//
// Created by rui ding on 2025/7/2.
//

#include "Hazel/LayerStack.h"

namespace Hazel
{
    LayerStack::LayerStack() {}

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
        m_Layers.emplace(m_Layers.begin() + m_LayerIteratorIndex, layer);
        m_LayerIteratorIndex++;
        layer->OnAttach();
    }

    void LayerStack::PushOverlay(Layer* layer)
    {
        m_Layers.emplace_back(layer);
        layer->OnAttach();
    }

    void LayerStack::PopLayer(Layer* layer)
    {
        auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerIteratorIndex, layer);
        if (it != m_Layers.begin() + m_LayerIteratorIndex)
        {
            layer->OnDetach();
            m_Layers.erase(it);
            m_LayerIteratorIndex--;
        }
    }

    void LayerStack::PopOverlay(Layer* overlay)
    {
        auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerIteratorIndex, overlay);
        if (it != m_Layers.end())
        {
            overlay->OnDetach();
            m_Layers.erase(it);
        }
    }
}  // namespace Hazel