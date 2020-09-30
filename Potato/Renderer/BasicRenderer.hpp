#ifndef POTATO_BASIC_RENDERER_HPP
#define POTATO_BASIC_RENDERER_HPP

#include "Potato/Camera/OrthographicCamera.hpp"

namespace Potato
{
	class BasicRenderer
	{
	public:
		static void Init();

		static void BeginScene(const OrthographicCamera& t_Camera);

		static void EndScene();
		static void Flush();

		static void DrawTriangle(const glm::vec2& t_Position);
	};
}	// namespace Potato

#endif
