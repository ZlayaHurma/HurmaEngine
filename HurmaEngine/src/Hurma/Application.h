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

    namespace Render
    {
        class IVertexBuffer;
        class IVertexArray;
        class IShader;
    }

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

         double mLastUpdateTime {0.0};

         static Application* sInstance;
    };

    Application* createApplication();
}
