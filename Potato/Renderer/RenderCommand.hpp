#ifndef POTATO_RENDER_COMMAND_HPP
#define POTATO_RENDER_COMMAND_HPP

#include "Potato/Core.hpp"
#include "RendererAPI.hpp"

namespace Potato
{
	class RenderCommand
	{
	public:
		static void Init()
		{
			s_RendererAPI = CreateScope<RendererAPI>(Application::Get().GetWindow()->GetRenderContext());
		}

		static void OnWindowResize(uint32_t t_Width, uint32_t t_Height)
		{
			s_RendererAPI->OnWindowResize(t_Width, t_Height);
		}

		static void Clear(const glm::vec4& color, bool t_IsUsingRenderTarget = false)
		{
			s_RendererAPI->Clear(color, t_IsUsingRenderTarget);
		}

		static void SetSwapChainRenderTargets()
		{
			s_RendererAPI->SetSwapChainRenderTargets();
		}

		static void Present()
		{
			s_RendererAPI->Present();
		}

		static void DrawVertices(uint32_t count)
		{
			s_RendererAPI->DrawVertices(count);
		}

		static void DrawIndexed(uint32_t count)
		{
			s_RendererAPI->DrawIndexed(count);
		}

	private:
		static Scope<RendererAPI> s_RendererAPI;
	};
}	// namespace Potato

#endif