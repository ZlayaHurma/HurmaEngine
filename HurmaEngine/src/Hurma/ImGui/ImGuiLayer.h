#pragma once
#include "Hurma/Layer.h"
#include "Hurma/Core.h"

namespace Hurma
{
    class HURMA_API ImGuiLayer : public Layer 
    {
     public:
        ImGuiLayer();

        void onAttach() override;

        void onDetach() override;

        void onUpdate() override;

        void onEvent(Event& event) override;

        void onImGuiRender() override;

        void begin();

        void end();

       private:
         bool onMouseButtonPressedEvent(class MouseButtonPressedEvent& e);
         bool onMouseButtonReleasedEvent(class MouseButtonReleasedEvent& e);
         bool onMouseMoveEvent(class MouseMovedEvent& e);
         bool onMouseScrolledEvent(class MouseScrolledEvent& e);
         bool onKeyPressedEvent(class KeyPressedEvent& e);
         bool onKeyReleasedEvent(class KeyReleasedEvent& e);
         bool onWindowResizeEvent(class WindowResizeEvent& e);

     private: 
         float mTime {};
    };
}