//
// Created by dingrui on 25-6-22.
//

#pragma once

namespace Hazel
{
    class Application
    {
    public:
        Application();
        virtual ~Application();
        void Run();
    };

    Application* CreateApplication();
}
