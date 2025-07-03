//
// Created by dingrui on 25-6-22.
//

#include <imgui.h>

#include "Hazel.h"

class ExampleLayer : public Hazel::Layer
{
   public:
    ExampleLayer() : Layer("Example Layer") {}

    void OnUpdate() override
    {
        if (Hazel::Input::IsKeyPressed(Hazel::Key::Tab))
        {
            HZ_TRACE("Tab key is pressed, poll");
        }
    }

    void OnEvent(Hazel::Event& e) override
    {
        if (e.GetEventType() == Hazel::EventType::KeyPressed)
        {
            Hazel::KeyPressedEvent& event = (Hazel::KeyPressedEvent&)e;
            if (event.GetKeyCode() == Hazel::Key::Tab)
            {
                HZ_TRACE("Tab key is pressed, event");
            }
            HZ_TRACE("{0}", (char)event.GetKeyCode());
        }
    }

    virtual void OnImGuiRender() override
    {
        ImGui::Begin("Test");
        ImGui::Text("HELLO WORLD!");
        ImGui::End();
    }
};

class Sandbox : public Hazel::Application
{
   public:
    Sandbox() { PushLayer(new ExampleLayer()); }

    ~Sandbox() {}
};

Hazel::Application* Hazel::CreateApplication()
{
    return new Sandbox();
}
