#pragma once

class ICollisionObject
{
public:
    virtual bool isCollidingWith(ICollisionObject* other) const = 0;
};