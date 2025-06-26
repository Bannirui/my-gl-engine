//
// Created by dingrui on 25-6-22.
//

#pragma once

#include "Hazel/Window.h"

namespace Hazel
{
    class Application
    {
        public:
            Application();
            virtual ~Application();
            void Run();
        private:
            std::unique_ptr<Window> m_Window;
            bool m_Running = true;
    };

    // for entry point
    Application* CreateApplication();
}
