//
// Created by rui ding on 2025/7/2.
//

#include "Hazel/Layer.h"

namespace Hazel
{
    Layer::Layer(const std::string& debugName): m_DebugName(debugName) {}

    void Layer::OnAttach() {
    }

    void Layer::OnDetach() {
    }

    void Layer::OnUpdate() {
    }

    void Layer::OnEvent(Event &e) {
    }
}
