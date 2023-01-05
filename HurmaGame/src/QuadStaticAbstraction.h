#pragma once
#include "IQuadCollisionObject.h"
#include "glm/ext/vector_float2.hpp"

class QuadStaticAbstraction : public IQuadCollisionObject 
{

public:
    QuadStaticAbstraction(const glm::vec2& centerPos, float sideLength);

    bool isCollidingWith(ICollisionObject* other) const override;
    const glm::vec2& getQuadPosition() const override;
    float getQuadSideLength() const override;

    void render() const;

private:
    const glm::vec2 mStaticPosition;
    const float mQuadSide;
};