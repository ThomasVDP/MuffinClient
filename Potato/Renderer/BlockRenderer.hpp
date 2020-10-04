#ifndef POTATO_BLOCK_RENDERER_HPP
#define POTATO_BLOCK_RENDERER_HPP

#include <glm/glm.hpp>

#include "Potato/Camera/Camera.hpp"

namespace Potato
{
	class BlockRenderer
	{
	public:
		BlockRenderer();
		~BlockRenderer();

		void Init();
		void Shutdown();

		void BeginScene(const Camera& t_Camera);

		void RenderFullBlock(const glm::vec3& position);
	};
}	// namespace Potato

#endif