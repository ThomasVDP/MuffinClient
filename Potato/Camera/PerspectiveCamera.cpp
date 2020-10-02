#include "PerspectiveCamera.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Potato
{
	PerspectiveCamera::PerspectiveCamera(float FOV, float aspectRatio, float near, float far) :
		m_ProjectionMatrix(glm::perspective(FOV, aspectRatio, near, far)), m_ViewMatrix(1.0f)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void PerspectiveCamera::SetProjection(float FOV, float aspectRatio, float near, float far)
	{
		m_ProjectionMatrix = glm::perspective(FOV, aspectRatio, near, far);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void PerspectiveCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position);

		glm::quat quatX = glm::angleAxis<float, glm::defaultp>(m_Rotation.x, { 1.0f, 0.0f, 0.0f });
		glm::quat quatY = glm::angleAxis<float, glm::defaultp>(m_Rotation.y, { 0.0f, 1.0f, 0.0f });
		glm::quat quatZ = glm::angleAxis<float, glm::defaultp>(m_Rotation.z, { 0.0f, 0.0f, 1.0f });
		glm::quat finalQuat = quatY * quatX * quatZ;

		transform *= glm::toMat4(finalQuat);
		//glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}	// namespace Potato
