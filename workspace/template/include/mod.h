#pragma once

#if defined(_WIN32) || defined(__CYGWIN__)
    #define HM_API __declspec(dllexport)
#else
    #define HM_API __attribute__((visibility("default")))
#endif

#define MOD_INIT HM_API void ModInit
#define MOD_EXIT HM_API void ModExit

extern void* ScriptGetFunction(const char* module, const char* function);

#define CALL_FUNC(mod, func, ...) ((func##Func)ScriptGetFunction(mod, func##Symbol))(__VA_ARGS__)

// STD-Replacements
#define malloc(size) GameEngine_Malloc(size)
#define free(ptr) GameEngine_Free(ptr)