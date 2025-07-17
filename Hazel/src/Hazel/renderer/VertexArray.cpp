//
// Created by rui ding on 2025/7/8.
//

#include "Hazel/renderer/VertexArray.h"
#include "Hazel/renderer/Renderer.h"
#include "platform/opengl/OpenGLVertexArray.h"
#include "Hazel/renderer/RendererAPI.h"

namespace Hazel
{
    Ref<VertexArray> VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:
                HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return CreateRef<OpenGLVertexArray>();
        }
        HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}  // namespace Hazel