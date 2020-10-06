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

	void VulkanContext::Init(bool t_NoDepthBuffer)
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
		if (t_NoDepthBuffer)
		{
			SwapChainDesc.DepthBufferFormat = Diligent::TEX_FORMAT_UNKNOWN;
		}

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

	void VulkanContext::Present()
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
}	// namespace Potato