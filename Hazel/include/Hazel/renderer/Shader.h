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

        /**
         * @param srcPath 源码文件 相对路径 一个源码文件中是一对vertex和fragment shader
         */
        static Shader* Create(const std::string& srcPath);
        /**
         * @param vertexSrc vertex shader的源码
         * @param fragmentSrc fragment shader的源码
         * @return
         */
        static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
    };
}