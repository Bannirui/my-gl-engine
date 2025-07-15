//
// Created by rui ding on 2025/7/10.
//

#pragma once

#include "glm/gtx/io.hpp"
#include "Hazel/renderer/Texture.h"

namespace Hazel
{
    class OpenGLTexture2D : public Texture2D
    {
       public:
        /**
         * @param path 图片相对路径
         */
        OpenGLTexture2D(const std::string& path);
        virtual ~OpenGLTexture2D();

        virtual uint32_t GetWidth() const override { return m_Width; }
        virtual uint32_t GetHeight() const override { return m_Height; }

        virtual void Bind(uint32_t slot = 0) const override;

       private:
        std::string m_Path;
        int         m_Width, m_Height;
        uint32_t    m_RendererID;
    };
}  // namespace Hazel