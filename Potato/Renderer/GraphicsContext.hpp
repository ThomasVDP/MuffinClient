#ifndef POTATO_ENGINE_GRAPHICS_CONTEXT_HPP
#define POTATO_ENGINE_GRAPHICS_CONTEXT_HPP

#include "Potato/Core.hpp"

//Diligent Engine
#include "Common/interface/RefCntAutoPtr.hpp"
#include "Graphics/GraphicsEngine/interface/RenderDevice.h"
#include "Graphics/GraphicsEngine/interface/DeviceContext.h"
#include "Graphics/GraphicsEngine/interface/SwapChain.h"

namespace Potato
{
	struct WindowProps;

	class GraphicsContext
	{
	public:
		enum class API
		{
			None = 0,
			Vulkan = 1
		};

		virtual ~GraphicsContext() {}

		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

		virtual void OnWindowResize(unsigned int t_Wdith, unsigned int t_Height) = 0;

		virtual Diligent::RefCntAutoPtr<Diligent::IRenderDevice> GetRenderDevice() const noexcept = 0;
		virtual Diligent::RefCntAutoPtr<Diligent::IDeviceContext> GetImmediateContext() const noexcept = 0;
		virtual Diligent::RefCntAutoPtr<Diligent::ISwapChain> GetSwapChain() const noexcept = 0;

		virtual void ShutDown() = 0;

		static Scope<GraphicsContext> Create(void* window, API t_api);
		static void SetWindowHints(API t_api);
	};
}	// namespace Potato

#endif