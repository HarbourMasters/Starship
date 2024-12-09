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

#include "resource/importers/audio/AudioTableFactory.h"
#include "resource/importers/audio/BookFactory.h"
#include "resource/importers/audio/DrumFactory.h"
#include "resource/importers/audio/EnvelopeFactory.h"
#include "resource/importers/audio/InstrumentFactory.h"
#include "resource/importers/audio/LoopFactory.h"
#include "resource/importers/audio/SampleFactory.h"
#include "resource/importers/audio/SoundFontFactory.h"

#include "port/interpolation/FrameInterpolation.h"
#include <Fast3D/Fast3dWindow.h>
#include <DisplayListFactory.h>
#include <TextureFactory.h>
#include <MatrixFactory.h>
#include <BlobFactory.h>
#include <VertexFactory.h>
#include "audio/GameAudio.h"
#include "port/patches/DisplayListPatch.h"
// #include "sf64audio_provisional.h"

#include <Fast3D/gfx_pc.h>
#include <Fast3D/gfx_rendering_api.h>
#include <SDL2/SDL.h>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

// extern "C" AudioBufferParameters gAudioBufferParams;

#include <utility>

extern "C" {
float gInterpolationStep = 0.0f;
#include <sf64thread.h>
#include <macros.h>
void AudioThread_CreateNextAudioBuffer(int16_t* samples, uint32_t num_samples);
}

GameEngine* GameEngine::Instance;
static GamePool MemoryPool = { .chunk = 1024 * 512, .cursor = 0, .length = 0, .memory = nullptr };

GameEngine::GameEngine() {
    std::vector<std::string> OTRFiles;
    if (const std::string cube_path = Ship::Context::GetPathRelativeToAppDirectory("starship.otr");
        std::filesystem::exists(cube_path)) {
        OTRFiles.push_back(cube_path);
    }
    if (const std::string sm64_otr_path = Ship::Context::GetPathRelativeToAppDirectory("sf64.otr");
        std::filesystem::exists(sm64_otr_path)) {
        OTRFiles.push_back(sm64_otr_path);
    }
    if (const std::string patches_path = Ship::Context::GetPathRelativeToAppDirectory("mods");
        !patches_path.empty() && std::filesystem::exists(patches_path)) {
        if (std::filesystem::is_directory(patches_path)) {
            for (const auto& p : std::filesystem::recursive_directory_iterator(patches_path)) {
                const auto ext = p.path().extension().string();
                if (StringHelper::IEquals(ext, ".otr") || StringHelper::IEquals(ext, ".o2r")) {
                    OTRFiles.push_back(p.path().generic_string());
                }
            }
        }
    }

    this->context =
        Ship::Context::CreateInstance("Starship", "ship", "starship.cfg.json", OTRFiles, {}, 3, { 44100, 1024*2, 2480*2 });

    Ship::Context::GetInstance()->GetLogger()->set_level((spdlog::level::level_enum)CVarGetInteger("gDeveloperTools.LogLevel", 1));
    Ship::Context::GetInstance()->GetLogger()->set_pattern("[%H:%M:%S.%e] [%s:%#] [%l] %v");

    auto loader = context->GetResourceManager()->GetResourceLoader();
    loader->RegisterResourceFactory(std::make_shared<SF64::ResourceFactoryBinaryAnimV0>(), RESOURCE_FORMAT_BINARY,
                                    "Animation", static_cast<uint32_t>(SF64::ResourceType::AnimData), 0);
    loader->RegisterResourceFactory(std::make_shared<SF64::ResourceFactoryBinarySkeletonV0>(), RESOURCE_FORMAT_BINARY,
                                    "Skeleton", static_cast<uint32_t>(SF64::ResourceType::Skeleton), 0);
    loader->RegisterResourceFactory(std::make_shared<SF64::ResourceFactoryBinaryLimbV0>(), RESOURCE_FORMAT_BINARY,
                                    "Limb", static_cast<uint32_t>(SF64::ResourceType::Limb), 0);
    loader->RegisterResourceFactory(std::make_shared<SF64::ResourceFactoryBinaryMessageV0>(), RESOURCE_FORMAT_BINARY,
                                    "Message", static_cast<uint32_t>(SF64::ResourceType::Message), 0);
    loader->RegisterResourceFactory(std::make_shared<SF64::ResourceFactoryBinaryMessageLookupV0>(),
                                    RESOURCE_FORMAT_BINARY, "MessageTable",
                                    static_cast<uint32_t>(SF64::ResourceType::MessageTable), 0);
    loader->RegisterResourceFactory(std::make_shared<SF64::ResourceFactoryBinaryEnvSettingsV0>(),
                                    RESOURCE_FORMAT_BINARY, "EnvSettings",
                                    static_cast<uint32_t>(SF64::ResourceType::Environment), 0);
    loader->RegisterResourceFactory(std::make_shared<SF64::ResourceFactoryBinaryObjectInitV0>(), RESOURCE_FORMAT_BINARY,
                                    "ObjectInit", static_cast<uint32_t>(SF64::ResourceType::ObjectInit), 0);
    loader->RegisterResourceFactory(std::make_shared<SF64::ResourceFactoryBinaryHitboxV0>(), RESOURCE_FORMAT_BINARY,
                                    "Hitbox", static_cast<uint32_t>(SF64::ResourceType::Hitbox), 0);
    loader->RegisterResourceFactory(std::make_shared<SF64::ResourceFactoryBinaryScriptV0>(), RESOURCE_FORMAT_BINARY,
                                    "Script", static_cast<uint32_t>(SF64::ResourceType::Script), 0);
    loader->RegisterResourceFactory(std::make_shared<SF64::ResourceFactoryBinaryScriptCMDV0>(), RESOURCE_FORMAT_BINARY,
                                    "ScriptCMD", static_cast<uint32_t>(SF64::ResourceType::ScriptCmd), 0);
    loader->RegisterResourceFactory(std::make_shared<SF64::ResourceFactoryBinaryColPolyV0>(), RESOURCE_FORMAT_BINARY,
                                    "ColPoly", static_cast<uint32_t>(SF64::ResourceType::ColPoly), 0);
    loader->RegisterResourceFactory(std::make_shared<SF64::ResourceFactoryBinaryVec3fV0>(), RESOURCE_FORMAT_BINARY,
                                    "Vec3f", static_cast<uint32_t>(SF64::ResourceType::Vec3f), 0);
    loader->RegisterResourceFactory(std::make_shared<SF64::ResourceFactoryBinaryVec3sV0>(), RESOURCE_FORMAT_BINARY,
                                    "Vec3s", static_cast<uint32_t>(SF64::ResourceType::Vec3s), 0);
    loader->RegisterResourceFactory(std::make_shared<SF64::ResourceFactoryBinaryGenericArrayV0>(),
                                    RESOURCE_FORMAT_BINARY, "GenericArray",
                                    static_cast<uint32_t>(SF64::ResourceType::GenericArray), 0);
    loader->RegisterResourceFactory(std::make_shared<LUS::ResourceFactoryBinaryTextureV0>(), RESOURCE_FORMAT_BINARY,
                                    "Texture", static_cast<uint32_t>(LUS::ResourceType::Texture), 0);
    loader->RegisterResourceFactory(std::make_shared<LUS::ResourceFactoryBinaryTextureV1>(), RESOURCE_FORMAT_BINARY,
                                    "Texture", static_cast<uint32_t>(LUS::ResourceType::Texture), 1);

    loader->RegisterResourceFactory(std::make_shared<LUS::ResourceFactoryBinaryVertexV0>(), RESOURCE_FORMAT_BINARY,
                                    "Vertex", static_cast<uint32_t>(LUS::ResourceType::Vertex), 0);
    loader->RegisterResourceFactory(std::make_shared<LUS::ResourceFactoryXMLVertexV0>(), RESOURCE_FORMAT_XML,
                                    "Vertex", static_cast<uint32_t>(LUS::ResourceType::Vertex), 0);

    loader->RegisterResourceFactory(std::make_shared<LUS::ResourceFactoryBinaryDisplayListV0>(), RESOURCE_FORMAT_BINARY,
                                    "DisplayList", static_cast<uint32_t>(LUS::ResourceType::DisplayList), 0);
    loader->RegisterResourceFactory(std::make_shared<LUS::ResourceFactoryXMLDisplayListV0>(), RESOURCE_FORMAT_XML,
                                    "DisplayList", static_cast<uint32_t>(LUS::ResourceType::DisplayList), 0);

    loader->RegisterResourceFactory(std::make_shared<LUS::ResourceFactoryBinaryMatrixV0>(), RESOURCE_FORMAT_BINARY,
                                    "Matrix", static_cast<uint32_t>(LUS::ResourceType::Matrix), 0);

    loader->RegisterResourceFactory(std::make_shared<LUS::ResourceFactoryBinaryBlobV0>(), RESOURCE_FORMAT_BINARY,
                                    "Blob", static_cast<uint32_t>(LUS::ResourceType::Blob), 0);

    loader->RegisterResourceFactory(std::make_shared<SF64::ResourceFactoryBinaryAudioTableV0>(), RESOURCE_FORMAT_BINARY,
                                    "AudioTable", static_cast<uint32_t>(SF64::ResourceType::AudioTable), 0);

    loader->RegisterResourceFactory(std::make_shared<SF64::ResourceFactoryBinaryAdpcmBookV0>(), RESOURCE_FORMAT_BINARY,
                                    "AdpcmBook", static_cast<uint32_t>(SF64::ResourceType::AdpcmBook), 0);

    loader->RegisterResourceFactory(std::make_shared<SF64::ResourceFactoryBinaryDrumV0>(), RESOURCE_FORMAT_BINARY,
                                    "Drum", static_cast<uint32_t>(SF64::ResourceType::Drum), 0);

    loader->RegisterResourceFactory(std::make_shared<SF64::ResourceFactoryBinaryEnvelopeV0>(), RESOURCE_FORMAT_BINARY,
                                    "Envelope", static_cast<uint32_t>(SF64::ResourceType::Envelope), 0);

    loader->RegisterResourceFactory(std::make_shared<SF64::ResourceFactoryBinaryInstrumentV0>(), RESOURCE_FORMAT_BINARY,
                                    "Instrument", static_cast<uint32_t>(SF64::ResourceType::Instrument), 0);

    loader->RegisterResourceFactory(std::make_shared<SF64::ResourceFactoryBinaryAdpcmLoopV0>(), RESOURCE_FORMAT_BINARY,
                                    "AdpcmLoop", static_cast<uint32_t>(SF64::ResourceType::AdpcmLoop), 0);

    loader->RegisterResourceFactory(std::make_shared<SF64::ResourceFactoryBinarySampleV1>(), RESOURCE_FORMAT_BINARY,
                                    "Sample", static_cast<uint32_t>(SF64::ResourceType::Sample), 1);
    loader->RegisterResourceFactory(std::make_shared<SF64::ResourceFactoryBinarySampleV2>(), RESOURCE_FORMAT_BINARY,
                                    "Sample", static_cast<uint32_t>(SF64::ResourceType::Sample), 2);

    loader->RegisterResourceFactory(std::make_shared<SF64::ResourceFactoryBinarySoundFontV0>(), RESOURCE_FORMAT_BINARY,
                                    "SoundFont", static_cast<uint32_t>(SF64::ResourceType::SoundFont), 0);
}

void GameEngine::Create() {
    const auto instance = Instance = new GameEngine();
    instance->AudioInit();
    DisplayListPatch::Run();
    GameUI::SetupGuiElements();
#if defined(__SWITCH__) || defined(__WIIU__)
    CVarRegisterInteger("gControlNav", 1); // always enable controller nav on switch/wii u
#endif
}

void GameEngine::Destroy() {
    AudioExit();
    free(MemoryPool.memory);
}

bool ShouldClearTextureCacheAtEndOfFrame = false;

void GameEngine::StartFrame() const {
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
        default:
            break;
    }
    this->context->GetWindow()->StartFrame();
}

#if 1
// Values for 44100 hz
#define SAMPLES_HIGH 752
#define SAMPLES_LOW 720
#else
// Values for 32000 hz
#define SAMPLES_HIGH 560
#define SAMPLES_LOW 544

#endif

#define NUM_AUDIO_CHANNELS 2

extern "C" u16 audBuffer = 0;
#include <sf64audio_provisional.h>

extern "C" volatile s32 gAudioTaskCountQ;
int frames = 0;
extern "C" int countermin = 0;

extern "C" unsigned short samples_high = SAMPLES_HIGH;
extern "C" unsigned short samples_low = SAMPLES_LOW;

void GameEngine::HandleAudioThread() {
#ifdef PIPE_DEBUG
    std::ofstream outfile("audio.bin", std::ios::binary | std::ios::app);
#endif
    while (audio.running) {
        {
            std::unique_lock<std::mutex> Lock(audio.mutex);
            while (!audio.processing && audio.running) {
                audio.cv_to_thread.wait(Lock);
            }
            if (!audio.running) {
                break;
            }
        }

        // gVIsPerFrame = 2;

#define AUDIO_FRAMES_PER_UPDATE (gVIsPerFrame > 0 ? gVIsPerFrame : 1)

        std::unique_lock<std::mutex> Lock(audio.mutex);
        int samples_left = AudioPlayerBuffered();
        u32 num_audio_samples = samples_left < AudioPlayerGetDesiredBuffered()
                                    ? (((samples_high ) ) )
                                    : (((samples_low)) );

        frames++;

        if (frames > 60) {
            countermin++;
        }

        s16 audio_buffer[SAMPLES_HIGH * NUM_AUDIO_CHANNELS * 3] = { 0 };
        for (int i = 0; i < AUDIO_FRAMES_PER_UPDATE; i++) {
            AudioThread_CreateNextAudioBuffer(audio_buffer + i * (num_audio_samples * NUM_AUDIO_CHANNELS),
                                              num_audio_samples);
        }
#ifdef PIPE_DEBUG
        if (outfile.is_open()) {
            outfile.write(reinterpret_cast<char*>(audio_buffer),
                          num_audio_samples * (sizeof(int16_t) * NUM_AUDIO_CHANNELS * AUDIO_FRAMES_PER_UPDATE));
        }
#endif
        AudioPlayerPlayFrame((u8*) audio_buffer,
                             num_audio_samples * (sizeof(int16_t) * NUM_AUDIO_CHANNELS * AUDIO_FRAMES_PER_UPDATE));
        audio.processing = false;
        audio.cv_from_thread.notify_one();
    }
#ifdef PIPE_DEBUG
    outfile.close();
#endif
}

void GameEngine::StartAudioFrame() {
    {
        std::unique_lock<std::mutex> Lock(audio.mutex);
        audio.processing = true;
    }
    audio.cv_to_thread.notify_one();
}

void GameEngine::EndAudioFrame() {
    {
        std::unique_lock<std::mutex> Lock(audio.mutex);
        while (audio.processing) {
            audio.cv_from_thread.wait(Lock);
        }
    }
}

void GameEngine::AudioInit() {
    if (!audio.running) {
        audio.running = true;
        audio.thread = std::thread(HandleAudioThread);
    }
}

void GameEngine::AudioExit() {
    {
        std::unique_lock lock(audio.mutex);
        audio.running = false;
    }
    audio.cv_to_thread.notify_all();
    // Wait until the audio thread quit
    audio.thread.join();
}

void GameEngine::RunCommands(Gfx* Commands, const std::vector<std::unordered_map<Mtx*, MtxF>>& mtx_replacements) {
    for (const auto& m : mtx_replacements) {
        gfx_run(Commands, m);
        gfx_end_frame();
    }

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

    wnd->EnableSRGBMode();
    wnd->SetRendererUCode(UcodeHandlers::ucode_f3dex);

    std::vector<std::unordered_map<Mtx*, MtxF>> mtx_replacements;
    int target_fps = CVarGetInteger("gInterpolationFPS", 20);
    static int last_fps;
    static int last_update_rate;
    static int time;
    int fps = target_fps;
    int original_fps = 60 / gVIsPerFrame;

    if (target_fps == 20 || original_fps > target_fps) {
        fps = original_fps;
    }

    if (last_fps != fps || last_update_rate != gVIsPerFrame) {
        time = 0;
    }

    // time_base = fps * original_fps (one second)
    int next_original_frame = fps;

    while (time + original_fps <= next_original_frame) {
        time += original_fps;
        if (time != next_original_frame) {
            mtx_replacements.push_back(FrameInterpolation_Interpolate((float) time / next_original_frame));
        } else {
            mtx_replacements.emplace_back();
        }
    }

    time -= fps;

    int threshold = CVarGetInteger("gExtraLatencyThreshold", 80);

    if (wnd != nullptr) {
        wnd->SetTargetFps(fps);
        wnd->SetMaximumFrameLatency(threshold > 0 && target_fps >= threshold ? 2 : 1);
    }

    // When the gfx debugger is active, only run with the final mtx
    if (GfxDebuggerIsDebugging()) {
        mtx_replacements.clear();
        mtx_replacements.emplace_back();
    }

    RunCommands(commands, mtx_replacements);

    last_fps = fps;
    last_update_rate = gVIsPerFrame;
}

uint32_t GameEngine::GetInterpolationFPS() {
    if (Ship::Context::GetInstance()->GetWindow()->GetWindowBackend() == Ship::WindowBackend::FAST3D_DXGI_DX11) {
        return CVarGetInteger("gInterpolationFPS", 20);
    }

    if (CVarGetInteger("gMatchRefreshRate", 0)) {
        return Ship::Context::GetInstance()->GetWindow()->GetCurrentRefreshRate();
    }

    return std::min<uint32_t>(Ship::Context::GetInstance()->GetWindow()->GetCurrentRefreshRate(),
                              CVarGetInteger("gInterpolationFPS", 20));
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

extern "C" uint32_t GameEngine_GetSamplesPerFrame() {
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
    if (data == nullptr) {
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

    if (gTimerTasks.empty()) {
        return;
    }

    const auto millis = Timer_GetCurrentMillis();

    for (auto& task : gTimerTasks) {
        if (task.active && millis >= task.duration) {
            Timer_CompleteTask(task);
        }
    }
}

// Gets the width of the main ImGui window
extern "C" uint32_t OTRGetCurrentWidth() {
    return GameEngine::Instance->context->GetWindow()->GetWidth();
}

// Gets the height of the main ImGui window
extern "C" uint32_t OTRGetCurrentHeight() {
    return GameEngine::Instance->context->GetWindow()->GetHeight();
}

extern "C" float OTRGetAspectRatio() {
    return gfx_current_dimensions.aspect_ratio;
}

extern "C" float OTRGetDimensionFromLeftEdge(float v) {
    return (gfx_native_dimensions.width / 2 - gfx_native_dimensions.height / 2 * OTRGetAspectRatio() + (v));
}

extern "C" float OTRGetDimensionFromRightEdge(float v) {
    return (gfx_native_dimensions.width / 2 + gfx_native_dimensions.height / 2 * OTRGetAspectRatio() -
            (gfx_native_dimensions.width - v));
}

// Gets the width of the current render target area
extern "C" uint32_t OTRGetGameRenderWidth() {
    return gfx_current_dimensions.width;
}

// Gets the height of the current render target area
extern "C" uint32_t OTRGetGameRenderHeight() {
    return gfx_current_dimensions.height;
}

extern "C" int16_t OTRGetRectDimensionFromLeftEdge(float v) {
    return ((int) floorf(OTRGetDimensionFromLeftEdge(v)));
}

extern "C" int16_t OTRGetRectDimensionFromRightEdge(float v) {
    return ((int) ceilf(OTRGetDimensionFromRightEdge(v)));
}

extern "C" int32_t OTRConvertHUDXToScreenX(int32_t v) {
    float gameAspectRatio = gfx_current_dimensions.aspect_ratio;
    int32_t gameHeight = gfx_current_dimensions.height;
    int32_t gameWidth = gfx_current_dimensions.width;
    float hudAspectRatio = 4.0f / 3.0f;
    int32_t hudHeight = gameHeight;
    int32_t hudWidth = hudHeight * hudAspectRatio;
    float hudScreenRatio = (hudWidth / 320.0f);
    float hudCoord = v * hudScreenRatio;
    float gameOffset = (gameWidth - hudWidth) / 2;
    float gameCoord = hudCoord + gameOffset;
    float gameScreenRatio = (320.0f / gameWidth);
    float screenScaledCoord = gameCoord * gameScreenRatio;
    int32_t screenScaledCoordInt = screenScaledCoord;
    return screenScaledCoordInt;
}

extern "C" void* GameEngine_Malloc(size_t size) {
    // This is really wrong
    return malloc(size);
    // TODO: Kenix please take a look at this, i think it works but you are better at this

    const auto chunk = MemoryPool.chunk;

    if (size == 0) {
        return nullptr;
    }

    if (MemoryPool.cursor + size < MemoryPool.length) {
        const auto res = static_cast<uint8_t*>(MemoryPool.memory) + MemoryPool.cursor;
        MemoryPool.cursor += size;
        // SPDLOG_INFO("Allocating {} into memory pool", size);
        return res;
    }

    MemoryPool.length += chunk;
    MemoryPool.memory =
        MemoryPool.memory == nullptr ? malloc(MemoryPool.length) : realloc(MemoryPool.memory, MemoryPool.length);
    memset(static_cast<uint8_t*>(MemoryPool.memory) + MemoryPool.length, 0, MemoryPool.length - chunk);
    SPDLOG_INFO("Memory pool resized from {} to {}", MemoryPool.length - chunk, MemoryPool.length);
    return GameEngine_Malloc(size);
}

extern "C" float GetWindowWidth() {
    return Ship::Context::GetInstance()->GetWindow()->GetWidth();
}

extern "C" float GetWindowHeight() {
    return Ship::Context::GetInstance()->GetWindow()->GetHeight();
}