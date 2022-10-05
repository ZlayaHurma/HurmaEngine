#pragma once
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
   //define something for Windows (32-bit and 64-bit, this part is common)
   #ifdef _WIN64
      #define PLATFORM_WINDOWS
   #else
      #error Currently Hurma only supports windows 32 bit
   #endif
#elif __APPLE__
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR
         #error Currently Hurma only supports ios
    #elif TARGET_OS_MACCATALYST
          #error Currently Hurma only supports ios
    #elif TARGET_OS_IPHONE
         #error Currently Hurma only supports ios
    #elif TARGET_OS_MAC
         #error Currently Hurma only supports ios
    #else
    #   error "Unknown Apple platform"
    #endif
#elif __ANDROID__
    #error Currently Hurma only supports android
#elif __linux__
    #error Currently Hurma only supports linux
#elif __unix__ // all unices not caught above
    #error Currently Hurma only supports this
#elif defined(_POSIX_VERSION)
    #error Currently Hurma only supports this
#else
    #error "Unknown compiler"
#endif