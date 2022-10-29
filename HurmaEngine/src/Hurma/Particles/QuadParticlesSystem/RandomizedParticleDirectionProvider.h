#pragma once
#include "IParticle2DLinearDirectionProvider.h"
#include "glm/gtc/constants.hpp"
#include "Hurma/Utils/RandomUtils.h"
#include "glm/ext/vector_float2.hpp"
#include "Hurma/Core.h"

namespace Hurma
{

    class HURMA_API RandomizedParticleDirectionProvider : public IParticle2DLinearDirectionProvider
    {
    public:
        RandomizedParticleDirectionProvider(size_t particlesNum);

        glm::vec2 getDirection(size_t particleInd) const override;

    private:
        size_t mParticlesNum;
    };

}