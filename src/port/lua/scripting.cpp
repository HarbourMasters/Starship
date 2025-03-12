#include "scripting.h"
#include "port/hooks/Events.h"
#include "fox_option.h"
#include <spdlog/spdlog.h>

#include "fox_co.h"
#include "hit64.h"
#include "hud.h"
#include "assets.h"
#include "fox_map.h"
#include "global.h"
#include <filesystem>
#include "port/resource/type/ResourceType.h"
#include "port/resource/type/Text.h"

#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

namespace fs = std::filesystem;

ScriptingLayer* ScriptingLayer::Instance = new ScriptingLayer();
sol::state lua;

std::vector<std::pair<EventID, ListenerID>> RegisteredListeners;
std::vector<std::pair<std::string, EventID>> RegisteredEvents;

std::optional<std::string> LoadFromO2R(const std::string& path) {
    auto init = std::make_shared<Ship::ResourceInitData>();
    init->Type = (uint32_t) SF64::ResourceType::Text;
    init->ByteOrder = Ship::Endianness::Native;
    init->Format = RESOURCE_FORMAT_BINARY;
    auto res = static_pointer_cast<SF64::Text>(
        Ship::Context::GetInstance()->GetResourceManager()->LoadResource(path, true, init));

    if (res == nullptr) {
        return std::nullopt;
    }

    return *static_cast<std::string*>(res->GetRawPointer());
}

int ScriptingLayer::Require(lua_State* L) {
    std::string path = sol::stack::get<std::string>(L, 1);

    auto result = LoadFromO2R(path);

    if(!result.has_value()){
        const auto error = "Failed to load " + path;
        SPDLOG_ERROR(error);
        sol::stack::push(L, error);
        return 0;
    }

    const auto& script = result.value();
    luaL_loadbuffer(
        L, script.data(), script.size(), path.c_str());

    return 1;
}

void ScriptingLayer::Init() {
    lua.open_libraries(sol::lib::base, sol::lib::io, sol::lib::math, sol::lib::table);

    lua["RegisterListener"] = [](EventID eventId, const sol::function& callback, uint32_t priority) {
        auto lid = EventSystem::Instance->RegisterListener(eventId, callback, (EventPriority) priority);
        RegisteredListeners.emplace_back(eventId, lid);
        return lid;
    };

    lua["Game"] = lua.create_table();
    lua["Assets"] = lua.create_table();
    lua["Events"] = lua.create_table();

    for (const auto& [name, id] : RegisteredEvents) {
        lua["Events"][name] = id;
    }

    #include "scripts/autobind.gen"

    try {
        // TODO: Decide if we want to load scripts from the game's directory for debugging
        if (!fs::exists("scripts")) {
            return;
        }
        for (const auto& entry : fs::directory_iterator("scripts")) {
            if (entry.path().extension() == ".lua") {
                lua.safe_script_file(entry.path().string());
            }
        }
    } catch (const sol::error& e) {
        SPDLOG_ERROR(std::string(e.what()));
        return;
    }
}

void ScriptingLayer::Clean() {
    for (const auto& [eventId, listenerId] : RegisteredListeners) {
        EventSystem::Instance->UnregisterListener(eventId, listenerId);
    }
    RegisteredListeners.clear();
}

void ScriptingLayer::Reload() {
    this->Clean();
    lua.collect_garbage();
    lua = sol::state();
    this->Init();
}

extern "C" void BindEvent(const char* name, EventID id) {
    RegisteredEvents.emplace_back(name, id);
}