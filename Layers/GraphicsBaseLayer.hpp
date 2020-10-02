#ifndef MUFFIN_CLIENT_GRAPHICS_BASE_LAYER_HPP
#define MUFFIN_CLIENT_GRAPHICS_BASE_LAYER_HPP

#include "PotatoEngine.hpp"

namespace Muffin
{
	class GraphicsBaseLayer : public Potato::Layer
	{
	public:
		GraphicsBaseLayer();

		void OnAttach() override;

		void OnDetach() override;

		void OnUpdate(Potato::Timestep t_Timestep) override;

		void OnRender() override;

		void OnEvent(Potato::Event& event) override;

	private:
		float timePassed{ 0.0f };
		uint32_t framesRendered{ 0 };

		Potato::PerspectiveCameraController m_CameraController;
	};
}	// namespace Muffin

#endif