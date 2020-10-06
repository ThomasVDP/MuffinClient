#ifndef POTATO_DEFAULT_RENDER_TARGET_OBJECT_HPP
#define POTATO_DEFAULT_RENDER_TARGET_OBJECT_HPP

#include "Potato/Renderer/PipelineState.hpp"
#include "Potato/Renderer/RenderTarget.hpp"
#include "Potato/Events/ApplicationEvent.hpp"

namespace Potato
{
	class DefaultRenderTargetObject
	{
	public:
		DefaultRenderTargetObject(const glm::vec4& t_ClearColor);

		//file paths are provided
		void Init(const std::string& t_VertShader, const std::string& t_PixelShader);

		void Bind();

		void RenderToScreen();

		void OnEvent(Event& e);

	private:
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		PipelineState m_PipelineState;

		RenderTarget m_RenderTarget;
	};
}	// namespace Potato

#endif