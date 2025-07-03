//
// Created by rui ding on 2025/7/2.
//

#pragma once

#include <Hazel/Layer.h>

namespace Hazel
{
    class ImGuiLayer : public Hazel::Layer
    {
        public:
            ImGuiLayer();
            ~ImGuiLayer();

            virtual void OnAttach();
            virtual void OnDetach();
            virtual void OnUpdate();
            virtual void OnEvent(Event& e);

        private:
            float m_Time = 0.0f;
    };
}
