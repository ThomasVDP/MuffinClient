#ifndef POTATO_RENDER_TARGET_HPP
#define POTATO_RENDER_TARGET_HPP

#include <Common/interface/RefCntAutoPtr.hpp>

#include <glm/glm.hpp>

#include "Potato/Events/ApplicationEvent.hpp"
#include "PipelineState.hpp"

namespace Potato
{
	class RenderTarget
	{
	public:
		RenderTarget(const glm::vec4& t_ClearColor);

		//returns the color shader resource;
		Diligent::RefCntAutoPtr<Diligent::ITextureView> CreateRenderTargets();

		Diligent::RefCntAutoPtr<Diligent::ITextureView> GetColorView() const { return m_pColorRTV; }

		Diligent::RefCntAutoPtr<Diligent::ITextureView> GetDepthBuffer() const { return m_pDepthDSV; }

		const glm::vec4& GetOptimalClearColor() const { return m_ClearColor; }

		static constexpr Diligent::TEXTURE_FORMAT RenderTargetFormat = Diligent::TEX_FORMAT_RGBA8_UNORM;
		static constexpr Diligent::TEXTURE_FORMAT DepthBufferFormat = Diligent::TEX_FORMAT_D32_FLOAT;

	private:
		// Offscreen render target and depth-stencil
		Diligent::RefCntAutoPtr<Diligent::ITextureView> m_pColorRTV;
		Diligent::RefCntAutoPtr<Diligent::ITextureView> m_pDepthDSV;

		glm::vec4 m_ClearColor;
	};
}	// namespace Potato

#endif