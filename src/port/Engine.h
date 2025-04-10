#pragma once

#define LOAD_ASSET(path) (path == NULL ? NULL : (GameEngine_OTRSigCheck((const char*) path) ? ResourceGetDataByName((const char*) path) : path))
#define LOAD_ASSET_RAW(path) ResourceGetDataByName((const char*) path)

typedef enum {
    SF64_VER_US = 0x94F1D5A7,
    SF64_VER_EU = 0x6EE9ADE7,
    SF64_VER_JP = 0x3728D3E1
} SF64Version;

#ifdef __cplusplus
#include <vector>
#include <SDL2/SDL.h>
#include <Fast3D/interpreter.h>
#include "libultraship/src/Context.h"

#ifndef IDYES
#define IDYES 6
#endif
#ifndef IDNO
#define IDNO 7
#endif

class GameEngine {
  public:
    static GameEngine* Instance;

    std::shared_ptr<Ship::Context> context;

    GameEngine();
    void StartFrame() const;
    static bool GenAssetFile(bool exitOnFail = true);
    static void Create();
    static void HandleAudioThread();
    static void StartAudioFrame();
    static void EndAudioFrame();
    static void AudioInit();
    static void AudioExit();
    static void RunCommands(Gfx* Commands, const std::vector<std::unordered_map<Mtx*, MtxF>>& mtx_replacements);
    static void Destroy();
	static uint32_t GetInterpolationFPS();
	static uint32_t GetInterpolationFrameCount();
    static void ProcessGfxCommands(Gfx* commands);

    static int ShowYesNoBox(const char* title, const char* box);
    static void ShowMessage(const char* title, const char* message, SDL_MessageBoxFlags type = SDL_MESSAGEBOX_ERROR);
    static bool HasVersion(SF64Version ver);
};

Fast::Interpreter* GameEngine_GetInterpreter();
#define memallocn(type, n) (type*) GameEngine_Malloc(sizeof(type) * n)
#define memalloc(type) memallocn(type, 1)

extern "C" {
#else
#include <stdint.h>
#define memalloc(size) GameEngine_Malloc(size)
#endif

void* GameEngine_Malloc(size_t size);
bool GameEngine_HasVersion(SF64Version ver);
void GameEngine_ProcessGfxCommands(Gfx* commands);
float GameEngine_GetAspectRatio();
uint8_t GameEngine_OTRSigCheck(const char* imgData);
uint32_t OTRGetCurrentWidth(void);
uint32_t OTRGetCurrentHeight(void);
float OTRGetHUDAspectRatio();
int32_t OTRConvertHUDXToScreenX(int32_t v);
float OTRGetDimensionFromLeftEdge(float v);
float OTRGetDimensionFromRightEdge(float v);
int16_t OTRGetRectDimensionFromLeftEdge(float v);
int16_t OTRGetRectDimensionFromRightEdge(float v);
float OTRGetDimensionFromLeftEdgeForcedAspect(float v, float aspectRatio);
float OTRGetDimensionFromRightEdgeForcedAspect(float v, float aspectRatio);
int16_t OTRGetRectDimensionFromLeftEdgeForcedAspect(float v, float aspectRatio);
int16_t OTRGetRectDimensionFromRightEdgeForcedAspect(float v, float aspectRatio);
float OTRGetDimensionFromLeftEdgeOverride(float v);
float OTRGetDimensionFromRightEdgeOverride(float v);
int16_t OTRGetRectDimensionFromLeftEdgeOverride(float v);
int16_t OTRGetRectDimensionFromRightEdgeOverride(float v);
uint32_t OTRGetGameRenderWidth();
uint32_t OTRGetGameRenderHeight();
void* GameEngine_Malloc(size_t size);
void GameEngine_GetTextureInfo(const char* path, int32_t* width, int32_t* height, float* scale, bool* custom);
void gDPSetTileSizeInterp(Gfx* pkt, int t, float uls, float ult, float lrs, float lrt);
uint32_t GameEngine_GetInterpolationFrameCount();

#ifdef __cplusplus
}
#endif