//
// Created by rui ding on 2025/7/17.
//

#pragma once

#include "Hazel.h"

class Sandbox2D : public Hazel::Layer
{
public:
    Sandbox2D();
    virtual ~Sandbox2D() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    void         OnUpdate(Hazel::Timestep ts) override;
    virtual void OnImGuiRender() override;
    void         OnEvent(Hazel::Event& e) override;

private:
    Hazel::OrthographicCameraController m_CameraController;
    Hazel::Ref<Hazel::VertexArray>      m_SquareVA;
    Hazel::Ref<Hazel::Shader>           m_FlatColorShader;
    glm::vec4                           m_SquareColor = {0.2f, 0.3f, 0.8f, 1.0f};
};
