#pragma once
#include "glm/ext/vector_float2.hpp"
#include "Hurma/Math/Constants.h"
#include "glm/gtc/constants.hpp"
#include "glm/gtx/compatibility.hpp"

namespace Hurma
{

    class ParticleQuad
    {
    public:
        ParticleQuad(glm::vec2 initialPos, float lifetime, float initialSize, float flySpeed, float rotationSpeedRadPerSec,
            const glm::vec2& flyDirection, float initialRoatation, const glm::vec4& color)
            : mRemainingLifetime(lifetime)
            , mCurrSize(initialSize)
            , mInitialSize(initialSize)
            , mFlySpeed(flySpeed)
            , mRotationSpeedRadPerSec(rotationSpeedRadPerSec)
            , mFlyDirection(flyDirection)
            , mPosition(initialPos)
            , mRotationAngle(initialRoatation)
            , mLifetime(lifetime)
            , mColor(color)
        {}

        void update(double deltaTimeSec)
        {
            mRemainingLifetime -= deltaTimeSec;
            if (mRemainingLifetime < Constants::TimeErrorSec)
                return;

            float deltaLegth = deltaTimeSec * mFlySpeed;
            mPosition = mPosition + mFlyDirection * deltaLegth;

            mRotationAngle = mRotationAngle + deltaTimeSec * mRotationSpeedRadPerSec;
            if (mRotationAngle > glm::two_pi<float>())
                mRotationAngle -= glm::two_pi<float>();

            mCurrSize = glm::lerp(0.f, mInitialSize, mRemainingLifetime / mLifetime);
        }

        bool isAlive() const
        {
            return mRemainingLifetime > Constants::TimeErrorSec;
        }

        glm::vec2 getPosition() const { return mPosition; }
        float getRotation() const { return mRotationAngle; }
        float getSize() const { return mCurrSize; }
        glm::vec4 getColor() const { return mColor; }

    private:
        float mRemainingLifetime;
        float mCurrSize;
        glm::vec2 mPosition;
        float mRotationAngle;

        const glm::vec2 mFlyDirection;
        const float mRotationSpeedRadPerSec;
        const float mFlySpeed;
        const float mInitialSize;
        const float mLifetime;
        const glm::vec4 mColor;
    };

}