#include "Layers/GraphicsBaseLayer.hpp"

// ---Entry Point---------------------
#include "Potato/EntryPoint.hpp"
// -----------------------------------

class MainApp : public Potato::Application
{
public:
	MainApp()
	{
		PushLayer(new Muffin::GraphicsBaseLayer());
		//PushLayer(new BaseLayer());
	}

	~MainApp()
	{
	}
};

Potato::Application* Potato::CreateApplication()
{
	return new MainApp();
}