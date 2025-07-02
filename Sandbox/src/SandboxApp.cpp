//
// Created by dingrui on 25-6-22.
//
#include "Hazel.h"

class ExampleLayer : public Hazel::Layer
{
    public:
        ExampleLayer() : Layer("Example Layer") { }

        void OnUpdate() override {
            HZ_INFO("Example Layer::OnUpdate");
        }

        void OnEvent(Hazel::Event& e) override {
            HZ_TRACE("Example Layer::OnEvent {0}", e.ToString());
        }
};

class Sandbox : public Hazel::Application
{
    public:
        Sandbox() {
            PushLayer(new ExampleLayer());
        }

        ~Sandbox() { }
};

Hazel::Application* Hazel::CreateApplication()
{
    return new Sandbox();
}