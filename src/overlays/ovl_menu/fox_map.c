/*
 * File: fox_map.c
 * System: Map
 * Description: Starfox Map Handler
 */

#include "mods.h"
#include "global.h"
#include "fox_map.h"
#include "fox_option.h"
#include "sf64save.h"
#include "prevent_bss_reordering.h"
#include "prevent_bss_reordering2.h"
// #include "prevent_bss_reordering3.h"
#include "assets/ast_map.h"
#include "assets/ast_text.h"
#include "assets/ast_font_3d.h"
#include "port/interpolation/FrameInterpolation.h"
#include "port/mods/PortEnhancements.h"

extern bool gBackToMap;

// BSS STARTS HERE
u8 gMapVenomCloudTex[96 * 96];
u8 gMapCorneriaTex[96 * 96];
u8 gMapFortunaTex[96 * 96];
u8 gMapAquasTex[96 * 96];
u8 gMapVenomTex[96 * 96];
u8 gMapTitaniaTex[96 * 96];
u8 gMapKatinaTex[96 * 96];
u8 gMapMacbethTex[96 * 96];
u8 gMapZonessTex[96 * 96];

s32 D_menu_801CD810;
f32 D_menu_801CD818[9];
s32 D_menu_801CD83C;
s32 sUnusedPathIdx[24]; // Path index, set but not used
s32 D_menu_801CD8A0[15];
s32 D_menu_801CD8E0[7];
s32 D_menu_801CD900[15]; // planet alpha used for something?
MissionStatus sPrevMissionStatus;
s32 D_menu_801CD940;
s32 sMapState;
s32 sMapSubState; // Another type of map state? Investigate
s32 D_menu_801CD94C;
PlanetId sPrevPlanetId;
PlanetId sCurrentPlanetId; // sCurrentPlanetId
PlanetId sNextPlanetId;
s32 D_menu_801CD95C;
s32 D_menu_801CD960;
s32 D_menu_801CD964;
s32 D_menu_801CD968;
bool D_menu_801CD96C;
s32 D_menu_801CD970;
bool D_menu_801CD974;
s32 D_menu_801CD978;
s32 D_menu_801CD97C;
bool D_menu_801CD980;
s32 D_menu_801CD984;
s32 D_menu_801CD988;
s32 D_menu_801CD98C;
s32 D_menu_801CD990;
s32 D_menu_801CD994;
s32 D_menu_801CD998;
f32 D_menu_801CD99C;
bool D_menu_801CD9A0;
s32 D_menu_801CD9A4;
s32 sLevelPlayed;
s32 D_menu_801CD9AC;
f32 D_menu_801CD9B0;
f32 D_menu_801CD9B4;
s32 sMapTimer1;
s32 sMapTimer2;
s32 sMapTimer3;
s32 D_menu_801CD9C4;
s32 D_menu_801CD9C8;
s32 sRestartLevelStates;
s32 sExplosionAnimIdx;
s32 D_menu_801CD9D4;
s32 D_menu_801CD9D8;
f32 sPrologueTextXpos;
f32 sPrologueTextYpos;
f32 sPrologueNextTexAlpha;
f32 sPrologueCurrentTexAlpha;
f32 D_menu_801CD9EC;
s32 sPrologueTexIdx;
f32 sMapCamEyeX;     // x
f32 sMapCamEyeY;     // y
f32 sMapCamEyeZ;     // z
f32 sMapCamAtX;      // x
f32 sMapCamAtY;      // y
f32 sMapCamAtZ;      // z
f32 D_menu_801CDA0C; // camera x
f32 D_menu_801CDA10; // camera y
f32 D_menu_801CDA14;
f32 D_menu_801CDA18;
f32 D_menu_801CDA1C;
f32 sMapCamUpX;
f32 sMapCamUpY;
f32 sMapCamUpZ;
f32 sPathFollowCamAtX;
f32 sPathFollowCamAtY;
f32 sPathFollowCamEyeX;
f32 sPathFollowCamEyeY;
Vec3f sZoomPlanetCamAt;
Vec3f sZoomPlanetCamEye;
Matrix D_menu_801CDA60[15];
Matrix D_menu_801CDE20[15]; // planet related
Matrix D_menu_801CE1E0[15];
Matrix D_menu_801CE5A0[15];
Vec3f sPlanetPositions[15];
f32 D_menu_801CEA18[15];
f32 sCurrentPlanetCamZDist;
f32 D_menu_801CEA58;
f32 D_menu_801CEA5C;
f32 D_menu_801CEA60;
f32 D_menu_801CEA64;
f32 D_menu_801CEA68;
f32 sMapPlanetCardAlpha;
f32 sMapPlanetCardAlphaScale;
s32 sTeamStatusAlpha;
f32 D_menu_801CEA78;
f32 D_menu_801CEA7C;
f32 D_menu_801CEA80;
f32 D_menu_801CEA84;
f32 D_menu_801CEA88;
f32 D_menu_801CEA8C;
f32 D_menu_801CEA90;
f32 D_menu_801CEA94;
s32 D_menu_801CEA98;
f32 D_menu_801CEA9C;
f32 D_menu_801CEAA0;
f32 D_menu_801CEAA4;
f32 sCursorYpos;
f32 D_menu_801CEAAC;
f32 D_menu_801CEAB0;
s32 D_menu_801CEAB4;
f32 D_menu_801CEAB8[15];
f32 D_menu_801CEAF8[15];
s32 D_menu_801CEB34;
s32 D_menu_801CEB38;
f32 sMapCorneriaExplosionScale;
f32 D_menu_801CEB40;
bool sPlanetExplosions[EXPLOSIONS_MAX];
s32 D_menu_801CEB58[3][10];
s32 D_menu_801CEBD0[3][10];
f32 D_menu_801CEC48[3][10];
f32 D_menu_801CECC0[3][10];
f32 D_menu_801CED38[3][10];
f32 D_menu_801CEDB0[3][10];
f32 D_menu_801CEE28[3][10];
s32 D_menu_801CEEA0;
s32 D_menu_801CEEA4;
s32 D_menu_801CEEA8;
s32 D_menu_801CEEAC;
Vec3f D_menu_801CEEB0;
f32 D_menu_801CEEBC;
f32 D_menu_801CEEC0;
s32 D_menu_801CEEC4;
s32 D_menu_801CEEC8;
s32 D_menu_801CEECC;
s32 D_menu_801CEED0;
s32 D_menu_801CEED4;
s32 D_menu_801CEED8;
f32 D_menu_801CEEDC;
f32 D_menu_801CEEE0;
Vec3f D_menu_801CEEE8[9];
Vec3f D_menu_801CEF58[9];
s32 D_menu_801CEFC4;
s32 D_menu_801CEFC8;
s32 D_menu_801CEFCC;
s32 D_menu_801CEFD0;
s32 D_menu_801CEFD4;
bool D_menu_801CEFD8;
s32 D_menu_801CEFDC;
f32 D_menu_801CEFE0;
f32 D_menu_801CEFE8[3];
f32 D_menu_801CEFF4;
f32 D_menu_801CEFF8;
s32 D_menu_801CF000[3];
s32 D_menu_801CF00C;
s32 D_menu_801CF010;
s32 D_menu_801CF014;
s32 D_menu_801CF018;
f32 s3DFontXpos[8];
f32 s3DFontYpos[8];
f32 s3DFontZpos[8];
f32 s3DFontScale;
f32 s3DFontXrot[8];
f32 s3DFontYrot[8];
f32* D_menu_801CF0C8;
f32* D_menu_801CF0CC;
f32* D_menu_801CF0D0;
s32 D_menu_801CF0D8[8];
s32 D_menu_801CF0F8[8];
s32 D_menu_801CF118;
s32 D_menu_801CF11C;
bool D_menu_801CF120;
f32 D_menu_801CF124;

s32 D_menu_801AF420[2] = { 10, 20 };

u16* sBriefingMsg[15][2] = {
    { gMsg_ID_1220, gMsg_ID_1230 }, { gMsg_ID_1320, gMsg_ID_1330 },
    { gMsg_ID_1300, gMsg_ID_1310 }, { gMsg_ID_1420, gMsg_ID_1430 },
    { gMsg_ID_1260, gMsg_ID_1270 }, { gMsg_ID_1440, gMsg_ID_1450 },
    { gMsg_ID_1360, gMsg_ID_1370 }, { gMsg_ID_1340, gMsg_ID_1350 },
    { gMsg_ID_1400, gMsg_ID_1410 }, { gMsg_ID_1200, gMsg_ID_1210 },
    { gMsg_ID_1240, gMsg_ID_1250 }, { gMsg_ID_1380, gMsg_ID_1390 },
    { gMsg_ID_1280, gMsg_ID_1290 }, { NULL, NULL },
    { gMsg_ID_1460, gMsg_ID_1470 },
};

Planet sPlanets[PLANET_MAX] = {
    {
        PLANET_METEO,
        { 1150.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f },
        -130.0f,
        1.0f,
        0,
        PL_ANIM_STATIC,
        PLANET_FORTUNA,
        PLANET_NONE,
        PLANET_KATINA,
    },
    {
        PLANET_AREA_6,
        { 1400.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f },
        -315.0f,
        0.15f,
        0,
        PL_ANIM_ROTATE_Y,
        PLANET_NONE,
        PLANET_NONE,
        PLANET_NONE,
    },
    {
        PLANET_BOLSE,
        { 1400.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f },
        -345.0f,
        0.15f,
        0,
        PL_ANIM_ROTATE_Y,
        PLANET_NONE,
        PLANET_NONE,
        PLANET_NONE,
    },
    {
        PLANET_SECTOR_Z,
        { 1125.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f },
        -285.0f,
        2.5f * 2.0f,
        0,
        PL_ANIM_BILLBOARD,
        PLANET_BOLSE,
        PLANET_AREA_6,
        PLANET_NONE,
    },
    {
        PLANET_SECTOR_X,
        { 750.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f },
        -60.0f,
        2.5f * 2.0f,
        0,
        PL_ANIM_BILLBOARD,
        PLANET_TITANIA,
        PLANET_MACBETH,
        PLANET_SECTOR_Z,
    },
    {
        PLANET_SECTOR_Y,
        { 1125.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f },
        -190.0f,
        2.5f * 2.0f,
        0,
        PL_ANIM_BILLBOARD,
        PLANET_KATINA,
        PLANET_AQUAS,
        PLANET_NONE,
    },
    {
        PLANET_KATINA,
        { 750.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f },
        -150.0f,
        2.5f,
        0,
        PL_ANIM_SPIN,
        PLANET_SECTOR_X,
        PLANET_SOLAR,
        PLANET_NONE,
    },
    {
        PLANET_MACBETH,
        { 825.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f },
        -330.0f,
        2.5f,
        0,
        PL_ANIM_SPIN,
        PLANET_BOLSE,
        PLANET_AREA_6,
        PLANET_NONE,
    },
    {
        PLANET_ZONESS,
        { 900.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f },
        -260.0f,
        2.5f,
        0,
        PL_ANIM_SPIN,
        PLANET_MACBETH,
        PLANET_SECTOR_Z,
        PLANET_NONE,
    },
    {
        PLANET_CORNERIA,
        { 1500.0f, 0.0f, 10.0f },
        { 0.0f, 0.0f, 0.0f },
        -150.0f,
        5.0f,
        0,
        PL_ANIM_SPIN,
        PLANET_METEO,
        PLANET_SECTOR_Y,
        PLANET_NONE,
    },
    {
        PLANET_TITANIA,
        { 975.0f, 0.0f, -10.0f },
        { 0.0f, 0.0f, 0.0f },
        -375.0f,
        2.5f,
        0,
        PL_ANIM_SPIN,
        PLANET_BOLSE,
        PLANET_NONE,
        PLANET_NONE,
    },
    {
        PLANET_AQUAS,
        { 900.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f },
        -220.0f,
        2.5f,
        0,
        PL_ANIM_SPIN,
        PLANET_ZONESS,
        PLANET_NONE,
        PLANET_NONE,
    },
    {
        PLANET_FORTUNA,
        { 975.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f },
        -105.0f,
        2.5f,
        0,
        PL_ANIM_SPIN,
        PLANET_SECTOR_X,
        PLANET_SOLAR,
        PLANET_NONE,
    },
    {
        PLANET_VENOM,
        { 1800.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f },
        -330.0f,
        9.0f,
        0,
        PL_ANIM_SPIN,
        PLANET_NONE,
        PLANET_NONE,
        PLANET_NONE,
    },
    {
        PLANET_SOLAR,
        { 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f },
        0.0f,
        10.0f,
        0,
        PL_ANIM_ROTATE_Z,
        PLANET_MACBETH,
        PLANET_NONE,
        PLANET_NONE,
    },
};

// unused
PlanetId sPlanetList[] = {
    PLANET_CORNERIA, PLANET_METEO,  PLANET_TITANIA, PLANET_SECTOR_X, PLANET_AQUAS,
    PLANET_BOLSE,    PLANET_VENOM,  PLANET_FORTUNA, PLANET_AREA_6,   PLANET_MACBETH,
    PLANET_SECTOR_Z, PLANET_ZONESS, PLANET_KATINA,  PLANET_SECTOR_Y, PLANET_SOLAR,
};

Gfx* sExplosionAnimDLs[4] = { aMapExplosion1DL, aMapExplosion2DL, aMapExplosion3DL, aMapExplosion4DL };

TitleCard sPlanetNameCards[14] = {
    { D_MAP_6007B90, 128, 28, 95.0f }, { D_MAP_60030D0, 96, 28, 110.0f },  { D_MAP_60131A0, 176, 12, 73.0f },
    { D_MAP_6009AD0, 168, 28, 77.0f }, { D_MAP_600B9B0, 168, 28, 74.0f },  { D_MAP_6001C80, 96, 13, 106.0f },
    { D_MAP_6011660, 176, 12, 75.0f }, { D_MAP_6010010, 112, 13, 109.0f }, { D_MAP_6017640, 112, 28, 101.0f },
    { D_MAP_6015CE0, 96, 28, 108.0f }, { D_MAP_600E210, 160, 28, 78.0f },  { D_MAP_6014360, 176, 12, 73.0f },
    { D_MAP_6004AC0, 168, 19, 72.0f }, { D_MAP_6006320, 104, 28, 105.0f },
};

TitleCard sPlanetTitleCards[] = {
    { D_MAP_6008990, 232, 19, 46.0f }, { D_MAP_6003B50, 208, 19, 56.0f }, { D_MAP_60139E0, 128, 19, 98.0f },
    { D_MAP_600AD30, 168, 19, 77.0f }, { D_MAP_600CC10, 128, 19, 95.0f }, { D_MAP_6002160, 208, 19, 57.0f },
    { D_MAP_6011EA0, 256, 19, 40.0f }, { D_MAP_60105C0, 224, 19, 49.0f }, { D_MAP_6018280, 184, 19, 70.0f },
    { D_MAP_6016760, 200, 18, 61.0f }, { D_MAP_600F390, 168, 19, 75.0f }, { D_MAP_6014BA0, 232, 19, 43.0f },
    { D_MAP_6005740, 160, 19, 81.0f }, { D_MAP_6006E80, 176, 19, 70.0f },
};

char* sPlanetNames[] = {
    "ME", "A6", "BO", "SZ", "SX", "SY", "KA", "MA", "ZO", "CO", "TI", "AQ", "FO", "VE", "SO",
};

Gfx* sMapGralPepperFaceDLs[2] = {
    aMapGralPepperFace1DL,
    aMapGralPepperFace2DL,
};

ObjPosition sMapMeteors[] = {
    { -491.0f, 1170.0f, 20.0f, 0.71f },  { -488.0f, 1135.0f, 15.0f, 0.6f },   { -496.0f, 1090.0f, 0.0f, 0.50f },
    { -489.0f, 1200.0f, 0.0f, 0.6f },    { -489.0f, 1150.0f, -15.0f, 0.80f }, { -487.0f, 1143.0f, -15.0f, 0.8f },
    { -493.0f, 1182.0f, -20.0f, 0.90f }, { -491.0f, 1080.0f, -25.0f, 0.8f },  { -497.0f, 1114.0f, -25.0f, 0.70f },
    { -497.0f, 1164.0f, -20.0f, 0.9f },  { -485.0f, 1206.0f, 15.0f, 1.10f },  { -488.0f, 1213.0f, -20.0f, 1.1f },
    { -485.0f, 1257.0f, 0.0f, 1.10f },   { -491.0f, 1213.0f, -20.0f, 0.9f },  { -484.0f, 1295.0f, 0.0f, 0.80f },
    { -487.0f, 1277.0f, 20.0f, 0.8f },   { -485.0f, 1310.0f, 25.0f, 0.70f },  { -485.0f, 1331.0f, 0.0f, 0.8f },
    { -493.0f, 1118.0f, 15.0f, 0.80f },  { -494.0f, 1068.0f, 30.0f, 0.6f },   { -504.0f, 1018.0f, -30.0f, 0.50f },
    { -492.0f, 1071.0f, -10.0f, 0.6f },  { -494.0f, 1164.0f, -10.0f, 0.50f }, { -498.0f, 1091.0f, 0.0f, 0.5f },
    { -493.0f, 1082.0f, 0.0f, 0.60f },   { -498.0f, 1141.0f, 15.0f, 0.7f },   { -498.0f, 1034.0f, 15.0f, 0.70f },
    { -504.0f, 1041.0f, 20.0f, 0.8f },   { -507.0f, 1076.0f, 25.0f, 0.70f },  { -504.0f, 1092.0f, 0.0f, 0.8f },
    { -499.0f, 1076.0f, 20.0f, 1.00f },  { -519.0f, 1084.0f, -15.0f, 1.0f },  { -506.0f, 1133.0f, 20.0f, 1.10f },
    { -502.0f, 1144.0f, 0.0f, 1.0f },    { -514.0f, 1109.0f, -10.0f, 0.90f }, { -521.0f, 1136.0f, -20.0f, 0.8f },
    { -511.0f, 1052.0f, 20.0f, 0.80f },  { -515.0f, 1142.0f, -25.0f, 0.6f },  { -518.0f, 1138.0f, -20.0f, 0.80f },
    { -512.0f, 1099.0f, -15.0f, 0.5f },  { -523.0f, 1179.0f, -30.0f, 0.70f }, { -519.0f, 1176.0f, -30.0f, 0.5f },
};

ObjPosition sMapArea6Ships[4] = {
    { 50.0f, 1410.0f, 40.0f, 0.10f },
    { 35.0f, 1235.0f, 40.0f, 0.03f },
    { 42.0f, 1270.0f, 60.0f, 0.05f },
    { 35.0f, 1280.0f, 20.0f, 0.05f },
};

PlanetPath sPaths[24] = {
    { PL_PATH_BLU, PLANET_CORNERIA, PLANET_METEO, 5, 0, 0, 0 },
    { PL_PATH_BLU, PLANET_METEO, PLANET_FORTUNA, 5, 0, 0, 0 },
    { PL_PATH_BLU, PLANET_FORTUNA, PLANET_SECTOR_X, 5, 0, 0, 0 },
    { PL_PATH_BLU, PLANET_SECTOR_X, PLANET_TITANIA, 5, 0, 0, 0 },
    { PL_PATH_BLU, PLANET_TITANIA, PLANET_BOLSE, 5, 0, 0, 0 },
    { PL_PATH_BLU, PLANET_KATINA, PLANET_SECTOR_X, 5, 0, 0, 0 },
    { PL_PATH_BLU, PLANET_MACBETH, PLANET_BOLSE, 5, 0, 0, 0 },
    { PL_PATH_BLU, PLANET_SECTOR_Z, PLANET_BOLSE, 5, 0, 0, 0 },
    { PL_PATH_BLU, PLANET_BOLSE, PLANET_VENOM, 5, 0, 0, 0 },
    { PL_PATH_YLW, PLANET_SECTOR_Y, PLANET_KATINA, 5, 0, 0, 0 },
    { PL_PATH_YLW, PLANET_KATINA, PLANET_SOLAR, 5, 0, 0, 0 },
    { PL_PATH_YLW, PLANET_SOLAR, PLANET_MACBETH, 5, 0, 0, 0 },
    { PL_PATH_YLW, PLANET_SECTOR_X, PLANET_MACBETH, 5, 0, 0, 0 },
    { PL_PATH_YLW, PLANET_FORTUNA, PLANET_SOLAR, 5, 0, 0, 0 },
    { PL_PATH_YLW, PLANET_ZONESS, PLANET_MACBETH, 5, 0, 0, 0 },
    { PL_PATH_RED, PLANET_CORNERIA, PLANET_SECTOR_Y, 5, 0, 0, 0 },
    { PL_PATH_RED, PLANET_SECTOR_Y, PLANET_AQUAS, 5, 0, 0, 0 },
    { PL_PATH_RED, PLANET_AQUAS, PLANET_ZONESS, 5, 0, 0, 0 },
    { PL_PATH_RED, PLANET_ZONESS, PLANET_SECTOR_Z, 5, 0, 0, 0 },
    { PL_PATH_RED, PLANET_SECTOR_Z, PLANET_AREA_6, 5, 0, 0, 0 },
    { PL_PATH_RED, PLANET_MACBETH, PLANET_AREA_6, 5, 0, 0, 0 },
    { PL_PATH_RED, PLANET_AREA_6, PLANET_VENOM, 5, 0, 0, 0 },
    { PL_WARP_YLW, PLANET_METEO, PLANET_KATINA, 5, 0, 0, 0 },
    { PL_WARP_RED, PLANET_SECTOR_X, PLANET_SECTOR_Z, 10, 0, 0, 0 },
};

f32 D_menu_801AFFB8[] = {
    90.0f, 170.0f, 130.0f, 100.0f, 100.0f, 100.0f, 80.0f, 80.0f, 80.0f, 150.0f, 80.0f, 80.0f, 80.0f, 270.0f, 250.0f,
};

f32 D_menu_801AFFF4 = 0.0f; // yRot of something
f32 D_menu_801AFFF8 = 0.0f; // xRot of something
f32 D_menu_801AFFFC = 0.0f; // yRot of something
f32 D_menu_801B0000 = 0.0f; // xRot of something

s32 D_menu_801B0004[47] = {
    39, 35, 32, 30, 27, 26, 24, 22, 21, 20, 18, 17, 16, 15, 14, 13, 12, 12, 11, 10, 9, 9, 8, 8,
    7,  6,  6,  6,  5,  5,  4,  4,  4,  3,  3,  3,  3,  2,  2,  2,  2,  2,  2,  2,  2, 2, 1,
};

// Looks like a quarter of a circle
s32
    sMapQuarterCircleTex[47][96] = {
        { 0, 2, 2, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 11 },
        { 0, 2, 3, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13, 14, 15, 16, 17 },
        { 0,  2,  3,  4,  5,  6,  6,  7,  8,  8,  9,  9,  10, 10, 11, 11,
          12, 12, 13, 13, 14, 14, 15, 15, 16, 16, 17, 17, 18, 19, 20, 21 },
        { 0,  2,  4,  5,  5,  6,  7,  7,  8,  9,  9,  10, 10, 11, 11, 12, 12, 13,
          13, 14, 14, 15, 15, 16, 16, 17, 17, 18, 18, 19, 19, 20, 21, 22, 23, 24 },
        { 0,  3,  4,  5,  6,  7,  7,  8,  9,  9,  10, 10, 11, 11, 12, 12, 13, 13, 14, 14, 15,
          15, 16, 16, 17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 23, 23, 24, 25, 26, 27, 28 },
        { 0,  3,  4,  5,  6,  7,  7,  8,  9,  9,  10, 11, 11, 12, 12, 13, 13, 14, 14, 15, 15, 16,
          16, 17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 23, 24, 25, 25, 26, 27, 28, 29 },
        { 0,  3,  4,  5,  6,  7,  8,  9,  9,  10, 10, 11, 12, 12, 13, 13, 14, 14, 15, 15, 16, 16, 17, 17,
          18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 23, 24, 24, 25, 25, 26, 27, 27, 28, 29, 30, 31, 32 },
        { 0,  3,  4,  6,  7,  7,  8,  9,  10, 10, 11, 11, 12, 13, 13, 14, 14, 15, 15, 16, 16, 17, 17, 18, 18, 19,
          19, 20, 20, 21, 21, 22, 22, 23, 23, 24, 24, 25, 25, 26, 26, 27, 27, 28, 29, 29, 30, 31, 32, 33, 34, 35 },
        { 0,  3,  5,  6,  7,  8,  8,  9,  10, 10, 11, 12, 12, 13, 13, 14, 14, 15, 15, 16, 16, 17, 17, 18, 18, 19, 19,
          20, 20, 21, 21, 22, 22, 23, 23, 24, 24, 25, 25, 26, 26, 27, 27, 28, 29, 29, 30, 31, 31, 32, 33, 34, 35, 37 },
        { 0,  3,  5,  6,  7,  8,  8,  9,  10, 11, 11, 12, 12, 13, 14, 14, 15, 15, 16,
          16, 17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 23, 24, 24, 25, 25,
          26, 26, 27, 27, 28, 28, 29, 29, 30, 31, 31, 32, 33, 34, 34, 35, 37, 38 },
        { 0,  3,  5,  6,  7,  8,  9,  10, 10, 11, 12, 12, 13, 13, 14, 15, 15, 16, 16, 17,
          17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 23, 24, 24, 25, 25, 26, 26, 27,
          27, 28, 28, 29, 29, 30, 30, 31, 31, 32, 33, 33, 34, 35, 35, 36, 37, 38, 39, 41 },
        { 0,  3,  5,  6,  7,  8,  9,  10, 10, 11, 12, 12, 13, 14, 14, 15, 15, 16, 16, 17, 17,
          18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 23, 24, 24, 25, 25, 26, 26, 27, 27, 28,
          28, 29, 29, 30, 30, 31, 32, 32, 33, 33, 34, 35, 35, 36, 37, 38, 39, 40, 41, 42 },
        { 0,  3,  5,  6,  7,  8,  9,  10, 11, 11, 12, 13, 13, 14, 14, 15, 16, 16, 17, 17, 18, 18,
          19, 19, 20, 20, 21, 21, 22, 22, 23, 23, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29,
          30, 30, 31, 31, 32, 32, 33, 33, 34, 35, 35, 36, 37, 37, 38, 39, 40, 41, 42, 44 },
        { 0,  3,  5,  6,  7,  8,  9,  10, 11, 11, 12, 13, 13, 14, 15, 15, 16, 16, 17, 17, 18, 18,
          19, 20, 20, 21, 21, 21, 22, 22, 23, 23, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29,
          30, 30, 31, 31, 32, 32, 33, 34, 34, 35, 35, 36, 37, 37, 38, 39, 40, 40, 41, 42, 44, 45 },
        { 0,  3,  5,  6,  7,  8,  9,  10, 11, 12, 12, 13, 14, 14, 15, 15, 16, 17, 17, 18, 18, 19, 19,
          20, 20, 21, 21, 22, 22, 23, 23, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30, 31,
          31, 32, 32, 33, 33, 34, 34, 35, 35, 36, 37, 37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 47 },
        { 0,  4,  5,  7,  8,  9,  9,  10, 11, 12, 13, 13, 14, 14, 15, 16, 16, 17, 17, 18, 18, 19, 19, 20,
          21, 21, 22, 22, 23, 23, 23, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30, 31, 31, 32,
          32, 33, 33, 34, 34, 35, 36, 36, 37, 37, 38, 39, 39, 40, 41, 41, 42, 43, 44, 45, 47, 48 },
        { 0,  4,  5,  7,  8,  9,  10, 10, 11, 12, 13, 13, 14, 15, 15, 16, 16, 17, 18, 18, 19, 19, 20, 20,
          21, 21, 22, 22, 23, 23, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30, 31, 31, 32, 32,
          33, 33, 34, 34, 35, 35, 36, 36, 37, 37, 38, 39, 39, 40, 41, 41, 42, 43, 44, 45, 46, 47, 48, 50 },
        { 0,  4,  5,  7,  8,  9,  10, 10, 11, 12, 13, 13, 14, 15, 15, 16, 16, 17, 18, 18, 19, 19, 20, 20,
          21, 21, 22, 22, 23, 23, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30, 31, 31, 32, 32,
          33, 33, 34, 34, 35, 35, 36, 36, 37, 37, 38, 39, 39, 40, 41, 41, 42, 43, 44, 45, 46, 47, 48, 50 },
        { 0,  4,  5,  7,  8,  9,  10, 11, 11, 12, 13, 14, 14, 15, 15, 16, 17, 17, 18, 18, 19, 19, 20, 21, 21,
          22, 22, 23, 23, 24, 24, 25, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30, 31, 31, 32, 32, 33, 33,
          34, 34, 35, 35, 36, 36, 37, 38, 38, 39, 39, 40, 41, 41, 42, 43, 43, 44, 45, 46, 47, 48, 49, 51 },
        { 0,  4,  5,  7,  8,  9,  10, 11, 12, 12, 13, 14, 14, 15, 16, 16, 17, 17, 18, 19, 19, 20, 20, 21, 21, 22,
          22, 23, 23, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30, 31, 31, 32, 32, 33, 33, 34, 34, 35,
          35, 36, 36, 37, 37, 38, 38, 39, 39, 40, 41, 41, 42, 43, 43, 44, 45, 46, 46, 47, 48, 50, 51, 53 },
        { 0,  4,  6,  7,  8,  9,  10, 11, 12, 12, 13, 14, 15, 15, 16, 16, 17, 18, 18, 19, 19, 20, 20, 21, 22, 22,
          23, 23, 24, 24, 25, 25, 26, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30, 31, 31, 32, 32, 33, 33, 34, 34, 35,
          35, 36, 36, 37, 37, 38, 38, 39, 40, 40, 41, 41, 42, 43, 43, 44, 45, 45, 46, 47, 48, 49, 50, 51, 52, 54 },
        { 0,  4,  6,  7,  8,  9,  10, 11, 12, 12, 13, 14, 15, 15, 16, 16, 17, 18, 18, 19, 19, 20, 20, 21, 22, 22,
          23, 23, 24, 24, 25, 25, 26, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30, 31, 31, 32, 32, 33, 33, 34, 34, 35,
          35, 36, 36, 37, 37, 38, 38, 39, 40, 40, 41, 41, 42, 43, 43, 44, 45, 45, 46, 47, 48, 49, 50, 51, 52, 54 },
        { 0,  4,  6,  7,  8,  9,  10, 11, 12, 13, 13, 14, 15, 15, 16, 17, 17, 18, 18, 19, 20, 20, 21, 21, 22, 22, 23,
          23, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30, 31, 31, 32, 32, 33, 33, 34, 34, 35, 35, 36, 36,
          37, 37, 38, 38, 39, 39, 40, 40, 41, 41, 42, 43, 43, 44, 45, 45, 46, 47, 47, 48, 49, 50, 51, 52, 54, 56 },
        { 0,  4,  6,  7,  8,  9,  10, 11, 12, 13, 13, 14, 15, 15, 16, 17, 17, 18, 18, 19, 20, 20, 21, 21, 22, 22, 23,
          23, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30, 31, 31, 32, 32, 33, 33, 34, 34, 35, 35, 36, 36,
          37, 37, 38, 38, 39, 39, 40, 40, 41, 41, 42, 43, 43, 44, 45, 45, 46, 47, 47, 48, 49, 50, 51, 52, 54, 56 },
        { 0,  4,  6,  7,  8,  9,  10, 11, 12, 13, 14, 14, 15, 16, 16, 17, 18, 18, 19, 19, 20,
          20, 21, 21, 22, 23, 23, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 28, 29, 29, 30, 30,
          31, 31, 32, 32, 33, 33, 34, 34, 35, 35, 36, 36, 37, 37, 38, 38, 39, 39, 40, 40, 41,
          42, 42, 43, 43, 44, 45, 45, 46, 47, 47, 48, 49, 50, 51, 52, 53, 54, 55, 57 },
        { 0,  4,  6,  7,  8,  9,  10, 11, 12, 13, 14, 14, 15, 16, 16, 17, 18, 18, 19, 19, 20,
          21, 21, 22, 22, 23, 23, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30, 31,
          31, 32, 32, 33, 33, 34, 34, 35, 35, 36, 36, 37, 37, 38, 38, 39, 39, 40, 40, 41, 41,
          42, 42, 43, 43, 44, 45, 45, 46, 47, 47, 48, 49, 49, 50, 51, 52, 53, 54, 55, 57, 58 },
        { 0,  4,  6,  7,  8,  9,  10, 11, 12, 13, 14, 14, 15, 16, 16, 17, 18, 18, 19, 19, 20,
          21, 21, 22, 22, 23, 23, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30, 31,
          31, 32, 32, 33, 33, 34, 34, 35, 35, 36, 36, 37, 37, 38, 38, 39, 39, 40, 40, 41, 41,
          42, 42, 43, 43, 44, 45, 45, 46, 47, 47, 48, 49, 49, 50, 51, 52, 53, 54, 55, 57, 58 },
        { 0,  4,  6,  7,  8,  9,  10, 11, 12, 13, 14, 14, 15, 16, 16, 17, 18, 18, 19, 19, 20,
          21, 21, 22, 22, 23, 23, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30, 31,
          31, 32, 32, 33, 33, 34, 34, 35, 35, 36, 36, 37, 37, 38, 38, 39, 39, 40, 40, 41, 41,
          42, 42, 43, 43, 44, 45, 45, 46, 47, 47, 48, 49, 49, 50, 51, 52, 53, 54, 55, 57, 58 },
        { 0,  4,  6,  7,  8,  10, 11, 11, 12, 13, 14, 15, 15, 16, 17, 17, 18, 19, 19, 20, 20, 21,
          21, 22, 22, 23, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30, 30, 31, 31, 32,
          32, 33, 33, 34, 34, 35, 35, 36, 36, 37, 37, 38, 38, 39, 39, 40, 40, 41, 41, 42, 42, 43,
          44, 44, 45, 45, 46, 47, 47, 48, 49, 49, 50, 51, 52, 52, 53, 54, 55, 57, 58, 60 },
        { 0,  4,  6,  7,  8,  10, 11, 11, 12, 13, 14, 15, 15, 16, 17, 17, 18, 19, 19, 20, 20, 21,
          21, 22, 22, 23, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30, 30, 31, 31, 32,
          32, 33, 33, 34, 34, 35, 35, 36, 36, 37, 37, 38, 38, 39, 39, 40, 40, 41, 41, 42, 42, 43,
          44, 44, 45, 45, 46, 47, 47, 48, 49, 49, 50, 51, 52, 52, 53, 54, 55, 57, 58, 60 },
        { 0,  4,  6,  7,  9,  10, 11, 12, 12, 13, 14, 15, 15, 16, 17, 17, 18, 19, 19, 20, 20, 21,
          22, 22, 23, 23, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30, 31, 31, 32, 32,
          33, 33, 34, 34, 35, 35, 36, 36, 37, 37, 38, 38, 39, 39, 40, 40, 41, 41, 42, 42, 43, 43,
          44, 44, 45, 45, 46, 47, 47, 48, 49, 49, 50, 51, 51, 52, 53, 54, 55, 56, 57, 58, 59, 61 },
        { 0,  4,  6,  7,  9,  10, 11, 12, 12, 13, 14, 15, 15, 16, 17, 17, 18, 19, 19, 20, 20, 21,
          22, 22, 23, 23, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30, 31, 31, 32, 32,
          33, 33, 34, 34, 35, 35, 36, 36, 37, 37, 38, 38, 39, 39, 40, 40, 41, 41, 42, 42, 43, 43,
          44, 44, 45, 45, 46, 47, 47, 48, 49, 49, 50, 51, 51, 52, 53, 54, 55, 56, 57, 58, 59, 61 },
        { 0,  4,  6,  7,  9,  10, 11, 12, 12, 13, 14, 15, 15, 16, 17, 17, 18, 19, 19, 20, 20, 21,
          22, 22, 23, 23, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30, 31, 31, 32, 32,
          33, 33, 34, 34, 35, 35, 36, 36, 37, 37, 38, 38, 39, 39, 40, 40, 41, 41, 42, 42, 43, 43,
          44, 44, 45, 45, 46, 47, 47, 48, 49, 49, 50, 51, 51, 52, 53, 54, 55, 56, 57, 58, 59, 61 },
        { 0,  4,  6,  7,  9,  10, 11, 12, 13, 13, 14, 15, 16, 16, 17, 18, 18, 19, 20, 20, 21, 21, 22,
          22, 23, 23, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30, 31, 31, 32, 32, 32, 33, 33,
          34, 34, 35, 35, 36, 36, 37, 37, 38, 38, 39, 39, 40, 40, 41, 41, 42, 42, 43, 43, 44, 44, 45,
          46, 46, 47, 47, 48, 49, 49, 50, 51, 51, 52, 53, 53, 54, 55, 56, 57, 58, 59, 61, 63 },
        { 0,  4,  6,  7,  9,  10, 11, 12, 13, 13, 14, 15, 16, 16, 17, 18, 18, 19, 20, 20, 21, 21, 22,
          22, 23, 23, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30, 31, 31, 32, 32, 32, 33, 33,
          34, 34, 35, 35, 36, 36, 37, 37, 38, 38, 39, 39, 40, 40, 41, 41, 42, 42, 43, 43, 44, 44, 45,
          46, 46, 47, 47, 48, 49, 49, 50, 51, 51, 52, 53, 53, 54, 55, 56, 57, 58, 59, 61, 63 },
        { 0,  4,  6,  7,  9,  10, 11, 12, 13, 13, 14, 15, 16, 16, 17, 18, 18, 19, 20, 20, 21, 21, 22,
          22, 23, 23, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30, 31, 31, 32, 32, 32, 33, 33,
          34, 34, 35, 35, 36, 36, 37, 37, 38, 38, 39, 39, 40, 40, 41, 41, 42, 42, 43, 43, 44, 44, 45,
          46, 46, 47, 47, 48, 49, 49, 50, 51, 51, 52, 53, 53, 54, 55, 56, 57, 58, 59, 61, 63 },
        { 0,  4,  6,  7,  9,  10, 11, 12, 13, 13, 14, 15, 16, 16, 17, 18, 18, 19, 20, 20, 21, 21, 22,
          22, 23, 23, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30, 31, 31, 32, 32, 32, 33, 33,
          34, 34, 35, 35, 36, 36, 37, 37, 38, 38, 39, 39, 40, 40, 41, 41, 42, 42, 43, 43, 44, 44, 45,
          46, 46, 47, 47, 48, 49, 49, 50, 51, 51, 52, 53, 53, 54, 55, 56, 57, 58, 59, 61, 63 },
        { 0,  4,  6,  8,  9,  10, 11, 12, 13, 14, 14, 15, 16, 17, 17, 18, 18, 19, 20, 20, 21, 21, 22,
          23, 23, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30, 31, 31, 32, 32, 33, 33, 34,
          34, 35, 35, 36, 36, 37, 37, 38, 38, 39, 39, 40, 40, 41, 41, 42, 42, 43, 43, 44, 44, 45, 45,
          46, 46, 47, 47, 48, 49, 49, 50, 51, 51, 52, 53, 53, 54, 55, 56, 57, 57, 58, 60, 61, 62, 64 },
        { 0,  4,  6,  8,  9,  10, 11, 12, 13, 14, 14, 15, 16, 17, 17, 18, 18, 19, 20, 20, 21, 21, 22,
          23, 23, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30, 31, 31, 32, 32, 33, 33, 34,
          34, 35, 35, 36, 36, 37, 37, 38, 38, 39, 39, 40, 40, 41, 41, 42, 42, 43, 43, 44, 44, 45, 45,
          46, 46, 47, 47, 48, 49, 49, 50, 51, 51, 52, 53, 53, 54, 55, 56, 57, 57, 58, 60, 61, 62, 64 },
        { 0,  4,  6,  8,  9,  10, 11, 12, 13, 14, 14, 15, 16, 17, 17, 18, 18, 19, 20, 20, 21, 21, 22,
          23, 23, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30, 31, 31, 32, 32, 33, 33, 34,
          34, 35, 35, 36, 36, 37, 37, 38, 38, 39, 39, 40, 40, 41, 41, 42, 42, 43, 43, 44, 44, 45, 45,
          46, 46, 47, 47, 48, 49, 49, 50, 51, 51, 52, 53, 53, 54, 55, 56, 57, 57, 58, 60, 61, 62, 64 },
        { 0,  4,  6,  8,  9,  10, 11, 12, 13, 14, 14, 15, 16, 17, 17, 18, 18, 19, 20, 20, 21, 21, 22,
          23, 23, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30, 31, 31, 32, 32, 33, 33, 34,
          34, 35, 35, 36, 36, 37, 37, 38, 38, 39, 39, 40, 40, 41, 41, 42, 42, 43, 43, 44, 44, 45, 45,
          46, 46, 47, 47, 48, 49, 49, 50, 51, 51, 52, 53, 53, 54, 55, 56, 57, 57, 58, 60, 61, 62, 64 },
        { 0,  4,  6,  8,  9,  10, 11, 12, 13, 14, 14, 15, 16, 17, 17, 18, 18, 19, 20, 20, 21, 21, 22,
          23, 23, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30, 31, 31, 32, 32, 33, 33, 34,
          34, 35, 35, 36, 36, 37, 37, 38, 38, 39, 39, 40, 40, 41, 41, 42, 42, 43, 43, 44, 44, 45, 45,
          46, 46, 47, 47, 48, 49, 49, 50, 51, 51, 52, 53, 53, 54, 55, 56, 57, 57, 58, 60, 61, 62, 64 },
        { 0,  4,  6,  8,  9,  10, 11, 12, 13, 14, 14, 15, 16, 17, 17, 18, 18, 19, 20, 20, 21, 21, 22,
          23, 23, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30, 31, 31, 32, 32, 33, 33, 34,
          34, 35, 35, 36, 36, 37, 37, 38, 38, 39, 39, 40, 40, 41, 41, 42, 42, 43, 43, 44, 44, 45, 45,
          46, 46, 47, 47, 48, 49, 49, 50, 51, 51, 52, 53, 53, 54, 55, 56, 57, 57, 58, 60, 61, 62, 64 },
        { 0,  4,  6,  8,  9,  10, 11, 12, 13, 14, 14, 15, 16, 17, 17, 18, 18, 19, 20, 20, 21, 21, 22,
          23, 23, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30, 31, 31, 32, 32, 33, 33, 34,
          34, 35, 35, 36, 36, 37, 37, 38, 38, 39, 39, 40, 40, 41, 41, 42, 42, 43, 43, 44, 44, 45, 45,
          46, 46, 47, 47, 48, 49, 49, 50, 51, 51, 52, 53, 53, 54, 55, 56, 57, 57, 58, 60, 61, 62, 64 },
        { 0,  4,  6,  8,  9,  10, 11, 12, 13, 14, 14, 15, 16, 17, 17, 18, 18, 19, 20, 20, 21, 21, 22,
          23, 23, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30, 31, 31, 32, 32, 33, 33, 34,
          34, 35, 35, 36, 36, 37, 37, 38, 38, 39, 39, 40, 40, 41, 41, 42, 42, 43, 43, 44, 44, 45, 45,
          46, 46, 47, 47, 48, 49, 49, 50, 51, 51, 52, 53, 53, 54, 55, 56, 57, 57, 58, 60, 61, 62, 64 },
        { 0,  4,  6,  8,  9,  10, 11, 12, 13, 14, 14, 15, 16, 17, 17, 18, 18, 19, 20, 20, 21, 21, 22,
          23, 23, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30, 31, 31, 32, 32, 33, 33, 34,
          34, 35, 35, 36, 36, 37, 37, 38, 38, 39, 39, 40, 40, 41, 41, 42, 42, 43, 43, 44, 44, 45, 45,
          46, 46, 47, 47, 48, 49, 49, 50, 51, 51, 52, 53, 53, 54, 55, 56, 57, 57, 58, 60, 61, 62, 64 },
        { 0,  4,  6,  8,  9,  10, 11, 12, 13, 14, 14, 15, 16, 17, 17, 18, 19, 19, 20, 21, 21, 22, 22, 23,
          23, 24, 24, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30, 31, 31, 32, 32, 33, 33, 33, 34, 34, 35,
          35, 36, 36, 37, 37, 38, 38, 39, 39, 40, 40, 41, 41, 42, 42, 43, 43, 44, 44, 45, 45, 46, 46, 47,
          48, 48, 49, 49, 50, 51, 51, 52, 52, 53, 54, 55, 55, 56, 57, 58, 59, 60, 61, 62, 64, 66 },
    };

Vtx gMapPlanetVTX[] = {
    VTX(30, 30, 0, 3072, 0, 255, 255, 255, 255),  VTX(-30, 30, 0, 0, 0, 255, 255, 255, 255),
    VTX(-30, 25, 0, 0, 256, 255, 255, 255, 255),  VTX(30, 25, 0, 3072, 256, 255, 255, 255, 255),
    VTX(30, 25, 0, 3072, 0, 255, 255, 255, 255),  VTX(-30, 25, 0, 0, 0, 255, 255, 255, 255),
    VTX(-30, 20, 0, 0, 256, 255, 255, 255, 255),  VTX(30, 20, 0, 3072, 256, 255, 255, 255, 255),
    VTX(30, 20, 0, 3072, 0, 255, 255, 255, 255),  VTX(-30, 20, 0, 0, 0, 255, 255, 255, 255),
    VTX(-30, 15, 0, 0, 256, 255, 255, 255, 255),  VTX(30, 15, 0, 3072, 256, 255, 255, 255, 255),
    VTX(30, 15, 0, 3072, 0, 255, 255, 255, 255),  VTX(-30, 15, 0, 0, 0, 255, 255, 255, 255),
    VTX(-30, 10, 0, 0, 256, 255, 255, 255, 255),  VTX(30, 10, 0, 3072, 256, 255, 255, 255, 255),
    VTX(30, 10, 0, 3072, 0, 255, 255, 255, 255),  VTX(-30, 10, 0, 0, 0, 255, 255, 255, 255),
    VTX(-30, 5, 0, 0, 256, 255, 255, 255, 255),   VTX(30, 5, 0, 3072, 256, 255, 255, 255, 255),
    VTX(30, 5, 0, 3072, 0, 255, 255, 255, 255),   VTX(-30, 5, 0, 0, 0, 255, 255, 255, 255),
    VTX(-30, 0, 0, 0, 256, 255, 255, 255, 255),   VTX(30, 0, 0, 3072, 256, 255, 255, 255, 255),
    VTX(30, 0, 0, 3072, 0, 255, 255, 255, 255),   VTX(-30, 0, 0, 0, 0, 255, 255, 255, 255),
    VTX(-30, -5, 0, 0, 256, 255, 255, 255, 255),  VTX(30, -5, 0, 3072, 256, 255, 255, 255, 255),
    VTX(30, -5, 0, 3072, 0, 255, 255, 255, 255),  VTX(-30, -5, 0, 0, 0, 255, 255, 255, 255),
    VTX(-30, -10, 0, 0, 256, 255, 255, 255, 255), VTX(30, -10, 0, 3072, 256, 255, 255, 255, 255),
    VTX(30, -10, 0, 3072, 0, 255, 255, 255, 255), VTX(-30, -10, 0, 0, 0, 255, 255, 255, 255),
    VTX(-30, -15, 0, 0, 256, 255, 255, 255, 255), VTX(30, -15, 0, 3072, 256, 255, 255, 255, 255),
    VTX(30, -15, 0, 3072, 0, 255, 255, 255, 255), VTX(-30, -15, 0, 0, 0, 255, 255, 255, 255),
    VTX(-30, -20, 0, 0, 256, 255, 255, 255, 255), VTX(30, -20, 0, 3072, 256, 255, 255, 255, 255),
    VTX(30, -20, 0, 3072, 0, 255, 255, 255, 255), VTX(-30, -20, 0, 0, 0, 255, 255, 255, 255),
    VTX(-30, -25, 0, 0, 256, 255, 255, 255, 255), VTX(30, -25, 0, 3072, 256, 255, 255, 255, 255),
    VTX(30, -25, 0, 3072, 0, 255, 255, 255, 255), VTX(-30, -25, 0, 0, 0, 255, 255, 255, 255),
    VTX(-30, -30, 0, 0, 256, 255, 255, 255, 255), VTX(30, -30, 0, 3072, 256, 255, 255, 255, 255),
};

Gfx gMapVenomCloudDL[] = {
    gsSPVertex(gMapPlanetVTX, 16, 0),
    gsDPLoadTextureBlock(gMapVenomCloudTex, G_IM_FMT_IA, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&gMapVenomCloudTex[96 * 8 * 1], G_IM_FMT_IA, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&gMapVenomCloudTex[96 * 8 * 2], G_IM_FMT_IA, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&gMapVenomCloudTex[96 * 8 * 3], G_IM_FMT_IA, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsSPVertex(&gMapPlanetVTX[16], 16, 0),
    gsDPLoadTextureBlock(&gMapVenomCloudTex[96 * 8 * 4], G_IM_FMT_IA, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&gMapVenomCloudTex[96 * 8 * 5], G_IM_FMT_IA, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&gMapVenomCloudTex[96 * 8 * 6], G_IM_FMT_IA, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&gMapVenomCloudTex[96 * 8 * 7], G_IM_FMT_IA, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsSPVertex(&gMapPlanetVTX[32], 16, 0),
    gsDPLoadTextureBlock(&gMapVenomCloudTex[96 * 8 * 8], G_IM_FMT_IA, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&gMapVenomCloudTex[96 * 8 * 9], G_IM_FMT_IA, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&gMapVenomCloudTex[96 * 8 * 10], G_IM_FMT_IA, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&gMapVenomCloudTex[96 * 8 * 11], G_IM_FMT_IA, G_IM_SIZ_8b, 96, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPEndDisplayList(),
};

Gfx gMapCorneriaDL[] = {
    gsDPLoadTLUT_pal256(gMapCorneriaTLUT),
    gsSPVertex(gMapPlanetVTX, 16, 0),
    gsDPLoadTextureBlock(gMapCorneriaTex, G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&gMapCorneriaTex[96 * 8 * 1], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&gMapCorneriaTex[96 * 8 * 2], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&gMapCorneriaTex[96 * 8 * 3], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsSPVertex(&gMapPlanetVTX[16], 16, 0),
    gsDPLoadTextureBlock(&gMapCorneriaTex[96 * 8 * 4], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&gMapCorneriaTex[96 * 8 * 5], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&gMapCorneriaTex[96 * 8 * 6], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&gMapCorneriaTex[96 * 8 * 7], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsSPVertex(&gMapPlanetVTX[32], 16, 0),
    gsDPLoadTextureBlock(&gMapCorneriaTex[96 * 8 * 8], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&gMapCorneriaTex[96 * 8 * 9], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&gMapCorneriaTex[96 * 8 * 10], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&gMapCorneriaTex[96 * 8 * 11], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPEndDisplayList(),
};

Gfx gMapFortunaDL[] = {
    gsDPLoadTLUT_pal256(gMapFortunaTLUT),
    gsSPVertex(gMapPlanetVTX, 16, 0),
    gsDPLoadTextureBlock(&gMapFortunaTex, G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&gMapFortunaTex[96 * 8 * 1], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&gMapFortunaTex[96 * 8 * 2], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&gMapFortunaTex[96 * 8 * 3], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsSPVertex(&gMapPlanetVTX[16], 16, 0),
    gsDPLoadTextureBlock(&gMapFortunaTex[96 * 8 * 4], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&gMapFortunaTex[96 * 8 * 5], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&gMapFortunaTex[96 * 8 * 6], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&gMapFortunaTex[96 * 8 * 7], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsSPVertex(&gMapPlanetVTX[32], 16, 0),
    gsDPLoadTextureBlock(&gMapFortunaTex[96 * 8 * 8], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&gMapFortunaTex[96 * 8 * 9], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&gMapFortunaTex[96 * 8 * 10], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&gMapFortunaTex[96 * 8 * 11], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPEndDisplayList(),
};

Gfx gMapAquasDL[] = {
    gsDPLoadTLUT_pal256(gMapAquasTLUT),
    gsSPVertex(gMapPlanetVTX, 16, 0),
    gsDPLoadTextureBlock(gMapAquasTex, G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&gMapAquasTex[96 * 8 * 1], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&gMapAquasTex[96 * 8 * 2], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&gMapAquasTex[96 * 8 * 3], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsSPVertex(&gMapPlanetVTX[16], 16, 0),
    gsDPLoadTextureBlock(&gMapAquasTex[96 * 8 * 4], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&gMapAquasTex[96 * 8 * 5], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&gMapAquasTex[96 * 8 * 6], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&gMapAquasTex[96 * 8 * 7], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsSPVertex(&gMapPlanetVTX[32], 16, 0),
    gsDPLoadTextureBlock(&gMapAquasTex[96 * 8 * 8], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&gMapAquasTex[96 * 8 * 9], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&gMapAquasTex[96 * 8 * 10], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&gMapAquasTex[96 * 8 * 11], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPEndDisplayList(),
};

Gfx gMapVenomDL[] = {
    gsDPLoadTLUT_pal256(gMapVenomTLUT),
    gsSPVertex(gMapPlanetVTX, 16, 0),
    gsDPLoadTextureBlock(gMapVenomTex, G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&gMapVenomTex[96 * 8 * 1], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&gMapVenomTex[96 * 8 * 2], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&gMapVenomTex[96 * 8 * 3], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsSPVertex(&gMapPlanetVTX[16], 16, 0),
    gsDPLoadTextureBlock(&gMapVenomTex[96 * 8 * 4], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&gMapVenomTex[96 * 8 * 5], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&gMapVenomTex[96 * 8 * 6], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&gMapVenomTex[96 * 8 * 7], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsSPVertex(&gMapPlanetVTX[32], 16, 0),
    gsDPLoadTextureBlock(&gMapVenomTex[96 * 8 * 8], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&gMapVenomTex[96 * 8 * 9], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&gMapVenomTex[96 * 8 * 10], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&gMapVenomTex[96 * 8 * 11], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPEndDisplayList(),
};

Gfx gMapTitaniaDL[] = {
    gsDPLoadTLUT_pal256(gMapTitaniaTLUT),
    gsSPVertex(gMapPlanetVTX, 16, 0),
    gsDPLoadTextureBlock(gMapTitaniaTex, G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&gMapTitaniaTex[96 * 8 * 1], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&gMapTitaniaTex[96 * 8 * 2], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&gMapTitaniaTex[96 * 8 * 3], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsSPVertex(&gMapPlanetVTX[16], 16, 0),
    gsDPLoadTextureBlock(&gMapTitaniaTex[96 * 8 * 4], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&gMapTitaniaTex[96 * 8 * 5], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&gMapTitaniaTex[96 * 8 * 6], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&gMapTitaniaTex[96 * 8 * 7], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsSPVertex(&gMapPlanetVTX[32], 16, 0),
    gsDPLoadTextureBlock(&gMapTitaniaTex[96 * 8 * 8], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&gMapTitaniaTex[96 * 8 * 9], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&gMapTitaniaTex[96 * 8 * 10], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&gMapTitaniaTex[96 * 8 * 11], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPEndDisplayList(),
};

Gfx gMapKatinaDL[] = {
    gsDPLoadTLUT_pal256(gMapKatinaTLUT),
    gsSPVertex(gMapPlanetVTX, 16, 0),
    gsDPLoadTextureBlock(gMapKatinaTex, G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&gMapKatinaTex[96 * 8 * 1], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&gMapKatinaTex[96 * 8 * 2], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&gMapKatinaTex[96 * 8 * 3], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsSPVertex(&gMapPlanetVTX[16], 16, 0),
    gsDPLoadTextureBlock(&gMapKatinaTex[96 * 8 * 4], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&gMapKatinaTex[96 * 8 * 5], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&gMapKatinaTex[96 * 8 * 6], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&gMapKatinaTex[96 * 8 * 7], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsSPVertex(&gMapPlanetVTX[32], 16, 0),
    gsDPLoadTextureBlock(&gMapKatinaTex[96 * 8 * 8], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&gMapKatinaTex[96 * 8 * 9], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&gMapKatinaTex[96 * 8 * 10], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&gMapKatinaTex[96 * 8 * 11], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPEndDisplayList(),
};

Gfx gMapMacbethDL[] = {
    gsDPLoadTLUT_pal256(gMapMacbethTLUT),
    gsSPVertex(gMapPlanetVTX, 16, 0),
    gsDPLoadTextureBlock(gMapMacbethTex, G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&gMapMacbethTex[96 * 8 * 1], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&gMapMacbethTex[96 * 8 * 2], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&gMapMacbethTex[96 * 8 * 3], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsSPVertex(&gMapPlanetVTX[16], 16, 0),
    gsDPLoadTextureBlock(&gMapMacbethTex[96 * 8 * 4], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&gMapMacbethTex[96 * 8 * 5], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&gMapMacbethTex[96 * 8 * 6], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&gMapMacbethTex[96 * 8 * 7], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsSPVertex(&gMapPlanetVTX[32], 16, 0),
    gsDPLoadTextureBlock(&gMapMacbethTex[96 * 8 * 8], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&gMapMacbethTex[96 * 8 * 9], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&gMapMacbethTex[96 * 8 * 10], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&gMapMacbethTex[96 * 8 * 11], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPEndDisplayList(),
};

Gfx gMapZonessDL[] = {
    gsDPLoadTLUT_pal256(gMapZonessTLUT),
    gsSPVertex(gMapPlanetVTX, 16, 0),
    gsDPLoadTextureBlock(gMapZonessTex, G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(gMapZonessTex + (96 * 8 * 1), G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(gMapZonessTex + (96 * 8 * 2), G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(gMapZonessTex + (96 * 8 * 3), G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsSPVertex(&gMapPlanetVTX[16], 16, 0),
    gsDPLoadTextureBlock(gMapZonessTex + (96 * 8 * 4), G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(gMapZonessTex + (96 * 8 * 5), G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(gMapZonessTex + (96 * 8 * 6), G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(gMapZonessTex + (96 * 8 * 7), G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsSPVertex(&gMapPlanetVTX[32], 16, 0),
    gsDPLoadTextureBlock(gMapZonessTex + (96 * 8 * 8), G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(gMapZonessTex + (96 * 8 * 9), G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(gMapZonessTex + (96 * 8 * 10), G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(gMapZonessTex + (96 * 8 * 11), G_IM_FMT_CI, G_IM_SIZ_8b, 96, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPEndDisplayList(),
};

// BSS
u8* gBSSMapPlanetTextures[9] = {
    gMapKatinaTex, gMapMacbethTex, gMapZonessTex, gMapCorneriaTex,   gMapTitaniaTex,
    gMapAquasTex,  gMapFortunaTex, gMapVenomTex,  gMapVenomCloudTex,
};

// AST_MAP
u8* gAssetMapPlanetTextures[9] = {
    aMapKatinaTex, aMapMacbethTex, aMapZonessTex, aMapCorneriaTex,   aMapTitaniaTex,
    aMapAquasTex,  aMapFortunaTex, aMapVenomTex,  aMapVenomCloudTex,
};

Gfx* sMapPlanets[PLANET_MAX] = {
    aMapMeteorDL,  aMapArea6DL,  aMapBolseDL,   aMapSectorZDL, aMapSectorXDL,
    aMapSectorYDL, gMapKatinaDL, gMapMacbethDL, gMapZonessDL,  gMapCorneriaDL,
    gMapTitaniaDL, gMapAquasDL,  gMapFortunaDL, gMapVenomDL,   aMapSolarDL,
};

void Map_8019E800(void);
void Map_Setup(void);
void Map_Setup_Play(void);
void Map_Setup_GameOver(void);
void Map_Setup_Menu(void);
void Map_TeamStatus_Refill(void);
void Map_Level_CamSetup(void);
void Map_PathStatus_Setup(void);
void Map_CurrentPlanet_SetAlpha(void);
void Map_PlanetExplosions_Setup(void);
bool Map_PlanetSaveSlot_Setup(LevelId, PlanetSaveSlotTypes);
void Map_Update(void);
s32 Map_801A05B4(void);
void Map_Starfield_Setup(void);
void Map_Prologue_Update(void);
void Map_Prologue_Draw(void);
void Map_LylatCard_Update(void);
void Map_PrologueArwing_Draw(void);
void Map_LylatCard_Draw(void);
void Map_ZoomPlanet_Update(void);
bool Map_GralPepper_Talk(void);
f32 Map_GetPlanetCamZDist(PlanetId);
void Map_801A2674(void);
void Map_801A281C(void);
void Map_ZoomPlanetPath_Update(void);
void Map_801A2EB8(void);
void Map_801A3440(f32);
void Map_801A3550(Vec3f*, Vec3f*, Vec3f*, f32);
void Map_GameOver_Update(void);
void Map_GameOver_3DFont(void);
void Map_801A4394(void);
void Map_GameOver_Draw(void);
void Map_801A48C0(f32 speed);
void Map_801A4A38(f32 arg0);
void Map_PathChange_Update(void);
void Map_PathChange_UpdateEntry(u32);
void Map_PathChange_Input(void);
void Map_GoToGameOver(void);
void Map_RetryCourse(void);
void Map_ChangePath(void);
void Map_PathChange_DrawOptions(void);
void Map_RestartLevelLifeDown_Draw(void);
bool Map_Input_CursorY(void);
void Map_LevelStart_Update(void);
void Map_CurrentLevel_Setup(void);
void Map_LevelStart_AudioSpecSetup(LevelId level);
bool Map_LevelPlayedStatus_Check(PlanetId planet);
s32 Map_GetPathId(PlanetId start, PlanetId end);
void Map_PlayLevel(void);
void Map_PositionPlanets(void);
void Map_PlanetOrderZpos(void);
void Map_Fade_Update(void);
void Map_Planet_Draw(PlanetId);
s32 Map_CheckPlanetMedal(PlanetId planetId);
void Map_PlanetAnim2(PlanetId planetId);
void Map_PlanetAnim(PlanetId planetId);
void Map_SolarRays_Draw(PlanetId);
void Map_VenomCloud2_Draw(PlanetId planetId);
void Map_PlanetShadow_Draw(PlanetId planetId);
void Map_Titania_DrawRings1(PlanetId planetId);
void Map_Titania_DrawRings2(PlanetId planetId);
void Map_VenomCloud_Draw(f32* zAngle, f32 next, f32 scale);
void Map_PlanetCleared2_Draw(PlanetId planetId);
void Map_PlanetCleared_Draw(PlanetId planetId);
void Map_PositionCursor(void);
void Map_TotalHits_Draw(void);
void Map_Idle_Update(void);
void Map_SetCamRot(f32, f32, f32, f32*, f32*, f32*, f32, f32, f32);
PlanetId Map_GetPlanetId(LevelId level);
void Map_PlanetMedal_Draw(PlanetId planetId);
void Map_CorneriaExplosion_Draw(void);
void Map_PlanetExplosions_Draw(PlanetId, PlanetExplosions);
void Map_Cursor_draw(void);
void Map_MeteoMeteors_Draw(void);
void Map_Area6Ships_Draw(void);
void Map_Wipe_Draw(void);
void Map_TitleCards_Draw(void);
void Map_801A9A8C(void);
void Map_801A9DE8(void);
void Map_PathLineBox_Draw(s32);
void Map_PathInfo_Draw(s32, f32, f32, s32);
void Map_PathPlanet_Draw(s32, f32, f32, PlanetId);
void Map_PathPlanetMedal_Draw(f32 x, f32 y, f32 z);
void Map_BriefingRadio_Setup(void);
void Map_BriefingRadio_Update(void);
void Map_BriefingRadio_Draw(s32);
void Map_TeamDownWrench_Draw(s32 teamIdx, s32 alpha);
void Map_GralPepperFace_Draw(void);
void Map_Path_Draw(s32);
void Map_Arwing_Draw(s32 index);
void Map_PathLine_Draw(PathType);
void Map_PathLines_Draw(s32);
void Map_PathLinePos(s32 index, Vec3f* src, Vec3f* dest);
void Map_CamMatrixRot(void);

void Map_8019E800(void) {
    Memory_FreeAll();
    Play_GenerateStarfield();
    gStarCount = 0;
    gNextGameState = GSTATE_MAP;
    gLastGameState = GSTATE_GAME_OVER;
    D_ctx_80177868 = 2;
    gDrawMode = DRAW_NONE;
}

void Map_GameOver(void) {
    switch (D_ctx_80177868) {
        case 0:
            if (gNextGameStateTimer == 0) {
                D_ctx_80177868 = 1;
            }
            break;

        case 2:
            break;

        case 1:
            Map_8019E800();
            break;
    }
}

void Map_8019E8C8(void) {
}

void Map_Main(void) {
    if (sMapTimer1 > 0) {
        sMapTimer1--;
    }
    if (sMapTimer2 > 0) {
        sMapTimer2--;
    }
    if (sMapTimer3 > 0) {
        sMapTimer3--;
    }

    switch (gMapState) {
        case 0:
            if (gNextGameStateTimer == 0) {
                gMapState = 1;
            }
            break;

        case 1:
            gDrawMode = DRAW_NONE;
            Map_Setup();
            break;

        case 2:
            gDrawMode = DRAW_MAP;
            Map_Update();
            break;
    }
}

void Map_Setup(void) {
    s32 i;
    s32 j;

    AUDIO_SET_SPEC(SFXCHAN_1, AUDIOSPEC_24);

    gVIsPerFrame = 2;
    gGameFrameCount = 0;

    Title_GetRankTotalHits();

    D_menu_801CD83C = Map_801A05B4();

    D_menu_801CD980 = false;
    D_menu_801CD984 = 0;
    D_menu_801CD98C = 0;
    D_menu_801CD990 = 0;
    D_menu_801CD994 = 0;
    sRestartLevelStates = 0;

    sPlanetExplosions[EXPLOSIONS_CORNERIA] = false;
    sPlanetExplosions[EXPLOSIONS_KATINA] = false;
    sPlanetExplosions[EXPLOSIONS_SECTOR_Y] = false;

    for (i = 0; i < 10; i++) {
        D_menu_801CEB58[1][i] = 0;
        D_menu_801CEB58[2][i] = 0;
        D_menu_801CEBD0[1][i] = 255;
        D_menu_801CEBD0[2][i] = 255;
        D_menu_801CEC48[1][i] = 0.0f;
        D_menu_801CEC48[2][i] = 0.0f;
        D_menu_801CECC0[1][i] = 0.5f + RAND_FLOAT(0.3f);
        D_menu_801CECC0[2][i] = 0.5f + RAND_FLOAT(0.3f);
        D_menu_801CEE28[1][i] = 1 + RAND_INT(5.0f);
        D_menu_801CEE28[2][i] = 1 + RAND_INT(5.0f);
        D_menu_801CED38[1][i] = 50.0f + RAND_INT(30.0f);
        D_menu_801CED38[2][i] = 110.0f + RAND_INT(30.0f);
        D_menu_801CEDB0[1][i] = -10.0f + RAND_FLOAT(-60.0f);
        D_menu_801CEDB0[2][i] = -10.0f + RAND_FLOAT(-60.0f);
    }

    D_menu_801CD978 = 0;
    D_menu_801CD97C = 0;
    D_menu_801CF010 = 0;
    D_menu_801CF014 = 0;

    for (j = 0; j < 15; j++) {
        D_menu_801CD900[j] = 0;
        D_menu_801CEAB8[j] = 0.0f;
        D_menu_801CEAF8[j] = -90.0f;
    }

    sMapCamUpX = 0.0f;
    sMapCamUpY = 1.0f;
    sMapCamUpZ = 0.0f;
    sMapCamAtX = -150.55215f;
    sMapCamAtY = -489.68f;
    sMapCamAtZ = 0.0f;
    D_menu_801CDA0C = -42.750008f;
    D_menu_801CDA10 = -9.849999f;
    D_menu_801CDA14 = 3375.0f; // 15^3
    D_menu_801CDA18 = 0.0f;
    D_menu_801CDA1C = 0.0f;

    Map_SetCamRot(sMapCamAtX, sMapCamAtY, sMapCamAtZ, &sMapCamEyeX, &sMapCamEyeY, &sMapCamEyeZ, D_menu_801CDA14,
                  D_menu_801CDA0C + D_menu_801CDA18, D_menu_801CDA10 + D_menu_801CDA1C);

    for (i = 0; i < 15; i++) {
        D_menu_801CD8A0[i] = i;
    }

    D_menu_801CD960 = 0;

    gFillScreenAlpha = 255;
    gFillScreenRed = 0;
    gFillScreenGreen = 0;
    gFillScreenBlue = 0;
    gPathProgress = 0.0f;

    D_menu_801CF018 = 0;

    gBgColor = 0;

    D_menu_801CEA58 = 0.0f;
    D_menu_801CEA5C = 0.0f;
    D_menu_801CEA60 = 0.0f;

    Map_Starfield_Setup();

    sLevelStartState = 0;
    sWipeHeight = 0;
    sMapTimer1 = 0;
    sMapTimer2 = 0;
    sMapTimer3 = 0;
    D_menu_801CD964 = 0;
    D_menu_801CD968 = 0;
    D_menu_801CD96C = false;
    sMapPlanetCardAlpha = 0.0f;
    sMapPlanetCardAlphaScale = 0.002f;

    AUDIO_PLAY_BGM(NA_BGM_MAP);

    D_menu_801CEFC4 = 0;
    D_menu_801CEFC8 = 0;
    D_menu_801CEFD0 = false;
    D_menu_801CD974 = 0;

    for (i = 0; i < ARRAY_COUNT(sPaths); i++) {
        sUnusedPathIdx[i] = i;
        sPaths[i].unk_14 = 0;
    }

    Map_PositionPlanets();

    switch (gLastGameState) {
        default:
        case GSTATE_NONE:
            Map_Setup_Menu();
            break;

        case GSTATE_PLAY:
            Map_Setup_Play();
            break;

        case GSTATE_GAME_OVER:
            Map_Setup_GameOver();
            break;
    }

    Map_PositionCursor();

    for (i = 0; i < 96 * 96; i++) {
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

    D_menu_801CD810 = 0;

    gMapState = 2;

    sMapSubState = 0;
    D_menu_801CEEC4 = 0;
    D_menu_801CEEC8 = 5;
    D_menu_801CEFF4 = 255.0f;
    D_menu_801CEFF8 = 255.0f;
    D_menu_801CEEBC = 0.0f;
    D_menu_801CEEC0 = 0.0f;
    D_menu_801CEEA0 = 0;
    D_menu_801CEEA4 = 0;
    D_menu_801CEEA8 = 255;
    D_menu_801CEEAC = 255;
    D_menu_801CEB34 = -1;
}

void Map_Setup_Play(void) {
    s32 i;

    D_menu_801CD974 = 1;

    if (gLifeCount[gPlayerNum] > 99) {
        gLifeCount[gPlayerNum] = 99;
    }

    for (i = 0; i < TEAM_ID_MAX; i++) {
        gPrevPlanetTeamShields[i] = gTeamShields[i];
        gPrevPlanetSavedTeamShields[i] = gSavedTeamShields[i];
        gSavedTeamShields[i] = gTeamShields[i];
    }

    for (i = TEAM_ID_FALCO; i <= TEAM_ID_PEPPY; i++) {
        if (gPrevPlanetTeamShields[i] == 0) {
            gPrevPlanetTeamShields[i] = 255;
        }
    }

    sPrevMissionStatus = gMissionStatus;

    sCurrentPlanetId = Map_GetPlanetId(gCurrentLevel);

    sPrevPlanetId = sCurrentPlanetId;

    D_menu_801CD980 = Map_PlanetSaveSlot_Setup(gCurrentLevel, SAVETYPE_PLAYED);

    Map_PlanetSaveSlot_Setup(gCurrentLevel, SAVETYPE_CLEAR);

    if (gLeveLClearStatus[gCurrentLevel] == 2) {
        D_menu_801CD98C = 1;
        gMissionMedal[gMissionNumber] = 1;
        Map_PlanetSaveSlot_Setup(gCurrentLevel, SAVETYPE_MEDAL);
    }

    Save_Write();

    Map_Level_CamSetup();

    Map_PathStatus_Setup();

    Map_CurrentPlanet_SetAlpha();

    switch (sPrevMissionStatus) {
        case MISSION_COMPLETE:
            sNextPlanetId = sPlanets[sCurrentPlanetId].dest1;
            break;

        case MISSION_ACCOMPLISHED:
            sNextPlanetId = sPlanets[sCurrentPlanetId].dest2;
            break;

        case MISSION_WARP:
            sNextPlanetId = sPlanets[sCurrentPlanetId].warp;
            break;
    }

    gMissionNumber++;

    Map_PlanetExplosions_Setup();

    D_menu_801CEFC4 = 0;
    D_menu_801CEFD0 = false;
    D_menu_801CEFE0 = 32.0f;

    D_menu_801CEFE8[0] = 255.0f;
    D_menu_801CEFE8[1] = 255.0f;
    D_menu_801CEFE8[2] = 255.0f;

    D_menu_801CEFD8 = 0;

    if (sPrevMissionStatus != MISSION_COMPLETE) {
        D_menu_801CEFD8 = 1;
    }

    gHitCount = 0;

    D_menu_801CD94C = 0;
    sMapState = MAP_ZOOM_PLANET_PATH;
}

void Map_Setup_GameOver(void) {
    s32 i;

    gTotalHits += gHitCount;
    gLifeCount[gPlayerNum] = 0;

    D_menu_801CD974 = 1;
    sCurrentPlanetId = Map_GetPlanetId(gCurrentLevel);

    gMissionHitCount[gMissionNumber] = gHitCount;

    Map_TeamStatus_Refill();
    Map_PlanetSaveSlot_Setup(gCurrentLevel, SAVETYPE_PLAYED);
    Save_Write();
    Map_PathStatus_Setup();

    for (i = 0; i < 7; i++) {
        D_menu_801CD8E0[i] = 0;
    }

    if (gMissionNumber != 0) {
        for (i = 0; i < gMissionNumber; i++) {
            D_menu_801CD8E0[i] = Map_GetPathId(gMissionPlanet[i], gMissionPlanet[i + 1]);
        }
    }

    for (i = 0; i < 24; i++) {
        gPlanetPathStatus[i] = 0;
    }

    for (i = 0; i < 15; i++) {
        sPlanets[i].alpha = 0;
    }

    Map_PlanetExplosions_Setup();

    D_menu_801CD9AC = 0;

    AUDIO_SET_SPEC(SFXCHAN_0, AUDIOSPEC_25);

    sMapSubState = 0;
    D_menu_801CD94C = 0;
    sMapState = MAP_GAME_OVER;
}

void Map_Setup_Menu(void) {
    s32 i;
    s32 path1;
    s32 path2;

    gTotalHits = 0;
    gHitCount = 0;

    gTeamShields[TEAM_ID_FALCO] = 255;
    gTeamShields[TEAM_ID_SLIPPY] = 255;
    gTeamShields[TEAM_ID_PEPPY] = 255;
    gSavedTeamShields[TEAM_ID_FALCO] = 255;
    gSavedTeamShields[TEAM_ID_SLIPPY] = 255;
    gSavedTeamShields[TEAM_ID_PEPPY] = 255;
    gPrevPlanetTeamShields[TEAM_ID_FALCO] = 255;
    gPrevPlanetTeamShields[TEAM_ID_SLIPPY] = 255;
    gPrevPlanetTeamShields[TEAM_ID_PEPPY] = 255;
    D_ctx_80177C58[TEAM_ID_FALCO] = 255;
    D_ctx_80177C58[TEAM_ID_SLIPPY] = 255;
    D_ctx_80177C58[TEAM_ID_PEPPY] = 255;

    sPrevPlanetId = PLANET_NONE;

    for (i = 0; i < PLANET_MAX; i++) {
        sPlanets[i].alpha = 0;
    }

    D_menu_801CD970 = 0;
    //! @bug gPlanetPathStatus is 2 shorter than sPaths
    for (i = 0; i < ARRAY_COUNT(sPaths); i++) {
        gPlanetPathStatus[i] = 0;
        gTexturedLines[i].zScale = 0.0f;
    }

    for (i = 0; i < ARRAY_COUNT(gMissionMedal); i++) {
        gMissionMedal[i] = 0;
        gMissionHitCount[i] = 0;
        gMissionTeamStatus[i] = 0x00FFFFFF;
    }

    gMissionPlanet[0] = PLANET_CORNERIA;
    gMissionPlanet[1] = PLANET_NONE;
    gMissionPlanet[2] = PLANET_NONE;
    gMissionPlanet[3] = PLANET_NONE;
    gMissionPlanet[4] = PLANET_NONE;
    gMissionPlanet[5] = PLANET_NONE;
    gMissionPlanet[6] = PLANET_VENOM;

    for (i = 0; i < ARRAY_COUNT(sPaths); i++) {
        sPaths[i].alpha = 255;
    }

    gMissionNumber = 0;
    gCurrentLevel = LEVEL_CORNERIA;

    sCurrentPlanetId = PLANET_CORNERIA;
    D_menu_801CEA9C = 0.0f;
    D_menu_801CD9B0 = 0.002f;
    D_menu_801CD9B4 = 0.01f;
    sMapState = MAP_PROLOGUE;

    path1 = Map_GetPathId(sCurrentPlanetId, sPlanets[sCurrentPlanetId].dest1);
    path2 = Map_GetPathId(sCurrentPlanetId, sPlanets[sCurrentPlanetId].dest2);
    gPlanetPathStatus[path1] = 1;
    gPlanetPathStatus[path2] = 1;
}

void Map_PathStatus_Setup(void) {
    s32 i;

    D_menu_801CD970 = 0;

    //! @bug gPlanetPathStatus is 2 shorter than sPaths
    for (i = 0; i < ARRAY_COUNT(sPaths); i++) {
        if ((gPlanetPathStatus[i] == 4) || (gPlanetPathStatus[i] == 5) || (gPlanetPathStatus[i] == 1) ||
            (gPlanetPathStatus[i] == 11)) {
            gPlanetPathStatus[i] = 0;
        }

        if (gPlanetPathStatus[i] == 6) {
            sPaths[i].unk_14 = 5;
        }

        sPaths[i].alpha = 0;
        gTexturedLines[i].zScale = 0.0f;
    }
}

void Map_TeamStatus_Refill(void) {
    s32 i;
    s32 mask = 0x00FF0000;

    for (i = 0; i < 3; i++) {
        if (gTeamShields[3 - i] <= 0) {
            gMissionTeamStatus[gMissionNumber] ^= mask;
        } else {
            gMissionTeamStatus[gMissionNumber] |= mask;
        }
        mask >>= 8;
    }
}

void Map_Level_CamSetup(void) {
    sCurrentPlanetCamZDist = Map_GetPlanetCamZDist(sCurrentPlanetId);

    sMapCamEyeX = sMapCamAtX = sPlanets[sCurrentPlanetId].pos.x;
    sMapCamEyeY = sMapCamAtY = sPlanets[sCurrentPlanetId].pos.y;
    sMapCamAtZ = sPlanets[sCurrentPlanetId].pos.z;
    sMapCamEyeZ = sPlanets[sCurrentPlanetId].pos.z + sCurrentPlanetCamZDist;
}

void Map_CurrentPlanet_SetAlpha(void) {
    PlanetId planetId;

    for (planetId = 0; planetId < PLANET_MAX; planetId++) {
        if (planetId == sCurrentPlanetId) {
            if ((planetId == PLANET_SECTOR_Z) || (planetId == PLANET_SECTOR_X) || (planetId == PLANET_SECTOR_Y)) {
                sPlanets[planetId].alpha = 144;
            } else {
                sPlanets[planetId].alpha = 255;
            }
        } else {
            sPlanets[planetId].alpha = 0;
        }
    }
}

// For Katina and Sector Y
void Map_PlanetExplosions_Setup(void) {
    s32 i;

    if (gMissionNumber != PLANET_METEO) {
        sPlanetExplosions[EXPLOSIONS_KATINA] = true;
        sPlanetExplosions[EXPLOSIONS_SECTOR_Y] = true;
    }

    for (i = 0; i < ARRAY_COUNT(gMissionPlanet); i++) {
        if (gMissionPlanet[i] == PLANET_KATINA) {
            sPlanetExplosions[EXPLOSIONS_KATINA] = false;
        }
        if (gMissionPlanet[i] == PLANET_SECTOR_Y) {
            sPlanetExplosions[EXPLOSIONS_SECTOR_Y] = false;
        }
    }
}

bool Map_PlanetSaveSlot_Setup(LevelId levelId, PlanetSaveSlotTypes type) {
    s32 ret;
    s32 planetSaveSlot;

#ifdef AVOID_UB
    planetSaveSlot = PLANET_CORNERIA;
#endif

    switch (levelId) {
        case LEVEL_METEO:
            planetSaveSlot = PLANET_METEO;
            break;

        case LEVEL_AREA_6:
            planetSaveSlot = PLANET_AREA_6;
            break;

        case LEVEL_BOLSE:
            planetSaveSlot = PLANET_BOLSE;
            break;

        case LEVEL_SECTOR_Z:
            planetSaveSlot = PLANET_SECTOR_Z;
            break;

        case LEVEL_SECTOR_X:
            planetSaveSlot = PLANET_SECTOR_X;
            break;

        case LEVEL_SECTOR_Y:
            planetSaveSlot = PLANET_SECTOR_Y;
            break;

        case LEVEL_KATINA:
            planetSaveSlot = PLANET_KATINA;
            break;

        case LEVEL_MACBETH:
            planetSaveSlot = PLANET_MACBETH;
            break;

        case LEVEL_ZONESS:
            planetSaveSlot = PLANET_ZONESS;
            break;

        case LEVEL_CORNERIA:
            planetSaveSlot = PLANET_CORNERIA;
            break;

        case LEVEL_TITANIA:
            planetSaveSlot = PLANET_TITANIA;
            break;

        case LEVEL_AQUAS:
            planetSaveSlot = PLANET_AQUAS;
            break;

        case LEVEL_FORTUNA:
            planetSaveSlot = PLANET_FORTUNA;
            break;

        case LEVEL_SOLAR:
            planetSaveSlot = SAVE_SLOT_SOLAR;
            break;

        case LEVEL_VENOM_1:
            planetSaveSlot = SAVE_SLOT_VENOM_1;
            break;

        case LEVEL_VENOM_2:
            planetSaveSlot = SAVE_SLOT_VENOM_2;
            break;

        case LEVEL_VENOM_ANDROSS:
            if (gLevelPhase == 0) {
                planetSaveSlot = SAVE_SLOT_VENOM_1;
            } else {
                planetSaveSlot = SAVE_SLOT_VENOM_2;
            }
            break;
    }

    ret = false;

    switch (type) {
        case SAVETYPE_PLAYED:
            if (!(gSaveFile.save.data.planet[planetSaveSlot].played & 1)) {
                gSaveFile.save.data.planet[planetSaveSlot].played = 1;
                ret = true;
            }
            break;

        case SAVETYPE_MEDAL:
            if (gExpertMode) {
                if (!(gSaveFile.save.data.planet[planetSaveSlot].expertMedal & 1)) {
                    gSaveFile.save.data.planet[planetSaveSlot].expertMedal = 1;
                    ret = true;
                }
            } else {
                if (!(gSaveFile.save.data.planet[planetSaveSlot].normalMedal & 1)) {
                    gSaveFile.save.data.planet[planetSaveSlot].normalMedal = 1;
                    ret = true;
                }
            }
            break;

        case SAVETYPE_CLEAR:
            if (gExpertMode) {
                if (!(gSaveFile.save.data.planet[planetSaveSlot].expertClear & 1)) {
                    gSaveFile.save.data.planet[planetSaveSlot].expertClear = 1;
                    ret = true;
                }
            } else {
                if (!(gSaveFile.save.data.planet[planetSaveSlot].normalClear & 1)) {
                    gSaveFile.save.data.planet[planetSaveSlot].normalClear = 1;
                    ret = true;
                }
            }
            break;
    }

    return ret;
}

void Map_Update(void) {
    Map_PositionPlanets();
    Map_PlanetOrderZpos();
    Map_Fade_Update();

    switch (sMapState) {
        case MAP_PROLOGUE:
            Map_Prologue_Update();
            gStarfieldScrollX += 0.09f;
            break;

        case MAP_LYLAT_CARD:
            Map_LylatCard_Update();
            D_menu_801CDA1C += 0.03f;
            break;

        case MAP_IDLE:
            Map_Idle_Update();
            D_menu_801CDA1C += 0.03f;
            break;

        case MAP_ZOOM_PLANET:
            Map_ZoomPlanet_Update();
            break;

        case MAP_LEVEL_START:
            Map_LevelStart_Update();
            break;

        case MAP_ZOOM_PLANET_PATH:
            Map_ZoomPlanetPath_Update();
            break;

        case MAP_PATH_CHANGE:
            Map_PathChange_Update();
            break;

        case MAP_GAME_OVER:
            Map_GameOver_Update();
            break;

        default:
            break;
    }

    if ((sMapState == MAP_PROLOGUE) || (sMapState == MAP_LYLAT_CARD) || (sMapState == MAP_GAME_OVER) ||
        (sMapState == MAP_IDLE)) {
        Map_SetCamRot(sMapCamAtX, sMapCamAtY, sMapCamAtZ, &sMapCamEyeX, &sMapCamEyeY, &sMapCamEyeZ, D_menu_801CDA14,
                      D_menu_801CDA0C + D_menu_801CDA18, D_menu_801CDA10 + D_menu_801CDA1C);
        Camera_SetStarfieldPos(sMapCamEyeX, sMapCamEyeY, sMapCamEyeZ, sMapCamAtX, sMapCamAtY, sMapCamAtZ);
    }
    gGameFrameCount++;

    if (CVarGetInteger("gLevelSelector", 0)) {
        Map_LevelSelect();
    }
}

void Map_Draw(void) {
    s32 i;
    s32* ptr;

    Matrix_Push(&gGfxMatrix);
    Matrix_LookAt(gGfxMatrix, sMapCamEyeX, sMapCamEyeY, sMapCamEyeZ, sMapCamAtX, sMapCamAtY, sMapCamAtZ, sMapCamUpX,
                  sMapCamUpY, sMapCamUpZ, MTXF_APPLY);
    Matrix_Translate(gGfxMatrix, D_menu_801CEA58, D_menu_801CEA5C, D_menu_801CEA60, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);

    if (D_menu_801CD974 && (sMapState != MAP_PROLOGUE)) {
        for (i = 0; i < 24; i++) {
            if (gPlanetPathStatus[i] == 0) {
                continue;
            }
            if (sPaths[i].alpha == 0) {
                continue;
            }

            Map_PathLines_Draw(i);

            if (sPaths[i].unk_14 != 0) {
                Map_Path_Draw(i);
            }

            TexturedLine_DrawPath(i);
        }
    }

    Map_Cursor_draw();

    Map_MeteoMeteors_Draw();

    Map_Area6Ships_Draw();

    for (ptr = D_menu_801CD8A0, i = 0; i < 15; i++, ptr++) {
        Map_Planet_Draw(*ptr);
    }

    Map_CorneriaExplosion_Draw();

    Matrix_Pop(&gGfxMatrix);

    if (D_menu_801CD96C) {
        Map_GralPepperFace_Draw();
    }

    Map_BriefingRadio_Update();

    if (D_menu_801CEFC4) {
        Map_PathChange_DrawOptions();
    }

    if (D_menu_801CD964) {
        Map_TitleCards_Draw();
    }

    Map_Wipe_Draw();

    if (D_menu_801CD968) {
        Map_801A9A8C();
    }

    Map_801A9DE8();

    Map_RestartLevelLifeDown_Draw();

    if ((sMapState == MAP_GAME_OVER) && (sMapSubState == 1)) {
        Map_GameOver_Draw();
    }
    if (sMapState == MAP_PROLOGUE) {
        Map_Prologue_Draw();
    }
    if (sMapState == MAP_LYLAT_CARD) {
        Map_LylatCard_Draw();
    }

    if (D_menu_801CEEC8 == 0) {
        Map_Texture_Sphere(gBSSMapPlanetTextures[8], SEGMENTED_TO_VIRTUAL(gAssetMapPlanetTextures[8]),
                           &D_menu_801CD818[8]);
        D_menu_801CEEC8 = 5;
    } else {
        D_menu_801CEEC8--;
    }

    Map_Texture_Sphere(gBSSMapPlanetTextures[D_menu_801CEEC4 * 2],
                       SEGMENTED_TO_VIRTUAL(gAssetMapPlanetTextures[D_menu_801CEEC4 * 2]),
                       &D_menu_801CD818[D_menu_801CEEC4 * 2]);
    Map_Texture_Sphere(gBSSMapPlanetTextures[(D_menu_801CEEC4 * 2) + 1],
                       SEGMENTED_TO_VIRTUAL(gAssetMapPlanetTextures[(D_menu_801CEEC4 * 2) + 1]),
                       &D_menu_801CD818[(D_menu_801CEEC4 * 2) + 1]);

    D_menu_801CEEC4++;
    if (D_menu_801CEEC4 > 3) {
        D_menu_801CEEC4 = 0;
    }

    Lib_Texture_Mottle(aMapVenomCloudEffectTex, D_MAP_6048F80, 5);
}

s32 Map_801A05B4(void) {
    s32 i;
    s32 j;
    s32 sp30[10];
    s32 ret;
    s32 var_a3;
    s32 temp_a0;

    for (i = 0; i < RANKING_MAX; i++) {
        sp30[i] = 0;
    }

    for (i = 0; i < RANKING_MAX; i++) {
        temp_a0 = gSaveFile.save.data.rankingRoute[i];
        for (j = 0; j < temp_a0; j++) {
            var_a3 = gSaveFile.save.data.stats[i][j].hitCount;
            if (gSaveFile.save.data.stats[i][j].hitCountOver256 != 0) {
                var_a3 += 256;
            }
            sp30[i] += var_a3;
        }
    }

    ret = sp30[0];

    for (i = 1; i < RANKING_MAX; i++) {
        if (ret < sp30[i]) {
            ret = sp30[i];
        }
    }

    return ret;
}

void Map_Starfield_Setup(void) {
    gStarCount = 800;

    Memory_FreeAll();
    Play_GenerateStarfield();

    gStarfieldX = SCREEN_WIDTH;
    gStarfieldY = SCREEN_HEIGHT;
    gStarfieldScrollX = 0.0f;
    gStarfieldScrollY = 0.0f;
}

void Map_Texture_Sphere(u8* textureDest, u8* textureSrc, f32* offset) {
    s32* var_v0 = D_menu_801B0004;
    s32 temp;
    s32 i;
    s32 j;
    s32 k;

    textureSrc = LOAD_ASSET(textureSrc);

    for (i = 1; i < 48; i++, var_v0++) {
        for (k = 0, j = *var_v0; j < (95 - *var_v0); j++, k++) {
            temp = sMapQuarterCircleTex[i - 1][k] + (s32) *offset;

            if (temp > 95) {
                temp -= 95;
            }
            if (temp < 0) {
                temp += 95;
            }

            *(textureDest + ((i * 96) + j)) = *(textureSrc + ((i * 96) + temp));
            *(textureDest + ((95 - i) * 96) + j) = *(textureSrc + ((95 - i) * 96) + temp);
        }
    }

    *offset -= 1.0f;

    if (*offset <= 0.0f) {
        *offset = 95.0f;
    }

    if (*offset > 95.0f) {
        *offset = 0.0f;
    }
}

void Map_Prologue_Update(void) {
    PlanetId planetId;
    static f32 D_menu_801B6934[] = {
        99.0f, 24, -90.0f, -150.0f, -208.0f, -276.0f,
    };

    switch (sMapSubState) {
        case 100:
            break;

        case 0:
            sPrologueTexIdx = 0;
            sPrologueTextXpos = 30.0f;
            sPrologueTextYpos = 230.0f;
            sPrologueCurrentTexAlpha = 0;
            sPrologueNextTexAlpha = 0;
            D_menu_801CD9EC = 0.29f;
            gStarCount = 800;
            sMapTimer3 = 5;
            sMapSubState++;
            break;

        case 1:
            if ((sMapTimer3 == 0) && (gFillScreenAlpha == 0)) {
                if ((s32) sPrologueTextYpos == 205) {
                    Audio_PlayVoiceWithoutBGM(1000);
                }

                if (sPrologueTextYpos > -355.0f) {
                    sPrologueTextYpos -= D_menu_801CD9EC;
                }

                if ((sPrologueTextYpos < 200.0f) && (sPrologueCurrentTexAlpha != 255)) {
                    sPrologueCurrentTexAlpha += 8;
                    if (sPrologueCurrentTexAlpha > 255) {
                        sPrologueCurrentTexAlpha = 255;
                    }
                }

                if (sPrologueTextYpos < D_menu_801B6934[sPrologueTexIdx]) {
                    sPrologueNextTexAlpha += 8;
                    if (sPrologueNextTexAlpha > 255) {
                        sPrologueNextTexAlpha = 255;
                    }
                }

                if (sPrologueTextYpos <= -355.0f) {
                    sMapSubState++;
                }
            }
            break;

        case 2:
            sPrologueCurrentTexAlpha -= 16;
            if (sPrologueCurrentTexAlpha < 0) {
                sPrologueCurrentTexAlpha = 0;
                sMapSubState++;
                sMapTimer3 = 20;
            }
            break;

        case 3:
            if (sMapTimer3 == 0) {
                sMapSubState = 0;
                sMapState = MAP_LYLAT_CARD;
            }
            break;
    }

    if ((gControllerPress[gMainController].button & START_BUTTON) || gBackToMap) {
        gBackToMap = false;
        AUDIO_PLAY_BGM(NA_BGM_MAP);
        AUDIO_PLAY_SFX(NA_SE_MAP_MOVE_STOP, gDefaultSfxSource, 4);

        for (planetId = 0; planetId < PLANET_MAX; planetId++) {
            if ((planetId == PLANET_SECTOR_Z) || (planetId == PLANET_SECTOR_X) || (planetId == PLANET_SECTOR_Y)) {
                sPlanets[planetId].alpha = 144;
            } else {
                sPlanets[planetId].alpha = 255;
            }
            D_menu_801CD900[planetId] = 255;
        }

        D_menu_801CD970 = 255;

        Audio_ClearVoice();

        D_menu_801CD974 = 1;
        D_menu_801CD97C = 1;
        sMapSubState = 0;
        sMapState = MAP_IDLE;
    }
}

void Map_Prologue_Draw(void) {
    s32 i;
    static f32 sPrologueTextFadeTexUpperYpos = 71.0f;
    static f32 sPrologueTextFadeTexBottomYpos = 205.0f;
    static u8* sPrologueTextures[] = {
        aMapPrologue1Tex, aMapPrologue2Tex, aMapPrologue3Tex, aMapPrologue4Tex,
        aMapPrologue5Tex, aMapPrologue6Tex, aMapPrologue7Tex,
    };

    Map_PrologueArwing_Draw();

    RCP_SetupDL(&gMasterDisp, SETUPDL_81_OPTIONAL);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 180, 180, 180, 255);

    // Prologue text
    Message_DisplayScrollingText(&gMasterDisp, gMsg_ID_1, sPrologueTextXpos, sPrologueTextYpos, 218, 70,
                                 Message_GetCharCount(gMsg_ID_1));

    RCP_SetupDL(&gMasterDisp, SETUPDL_76_OPTIONAL);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    // Vertical Fade Margins for prologue text
    Lib_TextureRect_IA8(&gMasterDisp, aMapPrologueTextFadeTex, 8, 16, 0.0f, sPrologueTextFadeTexUpperYpos, 40.0f,
                        1.66f);
    Lib_TextureRect_IA8_MirY(&gMasterDisp, aMapPrologueTextFadeTex, 8, 16, 0.0f, sPrologueTextFadeTexBottomYpos, 40.0f,
                             1.68f);

    Background_DrawPartialStarfield(71, 118);
    Background_DrawPartialStarfield(205, 239);

    RCP_SetupDL(&gMasterDisp, SETUPDL_76_OPTIONAL);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, sPrologueCurrentTexAlpha);

    Lib_TextureRect_RGBA16(&gMasterDisp, sPrologueTextures[sPrologueTexIdx], 96, 52, 109.0f, 24.0f, 1.0f, 1.0f);

    // Next Prologue texture
    if ((sPrologueNextTexAlpha != 0) && ((sPrologueTexIdx + 1) < 7)) {
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, sPrologueNextTexAlpha);

        Lib_TextureRect_RGBA16(&gMasterDisp, sPrologueTextures[sPrologueTexIdx + 1], 96, 52, 109.0f, 24.0f, 1.0f, 1.0f);

        if (sPrologueNextTexAlpha == 255) {
            sPrologueNextTexAlpha = 0;
            sPrologueTexIdx++;
        }
    }
}

void Map_PrologueArwing_Draw(void) {
    static f32 sMapArwingXrot = 35.0f;
    ArwingInfo arwing;
    Vec3f dest;
    Vec3f src;
    s32 colR = 30, colG = 9, colB = 5;
    s32 pad[5];

    src.x = 0.0f;
    src.y = 0.0f;
    src.z = 100.0f;

    Matrix_RotateY(gCalcMatrix, M_DTOR * 22.0f, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, M_DTOR * -70.0f, MTXF_APPLY);
    Matrix_MultVec3f(gCalcMatrix, &src, &dest);

    if (sMapSubState >= 2) {
        colR -= 10;
        if (colR < 0) {
            colR = 0;
        }

        colG -= 3;
        if (colG < 0) {
            colG = 0;
        }

        colB -= 2;
        if (colB < 0) {
            colB = 0;
        }

        RCP_SetupDL(&gMasterDisp, SETUPDL_46);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, sPrologueCurrentTexAlpha);
    } else {
        RCP_SetupDL(&gMasterDisp, SETUPDL_23);
    }

    if ((sMapSubState < 2) || (sPrologueCurrentTexAlpha != 0)) {
        Matrix_Push(&gGfxMatrix);
        Matrix_LookAt(gGfxMatrix, 0.0f, 0.0f, 430.0f, 0.0f, 180.0f, 0.0f, 0.0f, 1.0f, 0.0f, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);

        Lights_SetOneLight(&gMasterDisp, dest.x, dest.y, dest.z, colR, colG, colB, 0, 0, 0);

        Matrix_Push(&gGfxMatrix);

        Matrix_Translate(gGfxMatrix, -60.0f, 293.0f, -360.0f, MTXF_APPLY);
        Matrix_Scale(gGfxMatrix, 3.0f, 3.0f, 3.0f, MTXF_APPLY);

        Matrix_RotateZ(gGfxMatrix, M_DTOR * -15.0f, MTXF_APPLY);
        Matrix_RotateX(gGfxMatrix, M_DTOR * sMapArwingXrot, MTXF_APPLY);
        Matrix_RotateY(gGfxMatrix, M_DTOR * -90.0f, MTXF_APPLY);

        Matrix_SetGfxMtx(&gMasterDisp);

        arwing.rightWingState = arwing.leftWingState = WINGSTATE_INTACT;
        // clang-format off
        arwing.laserGunsXpos = arwing.wingsXrot = arwing.wingsYrot = arwing.wingsZrot = arwing.upperRightFlapYrot =
        arwing.bottomRightFlapYrot = arwing.upperLeftFlapYrot = arwing.bottomLeftFlapYrot = arwing.unk_28 = 0.0f;
        // clang-format on

        arwing.laserGunsYpos = 0.0f;
        arwing.drawFace = true;
        arwing.teamFaceXrot = 0.0f;
        arwing.teamFaceYrot = 0.0f;
        arwing.cockpitGlassXrot = 0.0f;

        Display_ArwingWings(&arwing);

        Matrix_Pop(&gGfxMatrix);
        Matrix_Pop(&gGfxMatrix);
    }
    sMapArwingXrot += 0.6f;
}

f32 D_menu_801B6974[8] = { -248.0f, -76.0f, 84.0f, 248.0f, -242.0f, -79.0f, 82.0f, 245.0f };
f32 D_menu_801B6994[8] = { 80.0f, 80.0f, 80.0f, 80.0f, -30.0f, -30.0f, -30.0f, -30.0f };
f32 D_menu_801B69B4[8] = { -455.0f, -455.0f, -455.0f, -455.0f, -455.0f, -455.0f, -455.0f, -455.0f };

f32 D_menu_801B69D4[8] = { -248.0f, -76.0f, 84.0f, 248.0f, -242.0f, -79.0f, 82.0f, 245.0f };
f32 D_menu_801B69F4[8] = { 80.0f, 80.0f, 80.0f, 80.0f, -30.0f, -30.0f, -30.0f, -30.0f };
f32 D_menu_801B6A14[8] = { 1000.0f, 1000.0f, 1000.0f, 1000.0f, 1000.0f, 1000.0f, 1000.0f, 1000.0f };

f32* D_menu_801B6A34[2] = { D_menu_801B69D4, D_menu_801B6974 };
f32* D_menu_801B6A3C[2] = { D_menu_801B69F4, D_menu_801B6994 };
f32* D_menu_801B6A44[2] = { D_menu_801B6A14, D_menu_801B69B4 };

void Map_LylatCard_Update(void) {
    PlanetId planetId;
    f32 temp;

    switch (sMapSubState) {
        case 0:
            temp = Math_SmoothStepToF(&D_menu_801CEA9C, 255.0f, D_menu_801CD9B0, 10.0f, 1.0f);

            D_menu_801CD9B0 *= 1.06f;

            if (temp == 0.0f) {
                D_menu_801CEAA0 = 0.0f;
                D_menu_801CEAA4 = 0.0f;
                D_menu_801CD9B0 = 0.002f;
                sMapTimer1 = 10;
                sMapTimer2 = 45;
                sMapSubState++;
            }
            break;

        case 1:
            if (sMapTimer1 != 0) {
                break;
            }

            Math_SmoothStepToF(&D_menu_801CEA9C, 0.0f, D_menu_801CD9B4, 50.0f, 0.1f);
            D_menu_801CD9B4 *= 1.06f;

            if (sMapTimer2 != 0) {
                break;
            }

            Math_SmoothStepToF(&D_menu_801CEAA0, 144.0f, D_menu_801CD9B0, 50.0f, 0.1f);
            temp = Math_SmoothStepToF(&D_menu_801CEAA4, 255.0f, D_menu_801CD9B0, 50.0f, 0.1f);
            D_menu_801CD9B0 *= 1.09f;

            for (planetId = 0; planetId < PLANET_MAX; planetId++) {
                if ((planetId == PLANET_SECTOR_Z) || (planetId == PLANET_SECTOR_X) || (planetId == PLANET_SECTOR_Y)) {
                    sPlanets[planetId].alpha = D_menu_801CEAA0;
                } else {
                    sPlanets[planetId].alpha = D_menu_801CEAA4;
                    D_menu_801CD970 = D_menu_801CEAA4;
                }
                D_menu_801CD900[planetId] = D_menu_801CEAA4;
            }

            if (D_menu_801CEAA0 > 32) {
                D_menu_801CD974 = 1;
            }

            if (temp == 0.0f) {
                AUDIO_PLAY_SFX(NA_SE_MAP_MOVE_STOP, gDefaultSfxSource, 4);
                sMapSubState = 0;
                D_menu_801CD97C = 1;
                sMapState = MAP_IDLE;
            }
            break;
    }

    if (gControllerPress[gMainController].button & START_BUTTON) {
        AUDIO_PLAY_SFX(NA_SE_MAP_MOVE_STOP, gDefaultSfxSource, 4);

        for (planetId = 0; planetId < PLANET_MAX; planetId++) {
            if ((planetId == PLANET_SECTOR_Z) || (planetId == PLANET_SECTOR_X) || (planetId == PLANET_SECTOR_Y)) {
                sPlanets[planetId].alpha = 144;
            } else {
                sPlanets[planetId].alpha = 255;
            }
            D_menu_801CD900[planetId] = 255;
        }
        D_menu_801CD970 = 255;
        sMapState = MAP_IDLE;
        D_menu_801CD97C = 1;
    }
}

void Map_LylatCard_Draw(void) {
    s32 i;

    RCP_SetupDL(&gMasterDisp, SETUPDL_83_OPTIONAL);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, (s32) D_menu_801CEA9C);

    Lib_TextureRect_IA8(&gMasterDisp, D_MAP_600D590, 168, 19, 72.0f, 104.0f, 1.0f, 1.0f);
}

void Map_ZoomPlanet_Setup(void) {
    f32 x;
    f32 y;
    f32 z;

    D_menu_801CEA64 = 0.04f;

    sCurrentPlanetCamZDist = Map_GetPlanetCamZDist(sCurrentPlanetId);

    sZoomPlanetCamAt.x = sPlanets[sCurrentPlanetId].pos.x;
    sZoomPlanetCamAt.y = sPlanets[sCurrentPlanetId].pos.y;
    sZoomPlanetCamAt.z = sPlanets[sCurrentPlanetId].pos.z;

    sZoomPlanetCamEye.x = sPlanets[sCurrentPlanetId].pos.x;
    sZoomPlanetCamEye.y = sPlanets[sCurrentPlanetId].pos.y;
    sZoomPlanetCamEye.z = sZoomPlanetCamAt.z + sCurrentPlanetCamZDist;

    sPathFollowCamAtX = sMapCamAtX;
    sPathFollowCamAtY = sMapCamAtY;

    sPathFollowCamEyeX = sMapCamEyeX;
    sPathFollowCamEyeY = sMapCamEyeY;

    x = sZoomPlanetCamEye.x - sMapCamEyeX;
    y = sZoomPlanetCamEye.y - sMapCamEyeY;
    z = sZoomPlanetCamEye.z - sMapCamEyeZ;

    D_menu_801CEA68 = sqrtf(SQ(x) + SQ(y) + SQ(z));
}

// Camera zooms into planet before briefing starts
void Map_ZoomPlanet_Update(void) {
    s32 i;

    switch (sMapSubState) {
        case 0:
            Map_ZoomPlanet_Setup();

            D_menu_801CD94C = 0;
            D_menu_801CD9C4 = 0;
            D_menu_801CEA88 = 0.0f;
            D_menu_801CEA8C = 0.0f;
            D_menu_801CEA90 = -400.0f;

            D_menu_801CEA78 = 0.05f;
            D_menu_801CEA7C = 0.05f;
            D_menu_801CEA80 = 0.05f;
            D_menu_801CEA84 = 0.05f;
            D_menu_801CEA94 = 0.0f;
            D_menu_801CEA98 = 0;
            D_menu_801CD95C = 10;
            D_menu_801CD97C = 0;

            if (sCurrentPlanetId == PLANET_CORNERIA) {
                D_menu_801CD95C = 5;
            }

            D_menu_801CD9D8 = 0;

            for (i = 0; i < 24; i++) {
                sPaths[i].alpha = 0;
            }
            gStarCount = 0;

            gFillScreenRed = 255;
            gFillScreenGreen = 255;
            gFillScreenBlue = 255;
            gFillScreenAlpha = 0;

            sMapCorneriaExplosionScale = 0.0f;
            D_menu_801CEB38 = 255;

            sMapSubState++;
            break;

        case 1:
            if (D_menu_801CD95C == 0) {
                if (sCurrentPlanetId == PLANET_CORNERIA) {
                    gFillScreenAlpha = 0;
                    sMapSubState = 10;
                    AUDIO_PLAY_SFX(NA_SE_BACKUP_CLEAR, gDefaultSfxSource, 4);
                } else {
                    AUDIO_PLAY_SFX(NA_SE_MAP_ZOOM_START, gDefaultSfxSource, 4);
                    sMapSubState++;
                }
            } else {
                if (sCurrentPlanetId == PLANET_CORNERIA) {
                    gFillScreenAlpha ^= 0xFF;
                    if (D_menu_801CD95C == 2) {
                        D_menu_801CEB34 = 0;
                    }
                }
                D_menu_801CD95C--;
            }
            break;

        case 10:
            if (D_menu_801CEB34 == 4) {
                AUDIO_PLAY_SFX(NA_SE_MAP_ZOOM_START, gDefaultSfxSource, 4);
                sMapSubState = 2;
            }
            break;

        case 2:
            Map_801A2674();
            if ((sMapCamEyeZ == sZoomPlanetCamEye.z) && (D_menu_801CD9D8 == 0)) {
                AUDIO_PLAY_SFX(NA_SE_MAP_ZOOM_END, gDefaultSfxSource, 4);
                D_menu_801CD9D8 = 1;
                if (sCurrentPlanetId == PLANET_CORNERIA) {
                    sPlanetExplosions[EXPLOSIONS_CORNERIA] = true;
                    for (i = 0; i < 10; i++) {
                        D_menu_801CEB58[0][i] = RAND_INT(3.0f);
                        D_menu_801CEBD0[0][i] = 255;
                        D_menu_801CEC48[0][i] = 0.0f;
                        D_menu_801CECC0[0][i] = 0.5f + RAND_FLOAT(0.3f);
                        D_menu_801CEE28[0][i] = 1 + RAND_INT(4.0f);
                        D_menu_801CED38[0][i] = 110.0f + RAND_INT(30.0f);
                        D_menu_801CEDB0[0][i] = -10.0f + RAND_FLOAT(-60.0f);
                    }
                }
            }
            if ((sPathFollowCamEyeX == sZoomPlanetCamEye.x) && (sPathFollowCamEyeY == sZoomPlanetCamEye.y) &&
                (sMapCamEyeZ == sZoomPlanetCamEye.z) && (sMapCamAtZ == sZoomPlanetCamAt.z)) {

                D_menu_801CD964 = 1;
                D_menu_801CD96C = true;
                // clang-format off
                for (i = 0; i < 15; i++) {D_menu_801CD900[i] = 0;}
                // clang-format on
                D_menu_801CD970 = 0;

                if (Map_GralPepper_Talk()) {
                    sMapSubState = 3;
                }
            }
            break;

        case 20:
            if (gControllerPress[gMainController].button & START_BUTTON) {
                sMapSubState = 21;
            }

            if (gControllerHold[gMainController].button & R_TRIG) {
                sMapCamEyeZ += 10.0f;
            }

            if (gControllerHold[gMainController].button & Z_TRIG) {
                if (sMapCamEyeZ - 10.0f > sMapCamAtZ) {
                    sMapCamEyeZ -= 10.0f;
                }
            }
            break;

        case 21:
            D_menu_801CD964 = 1;
            D_menu_801CD96C = true;
            // clang-format off
            for (i = 0; i < 15; i++) { D_menu_801CD900[i] = 0; }
            // clang-format on
            D_menu_801CD970 = 0;

            if (Map_GralPepper_Talk()) {
                sMapSubState = 3;
            }
            break;

        case 3:
            sMapSubState = 0;
            sMapState = MAP_LEVEL_START;
            break;
    }
    D_menu_801CD9C4++;
}

bool Map_GralPepper_Talk(void) {
    bool ret = false;
    f32 sp28;
    f32 sp24;
    f32 sp20;
    f32 temp_fv0;

    switch (D_menu_801CD94C) {
        case 0:
            Audio_PlayVoice(3);
            D_menu_801CEA78 += 2.9f;
            D_menu_801CEA80 += 2.9f;
            if (D_menu_801CEA78 > 5.5f) {
                D_menu_801CEA78 = 5.5f;
                D_menu_801CEA80 = 4.6f;
                D_menu_801CD94C++;
                sMapTimer1 = 13;
            }
            break;

        case 1:
            D_menu_801CEA78 -= 2.5f;
            D_menu_801CEA98 += 10;
            D_menu_801CEA80 -= 2.5f;

            if (D_menu_801CEA78 < 5.0f) {
                D_menu_801CEA78 = 5.0f;
            }

            if (D_menu_801CEA80 < 3.9f) {
                D_menu_801CEA80 = 3.9f;
            }

            D_menu_801CEA7C += 2.5f;
            D_menu_801CEA84 += 2.5f;

            if (D_menu_801CEA7C > 5.0f) {
                D_menu_801CEA7C = 5.0f;
            }

            if (D_menu_801CEA84 > 3.9f) {
                D_menu_801CEA84 = 3.9f;
            }

            if (sMapTimer1 == 0) {
                D_menu_801CEA98 = 255;
                D_menu_801CD94C = 100;
            }
            break;

        case 100:
            sp28 = Math_SmoothStepToF(&D_menu_801CEA88, -206.0f, 0.4f, 100.0f, 1.0f);
            sp24 = Math_SmoothStepToF(&D_menu_801CEA8C, 51.0f, 0.4f, 100.0f, 1.0f);
            sp20 = Math_SmoothStepToF(&D_menu_801CEA90, -627.0f, 0.4f, 100.0f, 1.0f);
            temp_fv0 = Math_SmoothStepToF(&D_menu_801CEA94, 42.8f, 0.4f, 100.0f, 1.0f);
            if ((sp28 == 0.0f) && (sp24 == 0.0f) && (sp20 == 0.0f) && (temp_fv0 == 0.0f)) {
                ret = true;
            }
            break;
    }

    return ret;
}

f32 Map_GetPlanetCamZDist(PlanetId planetId) {
    f32 camZdist;

    switch (planetId) {
        case PLANET_AREA_6:
            camZdist = 900.0f;
            break;

        case PLANET_BOLSE:
            camZdist = 800.0f;
            break;

        case PLANET_METEO:
            camZdist = 650.0f;
            break;

        case PLANET_KATINA:
        case PLANET_MACBETH:
        case PLANET_ZONESS:
        case PLANET_TITANIA:
        case PLANET_AQUAS:
        case PLANET_FORTUNA:
            camZdist = 550.0f;
            break;

        case PLANET_CORNERIA:
            camZdist = 1100.0f;
            break;

        case PLANET_VENOM:
            camZdist = 2100.0f;
            break;

        case PLANET_SOLAR:
            camZdist = 850.0f;
            break;

        case PLANET_SECTOR_Z:
        case PLANET_SECTOR_X:
        case PLANET_SECTOR_Y:
            camZdist = 650.0f;
            break;

        default:
            break;
    }

    return camZdist;
}

void Map_801A2674(void) {
    s32 i;

    Map_801A48C0(D_menu_801CEA64);

    Map_801A4A38(D_menu_801CEA64);

    D_menu_801CEA64 *= 1.03f;

    for (i = 0; i < 15; i++) {
        D_menu_801CD900[i] -= 16;

        if (D_menu_801CD900[i] < 0) {
            D_menu_801CD900[i] = 0;
        }

        if (i == sCurrentPlanetId) {
            continue;
        }

        sPlanets[i].alpha -= 16;

        if (sPlanets[i].alpha < 0) {
            sPlanets[i].alpha = 0;
        }
    }

    for (i = 0; i < 24; i++) {
        if (gPlanetPathStatus[i] == 0) {
            continue;
        }

        sPaths[i].alpha -= 16;

        if (sPaths[i].alpha < 0) {
            sPaths[i].alpha = 0;
        }
    }

    if (sCurrentPlanetId == PLANET_BOLSE) {
        Math_SmoothStepToF(&D_menu_801AFFF8, 20.0f, 0.05f, 100.0f, 0.1f);
    }

    if (sCurrentPlanetId == PLANET_AREA_6) {
        Math_SmoothStepToF(&D_menu_801B0000, 15.0f, 0.05f, 100.0f, 0.1f);
    }

    D_menu_801CD970 -= 16;
    if (D_menu_801CD970 < 0) {
        D_menu_801CD970 = 0;
    }

    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 45);
    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 45);
}

void Map_801A281C(void) {
    gFillScreenRed = 0;
    gFillScreenGreen = 0;
    gFillScreenBlue = 0;
    gFillScreenAlpha = 255;

    D_menu_801CD988 = 5;
    D_menu_801CEED8 = 0;
    D_menu_801CEEDC = 0.0f;
    D_menu_801CEEE0 = 0.04f;

    D_menu_801CEEE8[0].x = D_menu_801CEEE8[1].x = sMapCamEyeX;
    D_menu_801CEEE8[0].y = D_menu_801CEEE8[1].y = sMapCamEyeY;
    D_menu_801CEEE8[0].z = D_menu_801CEEE8[1].z = sMapCamEyeZ;

    D_menu_801CEF58[0].x = D_menu_801CEF58[1].x = sMapCamAtX;
    D_menu_801CEF58[0].y = D_menu_801CEF58[1].y = sMapCamAtY;
    D_menu_801CEF58[0].z = D_menu_801CEF58[1].z = sMapCamAtZ;

    D_menu_801CEF58[5].x = D_menu_801CEF58[4].x = D_menu_801CEF58[3].x = D_menu_801CEF58[2].x =
        sPlanets[sNextPlanetId].pos.x;
    D_menu_801CEF58[5].y = D_menu_801CEF58[4].y = D_menu_801CEF58[3].y = D_menu_801CEF58[2].y =
        sPlanets[sNextPlanetId].pos.y;
    D_menu_801CEF58[5].z = D_menu_801CEF58[4].z = D_menu_801CEF58[3].z = D_menu_801CEF58[2].z =
        sPlanets[sNextPlanetId].pos.z;

    D_menu_801CDA0C = -46.5f;
    D_menu_801CDA10 = 0.0f;
    D_menu_801CDA14 = 500.0f;

    Map_SetCamRot(D_menu_801CEF58[2].x, D_menu_801CEF58[2].y, D_menu_801CEF58[2].z, &D_menu_801CEEE8[2].x,
                  &D_menu_801CEEE8[2].y, &D_menu_801CEEE8[2].z, D_menu_801CDA14, D_menu_801CDA0C, D_menu_801CDA10);

    D_menu_801CEEE8[5].x = D_menu_801CEEE8[4].x = D_menu_801CEEE8[3].x = D_menu_801CEEE8[2].x;
    D_menu_801CEEE8[5].y = D_menu_801CEEE8[4].y = D_menu_801CEEE8[3].y = D_menu_801CEEE8[2].y;
    D_menu_801CEEE8[5].z = D_menu_801CEEE8[4].z = D_menu_801CEEE8[3].z = D_menu_801CEEE8[2].z;

    D_menu_801CEF58[7].x = D_menu_801CEF58[6].x = -150.55215f;
    D_menu_801CEF58[7].y = D_menu_801CEF58[6].y = -489.68f;
    D_menu_801CEF58[7].z = D_menu_801CEF58[6].z = 0.0f;

    D_menu_801CDA0C = -42.750008f;
    D_menu_801CDA10 = -9.849999f;
    D_menu_801CDA14 = 3375.0f; // 15^3

    Map_SetCamRot(D_menu_801CEF58[6].x, D_menu_801CEF58[6].y, D_menu_801CEF58[6].z, &D_menu_801CEEE8[6].x,
                  &D_menu_801CEEE8[6].y, &D_menu_801CEEE8[6].z, D_menu_801CDA14, D_menu_801CDA0C, D_menu_801CDA10);

    D_menu_801CEEE8[7].x = D_menu_801CEEE8[6].x;
    D_menu_801CEEE8[7].y = D_menu_801CEEE8[6].y;
    D_menu_801CEEE8[7].z = D_menu_801CEEE8[6].z;

    D_menu_801CEECC = Map_GetPathId(sCurrentPlanetId, sNextPlanetId);

    if (sPrevMissionStatus == MISSION_WARP) {
        gPlanetPathStatus[D_menu_801CEECC] = 5;
        sPaths[D_menu_801CEECC].unk_14 = 5;
    } else {
        gPlanetPathStatus[D_menu_801CEECC] = 2;
        sPaths[D_menu_801CEECC].unk_14 = 1;
    }
}

void Map_ZoomPlanetPath_Update(void) {
    s32 i;

    switch (D_menu_801CD94C) {
        case 0:
            Map_801A281C();
            D_menu_801CD94C = 100;
            break;

        case 100:
            if (gFillScreenAlpha != 0) {
                gFillScreenAlpha -= 64;
                if (gFillScreenAlpha < 0) {
                    gFillScreenAlpha = 0;
                }
            } else {
                sMapTimer3 = 30;

                if ((D_menu_801CD98C == true) || (D_menu_801CD980 == true)) {
                    gFillScreenRed = 255;
                    gFillScreenGreen = 255;
                    gFillScreenBlue = 255;
                    gFillScreenAlpha = 0;
                    D_menu_801CD984 = 0;
                    D_menu_801CD94C = 10;
                    break;
                }
                D_menu_801CD9C4 = 0;
                D_menu_801CD94C = 1;
            }
            break;

        case 10:
            if (sMapTimer3 != 0) {
                break;
            }

            if ((D_menu_801CD984 == 255) && (gFillScreenAlpha == 0)) {
                D_menu_801CD980 = false;
                sMapTimer3 = 30;
                D_menu_801CD94C = 20;
            } else if (D_menu_801CD988 != 0) {
                gFillScreenAlpha ^= 255;
                D_menu_801CD988--;
            } else {
                D_menu_801CD988 = 0;

                if (gFillScreenAlpha != 0) {
                    gFillScreenAlpha -= 21;
                    if (gFillScreenAlpha < 0) {
                        gFillScreenAlpha = 0;
                    }
                }

                D_menu_801CD984 += 8;

                if (D_menu_801CD984 > 255) {
                    gFillScreenAlpha = 0;
                    D_menu_801CD984 = 255;
                }
            }

            break;

        case 20:
            if (sMapTimer3 != 0) {
                break;
            }
            if ((D_menu_801CD98C == true) || (D_menu_801CD980 == true)) {
                break;
            }
            D_menu_801CD9C4 = 0;
            sMapTimer3 = 30;
            D_menu_801CD94C = 1;
            break;

        case 1:
            if (sMapTimer3 != 0) {
                break;
            }
            Map_801A2EB8();
            break;

        case 2:
            if (sMapTimer3 != 0) {
                break;
            }

            for (i = 0; i < 15; i++) {
                D_menu_801CD900[i] = 255;
            }
            sMapTimer3 = 0;
            D_menu_801CD94C++;
            break;

        case 3:
            if (sMapTimer3 != 0) {
                break;
            }
            D_menu_801CEFC8 = 1;
            D_menu_801CD97C = 1;
            D_menu_801CD94C = 0;
            sMapState = MAP_IDLE;
            break;
    }

    Camera_SetStarfieldPos(sMapCamEyeX, sMapCamEyeY, sMapCamEyeZ, sMapCamAtX, sMapCamAtY, sMapCamAtZ);

    D_menu_801CD9C4++;
}

void Map_801A2EB8(void) {
    s32 i;
    s32 temp1;
    s32 temp2;

    if (D_menu_801CD9C4 == 30) {
        if (sPrevMissionStatus == MISSION_WARP) {
            AUDIO_PLAY_SFX(NA_SE_MAP_ARWING_WARP_DASH, gDefaultSfxSource, 4);
        } else {
            AUDIO_PLAY_SFX(NA_SE_MAP_ARWING_DASH, gDefaultSfxSource, 4);
        }
    }

    Map_801A3440(D_menu_801CEEE0);

    if (D_menu_801CD9C4 == 80) {
        sCurrentPlanetId = sNextPlanetId;
        gMissionPlanet[gMissionNumber] = sCurrentPlanetId;
        Map_CurrentLevel_Setup();
    }

    if (D_menu_801CD9C4 < 80) {
        sPaths[D_menu_801CEECC].alpha += 16;
        if (sPaths[D_menu_801CEECC].alpha > 255) {
            sPaths[D_menu_801CEECC].alpha = 255;
        }

        sPlanets[sNextPlanetId].alpha += 16;
        if ((sNextPlanetId == PLANET_SECTOR_Z) || (sNextPlanetId == PLANET_SECTOR_X) ||
            (sNextPlanetId == PLANET_SECTOR_Y)) {
            if (sPlanets[sNextPlanetId].alpha > 144) {
                sPlanets[sNextPlanetId].alpha = 144;
            }
        } else if (sPlanets[sNextPlanetId].alpha > 255) {
            sPlanets[sNextPlanetId].alpha = 255;
        }

    } else {
        D_menu_801CD970 += 16;
        if (D_menu_801CD970 > 255) {
            D_menu_801CD970 = 255;
        }

        for (i = 0; i < 24; i++) {
            if (gPlanetPathStatus[i] == 0) {
                continue;
            }
            sPaths[i].alpha += 16;
            if (sPaths[i].alpha > 255) {
                sPaths[i].alpha = 255;
            }
        }

#define PLANET_ID i

        for (PLANET_ID = 0; PLANET_ID < PLANET_MAX; PLANET_ID++) {
            if ((PLANET_ID == sCurrentPlanetId) || (PLANET_ID == sNextPlanetId)) {
                continue;
            }

            sPlanets[PLANET_ID].alpha += 16;

            if ((PLANET_ID == PLANET_SECTOR_Z) || (PLANET_ID == PLANET_SECTOR_X) || (PLANET_ID == PLANET_SECTOR_Y)) {
                if (sPlanets[PLANET_ID].alpha > 144) {
                    sPlanets[PLANET_ID].alpha = 144;
                }
            } else {
                if (sPlanets[PLANET_ID].alpha > 255) {
                    sPlanets[PLANET_ID].alpha = 255;
                }
            }
        }

#undef PLANET_ID
    }

    if ((D_menu_801CEED8 == 4) && (D_menu_801CEEDC == 0.0f)) {
        AUDIO_PLAY_SFX(NA_SE_MAP_ZOOM_OUT, gDefaultSfxSource, 4);
    }

    if ((D_menu_801CEED8 == 5) && (D_menu_801CEEDC == 0.0f)) {
        if (sPrevMissionStatus != MISSION_WARP) {
            sPaths[D_menu_801CEECC].unk_14 = 2;
            D_menu_801CEEA0 = 0;
            D_menu_801CEEA4 = 100;
            D_menu_801CEEA8 = 255;
            D_menu_801CEEAC = 255;
        }
    }

    if (D_menu_801CEED8 == -1) {

        D_menu_801CEED4 = -1;
        if (sPlanets[sNextPlanetId].dest1 != PLANET_NONE) {
            temp1 = Map_GetPathId(sNextPlanetId, sPlanets[sNextPlanetId].dest1);
            gPlanetPathStatus[temp1] = 1;
            sPaths[temp1].alpha = 255;
            D_menu_801CEED4 = temp1;
        }

        D_menu_801CEED0 = -1;
        if (sPlanets[sNextPlanetId].dest2 != PLANET_NONE) {
            temp2 = Map_GetPathId(sNextPlanetId, sPlanets[sNextPlanetId].dest2);
            gPlanetPathStatus[temp2] = 1;
            sPaths[temp2].alpha = 255;
            D_menu_801CEED0 = temp2;
        }
        sMapTimer3 = 50;
        D_menu_801CD94C++;
    }
}

void Map_801A3440(f32 arg0) {
    Vec3f vec[2];

    if (D_menu_801CEED8 != -1) {
        Map_801A3550(vec, &D_menu_801CEEE8[D_menu_801CEED8], &D_menu_801CEF58[D_menu_801CEED8], D_menu_801CEEDC);
        sMapCamEyeX = vec[0].x;
        sMapCamEyeY = vec[0].y;
        sMapCamEyeZ = vec[0].z;
        sMapCamAtX = vec[1].x;
        sMapCamAtY = vec[1].y;
        sMapCamAtZ = vec[1].z;
        D_menu_801CEEDC += arg0;

        if (D_menu_801CEEDC > 1.0f) {
            D_menu_801CEED8++;
            D_menu_801CEEDC = 0.0f;
            if (D_menu_801CEED8 >= 6) {
                D_menu_801CEED8 = -1;
            }
        }
    }
}

// Camera related
void Map_801A3550(Vec3f* arg0, Vec3f* arg1, Vec3f* arg2, f32 arg3) {
    f32 temp_fa1;
    f32 temp_fs0;
    f32 temp_ft5;

    temp_fa1 = 0.5f * ((1.0f - arg3) * (1.0f - arg3));
    temp_fs0 = (-arg3 + 1.0f) * arg3 + 0.5f;
    temp_ft5 = SQ(arg3) * 0.5f;

    arg0->x = (temp_fa1 * arg1->x) + (temp_fs0 * (arg1 + 1)->x) + (temp_ft5 * (arg1 + 2)->x);
    arg0->y = (temp_fa1 * arg1->y) + (temp_fs0 * (arg1 + 1)->y) + (temp_ft5 * (arg1 + 2)->y);
    arg0->z = (temp_fa1 * arg1->z) + (temp_fs0 * (arg1 + 1)->z) + (temp_ft5 * (arg1 + 2)->z);

    (arg0 + 1)->x = (temp_fa1 * arg2->x) + (temp_fs0 * (arg2 + 1)->x) + (temp_ft5 * (arg2 + 2)->x);
    (arg0 + 1)->y = (temp_fa1 * arg2->y) + (temp_fs0 * (arg2 + 1)->y) + (temp_ft5 * (arg2 + 2)->y);
    (arg0 + 1)->z = (temp_fa1 * arg2->z) + (temp_fs0 * (arg2 + 1)->z) + (temp_ft5 * (arg2 + 2)->z);
}

void Map_GameOver_Update(void) {
    s32 i;
    f32 temp;

    switch (sMapSubState) {
        case 0:
            gFillScreenRed = 0;
            gFillScreenGreen = 0;
            gFillScreenBlue = 0;
            gFillScreenAlpha = 255;

            for (i = 0; i < 8; i++) {
                s3DFontXpos[i] = D_menu_801B69D4[i];
                s3DFontYpos[i] = D_menu_801B69F4[i];
                s3DFontZpos[i] = D_menu_801B6A14[i];
            }

            D_menu_801CF0C8 = D_menu_801B6A34[1];
            D_menu_801CF0CC = D_menu_801B6A3C[1];
            D_menu_801CF0D0 = D_menu_801B6A44[1];

            D_menu_801CF120 = false;
            D_menu_801CEA9C = 255.0f;
            s3DFontScale = 1.0f;
            sMapSubState = 10;

            AUDIO_PLAY_BGM(NA_BGM_GAME_OVER);
            break;

        case 10:
            temp = Math_SmoothStepToF(&D_menu_801CEA9C, 0.0f, 1.0f, 100.0f, 1.0f);

            gFillScreenAlpha = D_menu_801CEA9C;

            if (temp == 0.0f) {
                gFillScreenAlpha = 0;
                sMapTimer3 = 0;
                sMapSubState = 20;
            }
            break;

        case 20:
            if (sMapTimer3 != 0) {
                break;
            }
            D_menu_801CD94C = 0;
            sMapTimer3 = 0;
            sMapSubState = 1;
            break;

        case 1:
            if (D_menu_801CF120) {
                D_menu_801CDA1C += 0.03f;
            }
            if (sMapTimer3 == 0) {
                Map_GameOver_3DFont();
            }
            break;

        case 2:
            Map_801A4394();
            break;

        case 3:
            gFillScreenAlpha += 32;
            if (gFillScreenAlpha > 255) {
                gFillScreenAlpha = 255;
                sMapSubState++;
            }
            break;

        case 4:
            gGameState = GSTATE_MENU;
            gNextGameStateTimer = 2;
            gOptionMenuStatus = OPTION_WAIT;
            gDrawMode = DRAW_NONE;
            gStarCount = 0;
            break;
    }

    if (gControllerPress[gMainController].button & (A_BUTTON | START_BUTTON)) {
        AUDIO_PLAY_SFX(NA_SE_DECIDE, gDefaultSfxSource, 4);
        sMapSubState = 3;
    }
}

void Map_GameOver_3DFont(void) {
    s32 i;
    bool boolTemp;
    f32 temp1[8];
    f32 temp2[8];
    f32 temp3[8];

    switch (D_menu_801CD94C) {
        case 0:
            for (i = 0; i < 8; i++) {
                if (!D_menu_801CF120) {
                    D_menu_801CF0D8[i] = i * 4;
                } else {
                    D_menu_801CF0D8[i] = i * 3;
                }
                s3DFontXrot[i] = 0.0f;
                s3DFontYrot[i] = 0.0f;
                D_menu_801CF0F8[i] = 0;
            }
            D_menu_801CD94C++;
            break;

        case 1:
            for (i = 0; i < 8; i++) {
                if (D_menu_801CF0D8[i] != 0) {
                    D_menu_801CF0D8[i]--;
                    continue;
                }

                temp1[i] = Math_SmoothStepToF(&s3DFontXpos[i], D_menu_801CF0C8[i], 0.05f, 100.0f, 10.0f);
                temp2[i] = Math_SmoothStepToF(&s3DFontYpos[i], D_menu_801CF0CC[i], 0.05f, 100.0f, 10.0f);
                temp3[i] = Math_SmoothStepToF(&s3DFontZpos[i], D_menu_801CF0D0[i], 0.1f, 100.0f, 0.1f);

                if (temp1[i] == 0.0f && temp2[i] == 0.0f && temp3[i] == 0.0f) {
                    s3DFontXrot[i] = 0.0f;
                    if (temp3[i] == 0.0f) {
                        D_menu_801CF0F8[i] = 1;
                    }
                } else {
                    s3DFontXrot[i] += 10.0f;
                }
            }

            boolTemp = true;
            for (i = 0; i < 8; i++) {
                if (D_menu_801CF0F8[i] == 0) {
                    boolTemp = false;
                    break;
                }
            }

            if (boolTemp == true) {
                D_menu_801CF118 = 0;
                for (i = 0; i < 8; i++) {
                    s3DFontXrot[i] = 0.0f;
                    D_menu_801CF0D8[i] = i * 10;
                    D_menu_801CF0F8[i] = 0;
                }
                sMapTimer3 = 60;
                sMapTimer2 = 85;
                D_menu_801CD94C = 11;
            }
            break;

        case 11:
            if (sMapTimer3 == 0) {
                if (sMapTimer2) {
                    for (i = 0; i < 8; i++) {
                        Math_SmoothStepToF(&s3DFontXrot[i], 360.0f, 0.3f, 100.0f, 1.0f);
                        Math_SmoothStepToF(&s3DFontYrot[i], 360.0f, 0.3f, 100.0f, 1.0f);
                    }
                } else {
                    D_menu_801CD94C = 10;
                }
            }
            break;

        case 10:
            if (!sMapTimer1) {
                if (!D_menu_801CF120) {
                    D_menu_801CEAA0 = 0.0f;
                    sMapTimer1 = 25;
                    D_menu_801CD94C = 3;
                } else {
                    for (i = 0; i < 8; i++) {
                        s3DFontXrot[i] = 0.0f;
                        s3DFontYrot[i] = 0.0f;
                        D_menu_801CF0F8[i] = 0;
                    }
                    D_menu_801CEFCC = 0;
                    D_menu_801CF0D8[0] = 4;
                    D_menu_801CD94C = 2;
                }
            }
            break;

        case 2:
            if (D_menu_801CF0D8[0] != 0) {
                D_menu_801CF0D8[0]--;
            } else {
                D_menu_801CEFCC++;
                if (D_menu_801CEFCC > 8) {
                    D_menu_801CEFCC = 8;
                    boolTemp = true;

                    for (i = 0; i < 8; i++) {
                        if (D_menu_801CF0F8[i] == 0) {
                            boolTemp = false;
                            break;
                        }
                    }

                    if (boolTemp) {
                        D_menu_801CEFCC = 0;
                        D_menu_801CF11C ^= 1;
                        D_menu_801CF0C8 = D_menu_801B6A34[D_menu_801CF11C];
                        D_menu_801CF0CC = D_menu_801B6A3C[D_menu_801CF11C];
                        D_menu_801CF0D0 = D_menu_801B6A44[D_menu_801CF11C];

                        sMapTimer3 = 15;
                        if (D_menu_801CF11C) {
                            sMapTimer3 = 240;
                        }
                        D_menu_801CD94C = 0;
                    }
                } else {
                    D_menu_801CF0D8[0] = 4;
                }
            }

            for (i = 0; i < D_menu_801CEFCC; i++) {
                if (D_menu_801CF0F8[i] == 1) {
                    continue;
                }

                if (s3DFontYrot[i] > 360.0f) {
                    s3DFontYrot[i] = 0.0f;
                    D_menu_801CF0F8[i] = 1;
                } else {
                    s3DFontYrot[i] += 10.0f;
                }
            }
            break;

        case 3:
            if (sMapTimer1 != 0) {
                break;
            }

            for (i = 0; i < 8; i++) {
                s3DFontXrot[i] += 30.0f;
                s3DFontZpos[i] += -300.0f;
                if (s3DFontZpos[i] <= -120000.0f) {
                    s3DFontZpos[i] = -12000.0f;
                }
            }

            if (s3DFontZpos[0] <= -11000.0f) {
                D_menu_801CEAA0 += 32.0f;

                if (D_menu_801CEAA0 > 255.0f) {
                    D_menu_801CEAA0 = 255.0f;
                }

#define PLANET_ID i
                for (PLANET_ID = 0; PLANET_ID < PLANET_MAX; PLANET_ID++) {
                    sPlanets[PLANET_ID].alpha = D_menu_801CEAA0;
                    D_menu_801CD970 = D_menu_801CEAA0;
                    if ((PLANET_ID == PLANET_SECTOR_Z) || (PLANET_ID == PLANET_SECTOR_X) ||
                        (PLANET_ID == PLANET_SECTOR_Y)) {
                        if (sPlanets[PLANET_ID].alpha > 144) {
                            sPlanets[PLANET_ID].alpha = 144;
                        }
                    }
                }
#undef PLANET_ID
            }

            if (D_menu_801CEAA0 == 255.0f) {
                s3DFontScale = 0.0f;
                sMapSubState = 2;
                D_menu_801CD94C = 0;
            }
            break;
    }
}

void Map_801A4394(void) {
    s32 i;

    switch (D_menu_801CD94C) {
        case 0:
            if (gMissionNumber == 0) {
                sMapTimer3 = 45;
                D_menu_801CD94C = 3;
            } else {
                D_menu_801CD94C++;
            }
            break;

        case 1:
            if (gMissionNumber == D_menu_801CD9AC) {
                D_menu_801CD94C = 3;
                sMapTimer3 = 45;
                break;
            }

            if ((sPaths[D_menu_801CD8E0[D_menu_801CD9AC]].type == 3) ||
                (sPaths[D_menu_801CD8E0[D_menu_801CD9AC]].type == 4)) {
                gPlanetPathStatus[D_menu_801CD8E0[D_menu_801CD9AC]] = 5;
                sPaths[D_menu_801CD8E0[D_menu_801CD9AC]].unk_14 = 5;
            } else {
                gPlanetPathStatus[D_menu_801CD8E0[D_menu_801CD9AC]] = 2;
                sPaths[D_menu_801CD8E0[D_menu_801CD9AC]].unk_14 = 0;
            }

            sPaths[D_menu_801CD8E0[D_menu_801CD9AC]].alpha = 255;
            D_menu_801CEEAC = 255;
            D_menu_801CEEA8 = 255;
            D_menu_801CD94C++;
            break;

        case 2:
            if ((gPlanetPathStatus[D_menu_801CD8E0[D_menu_801CD9AC]] == 3) ||
                (gPlanetPathStatus[D_menu_801CD8E0[D_menu_801CD9AC]] == 6)) {
                D_menu_801CD9AC++;
                D_menu_801CD94C = 1;
            }
            break;

        case 3:
            if (sMapTimer3 != 0) {
                break;
            }

            for (i = 0; i < 8; i++) {
                s3DFontXpos[i] = D_menu_801B69D4[i];
                s3DFontYpos[i] = D_menu_801B69F4[i];
                s3DFontZpos[i] = D_menu_801B6A14[i];
            }

            D_menu_801CD978 = 1;
            D_menu_801CF120 = true;
            D_menu_801CF11C = 1;

            D_menu_801CF0C8 = D_menu_801B6A34[1];
            D_menu_801CF0CC = D_menu_801B6A3C[1];
            D_menu_801CF0D0 = D_menu_801B6A44[1];

            s3DFontScale = 1.0f;
            sMapTimer3 = 450;
            D_menu_801CD94C = 0;
            sMapSubState = 1;
            break;
    }
}

void Map_GameOver_Draw(void) {
    s32 i;
    static Gfx* sMap3DFontDLs[] = {
        aFont3D_G, aFont3D_A, aFont3D_M, aFont3D_E, aFont3D_O, aFont3D_V, aFont3D_E, aFont3D_R,
    };

    Lights_SetOneLight(&gMasterDisp, 0, 0, 127, 28, 58, 105, 65, 70, 48);

    RCP_SetupDL(&gMasterDisp, SETUPDL_23);
    gSPTexture(gMasterDisp++, 2500, 200, 0, G_TX_RENDERTILE, G_ON);
    gSPSetGeometryMode(gMasterDisp++, G_TEXTURE_GEN);

    Matrix_Push(&gGfxMatrix);
    Matrix_LookAt(gGfxMatrix, 0.0f, 0.0f, 500.0f, 0.0f, 0.0f, -500.0f, 0.0f, 1.0f, 0.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);

    for (i = 0; i < ARRAY_COUNT(sMap3DFontDLs); i++) {
        Matrix_Push(&gGfxMatrix);

        Matrix_Translate(gGfxMatrix, s3DFontXpos[i], s3DFontYpos[i], s3DFontZpos[i], MTXF_APPLY);
        Matrix_RotateY(gGfxMatrix, M_DTOR * s3DFontYrot[i], MTXF_APPLY);
        Matrix_RotateX(gGfxMatrix, M_DTOR * s3DFontXrot[i], MTXF_APPLY);
        Matrix_Scale(gGfxMatrix, s3DFontScale, s3DFontScale, s3DFontScale, MTXF_APPLY);

        Matrix_SetGfxMtx(&gMasterDisp);

        gSPDisplayList(gMasterDisp++, sMap3DFontDLs[i]);

        Matrix_Pop(&gGfxMatrix);
    }

    Matrix_Pop(&gGfxMatrix);
}

void Map_801A48C0(f32 speed) {
    f32 x;
    f32 y;
    f32 z;
    f32 temp;
    f32 angle;

    Math_SmoothStepToF(&sPathFollowCamEyeX, sZoomPlanetCamEye.x, speed, 100.0f, 0.1f);
    Math_SmoothStepToF(&sPathFollowCamEyeY, sZoomPlanetCamEye.y, speed, 100.0f, 0.1f);
    Math_SmoothStepToF(&sMapCamEyeZ, sZoomPlanetCamEye.z, speed, 100.0f, 0.1f);

    x = sZoomPlanetCamEye.x - sPathFollowCamEyeX;
    y = sZoomPlanetCamEye.y - sPathFollowCamEyeY;
    z = sZoomPlanetCamEye.z - sMapCamEyeZ;

    temp = sqrtf(SQ(x) + SQ(y) + SQ(z));

    angle = M_DTOR * ((1 - (temp / D_menu_801CEA68)) * 180.0f);

    sMapCamEyeX = sPathFollowCamEyeX * (1 + __sinf(angle) * 1.1f);
    sMapCamEyeY = sPathFollowCamEyeY * (1 + __sinf(angle) * 1.3f);
}

void Map_801A4A38(f32 arg0) {
    Math_SmoothStepToF(&sPathFollowCamAtX, sZoomPlanetCamAt.x, arg0, 100.0f, 0.1f);
    Math_SmoothStepToF(&sPathFollowCamAtY, sZoomPlanetCamAt.y, arg0, 100.0f, 0.1f);
    Math_SmoothStepToF(&sMapCamAtZ, sZoomPlanetCamAt.z, arg0, 100.0f, 0.1f);
    sMapCamAtX = sPathFollowCamAtX;
    sMapCamAtY = sPathFollowCamAtY;
}

// Player selecting the next destination after Mission Accomplised
void Map_PathChange_Update(void) {
    s32 var_a0;
    s32 i;

    switch (D_menu_801CD94C) {
        case 0:
            Map_PathChange_Input();
            break;

        case 1:
            if (D_menu_801CF000[D_menu_801CEFDC] == 0) {
                if (D_menu_801CEFD0) {
                    if (gLifeCount[gPlayerNum] != 0) {
                        Audio_PlayDeathSequence();
                        sRestartLevelStates = 1;
                        sExplosionAnimIdx = 0;
                        sMapTimer1 = 120;
                    } else {
                        D_menu_801CD9D4 = 1;
                        sMapTimer1 = 0;
                    }
                } else {
                    sMapTimer1 = 0;
                }
                D_menu_801CEFC4 = 0;
                D_menu_801CD94C = 2;
            }
            break;

        case 2:
            if ((sRestartLevelStates != 0) && (sMapTimer1 == 110)) {
                gLifeCount[gPlayerNum]--;
            }

            if (sMapTimer1 == 0) {
                sRestartLevelStates = 0;

                var_a0 = D_menu_801CEFDC;
                if (sPrevMissionStatus != MISSION_COMPLETE) {
                    var_a0 += 2;
                }

                Map_PathChange_UpdateEntry(var_a0);

                if (D_menu_801CEFDC == 0) {
                    for (i = 0; i < TEAM_ID_MAX; i++) {
                        D_ctx_80177C58[i] = gTeamShields[i];
                    }
                    D_menu_801CEFC8 = 0;
                    sMapSubState = 0;
                    sMapState = MAP_ZOOM_PLANET;
                } else {
                    sMapState = MAP_IDLE;
                }
                D_menu_801CD94C = 0;
            }
            break;
    }
}

void Map_PathChange_UpdateEntry(u32 arg0) {
    switch (arg0) {
        case 1:
        case 4:
            if (D_menu_801CD9D4 != 0) {
                Map_GoToGameOver();
            } else {
                Map_RetryCourse();
            }
            break;

        case 3:
            Map_ChangePath();

        case 0:
        case 2:
            break;
    }
}

void Map_PathChange_Input(void) {
    f32 temp;

    if (Map_Input_CursorY() != 0) {
        D_menu_801CEFE8[D_menu_801CEFDC] = 255.0f;
        if (sPrevMissionStatus != MISSION_COMPLETE) {
            if (D_menu_801CEFD4 < 0) {
                D_menu_801CEFDC++;
                if (D_menu_801CEFDC >= 3) {
                    D_menu_801CEFDC = 0;
                }
            } else {
                D_menu_801CEFDC--;
                if (D_menu_801CEFDC < 0) {
                    D_menu_801CEFDC = 2;
                }
            }
        } else {
            D_menu_801CEFDC ^= 1;
        }
    }

    temp = Math_SmoothStepToF(&D_menu_801CEFE8[D_menu_801CEFDC], D_menu_801CEFE0, 0.5f, 100.0f, 1.0f);

    if (temp == 0.0f) {
        if (D_menu_801CEFE0 == 32.0f) {
            D_menu_801CEFE0 = 255.0f;
        } else {
            D_menu_801CEFE0 = 32.0f;
        }
    }

    if (gControllerPress[gMainController].button & (B_BUTTON | START_BUTTON)) {
        Audio_PlayMapMenuSfx(0);
        D_menu_801CEFC4 = 0;
        sMapState = MAP_IDLE;
    } else if (gControllerPress[gMainController].button & A_BUTTON) {
        Audio_PlayMapMenuSfx(0);
        AUDIO_PLAY_SFX(NA_SE_DECIDE, gDefaultSfxSource, 4);
        D_menu_801CF000[D_menu_801CEFDC] = 10;

        if (((sPrevMissionStatus != MISSION_COMPLETE) && (D_menu_801CEFDC == 2)) ||
            ((sPrevMissionStatus == MISSION_COMPLETE) && (D_menu_801CEFDC == 1))) {
            D_menu_801CEFD0 = true;
            D_menu_801CF00C = 10;
        }
        D_menu_801CD94C = 1;
    }
}

void Map_GoToGameOver(void) {
    gStarCount = 0;
    gGameState = GSTATE_GAME_OVER;
    D_ctx_80177868 = 0;
    gNextGameStateTimer = 2;
    gDrawMode = DRAW_NONE;
}

void Map_RetryCourse(void) {
    s32 i;
    s32 temp;
    s32 temp2;

    gPlayerNum = 0;

    for (i = 0; i < TEAM_ID_MAX; i++) {
        gSavedTeamShields[i] = D_ctx_80177C58[i];
        gTeamShields[i] = D_ctx_80177C58[i];
        gPrevPlanetTeamShields[i] = D_ctx_80177C58[i];
    }

    for (i = TEAM_ID_FALCO; i <= TEAM_ID_PEPPY; i++) {
        if (gPrevPlanetTeamShields[i] == 0) {
            gPrevPlanetTeamShields[i] = 255;
        }
    }

    gLaserStrength[gPlayerNum] = 0;
    gBombCount[gPlayerNum] = 3;

    if (sPlanets[sCurrentPlanetId].dest1 != PLANET_NONE) {
        temp2 = Map_GetPathId(sCurrentPlanetId, sPlanets[sCurrentPlanetId].dest1);
        gPlanetPathStatus[temp2] = 0;
        sPaths[temp2].alpha = 0;
    }

    if (sPlanets[sCurrentPlanetId].dest2 != PLANET_NONE) {
        temp = Map_GetPathId(sCurrentPlanetId, sPlanets[sCurrentPlanetId].dest2);
        gPlanetPathStatus[temp] = 0;
        sPaths[temp].alpha = 0;
    }

    if (sPlanets[sCurrentPlanetId].warp != PLANET_NONE) {
        temp = Map_GetPathId(sCurrentPlanetId, sPlanets[sCurrentPlanetId].warp);
        gPlanetPathStatus[temp] = 0;
        sPaths[temp].alpha = 0;
    }

    sPaths[D_menu_801CEECC].unk_14 = 0;
    D_menu_801CEEA0 = 0;
    D_menu_801CEEA4 = 0;
    D_menu_801CEEA8 = 255;
    D_menu_801CEEAC = 255;

    gTotalHits -= gMissionHitCount[gMissionNumber - 1];
    gMissionPlanet[gMissionNumber] = PLANET_NONE;
    gMissionHitCount[gMissionNumber - 1] = 0;
    gMissionMedal[gMissionNumber - 1] = 0;
    gMissionTeamStatus[gMissionNumber - 1] = TEAMSTATUS_ALIVE;
    gHitCount = 0;
    gMissionNumber--;

    D_menu_801CD83C = Map_801A05B4();

    sCurrentPlanetId = sPrevPlanetId;

    if (sPlanets[sCurrentPlanetId].dest1 != PLANET_NONE) {
        temp2 = Map_GetPathId(sCurrentPlanetId, sPlanets[sCurrentPlanetId].dest1);
        gPlanetPathStatus[temp2] = 1;
        sPaths[temp2].alpha = 255;
    }

    if (sPlanets[sCurrentPlanetId].dest2 != PLANET_NONE) {
        temp = Map_GetPathId(sCurrentPlanetId, sPlanets[sCurrentPlanetId].dest2);
        gPlanetPathStatus[temp] = 1;
        sPaths[temp].alpha = 255;
    }

    if (sPlanets[sCurrentPlanetId].warp != PLANET_NONE) {
        temp = Map_GetPathId(sCurrentPlanetId, sPlanets[sCurrentPlanetId].warp);
        gPlanetPathStatus[temp] = 0;
        sPaths[temp].alpha = 0;
    }

    Map_CurrentLevel_Setup();
}

void Map_ChangePath(void) {
    s32 temp;
    s32 temp2;

    D_menu_801CEFD8 ^= 1;

    if (sPlanets[sCurrentPlanetId].dest1 != PLANET_NONE) {
        temp2 = Map_GetPathId(sCurrentPlanetId, sPlanets[sCurrentPlanetId].dest1);
        gPlanetPathStatus[temp2] = 0;
        sPaths[temp2].alpha = 0;
    }

    if (sPlanets[sCurrentPlanetId].dest2 != PLANET_NONE) {
        temp = Map_GetPathId(sCurrentPlanetId, sPlanets[sCurrentPlanetId].dest2);
        gPlanetPathStatus[temp] = 0;
        sPaths[temp].alpha = 0;
    }

    gPlanetPathStatus[D_menu_801CEECC] = 0;

    sPaths[D_menu_801CEECC].alpha = 0;
    sPaths[D_menu_801CEECC].unk_14 = 0;

    sCurrentPlanetId = sPrevPlanetId;

    if (!D_menu_801CEFD8) {
        sNextPlanetId = sPlanets[sCurrentPlanetId].dest1;
    } else if (sPrevMissionStatus != MISSION_WARP) {
        if (sPlanets[sCurrentPlanetId].dest2 != PLANET_NONE) {
            sNextPlanetId = sPlanets[sCurrentPlanetId].dest2;
        } else {
            sNextPlanetId = sPlanets[sCurrentPlanetId].dest1;
        }
    } else if (sPlanets[sCurrentPlanetId].warp != PLANET_NONE) {
        sNextPlanetId = sPlanets[sCurrentPlanetId].warp;
    } else {
        sNextPlanetId = sPlanets[sCurrentPlanetId].dest1;
    }

    D_menu_801CEECC = Map_GetPathId(sCurrentPlanetId, sNextPlanetId);

    sPaths[D_menu_801CEECC].alpha = 255;

    gPlanetPathStatus[D_menu_801CEECC] = 3;

    sPaths[D_menu_801CEECC].unk_14 = 2;

    if ((sPaths[D_menu_801CEECC].type == PL_WARP_YLW) || (sPaths[D_menu_801CEECC].type == PL_WARP_RED)) {
        gPlanetPathStatus[D_menu_801CEECC] = 5;
        sPaths[D_menu_801CEECC].unk_14 = 5;
    }

    D_menu_801CEEA0 = 0;
    D_menu_801CEEA4 = 100;
    D_menu_801CEEA8 = 255;
    D_menu_801CEEAC = 255;

    sCurrentPlanetId = sNextPlanetId;
    gMissionPlanet[gMissionNumber] = sCurrentPlanetId;

    Map_CurrentLevel_Setup();

    if (sPlanets[sNextPlanetId].dest1 != PLANET_NONE) {
        temp2 = Map_GetPathId(sNextPlanetId, sPlanets[sNextPlanetId].dest1);
        gPlanetPathStatus[temp2] = 1;
        sPaths[temp2].alpha = 255;
    }

    if (sPlanets[sNextPlanetId].dest2 != PLANET_NONE) {
        temp = Map_GetPathId(sNextPlanetId, sPlanets[sNextPlanetId].dest2);
        gPlanetPathStatus[temp] = 1;
        sPaths[temp].alpha = 255;
    }
}

bool Map_Input_CursorY(void) {
    bool ret = false;
    s8 stickY = gControllerPress[gMainController].stick_y;

    if ((stickY > -40) && (stickY < 40)) {
        stickY = 0;
    }

    if (stickY != 0) {
        if (D_menu_801CEFD4 == 0) {
            ret = true;
        }
        D_menu_801CEFD4 = stickY;
    } else {
        D_menu_801CEFD4 = 0;
    }

    if (ret) {
        AUDIO_PLAY_SFX(NA_SE_CURSOR, gDefaultSfxSource, 4);
    }

    return ret;
}

void Map_PathChange_DrawOptions(void) {
    s32 i;
    f32 x;
    f32 y;
    f32 z;
    u8* texture;
    s32 colorIndex;
    s32 optionBgScaleIdx;
    s32 mask;
    s32 r[3];
    s32 g[3];
    s32 b[3];
    static f32 sMapOptionBgTexScales[] = { 3.05f, 4.15f };

    x = 101.0f;
    y = 92.0f;
    z = 0.0f;

    colorIndex = 0;

    for (i = 0; i < 3; i++) {
        r[i] = 64;
        g[i] = 64;
        b[i] = 64;
        if (i == D_menu_801CEFDC) {
            r[i] = 255;
            g[i] = D_menu_801CEFE8[i];
            b[i] = D_menu_801CEFE8[i];
        }
    }

    optionBgScaleIdx = 1;
    if (sPrevMissionStatus == MISSION_COMPLETE) {
        optionBgScaleIdx = 0;
    }

    if (gLifeCount[gPlayerNum] != 0) {
        texture = aMapRetryCourseLose1UPTex;
    } else {
        texture = aMapRetryCourseGameOverTex;
    }

    RCP_SetupDL(&gMasterDisp, SETUPDL_76);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 60, 60, 255, 170);

    Lib_TextureRect_IA8(&gMasterDisp, aMapOptionBgTex, 24, 17, x, y, 4.6f, sMapOptionBgTexScales[optionBgScaleIdx]);

    mask = 0xFFFFFFFF;
    if (D_menu_801CF000[colorIndex] != 0) {
        mask = 0x00000001;
        D_menu_801CF000[colorIndex]--;
    }

    if (gGameFrameCount & mask) { // can't be != 0?
        RCP_SetupDL(&gMasterDisp, SETUPDL_83_OPTIONAL);
        gDPSetPrimColor(gMasterDisp++, 0, 0, r[colorIndex], g[colorIndex], b[colorIndex], 255);
        Lib_TextureRect_IA8(&gMasterDisp, aMapProceedNextCourseTex, 96, 22, x + 11.0f, y + 3.0f, 1.0f, 1.0f);
    }
    z = 24.0f;
    colorIndex++;

    if (sPrevMissionStatus != MISSION_COMPLETE) {
        mask = 0xFFFFFFFF;
        if (D_menu_801CF000[colorIndex] != 0) {
            mask = 0x00000001;
            D_menu_801CF000[colorIndex]--;
        }

        if (gGameFrameCount & mask) { // can't be != 0?
            gDPSetPrimColor(gMasterDisp++, 0, 0, r[colorIndex], g[colorIndex], b[colorIndex], 255);
            Lib_TextureRect_IA8(&gMasterDisp, aMapChangeCourseTex, 96, 10, x + 10.0f, y + z + 8.0f, 1.0f, 1.0f);
        }
        z += 18.0f;
        colorIndex++;
    }

    mask = 0xFFFFFFFF;
    if (D_menu_801CF000[colorIndex] != 0) {
        mask = 0x00000001;
        D_menu_801CF000[colorIndex]--;
    }

    if ((gGameFrameCount & mask) != 0) {
        gDPSetPrimColor(gMasterDisp++, 0, 0, r[colorIndex], g[colorIndex], b[colorIndex], 255);
        Lib_TextureRect_IA8(&gMasterDisp, texture, 96, 22, x + 9.0f, y + z + 5.0f, 1.0f, 1.0f);
    }
}

void Map_RestartLevelLifeDown_Draw(void) {
    s32 pad[3];
    f32 scale;

    if (sRestartLevelStates != 0) {
        if (gLifeCount[gPlayerNum] < 10) {
            scale = 0.13f;
        } else {
            scale = 0.18f;
        }

        switch (sRestartLevelStates) {
            case 1:
                sMapTimer3 = 2;
                sRestartLevelStates = 2;
                break;

            case 2:
                if (sMapTimer3 != 0) {
                    break;
                }

                if ((sExplosionAnimIdx + 1) > 3) {
                    sExplosionAnimIdx = 0;
                    sRestartLevelStates = 0;
                } else {
                    sExplosionAnimIdx++;
                    sRestartLevelStates = 1;
                }
                break;
        }

        Matrix_Push(&gGfxMatrix);

        Matrix_LookAt(gGfxMatrix, 0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, MTXF_APPLY);

        Matrix_SetGfxMtx(&gMasterDisp);

        RCP_SetupDL(&gMasterDisp, SETUPDL_53);

        Matrix_Push(&gGfxMatrix);

        Matrix_Translate(gGfxMatrix, 45.0f, 32.0f, 0.01f, MTXF_APPLY);
        Matrix_Scale(gGfxMatrix, scale, scale, scale, MTXF_APPLY);

        Matrix_SetGfxMtx(&gMasterDisp);

        gSPDisplayList(gMasterDisp++, sExplosionAnimDLs[sExplosionAnimIdx]);

        Matrix_Pop(&gGfxMatrix);
    }
}

void Map_LevelStart_Update(void) {
    switch (sLevelStartState) {
        case 0:
            sWipeHeight = 0;
            D_menu_801CD9A0 = true;
            Map_CurrentLevel_Setup();
            sLevelPlayed = Map_LevelPlayedStatus_Check(sCurrentPlanetId);
            Map_BriefingRadio_Setup();
            sLevelStartState++;
            break;

        case 1:
            if ((gControllerPress[gMainController].button & START_BUTTON) && !sLevelPlayed) {
                Audio_KillSfxById(NA_SE_COMPUTER_NOISE);
                Audio_ClearVoice();
                D_menu_801CF018 = 0;
                sLevelStartState = 2;
                sMapTimer1 = 0;
            }

            if ((gControllerPress[gMainController].button & A_BUTTON) && (D_menu_801CD9A0 == false) && !sLevelPlayed) {
                Audio_ClearVoice();
                gRadioStateTimer = 0;
            }

            if ((gControllerPress[gMainController].button & A_BUTTON) && (D_menu_801CD9A0 == true) && !sLevelPlayed) {
                D_menu_801CD9A0 = false;
            }

            if (D_menu_801CF018 == 7) {
                sMapTimer1 = 5;
                sLevelStartState++;
            }
            break;

        case 2:
            if (sMapTimer1 != 0) {
                break;
            }

            if (sWipeHeight < 120) {
                sWipeHeight += 15;
                if (sCurrentPlanetId == PLANET_CORNERIA) {
                    sPlanetExplosions[EXPLOSIONS_CORNERIA] = false;
                }
            } else {
                sMapTimer1 = 5;
                D_menu_801CF018 = 0;
                sLevelStartState++;
            }
            break;

        case 3:
            if (sMapTimer1 == 0) {
                sMapTimer1 = 5;
                D_menu_801CD968 = 1;
                sLevelStartState++;
            }
            break;

        case 4:
            if (sMapTimer1 == 0) {
                AUDIO_PLAY_SFX(NA_SE_GOOD_LUCK, gDefaultSfxSource, 4);
                sMapTimer1 = 75;
                sLevelStartState++;
            }
            break;

        case 5:
            if (sMapTimer1 == 0) {
                Map_LevelStart_AudioSpecSetup(gCurrentLevel);
                sLevelStartState = 0;
                D_menu_801CD968 = 0;
                Map_PlayLevel();
            }
            break;
    }
}

void Map_LevelStart_AudioSpecSetup(LevelId level) {
    switch (level) {
        case LEVEL_CORNERIA:
            AUDIO_SET_SPEC(SFXCHAN_0, AUDIOSPEC_CO);
            break;

        case LEVEL_METEO:
            AUDIO_SET_SPEC(SFXCHAN_0, AUDIOSPEC_ME);
            break;

        case LEVEL_TITANIA:
            AUDIO_SET_SPEC(SFXCHAN_0, AUDIOSPEC_TI);
            break;

        case LEVEL_AQUAS:
            AUDIO_SET_SPEC(SFXCHAN_0, AUDIOSPEC_AQ);
            break;

        case LEVEL_BOLSE:
            AUDIO_SET_SPEC(SFXCHAN_0, AUDIOSPEC_BO);
            break;

        case LEVEL_KATINA:
            AUDIO_SET_SPEC(SFXCHAN_0, AUDIOSPEC_KA);
            break;

        case LEVEL_AREA_6:
            AUDIO_SET_SPEC(SFXCHAN_0, AUDIOSPEC_A6);
            break;

        case LEVEL_SECTOR_Z:
            AUDIO_SET_SPEC(SFXCHAN_0, AUDIOSPEC_SZ);
            break;

        case LEVEL_FORTUNA:
            AUDIO_SET_SPEC(SFXCHAN_0, AUDIOSPEC_FO);
            break;

        case LEVEL_SECTOR_X:
            AUDIO_SET_SPEC(SFXCHAN_0, AUDIOSPEC_SX);
            break;

        case LEVEL_MACBETH:
            AUDIO_SET_SPEC(SFXCHAN_0, AUDIOSPEC_MA);
            break;

        case LEVEL_ZONESS:
            AUDIO_SET_SPEC(SFXCHAN_0, AUDIOSPEC_ZO);
            break;

        case LEVEL_SECTOR_Y:
            AUDIO_SET_SPEC(SFXCHAN_0, AUDIOSPEC_SY);
            break;

        case LEVEL_SOLAR:
            AUDIO_SET_SPEC(SFXCHAN_2, AUDIOSPEC_SO);

        default:
            break;
    }
}

bool Map_LevelPlayedStatus_Check(PlanetId planet) {
    u32 planetSaveSlot;
    s32 played = true;

    switch (planet) {
        case PLANET_METEO:
        case PLANET_AREA_6:
        case PLANET_BOLSE:
        case PLANET_SECTOR_Z:
        case PLANET_SECTOR_X:
        case PLANET_SECTOR_Y:
        case PLANET_KATINA:
        case PLANET_MACBETH:
        case PLANET_ZONESS:
        case PLANET_CORNERIA:
        case PLANET_TITANIA:
        case PLANET_AQUAS:
        case PLANET_FORTUNA:
            planetSaveSlot = planet;
            break;

        case PLANET_SOLAR:
            planetSaveSlot = SAVE_SLOT_SOLAR;
            break;

        default:
            planetSaveSlot = planet;
            break;
    }

    if (CVarGetInteger("gLevelSelector", 0) && gMissionNumber == 6) {
        return false;
    }

    if (gSaveFile.save.data.planet[planetSaveSlot].played & 1) {
        played = false;
    }

    return played;
}

void Map_CurrentLevel_Setup(void) {
    switch (sCurrentPlanetId) {
        case PLANET_CORNERIA:
            gCurrentLevel = LEVEL_CORNERIA;
            break;

        case PLANET_METEO:
            gCurrentLevel = LEVEL_METEO;
            break;

        case PLANET_TITANIA:
            gCurrentLevel = LEVEL_TITANIA;
            break;

        case PLANET_AQUAS:
            gCurrentLevel = LEVEL_AQUAS;
            break;

        case PLANET_BOLSE:
            gCurrentLevel = LEVEL_BOLSE;
            break;

        case PLANET_KATINA:
            gCurrentLevel = LEVEL_KATINA;
            break;

        case PLANET_AREA_6:
            gCurrentLevel = LEVEL_AREA_6;
            break;

        case PLANET_SECTOR_Z:
            gCurrentLevel = LEVEL_SECTOR_Z;
            break;

        case PLANET_FORTUNA:
            gCurrentLevel = LEVEL_FORTUNA;
            break;

        case PLANET_SECTOR_X:
            gCurrentLevel = LEVEL_SECTOR_X;
            break;

        case PLANET_MACBETH:
            gCurrentLevel = LEVEL_MACBETH;
            break;

        case PLANET_ZONESS:
            gCurrentLevel = LEVEL_ZONESS;
            break;

        case PLANET_SECTOR_Y:
            gCurrentLevel = LEVEL_SECTOR_Y;
            break;

        case PLANET_VENOM:
            gCurrentLevel = LEVEL_VENOM_1;
            break;

        case PLANET_SOLAR:
            gCurrentLevel = LEVEL_SOLAR;

        default:
            break;
    }
}

PlanetId Map_GetPlanetId(LevelId level) {
    PlanetId planet;

    switch (level) {
        case LEVEL_CORNERIA:
            planet = PLANET_CORNERIA;
            break;

        case LEVEL_METEO:
            planet = PLANET_METEO;
            break;

        case LEVEL_TITANIA:
            planet = PLANET_TITANIA;
            break;

        case LEVEL_AQUAS:
            planet = PLANET_AQUAS;
            break;

        case LEVEL_BOLSE:
            planet = PLANET_BOLSE;
            break;

        case LEVEL_KATINA:
            planet = PLANET_KATINA;
            break;

        case LEVEL_AREA_6:
            planet = PLANET_AREA_6;
            break;

        case LEVEL_SECTOR_Z:
            planet = PLANET_SECTOR_Z;
            break;

        case LEVEL_FORTUNA:
            planet = PLANET_FORTUNA;
            break;

        case LEVEL_SECTOR_X:
            planet = PLANET_SECTOR_X;
            break;

        case LEVEL_MACBETH:
            planet = PLANET_MACBETH;
            break;

        case LEVEL_ZONESS:
            planet = PLANET_ZONESS;
            break;

        case LEVEL_SECTOR_Y:
            planet = PLANET_SECTOR_Y;
            break;

        case LEVEL_VENOM_1:
        case LEVEL_VENOM_ANDROSS:
        case LEVEL_VENOM_2:
            planet = PLANET_VENOM;
            break;

        case LEVEL_SOLAR:
            planet = PLANET_SOLAR;
    }

    return planet;
}

s32 Map_GetPathId(PlanetId start, PlanetId end) {
    s32 i;

    for (i = 0; i < 24; i++) {
        if ((sPaths[i].start == start) && (sPaths[i].end == end)) {
            break;
        }
    }

    return i;
}

void Map_SetState_ZoomPlanet(void) {
    Audio_KillSfxById(NA_SE_MAP_MOVE);
    Audio_KillSfxById(NA_SE_MAP_ROLL);

    if (sCurrentPlanetId != PLANET_CORNERIA) {
        AUDIO_PLAY_SFX(NA_SE_DECIDE, gDefaultSfxSource, 4);
    }

    D_menu_801CEFC8 = 0;
    sMapState = MAP_ZOOM_PLANET;
    sMapSubState = 0;
}

void Map_PlayLevel(void) {
    gGameState = GSTATE_PLAY;
    gNextGameStateTimer = 2;
    gPlayState = PLAY_STANDBY;
    gDrawMode = DRAW_NONE;
    gHitCount = 0;

    Play_Setup();

    gSavedObjectLoadIndex = 0;
    gSavedPathProgress = 0.0f;
    D_ctx_8017782C = true;
}

void Map_PositionPlanets(void) {
    PlanetId planetId;
    Vec3f dest;
    Vec3f src;

    src.x = 0.0f;
    src.y = 0.0f;
    src.z = 0.0f;

    for (planetId = 0; planetId < PLANET_MAX; planetId++) {
        Matrix_Push(&gGfxMatrix);

        Matrix_RotateY(gGfxMatrix, M_DTOR * sPlanets[planetId].longitude, MTXF_APPLY);
        Matrix_Translate(gGfxMatrix, sPlanets[planetId].orbit.radius, sPlanets[planetId].orbit.incl, 0.0f, MTXF_APPLY);

        Matrix_RotateY(gGfxMatrix, M_DTOR * -sPlanets[planetId].longitude, MTXF_APPLY);

        Map_CamMatrixRot();

        Matrix_SetGfxMtx(&gMasterDisp);

        Matrix_Copy(&D_menu_801CDA60[planetId], gGfxMatrix);

        Matrix_MultVec3f(gGfxMatrix, &src, &dest);

        sPlanets[planetId].pos.x = dest.x;
        sPlanets[planetId].pos.y = dest.y;
        sPlanets[planetId].pos.z = dest.z;

        Matrix_Pop(&gGfxMatrix);

        Matrix_Push(&gGfxMatrix);

        Matrix_LookAt(gGfxMatrix, sMapCamEyeX, sMapCamEyeY, sMapCamEyeZ, sMapCamAtX, sMapCamAtY, sMapCamAtZ, sMapCamUpX,
                      sMapCamUpY, sMapCamUpZ, MTXF_APPLY);
        Matrix_Translate(gGfxMatrix, D_menu_801CEA58, D_menu_801CEA5C, D_menu_801CEA60, MTXF_APPLY);
        Matrix_Mult(gGfxMatrix, &D_menu_801CDA60[planetId], MTXF_APPLY);

        Matrix_SetGfxMtx(&gMasterDisp);

        Matrix_MultVec3f(gGfxMatrix, &src, &sPlanetPositions[planetId]);

        Matrix_Pop(&gGfxMatrix);
    }
}

void Map_PlanetOrderZpos(void) {
    s32 i;
    s32 j;
    s32 var_a0;

    for (i = 0; i < 14; i++) {
        for (j = i; j < 15; j++) {
            if (sPlanetPositions[D_menu_801CD8A0[i]].z > sPlanetPositions[D_menu_801CD8A0[j]].z) {
                var_a0 = D_menu_801CD8A0[i];
                D_menu_801CD8A0[i] = D_menu_801CD8A0[j];
                D_menu_801CD8A0[j] = var_a0;
            }
        }
    }
}

void Map_Fade_Update(void) {
    switch (D_menu_801CD960) {
        case 0:
            if (gFillScreenAlpha != 0) {
                gFillScreenAlpha -= 5;
            } else {
                D_menu_801CD960 = 255;
            }
            break;

        case 1:
            if (gFillScreenAlpha != 255) {
                gFillScreenAlpha += 15;
            } else {
                D_menu_801CD960 = 255;
            }
            break;
    }
}

void Map_Planet_Draw(PlanetId planetId) {
    s32 mask;
    PlanetStatus planetStatus;

    if ((sPlanets[planetId].alpha == 0) && (planetId != sCurrentPlanetId)) {
        return;
    }

    if ((planetId == sCurrentPlanetId) && (sMapState == MAP_ZOOM_PLANET) && (D_menu_801CD95C != 0)) {
        mask = 0x00000001;
    } else {
        mask = 0xFFFFFFFF;
    }

    planetStatus = Map_CheckPlanetMedal(planetId);
    Map_PlanetAnim2(planetId);
    Map_PlanetCleared2_Draw(planetId);

    Matrix_Push(&gGfxMatrix);

    if ((gGameFrameCount & mask) != 0) {
        if (planetId == PLANET_TITANIA) {
            Map_Titania_DrawRings1(planetId);
        }

        if ((planetStatus == PLANET_CLEARED) && (sPlanetPositions[planetId].z > D_menu_801CEA18[planetId]) &&
            (planetId != PLANET_AREA_6) && (planetId != PLANET_BOLSE)) {
            Map_PlanetCleared_Draw(planetId);
        }

        Map_PlanetAnim(planetId);

        if (planetId == PLANET_SOLAR) {
            Map_SolarRays_Draw(planetId);
        }

        if (sPlanets[planetId].anim == PL_ANIM_SPIN) {
            if (planetId != PLANET_VENOM) {
                if ((planetId != PLANET_AQUAS) && (planetId != PLANET_TITANIA)) {
                    Map_VenomCloud2_Draw(planetId);
                }
                Map_PlanetShadow_Draw(planetId);
            }
            if (planetId == PLANET_VENOM) {
                Map_VenomCloud_Draw(&D_menu_801CEEBC, +0.1f, 3.1f);
                Map_VenomCloud_Draw(&D_menu_801CEEC0, -0.1f, 2.9f);
            }
        }

        if (planetId == PLANET_TITANIA) {
            Map_Titania_DrawRings2(planetId);
        }

        if ((planetId == PLANET_CORNERIA) && sPlanetExplosions[EXPLOSIONS_CORNERIA]) {
            Map_PlanetExplosions_Draw(PLANET_CORNERIA, EXPLOSIONS_CORNERIA);
        }

        if ((planetId == PLANET_KATINA) && sPlanetExplosions[EXPLOSIONS_KATINA]) {
            Map_PlanetExplosions_Draw(PLANET_KATINA, EXPLOSIONS_KATINA);
        }

        if ((planetId == PLANET_SECTOR_Y) && sPlanetExplosions[EXPLOSIONS_SECTOR_Y]) {
            Map_PlanetExplosions_Draw(PLANET_SECTOR_Y, EXPLOSIONS_SECTOR_Y);
        }

        if ((planetStatus == PLANET_CLEARED) && (sPlanetPositions[planetId].z <= D_menu_801CEA18[planetId]) &&
            (planetId != PLANET_AREA_6) && (planetId != PLANET_BOLSE)) {
            Map_PlanetCleared_Draw(planetId);
        }

        if ((planetStatus == PLANET_CLEARED) && ((planetId == PLANET_AREA_6) || (planetId == PLANET_BOLSE))) {
            Map_PlanetCleared_Draw(planetId);
        }

        if (planetStatus == PLANET_MEDAL) {
            Map_PlanetMedal_Draw(planetId);
        }
    }
    Matrix_Pop(&gGfxMatrix);
}

s32 Map_CheckPlanetMedal(PlanetId planetId) {
    s32 ret;
    s32 planetSaveSlot;
    bool medal;
    bool clear;

    if (planetId == PLANET_VENOM) {
        if (gExpertMode) {
            medal = gSaveFile.save.data.planet[SAVE_SLOT_VENOM_2].expertMedal & 1;
            clear = gSaveFile.save.data.planet[SAVE_SLOT_VENOM_1].expertClear & 1 |
                    gSaveFile.save.data.planet[SAVE_SLOT_VENOM_2].expertClear & 1;
        } else {
            medal = gSaveFile.save.data.planet[SAVE_SLOT_VENOM_2].normalMedal & 1;
            clear = gSaveFile.save.data.planet[SAVE_SLOT_VENOM_1].normalClear & 1 |
                    gSaveFile.save.data.planet[SAVE_SLOT_VENOM_2].normalClear & 1;
        }
    } else {
        planetSaveSlot = planetId;

        if (planetId == PLANET_SOLAR) {
            planetSaveSlot = SAVE_SLOT_SOLAR;
        }

        if (gExpertMode) {
            medal = gSaveFile.save.data.planet[planetSaveSlot].expertMedal & 1;
            clear = gSaveFile.save.data.planet[planetSaveSlot].expertClear & 1;
        } else {
            medal = gSaveFile.save.data.planet[planetSaveSlot].normalMedal & 1;
            clear = gSaveFile.save.data.planet[planetSaveSlot].normalClear & 1;
        }
    }

    ret = 0; // Has no medal or hasn't been cleared
    if (medal) {
        ret = 2; // Has medal
    } else if (clear) {
        ret = 1; // Has been cleared
    }

    return ret;
}

void Map_PlanetAnim2(PlanetId planetId) {
    f32 dirX;
    f32 dirY;
    f32 dirZ;
    Vec3f dst;
    Vec3f src;
    f32 x1;
    f32 y1;
    f32 x2;
    f32 y2;
    f32 z2;

    src.x = 0.0f;
    src.y = 0.0f;
    src.z = 0.0f;

    Matrix_Push(&gGfxMatrix);

    // @port: Tag the transform.
    FrameInterpolation_RecordOpenChild("Map_PlanetAnim2", planetId);

    Matrix_Mult(gGfxMatrix, &D_menu_801CDA60[planetId], MTXF_APPLY);

    if (sPlanets[planetId].anim == PL_ANIM_ROTATE_Y) {
        if (planetId == PLANET_BOLSE) {
            Matrix_RotateX(gGfxMatrix, M_DTOR * D_menu_801AFFF8, MTXF_APPLY);
            Matrix_RotateY(gGfxMatrix, M_DTOR * D_menu_801AFFF4, MTXF_APPLY);
        } else {
            Matrix_RotateX(gGfxMatrix, M_DTOR * D_menu_801B0000, MTXF_APPLY);
            Matrix_RotateY(gGfxMatrix, M_DTOR * D_menu_801AFFFC, MTXF_APPLY);
        }
    }

    Matrix_RotateZ(gGfxMatrix, M_DTOR * (sPlanets[planetId].orbit.tilt), MTXF_APPLY);

    Matrix_Scale(gGfxMatrix, sPlanets[planetId].scale, sPlanets[planetId].scale, sPlanets[planetId].scale, MTXF_APPLY);

    Matrix_SetGfxMtx(&gMasterDisp);

    if (sPlanets[planetId].anim == PL_ANIM_ROTATE_Y) {
        x2 = sPlanetPositions[PLANET_SOLAR].x - sPlanetPositions[planetId].x;
        y2 = sPlanetPositions[PLANET_SOLAR].y - sPlanetPositions[planetId].y;
        z2 = sPlanetPositions[PLANET_SOLAR].z - sPlanetPositions[planetId].z;

        x1 = Math_Atan2F(y2, sqrtf(SQ(x2) + SQ(z2)));
        y1 = -Math_Atan2F(x2, z2);

        src.x = 0.0f;
        src.y = 0.0f;
        src.z = 100.0f;

        Matrix_RotateY(gCalcMatrix, M_DTOR * (-D_menu_801CDA10 - y1), MTXF_NEW);
        Matrix_RotateX(gCalcMatrix, M_DTOR * (-D_menu_801CDA0C - x1), MTXF_APPLY);

        Matrix_MultVec3f(gCalcMatrix, &src, &dst);

        dirX = dst.x;
        dirY = dst.y;
        dirZ = dst.z;
        Lights_SetOneLight(&gMasterDisp, dirX, dirY, dirZ, 80, 80, 60, 10, 10, 8);
    }

    Matrix_Copy(&D_menu_801CDE20[planetId], gGfxMatrix);

    Matrix_Pop(&gGfxMatrix);

    // @port Pop the transform id.
    FrameInterpolation_RecordCloseChild();

    D_menu_801AFFF4 += 0.1f;
    D_menu_801AFFFC -= 0.09f;
}

void Map_PlanetAnim(PlanetId planetId) {
    switch (sPlanets[planetId].anim) {
        case PL_ANIM_STATIC:
            if (((sMapState == MAP_IDLE) || (planetId == sCurrentPlanetId) || (planetId == sNextPlanetId)) &&
                (sMapState != MAP_LYLAT_CARD) && sMapState != MAP_GAME_OVER) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_53);
            } else {
                RCP_SetupDL(&gMasterDisp, SETUPDL_41);
                gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, sPlanets[planetId].alpha);
            }
            break;

        case PL_ANIM_ROTATE_Y:
            if (((sMapState == MAP_IDLE) || (planetId == sCurrentPlanetId) || (planetId == sNextPlanetId)) &&
                (sMapState != MAP_LYLAT_CARD) && (sMapState != MAP_GAME_OVER)) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_23);
            } else {
                RCP_SetupDL(&gMasterDisp, SETUPDL_46);
                gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, sPlanets[planetId].alpha);
            }
            break;

        case PL_ANIM_BILLBOARD:
        case PL_ANIM_SPIN:
            RCP_SetupDL(&gMasterDisp, SETUPDL_64);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, sPlanets[planetId].alpha);
            break;

        case PL_ANIM_ROTATE_Z:
            RCP_SetupDL(&gMasterDisp, SETUPDL_67);

            gDPSetPrimColor(gMasterDisp++, 0, 0, 240, 0, 0, sPlanets[planetId].alpha);
            gDPSetEnvColor(gMasterDisp++, 31, 0, 0, 0);

            sPlanets[planetId].orbit.tilt += 0.1f;
            break;
    }

    Matrix_Push(&gGfxMatrix);

    // @port: Tag the transform.
    FrameInterpolation_RecordOpenChild("TAG_PLANET_ANIM", planetId);

    Matrix_Copy(gGfxMatrix, &D_menu_801CDE20[planetId]);
    Matrix_SetGfxMtx(&gMasterDisp);

    gSPDisplayList(gMasterDisp++, sMapPlanets[sPlanets[planetId].id]);

    Matrix_Pop(&gGfxMatrix);

    // @port Pop the transform id.
    FrameInterpolation_RecordCloseChild();
}

void Map_SolarRays_Draw(PlanetId planetId) {
    static f32 D_menu_801B6A74 = 0.0f;
    s32 alpha = sPlanets[PLANET_VENOM].alpha;

    if (sPlanets[planetId].alpha > 128) {
        alpha = 128;
    }

    RCP_SetupDL(&gMasterDisp, SETUPDL_67);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, alpha);
    gDPSetEnvColor(gMasterDisp++, 31, 0, 0, 0);

    Matrix_Push(&gGfxMatrix);

    // @port: Tag the transform.
    FrameInterpolation_RecordOpenChild("TAG_SOLAR_RAYS", planetId);

    Matrix_Copy(gGfxMatrix, &D_menu_801CDE20[planetId]);
    Matrix_RotateZ(gGfxMatrix, M_DTOR * D_menu_801B6A74, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, 0.8f, 0.8f, 0.8f, MTXF_APPLY);

    Matrix_SetGfxMtx(&gMasterDisp);

    gSPDisplayList(gMasterDisp++, sMapPlanets[sPlanets[planetId].id]);

    Matrix_Pop(&gGfxMatrix);

    // @port Pop the transform id.
    FrameInterpolation_RecordCloseChild();

    D_menu_801B6A74 -= 0.2f;
}

void Map_VenomCloud2_Draw(PlanetId planetId) {
    s32 r;
    s32 g;
    s32 b;

    r = g = b = 255;

    if (planetId == PLANET_MACBETH) {
        r = g = b = 64;
    }

    RCP_SetupDL(&gMasterDisp, SETUPDL_64);

    gDPSetPrimColor(gMasterDisp++, 0, 0, r, g, b, sPlanets[planetId].alpha);

    Matrix_Push(&gGfxMatrix);

    // @port: Tag the transform.
    FrameInterpolation_RecordOpenChild("TAG_VENOM_CLOUD_2", planetId);

    Matrix_Copy(gGfxMatrix, &D_menu_801CDE20[planetId]);
    Matrix_SetGfxMtx(&gMasterDisp);

    gSPDisplayList(gMasterDisp++, gMapVenomCloudDL);

    Matrix_Pop(&gGfxMatrix);

    // @port Pop the transform id.
    FrameInterpolation_RecordCloseChild();
}

void Map_PlanetShadow_Draw(PlanetId planetId) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_64);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, sPlanets[planetId].alpha);

    Matrix_Push(&gGfxMatrix);

    // @port: Tag the transform.
    FrameInterpolation_RecordOpenChild("TAG_PLANET_SHADOW", planetId);

    Matrix_Copy(gGfxMatrix, &D_menu_801CDE20[planetId]);

    if ((planetId == PLANET_TITANIA) || (planetId == PLANET_MACBETH) || (planetId == PLANET_ZONESS)) {
        Matrix_RotateY(gGfxMatrix, M_DTOR * 180.0f, MTXF_APPLY);
    }

    Matrix_RotateZ(gGfxMatrix, M_DTOR * sPlanets[planetId].orbit.tilt, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, 1.6f, 1.6f, 1.6f, MTXF_APPLY);

    Matrix_SetGfxMtx(&gMasterDisp);

    gSPDisplayList(gMasterDisp++, D_MAP_605C230);

    Matrix_Pop(&gGfxMatrix);

    // @port Pop the transform id.
    FrameInterpolation_RecordCloseChild();
}

void Map_Titania_DrawRings1(PlanetId planetId) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_67);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 175, 175, sPlanets[planetId].alpha);
    gDPSetEnvColor(gMasterDisp++, 73, 31, 15, 0);

    Matrix_Push(&gGfxMatrix);

    // @port: Tag the transform.
    FrameInterpolation_RecordOpenChild("TAG_TITANIA_RINGS", planetId);

    Matrix_Copy(gGfxMatrix, &D_menu_801CDE20[planetId]);

    Matrix_RotateZ(gGfxMatrix, M_DTOR * -sPlanets[planetId].orbit.tilt, MTXF_APPLY);
    Matrix_RotateX(gGfxMatrix, M_DTOR * 20.0f, MTXF_APPLY);

    Matrix_Scale(gGfxMatrix, 3.0f, 3.0f, 3.0f, MTXF_APPLY);

    Matrix_SetGfxMtx(&gMasterDisp);

    gSPDisplayList(gMasterDisp++, aMapTitaniaRings1DL);

    Matrix_Pop(&gGfxMatrix);

    // @port Pop the transform id.
    FrameInterpolation_RecordCloseChild();
}

void Map_Titania_DrawRings2(PlanetId planetId) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_67);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 175, 175, sPlanets[planetId].alpha);
    gDPSetEnvColor(gMasterDisp++, 73, 31, 15, 0);

    Matrix_Push(&gGfxMatrix);

    // @port: Tag the transform.
    FrameInterpolation_RecordOpenChild("TAG_TITANIA_RINGS", planetId);

    Matrix_Copy(gGfxMatrix, &D_menu_801CDE20[planetId]);
    Matrix_RotateZ(gGfxMatrix, M_DTOR * -sPlanets[planetId].orbit.tilt, MTXF_APPLY);
    Matrix_RotateX(gGfxMatrix, M_DTOR * 20.0f, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, 3.0f, 3.0f, 3.0f, MTXF_APPLY);

    Matrix_SetGfxMtx(&gMasterDisp);

    gSPDisplayList(gMasterDisp++, aMapTitaniaRings2DL);

    Matrix_Pop(&gGfxMatrix);

    // @port Pop the transform id.
    FrameInterpolation_RecordCloseChild();
}

void Map_VenomCloud_Draw(f32* zAngle, f32 next, f32 scale) {
    s32 alpha = sPlanets[PLANET_VENOM].alpha;

    if (sPlanets[PLANET_VENOM].alpha > 128) {
        alpha = 128;
    }

    RCP_SetupDL(&gMasterDisp, SETUPDL_67);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 63, 95, 30, alpha);
    gDPSetEnvColor(gMasterDisp++, 0, 0, 0, 0);

    Matrix_Push(&gGfxMatrix);

    // @port: Tag the transform.
    FrameInterpolation_RecordOpenChild("TAG_VENOM_CLOUD_1", 0);

    Matrix_Copy(gGfxMatrix, &D_menu_801CDE20[PLANET_VENOM]);
    Matrix_RotateZ(gGfxMatrix, M_DTOR * (*zAngle), MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, scale, scale, scale, MTXF_APPLY);

    Matrix_SetGfxMtx(&gMasterDisp);

    // @port This should be aMapVenomCloudDL but torch is stupid sometimes
    u8* buffer = SEGMENTED_TO_VIRTUAL(aMapVenomCloudEffectTex);
    gSPVertex(gMasterDisp++, ast_map_seg6_vtx_47F00, 8, 0);
    gDPLoadTextureBlock(gMasterDisp++, buffer, G_IM_FMT_IA, G_IM_SIZ_8b, 64, 33, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSP2Triangles(gMasterDisp++, 1, 2, 3, 0, 1, 3, 0, 0);
    gDPLoadTextureBlock(gMasterDisp++, buffer + 64 * 32, G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSP2Triangles(gMasterDisp++, 5, 6, 7, 0, 5, 7, 4, 0);

    Matrix_Pop(&gGfxMatrix);

    // @port Pop the transform id.
    FrameInterpolation_RecordCloseChild();

    *zAngle += next;
}

void Map_PlanetCleared2_Draw(PlanetId planetId) {
    Vec3f src;
    Vec3f dest;
    f32 scale;

    src.x = 0.0f;
    src.y = 0.0f;
    src.z = 0.0f;

    scale = 7.0f + RAND_FLOAT(8.0f);

    Matrix_Push(&gGfxMatrix);

    // @port: Tag the transform.
    FrameInterpolation_RecordOpenChild("Map_PlanetCleared2_Draw", planetId);

    Matrix_Mult(gGfxMatrix, &D_menu_801CDA60[planetId], MTXF_APPLY);
    Matrix_RotateY(gGfxMatrix, M_DTOR * D_menu_801CEAF8[planetId], MTXF_APPLY);
    Matrix_Translate(gGfxMatrix, D_menu_801AFFB8[planetId], 0.0f, 0.0f, MTXF_APPLY);
    Matrix_RotateY(gGfxMatrix, M_DTOR * -D_menu_801CEAF8[planetId], MTXF_APPLY);

    Matrix_SetGfxMtx(&gMasterDisp);

    Matrix_Copy(&D_menu_801CE5A0[planetId], gGfxMatrix);
    Matrix_RotateZ(gGfxMatrix, M_DTOR * D_menu_801CEAB8[planetId], MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, scale, scale, scale, MTXF_APPLY);
    Matrix_MultVec3f(gGfxMatrix, &src, &dest);

    D_menu_801CEA18[planetId] = dest.z;

    Matrix_SetGfxMtx(&gMasterDisp);

    Matrix_Copy(&D_menu_801CE1E0[planetId], gGfxMatrix);

    Matrix_Pop(&gGfxMatrix);

    // @port Pop the transform id.
    FrameInterpolation_RecordCloseChild();
}

void Map_PlanetCleared_Draw(PlanetId planetId) {
    s32 alpha;

    if (D_menu_801CD980 != true) {
        alpha = D_menu_801CD900[planetId];
    } else {
        alpha = D_menu_801CD984;
        D_menu_801CD900[planetId] = 255;
    }

    if (alpha != 0) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_67);

        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, alpha);
        gDPSetEnvColor(gMasterDisp++, 80, 80, 0, 0);

        Matrix_Push(&gGfxMatrix);

        // @port: Tag the transform.
        FrameInterpolation_RecordOpenChild("Map_PlanetCleared_Draw", planetId);

        Matrix_Copy(gGfxMatrix, &D_menu_801CE1E0[planetId]);
        Matrix_SetGfxMtx(&gMasterDisp);

        gSPDisplayList(gMasterDisp++, D_MAP_604D680);

        Matrix_Pop(&gGfxMatrix);

        // @port Pop the transform id.
        FrameInterpolation_RecordCloseChild();

        D_menu_801CEAB8[planetId] += 45.0f;
        if (D_menu_801CD980 == false) {
            D_menu_801CEAF8[planetId] += 5.0f;
        }
    }
}

void Map_PlanetMedal_Draw(PlanetId planetId) {
    static f32 D_menu_801B6A78 = 0.0f;
    s32 i;
    s32 alpha;
    f32 scale;

    if (D_menu_801CD98C != 1) {
        alpha = D_menu_801CD900[planetId];
    } else {
        alpha = D_menu_801CD984;
        D_menu_801CD900[planetId] = 255;
    }

    if (alpha == 0) {
        return;
    }

    if (D_menu_801CD98C == 1) {
        switch (D_menu_801CD990) {
            case 0:
                RCP_SetupDL(&gMasterDisp, SETUPDL_67);

                gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, alpha);
                gDPSetEnvColor(gMasterDisp++, 80, 80, 0, 0);

                Matrix_Push(&gGfxMatrix);

                // @port: Tag the transform.
                FrameInterpolation_RecordOpenChild("TAG_MEDAL", planetId);

                Matrix_Copy(gGfxMatrix, &D_menu_801CE1E0[planetId]);
                Matrix_Translate(gGfxMatrix, 0.0f, -30.0f, 0.0f, MTXF_APPLY);

                Matrix_SetGfxMtx(&gMasterDisp);

                gSPDisplayList(gMasterDisp++, D_MAP_604D680);

                Matrix_Pop(&gGfxMatrix);

                // @port Pop the transform id.
                FrameInterpolation_RecordCloseChild();

                D_menu_801CEAB8[planetId] += 45.0f;
                if (alpha == 255) {
                    D_menu_801CD9C8 = 15;
                    D_menu_801CD998 = 0;
                    D_menu_801CD994 = 255;
                    D_menu_801CD99C = 0.0f;
                    D_menu_801CD990++;
                }
                break;

            case 1:
                scale = 5.0f + RAND_FLOAT(4.0f);

                Math_SmoothStepToF(&D_menu_801CD99C, 150.0f, 0.09f, 100.0f, 0.1f);

                RCP_SetupDL(&gMasterDisp, SETUPDL_67);

                gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, D_menu_801CD994);
                gDPSetEnvColor(gMasterDisp++, 80, 80, 0, 0);

                for (i = 0; i < 8; i++) {
                    Matrix_Push(&gGfxMatrix);
                    // @port: Tag the transform.
                    FrameInterpolation_RecordOpenChild("TAG_MEDAL_1", planetId + i);
                    Matrix_Copy(gGfxMatrix, &D_menu_801CE5A0[planetId]);
                    Matrix_Translate(gGfxMatrix, 0.0f, -30.0f, 0.0f, MTXF_APPLY);
                    Matrix_RotateZ(gGfxMatrix, M_DTOR * (i * -45.0f), MTXF_APPLY);
                    Matrix_Translate(gGfxMatrix, 0.0f, D_menu_801CD99C, 0.0f, MTXF_APPLY);
                    Matrix_RotateZ(gGfxMatrix, M_DTOR * (D_menu_801B6A78), MTXF_APPLY);
                    Matrix_Scale(gGfxMatrix, scale, scale, scale, MTXF_APPLY);

                    Matrix_SetGfxMtx(&gMasterDisp);

                    gSPDisplayList(gMasterDisp++, D_MAP_604D680);

                    Matrix_Pop(&gGfxMatrix);

                    // @port Pop the transform id.
                    FrameInterpolation_RecordCloseChild();
                }

                D_menu_801B6A78 += 45.0f;
                D_menu_801CD994 -= 16;

                if (D_menu_801CD994 <= 0) {
                    D_menu_801CD994 = 0;
                }

                RCP_SetupDL(&gMasterDisp, SETUPDL_64);

                gDPSetTextureFilter(gMasterDisp++, G_TF_POINT);
                gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, D_menu_801CD998);

                Matrix_Push(&gGfxMatrix);

                // @port: Tag the transform.
                FrameInterpolation_RecordOpenChild("TAG_MEDAL_2", planetId);

                Matrix_Copy(gGfxMatrix, &D_menu_801CE5A0[planetId]);
                Matrix_Translate(gGfxMatrix, 0.0f, -30.0f, 0.0f, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, 3.0f, 3.0f, 3.0f, MTXF_APPLY);

                Matrix_SetGfxMtx(&gMasterDisp);

                gSPDisplayList(gMasterDisp++, aMapMedalDL);

                Matrix_Pop(&gGfxMatrix);

                // @port Pop the transform id.
                FrameInterpolation_RecordCloseChild();

                D_menu_801CEAF8[planetId] = -90.0f;

                D_menu_801CD998 += 8;

                if (D_menu_801CD998 == 8) {
                    AUDIO_PLAY_SFX(NA_SE_GET_EMBLEM, gDefaultSfxSource, 4);
                }

                if (D_menu_801CD998 >= 255) {
                    D_menu_801CD998 = 255;
                }
                if (D_menu_801CD998 == 255) {
                    if (!D_menu_801CD9C8) {
                        D_menu_801CD98C = 0;
                    } else {
                        D_menu_801CD9C8--;
                    }
                }
                break;
        }
    } else {
        RCP_SetupDL(&gMasterDisp, SETUPDL_64);

        gDPSetTextureFilter(gMasterDisp++, G_TF_POINT);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, alpha);

        Matrix_Push(&gGfxMatrix);

        // @port: Tag the transform.
        FrameInterpolation_RecordOpenChild("TAG_MEDAL_3", planetId);

        Matrix_Copy(gGfxMatrix, &D_menu_801CE5A0[planetId]);
        Matrix_Translate(gGfxMatrix, 0.0f, -30.0f, 0.0f, MTXF_APPLY);
        Matrix_Scale(gGfxMatrix, 3.0f, 3.0f, 3.0f, MTXF_APPLY);

        Matrix_SetGfxMtx(&gMasterDisp);

        gSPDisplayList(gMasterDisp++, aMapMedalDL);

        Matrix_Pop(&gGfxMatrix);

        // @port Pop the transform id.
        FrameInterpolation_RecordCloseChild();

        D_menu_801CEAF8[planetId] = -90.0f;
    }
}

void Map_CorneriaExplosion_Draw(void) {
    if (D_menu_801CEB34 >= 0) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_67);

        gDPSetEnvColor(gMasterDisp++, 255, 0, 0, 0);

        switch (D_menu_801CEB34) {
            case 0:
                sMapCorneriaExplosionScale += 0.15f;
                if (sMapCorneriaExplosionScale >= 0.7f) {
                    sMapCorneriaExplosionScale = 0.8f;
                    D_menu_801CEB34 = 2;
                    D_menu_801CEB40 = 2.0f;
                }
                break;

            case 2:
                D_menu_801CEB40--;
                if (D_menu_801CEB40 <= 0.0f) {
                    D_menu_801CEB34 = 3;
                    sMapCorneriaExplosionScale = 0.7f;
                }
                break;

            case 3:
                D_menu_801CEB38 -= 8;
                sMapCorneriaExplosionScale -= 0.001f;

                if (D_menu_801CEB38 < 0) {
                    D_menu_801CEB38 = 0;
                }

                if (D_menu_801CEB38 == 0) {
                    D_menu_801CEB34 = 4;
                }
                break;
        }

        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 200, 200, D_menu_801CEB38);

        Matrix_Push(&gGfxMatrix);

        // @port: Tag the transform.
        FrameInterpolation_RecordOpenChild("CORNERIA_EXPLOSION", 0);

        Matrix_Copy(gGfxMatrix, &D_menu_801CDE20[PLANET_CORNERIA]);
        Matrix_RotateZ(gGfxMatrix, M_DTOR * -50.0f, MTXF_APPLY);
        Matrix_Translate(gGfxMatrix, 0.0f, 25.0f, 0.0f, MTXF_APPLY);
        Matrix_Scale(gGfxMatrix, sMapCorneriaExplosionScale, sMapCorneriaExplosionScale, sMapCorneriaExplosionScale,
                     MTXF_APPLY);

        Matrix_SetGfxMtx(&gMasterDisp);

        gSPDisplayList(gMasterDisp++, aMapPlanetExplosionDL);

        Matrix_Pop(&gGfxMatrix);

        // @port Pop the transform id.
        FrameInterpolation_RecordCloseChild();
    }
}

void Map_PlanetExplosions_Draw(PlanetId planetId, PlanetExplosions explosionIdx) {
    s32 i;
    s32 temp2;
    f32 temp;

    if (sPlanets[planetId].alpha == 0) {
        return;
    }

    if (!sPlanetExplosions[explosionIdx]) {
        return;
    }

    temp2 = 10;
    if (planetId != PLANET_CORNERIA) {
        temp2 = 5;
    }

    RCP_SetupDL(&gMasterDisp, SETUPDL_67);

    gDPSetEnvColor(gMasterDisp++, 255, 0, 0, 0);

    for (i = 0; i < temp2; i++) {
        switch (D_menu_801CEB58[explosionIdx][i]) {
            case 0:
                D_menu_801CEC48[explosionIdx][i] += 0.1f;
                if (D_menu_801CEC48[explosionIdx][i] >= D_menu_801CECC0[explosionIdx][i]) {
                    D_menu_801CEC48[explosionIdx][i] = D_menu_801CECC0[explosionIdx][i];
                    D_menu_801CEB58[explosionIdx][i] = 1;
                }
                break;

            case 1:
                D_menu_801CEE28[explosionIdx][i]--;
                if (D_menu_801CEE28[explosionIdx][i] <= 0) {
                    D_menu_801CEB58[explosionIdx][i] = 2;
                }
                break;

            case 2:
                D_menu_801CEBD0[explosionIdx][i] -= 48;
                if (D_menu_801CEBD0[explosionIdx][i] < 0) {
                    D_menu_801CEBD0[explosionIdx][i] = 0;
                    D_menu_801CEB58[explosionIdx][i] = 3;
                }
                break;

            case 3:
                D_menu_801CEB58[explosionIdx][i] = RAND_INT(3.0f);
                D_menu_801CEBD0[explosionIdx][i] = 255;
                D_menu_801CEC48[explosionIdx][i] = 0.0f;
                D_menu_801CECC0[explosionIdx][i] = 0.5f + RAND_FLOAT(0.3f);
                D_menu_801CEE28[explosionIdx][i] = 1 + RAND_INT(4.0f);

                temp = 110.0f;
                if (explosionIdx == EXPLOSIONS_KATINA) {
                    temp = 50.0f;
                }

                D_menu_801CED38[explosionIdx][i] = temp + RAND_INT(30.0f);
                D_menu_801CEDB0[explosionIdx][i] = -10.0f + RAND_FLOAT(-60.0f);
                break;
        }

        if ((D_menu_801CECC0[explosionIdx][i] == 0.0f) || (D_menu_801CEBD0[explosionIdx][i] == 0)) {
            continue;
        }

        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 200, 200, D_menu_801CEBD0[explosionIdx][i]);

        Matrix_Push(&gGfxMatrix);

        // @port Skip interpolation
        FrameInterpolation_ShouldInterpolateFrame(false);

        Matrix_Mult(gGfxMatrix, &D_menu_801CDA60[planetId], MTXF_APPLY);
        Matrix_RotateZ(gGfxMatrix, M_DTOR * D_menu_801CEDB0[explosionIdx][i], MTXF_APPLY);
        Matrix_Translate(gGfxMatrix, 0.0f, D_menu_801CED38[explosionIdx][i], 0.0f, MTXF_APPLY);
        Matrix_Scale(gGfxMatrix, D_menu_801CEC48[explosionIdx][i], D_menu_801CEC48[explosionIdx][i],
                     D_menu_801CEC48[explosionIdx][i], MTXF_APPLY);

        Matrix_SetGfxMtx(&gMasterDisp);

        gSPDisplayList(gMasterDisp++, aMapPlanetExplosionDL);

        // @port renable interpolation
        FrameInterpolation_ShouldInterpolateFrame(true);

        Matrix_Pop(&gGfxMatrix);
    }
}

void Map_Cursor_draw(void) {
    static f32 D_menu_801B6A7C = 0.0f;
    s32 temp;

    if (D_menu_801CD97C != 0) {
        Lights_SetOneLight(&gMasterDisp, 0, 0, 127, 80, 80, 60, 50, 50, 50);

        RCP_SetupDL(&gMasterDisp, SETUPDL_23);

        temp = Math_SmoothStepToF(&sCursorYpos, D_menu_801CEAB0, 0.1f, 100.0f, 1.0f);
        if (temp == 0.0f) {
            if (D_menu_801CEAB0 == D_menu_801CEAAC) {
                sCursorYpos = D_menu_801CEAAC + 50.0f;
            }
        }

        Matrix_Push(&gGfxMatrix);

        // @port Skip interpolation
        FrameInterpolation_ShouldInterpolateFrame(false);

        Matrix_Mult(gGfxMatrix, &D_menu_801CDA60[sCurrentPlanetId], MTXF_APPLY);
        Matrix_Translate(gGfxMatrix, 0.0f, sCursorYpos, 0.0f, MTXF_APPLY);
        Matrix_RotateY(gGfxMatrix, M_DTOR * D_menu_801B6A7C, MTXF_APPLY);
        Matrix_Scale(gGfxMatrix, 3.0f, 3.0f, 3.0f, MTXF_APPLY);

        Matrix_SetGfxMtx(&gMasterDisp);

        gSPDisplayList(gMasterDisp++, aMapCursorDL);

        // @port renable interpolation
        FrameInterpolation_ShouldInterpolateFrame(true);

        Matrix_Pop(&gGfxMatrix);

        D_menu_801B6A7C += 6.0f;
    }
}

void Map_PositionCursor(void) {
    sCursorYpos = 140.0f;

    if (sCurrentPlanetId == PLANET_CORNERIA) {
        sCursorYpos = 230.0f;
    }

    if (sCurrentPlanetId == PLANET_AREA_6) {
        sCursorYpos = 210.0f;
    }

    if (sCurrentPlanetId == PLANET_SOLAR) {
        sCursorYpos = 250.0f;
    }

    if (sCurrentPlanetId == PLANET_SECTOR_X) {
        sCursorYpos = 150.0f;
    }

    if (sCurrentPlanetId == PLANET_SECTOR_Y) {
        sCursorYpos = 150.0f;
    }

    if (sCurrentPlanetId == PLANET_SECTOR_Z) {
        sCursorYpos = 150.0f;
    }

    if (sCurrentPlanetId == PLANET_VENOM) {
        sCursorYpos = 300.0f;
    }

    D_menu_801CEAAC = sCursorYpos;
    D_menu_801CEAB0 = sCursorYpos;
}

void Map_MeteoMeteors_Draw(void) {
    s32 i;
    s32 mask;

    if ((sPlanets[PLANET_METEO].alpha != 0) || (sCurrentPlanetId == PLANET_METEO)) {
        if ((sCurrentPlanetId == PLANET_METEO) && (sMapState == MAP_ZOOM_PLANET) && (D_menu_801CD95C != 0)) {
            mask = 0x00000001;
        } else {
            mask = 0xFFFFFFFF;
        }

        if ((sMapState == MAP_IDLE) || ((sCurrentPlanetId == PLANET_METEO) && (sMapState != MAP_GAME_OVER))) {
            RCP_SetupDL(&gMasterDisp, SETUPDL_53);
        } else {
            RCP_SetupDL(&gMasterDisp, SETUPDL_64);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, sPlanets[PLANET_METEO].alpha);
        }

        if ((gGameFrameCount & mask) != 0) {
            for (i = 0; i < ARRAY_COUNT(sMapMeteors); i++) {
                Matrix_Push(&gGfxMatrix);

                // @port: Tag the transform.
                FrameInterpolation_RecordOpenChild("TAG_PLANET_METEOR", i);

                Matrix_RotateY(gGfxMatrix, M_DTOR * sMapMeteors[i].angle, MTXF_APPLY);
                Matrix_Translate(gGfxMatrix, sMapMeteors[i].x, sMapMeteors[i].y, 0.0f, MTXF_APPLY);
                Matrix_RotateY(gGfxMatrix, M_DTOR * -sMapMeteors[i].angle, MTXF_APPLY);

                Map_CamMatrixRot();

                Matrix_Scale(gGfxMatrix, sMapMeteors[i].scale, sMapMeteors[i].scale, sMapMeteors[i].scale, MTXF_APPLY);

                Matrix_SetGfxMtx(&gMasterDisp);

                gSPDisplayList(gMasterDisp++, sMapPlanets[PLANET_METEO]);

                Matrix_Pop(&gGfxMatrix);

                // @port Pop the transform id.
                FrameInterpolation_RecordCloseChild();
            }
        }
    }
}

void Map_Area6Ships_Draw(void) {
    Vec3f src;
    Vec3f dest;
    f32 x1;
    f32 y1;
    f32 x;
    f32 y;
    f32 z;
    s32 i;
    s32 mask;
    static f32 D_menu_801B6A80 = -22.0f;

    if ((sPlanets[PLANET_AREA_6].alpha == 0) && (sCurrentPlanetId != PLANET_AREA_6)) {
        return;
    }

    if ((sCurrentPlanetId == PLANET_AREA_6) && (sMapState == MAP_ZOOM_PLANET) && (D_menu_801CD95C != 0)) {
        mask = 0x00000001;
    } else {
        mask = 0xFFFFFFFF;
    }

    if ((sMapState == MAP_IDLE) || (sCurrentPlanetId == PLANET_AREA_6)) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_23);
    } else {
        RCP_SetupDL(&gMasterDisp, SETUPDL_46);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, sPlanets[PLANET_AREA_6].alpha);
    }

    dest.x = 0.0f;
    dest.y = 0.0f;
    dest.z = 0.0f;

    if ((gGameFrameCount & mask) != 0) {
        for (i = 0; i < ARRAY_COUNT(sMapArea6Ships); i++) {
            Matrix_Push(&gGfxMatrix);

            // @port Tag the transform.
            FrameInterpolation_RecordOpenChild("TAG_AREA6_SHIPS", 0);

            Matrix_RotateY(gGfxMatrix, M_DTOR * sMapArea6Ships[i].angle, MTXF_APPLY);
            Matrix_Translate(gGfxMatrix, sMapArea6Ships[i].x, sMapArea6Ships[i].y, 0.0f, MTXF_APPLY);
            Matrix_RotateY(gGfxMatrix, M_DTOR * -(sMapArea6Ships[i].angle), MTXF_APPLY);

            Map_CamMatrixRot();

            Matrix_RotateY(gGfxMatrix, M_DTOR * D_menu_801B6A80, MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, sMapArea6Ships[i].scale, sMapArea6Ships[i].scale, sMapArea6Ships[i].scale,
                         MTXF_APPLY);

            Matrix_SetGfxMtx(&gMasterDisp);

            Matrix_MultVec3f(gGfxMatrix, &dest, &src);

            x = sPlanetPositions[PLANET_SOLAR].x - src.x;
            y = sPlanetPositions[PLANET_SOLAR].y - src.y;
            z = sPlanetPositions[PLANET_SOLAR].z - src.z;

            x1 = Math_Atan2F(y, sqrtf(SQ(x) + SQ(z)));
            y1 = -Math_Atan2F(x, z);

            dest.x = 0.0f;
            dest.y = 0.0f;
            dest.z = 100.0f;

            Matrix_RotateY(gCalcMatrix, M_DTOR * (-D_menu_801CDA10 - y1), MTXF_NEW);
            Matrix_RotateX(gCalcMatrix, M_DTOR * (-D_menu_801CDA0C - x1), MTXF_APPLY);

            Matrix_MultVec3f(gCalcMatrix, &dest, &src);
            Lights_SetOneLight(&gMasterDisp, src.x, src.y, src.z, 80, 80, 60, 0, 0, 0);

            gSPDisplayList(gMasterDisp++, aMapArea6ShipDL);

            Matrix_Pop(&gGfxMatrix);

            // @port Pop the transform id.
            FrameInterpolation_RecordCloseChild();
        }
    }
}

void Map_Wipe_Draw(void) {
    if (sLevelStartState != 0) {
        Matrix_Push(&gGfxMatrix);
        Matrix_LookAt(gGfxMatrix, sMapCamEyeX, sMapCamEyeY, sMapCamEyeZ, sMapCamAtX, sMapCamAtY, sMapCamAtZ, sMapCamUpX,
                      sMapCamUpY, sMapCamUpZ, MTXF_APPLY);
        Matrix_Translate(gGfxMatrix, D_menu_801CEA58, D_menu_801CEA5C, D_menu_801CEA60, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        Wipe_Draw(WIPE_VERTICAL, sWipeHeight);
        Matrix_Pop(&gGfxMatrix);
    }
}

void Map_TitleCards_Draw(void) {
    static s32 sMapCurPlanetCards[] = { 1, 13, 12, 11, 6, 2, 4, 10, 8, 0, 9, 5, 3, 7, 7 };
    s32 i;
    s32 planetCardIdx = sMapCurPlanetCards[sCurrentPlanetId];

    RCP_SetupDL(&gMasterDisp, SETUPDL_83_OPTIONAL);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, (s32) sMapPlanetCardAlpha);

    Lib_TextureRect_IA8(&gMasterDisp, sPlanetNameCards[planetCardIdx].texture, sPlanetNameCards[planetCardIdx].width,
                        sPlanetNameCards[planetCardIdx].height, sPlanetNameCards[planetCardIdx].xPos, 20.0f, 1.0f,
                        1.0f);

    Math_SmoothStepToF(&sMapPlanetCardAlpha, 255.0f, sMapPlanetCardAlphaScale, 10.0f, 1.0f);

    sMapPlanetCardAlphaScale *= 1.08;
}

void Map_801A9A8C(void) {
    s32 i;
    s32 planetIdx;
    u8* missionNoTex;
    static f32 sCardXpos[2] = { 91.0f, 207.0f };
    static f32 sCardYpos[2] = { 61.0f, 61.0f };

    switch (gCurrentLevel) {
        case LEVEL_CORNERIA:
            missionNoTex = aLargeText_1;
            planetIdx = 0;
            break;

        case LEVEL_METEO:
            missionNoTex = aLargeText_2;
            planetIdx = 1;
            break;

        case LEVEL_SECTOR_Y:
            missionNoTex = aLargeText_2;
            planetIdx = 2;
            break;

        case LEVEL_FORTUNA:
            missionNoTex = aLargeText_3;
            planetIdx = 3;
            break;

        case LEVEL_KATINA:
            missionNoTex = aLargeText_3;
            planetIdx = 4;
            break;

        case LEVEL_AQUAS:
            missionNoTex = aLargeText_3;
            planetIdx = 5;
            break;

        case LEVEL_SECTOR_X:
            missionNoTex = aLargeText_4;
            planetIdx = 6;
            break;

        case LEVEL_SOLAR:
            missionNoTex = aLargeText_4;
            planetIdx = 7;
            break;

        case LEVEL_ZONESS:
            missionNoTex = aLargeText_4;
            planetIdx = 8;
            break;

        case LEVEL_TITANIA:
            missionNoTex = aLargeText_5;
            planetIdx = 9;
            break;

        case LEVEL_MACBETH:
            missionNoTex = aLargeText_5;
            planetIdx = 10;
            break;

        case LEVEL_SECTOR_Z:
            missionNoTex = aLargeText_5;
            planetIdx = 11;
            break;

        case LEVEL_BOLSE:
            missionNoTex = aLargeText_6;
            planetIdx = 12;
            break;

        case LEVEL_AREA_6:
            missionNoTex = aLargeText_6;
            planetIdx = 13;
            break;
    }

    RCP_SetupDL(&gMasterDisp, SETUPDL_83_OPTIONAL);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    if (CVarGetInteger("gLevelSelector", 0) && gMissionNumber == 6) {
        return;
    }

    Lib_TextureRect_IA8(&gMasterDisp, aTextMissionNo, 112, 19, sCardXpos[0], sCardYpos[0], 1.0f, 1.0f);
    Lib_TextureRect_IA8(&gMasterDisp, missionNoTex, 16, 15, sCardXpos[1], sCardYpos[1], 1.0f, 1.0f);

    Lib_TextureRect_IA8(&gMasterDisp, sPlanetNameCards[planetIdx].texture, sPlanetNameCards[planetIdx].width,
                        sPlanetNameCards[planetIdx].height, sPlanetNameCards[planetIdx].xPos, 94.0f, 1.0f, 1.0f);

    Lib_TextureRect_IA8(&gMasterDisp, sPlanetTitleCards[planetIdx].texture, sPlanetTitleCards[planetIdx].width,
                        sPlanetTitleCards[planetIdx].height, sPlanetTitleCards[planetIdx].xPos, 140.0f, 1.0f, 1.0f);
}

void Map_801A9DE8(void) {
    s32 mask;

    if ((D_menu_801CD978 == 0) && !((sMapState == MAP_IDLE) || (sMapState == MAP_PATH_CHANGE) ||
                                    ((sMapState == MAP_GAME_OVER) && (sMapSubState == 2)))) {
        return;
    }

    mask = 0xFFFFFFFF;
    if (D_menu_801CF00C != 0) {
        mask = 0x00000001;
        D_menu_801CF00C--;
    }

    if ((gGameFrameCount & mask) != 0) {
        Map_RemainingLives_Draw(254, 16, gLifeCount[gPlayerNum]);
    }

    if ((gLastGameState == GSTATE_PLAY) || (gLastGameState == GSTATE_GAME_OVER)) {
        if (D_menu_801CD83C < gTotalHits) {
            D_menu_801CD83C = gTotalHits;
        }
        Map_TotalHits_Draw();
        Map_801A9FD4(false);
    }
}

void Map_TotalHits_Draw(void) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_83_OPTIONAL);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);

    Graphics_DisplaySmallText(24, 14, 1.0f, 1.0f, "TOTAL HITS");
    Graphics_DisplaySmallNumber(71 - (HUD_CountDigits(gTotalHits) * 8), 24, gTotalHits);
    Graphics_DisplaySmallText(143, 14, 1.0f, 1.0f, "TOP");
    Graphics_DisplaySmallNumber(167 - (HUD_CountDigits(D_menu_801CD83C) * 8), 24, D_menu_801CD83C);
}

void Map_801A9FD4(bool arg0) {
    s32 i;
    s32 curMission;
    f32 var_fs0, var_fs1;
    s32 pad[2];
    f32 temp = 16.0f;

    if (arg0) {
        curMission = gMissionNumber;
    } else {
        if ((gLastGameState == GSTATE_PLAY) || (gLastGameState == GSTATE_ENDING)) {
            curMission = gMissionNumber;
        }
        if (gLastGameState == GSTATE_GAME_OVER) {
            curMission = D_menu_801CD9AC;
        }
    }

    Map_PathLineBox_Draw(curMission);

    if ((gLastGameState == GSTATE_PLAY) || (gLastGameState == GSTATE_ENDING)) {
        curMission = 7;
    }

    if (gLastGameState == GSTATE_GAME_OVER) {
        curMission++;
    }

    Matrix_Push(&gGfxMatrix);

    Matrix_LookAt(gGfxMatrix, 0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, MTXF_APPLY);

    Matrix_SetGfxMtx(&gMasterDisp);

    for (var_fs0 = 0.0f, var_fs1 = -41.5f, i = 0; i < curMission; i++, var_fs0 += 24.0f + temp, var_fs1 += 13.8f) {
        if (gMissionPlanet[i] != PLANET_NONE) {
            Map_PathInfo_Draw(i, 28.0f + var_fs0, 182.0f, gMissionPlanet[i]);
            Map_PathPlanet_Draw(i, var_fs1, -25.4f, gMissionPlanet[i]);
        }
    }

    Matrix_Pop(&gGfxMatrix);
}

void Map_PathLineBox_Draw(s32 curMission) {
    s32 i;
    f32 x;
    s32 r;
    s32 g;
    s32 b;
    s32 pathId;
    f32 y = 182.0f;
    f32 x2 = 16.0f;
    PlanetId* ptr = &gMissionPlanet[0];

    for (x = 0.0f, i = 0; i < 7; i++, x += 24.0f + x2, ptr++) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_83_OPTIONAL);

        if (i < 6) {
            r = g = b = 255;
            if (i < curMission) {
                pathId = Map_GetPathId(*ptr, *(ptr + 1));
                switch (sPaths[pathId].type) {
                    case 0:
                        r = 16;
                        g = 64;
                        b = 255;
                        break;

                    case 1:
                    case 3:
                        r = 255;
                        g = 175;
                        b = 0;
                        break;

                    case 2:
                    case 4:
                        g = b = 0;
                        break;
                }
                gDPSetPrimColor(gMasterDisp++, 0, 0, r, g, b, 255);
            } else {
                gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
            }
            Lib_TextureRect_RGBA16(&gMasterDisp, aMapWhiteSquareTex, 8, 8, 28.0f + x + 24.0f, y + 11.0f, 2.0f, 0.2f);
        }
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
        Lib_TextureRect_RGBA16(&gMasterDisp, aMapPathBoxTex, 24, 24, 28.0f + x, y, 1.0f, 1.0f);
    }
}

void Map_PathInfo_Draw(s32 missionIdx, f32 x, f32 y, s32 idx) {
    s32 i;
    f32 x2;
    s32 pad;
    s32 mask;
    s32 curMission;
    static char* D_menu_801B6AD0[] = { "P", "S", "F" };
    static s32 D_menu_801B6ADC[] = { 255, 0, 30 };
    static s32 D_menu_801B6AE8[] = { 30, 179, 30 };
    static s32 D_menu_801B6AF4[] = { 0, 67, 255 };

    RCP_SetupDL(&gMasterDisp, SETUPDL_83_OPTIONAL);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);

    Graphics_DisplaySmallText(x + 12.0f - Graphics_GetSmallTextWidth(sPlanetNames[idx]) * 0.5f, y - 8.0f, 1.0f, 1.0f,
                              sPlanetNames[idx]);

    Graphics_DisplaySmallNumber(x + 15.0f - ((HUD_CountDigits(gMissionHitCount[missionIdx]) - 1) * 8), y + 24.0f + 1.0f,
                                gMissionHitCount[missionIdx]);

    if (gLastGameState == GSTATE_PLAY) {
        curMission = gMissionNumber;
    }

    if ((gLastGameState == GSTATE_GAME_OVER) || (gLastGameState == GSTATE_ENDING)) {
        curMission = gMissionNumber + 1;
    }

    if (missionIdx < curMission) {
        mask = 0x00FF0000;
        x2 = 0.0f;
        for (i = 0; i < 3; i++, x2 += 9.0f) {
            if ((gMissionTeamStatus[missionIdx] & mask) != 0) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_83_OPTIONAL);
                gDPSetPrimColor(gMasterDisp++, 0, 0, D_menu_801B6ADC[i], D_menu_801B6AE8[i], D_menu_801B6AF4[i], 255);
                Graphics_DisplaySmallText((s32) x + x2 - 1.0f, (s32) y + 24.0f + 8.0f + 2.0f, 1.0f, 1.0f,
                                          D_menu_801B6AD0[i]);
            }
            mask >>= 8;
        }
    }
}

void Map_PathPlanet_Draw(s32 missionIdx, f32 x, f32 y, PlanetId planetId) {
    s32 mask = 0xFFFFFFFF;

    if ((gGameState == GSTATE_MAP) && (planetId == sCurrentPlanetId)) {
        mask = 0x00000010;
    }

    switch (planetId) {
        case PLANET_SOLAR:
            if ((gGameFrameCount & mask) != 0) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_67);

                gDPSetPrimColor(gMasterDisp++, 0, 0, 240, 0, 0, 255);
                gDPSetEnvColor(gMasterDisp++, 31, 0, 0, 0);

                Matrix_Push(&gGfxMatrix);

                // @port: Tag the transform.
                FrameInterpolation_RecordOpenChild("Map_PathPlanet_Draw", planetId);

                Matrix_Translate(gGfxMatrix, x, y, 0.0f, MTXF_APPLY);
                Matrix_RotateZ(gGfxMatrix, M_DTOR * (sPlanets[planetId].orbit.tilt), MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, 0.11f, 0.11f, 0.11f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);

                gSPDisplayList(gMasterDisp++, sMapPlanets[sPlanets[planetId].id]);

                gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 128);
                gDPSetEnvColor(gMasterDisp++, 31, 0, 0, 0);

                Matrix_Scale(gGfxMatrix, 0.8f, 0.8f, 0.8f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);

                gSPDisplayList(gMasterDisp++, sMapPlanets[sPlanets[planetId].id]);

                Matrix_Pop(&gGfxMatrix);

                // @port Pop the transform id.
                FrameInterpolation_RecordCloseChild();
            }
            break;

        case PLANET_METEO:
            if ((gGameFrameCount & mask) != 0) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_62);

                gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

                Matrix_Push(&gGfxMatrix);

                // @port: Tag the transform.
                FrameInterpolation_RecordOpenChild("Map_PathPlanet_Draw", planetId);

                Matrix_Translate(gGfxMatrix, x - 0.4f, y + 0.9f, 0.0f, MTXF_APPLY);
                Matrix_RotateZ(gGfxMatrix, M_DTOR * sPlanets[planetId].orbit.tilt, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, 0.1f, 0.1f, 0.1f, MTXF_APPLY);

                Matrix_SetGfxMtx(&gMasterDisp);

                gSPDisplayList(gMasterDisp++, sMapPlanets[sPlanets[planetId].id]);

                Matrix_Translate(gGfxMatrix, 18.0f, -20.0f, 0.0f, MTXF_APPLY);

                Matrix_SetGfxMtx(&gMasterDisp);

                gSPDisplayList(gMasterDisp++, sMapPlanets[sPlanets[planetId].id]);

                Matrix_Pop(&gGfxMatrix);

                // @port Pop the transform id.
                FrameInterpolation_RecordCloseChild();
            }
            break;

        case PLANET_SECTOR_X:
        case PLANET_SECTOR_Y:
        case PLANET_SECTOR_Z:
            if ((gGameFrameCount & mask) != 0) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_62);

                gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 144);

                Matrix_Push(&gGfxMatrix);

                // @port: Tag the transform.
                FrameInterpolation_RecordOpenChild("Map_PathPlanet_Draw", planetId);

                Matrix_Translate(gGfxMatrix, x, y, 0.0f, MTXF_APPLY);
                Matrix_RotateZ(gGfxMatrix, M_DTOR * sPlanets[planetId].orbit.tilt, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, 0.09f, 0.09f, 0.09f, MTXF_APPLY);

                Matrix_SetGfxMtx(&gMasterDisp);

                gSPDisplayList(gMasterDisp++, sMapPlanets[sPlanets[planetId].id]);

                Matrix_Pop(&gGfxMatrix);

                // @port Pop the transform id.
                FrameInterpolation_RecordCloseChild();
            }
            break;

        case PLANET_BOLSE:
            if ((gGameFrameCount & mask) != 0) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_23);

                Lights_SetOneLight(&gMasterDisp, 0, 0, 100, 50, 50, 40, 100, 100, 100);

                Matrix_Push(&gGfxMatrix);

                // @port: Tag the transform.
                FrameInterpolation_RecordOpenChild("Map_PathPlanet_Draw", planetId);

                Matrix_Translate(gGfxMatrix, x, y, 0.0f, MTXF_APPLY);
                Matrix_RotateX(gGfxMatrix, M_DTOR * 20.0f, MTXF_APPLY);
                Matrix_RotateY(gGfxMatrix, M_DTOR * D_menu_801AFFF4, MTXF_APPLY);
                Matrix_RotateZ(gGfxMatrix, M_DTOR * sPlanets[planetId].orbit.tilt, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, 0.004f, 0.004f, 0.004f, MTXF_APPLY);

                Matrix_SetGfxMtx(&gMasterDisp);

                gSPDisplayList(gMasterDisp++, sMapPlanets[sPlanets[planetId].id]);

                Matrix_Pop(&gGfxMatrix);

                // @port Pop the transform id.
                FrameInterpolation_RecordCloseChild();
            }
            break;

        case PLANET_AREA_6:
            if ((gGameFrameCount & mask) != 0) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_23);

                Lights_SetOneLight(&gMasterDisp, 0, 0, 100, 50, 50, 40, 100, 100, 100);

                Matrix_Push(&gGfxMatrix);

                // @port: Tag the transform.
                FrameInterpolation_RecordOpenChild("Map_PathPlanet_Draw", planetId);

                Matrix_Translate(gGfxMatrix, x, y, 0.0f, MTXF_APPLY);
                Matrix_RotateX(gGfxMatrix, M_DTOR * 20.0f, MTXF_APPLY);
                Matrix_RotateY(gGfxMatrix, M_DTOR * D_menu_801AFFFC, MTXF_APPLY);
                Matrix_RotateZ(gGfxMatrix, M_DTOR * sPlanets[planetId].orbit.tilt, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, 0.003f, 0.003f, 0.003f, MTXF_APPLY);

                Matrix_SetGfxMtx(&gMasterDisp);

                gSPDisplayList(gMasterDisp++, sMapPlanets[sPlanets[planetId].id]);

                Matrix_Pop(&gGfxMatrix);

                // @port Pop the transform id.
                FrameInterpolation_RecordCloseChild();
            }
            break;

        default:
            if ((gGameFrameCount & mask) != 0) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_62);

                gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

                Matrix_Push(&gGfxMatrix);

                // @port: Tag the transform.
                FrameInterpolation_RecordOpenChild("Map_PathPlanet_Draw", planetId);

                Matrix_Translate(gGfxMatrix, x, y, 0.0f, MTXF_APPLY);
                Matrix_RotateZ(gGfxMatrix, M_DTOR * sPlanets[planetId].orbit.tilt, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, 0.1f, 0.1f, 0.1f, MTXF_APPLY);

                Matrix_SetGfxMtx(&gMasterDisp);

                gSPDisplayList(gMasterDisp++, sMapPlanets[sPlanets[planetId].id]);

                if (sPlanets[planetId].anim == PL_ANIM_SPIN) {
                    if (planetId != PLANET_VENOM && planetId != PLANET_AQUAS) {
                        Matrix_SetGfxMtx(&gMasterDisp);
                        if (planetId == PLANET_MACBETH) {
                            gDPSetPrimColor(gMasterDisp++, 0, 0, 64, 64, 64, 255);
                        } else {
                            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
                        }
                        gSPDisplayList(gMasterDisp++, gMapVenomCloudDL);
                    }
                    Matrix_Scale(gGfxMatrix, 1.6f, 1.6f, 1.6f, MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_MAP_605C230);
                }

                Matrix_Pop(&gGfxMatrix);

                // @port Pop the transform id.
                FrameInterpolation_RecordCloseChild();
            }
            break;
    }

    if (gMissionMedal[missionIdx] != 0) {
        Map_PathPlanetMedal_Draw(x, y, 0.0f);
    }
}

void Map_PathPlanetMedal_Draw(f32 x, f32 y, f32 z) {
    static f32 scale = 0.23f;
    static f32 xPos = 4.4f;
    static f32 yPos = 1.0f;

    RCP_SetupDL(&gMasterDisp, SETUPDL_53);
    gDPSetTextureFilter(gMasterDisp++, G_TF_POINT);

    Matrix_Push(&gGfxMatrix);

    // @port: Tag the transform.
    FrameInterpolation_RecordOpenChild("Map_PathPlanetMedal_Draw", (int) (x + y + z));

    Matrix_Translate(gGfxMatrix, x - xPos, y + yPos, z, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, scale, scale, scale, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);

    gSPDisplayList(gMasterDisp++, aMapMedalDL);

    Matrix_Pop(&gGfxMatrix);

    // @port Pop the transform id.
    FrameInterpolation_RecordCloseChild();
}

void Map_BriefingRadio_Setup(void) {
    D_menu_801CD940 = 0;
    gRadioMsg = SEGMENTED_TO_VIRTUAL(sBriefingMsg[sCurrentPlanetId][D_menu_801CD940]);
    gRadioMsgRadioId = D_menu_801AF420[D_menu_801CD940];
    D_menu_801CF018 = 100;
    gRadioPrintPosX = 78;
    gRadioPrintPosY = 166;
}

void Map_BriefingRadio_Update(void) {
    if (gRadioStateTimer > 0) {
        gRadioStateTimer--;
    }
    if (gRadioMouthTimer > 0) {
        gRadioMouthTimer--;
    }

    switch (D_menu_801CF018) {
        case 0:
            break;

        case 100:
            sTeamStatusAlpha = 0;
            gCurrentRadioPortrait = 0 + gRadioMsgRadioId;
            D_menu_801CF018 = 1;
            gRadioTextBoxScaleY = 0.0f;
            gRadioMsgCharIndex = 0;
            D_menu_801CF124 = 0.0f;
            D_menu_801CEAB4 = 0;
            break;

        case 200:
            D_menu_801CF018 = 210;
            gRadioStateTimer = 30;
            break;

        case 210:
            if (gRadioStateTimer != 0) {
                break;
            }

            D_menu_801CD940 = 1;
            gRadioMsg = SEGMENTED_TO_VIRTUAL(sBriefingMsg[sCurrentPlanetId][D_menu_801CD940]);

            Audio_PlayVoice(Message_IdFromPtr(gRadioMsg));

            gRadioMsgRadioId = D_menu_801AF420[D_menu_801CD940];
            gRadioStateTimer = Message_GetCharCount(gRadioMsg) * 2;
            gCurrentRadioPortrait = gRadioMsgRadioId;
            D_menu_801CF018 = 4;
            D_menu_801CD9A0 = true;
            break;

        case 1:
            sTeamStatusAlpha += 8;
            if (sTeamStatusAlpha > 255) {
                sTeamStatusAlpha = 255;
                gRadioTextBoxScaleY = 1.3f;

                AUDIO_PLAY_SFX(NA_SE_COMPUTER_NOISE, gDefaultSfxSource, 4);
                Audio_PlayVoice(Message_IdFromPtr(gRadioMsg));

                gRadioStateTimer = Message_GetCharCount(gRadioMsg) * 2;
                D_menu_801CD9A4 = 0;
                D_menu_801CF018 = 4;
            }
            break;

        case 4:
            if (!gRadioStateTimer && !Audio_GetCurrentVoice()) {
                gCurrentRadioPortrait = gRadioMsgRadioId;
                Audio_ClearVoice();
                if (D_menu_801CD940 == 0) {
                    gRadioMsgCharIndex = 0;
                    gRadioStateTimer = 30;
                } else {
                    gRadioStateTimer = 20;
                }
                D_menu_801CF018 = 41;
                break;
            }

            gCurrentRadioPortrait = gRadioMsgRadioId;

            if (gRadioMouthTimer > 0) {
                gCurrentRadioPortrait = 1 + gRadioMsgRadioId;
            }

            if (gRadioMsgCharIndex >= Message_GetCharCount(gRadioMsg)) {
                D_menu_801CD9A4 = 1;
            }

            if (D_menu_801CD9A0 == true) {
                D_menu_801CF124 += 0.7f;
                gRadioMsgCharIndex = D_menu_801CF124;
            } else {
                gRadioMsgCharIndex += 2;
            }

            if (D_menu_801CEAB4) {
                if (Audio_GetCurrentVoiceStatus() == 1) {
                    gRadioMouthTimer = 2;
                } else {
                    gRadioMouthTimer = 0;
                }
            }

            D_menu_801CEAB4 ^= 1;
            break;

        case 41:
            if (gRadioStateTimer != 0) {
                break;
            }

            if (D_menu_801CD940 == 1) {
                D_menu_801CF018 = 5;
                break;
            } else {
                D_menu_801CD940 = 1;
                gRadioMsg = SEGMENTED_TO_VIRTUAL(sBriefingMsg[sCurrentPlanetId][D_menu_801CD940]);
                Audio_PlayVoice(Message_IdFromPtr(gRadioMsg));
                gRadioMsgRadioId = D_menu_801AF420[D_menu_801CD940];
                gCurrentRadioPortrait = gRadioMsgRadioId;
                gRadioMsgCharIndex = 0;
                D_menu_801CF124 = 0.0f;
                gRadioStateTimer = Message_GetCharCount(gRadioMsg) * 2;
                D_menu_801CD9A0 = true;
                D_menu_801CD9A4 = 0;
                D_menu_801CF018 = 4;
            }
            break;

        case 5:
            gRadioStateTimer = 5;
            gCurrentRadioPortrait = gRadioMsgRadioId;
            D_menu_801CF018++;
            break;

        case 6:
            if (gRadioStateTimer == 0) {
                Audio_KillSfxById(NA_SE_COMPUTER_NOISE);
                Audio_PlayVoice(0);
                gRadioTextBoxScaleY = 0.0f;
                D_menu_801CF018++;
                D_menu_801CF018 = 7;
            }
            break;

        case 7:
            break;

        case 8:
            gCurrentRadioPortrait = gRadioMsgRadioId;
            gRadioTextBoxScaleY = 1.3f;
            sTeamStatusAlpha = 255;
            break;
    }

    if ((D_menu_801CF018 > 0) && (D_menu_801CF018 != 100)) {
        Map_BriefingRadio_Draw(gCurrentRadioPortrait);
        Map_BriefingRadio_Draw(D_menu_801AF420[!D_menu_801CD940]);
        if (CVarGetInteger("gLevelSelector", 0) && (gMissionNumber == 6)) {
            return;
        }
        func_radio_800BB388();
    }
}

void Map_BriefingRadio_Draw(s32 arg0) {
    s32 i;
    f32 xPos;
    f32 yPos;
    s32 alpha[3];
    static f32 sTeamStatusPos[3] = { 205.0f, 237.0f, 269.0f };
    static u16* sRadioCharacterFaces[3] = { aMapRadioCharPeppyTex, aMapRadioCharSlippyTex, aMapRadioCharFalcoTex };

    switch (arg0) {
        case 10:
        case 11:
            D_menu_801CD810 = arg0 - 10;
            break;

        case 20:
        case 21:
            if (sTeamStatusAlpha != 0) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_76_OPTIONAL);
                gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, sTeamStatusAlpha);
                xPos = 205.0f;
                yPos = 77.0f;

                Lib_TextureRect_RGBA16(&gMasterDisp, D_MAP_6044820, 92, 51, xPos, yPos, 1.0f, 1.0f);

                if (arg0 == 21) {
                    Lib_TextureRect_RGBA16(&gMasterDisp, D_MAP_6046CD0, 32, 34, xPos + 47.0, yPos, 1.0f, 1.0f);
                }

                for (i = 0; i < 3; i++) {
                    switch (gSavedTeamShields[3 - i]) {
                        case -1:
                        case -2:
                            if (sTeamStatusAlpha > 32) {
                                alpha[i] = 32;
                            } else {
                                alpha[i] = sTeamStatusAlpha;
                            }
                            break;

                        case 0:
                            RCP_SetupDL(&gMasterDisp, SETUPDL_83_OPTIONAL);
                            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);
                            if ((gGameFrameCount & 0x10) != 0) {
                                Graphics_DisplaySmallText(sTeamStatusPos[i], 131 + 28, 1.0f, 1.0f, "OK !");
                            }
                            alpha[i] = sTeamStatusAlpha;
                            break;

                        default:
                            alpha[i] = sTeamStatusAlpha;
                            break;
                    }

                    RCP_SetupDL(&gMasterDisp, SETUPDL_76_OPTIONAL);
                    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, alpha[i]);
                    Lib_TextureRect_RGBA16(&gMasterDisp, sRadioCharacterFaces[i], 28, 28, sTeamStatusPos[i], 131.0f,
                                           1.0f, 1.0f);

                    if ((gSavedTeamShields[3 - i] < 0) && (gSavedTeamShields[3 - i] != -2)) {
                        Map_TeamDownWrench_Draw(i, sTeamStatusAlpha);
                    }
                }
            }
    }
}

void Map_TeamDownWrench_Draw(s32 teamIdx, s32 alpha) {
    static s32 sTeamDownXpos[] = { 81.0f, 125.0f, 170.0f };

    Matrix_Push(&gGfxMatrix);

    // @port: Tag the transform.
    FrameInterpolation_RecordOpenChild("Map_TeamDownWrench_Draw", teamIdx);

    Matrix_LookAt(gGfxMatrix, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -400.0f, 0.0f, 1.0f, 0.0f, MTXF_APPLY);

    Matrix_SetGfxMtx(&gMasterDisp);

    RCP_SetupDL(&gMasterDisp, SETUPDL_41);

    gDPSetTextureFilter(gMasterDisp++, G_TF_POINT);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, alpha);

    Matrix_Push(&gGfxMatrix);

    Matrix_Translate(gGfxMatrix, sTeamDownXpos[teamIdx], -35.0f, -400.0f, MTXF_APPLY);
    Matrix_RotateZ(gGfxMatrix, M_DTOR * -40.0f, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, 0.3f, 0.3f, 1.0f, MTXF_APPLY);

    Matrix_SetGfxMtx(&gMasterDisp);

    gSPDisplayList(gMasterDisp++, aDownWrenchDL);

    Matrix_Pop(&gGfxMatrix);

    // @port Pop the transform id.
    FrameInterpolation_RecordCloseChild();

    Matrix_Push(&gGfxMatrix);

    // @port: Tag the transform.
    FrameInterpolation_RecordOpenChild("Map_TeamDownWrench_Draw", teamIdx + 10);

    Matrix_Translate(gGfxMatrix, sTeamDownXpos[teamIdx], -35.0f, -400.0f, MTXF_APPLY);
    Matrix_RotateZ(gGfxMatrix, M_DTOR * 40.0f, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, 0.3f, 0.3f, 1.0f, MTXF_APPLY);

    Matrix_SetGfxMtx(&gMasterDisp);

    gSPDisplayList(gMasterDisp++, aDownWrenchDL);

    Matrix_Pop(&gGfxMatrix);

    // @port Pop the transform id.
    FrameInterpolation_RecordCloseChild();

    Matrix_Pop(&gGfxMatrix);
}

void Map_GralPepperFace_Draw(void) {
    Matrix_Push(&gGfxMatrix);
    {

        // @port: Tag the transform.
        FrameInterpolation_RecordOpenChild("Map_GralPepperFace_Draw", 0);

        Matrix_LookAt(gGfxMatrix, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -400.0f, 0.0f, 1.0f, 0.0f, MTXF_APPLY);

        Matrix_SetGfxMtx(&gMasterDisp);

        RCP_SetupDL(&gMasterDisp, SETUPDL_21);

        Matrix_Push(&gGfxMatrix);
        {
            Matrix_Translate(gGfxMatrix, D_menu_801CEA88, D_menu_801CEA8C, D_menu_801CEA90, MTXF_APPLY);
            Matrix_RotateY(gGfxMatrix, M_DTOR * D_menu_801CEA94, MTXF_APPLY);

            Map_CamMatrixRot();

            Matrix_Scale(gGfxMatrix, D_menu_801CEA78, D_menu_801CEA7C, 1.0f, MTXF_APPLY);

            Matrix_SetGfxMtx(&gMasterDisp);

            gSPDisplayList(gMasterDisp++, sMapGralPepperFaceDLs[D_menu_801CD810]);

            Matrix_SetGfxMtx(&gMasterDisp);

            gSPDisplayList(gMasterDisp++, D_MAP_605A120);
        }
        Matrix_Pop(&gGfxMatrix);

        RCP_SetupDL(&gMasterDisp, SETUPDL_67);

        gDPSetPrimColor(gMasterDisp++, 0, 0, 32, 32, 255, D_menu_801CEA98);
        gDPSetEnvColor(gMasterDisp++, 207, 207, 255, 0);

        Matrix_Push(&gGfxMatrix);
        {
            Matrix_Translate(gGfxMatrix, D_menu_801CEA88, D_menu_801CEA8C - 1.5f, D_menu_801CEA90, MTXF_APPLY);
            Matrix_RotateY(gGfxMatrix, M_DTOR * D_menu_801CEA94, MTXF_APPLY);

            Map_CamMatrixRot();

            Matrix_Scale(gGfxMatrix, D_menu_801CEA80, D_menu_801CEA84, 3.3f, MTXF_APPLY);

            Matrix_SetGfxMtx(&gMasterDisp);

            gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
            gSPDisplayList(gMasterDisp++, aMapTvScreenGlowDL);
            gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
        }

        Matrix_Pop(&gGfxMatrix);

        // @port Pop the transform id.
        FrameInterpolation_RecordCloseChild();
    }
    Matrix_Pop(&gGfxMatrix);
}

void Map_Path_Draw(s32 index) {
    Vec3f v;
    f32 r;
    f32 r2;
    Vec3f vec;

    v.x = gTexturedLines[index].posBB.x - gTexturedLines[index].posAA.x;
    v.y = gTexturedLines[index].posBB.y - gTexturedLines[index].posAA.y;
    v.z = gTexturedLines[index].posBB.z - gTexturedLines[index].posAA.z;

    r = VEC3F_MAG(&v);

    if (r == 0.0f) {
        r = 1.0f;
    }

    if (sPaths[index].unk_14 == 2) {
        vec.x = (v.x / r) * (r / (sPaths[index].length - 1));
        vec.y = (v.y / r) * (r / (sPaths[index].length - 1));
        vec.z = (v.z / r) * (r / (sPaths[index].length - 1));

        D_menu_801CEEB0.x = gTexturedLines[index].posAA.x + (vec.x * D_menu_801CEEA0);
        D_menu_801CEEB0.y = gTexturedLines[index].posAA.y + (vec.y * D_menu_801CEEA0);
        D_menu_801CEEB0.z = gTexturedLines[index].posAA.z + (vec.z * D_menu_801CEEA0);

        switch (D_menu_801CEEA4) {
            case 0:
                break;

            case 100:
                sMapTimer2 = 5;
                D_menu_801CEEA4 = 10;
                break;

            case 10:
                if (sMapTimer2 != 0) {
                    break;
                }
                sMapTimer2 = 5;
                D_menu_801CEEA4 = 20;
                break;

            case 20:
                if (sMapTimer2 != 0) {
                    break;
                }

                D_menu_801CEEA0++;
                if (D_menu_801CEEA0 > sPaths[index].length - 1) {
                    D_menu_801CEEA0 = 0;
                }

                D_menu_801CEEA4 = 100;
                break;
        }

        if (D_menu_801CEEA4 != 10) {
            return;
        }
    } else {
        vec.x = (v.x / r) * gTexturedLines[index].zScale;
        vec.y = (v.y / r) * gTexturedLines[index].zScale;
        vec.z = (v.z / r) * gTexturedLines[index].zScale;

        D_menu_801CEEB0.x = gTexturedLines[index].posAA.x + vec.x;
        D_menu_801CEEB0.y = gTexturedLines[index].posAA.y + vec.y;
        D_menu_801CEEB0.z = gTexturedLines[index].posAA.z + vec.z;

        v.x = D_menu_801CEEB0.x - gTexturedLines[index].posAA.x;
        v.y = D_menu_801CEEB0.y - gTexturedLines[index].posAA.y;
        v.z = D_menu_801CEEB0.z - gTexturedLines[index].posAA.z;
        r2 = VEC3F_MAG(&v);

        if (((r / 9.0f) * 8.0f) < r2) {
            D_menu_801CEEAC -= 16;
            if (D_menu_801CEEAC < 0) {
                D_menu_801CEEAC = 0;
            }
        }
    }

    if (sPaths[index].unk_14 == 5) {
        Map_PathLine_Draw(sPaths[index].type);
    } else {
        Map_Arwing_Draw(index);
    }
}

void Map_Arwing_Draw(s32 index) {
    f32 dirX;
    f32 dirY;
    f32 dirZ;
    Vec3f dest;
    Vec3f src;
    f32 x1;
    f32 y1;
    f32 x;
    f32 y;
    f32 z;

    src.x = 0.0f;
    src.y = 0.0f;
    src.z = 0.0f;

    if (D_menu_801CEEA8 == 255) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_23);
    } else {
        RCP_SetupDL(&gMasterDisp, SETUPDL_46);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, D_menu_801CEEA8);
    }

    Matrix_Push(&gGfxMatrix);

    if (sPaths[index].unk_14 == 2) {
        // @port Skip interpolation
        FrameInterpolation_ShouldInterpolateFrame(false);
    } else {
        // @port: Tag the transform.
        FrameInterpolation_RecordOpenChild("Map_Arwing_Draw", 0);
    }

    Matrix_Translate(gGfxMatrix, D_menu_801CEEB0.x, D_menu_801CEEB0.y, D_menu_801CEEB0.z, MTXF_APPLY);

    Matrix_RotateY(gGfxMatrix, gTexturedLines[index].yRot, MTXF_APPLY);
    Matrix_RotateX(gGfxMatrix, M_DTOR * -90.0f, MTXF_APPLY);
    Matrix_RotateX(gGfxMatrix, gTexturedLines[index].xRot, MTXF_APPLY);

    Matrix_Scale(gGfxMatrix, 0.8f, 0.8f, 0.8f, MTXF_APPLY);

    Matrix_SetGfxMtx(&gMasterDisp);

    Matrix_MultVec3f(gGfxMatrix, &src, &dest);

    x = sPlanetPositions[PLANET_SOLAR].x - dest.x;
    y = sPlanetPositions[PLANET_SOLAR].y - dest.y;
    z = sPlanetPositions[PLANET_SOLAR].z - dest.z;

    x1 = Math_Atan2F(y, sqrtf(SQ(x) + SQ(z)));
    y1 = -Math_Atan2F(x, z);

    src.x = 0.0f;
    src.y = 0.0f;
    src.z = 10.0f;

    Matrix_RotateY(gCalcMatrix, M_DTOR * (-D_menu_801CDA10 - y1), MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, M_DTOR * (-D_menu_801CDA0C - x1), MTXF_APPLY);
    Matrix_MultVec3f(gCalcMatrix, &src, &dest);

    dirX = dest.x;
    dirY = dest.y;
    dirZ = dest.z;

    Lights_SetOneLight(&gMasterDisp, dirX, dirY, dirZ, 50, 50, 40, 0, 0, 0);

    gSPDisplayList(gMasterDisp++, aMapArwingDL);

    // @port renable interpolation
    FrameInterpolation_ShouldInterpolateFrame(true);

    Matrix_Pop(&gGfxMatrix);
}

void Map_PathLine_Draw(PathType pathType) {
    static f32 D_menu_801B6B30 = 0.0f;
    s32 r;
    s32 g;
    s32 b;

    if (pathType == PL_WARP_YLW) {
        r = 240;
        g = 160;
        b = 0;
    } else {
        r = 128;
        g = 0;
        b = 0;
    }

    RCP_SetupDL(&gMasterDisp, SETUPDL_67);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 80, D_menu_801CEEAC);
    gDPSetEnvColor(gMasterDisp++, r, g, b, 0);

    Matrix_Push(&gGfxMatrix);

    static f32 prevPosX = 0.0f;
    bool shouldSkipInterpolation = ABS(D_menu_801CEEB0.x) - ABS(prevPosX) > 30;

    if (shouldSkipInterpolation) {
        // @port Skip interpolation
        FrameInterpolation_ShouldInterpolateFrame(false);
    } else {
        // @port: Tag the transform.
        FrameInterpolation_RecordOpenChild("Map_PathLine_Draw", 0);
    }

    Matrix_Translate(gGfxMatrix, D_menu_801CEEB0.x, D_menu_801CEEB0.y, D_menu_801CEEB0.z, MTXF_APPLY);

    Map_CamMatrixRot();

    Matrix_RotateZ(gGfxMatrix, M_DTOR * D_menu_801B6B30, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, 10.0f, 10.0f, 10.0f, MTXF_APPLY);

    Matrix_SetGfxMtx(&gMasterDisp);

    gSPDisplayList(gMasterDisp++, D_MAP_604D680);

    Matrix_Pop(&gGfxMatrix);

    if (shouldSkipInterpolation) {
        // @port Skip interpolation
        FrameInterpolation_ShouldInterpolateFrame(true);
    } else {
        // @port Pop the transform id.
        FrameInterpolation_RecordCloseChild();
    }

    prevPosX = D_menu_801CEEB0.x;

    D_menu_801B6B30 -= 45.0f;
}

void Map_PathLines_Draw(s32 index) {
    Vec3f srcPos;
    Vec3f destPos;
    f32 x;
    f32 y;
    f32 z;
    f32 target;
    f32 temp;

    Map_PathLinePos(index, &srcPos, &destPos);

    x = srcPos.x - destPos.x;
    y = srcPos.y - destPos.y;
    z = srcPos.z - destPos.z;

    target = sqrtf(SQ(x) + SQ(y) + SQ(z));

    gTexturedLines[index].mode = 4;

    gTexturedLines[index].posAA.x = srcPos.x;
    gTexturedLines[index].posAA.y = srcPos.y;
    gTexturedLines[index].posAA.z = srcPos.z;

    gTexturedLines[index].posBB.x = destPos.x;
    gTexturedLines[index].posBB.y = destPos.y;
    gTexturedLines[index].posBB.z = destPos.z;

    gTexturedLines[index].yRot = Math_Atan2F(x, z);
    gTexturedLines[index].xRot = -Math_Atan2F(y, sqrtf(SQ(x) + SQ(z)));

    switch (gPlanetPathStatus[index]) {
        case 1:
            AUDIO_PLAY_SFX(NA_SE_MAP_LINE_DRAW, gDefaultSfxSource, 4);
            gPlanetPathStatus[index] = 11;
            break;

        case 11:
            Math_SmoothStepToF(&gTexturedLines[index].zScale, target, 0.1f, 100.0f, 4.0f);
            gTexturedLines[index].prim.a = 255;
            if (gTexturedLines[index].zScale == target) {
                Audio_KillSfxById(NA_SE_MAP_LINE_DRAW);
                gPlanetPathStatus[index] = 4;
            }
            break;

        case 5:
        case 6:
            Math_SmoothStepToF(&gTexturedLines[index].zScale, target, 0.1f, 100.0f, 1.0f);
            if (gTexturedLines[index].zScale == target) {
                gTexturedLines[index].zScale = 0.0f;
                gPlanetPathStatus[index] = 6;
                D_menu_801CEEAC = 255;
            }
            break;

        case 2:
            temp = 0.04f;
            if (sMapState == MAP_GAME_OVER) {
                temp = 0.25f;
            }
            Math_SmoothStepToF(&gTexturedLines[index].zScale, target, temp, 100.0f, 4.0f);
            gTexturedLines[index].prim.a = 255;
            if (gTexturedLines[index].zScale == target) {
                gPlanetPathStatus[index] = 3;
            }
            break;

        case 3:
        case 4:
            gTexturedLines[index].zScale = target;
            gTexturedLines[index].prim.a = sPaths[index].alpha;
            break;
    }

    if ((gPlanetPathStatus[index] == 1) || (gPlanetPathStatus[index] == 11) || (gPlanetPathStatus[index] == 4)) {
        gTexturedLines[index].prim.r = 32;
        gTexturedLines[index].prim.g = 32;
        gTexturedLines[index].prim.b = 32;
        gTexturedLines[index].xyScale = 4.0f;
    } else {
        switch (sPaths[index].type) {
            case PL_PATH_BLU:
                gTexturedLines[index].prim.r = 16;
                gTexturedLines[index].prim.g = 64;
                gTexturedLines[index].prim.b = 255;
                gTexturedLines[index].xyScale = 8.0f;
                break;

            case PL_PATH_YLW:
                gTexturedLines[index].prim.r = 255;
                gTexturedLines[index].prim.g = 175;
                gTexturedLines[index].prim.b = 0;
                gTexturedLines[index].xyScale = 8.0f;
                break;

            case PL_PATH_RED:
                gTexturedLines[index].prim.r = 255;
                gTexturedLines[index].prim.g = 0;
                gTexturedLines[index].prim.b = 0;
                gTexturedLines[index].xyScale = 8.0f;
                break;

            case PL_WARP_YLW:
            case PL_WARP_RED:
                gTexturedLines[index].prim.r = 0;
                gTexturedLines[index].prim.g = 0;
                gTexturedLines[index].prim.b = 0;
                gTexturedLines[index].prim.a = 0;
                gTexturedLines[index].xyScale = 0.1f;
                break;
        }
    }
}

void Map_PathLinePos(s32 index, Vec3f* src, Vec3f* dest) {
    f32 x1;
    f32 y1;
    f32 z1;
    f32 x2;
    f32 y2;
    f32 z2;
    Vec3f v0;
    f32 r;
    f32 temp1;
    f32 temp2;

    temp1 = 40.0f;

    if (sPaths[index].start == PLANET_FORTUNA) {
        temp1 = 50.0f;
    }
    if (sPaths[index].start == PLANET_TITANIA) {
        temp1 = 60.0f;
    }
    if (sPaths[index].start == PLANET_SOLAR) {
        temp1 = 20.0f;
    }
    if (sPaths[index].start == PLANET_METEO) {
        temp1 = 60.0f;
    }
    if (sPaths[index].start == PLANET_SECTOR_X) {
        temp1 = 20.0f;
    }
    if (sPaths[index].start == PLANET_SECTOR_Y) {
        temp1 = 20.0f;
    }
    if (sPaths[index].start == PLANET_SECTOR_Z) {
        temp1 = 20.0f;
    }
    if (sPaths[index].start == PLANET_AREA_6) {
        temp1 = 1200.0f;
    }
    if (sPaths[index].start == PLANET_BOLSE) {
        temp1 = 1200.0f;
    }

    temp2 = 40.0f;

    if (sPaths[index].end == PLANET_TITANIA) {
        temp2 = 60.0f;
    }
    if (sPaths[index].end == PLANET_FORTUNA) {
        temp2 = 50.0f;
    }
    if (sPaths[index].end == PLANET_SOLAR) {
        temp2 = 20.0f;
    }
    if (sPaths[index].end == PLANET_METEO) {
        temp2 = 60.0f;
    }
    if (sPaths[index].end == PLANET_SECTOR_X) {
        temp2 = 20.0f;
    }
    if (sPaths[index].end == PLANET_SECTOR_Y) {
        temp2 = 20.0f;
    }
    if (sPaths[index].end == PLANET_SECTOR_Z) {
        temp2 = 20.0f;
    }
    if (sPaths[index].end == PLANET_AREA_6) {
        temp2 = 1200.0f;
    }
    if (sPaths[index].end == PLANET_BOLSE) {
        temp2 = 1200.0f;
    }
    if (sPaths[index].end == PLANET_VENOM) {
        temp2 = 30.0f;
    }

    v0.x = sPlanets[sPaths[index].end].pos.x - sPlanets[sPaths[index].start].pos.x;
    v0.y = sPlanets[sPaths[index].end].pos.y - sPlanets[sPaths[index].start].pos.y;
    v0.z = sPlanets[sPaths[index].end].pos.z - sPlanets[sPaths[index].start].pos.z;

    r = VEC3F_MAG(&v0);

    x1 = sPlanets[sPaths[index].start].pos.x + (temp1 * sPlanets[sPaths[index].start].scale * (v0.x / r));
    y1 = sPlanets[sPaths[index].start].pos.y + (temp1 * sPlanets[sPaths[index].start].scale * (v0.y / r));
    z1 = sPlanets[sPaths[index].start].pos.z + (temp1 * sPlanets[sPaths[index].start].scale * (v0.z / r));

    x2 = sPlanets[sPaths[index].end].pos.x + (temp2 * sPlanets[sPaths[index].end].scale * (-v0.x / r));
    y2 = sPlanets[sPaths[index].end].pos.y + (temp2 * sPlanets[sPaths[index].end].scale * (-v0.y / r));
    z2 = sPlanets[sPaths[index].end].pos.z + (temp2 * sPlanets[sPaths[index].end].scale * (-v0.z / r));

    src->x = x1;
    src->y = y1;
    src->z = z1;

    dest->x = x2;
    dest->y = y2;
    dest->z = z2;
}

void Map_CamMatrixRot(void) {
    f32 xRot =
        Math_Atan2F(sMapCamEyeY - sMapCamAtY, sqrtf(SQ(sMapCamEyeX - sMapCamAtX) + SQ(sMapCamEyeZ - sMapCamAtZ)));
    f32 yRot = -Math_Atan2F(sMapCamEyeX - sMapCamAtX, sMapCamEyeZ - sMapCamAtZ);

    Matrix_RotateY(gGfxMatrix, -yRot, MTXF_APPLY);
    Matrix_RotateX(gGfxMatrix, -xRot, MTXF_APPLY);
}

void Map_Idle_Update(void) {
    s32 i;
    bool movingCamera;
    bool movingCameraStick;
    u8 var_a1 = 0;
    u8 var_a2 = 0;
    u8 var_a0;
    f32 stickX;
    f32 stickY;

    movingCameraStick = false;
    movingCamera = false;

    if (gControllerPress[gMainController].button & A_BUTTON) {
        if (CVarGetInteger("gLevelSelector", 0) == 1) {
            goto loadLevel;
        }
        if ((gLastGameState == GSTATE_PLAY) && (sPrevMissionStatus != MISSION_COMPLETE) && !D_menu_801CEFD0) {
            Audio_PlayMapMenuSfx(1);
            D_menu_801CEFC4 = 1;
            D_menu_801CEFD4 = 0;
            D_menu_801CEFDC = 0;
            sMapState = MAP_PATH_CHANGE;
            D_menu_801CD94C = 0;
        } else {
        loadLevel:
            for (i = 0; i < TEAM_ID_MAX; i++) {
                D_ctx_80177C58[i] = gTeamShields[i];
            }
            Map_SetState_ZoomPlanet();
        }
        return;
    }

    if (gControllerPress[gMainController].button & START_BUTTON) {
        if ((sMapState == MAP_IDLE) && (gLastGameState == GSTATE_PLAY)) {
            if (D_menu_801CEFD0) {
                AUDIO_PLAY_SFX(NA_SE_ERROR, gDefaultSfxSource, 4);
            } else {
                Audio_PlayMapMenuSfx(1);
                D_menu_801CEFC4 = 1;
                D_menu_801CEFD4 = 0;
                D_menu_801CEFDC = 0;
                sMapState = MAP_PATH_CHANGE;
                D_menu_801CD94C = 0;
            }
            return;
        }
    }

    stickX = gControllerPress[gMainController].stick_x;
    stickY = gControllerPress[gMainController].stick_y;

    if (stickY != 0.0f) {
        if (D_menu_801CDA0C - (stickY * 0.05f) < -80.0f) {
            D_menu_801CDA0C = -80.0f;
            stickY = 0.0f;
        } else if (D_menu_801CDA0C - (stickY * 0.05f) > 80.0f) {
            D_menu_801CDA0C = 80.0f;
            stickY = 0.0f;
        } else {
            D_menu_801CDA0C -= stickY * 0.05f;
            movingCameraStick = true;
            var_a1 = (s32) fabsf(((stickY * 0.05f) / 0.27f));
        }
    }

    if (stickX != 0.0f) {
        D_menu_801CDA10 += stickX * 0.05f;
        var_a2 = (s32) fabsf((stickX * 0.05f) / 0.27f);
        movingCameraStick = true;
    }

    if (D_menu_801CF014 == 1) {
        var_a0 = var_a1;
        if (var_a1 < var_a2) {
            var_a0 = var_a2;
        }
        Audio_SetSfxMapModulation(var_a0);
    }

    if ((D_menu_801CF014 == 0) && (movingCameraStick == true)) {
        Audio_PlaySfxModulated(gDefaultSfxSource, NA_SE_MAP_ROLL);
        D_menu_801CF014 = 1;
    }

    if ((D_menu_801CF014 == 1) && (movingCameraStick == false) && (stickY == 0.0f) && (stickX == 0.0f)) {
        var_a1 = 0;
        var_a2 = 0;
        Audio_KillSfxById(NA_SE_MAP_ROLL);
        D_menu_801CF014 = 0;
    }

    if (gControllerHold[gMainController].button & R_TRIG) {
        if ((D_menu_801CDA14 - 20.0f) > 2475.0f) {
            D_menu_801CDA14 -= 20.0f;
            movingCamera = true;
        }
    }

    if (gControllerHold[gMainController].button & Z_TRIG) {
        if ((D_menu_801CDA14 + 20.0f) < 7695.0f) {
            D_menu_801CDA14 += 20.0f;
            movingCamera = true;
        }
    }

    if (gControllerHold[gMainController].button & U_CBUTTONS) {
        if ((sMapCamAtY - 10.0f) >= -1200.0f) {
            sMapCamAtY -= 10.0f;
            movingCamera = true;
        }
    }

    if (gControllerHold[gMainController].button & D_CBUTTONS) {
        if ((sMapCamAtY + 10.0f) <= 1200.0f) {
            sMapCamAtY += 10.0f;
            movingCamera = true;
        }
    }

    if (gControllerHold[gMainController].button & L_CBUTTONS) {
        if ((sMapCamAtX + 10.0f) <= 1200.0f) {
            sMapCamAtX += 10.0f;
            movingCamera = true;
        }
    }

    if (gControllerHold[gMainController].button & R_CBUTTONS) {
        if ((sMapCamAtX - 10.0f) >= -1200.0f) {
            sMapCamAtX -= 10.0f;
            movingCamera = true;
        }
    }

    if ((D_menu_801CF010 == 0) && (movingCamera == true)) {
        AUDIO_PLAY_SFX(NA_SE_MAP_MOVE, gDefaultSfxSource, 4);
        D_menu_801CF010 = 1;
    }

    if ((D_menu_801CF010 == 1) && (movingCamera == false)) {
        Audio_KillSfxById(NA_SE_MAP_MOVE);
        D_menu_801CF010 = 0;
    }
}

void func_dummy_() {
}

void Map_SetCamRot(f32 camAtX, f32 camAtY, f32 camAtZ, f32* camEyeX, f32* camEyeY, f32* camEyeZ, f32 srcZ, f32 xRot,
                   f32 yRot) {
    Vec3f dest;
    Vec3f src;

    src.x = 0.0f;
    src.y = 0.0f;
    src.z = srcZ;

    Matrix_Translate(gCalcMatrix, camAtX, camAtY, camAtZ, MTXF_NEW);
    Matrix_RotateY(gCalcMatrix, M_DTOR * yRot, MTXF_APPLY);
    Matrix_RotateX(gCalcMatrix, M_DTOR * xRot, MTXF_APPLY);
    Matrix_MultVec3f(gCalcMatrix, &src, &dest);

    *camEyeX = dest.x;
    *camEyeY = dest.y;
    *camEyeZ = dest.z;
}

void Map_RemainingLives_Draw(s32 xPos, s32 yPos, s32 number) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_85_OPTIONAL);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
    Lib_TextureRect_CI4(&gMasterDisp, aMapArwingIconTex, aMapArwingIconTLUT, 16, 16, xPos, yPos, 1.0f, 1.0f);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);
    Lib_TextureRect_CI4(&gMasterDisp, aMapXTex, aMapXTLUT, 16, 7, xPos + 18.0f, yPos + 9.0f, 1.0f, 1.0f);

    RCP_SetupDL(&gMasterDisp, SETUPDL_83_OPTIONAL);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);

    if (number >= 10) {
        Graphics_DisplaySmallNumber(xPos + 33.0f - ((HUD_CountDigits(number) - 1) * 8) + 3, yPos + 8.0f, number);
    } else {
        Graphics_DisplaySmallNumber(xPos + 33.0f, yPos + 8.0f, number);
    }
}

// these probably belong to fox_title data

u32 padding_801B6B34[3] = { 0, 0, 0 };

CameraPoint D_menu_801B6B40[] = {
    { { 0.0f, 260.47226f, 1477.2115f }, { 0.0f, -17.364819f, -98.480774f } },
    { { 0.0f, 20.159666f, 759.7326f }, { 0.0f, -2.652588f, -99.96481f } },
    { { -45.790363f, 0.712088f, 336.90164f }, { 13.467754f, -0.209438f, -99.08872f } },
    { { -59.033607f, -7.952868f, 104.171906f }, { 49.19467f, 6.62739f, -86.80992f } },
    { { -39.374687f, 50.69824f, 40.264343f }, { 65.62447f, -4.497063f, -67.10724f } },
    { { -57.28257f, 48.529156f, -34.806377f }, { 95.470955f, 7.118073f, -11.322705f } },
    { { -64.80925f, 53.131527f, -77.35162f }, { 81.011566f, 3.335592f, 15.689522f } },
    { { -32.061317f, 30.244366f, -127.72071f }, { 32.061317f, 29.755634f, 61.72071f } },
    { { -62.32031f, 25.741756f, -222.99486f }, { 31.160154f, 32.12912f, 61.99743f } },
    { { -105.85609f, 14.339533f, -355.72162f }, { 31.134144f, 34.606018f, 61.91813f } },
    { { -136.99023f, 9.733513f, -450.63974f }, { 31.134144f, 34.606018f, 61.91813f } },
    { { -189.91827f, 1.90328f, -612.00055f }, { 31.134144f, 34.606018f, 61.91813f } },
};

CameraPoint D_menu_801B6C60[] = {
    { { 230.0f, -20.0f, -0.000004f }, { 90.0f, -20.0f, 0.000002f } },
    { { 217.92657f, 45.0272f, -0.006961f }, { 96.70746f, -25.01511f, 0.003867f } },
    { { 161.75992f, 66.4626f, 50.403748f }, { 73.1124f, -6.102585f, -28.316711f } },
    { { 117.362366f, 2.619884f, 27.208603f }, { 84.39606f, -4.366472f, -45.34767f } },
    { { 19.168537f, 2.445203f, 27.57978f }, { 7.556181f, -4.366434f, -49.249607f } },
    { { -116.45978f, 1.270139f, 27.862812f }, { -109.60754f, -2.268106f, -49.75502f } },
    { { -117.43788f, 1.272571f, 27.864624f }, { -110.646645f, -2.272449f, -49.758255f } },
    { { -118.43771f, 1.314066f, 27.862713f }, { -111.646935f, -2.346546f, -49.754845f } },
    { { -118.44501f, 1.314066f, 27.862074f }, { -111.63391f, -2.346546f, -49.753704f } },
    { { -118.46446f, 1.314066f, 27.860361f }, { -111.59918f, -2.346546f, -49.750645f } },
};

#include "../../mods/levelselect.c"
