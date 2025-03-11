#pragma once

#ifdef __cplusplus
#include <string>

struct lua_State;

class ScriptingLayer {
  public:
    static ScriptingLayer* Instance;

    void Init();
    void Load(std::string file);
    void Clean();
    void Reload();
    static int Require(lua_State* L);
};
#else
void BindEvent(const char* name, uint32_t id);
#endif