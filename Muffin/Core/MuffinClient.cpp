#include "MuffinClient.hpp"

namespace Muffin
{
	void MuffinClient::OnUpdate(Potato::Timestep t_Timestep)
	{
		this->time += t_Timestep;
		this->frames += 1;
		if (this->time >= 1.0f)
		{
			//POTATO_TRACE("FPS: {}", this->frames);
			this->time = 0.0f;
			this->frames = 0;
		}

		m_World.OnUpdate(t_Timestep);
		m_CameraController.OnUpdate(t_Timestep);
	}

	void MuffinClient::OnRender()
	{
		m_World.OnRender(m_CameraController.GetCamera());
	}

	void MuffinClient::OnEvent(Potato::Event& event)
	{
		if (event.GetEventType() == Potato::EventType::KeyReleased)
		{
			if ((uint16_t) static_cast<Potato::KeyReleasedEvent&>(event).GetKeyCode() == (uint16_t) POTATO_KEY_ESCAPE)
			{
				m_CameraActive = !m_CameraActive;
				m_CameraController.SetActive(m_CameraActive);
			}
		}

		m_World.OnEvent(event);
		m_CameraController.OnEvent(event);
	}
}	// namespace Muffin
