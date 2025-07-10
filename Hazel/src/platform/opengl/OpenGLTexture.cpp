//
// Created by rui ding on 2025/7/10.
//

#include "platform/opengl/OpenGLTexture.h"

#include <stb_image.h>
#include <glad/glad.h>

#include "Hazel/Core/Assert.h"

namespace Hazel
{
    OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
        : m_Path(path)
    {
        int width, height, channels;
        // 转换坐标原点 左上角->左下角
        stbi_set_flip_vertically_on_load(1);
        // 读图片
        stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, STBI_rgb_alpha);
        HZ_CORE_ASSERT(data, "Failed to load image!");
        m_Width  = width;
        m_Height = height;

        GLenum internalFormat = 0, dataFormat = 0;
        if (channels == 4)
        {
            internalFormat = GL_RGBA8;
            dataFormat     = GL_RGBA;
        }
        else if (channels == 3)
        {
            internalFormat = GL_RGB8;
            dataFormat     = GL_RGB;
        }

        HZ_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");

        // 创建纹理对象
        glGenTextures(1, &m_RendererID);
        // 绑定纹理单元 不显式激活纹理单元 默认用0号纹理单元
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
        // 开辟显存 传输图片数据
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
        // 纹理过滤器
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        stbi_image_free(data);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &m_RendererID);
    }

    void OpenGLTexture2D::Bind(uint32_t slot) const
    {
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
    }
}