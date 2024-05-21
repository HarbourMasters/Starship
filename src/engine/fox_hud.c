#include "sf64math.h"
#include "prevent_bss_reordering.h"
typedef struct {
    /* 0x00 */ u8* unk_00;
    /* 0x04 */ s32 width;
    /* 0x08 */ s32 height;
    /* 0x0C */ u8* unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
} UnkStruct_D_800D1AEC;

Vec3f D_801616A0;
Vec3f D_801616B0;
f32 D_801616BC;
f32 D_801616C0;
f32 D_801616C4;
f32 D_801616C8;
s32 D_801616D0[13];
s32 D_hud_80161704;
s32 D_hud_80161708;
s32 D_hud_8016170C;
s32 D_hud_80161710;
s32 gTotalHits;
s32 D_80161718;
s32 D_8016171C;
f32 D_hud_80161720[3];
s32 gDisplayedHitCount;
s32 D_hud_80161730;
s32 gShowBossHealth;
s32 D_80161738[4];
s32 D_80161748[4];
s32 D_80161758;
s32 D_80161760[4];
f32 D_80161770;
f32 D_80161774;
f32 D_80161778;
f32 D_8016177C;
f32 D_80161780;
f32 D_80161784;
s32 D_80161788;
s32 D_8016178C;
s32 D_80161790;
s32 D_80161794;
s32 D_80161798;
f32 D_8016179C;
f32 D_801617A0;
f32 D_801617A4;
f32 D_801617A8;
f32 D_801617AC;
s32 D_801617B0;
s32 gMedalStatus;
s32 gMedalFlashTimer;
s32 D_801617C0[10];
s32 D_801617E8[10];
s32 D_80161810[10];
s32 D_80161838[10];
s32 D_80161860[20];
f32 D_801618B0[20];
s32 D_80161900[20];

#include "global.h"

#include "assets/ast_bg_space.h"
#include "assets/ast_bg_planet.h"
#include "assets/ast_arwing.h"
#include "assets/ast_landmaster.h"
#include "assets/ast_blue_marine.h"
#include "assets/ast_versus.h"
#include "assets/ast_text.h"
#include "assets/ast_corneria.h"
#include "assets/ast_training.h"
#include "assets/ast_area_6.h"
#include "assets/ast_aquas.h"
#include "assets/ast_venom_1.h"
#include "assets/ast_venom_2.h"
#include "assets/ast_katina.h"
#include "assets/ast_macbeth.h"
#include "assets/ast_meteo.h"
#include "assets/ast_zoness.h"
#include "assets/ast_solar.h"
#include "assets/ast_titania.h"
#include "assets/ast_bolse.h"
#include "assets/ast_fortuna.h"
#include "assets/ast_sector_x.h"
#include "assets/ast_sector_y.h"
#include "assets/ast_sector_z.h"
#include "assets/ast_andross.h"
#include "assets/ast_allies.h"
#include "assets/ast_star_wolf.h"

void func_hud_80087788(void);

s16 D_hud_800D1970 = 0;

UNK_TYPE D_800D1974[14] = { 0 }; // unused

f32 D_800D19AC[] = { 255.0f, 255.0f, 255.0f, 255.0f, 255.0f };

f32 D_800D19C0[] = { 255.0f, 255.0f, 255.0f, 255.0f };

s32 D_800D19D0[] = { 0, 0, 0, 0 };

f32 D_800D19E0[] = { 1.0f, 1.0f, 1.0f, 1.0f };

f32 D_800D19F0 = 0.0f;

s32 D_800D19F4 = 0;

s32 D_800D19F8 = 0;

s32 D_800D19FC = 0;

Vtx D_800D1A00[] = {
    { 10, 10, 0, 0, 0, 0, 255, 255, 255, 255 },
    { -10, 10, 0, 0, 0, 0, 255, 255, 255, 255 },
    { -10, -10, 0, 0, 0, 0, 255, 255, 255, 255 },
    { 10, -10, 0, 0, 0, 0, 255, 255, 255, 255 },
};

Gfx D_800D1A40[] = {
    gsSPVertex(D_800D1A00, 4, 0),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsSPEndDisplayList(),
};

void func_hud_80084930(f32 arg0, f32 arg1, s32 arg2) {
    u8* D_800D1A58[] = {
        D_arwing_3000000,
        D_blue_marine_3000000,
        D_landmaster_3000000,
    };
    u16* D_800D1A64[] = {
        D_arwing_3000080,
        D_blue_marine_3000080,
        D_landmaster_3000080,
    };
    Player* player;
    s32 var_t0;
    s32 var_v0;
    s32 i;

    RCP_SetupDL(&gMasterDisp, SETUPDL_78);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    player = gPlayer;
    var_t0 = 0;

    switch (player->form) {
        case FORM_ARWING:
            var_t0 = 0;
            break;
        case FORM_LANDMASTER:
            var_t0 = 1;
            break;
        case FORM_BLUE_MARINE:
            var_t0 = 2;
            break;
    }

    TextureRect_CI4(&gMasterDisp, D_800D1A58[var_t0], D_800D1A64[var_t0], 16, 16, arg0, arg1 - 2.0f, 1.0f, 1.0f);
    TextureRect_CI4(&gMasterDisp, D_1011ED0, D_1011F08, 16, 7, arg0 + 16.0f, arg1 + 7.0f, 1.0f, 1.0f);

    if (arg2 >= 0) {
        arg0 += 11.0f;
        arg1 -= 1.0f;

        RCP_SetupDL(&gMasterDisp, SETUPDL_76);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

        var_v0 = 10;

        if (arg2 < 0) {
            arg2 = 0;
        }

        if (arg2 > 99) {
            arg2 = 99;
        }

        for (var_v0 = 10, i = 1; arg2 >= var_v0; i++) {
            var_v0 *= 10;
        }

        arg0 += 16.0f + 8 * (2 - i);
        func_hud_800869A0(arg0, arg1, arg2, 1.0f, 1, 99);
    }
}

void func_hud_80084B94(s32 arg0) {
    s32 i;
    Vec3f D_800D1A70[] = {
        { 191.0f, -129.0f, -600.0f },
        { 0.0f, -129.0f, -600.0f },
        { -191.0f, -129.0f, -600.0f },
    };

    RCP_SetupDL(&gMasterDisp, SETUPDL_36);
    if (arg0 == 0) {
        for (i = 1; i < 4; i++) {
            if (((gTeamShields[i] != 0) || (gPlayer[0].state_1C8 != PLAYERSTATE_1C8_LEVEL_COMPLETE)) &&
                (gTeamShields[i] <= 0) && (gTeamShields[i] != -2)) {
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, D_800D1A70[i - 1].x, D_800D1A70[i - 1].y, D_800D1A70[i - 1].z, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, 0.68f, 0.68f, 1.0f, MTXF_APPLY);
                Matrix_RotateZ(gGfxMatrix, M_PI / 4, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, aDownWrenchDL);
                Matrix_RotateZ(gGfxMatrix, 3 * M_PI / 2, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, aDownWrenchDL);
                Matrix_Pop(&gGfxMatrix);
            }
        }
    } else {
        Matrix_Push(&gGfxMatrix);
        Matrix_Translate(gGfxMatrix, -234.0f, -167.0f, -600.0f, MTXF_APPLY);
        Matrix_RotateZ(gGfxMatrix, M_PI / 4, MTXF_APPLY);
        Matrix_Scale(gGfxMatrix, 0.68f, 0.68f, 1.0f, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, aDownWrenchDL);
        Matrix_RotateZ(gGfxMatrix, 3 * M_PI / 2, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, aDownWrenchDL);
        Matrix_Pop(&gGfxMatrix);
    }
}

void func_hud_80084E78(Gfx** gfxP, u8* texture, u16* palette, u32 tWidth, u32 tHeight, f32 xPos, f32 yPos, f32 xScale,
                       f32 yScale, f32 xWidth, f32 yWidth) {
    gDPPipeSync((*gfxP)++);
    gDPLoadTLUT((*gfxP)++, 256, 256, palette);
    gDPLoadTextureBlock((*gfxP)++, texture, G_IM_FMT_CI, G_IM_SIZ_8b, tWidth, tHeight, 0, G_TX_NOMIRROR, G_TX_NOMIRROR,
                        G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSPTextureRectangle((*gfxP)++, (xPos * 4.0f), (yPos * 4.0f), ((xPos + (xWidth * xScale)) * 4.0f),
                        ((yPos + (yWidth * yScale)) * 4.0f), G_TX_RENDERTILE, 0 * 32, 0 * 32,
                        (s32) (1 / xScale * (32 * 32)), (s32) (1 / yScale * (32 * 32)));
}

void func_hud_800853A4(f32 xPos, f32 yPos, f32 xScale, f32 yScale) {
    TextureRect_CI8(&gMasterDisp, D_1013170, D_1013570, 24, 17, xPos, yPos, xScale, yScale);
}

void func_hud_80085404(f32 xPos, f32 yPos, f32 xScale, f32 yScale) {
    TextureRect_CI4(&gMasterDisp, D_1011280, D_10116A0, 48, 44, xPos, yPos, xScale, yScale);
}

void func_hud_80085464(f32 arg0, f32 arg1) {
    TextureRect_CI4(&gMasterDisp, D_1011AC0, D_1011B90, 16, 26, arg0, arg1, 1.0f, 1.0f);
}

void func_hud_800854BC(f32 arg0, f32 arg1) {
    TextureRect_CI4(&gMasterDisp, D_1011BB0, D_1011C80, 16, 26, arg0, arg1, 1.0f, 1.0f);
}

void func_hud_80085514(f32 arg0, f32 arg1) {
    TextureRect_CI4(&gMasterDisp, D_1011CA0, D_1011D70, 16, 26, arg0, arg1, 1.0f, 1.0f);
}

void func_hud_8008556C(f32 arg0, f32 arg1) {
    TextureRect_CI4(&gMasterDisp, D_1011D90, D_1011E60, 16, 26, arg0, arg1, 1.0f, 1.0f);
}

void func_hud_800855C4(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    TextureRect_IA8_MirX(&gMasterDisp, D_1002280, 8, 12, arg0, arg1, arg2, arg3);
}

void func_hud_80085618(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    TextureRect_IA8(&gMasterDisp, D_1002280, 8, 12, arg0, arg1, arg2, arg3);
}

void func_hud_8008566C(f32 x, f32 y, f32 arg2, f32 arg3) {
    TextureRect_IA8(&gMasterDisp, D_10030D0, 8, 12, x, y, arg2, arg3);
}

void func_hud_800856C0(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    func_hud_80084E78(&gMasterDisp, D_1013580, D_1013700, 48, 12, arg0, arg1, arg2, arg3, 48.0f * arg4, 8.0f);
}

void func_hud_80085740(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    if (gVersusMode) {
        TextureRect_IA8(&gMasterDisp, D_versus_3000B20, 32, 5, arg0, arg1, arg2, arg3);
    } else {
        TextureRect_IA8(&gMasterDisp, D_1000E80, 48, 9, arg0, arg1, arg2, arg3);
    }
}

void func_hud_800857DC(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    if (gVersusMode) {
        TextureRect_CI8(&gMasterDisp, D_versus_300D3C0, D_versus_300D408, 24, 3, arg0, arg1, arg2, arg3);
    } else {
        TextureRect_CI8(&gMasterDisp, D_10128C0, D_1012988, 40, 5, arg0, arg1, arg2, arg3);
    }
}

void func_hud_80085890(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    if (gVersusMode) {
        TextureRect_CI8(&gMasterDisp, D_versus_300D350, D_versus_300D398, 24, 3, arg0, arg1, arg2, arg3);
    } else {
        TextureRect_CI8(&gMasterDisp, D_10127D0, D_1012898, 40, 5, arg0, arg1, arg2, arg3);
    }
}

void func_hud_80085944(void) {
    Gfx* D_800D1A94[] = { D_101C170, D_101C000, D_101BE90, D_101BD20, D_101BBB0, D_101BA40,
                          D_101B8D0, D_101B760, D_101B5F0, D_101B480, D_101B310, D_101B1A0 };
    s32 i;
    s32 j;
    f32 D_800D1AC4[] = { 0.0f, -30.0f, -26.0f, -22.0f, -18.0f };
    f32 D_800D1AD8[] = { 0.0f, 28.0f, 28.0f, 28.0f, 28.0f };
    f32 scale;
    f32 x;
    f32 y;
    s32 temp;

    D_801618B0[6] += 0.7f;
    if (D_801618B0[6] >= 12.0f) {
        D_801618B0[6] = 0.0f;
    }

    if (D_80161900[4]) {
        D_80161900[4]--;
    }

    for (i = 0; i < 4; i++) {
        if (D_80161900[i]) {
            D_80161900[i]--;
        }
    }

    if ((D_80161900[4] == 0) && (gGoldRingCount[0] > gGoldRingCount[1])) {
        gGoldRingCount[1] += 1; // can't be ++

        if ((i = gGoldRingCount[1] % 3) == 0) {
            i = 3;
        }

        i--;

        D_80161860[1 + i] = 1;
        D_80161900[0 + i] = 14;
        D_801618B0[2 + i] = 0.0f;

        if (i == 2) {
            D_80161900[4] = 28;
        }

        if (gGoldRingCount[1] == 3) {
            D_80161900[4] += 28;
        }
    }

    for (i = 0; i < 3; i++) {
        switch (D_80161860[i + 1]) {
            case 0:
                RCP_SetupDL(&gMasterDisp, SETUPDL_62);
                Matrix_Push(&gGfxMatrix);

                x = D_800D1AC4[i + 1];
                y = D_800D1AD8[i + 1];
                scale = 0.28f;

                if (D_ctx_80177C70 == 2) {
                    x -= 7.00f;
                    y += 7.00f;
                    scale += 0.06f;
                }

                Matrix_Translate(gGfxMatrix, x, y, -100.0f, MTXF_NEW);
                Matrix_Scale(gGfxMatrix, scale, scale, scale, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gDPSetPrimColor(gMasterDisp++, 0, 0, 180, 180, 0, 50);
                gSPDisplayList(gMasterDisp++, D_1012110);
                Matrix_Pop(&gGfxMatrix);
                break;

            case 1:
            case 2:
                if (D_80161900[i]) {
                    if (D_80161900[i + 0] >= 7) {
                        D_801618B0[i + 2] += 0.15f;
                    } else {
                        D_801618B0[i + 2] -= 0.15f;
                    }

                    RCP_SetupDL(&gMasterDisp, SETUPDL_62);
                    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

                    Matrix_Push(&gGfxMatrix);
                    Matrix_Translate(gGfxMatrix, D_800D1AC4[i + 1], D_800D1AD8[i + 1], -100.0f, MTXF_NEW);
                    Matrix_RotateZ(gGfxMatrix, M_DTOR * D_801618B0[0], MTXF_APPLY);
                    Matrix_Scale(gGfxMatrix, D_801618B0[i + 2], D_801618B0[i + 2], D_801618B0[i + 2], MTXF_APPLY);

                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_101C2E0);
                    Matrix_Pop(&gGfxMatrix);
                }

                if (D_80161900[i] < 7) {
                    if (D_80161860[i + 1] == 2) {
                        RCP_SetupDL(&gMasterDisp, SETUPDL_62);
                    } else {
                        RCP_SetupDL(&gMasterDisp, SETUPDL_36);
                    }

                    Matrix_Push(&gGfxMatrix);

                    x = D_800D1AC4[i + 1];
                    y = D_800D1AD8[i + 1];
                    scale = 0.28f;

                    if (D_ctx_80177C70 == 2) {
                        x -= 7.00f;
                        y += 7.00f;
                        scale += 0.06f;
                    }

                    Matrix_Translate(gGfxMatrix, x, y, -100.0f, MTXF_NEW);
                    Matrix_Scale(gGfxMatrix, scale, scale, scale, MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);

                    if (D_80161860[i + 1] == 2) {
                        gDPSetPrimColor(gMasterDisp++, 0, 0, 180, 180, 0, 50);
                        gSPDisplayList(gMasterDisp++, D_1012110);
                    } else {
                        temp = D_801618B0[6];
                        gSPDisplayList(gMasterDisp++, D_800D1A94[temp]);
                    }
                    Matrix_Pop(&gGfxMatrix);
                }
                break;

            default:
                break;
        }
    }

    if ((gGoldRingCount[1] && ((gGoldRingCount[1] % 3) == 0)) && (D_80161900[4] == 1)) {
        for (j = 0; j < 4; j++) {
            if (D_80161860[j + 1] == 1) {
                D_80161860[j + 1] = 2;
                D_80161900[j + 0] = 14;
                D_801618B0[j + 2] = 0.0f;
                D_80161900[4] = 28;
            } else {
                D_80161860[j + 1] = 0;
                D_80161900[j + 0] = 14;
                D_801618B0[j + 2] = 0.0f;
            }
        }
    }
    D_801618B0[0] += 35.0f;
    D_801618B0[1] += 10.0f;
}

void func_hud_80086110(f32 arg0, f32 arg1, s32 arg2) {
    f32 temp = 0.82f;
    s32 pad;

    RCP_SetupDL(&gMasterDisp, SETUPDL_75);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    if (arg2 != 0) {
        func_hud_800856C0((8.0f * temp) + arg0, arg1 + 2.0f, temp, 1.0f, arg2 / 255.0f);
    }

    if ((arg2 <= 0) && (arg2 != -2) &&
        ((gPlayState == PLAY_PAUSE) || (gShowLevelClearStatusScreen == 1) || (gLevelStartStatusScreenTimer != 0))) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_76);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);
        if ((arg2 == 0) && (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_LEVEL_COMPLETE)) {
            Graphics_DisplaySmallText(arg0 + (8.0f * temp) + 4.0f, arg1 + 2.0f, 1.0f, 1.0f, " OK ");
        } else {
            Graphics_DisplaySmallText(arg0 + (8.0f * temp) + 4.0f, arg1 + 2.0f, 1.0f, 1.0f, "DOWN");
        }
    }

    RCP_SetupDL(&gMasterDisp, SETUPDL_76);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
    func_hud_80085618(arg0, arg1, temp, 1.0f);
    func_hud_800855C4(arg0 + (7.0f * temp) + (temp * 6.0f) * 8.0f, arg1, 1.0f, 1.0f);
    func_hud_8008566C(arg0 + (7.0f * temp), arg1, temp * 6.0f, 1.0f);
}

s32 func_hud_800863C8(void) {
    s32 ret = 0;

    switch (gCurrentLevel) {
        case LEVEL_TRAINING:
            ret++;

        case LEVEL_VENOM_ANDROSS:
            ret++;

        case LEVEL_VENOM_2:
            ret++;

        case LEVEL_VENOM_1:
            ret++;

        case LEVEL_AREA_6:
            ret++;

        case LEVEL_BOLSE:
            ret++;

        case LEVEL_SECTOR_Z:
            ret++;

        case LEVEL_MACBETH:
            ret++;

        case LEVEL_TITANIA:
            ret++;

        case LEVEL_ZONESS:
            ret++;

        case LEVEL_SOLAR:
            ret++;

        case LEVEL_SECTOR_X:
            ret++;

        case LEVEL_AQUAS:
            ret++;

        case LEVEL_KATINA:
            ret++;

        case LEVEL_FORTUNA:
            ret++;

        case LEVEL_SECTOR_Y:
            ret++;

        case LEVEL_METEO:
            ret++;

        case LEVEL_CORNERIA:
            break;
    }
    return ret;
}

UnkStruct_D_800D1AEC D_800D1AEC[] = {
    { aLargeText_1, 16, 15, D_CO_6000000, 128, 28 },      { aLargeText_2, 16, 15, D_ME_6000000, 96, 28 },
    { aLargeText_2, 16, 15, D_SY_6000000, 176, 12 },      { aLargeText_3, 16, 15, D_FO_6000000, 168, 28 },
    { aLargeText_3, 16, 15, D_KA_6000000, 168, 28 },      { aLargeText_3, 16, 15, D_AQ_6000000, 96, 13 },
    { aLargeText_4, 16, 15, D_SX_6000000, 176, 12 },      { aLargeText_4, 16, 15, D_SO_6000000, 112, 13 },
    { aLargeText_4, 16, 15, D_ZO_6000000, 112, 28 },      { aLargeText_5, 16, 15, D_TI_6000000, 96, 28 },
    { aLargeText_5, 16, 15, D_MA_6000000, 160, 28 },      { aLargeText_5, 16, 15, D_SZ_6000000, 176, 12 },
    { aLargeText_6, 16, 15, D_BO_6000000, 168, 19 },      { aLargeText_6, 16, 15, D_A6_6000000, 104, 28 },
    { aLargeText_7, 16, 15, D_VE1_6000D80, 128, 28 },     { aLargeText_7, 16, 15, D_VE2_60012D0, 128, 28 },
    { aLargeText_7, 16, 15, D_ANDROSS_C000A80, 128, 28 }, { aLargeText_0, 16, 15, aTextTraining, 80, 12 },
};

void func_hud_80086444(void) {
    s32 i = 9;
    s32 j;

    u8* D_800D1C9C[] = { D_VE1_6001B80, D_VE2_60020D0 };
    s32 D_800D1CA4[] = { 128, 104 };
    s32 D_800D1CAC[] = { 19, 19 };
    f32 D_800D1CB4[] = { 96.0f, 112.0f };
    f32 D_800D1CBC[] = { 89.0f, 89.0f };
    f32 D_800D1CC4[] = { 2.0f, 5.0f };
    f32 D_800D1CCC[] = { 1.6f, 1.6f };

    switch (gCurrentLevel) {
        case LEVEL_VENOM_2:
            i = 1;
            break;

        case LEVEL_VENOM_1:
            i = 0;
            break;

        default:
            break;
    }

    if (i != 9) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_76);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

        TextureRect_IA8(&gMasterDisp, D_800D1C9C[i], D_800D1CA4[i], 19, D_800D1CB4[i], D_800D1CBC[i] - 28.0f, 1.0f,
                         1.0f);
    }
}

void func_hud_80086664(f32 x, f32 y) {
    s32 i;
    s32 j;
    f32 x0;
    f32 y0;
    f32 x1;
    f32 y1;
    f32 x2;
    f32 y2;

    j = func_hud_800863C8();

    x0 = x;
    y0 = y;

    x1 = x0 + 72.0f;
    y1 = y0;

    x2 = x0 - ((D_800D1AEC[j].unk_10 - 88.0f - D_800D1AEC[j].width) / 2.0f);

    y2 = y0 + 19.0f + 8.0f;

    if (j == 7) {
        x2 += 4.0f;
    }

    switch (gCurrentLevel) {
        case LEVEL_CORNERIA:
        case LEVEL_METEO:
        case LEVEL_AREA_6:
        case LEVEL_FORTUNA:
        case LEVEL_KATINA:
        case LEVEL_ZONESS:
        case LEVEL_MACBETH:
        case LEVEL_TITANIA:
        case LEVEL_TRAINING:
        case LEVEL_VENOM_1:
        case LEVEL_VENOM_2:
        case LEVEL_VENOM_ANDROSS:
            break;

        case LEVEL_AQUAS:
        case LEVEL_BOLSE:
            y2 += 8.0f;
            break;

        case LEVEL_SECTOR_X:
        case LEVEL_SECTOR_Y:
        case LEVEL_SECTOR_Z:
            x2 += 4.0f;
            y2 += 8.0f;
            break;

        case LEVEL_SOLAR:
            x2 += 8.0f;
            y2 += 8.0f;
            break;

        default:
            break;
    }

    RCP_SetupDL(&gMasterDisp, SETUPDL_76);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    if ((j != 14) && (j != 15)) {
        TextureRect_IA8(&gMasterDisp, aTextMissionNo, 112, 19, x0 - 12.0f, y0 + 4.0f, 1.0f, 1.0f);

        TextureRect_IA8(&gMasterDisp, D_800D1AEC[j].unk_00, D_800D1AEC[j].width, D_800D1AEC[j].height, x1 + 28.0f,
                        y1 + 4.0f, 1.0f, 1.0f);
    } else {
        func_hud_80086444();
    }

    TextureRect_IA8(&gMasterDisp, D_800D1AEC[j].unk_0C, D_800D1AEC[j].unk_10, D_800D1AEC[j].unk_14, x2, y2, 1.0f,
                     1.0f);

    if ((gSavedObjectLoadIndex == 0) && (gAllRangeCheckpoint == 0) && (gCurrentLevel != LEVEL_VENOM_ANDROSS) &&
        (gCurrentLevel != LEVEL_TRAINING)) {
        func_hud_80087788();
        func_hud_80084B94(0);
    }

    if (gCurrentLevel != LEVEL_TRAINING) {
        func_hud_80084930(132.0f, 124.0f, gLifeCount[gPlayerNum]);
    }
}

void func_hud_800869A0(f32 arg0, f32 arg1, s32 k, f32 arg3, s32 arg4, s32 arg5) {
    s32 var_s2;
    s32 i;
    s32 j;

    u8* D_800D1CD4[] = {
        aLargeText_0, aLargeText_1, aLargeText_2, aLargeText_3, aLargeText_4,
        aLargeText_5, aLargeText_6, aLargeText_7, aLargeText_8, aLargeText_9,
    };

    if (arg4 != 0) {
        var_s2 = false;
    } else {
        var_s2 = true;
    }

    i = arg5 + 1;
    k %= i;

    for (i /= 10; i != 1; i /= 10) {
        j = k / i;
        if ((j != 0) || (var_s2 == true)) {
            TextureRect_IA8(&gMasterDisp, D_800D1CD4[j], 16, 15, arg0, arg1, arg3, arg3);
            arg0 += 13.0f * arg3;
            k %= i;
            var_s2 = true;
        }
    }
    TextureRect_IA8(&gMasterDisp, D_800D1CD4[k], 16, 15, arg0, arg1, arg3, arg3);
}

void func_hud_80086C08(f32 xPos, f32 yPos, f32 xScale, f32 yScale) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_78);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 60, 60, 128, 96);
    gDPSetAlphaDither(gMasterDisp++, G_AD_DISABLE);
    TextureRect_CI8(&gMasterDisp, D_1013170, D_1013570, 24, 17, xPos, yPos, xScale, yScale);
}

void HUD_DrawLevelStartStatusScreen(void) {
    char pad;
    f32 sp18;
    f32 temp;

    if ((gPlayState != PLAY_PAUSE) && (gLevelStartStatusScreenTimer != 0)) {
        gLevelStartStatusScreenTimer--;
    }

    if (gLevelStartStatusScreenTimer == 1) {
        D_80161718 = 30;
        D_8016171C = 0;
    }

    temp = 108.0f;
    sp18 = 81.0f;

    if (gLevelStartStatusScreenTimer != 0) {
        func_hud_80086C08(temp - 4.5f - 32.0f, sp18 - 24.0f - 4.0f, 7.4f, 3.9f);

        if (gCurrentLevel != LEVEL_TRAINING) {
            func_hud_80086C08(122.0f, 122.0f, 2.9f, 1.2f);
        }

        func_hud_80086664(temp, sp18 - 24.0f);
    }
}

f32 D_800D1CFC = 0.0f;

void HUD_DrawLevelClearScreen(void) {
    s32 i;
    s32 j;
    s32 temp;
    bool boolTemp;
    f32 x;
    f32 y;

    if ((gPlayState != PLAY_PAUSE) && (gLevelClearScreenTimer != 0)) {
        gLevelClearScreenTimer--;
    }

    boolTemp = gMissionStatus;

    if ((gCurrentLevel == LEVEL_TITANIA) || (gCurrentLevel == LEVEL_BOLSE) || (gCurrentLevel == LEVEL_VENOM_1) ||
        (gCurrentLevel == LEVEL_VENOM_2) || (gCurrentLevel == LEVEL_AREA_6) || (gCurrentLevel == LEVEL_AQUAS) ||
        (gCurrentLevel == LEVEL_SOLAR)) {
        boolTemp = true;
    }

    temp = 0;

    if (gCurrentLevel == LEVEL_AQUAS) {
        if (gLevelClearScreenTimer <= 100) {
            temp = 5;
        }
        if (gLevelClearScreenTimer <= 96) {
            temp = 5;
        }
        if (gLevelClearScreenTimer <= 92) {
            temp = 4;
        }
        if (gLevelClearScreenTimer <= 87) {
            temp = 3;
        }
        if (gLevelClearScreenTimer <= 82) {
            temp = 2;
        }
        if (gLevelClearScreenTimer <= 77) {
            temp = 1;
        }
        if (gLevelClearScreenTimer == 0) {
            temp = 0;
        }

        if ((gLevelClearScreenTimer == 92) || (gLevelClearScreenTimer == 87) || (gLevelClearScreenTimer == 82) ||
            (gLevelClearScreenTimer == 77)) {
            AUDIO_PLAY_SFX(NA_SE_MISSION_ACCOMPLISHED, gDefaultSfxSource, 4);
        }
    } else {
        if (gLevelClearScreenTimer <= 100) {
            temp = 5;
        }
        if (gLevelClearScreenTimer <= 90) {
            temp = 5;
        }
        if (gLevelClearScreenTimer <= 80) {
            temp = 4;
        }
        if (gLevelClearScreenTimer <= 72) {
            temp = 3;
        }
        if (gLevelClearScreenTimer <= 64) {
            temp = 2;
        }
        if (gLevelClearScreenTimer <= 56) {
            temp = 1;
        }
        if (gLevelClearScreenTimer == 0) {
            temp = 0;
        }

        if ((gLevelClearScreenTimer == 80) || (gLevelClearScreenTimer == 72) || (gLevelClearScreenTimer == 64) ||
            (gLevelClearScreenTimer == 56)) {
            if (!boolTemp) {
                AUDIO_PLAY_SFX(NA_SE_MISSION_COMPLETE, gDefaultSfxSource, 4);
            } else {
                AUDIO_PLAY_SFX(NA_SE_MISSION_ACCOMPLISHED, gDefaultSfxSource, 4);
            }
        }
    }

    switch (temp) {
        case 0:
            D_800D1CFC = 330.0f;
            break;

        case 5:
            if (gCurrentLevel == LEVEL_AQUAS) {
                D_800D1CFC -= 110.0F;
            } else {
                D_800D1CFC -= 66.0F;
            }
            if (D_800D1CFC < 0.0f) {
                D_800D1CFC = 0.0f;
            }
            break;

        default:
            D_800D1CFC = 0.0f;
            break;
    }

    j = func_hud_800863C8();

    if (temp != 0) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_76);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
        x = 98.0f;
        y = 64.0f;
    }

    switch (temp) {
        case 1:
            if (boolTemp) {
                TextureRect_IA8(&gMasterDisp, aTextPLISHED, 136, 23, x + 50.0f, y + 50.0f, 1.0f, 1.0f);
            } else {
                TextureRect_IA8(&gMasterDisp, aTextLETE, 80, 21, x + 66.0f, y + 50.0f, 1.0f, 1.0f);
            }

        case 2:
            if (boolTemp) {
                TextureRect_IA8(&gMasterDisp, aTextACCOM, 120, 23, x - 62.0f, y + 50.0f, 1.0f, 1.0f);
            } else {
                TextureRect_IA8(&gMasterDisp, aTextCOMP, 96, 23, x - 22.0f, y + 50.0f, 1.0f, 1.0f);
            }

        case 3:
            TextureRect_IA8(&gMasterDisp, aTextMISSION, 128, 23, x, y + 25.0f, 1.0f, 1.0f);

        case 4:
            TextureRect_IA8(&gMasterDisp, aTextMissionNo, 112, 19, x, y, 1.0f, 1.0f);
            TextureRect_IA8(&gMasterDisp, D_800D1AEC[j].unk_00, D_800D1AEC[j].width, D_800D1AEC[j].height, x + 112.0f,
                            y, 1.0f, 1.0f);

        case 5:
            func_hud_80086C08(30.0f + D_800D1CFC, 60.0f, 10.97f, 4.78f);
            break;

        default:
            break;
    }
}

void func_hud_80087530(f32 x, f32 y, s32 number) {
    u8* D_800D1D00[] = { D_arwing_3000000, D_blue_marine_3000000, D_landmaster_3000000 };
    u16* D_800D1D0C[] = { D_arwing_3000080, D_blue_marine_3000080, D_landmaster_3000080 };
    Player* player = &gPlayer[0];
    f32 x0;
    f32 x1;
    f32 x2;
    f32 y0;
    f32 y1;
    f32 y2;
    s32 var_v1;
    s32 i;
    s32 form;

    RCP_SetupDL(&gMasterDisp, SETUPDL_78);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    form = FORM_ARWING;

    switch (player->form) {
        case FORM_ARWING:
            form = FORM_ARWING;
            break;

        case FORM_LANDMASTER:
            form = FORM_LANDMASTER;
            break;

        case FORM_BLUE_MARINE:
            form = FORM_BLUE_MARINE;
            break;

        default:
            break;
    }

    x0 = x;
    y0 = y;
    x1 = x0 + 16.0f;
    y1 = y0 + 9.0f;
    x2 = x1 + 11.0f;
    y2 = y1 - 1.0f;

    if (number < 0) {
        number = 0;
    }
    if (number > 99) {
        number = 99;
    }

    var_v1 = 10;
    for (i = 1; var_v1 <= number; i++) {
        var_v1 *= 10;
    }
    x2 += (2 - i) * 4;

    TextureRect_CI4(&gMasterDisp, D_800D1D00[form], D_800D1D0C[form], 16, 16, x0, y0, 1.0f, 1.0f);
    TextureRect_CI4(&gMasterDisp, D_1011ED0, D_1011F08, 16, 7, x1, y1, 1.0f, 1.0f);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);
    Graphics_DisplayHUDNumber(x2, y2, number);
}

void func_hud_80087788(void) {
    u16* D_800D1D18[] = { D_10050E0, D_100BAC0, D_100D900, D_10032A0 };
    u8* D_800D1D28[] = { aTextPeppy, aTextSlippy, aTextFalco };
    s32 shield;
    s32 D_800D1D34[] = { 48, 56, 48 }; // width
    s32 D_800D1D40[] = { 10, 10, 8 };  // height
    s32 i;
    s32 j;
    f32 x[3][3], y[3][3];

    x[1][0] = 138.0f;
    y[1][0] = 156.0f + 4.0f;
    x[1][1] = 136.0f;
    y[1][1] = y[1][0] + 48.0f;
    x[1][2] = 134.0f;
    y[1][2] = 142.0f + 4.0f;

    x[0][0] = x[1][0] - 92.0f;
    y[0][0] = y[1][0];
    x[0][1] = x[1][1] + 4.0f - 92.0f;
    y[0][1] = y[1][1];
    x[0][2] = x[1][2] - 92.0f;
    y[0][2] = y[1][2];

    x[2][0] = x[1][0] + 92.0f;
    y[2][0] = y[1][0];
    x[2][1] = x[1][1] + 4.0f + 92.0f;
    y[2][1] = y[1][1] + 1.0f;
    x[2][2] = x[1][2] + 92.0f;
    y[2][2] = y[1][2];

    for (j = 0; j < 3; j++) {

        func_hud_80086C08(x[j][0] - 6.0f, y[j][1] - 1.0f, 2.4f, 0.7f);

        RCP_SetupDL(&gMasterDisp, SETUPDL_76);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
        TextureRect_IA8(&gMasterDisp, D_800D1D28[j], D_800D1D34[j], D_800D1D40[j], x[j][1], y[j][1], 1.0f, 1.0f);

        RCP_SetupDL(&gMasterDisp, SETUPDL_76);
        shield = gTeamShields[3 - j];

        if (shield <= 0) {
            gDPSetPrimColor(gMasterDisp++, 0, 0, 48, 48, 48, 255);
        } else {
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
        }

        TextureRect_RGBA16(&gMasterDisp, D_800D1D18[j + 1], 44, 44, x[j][0], y[j][0], 1.0f, 1.0f);

        func_hud_80086110(x[j][2], y[j][2], shield);
    }
}

void HUD_DrawLevelClearStatusScreen(void) {
    s32 i;
    s32 temp;
    f32 x0;
    f32 x1;
    f32 x2;
    f32 x3;
    f32 x4;
    f32 x5;
    f32 x6;
    f32 y0;
    f32 y1;
    f32 y2;
    f32 y3;
    f32 y4;
    f32 y5;
    f32 y6;

    if (gShowLevelClearStatusScreen == 0) {
        Audio_KillSfxById(NA_SE_TEAM_SHIELD_UP);
        D_801617C0[0] = 0;
    }

    if ((gPlayState != PLAY_PAUSE) && (gShowLevelClearStatusScreen == 1) && (D_801617E8[0] == 0)) {
        switch (D_801617C0[0]) {
            case 0:
                D_801617C0[5] = gHitCount;
                D_801617C0[1] = gHitCount;
                D_801617C0[2] = gTotalHits;
                gTotalHits += gHitCount;
                D_801617C0[3] = gLifeCount[gPlayerNum];
                gLifeCount[gPlayerNum] += ((D_801617C0[2] % 100) + gHitCount) / 100;

                if (gLifeCount[gPlayerNum] > 99) {
                    gLifeCount[gPlayerNum] = 99;
                }

                D_801617E8[0] = 10;
                D_801617C0[0] = 1;
                D_801617C0[4] = gHitCount / 2;
                D_801617C0[6] = 0;

                func_hud_800884E4();
                break;

            case 1:
                if (((gTeamShields[TEAM_ID_FALCO] > 0) && (gTeamShields[TEAM_ID_FALCO] < 255)) &&
                    ((gTeamShields[TEAM_ID_SLIPPY] > 0) && (gTeamShields[TEAM_ID_SLIPPY] < 255)) &&
                    ((gTeamShields[TEAM_ID_PEPPY] > 0) && (gTeamShields[TEAM_ID_PEPPY] < 255))) {
                    AUDIO_PLAY_SFX(NA_SE_TEAM_SHIELD_UP, gDefaultSfxSource, 4);
                }
                D_801617C0[0] = 2;

            case 2:
                if ((D_801617C0[5] == 0) && (D_801617C0[4] == 0)) {
                    Audio_KillSfxById(NA_SE_TEAM_SHIELD_UP);
                    D_801617C0[0] = 3;
                    D_801617E8[0] = 30;
                    break;
                }

                if (D_801617C0[5] > 0) {
                    AUDIO_PLAY_SFX(NA_SE_COUNT_UP, gDefaultSfxSource, 4);

                    if (D_801617C0[5] >= 100) {
                        D_801617C0[5] -= 100;
                        D_801617C0[2] += 100;
                    } else {
                        D_801617C0[5]--;
                        D_801617C0[2]++;
                    }
                }

                if (D_801617C0[4] > 0) {
                    for (i = TEAM_ID_FALCO, temp = 0; i <= TEAM_ID_PEPPY; i++) {
                        if (gTeamShields[i] > 0) {
                            if (D_801617C0[4] >= 4) {
                                gTeamShields[i] += 4;
                            } else {
                                gTeamShields[i]++;
                            }
                            if (gTeamShields[i] >= 255) {
                                gTeamShields[i] = 255;
                            } else {
                                temp++;
                            }
                        }
                    }

                    if (D_801617C0[4] >= 4) {
                        D_801617C0[4] -= 4;
                    } else {
                        D_801617C0[4]--;
                    }

                    if (D_801617C0[4] <= 0) {
                        D_801617C0[i] = 0;
                    }

                    if ((D_801617C0[i] == 0) || (temp == 0)) {
                        D_801617C0[4] = 0;
                        Audio_KillSfxById(NA_SE_TEAM_SHIELD_UP);
                    }
                }
                break;

            case 3:
            case 4:
                if (D_801617C0[3] < gLifeCount[gPlayerNum]) {
                    D_801617C0[6] = 30;
                }
                D_801617C0[0] = 5;

            case 5:
                if (D_801617C0[3] >= gLifeCount[gPlayerNum]) {
                    gLifeCount[gPlayerNum] = D_801617C0[3];
                    D_801617E8[0] = 10;
                    D_801617C0[0]++;
                } else {
                    if (((gGameFrameCount % 2) == 0)) {
                        AUDIO_PLAY_SFX(NA_SE_ONE_UP, gDefaultSfxSource, 4);
                        D_801617C0[3]++;
                    }
                }
                break;

            case 6:
            case 7:
                D_801617C0[0]++;
                D_801617C0[1] = gHitCount;
                break;

            default:
                break;
        }
    }

    if (D_801617C0[6] > 0) {
        D_801617C0[6]--;
    }

    if (gShowLevelClearStatusScreen == 1) {
        x0 = 128.0f;
        y0 = 30.0f;

        x1 = x0 + 8.0f + 4.0f;
        y1 = y0 + 19.0f + 4.0f;

        x2 = x1 + 13.0f;
        y2 = y1 + 18.0f + 6.0f;

        x3 = x0 - 84.0f;
        y3 = y2 + 19.0f;

        x4 = x3 + 103.0f + 24.0f;
        y4 = y3 - 6.0f;

        x5 = x4 + 60.0f;
        y5 = y4 + 10.0f;

        x6 = x2 - 56.0f + 16.0f;
        y6 = y3 + 18.0f;

        func_hud_80086C08(x0 - 4.0f, y0 - 4.0f, 2.9f, 3.6f);
        func_hud_80086C08(x3 - 4.0f, y3 - 4.0f, 10.0f, 1.0f);
        func_hud_80086C08(x6 - 12.0f, y6 + 8.0f, 5.2f, 1.0f);

        if (D_801617C0[1] < 0) {
            D_801617C0[1] = 0;
        }
        if (D_801617C0[1] > 999) {
            D_801617C0[1] = 999;
        }
        if (D_801617C0[2] < 0) {
            D_801617C0[2] = 0;
        }
        if (D_801617C0[2] > 9999) {
            D_801617C0[2] = 9999;
        }

        temp = 10;
        for (i = 1; temp <= D_801617C0[1]; i++) {
            temp *= 10;
        }
        x1 += (3 - i) * 8;

        temp = 10;
        for (i = 1; temp <= D_801617C0[2]; i++) {
            temp *= 10;
        }
        x4 += (4 - i) * 8;

        RCP_SetupDL(&gMasterDisp, SETUPDL_76);

        gDPSetPrimColor(gMasterDisp++, 0, 0, 90, 160, 200, 255);
        func_hud_800869A0(24.0f, 30.0f + 3.0f, D_801617C0[5], 1.0f, 0, 999);

        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
        TextureRect_IA8(&gMasterDisp, aTextEnemiesDown, 64, 25, x0, y0 + 4.0f, 1.0f, 1.0f);

        func_hud_800869A0(x1, y1 + 12.0f, D_801617C0[1], 1.0f, 1, 999);

        TextureRect_IA8(&gMasterDisp, aTextAccumTotal, 128, 10, x3, y3, 1.0f, 1.0f);

        func_hud_800869A0(x4 + 4.0f, y4 + 3.0f, D_801617C0[2], 1.00f, 1, 9999);

        if ((D_801617C0[6] % 2) == 0) {
            func_hud_80087530(232.0f, 90.0f, D_801617C0[3]);
        }

        RCP_SetupDL(&gMasterDisp, SETUPDL_76);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

        TextureRect_IA8(&gMasterDisp, aTextStatusOfTeam, 120, 12, x6 - 8.0f, y6 + 10.0f, 1.0f, 1.0f);

        func_hud_80087788();
        func_hud_80084B94(0);
        func_hud_8008B5B0(20.0f, 18.0f);
    }
}

void func_hud_800884E4(void) {
    s32 mask;
    s32 i;

    gMissionHitCount[gMissionNumber] = gHitCount;
    mask = 0x00FF0000;

    for (i = 0; i < 3; i++) {
        if (gTeamShields[3 - i] <= 0) {
            gMissionTeamStatus[gMissionNumber] ^= mask;
        } else {
            gMissionTeamStatus[gMissionNumber] |= mask;
        }
        mask >>= 8;
    }
}

void func_hud_80088564(void) {
    PlanetId planetId;

    if ((gCurrentLevel == LEVEL_BOLSE) || (gCurrentLevel == LEVEL_AREA_6)) {
        planetId = PLANET_BOLSE;

        if (gCurrentLevel == LEVEL_AREA_6) {
            planetId = PLANET_AREA_6;
        }

        gSaveFile.save.data.planet[planetId].played = 1;

        if (gExpertMode) {
            gSaveFile.save.data.planet[planetId].expertClear = 1;
        } else {
            gSaveFile.save.data.planet[planetId].normalClear = 1;
        }

        if (gLeveLClearStatus[gCurrentLevel] == 2) {
            gMissionMedal[gMissionNumber] = 1;

            if (gExpertMode) {
                gSaveFile.save.data.planet[planetId].expertMedal = 1;
            } else {
                gSaveFile.save.data.planet[planetId].normalMedal = 1;
            }
        }

        gMissionNumber++;
        gHitCount = 0;

        Save_Write();
    }
}

void HUD_DrawStatusScreens(void) {
    s32 i;

    for (i = 0; i < 5; i++) {
        if (D_801617E8[i] != 0) {
            D_801617E8[i]--;
        }
    }
    HUD_DrawLevelStartStatusScreen();
    HUD_DrawLevelClearScreen();
    HUD_DrawLevelClearStatusScreen();
}

s32 func_hud_800886B8(void) {
    s32 var_v1 = 0;
    f32 var_fv1 = gInputPress->stick_y; // related to the vertical height of the arwing

    if ((var_fv1 != 0.0f) && (D_80161810[4] != 0)) {
        return 0;
    }

    D_80161810[4] = 0;

    if (fabsf(var_fv1) < 30.0f) {
        var_fv1 = 0.0f;
    }

    if (var_fv1 != 0.0f) {
        if (D_80161810[2] == 0) {
            if (var_fv1 > 0) {
                var_v1 = 1;
            } else {
                var_v1 = -1;
            }
            D_80161810[2] = 1;
        }
    } else {
        D_80161810[2] = 0;
    }
    return var_v1;
}

void func_hud_80088784(s32 arg0) {
    Gfx* D_800D1D4C[] = {
        D_BG_PLANET_200B630, D_BG_PLANET_200A5A0, D_BG_PLANET_2009510, D_BG_PLANET_2008480, D_BG_PLANET_20073F0,
        D_BG_PLANET_2006360, D_BG_PLANET_200C6C0, D_BG_PLANET_20052D0, D_BG_PLANET_2004240, D_BG_PLANET_20031B0,
        D_BG_PLANET_2002120, D_BG_PLANET_2001090, D_BG_SPACE_2000000,  D_BG_PLANET_2010A30, D_BG_PLANET_20101A0,
        D_BG_PLANET_200F910, D_BG_PLANET_200F080, D_BG_PLANET_200E7F0,
    };
    Gfx* D_800D1D94[] = {
        D_BG_SPACE_20066C0, D_BG_SPACE_2005E30, D_BG_SPACE_20055A0, D_BG_SPACE_2004D10, D_BG_SPACE_2004480,
        D_BG_SPACE_2003BF0, D_BG_SPACE_2003360, D_BG_SPACE_2002AD0, D_BG_SPACE_2002240, D_BG_SPACE_20019B0,
        D_BG_SPACE_2001120, D_BG_SPACE_2000890, D_BG_SPACE_2000000,
    };
    s32 D_800D1DC8[] = {
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 200, 150, 100, 50,
    };

    if (arg0 != 0) {
        arg0--;
        RCP_SetupDL(&gMasterDisp, SETUPDL_36);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, D_800D1DC8[arg0]);
        Matrix_Push(&gGfxMatrix);
        Matrix_Translate(gGfxMatrix, 3.9f, -3.3f, -100.0f, MTXF_NEW);
        Matrix_Scale(gGfxMatrix, 0.37f, 0.37f, 0.37f, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);

        if (gLevelType == LEVELTYPE_PLANET) {
            gSPDisplayList(gMasterDisp++, D_800D1D4C[arg0]);
        } else {
            gSPDisplayList(gMasterDisp++, D_800D1D94[arg0]);
        }

        Matrix_Pop(&gGfxMatrix);
    }
}

void func_hud_80088970(void) {
    s32 i = 0;
    s32 j = 0;
    Player* player;
    f32 x0;
    f32 y0;
    f32 x1;
    f32 y1;
    f32 x2;
    f32 y2;
    s32 pad[2];
    s32 temp;
    s32 ret;

    D_80161838[0]++;

    if (gPlayState != PLAY_PAUSE) {
        D_80161838[0] = 0;
        D_80161838[1] = 0;
        // clang-format off
	for(i = 0; i < 5; i++) { D_80161810[i] = 0; }
        // clang-format on
        D_80161810[4] = 1;
    }

    if (D_80161810[0] >= 2) {
        gPauseEnabled = 0;
    }

    player = &gPlayer[gPlayerNum];

    if ((gPlayState == PLAY_PAUSE) && (gLevelStartStatusScreenTimer == 0) && !gVersusMode) {
        switch (D_80161810[0]) {
            case 0:
                D_80161838[0] = 0;
                D_80161810[1] = 0;
                D_80161810[0] = 1;
                break;

            case 1:
                ret = func_hud_800886B8();
                if (ret != 0) {
                    D_80161838[0] = 0;
                    if (((ret > 0) && (D_80161810[1] == 1)) || ((ret < 0) && (D_80161810[1] == 0))) {
                        D_80161810[1] ^= 1;
                        AUDIO_PLAY_SFX(NA_SE_CURSOR, gDefaultSfxSource, 4);
                    }
                }

                if (gInputPress->button & B_BUTTON) {
                    D_80161810[0] = 10;
                }

                if (gInputPress->button & A_BUTTON) {
                    if (D_80161810[1] == 0) {
                        D_80161810[0] = 10;
                    } else {
                        D_80161810[0] = 2;
                    }
                }
                break;

            case 2:
                gPlayer[0].state_1C8 = PLAYERSTATE_1C8_STANDBY;
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
                gFillScreenAlphaTarget = 255;
                gFillScreenAlphaStep = 32;

                gFillScreenAlpha += 32;
                if (gFillScreenAlpha < 255) {
                    break;
                }

                Audio_StopPlayerNoise(gPlayer[0].num);
                Audio_ClearVoice();

                gRadioState = 0;

                Play_ClearObjectData();

                gShowBossHealth = false;
                gFillScreenAlpha = 255;

                if (gLifeCount[gPlayerNum] == 0) {
                    D_80161810[0] = 3;
                } else {
                    D_80161810[0] = 3;
                }

                D_80161838[1] = 0;
                D_80161838[0] = 0;

            case 3:
                Graphics_FillRectangle(&gMasterDisp, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, 0, 0, 0, 255);

                gFillScreenAlphaTarget = 0;

                if ((gFillScreenAlpha -= 32) <= 0) {
                    gFillScreenAlpha = 0;
                }

                if (gCurrentLevel == LEVEL_TRAINING) {
                    gGameState = GSTATE_MENU;
                    gNextGameStateTimer = 2;
                    gOptionMenuStatus = OPTION_WAIT;
                    gDrawMode = DRAW_NONE;
                    gLastGameState = GSTATE_PLAY;
                    gStarCount = 0;
                    break;
                } else {
                    if (gFillScreenAlpha == 0) {
                        if (gLevelType == LEVELTYPE_PLANET) {
                            if (D_80161838[1] == 0) {
                                Audio_PlayDeathSequence();
                            }
                            if (D_80161838[1] == 10) {
                                gLifeCount[gPlayerNum]--;
                            }

                            D_80161838[1]++;
                            if (D_80161838[1] > 18) {
                                D_80161810[0] = 4;
                                D_80161838[1] = 0;
                            }
                        } else {
                            if (D_80161838[1] == 0) {
                                Audio_PlayDeathSequence();
                            }
                            if (D_80161838[1] == 6) {
                                gLifeCount[gPlayerNum]--;
                            }
                            D_80161838[1]++;
                            if (D_80161838[1] > 13) {
                                D_80161810[0] = 4;
                                D_80161838[1] = 0;
                            }
                        }
                    }
                }
                break;

            case 4:
                Graphics_FillRectangle(&gMasterDisp, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, 0, 0, 0, 255);
                if (D_80161838[0] < 140) {
                    break;
                }

                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
                gFillScreenAlphaTarget = 255;
                gFillScreenAlphaStep = 32;

                gFillScreenAlpha += 32;
                if (gFillScreenAlpha > 255) {
                    gFillScreenAlpha = 255;
                }
                if (D_80161838[0] < 160) {
                    break;
                }

            case 5:
                Graphics_FillRectangle(&gMasterDisp, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, 0, 0, 0, 255);

                for (i = 0; i < 6; i++) {
                    if (gPrevPlanetTeamShields[i] == -1) {
                        gSavedTeamShields[i] = 0;
                    } else {
                        gSavedTeamShields[i] = gPrevPlanetTeamShields[i];
                    }
                    gStarWolfTeamAlive[i] = gSavedStarWolfTeamAlive[i];
                }

                if ((gCurrentLevel == LEVEL_VENOM_ANDROSS) && (gAllRangeCheckpoint != 0)) {
                    D_ctx_80177CA4 = D_play_80161A5C;
                }

                gSavedPathProgress = 0.0f;
                gAllRangeCheckpoint = 0;
                gSavedZoSearchlightStatus = false;

                gSavedHitCount = gSavedObjectLoadIndex = 0;

                Audio_StopPlayerNoise(0);
                gPlayer[0].state_1C8 = PLAYERSTATE_1C8_NEXT;
                gScreenFlashTimer = 0;
                gPlayer[0].csTimer = 0;
                gFillScreenAlpha = gFillScreenAlphaTarget = 255;
                gFadeoutType = 7;

                gDrawMode = DRAW_PLAY;
                gPlayState = PLAY_UPDATE;
                break;

            case 10:
                Audio_PlayPauseSfx(0);
                gDrawMode = DRAW_PLAY;
                gPlayState = PLAY_UPDATE;
                break;
        }
    }

    if ((D_80161810[3] == 0) && (gPlayState == PLAY_PAUSE) && !gVersusMode && (gLevelStartStatusScreenTimer == 0)) {
        switch (D_80161810[0]) {
            case 0:
            case 1:
                j = func_hud_800863C8();

                x0 = 140.0f;
                y0 = 92.0f + 4.0f;

                x1 = x0 - 28.0f;
                y1 = y0 + 18.0f;

                x2 = 160.0f - (D_800D1AEC[j].unk_10 / 2.0f);
                y2 = y0 - 40.0f;

                func_hud_80086C08(69.0f, y2 - 4.0f, 7.6f, 2.1f);

                switch (gCurrentLevel) {
                    case LEVEL_CORNERIA:
                    case LEVEL_METEO:
                    case LEVEL_AREA_6:
                    case LEVEL_FORTUNA:
                    case LEVEL_KATINA:
                    case LEVEL_VENOM_1:
                    case LEVEL_ZONESS:
                    case LEVEL_MACBETH:
                    case LEVEL_TITANIA:
                    case LEVEL_VENOM_2:
                    case LEVEL_VENOM_ANDROSS:
                        break;

                    case LEVEL_AQUAS:
                    case LEVEL_BOLSE:
                    case LEVEL_TRAINING:
                        y2 += 8.0f;
                        break;

                    case LEVEL_SECTOR_X:
                    case LEVEL_SECTOR_Y:
                    case LEVEL_SECTOR_Z:
                        x2 += 4.0f;
                        y2 += 8.0f;
                        break;

                    case LEVEL_SOLAR:
                        x2 += 8.0f;
                        y2 += 8.0f;
                        break;

                    default:
                        break;
                }

                RCP_SetupDL(&gMasterDisp, SETUPDL_76);
                gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

                TextureRect_IA8(&gMasterDisp, D_800D1AEC[j].unk_0C, D_800D1AEC[j].unk_10, D_800D1AEC[j].unk_14, x2,
                                 y2 + i, 1.0f, 1.0f);

                func_hud_80086C08(x1 - 10.0f, y0 - 4.0f, 4.7f, 2.8f);

                RCP_SetupDL(&gMasterDisp, SETUPDL_76);

                if (D_80161810[1] == 0) {
                    temp = (D_80161838[0] % 20);
                    if (temp >= 10) {
                        temp = 20 - temp;
                    }
                    if ((temp = (temp * 16) - 1) < 0) {
                        temp = 0;
                    }
                    gDPSetPrimColor(gMasterDisp++, 0, 0, 160, temp, temp, 255);
                } else {
                    gDPSetPrimColor(gMasterDisp++, 0, 0, 64, 64, 64, 255);
                }

                TextureRect_IA8(&gMasterDisp, D_1000000, 64, 10, x0 - 12.0f, y0, 1.0f, 1.0f);

                if (D_80161810[1] == 1) {
                    temp = (D_80161838[0] % 20);
                    if (temp >= 10) {
                        temp = 20 - temp;
                    }
                    if ((temp = (temp * 16) - 1) < 0) {
                        temp = 0;
                    }
                    gDPSetPrimColor(gMasterDisp++, 0, 0, 160, temp, temp, 255);
                } else {
                    gDPSetPrimColor(gMasterDisp++, 0, 0, 64, 64, 64, 255);
                }

                if (gCurrentLevel == LEVEL_TRAINING) {
                    TextureRect_IA8(&gMasterDisp, D_TR_6000000, 96, 12, x1, y1, 1.0f, 1.0f);
                } else {
                    if (gLifeCount[gPlayerNum]) {
                        TextureRect_IA8(&gMasterDisp, D_1000280, 96, 10, x1, y1, 1.0f, 1.0f);
                    } else {
                        TextureRect_IA8(&gMasterDisp, D_1000640, 96, 22, x1, y1, 1.0f, 1.0f);
                    }
                }

                if ((gCurrentLevel != LEVEL_VENOM_ANDROSS) && (gCurrentLevel != LEVEL_TRAINING)) {
                    func_hud_80087788();
                    func_hud_80084B94(0);
                }
                break;

            case 3:
            case 4:
                if (gCurrentLevel != LEVEL_TRAINING) {
                    func_hud_80084930(132.0f, 124.0f, gLifeCount[gPlayerNum]);
                    func_hud_80088784(D_80161838[1]);
                }
                break;

            default:
                break;
        }
    }
}

void func_hud_80089670(void) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_62);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
    Matrix_Scale(gGfxMatrix, 18.64f, 21.04f, 1.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_1024AC0);
}

void func_hud_80089710(void) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_62);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
    Matrix_Scale(gGfxMatrix, 11.0f, 11.0f, 1.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_1024AC0);
}

void func_hud_800897B0(void) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_62);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
    Matrix_Scale(gGfxMatrix, 130.0f, 130.0f, 1.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_1024830);
}

void func_hud_80089850(void) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_62);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 0, 0, 0, 255);
    Matrix_Scale(gGfxMatrix, 125.0f, 125.0f, 1.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_102A8A0);
}

void func_hud_800898F0(void) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_1);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 208, 80, 255);
    Matrix_Scale(gGfxMatrix, 30.0f, 30.0f, 1.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_SZ_6004570);
}

f32 D_800D1E10 = 0.0f;

void func_hud_80089994(s32 arg0) {
    s32 D_800D1E14[][4] = {
        { 177, 242, 12, 255 }, { 89, 121, 6, 128 }, { 90, 90, 255, 255 }, { 45, 45, 128, 128 },
        { 0, 179, 67, 255 },   { 0, 90, 34, 128 },  { 255, 30, 0, 255 },  { 128, 15, 0, 128 },
    };
    f32 var_fv1;
    f32 var_fv2;

    if (gCamCount != 1) {
        var_fv1 = 38.0f;
        var_fv2 = 38.0f;
    } else {
        var_fv1 = 54.0f;
        var_fv2 = 54.0f;
    }

    RCP_SetupDL(&gMasterDisp, SETUPDL_62);
    gDPSetPrimColor(gMasterDisp++, 0, 0, D_800D1E14[arg0][0], D_800D1E14[arg0][1], D_800D1E14[arg0][2],
                    D_800D1E14[arg0][3]);
    Matrix_Scale(gGfxMatrix, var_fv1, var_fv2, 1.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_1015510);
}

void func_hud_80089AF4(void) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_62);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 0, 0, 0, 255);
    Matrix_Scale(gGfxMatrix, 54.0f, 54.0f, 1.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_STAR_WOLF_F014180);
}

void func_hud_80089B94(void) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_62);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 92, 92, 255);
    Matrix_Scale(gGfxMatrix, 54.0f, 54.0f, 1.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_D0098B0);
}

void func_hud_80089C38(void) {
    s32 alpha;

    RCP_SetupDL(&gMasterDisp, SETUPDL_12);

    alpha = gGameFrameCount % 21;

    if (alpha > 10) {
        alpha = 20 - alpha;
    }

    alpha *= 255.0f / 10.0f;
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, alpha);
    Matrix_Scale(gGfxMatrix, 15.0f, 15.0f, 1.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_1024230);
}

void func_hud_80089D28(void) {
    s32 gb;

    RCP_SetupDL(&gMasterDisp, SETUPDL_1);

    gb = gGameFrameCount % 21;

    if (gb > 10) {
        gb = 20 - gb;
    }

    gb *= 25.5f;

    if ((gb == 10) || (gb == 0)) {
        // clang-format off
        //! FAKE: Probably a MACRO
        if (1) {AUDIO_PLAY_SFX(NA_SE_MISSILE_ALARM, gDefaultSfxSource, 4);}
        // clang-format on
    }

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, gb, gb, 255);
    Matrix_Translate(gGfxMatrix, 0.0f, -185.92001f, 0, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, 3.55f, 0.13f, 1.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_1024230);
}

void RadarMark_Draw(s32 arg0) {
    s32 var_a1;
    s32 var_a1_2;

    switch (arg0) {
        case 0:
        case 1:
        case 2:
        case 3:
            var_a1_2 = var_a1 = arg0;
            if (gCamCount != 1) {
                if (arg0 == 1) {
                    var_a1 = 3;
                }
                if (arg0 == 3) {
                    var_a1 = 1;
                }

                if (gPlayer[arg0].state_1C8 == PLAYERSTATE_1C8_VS_STANDBY) {
                    break;
                }
            }
            if ((var_a1_2 == gPlayerNum) && (gGameFrameCount & 2)) {
                var_a1 = (var_a1 * 2) + 1;
            } else {
                var_a1 = var_a1 * 2;
            }
            func_hud_80089994(var_a1);
            break;

        case 4:
        case 5:
        case 6:
        case 7:
            func_hud_80089AF4();
            break;

        case 8:
            func_hud_80089B94();
            break;

        case 100:
            func_hud_800898F0();
            break;

        case 101:
            func_hud_80089850();
            break;

        case 102:
            func_hud_800897B0();
            break;

        case 103:
            if (gVersusMode == true) {
                func_hud_80089670();
            } else {
                func_hud_80089C38();
            }
            break;

        case 200:
        case 201:
            func_hud_80089670();
            break;

        case 999:
            break;

        default:
            func_hud_80089710();
            break;
    }
}

void func_hud_8008A07C(f32 x, f32 y) {
    f32 D_800D1E94[] = { 20.0f, 180.0f, 20.0f, 180.0f };
    f32 D_800D1EA4[] = { 72.0f, 72.0f, 192.0f, 192.0f };
    f32 xPos;
    f32 yPos;
    f32 xScale;
    f32 yScale;
    f32 xScale1;
    f32 yScale1;

    if (gCamCount != 1) {
        xPos = D_800D1E94[gPlayerNum];
        yPos = D_800D1EA4[gPlayerNum];
        xScale = 1.21f;
        yScale = 1.69f;
        xScale1 = 0.70f;
        yScale1 = 0.70f;
    } else {
        xPos = x - 32.0f;
        yPos = y - 14.0f;
        xScale = 2.98f;
        yScale = 4.24f;
        xScale1 = 1.70f;
        yScale1 = 1.70f;
    }

    RCP_SetupDL(&gMasterDisp, SETUPDL_78);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 60, 60, 255, 170);
    func_hud_800853A4(xPos + 1.0f, yPos + 1.0f, xScale, yScale);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
    func_hud_80085404(xPos, yPos, xScale1, yScale1);
}

void func_hud_8008A240(void) {
    s32 i;
    Item* item;

    for (i = 0; i < gCamCount; i++) {
        if (gPlayer[i].state_1C8 == PLAYERSTATE_1C8_NEXT) {
            continue;
        }
        gRadarMarks[i].status = 1;
        gRadarMarks[i].type = i;
        gRadarMarks[i].yRot = gPlayer[i].yRot_114 + gPlayer[i].rot.y;
        gRadarMarks[i].pos.z = gPlayer[i].trueZpos;
        gRadarMarks[i].pos.x = gPlayer[i].pos.x;

        if (gPlayerNum == i) {
            continue;
        }

        if (gVersusMode && gVersusStage == VS_STAGE_SECTOR_Z) {
            continue;
        }

        if (gPlayer[i].state_1C8 != PLAYERSTATE_1C8_ACTIVE) {
            continue;
        }

        if (gPlayer[i].pos.y >= 150.0f) {
            continue;
        }

        if ((gGameFrameCount % 64) != 0) {
            gRadarMarks[i].type = 999;
        }
    }

    if (gVersusMode == 1) {
        for (i = 0, item = gItems; i < ARRAY_COUNT(gItems); i++, item++) {
            if (item->obj.status >= OBJ_ACTIVE) {
                gRadarMarks[item->index + 50].status = 1;
                gRadarMarks[item->index + 50].type = 103;
                gRadarMarks[item->index + 50].pos.x = item->obj.pos.x;
                gRadarMarks[item->index + 50].pos.y = item->obj.pos.y;
                gRadarMarks[item->index + 50].pos.z = item->obj.pos.z;
                gRadarMarks[item->index + 50].yRot = 0.0f;
            }
        }
    }
}

s32 func_hud_8008A4DC(void) {
    s32 i;
    f32 scale;
    f32 x1;
    f32 y1;
    f32 z1;
    f32 x;
    f32 y;
    s32 pad;
    f32 temp;
    f32 temp2;
    f32 temp3;

    if (!gVersusMode) {
        if (gLevelMode != LEVELMODE_ALL_RANGE) {
            return 0;
        }

        if (gDrawBackdrop >= 5) {
            return 0;
        }

        if (gLevelStartStatusScreenTimer != 0) {
            D_800D1E10 = 60.0f;
        } else {
            Math_SmoothStepToF(&D_800D1E10, 0.0f, 0.3f, 10.0f, 0.1f);
        }

        if (D_800D1E10 == 60.0f) {
            return 0;
        }

        switch (gCurrentLevel) {
            case LEVEL_SECTOR_Z:
                temp2 = 20000.0f;
                y1 = -360.0f;
                x1 = 542.0f;
                z1 = -1584.0f;
                temp3 = 7.5f;
                scale = 0.02f;
                break;

            case LEVEL_CORNERIA:
                temp2 = 8000.0f;
                y1 = -142.0f;
                x1 = 214.0f;
                z1 = -626.0f;
                temp3 = 3.0f;
                scale = 0.008f;
                break;

            case LEVEL_BOLSE:
                temp2 = 10000.0f;
                y1 = -178.0f;
                x1 = 268.0f;
                z1 = -784.0f;
                temp3 = 3.7f;
                scale = 0.01f;
                break;

            default:
                temp2 = 12500.0f;
                y1 = -220.0f;
                x1 = 330.0f;
                z1 = -970.0f;
                temp3 = 4.7f;
                scale = 0.013f;
                break;
        }

        x = 254.000f + D_800D1E10;
        y = 162.000f;
        x1 += D_800D1E10 * temp3;
    } else {
        if ((gVsMatchStart == 0) || (D_versus_80178750 != 0)) {
            return 0;
        }
        temp2 = 13000.00f;

        scale = 0.03f;
        z1 = -885.00f;
        x1 = -274.00f;
        y1 = -166.00f;
    }

    func_hud_8008A240();
    func_hud_8008A07C(x, y);

    if (!gVersusMode &&
        ((gCurrentLevel == LEVEL_SECTOR_Z) || (gCurrentLevel == LEVEL_FORTUNA) || (gCurrentLevel == LEVEL_VENOM_2) ||
         (gCurrentLevel == LEVEL_BOLSE) || (gCurrentLevel == LEVEL_SECTOR_Y) || (gCurrentLevel == LEVEL_KATINA))) {

        RCP_SetupDL(&gMasterDisp, SETUPDL_76);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 128, 128, 128, 255);

        switch (gCurrentLevel) {
            case LEVEL_SECTOR_Z:
                TextureRect_IA8(&gMasterDisp, D_SZ_60012D0, 16, 9, 251.0f + D_800D1E10, 181.0f, 1.00f, 1.00f);
                break;

            case LEVEL_FORTUNA:
                TextureRect_IA8(&gMasterDisp, D_FO_6001260, 16, 16, 251.0f + D_800D1E10, 178.0f, 1.00f, 1.00f);
                break;

            case LEVEL_BOLSE:
                TextureRect_IA8(&gMasterDisp, D_BO_6000C80, 16, 16, 251.0f + D_800D1E10, 178.0f, 1.00f, 1.00f);
                break;

            case LEVEL_SECTOR_Y:
                if ((fabsf(gScenery360[0].obj.pos.x) < temp2 + 1000.0f) &&
                    (fabsf(gScenery360[0].obj.pos.z) < temp2 + 1000.0f)) {
                    temp = 150.0f + ((12500.0f + gScenery360[0].obj.pos.z) / 446.42f);

                    if ((y < 150.0f) || (y > 206.0f)) {
                        break;
                    }
                    TextureRect_IA8(&gMasterDisp, D_SY_6000840, 64, 64, 250.0f + D_800D1E10, temp, 0.25f, 0.25f);
                }
                break;

            case LEVEL_KATINA:
                TextureRect_IA8(&gMasterDisp, D_KA_6001260, 8, 8, 254.0f + D_800D1E10, 182.0f, 1.00f, 1.00f);
                break;

            case LEVEL_VENOM_2:
                TextureRect_IA8(&gMasterDisp, D_VE2_6002890, 16, 16, 251.0f + D_800D1E10, 178.0f, 1.00f, 1.00f);
                break;
        }
    }

    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, x1, y1, z1, MTXF_APPLY);

    if ((gCurrentLevel == LEVEL_SECTOR_Z) && (D_hud_80161710 != 0)) {
        Matrix_Push(&gGfxMatrix);
        func_hud_80089D28();
        Matrix_Pop(&gGfxMatrix);
        D_hud_80161710--;
    }

    for (i = ARRAY_COUNT(gRadarMarks) - 1; i >= 0; i--) {
        if ((gRadarMarks[i].status == 0) || (fabsf(gRadarMarks[i].pos.x) >= (temp2 + 1000.0f)) ||
            (fabsf(gRadarMarks[i].pos.z) >= (temp2 + 1000.0f))) {
            continue;
        }

        Matrix_Push(&gGfxMatrix);
        Matrix_Translate(gGfxMatrix, gRadarMarks[i].pos.x * 0.008f, -gRadarMarks[i].pos.z * 0.008f, 0.0f, MTXF_APPLY);

        if (gRadarMarks[i].type == 103) {
            gRadarMarks[i].yRot = 45.0f;
        }

        Matrix_RotateZ(gGfxMatrix, M_DTOR * gRadarMarks[i].yRot, MTXF_APPLY);
        Matrix_Scale(gGfxMatrix, scale, scale, 1.0f, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);

        RadarMark_Draw(gRadarMarks[i].type);
        Matrix_Pop(&gGfxMatrix);

        gRadarMarks[i].status = 0;
    }

    Matrix_Pop(&gGfxMatrix);
    return 0;
}

s32 func_hud_8008AC54(s32 arg0) {
    Actor* actor;
    s32 i;
    s32 ret = 0;

    for (i = 0, actor = gActors; i < 60; i++, actor++) {
        switch (arg0) {
            case 0:
                if ((actor->obj.status == OBJ_ACTIVE) && (actor->obj.id == OBJ_ACTOR_190)) {
                    ret++;
                }
                break;

            case 1:
                if ((actor->obj.status == OBJ_ACTIVE) && (actor->obj.id == OBJ_ACTOR_191)) {
                    ret++;
                }
                break;

            case 2:
                if (((actor->obj.id == OBJ_ACTOR_190) || (actor->obj.id == OBJ_ACTOR_191)) &&
                    (actor->obj.status == OBJ_ACTIVE)) {
                    ret++;
                }
                break;
        }
    }

    return ret;
}

void func_hud_8008AD94(void) {
    if (gGameState == GSTATE_PLAY) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_76);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);

        switch ((s32) gRadioMsgRadioId) {
            case RCID_FOX:
                Graphics_DisplaySmallText(73, 173, 1.0f, 1.0f, "FOX");
                break;

            case RCID_FALCO:
                Graphics_DisplaySmallText(73, 173, 1.0f, 1.0f, "FALCO");
                break;

            case RCID_SLIPPY:
                Graphics_DisplaySmallText(73, 173, 1.0f, 1.0f, "SLIPPY");
                break;

            case RCID_PEPPY:
                Graphics_DisplaySmallText(73, 173, 1.0f, 1.0f, "PEPPY");
                break;

            case RCID_WOLF:
            case RCID_WOLF_2:
                Graphics_DisplaySmallText(73, 173, 1.0f, 1.0f, "WOLF");
                break;

            case RCID_LEON:
            case RCID_LEON_2:
                Graphics_DisplaySmallText(73, 173, 1.0f, 1.0f, "LEON");
                break;

            case RCID_PIGMA:
            case RCID_PIGMA_2:
                Graphics_DisplaySmallText(73, 173, 1.0f, 1.0f, "PIGMA");
                break;

            case RCID_ANDREW:
            case RCID_ANDREW_2:
                Graphics_DisplaySmallText(73, 173, 1.0f, 1.0f, "ANDREW");
                break;

            case RCID_BILL:
                Graphics_DisplaySmallText(73, 173, 1.0f, 1.0f, "BILL");
                break;

            case RCID_KATT:
                Graphics_DisplaySmallText(73, 173, 1.0f, 1.0f, "KATT");
                break;
        }
    }
}

void func_hud_8008B044(void) {
    switch (D_80161798) {
        case 0:
            if (gCallTimer == 0) {
                return;
            }

            AUDIO_PLAY_SFX(NA_SE_COMMU_REQUEST, gDefaultSfxSource, 4);

            if (gCallVoiceParam != 0) {
                Audio_SetUnkVoiceParam(1);
            }
            D_80161794 = 0;
            D_80161798 = 1;

        case 1:
            if (gCallTimer != 0) {
                D_80161790++;
                if (D_80161790 >= 7) {
                    if ((D_80161794 % 2) != 0) {
                        AUDIO_PLAY_SFX(NA_SE_COMMU_REQUEST, gDefaultSfxSource, 4);
                    }
                    D_80161790 = 0;
                    D_80161794++;
                }
                gCallTimer--;
            } else {
                gCallVoiceParam = 0;
                D_80161790 = 0;
                D_80161798 = 0;
                Audio_KillSfxById(NA_SE_COMMU_REQUEST);
            }
            break;
    }
}

void func_hud_8008B1B0(void) {
    f32 temp = 142.0f;
    f32 temp2 = 18.0f;

    RCP_SetupDL(&gMasterDisp, SETUPDL_78);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    switch (D_80161790 / 2) {
        case 3:
            func_hud_8008556C(temp + 31.0f, temp2);
        case 2:
            func_hud_80085514(temp + 24.0f, temp2);
        case 1:
            func_hud_800854BC(temp + 18.0f, temp2);
        case 0:
            func_hud_80085464(temp, temp2);
            break;
        default:
            break;
    }
}

void func_hud_8008B2A4(void) {
    if (gPlayState != PLAY_PAUSE) {
        func_hud_8008B044();
    }
    if (gCallTimer != 0) {
        func_hud_8008B1B0();
    }
}

s32 D_800D1EB4 = 255;
s32 D_800D1EB8 = 255;
s32 D_800D1EBC = 255;

void func_hud_8008B2F0(void) {
    f32 var_fv0;

    switch (D_hud_80161730) {
        case 0:
            D_801617B0 = 0;
            D_8016179C = 20.0f;
            D_801617A0 = 18.0f;

            if (gGoldRingCount[0] >= 3) {
                D_801617A4 = D_801617A8 = 1.5f;
            } else {
                D_801617A4 = D_801617A8 = 1.0f;
            }

            var_fv0 = gPlayer[0].shields;
            D_801617AC = var_fv0 / ((256.0f * D_801617A8) - 1.0f);

            if (gGoldRingCount[0] >= 3) {
                D_hud_80161730 = 2;
            } else {
                D_hud_80161730 = 1;
            }
            break;

        case 1:
            if (gGoldRingCount[0] >= 3) {
                D_801617B0 = 55;
                D_hud_80161730 = 2;
            }

        case 2:
            D_800D1EB4 = D_800D1EB8 = D_800D1EBC = 255;
            if (D_801617B0 > 0) {
                if (--D_801617B0 == 0) {
                    gPlayer[0].heal += 128;
                }
            }

            if (((D_801617B0 != 0) || ((D_801617A4 - D_801617A8) > 0.1f)) && (gGameFrameCount & 2)) {
                D_800D1EB4 = 0;
                D_800D1EB8 = 255;
                D_800D1EBC = 0;
            }

            if ((D_801617B0 == 0) && (gGoldRingCount[0] >= 3)) {
                D_801617A4 = 1.5f;
            } else {
                D_801617A4 = 1.0f;
            }

            Math_SmoothStepToF(&D_801617A8, D_801617A4, 0.02f, 1000.0f, 0.001f);

            var_fv0 = gPlayer[0].shields;
            if (var_fv0 > (256.0f * D_801617A8) - 1.0f) {
                var_fv0 = (256.0f * D_801617A8) - 1.0f;
            }
            D_801617AC = var_fv0 / ((256.0f * D_801617A8) - 1.0f);
            break;
    }
}

void func_hud_8008B5B0(f32 x, f32 y) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_75);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
    func_hud_800856C0(x + 8.0f, y + 2.0f, D_801617A8, 1.0f, D_801617AC);
    RCP_SetupDL(&gMasterDisp, SETUPDL_76);
    gDPSetPrimColor(gMasterDisp++, 0, 0, D_800D1EB4, D_800D1EB8, D_800D1EBC, 255);
    func_hud_80085618(x, y, 1.0f, 1.0f);
    func_hud_800855C4(x + 7.0f + (D_801617A8 * 6.0f * 8.0f), y, 1.0f, 1.0f);
    func_hud_8008566C(x + 7.0f, y, D_801617A8 * 6.0f, 1.0f);
}

void func_hud_8008B734(void) {
    func_hud_8008B2F0();
    func_hud_8008B5B0(20.0f, 18.0f);
    func_hud_80085944();
}

s32 func_hud_8008B774(void) {
    s32 i;
    s32 ret = 0;
    s32 temp;

    switch (gCurrentRadioPortrait) {
        case 0:
        case 1:
            i = 0;
            break;

        case 10:
        case 11:
            temp = 1;
            i = 1;
            break;

        case 20:
        case 21:
            temp = 2;
            i = 2;
            break;

        case 30:
        case 31:
            temp = 3;
            i = 3;
            break;

        case 240:
        case 241:
        case 200:
        case 201:
            i = 4;
            break;

        case 260:
        case 261:
        case 220:
        case 221:
            i = 5;
            break;

        case 250:
        case 251:
        case 210:
        case 211:
            i = 6;
            break;

        case 270:
        case 271:
        case 230:
        case 231:
            i = 7;
            break;

        default:
            i = 8;
            break;
    }

    if ((i >= 1) && (i <= 3) &&
        ((gLevelMode != LEVELMODE_ALL_RANGE) || (gCurrentLevel == LEVEL_CORNERIA) ||
         (gCurrentLevel == LEVEL_SECTOR_Y))) {
        for (i = 0; i < ARRAY_COUNT(gActors); i++) {
            if ((gActors[i].obj.status == OBJ_ACTIVE) && (gActors[i].iwork[12] == temp)) {
                if ((gActors[i].eventType == EVID_2) || (gActors[i].eventType == EVID_TEAMMATE) ||
                    ((gActors[i].obj.id == OBJ_ACTOR_TEAM_BOSS) &&
                     ((gActors[i].aiType == AI360_FALCO) || (gActors[i].aiType == AI360_SLIPPY) ||
                      (gActors[i].aiType == AI360_PEPPY)))) {
                    if (gActors[i].timer_0C6) {
                        ret = 1;
                    } else {
                        ret = 0;
                    }
                    break;
                }
            }
        }
        i = 9;
    }

    switch (i) {
        case 0:
            if (gPlayer[0].radioDamageTimer != 0) {
                ret = 1;
            }
            break;

        case 4:
        case 5:
        case 6:
        case 7:
            if (gLevelMode == LEVELMODE_ALL_RANGE) {
                if (gActors[i].timer_0C6) {
                    ret = 1;
                }
                if ((ret == 1) && (gActors[i].health <= 0)) {
                    ret = 2;
                }
            }
            break;

        case 8:
        case 9:
            break;

        default:
            if (gActors[i].timer_0C6) {
                ret = 1;
            }
            break;
    }
    return ret;
}

void func_hud_8008B9E8(void) {
    s32 temp;

    // clang-format off
    if ((D_8016178C != 0) && (D_8016178C != 1)) { D_8016178C--; }
    // clang-format on

    if (D_80161788 != 0) {
        D_80161788--;
    }

    if ((D_80161788 == 0) && (D_8016178C == 0)) {
        if ((gRadioState >= 4) && (gCurrentRadioPortrait != RCID_STATIC) &&
            (gCurrentRadioPortrait != RCID_STATIC + 1)) {
            temp = func_hud_8008B774();
            if (temp == 1) {
                D_80161788 = 20;
            }
            if (temp == 2) {
                D_8016178C = 60;
            }
        } else {
            D_80161788 = 0;
        }
    }

    if ((gCurrentRadioPortrait == RCID_STATIC) || (gCurrentRadioPortrait == RCID_STATIC + 1)) {
        D_80161788 = 0;
        D_8016178C = 0;
    }
}

void func_hud_8008BAE4(void) {
    s32 r;
    s32 g;
    s32 b;
    s32 alpha;

    if (D_8016178C != 0) {
        alpha = 192 / D_8016178C;
        r = g = b = 255;
    }

    if (D_80161788 != 0) {
        r = alpha = D_80161788 * 12;
        g = b = 0;
    }

    if ((D_80161788 != 0) || (D_8016178C != 0)) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_12);
        gDPSetPrimColor(gMasterDisp++, 0, 0, r, g, b, alpha);
        Matrix_Push(&gGfxMatrix);
        Matrix_Translate(gGfxMatrix, -53.9f, -38.5f, -139.4f, MTXF_APPLY);
        Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 1.0f, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, D_800D1A40);
        Matrix_Pop(&gGfxMatrix);
    }
}

void func_hud_8008BC80(void) {
    if (gPlayState != PLAY_PAUSE) {
        func_hud_8008B9E8();
        func_hud_8008BAE4();
    }
}

s32 func_hud_8008BCBC(s32 arg0) {
    s32 temp = 10;
    s32 ret;

    if (arg0 < 0) {
        arg0 = (s64) -arg0;
    }

    ret = 1;

    while (arg0 >= temp) {
        ret++;
        temp *= 10;
    }

    return ret;
}

void func_hud_8008BD00(u8* texturePtr, s32 xPos, s32 yPos, u8 arg3) {
    u8* texture = LOAD_ASSET(texturePtr);
    u8 temp;
    s32 x;
    s32 y;

    switch (arg3) {
        case 0:
            for (x = 0; x < xPos; x++) {
                temp = texture[x];
                for (y = 1; y < yPos; y++) {
                    texture[(y - 1) * xPos + x] = texture[y * xPos + x];
                }
                texture[(yPos - 1) * xPos + x] = temp;
            }
            break;

        case 1:
            for (x = 0; x < xPos; x++) {
                temp = texture[(yPos - 1) * xPos + x];
                for (y = yPos - 2; y >= 0; y--) {
                    texture[(y + 1) * xPos + x] = texture[y * xPos + x];
                }
                texture[x] = temp;
            }
            break;

        case 2:
            for (y = 0; y < yPos; y++) {
                temp = texture[y * xPos + xPos - 1];
                for (x = xPos - 2; x >= 0; x--) {
                    texture[y * xPos + x + 1] = texture[y * xPos + x];
                }
                texture[y * xPos] = temp;
            }
            break;

        case 3:
            for (y = 0; y < yPos; y++) {
                temp = texture[y * xPos];
                // clang-format off
                for (x = 1; x < xPos; x++) { texture[y * xPos + x - 1] = texture[y * xPos + x]; }
                // clang-format on
                texture[(y * xPos) + xPos - 1] = temp;
            }
            break;

        default:
            break;
    }
}

void func_hud_8008C104(u16* srcTexture, u16* dstTexture) {
    u16 *src, *dst;
    u16 buffer[1024];
    f32 rowPhase;
    f32 angle;
    s32 j;
    s32 i;
    s32 width = 32;
    s32 height = 32;
    s32 halfHeight;
    s32 offset;

    src = LOAD_ASSET(srcTexture);
    dst = LOAD_ASSET(dstTexture);

    Texture_Scroll(srcTexture, width, height, 1);

    halfHeight = height / 2;

    rowPhase = 0.0f;

    for (i = halfHeight - 1; true; i--) {
        rowPhase += 90.0f / halfHeight;
        if (rowPhase > 90.0f) {
            break;
        }

        angle = (height / 2) * COS_DEG(rowPhase);
        offset = angle;

        if (offset >= height) {
            offset = 0;
        }

        for (j = 0; j < width; j++) {
            buffer[(i * width) + j] = src[(offset * width) + j];
        }

        for (j = 0; j < width; j++) {
            buffer[(((halfHeight - i) + (halfHeight - 1)) * width) + j] =
                src[(((halfHeight - offset) + (halfHeight - 1)) * width) + j];
        }
    }
    Texture_Mottle(dst, buffer, 2);
}

void HUD_DisplaySmallNumber(f32 xPos, f32 yPos, f32 scale, s32 number) {
    void* sSmallNumberTex[] = {
        aSmallText_0, aSmallText_1, aSmallText_2, aSmallText_3, aSmallText_4,
        aSmallText_5, aSmallText_6, aSmallText_7, aSmallText_8, aSmallText_9,
    };
    s32 i;

    for (i = 10; i != 1; i /= 10) {
        if ((xPos > 0.0f) && (yPos > 0.0f)) {
            TextureRect_IA8(&gMasterDisp, sSmallNumberTex[number / i], 16, 8, xPos, yPos, scale, scale);
        }
        xPos += 9.0f * scale;
        number %= i;
    }

    if ((xPos > 0.0f) && (yPos > 0.0f)) {
        TextureRect_IA8(&gMasterDisp, sSmallNumberTex[number / i], 16, 8, xPos, yPos, scale, scale);
    }
}

void func_hud_8008C5C8(f32 arg0, f32 arg1, f32 arg2, s32 arg3) {
    u16* D_800D1EE8[] = {
        D_10050E0,
        D_100BAC0,
        D_100D900,
        D_10032A0,
    };
    s32 i;

    TextureRect_RGBA16(&gMasterDisp, D_800D1EE8[arg3], 44, 44, arg0, arg1, arg2, arg2);
}

void func_hud_8008C6F4(s32 idx, s32 arg1) {
    f32 D_800D1EF8[] = { 0.0f, 0.0f, -9.0f, 9.0f, 10.0f, 10.0f, 10.0f, 10.0f, 0.0f, 0.0f, -8.0f, 8.0f };
    f32 D_800D1F28[] = { -7.0f, 7.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 8.0f, -8.0f, 0.0f, 0.0f };
    f32 D_800D1F58[] = {
        -22.0f, -22.0f, -22.0f, -22.0f, -28.0f, -28.0f, -28.0f, -28.0f, -28.0f, -28.0f, -28.0f, -28.0f
    };
    f32 D_800D1F88[] = { 0.0f, 0.0f, 0.0f, 0.0f, 495.0f, 405.0f, 585.0f, 675.0f, 0.0f, 0.0f, 0.0f, 0.0f };
    f32 D_800D1FB8[] = { 180.0f, 0.0f, 270.0f, 90.0f, 270.0f, 270.0f, 270.0f, 270.0f, 0.0f, 180.0f, 90.0f, 270.0f };
    f32 D_800D1FE8[] = { 0.0f, 0.0f, 2.0f, -2.0f, -2.0f, -2.0f, -2.0f, -2.0f, 0.0f, 0.0f, 2.0f, -2.0f };
    f32 D_800D2018[] = { 2.0f, -2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -2.0f, 2.0f, 0.0f, 0.0f };

    Matrix_Push(&gGfxMatrix);

    if (gPlayer[0].alternateView) {
        Matrix_RotateZ(gGfxMatrix, M_DTOR * gPlayer[0].camRoll, MTXF_APPLY);
    }

    if (D_800D1F88[idx]) {
        Matrix_RotateZ(gGfxMatrix, M_DTOR * D_800D1F88[idx], MTXF_APPLY);
    }

    if (arg1 != 0) {
        Matrix_Translate(gGfxMatrix, D_800D1EF8[idx] + D_800D1FE8[idx], D_800D1F28[idx] + D_800D2018[idx],
                         D_800D1F58[idx], MTXF_APPLY);
    } else {
        Matrix_Translate(gGfxMatrix, D_800D1EF8[idx], D_800D1F28[idx], D_800D1F58[idx], MTXF_APPLY);
    }

    Matrix_RotateZ(gGfxMatrix, M_DTOR * D_800D1FB8[idx], MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, 0.026f, 0.026f, 0.026f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);

    RCP_SetupDL(&gMasterDisp, SETUPDL_62);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 150);
    gSPDisplayList(gMasterDisp++, D_1024990);

    Matrix_Pop(&gGfxMatrix);
}

void HUD_DrawEdgeArrows(void) {
    s32 D_800D2048[] = {
        0x80, 0x40, 0x20, 0x10, 8 | 2, 8 | 1, 4 | 2, 4 | 1, 8, 4, 2, 1,
    };
    s32 i;
    s32 j;

    if ((gPlayer[gPlayerNum].flags_228 != 0) && (gPlayer[gPlayerNum].pathChangeTimer == 0) &&
        (gPlayState != PLAY_PAUSE)) {
        j = gPlayer[gPlayerNum].flags_228;

        for (i = 0; i < 12; i++) {
            if ((j & D_800D2048[i]) != D_800D2048[i]) {
                continue;
            }

            j = (D_800D2048[i] ^ 0xFF) & j;

            if (gGameFrameCount & 4) {
                func_hud_8008C6F4(i, 0);
            }
            if ((gGameFrameCount - 2) & 4) {
                func_hud_8008C6F4(i, 1);
            }
        }
        func_hud_8008BD00(D_1024A58, 8, 8, 2);
    }
}

s32 HUD_dummy_8008CB8C(void) {
    return 0;
}

void func_hud_8008CB98(f32 arg0, f32 arg1, f32 arg2) {
    TextureRect_IA8(&gMasterDisp, D_versus_30013E0, 8, 8, arg0, arg1, arg2, arg2);
}

void func_hud_8008CBE4(void) {
    f32 D_800D2078[] = { 62.0f, 222.0f, 62.0f, 222.0f }; // X
    f32 D_800D2088[] = { 86.0f, 86.0f, 206.0f, 206.0f }; // Y
    s32 D_800D2098[] = { 177, 255, 0, 30 };              // R
    s32 D_800D20A8[] = { 242, 30, 179, 30 };             // G
    s32 D_800D20B8[] = { 12, 0, 67, 255 };               // B
    s32 i;
    s32 j;

    if (gVsMatchType != 0) {
        return;
    }

    switch (D_80161758) {
        case 0:
            for (i = 0; i < 4; i++) {
                D_80161738[i] = 0;
                D_80161748[i] = 0;
                D_80161760[i] = 0;
            }
            D_80161758 = 1;
            break;

        case 1:
            if (gVsMatchStart == 0) {
                D_80161758 = 0;
                break;
            }

            if (D_80161760[gPlayerNum] != 0) {
                D_80161760[gPlayerNum]--;
                if ((D_80161760[gPlayerNum] & 4) != 0) {
                    break;
                }
            }

            for (i = 0; i < gVsPoints[gPlayerNum]; i++) {
                if (D_80161748[gPlayerNum] < (i + 1)) {
                    if (((i + 1) != 1) && ((i + 1) == (gVsPointsToWin - 1))) {
                        D_80161760[gPlayerNum] = 50;
                        D_80161738[gPlayerNum] = 0;
                    } else {
                        D_80161738[gPlayerNum] = 50;
                    }
                    D_80161748[gPlayerNum] = i + 1;
                }

                if ((D_80161748[gPlayerNum] == (i + 1)) && (D_80161738[gPlayerNum] != 0)) {
                    D_80161738[gPlayerNum]--;
                    if ((D_80161738[gPlayerNum] & 4) != 0) {
                        continue;
                    }
                }

                j = gVsKills[gPlayerNum][i];

                RCP_SetupDL(&gMasterDisp, SETUPDL_77);

                gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
                gDPSetEnvColor(gMasterDisp++, D_800D2098[j], D_800D20A8[j], D_800D20B8[j], 0);

                func_hud_8008CB98(D_800D2078[gPlayerNum] + (i * 9.0f), D_800D2088[gPlayerNum], 1.0f);
            }
            break;
    }
}

void func_hud_8008CFB8(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    s32 i;

    // LTodo: [HD-Texture] Is broken
    u8* texture = (u8*) LOAD_ASSET(D_versus_3000BC0);
    TextureRect_IA8(&gMasterDisp, texture + 2 * ((640 * i) / 2), 80, 8, arg0, (8 * i * arg3) + arg1, arg2, arg3);
}

void func_hud_8008D0DC(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    u32 var_t8 = 48.0f * arg4;

    func_hud_80084E78(&gMasterDisp, D_versus_300D440, D_versus_300D500, 48, 4, arg0, arg1, arg2, arg3, var_t8, 4);
}

void func_hud_8008D1F0(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    TextureRect_CI4(&gMasterDisp, D_10116B0, D_1011730, 16, 16, arg0, arg1, arg2, arg3);
}

void func_hud_8008D250(void) {
    f32 D_800D20C8[] = { 113.0f, 273.0f, 113.0f, 273.0f };
    f32 D_800D20D8[] = { 79.0f, 79.0f, 199.0f, 199.0f };

    RCP_SetupDL(&gMasterDisp, SETUPDL_76);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
    func_hud_8008C5C8(D_800D20C8[gPlayerNum], D_800D20D8[gPlayerNum], 0.54f, gPlayerNum);
}

void func_hud_8008D31C(void) {
    f32 D_800D20E8[] = { 60.0f, 220.0f, 60.0f, 220.0f };
    f32 D_800D20F8[] = { 78.0f, 78.0f, 198.0f, 198.0f };

    Math_SmoothStepToF(&D_800D19E0[gPlayerNum], gPlayer[gPlayerNum].shields * (1.0f / 255.0f), 0.3f, 10.0f, 0.01f);
    RCP_SetupDL(&gMasterDisp, SETUPDL_78);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    func_hud_8008D0DC(D_800D20E8[gPlayerNum] + 3.0f, D_800D20F8[gPlayerNum] + 18.0f, 1.0f, 1.0f,
                      D_800D19E0[gPlayerNum]);
    RCP_SetupDL(&gMasterDisp, SETUPDL_76);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    func_hud_8008CFB8(D_800D20E8[gPlayerNum], D_800D20F8[gPlayerNum], 1.0f, 1.0f);
}

void func_hud_8008D4F0(f32 arg0, f32 arg1) {
    f32 D_800D2108[] = {
        110.0f, 270.0f, 110.0f, 270.0f, 0.0f,
    };
    f32 D_800D211C[] = {
        16.0f, 16.0f, 136.0f, 136.0f, 0.0f,
    };
    f32 temp_fv0;
    f32 temp2;
    f32 temp_fs0;
    f32 sp68;
    f32 temp;
    f32 sp60;
    s32 temp_t9;
    s32 var_v1;

    if (gVersusMode) {
        temp = 2.0f;
        sp60 = 1.0f;
        var_v1 = gPlayerNum;
        sp68 = 24.0f;
    } else {
        temp = 2.0f;
        sp60 = 2.0f;
        sp68 = 40.0f;
        var_v1 = 4;
        D_800D2108[var_v1] = arg0;
        D_800D211C[var_v1] = arg1;
    }

    temp_fs0 = gPlayer[gPlayerNum].boostMeter * (1.0f / 90.0f);

    temp_fv0 = 1.0f - temp_fs0;
    temp2 = sp68 * temp_fs0;

    if (!gPlayer[gPlayerNum].boostCooldown) {
        Math_SmoothStepToF(&D_800D19AC[var_v1], 255.0f, 0.4f, 100.0f, 0.01f);
    } else {
        Math_SmoothStepToF(&D_800D19AC[var_v1], 100.0f, 0.4f, 100.0f, 0.01f);
    }

    temp_t9 = D_800D19AC[var_v1];

    RCP_SetupDL(&gMasterDisp, SETUPDL_78);

    gDPSetPrimColor(gMasterDisp++, 0, 0, temp_t9, temp_t9, temp_t9, 255);

    if (temp_fv0 > 0.01f) {
        func_hud_80085890(D_800D2108[var_v1] + temp + temp2, D_800D211C[var_v1] + sp60, temp_fv0, 1.0f);
    }
    if (temp_fs0 > 0.01f) {
        func_hud_800857DC(D_800D2108[var_v1] + temp + 1.0f, D_800D211C[var_v1] + sp60, temp_fs0, 1.0f);
    }
    RCP_SetupDL(&gMasterDisp, SETUPDL_76);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
    func_hud_80085740(D_800D2108[var_v1], D_800D211C[var_v1], 1.0f, 1.0f);
}

void func_hud_8008D7F4(void) {
    s32 D_800D2130[] = { 146, 165, 146, 165 };
    s32 D_800D2140[] = { 106, 106, 125, 125 };
    s32 D_800D2150[] = { 177, 255, 0, 30 };
    s32 D_800D2160[] = { 242, 30, 179, 30 };
    s32 D_800D2170[] = { 12, 0, 67, 255 };

    RCP_SetupDL(&gMasterDisp, SETUPDL_78);
    gDPSetPrimColor(gMasterDisp++, 0, 0, D_800D2150[gPlayerNum], D_800D2160[gPlayerNum], D_800D2170[gPlayerNum], 255);
    Graphics_DisplayHUDNumber(D_800D2130[gPlayerNum], D_800D2140[gPlayerNum], gPlayerNum + 1);
}

s32 D_800D2180[4] = { 0, 0, 0, 0 };
s32 D_800D2190[4] = { 0, 0, 0, 0 };
f32 D_800D21A0 = 255.0f;
f32 D_800D21A4 = 0.0f;

void func_hud_8008D984(void) {
    s32 D_800D21A8[] = { 146, 165, 146, 165 };
    s32 D_800D21B8[] = { 94, 94, 137, 137 };

    if (gBombCount[gPlayerNum] != D_800D2180[gPlayerNum]) {
        D_800D2180[gPlayerNum] = gBombCount[gPlayerNum];
        if (gBombCount[gPlayerNum] == 0) {
            D_800D2190[gPlayerNum] = 0;
        } else {
            D_800D2190[gPlayerNum] = 30;
        }
    }

    if (D_800D2190[gPlayerNum] != 0) {
        D_800D2190[gPlayerNum]--;
    }

    if (((D_800D2190[gPlayerNum] & 2) != 0) || ((D_800D2190[gPlayerNum] == 0) && (gBombCount[gPlayerNum] != 0))) {
        RCP_SetupDL_78();
        if (gBombCount[gPlayerNum] >= 2) {
            if (Math_SmoothStepToF(&D_800D21A4, D_800D21A0, 0.4f, 100.0f, 0.1f) == 0.0f) {
                if (D_800D21A0 == 255.0f) {
                    D_800D21A0 = 96.0f;
                } else {
                    D_800D21A0 = 255.0f;
                }
            }
        } else {
            D_800D21A4 = 255.0f;
        }
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, D_800D21A4);
        func_hud_8008D1F0(D_800D21A8[gPlayerNum], D_800D21B8[gPlayerNum], 1.0f, 1.0f);
    }
}

void func_hud_8008DC34(void) {
    if ((gVsMatchStart != 0) && (D_versus_80178750 == 0)) {
        func_hud_8008D250();
        func_hud_8008D7F4();
        func_hud_8008D4F0(0, 0);
        func_hud_8008D31C();
        func_hud_8008D984();
    }

    if (D_versus_80178750 == 0) {
        func_hud_8008CBE4();
    }
}

void func_hud_8008DCB0(f32 arg0, f32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    RCP_SetupDL_78();
    gDPSetPrimColor(gMasterDisp++, 0, 0, arg2, arg3, arg4, D_hud_80161708);
    TextureRect_CI4(&gMasterDisp, D_1011ED0, D_1011F08, 16, 7, arg0, arg1, 1.0f, 1.0f);
}

void func_hud_8008DD78(f32 arg0, f32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    RCP_SetupDL_78();
    gDPSetPrimColor(gMasterDisp++, 0, 0, arg3, arg4, arg5, D_hud_80161708);

    if (arg2 >= 10) {
        Graphics_DisplayHUDNumber((s32) arg0 - (func_hud_8008BCBC(arg2) * 8) + 11, arg1, arg2);
    } else {
        Graphics_DisplayHUDNumber(arg0, arg1, arg2);
    }
}

void HUD_DrawBossHealth(void) {
    f32 sp3C;
    f32 temp1;
    f32 temp2;
    f32 temp3;
    f32 temp4;
    f32 temp5;
    f32 temp6;
    f32 temp7;
    f32 var_fv0;

    if ((gShowBossHealth == 1) && (gTeamShields[TEAM_ID_SLIPPY] > 0)) {
        if ((gBossHealthBar >= 0) && (D_801616BC == -1.0f)) {
            AUDIO_PLAY_SFX(NA_SE_BOSS_GAUGE_OPEN, gDefaultSfxSource, 4);
            D_801616BC = 255.0f;
        }

        Math_SmoothStepToF(&D_801616C0, 25.0f, 0.3f, 4.0f, 4.0f);

        sp3C = D_801616C0;
        temp1 = 52.0f;
        temp2 = sp3C + 5.0f;
        temp3 = temp1 + 3.0f;
        temp4 = sp3C + 6.0f;
        temp5 = temp1 + 10.0f;

        RCP_SetupDL(&gMasterDisp, SETUPDL_78);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
        TextureRect_CI4(&gMasterDisp, D_1011A40, D_1011AB0, 32, 7, temp2, temp3, 1.0f, 1.0f);

        RCP_SetupDL(&gMasterDisp, SETUPDL_76);
        TextureRect_IA8(&gMasterDisp, D_1002040, 40, 12, sp3C, temp1, 1.0f, 1.0f);

        if (sp3C >= 25.0f) {
            Math_SmoothStepToF(&D_801616C4, 0.88f, 0.3f, 0.2f, 0.1f);
        }

        if ((D_801616C4 >= 0.1f) && (sp3C >= 25.0f)) {
            RCP_SetupDL(&gMasterDisp, SETUPDL_78);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
            TextureRect_CI8(&gMasterDisp, D_10129C0, D_1013090, 16, 109, temp4, temp5, 1.0f, D_801616C4);
        }

        RCP_SetupDL(&gMasterDisp, SETUPDL_76);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 0, 0, 0, 255);

        if (D_801616BC > 0.0f) {
            var_fv0 = (D_801616BC - gBossHealthBar) * (2.76f / D_801616BC);
            if (var_fv0 > 2.76f) {
                var_fv0 = 2.76f;
            }
            if (var_fv0 < 0.00f) {
                var_fv0 = 0.00f;
            }
            Math_SmoothStepToF(&D_801616C8, var_fv0, 0.2f, 1000.0f, 0.01f);
        } else {
            D_801616C8 = 2.76f;
        }

        if (D_801616C4 >= 0.88f) {
            temp6 = sp3C + 8.0f;
            temp7 = 101.0f - ((2200.0f / 69.0f) * D_801616C8) + temp1;
            if (D_801616C8 > 0.0f) {
                TextureRect_RGBA16(&gMasterDisp, D_Tex_800D99F8, 32, 32, temp6, temp7, 0.2f, D_801616C8);
            }
        }
    } else {
        D_801616C0 = 0.0f;
        D_801616C4 = 0.0f;
        D_801616C8 = 0.0f;
        D_801616BC = -1.0f;
    }
}

void HUD_DisplayCountdown(f32 xPos, f32 yPos, s32* countdown, f32 scale) {
    f32 var_fs0 = 0.0f;
    s32 var_s2 = 0;
    s32 i;

    xPos -= (scale - 1.0f) * 34.0f;
    yPos -= (scale - 1.0f) * 4.0f;

    for (i = 0; i != 5; i++) {
        if ((i == 0) || (i == 2)) {
            var_s2 = countdown[i / 2] % 60;
        }

        if (i == 4) {
            var_s2 = countdown[i / 2] % 100;
        }

        if ((i % 2) != 0) {
            RCP_SetupDL_78();
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
            TextureRect_CI4(&gMasterDisp, D_1011E80, D_1011EC0, 16, 8, (var_fs0 * scale) + xPos, yPos, scale, scale);
        } else {
            RCP_SetupDL_76();
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);
            HUD_DisplaySmallNumber((var_fs0 * scale) + xPos, yPos, scale, var_s2);
            var_fs0 += 9.0f;
        }
        var_fs0 += 9.0f;
    }
}

void HUD_DrawCountdown(s32* countdown, f32 scale) {
    //! FAKE:
    if (1) {}

    if (gPlayState != PLAY_PAUSE) {
        countdown[2] -= 3;
        if (countdown[2] >= 3) {
        } else {
            countdown[2] = 99;
            countdown[1]--;
            if (countdown[1] >= 0) {
            } else {
                countdown[1] = 59;
                countdown[0]--;
                if (countdown[0] >= 0) {
                } else {
                    countdown[0] = 0;
                    countdown[1] = 0;
                    countdown[2] = 0;
                }
            }
        }
    }

    if (gPlayState != PLAY_PAUSE) {
        HUD_DisplayCountdown(176.0f, 22.0f, countdown, scale);
    }
}

void func_hud_8008E5E8(void) {
    if (gVersusMode) {
        func_hud_8008DC34();
    }
    func_hud_8008A4DC();
}

void func_hud_8008E620(f32 arg0, f32 arg1) {
    f32 r;
    f32 g;
    f32 b;
    s32 ret;

    switch (gCurrentLevel) {
        case LEVEL_CORNERIA:
            ret = Play_CheckMedalStatus(150);
            break;

        case LEVEL_METEO:
            ret = Play_CheckMedalStatus(200);
            break;

        case LEVEL_FORTUNA:
            ret = Play_CheckMedalStatus(50);
            break;

        case LEVEL_SECTOR_X:
            ret = Play_CheckMedalStatus(150);
            break;

        case LEVEL_TITANIA:
            ret = Play_CheckMedalStatus(150);
            break;

        case LEVEL_BOLSE:
            ret = Play_CheckMedalStatus(150);
            break;

        case LEVEL_SECTOR_Y:
            ret = Play_CheckMedalStatus(150);
            break;

        case LEVEL_KATINA:
            ret = Play_CheckMedalStatus(150);
            break;

        case LEVEL_SOLAR:
            ret = Play_CheckMedalStatus(100);
            break;

        case LEVEL_MACBETH:
            ret = Play_CheckMedalStatus(150);
            break;

        case LEVEL_AQUAS:
            ret = Play_CheckMedalStatus(150);
            break;

        case LEVEL_ZONESS:
            ret = Play_CheckMedalStatus(250);
            break;

        case LEVEL_SECTOR_Z:
            ret = Play_CheckMedalStatus(100);
            break;

        case LEVEL_AREA_6:
            ret = Play_CheckMedalStatus(300);
            break;

        case LEVEL_VENOM_ANDROSS:
        case LEVEL_VENOM_2:
            ret = Play_CheckMedalStatus(200);
            break;

        default:
            ret = false;
            break;
    }

    if (gMedalFlashTimer != 0) {
        gMedalFlashTimer--;
    }

    if (ret != gMedalStatus) {
        gMedalFlashTimer = 30;
        gMedalStatus = ret;
    }

    if ((gMedalFlashTimer % 2) != 0) {
        r = 255;
        g = 255;
        b = 255;
    } else {
        if (ret != 0) {
            r = 200;
            g = 100;
            b = 50;
        } else {
            r = 90;
            g = 160;
            b = 200;
        }
    }
    RCP_SetupDL(&gMasterDisp, SETUPDL_76);
    gDPSetPrimColor(gMasterDisp++, 0, 0, r, g, b, 255);
    func_hud_80094D20(arg0, arg1);
}

void func_hud_8008E9EC(f32 arg0, f32 arg1) {
    func_hud_8008E620(arg0, arg1);
    func_hud_8008B734();
}

void func_hud_8008EA14(f32 x, f32 y) {
    s32 i;
    s32 sp68;
    f32 temp_fv0;
    f32 temp;

    if (gBombCount[gPlayerNum] > 9) {
        gBombCount[gPlayerNum] = 9;
    }

    switch (D_800D19F8) {
        case 0:
            D_800D19F4 = gBombCount[gPlayerNum];
            sp68 = 0;
            D_800D19F8 = 1;
            D_80161770 = D_80161774 = D_80161778 = 255.0f;
            D_8016177C = D_80161780 = D_80161784 = 255.0f;
            break;

        case 1:
            temp_fv0 = gBombCount[gPlayerNum] - D_800D19F4;
            if (temp_fv0 > 0.0f) {
                D_800D19F4++;
                if (D_800D19F4 > 5) {
                    sp68 = 0;
                    break;
                }
                if (D_800D19F4 == 5) {
                    D_800D19F0 = 0.0f;
                    sp68 = 4;
                    D_800D19F8 = 6;
                    break;
                } else {
                    D_800D19F0 = 0.0f;
                    sp68 = 3;
                    D_800D19F8 = 5;
                }
                break;
            }

            if (temp_fv0 < 0.0f) {
                D_800D19F8 = 2;
            }
            sp68 = 0;
            break;

        case 2:
            D_800D19F4--;
            sp68 = 0;
            D_800D19F8 = 1;
            if (D_800D19F4 <= 3) {
                D_800D19F0 = 0.0f;
                sp68 = 2;
                D_800D19F8 = 4;
                break;
            }

            if (D_800D19F4 == 4) {
                D_800D19F0 = 0.0f;
                sp68 = 1;
                D_800D19F8 = 3;
                break;
            }
            break;

        case 3:
            sp68 = 1;
            if (Math_SmoothStepToF(&D_800D19F0, 10.0f, 0.3f, 10.0f, 0.1f) == 0.0f) {
                D_800D19F8 = 1;
                D_800D19F0 = 10.0f;
                sp68 = 1;
            }
            break;

        case 4:
            sp68 = 2;
            if (Math_SmoothStepToF(&D_800D19F0, 10.0f, 0.3f, 10.0f, 0.1f) == 0.0f) {
                D_800D19F8 = 1;
                D_800D19F0 = 10.0f;
                sp68 = 2;
            }
            break;

        case 5:
            sp68 = 3;
            if (Math_SmoothStepToF(&D_800D19F0, 20.0f + ((D_800D19F4 - 1) * 10), 0.3f, 10.0f, 0.001f) == 0.0f) {
                D_800D19F8 = 1;
                D_800D19F0 = 20.0f + ((D_800D19F4 - 1) * 10);
                sp68 = 3;
            }
            break;

        case 6:
            sp68 = 4;
            if (Math_SmoothStepToF(&D_800D19F0, 10.0f, 0.3f, 10.0f, 0.1f) == 0.0f) {
                D_800D19F8 = 7;
                D_800D19F0 = 0.0f;
                sp68 = 5;
            }
            break;

        case 7:
            sp68 = 5;
            if (0.0f == Math_SmoothStepToF(&D_800D19F0, 12.0f, 0.3f, 10.0f, 5.0f)) {
                D_800D19F8 = 1;
                D_800D19F0 = 0.0f;
                sp68 = 0;
            }
            break;

        default:
            break;
    }

    if (gPlayerShots[15].obj.status == SHOT_FREE) {
        D_80161770 = D_80161774 = D_80161778 = 255.0f;
        D_8016177C = D_80161780 = 255.0f;
        D_80161784 = 0.0f;
    } else {
        D_80161770 = 100.0f;
        D_80161774 = D_80161778 = 0.0f;
        D_8016177C = D_80161780 = 40.0f;
        D_80161784 = 0.0f;
    }

    RCP_SetupDL_78();
    gDPSetPrimColor(gMasterDisp++, 0, 0, (s32) D_80161770, (s32) D_80161774, (s32) D_80161778, D_hud_80161708);

    if (gCurrentLevel == LEVEL_AQUAS) {
        sp68 = 6;
    }

    switch (sp68) {
        case 0:
            if (D_800D19F4 >= 5) {
                TextureRect_CI4(&gMasterDisp, D_10116B0, D_1011730, 16, 16, x, y, 1.0f, 1.0f);
                func_hud_8008DCB0(x + 14.0f, y + 2.0f, D_8016177C, D_80161780, D_80161784);
                func_hud_8008DD78(x + 29.0f, y + 1.0f, D_800D19F4, D_8016177C, D_80161780, D_80161784);
            } else {
                for (i = (D_800D19F4 - 1); i >= 0; i--) {
                    TextureRect_CI4(&gMasterDisp, D_10116B0, D_1011730, 16, 16, x + (30.0f - (i * 10)), y, 1.0f, 1.0f);
                }
            }
            break;

        case 1:
            TextureRect_CI4(&gMasterDisp, D_10116B0, D_1011730, 16, 16, x + (D_800D19F0 * 3.0f), y, 1.0f, 1.0f);
            TextureRect_CI4(&gMasterDisp, D_10116B0, D_1011730, 16, 16, x + (D_800D19F0 * 2.0f), y, 1.0f, 1.0f);
            TextureRect_CI4(&gMasterDisp, D_10116B0, D_1011730, 16, 16, x + (D_800D19F0 * 1.0f), y, 1.0f, 1.0f);
            TextureRect_CI4(&gMasterDisp, D_10116B0, D_1011730, 16, 16, x + (D_800D19F0 * 0.0f), y, 1.0f, 1.0f);
            break;

        case 2:
            for (i = D_800D19F4; i >= 0; i--) {
                if (i == 0) {
                    temp = D_800D19F0 * 4.0f;
                } else {
                    temp = D_800D19F0;
                }
                TextureRect_CI4(&gMasterDisp, D_10116B0, D_1011730, 16, 16, x + (30.0f - (i * 10)) + temp, y, 1.0f,
                                1.0f);
            }
            break;

        case 3:
            for (i = (D_800D19F4 - 2); i >= 0; i--) {
                TextureRect_CI4(&gMasterDisp, D_10116B0, D_1011730, 16, 16, x + (30.0f - (i * 10)), y, 1.0f, 1.0f);
            }
            TextureRect_CI4(&gMasterDisp, D_10116B0, D_1011730, 16, 16, x + 50.0f - D_800D19F0, y, 1.0f, 1.0f);
            break;

        case 4:
            TextureRect_CI4(&gMasterDisp, D_10116B0, D_1011730, 16, 16, x + 30.0f - (D_800D19F0 * 3.0f), y, 1.0f, 1.0f);
            TextureRect_CI4(&gMasterDisp, D_10116B0, D_1011730, 16, 16, x + 20.0f - (D_800D19F0 * 2.0f), y, 1.0f, 1.0f);
            TextureRect_CI4(&gMasterDisp, D_10116B0, D_1011730, 16, 16, x + 10.0f - (D_800D19F0 * 1.0f), y, 1.0f, 1.0f);
            TextureRect_CI4(&gMasterDisp, D_10116B0, D_1011730, 16, 16, x, y, 1.0f, 1.0f);
            break;

        case 5:
            func_hud_8008DCB0(x + D_800D19F0, y + 2.0f, D_8016177C, D_80161780, D_80161784);
            func_hud_8008DD78(x + 15.0f + D_800D19F0, y + 1.0f, D_800D19F4, D_8016177C, D_80161780, D_80161784);
            TextureRect_CI4(&gMasterDisp, D_10116B0, D_1011730, 16, 16, x, y, 1.0f, 1.0f);
            break;

        case 6:
            RCP_SetupDL(&gMasterDisp, SETUPDL_78);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
            TextureRect_CI4(&gMasterDisp, D_blue_marine_3000090, D_blue_marine_3000120, 32, 9, x + 1.0f, y, 1.0f, 1.0f);
            break;
    }
}

void func_hud_8008F94C(void) {
    func_hud_8008E5E8();
}

void func_hud_8008F96C(void) {
    if (gPlayState != PLAY_PAUSE) {
        func_hud_8008E5E8();
    }

    RCP_SetupDL_36();

    if ((gLevelMode != LEVELMODE_UNK_2) && (D_hud_80161708 != 0)) {
        func_hud_8008D4F0(246.0f, 28.0f);
        func_hud_8008EA14(250.0f, 38.0f);
    }

    func_hud_8008B2A4();

    if (D_hud_80161708 != 0) {
        func_hud_8008E9EC(24.0f, 30.0f);
        if (gCurrentLevel != LEVEL_TRAINING) {
            func_hud_80087530(248.0f, 11.0f, gLifeCount[gPlayerNum]);
        }
    }

    if (gCurrentLevel == LEVEL_TRAINING) {
        Training_801988E0();
    }
}

void HUD_Draw(void) {
    s32 i;
    s32 goldRings;
    bool medalStatus;

    if (D_hud_80161730 == 0) {
        for (i = 0; i < 10; i++) {
            D_801617E8[i] = 0;
            D_801617C0[i] = 0;
            D_80161838[i] = 0;
            D_80161810[i] = 0;
        }

        for (i = 0; i < 20; i++) {
            D_80161900[i] = 0;
            D_80161860[i] = 0;
            D_801618B0[i] = 0.0f;
        }

        if (gGoldRingCount[0] != 0) {
            goldRings = gGoldRingCount[0];
            if (!(goldRings = gGoldRingCount[0] % 3)) {
                goldRings = 3;
            }

            for (i = 0; i < goldRings; i++) {
                if (goldRings != 3) {
                    D_80161860[i + 1] = 1;
                }
            }
            gGoldRingCount[1] = gGoldRingCount[0];
        } else {
            gGoldRingCount[1] = 0;
        }

        D_800D19F8 = 0;
        D_80161788 = 0;
        D_8016178C = 0;
        gMedalStatus = 0;
        gMedalFlashTimer = 0;

        switch (gCurrentLevel) {
            case LEVEL_CORNERIA:
                medalStatus = Play_CheckMedalStatus(150);
                break;
            case LEVEL_METEO:
                medalStatus = Play_CheckMedalStatus(200);
                break;
            case LEVEL_FORTUNA:
                medalStatus = Play_CheckMedalStatus(50);
                break;
            case LEVEL_SECTOR_X:
                medalStatus = Play_CheckMedalStatus(150);
                break;
            case LEVEL_TITANIA:
                medalStatus = Play_CheckMedalStatus(150);
                break;
            case LEVEL_BOLSE:
                medalStatus = Play_CheckMedalStatus(150);
                break;
            case LEVEL_SECTOR_Y:
                medalStatus = Play_CheckMedalStatus(150);
                break;
            case LEVEL_KATINA:
                medalStatus = Play_CheckMedalStatus(150);
                break;
            case LEVEL_SOLAR:
                medalStatus = Play_CheckMedalStatus(100);
                break;
            case LEVEL_MACBETH:
                medalStatus = Play_CheckMedalStatus(200);
                break;
            case LEVEL_AQUAS:
                medalStatus = Play_CheckMedalStatus(100);
                break;
            case LEVEL_ZONESS:
                medalStatus = Play_CheckMedalStatus(250);
                break;
            case LEVEL_SECTOR_Z:
                medalStatus = Play_CheckMedalStatus(100);
                break;
            case LEVEL_AREA_6:
                medalStatus = Play_CheckMedalStatus(300);
                break;
            case LEVEL_VENOM_2:
            case LEVEL_VENOM_ANDROSS:
                medalStatus = Play_CheckMedalStatus(200);
                break;

            default:
                medalStatus = false;
                break;
        }
        if (medalStatus != gMedalStatus) {
            gMedalStatus = medalStatus;
        }
    }

    if ((D_hud_80161704 != 0) && (gPlayState != PLAY_PAUSE)) {
        D_hud_80161708 += 16;
        if (D_hud_80161708 >= D_hud_80161704) {
            D_hud_80161708 = D_hud_80161704;
        }
    }

    if (gCamCount != 1) {
        func_hud_8008F94C();
    } else {
        func_hud_8008F96C();
    }
    func_hud_8008BC80();
    func_hud_80088970();
}

void HUD_BossFO_Draw(Boss* boss) {
    RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
    gSPDisplayList(gMasterDisp++, D_FO_6003090);
    RCP_SetupDL_34(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
    gDPSetTextureFilter(gMasterDisp++, G_TF_POINT);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 0, (s32) boss->fwork[1], (s32) boss->fwork[2], 255);
    gSPDisplayList(gMasterDisp++, D_FO_600D5C0);
    gDPSetTextureFilter(gMasterDisp++, G_TF_BILERP);
}

void func_hud_8008FFF0(Boss* boss, s32 arg1) {
    Vec3s D_800D21C8[] = {
        { -385, 54, 233 },   { -324, 148, 193 },  { -267, 186, 136 },  { -128, 430, 180 },  { -231, 584, 140 },
        { -431, 551, -120 }, { -285, 516, -32 },  { -285, 601, 18 },   { 300, 596, 18 },    { 300, 529, -65 },
        { 491, 529, -178 },  { 94, 457, 219 },    { 247, 457, 36 },    { 220, 611, 129 },   { 220, 427, 129 },
        { 150, 451, 213 },   { 72, 379, 156 },    { 98, 255, 156 },    { 263, 188, 156 },   { 96, 289, 55 },
        { 375, 43, 215 },    { 2, 43, -431 },     { 50, 154, -354 },   { -59, 231, -211 },  { 40, 272, -133 },
        { -48, 370, -147 },  { -116, 410, -153 }, { -116, 600, -230 }, { -231, 580, -285 }, { -231, 498, -218 },
        { -413, 450, -269 }, { -203, 450, -152 }, { 149, 450, -152 },  { 308, 450, -213 },  { 308, 552, -326 },
        { 376, 494, -304 },  { 376, 494, -304 },
    };
    s32 i;
    f32 temp;
    s32 temp2;
    if (arg1 >= 7000) {
        temp2 = arg1 - 7000;

        if (temp2 > 1596) {
            temp2 = 1596;
        }

        temp = temp2 / 1596.0f;

        if (boss->swork[0] != 1) {
            temp /= 2.0f;
        }

        i = RAND_INT(36.0f);

        if ((gGameFrameCount & 2) == 0) {
            func_effect_8007C120(boss->obj.pos.x + D_800D21C8[i].x, boss->obj.pos.y + D_800D21C8[i].y,
                                 boss->obj.pos.z + D_800D21C8[i].z, 0.0f, 0.0f, 0.0f, 0.3f * temp, 20);
        }

        if (((gGameFrameCount % 8) == 0)) {
            func_effect_8007BFFC(boss->obj.pos.x + D_800D21C8[i].x, boss->obj.pos.y + D_800D21C8[i].y,
                                 boss->obj.pos.z + D_800D21C8[i].z, 0.0f, 0.0f, 0.0f, 7.0f * temp, 10);
        }
    }
}

s32 func_hud_80090200(Boss* boss) {
    Vec3f dest, src;
    Player* player;
    s32 ret = 0;

    if (boss->swork[0] == 1) {
        func_hud_8008FFF0(boss, 8596);
        player = &gPlayer[0];
        ret = 1;

        switch (boss->swork[1]) {
            case 0:
                AUDIO_PLAY_SFX(NA_SE_EARTHQUAKE, boss->sfxSource, 0);
                AUDIO_PLAY_SFX(NA_SE_EXPLOSION_DEMO, boss->sfxSource, 0);
                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 50);
                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 50);

                player->cam.eye.x = boss->fwork[4] = boss->obj.pos.x;
                player->cam.eye.y = boss->fwork[5] = boss->obj.pos.y + 500.0f;
                player->cam.eye.z = boss->fwork[6] = boss->obj.pos.z + 4000.0f;

                player->cam.at.x = boss->obj.pos.x;
                player->cam.at.y = boss->obj.pos.y;
                player->cam.at.z = boss->obj.pos.z;

                boss->fwork[7] = 0.0f;
                boss->fwork[8] = 0.0f;
                boss->fwork[9] = 10.0f;

                boss->timer_050 = 1000;

                boss->swork[1] = 1;
                break;

            case 1:
                if (boss->timer_050 == 930) {
                    boss->swork[1] = 2;
                }

                boss->fwork[7] += 0.5f;
                if (boss->fwork[7] >= 360.0f) {
                    boss->fwork[7] = 0.0f;
                }

                Math_SmoothStepToF(&boss->fwork[9], 80.0f, 0.01f, 10000.0f, 0.0f);
                Math_SmoothStepToF(&boss->fwork[4], boss->obj.pos.x + 0.0f, 0.02f, 10000.0f, 0.0f);
                Math_SmoothStepToF(&boss->fwork[5], boss->obj.pos.y + 500.0f, 0.02f, 10000.0f, 0.0f);
                Math_SmoothStepToF(&boss->fwork[6], boss->obj.pos.z + 1500.0f, 0.02f, 10000.0f, 0.0f);
                break;

            case 2:
                if (boss->timer_050 == 870) {
                    boss->swork[1] = 3;
                }

                boss->fwork[7] += 3.0f;
                if (boss->fwork[7] >= 360.0f) {
                    boss->fwork[7] = 0.0f;
                }

                Math_SmoothStepToF(&boss->fwork[4], boss->obj.pos.x + 0.0f, 0.02f, 10000.0f, 0.0f);
                Math_SmoothStepToF(&boss->fwork[5], boss->obj.pos.y + 1500.0f, 0.02f, 10000.0f, 0.0f);
                Math_SmoothStepToF(&boss->fwork[6], boss->obj.pos.z + 1500.0f, 0.02f, 10000.0f, 0.0f);
                break;

            case 3:
                if (boss->timer_050 == 770) {
                    boss->swork[1] = 4;
                }

                Math_SmoothStepToF(&boss->fwork[9], 10.0f, 0.01f, 10000.0f, 0.0f);
                Math_SmoothStepToF(&boss->fwork[4], boss->obj.pos.x + 4000.0f, 0.02f, 10000.0f, 0.0f);
                Math_SmoothStepToF(&boss->fwork[5], boss->obj.pos.y + 2000.0f, 0.02f, 10000.0f, 0.0f);
                Math_SmoothStepToF(&boss->fwork[6], boss->obj.pos.z + 1500.0f, 0.02f, 10000.0f, 0.0f);
                break;

            case 4:
                ret = 2;
        }

        if (boss->swork[1] < 4) {
            src.x = boss->fwork[4] - boss->obj.pos.x;
            src.y = boss->fwork[5] - boss->obj.pos.y;
            src.z = boss->fwork[6] - boss->obj.pos.z;

            Matrix_Translate(gCalcMatrix, boss->obj.pos.x, boss->obj.pos.y, boss->obj.pos.z, MTXF_NEW);
            Matrix_RotateY(gCalcMatrix, M_DTOR * boss->fwork[7], MTXF_APPLY);
            Matrix_RotateX(gCalcMatrix, M_DTOR * boss->fwork[8], MTXF_APPLY);
            Matrix_MultVec3f(gCalcMatrix, &src, &dest);

            player->cam.eye.x = dest.x;
            player->cam.eye.y = dest.y;
            player->cam.eye.z = dest.z;

            player->cam.at.x = boss->obj.pos.x;
            player->cam.at.y = boss->obj.pos.x;
            player->cam.at.z = boss->obj.pos.x;

            player->cam.at.x += COS_DEG(boss->timer_050 * 60.0f) * boss->fwork[9];
            player->cam.at.y += SIN_DEG(boss->timer_050 * 179.0f) * boss->fwork[9];
        }
    }

    return ret;
}

void HUD_BossFO_Update(Boss* boss) {
    switch (boss->state) {
        case 0:
            if ((boss->fwork[1] == 255.0f) && (boss->fwork[2] == 212.0f)) {
                boss->state = 1;

            } else {
                Math_SmoothStepToF(&boss->fwork[1], 255.0f, 0.3f, 6.0f, 6.0f);
                Math_SmoothStepToF(&boss->fwork[2], 212.0f, 0.3f, 4.98f, 4.98f);
            }
            break;

        case 1:
            if ((boss->fwork[1] == 28.0f) && (boss->fwork[2] == 23.0f)) {
                boss->state = 0;
            } else {
                Math_SmoothStepToF(&boss->fwork[1], 28.0f, 0.3f, 6.0f, 6.0f);
                Math_SmoothStepToF(&boss->fwork[2], 23.0f, 0.3f, 4.98f, 4.98f);
            }
            break;
    }
    func_hud_8008FFF0(boss, gAllRangeEventTimer);
}

bool func_hud_8009092C(Actor* actor) {
    bool var_s5 = false;
    Boss* boss;
    s32 i = 0;

    if (actor->aiIndex != 0) {
        return true;
    }

    boss = &gBosses[1];

    for (i = 1; i < ARRAY_COUNT(gBosses); i++, boss++) {
        if (boss->obj.status == OBJ_ACTIVE) {
            var_s5 = true;
            if (actor->aiIndex == 0) {
                actor->aiIndex = i;
            } else if (Rand_ZeroOne() > 0.4f) {
                actor->aiIndex = i;
            }
            actor->state = 0;
        }
    }

    return var_s5;
}

bool func_hud_80090A00(Actor* actor) {
    switch (actor->iwork[5]) {
        case 0:
            actor->fwork[8] = 0.0f;
            actor->fwork[7] = 360.0f;
            actor->timer_0BC = 8;
            actor->rot_0F4.y = 100.0f;
            actor->rot_0F4.x = 300.0f;
            actor->iwork[4] = 1;
            actor->iwork[5] = 1;

        case 1:
            if (actor->timer_0BC == 0.0f) {
                actor->fwork[1] = 20.0f;
                actor->fwork[3] = 3.6f;
                actor->iwork[2] = 0;
                actor->iwork[3] = 36;
                actor->iwork[5] = 2;
            } else {
                actor->obj.pos.y -= 8.0f;
                break;
            }

        case 2:
            actor->fwork[4] = gBosses[0].obj.pos.x + 1000.0f;
            actor->fwork[5] = 300.0f;
            actor->fwork[6] = actor->obj.pos.z - 10000.0f;
            actor->iwork[2]++;
            if (actor->iwork[2] == actor->iwork[3]) {
                actor->iwork[5] = 3;
                actor->iwork[3] = 40;
                actor->iwork[2] = 0;
            } else if (actor->iwork[2] == 6) {
                actor->iwork[1] = 1;
            }
            break;

        case 3:
            actor->fwork[4] = gBosses[0].obj.pos.x - 1000.0f;
            actor->fwork[5] = 400.0f;
            actor->fwork[6] = gBosses[0].obj.pos.z;
            actor->iwork[2]++;
            if (actor->iwork[2] == actor->iwork[3]) {
                actor->iwork[5] = 4;
            } else if (actor->iwork[2] == 20) {
                actor->fwork[1] = 30.0f;
            }
            break;

        case 4:
            actor->fwork[6] = gPlayer[0].trueZpos;
            actor->fwork[5] = 100.0f;
            actor->fwork[4] = gPlayer[0].pos.x;
            if ((fabsf(actor->obj.pos.x - gPlayer[0].pos.x) < 300.0f) &&
                (fabsf(actor->obj.pos.z - gPlayer[0].trueZpos) < 300.0f)) {
                actor->iwork[5] = 5;
                actor->iwork[3] = 20;
                actor->iwork[2] = 0;
            }
            break;

        case 5:
            actor->fwork[6] = gPlayer[0].trueZpos + 1000.0f;
            actor->fwork[5] = 1000.0f;
            actor->fwork[4] = gPlayer[0].pos.x - 1000.0f;
            actor->iwork[2]++;
            if (actor->iwork[2] == actor->iwork[3]) {
                Object_Kill(&actor->obj, actor->sfxSource);
            }
            break;
    }
    return false;
}

bool func_hud_80090CCC(Actor* actor) {
    bool ret = false;

    if (func_hud_8009092C(actor)) {
        actor->fwork[6] = gBosses[actor->aiIndex].obj.pos.z;
        actor->fwork[5] = gBosses[actor->aiIndex].obj.pos.y;
        actor->fwork[4] = gBosses[actor->aiIndex].obj.pos.x;
    } else {
        actor->fwork[6] = gBosses[0].obj.pos.z;
        actor->fwork[5] = gBosses[0].obj.pos.y;
        actor->fwork[4] = gBosses[0].obj.pos.x;
    }

    if ((fabsf(actor->obj.pos.x - actor->fwork[4]) < 2000.0f) &&
        (fabsf(actor->obj.pos.z - actor->fwork[6]) < 2000.0f)) {
        actor->iwork[6]++;
        if (actor->iwork[6] >= 9) {
            actor->iwork[0] = 1;
            actor->iwork[6] = 0;
        }
    }

    if ((fabsf(actor->obj.pos.x - actor->fwork[4]) < 700.0f) && (fabsf(actor->obj.pos.x - actor->fwork[4]) < 700.0f)) {
        actor->state = 1;
        actor->iwork[6] = 0;
        ret = true;
    }

    if (actor->timer_0BE == 0) {
        actor->timer_0BE = RAND_INT(200.0f) + 200;
        actor->fwork[10] = 30.0f;
    }

    if (gBosses[actor->aiIndex].obj.status == OBJ_FREE) {
        actor->state = 1;
        actor->aiIndex = 0;
        actor->iwork[6] = 0;
        ret = true;
    }

    return ret;
}

s32 func_hud_80090E8C(Actor* actor) {
    f32 x;
    f32 y;
    f32 z;
    f32 var_fv1_2;

    if (actor->timer_0BC == 0) {
        if (gLevelType == LEVELTYPE_SPACE) {
            x = RAND_FLOAT_CENTERED(20000.0f);
            y = RAND_FLOAT_CENTERED(5000.0f);
            z = RAND_FLOAT_CENTERED(20000.0f);
        } else {
            x = RAND_FLOAT_CENTERED(10000.0f);
            y = RAND_FLOAT(1000.0f);
            z = RAND_FLOAT_CENTERED(10000.0f);
        }

        if ((fabsf(actor->obj.pos.x - x) > 2000.0f) && (fabsf(actor->obj.pos.z - z) > 2000.0f)) {
            actor->fwork[4] = x;
            actor->fwork[5] = y;
            actor->fwork[6] = z;
            actor->timer_0BC = RAND_INT(20.0f) + 10;
        }
    }

    if (actor->aiType == AI360_FALCO) {
        var_fv1_2 = 3000.0f;
    } else {
        var_fv1_2 = 5000.0f;
    }

    if ((var_fv1_2 < fabsf(actor->obj.pos.x - gBosses[0].obj.pos.x)) &&
        (var_fv1_2 < fabsf(actor->obj.pos.z - gBosses[0].obj.pos.z))) {
        actor->state = 0;
    }

    if (actor->timer_0BE == 0) {
        actor->timer_0BE = RAND_INT(200.0f) + 200;
        actor->fwork[10] = 30.0f;
    }
    return false;
}

bool func_hud_800910C0(Actor* actor) {
    f32 var_fv1;

    if (actor->timer_0BC == 0) {
        actor->vwork[28].x = RAND_FLOAT_CENTERED(2000.0f);
        actor->vwork[28].y = RAND_FLOAT(1000.0f) + 200.0f;
        actor->vwork[28].z = RAND_FLOAT_CENTERED(2000.0f);
        actor->timer_0BC = RAND_INT(20.0f) + 10;
    }

    actor->fwork[4] = gBosses[0].obj.pos.x + actor->vwork[28].x;
    actor->fwork[5] = actor->vwork[28].y;
    actor->fwork[6] = gBosses[0].obj.pos.z + actor->vwork[28].z;

    if (actor->aiType == AI360_FALCO) {
        var_fv1 = 1500.0f;
    } else {
        var_fv1 = 3000.0f;
    }

    if ((var_fv1 < fabsf(actor->obj.pos.x - actor->fwork[4])) &&
        (var_fv1 < fabsf(actor->obj.pos.z - actor->fwork[6]))) {
        actor->state = 0;
    }

    if (actor->timer_0BE == 0) {
        actor->timer_0BE = RAND_INT(200.0f) + 200;
        actor->fwork[10] = 30.0f;
    }
    return false;
}

void func_hud_80091254(Actor* actor) {
    if (gLevelMode == LEVELMODE_ALL_RANGE) {
        func_hud_80090E8C(actor);
    } else {
        func_hud_800910C0(actor);
    }
}

bool func_hud_80091298(Actor* actor) {
    actor->fwork[1] = gPlayer[0].baseSpeed + 10.0f;
    actor->fwork[3] = 3.6f;
    actor->fwork[4] = gPlayer[0].pos.x + ((f32) (actor->aiType - 2) * 700.0f);
    actor->fwork[5] = gPlayer[0].pos.y;
    actor->fwork[6] = gPlayer[0].trueZpos;

    if ((fabsf(actor->obj.pos.x - actor->fwork[4]) < 700.0f) || (fabsf(actor->obj.pos.z - actor->fwork[6]) < 700.0f)) {
        actor->fwork[1] = gPlayer[0].baseSpeed - 10.0f;
        actor->fwork[3] = 1.2f;
    }
    return false;
}

bool func_hud_80091368(Actor* actor) {
    switch (actor->iwork[5]) {
        case 0:
            actor->fwork[5] = 20000.0f;
            actor->iwork[1] = 1;
            actor->iwork[5] = 1;
            gTeamShields[actor->aiType] = 1;

            switch (actor->aiType) {
                case AI360_FALCO:
                    Radio_PlayMessage(gMsg_ID_20220, RCID_FALCO);
                    break;

                case AI360_PEPPY:
                    Radio_PlayMessage(gMsg_ID_20221, RCID_PEPPY);
                    break;

                case AI360_SLIPPY:
                    Radio_PlayMessage(gMsg_ID_20222, RCID_SLIPPY);
                    break;
            }
            gTeamShields[actor->aiType] = -1;
            break;

        case 1:
            if (actor->fwork[29] < 2.0f) {
                actor->fwork[29] = 2.0f;
            }

            if (actor->timer_0BC == 0) {
                actor->timer_0BC = RAND_INT(20.0f) + 30;
                actor->fwork[7] = 360.0f;
                actor->fwork[8] = 0.0f;
            }

            if (actor->obj.pos.y > 3000.0f) {
                Object_Kill(&actor->obj, actor->sfxSource);
            }
            break;
    }
    return false;
}

void func_hud_800914FC(Actor* actor) {
    switch (actor->state) {
        case 0:
            if (!func_hud_80090CCC(actor)) {
                break;
            }
        case 1:
            func_hud_80091254(actor);
            break;

        case 2:
            func_hud_80091298(actor);
            break;

        case 3:
            func_hud_80091368(actor);
            break;

        case 7:
            func_hud_80090A00(actor);
            break;
    }

    if ((gTeamShields[actor->aiType] <= 0) && (actor->state != 3)) {
        actor->iwork[5] = 0;
        actor->state = 3;
    }

    if (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_LEVEL_COMPLETE) {
        if ((actor->state != 2) && (actor->state != 3)) {
            actor->iwork[4] = 1;
            actor->state = 2;
        }
    }
}

bool func_hud_800915FC(Actor* actor) {
    s32 i;
    f32 y;
    Vec3f vec;
    Boss* boss;
    Scenery360* scenery360;
    bool ret = false;

    Math_Vec3fFromAngles(&vec, 0.0f, actor->rot_0F4.y, 650.0f + actor->fwork[9] * 10.0f);

    if (gLevelMode == LEVELMODE_ALL_RANGE) {
        for (i = 0, scenery360 = &gScenery360[0]; i < 200; i++, scenery360++) {
            if (scenery360->obj.status != OBJ_ACTIVE) {
                continue;
            }

            if (fabsf(scenery360->obj.pos.x - (actor->obj.pos.x + vec.x)) > 1200.0f) {
                continue;
            }

            if (fabsf(scenery360->obj.pos.z - (actor->obj.pos.z + vec.z)) > 1200.0f) {
                continue;
            }

            if (actor->obj.pos.y + vec.y < 650.0f) {
                ret = true;
            }
        }
    }

    if (ret) {
        return true;
    }

    boss = &gBosses[0];

    y = 650.0f;
    if (actor->aiType < AI360_KATT) {
        y = 720.0f;
    }

    if (boss->obj.id == OBJ_BOSS_293) {
        y = 280.0f;
    }

    if (!(fabsf(boss->obj.pos.x - (actor->obj.pos.x + vec.x)) > 1000.0f) &&
        !(fabsf(boss->obj.pos.z - (actor->obj.pos.z + vec.z)) > 1000.0f) &&
        !(fabsf(boss->obj.pos.y - (actor->obj.pos.y)) > y)) {
        ret = true;
    }

    return ret;
}

bool func_hud_80091864(Actor* actor) {
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 x;
    f32 y;
    f32 z;
    f32 sp2C;
    f32 sp28;

    x = actor->fwork[4] - actor->obj.pos.x;
    y = actor->fwork[5] - actor->obj.pos.y;
    z = actor->fwork[6] - actor->obj.pos.z;

    sp40 = Math_RadToDeg(Math_Atan2F(x, z));
    sp44 = Math_RadToDeg(Math_Atan2F(y, sqrtf(SQ(x) + SQ(z))));

    if ((func_hud_800915FC(actor) != 0) && (actor->iwork[4] == 0)) {
        sp44 += 40.0f;
        if (sp44 >= 360.0f) {
            sp44 -= 360.0f;
        } else if ((actor->obj.pos.y < (gGroundHeight + 50.0f)) && (gLevelType == LEVELTYPE_PLANET) &&
                   (sp44 > 180.0f)) {
            sp44 = 0.0f;
        }
        actor->iwork[0] = 0;
    }

    sp3C = Math_SmoothStepToAngle(&actor->rot_0F4.y, sp40, 0.5f, actor->fwork[2], 0.001f) * 30.0f;
    Math_SmoothStepToAngle(&actor->rot_0F4.x, sp44, 0.5f, actor->fwork[2], 0.0001f);
    sp2C = sp28 = 0.0f;

    if (sp3C < 0.0f) {
        sp2C = -sp3C;
    } else {
        sp28 = sp3C;
    }

    Math_SmoothStepToF(&actor->fwork[15], sp2C, 0.2f, 30.0f, 0.00f);
    Math_SmoothStepToF(&actor->fwork[26], -sp2C, 0.2f, 30.0f, 0.00f);
    Math_SmoothStepToF(&actor->fwork[16], sp28, 0.2f, 30.0f, 0.00f);
    Math_SmoothStepToF(&actor->fwork[27], -sp28, 0.2f, 30.0f, 0.00f);

    if (sp3C < 0.0f) {
        sp3C *= -1.0f;
    } else {
        sp3C = 360.0f - sp3C;
    }

    Math_SmoothStepToF(&actor->fwork[7], actor->fwork[8], 0.2f, 30.0f, 0.0001f);

    if ((actor->fwork[7] > 0.01f) && (actor->fwork[7] < 359.9f)) {
        Math_SmoothStepToAngle(&actor->obj.rot.z, actor->fwork[7], 0.2f, 100.0f, 0.01f);
    } else {
        Math_SmoothStepToAngle(&actor->obj.rot.z, sp3C, 0.1f, 3.0f, 0.01f);
    }

    return false;
}

bool func_hud_80091B90(Actor* actor) {
    Vec3f vec;

    actor->obj.rot.x = -actor->rot_0F4.x;
    actor->obj.rot.y = actor->rot_0F4.y;

    Math_SmoothStepToF(&actor->fwork[0], actor->fwork[1], 0.2f, 1.0f, 0.0f);
    Math_SmoothStepToF(&actor->fwork[2], actor->fwork[3], 1.0f, 1.0f, 0.0f);

    Math_Vec3fFromAngles(&vec, actor->obj.rot.x, actor->obj.rot.y, actor->fwork[0] + actor->fwork[9]);

    actor->vel.y = actor->fwork[14] + vec.y;
    actor->vel.x = actor->fwork[13] + vec.x;
    actor->vel.z = actor->fwork[12] + vec.z;

    actor->fwork[13] -= actor->fwork[13] * 0.1f;
    actor->fwork[14] -= actor->fwork[14] * 0.1f;
    actor->fwork[12] -= actor->fwork[12] * 0.1f;

    if ((actor->obj.pos.y < gGroundHeight + 40.0f) && (actor->vel.y < 0.0f) && (gLevelType == LEVELTYPE_PLANET)) {
        actor->obj.pos.y = gGroundHeight + 40.0f;
        actor->vel.y = 0.0f;
    }
    actor->vel.z -= gPathVelZ;

    return false;
}

bool func_hud_80091CF8(Actor* actor) {
    if (actor->iwork[1] != 0) {
        if (actor->fwork[10] < 0.1f) {
            actor->fwork[10] = 20.0f;
            AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, actor->sfxSource, 0);
            actor->fwork[29] = 5.0f;
        }
        actor->iwork[1] = 0;
    }

    Math_SmoothStepToF(&actor->fwork[10], 0.0f, 0.1f, 0.2f, 0.0f);
    Math_SmoothStepToF(&actor->fwork[9], actor->fwork[10], 0.1f, 2.0f, 0.0f);

    if (actor->fwork[10] < 0.1f) {
        actor->iwork[11] = 1;
    }
    return false;
}

bool func_hud_80091DF4(Actor* actor) {
    Vec3f sp44;
    Vec3f sp38;

    if ((actor->iwork[0] != 0) && (gBossHealthBar > 70)) {
        actor->iwork[0] = 0;
        sp44.x = 0.0f;
        sp44.y = 0.0f;
        sp44.z = 100.0f;
        Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp44, &sp38);
        Actor_SpawnPlayerLaser(actor->aiType, actor->obj.pos.x + (sp38.x * 1.5), actor->obj.pos.y + (sp38.y * 1.5),
                               actor->obj.pos.z + (sp38.z * 1.5), sp38.x, sp38.y, sp38.z, actor->obj.rot.x,
                               actor->obj.rot.y, actor->obj.rot.z);
    }
    return false;
}

bool func_hud_80091F00(Actor* actor) {
    u8 temp_v0 = actor->dmgType;
    Vec3f sp40;
    Vec3f sp34;

    actor->dmgType = DMG_NONE;

    if ((actor->state == 3) || (temp_v0 == DMG_EXPLOSION)) {
        return false;
    }

    actor->health -= actor->damage;
    if (actor->health <= 0) {
        actor->health = -1;
    }
    actor->timer_0C6 = 20;

    AUDIO_PLAY_SFX(NA_SE_EN_DAMAGE_S, actor->sfxSource, 4);
    func_effect_8007D10C(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, 1.5f);
    Matrix_RotateY(gCalcMatrix, actor->rot_0F4.y * M_DTOR, MTXF_NEW);

    if (Rand_ZeroOne() < 0.5f) {
        sp40.x = -20.0f;
    } else {
        sp40.x = 20.0f;
    }

    sp40.y = RAND_FLOAT_CENTERED(20.0f);
    sp40.z = 0.0f;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp40, &sp34);

    actor->fwork[13] = sp34.x;
    actor->fwork[14] = sp34.y;
    actor->fwork[12] = sp34.z;

    gTeamShields[actor->aiType] = actor->health;

    if (gRadioState != 0) {
        return false;
    }

    if ((actor->dmgType == DMG_COLLISION) && (actor->dmgSource == AI360_FOX + 1)) {
        switch (actor->aiType) {
            case AI360_FALCO:
                Radio_PlayMessage(gMsg_ID_20210, RCID_FALCO);
                break;
            case AI360_PEPPY:
                Radio_PlayMessage(gMsg_ID_20200, RCID_PEPPY);
                break;
            case AI360_SLIPPY:
                Radio_PlayMessage(gMsg_ID_20190, RCID_SLIPPY);
                break;
        }
    }

    if ((actor->dmgType != DMG_COLLISION) && (actor->dmgSource == AI360_FOX + 1)) {
        switch (actor->aiType) {
            case AI360_FALCO:
                Radio_PlayMessage(gMsg_ID_20060, RCID_FALCO);
                break;
            case AI360_PEPPY:
                Radio_PlayMessage(gMsg_ID_20070, RCID_PEPPY);
                break;
            case AI360_SLIPPY:
                Radio_PlayMessage(gMsg_ID_20080, RCID_SLIPPY);
                break;
        }
    }

    if ((actor->dmgSource == DMG_SRC_2) || (actor->dmgSource == DMG_SRC_100)) {
        switch (actor->aiType) {
            case AI360_FALCO:
                Radio_PlayMessage(gMsg_ID_20030, RCID_FALCO);
                break;
            case AI360_PEPPY:
                Radio_PlayMessage(gMsg_ID_20040, RCID_PEPPY);
                break;
            case AI360_SLIPPY:
                Radio_PlayMessage(gMsg_ID_20050, RCID_SLIPPY);
                break;
        }
    }
    actor->iwork[8] = 20;

    return false;
}

void func_hud_80092244(Actor* actor) {
    gRadarMarks[actor->index].status = 1;
    gRadarMarks[actor->index].type = actor->aiType;
    gRadarMarks[actor->index].pos.x = actor->obj.pos.x;
    gRadarMarks[actor->index].pos.y = actor->obj.pos.y;
    gRadarMarks[actor->index].pos.z = actor->obj.pos.z;
    gRadarMarks[actor->index].yRot = actor->rot_0F4.y + 180.0f;
}

void func_hud_800922F4(Actor* actor) {
    s32 temp;

    if ((gTeamShields[actor->aiType] < 64) && (gPlayer[0].state_1C8 != PLAYERSTATE_1C8_LEVEL_COMPLETE)) {
        temp = 8 - 1;
        if (gTeamShields[actor->aiType] > 16) {
            temp = 16 - 1;
        }
        if (gTeamShields[actor->aiType] > 32) {
            temp = 32 - 1;
        }
        if (gTeamShields[actor->aiType] > 48) {
            temp = 64 - 1;
        }

        if ((gGameFrameCount & temp) == 0) {
            func_effect_8007D10C(actor->obj.pos.x + RAND_FLOAT_CENTERED(10.0f), actor->obj.pos.y + RAND_FLOAT(10.0f),
                                 actor->obj.pos.z + RAND_FLOAT_CENTERED(10.0f), 2.2f);
        }

        if (!(gGameFrameCount & (temp >> 2)) && (Rand_ZeroOne() < 0.5f)) {
            func_effect_8007C120(actor->obj.pos.x + RAND_FLOAT_CENTERED(30.0f), actor->obj.pos.y + RAND_FLOAT(10.0f),
                                 actor->obj.pos.z + RAND_FLOAT_CENTERED(30.0f), actor->vel.x, actor->vel.y,
                                 actor->vel.z, actor->scale * 0.07f, 3);
        }
    }
}

bool func_hud_800924E0(Actor* actor) {
    Vec3f src;
    Vec3f dest;
    f32 var_fv0;
    bool ret = false;

    if (actor->iwork[7] == 0) {
        actor->vwork[29].x = actor->obj.rot.x;
        actor->iwork[7] = 1;
        actor->iwork[1] = 1;
    }

    if (actor->fwork[29] < 2.0f) {
        actor->fwork[29] = 2.0f;
    }

    var_fv0 = 60.0f;

    if (actor->fwork[19] > 240.0f) {
        var_fv0 = -50.0f;
    }

    Math_SmoothStepToF(&actor->fwork[15], var_fv0, 0.3f, 100.0f, 0.0f);
    Math_SmoothStepToF(&actor->fwork[26], var_fv0, 0.3f, 100.0f, 0.0f);
    Math_SmoothStepToF(&actor->fwork[16], var_fv0, 0.3f, 100.0f, 0.0f);
    Math_SmoothStepToF(&actor->fwork[27], var_fv0, 0.3f, 100.0f, 0.0f);

    if (actor->fwork[19] < 180.0f) {
        actor->obj.pos.y += 2.0f;
    }

    if (Math_SmoothStepToF(&actor->fwork[19], 360.0f, 0.1f, 5.0f, 0.01f) == 0.0f) {
        actor->obj.rot.x = actor->vwork[29].x;
        actor->fwork[19] = actor->vwork[29].x = 0.0f;
        ret = true;
        actor->iwork[7] = 0;
        actor->fwork[29] = 1.0f;
    }

    if (actor->iwork[7] != 0) {
        Math_SmoothStepToAngle(&actor->vwork[29].x, 0.0f, 0.1f, 5.0f, 0.0f);
        Math_SmoothStepToAngle(&actor->obj.rot.z, 0.0f, 0.1f, 5.0f, 0.0f);
        actor->obj.rot.x = actor->vwork[29].x + (360.0f - actor->fwork[19]);

        Matrix_RotateY(gCalcMatrix, actor->rot_0F4.y * M_DTOR, MTXF_NEW);
        Matrix_RotateX(gCalcMatrix, -(M_DTOR * ((actor->rot_0F4.x + actor->vwork[29].x) + actor->fwork[19])),
                       MTXF_APPLY);

        src.z = actor->fwork[1];
        src.y = 0.0f;
        src.x = 0.0f;

        Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

        actor->vel.x = dest.x;
        actor->vel.y = dest.y;
        actor->vel.z = dest.z;

        if (actor->obj.pos.y < gGroundHeight + 50.0f) {
            actor->obj.pos.y = gGroundHeight + 50.0f;
            actor->vel.y = 0.0f;
        }
    }

    return ret;
}

bool func_hud_800927A0(Actor* actor) {
    Vec3f src;
    Vec3f dest;
    f32 sp54;
    f32 sp50;
    bool ret = false;

    if (actor->iwork[11] == 0) {
        actor->unk_046 = 0;
        actor->iwork[11] = 1;
        actor->iwork[1] = 1;
        actor->vwork[29].x = actor->obj.rot.x;
        actor->vwork[29].y = actor->obj.rot.y;
        actor->vwork[29].z = actor->obj.rot.z;
    } else {
        Math_SmoothStepToAngle(&actor->vwork[29].z, 0.0f, 0.1f, 5.0f, 0.0f);
        Math_SmoothStepToAngle(&actor->vwork[29].y, 0.0f, 0.1f, 5.0f, 0.0f);
        Math_SmoothStepToAngle(&actor->vwork[29].x, 0.0f, 0.1f, 5.0f, 0.0f);
        sp50 = Math_RadToDeg(Math_Atan2F(0.0f - actor->obj.pos.x, 0.0f - actor->obj.pos.z));

        switch (actor->unk_046) {
            case 0:
                if (actor->unk_04A != 0) {
                    actor->timer_0BC = 30;
                } else {
                    actor->timer_0BC = 10;
                }
                actor->unk_046 = 1;
                if (actor->fwork[19] > 180.0f) {
                    actor->fwork[19] = actor->fwork[19] - 360.0f;
                }

            case 1:
                if (actor->timer_0BC == 0) {
                    actor->unk_046 = 2;
                    if (actor->unk_04A != 0) {
                        actor->timer_0BC = 80;
                    } else {
                        actor->timer_0BC = 60;
                    }
                    Math_SmoothStepToF(&actor->fwork[20], 0.0f, 0.1f, 15.0f, 0.0f);
                }
                break;

            case 2:
                if (actor->fwork[19] > 140.0f) {
                    sp54 = 0.0f;
                } else {
                    sp54 = 60.0f;
                }

                Math_SmoothStepToF(&actor->fwork[15], sp54, 0.3f, 100.0f, 0.0f);
                Math_SmoothStepToF(&actor->fwork[26], sp54, 0.3f, 100.0f, 0.0f);
                Math_SmoothStepToF(&actor->fwork[16], sp54, 0.3f, 100.0f, 0.0f);
                Math_SmoothStepToF(&actor->fwork[27], sp54, 0.3f, 100.0f, 0.0f);
                Math_SmoothStepToF(&actor->fwork[19], 190.0f, 0.1f, 6.0f, 0.001f);
                Math_SmoothStepToF(&actor->fwork[20], 0.0f, 0.1f, 15.0f, 0.0f);

                if (actor->fwork[19] > 180.0f) {
                    actor->rot_0F4.y += 180.0f;
                    if (actor->rot_0F4.y >= 360.0f) {
                        actor->rot_0F4.y = actor->rot_0F4.y - 360.0f;
                    }

                    actor->fwork[19] -= 180.0f;

                    if ((sp50 - actor->rot_0F4.y) < 180.0f) {
                        actor->fwork[20] = 180.0f;
                    } else {
                        actor->fwork[20] = -180.0f;
                    }
                    actor->iwork[1] = 1;
                    actor->unk_046 = 3;
                }
                actor->fwork[28] -= 0.2f;
                break;

            case 3:
                if (actor->fwork[29] < 2.0f) {
                    actor->fwork[29] = 2.0f;
                }
                Math_SmoothStepToF(&actor->fwork[20], 0.0f, 0.1f, 15.0f, 0.0f);

                sp54 = actor->fwork[20] * 0.3f;

                Math_SmoothStepToF(&actor->fwork[15], sp54, 0.3f, 100.0f, 0.0f);
                Math_SmoothStepToF(&actor->fwork[26], sp54, 0.3f, 100.0f, 0.0f);
                Math_SmoothStepToF(&actor->fwork[16], -sp54, 0.3f, 100.0f, 0.0f);
                Math_SmoothStepToF(&actor->fwork[27], -sp54, 0.3f, 100.0f, 0.0f);

                if (actor->unk_04A != 0) {
                    Math_SmoothStepToAngle(&actor->rot_0F4.y, sp50, 0.1f, 2.0f, 0.0f);
                }

                if (actor->obj.pos.y < gPlayer[0].pathHeight) {
                    if (actor->fwork[28] < 0.0f) {
                        actor->fwork[28] = actor->fwork[28] + 0.2f;
                    }
                } else {
                    actor->fwork[28] -= 0.2f;
                }

                if (actor->timer_0BC == 0) {
                    ret = true;
                    actor->iwork[11] = 0;
                    actor->unk_046 = 0;
                    actor->fwork[28] = 0.0f;
                    actor->fwork[20] = 0.0f;
                    actor->fwork[29] = 1.0f;
                }
                break;
        }

        actor->obj.rot.x = actor->vwork[29].x - actor->fwork[19];
        actor->obj.rot.y = actor->rot_0F4.y;
        actor->obj.rot.z = actor->vwork[29].z + actor->fwork[20];
        actor->obj.pos.y += actor->fwork[28];

        Matrix_RotateY(gCalcMatrix, actor->rot_0F4.y * M_DTOR, 0U);
        Matrix_RotateX(gCalcMatrix, -(M_DTOR * (actor->rot_0F4.x + actor->vwork[29].x + actor->fwork[19])), MTXF_APPLY);

        src.z = actor->fwork[1];
        src.y = 0.0f;
        src.x = 0.0f;

        Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

        actor->vel.x = dest.x;
        actor->vel.y = dest.y;
        actor->vel.z = dest.z;
    }
    return ret;
}

void ActorTeamBoss_Init(Actor* actor) {
    s32 D_800D22A8[] = { TEAM_ID_FALCO, TEAM_ID_SLIPPY, TEAM_ID_PEPPY };

    if (gCurrentLevel != LEVEL_TITANIA) {
        actor->fwork[1] = 40.0f;
        actor->fwork[3] = 1.2f;
        actor->aiType = (D_hud_800D1970 % 4U) + 1;
        D_hud_800D1970++;
    } else {
        actor->state = 7;
        actor->aiType = AI360_SLIPPY;
        actor->iwork[5] = 0;
        gTeamShields[TEAM_ID_SLIPPY] = 255;
    }

    actor->iwork[12] = D_800D22A8[actor->aiType - 1];
    actor->iwork[11] = 1;

    if (gLevelType == LEVELTYPE_PLANET) {
        actor->drawShadow = true;
    }

    AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, actor->sfxSource, 4);

    if (((s32) (D_hud_800D1970 % 4U) == AI360_SLIPPY) && (gCurrentLevel == LEVEL_SECTOR_X)) {
        Object_Kill(&actor->obj, actor->sfxSource);
    }

    if (gTeamShields[actor->aiType] <= 0) {
        Object_Kill(&actor->obj, actor->sfxSource);
    }
}

void ActorTeamBoss_Update(ActorTeamBoss* this) {
    f32 var_fv1;

    this->health = gTeamShields[this->aiType];

    switch (this->unk_048) {
        case 0:
            func_hud_800914FC(this);
            func_hud_80091864(this);
            func_hud_80091B90(this);
            func_hud_80091DF4(this);

            if (this->dmgType != DMG_NONE) {
                func_hud_80091F00(this);
            }

            if (this->state == 3) {
                break;
            }

            switch (gCurrentLevel) {
                case LEVEL_SECTOR_Z:
                    var_fv1 = 20000.0f;
                    break;

                case LEVEL_CORNERIA:
                    var_fv1 = 8000.0f;
                    break;

                case LEVEL_BOLSE:
                    var_fv1 = 10000.0f;
                    break;

                default:
                    var_fv1 = 12500.0f;
                    break;
            }

            if ((this->iwork[10] != 0) && (gLevelMode == LEVELMODE_ALL_RANGE) && (this->iwork[9] == 0) &&
                (gPlayer[0].state_1C8 != PLAYERSTATE_1C8_LEVEL_COMPLETE)) {
                this->unk_048 = 2;
                this->unk_04A = 0;
            }

            if ((gLevelMode == LEVELMODE_ALL_RANGE) &&
                (fabsf(this->obj.pos.x > var_fv1) || fabsf(this->obj.pos.z > var_fv1)) &&
                (gPlayer[0].state_1C8 != PLAYERSTATE_1C8_LEVEL_COMPLETE)) {
                this->unk_048 = 2;
                this->unk_04A = 1;
            }
            break;

        case 1:
            if (func_hud_800924E0(this) != 0) {
                this->unk_048 = 0;
                this->iwork[9] = RAND_INT(30.0f) + 90;
            }
            break;

        case 2:
            if (func_hud_800927A0(this) != 0) {
                this->unk_04A = 0;
                this->unk_048 = this->unk_04A;
                this->iwork[9] = RAND_INT(30.0f) + 90;
            }
            break;
    }

    func_hud_80091CF8(this);
    func_hud_800922F4(this);
    func_hud_80092244(this);

    if (this->iwork[9] != 0) {
        this->iwork[9]--;
    }
    this->iwork[10] = 0;
}

void func_hud_80093164(Actor* actor) {
    Vec3f src;
    Vec3f dest;
    Player* player = &gPlayer[0];

    if (actor->state == 0) {
        switch (actor->animFrame) {
            case 1:
                if ((player->state_1C8 != PLAYERSTATE_1C8_LEVEL_INTRO) || (actor->animFrame != 1)) {
                    if (gCsFrameCount > 1588) {
                        actor->fwork[0] = 5.0f;
                    } else {
                        actor->fwork[0] = 15.0f;
                    }
                    actor->fwork[0] = 12.0f;
                }
                break;

            case 41:
                Aquas_801BE034(actor);
                break;

            case 44:
                actor->iwork[0]++;
                if (actor->iwork[0] > 118) {
                    actor->iwork[0] = 0;
                }
                break;
        }
    }

    Matrix_RotateY(gCalcMatrix, (actor->rot_0F4.y + 180.0f) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -(actor->rot_0F4.x * M_DTOR), MTXF_APPLY);
    src.x = 0.0f;
    src.y = 0.0f;
    src.z = actor->fwork[0];
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);
    actor->vel.x = dest.x;
    actor->vel.y = dest.y;
    actor->vel.z = dest.z;
    actor->obj.rot.x = -actor->rot_0F4.x;
    actor->obj.rot.y = actor->rot_0F4.y + 180.0f;
    actor->obj.rot.z = -actor->rot_0F4.z;
}

void func_hud_80093310(void) {
    Actor* this = &gActors[0];

    Actor_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.pos.x = 0.0f;
    this->obj.pos.y += 1700.0f;
    this->obj.pos.z -= 5000.0f;
    gActors[0].animFrame = 1;
    if (1) {}
    this->obj.id = OBJ_ACTOR_CUTSCENE;
    Object_SetInfo(&this->info, this->obj.id);
    AUDIO_PLAY_SFX(NA_SE_GREATFOX_ENGINE, this->sfxSource, 0);
}

void func_hud_800933D8(f32 x, f32 y, f32 z, f32 arg3) {
    s32 i;
    Effect* effect = &gEffects[ARRAY_COUNT(gEffects) - 1];
    Player* player = gPlayer;

    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        if (effect->obj.status == OBJ_FREE) {
            Effect_Initialize(effect);
            effect->obj.status = OBJ_INIT;
            effect->obj.id = OBJ_EFFECT_363;
            effect->obj.pos.x = x;
            effect->obj.pos.y = y;
            effect->obj.pos.z = z;

            if ((player->state_1C8 == PLAYERSTATE_1C8_LEVEL_INTRO) && (gCurrentLevel == LEVEL_AQUAS) &&
                (player->csState < 2)) {
                effect->scale1 = 0.4f;
                effect->unk_44 = 0;
                effect->unk_46 = 24;
                effect->unk_48 = RAND_INT(4.0f);
                if (Rand_ZeroOne() < 0.5f) {
                    effect->unk_48 = -effect->unk_48;
                }
            } else {
                effect->vel.x = RAND_FLOAT_CENTERED(5.0f);
                effect->vel.y = RAND_FLOAT_CENTERED(3.0f);
                effect->unk_48 = 0;

                if (Rand_ZeroOne() < 0.5f) {
                    effect->unk_48 = -effect->unk_48;
                }

                if (player->csState >= 5) {
                    effect->unk_4A = 96;
                    effect->unk_46 = 4;
                } else {
                    effect->unk_4A = 128;
                    effect->unk_46 = 2;
                }
            }

            effect->scale2 = arg3 * 0.2f;
            effect->obj.rot.z = RAND_FLOAT(360.0f);
            Object_SetInfo(&effect->info, effect->obj.id);
            break;
        }
        effect--;
    }
}

f32 D_800D22B4 = -100.0f;
f32 D_800D22B8 = 0.01f;
f32 D_800D22BC = 0.04f;
f32 D_800D22C0 = 0.05f;
f32 D_800D22C4 = 260.0f;
f32 D_800D22C8 = 260.0f;
f32 D_800D22CC = 260.0f;
s32 D_800D22D0 = 50;
s32 D_800D22D4 = 2;

void HUD_AquasStart(Player* player) {
    Vec3f D_800D22D8[] = { { -1730.0f, 1600.0f, -6690.0f },
                           { -830.0f, 1600.0f, -7380.0f },
                           { 0.0f, 1600.0f, -7380.0f } };
    Vec3f D_800D22FC[] = { { 0.0f, 0.0f, 0.0f }, { 190.0f, 2570.0f, -4740.0f }, { 0.0f, 0.0f, 0.0f } };
    Vec3f D_800D2320[] = { { 50.0f, -165.0f, -900.0f },   { -100.0f, -165.0f, -900.0f }, { -100.0f, -165.0f, -850.0f },
                           { -200.0f, -165.0f, -800.0f }, { -200.0f, -165.0f, -750.0f }, { -240.0f, -165.0f, -700.0f },
                           { -240.0f, -165.0f, -650.0f }, { -280.0f, -165.0f, -600.0f }, { -280.0f, -165.0f, -550.0f },
                           { -320.0f, -165.0f, -500.0f }, { -320.0f, -165.0f, -450.0f }, { -360.0f, -165.0f, -400.0f },
                           { -360.0f, -165.0f, -350.0f }, { -400.0f, -165.0f, -300.0f }, { -400.0f, -165.0f, -250.0f },
                           { -440.0f, -165.0f, -200.0f }, { -440.0f, -165.0f, -150.0f }, { -480.0f, -165.0f, -100.0f },
                           { -480.0f, -165.0f, -50.0f },  { -520.0f, -165.0f, 0.0f },    { -520.0f, -165.0f, 50.0f },
                           { -560.0f, -165.0f, 100.0f },  { -560.0f, -165.0f, 150.0f },  { -600.0f, -165.0f, 200.0f },
                           { -600.0f, -165.0f, 250.0f },  { -640.0f, -165.0f, 300.0f },  { -640.0f, -165.0f, 350.0f },
                           { -680.0f, -165.0f, 400.0f },  { -680.0f, -165.0f, 450.0f },  { -720.0f, -165.0f, 500.0f },
                           { -720.0f, -165.0f, 550.0f },  { -50.0f, -165.0f, -900.0f } };
    Vec3f src, dest;
    f32 x;
    f32 y;
    f32 z;
    f32 stepSize;
    f32 temp2;
    f32 temp;
    s32 i;
    s32 j;
    Actor* actor;

    actor = &gActors[0];

    switch (player->csState) {

        case 0:
            func_hud_80093310();
            gCsFrameCount = 0;
            gDrawBackdrop = 1;
            gAqDrawMode = 1;
            player->unk_234 = 0;
            player->csState = 1;
            player->unk_208 = 0;
            player->baseSpeed = 0.0f;

            gFillScreenAlpha = 255;
            gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
            gFillScreenAlphaTarget = 0;

            player->cam.eye.x = gCsCamEyeX = -3061.2f;
            player->cam.eye.y = gCsCamEyeY = 1745.9f;
            player->cam.eye.z = gCsCamEyeZ = -5786.0f;

            player->cam.at.x = gCsCamAtX = 300.0f;
            player->cam.at.y = gCsCamAtY = 2200.0f;
            player->cam.at.z = gCsCamAtZ = -5700.0f;

            D_801616A0.x = 5.18f;
            D_801616A0.y = 124.17f;
            D_801616A0.z = 0.00f;

            actor->rot_0F4.y = 30.0f;

            D_ctx_80177A48[5] = 14.0f;
            D_ctx_80177A48[0] = 0.2f;
            D_ctx_80177A10[6] = 0;
            D_ctx_80177A10[7] = 0;
            D_801616B0.x = D_801616B0.y = D_801616B0.z = 0.0f;
            D_ctx_80177A48[7] = 0.0f;

        case 1:
            if ((player->unk_208 == 0) && (gCsFrameCount < 250)) {
                i = RAND_INT(64.0f);
                if (i < 32) {
                    for (j = 0; j < 4; j++) {
                        src.x = D_800D2320[i].x;
                        src.y = D_800D2320[i].y + RAND_FLOAT(12.0f);
                        src.z = D_800D2320[i].z;

                        Matrix_Translate(gCalcMatrix, actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, MTXF_NEW);
                        Matrix_RotateY(gCalcMatrix, M_DTOR * 30.0f, MTXF_APPLY);
                        Matrix_MultVec3f(gCalcMatrix, &src, &dest);

                        x = dest.x;
                        y = dest.y;
                        z = dest.z;

                        func_hud_800933D8(x, y, z, 20.0f);

                        i = (i + 1) % 32;
                    }
                } else {
                    i -= 32;
                    for (j = 0; j < 4; j++) {
                        src.x = -D_800D2320[i].x;
                        src.y = D_800D2320[i].y + RAND_FLOAT(12.0f);
                        src.z = D_800D2320[i].z;

                        Matrix_Translate(gCalcMatrix, actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, MTXF_NEW);
                        Matrix_RotateY(gCalcMatrix, M_DTOR * 30.0f, MTXF_APPLY);
                        Matrix_MultVec3f(gCalcMatrix, &src, &dest);

                        x = dest.x;
                        y = dest.y;
                        z = dest.z;

                        func_hud_800933D8(x, y, z, 20.0f);

                        i = (i + 1) % 32;
                    }
                }
                player->unk_208 = RAND_INT(3.0f) + 1;
            } else {
                player->unk_208--;
            }

            if (D_ctx_80177A10[6] < 3) {
                i = D_ctx_80177A10[6];
                stepSize = D_ctx_80177A48[5];

                src.x = gCsCamEyeX;
                src.y = gCsCamEyeY;
                src.z = gCsCamEyeZ;

                dest.x = D_800D22D8[i].x;
                dest.y = D_800D22D8[i].y;
                dest.z = D_800D22D8[i].z;

                if (Math_PursueVec3f(&src, &dest, &D_801616A0, stepSize, 0.4f, 4.8f, stepSize)) {
                    if (D_ctx_80177A10[6] == 0) {
                        D_ctx_80177A10[7]++;
                    }
                    D_ctx_80177A10[6]++;
                }
                gCsCamEyeX = src.x;
                gCsCamEyeY = src.y;
                gCsCamEyeZ = src.z;
            }

            if (D_ctx_80177A10[7] == 1) {
                i = D_ctx_80177A10[7];
                stepSize = D_ctx_80177A48[5];

                src.x = gCsCamAtX;
                src.y = gCsCamAtY;
                src.z = gCsCamAtZ;

                dest.x = D_800D22FC[i].x;
                dest.y = D_800D22FC[i].y;
                dest.z = D_800D22FC[i].z;

                if (D_ctx_80177A10[6] <= D_ctx_80177A10[7]) {
                    if (Math_PursueVec3f(&src, &dest, &D_801616B0, stepSize, 0.4f, 4.8f, stepSize)) {
                        D_ctx_80177A10[7]++;
                    }
                }

                gCsCamAtX = src.x;
                gCsCamAtY = src.y;
                gCsCamAtZ = src.z;
            }

            if (gCsFrameCount >= 50) {
                // clang-format off
	        if (gFillScreenAlpha == 255) { player->csState = 2; }
                // clang-format on
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
                gFillScreenAlphaTarget = 255;
                Math_SmoothStepToF(&D_ctx_80177A48[7], 16.0f, 0.04f, 0.05f, 0.0f);
                gFillScreenAlphaStep = D_ctx_80177A48[7];
            }
            break;

        case 2:
            gPlayerGlareAlphas[0] = 0;

            D_ctx_80177A10[0] = gLight1R;
            D_ctx_80177A10[1] = gLight1G;
            D_ctx_80177A10[2] = gLight1B;
            D_ctx_80177A10[3] = gAmbientR;
            D_ctx_80177A10[4] = gAmbientG;
            D_ctx_80177A10[5] = gAmbientB;

            gLight1R = 40;
            gLight1G = 100;
            gLight1B = 120;

            gAmbientR = 20;
            gAmbientG = 30;
            gAmbientB = 50;

            D_ctx_80177A48[2] = 0.0f;
            D_ctx_80177A48[3] = -1600.0f;
            D_ctx_80177A48[4] = 520.0f;

            player->csState = 3;

            gDrawBackdrop = 0;

            player->camRoll = 60.0f;
            player->csTimer = 1000;

            player->rot.y = 30.0f;

            player->pos.z = -5100.0f;
            player->pos.x = -50.0f;
            player->pos.y = 1200.0f;

            gFillScreenAlphaTarget = 0;

            Aquas_801BDF14();

            AUDIO_PLAY_BGM(NA_BGM_START_DEMO_M);

        case 3:
            gFillScreenAlphaStep = 16;

            if (player->csTimer > 774) {
                if (D_ctx_80177A48[4] >= 200.0f) {
                    Math_SmoothStepToF(&D_ctx_80177A48[4], -200.0f, 1.00f, 4.0f, 4.0f);
                } else {
                    Math_SmoothStepToF(&D_ctx_80177A48[4], -200.0f, 0.06f, 4.0f, 0.0f);
                }

                src.x = D_ctx_80177A48[2];
                src.y = D_ctx_80177A48[3];
                src.z = D_ctx_80177A48[4];

                Matrix_Translate(gCalcMatrix, actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, MTXF_NEW);
                Matrix_RotateY(gCalcMatrix, M_DTOR * 30.0f, MTXF_APPLY);
                Matrix_MultVec3f(gCalcMatrix, &src, &dest);

                gCsCamEyeX = dest.x;
                gCsCamEyeY = dest.y;
                gCsCamEyeZ = dest.z;

                player->cam.at.x = gCsCamAtX = gCsCamEyeX;
                player->cam.at.y = gCsCamAtY = gCsCamEyeY + 100.0f;
                player->cam.at.z = gCsCamAtZ = gCsCamEyeZ + 10.0f;

                player->cam.eye.x = gCsCamEyeX;
                player->cam.eye.y = gCsCamEyeY;
                player->cam.eye.z = gCsCamEyeZ;
            }

            if (player->csTimer == 774) {
                AUDIO_PLAY_SFX(NA_SE_MAR_LAUNCH, player->sfxSource, 0);
                D_ctx_80177A10[9] = 40;
            }

            if (player->csTimer <= 774) {
                D_ctx_80177A48[0] = 0.0f;
                temp2 = 0.0f;

                if (D_ctx_80177A10[9] != 0) {
                    D_ctx_80177A10[9]--;
                    temp = D_ctx_80177A10[9];
                    if (temp > 20.0f) {
                        temp = 20.0f;
                    }
                    temp2 = SIN_DEG(gGameFrameCount * 70.0f) * temp;
                }

                player->cam.eye.y = gCsCamEyeY + temp2;
                player->cam.at.y = gCsCamEyeY + 100.0f;

                Math_SmoothStepToF(&player->unk_018, -1200.0f, 0.02f, 60.0f, 0.0f);

                src.x = 0.0f;
                src.y = 0.0f;
                src.z = player->unk_018;

                Matrix_Translate(gCalcMatrix, player->pos.x, player->pos.y, player->pos.z, MTXF_NEW);
                Matrix_RotateY(gCalcMatrix, M_DTOR * 30.0f, MTXF_APPLY);
                Matrix_MultVec3f(gCalcMatrix, &src, &dest);

                player->pos.x = dest.x;
                player->pos.y = dest.y;
                player->pos.z = dest.z;

                if (((player->csTimer % 8) == 0) && (player->csTimer > 740)) {
                    func_effect_8007D9DC(player->cam.eye.x, 1600.0f, player->cam.eye.z, 10.0f, 100.0f, 0);
                }

                if ((player->unk_018 > -200.0f) && (D_ctx_80177A10[8] < 6)) {
                    if (D_ctx_80177A10[8] < 2) {
                        func_hud_800933D8(player->pos.x, player->pos.y - 400.0f, player->pos.z, 20.0f);
                    }
                    if (D_ctx_80177A10[8] >= 2) {
                        func_hud_800933D8(player->pos.x, player->pos.y, player->pos.z, 10.0f);
                    }
                    D_ctx_80177A10[8]++;
                }

                if (((gGameFrameCount % 3) == 0) && (player->csTimer <= 740)) {
                    for (i = 0; i < 8; i++) {
                        Aquas_801AC8A8(player->cam.eye.x + RAND_FLOAT_CENTERED(D_800D22C4),
                                       player->cam.eye.y + 260.0f + RAND_FLOAT_CENTERED(D_800D22C8),
                                       player->cam.eye.z + RAND_FLOAT_CENTERED(D_800D22CC), 1.0f, 0);
                    }
                }
            }

            if (player->csTimer < 736) {
                player->csState = 4;
                gAqDrawMode = 1;
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
                gFillScreenAlphaTarget = 255;
            }
            break;

        case 4:
            if (gFillScreenAlpha == 255) {
                player->csState = 5;
            }
            break;

        case 5:
            player->pos.x = 0.0f;
            player->pos.y = 350.0f;
            player->pos.z = 0.0f;

            player->cam.eye.x = player->pos.x * (600.0f / player->pathWidth);
            player->cam.eye.y = player->pos.y * (1040.0f / player->pathHeight);
            player->cam.eye.y -= 50.0f;

            player->cam.at.x = player->pos.x * (600.0f / player->pathWidth);
            player->cam.at.y = player->pos.y * (1050.0f / player->pathHeight);
            player->cam.at.y += player->xRock * 10.0f;

            player->pos.z += 1000.0f;
            player->camRoll = 0.0f;

            D_ctx_80177A48[0] = 0.1f;

            player->rot.y = 0.0f;
            player->baseSpeed = 20.0f;
            player->unk_234 = 1;
            player->csState = 6;

            player->csTimer = 1000;

            gAqDrawMode = 0;
            gFillScreenAlphaTarget = 0;

            Object_Kill(&actor->obj, actor->sfxSource);

            player->cam.eye.z = gCsCamEyeZ = 800.0f;
            player->cam.at.z = gCsCamAtZ = 0.0f;

        case 6:
            player->xRock = SIN_DEG(player->rockPhase * 0.7f) * 0.5f;
            player->bobPhase += 10.0f;
            player->rockPhase += 8.0f;
            player->yBob = -SIN_DEG(player->bobPhase) * 0.5f;
            player->rockAngle = SIN_DEG(player->rockPhase) * 1.5f;

            gCsCamEyeX = player->pos.x * (600.0f / player->pathWidth);
            gCsCamEyeY = player->pos.y * (740.0f / player->pathHeight);
            gCsCamEyeY -= -50.0f;

            gCsCamAtX = player->pos.x * (600.0f / player->pathWidth);
            gCsCamAtY = player->pos.y * (750.0f / player->pathHeight);
            gCsCamAtY += player->xRock * 10.0f;

            Math_SmoothStepToF(&player->pos.z, 0.0f, 0.1f, 40.0f, 0.1f);

            D_ctx_80177A48[0] = 0.03f;
            gCsCamEyeZ = 240.0f;
            gCsCamAtZ = player->pos.z + (gPathProgress - 1.0f);

            if (((player->csTimer % 2) == 0) && (player->csTimer > 962)) {
                func_hud_800933D8(player->pos.x, player->pos.y, player->pos.z + 50.0f, 20.0f);
            }

            if (player->csTimer <= 900) {
                gLevelStartStatusScreenTimer = 50;

                player->state_1C8 = PLAYERSTATE_1C8_ACTIVE;
                player->csState = 0;
                player->csTimer = 0;

                gLoadLevelObjects = 1;
                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 50);
                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 50);
                AUDIO_PLAY_BGM(NA_BGM_STAGE_AQ);
            }

            Aquas_801AC8A8(player->pos.x + RAND_FLOAT_CENTERED(10.0f), player->pos.y + RAND_FLOAT_CENTERED(10.0f),
                           player->pos.z - 65.0f + RAND_FLOAT_CENTERED(10.0f), 0.4f, 1);
            break;

        default:
            break;
    }

    Matrix_RotateY(gCalcMatrix, M_DTOR * (player->rot.y + player->yRot_114 + 180.0f), MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -(M_DTOR * player->rot.x), MTXF_APPLY);

    src.x = 0.0f;
    src.y = 0.0f;
    src.z = player->baseSpeed;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

    player->vel.x = dest.x;
    player->vel.y = dest.y;
    player->vel.z = dest.z;

    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;
    gPathTexScroll -= player->vel.z;

    player->bankAngle = player->rot.z + player->zRotBank + player->zRotBarrelRoll;

    Math_SmoothStepToF(&player->cam.eye.x, gCsCamEyeX, D_ctx_80177A48[0], 50000.0f, 0.0f);
    Math_SmoothStepToF(&player->cam.eye.y, gCsCamEyeY, D_ctx_80177A48[0], 50000.0f, 0.0f);
    Math_SmoothStepToF(&player->cam.eye.z, gCsCamEyeZ, D_ctx_80177A48[0], 50000.0f, 0.0f);
    Math_SmoothStepToF(&player->cam.at.x, gCsCamAtX, D_ctx_80177A48[0], 50000.0f, 0.0f);
    Math_SmoothStepToF(&player->cam.at.y, gCsCamAtY, D_ctx_80177A48[0], 50000.0f, 0.0f);
    Math_SmoothStepToF(&player->cam.at.z, gCsCamAtZ, D_ctx_80177A48[0], 50000.0f, 0.0f);
}

// unused data
s32 D_800D24A0[] = { 60, 200 };
f32 D_800D24A8[] = { 0.0f, 10.0f, 20.0f, 5.0f, 7.0f, 13.0f };
f32 D_800D24C0[] = { 128.0f, 128.0f, 255.0f, 128.0f };
s32 D_800D24C8[] = { 0, 900 };
f32 D_800D24CC = 0.02f;

void func_hud_80094954(Effect* effect) {
    Player* player = &gPlayer[0];

    if ((player->state_1C8 == PLAYERSTATE_1C8_LEVEL_INTRO) && (gCurrentLevel == LEVEL_AQUAS) && (player->csState < 2)) {
        switch (effect->state) {
            case 0:
                effect->unk_44 += effect->unk_46;
                effect->unk_4A = effect->unk_44;
                effect->scale2 += 0.01f;

                if (effect->unk_4A >= 200) {
                    effect->state = 1;
                    effect->unk_4A = 200;
                }
                break;

            case 1:
                effect->unk_4A -= effect->unk_46;
                effect->scale2 -= 0.1f;
                break;
        }

        if ((effect->state == 1) && (effect->unk_4A <= 0)) {
            Object_Kill(&effect->obj, effect->sfxSource);
        }

        effect->vel.y += effect->scale1;
        effect->scale1 -= 0.05f;

        if (effect->scale1 < -1.0f) {
            effect->scale1 = -1.0f;
        }
        effect->obj.rot.z += effect->unk_48;
    } else {
        if (player->state_1C8 == PLAYERSTATE_1C8_LEVEL_COMPLETE) {
            effect->obj.rot.x = RAD_TO_DEG(player->camPitch);
            effect->obj.rot.y = RAD_TO_DEG(-player->camYaw);
        }

        if (player->state_1C8 == PLAYERSTATE_1C8_NEXT) {
            effect->unk_46 = 2;
            if (player->csState >= 4) {
                effect->vel.y -= 0.13f;
            }
        }

        effect->scale2 += 0.8f;
        effect->unk_4A -= effect->unk_46;

        if ((effect->unk_4A < 0) || ((player->state_1C8 == PLAYERSTATE_1C8_LEVEL_INTRO) &&
                                     (gCurrentLevel == LEVEL_AQUAS) && (player->csState == 5))) {
            Object_Kill(&effect->obj, effect->sfxSource);
        }
        effect->obj.rot.z += effect->unk_48;
    }
}

void func_hud_80094BBC(Effect* effect) {
    if ((gPlayer[0].state_1C8 == PLAYERSTATE_1C8_LEVEL_INTRO) && (gCurrentLevel == LEVEL_AQUAS) &&
        (gPlayer[0].csState < 2)) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_68);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 0, 21, 34, effect->unk_4A);
        gDPSetEnvColor(gMasterDisp++, 255, 255, 251, 0);
        Graphics_SetScaleMtx(effect->scale2);
        gSPDisplayList(gMasterDisp++, D_1023750);
    } else {
        Graphics_SetScaleMtx(effect->scale2);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, effect->unk_4A);
        gSPDisplayList(gMasterDisp++, D_1023750);
    }
}

void stub_80094D10(void) {
}
void stub_80094D18(void) {
}

void func_hud_80094D20(f32 x, f32 y) {
    u8* D_800D24DC[] = { aLargeText_0, aLargeText_1, aLargeText_2, aLargeText_3, aLargeText_4,
                         aLargeText_5, aLargeText_6, aLargeText_7, aLargeText_8, aLargeText_9 };
    s32 D_800D2504[] = { 100, 10, 1 };
    bool boolTemp;
    s32 i;
    s32 j;
    s32 temp;
    s32 temp2;
    s32 temp3;
    s32 temp4;
    f32 x1;
    f32 y1;
    f32 xScale;

    if (gHitCount > gDisplayedHitCount) {
        temp3 = gDisplayedHitCount + 1;
        temp4 = gDisplayedHitCount;
    } else {
        temp3 = gHitCount;
        temp4 = gDisplayedHitCount;
    }

    boolTemp = false;
    i = 1000;
    temp3 %= i;
    temp4 %= i;

    for (i /= 10, j = 0; i != 1; i /= 10, j++) {
        xScale = 1.0f;
        x1 = x;
        y1 = y + 3.0f;

        temp = temp3 / i;
        temp2 = temp4 / i;

        if ((temp != 0) || (boolTemp == true)) {
            if (temp != temp2) {
                D_hud_80161720[j] += 0.4f;
                if (D_hud_80161720[j] <= 0.9f) {
                    xScale = D_hud_80161720[j];
                    x1 += 8.0f * xScale;
                    xScale = 1.0f - xScale;
                }

                if ((D_hud_80161720[j] > 0.9f) && (D_hud_80161720[j] < 1.1f)) {
                    xScale = 0.0f;
                }

                if (D_hud_80161720[j] >= 2.0f) {
                    temp2++;
                    if (temp2 >= 10) {
                        temp2 = 0;
                    }
                    D_hud_80161720[j] = 0.0f;
                }

                if ((D_hud_80161720[j] < 2.0f) && (D_hud_80161720[j] >= 1.1f)) {
                    temp2++;
                    if (temp2 >= 10) {
                        temp2 = 0;
                    }
                    xScale = 2.0f - D_hud_80161720[j];
                    x1 += 8.0f * xScale;
                    xScale = 1.0f - xScale;
                }
                temp = temp2;
            }

            if (xScale != 0.0f) {
                TextureRect_IA8(&gMasterDisp, D_800D24DC[temp], 16, 15, x1, y1, xScale, 1.0f);
            }
            boolTemp = true;
        }

        if (!boolTemp && (xScale != 0.0f)) {
            TextureRect_IA8(&gMasterDisp, D_800D24DC[0], 16, 15, x1, y1, xScale, 1.0f);
        }

        x += 13.0f;
        temp3 %= i;
        temp4 %= i;
    }

    xScale = 1.0f;
    x1 = x;
    y1 = y + 3.0f;

    if (temp3 != temp4) {
        D_hud_80161720[j] += 0.4f;
        if (D_hud_80161720[j] <= 0.9f) {
            xScale = D_hud_80161720[j];
            x1 += 8.0f * xScale;
            xScale = 1.0f - xScale;
        }

        if ((D_hud_80161720[j] > 0.9f) && (D_hud_80161720[j] < 1.1f)) {
            xScale = 0.0f;
        }

        if (D_hud_80161720[j] >= 2.0f) {
            temp4++;
            if (temp4 >= 10) {
                temp4 = 0;
            }
            D_hud_80161720[j] = 0.0f;
        }

        if ((D_hud_80161720[j] < 2.0f) && (D_hud_80161720[j] >= 1.1f)) {
            temp4++;
            if (temp4 >= 10) {
                temp4 = 0;
            }
            xScale = 2.0f - D_hud_80161720[j];
            x1 += 8.0f * xScale;
            xScale = 1.0f - xScale;
        }
        temp3 = temp4;
    }

    if (xScale != 0.0f) {
        TextureRect_IA8(&gMasterDisp, D_800D24DC[temp3], 16, 15, x1, y1, xScale, 1.0f);
    }

    if ((gHitCount != gDisplayedHitCount) && (D_hud_80161720[0] == 0.0f) && (D_hud_80161720[1] == 0.0f) &&
        (D_hud_80161720[2] == 0.0f)) {
        gDisplayedHitCount++;

        if ((gDisplayedHitCount == 4) || (gDisplayedHitCount == 9) || (gDisplayedHitCount == 14) ||
            (gDisplayedHitCount == 19) || (gDisplayedHitCount == 24) || (gDisplayedHitCount == 29)) {
            gDropHitCountItem = gDisplayedHitCount;
        }
    }
}

void func_hud_80095350(Actor* actor) {
    Actor_Initialize(actor);
    actor->obj.status = OBJ_ACTIVE;
    actor->obj.id = OBJ_ACTOR_CUTSCENE;
    actor->animFrame = 9999;
    Object_SetInfo(&actor->info, actor->obj.id);
}

void func_hud_800953A0(Actor* actor, s32 arg1) {
    Vec3f D_800D2510[] = {
        { 1800.0f, 0.0f, -4000.0f },
        { -1000.0f, 0.0f, -4800.0f },
        { 800.0f, 0.0f, -5600.0f },
        { -200.0f, 0.0f, -7000.0f },
    };

    Actor_Initialize(actor);
    actor->obj.status = OBJ_ACTIVE;
    actor->obj.id = OBJ_ACTOR_CUTSCENE;
    actor->obj.pos = D_800D2510[arg1];
    actor->obj.pos.z -= gPathProgress;
    actor->animFrame = 45;
    Object_SetInfo(&actor->info, actor->obj.id);
}

void func_hud_8009546C(Actor* actor, s32 arg1) {
    Vec3f D_800D2540[] = {
        { 1300.0f, 0.0f, -2000.0f },  { -1000.0f, 0.0f, -3000.0f }, { 800.0f, 0.0f, 0.0f },
        { -1200.0f, 0.0f, -1000.0f }, { -1400.0f, 0.0f, 700.0f },
    };

    Actor_Initialize(actor);
    actor->obj.status = OBJ_ACTIVE;
    actor->obj.id = OBJ_ACTOR_CUTSCENE;
    actor->obj.pos = D_800D2540[arg1];
    actor->obj.pos.z -= gPathProgress;
    actor->animFrame = 46;
    Object_SetInfo(&actor->info, actor->obj.id);
}

void func_hud_80095538(Actor* actor, s32 arg1) {
    Vec3f D_800D257C[] = {
        { 0.0f, 0.0f, -200.0f },    { -300.0f, 0.0f, -700.0f },  { 400.0f, 0.0f, -900.0f },
        { 300.0f, 0.0f, -1700.0f }, { -260.0f, 0.0f, -2000.0f }, { -200.0f, 0.0f, -2600.0f },
    };

    Actor_Initialize(actor);
    actor->obj.status = OBJ_ACTIVE;
    actor->obj.id = OBJ_ACTOR_CUTSCENE;
    actor->obj.pos = D_800D257C[arg1];
    actor->obj.pos.z -= gPathProgress;
    actor->animFrame = 47;
    Object_SetInfo(&actor->info, actor->obj.id);
}
void HUD_AquasComplete(Player* player) {
    s32 i;
    s32 j;
    Actor* actor;
    f32 x;
    f32 y;
    f32 z;
    f32 x1;
    f32 y1;
    f32 z1;
    s32 pad;
    Vec3f src;
    Vec3f dest;
    s32 shield;

    actor = &gActors[0];

    switch (player->csState) {
        case 0:
            gCsFrameCount = 0;
            player->barrelRollAlpha = 0;
            player->csState = 1;

            D_ctx_80177A48[1] = gBosses[0].obj.pos.x;
            D_ctx_80177A48[2] = gBosses[0].obj.pos.y;
            D_ctx_80177A48[3] = gBosses[0].obj.pos.z;
            D_ctx_80177A48[4] = 0.0f;
            D_ctx_80177A48[5] = 0.0f;
            D_ctx_80177A48[6] = 0.05f;

            D_ctx_80177A48[7] = 0.0f;
            D_ctx_80177A48[8] = 0.0f;
            D_ctx_80177A48[9] = 0.0f;
            D_ctx_80177A48[0] = 0.0f;

        case 1:
            if (gCsFrameCount > 240) {
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
                gFillScreenAlphaTarget = 255;
                gFillScreenAlphaStep = 16;
                if (gCsFrameCount == 280) {
                    player->csState = 10;
                }
            }

            if ((gCsFrameCount >= 30) && (gCsFrameCount < 90)) {
                D_ctx_80177A48[5] -= 0.6f;
                if (D_ctx_80177A48[5] < 0.0f) {
                    D_ctx_80177A48[5] += 360.0f;
                }
                if (D_ctx_80177A48[5] > 360.0f) {
                    D_ctx_80177A48[5] -= 360.0f;
                }
                src.x = 1000.0f;
                src.y = 300.0f;
                src.z = 1000.0f;

                Matrix_Translate(gCalcMatrix, D_ctx_80177A48[1], D_ctx_80177A48[2], D_ctx_80177A48[3], MTXF_NEW);
                Matrix_RotateY(gCalcMatrix, -(M_DTOR * D_ctx_80177A48[5]), MTXF_APPLY);
                Matrix_MultVec3f(gCalcMatrix, &src, &dest);
            }

            if (gCsFrameCount < 30) {
                dest.x = gBosses[0].obj.pos.x;
                dest.y = player->pos.y;
                dest.z = gBosses[0].obj.pos.z + 1000.0f;
            }
            if (gCsFrameCount >= 90) {
                dest.x = player->cam.eye.x;
                dest.y = player->cam.eye.y;
                dest.z = player->cam.eye.z + 200.0f - gPathProgress;
            }

            Math_SmoothStepToAngle(&player->zRotBarrelRoll, 0.0f, 0.05f, 1.2f, 0.0001f);
            Math_SmoothStepToAngle(&player->zRotBank, 0.0f, 0.05f, 1.2f, 0.0001f);
            Math_SmoothStepToF(&player->camRoll, 0.0f, 0.1f, 3.0f, 0.0f);
            Math_SmoothStepToAngle(&player->aerobaticPitch, 0.0f, 0.1f, 20.0f, 0.0f);

            x = player->pos.x - dest.x;
            y = player->pos.y - dest.y;
            z = player->pos.z - dest.z;

            y1 = Math_RadToDeg(Math_Atan2F(x, z));
            z = sqrtf(SQ(x) + SQ(z));
            x1 = Math_RadToDeg(-Math_Atan2F(y, z));

            if ((x1 + 40.0f) >= 360.0f) {
                x1 -= 360.0f;
            }
            if (x1 > 180.0f) {
                x1 = 0.0f;
            }

            z1 = Math_SmoothStepToAngle(&player->rot.y, y1, 0.5f, 2.0f, 0.0001f) * 30.0f;
            Math_SmoothStepToAngle(&player->rot.x, x1, 0.5f, 2.0f, 0.0001f);
            Math_SmoothStepToAngle(&player->rot.z, z1, 0.1f, 5.0f, 0.0001f);

            Math_SmoothStepToAngle(&D_ctx_80177A48[4], 30.0f, 0.05f, 1.0f, 0.001f);
            Math_SmoothStepToF(&D_ctx_80177A48[8], 600.0f, 0.05f, 1000.0f, 0.001f);
            Math_SmoothStepToF(&D_ctx_80177A48[9], 2400.0f, 0.05f, 1000.0f, 0.001f);

            src.x = 0.0f;
            src.y = D_ctx_80177A48[8];
            src.z = D_ctx_80177A48[9];

            Matrix_Translate(gCalcMatrix, gBosses[0].obj.pos.x, gBosses[0].obj.pos.y,
                             gBosses[0].obj.pos.z + gPathProgress, MTXF_NEW);
            Matrix_RotateY(gCalcMatrix, -(M_DTOR * D_ctx_80177A48[4]), MTXF_APPLY);
            Matrix_MultVec3f(gCalcMatrix, &src, &dest);

            Math_SmoothStepToF(&gCsCamEyeX, dest.x, 0.02f, player->baseSpeed, 0.001f);
            Math_SmoothStepToF(&gCsCamEyeY, dest.y, 0.02f, player->baseSpeed, 0.001f);
            Math_SmoothStepToF(&gCsCamEyeZ, dest.z, 0.02f, player->baseSpeed, 0.001f);

            player->cam.eye.x = gCsCamEyeX;
            player->cam.eye.y = gCsCamEyeY;
            player->cam.eye.z = gCsCamEyeZ;

            if (gCsFrameCount < 200) {
                Math_SmoothStepToF(&gCsCamAtX, gBosses[0].obj.pos.x, 0.03f, 100.0f, 0.001f);
                Math_SmoothStepToF(&gCsCamAtY, gBosses[0].obj.pos.y, 0.03f, 100.0f, 0.001f);
                Math_SmoothStepToF(&gCsCamAtZ, gBosses[0].obj.pos.z + 600.0f + gPathProgress, 0.03f, 100.0f, 0.001f);
            } else {
                Math_SmoothStepToF(&gCsCamAtX, player->pos.x, D_ctx_80177A48[6], 1000.0f, 0.001f);
                Math_SmoothStepToF(&gCsCamAtY, player->pos.y, D_ctx_80177A48[6], 1000.0f, 0.001f);
                Math_SmoothStepToF(&gCsCamAtZ, player->pos.z + gPathProgress, D_ctx_80177A48[6], 1000.0f, 0.001f);
                if (gCsFrameCount > 180) {
                    D_ctx_80177A48[6] += 0.005f;
                } else {
                    D_ctx_80177A48[6] += 0.005f;
                }
            }

            player->cam.at.x = gCsCamAtX;
            player->cam.at.y = gCsCamAtY;
            player->cam.at.z = gCsCamAtZ;

            D_ctx_80177A48[0] = 0.0f;
            break;

        case 10:
            player->unk_234 = 1;
            gAqDrawMode = 2;
            player->csState = 11;

            player->bankAngle = player->rot.z = player->zRotBank = player->zRotBarrelRoll = 0.0f;
            player->vel.x = player->vel.y = player->vel.z = 0.0f;
            player->rot.x = player->rot.y = player->rot.z = 0.0f;
            player->boostSpeed = player->yRot_114 = 0.0f;
            player->baseSpeed = 3.6f;
            player->trueZpos = player->pos.z = 0.0f;
            player->pos.y = 100.0f;
            player->pos.x = -100.0f;
            player->barrelRollAlpha = 0;
            player->unk_17C = player->unk_180 = 0.0f;

            D_bg_8015F974 = D_bg_8015F978 = D_bg_8015F97C = 255;
            D_bg_8015F980 = 0;

            gLight1R = 40;
            gLight1G = 100;
            gLight1B = 120;

            gAmbientR = 20;
            gAmbientG = 30;
            gAmbientB = 50;

            Play_ClearObjectData();

            player->zPath = gPathProgress = 0;

            j = 0;
            func_hud_80095350(actor);
            j++;

            for (i = 0; i < 6; i++, j++) {
                func_hud_80095538(&gActors[j], i);
            }

            for (i = 0; i < 5; i++, j++) {
                func_hud_8009546C(&gActors[j], i);
            }

            for (i = 0; i < 4; i++, j++) {
                func_hud_800953A0(&gActors[j], i);
            }

            player->pos.z -= gPathProgress;
            player->trueZpos = player->pos.z;

            actor->fwork[1] = 0.0f;
            actor->fwork[2] = 600.0f;
            actor->fwork[3] = 2600.0f;
            actor->fwork[7] = 0.5f;

            actor->rot_0F4.y = 130.0f;

            src.x = actor->fwork[1];
            src.y = actor->fwork[2];
            src.z = actor->fwork[3];

            Matrix_Translate(gCalcMatrix, player->pos.x, player->pos.y, player->trueZpos + gPathProgress, MTXF_NEW);
            Matrix_RotateY(gCalcMatrix, -(M_DTOR * actor->rot_0F4.y), MTXF_APPLY);
            Matrix_MultVec3f(gCalcMatrix, &src, &dest);

            player->cam.at.x = gCsCamAtX = player->pos.x;
            player->cam.at.y = gCsCamAtY = player->pos.y;
            player->cam.at.z = gCsCamAtZ = player->pos.z - 50.0f + gPathProgress;

            player->cam.eye.x = gCsCamEyeX = dest.x;
            player->cam.eye.y = gCsCamEyeY = dest.y;
            player->cam.eye.z = gCsCamEyeZ = dest.z;

            D_ctx_80177A48[0] = 1.0f;

        case 11:
            gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
            gFillScreenAlphaTarget = 0;
            gFillScreenAlphaStep = 8;

            if (gFillScreenAlpha == 0) {
                player->csState = 12;
            }

        case 12:
            if ((gCsFrameCount >= 380) && (gCsFrameCount < 640 + 280)) {
                Math_SmoothStepToF(&actor->fwork[2], 0.0f, 0.02f, 1000.0f, 0.001f);
                Math_SmoothStepToF(&actor->fwork[3], 300.0f, 0.02f, 1000.0f, 0.001f);
            }
            if (gCsFrameCount >= 920) {
                Math_SmoothStepToF(&actor->fwork[3], 200.0f, 0.02f, 1000.0f, 0.001f);
            }
            if (gCsFrameCount >= 1120) {
                Math_SmoothStepToF(&actor->fwork[7], 0.1f, 0.05f, 1000.0f, 0.001f);
            }
            if (gCsFrameCount >= 1200) {
                Math_SmoothStepToF(&actor->fwork[3], 800.0f, 0.02f, 1000.0f, 0.001f);
                Math_SmoothStepToF(&player->baseSpeed, 5.0f, 0.1f, 1000.0f, 0.001f);
            } else {
                actor->fwork[4] = player->pos.x;
                actor->fwork[5] = player->pos.y;
                actor->fwork[6] = player->trueZpos + gPathProgress;
            }

            if (gCsFrameCount < 1200) {
                gCsCamAtX = player->pos.x;
                gCsCamAtY = player->pos.y;
                gCsCamAtZ = player->pos.z - 50.0f + gPathProgress;
            } else {
                gCsCamAtX = player->pos.x;
                gCsCamAtY = player->pos.y + 10.0f;
                gCsCamAtZ = player->pos.z - 50.0f + gPathProgress;
            }
            D_ctx_80177A48[0] = 0.05f;

            actor->rot_0F4.y += actor->fwork[7];
            if ((actor->rot_0F4.y) < 0.0f) {
                actor->rot_0F4.y += 360.0f;
            }
            if ((actor->rot_0F4.y) > 360.0f) {
                actor->rot_0F4.y -= 360.0f;
            }

            src.x = actor->fwork[1];
            src.y = actor->fwork[2];
            src.z = actor->fwork[3];

            Matrix_Translate(gCalcMatrix, actor->fwork[4], actor->fwork[5], actor->fwork[6], MTXF_NEW);
            Matrix_RotateY(gCalcMatrix, -(M_DTOR * actor->rot_0F4.y), MTXF_APPLY);
            Matrix_MultVec3f(gCalcMatrix, &src, &dest);

            gCsCamEyeX = dest.x;
            gCsCamEyeY = dest.y;
            gCsCamEyeZ = dest.z;

            if (gCsFrameCount >= 1360) {
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
                gFillScreenAlphaTarget = 255;
                gFillScreenAlphaStep = 16;

                if (gFillScreenAlpha == 255) {
                    gLeveLClearStatus[LEVEL_AQUAS] = Play_CheckMedalStatus(150) + 1;
                    player->state_1C8 = PLAYERSTATE_1C8_NEXT;
                    player->csTimer = 0;
                    Audio_FadeOutAll(10);
                    gFadeoutType = 4;
                }
            }

            if (gCsFrameCount == 1310) {
                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 80);
                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 80);
            }
            break;

        default:
            break;
    }

    switch (gCsFrameCount) {
        case 300:
            Radio_PlayMessage(gMsg_ID_15200, RCID_FOX);
            break;

        case 400:
            AUDIO_PLAY_BGM(NA_BGM_COURSE_CLEAR);
            break;

        case 440:
            gLevelClearScreenTimer = 100;
            break;

        case 520:
            Radio_PlayMessage(gMsg_ID_15253, RCID_FOX);
            break;

        case 600:
            shield = gTeamShields[TEAM_ID_PEPPY];
            gTeamShields[TEAM_ID_PEPPY] = 1;
            Radio_PlayMessage(gMsg_ID_15210, RCID_PEPPY);
            gTeamShields[TEAM_ID_PEPPY] = shield;
            break;

        case 680:
            shield = gTeamShields[TEAM_ID_SLIPPY];
            gTeamShields[TEAM_ID_SLIPPY] = 1;
            Radio_PlayMessage(gMsg_ID_15220, RCID_SLIPPY);
            gTeamShields[TEAM_ID_SLIPPY] = shield;
            break;

        case 760:
            shield = gTeamShields[TEAM_ID_FALCO];
            gTeamShields[TEAM_ID_FALCO] = 1;
            Radio_PlayMessage(gMsg_ID_15230, RCID_FALCO);
            gTeamShields[TEAM_ID_FALCO] = shield;
            break;

        case 840:
            shield = gTeamShields[TEAM_ID_SLIPPY];
            gTeamShields[TEAM_ID_SLIPPY] = 1;
            Radio_PlayMessage(gMsg_ID_15240, RCID_SLIPPY);
            gTeamShields[TEAM_ID_SLIPPY] = shield;
            break;

        case 1000:
            gShowLevelClearStatusScreen = 1;
            break;

        case 1200:
            gShowLevelClearStatusScreen = 0;
            break;
    }

    Matrix_RotateY(gCalcMatrix, M_DTOR * (player->rot.y + player->yRot_114 + 180.0f), MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -(M_DTOR * player->rot.x), MTXF_APPLY);

    src.x = 0.0f;
    src.y = 0.0f;
    src.z = player->baseSpeed;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

    player->vel.x = dest.x;
    player->vel.y = dest.y;
    player->vel.z = dest.z;

    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;
    player->pos.z += player->vel.z;

    player->trueZpos = player->pos.z;

    player->bankAngle = player->rot.z + player->zRotBank + player->zRotBarrelRoll;

    player->xRock = SIN_DEG(player->rockPhase * 0.7f) * 0.5f;
    player->bobPhase += 10.0f;
    player->rockPhase += 8.0f;
    player->yBob = -SIN_DEG(player->bobPhase) * 0.5f;
    player->rockAngle = SIN_DEG(player->rockPhase) * 1.5f;

    if (player->unk_234) {
        src.x = 0.0f;
        src.y = 0.0f;
        src.z = -70.0f;
        Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);
        Aquas_801AC8A8(player->pos.x + dest.x + RAND_FLOAT_CENTERED(10.0f),
                       player->pos.y + dest.y + RAND_FLOAT_CENTERED(10.0f),
                       player->pos.z + dest.z + RAND_FLOAT_CENTERED(10.0f), 0.4f, 1);
    }

    player->unk_178 += 20.0f;

    Math_SmoothStepToF(&player->cam.eye.x, gCsCamEyeX, D_ctx_80177A48[0], 50000.0f, 0.001f);
    Math_SmoothStepToF(&player->cam.eye.y, gCsCamEyeY, D_ctx_80177A48[0], 50000.0f, 0.001f);
    Math_SmoothStepToF(&player->cam.eye.z, gCsCamEyeZ, D_ctx_80177A48[0], 50000.0f, 0.001f);
    Math_SmoothStepToF(&player->cam.at.x, gCsCamAtX, D_ctx_80177A48[0], 50000.0f, 0.001f);
    Math_SmoothStepToF(&player->cam.at.y, gCsCamAtY, D_ctx_80177A48[0], 50000.0f, 0.001f);
    Math_SmoothStepToF(&player->cam.at.z, gCsCamAtZ, D_ctx_80177A48[0], 50000.0f, 0.001f);
}

void func_hud_80096A74(Player* player) {
    Vec3f src, dest;
    s32 button;

    switch (player->csState) {
        case 0:
            player->pos.y += 3400.0f;
            player->rot.x = 270.0f;
            gPlayer[0].baseSpeed = 0.0f;

            D_ctx_80177A48[1] = 100.0f;
            D_ctx_80177A48[2] = 0.0f;
            D_ctx_80177A48[0] = 0.2f;
            gCsFrameCount = 0;
            player->csState = 1;
            gFillScreenAlpha = gFillScreenAlphaTarget = 255;

            player->cam.eye.x = gCsCamEyeX = 0.0f;
            player->cam.eye.y = gCsCamEyeY = player->pos.y + D_ctx_80177A48[1];
            player->cam.eye.z = gCsCamEyeZ = 0.0f;

            player->cam.at.x = gCsCamAtX = 0.0f;
            player->cam.at.y = gCsCamAtY = 0.0f;
            player->cam.at.z = gCsCamAtZ = 0.0f;

            D_ctx_80177A48[0] = 1.0f;
            D_ctx_80177A48[2] = 0.0f;
            D_ctx_80177A48[4] = 0.0f;

        case 1:
            if (gCsFrameCount < 30) {
                break;
            }

            if ((gCsFrameCount >= 40) && (gFillScreenAlpha != 0)) {
                gFillScreenAlphaTarget = 0;
                gFillScreenAlphaStep = 8;
            }

            if (gCsFrameCount < 140) {
                Math_SmoothStepToF(&D_ctx_80177A48[1], 800.0f, 0.2f, 10.0f, 0.0f);
                if (gCsFrameCount > 60) {
                    Math_SmoothStepToF(&D_ctx_80177A48[4], 3.0f, 0.05f, 1000.0f, 0.001f);
                }
                player->camRoll += D_ctx_80177A48[4];
                if (player->camRoll >= 360.0f) {
                    player->camRoll -= 360.0f;
                }
                if (player->camRoll < 0.0f) {
                    player->camRoll += 360.0f;
                }
            }

            if (gCsFrameCount >= 140) {
                Math_SmoothStepToAngle(&player->camRoll, 0.0f, 0.05f, 3.0f, 0.001f);
                Math_SmoothStepToF(&D_ctx_80177A48[1], 200.0f, 0.2f, 6.0f, 0.0f);
                Math_SmoothStepToF(&D_ctx_80177A48[2], 200.0f, 0.2f, 6.0f, 0.0f);
                D_ctx_80177A48[0] = 0.2f;
            }

            gCsCamEyeX = player->pos.x;
            gCsCamEyeY = player->pos.y + D_ctx_80177A48[1];
            gCsCamEyeZ = player->pos.z + D_ctx_80177A48[2];

            gCsCamAtX = player->pos.x;
            gCsCamAtY = player->pos.y;
            gCsCamAtZ = player->pos.z;

            if (gCsFrameCount == 270) {
                player->unk_190 = player->unk_194 = 10.0f;
                player->csState = 2;
                D_ctx_80177A48[1] = 400.0f;
                AUDIO_PLAY_SFX(NA_SE_ARWING_DASH, player->sfxSource, 0);
            }
            break;

        case 2:
            D_ctx_80177A48[0] = 0.12f;

            Math_SmoothStepToAngle(&player->camRoll, 0.0f, 0.05f, 3.0f, 0.001f);
            Math_SmoothStepToF(&D_ctx_80177A48[1], (player->pos.y * player->unk_148 + 50.0f), 0.2f, 10.0f, 0.0f);
            Math_SmoothStepToF(&D_ctx_80177A48[2], 400.0f, 0.2f, 6.0f, 0.0f);
            Math_SmoothStepToF(&player->pos.y, 350.0f, 0.1f, 40.0f, 0.0f);

            button = gControllerHold[player->num].button;
            gControllerHold[player->num].button = gBoostButton[player->num];
            player->boostMeter = 1;
            player->csTimer = 60;

            Player_ArwingBoost(player);

            gControllerRumbleFlags[0] = 0;
            gControllerHold[player->num].button = button;

            gCsCamEyeX = player->pos.x;
            gCsCamEyeY = (player->pos.y * player->unk_148 + 50.0f);
            gCsCamEyeZ = D_ctx_80177A48[2];

            gCsCamAtX = player->pos.x;
            gCsCamAtY = (player->pos.y * player->unk_148 + 20.0f);
            gCsCamAtZ = player->pos.z;

            if (gCsFrameCount == 300) {
                gPathTexScroll = 0;
                gLevelStartStatusScreenTimer = 50;
                player->state_1C8 = PLAYERSTATE_1C8_ACTIVE;
                player->baseSpeed = gArwingSpeed;
                player->csState = 0;
                player->csTimer = 0;
                player->unk_014 = 0.0f;
                player->unk_018 = 0.0f;
                player->camRoll = 0.0f;
                gLoadLevelObjects = 1;
            }
            break;
    }

    if (gCsFrameCount >= 30) {
        Math_SmoothStepToF(&player->baseSpeed, 30.0f, 0.05f, 1000.0f, 0.001f);

        if (gCsFrameCount < 110) {
            player->rot.z += (D_ctx_80177A48[4] * 2.0f);
            if (player->rot.z >= 360.0f) {
                player->rot.z -= 360.0f;
            }
            if (player->rot.z < 0.0f) {
                player->rot.z += 360.0f;
            }
        } else {
            Math_SmoothStepToAngle(&player->rot.z, 0.0f, 0.4f, (D_ctx_80177A48[4] * 2.0f), 1.0f);
            if (player->rot.z == 0.0f) {
                if (player->rot.x != 0.0f) {
                    Math_SmoothStepToAngle(&player->rot.x, 0.0f, 0.1f, 2.4f, 0.001f);
                } else {
                    player->bobPhase += 10.0f;
                    player->yBob = -SIN_DEG(player->bobPhase) * 0.5f;
                    player->rockPhase += 3.0f;
                    player->rockAngle = SIN_DEG(player->rockPhase) * 1.5f;
                }
            }
        }

        Matrix_RotateY(gCalcMatrix, M_DTOR * (player->rot.y + player->yRot_114 + 180.0f), MTXF_NEW);
        Matrix_RotateX(gCalcMatrix, -(M_DTOR * (player->rot.x)), MTXF_APPLY);

        src.x = 0.0f;
        src.y = 0.0f;
        src.z = player->baseSpeed;

        Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

        player->vel.x = dest.x;
        player->vel.z = dest.z;
        player->vel.y = dest.y;

        player->pos.x += player->vel.x;
        player->pos.y += player->vel.y;
        gPathTexScroll += player->vel.z;

        player->bankAngle = player->rot.z + player->zRotBank + player->zRotBarrelRoll;
    }

    Math_SmoothStepToF(&player->cam.eye.x, gCsCamEyeX, D_ctx_80177A48[0], 50000.0f, 0.0f);
    Math_SmoothStepToF(&player->cam.eye.y, gCsCamEyeY, D_ctx_80177A48[0], 50000.0f, 0.0f);
    Math_SmoothStepToF(&player->cam.eye.z, gCsCamEyeZ, D_ctx_80177A48[0], 50000.0f, 0.0f);
    Math_SmoothStepToF(&player->cam.at.x, gCsCamAtX, D_ctx_80177A48[0], 50000.0f, 0.0f);
    Math_SmoothStepToF(&player->cam.at.y, gCsCamAtY, D_ctx_80177A48[0], 50000.0f, 0.0f);
    Math_SmoothStepToF(&player->cam.at.z, gCsCamAtZ, D_ctx_80177A48[0], 50000.0f, 0.0f);
}
