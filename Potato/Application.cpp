#include "Application.hpp"

#include "GLFW/glfw3.h"

#include "Renderer/Renderer.hpp"

namespace Potato
{
	Application* Application::s_Instance = nullptr;

	Application::Application(const std::string& name)
	{
		POTATO_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = Window::Create(WindowProps(name));
		m_Window->SetEventCallback(POTATO_BIND_EVENT_FN(OnEvent, Event));

		Renderer::Init();
	}

	Application::~Application()
	{
		Renderer::Shutdown();
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::Close()
	{
		m_Running = false;
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(POTATO_BIND_EVENT_FN(OnWindowClose, WindowCloseEvent));
		dispatcher.Dispatch<WindowResizeEvent>(POTATO_BIND_EVENT_FN(OnWindowResize, WindowResizeEvent));

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			if (e.IsHandled())
			{
				break;
			}
			(*it)->OnEvent(e);
		}

		//POTATO_CORE_TRACE("{0}", e);
	}

	void Application::Run()
	{
		while (m_Running)
		{
			float time = (float) glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				{
					//HZ_PROFILE_SCOPE("LayerStack OnUpdate");

					for (Layer* layer : m_LayerStack)
						layer->OnUpdate(timestep);
				}
			}

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}
}	// namespace Potato