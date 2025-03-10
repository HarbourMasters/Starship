#include "scripting.h"
#include "port/hooks/Events.h"
#include "fox_option.h"

#include "fox_co.h"
#include "hit64.h"
#include "hud.h"
#include "assets.h"
#include "fox_map.h"

#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

ScriptingLayer* ScriptingLayer::Instance = new ScriptingLayer();
sol::state lua;

void ScriptingLayer::Init() {
    lua.open_libraries(sol::lib::base, sol::lib::io, sol::lib::math, sol::lib::table);

    lua["RegisterListener"] = [](EventID eventId, const sol::function& callback, uint32_t priority) {
        return EventSystem::Instance->RegisterListener(eventId, callback, (EventPriority) priority);
    };

    #include "scripts/autobind.gen"

    try
    {
        lua.safe_script_file("scripts/test.lua");
        std::cout << "[CPP S1] Lua File read OK!\n";
    }
    catch (const sol::error& e)
    {
        // Something went wrong with loading this script
        std::cout << std::string(e.what()) << "\n";
        return 0;
    }
}

extern "C" void BindEvent(const char* name, EventID id) {
    lua[name] = id;
}