#pragma once
#include "PlatformDetector.h"

#define BIT(n) 1 << n

#ifdef PLATFORM_WINDOWS
    #ifdef HURMA_BUILD
        #define HURMA_API __declspec(dllexport)
    #else
        #define HURMA_API __declspec(dllimport)
    #endif
#else
    #error Currently Hurma only supports windows
#endif