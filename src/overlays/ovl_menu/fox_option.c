/*
 * File: fox_option.c
 * System: Option
 * Description: Starfox Option Menu Handler
 */

#include "mods.h"
#include "prevent_bss_reordering.h"
#include "global.h"
#include "fox_option.h"
#include "assets/ast_font.h"
#include "assets/ast_font_3d.h"
#include "assets/ast_option.h"
#include "assets/ast_vs_menu.h"
#include "assets/ast_map.h"

extern s32 D_menu_801B81A8[][3];
extern Gfx D_menu_801B4A40[];
extern Gfx D_menu_801B5E78[];
extern Gfx D_menu_801B61E0[];
extern Gfx D_menu_801B6548[];
extern Gfx D_menu_801B4D70[];
extern Gfx D_menu_801B5B10[];
extern Gfx D_menu_801B5440[];
extern Gfx D_menu_801B50D8[];
extern Gfx D_menu_801B5E78[];
extern Gfx D_menu_801B57A8[];
extern f32 D_menu_801CD818[];

s32 D_menu_801B9090;
s32 D_menu_801B9094;
s32 D_menu_801B9098;    // gap
s32 D_menu_801B90A0[3]; // gap
s32 D_menu_801B90B0[3]; // gap
f32 D_menu_801B90C0[3]; // gap
f32 D_menu_801B90D0[3]; // gap
f32 D_menu_801B90E0[3]; // gap
f32 D_menu_801B90F0[3]; // gap
f32 D_menu_801B9100[3]; // gap
f32 D_menu_801B9110[3];
f32 D_menu_801B911C;
f32 D_menu_801B9120;
OptionId D_menu_801B9124;
s32 D_menu_801B9128;
s32 D_menu_801B912C;
s32 D_menu_801B9130;
s32 D_menu_801B9134;
s32 D_menu_801B9138;
s32 D_menu_801B913C;
s32 D_menu_801B9140[3];
s32 D_menu_801B914C;
u8 D_menu_801B9150[3][2];
s32 D_menu_801B9158;
UnkStruct_D_menu_801B9250 D_menu_801B9160[3];
s32 D_menu_801B9178;
s32 D_menu_801B917C;
UnkStruct_D_menu_801B9250 D_menu_801B9180; // gap
UnkStruct_D_menu_801B9250 D_menu_801B9188;
UnkStruct_D_menu_801B9250 D_menu_801B9190;
UnkStruct_D_menu_801B9250 D_menu_801B9198;
s32 D_menu_801B91A0;
s32 D_menu_801B91A4;
s32 D_menu_801B91A8;
s32 D_menu_801B91AC;
s32 D_menu_801B91B0;
s32 D_menu_801B91B4;
s32 D_menu_801B91B8;
s32 D_menu_801B91BC;
s32 D_menu_801B91C0;
s32 D_menu_801B91C4;
s32 D_menu_801B91C8;
s32 D_menu_801B91CC;
s32 D_menu_801B91D0;
f32 D_menu_801B91D4;
f32 D_menu_801B91D8;
f32 D_menu_801B91DC;
f32 D_menu_801B91E0;
f32 D_menu_801B91E4;
f32 D_menu_801B91E8;
f32 D_menu_801B91EC;
s32 D_menu_801B91F0;
f32 D_menu_801B91F4;
f32 D_menu_801B91F8;
f32 D_menu_801B91FC;
f32 D_menu_801B9200;
f32 D_menu_801B9204;
f32 D_menu_801B9208;
f32 D_menu_801B920C;
f32 D_menu_801B9210;
s32 D_menu_801B9214;
f32 D_menu_801B9218;
f32 D_menu_801B921C;
f32 D_menu_801B9220;
f32 D_menu_801B9224;
f32 D_menu_801B9228;
s32 D_menu_801B922C;
s32 D_menu_801B9230;
s32 D_menu_801B9234;
s32 D_menu_801B9238;
s32 D_menu_801B923C;
s32 D_menu_801B9240;
s32 D_menu_801B9244;
s32 D_menu_801B9248;
u8 D_menu_801B924C;
UnkStruct_D_menu_801B9250 D_menu_801B9250;
UnkStruct_D_menu_801B9250 D_menu_801B9258;
UnkStruct_D_menu_801B9250 D_menu_801B9260;
UnkStruct_D_menu_801B9250 D_menu_801B9268;
f32 D_menu_801B9270[5];
s32 D_menu_801B9284;
s32 D_menu_801B9288; // gap
UnkStruct_D_menu_801B9250 D_menu_801B9290;
f32 D_menu_801B9298[32];
s32 spectrumAnalizerMode;
s32 D_menu_801B931C;
bool D_menu_801B9320; // MusicPlaying status in the expert sound options
extern s32 BSS_PAD_0;
s32 D_menu_801B9330[2];
s32 D_menu_801B933C;
s32 D_menu_801B9340; // gap
s32 D_menu_801B9348[4];
f32 D_menu_801B9358[4];
f32 D_menu_801B9368;
s32 D_menu_801B936C;
f32 D_menu_801B9370;
s32 D_menu_801B9374;
f32 D_menu_801B9378;
s32 D_menu_801B937C;
UnkStruct_D_menu_801B9250 D_menu_801B9380[4];
UnkStruct_D_menu_801B9250 D_menu_801B93A0[4];
u8 D_menu_801B93C4;
extern s32 BSS_PAD_1;
s32 D_menu_801B93D0;
s32 D_menu_801B93D4;
s32 D_menu_801B93D8;
s32 D_menu_801B93DC;
s32 D_menu_801B93E0;
s32 D_menu_801B93E4;
s32 D_menu_801B93E8;
s32 D_menu_801B93EC;
f32 D_menu_801B93F0;
f32 D_menu_801B93F4;
f32 D_menu_801B93F8; // gap
UnkStruct_D_menu_801B9250 D_menu_801B9400;
UnkStruct_D_menu_801B9250 D_menu_801B9408;

#include "prevent_bss_reordering2.h"
struct BssPad0 {
    int x;
};
struct BssPad1 {
    int x;
};
// struct BssPad2 {int x;};
// struct BssPad3 {int x;};
// struct BssPad4 {int x;};
extern s32 BSS_PAD_2;

static f32 sOptionCardPosY[] = { 60.0f, 36.0f, 12.0f, -12.0f, -36.0f, -60.0f };           // D_menu_801AE570
static f32 sOptionCardTextPosX[] = { 124.0f, 118.0f, 145.0f, 125.0f, 133.0f, 118.0f };    // D_menu_801AE588
static f32 sOptionCardTextPosY[] = { 54.0f, 78.0f, 103.0f, 126.0f, 151.0f, 175.0f };      // D_menu_801AE5A0
static f32 sOptionCardCurTextPosX[] = { 124.0f, 118.0f, 145.0f, 125.0f, 133.0f, 118.0f }; // D_menu_801AE5B8
static f32 sOptionCardCurTextPosY[] = { 54.0f, 78.0f, 103.0f, 126.0f, 151.0f, 175.0f };   // D_menu_801AE5D0
static f32 D_menu_801AE5E8[] = { 124.0f, 125.0f };
static f32 D_menu_801AE5F0[] = { 54.0f, 55.0f };
static f32 D_menu_801AE5F8[] = { 133.0f, 125.0f };
static f32 D_menu_801AE600[] = { 151.0f, 151.0f };
static f32 D_menu_801AE608[] = { 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f };
static f32 D_menu_801AE620[] = { 1.9f, 2.4f, 0.9f, 1.9f, 1.8f, 2.4f };

// D_menu_801AE638
static OptionEntry sOptionCardList[] = {
    {
        { 0, 0, D_OPT_8003B50, 0, 72, 12, 126.0f, 46.0f, 1.0f, 1.0f, 20, 0, 75, 255 },
        { 0.0f, 30.0f, -130.0f, 0.2f, 0.11f },
        { -40.0f, 27.0f, 80.0f },
        1,
        1,
    },
    {
        { 0, 0, D_OPT_8003EB0, 0, 80, 12, 126.0f, 184.0f, 1.0f, 1.0f, 20, 0, 75, 255 },
        { 0.0f, 18.0f, -130.0f, 0.2f, 0.11f },
        { -40.0f, 16.0f, 80.0f },
        1,
        1,
    },
    {
        { 0, 0, D_OPT_8004270, 0, 32, 10, 126.0f, 184.0f, 1.0f, 1.0f, 20, 0, 75, 255 },
        { 0.0f, 6.0f, -130.0f, 0.2f, 0.11f },
        { -40.0f, 6.0f, 80.0f },
        1,
        1,
    },
    {
        { 0, 0, D_OPT_80043B0, 0, 64, 12, 110.0f, 91.0f, 1.0f, 1.0f, 20, 0, 75, 255 },
        { 0.0f, -6.0f, -130.0f, 0.2f, 0.11f },
        { -40.0f, -5.0f, 80.0f },
        1,
        1,
    },
    {
        { 0, 0, D_OPT_80046B0, 0, 64, 10, 110.0f, 116.0f, 1.0f, 1.0f, 20, 0, 75, 255 },
        { 0.0f, -18.0f, -130.0f, 0.2f, 0.11f },
        { -40.0f, -16.0f, 80.0f },
        1,
        1,
    },
    {
        { 0, 0, D_OPT_8004930, 0, 80, 10, 126.0f, 184.0f, 1.0f, 1.0f, 20, 0, 75, 255 },
        { 0.0f, -30.0f, -130.0f, 0.2f, 0.11f },
        { -40.0f, -27.0f, 80.0f },
        1,
        1,
    },
};

// D_menu_801AE878
static OptionEntry sOptionVSCardList[] = {
    {
        { 0, 0, D_OPT_8005010, 0, 96, 13, 110.0f, 91.0f, 1.0f, 1.0f, 20, 0, 75, 255 },
        { 0.0f, 11.0f, -130.0f, 0.2f, 0.11f },
        { -40.0f, 11.0f, 80.0f },
        1,
        1,
    },
    {
        { 0, 0, D_OPT_80054F0, 0, 96, 10, 110.0f, 116.0f, 1.0f, 1.0f, 20, 0, 75, 255 },
        { 0.0f, 0.0f, -130.0f, 0.2f, 0.11f },
        { -40.0f, 0.0f, 80.0f },
        1,
        1,
    },
    {
        { 0, 0, D_OPT_8005910, 0, 96, 10, 110.0f, 138.0f, 1.0f, 1.0f, 20, 0, 75, 255 },
        { 0.0f, -11.0f, -130.0f, 0.2f, 0.11f },
        { -40.0f, -11.0f, 80.0f },
        1,
        1,
    },
};
static u8 D_menu_801AE998[] = { SOUNDMODE_STEREO, SOUNDMODE_MONO, SOUNDMODE_HEADSET };

static u8 D_menu_801AE99C[] = { 0, 1, 2 };

static f32 D_menu_801AE9A0[4] = { 62.0f, 222.0f, 75.0f, 235.0f };

static f32 D_menu_801AE9B0[4] = { 43.0f, 43.0f, 46.0f, 46.0f };

static OptionTexture D_menu_801AE9C0[4] = {
    { 2, 0, D_OPT_80143B0, D_OPT_80147B0, 32, 32, 56.0f, 175.0f, 1.0f, 1.0f, 255, 255, 255, 255 },
    { 2, 0, D_OPT_80143B0, D_OPT_80147B0, 32, 32, 216.0f, 175.0f, 1.0f, 1.0f, 255, 255, 255, 255 },
    { 1, 0, D_OPT_80039D0, D_OPT_8003A50, 16, 16, 69.0f, 178.0f, 1.0f, 1.0f, 255, 255, 255, 255 },
    { 1, 0, D_OPT_80039D0, D_OPT_8003A50, 16, 16, 229.0f, 178.0f, 1.0f, 1.0f, 255, 255, 255, 255 },
};

static OptionTexture D_menu_801AEAA0[3] = {
    { 3, 0, D_OPT_8013990, 0, 104, 10, 151.0f, 135.0f, 1.05f, 1.0f, 255, 255, 255, 255 },
    { 3, 0, D_OPT_8013990, 0, 104, 10, 151.0f, 161.0f, 1.05f, 1.0f, 255, 255, 255, 255 },
    { 3, 0, D_OPT_8013990, 0, 104, 10, 151.0f, 188.0f, 1.05f, 1.0f, 255, 255, 255, 255 },
};

static OptionTexture D_menu_801AEB48[3] = {
    { 3, 0, D_OPT_80141B0, 0, 16, 16, 245.0f, 132.0f, 1.0f, 1.0f, 255, 255, 255, 255 },
    { 3, 0, D_OPT_80141B0, 0, 16, 16, 245.0f, 158.0f, 1.0f, 1.0f, 255, 255, 255, 255 },
    { 3, 0, D_OPT_80141B0, 0, 16, 16, 245.0f, 185.0f, 1.0f, 1.0f, 255, 255, 255, 255 },
};

static Vtx D_menu_801AEBF0[] = {
    { 1, 1, 0, 0, 0, 0, 255, 255, 255, 255 },
    { -1, 1, 0, 0, 0, 0, 255, 255, 255, 255 },
    { -1, 0, 0, 0, 0, 0, 255, 255, 255, 255 },
    { 1, 0, 0, 0, 0, 0, 255, 255, 255, 255 },
};

static Gfx D_menu_801AEC30[] = {
    gsSPVertex(D_menu_801AEBF0, 4, 0),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsSPEndDisplayList(),
};

static Vtx D_menu_801AEC48[] = {
    { 1, 0, 0, 0, 0, 0, 255, 255, 255, 255 },
    { -1, 0, 0, 0, 0, 0, 255, 255, 255, 255 },
    { -1, -1, 0, 0, 0, 0, 255, 255, 255, 255 },
    { 1, -1, 0, 0, 0, 0, 255, 255, 255, 255 },
};

static Gfx D_menu_801AEC88[] = {
    gsSPVertex(D_menu_801AEC48, 4, 0),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsSPEndDisplayList(),
};

static Vtx D_menu_801AECA0[] = {
    { 1, 1, 0, 0, 0, 0, 255, 255, 255, 255 },
    { -1, 1, 0, 0, 0, 0, 255, 255, 255, 255 },
    { -1, -1, 0, 0, 0, 0, 255, 255, 255, 255 },
    { 1, -1, 0, 0, 0, 0, 255, 255, 255, 255 },
};

static Gfx D_menu_801AECE0[] = {
    gsSPVertex(D_menu_801AECA0, 4, 0),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsSPEndDisplayList(),
};

static u8* D_menu_801AECF8[10] = {
    D_5009F60, D_500A050, D_500A140, D_500A230, D_500A320, D_500A410, D_500A500, D_500A5F0, D_500A6E0, D_500A7D0,
};
static f32 D_menu_801AED20[2] = { 255.0f, 255.0f };

// TF is this? seems unused
static s32 D_menu_801AED28[] = {
    /* EE73E8 801AED28 00000038 */ 56,
    /* EE73EC 801AED2C 00000043 */ 67,
    /* EE73F0 801AED30 0000004E */ 78,
    /* EE73F4 801AED34 00000059 */ 89,
    /* EE73F8 801AED38 0000005B */ 91,
};

static s32 D_menu_801AED3C[4] = { 0, 0, 0, 0 };

static UnkStruct_D_menu_801AED4C D_menu_801AED4C[24] = {
    { 9, 0, 0 },  { 0, 12, 0 }, { 12, 4, 0 }, { 4, 10, 0 }, { 10, 2, 0 }, { 6, 4, 0 },   { 7, 2, 0 }, { 3, 2, 0 },
    { 2, 14, 0 }, { 5, 6, 1 },  { 6, 13, 1 }, { 13, 7, 1 }, { 4, 7, 1 },  { 12, 13, 1 }, { 8, 7, 1 }, { 9, 5, 2 },
    { 5, 11, 2 }, { 11, 8, 2 }, { 8, 3, 2 },  { 3, 1, 2 },  { 7, 1, 2 },  { 1, 14, 2 },  { 0, 6, 3 }, { 4, 3, 4 },
};

static Gfx* D_menu_801AEE6C[16] = {
    D_MAP_6060610,   D_MAP_601DE80,   D_MAP_604B750,   D_MAP_601F6B0,   D_MAP_601C0D0,   D_MAP_601C960,
    D_menu_801B5E78, D_menu_801B61E0, D_menu_801B6548, D_menu_801B4D70, D_menu_801B5B10, D_menu_801B5440,
    D_menu_801B50D8, D_MAP_604DB10,   D_menu_801B57A8, D_menu_801B57A8,
};

static char* D_menu_801AEEAC[] = {
    "ME", "A6", "BO", "SZ", "SX", "SY", "KA", "MA", "ZO", "CO", "TI", "AQ", "FO", "SO", "VE", "VE",
};

static s32 PAD_menu_801AEEEC = 0;

static Vtx D_menu_801AEEF0[] = {
    { -11, -11, 0, 0, 0, 255, 0, 0, 0, 0 },
    { 11, -11, 0, 0, 255, 255, 0, 0, 0, 0 },
    { 11, 11, 0, 0, 255, 0, 0, 0, 0, 0 },
    { -11, 11, 0, 0, 0, 0, 0, 0, 0, 0 },
};

static Gfx D_menu_801AEF30[] = {
    gsSPVertex(D_menu_801AEEF0, 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSPEndDisplayList(),
};

static s32 PAD_menu_801AEF50[] = { 0, 0, 0 };

static char D_menu_801AEF5C[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.";

static f32 D_menu_801AEF84[] = { 24.0f, 0.0f, -24.0f };
static f32 D_menu_801AEF90[] = { 111.0f, 112.0f, 121.0f };
static f32 D_menu_801AEF9C[] = { 89.0f, 115.0f, 139.0f };

void Option_Setup(void) {
    bool enableExpertModes;
    bool playedExpertMode;
    s32 i;

    D_80137E78 = 2;

    sOptionCardList[0].unk_00.unk_08 = D_OPT_8003B50;
    sOptionCardList[0].unk_00.unk_10 = 72;
    sOptionCardList[0].unk_00.unk_14 = 12;
    sOptionCardList[4].unk_00.unk_08 = D_OPT_80046B0;
    sOptionCardList[4].unk_00.unk_10 = 64;
    sOptionCardList[4].unk_00.unk_14 = 10;

    for (i = 0; i < OPTION_COUNT; i++) {
        sOptionCardCurTextPosX[i] = sOptionCardTextPosX[i];
        sOptionCardCurTextPosY[i] = sOptionCardTextPosY[i];
    }

    enableExpertModes = true;
    for (i = 0; i < 16; i++) {
        if (i == SAVE_SLOT_VENOM_1) {
            continue;
        }
        if (!(gSaveFile.save.data.planet[i].normalMedal & 1)) {
            if (CVarGetInteger("gLevelSelector", 0) || CVarGetInteger("gSfxJukebox", 0)) {
                enableExpertModes = true;
            } else {
                enableExpertModes = false;
            }
            break;
        }
    }

    D_menu_801B91C8 = enableExpertModes;
    gFillScreenRed = 0;
    gFillScreenGreen = 0;
    gFillScreenBlue = 0;
    gFillScreenAlpha = 0;

    gBlurAlpha = 255;

    gBgColor = 0;

    D_menu_801B91A4 = 0;
    if ((D_game_80161A34 == 7) && (gCurrentLevel == LEVEL_TRAINING)) {
        D_game_80161A34 = 0;
        D_menu_801B91A4 = 1;
    }

    D_menu_801B91A8 = 0;
    D_menu_801B91AC = 0;
    D_menu_801B91B0 = 0;
    playedExpertMode = gExpertMode;
    gExpertMode = false;

    gGameFrameCount = 0;
    D_menu_801B8284 = 0;
    D_menu_801B9178 = 0;
    D_menu_801B917C = 0;

    D_menu_801B9124 = OPTION_MAIN;

    if ((D_game_80161A34 == 5) || (D_game_80161A34 == 8)) {
        if (D_game_80161A34 == 8) {
            D_ctx_80177B90[gCurrentPlanet] = PLANET_VENOM;
            if (D_play_800D3180[LEVEL_VENOM_ANDROSS] == 1) {
                gSaveFile.save.data.planet[SAVE_SLOT_VENOM_1].played = 1;
                if (playedExpertMode) {
                    gSaveFile.save.data.planet[SAVE_SLOT_VENOM_1].expertClear = 1;
                } else {
                    gSaveFile.save.data.planet[SAVE_SLOT_VENOM_1].normalClear = 1;
                }
                Save_Write();
            } else if (D_play_800D3180[LEVEL_VENOM_ANDROSS] == 2) {
                D_ctx_80177BB0[gCurrentPlanet] = 1;
                gSaveFile.save.data.planet[SAVE_SLOT_VENOM_2].played = 1;
                if (playedExpertMode) {
                    gSaveFile.save.data.planet[SAVE_SLOT_VENOM_2].expertClear = 1;
                    gSaveFile.save.data.planet[SAVE_SLOT_VENOM_2].expertMedal = 1;
                } else {
                    gSaveFile.save.data.planet[SAVE_SLOT_VENOM_2].normalClear = 1;
                    gSaveFile.save.data.planet[SAVE_SLOT_VENOM_2].normalMedal = 1;
                }
                Save_Write();
            }
        }

        Title_80188010();
        D_menu_801B9094 = Option_8019C8C4();

        if (D_menu_801B9094 != -1) {
            D_menu_801B9124 = 200;
        } else {
            D_menu_801B9124 = 300;
        }
    } else {
        if (D_game_800D2870 != 0) {
            D_menu_801B91A4 = 2;
            D_menu_801B91A8 = D_ctx_801778AC;
            for (i = 0; i < OPTION_COUNT; i++) {
                if (i == 2) {
                    continue;
                }
                sOptionCardList[i].unk_38.unk_0C = 0.01f;
                sOptionCardList[i].unk_38.unk_10 = 0.21f;
                sOptionCardList[i].unk_38.unk_04 = sOptionCardPosY[i];
                sOptionCardList[i].unk_38.unk_00 = 0.0f;
                sOptionCardList[i].unk_38.unk_08 = 0.0f;
                sOptionCardList[i].unk_5C = 0;

                sOptionCardList[i].unk_00.unk_20 = 0.01f;
                sOptionCardList[i].unk_00.unk_24 = 1.0f;
                sOptionCardList[i].unk_00.unk_18 = 158.0f;
                sOptionCardList[i].unk_00.unk_1C = sOptionCardCurTextPosY[i];
                sOptionCardList[i].unk_58 = 0;
            }
            sOptionCardList[2].unk_38.unk_00 = 0.0f;
            sOptionCardList[2].unk_38.unk_08 = 0.0f;
            sOptionCardList[2].unk_38.unk_04 = 90.0f;
            sOptionCardList[2].unk_38.unk_0C = 0.4f;
            sOptionCardList[2].unk_38.unk_10 = 0.21f;
            sOptionCardList[2].unk_5C = 1;
            sOptionCardList[2].unk_00.unk_20 = 1.0f;
            sOptionCardList[2].unk_00.unk_24 = 1.0f;
            sOptionCardList[2].unk_00.unk_18 = 145.0f;
            sOptionCardList[2].unk_00.unk_1C = 25.0f;
            sOptionCardList[2].unk_58 = 1;

            D_menu_801B9124 = OPTION_VERSUS;
        } else {
            D_menu_801B9124 = OPTION_MAIN;
        }
    }

    D_menu_801B912C = 0;
    D_menu_801B9134 = 0;
    D_menu_801B913C = 0;

    gOptionMenuStatus = OPTION_UPDATE;

    Memory_FreeAll();

    D_ctx_80178420 = 320.0f;
    D_ctx_80178424 = 240.0f;

    func_play_800A5D6C();

    gCsCamEyeX = 0.0f;
    gCsCamEyeY = 0.0f;
    gCsCamEyeZ = 10.0f;
    gCsCamAtX = 0.0f;
    gCsCamAtY = 0.0f;
    gCsCamAtZ = 0.0f;

    D_menu_801B9224 = -80.0f;
    D_menu_801B9228 = 0.0f;

    D_menu_801B922C = 225;
    D_menu_801B9230 = 225;
    D_menu_801B9234 = 225;
    D_menu_801B9238 = 30;
    D_menu_801B923C = 30;
    D_menu_801B9240 = 30;

    D_menu_801B91F8 = 0.1f;
    D_menu_801B91F4 = -130.0f;
    D_menu_801B91FC = 0.0f;
    D_menu_801B9200 = 0.0f;

    D_menu_801B91EC = 0;
    D_menu_801B9244 = 0;
    D_menu_801B9248 = 0;
    AUDIO_PLAY_BGM(SEQ_ID_MENU);
}

void Option_Init(void) {
    if (D_menu_801B9178 > 0) {
        D_menu_801B9178--;
    }
    if (D_menu_801B917C > 0) {
        D_menu_801B917C--;
    }

    switch (gOptionMenuStatus) {
        case OPTION_WAIT:
            if (gNextGameStateTimer == 0) {
                gOptionMenuStatus = OPTION_SETUP;
                Audio_SetAudioSpec(0, 23);
            }
            break;

        case OPTION_SETUP:
            gDrawMode = DRAW_NONE;
            Option_Setup();
            break;

        case OPTION_UPDATE:
            gDrawMode = DRAW_OPTION;
            Option_UpdateEntry();
            break;
    }
    gGameFrameCount++;
}

void Option_UpdateEntry(void) {
    switch (D_menu_801B9124) {
        case OPTION_MAIN:
            Option_MainMenuUpdate();
            break;

        case OPTION_MAP:
            Option_MapUpdate();
            break;

        case OPTION_TRAINING:
            Option_TrainingUpdate();
            break;

        case OPTION_VERSUS:
            Option_VersusUpdate();
            break;

        case OPTION_RANKING:
            Option_RankingUpdate();
            break;

        case OPTION_SOUND:
            Option_SoundUpdate();
            break;

        case OPTION_DATA:
            Option_DataUpdate();
            break;

        case OPTION_EXPERT_SOUND:
            Option_ExpertSoundUpdate();
            break;

        case OPTION_VERSUS_STAGE:
            Option_VersusStageUpdate();
            break;

        case OPTION_POINT_MATCH:
        case OPTION_BR_MATCH:
        case OPTION_TT_MATCH:
            Option_VersusMenuUpdate();
            break;

        case OPTION_NAME:
            Option_8019CAE0();
            break;

        case OPTION_SCORE:
            Option_8019DD44();
            break;

        case OPTION_INVOICE:
            Option_InvoiceUpdate();
            break;
    }

    if (D_menu_801B91BC != 0) {
        D_menu_801B91FC += 3.8f;
        D_menu_801B9200 += 4.2f;
    }
}

void Option_DrawEntry(void) {
    switch (D_menu_801B9124) {
        case OPTION_MAIN:
            Option_MainMenuDraw();
            break;

        case OPTION_VERSUS:
            Option_VersusDraw();
            break;

        case OPTION_RANKING:
            Option_RankingDraw();
            break;

        case OPTION_SOUND:
            Option_SoundDraw();
            break;

        case OPTION_EXPERT_SOUND:
            Option_ExpertSoundDraw();
            break;

        case OPTION_DATA:
            Option_DataDraw();
            break;

        case OPTION_VERSUS_STAGE:
            Option_VersusStageDraw();
            break;

        case OPTION_POINT_MATCH:
        case OPTION_BR_MATCH:
        case OPTION_TT_MATCH:
            Option_VersusMenuDraw();
            break;

        case OPTION_NAME:
            Option_8019D118();
            break;

        case OPTION_SCORE:
            Option_8019DF64();
            break;

        case OPTION_INVOICE:
            Option_InvoiceDraw();
            break;
    }

    if (D_menu_801B8280 != 0) {
        Option_8019BDF0();
        func_fade_80084688(2, D_menu_801B8284);
        Matrix_Pop(&gGfxMatrix);
    }
}

void Option_InitEntry(void) {
    gBlurAlpha = 255;
    D_menu_801B912C = 0;

    switch (D_menu_801B9124) {
        case OPTION_MAP:
            gDrawMode = DRAW_NONE;
            break;

        case OPTION_POINT_MATCH:
        case OPTION_BR_MATCH:
        case OPTION_TT_MATCH:
            Option_VersusMenuInit();
            break;

        case OPTION_VERSUS_STAGE:
            Option_VersusStageInit();
            break;

        case OPTION_RANKING:
            Option_RankingInit();
            break;

        case OPTION_SOUND:
            Option_SoundInit();
            break;

        case OPTION_EXPERT_SOUND:
            Option_ExpertSoundInit();
            break;

        case OPTION_DATA:
            Option_DataInit();
            break;
    }
}

void Option_80192598(void) {
    s32 i;

    D_menu_801B93E8 = 0;
    D_menu_801B93EC = 0;

    for (i = 0; i < (96 * 96); i++) {
        // Planet Textures
        D_menu_801BB810[i] = 106;
        D_menu_801BDC10[i] = 84;
        D_menu_801C0010[i] = 75;
        D_menu_801C2410[i] = 81;
        D_menu_801C4810[i] = 55;
        D_menu_801C6C10[i] = 82;
        D_menu_801C9010[i] = 68;
        D_menu_801CB410[i] = 52;
        D_menu_801B9410[i] = 0;
    }

    for (i = 0; i < 9; i++) {
        D_menu_801CD818[i] = 0.0f;
        Map_801A07E8(D_menu_801B68B0[i], SEGMENTED_TO_VIRTUAL(D_menu_801B68D4[i]), &D_menu_801CD818[i]);
    }
}

void Option_80192738(void) {
    if (D_menu_801B93E8 == 5) {
        Map_801A07E8(D_menu_801B68B0[8], SEGMENTED_TO_VIRTUAL(D_menu_801B68D4[8]), &D_menu_801CD818[8]);
        D_menu_801B93E8 = 0;
    } else {
        D_menu_801B93E8++;
    }

    Map_801A07E8(D_menu_801B68B0[D_menu_801B93EC * 2], SEGMENTED_TO_VIRTUAL(D_menu_801B68D4[D_menu_801B93EC * 2]),
                 &D_menu_801CD818[D_menu_801B93EC * 2]);

    Map_801A07E8(D_menu_801B68B0[(D_menu_801B93EC * 2) + 1],
                 SEGMENTED_TO_VIRTUAL(D_menu_801B68D4[(D_menu_801B93EC * 2) + 1]),
                 &D_menu_801CD818[(D_menu_801B93EC * 2) + 1]);

    D_menu_801B93EC++;
    if (D_menu_801B93EC >= 4) {
        D_menu_801B93EC = 0;
    }
}

void Option_MapUpdate(void) {
    if (gFillScreenAlpha == 255) {
        D_ctx_80178410 = 0;
        D_menu_801B9124 = 100;
        gGameState = GSTATE_MAP;
        gNextGameStateTimer = 2;
        D_ctx_80177B40 = 0;
        gDrawMode = DRAW_NONE;
        gControllerLock = 3;
    } else {
        gFillScreenAlpha += 32;
        if (gFillScreenAlpha > 255) {
            gFillScreenAlpha = 255;
        }
    }
}

void Option_TrainingUpdate(void) {
    if (gFillScreenAlpha == 255) {
        gCurrentLevel = LEVEL_TRAINING;
        gGameState = GSTATE_PLAY;
        gNextGameStateTimer = 2;
        gPlayState = PLAY_STANDBY;
        gDrawMode = DRAW_NONE;
        Play_Setup();
        D_ctx_80177CA0 = 0;
        D_ctx_80177CB0 = 0.0f;
        D_ctx_8017782C = 1;
        gControllerLock = 3;
        Audio_SetAudioSpec(0, 28);
    } else {
        gFillScreenAlpha += 32;
        if (gFillScreenAlpha > 255) {
            gFillScreenAlpha = 255;
        }
    }
}

void Option_801929F0(void) {
    s32 i;

    D_game_800D2870 = 0;
    gBlurAlpha = 255;
    gControllerLock = 0;
    D_ctx_80178410 = 800;
    D_menu_801B9248 = 0;

    if (D_menu_801B9244 == 0) {
        D_menu_801B91BC = 1;
        for (i = 0; i < OPTION_COUNT; i++) {
            sOptionCardList[i].unk_00.unk_18 = sOptionCardCurTextPosX[i];
            sOptionCardList[i].unk_00.unk_1C = sOptionCardCurTextPosY[i];
            sOptionCardList[i].unk_00.unk_20 = 1.0f;
            sOptionCardList[i].unk_00.unk_24 = 1.0f;
            sOptionCardList[i].unk_58 = 1;

            sOptionCardList[i].unk_38.unk_0C = 0.4f;
            sOptionCardList[i].unk_38.unk_10 = 0.21f;
            sOptionCardList[i].unk_38.unk_04 = sOptionCardPosY[i];
            sOptionCardList[i].unk_38.unk_08 = 0.0f;
            sOptionCardList[i].unk_5C = 1;
        }
    } else {
        D_menu_801B91BC = 0;
        for (i = 0; i < OPTION_COUNT; i++) {
            sOptionCardList[i].unk_00.unk_24 = 1.0f;
            sOptionCardList[i].unk_38.unk_10 = 0.21f;
            sOptionCardList[i].unk_38.unk_08 = 0.0f;
            sOptionCardList[i].unk_5C = 1;
            sOptionCardList[i].unk_58 = 1;
        }
    }

    D_menu_801B9204 = -45.0f;
    D_menu_801B9214 = 0;

    D_menu_801B9180.unk_0 = 0;
    D_menu_801B9180.unk_4 = 0;
    D_menu_801B9190.unk_0 = 0;
    D_menu_801B9190.unk_4 = 0;
    D_menu_801B9198.unk_0 = 0;
    D_menu_801B9198.unk_4 = 0;
}

void Option_MainMenuUpdate(void) {
    s32 i;
    f32 var_fs0;
    f32 var_fs1;
    s32 temp1;
    s32 temp2;

    switch (D_menu_801B912C) {
        case 0:
            Option_801929F0();
            if (D_menu_801B9244 == 0) {
                D_menu_801B912C++;
            } else {
                sOptionCardCurTextPosX[0] = D_menu_801AE5E8[D_menu_801B91B0];
                sOptionCardCurTextPosY[0] = D_menu_801AE5F0[D_menu_801B91B0];
                sOptionCardCurTextPosX[4] = D_menu_801AE5F8[D_menu_801B91AC];
                sOptionCardCurTextPosY[4] = D_menu_801AE600[D_menu_801B91AC];
                D_menu_801B912C = 1000;
            }
            break;

        case 1000:
            for (i = 0; i < OPTION_COUNT; i++) {
                if (sOptionCardList[i].unk_38.unk_0C < 0.4f) {
                    sOptionCardList[i].unk_38.unk_0C += 0.04f;
                    if (sOptionCardList[i].unk_38.unk_0C > 0.4f) {
                        sOptionCardList[i].unk_38.unk_0C = 0.4f;
                    }
                }
                if (sOptionCardList[i].unk_00.unk_20 < 1.0f) {
                    sOptionCardList[i].unk_00.unk_20 += 0.1f;
                    if (sOptionCardList[i].unk_00.unk_20 > 1.0f) {
                        sOptionCardList[i].unk_00.unk_20 = 1.0f;
                    }
                }

                Math_SmoothStepToF(&sOptionCardList[i].unk_00.unk_1C, sOptionCardCurTextPosY[i], 0.15f, 100.0f, 0.1f);
                Math_SmoothStepToF(&sOptionCardList[i].unk_38.unk_04, sOptionCardPosY[i], 0.15f, 100.0f, 0.1f);
                Math_SmoothStepToF(&sOptionCardList[i].unk_00.unk_18, sOptionCardCurTextPosX[i], 0.2f,
                                   D_menu_801AE620[i], 0.1f);
            }

            gBlurAlpha += 4;

            if (sOptionCardList[D_menu_801B91A4].unk_38.unk_04 == sOptionCardPosY[D_menu_801B91A4]) {
                for (i = 0; i < OPTION_COUNT; i++) {
                    sOptionCardList[i].unk_00.unk_20 = 1.0f;
                    sOptionCardList[i].unk_00.unk_18 = sOptionCardCurTextPosX[i];
                    sOptionCardList[i].unk_00.unk_1C = sOptionCardCurTextPosY[i];
                }
                D_menu_801B91BC = 1;
                gBlurAlpha = 255;
                D_menu_801B912C = 1;
            }
            break;

        case 1:
            temp1 =
                Option_8019C418(&D_menu_801B91A4, OPTION_COUNT - 1, 1, 0, 20, 5, 4, gMainController, &D_menu_801B9180);
            // clang-format off
            if (temp1 != 0) { AUDIO_PLAY_SFX(0x49000022, gDefaultSfxSource, 4); }
            // clang-format on

            if ((D_menu_801B91A4 == 0) && (D_menu_801B91C8 != 0)) {
                temp2 = Option_8019C418(&D_menu_801B91B0, 1, 0, 0, 20, 5, 4, gMainController, &D_menu_801B9190);
                if (temp2 != 0) {
                    AUDIO_PLAY_SFX(0x49000022, gDefaultSfxSource, 4);
                    if (D_menu_801B91B0) {
                        sOptionCardList[0].unk_00.unk_08 = D_OPT_8004C50;
                        sOptionCardList[0].unk_00.unk_10 = 80;
                        sOptionCardList[0].unk_00.unk_14 = 12;
                        sOptionCardList[0].unk_00.unk_18 = 125.0f;
                        sOptionCardList[0].unk_00.unk_1C = 55.0f;
                    } else {
                        sOptionCardList[0].unk_00.unk_08 = D_OPT_8003B50;
                        sOptionCardList[0].unk_00.unk_10 = 72;
                        sOptionCardList[0].unk_00.unk_14 = 12;
                        sOptionCardList[0].unk_00.unk_18 = 124.0f;
                        sOptionCardList[0].unk_00.unk_1C = 54.0f;
                    }
                    gExpertMode = D_menu_801B91B0;
                }
            }
            if ((D_menu_801B91A4 == 4) && (D_menu_801B91C8 != 0)) {
                temp2 = Option_8019C418(&D_menu_801B91AC, 1, 0, 0, 20, 5, 4, gMainController, &D_menu_801B9198);
                if (temp2 != 0) {
                    AUDIO_PLAY_SFX(0x49000022, gDefaultSfxSource, 4);
                    if (D_menu_801B91AC) {
                        sOptionCardList[4].unk_00.unk_08 = D_OPT_8004C50;
                        sOptionCardList[4].unk_00.unk_10 = 80;
                        sOptionCardList[4].unk_00.unk_14 = 12;
                        sOptionCardList[4].unk_00.unk_18 = 125.0f;
                        sOptionCardList[4].unk_00.unk_1C = 151.0f;
                    } else {
                        sOptionCardList[4].unk_00.unk_08 = D_OPT_80046B0;
                        sOptionCardList[4].unk_00.unk_10 = 64;
                        sOptionCardList[4].unk_00.unk_14 = 10;
                        sOptionCardList[4].unk_00.unk_18 = 133.0f;
                        sOptionCardList[4].unk_00.unk_1C = 151.0f;
                    }
                }
            }

            if (gControllerPress[gMainController].button & (A_BUTTON | START_BUTTON)) {
                AUDIO_PLAY_SFX(0x49000020, gDefaultSfxSource, 4);
                D_menu_801B9208 = sOptionCardPosY[D_menu_801B91A4];
                D_menu_801B91BC = 0;
                D_menu_801B912C = 11;
            }
            if (gControllerPress[gMainController].button & B_BUTTON) {
                AUDIO_PLAY_SFX(0x49000021, gDefaultSfxSource, 4);
                D_menu_801B8284 = 0;
                D_menu_801B8280 = 1;
                D_menu_801B912C = 100;
            }
            break;

        case 11:
            gBlurAlpha = 16;
            D_menu_801B9178 = 3;
            sOptionCardList[D_menu_801B91A4].unk_38.unk_0C -= 0.01f;
            sOptionCardList[D_menu_801B91A4].unk_38.unk_10 -= 0.01f;
            sOptionCardList[D_menu_801B91A4].unk_00.unk_20 -= 0.1f;
            sOptionCardList[D_menu_801B91A4].unk_00.unk_24 -= 0.1f;
            sOptionCardList[D_menu_801B91A4].unk_00.unk_18 += 4.0f;
            D_menu_801B917C = 3;
            D_menu_801B912C++;
            break;

        case 12:
            if (D_menu_801B9178 == 1) {
                sOptionCardList[D_menu_801B91A4].unk_38.unk_0C += 0.01f;
                sOptionCardList[D_menu_801B91A4].unk_38.unk_10 += 0.01f;
                sOptionCardList[D_menu_801B91A4].unk_00.unk_20 += 0.1f;
                sOptionCardList[D_menu_801B91A4].unk_00.unk_24 += 0.1f;
                sOptionCardList[D_menu_801B91A4].unk_00.unk_18 -= 4.0f;
                D_menu_801B9214 = 1;
            }

            for (i = 0; i < OPTION_COUNT; i++) {
                if (i == D_menu_801B91A4) {
                    continue;
                }

                if (sOptionCardList[i].unk_38.unk_0C > 0.01f) {
                    sOptionCardList[i].unk_38.unk_0C -= 0.05f;
                    sOptionCardList[i].unk_00.unk_20 -= 0.19f;
                    Math_SmoothStepToF(&sOptionCardList[i].unk_00.unk_18, 158.0f, 0.2f, D_menu_801AE608[i], 0.1f);
                } else {
                    sOptionCardList[i].unk_5C = 0;
                    sOptionCardList[i].unk_58 = 0;
                }
            }

            if (D_menu_801B917C != 0) {
                break;
            }

            var_fs0 = 25.0f;
            var_fs1 = 90.0f;

            if ((D_menu_801B91A4 == 0) || (D_menu_801B91A4 == 1)) {
                var_fs0 = 0.0f;
                var_fs1 = 120.0f;
            }

            Math_SmoothStepToF(&sOptionCardList[D_menu_801B91A4].unk_00.unk_1C, var_fs0, 0.25f, 100.0f, 0.1f);
            Math_SmoothStepToF(&sOptionCardList[D_menu_801B91A4].unk_38.unk_04, var_fs1, 0.25f, 100.0f, 0.1f);

            gBlurAlpha += 4;

            if ((sOptionCardList[D_menu_801B91A4].unk_00.unk_1C == var_fs0) &&
                (sOptionCardList[D_menu_801B91A4].unk_38.unk_04 == var_fs1)) {
                gBlurAlpha += 255;
                D_menu_801B9124 = D_menu_801B91A4;

                if (D_menu_801B91A4 == 4 && D_menu_801B91AC) {
                    D_menu_801B9124 = 6;
                }

                Option_InitEntry();
            }
            break;

        case 100:
            if (D_menu_801B8284 < 120) {
                D_menu_801B8284 += 18;
            } else {
                D_ctx_80178410 = 0;
                gGameState = GSTATE_TITLE;
                gNextGameStateTimer = 2;
                D_ctx_80177AE0 = 0;
                D_menu_801B827C = 1;
                gDrawMode = DRAW_NONE;
                D_menu_801B8280 = 0;
                D_menu_801B8284 = 0;
                gControllerLock = 3;
            }
            break;
    }
}

void Option_MainMenuDraw(void) {
    s32 i;

    Option_8019BDF0();

    for (i = 0; i < OPTION_COUNT; i++) {
        if (sOptionCardList[i].unk_5C) {
            Option_DrawMenuCard(sOptionCardList[i].unk_38);
        }
    }

    Option_DrawMenuArwing(sOptionCardList[D_menu_801B91A4].unk_4C);
    Matrix_Pop(&gGfxMatrix);

    for (i = 0; i < OPTION_COUNT; i++) {
        if (!(sOptionCardList[i].unk_58) || (sOptionCardList[i].unk_00.unk_20) <= 0.0f) {
            continue;
        }
        if ((i == 0) && (D_menu_801B91C8 != 0) && ((D_menu_801B912C == 0) || (D_menu_801B912C == 1))) {
            Option_8019B6D8(106.0f, 56.0f, 98.0f, 20, 0, 75);
        }
        if ((i == 4) && (D_menu_801B91C8 != 0) && ((D_menu_801B912C == 0) || (D_menu_801B912C == 1))) {
            Option_8019B6D8(106.0f, 152.0f, 98.0f, 20, 0, 75);
        }
        Option_DrawCardLabel(sOptionCardList[i].unk_00);
    }

    Option_8019BF34();
}

void Option_80193B04(void) {
    s32 i;

    gBlurAlpha = 255;
    gControllerLock = 0;
    D_ctx_80178410 = 800;

    if (D_menu_801B9248 == 0) {
        D_menu_801B91BC = 1;

        for (i = 0; i < 3; i++) {
            sOptionVSCardList[i].unk_00.unk_18 = D_menu_801AEF90[i];
            sOptionVSCardList[i].unk_00.unk_1C = D_menu_801AEF9C[i];
            sOptionVSCardList[i].unk_00.unk_20 = 1.0f;
            sOptionVSCardList[i].unk_00.unk_24 = 1.0f;
            sOptionVSCardList[i].unk_58 = 1;
            sOptionVSCardList[i].unk_38.unk_0C = 0.4f;
            sOptionVSCardList[i].unk_38.unk_10 = 0.21f;
            sOptionVSCardList[i].unk_38.unk_04 = D_menu_801AEF84[i];
            sOptionVSCardList[i].unk_38.unk_08 = 0.0f;
            sOptionVSCardList[i].unk_5C = 1;
        }
    } else {
        D_menu_801B91BC = 0;

        for (i = 0; i < 3; i++) {
            sOptionVSCardList[i].unk_00.unk_24 = 1.0f;
            sOptionVSCardList[i].unk_38.unk_10 = 0.21f;
            sOptionVSCardList[i].unk_38.unk_08 = 0.0f;
            sOptionVSCardList[i].unk_58 = 1;
            sOptionVSCardList[i].unk_5C = 1;
        }
    }

    D_menu_801B9204 = -45.0f;
    D_menu_801B9214 = 0;
    D_menu_801B9188.unk_0 = 0;
    D_menu_801B9188.unk_4 = 0;
}

void Option_VersusUpdate(void) {
    f32 var_fs0;
    s32 i;

    switch (D_menu_801B912C) {
        case 0:
            Option_80193B04();
            if (D_menu_801B9248 == 0) {
                D_menu_801B912C++;
            } else {
                D_menu_801B912C = 1000;
            }
            break;

        case 1000:
            for (i = 0; i < 3; i++) {
                if (sOptionVSCardList[i].unk_38.unk_0C < 0.4f) {
                    sOptionVSCardList[i].unk_38.unk_0C += 0.04f;
                    if (sOptionVSCardList[i].unk_38.unk_0C > 0.4f) {
                        sOptionVSCardList[i].unk_38.unk_0C = 0.4f;
                    }
                }

                if (sOptionVSCardList[i].unk_00.unk_20 < 1.0f) {
                    sOptionVSCardList[i].unk_00.unk_20 += 0.15f;
                    if (sOptionVSCardList[i].unk_00.unk_20 > 1.0f) {
                        sOptionVSCardList[i].unk_00.unk_20 = 1.0f;
                    }
                }

                Math_SmoothStepToF(&sOptionVSCardList[i].unk_38.unk_04, D_menu_801AEF84[i], 0.15f, 100.0f, 0.1f);
                Math_SmoothStepToF(&sOptionVSCardList[i].unk_00.unk_18, D_menu_801AEF90[i], 0.2f, 3.1f, 0.1f);
                Math_SmoothStepToF(&sOptionVSCardList[i].unk_00.unk_1C, D_menu_801AEF9C[i], 0.15f, 100.0f, 0.1f);
            }

            Math_SmoothStepToF(&sOptionCardList[D_menu_801B91A4].unk_00.unk_1C, 25.0f, 0.25f, 100.0f, 0.1f);
            Math_SmoothStepToF(&sOptionCardList[D_menu_801B91A4].unk_38.unk_04, 90.0f, 0.25f, 100.0f, 0.1f);

            gBlurAlpha += 4;

            if (sOptionVSCardList[D_menu_801B91A8].unk_38.unk_04 == D_menu_801AEF84[D_menu_801B91A8]) {
                for (i = 0; i < 3; i++) {
                    sOptionVSCardList[i].unk_00.unk_20 = 1.0f;
                    sOptionVSCardList[i].unk_00.unk_1C = D_menu_801AEF9C[i];
                    sOptionVSCardList[i].unk_00.unk_18 = D_menu_801AEF90[i];
                }

                sOptionCardList[D_menu_801B91A4].unk_00.unk_1C = 25.0f;
                sOptionCardList[D_menu_801B91A4].unk_38.unk_04 = 90.0f;
                D_menu_801B91BC = 1;
                gBlurAlpha = 255;
                D_menu_801B912C = 1;
            }
            break;

        case 1:
            // clang-format off
            if (Option_8019C418(&D_menu_801B91A8, 2, 1, 0, 20, 5, 4, gMainController, &D_menu_801B9188)) { AUDIO_PLAY_SFX(0x49000022, gDefaultSfxSource, 4); }
            // clang-format on

            if (gControllerPress[gMainController].button & (A_BUTTON | START_BUTTON)) {
                AUDIO_PLAY_SFX(0x49000020, gDefaultSfxSource, 4);
                D_menu_801B9208 = D_menu_801AEF84[D_menu_801B91A8];
                D_menu_801B91BC = 0;
                D_menu_801B912C = 11;
            }

            if (gControllerPress[gMainController].button & B_BUTTON) {
                AUDIO_PLAY_SFX(0x49000021, gDefaultSfxSource, 4);
                D_menu_801B912C = 0;
                D_menu_801B9124 = 1000;
                gDrawMode = DRAW_NONE;
                D_menu_801B9244 = 1;
            }
            break;

        case 11:
            gBlurAlpha = 16;
            D_menu_801B9178 = 5;
            sOptionVSCardList[D_menu_801B91A8].unk_38.unk_0C -= 0.01f;
            sOptionVSCardList[D_menu_801B91A8].unk_38.unk_10 -= 0.01f;
            sOptionVSCardList[D_menu_801B91A8].unk_00.unk_20 -= 0.1f;
            sOptionVSCardList[D_menu_801B91A8].unk_00.unk_24 -= 0.1f;
            sOptionVSCardList[D_menu_801B91A8].unk_00.unk_18 += 4.0f;
            D_menu_801B917C = 5;
            D_menu_801B912C++;
            break;

        case 12:
            if (D_menu_801B9178 == 1) {
                sOptionVSCardList[D_menu_801B91A8].unk_38.unk_0C += 0.01f;
                sOptionVSCardList[D_menu_801B91A8].unk_38.unk_10 += 0.01f;
                sOptionVSCardList[D_menu_801B91A8].unk_00.unk_20 += 0.1f;
                sOptionVSCardList[D_menu_801B91A8].unk_00.unk_24 += 0.1f;
                sOptionVSCardList[D_menu_801B91A8].unk_00.unk_18 -= 4.0f;
                D_menu_801B9214 = 1;
            }

            for (i = 0; i < 3; i++) {
                if (i == D_menu_801B91A8) {
                    continue;
                }

                if (sOptionVSCardList[i].unk_38.unk_0C > 0.01f) {
                    sOptionVSCardList[i].unk_38.unk_0C -= 0.05f;
                    sOptionVSCardList[i].unk_00.unk_20 -= 0.19f;
                    Math_SmoothStepToF(&sOptionVSCardList[i].unk_00.unk_18, 158.0f, 0.2f, D_menu_801AE608[i + 1], 0.1f);
                } else {
                    sOptionVSCardList[i].unk_5C = 0;
                    sOptionVSCardList[i].unk_58 = 0;
                }
            }

            if (D_menu_801B917C == 0) {
                if (D_menu_801B91A8 == 0) {
                    var_fs0 = 129.0f;
                } else {
                    var_fs0 = 131.0f;
                }

                Math_SmoothStepToF(&sOptionVSCardList[D_menu_801B91A8].unk_00.unk_1C, var_fs0, 0.25f, 100.0f, 0.1f);
                Math_SmoothStepToF(&sOptionVSCardList[D_menu_801B91A8].unk_38.unk_04, -15.5f, 0.25f, 100.0f, 0.1f);
                Math_SmoothStepToF(&sOptionCardList[D_menu_801B91A4].unk_00.unk_1C, -10.0f, 0.35f, 100.0f, 0.1f);
                Math_SmoothStepToF(&sOptionCardList[D_menu_801B91A4].unk_38.unk_04, 150.0f, 0.35f, 100.0f, 0.1f);

                gBlurAlpha += 4;

                if ((var_fs0 == sOptionVSCardList[D_menu_801B91A8].unk_00.unk_1C) &&
                    (sOptionVSCardList[D_menu_801B91A8].unk_38.unk_04 == -15.5f)) {
                    gBlurAlpha += 255;
                    D_menu_801B9124 = (D_menu_801B91A8 + 1) * 10;
                    D_ctx_801778AC = D_menu_801B91A8;
                    D_menu_801B91C4 = 1;
                    Option_InitEntry();
                }
            }
            break;
    }
}

void Option_VersusDraw(void) {
    s32 i;

    Option_DrawMenuLabel();
    Option_8019BDF0();

    for (i = 0; i < 3; i++) {
        if (sOptionVSCardList[i].unk_5C != 0) {
            Option_DrawMenuCard(sOptionVSCardList[i].unk_38);
        }
    }

    Option_DrawMenuArwing(sOptionVSCardList[D_menu_801B91A8].unk_4C);
    Matrix_Pop(&gGfxMatrix);

    for (i = 0; i < 3; i++) {
        if ((sOptionVSCardList[i].unk_58 != 0) && !(sOptionVSCardList[i].unk_00.unk_20 <= 0.0f)) {
            Option_DrawCardLabel(sOptionVSCardList[i].unk_00);
        }
    }

    Option_8019BF34();
}

void Option_SoundInit(void) {
    s32 i;

    D_ctx_80178410 = 800;

    D_menu_801B91B4 = 0;
    D_menu_801B91B8 = 0;
    D_menu_801B91BC = 1;
    D_menu_801B91A0 = 0;

    gSoundMode = gSaveFile.save.data.soundMode;
    SEQCMD_SET_SOUND_MODE(D_menu_801AE998[gSoundMode]);

    gVolumeSettings[0] = gSaveFile.save.data.musicVolume;
    gVolumeSettings[1] = gSaveFile.save.data.voiceVolume;
    gVolumeSettings[2] = gSaveFile.save.data.sfxVolume;

    if (gVolumeSettings[0] > 99) {
        gVolumeSettings[0] = 99;
    }
    if (gVolumeSettings[1] > 99) {
        gVolumeSettings[1] = 99;
    }
    if (gVolumeSettings[2] > 99) {
        gVolumeSettings[2] = 99;
    }

    func_8001D8A8(0, gVolumeSettings[0]);
    func_8001D8A8(1, gVolumeSettings[1]);
    func_8001D8A8(2, gVolumeSettings[2]);

    D_menu_801AEB48[0].unk_18 = gVolumeSettings[0] + 146.0f;
    D_menu_801AEB48[1].unk_18 = gVolumeSettings[1] + 146.0f;
    D_menu_801AEB48[2].unk_18 = gVolumeSettings[2] + 146.0f;

    D_menu_801B9288 = 0;
    D_menu_801B9284 = 0;
    D_menu_801B914C = 0;
    D_menu_801B9158 = 0;
    D_menu_801B9178 = 0;
    D_menu_801B917C = 0;

    // clang-format off
    for (i = 0; i < 5; i++) { D_menu_801B9270[i] = 255.0f; }
    // clang-format on
    D_menu_801B91E4 = 255.0f;

    D_menu_801B9218 = 56.0f;
    D_menu_801B921C = -43.0f;
    D_menu_801B9220 = 0.0f;

    D_menu_801B9250.unk_0 = 0;
    D_menu_801B9250.unk_4 = 0;

    D_menu_801B9258.unk_0 = 0;
    D_menu_801B9258.unk_4 = 0;

    D_menu_801B9260.unk_0 = 0;
    D_menu_801B9260.unk_4 = 0;

    D_menu_801B9268.unk_0 = 0;
    D_menu_801B9268.unk_4 = 0;
}

void Option_SoundUpdate(void) {
    s32 sp34;
    s32 temp;

    sp34 = D_menu_801B9288;
    temp = Option_8019C418(&D_menu_801B9288, 3, 1, 0, 20, 5, 4, gMainController, &D_menu_801B9250);
    if (temp != 0) {
        D_menu_801B9270[sp34] = 255.0f;
        AUDIO_PLAY_SFX(0x49000002, gDefaultSfxSource, 4);
    }

    if (D_menu_801B9288 == 0) {
        Option_80194AEC();
    } else {
        Option_80194BD0();
    }

    // Test sound
    if (gControllerPress[gMainController].button & R_TRIG) {
        D_menu_801B9284 ^= 1;
        Audio_PlaySoundTest(D_menu_801B9284);
    }

    if (gControllerPress[gMainController].button & A_BUTTON) {
        AUDIO_PLAY_SFX(0x49000003, gDefaultSfxSource, 4);
        D_menu_801B9288 = (D_menu_801B9288 + 1) % 4U;
    }

    if (gControllerPress[gMainController].button & B_BUTTON) {
        AUDIO_PLAY_SFX(0x49000021, gDefaultSfxSource, 4);
        if (D_menu_801B9284 == 1) {
            D_menu_801B9284 = 0;
            Audio_PlaySoundTest(D_menu_801B9284);
        }
        Save_Write();
        gDrawMode = DRAW_NONE;
        D_menu_801B9124 = 1000;
        D_menu_801B912C = 0;
        D_menu_801B9244 = 1;
    }
}

void Option_80194AEC(void) {
    s32 sp3C = gSoundMode;
    s32 pad;

    if (Option_8019C418(&sp3C, 2, 0, 0, 20, 5, 4, gMainController, &D_menu_801B9260)) {
        AUDIO_PLAY_SFX(0x49000002, gDefaultSfxSource, 4);
        gSoundMode = sp3C;
        if (gSoundMode >= OPTIONSOUND_MAX) {
            gSoundMode = OPTIONSOUND_STEREO;
        }
        gSaveFile.save.data.soundMode = gSoundMode;
        SEQCMD_SET_SOUND_MODE(D_menu_801AE998[gSoundMode]);
    }
}

void Option_80194BD0(void) {
    s32 var_v1;

    D_menu_801B924C = D_menu_801AE99C[D_menu_801B9288 - 1];

    if (Option_8019C66C(&(D_menu_801AEB48[D_menu_801B9288 - 1].unk_18), 146.0f, 245.0f, &D_menu_801B9268)) {
        var_v1 = D_menu_801AEB48[D_menu_801B9288 - 1].unk_18 - 146.0f;

        gVolumeSettings[D_menu_801B9288 - 1] = var_v1;

        if (var_v1 > 99) {
            var_v1 = 99;
        }

        switch (D_menu_801B9288 - 1) {
            case 0:
                gSaveFile.save.data.musicVolume = var_v1;
                break;

            case 1:
                gSaveFile.save.data.voiceVolume = var_v1;
                break;

            case 2:
                gSaveFile.save.data.sfxVolume = var_v1;
                break;
        }
        func_8001D8A8(D_menu_801B924C, var_v1);
    }
}

void Option_SoundDraw(void) {
    s32 i;
    s32 colorGB;

    static f32 D_menu_801AEFA8[11] = {
        48.0f, 103.0f, 77.0f, 55.0f, 71.0f, 87.0f, 143.0f, 244.0f, 169.0f, 170.0f, 157.0f
    };
    static f32 D_menu_801AEFD4[11] = {
        79.0f, 52.0f, 99.0f, 131.0f, 157.0f, 186.0f, 102.0f, 102.0f, 98.0f, 99.0f, 98.0f
    };
    static f32 D_menu_801AF000 = 27.5f;

    Option_DrawMenuLabel();

    Option_801952B4();

    RCP_SetupDL(&gMasterDisp, 0x4C);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
    TextureRect_16bRGBA(&gMasterDisp, D_MAP_60447A0, 8, 8, D_menu_801AEFA8[0], D_menu_801AEFD4[0], D_menu_801AF000,
                        0.2f);

    RCP_SetupDL(&gMasterDisp, 0x53);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
    TextureRect_8bIA(&gMasterDisp, D_OPT_8005CD0, 112, 13, D_menu_801AEFA8[1], D_menu_801AEFD4[1], 1.0f, 1.0f);

    for (i = 0; i < 4; i++) {
        if (D_menu_801B9288 == i) {
            Option_8019C824(&D_menu_801B9270[i]);
        } else {
            D_menu_801B9270[i] = 255.0f;
        }
    }

    colorGB = D_menu_801B9270[0];
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, colorGB, colorGB, 255);
    TextureRect_8bIA(&gMasterDisp, D_OPT_8006280, 48, 13, D_menu_801AEFA8[2], D_menu_801AEFD4[2], 1.0f, 1.0f);

    colorGB = D_menu_801B9270[1];
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, colorGB, colorGB, 255);
    TextureRect_8bIA(&gMasterDisp, D_OPT_80064F0, 88, 14, D_menu_801AEFA8[3], D_menu_801AEFD4[3], 1.0f, 1.0f);

    colorGB = D_menu_801B9270[2];
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, colorGB, colorGB, 255);
    TextureRect_8bIA(&gMasterDisp, D_OPT_80069C0, 56, 15, D_menu_801AEFA8[4], D_menu_801AEFD4[4], 1.0f, 1.0f);

    colorGB = D_menu_801B9270[3];
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, colorGB, colorGB, 255);
    TextureRect_8bIA(&gMasterDisp, D_OPT_8006D10, 24, 13, D_menu_801AEFA8[5], D_menu_801AEFD4[5], 1.0f, 1.0f);

    if (D_menu_801B9288 == 0) {
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
        TextureRect_8bIA_MirX(&gMasterDisp, D_OPT_800E130, 8, 8, D_menu_801AEFA8[6], D_menu_801AEFD4[6], 1.0f, 1.0f);
        TextureRect_8bIA(&gMasterDisp, D_OPT_800E130, 8, 8, D_menu_801AEFA8[7], D_menu_801AEFD4[7], 1.0f, 1.0f);
    }

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    switch (gSoundMode) {
        case OPTIONSOUND_STEREO:
            TextureRect_8bIA(&gMasterDisp, D_OPT_800CD90, 56, 13, D_menu_801AEFA8[8], D_menu_801AEFD4[8], 1.0f, 1.0f);
            break;

        case OPTIONSOUND_MONO:
            TextureRect_8bIA(&gMasterDisp, D_OPT_80076E0, 56, 14, D_menu_801AEFA8[9], D_menu_801AEFD4[9], 1.0f, 1.0f);
            break;

        case OPTIONSOUND_HEADSET:
            TextureRect_8bIA(&gMasterDisp, D_OPT_8007210, 88, 14, D_menu_801AEFA8[10], D_menu_801AEFD4[10], 1.0f, 1.0f);
            break;
    }

    TextureRect_8bIA(&gMasterDisp, D_OPT_8006E50, 96, 10, 166.0f, 213.0f, 1.0f, 1.0f);

    for (i = 0; i < 3; i++) {
        Option_DrawCardLabel(D_menu_801AEAA0[i]);
        Option_DrawCardLabel(D_menu_801AEB48[i]);
    }
}

void Option_801952B4(void) {
    s32 i;

    if (D_menu_801B9284 == 1) {
        switch (D_menu_801B914C) {
            case 0:
                D_menu_801B914C++;
                break;

            case 1:
                if (D_menu_801B9178) {
                    break;
                }

                for (i = 2; i < 4; i++) {
                    D_menu_801AE9C0[i].unk_20 += 0.02f;
                    D_menu_801AE9C0[i].unk_24 += 0.02f;
                    D_menu_801AE9C0[i].unk_18 -= 0.1f;
                }

                D_menu_801B9178 = 2;
                D_menu_801B914C++;
                break;

            case 2:
                if (D_menu_801B9178) {
                    break;
                }

                for (i = 2; i < 4; i++) {
                    D_menu_801AE9C0[i].unk_20 -= 0.02f;
                    D_menu_801AE9C0[i].unk_24 -= 0.02f;
                    D_menu_801AE9C0[i].unk_18 += 0.1f;
                }

                D_menu_801B914C++;
                break;

            case 3:
                D_menu_801B9178 = RAND_INT(15.0f);
                D_menu_801B914C = 1;
                break;
        }

        switch (D_menu_801B9158) {
            case 0:
                if (D_menu_801B917C) {
                    break;
                }

                for (i = 0; i < 4; i++) {
                    D_menu_801AE9C0[i].unk_20 += 0.08f;
                    D_menu_801AE9C0[i].unk_24 += 0.08f;
                    D_menu_801AE9C0[i].unk_18 -= 0.4f;
                    D_menu_801AE9C0[i].unk_1C -= 0.4f;
                }

                D_menu_801B917C = 2;
                D_menu_801B9158++;
                break;

            case 1:
                if (D_menu_801B917C) {
                    break;
                }

                for (i = 0; i < 4; i++) {
                    D_menu_801AE9C0[i].unk_20 -= 0.08f;
                    D_menu_801AE9C0[i].unk_24 -= 0.08f;
                    D_menu_801AE9C0[i].unk_18 += 0.4f;
                    D_menu_801AE9C0[i].unk_1C += 0.4f;
                }

                D_menu_801B917C = 2;
                D_menu_801B9158++;
                break;

            case 2:
                if (D_menu_801B917C) {
                    break;
                }

                D_menu_801B917C = RAND_INT(30.0f);
                D_menu_801B9158 = 0;
                break;
        }

    } else {
        for (i = 0; i < 4; i++) {
            D_menu_801AE9C0[i].unk_20 = 1.0f;
            D_menu_801AE9C0[i].unk_24 = 1.0f;
            D_menu_801AE9C0[i].unk_18 = D_menu_801AE9A0[i];
            D_menu_801AE9C0[i].unk_1C = D_menu_801AE9B0[i];
        }
    }

    for (i = 0; i < 2; i++) {
        Option_DrawCardLabel(D_menu_801AE9C0[i]);
    }

    for (i = 2; i < 4; i++) {
        if (D_menu_801B914C != 3) {
            Option_DrawCardLabel(D_menu_801AE9C0[i]);
        }
    }
}

void Option_ExpertSoundInit(void) {
    s32 i;

    D_ctx_80178410 = 800;
    D_menu_801B931C = 0;

    D_menu_801B9290.unk_0 = 0;
    D_menu_801B9290.unk_4 = 0;

    spectrumAnalizerMode = 0;
    D_menu_801B9320 = 0;

    // clang-format off
    for (i = 0; i < 32; i++) { D_menu_801B9298[i] = 0.0f; }
    // clang-format on
}

#include "../../mods/sfxjukebox.c"

// Expert Sound Options
void Option_ExpertSoundUpdate(void) {
    s32 pad;
    f32 sp28 = D_menu_801B931C;

    if (CVarGetInteger("gSfxJukebox", 0) == 1) {
        Option_JukeboxSoundUpdate();
        return;
    }

    if (Option_8019C66C(&sp28, 0.0f, 49.0f, &D_menu_801B9290) != 0) {
        AUDIO_PLAY_SFX(0x49000002, gDefaultSfxSource, 4);
        D_menu_801B931C = sp28;
    }

    if (gControllerPress[gMainController].button & A_BUTTON) {
        Audio_PlaySoundTestTrack(D_menu_801B931C);
        D_menu_801B9320 = true;
    }

    if (gControllerPress[gMainController].button & B_BUTTON) {
        if (!D_menu_801B9320) {
            AUDIO_PLAY_SFX(0x49000021, gDefaultSfxSource, 4);
            AUDIO_PLAY_BGM(SEQ_ID_MENU);
            gDrawMode = DRAW_NONE;
            D_menu_801B9124 = 1000;
            D_menu_801B912C = 0;
            D_menu_801B9244 = 1;
        } else {
            AUDIO_PLAY_SFX(0x4900101D, gDefaultSfxSource, 4);
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 1);
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 1);
            D_menu_801B9320 = false;
        }
    }

    // Spectrum Analizer mode selector
    if (gControllerPress[gMainController].button & R_CBUTTONS) {
        spectrumAnalizerMode++;
        if (spectrumAnalizerMode > 2) {
            spectrumAnalizerMode = 0;
        }
    }
}

void Option_ExpertSoundDraw(void) {
    u8* temp_v0_4;
    f32 var_fs0;
    f32 var_fv1;
    s32 i;
    f32 r;
    f32 g;
    f32 b;
    static f32 D_menu_801AF004 = -125.0f;
    static f32 D_menu_801AF008 = 0.0f;
    static f32 D_menu_801AF00C = 2.0f;
    static f32 D_menu_801AF010 = 8.0f;
    static f32 D_menu_801AF014[4] = { 30.0f, 30.0f, 28.0f, 288.0f };
    static f32 D_menu_801AF024[4] = { 125.0f, 197.0f, 125.0f, 125.0f };
    static f32 D_menu_801AF034[4] = { 32.3f, 32.3f, 0.2f, 0.2f };
    static f32 D_menu_801AF044[4] = { 0.2f, 0.2f, 9.2f, 9.2f };
    static f32 D_menu_801AF054 = 255.0f;
    static f32 D_menu_801AF058 = 100.0f;
    static f32 D_menu_801AF05C = 255.0f;
    static f32 D_menu_801AF060 = 100.0f;
    static f32 D_menu_801AF064 = 255.0f;
    static f32 D_menu_801AF068 = 100.0f;
    static Gfx* D_menu_801AF06C[] = {
        D_menu_801AEC30,
        D_menu_801AEC88,
        D_menu_801AECE0,
    };
    static f32 D_menu_801AF078[] = { -73.0f, -13.0f, -43.0f };

    Option_DrawMenuLabel();

    RCP_SetupDL(&gMasterDisp, 0x53);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    TextureRect_8bIA(&gMasterDisp, D_OPT_80079F0, 128, 14, 49.0f, 81.0f, 1.0f, 1.0f);

    TextureRect_8bIA(&gMasterDisp, D_menu_801AECF8[D_menu_801B931C / 10], 16, 15, 230.0f, 82.0f, 1.0f, 1.0f);

    TextureRect_8bIA(&gMasterDisp, D_menu_801AECF8[D_menu_801B931C % 10], 16, 15, 244.0f, 82.0f, 1.0f, 1.0f);

    Option_8019B7D4();

    RCP_SetupDL(&gMasterDisp, 0x4C);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 50, 50, 200, 255);

    for (i = 0; i < 4; i++) {
        TextureRect_16bRGBA(&gMasterDisp, D_MAP_60447A0, 8, 8, D_menu_801AF014[i], D_menu_801AF024[i],
                            D_menu_801AF034[i], D_menu_801AF044[i]);
    }

    if (D_menu_801B9320 != 0) {
        temp_v0_4 = Audio_UpdateFrequencyAnalysis();
        var_fv1 = 60.0f;

        if (spectrumAnalizerMode == 2) {
            var_fv1 = 30.0f;
        }

        for (i = 0; i < 32; i++) {
            if (spectrumAnalizerMode == 0 || spectrumAnalizerMode == 2) {
                D_menu_801B9298[i] = (var_fv1 / 255.0f) * temp_v0_4[i];
            } else {
                D_menu_801B9298[i] = var_fv1 - ((var_fv1 / 255.0f) * temp_v0_4[i]);
            }
        }
    } else {
        for (i = 0; i < 32; i++) {
            Math_SmoothStepToF(&D_menu_801B9298[i], 0.0f, 0.2f, 100.0f, 0.1f);
        }
    }

    Lib_InitOrtho(&gMasterDisp);

    RCP_SetupDL(&gMasterDisp, 5);

    Matrix_Push(&gGfxMatrix);
    Matrix_LookAt(gGfxMatrix, 0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1);
    Matrix_SetGfxMtx(&gMasterDisp);

    for (var_fs0 = D_menu_801AF004, i = 0; i < 32; i++, var_fs0 += D_menu_801AF010) {
        r = D_menu_801AF054 + ((D_menu_801AF060 - D_menu_801AF054) / 31.0f) * i;
        g = D_menu_801AF058 + ((D_menu_801AF064 - D_menu_801AF058) / 31.0f) * i;
        b = D_menu_801AF05C + ((D_menu_801AF068 - D_menu_801AF05C) / 31.0f) * i;

        gDPSetPrimColor(gMasterDisp++, 0, 0, (s32) r, (s32) g, (s32) b, 255);

        Matrix_Push(&gGfxMatrix);
        Matrix_Translate(gGfxMatrix, var_fs0, D_menu_801AF078[spectrumAnalizerMode], D_menu_801AF008, 1);
        Matrix_Scale(gGfxMatrix, D_menu_801AF00C, D_menu_801B9298[i], 1.0f, 1);
        Matrix_SetGfxMtx(&gMasterDisp);

        gSPDisplayList(gMasterDisp++, D_menu_801AF06C[spectrumAnalizerMode]);

        Matrix_Pop(&gGfxMatrix);
    }

    Matrix_Pop(&gGfxMatrix);
    Lib_InitPerspective(&gMasterDisp);
}

void Option_DataInit(void) {
    D_ctx_80178410 = 800;
    D_menu_801B91E4 = 255.0f;
    D_menu_801B9330[0] = 0;
    D_menu_801B9330[1] = 0;
    D_menu_801B91C0 = 0;
    D_menu_801B91CC = 0;
}

void Option_DataUpdate(void) {
    f32 temp_fv0;
    s32 i;

    switch (D_menu_801B912C) {
        case 0:
            Option_8019669C();
            break;

        case 2:
            if (D_menu_801B9330[D_menu_801B91C0] != 0) {
                break;
            }
            D_menu_801B91CC = 0;
            D_menu_801B91C0 = 0;
            D_menu_801B912C = 0;
            break;

        case 3:
            if (D_menu_801B9330[D_menu_801B91C0]) {
                break;
            }
            gDrawMode = DRAW_NONE;
            D_menu_801B9124 = 1000;
            D_menu_801B912C = 0;
            D_menu_801B9244 = 1;
            break;

        case 4:
            if (D_menu_801B9330[D_menu_801B91C0]) {
                break;
            }

            switch (D_menu_801B91CC) {
                case 0:
                    D_menu_801B91CC = 1;
                    D_menu_801B91C0 = 0;
                    D_menu_801B912C = 0;
                    break;

                case 1:
                    D_menu_801B91CC = 2;
                    AUDIO_PLAY_SFX(0x0940A00B, gDefaultSfxSource, 4);
                    D_ctx_801779A8[gMainController] = 50.0f;
                    D_ctx_80177990[gMainController] = 0;
                    break;

                case 2:
                    D_ctx_80177990[gMainController] += (s32) D_ctx_801779A8[gMainController];
                    temp_fv0 = Math_SmoothStepToF(&D_ctx_801779A8[gMainController], 100.0f, 0.05f, 100.0f, 0.1f);

                    if (D_ctx_80177990[gMainController] >= 100) {
                        D_ctx_80177990[gMainController] -= 100;
                        D_80137E84[gMainController] = 1;
                    }

                    if (temp_fv0 == 0.0f) {
                        D_menu_801B91CC = 3;

                        gSaveFile = *(SaveFile*) &gDefaultSave;

                        Save_Write();

                        D_menu_801B91AC = 0;
                        D_menu_801B91B0 = 0;
                        D_menu_801B91C8 = 0;

                        gExpertMode = false;

                        sOptionCardList[0].unk_00.unk_08 = D_OPT_8003B50;
                        sOptionCardList[0].unk_00.unk_10 = 72;
                        sOptionCardList[0].unk_00.unk_14 = 12;
                        sOptionCardList[4].unk_00.unk_08 = D_OPT_80046B0;
                        sOptionCardList[4].unk_00.unk_10 = 64;
                        sOptionCardList[4].unk_00.unk_14 = 10;

                        for (i = 0; i < OPTION_COUNT; i++) {
                            sOptionCardCurTextPosX[i] = sOptionCardTextPosX[i];
                            sOptionCardCurTextPosY[i] = sOptionCardTextPosY[i];
                        }
                        Title_80188010();
                    }
                    break;

                case 3:
                    D_menu_801B912C = 0;
                    break;
            }
            break;
    }
}

void Option_8019669C(void) {
    if ((D_menu_801B91CC == 0) || (D_menu_801B91CC == 1)) {
        if (Option_8019C5A0(&D_menu_801B91C0) != 0) {
            AUDIO_PLAY_SFX(0x49000002, gDefaultSfxSource, 4);
        }
        if (1) {}
    }

    if (gControllerPress[gMainController].button & A_BUTTON) {
        if (D_menu_801B91CC == 3) {
            AUDIO_PLAY_SFX(0x49000021, gDefaultSfxSource, 4);
            D_menu_801B912C = 3;
        } else {
            D_menu_801B9330[D_menu_801B91C0] = 10;
            if (D_menu_801B91C0 == 0) {
                if (D_menu_801B91CC == 1) {
                    AUDIO_PLAY_SFX(0x49000003, gDefaultSfxSource, 4);
                    D_menu_801B912C = 2;
                } else {
                    AUDIO_PLAY_SFX(0x49000021, gDefaultSfxSource, 4);
                    D_menu_801B912C = 3;
                }
            } else {
                AUDIO_PLAY_SFX(0x49000003, gDefaultSfxSource, 4);
                D_menu_801B912C = 4;
            }
        }
    } else if (gControllerPress[gMainController].button & B_BUTTON) {
        if (D_menu_801B91CC == 1) {
            AUDIO_PLAY_SFX(0x4900101D, gDefaultSfxSource, 4);
            D_menu_801B912C = 2;
        } else {
            AUDIO_PLAY_SFX(0x49000021, gDefaultSfxSource, 4);
            D_menu_801B912C = 3;
        }
    }
}

void Option_DataDraw(void) {
    s32 i;
    s32 sp7C[2];
    s32 sp74[2];
    static f32 D_menu_801AF084[2] = { 172.0f, 76.0f };
    static f32 D_menu_801AF08C[2] = { 228.0f, 121.0f };

    static f32 D_menu_801AF094[6] = { 72.0f, 88.0f, 185.0f, 80.0f, 84.0f, 88.0f };
    static f32 D_menu_801AF0AC[6] = { 53.0f, 137.0f, 137.0f, 90.0f, 80.0f, 97.0f };

    Option_DrawMenuLabel();

    RCP_SetupDL(&gMasterDisp, 0x53);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    for (i = 0; i < 2; i++) {
        TextureRect_8bIA(&gMasterDisp, D_OPT_80084B0 + (i * 176 * 4), 176, 4, D_menu_801AF094[0],
                         D_menu_801AF0AC[0] + (4.0f * i), 1.0f, 1.0f);
    }
    TextureRect_8bIA(&gMasterDisp, D_OPT_80084B0 + 1408, 176, 5, D_menu_801AF094[0], D_menu_801AF0AC[0] + 8.0f, 1.0f,
                     1.0f);

    if (D_menu_801B91CC < 2) {
        TextureRect_8bIA_MirX(&gMasterDisp, D_OPT_800E130, 8, 8, D_menu_801AF084[D_menu_801B91C0], 140.0f, 1.0f, 1.0f);
        TextureRect_8bIA(&gMasterDisp, D_OPT_800E130, 8, 8, D_menu_801AF08C[D_menu_801B91C0], 140.0f, 1.0f, 1.0f);

        Option_8019C824(&D_menu_801AED20[D_menu_801B91C0]);
        D_menu_801AED20[!D_menu_801B91C0] = 255.0f;

        sp74[0] = sp74[1] = 0xFFFFFFFF;

        for (i = 0; i < 2; i++) {
            if (D_menu_801B9330[i]) {
                sp74[i] = 1;
                sp7C[i] = 255;
                D_menu_801B9330[i]--;
            }
        }

        if (gGameFrameCount & sp74[1]) {
            sp7C[1] = D_menu_801AED20[1];
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, sp7C[1], sp7C[1], 255);
            TextureRect_8bIA(&gMasterDisp, D_OPT_8009980, 32, 12, D_menu_801AF094[1], D_menu_801AF0AC[1], 1.0f, 1.0f);
        }

        if (gGameFrameCount & sp74[0]) {
            sp7C[0] = D_menu_801AED20[0];
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, sp7C[0], sp7C[0], 255);
            TextureRect_8bIA(&gMasterDisp, D_OPT_8009B00, 40, 12, D_menu_801AF094[2], D_menu_801AF0AC[2], 1.0f, 1.0f);
        }
    }

    switch (D_menu_801B91CC) {
        case 0:
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

            for (i = 0; i < 9; i++) {
                TextureRect_8bIA(&gMasterDisp, D_OPT_8008DA0 + (160 * 2 * i), 160, 2, D_menu_801AF094[3],
                                 D_menu_801AF0AC[3] + (2.0f * i), 1.0f, 1.0f);
            }
            TextureRect_8bIA(&gMasterDisp, D_OPT_8008DA0 + 2880, 160, 1, D_menu_801AF094[3], D_menu_801AF0AC[3] + 18.0f,
                             1.0f, 1.0f);
            break;

        case 1:
        case 2:
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

            for (i = 0; i < 20; i++) {
                TextureRect_8bIA(&gMasterDisp, D_OPT_8009CE0 + (160 * 2 * i), 160, 2, D_menu_801AF094[4],
                                 D_menu_801AF0AC[4] + (2.0f * i), 1.0f, 1.0f);
            }
            TextureRect_8bIA(&gMasterDisp, D_OPT_8009CE0 + 6400, 160, 1, D_menu_801AF094[4], D_menu_801AF0AC[4] + 40.0f,
                             1.0f, 1.0f);
            break;

        case 3:
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 32, 32, 255);

            TextureRect_8bIA(&gMasterDisp, D_OPT_800B680, 144, 28, D_menu_801AF094[5], D_menu_801AF0AC[5], 1.0f, 1.0f);
            TextureRect_8bIA(&gMasterDisp, D_OPT_800B680 + 4032, 144, 13, D_menu_801AF094[5],
                             D_menu_801AF0AC[5] + 28.0f, 1.0f, 1.0f);
            break;
    }

    Option_8019B7D4();
}

static char* D_menu_801AF0C4[3] = { "P", "S", "F" };
static s32 D_menu_801AF0D0[3] = { 255, 0, 30 };
static s32 D_menu_801AF0DC[3] = { 30, 179, 30 };
static s32 D_menu_801AF0E8[3] = { 0, 67, 255 };

void Option_RankingInit(void) {
    Title_80188010();

    D_ctx_80178410 = 800;

    D_menu_801B91D0 = 1;
    D_menu_801B93E4 = 0;

    D_menu_801B91D4 = 114.0f;
    D_menu_801B91DC = 114.0f;

    D_menu_801B91D8 = -6.0f;
    D_menu_801B91E0 = -6.0f;

    D_menu_801B93E0 = 0;
    D_menu_801B8288 = 10;

    D_menu_801B9400.unk_0 = 0;
    D_menu_801B9400.unk_4 = 0;
    D_menu_801B9408.unk_0 = 0;
    D_menu_801B9408.unk_4 = 0;

    Option_80192598();
}

void Option_RankingUpdate(void) {
    Option_80196FC4();

    if (gControllerPress[gMainController].button & B_BUTTON) {
        AUDIO_PLAY_SFX(0x49000021, gDefaultSfxSource, 4);
        gDrawMode = DRAW_NONE;
        D_menu_801B9124 = 1000;
        D_menu_801B912C = 0;
        D_menu_801B9244 = 1;
    }
}

void Option_RankingDraw(void) {
    Option_RankingMenuDraw();
    Option_DrawMenuLabel();
}

void Option_80196FC4(void) {
    if (gControllerPress[gMainController].button & A_BUTTON) {
        AUDIO_PLAY_SFX(0x49000003, gDefaultSfxSource, 4);
        D_menu_801B93E0 ^= 1;
    }

    if (D_menu_801B93E0 != 0) {
        Option_8019715C();
        return;
    }

    Option_80197074();
}

void Option_80197074(void) {
    if (Option_8019C418(&D_menu_801B93E4, 9, 1, 0, 20, 5, 4, gMainController, &D_menu_801B9400)) {
        AUDIO_PLAY_SFX(0x49000002, gDefaultSfxSource, 4);
        D_menu_801B91D4 = 114.0f - D_menu_801B93E4 * 130.0f;
        D_menu_801B91DC = 114.0f - D_menu_801B93E4 * 130.0f;
        D_menu_801B91D8 = -6.0f + D_menu_801B93E4 * 130.0f;
        D_menu_801B91E0 = -6.0f + D_menu_801B93E4 * 130.0f;
    }
}

void Option_8019715C(void) {
    s32 pad;
    f32 sp30;
    f32 temp_fv0_2;
    s32 temp;
    s32 temp2;

    if (D_menu_801B91D0 != 0) {
        if (Option_8019C418(&D_menu_801B93E4, 9, 1, 1, 20, 2, 9, gMainController, &D_menu_801B9408) != 0.00f) {
            AUDIO_PLAY_SFX(0x49000002, gDefaultSfxSource, 4);
            D_menu_801B91DC = 114.0f - D_menu_801B93E4 * 130.0f;
            D_menu_801B91E0 = -6.0f + D_menu_801B93E4 * 130.0f;
            D_menu_801B91D0 = 0;
        }
    } else {
        sp30 = Math_SmoothStepToF(&D_menu_801B91D8, D_menu_801B91E0, 0.5f, 100.0f, 1.0f);
        temp_fv0_2 = Math_SmoothStepToF(&D_menu_801B91D4, D_menu_801B91DC, 0.5f, 100.0f, 1.0f);
        if ((sp30 == 0.0f) && (temp_fv0_2 == 0.0f)) {
            D_menu_801B91D0 = 1;
        }
    }

    temp = D_menu_801B91D4;
    temp2 = D_menu_801B91D8;

    D_menu_801B91D4 = temp;
    D_menu_801B91D8 = temp2;

    if (D_menu_801B91D4 >= 114.0f) {
        D_menu_801B91D4 = 114.0f;
    }
    if (D_menu_801B91D4 <= -1056.0f) {
        D_menu_801B91D4 = -1056.0f;
    }
    if (D_menu_801B91D8 <= -6.0f) {
        D_menu_801B91D8 = -6.0f;
    }
    if (D_menu_801B91D8 >= 1164.0f) {
        D_menu_801B91D8 = 1164.0f;
    }
}

void Option_RankingMenuDraw(void) {
    s32 temp_t0;

    if (D_menu_801B93E0 != 0) {
        Option_8019752C();
    } else {
        Title_80187E28();
        RCP_SetupDL(&gMasterDisp, 0x53);
        Option_8019C824(&D_menu_801B93F0);
        temp_t0 = D_menu_801B93F0;
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, temp_t0, temp_t0, 255);
        TextureRect_8bIA(&gMasterDisp, D_VS_MENU_7004010, 8, 8, 70.0f, (D_menu_801B93E4 * 17.0f) + 55.0f, 1.0f, 1.0f);
    }
    RCP_SetupDL(&gMasterDisp, 0x53);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);
    Graphics_DisplaySmallText(242, 215, 1.0f, 1.0f, "PUSH A");
}

void Option_8019752C(void) {
    f32 var_fs0;
    f32 var_fs1;
    s32 temp_a0;
    s32 i;
    static f32 D_menu_801AF0F4 = 130.0f;
    static f32 D_menu_801AF0F8[] = { 48.0f, 175.0f };

    var_fs0 = D_menu_801B91D4;
    var_fs1 = D_menu_801B91D8;

    for (i = 0; i < 10; i++) {
        if ((var_fs0 > 69.0f) && (var_fs0 < 230.0f)) {
            Option_80197A3C(i, 41, var_fs0);
            Option_80197D30(i, 75, var_fs0 - 25.0f);
            Option_80197DE4(i, 130, (var_fs0 - 26.0f));
            Map_801AD7EC(210, (var_fs0 - 24.0f), gSaveFile.save.data.unk_40[i]);
            Option_80197F74(i, 258, var_fs0 - 25.0f);
        }
        Option_80198164(i, var_fs0, var_fs1);
        var_fs0 += D_menu_801AF0F4;
        var_fs1 -= D_menu_801AF0F4;
    }

    Option_8019BDF0();
    Option_80197914();

    Matrix_Pop(&gGfxMatrix);
    RCP_SetupDL(&gMasterDisp, 0x4C);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    TextureRect_8bIA(&gMasterDisp, D_OPT_800D170, 8, 16, 0.0f, D_menu_801AF0F8[0], 40.0f, 1.5f);
    TextureRect_8bIA_MirY(&gMasterDisp, D_OPT_800D170, 8, 16, 0.0f, D_menu_801AF0F8[1], 40.0f, 1.5f);

    func_bg_8003DE68(0, 70);
    func_bg_8003DE68(170, 239);
    RCP_SetupDL(&gMasterDisp, 0x53);

    if (D_menu_801B91D4 >= 114.0f) {
        gDPSetPrimColor(gMasterDisp++, 0, 0, 32, 32, 32, 255);
    } else {
        Option_8019C824(&D_menu_801B93F4);
        temp_a0 = D_menu_801B93F4;
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, temp_a0, temp_a0, 255);
    }

    TextureRect_8bIA(&gMasterDisp, D_OPT_800D070, 16, 16, 150.0f, 44.0f, 1.0f, 1.0f);

    if (D_menu_801B91D4 <= -1055.0f) {
        gDPSetPrimColor(gMasterDisp++, 0, 0, 32, 32, 32, 255);
    } else {
        Option_8019C824(&D_menu_801B93F8);
        temp_a0 = D_menu_801B93F8;
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, temp_a0, temp_a0, 255);
    }

    TextureRect_8bIA_MirY(&gMasterDisp, D_OPT_800D070, 16, 16, 150.0f, 200.0f, 1.0f, 1.0f);
}

static Vec3f D_menu_801AF100[2] = { { 0.0f, 167.0f, 0.0f }, { 0.0f, -167.0f, 0.0f } };
static Vec3f D_menu_801AF118[2] = { { 25.0f, 3.6f, 0.0f }, { 25.0f, 3.6f, 0.0f } };

void Option_80197914(void) {
    Vec3f* vec1;
    Vec3f* vec2;
    s32 i;

    RCP_SetupDL(&gMasterDisp, 0);

    for (i = 0, vec1 = D_menu_801AF100, vec2 = D_menu_801AF118; i < 2; i++, vec1++, vec2++) {
        Matrix_Push(&gGfxMatrix);
        Matrix_Translate(gGfxMatrix, vec1->x, vec1->y, -500.0f, 1);
        Matrix_Scale(gGfxMatrix, vec2->x, vec2->y, 1.0f, 1);
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, D_menu_801AEF30);
        Matrix_Pop(&gGfxMatrix);
    }
}

void Option_80197A3C(s32 arg0, s32 arg1, s32 arg2) {
    RCP_SetupDL(&gMasterDisp, 0x53);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    if (arg0 != 9) {
        TextureRect_8bIA(&gMasterDisp, D_menu_801AECF8[arg0 + 1], 16, 15, arg1, arg2 - 25.0f, 1.0f, 1.0f);
    } else {
        TextureRect_8bIA(&gMasterDisp, D_500A050, 16, 15, arg1 - 14.0f, arg2 - 25.0f, 1.0f, 1.0f);
        TextureRect_8bIA(&gMasterDisp, D_5009F60, 16, 15, arg1, arg2 - 25.0f, 1.0f, 1.0f);
    }

    RCP_SetupDL(&gMasterDisp, 0x55);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    switch (arg0) {
        case 0:
            TextureRect_4bCI(&gMasterDisp, D_OPT_8003A70, D_OPT_8003AB8, 16, 9, arg1 + 17.0f, arg2 - 19.0f, 1.0f, 1.0f);
            break;

        case 1:
            TextureRect_4bCI(&gMasterDisp, D_OPT_80038E0, D_OPT_8003930, 16, 10, arg1 + 17.0f, arg2 - 19.0f, 1.0f,
                             1.0f);
            break;

        case 2:
            TextureRect_4bCI(&gMasterDisp, D_OPT_8003950, D_OPT_80039A8, 16, 11, arg1 + 17.0f, arg2 - 20.0f, 1.0f,
                             1.0f);
            break;

        default:
            TextureRect_4bCI(&gMasterDisp, D_OPT_8003AE0, D_OPT_8003B28, 16, 9, arg1 + 17.0f, arg2 - 19.0f, 1.0f, 1.0f);
            break;
    }
}

void Option_80197D30(s32 arg0, s32 arg1, s32 arg2) {
    char temp[4];

    RCP_SetupDL(&gMasterDisp, 0x53);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);

    temp[0] = gSaveFile.save.data.unk_18[arg0][0] & 0xFF;
    temp[1] = gSaveFile.save.data.unk_18[arg0][1] & 0xFF;
    temp[2] = gSaveFile.save.data.unk_18[arg0][2] & 0xFF;
    temp[3] = '\0';

    Graphics_DisplayLargeText(arg1, arg2, 1.0f, 1.0f, temp);
}

void Option_80197DE4(s32 arg0, s32 arg1, s32 arg2) {
    RCP_SetupDL(&gMasterDisp, 0x53);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 60, 60, 255, 170);
    TextureRect_8bIA(&gMasterDisp, D_MAP_601B4B0, 24, 17, arg1, arg2, 3.17f, 1.05f);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);
    Graphics_DisplaySmallText(arg1, arg2, 1.0f, 1.0f, "TOTAL HITS");
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
    Graphics_DisplaySmallNumber((arg1 + 40.0f) - ((func_hud_8008BCBC(D_menu_801B8220[arg0]) * 8) - 8), (arg2 + 9.0f),
                                D_menu_801B8220[arg0]);
}

void Option_80197F74(s32 arg0, s32 arg1, s32 arg2) {
    f32 temp_fs1;
    s32 i;

    RCP_SetupDL(&gMasterDisp, 0x53);

    for (temp_fs1 = 0.0f, i = 0; i < 3; i++, temp_fs1 += 12.0f) {
        gDPSetPrimColor(gMasterDisp++, 0, 0, D_menu_801AF0D0[i], D_menu_801AF0DC[i], D_menu_801AF0E8[i], 255);
        Graphics_DisplaySmallText(temp_fs1 + arg1, arg2, 1.0f, 1.0f, D_menu_801AF0C4[i]);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
        Graphics_DisplaySmallNumber(arg1 + temp_fs1 - ((func_hud_8008BCBC(D_menu_801B81A8[arg0][i]) - 1) * 8),
                                    arg2 + 9.0f, D_menu_801B81A8[arg0][i]);
    }
}

void Option_80198164(s32 arg0, f32 arg1, f32 arg2) {
    f32 temp = 16.0f;
    s32 temp_s2 = gSaveFile.save.data.unk_36[arg0];
    f32 var_fs2;
    s32 i;

    for (var_fs2 = 0.0f, i = 0; i < 7; i++, var_fs2 += 24.0f + temp) {
        Option_801982B0(arg0, i, 28.0f + var_fs2, arg1, temp_s2);
        if (i < temp_s2) {
            Option_8019882C(arg0, i, 28.0f + var_fs2, arg1);
            Option_801984D0(arg0, i, 28.0f + var_fs2, arg1);
            Option_80198608(arg0, i, 28.0f + var_fs2, arg1);
        }
    }

    if ((arg2 < 75.0f) && (arg2 > -80.0f)) {
        Option_8019896C(arg0, arg2, temp_s2);
    }
}

void Option_801982B0(s32 arg0, s32 arg1, f32 arg2, f32 arg3, s32 arg4) {
    s32 r;
    s32 g;
    s32 b;
    s32 temp_v0;
    PlanetId start;
    PlanetId end;

    if ((arg3 > 30.0f) && (arg3 < 200.0f)) {
        RCP_SetupDL(&gMasterDisp, 0x4C);
        if (arg1 < 6) {
            b = 255;
            g = 255;
            r = 255;
            if (arg1 < (arg4 - 1)) {
                start = gSaveFile.save.data.unk_5E[arg0][arg1].unk_8 & 0xF;
                end = gSaveFile.save.data.unk_5E[arg0][arg1 + 1].unk_8 & 0xF;

                temp_v0 = Option_80199284(start, end);

                g = 255;
                b = 255;
                r = 255;

                switch (temp_v0) {
                    case 0:
                        r = 16;
                        g = 64;
                        break;

                    case 1:
                    case 3:
                        g = 175;
                        b = 0;
                        break;

                    case 2:
                    case 4:
                        b = 0;
                        g = 0;
                        break;
                }
            }
            gDPSetPrimColor(gMasterDisp++, 0, 0, r, g, b, 255);
            TextureRect_16bRGBA(&gMasterDisp, D_MAP_60447A0, 8, 8, arg2 + 24.0f, arg3 + 11.0f, 2.0f, 0.2f);
        }
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
        TextureRect_16bRGBA(&gMasterDisp, D_MAP_6047550, 24, 24, arg2, arg3, 1.0f, 1.0f);
    }
}

void Option_801984D0(s32 arg0, s32 arg1, f32 arg2, f32 arg3) {
    s32 sp1C;

    if ((arg3 > 22.0f) && (arg3 < 162.0f)) {
        RCP_SetupDL(&gMasterDisp, 0x53);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);
        sp1C = (gSaveFile.save.data.unk_5E[arg0][arg1].unk_C & 1) << 8;
        sp1C |= gSaveFile.save.data.unk_5E[arg0][arg1].unk_0;
        Graphics_DisplaySmallNumber(arg2 + 15.0f - (func_hud_8008BCBC(sp1C) - 1) * 8, arg3 + 24.0f + 1.0f, sp1C);
    }
}

void Option_80198608(s32 arg0, s32 arg1, f32 arg2, f32 arg3) {
    f32 var_fs1;
    s32 sp90[3];
    s32 i;

    if ((arg3 > 12.0f) && (arg3 < 154.0f)) {
        RCP_SetupDL(&gMasterDisp, 0x53);

        sp90[0] = gSaveFile.save.data.unk_5E[arg0][arg1].unk_D & 1;
        sp90[1] = gSaveFile.save.data.unk_5E[arg0][arg1].unk_F & 1;
        sp90[2] = gSaveFile.save.data.unk_5E[arg0][arg1].unk_E & 1;

        for (var_fs1 = 0.0f, i = 0; i < 3; i++, var_fs1 += 9.0f) {
            if (sp90[i] == 0) {
                continue;
            }
            gDPSetPrimColor(gMasterDisp++, 0, 0, D_menu_801AF0D0[i], D_menu_801AF0DC[i], D_menu_801AF0E8[i], 255);
            Graphics_DisplaySmallText(arg2 + var_fs1 - 1.0f, arg3 + 24.0f + 8.0f + 1.0f, 1.0f, 1.0f,
                                      D_menu_801AF0C4[i]);
        }
    }
}

void Option_8019882C(s32 arg0, s32 arg1, f32 arg2, f32 arg3) {
    PlanetId temp;
    char* sp20;
    f32 temp2;

    if ((arg3 > 58.0f) && (arg3 < 197.0f)) {
        temp = gSaveFile.save.data.unk_5E[arg0][arg1].unk_8 & 0xF;
        sp20 = D_menu_801AEEAC[temp];
        RCP_SetupDL(&gMasterDisp, 0x53);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);
        temp2 = Graphics_GetSmallTextWidth(sp20) / 2.0f;
        Graphics_DisplaySmallText(arg2 + 12.0f - temp2, arg3 - 8.0f, 1.0f, 1.0f, sp20);
    }
}

void Option_8019896C(s32 arg0, f32 y, s32 arg2) {
    static f32 D_menu_801AF130 = 0.0f;
    static f32 D_menu_801AF134 = -121.0f;
    static f32 D_menu_801AF138 = 40.1f;
    s32 i;
    PlanetId planet;
    s32 spFC;
    s32 spF4;
    f32 x;
    s32 pad[2];

    Matrix_Push(&gGfxMatrix);
    Matrix_LookAt(gGfxMatrix, 0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1);
    Matrix_SetGfxMtx(&gMasterDisp);

    Lib_InitOrtho(&gMasterDisp);

    spFC = gSaveFile.save.data.unk_4A[arg0];
    for (x = D_menu_801AF134, i = 0; i < arg2; i++, x += D_menu_801AF138) {
        planet = gSaveFile.save.data.unk_5E[arg0][i].unk_8 & 0xF;

        switch (planet) {
            case SAVE_SLOT_SOLAR:
                RCP_SetupDL(&gMasterDisp, 0x43);

                gDPSetPrimColor(gMasterDisp++, 0, 0, 240, 0, 0, 255);
                gDPSetEnvColor(gMasterDisp++, 31, 0, 0, 0);

                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, x, y, 0.0f, 1);
                Matrix_RotateZ(gGfxMatrix, M_DTOR * D_menu_801AF130, 1);
                Matrix_Scale(gGfxMatrix, 0.3f, 0.3f, 0.3f, 1);
                Matrix_SetGfxMtx(&gMasterDisp);

                gSPDisplayList(gMasterDisp++, D_menu_801AEE6C[planet]);
                gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 128);
                gDPSetEnvColor(gMasterDisp++, 31, 0, 0, 0);
                Matrix_Scale(gGfxMatrix, 0.8f, 0.8f, 0.8f, 1);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_menu_801AEE6C[planet]);
                Matrix_Pop(&gGfxMatrix);
                break;

            case PLANET_METEO:
                RCP_SetupDL(&gMasterDisp, 0x3E);

                gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, x - 1.0f, y + 4.0f, 0.0f, 1);
                Matrix_Scale(gGfxMatrix, 0.3f, 0.3f, 0.3f, 1);
                Matrix_SetGfxMtx(&gMasterDisp);

                gSPDisplayList(gMasterDisp++, D_menu_801AEE6C[planet]);

                Matrix_Translate(gGfxMatrix, 18.0f, -20.0f, 0.0f, 1);
                Matrix_SetGfxMtx(&gMasterDisp);

                gSPDisplayList(gMasterDisp++, D_menu_801AEE6C[planet]);

                Matrix_Pop(&gGfxMatrix);
                break;

            case PLANET_SECTOR_X:
            case PLANET_SECTOR_Y:
            case PLANET_SECTOR_Z:
                RCP_SetupDL(&gMasterDisp, 0x3E);

                gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 144);

                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, x, y, 0.0f, 1);
                Matrix_Scale(gGfxMatrix, 0.3f, 0.3f, 0.3f, 1);
                Matrix_SetGfxMtx(&gMasterDisp);

                gSPDisplayList(gMasterDisp++, D_menu_801AEE6C[planet]);

                Matrix_Pop(&gGfxMatrix);
                break;

            case PLANET_BOLSE:
                RCP_SetupDL(&gMasterDisp, 0x17);
                Lights_SetOneLight(&gMasterDisp, 0, 0, 100, 100, 100, 70, 100, 100, 100);

                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, x, y, 0.0f, 1);
                Matrix_RotateX(gGfxMatrix, M_DTOR * 20.0f, 1);
                Matrix_Scale(gGfxMatrix, 0.01f, 0.01f, 0.01f, 1);
                Matrix_SetGfxMtx(&gMasterDisp);

                gSPDisplayList(gMasterDisp++, D_menu_801AEE6C[planet]);

                Matrix_Pop(&gGfxMatrix);
                break;

            case PLANET_AREA_6:
                RCP_SetupDL(&gMasterDisp, 0x17);
                Lights_SetOneLight(&gMasterDisp, 0, 0, 100, 100, 100, 70, 100, 100, 100);

                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, x, y, 0.0f, 1);
                Matrix_RotateX(gGfxMatrix, M_DTOR * 20.0f, 1);
                Matrix_Scale(gGfxMatrix, 0.01f, 0.01f, 0.01f, 1);
                Matrix_SetGfxMtx(&gMasterDisp);

                gSPDisplayList(gMasterDisp++, D_menu_801AEE6C[planet]);

                Matrix_Pop(&gGfxMatrix);
                break;

            default:
                RCP_SetupDL(&gMasterDisp, 0x3E);

                gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, x, y, 0.0f, 1);
                Matrix_Scale(gGfxMatrix, 0.3f, 0.3f, 0.3f, 1);
                Matrix_SetGfxMtx(&gMasterDisp);

                gSPDisplayList(gMasterDisp++, D_menu_801AEE6C[planet]);

                if ((planet != SAVE_SLOT_VENOM_1) && (planet != SAVE_SLOT_VENOM_2) && (planet != PLANET_AQUAS)) {
                    if (planet == PLANET_MACBETH) {
                        gDPSetPrimColor(gMasterDisp++, 0, 0, 64, 64, 64, 255);
                    } else {
                        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
                    }
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_menu_801B4A40);
                }
                Matrix_Scale(gGfxMatrix, 1.6f, 1.6f, 1.6f, 1);
                Matrix_SetGfxMtx(&gMasterDisp);

                gSPDisplayList(gMasterDisp++, D_MAP_605C230);

                Matrix_Pop(&gGfxMatrix);
                break;
        }

        spF4 = (spFC >> i) & 1;
        if (spF4 != 0) {
            Option_80199198(x, y, 0.0f);
        }
    }

    Matrix_Pop(&gGfxMatrix);

    Option_80192738();

    D_menu_801AF130 += 0.1f;

    Lib_InitPerspective(&gMasterDisp);
}

static f32 D_menu_801AF13C = 0.7f;
static f32 D_menu_801AF140 = 11.0f;
static f32 D_menu_801AF144 = 2.7f;

void Option_80199198(f32 arg0, f32 arg1, f32 arg2) {
    RCP_SetupDL(&gMasterDisp, 0x35);
    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, arg0 - D_menu_801AF140, arg1 + D_menu_801AF144, arg2, 1);
    Matrix_Scale(gGfxMatrix, D_menu_801AF13C, D_menu_801AF13C, D_menu_801AF13C, 1);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_MAP_601D1F0);
    Matrix_Pop(&gGfxMatrix);
}

s32 Option_80199284(PlanetId start, PlanetId end) {
    s32 i;

    for (i = 0; i < 24; i++) {
        if ((D_menu_801AED4C[i].unk_0 == start) && (D_menu_801AED4C[i].unk_4 == end)) {
            break;
        }
    }

    return D_menu_801AED4C[i].unk_8;
}

void Option_VersusMenuInit(void) {
    s32 i;

    if (D_menu_801B91C4) {
        AUDIO_PLAY_BGM(SEQ_ID_VS_MENU);
    }

    D_menu_801B93D0 = D_menu_801B9124;

    if (D_game_800D2870) {
        sOptionCardList[1].unk_00.unk_1C = 129.0f;
        sOptionCardList[1].unk_38.unk_04 = -7.5f;
    }

    D_ctx_801778A4 = 3;

    D_menu_801B9340 = 2;

    D_game_80161A28 = 0;
    D_ctx_80178410 = 0;

    D_menu_801B93C4 = 0;

    for (i = 0; i < 4; i++) {
        gPlayerInactive[i] = false;
        if (gControllerPlugged[i] == 0) {
            gPlayerInactive[i] = true;
            D_menu_801B93C4 |= 1 << i;
        }
        D_menu_801B9358[i] = 255.0f;
        D_menu_801B93A0[i].unk_0 = 0;
        D_menu_801B93A0[i].unk_4 = 0;
    }

    D_menu_801B91E8 = 255.0f;
}

void Option_VersusMenuUpdate(void) {
    switch (D_menu_801B912C) {
        case 0:
            Option_8019949C();
            break;

        case 1:
            if (D_menu_801B91EC == 0.0f) {
                D_menu_801B9124 = 2000;
                Option_InitEntry();
            }
            break;
    }
}

void Option_8019949C(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (!(D_menu_801B93C4 & (1 << i))) {
            Option_8019C824(&D_menu_801B9358[i]);
            if (Option_8019C418(&D_menu_801AED3C[i], 2, 0, 0, 20, 2, 4, i, &D_menu_801B93A0[i])) {
                AUDIO_PLAY_SFX(0x49000002, gDefaultSfxSource, 4);
            }
        }

        if (gControllerPress[i].button & A_BUTTON) {
            if (D_menu_801B93C4 == 15) {
                AUDIO_PLAY_SFX(0x49000003, gDefaultSfxSource, 4);
                D_menu_801B91EC = 10;
                D_menu_801B912C++;
                break;
            } else {
                if (!(D_menu_801B93C4 & (1 << i))) {
                    AUDIO_PLAY_SFX(0x49000003, gDefaultSfxSource, 4);
                    gHandicap[i] = D_menu_801AED3C[i];
                    D_menu_801B9358[i] = 255.0f;
                    D_menu_801B9348[i] = 10;
                    D_menu_801B93C4 = D_menu_801B93C4 | (1 << i);
                }
            }
        }

        if (gControllerPress[i].button & B_BUTTON) {
            if (D_menu_801B93C4 & (1 << i)) {
                AUDIO_PLAY_SFX(0x4900101D, gDefaultSfxSource, 4);
                D_menu_801B93C4 &= (1 << i) ^ 15;
            } else {
                AUDIO_PLAY_BGM(SEQ_ID_MENU);
                AUDIO_PLAY_SFX(0x49000021, gDefaultSfxSource, 4);
                Option_8019B8A0(2);
                D_menu_801B9248 = 1;
                break;
            }
        }
    }
}

void Option_VersusMenuDraw(void) {
    s32 i;

    Option_8019B8C8();
    Option_80199EA8();

    for (i = 0; i < 4; i++) {
        if (gControllerPlugged[i] == 1) {
            Option_80199820(i);
        }
    }

    if (D_menu_801B93C4 == 15) {
        Option_8019B5AC();
    }
}

static f32 D_menu_801AF148[4] = { 30.0f, 214.0f, 30.0f, 215.0f };
static f32 D_menu_801AF158[4] = { 18.0f, 18.0f, 151.0f, 151.0f };
static s32 D_menu_801AF168[4] = { 56, 48, 56, 48 };
static s32 D_menu_801AF178[4] = { 8, 10, 10, 8 };
static f32 D_menu_801AF188[4] = { 12.0f, 16.0f, 12.0f, 18.0f };
static f32 D_menu_801AF198 = -1.0f;
static f32 D_menu_801AF19C[4] = { 46.0f, 41.0f, 41.0f, 41.0f };
static f32 D_menu_801AF1AC = 24.0f;
static f32 D_menu_801AF1B0 = 1.4f;
static f32 D_menu_801AF1B4 = 5.0f;
static f32 D_menu_801AF1B8 = 11.0f;
static f32 D_menu_801AF1BC = 8.0f;
static f32 D_menu_801AF1C0 = 45.0f;
static f32 D_menu_801AF1C4 = 20.0f;
static f32 D_menu_801AF1C8 = 55.0f;
static f32 D_menu_801AF1CC = 37.0f;
static f32 D_menu_801AF1D0 = 11.0f;
static f32 D_menu_801AF1D4 = 7.0f;
static f32 D_menu_801AF1D8 = 59.0f;
static f32 D_menu_801AF1DC = 58.0f;

void Option_80199820(s32 arg0) {
    s32 var_v0;
    s32 var_a2;
    s32 colorGB;
    s32 i;
    static u8* D_menu_801AF1E0[3] = {
        D_VS_MENU_70030B0,
        D_VS_MENU_7003290,
        D_VS_MENU_7003470,
    };
    static u8* D_menu_801AF1EC[4] = {
        D_VS_MENU_70049C0,
        D_VS_MENU_7004BB0,
        D_VS_MENU_7004DC0,
        D_VS_MENU_7005020,
    };
    static u16* D_menu_801AF1FC[4] = {
        D_VS_MENU_7004B80,
        D_VS_MENU_7004D90,
        D_VS_MENU_7004FF0,
        D_VS_MENU_70051A0,
    };
    static u16* D_menu_801AF20C[4] = {
        D_VS_MENU_7008EE0,
        D_VS_MENU_700AD20,
        D_VS_MENU_700CB60,
        D_VS_MENU_70070A0,
    };
    static u8* D_menu_801AF21C[4] = {
        D_VS_MENU_7000000,
        D_VS_MENU_70000D0,
        D_VS_MENU_7000210,
        D_VS_MENU_7000350,
    };
    static s32 D_menu_801AF22C[4] = { 177, 255, 0, 30 };
    static s32 D_menu_801AF23C[4] = { 242, 30, 255, 30 };
    static s32 D_menu_801AF24C[4] = { 12, 0, 67, 255 };

    RCP_SetupDL(&gMasterDisp, 0x55);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    TextureRect_4bCI(&gMasterDisp, D_VS_MENU_70118E0, D_VS_MENU_70123F8, 80, 71, D_menu_801AF148[arg0],
                     D_menu_801AF158[arg0], 1.0f, 1.0f);

    gDPSetPrimColor(gMasterDisp++, 0, 0, D_menu_801AF22C[arg0], D_menu_801AF23C[arg0], D_menu_801AF24C[arg0], 255);

    TextureRect_8bCI(&gMasterDisp, D_menu_801AF1EC[arg0], D_menu_801AF1FC[arg0], D_menu_801AF168[arg0],
                     D_menu_801AF178[arg0], D_menu_801AF148[arg0] + D_menu_801AF188[arg0],
                     D_menu_801AF158[arg0] + D_menu_801AF198, 1.0f, 1.0f);

    RCP_SetupDL(&gMasterDisp, 0x53);

    var_v0 = 0xFFFFFFFF;
    if (D_menu_801B9348[arg0] != 0) {
        var_v0 = 1;
        D_menu_801B9348[arg0]--;
    }

    if (gGameFrameCount & var_v0) {
        colorGB = D_menu_801B9358[arg0];

        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, colorGB, colorGB, 255);

        TextureRect_8bIA(&gMasterDisp, D_VS_MENU_7001030, 64, 9, D_menu_801AF148[arg0] + D_menu_801AF1BC,
                         D_menu_801AF158[arg0] + D_menu_801AF1C0, 1.0f, 1.0f);

        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, colorGB, colorGB, 255);

        TextureRect_8bIA(&gMasterDisp, D_menu_801AF1E0[D_menu_801AED3C[arg0]], 40, 12,
                         D_menu_801AF148[arg0] + D_menu_801AF1C4, D_menu_801AF158[arg0] + D_menu_801AF1C8, 1.0f, 1.0f);
    }

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    TextureRect_8bIA_MirX(&gMasterDisp, D_OPT_800E130, 8, 8, D_menu_801AF148[arg0] + D_menu_801AF1D4,
                          D_menu_801AF158[arg0] + D_menu_801AF1DC, 1.0f, 1.0f);

    TextureRect_8bIA(&gMasterDisp, D_OPT_800E130, 8, 8, D_menu_801AF148[arg0] + D_menu_801AF1D8,
                     D_menu_801AF158[arg0] + D_menu_801AF1DC, 1.0f, 1.0f);

    TextureRect_8bIA(&gMasterDisp, D_VS_MENU_7000F10, 40, 7, D_menu_801AF148[arg0] + D_menu_801AF1CC,
                     D_menu_801AF158[arg0] + D_menu_801AF1D0, 1.0f, 1.0f);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    TextureRect_16bRGBA(&gMasterDisp, D_menu_801AF20C[arg0], 44, 44, D_menu_801AF148[arg0] + D_menu_801AF1B4,
                        D_menu_801AF158[arg0] + D_menu_801AF1B8, 0.7f, 0.7f);

    var_a2 = 24;
    if (arg0 == 0) {
        var_a2 = 16;
    }

    gDPSetPrimColor(gMasterDisp++, 0, 0, D_menu_801AF22C[arg0], D_menu_801AF23C[arg0], D_menu_801AF24C[arg0], 255);

    TextureRect_8bIA(&gMasterDisp, D_menu_801AF21C[arg0], var_a2, 13, D_menu_801AF148[arg0] + D_menu_801AF19C[arg0],
                     D_menu_801AF158[arg0] + D_menu_801AF1AC, D_menu_801AF1B0, D_menu_801AF1B0);
}

void Option_80199EA8(void) {
    s32 i;

    RCP_SetupDL_76();

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
    TextureRect_16bRGBA(&gMasterDisp, D_VS_MENU_700E9A0, 144, 42, 87.0f, 84, 1.0f, 1.0f);
}

void Option_VersusStageInit(void) {
    s32 i;

    D_ctx_80178410 = 0;
    D_menu_801B933C = 0;
    D_menu_801B91E8 = 255.0f;
    D_menu_801B93D4 = D_ctx_801778A4 - 1;
    D_menu_801B93D8 = D_game_80161A28;
    D_menu_801B93DC = D_menu_801B9340;
    D_ctx_801778C8 = D_menu_801B93DC;
    // clang-format off
    for (i = 0; i < 4; i++) {\
        D_menu_801B9358[i] = 0;
    }
    // clang-format on
    D_menu_801B936C = 0;
    D_menu_801B9374 = 0;
    D_menu_801B937C = 0;
    D_menu_801B91EC = 0;
    D_menu_801B91F0 = 0;
    D_menu_801B9368 = 255.0f;
    D_menu_801B9370 = 255.0f;
    D_menu_801B9378 = 255.0f;
    Option_8019A080();
}

// D_menu_801B9380 needs to be static but belongs to bss section?
void Option_8019A080(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        D_menu_801B9380[i].unk_0 = 0;
        D_menu_801B9380[i].unk_4 = 0;
    }
}

void Option_VersusStageUpdate(void) {
    switch (D_menu_801B93D0) {
        case OPTION_POINT_MATCH:
            Option_8019A124();
            break;

        case OPTION_BR_MATCH:
            Option_8019A1A8();
            break;

        case OPTION_TT_MATCH:
            Option_8019A214();
            break;
    }
}

void Option_8019A124(void) {
    switch (D_menu_801B912C) {
        case 0:
            Option_8019A2E0();
            break;

        case 1:
            Option_8019A6DC();
            break;

        case 2:
            Option_8019A954();
            break;

        case 3:
            Option_8019A298();
            break;
    }
}

void Option_8019A1A8(void) {
    switch (D_menu_801B912C) {
        case 0:
            Option_8019A6DC();
            break;

        case 1:
            Option_8019A954();
            break;

        case 2:
            Option_8019A298();
            break;
    }
}

void Option_8019A214(void) {
    switch (D_menu_801B912C) {
        case 0:
            Option_8019A4DC();
            break;
        case 1:
            Option_8019A6DC();
            break;
        case 2:
            Option_8019A954();
            break;
        case 3:
            Option_8019A298();
            break;
    }
}

void Option_8019A298(void) {
    if (D_menu_801B91EC == 0.0f) {
        gGameState = GSTATE_VS_INIT;
        gNextGameStateTimer = 2;
        gOptionMenuStatus = OPTION_WAIT;
        gDrawMode = DRAW_NONE;
    }
}

void Option_8019A2E0(void) {
    s32 i;

    if (D_menu_801B936C != 0) {
        return;
    }

    if (D_menu_801B91F0) {
        D_menu_801B912C++;
        D_menu_801B91F0 = 0;
        return;
    }

    for (i = 0; i < 4; i++) {
        if (gControllerPlugged[i] == 0) {
            continue;
        }

        if (Option_8019C418(&D_menu_801B93D4, 4, 0, 0, 20, 2, 4, i, &D_menu_801B9380[i])) {
            AUDIO_PLAY_SFX(0x49000002, gDefaultSfxSource, 4);
            D_ctx_801778A4 = D_menu_801B93D4 + 1;
        }

        if (gControllerPress[i].button & A_BUTTON) {
            AUDIO_PLAY_SFX(0x49000003, gDefaultSfxSource, 4);
            Option_8019A080();
            D_menu_801B936C = 10;
            break;
        }

        if (gControllerPress[i].button & B_BUTTON) {
            AUDIO_PLAY_SFX(0x4900101D, gDefaultSfxSource, 4);
            D_menu_801B9124 = D_menu_801B93D0;
            D_menu_801B91C4 = 0;
            Option_InitEntry();
            break;
        }
    }
}

void Option_8019A4DC(void) {
    s32 i;

    if (D_menu_801B937C) {
        return;
    }

    if (D_menu_801B91F0) {
        D_menu_801B912C++;
        D_menu_801B91F0 = 0;
        return;
    }

    for (i = 0; i < 4; i++) {
        if (gControllerPlugged[i] == 0) {
            continue;
        }

        if (Option_8019C418(&D_menu_801B93DC, 4, 0, 0, 20, 2, 4, i, &D_menu_801B9380[i])) {
            AUDIO_PLAY_SFX(0x49000002, gDefaultSfxSource, 4);
            D_menu_801B9340 = D_menu_801B93DC;
            D_ctx_801778C8 = D_menu_801B93DC;
        }

        if (gControllerPress[i].button & A_BUTTON) {
            AUDIO_PLAY_SFX(0x49000003, gDefaultSfxSource, 4);
            Option_8019A080();
            D_menu_801B937C = 10;
            break;
        }

        if (gControllerPress[i].button & B_BUTTON) {
            AUDIO_PLAY_SFX(0x4900101D, gDefaultSfxSource, 4);
            D_menu_801B9124 = D_menu_801B93D0;
            D_menu_801B91C4 = 0;
            Option_InitEntry();
            break;
        }
    }
}

void Option_8019A6DC(void) {
    s32 i;

    if (D_menu_801B9374) {
        return;
    }

    if (D_menu_801B91F0) {
        D_menu_801B933C = 1;
        D_menu_801B91F0 = 0;
        D_menu_801B912C++;
        return;
    }

    for (i = 0; i < 4; i++) {
        if (gControllerPlugged[i] == 0) {
            continue;
        }
        if (Option_8019C418(&D_menu_801B93D8, 1, 0, 1, 20, 2, 4, i, &D_menu_801B9380[i])) {
            AUDIO_PLAY_SFX(0x49000002, gDefaultSfxSource, 4);
            D_game_80161A28 = D_menu_801B93D8;
        }

        if (gControllerPress[i].button & A_BUTTON) {
            AUDIO_PLAY_SFX(0x49000003, gDefaultSfxSource, 4);
            if (D_game_80161A28 == 0) {
                gVersusStage = VS_STAGE_CORNERIA;
                if (D_menu_801B93D0 == 30) {
                    gVersusStage = VS_STAGE_KATINA;
                }
            } else {
                gVersusStage = VS_STAGE_SECTOR_Z;
            }

            D_menu_801B9374 = 10;
            Option_8019A080();
            break;
        }

        if (gControllerPress[i].button & B_BUTTON) {
            AUDIO_PLAY_SFX(0x4900101D, gDefaultSfxSource, 4);
            if (D_menu_801B93D0 == 20) {
                D_menu_801B9124 = D_menu_801B93D0;
                D_menu_801B91C4 = 0;
                Option_InitEntry();
            } else {
                Option_8019A080();
                D_menu_801B91F0 = 0;
                D_menu_801B912C--;
            }
            break;
        }
    }
}

void Option_8019A954(void) {
    s32 i;

    if (D_menu_801B91EC) {
        return;
    }

    if (D_menu_801B91F0) {

        D_menu_801B91F0 = 0;
        D_menu_801B912C++;
        return;
    }

    for (i = 0; i < 4; i++) {
        if (gControllerPlugged[i] == 0) {
            continue;
        }

        if (gControllerPress[i].button & A_BUTTON) {
            AUDIO_PLAY_SFX(0x49000003, gDefaultSfxSource, 4);
            D_menu_801B91EC = 10;
            break;
        }

        if (gControllerPress[i].button & B_BUTTON) {
            AUDIO_PLAY_SFX(0x4900101D, gDefaultSfxSource, 4);
            Option_8019A080();
            D_menu_801B933C = 0;
            D_menu_801B91F0 = 0;
            D_menu_801B912C--;
            break;
        }
    }
}

void Option_VersusStageDraw(void) {
    switch (D_menu_801B93D0) {
        case OPTION_BR_MATCH:
            break;

        case OPTION_POINT_MATCH:
            Option_8019AB30();
            break;

        case OPTION_TT_MATCH:
            Option_8019AD84();
            break;
    }

    Option_8019AFFC();

    if (D_menu_801B933C != 0) {
        Option_8019B5AC();
    }
}

void Option_8019AB30(void) {
    s32 pad[5];
    s32 colorGB;
    s32 sp44 = D_ctx_801778A4;
    s32 var_v0;

    RCP_SetupDL(&gMasterDisp, 0x53);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 60, 60, 255, 190);

    TextureRect_8bIA(&gMasterDisp, D_MAP_601B4B0, 24, 17, 94.0f, 43.0f, 5.0f, 1.1f);

    if (D_menu_801B912C == 0) {
        Option_8019B6D8(97.0f, 50.0f, 107.0f, 255, 255, 255);
        Option_8019C824(&D_menu_801B9368);
    } else {
        D_menu_801B9368 = 255.0f;
    }

    colorGB = D_menu_801B9368;

    var_v0 = 0xFFFFFFFF;

    if (D_menu_801B936C != 0) {
        colorGB = 255;
        var_v0 = 1;
        D_menu_801B936C--;
        if (D_menu_801B936C == 0) {
            D_menu_801B91F0 = 1;
        }
    }

    if (gGameFrameCount & var_v0) {
        RCP_SetupDL(&gMasterDisp, 0x53);

        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, colorGB, colorGB, 255);

        TextureRect_8bIA(&gMasterDisp, D_menu_801AECF8[sp44], 16, 15, 109.0f, 45.0f, 1.0f, 1.0f);

        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, colorGB, colorGB, 255);

        TextureRect_8bIA(&gMasterDisp, D_VS_MENU_7001DF0, 80, 10, 122.0f, 49.0f, 1.0f, 1.0f);
    }
}

void Option_8019AD84(void) {
    static f32 D_menu_801AF25C[6] = { 156.0f, 112.0f, 112.0f, 112.0f, 112.0f, 112.0f };
    static f32 D_menu_801AF274[6] = { 46.0f, 43.0f, 43.0f, 43.0f, 43.0f, 43.0f };
    static f32 D_menu_801B9324;
    static f32 D_menu_801B9328;
    static f32 D_menu_801B9338;
    s32 pad[2];
    s32 colorGB;
    s32 var_v0;

    static u8* sTimeTrialMinuteTextures[] = { D_VS_MENU_70024D0, D_VS_MENU_7002730, D_VS_MENU_7002990,
                                              D_VS_MENU_7002BF0, D_VS_MENU_7002E50 };

    RCP_SetupDL(&gMasterDisp, 0x53);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 60, 60, 255, 190);

    TextureRect_8bIA(&gMasterDisp, D_MAP_601B4B0, 24, 17, 93.0f, 42.0f, 5.1f, 1.1f);

    if (D_menu_801B912C == 0) {
        D_menu_801B9324 = 97.0f;
        D_menu_801B9328 = 49.0f;
        D_menu_801B9338 = 107.0f;
        Option_8019B6D8(D_menu_801B9324, D_menu_801B9328, D_menu_801B9338, 255, 255, 255);
        Option_8019C824(&D_menu_801B9378);
    } else {
        D_menu_801B9378 = 255.0f;
    }

    colorGB = D_menu_801B9378;

    var_v0 = 0xFFFFFFFF;

    if (D_menu_801B937C != 0) {
        colorGB = 255;
        var_v0 = 1;
        D_menu_801B937C--;
        if (!D_menu_801B937C) {
            D_menu_801B91F0 = 1;
        }
    }

    if (gGameFrameCount & var_v0) {
        RCP_SetupDL(&gMasterDisp, 0x53);

        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, colorGB, colorGB, 255);

        TextureRect_8bIA(&gMasterDisp, sTimeTrialMinuteTextures[D_menu_801B9340], 40, 15,
                         D_menu_801AF25C[D_menu_801B9340 + 1], D_menu_801AF274[D_menu_801B9340 + 1], 1.0f, 1.0f);

        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, colorGB, colorGB, 255);

        TextureRect_8bIA(&gMasterDisp, D_VS_MENU_7002110, 80, 12, D_menu_801AF25C[0], D_menu_801AF274[0], 1.0f, 1.0f);
    }
}

void Option_8019AFFC(void) {
    static f32 D_menu_801B93C0;
    static f32 D_menu_801B93C8;
    static f32 D_menu_801B93CC;
    static f32 D_menu_801AF2A0 = 101.0f;
    static f32 D_menu_801AF2A4 = 86.0f;
    s32 var_v0;
    s32 colorGB;

    if ((D_menu_801B912C == 0 && D_menu_801B93D0 == 20) || (D_menu_801B912C == 1 && D_menu_801B93D0 != 20)) {
        D_menu_801B93C0 = 94.0f;
        D_menu_801B93C8 = 88.0f;
        D_menu_801B93CC = 114.0f;

        RCP_SetupDL(&gMasterDisp, 0x53);

        Option_8019B6D8(D_menu_801B93C0, D_menu_801B93C8, D_menu_801B93CC, 255, 255, 255);
        Option_8019C824(&D_menu_801B9370);
    } else {
        D_menu_801B9370 = 255.0f;
    }

    colorGB = D_menu_801B9370;

    var_v0 = 0xFFFFFFFF;
    if (D_menu_801B9374 != 0) {
        var_v0 = 1;
        colorGB = 255;
        D_menu_801B9374--;
        if (!D_menu_801B9374) {
            D_menu_801B91F0 = 1;
        }
    }

    if (gGameFrameCount & var_v0) {
        RCP_SetupDL(&gMasterDisp, 0x53);

        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, colorGB, colorGB, 255);

        TextureRect_8bIA(&gMasterDisp, D_VS_MENU_7001270, 112, 12, D_menu_801AF2A0, D_menu_801AF2A4, 1.0f, 1.0f);
    }

    if (D_menu_801B93D0 == 30) {
        Option_8019B1F8();
    } else {
        Option_8019B3DC();
    }
}

void Option_8019B1F8(void) {
    static f32 D_menu_801AF2A8 = 69.0f;
    static f32 D_menu_801AF2AC = 110.0f;
    static f32 D_menu_801AF2B0 = 123.0f;
    static f32 D_menu_801AF2B4[] = { 72.0f, 189.0f };
    f32 xPos;
    s32 i;
    s32 width;
    s32 sp8C[2];
    static u8* D_menu_801AF2BC[] = { D_VS_MENU_7001C10, D_VS_MENU_70019E0 };
    static u8* D_menu_801AF2C4[] = { D_VS_MENU_7006780, D_VS_MENU_7005F10 };
    static u16* D_menu_801AF2CC[] = { D_VS_MENU_7006EA0, D_VS_MENU_7006630 };

    for (xPos = D_menu_801AF2A8, i = 0; i < 2; i++, xPos += D_menu_801AF2B0) {
        if (i == D_game_80161A28) {
            sp8C[i] = 255;
        } else {
            sp8C[i] = 32;
        }

        RCP_SetupDL(&gMasterDisp, 0x55);

        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, sp8C[i]);

        TextureRect_8bCI(&gMasterDisp, D_menu_801AF2C4[i], D_menu_801AF2CC[i], 48, 38, xPos, D_menu_801AF2AC, 1.0f,
                         1.0f);

        width = 48;
        if (i == 1) {
            width = 56;
        }
        RCP_SetupDL(&gMasterDisp, 0x53);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, sp8C[i]);
        TextureRect_8bIA(&gMasterDisp, D_menu_801AF2BC[i], width, 10, D_menu_801AF2B4[i], D_menu_801AF2AC + 40.0f, 1.0f,
                         1.0f);
    }
}

void Option_8019B3DC(void) {
    static f32 D_menu_801AF2D4 = 69.0f;
    static f32 D_menu_801AF2D8 = 110.0f;
    static f32 D_menu_801AF2DC = 123.0f;
    static f32 D_menu_801AF2E0[] = { 66.0f, 189.0f };
    f32 xPos;
    s32 i;
    s32 sp8C[3];
    static u8* D_menu_801AF2E8[] = {
        D_VS_MENU_70017B0,
        D_VS_MENU_70019E0,
    };
    static u8* D_menu_801AF2F0[] = {
        D_VS_MENU_7005600,
        D_VS_MENU_7005F10,
    };
    static u16* D_menu_801AF2F8[] = {
        D_VS_MENU_7005D20,
        D_VS_MENU_7006630,
    };

    for (xPos = D_menu_801AF2D4, i = 0; i < 2; i++, xPos += D_menu_801AF2DC) {
        if (i == D_game_80161A28) {
            sp8C[i] = 255;
        } else {
            sp8C[i] = 32;
        }

        RCP_SetupDL(&gMasterDisp, 0x55);

        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, sp8C[i]);

        TextureRect_8bCI(&gMasterDisp, D_menu_801AF2F0[i], D_menu_801AF2F8[i], 48, 38, xPos, D_menu_801AF2D8, 1.0f,
                         1.0f);

        RCP_SetupDL(&gMasterDisp, 0x53);

        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, sp8C[i]);

        TextureRect_8bIA(&gMasterDisp, D_menu_801AF2E8[i], 56, 10, D_menu_801AF2E0[i], D_menu_801AF2D8 + 40.0f, 1.0f,
                         1.0f);
    }
}

void Option_8019B5AC(void) {
    s32 pad[2];
    s32 colorGB;
    s32 var_v0;

    Option_8019C824(&D_menu_801B91E8);

    colorGB = D_menu_801B91E8;
    var_v0 = 0xFFFFFFFF;

    if (D_menu_801B91EC) {
        colorGB = 255;
        var_v0 = 1;
        D_menu_801B91EC--;
        if (D_menu_801B91EC == 0) {
            D_menu_801B91F0 = 1;
        }
    }

    if (gGameFrameCount & var_v0) {
        RCP_SetupDL(&gMasterDisp, 0x53);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, colorGB, colorGB, 255);
        TextureRect_8bIA(&gMasterDisp, D_VS_MENU_7003650, 40, 12, 143.0f, 210.0f, 1.0f, 1.0f);
    }
}

void Option_8019B6D8(f32 xPos, f32 yPos, f32 offset, s32 r, s32 g, s32 b) {
    RCP_SetupDL(&gMasterDisp, 0x53);
    gDPSetPrimColor(gMasterDisp++, 0, 0, r, g, b, 255);
    TextureRect_8bIA_MirX(&gMasterDisp, D_VS_MENU_7004010, 8, 8, xPos, yPos, 1.0f, 1.0f);
    TextureRect_8bIA(&gMasterDisp, D_VS_MENU_7004010, 8, 8, xPos + offset, yPos, 1.0f, 1.0f);
}

void Option_8019B7D4(void) {
    RCP_SetupDL(&gMasterDisp, 0x53);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
    TextureRect_8bIA(&gMasterDisp, D_OPT_80080F0, 96, 10, 62.0f, 213.0f, 1.0f, 1.0f);
    TextureRect_8bIA(&gMasterDisp, D_OPT_8006E50, 96, 10, 166.0f, 213.0f, 1.0f, 1.0f);
}

void Option_8019B8A0(s32 arg0) {
    D_menu_801B9124 = arg0;
    gDrawMode = DRAW_NONE;
    D_menu_801B912C = 0;
    D_menu_801B91B4 = 0;
}

void Option_8019B8C8(void) {
    Option_8019BDF0();
    Option_DrawMenuCard(sOptionVSCardList[D_menu_801B91A8].unk_38);
    Matrix_Pop(&gGfxMatrix);
    Option_DrawCardLabel(sOptionVSCardList[D_menu_801B91A8].unk_00);
}

void Option_DrawMenuLabel(void) {
    Option_8019BDF0();
    Option_DrawMenuCard(sOptionCardList[D_menu_801B91A4].unk_38);
    Matrix_Pop(&gGfxMatrix);
    Option_DrawCardLabel(sOptionCardList[D_menu_801B91A4].unk_00);
}

void Option_DrawMenuCard(MenuContext_38 arg0) {
    RCP_SetupDL(&gMasterDisp, 0x11);

    Lib_InitOrtho(&gMasterDisp);

    Matrix_Push(&gGfxMatrix);

    Matrix_Translate(gGfxMatrix, arg0.unk_00, arg0.unk_04, arg0.unk_08, 1);
    Matrix_Scale(gGfxMatrix, arg0.unk_0C, arg0.unk_10, 1.0f, 1);
    Matrix_RotateX(gGfxMatrix, M_DTOR * 90.0f, 1);

    Matrix_SetGfxMtx(&gMasterDisp);

    gSPDisplayList(gMasterDisp++, D_OPT_8015550);

    Matrix_Pop(&gGfxMatrix);

    Lib_InitPerspective(&gMasterDisp);
}

void Option_DrawMenuArwing(ArwingPosition arg0) {
    if (D_menu_801B91BC != 0) {
        Option_8019BC44(arg0.unk_0, arg0.unk_4, D_menu_801B91F4, D_menu_801B9200, 90.0f, D_menu_801B91F8);
        Option_8019BC44(arg0.unk_0 + arg0.unk_8, arg0.unk_4, D_menu_801B91F4, D_menu_801B91FC, -90.0f, D_menu_801B91F8);
    }
}

void Option_8019BC44(f32 x, f32 y, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    f32 sp44;
    f32 sp40;
    f32 sp3C;

    Option_8019BE7C(D_menu_801B9224, D_menu_801B9228, 100.0f, &sp44, &sp40, &sp3C);

    Lights_SetOneLight(&gMasterDisp, sp44, sp40, sp3C, D_menu_801B922C, D_menu_801B9230, D_menu_801B9234,
                       D_menu_801B9238, D_menu_801B923C, D_menu_801B9240);

    Matrix_Push(&gGfxMatrix);

    Matrix_Translate(gGfxMatrix, x, y, arg2, 1);

    Matrix_Scale(gGfxMatrix, arg5, arg5, arg5, 1);
    Matrix_RotateZ(gGfxMatrix, M_DTOR * arg4, 1);
    Matrix_RotateY(gGfxMatrix, M_DTOR * arg3, 1);

    Matrix_SetGfxMtx(&gMasterDisp);

    RCP_SetupDL_55();

    gSPDisplayList(gMasterDisp++, D_MAP_604A9F0);

    Matrix_Pop(&gGfxMatrix);
}

void Option_8019BDF0(void) {
    Matrix_Push(&gGfxMatrix);
    Matrix_LookAt(gGfxMatrix, gCsCamEyeX, gCsCamEyeY, gCsCamEyeZ, gCsCamAtX, gCsCamAtY, gCsCamAtZ, 0.0f, 1.0f, 0.0f, 1);
}

void Option_8019BE7C(f32 arg0, f32 arg1, f32 arg2, f32* arg3, f32* arg4, f32* arg5) {
    Vec3f sp24;
    Vec3f sp18;

    sp18.x = 0.0f;
    sp18.y = 0.0f;
    sp18.z = arg2;

    Matrix_RotateY(gCalcMatrix, M_DTOR * arg1, 0);
    Matrix_RotateX(gCalcMatrix, M_DTOR * arg0, 1);
    Matrix_MultVec3f(gCalcMatrix, &sp18, &sp24);

    *arg3 = sp24.x;
    *arg4 = sp24.y;
    *arg5 = sp24.z;
}

void Option_8019BF34(void) {
    s32 i;
    f32 sp40;

    if (D_menu_801B9214 != 0) {
        sp40 = D_menu_801B9204;
        Option_8019BDF0();

        for (i = 0; i < 3; i++) {
            D_menu_801B920C = RAND_FLOAT(0.5f);
            D_menu_801B9210 = 0.5f;
            Option_8019C04C();
            D_menu_801B9204 += 6.0f;
        }

        Matrix_Pop(&gGfxMatrix);
        D_menu_801B9204 = sp40;

        if (D_menu_801B9204 < 23.0f) {
            D_menu_801B9204 += 18.0f;
        } else {
            D_menu_801B9204 = 23.0f;
            D_menu_801B9214 = 0;
        }
    }
}

void Option_8019C04C(void) {
    RCP_SetupDL(&gMasterDisp, 0x24);

    Lib_InitOrtho(&gMasterDisp);

    Matrix_Push(&gGfxMatrix);

    Matrix_Translate(gGfxMatrix, D_menu_801B9204, D_menu_801B9208, 0.0f, 1);
    Matrix_Scale(gGfxMatrix, D_menu_801B920C, D_menu_801B9210, 1.0f, 1);

    Matrix_SetGfxMtx(&gMasterDisp);

    gSPDisplayList(gMasterDisp++, D_OPT_8015DF0);

    Matrix_Pop(&gGfxMatrix);

    Lib_InitPerspective(&gMasterDisp);
}

void Option_DrawCardLabel(OptionTexture arg0) {
    if (!(arg0.unk_20 <= 0.0f) && !(arg0.unk_24 <= 0.0f)) {
        switch (arg0.unk_00) {
            case 1:
                RCP_SetupDL(&gMasterDisp, 0x4E);
                gDPSetPrimColor(gMasterDisp++, 0, 0, arg0.unk_28, arg0.unk_2C, arg0.unk_30, arg0.unk_34);
                TextureRect_4bCI(&gMasterDisp, arg0.unk_08, arg0.unk_0C, arg0.unk_10, arg0.unk_14, arg0.unk_18,
                                 arg0.unk_1C, arg0.unk_20, arg0.unk_24);
                break;

            case 2:
                RCP_SetupDL(&gMasterDisp, 0x4E);
                gDPSetPrimColor(gMasterDisp++, 0, 0, arg0.unk_28, arg0.unk_2C, arg0.unk_30, arg0.unk_34);
                TextureRect_8bCI(&gMasterDisp, arg0.unk_08, arg0.unk_0C, arg0.unk_10, arg0.unk_14, arg0.unk_18,
                                 arg0.unk_1C, arg0.unk_20, arg0.unk_24);
                break;

            case 0:
                RCP_SetupDL(&gMasterDisp, 0x4C);
                gDPSetPrimColor(gMasterDisp++, 0, 0, arg0.unk_28, arg0.unk_2C, arg0.unk_30, arg0.unk_34);
                TextureRect_8bIA(&gMasterDisp, arg0.unk_08, arg0.unk_10, arg0.unk_14, arg0.unk_18, arg0.unk_1C,
                                 arg0.unk_20, arg0.unk_24);
                break;

            case 3:
                RCP_SetupDL(&gMasterDisp, 0x4C);
                gDPSetPrimColor(gMasterDisp++, 0, 0, arg0.unk_28, arg0.unk_2C, arg0.unk_30, arg0.unk_34);
                TextureRect_16bRGBA(&gMasterDisp, arg0.unk_08, arg0.unk_10, arg0.unk_14, arg0.unk_18, arg0.unk_1C,
                                    arg0.unk_20, arg0.unk_24);
                break;
        }
    }
}

bool Option_8019C418(s32* arg0, s32 arg1, bool arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                     UnkStruct_D_menu_801B9250* arg8) {
    s32 axis;
    s32 x;
    s32 y;
    s32 temp;
    bool ret = false;

    if (arg1 == 0) {
        return ret;
    }

    temp = *arg0;

    x = gControllerPress[arg7].stick_x;
    y = -gControllerPress[arg7].stick_y;

    if (arg2 == true) {
        axis = y;
        if ((x > 40) || (x < -40)) {
            return ret;
        }
    } else {
        axis = x;
        if ((y > 40) || (y < -40)) {
            return ret;
        }
    }

    if ((axis < arg4) && (axis > -arg4)) {
        axis = 0;
    }

    if (!(arg8->unk_4)) {
        if (axis != 0) {
            if (axis > 0) {
                (*arg0)++;
                if (*arg0 > arg1) {
                    if (arg3 == 0) {
                        *arg0 = 0;
                    } else {
                        *arg0 = arg1;
                    }
                }
            }

            if (axis < 0) {
                (*arg0)--;
                if (*arg0 < 0) {
                    if (arg3 == 0) {
                        *arg0 = arg1;
                    } else {
                        *arg0 = 0;
                    }
                }
            }

            arg8->unk_4 = arg5 + arg8->unk_0;
            if (arg8->unk_0 > 0) {
                arg8->unk_0 -= arg6;
            }
        } else {
            arg8->unk_4 = 0;
            arg8->unk_0 = arg6;
        }
    }

    if (arg8->unk_4 > 0) {
        arg8->unk_4--;
    }

    if (temp != *arg0) {
        ret = true;
    }

    return ret;
}

s32 Option_8019C5A0(s32* arg0) {
    s32 ret = 0;
    s32 temp = *arg0;
    s32 x = gControllerPress[gMainController].stick_x;
    s32 y = -gControllerPress[gMainController].stick_y;

    if ((y > 40) || (y < -40)) {
        return ret;
    }

    if ((x < 30) && (x > -30)) {
        x = 0;
    }

    if (D_menu_801B91A0 == 0) {
        if (x != 0) {
            if (x > 0) {
                *arg0 = 0;
                ret = 1;
            }
            if (x < 0) {
                *arg0 = 1;
                ret = -1;
            }
            D_menu_801B91A0 = OPTION_COUNT;
        }
    }

    if (D_menu_801B91A0 > 0) {
        D_menu_801B91A0--;
    }

    if (temp == *arg0) {
        ret = 0;
    }

    return ret;
}

bool Option_8019C66C(f32* arg0, f32 arg1, f32 arg2, UnkStruct_D_menu_801B9250* arg3) {
    f32 var_fv1;
    f32 temp2;
    bool var_a2 = false;
    f32 temp = *arg0;
    s32 x = gControllerPress[gMainController].stick_x;
    s32 y = -gControllerPress[gMainController].stick_y;

    if ((y > 10) || (y < -10)) {
        return 0;
    }

    if ((x < 10) && (x > -10)) {
        x = 0;
    } else if (x < 0) {
        x += 10;
    } else {
        x -= 10;
    }

    if (arg3->unk_4 == 0) {
        if (x != 0) {
            var_fv1 = x / 20.0f;
            arg3->unk_4 = arg3->unk_0;

            if (arg3->unk_0 != 0) {
                arg3->unk_0 -= 7;
            }

            if (arg3->unk_4 != 0) {
                if (x > 0) {
                    var_fv1 = 1.0f;
                } else {
                    var_fv1 = -1.0f;
                }
            }

            *arg0 += var_fv1;

            if (arg2 < *arg0) {
                *arg0 = arg2;
            }
            if (*arg0 < arg1) {
                *arg0 = arg1;
            }
        } else {
            arg3->unk_4 = 0;
            arg3->unk_0 = 7;
        }
    }

    if (arg3->unk_4 > 0) {
        arg3->unk_4--;
    }

    temp2 = *arg0;

    if ((s32) temp2 != (s32) temp) {
        AUDIO_PLAY_SFX(0x49004007, gDefaultSfxSource, 4);
        var_a2 = true;
    }

    return var_a2;
}

void Option_8019C824(f32* arg0) {
    if ((s32) Math_SmoothStepToF(arg0, D_menu_801B91E4, 0.5f, 100.0f, 1.0f) == 0.0f) {
        if (*arg0 == 32.0f) {
            D_menu_801B91E4 = 255.0f;
        } else {
            D_menu_801B91E4 = 32.0f;
        }
    }
}

s32 Option_8019C8C4(void) {
    s32 i;
    s32 j;
    s32 k;
    s32 m;
    s32 ret;
    s32 var_v0 = 0;
    s32 var_a0 = 0;
    s32 temp[10];

    for (i = 0; i < gCurrentPlanet + 1; i++) {
        var_v0 += ((D_ctx_80177B50[i] & 0x00FF0000) >> 16) & 1;
        var_v0 += ((D_ctx_80177B50[i] & 0x0000FF00) >> 8) & 1;
        var_v0 += (D_ctx_80177B50[i] & 0x000000FF) & 1;
    }

    for (i = 0; i < 10; i++) {
        temp[i] = gSaveFile.save.data.unk_40[i];
    }

    ret = -1;

    for (i = 0; i < 10; i++) {
        if (D_menu_801B8220[i] <= gTotalHits) {
            if (D_menu_801B8220[i] == gTotalHits) {
                for (j = i; j < 10; j++) {
                    if (D_menu_801B8220[j] != gTotalHits) {
                        ret = j;
                        break;
                    }

                    if (temp[j] <= gLifeCount[gPlayerNum]) {
                        if (temp[j] == gLifeCount[gPlayerNum]) {
                            for (k = j; k < 10; k++) {
                                if ((temp[k] != gLifeCount[gPlayerNum]) || (D_menu_801B8220[k] != gTotalHits)) {
                                    ret = k;
                                    break;
                                }

                                for (var_a0 = 0, m = 0; m < 3; m++) {
                                    var_a0 += D_menu_801B81A8[k][m];
                                }

                                if (var_v0 > var_a0) {
                                    ret = k;
                                    break;
                                }
                            }
                        } else {
                            ret = j;
                        }
                        break;
                    }
                }
            } else {
                ret = i;
            }
            break;
        }
    }

    return ret;
}

void Option_8019CAE0(void) {
    switch (D_menu_801B912C) {
        case 0:
            Option_8019CBC0();
            D_menu_801B912C++;
            break;

        case 1:
            Option_8019CD54();
            break;

        case 2:
            Option_8019D624();
            Title_80188010();
            D_menu_801B917C = 15;
            D_menu_801B912C++;
            break;

        case 3:
            if (D_menu_801B917C == 0) {
                gBlurAlpha = 255;
                gDrawMode = DRAW_NONE;
                D_menu_801B912C = 0;
                D_menu_801B9124 = 300;
            }
            break;
    }
}

void Option_8019CBC0(void) {
    s32 temp;
    s32 i;

    AUDIO_PLAY_BGM(SEQ_ID_MENU);

    gBlurAlpha = 208;
    D_ctx_80178410 = 800;

    D_menu_801B9130 = 1;
    D_menu_801B9128 = 0;
    D_menu_801B911C = 0.0f;
    D_menu_801B9120 = 70.0f;

    temp = gSaveFile.save.data.unk_EA & 0xFF;

    if (temp < 10) {
        D_menu_801B9098 = 3;
        D_menu_801B9138 = 1;

        D_menu_801B9150[0][0] = gSaveFile.save.data.unk_18[temp][0] & 0xFF;
        D_menu_801B9150[1][0] = gSaveFile.save.data.unk_18[temp][1] & 0xFF;
        D_menu_801B9150[2][0] = gSaveFile.save.data.unk_18[temp][2] & 0xFF;

        for (i = 0; i < 3; i++) {
            D_menu_801B90A0[i] = Option_8019DCE8(D_menu_801B9150[i][0]);
            D_menu_801B90B0[i] = 1;
            D_menu_801B9150[i][1] = 0;
        }
    } else {
        D_menu_801B9098 = 0;
        D_menu_801B9138 = 0;

        for (i = 0; i < 3; i++) {
            D_menu_801B90B0[i] = 0;
            D_menu_801B90A0[i] = 0;
            D_menu_801B9150[i][0] = 65;
            D_menu_801B9150[i][1] = 0;
        }
    }
    Option_80192598();
}

void Option_8019CD54(void) {
    switch (D_menu_801B9128) {
        case 0:
            if (D_menu_801B9138 == 0) {
                if (Option_8019C418(&D_menu_801B90A0[D_menu_801B9098], 36, 0, 0, 50, 5, 10, gMainController,
                                    &D_menu_801B9160[D_menu_801B9098])) {
                    AUDIO_PLAY_SFX(0x49000002, gDefaultSfxSource, 4);
                    D_menu_801B9150[D_menu_801B9098][0] = D_menu_801AEF5C[D_menu_801B90A0[D_menu_801B9098]];
                    D_menu_801B90D0[D_menu_801B9098] = 0.0f;
                    D_menu_801B9100[D_menu_801B9098] = 0.0f;
                }
            }

            if (gControllerPress[gMainController].button & A_BUTTON) {
                D_menu_801B90D0[D_menu_801B9098] = 0.0f;
                if (D_menu_801B9138 != 0) {
                    AUDIO_PLAY_SFX(0x49000003, gDefaultSfxSource, 4);
                    D_menu_801B9140[0] = 10;
                    D_menu_801B9140[1] = 10;
                    D_menu_801B9140[2] = 10;
                    D_menu_801B9138 = -1;
                    D_menu_801B9128 = 2;
                    break;

                } else {
                    if (D_menu_801B9098 < 3) {
                        AUDIO_PLAY_SFX(0x49000003, gDefaultSfxSource, 4);
                        D_menu_801B90D0[D_menu_801B9098] = 0.0f;
                        D_menu_801B9140[D_menu_801B9098] = 15;
                        D_menu_801B9128 = 1;
                        break;
                    }
                }
            }

            if ((gControllerPress[gMainController].button & B_BUTTON) && (D_menu_801B9098 != 0)) {
                AUDIO_PLAY_SFX(0x4900101D, gDefaultSfxSource, 4);
                if (D_menu_801B9138 != 0) {
                    D_menu_801B9138 = 0;
                }
                D_menu_801B9098--;
                D_menu_801B9140[D_menu_801B9098] = 15;
                D_menu_801B9128 = 10;
            }
            break;

        case 10:
            D_menu_801B9140[D_menu_801B9098]--;
            if (D_menu_801B9140[D_menu_801B9098] != 0) {
                break;
            }

            D_menu_801B9128 = 0;
            break;

        case 1:
            D_menu_801B9140[D_menu_801B9098]--;
            if (D_menu_801B9140[D_menu_801B9098] != 0) {
                break;
            }

            if ((D_menu_801B9098 + 1) > 2) {
                D_menu_801B9138 = 1;
            }

            D_menu_801B9098++;
            D_menu_801B9128 = 0;
            break;

        case 2:
            D_menu_801B9140[0]--;
            D_menu_801B9140[1]--;
            D_menu_801B9140[2]--;

            if (D_menu_801B9140[0] != 0) {
                break;
            }

            D_menu_801B917C = 20;
            D_menu_801B9128 = 3;
            break;

        case 3:
            if (D_menu_801B917C == 0) {
                D_menu_801B912C = 2;
                break;
            }
    }
}

void Option_8019D118(void) {
    static f32 D_menu_801AF300[] = { -120.0f, 0.0f, 120.0f };
    f32 dirX;
    f32 dirY;
    f32 dirZ;
    s32 mask[3];
    s32 i;
    static f32 D_menu_801AF30C[6] = { 51.0f, 138.0f, 118.0f, 166.0f, 138.0f, 267.0f };
    static f32 D_menu_801AF324[6] = { 29.0f, 49.0f, 145.0f, 155.0f, 87.0f, 127.0f };

    RCP_SetupDL(&gMasterDisp, 0x4C);

    if (D_game_80161A34 == 8) {
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
        Graphics_DisplayLargeText(D_menu_801AF30C[0], D_menu_801AF324[0], 1.0f, 1.0f, "CONGRATULATIONS");
    }

    if (D_menu_801B9178 != 0) {
        return;
    }

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);
    Graphics_DisplaySmallText(D_menu_801AF30C[1], D_menu_801AF324[1], 1.0f, 1.0f, "RANK");
    Graphics_DisplaySmallText(D_menu_801AF30C[2], D_menu_801AF324[2], 1.0f, 1.0f, "TOTAL HITS");
    (void) "p:%d x:%f y:%f\n";
    if (D_menu_801B9138 == 1) {
        if (gGameFrameCount & 0x10) {
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);
            TextureRect_8bIA(&gMasterDisp, D_50021F0, 32, 8, D_menu_801AF30C[5], D_menu_801AF324[5], 1.0f, 1.0f);
        }
    }

    Option_80197A3C(D_menu_801B9094, D_menu_801AF30C[4], D_menu_801AF324[4]);

    RCP_SetupDL(&gMasterDisp, 0x4C);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    Graphics_DisplayLargeNumber(D_menu_801AF30C[3] - ((func_hud_8008BCBC(gTotalHits) - 1) * 13), D_menu_801AF324[3],
                                gTotalHits);

    Map_801A9FD4(1);

    Option_80192738();

    for (i = 0; i < 3; i++) {
        if (i == D_menu_801B9098) {
            D_menu_801B9100[i] += 1.0f;
        } else {
            D_menu_801B9100[i] = 0.0f;
        }

        mask[i] = 0xFFFFFFFF;

        if (D_menu_801B9140[i]) {
            mask[i] = 0x1;
            D_menu_801B9100[i] = 0.0f;
        }
    }

    Option_8019BE7C(D_menu_801B911C, D_menu_801B9120, 127.0f, &dirX, &dirY, &dirZ);

    Lights_SetOneLight(&gMasterDisp, dirX, dirY, dirZ, 255, 255, 255, 65, 70, 48);

    Matrix_Push(&gGfxMatrix);

    Matrix_LookAt(gGfxMatrix, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -100.0f, 0.0f, 1.0f, 0.0f, 1);

    Matrix_SetGfxMtx(&gMasterDisp);

    for (i = 0; i < 3; i++) {
        if (gGameFrameCount & mask[i]) {
            Option_8019DB20(D_menu_801B9150[i][0], D_menu_801AF300[i], 18.0f, -455.0f, 1.0f,
                            D_menu_801B90C0[i] + D_menu_801B90F0[i], D_menu_801B90D0[i] + D_menu_801B9100[i],
                            D_menu_801B90E0[i] + D_menu_801B9110[i]);
        }
    }

    Matrix_Pop(&gGfxMatrix);
}

void Option_8019D624(void) {
    s32 i;
    s32 j;
    s32 var_t2;
    s32 var_a3, var_a0;
    s32 var_a1;
    u8 sp142[11][3];
    u8 sp122[11];
    u8 sp116[11];
    u8 sp10A[11];
    Save_SubStruct_5E var_s0[11][7];

    sp142[10][0] = D_menu_801B9150[0][0];
    sp142[10][1] = D_menu_801B9150[1][0];
    sp142[10][2] = D_menu_801B9150[2][0];

    sp122[10] = gCurrentPlanet + 1;

    sp116[10] = gLifeCount[0];

    sp10A[10] = 0;

    for (i = 0; i < 7; i++) {
        sp10A[10] |= (D_ctx_80177BB0[i] << i);
    }

    for (j = 0; j < 7; j++) {
        var_s0[10][j].unk_C = 0;

        var_t2 = D_ctx_80177B70[j];

        if (var_t2 > 255) {
            var_t2 = var_t2 - 256;
            var_s0[10][j].unk_C = 1;
        }

        var_s0[10][j].unk_0 = var_t2;

        var_a0 = D_ctx_80177B90[j];

        if (D_ctx_80177B90[j] == PLANET_VENOM) {
            var_a0 = SAVE_SLOT_VENOM_1;
        }

        if (D_ctx_80177B90[j] == PLANET_SOLAR) {
            var_a0 = SAVE_SLOT_SOLAR;
        }

        var_s0[10][j].unk_8 = var_a0;

        var_s0[10][j].unk_D = ((D_ctx_80177B50[j] & 0x00FF0000) >> 16) & 1;
        var_s0[10][j].unk_F = ((D_ctx_80177B50[j] & 0x0000FF00) >> 8) & 1;
        var_s0[10][j].unk_E = (D_ctx_80177B50[j] & 0x000000FF) & 1;
    }

    for (i = 0; i < 10; i++) {
        sp142[i][0] = gSaveFile.save.data.unk_18[i][0];
        sp142[i][1] = gSaveFile.save.data.unk_18[i][1];
        sp142[i][2] = gSaveFile.save.data.unk_18[i][2];
        sp122[i] = gSaveFile.save.data.unk_36[i];
        sp116[i] = gSaveFile.save.data.unk_40[i];
        sp10A[i] = gSaveFile.save.data.unk_4A[i];

        for (j = 0; j < 7; j++) {
            var_s0[i][j].unk_0 = gSaveFile.save.data.unk_5E[i][j].unk_0;
            var_s0[i][j].unk_8 = gSaveFile.save.data.unk_5E[i][j].unk_8;
            var_s0[i][j].unk_C = gSaveFile.save.data.unk_5E[i][j].unk_C;
            var_s0[i][j].unk_D = gSaveFile.save.data.unk_5E[i][j].unk_D;
            var_s0[i][j].unk_E = gSaveFile.save.data.unk_5E[i][j].unk_E;
            var_s0[i][j].unk_F = gSaveFile.save.data.unk_5E[i][j].unk_F;
        }
    }

    for (var_a1 = 0, i = 0; i < 10; i++) {
        if (i == D_menu_801B9094) {
            var_a3 = var_a1;
            var_a1 = 10;
        }

        gSaveFile.save.data.unk_18[i][0] = sp142[var_a1][0];
        gSaveFile.save.data.unk_18[i][1] = sp142[var_a1][1];
        gSaveFile.save.data.unk_18[i][2] = sp142[var_a1][2];
        gSaveFile.save.data.unk_36[i] = sp122[var_a1];
        gSaveFile.save.data.unk_40[i] = sp116[var_a1];
        gSaveFile.save.data.unk_4A[i] = sp10A[var_a1];

        for (j = 0; j < 7; j++) {
            gSaveFile.save.data.unk_5E[i][j].unk_0 = var_s0[var_a1][j].unk_0;
            gSaveFile.save.data.unk_5E[i][j].unk_8 = var_s0[var_a1][j].unk_8;
            gSaveFile.save.data.unk_5E[i][j].unk_C = var_s0[var_a1][j].unk_C;
            gSaveFile.save.data.unk_5E[i][j].unk_D = var_s0[var_a1][j].unk_D;
            gSaveFile.save.data.unk_5E[i][j].unk_E = var_s0[var_a1][j].unk_E;
            gSaveFile.save.data.unk_5E[i][j].unk_F = var_s0[var_a1][j].unk_F;
        }

        if (i == D_menu_801B9094) {
            var_a1 = var_a3;
        } else {
            var_a1++;
        }
    }

    gSaveFile.save.data.unk_EA = D_menu_801B9094;

    Save_Write();
}

void Option_8019DB20(s32 character, f32 x, f32 y, f32 z, f32 scale, f32 xAngle, f32 yAngle, f32 zAngle) {
    static Gfx* D_menu_801AF33C[37] = {
        D_FONT3D_90086F0, D_FONT3D_9007FD0, D_FONT3D_9007BB0, D_FONT3D_9000980, D_FONT3D_90075A0, D_FONT3D_90070C0,
        D_FONT3D_9006AE0, D_FONT3D_9006500, D_FONT3D_90062D0, D_FONT3D_9001120, D_FONT3D_9005CA0, D_FONT3D_9005980,
        D_FONT3D_9005380, D_FONT3D_9004E10, D_FONT3D_9000570, D_FONT3D_90014E0, D_FONT3D_9004920, D_FONT3D_9004230,
        D_FONT3D_9003A30, D_FONT3D_9003620, D_FONT3D_9003230, D_FONT3D_9002EA0, D_FONT3D_9002890, D_FONT3D_90022A0,
        D_FONT3D_9001E90, D_FONT3D_9001A10, D_FONT3D_900BB90, D_FONT3D_90001F0, D_FONT3D_900B580, D_FONT3D_900AF60,
        D_FONT3D_900A870, D_FONT3D_900A290, D_FONT3D_9009CB0, D_FONT3D_9009990, D_FONT3D_9009280, D_FONT3D_9008C60,
        D_FONT3D_9000000,
    };

    s32 i;
    s32 charIndex = -1;

    for (i = 0; D_menu_801AEF5C[i] != NULL; i++) {
        if (character == D_menu_801AEF5C[i]) {
            charIndex = i;
            break;
        }
    }

    if (charIndex == -1) {
        return;
    }

    RCP_SetupDL(&gMasterDisp, 0x17);
    gSPTexture(gMasterDisp++, 2500, 200, 0, G_TX_RENDERTILE, G_ON);
    gSPSetGeometryMode(gMasterDisp++, G_TEXTURE_GEN);

    Matrix_Push(&gGfxMatrix);

    Matrix_Translate(gGfxMatrix, x, y, z, 1);

    Matrix_RotateZ(gGfxMatrix, M_DTOR * zAngle, 1);
    Matrix_RotateX(gGfxMatrix, M_DTOR * xAngle, 1);
    Matrix_RotateY(gGfxMatrix, M_DTOR * yAngle, 1);

    Matrix_Scale(gGfxMatrix, scale, scale, scale, 1);

    Matrix_SetGfxMtx(&gMasterDisp);

    gSPDisplayList(gMasterDisp++, D_menu_801AF33C[charIndex]);

    Matrix_Pop(&gGfxMatrix);
}

s32 Option_8019DCE8(s32 arg0) {
    s32 i = 0;

    // 'for()' causes instruction reorder
    while (D_menu_801AEF5C[i] != 0) {
        if (D_menu_801AEF5C[i] == arg0) {
            break;
        }
        i++;
    }

    if (D_menu_801AEF5C[i] == 0) {
        i = 0;
    }

    return i;
}

void Option_8019DD44(void) {
    switch (D_menu_801B912C) {
        case 0:
            Option_RankingInit();

            D_menu_801B93E4 = D_menu_801B9094;

            if ((D_menu_801B9094 < 0) || (D_menu_801B9094 >= 10)) {
                D_menu_801B93E4 = 0;
            }

            D_menu_801B91D4 = 114.0f - D_menu_801B93E4 * 130.0f;
            D_menu_801B91D8 = -6.0f + D_menu_801B93E4 * 130.0f;
            sOptionCardList[3].unk_00.unk_18 = sOptionCardCurTextPosX[3];
            sOptionCardList[3].unk_00.unk_1C = 23.0f;
            sOptionCardList[3].unk_00.unk_20 = 1.0f;
            sOptionCardList[3].unk_00.unk_24 = 1.0f;
            sOptionCardList[3].unk_58 = 1;
            sOptionCardList[3].unk_38.unk_04 = 90.0f;
            sOptionCardList[3].unk_38.unk_0C = 0.4f;
            sOptionCardList[3].unk_38.unk_10 = 0.21f;
            sOptionCardList[3].unk_5C = 1;
            D_menu_801B912C++;
            break;

        case 1:
            Option_8019DE74();
            break;
    }
}

void Option_8019DE74(void) {
    Option_8019715C();

    if (gControllerPress[gMainController].button & (START_BUTTON | A_BUTTON | B_BUTTON | D_CBUTTONS | L_CBUTTONS |
                                                    U_CBUTTONS)) { // START, A, B, C-UP, C-LEFT, C-DOWN
        AUDIO_PLAY_SFX(0x49000003, gDefaultSfxSource, 4);

        gDrawMode = DRAW_NONE;
        D_menu_801B912C = 0;

        if (D_game_80161A34 == 5) {
            D_ctx_80178410 = 0;
            gGameState = GSTATE_INIT;
            gLifeCount[0] = 2;
            gTotalHits = 0;
        } else if (D_game_80161A34 == 8) {
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 1);
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 1);
            D_menu_801B9124 = 400;
        }
    }
}

void Option_8019DF64(void) {
    Option_8019752C();
    Option_8019BDF0();
    Option_DrawMenuCard(sOptionCardList[3].unk_38);
    Matrix_Pop(&gGfxMatrix);
    Option_DrawCardLabel(sOptionCardList[3].unk_00);
}

void Option_InvoiceUpdate(void) {
    switch (D_menu_801B912C) {
        case 0:
            D_ctx_80178410 = 0;
            gBgColor = 0;
            gFillScreenRed = 0;
            gFillScreenGreen = 0;
            gFillScreenBlue = 0;
            gFillScreenAlpha = 0;
            D_menu_801B9090 = 0;
            D_menu_801B9178 = 30;
            D_menu_801B912C++;
            break;

        case 1:
            if (D_menu_801B9178 == 0) {
                if (((gTotalHits * 64) >= 50000) && ((gTotalHits * 64) < 70000)) {
                    AUDIO_PLAY_SFX(0x49000032, gDefaultSfxSource, 4);
                }
                if ((gTotalHits * 64) >= 70000) {
                    AUDIO_PLAY_SFX(0x49000033, gDefaultSfxSource, 4);
                }
                D_menu_801B9178 = 20;
                D_menu_801B912C++;
            }
            break;

        case 2:
            if ((D_menu_801B9178 == 0) &&
                (gControllerPress[gMainController].button &
                 (START_BUTTON | A_BUTTON | B_BUTTON | D_CBUTTONS | L_CBUTTONS | U_CBUTTONS))) {
                AUDIO_PLAY_SFX(0x19031083, gDefaultSfxSource, 4);
                D_menu_801B9090 = 1;
                D_menu_801B9178 = 60;
                D_menu_801B912C++;
            }
            break;

        case 3:
            if (D_menu_801B9178 == 0) {
                D_ctx_80178410 = 0;
                gGameState = GSTATE_INIT;
                gDrawMode = DRAW_NONE;
                *gLifeCount = 2;
                gTotalHits = 0;
            }
            break;
    }
}

void Option_InvoiceDraw(void) {
    s32 i;
    s32 temp_a0;
    static f32 D_menu_801AF3D0[8] = { 96.0f, 31.0f, 32.0f, 80.0f, 86.0f, 213.0f, 275.0f, 276.0f };
    static f32 D_menu_801AF3F0[8] = { 24.0f, 57.0f, 92.0f, 162.0f, 163.0f, 171.0f, 103.0f, 131.0f };
    static s32 D_menu_801AF410 = 0;

    Graphics_FillRectangle(&gMasterDisp, 25, 18, 295, 222, 255, 255, 255, 255);

    RCP_SetupDL(&gMasterDisp, 0x4E);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    TextureRect_4bCI(&gMasterDisp, D_OPT_8000000, D_OPT_8000680, 128, 16, D_menu_801AF3D0[0], D_menu_801AF3F0[0], 1.0f,
                     1.0f);

    TextureRect_4bCI(&gMasterDisp, D_OPT_8000000 + 1024, D_OPT_8000680, 128, 10, D_menu_801AF3D0[0],
                     D_menu_801AF3F0[0] + 16.0f, 1.0f, 1.0f);

    for (i = 0; i < 2; i++) {
        TextureRect_4bCI(&gMasterDisp, D_OPT_80006A0 + (256 * 16 * i) / 2, D_OPT_80017A0, 256, 16, D_menu_801AF3D0[1],
                         D_menu_801AF3F0[1] + (16 * i), 1.0f, 1.0f);
    }

    TextureRect_4bCI(&gMasterDisp, D_OPT_80006A0 + 256 * 16, D_OPT_80017A0, 256, 2, D_menu_801AF3D0[1],
                     D_menu_801AF3F0[1] + 32.0f, 1.0f, 1.0f);

    for (i = 0; i < 4; i++) {
        TextureRect_4bCI(&gMasterDisp, D_OPT_80017C0 + (256 * 16 * i) / 2, D_OPT_80038C0, 256, 16, D_menu_801AF3D0[2],
                         D_menu_801AF3F0[2] + (16 * i), 1.0f, 1.0f);
    }

    TextureRect_4bCI(&gMasterDisp, D_OPT_80017C0 + 8192, D_OPT_80038C0, 256, 2, D_menu_801AF3D0[2],
                     D_menu_801AF3F0[2] + 64.0f, 1.0f, 1.0f);

    RCP_SetupDL(&gMasterDisp, 0x4C);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    for (i = 0; i < 30; i++) {
        TextureRect_16bRGBA(&gMasterDisp, D_OPT_800E170 + (188 * 2 * i), 188, 2, D_menu_801AF3D0[3],
                            D_menu_801AF3F0[3] + (2.0f * i), 1.0f, 1.0f);
    }

    gDPSetPrimColor(gMasterDisp++, 0, 0, 0, 0, 0, 255);

    Graphics_DisplayLargeNumber(D_menu_801AF3D0[6] - ((func_hud_8008BCBC(gTotalHits) - 1) * 13), D_menu_801AF3F0[6],
                                gTotalHits);

    temp_a0 = gTotalHits * 64;

    Graphics_DisplayLargeNumber(D_menu_801AF3D0[7] - ((func_hud_8008BCBC(temp_a0) - 1) * 13), D_menu_801AF3F0[7],
                                temp_a0);

    if (D_menu_801B9090) {
        gDPSetPrimColor(gMasterDisp++, 0, 0, 120, 0, 0, 192);
        for (i = 0; i < 3; i++) {
            TextureRect_8bIA(&gMasterDisp, D_OPT_800D1F0 + (80 * 16 * i), 80, 16, D_menu_801AF3D0[5],
                             D_menu_801AF3F0[5] + (16.0f * i), 1.0f, 1.0f);
        }
    }

    /**
     * Debug: The following code was probably left out by mistake,
     * It lets you move the graphics on the bill at the end with the 4th controller,
     * programmers probably used it to know which position values to hardcode in place.
     */

    if (gControllerPress[3].button & R_TRIG) {
        D_menu_801AF410++;
        if (D_menu_801AF410 > 7) {
            D_menu_801AF410 = 0;
        }
    }

    if (gControllerPress[3].button & L_TRIG) {
        D_menu_801AF410--;
        if (D_menu_801AF410 < 0) {
            D_menu_801AF410 = 7;
        }
    }

    if (gControllerHold[3].button & U_JPAD) {
        D_menu_801AF3F0[D_menu_801AF410] -= 1.0f;
    }

    if (gControllerHold[3].button & D_JPAD) {
        D_menu_801AF3F0[D_menu_801AF410] += 1.0f;
    }

    if (gControllerHold[3].button & L_JPAD) {
        D_menu_801AF3D0[D_menu_801AF410] -= 1.0f;
    }

    if (gControllerHold[3].button & R_JPAD) {
        D_menu_801AF3D0[D_menu_801AF410] += 1.0f;
    }
}
