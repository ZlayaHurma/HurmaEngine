#include "Application.h"
#include "Log/Log.h"
#include "Log/impl/SpdLogger.h"
#include "GLFWWindow.h"

namespace Hurma
{

    Application::Application() 
    {
        Log::InitLogger(std::make_unique<SpdLogger>());
        IWindow* window = new GLFWWindow({100, 100, "Test"});
        window->SetEventCallback([](const Event& ev) { 
            Log::logInfo(ev.toString()); 
        });
    }
    
    Application::~Application() 
    {
        
    }

    void Application::run() 
    {
        Log::logInfo("Hello!");
    }

};
