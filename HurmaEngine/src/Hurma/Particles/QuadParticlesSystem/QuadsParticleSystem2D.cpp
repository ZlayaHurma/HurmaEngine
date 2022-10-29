#include <memory>
#include "QuadsParticleSystem2D.h"
#include "Hurma/Renderer/Renderer.h"
#include "IParticle2DLinearDirectionProvider.h"

namespace Hurma
{

    QuadsParticleSystem2D::QuadsParticleSystem2D(std::unique_ptr<IParticle2DLinearDirectionProvider> directionProvider)
        : mDirectionProvider(std::move(directionProvider))
    {}

    QuadsParticleSystem2D::~QuadsParticleSystem2D()
    {}

    void QuadsParticleSystem2D::update(double deltaTimeSec)
    {
        for (ParticleQuad& quad : mParticleQuads)
        {
            quad.update(deltaTimeSec);
        }

        clearDeadParticles();
    }

    void QuadsParticleSystem2D::clearDeadParticles()
    {
        std::vector<ParticleQuad> aliveParticles;
        for (const ParticleQuad& quad : mParticleQuads)
        {
            if(quad.isAlive())
                aliveParticles.push_back(quad);
        }

        std::swap(aliveParticles, mParticleQuads);
    }

    void QuadsParticleSystem2D::render() const
    {
        for (const ParticleQuad& quad : mParticleQuads)
        {
            Render::Renderer::draw2DQuad(quad.getPosition(), quad.getSize(), quad.getRotation(), quad.getColor());
        }
    }

    void QuadsParticleSystem2D::applyAtPoint(const glm::vec2& point, const ParticlesTraits& traits)
    {
        // Spawn group
        for (size_t groupInd = 0; groupInd < traits.quadsSpawnNum; groupInd++)
        {
            auto quadFlyDirection = mDirectionProvider->getDirection(groupInd);

            mParticleQuads.push_back(
                ParticleQuad 
                {
                    point,
                    traits.quadsLifetimeSec,
                    traits.initialQuadSize,
                    traits.dispersalSpeed,
                    traits.rotationSpeedRadSec,
                    quadFlyDirection,
                    // TODO: provider for initial rotation
                    0.f,
                    traits.groupColor
                });
        }
    }

}

