#pragma once
#include "glm/vec3.hpp"
#include "Hurma/Core.h"
#include "Hurma/Commons/IPositionable.h"

namespace Hurma
{

    class HURMA_API PhysicalObject : public IPositionable
    {
    public:
        PhysicalObject(const glm::vec3& initialPosition, const glm::vec3& initialVelocity, float objectMass = 1.f);

        void applyForce(const glm::vec3& force);
        virtual void update(double dt);
        void setVelocity(const glm::vec3& velocity);

        float getMass() const;
        const glm::vec3& getVelocity() const;
        const glm::vec3& getPosition() const override;

    private:
        #pragma warning(push)
        #pragma warning(disable:4251)
        glm::vec3 mObjectPosition;
        glm::vec3 mObjectVelocity;
        
        const float mObjectMass;

        glm::vec3 mCurrentForce;
        #pragma warning(pop)
    };

}
