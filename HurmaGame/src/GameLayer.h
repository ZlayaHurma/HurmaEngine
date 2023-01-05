#pragma once
#include "Hurma/Layer.h"
#include <memory>

namespace Hurma
{
    class Camera;
    class QuadsParticleSystem2D;
    class ITexture;

    namespace Render
    {
        class IVertexArray;
        class IShader;
    }
}

class GameLayer : public Hurma::Layer
{
    
public:
  void onAttach() override;

  void onDetach() override;

  void onUpdate(double deltaTimeSec) override;

  void onEvent(Hurma::Event& event) override;

  void onImGuiRender() override;

private:
    std::shared_ptr<Hurma::Render::IVertexArray> mTriangleVertexArray;
    std::shared_ptr<Hurma::Render::IVertexArray> mRectVertexArray;
    std::shared_ptr<Hurma::Render::IShader> mTriangleShader;
    std::shared_ptr<Hurma::Render::IShader> mRectShader;
    std::shared_ptr<Hurma::Camera> mCamera;
    std::shared_ptr<Hurma::QuadsParticleSystem2D> mParticleSystem;

    std::shared_ptr<Hurma::ITexture> mTexture;
    std::shared_ptr<Hurma::ITexture> mTexture2;

    class PlayerQuad* player;
};