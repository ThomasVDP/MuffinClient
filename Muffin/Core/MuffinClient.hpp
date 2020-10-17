#ifndef MUFFIN_CLIENT_HPP
#define MUFFIN_CLIENT_HPP

#include "PotatoEngine.hpp"

#include "Muffin/World/World.hpp"

namespace Muffin
{
	class MuffinClient : public Potato::Layer
	{
	public:
		MuffinClient(float aspectRatio) :
			Layer("MuffinClient Main Layer"), m_CameraController(aspectRatio) {}

		void OnUpdate(Potato::Timestep t_Timestep) override;

		void OnRender() override;

		void OnEvent(Potato::Event& event) override;

	private:
		World m_World;

		//fps counter
		uint32_t frames{ 0 };
		float time{ 0.0f };

		bool m_CameraActive{ false };
		Potato::PerspectiveCameraController m_CameraController;
	};
}	// namespace Muffin

#endif