#include "QuadStaticAbstraction.h"
#include "glm/ext/vector_float4.hpp"
#include "Hurma/Renderer/Renderer.h"

QuadStaticAbstraction::QuadStaticAbstraction(const glm::vec2& centerPos, float sideLength)
    : mStaticPosition(centerPos)
    , mQuadSide(sideLength)
{
}

bool QuadStaticAbstraction::isCollidingWith(ICollisionObject* other) const
{
    if(IQuadCollisionObject* otherQuad = dynamic_cast<IQuadCollisionObject*>(other))
    {
        auto center1 = mStaticPosition;
        auto side1 = mQuadSide;

        auto center2 = otherQuad->getQuadPosition();
        auto side2 = otherQuad->getQuadSideLength();

        auto quad1LowerX = center1.x - side1 * 0.5;
        auto quad1UpperX = center1.x + side1 * 0.5;

        auto quad2LowerX = center2.x - side2 * 0.5;
        auto quad2UpperX = center2.x + side2 * 0.5;

        bool xOverlap = quad1LowerX < quad2UpperX && quad1UpperX > quad2LowerX;
        if(!xOverlap)
            return false;

        auto quad1LowerY = center1.y - side1 * 0.5;
        auto quad1UpperY = center1.y + side1 * 0.5;
                                   
        auto quad2LowerY = center2.y - side2 * 0.5;
        auto quad2UpperY = center2.y + side2 * 0.5;

        bool yOverlap = quad1LowerY < quad2UpperY && quad1UpperY > quad2LowerY;
        return yOverlap;
    }

    return false;
}

const glm::vec2& QuadStaticAbstraction::getQuadPosition() const
{
    return mStaticPosition;
}

float QuadStaticAbstraction::getQuadSideLength() const
{
    return mQuadSide;
}

void QuadStaticAbstraction::render() const
{
    Hurma::Render::Renderer::draw2DQuad(mStaticPosition, mQuadSide, 0.f, glm::vec4(0.2f, 0.8f, 0.1f, 1.f));
}
