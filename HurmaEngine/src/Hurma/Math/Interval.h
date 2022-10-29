#pragma once
#include "IInterval.h"

template<class T>
class Interval : public IInterval<T>
{
public:
    Interval(const T& upperBound, const T& lowerBound)
        : mLowerBound(lowerBound)
        , mUpperBound(upperBound)
    {}

    T getLoweBound() const override
    {
        return mLowerBound;
    }

    T getUpperBound() const override
    {
        return mUpperBound;
    }

    bool isEmpty() const override
    {
        return mLowerBound >= mUpperBound;
    }

    T getLength() const
    {
        return mUpperBound - mLowerBound;
    }

private:
    T mLowerBound;
    T mUpperBound;
};