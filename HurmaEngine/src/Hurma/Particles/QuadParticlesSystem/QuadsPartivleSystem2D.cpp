#include <memory>
#include "QuadsPartivleSystem2D.h"
#include "Hurma/Renderer/Renderer.h"
#include "IParticle2DLinearDirectionProvider.h"

namespace Hurma
{

    QuadsPartivleSystem2D::QuadsPartivleSystem2D(std::unique_ptr<IParticle2DLinearDirectionProvider> directionProvider)
        : mDirectionProvider(std::move(directionProvider))
    {
    }

    QuadsPartivleSystem2D::~QuadsPartivleSystem2D()
    {
    }

    void QuadsPartivleSystem2D::update(double deltaTimeSec)
    {
        for (ParticleQuad& quad : mParticleQuads)
        {
            quad.update(deltaTimeSec);
        }
    }

    void QuadsPartivleSystem2D::render() const
    {
        for (const ParticleQuad& quad : mParticleQuads)
        {
            Render::Renderer::draw2DQuad(quad.getPosition(), quad.getSize(), quad.getRotation(), {1,0,0,1});
        }
    }

    void QuadsPartivleSystem2D::applyAtPoint(const glm::vec2& point, const ParticlesTraits& traits)
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
                    0.f
                });
        }
    }

}

