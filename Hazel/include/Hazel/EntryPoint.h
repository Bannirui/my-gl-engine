//
// Created by dingrui on 25-6-22.
//

#pragma once

extern Hazel::Application* CreateApplication();

int main(int argc, char** argv)
{
    printf("Running...\n");
    auto app = Hazel::CreateApplication();
    app->Run();
    delete app;
}