#ifndef POTATO_RENDERER_API_HPP
#define POTATO_RENDERER_API_HPP

#include "Potato/Application.hpp"
#include "GraphicsContext.hpp"

#include <glm/glm.hpp>

namespace Potato
{
	class RendererAPI
	{
	public:
		RendererAPI(const Scope<GraphicsContext>& t_GraphicsContext);

		void OnWindowResize(uint32_t t_Width, uint32_t t_Height);

		void Clear(const glm::vec4& color);

		void DrawVertices(uint32_t count);

		void DrawIndexed(uint32_t count);

		void Present() const;

	private:
		const Scope<GraphicsContext>& m_GraphicsContext;
	};
}	// namespace Potato

#endif