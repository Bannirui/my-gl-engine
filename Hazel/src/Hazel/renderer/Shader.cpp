//
// Created by rui ding on 2025/7/7.
//

#include "Hazel/renderer/Shader.h"

#include "Hazel/Core/Assert.h"
#include "Hazel/renderer/Renderer.h"
#include "platform/opengl/OpenGLShader.h"

namespace Hazel
{
    Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:
            {
                HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            }
            case RendererAPI::API::OpenGL:
                return new OpenGLShader(vertexSrc, fragmentSrc);
        }
        HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}