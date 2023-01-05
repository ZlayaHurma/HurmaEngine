#pragma once
#include "Hurma/Layer.h"
#include "Hurma/Events/Event.h"

namespace Hurma
{
    class OrthoCamera;
    class QuadsParticleSystem2D;
}

class FlappyQuadLayer : public Hurma::Layer
{
public:
    void onAttach() override;

    void onDetach() override;

    void onUpdate(double deltaTimeSec) override;

    void onEvent(Hurma::Event& event) override;

    void onImGuiRender() override;

private:
    std::shared_ptr<class PlayerQuad> mPlayerQuad;
    std::shared_ptr<Hurma::OrthoCamera> mCamera;

    std::shared_ptr<class AbstractionsGenerator> mAbstractionGenerator;
    std::shared_ptr<class Hurma::QuadsParticleSystem2D> mParticleSystem;
};

