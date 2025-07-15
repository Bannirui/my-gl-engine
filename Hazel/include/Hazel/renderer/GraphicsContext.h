//
// Created by rui ding on 2025/7/15.
//

#pragma once

#include "Hazel/Core.h"

namespace Hazel
{
    class GraphicsContext
    {
    public:
        virtual ~GraphicsContext() = default;

        virtual void Init()        = 0;
        virtual void SwapBuffers() = 0;

        static Scope<GraphicsContext> Create(void* window);
    };
}  // namespace Hazel
