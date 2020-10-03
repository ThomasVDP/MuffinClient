#include "QuadRenderer.hpp"

#include <Common/interface/BasicMath.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

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

	struct QuadRendererData
	{
		static const uint32_t MaxQuads = 20000;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;

		Potato::PipelineState pipeline = PipelineState("Quad pipeline!");
		Potato::VertexBuffer vertexBuffer;
		Potato::IndexBuffer indexBuffer;
	};

	static QuadRendererData s_Data;

	void QuadRenderer::Init()
	{
		Shader vertexShader("shaders/vertex.vsh", ShaderTypeEnum::VERTEX);
		Shader pixelShader("shaders/pixel.vsh", ShaderTypeEnum::PIXEL);

		s_Data.pipeline.AddShader(vertexShader);
		s_Data.pipeline.AddShader(pixelShader);

		s_Data.pipeline.SetVertexLayout({ { 0, 0, 3, Diligent::VT_FLOAT32, Diligent::False },
										  { 1, 0, 4, Diligent::VT_FLOAT32, Diligent::False } });
		s_Data.pipeline.Create();
		s_Data.pipeline.CreateShaderConstants({ { "ViewProjConstants", sizeof(VertexShaderViewProjConstants), ShaderTypeEnum::VERTEX },
												{ "TransformConstants", sizeof(VertexShaderTransformConstants), ShaderTypeEnum::VERTEX } });

		Vertex squareVertices[4] = {
			{ { -0.5, 0.5, 0 }, Diligent::float4(1, 0, 0, 1) },
			{ Diligent::float3(0.5, 0.5, 0), Diligent::float4(0, 1, 0, 1) },
			{ Diligent::float3(-0.5, -0.5, 0), Diligent::float4(0, 0, 1, 1) },
			{ Diligent::float3(0.5, -0.5, 0), Diligent::float4(1, 0, 0, 1) }
		};
		s_Data.vertexBuffer.Create(BufferUsage::STATIC, sizeof(squareVertices), &squareVertices);

		uint32_t squareIndices[6] = {
			0, 1, 2,
			2, 1, 3
		};
		s_Data.indexBuffer.Create(sizeof(squareIndices), squareIndices);
	}

	void QuadRenderer::Shutdown()
	{
	}

	void QuadRenderer::BeginScene(const Camera& t_Camera)
	{
		s_Data.pipeline.SetShaderConstants<VertexShaderViewProjConstants>(ShaderTypeEnum::VERTEX, "ViewProjConstants", { t_Camera.GetViewProjectionMatrix() });
	}

	void QuadRenderer::DrawQuad(const glm::vec3& t_Position, const glm::vec3& t_Rotation)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), t_Position);
		glm::quat quatX = glm::angleAxis<float, glm::defaultp>(glm::radians(t_Rotation.x), { 1.0f, 0.0f, 0.0f });
		glm::quat quatY = glm::angleAxis<float, glm::defaultp>(glm::radians(t_Rotation.y), { 0.0f, 1.0f, 0.0f });
		glm::quat quatZ = glm::angleAxis<float, glm::defaultp>(glm::radians(t_Rotation.z), { 0.0f, 0.0f, 1.0f });
		glm::quat finalQuat = quatY * quatX * quatZ;
		transform *= glm::toMat4(finalQuat);

		s_Data.pipeline.SetShaderConstants<VertexShaderTransformConstants>(ShaderTypeEnum::VERTEX, "TransformConstants", { transform });

		s_Data.vertexBuffer.Bind();
		s_Data.indexBuffer.Bind();
		s_Data.pipeline.Bind();
		RenderCommand::DrawIndexed(s_Data.indexBuffer.GetCount());
	}
}	// namespace Potato
