#ifndef POTATO_QUAD_RENDERER_HPP
#define POTATO_QUAD_RENDERER_HPP

#include <Potato/Camera/Camera.hpp>

namespace Potato
{
	class QuadRenderer
	{
	public:
		static void Init();

		static void BeginScene(const Camera& t_Camera);

		static void DrawQuad();
	};
}	// namespace Potato

#endif