#ifndef POTATO_ENGINE_ENTRYPOINT_HPP
#define POTATO_ENGINE_ENTRYPOINT_HPP

#include "Application.hpp"

extern Potato::Application* Potato::CreateApplication();

int main(int argc, char** argv)
{
	Potato::Log::Init();
	POTATO_CORE_INFO("Initialized Log!");

	POTATO_CORE_INFO("Launching Application!");
	auto app = Potato::CreateApplication();
	app->Run();
	delete app;

	return 0;
}

#endif