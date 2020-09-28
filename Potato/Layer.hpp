#ifndef POTATO_ENGINE_LAYER_HPP
#define POTATO_ENGINE_LAYER_HPP

#include "Potato/Core.hpp"
#include "Potato/Events/Event.hpp"
#include "TimeStep.hpp"

namespace Potato
{
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep t_Timestep) {}
		virtual void OnRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() { return m_DebugName; }

	private:
		std::string m_DebugName;
	};
}	// namespace Potato

#endif