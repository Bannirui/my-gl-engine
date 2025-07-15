//
// Created by rui ding on 2025/7/15.
//

#include "Hazel/renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

#include "Hazel/renderer/Renderer.h"
#include "platform/opengl/OpenGLContext.h"

namespace Hazel
{
    Scope<GraphicsContext> GraphicsContext::Create(void* window)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:
            {
                HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            }
            case RendererAPI::API::OpenGL:
                return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
        }
        HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}  // namespace Hazel
