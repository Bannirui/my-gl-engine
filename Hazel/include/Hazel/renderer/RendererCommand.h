//
// Created by rui ding on 2025/7/9.
//

#pragma once

#include "Hazel/renderer/RendererAPI.h"

namespace Hazel
{
    class RendererCommand
    {
    public:
        inline static void SetClearColor(const glm::vec4 color)
        {
            s_RendererAPI->SetClearColor(color);
        }

        inline static void Clear()
        {
            s_RendererAPI->Clear();
        }

        inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
        {
            s_RendererAPI->DrawIndexed(vertexArray);
        }

    private:
        static RendererAPI* s_RendererAPI;
    };
}
