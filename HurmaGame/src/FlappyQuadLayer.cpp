#include "FlappyQuadLayer.h"
#include "PlayerQuad.h"
#include "Hurma/Camera/OrthoCamera.h"
#include "Hurma/Input.h"
#include "Hurma/Renderer/Renderer.h"
#include "QuadStaticAbstraction.h"
#include "Hurma/Events/MouseEvent.h"
#include "AbstractionsGenerator.h"
#include "Hurma/Particles/QuadParticlesSystem/QuadsParticleSystem2D.h"
#include "Hurma/Particles/QuadParticlesSystem/RandomizedParticleDirectionProvider.h"

void FlappyQuadLayer::onAttach()
{
    mPlayerQuad = std::make_shared<PlayerQuad>(glm::vec3(0.f), 1.f);
    mPlayerQuad->setVelocity({0.2f, 0.f, 0.f});

    mCamera = std::make_shared<Hurma::OrthoCamera>(-1.f, 1.f, -1.f, 1.f, 0.f, 99999.f, glm::vec3{0.f, 0.f, 1.f}, 
        glm::vec3{0.f, 0.f, 0.f}, glm::vec3{0.f, 1.f, 0.f});

    // mQuadAbstraction = std::make_shared<QuadStaticAbstraction>(glm::vec2(0.f, -2.f + 0.1f), 2.f);
    mAbstractionGenerator = std::make_shared<AbstractionsGenerator>(5, 0.3f, 0.1f, 1.f, -1.f, glm::vec2{0.f, 0.f});
    mParticleSystem = std::make_unique<Hurma::QuadsParticleSystem2D>(std::make_unique<Hurma::RandomizedParticleDirectionProvider>(1));
}

void FlappyQuadLayer::onDetach()
{
}

void FlappyQuadLayer::onUpdate(double deltaTimeSec)
{
//     if(mQuadAbstraction->isCollidingWith(mPlayerQuad.get()))
//         return;
    if(mAbstractionGenerator->isCollidingWith(mPlayerQuad.get()))
        return;

    if (Hurma::Input::isMouseButtonPressed(Hurma::MouseCode::Left))
    {
        mPlayerQuad->applyForce({0.f, 4.f, 0.f});
        mParticleSystem->applyAtPoint(mPlayerQuad->getPosition(), Hurma::ParticlesTraits{ 1, 0.1f, 2.f, 0.1f, 1.5f, {0.5f,0.5f,0.f,1.f} });
    }

    mPlayerQuad->update(deltaTimeSec);
    mAbstractionGenerator->update(deltaTimeSec, mPlayerQuad->getPosition());
    mParticleSystem->update(deltaTimeSec);

    // Camera tracks player's updated position
    mCamera->setEye({mPlayerQuad->getQuadPosition(), mCamera->getEye().z});
    mCamera->setCenter({mPlayerQuad->getQuadPosition(), mCamera->getCenter().z});

    Hurma::Render::Renderer::setClearColor({ 0.1f, 0.1f, 0.1f, 1.f });
    Hurma::Render::Renderer::clear();

    Hurma::Render::Renderer::beginScene(mCamera);
    {
        mPlayerQuad->render();

        mAbstractionGenerator->render();
        mParticleSystem->render();

    }
    Hurma::Render::Renderer::endScene();
}

void FlappyQuadLayer::onEvent(Hurma::Event& event)
{
    Hurma::EventDispatcher dispatcher(event);
    dispatcher.dispatch<Hurma::MouseScrolledEvent>([this](Hurma::MouseScrolledEvent& event) {
        if(event.getYOffset() > 0)
            mCamera->zoom(0.9f);
        else
            mCamera->zoom(1.1f);

        return false;
    });
}

void FlappyQuadLayer::onImGuiRender()
{
}
