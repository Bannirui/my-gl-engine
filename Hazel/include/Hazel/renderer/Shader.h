//
// Created by rui ding on 2025/7/7.
//

#pragma once

namespace Hazel
{
    class Shader
    {
    public:
        virtual ~Shader() = default;

        virtual void Bind() const =0;
        virtual void Unbind() const =0;

        static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
    };
}