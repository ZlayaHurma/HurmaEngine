#include "Application.h"
#include "Log/Log.h"
#include "Log/impl/SpdLogger.h"
#include "GLFWWindow.h"
#include "Events/Event.h"
#include "LayersStack.h"
#include "Layer.h"
#include "glad/glad.h"
#include "ImGui/ImGuiLayer.h"
#include "GLFW/glfw3.h"
#include "Renderer/OpenGLVertexBuffer.h"
#include "Renderer/IVertexBuffer.h"
#include "Renderer/OpenGLIndexBuffer.h"
#include "Renderer/OpenGLVertexArray.h"
#include "Renderer/BufferLayout.h"
#include "Renderer/OpenGLShader.h"
#include "Renderer/Renderer.h"
#include "Events/ApplicationEvent.h"

namespace Hurma
{

    Application* Application::sInstance = nullptr;

    Application::Application() 
        : mWindow(std::make_unique<GLFWWindow>(WindowProps{1000, 1000, "Test"}))
        , mLayersStack(std::make_unique<LayersStack>())
    {
        Log::InitLogger(std::make_unique<SpdLogger>());
        Render::Renderer::init();

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
        using namespace Render;

        Log::logInfo("Hello!");
        
        while(!mWindow->shouldClose())
        {
            const double currTime = glfwGetTime();
            double updateDeltaTimeSec = currTime - mLastUpdateTime;
            mLastUpdateTime = currTime;

            for(Layer* layer : *mLayersStack)
            {
                layer->onUpdate(updateDeltaTimeSec);
            }

            mImGuiLayer->begin();
            for(Layer* layer : *mLayersStack)
            {
                layer->onImGuiRender();
            }
            mImGuiLayer->end();

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
        dispatcher.dispatch<WindowResizeEvent>(HURMA_BIND_METHOD(Application::onWindowResizeEvent));

        for( auto it = mLayersStack->end(); it != mLayersStack->begin(); )
        {
            (*--it)->onEvent(event);
            if(event.isHandled())
                break;
        }
    }

    bool Application::onWindowResizeEvent(WindowResizeEvent& resizeEvent) 
    {
        Render::Renderer::onWindowResize(resizeEvent.getWidth(), resizeEvent.getHeight());
        return false;
    }

};
