//
// Created by rui ding on 2025/7/10.
//

#pragma once

#include "hzpch.h"
#include "Hazel/Core.h"

namespace Hazel
{
    class Texture
    {
    public:
        virtual ~Texture() = default;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;

        virtual void Bind(uint32_t slot = 0) const = 0;
    };

    class Texture2D : public Texture
    {
    public:
        /**
         * @param path 图片路径 相对路径
         */
        static Ref<Texture2D> Create(const std::string& path);
    };
}