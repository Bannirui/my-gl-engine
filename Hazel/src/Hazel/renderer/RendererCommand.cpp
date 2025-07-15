//
// Created by rui ding on 2025/7/9.
//

#include "Hazel/renderer/RendererCommand.h"

#include "platform/opengl/OpenGLRendererAPI.h"

namespace Hazel
{
    Scope<RendererAPI> RendererCommand::s_RendererAPI = CreateScope<OpenGLRendererAPI>();
}