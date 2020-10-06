#ifndef POTATO_ENGINE_GLFW_WINDOW_HPP
#define POTATO_ENGINE_GLFW_WINDOW_HPP

#include <functional>

#include "Potato/GraphicsInclude.hpp"
#include "Potato/Renderer/GraphicsContext.hpp"
#include "Potato/Window.hpp"

namespace Potato
{
	class GlfwWindow : public Window
	{
	public:
		GlfwWindow(const WindowProps& props);
		virtual ~GlfwWindow();

		void Present() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		inline const Scope<GraphicsContext>& GetRenderContext() const override { return m_Context; }

		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }

		void* GetNativeWindow() const override { return m_Window; };

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	private:
		GLFWwindow* m_Window;
		Scope<GraphicsContext> m_Context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}	// namespace Potato

#endif