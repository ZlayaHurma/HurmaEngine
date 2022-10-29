#include "RandomizedParticleDirectionProvider.h"

namespace Hurma
{

    RandomizedParticleDirectionProvider::RandomizedParticleDirectionProvider(size_t particlesNum)
        : mParticlesNum(particlesNum)
    {
    }

    glm::vec2 RandomizedParticleDirectionProvider::getDirection(size_t particleInd) const
    {
        float sectorLength = glm::two_pi<float>() / mParticlesNum;
        float fromAngle = sectorLength * particleInd;
        float toAngle = fromAngle + sectorLength;


        float rndAngleWithinSector = RandomUtils::rnd<float>(fromAngle, toAngle);
        return { cos(rndAngleWithinSector), sin(rndAngleWithinSector) };
    }

}