#include "GraphicsBaseLayer.hpp"

namespace Muffin
{
	GraphicsBaseLayer::GraphicsBaseLayer() :
		Layer("BaseLayer"), m_CameraController(1120.0f / 720.0f)
	{
	}

	void GraphicsBaseLayer::OnAttach()
	{
	}

	void GraphicsBaseLayer::OnDetach()
	{
	}

	void GraphicsBaseLayer::OnUpdate(Potato::Timestep t_Timestep)
	{
		//update
		//POTATO_TRACE("Frametime: {}", t_Timestep.GetMilliseconds());
		this->timePassed += t_Timestep.GetMilliseconds();
		this->framesRendered++;
		if (this->timePassed >= 1000)
		{
			//POTATO_TRACE("FPS: {}", this->framesRendered);
			this->timePassed = 0;
			this->framesRendered = 0;
		}
		//POTATO_TRACE("Frame time: {}", t_Timestep.GetMilliseconds());

		m_CameraController.OnUpdate(t_Timestep);
	}

	void GraphicsBaseLayer::OnRender()
	{
		//render triangle
		Potato::QuadRenderer::BeginScene(m_CameraController.GetCamera());
		Potato::QuadRenderer::DrawQuad();
	}

	void GraphicsBaseLayer::OnEvent(Potato::Event& event)
	{
		m_CameraController.OnEvent(event);
	}
}	// namespace Muffin
