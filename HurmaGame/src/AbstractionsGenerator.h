#pragma once
#include "QuadStaticAbstraction.h"
#include <list>

class AbstractionsGenerator : public ICollisionObject
{
public:
    AbstractionsGenerator(size_t abstractionsNum, float abstractionsSideLength, float abstractionDist, 
        float upperGeneratingBound, float lowerGeneratingBound, const glm::vec2& playerPos);

    void update(double deltaTimeSec, const glm::vec2& playerPos);
    void render() const;
    bool isCollidingWith(ICollisionObject* other) const override;

private:
    float generateYForQuad(bool upper) const;


private:
    const size_t mAbstractionsNum;
    const float mAbstractionsSideLength;
    const float mAbstractionGaps;
    const float mAbstractionsRangeX;

    const float mUpperGeneratingBound;
    const float mLowerGeneratingBound;

    std::list<QuadStaticAbstraction> mUpperAbstractions;
    std::list<QuadStaticAbstraction> mLowerAbstractions;
};