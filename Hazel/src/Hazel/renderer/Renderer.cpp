//
// Created by rui ding on 2025/7/7.
//

#include "Hazel/renderer/Renderer.h"
#include "Hazel/renderer/RendererCommand.h"
#include "platform/opengl/OpenGLShader.h"

namespace Hazel
{
    Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<Renderer::SceneData>();

    void Renderer::Init()
    {
        RendererCommand::Init();
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height)
    {
        RendererCommand::SetViewport(0, 0, width, height);
    }

    void Renderer::BeginScene(OrthographicCamera& camera)
    {
        s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray,
                          const glm::mat4&               transform)
    {
        shader->Bind();
        auto open_gl_shader = std::dynamic_pointer_cast<OpenGLShader>(shader);
        open_gl_shader->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
        open_gl_shader->UploadUniformMat4("u_Transform", transform);

        vertexArray->Bind();
        RendererCommand::DrawIndexed(vertexArray);
    }
}