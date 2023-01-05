#include "GameLayer.h"
#include "Hurma.h" 
#include "Hurma/Log/Log.h"
#include "Hurma/ImGui/ImGuiLayer.h"
#include "Hurma/Layer.h"
#include "Hurma/Renderer/Renderer.h"
#include "Hurma/Renderer/IIndexBuffer.h"
#include "glm/matrix.hpp"
#include "Hurma/Camera/Camera.h"
#include "Hurma/Camera/OrthoCamera.h"
#include "Hurma/Events/Event.h"
#include "Hurma/Events/KeyEvent.h"
#include "Hurma/Input.h"
#include "Hurma/Events/ApplicationEvent.h"
#include "Hurma/Renderer/BufferLayout.h"
#include "Hurma/Renderer/IVertexArray.h"
#include "Hurma/Renderer/IShader.h"
#include "Hurma/Renderer/ITexture.h"
#include "glad/glad.h"
#include "Hurma/Particles/QuadParticlesSystem/QuadsParticleSystem2D.h"
#include "Hurma/Particles/QuadParticlesSystem/RandomizedParticleDirectionProvider.h"
#include "Hurma/IWindow.h"
#include "PlayerQuad.h"

void GameLayer::onAttach()
{
    using namespace Hurma;

    //       mTriangleVertexArray = Render::Renderer::createVertexArray();
    // 
    //       float triVertices[3 * 5] = {
    //          -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
    //           0.5f, -0.5f, 0.0f, 0.0f, 1.f,
    //           0.0f,  0.5f, 0.0f, 1.f,  1.f,
    //         };
    //         std::shared_ptr<Render::IVertexBuffer> triVertexBuffer = 
    //             Render::Renderer::createVertexBuffer(triVertices, static_cast<uint32_t>(sizeof(triVertices)));
    // 
    //         triVertexBuffer->setLayout(Render::BufferLayout({
    //             {ShaderDataType::Float3, "position"}, 
    //             {ShaderDataType::Float2, "textureCoords"}
    //         }));
    //         
    //         unsigned int triIndices[3] = { 0, 1, 2 };
    //         std::shared_ptr<Render::IIndexBuffer> triIndexBuffer = 
    //             Render::Renderer::createIndexBuffer(triIndices, static_cast<uint32_t>(sizeof(triIndices)));
    //         
    //         mTriangleVertexArray->addVertexBuffer(triVertexBuffer);
    //         mTriangleVertexArray->setIndexBuffer(triIndexBuffer);

    mRectVertexArray = Render::Renderer::createVertexArray();

    float rectVertices[5 * 5] = {
     -0.5f, -0.5f, 0.0f, 0.f, 0.f,
     -0.5f,  0.5f, 0.0f, 0.f, 1.f,
      0.1f,  0.1f, 0.0f, 1.f, 1.f,
      0.5f, -0.5f, 0.0f, 1.f, 0.f,
     -1.f,   0.f,  0.0f, 0.5, 0.5
    };
    std::shared_ptr<Render::IVertexBuffer> rectVertexBuffer =
        Render::Renderer::createVertexBuffer(rectVertices, static_cast<uint32_t>(sizeof(rectVertices)));

    rectVertexBuffer->setLayout(Render::BufferLayout({
        {ShaderDataType::Float3, "position"},
        {ShaderDataType::Float2, "textureCoords"}
        }));

    unsigned int rectIndices[9] = { 0, 1, 2, 0, 2, 3, 0, 1, 4 };
    std::shared_ptr<Render::IIndexBuffer> rectIndexBuffer =
        Render::Renderer::createIndexBuffer(rectIndices, static_cast<uint32_t>(sizeof(rectIndices)));

    mRectVertexArray->addVertexBuffer(rectVertexBuffer);
    mRectVertexArray->setIndexBuffer(rectIndexBuffer);

    std::string vert = R"(
            #version 330 core

            layout(location = 0) in vec3 aPosition;
            layout(location = 1) in vec2 aTextureCoords;

            uniform mat4 uProjMatrix;
            uniform mat4 uViewMatrix;

            out vec2 vTextureCoords;

            void main(){
                gl_Position = uProjMatrix * uViewMatrix * vec4(aPosition, 1.0);
                vTextureCoords = aTextureCoords;
            }
        )";

    std::string frag = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec2 vTextureCoords;

            uniform sampler2D uTexture;

            void main(){
              color = texture(uTexture, vTextureCoords);
            }
        )";

    mTriangleShader = Render::Renderer::createShader(vert, frag);
    mRectShader = Render::Renderer::createShader(vert, frag);
    mRectShader->uploadUniformInt(0, "uTexture");

    mTexture = Render::Renderer::createTexture("D:\\CPP Projects\\HurmaEngine\\HurmaGame\\src\\sm.png");
    mTexture2 = Render::Renderer::createTexture("D:\\CPP Projects\\HurmaEngine\\HurmaGame\\src\\car.png");

    mCamera = std::make_shared<Hurma::OrthoCamera>(-1.f, 1.f, -1.f, 1.f, 0.f, 9999.f, glm::vec3{ 0.f,0.f,1.f }, glm::vec3{ 0.f,0.f,0.f }, glm::vec3{ 0.f,1.f,0.f });
    mParticleSystem = std::make_unique<Hurma::QuadsParticleSystem2D>(std::make_unique<Hurma::RandomizedParticleDirectionProvider>(1));

    player = new PlayerQuad(glm::vec3(0.f), 1.f);
}

void GameLayer::onDetach()
{
}

void GameLayer::onUpdate(double deltaTimeSec)
{
    using namespace Hurma::Render;

    mParticleSystem->update(deltaTimeSec);

    const static double cameraSpeed = 4;
    double cameraOffset = cameraSpeed * deltaTimeSec;

    if (Hurma::Input::isKeyPressed(Hurma::KeyCode::Left))
        mCamera->moveCamera({ -cameraOffset, 0, 0 });
    if (Hurma::Input::isKeyPressed(Hurma::KeyCode::Right))
        mCamera->moveCamera({ cameraOffset, 0, 0 });
    if (Hurma::Input::isKeyPressed(Hurma::KeyCode::Up))
        mCamera->moveCamera({ 0, cameraOffset, 0 });
    if (Hurma::Input::isKeyPressed(Hurma::KeyCode::Down))
        mCamera->moveCamera({ 0, -cameraOffset, 0 });
    if (Hurma::Input::isMouseButtonPressed(Hurma::MouseCode::Left))
    {
        auto mousePos = Hurma::Input::getMousePosition();
        mousePos[0] /= Hurma::Application::get().getWindow()->getWidth();
        mousePos[1] /= Hurma::Application::get().getWindow()->getHeight();
        std::swap(mousePos[0], mousePos[1]);
        mousePos[1] *= -1;
        mParticleSystem->applyAtPoint(mousePos, Hurma::ParticlesTraits{ 1, 0.1f, 2.f, 0.1f, 1.5f, {0.5f,0.5f,0.f,1.f} });
        player->applyForce({0.f, player->getMass() * player->getAcceleration() * 2, 0.f});
    }

    player->update(deltaTimeSec);

    Renderer::setClearColor({ 0.1f, 0.1f, 0.1f, 1 });
    Renderer::clear();

    Renderer::beginScene(mCamera);
    {
        Renderer::draw2DQuad({ 1.f,1.f }, 0.5f, glm::pi<float>() * 0.25f, mTexture2);

        mTexture->bind();
        Renderer::submit(mTriangleShader, mRectVertexArray);
        // 
        //mTexture2->bind();
        //Renderer::draw2DQuad({ 0.f, 0.f }, 0.5f, 0.f, mTexture2);

        Renderer::draw2DQuad({ -1.f,-1.f }, 0.5f, glm::pi<float>() * 0.25f, glm::vec4(1, 0, 0, 1));
        Renderer::draw2DQuad({ 1.f,-1.f }, 0.5f, glm::pi<float>() * 0.25f, glm::vec4(1, 0, 0, 1));
        Renderer::draw2DQuad({ -1.f,1.f }, 0.5f, glm::pi<float>() * 0.25f, glm::vec4(1, 0, 0, 1));

        mParticleSystem->render();
        player->render();

    }
    Renderer::endScene();
}

void GameLayer::onEvent(Hurma::Event& event)
{
    Hurma::EventDispatcher dispatcher(event);
    dispatcher.dispatch<Hurma::KeyPressedEvent>([this](Hurma::KeyPressedEvent& event) {

        const static double cameraSpeed = 50.0;
        double cameraOffset = cameraSpeed /** mLastDeltaTimeSec*/;

        switch (event.getKeyCode())
        {
        case Hurma::KeyCode::Left:
            //mCamera->moveCamera({-cameraOffset, 0, 0});
            break;

        case Hurma::KeyCode::Right:
            //mCamera->moveCamera({cameraOffset, 0, 0});
            break;

        case Hurma::KeyCode::Up:
            //mCamera->moveCamera({0, cameraOffset, 0});
            break;

        case Hurma::KeyCode::Down:
            //mCamera->moveCamera({0, -cameraOffset, 0});
            break;
        }

        return false;
        });
    dispatcher.dispatch<Hurma::WindowResizeEvent>([this](Hurma::WindowResizeEvent& event) {
        // mCamera->setAspectRatio(static_cast<float>(event.getWidth()) / static_cast<float>(event.getHeight()));
        return false;
        });
}

void GameLayer::onImGuiRender()
{
}
