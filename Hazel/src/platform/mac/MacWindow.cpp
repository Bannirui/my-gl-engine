//
// Created by rui ding on 2025/6/25.
//

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include "hzpch.h"
#include "platform/mac/MacWindow.h"
#include "Hazel/Core/Assert.h"
#include "Hazel/Log.h"

namespace Hazel {
    static bool s_GLFWInitialized = false;

    Window* Window::Create(const WindowProps &props) {
        return new MacWindow(props);
    }

    MacWindow::MacWindow(const WindowProps &props) {
        Init(props);
    }

    MacWindow::~MacWindow() {
        Shutdown();
    }

    void MacWindow::Init(const WindowProps &props) {
        int succ;
        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;
        HZ_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);
        if (!s_GLFWInitialized) {
            succ = glfwInit();
            // 防止编译器unused warn
            (void)succ;
            HZ_CORE_ASSERT(succ, "Could not intialize GLFW!");
            s_GLFWInitialized = true;
        }
        m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);
        // 有了上下文 开始初始化glad
        succ = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        (void)succ;
        HZ_CORE_ASSERT(succ, "Could not intialize GLAD!");
        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);
    }

    void MacWindow::Shutdown() {
        glfwDestroyWindow(m_Window);
    }

    void MacWindow::OnUpdate() {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    void MacWindow::SetVSync(bool enabled) {
        if (enabled) {
            glfwSwapInterval(1);
        } else {
            glfwSwapInterval(0);
        }
        m_Data.VSync = enabled;
    }

    bool MacWindow::IsVSync() const {
        return m_Data.VSync;
    }

}