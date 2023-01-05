#include "Hurma/Application.h"
#include "GameLayer.h"
#include "Hurma/Log/Log.h"
#include "FlappyQuadLayer.h"
#include "Test3DLayer.h"

class GameApplication : public Hurma::Application
{
 public:
     GameApplication()
     {
        Hurma::Log::logInfo("Hello from the client!");
        // pushLayer(new GameLayer());
        pushLayer(new FlappyQuadLayer());
        // pushLayer(new Test3DLayer());
     }
     ~GameApplication(){}
};

Hurma::Application* Hurma::createApplication()
{
    return new GameApplication();
}