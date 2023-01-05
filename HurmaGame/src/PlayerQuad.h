#pragma once
#include <memory>
#include "Hurma/Renderer/IShader.h"
#include "Hurma/Physics/GravityObject.h"
#include "IQuadCollisionObject.h"

class PlayerQuad : public Hurma::GravityObject, public IQuadCollisionObject
{
public:
    PlayerQuad(const glm::vec2& pos, float acceleration);

    void update(double deltaTimeSec) override;
    void render() const;

    const glm::vec2& getQuadPosition() const override;
    float getQuadSideLength() const override;
    bool isCollidingWith(ICollisionObject* other) const override;

private:
    const float mPlayerQuadSideLength = 0.1f;

};