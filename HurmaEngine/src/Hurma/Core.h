#pragma once

#ifdef HURMA_BUILD
    #define HURMA_API __declspec(dllexport)
#else
    #define HURMA_API __declspec(dllimport)
#endif