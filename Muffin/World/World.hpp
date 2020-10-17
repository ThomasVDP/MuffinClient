#ifndef MUFFIN_WORLD_HPP
#define MUFFIN_WORLD_HPP

#include "PotatoEngine.hpp"

#include "Muffin/Graphics/Skybox/Skybox.hpp"

namespace Muffin
{
	class World
	{
	public:
		World();

		void OnUpdate(Potato::Timestep t_Timestep);

		void OnRender(const Potato::Camera& t_Camera);

		void OnEvent(Potato::Event& event);

	private:
		Skybox m_Skybox;

		Potato::BlockRenderer m_BlockRenderer;
	};
}	// namespace Muffin

#endif