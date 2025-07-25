//
// Created by dingrui on 25-6-22.
//

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

#include "Hazel.h"
#include "platform/opengl/OpenGLShader.h"
#include "Hazel/EntryPoint.h"
#include "Sandbox2D.h"

class ExampleLayer : public Hazel::Layer
{
public:
    ExampleLayer() : Layer("Example Layer"), m_CameraController(1280.0f / 720.0f)
    {
        m_VertexArray = Hazel::VertexArray::Create();

        float vertices[3 * 7] = {-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f, 0.5f, -0.5f, 0.0f, 0.2f,
                                 0.3f,  0.8f,  1.0f, 0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f,  1.0f};
        Hazel::Ref<Hazel::VertexBuffer> vertexBuffer;
        vertexBuffer.reset(Hazel::VertexBuffer::Create(vertices, sizeof(vertices)));
        Hazel::BufferLayout layout = {{Hazel::ShaderDataType::Float3, "a_Position"},
                                      {Hazel::ShaderDataType::Float4, "a_Color"}};
        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        uint32_t                       indices[3] = {0, 1, 2};
        Hazel::Ref<Hazel::IndexBuffer> indexBuffer;
        indexBuffer.reset(Hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        m_SquareVA                  = Hazel::VertexArray::Create();
        float squareVertices[5 * 4] = {// xyz              // uv
                                       -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.0f,
                                       0.5f,  0.5f,  0.0f, 1.0f, 1.0f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f};

        Hazel::Ref<Hazel::VertexBuffer> squareVB;
        squareVB.reset(Hazel::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
        squareVB->SetLayout({
            {Hazel::ShaderDataType::Float3, "a_Position"},
            {Hazel::ShaderDataType::Float2, "a_TexCoord"},
        });
        m_SquareVA->AddVertexBuffer(squareVB);

        uint32_t                       squareIndices[6] = {0, 1, 2, 2, 3, 0};
        Hazel::Ref<Hazel::IndexBuffer> squareIB;
        squareIB.reset(Hazel::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
        m_SquareVA->SetIndexBuffer(squareIB);

        m_Shader           = Hazel::Shader::Create("asset/shader/triangle_3_3.glsl");
        m_FlatColorShader  = Hazel::Shader::Create("asset/shader/rectangle_3_3.glsl");
        auto textureShader = m_ShaderLibrary.Load("asset/shader/texture_3_3.glsl");

        m_Texture  = Hazel::Texture2D::Create("asset/texture/Checkerboard.png");
        m_Texture2 = Hazel::Texture2D::Create("asset/texture/cppLogo.png");

        std::dynamic_pointer_cast<Hazel::OpenGLShader>(textureShader)->Bind();
        std::dynamic_pointer_cast<Hazel::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
    }

    void OnUpdate(Hazel::Timestep ts) override
    {
        m_CameraController.OnUpdate(ts);
        Hazel::RendererCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
        Hazel::RendererCommand::Clear();

        Hazel::Renderer::BeginScene(m_CameraController.GetCamera());

        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

        std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_FlatColorShader)->Bind();
        std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_FlatColorShader)
            ->UploadUniformFloat3("u_Color", m_SquareColor);

        for (int y = 0; y < 20; y++)
        {
            for (int x = 0; x < 20; x++)
            {
                glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
                Hazel::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
            }
        }

        m_Texture->Bind();
        auto textureShader = m_ShaderLibrary.Get("texture_3_3");
        Hazel::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
        m_Texture2->Bind();
        Hazel::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
        // 三角形
        Hazel::Renderer::Submit(m_Shader, m_VertexArray);

        Hazel::Renderer::EndScene();
    }

    void OnEvent(Hazel::Event& e) override { m_CameraController.OnEvent(e); }

    virtual void OnImGuiRender() override
    {
        ImGui::Begin("Settings");
        ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
        ImGui::End();
    }

private:
    Hazel::ShaderLibrary           m_ShaderLibrary;
    Hazel::Ref<Hazel::Shader>      m_Shader;
    Hazel::Ref<Hazel::VertexArray> m_VertexArray;

    Hazel::Ref<Hazel::Shader>           m_FlatColorShader;
    Hazel::Ref<Hazel::VertexArray>      m_SquareVA;
    Hazel::Ref<Hazel::Texture2D>        m_Texture, m_Texture2;
    Hazel::OrthographicCameraController m_CameraController;
    glm::vec3                           m_SquareColor = {0.2f, 0.3f, 0.8f};
};

class Sandbox : public Hazel::Application
{
public:
    Sandbox() { PushLayer(new Sandbox2D()); }

    ~Sandbox() {}
};

Hazel::Application* Hazel::CreateApplication()
{
    return new Sandbox();
}