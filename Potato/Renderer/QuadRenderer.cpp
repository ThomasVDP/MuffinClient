#include "QuadRenderer.hpp"

#include <Common/interface/BasicMath.hpp>

#include "RenderCommand.hpp"
#include "PipelineState.hpp"

namespace Potato
{
	struct Vertex
	{
		Diligent::float3 pos;
		Diligent::float4 color;
	};

	struct VertexShaderConstants
	{
		glm::mat4 m_ViewProjectionMatrix;
	};

	struct QuadRendererData
	{
		Potato::PipelineState pipeline = PipelineState("Quad pipeline!");
		Potato::VertexBuffer vertexBuffer;
		Potato::IndexBuffer indexBuffer;
	};

	static QuadRendererData s_Data;

	void QuadRenderer::Init()
	{
		Shader vertexShader("vertex.vsh", ShaderTypeEnum::VERTEX);
		Shader pixelShader("pixel.vsh", ShaderTypeEnum::PIXEL);

		s_Data.pipeline.AddShader(vertexShader);
		s_Data.pipeline.AddShader(pixelShader);

		s_Data.pipeline.SetVertexLayout({ { 0, 0, 3, Diligent::VT_FLOAT32, Diligent::False },
										  { 1, 0, 4, Diligent::VT_FLOAT32, Diligent::False } });
		s_Data.pipeline.Create();
		s_Data.pipeline.CreateShaderConstants({ { "Constants", sizeof(VertexShaderConstants), ShaderTypeEnum::VERTEX } });

		Vertex squareVertices[4] = {
			{ Diligent::float3(-0.5, 0.5, 0), Diligent::float4(1, 0, 0, 1) },
			{ Diligent::float3(0.5, 0.5, 0), Diligent::float4(0, 1, 0, 1) },
			{ Diligent::float3(-0.5, -0.5, 0), Diligent::float4(0, 0, 1, 1) },
			{ Diligent::float3(0.5, -0.5, 0), Diligent::float4(1, 0, 0, 1) }
		};
		s_Data.vertexBuffer.Create(sizeof(squareVertices), &squareVertices);

		uint32_t squareIndices[6] = {
			0, 1, 2,
			2, 1, 3
		};
		s_Data.indexBuffer.Create(sizeof(squareIndices), squareIndices);
	}

	void QuadRenderer::BeginScene(const Camera& t_Camera)
	{
		s_Data.pipeline.SetShaderConstants<VertexShaderConstants>(ShaderTypeEnum::VERTEX, "Constants", { t_Camera.GetViewProjectionMatrix() });
	}

	void QuadRenderer::DrawQuad()
	{
		s_Data.vertexBuffer.Bind();
		s_Data.indexBuffer.Bind();
		s_Data.pipeline.Bind();
		RenderCommand::DrawIndexed(s_Data.indexBuffer.GetCount());
	}
}	// namespace Potato
