#pragma once

template<class T>
class IInterval
{
public:
    virtual T getLoweBound() const = 0;
    virtual T getUpperBound() const = 0;
    bool isEmpty() const = 0;
};