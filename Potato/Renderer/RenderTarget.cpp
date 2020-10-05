#include "RenderTarget.hpp"

#include "Potato/Application.hpp"
#include "RenderCommand.hpp"

namespace Potato
{
	RenderTarget::RenderTarget(const std::string& t_PipelineName, float t_AspectRatio) :
		m_PipelineState(t_PipelineName, PipelineTypeEnum::GRAPHICS, Diligent::PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP), m_AspectRatio(t_AspectRatio)
	{
	}

	void RenderTarget::Create()
	{
		Shader vertexShader("assets/shaders/barreldistortion.vsh", ShaderTypeEnum::VERTEX);
		Shader pixelShader("assets/shaders/barreldistortion.psh", ShaderTypeEnum::PIXEL);

		m_PipelineState.SetDepthEnabled(false);
		m_PipelineState.SetCullMode(Diligent::CULL_MODE_BACK);

		m_PipelineState.AddShader(vertexShader);
		m_PipelineState.AddShader(pixelShader);

		m_PipelineState.Create("g_Texture");
		m_PipelineState.CreateShaderResourceBinding();

		CreateRenderTargets();
	}

	void RenderTarget::Bind(const glm::vec4& t_Color)
	{
		const float ClearColor[] = { t_Color.r, t_Color.g, t_Color.b, t_Color.a };

		Diligent::RefCntAutoPtr<Diligent::IDeviceContext> pImmediateContext = Application::Get().GetWindow()->GetRenderContext()->GetImmediateContext();
		pImmediateContext->SetRenderTargets(1, &m_pColorRTV, m_pDepthDSV, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
		pImmediateContext->ClearRenderTarget(m_pColorRTV, ClearColor, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
		pImmediateContext->ClearDepthStencil(m_pDepthDSV, Diligent::CLEAR_DEPTH_FLAG, 1.0f, 0, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
	}

	void RenderTarget::RenderToScreen()
	{
		m_PipelineState.Bind();

		RenderCommand::DrawVertices(4);

		// Diligent::DrawAttribs RTDrawAttrs;
		// RTDrawAttrs.NumVertices = 4;
		// RTDrawAttrs.Flags = Diligent::DRAW_FLAG_VERIFY_ALL;	  // Verify all states
		// Application::Get().GetWindow()->GetRenderContext()->GetImmediateContext()->Draw(RTDrawAttrs);
	}

	void RenderTarget::CreateRenderTargets()
	{
		Diligent::RefCntAutoPtr<Diligent::ITexture> pRTColor;
		Diligent::TextureDesc RTColorDesc;
		RTColorDesc.Type = Diligent::RESOURCE_DIM_TEX_2D;
		RTColorDesc.Width = Application::Get().GetWindow()->GetRenderContext()->GetSwapChain()->GetDesc().Width;
		RTColorDesc.Height = Application::Get().GetWindow()->GetRenderContext()->GetSwapChain()->GetDesc().Height;
		RTColorDesc.MipLevels = 1;
		RTColorDesc.Format = RenderTargetFormat;
		RTColorDesc.BindFlags = Diligent::BIND_SHADER_RESOURCE | Diligent::BIND_RENDER_TARGET;
		// Define optimal clear value
		RTColorDesc.ClearValue.Format = RTColorDesc.Format;
		RTColorDesc.ClearValue.Color[0] = 0.350f;
		RTColorDesc.ClearValue.Color[1] = 0.350f;
		RTColorDesc.ClearValue.Color[2] = 0.350f;
		RTColorDesc.ClearValue.Color[3] = 1.f;
		Application::Get().GetWindow()->GetRenderContext()->GetRenderDevice()->CreateTexture(RTColorDesc, nullptr, &pRTColor);
		m_pColorRTV = pRTColor->GetDefaultView(Diligent::TEXTURE_VIEW_RENDER_TARGET);

		Diligent::RefCntAutoPtr<Diligent::ITexture> pRTDepth;
		Diligent::TextureDesc RTDepthDesc = RTColorDesc;
		RTDepthDesc.Format = DepthBufferFormat;
		RTDepthDesc.BindFlags = Diligent::BIND_SHADER_RESOURCE | Diligent::BIND_DEPTH_STENCIL;
		Application::Get().GetWindow()->GetRenderContext()->GetRenderDevice()->CreateTexture(RTDepthDesc, nullptr, &pRTDepth);
		m_pDepthDSV = pRTDepth->GetDefaultView(Diligent::TEXTURE_VIEW_DEPTH_STENCIL);

		m_PipelineState.ReleaseResourceBinding();
		m_PipelineState.CreateShaderResourceBinding();
		m_PipelineState.BindTexture("g_Texture", Diligent::RefCntAutoPtr<Diligent::ITextureView>(pRTColor->GetDefaultView(Diligent::TEXTURE_VIEW_SHADER_RESOURCE)));
	}

	void RenderTarget::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowResizeEvent>(POTATO_BIND_EVENT_FN(RenderTarget::OnWindowResize));
	}

	bool RenderTarget::OnWindowResize(WindowResizeEvent& e)
	{
		CreateRenderTargets();
		m_AspectRatio = e.GetWidth() / e.GetHeight();
		return false;
	}
}	// namespace Potato
