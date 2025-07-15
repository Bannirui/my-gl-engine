//
// Created by rui ding on 2025/7/15.
//

#pragma once

#include "Hazel/renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Hazel
{

    class OpenGLContext : public GraphicsContext
    {
    public:
        OpenGLContext(GLFWwindow* windowHandle);

        void Init() override;
        void SwapBuffers() override;

    private:
        GLFWwindow* m_WindowHandle;
    };
}  // namespace Hazel
