//
// Created by dingrui on 25-6-22.
//
#include "Hazel.h"

class Sanbox : public Hazel::Application
{
public:
    Sanbox()
    {
    }

    ~Sanbox()
    {
    }
};

Hazel::Application* Hazel::CreateApplication()
{
    return new Sanbox();
}