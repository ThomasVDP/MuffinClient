#include "Skybox.hpp"

#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include <Common/interface/BasicMath.hpp>

#include "Potato/Application.hpp"

namespace Muffin
{
	struct Vertex
	{
		Diligent::float3 pos;
		Diligent::float2 uv;
	};

	struct ViewProjectionConstants
	{
		glm::mat4 m_ViewProj;
	};

	Skybox::Skybox(const std::string& t_SkyboxFile) :
		m_PipelineState("Skybox pipeline state")
	{
		Potato::Shader vertexShader("assets/shaders/skybox.vsh", Potato::ShaderTypeEnum::VERTEX);
		Potato::Shader pixelShader("assets/shaders/skybox.psh", Potato::ShaderTypeEnum::PIXEL);

		m_PipelineState.SetDepthEnabled(false);
		m_PipelineState.SetCullMode(Diligent::CULL_MODE_BACK);
		m_PipelineState.SetCustomFormats(true);
		m_PipelineState.SetRenderFormats(Potato::RenderTarget::RenderTargetFormat, Potato::RenderTarget::DepthBufferFormat);

		m_PipelineState.AddShader(vertexShader);
		m_PipelineState.AddShader(pixelShader);

		m_PipelineState.SetVertexLayout({ { 0, 0, 3, Diligent::VT_FLOAT32, Diligent::False },
										  { 1, 0, 2, Diligent::VT_FLOAT32, Diligent::False } });

		m_Texture = Potato::Texture(t_SkyboxFile, "g_Texture");
		m_PipelineState.Create(m_Texture.GetTextureName());
		m_PipelineState.CreateShaderConstants({ { "ViewProjConstants", sizeof(ViewProjectionConstants), Potato::ShaderTypeEnum::VERTEX } });
		m_PipelineState.CreateShaderResourceBinding();
		m_PipelineState.BindTexture(m_Texture.GetTextureName(), m_Texture.GetTextureSRV());

		Vertex CubeMapVertices[] = {
			//north
			{ { -0.5f, -0.5f, -0.5f }, { 1.0f / 3.0f, 1.0f } },
			{ { -0.5f, 0.5f, -0.5f }, { 1.0f / 3.0f, 0.5f } },
			{ { 0.5f, 0.5f, -0.5f }, { 2.0f / 3.0f, 0.5f } },
			{ { 0.5f, -0.5f, -0.5f }, { 2.0f / 3.0f, 1.0f } },

			//east
			{ { 0.5f, -0.5f, -0.5f }, { 2.0f / 3.0f, 1.0f } },
			{ { 0.5f, 0.5f, -0.5f }, { 2.0f / 3.0f, 0.5f } },
			{ { 0.5f, 0.5f, 0.5f }, { 1.0f, 0.5f } },
			{ { 0.5f, -0.5f, 0.5f }, { 1.0f, 1.0f } },

			//south
			{ { 0.5f, -0.5f, 0.5f }, { 2.0f / 3.0f, 0.5f } },
			{ { 0.5f, 0.5f, 0.5f }, { 2.0f / 3.0f, 0.0f } },
			{ { -0.5f, 0.5f, 0.5f }, { 1.0f, 0.0f } },
			{ { -0.5f, -0.5f, 0.5f }, { 1.0f, 0.5f } },

			//west
			{ { -0.5f, -0.5f, 0.5f }, { 0.0f, 1.0f } },
			{ { -0.5f, 0.5f, 0.5f }, { 0.0f, 0.5f } },
			{ { -0.5f, 0.5f, -0.5f }, { 1.0f / 3.0f, 0.5f } },
			{ { -0.5f, -0.5f, -0.5f }, { 1.0f / 3.0f, 1.0f } },

			//up
			{ { -0.5f, 0.5f, -0.5f }, { 1.0f / 3.0f, 0.5f } },
			{ { -0.5f, 0.5f, 0.5f }, { 1.0f / 3.0f, 0.0f } },
			{ { 0.5f, 0.5f, 0.5f }, { 2.0f / 3.0f, 0.0f } },
			{ { 0.5f, 0.5f, -0.5f }, { 2.0f / 3.0f, 0.5f } },

			//down
			{ { -0.5f, -0.5f, 0.5f }, { 0.0f, 0.5f } },
			{ { -0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f } },
			{ { 0.5f, -0.5f, -0.5f }, { 1.0f / 3.0f, 0.0f } },
			{ { 0.5f, -0.5f, 0.5f }, { 1.0f / 3.0f, 0.5f } }
		};
		m_VertexBuffer.Create(Potato::BufferUsage::STATIC, sizeof(CubeMapVertices), &CubeMapVertices);

		uint32_t CubeMapIndices[] = {
			0, 1, 2, 2, 3, 0,
			4, 5, 6, 6, 7, 4,
			8, 9, 10, 10, 11, 8,
			12, 13, 14, 14, 15, 12,
			16, 17, 18, 18, 19, 16,
			20, 21, 22, 22, 23, 20,
			24, 25, 26, 26, 27, 24
		};
		m_IndexBuffer.Create(sizeof(CubeMapIndices), CubeMapIndices);
	}

	void Skybox::OnRender(const Potato::Camera& t_Camera)
	{
		//glm::mat4 viewProj = t_Camera.GetViewProjectionMatrix();
		glm::mat4 viewProj = t_Camera.GetProjectionMatrix() * glm::mat4(glm::mat3(t_Camera.GetViewMatrix()));

		m_PipelineState.SetShaderConstants<ViewProjectionConstants>(Potato::ShaderTypeEnum::VERTEX, "ViewProjConstants", { viewProj });

		m_VertexBuffer.Bind();
		m_IndexBuffer.Bind();
		m_PipelineState.Bind();
		Potato::RenderCommand::DrawIndexed(m_IndexBuffer.GetCount());
	}
}	// namespace Muffin
