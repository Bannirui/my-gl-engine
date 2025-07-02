//
// Created by dingrui on 25-6-22.
//

#include "hzpch.h"

#include "Hazel/Application.h"

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

namespace Hazel
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application::Application() {
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        // 告诉GL状态机清屏的时候清成啥样
        glClearColor(1.0f, 0.5f, 1.0f, 0.7f);
        while (m_Running) {
            // 每帧都要清屏
            glClear(GL_COLOR_BUFFER_BIT);
            for (Layer* layer : m_LayerStack) layer->OnUpdate();
            m_Window->OnUpdate();
        }
    }
    void Application::OnEvent(Event &e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
            (*--it)->OnEvent(e);
            if (e.Handled) return;
        }
    }

    void Application::PushLayer(Layer *layer) {
        m_LayerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer *layer) {
        m_LayerStack.PushOverlay(layer);
    }

    bool Application::OnWindowClose(WindowCloseEvent &e) {
        m_Running = false;
        return true;
    }

}
