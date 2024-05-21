#include "Engine.h"
#include "ui/ImguiUI.h"
#include "StringHelper.h"
#include "libultraship/src/Context.h"
#include "resource/type/ResourceType.h"
#include "resource/importers/AnimFactory.h"
#include "resource/importers/ColPolyFactory.h"
#include "resource/importers/EnvSettingsFactory.h"
#include "resource/importers/GenericArrayFactory.h"
#include "resource/importers/HitboxFactory.h"
#include "resource/importers/LimbFactory.h"
#include "resource/importers/MessageFactory.h"
#include "resource/importers/MessageLookupFactory.h"
#include "resource/importers/ObjectInitFactory.h"
#include "resource/importers/ScriptCommandFactory.h"
#include "resource/importers/ScriptFactory.h"
#include "resource/importers/SkeletonFactory.h"
#include "resource/importers/Vec3fFactory.h"
#include "resource/importers/Vec3sFactory.h"
#include <Fast3D/Fast3dWindow.h>
#include <DisplayListFactory.h>
#include <TextureFactory.h>
#include <MatrixFactory.h>
#include <ArrayFactory.h>
#include <BlobFactory.h>
#include <VertexFactory.h>

#include <Fast3D/gfx_pc.h>
#include <Fast3D/gfx_rendering_api.h>
#include <SDL2/SDL.h>

#include <utility>

extern "C" {
extern uint16_t gFPS;
float gInterpolationStep = 0.0f;
#include <sf64thread.h>
#include <macros.h>
}

GameEngine* GameEngine::Instance;

GameEngine::GameEngine() {
    std::vector<std::string> OTRFiles;
    if (const std::string cube_path = Ship::Context::GetPathRelativeToAppDirectory("starship.otr"); std::filesystem::exists(cube_path)) {
        OTRFiles.push_back(cube_path);
    }
    if (const std::string sm64_otr_path = Ship::Context::GetPathRelativeToAppBundle("sm64.otr"); std::filesystem::exists(sm64_otr_path)) {
        OTRFiles.push_back(sm64_otr_path);
    }
    if (const std::string patches_path = Ship::Context::GetPathRelativeToAppDirectory("mods"); !patches_path.empty() && std::filesystem::exists(patches_path)) {
        if (std::filesystem::is_directory(patches_path)) {
            for (const auto&p: std::filesystem::recursive_directory_iterator(patches_path)) {
                if (StringHelper::IEquals(p.path().extension().string(), ".otr")) {
                    OTRFiles.push_back(p.path().generic_string());
                }
            }
        }
    }

    this->context = Ship::Context::CreateInstance("Starship", "ship", "starship.cfg.json", OTRFiles, {}, 3);

    auto loader = context->GetResourceManager()->GetResourceLoader();
    loader->RegisterResourceFactory(std::make_shared<SF64::ResourceFactoryBinaryAnimV0>(), RESOURCE_FORMAT_BINARY, "Animation", static_cast<uint32_t>(SF64::ResourceType::AnimData), 0);
    loader->RegisterResourceFactory(std::make_shared<SF64::ResourceFactoryBinarySkeletonV0>(), RESOURCE_FORMAT_BINARY, "Skeleton", static_cast<uint32_t>(SF64::ResourceType::Skeleton), 0);
    loader->RegisterResourceFactory(std::make_shared<SF64::ResourceFactoryBinaryLimbV0>(), RESOURCE_FORMAT_BINARY, "Limb", static_cast<uint32_t>(SF64::ResourceType::Limb), 0);
    loader->RegisterResourceFactory(std::make_shared<SF64::ResourceFactoryBinaryMessageV0>(), RESOURCE_FORMAT_BINARY, "Message", static_cast<uint32_t>(SF64::ResourceType::Message), 0);
    loader->RegisterResourceFactory(std::make_shared<SF64::ResourceFactoryBinaryMessageLookupV0>(), RESOURCE_FORMAT_BINARY, "MessageTable", static_cast<uint32_t>(SF64::ResourceType::MessageTable), 0);
    loader->RegisterResourceFactory(std::make_shared<SF64::ResourceFactoryBinaryEnvSettingsV0>(), RESOURCE_FORMAT_BINARY, "EnvSettings", static_cast<uint32_t>(SF64::ResourceType::Environment), 0);
    loader->RegisterResourceFactory(std::make_shared<SF64::ResourceFactoryBinaryObjectInitV0>(), RESOURCE_FORMAT_BINARY, "ObjectInit", static_cast<uint32_t>(SF64::ResourceType::ObjectInit), 0);
    loader->RegisterResourceFactory(std::make_shared<SF64::ResourceFactoryBinaryHitboxV0>(), RESOURCE_FORMAT_BINARY, "Hitbox", static_cast<uint32_t>(SF64::ResourceType::Hitbox), 0);
    loader->RegisterResourceFactory(std::make_shared<SF64::ResourceFactoryBinaryScriptV0>(), RESOURCE_FORMAT_BINARY, "Script", static_cast<uint32_t>(SF64::ResourceType::Script), 0);
    loader->RegisterResourceFactory(std::make_shared<SF64::ResourceFactoryBinaryScriptCMDV0>(), RESOURCE_FORMAT_BINARY, "ScriptCMD", static_cast<uint32_t>(SF64::ResourceType::ScriptCmd), 0);
    loader->RegisterResourceFactory(std::make_shared<SF64::ResourceFactoryBinaryColPolyV0>(), RESOURCE_FORMAT_BINARY, "ColPoly", static_cast<uint32_t>(SF64::ResourceType::ColPoly), 0);
    loader->RegisterResourceFactory(std::make_shared<SF64::ResourceFactoryBinaryVec3fV0>(), RESOURCE_FORMAT_BINARY, "Vec3f", static_cast<uint32_t>(SF64::ResourceType::Vec3f), 0);
    loader->RegisterResourceFactory(std::make_shared<SF64::ResourceFactoryBinaryVec3sV0>(), RESOURCE_FORMAT_BINARY, "Vec3s", static_cast<uint32_t>(SF64::ResourceType::Vec3s), 0);
    loader->RegisterResourceFactory(std::make_shared<SF64::ResourceFactoryBinaryGenericArrayV0>(), RESOURCE_FORMAT_BINARY, "GenericArray", static_cast<uint32_t>(SF64::ResourceType::GenericArray), 0);
    loader->RegisterResourceFactory(std::make_shared<LUS::ResourceFactoryBinaryTextureV0>(), RESOURCE_FORMAT_BINARY, "Texture", static_cast<uint32_t>(LUS::ResourceType::Texture), 0);
    loader->RegisterResourceFactory(std::make_shared<LUS::ResourceFactoryBinaryTextureV1>(), RESOURCE_FORMAT_BINARY, "Texture", static_cast<uint32_t>(LUS::ResourceType::Texture), 1);
    loader->RegisterResourceFactory(std::make_shared<LUS::ResourceFactoryBinaryVertexV0>(), RESOURCE_FORMAT_BINARY, "Vertex", static_cast<uint32_t>(LUS::ResourceType::Vertex), 0);
    loader->RegisterResourceFactory(std::make_shared<LUS::ResourceFactoryBinaryDisplayListV0>(), RESOURCE_FORMAT_BINARY, "DisplayList", static_cast<uint32_t>(LUS::ResourceType::DisplayList), 0);
    loader->RegisterResourceFactory(std::make_shared<LUS::ResourceFactoryBinaryMatrixV0>(), RESOURCE_FORMAT_BINARY, "Matrix", static_cast<uint32_t>(LUS::ResourceType::Matrix), 0);
    loader->RegisterResourceFactory(std::make_shared<LUS::ResourceFactoryBinaryArrayV0>(), RESOURCE_FORMAT_BINARY, "Array", static_cast<uint32_t>(LUS::ResourceType::Array), 0);
    loader->RegisterResourceFactory(std::make_shared<LUS::ResourceFactoryBinaryBlobV0>(), RESOURCE_FORMAT_BINARY, "Blob", static_cast<uint32_t>(LUS::ResourceType::Blob), 0);
}

void GameEngine::Create(){
    const auto instance = Instance = new GameEngine();
    GameUI::SetupGuiElements();
#if defined(__SWITCH__) || defined(__WIIU__)
    CVarRegisterInteger("gControlNav", 1); // always enable controller nav on switch/wii u
#endif
}

void GameEngine::Destroy(){

}

bool ShouldClearTextureCacheAtEndOfFrame = false;

void GameEngine::StartFrame() const{
    using Ship::KbScancode;
    const int32_t dwScancode = this->context->GetWindow()->GetLastScancode();
    this->context->GetWindow()->SetLastScancode(-1);

    switch (dwScancode) {
        case KbScancode::LUS_KB_TAB: {
            // Toggle HD Assets
            CVarSetInteger("gAltAssets", !CVarGetInteger("gAltAssets", 0));
            ShouldClearTextureCacheAtEndOfFrame = true;
            break;
        }
        default: break;
    }
    this->context->GetWindow()->StartFrame();
}

void GameEngine::RunCommands(Gfx* Commands) {
    gfx_run(Commands, {});
    gfx_end_frame();

    if (ShouldClearTextureCacheAtEndOfFrame) {
        gfx_texture_cache_clear();
        ShouldClearTextureCacheAtEndOfFrame = false;
    }
}

void GameEngine::ProcessGfxCommands(Gfx* commands) {
    auto wnd = std::dynamic_pointer_cast<Fast::Fast3dWindow>(Ship::Context::GetInstance()->GetWindow());

    if (wnd == nullptr) {
        return;
    }

    gFPS = 30;
    wnd->SetRendererUCode(UcodeHandlers::ucode_f3dex);
    wnd->SetTargetFps(30);
    wnd->SetMaximumFrameLatency(1);

    RunCommands(commands);
}

extern "C" uint32_t GameEngine_GetSampleRate() {
    auto player = Ship::Context::GetInstance()->GetAudio()->GetAudioPlayer();
    if (player == nullptr) {
        return 0;
    }

    if (!player->IsInitialized()) {
        return 0;
    }

    return player->GetSampleRate();
}

extern "C" uint32_t GameEngine_GetSamplesPerFrame(){
    return SAMPLES_PER_FRAME;
}

// End

extern "C" float GameEngine_GetAspectRatio() {
    return gfx_current_dimensions.aspect_ratio;
}

extern "C" uint32_t GameEngine_GetGameVersion() {
    return 0x00000001;
}

static const char* sOtrSignature = "__OTR__";

extern "C" uint8_t GameEngine_OTRSigCheck(const char* data) {
    if(data == nullptr) {
        return 0;
    }
    return strncmp(data, sOtrSignature, strlen(sOtrSignature)) == 0;
}

extern "C" float __cosf(float angle) {
    return cosf(angle);
}

extern "C" float __sinf(float angle) {
    return sinf(angle);
}

extern "C" float SIN_DEG(float angle) {
    return __sinf(M_DTOR * angle);
}
extern "C" float COS_DEG(float angle) {
    return __cosf(M_DTOR * angle);
}

struct TimedEntry {
    uint64_t duration;
    TimerAction action;
    int32_t* address;
    int32_t value;
    bool active;
};

std::vector<TimedEntry> gTimerTasks;


uint64_t Timer_GetCurrentMillis() {
    return SDL_GetTicks();
}

extern "C" s32 Timer_CreateTask(u64 time, TimerAction action, s32* address, s32 value) {
    const auto millis = Timer_GetCurrentMillis();
    TimedEntry entry = {
        .duration = millis + CYCLES_TO_MSEC_PC(time),
        .action = action,
        .address = address,
        .value = value,
        .active = true,
    };

    gTimerTasks.push_back(entry);

    return gTimerTasks.size() - 1;
}

extern "C" void Timer_Increment(int32_t* address, int32_t value) {
    *address += value;
}

extern "C" void Timer_SetValue(int32_t* address, int32_t value) {
    *address = value;
}

void Timer_CompleteTask(TimedEntry& task) {
    if (task.action != nullptr) {
        task.action(task.address, task.value);
    }
    task.active = false;
}

extern "C" void Timer_Update() {

    if(gTimerTasks.empty()) {
        return;
    }

    const auto millis = Timer_GetCurrentMillis();

    for (auto& task : gTimerTasks) {
        if (task.active && millis >= task.duration) {
            Timer_CompleteTask(task);
        }
    }
}
