#ifndef POTATO_PIPELINE_STATE_HPP
#define POTATO_PIPELINE_STATE_HPP

#include <Graphics/GraphicsEngine/interface/PipelineState.h>
#include <Common/interface/RefCntAutoPtr.hpp>
#include <Graphics/GraphicsTools/interface/MapHelper.hpp>

#include <string>
#include <vector>

#include "Potato/Core.hpp"
#include "Potato/Application.hpp"
#include "Shader.hpp"
#include "Buffer.hpp"

namespace Potato
{
	enum class PipelineTypeEnum
	{
		GRAPHICS = 0,
		COMPUTE = 1,
		MESH = 2
	};

	struct ShaderConstantsData
	{
		const char* m_Name;
		uint32_t m_Size;
		ShaderTypeEnum m_ShaderType;
	};

	struct ShaderConstant
	{
		std::string m_Name;
		ShaderTypeEnum m_ShaderType;
		Diligent::RefCntAutoPtr<Diligent::IBuffer> m_Buffer;
	};

	class PipelineState
	{
	public:
		PipelineState(const std::string& t_Name, PipelineTypeEnum t_PipelineType = PipelineTypeEnum::GRAPHICS, Diligent::PRIMITIVE_TOPOLOGY t_PrimitiveTopology = Diligent::PRIMITIVE_TOPOLOGY_TRIANGLE_LIST);

		void Bind();

		void AddShader(const Shader& t_Shader);

		void CreateShaderConstants(const std::initializer_list<ShaderConstantsData>& t_ShaderConstants);

		template<typename T>
		void SetShaderConstants(ShaderTypeEnum t_ShaderType, const std::string& t_Name, const T& t_Data)
		{
			std::vector<ShaderConstant>::iterator shaderConstant = std::find_if(m_ShaderConstants.begin(), m_ShaderConstants.end(), [t_ShaderType, t_Name](const ShaderConstant& sc) { return sc.m_Name == t_Name && sc.m_ShaderType == t_ShaderType; });
			if (shaderConstant == m_ShaderConstants.end())
			{
				return;
			}
			// Map the buffer and write current world-view-projection matrix
			Diligent::MapHelper<T> CBConstants(Application::Get().GetWindow()->GetRenderContext()->GetImmediateContext(), shaderConstant->m_Buffer, Diligent::MAP_WRITE, Diligent::MAP_FLAG_DISCARD);
			*CBConstants = t_Data;
		}

		void SetVertexLayout(const BufferLayout& t_LayoutBuffer)
		{
			m_BufferLayout = t_LayoutBuffer;
		}

		void SetCullMode(Diligent::CULL_MODE t_Mode) { this->m_CullMode = t_Mode; }

		void SetDepthEnabled(bool t_DepthEnabled) { this->m_DepthEnabled = t_DepthEnabled; }

		void Create();

	private:
		std::string m_Name;
		PipelineTypeEnum m_PipelineType;
		Diligent::PRIMITIVE_TOPOLOGY m_PrimitiveTopology;
		Diligent::CULL_MODE m_CullMode{ Diligent::CULL_MODE_BACK };
		bool m_DepthEnabled{ false };

		Diligent::RefCntAutoPtr<Diligent::IPipelineState> m_pPSO;
		Diligent::RefCntAutoPtr<Diligent::IShaderResourceBinding> m_pSRB;

		std::vector<ShaderConstant> m_ShaderConstants;
		std::vector<Shader> m_Shaders;
		BufferLayout m_BufferLayout{};
	};
}	// namespace Potato

#endif