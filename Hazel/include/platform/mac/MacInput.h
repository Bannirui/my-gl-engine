//
// Created by rui ding on 2025/7/3.
//

#pragma once

#include "Hazel/Input.h"

namespace Hazel
{
    class MacInput : public Input
    {
    protected:
        virtual bool                    IsKeyPressedImpl(int keycode) override;
        virtual bool                    IsMouseButtonPressedImpl(int button) override;
        virtual std::pair<float, float> GetMousePositionImpl() override;
        virtual float                   GetMouseXImpl() override;
        virtual float                   GetMouseYImpl() override;
    };
}