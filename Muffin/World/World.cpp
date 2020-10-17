#include "World.hpp"

namespace Muffin
{
	World::World() :
		m_Skybox("assets/textures/skybox/night.png")
	{
	}

	void World::OnRender(const Potato::Camera& t_Camera)
	{
		//first render skybox
		m_Skybox.OnRender(t_Camera);

		//render rest of scene
		m_BlockRenderer.BeginScene(t_Camera);
		m_BlockRenderer.RenderFullBlock({ 0.0f, 0.0f, 0.0f });
	}

	void World::OnUpdate(Potato::Timestep t_Timestep)
	{
	}

	void World::OnEvent(Potato::Event& event)
	{
	}
}	// namespace Muffin
