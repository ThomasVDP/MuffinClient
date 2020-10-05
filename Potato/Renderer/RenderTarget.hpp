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
		RenderTarget(const std::string& t_PipelineName, float t_AspectRatio);

		void Create();

		void Bind(const glm::vec4& t_Color);

		void RenderToScreen();

		void OnEvent(Event& e);

		bool OnWindowResize(WindowResizeEvent& e);

		void CreateRenderTargets();

		static constexpr Diligent::TEXTURE_FORMAT RenderTargetFormat = Diligent::TEX_FORMAT_RGBA8_UNORM;
		static constexpr Diligent::TEXTURE_FORMAT DepthBufferFormat = Diligent::TEX_FORMAT_D32_FLOAT;

	private:
		Potato::PipelineState m_PipelineState;

		// Offscreen render target and depth-stencil
		Diligent::RefCntAutoPtr<Diligent::ITextureView> m_pColorRTV;
		Diligent::RefCntAutoPtr<Diligent::ITextureView> m_pDepthDSV;

		float m_AspectRatio;
	};
}	// namespace Potato

#endif