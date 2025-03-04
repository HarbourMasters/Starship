/*
 * File: fox_option.c
 * System: Option
 * Description: Starfox Option Menu Handler
 */

#include "mods.h"
#include "prevent_bss_reordering.h"
#include "global.h"
#include "fox_option.h"
#include "assets/ast_text.h"
#include "assets/ast_font_3d.h"
#include "assets/ast_option.h"
#include "assets/ast_vs_menu.h"
#include "assets/ast_map.h"
#include "port/interpolation/FrameInterpolation.h"
#include "port/mods/PortEnhancements.h"

extern s32 gRankingTeamAlive[][3];
extern Gfx gMapVenomCloudDL[];
extern Gfx gMapKatinaDL[];
extern Gfx gMapMacbethDL[];
extern Gfx gMapZonessDL[];
extern Gfx gMapCorneriaDL[];
extern Gfx gMapTitaniaDL[];
extern Gfx gMapAquasDL[];
extern Gfx gMapFortunaDL[];
extern Gfx gMapKatinaDL[];
extern Gfx gMapVenomDL[];
extern f32 D_menu_801CD818[9];

s32 D_menu_801B9090;
s32 sRankInPos;
s32 D_menu_801B9098;
s32 D_menu_801B90A0[3];
s32 D_menu_801B90B0[3];
f32 D_menu_801B90C0[3];
f32 D_menu_801B90D0[3];
f32 D_menu_801B90E0[3];
f32 D_menu_801B90F0[3];
f32 D_menu_801B9100[3];
f32 D_menu_801B9110[3];
f32 sNameEntryLightXrot;
f32 sNameEntryLightYrot;
OptionId sMenuEntryState;
s32 D_menu_801B9128;
s32 sMainMenuState;
s32 D_menu_801B9130;
s32 D_menu_801B9134;
s32 D_menu_801B9138;
s32 D_menu_801B913C;
s32 D_menu_801B9140[3];
s32 D_menu_801B914C;
u8 D_menu_801B9150[3][2];
s32 D_menu_801B9158;
StickInput D_menu_801B9160[3];
s32 D_menu_801B9178; // timer of some kind
s32 D_menu_801B917C; // timer of some kind
StickInput D_menu_801B9180;
StickInput D_menu_801B9188;
StickInput D_menu_801B9190;
StickInput D_menu_801B9198;
s32 D_menu_801B91A0;
s32 sMainMenuCursor;    // Position of the cursor in the main menu.
s32 sVsMenuCursor;      // Position of the cursor in the versus menu.
s32 sExpertSoundCursor; // Whether the Expert Sound options are selected in the menu.
s32 sExpertModeCursor;  // Whether the Expert Main Game mode is selected in the menu.
s32 D_menu_801B91B4;    // Set to 0 and never used.
s32 D_menu_801B91B8;
bool sDrawCursor;
s32 D_menu_801B91C0;
s32 D_menu_801B91C4;
bool sExpertModesEnabled;
s32 D_menu_801B91CC;
s32 D_menu_801B91D0;
f32 D_menu_801B91D4;
f32 D_menu_801B91D8;
f32 D_menu_801B91DC;
f32 D_menu_801B91E0;
f32 D_menu_801B91E4;
f32 D_menu_801B91E8;
f32 sOkConfirmTimer;       // Time before going to the next screen after confirming "OK?" in the versus menu.
bool sVsSubMenuFirstState; // Whether the first sub menu option has yet to be selected
f32 D_menu_801B91F4;
f32 D_menu_801B91F8;
f32 sRightArwingCursorYrot;
f32 sLeftArwingCursorYrot;
f32 sLightningXpos;
f32 sLightningYpos;
f32 sLightningXScale;
f32 sLightningYScale;
s32 D_menu_801B9214;
f32 D_menu_801B9218;
f32 D_menu_801B921C;
f32 D_menu_801B9220;
f32 sArwingLightXrot;
f32 sArwingLightYrot;
s32 sArwingLightColR;
s32 sArwingLightColG;
s32 sArwingLightColB;
s32 sArwingLightAmbR;
s32 sArwingLightAmbG;
s32 sArwingLightAmbB;
bool sMainMenuFromCancel;
bool sVsSubMenuFromCancel;
u8 D_menu_801B924C;
StickInput D_menu_801B9250;
StickInput D_menu_801B9258;
StickInput D_menu_801B9260;
StickInput D_menu_801B9268;
f32 D_menu_801B9270[5];
s32 D_menu_801B9284;
s32 D_menu_801B9288;
StickInput D_menu_801B9290;
f32 D_menu_801B9298[32];
s32 sSpectrumAnalyzerMode;
s32 D_menu_801B931C;
bool sMusicPlaying; // Music is playing status in the expert sound options
extern s32 BSS_PAD_0;
s32 D_menu_801B9330[2];
s32 D_menu_801B933C;
s32 D_menu_801B9340;
s32 D_menu_801B9348[4];
f32 D_menu_801B9358[4];
f32 D_menu_801B9368;
s32 sPointConfirmTimer;
f32 D_menu_801B9370;
s32 sStageSelectConfirmTimer;
f32 D_menu_801B9378;
s32 sTimeTrialConfirmTimer;
StickInput D_menu_801B9380[4];
StickInput D_menu_801B93A0[4];
u8 D_menu_801B93C4;
extern s32 BSS_PAD_1;
s32 sVsMenuSelection;
s32 D_menu_801B93D4;
s32 D_menu_801B93D8;
s32 D_menu_801B93DC;
bool sRanking2ndPage;
s32 D_menu_801B93E4;
s32 D_menu_801B93E8;
s32 D_menu_801B93EC;
f32 D_menu_801B93F0;
f32 D_menu_801B93F4;
f32 D_menu_801B93F8;
StickInput D_menu_801B9400;
StickInput D_menu_801B9408;

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

f32 sOptionCardPosY[] = { 60.0f, 36.0f, 12.0f, -12.0f, -36.0f, -60.0f };
f32 sOptionCardTextPosX[] = { 124.0f, 118.0f, 145.0f, 125.0f, 133.0f, 118.0f };
f32 sOptionCardTextPosY[] = { 54.0f, 78.0f, 103.0f, 126.0f, 151.0f, 175.0f };
f32 sOptionCardCurTextPosX[] = { 124.0f, 118.0f, 145.0f, 125.0f, 133.0f, 118.0f };
f32 sOptionCardCurTextPosY[] = { 54.0f, 78.0f, 103.0f, 126.0f, 151.0f, 175.0f };
f32 D_menu_801AE5E8[] = { 124.0f, 125.0f };
f32 D_menu_801AE5F0[] = { 54.0f, 55.0f };
f32 D_menu_801AE5F8[] = { 133.0f, 125.0f };
f32 D_menu_801AE600[] = { 151.0f, 151.0f };
f32 D_menu_801AE608[] = { 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f };
f32 D_menu_801AE620[] = { 1.9f, 2.4f, 0.9f, 1.9f, 1.8f, 2.4f };

OptionEntry sOptionCardList[] = {
    {
        { 0, 0, aMainGameCardTex, 0, 72, 12, 126.0f, 46.0f, 1.0f, 1.0f, 20, 0, 75, 255 },
        { 0.0f, 30.0f, -130.0f, 0.2f, 0.11f },
        { -40.0f, 27.0f, 80.0f },
        1,
        1,
    },
    {
        { 0, 0, aTrainingCardTex, 0, 80, 12, 126.0f, 184.0f, 1.0f, 1.0f, 20, 0, 75, 255 },
        { 0.0f, 18.0f, -130.0f, 0.2f, 0.11f },
        { -40.0f, 16.0f, 80.0f },
        1,
        1,
    },
    {
        { 0, 0, aVsCardTex, 0, 32, 10, 126.0f, 184.0f, 1.0f, 1.0f, 20, 0, 75, 255 },
        { 0.0f, 6.0f, -130.0f, 0.2f, 0.11f },
        { -40.0f, 6.0f, 80.0f },
        1,
        1,
    },
    {
        { 0, 0, aRankingCardTex, 0, 64, 12, 110.0f, 91.0f, 1.0f, 1.0f, 20, 0, 75, 255 },
        { 0.0f, -6.0f, -130.0f, 0.2f, 0.11f },
        { -40.0f, -5.0f, 80.0f },
        1,
        1,
    },
    {
        { 0, 0, aSoundCardTex, 0, 64, 10, 110.0f, 116.0f, 1.0f, 1.0f, 20, 0, 75, 255 },
        { 0.0f, -18.0f, -130.0f, 0.2f, 0.11f },
        { -40.0f, -16.0f, 80.0f },
        1,
        1,
    },
    {
        { 0, 0, aDataCardTex, 0, 80, 10, 126.0f, 184.0f, 1.0f, 1.0f, 20, 0, 75, 255 },
        { 0.0f, -30.0f, -130.0f, 0.2f, 0.11f },
        { -40.0f, -27.0f, 80.0f },
        1,
        1,
    },
};

OptionEntry sOptionVSCardList[] = {
    {
        { 0, 0, aVsPointMatchCardTex, 0, 96, 13, 110.0f, 91.0f, 1.0f, 1.0f, 20, 0, 75, 255 },
        { 0.0f, 11.0f, -130.0f, 0.2f, 0.11f },
        { -40.0f, 11.0f, 80.0f },
        1,
        1,
    },
    {
        { 0, 0, aVsBattleRoyalCardTex, 0, 96, 10, 110.0f, 116.0f, 1.0f, 1.0f, 20, 0, 75, 255 },
        { 0.0f, 0.0f, -130.0f, 0.2f, 0.11f },
        { -40.0f, 0.0f, 80.0f },
        1,
        1,
    },
    {
        { 0, 0, aVsTimeTrialCardTex, 0, 96, 10, 110.0f, 138.0f, 1.0f, 1.0f, 20, 0, 75, 255 },
        { 0.0f, -11.0f, -130.0f, 0.2f, 0.11f },
        { -40.0f, -11.0f, 80.0f },
        1,
        1,
    },
};

u8 sSoundMode[] = { SOUNDMODE_STEREO, SOUNDMODE_MONO, SOUNDMODE_HEADSET };

u8 D_menu_801AE99C[] = { 0, 1, 2 };

f32 D_menu_801AE9A0[4] = { 62.0f, 222.0f, 75.0f, 235.0f };

f32 D_menu_801AE9B0[4] = { 43.0f, 43.0f, 46.0f, 46.0f };

OptionCardTexture D_menu_801AE9C0[4] = {
    { 2, 0, aSpeakerTex, aSpeakerTLUT, 32, 32, 56.0f, 175.0f, 1.0f, 1.0f, 255, 255, 255, 255 },
    { 2, 0, aSpeakerTex, aSpeakerTLUT, 32, 32, 216.0f, 175.0f, 1.0f, 1.0f, 255, 255, 255, 255 },
    { 1, 0, aSpeakerCenterTex, aSpeakerCenterTLUT, 16, 16, 69.0f, 178.0f, 1.0f, 1.0f, 255, 255, 255, 255 },
    { 1, 0, aSpeakerCenterTex, aSpeakerCenterTLUT, 16, 16, 229.0f, 178.0f, 1.0f, 1.0f, 255, 255, 255, 255 },
};

OptionCardTexture D_menu_801AEAA0[3] = {
    { 3, 0, aSliderFrameTex, 0, 104, 10, 151.0f, 135.0f, 1.05f, 1.0f, 255, 255, 255, 255 },
    { 3, 0, aSliderFrameTex, 0, 104, 10, 151.0f, 161.0f, 1.05f, 1.0f, 255, 255, 255, 255 },
    { 3, 0, aSliderFrameTex, 0, 104, 10, 151.0f, 188.0f, 1.05f, 1.0f, 255, 255, 255, 255 },
};

OptionCardTexture D_menu_801AEB48[3] = {
    { 3, 0, aSliderTex, 0, 16, 16, 245.0f, 132.0f, 1.0f, 1.0f, 255, 255, 255, 255 },
    { 3, 0, aSliderTex, 0, 16, 16, 245.0f, 158.0f, 1.0f, 1.0f, 255, 255, 255, 255 },
    { 3, 0, aSliderTex, 0, 16, 16, 245.0f, 185.0f, 1.0f, 1.0f, 255, 255, 255, 255 },
};

Vtx D_menu_801AEBF0[] = {
    { 1, 1, 0, 0, 0, 0, 255, 255, 255, 255 },
    { -1, 1, 0, 0, 0, 0, 255, 255, 255, 255 },
    { -1, 0, 0, 0, 0, 0, 255, 255, 255, 255 },
    { 1, 0, 0, 0, 0, 0, 255, 255, 255, 255 },
};

Gfx D_menu_801AEC30[] = {
    gsSPVertex(D_menu_801AEBF0, 4, 0),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsSPEndDisplayList(),
};

Vtx D_menu_801AEC48[] = {
    { 1, 0, 0, 0, 0, 0, 255, 255, 255, 255 },
    { -1, 0, 0, 0, 0, 0, 255, 255, 255, 255 },
    { -1, -1, 0, 0, 0, 0, 255, 255, 255, 255 },
    { 1, -1, 0, 0, 0, 0, 255, 255, 255, 255 },
};

Gfx D_menu_801AEC88[] = {
    gsSPVertex(D_menu_801AEC48, 4, 0),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsSPEndDisplayList(),
};

Vtx D_menu_801AECA0[] = {
    { 1, 1, 0, 0, 0, 0, 255, 255, 255, 255 },
    { -1, 1, 0, 0, 0, 0, 255, 255, 255, 255 },
    { -1, -1, 0, 0, 0, 0, 255, 255, 255, 255 },
    { 1, -1, 0, 0, 0, 0, 255, 255, 255, 255 },
};

Gfx D_menu_801AECE0[] = {
    gsSPVertex(D_menu_801AECA0, 4, 0),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsSPEndDisplayList(),
};

u8* D_menu_801AECF8[10] = {
    aLargeText_0, aLargeText_1, aLargeText_2, aLargeText_3, aLargeText_4,
    aLargeText_5, aLargeText_6, aLargeText_7, aLargeText_8, aLargeText_9,
};
f32 D_menu_801AED20[2] = { 255.0f, 255.0f };

// TF is this? seems unused
s32 D_menu_801AED28[] = {
    /* EE73E8 801AED28 00000038 */ 56,
    /* EE73EC 801AED2C 00000043 */ 67,
    /* EE73F0 801AED30 0000004E */ 78,
    /* EE73F4 801AED34 00000059 */ 89,
    /* EE73F8 801AED38 0000005B */ 91,
};

s32 D_menu_801AED3C[4] = { 0, 0, 0, 0 };

RouteColoredLine sRouteColoredLine[24] = {
    { 9, 0, 0 },  { 0, 12, 0 }, { 12, 4, 0 }, { 4, 10, 0 }, { 10, 2, 0 }, { 6, 4, 0 },   { 7, 2, 0 }, { 3, 2, 0 },
    { 2, 14, 0 }, { 5, 6, 1 },  { 6, 13, 1 }, { 13, 7, 1 }, { 4, 7, 1 },  { 12, 13, 1 }, { 8, 7, 1 }, { 9, 5, 2 },
    { 5, 11, 2 }, { 11, 8, 2 }, { 8, 3, 2 },  { 3, 1, 2 },  { 7, 1, 2 },  { 1, 14, 2 },  { 0, 6, 3 }, { 4, 3, 4 },
};

Gfx* D_menu_801AEE6C[16] = {
    aMapMeteorDL,  aMapArea6DL,   aMapBolseDL,  aMapSectorZDL,  aMapSectorXDL, aMapSectorYDL,
    gMapKatinaDL,  gMapMacbethDL, gMapZonessDL, gMapCorneriaDL, gMapTitaniaDL, gMapAquasDL,
    gMapFortunaDL, aMapSolarDL,   gMapVenomDL,  gMapVenomDL,
};

char* D_menu_801AEEAC[] = {
    "ME", "A6", "BO", "SZ", "SX", "SY", "KA", "MA", "ZO", "CO", "TI", "AQ", "FO", "SO", "VE", "VE",
};

s32 PAD_menu_801AEEEC = 0;

Vtx D_menu_801AEEF0[] = {
    { -11, -11, 0, 0, 0, 255, 0, 0, 0, 0 },
    { 11, -11, 0, 0, 255, 255, 0, 0, 0, 0 },
    { 11, 11, 0, 0, 255, 0, 0, 0, 0, 0 },
    { -11, 11, 0, 0, 0, 0, 0, 0, 0, 0 },
};

Gfx D_menu_801AEF30[] = {
    gsSPVertex(D_menu_801AEEF0, 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSPEndDisplayList(),
};

s32 PAD_menu_801AEF50[] = { 0, 0, 0 };

char sCharMap[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.";

f32 D_menu_801AEF84[] = { 24.0f, 0.0f, -24.0f };
f32 D_menu_801AEF90[] = { 111.0f, 112.0f, 121.0f };
f32 D_menu_801AEF9C[] = { 89.0f, 115.0f, 139.0f };

void Option_Setup(void) {
    bool enableExpertModes;
    bool playedExpertMode;
    s32 i;

    // @port: Force expert mode: Warning this
    if (CVarGetInteger("gForceExpertMode", 0) == 1) {
        for (i = 0; i < ARRAY_COUNT(gSaveFile.save.data.planet); i++) {
            gSaveFile.save.data.planet[i].expertClear = 1;
            gSaveFile.save.data.planet[i].normalClear = 1;
            gSaveFile.save.data.planet[i].normalMedal = 1;
            gSaveFile.save.data.planet[i].expertMedal = 1;
            gSaveFile.save.data.planet[i].played = 1;
        }
    }
    gVIsPerFrame = 2;

    sOptionCardList[OPTION_MAP].tex.texture = aMainGameCardTex;
    sOptionCardList[OPTION_MAP].tex.width = 72;
    sOptionCardList[OPTION_MAP].tex.height = 12;
    sOptionCardList[OPTION_SOUND].tex.texture = aSoundCardTex;
    sOptionCardList[OPTION_SOUND].tex.width = 64;
    sOptionCardList[OPTION_SOUND].tex.height = 10;

    for (i = 0; i < ARRAY_COUNT(sOptionCardList); i++) {
        sOptionCardCurTextPosX[i] = sOptionCardTextPosX[i];
        sOptionCardCurTextPosY[i] = sOptionCardTextPosY[i];
    }

    enableExpertModes = true;
    for (i = 0; i < ARRAY_COUNT(gSaveFile.save.data.planet); i++) {
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

    sExpertModesEnabled = enableExpertModes;

    gFillScreenRed = 0;
    gFillScreenGreen = 0;
    gFillScreenBlue = 0;
    gFillScreenAlpha = 0;

    gBlurAlpha = 255;
    gBgColor = 0;

    sMainMenuCursor = OPTION_MAP;
    if ((gLastGameState == GSTATE_PLAY) && (gCurrentLevel == LEVEL_TRAINING)) {
        gLastGameState = GSTATE_NONE;
        sMainMenuCursor = OPTION_TRAINING;
    }

    sVsMenuCursor = 0;
    sExpertSoundCursor = 0;
    sExpertModeCursor = 0;
    playedExpertMode = gExpertMode;
    gExpertMode = false;

    gGameFrameCount = 0;
    sWipeHeight = 0;
    D_menu_801B9178 = 0;
    D_menu_801B917C = 0;

    sMenuEntryState = OPTION_MAIN_MENU;

    if ((gLastGameState == GSTATE_GAME_OVER) || (gLastGameState == GSTATE_ENDING)) {
        if (gLastGameState == GSTATE_ENDING) {
            gMissionPlanet[gMissionNumber] = PLANET_VENOM;
            if (gLeveLClearStatus[LEVEL_VENOM_ANDROSS] == 1) {
                gSaveFile.save.data.planet[SAVE_SLOT_VENOM_1].played = 1;
                if (playedExpertMode) {
                    gSaveFile.save.data.planet[SAVE_SLOT_VENOM_1].expertClear = 1;
                } else {
                    gSaveFile.save.data.planet[SAVE_SLOT_VENOM_1].normalClear = 1;
                }
                Save_Write();
            } else if (gLeveLClearStatus[LEVEL_VENOM_ANDROSS] == 2) {
                gMissionMedal[gMissionNumber] = 1;
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

        Title_GetRankTotalHits();

        sRankInPos = Option_RankInPos_Check();

        if (sRankInPos != -1) {
            sMenuEntryState = OPTION_NAME_ENTRY;
        } else {
            sMenuEntryState = OPTION_SCORE;
        }
    } else if (D_game_800D2870) {
        sMainMenuCursor = OPTION_VERSUS;
        sVsMenuCursor = gVsMatchType;
        for (i = 0; i < ARRAY_COUNT(sOptionCardList); i++) {
            if (i == OPTION_VERSUS) {
                continue;
            }
            sOptionCardList[i].frame.xScale = 0.01f;
            sOptionCardList[i].frame.yScale = 0.21f;
            sOptionCardList[i].frame.y = sOptionCardPosY[i];
            sOptionCardList[i].frame.x = 0.0f;
            sOptionCardList[i].frame.z = 0.0f;
            sOptionCardList[i].drawFrame = false;

            sOptionCardList[i].tex.xScale = 0.01f;
            sOptionCardList[i].tex.yScale = 1.0f;
            sOptionCardList[i].tex.xPos = 158.0f;
            sOptionCardList[i].tex.yPos = sOptionCardCurTextPosY[i];
            sOptionCardList[i].drawTex = false;
        }
        sOptionCardList[OPTION_VERSUS].frame.x = 0.0f;
        sOptionCardList[OPTION_VERSUS].frame.z = 0.0f;
        sOptionCardList[OPTION_VERSUS].frame.y = 90.0f;
        sOptionCardList[OPTION_VERSUS].frame.xScale = 0.4f;
        sOptionCardList[OPTION_VERSUS].frame.yScale = 0.21f;
        sOptionCardList[OPTION_VERSUS].drawFrame = true;
        sOptionCardList[OPTION_VERSUS].tex.xScale = 1.0f;
        sOptionCardList[OPTION_VERSUS].tex.yScale = 1.0f;
        sOptionCardList[OPTION_VERSUS].tex.xPos = 145.0f;
        sOptionCardList[OPTION_VERSUS].tex.yPos = 25.0f;
        sOptionCardList[OPTION_VERSUS].drawTex = true;

        sMenuEntryState = OPTION_VERSUS;
    } else {
        sMenuEntryState = OPTION_MAIN_MENU;
    }

    sMainMenuState = 0;
    D_menu_801B9134 = 0;
    D_menu_801B913C = 0;

    gOptionMenuStatus = OPTION_UPDATE;

    Memory_FreeAll();

    gStarfieldX = SCREEN_WIDTH;
    gStarfieldY = SCREEN_HEIGHT;

    Play_GenerateStarfield();

    gCsCamEyeX = 0.0f;
    gCsCamEyeY = 0.0f;
    gCsCamEyeZ = 10.0f;
    gCsCamAtX = 0.0f;
    gCsCamAtY = 0.0f;
    gCsCamAtZ = 0.0f;

    sArwingLightXrot = -80.0f;
    sArwingLightYrot = 0.0f;

    sArwingLightColR = 225;
    sArwingLightColG = 225;
    sArwingLightColB = 225;
    sArwingLightAmbR = 30;
    sArwingLightAmbG = 30;
    sArwingLightAmbB = 30;

    D_menu_801B91F8 = 0.1f;
    D_menu_801B91F4 = -130.0f;
    sRightArwingCursorYrot = 0.0f;
    sLeftArwingCursorYrot = 0.0f;

    sOkConfirmTimer = 0;
    sMainMenuFromCancel = false;
    sVsSubMenuFromCancel = false;
    AUDIO_PLAY_BGM(NA_BGM_SELECT);
}

void Option_Main(void) {
#if 0 // Docs debug
    {
        RCP_SetupDL(&gMasterDisp, SETUPDL_83);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);
        Graphics_DisplaySmallNumber(80, 220, sVsSubMenuFromCancel);
    }
#endif
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
                AUDIO_SET_SPEC(SFXCHAN_0, AUDIOSPEC_23);
            }
            break;

        case OPTION_SETUP:
            gDrawMode = DRAW_NONE;
            Option_Setup();
            break;

        case OPTION_UPDATE:
            gDrawMode = DRAW_OPTION;
            Option_Entry_Update();
            break;
    }
    gGameFrameCount++;
}

void Option_Entry_Update(void) {
    switch (sMenuEntryState) {
        case OPTION_MAIN_MENU:
            Option_MainMenu_Update();
            break;

        case OPTION_MAP:
            Option_Map_Update();
            break;

        case OPTION_TRAINING:
            Option_Training_Update();
            break;

        case OPTION_VERSUS:
            Option_Versus_Update();
            break;

        case OPTION_RANKING:
            Option_Ranking_Update();
            break;

        case OPTION_SOUND:
            Option_Sound_Update();
            break;

        case OPTION_DATA:
            Option_Data_Update();
            break;

        case OPTION_EXPERT_SOUND:
            Option_ExpertSound_Update();
            break;

        case OPTION_VERSUS_STAGE:
            Option_VersusStage_Update();
            break;

        case OPTION_POINT_MATCH:
        case OPTION_BR_MATCH:
        case OPTION_TT_MATCH:
            Option_VersusMenu_Update();
            break;

        case OPTION_NAME_ENTRY:
            Option_NameEntry_Update();
            break;

        case OPTION_SCORE:
            Option_Score_Update();
            break;

        case OPTION_INVOICE:
            Option_Invoice_Update();
            break;
    }

    if (sDrawCursor) {
        sRightArwingCursorYrot += 3.8f;
        sLeftArwingCursorYrot += 4.2f;
    }
}

void Option_Entry_Draw(void) {
    switch (sMenuEntryState) {
        case OPTION_MAIN_MENU:
            Option_MainMenu_Draw();
            break;

        case OPTION_VERSUS:
            Option_Versus_Draw();
            break;

        case OPTION_RANKING:
            Option_Ranking_Draw();
            break;

        case OPTION_SOUND:
            Option_Sound_Draw();
            break;

        case OPTION_EXPERT_SOUND:
            Option_ExpertSound_Draw();
            break;

        case OPTION_DATA:
            Option_Data_Draw();
            break;

        case OPTION_VERSUS_STAGE:
            Option_VersusStage_Draw();
            break;

        case OPTION_POINT_MATCH:
        case OPTION_BR_MATCH:
        case OPTION_TT_MATCH:
            Option_VersusMenu_Draw();
            break;

        case OPTION_NAME_ENTRY:
            Option_NameEntry_Draw();
            break;

        case OPTION_SCORE:
            Option_Score_Draw();
            break;

        case OPTION_INVOICE:
            Option_InvoiceDraw();
            break;
    }

    if (sLevelStartState) {
        Option_Menu_Push();
        Wipe_Draw(WIPE_VERTICAL, sWipeHeight);
        Matrix_Pop(&gGfxMatrix);
    }
}

void Option_Entry_Setup(void) {
    gBlurAlpha = 255;
    sMainMenuState = 0;

    switch (sMenuEntryState) {
        case OPTION_MAP:
            gDrawMode = DRAW_NONE;
            break;

        case OPTION_POINT_MATCH:
        case OPTION_BR_MATCH:
        case OPTION_TT_MATCH:
            Option_VersusMenu_Setup();
            break;

        case OPTION_VERSUS_STAGE:
            Option_VersusStage_Setup();
            break;

        case OPTION_RANKING:
            Option_Ranking_Setup();
            break;

        case OPTION_SOUND:
            Option_Sound_Setup();
            break;

        case OPTION_EXPERT_SOUND:
            Option_ExpertSound_Setup();
            break;

        case OPTION_DATA:
            Option_Data_Setup();
            break;
    }
}

// Initialize the Planet textures before any drawing occurs
void Option_PlanetTextures_Setup(void) {
    s32 i;

    D_menu_801B93E8 = 0;
    D_menu_801B93EC = 0;

    for (i = 0; i < (96 * 96); i++) {
        // Planet Textures
        gMapCorneriaTex[i] = 106;
        gMapFortunaTex[i] = 84;
        gMapAquasTex[i] = 75;
        gMapVenomTex[i] = 81;
        gMapTitaniaTex[i] = 55;
        gMapKatinaTex[i] = 82;
        gMapMacbethTex[i] = 68;
        gMapZonessTex[i] = 52;
        gMapVenomCloudTex[i] = 0;
    }

    for (i = 0; i < ARRAY_COUNT(gBSSMapPlanetTextures); i++) {
        D_menu_801CD818[i] = 0.0f;
        Map_Texture_Sphere(gBSSMapPlanetTextures[i], SEGMENTED_TO_VIRTUAL(gAssetMapPlanetTextures[i]),
                           &D_menu_801CD818[i]);
    }
}

void Option_ScrollPlanetTexture(void) {
    if (D_menu_801B93E8 == 5) {
        Map_Texture_Sphere(gBSSMapPlanetTextures[8], SEGMENTED_TO_VIRTUAL(gAssetMapPlanetTextures[8]),
                           &D_menu_801CD818[8]);
        D_menu_801B93E8 = 0;
    } else {
        D_menu_801B93E8++;
    }

    Map_Texture_Sphere(gBSSMapPlanetTextures[D_menu_801B93EC * 2],
                       SEGMENTED_TO_VIRTUAL(gAssetMapPlanetTextures[D_menu_801B93EC * 2]),
                       &D_menu_801CD818[D_menu_801B93EC * 2]);

    Map_Texture_Sphere(gBSSMapPlanetTextures[(D_menu_801B93EC * 2) + 1],
                       SEGMENTED_TO_VIRTUAL(gAssetMapPlanetTextures[(D_menu_801B93EC * 2) + 1]),
                       &D_menu_801CD818[(D_menu_801B93EC * 2) + 1]);

    D_menu_801B93EC++;
    if (D_menu_801B93EC >= 4) {
        D_menu_801B93EC = 0;
    }
}

void Option_Map_Update(void) {
    if (gFillScreenAlpha == 255) {
        gStarCount = 0;
        sMenuEntryState = 100;
        gGameState = GSTATE_MAP;
        gNextGameStateTimer = 2;
        gMapState = 0;
        gDrawMode = DRAW_NONE;
        gControllerLock = 3;
    } else {
        gFillScreenAlpha += 32;
        if (gFillScreenAlpha > 255) {
            gFillScreenAlpha = 255;
        }
    }
}

void Option_Training_Update(void) {
    if (gFillScreenAlpha == 255) {
        gCurrentLevel = LEVEL_TRAINING;
        gGameState = GSTATE_PLAY;
        gNextGameStateTimer = 2;
        gPlayState = PLAY_STANDBY;
        gDrawMode = DRAW_NONE;
        Play_Setup();
        gSavedObjectLoadIndex = 0;
        gSavedPathProgress = 0.0f;
        D_ctx_8017782C = true;
        gControllerLock = 3;
        AUDIO_SET_SPEC(SFXCHAN_0, AUDIOSPEC_28);
    } else {
        gFillScreenAlpha += 32;
        if (gFillScreenAlpha > 255) {
            gFillScreenAlpha = 255;
        }
    }
}

void Option_MainMenu_Setup(void) {
    s32 i;

    D_game_800D2870 = false;
    gBlurAlpha = 255;
    gControllerLock = 0;
    gStarCount = 800;
    sVsSubMenuFromCancel = false;

    if (!sMainMenuFromCancel) {
        sDrawCursor = true;
        for (i = 0; i < ARRAY_COUNT(sOptionCardList); i++) {
            sOptionCardList[i].tex.xPos = sOptionCardCurTextPosX[i];
            sOptionCardList[i].tex.yPos = sOptionCardCurTextPosY[i];
            sOptionCardList[i].tex.xScale = 1.0f;
            sOptionCardList[i].tex.yScale = 1.0f;
            sOptionCardList[i].drawTex = true;

            sOptionCardList[i].frame.xScale = 0.4f;
            sOptionCardList[i].frame.yScale = 0.21f;
            sOptionCardList[i].frame.y = sOptionCardPosY[i];
            sOptionCardList[i].frame.z = 0.0f;
            sOptionCardList[i].drawFrame = true;
        }
    } else {
        sDrawCursor = false;
        for (i = 0; i < ARRAY_COUNT(sOptionCardList); i++) {
            sOptionCardList[i].tex.yScale = 1.0f;
            sOptionCardList[i].frame.yScale = 0.21f;
            sOptionCardList[i].frame.z = 0.0f;
            sOptionCardList[i].drawFrame = true;
            sOptionCardList[i].drawTex = true;
        }
    }

    sLightningXpos = -45.0f;
    D_menu_801B9214 = 0;

    D_menu_801B9180.unk_0 = 0;
    D_menu_801B9180.unk_4 = 0;
    D_menu_801B9190.unk_0 = 0;
    D_menu_801B9190.unk_4 = 0;
    D_menu_801B9198.unk_0 = 0;
    D_menu_801B9198.unk_4 = 0;
}

void Option_MainMenu_Update(void) {
    s32 i;
    f32 var_fs0;
    f32 var_fs1;

    switch (sMainMenuState) {
        case 0:
            Option_MainMenu_Setup();
            if (!sMainMenuFromCancel) {
                sMainMenuState++;
            } else {
                sOptionCardCurTextPosX[0] = D_menu_801AE5E8[sExpertModeCursor];
                sOptionCardCurTextPosY[0] = D_menu_801AE5F0[sExpertModeCursor];
                sOptionCardCurTextPosX[4] = D_menu_801AE5F8[sExpertSoundCursor];
                sOptionCardCurTextPosY[4] = D_menu_801AE600[sExpertSoundCursor];
                sMainMenuState = 1000;
            }
            break;

        case 1000:
            for (i = 0; i < ARRAY_COUNT(sOptionCardList); i++) {
                if (sOptionCardList[i].frame.xScale < 0.4f) {
                    sOptionCardList[i].frame.xScale += 0.04f;
                    if (sOptionCardList[i].frame.xScale > 0.4f) {
                        sOptionCardList[i].frame.xScale = 0.4f;
                    }
                }
                if (sOptionCardList[i].tex.xScale < 1.0f) {
                    sOptionCardList[i].tex.xScale += 0.1f;
                    if (sOptionCardList[i].tex.xScale > 1.0f) {
                        sOptionCardList[i].tex.xScale = 1.0f;
                    }
                }

                Math_SmoothStepToF(&sOptionCardList[i].tex.yPos, sOptionCardCurTextPosY[i], 0.15f, 100.0f, 0.1f);
                Math_SmoothStepToF(&sOptionCardList[i].frame.y, sOptionCardPosY[i], 0.15f, 100.0f, 0.1f);
                Math_SmoothStepToF(&sOptionCardList[i].tex.xPos, sOptionCardCurTextPosX[i], 0.2f, D_menu_801AE620[i],
                                   0.1f);
            }

            gBlurAlpha += 4;

            if (sOptionCardList[sMainMenuCursor].frame.y == sOptionCardPosY[sMainMenuCursor]) {
                for (i = 0; i < ARRAY_COUNT(sOptionCardList); i++) {
                    sOptionCardList[i].tex.xScale = 1.0f;
                    sOptionCardList[i].tex.xPos = sOptionCardCurTextPosX[i];
                    sOptionCardList[i].tex.yPos = sOptionCardCurTextPosY[i];
                }
                sDrawCursor = true;
                gBlurAlpha = 255;
                sMainMenuState = 1;
            }
            break;

        case 1:
            // clang-format off
            if (Option_Input_MoveCursor_Y(&sMainMenuCursor, ARRAY_COUNT(sOptionCardList) - 1, 1, 0, 20, 5, 4, gMainController, &D_menu_801B9180)) { \
                AUDIO_PLAY_SFX(NA_SE_ARWING_CURSOR, gDefaultSfxSource, 4);
            }
            // clang-format on

            if ((sMainMenuCursor == OPTION_MAP) && sExpertModesEnabled &&
                Option_Input_MoveCursor_Y(&sExpertModeCursor, 1, 0, 0, 20, 5, 4, gMainController, &D_menu_801B9190)) {
                AUDIO_PLAY_SFX(NA_SE_ARWING_CURSOR, gDefaultSfxSource, 4);
                if (sExpertModeCursor) {
                    sOptionCardList[OPTION_MAP].tex.texture = aExpertCardTex;
                    sOptionCardList[OPTION_MAP].tex.width = 80;
                    sOptionCardList[OPTION_MAP].tex.height = 12;
                    sOptionCardList[OPTION_MAP].tex.xPos = 125.0f;
                    sOptionCardList[OPTION_MAP].tex.yPos = 55.0f;
                } else {
                    sOptionCardList[OPTION_MAP].tex.texture = aMainGameCardTex;
                    sOptionCardList[OPTION_MAP].tex.width = 72;
                    sOptionCardList[OPTION_MAP].tex.height = 12;
                    sOptionCardList[OPTION_MAP].tex.xPos = 124.0f;
                    sOptionCardList[OPTION_MAP].tex.yPos = 54.0f;
                }
                gExpertMode = sExpertModeCursor;
            }

            if ((sMainMenuCursor == OPTION_SOUND) && sExpertModesEnabled &&
                Option_Input_MoveCursor_Y(&sExpertSoundCursor, 1, 0, 0, 20, 5, 4, gMainController, &D_menu_801B9198)) {
                AUDIO_PLAY_SFX(NA_SE_ARWING_CURSOR, gDefaultSfxSource, 4);
                if (sExpertSoundCursor) {
                    sOptionCardList[OPTION_SOUND].tex.texture = aExpertCardTex;
                    sOptionCardList[OPTION_SOUND].tex.width = 80;
                    sOptionCardList[OPTION_SOUND].tex.height = 12;
                    sOptionCardList[OPTION_SOUND].tex.xPos = 125.0f;
                    sOptionCardList[OPTION_SOUND].tex.yPos = 151.0f;
                } else {
                    sOptionCardList[OPTION_SOUND].tex.texture = aSoundCardTex;
                    sOptionCardList[OPTION_SOUND].tex.width = 64;
                    sOptionCardList[OPTION_SOUND].tex.height = 10;
                    sOptionCardList[OPTION_SOUND].tex.xPos = 133.0f;
                    sOptionCardList[OPTION_SOUND].tex.yPos = 151.0f;
                }
            }

            if (gControllerPress[gMainController].button & (A_BUTTON | START_BUTTON)) {
#if DEBUG_VERSUS == 0
                if (sMainMenuCursor == 2) {
                    break;
                }
#endif
                AUDIO_PLAY_SFX(NA_SE_ARWING_DECIDE, gDefaultSfxSource, 4);
                sLightningYpos = sOptionCardPosY[sMainMenuCursor];
                sDrawCursor = false;
                sMainMenuState = 11;
            }
            if (gControllerPress[gMainController].button & B_BUTTON) {
                AUDIO_PLAY_SFX(NA_SE_ARWING_CANCEL, gDefaultSfxSource, 4);
                sWipeHeight = 0;
                sLevelStartState = 1;
                sMainMenuState = 100;
            }
            break;

        case 11:
            gBlurAlpha = 16;
            D_menu_801B9178 = 3;
            sOptionCardList[sMainMenuCursor].frame.xScale -= 0.01f;
            sOptionCardList[sMainMenuCursor].frame.yScale -= 0.01f;
            sOptionCardList[sMainMenuCursor].tex.xScale -= 0.1f;
            sOptionCardList[sMainMenuCursor].tex.yScale -= 0.1f;
            sOptionCardList[sMainMenuCursor].tex.xPos += 4.0f;
            D_menu_801B917C = 3;
            sMainMenuState++;
            break;

        case 12:
            if (D_menu_801B9178 == 1) {
                sOptionCardList[sMainMenuCursor].frame.xScale += 0.01f;
                sOptionCardList[sMainMenuCursor].frame.yScale += 0.01f;
                sOptionCardList[sMainMenuCursor].tex.xScale += 0.1f;
                sOptionCardList[sMainMenuCursor].tex.yScale += 0.1f;
                sOptionCardList[sMainMenuCursor].tex.xPos -= 4.0f;
                D_menu_801B9214 = 1;
            }

            for (i = 0; i < ARRAY_COUNT(sOptionCardList); i++) {
                if (i == sMainMenuCursor) {
                    continue;
                }

                if (sOptionCardList[i].frame.xScale > 0.01f) {
                    sOptionCardList[i].frame.xScale -= 0.05f;
                    sOptionCardList[i].tex.xScale -= 0.19f;
                    Math_SmoothStepToF(&sOptionCardList[i].tex.xPos, 158.0f, 0.2f, D_menu_801AE608[i], 0.1f);
                } else {
                    sOptionCardList[i].drawFrame = false;
                    sOptionCardList[i].drawTex = false;
                }
            }

            if (D_menu_801B917C == 0) {
                var_fs0 = 25.0f;
                var_fs1 = 90.0f;

                if ((sMainMenuCursor == OPTION_MAP) || (sMainMenuCursor == OPTION_TRAINING)) {
                    var_fs0 = 0.0f;
                    var_fs1 = 120.0f;
                }

                Math_SmoothStepToF(&sOptionCardList[sMainMenuCursor].tex.yPos, var_fs0, 0.25f, 100.0f, 0.1f);
                Math_SmoothStepToF(&sOptionCardList[sMainMenuCursor].frame.y, var_fs1, 0.25f, 100.0f, 0.1f);

                gBlurAlpha += 4;

                if ((sOptionCardList[sMainMenuCursor].tex.yPos == var_fs0) &&
                    (sOptionCardList[sMainMenuCursor].frame.y == var_fs1)) {
                    gBlurAlpha += 255;
                    sMenuEntryState = sMainMenuCursor;

                    if ((sMainMenuCursor == OPTION_SOUND) && sExpertSoundCursor) {
                        sMenuEntryState = OPTION_EXPERT_SOUND;
                    }
                    Option_Entry_Setup();
                }
            }
            break;

        case 100:
            if (sWipeHeight < 120) {
                sWipeHeight += 18;
            } else {
                gStarCount = 0;
                gGameState = GSTATE_TITLE;
                gNextGameStateTimer = 2;
                gTitleState = 0;
                gGoToTitle = true;
                gDrawMode = DRAW_NONE;
                sLevelStartState = 0;
                sWipeHeight = 0;
                gControllerLock = 3;
            }
            break;
    }
}

void Option_MainMenu_Draw(void) {
    s32 i;

    Option_Menu_Push();

    for (i = 0; i < ARRAY_COUNT(sOptionCardList); i++) {
        if (sOptionCardList[i].drawFrame) {
            Option_DrawMenuCard(sOptionCardList[i].frame);
        }
    }

    Option_DrawMenuArwing(sOptionCardList[sMainMenuCursor].pos);
    Matrix_Pop(&gGfxMatrix);

    for (i = 0; i < ARRAY_COUNT(sOptionCardList); i++) {
        if (!(sOptionCardList[i].drawTex) || (sOptionCardList[i].tex.xScale) <= 0.0f) {
            continue;
        }
        if ((i == 0) && sExpertModesEnabled && ((sMainMenuState == 0) || (sMainMenuState == 1))) {
            Option_VsSelectionArrows_Draw(106.0f, 56.0f, 98.0f, 20, 0, 75);
        }
        if ((i == 4) && sExpertModesEnabled && ((sMainMenuState == 0) || (sMainMenuState == 1))) {
            Option_VsSelectionArrows_Draw(106.0f, 152.0f, 98.0f, 20, 0, 75);
        }
        Option_DrawCardLabel(sOptionCardList[i].tex);
    }

    Option_CardLightning_Update();
}

void Option_Versus_Setup(void) {
    s32 i;

    gBlurAlpha = 255;
    gControllerLock = 0;
    gStarCount = 800;

    if (!sVsSubMenuFromCancel) {
        sDrawCursor = true;

        for (i = 0; i < ARRAY_COUNT(sOptionVSCardList); i++) {
            sOptionVSCardList[i].tex.xPos = D_menu_801AEF90[i];
            sOptionVSCardList[i].tex.yPos = D_menu_801AEF9C[i];
            sOptionVSCardList[i].tex.xScale = 1.0f;
            sOptionVSCardList[i].tex.yScale = 1.0f;
            sOptionVSCardList[i].drawTex = true;
            sOptionVSCardList[i].frame.xScale = 0.4f;
            sOptionVSCardList[i].frame.yScale = 0.21f;
            sOptionVSCardList[i].frame.y = D_menu_801AEF84[i];
            sOptionVSCardList[i].frame.z = 0.0f;
            sOptionVSCardList[i].drawFrame = true;
        }
    } else {
        sDrawCursor = false;

        for (i = 0; i < ARRAY_COUNT(sOptionVSCardList); i++) {
            sOptionVSCardList[i].tex.yScale = 1.0f;
            sOptionVSCardList[i].frame.yScale = 0.21f;
            sOptionVSCardList[i].frame.z = 0.0f;
            sOptionVSCardList[i].drawTex = true;
            sOptionVSCardList[i].drawFrame = true;
        }
    }

    sLightningXpos = -45.0f;
    D_menu_801B9214 = 0;
    D_menu_801B9188.unk_0 = 0;
    D_menu_801B9188.unk_4 = 0;
}

void Option_Versus_Update(void) {
    f32 var_fs0;
    s32 i;

    switch (sMainMenuState) {
        case 0:
            Option_Versus_Setup();
            if (!sVsSubMenuFromCancel) {
                sMainMenuState++;
            } else {
                sMainMenuState = 1000;
            }
            break;

        case 1000:
            for (i = 0; i < ARRAY_COUNT(sOptionVSCardList); i++) {
                if (sOptionVSCardList[i].frame.xScale < 0.4f) {
                    sOptionVSCardList[i].frame.xScale += 0.04f;
                    if (sOptionVSCardList[i].frame.xScale > 0.4f) {
                        sOptionVSCardList[i].frame.xScale = 0.4f;
                    }
                }

                if (sOptionVSCardList[i].tex.xScale < 1.0f) {
                    sOptionVSCardList[i].tex.xScale += 0.15f;
                    if (sOptionVSCardList[i].tex.xScale > 1.0f) {
                        sOptionVSCardList[i].tex.xScale = 1.0f;
                    }
                }

                Math_SmoothStepToF(&sOptionVSCardList[i].frame.y, D_menu_801AEF84[i], 0.15f, 100.0f, 0.1f);
                Math_SmoothStepToF(&sOptionVSCardList[i].tex.xPos, D_menu_801AEF90[i], 0.2f, 3.1f, 0.1f);
                Math_SmoothStepToF(&sOptionVSCardList[i].tex.yPos, D_menu_801AEF9C[i], 0.15f, 100.0f, 0.1f);
            }

            Math_SmoothStepToF(&sOptionCardList[sMainMenuCursor].tex.yPos, 25.0f, 0.25f, 100.0f, 0.1f);
            Math_SmoothStepToF(&sOptionCardList[sMainMenuCursor].frame.y, 90.0f, 0.25f, 100.0f, 0.1f);

            gBlurAlpha += 4;

            if (sOptionVSCardList[sVsMenuCursor].frame.y == D_menu_801AEF84[sVsMenuCursor]) {
                for (i = 0; i < ARRAY_COUNT(sOptionVSCardList); i++) {
                    sOptionVSCardList[i].tex.xScale = 1.0f;
                    sOptionVSCardList[i].tex.yPos = D_menu_801AEF9C[i];
                    sOptionVSCardList[i].tex.xPos = D_menu_801AEF90[i];
                }

                sOptionCardList[sMainMenuCursor].tex.yPos = 25.0f;
                sOptionCardList[sMainMenuCursor].frame.y = 90.0f;
                sDrawCursor = true;
                gBlurAlpha = 255;
                sMainMenuState = 1;
            }
            break;

        case 1:
            // clang-format off
            if (Option_Input_MoveCursor_Y(&sVsMenuCursor, 2, 1, 0, 20, 5, 4, gMainController, &D_menu_801B9188)) {\
                AUDIO_PLAY_SFX(NA_SE_ARWING_CURSOR, gDefaultSfxSource, 4);\
            }
            // clang-format on

            if (gControllerPress[gMainController].button & (A_BUTTON | START_BUTTON)) {
                AUDIO_PLAY_SFX(NA_SE_ARWING_DECIDE, gDefaultSfxSource, 4);
                sLightningYpos = D_menu_801AEF84[sVsMenuCursor];
                sDrawCursor = false;
                sMainMenuState = 11;
            }

            if (gControllerPress[gMainController].button & B_BUTTON) {
                AUDIO_PLAY_SFX(NA_SE_ARWING_CANCEL, gDefaultSfxSource, 4);
                sMainMenuState = 0;
                sMenuEntryState = OPTION_MAIN_MENU;
                gDrawMode = DRAW_NONE;
                sMainMenuFromCancel = true;
            }
            break;

        case 11:
            gBlurAlpha = 16;
            D_menu_801B9178 = 5;
            sOptionVSCardList[sVsMenuCursor].frame.xScale -= 0.01f;
            sOptionVSCardList[sVsMenuCursor].frame.yScale -= 0.01f;
            sOptionVSCardList[sVsMenuCursor].tex.xScale -= 0.1f;
            sOptionVSCardList[sVsMenuCursor].tex.yScale -= 0.1f;
            sOptionVSCardList[sVsMenuCursor].tex.xPos += 4.0f;
            D_menu_801B917C = 5;
            sMainMenuState++;
            break;

        case 12:
            if (D_menu_801B9178 == 1) {
                sOptionVSCardList[sVsMenuCursor].frame.xScale += 0.01f;
                sOptionVSCardList[sVsMenuCursor].frame.yScale += 0.01f;
                sOptionVSCardList[sVsMenuCursor].tex.xScale += 0.1f;
                sOptionVSCardList[sVsMenuCursor].tex.yScale += 0.1f;
                sOptionVSCardList[sVsMenuCursor].tex.xPos -= 4.0f;
                D_menu_801B9214 = 1;
            }

            for (i = 0; i < ARRAY_COUNT(sOptionVSCardList); i++) {
                if (i == sVsMenuCursor) {
                    continue;
                }

                if (sOptionVSCardList[i].frame.xScale > 0.01f) {
                    sOptionVSCardList[i].frame.xScale -= 0.05f;
                    sOptionVSCardList[i].tex.xScale -= 0.19f;
                    Math_SmoothStepToF(&sOptionVSCardList[i].tex.xPos, 158.0f, 0.2f, D_menu_801AE608[i + 1], 0.1f);
                } else {
                    sOptionVSCardList[i].drawFrame = false;
                    sOptionVSCardList[i].drawTex = false;
                }
            }

            if (D_menu_801B917C == 0) {
                if (sVsMenuCursor == 0) {
                    var_fs0 = 129.0f;
                } else {
                    var_fs0 = 131.0f;
                }

                Math_SmoothStepToF(&sOptionVSCardList[sVsMenuCursor].tex.yPos, var_fs0, 0.25f, 100.0f, 0.1f);
                Math_SmoothStepToF(&sOptionVSCardList[sVsMenuCursor].frame.y, -15.5f, 0.25f, 100.0f, 0.1f);
                Math_SmoothStepToF(&sOptionCardList[sMainMenuCursor].tex.yPos, -10.0f, 0.35f, 100.0f, 0.1f);
                Math_SmoothStepToF(&sOptionCardList[sMainMenuCursor].frame.y, 150.0f, 0.35f, 100.0f, 0.1f);

                gBlurAlpha += 4;

                if ((var_fs0 == sOptionVSCardList[sVsMenuCursor].tex.yPos) &&
                    (sOptionVSCardList[sVsMenuCursor].frame.y == -15.5f)) {
                    gBlurAlpha += 255;
                    sMenuEntryState = (sVsMenuCursor + 1) * 10;
                    gVsMatchType = sVsMenuCursor;
                    D_menu_801B91C4 = 1;
                    Option_Entry_Setup();
                }
            }
            break;
    }
}

void Option_Versus_Draw(void) {
    s32 i;

    Option_DrawMenuLabel();
    Option_Menu_Push();

    for (i = 0; i < ARRAY_COUNT(sOptionVSCardList); i++) {
        if (sOptionVSCardList[i].drawFrame) {
            Option_DrawMenuCard(sOptionVSCardList[i].frame);
        }
    }

    Option_DrawMenuArwing(sOptionVSCardList[sVsMenuCursor].pos);
    Matrix_Pop(&gGfxMatrix);

    for (i = 0; i < ARRAY_COUNT(sOptionVSCardList); i++) {
        if ((sOptionVSCardList[i].drawTex) && !(sOptionVSCardList[i].tex.xScale <= 0.0f)) {
            Option_DrawCardLabel(sOptionVSCardList[i].tex);
        }
    }

    Option_CardLightning_Update();
}

void Option_Sound_Setup(void) {
    s32 i;

    gStarCount = 800;

    D_menu_801B91B4 = 0;
    D_menu_801B91B8 = 0;
    sDrawCursor = true;
    D_menu_801B91A0 = 0;

    gOptionSoundMode = gSaveFile.save.data.soundMode;
    SEQCMD_SET_SOUND_MODE(sSoundMode[gOptionSoundMode]);

    gVolumeSettings[AUDIO_TYPE_MUSIC] = gSaveFile.save.data.musicVolume;
    gVolumeSettings[AUDIO_TYPE_VOICE] = gSaveFile.save.data.voiceVolume;
    gVolumeSettings[AUDIO_TYPE_SFX] = gSaveFile.save.data.sfxVolume;

    if (gVolumeSettings[AUDIO_TYPE_MUSIC] > 99) {
        gVolumeSettings[AUDIO_TYPE_MUSIC] = 99;
    }
    if (gVolumeSettings[AUDIO_TYPE_VOICE] > 99) {
        gVolumeSettings[AUDIO_TYPE_VOICE] = 99;
    }
    if (gVolumeSettings[AUDIO_TYPE_SFX] > 99) {
        gVolumeSettings[AUDIO_TYPE_SFX] = 99;
    }

    Audio_SetVolume(AUDIO_TYPE_MUSIC, gVolumeSettings[AUDIO_TYPE_MUSIC]);
    Audio_SetVolume(AUDIO_TYPE_VOICE, gVolumeSettings[AUDIO_TYPE_VOICE]);
    Audio_SetVolume(AUDIO_TYPE_SFX, gVolumeSettings[AUDIO_TYPE_SFX]);

    D_menu_801AEB48[0].xPos = gVolumeSettings[AUDIO_TYPE_MUSIC] + 146.0f;
    D_menu_801AEB48[1].xPos = gVolumeSettings[AUDIO_TYPE_VOICE] + 146.0f;
    D_menu_801AEB48[2].xPos = gVolumeSettings[AUDIO_TYPE_SFX] + 146.0f;

    D_menu_801B9288 = 0;
    D_menu_801B9284 = 0;
    D_menu_801B914C = 0;
    D_menu_801B9158 = 0;
    D_menu_801B9178 = 0;
    D_menu_801B917C = 0;

    // clang-format off
    for (i = 0; i < ARRAY_COUNT(D_menu_801B9270); i++) { D_menu_801B9270[i] = 255.0f; }
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

void Option_Sound_Update(void) {
    s32 sp34 = D_menu_801B9288;

    if (Option_Input_MoveCursor_Y(&D_menu_801B9288, 3, 1, 0, 20, 5, 4, gMainController, &D_menu_801B9250)) {
        D_menu_801B9270[sp34] = 255.0f;
        AUDIO_PLAY_SFX(NA_SE_CURSOR, gDefaultSfxSource, 4);
    }

    if (D_menu_801B9288 == 0) {
        Option_Sound_SetSoundMode();
    } else {
        Option_Sound_SetVolumeLevels();
    }

    // Test sound
    if (gControllerPress[gMainController].button & R_TRIG) {
        D_menu_801B9284 ^= 1;
        Audio_PlaySoundTest(D_menu_801B9284);
    }

    if (gControllerPress[gMainController].button & A_BUTTON) {
        AUDIO_PLAY_SFX(NA_SE_DECIDE, gDefaultSfxSource, 4);
        D_menu_801B9288 = (D_menu_801B9288 + 1) % 4U;
    }

    if (gControllerPress[gMainController].button & B_BUTTON) {
        AUDIO_PLAY_SFX(NA_SE_ARWING_CANCEL, gDefaultSfxSource, 4);
        if (D_menu_801B9284 == 1) {
            D_menu_801B9284 = 0;
            Audio_PlaySoundTest(D_menu_801B9284);
        }
        Save_Write();
        gDrawMode = DRAW_NONE;
        sMenuEntryState = OPTION_MAIN_MENU;
        sMainMenuState = 0;
        sMainMenuFromCancel = true;
    }
}

void Option_Sound_SetSoundMode(void) {
    s32 sp3C = gOptionSoundMode;
    s32 pad;

    if (Option_Input_MoveCursor_Y(&sp3C, 2, 0, 0, 20, 5, 4, gMainController, &D_menu_801B9260)) {
        AUDIO_PLAY_SFX(NA_SE_CURSOR, gDefaultSfxSource, 4);
        gOptionSoundMode = sp3C;
        if (gOptionSoundMode >= OPTIONSOUND_MAX) {
            gOptionSoundMode = OPTIONSOUND_STEREO;
        }
        gSaveFile.save.data.soundMode = gOptionSoundMode;
        SEQCMD_SET_SOUND_MODE(sSoundMode[gOptionSoundMode]);
    }
}

void Option_Sound_SetVolumeLevels(void) {
    s32 volume;

    D_menu_801B924C = D_menu_801AE99C[D_menu_801B9288 - 1];

    if (Option_Input_Sound_X(&(D_menu_801AEB48[D_menu_801B9288 - 1].xPos), 146.0f, 245.0f, &D_menu_801B9268)) {
        volume = D_menu_801AEB48[D_menu_801B9288 - 1].xPos - 146.0f;

        gVolumeSettings[D_menu_801B9288 - 1] = volume;

        if (volume > 99) {
            volume = 99;
        }

        switch (D_menu_801B9288 - 1) {
            case 0:
                gSaveFile.save.data.musicVolume = volume;
                break;

            case 1:
                gSaveFile.save.data.voiceVolume = volume;
                break;

            case 2:
                gSaveFile.save.data.sfxVolume = volume;
                break;
        }
        Audio_SetVolume(D_menu_801B924C, volume);
    }
}

void Option_Sound_Draw(void) {
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

    Option_Sound_Speaker_Draw();

    RCP_SetupDL(&gMasterDisp, SETUPDL_76_OPTIONAL);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
    Lib_TextureRect_RGBA16(&gMasterDisp, aMapWhiteSquareTex, 8, 8, D_menu_801AEFA8[0], D_menu_801AEFD4[0],
                           D_menu_801AF000, 0.2f);

    RCP_SetupDL(&gMasterDisp, SETUPDL_83_OPTIONAL);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
    Lib_TextureRect_IA8(&gMasterDisp, D_OPT_8005CD0, 112, 13, D_menu_801AEFA8[1], D_menu_801AEFD4[1], 1.0f, 1.0f);

    for (i = 0; i < 4; i++) {
        if (D_menu_801B9288 == i) {
            Option_Color_FlashRed(&D_menu_801B9270[i]);
        } else {
            D_menu_801B9270[i] = 255.0f;
        }
    }

    colorGB = D_menu_801B9270[0];
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, colorGB, colorGB, 255);
    Lib_TextureRect_IA8(&gMasterDisp, D_OPT_8006280, 48, 13, D_menu_801AEFA8[2], D_menu_801AEFD4[2], 1.0f, 1.0f);

    colorGB = D_menu_801B9270[1];
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, colorGB, colorGB, 255);
    Lib_TextureRect_IA8(&gMasterDisp, D_OPT_80064F0, 88, 14, D_menu_801AEFA8[3], D_menu_801AEFD4[3], 1.0f, 1.0f);

    colorGB = D_menu_801B9270[2];
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, colorGB, colorGB, 255);
    Lib_TextureRect_IA8(&gMasterDisp, D_OPT_80069C0, 56, 15, D_menu_801AEFA8[4], D_menu_801AEFD4[4], 1.0f, 1.0f);

    colorGB = D_menu_801B9270[3];
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, colorGB, colorGB, 255);
    Lib_TextureRect_IA8(&gMasterDisp, D_OPT_8006D10, 24, 13, D_menu_801AEFA8[5], D_menu_801AEFD4[5], 1.0f, 1.0f);

    if (D_menu_801B9288 == 0) {
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
        Lib_TextureRect_IA8_MirX(&gMasterDisp, aArrowTex, 8, 8, D_menu_801AEFA8[6], D_menu_801AEFD4[6], 1.0f, 1.0f);
        Lib_TextureRect_IA8(&gMasterDisp, aArrowTex, 8, 8, D_menu_801AEFA8[7], D_menu_801AEFD4[7], 1.0f, 1.0f);
    }

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    switch (gOptionSoundMode) {
        case OPTIONSOUND_STEREO:
            Lib_TextureRect_IA8(&gMasterDisp, D_OPT_800CD90, 56, 13, D_menu_801AEFA8[8], D_menu_801AEFD4[8], 1.0f,
                                1.0f);
            break;

        case OPTIONSOUND_MONO:
            Lib_TextureRect_IA8(&gMasterDisp, D_OPT_80076E0, 56, 14, D_menu_801AEFA8[9], D_menu_801AEFD4[9], 1.0f,
                                1.0f);
            break;

        case OPTIONSOUND_HEADSET:
            Lib_TextureRect_IA8(&gMasterDisp, D_OPT_8007210, 88, 14, D_menu_801AEFA8[10], D_menu_801AEFD4[10], 1.0f,
                                1.0f);
            break;
    }

    Lib_TextureRect_IA8(&gMasterDisp, aBtoCancelTex, 96, 10, 166.0f, 213.0f, 1.0f, 1.0f);

    for (i = 0; i < ARRAY_COUNT(D_menu_801AEAA0); i++) {
        Option_DrawCardLabel(D_menu_801AEAA0[i]);
        Option_DrawCardLabel(D_menu_801AEB48[i]);
    }
}

void Option_Sound_Speaker_Draw(void) {
    s32 i;

    if (D_menu_801B9284 == 1) {
        switch (D_menu_801B914C) {
            case 0:
                D_menu_801B914C++;
                break;

            case 1:
                if (D_menu_801B9178 != 0) {
                    break; // looks fake, but isn't
                }

                for (i = 2; i < ARRAY_COUNT(D_menu_801AE9C0); i++) {
                    D_menu_801AE9C0[i].xScale += 0.02f;
                    D_menu_801AE9C0[i].yScale += 0.02f;
                    D_menu_801AE9C0[i].xPos -= 0.1f;
                }

                D_menu_801B9178 = 2;
                D_menu_801B914C++;
                break;

            case 2:
                if (D_menu_801B9178 == 0) {
                    for (i = 2; i < ARRAY_COUNT(D_menu_801AE9C0); i++) {
                        D_menu_801AE9C0[i].xScale -= 0.02f;
                        D_menu_801AE9C0[i].yScale -= 0.02f;
                        D_menu_801AE9C0[i].xPos += 0.1f;
                    }
                    D_menu_801B914C++;
                }
                break;

            case 3:
                D_menu_801B9178 = RAND_INT(15.0f);
                D_menu_801B914C = 1;
                break;
        }

        switch (D_menu_801B9158) {
            case 0:
                if (D_menu_801B917C == 0) {
                    for (i = 0; i < ARRAY_COUNT(D_menu_801AE9C0); i++) {
                        D_menu_801AE9C0[i].xScale += 0.08f;
                        D_menu_801AE9C0[i].yScale += 0.08f;
                        D_menu_801AE9C0[i].xPos -= 0.4f;
                        D_menu_801AE9C0[i].yPos -= 0.4f;
                    }

                    D_menu_801B917C = 2;
                    D_menu_801B9158++;
                }
                break;

            case 1:
                if (D_menu_801B917C == 0) {

                    for (i = 0; i < ARRAY_COUNT(D_menu_801AE9C0); i++) {
                        D_menu_801AE9C0[i].xScale -= 0.08f;
                        D_menu_801AE9C0[i].yScale -= 0.08f;
                        D_menu_801AE9C0[i].xPos += 0.4f;
                        D_menu_801AE9C0[i].yPos += 0.4f;
                    }

                    D_menu_801B917C = 2;
                    D_menu_801B9158++;
                }
                break;

            case 2:
                if (D_menu_801B917C == 0) {
                    D_menu_801B917C = RAND_INT(30.0f);
                    D_menu_801B9158 = 0;
                }
                break;
        }

    } else {
        for (i = 0; i < ARRAY_COUNT(D_menu_801AE9C0); i++) {
            D_menu_801AE9C0[i].xScale = 1.0f;
            D_menu_801AE9C0[i].yScale = 1.0f;
            D_menu_801AE9C0[i].xPos = D_menu_801AE9A0[i];
            D_menu_801AE9C0[i].yPos = D_menu_801AE9B0[i];
        }
    }

    for (i = 0; i < 2; i++) {
        Option_DrawCardLabel(D_menu_801AE9C0[i]);
    }

    for (i = 2; i < ARRAY_COUNT(D_menu_801AE9C0); i++) {
        if (D_menu_801B914C != 3) {
            Option_DrawCardLabel(D_menu_801AE9C0[i]);
        }
    }
}

void Option_ExpertSound_Setup(void) {
    s32 i;

    gStarCount = 800;
    D_menu_801B931C = 0;

    D_menu_801B9290.unk_0 = 0;
    D_menu_801B9290.unk_4 = 0;

    sSpectrumAnalyzerMode = 0;
    sMusicPlaying = false;

    // clang-format off
    for (i = 0; i < ARRAY_COUNT(D_menu_801B9298); i++) { D_menu_801B9298[i] = 0.0f; }
    // clang-format on
}

#include "../../mods/sfxjukebox2.c"

// Expert Sound Options
void Option_ExpertSound_Update(void) {
    s32 pad;
    f32 sp28 = D_menu_801B931C;

    if (CVarGetInteger("gSfxJukebox", 0) == 1) {
        if (gControllerPress[gMainController].button & L_TRIG) {
            showJukebox ^= 1;
        }
        if (showJukebox) {
            Jukebox_Update();
            return;
        }
    }

    if (Option_Input_Sound_X(&sp28, 0.0f, 49.0f, &D_menu_801B9290) != 0) {
        AUDIO_PLAY_SFX(NA_SE_CURSOR, gDefaultSfxSource, 4);
        D_menu_801B931C = sp28;
    }

    if (gControllerPress[gMainController].button & A_BUTTON) {
        Audio_PlaySoundTestTrack(D_menu_801B931C);
        sMusicPlaying = true;
    }

    if (gControllerPress[gMainController].button & B_BUTTON) {
        if (!sMusicPlaying) {
            AUDIO_PLAY_SFX(NA_SE_ARWING_CANCEL, gDefaultSfxSource, 4);
            AUDIO_PLAY_BGM(NA_BGM_SELECT);
            gDrawMode = DRAW_NONE;
            sMenuEntryState = OPTION_MAIN_MENU;
            sMainMenuState = 0;
            sMainMenuFromCancel = true;
        } else {
            AUDIO_PLAY_SFX(NA_SE_CANCEL, gDefaultSfxSource, 4);
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 1);
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 1);
            sMusicPlaying = false;
        }
    }

    // Spectrum Analyzer mode selector
    if (gControllerPress[gMainController].button & R_CBUTTONS) {
        sSpectrumAnalyzerMode++;
        if (sSpectrumAnalyzerMode > 2) {
            sSpectrumAnalyzerMode = 0;
        }
    }
}

void Option_ExpertSound_Draw(void) {
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

#if MODS_SFX_JUKEBOX == 1
    if (!showJukebox) {
#endif

        RCP_SetupDL(&gMasterDisp, SETUPDL_83_OPTIONAL);

        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

        Lib_TextureRect_IA8(&gMasterDisp, D_OPT_80079F0, 128, 14, 49.0f, 81.0f, 1.0f, 1.0f);

        Lib_TextureRect_IA8(&gMasterDisp, D_menu_801AECF8[D_menu_801B931C / 10], 16, 15, 230.0f, 82.0f, 1.0f, 1.0f);

        Lib_TextureRect_IA8(&gMasterDisp, D_menu_801AECF8[D_menu_801B931C % 10], 16, 15, 244.0f, 82.0f, 1.0f, 1.0f);

#if MODS_SFX_JUKEBOX == 1
    }
#endif

    Option_AcceptCancel_Draw();

    RCP_SetupDL(&gMasterDisp, SETUPDL_76);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 50, 50, 200, 255);

    for (i = 0; i < 4; i++) {
        Lib_TextureRect_RGBA16(&gMasterDisp, aMapWhiteSquareTex, 8, 8, D_menu_801AF014[i], D_menu_801AF024[i],
                               D_menu_801AF034[i], D_menu_801AF044[i]);
    }

    if (sMusicPlaying) {
        temp_v0_4 = Audio_UpdateFrequencyAnalysis();
        var_fv1 = 60.0f;

        if (sSpectrumAnalyzerMode == 2) {
            var_fv1 = 30.0f;
        }

        for (i = 0; i < ARRAY_COUNT(D_menu_801B9298); i++) {
            if ((sSpectrumAnalyzerMode == 0) || (sSpectrumAnalyzerMode == 2)) {
                D_menu_801B9298[i] = (var_fv1 / 255.0f) * temp_v0_4[i];
            } else {
                D_menu_801B9298[i] = var_fv1 - ((var_fv1 / 255.0f) * temp_v0_4[i]);
            }
        }
    } else {
        for (i = 0; i < ARRAY_COUNT(D_menu_801B9298); i++) {
            Math_SmoothStepToF(&D_menu_801B9298[i], 0.0f, 0.2f, 100.0f, 0.1f);
        }
    }

    Lib_InitOrtho(&gMasterDisp);

    RCP_SetupDL(&gMasterDisp, SETUPDL_5);

    Matrix_Push(&gGfxMatrix);
    Matrix_LookAt(gGfxMatrix, 0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);

    for (var_fs0 = D_menu_801AF004, i = 0; i < ARRAY_COUNT(D_menu_801B9298); i++, var_fs0 += D_menu_801AF010) {
        r = D_menu_801AF054 + ((D_menu_801AF060 - D_menu_801AF054) / 31.0f) * i;
        g = D_menu_801AF058 + ((D_menu_801AF064 - D_menu_801AF058) / 31.0f) * i;
        b = D_menu_801AF05C + ((D_menu_801AF068 - D_menu_801AF05C) / 31.0f) * i;

        gDPSetPrimColor(gMasterDisp++, 0, 0, (s32) r, (s32) g, (s32) b, 255);

        Matrix_Push(&gGfxMatrix);
        Matrix_Translate(gGfxMatrix, var_fs0, D_menu_801AF078[sSpectrumAnalyzerMode], D_menu_801AF008, MTXF_APPLY);
        Matrix_Scale(gGfxMatrix, D_menu_801AF00C, D_menu_801B9298[i], 1.0f, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);

        gSPDisplayList(gMasterDisp++, D_menu_801AF06C[sSpectrumAnalyzerMode]);

        Matrix_Pop(&gGfxMatrix);
    }

    Matrix_Pop(&gGfxMatrix);
    Lib_InitPerspective(&gMasterDisp);
}

void Option_Data_Setup(void) {
    gStarCount = 800;
    D_menu_801B91E4 = 255.0f;
    D_menu_801B9330[0] = 0;
    D_menu_801B9330[1] = 0;
    D_menu_801B91C0 = 0;
    D_menu_801B91CC = 0;
}

void Option_Data_Update(void) {
    f32 temp_fv0;
    s32 i;

    switch (sMainMenuState) {
        case 0:
            Option_Data_Select();
            break;

        case 2:
            if (D_menu_801B9330[D_menu_801B91C0] != 0) {
                break; // looks fake, but isn't
            }
            D_menu_801B91CC = 0;
            D_menu_801B91C0 = 0;
            sMainMenuState = 0;
            break;

        case 3:
            if (D_menu_801B9330[D_menu_801B91C0] == 0) {
                gDrawMode = DRAW_NONE;
                sMenuEntryState = OPTION_MAIN_MENU;
                sMainMenuState = 0;
                sMainMenuFromCancel = true;
            }
            break;

        case 4:
            if (D_menu_801B9330[D_menu_801B91C0] == 0) {
                switch (D_menu_801B91CC) {
                    case 0:
                        D_menu_801B91CC = 1;
                        D_menu_801B91C0 = 0;
                        sMainMenuState = 0;
                        break;

                    case 1:
                        D_menu_801B91CC = 2;
                        AUDIO_PLAY_SFX(NA_SE_BACKUP_CLEAR, gDefaultSfxSource, 4);
                        D_ctx_801779A8[gMainController] = 50.0f;
                        D_ctx_80177990[gMainController] = 0;
                        break;

                    case 2:
                        D_ctx_80177990[gMainController] += (s32) D_ctx_801779A8[gMainController];
                        temp_fv0 = Math_SmoothStepToF(&D_ctx_801779A8[gMainController], 100.0f, 0.05f, 100.0f, 0.1f);

                        if (D_ctx_80177990[gMainController] >= 100) {
                            D_ctx_80177990[gMainController] -= 100;
                            gControllerRumbleFlags[gMainController] = 1;
                        }

                        if (temp_fv0 == 0.0f) {
                            D_menu_801B91CC = 3;
#ifdef AVOID_UB
                            gSaveFile.save = gDefaultSave;
                            gSaveFile.backup = gDefaultSave;
#else
                            gSaveFile = *(SaveFile*) &gDefaultSave;
#endif

                            Save_Write();

                            sExpertSoundCursor = 0;
                            sExpertModeCursor = 0;
                            sExpertModesEnabled = false;

                            gExpertMode = false;

                            sOptionCardList[OPTION_MAP].tex.texture = aMainGameCardTex;
                            sOptionCardList[OPTION_MAP].tex.width = 72;
                            sOptionCardList[OPTION_MAP].tex.height = 12;
                            sOptionCardList[OPTION_SOUND].tex.texture = aSoundCardTex;
                            sOptionCardList[OPTION_SOUND].tex.width = 64;
                            sOptionCardList[OPTION_SOUND].tex.height = 10;

                            for (i = 0; i < ARRAY_COUNT(sOptionCardList); i++) {
                                sOptionCardCurTextPosX[i] = sOptionCardTextPosX[i];
                                sOptionCardCurTextPosY[i] = sOptionCardTextPosY[i];
                            }
                            Title_GetRankTotalHits();
                        }
                        break;

                    case 3:
                        sMainMenuState = 0;
                        break;
                }
            }
            break;
    }
}

void Option_Data_Select(void) {
    if ((D_menu_801B91CC == 0) || (D_menu_801B91CC == 1)) {
        if (Option_Input_DataSelect_X(&D_menu_801B91C0) != 0) {
            AUDIO_PLAY_SFX(NA_SE_CURSOR, gDefaultSfxSource, 4);
        }
        if (1) {}
    }

    if (gControllerPress[gMainController].button & A_BUTTON) {
        if (D_menu_801B91CC == 3) {
            AUDIO_PLAY_SFX(NA_SE_ARWING_CANCEL, gDefaultSfxSource, 4);
            sMainMenuState = 3;
        } else {
            D_menu_801B9330[D_menu_801B91C0] = 10;
            if (D_menu_801B91C0 == 0) {
                if (D_menu_801B91CC == 1) {
                    AUDIO_PLAY_SFX(NA_SE_DECIDE, gDefaultSfxSource, 4);
                    sMainMenuState = 2;
                } else {
                    AUDIO_PLAY_SFX(NA_SE_ARWING_CANCEL, gDefaultSfxSource, 4);
                    sMainMenuState = 3;
                }
            } else {
                AUDIO_PLAY_SFX(NA_SE_DECIDE, gDefaultSfxSource, 4);
                sMainMenuState = 4;
            }
        }
    } else if (gControllerPress[gMainController].button & B_BUTTON) {
        if (D_menu_801B91CC == 1) {
            AUDIO_PLAY_SFX(NA_SE_CANCEL, gDefaultSfxSource, 4);
            sMainMenuState = 2;
        } else {
            AUDIO_PLAY_SFX(NA_SE_ARWING_CANCEL, gDefaultSfxSource, 4);
            sMainMenuState = 3;
        }
    }
}

void Option_Data_Draw(void) {
    s32 i;
    s32 sp7C[2];
    s32 mask[2];
    static f32 D_menu_801AF084[2] = { 172.0f, 76.0f };
    static f32 D_menu_801AF08C[2] = { 228.0f, 121.0f };

    static f32 D_menu_801AF094[6] = { 72.0f, 88.0f, 185.0f, 80.0f, 84.0f, 88.0f };
    static f32 D_menu_801AF0AC[6] = { 53.0f, 137.0f, 137.0f, 90.0f, 80.0f, 97.0f };

    Option_DrawMenuLabel();

    RCP_SetupDL(&gMasterDisp, SETUPDL_83_OPTIONAL);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    Lib_TextureRect_IA8(&gMasterDisp, D_OPT_80084B0, 176, 13, D_menu_801AF094[0], D_menu_801AF0AC[0] + (4.0f * i), 1.0f,
                        1.0f);

    if (D_menu_801B91CC < 2) {
        Lib_TextureRect_IA8_MirX(&gMasterDisp, aArrowTex, 8, 8, D_menu_801AF084[D_menu_801B91C0], 140.0f, 1.0f, 1.0f);
        Lib_TextureRect_IA8(&gMasterDisp, aArrowTex, 8, 8, D_menu_801AF08C[D_menu_801B91C0], 140.0f, 1.0f, 1.0f);

        Option_Color_FlashRed(&D_menu_801AED20[D_menu_801B91C0]);
        D_menu_801AED20[!D_menu_801B91C0] = 255.0f;

        mask[0] = mask[1] = 0xFFFFFFFF;

        for (i = 0; i < ARRAY_COUNT(D_menu_801B9330); i++) {
            if (D_menu_801B9330[i] != 0) {
                mask[i] = 1;
                sp7C[i] = 255;
                D_menu_801B9330[i]--;
            }
        }

        if ((gGameFrameCount & mask[1]) != 0) {
            sp7C[1] = D_menu_801AED20[1];
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, sp7C[1], sp7C[1], 255);
            Lib_TextureRect_IA8(&gMasterDisp, D_OPT_8009980, 32, 12, D_menu_801AF094[1], D_menu_801AF0AC[1], 1.0f,
                                1.0f);
        }

        if ((gGameFrameCount & mask[0]) != 0) {
            sp7C[0] = D_menu_801AED20[0];
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, sp7C[0], sp7C[0], 255);
            Lib_TextureRect_IA8(&gMasterDisp, D_OPT_8009B00, 40, 12, D_menu_801AF094[2], D_menu_801AF0AC[2], 1.0f,
                                1.0f);
        }
    }

    switch (D_menu_801B91CC) {
        case 0:
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
            {
                Lib_TextureRect_IA8(&gMasterDisp, D_OPT_8008DA0, 160, 19, D_menu_801AF094[3], D_menu_801AF0AC[3], 1.0f,
                                    1.0f);
            }
            break;

        case 1:
        case 2:
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
            {
                Lib_TextureRect_IA8(&gMasterDisp, D_OPT_8009CE0, 160, 41, D_menu_801AF094[4], D_menu_801AF0AC[4], 1.0f,
                                    1.0f);
            }
            break;

        case 3:
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 32, 32, 255);

            Lib_TextureRect_IA8(&gMasterDisp, D_OPT_800B680, 144, 41, D_menu_801AF094[5], D_menu_801AF0AC[5], 1.0f,
                                1.0f);
            break;
    }

    Option_AcceptCancel_Draw();
}

char* sTeamLetter[3] = { "P", "S", "F" };
s32 sTeamAlivePrimR[3] = { 255, 0, 30 };
s32 sTeamAlivePrimG[3] = { 30, 179, 30 };
s32 sTeamAlivePrimB[3] = { 0, 67, 255 };

void Option_Ranking_Setup(void) {
    Title_GetRankTotalHits();

    gStarCount = 800;

    D_menu_801B91D0 = 1;
    D_menu_801B93E4 = 0;

    D_menu_801B91D4 = 114.0f;
    D_menu_801B91DC = 114.0f;

    D_menu_801B91D8 = -6.0f;
    D_menu_801B91E0 = -6.0f;

    sRanking2ndPage = false;
    sTitleRankMaxRecords = 10;

    D_menu_801B9400.unk_0 = 0;
    D_menu_801B9400.unk_4 = 0;
    D_menu_801B9408.unk_0 = 0;
    D_menu_801B9408.unk_4 = 0;

    Option_PlanetTextures_Setup();
}

void Option_Ranking_Update(void) {
    Option_Ranking_Select();

    if (gControllerPress[gMainController].button & B_BUTTON) {
        AUDIO_PLAY_SFX(NA_SE_ARWING_CANCEL, gDefaultSfxSource, 4);
        gDrawMode = DRAW_NONE;
        sMenuEntryState = OPTION_MAIN_MENU;
        sMainMenuState = 0;
        sMainMenuFromCancel = true;
    }
}

void Option_Ranking_Draw(void) {
    Option_RankingMenu_Draw();
    Option_DrawMenuLabel();
}

void Option_Ranking_Select(void) {
    // Press A to go to the 2nd page
    if (gControllerPress[gMainController].button & A_BUTTON) {
        AUDIO_PLAY_SFX(NA_SE_DECIDE, gDefaultSfxSource, 4);
        sRanking2ndPage ^= 1;
    }

    if (sRanking2ndPage) {
        Option_Ranking2_Cursor();
        return;
    }

    Option_Ranking_Cursor();
}

void Option_Ranking_Cursor(void) {
    if (Option_Input_MoveCursor_Y(&D_menu_801B93E4, 9, 1, 0, 20, 5, 4, gMainController, &D_menu_801B9400)) {
        AUDIO_PLAY_SFX(NA_SE_CURSOR, gDefaultSfxSource, 4);
        D_menu_801B91D4 = 114.0f - D_menu_801B93E4 * 130.0f;
        D_menu_801B91DC = 114.0f - D_menu_801B93E4 * 130.0f;
        D_menu_801B91D8 = -6.0f + D_menu_801B93E4 * 130.0f;
        D_menu_801B91E0 = -6.0f + D_menu_801B93E4 * 130.0f;
    }
}

void Option_Ranking2_Cursor(void) {
    s32 pad;
    f32 sp30;
    f32 temp_fv0_2;
    s32 temp;
    s32 temp2;

    if (D_menu_801B91D0 != 0) {
        if (Option_Input_MoveCursor_Y(&D_menu_801B93E4, 9, 1, 1, 20, 2, 9, gMainController, &D_menu_801B9408) !=
            0.00f) {
            AUDIO_PLAY_SFX(NA_SE_CURSOR, gDefaultSfxSource, 4);
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

void Option_RankingMenu_Draw(void) {
    s32 colorGB;

    if (sRanking2ndPage) {
        Option_RankingMenu2_Draw();
    } else {
        Title_RankingData_Draw();
        RCP_SetupDL(&gMasterDisp, SETUPDL_83_OPTIONAL);
        Option_Color_FlashRed(&D_menu_801B93F0);
        colorGB = D_menu_801B93F0;
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, colorGB, colorGB, 255);
        // Selection arrow
        Lib_TextureRect_IA8(&gMasterDisp, D_VS_MENU_7004010, 8, 8, 70.0f, (D_menu_801B93E4 * 17.0f) + 55.0f, 1.0f,
                            1.0f);
    }
    RCP_SetupDL(&gMasterDisp, SETUPDL_83_OPTIONAL);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);
    Graphics_DisplaySmallText(242, 215, 1.0f, 1.0f, "PUSH A");
}

// 2nd page and more detailed version of the Ranking
void Option_RankingMenu2_Draw(void) {
    f32 var_fs0;
    f32 var_fs1;
    s32 colorGB;
    s32 i;
    static f32 D_menu_801AF0F4 = 130.0f;
    static f32 D_menu_801AF0F8[] = { 48.0f, 175.0f };

    var_fs0 = D_menu_801B91D4;
    var_fs1 = D_menu_801B91D8;

    for (i = 0; i < RANKING_MAX; i++) {
        if ((var_fs0 > 69.0f) && (var_fs0 < 230.0f)) {
            Option_OrdinalNumbers_Draw(i, 41, var_fs0);
            Option_RankingName_Draw(i, 75, var_fs0 - 25.0f);
            Option_RankingTotalHits_Draw(i, 130, (var_fs0 - 26.0f));
            Map_RemainingLives_Draw(210, (var_fs0 - 24.0f), gSaveFile.save.data.rankingLives[i]);
            Option_RankingTeamAlive_Draw(i, 258, var_fs0 - 25.0f);
        }
        Option_RankingRoute_Draw(i, var_fs0, var_fs1);
        var_fs0 += D_menu_801AF0F4;
        var_fs1 -= D_menu_801AF0F4;
    }

    Option_Menu_Push();
    Option_80197914();

    Matrix_Pop(&gGfxMatrix);

    RCP_SetupDL(&gMasterDisp, SETUPDL_76);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    Lib_TextureRect_IA8(&gMasterDisp, D_OPT_800D170, 8, 16, 0.0f, D_menu_801AF0F8[0], 40.0f, 1.5f);
    Lib_TextureRect_IA8_MirY(&gMasterDisp, D_OPT_800D170, 8, 16, 0.0f, D_menu_801AF0F8[1], 40.0f, 1.5f);

    Background_DrawPartialStarfield(0, 70);
    Background_DrawPartialStarfield(170, 239);

    RCP_SetupDL(&gMasterDisp, SETUPDL_83);

    if (D_menu_801B91D4 >= 114.0f) {
        gDPSetPrimColor(gMasterDisp++, 0, 0, 32, 32, 32, 255);
    } else {
        Option_Color_FlashRed(&D_menu_801B93F4);
        colorGB = D_menu_801B93F4;
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, colorGB, colorGB, 255);
    }

    Lib_TextureRect_IA8(&gMasterDisp, D_OPT_800D070, 16, 16, 150.0f, 44.0f, 1.0f, 1.0f);

    if (D_menu_801B91D4 <= -1055.0f) {
        gDPSetPrimColor(gMasterDisp++, 0, 0, 32, 32, 32, 255);
    } else {
        Option_Color_FlashRed(&D_menu_801B93F8);
        colorGB = D_menu_801B93F8;
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, colorGB, colorGB, 255);
    }

    Lib_TextureRect_IA8_MirY(&gMasterDisp, D_OPT_800D070, 16, 16, 150.0f, 200.0f, 1.0f, 1.0f);
}

Vec3f D_menu_801AF100[2] = { { 0.0f, 167.0f, 0.0f }, { 0.0f, -167.0f, 0.0f } };
Vec3f D_menu_801AF118[2] = { { 25.0f, 3.6f, 0.0f }, { 25.0f, 3.6f, 0.0f } };

void Option_80197914(void) {
    Vec3f* vec1;
    Vec3f* vec2;
    s32 i;

    RCP_SetupDL(&gMasterDisp, SETUPDL_0);

    for (i = 0, vec1 = D_menu_801AF100, vec2 = D_menu_801AF118; i < 2; i++, vec1++, vec2++) {
        Matrix_Push(&gGfxMatrix);
        // @port: Tag the transform.
        FrameInterpolation_RecordOpenChild("RANKING_BORDERS", i);

                Matrix_Translate(gGfxMatrix, vec1->x, vec1->y, -500.0f, MTXF_APPLY);

        // @port: Increase the scale by 2.5f to compensate for missing borders
        Matrix_Scale(gGfxMatrix, vec2->x * 4, vec2->y + 2.5f, 1.0f, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, D_menu_801AEF30);
        Matrix_Pop(&gGfxMatrix);

        // @port Pop the transform id.
        FrameInterpolation_RecordCloseChild();
    }
}

void Option_OrdinalNumbers_Draw(s32 ordinalType, s32 xPos, s32 yPos) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_83_OPTIONAL);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    if (ordinalType != 9) {
        Lib_TextureRect_IA8(&gMasterDisp, D_menu_801AECF8[ordinalType + 1], 16, 15, xPos, yPos - 25.0f, 1.0f, 1.0f);
    } else {
        Lib_TextureRect_IA8(&gMasterDisp, aLargeText_1, 16, 15, xPos - 14.0f, yPos - 25.0f, 1.0f, 1.0f);
        Lib_TextureRect_IA8(&gMasterDisp, aLargeText_0, 16, 15, xPos, yPos - 25.0f, 1.0f, 1.0f);
    }

    RCP_SetupDL(&gMasterDisp, SETUPDL_85_OPTIONAL);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    switch (ordinalType) {
        case 0: // st
            Lib_TextureRect_CI4(&gMasterDisp, aStTex, aStTLUT, 16, 9, xPos + 17.0f, yPos - 19.0f, 1.0f, 1.0f);
            break;

        case 1: // nd
            Lib_TextureRect_CI4(&gMasterDisp, aNdTex, aNdTLUT, 16, 10, xPos + 17.0f, yPos - 19.0f, 1.0f, 1.0f);
            break;

        case 2: // rd
            Lib_TextureRect_CI4(&gMasterDisp, aRdTex, aRdTLUT, 16, 11, xPos + 17.0f, yPos - 20.0f, 1.0f, 1.0f);
            break;

        default: // th
            Lib_TextureRect_CI4(&gMasterDisp, aThTex, aThTLUT, 16, 9, xPos + 17.0f, yPos - 19.0f, 1.0f, 1.0f);
            break;
    }
}

void Option_RankingName_Draw(s32 rankIdx, s32 xPos, s32 yPos) {
    char rankName[4];

    RCP_SetupDL(&gMasterDisp, SETUPDL_83_OPTIONAL);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);

    rankName[0] = gSaveFile.save.data.rankNameEntry[rankIdx][0] & 0xFF;
    rankName[1] = gSaveFile.save.data.rankNameEntry[rankIdx][1] & 0xFF;
    rankName[2] = gSaveFile.save.data.rankNameEntry[rankIdx][2] & 0xFF;
    rankName[3] = '\0';

    Graphics_DisplayLargeText(xPos, yPos, 1.0f, 1.0f, rankName);
}

void Option_RankingTotalHits_Draw(s32 rankIdx, s32 xPos, s32 yPos) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_83_OPTIONAL);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 60, 60, 255, 170);
    Lib_TextureRect_IA8(&gMasterDisp, aMapOptionBgTex, 24, 17, xPos, yPos, 3.17f, 1.05f);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);
    Graphics_DisplaySmallText(xPos, yPos, 1.0f, 1.0f, "TOTAL HITS");

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
    Graphics_DisplaySmallNumber((xPos + 40.0f) - ((HUD_CountDigits(gTotalHitsRanking[rankIdx]) * 8) - 8), (yPos + 9.0f),
                                gTotalHitsRanking[rankIdx]);
}

void Option_RankingTeamAlive_Draw(s32 rankIdx, s32 xPos, s32 yPos) {
    f32 xOffset;
    s32 i;

    RCP_SetupDL(&gMasterDisp, SETUPDL_83_OPTIONAL);

    for (xOffset = 0.0f, i = 0; i < ARRAY_COUNT(sTeamAlivePrimR); i++, xOffset += 12.0f) {
        gDPSetPrimColor(gMasterDisp++, 0, 0, sTeamAlivePrimR[i], sTeamAlivePrimG[i], sTeamAlivePrimB[i], 255);
        Graphics_DisplaySmallText(xOffset + xPos, yPos, 1.0f, 1.0f, sTeamLetter[i]);

        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
        Graphics_DisplaySmallNumber(xPos + xOffset - ((HUD_CountDigits(gRankingTeamAlive[rankIdx][i]) - 1) * 8),
                                    yPos + 9.0f, gRankingTeamAlive[rankIdx][i]);
    }
}

void Option_RankingRoute_Draw(s32 rankIdx, f32 arg1, f32 arg2) {
    f32 temp = 16.0f;
    s32 routeMax = gSaveFile.save.data.rankingRoute[rankIdx];
    f32 var_fs2;
    s32 i;

    for (var_fs2 = 0.0f, i = 0; i < ROUTE_MAX; i++, var_fs2 += 24.0f + temp) {
        Option_RankingRouteFrame_Draw(rankIdx, i, 28.0f + var_fs2, arg1, routeMax);
        if (i < routeMax) {
            Option_RankingPlanetName_Draw(rankIdx, i, 28.0f + var_fs2, arg1);
            Option_RankingHitCount_Draw(rankIdx, i, 28.0f + var_fs2, arg1);
            Option_RankingTeamPresence_Draw(rankIdx, i, 28.0f + var_fs2, arg1);
        }
    }

    if ((arg2 < 75.0f) && (arg2 > -80.0f)) {
        Option_RankingPlanetRoute_Draw(rankIdx, arg2, routeMax);
    }
}

void Option_RankingRouteFrame_Draw(s32 rankIdx, s32 routeIdx, f32 xPos, f32 yPos, s32 arg4) {
    s32 r;
    s32 g;
    s32 b;
    s32 routeLineColor;
    PlanetId start;
    PlanetId end;

    if ((yPos > 30.0f) && (yPos < 200.0f)) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_76_OPTIONAL);

        if (routeIdx < 6) {
            r = g = b = 255;

            if (routeIdx < (arg4 - 1)) {
                start = gSaveFile.save.data.stats[rankIdx][routeIdx].planetId & 0xF;
                end = gSaveFile.save.data.stats[rankIdx][routeIdx + 1].planetId & 0xF;

                routeLineColor = Option_GetRouteLineColor(start, end);

                r = g = b = 255; // white by default

                switch (routeLineColor) {
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
            Lib_TextureRect_RGBA16(&gMasterDisp, aMapWhiteSquareTex, 8, 8, xPos + 24.0f, yPos + 11.0f, 2.0f, 0.2f);
        }
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
        Lib_TextureRect_RGBA16(&gMasterDisp, aMapPathBoxTex, 24, 24, xPos, yPos, 1.0f, 1.0f);
    }
}

void Option_RankingHitCount_Draw(s32 rankIdx, s32 routeIdx, f32 xPos, f32 yPos) {
    s32 hitCount;

    if ((yPos > 22.0f) && (yPos < 162.0f)) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_83);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);
        hitCount = (gSaveFile.save.data.stats[rankIdx][routeIdx].hitCountOver256 & 1) << 8;
        hitCount |= gSaveFile.save.data.stats[rankIdx][routeIdx].hitCount;
        Graphics_DisplaySmallNumber(xPos + 15.0f - (HUD_CountDigits(hitCount) - 1) * 8, yPos + 24.0f + 1.0f, hitCount);
    }
}

void Option_RankingTeamPresence_Draw(s32 rankIdx, s32 routeIdx, f32 xPos, f32 yPos) {
    f32 xOffset;
    s32 teamAlive[3];
    s32 i;

    if ((yPos > 12.0f) && (yPos < 154.0f)) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_83_OPTIONAL);

        teamAlive[0] = gSaveFile.save.data.stats[rankIdx][routeIdx].peppyAlive & 1;
        teamAlive[1] = gSaveFile.save.data.stats[rankIdx][routeIdx].slippyAlive & 1;
        teamAlive[2] = gSaveFile.save.data.stats[rankIdx][routeIdx].falcoAlive & 1;

        for (xOffset = 0.0f, i = 0; i < ARRAY_COUNT(teamAlive); i++, xOffset += 9.0f) {
            if (teamAlive[i] == 0) {
                continue;
            }
            gDPSetPrimColor(gMasterDisp++, 0, 0, sTeamAlivePrimR[i], sTeamAlivePrimG[i], sTeamAlivePrimB[i], 255);
            Graphics_DisplaySmallText(xPos + xOffset - 1.0f, yPos + 24.0f + 8.0f + 1.0f, 1.0f, 1.0f, sTeamLetter[i]);
        }
    }
}

void Option_RankingPlanetName_Draw(s32 rankIdx, s32 routeIdx, f32 xPos, f32 yPos) {
    PlanetId planetIdx;
    char* planetName;
    f32 textWidth;

    if ((yPos > 58.0f) && (yPos < 197.0f)) {
        planetIdx = gSaveFile.save.data.stats[rankIdx][routeIdx].planetId & 0xF;
        planetName = D_menu_801AEEAC[planetIdx];

        RCP_SetupDL(&gMasterDisp, SETUPDL_83_OPTIONAL);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);
        textWidth = Graphics_GetSmallTextWidth(planetName) / 2.0f;
        Graphics_DisplaySmallText(xPos + 12.0f - textWidth, yPos - 8.0f, 1.0f, 1.0f, planetName);
    }
}

void Option_RankingPlanetRoute_Draw(s32 rankIdx, f32 y, s32 routeMax) {
    static f32 zAngle = 0.0f;
    static f32 xStart = -121.0f;
    static f32 xAdvance = 40.1f;
    s32 i;
    PlanetId planet;
    u16 gotMedal;
    bool drawPlanetMedal;
    f32 x;
    s32 pad[2];

    Matrix_Push(&gGfxMatrix);
    Matrix_LookAt(gGfxMatrix, 0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);

    Lib_InitOrtho(&gMasterDisp);

    gotMedal = gSaveFile.save.data.rankingMedal[rankIdx];

    for (x = xStart, i = 0; i < routeMax; i++, x += xAdvance) {
        planet = gSaveFile.save.data.stats[rankIdx][i].planetId & 0xF;

        switch (planet) {
            case SAVE_SLOT_SOLAR:
                RCP_SetupDL(&gMasterDisp, SETUPDL_67);

                gDPSetPrimColor(gMasterDisp++, 0, 0, 240, 0, 0, 255);
                gDPSetEnvColor(gMasterDisp++, 31, 0, 0, 0);

                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, x, y, 0.0f, MTXF_APPLY);
                Matrix_RotateZ(gGfxMatrix, M_DTOR * zAngle, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, 0.3f, 0.3f, 0.3f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_menu_801AEE6C[planet]);

                gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 128);
                gDPSetEnvColor(gMasterDisp++, 31, 0, 0, 0);
                Matrix_Scale(gGfxMatrix, 0.8f, 0.8f, 0.8f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_menu_801AEE6C[planet]);

                Matrix_Pop(&gGfxMatrix);
                break;

            case PLANET_METEO:
                RCP_SetupDL(&gMasterDisp, SETUPDL_62);

                gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, x - 1.0f, y + 4.0f, 0.0f, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, 0.3f, 0.3f, 0.3f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_menu_801AEE6C[planet]);

                Matrix_Translate(gGfxMatrix, 18.0f, -20.0f, 0.0f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_menu_801AEE6C[planet]);

                Matrix_Pop(&gGfxMatrix);
                break;

            case PLANET_SECTOR_X:
            case PLANET_SECTOR_Y:
            case PLANET_SECTOR_Z:
                RCP_SetupDL(&gMasterDisp, SETUPDL_62);

                gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 144);

                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, x, y, 0.0f, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, 0.3f, 0.3f, 0.3f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_menu_801AEE6C[planet]);

                Matrix_Pop(&gGfxMatrix);
                break;

            case PLANET_BOLSE:
                RCP_SetupDL(&gMasterDisp, SETUPDL_23);
                Lights_SetOneLight(&gMasterDisp, 0, 0, 100, 100, 100, 70, 100, 100, 100);

                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, x, y, 0.0f, MTXF_APPLY);
                Matrix_RotateX(gGfxMatrix, M_DTOR * 20.0f, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, 0.01f, 0.01f, 0.01f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_menu_801AEE6C[planet]);

                Matrix_Pop(&gGfxMatrix);
                break;

            case PLANET_AREA_6:
                RCP_SetupDL(&gMasterDisp, SETUPDL_23);
                Lights_SetOneLight(&gMasterDisp, 0, 0, 100, 100, 100, 70, 100, 100, 100);

                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, x, y, 0.0f, MTXF_APPLY);
                Matrix_RotateX(gGfxMatrix, M_DTOR * 20.0f, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, 0.01f, 0.01f, 0.01f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);

                gSPDisplayList(gMasterDisp++, D_menu_801AEE6C[planet]);

                Matrix_Pop(&gGfxMatrix);
                break;

            default:
                RCP_SetupDL(&gMasterDisp, SETUPDL_62);

                gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, x, y, 0.0f, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, 0.3f, 0.3f, 0.3f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_menu_801AEE6C[planet]);

                if ((planet != SAVE_SLOT_VENOM_1) && (planet != SAVE_SLOT_VENOM_2) && (planet != PLANET_AQUAS)) {
                    if (planet == PLANET_MACBETH) {
                        gDPSetPrimColor(gMasterDisp++, 0, 0, 64, 64, 64, 255);
                    } else {
                        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
                    }
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, gMapVenomCloudDL);
                }
                Matrix_Scale(gGfxMatrix, 1.6f, 1.6f, 1.6f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);

                gSPDisplayList(gMasterDisp++, D_MAP_605C230);

                Matrix_Pop(&gGfxMatrix);
                break;
        }

        drawPlanetMedal = (gotMedal >> i) & 1;
        if (drawPlanetMedal) {
            Option_RankingRouteMedal_Draw(x, y, 0.0f);
        }
    }

    Matrix_Pop(&gGfxMatrix);

    Option_ScrollPlanetTexture();

    zAngle += 0.1f;

    Lib_InitPerspective(&gMasterDisp);
}

f32 D_menu_801AF13C = 0.7f;
f32 D_menu_801AF140 = 11.0f;
f32 D_menu_801AF144 = 2.7f;

void Option_RankingRouteMedal_Draw(f32 xPos, f32 yPos, f32 zPos) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_53);
    Matrix_Push(&gGfxMatrix);
    // @port: Tag the transform.
    FrameInterpolation_RecordOpenChild("Option_RankingRouteMedal_Draw", (u32) xPos << 8 | (u32) yPos);

    Matrix_Translate(gGfxMatrix, xPos - D_menu_801AF140, yPos + D_menu_801AF144, zPos, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, D_menu_801AF13C, D_menu_801AF13C, D_menu_801AF13C, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, aMapMedalDL);
    Matrix_Pop(&gGfxMatrix);

    // @port Pop the transform id.
    FrameInterpolation_RecordCloseChild();
}

s32 Option_GetRouteLineColor(PlanetId start, PlanetId end) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sRouteColoredLine); i++) {
        if ((sRouteColoredLine[i].start == start) && (sRouteColoredLine[i].end == end)) {
            break;
        }
    }

    return sRouteColoredLine[i].color;
}

void Option_VersusMenu_Setup(void) {
    s32 i;

    if (D_menu_801B91C4) {
        AUDIO_PLAY_BGM(NA_BGM_VS_SELECT);
    }

    sVsMenuSelection = sMenuEntryState;

    if (D_game_800D2870) {
        sOptionCardList[OPTION_TRAINING].tex.yPos = 129.0f;
        sOptionCardList[OPTION_TRAINING].frame.y = -7.5f;
    }

    gVsPointsToWin = 3;

    D_menu_801B9340 = 2;

    gVsMenuSelection = 0;
    gStarCount = 0;

    D_menu_801B93C4 = 0;

    for (i = 0; i < ARRAY_COUNT(gControllerPlugged); i++) {
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

void Option_VersusMenu_Update(void) {
    switch (sMainMenuState) {
        case 0:
            Option_VersusMenu_Cursor();
            break;

        case 1:
            if (sOkConfirmTimer == 0.0f) {
                sMenuEntryState = OPTION_VERSUS_STAGE;
                Option_Entry_Setup();
            }
            break;
    }
}

void Option_VersusMenu_Cursor(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gControllerPress); i++) {
        if (!(D_menu_801B93C4 & (1 << i))) {
            Option_Color_FlashRed(&D_menu_801B9358[i]);
            if (Option_Input_MoveCursor_Y(&D_menu_801AED3C[i], 2, 0, 0, 20, 2, 4, i, &D_menu_801B93A0[i])) {
                AUDIO_PLAY_SFX(NA_SE_CURSOR, gDefaultSfxSource, 4);
            }
        }

        if (gControllerPress[i].button & A_BUTTON) {
            if (D_menu_801B93C4 == 15) {
                AUDIO_PLAY_SFX(NA_SE_DECIDE, gDefaultSfxSource, 4);
                sOkConfirmTimer = 10;
                sMainMenuState++;
                break;
            } else {
                if (!(D_menu_801B93C4 & (1 << i))) {
                    AUDIO_PLAY_SFX(NA_SE_DECIDE, gDefaultSfxSource, 4);
                    gHandicap[i] = D_menu_801AED3C[i];
                    D_menu_801B9358[i] = 255.0f;
                    D_menu_801B9348[i] = 10;
                    D_menu_801B93C4 = D_menu_801B93C4 | (1 << i);
                }
            }
        }

        if (gControllerPress[i].button & B_BUTTON) {
            if (D_menu_801B93C4 & (1 << i)) {
                AUDIO_PLAY_SFX(NA_SE_CANCEL, gDefaultSfxSource, 4);
                D_menu_801B93C4 &= (1 << i) ^ 15;
            } else {
                AUDIO_PLAY_BGM(NA_BGM_SELECT);
                AUDIO_PLAY_SFX(NA_SE_ARWING_CANCEL, gDefaultSfxSource, 4);
                Option_VsBackToSubMenu(2);
                sVsSubMenuFromCancel = true;
                break;
            }
        }
    }
}

void Option_VersusMenu_Draw(void) {
    s32 i;

    Option_VsMenuCard_Draw();
    Option_VS_N64Console_Draw();

    for (i = 0; i < ARRAY_COUNT(gControllerPlugged); i++) {
        if (gControllerPlugged[i] == 1) {
            Option_VS_HandicapSet_Draw(i);
        }
    }

    if (D_menu_801B93C4 == 15) {
        Option_VsOKConfirm_Draw();
    }
}

f32 sVsHandicapFrameXpos[4] = { 30.0f, 214.0f, 30.0f, 215.0f };
f32 sVsHandicapFrameYpos[4] = { 18.0f, 18.0f, 151.0f, 151.0f };
s32 sCharNameWidth[4] = { 56, 48, 56, 48 };
s32 sCharNameHeight[4] = { 8, 10, 10, 8 };
f32 sCharNameXoffsetPos[4] = { 12.0f, 16.0f, 12.0f, 18.0f };
f32 sCharNameYoffsetPos = -1.0f;
f32 D_menu_801AF19C[4] = { 46.0f, 41.0f, 41.0f, 41.0f };
f32 D_menu_801AF1AC = 24.0f;
f32 D_menu_801AF1B0 = 1.4f;
f32 sPlayerFaceXoffsetPos = 5.0f;
f32 sPlayerFaceYoffsetPos = 11.0f;
f32 D_menu_801AF1BC = 8.0f;
f32 D_menu_801AF1C0 = 45.0f;
f32 D_menu_801AF1C4 = 20.0f;
f32 D_menu_801AF1C8 = 55.0f;
f32 D_menu_801AF1CC = 37.0f;
f32 D_menu_801AF1D0 = 11.0f;
f32 D_menu_801AF1D4 = 7.0f;
f32 D_menu_801AF1D8 = 59.0f;
f32 D_menu_801AF1DC = 58.0f;

void Option_VS_HandicapSet_Draw(s32 PlayerIdx) {
    s32 mask;
    s32 width;
    s32 colorGB;
    s32 i;
    static u8* sVsHandicapLvlTex[3] = {
        aVsHandicapLvl1Tex,
        aVsHandicapLvl2Tex,
        aVsHandicapLvl3Tex,
    };
    static u8* sVsCharNameTex[4] = {
        aVsFoxNameTex,
        aVsPeppyNameTex,
        aVsSlippyNameTex,
        aVsFalcoNameTex,
    };
    static u16* sVsCharNameTLUT[4] = {
        aVsFoxNameTLUT,
        aVsPeppyNameTLUT,
        aVsSlippyNameTLUT,
        aVsFalcoNameTLUT,
    };
    static u16* sVsPlayerFaceTex[4] = {
        aVsFoxFaceTex,
        aVsPeppyFaceTex,
        aVsSlippyFaceTex,
        aVsFalcoFaceTex,
    };
    static u8* sVsPlayerNumTex[4] = {
        aVsPlayerNum1Tex,
        aVsPlayerNum2Tex,
        aVsPlayerNum3Tex,
        aVsPlayerNum4Tex,
    };
    static s32 sCharNameR[4] = { 177, 255, 0, 30 };
    static s32 sCharNameG[4] = { 242, 30, 255, 30 };
    static s32 sCharNameB[4] = { 12, 0, 67, 255 };

    RCP_SetupDL(&gMasterDisp, SETUPDL_85_OPTIONAL);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    Lib_TextureRect_CI4(&gMasterDisp, aVsHandicapFrameTex, aVsHandicapFrameTLUT, 80, 71,
                        sVsHandicapFrameXpos[PlayerIdx], sVsHandicapFrameYpos[PlayerIdx], 1.0f, 1.0f);

    Lib_TextureRect_CI8(&gMasterDisp, sVsCharNameTex[PlayerIdx], sVsCharNameTLUT[PlayerIdx], sCharNameWidth[PlayerIdx],
                        sCharNameHeight[PlayerIdx], sVsHandicapFrameXpos[PlayerIdx] + sCharNameXoffsetPos[PlayerIdx],
                        sVsHandicapFrameYpos[PlayerIdx] + sCharNameYoffsetPos, 1.0f, 1.0f);

    RCP_SetupDL(&gMasterDisp, SETUPDL_83);

    mask = 0xFFFFFFFF;
    if (D_menu_801B9348[PlayerIdx] != 0) {
        mask = 0x00000001;
        D_menu_801B9348[PlayerIdx]--;
    }

    if ((gGameFrameCount & mask) != 0) {
        colorGB = D_menu_801B9358[PlayerIdx];

        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, colorGB, colorGB, 255);

        Lib_TextureRect_IA8(&gMasterDisp, D_VS_MENU_7001030, 64, 9, sVsHandicapFrameXpos[PlayerIdx] + D_menu_801AF1BC,
                            sVsHandicapFrameYpos[PlayerIdx] + D_menu_801AF1C0, 1.0f, 1.0f);

        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, colorGB, colorGB, 255);

        Lib_TextureRect_IA8(&gMasterDisp, sVsHandicapLvlTex[D_menu_801AED3C[PlayerIdx]], 40, 12,
                            sVsHandicapFrameXpos[PlayerIdx] + D_menu_801AF1C4,
                            sVsHandicapFrameYpos[PlayerIdx] + D_menu_801AF1C8, 1.0f, 1.0f);
    }

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    Lib_TextureRect_IA8_MirX(&gMasterDisp, aArrowTex, 8, 8, sVsHandicapFrameXpos[PlayerIdx] + D_menu_801AF1D4,
                             sVsHandicapFrameYpos[PlayerIdx] + D_menu_801AF1DC, 1.0f, 1.0f);

    Lib_TextureRect_IA8(&gMasterDisp, aArrowTex, 8, 8, sVsHandicapFrameXpos[PlayerIdx] + D_menu_801AF1D8,
                        sVsHandicapFrameYpos[PlayerIdx] + D_menu_801AF1DC, 1.0f, 1.0f);

    Lib_TextureRect_IA8(&gMasterDisp, aVsTextContTex, 40, 7, sVsHandicapFrameXpos[PlayerIdx] + D_menu_801AF1CC,
                        sVsHandicapFrameYpos[PlayerIdx] + D_menu_801AF1D0, 1.0f, 1.0f);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    Lib_TextureRect_RGBA16(&gMasterDisp, sVsPlayerFaceTex[PlayerIdx], 44, 44,
                           sVsHandicapFrameXpos[PlayerIdx] + sPlayerFaceXoffsetPos,
                           sVsHandicapFrameYpos[PlayerIdx] + sPlayerFaceYoffsetPos, 0.7f, 0.7f);

    width = 24;
    if (PlayerIdx == 0) {
        width = 16;
    }

    gDPSetPrimColor(gMasterDisp++, 0, 0, sCharNameR[PlayerIdx], sCharNameG[PlayerIdx], sCharNameB[PlayerIdx], 255);

    Lib_TextureRect_IA8(&gMasterDisp, sVsPlayerNumTex[PlayerIdx], width, 13,
                        sVsHandicapFrameXpos[PlayerIdx] + D_menu_801AF19C[PlayerIdx],
                        sVsHandicapFrameYpos[PlayerIdx] + D_menu_801AF1AC, D_menu_801AF1B0, D_menu_801AF1B0);
}

void Option_VS_N64Console_Draw(void) {
    s32 i;

    RCP_SetupDL_76();
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
    Lib_TextureRect_RGBA16(&gMasterDisp, aVsN64ConsoleTex, 144, 42, 87.0f, 84, 1.0f, 1.0f);
}

void Option_VersusStage_Setup(void) {
    s32 i;

    gStarCount = 0;
    D_menu_801B933C = 0;
    D_menu_801B91E8 = 255.0f;
    D_menu_801B93D4 = gVsPointsToWin - 1;
    D_menu_801B93D8 = gVsMenuSelection;
    D_menu_801B93DC = D_menu_801B9340;
    gVsTimeTrialLimit = D_menu_801B93DC;
    // clang-format off
    for (i = 0; i < ARRAY_COUNT(D_menu_801B9358); i++) { \
        D_menu_801B9358[i] = 0;
    }
    // clang-format on
    sPointConfirmTimer = 0;
    sStageSelectConfirmTimer = 0;
    sTimeTrialConfirmTimer = 0;
    sOkConfirmTimer = 0;
    sVsSubMenuFirstState = false;
    D_menu_801B9368 = 255.0f;
    D_menu_801B9370 = 255.0f;
    D_menu_801B9378 = 255.0f;
    Option_8019A080();
}

void Option_8019A080(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_menu_801B9380); i++) {
        D_menu_801B9380[i].unk_0 = 0;
        D_menu_801B9380[i].unk_4 = 0;
    }
}

void Option_VersusStage_Update(void) {
    switch (sVsMenuSelection) {
        case OPTION_POINT_MATCH:
            Option_Vs_PointMatch_Update();
            break;

        case OPTION_BR_MATCH:
            Option_Vs_BattleRoyal_Update();
            break;

        case OPTION_TT_MATCH:
            Option_Vs_TimeTrial_Update();
            break;
    }
}

void Option_Vs_PointMatch_Update(void) {
    switch (sMainMenuState) {
        case 0:
            Option_Vs_Point_Selection();
            break;

        case 1:
            Option_VsStageSelection();
            break;

        case 2:
            Option_VsConfirmSelection();
            break;

        case 3:
            Option_Vs_StartMatch();
            break;
    }
}

void Option_Vs_BattleRoyal_Update(void) {
    switch (sMainMenuState) {
        case 0:
            Option_VsStageSelection();
            break;

        case 1:
            Option_VsConfirmSelection();
            break;

        case 2:
            Option_Vs_StartMatch();
            break;
    }
}

void Option_Vs_TimeTrial_Update(void) {
    switch (sMainMenuState) {
        case 0:
            Option_VsTimeSelection();
            break;
        case 1:
            Option_VsStageSelection();
            break;
        case 2:
            Option_VsConfirmSelection();
            break;
        case 3:
            Option_Vs_StartMatch();
            break;
    }
}

void Option_Vs_StartMatch(void) {
    if (sOkConfirmTimer == 0.0f) {
        gGameState = GSTATE_VS_INIT;
        gNextGameStateTimer = 2;
        gOptionMenuStatus = OPTION_WAIT;
        gDrawMode = DRAW_NONE;
    }
}

void Option_Vs_Point_Selection(void) {
    s32 i;

    if (sPointConfirmTimer != 0) {
        return;
    }

    if (sVsSubMenuFirstState) {
        sMainMenuState++;
        sVsSubMenuFirstState = false;
        return;
    }

    for (i = 0; i < ARRAY_COUNT(gControllerPlugged); i++) {
        if (gControllerPlugged[i] == 0) {
            continue;
        }

        if (Option_Input_MoveCursor_Y(&D_menu_801B93D4, 4, 0, 0, 20, 2, 4, i, &D_menu_801B9380[i])) {
            AUDIO_PLAY_SFX(NA_SE_CURSOR, gDefaultSfxSource, 4);
            gVsPointsToWin = D_menu_801B93D4 + 1;
        }

        if (gControllerPress[i].button & A_BUTTON) {
            AUDIO_PLAY_SFX(NA_SE_DECIDE, gDefaultSfxSource, 4);
            Option_8019A080();
            sPointConfirmTimer = 10;
            break;
        }

        if (gControllerPress[i].button & B_BUTTON) {
            AUDIO_PLAY_SFX(NA_SE_CANCEL, gDefaultSfxSource, 4);
            sMenuEntryState = sVsMenuSelection;
            D_menu_801B91C4 = 0;
            Option_Entry_Setup();
            break;
        }
    }
}

void Option_VsTimeSelection(void) {
    s32 i;

    if (sTimeTrialConfirmTimer != 0) {
        return;
    }

    if (sVsSubMenuFirstState) {
        sMainMenuState++;
        sVsSubMenuFirstState = false;
        return;
    }

    for (i = 0; i < ARRAY_COUNT(gControllerPlugged); i++) {
        if (!gControllerPlugged[i]) {
            continue;
        }

        if (Option_Input_MoveCursor_Y(&D_menu_801B93DC, 4, 0, 0, 20, 2, 4, i, &D_menu_801B9380[i])) {
            AUDIO_PLAY_SFX(NA_SE_CURSOR, gDefaultSfxSource, 4);
            D_menu_801B9340 = D_menu_801B93DC;
            gVsTimeTrialLimit = D_menu_801B93DC;
        }

        if (gControllerPress[i].button & A_BUTTON) {
            AUDIO_PLAY_SFX(NA_SE_DECIDE, gDefaultSfxSource, 4);
            Option_8019A080();
            sTimeTrialConfirmTimer = 10;
            break;
        }

        if (gControllerPress[i].button & B_BUTTON) {
            AUDIO_PLAY_SFX(NA_SE_CANCEL, gDefaultSfxSource, 4);
            sMenuEntryState = sVsMenuSelection;
            D_menu_801B91C4 = 0;
            Option_Entry_Setup();
            break;
        }
    }
}

void Option_VsStageSelection(void) {
    s32 i;

    if (sStageSelectConfirmTimer != 0) {
        return;
    }

    if (sVsSubMenuFirstState) {
        D_menu_801B933C = 1;
        sVsSubMenuFirstState = false;
        sMainMenuState++;
        return;
    }

    for (i = 0; i < ARRAY_COUNT(gControllerPlugged); i++) {
        if (gControllerPlugged[i] == 0) {
            continue;
        }
        if (Option_Input_MoveCursor_Y(&D_menu_801B93D8, 1, 0, 1, 20, 2, 4, i, &D_menu_801B9380[i])) {
            AUDIO_PLAY_SFX(NA_SE_CURSOR, gDefaultSfxSource, 4);
            gVsMenuSelection = D_menu_801B93D8;
        }

        if (gControllerPress[i].button & A_BUTTON) {
            AUDIO_PLAY_SFX(NA_SE_DECIDE, gDefaultSfxSource, 4);
            if (gVsMenuSelection == 0) {
                gVersusStage = VS_STAGE_CORNERIA;
                if (sVsMenuSelection == OPTION_TT_MATCH) {
                    gVersusStage = VS_STAGE_KATINA;
                }
            } else {
                gVersusStage = VS_STAGE_SECTOR_Z;
            }

            sStageSelectConfirmTimer = 10;
            Option_8019A080();
            break;
        }

        if (gControllerPress[i].button & B_BUTTON) {
            AUDIO_PLAY_SFX(NA_SE_CANCEL, gDefaultSfxSource, 4);
            if (sVsMenuSelection == OPTION_BR_MATCH) {
                sMenuEntryState = sVsMenuSelection;
                D_menu_801B91C4 = 0;
                Option_Entry_Setup();
            } else {
                Option_8019A080();
                sVsSubMenuFirstState = false;
                sMainMenuState--;
            }
            break;
        }
    }
}

void Option_VsConfirmSelection(void) {
    s32 i;

    if (sOkConfirmTimer != 0) {
        return;
    }

    if (sVsSubMenuFirstState) {
        sVsSubMenuFirstState = false;
        sMainMenuState++;
        return;
    }

    for (i = 0; i < ARRAY_COUNT(gControllerPlugged); i++) {
        if (gControllerPlugged[i] == 0) {
            continue;
        }

        if (gControllerPress[i].button & A_BUTTON) {
            AUDIO_PLAY_SFX(NA_SE_DECIDE, gDefaultSfxSource, 4);
            sOkConfirmTimer = 10;
            break;
        }

        if (gControllerPress[i].button & B_BUTTON) {
            AUDIO_PLAY_SFX(NA_SE_CANCEL, gDefaultSfxSource, 4);
            Option_8019A080();
            D_menu_801B933C = 0;
            sVsSubMenuFirstState = false;
            sMainMenuState--;
            break;
        }
    }
}

void Option_VersusStage_Draw(void) {
    switch (sVsMenuSelection) {
        case OPTION_BR_MATCH:
            break;

        case OPTION_POINT_MATCH:
            Option_VsPointMatch_Draw();
            break;

        case OPTION_TT_MATCH:
            Option_VsTimeTrial_Draw();
            break;
    }

    Option_VsStageSelect_Draw();

    if (D_menu_801B933C != 0) {
        Option_VsOKConfirm_Draw();
    }
}

void Option_VsPointMatch_Draw(void) {
    s32 pad[5];
    s32 colorGB;
    s32 sp44 = gVsPointsToWin;
    s32 mask;

    RCP_SetupDL(&gMasterDisp, SETUPDL_83);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 60, 60, 255, 190);

    Lib_TextureRect_IA8(&gMasterDisp, aMapOptionBgTex, 24, 17, 94.0f, 43.0f, 5.0f, 1.1f);

    if (sMainMenuState == 0) {
        Option_VsSelectionArrows_Draw(97.0f, 50.0f, 107.0f, 255, 255, 255);
        Option_Color_FlashRed(&D_menu_801B9368);
    } else {
        D_menu_801B9368 = 255.0f;
    }

    colorGB = D_menu_801B9368;

    mask = 0xFFFFFFFF;

    if (sPointConfirmTimer != 0) {
        colorGB = 255;
        mask = 0x00000001;
        sPointConfirmTimer--;
        if (sPointConfirmTimer == 0) {
            sVsSubMenuFirstState = true;
        }
    }

    if ((gGameFrameCount & mask) != 0) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_83);

        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, colorGB, colorGB, 255);

        Lib_TextureRect_IA8(&gMasterDisp, D_menu_801AECF8[sp44], 16, 15, 109.0f, 45.0f, 1.0f, 1.0f);

        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, colorGB, colorGB, 255);

        Lib_TextureRect_IA8(&gMasterDisp, D_VS_MENU_7001DF0, 80, 10, 122.0f, 49.0f, 1.0f, 1.0f);
    }
}

void Option_VsTimeTrial_Draw(void) {
    static f32 D_menu_801AF25C[6] = { 156.0f, 112.0f, 112.0f, 112.0f, 112.0f, 112.0f };
    static f32 D_menu_801AF274[6] = { 46.0f, 43.0f, 43.0f, 43.0f, 43.0f, 43.0f };
    static f32 D_menu_801B9324;
    static f32 D_menu_801B9328;
    static f32 D_menu_801B9338;
    s32 pad[2];
    s32 colorGB;
    s32 mask;

    static u8* sTimeTrialMinuteTextures[] = { D_VS_MENU_70024D0, D_VS_MENU_7002730, D_VS_MENU_7002990,
                                              D_VS_MENU_7002BF0, D_VS_MENU_7002E50 };

    RCP_SetupDL(&gMasterDisp, SETUPDL_83);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 60, 60, 255, 190);

    Lib_TextureRect_IA8(&gMasterDisp, aMapOptionBgTex, 24, 17, 93.0f, 42.0f, 5.1f, 1.1f);

    if (sMainMenuState == 0) {
        D_menu_801B9324 = 97.0f;
        D_menu_801B9328 = 49.0f;
        D_menu_801B9338 = 107.0f;
        Option_VsSelectionArrows_Draw(D_menu_801B9324, D_menu_801B9328, D_menu_801B9338, 255, 255, 255);
        Option_Color_FlashRed(&D_menu_801B9378);
    } else {
        D_menu_801B9378 = 255.0f;
    }

    colorGB = D_menu_801B9378;

    mask = 0xFFFFFFFF;

    if (sTimeTrialConfirmTimer != 0) {
        colorGB = 255;
        mask = 0x00000001;
        sTimeTrialConfirmTimer--;
        if (sTimeTrialConfirmTimer == 0) {
            sVsSubMenuFirstState = true;
        }
    }

    if ((gGameFrameCount & mask) != 0) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_83);

        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, colorGB, colorGB, 255);

        Lib_TextureRect_IA8(&gMasterDisp, sTimeTrialMinuteTextures[D_menu_801B9340], 40, 15,
                            D_menu_801AF25C[D_menu_801B9340 + 1], D_menu_801AF274[D_menu_801B9340 + 1], 1.0f, 1.0f);

        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, colorGB, colorGB, 255);

        Lib_TextureRect_IA8(&gMasterDisp, D_VS_MENU_7002110, 80, 12, D_menu_801AF25C[0], D_menu_801AF274[0], 1.0f,
                            1.0f);
    }
}

void Option_VsStageSelect_Draw(void) {
    static f32 D_menu_801B93C0;
    static f32 D_menu_801B93C8;
    static f32 D_menu_801B93CC;
    static f32 D_menu_801AF2A0 = 101.0f;
    static f32 D_menu_801AF2A4 = 86.0f;
    s32 mask;
    s32 colorGB;

    if (((sMainMenuState == 0) && (sVsMenuSelection == OPTION_BR_MATCH)) ||
        ((sMainMenuState == 1) && (sVsMenuSelection != OPTION_BR_MATCH))) {
        D_menu_801B93C0 = 94.0f;
        D_menu_801B93C8 = 88.0f;
        D_menu_801B93CC = 114.0f;

        RCP_SetupDL(&gMasterDisp, SETUPDL_83);

        Option_VsSelectionArrows_Draw(D_menu_801B93C0, D_menu_801B93C8, D_menu_801B93CC, 255, 255, 255);
        Option_Color_FlashRed(&D_menu_801B9370);
    } else {
        D_menu_801B9370 = 255.0f;
    }

    colorGB = D_menu_801B9370;

    mask = 0xFFFFFFFF;
    if (sStageSelectConfirmTimer != 0) {
        mask = 0x00000001;
        colorGB = 255;
        sStageSelectConfirmTimer--;
        if (sStageSelectConfirmTimer == 0) {
            sVsSubMenuFirstState = true;
        }
    }

    if ((gGameFrameCount & mask) != 0) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_83);

        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, colorGB, colorGB, 255);

        Lib_TextureRect_IA8(&gMasterDisp, D_VS_MENU_7001270, 112, 12, D_menu_801AF2A0, D_menu_801AF2A4, 1.0f, 1.0f);
    }

    if (sVsMenuSelection == OPTION_TT_MATCH) {
        Option_VsTimeTrialStageSelect_Draw();
    } else {
        Option_VsStageSelect2_Draw();
    }
}

void Option_VsTimeTrialStageSelect_Draw(void) {
    static f32 D_menu_801AF2A8 = 69.0f;
    static f32 D_menu_801AF2AC = 110.0f;
    static f32 D_menu_801AF2B0 = 123.0f;
    static f32 D_menu_801AF2B4[] = { 72.0f, 189.0f };
    f32 xPos;
    s32 i;
    s32 width;
    s32 alpha[2];
    static u8* sVsTextLevelTex[] = { aVsTextKatinaTex, aVsTextSectorZTex };
    static u8* sVsLevelTex[] = { aVsKatinaTex, aVsSectorZTex };
    static u16* sVsLevelTLUT[] = { aVsKatinaTLUT, aVsSectorZTLUT };

    for (xPos = D_menu_801AF2A8, i = 0; i < ARRAY_COUNT(sVsTextLevelTex); i++, xPos += D_menu_801AF2B0) {
        if (i == gVsMenuSelection) {
            alpha[i] = 255;
        } else {
            alpha[i] = 32;
        }

        RCP_SetupDL(&gMasterDisp, SETUPDL_85_OPTIONAL);

        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, alpha[i]);

        Lib_TextureRect_CI8(&gMasterDisp, sVsLevelTex[i], sVsLevelTLUT[i], 48, 38, xPos, D_menu_801AF2AC, 1.0f, 1.0f);

        width = 48;
        if (i == 1) {
            width = 56;
        }

        RCP_SetupDL(&gMasterDisp, SETUPDL_83);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, alpha[i]);
        Lib_TextureRect_IA8(&gMasterDisp, sVsTextLevelTex[i], width, 10, D_menu_801AF2B4[i], D_menu_801AF2AC + 40.0f,
                            1.0f, 1.0f);
    }
}

void Option_VsStageSelect2_Draw(void) {
    static f32 D_menu_801AF2D4 = 69.0f;
    static f32 D_menu_801AF2D8 = 110.0f;
    static f32 D_menu_801AF2DC = 123.0f;
    static f32 D_menu_801AF2E0[] = { 66.0f, 189.0f };
    f32 xPos;
    s32 i;
    s32 alpha[3];
    static u8* sVsTextLevelTex[] = {
        aVsTextCorneriaTex,
        aVsTextSectorZTex,
    };
    static u8* sVsLevelTex[] = {
        aVsCorneriaTex,
        aVsSectorZTex,
    };
    static u16* sVsLevelTLUT[] = {
        aVsCorneriaTLUT,
        aVsSectorZTLUT,
    };

    for (xPos = D_menu_801AF2D4, i = 0; i < ARRAY_COUNT(sVsTextLevelTex); i++, xPos += D_menu_801AF2DC) {
        if (i == gVsMenuSelection) {
            alpha[i] = 255;
        } else {
            alpha[i] = 32;
        }

        RCP_SetupDL(&gMasterDisp, SETUPDL_85_OPTIONAL);

        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, alpha[i]);

        Lib_TextureRect_CI8(&gMasterDisp, sVsLevelTex[i], sVsLevelTLUT[i], 48, 38, xPos, D_menu_801AF2D8, 1.0f, 1.0f);

        RCP_SetupDL(&gMasterDisp, SETUPDL_83);

        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, alpha[i]);

        Lib_TextureRect_IA8(&gMasterDisp, sVsTextLevelTex[i], 56, 10, D_menu_801AF2E0[i], D_menu_801AF2D8 + 40.0f, 1.0f,
                            1.0f);
    }
}

void Option_VsOKConfirm_Draw(void) {
    s32 pad[2];
    s32 colorGB;
    s32 bitmask;

    Option_Color_FlashRed(&D_menu_801B91E8);

    colorGB = D_menu_801B91E8;
    bitmask = 0xFFFFFFFF;

    if (sOkConfirmTimer != 0) {
        colorGB = 255;
        bitmask = 0x00000001;
        sOkConfirmTimer--;
        if (sOkConfirmTimer == 0) {
            sVsSubMenuFirstState = true;
        }
    }

    if (gGameFrameCount & bitmask) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_83);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, colorGB, colorGB, 255);
        Lib_TextureRect_IA8(&gMasterDisp, D_VS_MENU_7003650, 40, 12, 143.0f, 210.0f, 1.0f, 1.0f);
    }
}

void Option_VsSelectionArrows_Draw(f32 xPos, f32 yPos, f32 offset, s32 r, s32 g, s32 b) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_83);
    gDPSetPrimColor(gMasterDisp++, 0, 0, r, g, b, 255);
    Lib_TextureRect_IA8_MirX(&gMasterDisp, D_VS_MENU_7004010, 8, 8, xPos, yPos, 1.0f, 1.0f);
    Lib_TextureRect_IA8(&gMasterDisp, D_VS_MENU_7004010, 8, 8, xPos + offset, yPos, 1.0f, 1.0f);
}

void Option_AcceptCancel_Draw(void) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_83_OPTIONAL);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
    Lib_TextureRect_IA8(&gMasterDisp, aAtoConfirmTex, 96, 10, 62.0f, 213.0f, 1.0f, 1.0f);
    Lib_TextureRect_IA8(&gMasterDisp, aBtoCancelTex, 96, 10, 166.0f, 213.0f, 1.0f, 1.0f);
}

void Option_VsBackToSubMenu(OptionId menuEntryState) {
    sMenuEntryState = menuEntryState;
    gDrawMode = DRAW_NONE;
    sMainMenuState = 0;
    D_menu_801B91B4 = 0;
}

// Menu card drawned below the N64 console
void Option_VsMenuCard_Draw(void) {
    Option_Menu_Push();
    Option_DrawMenuCard(sOptionVSCardList[sVsMenuCursor].frame);
    Matrix_Pop(&gGfxMatrix);
    Option_DrawCardLabel(sOptionVSCardList[sVsMenuCursor].tex);
}

void Option_DrawMenuLabel(void) {
    Option_Menu_Push();
    Option_DrawMenuCard(sOptionCardList[sMainMenuCursor].frame);
    Matrix_Pop(&gGfxMatrix);
    Option_DrawCardLabel(sOptionCardList[sMainMenuCursor].tex);
}

void Option_DrawMenuCard(OptionCardFrame arg0) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_17);

    Lib_InitOrtho(&gMasterDisp);

    Matrix_Push(&gGfxMatrix);

    Matrix_Translate(gGfxMatrix, arg0.x, arg0.y, arg0.z, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, arg0.xScale, arg0.yScale, 1.0f, MTXF_APPLY);
    Matrix_RotateX(gGfxMatrix, M_DTOR * 90.0f, MTXF_APPLY);

    Matrix_SetGfxMtx(&gMasterDisp);

    gSPDisplayList(gMasterDisp++, D_OPT_8015550);

    Matrix_Pop(&gGfxMatrix);

    Lib_InitPerspective(&gMasterDisp);
}

void Option_DrawMenuArwing(ArwingCursorPos arwing) {
    if (sDrawCursor) {
        Option_DrawArwing(arwing.x, arwing.y, D_menu_801B91F4, sLeftArwingCursorYrot, 90.0f, D_menu_801B91F8, 0);
        Option_DrawArwing(arwing.x + arwing.range, arwing.y, D_menu_801B91F4, sRightArwingCursorYrot, -90.0f,
                          D_menu_801B91F8, 1);
    }
}

void Option_DrawArwing(f32 x, f32 y, f32 z, f32 yRot, f32 zRot, f32 scale, s32 index) {
    f32 dirX;
    f32 dirY;
    f32 dirZ;
    static int arwingCursorPrevPos = 0;
    bool interpolationEnabled;

    if (arwingCursorPrevPos != sMainMenuCursor) {
        // @port Skip interpolation
        FrameInterpolation_ShouldInterpolateFrame(false);
        interpolationEnabled = false;
    } else {
        // @port renable interpolation
        FrameInterpolation_ShouldInterpolateFrame(true);
        interpolationEnabled = true;
        // @port: Tag the transform.
        FrameInterpolation_RecordOpenChild("Option_DrawArwing", index);
    }

    Option_SetMenuLightPos(sArwingLightXrot, sArwingLightYrot, 100.0f, &dirX, &dirY, &dirZ);

    Lights_SetOneLight(&gMasterDisp, dirX, dirY, dirZ, sArwingLightColR, sArwingLightColG, sArwingLightColB,
                       sArwingLightAmbR, sArwingLightAmbG, sArwingLightAmbB);

    Matrix_Push(&gGfxMatrix);

    Matrix_Translate(gGfxMatrix, x, y, z, MTXF_APPLY);

    Matrix_Scale(gGfxMatrix, scale, scale, scale, MTXF_APPLY);
    Matrix_RotateZ(gGfxMatrix, M_DTOR * zRot, MTXF_APPLY);
    Matrix_RotateY(gGfxMatrix, M_DTOR * yRot, MTXF_APPLY);

    Matrix_SetGfxMtx(&gMasterDisp);

    RCP_SetupDL_55();

    gSPDisplayList(gMasterDisp++, aMapArwingDL);

    Matrix_Pop(&gGfxMatrix);

    if (interpolationEnabled) {
        // @port Pop the transform id.
        FrameInterpolation_RecordCloseChild();
    } else {
        // @port renable interpolation
        FrameInterpolation_ShouldInterpolateFrame(true);
    }

    arwingCursorPrevPos = sMainMenuCursor;
}

void Option_Menu_Push(void) {
    Matrix_Push(&gGfxMatrix);
    Matrix_LookAt(gGfxMatrix, gCsCamEyeX, gCsCamEyeY, gCsCamEyeZ, gCsCamAtX, gCsCamAtY, gCsCamAtZ, 0.0f, 1.0f, 0.0f,
                  MTXF_APPLY);
}

void Option_SetMenuLightPos(f32 xRot, f32 yRot, f32 zSrc, f32* dirX, f32* dirY, f32* dirZ) {
    Vec3f dest;
    Vec3f src;

    src.x = 0.0f;
    src.y = 0.0f;
    src.z = zSrc;

    Matrix_RotateY(gCalcMatrix, M_DTOR * yRot, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, M_DTOR * xRot, MTXF_APPLY);
    Matrix_MultVec3f(gCalcMatrix, &src, &dest);

    *dirX = dest.x;
    *dirY = dest.y;
    *dirZ = dest.z;
}

void Option_CardLightning_Update(void) {
    s32 i;
    f32 savedLightningXpos;

    if (D_menu_801B9214 != 0) {
        savedLightningXpos = sLightningXpos;
        Option_Menu_Push();

        for (i = 0; i < 3; i++) {
            sLightningXScale = RAND_FLOAT(0.5f);
            sLightningYScale = 0.5f;
            Option_CardLightning_Draw();
            sLightningXpos += 6.0f;
        }

        Matrix_Pop(&gGfxMatrix);
        sLightningXpos = savedLightningXpos;

        if (sLightningXpos < 23.0f) {
            sLightningXpos += 18.0f;
        } else {
            sLightningXpos = 23.0f;
            D_menu_801B9214 = 0;
        }
    }
}

void Option_CardLightning_Draw(void) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_36);

    Lib_InitOrtho(&gMasterDisp);

    Matrix_Push(&gGfxMatrix);

    Matrix_Translate(gGfxMatrix, sLightningXpos, sLightningYpos, 0.0f, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, sLightningXScale, sLightningYScale, 1.0f, MTXF_APPLY);

    Matrix_SetGfxMtx(&gMasterDisp);

    gSPDisplayList(gMasterDisp++, aLightningDL);

    Matrix_Pop(&gGfxMatrix);

    Lib_InitPerspective(&gMasterDisp);
}

//! TODO: Enum for Texture types

void Option_DrawCardLabel(OptionCardTexture tex) {
    if (!(tex.xScale <= 0.0f) && !(tex.yScale <= 0.0f)) {
        switch (tex.type) {
            case 1:
                RCP_SetupDL(&gMasterDisp, SETUPDL_78_OPTIONAL);
                gDPSetPrimColor(gMasterDisp++, 0, 0, tex.red, tex.green, tex.blue, tex.alpha);
                Lib_TextureRect_CI4(&gMasterDisp, tex.texture, tex.palette, tex.width, tex.height, tex.xPos, tex.yPos,
                                    tex.xScale, tex.yScale);
                break;

            case 2:
                RCP_SetupDL(&gMasterDisp, SETUPDL_78_OPTIONAL);
                gDPSetPrimColor(gMasterDisp++, 0, 0, tex.red, tex.green, tex.blue, tex.alpha);
                Lib_TextureRect_CI8(&gMasterDisp, tex.texture, tex.palette, tex.width, tex.height, tex.xPos, tex.yPos,
                                    tex.xScale, tex.yScale);
                break;

            case 0:
                RCP_SetupDL(&gMasterDisp, SETUPDL_76_OPTIONAL);
                gDPSetPrimColor(gMasterDisp++, 0, 0, tex.red, tex.green, tex.blue, tex.alpha);
                Lib_TextureRect_IA8(&gMasterDisp, tex.texture, tex.width, tex.height, tex.xPos, tex.yPos, tex.xScale,
                                    tex.yScale);
                break;

            case 3:
                RCP_SetupDL(&gMasterDisp, SETUPDL_76_OPTIONAL);
                gDPSetPrimColor(gMasterDisp++, 0, 0, tex.red, tex.green, tex.blue, tex.alpha);
                Lib_TextureRect_RGBA16(&gMasterDisp, tex.texture, tex.width, tex.height, tex.xPos, tex.yPos, tex.xScale,
                                       tex.yScale);
                break;
        }
    }
}

// Input for vertical movement of the cursor
bool Option_Input_MoveCursor_Y(s32* arg0, s32 arg1, bool arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                               StickInput* stick) {
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

    if (!(stick->unk_4)) {
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

            stick->unk_4 = arg5 + stick->unk_0;
            if (stick->unk_0 > 0) {
                stick->unk_0 -= arg6;
            }
        } else {
            stick->unk_4 = 0;
            stick->unk_0 = arg6;
        }
    }

    if (((gControllerPress[0].button & D_JPAD) || (gControllerPress[0].button & U_JPAD)) && (arg2 == true)) {
        if (gControllerPress[0].button & D_JPAD) {
            (*arg0)++;
            if (*arg0 > arg1) {
                if (arg3 == 0) {
                    *arg0 = 0;
                } else {
                    *arg0 = arg1;
                }
            }
        }

        if (gControllerPress[0].button & U_JPAD) {
            (*arg0)--;
            if (*arg0 < 0) {
                if (arg3 == 0) {
                    *arg0 = arg1;
                } else {
                    *arg0 = 0;
                }
            }
        }

        stick->unk_4 = arg5 + stick->unk_0;
        if (stick->unk_0 > 0) {
            stick->unk_0 -= arg6;
        }
    } else if (((gControllerPress[0].button & L_JPAD) || (gControllerPress[0].button & R_JPAD)) && (arg2 == false)) {
        if (gControllerPress[0].button & R_JPAD) {
            (*arg0)++;
            if (*arg0 > arg1) {
                if (arg3 == 0) {
                    *arg0 = 0;
                } else {
                    *arg0 = arg1;
                }
            }
        }

        if (gControllerPress[0].button & L_JPAD) {
            (*arg0)--;
            if (*arg0 < 0) {
                if (arg3 == 0) {
                    *arg0 = arg1;
                } else {
                    *arg0 = 0;
                }
            }
        }

        stick->unk_4 = arg5 + stick->unk_0;
        if (stick->unk_0 > 0) {
            stick->unk_0 -= arg6;
        }
    }

    if (stick->unk_4 > 0) {
        stick->unk_4--;
    }

    if (temp != *arg0) {
        ret = true;
    }

    return ret;
}

// Input for horizontal selection in DataSelect
s32 Option_Input_DataSelect_X(s32* arg0) {
    s32 ret = 0;
    s32 temp = *arg0;
    s32 x = +gControllerPress[gMainController].stick_x;
    s32 y = -gControllerPress[gMainController].stick_y;

    if ((y > 40) || (y < -40)) {
        return ret;
    }

    if ((x < 30) && (x > -30)) {
        x = 0;
    }

    if (D_menu_801B91A0 == 0) {
        // @port: D_PAD control
        if (gControllerPress[0].button & R_JPAD) {
            *arg0 = 0;
            ret = 1;
            D_menu_801B91A0 = 6;
        } else if (gControllerPress[0].button & L_JPAD) {
            *arg0 = 1;
            ret = -1;
            D_menu_801B91A0 = 6;
        }

        if (x != 0) {
            if (x > 0) {
                *arg0 = 0;
                ret = 1;
            }
            if (x < 0) {
                *arg0 = 1;
                ret = -1;
            }
            D_menu_801B91A0 = 6;
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

// Input for horizontal selection in Sound menus
bool Option_Input_Sound_X(f32* arg0, f32 arg1, f32 arg2, StickInput* arg3) {
    f32 var_fv1;
    f32 temp2;
    bool var_a2 = false;
    f32 temp = *arg0;
    s32 stickX = +gControllerPress[gMainController].stick_x;
    s32 stickY = -gControllerPress[gMainController].stick_y;
    static int holdTimer = 0;

    if (gControllerHold[gMainController].button & (L_JPAD | R_JPAD)) {
        holdTimer++;
    } else {
        holdTimer = 0;
    }

    if ((stickY > 10) || (stickY < -10)) {
        return 0;
    }

    if ((stickX < 10) && (stickX > -10)) {
        stickX = 0;
    } else if (stickX < 0) {
        stickX += 10;
    } else {
        stickX -= 10;
    }

    if (arg3->unk_4 == 0) {
        if (stickX != 0) {
            var_fv1 = stickX / 20.0f;
            arg3->unk_4 = arg3->unk_0;

            if (arg3->unk_0 != 0) {
                arg3->unk_0 -= 7;
            }

            if (arg3->unk_4 != 0) {
                if (stickX > 0) {
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

    if (gControllerPress[gMainController].button & R_JPAD) {
        stickX += 10;
    } else if (gControllerPress[gMainController].button & L_JPAD) {
        stickX -= 10;
    }

    if (holdTimer > 15) {
        if (gControllerHold[gMainController].button & L_JPAD) {
            var_fv1 = -1.0f;
        } else if (gControllerHold[gMainController].button & R_JPAD) {
            var_fv1 = 1.0f;
        }
        *arg0 += var_fv1;

        if (arg2 < *arg0) {
            *arg0 = arg2;
        }
        if (*arg0 < arg1) {
            *arg0 = arg1;
        }
    }

    if (gControllerPress[gMainController].button & L_JPAD) {
        var_fv1 = -1.0f;
        *arg0 += var_fv1;
        if (arg2 < *arg0) {
            *arg0 = arg2;
        }
        if (*arg0 < arg1) {
            *arg0 = arg1;
        }
    } else if (gControllerPress[gMainController].button & R_JPAD) {
        var_fv1 = 1.0f;
        *arg0 += var_fv1;
        if (arg2 < *arg0) {
            *arg0 = arg2;
        }
        if (*arg0 < arg1) {
            *arg0 = arg1;
        }
    }

    if (arg3->unk_4 > 0) {
        arg3->unk_4--;
    }

    temp2 = *arg0;

    if ((s32) temp2 != (s32) temp) {
        AUDIO_PLAY_SFX(NA_SE_COUNT_UP, gDefaultSfxSource, 4);
        var_a2 = true;
    }

    return var_a2;
}

void Option_Color_FlashRed(f32* color) {
    if ((s32) Math_SmoothStepToF(color, D_menu_801B91E4, 0.5f, 100.0f, 1.0f) == 0.0f) {
        if (*color == 32.0f) {
            D_menu_801B91E4 = 255.0f;
        } else {
            D_menu_801B91E4 = 32.0f;
        }
    }
}

s32 Option_RankInPos_Check(void) {
    s32 i;
    s32 j;
    s32 k;
    s32 m;
    s32 rankInPos;
    s32 missionTeamStatus = 0;
    s32 rankingTeamAlive = 0;
    s32 rankingLives[10];

    for (i = 0; i < gMissionNumber + 1; i++) {
        missionTeamStatus += ((gMissionTeamStatus[i] & TEAMSTATUS_PEPPY) >> 16) & 1;
        missionTeamStatus += ((gMissionTeamStatus[i] & TEAMSTATUS_SLIPPY) >> 8) & 1;
        missionTeamStatus += (gMissionTeamStatus[i] & TEAMSTATUS_FALCO) & 1;
    }

    for (i = 0; i < RANKING_MAX; i++) {
        rankingLives[i] = gSaveFile.save.data.rankingLives[i];
    }

    rankInPos = -1; // Didn't get into the ranking

    // Ranking
    for (i = 0; i < RANKING_MAX; i++) {
        if (gTotalHitsRanking[i] <= gTotalHits) {
            if (gTotalHitsRanking[i] == gTotalHits) {
                for (j = i; j < RANKING_MAX; j++) {
                    if (gTotalHitsRanking[j] != gTotalHits) {
                        rankInPos = j;
                        break;
                    }

                    // Lives count
                    if (rankingLives[j] <= gLifeCount[gPlayerNum]) {
                        if (rankingLives[j] == gLifeCount[gPlayerNum]) {
                            for (k = j; k < RANKING_MAX; k++) {
                                if ((rankingLives[k] != gLifeCount[gPlayerNum]) ||
                                    (gTotalHitsRanking[k] != gTotalHits)) {
                                    rankInPos = k;
                                    break;
                                }

                                // Team count
                                for (rankingTeamAlive = 0, m = 0; m < 3; m++) {
                                    rankingTeamAlive += gRankingTeamAlive[k][m];
                                }

                                if (missionTeamStatus > rankingTeamAlive) {
                                    rankInPos = k;
                                    break;
                                }
                            }
                        } else {
                            rankInPos = j;
                        }
                        break;
                    }
                }
            } else {
                rankInPos = i;
            }
            break;
        }
    }

    return rankInPos;
}

void Option_NameEntry_Update(void) {
    switch (sMainMenuState) {
        case 0:
            Option_NameEntry_Setup();
            sMainMenuState++;
            break;

        case 1:
            Option_NameEntry_Select();
            break;

        case 2:
            Option_Ranking_SaveData();
            Title_GetRankTotalHits();
            D_menu_801B917C = 15;
            sMainMenuState++;
            break;

        case 3:
            if (D_menu_801B917C == 0) {
                gBlurAlpha = 255;
                gDrawMode = DRAW_NONE;
                sMainMenuState = 0;
                sMenuEntryState = OPTION_SCORE;
            }
            break;
    }
}

void Option_NameEntry_Setup(void) {
    s32 temp;
    s32 i;

    AUDIO_PLAY_BGM(NA_BGM_SELECT);

    gBlurAlpha = 208;
    gStarCount = 800;

    D_menu_801B9130 = 1;
    D_menu_801B9128 = 0;
    sNameEntryLightXrot = 0.0f;
    sNameEntryLightYrot = 70.0f;

    temp = gSaveFile.save.data.unk_EA & 0xFF;

    if (temp < 10) {
        D_menu_801B9098 = 3;
        D_menu_801B9138 = 1;

        D_menu_801B9150[0][0] = gSaveFile.save.data.rankNameEntry[temp][0] & 0xFF;
        D_menu_801B9150[1][0] = gSaveFile.save.data.rankNameEntry[temp][1] & 0xFF;
        D_menu_801B9150[2][0] = gSaveFile.save.data.rankNameEntry[temp][2] & 0xFF;

        for (i = 0; i < 3; i++) {
            D_menu_801B90A0[i] = Option_GetCharIndex(D_menu_801B9150[i][0]);
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
    Option_PlanetTextures_Setup();
}

void Option_NameEntry_Select(void) {
    switch (D_menu_801B9128) {
        case 0:
            if ((D_menu_801B9138 == 0) &&
                (Option_Input_MoveCursor_Y(&D_menu_801B90A0[D_menu_801B9098], 36, 0, 0, 50, 5, 10, gMainController,
                                           &D_menu_801B9160[D_menu_801B9098]))) {
                AUDIO_PLAY_SFX(NA_SE_CURSOR, gDefaultSfxSource, 4);
                D_menu_801B9150[D_menu_801B9098][0] = sCharMap[D_menu_801B90A0[D_menu_801B9098]];
                D_menu_801B90D0[D_menu_801B9098] = 0.0f;
                D_menu_801B9100[D_menu_801B9098] = 0.0f;
            }

            if (gControllerPress[gMainController].button & A_BUTTON) {
                D_menu_801B90D0[D_menu_801B9098] = 0.0f;
                if (D_menu_801B9138 != 0) {
                    AUDIO_PLAY_SFX(NA_SE_DECIDE, gDefaultSfxSource, 4);
                    D_menu_801B9140[0] = 10;
                    D_menu_801B9140[1] = 10;
                    D_menu_801B9140[2] = 10;
                    D_menu_801B9138 = -1;
                    D_menu_801B9128 = 2;
                    break;
                }
                if (D_menu_801B9098 < 3) {
                    AUDIO_PLAY_SFX(NA_SE_DECIDE, gDefaultSfxSource, 4);
                    D_menu_801B90D0[D_menu_801B9098] = 0.0f;
                    D_menu_801B9140[D_menu_801B9098] = 15;
                    D_menu_801B9128 = 1;
                    break;
                }
            }

            if ((gControllerPress[gMainController].button & B_BUTTON) && (D_menu_801B9098 != 0)) {
                AUDIO_PLAY_SFX(NA_SE_CANCEL, gDefaultSfxSource, 4);
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
            if (D_menu_801B9140[D_menu_801B9098] == 0) {
                D_menu_801B9128 = 0;
            }
            break;

        case 1:
            D_menu_801B9140[D_menu_801B9098]--;
            if (D_menu_801B9140[D_menu_801B9098] == 0) {
                if ((D_menu_801B9098 + 1) > 2) {
                    D_menu_801B9138 = 1;
                }

                D_menu_801B9098++;
                D_menu_801B9128 = 0;
            }
            break;

        case 2:
            D_menu_801B9140[0]--;
            D_menu_801B9140[1]--;
            D_menu_801B9140[2]--;

            if (D_menu_801B9140[0] != 0) {
                break; // looks fake
            }
            D_menu_801B917C = 20;
            D_menu_801B9128 = 3;
            break;

        case 3:
            if (D_menu_801B917C == 0) {
                sMainMenuState = 2;
            }
            break;
    }
}

void Option_NameEntry_Draw(void) {
    static f32 D_menu_801AF300[] = { -120.0f, 0.0f, 120.0f };
    f32 dirX;
    f32 dirY;
    f32 dirZ;
    s32 bitmask[3];
    s32 i;
    static f32 D_menu_801AF30C[6] = { 51.0f, 138.0f, 118.0f, 166.0f, 138.0f, 267.0f };
    static f32 D_menu_801AF324[6] = { 29.0f, 49.0f, 145.0f, 155.0f, 87.0f, 127.0f };

    RCP_SetupDL(&gMasterDisp, SETUPDL_76_OPTIONAL);

    if (gLastGameState == GSTATE_ENDING) {
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
        Graphics_DisplayLargeText(D_menu_801AF30C[0], D_menu_801AF324[0], 1.0f, 1.0f, "CONGRATULATIONS");
    }

    if (D_menu_801B9178 != 0) {
        return;
    }

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);
    Graphics_DisplaySmallText(D_menu_801AF30C[1], D_menu_801AF324[1], 1.0f, 1.0f, "RANK");
    Graphics_DisplaySmallText(D_menu_801AF30C[2], D_menu_801AF324[2], 1.0f, 1.0f, "TOTAL HITS");

    PRINTF("p:%d x:%f y:%f\n");

    if (D_menu_801B9138 == 1) {
        if ((gGameFrameCount & 0x10) != 0) {
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);
            Lib_TextureRect_IA8(&gMasterDisp, aTextEnd, 32, 8, D_menu_801AF30C[5], D_menu_801AF324[5], 1.0f, 1.0f);
        }
    }

    Option_OrdinalNumbers_Draw(sRankInPos, D_menu_801AF30C[4], D_menu_801AF324[4]);

    RCP_SetupDL(&gMasterDisp, SETUPDL_76);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    Graphics_DisplayLargeNumber(D_menu_801AF30C[3] - ((HUD_CountDigits(gTotalHits) - 1) * 13), D_menu_801AF324[3],
                                gTotalHits);

    Map_801A9FD4(true);

    Option_ScrollPlanetTexture();

    for (i = 0; i < 3; i++) {
        if (i == D_menu_801B9098) {
            D_menu_801B9100[i] += 1.0f;
        } else {
            D_menu_801B9100[i] = 0.0f;
        }

        bitmask[i] = 0xFFFFFFFF;

        if (D_menu_801B9140[i] != 0) {
            bitmask[i] = 0x00000001;
            D_menu_801B9100[i] = 0.0f;
        }
    }

    Option_SetMenuLightPos(sNameEntryLightXrot, sNameEntryLightYrot, 127.0f, &dirX, &dirY, &dirZ);

    Lights_SetOneLight(&gMasterDisp, dirX, dirY, dirZ, 255, 255, 255, 65, 70, 48);

    Matrix_Push(&gGfxMatrix);

    Matrix_LookAt(gGfxMatrix, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -100.0f, 0.0f, 1.0f, 0.0f, MTXF_APPLY);

    Matrix_SetGfxMtx(&gMasterDisp);

    for (i = 0; i < 3; i++) {
        // @port: Tag the transform.
        FrameInterpolation_RecordOpenChild("Option_3DFont_Draw", i);

        if (gGameFrameCount & bitmask[i]) {
            Option_3DFont_Draw(D_menu_801B9150[i][0], D_menu_801AF300[i], 18.0f, -455.0f, 1.0f,
                               D_menu_801B90C0[i] + D_menu_801B90F0[i], D_menu_801B90D0[i] + D_menu_801B9100[i],
                               D_menu_801B90E0[i] + D_menu_801B9110[i]);
        }

        // @port Pop the transform id.
        FrameInterpolation_RecordCloseChild();
    }

    Matrix_Pop(&gGfxMatrix);
}

void Option_Ranking_SaveData(void) {
    s32 i;
    s32 j;
    s32 missionHitCount;
    s32 originalRankIdx;
    PlanetId planetId;
    s32 currentRankIdx;
    u8 rankNameEntry[11][3];
    u8 rankingRoute[11];
    u8 rankingLives[11];
    u8 rankingMedal[11];
    PlanetStats planetStats[11][7];

    rankNameEntry[10][0] = D_menu_801B9150[0][0];
    rankNameEntry[10][1] = D_menu_801B9150[1][0];
    rankNameEntry[10][2] = D_menu_801B9150[2][0];

    rankingRoute[10] = gMissionNumber + 1;

    rankingLives[10] = gLifeCount[0];

    rankingMedal[10] = 0;

    for (i = 0; i < ROUTE_MAX; i++) {
        rankingMedal[10] |= (gMissionMedal[i] << i);
    }

    for (j = 0; j < ROUTE_MAX; j++) {
        planetStats[10][j].hitCountOver256 = 0;

        missionHitCount = gMissionHitCount[j];

        if (missionHitCount > 255) {
            missionHitCount -= 256;
            planetStats[10][j].hitCountOver256 = 1;
        }

        planetStats[10][j].hitCount = missionHitCount;

        planetId = gMissionPlanet[j];

        if (gMissionPlanet[j] == PLANET_VENOM) {
            planetId = SAVE_SLOT_VENOM_1;
        }

        if (gMissionPlanet[j] == PLANET_SOLAR) {
            planetId = SAVE_SLOT_SOLAR;
        }

        planetStats[10][j].planetId = planetId;

        planetStats[10][j].peppyAlive = ((gMissionTeamStatus[j] & TEAMSTATUS_PEPPY) >> 16) & 1;
        planetStats[10][j].slippyAlive = ((gMissionTeamStatus[j] & TEAMSTATUS_SLIPPY) >> 8) & 1;
        planetStats[10][j].falcoAlive = (gMissionTeamStatus[j] & TEAMSTATUS_FALCO) & 1;
    }

    for (i = 0; i < RANKING_MAX; i++) {
        rankNameEntry[i][0] = gSaveFile.save.data.rankNameEntry[i][0];
        rankNameEntry[i][1] = gSaveFile.save.data.rankNameEntry[i][1];
        rankNameEntry[i][2] = gSaveFile.save.data.rankNameEntry[i][2];
        rankingRoute[i] = gSaveFile.save.data.rankingRoute[i];
        rankingLives[i] = gSaveFile.save.data.rankingLives[i];
        rankingMedal[i] = gSaveFile.save.data.rankingMedal[i];

        for (j = 0; j < ROUTE_MAX; j++) {
            planetStats[i][j].hitCount = gSaveFile.save.data.stats[i][j].hitCount;
            planetStats[i][j].planetId = gSaveFile.save.data.stats[i][j].planetId;
            planetStats[i][j].hitCountOver256 = gSaveFile.save.data.stats[i][j].hitCountOver256;
            planetStats[i][j].peppyAlive = gSaveFile.save.data.stats[i][j].peppyAlive;
            planetStats[i][j].falcoAlive = gSaveFile.save.data.stats[i][j].falcoAlive;
            planetStats[i][j].slippyAlive = gSaveFile.save.data.stats[i][j].slippyAlive;
        }
    }

    for (currentRankIdx = 0, i = 0; i < RANKING_MAX; i++) {
        if (i == sRankInPos) {
            originalRankIdx = currentRankIdx;
            currentRankIdx = 10;
        }

        gSaveFile.save.data.rankNameEntry[i][0] = rankNameEntry[currentRankIdx][0];
        gSaveFile.save.data.rankNameEntry[i][1] = rankNameEntry[currentRankIdx][1];
        gSaveFile.save.data.rankNameEntry[i][2] = rankNameEntry[currentRankIdx][2];
        gSaveFile.save.data.rankingRoute[i] = rankingRoute[currentRankIdx];
        gSaveFile.save.data.rankingLives[i] = rankingLives[currentRankIdx];
        gSaveFile.save.data.rankingMedal[i] = rankingMedal[currentRankIdx];

        for (j = 0; j < ROUTE_MAX; j++) {
            gSaveFile.save.data.stats[i][j].hitCount = planetStats[currentRankIdx][j].hitCount;
            gSaveFile.save.data.stats[i][j].planetId = planetStats[currentRankIdx][j].planetId;
            gSaveFile.save.data.stats[i][j].hitCountOver256 = planetStats[currentRankIdx][j].hitCountOver256;
            gSaveFile.save.data.stats[i][j].peppyAlive = planetStats[currentRankIdx][j].peppyAlive;
            gSaveFile.save.data.stats[i][j].falcoAlive = planetStats[currentRankIdx][j].falcoAlive;
            gSaveFile.save.data.stats[i][j].slippyAlive = planetStats[currentRankIdx][j].slippyAlive;
        }

        if (i == sRankInPos) {
            currentRankIdx = originalRankIdx;
        } else {
            currentRankIdx++;
        }
    }

    gSaveFile.save.data.unk_EA = sRankInPos;

    Save_Write();
}

void Option_3DFont_Draw(s32 character, f32 x, f32 y, f32 z, f32 scale, f32 xAngle, f32 yAngle, f32 zAngle) {
    static Gfx* s3DFont[37] = {
        aFont3D_A, aFont3D_B, aFont3D_C, aFont3D_D, aFont3D_E, aFont3D_F, aFont3D_G,   aFont3D_H, aFont3D_I, aFont3D_J,
        aFont3D_K, aFont3D_L, aFont3D_M, aFont3D_N, aFont3D_O, aFont3D_P, aFont3D_Q,   aFont3D_R, aFont3D_S, aFont3D_T,
        aFont3D_U, aFont3D_V, aFont3D_W, aFont3D_X, aFont3D_Y, aFont3D_Z, aFont3D_0,   aFont3D_1, aFont3D_2, aFont3D_3,
        aFont3D_4, aFont3D_5, aFont3D_6, aFont3D_7, aFont3D_8, aFont3D_9, aFont3D_DOT,
    };
    s32 i;
    s32 charIndex = -1;

    for (i = 0; sCharMap[i] != NULL; i++) {
        if (character == sCharMap[i]) {
            charIndex = i;
            break;
        }
    }

    if (charIndex == -1) {
        return;
    }

    RCP_SetupDL(&gMasterDisp, SETUPDL_23);
    gSPTexture(gMasterDisp++, 2500, 200, 0, G_TX_RENDERTILE, G_ON);
    gSPSetGeometryMode(gMasterDisp++, G_TEXTURE_GEN);

    Matrix_Push(&gGfxMatrix);

    Matrix_Translate(gGfxMatrix, x, y, z, MTXF_APPLY);

    Matrix_RotateZ(gGfxMatrix, M_DTOR * zAngle, MTXF_APPLY);
    Matrix_RotateX(gGfxMatrix, M_DTOR * xAngle, MTXF_APPLY);
    Matrix_RotateY(gGfxMatrix, M_DTOR * yAngle, MTXF_APPLY);

    Matrix_Scale(gGfxMatrix, scale, scale, scale, MTXF_APPLY);

    Matrix_SetGfxMtx(&gMasterDisp);

    gSPDisplayList(gMasterDisp++, s3DFont[charIndex]);

    Matrix_Pop(&gGfxMatrix);
}

s32 Option_GetCharIndex(s32 character) {
    s32 charIdx = 0;

    // 'for()' causes instruction reorder
    while (sCharMap[charIdx] != 0) {
        if (sCharMap[charIdx] == character) {
            break;
        }
        charIdx++;
    }

    if (sCharMap[charIdx] == 0) {
        charIdx = 0;
    }

    return charIdx;
}

void Option_Score_Update(void) {
    switch (sMainMenuState) {
        case 0:
            Option_Ranking_Setup();

            D_menu_801B93E4 = sRankInPos;

            if ((sRankInPos < 0) || (sRankInPos >= 10)) {
                D_menu_801B93E4 = 0;
            }

            D_menu_801B91D4 = 114.0f - D_menu_801B93E4 * 130.0f;
            D_menu_801B91D8 = -6.0f + D_menu_801B93E4 * 130.0f;
            sOptionCardList[3].tex.xPos = sOptionCardCurTextPosX[3];
            sOptionCardList[3].tex.yPos = 23.0f;
            sOptionCardList[3].tex.xScale = 1.0f;
            sOptionCardList[3].tex.yScale = 1.0f;
            sOptionCardList[3].drawTex = true;
            sOptionCardList[3].frame.y = 90.0f;
            sOptionCardList[3].frame.xScale = 0.4f;
            sOptionCardList[3].frame.yScale = 0.21f;
            sOptionCardList[3].drawFrame = true;
            sMainMenuState++;
            break;

        case 1:
            Option_Score_Update2();
            break;
    }
}

void Option_Score_Update2(void) {
    Option_Ranking2_Cursor();

    if (gControllerPress[gMainController].button &
        (START_BUTTON | A_BUTTON | B_BUTTON | D_CBUTTONS | L_CBUTTONS | U_CBUTTONS)) {
        AUDIO_PLAY_SFX(NA_SE_DECIDE, gDefaultSfxSource, 4);

        gDrawMode = DRAW_NONE;
        sMainMenuState = 0;

        if (gLastGameState == GSTATE_GAME_OVER) {
            gStarCount = 0;
            gGameState = GSTATE_INIT;
            gLifeCount[0] = 2;
            gTotalHits = 0;
        } else if (gLastGameState == GSTATE_ENDING) {
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 1);
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 1);
            sMenuEntryState = OPTION_INVOICE;
        }
    }
}

void Option_Score_Draw(void) {
    Option_RankingMenu2_Draw();
    Option_Menu_Push();
    Option_DrawMenuCard(sOptionCardList[3].frame);
    Matrix_Pop(&gGfxMatrix);
    Option_DrawCardLabel(sOptionCardList[3].tex);
}

void Option_Invoice_Update(void) {
    switch (sMainMenuState) {
        case 0:
            gStarCount = 0;
            gBgColor = 0;
            gFillScreenRed = 0;
            gFillScreenGreen = 0;
            gFillScreenBlue = 0;
            gFillScreenAlpha = 0;
            D_menu_801B9090 = 0;
            D_menu_801B9178 = 30;
            sMainMenuState++;
            break;

        case 1:
            if (D_menu_801B9178 == 0) {
                if (((gTotalHits * 64) >= 50000) && ((gTotalHits * 64) < 70000)) {
                    AUDIO_PLAY_SFX(NA_SE_VO_PEPPER_CONSENT, gDefaultSfxSource, 4);
                }
                if ((gTotalHits * 64) >= 70000) {
                    AUDIO_PLAY_SFX(NA_SE_VO_PEPPER_SURPRISE, gDefaultSfxSource, 4);
                }
                D_menu_801B9178 = 20;
                sMainMenuState++;
            }
            break;

        case 2:
            if ((D_menu_801B9178 == 0) &&
                (gControllerPress[gMainController].button &
                 (START_BUTTON | A_BUTTON | B_BUTTON | D_CBUTTONS | L_CBUTTONS | U_CBUTTONS))) {
                AUDIO_PLAY_SFX(NA_SE_STARFOX_SEAL, gDefaultSfxSource, 4);
                D_menu_801B9090 = 1;
                D_menu_801B9178 = 60;
                sMainMenuState++;
            }
            break;

        case 3:
            if (D_menu_801B9178 == 0) {
                gStarCount = 0;
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

    Graphics_FillRectangle(&gMasterDisp, 25, 18, SCREEN_WIDTH - 25, SCREEN_HEIGHT - 18, 255, 255, 255, 255);

    RCP_SetupDL(&gMasterDisp, SETUPDL_78_OPTIONAL);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    Lib_TextureRect_CI4(&gMasterDisp, D_OPT_8000000, D_OPT_8000680, 128, 26, D_menu_801AF3D0[0], D_menu_801AF3F0[0],
                        1.0f, 1.0f);

    Lib_TextureRect_CI4(&gMasterDisp, D_OPT_80006A0, D_OPT_80017A0, 256, 34, D_menu_801AF3D0[1], D_menu_801AF3F0[1],
                        1.0f, 1.0f);

    Lib_TextureRect_CI4(&gMasterDisp, D_OPT_80017C0, D_OPT_80038C0, 256, 66, D_menu_801AF3D0[2], D_menu_801AF3F0[2],
                        1.0f, 1.0f);

    RCP_SetupDL(&gMasterDisp, SETUPDL_76_OPTIONAL);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    Lib_TextureRect_RGBA16(&gMasterDisp, D_OPT_800E170, 188, 60, D_menu_801AF3D0[3], D_menu_801AF3F0[3], 1.0f, 1.0f);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 0, 0, 0, 255);
    Graphics_DisplayLargeNumber(D_menu_801AF3D0[6] - ((HUD_CountDigits(gTotalHits) - 1) * 13), D_menu_801AF3F0[6],
                                gTotalHits);

    temp_a0 = gTotalHits * 64;

    Graphics_DisplayLargeNumber(D_menu_801AF3D0[7] - ((HUD_CountDigits(temp_a0) - 1) * 13), D_menu_801AF3F0[7],
                                temp_a0);

    RCP_SetupDL(&gMasterDisp, SETUPDL_76);

    if (D_menu_801B9090) {
        gDPSetPrimColor(gMasterDisp++, 0, 0, 120, 0, 0, 192);
        Lib_TextureRect_IA8(&gMasterDisp, D_OPT_800D1F0, 80, 48, D_menu_801AF3D0[5], D_menu_801AF3F0[5], 1.0f, 1.0f);
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
