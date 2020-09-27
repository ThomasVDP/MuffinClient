#ifndef POTATO_RENDERER_HPP
#define POTATO_RENDERER_HPP

namespace Potato
{
	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void OnWindowResize(unsigned int t_Width, unsigned int t_Height);
	};
}	// namespace Potato

#endif