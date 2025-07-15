//
// Created by rui ding on 2025/7/15.
//

#include "platform/opengl/OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Hazel/Core/Assert.h"

Hazel::OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle)
{
    HZ_CORE_ASSERT(windowHandle, "Window handle is null!")
}
void Hazel::OpenGLContext::Init()
{
    glfwMakeContextCurrent(m_WindowHandle);
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    (void)status;
    HZ_CORE_ASSERT(status, "Failed to initialize Glad!");
}
void Hazel::OpenGLContext::SwapBuffers()
{
    glfwSwapBuffers(m_WindowHandle);
}
