/*
 * File: fox_map.c
 * System: Map
 * Description: Starfox Map Handler
 */

#include "mods.h"
// #include "prevent_bss_reordering.h"
#include "global.h"
#include "fox_map.h"
#include "fox_option.h"
#include "assets/ast_map.h"
#include "assets/ast_font.h"
#include "assets/ast_font_3d.h"

// BSS STARTS HERE
u8 D_menu_801B9410[96 * 96];
u8 D_menu_801BB810[96 * 96];
u8 D_menu_801BDC10[96 * 96];
u8 D_menu_801C0010[96 * 96];
u8 D_menu_801C2410[96 * 96];
u8 D_menu_801C4810[96 * 96];
u8 D_menu_801C6C10[96 * 96];
u8 D_menu_801C9010[96 * 96];
u8 D_menu_801CB410[96 * 96];
s32 D_menu_801CD810;
f32 D_menu_801CD818[9];
s32 D_menu_801CD83C;
s32 D_menu_801CD840[24];
s32 D_menu_801CD8A0[15];
s32 D_menu_801CD8E0[7];
s32 D_menu_801CD900[15];
s32 D_menu_801CD93C;
s32 D_menu_801CD940;
s32 D_menu_801CD944; // mapState
s32 D_menu_801CD948;
s32 D_menu_801CD94C;
s32 D_menu_801CD950;
PlanetId sCurrentPlanetId; // sCurrentPlanetId
PlanetId sNextPlanetId;
s32 D_menu_801CD95C;
s32 D_menu_801CD960;
s32 D_menu_801CD964;
s32 D_menu_801CD968;
s32 D_menu_801CD96C;
s32 D_menu_801CD970;
s32 D_menu_801CD974;
s32 D_menu_801CD978;
s32 D_menu_801CD97C;
s32 D_menu_801CD980;
s32 D_menu_801CD984;
s32 D_menu_801CD988;
s32 D_menu_801CD98C;
s32 D_menu_801CD990;
s32 D_menu_801CD994;
s32 D_menu_801CD998;
f32 D_menu_801CD99C;
s32 D_menu_801CD9A0;
s32 D_menu_801CD9A4;
s32 D_menu_801CD9A8;
s32 D_menu_801CD9AC;
f32 D_menu_801CD9B0;
f32 D_menu_801CD9B4;
s32 D_menu_801CD9B8;
s32 D_menu_801CD9BC;
s32 D_menu_801CD9C0;
s32 D_menu_801CD9C4;
s32 D_menu_801CD9C8;
s32 D_menu_801CD9CC;
s32 D_menu_801CD9D0;
s32 D_menu_801CD9D4;
s32 D_menu_801CD9D8;
f32 D_menu_801CD9DC;
f32 D_menu_801CD9E0;
f32 D_menu_801CD9E4;
f32 D_menu_801CD9E8;
f32 D_menu_801CD9EC;
s32 D_menu_801CD9F0;
f32 D_menu_801CD9F4; // x
f32 D_menu_801CD9F8; // y
f32 D_menu_801CD9FC; // z
f32 D_menu_801CDA00; // x
f32 D_menu_801CDA04; // y
f32 D_menu_801CDA08; // z
f32 D_menu_801CDA0C; // camera x
f32 D_menu_801CDA10; // camera y
f32 D_menu_801CDA14;
f32 D_menu_801CDA18;
f32 D_menu_801CDA1C;
f32 D_menu_801CDA20;
f32 D_menu_801CDA24;
f32 D_menu_801CDA28;
f32 D_menu_801CDA2C;
f32 D_menu_801CDA30;
f32 D_menu_801CDA34;
f32 D_menu_801CDA38;
Vec3f D_menu_801CDA40;
Vec3f D_menu_801CDA50;
Matrix D_menu_801CDA60[15];
Matrix D_menu_801CDE20[15]; // planet related
Matrix D_menu_801CE1E0[15];
Matrix D_menu_801CE5A0[15];
Vec3f D_menu_801CE960[15]; // sPlanetsPositions
f32 D_menu_801CEA18[15];
f32 D_menu_801CEA54;
f32 D_menu_801CEA58;
f32 D_menu_801CEA5C;
f32 D_menu_801CEA60;
f32 D_menu_801CEA64;
f32 D_menu_801CEA68;
f32 D_menu_801CEA6C;
f32 D_menu_801CEA70;
s32 D_menu_801CEA74;
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
f32 D_menu_801CEAA8;
f32 D_menu_801CEAAC;
f32 D_menu_801CEAB0;
s32 D_menu_801CEAB4;
f32 D_menu_801CEAB8[15];
f32 D_menu_801CEAF8[15];
s32 D_menu_801CEB34;
s32 D_menu_801CEB38;
f32 D_menu_801CEB3C;
f32 D_menu_801CEB40;
s32 D_menu_801CEB48[3];
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
f32 D_menu_801CF020[8];
f32 D_menu_801CF040[8];
f32 D_menu_801CF060[8];
f32 D_menu_801CF080;
f32 D_menu_801CF088[8];
f32 D_menu_801CF0A8[8];
f32* D_menu_801CF0C8;
f32* D_menu_801CF0CC;
f32* D_menu_801CF0D0;
s32 D_menu_801CF0D8[8];
s32 D_menu_801CF0F8[8];
s32 D_menu_801CF118;
s32 D_menu_801CF11C;
s32 D_menu_801CF120;
f32 D_menu_801CF124;

s32 D_menu_801AF420[2] = { 10, 20 };

u16* D_menu_801AF428[15][2] = {
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

Gfx* D_menu_801AF824[4] = { D_MAP_604A710, D_MAP_604A400, D_MAP_604A190, D_MAP_6049F80 };

TitleCard D_menu_801AF834[14] = {
    { D_MAP_6007B90, 128, 28, 95.0f }, { D_MAP_60030D0, 96, 28, 110.0f },  { D_MAP_60131A0, 176, 12, 73.0f },
    { D_MAP_6009AD0, 168, 28, 77.0f }, { D_MAP_600B9B0, 168, 28, 74.0f },  { D_MAP_6001C80, 96, 13, 106.0f },
    { D_MAP_6011660, 176, 12, 75.0f }, { D_MAP_6010010, 112, 13, 109.0f }, { D_MAP_6017640, 112, 28, 101.0f },
    { D_MAP_6015CE0, 96, 28, 108.0f }, { D_MAP_600E210, 160, 28, 78.0f },  { D_MAP_6014360, 176, 12, 73.0f },
    { D_MAP_6004AC0, 168, 19, 72.0f }, { D_MAP_6006320, 104, 28, 105.0f },
};

TitleCard D_menu_801AF914[] = {
    { D_MAP_6008990, 232, 19, 46.0f }, { D_MAP_6003B50, 208, 19, 56.0f }, { D_MAP_60139E0, 128, 19, 98.0f },
    { D_MAP_600AD30, 168, 19, 77.0f }, { D_MAP_600CC10, 128, 19, 95.0f }, { D_MAP_6002160, 208, 19, 57.0f },
    { D_MAP_6011EA0, 256, 19, 40.0f }, { D_MAP_60105C0, 224, 19, 49.0f }, { D_MAP_6018280, 184, 19, 70.0f },
    { D_MAP_6016760, 200, 18, 61.0f }, { D_MAP_600F390, 168, 19, 75.0f }, { D_MAP_6014BA0, 232, 19, 43.0f },
    { D_MAP_6005740, 160, 19, 81.0f }, { D_MAP_6006E80, 176, 19, 70.0f },
};

char* sPlanetNames[] = {
    "ME", "A6", "BO", "SZ", "SX", "SY", "KA", "MA", "ZO", "CO", "TI", "AQ", "FO", "VE", "SO",
};

Gfx* D_menu_801AFA30[2] = {
    D_MAP_6055F20,
    D_MAP_6051D20,
};

ObjPosition D_menu_801AFA38[] = {
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

ObjPosition D_menu_801AFCD8[4] = {
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
    D_menu_801B00C0[47][96] = {
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

Vtx D_menu_801B4740[] = {
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

Gfx D_menu_801B4A40[] = {
    gsSPVertex(D_menu_801B4740, 16, 0),
    gsDPLoadTextureBlock(D_menu_801B9410, G_IM_FMT_IA, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&D_menu_801B9410[96 * 8 * 1], G_IM_FMT_IA, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&D_menu_801B9410[96 * 8 * 2], G_IM_FMT_IA, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&D_menu_801B9410[96 * 8 * 3], G_IM_FMT_IA, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsSPVertex(&D_menu_801B4740[16], 16, 0),
    gsDPLoadTextureBlock(&D_menu_801B9410[96 * 8 * 4], G_IM_FMT_IA, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&D_menu_801B9410[96 * 8 * 5], G_IM_FMT_IA, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&D_menu_801B9410[96 * 8 * 6], G_IM_FMT_IA, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&D_menu_801B9410[96 * 8 * 7], G_IM_FMT_IA, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsSPVertex(&D_menu_801B4740[32], 16, 0),
    gsDPLoadTextureBlock(&D_menu_801B9410[96 * 8 * 8], G_IM_FMT_IA, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&D_menu_801B9410[96 * 8 * 9], G_IM_FMT_IA, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&D_menu_801B9410[96 * 8 * 10], G_IM_FMT_IA, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&D_menu_801B9410[96 * 8 * 11], G_IM_FMT_IA, G_IM_SIZ_8b, 96, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPEndDisplayList(),
};

Gfx D_menu_801B4D70[] = {
    gsDPLoadTLUT_pal256(D_MAP_6026C90),
    gsSPVertex(D_menu_801B4740, 16, 0),
    gsDPLoadTextureBlock(D_menu_801BB810, G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&D_menu_801BB810[96 * 8 * 1], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&D_menu_801BB810[96 * 8 * 2], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&D_menu_801BB810[96 * 8 * 3], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsSPVertex(&D_menu_801B4740[16], 16, 0),
    gsDPLoadTextureBlock(&D_menu_801BB810[96 * 8 * 4], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&D_menu_801BB810[96 * 8 * 5], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&D_menu_801BB810[96 * 8 * 6], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&D_menu_801BB810[96 * 8 * 7], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsSPVertex(&D_menu_801B4740[32], 16, 0),
    gsDPLoadTextureBlock(&D_menu_801BB810[96 * 8 * 8], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&D_menu_801BB810[96 * 8 * 9], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&D_menu_801BB810[96 * 8 * 10], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&D_menu_801BB810[96 * 8 * 11], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPEndDisplayList(),
};

Gfx D_menu_801B50D8[] = {
    gsDPLoadTLUT_pal256(D_MAP_6029170),
    gsSPVertex(D_menu_801B4740, 16, 0),
    gsDPLoadTextureBlock(&D_menu_801BDC10, G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&D_menu_801BDC10[96 * 8 * 1], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&D_menu_801BDC10[96 * 8 * 2], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&D_menu_801BDC10[96 * 8 * 3], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsSPVertex(&D_menu_801B4740[16], 16, 0),
    gsDPLoadTextureBlock(&D_menu_801BDC10[96 * 8 * 4], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&D_menu_801BDC10[96 * 8 * 5], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&D_menu_801BDC10[96 * 8 * 6], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&D_menu_801BDC10[96 * 8 * 7], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsSPVertex(&D_menu_801B4740[32], 16, 0),
    gsDPLoadTextureBlock(&D_menu_801BDC10[96 * 8 * 8], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&D_menu_801BDC10[96 * 8 * 9], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&D_menu_801BDC10[96 * 8 * 10], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&D_menu_801BDC10[96 * 8 * 11], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPEndDisplayList(),
};

Gfx D_menu_801B5440[] = {
    gsDPLoadTLUT_pal256(D_MAP_6022340),
    gsSPVertex(D_menu_801B4740, 16, 0),
    gsDPLoadTextureBlock(D_menu_801C0010, G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&D_menu_801C0010[96 * 8 * 1], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&D_menu_801C0010[96 * 8 * 2], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&D_menu_801C0010[96 * 8 * 3], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsSPVertex(&D_menu_801B4740[16], 16, 0),
    gsDPLoadTextureBlock(&D_menu_801C0010[96 * 8 * 4], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&D_menu_801C0010[96 * 8 * 5], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&D_menu_801C0010[96 * 8 * 6], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&D_menu_801C0010[96 * 8 * 7], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsSPVertex(&D_menu_801B4740[32], 16, 0),
    gsDPLoadTextureBlock(&D_menu_801C0010[96 * 8 * 8], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&D_menu_801C0010[96 * 8 * 9], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&D_menu_801C0010[96 * 8 * 10], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&D_menu_801C0010[96 * 8 * 11], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPEndDisplayList(),
};

Gfx D_menu_801B57A8[] = {
    gsDPLoadTLUT_pal256(D_MAP_60247E0),
    gsSPVertex(D_menu_801B4740, 16, 0),
    gsDPLoadTextureBlock(D_menu_801C2410, G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&D_menu_801C2410[96 * 8 * 1], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&D_menu_801C2410[96 * 8 * 2], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&D_menu_801C2410[96 * 8 * 3], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsSPVertex(&D_menu_801B4740[16], 16, 0),
    gsDPLoadTextureBlock(&D_menu_801C2410[96 * 8 * 4], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&D_menu_801C2410[96 * 8 * 5], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&D_menu_801C2410[96 * 8 * 6], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&D_menu_801C2410[96 * 8 * 7], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsSPVertex(&D_menu_801B4740[32], 16, 0),
    gsDPLoadTextureBlock(&D_menu_801C2410[96 * 8 * 8], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&D_menu_801C2410[96 * 8 * 9], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&D_menu_801C2410[96 * 8 * 10], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&D_menu_801C2410[96 * 8 * 11], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPEndDisplayList(),
};

Gfx D_menu_801B5B10[] = {
    gsDPLoadTLUT_pal256(D_MAP_602FF60),
    gsSPVertex(D_menu_801B4740, 16, 0),
    gsDPLoadTextureBlock(D_menu_801C4810, G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&D_menu_801C4810[96 * 8 * 1], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&D_menu_801C4810[96 * 8 * 2], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&D_menu_801C4810[96 * 8 * 3], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsSPVertex(&D_menu_801B4740[16], 16, 0),
    gsDPLoadTextureBlock(&D_menu_801C4810[96 * 8 * 4], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&D_menu_801C4810[96 * 8 * 5], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&D_menu_801C4810[96 * 8 * 6], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&D_menu_801C4810[96 * 8 * 7], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsSPVertex(&D_menu_801B4740[32], 16, 0),
    gsDPLoadTextureBlock(&D_menu_801C4810[96 * 8 * 8], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&D_menu_801C4810[96 * 8 * 9], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&D_menu_801C4810[96 * 8 * 10], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&D_menu_801C4810[96 * 8 * 11], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPEndDisplayList(),
};

Gfx D_menu_801B5E78[] = {
    gsDPLoadTLUT_pal256(D_MAP_602B620),
    gsSPVertex(D_menu_801B4740, 16, 0),
    gsDPLoadTextureBlock(D_menu_801C6C10, G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&D_menu_801C6C10[96 * 8 * 1], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&D_menu_801C6C10[96 * 8 * 2], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&D_menu_801C6C10[96 * 8 * 3], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsSPVertex(&D_menu_801B4740[16], 16, 0),
    gsDPLoadTextureBlock(&D_menu_801C6C10[96 * 8 * 4], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&D_menu_801C6C10[96 * 8 * 5], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&D_menu_801C6C10[96 * 8 * 6], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&D_menu_801C6C10[96 * 8 * 7], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsSPVertex(&D_menu_801B4740[32], 16, 0),
    gsDPLoadTextureBlock(&D_menu_801C6C10[96 * 8 * 8], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&D_menu_801C6C10[96 * 8 * 9], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&D_menu_801C6C10[96 * 8 * 10], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&D_menu_801C6C10[96 * 8 * 11], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPEndDisplayList(),
};

Gfx D_menu_801B61E0[] = {
    gsDPLoadTLUT_pal256(D_MAP_602DAD0),
    gsSPVertex(D_menu_801B4740, 16, 0),
    gsDPLoadTextureBlock(D_menu_801C9010, G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&D_menu_801C9010[96 * 8 * 1], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&D_menu_801C9010[96 * 8 * 2], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&D_menu_801C9010[96 * 8 * 3], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsSPVertex(&D_menu_801B4740[16], 16, 0),
    gsDPLoadTextureBlock(&D_menu_801C9010[96 * 8 * 4], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&D_menu_801C9010[96 * 8 * 5], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&D_menu_801C9010[96 * 8 * 6], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&D_menu_801C9010[96 * 8 * 7], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsSPVertex(&D_menu_801B4740[32], 16, 0),
    gsDPLoadTextureBlock(&D_menu_801C9010[96 * 8 * 8], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(&D_menu_801C9010[96 * 8 * 9], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(&D_menu_801C9010[96 * 8 * 10], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(&D_menu_801C9010[96 * 8 * 11], G_IM_FMT_CI, G_IM_SIZ_8b, 96, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPEndDisplayList(),
};

Gfx D_menu_801B6548[] = {
    gsDPLoadTLUT_pal256(D_MAP_60323D0),
    gsSPVertex(D_menu_801B4740, 16, 0),
    gsDPLoadTextureBlock(D_menu_801CB410, G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(D_menu_801CB410 + (96 * 8 * 1), G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(D_menu_801CB410 + (96 * 8 * 2), G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(D_menu_801CB410 + (96 * 8 * 3), G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsSPVertex(&D_menu_801B4740[16], 16, 0),
    gsDPLoadTextureBlock(D_menu_801CB410 + (96 * 8 * 4), G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(D_menu_801CB410 + (96 * 8 * 5), G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(D_menu_801CB410 + (96 * 8 * 6), G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(D_menu_801CB410 + (96 * 8 * 7), G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsSPVertex(&D_menu_801B4740[32], 16, 0),
    gsDPLoadTextureBlock(D_menu_801CB410 + (96 * 8 * 8), G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsDPLoadTextureBlock(D_menu_801CB410 + (96 * 8 * 9), G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(5, 6, 7, 4, 0),
    gsDPLoadTextureBlock(D_menu_801CB410 + (96 * 8 * 10), G_IM_FMT_CI, G_IM_SIZ_8b, 96, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(9, 10, 11, 8, 0),
    gsDPLoadTextureBlock(D_menu_801CB410 + (96 * 8 * 11), G_IM_FMT_CI, G_IM_SIZ_8b, 96, 8, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD),
    gsSP1Quadrangle(13, 14, 15, 12, 0),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPEndDisplayList(),
};

u8* D_menu_801B68B0[] = {
    D_menu_801C6C10, D_menu_801C9010, D_menu_801CB410, D_menu_801BB810, D_menu_801C4810,
    D_menu_801C0010, D_menu_801BDC10, D_menu_801C2410, D_menu_801B9410,
};

u8* D_menu_801B68D4[] = {
    D_MAP_6029220, D_MAP_602B6D0, D_MAP_602FFD0, D_MAP_6024890, D_MAP_602DB60,
    D_MAP_601FF40, D_MAP_6026D70, D_MAP_60223E0, D_MAP_60190B0,
};

Gfx* D_menu_801B68F8[] = {
    D_MAP_6060610,   D_MAP_601DE80,   D_MAP_604B750,   D_MAP_601F6B0,   D_MAP_601C0D0,
    D_MAP_601C960,   D_menu_801B5E78, D_menu_801B61E0, D_menu_801B6548, D_menu_801B4D70,
    D_menu_801B5B10, D_menu_801B5440, D_menu_801B50D8, D_menu_801B57A8, D_MAP_604DB10,
};

void Map_8019E800(void);
void Map_8019E99C(void);
void Map_8019F164(void);
void Map_8019F42C(void);
void Map_8019F600(void);
void Map_8019F910(void);
void Map_8019F97C(void);
void Map_8019F83C(void);
void Map_8019FA1C(void);
void Map_8019FC04(void);
bool Map_8019FD1C(LevelId levelId, s32 arg1);
void Map_8019FF48(void);
s32 Map_801A05B4(void);
void Map_801A0788(void);
void Map_801A0954(void);
void Map_801A0D14(void);
void Map_801A1528(void);
void Map_801A116C(void);
void Map_801A19A8(void);
void Map_801A1C14(void);
bool Map_801A2304(void);
f32 Map_801A25C8(PlanetId);
void Map_801A2674(void);
void Map_801A281C(void);
void Map_801A2B8C(void);
void Map_801A2EB8(void);
void Map_801A3440(f32);
void Map_801A3550(Vec3f*, Vec3f*, Vec3f*, f32);
void Map_801A36A8(void);
void Map_801A3A00(void);
void Map_801A4394(void);
void Map_801A4650(void);
void Map_801A48C0(f32 speed);
void Map_801A4A38(f32 arg0);
void Map_801A4AE8(void);
void Map_801A4D0C(u32);
void Map_801A4D7C(void);
void Map_801A4F8C(void);
void Map_801A4FC4(void);
void Map_801A53C8(void);
void Map_801A5834(void);
void Map_801A5C90(void);
bool Map_801A5770(void);
void Map_801A5E80(void);
void Map_801A6368(void);
void Map_801A61B4(LevelId level);
bool Map_801A62FC(PlanetId planet);
s32 Map_801A655C(PlanetId start, PlanetId end);
void Map_801A6628(void);
void Map_801A6694(void);
void Map_801A68E4(void);
void Map_801A6A24(void);
void Map_801A6A98(PlanetId);
s32 Map_801A6DAC(PlanetId planetId);
void Map_801A6EC0(PlanetId planetId);
void Map_801A7230(PlanetId planetId);
void Map_801A74F4(PlanetId);
void Map_801A7684(PlanetId planetId);
void Map_801A77B0(PlanetId planetId);
void Map_801A791C(PlanetId planetId);
void Map_801A7A84(PlanetId planetId);
void Map_801A7BEC(f32* zAngle, f32 next, f32 scale);
void Map_801A7D3C(PlanetId planetId);
void Map_801A7F1C(PlanetId planetId);
void Map_801A914C(void);
void Map_801A9EE4(void);
void Map_801AD11C(void);
void Map_801AD718(f32, f32, f32, f32*, f32*, f32*, f32, f32, f32);
PlanetId Map_GetPlanetId(LevelId level);
void Map_801A809C(PlanetId planetId);
void Map_801A8738(void);
void Map_801A89BC(PlanetId, s32);
void Map_801A8F40(void);
void Map_801A9224(void);
void Map_801A9448(void);
void Map_801A9814(void);
void Map_801A9910(void);
void Map_801A9A8C(void);
void Map_801A9DE8(void);
void Map_801AA1CC(s32);
void Map_801AA434(s32, f32, f32, s32);
void Map_801AA778(s32, f32, f32, PlanetId);
void Map_801AB17C(f32 x, f32 y, f32 z);
void Map_801AB284(void);
void Map_801AB300(void);
void Map_801AB978(s32);
void Map_801ABCDC(s32 arg0, s32 alpha);
void Map_801ABF1C(void);
void Map_801AC200(s32);
void Map_801AC530(s32 index);
void Map_801AC80C(PathType);
void Map_801AC9A0(s32);
void Map_801ACD90(s32 index, Vec3f* src, Vec3f* dest);
void Map_801AD048(void);

void Map_8019E800(void) {
    Memory_FreeAll();
    func_play_800A5D6C();
    D_ctx_80178410 = 0;
    gNextGameState = GSTATE_MAP;
    D_game_80161A34 = 5;
    D_ctx_80177868 = 2;
    gDrawMode = DRAW_NONE;
}

void Map_8019E85C(void) {
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

void Map_8019E8D0(void) {
    if (D_menu_801CD9B8 > 0) {
        D_menu_801CD9B8--;
    }
    if (D_menu_801CD9BC > 0) {
        D_menu_801CD9BC--;
    }
    if (D_menu_801CD9C0 > 0) {
        D_menu_801CD9C0--;
    }

    switch (D_ctx_80177B40) {
        case 0:
            if (gNextGameStateTimer == 0) {
                D_ctx_80177B40 = 1;
            }
            break;

        case 1:
            gDrawMode = DRAW_NONE;
            Map_8019E99C();
            break;

        case 2:
            gDrawMode = DRAW_MAP;
            Map_8019FF48();
            break;
    }
}

void Map_8019E99C(void) {
    s32 i;
    s32 j;

    Audio_SetAudioSpec(0, 0x118);

    D_80137E78 = 2;
    gGameFrameCount = 0;

    Title_80188010();

    D_menu_801CD83C = Map_801A05B4();

    D_menu_801CD980 = 0;
    D_menu_801CD984 = 0;
    D_menu_801CD98C = 0;
    D_menu_801CD990 = 0;
    D_menu_801CD994 = 0;
    D_menu_801CD9CC = 0;

    D_menu_801CEB48[0] = false;
    D_menu_801CEB48[1] = false;
    D_menu_801CEB48[2] = false;

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

    D_menu_801CDA20 = 0.0f;
    D_menu_801CDA24 = 1.0f;
    D_menu_801CDA28 = 0.0f;
    D_menu_801CDA00 = -150.55215f;
    D_menu_801CDA04 = -489.68f;
    D_menu_801CDA08 = 0.0f;
    D_menu_801CDA0C = -42.750008f;
    D_menu_801CDA10 = -9.849999f;
    D_menu_801CDA14 = 3375.000000f;
    D_menu_801CDA18 = 0.0f;
    D_menu_801CDA1C = 0.0f;

    Map_801AD718(D_menu_801CDA00, D_menu_801CDA04, D_menu_801CDA08, &D_menu_801CD9F4, &D_menu_801CD9F8,
                 &D_menu_801CD9FC, D_menu_801CDA14, D_menu_801CDA0C + D_menu_801CDA18,
                 D_menu_801CDA10 + D_menu_801CDA1C);

    for (i = 0; i < 15; i++) {
        D_menu_801CD8A0[i] = i;
    }

    D_menu_801CD960 = 0;

    gFillScreenAlpha = 255;
    gFillScreenRed = 0;
    gFillScreenGreen = 0;
    gFillScreenBlue = 0;
    D_ctx_80177D20 = 0.0f;

    D_menu_801CF018 = 0;

    gBgColor = 0;

    D_menu_801CEA58 = 0.0f;
    D_menu_801CEA5C = 0.0f;
    D_menu_801CEA60 = 0.0f;

    Map_801A0788();

    D_menu_801B8280 = 0;
    D_menu_801B8284 = 0;
    D_menu_801CD9B8 = 0;
    D_menu_801CD9BC = 0;
    D_menu_801CD9C0 = 0;
    D_menu_801CD964 = 0;
    D_menu_801CD968 = 0;
    D_menu_801CD96C = 0;
    D_menu_801CEA6C = 0.0f;
    D_menu_801CEA70 = 0.002f;

    AUDIO_PLAY_BGM(SEQ_ID_WORLD_MAP);

    D_menu_801CEFC4 = 0;
    D_menu_801CEFC8 = 0;
    D_menu_801CEFD0 = 0;
    D_menu_801CD974 = 0;

    for (i = 0; i < 24; i++) {
        D_menu_801CD840[i] = i;
        sPaths[i].unk_14 = 0;
    }

    Map_801A6694();

    switch (D_game_80161A34) {
        default:
        case 0:
            Map_8019F600();
            break;

        case 7:
            Map_8019F164();
            break;

        case 5:
            Map_8019F42C();
            break;
    }

    Map_801A914C();

    for (i = 0; i < 96 * 96; i++) {
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

    D_menu_801CD810 = 0;

    D_ctx_80177B40 = 2;

    D_menu_801CD948 = 0;
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

void Map_8019F164(void) {
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

    D_menu_801CD93C = gNextPlanetPath;

    sCurrentPlanetId = Map_GetPlanetId(gCurrentLevel);

    D_menu_801CD950 = sCurrentPlanetId;

    D_menu_801CD980 = Map_8019FD1C(gCurrentLevel, 0);

    Map_8019FD1C(gCurrentLevel, 2);

    if (D_play_800D3180[gCurrentLevel] == 2) {
        D_menu_801CD98C = 1;
        D_ctx_80177BB0[gCurrentPlanet] = 1;
        Map_8019FD1C(gCurrentLevel, 1);
    }

    Save_Write();

    Map_8019F97C();

    Map_8019F83C();

    Map_8019FA1C();

    switch (D_menu_801CD93C) {
        case 0:
            sNextPlanetId = sPlanets[sCurrentPlanetId].dest1;
            break;

        case 1:
            sNextPlanetId = sPlanets[sCurrentPlanetId].dest2;
            break;

        case 2:
            sNextPlanetId = sPlanets[sCurrentPlanetId].warp;
            break;
    }

    gCurrentPlanet++;

    Map_8019FC04();

    D_menu_801CEFC4 = 0;
    D_menu_801CEFD0 = 0;
    D_menu_801CEFE0 = 32.0f;

    D_menu_801CEFE8[0] = 255.0f;
    D_menu_801CEFE8[1] = 255.0f;
    D_menu_801CEFE8[2] = 255.0f;

    D_menu_801CEFD8 = 0;

    if (D_menu_801CD93C != 0) {
        D_menu_801CEFD8 = 1;
    }

    gHitCount = 0;

    D_menu_801CD94C = 0;
    D_menu_801CD944 = 5;
}

void Map_8019F42C(void) {
    s32 i;

    gTotalHits += gHitCount;
    gLifeCount[gPlayerNum] = 0;

    D_menu_801CD974 = 1;
    sCurrentPlanetId = Map_GetPlanetId(gCurrentLevel);

    D_ctx_80177B70[gCurrentPlanet] = gHitCount;

    Map_8019F910();
    Map_8019FD1C(gCurrentLevel, 0);
    Save_Write();
    Map_8019F83C();

    for (i = 0; i < 7; i++) {
        D_menu_801CD8E0[i] = 0;
    }

    if (gCurrentPlanet != 0) {
        for (i = 0; i < gCurrentPlanet; i++) {
            D_menu_801CD8E0[i] = Map_801A655C(D_ctx_80177B90[i], D_ctx_80177B90[i + 1]);
        }
    }

    for (i = 0; i < 24; i++) {
        D_ctx_80177BD8[i] = 0;
    }

    for (i = 0; i < 15; i++) {
        sPlanets[i].alpha = 0;
    }

    Map_8019FC04();

    D_menu_801CD9AC = 0;

    Audio_SetAudioSpec(0, 0x19);

    D_menu_801CD948 = 0;
    D_menu_801CD94C = 0;
    D_menu_801CD944 = 7;
}

void Map_8019F600(void) {
    s32 i;
    s32 sp18;
    s32 temp_t4;

    gTotalHits = 0;
    gHitCount = 0;

    gTeamShields[TEAM_ID_FALCO] = 255;
    gTeamShields[TEAM_ID_SLIPPY] = 255;
    gTeamShields[TEAM_ID_PEPPY] = 255;
    gSavedTeamShields[1] = 255;
    gSavedTeamShields[2] = 255;
    gSavedTeamShields[3] = 255;
    gPrevPlanetTeamShields[1] = 255;
    gPrevPlanetTeamShields[2] = 255;
    gPrevPlanetTeamShields[3] = 255;
    D_ctx_80177C58[1] = 255;
    D_ctx_80177C58[2] = 255;
    D_ctx_80177C58[3] = 255;

    D_menu_801CD950 = -1;

    for (i = 0; i < 15; i++) {
        sPlanets[i].alpha = 0;
    }

    D_menu_801CD970 = 0;
    for (i = 0; i < 24; i++) {
        D_ctx_80177BD8[i] = 0;
        gTexturedLines[i].unk_24 = 0.0f;
    }

    for (i = 0; i < 7; i++) {
        D_ctx_80177BB0[i] = 0;
        D_ctx_80177B70[i] = 0;
        D_ctx_80177B50[i] = 0x00FFFFFF;
    }
    D_ctx_80177B90[0] = PLANET_CORNERIA;
    D_ctx_80177B90[1] = PLANET_NONE;
    D_ctx_80177B90[2] = PLANET_NONE;
    D_ctx_80177B90[3] = PLANET_NONE;
    D_ctx_80177B90[4] = PLANET_NONE;
    D_ctx_80177B90[5] = PLANET_NONE;
    D_ctx_80177B90[6] = PLANET_VENOM;

    for (i = 0; i < 24; i++) {
        sPaths[i].alpha = 255;
    }

    gCurrentPlanet = 0;
    gCurrentLevel = 0;

    sCurrentPlanetId = 9;
    D_menu_801CEA9C = 0.0f;
    D_menu_801CD9B0 = 0.002f;
    D_menu_801CD9B4 = 0.01f;
    D_menu_801CD944 = 0;

    sp18 = Map_801A655C(sCurrentPlanetId, sPlanets[sCurrentPlanetId].dest1);
    temp_t4 = Map_801A655C(sCurrentPlanetId, sPlanets[sCurrentPlanetId].dest2);
    D_ctx_80177BD8[sp18] = 1;
    D_ctx_80177BD8[temp_t4] = 1;
}

void Map_8019F83C(void) {
    s32 i;

    D_menu_801CD970 = 0;

    for (i = 0; i < 24; i++) {
        if ((D_ctx_80177BD8[i] == 4) || (D_ctx_80177BD8[i] == 5) || (D_ctx_80177BD8[i] == 1) ||
            (D_ctx_80177BD8[i] == 11)) {
            D_ctx_80177BD8[i] = 0;
        }

        if (D_ctx_80177BD8[i] == 6) {
            sPaths[i].unk_14 = 5;
        }

        sPaths[i].alpha = 0;
        gTexturedLines[i].unk_24 = 0.0f;
    }
}

void Map_8019F910(void) {
    s32 i;
    s32 mask = 0x00FF0000;

    for (i = 0; i < 3; i++) {
        if (gTeamShields[3 - i] <= 0) {
            D_ctx_80177B50[gCurrentPlanet] ^= mask;
        } else {
            D_ctx_80177B50[gCurrentPlanet] |= mask;
        }
        mask >>= 8;
    }
}

void Map_8019F97C(void) {
    D_menu_801CEA54 = Map_801A25C8(sCurrentPlanetId);

    D_menu_801CD9F4 = D_menu_801CDA00 = sPlanets[sCurrentPlanetId].pos.x;
    D_menu_801CD9F8 = D_menu_801CDA04 = sPlanets[sCurrentPlanetId].pos.y;
    D_menu_801CDA08 = sPlanets[sCurrentPlanetId].pos.z;
    D_menu_801CD9FC = sPlanets[sCurrentPlanetId].pos.z + D_menu_801CEA54;
}

void Map_8019FA1C(void) {
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

void Map_8019FC04(void) {
    s32 i;

    if (gCurrentPlanet != PLANET_METEO) {
        D_menu_801CEB48[1] = true;
        D_menu_801CEB48[2] = true;
    }

    for (i = 0; i < 7; i++) {
        if (D_ctx_80177B90[i] == PLANET_KATINA) {
            D_menu_801CEB48[1] = false;
        }
        if (D_ctx_80177B90[i] == PLANET_SECTOR_Y) {
            D_menu_801CEB48[2] = false;
        }
    }
}

bool Map_8019FD1C(LevelId levelId, s32 arg1) {
    s32 ret;
    s32 planetSaveSlot;

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
            if (gLevelStage == 0) {
                planetSaveSlot = SAVE_SLOT_VENOM_1;
            } else {
                planetSaveSlot = SAVE_SLOT_VENOM_2;
            }
            break;
    }

    ret = false;

    switch (arg1) {
        case 0:
            if (!(gSaveFile.save.data.planet[planetSaveSlot].played & 1)) {
                gSaveFile.save.data.planet[planetSaveSlot].played = 1;
                ret = true;
            }
            break;

        case 1:
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

        case 2:
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

void Map_8019FF48(void) {
    Map_801A6694();
    Map_801A68E4();
    Map_801A6A24();

    switch (D_menu_801CD944) {
        case 0:
            Map_801A0954();
            D_ctx_8017842C += 0.09f;
            break;

        case 1:
            Map_801A1528();
            D_menu_801CDA1C += 0.03f;
            break;

        case 3:
            Map_801AD11C();
            D_menu_801CDA1C += 0.03f;
            break;

        case 2:
            Map_801A1C14();
            break;

        case 4:
            Map_801A5E80();
            break;

        case 5:
            Map_801A2B8C();
            break;

        case 6:
            Map_801A4AE8();
            break;

        case 7:
            Map_801A36A8();
            break;

        default:
            break;
    }

    if ((D_menu_801CD944 == 0) || (D_menu_801CD944 == 1) || (D_menu_801CD944 == 7) || (D_menu_801CD944 == 3)) {
        Map_801AD718(D_menu_801CDA00, D_menu_801CDA04, D_menu_801CDA08, &D_menu_801CD9F4, &D_menu_801CD9F8,
                     &D_menu_801CD9FC, D_menu_801CDA14, D_menu_801CDA0C + D_menu_801CDA18,
                     D_menu_801CDA10 + D_menu_801CDA1C);
        func_play_800B6F50(D_menu_801CD9F4, D_menu_801CD9F8, D_menu_801CD9FC, D_menu_801CDA00, D_menu_801CDA04,
                           D_menu_801CDA08);
    }
    gGameFrameCount++;
    if(CVarGetInteger("gLevelSelector", 0)){
        Map_LevelSelect();
    }
}

void Map_801A01A8(void) {
    s32 i;
    s32* ptr;

    Matrix_Push(&gGfxMatrix);
    Matrix_LookAt(gGfxMatrix, D_menu_801CD9F4, D_menu_801CD9F8, D_menu_801CD9FC, D_menu_801CDA00, D_menu_801CDA04,
                  D_menu_801CDA08, D_menu_801CDA20, D_menu_801CDA24, D_menu_801CDA28, 1);
    Matrix_Translate(gGfxMatrix, D_menu_801CEA58, D_menu_801CEA5C, D_menu_801CEA60, 1);
    Matrix_SetGfxMtx(&gMasterDisp);

    if (D_menu_801CD974 && D_menu_801CD944 != 0) {
        for (i = 0; i < 24; i++) {
            if (D_ctx_80177BD8[i] == 0) {
                continue;
            }
            if (sPaths[i].alpha == 0) {
                continue;
            }

            Map_801AC9A0(i);

            if (sPaths[i].unk_14) {
                Map_801AC200(i);
            }

            TexturedLine_DrawPath(i);
        }
    }

    Map_801A8F40();

    Map_801A9224();

    Map_801A9448();

    for (ptr = D_menu_801CD8A0, i = 0; i < 15; i++, ptr++) {
        Map_801A6A98(*ptr);
    }

    Map_801A8738();

    Matrix_Pop(&gGfxMatrix);

    if (D_menu_801CD96C) {
        Map_801ABF1C();
    }

    Map_801AB300();

    if (D_menu_801CEFC4) {
        Map_801A5834();
    }

    if (D_menu_801CD964) {
        Map_801A9910();
    }

    Map_801A9814();

    if (D_menu_801CD968) {
        Map_801A9A8C();
    }

    Map_801A9DE8();

    Map_801A5C90();

    if ((D_menu_801CD944 == 7) && (D_menu_801CD948 == 1)) {
        Map_801A4650();
    }
    if (D_menu_801CD944 == 0) {
        Map_801A0D14();
    }
    if (D_menu_801CD944 == 1) {
        Map_801A19A8();
    }

    if (D_menu_801CEEC8 == 0) {
        Map_801A07E8(D_menu_801B68B0[8], SEGMENTED_TO_VIRTUAL(D_menu_801B68D4[8]), &D_menu_801CD818[8]);
        D_menu_801CEEC8 = 5;
    } else {
        D_menu_801CEEC8--;
    }

    Map_801A07E8(D_menu_801B68B0[D_menu_801CEEC4 * 2], SEGMENTED_TO_VIRTUAL(D_menu_801B68D4[D_menu_801CEEC4 * 2]),
                 &D_menu_801CD818[D_menu_801CEEC4 * 2]);
    Map_801A07E8(D_menu_801B68B0[(D_menu_801CEEC4 * 2) + 1],
                 SEGMENTED_TO_VIRTUAL(D_menu_801B68D4[(D_menu_801CEEC4 * 2) + 1]),
                 &D_menu_801CD818[(D_menu_801CEEC4 * 2) + 1]);
    D_menu_801CEEC4++;
    if (D_menu_801CEEC4 > 3) {
        D_menu_801CEEC4 = 0;
    }

    Texture_Mottle((u16*) D_MAP_6047F80, (u16*) D_MAP_6048F80, 5);
}

s32 Map_801A05B4(void) {
    s32 i;
    s32 j;
    s32 sp30[10];
    s32 ret;
    s32 var_a3;
    s32 temp_a0;

    for (i = 0; i < 10; i++) {
        sp30[i] = 0;
    }

    for (i = 0; i < 10; i++) {
        temp_a0 = gSaveFile.save.data.unk_36[i];
        for (j = 0; j < temp_a0; j++) {
            var_a3 = gSaveFile.save.data.unk_5E[i][j].unk_0;
            if (gSaveFile.save.data.unk_5E[i][j].unk_C != 0) {
                var_a3 += 256;
            }
            sp30[i] += var_a3;
        }
    }

    ret = sp30[0];

    for (i = 1; i < 10; i++) {
        if (ret < sp30[i]) {
            ret = sp30[i];
        }
    }

    return ret;
}

void Map_801A0788(void) {
    D_ctx_80178410 = 800;

    Memory_FreeAll();
    func_play_800A5D6C();

    D_ctx_80178420 = 320.0f;
    D_ctx_80178424 = 240.0f;
    D_ctx_8017842C = 0.0f;
    D_ctx_80178430 = 0.0f;
}

void Map_801A07E8(u8* arg0, u8* arg1, f32* arg2) {
    s32* var_v0 = D_menu_801B0004;
    s32 temp;
    s32 i;
    s32 j;
    s32 k;

    arg1 = LOAD_ASSET(arg1);

    for (i = 1; i < 48; i++, var_v0++) {
        for (k = 0, j = *var_v0; j < (95 - *var_v0); j++, k++) {
            temp = D_menu_801B00C0[i - 1][k] + (s32) *arg2;

            if (temp > 95) {
                temp -= 95;
            }
            if (temp < 0) {
                temp += 95;
            }

            *(arg0 + ((i * 96) + j)) = *(arg1 + ((i * 96) + temp));
            *(arg0 + ((95 - i) * 96) + j) = *(arg1 + ((95 - i) * 96) + temp);
        }
    }

    *arg2 -= 1.0f;

    if (*arg2 <= 0.0f) {
        *arg2 = 95.0f;
    }

    if (*arg2 > 95.0f) {
        *arg2 = 0.0f;
    }
}

void Map_801A0954(void) {
    PlanetId planetId;
    static f32 D_menu_801B6934[] = {
        99.0f, 24, -90.0f, -150.0f, -208.0f, -276.0f,
    };

    switch (D_menu_801CD948) {
        case 100:
            break;

        case 0:
            D_menu_801CD9F0 = 0;
            D_menu_801CD9DC = 30.0f;
            D_menu_801CD9E0 = 230.0f;
            D_menu_801CD9E8 = 0;
            D_menu_801CD9E4 = 0;
            D_menu_801CD9EC = 0.29f;
            D_ctx_80178410 = 800;
            D_menu_801CD9C0 = 5;
            D_menu_801CD948++;
            break;

        case 1:
            if (D_menu_801CD9C0 != 0) {
                break;
            }

            if (gFillScreenAlpha != 0) {
                break;
            }

            if ((s32) D_menu_801CD9E0 == 205) {
                Audio_PlayVoiceWithoutBGM(1000);
            }

            if (D_menu_801CD9E0 > -355.0f) {
                D_menu_801CD9E0 -= D_menu_801CD9EC;
            }

            if ((D_menu_801CD9E0 < 200.0f) && (D_menu_801CD9E8 != 255)) {
                D_menu_801CD9E8 += 8;
                if (D_menu_801CD9E8 > 255) {
                    D_menu_801CD9E8 = 255;
                }
            }

            if (D_menu_801CD9E0 < D_menu_801B6934[D_menu_801CD9F0]) {
                D_menu_801CD9E4 += 8;
                if (D_menu_801CD9E4 > 255) {
                    D_menu_801CD9E4 = 255;
                }
            }

            if (D_menu_801CD9E0 <= -355.0f) {
                D_menu_801CD948++;
            }
            break;

        case 2:
            D_menu_801CD9E8 -= 16;
            if (D_menu_801CD9E8 < 0) {
                D_menu_801CD9E8 = 0;
                D_menu_801CD948++;
                D_menu_801CD9C0 = 20;
            }
            break;

        case 3:
            if (D_menu_801CD9C0 != 0) {
                break;
            }
            D_menu_801CD948 = 0;
            D_menu_801CD944 = 1;
            break;
    }

    if (gControllerPress[gMainController].button & START_BUTTON) {
        AUDIO_PLAY_BGM(SEQ_ID_WORLD_MAP);

        AUDIO_PLAY_SFX(0x4900001FU, gDefaultSfxSource, 4U);

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
        D_menu_801CD948 = 0;
        D_menu_801CD944 = 3;
    }
}

static const char* D_menu_801B6954[] = {
    D_MAP_6041A80, D_MAP_6035780, D_MAP_6033080, D_MAP_603A580, D_MAP_603F380, D_MAP_6037E80, D_MAP_603CC80,
};

void Map_801A0D14(void) {
    s32 i;
    static f32 D_menu_801B694C = 71.0f;
    static f32 D_menu_801B6950 = 205.0f;

    Map_801A116C();

    RCP_SetupDL(&gMasterDisp, 0x51);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 180, 180, 180, 255);

    Message_DisplayScrollingText(&gMasterDisp, gMsg_ID_1, D_menu_801CD9DC, D_menu_801CD9E0, 218, 70,
                                 Message_GetCharCount(gMsg_ID_1));

    RCP_SetupDL(&gMasterDisp, 0x4C);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    TextureRect_8bIA(&gMasterDisp, D_MAP_6019030, 8, 16, 0.0f, D_menu_801B694C, 40.0f, 1.66f);
    TextureRect_8bIA_MirY(&gMasterDisp, D_MAP_6019030, 8, 16, 0.0f, D_menu_801B6950, 40.0f, 1.68f);

    func_bg_8003DE68(71, 118);
    func_bg_8003DE68(205, 239);

    RCP_SetupDL(&gMasterDisp, 0x4C);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, D_menu_801CD9E8);

    TextureRect_16bRGBA(&gMasterDisp, D_menu_801B6954[D_menu_801CD9F0], 96, 52, 109.0f, 24.0f, 1.0f, 1.0f);

    if ((D_menu_801CD9E4 != 0) && (D_menu_801CD9F0 + 1 < 7)) {
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, D_menu_801CD9E4);

        TextureRect_16bRGBA(&gMasterDisp, D_menu_801B6954[D_menu_801CD9F0 + 1], 96, 52, 109.0f, 24.0f, 1.0f, 1.0f);

        if (D_menu_801CD9E4 == 255) {
            D_menu_801CD9E4 = 0;
            D_menu_801CD9F0++;
        }
    }
}

void Map_801A116C(void) {
    static f32 D_menu_801B6970 = 35.0f;
    WingInfo wings;
    Vec3f dest;
    Vec3f src;
    s32 colR = 30, colG = 9, colB = 5;
    s32 pad[5];

    src.x = 0.0f;
    src.y = 0.0f;
    src.z = 100.0f;

    Matrix_RotateY(gCalcMatrix, M_DTOR * 22.0f, 0);
    Matrix_RotateX(gCalcMatrix, M_DTOR * -70.0f, 1);
    Matrix_MultVec3f(gCalcMatrix, &src, &dest);

    if (D_menu_801CD948 >= 2) {
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

        RCP_SetupDL(&gMasterDisp, 0x2E);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, D_menu_801CD9E8);
    } else {
        RCP_SetupDL(&gMasterDisp, 0x17);
    }

    if ((D_menu_801CD948 < 2) || (D_menu_801CD9E8 != 0)) {
        Matrix_Push(&gGfxMatrix);
        Matrix_LookAt(gGfxMatrix, 0.0f, 0.0f, 430.0f, 0.0f, 180.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1);
        Matrix_SetGfxMtx(&gMasterDisp);

        Lights_SetOneLight(&gMasterDisp, dest.x, dest.y, dest.z, colR, colG, colB, 0, 0, 0);

        Matrix_Push(&gGfxMatrix);

        Matrix_Translate(gGfxMatrix, -60.0f, 293.0f, -360.0f, 1);
        Matrix_Scale(gGfxMatrix, 3.0f, 3.0f, 3.0f, 1);

        Matrix_RotateZ(gGfxMatrix, M_DTOR * -15.0f, 1);
        Matrix_RotateX(gGfxMatrix, M_DTOR * D_menu_801B6970, 1);
        Matrix_RotateY(gGfxMatrix, M_DTOR * -90.0f, 1);

        Matrix_SetGfxMtx(&gMasterDisp);

        wings.rightState = wings.leftState = 2;
        // clang-format off
        wings.unk_18 = wings.unk_1C = wings.unk_20 = wings.unk_24 = wings.unk_04 =
        wings.unk_08 = wings.unk_0C = wings.unk_10 = wings.unk_28 = 0.0f;
        // clang-format on

        wings.unk_14 = 0.0f;
        wings.unk_2C = 1;
        wings.unk_30 = 0.0f;
        wings.unk_34 = 0.0f;
        wings.unk_38 = 0.0f;

        func_display_80053658(&wings);

        Matrix_Pop(&gGfxMatrix);
        Matrix_Pop(&gGfxMatrix);
    }
    D_menu_801B6970 += 0.6f;
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

void Map_801A1528(void) {
    PlanetId planetId;
    f32 temp;

    switch (D_menu_801CD948) {
        case 0:
            temp = Math_SmoothStepToF(&D_menu_801CEA9C, 255.0f, D_menu_801CD9B0, 10.0f, 1.0f);

            D_menu_801CD9B0 *= 1.06f;

            if (temp == 0.0f) {
                D_menu_801CEAA0 = 0.0f;
                D_menu_801CEAA4 = 0.0f;
                D_menu_801CD9B0 = 0.002f;
                D_menu_801CD9B8 = 10;
                D_menu_801CD9BC = 45;
                D_menu_801CD948++;
            }
            break;

        case 1:
            if (D_menu_801CD9B8 != 0) {
                break;
            }

            Math_SmoothStepToF(&D_menu_801CEA9C, 0.0f, D_menu_801CD9B4, 50.0f, 0.1f);
            D_menu_801CD9B4 *= 1.06f;

            if (D_menu_801CD9BC != 0) {
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
                AUDIO_PLAY_SFX(0x4900001FU, gDefaultSfxSource, 4U);
                D_menu_801CD948 = 0;
                D_menu_801CD97C = 1;
                D_menu_801CD944 = 3;
            }
            break;
    }

    if (gControllerPress[gMainController].button & START_BUTTON) {
        AUDIO_PLAY_SFX(0x4900001FU, gDefaultSfxSource, 4U);

        for (planetId = 0; planetId < PLANET_MAX; planetId++) {
            if ((planetId == PLANET_SECTOR_Z) || (planetId == PLANET_SECTOR_X) || (planetId == PLANET_SECTOR_Y)) {
                sPlanets[planetId].alpha = 144;
            } else {
                sPlanets[planetId].alpha = 255;
            }
            D_menu_801CD900[planetId] = 255;
        }
        D_menu_801CD970 = 255;
        D_menu_801CD944 = 3;
        D_menu_801CD97C = 1;
    }
}

void Map_801A19A8(void) {
    s32 i;

    RCP_SetupDL(&gMasterDisp, 0x53);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, (s32) D_menu_801CEA9C);

    TextureRect_8bIA(&gMasterDisp, D_MAP_600D590, 168, 19, 72.0f, 104.0f, 1.0f, 1.0f);
}

void Map_801A1AE8(void) {
    f32 x;
    f32 y;
    f32 z;

    D_menu_801CEA64 = 0.04f;

    D_menu_801CEA54 = Map_801A25C8(sCurrentPlanetId);

    D_menu_801CDA40.x = sPlanets[sCurrentPlanetId].pos.x;
    D_menu_801CDA40.y = sPlanets[sCurrentPlanetId].pos.y;
    D_menu_801CDA40.z = sPlanets[sCurrentPlanetId].pos.z;

    D_menu_801CDA50.x = sPlanets[sCurrentPlanetId].pos.x;
    D_menu_801CDA50.y = sPlanets[sCurrentPlanetId].pos.y;
    D_menu_801CDA50.z = D_menu_801CDA40.z + D_menu_801CEA54;

    D_menu_801CDA2C = D_menu_801CDA00;
    D_menu_801CDA30 = D_menu_801CDA04;

    D_menu_801CDA34 = D_menu_801CD9F4;
    D_menu_801CDA38 = D_menu_801CD9F8;

    x = D_menu_801CDA50.x - D_menu_801CD9F4;
    y = D_menu_801CDA50.y - D_menu_801CD9F8;
    z = D_menu_801CDA50.z - D_menu_801CD9FC;

    D_menu_801CEA68 = sqrtf(SQ(x) + SQ(y) + SQ(z));
}

void Map_801A1C14(void) {
    s32 i;

    switch (D_menu_801CD948) {
        case 0:
            Map_801A1AE8();

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
            D_ctx_80178410 = 0;

            gFillScreenRed = 255;
            gFillScreenGreen = 255;
            gFillScreenBlue = 255;
            gFillScreenAlpha = 0;

            D_menu_801CEB3C = 0.0f;
            D_menu_801CEB38 = 255;

            D_menu_801CD948++;
            break;

        case 1:
            if (D_menu_801CD95C == 0) {
                if (sCurrentPlanetId == PLANET_CORNERIA) {
                    gFillScreenAlpha = 0;
                    D_menu_801CD948 = 10;
                    AUDIO_PLAY_SFX(0x0940A00BU, gDefaultSfxSource, 4U);
                } else {
                    AUDIO_PLAY_SFX(0x19003012U, gDefaultSfxSource, 4U);
                    D_menu_801CD948++;
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
                AUDIO_PLAY_SFX(0x19003012U, gDefaultSfxSource, 4U);
                D_menu_801CD948 = 2;
            }
            break;

        case 2:
            Map_801A2674();
            if ((D_menu_801CD9FC == D_menu_801CDA50.z) && (D_menu_801CD9D8 == 0)) {
                AUDIO_PLAY_SFX(0x19004013U, gDefaultSfxSource, 4U);
                D_menu_801CD9D8 = 1;
                if (sCurrentPlanetId == PLANET_CORNERIA) {
                    D_menu_801CEB48[0] = true;
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
            if ((D_menu_801CDA34 == D_menu_801CDA50.x) && (D_menu_801CDA38 == D_menu_801CDA50.y) &&
                (D_menu_801CD9FC == D_menu_801CDA50.z) && (D_menu_801CDA08 == D_menu_801CDA40.z)) {

                D_menu_801CD964 = 1;
                D_menu_801CD96C = 1;
                // clang-format off
                for (i = 0; i < 15; i++) {D_menu_801CD900[i] = 0;}
                // clang-format on
                D_menu_801CD970 = 0;

                if (Map_801A2304()) {
                    D_menu_801CD948 = 3;
                }
            }
            break;

        case 20:
            if (gControllerPress[gMainController].button & START_BUTTON) {
                D_menu_801CD948 = 21;
            }

            if (gControllerHold[gMainController].button & R_TRIG) {
                D_menu_801CD9FC += 10.0f;
            }

            if (gControllerHold[gMainController].button & Z_TRIG) {
                if (D_menu_801CD9FC - 10.0f > D_menu_801CDA08) {
                    D_menu_801CD9FC -= 10.0f;
                }
            }
            break;

        case 21:
            D_menu_801CD964 = 1;
            D_menu_801CD96C = 1;
            // clang-format off
            for (i = 0; i < 15; i++) {D_menu_801CD900[i] = 0;}
            // clang-format on
            D_menu_801CD970 = 0;

            if (Map_801A2304()) {
                D_menu_801CD948 = 3;
            }
            break;

        case 3:
            D_menu_801CD948 = 0;
            D_menu_801CD944 = 4;
            break;
    }
    D_menu_801CD9C4++;
}

bool Map_801A2304(void) {
    s32 ret = false;
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
                D_menu_801CD94C += 1;
                D_menu_801CD9B8 = 13;
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

            if (D_menu_801CD9B8 == 0) {
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

f32 Map_801A25C8(PlanetId planetId) {
    f32 sp4;

    switch (planetId) {
        case PLANET_AREA_6:
            sp4 = 900.0f;
            break;

        case PLANET_BOLSE:
            sp4 = 800.0f;
            break;

        case PLANET_METEO:
            sp4 = 650.0f;
            break;

        case PLANET_KATINA:
        case PLANET_MACBETH:
        case PLANET_ZONESS:
        case PLANET_TITANIA:
        case PLANET_AQUAS:
        case PLANET_FORTUNA:
            sp4 = 550.0f;
            break;

        case PLANET_CORNERIA:
            sp4 = 1100.0f;
            break;

        case PLANET_VENOM:
            sp4 = 2100.0f;
            break;

        case PLANET_SOLAR:
            sp4 = 850.0f;
            break;

        case PLANET_SECTOR_Z:
        case PLANET_SECTOR_X:
        case PLANET_SECTOR_Y:
            sp4 = 650.0f;
            break;

        default:
            break;
    }

    return sp4;
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
        if (D_ctx_80177BD8[i] == 0) {
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

    D_menu_801CEEE8[0].x = D_menu_801CEEE8[1].x = D_menu_801CD9F4;
    D_menu_801CEEE8[0].y = D_menu_801CEEE8[1].y = D_menu_801CD9F8;
    D_menu_801CEEE8[0].z = D_menu_801CEEE8[1].z = D_menu_801CD9FC;

    D_menu_801CEF58[0].x = D_menu_801CEF58[1].x = D_menu_801CDA00;
    D_menu_801CEF58[0].y = D_menu_801CEF58[1].y = D_menu_801CDA04;
    D_menu_801CEF58[0].z = D_menu_801CEF58[1].z = D_menu_801CDA08;

    D_menu_801CEF58[5].x = D_menu_801CEF58[4].x = D_menu_801CEF58[3].x = D_menu_801CEF58[2].x =
        sPlanets[sNextPlanetId].pos.x;
    D_menu_801CEF58[5].y = D_menu_801CEF58[4].y = D_menu_801CEF58[3].y = D_menu_801CEF58[2].y =
        sPlanets[sNextPlanetId].pos.y;
    D_menu_801CEF58[5].z = D_menu_801CEF58[4].z = D_menu_801CEF58[3].z = D_menu_801CEF58[2].z =
        sPlanets[sNextPlanetId].pos.z;

    D_menu_801CDA0C = -46.5f;
    D_menu_801CDA10 = 0.0f;
    D_menu_801CDA14 = 500.0f;

    Map_801AD718(D_menu_801CEF58[2].x, D_menu_801CEF58[2].y, D_menu_801CEF58[2].z, &D_menu_801CEEE8[2].x,
                 &D_menu_801CEEE8[2].y, &D_menu_801CEEE8[2].z, D_menu_801CDA14, D_menu_801CDA0C, D_menu_801CDA10);

    D_menu_801CEEE8[5].x = D_menu_801CEEE8[4].x = D_menu_801CEEE8[3].x = D_menu_801CEEE8[2].x;
    D_menu_801CEEE8[5].y = D_menu_801CEEE8[4].y = D_menu_801CEEE8[3].y = D_menu_801CEEE8[2].y;
    D_menu_801CEEE8[5].z = D_menu_801CEEE8[4].z = D_menu_801CEEE8[3].z = D_menu_801CEEE8[2].z;

    D_menu_801CEF58[7].x = D_menu_801CEF58[6].x = -150.55215f;
    D_menu_801CEF58[7].y = D_menu_801CEF58[6].y = -489.68f;
    D_menu_801CEF58[7].z = D_menu_801CEF58[6].z = 0.0f;

    D_menu_801CDA0C = -42.750008f;
    D_menu_801CDA10 = -9.849999f;
    D_menu_801CDA14 = 3375.000000f;

    Map_801AD718(D_menu_801CEF58[6].x, D_menu_801CEF58[6].y, D_menu_801CEF58[6].z, &D_menu_801CEEE8[6].x,
                 &D_menu_801CEEE8[6].y, &D_menu_801CEEE8[6].z, D_menu_801CDA14, D_menu_801CDA0C, D_menu_801CDA10);

    D_menu_801CEEE8[7].x = D_menu_801CEEE8[6].x;
    D_menu_801CEEE8[7].y = D_menu_801CEEE8[6].y;
    D_menu_801CEEE8[7].z = D_menu_801CEEE8[6].z;

    D_menu_801CEECC = Map_801A655C(sCurrentPlanetId, sNextPlanetId);

    if (D_menu_801CD93C == 2) {
        D_ctx_80177BD8[D_menu_801CEECC] = 5;
        sPaths[D_menu_801CEECC].unk_14 = 5;
    } else {
        D_ctx_80177BD8[D_menu_801CEECC] = 2;
        sPaths[D_menu_801CEECC].unk_14 = 1;
    }
}

void Map_801A2B8C(void) {
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
                D_menu_801CD9C0 = 30;

                if ((D_menu_801CD98C == 1) || (D_menu_801CD980 == 1)) {
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
            if (D_menu_801CD9C0 != 0) {
                break;
            }

            if ((D_menu_801CD984 == 255) && (gFillScreenAlpha == 0)) {
                D_menu_801CD980 = 0;
                D_menu_801CD9C0 = 30;
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
            if (D_menu_801CD9C0 != 0) {
                break;
            }
            if ((D_menu_801CD98C == 1) || (D_menu_801CD980 == 1)) {
                break;
            }
            D_menu_801CD9C4 = 0;
            D_menu_801CD9C0 = 30;
            D_menu_801CD94C = 1;
            break;

        case 1:
            if (D_menu_801CD9C0 != 0) {
                break;
            }
            Map_801A2EB8();
            break;

        case 2:
            if (D_menu_801CD9C0 != 0) {
                break;
            }

            for (i = 0; i < 15; i++) {
                D_menu_801CD900[i] = 255;
            }
            D_menu_801CD9C0 = 0;
            D_menu_801CD94C++;
            break;

        case 3:
            if (D_menu_801CD9C0 != 0) {
                break;
            }
            D_menu_801CEFC8 = 1;
            D_menu_801CD97C = 1;
            D_menu_801CD94C = 0;
            D_menu_801CD944 = 3;
            break;
    }

    func_play_800B6F50(D_menu_801CD9F4, D_menu_801CD9F8, D_menu_801CD9FC, D_menu_801CDA00, D_menu_801CDA04,
                       D_menu_801CDA08);

    D_menu_801CD9C4++;
}

void Map_801A2EB8(void) {
    s32 i;
    s32 temp1;
    s32 temp2;

    if (D_menu_801CD9C4 == 30) {
        if (D_menu_801CD93C == 2) {
            AUDIO_PLAY_SFX(0x0900802AU, gDefaultSfxSource, 4U);
        } else {
            AUDIO_PLAY_SFX(0x09000032U, gDefaultSfxSource, 4U);
        }
    }

    Map_801A3440(D_menu_801CEEE0);

    if (D_menu_801CD9C4 == 80) {
        sCurrentPlanetId = sNextPlanetId;
        D_ctx_80177B90[gCurrentPlanet] = sCurrentPlanetId;
        Map_801A6368();
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
            if (D_ctx_80177BD8[i] == 0) {
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
        AUDIO_PLAY_SFX(0x19000026U, gDefaultSfxSource, 4U);
    }

    if ((D_menu_801CEED8 == 5) && (D_menu_801CEEDC == 0.0f)) {
        if (D_menu_801CD93C != 2) {
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
            temp1 = Map_801A655C(sNextPlanetId, sPlanets[sNextPlanetId].dest1);
            D_ctx_80177BD8[temp1] = 1;
            sPaths[temp1].alpha = 255;
            D_menu_801CEED4 = temp1;
        }

        D_menu_801CEED0 = -1;
        if (sPlanets[sNextPlanetId].dest2 != PLANET_NONE) {
            temp2 = Map_801A655C(sNextPlanetId, sPlanets[sNextPlanetId].dest2);
            D_ctx_80177BD8[temp2] = 1;
            sPaths[temp2].alpha = 255;
            D_menu_801CEED0 = temp2;
        }
        D_menu_801CD9C0 = 50;
        D_menu_801CD94C++;
    }
}

void Map_801A3440(f32 arg0) {
    Vec3f vec[2];

    if (D_menu_801CEED8 != -1) {
        Map_801A3550(vec, &D_menu_801CEEE8[D_menu_801CEED8], &D_menu_801CEF58[D_menu_801CEED8], D_menu_801CEEDC);
        D_menu_801CD9F4 = vec[0].x;
        D_menu_801CD9F8 = vec[0].y;
        D_menu_801CD9FC = vec[0].z;
        D_menu_801CDA00 = vec[1].x;
        D_menu_801CDA04 = vec[1].y;
        D_menu_801CDA08 = vec[1].z;
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

void Map_801A36A8(void) {
    s32 i;
    f32 temp;

    switch (D_menu_801CD948) {
        case 0:
            gFillScreenRed = 0;
            gFillScreenGreen = 0;
            gFillScreenBlue = 0;
            gFillScreenAlpha = 255;

            for (i = 0; i < 8; i++) {
                D_menu_801CF020[i] = D_menu_801B69D4[i];
                D_menu_801CF040[i] = D_menu_801B69F4[i];
                D_menu_801CF060[i] = D_menu_801B6A14[i];
            }

            D_menu_801CF0C8 = D_menu_801B6A34[1];
            D_menu_801CF0CC = D_menu_801B6A3C[1];
            D_menu_801CF0D0 = D_menu_801B6A44[1];

            D_menu_801CF120 = 0;
            D_menu_801CEA9C = 255.0f;
            D_menu_801CF080 = 1.0f;
            D_menu_801CD948 = 10;

            AUDIO_PLAY_BGM(SEQ_ID_GAME_OVER);
            break;

        case 10:
            temp = Math_SmoothStepToF(&D_menu_801CEA9C, 0.0f, 1.0f, 100.0f, 1.0f);

            gFillScreenAlpha = D_menu_801CEA9C;

            if (temp == 0.0f) {
                gFillScreenAlpha = 0;
                D_menu_801CD9C0 = 0;
                D_menu_801CD948 = 20;
            }
            break;

        case 20:
            if (D_menu_801CD9C0 != 0) {
                break;
            }
            D_menu_801CD94C = 0;
            D_menu_801CD9C0 = 0;
            D_menu_801CD948 = 1;
            break;

        case 1:
            if (D_menu_801CF120) {
                D_menu_801CDA1C += 0.03f;
            }
            if (D_menu_801CD9C0) {
                break;
            }
            Map_801A3A00();
            break;

        case 2:
            Map_801A4394();
            break;

        case 3:
            gFillScreenAlpha += 32;
            if (gFillScreenAlpha > 255) {
                gFillScreenAlpha = 255;
                D_menu_801CD948++;
            }
            break;

        case 4:
            gGameState = GSTATE_MENU;
            gNextGameStateTimer = 2;
            gOptionMenuStatus = OPTION_WAIT;
            gDrawMode = 0;
            D_ctx_80178410 = 0;
            break;
    }

    if (gControllerPress[gMainController].button & (A_BUTTON | START_BUTTON)) {
        AUDIO_PLAY_SFX(0x49000003U, gDefaultSfxSource, 4U);
        D_menu_801CD948 = 3;
    }
}

void Map_801A3A00(void) {
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
                D_menu_801CF088[i] = 0.0f;
                D_menu_801CF0A8[i] = 0.0f;
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

                temp1[i] = Math_SmoothStepToF(&D_menu_801CF020[i], *(D_menu_801CF0C8 + i), 0.05f, 100.0f, 10.0f);
                temp2[i] = Math_SmoothStepToF(&D_menu_801CF040[i], *(D_menu_801CF0CC + i), 0.05f, 100.0f, 10.0f);
                temp3[i] = Math_SmoothStepToF(&D_menu_801CF060[i], *(D_menu_801CF0D0 + i), 0.1f, 100.0f, 0.1f);

                if (temp1[i] == 0.0f && temp2[i] == 0.0f && temp3[i] == 0.0f) {
                    D_menu_801CF088[i] = 0.0f;
                    if (temp3[i] == 0.0f) {
                        D_menu_801CF0F8[i] = 1;
                    }
                } else {
                    D_menu_801CF088[i] += 10.0f;
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
                    D_menu_801CF088[i] = 0.0f;
                    D_menu_801CF0D8[i] = i * 10;
                    D_menu_801CF0F8[i] = 0;
                }
                D_menu_801CD9C0 = 60;
                D_menu_801CD9BC = 85;
                D_menu_801CD94C = 11;
            }
            break;

        case 11:
            if (D_menu_801CD9C0) {
                break;
            }

            if (D_menu_801CD9BC) {
                for (i = 0; i < 8; i++) {
                    Math_SmoothStepToF(&D_menu_801CF088[i], 360.0f, 0.3f, 100.0f, 1.0f);
                    Math_SmoothStepToF(&D_menu_801CF0A8[i], 360.0f, 0.3f, 100.0f, 1.0f);
                }
            } else {
                D_menu_801CD94C = 10;
            }
            break;

        case 10:
            if (!D_menu_801CD9B8) {
                if (!D_menu_801CF120) {
                    D_menu_801CEAA0 = 0.0f;
                    D_menu_801CD9B8 = 25;
                    D_menu_801CD94C = 3;
                } else {
                    for (i = 0; i < 8; i++) {
                        D_menu_801CF088[i] = 0.0f;
                        D_menu_801CF0A8[i] = 0.0f;
                        D_menu_801CF0F8[i] = 0;
                    }
                    D_menu_801CEFCC = 0;
                    D_menu_801CF0D8[0] = 4;
                    D_menu_801CD94C = 2;
                }
            }
            break;

        case 2:
            if (D_menu_801CF0D8[0]) {
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

                        D_menu_801CD9C0 = 15;
                        if (D_menu_801CF11C) {
                            D_menu_801CD9C0 = 240;
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

                if (D_menu_801CF0A8[i] > 360.0f) {
                    D_menu_801CF0A8[i] = 0.0f;
                    D_menu_801CF0F8[i] = 1;
                } else {
                    D_menu_801CF0A8[i] += 10.0f;
                }
            }
            break;

        case 3:
            if (D_menu_801CD9B8 != 0) {
                break;
            }

            for (i = 0; i < 8; i++) {
                D_menu_801CF088[i] += 30.0f;
                D_menu_801CF060[i] += -300.0f;
                if (D_menu_801CF060[i] <= -120000.0f) {
                    D_menu_801CF060[i] = -12000.0f;
                }
            }

            if (D_menu_801CF060[0] <= -11000.0f) {
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
                D_menu_801CF080 = 0.0f;
                D_menu_801CD948 = 2;
                D_menu_801CD94C = 0;
            }
            break;
    }
}

void Map_801A4394(void) {
    s32 i;

    switch (D_menu_801CD94C) {
        case 0:
            if (gCurrentPlanet == 0) {
                D_menu_801CD9C0 = 45;
                D_menu_801CD94C = 3;
            } else {
                D_menu_801CD94C++;
            }
            break;

        case 1:
            if (gCurrentPlanet == D_menu_801CD9AC) {
                D_menu_801CD94C = 3;
                D_menu_801CD9C0 = 45;
                break;
            }

            if ((sPaths[D_menu_801CD8E0[D_menu_801CD9AC]].type == 3) ||
                (sPaths[D_menu_801CD8E0[D_menu_801CD9AC]].type == 4)) {
                D_ctx_80177BD8[D_menu_801CD8E0[D_menu_801CD9AC]] = 5;
                sPaths[D_menu_801CD8E0[D_menu_801CD9AC]].unk_14 = 5;
            } else {
                D_ctx_80177BD8[D_menu_801CD8E0[D_menu_801CD9AC]] = 2;
                sPaths[D_menu_801CD8E0[D_menu_801CD9AC]].unk_14 = 0;
            }

            sPaths[D_menu_801CD8E0[D_menu_801CD9AC]].alpha = 255;
            D_menu_801CEEAC = 255;
            D_menu_801CEEA8 = 255;
            D_menu_801CD94C++;
            break;

        case 2:
            if ((D_ctx_80177BD8[D_menu_801CD8E0[D_menu_801CD9AC]] == 3) ||
                (D_ctx_80177BD8[D_menu_801CD8E0[D_menu_801CD9AC]] == 6)) {
                D_menu_801CD9AC++;
                D_menu_801CD94C = 1;
            }
            break;

        case 3:
            if (D_menu_801CD9C0 != 0) {
                break;
            }

            for (i = 0; i < 8; i++) {
                D_menu_801CF020[i] = D_menu_801B69D4[i];
                D_menu_801CF040[i] = D_menu_801B69F4[i];
                D_menu_801CF060[i] = D_menu_801B6A14[i];
            }

            D_menu_801CD978 = 1;
            D_menu_801CF120 = 1;
            D_menu_801CF11C = 1;

            D_menu_801CF0C8 = D_menu_801B6A34[1];
            D_menu_801CF0CC = D_menu_801B6A3C[1];
            D_menu_801CF0D0 = D_menu_801B6A44[1];

            D_menu_801CF080 = 1.0f;
            D_menu_801CD9C0 = 450;
            D_menu_801CD94C = 0;
            D_menu_801CD948 = 1;
            break;
    }
}

void Map_801A4650(void) {
    s32 i;
    static Gfx* D_menu_801B6A4C[] = {
        D_FONT3D_9006AE0, D_FONT3D_90086F0, D_FONT3D_9005380, D_FONT3D_90075A0,
        D_FONT3D_9000570, D_FONT3D_9002EA0, D_FONT3D_90075A0, D_FONT3D_9004230,
    };

    Lights_SetOneLight(&gMasterDisp, 0, 0, 127, 28, 58, 105, 65, 70, 48);

    RCP_SetupDL(&gMasterDisp, 0x17);

    gSPTexture(gMasterDisp++, 2500, 200, 0, G_TX_RENDERTILE, G_ON);
    gSPSetGeometryMode(gMasterDisp++, G_TEXTURE_GEN);

    Matrix_Push(&gGfxMatrix);

    Matrix_LookAt(gGfxMatrix, 0.0f, 0.0f, 500.0f, 0.0f, 0.0f, -500.0f, 0.0f, 1.0f, 0.0f, 1);

    Matrix_SetGfxMtx(&gMasterDisp);

    for (i = 0; i < 8; i++) {
        Matrix_Push(&gGfxMatrix);

        Matrix_Translate(gGfxMatrix, D_menu_801CF020[i], D_menu_801CF040[i], D_menu_801CF060[i], 1);
        Matrix_RotateY(gGfxMatrix, M_DTOR * D_menu_801CF0A8[i], 1);
        Matrix_RotateX(gGfxMatrix, M_DTOR * D_menu_801CF088[i], 1);
        Matrix_Scale(gGfxMatrix, D_menu_801CF080, D_menu_801CF080, D_menu_801CF080, 1);

        Matrix_SetGfxMtx(&gMasterDisp);

        gSPDisplayList(gMasterDisp++, D_menu_801B6A4C[i]);

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

    Math_SmoothStepToF(&D_menu_801CDA34, D_menu_801CDA50.x, speed, 100.0f, 0.1f);
    Math_SmoothStepToF(&D_menu_801CDA38, D_menu_801CDA50.y, speed, 100.0f, 0.1f);
    Math_SmoothStepToF(&D_menu_801CD9FC, D_menu_801CDA50.z, speed, 100.0f, 0.1f);

    x = D_menu_801CDA50.x - D_menu_801CDA34;
    y = D_menu_801CDA50.y - D_menu_801CDA38;
    z = D_menu_801CDA50.z - D_menu_801CD9FC;

    temp = sqrtf(SQ(x) + SQ(y) + SQ(z));

    angle = M_DTOR * ((1 - (temp / D_menu_801CEA68)) * 180.0f);

    D_menu_801CD9F4 = D_menu_801CDA34 * (1 + __sinf(angle) * 1.1f);
    D_menu_801CD9F8 = D_menu_801CDA38 * (1 + __sinf(angle) * 1.3f);
}

void Map_801A4A38(f32 arg0) {
    Math_SmoothStepToF(&D_menu_801CDA2C, D_menu_801CDA40.x, arg0, 100.0f, 0.1f);
    Math_SmoothStepToF(&D_menu_801CDA30, D_menu_801CDA40.y, arg0, 100.0f, 0.1f);
    Math_SmoothStepToF(&D_menu_801CDA08, D_menu_801CDA40.z, arg0, 100.0f, 0.1f);
    D_menu_801CDA00 = D_menu_801CDA2C;
    D_menu_801CDA04 = D_menu_801CDA30;
}

void Map_801A4AE8(void) {
    s32 var_a0;
    s32 i;

    switch (D_menu_801CD94C) {
        case 0:
            Map_801A4D7C();
            break;

        case 1:
            if (D_menu_801CF000[D_menu_801CEFDC] == 0) {
                if (D_menu_801CEFD0 != 0) {
                    if (gLifeCount[gPlayerNum] != 0) {
                        func_8001D520();
                        D_menu_801CD9CC = 1;
                        D_menu_801CD9D0 = 0;
                        D_menu_801CD9B8 = 120;
                    } else {
                        D_menu_801CD9D4 = 1;
                        D_menu_801CD9B8 = 0;
                    }
                } else {

                    D_menu_801CD9B8 = 0;
                }
                D_menu_801CEFC4 = 0;
                D_menu_801CD94C = 2;
            }
            break;

        case 2:
            if ((D_menu_801CD9CC != 0) && (D_menu_801CD9B8 == 110)) {
                gLifeCount[gPlayerNum]--;
            }

            if (D_menu_801CD9B8 == 0) {
                D_menu_801CD9CC = 0;

                var_a0 = D_menu_801CEFDC;
                if (D_menu_801CD93C != 0) {
                    var_a0 += 2;
                }

                Map_801A4D0C(var_a0);

                if (D_menu_801CEFDC == 0) {
                    for (i = 0; i < TEAM_ID_MAX; i++) {
                        D_ctx_80177C58[i] = gTeamShields[i];
                    }
                    D_menu_801CEFC8 = 0;
                    D_menu_801CD948 = 0;
                    D_menu_801CD944 = 2;
                } else {
                    D_menu_801CD944 = 3;
                }
                D_menu_801CD94C = 0;
            }
            break;
    }
}

void Map_801A4D0C(u32 arg0) {
    switch (arg0) {
        case 1:
        case 4:
            if (D_menu_801CD9D4 != 0) {
                Map_801A4F8C();
            } else {
                Map_801A4FC4();
            }
            break;

        case 3:
            Map_801A53C8();

        case 0:
        case 2:
            break;
    }
}

void Map_801A4D7C(void) {
    f32 temp;

    if (Map_801A5770() != 0) {
        D_menu_801CEFE8[D_menu_801CEFDC] = 255.0f;
        if (D_menu_801CD93C != 0) {
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
        func_8001D6DC(0);
        D_menu_801CEFC4 = 0;
        D_menu_801CD944 = 3;
        return;
    }

    if (gControllerPress[gMainController].button & A_BUTTON) {
        func_8001D6DC(0);
        AUDIO_PLAY_SFX(0x49000003U, gDefaultSfxSource, 4U);
        D_menu_801CF000[D_menu_801CEFDC] = 10;

        if (((D_menu_801CD93C != 0) && (D_menu_801CEFDC == 2)) || ((D_menu_801CD93C == 0) && (D_menu_801CEFDC == 1))) {
            D_menu_801CEFD0 = 1;
            D_menu_801CF00C = 10;
        }
        D_menu_801CD94C = 1;
    }
}

void Map_801A4F8C(void) {
    D_ctx_80178410 = 0;
    gGameState = GSTATE_GAME_OVER;
    D_ctx_80177868 = 0;
    gNextGameStateTimer = 2;
    gDrawMode = DRAW_NONE;
}

void Map_801A4FC4(void) {
    s32 i;
    s32 temp;
    s32 temp2;

    gPlayerNum = 0;

    for (i = 0; i < 6; i++) {
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
        temp2 = Map_801A655C(sCurrentPlanetId, sPlanets[sCurrentPlanetId].dest1);
        D_ctx_80177BD8[temp2] = 0;
        sPaths[temp2].alpha = 0;
    }

    if (sPlanets[sCurrentPlanetId].dest2 != PLANET_NONE) {
        temp = Map_801A655C(sCurrentPlanetId, sPlanets[sCurrentPlanetId].dest2);
        D_ctx_80177BD8[temp] = 0;
        sPaths[temp].alpha = 0;
    }

    if (sPlanets[sCurrentPlanetId].warp != PLANET_NONE) {
        temp = Map_801A655C(sCurrentPlanetId, sPlanets[sCurrentPlanetId].warp);
        D_ctx_80177BD8[temp] = 0;
        sPaths[temp].alpha = 0;
    }

    sPaths[D_menu_801CEECC].unk_14 = 0;
    D_menu_801CEEA0 = 0;
    D_menu_801CEEA4 = 0;
    D_menu_801CEEA8 = 255;
    D_menu_801CEEAC = 255;

    gTotalHits -= D_ctx_80177B70[gCurrentPlanet - 1];
    D_ctx_80177B90[gCurrentPlanet] = PLANET_NONE;
    D_ctx_80177B70[gCurrentPlanet - 1] = 0;
    D_ctx_80177BB0[gCurrentPlanet - 1] = 0;
    D_ctx_80177B50[gCurrentPlanet - 1] = 0x00FFFFFF;
    gHitCount = 0;
    gCurrentPlanet--;

    D_menu_801CD83C = Map_801A05B4();

    sCurrentPlanetId = D_menu_801CD950;

    if (sPlanets[sCurrentPlanetId].dest1 != PLANET_NONE) {
        temp2 = Map_801A655C(sCurrentPlanetId, sPlanets[sCurrentPlanetId].dest1);
        D_ctx_80177BD8[temp2] = 1;
        sPaths[temp2].alpha = 255;
    }

    if (sPlanets[sCurrentPlanetId].dest2 != PLANET_NONE) {
        temp = Map_801A655C(sCurrentPlanetId, sPlanets[sCurrentPlanetId].dest2);
        D_ctx_80177BD8[temp] = 1;
        sPaths[temp].alpha = 255;
    }

    if (sPlanets[sCurrentPlanetId].warp != PLANET_NONE) {
        temp = Map_801A655C(sCurrentPlanetId, sPlanets[sCurrentPlanetId].warp);
        D_ctx_80177BD8[temp] = 0;
        sPaths[temp].alpha = 0;
    }

    Map_801A6368();
}

void Map_801A53C8(void) {
    s32 temp;
    s32 temp2;

    D_menu_801CEFD8 ^= 1;

    if (sPlanets[sCurrentPlanetId].dest1 != PLANET_NONE) {
        temp2 = Map_801A655C(sCurrentPlanetId, sPlanets[sCurrentPlanetId].dest1);
        D_ctx_80177BD8[temp2] = 0;
        sPaths[temp2].alpha = 0;
    }

    if (sPlanets[sCurrentPlanetId].dest2 != PLANET_NONE) {
        temp = Map_801A655C(sCurrentPlanetId, sPlanets[sCurrentPlanetId].dest2);
        D_ctx_80177BD8[temp] = 0;
        sPaths[temp].alpha = 0;
    }

    D_ctx_80177BD8[D_menu_801CEECC] = 0;

    sPaths[D_menu_801CEECC].alpha = 0;
    sPaths[D_menu_801CEECC].unk_14 = 0;

    sCurrentPlanetId = D_menu_801CD950;

    if (!D_menu_801CEFD8) {
        sNextPlanetId = sPlanets[sCurrentPlanetId].dest1;
    } else if (D_menu_801CD93C != 2) {
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

    D_menu_801CEECC = Map_801A655C(sCurrentPlanetId, sNextPlanetId);

    sPaths[D_menu_801CEECC].alpha = 255;

    D_ctx_80177BD8[D_menu_801CEECC] = 3;

    sPaths[D_menu_801CEECC].unk_14 = 2;

    if ((sPaths[D_menu_801CEECC].type == PL_WARP_YLW) || (sPaths[D_menu_801CEECC].type == PL_WARP_RED)) {
        D_ctx_80177BD8[D_menu_801CEECC] = 5;
        sPaths[D_menu_801CEECC].unk_14 = 5;
    }

    D_menu_801CEEA0 = 0;
    D_menu_801CEEA4 = 100;
    D_menu_801CEEA8 = 255;
    D_menu_801CEEAC = 255;

    sCurrentPlanetId = sNextPlanetId;
    D_ctx_80177B90[gCurrentPlanet] = sCurrentPlanetId;

    Map_801A6368();

    if (sPlanets[sNextPlanetId].dest1 != PLANET_NONE) {
        temp2 = Map_801A655C(sNextPlanetId, sPlanets[sNextPlanetId].dest1);
        D_ctx_80177BD8[temp2] = 1;
        sPaths[temp2].alpha = 255;
    }

    if (sPlanets[sNextPlanetId].dest2 != PLANET_NONE) {
        temp = Map_801A655C(sNextPlanetId, sPlanets[sNextPlanetId].dest2);
        D_ctx_80177BD8[temp] = 1;
        sPaths[temp].alpha = 255;
    }
}

bool Map_801A5770(void) {
    bool ret = false;
    s8 y = gControllerPress[gMainController].stick_y;

    if ((y > -40) && (y < 40)) {
        y = 0;
    }

    if (y != 0) {
        if (D_menu_801CEFD4 == 0) {
            ret = true;
        }
        D_menu_801CEFD4 = y;
    } else {
        D_menu_801CEFD4 = 0;
    }

    if (ret) {
        AUDIO_PLAY_SFX(0x49000002, gDefaultSfxSource, 4);
    }

    return ret;
}

void Map_801A5834(void) {
    s32 i;
    f32 x;
    f32 y;
    f32 z;
    u8* texture;
    s32 colorIndex;
    s32 var_t0;
    s32 mask;
    s32 r[3];
    s32 g[3];
    s32 b[3];
    static f32 D_menu_801B6A6C[] = { 3.05f, 4.15f };

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

    var_t0 = 1;
    if (D_menu_801CD93C == 0) {
        var_t0 = 0;
    }

    if (gLifeCount[gPlayerNum]) {
        texture = D_MAP_6001080;
    } else {
        texture = D_MAP_6000000;
    }

    RCP_SetupDL(&gMasterDisp, 0x4C);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 60, 60, 255, 170);

    TextureRect_8bIA(&gMasterDisp, D_MAP_601B4B0, 24, 17, x, y, 4.6f, D_menu_801B6A6C[var_t0]);

    mask = 0xFFFFFFFF;
    if (D_menu_801CF000[colorIndex] != 0) {
        mask = 0x00000001;
        D_menu_801CF000[colorIndex]--;
    }

    if (gGameFrameCount & mask) {
        RCP_SetupDL(&gMasterDisp, 0x53);
        gDPSetPrimColor(gMasterDisp++, 0, 0, r[colorIndex], g[colorIndex], b[colorIndex], 255);
        TextureRect_8bIA(&gMasterDisp, D_MAP_6000840, 96, 22, x + 11.0f, y + 3.0f, 1.0f, 1.0f);
    }
    z = 24.0f;
    colorIndex++;

    if (D_menu_801CD93C != 0) {
        mask = 0xFFFFFFFF;
        if (D_menu_801CF000[colorIndex] != 0) {
            mask = 0x00000001;
            D_menu_801CF000[colorIndex]--;
        }

        if (gGameFrameCount & mask) {
            gDPSetPrimColor(gMasterDisp++, 0, 0, r[colorIndex], g[colorIndex], b[colorIndex], 255);
            TextureRect_8bIA(&gMasterDisp, D_MAP_60018C0, 96, 10, x + 10.0f, y + z + 8.0f, 1.0f, 1.0f);
        }
        z += 18.0f;
        colorIndex++;
    }

    mask = 0xFFFFFFFF;
    if (D_menu_801CF000[colorIndex] != 0) {
        mask = 0x00000001;
        D_menu_801CF000[colorIndex]--;
    }

    if (gGameFrameCount & mask) {
        gDPSetPrimColor(gMasterDisp++, 0, 0, r[colorIndex], g[colorIndex], b[colorIndex], 255);
        TextureRect_8bIA(&gMasterDisp, texture, 96, 22, x + 9.0f, y + z + 5.0f, 1.0f, 1.0f);
    }
}

void Map_801A5C90(void) {
    s32 pad[3];
    f32 scale;

    if (D_menu_801CD9CC != 0) {
        if (gLifeCount[gPlayerNum] < 10) {
            scale = 0.13f;
        } else {
            scale = 0.18f;
        }

        switch (D_menu_801CD9CC) {
            case 1:
                D_menu_801CD9C0 = 2;
                D_menu_801CD9CC = 2;
                break;

            case 2:
                if (D_menu_801CD9C0 != 0) {
                    break;
                }

                if ((D_menu_801CD9D0 + 1) > 3) {
                    D_menu_801CD9D0 = 0;
                    D_menu_801CD9CC = 0;
                } else {
                    D_menu_801CD9D0++;
                    D_menu_801CD9CC = 1;
                }
                break;
        }

        Matrix_Push(&gGfxMatrix);

        Matrix_LookAt(gGfxMatrix, 0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1);

        Matrix_SetGfxMtx(&gMasterDisp);

        RCP_SetupDL(&gMasterDisp, 0x35);

        Matrix_Push(&gGfxMatrix);

        Matrix_Translate(gGfxMatrix, 45.0f, 32.0f, 0.01f, 1);
        Matrix_Scale(gGfxMatrix, scale, scale, scale, 1);

        Matrix_SetGfxMtx(&gMasterDisp);

        gSPDisplayList(gMasterDisp++, D_menu_801AF824[D_menu_801CD9D0]);

        Matrix_Pop(&gGfxMatrix);
    }
}

void Map_801A5E80(void) {
    switch (D_menu_801B8280) {
        case 0:
            D_menu_801B8284 = 0;
            D_menu_801CD9A0 = 1;
            Map_801A6368();
            D_menu_801CD9A8 = Map_801A62FC(sCurrentPlanetId);
            Map_801AB284();
            D_menu_801B8280++;
            break;

        case 1:
            if ((gControllerPress[gMainController].button & START_BUTTON) && !(D_menu_801CD9A8)) {
                Audio_KillSfxById(0x4100001EU);
                Audio_ClearVoice();
                D_menu_801CF018 = 0;
                D_menu_801B8280 = 2;
                D_menu_801CD9B8 = 0;
            }

            if ((gControllerPress[gMainController].button & A_BUTTON) && (D_menu_801CD9A0 == 0) && !(D_menu_801CD9A8)) {
                Audio_ClearVoice();
                D_Timer_801782AC = 0;
            }

            if ((gControllerPress[gMainController].button & A_BUTTON) && (D_menu_801CD9A0 == 1) && !(D_menu_801CD9A8)) {
                D_menu_801CD9A0 = 0;
            }

            if (D_menu_801CF018 == 7) {
                D_menu_801CD9B8 = 5;
                D_menu_801B8280++;
            }
            break;

        case 2:
            if (D_menu_801CD9B8 != 0) {
                break;
            }

            if (D_menu_801B8284 < 120) {
                D_menu_801B8284 += 15;
                if (sCurrentPlanetId == PLANET_CORNERIA) {
                    D_menu_801CEB48[0] = false;
                }
            } else {
                D_menu_801CD9B8 = 5;
                D_menu_801CF018 = 0;
                D_menu_801B8280++;
            }
            break;

        case 3:
            if (D_menu_801CD9B8 == 0) {
                D_menu_801CD9B8 = 5;
                D_menu_801CD968 = 1;
                D_menu_801B8280++;
            }
            break;

        case 4:
            if (D_menu_801CD9B8 == 0) {
                AUDIO_PLAY_SFX(0x49002016U, gDefaultSfxSource, 4U);
                D_menu_801CD9B8 = 75;
                D_menu_801B8280++;
            }
            break;

        case 5:
            if (D_menu_801CD9B8 == 0) {
                Map_801A61B4(gCurrentLevel);
                D_menu_801B8280 = 0;
                D_menu_801CD968 = 0;
                Map_801A6628();
            }
            break;
    }
}

void Map_801A61B4(LevelId level) {
    switch (level) {
        case LEVEL_CORNERIA:
            Audio_SetAudioSpec(0, 0);
            break;

        case LEVEL_METEO:
            Audio_SetAudioSpec(0, 1);
            break;

        case LEVEL_TITANIA:
            Audio_SetAudioSpec(0, 2);
            break;

        case LEVEL_AQUAS:
            Audio_SetAudioSpec(0, 12);
            break;

        case LEVEL_BOLSE:
            Audio_SetAudioSpec(0, 10);
            break;

        case LEVEL_KATINA:
            Audio_SetAudioSpec(0, 11);
            break;

        case LEVEL_AREA_6:
            Audio_SetAudioSpec(0, 5);
            break;

        case LEVEL_SECTOR_Z:
            Audio_SetAudioSpec(0, 13);
            break;

        case LEVEL_FORTUNA:
            Audio_SetAudioSpec(0, 8);
            break;

        case LEVEL_SECTOR_X:
            Audio_SetAudioSpec(0, 3);
            break;

        case LEVEL_MACBETH:
            Audio_SetAudioSpec(0, 14);
            break;

        case LEVEL_ZONESS:
            Audio_SetAudioSpec(0, 4);
            break;

        case LEVEL_SECTOR_Y:
            Audio_SetAudioSpec(0, 7);
            break;

        case LEVEL_SOLAR:
            Audio_SetAudioSpec(0, 0x209);

        default:
            break;
    }
}

bool Map_801A62FC(PlanetId planet) {
    u32 planetSaveSlot;
    s32 ret = true;

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
    }

    if (CVarGetInteger("gLevelSelector", 0) && gCurrentPlanet == 6) {
        return false;
    }

    if (gSaveFile.save.data.planet[planetSaveSlot].played & 1) {
        ret = false;
    }

    return ret;
}

void Map_801A6368(void) {
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

s32 Map_801A655C(PlanetId start, PlanetId end) {
    s32 i;

    for (i = 0; i < 24; i++) {
        if ((sPaths[i].start == start) && (sPaths[i].end == end)) {
            break;
        }
    }

    return i;
}

void Map_801A659C(void) {
    Audio_KillSfxById(0x1100004C);
    Audio_KillSfxById(0x1100204C);

    if (sCurrentPlanetId != 9) {
        AUDIO_PLAY_SFX(0x49000003, gDefaultSfxSource, 4);
    }

    D_menu_801CEFC8 = 0;
    D_menu_801CD944 = 2;
    D_menu_801CD948 = 0;
}

void Map_801A6628(void) {
    gGameState = GSTATE_PLAY;
    gNextGameStateTimer = 2;
    gPlayState = PLAY_STANDBY;
    gDrawMode = DRAW_NONE;
    gHitCount = 0;

    Play_Setup();

    D_ctx_80177CA0 = 0;
    D_ctx_80177CB0 = 0.0f;
    D_ctx_8017782C = 1;
}

void Map_801A6694(void) {
    PlanetId planetId;
    Vec3f dest;
    Vec3f src;

    src.x = 0.0f;
    src.y = 0.0f;
    src.z = 0.0f;

    for (planetId = 0; planetId < PLANET_MAX; planetId++) {
        Matrix_Push(&gGfxMatrix);

        Matrix_RotateY(gGfxMatrix, M_DTOR * sPlanets[planetId].longitude, 1);
        Matrix_Translate(gGfxMatrix, sPlanets[planetId].orbit.radius, sPlanets[planetId].orbit.incl, 0.0f, 1);

        Matrix_RotateY(gGfxMatrix, M_DTOR * -sPlanets[planetId].longitude, 1);

        Map_801AD048();

        Matrix_SetGfxMtx(&gMasterDisp);

        Matrix_Copy(&D_menu_801CDA60[planetId], gGfxMatrix);

        Matrix_MultVec3f(gGfxMatrix, &src, &dest);

        sPlanets[planetId].pos.x = dest.x;
        sPlanets[planetId].pos.y = dest.y;
        sPlanets[planetId].pos.z = dest.z;

        Matrix_Pop(&gGfxMatrix);

        Matrix_Push(&gGfxMatrix);

        Matrix_LookAt(gGfxMatrix, D_menu_801CD9F4, D_menu_801CD9F8, D_menu_801CD9FC, D_menu_801CDA00, D_menu_801CDA04,
                      D_menu_801CDA08, D_menu_801CDA20, D_menu_801CDA24, D_menu_801CDA28, 1);
        Matrix_Translate(gGfxMatrix, D_menu_801CEA58, D_menu_801CEA5C, D_menu_801CEA60, 1);
        Matrix_Mult(gGfxMatrix, &D_menu_801CDA60[planetId], 1);

        Matrix_SetGfxMtx(&gMasterDisp);

        Matrix_MultVec3f(gGfxMatrix, &src, &D_menu_801CE960[planetId]);

        Matrix_Pop(&gGfxMatrix);
    }
}

void Map_801A68E4(void) {
    s32 i;
    s32 j;
    s32 var_a0;

    for (i = 0; i < 14; i++) {
        for (j = i; j < 15; j++) {
            if (D_menu_801CE960[D_menu_801CD8A0[i]].z > D_menu_801CE960[D_menu_801CD8A0[j]].z) {
                var_a0 = D_menu_801CD8A0[i];
                D_menu_801CD8A0[i] = D_menu_801CD8A0[j];
                D_menu_801CD8A0[j] = var_a0;
            }
        }
    }
}

void Map_801A6A24(void) {
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

void Map_801A6A98(PlanetId planetId) {
    s32 mask;
    s32 temp;

    if ((sPlanets[planetId].alpha == 0) && (planetId != sCurrentPlanetId)) {
        return;
    }

    if ((planetId == sCurrentPlanetId) && (D_menu_801CD944 == 2) && (D_menu_801CD95C != 0)) {
        mask = 0x00000001;
    } else {
        mask = 0xFFFFFFFF;
    }

    temp = Map_801A6DAC(planetId);

    Map_801A6EC0(planetId);
    Map_801A7D3C(planetId);
    Matrix_Push(&gGfxMatrix);

    if (gGameFrameCount & mask) {
        if (planetId == PLANET_TITANIA) {
            Map_801A791C(planetId);
        }

        if ((temp == 1) && (D_menu_801CE960[planetId].z > D_menu_801CEA18[planetId]) && (planetId != PLANET_AREA_6) &&
            (planetId != PLANET_BOLSE)) {

            Map_801A7F1C(planetId);
        }

        Map_801A7230(planetId);

        if (planetId == PLANET_SOLAR) {
            Map_801A74F4(planetId);
        }

        if (sPlanets[planetId].anim == PL_ANIM_SPIN) {
            if (planetId != PLANET_VENOM) {

                if ((planetId != PLANET_AQUAS) && (planetId != PLANET_TITANIA)) {
                    Map_801A7684(planetId);
                }

                Map_801A77B0(planetId);
            }
            if (planetId == PLANET_VENOM) {
                Map_801A7BEC(&D_menu_801CEEBC, 0.1f, 3.1f);
                Map_801A7BEC(&D_menu_801CEEC0, -0.1f, 2.9f);
            }
        }

        if (planetId == PLANET_TITANIA) {
            Map_801A7A84(planetId);
        }

        if ((planetId == PLANET_CORNERIA) && D_menu_801CEB48[0]) {
            Map_801A89BC(PLANET_CORNERIA, 0);
        }

        if ((planetId == PLANET_KATINA) && D_menu_801CEB48[1]) {
            Map_801A89BC(PLANET_KATINA, 1);
        }

        if ((planetId == PLANET_SECTOR_Y) && D_menu_801CEB48[2]) {
            Map_801A89BC(PLANET_SECTOR_Y, 2);
        }

        if ((temp == 1) && (D_menu_801CE960[planetId].z <= D_menu_801CEA18[planetId]) && (planetId != PLANET_AREA_6) &&
            (planetId != PLANET_BOLSE)) {

            Map_801A7F1C(planetId);
        }

        if ((temp == 1) && ((planetId == PLANET_AREA_6) || (planetId == PLANET_BOLSE))) {

            Map_801A7F1C(planetId);
        }

        if (temp == 2) {
            Map_801A809C(planetId);
        }
    }
    Matrix_Pop(&gGfxMatrix);
}

s32 Map_801A6DAC(PlanetId planetId) {
    s32 ret;
    s32 planetSaveSlot;
    s32 var_v0;
    s32 var_a0;

    if (planetId == PLANET_VENOM) {
        if (gExpertMode) {
            var_v0 = gSaveFile.save.data.planet[SAVE_SLOT_VENOM_2].expertMedal & 1;
            var_a0 = gSaveFile.save.data.planet[SAVE_SLOT_VENOM_1].expertClear & 1 |
                     gSaveFile.save.data.planet[SAVE_SLOT_VENOM_2].expertClear & 1;
        } else {
            var_v0 = gSaveFile.save.data.planet[SAVE_SLOT_VENOM_2].normalMedal & 1;
            var_a0 = gSaveFile.save.data.planet[SAVE_SLOT_VENOM_1].normalClear & 1 |
                     gSaveFile.save.data.planet[SAVE_SLOT_VENOM_2].normalClear & 1;
        }
    } else {
        planetSaveSlot = planetId;

        if (planetId == PLANET_SOLAR) {
            planetSaveSlot = SAVE_SLOT_SOLAR;
        }

        if (gExpertMode) {
            var_v0 = gSaveFile.save.data.planet[planetSaveSlot].expertMedal & 1;
            var_a0 = gSaveFile.save.data.planet[planetSaveSlot].expertClear & 1;
        } else {
            var_v0 = gSaveFile.save.data.planet[planetSaveSlot].normalMedal & 1;
            var_a0 = gSaveFile.save.data.planet[planetSaveSlot].normalClear & 1;
        }
    }

    ret = 0;

    if (var_v0) {
        ret = 2;
    } else if (var_a0) {
        ret = 1;
    }

    return ret;
}

void Map_801A6EC0(PlanetId planetId) {
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

    Matrix_Mult(gGfxMatrix, &D_menu_801CDA60[planetId], 1);

    if (sPlanets[planetId].anim == PL_ANIM_ROTATE_Y) {
        if (planetId == PLANET_BOLSE) {
            Matrix_RotateX(gGfxMatrix, M_DTOR * D_menu_801AFFF8, 1);
            Matrix_RotateY(gGfxMatrix, M_DTOR * D_menu_801AFFF4, 1);
        } else {
            Matrix_RotateX(gGfxMatrix, M_DTOR * D_menu_801B0000, 1);
            Matrix_RotateY(gGfxMatrix, M_DTOR * D_menu_801AFFFC, 1);
        }
    }

    Matrix_RotateZ(gGfxMatrix, M_DTOR * (sPlanets[planetId].orbit.tilt), 1);

    Matrix_Scale(gGfxMatrix, sPlanets[planetId].scale, sPlanets[planetId].scale, sPlanets[planetId].scale, 1);

    Matrix_SetGfxMtx(&gMasterDisp);

    if (sPlanets[planetId].anim == PL_ANIM_ROTATE_Y) {
        x2 = D_menu_801CE960[PLANET_SOLAR].x - D_menu_801CE960[planetId].x;
        y2 = D_menu_801CE960[PLANET_SOLAR].y - D_menu_801CE960[planetId].y;
        z2 = D_menu_801CE960[PLANET_SOLAR].z - D_menu_801CE960[planetId].z;

        x1 = Math_Atan2F(y2, sqrtf(SQ(x2) + SQ(z2)));
        y1 = -Math_Atan2F(x2, z2);

        src.x = 0.0f;
        src.y = 0.0f;
        src.z = 100.0f;

        Matrix_RotateY(gCalcMatrix, M_DTOR * (-D_menu_801CDA10 - y1), 0);
        Matrix_RotateX(gCalcMatrix, M_DTOR * (-D_menu_801CDA0C - x1), 1);

        Matrix_MultVec3f(gCalcMatrix, &src, &dst);

        dirX = dst.x;
        dirY = dst.y;
        dirZ = dst.z;
        Lights_SetOneLight(&gMasterDisp, dirX, dirY, dirZ, 80, 80, 60, 10, 10, 8);
    }

    Matrix_Copy(&D_menu_801CDE20[planetId], gGfxMatrix);

    Matrix_Pop(&gGfxMatrix);

    D_menu_801AFFF4 += 0.1f;
    D_menu_801AFFFC -= 0.09f;
}

void Map_801A7230(PlanetId planetId) {
    switch (sPlanets[planetId].anim) {
        case PL_ANIM_STATIC:
            if ((D_menu_801CD944 == 3 || planetId == sCurrentPlanetId || planetId == sNextPlanetId) &&
                D_menu_801CD944 != 1 && D_menu_801CD944 != 7) {
                RCP_SetupDL(&gMasterDisp, 0x35);
            } else {
                RCP_SetupDL(&gMasterDisp, 0x29);
                gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, sPlanets[planetId].alpha);
            }
            break;

        case PL_ANIM_ROTATE_Y:
            if ((D_menu_801CD944 == 3 || planetId == sCurrentPlanetId || planetId == sNextPlanetId) &&
                D_menu_801CD944 != 1 && D_menu_801CD944 != 7) {
                RCP_SetupDL(&gMasterDisp, 0x17);
            } else {
                RCP_SetupDL(&gMasterDisp, 0x2E);
                gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, sPlanets[planetId].alpha);
            }
            break;

        case PL_ANIM_BILLBOARD:
        case PL_ANIM_SPIN:
            RCP_SetupDL(&gMasterDisp, 0x40);

            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, sPlanets[planetId].alpha);
            break;

        case PL_ANIM_ROTATE_Z:
            RCP_SetupDL(&gMasterDisp, 0x43);

            gDPSetPrimColor(gMasterDisp++, 0, 0, 240, 0, 0, sPlanets[planetId].alpha);
            gDPSetEnvColor(gMasterDisp++, 31, 0, 0, 0);

            sPlanets[planetId].orbit.tilt += 0.1f;
            break;
    }

    Matrix_Push(&gGfxMatrix);

    Matrix_Copy(gGfxMatrix, &D_menu_801CDE20[planetId]);
    Matrix_SetGfxMtx(&gMasterDisp);

    gSPDisplayList(gMasterDisp++, D_menu_801B68F8[sPlanets[planetId].id]);

    Matrix_Pop(&gGfxMatrix);
}

void Map_801A74F4(PlanetId planetId) {
    static f32 D_menu_801B6A74 = 0.0f;
    s32 alpha = sPlanets[PLANET_VENOM].alpha;

    if (sPlanets[planetId].alpha > 128) {
        alpha = 128;
    }

    RCP_SetupDL(&gMasterDisp, 0x43);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, alpha);
    gDPSetEnvColor(gMasterDisp++, 31, 0, 0, 0);

    Matrix_Push(&gGfxMatrix);

    Matrix_Copy(gGfxMatrix, &D_menu_801CDE20[planetId]);
    Matrix_RotateZ(gGfxMatrix, M_DTOR * D_menu_801B6A74, 1);
    Matrix_Scale(gGfxMatrix, 0.8f, 0.8f, 0.8f, 1);

    Matrix_SetGfxMtx(&gMasterDisp);

    gSPDisplayList(gMasterDisp++, D_menu_801B68F8[sPlanets[planetId].id]);

    Matrix_Pop(&gGfxMatrix);

    D_menu_801B6A74 -= 0.2f;
}

void Map_801A7684(PlanetId planetId) {
    s32 r;
    s32 g;
    s32 b;

    r = g = b = 255;

    if (planetId == PLANET_MACBETH) {
        r = g = b = 64;
    }

    RCP_SetupDL(&gMasterDisp, 0x40);

    gDPSetPrimColor(gMasterDisp++, 0, 0, r, g, b, sPlanets[planetId].alpha);

    Matrix_Push(&gGfxMatrix);
    Matrix_Copy(gGfxMatrix, &D_menu_801CDE20[planetId]);
    Matrix_SetGfxMtx(&gMasterDisp);

    gSPDisplayList(gMasterDisp++, D_menu_801B4A40);

    Matrix_Pop(&gGfxMatrix);
}

void Map_801A77B0(PlanetId planetId) {
    RCP_SetupDL(&gMasterDisp, 0x40);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, sPlanets[planetId].alpha);

    Matrix_Push(&gGfxMatrix);

    Matrix_Copy(gGfxMatrix, &D_menu_801CDE20[planetId]);

    if ((planetId == 10) || (planetId == 7) || (planetId == 8)) {
        Matrix_RotateY(gGfxMatrix, M_DTOR * 180.0f, 1);
    }

    Matrix_RotateZ(gGfxMatrix, M_DTOR * sPlanets[planetId].orbit.tilt, 1);
    Matrix_Scale(gGfxMatrix, 1.6f, 1.6f, 1.6f, 1);

    Matrix_SetGfxMtx(&gMasterDisp);

    gSPDisplayList(gMasterDisp++, D_MAP_605C230);

    Matrix_Pop(&gGfxMatrix);
}

void Map_801A791C(PlanetId planetId) {
    RCP_SetupDL(&gMasterDisp, 0x43);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 175, 175, sPlanets[planetId].alpha);
    gDPSetEnvColor(gMasterDisp++, 73, 31, 15, 0);

    Matrix_Push(&gGfxMatrix);

    Matrix_Copy(gGfxMatrix, &D_menu_801CDE20[planetId]);

    Matrix_RotateZ(gGfxMatrix, M_DTOR * -sPlanets[planetId].orbit.tilt, 1);
    Matrix_RotateX(gGfxMatrix, M_DTOR * 20.0f, 1);

    Matrix_Scale(gGfxMatrix, 3.0f, 3.0f, 3.0f, 1);

    Matrix_SetGfxMtx(&gMasterDisp);

    gSPDisplayList(gMasterDisp++, D_MAP_604C540);

    Matrix_Pop(&gGfxMatrix);
}

void Map_801A7A84(PlanetId planetId) {
    RCP_SetupDL(&gMasterDisp, 0x43);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 175, 175, sPlanets[planetId].alpha);
    gDPSetEnvColor(gMasterDisp++, 73, 31, 15, 0);

    Matrix_Push(&gGfxMatrix);

    Matrix_Copy(gGfxMatrix, &D_menu_801CDE20[planetId]);
    Matrix_RotateZ(gGfxMatrix, M_DTOR * -sPlanets[planetId].orbit.tilt, 1);
    Matrix_RotateX(gGfxMatrix, M_DTOR * 20.0f, 1);
    Matrix_Scale(gGfxMatrix, 3.0f, 3.0f, 3.0f, 1);

    Matrix_SetGfxMtx(&gMasterDisp);

    gSPDisplayList(gMasterDisp++, D_MAP_604CDE0);

    Matrix_Pop(&gGfxMatrix);
}

void Map_801A7BEC(f32* zAngle, f32 next, f32 scale) {
    s32 alpha = sPlanets[PLANET_VENOM].alpha;

    if (sPlanets[PLANET_VENOM].alpha > 128) {
        alpha = 128;
    }

    RCP_SetupDL(&gMasterDisp, 0x43);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 63, 95, 30, alpha);
    gDPSetEnvColor(gMasterDisp++, 0, 0, 0, 0);

    Matrix_Push(&gGfxMatrix);

    Matrix_Copy(gGfxMatrix, &D_menu_801CDE20[PLANET_VENOM]);
    Matrix_RotateZ(gGfxMatrix, M_DTOR * (*zAngle), 1);
    Matrix_Scale(gGfxMatrix, scale, scale, scale, 1);

    Matrix_SetGfxMtx(&gMasterDisp);

    gSPDisplayList(gMasterDisp++, D_MAP_6047E70);

    Matrix_Pop(&gGfxMatrix);

    *zAngle += next;
}

void Map_801A7D3C(PlanetId planetId) {
    Vec3f src;
    Vec3f dest;
    f32 scale;

    src.x = 0.0f;
    src.y = 0.0f;
    src.z = 0.0f;

    scale = 7.0f + RAND_FLOAT(8.0f);

    Matrix_Push(&gGfxMatrix);

    Matrix_Mult(gGfxMatrix, &D_menu_801CDA60[planetId], 1);
    Matrix_RotateY(gGfxMatrix, M_DTOR * D_menu_801CEAF8[planetId], 1);
    Matrix_Translate(gGfxMatrix, D_menu_801AFFB8[planetId], 0.0f, 0.0f, 1);
    Matrix_RotateY(gGfxMatrix, M_DTOR * -D_menu_801CEAF8[planetId], 1);

    Matrix_SetGfxMtx(&gMasterDisp);

    Matrix_Copy(&D_menu_801CE5A0[planetId], gGfxMatrix);
    Matrix_RotateZ(gGfxMatrix, M_DTOR * D_menu_801CEAB8[planetId], 1);
    Matrix_Scale(gGfxMatrix, scale, scale, scale, 1);
    Matrix_MultVec3f(gGfxMatrix, &src, &dest);

    D_menu_801CEA18[planetId] = dest.z;

    Matrix_SetGfxMtx(&gMasterDisp);

    Matrix_Copy(&D_menu_801CE1E0[planetId], gGfxMatrix);

    Matrix_Pop(&gGfxMatrix);
}

void Map_801A7F1C(PlanetId planetId) {
    s32 alpha;

    if (D_menu_801CD980 != 1) {
        alpha = D_menu_801CD900[planetId];
    } else {
        alpha = D_menu_801CD984;
        D_menu_801CD900[planetId] = 255;
    }

    if (alpha != 0) {
        RCP_SetupDL(&gMasterDisp, 0x43);

        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, alpha);
        gDPSetEnvColor(gMasterDisp++, 80, 80, 0, 0);

        Matrix_Push(&gGfxMatrix);

        Matrix_Copy(gGfxMatrix, &D_menu_801CE1E0[planetId]);
        Matrix_SetGfxMtx(&gMasterDisp);

        gSPDisplayList(gMasterDisp++, D_MAP_604D680);

        Matrix_Pop(&gGfxMatrix);

        D_menu_801CEAB8[planetId] += 45.0f;
        if (D_menu_801CD980 == 0) {
            D_menu_801CEAF8[planetId] += 5.0f;
        }
    }
}

void Map_801A809C(PlanetId planetId) {
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
                RCP_SetupDL(&gMasterDisp, 0x43);

                gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, alpha);
                gDPSetEnvColor(gMasterDisp++, 80, 80, 0, 0);

                Matrix_Push(&gGfxMatrix);

                Matrix_Copy(gGfxMatrix, &D_menu_801CE1E0[planetId]);
                Matrix_Translate(gGfxMatrix, 0.0f, -30.0f, 0.0f, 1);

                Matrix_SetGfxMtx(&gMasterDisp);

                gSPDisplayList(gMasterDisp++, D_MAP_604D680);

                Matrix_Pop(&gGfxMatrix);

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

                RCP_SetupDL(&gMasterDisp, 0x43);

                gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, D_menu_801CD994);
                gDPSetEnvColor(gMasterDisp++, 80, 80, 0, 0);

                for (i = 0; i < 8; i++) {
                    Matrix_Push(&gGfxMatrix);

                    Matrix_Copy(gGfxMatrix, &D_menu_801CE5A0[planetId]);
                    Matrix_Translate(gGfxMatrix, 0.0f, -30.0f, 0.0f, 1);
                    Matrix_RotateZ(gGfxMatrix, M_DTOR * (i * -45.0f), 1);
                    Matrix_Translate(gGfxMatrix, 0.0f, D_menu_801CD99C, 0.0f, 1);
                    Matrix_RotateZ(gGfxMatrix, M_DTOR * (D_menu_801B6A78), 1);
                    Matrix_Scale(gGfxMatrix, scale, scale, scale, 1);

                    Matrix_SetGfxMtx(&gMasterDisp);

                    gSPDisplayList(gMasterDisp++, D_MAP_604D680);

                    Matrix_Pop(&gGfxMatrix);
                }

                D_menu_801B6A78 += 45.0f;
                D_menu_801CD994 -= 16;

                if (D_menu_801CD994 <= 0) {
                    D_menu_801CD994 = 0;
                }

                RCP_SetupDL(&gMasterDisp, 0x40);

                gDPSetTextureFilter(gMasterDisp++, G_TF_POINT);
                gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, D_menu_801CD998);

                Matrix_Push(&gGfxMatrix);

                Matrix_Copy(gGfxMatrix, &D_menu_801CE5A0[planetId]);
                Matrix_Translate(gGfxMatrix, 0.0f, -30.0f, 0.0f, 1);
                Matrix_Scale(gGfxMatrix, 3.0f, 3.0f, 3.0f, 1);

                Matrix_SetGfxMtx(&gMasterDisp);

                gSPDisplayList(gMasterDisp++, D_MAP_601D1F0);

                Matrix_Pop(&gGfxMatrix);

                D_menu_801CEAF8[planetId] = -90.0f;

                D_menu_801CD998 += 8;

                if (D_menu_801CD998 == 8) {
                    AUDIO_PLAY_SFX(0x49008030U, gDefaultSfxSource, 4U);
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
        RCP_SetupDL(&gMasterDisp, 0x40);

        gDPSetTextureFilter(gMasterDisp++, G_TF_POINT);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, alpha);

        Matrix_Push(&gGfxMatrix);

        Matrix_Copy(gGfxMatrix, &D_menu_801CE5A0[planetId]);
        Matrix_Translate(gGfxMatrix, 0.0f, -30.0f, 0.0f, 1);
        Matrix_Scale(gGfxMatrix, 3.0f, 3.0f, 3.0f, 1);

        Matrix_SetGfxMtx(&gMasterDisp);

        gSPDisplayList(gMasterDisp++, D_MAP_601D1F0);

        Matrix_Pop(&gGfxMatrix);

        D_menu_801CEAF8[planetId] = -90.0f;
    }
}

void Map_801A8738(void) {
    if (D_menu_801CEB34 >= 0) {
        RCP_SetupDL(&gMasterDisp, 0x43);

        gDPSetEnvColor(gMasterDisp++, 255, 0, 0, 0);

        switch (D_menu_801CEB34) {
            case 0:
                D_menu_801CEB3C += 0.15f;
                if (D_menu_801CEB3C >= 0.7f) {
                    D_menu_801CEB3C = 0.8f;
                    D_menu_801CEB34 = 2;
                    D_menu_801CEB40 = 2.0f;
                }
                break;

            case 2:
                D_menu_801CEB40--;
                if (D_menu_801CEB40 <= 0.0f) {
                    D_menu_801CEB34 = 3;
                    D_menu_801CEB3C = 0.7f;
                }
                break;

            case 3:
                D_menu_801CEB38 -= 8;
                D_menu_801CEB3C -= 0.001f;

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

        Matrix_Copy(gGfxMatrix, &D_menu_801CDE20[PLANET_CORNERIA]);
        Matrix_RotateZ(gGfxMatrix, M_DTOR * -50.0f, 1);
        Matrix_Translate(gGfxMatrix, 0.0f, 25.0f, 0.0f, 1);
        Matrix_Scale(gGfxMatrix, D_menu_801CEB3C, D_menu_801CEB3C, D_menu_801CEB3C, 1);

        Matrix_SetGfxMtx(&gMasterDisp);

        gSPDisplayList(gMasterDisp++, D_MAP_60479D0);

        Matrix_Pop(&gGfxMatrix);
    }
}

void Map_801A89BC(PlanetId planetId, s32 arg1) {
    s32 i;
    s32 temp2;
    f32 temp;

    if (sPlanets[planetId].alpha == 0) {
        return;
    }

    if (!D_menu_801CEB48[arg1]) {
        return;
    }

    temp2 = 10;
    if (planetId != PLANET_CORNERIA) {
        temp2 = 5;
    }

    RCP_SetupDL(&gMasterDisp, 0x43);

    gDPSetEnvColor(gMasterDisp++, 255, 0, 0, 0);

    for (i = 0; i < temp2; i++) {
        switch (D_menu_801CEB58[arg1][i]) {
            case 0:
                D_menu_801CEC48[arg1][i] += 0.1f;
                if (D_menu_801CEC48[arg1][i] >= D_menu_801CECC0[arg1][i]) {
                    D_menu_801CEC48[arg1][i] = D_menu_801CECC0[arg1][i];
                    D_menu_801CEB58[arg1][i] = 1;
                }
                break;

            case 1:
                D_menu_801CEE28[arg1][i]--;
                if (D_menu_801CEE28[arg1][i] <= 0) {
                    D_menu_801CEB58[arg1][i] = 2;
                }
                break;

            case 2:
                D_menu_801CEBD0[arg1][i] -= 48;
                if (D_menu_801CEBD0[arg1][i] < 0) {
                    D_menu_801CEBD0[arg1][i] = 0;
                    D_menu_801CEB58[arg1][i] = 3;
                }
                break;

            case 3:
                D_menu_801CEB58[arg1][i] = RAND_INT(3.0f);
                D_menu_801CEBD0[arg1][i] = 255;
                D_menu_801CEC48[arg1][i] = 0.0f;
                D_menu_801CECC0[arg1][i] = 0.5f + RAND_FLOAT(0.3f);
                D_menu_801CEE28[arg1][i] = 1 + RAND_INT(4.0f);

                temp = 110.0f;
                if (arg1 == 1) {
                    temp = 50.0f;
                }

                D_menu_801CED38[arg1][i] = temp + RAND_INT(30.0f);
                D_menu_801CEDB0[arg1][i] = -10.0f + RAND_FLOAT(-60.0f);
                break;
        }

        if ((D_menu_801CECC0[arg1][i] == 0.0f) || (D_menu_801CEBD0[arg1][i] == 0)) {
            continue;
        }

        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 200, 200, D_menu_801CEBD0[arg1][i]);

        Matrix_Push(&gGfxMatrix);

        Matrix_Mult(gGfxMatrix, &D_menu_801CDA60[planetId], 1);
        Matrix_RotateZ(gGfxMatrix, M_DTOR * D_menu_801CEDB0[arg1][i], 1);
        Matrix_Translate(gGfxMatrix, 0.0f, D_menu_801CED38[arg1][i], 0.0f, 1);
        Matrix_Scale(gGfxMatrix, D_menu_801CEC48[arg1][i], D_menu_801CEC48[arg1][i], D_menu_801CEC48[arg1][i], 1);

        Matrix_SetGfxMtx(&gMasterDisp);

        gSPDisplayList(gMasterDisp++, D_MAP_60479D0);

        Matrix_Pop(&gGfxMatrix);
    }
}

void Map_801A8F40(void) {
    static f32 D_menu_801B6A7C = 0.0f;
    s32 temp;

    if (D_menu_801CD97C != 0) {
        Lights_SetOneLight(&gMasterDisp, 0, 0, 127, 80, 80, 60, 50, 50, 50);

        RCP_SetupDL(&gMasterDisp, 0x17);

        temp = Math_SmoothStepToF(&D_menu_801CEAA8, D_menu_801CEAB0, 0.1f, 100.0f, 1.0f);

        if (temp == 0.0f) {
            if (D_menu_801CEAB0 == D_menu_801CEAAC) {
                D_menu_801CEAA8 = D_menu_801CEAAC + 50.0f;
            }
        }

        Matrix_Push(&gGfxMatrix);

        Matrix_Mult(gGfxMatrix, &D_menu_801CDA60[sCurrentPlanetId], 1);
        Matrix_Translate(gGfxMatrix, 0.0f, D_menu_801CEAA8, 0.0f, 1);
        Matrix_RotateY(gGfxMatrix, M_DTOR * D_menu_801B6A7C, 1);
        Matrix_Scale(gGfxMatrix, 3.0f, 3.0f, 3.0f, 1);

        Matrix_SetGfxMtx(&gMasterDisp);

        gSPDisplayList(gMasterDisp++, D_MAP_601DCF0);

        Matrix_Pop(&gGfxMatrix);

        D_menu_801B6A7C += 6.0f;
    }
}

void Map_801A914C(void) {
    D_menu_801CEAA8 = 140.0f;

    if (sCurrentPlanetId == PLANET_CORNERIA) {
        D_menu_801CEAA8 = 230.0f;
    }

    if (sCurrentPlanetId == PLANET_AREA_6) {
        D_menu_801CEAA8 = 210.0f;
    }

    if (sCurrentPlanetId == PLANET_SOLAR) {
        D_menu_801CEAA8 = 250.0f;
    }

    if (sCurrentPlanetId == PLANET_SECTOR_X) {
        D_menu_801CEAA8 = 150.0f;
    }

    if (sCurrentPlanetId == PLANET_SECTOR_Y) {
        D_menu_801CEAA8 = 150.0f;
    }

    if (sCurrentPlanetId == PLANET_SECTOR_Z) {
        D_menu_801CEAA8 = 150.0f;
    }

    if (sCurrentPlanetId == PLANET_VENOM) {
        D_menu_801CEAA8 = 300.0f;
    }

    D_menu_801CEAAC = D_menu_801CEAA8;
    D_menu_801CEAB0 = D_menu_801CEAA8;
}

void Map_801A9224(void) {
    s32 i;
    s32 mask;

    if ((sPlanets[PLANET_METEO].alpha != 0) || (sCurrentPlanetId == PLANET_METEO)) {
        if ((sCurrentPlanetId == PLANET_METEO) && (D_menu_801CD944 == 2) && (D_menu_801CD95C != 0)) {
            mask = 0x00000001;
        } else {
            mask = 0xFFFFFFFF;
        }

        if ((D_menu_801CD944 == 3) || ((sCurrentPlanetId == 0) && (D_menu_801CD944 != 7))) {
            RCP_SetupDL(&gMasterDisp, 0x35);
        } else {
            RCP_SetupDL(&gMasterDisp, 0x40);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, sPlanets[PLANET_METEO].alpha);
        }

        if (gGameFrameCount & mask) {
            for (i = 0; i < 42; i++) {
                Matrix_Push(&gGfxMatrix);

                Matrix_RotateY(gGfxMatrix, M_DTOR * D_menu_801AFA38[i].angle, 1);
                Matrix_Translate(gGfxMatrix, D_menu_801AFA38[i].x, D_menu_801AFA38[i].y, 0.0f, 1);
                Matrix_RotateY(gGfxMatrix, M_DTOR * -D_menu_801AFA38[i].angle, 1);

                Map_801AD048();

                Matrix_Scale(gGfxMatrix, D_menu_801AFA38[i].scale, D_menu_801AFA38[i].scale, D_menu_801AFA38[i].scale,
                             1);

                Matrix_SetGfxMtx(&gMasterDisp);

                gSPDisplayList(gMasterDisp++, D_menu_801B68F8[PLANET_METEO]);

                Matrix_Pop(&gGfxMatrix);
            }
        }
    }
}

void Map_801A9448(void) {
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

    if ((sCurrentPlanetId == PLANET_AREA_6) && (D_menu_801CD944 == 2) && (D_menu_801CD95C != 0)) {
        mask = 0x00000001;
    } else {
        mask = 0xFFFFFFFF;
    }

    if ((D_menu_801CD944 == 3) || (sCurrentPlanetId == PLANET_AREA_6)) {
        RCP_SetupDL(&gMasterDisp, 0x17);
    } else {
        RCP_SetupDL(&gMasterDisp, 0x2E);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, sPlanets[PLANET_AREA_6].alpha);
    }

    dest.x = 0.0f;
    dest.y = 0.0f;
    dest.z = 0.0f;

    if (gGameFrameCount & mask) {
        for (i = 0; i < 4; i++) {
            Matrix_Push(&gGfxMatrix);

            Matrix_RotateY(gGfxMatrix, M_DTOR * D_menu_801AFCD8[i].angle, 1);
            Matrix_Translate(gGfxMatrix, D_menu_801AFCD8[i].x, D_menu_801AFCD8[i].y, 0.0f, 1);
            Matrix_RotateY(gGfxMatrix, M_DTOR * -(D_menu_801AFCD8[i].angle), 1);

            Map_801AD048();

            Matrix_RotateY(gGfxMatrix, M_DTOR * D_menu_801B6A80, 1);
            Matrix_Scale(gGfxMatrix, D_menu_801AFCD8[i].scale, D_menu_801AFCD8[i].scale, D_menu_801AFCD8[i].scale, 1);

            Matrix_SetGfxMtx(&gMasterDisp);

            Matrix_MultVec3f(gGfxMatrix, &dest, &src);

            x = D_menu_801CE960[PLANET_SOLAR].x - src.x;
            y = D_menu_801CE960[PLANET_SOLAR].y - src.y;
            z = D_menu_801CE960[PLANET_SOLAR].z - src.z;

            x1 = Math_Atan2F(y, sqrtf(SQ(x) + SQ(z)));
            y1 = -Math_Atan2F(x, z);

            dest.x = 0.0f;
            dest.y = 0.0f;
            dest.z = 100.0f;

            Matrix_RotateY(gCalcMatrix, M_DTOR * (-D_menu_801CDA10 - y1), 0);
            Matrix_RotateX(gCalcMatrix, M_DTOR * (-D_menu_801CDA0C - x1), 1);

            Matrix_MultVec3f(gCalcMatrix, &dest, &src);
            Lights_SetOneLight(&gMasterDisp, src.x, src.y, src.z, 80, 80, 60, 0, 0, 0);

            gSPDisplayList(gMasterDisp++, D_MAP_601E9A0);

            Matrix_Pop(&gGfxMatrix);
        }
    }
}

void Map_801A9814(void) {
    if (D_menu_801B8280 != 0) {
        Matrix_Push(&gGfxMatrix);
        Matrix_LookAt(gGfxMatrix, D_menu_801CD9F4, D_menu_801CD9F8, D_menu_801CD9FC, D_menu_801CDA00, D_menu_801CDA04,
                      D_menu_801CDA08, D_menu_801CDA20, D_menu_801CDA24, D_menu_801CDA28, 1);
        Matrix_Translate(gGfxMatrix, D_menu_801CEA58, D_menu_801CEA5C, D_menu_801CEA60, 1);
        Matrix_SetGfxMtx(&gMasterDisp);
        func_fade_80084688(2, D_menu_801B8284);
        Matrix_Pop(&gGfxMatrix);
    }
}

void Map_801A9910(void) {
    static s32 D_menu_801B6A84[] = { 1, 13, 12, 11, 6, 2, 4, 10, 8, 0, 9, 5, 3, 7, 7 };
    s32 i;
    s32 var_s0 = D_menu_801B6A84[sCurrentPlanetId];

    RCP_SetupDL(&gMasterDisp, 0x53);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, (s32) D_menu_801CEA6C);

    TextureRect_8bIA(&gMasterDisp, D_menu_801AF834[var_s0].texture,
        D_menu_801AF834[var_s0].width, D_menu_801AF834[var_s0].height, D_menu_801AF834[var_s0].xPos, 20.0f, 1.0f, 1.0f);

    Math_SmoothStepToF(&D_menu_801CEA6C, 255.0f, D_menu_801CEA70, 10.0f, 1.0f);

    D_menu_801CEA70 *= 1.08;
}

void Map_801A9A8C(void) {
    s32 i;
    s32 sp58;
    u8* sp54;
    static f32 D_menu_801B6AC0[2] = { 91.0f, 207.0f };
    static f32 D_menu_801B6AC8[2] = { 61.0f, 61.0f };

    switch (gCurrentLevel) {
        case LEVEL_CORNERIA:
            sp54 = D_500A050;
            sp58 = 0;
            break;

        case LEVEL_METEO:
            sp54 = D_500A140;
            sp58 = 1;
            break;

        case LEVEL_SECTOR_Y:
            sp54 = D_500A140;
            sp58 = 2;
            break;

        case LEVEL_FORTUNA:
            sp54 = D_500A230;
            sp58 = 3;
            break;

        case LEVEL_KATINA:
            sp54 = D_500A230;
            sp58 = 4;
            break;

        case LEVEL_AQUAS:
            sp54 = D_500A230;
            sp58 = 5;
            break;

        case LEVEL_SECTOR_X:
            sp54 = D_500A320;
            sp58 = 6;
            break;

        case LEVEL_SOLAR:
            sp54 = D_500A320;
            sp58 = 7;
            break;

        case LEVEL_ZONESS:
            sp54 = D_500A320;
            sp58 = 8;
            break;

        case LEVEL_TITANIA:
            sp54 = D_500A410;
            sp58 = 9;
            break;

        case LEVEL_MACBETH:
            sp54 = D_500A410;
            sp58 = 10;
            break;

        case LEVEL_SECTOR_Z:
            sp54 = D_500A410;
            sp58 = 11;
            break;

        case LEVEL_BOLSE:
            sp54 = D_500A500;
            sp58 = 12;
            break;

        case LEVEL_AREA_6:
            sp54 = D_500A500;
            sp58 = 13;
            break;
    }

    RCP_SetupDL(&gMasterDisp, 0x53);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    if (CVarGetInteger("gLevelSelector", 0) && gCurrentPlanet == 6) {
        return;
    }

    TextureRect_8bIA(&gMasterDisp, D_5000500, 112, 19, D_menu_801B6AC0[0], D_menu_801B6AC8[0], 1.0f, 1.0f);
    TextureRect_8bIA(&gMasterDisp, sp54, 16, 15, D_menu_801B6AC0[1], D_menu_801B6AC8[1], 1.0f, 1.0f);

    for (i = 0; i < D_menu_801AF834[sp58].height; i++) {

    }

    TextureRect_8bIA(&gMasterDisp, D_menu_801AF834[sp58].texture, D_menu_801AF834[sp58].width, D_menu_801AF834[sp58].height,
        D_menu_801AF834[sp58].xPos, 94.0f, 1.0f, 1.0f);

    TextureRect_8bIA(&gMasterDisp, D_menu_801AF914[sp58].texture, D_menu_801AF914[sp58].width, D_menu_801AF914[sp58].height,
        D_menu_801AF914[sp58].xPos, 140.0f, 1.0f, 1.0f);
}

void Map_801A9DE8(void) {
    s32 mask;

    if ((D_menu_801CD978 == 0) &&
        !((D_menu_801CD944 == 3) || (D_menu_801CD944 == 6) || ((D_menu_801CD944 == 7) && (D_menu_801CD948 == 2)))) {
        return;
    }

    mask = 0xFFFFFFFF;
    if (D_menu_801CF00C != 0) {
        mask = 0x00000001;
        D_menu_801CF00C--;
    }

    if (gGameFrameCount & mask) {
        Map_801AD7EC(254, 16, gLifeCount[gPlayerNum]);
    }

    if ((D_game_80161A34 == 7) || (D_game_80161A34 == 5)) {
        if (D_menu_801CD83C < gTotalHits) {
            D_menu_801CD83C = gTotalHits;
        }
        Map_801A9EE4();
        Map_801A9FD4(0);
    }
}

void Map_801A9EE4(void) {
    RCP_SetupDL(&gMasterDisp, 0x53);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);

    Graphics_DisplaySmallText(24, 14, 1.0f, 1.0f, "TOTAL HITS");
    Graphics_DisplaySmallNumber(71 - (func_hud_8008BCBC(gTotalHits) * 8), 24, gTotalHits);
    Graphics_DisplaySmallText(143, 14, 1.0f, 1.0f, "TOP");
    Graphics_DisplaySmallNumber(167 - (func_hud_8008BCBC(D_menu_801CD83C) * 8), 24, D_menu_801CD83C);
}

void Map_801A9FD4(s32 arg0) {
    s32 i;
    s32 var_s3;
    f32 var_fs0, var_fs1;
    s32 pad[2];
    f32 temp = 16.0f;

    if (arg0) {
        var_s3 = gCurrentPlanet;
    } else {
        if ((D_game_80161A34 == 7) || (D_game_80161A34 == 8)) {
            var_s3 = gCurrentPlanet;
        }
        if (D_game_80161A34 == 5) {
            var_s3 = D_menu_801CD9AC;
        }
    }

    Map_801AA1CC(var_s3);

    if ((D_game_80161A34 == 7) || (D_game_80161A34 == 8)) {
        var_s3 = 7;
    }

    if (D_game_80161A34 == 5) {
        var_s3++;
    }

    Matrix_Push(&gGfxMatrix);

    Matrix_LookAt(gGfxMatrix, 0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1);

    Matrix_SetGfxMtx(&gMasterDisp);

    for (var_fs0 = 0.0f, var_fs1 = -41.5f, i = 0; i < var_s3; i++, var_fs0 += 24.0f + temp, var_fs1 += 13.8f) {
        if (D_ctx_80177B90[i] != PLANET_NONE) {
            Map_801AA434(i, 28.0f + var_fs0, 182.0f, D_ctx_80177B90[i]);
            Map_801AA778(i, var_fs1, -25.4f, D_ctx_80177B90[i]);
        }
    }

    Matrix_Pop(&gGfxMatrix);
}

void Map_801AA1CC(s32 arg0) {
    s32 i;
    f32 x;
    s32 r;
    s32 g;
    s32 b;
    s32 temp;
    f32 y = 182.0f;
    f32 x2 = 16.0f;
    PlanetId* ptr = &D_ctx_80177B90[0];

    for (x = 0.0f, i = 0; i < 7; i++, x += 24.0f + x2, ptr++) {
        RCP_SetupDL(&gMasterDisp, 0x53);

        if (i < 6) {
            r = g = b = 255;
            if (i < arg0) {
                temp = Map_801A655C(*ptr, *(ptr + 1));
                switch (sPaths[temp].type) {
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
            TextureRect_16bRGBA(&gMasterDisp, D_MAP_60447A0, 8, 8, 28.0f + x + 24.0f, y + 11.0f, 2.0f, 0.2f);
        }
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
        TextureRect_16bRGBA(&gMasterDisp, D_MAP_6047550, 24, 24, 28.0f + x, y, 1.0f, 1.0f);
    }
}

void Map_801AA434(s32 arg0, f32 x, f32 y, s32 idx) {
    s32 i;
    f32 x2;
    s32 pad;
    s32 mask;
    s32 temp;
    static char* D_menu_801B6AD0[] = { "P", "S", "F" };
    static s32 D_menu_801B6ADC[] = { 255, 0, 30 };
    static s32 D_menu_801B6AE8[] = { 30, 179, 30 };
    static s32 D_menu_801B6AF4[] = { 0, 67, 255 };

    RCP_SetupDL(&gMasterDisp, 0x53);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);

    Graphics_DisplaySmallText(x + 12.0f - Graphics_GetSmallTextWidth(sPlanetNames[idx]) * 0.5f, y - 8.0f, 1.0f, 1.0f,
                              sPlanetNames[idx]);

    Graphics_DisplaySmallNumber(x + 15.0f - ((func_hud_8008BCBC(D_ctx_80177B70[arg0]) - 1) * 8), y + 24.0f + 1.0f,
                                D_ctx_80177B70[arg0]);

    if (D_game_80161A34 == 7) {
        temp = gCurrentPlanet;
    }
    if ((D_game_80161A34 == 5) || (D_game_80161A34 == 8)) {
        temp = gCurrentPlanet + 1;
    }

    if (arg0 < temp) {
        mask = 0x00FF0000;
        x2 = 0.0f;
        for (i = 0; i < 3; i++, x2 += 9.0f) {
            if ((D_ctx_80177B50[arg0] & mask)) {
                RCP_SetupDL(&gMasterDisp, 0x53);
                gDPSetPrimColor(gMasterDisp++, 0, 0, D_menu_801B6ADC[i], D_menu_801B6AE8[i], D_menu_801B6AF4[i], 255);
                Graphics_DisplaySmallText((s32) x + x2 - 1.0f, (s32) y + 24.0f + 8.0f + 2.0f, 1.0f, 1.0f,
                                          D_menu_801B6AD0[i]);
            }
            mask >>= 8;
        }
    }
}

void Map_801AA778(s32 arg0, f32 x, f32 y, PlanetId planetId) {
    s32 mask = 0xFFFFFFFF;

    if ((gGameState == GSTATE_MAP) && (planetId == sCurrentPlanetId)) {
        mask = 0x00000010;
    }

    switch (planetId) {
        case PLANET_SOLAR:
            if (gGameFrameCount & mask) {
                RCP_SetupDL(&gMasterDisp, 0x43);

                gDPSetPrimColor(gMasterDisp++, 0, 0, 240, 0, 0, 255);
                gDPSetEnvColor(gMasterDisp++, 31, 0, 0, 0);

                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, x, y, 0.0f, 1);
                Matrix_RotateZ(gGfxMatrix, M_DTOR * (sPlanets[planetId].orbit.tilt), 1);
                Matrix_Scale(gGfxMatrix, 0.11f, 0.11f, 0.11f, 1);
                Matrix_SetGfxMtx(&gMasterDisp);

                gSPDisplayList(gMasterDisp++, D_menu_801B68F8[sPlanets[planetId].id]);

                gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 128);
                gDPSetEnvColor(gMasterDisp++, 31, 0, 0, 0);

                Matrix_Scale(gGfxMatrix, 0.8f, 0.8f, 0.8f, 1);
                Matrix_SetGfxMtx(&gMasterDisp);

                gSPDisplayList(gMasterDisp++, D_menu_801B68F8[sPlanets[planetId].id]);

                Matrix_Pop(&gGfxMatrix);
            }
            break;

        case PLANET_METEO:
            if (gGameFrameCount & mask) {
                RCP_SetupDL(&gMasterDisp, 0x3E);

                gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

                Matrix_Push(&gGfxMatrix);

                Matrix_Translate(gGfxMatrix, x - 0.4f, y + 0.9f, 0.0f, 1);
                Matrix_RotateZ(gGfxMatrix, M_DTOR * sPlanets[planetId].orbit.tilt, 1);
                Matrix_Scale(gGfxMatrix, 0.1f, 0.1f, 0.1f, 1);

                Matrix_SetGfxMtx(&gMasterDisp);

                gSPDisplayList(gMasterDisp++, D_menu_801B68F8[sPlanets[planetId].id]);

                Matrix_Translate(gGfxMatrix, 18.0f, -20.0f, 0.0f, 1);

                Matrix_SetGfxMtx(&gMasterDisp);

                gSPDisplayList(gMasterDisp++, D_menu_801B68F8[sPlanets[planetId].id]);
                Matrix_Pop(&gGfxMatrix);
            }
            break;

        case PLANET_SECTOR_X:
        case PLANET_SECTOR_Y:
        case PLANET_SECTOR_Z:
            if (gGameFrameCount & mask) {
                RCP_SetupDL(&gMasterDisp, 0x3E);

                gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 144);

                Matrix_Push(&gGfxMatrix);

                Matrix_Translate(gGfxMatrix, x, y, 0.0f, 1);
                Matrix_RotateZ(gGfxMatrix, M_DTOR * sPlanets[planetId].orbit.tilt, 1);
                Matrix_Scale(gGfxMatrix, 0.09f, 0.09f, 0.09f, 1);

                Matrix_SetGfxMtx(&gMasterDisp);

                gSPDisplayList(gMasterDisp++, D_menu_801B68F8[sPlanets[planetId].id]);

                Matrix_Pop(&gGfxMatrix);
            }
            break;

        case PLANET_BOLSE:
            if (gGameFrameCount & mask) {
                RCP_SetupDL(&gMasterDisp, 0x17);

                Lights_SetOneLight(&gMasterDisp, 0, 0, 100, 50, 50, 40, 100, 100, 100);

                Matrix_Push(&gGfxMatrix);

                Matrix_Translate(gGfxMatrix, x, y, 0.0f, 1);
                Matrix_RotateX(gGfxMatrix, M_DTOR * 20.0f, 1);
                Matrix_RotateY(gGfxMatrix, M_DTOR * D_menu_801AFFF4, 1);
                Matrix_RotateZ(gGfxMatrix, M_DTOR * sPlanets[planetId].orbit.tilt, 1);
                Matrix_Scale(gGfxMatrix, 0.004f, 0.004f, 0.004f, 1);

                Matrix_SetGfxMtx(&gMasterDisp);

                gSPDisplayList(gMasterDisp++, D_menu_801B68F8[sPlanets[planetId].id]);

                Matrix_Pop(&gGfxMatrix);
            }
            break;

        case PLANET_AREA_6:
            if (gGameFrameCount & mask) {
                RCP_SetupDL(&gMasterDisp, 0x17);

                Lights_SetOneLight(&gMasterDisp, 0, 0, 100, 50, 50, 40, 100, 100, 100);

                Matrix_Push(&gGfxMatrix);

                Matrix_Translate(gGfxMatrix, x, y, 0.0f, 1);
                Matrix_RotateX(gGfxMatrix, M_DTOR * 20.0f, 1);
                Matrix_RotateY(gGfxMatrix, M_DTOR * D_menu_801AFFFC, 1);
                Matrix_RotateZ(gGfxMatrix, M_DTOR * sPlanets[planetId].orbit.tilt, 1);
                Matrix_Scale(gGfxMatrix, 0.003f, 0.003f, 0.003f, 1);

                Matrix_SetGfxMtx(&gMasterDisp);

                gSPDisplayList(gMasterDisp++, D_menu_801B68F8[sPlanets[planetId].id]);

                Matrix_Pop(&gGfxMatrix);
            }
            break;

        default:
            if (gGameFrameCount & mask) {
                RCP_SetupDL(&gMasterDisp, 0x3E);

                gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

                Matrix_Push(&gGfxMatrix);

                Matrix_Translate(gGfxMatrix, x, y, 0.0f, 1);
                Matrix_RotateZ(gGfxMatrix, M_DTOR * sPlanets[planetId].orbit.tilt, 1);
                Matrix_Scale(gGfxMatrix, 0.1f, 0.1f, 0.1f, 1);

                Matrix_SetGfxMtx(&gMasterDisp);

                gSPDisplayList(gMasterDisp++, D_menu_801B68F8[sPlanets[planetId].id]);

                if (sPlanets[planetId].anim == PL_ANIM_SPIN) {
                    if (planetId != PLANET_VENOM && planetId != PLANET_AQUAS) {
                        Matrix_SetGfxMtx(&gMasterDisp);
                        if (planetId == PLANET_MACBETH) {
                            gDPSetPrimColor(gMasterDisp++, 0, 0, 64, 64, 64, 255);
                        } else {
                            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
                        }
                        gSPDisplayList(gMasterDisp++, D_menu_801B4A40);
                    }
                    Matrix_Scale(gGfxMatrix, 1.6f, 1.6f, 1.6f, 1);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_MAP_605C230);
                }
                Matrix_Pop(&gGfxMatrix);
            }
            break;
    }

    if (D_ctx_80177BB0[arg0] != 0) {
        Map_801AB17C(x, y, 0.0f);
    }
}

void Map_801AB17C(f32 x, f32 y, f32 z) {
    static f32 scale = 0.23f;
    static f32 xPos = 4.4f;
    static f32 yPos = 1.0f;

    RCP_SetupDL(&gMasterDisp, 0x35);
    gDPSetTextureFilter(gMasterDisp++, G_TF_POINT);

    Matrix_Push(&gGfxMatrix);

    Matrix_Translate(gGfxMatrix, x - xPos, y + yPos, z, 1);
    Matrix_Scale(gGfxMatrix, scale, scale, scale, 1);
    Matrix_SetGfxMtx(&gMasterDisp);

    gSPDisplayList(gMasterDisp++, D_MAP_601D1F0);

    Matrix_Pop(&gGfxMatrix);
}

void Map_801AB284(void) {
    D_menu_801CD940 = 0;
    D_ctx_80178308 = D_menu_801AF428[sCurrentPlanetId][D_menu_801CD940];
    D_ctx_80177D68 = D_menu_801AF420[D_menu_801CD940];
    D_menu_801CF018 = 100;
    D_radio_80178728 = 78;
    D_radio_8017872C = 166;
}

void Map_801AB300(void) {
    if (D_Timer_801782AC > 0) {
        D_Timer_801782AC--;
    }
    if (D_Timer_801782B4 > 0) {
        D_Timer_801782B4--;
    }

    switch (D_menu_801CF018) {
        case 0:
            break;

        case 100:
            D_menu_801CEA74 = 0;
            D_ctx_801782A4 = 0 + D_ctx_80177D68;
            D_menu_801CF018 = 1;
            D_ctx_80177D50 = 0.0f;
            D_ctx_801782D8 = 0;
            D_menu_801CF124 = 0.0f;
            D_menu_801CEAB4 = 0;
            break;

        case 200:
            D_menu_801CF018 = 210;
            D_Timer_801782AC = 30;
            break;

        case 210:
            if (D_Timer_801782AC) {
                break;
            }

            D_menu_801CD940 = 1;
            D_ctx_80178308 = D_menu_801AF428[sCurrentPlanetId][D_menu_801CD940];

            Audio_PlayVoice(Message_IdFromPtr(D_ctx_80178308));

            D_ctx_80177D68 = D_menu_801AF420[D_menu_801CD940];
            D_Timer_801782AC = Message_GetCharCount(D_ctx_80178308) * 2;
            D_ctx_801782A4 = D_ctx_80177D68;
            D_menu_801CF018 = 4;
            D_menu_801CD9A0 = 1;
            break;

        case 1:
            D_menu_801CEA74 += 8;
            if (D_menu_801CEA74 > 255) {
                D_menu_801CEA74 = 255;
                D_ctx_80177D50 = 1.3f;

                AUDIO_PLAY_SFX(0x4100001EU, gDefaultSfxSource, 4U);
                Audio_PlayVoice(Message_IdFromPtr(D_ctx_80178308));

                D_Timer_801782AC = Message_GetCharCount(D_ctx_80178308) * 2;
                D_menu_801CD9A4 = 0;
                D_menu_801CF018 = 4;
            }
            break;

        case 4:
            if (!D_Timer_801782AC && !Audio_GetCurrentVoice()) {
                D_ctx_801782A4 = D_ctx_80177D68;
                Audio_ClearVoice();
                if (D_menu_801CD940 == 0) {
                    D_ctx_801782D8 = 0;
                    D_Timer_801782AC = 30;
                } else {
                    D_Timer_801782AC = 20;
                }
                D_menu_801CF018 = 41;
                break;
            }

            D_ctx_801782A4 = D_ctx_80177D68;

            if (D_Timer_801782B4 > 0) {
                D_ctx_801782A4 = 1 + D_ctx_80177D68;
            }

            if (D_ctx_801782D8 >= Message_GetCharCount(D_ctx_80178308)) {
                D_menu_801CD9A4 = 1;
            }

            if (D_menu_801CD9A0 == 1) {
                D_menu_801CF124 += 0.7f;
                D_ctx_801782D8 = D_menu_801CF124;
            } else {
                D_ctx_801782D8 += 2;
            }

            if (D_menu_801CEAB4) {
                if (Audio_GetCurrentVoiceStatus() == 1) {
                    D_Timer_801782B4 = 2;
                } else {
                    D_Timer_801782B4 = 0;
                }
            }

            D_menu_801CEAB4 ^= 1;
            break;

        case 41:
            if (D_Timer_801782AC) {
                break;
            }

            if (D_menu_801CD940 == 1) {
                D_menu_801CF018 = 5;
                break;
            } else {
                D_menu_801CD940 = 1;
                D_ctx_80178308 = D_menu_801AF428[sCurrentPlanetId][D_menu_801CD940];
                Audio_PlayVoice(Message_IdFromPtr(D_ctx_80178308));
                D_ctx_80177D68 = D_menu_801AF420[D_menu_801CD940];
                D_ctx_801782A4 = D_ctx_80177D68;
                D_ctx_801782D8 = 0;
                D_menu_801CF124 = 0.0f;
                D_Timer_801782AC = Message_GetCharCount(D_ctx_80178308) * 2;
                D_menu_801CD9A0 = 1;
                D_menu_801CD9A4 = 0;
                D_menu_801CF018 = 4;
            }
            break;

        case 5:
            D_Timer_801782AC = 5;
            D_ctx_801782A4 = D_ctx_80177D68;
            D_menu_801CF018++;
            break;

        case 6:
            if (D_Timer_801782AC == 0) {
                Audio_KillSfxById(0x4100001EU);
                Audio_PlayVoice(0);
                D_ctx_80177D50 = 0.0f;
                D_menu_801CF018++;
                D_menu_801CF018 = 7;
            }
            break;

        case 7:
            break;

        case 8:
            D_ctx_801782A4 = D_ctx_80177D68;
            D_ctx_80177D50 = 1.3f;
            D_menu_801CEA74 = 255;
            break;
    }

    if ((D_menu_801CF018 > 0) && (D_menu_801CF018 != 100)) {
        Map_801AB978(D_ctx_801782A4);
        Map_801AB978(D_menu_801AF420[!D_menu_801CD940]);
        if (CVarGetInteger("gLevelSelector", 0) && gCurrentPlanet == 6) {
            return;
        }
        func_radio_800BB388();
    }
}

void Map_801AB978(s32 arg0) {
    s32 i;
    f32 xPos;
    f32 yPos;
    s32 sp90[3];
    static f32 D_menu_801B6B0C[3] = { 205.0f, 237.0f, 269.0f };
    static u16* D_menu_801B6B18[3] = { D_MAP_6032A60, D_MAP_6044180, D_MAP_6032440 };

    switch (arg0) {
        case 10:
        case 11:
            D_menu_801CD810 = arg0 - 10;
            break;

        case 20:
        case 21:
            if (D_menu_801CEA74 != 0) {
                RCP_SetupDL(&gMasterDisp, 0x4C);
                gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, D_menu_801CEA74);
                xPos = 205.0f;
                yPos = 77.0f;

                TextureRect_16bRGBA(&gMasterDisp, D_MAP_6044820, 92, 51, xPos, yPos, 1.0f, 1.0f);

                if (arg0 == 21) {
                    TextureRect_16bRGBA(&gMasterDisp, D_MAP_6046CD0, 32, 34, xPos + 47.0, yPos, 1.0f, 1.0f);
                }

                for (i = 0; i < 3; i++) {
                    switch (gSavedTeamShields[3 - i]) {
                        case -1:
                        case -2:
                            if (D_menu_801CEA74 > 32) {
                                sp90[i] = 32;
                            } else {
                                sp90[i] = D_menu_801CEA74;
                            }
                            break;

                        case 0:
                            RCP_SetupDL(&gMasterDisp, 0x53);
                            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);
                            if (gGameFrameCount & 0x10) {
                                Graphics_DisplaySmallText(D_menu_801B6B0C[i], 131 + 28, 1.0f, 1.0f, "OK !");
                            }
                            sp90[i] = D_menu_801CEA74;
                            break;

                        default:
                            sp90[i] = D_menu_801CEA74;
                            break;
                    }

                    RCP_SetupDL(&gMasterDisp, 0x4C);
                    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, sp90[i]);
                    TextureRect_16bRGBA(&gMasterDisp, D_menu_801B6B18[i], 28, 28, D_menu_801B6B0C[i], 131.0f, 1.0f,
                                        1.0f);

                    if ((gSavedTeamShields[3 - i] < 0) && (gSavedTeamShields[3 - i] != -2)) {
                        Map_801ABCDC(i, D_menu_801CEA74);
                    }
                }
            }
    }
}

void Map_801ABCDC(s32 arg0, s32 alpha) {
    static s32 D_menu_801B6B24[] = { 81.0f, 125.0f, 170.0f };

    Matrix_Push(&gGfxMatrix);

    Matrix_LookAt(gGfxMatrix, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -400.0f, 0.0f, 1.0f, 0.0f, 1);

    Matrix_SetGfxMtx(&gMasterDisp);

    RCP_SetupDL(&gMasterDisp, 0x29);

    gDPSetTextureFilter(gMasterDisp++, G_TF_POINT);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, alpha);

    Matrix_Push(&gGfxMatrix);

    Matrix_Translate(gGfxMatrix, D_menu_801B6B24[arg0], -35.0f, -400.0f, 1);
    Matrix_RotateZ(gGfxMatrix, M_DTOR * -40.0f, 1);
    Matrix_Scale(gGfxMatrix, 0.3f, 0.3f, 1.0f, 1);

    Matrix_SetGfxMtx(&gMasterDisp);

    gSPDisplayList(gMasterDisp++, D_500B600);

    Matrix_Pop(&gGfxMatrix);
    Matrix_Push(&gGfxMatrix);

    Matrix_Translate(gGfxMatrix, D_menu_801B6B24[arg0], -35.0f, -400.0f, 1);
    Matrix_RotateZ(gGfxMatrix, M_DTOR * 40.0f, 1);
    Matrix_Scale(gGfxMatrix, 0.3f, 0.3f, 1.0f, 1);

    Matrix_SetGfxMtx(&gMasterDisp);

    gSPDisplayList(gMasterDisp++, D_500B600);

    Matrix_Pop(&gGfxMatrix);
    Matrix_Pop(&gGfxMatrix);
}

void Map_801ABF1C(void) {
    Matrix_Push(&gGfxMatrix);
    {
        Matrix_LookAt(gGfxMatrix, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -400.0f, 0.0f, 1.0f, 0.0f, 1);

        Matrix_SetGfxMtx(&gMasterDisp);

        RCP_SetupDL(&gMasterDisp, 0x15);

        Matrix_Push(&gGfxMatrix);
        {
            Matrix_Translate(gGfxMatrix, D_menu_801CEA88, D_menu_801CEA8C, D_menu_801CEA90, 1);
            Matrix_RotateY(gGfxMatrix, M_DTOR * D_menu_801CEA94, 1);

            Map_801AD048();

            Matrix_Scale(gGfxMatrix, D_menu_801CEA78, D_menu_801CEA7C, 1.0f, 1);

            Matrix_SetGfxMtx(&gMasterDisp);

            gSPDisplayList(gMasterDisp++, D_menu_801AFA30[D_menu_801CD810]);

            Matrix_SetGfxMtx(&gMasterDisp);

            gSPDisplayList(gMasterDisp++, D_MAP_605A120);
        }
        Matrix_Pop(&gGfxMatrix);

        RCP_SetupDL(&gMasterDisp, 0x43);

        gDPSetPrimColor(gMasterDisp++, 0, 0, 32, 32, 255, D_menu_801CEA98);
        gDPSetEnvColor(gMasterDisp++, 207, 207, 255, 0);

        Matrix_Push(&gGfxMatrix);
        {
            Matrix_Translate(gGfxMatrix, D_menu_801CEA88, D_menu_801CEA8C - 1.5f, D_menu_801CEA90, 1);
            Matrix_RotateY(gGfxMatrix, M_DTOR * D_menu_801CEA94, 1);

            Map_801AD048();

            Matrix_Scale(gGfxMatrix, D_menu_801CEA80, D_menu_801CEA84, 3.3f, 1);

            Matrix_SetGfxMtx(&gMasterDisp);

            gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
            gSPDisplayList(gMasterDisp++, D_MAP_604C350);
            gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
        }
        Matrix_Pop(&gGfxMatrix);
    }
    Matrix_Pop(&gGfxMatrix);
}

void Map_801AC200(s32 index) {
    // f32 z;
    // f32 x;
    // f32 y;
    Vec3f v;
    f32 r;
    f32 r2;
    Vec3f vec;

    v.x = gTexturedLines[index].unk_10.x - gTexturedLines[index].unk_04.x;
    v.y = gTexturedLines[index].unk_10.y - gTexturedLines[index].unk_04.y;
    v.z = gTexturedLines[index].unk_10.z - gTexturedLines[index].unk_04.z;

    r = VEC3F_MAG(&v);

    if (r == 0.0f) {
        r = 1.0f;
    }

    if (sPaths[index].unk_14 == 2) {
        vec.x = (v.x / r) * (r / (sPaths[index].length - 1));
        vec.y = (v.y / r) * (r / (sPaths[index].length - 1));
        vec.z = (v.z / r) * (r / (sPaths[index].length - 1));

        D_menu_801CEEB0.x = gTexturedLines[index].unk_04.x + (vec.x * D_menu_801CEEA0);
        D_menu_801CEEB0.y = gTexturedLines[index].unk_04.y + (vec.y * D_menu_801CEEA0);
        D_menu_801CEEB0.z = gTexturedLines[index].unk_04.z + (vec.z * D_menu_801CEEA0);

        switch (D_menu_801CEEA4) {
            case 0:
                break;

            case 100:
                D_menu_801CD9BC = 5;
                D_menu_801CEEA4 = 10;
                break;

            case 10:
                if (D_menu_801CD9BC) {
                    break;
                }
                D_menu_801CD9BC = 5;
                D_menu_801CEEA4 = 20;
                break;

            case 20:
                if (D_menu_801CD9BC) {
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
        vec.x = (v.x / r) * gTexturedLines[index].unk_24;
        vec.y = (v.y / r) * gTexturedLines[index].unk_24;
        vec.z = (v.z / r) * gTexturedLines[index].unk_24;

        D_menu_801CEEB0.x = gTexturedLines[index].unk_04.x + vec.x;
        D_menu_801CEEB0.y = gTexturedLines[index].unk_04.y + vec.y;
        D_menu_801CEEB0.z = gTexturedLines[index].unk_04.z + vec.z;

        v.x = D_menu_801CEEB0.x - gTexturedLines[index].unk_04.x;
        v.y = D_menu_801CEEB0.y - gTexturedLines[index].unk_04.y;
        v.z = D_menu_801CEEB0.z - gTexturedLines[index].unk_04.z;
        r2 = VEC3F_MAG(&v);

        if (((r / 9.0f) * 8.0f) < r2) {
            D_menu_801CEEAC -= 16;
            if (D_menu_801CEEAC < 0) {
                D_menu_801CEEAC = 0;
            }
        }
    }

    if (sPaths[index].unk_14 == 5) {
        Map_801AC80C(sPaths[index].type);
    } else {
        Map_801AC530(index);
    }
}

void Map_801AC530(s32 index) {
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
        RCP_SetupDL(&gMasterDisp, 0x17);
    } else {
        RCP_SetupDL(&gMasterDisp, 0x2E);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, D_menu_801CEEA8);
    }

    Matrix_Push(&gGfxMatrix);

    Matrix_Translate(gGfxMatrix, D_menu_801CEEB0.x, D_menu_801CEEB0.y, D_menu_801CEEB0.z, 1);

    Matrix_RotateY(gGfxMatrix, gTexturedLines[index].unk_20, 1);
    Matrix_RotateX(gGfxMatrix, M_DTOR * -90.0f, 1);
    Matrix_RotateX(gGfxMatrix, gTexturedLines[index].unk_1C, 1);

    Matrix_Scale(gGfxMatrix, 0.8f, 0.8f, 0.8f, 1);

    Matrix_SetGfxMtx(&gMasterDisp);

    Matrix_MultVec3f(gGfxMatrix, &src, &dest);

    x = D_menu_801CE960[PLANET_SOLAR].x - dest.x;
    y = D_menu_801CE960[PLANET_SOLAR].y - dest.y;
    z = D_menu_801CE960[PLANET_SOLAR].z - dest.z;

    x1 = Math_Atan2F(y, sqrtf(SQ(x) + SQ(z)));
    y1 = -Math_Atan2F(x, z);

    src.x = 0.0f;
    src.y = 0.0f;
    src.z = 10.0f;

    Matrix_RotateY(gCalcMatrix, M_DTOR * (-D_menu_801CDA10 - y1), 0);
    Matrix_RotateX(gCalcMatrix, M_DTOR * (-D_menu_801CDA0C - x1), 1);
    Matrix_MultVec3f(gCalcMatrix, &src, &dest);

    dirX = dest.x;
    dirY = dest.y;
    dirZ = dest.z;

    Lights_SetOneLight(&gMasterDisp, dirX, dirY, dirZ, 50, 50, 40, 0, 0, 0);

    gSPDisplayList(gMasterDisp++, D_MAP_604A9F0);

    Matrix_Pop(&gGfxMatrix);
}

void Map_801AC80C(PathType pathType) {
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

    RCP_SetupDL(&gMasterDisp, 0x43);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 80, D_menu_801CEEAC);
    gDPSetEnvColor(gMasterDisp++, r, g, b, 0);

    Matrix_Push(&gGfxMatrix);

    Matrix_Translate(gGfxMatrix, D_menu_801CEEB0.x, D_menu_801CEEB0.y, D_menu_801CEEB0.z, 1);

    Map_801AD048();

    Matrix_RotateZ(gGfxMatrix, M_DTOR * D_menu_801B6B30, 1);
    Matrix_Scale(gGfxMatrix, 10.0f, 10.0f, 10.0f, 1);

    Matrix_SetGfxMtx(&gMasterDisp);

    gSPDisplayList(gMasterDisp++, D_MAP_604D680);

    Matrix_Pop(&gGfxMatrix);

    D_menu_801B6B30 -= 45.0f;
}

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

void Map_801AC9A0(s32 index) {
    Vec3f srcPos;
    Vec3f destPos;
    f32 x;
    f32 y;
    f32 z;
    f32 target;
    f32 temp;

    Map_801ACD90(index, &srcPos, &destPos);

    x = srcPos.x - destPos.x;
    y = srcPos.y - destPos.y;
    z = srcPos.z - destPos.z;

    target = sqrtf(SQ(x) + SQ(y) + SQ(z));

    gTexturedLines[index].mode = 4;

    gTexturedLines[index].unk_04.x = srcPos.x;
    gTexturedLines[index].unk_04.y = srcPos.y;
    gTexturedLines[index].unk_04.z = srcPos.z;

    gTexturedLines[index].unk_10.x = destPos.x;
    gTexturedLines[index].unk_10.y = destPos.y;
    gTexturedLines[index].unk_10.z = destPos.z;

    gTexturedLines[index].unk_20 = Math_Atan2F(x, z);
    gTexturedLines[index].unk_1C = -Math_Atan2F(y, sqrtf(SQ(x) + SQ(z)));

    switch (D_ctx_80177BD8[index]) {
        case 1:
            AUDIO_PLAY_SFX(0x1900404DU, gDefaultSfxSource, 4U);
            D_ctx_80177BD8[index] = 11;
            break;

        case 11:
            Math_SmoothStepToF(&gTexturedLines[index].unk_24, target, 0.1f, 100.0f, 4.0f);
            gTexturedLines[index].unk_2F = 255;
            if (gTexturedLines[index].unk_24 == target) {
                Audio_KillSfxById(0x1900404DU);
                D_ctx_80177BD8[index] = 4;
            }
            break;

        case 5:
        case 6:
            Math_SmoothStepToF(&gTexturedLines[index].unk_24, target, 0.1f, 100.0f, 1.0f);
            if (gTexturedLines[index].unk_24 == target) {
                gTexturedLines[index].unk_24 = 0.0f;
                D_ctx_80177BD8[index] = 6;
                D_menu_801CEEAC = 255;
            }
            break;

        case 2:
            temp = 0.04f;
            if (D_menu_801CD944 == 7) {
                temp = 0.25f;
            }
            Math_SmoothStepToF(&gTexturedLines[index].unk_24, target, temp, 100.0f, 4.0f);
            gTexturedLines[index].unk_2F = 255;
            if (gTexturedLines[index].unk_24 == target) {
                D_ctx_80177BD8[index] = 3;
            }
            break;

        case 3:
        case 4:
            gTexturedLines[index].unk_24 = target;
            gTexturedLines[index].unk_2F = sPaths[index].alpha;
            break;
    }

    if ((D_ctx_80177BD8[index] == 1) || (D_ctx_80177BD8[index] == 11) || (D_ctx_80177BD8[index] == 4)) {
        gTexturedLines[index].unk_2C = 32;
        gTexturedLines[index].unk_2D = 32;
        gTexturedLines[index].unk_2E = 32;
        gTexturedLines[index].unk_28 = 4.0f;
    } else {
        switch (sPaths[index].type) {
            case PL_PATH_BLU:
                gTexturedLines[index].unk_2C = 16;
                gTexturedLines[index].unk_2D = 64;
                gTexturedLines[index].unk_2E = 255;
                gTexturedLines[index].unk_28 = 8.0f;
                break;

            case PL_PATH_YLW:
                gTexturedLines[index].unk_2C = 255;
                gTexturedLines[index].unk_2D = 175;
                gTexturedLines[index].unk_2E = 0;
                gTexturedLines[index].unk_28 = 8.0f;
                break;

            case PL_PATH_RED:
                gTexturedLines[index].unk_2C = 255;
                gTexturedLines[index].unk_2D = 0;
                gTexturedLines[index].unk_2E = 0;
                gTexturedLines[index].unk_28 = 8.0f;
                break;

            case PL_WARP_YLW:
            case PL_WARP_RED:
                gTexturedLines[index].unk_2C = 0;
                gTexturedLines[index].unk_2D = 0;
                gTexturedLines[index].unk_2E = 0;
                gTexturedLines[index].unk_2F = 0;
                gTexturedLines[index].unk_28 = 0.1f;
                break;
        }
    }
}

void Map_801ACD90(s32 index, Vec3f* src, Vec3f* dest) {
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

void Map_801AD048(void) {
    f32 sp1C = Math_Atan2F(D_menu_801CD9F8 - D_menu_801CDA04,
                           sqrtf(SQ(D_menu_801CD9F4 - D_menu_801CDA00) + SQ(D_menu_801CD9FC - D_menu_801CDA08)));
    f32 temp = -Math_Atan2F(D_menu_801CD9F4 - D_menu_801CDA00, D_menu_801CD9FC - D_menu_801CDA08);

    Matrix_RotateY(gGfxMatrix, -temp, 1);
    Matrix_RotateX(gGfxMatrix, -sp1C, 1);
}

void Map_801AD11C(void) {
    s32 i;
    s32 var_t0;
    s32 var_a3;
    u8 var_a1 = 0;
    u8 var_a2 = 0;
    u8 var_a0;
    f32 x;
    f32 y;

    var_a3 = 0;
    var_t0 = 0;

    if (gControllerPress[gMainController].button & A_BUTTON) {
        if ((D_game_80161A34 == 7) && (D_menu_801CD93C != 0) && (!D_menu_801CEFD0)) {
            func_8001D6DC(1);
            D_menu_801CEFC4 = 1;
            D_menu_801CEFD4 = 0;
            D_menu_801CEFDC = 0;
            D_menu_801CD944 = 6;
            D_menu_801CD94C = 0;
        } else {
            for (i = 0; i < TEAM_ID_MAX; i++) {
                D_ctx_80177C58[i] = gTeamShields[i];
            }
            Map_801A659C();
        }
        return;
    }

    if (gControllerPress[gMainController].button & START_BUTTON) {
        if (D_menu_801CD944 == 3 && D_game_80161A34 == 7) {
            if (D_menu_801CEFD0) {
                AUDIO_PLAY_SFX(0x4900100AU, gDefaultSfxSource, 4U);
            } else {
                func_8001D6DC(1);
                D_menu_801CEFC4 = 1;
                D_menu_801CEFD4 = 0;
                D_menu_801CEFDC = 0;
                D_menu_801CD944 = 6;
                D_menu_801CD94C = 0;
            }
            return;
        }
    }

    x = gControllerPress[gMainController].stick_x;
    y = gControllerPress[gMainController].stick_y;

    if (y != 0.0f) {
        if (D_menu_801CDA0C - (y * 0.05f) < -80.0f) {
            D_menu_801CDA0C = -80.0f;
            y = 0.0f;
        } else if (D_menu_801CDA0C - (y * 0.05f) > 80.0f) {
            D_menu_801CDA0C = 80.0f;
            y = 0.0f;
        } else {
            D_menu_801CDA0C -= y * 0.05f;
            var_a3 = 1;
            var_a1 = (s32) fabsf(((y * 0.05f) / 0.27f));
        }
    }

    if (x != 0.0f) {
        D_menu_801CDA10 += x * 0.05f;
        var_a2 = (s32) fabsf((x * 0.05f) / 0.27f);
        var_a3 = 1;
    }

    if (D_menu_801CF014 == 1) {
        var_a0 = var_a1;
        if (var_a1 < var_a2) {
            var_a0 = var_a2;
        }
        func_8001D15C(var_a0);
    }

    if (D_menu_801CF014 == 0 && var_a3 == 1) {
        func_8001D10C(gDefaultSfxSource, 0x1100204C);
        D_menu_801CF014 = 1;
    }

    if ((D_menu_801CF014 == 1) && (var_a3 == 0) && (y == 0.0f) && (x == 0.0f)) {
        var_a1 = 0;
        var_a2 = 0;
        Audio_KillSfxById(0x1100204CU);
        D_menu_801CF014 = 0;
    }

    if (gControllerHold[gMainController].button & R_TRIG) {
        if (D_menu_801CDA14 - 20.0f > 2475.0f) {
            D_menu_801CDA14 -= 20.0f;
            var_t0 = 1;
        }
    }

    if (gControllerHold[gMainController].button & Z_TRIG) {
        if (D_menu_801CDA14 + 20.0f < 7695.0f) {
            D_menu_801CDA14 += 20.0f;
            var_t0 = 1;
        }
    }

    if (gControllerHold[gMainController].button & U_CBUTTONS) {
        if (D_menu_801CDA04 - 10.0f >= -1200.0f) {
            D_menu_801CDA04 -= 10.0f;
            var_t0 = 1;
        }
    }

    if (gControllerHold[gMainController].button & D_CBUTTONS) {
        if (D_menu_801CDA04 + 10.0f <= 1200.0f) {
            D_menu_801CDA04 += 10.0f;
            var_t0 = 1;
        }
    }

    if (gControllerHold[gMainController].button & L_CBUTTONS) {
        if (D_menu_801CDA00 + 10.0f <= 1200.0f) {
            D_menu_801CDA00 += 10.0f;
            var_t0 = 1;
        }
    }

    if (gControllerHold[gMainController].button & R_CBUTTONS) {
        if (D_menu_801CDA00 - 10.0f >= -1200.0f) {
            D_menu_801CDA00 -= 10.0f;
            var_t0 = 1;
        }
    }

    if (D_menu_801CF010 == 0 && var_t0 == 1) {
        AUDIO_PLAY_SFX(0x1100004CU, gDefaultSfxSource, 4U);
        D_menu_801CF010 = 1;
    }

    if (D_menu_801CF010 == 1 && var_t0 == 0) {
        Audio_KillSfxById(0x1100004CU);
        D_menu_801CF010 = 0;
    }
}

void func_dummy_() {
}

void Map_801AD718(f32 arg0, f32 arg1, f32 arg2, f32* arg3, f32* arg4, f32* arg5, f32 arg6, f32 arg7, f32 arg8) {
    Vec3f sp2C;
    Vec3f sp20;

    sp20.x = 0.0f;
    sp20.y = 0.0f;
    sp20.z = arg6;

    Matrix_Translate(gCalcMatrix, arg0, arg1, arg2, 0);
    Matrix_RotateY(gCalcMatrix, M_DTOR * arg8, 1);
    Matrix_RotateX(gCalcMatrix, M_DTOR * arg7, 1);
    Matrix_MultVec3f(gCalcMatrix, &sp20, &sp2C);

    *arg3 = sp2C.x;
    *arg4 = sp2C.y;
    *arg5 = sp2C.z;
}

void Map_801AD7EC(s32 xPos, s32 yPos, s32 number) {
    RCP_SetupDL(&gMasterDisp, 0x55);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    TextureRect_4bCI(&gMasterDisp, D_MAP_601DC10, D_MAP_601DC90, 16, 16, xPos, yPos, 1.0f, 1.0f);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);

    TextureRect_4bCI(&gMasterDisp, D_MAP_601DCA0, D_MAP_601DCD8, 16, 7, xPos + 18.0f, yPos + 9.0f, 1.0f, 1.0f);

    RCP_SetupDL(&gMasterDisp, 0x53);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);

    if (number >= 10) {
        Graphics_DisplaySmallNumber(xPos + 33.0f - ((func_hud_8008BCBC(number) - 1) * 8) + 3, yPos + 8.0f, number);
    } else {
        Graphics_DisplaySmallNumber(xPos + 33.0f, yPos + 8.0f, number);
    }
}

#include "../../mods/levelselect.c"
