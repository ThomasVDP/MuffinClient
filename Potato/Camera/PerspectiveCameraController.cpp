#include "PerspectiveCameraController.hpp"

#include "Potato/Core/Input.hpp"
#include "Potato/Core/KeyCodes.hpp"

namespace Potato
{
	PerspectiveCameraController::PerspectiveCameraController(float aspectRatio) :
		m_AspectRatio(aspectRatio), m_Fov(90), m_Camera(m_Fov, m_AspectRatio, 0.01f, 100.0f)
	{
		m_CameraPosition = { 0.0f, 0.0f, 5.0f };
		m_Camera.SetPosition(m_CameraPosition);

		/*m_CameraRotation = { 0.0f, 45.0f, 0.0f };
		m_Camera.SetRotation(m_CameraRotation);*/
	}

	void PerspectiveCameraController::OnUpdate(Timestep ts)
	{
		if (Input::IsKeyPressed(POTATO_KEY_A))
		{
			//m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			//m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			//POTATO_TRACE("Rotation: {}", m_CameraRotation.y);
			m_CameraPosition.x -= cos(m_CameraRotation.y) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.z += sin(m_CameraRotation.y) * m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(POTATO_KEY_D))
		{
			// m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			// m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.x += cos(m_CameraRotation.y) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.z -= sin(m_CameraRotation.y) * m_CameraTranslationSpeed * ts;
		}

		if (Input::IsKeyPressed(POTATO_KEY_W))
		{
			// m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			// m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.x -= cos(glm::radians(90.0f) - m_CameraRotation.y) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.z -= sin(glm::radians(90.0f) - m_CameraRotation.y) * m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(POTATO_KEY_S))
		{
			// m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			// m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.x += cos(glm::radians(90.0f) - m_CameraRotation.y) * m_CameraTranslationSpeed * ts;
			m_CameraPosition.z += sin(glm::radians(90.0f) - m_CameraRotation.y) * m_CameraTranslationSpeed * ts;
		}

		if (Input::IsKeyPressed(POTATO_KEY_SPACE))
		{
			m_CameraPosition.y += m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(POTATO_KEY_LEFT_SHIFT))
		{
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts;
		}

		/*if (m_Rotation)
		{
			if (Input::IsKeyPressed(POTATO_KEY_Q))
				m_CameraRotation += m_CameraRotationSpeed * ts;
			if (Input::IsKeyPressed(POTATO_KEY_E))
				m_CameraRotation -= m_CameraRotationSpeed * ts;

			if (m_CameraRotation > 180.0f)
				m_CameraRotation -= 360.0f;
			else if (m_CameraRotation <= -180.0f)
				m_CameraRotation += 360.0f;

			m_Camera.SetRotation(m_CameraRotation);
		}*/

		m_Camera.SetPosition(m_CameraPosition);
	}

	void PerspectiveCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowResizeEvent>(POTATO_BIND_EVENT_FN(PerspectiveCameraController::OnWindowResized));
		dispatcher.Dispatch<MouseMovedEvent>(POTATO_BIND_EVENT_FN(PerspectiveCameraController::OnMouseMoved));
	}

	void PerspectiveCameraController::OnResize(float width, float height)
	{
		m_AspectRatio = width / height;
		m_Camera.SetProjection(m_Fov, m_AspectRatio, 0.01f, 100.0f);
	}

	bool PerspectiveCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		OnResize((float) e.GetWidth(), (float) e.GetHeight());
		return false;
	}

	bool PerspectiveCameraController::OnMouseMoved(MouseMovedEvent& e)
	{
		if (lastX == 0 && lastY == 0)
		{
			lastX = e.GetX();
			lastY = e.GetY();
			return false;
		}

		float deltaX = lastX - e.GetX();
		lastX = e.GetX();
		float deltaY = lastY - e.GetY();
		lastY = e.GetY();
		m_CameraRotation.x += deltaY * m_CameraRotationSpeed;
		m_CameraRotation.y += deltaX * m_CameraRotationSpeed;

		if (m_CameraRotation.x > glm::radians(180.0f))
			m_CameraRotation.x -= glm::radians(360.0f);
		else if (m_CameraRotation.y <= glm::radians(-180.0f))
			m_CameraRotation.y += glm::radians(360.0f);

		m_Camera.SetRotation(m_CameraRotation);

		return false;
	}
}	// namespace Potato
