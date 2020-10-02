#ifndef POTATO_PERSPECTIVE_CAMERA_HPP
#define POTATO_PERSPECTIVE_CAMERA_HPP

#include "Camera.hpp"

namespace Potato
{
	class PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera(float FOV, float aspectRatio, float near, float far);

		void SetProjection(float FOV, float aspectRatio, float near, float far);

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position)
		{
			m_Position = position;
			RecalculateViewMatrix();
		}

		const glm::vec3& GetRotation() const { return m_Rotation; }
		void SetRotation(const glm::vec3& rotation)
		{
			m_Rotation = rotation;
			RecalculateViewMatrix();
		}

		const glm::mat4& GetProjectionMatrix() const override { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const override { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const override { return m_ViewProjectionMatrix; }

	private:
		void RecalculateViewMatrix();

	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position{ 0.0f, 0.0f, 0.0f };
		glm::vec3 m_Rotation{ 0.0f, 0.0f, 0.0f };
	};
}	// namespace Potato

#endif