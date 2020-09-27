#include "GraphicsContext.hpp"

#include "Potato/Vulkan/VulkanContext.hpp"
#include "Potato/Window.hpp"

namespace Potato
{
	Scope<GraphicsContext> GraphicsContext::Create(void* window, GraphicsContext::API t_api)
	{
		switch (t_api)
		{
		case GraphicsContext::API::None: POTATO_CORE_ASSERT(false, "GraphicsContext::None is currently not supported!"); return nullptr;
		case GraphicsContext::API::Vulkan:
			Scope<GraphicsContext> context = CreateScope<VulkanContext>(static_cast<GLFWwindow*>(window));
			return context;
		}

		POTATO_CORE_ASSERT(false, "Unknown GraphicsContext!");
		return nullptr;
	}

	void GraphicsContext::SetWindowHints(GraphicsContext::API t_api)
	{
		switch (t_api)
		{
		case GraphicsContext::API::None:
			POTATO_CORE_ASSERT(false, "GraphicsContext::None is currently not supported!");
			return;
		case GraphicsContext::API::Vulkan:
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			return;
		}

		POTATO_CORE_ASSERT(false, "Unknown GraphicsContext!");
	}
}	// namespace Potato