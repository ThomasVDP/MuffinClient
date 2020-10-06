#include "RenderTarget.hpp"

#include "Potato/Application.hpp"
#include "RenderCommand.hpp"

namespace Potato
{
	RenderTarget::RenderTarget(const glm::vec4& t_ClearColor) :
		m_ClearColor(t_ClearColor)
	{
	}

	Diligent::RefCntAutoPtr<Diligent::ITextureView> RenderTarget::CreateRenderTargets()
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
		RTColorDesc.ClearValue.Color[0] = m_ClearColor.r;
		RTColorDesc.ClearValue.Color[1] = m_ClearColor.g;
		RTColorDesc.ClearValue.Color[2] = m_ClearColor.b;
		RTColorDesc.ClearValue.Color[3] = m_ClearColor.a;
		Application::Get().GetWindow()->GetRenderContext()->GetRenderDevice()->CreateTexture(RTColorDesc, nullptr, &pRTColor);
		m_pColorRTV = pRTColor->GetDefaultView(Diligent::TEXTURE_VIEW_RENDER_TARGET);

		Diligent::RefCntAutoPtr<Diligent::ITexture> pRTDepth;
		Diligent::TextureDesc RTDepthDesc = RTColorDesc;
		RTDepthDesc.Format = DepthBufferFormat;
		RTDepthDesc.BindFlags = Diligent::BIND_SHADER_RESOURCE | Diligent::BIND_DEPTH_STENCIL;
		Application::Get().GetWindow()->GetRenderContext()->GetRenderDevice()->CreateTexture(RTDepthDesc, nullptr, &pRTDepth);
		m_pDepthDSV = pRTDepth->GetDefaultView(Diligent::TEXTURE_VIEW_DEPTH_STENCIL);

		return Diligent::RefCntAutoPtr<Diligent::ITextureView>(pRTColor->GetDefaultView(Diligent::TEXTURE_VIEW_SHADER_RESOURCE));
	}
}	// namespace Potato
