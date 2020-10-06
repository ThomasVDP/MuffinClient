#include "DefaultRenderTargetObject.hpp"

#include "Potato/Application.hpp"
#include "Potato/Renderer/RenderCommand.hpp"

namespace Potato
{
	DefaultRenderTargetObject::DefaultRenderTargetObject(const glm::vec4& t_ClearColor) :
		m_RenderTarget(t_ClearColor), m_PipelineState("Default render target", PipelineTypeEnum::GRAPHICS, Diligent::PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP)
	{
	}

	void DefaultRenderTargetObject::Init(const std::string& t_VertShader, const std::string& t_PixelShader)
	{
		Shader vertexShader(t_VertShader, ShaderTypeEnum::VERTEX);
		Shader pixelShader(t_PixelShader, ShaderTypeEnum::PIXEL);

		m_PipelineState.SetDepthEnabled(false);
		m_PipelineState.SetCullMode(Diligent::CULL_MODE_BACK);

		m_PipelineState.AddShader(vertexShader);
		m_PipelineState.AddShader(pixelShader);

		m_PipelineState.Create("g_Texture");
		m_PipelineState.CreateShaderResourceBinding();

		m_PipelineState.BindTexture("g_Texture", m_RenderTarget.CreateRenderTargets());
	}

	void DefaultRenderTargetObject::Bind()
	{
		const glm::vec4& clearColor = m_RenderTarget.GetOptimalClearColor();
		const float ClearColor[] = { clearColor.r, clearColor.g, clearColor.b, clearColor.a };

		Diligent::RefCntAutoPtr<Diligent::IDeviceContext> pImmediateContext = Application::Get().GetWindow()->GetRenderContext()->GetImmediateContext();
		pImmediateContext->SetRenderTargets(1, &m_RenderTarget.GetColorView(), m_RenderTarget.GetDepthBuffer(), Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
		pImmediateContext->ClearRenderTarget(m_RenderTarget.GetColorView(), ClearColor, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
		pImmediateContext->ClearDepthStencil(m_RenderTarget.GetDepthBuffer(), Diligent::CLEAR_DEPTH_FLAG, 1.0f, 0, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
	}

	void DefaultRenderTargetObject::RenderToScreen()
	{
		m_PipelineState.Bind();

		RenderCommand::DrawVertices(4);
	}

	void DefaultRenderTargetObject::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowResizeEvent>(POTATO_BIND_EVENT_FN(DefaultRenderTargetObject::OnWindowResize));
	}

	bool DefaultRenderTargetObject::OnWindowResize(WindowResizeEvent& e)
	{
		m_PipelineState.ReleaseResourceBinding();
		m_PipelineState.CreateShaderResourceBinding();
		m_PipelineState.BindTexture("g_Texture", m_RenderTarget.CreateRenderTargets());

		return false;
	}
}	// namespace Potato
