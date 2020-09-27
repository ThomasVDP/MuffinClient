#ifndef POTATO_ENGINE_WINDOW_HPP
#define POTATO_ENGINE_WINDOW_HPP

#include "Potato/Core.hpp"
#include "Potato/Events/Event.hpp"
#include "Potato/Renderer/GraphicsContext.hpp"

namespace Potato
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;
		GraphicsContext::API ChosenAPI;

		WindowProps(const std::string& title = "Potato Engine",
					unsigned int width = 1280,
					unsigned int height = 720,
					GraphicsContext::API t_api = GraphicsContext::API::Vulkan) :
			Title(title),
			Width(width), Height(height),
			ChosenAPI(t_api)
		{
		}
	};

	// Interface representing a desktop system based Window
	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual const Scope<GraphicsContext>& GetRenderContext() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Scope<Window> Create(const WindowProps& props = WindowProps());
	};
}	// namespace Potato

#endif