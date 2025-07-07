//
// Created by dingrui on 25-6-22.
//

#pragma once

#include "Hazel/Event/ApplicationEvent.h"

#include "Hazel/Window.h"
#include "Hazel/imgui/ImGuiLayer.h"
#include "Hazel/Layer.h"
#include "Hazel/LayerStack.h"
#include "Hazel/renderer/Shader.h"
#include "Hazel/renderer/Buffer.h"

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

        inline Window& GetWindow() { return *m_Window; }
        inline static Application& Get() { return *s_Instance; }

    private:
        bool OnWindowClose(WindowCloseEvent& e);

        std::unique_ptr<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        bool m_Running = true;
        LayerStack m_LayerStack;

        // VAO VBO EBO
        unsigned int m_VertexArray;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
        std::unique_ptr<Shader> m_Shader;

    private:
        static Application* s_Instance;
    };

    // for entry point
    Application* CreateApplication();
} // namespace Hazel
