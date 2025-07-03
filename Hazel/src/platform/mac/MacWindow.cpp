//
// Created by rui ding on 2025/6/25.
//

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include "hzpch.h"
#include "platform/mac/MacWindow.h"

#include "Hazel/Event/ApplicationEvent.h"
#include "Hazel/Event/KeyEvent.h"
#include "Hazel/Event/MouseEvent.h"
#include "Hazel/Core/Assert.h"
#include "Hazel/Log.h"

namespace Hazel {
    static bool s_GLFWInitialized = false;

    static void GLFWErrorCallback(int error, const char* description) {
        HZ_CORE_ERROR("GLFW Error ({0}):{1}", error, description);
    }

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
            glfwSetErrorCallback(GLFWErrorCallback);
            s_GLFWInitialized = true;
        }
        // OpenGL版本3.3
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        // 使用核心模式
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
        m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);
        // 有了上下文 开始初始化glad 加载处理显卡提供的驱动函数 以后才能使用gl函数
        succ = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        (void)succ;
        HZ_CORE_ASSERT(succ, "Could not intialize GLAD!");
        // 缓存到glfw的窗口中 将来可以从里面取出来用
        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);
        // 向glfw窗体注册事件监听
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) -> void {
            // 从glfw窗体中拿到缓存
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            // 窗口新的大小
            data.Width = width;
            data.Height = height;
            WindowResizeEvent event(width, height);
            data.EventCallback(event);
        });
        // glfw窗体关闭事件监听
        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) -> void {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.EventCallback(event);
        });
        // 监听glfw的键盘事件
        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) -> void {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            switch (action) {
                case GLFW_PRESS: {
                    KeyPressedEvent event(key, 0);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    KeyReleasedEvent event(key);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT: {
                    KeyPressedEvent event(key, 1);
                    data.EventCallback(event);
                    break;
                }
            }
        });
        // 键盘输入监听
        glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int codepoint) -> void {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            KeyTypedEvent event(codepoint);
            data.EventCallback(event);
        });
        // 监听glfw鼠标点击事件
        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) -> void {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            switch (action) {
                case GLFW_PRESS: {
                    MouseButtonPressedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    MouseButtonReleasedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
            }
        });
        // 监听鼠标滚轮
        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset) -> void {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            MouseScrolledEvent event((float)xoffset, (float)yoffset);
            data.EventCallback(event);
        });
        // 监听鼠标位置
        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos) -> void {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            MouseMovedEvent event((float)xpos, (float)ypos);
            data.EventCallback(event);
        });
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