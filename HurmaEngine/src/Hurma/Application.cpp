#include "Application.h"
#include "Log/Log.h"
#include "Log/impl/SpdLogger.h"
#include "GLFWWindow.h"
#include "Events/Event.h"
#include "LayersStack.h"
#include "Layer.h"
#include "glad/glad.h"
#include "ImGui/ImGuiLayer.h"

namespace Hurma
{

    Application* Application::sInstance = nullptr;

    Application::Application() 
        : mWindow(std::make_unique<GLFWWindow>(WindowProps{1000, 1000, "Test"}))
        , mLayersStack(std::make_unique<LayersStack>())
    {
        Log::InitLogger(std::make_unique<SpdLogger>());

        mWindow->setEventCallback(HURMA_BIND_METHOD(Application::onEvent));

        _ASSERTE(!sInstance);
        sInstance = this;

        mImGuiLayer = new ImGuiLayer();
        pushOverlay(mImGuiLayer);
    }
    
    Application::~Application() 
    {
        
    }

    void Application::run() 
    {
        Log::logInfo("Hello!");
        
        while(true)
        {
            glClearColor(1,1,1,1);
            glClear(GL_COLOR_BUFFER_BIT);

            for(Layer* layer : *mLayersStack)
            {
                layer->onUpdate();
            }

            for(Layer* layer : *mLayersStack)
            {
                mImGuiLayer->begin();
                layer->onImGuiRender();
                mImGuiLayer->end();
            }

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
            if(event.isHandled())
                break;
        }
    }

};
