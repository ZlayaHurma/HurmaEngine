#pragma once
#include "PhysicalObject.h"
#include "Hurma/Core.h"

namespace Hurma
{

    class HURMA_API GravityObject : public PhysicalObject
    {
    public:
        GravityObject(const glm::vec3& initialPosition, const glm::vec3& initialVelocity, float objectMass = 1.f, float gravityAcceleration = 9.81f);
        virtual void update(double dt) override;

        float getAcceleration() const;

    private:
        const float mAcceleration;
    };

}