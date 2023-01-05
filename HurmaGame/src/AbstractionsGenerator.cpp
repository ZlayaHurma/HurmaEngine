#include "AbstractionsGenerator.h"
#include "Hurma/Math/IntervalF.h"
#include "Hurma/Utils/RandomUtils.h"

AbstractionsGenerator::AbstractionsGenerator(size_t abstractionsNum, float abstractionsSideLength, float abstractionGaps,
    float upperGeneratingBound, float lowerGeneratingBound, const glm::vec2& playerPos)
    : mAbstractionGaps(abstractionGaps)
    , mAbstractionsNum(abstractionsNum)
    , mAbstractionsSideLength(abstractionsSideLength)
    , mAbstractionsRangeX(abstractionsSideLength * abstractionsNum + abstractionGaps * (abstractionsNum - 1))
    , mLowerGeneratingBound(lowerGeneratingBound)
    , mUpperGeneratingBound(upperGeneratingBound)
{
    _ASSERTE(abstractionsNum > 0);

    float abstractionsStartX = playerPos.x - mAbstractionsRangeX * 0.5f;

    for(size_t i = 0; i < abstractionsNum; i++)
    {
        QuadStaticAbstraction upperAbstraction( {i * ( abstractionsSideLength + abstractionGaps ) + abstractionsStartX + abstractionsSideLength * 0.5f, generateYForQuad(true) }, abstractionsSideLength );
        QuadStaticAbstraction lowerAbstraction( {i * ( abstractionsSideLength + abstractionGaps ) + abstractionsStartX + abstractionsSideLength * 0.5f, generateYForQuad(false)}, abstractionsSideLength );
        
        mUpperAbstractions.push_back(upperAbstraction);
        mLowerAbstractions.push_back(lowerAbstraction);
    }
}

void AbstractionsGenerator::update(double deltaTimeSec, const glm::vec2& playerPos)
{
    if(playerPos.x - mAbstractionsRangeX * 0.5 > mUpperAbstractions.front().getQuadPosition().x + mAbstractionsSideLength * 0.5)
    {
        mUpperAbstractions.erase(mUpperAbstractions.begin());
        mLowerAbstractions.erase(mLowerAbstractions.begin());

        float newAbstractionX = mUpperAbstractions.back().getQuadPosition().x + mAbstractionsSideLength + mAbstractionGaps;
        
        QuadStaticAbstraction newUpperAbstraction({newAbstractionX, generateYForQuad(true)}, mAbstractionsSideLength);
        QuadStaticAbstraction newLowerAbstraction({newAbstractionX, generateYForQuad(false)}, mAbstractionsSideLength);
        
        mUpperAbstractions.push_back(newUpperAbstraction);
        mLowerAbstractions.push_back(newLowerAbstraction);
    }
}

void AbstractionsGenerator::render() const
{
    for(const auto& abstraction : mUpperAbstractions)
    {
        abstraction.render();
    }

    for(const auto& abstraction : mLowerAbstractions)
    {
        abstraction.render();
    }
}

bool AbstractionsGenerator::isCollidingWith(ICollisionObject* other) const
{
    for(const auto& abstraction : mUpperAbstractions)
    {
        if(abstraction.isCollidingWith(other))
            return true;
    }

    for(const auto& abstraction : mLowerAbstractions)
    {
        if(abstraction.isCollidingWith(other))
            return true;
    }

    return false;
}

float AbstractionsGenerator::generateYForQuad(bool upper) const
{
    float from;
    float to;

    if(upper)
    {
        from = (mUpperGeneratingBound + mLowerGeneratingBound) * 0.5f + mAbstractionsSideLength * 0.5f;
        to = mUpperGeneratingBound - mAbstractionsSideLength * 0.5f;
    }
    else
    {
        from = mLowerGeneratingBound + mAbstractionsSideLength * 0.5f;
        to = (mUpperGeneratingBound + mLowerGeneratingBound) * 0.5f - mAbstractionsSideLength * 0.5f;
    }

    return RandomUtils::rnd<float>(from, to);
}
