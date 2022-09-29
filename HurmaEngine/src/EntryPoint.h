#pragma once
#include "Application.h"

int main()
{
    Hurma::Application* app = Hurma::createApplication();
    app->run();
    delete app;
}