#include "global.h"
#include "assets/ast_blue_marine.h"
#include "assets/ast_arwing.h"
#include "assets/ast_bg_space.h"
#include "assets/ast_bg_planet.h"
#include "assets/ast_corneria.h"
#include "assets/ast_meteo.h"
#include "assets/ast_training.h"
#include "assets/ast_sector_x.h"
#include "assets/ast_sector_y.h"
#include "assets/ast_aquas.h"
#include "assets/ast_macbeth.h"
#include "assets/ast_titania.h"
#include "assets/ast_area_6.h"
#include "assets/ast_A_ti.h"
#include "assets/ast_ve1_boss.h"
#include "assets/ast_enmy_planet.h"
#include "assets/ast_zoness.h"

// rodata
const char D_800D7230[] = "Enm->wrk3=<%d>\n";
const char D_800D7240[] = "a=<%d>\n";
const char D_800D7248[] = "a=<%d>\n";

s32 BonusText_Display(f32 xPos, f32 yPos, f32 zPos, s32 hits) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gBonusText); i++) {
        if (gBonusText[i].hits == BONUS_TEXT_FREE) {
            gBonusText[i].hits = hits;
            gBonusText[i].pos.x = xPos;
            gBonusText[i].pos.y = yPos;
            gBonusText[i].pos.z = zPos;
            gBonusText[i].rise = 0.0f;
            gBonusText[i].timer = 65;
            break;
        }
    }
}

void BonusText_Update(void) {
    BonusText* bonus;
    s32 i;

    for (i = 0, bonus = gBonusText; i < ARRAY_COUNT(gBonusText); i++, bonus++) {
        if (bonus->hits != BONUS_TEXT_FREE) {
            if (bonus->timer != 0) {
                bonus->timer -= 1; // can't be --
            }
            if (bonus->timer == 0) {
                bonus->hits = BONUS_TEXT_FREE;
            }

            if (gLevelMode == LEVELMODE_ON_RAILS) {
                bonus->pos.z -= gPathVelZ;
            } else if (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_ACTIVE) {
                bonus->pos.x += gPlayer[0].vel.x;
                bonus->pos.z += gPlayer[0].vel.z;
            }

            if (bonus->timer < 45) {
                Math_SmoothStepToF(&bonus->rise, 300.0f, 0.1f, 20.0f, 0.0f);
            }
        }
    }
}

static Gfx* sLargeBonusDLs[4][2] = {
    { D_1016410, D_1003130 },
    { D_10162A0, D_1003130 },
    { D_1016130, D_1003130 },
    { D_1015FC0, D_1003130 },
};

static Gfx* sSmallBonusDLs[10] = {
    D_1015810, D_1016410, D_10162A0, D_1016130, D_1015FC0, D_1015E50, D_10156A0, D_1015CE0, D_1015B70, D_1015320,
};

void BonusText_Draw(BonusText* bonus) {
    s32 dlIndex;
    Vec3f sp60 = { 0.0f, 0.0f, 0.0f };
    Vec3f sp54;
    f32 sp50;

    if (bonus->timer <= 45) {
        Matrix_Translate(gGfxMatrix, bonus->pos.x, bonus->pos.y, bonus->pos.z + gPathProgress, MTXF_APPLY);
        Matrix_MultVec3f(gGfxMatrix, &sp60, &sp54);

        if ((fabsf(sp54.x) < 20000.0f) && (fabsf(sp54.y) < 20000.0f)) {
            if ((sp54.z < 0.0f) && (sp54.z > -20000.0f)) {
                sp50 = (VEC3F_MAG(&sp54)) * 0.0015f * 0.2f;
                Matrix_RotateY(gGfxMatrix, -gPlayer[gPlayerNum].camYaw, MTXF_APPLY);
                Matrix_RotateX(gGfxMatrix, gPlayer[gPlayerNum].camPitch, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, sp50, sp50, 1.0f, MTXF_APPLY);
                Matrix_Translate(gGfxMatrix, 0.0f, bonus->rise, 0.0f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);

                if (bonus->hits <= 10) {
                    gSPDisplayList(gMasterDisp++, D_1015980);
                    gSPDisplayList(gMasterDisp++, sSmallBonusDLs[bonus->hits - 1]);
                } else if (bonus->hits == BONUS_TEXT_1UP) {
                    gSPDisplayList(gMasterDisp++, D_1011F20);
                } else if (bonus->hits == BONUS_TEXT_GREAT) {
                    gSPDisplayList(gMasterDisp++, D_1016580);
                } else {
                    gSPDisplayList(gMasterDisp++, D_1015980);
                    switch (bonus->hits) {
                        case 20:
                            dlIndex = 0;
                            break;
                        case 30:
                            dlIndex = 1;
                            break;
                        case 40:
                            dlIndex = 2;
                            break;
                        case 50:
                        default:
                            dlIndex = 3;
                            break;
                    }
                    gSPDisplayList(gMasterDisp++, sLargeBonusDLs[dlIndex][0]);
                    gSPDisplayList(gMasterDisp++, sLargeBonusDLs[dlIndex][1]);
                }
            } else {
                bonus->hits = BONUS_TEXT_FREE;
            }
        }
    }
}

void BonusText_DrawAll(void) {
    BonusText* bonus;
    s32 i;

    RCP_SetupDL(&gMasterDisp, SETUPDL_62);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    for (i = 0, bonus = gBonusText; i < ARRAY_COUNT(gBonusText); i++, bonus++) {
        if (bonus->hits != 0) {
            Matrix_Push(&gGfxMatrix);
            BonusText_Draw(bonus);
            Matrix_Pop(&gGfxMatrix);
        }
    }
}

Effect* func_effect_8007783C(ObjectId objId) {
    Effect* effect;
    s32 i;

    for (i = 0, effect = gEffects; i < ARRAY_COUNT(gEffects); i++, effect++) {
        if (effect->obj.status == OBJ_FREE) {
            Effect_Initialize(effect);
            effect->obj.status = OBJ_ACTIVE;
            effect->obj.id = objId;
            Object_SetInfo(&effect->info, effect->obj.id);
            break;
        }
    }
    if (i == ARRAY_COUNT(gEffects)) {
        effect = NULL;
    }
    return effect;
}

void func_effect_800778C4(Effect* effect, f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 scale2) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = OBJ_EFFECT_FIRE_SMOKE;

    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;

    effect->vel.x = xVel;
    effect->vel.y = yVel;
    effect->vel.z = zVel;

    effect->scale2 = scale2;
    effect->unk_4C = 0;
    effect->scale1 = 0.5f;
    effect->obj.rot.z = RAND_FLOAT(360.0f);
    Object_SetInfo(&effect->info, effect->obj.id);
    effect->unk_44 = 255;
}

void func_effect_8007797C(f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 scale2) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            func_effect_800778C4(&gEffects[i], xPos, yPos, zPos, xVel, yVel, zVel, scale2);
            break;
        }
    }
}

void func_effect_80077A00(Effect* effect) {
    Graphics_SetScaleMtx(effect->scale2);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, effect->unk_44);
    gSPDisplayList(gMasterDisp++, D_arwing_3016B30);
}

void func_effect_80077A7C(Effect* effect) {
    RCP_SetupDL_49();
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, effect->unk_44);
    gDPSetEnvColor(gMasterDisp++, 255, 255, 255, effect->unk_44);
    Matrix_Scale(gGfxMatrix, effect->scale1, effect->scale2, 1.0f, MTXF_APPLY);
    Matrix_Translate(gGfxMatrix, 0.0f, 20.0f, 0.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_ZO_6024220);
    RCP_SetupDL(&gMasterDisp, SETUPDL_64);
}

void func_effect_80077B78(Effect* effect) {
}

void func_effect_80077B84(Effect* effect) {
    Graphics_SetScaleMtx(effect->scale2);

    if ((effect->scale1 == 71.0f) ||
        ((gPlayer[0].state_1C8 == PLAYERSTATE_1C8_LEVEL_COMPLETE) && (gCurrentLevel == LEVEL_CORNERIA))) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_38);
    } else {
        RCP_SetupDL(&gMasterDisp, SETUPDL_67);
    }

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, effect->unk_44);

    switch (effect->unk_4C) {
        case 0:
            gDPSetEnvColor(gMasterDisp++, 0, 128, 255, effect->unk_44);
            break;
        case 1:
            gDPSetEnvColor(gMasterDisp++, 255, 64, 255, effect->unk_44);
            break;
        case 2:
            gDPSetEnvColor(gMasterDisp++, 255, 128, 0, effect->unk_44);
            break;
        case 3:
            gDPSetEnvColor(gMasterDisp++, 255, 48, 48, effect->unk_44);
            break;
        case 4:
            gDPSetEnvColor(gMasterDisp++, 255, 255, 48, effect->unk_44);
            break;
        case 5:
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, effect->unk_44);
            gDPSetEnvColor(gMasterDisp++, 255, 32, 32, effect->unk_44);
            break;
        case 6:
            if (gCurrentLevel == LEVEL_BOLSE) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_38);
            }
            switch ((effect->index + gGameFrameCount) % 4U) {
                case 0:
                    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 0, 0, effect->unk_44);
                    break;
                case 1:
                    gDPSetPrimColor(gMasterDisp++, 0, 0, 0, 255, 0, effect->unk_44);
                    break;
                case 2:
                    gDPSetPrimColor(gMasterDisp++, 0, 0, 0, 0, 255, effect->unk_44);
                    break;
                case 3:
                    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, effect->unk_44);
                    break;
            }
            gDPSetEnvColor(gMasterDisp++, 0, 0, 0, effect->unk_44);
            break;
        case 7:
            gDPSetEnvColor(gMasterDisp++, 48, 48, 255, effect->unk_44);
            break;
        case 10:
            gDPSetEnvColor(gMasterDisp++, 255, 255, 32, effect->unk_44);
            break;
        case 11:
            gDPSetEnvColor(gMasterDisp++, 255, 32, 32, effect->unk_44);
            break;
        case 12:
            gDPSetEnvColor(gMasterDisp++, 32, 255, 32, effect->unk_44);
            break;
        case 13:
            gDPSetEnvColor(gMasterDisp++, 32, 32, 255, effect->unk_44);
            break;
    }

    gSPDisplayList(gMasterDisp++, D_1024AC0);
    RCP_SetupDL(&gMasterDisp, SETUPDL_64);
}

void func_effect_80078038(Effect* effect) {
    Graphics_SetScaleMtx(effect->scale2);
    RCP_SetupDL_49();
    RCP_SetupDL(&gMasterDisp, SETUPDL_38);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 64, 192, 255, effect->unk_44);
    gDPSetEnvColor(gMasterDisp++, 0, 0, 0, effect->unk_44);
    gSPDisplayList(gMasterDisp++, D_1024AC0);
    RCP_SetupDL(&gMasterDisp, SETUPDL_64);
}

// Possibly the little sparks of electricity that come off the arwing and landmaster when low on health
static f32 D_800D1534[][10] = {
    { 38.45957f, -65.08043f, 8.068213f, 87.01006f, -86.956184f, -71.82677f, 37.854507f, 46.845963f, 23.723173f,
      84.2551f },
    { -77.50479f, 86.4889f, -8.664565f, -74.90449f, -42.23121f, 49.20716f, -18.885563f, -47.375793f, -58.059227f,
      -2.498746f },
    { -74.84084f, -66.523506f, -71.39976f, 21.378086f, 28.324728f, 89.42064f, -85.24717f, -28.109077f, 31.949314f,
      5.697076f },
    { 58.005924f, 64.38876f, 50.419434f, -45.34431f, 60.55692f, 58.689392f, 28.175598f, -20.696762f, -13.056221f,
      36.156307f },
    { -72.78266f, -67.081665f, 57.92814f, -56.805496f, -51.114407f, 79.95429f, 37.474f, -62.60574f, -88.01894f,
      -69.37549f },
    { 52.336594f, 34.10212f, 55.353027f, 27.779789f, -38.374107f, -42.059826f, -80.53026f, 60.73118f, 38.044014f,
      -62.561646f },
    { -56.799488f, 0.500157f, -71.042145f, -28.663008f, 39.668713f, 36.233597f, -49.26364f, -85.028854f, 71.3247f,
      44.180447f },
    { 62.98788f, -68.41569f, -25.23802f, -89.18237f, -34.72465f, 77.61012f, 83.1443f, -66.71512f, 22.06076f,
      -60.077705f },
    { 34.752354f, -61.9954f, 87.50011f, 40.39249f, 25.152748f, -68.16201f, 47.702785f, -44.814285f, 84.87108f,
      71.68733f },
    { 30.700006f, 71.38295f, 18.13302f, -45.159817f, -55.795097f, -52.275223f, 3.216162f, 85.24068f, 49.815186f,
      -71.90831f },
    { -53.34575f, 85.58262f, 86.26517f, -60.348373f, 26.2602f, -58.774044f, -58.923035f, 4.206734f, 23.082275f,
      -74.58816f },
    { -0.396795f, 74.36148f, 73.00557f, 2.217007f, -77.69297f, -55.191216f, 55.187286f, -53.86457f, -88.575294f,
      35.68634f },
    { 41.014538f, -79.47855f, -29.881096f, 70.93344f, -86.55003f, 60.424816f, 51.190754f, -66.513695f, 73.50617f,
      41.706547f },
};

void func_effect_800780F8(Effect* effect) {
    s32 i;

    if (effect->unk_4A > 10) {
        if (((effect->index + gGameFrameCount) % 2) == 0) {
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 128, 128, 32);
        } else {
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 128, 128, 128);
        }
    } else if (((effect->index + gGameFrameCount) % 2) == 0) {
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
    } else {
        gDPSetPrimColor(gMasterDisp++, 0, 0, 96, 96, 255, 255);
    }

    Graphics_SetScaleMtx(effect->scale2);

    for (i = 0; i < 10; i++) {
        if ((i >= effect->unk_48) && (i < effect->unk_46)) {
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, 0.0f, -60.0f, 0.0f, MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, 0.8f, 3.0f, 1.0f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_102F5E0);
            Matrix_Pop(&gGfxMatrix);
        }
        Matrix_Translate(gGfxMatrix, 0.0f, -120.0f, 0.0f, MTXF_APPLY);
        Matrix_RotateZ(gGfxMatrix, D_800D1534[effect->unk_4C][i] * M_DTOR, MTXF_APPLY);
    }
}

void func_effect_800783C0(Effect* effect) {
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, effect->unk_44);
    Graphics_SetScaleMtx(effect->scale2);
    gSPDisplayList(gMasterDisp++, D_BG_SPACE_2006F50);
}

void func_effect_80078438(Effect* effect) {
    Graphics_SetScaleMtx(effect->scale2);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, effect->unk_4A);
    gSPDisplayList(gMasterDisp++, D_102A8A0);
}

void func_effect_800784B4(Effect* effect) {
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, effect->unk_46);
    Graphics_SetScaleMtx(effect->scale2);
    Matrix_RotateX(gGfxMatrix, M_PI / 2, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_BG_PLANET_200D750);
}

void func_effect_80078550(Effect* effect) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_67);
    Graphics_SetScaleMtx(effect->scale2);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, effect->unk_4A);
    gDPSetEnvColor(gMasterDisp++, 101, 138, 153, 255);
    gSPDisplayList(gMasterDisp++, D_blue_marine_3000660);
    RCP_SetupDL(&gMasterDisp, SETUPDL_64);
}

void func_effect_80078604(Effect* effect) {
    if (effect->timer_50 == 0) {
        Graphics_SetScaleMtx(effect->scale2);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, effect->unk_44);
        gSPDisplayList(gMasterDisp++, D_BG_PLANET_20112C0);
    }
}

void func_effect_8007868C(Effect* effect) {
    RCP_SetupDL_60(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
    Matrix_Scale(gGfxMatrix, effect->scale2, effect->scale2, effect->scale2, MTXF_APPLY);
    if (effect->unk_44 >= 2) {
        Matrix_RotateX(gGfxMatrix, M_PI / 2, MTXF_APPLY);
    }
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_1029780);
    RCP_SetupDL(&gMasterDisp, SETUPDL_64);
}

void func_effect_8007879C(Effect* effect) {
    RCP_SetupDL_60(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
    Matrix_Scale(gGfxMatrix, effect->scale2 * 0.6f, 1.0f, effect->scale2 * 3.5f, MTXF_APPLY);
    Matrix_RotateX(gGfxMatrix, M_PI / 2, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_1029780);
    RCP_SetupDL(&gMasterDisp, SETUPDL_64);
}

static s32 D_800D173C[] = { 255, 255, 255, 0, 0, 0, 255, 0, 255, 0, 0, 0, 255, 255, 0, 0, 0, 255, 0, 0 };

void func_effect_800788B0(Effect* effect) {
    s32 temp_ft3;
    s32 tmp;

    switch (gCurrentLevel) {
        case LEVEL_METEO:
            Graphics_SetScaleMtx(effect->scale2);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 128, 128, 128, 255);
            gSPDisplayList(gMasterDisp++, D_ME_601FF80);
            break;

        case LEVEL_AQUAS:
            RCP_SetupDL(&gMasterDisp, SETUPDL_67);
            temp_ft3 = Math_ModF(effect->index, 4.0f);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, (s32) effect->scale1);
            tmp = temp_ft3 * 4.0f;
            gDPSetEnvColor(gMasterDisp++, D_800D173C[tmp + 0], D_800D173C[tmp + 1], D_800D173C[tmp + 2], 255);
            Graphics_SetScaleMtx(effect->scale2);
            gSPDisplayList(gMasterDisp++, D_1024AC0);
            RCP_SetupDL(&gMasterDisp, SETUPDL_64);
            break;
    }
}

void func_effect_80078A64(Effect* effect) {
    Graphics_SetScaleMtx(effect->scale2);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, effect->unk_44);
    gSPDisplayList(gMasterDisp++, D_BG_PLANET_20112C0);
}

void func_effect_80078AE0(void* effect) {
}

void func_effect_80078AEC(Effect* effect) {
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 180);
    Graphics_SetScaleMtx(effect->scale2 * (13.0f + ((s32) (gGameFrameCount % 2U) * 2.5f)));
    gSPDisplayList(gMasterDisp++, D_102ED50);
}

void func_effect_80078B8C(Effect* effect) {
    RCP_SetupDL_21();
    gSPDisplayList(gMasterDisp++, D_101ABD0);
    RCP_SetupDL(&gMasterDisp, SETUPDL_64);
}

void func_effect_80078BE0(Effect* effect) {
    f32 var_fv0;

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 160);

    var_fv0 = 3.0f;
    if ((gGameFrameCount % 2) != 0) {
        var_fv0 *= 1.2f;
    }
    Graphics_SetScaleMtx(effect->scale2 * var_fv0);
    gSPDisplayList(gMasterDisp++, D_SX_600F8A0);
}

void func_effect_80078C84(Effect* effect) {
    Graphics_SetScaleMtx(effect->scale2);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 192);
    gSPDisplayList(gMasterDisp++, D_ME_6000A80);
}

void func_effect_80078CE8(Effect* effect) {
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, effect->unk_4A);
    Graphics_SetScaleMtx(effect->scale2);
    gSPDisplayList(gMasterDisp++, D_CO_6033000);
}

void func_effect_80078D60(Effect* effect, f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = OBJ_EFFECT_393;
    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;
    effect->scale2 = scale2;

    if (scale2 == 3.1f) {
        effect->vel.x = gActors[8].vel.x;
        effect->vel.y = gActors[8].vel.y;
        effect->vel.z = gActors[8].vel.z;
    }
    if (scale2 != 30.0f) {
        effect->state = 1;
    }
    if (scale2 == 3.5f) {
        effect->state = 2;
    }

    effect->timer_50 = 14;
    Object_SetInfo(&effect->info, effect->obj.id);
}

void func_effect_80078E50(f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            func_effect_80078D60(&gEffects[i], xPos, yPos, zPos, scale2);
            break;
        }
    }
}

void func_effect_80078EBC(Effect* effect) {
    if (effect->state == 2) {
        effect->vel.x = gPlayer[0].vel.x;
        effect->vel.y = gPlayer[0].vel.y;
        effect->vel.z = gPlayer[0].vel.z;
    }

    effect->obj.rot.z += 35.0f;

    if (effect->timer_50 >= 7) {
        effect->scale1 += 0.25f;
    } else {
        effect->scale1 -= 0.25f;
    }
    if (effect->scale1 <= 0.0f) {
        Object_Kill(&effect->obj, effect->sfxSource);
    }
}

void func_effect_80078F78(Effect* effect) {
    if (effect->state != 0) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_67);
    } else {
        RCP_SetupDL(&gMasterDisp, SETUPDL_63);
    }
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
    gDPSetEnvColor(gMasterDisp++, 255, 255, 0, 255);
    Graphics_SetScaleMtx(effect->scale2 * effect->scale1);
    gSPDisplayList(gMasterDisp++, D_101C2E0);
    RCP_SetupDL(&gMasterDisp, SETUPDL_64);
}

void func_effect_8007905C(Effect* effect, f32 xPos, f32 yPos, f32 zPos, f32 scale2, u8 arg5) {
    Vec3f sp54;
    Vec3f sp48;
    Vec3f sp3C;
    f32 sp38;
    f32 xAng;
    f32 yAng;

    Effect_Initialize(effect);
    effect->obj.status = OBJ_ACTIVE;
    effect->obj.id = OBJ_EFFECT_357;

    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;

    effect->unk_4C = arg5;

    if (scale2 == 1.6f) {
        effect->vel.x = (xPos - gBosses[1].obj.pos.x) * 0.1f;
        effect->vel.z = (zPos - gBosses[1].obj.pos.z) * 0.1f;
    } else if (scale2 == 1.3f) {
        effect->vel.x = (RAND_FLOAT(0.05f) + 0.03f) * xPos;
        effect->vel.z = (RAND_FLOAT(0.05f) + 0.03f) * zPos;
        effect->vel.y = 5.0f;
    } else if (scale2 == 1.55f) {
        effect->vel.x = RAND_FLOAT_CENTERED(10.0f);
        effect->vel.z = RAND_FLOAT_CENTERED(10.0f);
    } else if ((gCurrentLevel == LEVEL_BOLSE) && ((scale2 == 5.11f) || (scale2 == 7.22f))) {
        sp3C.x = gPlayer[0].pos.x;
        sp3C.y = gPlayer[0].pos.y;
        sp3C.z = gPlayer[0].pos.z;
        yAng = Math_Atan2F(sp3C.x - xPos, sp3C.z - zPos);
        sp38 = sqrtf(SQ(sp3C.x - xPos) + SQ(sp3C.z - zPos));
        xAng = -Math_Atan2F(sp3C.y - yPos, sp38);
        Matrix_RotateY(gCalcMatrix, yAng, MTXF_NEW);
        Matrix_RotateX(gCalcMatrix, xAng, MTXF_APPLY);
        sp54.x = RAND_FLOAT_CENTERED(50.0f);
        sp54.y = RAND_FLOAT_CENTERED(50.0f);
        sp54.z = RAND_FLOAT(10.0f) + 150.0f;
        Matrix_MultVec3f(gCalcMatrix, &sp54, &sp48);
        effect->vel.x = sp48.x;
        effect->vel.y = sp48.y;
        effect->vel.z = sp48.z;
    } else {
        effect->vel.y = (gLevelType == LEVELTYPE_PLANET) ? RAND_FLOAT(7.0f) + 7.0f : RAND_FLOAT_CENTERED(10.0f);
        effect->vel.x = RAND_FLOAT_CENTERED(10.0f);
        effect->vel.z = RAND_FLOAT_CENTERED(10.0f);
    }
    effect->scale2 = (RAND_FLOAT(0.8f) + 0.3f) * scale2;
    effect->timer_50 = RAND_INT(50.0f) + 70;
    effect->obj.rot.x = RAND_FLOAT(360.0f);
    effect->unk_60.x = RAND_FLOAT_CENTERED(30.0f);
    effect->unk_60.y = RAND_FLOAT_CENTERED(30.0f);
    effect->unk_60.z = RAND_FLOAT_CENTERED(30.0f);
    Object_SetInfo(&effect->info, effect->obj.id);
}

void func_effect_800794CC(f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    s32 i;

    for (i = 50; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            func_effect_8007905C(&gEffects[i], xPos, yPos, zPos, scale2, 0);
            break;
        }
    }
}

// Broken pieces and debris effect
void func_effect_8007953C(f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    s32 i;

    for (i = (ARRAY_COUNT(gEffects) - 20) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            func_effect_8007905C(&gEffects[i], xPos, yPos, zPos, scale2, 0);
            break;
        }
    }
}

void func_effect_800795AC(f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    s32 i;

    for (i = 0; i < 95; i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            func_effect_8007905C(&gEffects[i], xPos, yPos, zPos, scale2, 0);
            break;
        }
    }
}

void func_effect_80079618(f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    s32 i;

    for (i = 50; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            func_effect_8007905C(&gEffects[i], xPos, yPos, zPos, scale2, 1);
            break;
        }
    }
}

void func_effect_8007968C(Effect* effect) {
    if ((gCurrentLevel != LEVEL_MACBETH) || (effect->unk_44 != 7)) {
        if ((effect->timer_50 == 0) || (effect->obj.pos.y < gGroundHeight)) {
            Object_Kill(&effect->obj, effect->sfxSource);
        }
    } else {
        if (((gGameFrameCount % 4) == 0)) {
            func_effect_8007D2C8(effect->obj.pos.x, effect->obj.pos.y + 550.0f, effect->obj.pos.z, 10.0f);
        }
        if ((effect->timer_50 == 0) || (effect->obj.pos.y < (gGroundHeight - 100.0f))) {
            Object_Kill(&effect->obj, effect->sfxSource);
        }
    }

    effect->obj.rot.x += effect->unk_60.x;
    effect->obj.rot.y += effect->unk_60.y;
    effect->obj.rot.z += effect->unk_60.z;

    if (gLevelType == LEVELTYPE_PLANET) {
        effect->vel.y -= 0.5f;
    }

    if ((gCurrentLevel == LEVEL_BOLSE) && (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_LEVEL_COMPLETE) &&
        (gCsFrameCount > 175)) {
        effect->vel.x *= 0.95f;
        effect->vel.y *= 0.95f;
        effect->vel.z *= 0.95f;
    }

    if ((gCurrentLevel == LEVEL_MACBETH) && (effect->unk_44 == 10)) {
        effect->obj.rot.x = 0.0f;
        effect->obj.rot.y = 0.0f;
        if (effect->timer_50 >= 25) {
            effect->scale1 = 0.5f;
        } else if (effect->scale1 > 0.03) {
            effect->scale1 -= 0.02f;
        }
    }
}

bool func_effect_800798C4(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* data) {
    if ((limbIndex != 1) && (limbIndex != 5)) {
        *dList = NULL;
    }
    return false;
}

void func_effect_800798F0(Effect* effect) {
    Vec3f frameJointTable[50];

    if ((gCurrentLevel == LEVEL_BOLSE) && (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_LEVEL_COMPLETE)) {
        Display_SetSecondLight(&effect->obj.pos);
    }

    RCP_SetupDL(&gMasterDisp, SETUPDL_29);

    if (gCurrentLevel == LEVEL_KATINA) {
        gSPFogPosition(gMasterDisp++, gFogNear, 1005);
    }

    Graphics_SetScaleMtx(effect->scale2);

    switch (gCurrentLevel) {
        case LEVEL_MACBETH:
            switch (effect->unk_44) {
                case 1:
                    if ((effect->index % 2) != 0) {
                        gSPDisplayList(gMasterDisp++, D_MA_6022530);
                    } else {
                        gSPDisplayList(gMasterDisp++, D_MA_6022450);
                    }
                    break;

                case 2:
                    RCP_SetupDL(&gMasterDisp, SETUPDL_57);
                    if ((effect->index % 2) != 0) {
                        gSPDisplayList(gMasterDisp++, D_MA_601A7A0);
                    } else {
                        gSPDisplayList(gMasterDisp++, D_MA_60223C0);
                    }
                    RCP_SetupDL(&gMasterDisp, SETUPDL_29);
                    break;

                case 7:
                    Animation_GetFrameData(&D_MA_6027320, 0, frameJointTable);
                    Animation_DrawSkeleton(1, D_MA_602742C, frameJointTable, func_effect_800798C4, NULL, effect,
                                           &gIdentityMatrix);
                    break;

                case 8:
                    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                    gSPDisplayList(gMasterDisp++, D_MA_6020E60);
                    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
                    break;

                case 9:
                    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                    gSPDisplayList(gMasterDisp++, D_MA_6020A30);
                    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
                    break;

                case 10:
                    RCP_SetupDL(&gMasterDisp, SETUPDL_67);
                    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
                    gDPSetEnvColor(gMasterDisp++, 255, 80, 0, 255);
                    Graphics_SetScaleMtx(effect->scale1);
                    gSPDisplayList(gMasterDisp++, D_1024AC0);
                    break;

                case 11:
                    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                    gSPDisplayList(gMasterDisp++, D_MA_60200E0);
                    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
                    break;

                case 12:
                    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                    gSPDisplayList(gMasterDisp++, D_MA_600F2F0);
                    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
                    break;

                case 13:
                    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                    gSPDisplayList(gMasterDisp++, D_MA_6001A60);
                    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
                    break;

                case 14:
                    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                    gSPDisplayList(gMasterDisp++, D_MA_600F160);
                    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
                    break;

                case 15:
                    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                    gSPDisplayList(gMasterDisp++, D_MA_600F3D0);
                    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
                    break;

                case 16:
                    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                    gSPDisplayList(gMasterDisp++, D_SY_600F6C0);
                    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
                    break;

                case 17:
                    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                    gSPDisplayList(gMasterDisp++, D_MA_600F9B0);
                    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
                    break;

                default:
                    if ((effect->index % 2) != 0) {
                        gSPDisplayList(gMasterDisp++, D_10194C0);
                    } else {
                        gSPDisplayList(gMasterDisp++, D_1024290);
                    }
                    break;
            }
            break;

        case LEVEL_AQUAS:
            Matrix_SetGfxMtx(&gMasterDisp);
            RCP_SetupDL(&gMasterDisp, SETUPDL_60);
            gSPDisplayList(gMasterDisp++, D_AQ_600A220);
            break;

        default:
            switch (effect->unk_4C) {
                case 0:
                    if ((effect->index % 2) != 0) {
                        gSPDisplayList(gMasterDisp++, D_10194C0);
                    } else {
                        gSPDisplayList(gMasterDisp++, D_1024290);
                    }
                    break;

                case 1:
                    switch ((s32) (effect->index % 4U)) {
                        case 0:
                            Matrix_Scale(gGfxMatrix, 1.0f, 0.3f, 1.0f, MTXF_APPLY);
                            break;
                        case 1:
                            Matrix_Scale(gGfxMatrix, 0.3f, 1.0f, 1.0f, MTXF_APPLY);
                            break;
                        case 2:
                            Matrix_Scale(gGfxMatrix, 1.0f, 0.5f, 1.0f, MTXF_APPLY);
                            break;
                        case 3:
                            Matrix_Scale(gGfxMatrix, 0.5f, 1.0f, 1.0f, MTXF_APPLY);
                            break;
                    }
                    Matrix_SetGfxMtx(&gMasterDisp);
                    RCP_SetupDL(&gMasterDisp, SETUPDL_57);
                    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                    gSPDisplayList(gMasterDisp++, D_1021E20);
                    RCP_SetupDL(&gMasterDisp, SETUPDL_64);
                    break;
            }
            break;
    }

    RCP_SetupDL(&gMasterDisp, SETUPDL_64);

    if (gCurrentLevel == LEVEL_KATINA) {
        gSPFogPosition(gMasterDisp++, gFogNear, gFogFar);
    }
}

void func_effect_8007A28C(Effect* effect) {
    Texture_Scroll(D_10190C0, 16, 32, 0);
    gGroundClipMode = 2;
    effect->obj.rot.y += 1.0f;
    Math_SmoothStepToF(&effect->scale2, effect->scale1, 0.05f, 1.5f, 0.001f);

    if (effect->timer_50 > 10) {
        D_ctx_801779A8[0] = 60.0f;
    }
    if (effect->timer_50 == 48) {
        gFillScreenAlpha = 150;
    }
    if (effect->timer_50 > 45) {
        gFillScreenAlphaTarget = 0;
        gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
    }

    gFillScreenAlphaStep = 3;

    if (effect->timer_50 == 0) {
        effect->unk_44 -= 2;
        if (effect->unk_44 < 0) {
            effect->unk_44 = 0;
            Object_Kill(&effect->obj, effect->sfxSource);
            gGroundClipMode = 0;
        }
    }
}

void func_effect_8007A3C0(Effect* effect) {
    if (gReflectY > 0) {
        Matrix_Scale(gGfxMatrix, effect->scale2, effect->scale2, effect->scale2, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        RCP_SetupDL_64_2();
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, effect->unk_44);
        gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
        gSPDisplayList(gMasterDisp++, D_10182C0);
        gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
        RCP_SetupDL_64_2();
    }
}

void func_effect_8007A4B8(Effect* effect, f32 xPos, f32 yPos, f32 zPos, f32 scale1) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = OBJ_EFFECT_383;
    effect->scale1 = scale1;
    effect->timer_50 = 50;
    effect->unk_44 = 200;

    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;

    AUDIO_PLAY_SFX(NA_SE_EN_STAR_EXPLOSION, effect->sfxSource, 4);
    Object_SetInfo(&effect->info, effect->obj.id);
}

void func_effect_8007A568(f32 xPos, f32 yPos, f32 zPos, f32 scale1) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            func_effect_8007A4B8(&gEffects[i], xPos, yPos, zPos, scale1);
            break;
        }
    }
    func_effect_8007B344(xPos, yPos, zPos, 80.0f, 4);
}

void func_effect_8007A5F8(Effect* effect, Vec3f* pos, u32 sfxId) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_ACTIVE;
    effect->obj.id = OBJ_EFFECT_373;

    effect->obj.pos.x = pos->x;
    effect->obj.pos.y = pos->y;
    effect->obj.pos.z = pos->z;

    effect->timer_50 = 50;

    if ((sfxId == NA_SE_OB_EXPLOSION_S) || (sfxId == NA_SE_OB_SMOKE)) {
        AUDIO_PLAY_SFX(sfxId, effect->sfxSource, 0);
        if (sfxId == NA_SE_OB_SMOKE) {
            effect->timer_50 = 300;
        }
    } else {
        AUDIO_PLAY_SFX(sfxId, effect->sfxSource, 4);
    }
    Object_SetInfo(&effect->info, effect->obj.id);
}

void func_effect_8007A6F0(Vec3f* pos, s32 sfxId) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            func_effect_8007A5F8(&gEffects[i], pos, sfxId);
            break;
        }
    }
}

void func_effect_8007A748(Effect* effect) {
    if (effect->timer_50 == 0) {
        Object_Kill(&effect->obj, effect->sfxSource);
    }
}

bool func_effect_8007A774(Player* player, Effect* effect, f32 arg2) {
    if ((fabsf(player->trueZpos - effect->obj.pos.z) < arg2) && (fabsf(player->pos.x - effect->obj.pos.x) < arg2) &&
        (fabsf(player->pos.y - effect->obj.pos.y) < arg2) && (player->timer_498 == 0)) {
        Player_ApplyDamage(player, 0, effect->info.damage);
        return true;
    } else {
        return false;
    }
}

void func_effect_8007A818(Effect* effect, f32 xPos, f32 yPos, f32 zPos, f32 scale1, u8 arg5, u8 arg6, u16 arg7) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = OBJ_EFFECT_359;

    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;

    effect->scale1 = scale1;
    effect->unk_44 = arg5;
    effect->unk_46 = arg6;
    effect->unk_60.z = RAND_FLOAT_CENTERED(10.0f);
    effect->unk_60.y = scale1 * 0.1f;
    if (arg7 != 0) {
        effect->vel.x = RAND_FLOAT_CENTERED(30.0f);
    }
    Object_SetInfo(&effect->info, effect->obj.id);
}

void func_effect_8007A900(f32 xPos, f32 yPos, f32 zPos, f32 scale1, u8 arg4, u8 arg5, u16 arg6) {
    s32 i;

    if (gCurrentLevel == LEVEL_TITANIA) {
        for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
            if (gEffects[i].obj.status == OBJ_FREE) {
                func_effect_8007A818(&gEffects[i], xPos, yPos, zPos, scale1, arg4, arg5, arg6);
                break;
            }
        }
    }
}

void func_effect_8007A994(Effect* effect) {
    Math_SmoothStepToF(&effect->scale2, effect->scale1, 0.1f, 10.0f, 0.01f);
    effect->obj.rot.z += effect->unk_60.z;
    effect->vel.y += effect->unk_60.y;

    if ((effect->unk_4A % 2) != 0) {
        effect->unk_48++;
        if (effect->unk_48 > 5) {
            effect->unk_48 = 5;
        }
    }

    effect->unk_44 -= effect->unk_46;
    if (effect->unk_44 <= 20) {
        Object_Kill(&effect->obj, effect->sfxSource);
    }
    effect->unk_4A++;
}

static Gfx* D_800D178C[] = { D_TI_6003440, D_TI_60034E0, D_TI_6003580, D_TI_6003620, D_TI_60036C0, D_TI_6003760 };

void func_effect_8007AA60(Effect* effect) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_68);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 31, 10, 00, effect->unk_44);
    gDPSetEnvColor(gMasterDisp++, 141, 73, 5, 0);
    Matrix_Scale(gGfxMatrix, effect->scale2, effect->scale2, 1.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_800D178C[effect->unk_4C]);
    effect->unk_4C = effect->unk_48;
    RCP_SetupDL(&gMasterDisp, SETUPDL_64);
}

void func_effect_8007AB50(Effect* effect) {
    if (effect->state == 0) {
        Math_SmoothStepToF(&effect->scale2, effect->scale1, 0.1f, 10.0f, 0.0f);
        effect->unk_44 -= 20;
        if (effect->unk_44 < 0) {
            Object_Kill(&effect->obj, effect->sfxSource);
        }
    } else {
        Math_SmoothStepToF(&effect->scale2, effect->scale1, 0.1f, 10.0f, 0.0f);
        effect->unk_44 -= 10;
        if (effect->unk_44 < 0) {
            Object_Kill(&effect->obj, effect->sfxSource);
        }
    }
}

void func_effect_8007AC0C(Effect* effect, f32 xPos, f32 unused_posY, f32 zPos, f32 scale2, f32 scale1, f32 yRot) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = OBJ_EFFECT_372;

    effect->obj.pos.x = xPos;
    effect->obj.pos.y = gGroundHeight;
    effect->obj.pos.z = zPos;

    effect->unk_44 = 180;
    effect->scale2 = scale2;
    effect->scale1 = scale1;
    effect->obj.rot.y = yRot;
    effect->vel.x = gPlayer[0].vel.x * 0.6f;
    effect->vel.z = gPlayer[0].vel.z * 0.6; // Forgotten f means bad codegen
    Object_SetInfo(&effect->info, effect->obj.id);
}

void func_effect_8007ACE0(f32 xPos, f32 yPos, f32 zPos, f32 scale2, f32 scale1, f32 yRot) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            func_effect_8007AC0C(&gEffects[i], xPos, yPos, zPos, scale2, scale1, yRot);
            break;
        }
    }
}

void func_effect_8007AD58(Effect* effect, f32 xPos, f32 unused_posY, f32 zPos, f32 scale2, f32 scale1, f32 yRot) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = OBJ_EFFECT_372;
    effect->state = 1;

    effect->obj.pos.x = xPos;
    effect->obj.pos.y = gGroundHeight;
    effect->obj.pos.z = zPos;

    effect->unk_44 = 180;
    effect->scale2 = scale2;
    effect->scale1 = scale1;
    effect->obj.rot.y = yRot;
    Object_SetInfo(&effect->info, effect->obj.id);
}

void func_effect_8007ADF4(f32 xPos, f32 yPos, f32 zPos, f32 scale2, f32 scale1) {
    f32 cosf;
    f32 sinf;
    f32 yRot;
    s32 i;
    s32 j;

    for (yRot = 11.25f, i = 0; i < 16; i++, yRot += 22.5f) {
        for (j = 0; j < ARRAY_COUNT(gEffects); j++) {
            if (gEffects[j].obj.status == OBJ_FREE) {
                sinf = SIN_DEG(yRot) * scale1 * 20.0f;
                cosf = COS_DEG(yRot) * scale1 * 20.0f;
                func_effect_8007AD58(&gEffects[j], xPos + sinf, yPos, zPos + cosf, scale2, scale1, yRot);
                break;
            }
        }
    }
}

void func_effect_8007AF30(Effect* effect, f32 xPos, f32 zPos, f32 xVel, f32 zVel, f32 scale1) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = OBJ_EFFECT_382;

    effect->obj.pos.x = xPos;
    effect->obj.pos.y = -10.0f;
    effect->obj.pos.z = zPos;

    effect->vel.x = xVel;
    effect->vel.z = zVel - gPathVelZ;
    effect->scale1 = scale1;
    effect->timer_50 = 100;
    Object_SetInfo(&effect->info, effect->obj.id);
}

void func_effect_8007AFD0(f32 xPos, f32 zPos, f32 xVel, f32 zVel, f32 scale1) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            func_effect_8007AF30(&gEffects[i], xPos, zPos, xVel, zVel, scale1);
            break;
        }
    }
}

void func_effect_8007B040(Effect* effect) {
    f32 sp2C;
    s32 sp28;

    if (Play_CheckDynaFloorCollision(&sp2C, &sp28, effect->obj.pos.x, effect->obj.pos.y, effect->obj.pos.z)) {
        D_ctx_801782EC[sp28] = effect->scale1;
        D_ctx_801782EC[sp28 + 1] = effect->scale1 * 0.7f;
        D_ctx_801782EC[sp28 - 1] = effect->scale1 * 0.7f;
    }
    if (effect->timer_50 == 0) {
        Object_Kill(&effect->obj, effect->sfxSource);
    }
}

void func_effect_8007B0F4(Effect* effect) {
    Math_SmoothStepToF(&effect->scale2, effect->scale1 * 3.0f, 0.1f, 10.0f, 0.0f);
    effect->unk_44 -= 13;
    effect->obj.rot.y = 180.0f - effect->obj.rot.y;
    if (effect->unk_44 < 0) {
        Object_Kill(&effect->obj, effect->sfxSource);
    }
}

void func_effect_8007B180(Effect* effect, f32 xPos, f32 yPos, f32 zPos, f32 scale1) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = OBJ_EFFECT_381;

    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;

    effect->unk_44 = 255;
    effect->scale1 = scale1;
    Object_SetInfo(&effect->info, effect->obj.id);
    AUDIO_PLAY_SFX(NA_SE_SPLASH_LEVEL_L, effect->sfxSource, 0);
}

void func_effect_8007B228(f32 xPos, f32 yPos, f32 zPos, f32 scale1) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffects) && gCurrentLevel == LEVEL_ZONESS; i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            func_effect_8007B180(&gEffects[i], xPos, yPos, zPos, scale1);
            break;
        }
    }
}

void func_effect_8007B2BC(Effect* effect, f32 xPos, f32 yPos, f32 zPos, f32 scale1, s32 arg5) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = OBJ_EFFECT_384;

    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;

    effect->scale1 = scale1;
    effect->unk_44 = 255;
    effect->unk_4C = arg5;
    Object_SetInfo(&effect->info, effect->obj.id);
}

// Orange-yellowish light effect simulating an explosion
void func_effect_8007B344(f32 xPos, f32 yPos, f32 zPos, f32 scale1, s32 arg4) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            func_effect_8007B2BC(&gEffects[i], xPos, yPos, zPos, scale1, arg4);
            break;
        }
    }
}

void func_effect_8007B3B8(Effect* effect) {
    f32 var_fv0;
    f32 var_fv1;
    s32 var_v0;

    if (effect->unk_4C == 6) {
        var_fv0 = 15.0f;
        var_fv1 = 0.05f;
        var_v0 = 4;
    } else if ((effect->unk_4C == 5) && ((gCurrentLevel == LEVEL_KATINA) || (gCurrentLevel == LEVEL_METEO))) {
        var_fv0 = 10.0f;
        var_fv1 = 0.1f;
        var_v0 = 4;
    } else {
        var_fv0 = 10.0f;
        var_fv1 = 0.1f;
        var_v0 = 8;
    }

    Math_SmoothStepToF(&effect->scale2, effect->scale1, var_fv1, var_fv0, 0.0f);

    effect->unk_44 -= var_v0;
    if (effect->unk_44 < 0) {
        Object_Kill(&effect->obj, effect->sfxSource);
    }
}

void func_effect_8007B494(Effect* effect, f32 xPos, f32 yPos, f32 zPos, f32 scale1, s32 arg5) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = OBJ_EFFECT_385;

    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;

    effect->obj.rot.x = 90.0f;
    effect->scale1 = scale1;
    effect->unk_44 = arg5;

    if (arg5 < 60) {
        effect->unk_46 = 1;
    } else if (arg5 < 90) {
        effect->unk_46 = 2;
    } else {
        effect->unk_46 = 3;
    }
    Object_SetInfo(&effect->info, effect->obj.id);
}

void func_effect_8007B550(f32 xPos, f32 yPos, f32 zPos, f32 scale1, s32 arg4) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            func_effect_8007B494(&gEffects[i], xPos, yPos, zPos, scale1, arg4);
            break;
        }
    }
}

void func_effect_8007B5C0(Effect* effect) {
    Math_SmoothStepToF(&effect->scale2, effect->scale1, 0.1f, 10.0f, 0.1f);
    effect->unk_44 -= effect->unk_46;
    if (effect->unk_44 < 0) {
        Object_Kill(&effect->obj, effect->sfxSource);
    }
}

void func_effect_8007B62C(Effect* effect) {
    if (effect->timer_50 == 0) {
        effect->unk_46 -= 4;
        if (effect->unk_46 <= 0) {
            Object_Kill(&effect->obj, effect->sfxSource);
        }
    }
}

void func_effect_8007B670(Effect* effect) {
}

void func_effect_8007B67C(Effect* effect) {
    s32 var_v1;

    effect->unk_46 += 2;

    if (effect->unk_46 >= 10) {
        effect->unk_46 = 10;
    }

    if (effect->unk_46 >= 9) {
        effect->unk_48++;
        if (effect->unk_48 >= 10) {
            Object_Kill(&effect->obj, effect->sfxSource);
        }
    }

    var_v1 = effect->unk_4A;
    if (var_v1 != 0) {
        if (var_v1 > 10) {
            var_v1 -= 10;
        }
        effect->vel.x = gPlayer[var_v1 - 1].vel.x;
        effect->vel.y = gPlayer[var_v1 - 1].vel.y;
        effect->vel.z = gPlayer[var_v1 - 1].vel.z;
    }
}

void func_effect_8007B758(Effect* effect) {
    Math_SmoothStepToF(&effect->scale2, effect->scale1, 0.1f, 10.0f, 0.1f);
    effect->unk_44 -= 2;
    if (effect->unk_44 < 0) {
        Object_Kill(&effect->obj, effect->sfxSource);
    }
    func_effect_8007A774(gPlayer, effect, effect->scale2 * 20.0f);
}

void func_effect_8007B7E8(Effect* effect, f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = OBJ_EFFECT_364;

    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;

    effect->vel.x = RAND_FLOAT_CENTERED(5.0f);
    effect->vel.y = RAND_FLOAT_CENTERED(3.0f);
    effect->unk_48 = 3;

    if (Rand_ZeroOne() < 0.5f) {
        effect->unk_48 = -effect->unk_48;
    }
    effect->unk_4A = 50;
    effect->unk_46 = 1;
    effect->scale2 = scale2 * 0.2f;
    effect->obj.rot.z = RAND_FLOAT(360.0f);
    Object_SetInfo(&effect->info, effect->obj.id);
}

void func_effect_8007B8F8(f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    s32 i, j;

    for (i = ARRAY_COUNT(gEffects) - 1, j = 0; j < ARRAY_COUNT(gEffects); i--, j++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            func_effect_8007B7E8(&gEffects[i], xPos, yPos, zPos, scale2);
            break;
        }
    }
}

void func_effect_8007B960(Effect* effect) {
    effect->scale2 += 0.07f;
    effect->unk_4A -= effect->unk_46;
    if (effect->unk_4A < 0) {
        Object_Kill(&effect->obj, effect->sfxSource);
    }
    effect->obj.rot.z += effect->unk_48;
    effect->vel.y += 0.2f;
}

void func_effect_8007B9DC(Effect* effect) {
    //! DEBUG: Hold Z on controller 4 to set up a display list.
    if (gControllerHold[3].button & Z_TRIG) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_4);
    }

    Graphics_SetScaleMtx(effect->scale2);

    if (gCurrentLevel != LEVEL_MACBETH) {
        gDPSetPrimColor(gMasterDisp++, 0, 0, 140, 99, 58, effect->unk_4A);
    } else {
        gDPSetPrimColor(gMasterDisp++, 0, 0, (gGameFrameCount % 4U) + 5, (gGameFrameCount % 4U) + 3,
                        (gGameFrameCount % 4U) + 3, 220);
    }
    //! DEBUG: Hold Z on controller 4 to set up a display list.
    if (!(gControllerHold[3].button & A_BUTTON)) {
        gSPDisplayList(gMasterDisp++, D_BG_PLANET_2010A30);
    }
    //! DEBUG: Hold Z on controller 4 to set up a display list.
    if (gControllerHold[3].button & Z_TRIG) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_64);
    }
}

void func_effect_8007BB14(Effect* effect, f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = OBJ_EFFECT_362;

    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;

    effect->vel.x = RAND_FLOAT_CENTERED(5.0f);
    effect->vel.y = RAND_FLOAT_CENTERED(3.0f);
    effect->unk_48 = 3;

    if (Rand_ZeroOne() < 0.5f) {
        effect->unk_48 = -effect->unk_48;
    }

    effect->unk_4A = 180;
    effect->unk_46 = 8;

    if (scale2 > 15.0f) {
        effect->unk_46 = 5;
        effect->unk_4A = 80;
    }

    effect->scale2 = scale2 * 0.25f;
    effect->obj.rot.z = RAND_FLOAT(360.0f);

    if (scale2 == 6.0f) {
        effect->vel.z = gPlayer[0].vel.z * 0.6f;
    }
    Object_SetInfo(&effect->info, effect->obj.id);
}

void func_effect_8007BC7C(f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 20; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            func_effect_8007BB14(&gEffects[i], xPos, yPos, zPos, scale2);
            break;
        }
    }
}

void func_effect_8007BCE8(Effect* effect) {
    if (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_LEVEL_COMPLETE) {
        effect->obj.rot.x = RAD_TO_DEG(gPlayer[0].camPitch);
        effect->obj.rot.y = RAD_TO_DEG(-gPlayer[0].camYaw);
    }
    if (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_NEXT) {
        effect->unk_46 = 2;
        effect->vel.y -= 0.13f;
    }

    effect->scale2 += 0.07f;
    effect->unk_4A -= effect->unk_46;

    if (effect->unk_4A < 0) {
        Object_Kill(&effect->obj, effect->sfxSource);
    }
    effect->obj.rot.z += effect->unk_48;
    effect->vel.y += 0.2f;
}

void func_effect_8007BDE0(Effect* effect) {
    effect->scale2 += 0.04f;
    effect->unk_4A -= 2;
    if (effect->unk_4A < 0) {
        Object_Kill(&effect->obj, effect->sfxSource);
    }
    effect->obj.rot.z += effect->unk_48;
    effect->vel.y += effect->scale1;
}

void func_effect_8007BE54(Effect* effect) {
    effect->scale2 += 0.02f;
    effect->unk_4A -= 3;
    if (effect->unk_4A < 0) {
        Object_Kill(&effect->obj, effect->sfxSource);
    }
    effect->vel.z = gPlayer[0].vel.z + 7.0f;
    effect->obj.rot.z += effect->unk_48;
    effect->vel.y += 0.1f;
}

void func_effect_8007BEE8(Effect* effect) {
    Graphics_SetScaleMtx(effect->scale2);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, effect->unk_4A);
    gSPDisplayList(gMasterDisp++, D_BG_PLANET_2010A30);
}

void func_effect_8007BF64(Effect* effect, f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 scale2,
                          s32 timer50) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = OBJ_EFFECT_386;

    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;

    effect->vel.x = xVel;
    effect->vel.y = yVel;
    effect->vel.z = zVel;
    effect->scale2 = scale2;
    effect->timer_50 = timer50;
    Object_SetInfo(&effect->info, effect->obj.id);
}

void func_effect_8007BFFC(f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 scale2, s32 timer50) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            func_effect_8007BF64(&gEffects[i], xPos, yPos, zPos, xVel, yVel, zVel, scale2, timer50);
            break;
        }
    }
}

void func_effect_8007C088(Effect* effect, f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 scale2,
                          s32 timer50) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = OBJ_EFFECT_390;

    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;

    effect->vel.x = xVel;
    effect->vel.y = yVel;
    effect->vel.z = zVel;
    effect->scale2 = scale2;
    effect->timer_50 = timer50;
    Object_SetInfo(&effect->info, effect->obj.id);
}

void func_effect_8007C120(f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 scale2, s32 timer50) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            func_effect_8007C088(&gEffects[i], xPos, yPos, zPos, xVel, yVel, zVel, scale2, timer50);
            break;
        }
    }
}

void func_effect_8007C1AC(f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 scale2, s32 timer50) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            func_effect_8007BF64(&gEffects[i], xPos, yPos, zPos, xVel, yVel, zVel, scale2, timer50);
            Play_PlaySfxNoPlayer(gEffects[i].sfxSource, NA_SE_EXPLOSION_S);
            break;
        }
    }
}

void func_effect_8007C250(Effect* effect) {
    f32 randX;
    f32 randY;
    f32 randOther;
    s32 var_v0;

    Math_SmoothStepToF(&effect->vel.x, 0.0f, 0.2f, 10.0f, 0.1f);
    Math_SmoothStepToF(&effect->vel.y, 0.0f, 0.2f, 10.0f, 0.1f);
    Math_SmoothStepToF(&effect->vel.z, 0.0f, 0.2f, 10.0f, 0.1f);

    var_v0 = 4 - 1;
    if (gLevelMode == LEVELMODE_ALL_RANGE) {
        var_v0 = 2 - 1;
    }

    if ((effect->timer_50 & var_v0) == 0) {
        randX = RAND_FLOAT_CENTERED(40.0f);
        randY = RAND_FLOAT_CENTERED(40.0f);
        randOther = RAND_FLOAT(0.5f) + 1.0f;
        func_effect_8007D0E0(effect->obj.pos.x + randX, effect->obj.pos.y + randY, effect->obj.pos.z,
                             effect->scale2 * randOther);
        if (effect->timer_50 == 0) {
            Object_Kill(&effect->obj, effect->sfxSource);
        }
    }
}

void func_effect_8007C3B4(Effect* effect, f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 scale2,
                          s32 arg8) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = OBJ_EFFECT_389;

    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;

    effect->vel.x = xVel;
    effect->vel.y = yVel;
    effect->vel.z = zVel;

    effect->scale2 = scale2;
    effect->unk_4A = arg8;
    effect->unk_4C = RAND_INT(12.0f);
    effect->obj.rot.z = RAND_FLOAT(360.0f);
    Object_SetInfo(&effect->info, effect->obj.id);
    effect->unk_44 = 255;
}

void func_effect_8007C484(f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 scale2, s32 arg7) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i > 32; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            func_effect_8007C3B4(&gEffects[i], xPos, yPos, zPos, xVel, yVel, zVel, scale2, arg7);
            break;
        }
    }
}

void func_effect_8007C50C(Effect* effect) {
    f32 randX;
    f32 randY;
    f32 randOther;

    if ((effect->timer_50 % 8) == 0) {
        randX = RAND_FLOAT_CENTERED(40.0f) * effect->scale2;
        randY = RAND_FLOAT_CENTERED(40.0f) * effect->scale2;
        randOther = RAND_FLOAT(1.0f) + 1.0f;
        func_effect_8007C484(effect->obj.pos.x + randX, effect->obj.pos.y + randY, effect->obj.pos.z, effect->vel.x,
                             effect->vel.y, effect->vel.z, effect->scale2 * randOther, 0);
        if (effect->timer_50 == 0) {
            Object_Kill(&effect->obj, effect->sfxSource);
        }
    }
}

void func_effect_8007C608(Effect* effect, f32 xPos, f32 yPos, f32 zPos, f32 scale2, s32 timer50) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = OBJ_EFFECT_387;

    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;

    effect->scale2 = scale2;
    effect->timer_50 = timer50;
    Object_SetInfo(&effect->info, effect->obj.id);
}

void func_effect_8007C688(f32 xPos, f32 yPos, f32 zPos, f32 scale2, s32 timer50) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            func_effect_8007C608(&gEffects[i], xPos, yPos, zPos, scale2, timer50);
            break;
        }
    }
}

void func_effect_8007C6FC(Effect* effect, f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = OBJ_EFFECT_343;

    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;

    effect->unk_48 = 3;
    effect->vel.y = 5.0f;
    if (Rand_ZeroOne() < 0.5f) {
        effect->unk_48 = -effect->unk_48;
    }
    if ((gCurrentLevel == LEVEL_FORTUNA) && (gPlayer[0].state_1C8 != PLAYERSTATE_1C8_NEXT)) {
        effect->unk_4A = 180;
    } else {
        effect->unk_4A = 255;
    }

    effect->scale2 = scale2 * 0.25f;
    effect->obj.rot.z = RAND_FLOAT(360.0f);
    effect->unk_44 = 0;

    if (Rand_ZeroOne() < 0.3f) {
        effect->unk_44 = 1;
        effect->unk_4A = 255;
        effect->scale2 = scale2 * 0.3f;
    }
    effect->scale1 = RAND_FLOAT(0.2f);
    Object_SetInfo(&effect->info, effect->obj.id);
}

void func_effect_8007C85C(f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffects) - 20; i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            func_effect_8007C6FC(&gEffects[i], xPos, yPos, zPos, scale2);
            break;
        }
    }
}

void func_effect_8007C8C4(Effect* effect) {
    f32 randX;
    f32 randY;
    f32 randOther;
    s32 var_v0;

    var_v0 = 1 - 1;
    if ((gCurrentLevel == LEVEL_FORTUNA) && (gPlayer[0].state_1C8 != PLAYERSTATE_1C8_NEXT)) {
        var_v0 = 4 - 1;
    }

    if (((effect->timer_50 & var_v0) == 0) && (gLevelType == LEVELTYPE_PLANET)) {
        randX = RAND_FLOAT_CENTERED(10.0f);
        randY = RAND_FLOAT_CENTERED(10.0f);
        randOther = RAND_FLOAT(0.5f) + 1.0f;
        func_effect_8007C85C(effect->obj.pos.x + randX, effect->obj.pos.y + randY, effect->obj.pos.z,
                             effect->scale2 * randOther);
        if (effect->timer_50 == 0) {
            Object_Kill(&effect->obj, effect->sfxSource);
        }
    }
}

void func_effect_8007C9E0(Effect* effect) {
    if (effect->unk_44 == 0) {
        effect->scale2 *= 1.03f;
        effect->unk_4A -= 3;
        if (effect->unk_4A < 0) {
            Object_Kill(&effect->obj, effect->sfxSource);
        }
        effect->obj.rot.z += effect->unk_48;
        effect->vel.y += 0.3f;
        effect->vel.x += effect->scale1;
    } else {
        effect->scale2 *= 1.03f;
        effect->unk_4A -= 7;
        if (effect->unk_4A < 0) {
            Object_Kill(&effect->obj, effect->sfxSource);
        }
        effect->obj.rot.z += effect->unk_48;
        effect->vel.y += 0.3f;
        effect->vel.x += effect->scale1;
    }
}

void func_effect_8007CAF0(Effect* effect) {
    Graphics_SetScaleMtx(effect->scale2);
    if (effect->unk_44 == 0) {
        gDPSetPrimColor(gMasterDisp++, 0, 0, 0, 0, 0, effect->unk_4A);
        gSPDisplayList(gMasterDisp++, D_102A010);
    } else {
        Matrix_Scale(gGfxMatrix, 1.5f, 1.5f, 1.5f, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, effect->unk_4A);
        gSPDisplayList(gMasterDisp++, D_BG_PLANET_20031B0);
    }
}

void func_effect_8007CC00(Effect* effect, f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = OBJ_EFFECT_FIRE_SMOKE;
    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;
    effect->scale2 = scale2;
    effect->scale1 = 0.5f;
    effect->unk_4C = 0;
    effect->obj.rot.z = RAND_FLOAT(360.0f);
    Object_SetInfo(&effect->info, effect->obj.id);
    if (gLevelType == LEVELTYPE_PLANET) {
        effect->unk_44 = 230;
    } else {
        effect->unk_44 = 255;
    }
}

void func_effect_8007CCBC(Effect* effect, f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = OBJ_EFFECT_340;

    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;

    effect->scale2 = scale2;
    effect->unk_4C = 3;
    effect->scale1 = 0.2f;
    effect->obj.rot.z = RAND_FLOAT(360.0f);
    Object_SetInfo(&effect->info, effect->obj.id);
    if (gLevelType == LEVELTYPE_PLANET) {
        effect->unk_44 = 230;
    } else {
        effect->unk_44 = 255;
    }
}

void func_effect_8007CD7C(Effect* effect, f32 xPos, f32 yPos, f32 zPos, f32 scale2, s32 timer50) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = OBJ_EFFECT_342;
    effect->timer_50 = timer50;

    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;

    effect->unk_48 = 3;
    if (Rand_ZeroOne() < 0.5f) {
        effect->unk_48 = -effect->unk_48;
    }
    effect->unk_4A = 255;
    effect->scale2 = scale2;
    effect->obj.rot.z = RAND_FLOAT(360.0f);

    if ((Rand_ZeroOne() < 0.5f) && (gLevelType == LEVELTYPE_PLANET) && (timer50 != 1)) {
        effect->unk_44 = 1;
    }
    if (timer50 == 2) {
        effect->unk_44 = 1;
    }
    if (scale2 == 2.2f) {
        effect->unk_44 = 0;
    }
    Object_SetInfo(&effect->info, effect->obj.id);
}

void func_effect_8007CEBC(f32 xPos, f32 yPos, f32 zPos, f32 scale2, s32 timer50) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            func_effect_8007CD7C(&gEffects[i], xPos, yPos, zPos, scale2, timer50);
            break;
        }
    }
}

void func_effect_8007CF30(f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            func_effect_8007CC00(&gEffects[i], xPos, yPos, zPos, scale2);
            break;
        }
    }
}

void func_effect_8007CF9C(f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            func_effect_8007CCBC(&gEffects[i], xPos, yPos, zPos, scale2);
            break;
        }
    }
}

void func_effect_8007D008(f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            func_effect_8007CC00(&gEffects[i], xPos, yPos, zPos, scale2);
            break;
        }
    }
}

void func_effect_8007D074(f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            func_effect_8007CCBC(&gEffects[i], xPos, yPos, zPos, scale2);
            break;
        }
    }
}

void func_effect_8007D0E0(f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    func_effect_8007CF30(xPos, yPos, zPos, scale2);
}

void func_effect_8007D10C(f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    func_effect_8007CF9C(xPos, yPos, zPos, scale2);
}

void func_effect_8007D138(Effect* effect, f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = OBJ_EFFECT_341;

    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;

    effect->scale2 = scale2;
    effect->obj.rot.z = RAND_FLOAT(360.0f);
    Object_SetInfo(&effect->info, effect->obj.id);
    if (gLevelType == LEVELTYPE_PLANET) {
        effect->unk_4C = 15;
    }
    effect->unk_44 = 180;
}

void func_effect_8007D1E0(f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            func_effect_8007D138(&gEffects[i], xPos, yPos, zPos, scale2);
            break;
        }
    }
}

void func_effect_8007D24C(f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    if (gLevelType == LEVELTYPE_PLANET) {
        func_effect_8007D1E0(xPos, yPos, zPos, scale2);
        func_effect_8007CEBC(xPos, scale2 + yPos, zPos, scale2, 9);
    } else {
        func_effect_8007D0E0(xPos, yPos, zPos, scale2);
    }
}

void func_effect_8007D2C8(f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    func_effect_8007D008(xPos, yPos, zPos, scale2);
}

void func_effect_8007D2F4(Effect* effect) {
    if (gLevelType == LEVELTYPE_PLANET) {
        if ((gCurrentLevel == LEVEL_KATINA) && (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_LEVEL_COMPLETE)) {
            effect->vel.y += 0.1f;
            if (effect->timer_50 == 0) {
                effect->unk_4C++;
                effect->timer_50 = 4;
                if (effect->unk_4C > 15) {
                    effect->timer_50 = 5;
                }
                if (effect->unk_4C > 20) {
                    Object_Kill(&effect->obj, effect->sfxSource);
                }
            }
        } else {
            if ((gCurrentLevel == LEVEL_MACBETH) && (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_LEVEL_COMPLETE) &&
                (effect->vel.x != 0)) {
                Math_SmoothStepToF(&effect->vel.x, -1.0f, 1.0f, 1.0f, 0.0f);
                Math_SmoothStepToF(&effect->vel.z, 4.0f, 1.0f, 1.0f, 0.0f);
                effect->vel.y += 1.7f;
            }
            effect->vel.y += 0.3f;
            if (effect->timer_50 == 0) {
                effect->unk_4C++;
                if (effect->unk_4C > 15) {
                    effect->timer_50 = 2;
                }
                if (effect->unk_4C > 20) {
                    Object_Kill(&effect->obj, effect->sfxSource);
                }
            }
        }
    } else {
        if (effect->timer_50 == 0) {
            effect->unk_4C++;
            effect->timer_50 = effect->unk_46;
            if (effect->unk_4C > 13) {
                Object_Kill(&effect->obj, effect->sfxSource);
            }
        }
        effect->unk_44 -= 15;
    }
    if (gLight3Brightness < effect->scale1) {
        gLight3Brightness = effect->scale1;
        gLight3x = effect->obj.pos.x;
        gLight3y = effect->obj.pos.y;
        gLight3z = effect->obj.pos.z;
        gLight3R = 255;
        gLight3G = 50;
        gLight3B = 0;
    }
    Math_SmoothStepToF(&effect->scale1, 0.0f, 1.0f, 0.05f, 0.0f);
}

static Gfx* D_800D17A4[] = {
    D_BG_PLANET_200B630, D_BG_PLANET_200B630, D_BG_PLANET_200B630, D_BG_PLANET_200B630, D_BG_PLANET_200A5A0,
    D_BG_PLANET_2009510, D_BG_PLANET_2008480, D_BG_PLANET_20073F0, D_BG_PLANET_2006360, D_BG_PLANET_200C6C0,
    D_BG_PLANET_20052D0, D_BG_PLANET_2004240, D_BG_PLANET_20031B0, D_BG_PLANET_2002120, D_BG_PLANET_2001090,
    D_BG_PLANET_2000000, D_BG_PLANET_2010A30, D_BG_PLANET_20101A0, D_BG_PLANET_200F910, D_BG_PLANET_200F080,
    D_BG_PLANET_200E7F0,
};

static f32 D_800D17F8[] = {
    1.0f, 1.1f, 1.1f, 1.2f, 1.2f, 1.3f, 1.3f, 1.4f, 1.4f, 1.5f, 1.5f,
    1.6f, 1.6f, 1.7f, 1.7f, 1.8f, 1.8f, 1.9f, 1.9f, 2.0f, 2.0f,
};

static Color_RGBA32 D_800D184C[] = {
    { 255, 255, 255, 255 }, { 255, 0, 0, 255 },     { 255, 40, 40, 255 },   { 255, 80, 80, 255 },
    { 255, 120, 120, 255 }, { 255, 160, 160, 255 }, { 255, 200, 200, 255 }, { 255, 240, 240, 255 },
    { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 },
    { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 },
    { 0, 0, 0, 255 },       { 0, 0, 0, 200 },       { 0, 0, 0, 150 },       { 0, 0, 0, 100 },
    { 0, 0, 0, 50 },
};

static Gfx* D_800D18A0[] = {
    D_BG_SPACE_20066C0, D_BG_SPACE_20066C0, D_BG_SPACE_2005E30, D_BG_SPACE_20055A0, D_BG_SPACE_2004D10,
    D_BG_SPACE_2004480, D_BG_SPACE_2003BF0, D_BG_SPACE_2003360, D_BG_SPACE_2002AD0, D_BG_SPACE_2002240,
    D_BG_SPACE_20019B0, D_BG_SPACE_2001120, D_BG_SPACE_2000890, D_BG_SPACE_2000000,
};

void func_effect_8007D55C(Effect* effect) {
    f32 scale;

    Graphics_SetScaleMtx(effect->scale2);
    if (gLevelType == LEVELTYPE_PLANET) {
        gDPSetPrimColor(gMasterDisp++, 0, 0, D_800D184C[effect->unk_4C].r, D_800D184C[effect->unk_4C].g,
                        D_800D184C[effect->unk_4C].b, D_800D184C[effect->unk_4C].a);
        scale = D_800D17F8[effect->unk_4C] - 0.5f;
        Matrix_Scale(gGfxMatrix, scale, scale, 1.0f, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, D_800D17A4[effect->unk_4C]);
        return;
    }
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 100, effect->unk_44);
    if (effect->unk_4C == 0) {
        Matrix_Scale(gGfxMatrix, 2.5f, 2.5f, 2.5f, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, D_800D18A0[effect->unk_4C]);
        return;
    }
    gSPDisplayList(gMasterDisp++, D_800D18A0[effect->unk_4C]);
}

void func_effect_8007D748(Effect* effect) {
    if (gLevelType == LEVELTYPE_PLANET) {
        effect->vel.y += 0.3f;
        if (effect->timer_50 == 0) {
            if (effect->unk_4C > 15) {
                effect->timer_50 = 2;
                effect->unk_4C = effect->unk_4C + 1;
            } else {
                effect->unk_4C = effect->unk_4C + 2;
            }
            if (effect->unk_4C > 20) {
                Object_Kill(&effect->obj, effect->sfxSource);
            }
        }
    } else {
        if (effect->timer_50 == 0) {
            effect->unk_4C++;
            effect->timer_50 = 0;
            if (effect->unk_4C > 13) {
                Object_Kill(&effect->obj, effect->sfxSource);
            }
        }
        effect->unk_44 -= 15;
    }
    if (gLight3Brightness < effect->scale1) {
        gLight3Brightness = effect->scale1;
        gLight3x = effect->obj.pos.x;
        gLight3y = effect->obj.pos.y;
        gLight3z = effect->obj.pos.z;
        gLight3R = 255;
        gLight3G = 50;
        gLight3B = 0;
    }
    Math_SmoothStepToF(&effect->scale1, 0, 1.0f, 0.1f, 0.0f);
}

void func_effect_8007D8A8(Effect* effect) {
    if (gLevelType == LEVELTYPE_SPACE) {
        func_effect_8007D2F4(effect);
        return;
    }
    effect->vel.y += 0.3f;
    if (effect->timer_50 == 0) {
        effect->unk_4C++;
        effect->timer_50 = 2;
        if (effect->unk_4C >= 20) {
            Object_Kill(&effect->obj, effect->sfxSource);
        }
    }
    if (effect->unk_4C > 15) {
        effect->unk_44 -= 20;
    }
}

void func_effect_8007D94C(Effect* effect, f32 xPos, f32 yPos, f32 zPos, f32 scale2, f32 scale1, s32 timer50) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = OBJ_EFFECT_367;
    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;
    effect->unk_44 = 80;
    effect->scale2 = scale2;
    effect->scale1 = scale1;
    effect->timer_50 = timer50;
    Object_SetInfo(&effect->info, effect->obj.id);
}

void func_effect_8007D9DC(f32 xPos, f32 yPos, f32 zPos, f32 scale2, f32 scale1, s32 timer50) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            func_effect_8007D94C(&gEffects[i], xPos, yPos, zPos, scale2, scale1, timer50);
            break;
        }
    }
}

void func_effect_8007DA58(Effect* effect) {
    effect->scale2 += effect->scale1;
    if (effect->scale1 > 0.0f) {
        effect->scale1 -= 0.01f;
    } else {
        effect->scale1 -= 0.001f;
    }
    effect->obj.rot.y += effect->unk_60.y;
    if (effect->scale2 < 0.01f) {
        Object_Kill(&effect->obj, effect->sfxSource);
    }
}

void func_effect_8007DAE4(Effect* effect) {
    Graphics_SetScaleMtx(effect->scale2);
    RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
    gSPDisplayList(gMasterDisp++, D_CO_6004900);
    RCP_SetupDL(&gMasterDisp, SETUPDL_64);
}

void func_effect_8007DB70(Effect* effect) {
    Vec3f sp54 = { 0.0f, -10.0f, 0.0f };

    switch (effect->state) {
        case 0:
            effect->vel.y -= 0.5f;
            if ((effect->timer_50 == 0) && ((Object_CheckCollision(1000, &effect->obj.pos, &sp54, 1) != 0) ||
                                            (effect->obj.pos.y < (gGroundHeight + 10.0f)))) {
                effect->vel.y = 0.0f;
                if (effect->obj.pos.y < (gGroundHeight + 10.0f)) {
                    effect->obj.pos.y = gGroundHeight;
                }
                effect->state = 1;
                effect->timer_50 = 30;
                effect->unk_44 = 192;
                effect->scale2 = 2.5f;
                effect->scale1 = 2.5f;
                AUDIO_PLAY_SFX(NA_SE_EN_EXPLOSION_M, effect->sfxSource, 4);
                func_effect_8007D0E0(effect->obj.pos.x, effect->obj.pos.y + 30.0f, effect->obj.pos.z, 7.0f);
                func_effect_8007BFFC(effect->obj.pos.x, effect->obj.pos.y + 30.0f, effect->obj.pos.z, 0.0f, 0.0f, 0.0f,
                                     4.0f, 5);
                if ((effect->obj.pos.y < (gGroundHeight + 10.0f)) || (gGroundSurface != SURFACE_WATER)) {
                    PlayerShot_SpawnEffect344(effect->obj.pos.x, 3.0f, effect->obj.pos.z, effect->obj.pos.x,
                                              effect->obj.pos.z, 0.0f, 0.0f, 90.0f, 5.0f, 0, 0);
                    break;
                }
            }
            break;

        case 1:
            effect->scale2 += ((20.0f - effect->scale2) * 0.1f);
            if (effect->scale2 > 19.0f) {
                effect->scale1 -= 0.3f;
                effect->unk_44 -= 20;
                if (effect->unk_44 < 0) {
                    Object_Kill(&effect->obj, effect->sfxSource);
                }
            }
            effect->obj.rot.y = 180.0f - effect->obj.rot.y;
            if ((fabsf(gPlayer[0].trueZpos - effect->obj.pos.z) < 40.0f) &&
                (fabsf(gPlayer[0].pos.x - effect->obj.pos.x) < 80.0f)) {
                if ((effect->obj.pos.y < gPlayer[0].pos.y) &&
                    ((gPlayer[0].pos.y - effect->obj.pos.y) < (effect->scale2 * 35.0f)) &&
                    (gPlayer[0].timer_498 == 0)) {
                    Player_ApplyDamage(gPlayer, 0, effect->info.damage);
                }
            }
            break;
    }
}

void func_effect_8007DED4(Effect* effect) {
    switch (effect->state) {
        case 0:
            Graphics_SetScaleMtx(effect->scale2);
            RCP_SetupDL_60(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
            gSPDisplayList(gMasterDisp++, D_ENMY_PLANET_4008CE0);
            RCP_SetupDL(&gMasterDisp, SETUPDL_64);
            break;

        case 1:
            Matrix_Scale(gGfxMatrix, effect->scale1, effect->scale2, 2.5f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            RCP_SetupDL_40();
            gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
            gSPDisplayList(gMasterDisp++, D_ENMY_PLANET_4008F70);
            RCP_SetupDL(&gMasterDisp, SETUPDL_64);
            break;
    }
}

void func_effect_8007E014(Effect* effect) {
    s32 i;
    f32 x;
    f32 z;
    f32 y;

    if (gGroundType == 4) {
        Ground_801B6E20(effect->obj.pos.x, effect->obj.pos.z + gPathProgress, &x, &y, &z);
        effect->obj.pos.y = y + 3.0f;
        effect->obj.rot.x = RAD_TO_DEG(x);
        effect->obj.rot.z = RAD_TO_DEG(z);
    }

    if (((effect->unk_44 == 1) || (effect->unk_44 == 3)) && ((s32) (effect->timer_50 % 4U) == 1) &&
        (Rand_ZeroOne() < 0.5f)) {
        func_effect_8007D10C(effect->obj.pos.x, effect->obj.pos.y + (effect->scale2 * 5.0f), effect->obj.pos.z + 3.0f,
                             (RAND_FLOAT(0.7f) + 1.0f) * (effect->scale2 * 1.2f));
    }

    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        if ((gEffects[i].obj.status == OBJ_ACTIVE) && (gEffects[i].obj.id == OBJ_EFFECT_344) && (i != effect->index) &&
            (fabsf(effect->obj.pos.z - gEffects[i].obj.pos.z) < 20.0f) &&
            (fabsf(effect->obj.pos.x - gEffects[i].obj.pos.x) < 20.0f) &&
            (fabsf(effect->obj.pos.y - gEffects[i].obj.pos.y) < 20.0f)) {
            Object_Kill(&effect->obj, effect->sfxSource);
        }
    }
}

void func_effect_8007E258(Effect* effect) {
    if ((gCamCount != 1) && (effect->timer_50 == 0)) {
        Object_Kill(&effect->obj, effect->sfxSource);
    }
}

void func_effect_8007E298(Effect* effect) {
    if (effect->timer_50 == 0) {
        effect->scale2 *= 1.035f;
        effect->unk_4A -= 8;
        if (effect->unk_4A < 0) {
            Object_Kill(&effect->obj, effect->sfxSource);
        }
    }
    effect->obj.rot.z += effect->unk_48;
    if (gLevelType == LEVELTYPE_PLANET) {
        effect->vel.y += 0.2f;
    }
}

void func_effect_8007E330(Effect* effect) {
    Graphics_SetScaleMtx(effect->scale2);
    if (effect->unk_44 == 0) {
        gDPSetPrimColor(gMasterDisp++, 0, 0, 0, 0, 0, effect->unk_4A);
    } else {
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, effect->unk_4A);
    }
    gSPDisplayList(gMasterDisp++, D_BG_PLANET_2010A30);
}

void func_effect_8007E3E4(Effect* effect) {
    effect->scale2 += 0.02f;
    effect->unk_4A -= 4;
    if (effect->unk_4A < 0) {
        Object_Kill(&effect->obj, effect->sfxSource);
    }
    effect->obj.rot.z += effect->unk_48;
    effect->vel.y += 0.05f;
}

void func_effect_8007E45C(Effect* effect) {
    switch (effect->state) {
        case 0:
            if (effect->unk_4C != 0) {
                Math_SmoothStepToF(&effect->scale2, 5.0f, 0.05f, 0.5f, 0.0f);
                effect->unk_44 -= 10;
                effect->obj.rot.z += effect->scale1;
                if (effect->unk_44 < 0) {
                    Object_Kill(&effect->obj, effect->sfxSource);
                }
                break;
            }

            effect->scale2 += 0.02f;
            effect->unk_44--;

            if (effect->unk_44 < 0) {
                Object_Kill(&effect->obj, effect->sfxSource);
            }

            effect->obj.rot.z += effect->scale1;
            Math_SmoothStepToF(&effect->vel.y, 0.5f, 0.05f, 0.2f, 0.00001f);
            break;

        case 1:
            effect->vel.y = 3.0f;
            Math_SmoothStepToF(&effect->scale2, 5.0f, 0.05f, 0.5f, 0.0f);
            effect->unk_44 -= 10;
            effect->obj.rot.z += effect->scale1;
            if (effect->unk_44 < 0) {
                Object_Kill(&effect->obj, effect->sfxSource);
            }
            break;
    }
}

void func_effect_8007E5CC(Effect* effect) {
    Graphics_SetScaleMtx(effect->scale2);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, effect->unk_44);
    gSPDisplayList(gMasterDisp++, D_BG_PLANET_2010A30);
}

void func_effect_8007E648(Effect* effect) {
    if (effect->timer_50 == 0) {
        Math_SmoothStepToF(&effect->scale2, effect->scale1, 0.05f, 100.0f, 0.0f);
        effect->unk_44 -= 2;
        if (effect->unk_44 < 0) {
            Object_Kill(&effect->obj, effect->sfxSource);
        }
    }
}

void func_effect_8007E6B8(Effect* effect, u32 objId, f32 xPos, f32 yPos, f32 zPos, f32 speed) {
    f32 sp54;
    f32 sp50;
    f32 temp_ft4;
    Vec3f sp40;
    Vec3f sp34;

    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = objId;
    effect->timer_50 = 100;

    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;

    Object_SetInfo(&effect->info, effect->obj.id);
    sp50 = Math_Atan2F(gPlayer[0].pos.x - xPos, gPlayer[0].trueZpos - zPos);
    temp_ft4 = sqrtf(SQ(gPlayer[0].pos.x - xPos) + SQ(gPlayer[0].trueZpos - zPos));
    sp54 = -Math_Atan2F(gPlayer[0].pos.y - yPos, temp_ft4);

    Matrix_RotateY(gCalcMatrix, sp50, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, sp54, MTXF_APPLY);

    sp40.x = 0.0f;
    sp40.y = 0.0f;
    sp40.z = speed;

    Matrix_MultVec3f(gCalcMatrix, &sp40, &sp34);

    effect->vel.x = sp34.x + gPathVelX;
    effect->vel.y = sp34.y + gPathVelY;
    effect->vel.z = sp34.z - gPathVelZ;

    if ((objId == OBJ_EFFECT_353) || (objId == OBJ_EFFECT_354)) {
        effect->obj.rot.x = RAD_TO_DEG(sp54);
        effect->obj.rot.y = RAD_TO_DEG(sp50);
    }

    if (objId == OBJ_EFFECT_356) {
        AUDIO_PLAY_SFX(NA_SE_EN_ENERGY_BEAM, effect->sfxSource, 4);
    }

    if (objId == OBJ_EFFECT_376) {
        effect->obj.rot.z = RAND_FLOAT(360.0f);
        effect->unk_4A = 180;
        effect->scale2 = 5.0f;
    } else if ((objId == OBJ_EFFECT_355) || (objId == OBJ_EFFECT_377)) {
        AUDIO_PLAY_SFX(NA_SE_EN_ENERGY_BEAM, effect->sfxSource, 4);
    } else {
        AUDIO_PLAY_SFX(NA_SE_EN_SHOT_0, effect->sfxSource, 4);
    }
}

void func_effect_8007E93C(Effect* effect, u32 objId, f32 xPos, f32 yPos, f32 zPos, f32 speed) {
    f32 sp54;
    f32 sp50;
    f32 temp_ft4;
    Vec3f sp40;
    Vec3f sp34;

    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = objId;
    effect->timer_50 = 100;

    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;

    Object_SetInfo(&effect->info, effect->obj.id);
    sp50 = Math_Atan2F(gPlayer[0].cam.eye.x - xPos, gPlayer[0].cam.eye.z - zPos);
    temp_ft4 = sqrtf(SQ(gPlayer[0].cam.eye.x - xPos) + SQ(gPlayer[0].cam.eye.z - zPos));
    sp54 = -Math_Atan2F(gPlayer[0].cam.eye.y - yPos, temp_ft4);

    Matrix_RotateY(gCalcMatrix, sp50, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, sp54, MTXF_APPLY);

    sp40.x = 0.0f;
    sp40.y = 0.0f;
    sp40.z = speed;

    Matrix_MultVec3f(gCalcMatrix, &sp40, &sp34);

    effect->vel.x = sp34.x + gPathVelX;
    effect->vel.y = sp34.y + gPathVelY;
    effect->vel.z = sp34.z - gPathVelZ;

    if (objId == OBJ_EFFECT_353) {
        effect->obj.rot.x = RAD_TO_DEG(sp54);
        effect->obj.rot.y = RAD_TO_DEG(sp50);
    }

    if (objId == OBJ_EFFECT_356) {
        AUDIO_PLAY_SFX(NA_SE_EN_ENERGY_BEAM, effect->sfxSource, 4);
    }

    if (objId == OBJ_EFFECT_376) {
        effect->obj.rot.z = RAND_FLOAT(360.0f);
        effect->unk_4A = 180;
        effect->scale2 = 5.0f;
    } else if ((objId == OBJ_EFFECT_355) || (objId == OBJ_EFFECT_377)) {
        AUDIO_PLAY_SFX(NA_SE_EN_ENERGY_BEAM, effect->sfxSource, 4);
    } else {
        AUDIO_PLAY_SFX(NA_SE_EN_SHOT_0, effect->sfxSource, 4);
    }
}

void func_effect_8007EBB8(Effect* effect, ObjectId objId, f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel,
                          f32 scale2) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = objId;

    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;

    effect->timer_50 = 100;

    effect->vel.x = xVel;
    effect->vel.y = yVel;
    effect->vel.z = zVel;

    effect->scale2 = scale2;
    if (objId == OBJ_EFFECT_355) {
        AUDIO_PLAY_SFX(NA_SE_EN_ENERGY_BEAM, effect->sfxSource, 4);
    } else {
        AUDIO_PLAY_SFX(NA_SE_EN_SHOT_0, effect->sfxSource, 4);
    }
    Object_SetInfo(&effect->info, effect->obj.id);
}

void func_effect_8007ECB4(ObjectId objId, f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 scale2) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            func_effect_8007EBB8(&gEffects[i], objId, xPos, yPos, zPos, xVel, yVel, zVel, scale2);
            break;
        }
    }
}

void func_effect_8007ED54(Effect* effect, ObjectId objId, f32 xPos, f32 yPos, f32 zPos, f32 xRot, f32 yRot, f32 zRot,
                          f32 unkX, f32 unkY, f32 unkZ, f32 xVel, f32 yVel, f32 zVel, f32 scale2) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = objId;

    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;

    effect->timer_50 = 100;
    if (gCurrentLevel == LEVEL_AQUAS) {
        effect->timer_50 = 75;
    }

    effect->vel.x = xVel;
    effect->vel.y = yVel;
    effect->vel.z = zVel;

    effect->obj.rot.x = xRot;
    effect->obj.rot.y = yRot;
    effect->obj.rot.z = zRot;

    effect->unk_60.x = unkX;
    effect->unk_60.y = unkY;
    effect->unk_60.z = unkZ;

    effect->scale2 = scale2;
    if (effect->obj.id != OBJ_EFFECT_380) {
        AUDIO_PLAY_SFX(NA_SE_EN_SHOT_0, effect->sfxSource, 4);
    }
    Object_SetInfo(&effect->info, effect->obj.id);
}

void func_effect_8007EE68(ObjectId objId, Vec3f* pos, Vec3f* rot, Vec3f* arg3, Vec3f* arg4, f32 scale2) {
    s32 i;
    Vec3f sp68;

    Matrix_RotateY(gCalcMatrix, arg3->y * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, arg3->x * M_DTOR, MTXF_APPLY);
    Matrix_RotateZ(gCalcMatrix, arg3->z * M_DTOR, MTXF_APPLY);
    Matrix_RotateY(gCalcMatrix, rot->y * M_DTOR, MTXF_APPLY);
    Matrix_RotateX(gCalcMatrix, rot->x * M_DTOR, MTXF_APPLY);
    Matrix_RotateZ(gCalcMatrix, rot->z * M_DTOR, MTXF_APPLY);
    Matrix_MultVec3f(gCalcMatrix, arg4, &sp68);

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            func_effect_8007ED54(&gEffects[i], objId, pos->x + sp68.x, pos->y + sp68.y, pos->z + sp68.z, rot->x, rot->y,
                                 rot->z, arg3->x, arg3->y, arg3->z, sp68.x + gPathVelX, sp68.y + gPathVelY,
                                 sp68.z - gPathVelZ, scale2);
            break;
        }
    }
}

void func_effect_8007F04C(ObjectId objId, f32 xPos, f32 yPos, f32 zPos, f32 xRot, f32 yRot, f32 zRot, f32 unkX,
                          f32 unkY, f32 unkZ, f32 xVel, f32 yVel, f32 zVel, f32 scale2) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            func_effect_8007ED54(&gEffects[i], objId, xPos, yPos, zPos, xRot, yRot, zRot, unkX, unkY, unkZ, xVel, yVel,
                                 zVel, scale2);
            break;
        }
    }
}

void func_effect_8007F11C(ObjectId objId, f32 xPos, f32 yPos, f32 zPos, f32 speed) {
    s32 i;

    if ((fabsf(zPos - gPlayer[0].trueZpos) > 300.0f) || (fabsf(xPos - gPlayer[0].pos.x) > 300.0f)) {
        for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
            if (gEffects[i].obj.status == OBJ_FREE) {
                Matrix_Push(&gCalcMatrix);
                func_effect_8007E6B8(&gEffects[i], objId, xPos, yPos, zPos, speed);
                Matrix_Pop(&gCalcMatrix);
                break;
            }
        }
    }
}

void func_effect_8007F20C(ObjectId objId, f32 xPos, f32 yPos, f32 zPos, f32 speed) {
    s32 i;

    if ((fabsf(zPos - gPlayer[0].cam.eye.z) > 300.0f) || (fabsf(xPos - gPlayer[0].cam.eye.x) > 300.0f)) {
        for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
            if (gEffects[i].obj.status == OBJ_FREE) {
                Matrix_Push(&gCalcMatrix);
                func_effect_8007E93C(&gEffects[i], objId, xPos, yPos, zPos, speed);
                Matrix_Pop(&gCalcMatrix);
                break;
            }
        }
    }
}

void func_effect_8007F2FC(Effect* effect) {
    if (effect->timer_50 == 0) {
        Object_Kill(&effect->obj, effect->sfxSource);
    }

    if ((effect->obj.pos.y < gGroundHeight) && (gLevelType == LEVELTYPE_PLANET)) {
        Object_Kill(&effect->obj, effect->sfxSource);
    }

    if (gLevelType == LEVELTYPE_PLANET) {
        effect->vel.y -= 0.3f;
    }

    if (effect->obj.pos.y < gWaterLevel) {
        effect->vel.y += 0.2f;
        effect->obj.pos.y -= effect->vel.y * 0.5f;
        effect->obj.pos.x -= effect->vel.x * 0.5f;
        effect->obj.pos.z -= effect->vel.z * 0.5f;
    }

    if ((effect->unk_44 == 1) && ((gGameFrameCount % 2) == 0)) {
        func_effect_8007D0E0(effect->obj.pos.x, effect->obj.pos.y, effect->obj.pos.z, 1.5f);
    }
}

void func_effect_8007F438(Effect* effect) {
    if (gCurrentLevel == LEVEL_AQUAS) {
        effect->obj.rot.z += 3.5f;
        effect->vel.z = 5.0f;

        if (effect->unk_44 != 0) {
            Math_SmoothStepToF(&effect->scale1, 100.0f, 1.0f, 20.0f, 0.0001f);
        } else {
            Math_SmoothStepToF(&effect->scale1, 0.0f, 1.0f, 20.0f, 0.0001f);
        }

        if (effect->unk_46 == 0) {
            effect->unk_46 = 30;
            effect->unk_44++;
            effect->unk_44 &= 1;
        } else {
            effect->unk_46--;
        }

        if (gPathVelZ < 0.0f) {
            effect->vel.z = -10.0f;
        }

        if (effect->timer_50 == 0) {
            Object_Kill(&effect->obj, effect->sfxSource);
        }
    } else {
        effect->obj.rot.z += 3.5f;
        if (gLevelType == LEVELTYPE_PLANET) {
            effect->vel.y += 0.2f;
        }
        if (effect->timer_50 == 0) {
            Object_Kill(&effect->obj, effect->sfxSource);
        }
    }
}

void func_effect_8007F5AC(Effect* effect) {
    if (effect->unk_4C == 0) {
        effect->unk_46++;
        if ((effect->unk_46 & 0x20) == 0) {
            effect->vel.x += 0.5f;
        } else {
            effect->vel.x -= 0.5f;
        }

        if (((gGameFrameCount % 2) == 0)) {
            effect->unk_44--;
            if (effect->unk_44 < 20) {
                Object_Kill(&effect->obj, effect->sfxSource);
            }
        }

        effect->scale2 += 0.02f;
        if ((gGameFrameCount & 0x10) == 0) {
            effect->scale2 += 0.01f;
        } else {
            effect->scale2 -= 0.01f;
        }
    }
}

void func_effect_8007F6B0(Effect* effect) {
    s32 i;
    f32 temp;
    f32 cos;
    f32 sin;
    f32 randfloat;
    f32 x;
    f32 z;
    f32 y;
    f32 yPos;

    Math_SmoothStepToF(&effect->scale2, effect->scale1, 0.1f, 12.0f, 0.1f);

    effect->unk_44 -= 2;
    if (effect->unk_44 < 0) {
        Object_Kill(&effect->obj, effect->sfxSource);
    }

    if (((gGameFrameCount % 4) == 0) && (effect->state == 0)) {
        randfloat = RAND_FLOAT(30.0f);
        for (i = 0; i < 36; i += 2) {
            temp = (i * 10.0f * M_DTOR) + randfloat;
            sin = __sinf(temp) * effect->scale2 * 8.0f;
            cos = __cosf(temp) * effect->scale2 * 8.0f;
            yPos = gGroundHeight + 40.0f;

            if (gGroundType == 4) {
                Ground_801B6E20(effect->obj.pos.x + sin, effect->obj.pos.z + cos + gPathProgress, &x, &y, &z);
                yPos = y + 30.0f;
            }

            if (gCurrentLevel == LEVEL_AQUAS) {
                func_effect_8007B8F8(effect->obj.pos.x + sin, yPos, effect->obj.pos.z + cos, 20.0f);
            } else if (gCurrentLevel == LEVEL_FORTUNA) {
                func_effect_8007BC7C(effect->obj.pos.x + sin, yPos, effect->obj.pos.z + cos, 20.0f);
            } else if (gCurrentLevel == LEVEL_TITANIA) {
                func_effect_8007A900(effect->obj.pos.x + sin, yPos, effect->obj.pos.z + cos, 10.0f, 255, 15, 0);
            }
        }
    }
}

void func_effect_8007F958(Effect* effect) {
    s32 i;
    f32 x;
    f32 z;
    f32 y;
    f32 temp;
    f32 cos;
    f32 sin;
    f32 randFloat;
    f32 yPos;

    effect->scale2 += effect->scale1;
    effect->scale1 -= 0.08f;
    if (effect->scale1 < 0.1f) {
        effect->scale1 = 0.1f;
    }

    effect->unk_44 -= 9;
    if (effect->unk_44 < 0) {
        Object_Kill(&effect->obj, effect->sfxSource);
        return;
    }

    if (((gGameFrameCount % 2) == 0)) {
        randFloat = RAND_FLOAT(144.0f);
        for (i = 0; i < 5; i++) {
            temp = (i * 72.0f * M_DTOR) + randFloat;
            sin = __sinf(temp) * effect->scale2 * 16.0f;
            cos = __cosf(temp) * effect->scale2 * 16.0f;
            yPos = gGroundHeight + 10.0f;

            if (gGroundType == 4) {
                Ground_801B6E20(effect->obj.pos.x + sin, effect->obj.pos.z + cos + gPathProgress, &x, &y, &z);
                yPos = y + 10.0f;
            }

            if (gCurrentLevel == LEVEL_FORTUNA) {
                func_effect_8007BC7C(effect->obj.pos.x + sin, yPos, effect->obj.pos.z + cos, 8.0f);
            } else if (gCurrentLevel == LEVEL_TITANIA) {
                func_effect_8007A900(effect->obj.pos.x + sin, yPos, effect->obj.pos.z + cos, 8.0f, 255, 15, 0);
            }
        }
    }
}

void func_effect_8007FBE0(Effect* effect) {
    s32 i;
    f32 temp;
    f32 sin;
    f32 cos;
    f32 randFloat;
    f32 yPos;

    effect->scale2 += effect->scale1;
    effect->scale1 -= .1f;
    if (effect->scale1 < 0.1f) {
        effect->scale1 = 0.1f;
    }

    effect->unk_44 -= 6;
    if (effect->unk_44 < 0) {
        Object_Kill(&effect->obj, effect->sfxSource);
    }

    if (((gGameFrameCount % 2) == 0)) {
        randFloat = RAND_FLOAT(144.0f);
        for (i = 0; i < 10; i++) {
            temp = (i * 36.0f * M_DTOR) + randFloat;
            sin = __sinf(temp) * effect->scale2 * 16.0f;
            cos = __cosf(temp) * effect->scale2 * 16.0f;
            yPos = gGroundHeight + 10.0f;
            func_effect_8007BC7C(effect->obj.pos.x + sin, yPos, effect->obj.pos.z + cos, 12.0f);
        }
    }
}

bool func_effect_8007FD84(Effect* effect) {
    s32 i;
    Actor* actor;

    for (i = 1; i < ARRAY_COUNT(gTeamEventActorIndex); i++) {
        actor = &gActors[gTeamEventActorIndex[i]];
        if (actor->obj.status == OBJ_ACTIVE) {
            if ((actor->iwork[12] >= TEAM_ID_FALCO) && (actor->iwork[12] <= TEAM_ID_BILL) &&
                (fabsf(actor->obj.pos.z - effect->obj.pos.z) < 100.0f) &&
                (fabsf(actor->obj.pos.x - effect->obj.pos.x) < 100.0f) &&
                (fabsf(actor->obj.pos.y - effect->obj.pos.y) < 100.0f)) {
                actor->dmgType = DMG_BEAM;
                actor->dmgPart = 0;
                actor->damage = 10;
                if (effect->obj.id == OBJ_EFFECT_354) {
                    actor->damage = 30;
                }
                actor->dmgSource = CS_SHOT_ID;
                return true;
            }
        }
    }
    return false;
}

void func_effect_8007FE88(Effect* effect) {
    Vec3f srcVelocity;
    Vec3f destVelocity;
    Vec3f velocity;
    f32 var_fa0 = 0.0f;

    if (effect->timer_50 == 0) {
        Object_Kill(&effect->obj, effect->sfxSource);
        return;
    }

    if (func_effect_8007FD84(effect)) {
        Object_Kill(&effect->obj, effect->sfxSource);
        return;
    }

    if (gPlayer[0].barrelRollAlpha != 0) {
        var_fa0 = 100.0f;
    }

    if (fabsf(gPlayer[0].trueZpos - effect->obj.pos.z) < (50.0f + var_fa0)) {
        if ((fabsf(gPlayer[0].pos.x - effect->obj.pos.x) < (30.0f + var_fa0)) &&
            (fabsf(gPlayer[0].pos.y - effect->obj.pos.y) < (30.0f + var_fa0))) {
            if ((gPlayer[0].barrelRollAlpha != 0) || (gPlayer[0].meteoWarpTimer != 0)) {
                effect->obj.rot.y = 90.0f;
                effect->obj.rot.x = RAND_FLOAT(360.0f);
                Matrix_RotateY(gCalcMatrix, effect->obj.rot.y * M_DTOR, MTXF_NEW);
                Matrix_RotateX(gCalcMatrix, effect->obj.rot.x * M_DTOR, MTXF_APPLY);
                srcVelocity.x = 0.0f;
                srcVelocity.y = 0.0f;
                srcVelocity.z = 100.0f;
                Matrix_MultVec3f(gCalcMatrix, &srcVelocity, &destVelocity);
                effect->vel.x = destVelocity.x;
                effect->vel.y = destVelocity.y;
                effect->vel.z = destVelocity.z;
                gPlayer[0].unk_2C4++;
                AUDIO_PLAY_SFX(NA_SE_ROLLING_REFLECT, effect->sfxSource, 0);
            }

            if ((gPlayer[0].barrelRollAlpha == 0) && (gPlayer[0].timer_498 == 0)) {
                Player_ApplyDamage(gPlayer, 0, effect->info.damage);
                gPlayer[0].knockback.x = 20.0f;
                if (effect->vel.x < 0.0f) {
                    gPlayer[0].knockback.x *= -1.0f;
                }
                if (gCurrentLevel != LEVEL_MACBETH) {
                    gPlayer[0].knockback.y = 20.0f;
                    if (effect->vel.y < 0.0f) {
                        gPlayer[0].knockback.y *= -1.0f;
                    }
                }
                Object_Kill(&effect->obj, effect->sfxSource);
            }
        }
    }

    if (gGroundType == 4) {
        if (Ground_801B6AEC(effect->obj.pos.x, effect->obj.pos.y, effect->obj.pos.z + gPathProgress) != 0) {
            Object_Kill(&effect->obj, effect->sfxSource);
        }
    } else if (effect->obj.pos.y < gGroundHeight) {
        Object_Kill(&effect->obj, effect->sfxSource);
        if (gGroundSurface != SURFACE_WATER) {
            effect->obj.pos.y = gGroundHeight;
            func_effect_8007D074(effect->obj.pos.x, effect->obj.pos.y, effect->obj.pos.z, 2.0f);
        }
    }

    velocity.x = effect->vel.x;
    velocity.y = effect->vel.y;
    velocity.z = effect->vel.z;

    if (gCurrentLevel != LEVEL_MACBETH) {
        if (Object_CheckCollision(1000, &effect->obj.pos, &velocity, 2) != 0) {
            func_effect_8007D10C(effect->obj.pos.x, effect->obj.pos.y, effect->obj.pos.z, 2.0f);
            Object_Kill(&effect->obj, effect->sfxSource);
        }
    } else if (Macbeth_801A55D4(1000, &effect->obj.pos, &velocity, 0) != 0) {
        func_effect_8007D10C(effect->obj.pos.x, effect->obj.pos.y, effect->obj.pos.z, 2.0f);
        Object_Kill(&effect->obj, effect->sfxSource);
    }
}

void func_effect_800802B8(Effect* effect) {
    func_effect_8007FE88(effect);
}

void func_effect_800802D8(Effect* effect) {
    func_effect_8007FE88(effect);
}

void func_effect_800802F8(Effect* effect) {
    func_effect_8007FE88(effect);
    effect->obj.rot.z += 10.0f;
    effect->scale2 = 3.0f;
    if ((gGameFrameCount % 2) != 0) {
        effect->scale2 = 3.5f;
    }
}

void func_effect_80080360(Effect* effect) {
    effect->obj.rot.z += 8.0f;
    effect->scale2 += 0.1f;
    // It seems they forgot that unk_4A is s16 and not a float...
    effect->unk_4A -= 3.5f;
    if (effect->unk_4A < 50.0f) {
        effect->unk_4A = 50;
    }
    func_effect_8007A774(gPlayer, effect, 50.0f);
}

void func_effect_8008040C(Effect* effect) {
    f32 xRot;
    f32 yRot;
    f32 temp;
    f32 var_fa0 = 0.0f;
    Vec3f srcVelocity;
    Vec3f destVelocity;
    Vec3f sp3C;

    switch (effect->state) {
        case 0:
            yRot = Math_Atan2F(gPlayer[0].pos.x - effect->obj.pos.x, gPlayer[0].trueZpos - effect->obj.pos.z);
            temp = sqrtf(SQ(gPlayer[0].pos.x - effect->obj.pos.x) + SQ(gPlayer[0].trueZpos - effect->obj.pos.z));
            xRot = -Math_Atan2F(gPlayer[0].pos.y - effect->obj.pos.y, temp);
            Matrix_RotateY(gCalcMatrix, yRot, MTXF_NEW);
            Matrix_RotateX(gCalcMatrix, xRot, MTXF_APPLY);
            srcVelocity.y = 0.0f;
            srcVelocity.x = 0.0f;
            srcVelocity.z = 100.0f;
            Matrix_MultVec3f(gCalcMatrix, &srcVelocity, &destVelocity);
            effect->vel.x = destVelocity.x + gPathVelX;
            effect->vel.y = destVelocity.y + gPathVelY;
            effect->vel.z = destVelocity.z - gPathVelZ;
            effect->state++;
            break;

        case 1:
            effect->obj.rot.z = 360.0f - effect->obj.rot.z;
            if (effect->timer_50 == 0) {
                Object_Kill(&effect->obj, effect->sfxSource);
                return;
            }

            if (func_effect_8007FD84(effect)) {
                Object_Kill(&effect->obj, effect->sfxSource);
                return;
            }

            if (gPlayer[0].barrelRollAlpha != 0) {
                var_fa0 = 100.0f;
            }

            if (fabsf(gPlayer[0].trueZpos - effect->obj.pos.z) < (50.0f + var_fa0)) {
                if ((fabsf(gPlayer[0].pos.x - effect->obj.pos.x) < (30.0f + var_fa0)) &&
                    (fabsf(gPlayer[0].pos.y - effect->obj.pos.y) < (30.0f + var_fa0))) {
                    if ((gPlayer[0].barrelRollAlpha != 0) || (gPlayer[0].meteoWarpTimer != 0)) {
                        effect->obj.rot.y = 90.0f;
                        effect->obj.rot.x = RAND_FLOAT(360.0f);
                        Matrix_RotateY(gCalcMatrix, effect->obj.rot.y * M_DTOR, MTXF_NEW);
                        Matrix_RotateX(gCalcMatrix, effect->obj.rot.x * M_DTOR, MTXF_APPLY);
                        srcVelocity.y = 0.0f;
                        srcVelocity.x = 0.0f;
                        srcVelocity.z = 100.0f;
                        Matrix_MultVec3f(gCalcMatrix, &srcVelocity, &destVelocity);
                        effect->vel.x = destVelocity.x;
                        effect->vel.y = destVelocity.y;
                        effect->vel.z = destVelocity.z;
                        gPlayer[0].unk_2C4++;
                        AUDIO_PLAY_SFX(NA_SE_ROLLING_REFLECT, effect->sfxSource, 0);
                    }

                    if ((gPlayer[0].barrelRollAlpha == 0) && (gPlayer[0].timer_498 == 0)) {
                        Player_ApplyDamage(gPlayer, 0, effect->info.damage);
                        gPlayer[0].knockback.x = 20.0f;
                        if (effect->vel.x < 0.0f) {
                            gPlayer[0].knockback.x *= -1.0f;
                        }
                        gPlayer[0].knockback.y = 20.0f;
                        if (effect->vel.y < 0.0f) {
                            gPlayer[0].knockback.y *= -1.0f;
                        }
                        Object_Kill(&effect->obj, effect->sfxSource);
                    }
                }

                if (gGroundType == 4) {
                    if (Ground_801B6AEC(effect->obj.pos.x, effect->obj.pos.y, effect->obj.pos.z + gPathProgress) != 0) {
                        Object_Kill(&effect->obj, effect->sfxSource);
                    }
                } else if (effect->obj.pos.y < gGroundHeight) {
                    Object_Kill(&effect->obj, effect->sfxSource);
                    if (gGroundSurface != SURFACE_WATER) {
                        effect->obj.pos.y = gGroundHeight;
                        func_effect_8007D074(effect->obj.pos.x, effect->obj.pos.y, effect->obj.pos.z, 2.0f);
                    }
                }

                sp3C.x = effect->vel.x;
                sp3C.y = effect->vel.y;
                sp3C.z = effect->vel.z;

                if (Object_CheckCollision(1000, &effect->obj.pos, &sp3C, 2) != 0) {
                    func_effect_8007D10C(effect->obj.pos.x, effect->obj.pos.y, effect->obj.pos.z, 2.0f);
                    Object_Kill(&effect->obj, effect->sfxSource);
                }
            }
            break;
    }

    func_effect_8007A774(gPlayer, effect, 50.0f);
}

void func_effect_8008092C(Effect* effect) {
    switch (effect->unk_44) {
        case 0:
            RCP_SetupDL(&gMasterDisp, SETUPDL_49);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);
            gDPSetEnvColor(gMasterDisp++, 255, 0, 0, 255);
            Matrix_Scale(gGfxMatrix, 4.0f, 2.0f, 4.0f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_ZO_6018AF0);
            break;

        case 1:
            RCP_SetupDL(&gMasterDisp, SETUPDL_49);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);
            gDPSetEnvColor(gMasterDisp++, 255, 0, 0, 255);
            Matrix_RotateZ(gGfxMatrix, 30.0f * M_DTOR, MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, 3.0f, 1.5f, 3.0f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_1024AC0);
            break;
    }
}

void func_effect_80080ACC(Effect* effect) {
    s16 temp_ft2;

    switch (effect->unk_78) {
        case 0:
            break;

        case 1:
            effect->unk_46--;
            break;

        case 10:
            effect->unk_44--;
            if (effect->unk_44 <= 0) {
                effect->unk_44 = effect->unk_46;
            }
            temp_ft2 = (((f32) effect->unk_44 / (f32) effect->unk_46) * 255.0f);
            effect->unk_48 = temp_ft2;
            if (temp_ft2 > 255) {
                effect->unk_48 = 255;
            }
            if (effect->unk_48 < 32) {
                Object_Kill(&effect->obj, effect->sfxSource);
            }
            break;

        case 11:
            effect->obj.rot.z += effect->unk_60.z;
            effect->scale2 += 0.07f;
            effect->vel.y += 0.2f;
            effect->unk_44 += effect->unk_46;
            if (effect->unk_44 < 10) {
                Object_Kill(&effect->obj, effect->sfxSource);
            }
            break;

        case 12:
            effect->obj.rot.x += effect->unk_60.x;
            effect->obj.rot.y += effect->unk_60.y;
            effect->obj.rot.z += effect->unk_60.z;
            if ((effect->unk_44 == 0) && (effect->obj.pos.y < gGroundHeight)) {
                Object_Kill(&effect->obj, effect->sfxSource);
            }
            if (effect->unk_44 != 0) {
                effect->unk_44--;
            }
            effect->vel.y -= 4.0f;
            break;

        case 16:
            break;

        case 100:
            func_effect_8007E45C(effect);
            break;

        case 101:
            func_effect_8007BCE8(effect);
            break;

        case 102:
            func_effect_8007B758(effect);
            break;
    }
}

void func_effect_80080D04(Effect* effect) {
    static s32 D_800D18E4 = 0;
    s32 i;
    s32 alpha;

    switch (effect->unk_7A) {
        case 0:
            if (effect->unk_44 != 64) {
                RCP_SetupDL(&gMasterDisp, effect->unk_44);
            }
            gSPDisplayList(gMasterDisp++, effect->unk_74);
            if (effect->unk_44 != 64) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_64);
            }
            break;

        case 1:
            if (effect->unk_48 == 0) {
                effect->unk_48 = effect->unk_46;
            }

            if (effect->unk_44 != 64) {
                RCP_SetupDL(&gMasterDisp, effect->unk_44);
            }

            alpha = (((f32) effect->unk_46 / (f32) effect->unk_48) * 255.0f);
            if (alpha > 255) {
                alpha = 255;
            }

            if (alpha < 32) {
                Object_Kill(&effect->obj, effect->sfxSource);
            } else {
                gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, alpha);
                gSPDisplayList(gMasterDisp++, effect->unk_74);
            }

            if (effect->unk_44 != 64) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_64);
            }
            break;

        case 10:
            RCP_SetupDL(&gMasterDisp, SETUPDL_65);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, effect->unk_48);
            Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, effect->scale2, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_TI_A000000);
            RCP_SetupDL(&gMasterDisp, SETUPDL_64);
            break;

        case 11:
            RCP_SetupDL(&gMasterDisp, SETUPDL_68);
            Graphics_SetScaleMtx(effect->scale2);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 120, 60, 0, effect->unk_44);
            gDPSetEnvColor(gMasterDisp++, 0, 0, 0, 0);
            gSPDisplayList(gMasterDisp++, D_1023750);
            RCP_SetupDL(&gMasterDisp, SETUPDL_64);
            break;

        case 12:
            Graphics_SetScaleMtx(effect->scale2);
            RCP_SetupDL(&gMasterDisp, SETUPDL_23);
            gSPDisplayList(gMasterDisp++, D_VE1_9013C20);
            RCP_SetupDL(&gMasterDisp, SETUPDL_64);
            break;

        case 13:
            Graphics_SetScaleMtx(effect->scale2);
            RCP_SetupDL(&gMasterDisp, SETUPDL_68);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, effect->unk_44);
            gDPSetEnvColor(gMasterDisp++, 36, 45, 28, 0);
            gSPDisplayList(gMasterDisp++, D_1023750);
            RCP_SetupDL(&gMasterDisp, SETUPDL_64);
            break;

        case 14:
            Graphics_SetScaleMtx(effect->scale2);
            RCP_SetupDL(&gMasterDisp, SETUPDL_68);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, effect->unk_44);
            gDPSetEnvColor(gMasterDisp++, 255, 255, 255, 0);
            gSPDisplayList(gMasterDisp++, D_1023750);
            RCP_SetupDL(&gMasterDisp, SETUPDL_64);
            break;

        case 15:
            Graphics_SetScaleMtx(effect->scale2);
            RCP_SetupDL(&gMasterDisp, SETUPDL_68);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, effect->unk_4A);
            gDPSetEnvColor(gMasterDisp++, 36, 45, 28, 0);
            gSPDisplayList(gMasterDisp++, D_1023750);
            RCP_SetupDL(&gMasterDisp, SETUPDL_64);
            break;

        case 16:
            Graphics_SetScaleMtx(effect->scale2);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 96, 96, 255, 255);
            Matrix_Translate(gGfxMatrix, 34.14f, 0.0f, 0.0f, MTXF_APPLY);
            Matrix_Push(&gGfxMatrix);
            Matrix_Scale(gGfxMatrix, 0.25f, 1.0f, 1.0f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_102F5E0);
            Matrix_Pop(&gGfxMatrix);

            for (i = 0; i < 7; i++) {
                Matrix_Translate(gGfxMatrix, 0.0f, 10.0f, 0.0f, MTXF_APPLY);
                Matrix_RotateZ(gGfxMatrix, M_PI / 4, MTXF_APPLY);
                Matrix_Translate(gGfxMatrix, 1.0f, 20.0f, 0.0f, MTXF_APPLY);
                Matrix_Push(&gGfxMatrix);
                Matrix_Scale(gGfxMatrix, 0.25f, 1.0f, 1.0f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_102F5E0);
                Matrix_Pop(&gGfxMatrix);
            }
            effect->obj.rot.z += 1.0f;
            break;

        case 17:
            //! DEBUG: some code used for debugging with the 4th controller
            if ((gControllerPress[3].button & U_JPAD) && (D_800D18E4 > 0)) {
                D_800D18E4--;
            }
            if ((gControllerPress[3].button & D_JPAD) && (D_800D18E4 < 12)) {
                D_800D18E4++;
            }

            if (((effect->index + gGameFrameCount) % 2) == 0) {
                gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
            } else {
                gDPSetPrimColor(gMasterDisp++, 0, 0, 96, 96, 255, 255);
            }

            Graphics_SetScaleMtx(effect->scale2);

            for (i = 0; i < 10; i++) {
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, 0.0f, -60.0f, 0.0f, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, 0.8f, 3.0f, 1.0f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_102F5E0);
                Matrix_Pop(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, 0.0f, -120.0f, 0.0f, MTXF_APPLY);
                Matrix_RotateZ(gGfxMatrix, D_800D1534[D_800D18E4][i] * M_DTOR, MTXF_APPLY);
            }
            break;

        case 18:
            RCP_SetupDL(&gMasterDisp, SETUPDL_48);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 190, 255);
            gDPSetEnvColor(gMasterDisp++, 239, 15, 0, 255);
            Graphics_SetScaleMtx(effect->scale2);
            gSPDisplayList(gMasterDisp++, D_1024AC0);
            break;
    }
}

void func_effect_800815DC(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        if ((gEffects[i].obj.id == OBJ_EFFECT_366 || (gEffects[i].obj.id == OBJ_EFFECT_395 && gEffects[i].state == 1) ||
             gEffects[i].obj.id == OBJ_EFFECT_364 || gEffects[i].obj.id == OBJ_EFFECT_346) &&
            gEffects[i].obj.status == OBJ_ACTIVE) {
            gEffects[i].obj.status = OBJ_FREE;
            break;
        }
    }
}

void func_effect_8008165C(Effect* effect, f32 xPos, f32 yPos, f32 zPos, f32 scale2, s32 arg5) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = OBJ_EFFECT_395;

    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;

    effect->scale2 = scale2;
    effect->state = arg5;
    Object_SetInfo(&effect->info, effect->obj.id);
    effect->timer_50 = 300;

    switch (effect->state) {
        case 4:
            effect->unk_4A = 255;
            effect->unk_46 = 1;
            break;

        case 5:
            effect->vel.x = RAND_FLOAT_CENTERED(20.0f);
            effect->vel.y = RAND_FLOAT(20.0f) + 30.0f;
            effect->vel.z = RAND_FLOAT(30.0f);

            effect->unk_46 = 5;
            effect->unk_44 = RAND_FLOAT_CENTERED(20.0f) * 1.5f;
            effect->info.unk_14 = 0;
            effect->unk_4A = 255;
            break;

        case 6:
            effect->unk_4A = 255;
            effect->unk_46 = 10;
            break;

        case 7:
            effect->vel.y = RAND_FLOAT(7.0f) + 7.0f;
            effect->vel.x = RAND_FLOAT_CENTERED(10.0f);
            effect->vel.z = RAND_FLOAT_CENTERED(10.0f);

            effect->scale2 = (RAND_FLOAT(0.8f) + 0.3f) * scale2;
            effect->timer_50 = RAND_INT(50.0f) + 70;
            effect->obj.rot.x = RAND_FLOAT(360.0f);

            effect->unk_60.x = RAND_FLOAT_CENTERED(30.0f);
            effect->unk_60.y = RAND_FLOAT_CENTERED(30.0f);
            effect->unk_60.z = RAND_FLOAT_CENTERED(30.0f);

            effect->info.unk_14 = 0;
            break;

        case 9:
            effect->obj.pos.x += RAND_FLOAT_CENTERED(600.0f);
            effect->obj.pos.y += RAND_FLOAT_CENTERED(600.0f);
            effect->obj.pos.z += RAND_FLOAT_CENTERED(300.0f) + 300.0f;
            effect->scale1 = 0.0f;
            effect->scale2 = RAND_FLOAT(1.0f) + 1.0f;
            break;

        case 10:
            effect->timer_50 = 10;
            AUDIO_PLAY_SFX(NA_SE_EN_A6BOSS_BEAM, effect->sfxSource, 4);
            break;

        case 11:
            effect->scale1 = 255.0f;
            effect->vel.y = 20.0f;
            if (effect->scale2 > 10.0f) {
                effect->scale2 = 10.0f;
            }
            break;

        case 12:
            effect->scale1 = scale2;
            effect->scale2 = 1.0f;
            effect->timer_50 = 50;
            effect->unk_44 = 100;

            effect->obj.pos.x = xPos;
            effect->obj.pos.y = yPos;
            effect->obj.pos.z = zPos;

            AUDIO_PLAY_SFX(NA_SE_EN_STAR_EXPLOSION, effect->sfxSource, 4);
            gControllerRumbleTimers[0] = 60;
            break;
    }
}

void func_effect_80081A8C(f32 xPos, f32 yPos, f32 zPos, f32 scale2, s32 arg4) {
    s32 i;

    if (arg4 == 6 || arg4 == 7) {
        func_effect_800815DC();
    }

    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            func_effect_8008165C(&gEffects[i], xPos, yPos, zPos, scale2, arg4);
            break;
        }
    }
}

s32 func_effect_80081B24(f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    s32 i;
    Effect* effect;

    func_effect_800815DC();

    for (i = 0, effect = gEffects; i < ARRAY_COUNT(gEffects); i++, effect++) {
        if (effect->obj.status == OBJ_FREE) {
            Effect_Initialize(effect);
            effect->obj.status = OBJ_ACTIVE;
            effect->obj.id = OBJ_EFFECT_395;

            effect->obj.pos.x = xPos;
            effect->obj.pos.y = yPos;
            effect->obj.pos.z = zPos;

            effect->scale2 = scale2;
            effect->timer_50 = 80;
            effect->state = 2;
            Object_SetInfo(&effect->info, effect->obj.id);
            break;
        }
    }
    if (i == ARRAY_COUNT(gEffects)) {
        i = 0;
    }
    return i;
}

void func_effect_80081BEC(f32 xPos, f32 yPos, f32 zPos, f32 scale2, s32 arg4) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            func_effect_8008165C(&gEffects[i], xPos, yPos, zPos, scale2, arg4);
            break;
        }
    }
}

static f32 D_800D18E8 = 0.0f;
static f32 D_800D18EC = 0.0f;

void func_effect_80081C5C(Effect* effect) {
    f32 sp84;
    f32 posXDiff;
    f32 posYDiff;
    f32 posZDiff;
    f32 xRotDeg;
    f32 yRotDeg;
    f32 posYOut;
    s32 unusedOut;
    Vec3f velocity;
    Vec3f velocityDest;

    velocity.x = effect->vel.x;
    velocity.y = effect->vel.y;
    velocity.z = effect->vel.z;

    //! FAKE: Probably some debug stuff printing different messages depending on what unk_4E is.
    if (effect->state != 0 && effect->state != 6 && effect->state != 7 && effect->state != 11) {
        if (gCurrentLevel) {}
        PRINTF("ＺＯ＿ＭＯＶＥ ＨＥＬＰ %d\n");
    }
    if (effect->state != 1 && effect->state != 2 && effect->state != 4 && effect->state != 5 && effect->state != 8 &&
        effect->state != 9) {
        if (gCurrentLevel) {}
        PRINTF("ＡＣ＿ＭＯＶＥ ＨＥＬＰ %d\n");
    }

    switch (effect->state) {
        case 0:
            if (effect->timer_50 == 0) {
                Object_Kill(&effect->obj, effect->sfxSource);
                break;
            }

            if (((gGameFrameCount % 2) == 0)) {
                func_effect_8007C484(RAND_FLOAT_CENTERED(50.0f) + effect->obj.pos.x,
                                     RAND_FLOAT_CENTERED(50.0f) + effect->obj.pos.y,
                                     RAND_FLOAT_CENTERED(50.0f) + effect->obj.pos.z, effect->vel.x, effect->vel.y,
                                     effect->vel.z, RAND_FLOAT(0.05f) + 0.05f, 0);
            }

            if (Object_CheckCollision(effect->index, &effect->obj.pos, &velocity, 1) != 0) {
                func_effect_8007B344(effect->obj.pos.x, effect->obj.pos.y, effect->obj.pos.z, 3.0f, 7);
                Object_Kill(&effect->obj, effect->sfxSource);
            }
            sp84 = 50.0f;
            break;

        case 1:
            if (effect->timer_50 == 0) {
                Object_Kill(&effect->obj, effect->sfxSource);
                break;
            }

            effect->unk_60.z += 10.0f;
            effect->vel.z = 5.0f;

            if (((gGameFrameCount % 8) == 0)) {
                effect->unk_44++;
                effect->unk_44 &= 1;
            }

            if (effect->unk_44 == 0) {
                Math_SmoothStepToF(&effect->scale2, 0.2f, 0.01f, 0.02f, 0.0f);
            } else {
                Math_SmoothStepToF(&effect->scale2, 0.5f, 0.01f, 0.02f, 0.0f);
            }

            if (Object_CheckCollision(effect->index, &effect->obj.pos, &velocity, 1) != 0) {
                Object_Kill(&effect->obj, effect->sfxSource);
                func_effect_8007D0E0(effect->obj.pos.x, effect->obj.pos.y, effect->obj.pos.z, 1.0f);
            }
            break;

        case 2:
            if (effect->timer_50 == 0) {
                Object_Kill(&effect->obj, effect->sfxSource);
                break;
            }

            switch (effect->unk_44) {
                case 1:
                case 2:
                    break;

                case 0:
                    Math_SmoothStepToF(&effect->scale2, 1.0f, 0.1f, 5.0f, 0.0001f);
                    if (effect->scale2 >= 1.0f) {
                        effect->unk_44++;
                    }
                    break;

                case 3:
                    Math_SmoothStepToF(&effect->scale2, 0.0f, 0.1f, 10.0f, 0.0001f);
                    if (effect->scale2 < 0.3f) {
                        Object_Kill(&effect->obj, effect->sfxSource);
                    }
                    break;
            }

            if (((gGameFrameCount % 4) == 0)) {
                func_effect_8007C120((RAND_FLOAT_CENTERED(effect->scale2) * 50.0f) + effect->obj.pos.x,
                                     (RAND_FLOAT_CENTERED(effect->scale2) * 50.0f) + effect->obj.pos.y,
                                     (RAND_FLOAT_CENTERED(effect->scale2) * 50.0f) + effect->obj.pos.z, effect->vel.x,
                                     effect->vel.y, effect->vel.z, RAND_FLOAT(0.03f) + 0.05f, 10);
            }
            if (Object_CheckCollision(effect->index, &effect->obj.pos, &velocity, 1) != 0) {
                func_effect_8007B344(effect->obj.pos.x, effect->obj.pos.y, effect->obj.pos.z, 3.0f, 7);
                Object_Kill(&effect->obj, effect->sfxSource);
            }
            sp84 = 50.0f;
            break;

        case 3:
            effect->info.unk_19 = 2;
            if (effect->unk_44 != 0) {
                Object_Kill(&effect->obj, effect->sfxSource);
                func_effect_8007D0E0(effect->obj.pos.x, effect->obj.pos.y, effect->obj.pos.z, 5.0f);
            } else if (fabsf(gPlayer[0].trueZpos - effect->obj.pos.z) < 1000.0f) {
                ActorEvent_SpawnEffect347(effect->obj.pos.x, effect->obj.pos.y, effect->obj.pos.z, 15.0f);
                Object_Kill(&effect->obj, effect->sfxSource);
            }
            sp84 = 50.0f;
            break;

        case 4:
            effect->scale2 += 0.07f;
            effect->unk_4A -= effect->unk_46;
            effect->obj.rot.z += 3.0f;
            effect->vel.y += 0.2f;
            if (effect->unk_4A < 0) {
                Object_Kill(&effect->obj, effect->sfxSource);
            }
            break;

        case 5:
            func_effect_80081A8C(effect->obj.pos.x, effect->obj.pos.y, effect->obj.pos.z, 5.0f, 6);
            effect->unk_4A -= effect->unk_46;
            effect->obj.rot.x += effect->unk_44;
            effect->obj.rot.y += effect->unk_44;
            effect->obj.rot.z += effect->unk_44;
            effect->vel.y -= 2.0f;
            if ((effect->unk_4A < 0) || (effect->timer_50 == 0)) {
                Object_Kill(&effect->obj, effect->sfxSource);
            }
            break;

        case 6:
            effect->unk_4A -= effect->unk_46;
            Math_SmoothStepToF(&effect->scale2, 0.0f, 0.1f, 1.0f, 0.00001f);
            if ((effect->unk_4A < 0) || (effect->timer_50 == 0)) {
                Object_Kill(&effect->obj, effect->sfxSource);
            }
            break;

        case 7:
            switch (gCurrentLevel) {
                case LEVEL_AQUAS:
                    if (((gGameFrameCount % 4) == 0)) {
                        func_effect_80081A8C(effect->obj.pos.x, effect->obj.pos.y, effect->obj.pos.z, effect->scale2,
                                             6);
                    }
                    effect->obj.rot.x += effect->unk_60.x;
                    effect->obj.rot.y += effect->unk_60.y;
                    effect->obj.rot.z += effect->unk_60.z;
                    effect->vel.y -= 0.5f;
                    if ((effect->timer_50 == 0) || (effect->obj.pos.y < gGroundHeight)) {
                        Object_Kill(&effect->obj, effect->sfxSource);
                    }
                    break;

                case LEVEL_ZONESS:
                    if (((gGameFrameCount % 4) == 0)) {
                        // clang-format off
                        func_effect_80081A8C(effect->obj.pos.x, effect->obj.pos.y, effect->obj.pos.z, effect->scale2 * 3.0f, 6);
                        // clang-format on
                    }

                    effect->obj.rot.x += effect->unk_60.x;
                    effect->obj.rot.y += effect->unk_60.y;
                    effect->obj.rot.z += effect->unk_60.z;

                    effect->vel.y -= 1.0f;

                    if ((Play_CheckDynaFloorCollision(&posYOut, &unusedOut, effect->obj.pos.x, effect->obj.pos.y,
                                                      effect->obj.pos.z)) ||
                        (effect->timer_50 == 0)) {
                        func_effect_8007B228(effect->obj.pos.x, posYOut, effect->obj.pos.z, effect->scale2);
                        Object_Kill(&effect->obj, effect->sfxSource);
                    }
                    break;
            }
            break;

        case 8:
            Math_SmoothStepToF(D_ctx_801779A8, 30.0f, 1.0f, 5.0f, 0.0f);
            Matrix_RotateY(gCalcMatrix, gBosses[0].obj.rot.y * M_DTOR, MTXF_NEW);
            Matrix_RotateX(gCalcMatrix, gBosses[0].obj.rot.x * M_DTOR, MTXF_APPLY);

            velocity.y = 0.0f;
            velocity.x = 0;
            velocity.z = 250.0f;

            if (effect->unk_44 > 0) {
                velocity.z = 2000.0f;
            }

            Matrix_MultVec3fNoTranslate(gCalcMatrix, &velocity, &velocityDest);

            effect->obj.pos.x = gBosses[0].obj.pos.x + velocityDest.x;
            effect->obj.pos.y = gBosses[0].obj.pos.y + velocityDest.y;
            effect->obj.pos.z = gBosses[0].obj.pos.z + velocityDest.z;

            switch (effect->unk_44) {
                case 0:
                    func_effect_80081BEC(effect->obj.pos.x, effect->obj.pos.y, effect->obj.pos.z, 1.0f, 9);
                    Math_SmoothStepToF(&effect->scale2, 6.0f, 0.01f, 0.05f, 0.00001f);
                    if (effect->scale2 >= 5.0f) {
                        gEffects[ARRAY_COUNT(gEffects) - 1].obj.status =
                            gEffects[ARRAY_COUNT(gEffects) - 2].obj.status = OBJ_FREE;
                        func_effect_80081BEC(effect->obj.pos.x, effect->obj.pos.y, effect->obj.pos.z, 1.0f, 10);
                        gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
                        gFillScreenAlpha = gFillScreenAlphaTarget = 255;
                        gFillScreenAlphaTarget = 0;
                        gFillScreenAlphaStep = 25;
                        effect->timer_50 = 10;
                        D_800D18EC = 0.0f;
                        D_800D18E8 = 0.0f;
                        gBosses[0].timer_050 = 150;
                        gBosses[0].state = 6;
                        effect->unk_44++;
                    }
                    break;

                case 1:
                    Math_SmoothStepToF(&effect->scale2, 8.0f, 0.1f, 1.0f, 0.00001f);
                    if (effect->timer_50 == 0) {
                        if (gFillScreenAlpha != 0) {
                            gFillScreenRed = gFillScreenGreen = gFillScreenBlue = gFillScreenAlpha = 0;
                        }
                        effect->timer_50 = gBosses[0].timer_050;
                        effect->unk_44++;
                    }
                    break;

                case 2:
                    if (effect->timer_50 == 0) {
                        Math_SmoothStepToF(&effect->scale2, 0.0f, 1.0f, 10.0f, 0.00001f);
                        if (effect->scale2 == 0.0f) {
                            Object_Kill(&effect->obj, effect->sfxSource);
                        }
                    } else {
                        Math_SmoothStepToF(&effect->scale2, 8.0f, 0.1f, 1.0f, 0.00001f);
                    }
                    break;
            }
            break;

        case 9:
            posXDiff = gBosses[0].obj.pos.x - effect->obj.pos.x;
            posYDiff = gBosses[0].obj.pos.y - effect->obj.pos.y;
            posZDiff = gBosses[0].obj.pos.z - effect->obj.pos.z;

            yRotDeg = Math_RadToDeg(Math_Atan2F(posXDiff, posZDiff));
            xRotDeg = Math_RadToDeg(-Math_Atan2F(posYDiff, sqrtf(SQ(posXDiff) + SQ(posZDiff))));

            Matrix_RotateY(gCalcMatrix, M_DTOR * yRotDeg, MTXF_NEW);
            Matrix_RotateX(gCalcMatrix, M_DTOR * xRotDeg, MTXF_APPLY);

            velocity.x = velocity.y = 0.0f;
            velocity.z = 20.0f;

            Matrix_MultVec3fNoTranslate(gCalcMatrix, &velocity, &velocityDest);

            effect->vel.x = velocityDest.x;
            effect->vel.y = velocityDest.y;
            effect->vel.z = -50.0f;

            effect->unk_44++;
            Math_SmoothStepToF(&effect->scale1, 255.0f, 1.0f, 20.0f, 0.0f);
            Math_SmoothStepToF(&effect->vel.z, -70.0f, 0.01f, 0.1f, 0.0f);
            Math_SmoothStepToF(&effect->scale2, 0.0f, 0.1f, 0.5f, 0.00001f);
            if (effect->scale2 == 0.0f) {
                Object_Kill(&effect->obj, effect->sfxSource);
            }
            break;

        case 10:
            switch (effect->unk_44) {
                case 0:
                    D_ctx_801779A8[0] = 50.0f;
                    if (effect->unk_46 == 10) {
                        gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
                        gFillScreenAlpha = gFillScreenAlphaTarget = 255;
                        gFillScreenAlphaTarget = 0;
                        gFillScreenAlphaStep = 25;
                        gCameraShake = 50;
                    }
                    if (effect->unk_46 == 0) {
                        gFillScreenRed = gFillScreenGreen = gFillScreenBlue = gFillScreenAlpha = 0;
                        effect->unk_46 = 50;
                    }
                    if (effect->unk_46 != 0) {
                        effect->unk_46--;
                    }
                    if ((((gGameFrameCount % 16) == 0)) && (effect->timer_50 == 0)) {
                        D_800D18EC =
                            RAD_TO_DEG(Math_Atan2F(gPlayer[0].cam.eye.x - gBosses[0].obj.pos.x,
                                                   gPlayer[0].cam.eye.z - (gBosses[0].obj.pos.z + gPathProgress)));

                        D_800D18E8 = RAD_TO_DEG(
                            -Math_Atan2F(gPlayer[0].cam.eye.y - gBosses[0].obj.pos.y,
                                         sqrtf(SQ(gPlayer[0].cam.eye.z - (gBosses[0].obj.pos.z + gPathProgress)) +
                                               SQ(gPlayer[0].cam.eye.x - gBosses[0].obj.pos.x))));
                    }
                    if (gBosses[0].timer_050 == 0) {
                        gBosses[0].swork[39] = effect->index;
                        effect->unk_44 = 1;
                    }
                    break;

                case 1:
                    Math_SmoothStepToF(D_ctx_801779A8, 20.0f, 1.0f, 5.0f, 0.0f);
                    break;
            }

            effect->info.unk_14 = 0;

            Math_SmoothStepToAngle(&gBosses[0].obj.rot.x, D_800D18E8, 0.1f, 1.0f, 0.00001f);
            Math_SmoothStepToAngle(&gBosses[0].obj.rot.y, D_800D18EC, 0.1f, 1.0f, 0.00001f);

            effect->obj.rot.x = gBosses[0].obj.rot.x;
            effect->obj.rot.y = gBosses[0].obj.rot.y;
            effect->obj.rot.z += 30.0f;

            Matrix_RotateY(gCalcMatrix, gBosses[0].obj.rot.y * M_DTOR, MTXF_NEW);
            Matrix_RotateX(gCalcMatrix, gBosses[0].obj.rot.x * M_DTOR, MTXF_APPLY);

            velocity.x = velocity.y = 0.0f;
            velocity.z = 250.0f;

            Matrix_MultVec3fNoTranslate(gCalcMatrix, &velocity, &velocityDest);

            effect->obj.pos.x = gBosses[0].obj.pos.x + velocityDest.x;
            effect->obj.pos.y = gBosses[0].obj.pos.y + velocityDest.y;
            effect->obj.pos.z = gBosses[0].obj.pos.z + velocityDest.z;

            if (effect->unk_44 == 0) {
                Math_SmoothStepToF(&effect->unk_60.x, 5.0f, 0.1f, 1.0f, 0.00001f);
                Math_SmoothStepToF(&effect->unk_60.y, 5.0f, 0.1f, 1.0f, 0.00001f);
                Math_SmoothStepToF(&effect->unk_60.z, 50.0f, 1.0f, 2.0f, 0.00001f);
            }

            velocity.x = velocity.y = 0.0f;
            velocity.z = fabsf(gPlayer[0].trueZpos - effect->obj.pos.z);

            Matrix_MultVec3fNoTranslate(gCalcMatrix, &velocity, &velocityDest);

            if ((((effect->timer_50 == 0) &&
                  (fabsf(gPlayer[0].pos.x - (effect->obj.pos.x + velocityDest.x)) <= (effect->unk_60.x * 50.0f))) &&
                 (fabsf(gPlayer[0].pos.y - (effect->obj.pos.y + velocityDest.y)) <= (effect->unk_60.y * 50.0f))) &&
                (gPlayer[0].timer_498 == 0)) {
                Player_ApplyDamage(gPlayer, 0, 40);
            }
            break;

        case 11:
            effect->obj.rot.z += 20.0f;
            effect->vel.y -= 2.0f;
            if (effect->vel.y < (-20.0f)) {
                effect->vel.y = -20.0f;
            }

            Math_SmoothStepToF(&effect->scale1, 0.0f, 0.1f, 100.0f, 0.00001f);

            if ((effect->scale1 < 1.0f) || (effect->timer_50 == 0)) {
                Object_Kill(&effect->obj, effect->sfxSource);
            }
            break;

        case 12:
            func_effect_8007A28C(effect);
            break;
    }

    if ((effect->state == 2) && (effect->unk_44 == 2)) {
        func_effect_8007FE88(effect);
    }
    if ((effect->state < 4) && (effect->state != 1)) {
        func_effect_8007A774(gPlayer, effect, sp84);
    }
}

void func_effect_80082F78(Effect* effect) {
    //! FAKE: Probably some debug stuff printing different messages depending on what unk_4E is.
    if (effect->state != 0 && effect->state != 6) {
        if (effect->unk_4A && effect->unk_4A) {}
        PRINTF("ＺＯ＿ＤＩＳＰ ＨＥＬＰ %d\n");
    }
    if (effect->state != 1 && effect->state != 2 && effect->state != 4 && effect->state != 5 && effect->state != 7) {
        if (effect->unk_4A && !effect->scale2) {}
        PRINTF("ＡＣ＿ＤＩＳＰ ＨＥＬＰ %d\n");
    }

    switch (effect->state) {
        case 0:
            RCP_SetupDL(&gMasterDisp, SETUPDL_49);
            Matrix_Scale(gGfxMatrix, 0.7f, 0.7f, 1.0f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
            gDPSetEnvColor(gMasterDisp++, 32, 32, 255, 255);
            gSPDisplayList(gMasterDisp++, D_1024AC0);
            break;

        case 1:
            RCP_SetupDL(&gMasterDisp, SETUPDL_41);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
            Graphics_SetScaleMtx(effect->scale2);
            gSPDisplayList(gMasterDisp++, D_101C2E0);
            break;

        case 2:
            RCP_SetupDL(&gMasterDisp, SETUPDL_49);
            Matrix_Scale(gGfxMatrix, effect->scale2, effect->scale2, effect->scale2, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
            gDPSetEnvColor(gMasterDisp++, 32, 32, 255, 255);
            gSPDisplayList(gMasterDisp++, D_1024AC0);
            break;

        case 3:
            RCP_SetupDL_60(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
            gSPDisplayList(gMasterDisp++, D_A6_601A120);
            break;

        case 4:
            Graphics_SetScaleMtx(effect->scale2);
            RCP_SetupDL(&gMasterDisp, SETUPDL_68);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 0, 0, 0, effect->unk_4A);
            gDPSetEnvColor(gMasterDisp++, 0, 0, 0, 0);
            gSPDisplayList(gMasterDisp++, D_1023750);
            break;

        case 5:
        case 7:
            Graphics_SetScaleMtx(effect->scale2);
            RCP_SetupDL(&gMasterDisp, SETUPDL_60);
            if (gCurrentLevel == LEVEL_AQUAS) {
                gSPDisplayList(gMasterDisp++, D_AQ_600A220);
            }
            if (gCurrentLevel == LEVEL_ZONESS) {
                gSPDisplayList(gMasterDisp++, D_ZO_6016880);
            }
            break;

        case 6:
            Graphics_SetScaleMtx(effect->scale2);
            if (gCurrentLevel == LEVEL_ZONESS) {
                Graphics_SetScaleMtx(effect->scale2);
            }
            RCP_SetupDL(&gMasterDisp, SETUPDL_64);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 0, 255, 0, effect->unk_4A);
            gSPDisplayList(gMasterDisp++, D_1023750);
            break;

        case 8:
            RCP_SetupDL(&gMasterDisp, SETUPDL_49);
            Matrix_Scale(gGfxMatrix, effect->scale2, effect->scale2, effect->scale2, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
            gDPSetEnvColor(gMasterDisp++, 255, 0, 128, 255);
            gSPDisplayList(gMasterDisp++, D_1024AC0);
            break;

        case 9:
            RCP_SetupDL(&gMasterDisp, SETUPDL_49);
            Matrix_Scale(gGfxMatrix, effect->scale2, effect->scale2, effect->scale2, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, effect->scale1);
            gDPSetEnvColor(gMasterDisp++, 255, 255, 128, 255);
            gSPDisplayList(gMasterDisp++, D_1024AC0);
            break;

        case 10:
            if (gPlayState != PLAY_PAUSE) {
                Texture_Scroll(D_A6_6012840, 16, 16, 0);
            }
            RCP_SetupDL(&gMasterDisp, SETUPDL_53);
            Matrix_Scale(gGfxMatrix, effect->unk_60.x, effect->unk_60.y, effect->unk_60.z, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
            gSPDisplayList(gMasterDisp++, D_A6_6012550);
            break;

        case 11:
            RCP_SetupDL(&gMasterDisp, SETUPDL_67);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 111, 111, 111, (s32) effect->scale1);
            gDPSetEnvColor(gMasterDisp++, 255, 255, 255, 255);
            Graphics_SetScaleMtx(effect->scale2);
            gSPDisplayList(gMasterDisp++, D_1024AC0);
            break;

        case 12:
            func_effect_8007A3C0(effect);
            break;
    }

    RCP_SetupDL(&gMasterDisp, SETUPDL_64);
}

void func_effect_800836C0(Effect* effect, f32 xPos, f32 yPos, f32 zPos, f32 arg4, f32 scale) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = OBJ_EFFECT_391;

    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;

    effect->unk_60.x = scale * 0.8f;
    effect->unk_60.y = 1.2f;

    if (arg4 != 0.0f) {
        effect->unk_60.y = arg4;
    }
    effect->unk_44 = 230;
    effect->scale1 = scale;
    effect->scale2 = 0.1f;
    Object_SetInfo(&effect->info, effect->obj.id);
}

void func_effect_8008377C(f32 xPos, f32 yPos, f32 zPos, f32 arg3, f32 scale) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            func_effect_800836C0(&gEffects[i], xPos, yPos, zPos, arg3, scale);
            break;
        }
    }
}

void func_effect_800837EC(Effect* effect) {
    s32 pad[2];
    f32 var_fv1;
    s32 var_s2;
    s32 i;

    switch (effect->state) {
        case 0:
            if (effect->unk_60.y == 1.2f) {
                Math_SmoothStepToF(&effect->scale2, effect->scale1, 0.5f, effect->scale1, 0.01f);
            } else {
                Math_SmoothStepToF(&effect->scale2, effect->scale1, 1.0f, effect->scale1 * 0.1f, 0.01f);
            }

            if (effect->scale2 > (effect->scale1 * 0.7f)) {
                Math_SmoothStepToF(&effect->unk_60.x, effect->scale2 * 1.3f, 0.1f, 0.5f, 0.0001f);
            }

            if (effect->scale2 == effect->scale1) {
                var_s2 = effect->scale2 * 5.0f;
                if (var_s2 < 5) {
                    var_s2 = 5;
                }
                if (var_s2 > 10) {
                    var_s2 = 10;
                }
                var_fv1 = effect->unk_60.y * 300.0f;
                if (effect->unk_60.y == 1.2f) {
                    var_fv1 = effect->unk_60.y * 100.0f;
                }
                for (i = 0; i < var_s2; i++) {
                    func_effect_80081BEC(effect->obj.pos.x + RAND_FLOAT_CENTERED(effect->scale2 * 200.0f),
                                         effect->obj.pos.y + var_fv1 + RAND_FLOAT_CENTERED(effect->scale2 * 100.0f),
                                         effect->obj.pos.z + RAND_FLOAT_CENTERED(effect->scale2 * 200.0f),
                                         0.3f - RAND_FLOAT_CENTERED(0.2f), 11);
                }
                effect->state++;
            }
            break;

        case 1:
            effect->vel.y -= 4.0f;
            Math_SmoothStepToF(&effect->scale2, 0.0f, 0.01f, 0.1f, 0.0001f);
            Math_SmoothStepToF(&effect->unk_60.x, effect->scale2 * 1.3f, 0.1f, 0.5f, 0.0001f);
            effect->unk_44 -= 35;
            if (effect->unk_44 < 0) {
                Object_Kill(&effect->obj, effect->sfxSource);
            }
            break;
    }

    effect->obj.rot.y = RAD_TO_DEG(Math_Atan2F(gPlayer[0].cam.eye.x - effect->obj.pos.x,
                                               gPlayer[0].cam.eye.z - (effect->obj.pos.z + gPathProgress)));
}

void func_effect_80083B8C(Effect* effect) {
    RCP_SetupDL_49();
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, effect->unk_44);
    gDPSetEnvColor(gMasterDisp++, 36, 45, 28, 255);
    Matrix_Scale(gGfxMatrix, effect->unk_60.x, effect->scale2 * effect->unk_60.y, effect->scale2, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_ZO_601BAD0);
    RCP_SetupDL(&gMasterDisp, SETUPDL_64);
}

void func_effect_80083C70(Effect* effect, f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 arg7,
                          s32 arg8) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = OBJ_EFFECT_399;
    effect->obj.pos.x = xPos;
    effect->unk_60.x = xPos;
    effect->unk_60.y = yPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;

    effect->vel.x = xVel;
    effect->vel.y = yVel;
    effect->vel.z = zVel;

    effect->unk_60.z = arg7;
    effect->scale2 = 1.6f;
    effect->scale1 = 0.0f;
    effect->timer_50 = 100;
    effect->unk_44 = arg8;
    Object_SetInfo(&effect->info, effect->obj.id);
}

void func_effect_80083D2C(f32 xPos, f32 yPos, f32 zPos, f32 srcZ) {
    s32 i;
    s32 j;
    s32 pad1;
    f32 x;
    f32 y;
    f32 z;
    f32 xRot;
    f32 yRot;
    f32 xSway;
    s32 pad2;
    Vec3f src;
    Vec3f dest;

    if (gCurrentLevel != LEVEL_AQUAS) {
        xSway = 175.0f;
        if (Rand_ZeroOne() < 0.5f) {
            xSway = -175.0f;
        }
    } else {
        xSway = 350.0f;
        if (Rand_ZeroOne() < 0.5f) {
            xSway = -350.0f;
        }
    }

    x = gPlayer[0].pos.x + xSway - xPos;
    y = gPlayer[0].pos.y - yPos;
    z = gPlayer[0].trueZpos - zPos;

    yRot = Math_Atan2F(x, z);
    xRot = -Math_Atan2F(y, sqrtf(SQ(x) + SQ(z)));

    Matrix_RotateY(gCalcMatrix, yRot, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, xRot, MTXF_APPLY);

    src.x = src.y = 0.0f;
    src.z = srcZ;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

    dest.z -= gPathVelZ;

    for (i = 0; i < 6; i++) {
        for (j = 0; j < ARRAY_COUNT(gEffects); j++) {
            if (gEffects[j].obj.status == OBJ_FREE) {
                func_effect_80083C70(&gEffects[j], xPos, yPos, zPos, dest.x, dest.y, dest.z, i * 60.0f, i);
                if (i == 0) {
                    AUDIO_PLAY_SFX(NA_SE_EN_MARBLE_BEAM, gEffects[j].sfxSource, 4);
                }
                break;
            }
        }
    }
}

void func_effect_80083FA8(Effect* effect) {
    Vec3f src;
    Vec3f dest;

    if (effect->timer_50 == 0) {
        Object_Kill(&effect->obj, effect->sfxSource);
        return;
    }

    effect->obj.rot.y = RAD_TO_DEG(-gPlayer[0].camYaw);
    effect->obj.rot.x = RAD_TO_DEG(gPlayer[0].camPitch);
    effect->obj.rot.z += 20.0f;

    Matrix_RotateZ(gCalcMatrix, effect->unk_60.z * M_DTOR, MTXF_NEW);
    Matrix_RotateZ(gCalcMatrix, effect->unk_46 * M_DTOR, MTXF_APPLY);

    src.x = 0.0f;
    src.y = effect->scale1;
    src.z = 0.0f;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

    effect->unk_60.x += effect->vel.x;
    effect->unk_60.y += effect->vel.y;

    effect->obj.pos.x = effect->unk_60.x + dest.x;
    effect->obj.pos.y = effect->unk_60.y + dest.y;

    effect->unk_48 += 2;
    if (effect->unk_48 > 20) {
        effect->unk_48 = 20;
    }
    effect->unk_46 += effect->unk_48;

    Math_SmoothStepToF(&effect->scale1, 350.0f, 1.0f, 20.0f, 0.00001f);

    if ((effect->scale1 >= 349.0f) && (effect->timer_50 > 50)) {
        effect->timer_50 = 50;
    }
    func_effect_8007A774(gPlayer, effect, 100.0f);
}

// RGB Values. Used like an array of [8][3], but only matches this way.
static s32 D_800D18F0[] = { 32, 32, 255, 0, 255, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 255, 255, 0, 255, 0, 255, 0 };

// Alpha values
static s32 D_800D1950[] = { 255, 210, 180, 120, 70, 30, 0, 0 };

void func_effect_80084194(Effect* effect) {
    s32 tmp;

    if (gCurrentLevel != LEVEL_AQUAS) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_49);
        Matrix_Scale(gGfxMatrix, effect->scale2, effect->scale2, effect->scale2, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
        tmp = effect->unk_44 * 4;
        gDPSetEnvColor(gMasterDisp++, D_800D18F0[tmp + 0], D_800D18F0[tmp + 1], D_800D18F0[tmp + 2], 255);
    } else {
        RCP_SetupDL(&gMasterDisp, SETUPDL_49);
        Matrix_Scale(gGfxMatrix, effect->scale2, effect->scale2, effect->scale2, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, D_800D1950[effect->unk_44]);
        gDPSetEnvColor(gMasterDisp++, 255, 0, 0, 255);
    }
    gSPDisplayList(gMasterDisp++, D_1024AC0);
    RCP_SetupDL(&gMasterDisp, SETUPDL_64);
}
