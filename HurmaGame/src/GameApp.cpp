#include "Hurma.h" 

class GameApplication : public Hurma::Application
{
 public:
     GameApplication(){}
     ~GameApplication(){}
};

Hurma::Application* Hurma::createApplication()
{
    return new GameApplication();
}