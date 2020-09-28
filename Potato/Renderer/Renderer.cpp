#include "Renderer.hpp"

#include "RenderCommand.hpp"
#include "BasicRenderer.hpp"

namespace Potato
{
	void Renderer::Init()
	{
		RenderCommand::Init();
		BasicRenderer::Init();
	}

	void Renderer::Shutdown()
	{
	}

	void Renderer::OnWindowResize(unsigned int t_Width, unsigned int t_Height)
	{
		RenderCommand::OnWindowResize(t_Width, t_Height);
	}
}	// namespace Potato
