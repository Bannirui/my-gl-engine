//
// Created by rui ding on 2025/7/3.
//

#pragma once

namespace Hazel
{
    class Input
    {
    protected:
        Input() = default;

    public:
        /**
         * 禁用拷贝构造
         */
        Input(const Input&) = delete;
        /**
         * 禁用拷贝赋值
         */
        Input& operator=(const Input&) = delete;

        inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
        inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
        inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
        inline static float                   GetMouseX() { return s_Instance->GetMouseXImpl(); }
        inline static float                   GetMouseY() { return s_Instance->GetMouseYImpl(); }

    protected:
        virtual bool                    IsKeyPressedImpl(int keycode)        = 0;
        virtual bool                    IsMouseButtonPressedImpl(int button) = 0;
        virtual std::pair<float, float> GetMousePositionImpl()               = 0;
        virtual float                   GetMouseXImpl()                      = 0;
        virtual float                   GetMouseYImpl()                      = 0;

    private:
        static Input* s_Instance;
    };
}  // namespace Hazel