#include "Hurma.h" 
#include "Hurma/Log/Log.h"
#include "Hurma/ImGui/ImGuiLayer.h"
#include "Hurma/Layer.h"
#include "Hurma/Renderer/RenderCommand.h"
#include "Hurma/Renderer/Renderer.h"
#include "Hurma/Renderer/OpenGLVertexBuffer.h"
#include "Hurma/Renderer/IIndexBuffer.h"
#include "Hurma/Renderer/OpenGLIndexBuffer.h"
#include "Hurma/Renderer/OpenGLVertexArray.h"
#include "Hurma/Renderer/OpenGLShader.h"
#include "glm/matrix.hpp"
#include "Hurma/Camera/Camera.h"
#include "Hurma/Camera/OrthoCamera.h"
#include "Hurma/Events/Event.h"
#include "Hurma/Events/KeyEvent.h"
#include "Hurma/Input.h"

class GameLayer : public Hurma::Layer
{
    
public:

  void onAttach() override 
  {
      using namespace Hurma;

      float triVertices[3 * 7] = {
         -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
          0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
          0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
        };
        std::shared_ptr<Render::IVertexBuffer> triVertexBuffer = 
            std::make_shared<Render::OpenGLVertexBuffer>(triVertices, static_cast<uint32_t>(sizeof(triVertices)));

        triVertexBuffer->setLayout(Render::BufferLayout({
            {ShaderDataType::Float3, "position"}, 
            {ShaderDataType::Float4, "color"}
        }));
        
        unsigned int triIndices[3] = { 0, 1, 2 };
        std::shared_ptr<Render::IIndexBuffer> triIndexBuffer = 
            std::make_shared<Render::OpenGLIndexBuffer>(triIndices, static_cast<uint32_t>(sizeof(triIndices)));
        
        mTriangleVertexArray = std::make_shared<Render::OpenGLVertexArray>();
        mTriangleVertexArray->addVertexBuffer(triVertexBuffer);
        mTriangleVertexArray->setIndexBuffer(triIndexBuffer);

        float rectVertices[4 * 7] = {
         -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
         -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
          0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
          0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        };
        std::shared_ptr<Render::IVertexBuffer> rectVertexBuffer = 
            std::make_shared<Render::OpenGLVertexBuffer>(rectVertices, static_cast<uint32_t>(sizeof(rectVertices)));

        rectVertexBuffer->setLayout(Render::BufferLayout({
            {ShaderDataType::Float3, "position"}, 
            {ShaderDataType::Float4, "color"}
        }));
        
        unsigned int rectIndices[6] = { 0, 1, 2, 0, 2, 3 };
        std::shared_ptr<Render::IIndexBuffer> rectIndexBuffer = 
            std::make_shared<Render::OpenGLIndexBuffer>(rectIndices, static_cast<uint32_t>(sizeof(rectIndices)));
        
        mRectVertexArray = std::make_shared<Render::OpenGLVertexArray>();
        mRectVertexArray->addVertexBuffer(rectVertexBuffer);
        mRectVertexArray->setIndexBuffer(rectIndexBuffer);

        std::string vert = R"(
            #version 330 core

            layout(location = 0) in vec3 aPosition;
            layout(location = 1) in vec4 aColor;

            uniform mat4 uProjMatrix;
            uniform mat4 uViewMatrix;

            out vec3 vPosition;
            out vec4 vColor;

            void main(){
                gl_Position = uProjMatrix * uViewMatrix * vec4(aPosition, 1.0);
                vPosition = aPosition;
                vColor = aColor;
            }
        )";

         std::string frag = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec3 vPosition;
            in vec4 vColor;

            void main(){
              color = vColor;
            }
        )";

        mTriangleShader = std::make_unique<Render::OpenGLShader>(vert, frag);
        mRectShader = std::make_unique<Render::OpenGLShader>(vert, frag);

        mCamera = std::make_shared<Hurma::OrthoCamera>(-2.f, 2.f, -2.f, 2.f, glm::vec3{0.f,0.f,1.f}, glm::vec3{0.f,0.f,0.f}, glm::vec3{0.f,1.f,0.f});
  }

  void onDetach() override 
  {
  }

  void onUpdate(double deltaTimeSec) override 
  {
      using namespace Hurma::Render;

      const static double cameraSpeed = 4;
      double cameraOffset = cameraSpeed * deltaTimeSec; 

      if(Hurma::Input::isKeyPressed(Hurma::KeyCode::Left))
          mCamera->moveCamera({-cameraOffset, 0, 0});
      if(Hurma::Input::isKeyPressed(Hurma::KeyCode::Right))
          mCamera->moveCamera({cameraOffset, 0, 0});
      if(Hurma::Input::isKeyPressed(Hurma::KeyCode::Up))
          mCamera->moveCamera({0, cameraOffset, 0});
      if(Hurma::Input::isKeyPressed(Hurma::KeyCode::Down))
          mCamera->moveCamera({0, -cameraOffset, 0});
      
      RenderCommand::setClearColor({0.1f, 0.1f, 0.1f, 1});
      RenderCommand::clear();
      
      Renderer::beginScene(mCamera);
      {
          Renderer::submit(mRectShader, mRectVertexArray);
          Renderer::submit(mTriangleShader, mTriangleVertexArray);
      }
      Renderer::endScene();

      mLastDeltaTimeSec = deltaTimeSec;
  }

  void onEvent(Hurma::Event& event) override 
  {
      Hurma::EventDispatcher dispatcher(event);
      dispatcher.dispatch<Hurma::KeyPressedEvent>([this](Hurma::KeyPressedEvent& event){

          const static double cameraSpeed = 50.0;
          double cameraOffset = cameraSpeed * mLastDeltaTimeSec; 

          switch(event.getKeyCode()) 
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
  }

  void onImGuiRender() override 
  {
  }

private:
    std::shared_ptr<Hurma::Render::IVertexArray> mTriangleVertexArray;
    std::shared_ptr<Hurma::Render::IVertexArray> mRectVertexArray;
    std::shared_ptr<Hurma::Render::IShader> mTriangleShader;
    std::shared_ptr<Hurma::Render::IShader> mRectShader;
    std::shared_ptr<Hurma::Camera> mCamera;

    double mLastDeltaTimeSec {0};
};

class GameApplication : public Hurma::Application
{
 public:
     GameApplication()
     {
        Hurma::Log::logInfo("Hello from the client!");
        pushLayer(new GameLayer());
     }
     ~GameApplication(){}
};

Hurma::Application* Hurma::createApplication()
{
    return new GameApplication();
}