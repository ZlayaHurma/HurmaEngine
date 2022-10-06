#pragma once
#include "Core.h"
#include <memory>

namespace Hurma
{
    class Layer;
    class Event;
    class IWindow;
    class LayersStack;

    class HURMA_API Application 
    {
     public:
        Application();
        ~Application();

        void run();

	    void pushLayer(Layer* layer);
	    void pushOverlay(Layer* overlay);

     private:
         void onEvent(Event& event);

     private:
         #pragma warning(push)
         #pragma warning(disable:4251)
         std::unique_ptr<IWindow> mWindow;
         std::unique_ptr<LayersStack> mLayersStack;
         #pragma warning(pop)
    };

    Application* createApplication();
}
