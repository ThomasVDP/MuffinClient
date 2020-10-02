#ifndef POTATO_PERSPECTIVE_CAMERA_CONTROLLER_HPP
#define POTATO_PERSPECTIVE_CAMERA_CONTROLLER_HPP

#include "PerspectiveCamera.hpp"

#include "Potato/TimeStep.hpp"
#include "Potato/Events/ApplicationEvent.hpp"
#include "Potato/Events/MouseEvent.hpp"

namespace Potato
{
	class PerspectiveCameraController
	{
	public:
		PerspectiveCameraController(float aspectRatio);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		void OnResize(float width, float height);

		void SetActive(bool t_Activeness);

		PerspectiveCamera& GetCamera() { return m_Camera; }
		const PerspectiveCamera& GetCamera() const { return m_Camera; }

		float GetFOV() const { return m_Fov; }
		void SetFOV(float t_Fov) { m_Fov = t_Fov; }

	private:
		bool OnMouseMoved(MouseMovedEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

	private:
		float m_AspectRatio;
		float m_Fov;
		PerspectiveCamera m_Camera;

		glm::vec3 m_CameraPosition{ 0.0f, 0.0f, 0.0f };
		glm::vec3 m_CameraRotation{ 0.0f, 0.0f, 0.0f };	  //In radians, in the anti-clockwise direction
		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 0.003f;

		float m_LastX{ 0.0f }, m_LastY{ 0.0f };
		bool m_Active{ false };
	};
}	// namespace Potato

#endif