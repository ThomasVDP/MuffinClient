#include "VulkanContext.hpp"

//#include "VulkanFunctionLoader.hpp"

namespace Potato
{
	VulkanContext::VulkanContext(GLFWwindow* window) :
		m_WindowHandle(window)
	{
		POTATO_CORE_ASSERT(m_WindowHandle, "No window handle!");
	}

	VulkanContext::~VulkanContext()
	{
	}

	void VulkanContext::Init()
	{
		//Initialize Vulkan Engine
		m_pFactoryVk = Diligent::GetEngineFactoryVk();
		//Diligent::RefCntAutoPtr<Diligent::IEngineFactoryVk> pFactoryVk = Diligent::GetEngineFactoryVk();
		Diligent::EngineVkCreateInfo engineVkAttribs;
		engineVkAttribs.EnableValidation = true;
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
		engineVkAttribs.GlobalExtensionCount += glfwExtensionCount;
		engineVkAttribs.ppGlobalExtensionNames = glfwExtensions;

		Diligent::SwapChainDesc SwapChainDesc;
		SwapChainDesc.BufferCount = 3;

		std::vector<Diligent::IDeviceContext*> ppContexts(engineVkAttribs.NumDeferredContexts + 1);
		m_pFactoryVk->CreateDeviceAndContextsVk(engineVkAttribs, &m_pDevice, ppContexts.data());

		if (!m_pDevice)
		{
		}
		Diligent::NativeWindow nw{ m_WindowHandle };   // GLFW Window

		if (!m_pSwapChain)
		{
			m_pFactoryVk->CreateSwapChainVk(m_pDevice, ppContexts[0], SwapChainDesc, nw, &m_pSwapChain);
		}
		m_pImmediateContext = ppContexts[0];
		auto NumDeferredCtx = ppContexts.size() - 1;
		m_pDeferredContexts.resize(NumDeferredCtx);
		for (uint32_t ctx = 0; ctx < NumDeferredCtx; ++ctx)
			m_pDeferredContexts[ctx] = ppContexts[1 + ctx];
	}

	void VulkanContext::SwapBuffers()
	{
		this->m_pSwapChain->Present();
	}

	void VulkanContext::OnWindowResize(unsigned int t_Width, unsigned int t_Height)
	{
		this->m_pSwapChain->Resize(t_Width, t_Height);
	}

	void VulkanContext::ShutDown() noexcept
	{
		POTATO_CORE_INFO("Terminated VulkanContext!");
	}

	/*std::vector<char> VulkanContext::ReadFile(const std::string& filename)
	{
		std::ifstream file(filename, std::ios::ate | std::ios::binary);

		if (!file.is_open())
		{
			throw std::runtime_error("failed to open file!");
		}

		size_t fileSize = (size_t) file.tellg();
		std::vector<char> buffer(fileSize);
		file.seekg(0);
		file.read(buffer.data(), fileSize);

		file.close();

		return buffer;
	}*/
}	// namespace Potato