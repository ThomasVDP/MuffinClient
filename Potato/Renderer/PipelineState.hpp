#ifndef POTATO_PIPELINE_STATE_HPP
#define POTATO_PIPELINE_STATE_HPP

#include <Graphics/GraphicsEngine/interface/PipelineState.h>
#include <Common/interface/RefCntAutoPtr.hpp>

#include <string>
#include <vector>

#include "Potato/Core.hpp"
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

	class PipelineState
	{
	public:
		PipelineState(const std::string& t_Name, PipelineTypeEnum t_PipelineType = PipelineTypeEnum::GRAPHICS, Diligent::PRIMITIVE_TOPOLOGY t_PrimitiveTopology = Diligent::PRIMITIVE_TOPOLOGY_TRIANGLE_LIST);

		void Bind();

		void AddShader(const Shader& t_Shader);

		void SetVertexLayout(const VertexBuffer& t_VertexBuffer) { m_BufferLayout = t_VertexBuffer.GetLayout(); }

		void SetCullMode(Diligent::CULL_MODE t_Mode) { this->m_CullMode = t_Mode; }

		void SetDepthEnabled(bool t_DepthEnabled) { this->m_DepthEnabled = t_DepthEnabled; }

		void Create();

	private:
		std::string m_Name;
		PipelineTypeEnum m_PipelineType;
		Diligent::PRIMITIVE_TOPOLOGY m_PrimitiveTopology;
		Diligent::CULL_MODE m_CullMode{ Diligent::CULL_MODE_NONE };
		bool m_DepthEnabled{ false };

		Diligent::RefCntAutoPtr<Diligent::IPipelineState> m_pPSO;

		std::vector<Shader> m_Shaders;
		BufferLayout m_BufferLayout{};
	};
}	// namespace Potato

#endif