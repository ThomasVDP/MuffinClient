#include "PipelineState.hpp"

#include <Graphics/GraphicsEngine/interface/SwapChain.h>

#include "Potato/Application.hpp"

namespace Potato
{
	PipelineState::PipelineState(const std::string& t_Name, PipelineTypeEnum t_PipelineType, Diligent::PRIMITIVE_TOPOLOGY t_PrimitiveTopology) :
		m_Name(t_Name), m_PipelineType(t_PipelineType), m_PrimitiveTopology(t_PrimitiveTopology)
	{
	}

	void PipelineState::Bind()
	{
		Application::Get().GetWindow()->GetRenderContext()->GetImmediateContext()->SetPipelineState(m_pPSO);
		Application::Get().GetWindow()->GetRenderContext()->GetImmediateContext()->CommitShaderResources(m_pSRB, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
	}

	void PipelineState::AddShader(const Shader& t_Shader)
	{
		if (std::find_if(m_Shaders.begin(), m_Shaders.end(), [&t_Shader](const Shader& shader) { return shader.GetShaderType() == t_Shader.GetShaderType(); }) == m_Shaders.end())
		{
			m_Shaders.push_back(t_Shader);
		}
		else
		{
			const char* shaderType;
			switch (t_Shader.GetShaderType())
			{
			case ShaderTypeEnum::VERTEX: shaderType = "Vertex"; break;
			case ShaderTypeEnum::PIXEL: shaderType = "Pixel"; break;
			}

			POTATO_CORE_WARN("Already bound {0} Shader to pipeline state! (this will get ignored)", shaderType);
		}
	}

	void PipelineState::Create()
	{
		Diligent::PipelineStateCreateInfo PSOCreateInfo;
		Diligent::PipelineStateDesc& PSODesc = PSOCreateInfo.PSODesc;
		PSODesc.Name = this->m_Name.c_str();

		//set pipline type
		switch (m_PipelineType)
		{
		case PipelineTypeEnum::GRAPHICS: PSODesc.PipelineType = Diligent::PIPELINE_TYPE_GRAPHICS; break;
		case PipelineTypeEnum::COMPUTE: PSODesc.PipelineType = Diligent::PIPELINE_TYPE_COMPUTE; break;
		case PipelineTypeEnum::MESH: PSODesc.PipelineType = Diligent::PIPELINE_TYPE_MESH; break;
		}

		//default settings
		Diligent::RefCntAutoPtr<Diligent::ISwapChain> swapChain = Application::Get().GetWindow()->GetRenderContext()->GetSwapChain();
		PSODesc.GraphicsPipeline.NumRenderTargets = 1;
		PSODesc.GraphicsPipeline.RTVFormats[0] = swapChain->GetDesc().ColorBufferFormat;
		PSODesc.GraphicsPipeline.DSVFormat = swapChain->GetDesc().DepthBufferFormat;

		PSODesc.GraphicsPipeline.PrimitiveTopology = m_PrimitiveTopology;
		PSODesc.GraphicsPipeline.RasterizerDesc.CullMode = m_CullMode;
		PSODesc.GraphicsPipeline.DepthStencilDesc.DepthEnable = m_DepthEnabled;

		//set shaders
		for (const Shader& shader : m_Shaders)
		{
			switch (shader.GetShaderType())
			{
			case ShaderTypeEnum::VERTEX: PSODesc.GraphicsPipeline.pVS = shader.GetShader(); break;
			case ShaderTypeEnum::PIXEL: PSODesc.GraphicsPipeline.pPS = shader.GetShader(); break;
			}
		}

		// Define vertex shader input layout
		PSODesc.GraphicsPipeline.InputLayout.LayoutElements = m_BufferLayout.GetElements().data();
		PSODesc.GraphicsPipeline.InputLayout.NumElements = m_BufferLayout.GetElements().size();

		// Define variable type that will be used by default
		PSODesc.ResourceLayout.DefaultVariableType = Diligent::SHADER_RESOURCE_VARIABLE_TYPE_STATIC;

		//create the PipelineStateObject
		Application::Get().GetWindow()->GetRenderContext()->GetRenderDevice()->CreatePipelineState(PSOCreateInfo, &m_pPSO);
	}

	void PipelineState::CreateShaderConstants(const std::initializer_list<ShaderConstantsData>& t_ShaderConstants)
	{
		for (ShaderConstantsData shaderConstants : t_ShaderConstants)
		{
			Diligent::RefCntAutoPtr<Diligent::IBuffer> iBuffer;
			Diligent::BufferDesc CBDesc;
			CBDesc.Name = shaderConstants.m_Name;
			CBDesc.uiSizeInBytes = shaderConstants.m_Size;
			CBDesc.Usage = Diligent::USAGE_DYNAMIC;
			CBDesc.BindFlags = Diligent::BIND_UNIFORM_BUFFER;
			CBDesc.CPUAccessFlags = Diligent::CPU_ACCESS_WRITE;
			Application::Get().GetWindow()->GetRenderContext()->GetRenderDevice()->CreateBuffer(CBDesc, nullptr, &iBuffer);

			switch (shaderConstants.m_ShaderType)
			{
			case ShaderTypeEnum::VERTEX: m_pPSO->GetStaticVariableByName(Diligent::SHADER_TYPE_VERTEX, shaderConstants.m_Name)->Set(iBuffer); break;
			case ShaderTypeEnum::PIXEL: m_pPSO->GetStaticVariableByName(Diligent::SHADER_TYPE_PIXEL, shaderConstants.m_Name)->Set(iBuffer); break;
			}
			m_ShaderConstants.push_back({ shaderConstants.m_Name, shaderConstants.m_ShaderType, iBuffer });
		}

		m_pPSO->CreateShaderResourceBinding(&m_pSRB, true);
	}
}	// namespace Potato
