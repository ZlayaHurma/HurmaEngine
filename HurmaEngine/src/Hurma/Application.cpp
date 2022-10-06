#include "Application.h"
#include "Log/Log.h"
#include "Log/impl/SpdLogger.h"
#include "GLFWWindow.h"
#include "Events/Event.h"
#include "LayersStack.h"
#include "Layer.h"

namespace Hurma
{

    #define HURMA_BIND_METHOD(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application::Application() 
        : mWindow(std::make_unique<GLFWWindow>(WindowProps{100, 100, "Test"}))
        , mLayersStack(std::make_unique<LayersStack>())
    {
        Log::InitLogger(std::make_unique<SpdLogger>());

        mWindow->setEventCallback(HURMA_BIND_METHOD(onEvent));
    }
    
    Application::~Application() 
    {
        
    }

    void Application::run() 
    {
        Log::logInfo("Hello!");
        
        while(true)
        {
            mWindow->onUpdate();
        }

    }

    void Application::pushLayer(Layer* layer) 
    {
        mLayersStack->pushLayer(layer);
        layer->onAttach();
    }

    void Application::pushOverlay(Layer* overlay) 
    {
        mLayersStack->pushOverlay(overlay);
        overlay->onAttach();
    }

    void Application::onEvent(Event& event) 
    {
        EventDispatcher dispatcher(event);

        for( auto it = mLayersStack->end(); it != mLayersStack->begin(); )
        {
            (*--it)->onEvent(event);
            if(event.handled)
                break;
        }
    }

};
