#ifndef POTATO_CAMERA_HPP
#define POTATO_CAMERA_HPP

#include <glm/glm.hpp>

namespace Potato
{
	class Camera
	{
	public:
		virtual const glm::mat4& GetProjectionMatrix() const = 0;
		virtual const glm::mat4& GetViewMatrix() const = 0;
		virtual const glm::mat4& GetViewProjectionMatrix() const = 0;
	};
}	// namespace Potato

#endif