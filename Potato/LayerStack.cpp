#include "LayerStack.hpp"

namespace Potato
{
	LayerStack::LayerStack()
	{
		m_LayerInsert = m_Layers.begin();
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
		{
			layer->OnDetach();
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		int layerInsertIndex = m_LayerInsert - m_Layers.begin();
		m_Layers.emplace_back(overlay);
		m_LayerInsert = m_Layers.begin() + layerInsertIndex;
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			int layerInsertIndex = m_LayerInsert - m_Layers.begin();
			layerInsertIndex = layerInsertIndex >= it - m_Layers.begin() ? layerInsertIndex - 1 : layerInsertIndex;
			m_Layers.erase(it);
			layer->OnDetach();
			m_LayerInsert = m_Layers.begin() + layerInsertIndex;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end())
		{
			int layerInsertIndex = m_LayerInsert - m_Layers.begin();
			m_Layers.erase(it);
			overlay->OnDetach();
			m_LayerInsert = m_Layers.begin() + layerInsertIndex;
		}
	}
}	// namespace Potato
