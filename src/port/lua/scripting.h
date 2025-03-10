#pragma once

#ifdef __cplusplus
#include <string>

class ScriptingLayer {
  public:
    static ScriptingLayer* Instance;

    void Init();
    void Load(std::string file);
};
#else
void BindEvent(const char* name, uint32_t id);
#endif