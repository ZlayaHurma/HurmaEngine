#pragma once
#include "glm/ext/vector_float2.hpp"
#include "Hurma/Core.h"

namespace Hurma
{

    class HURMA_API IParticle2DLinearDirectionProvider
    {
    public:
        virtual glm::vec2 getDirection(size_t particleInd) const = 0;
    };

}