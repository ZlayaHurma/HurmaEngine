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

        void onUpdate(double deltaTimeSec) override;

        void onEvent(Event& event) override;

        void onImGuiRender() override;

        void begin();

        void end();

     private: 
         float mTime {};
    };
}