#ifndef POTATO_QUAD_RENDERER_HPP
#define POTATO_QUAD_RENDERER_HPP

#include <Potato/Camera/Camera.hpp>

namespace Potato
{
	class QuadRenderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const Camera& t_Camera);

		//rotation in degrees
		static void DrawQuad(const glm::vec3& t_Position, const glm::vec3& t_Rotation = { 0.0f, 0.0f, 0.0f });
	};
}	// namespace Potato

#endif