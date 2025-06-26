//
// Created by dingrui on 25-6-22.
//

#include "hzpch.h"

#include "Hazel/Application.h"

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

namespace Hazel
{
    Application::Application() {
        m_Window = std::unique_ptr<Window>(Window::Create());
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        while (m_Running) {
            glClearColor(0.3f, 0.5f, 1.0f, 0.7f);
            glClear(GL_COLOR_BUFFER_BIT);
            m_Window->OnUpdate();
        }
    }
}
