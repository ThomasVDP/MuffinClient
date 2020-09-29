#include "BasicRenderer.hpp"

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

	struct BasicRendererData
	{
		Potato::PipelineState pipeline = PipelineState("Triangle pipeline!");
		Potato::VertexBuffer vertexBuffer;
		Potato::IndexBuffer indexBuffer;
	};

	static BasicRendererData s_Data;

	void BasicRenderer::Init()
	{
		Shader vertexShader("vertex.vsh", ShaderTypeEnum::VERTEX);
		Shader pixelShader("pixel.vsh", ShaderTypeEnum::PIXEL);

		s_Data.pipeline.AddShader(vertexShader);
		s_Data.pipeline.AddShader(pixelShader);

		s_Data.vertexBuffer.SetLayout({ { 0, 0, 3, Diligent::VT_FLOAT32, Diligent::True },
										{ 1, 0, 4, Diligent::VT_FLOAT32, Diligent::False } });

		s_Data.pipeline.SetVertexLayout(s_Data.vertexBuffer);
		s_Data.pipeline.Create();

		Vertex triangleVertices[4] = {
			{ Diligent::float3(-0.5, 0.5, 0), Diligent::float4(1, 0, 0, 1) },
			{ Diligent::float3(0.5, 0.5, 0), Diligent::float4(0, 1, 0, 1) },
			{ Diligent::float3(-0.5, -0.5, 0), Diligent::float4(0, 0, 1, 1) },
			{ Diligent::float3(0.5, -0.5, 0), Diligent::float4(1, 1, 0, 1) }
		};
		s_Data.vertexBuffer.Create(sizeof(triangleVertices), &triangleVertices);

		uint32_t triangleIndices[6] = {
			0, 1, 2,
			2, 1, 3
		};
		s_Data.indexBuffer.Create(sizeof(triangleIndices), triangleIndices);
	}

	void BasicRenderer::DrawTriangle()
	{
		s_Data.vertexBuffer.Bind();
		s_Data.indexBuffer.Bind();

		s_Data.pipeline.Bind();
		RenderCommand::DrawIndexed(6);
	}
}	// namespace Potato
