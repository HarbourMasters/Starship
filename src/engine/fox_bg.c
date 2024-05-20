#include "global.h"
#include "assets/ast_katina.h"
#include "assets/ast_venom_1.h"
#include "assets/ast_venom_2.h"
#include "assets/ast_fortuna.h"
#include "assets/ast_bg_planet.h"
#include "assets/ast_versus.h"
#include "assets/ast_corneria.h"
#include "assets/ast_meteo.h"
#include "assets/ast_training.h"
#include "assets/ast_sector_x.h"
#include "assets/ast_sector_y.h"
#include "assets/ast_sector_z.h"
#include "assets/ast_aquas.h"
#include "assets/ast_bolse.h"
#include "assets/ast_titania.h"
#include "assets/ast_macbeth.h"
#include "assets/ast_andross.h"
#include "assets/ast_solar.h"
#include "assets/ast_warp_zone.h"
#include "assets/ast_area_6.h"
#include "assets/ast_zoness.h"

#include "prevent_bss_reordering2.h"
#include "prevent_bss_reordering3.h"

f32 gWarpZoneBgAlpha;
u8 D_bg_8015F964;  // related to water surfaces
f32 D_bg_8015F968; // heat shimmer effect for SO and TI?
f32 D_bg_8015F96C; // unused. some sort of starfield motion blur for meteo?
f32 D_bg_8015F970; // these next few vars seem to be related to aquas surface
s32 D_bg_8015F974;
s32 D_bg_8015F978;
s32 D_bg_8015F97C;
s32 D_bg_8015F980;
f32 D_bg_8015F984;             // related to scale of venom in area 6
UNK_TYPE D_bg_8015F988[0x683]; // Unused? Close to being [13][0x80]
f32 gAndrossUnkBrightness;     // can be static

f32 gAndrossUnkAlpha = 0.0f;
u16 gBolseDynamicGround = true;
s32 D_bg_800C9C38 = 0; // unused?
u16 gStarColors[16] = {
    0x108B, 0x108B, 0x1087, 0x1089, 0x39FF, 0x190D, 0x108B, 0x1089,
    0x294B, 0x18DF, 0x294B, 0x1085, 0x39FF, 0x108B, 0x18CD, 0x108B,
};
Gfx* sSunDLs[13] = {
    D_102A8A0, D_102A8A0, D_102A8A0, D_102A8A0, D_102A8A0,           D_BG_PLANET_20112C0, D_102A8A0,
    D_102A8A0, D_102A8A0, D_102A8A0, D_102A8A0, D_BG_PLANET_20112C0, D_102A8A0,
};
Gfx* sKaSunDLs[13] = {
    D_102A8A0, D_102A8A0, D_102A8A0, D_102A8A0, D_102A8A0, D_102A8A0, D_102A8A0,
    D_102A8A0, D_102A8A0, D_102A8A0, D_102A8A0, D_102A8A0, D_102A8A0,
};
f32 sSunShifts[13] = {
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 10.0f, 13.0f, 20.0f, 35.0f, 40.0f, 50.0f, 50.0f, 70.0f,
};
f32 sKaSunShifts[13] = {
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 5.0f, 10.0f, 16.0f, 20.0f, 30.0f, 45.0f, 60.0f, 70.0f,
};
f32 sSunScales[13] = {
    0.7f, 1.0f, 1.2f, 1.4f, 1.8f, 2.0f, 0.4f, 0.6f, 0.8f, 1.7f, 0.8f, 4.0f, 2.0f,
};
f32 sKaSunScales[13] = {
    0.525f, 0.75f, 0.90000004f, 1.05f, 1.3499999f, 0.15f, 0.25f, 0.35f, 1.0f, 0.6f, 0.35f, 0.9f, 1.0f,
};
Color_RGB8 sSunColors[13] = {
    { 255, 255, 255 }, { 255, 255, 192 }, { 255, 255, 128 }, { 255, 255, 96 }, { 255, 255, 64 },
    { 255, 255, 64 },  { 255, 255, 64 },  { 255, 255, 64 },  { 255, 255, 64 }, { 255, 255, 64 },
    { 255, 255, 64 },  { 255, 255, 64 },  { 255, 255, 64 },
};
Color_RGB8 sKaSunColors[13] = {
    { 255, 128, 64 },  { 255, 128, 64 }, { 255, 128, 64 }, { 255, 128, 64 }, { 255, 128, 64 },
    { 255, 255, 64 },  { 255, 128, 64 }, { 255, 128, 64 }, { 255, 255, 64 }, { 128, 128, 128 },
    { 128, 128, 255 }, { 255, 255, 64 }, { 255, 128, 64 },
};
s32 sSunAlphas[13] = {
    255, 80, 64, 48, 32, 12, 32, 44, 32, 42, 36, 12, 38,
};
s32 sKaSunAlphas[13] = {
    80, 60, 40, 20, 10, 20, 30, 20, 15, 30, 20, 27, 20,
};
s32 sSunGlareAlphaStep[2] = { 10, 4 };
s32 sSunGlareMaxAlpha[2] = { 140, 40 };
f32 sLensFlareAlphaMod[2] = { 1.2f, 0.5f };
f32 sGroundPositions360x[4] = {
    6000.0f,
    -6000.0f,
    6000.0f,
    -6000.0f,
};
f32 sGroundPositions360z[4] = {
    6000.0f,
    6000.0f,
    -6000.0f,
    -6000.0f,
};

void Background_DrawStarfield(void) {
    f32 by;
    f32 bx;
    s16 vy;
    s16 vx;
    s32 i;
    s32 starCount;
    f32 zCos;
    f32 zSin;
    f32 xField;
    f32 yField;
    f32* xStar;
    f32* yStar;
    u32* color;

    gDPPipeSync(gMasterDisp++);
    gDPSetCycleType(gMasterDisp++, G_CYC_FILL);
    gDPSetCombineMode(gMasterDisp++, G_CC_SHADE, G_CC_SHADE);
    gDPSetRenderMode(gMasterDisp++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    starCount = gStarCount;
    if (starCount != 0) {
        if (gStarfieldX >= 1.5f * SCREEN_WIDTH) {
            gStarfieldX -= 1.5f * SCREEN_WIDTH;
        }
        if (gStarfieldY >= 1.5f * SCREEN_HEIGHT) {
            gStarfieldY -= 1.5f * SCREEN_HEIGHT;
        }
        if (gStarfieldX < 0.0f) {
            gStarfieldX += 1.5f * SCREEN_WIDTH;
        }
        if (gStarfieldY < 0.0f) {
            gStarfieldY += 1.5f * SCREEN_HEIGHT;
        }
        xField = gStarfieldX;
        yField = gStarfieldY;

        xStar = gStarOffsetsX;
        yStar = gStarOffsetsY;
        color = gStarFillColors;

        if (gGameState != GSTATE_PLAY) {
            starCount = 1000;
        }
        zCos = __cosf(gStarfieldRoll);
        zSin = __sinf(gStarfieldRoll);
        for (i = 0; i < starCount; i++, yStar++, xStar++, color++) {
            bx = *xStar + xField;
            by = *yStar + yField;
            if (bx >= 1.25f * SCREEN_WIDTH) {
                bx -= 1.5f * SCREEN_WIDTH;
            }
            bx -= SCREEN_WIDTH / 2.0f;

            if (by >= 1.25f * SCREEN_HEIGHT) {
                by -= 1.5f * SCREEN_HEIGHT;
            }
            by -= SCREEN_HEIGHT / 2.0f;

            vx = (zCos * bx) + (zSin * by) + SCREEN_WIDTH / 2.0f;
            vy = (-zSin * bx) + (zCos * by) + SCREEN_HEIGHT / 2.0f;
            if ((vx >= 0) && (vx < SCREEN_WIDTH) && (vy > 0) && (vy < SCREEN_HEIGHT)) {
                gDPPipeSync(gMasterDisp++);
                gDPSetFillColor(gMasterDisp++, *color);
                gDPFillRectangle(gMasterDisp++, vx, vy, vx, vy);
            }
        }
    }
    gDPPipeSync(gMasterDisp++);
    gDPSetColorDither(gMasterDisp++, G_CD_MAGICSQ);
}

void Background_DrawPartialStarfield(s32 yMin, s32 yMax) {
    f32 by; // 8C
    f32 bx; // 88
    s16 vy; // 84
    s16 vx;
    s32 i;      // 80
    s32 var_s2; // 7C
    f32 cos;    // 78
    f32 sin;    // 74
    f32 spf68;  // 70
    f32 spf64;  // 6C
    f32* sp60;  // 68
    f32* sp5C;  // 64
    u32* sp58;  // 60

    gDPPipeSync(gMasterDisp++);
    gDPSetCycleType(gMasterDisp++, G_CYC_FILL);
    gDPSetCombineMode(gMasterDisp++, G_CC_SHADE, G_CC_SHADE);
    gDPSetRenderMode(gMasterDisp++, G_RM_OPA_SURF, G_RM_OPA_SURF2);

    if (gStarfieldX >= 1.5f * SCREEN_WIDTH) {
        gStarfieldX -= 1.5f * SCREEN_WIDTH;
    }
    if (gStarfieldY >= 1.5f * SCREEN_HEIGHT) {
        gStarfieldY -= 1.5f * SCREEN_HEIGHT;
    }
    if (gStarfieldX < 0.0f) {
        gStarfieldX += 1.5f * SCREEN_WIDTH;
    }
    if (gStarfieldY < 0.0f) {
        gStarfieldY += 1.5f * SCREEN_HEIGHT;
    }

    spf68 = gStarfieldX;
    spf64 = gStarfieldY;

    sp60 = gStarOffsetsX;
    sp5C = gStarOffsetsY;
    sp58 = gStarFillColors;
    var_s2 = 500;

    cos = __cosf(gStarfieldRoll);
    sin = __sinf(gStarfieldRoll);
    for (i = 0; i < var_s2; i++, sp5C++, sp60++, sp58++) {
        bx = *sp60 + spf68;
        by = *sp5C + spf64;
        if (bx >= SCREEN_WIDTH * 1.25f) {
            bx -= 1.5f * SCREEN_WIDTH;
        }
        bx -= SCREEN_WIDTH / 2.0f;
        if (by >= SCREEN_HEIGHT * 1.25f) {
            by -= 1.5f * SCREEN_HEIGHT;
        }
        by -= SCREEN_HEIGHT / 2.0f;

        vx = (cos * bx) + (sin * by) + SCREEN_WIDTH / 2.0f;
        vy = (-sin * bx) + (cos * by) + SCREEN_HEIGHT / 2.0f;
        if ((vx >= 0) && (vx < SCREEN_WIDTH) && (yMin < vy) && (vy < yMax)) {
            gDPPipeSync(gMasterDisp++);
            gDPSetFillColor(gMasterDisp++, *sp58);
            gDPFillRectangle(gMasterDisp++, vx, vy, vx, vy);
        }
    }
    gDPPipeSync(gMasterDisp++);
    gDPSetColorDither(gMasterDisp++, G_CD_MAGICSQ);
}

void func_bg_8003E1E0(void) {
}

// TODO: use SCREEN_WIDTH and _HEIGHT
void Background_DrawBackdrop(void) {
    f32 sp13C;
    f32 sp138;
    f32 sp134;
    f32 sp130;
    f32 sp12C;
    f32 sp128;
    s32 i;
    u8 levelType;
    s32 levelId;

    if (gDrawBackdrop == 0) {
        return;
    }

    levelType = gLevelType;
    if ((gCurrentLevel == LEVEL_VERSUS) && (gVersusStage == VS_STAGE_SECTOR_Z)) {
        levelType = LEVELTYPE_PLANET;
    }
    if (gCurrentLevel == LEVEL_TRAINING) {
        levelType = LEVELTYPE_SPACE;
    }
    levelId = gCurrentLevel;
    Matrix_Push(&gGfxMatrix);
    if (D_ctx_80177C70 == 2) {
        Matrix_Scale(gGfxMatrix, 1.2f, 1.2f, 1.0f, MTXF_APPLY);
    }
    switch (levelType) {
        case LEVELTYPE_PLANET:
            RCP_SetupDL(&gMasterDisp, SETUPDL_17);
            switch (levelId) {
                case LEVEL_FORTUNA:
                case LEVEL_KATINA:
                case LEVEL_VENOM_2:
                case LEVEL_VERSUS:
                    sp134 = (gPlayer[gPlayerNum].camPitch * -6000.0f) - (gPlayer[gPlayerNum].cam.eye.y * 0.4f);
                    sp13C = Math_ModF(Math_RadToDeg(gPlayer[gPlayerNum].camYaw) * (-7280.0f / 360.0f) * 5.0f, 7280.0f);
                    Matrix_RotateZ(gGfxMatrix, gPlayer[gPlayerNum].camRoll * M_DTOR, MTXF_APPLY);
                    Matrix_Translate(gGfxMatrix, sp13C, -2000.0f + sp134, -6000.0f, MTXF_APPLY);
                    if (gCurrentLevel == LEVEL_FORTUNA) {
                        Matrix_Translate(gGfxMatrix, 0.0f, -2000.0f, 0, MTXF_APPLY);
                    } else if (gCurrentLevel == LEVEL_KATINA) {
                        Matrix_Translate(gGfxMatrix, 0.0f, -2500.0f, 0, MTXF_APPLY);
                    }
                    Matrix_SetGfxMtx(&gMasterDisp);
                    switch (gCurrentLevel) {
                        case LEVEL_VERSUS:
                            if (gVersusStage == VS_STAGE_CORNERIA) {
                                gSPDisplayList(gMasterDisp++, D_versus_302D4D0);
                            } else if (gVersusStage == VS_STAGE_KATINA) {
                                gSPDisplayList(gMasterDisp++, D_versus_30146B0);
                            } else {
                                gSPDisplayList(gMasterDisp++, D_versus_3011E40);
                            }
                            break;
                        case LEVEL_FORTUNA:
                            gSPDisplayList(gMasterDisp++, D_FO_600D9F0);
                            break;
                        case LEVEL_KATINA:
                            gSPDisplayList(gMasterDisp++, D_KA_600F1D0);
                            break;
                        case LEVEL_VENOM_2:
                            gSPDisplayList(gMasterDisp++, D_VE2_600F670);
                            break;
                    }
                    Matrix_Translate(gGfxMatrix, 7280.0f, 0.0f, 0.0f, MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    switch (gCurrentLevel) {
                        case LEVEL_VERSUS:
                            if (gVersusStage == VS_STAGE_CORNERIA) {
                                gSPDisplayList(gMasterDisp++, D_versus_302D4D0);
                            } else if (gVersusStage == VS_STAGE_KATINA) {
                                gSPDisplayList(gMasterDisp++, D_versus_30146B0);
                            } else {
                                gSPDisplayList(gMasterDisp++, D_versus_3011E40);
                            }
                            break;
                        case LEVEL_FORTUNA:
                            gSPDisplayList(gMasterDisp++, D_FO_600D9F0);
                            break;
                        case LEVEL_KATINA:
                            gSPDisplayList(gMasterDisp++, D_KA_600F1D0);
                            break;
                        case LEVEL_VENOM_2:
                            gSPDisplayList(gMasterDisp++, D_VE2_600F670);
                            break;
                    }
                    break;
                case LEVEL_CORNERIA:
                case LEVEL_VENOM_1:
                    sp134 = (gPlayer[gPlayerNum].camPitch * -6000.0f) - (gPlayer[gPlayerNum].cam.eye.y * 0.6f);
                    sp13C = Math_ModF(Math_RadToDeg(gPlayer[gPlayerNum].camYaw) * (-7280.0f / 360.0f) * 5.0f, 7280.0f);
                    Matrix_RotateZ(gGfxMatrix, gPlayer[gPlayerNum].camRoll * M_DTOR, MTXF_APPLY);
                    Matrix_Translate(gGfxMatrix, sp13C, -2000.0f + sp134, -6000.0f, MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    switch (gCurrentLevel) {
                        case LEVEL_CORNERIA:
                            gSPDisplayList(gMasterDisp++, D_CO_60059F0);
                            break;
                        case LEVEL_VENOM_1:
                            gSPDisplayList(gMasterDisp++, D_VE1_60046F0);
                            break;
                    }
                    Matrix_Translate(gGfxMatrix, 7280.0f, 0.0f, 0.0f, MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    switch (gCurrentLevel) {
                        case LEVEL_CORNERIA:
                            gSPDisplayList(gMasterDisp++, D_CO_60059F0);
                            break;
                        case LEVEL_VENOM_1:
                            gSPDisplayList(gMasterDisp++, D_VE1_60046F0);
                            break;
                    }
                    break;
                case LEVEL_VENOM_ANDROSS:
                    if (gDrawBackdrop != 6) {
                        if ((gDrawBackdrop == 2) || (gDrawBackdrop == 7)) {
                            Matrix_RotateZ(gGfxMatrix, gPlayer[gPlayerNum].camRoll * M_DTOR, MTXF_APPLY);
                            Matrix_Translate(gGfxMatrix, 0.0f, -4000.0f, -7000.0f, MTXF_APPLY);
                            Matrix_SetGfxMtx(&gMasterDisp);
                            gSPDisplayList(gMasterDisp++, D_VE2_600F670);
                        } else if ((gDrawBackdrop == 3) || (gDrawBackdrop == 4)) {
                            RCP_SetupDL(&gMasterDisp, SETUPDL_62);
                            if (gDrawBackdrop == 4) {
                                if ((gGameFrameCount & 8) == 0) {
                                    Math_SmoothStepToF(&gAndrossUnkBrightness, 0.0f, 1.0f, 30.0f, 0);
                                } else {
                                    Math_SmoothStepToF(&gAndrossUnkBrightness, 120.0f, 1.0f, 30.0f, 0);
                                }
                            } else {
                                gAndrossUnkBrightness = 255.0f;
                            }
                            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, (s32) gAndrossUnkBrightness,
                                            (s32) gAndrossUnkBrightness, (s32) gAndrossUnkAlpha);

                            sp134 = (gPlayer[gPlayerNum].camPitch * -6000.0f) - (gPlayer[gPlayerNum].cam.eye.y * 0.4f);
                            sp13C = Math_ModF(Math_RadToDeg(gPlayer[gPlayerNum].camYaw) * (-7280.0f / 360.0f) * 5.0f,
                                              7280.0f);
                            Matrix_RotateZ(gGfxMatrix, gPlayer[gPlayerNum].camRoll * M_DTOR, MTXF_APPLY);
                            Matrix_Translate(gGfxMatrix, sp13C, -2000.0f + sp134, -6000.0f, MTXF_APPLY);
                            Matrix_Translate(gGfxMatrix, 0.0f, -2500.0f, 0.0f, MTXF_APPLY);
                            Matrix_SetGfxMtx(&gMasterDisp);
                            gSPDisplayList(gMasterDisp++, D_VE2_60038E0);
                            Matrix_Translate(gGfxMatrix, 7280.0f, 0.0f, 0.0f, MTXF_APPLY);
                            Matrix_SetGfxMtx(&gMasterDisp);
                            gSPDisplayList(gMasterDisp++, D_VE2_60038E0);
                        } else {
                        fake_label: // fake
                            RCP_SetupDL(&gMasterDisp, SETUPDL_62);
                            if (gDrawBackdrop == 5) {
                                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 64);
                            } else {
                                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 0, 255, 128, (s32) gAndrossUnkAlpha);
                            }
                            Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -290.0f, MTXF_APPLY);
                            Matrix_Push(&gGfxMatrix);
                            Matrix_Scale(gGfxMatrix, 11.0f, 11.0f, 1.0f, MTXF_APPLY);
                            Matrix_RotateZ(gGfxMatrix, (gPlayer[0].camRoll + (gGameFrameCount * 1.5f)) * M_DTOR,
                                           MTXF_APPLY);
                            Matrix_SetGfxMtx(&gMasterDisp);
                            gSPDisplayList(gMasterDisp++, D_ANDROSS_C039208);
                            Matrix_Pop(&gGfxMatrix);
                            if (gDrawBackdrop != 5) {
                                Matrix_Push(&gGfxMatrix);
                                Matrix_Scale(gGfxMatrix, 10.0f, 10.0f, 1.0f, MTXF_APPLY);
                                Matrix_RotateZ(gGfxMatrix, (gPlayer[0].camRoll + (gGameFrameCount * -1.3f)) * M_DTOR,
                                               MTXF_APPLY);
                                Matrix_SetGfxMtx(&gMasterDisp);
                                gSPDisplayList(gMasterDisp++, D_ANDROSS_C039208);
                                Matrix_Pop(&gGfxMatrix);
                            }
                        }
                    }
                    break;
                case LEVEL_AQUAS:
                    if (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_LEVEL_INTRO) {
                        sp13C = Math_RadToDeg(gPlayer[gPlayerNum].camYaw) - gPlayer[gPlayerNum].yRot_114;
                        sp134 = (gPlayer[gPlayerNum].camPitch * -7000.0f) - (gPlayer[gPlayerNum].cam.eye.y * 0.6f);
                        sp13C = Math_ModF(sp13C * -40.44444f * 2.0f, 7280.0f); // close to 7280.0f / 180.0f
                        RCP_SetupDL_17();
                        Matrix_RotateZ(gGfxMatrix, gPlayer[gPlayerNum].camRoll * M_DTOR, MTXF_APPLY);
                        Matrix_Scale(gGfxMatrix, 1.5f, 1.0f, 1.0f, MTXF_APPLY);
                        Matrix_Push(&gGfxMatrix);
                        Matrix_Translate(gGfxMatrix, sp13C, sp134, -7000.0f, MTXF_APPLY);
                        Matrix_SetGfxMtx(&gMasterDisp);
                        if (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_LEVEL_INTRO) {
                            gSPDisplayList(gMasterDisp++, D_AQ_601AFF0);
                        } else {
                            gSPDisplayList(gMasterDisp++, D_AQ_601C080);
                        }

                        if (sp13C < 0) {
                            sp13C = 1.0f;
                        } else {
                            sp13C = -1.0f;
                        }
                        Matrix_Translate(gGfxMatrix, 7280.0f * sp13C, 0.0f, 0.0f, MTXF_APPLY);
                        Matrix_SetGfxMtx(&gMasterDisp);
                        if (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_LEVEL_INTRO) {
                            gSPDisplayList(gMasterDisp++, D_AQ_601AFF0);

                        } else {
                            gSPDisplayList(gMasterDisp++, D_AQ_601C080);
                        }
                        Matrix_Pop(&gGfxMatrix);
                    }
                    break;
                case LEVEL_SOLAR:
                case LEVEL_ZONESS:
                case LEVEL_MACBETH:
                case LEVEL_TITANIA:
                    sp12C = Math_RadToDeg(gPlayer[gPlayerNum].camYaw) - gPlayer[gPlayerNum].yRot_114;
                    sp134 = (gPlayer[gPlayerNum].camPitch * -7000.0f) - (gPlayer[gPlayerNum].cam.eye.y * 0.6f);
                    sp13C = sp12C * -40.44444f * 2.0f; // close to 7280.0f / 180.0f
                    if ((gCurrentLevel == LEVEL_TITANIA) && (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_LEVEL_INTRO) &&
                        (gPlayer[0].csState < 3)) {
                        D_bg_8015F968 += __sinf(gPlayer[0].camYaw) * 20.0f;
                        sp13C += D_bg_8015F968;
                    }
                    if ((gCurrentLevel == LEVEL_SOLAR) && (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_LEVEL_INTRO) &&
                        (gPlayer[0].csState >= 2) && (gPlayer[0].cam.eye.z <= -1900.0f)) {
                        D_bg_8015F968 = __sinf(gPlayer[0].camPitch) * 7000.0f;
                        sp134 -= fabsf(D_bg_8015F968);
                    }
                    sp13C = Math_ModF(sp13C, 7280.0f);
                    RCP_SetupDL_17();
                    Matrix_RotateZ(gGfxMatrix, gPlayer[gPlayerNum].camRoll * M_DTOR, MTXF_APPLY);
                    Matrix_Scale(gGfxMatrix, 1.5f, 1.0f, 1.0f, MTXF_APPLY);
                    if ((gCurrentLevel == LEVEL_TITANIA) || (gCurrentLevel == LEVEL_ZONESS)) {
                        Matrix_Translate(gGfxMatrix, sp13C, -3000.0f + sp134, -7000.0f, MTXF_APPLY);
                    } else if (gCurrentLevel == LEVEL_SOLAR) {
                        Matrix_Translate(gGfxMatrix, sp13C, -3500.0f + sp134, -7000.0f, MTXF_APPLY);
                    } else if (gCurrentLevel == LEVEL_MACBETH) {
                        Matrix_Translate(gGfxMatrix, sp13C, -4000.0f + sp134, -7000.0f, MTXF_APPLY);
                    }
                    Matrix_SetGfxMtx(&gMasterDisp);
                    if (gCurrentLevel == LEVEL_TITANIA) {
                        gSPDisplayList(gMasterDisp++, D_TI_6000A80);
                    } else if (gCurrentLevel == LEVEL_MACBETH) {
                        gSPDisplayList(gMasterDisp++, D_MA_6019220);
                    } else if (gCurrentLevel == LEVEL_ZONESS) {
                        gSPDisplayList(gMasterDisp++, D_ZO_6013480);
                    } else if (gCurrentLevel == LEVEL_SOLAR) {
                        gSPDisplayList(gMasterDisp++, D_SO_601E150);
                    }
                    if (sp13C < 0) {
                        sp13C = 1.0f;
                    } else {
                        sp13C = -1.0f;
                    }
                    Matrix_Translate(gGfxMatrix, 7280.0f * sp13C, 0.0f, 0.0f, MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    if (gCurrentLevel == LEVEL_TITANIA) {
                        gSPDisplayList(gMasterDisp++, D_TI_6000A80);
                    } else if (gCurrentLevel == LEVEL_MACBETH) {
                        gSPDisplayList(gMasterDisp++, D_MA_6019220);
                    } else if (gCurrentLevel == LEVEL_ZONESS) {
                        gSPDisplayList(gMasterDisp++, D_ZO_6013480);
                    } else if (gCurrentLevel == LEVEL_SOLAR) {
                        gSPDisplayList(gMasterDisp++, D_SO_601E150);
                    }
                    break;
            }
            break;
        case LEVELTYPE_SPACE:
            if (gPlayer[0].state_1C8 != PLAYERSTATE_1C8_ENTER_WARP_ZONE) {
                Matrix_Push(&gGfxMatrix);
                sp12C = Math_RadToDeg(gPlayer[0].camYaw);
                sp130 = Math_RadToDeg(gPlayer[0].camPitch);
                if (((sp12C < 45.0f) || (sp12C > 315.0f)) && ((sp130 < 40.0f) || (sp130 > 325.0f))) {
                    RCP_SetupDL_36();
                    sp138 = gStarfieldX;
                    sp134 = gStarfieldY;
                    if (((gCurrentLevel == LEVEL_SECTOR_X) || (gCurrentLevel == LEVEL_METEO)) && (gLevelPhase == 1)) {
                        levelId = LEVEL_WARP_ZONE;
                    }
                    if (levelId == LEVEL_SECTOR_X) {
                        sp138 = Math_ModF(sp138 + 60.0f, 480.0f);
                        sp134 = Math_ModF(sp134 + 360.0f - 40.0f, 360.0f);
                    } else if (levelId == LEVEL_TRAINING) {
                        sp138 = Math_ModF(sp138 - 30.0f, 480.0f);
                        sp134 = Math_ModF(sp134 + 360.0f - 40.0f, 360.0f);
                    } else if ((levelId == LEVEL_SECTOR_Y) && (gLevelMode == LEVELMODE_ON_RAILS)) {
                        sp138 = Math_ModF(sp138 + 480.0f - 60.0f, 480.0f);
                        sp134 = Math_ModF(sp134, 360.0f);
                    } else if (levelId == LEVEL_FORTUNA) {
                        sp138 = Math_ModF(sp138 - 34.5f, 480.0f);
                        sp134 = Math_ModF(sp134 + 19.0f, 360.0f);
                    } else if (levelId == LEVEL_BOLSE) {
                        if ((gPlayer[0].state_1C8 != PLAYERSTATE_1C8_LEVEL_COMPLETE) || (gPlayer[0].csState < 10)) {
                            sp134 = Math_ModF(sp134 + 360.0f - 100.0f, 360.0f);
                        }
                    } else {
                        sp138 = Math_ModF(sp138, 480.0f);
                        sp134 = Math_ModF(sp134, 360.0f);
                    }
                    if ((sp12C < 180.0f) && (sp138 > 380.0f)) {
                        sp138 = -(480.0f - sp138);
                    }
                    if ((sp130 > 180.0f) && (sp134 > 280.0f)) {
                        sp134 = -(360.0f - sp134);
                    }
                    Matrix_RotateZ(gGfxMatrix, gStarfieldRoll, MTXF_APPLY);
                    switch (levelId) {
                        case LEVEL_WARP_ZONE:
                            if ((s32) gWarpZoneBgAlpha != 0) {
                                RCP_SetupDL_62();
                                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, (s32) gWarpZoneBgAlpha);
                                Matrix_Translate(gGfxMatrix, sp138 - 120.0f, -(sp134 - 120.0f), -290.0f, MTXF_APPLY);
                                Matrix_Scale(gGfxMatrix, 1.7f, 1.7f, 1.0f, MTXF_APPLY);
                                Matrix_Push(&gGfxMatrix);
                                Matrix_RotateZ(gGfxMatrix, -(f32) gGameFrameCount * 10.0f * M_DTOR, MTXF_APPLY);
                                Matrix_Scale(gGfxMatrix, 1.07f, 0.93f, 1.0f, MTXF_APPLY);
                                Matrix_RotateZ(gGfxMatrix, gGameFrameCount * 10.0f * M_DTOR, MTXF_APPLY);
                                Matrix_Scale(gGfxMatrix, 1.07f, 0.93f, 1.0f, MTXF_APPLY);
                                Matrix_SetGfxMtx(&gMasterDisp);
                                gSPDisplayList(gMasterDisp++, D_WZ_7001540);
                                Matrix_Pop(&gGfxMatrix);
                            }
                            break;
                        case LEVEL_METEO:
                            if ((gPlayer[0].state_1C8 == PLAYERSTATE_1C8_LEVEL_COMPLETE) && (gCsFrameCount > 260)) {
                                Matrix_Translate(gGfxMatrix, sp138 - 120.0f, -(sp134 - 120.0f) - 30.0f, -290.0f,
                                                 MTXF_APPLY);
                                Matrix_Scale(gGfxMatrix, 0.5f, 0.5f, 1.0f, MTXF_APPLY);
                                Matrix_SetGfxMtx(&gMasterDisp);
                                gSPDisplayList(gMasterDisp++, D_ME_600DDF0);
                            } else if (gPathProgress > 185668.0f) {
                                Matrix_Translate(gGfxMatrix, sp138 - 120.0f, -(sp134 - 120.0f) - 130.0f, -290.0f,
                                                 MTXF_APPLY);
                                Matrix_Scale(gGfxMatrix, 0.4f, 0.4f, 1.0f, MTXF_APPLY);
                                Matrix_SetGfxMtx(&gMasterDisp);
                                gSPDisplayList(gMasterDisp++, D_ME_600DDF0);
                            }
                            break;
                        case LEVEL_SECTOR_X:
                            if (gSceneSetup == 0) {
                                Matrix_Translate(gGfxMatrix, sp138 - 120.0f, -(sp134 - 120.0f), -290.0f, MTXF_APPLY);
                                Matrix_Scale(gGfxMatrix, 3.0f, 3.0f, 1.0f, MTXF_APPLY);
                                Matrix_SetGfxMtx(&gMasterDisp);
                                RCP_SetupDL_62();
                                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 192);
                                gSPDisplayList(gMasterDisp++, D_SX_6029890);
                            }
                            break;
                        case LEVEL_TRAINING:
                            Matrix_Translate(gGfxMatrix, sp138 - 120.0f, -(sp134 - 120.0f), -290.0f, MTXF_APPLY);
                            Matrix_Scale(gGfxMatrix, 0.2f, 0.2f, 1.0f, MTXF_APPLY);
                            Matrix_SetGfxMtx(&gMasterDisp);
                            RCP_SetupDL_62();
                            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
                            gSPDisplayList(gMasterDisp++, D_TR_6003760);
                            break;
                        case LEVEL_AREA_6:
                        case LEVEL_UNK_4:
                            sp128 = (gPathProgress * 0.00004f) + 0.5f;
                            if (sp128 > 3.5f) {
                                sp128 = 3.5f;
                            }
                            if (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_LEVEL_COMPLETE) {
                                sp128 = D_bg_8015F984;
                                if (sp128 > 3.5f) {
                                    sp128 = 3.5f;
                                }
                            }
                            sp128 = sp128;
                            Matrix_Translate(gGfxMatrix, sp138 - 120.0f, -(sp134 - 120.0f), -290.0f, MTXF_APPLY);
                            Matrix_Scale(gGfxMatrix, sp128 * 0.75, sp128 * 0.75f, 1.0f, MTXF_APPLY);
                            Matrix_SetGfxMtx(&gMasterDisp);
                            gSPDisplayList(gMasterDisp++, D_A6_601BB40);
                            break;
                        case LEVEL_FORTUNA:
                            sp128 = 1.5f;
                            if ((gCsFrameCount > 400) && (gMissionStatus == MISSION_COMPLETE)) {
                                sp128 = 0.75f;
                            }
                            Matrix_Translate(gGfxMatrix, sp138 - 120.0f, -(sp134 - 120.0f), -290.0f, MTXF_APPLY);
                            Matrix_Scale(gGfxMatrix, sp128, sp128, sp128, MTXF_APPLY);
                            Matrix_SetGfxMtx(&gMasterDisp);
                            gSPDisplayList(gMasterDisp++, D_FO_600B4B0);
                            break;
                        case LEVEL_BOLSE:
                            sp128 = 1.0f;
                            if ((gCsFrameCount > 500) && (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_LEVEL_COMPLETE)) {
                                sp128 = 1.3f;
                            }
                            Matrix_Translate(gGfxMatrix, sp138 - 120.0f, -(sp134 - 120.0f), -290.0f, MTXF_APPLY);
                            Matrix_Scale(gGfxMatrix, sp128, sp128, sp128, MTXF_APPLY);
                            Matrix_SetGfxMtx(&gMasterDisp);
                            gSPDisplayList(gMasterDisp++, D_BO_600D190);
                            break;
                        case LEVEL_SECTOR_Z:
                            Matrix_Translate(gGfxMatrix, sp138 - 120.0f, -(sp134 - 120.0f), -290.0f, MTXF_APPLY);
                            Matrix_Scale(gGfxMatrix, 0.5f, 0.5f, 0.5f, MTXF_APPLY);
                            Matrix_RotateX(gGfxMatrix, M_PI / 2, MTXF_APPLY);
                            Matrix_SetGfxMtx(&gMasterDisp);
                            gSPDisplayList(gMasterDisp++, D_SZ_6002F80);
                            break;
                        case LEVEL_SECTOR_Y:
                            Matrix_Translate(gGfxMatrix, sp138 - 120.0f, -(sp134 - 120.0f), -290.0f, MTXF_APPLY);
                            Matrix_Scale(gGfxMatrix, 0.4f, 0.4f, 1.0f, MTXF_APPLY);
                            Matrix_SetGfxMtx(&gMasterDisp);
                            RCP_SetupDL_62();
                            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 192);
                            gSPDisplayList(gMasterDisp++, D_SY_6001840);
                            break;
                    }
                }
                Matrix_Pop(&gGfxMatrix);
            }
            if (gStarWarpDistortion > 0.0f) {
                f32* xStar = gStarOffsetsX;
                f32* yStar = gStarOffsetsY;
                f32 zRot;

                RCP_SetupDL_14();
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 128, 128, 255, 255);
                i = 0;
                zRot = 0.0f;
                for (i = 0; i < 300; i++, xStar++, yStar++) {
                    *xStar = RAND_FLOAT_SEEDED(480.0f) - 80.0f;
                    *yStar = RAND_FLOAT_SEEDED(360.0f) - 60.0f;
                    Matrix_Push(&gGfxMatrix);
                    Matrix_Translate(gGfxMatrix, (*xStar - 160.0f) * 10.0f, (*yStar - 120.0f) * 10.0f, -5000.0f,
                                     MTXF_APPLY);
                    Matrix_RotateZ(gGfxMatrix, zRot, MTXF_APPLY);
                    Matrix_Scale(gGfxMatrix, 10.0f, 1.0f, -gStarWarpDistortion, MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_edisplay_800CFD80);
                    Matrix_Pop(&gGfxMatrix);
                    zRot += M_PI / 4;
                }
            }
            break;
    }
    Matrix_Pop(&gGfxMatrix);
}

void Background_DrawSun(void) {
    f32 camYaw;
    f32 camPitch;
    Color_RGB8* sunColor;
    s32* sunAlpha;
    Gfx** sunDL;
    f32* sunScale;
    s32 i;
    s32 levelType = gLevelType;

    if ((gCurrentLevel == LEVEL_KATINA) || (gCurrentLevel == LEVEL_VENOM_2) || (gCurrentLevel == LEVEL_VENOM_ANDROSS) ||
        (gCurrentLevel == LEVEL_SOLAR) || (gCurrentLevel == LEVEL_TRAINING) || gVersusMode) {
        return;
    }
    gPlayerGlareAlphas[gPlayerNum] -= sSunGlareAlphaStep[levelType];
    if (gPlayerGlareAlphas[gPlayerNum] > 300) {
        gPlayerGlareAlphas[gPlayerNum] = 0;
    }
    if (((gCurrentLevel == LEVEL_AQUAS) && (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_LEVEL_INTRO)) ||
        (((gPlayer[gPlayerNum].state_1C8 == PLAYERSTATE_1C8_U_TURN) || (gLevelMode == LEVELMODE_ALL_RANGE) ||
          (gPlayer[gPlayerNum].state_1C8 == PLAYERSTATE_1C8_LEVEL_COMPLETE)) &&
         (gLevelType == LEVELTYPE_PLANET) && (gCurrentLevel != LEVEL_TITANIA) && (gCurrentLevel != LEVEL_AQUAS))) {
        gPlayerGlareReds[gPlayerNum] = 128;
        gPlayerGlareGreens[gPlayerNum] = 128;
        gPlayerGlareBlues[gPlayerNum] = 128;
        camYaw = Math_RadToDeg(gPlayer[gPlayerNum].camYaw);
        camPitch = Math_RadToDeg(gPlayer[gPlayerNum].camPitch);
        if (camPitch > 180.0f) {
            camPitch -= 360.0f;
        }
        camYaw -= 135.0f;
        gSunViewX = -camYaw * 3.2f;
        gSunViewY = (-camPitch * 3.2f) + 130.0f - ((gPlayer[gPlayerNum].cam.eye.y - 350.0f) * 0.015f);
        if (gCurrentLevel == LEVEL_KATINA) {
            gSunViewY -= 80.0f;
        }
        if ((gCurrentLevel == LEVEL_ZONESS) && (gPlayer[0].csState >= 2) && !gMissedZoSearchlight) {
            gSunViewY -= 60.0f;
            gSunViewX -= 480.0f;
        }
        if ((gSunViewX < 120.0f) && (gSunViewX > -120.0f) && (gSunViewY < 120.0f)) {
            gPlayerGlareAlphas[gPlayerNum] += sSunGlareAlphaStep[levelType] * 2;
            if (sSunGlareMaxAlpha[levelType] < gPlayerGlareAlphas[gPlayerNum]) {
                gPlayerGlareAlphas[gPlayerNum] = sSunGlareMaxAlpha[levelType];
            }
        }
    }
    if (gPlayerGlareAlphas[gPlayerNum] != 0) {
        Matrix_Push(&gGfxMatrix);
        Matrix_RotateZ(gGfxMatrix, gPlayer[gPlayerNum].camRoll * M_DTOR, MTXF_APPLY);
        Matrix_Translate(gGfxMatrix, gSunViewX, gSunViewY, -200.0f, MTXF_APPLY);
        RCP_SetupDL_62();
        sunColor = sSunColors;
        sunAlpha = sSunAlphas;
        sunDL = sSunDLs;
        sunScale = sSunScales;
        if (gCurrentLevel == LEVEL_KATINA) {
            sunColor = sKaSunColors;
            sunAlpha = sKaSunAlphas;
            sunDL = sKaSunDLs;
            sunScale = sKaSunScales;
        }
        for (i = 0; i < 5; i++, sunColor++, sunAlpha++, sunDL++, sunScale++) {
            Matrix_Push(&gGfxMatrix);
            Matrix_Scale(gGfxMatrix, *sunScale, *sunScale, *sunScale, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, sunColor->r, sunColor->g, sunColor->b, *sunAlpha);
            gSPDisplayList(gMasterDisp++, *sunDL);
            Matrix_Pop(&gGfxMatrix);
        }
        Matrix_Pop(&gGfxMatrix);
    }
}

void Background_DrawLensFlare(void) {
    s32 i;
    Color_RGB8* lensFlareColor;
    s32* lensFlareAlpha;
    Gfx** lensFlareDL;
    f32* lensFlareScale;
    f32* lensFlareShift;
    f32 lensFlareOffsetX;
    f32 lensFlareOffsetY;
    f32 alphaMod;
    f32 alpha;

    if ((gCurrentLevel == LEVEL_VENOM_ANDROSS) || (gLevelType == LEVELTYPE_SPACE) ||
        (gPlayerGlareAlphas[gPlayerNum] == 0)) {
        return;
    }
    alphaMod = 1.0f;
    if (gPlayerGlareAlphas[gPlayerNum] < 80) {
        alphaMod = gPlayerGlareAlphas[gPlayerNum] / 80.0f;
    }
    alphaMod *= sLensFlareAlphaMod[gLevelType];
    Matrix_Push(&gGfxMatrix);
    Matrix_RotateZ(gGfxMatrix, gPlayer[gPlayerNum].camRoll * M_DTOR, MTXF_APPLY);
    Matrix_Translate(gGfxMatrix, gSunViewX, gSunViewY, -200.0f, MTXF_APPLY);
    RCP_SetupDL_62();
    lensFlareOffsetX = gSunViewX * -0.03f;
    lensFlareOffsetY = gSunViewY * 0.03f;
    lensFlareColor = &sSunColors[5];
    lensFlareAlpha = &sSunAlphas[5];
    lensFlareDL = &sSunDLs[5];
    lensFlareScale = &sSunScales[5];
    lensFlareShift = &sSunShifts[5];
    if (gCurrentLevel == LEVEL_KATINA) {
        lensFlareColor = &sKaSunColors[5];
        lensFlareAlpha = &sKaSunAlphas[5];
        lensFlareDL = &sKaSunDLs[5];
        lensFlareScale = &sKaSunScales[5];
        lensFlareShift = &sKaSunShifts[5];
    }
    for (i = 5; i < 13; i++, lensFlareColor++, lensFlareAlpha++, lensFlareDL++, lensFlareScale++, lensFlareShift++) {
        Matrix_Push(&gGfxMatrix);
        Matrix_Translate(gGfxMatrix, *lensFlareShift * lensFlareOffsetX, *lensFlareShift * -lensFlareOffsetY, 0.0f,
                         MTXF_APPLY);
        Matrix_Scale(gGfxMatrix, *lensFlareScale, *lensFlareScale, *lensFlareScale, MTXF_APPLY);
        if (((i == 5) || (i == 11)) && (gCurrentLevel != LEVEL_KATINA)) {
            Matrix_RotateX(gGfxMatrix, M_PI / 2, MTXF_APPLY);
        }
        Matrix_SetGfxMtx(&gMasterDisp);
        alpha = *lensFlareAlpha;
        if (i >= 5) {
            alpha *= alphaMod;
        }
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, lensFlareColor->r, lensFlareColor->g, lensFlareColor->b,
                        (s32) alpha);
        gSPDisplayList(gMasterDisp++, *lensFlareDL);
        Matrix_Pop(&gGfxMatrix);
    }
    Matrix_Pop(&gGfxMatrix);
}

void Background_dummy_80040CDC(void) {
}

void Background_DrawGround(void) {
    f32 sp1D4;
    s32 i;
    u32 temp_fv0;
    u32 temp_s0;
    u16* sp1C4;
    Gfx* sp1C0;

    if ((gCurrentLevel != LEVEL_VENOM_2) && ((gPlayer[0].cam.eye.y > 4000.0f) || !gDrawGround)) {
        return;
    }
    if ((gCurrentLevel == LEVEL_BOLSE) && gBolseDynamicGround) {
        Bolse_DrawDynamicGround();
        return;
    }
    sp1D4 = 0.0f;
    if ((gGroundType != 10) && (gGroundType != 11)) {
        sp1D4 = -4000.0f;
    }
    if (gGroundType == 7) {
        sp1D4 = 0.0f;
        gPlayer[gPlayerNum].xPath = 0.0f;
    }

    if (gLevelMode == LEVELMODE_ALL_RANGE) {
        Vec3f sp1B4;
        Vec3f sp1A8;
        f32 temp_fv1;
        f32 temp_fa0;

        sp1D4 = 0.0f;
        gPlayer[gPlayerNum].xPath = 0.0f;

        sp1B4.x = 0;
        sp1B4.y = 0;
        sp1B4.z = -5500.0f;
        Matrix_RotateY(gCalcMatrix, -gPlayer[gPlayerNum].camYaw, MTXF_NEW);
        Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp1B4, &sp1A8);
        temp_fv1 = gPlayer[gPlayerNum].cam.eye.x + sp1A8.x;
        temp_fa0 = gPlayer[gPlayerNum].cam.eye.z + sp1A8.z;
        if (temp_fv1 > 6000.0f) {
            gPlayer[gPlayerNum].xPath = 12000.0f;
        }
        if (temp_fv1 > 18000.0f) {
            gPlayer[gPlayerNum].xPath = 24000.0f;
        }
        if (temp_fv1 < -6000.0f) {
            gPlayer[gPlayerNum].xPath = -12000.0f;
        }
        if (temp_fv1 < -18000.0f) {
            gPlayer[gPlayerNum].xPath = -24000.0f;
        }
        if (temp_fa0 > 6000.0f) {
            sp1D4 = 12000.0f;
        }
        if (temp_fa0 > 18000.0f) {
            sp1D4 = 24000.0f;
        }
        if (temp_fa0 < -6000.0f) {
            sp1D4 = -12000.0f;
        }
        if (temp_fa0 < -18000.0f) {
            sp1D4 = -24000.0f;
        }
    }
    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, gPlayer[gPlayerNum].xPath, -3.0f + gCameraShakeY, sp1D4, MTXF_APPLY);
    if (D_ctx_80177C70 == 2) {
        Matrix_Scale(gGfxMatrix, 1.2f, 1.2f, 1.0f, MTXF_APPLY);
    }
    Matrix_SetGfxMtx(&gMasterDisp);
    switch (gCurrentLevel) {
        case LEVEL_CORNERIA:
            if (gGroundClipMode != 0) {
                RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
            } else {
                RCP_SetupDL_20(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
            }
            if (gLevelMode == LEVELMODE_ON_RAILS) {
                gDPSetTextureImage(gMasterDisp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, SEGMENTED_TO_VIRTUAL(D_CO_601B6C0));
                temp_s0 = fabsf(Math_ModF(2.0f * (gPathTexScroll * 0.2133333f), 128.0f)); // 0.64f / 3.0f
                temp_fv0 = Math_ModF((10000.0f - gPlayer[gPlayerNum].xPath) * 0.32f, 128.0f);
                gDPSetupTile(gMasterDisp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, temp_fv0, temp_s0,
                             G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
                switch (gGroundSurface) {
                    case SURFACE_GRASS:
                        gDPLoadTileTexture(gMasterDisp++, D_CO_601B6C0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32);
                        gBgColor = 0x845; // 8, 8, 32
                        break;
                    case SURFACE_ROCK:
                        gDPLoadTileTexture(gMasterDisp++, D_CO_6028260, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32);
                        gBgColor = 0x845; // 8, 8, 32
                        break;
                    case SURFACE_WATER:
                        RCP_SetupDL_45(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
                        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 128);
                        gDPLoadTileTexture(gMasterDisp++, D_CO_6028A60, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32);
                        gBgColor = 0x190F; // 24, 32, 56
                        break;
                }
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -3000.0f, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 0.5f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_CO_601B640);
                Matrix_Pop(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, 3000.0f, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 0.5f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_CO_601B640);
            } else {
                gGroundSurface = SURFACE_GRASS;
                gBgColor = 0x845; // 8, 8, 32
                for (i = 0; i < ARRAY_COUNT(sGroundPositions360x); i++) {
                    Matrix_Push(&gGfxMatrix);
                    Matrix_Translate(gGfxMatrix, sGroundPositions360x[i], 0.0f, sGroundPositions360z[i], MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_CO_601EAA0);
                    Matrix_Pop(&gGfxMatrix);
                }
            }
            break;
        case LEVEL_VENOM_1:
        case LEVEL_MACBETH:
            RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
            switch (gCurrentLevel) {
                case LEVEL_VENOM_1:
                    sp1C4 = D_VE1_6006750;
                    sp1C0 = D_VE1_60066D0;
                    gDPLoadTextureBlock(gMasterDisp++, sp1C4, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
                                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD,
                                        G_TX_NOLOD);
                    break;
                case LEVEL_MACBETH:
                    sp1C4 = D_MA_602DCB8;
                    sp1C0 = D_MA_60306D0;
                    gDPLoadTextureBlock(gMasterDisp++, sp1C4, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
                                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD,
                                        G_TX_NOLOD);
                    break;
            }
            gDPSetTextureImage(gMasterDisp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sp1C4);
            temp_s0 = fabsf(Math_ModF(2.0f * (gPathTexScroll * 0.2133333f), 128.0f));
            temp_fv0 = Math_ModF((10000.0f - gPlayer[gPlayerNum].xPath) * 0.32f, 128.0f);
            gDPSetupTile(gMasterDisp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, temp_fv0, temp_s0,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -3000.0f, MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 0.5f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, sp1C0);
            Matrix_Pop(&gGfxMatrix);
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, 3000.0f, MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 0.5f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, sp1C0);
            Matrix_Pop(&gGfxMatrix);
            break;
        case LEVEL_TRAINING:
            RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
            if (gLevelMode == LEVELMODE_ON_RAILS) {
                if (gPathTexScroll > 290.0f) {
                    gPathTexScroll -= 290.0f;
                }
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -3000.0f + gPathTexScroll, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 0.5f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_TR_6005880);
                Matrix_Pop(&gGfxMatrix);
                if (1) {}
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, 3000.0f + gPathTexScroll, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 0.5f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_TR_6005880);
                Matrix_Pop(&gGfxMatrix);
            } else {
                for (i = 0; i < ARRAY_COUNT(sGroundPositions360x); i++) {
                    Matrix_Push(&gGfxMatrix);
                    Matrix_Translate(gGfxMatrix, sGroundPositions360x[i], 0.0f, sGroundPositions360z[i], MTXF_APPLY);
                    Matrix_Scale(gGfxMatrix, 1.5f, 1.0f, 1.0f, MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_TR_6005880);
                    Matrix_Pop(&gGfxMatrix);
                }
            }
            break;
        case LEVEL_AQUAS:
            RCP_SetupDL(&gMasterDisp, SETUPDL_20);
            sp1C0 = D_AQ_600AB10;
            gSPFogPosition(gMasterDisp++, gFogNear, gFogFar);
            if ((D_bg_8015F964 == 0) && ((gAqDrawMode == 0) || (gAqDrawMode == 2))) {

                gDPLoadTileTexture(gMasterDisp++, SEGMENTED_TO_VIRTUAL(D_AQ_600AB68), G_IM_FMT_RGBA, G_IM_SIZ_16b, 32,
                                   32);
                gDPSetTextureImage(gMasterDisp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, SEGMENTED_TO_VIRTUAL(D_AQ_600AB68));
                temp_s0 = fabsf(Math_ModF(2.0f * (gPathTexScroll * 0.2133333f), 128.0f));
                temp_fv0 = Math_ModF((10000.0f - gPlayer[gPlayerNum].xPath) * 0.32f, 128.0f);
                gDPSetupTile(gMasterDisp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, temp_fv0, temp_s0,
                             G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);

                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -3000.0f, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 0.5f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, sp1C0);
                Matrix_Pop(&gGfxMatrix);
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, 3000.0f, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 0.5f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, sp1C0);
                Matrix_Pop(&gGfxMatrix);
            }
            if ((D_bg_8015F964 != 0) || (gAqDrawMode == 0)) {
                gDPLoadTileTexture(gMasterDisp++, SEGMENTED_TO_VIRTUAL(D_AQ_602ACC0), G_IM_FMT_RGBA, G_IM_SIZ_16b, 32,
                                   32);
                gDPSetTextureImage(gMasterDisp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, SEGMENTED_TO_VIRTUAL(D_AQ_602ACC0));
                temp_s0 = fabsf(Math_ModF(2.0f * (gPathTexScroll * 0.2133333f), 128.0f));
                temp_fv0 = Math_ModF((10000.0f - gPlayer[gPlayerNum].xPath) * 0.32f, 128.0f);
                gDPSetupTile(gMasterDisp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, temp_fv0, temp_s0,
                             G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
                if (gAqDrawMode != 0) {
                    RCP_SetupDL(&gMasterDisp, SETUPDL_47);
                } else {
                    RCP_SetupDL(&gMasterDisp, SETUPDL_37);
                }
                if ((gPlayer[0].state_1C8 == PLAYERSTATE_1C8_LEVEL_INTRO) && (gPlayer[0].csState < 2)) {
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
                } else if (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_LEVEL_COMPLETE) {
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, D_bg_8015F974, D_bg_8015F978, D_bg_8015F97C,
                                    D_bg_8015F980);
                } else {
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, (s32) D_AQ_801C4188);
                }
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, 0.0f, D_bg_8015F970, -3000.0f, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, 2.0f, 1.0f, 0.5f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_AQ_602AC40);
                Matrix_Pop(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, 0.0f, D_bg_8015F970, 3000.0f, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, 2.0f, 1.0f, 0.5f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_AQ_602AC40);
            }
            break;
        case LEVEL_FORTUNA:
        case LEVEL_KATINA:
        case LEVEL_BOLSE:
        case LEVEL_VENOM_2:
            if ((gGroundClipMode != 0) || (gCurrentLevel == LEVEL_BOLSE)) {
                RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
            } else {
                RCP_SetupDL_20(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
            }
            for (i = 0; i < ARRAY_COUNT(sGroundPositions360x); i++) {
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, sGroundPositions360x[i], 0.0f, sGroundPositions360z[i], MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                if (gCurrentLevel == LEVEL_FORTUNA) {
                    gSPDisplayList(gMasterDisp++, D_FO_6001360);
                } else if (gCurrentLevel == LEVEL_KATINA) {
                    gSPDisplayList(gMasterDisp++, D_KA_6009250);
                } else if (gCurrentLevel == LEVEL_BOLSE) {
                    gSPDisplayList(gMasterDisp++, D_BO_600A810);
                } else if (gCurrentLevel == LEVEL_VENOM_2) {
                    gSPDisplayList(gMasterDisp++, D_MA_6010700);
                }
                Matrix_Pop(&gGfxMatrix);
            }
            break;
        case LEVEL_VERSUS:
            if (gGroundClipMode != 0) {
                RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
            } else {
                RCP_SetupDL_20(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
            }
            for (i = 0; i < ARRAY_COUNT(sGroundPositions360x); i++) {
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, sGroundPositions360x[i], 0.0f, sGroundPositions360z[i], MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                if (gVersusStage == VS_STAGE_CORNERIA) {
                    gSPDisplayList(gMasterDisp++, D_versus_3018800);
                } else {
                    gSPDisplayList(gMasterDisp++, D_versus_30160A0);
                }
                Matrix_Pop(&gGfxMatrix);
            }
            break;
        case LEVEL_SOLAR:
            RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
            Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -2000.0f, MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, 3.0f, 2.0f, 3.0f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            if ((gGameFrameCount % 2) != 0) {
                gSPDisplayList(gMasterDisp++, D_SO_60005B0);
            } else {
                gSPDisplayList(gMasterDisp++, D_SO_6002E60);
            }
            break;
        case LEVEL_ZONESS:
            RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
            Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -1500.0f, MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, 3.0f, 2.0f, 3.0f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            if ((gGameFrameCount % 2) != 0) {
                gSPDisplayList(gMasterDisp++, D_ZO_6008830);
            } else {
                gSPDisplayList(gMasterDisp++, D_ZO_600B0E0);
            }
            break;
    }
    Matrix_Pop(&gGfxMatrix);
}

void func_bg_80042D38(void) {
    f32 xEye;
    f32 zEye;

    if (!gPlayer[gPlayerNum].cam.eye.x) {}
    if (!gPlayer[gPlayerNum].cam.eye.y) {} // all sorts of fake

    Matrix_Push(&gGfxMatrix);
    xEye = gPlayer[gPlayerNum].cam.eye.x;
    if (0) {}
    zEye = gPlayer[gPlayerNum].cam.eye.z;
    Matrix_Translate(gGfxMatrix, xEye, 2.0f + gCameraShakeY, zEye, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, 1.5f, 1.0f, 1.0f, MTXF_APPLY);
    RCP_SetupDL_37(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 125);
    Matrix_SetGfxMtx(&gMasterDisp);
    if ((gGameFrameCount % 2) != 0) {
        gSPDisplayList(gMasterDisp++, D_AQ_602C030);
    } else {
        gSPDisplayList(gMasterDisp++, D_AQ_602C088);
    }
    Matrix_Pop(&gGfxMatrix);
}
