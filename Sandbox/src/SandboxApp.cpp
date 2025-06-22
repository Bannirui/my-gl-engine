//
// Created by dingrui on 25-6-22.
//
#include "Hazel.h"

class Sandbox : public Hazel::Application
{
public:
    Sandbox()
    {
    }

    ~Sandbox()
    {
    }
};

Hazel::Application* Hazel::CreateApplication()
{
    return new Sandbox();
}