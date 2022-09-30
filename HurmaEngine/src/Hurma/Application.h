#pragma once
#include "Core.h"

namespace Hurma
{

    class HURMA_API Application 
    {
     public:
        Application();
        ~Application();

        void run();
    };

    Application* createApplication();
}
