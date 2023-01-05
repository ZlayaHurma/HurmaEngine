#pragma once
#include "Hurma/Layer.h"
#include "Hurma/Events/Event.h"

namespace Hurma
{
    class OrthoCamera;
    class QuadsParticleSystem2D;
}

class Test3DLayer : public Hurma::Layer
{
public:
    void onAttach() override;

    void onDetach() override;

    void onUpdate(double deltaTimeSec) override;

    void onEvent(Hurma::Event& event) override;

    void onImGuiRender() override;

private:
    std::shared_ptr<Hurma::OrthoCamera> mCamera;
};

