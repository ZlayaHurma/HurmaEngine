#include "PlayerQuad.h"
#include "Hurma/Renderer/Renderer.h"

PlayerQuad::PlayerQuad(const glm::vec2& pos, float acceleration)
    : GravityObject({pos, 0.f}, glm::vec3(0.1f, 0.f, 0.f), 1.f, acceleration)
{
}

void PlayerQuad::update(double deltaTimeSec)
{
    GravityObject::update(deltaTimeSec);
}

void PlayerQuad::render() const
{
    glm::vec2 pos = getPosition();
    Hurma::Render::Renderer::draw2DQuad( pos, mPlayerQuadSideLength, 0.f, {1.f, 0.f, 0.f, 1.f} );
}

const glm::vec2& PlayerQuad::getQuadPosition() const
{
    return getPosition();
}

float PlayerQuad::getQuadSideLength() const
{
    return mPlayerQuadSideLength;
}

bool PlayerQuad::isCollidingWith(ICollisionObject* other) const
{
    return false;
}
