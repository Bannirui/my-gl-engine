//
// Created by dingrui on 25-6-22.
//

#include "Hazel/Application.h"

#include <GLAD/glad.h>

#include "Hazel/Core/Assert.h"
#include "Hazel/Log.h"
#include "Hazel/imgui/ImGuiLayer.h"
#include "hzpch.h"

namespace Hazel
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application* Application::s_Instance = nullptr;

    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
            case Hazel::ShaderDataType::Float:
                return GL_FLOAT;
            case Hazel::ShaderDataType::Float2:
                return GL_FLOAT;
            case Hazel::ShaderDataType::Float3:
                return GL_FLOAT;
            case Hazel::ShaderDataType::Float4:
                return GL_FLOAT;
            case Hazel::ShaderDataType::Mat3:
                return GL_FLOAT;
            case Hazel::ShaderDataType::Mat4:
                return GL_FLOAT;
            case Hazel::ShaderDataType::Int:
                return GL_INT;
            case Hazel::ShaderDataType::Int2:
                return GL_INT;
            case Hazel::ShaderDataType::Int3:
                return GL_INT;
            case Hazel::ShaderDataType::Int4:
                return GL_INT;
            case Hazel::ShaderDataType::Bool:
                return GL_BOOL;
            default:
            {
                HZ_CORE_ASSERT(false, "Unknown ShaderDataType!");
                return 0;
            }
        }
    }

    Application::Application()
    {
        HZ_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;
        m_Window   = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);

        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
            0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
            0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
        };
        m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
        {
            BufferLayout layout = {
                {ShaderDataType::Float3, "a_Position"},
                {ShaderDataType::Float4, "a_Color"}
            };
            m_VertexBuffer->SetLayout(layout);
        }

        const auto& layout = m_VertexBuffer->GetLayout();
        // VAO
        glGenVertexArrays(1, &m_VertexArray);
        glBindVertexArray(m_VertexArray);
        // VAO属性
        uint32_t index = 0;
        for (const auto& element : layout)
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index,
                                  element.GetComponentCount(),
                                  ShaderDataTypeToOpenGLBaseType(element.Type),
                                  element.Normalized ? GL_TRUE : GL_FALSE,
                                  layout.GetStride(),
                                  reinterpret_cast<const void*>(static_cast<uintptr_t>(element.Offset)));
            index++;
        }

        unsigned int indices[3] = {0, 1, 2};
        m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));

        std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

        std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";
        m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
    }

    void Application::Run()
    {
        // 告诉GL状态机清屏的时候清成啥样
        glClearColor(1.0f, 0.5f, 1.0f, 0.7f);
        while (m_Running)
        {
            // 每帧都要清屏
            glClear(GL_COLOR_BUFFER_BIT);

            m_Shader->Bind();
            glBindVertexArray(m_VertexArray);
            glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

            for (Layer* layer : m_LayerStack) layer->OnUpdate();

            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack) layer->OnImGuiRender();
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
        {
            (*--it)->OnEvent(e);
            if (e.Handled) return;
        }
    }

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer* layer)
    {
        m_LayerStack.PushOverlay(layer);
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }
}