//
// Created by rui ding on 2025/7/9.
//

#include "platform/opengl/OpenGLRendererAPI.h"

#include <GLAD/glad.h>

namespace Hazel
{
    void OpenGLRendererAPI::SetClearColor(const glm::vec4 color)
    {
        glClearColor(color.x, color.y, color.z, color.w);
    }

    void OpenGLRendererAPI::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
    {
        glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT,
                       reinterpret_cast<const void*>(static_cast<uintptr_t>(0)));
    }
}