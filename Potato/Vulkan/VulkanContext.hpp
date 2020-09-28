#ifndef POTATO_ENGINE_VULKAN_CONTEXT_HPP
#define POTATO_ENGINE_VULKAN_CONTEXT_HPP

#include "Potato/Core.hpp"
#include "Potato/Renderer/GraphicsContext.hpp"
#include "Potato/GraphicsInclude.hpp"

#include "Graphics/GraphicsEngineVulkan/interface/EngineFactoryVk.h"
#include "Common/interface/RefCntAutoPtr.hpp"

#include <optional>
#include <vector>

#ifdef POTATO_VULKAN_ENABLE_LAYERS
const bool VulkanEnableValidationLayers = true;
#else
const bool VulkanEnableValidationLayers = false;
#endif

struct GLFWwindow;

namespace Potato
{
	class VulkanContext : public GraphicsContext
	{
	public:
		VulkanContext(GLFWwindow* windowHandle);

		~VulkanContext();

		void Init() override;
		void SwapBuffers() override;

		void OnWindowResize(unsigned int t_Wdith, unsigned int t_Height) override;

		void ShutDown() noexcept override;

		Diligent::RefCntAutoPtr<Diligent::IRenderDevice> GetRenderDevice() const noexcept override { return m_pDevice; }
		Diligent::RefCntAutoPtr<Diligent::IDeviceContext> GetImmediateContext() const noexcept override { return m_pImmediateContext; }
		Diligent::RefCntAutoPtr<Diligent::ISwapChain> GetSwapChain() const noexcept override { return m_pSwapChain; }
		Diligent::IEngineFactory* GetEngineFactory() const noexcept override { return m_pFactoryVk; }

	private:
		GLFWwindow* m_WindowHandle;

		//diligent engine
		Diligent::IEngineFactoryVk* m_pFactoryVk;

		Diligent::RefCntAutoPtr<Diligent::IRenderDevice> m_pDevice;
		Diligent::RefCntAutoPtr<Diligent::IDeviceContext> m_pImmediateContext;
		std::vector<Diligent::RefCntAutoPtr<Diligent::IDeviceContext>> m_pDeferredContexts;
		Diligent::RefCntAutoPtr<Diligent::ISwapChain> m_pSwapChain;
	};
}	// namespace Potato

#endif