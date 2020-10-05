#include "BlockRenderer.hpp"

#include <Common/interface/BasicMath.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include "RenderCommand.hpp"
#include "PipelineState.hpp"
#include "RenderTarget.hpp"

namespace Potato
{
	struct Vertex
	{
		Diligent::float3 pos;
		Diligent::float2 uv;
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
		Potato::Texture dirtTexture;
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
		Shader vertexShader("assets/shaders/vertex.vsh", ShaderTypeEnum::VERTEX);
		Shader pixelShader("assets/shaders/pixel.vsh", ShaderTypeEnum::PIXEL);

		s_Data.pipeline.SetDepthEnabled(true);
		s_Data.pipeline.SetCullMode(Diligent::CULL_MODE_NONE);
		s_Data.pipeline.SetCustomFormats(true);
		s_Data.pipeline.SetRenderFormats(RenderTarget::RenderTargetFormat, RenderTarget::DepthBufferFormat);

		s_Data.pipeline.AddShader(vertexShader);
		s_Data.pipeline.AddShader(pixelShader);

		s_Data.pipeline.SetVertexLayout({ { 0, 0, 3, Diligent::VT_FLOAT32, Diligent::False },
										  { 1, 0, 2, Diligent::VT_FLOAT32, Diligent::False } });

		s_Data.dirtTexture = Texture("dirt.png", "g_Texture");
		s_Data.pipeline.Create(s_Data.dirtTexture.GetTextureName());
		s_Data.pipeline.CreateShaderConstants({ { "ViewProjConstants", sizeof(VertexShaderViewProjConstants), ShaderTypeEnum::VERTEX },
												{ "TransformConstants", sizeof(VertexShaderTransformConstants), ShaderTypeEnum::VERTEX } });
		s_Data.pipeline.CreateShaderResourceBinding();
		s_Data.pipeline.BindTexture(s_Data.dirtTexture.GetTextureName(), s_Data.dirtTexture.GetTextureSRV());
		POTATO_CORE_INFO("Bound texture: {}", s_Data.dirtTexture.GetTextureName());

		Vertex blockVertices[4] = {
			{ { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f } },
			{ { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f } },
			{ { 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f } },
			{ { 1.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } }
			// { { 1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
			// { { 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
			// { { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
			// { { 0.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } }
		};
		s_Data.vertexBuffer.Create(BufferUsage::STATIC, sizeof(blockVertices), &blockVertices);

		uint32_t squareIndices[6] = {
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
