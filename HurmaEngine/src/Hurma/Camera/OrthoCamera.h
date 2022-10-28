#pragma once
#include "Camera.h"
#include "glm/ext/matrix_clip_space.hpp"

namespace Hurma
{
    class OrthoCamera : public Camera
    {
    public:
        OrthoCamera(float left, float right, float bottom, float top, float zNear, float zFar, const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up)
            : Camera(glm::ortho(left, right, bottom, top, zNear, zFar), eye, center, up)
            , mLeft(left)
            , mRight(right)
            , mBottom(bottom)
            , mTop(top)
            , mZNear(zNear)
            , mZFar(zFar)
        {}

        CameraProjType getProjType() const override 
        {
            return CameraProjType::Ortho;
        }

        void setAspectRatio(float aspectRatio) override 
        {
            mProjMatrix = glm::ortho(mLeft * aspectRatio, mRight * aspectRatio, mBottom, mTop, mZNear, mZFar);
        }

    private:
        float mLeft;
        float mRight;
        float mBottom;
        float mTop;
        float mZNear;
        float mZFar;
    };
}