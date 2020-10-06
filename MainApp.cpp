#include "Layers/GraphicsBaseLayer.hpp"

#include "PotatoEngine.hpp"
#include "Potato/PipelineStates/DefaultRenderTargetObject.hpp"

// ---Entry Point---------------------
#include "Potato/EntryPoint.hpp"
// -----------------------------------

class MainApp : public Potato::Application
{
public:
	MainApp(const std::string& t_WindowTitle) :
		Potato::Application(t_WindowTitle, true),
		m_RenderTarget({ 0.35f, 0.35f, 0.35f, 1.0f })
	{
		m_RenderTarget.Init("assets/shaders/defRenderTarget.vsh", "assets/shaders/defRenderTarget.psh");

		PushLayer(new Muffin::GraphicsBaseLayer());
		//PushLayer(new BaseLayer());
	}

	~MainApp()
	{
	}

	void ClearWindow() override
	{
		m_RenderTarget.Bind();
	}

	void PresentWindow() override
	{
		//clear screen
		Potato::RenderCommand::Clear({ 0.0f, 0.0f, 0.0f, 1.0f }, true);
		m_RenderTarget.RenderToScreen();

		this->GetWindow()->Present();
	}

private:
	Potato::DefaultRenderTargetObject m_RenderTarget;
};

Potato::Application* Potato::CreateApplication()
{
	return new MainApp("Minecraft C++ Replica!");
}