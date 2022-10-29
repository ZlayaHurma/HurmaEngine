#pragma once
#include <stdlib.h>

struct RandomUtils
{
    template<typename T>
    static T rnd(const T& from, const T& to)
    {
        T normalized = static_cast <T> (rand()) / static_cast <T> (RAND_MAX);
        return (1 - normalized) * from + normalized * to;
    }
};