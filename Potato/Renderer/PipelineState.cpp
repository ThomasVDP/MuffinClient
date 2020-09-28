#include "PipelineState.hpp"

#include <Graphics/GraphicsEngine/interface/SwapChain.h>

#include "Potato/Application.hpp"

namespace Potato
{
	PipelineState::PipelineState(const std::string& t_Name, PipelineTypeEnum t_PipelineType, Diligent::PRIMITIVE_TOPOLOGY t_PrimitiveTopology) :
		m_Name(t_Name), m_PipelineType(t_PipelineType), m_PrimitiveTopology(t_PrimitiveTopology)
	{
	}

	void PipelineState::Create(const std::string& t_VertexPath, const std::string& t_PixelPath)
	{
		Diligent::PipelineStateCreateInfo PSOCreateInfo;
		Diligent::PipelineStateDesc& PSODesc = PSOCreateInfo.PSODesc;
		PSODesc.Name = this->m_Name.c_str();
		switch (m_PipelineType)
		{
		case PipelineTypeEnum::GRAPHICS: PSODesc.PipelineType = Diligent::PIPELINE_TYPE_GRAPHICS; break;
		case PipelineTypeEnum::COMPUTE: PSODesc.PipelineType = Diligent::PIPELINE_TYPE_COMPUTE; break;
		case PipelineTypeEnum::MESH: PSODesc.PipelineType = Diligent::PIPELINE_TYPE_MESH; break;
		}

		Diligent::RefCntAutoPtr<Diligent::ISwapChain> swapChain = Application::Get().GetWindow()->GetRenderContext()->GetSwapChain();
		PSODesc.GraphicsPipeline.NumRenderTargets = 1;
		PSODesc.GraphicsPipeline.RTVFormats[0] = swapChain->GetDesc().ColorBufferFormat;
		PSODesc.GraphicsPipeline.DSVFormat = swapChain->GetDesc().DepthBufferFormat;

		PSODesc.GraphicsPipeline.PrimitiveTopology = m_PrimitiveTopology;
		PSODesc.GraphicsPipeline.RasterizerDesc.CullMode = m_CullMode;
		PSODesc.GraphicsPipeline.DepthStencilDesc.DepthEnable = m_DepthEnabled;

		Diligent::RefCntAutoPtr<Diligent::IShader> pVS = CreateShader(t_VertexPath, Diligent::SHADER_TYPE_VERTEX);
		Diligent::RefCntAutoPtr<Diligent::IShader> pPS = CreateShader(t_PixelPath, Diligent::SHADER_TYPE_PIXEL);

		PSODesc.GraphicsPipeline.pVS = pVS;
		PSODesc.GraphicsPipeline.pPS = pPS;
		Application::Get().GetWindow()->GetRenderContext()->GetRenderDevice()->CreatePipelineState(PSOCreateInfo, &m_pPSO);
	}

	void PipelineState::Bind()
	{
		Application::Get().GetWindow()->GetRenderContext()->GetImmediateContext()->SetPipelineState(m_pPSO);
	}

	Diligent::RefCntAutoPtr<Diligent::IShader> PipelineState::CreateShader(const std::string& t_ShaderPath, Diligent::SHADER_TYPE t_ShaderType)
	{
		Diligent::ShaderCreateInfo ShaderCI;
		ShaderCI.SourceLanguage = Diligent::SHADER_SOURCE_LANGUAGE_HLSL;
		ShaderCI.UseCombinedTextureSamplers = true;

		Diligent::RefCntAutoPtr<Diligent::IShaderSourceInputStreamFactory> pShaderSourceFactory;
		Application::Get().GetWindow()->GetRenderContext()->GetEngineFactory()->CreateDefaultShaderSourceStreamFactory(nullptr, &pShaderSourceFactory);
		ShaderCI.pShaderSourceStreamFactory = pShaderSourceFactory;

		// Create a vertex shader
		Diligent::RefCntAutoPtr<Diligent::IShader> pShader;
		{
			ShaderCI.Desc.ShaderType = t_ShaderType;
			ShaderCI.EntryPoint = "main";
			ShaderCI.Desc.Name = (t_ShaderPath + ", shader type: " + std::to_string(t_ShaderType)).c_str();
			ShaderCI.FilePath = t_ShaderPath.c_str();
			Application::Get().GetWindow()->GetRenderContext()->GetRenderDevice()->CreateShader(ShaderCI, &pShader);
		}

		return pShader;
	}
}	// namespace Potato
