#include "global.h"
#include "fox_map.h"
#include "fox_option.h"
#include "sf64audio_provisional.h"

extern s32 spectrumAnalyzerMode;
extern bool D_menu_801B9320;
extern s32 D_menu_801B9244;
extern OptionId D_menu_801B9124;
extern s32 D_menu_801B912C;

static s32 showJukebox = 0;
static u32 prevSfx = NA_SE_NONE;
static u32 sfx = NA_SE_NONE;
static s32 sfxId = 0;
static u32 sfxBank = SFX_BANK_PLAYER;
static u32 sfxRange = 0;
static s32 sfxImport = 0;
static int holdTimer = 0;
static u8 sfxFlag = 0;
static u8 sfxFlags[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
static char* flagNames[] = { "F18", "F19", "F20", "F21", "F22", "F23", "STT", "F25", "F26", "SFX" };
static u8 bankSizes[] = { 0x33, 0x85, 0x9C, 0x9C, 0x37 };
static u32 sfxEditMode = 9;
static u32 srcEditMode = 0;
static u32 editMode = 0;
static s32 srcVec[3] = { 0, 0, 0 };
static f32 sfxSource[3] = { 0.0f, 0.0f, 0.0f };

void Jukebox_SelectFlag(u8* flag) {
    if (gControllerPress[gMainController].button & (U_CBUTTONS | D_CBUTTONS | R_CBUTTONS | L_CBUTTONS)) {
        *flag ^= 1;
    }
}

void Jukebox_SelectWrap(u32* option, s32 range) {
    if (gControllerPress[gMainController].button & (U_CBUTTONS | R_CBUTTONS)) {
        (*option)++;
    } else if (gControllerPress[gMainController].button & (D_CBUTTONS | L_CBUTTONS)) {
        (*option)--;
    }
    *option = (*option + range) % range;
}

Jukebox_SelectClamp(s32* option, s32 range, s32 skip) {
    OSContPad* contPress = &gControllerPress[gMainController];
    OSContPad* contHold = &gControllerHold[gMainController];

    if (contHold->button & (U_CBUTTONS | D_CBUTTONS)) {
        holdTimer++;
    } else {
        holdTimer = 0;
    }

    if (((contHold->button & U_CBUTTONS) && (holdTimer > 15)) || (contPress->button & U_CBUTTONS)) {
        (*option)++;
    } else if (((contHold->button & D_CBUTTONS) && (holdTimer > 15)) || (contPress->button & D_CBUTTONS)) {
        (*option)--;
    } else if (contPress->button & L_CBUTTONS) {
        *option -= skip;
    } else if (contPress->button & R_CBUTTONS) {
        *option += skip;
    }
    if (*option < 0) {
        *option = 0;
    } else if (*option >= range) {
        *option = range - 1;
    }
}

void Jukebox_UpdateSource(void) {
    OSContPad* contPress = &gControllerPress[gMainController];
    OSContPad* contHold = &gControllerHold[gMainController];

    if (contPress->button & L_JPAD) {
        srcEditMode--;
    } else if (contPress->button & R_JPAD) {
        srcEditMode++;
    }
    srcEditMode = (srcEditMode + 3) % 3;

    if (contHold->button & (U_CBUTTONS | D_CBUTTONS | L_CBUTTONS | R_CBUTTONS)) {
        holdTimer++;
    } else {
        holdTimer = 0;
    }

    if (((contHold->button & U_CBUTTONS) && (holdTimer > 15)) || (contPress->button & U_CBUTTONS)) {
        sfxSource[srcEditMode] += 100.0f;
    } else if (((contHold->button & D_CBUTTONS) && (holdTimer > 15)) || (contPress->button & D_CBUTTONS)) {
        sfxSource[srcEditMode] -= 100.0f;
    } else if (((contHold->button & R_CBUTTONS) && (holdTimer > 15)) || (contPress->button & R_CBUTTONS)) {
        sfxSource[srcEditMode] += 10.0f;
    } else if (((contHold->button & L_CBUTTONS) && (holdTimer > 15)) || (contPress->button & L_CBUTTONS)) {
        sfxSource[srcEditMode] -= 10.0f;
    }
}

void Jukebox_UpdateSfx(void) {
    s32 i;
    u16 flags = 0;

    if (gControllerPress[gMainController].button & L_JPAD) {
        sfxEditMode--;
    } else if (gControllerPress[gMainController].button & R_JPAD) {
        sfxEditMode++;
    }
    sfxEditMode = (sfxEditMode + 13) % 13;
    switch (sfxEditMode) {
        case 9:
            Jukebox_SelectWrap(&sfxBank, 5);
            break;
        case 10:
            Jukebox_SelectClamp(&sfxId, bankSizes[sfxBank], 0x10);
            break;
        case 11:
            Jukebox_SelectFlag(&sfxFlag);
            break;
        case 12:
            Jukebox_SelectWrap(&sfxRange, 4);
            break;
        case 8:
            Jukebox_SelectClamp(&sfxImport, 0x100, 0x10);
            break;
        default:
            if ((sfxEditMode >= 0) && (sfxEditMode < 8)) {
                Jukebox_SelectFlag(&sfxFlags[sfxEditMode]);
            }
            break;
    }
    for (i = 0; i < 8; i++) {
        flags |= sfxFlags[i] << (i + (i > 5));
    }
    sfx = SFX_PACK(sfxBank, sfxId, sfxRange, sfxImport, (sfxFlag << 27) | (flags << 18));
}

s32 sfxModeX[] = { 95, 104, 113, 122, 131, 140, 149, 158, 180, 0, 22, 43, 60 };
s32 srcModeX[] = { 45, 135, 225 };

void Jukebox_Update(void) {
    s32 i;
    OSContPad* contPress = &gControllerPress[gMainController];
    OSContPad* contHold = &gControllerHold[gMainController];

    if (contPress->button & U_JPAD) {
        editMode--;
    } else if (contPress->button & D_JPAD) {
        editMode++;
    }
    editMode %= 2;
    switch (editMode) {
        case 0:
            Jukebox_UpdateSfx();
            break;
        case 1:
            Jukebox_UpdateSource();
            break;
    }

    if (prevSfx != sfx) {
        AUDIO_PLAY_SFX(NA_SE_CURSOR, gDefaultSfxSource, 4);
        prevSfx = sfx;
    }

    if (contPress->button & A_BUTTON) {
        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 1);
        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 1);
        AUDIO_PLAY_SFX(sfx, sfxSource, 4);
        D_menu_801B9320 = true;
    }

    if (contPress->button & B_BUTTON) {
        if (!D_menu_801B9320) {
            AUDIO_PLAY_SFX(NA_SE_ARWING_CANCEL, gDefaultSfxSource, 4);
            AUDIO_PLAY_BGM(NA_BGM_SELECT);
            gDrawMode = DRAW_NONE;
            D_menu_801B9124 = 1000;
            D_menu_801B912C = 0;
            D_menu_801B9244 = 1;
            return;
        } else {
            AUDIO_PLAY_SFX(NA_SE_CANCEL, gDefaultSfxSource, 4);
            Audio_KillSfxBySource(sfxSource);
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 1);
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 1);
            D_menu_801B9320 = false;
        }
    }

    // Spectrum Analyzer mode selector
    if (contPress->button & Z_TRIG) {
        spectrumAnalyzerMode++;
        if (spectrumAnalyzerMode > 2) {
            spectrumAnalyzerMode = 0;
        }
    }

    /* Draw */

    RCP_SetupDL(&gMasterDisp, SETUPDL_83);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);

    Graphics_Printf("SFX ID: %08X", sfx);
    Graphics_DisplaySmallText(20, 50, 1.0f, 1.0f, D_801619A0);
    Graphics_DisplaySmallText(20, 80, 1.0f, 1.0f, "B ID  X R S    FLAG   IMP");
    Graphics_Printf("%d %02X %d %d %d %d%d%d%d%d%d%d%d %02X", sfxBank, sfxId, sfxFlag, sfxRange, 1, sfxFlags[0],
                    sfxFlags[1], sfxFlags[2], sfxFlags[3], sfxFlags[4], sfxFlags[5], sfxFlags[6], sfxFlags[7],
                    sfxImport);
    Graphics_DisplaySmallText(20, 70, 1.0f, 1.0f, D_801619A0);

    // Graphics_DisplaySmallText(80, 50, 1.0f, 1.0f, hexString);
    for (i = 0; i < 3; i++) {
        Graphics_Printf("%5.0f", sfxSource[i]);
        Graphics_DisplaySmallText(20 + 90 * i, 100, 1.0f, 1.0f, D_801619A0);
    }
    Graphics_DisplaySmallText(45, 110, 1.0f, 1.0f, "X");
    Graphics_DisplaySmallText(135, 110, 1.0f, 1.0f, "Y");
    Graphics_DisplaySmallText(225, 110, 1.0f, 1.0f, "Z");
    switch (editMode) {
        case 0:
            Graphics_DisplaySmallText(20 + sfxModeX[sfxEditMode], 60, 1.0f, 1.0f, "V");
            break;
        case 1:
            Graphics_DisplaySmallText(45 + 90 * srcEditMode, 90, 1.0f, 1.0f, "V");
            break;
    }
}
