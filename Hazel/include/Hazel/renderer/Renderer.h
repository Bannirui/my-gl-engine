//
// Created by rui ding on 2025/7/7.
//

#pragma once

namespace Hazel
{
    enum class RendererAPI
    {
        None = 0, OpenGL = 1
    };

    class Renderer
    {
    public:
        inline static RendererAPI GetAPI() { return s_RendererAPI; };

    private :
        static RendererAPI s_RendererAPI;
    };
}
