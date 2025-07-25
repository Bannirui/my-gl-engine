//
// Created by rui ding on 2025/7/8.
//

#include "platform/opengl/OpenGLVertexArray.h"

#include "spdlog/fmt/bundled/base.h"

#include <glad/glad.h>

namespace Hazel
{
    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
            case Hazel::ShaderDataType::Float:
                return GL_FLOAT;
            case Hazel::ShaderDataType::Float2:
                return GL_FLOAT;
            case Hazel::ShaderDataType::Float3:
                return GL_FLOAT;
            case Hazel::ShaderDataType::Float4:
                return GL_FLOAT;
            case Hazel::ShaderDataType::Mat3:
                return GL_FLOAT;
            case Hazel::ShaderDataType::Mat4:
                return GL_FLOAT;
            case Hazel::ShaderDataType::Int:
                return GL_INT;
            case Hazel::ShaderDataType::Int2:
                return GL_INT;
            case Hazel::ShaderDataType::Int3:
                return GL_INT;
            case Hazel::ShaderDataType::Int4:
                return GL_INT;
            case Hazel::ShaderDataType::Bool:
                return GL_BOOL;
            default:
            {
                HZ_CORE_ASSERT(false, "Unknown ShaderDataType!");
                return 0;
            }
        }
    }

    OpenGLVertexArray::OpenGLVertexArray()
    {
        glGenVertexArrays(1, &m_RendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &m_RendererID);
    }

    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(m_RendererID);
    }

    void OpenGLVertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
    {
        HZ_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

        glBindVertexArray(m_RendererID);
        vertexBuffer->Bind();

        uint32_t    index  = 0;
        const auto& layout = vertexBuffer->GetLayout();
        for (const auto& element : layout)
        {
            glEnableVertexAttribArray(index + m_VertexBufferIndex);
            glVertexAttribPointer(index + m_VertexBufferIndex, element.GetComponentCount(),
                                  ShaderDataTypeToOpenGLBaseType(element.Type), element.Normalized ? GL_TRUE : GL_FALSE,
                                  layout.GetStride(),
                                  reinterpret_cast<const void*>(static_cast<uintptr_t>(element.Offset)));
            m_VertexBufferIndex++;
        }
        m_VertexBuffers.push_back(vertexBuffer);
        m_VertexBufferIndex += layout.GetElements().size();
    }

    void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
    {
        glBindVertexArray(m_RendererID);
        indexBuffer->Bind();

        m_IndexBuffer = indexBuffer;
    }
}  // namespace Hazel