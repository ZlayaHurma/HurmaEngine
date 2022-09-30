#include "Application.h"
#include "Log/Log.h"
#include "Log/impl/SpdLogger.h"

namespace Hurma
{

    Application::Application() 
    {
        Log::InitLogger(std::make_unique<SpdLogger>());
    }
    
    Application::~Application() 
    {
        
    }

    void Application::run() 
    {
        Log::logInfo("Hello!");
    }

};
