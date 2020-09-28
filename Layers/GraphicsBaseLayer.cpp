#include "GraphicsBaseLayer.hpp"

namespace Muffin
{
	GraphicsBaseLayer::GraphicsBaseLayer() :
		Layer("BaseLayer")
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
	}

	void GraphicsBaseLayer::OnRender()
	{
		//render triangle
	}

	void GraphicsBaseLayer::OnEvent(Potato::Event& event)
	{
	}
}	// namespace Muffin
