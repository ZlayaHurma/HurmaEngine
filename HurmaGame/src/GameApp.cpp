#include "Hurma.h" 
#include "Hurma/Log/Log.h"

class GameApplication : public Hurma::Application
{
 public:
     GameApplication()
     {
        Hurma::Log::logInfo("Hello from the client!");
     }
     ~GameApplication(){}
};

Hurma::Application* Hurma::createApplication()
{
    return new GameApplication();
}