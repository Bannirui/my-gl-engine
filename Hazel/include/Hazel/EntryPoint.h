//
// Created by dingrui on 25-6-22.
//

#pragma once
#include "Log.h"

extern Hazel::Application* CreateApplication();

int main(int argc, char** argv)
{
    Hazel::Log::Init();
    auto app = Hazel::CreateApplication();
    app->Run();
    delete app;
}