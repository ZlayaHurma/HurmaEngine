#pragma once
#include "glm/matrix.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "Hurma/Core.h"

namespace Hurma
{

    enum class CameraProjType 
    {
        Projection,
        Ortho
    };

    class Camera 
    {

    public:
        Camera(const glm::mat4& projMatrix, const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up) 
            : mProjMatrix(projMatrix)
            , mViewMatrix(1.0f)
            , mEye(eye)
            , mCenter(center)
            , mUp(up)
        {
            recomputeViewMatrix();
        }

        virtual CameraProjType getProjType() const = 0;
        virtual void setAspectRatio(float aspectRatio) = 0;

        virtual void zoom(float factor) = 0;
    
        inline const glm::mat4& getProjMatrix() const { return mProjMatrix; }
        inline const glm::mat4& getViewMatrix() const { return mViewMatrix; }

        inline const glm::vec3& getEye() { return mEye; }
        inline const glm::vec3& getCenter() { return mCenter; }
    
        inline void setEye(const glm::vec3& newEye) { mEye = newEye; recomputeViewMatrix(); }
        inline void setCenter(const glm::vec3& newCenter) { mCenter = newCenter; recomputeViewMatrix(); }
        inline void setUp(const glm::vec3& newUp) { mUp = newUp; recomputeViewMatrix(); }

        void moveCamera(const glm::vec3& worldVec)
        {
            mEye += worldVec;
            mCenter += worldVec;
            recomputeViewMatrix();
        }

        void rotateCamera(const glm::vec2& vec)
        {
            glm::vec3 eyeCenter = mCenter - mEye;
            float eyeCenterLength = glm::length(eyeCenter);
            float upAngle = atan(vec.y / eyeCenterLength);
            float sideAngle = atan(vec.x / eyeCenterLength);

            glm::vec3 verticalRotationVec = glm::cross(mUp, eyeCenter);
            glm::vec3 horizontalRotationVec = mUp;

            glm::mat4 rotation = glm::rotate(glm::mat4(1.f), upAngle, verticalRotationVec) * glm::rotate(glm::mat4(1.f), sideAngle, horizontalRotationVec);
            mEye = rotation * glm::vec4{ mEye, 1.f };
            mUp = rotation * glm::vec4{ mUp, 0.f };

            recomputeViewMatrix();
        }
    
    private:
        void recomputeViewMatrix() { mViewMatrix = glm::lookAt(mEye, mCenter, mUp); } 
    
    protected:
        #pragma warning(push)
        #pragma warning(disable:4251)
        glm::mat4 mProjMatrix;
        glm::mat4 mViewMatrix;
    
        glm::vec3 mUp;
        glm::vec3 mEye;
        glm::vec3 mCenter;
        #pragma warning(pop)
    };

}