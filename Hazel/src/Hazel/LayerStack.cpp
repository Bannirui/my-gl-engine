//
// Created by rui ding on 2025/7/2.
//

#include "Hazel/LayerStack.h"

namespace Hazel
{
LayerStack::LayerStack() { m_LayerIterator = m_Layers.begin(); }

LayerStack::~LayerStack() {
    for (Layer* layer : m_Layers) delete layer;
}

void LayerStack::PushLayer(Layer* layer) {
    m_Layers.emplace(m_Layers.begin() + m_LayerIteratorIndex, layer);
    m_LayerIteratorIndex++;
    layer->OnAttach();
}

void LayerStack::PushOverlay(Layer *layer) {
    m_Layers.emplace_back(layer);
    layer->OnAttach();
}

void LayerStack::PopLayer(Layer *layer) {
    auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
    if (it != m_Layers.end()) {
        m_Layers.erase(it);
        m_LayerIteratorIndex--;
        layer->OnDetach();
    }
}

void LayerStack::PopOverlay(Layer* overlay) {
    auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
    if (it != m_Layers.end()) {
        m_Layers.erase(it);
        overlay->OnDetach();
    }
}
}