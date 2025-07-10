//
// Created by rui ding on 2025/7/9.
//

#pragma once

#include "Hazel/renderer/RendererAPI.h"

namespace Hazel
{
    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        virtual void Init() override;
        virtual void SetClearColor(const glm::vec4 color) override;
        virtual void Clear() override;

        virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
    };
}
