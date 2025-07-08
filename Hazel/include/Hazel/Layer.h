//
// Created by rui ding on 2025/7/2.
//

#pragma once

#include <string>

#include "Hazel/Event/Event.h"

namespace Hazel
{
    class Layer
    {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer() = default;

        virtual void OnAttach()
        {
        }

        virtual void OnDetach()
        {
        }

        virtual void OnUpdate()
        {
        }

        virtual void OnImGuiRender()
        {
        }

        virtual void OnEvent(Event& e)
        {
        }

        inline const std::string& GetName() const { return m_DebugName; }

    private:
        std::string m_DebugName;
    };
} // namespace Hazel
