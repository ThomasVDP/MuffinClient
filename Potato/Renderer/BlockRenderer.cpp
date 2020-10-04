#include "BlockRenderer.hpp"

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

	struct VertexShaderViewProjConstants
	{
		glm::mat4 m_ViewProjectionMatrix;
	};
	struct VertexShaderTransformConstants
	{
		glm::mat4 m_Transform;
	};

	struct BlockRenderData
	{
		Potato::PipelineState pipeline = PipelineState("Block pipeline!");
		Potato::VertexBuffer vertexBuffer;
		Potato::IndexBuffer indexBuffer;
	};

	static BlockRenderData s_Data;

	BlockRenderer::BlockRenderer()
	{
		Init();
	}

	BlockRenderer::~BlockRenderer()
	{
		Shutdown();
	}

	void BlockRenderer::Init()
	{
		Shader vertexShader("shaders/vertex.vsh", ShaderTypeEnum::VERTEX);
		Shader pixelShader("shaders/pixel.vsh", ShaderTypeEnum::PIXEL);

		s_Data.pipeline.SetDepthEnabled(true);

		s_Data.pipeline.AddShader(vertexShader);
		s_Data.pipeline.AddShader(pixelShader);

		s_Data.pipeline.SetVertexLayout({ { 0, 0, 3, Diligent::VT_FLOAT32, Diligent::False },
										  { 1, 0, 4, Diligent::VT_FLOAT32, Diligent::False } });
		s_Data.pipeline.Create();
		s_Data.pipeline.CreateShaderConstants({ { "ViewProjConstants", sizeof(VertexShaderViewProjConstants), ShaderTypeEnum::VERTEX },
												{ "TransformConstants", sizeof(VertexShaderTransformConstants), ShaderTypeEnum::VERTEX } });

		Vertex blockVertices[4] = {
			{ { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
			{ { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
			{ { 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
			{ { 1.0f, 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } }
			// { { 1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
			// { { 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
			// { { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
			// { { 0.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } }
		};
		s_Data.vertexBuffer.Create(BufferUsage::STATIC, sizeof(blockVertices), &blockVertices);

		uint32_t squareIndices[] = {
			0, 1, 3,
			0, 3, 2
		};
		s_Data.indexBuffer.Create(sizeof(squareIndices), squareIndices);
	}

	void BlockRenderer::Shutdown()
	{
	}

	void BlockRenderer::BeginScene(const Camera& t_Camera)
	{
		s_Data.pipeline.SetShaderConstants<VertexShaderViewProjConstants>(ShaderTypeEnum::VERTEX, "ViewProjConstants", { t_Camera.GetViewProjectionMatrix() });
	}

	void BlockRenderer::RenderFullBlock(const glm::vec3& t_Position)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), t_Position);

		s_Data.pipeline.SetShaderConstants<VertexShaderTransformConstants>(ShaderTypeEnum::VERTEX, "TransformConstants", { transform });

		s_Data.vertexBuffer.Bind();
		s_Data.indexBuffer.Bind();
		s_Data.pipeline.Bind();
		RenderCommand::DrawIndexed(s_Data.indexBuffer.GetCount());
	}
}	// namespace Potato
