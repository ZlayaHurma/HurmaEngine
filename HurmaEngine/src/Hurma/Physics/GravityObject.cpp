#include "GravityObject.h"

namespace Hurma
{

    GravityObject::GravityObject(const glm::vec3& initialPosition, const glm::vec3& initialVelocity, float objectMass /*= 1.f*/, float gravityAcceleration)
        : PhysicalObject(initialPosition, initialVelocity, objectMass)
        , mAcceleration(gravityAcceleration)
    {
    }

    void GravityObject::update(double dt)
    {
        static glm::vec3 gravityForce = {0.f, -mAcceleration, 0.f};
        applyForce(getMass() * gravityForce);

        PhysicalObject::update(dt);
    }

    float GravityObject::getAcceleration() const
    {
        return mAcceleration;
    }

}
