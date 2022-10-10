#pragma once
#include "Core.h"
#include <memory>

namespace Hurma
{
    class Layer;
    class Event;
    class IWindow;
    class LayersStack;
    class ImGuiLayer;

    class HURMA_API Application 
    {
     public:
        Application();
        ~Application();

        void run();

	    void pushLayer(Layer* layer);
	    void pushOverlay(Layer* overlay);

        IWindow* getWindow() { return mWindow.get(); } 

        static Application& get() { return *sInstance; }

     private:
         void onEvent(Event& event);

     private:
         #pragma warning(push)
         #pragma warning(disable:4251)
         std::unique_ptr<IWindow> mWindow;
         std::unique_ptr<LayersStack> mLayersStack;
         #pragma warning(pop)

         ImGuiLayer* mImGuiLayer;

         static Application* sInstance;
    };

    Application* createApplication();
}
