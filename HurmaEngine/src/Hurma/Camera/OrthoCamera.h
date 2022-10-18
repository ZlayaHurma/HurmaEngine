#pragma once
#include "Camera.h"
#include "glm/ext/matrix_clip_space.hpp"

namespace Hurma
{
    class OrthoCamera : public Camera
    {
    public:
        OrthoCamera(float left, float right, float bottom, float top, const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up)
            : Camera(glm::ortho(left, right, bottom, top), eye, center, up)
        {}
    };
}