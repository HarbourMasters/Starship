#pragma once

#if defined(_WIN32) || defined(__CYGWIN__)
    #define HM_API __declspec(dllexport)
#else
    #define HM_API __attribute__((visibility("default")))
#endif

#define MOD_INIT HM_API void ModInit
#define MOD_EXIT HM_API void ModExit