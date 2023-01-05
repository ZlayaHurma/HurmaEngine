#include "PhysicalObject.h"

namespace Hurma
{

    PhysicalObject::PhysicalObject(const glm::vec3& initialPosition, const glm::vec3& initialVelocity, float objectMass)
        : mObjectPosition(initialPosition)
        , mObjectVelocity(initialVelocity)
        , mObjectMass(objectMass)
        , mCurrentForce(0.f)
    {
    }

    void PhysicalObject::applyForce(const glm::vec3& force)
    {
        mCurrentForce += force;
    }

    float PhysicalObject::getMass() const 
    {
        return mObjectMass;
    }

    const glm::vec3& PhysicalObject::getVelocity() const 
    {
        return mObjectVelocity;
    }

    const glm::vec3& PhysicalObject::getPosition() const 
    {
        return mObjectPosition;
    }

    void PhysicalObject::update(double dt)
    {
        glm::vec3 prevVelocity = mObjectVelocity;
        glm::vec3 acceleration = mCurrentForce / mObjectMass;
        mObjectVelocity = prevVelocity + acceleration * static_cast<float>(dt);

        mObjectPosition += (prevVelocity + mObjectVelocity) * 0.5f * static_cast<float>(dt);

        mCurrentForce = glm::vec3(0.f);
    }

    void PhysicalObject::setVelocity(const glm::vec3& velocity)
    {
        mObjectVelocity = velocity;
    }

}