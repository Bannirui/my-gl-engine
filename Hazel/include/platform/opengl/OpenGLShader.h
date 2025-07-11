//
// Created by rui ding on 2025/7/10.
//

#pragma once

#include <glm/glm.hpp>

#include "Hazel/renderer/Shader.h"

// todo 临时先用着
typedef unsigned int GLenum;

namespace Hazel
{
    class OpenGLShader : public Shader
    {
    public:
        /**
         * @param srcPath shader源码文件相对路径 一个文件里面放一对vertex和fragment shader
         */
        OpenGLShader(const std::string& srcPath);
        OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
        virtual ~OpenGLShader();

        virtual void               Bind() const override;
        virtual void               Unbind() const override;
        virtual const std::string& GetName() const override { return m_Name; };

        void UploadUniformInt(const std::string& name, int value);
        void UploadUniformFloat(const std::string& name, float value);
        void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
        void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
        void UploadUniformFloat4(const std::string& name, const glm::vec4& value);

        void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
        void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

    private:
        /**
         * @param filepath 源码相对路径 里面包含vertex和fragment shader
         * @return vertex和fragment shader程序代码
         */
        std::string ReadFile(const std::string& filepath);
        /**
         * @param source vertex和fragment源码
         * @return vertex和fragment源码用两个键区分对应的值
         */
        std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
        void                                    Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

    private:
        uint32_t    m_RendererID;
        std::string m_Name;
    };
}