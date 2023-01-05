#pragma once
#include "glm/ext/vector_float3.hpp"

class IPositionable
{
    virtual const glm::vec3& getPosition() const = 0;
};