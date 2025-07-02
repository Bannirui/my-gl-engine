//
// Created by rui ding on 2025/7/2.
//

#pragma once

#include <vector>

#include "Hazel/Layer.h"

namespace Hazel
{
    class LayerStack {
        public:
            LayerStack();
            ~LayerStack();

            void PushLayer(Layer* layer);
            void PushOverlay(Layer* layer);
            void PopLayer(Layer* layer);
            void PopOverlay(Layer* layer);

            std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
            std::vector<Layer*>::iterator end() { return m_Layers.end(); }
        private:
            std::vector<Layer*> m_Layers;
            std::vector<Layer*>::iterator m_LayerIterator;
    };
}
