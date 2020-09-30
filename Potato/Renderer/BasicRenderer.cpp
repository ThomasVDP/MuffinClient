#include "BasicRenderer.hpp"

#include <Common/interface/BasicMath.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

		s_Data.vertexBuffer.SetLayout({ { 0, 0, 3, Diligent::VT_FLOAT32, Diligent::False },
										{ 1, 0, 4, Diligent::VT_FLOAT32, Diligent::False } });

		s_Data.pipeline.SetVertexLayout(s_Data.vertexBuffer);
		s_Data.pipeline.Create();
		s_Data.pipeline.CreateShaderConstants({ { "Constants", sizeof(VertexShaderConstants), ShaderTypeEnum::VERTEX } });

		Vertex triangleVertices[4] = {
			{ Diligent::float3(-0.5, 0.5, 0), Diligent::float4(1, 0, 0, 1) },
			{ Diligent::float3(0.5, 0.5, 0), Diligent::float4(0, 1, 0, 1) },
			{ Diligent::float3(-0.5, -0.5, 0), Diligent::float4(0, 0, 1, 1) },
			{ Diligent::float3(0.5, -0.5, 0), Diligent::float4(1, 0, 0, 1) }
		};
		s_Data.vertexBuffer.Create(sizeof(triangleVertices), &triangleVertices);

		uint32_t triangleIndices[6] = {
			0, 1, 2,
			2, 1, 3
		};
		s_Data.indexBuffer.Create(sizeof(triangleIndices), triangleIndices);
	}

	void BasicRenderer::BeginScene(const OrthographicCamera& t_Camera)
	{
		s_Data.pipeline.SetShaderConstants<VertexShaderConstants>(ShaderTypeEnum::VERTEX, "Constants", { t_Camera.GetViewProjectionMatrix() });
	}

	void BasicRenderer::DrawTriangle(const glm::vec2& t_Position)
	{
		s_Data.vertexBuffer.Bind();
		s_Data.indexBuffer.Bind();

		s_Data.pipeline.Bind();
		RenderCommand::DrawIndexed(6);
	}
}	// namespace Potato
