#pragma once
#include "glm/ext/vector_float2.hpp"
#include "Hurma/Physics/ICollisionObject.h"

class IQuadCollisionObject : public ICollisionObject
{
public:
    virtual const glm::vec2& getQuadPosition() const = 0;
    virtual float getQuadSideLength() const = 0;
};