#include "Renderer.hpp"

#include "RenderCommand.hpp"
#include "QuadRenderer.hpp"

namespace Potato
{
	void Renderer::Init()
	{
		RenderCommand::Init();
		QuadRenderer::Init();
	}

	void Renderer::Shutdown()
	{
		QuadRenderer::Shutdown();
	}

	void Renderer::OnWindowResize(unsigned int t_Width, unsigned int t_Height)
	{
		RenderCommand::OnWindowResize(t_Width, t_Height);
	}
}	// namespace Potato
