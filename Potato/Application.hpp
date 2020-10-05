#ifndef POTATO_ENGINE_APPLICATION_HPP
#define POTATO_ENGINE_APPLICATION_HPP

#include "Core.hpp"
#include "TimeStep.hpp"
#include "Events/ApplicationEvent.hpp"
#include "Events/Event.hpp"
#include "Events/KeyEvent.hpp"
#include "LayerStack.hpp"
#include "Window.hpp"
#include "Potato/Renderer/GraphicsContext.hpp"
#include "Potato/Renderer/RenderTarget.hpp"

namespace Potato
{
	class Application
	{
	public:
		Application(const std::string& name = "Potato App");
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		void Close();

		inline const Scope<Window>& GetWindow() const { return m_Window; }

		static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		bool OnWindowResize(WindowResizeEvent& e);

		Scope<Window> m_Window;
		bool m_Running = true;
		bool m_Minimized = false;
		float m_LastFrameTime = 0.0f;

		LayerStack m_LayerStack;

	private:
		static Application* s_Instance;

	private:
		RenderTarget m_RenderTarget;
	};

	Application* CreateApplication();
}	// namespace Potato

#endif