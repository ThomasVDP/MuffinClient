#include "RendererAPI.hpp"

namespace Potato
{
	RendererAPI::RendererAPI(const Scope<GraphicsContext>& t_GraphicsContext) :
		m_GraphicsContext(t_GraphicsContext)
	{
	}

	void RendererAPI::OnWindowResize(uint32_t t_Width, uint32_t t_Height)
	{
		this->m_GraphicsContext->OnWindowResize(t_Width, t_Height);
	}

	void RendererAPI::Clear(const glm::vec4& color, bool t_IsUsingRenderTarget)
	{
		auto* pRTV = m_GraphicsContext->GetSwapChain()->GetCurrentBackBufferRTV();
		auto* pDSV = m_GraphicsContext->GetSwapChain()->GetDepthBufferDSV();
		m_GraphicsContext->GetImmediateContext()->SetRenderTargets(1, &pRTV, pDSV, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
		// Clear the back buffer
		const float ClearColor[] = { color.r, color.g, color.b, color.a };
		// Let the engine perform required state transitions
		m_GraphicsContext->GetImmediateContext()->ClearRenderTarget(pRTV, ClearColor, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
		if (!t_IsUsingRenderTarget)
		{
			m_GraphicsContext->GetImmediateContext()->ClearDepthStencil(pDSV, Diligent::CLEAR_DEPTH_FLAG, 1.f, 0, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
		}
	}

	void RendererAPI::SetSwapChainRenderTargets()
	{
		auto* pRTV = m_GraphicsContext->GetSwapChain()->GetCurrentBackBufferRTV();
		auto* pDSV = m_GraphicsContext->GetSwapChain()->GetDepthBufferDSV();
		m_GraphicsContext->GetImmediateContext()->SetRenderTargets(1, &pRTV, pDSV, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
	}

	void RendererAPI::Present() const
	{
		m_GraphicsContext->GetSwapChain()->Present();
	}

	void RendererAPI::DrawVertices(uint32_t t_Count)
	{
		Diligent::DrawAttribs drawAttrs;
		drawAttrs.NumVertices = t_Count;
		// Verify the state of vertex and index buffers
		drawAttrs.Flags = Diligent::DRAW_FLAG_VERIFY_ALL;
		m_GraphicsContext->GetImmediateContext()->Draw(drawAttrs);
	}

	void RendererAPI::DrawIndexed(uint32_t t_Count)
	{
		Diligent::DrawIndexedAttribs DrawAttrs;	  // This is an indexed draw call
		DrawAttrs.IndexType = Diligent::VT_UINT32;	 // Index type
		DrawAttrs.NumIndices = t_Count;
		// Verify the state of vertex and index buffers
		DrawAttrs.Flags = Diligent::DRAW_FLAG_VERIFY_ALL;
		m_GraphicsContext->GetImmediateContext()->DrawIndexed(DrawAttrs);
	}
}	// namespace Potato
