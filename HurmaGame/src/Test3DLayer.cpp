#include "Test3DLayer.h"
#include "Test3DLayer.h"
#include "PlayerQuad.h"
#include "Hurma/Camera/OrthoCamera.h"
#include "Hurma/Input.h"
#include "Hurma/Renderer/Renderer.h"
#include "QuadStaticAbstraction.h"
#include "Hurma/Events/MouseEvent.h"
#include "AbstractionsGenerator.h"
#include "Hurma/Particles/QuadParticlesSystem/QuadsParticleSystem2D.h"
#include "Hurma/Particles/QuadParticlesSystem/RandomizedParticleDirectionProvider.h"

void Test3DLayer::onAttach()
{
    mCamera = std::make_shared<Hurma::OrthoCamera>(-1.f, 1.f, -1.f, 1.f, 0.f, 99999.f, glm::vec3{0.f, 0.f, 1.f}, 
        glm::vec3{0.f, 0.f, 0.f}, glm::vec3{0.f, 1.f, 0.f});

    Hurma::Render::Renderer::setLightDirection({-0.5f, -0.5f, -0.5f});
}

void Test3DLayer::onDetach()
{
}

void Test3DLayer::onUpdate(double deltaTimeSec)
{
    if (Hurma::Input::isMouseButtonPressed(Hurma::MouseCode::Left))
    {
    }
    if (Hurma::Input::isKeyPressed(Hurma::KeyCode::Left))
    {
        mCamera->rotateCamera({-0.01f, 0.f});
    }
    if (Hurma::Input::isKeyPressed(Hurma::KeyCode::Right))
    {
        mCamera->rotateCamera({0.01f, 0.f});
    }
    if (Hurma::Input::isKeyPressed(Hurma::KeyCode::Up))
    {
        mCamera->rotateCamera({0.f, 0.01f});
    }
    if (Hurma::Input::isKeyPressed(Hurma::KeyCode::Down))
    {
        mCamera->rotateCamera({0.f, -0.01f});
    }

    Hurma::Render::Renderer::setClearColor({ 0.1f, 0.1f, 0.1f, 1.f });
    Hurma::Render::Renderer::clear();

    Hurma::Render::Renderer::beginScene(mCamera);
    {
        Hurma::Render::Renderer::drawCube({0.f, 0.f, 0.f}, 0.5f, {1.f, 0.f, 0.f, 1.f});
    }
    Hurma::Render::Renderer::endScene();
}

void Test3DLayer::onEvent(Hurma::Event& event)
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

void Test3DLayer::onImGuiRender()
{
}
