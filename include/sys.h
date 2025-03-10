#ifndef SYS_H
#define SYS_H

#include "PR/xstdio.h"
#include "PR/controller.h"
#include <libultraship.h>
#include "math.h"
#include "libc/math.h"
#include "stdarg.h"
#include "stdbool.h"
#include "stdint.h"
#include "stddef.h"
#include "string.h"
#include "macros.h"
#include "sf64math.h"
#include "gfx.h"
#include "sf64thread.h"
#include "sf64save.h"
#include "buffers.h"

#define UNK_TYPE s32

#ifdef __cplusplus
extern "C" {
#endif

typedef s32 (*CompareFunc)(void*, void*);

s32 Lib_vsPrintf(char* dst, const char* fmt, va_list args);
void Lib_vTable(s32 index, void (**table)(s32, s32), s32 arg0, s32 arg1);
void Lib_QuickSort(u8* first, u32 length, u32 size, CompareFunc cFunc);
void Lib_InitPerspective(Gfx** dList);
void Lib_InitOrtho(Gfx** dList);
void Lib_DmaRead(void* src, void* dst, s32 size);
void Lib_FillScreen(u8 setFill);

void Memory_FreeAll(void);
void* Memory_Allocate(s32);

void Game_Initialize(void);
void Game_Update(void);

extern bool gShowReticles[];
extern bool D_game_800D2870;

extern f32 gNextVsViewScale;
extern f32 gVsViewScale;
extern s32 gPlayerInactive[4];
extern s32 gVsMenuSelection;
extern u8 gShowHud;
extern u16 gNextLevelPhase;
extern u16 gNextLevel;
extern u16 gNextGameState;
extern u16 gLastGameState;
extern u16 gBgColor;
extern u8 gBlurAlpha;
extern u8 gGameStandby;
extern f32 gFovY;
extern f32 gProjectNear;
extern f32 gProjectFar;

#ifdef __cplusplus
}
#endif

typedef enum OptionState {
    OPTION_WAIT,
    OPTION_SETUP,
    OPTION_UPDATE
} OptionState;

#endif
