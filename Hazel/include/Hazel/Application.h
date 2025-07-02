//
// Created by dingrui on 25-6-22.
//

#pragma once

#include "Layer.h"
#include "LayerStack.h"
#include "Hazel/Window.h"
#include "Hazel/Events/ApplicationEvent.h"

namespace Hazel
{
    class Application
    {
        public:
            Application();
            virtual ~Application();
            void Run();
            void OnEvent(Event& e);

            void PushLayer(Layer* layer);
            void PushOverlay(Layer* layer);
        private:
            std::unique_ptr<Window> m_Window;
            bool m_Running = true;
            bool OnWindowClose(WindowCloseEvent& e);
            LayerStack m_LayerStack;
    };

    // for entry point
    Application* CreateApplication();
}
