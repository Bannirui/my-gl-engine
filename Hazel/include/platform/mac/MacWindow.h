//
// Created by rui ding on 2025/6/25.
//

#pragma once

#include "Hazel/Window.h"
#include "Hazel/renderer/GraphicsContext.h"

// 前向声明
struct GLFWwindow;

namespace Hazel
{

    class MacWindow : public Window
    {
    public:
        MacWindow(const WindowProps& props);
        virtual ~MacWindow();
        void                OnUpdate() override;
        inline unsigned int GetWidth() const override { return m_Data.Width; }
        inline unsigned int GetHeight() const override { return m_Data.Height; }
        inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
        void        SetVSync(bool enabled) override;
        bool        IsVSync() const override;

        inline void* GetNativeWindow() const override { return m_Window; }

    private:
        virtual void Init(const WindowProps& props);
        virtual void Shutdown();

    private:
        GLFWwindow*            m_Window;
        Scope<GraphicsContext> m_Context;

        struct WindowData
        {
            std::string     Title;
            unsigned int    Width, Height;
            bool            VSync;
            EventCallbackFn EventCallback;
        };
        WindowData m_Data;
    };

}  // namespace Hazel