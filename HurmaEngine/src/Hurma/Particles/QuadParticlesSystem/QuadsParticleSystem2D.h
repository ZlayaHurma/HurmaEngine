#pragma once
#include "glm/ext/vector_float2.hpp"
#include "glm/gtc/constants.hpp"
#include "Hurma/Utils/RandomUtils.h"
#include "glm/gtx/compatibility.hpp"
#include <vector>
#include "ParticleQuad.h"
#include "Hurma/Core.h"

namespace Hurma
{
    class IParticle2DLinearDirectionProvider;

    struct HURMA_API ParticlesTraits
    {
        size_t quadsSpawnNum {};

        float initialQuadSize {};
        float quadsLifetimeSec {};
        float dispersalSpeed {};
        float rotationSpeedRadSec {};
        glm::vec4 groupColor {};
    };

    class HURMA_API QuadsParticleSystem2D
    {
    public:
        QuadsParticleSystem2D(std::unique_ptr<IParticle2DLinearDirectionProvider> directionProvider);
        ~QuadsParticleSystem2D();

        void update(double deltaTimeMs);
        void render() const;

        void applyAtPoint(const glm::vec2& point, const ParticlesTraits& traits);

    private:
        void clearDeadParticles();

    private:
        std::vector<ParticleQuad> mParticleQuads;
        std::unique_ptr<IParticle2DLinearDirectionProvider> mDirectionProvider;
    };

}