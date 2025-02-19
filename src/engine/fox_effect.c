/*
 * File: fox_effect.c
 * System: Effect
 * Description: Effect Draw routines
 */

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
#include "port/interpolation/FrameInterpolation.h"
#include "port/mods/PortEnhancements.h"

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

    for (i = 0, bonus = &gBonusText[0]; i < ARRAY_COUNT(gBonusText); i++, bonus++) {
        if (bonus->hits != BONUS_TEXT_FREE) {
            if (bonus->timer != 0) {
                bonus->timer -= 1; // can't be --
            }
            if (bonus->timer == 0) {
                bonus->hits = BONUS_TEXT_FREE;
            }

            if (gLevelMode == LEVELMODE_ON_RAILS) {
                bonus->pos.z -= gPathVelZ;
            } else if (gPlayer[0].state == PLAYERSTATE_ACTIVE) {
                bonus->pos.x += gPlayer[0].vel.x;
                bonus->pos.z += gPlayer[0].vel.z;
            }

            if (bonus->timer < 45) {
                Math_SmoothStepToF(&bonus->rise, 300.0f, 0.1f, 20.0f, 0.0f);
            }
        }
    }
}

Gfx* sLargeBonusDLs[4][2] = {
    { D_1016410, D_1003130 },
    { D_10162A0, D_1003130 },
    { D_1016130, D_1003130 },
    { D_1015FC0, D_1003130 },
};

Gfx* sSmallBonusDLs[10] = {
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

    RCP_SetupDL(&gMasterDisp, SETUPDL_62_OPTIONAL);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    for (i = 0, bonus = gBonusText; i < ARRAY_COUNT(gBonusText); i++, bonus++) {
        if (bonus->hits != 0) {
            FrameInterpolation_RecordOpenChild(bonus, i);
            FrameInterpolation_RecordMarker(__FILE__, __LINE__);
            Matrix_Push(&gGfxMatrix);
            BonusText_Draw(bonus);
            Matrix_Pop(&gGfxMatrix);
            FrameInterpolation_RecordCloseChild();
        }
    }
}

Effect* Effect_Load(ObjectId objId) {
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

void Effect_FireSmoke_Setup2(EffectFireSmoke* this, f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel,
                             f32 scale2) {
    Effect_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_EFFECT_FIRE_SMOKE_1;

    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;

    this->vel.x = xVel;
    this->vel.y = yVel;
    this->vel.z = zVel;

    this->scale2 = scale2;
    this->unk_4C = 0;
    this->scale1 = 0.5f;
    this->obj.rot.z = RAND_FLOAT(360.0f);

    Object_SetInfo(&this->info, this->obj.id);

    this->unk_44 = 255;
}

void Effect_FireSmoke_Spawn2(f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 scale2) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Effect_FireSmoke_Setup2(&gEffects[i], xPos, yPos, zPos, xVel, yVel, zVel, scale2);
            break;
        }
    }
}

void Effect_Effect372_Draw(Effect372* this) {
    Graphics_SetScaleMtx(this->scale2);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, this->unk_44);
    gSPDisplayList(gMasterDisp++, D_arwing_3016B30);
}

void Effect_Effect382_Draw(Effect382* this) {
    RCP_SetupDL_49();
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, this->unk_44);
    gDPSetEnvColor(gMasterDisp++, 255, 255, 255, this->unk_44);
    Matrix_Scale(gGfxMatrix, this->scale1, this->scale2, 1.0f, MTXF_APPLY);
    Matrix_Translate(gGfxMatrix, 0.0f, 20.0f, 0.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_ZO_6024220);
    RCP_SetupDL(&gMasterDisp, SETUPDL_64);
}

void Effect_Effect388_Draw(Effect388* this) {
}

void Effect_Effect384_Draw(Effect384* this) {
    Graphics_SetScaleMtx(this->scale2);

    if ((this->scale1 == 71.0f) ||
        ((gPlayer[0].state == PLAYERSTATE_LEVEL_COMPLETE) && (gCurrentLevel == LEVEL_CORNERIA))) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_38);
    } else {
        RCP_SetupDL(&gMasterDisp, SETUPDL_67);
    }

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, this->unk_44);

    switch (this->unk_4C) {
        case 0:
            gDPSetEnvColor(gMasterDisp++, 0, 128, 255, this->unk_44);
            break;
        case 1:
            gDPSetEnvColor(gMasterDisp++, 255, 64, 255, this->unk_44);
            break;
        case 2:
            gDPSetEnvColor(gMasterDisp++, 255, 128, 0, this->unk_44);
            break;
        case 3:
            gDPSetEnvColor(gMasterDisp++, 255, 48, 48, this->unk_44);
            break;
        case 4:
            gDPSetEnvColor(gMasterDisp++, 255, 255, 48, this->unk_44);
            break;
        case 5:
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, this->unk_44);
            gDPSetEnvColor(gMasterDisp++, 255, 32, 32, this->unk_44);
            break;
        case 6:
            if (gCurrentLevel == LEVEL_BOLSE) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_38);
            }
            switch ((this->index + gGameFrameCount) % 4U) {
                case 0:
                    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 0, 0, this->unk_44);
                    break;
                case 1:
                    gDPSetPrimColor(gMasterDisp++, 0, 0, 0, 255, 0, this->unk_44);
                    break;
                case 2:
                    gDPSetPrimColor(gMasterDisp++, 0, 0, 0, 0, 255, this->unk_44);
                    break;
                case 3:
                    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, this->unk_44);
                    break;
            }
            gDPSetEnvColor(gMasterDisp++, 0, 0, 0, this->unk_44);
            break;
        case 7:
            gDPSetEnvColor(gMasterDisp++, 48, 48, 255, this->unk_44);
            break;
        case 10:
            gDPSetEnvColor(gMasterDisp++, 255, 255, 32, this->unk_44);
            break;
        case 11:
            gDPSetEnvColor(gMasterDisp++, 255, 32, 32, this->unk_44);
            break;
        case 12:
            gDPSetEnvColor(gMasterDisp++, 32, 255, 32, this->unk_44);
            break;
        case 13:
            gDPSetEnvColor(gMasterDisp++, 32, 32, 255, this->unk_44);
            break;
    }

    gSPDisplayList(gMasterDisp++, aOrbDL);
    RCP_SetupDL(&gMasterDisp, SETUPDL_64);
}

void Effect_Effect385_Draw(Effect385* this) {
    Graphics_SetScaleMtx(this->scale2);
    RCP_SetupDL_49();
    RCP_SetupDL(&gMasterDisp, SETUPDL_38);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 64, 192, 255, this->unk_44);
    gDPSetEnvColor(gMasterDisp++, 0, 0, 0, this->unk_44);
    gSPDisplayList(gMasterDisp++, aOrbDL);
    RCP_SetupDL(&gMasterDisp, SETUPDL_64);
}

// Possibly the little sparks of electricity that come off the arwing and landmaster when low on health
f32 D_800D1534[][10] = {
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

void Effect_Effect389_Draw(Effect389* this) {
    s32 i;

    if (this->unk_4A > 10) {
        if (((this->index + gGameFrameCount) % 2) == 0) {
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 128, 128, 32);
        } else {
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 128, 128, 128);
        }
    } else if (((this->index + gGameFrameCount) % 2) == 0) {
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
    } else {
        gDPSetPrimColor(gMasterDisp++, 0, 0, 96, 96, 255, 255);
    }

    Graphics_SetScaleMtx(this->scale2);

    for (i = 0; i < 10; i++) {
        if ((i >= this->unk_48) && (i < this->unk_46)) {
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, 0.0f, -60.0f, 0.0f, MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, 0.8f, 3.0f, 1.0f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_102F5E0);
            Matrix_Pop(&gGfxMatrix);
        }
        Matrix_Translate(gGfxMatrix, 0.0f, -120.0f, 0.0f, MTXF_APPLY);
        Matrix_RotateZ(gGfxMatrix, D_800D1534[this->unk_4C][i] * M_DTOR, MTXF_APPLY);
    }
}

void Effect_Effect347_Draw(Effect347* this) {
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, this->unk_44);
    Graphics_SetScaleMtx(this->scale2);
    gSPDisplayList(gMasterDisp++, D_BG_SPACE_2006F50);
}

void Effect_Effect351_Draw(Effect351* this) {
    Graphics_SetScaleMtx(this->scale2);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, this->unk_4A);
    gSPDisplayList(gMasterDisp++, aBallDL);
}

void Effect_Clouds_Draw(EffectClouds* this) {
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, this->unk_46);
    Graphics_SetScaleMtx(this->scale2);
    Matrix_RotateX(gGfxMatrix, M_PI / 2, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_BG_PLANET_200D750);
}

void Effect_Effect366_Draw(Effect366* this) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_67);
    Graphics_SetScaleMtx(this->scale2);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, this->unk_4A);
    gDPSetEnvColor(gMasterDisp++, 101, 138, 153, 255);
    gSPDisplayList(gMasterDisp++, D_blue_marine_3000660);
    RCP_SetupDL(&gMasterDisp, SETUPDL_64);
}

void Effect_Effect367_Draw(Effect367* this) {
    if (this->timer_50 == 0) {
        Graphics_SetScaleMtx(this->scale2);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, this->unk_44);
        gSPDisplayList(gMasterDisp++, D_BG_PLANET_20112C0);
    }
}

void Effect_Effect344_Draw(Effect344* this) {
    RCP_SetupDL_60(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
    Matrix_Scale(gGfxMatrix, this->scale2, this->scale2, this->scale2, MTXF_APPLY);
    if (this->unk_44 >= 2) {
        Matrix_RotateX(gGfxMatrix, M_PI / 2, MTXF_APPLY);
    }
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_1029780);
    RCP_SetupDL(&gMasterDisp, SETUPDL_64);
}

void Effect_Effect345_Draw(Effect345* this) {
    RCP_SetupDL_60(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
    Matrix_Scale(gGfxMatrix, this->scale2 * 0.6f, 1.0f, this->scale2 * 3.5f, MTXF_APPLY);
    Matrix_RotateX(gGfxMatrix, M_PI / 2, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_1029780);
    RCP_SetupDL(&gMasterDisp, SETUPDL_64);
}

s32 D_800D173C[] = { 255, 255, 255, 0, 0, 0, 255, 0, 255, 0, 0, 0, 255, 255, 0, 0, 0, 255, 0, 0 };

void Effect_Effect346_Draw(Effect346* this) {
    s32 temp_ft3;
    s32 tmp;

    switch (gCurrentLevel) {
        case LEVEL_METEO:
            Graphics_SetScaleMtx(this->scale2);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 128, 128, 128, 255);
            gSPDisplayList(gMasterDisp++, D_ME_601FF80);
            break;

        case LEVEL_AQUAS:
            RCP_SetupDL(&gMasterDisp, SETUPDL_67);
            temp_ft3 = Math_ModF(this->index, 4.0f);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, (s32) this->scale1);
            tmp = temp_ft3 * 4.0f;
            gDPSetEnvColor(gMasterDisp++, D_800D173C[tmp + 0], D_800D173C[tmp + 1], D_800D173C[tmp + 2], 255);
            Graphics_SetScaleMtx(this->scale2);
            gSPDisplayList(gMasterDisp++, aOrbDL);
            RCP_SetupDL(&gMasterDisp, SETUPDL_64);
            break;
    }
}

void Effect_Effect348_Draw(Effect348* this) {
    Graphics_SetScaleMtx(this->scale2);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, this->unk_44);
    gSPDisplayList(gMasterDisp++, D_BG_PLANET_20112C0);
}

void func_effect_80078AE0(Effect* this) {
    /* Unimplemented */
}

void Effect_Effect355_Draw(Effect355* this) {
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 180);
    Graphics_SetScaleMtx(this->scale2 * (13.0f + ((s32) (gGameFrameCount % 2U) * 2.5f)));
    gSPDisplayList(gMasterDisp++, aBlueSphereDL);
}

void Effect_Effect353_Draw(Effect353* this) {
    RCP_SetupDL_21();
    gSPDisplayList(gMasterDisp++, D_101ABD0);
    RCP_SetupDL(&gMasterDisp, SETUPDL_64);
}

void Effect_Effect377_Draw(Effect377* this) {
    f32 scale;

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 160);

    scale = 3.0f;
    if ((gGameFrameCount % 2) != 0) {
        scale *= 1.2f;
    }

    Graphics_SetScaleMtx(this->scale2 * scale);
    gSPDisplayList(gMasterDisp++, D_SX_600F8A0);
}

void Effect_Effect356_Draw(Effect356* this) {
    Graphics_SetScaleMtx(this->scale2);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 192);
    gSPDisplayList(gMasterDisp++, D_ME_6000A80);
}

void Effect_Effect376_Draw(Effect376* this) {
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, this->unk_4A);
    Graphics_SetScaleMtx(this->scale2);
    gSPDisplayList(gMasterDisp++, D_CO_6033000);
}

void Effect_Effect393_Setup(Effect393* this, f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    Effect_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_EFFECT_393;
    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;
    this->scale2 = scale2;

    if (scale2 == 3.1f) {
        this->vel.x = gActors[8].vel.x;
        this->vel.y = gActors[8].vel.y;
        this->vel.z = gActors[8].vel.z;
    }
    if (scale2 != 30.0f) {
        this->state = 1;
    }
    if (scale2 == 3.5f) {
        this->state = 2;
    }

    this->timer_50 = 14;
    Object_SetInfo(&this->info, this->obj.id);
}

void Effect_Effect393_Spawn(f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Effect_Effect393_Setup(&gEffects[i], xPos, yPos, zPos, scale2);
            break;
        }
    }
}

void Effect_Effect393_Update(Effect393* this) {
    if (this->state == 2) {
        this->vel.x = gPlayer[0].vel.x;
        this->vel.y = gPlayer[0].vel.y;
        this->vel.z = gPlayer[0].vel.z;
    }

    this->obj.rot.z += 35.0f;

    if (this->timer_50 >= 7) {
        this->scale1 += 0.25f;
    } else {
        this->scale1 -= 0.25f;
    }
    if (this->scale1 <= 0.0f) {
        Object_Kill(&this->obj, this->sfxSource);
    }
}

void Effect_Effect393_Draw(Effect393* this) {
    if (this->state != 0) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_67);
    } else {
        RCP_SetupDL(&gMasterDisp, SETUPDL_63);
    }

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
    gDPSetEnvColor(gMasterDisp++, 255, 255, 0, 255);
    Graphics_SetScaleMtx(this->scale2 * this->scale1);
    gSPDisplayList(gMasterDisp++, aStarDL);
    RCP_SetupDL(&gMasterDisp, SETUPDL_64);
}

void Effect_Effect357_Setup(Effect357* this, f32 xPos, f32 yPos, f32 zPos, f32 scale2, u8 arg5) {
    Vec3f sp54;
    Vec3f sp48;
    Vec3f sp3C;
    f32 sp38;
    f32 xAng;
    f32 yAng;

    Effect_Initialize(this);
    this->obj.status = OBJ_ACTIVE;
    this->obj.id = OBJ_EFFECT_357;

    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;

    this->unk_4C = arg5;

    if (scale2 == 1.6f) {
        this->vel.x = (xPos - gBosses[1].obj.pos.x) * 0.1f;
        this->vel.z = (zPos - gBosses[1].obj.pos.z) * 0.1f;
    } else if (scale2 == 1.3f) {
        this->vel.x = (RAND_FLOAT(0.05f) + 0.03f) * xPos;
        this->vel.z = (RAND_FLOAT(0.05f) + 0.03f) * zPos;
        this->vel.y = 5.0f;
    } else if (scale2 == 1.55f) {
        this->vel.x = RAND_FLOAT_CENTERED(10.0f);
        this->vel.z = RAND_FLOAT_CENTERED(10.0f);
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
        this->vel.x = sp48.x;
        this->vel.y = sp48.y;
        this->vel.z = sp48.z;
    } else {
        this->vel.y = (gLevelType == LEVELTYPE_PLANET) ? RAND_FLOAT(7.0f) + 7.0f : RAND_FLOAT_CENTERED(10.0f);
        this->vel.x = RAND_FLOAT_CENTERED(10.0f);
        this->vel.z = RAND_FLOAT_CENTERED(10.0f);
    }
    this->scale2 = (RAND_FLOAT(0.8f) + 0.3f) * scale2;
    this->timer_50 = RAND_INT(50.0f) + 70;
    this->obj.rot.x = RAND_FLOAT(360.0f);
    this->unk_60.x = RAND_FLOAT_CENTERED(30.0f);
    this->unk_60.y = RAND_FLOAT_CENTERED(30.0f);
    this->unk_60.z = RAND_FLOAT_CENTERED(30.0f);
    Object_SetInfo(&this->info, this->obj.id);
}

void Effect_Effect357_Spawn50(f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    s32 i;

    for (i = 50; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Effect_Effect357_Setup(&gEffects[i], xPos, yPos, zPos, scale2, 0);
            break;
        }
    }
}

// Broken pieces and debris effect
void Effect_Effect357_Spawn80(f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    s32 i;

    for (i = (ARRAY_COUNT(gEffects) - 20) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Effect_Effect357_Setup(&gEffects[i], xPos, yPos, zPos, scale2, 0);
            break;
        }
    }
}

void Effect_Effect357_Spawn95(f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    s32 i;

    for (i = 0; i < 95; i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Effect_Effect357_Setup(&gEffects[i], xPos, yPos, zPos, scale2, 0);
            break;
        }
    }
}

void func_effect_80079618(f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    s32 i;

    for (i = 50; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Effect_Effect357_Setup(&gEffects[i], xPos, yPos, zPos, scale2, 1);
            break;
        }
    }
}

void Effect_Effect357_Update(Effect357* this) {
    if ((gCurrentLevel != LEVEL_MACBETH) || (this->unk_44 != 7)) {
        if ((this->timer_50 == 0) || (this->obj.pos.y < gGroundHeight)) {
            Object_Kill(&this->obj, this->sfxSource);
        }
    } else {
        if (((gGameFrameCount % 4) == 0)) {
            func_effect_8007D2C8(this->obj.pos.x, this->obj.pos.y + 550.0f, this->obj.pos.z, 10.0f);
        }
        if ((this->timer_50 == 0) || (this->obj.pos.y < (gGroundHeight - 100.0f))) {
            Object_Kill(&this->obj, this->sfxSource);
        }
    }

    this->obj.rot.x += this->unk_60.x;
    this->obj.rot.y += this->unk_60.y;
    this->obj.rot.z += this->unk_60.z;

    if (gLevelType == LEVELTYPE_PLANET) {
        this->vel.y -= 0.5f;
    }

    if ((gCurrentLevel == LEVEL_BOLSE) && (gPlayer[0].state == PLAYERSTATE_LEVEL_COMPLETE) && (gCsFrameCount > 175)) {
        this->vel.x *= 0.95f;
        this->vel.y *= 0.95f;
        this->vel.z *= 0.95f;
    }

    if ((gCurrentLevel == LEVEL_MACBETH) && (this->unk_44 == 10)) {
        this->obj.rot.x = 0.0f;
        this->obj.rot.y = 0.0f;
        if (this->timer_50 >= 25) {
            this->scale1 = 0.5f;
        } else if (this->scale1 > 0.03) {
            this->scale1 -= 0.02f;
        }
    }
}

bool func_effect_800798C4(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* data) {
    if ((limbIndex != 1) && (limbIndex != 5)) {
        *dList = NULL;
    }
    return false;
}

void Effect_Effect357_Draw(Effect357* this) {
    Vec3f frameJointTable[50];

    if ((gCurrentLevel == LEVEL_BOLSE) && (gPlayer[0].state == PLAYERSTATE_LEVEL_COMPLETE)) {
        Display_SetSecondLight(&this->obj.pos);
    }

    RCP_SetupDL(&gMasterDisp, SETUPDL_29);

    if (gCurrentLevel == LEVEL_KATINA) {
        gSPFogPosition(gMasterDisp++, gFogNear, 1005);
    }

    Graphics_SetScaleMtx(this->scale2);

    switch (gCurrentLevel) {
        case LEVEL_MACBETH:
            switch (this->unk_44) {
                case 1:
                    if ((this->index % 2) != 0) {
                        gSPDisplayList(gMasterDisp++, D_MA_6022530);
                    } else {
                        gSPDisplayList(gMasterDisp++, D_MA_6022450);
                    }
                    break;

                case 2:
                    RCP_SetupDL(&gMasterDisp, SETUPDL_57);
                    if ((this->index % 2) != 0) {
                        gSPDisplayList(gMasterDisp++, D_MA_601A7A0);
                    } else {
                        gSPDisplayList(gMasterDisp++, D_MA_60223C0);
                    }
                    RCP_SetupDL(&gMasterDisp, SETUPDL_29);
                    break;

                case 7:
                    Animation_GetFrameData(&D_MA_6027320, 0, frameJointTable);
                    Animation_DrawSkeleton(1, D_MA_602742C, frameJointTable, func_effect_800798C4, NULL, this,
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
                    Graphics_SetScaleMtx(this->scale1);
                    gSPDisplayList(gMasterDisp++, aOrbDL);
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
                    gSPDisplayList(gMasterDisp++, D_MA_600F6C0);
                    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
                    break;

                case 17:
                    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                    gSPDisplayList(gMasterDisp++, D_MA_600F9B0);
                    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
                    break;

                default:
                    if ((this->index % 2) != 0) {
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
            switch (this->unk_4C) {
                case 0:
                    if ((this->index % 2) != 0) {
                        gSPDisplayList(gMasterDisp++, D_10194C0);
                    } else {
                        gSPDisplayList(gMasterDisp++, D_1024290);
                    }
                    break;

                case 1:
                    switch ((s32) (this->index % 4U)) {
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

void Effect_Effect383_Update(Effect383* this) {
    Lib_Texture_Scroll(D_10190C0, 16, 32, 0);
    gGroundClipMode = 2;
    this->obj.rot.y += 1.0f;
    Math_SmoothStepToF(&this->scale2, this->scale1, 0.05f, 1.5f, 0.001f);

    if (this->timer_50 > 10) {
        D_ctx_801779A8[0] = 60.0f;
    }
    if (this->timer_50 == 48) {
        gFillScreenAlpha = 150;
    }
    if (this->timer_50 > 45) {
        gFillScreenAlphaTarget = 0;
        gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
    }

    gFillScreenAlphaStep = 3;

    if (this->timer_50 == 0) {
        this->unk_44 -= 2;
        if (this->unk_44 < 0) {
            this->unk_44 = 0;
            Object_Kill(&this->obj, this->sfxSource);
            gGroundClipMode = 0;
        }
    }
}

void Effect_Effect383_Draw(Effect383* this) {
    if (gReflectY > 0) {
        Matrix_Scale(gGfxMatrix, this->scale2, this->scale2, this->scale2, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        RCP_SetupDL_64_2();
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, this->unk_44);
        gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
        gSPDisplayList(gMasterDisp++, D_10182C0);
        gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
        RCP_SetupDL_64_2();
    }
}

void Effect_Effect383_Setup(Effect383* this, f32 xPos, f32 yPos, f32 zPos, f32 scale1) {
    Effect_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_EFFECT_383;
    this->scale1 = scale1;
    this->timer_50 = 50;
    this->unk_44 = 200;

    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;

    AUDIO_PLAY_SFX(NA_SE_EN_STAR_EXPLOSION, this->sfxSource, 4);
    Object_SetInfo(&this->info, this->obj.id);
}

void Effect_Effect383_Spawn(f32 xPos, f32 yPos, f32 zPos, f32 scale1) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Effect_Effect383_Setup(&gEffects[i], xPos, yPos, zPos, scale1);
            break;
        }
    }
    Effect_Effect384_Spawn(xPos, yPos, zPos, 80.0f, 4);
}

void Effect_SetupTimedSfxAtPos(TimedSfx* this, Vec3f* pos, u32 sfxId) {
    Effect_Initialize(this);
    this->obj.status = OBJ_ACTIVE;
    this->obj.id = OBJ_EFFECT_TIMED_SFX;

    this->obj.pos.x = pos->x;
    this->obj.pos.y = pos->y;
    this->obj.pos.z = pos->z;

    this->timer_50 = 50;

    if ((sfxId == NA_SE_OB_EXPLOSION_S) || (sfxId == NA_SE_OB_SMOKE)) {
        AUDIO_PLAY_SFX(sfxId, this->sfxSource, 0);
        if (sfxId == NA_SE_OB_SMOKE) {
            this->timer_50 = 300;
        }
    } else {
        AUDIO_PLAY_SFX(sfxId, this->sfxSource, 4);
    }

    Object_SetInfo(&this->info, this->obj.id);
}

void Effect_SpawnTimedSfxAtPos(Vec3f* pos, s32 sfxId) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Effect_SetupTimedSfxAtPos(&gEffects[i], pos, sfxId);
            break;
        }
    }
}

void Effect_TimedSfx_Update(TimedSfx* this) {
    if (this->timer_50 == 0) {
        Object_Kill(&this->obj, this->sfxSource);
    }
}

bool func_effect_8007A774(Player* player, Effect* this, f32 arg2) {
    if ((fabsf(player->trueZpos - this->obj.pos.z) < arg2) && (fabsf(player->pos.x - this->obj.pos.x) < arg2) &&
        (fabsf(player->pos.y - this->obj.pos.y) < arg2) && (player->mercyTimer == 0)) {
        Player_ApplyDamage(player, 0, this->info.damage);
        return true;
    } else {
        return false;
    }
}

void Effect_Effect359_Setup(Effect359* this, f32 xPos, f32 yPos, f32 zPos, f32 scale1, u8 arg5, u8 arg6, u16 arg7) {
    Effect_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_EFFECT_359;

    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;

    this->scale1 = scale1;
    this->unk_44 = arg5;
    this->unk_46 = arg6;
    this->unk_60.z = RAND_FLOAT_CENTERED(10.0f);
    this->unk_60.y = scale1 * 0.1f;
    if (arg7 != 0) {
        this->vel.x = RAND_FLOAT_CENTERED(30.0f);
    }
    Object_SetInfo(&this->info, this->obj.id);
}

void Effect_Effect359_Spawn(f32 xPos, f32 yPos, f32 zPos, f32 scale1, u8 arg4, u8 arg5, u16 arg6) {
    s32 i;

    if (gCurrentLevel == LEVEL_TITANIA) {
        for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
            if (gEffects[i].obj.status == OBJ_FREE) {
                Effect_Effect359_Setup(&gEffects[i], xPos, yPos, zPos, scale1, arg4, arg5, arg6);
                break;
            }
        }
    }
}

void Effect_Effect359_Update(Effect359* this) {
    Math_SmoothStepToF(&this->scale2, this->scale1, 0.1f, 10.0f, 0.01f);
    this->obj.rot.z += this->unk_60.z;
    this->vel.y += this->unk_60.y;

    if ((this->unk_4A % 2) != 0) {
        this->unk_48++;
        if (this->unk_48 > 5) {
            this->unk_48 = 5;
        }
    }

    this->unk_44 -= this->unk_46;
    if (this->unk_44 <= 20) {
        Object_Kill(&this->obj, this->sfxSource);
    }
    this->unk_4A++;
}

Gfx* D_800D178C[] = { D_TI_6003440, D_TI_60034E0, D_TI_6003580, D_TI_6003620, D_TI_60036C0, D_TI_6003760 };

void Effect_Effect359_Draw(Effect359* this) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_68);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 31, 10, 00, this->unk_44);
    gDPSetEnvColor(gMasterDisp++, 141, 73, 5, 0);
    Matrix_Scale(gGfxMatrix, this->scale2, this->scale2, 1.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_800D178C[this->unk_4C]);
    this->unk_4C = this->unk_48;
    RCP_SetupDL(&gMasterDisp, SETUPDL_64);
}

void Effect_Effect372_Update(Effect372* this) {
    if (this->state == 0) {
        Math_SmoothStepToF(&this->scale2, this->scale1, 0.1f, 10.0f, 0.0f);
        this->unk_44 -= 20;
        if (this->unk_44 < 0) {
            Object_Kill(&this->obj, this->sfxSource);
        }
    } else {
        Math_SmoothStepToF(&this->scale2, this->scale1, 0.1f, 10.0f, 0.0f);
        this->unk_44 -= 10;
        if (this->unk_44 < 0) {
            Object_Kill(&this->obj, this->sfxSource);
        }
    }
}

void Effect_Effect372_Setup1(Effect372* this, f32 xPos, f32 unused_posY, f32 zPos, f32 scale2, f32 scale1, f32 yRot) {
    Effect_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_EFFECT_372;

    this->obj.pos.x = xPos;
    this->obj.pos.y = gGroundHeight;
    this->obj.pos.z = zPos;

    this->unk_44 = 180;
    this->scale2 = scale2;
    this->scale1 = scale1;
    this->obj.rot.y = yRot;
    this->vel.x = gPlayer[0].vel.x * 0.6f;
    this->vel.z = gPlayer[0].vel.z * 0.6; // Forgotten f means bad codegen
    Object_SetInfo(&this->info, this->obj.id);
}

void Effect_Effect372_Spawn1(f32 xPos, f32 yPos, f32 zPos, f32 scale2, f32 scale1, f32 yRot) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Effect_Effect372_Setup1(&gEffects[i], xPos, yPos, zPos, scale2, scale1, yRot);
            break;
        }
    }
}

void Effect_Effect372_Setup2(Effect372* this, f32 xPos, f32 unused_posY, f32 zPos, f32 scale2, f32 scale1, f32 yRot) {
    Effect_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_EFFECT_372;
    this->state = 1;

    this->obj.pos.x = xPos;
    this->obj.pos.y = gGroundHeight;
    this->obj.pos.z = zPos;

    this->unk_44 = 180;
    this->scale2 = scale2;
    this->scale1 = scale1;
    this->obj.rot.y = yRot;
    Object_SetInfo(&this->info, this->obj.id);
}

void Effect_Effect372_Spawn2(f32 xPos, f32 yPos, f32 zPos, f32 scale2, f32 scale1) {
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
                Effect_Effect372_Setup2(&gEffects[j], xPos + sinf, yPos, zPos + cosf, scale2, scale1, yRot);
                break;
            }
        }
    }
}

void Effect_Effect382_Setup(Effect382* this, f32 xPos, f32 zPos, f32 xVel, f32 zVel, f32 scale1) {
    Effect_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_EFFECT_382;

    this->obj.pos.x = xPos;
    this->obj.pos.y = -10.0f;
    this->obj.pos.z = zPos;

    this->vel.x = xVel;
    this->vel.z = zVel - gPathVelZ;
    this->scale1 = scale1;
    this->timer_50 = 100;
    Object_SetInfo(&this->info, this->obj.id);
}

void Effect_Effect382_Spawn(f32 xPos, f32 zPos, f32 xVel, f32 zVel, f32 scale1) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Effect_Effect382_Setup(&gEffects[i], xPos, zPos, xVel, zVel, scale1);
            break;
        }
    }
}

void Effect_Effect382_Update(Effect382* this) {
    f32 sp2C;
    s32 sp28;

    if (Play_CheckDynaFloorCollision(&sp2C, &sp28, this->obj.pos.x, this->obj.pos.y, this->obj.pos.z)) {
        D_ctx_801782EC[sp28] = this->scale1;
        D_ctx_801782EC[sp28 + 1] = this->scale1 * 0.7f;
        D_ctx_801782EC[sp28 - 1] = this->scale1 * 0.7f;
    }
    if (this->timer_50 == 0) {
        Object_Kill(&this->obj, this->sfxSource);
    }
}

void Effect_Effect381_Update(Effect381* this) {
    Math_SmoothStepToF(&this->scale2, this->scale1 * 3.0f, 0.1f, 10.0f, 0.0f);
    this->unk_44 -= 13;
    this->obj.rot.y = 180.0f - this->obj.rot.y;
    if (this->unk_44 < 0) {
        Object_Kill(&this->obj, this->sfxSource);
    }
}

void Effect_Effect381_Setup(Effect381* this, f32 xPos, f32 yPos, f32 zPos, f32 scale1) {
    Effect_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_EFFECT_381;

    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;

    this->unk_44 = 255;
    this->scale1 = scale1;
    Object_SetInfo(&this->info, this->obj.id);
    AUDIO_PLAY_SFX(NA_SE_SPLASH_LEVEL_L, this->sfxSource, 0);
}

void Effect_Effect381_Spawn(f32 xPos, f32 yPos, f32 zPos, f32 scale1) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffects) && gCurrentLevel == LEVEL_ZONESS; i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Effect_Effect381_Setup(&gEffects[i], xPos, yPos, zPos, scale1);
            break;
        }
    }
}

void Effect_Effect384_Setup(Effect384* this, f32 xPos, f32 yPos, f32 zPos, f32 scale1, s32 arg5) {
    Effect_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_EFFECT_384;

    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;

    this->scale1 = scale1;
    this->unk_44 = 255;
    this->unk_4C = arg5;

    Object_SetInfo(&this->info, this->obj.id);
}

// Orange-yellowish light simulating an explosion
void Effect_Effect384_Spawn(f32 xPos, f32 yPos, f32 zPos, f32 scale1, s32 arg4) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Effect_Effect384_Setup(&gEffects[i], xPos, yPos, zPos, scale1, arg4);
            break;
        }
    }
}

void Effect_Effect384_Update(Effect384* this) {
    f32 var_fv0;
    f32 var_fv1;
    s32 var_v0;

    if (this->unk_4C == 6) {
        var_fv0 = 15.0f;
        var_fv1 = 0.05f;
        var_v0 = 4;
    } else if ((this->unk_4C == 5) && ((gCurrentLevel == LEVEL_KATINA) || (gCurrentLevel == LEVEL_METEO))) {
        var_fv0 = 10.0f;
        var_fv1 = 0.1f;
        var_v0 = 4;
    } else {
        var_fv0 = 10.0f;
        var_fv1 = 0.1f;
        var_v0 = 8;
    }

    Math_SmoothStepToF(&this->scale2, this->scale1, var_fv1, var_fv0, 0.0f);

    this->unk_44 -= var_v0;
    if (this->unk_44 < 0) {
        Object_Kill(&this->obj, this->sfxSource);
    }
}

void Effect_Effect385_Setup(Effect385* this, f32 xPos, f32 yPos, f32 zPos, f32 scale1, s32 arg5) {
    Effect_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_EFFECT_385;

    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;

    this->obj.rot.x = 90.0f;
    this->scale1 = scale1;
    this->unk_44 = arg5;

    if (arg5 < 60) {
        this->unk_46 = 1;
    } else if (arg5 < 90) {
        this->unk_46 = 2;
    } else {
        this->unk_46 = 3;
    }

    Object_SetInfo(&this->info, this->obj.id);
}

void Effect_Effect385_Spawn(f32 xPos, f32 yPos, f32 zPos, f32 scale1, s32 arg4) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Effect_Effect385_Setup(&gEffects[i], xPos, yPos, zPos, scale1, arg4);
            break;
        }
    }
}

void Effect_Effect385_Update(Effect385* this) {
    Math_SmoothStepToF(&this->scale2, this->scale1, 0.1f, 10.0f, 0.1f);
    this->unk_44 -= this->unk_46;
    if (this->unk_44 < 0) {
        Object_Kill(&this->obj, this->sfxSource);
    }
}

void Effect_Clouds_Update(EffectClouds* this) {
    if (this->timer_50 == 0) {
        this->unk_46 -= 4;
        if (this->unk_46 <= 0) {
            Object_Kill(&this->obj, this->sfxSource);
        }
    }
}

void Effect_Effect388_Update(Effect388* this) {
}

void Effect_Effect389_Update(Effect389* this) {
    s32 var_v1;

    this->unk_46 += 2;

    if (this->unk_46 >= 10) {
        this->unk_46 = 10;
    }

    if (this->unk_46 >= 9) {
        this->unk_48++;
        if (this->unk_48 >= 10) {
            Object_Kill(&this->obj, this->sfxSource);
        }
    }

    var_v1 = this->unk_4A;
    if (var_v1 != 0) {
        if (var_v1 > 10) {
            var_v1 -= 10;
        }
        this->vel.x = gPlayer[var_v1 - 1].vel.x;
        this->vel.y = gPlayer[var_v1 - 1].vel.y;
        this->vel.z = gPlayer[var_v1 - 1].vel.z;
    }
}

void Effect_Effect347_Update(Effect347* this) {
    Math_SmoothStepToF(&this->scale2, this->scale1, 0.1f, 10.0f, 0.1f);
    this->unk_44 -= 2;
    if (this->unk_44 < 0) {
        Object_Kill(&this->obj, this->sfxSource);
    }
    func_effect_8007A774(gPlayer, this, this->scale2 * 20.0f);
}

void Effect_Effect364_Setup(Effect364* this, f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    Effect_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_EFFECT_364;

    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;

    this->vel.x = RAND_FLOAT_CENTERED(5.0f);
    this->vel.y = RAND_FLOAT_CENTERED(3.0f);
    this->unk_48 = 3;

    if (Rand_ZeroOne() < 0.5f) {
        this->unk_48 = -this->unk_48;
    }
    this->unk_4A = 50;
    this->unk_46 = 1;
    this->scale2 = scale2 * 0.2f;
    this->obj.rot.z = RAND_FLOAT(360.0f);
    Object_SetInfo(&this->info, this->obj.id);
}

void Effect_Effect364_Spawn(f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    s32 i, j;

    for (i = ARRAY_COUNT(gEffects) - 1, j = 0; j < ARRAY_COUNT(gEffects); i--, j++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Effect_Effect364_Setup(&gEffects[i], xPos, yPos, zPos, scale2);
            break;
        }
    }
}

void Effect_Effect364_Update(Effect364* this) {
    this->scale2 += 0.07f;

    this->unk_4A -= this->unk_46;
    if (this->unk_4A < 0) {
        Object_Kill(&this->obj, this->sfxSource);
    }
    this->obj.rot.z += this->unk_48;
    this->vel.y += 0.2f;
}

void Effect_Effect364_Draw(Effect364* this) {
    //! DEBUG: Hold Z on controller 4 to set up a display list.
    if (gControllerHold[3].button & Z_TRIG) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_4);
    }

    Graphics_SetScaleMtx(this->scale2);

    if (gCurrentLevel != LEVEL_MACBETH) {
        gDPSetPrimColor(gMasterDisp++, 0, 0, 140, 99, 58, this->unk_4A);
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

void Effect_Effect362_Setup(Effect362* this, f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    Effect_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_EFFECT_362;

    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;

    this->vel.x = RAND_FLOAT_CENTERED(5.0f);
    this->vel.y = RAND_FLOAT_CENTERED(3.0f);
    this->unk_48 = 3;

    if (Rand_ZeroOne() < 0.5f) {
        this->unk_48 = -this->unk_48;
    }

    this->unk_4A = 180;
    this->unk_46 = 8;

    if (scale2 > 15.0f) {
        this->unk_46 = 5;
        this->unk_4A = 80;
    }

    this->scale2 = scale2 * 0.25f;
    this->obj.rot.z = RAND_FLOAT(360.0f);

    if (scale2 == 6.0f) {
        this->vel.z = gPlayer[0].vel.z * 0.6f;
    }
    Object_SetInfo(&this->info, this->obj.id);
}

void Effect_Effect362_Spawn(f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 20; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Effect_Effect362_Setup(&gEffects[i], xPos, yPos, zPos, scale2);
            break;
        }
    }
}

void Effect_Effect362_Update(Effect362* this) {
    if (gPlayer[0].state == PLAYERSTATE_LEVEL_COMPLETE) {
        this->obj.rot.x = RAD_TO_DEG(gPlayer[0].camPitch);
        this->obj.rot.y = RAD_TO_DEG(-gPlayer[0].camYaw);
    }
    if (gPlayer[0].state == PLAYERSTATE_NEXT) {
        this->unk_46 = 2;
        this->vel.y -= 0.13f;
    }

    this->scale2 += 0.07f;
    this->unk_4A -= this->unk_46;

    if (this->unk_4A < 0) {
        Object_Kill(&this->obj, this->sfxSource);
    }
    this->obj.rot.z += this->unk_48;
    this->vel.y += 0.2f;
}

void Effect_Effect361_Update(Effect361* this) {
    this->scale2 += 0.04f;

    this->unk_4A -= 2;
    if (this->unk_4A < 0) {
        Object_Kill(&this->obj, this->sfxSource);
    }
    this->obj.rot.z += this->unk_48;
    this->vel.y += this->scale1;
}

void Effect_Effect360_Update(Effect360* this) {
    this->scale2 += 0.02f;
    this->unk_4A -= 3;
    if (this->unk_4A < 0) {
        Object_Kill(&this->obj, this->sfxSource);
    }
    this->vel.z = gPlayer[0].vel.z + 7.0f;
    this->obj.rot.z += this->unk_48;
    this->vel.y += 0.1f;
}

void Effect_Effect360_361_362_Draw(Effect* this) {
    Graphics_SetScaleMtx(this->scale2);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, this->unk_4A);
    gSPDisplayList(gMasterDisp++, D_BG_PLANET_2010A30);
}

void Effect_Effect386_Setup(Effect386* this, f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 scale2,
                            s32 timer50) {
    Effect_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_EFFECT_386;

    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;

    this->vel.x = xVel;
    this->vel.y = yVel;
    this->vel.z = zVel;
    this->scale2 = scale2;
    this->timer_50 = timer50;
    Object_SetInfo(&this->info, this->obj.id);
}

void Effect386_Spawn1(f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 scale2, s32 timer50) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Effect_Effect386_Setup(&gEffects[i], xPos, yPos, zPos, xVel, yVel, zVel, scale2, timer50);
            break;
        }
    }
}

void Effect_Effect390_Setup(Effect390* this, f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 scale2,
                            s32 timer50) {
    Effect_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_EFFECT_390;

    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;

    this->vel.x = xVel;
    this->vel.y = yVel;
    this->vel.z = zVel;
    this->scale2 = scale2;
    this->timer_50 = timer50;
    Object_SetInfo(&this->info, this->obj.id);
}

void Effect_Effect390_Spawn(f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 scale2, s32 timer50) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Effect_Effect390_Setup(&gEffects[i], xPos, yPos, zPos, xVel, yVel, zVel, scale2, timer50);
            break;
        }
    }
}

void Effect386_Spawn2(f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 scale2, s32 timer50) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Effect_Effect386_Setup(&gEffects[i], xPos, yPos, zPos, xVel, yVel, zVel, scale2, timer50);
            Play_PlaySfxNoPlayer(gEffects[i].sfxSource, NA_SE_EXPLOSION_S);
            break;
        }
    }
}

void Effect_Effect386_Update(Effect386* this) {
    f32 randX;
    f32 randY;
    f32 randOther;
    s32 mask;

    Math_SmoothStepToF(&this->vel.x, 0.0f, 0.2f, 10.0f, 0.1f);
    Math_SmoothStepToF(&this->vel.y, 0.0f, 0.2f, 10.0f, 0.1f);
    Math_SmoothStepToF(&this->vel.z, 0.0f, 0.2f, 10.0f, 0.1f);

    mask = 4 - 1;
    if (gLevelMode == LEVELMODE_ALL_RANGE) {
        mask = 2 - 1;
    }

    if ((this->timer_50 & mask) == 0) {
        randX = RAND_FLOAT_CENTERED(40.0f);
        randY = RAND_FLOAT_CENTERED(40.0f);
        randOther = RAND_FLOAT(0.5f) + 1.0f;
        func_effect_8007D0E0(this->obj.pos.x + randX, this->obj.pos.y + randY, this->obj.pos.z,
                             this->scale2 * randOther);
        if (this->timer_50 == 0) {
            Object_Kill(&this->obj, this->sfxSource);
        }
    }
}

void Effect_Effect389_Setup(Effect389* this, f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 scale2,
                            s32 arg8) {
    Effect_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_EFFECT_389;

    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;

    this->vel.x = xVel;
    this->vel.y = yVel;
    this->vel.z = zVel;

    this->scale2 = scale2;
    this->unk_4A = arg8;
    this->unk_4C = RAND_INT(12.0f);
    this->obj.rot.z = RAND_FLOAT(360.0f);

    Object_SetInfo(&this->info, this->obj.id);

    this->unk_44 = 255;
}

void Effect_Effect389_Spawn(f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 scale2, s32 arg7) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i > 32; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Effect_Effect389_Setup(&gEffects[i], xPos, yPos, zPos, xVel, yVel, zVel, scale2, arg7);
            break;
        }
    }
}

void Effect_Effect390_Update(Effect390* this) {
    f32 randX;
    f32 randY;
    f32 randOther;

    if ((this->timer_50 % 8) == 0) {
        randX = RAND_FLOAT_CENTERED(40.0f) * this->scale2;
        randY = RAND_FLOAT_CENTERED(40.0f) * this->scale2;
        randOther = RAND_FLOAT(1.0f) + 1.0f;
        Effect_Effect389_Spawn(this->obj.pos.x + randX, this->obj.pos.y + randY, this->obj.pos.z, this->vel.x,
                               this->vel.y, this->vel.z, this->scale2 * randOther, 0);
        if (this->timer_50 == 0) {
            Object_Kill(&this->obj, this->sfxSource);
        }
    }
}

void Effect_Effect387_Setup(Effect387* this, f32 xPos, f32 yPos, f32 zPos, f32 scale2, s32 timer50) {
    Effect_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_EFFECT_387;

    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;

    this->scale2 = scale2;
    this->timer_50 = timer50;
    Object_SetInfo(&this->info, this->obj.id);
}

void Effect_Effect387_Spawn(f32 xPos, f32 yPos, f32 zPos, f32 scale2, s32 timer50) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Effect_Effect387_Setup(&gEffects[i], xPos, yPos, zPos, scale2, timer50);
            break;
        }
    }
}

void Effect_Effect343_Setup(Effect343* this, f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    Effect_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_EFFECT_SMOKE_2;

    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;

    this->unk_48 = 3;
    this->vel.y = 5.0f;

    if (Rand_ZeroOne() < 0.5f) {
        this->unk_48 = -this->unk_48;
    }

    if ((gCurrentLevel == LEVEL_FORTUNA) && (gPlayer[0].state != PLAYERSTATE_NEXT)) {
        this->unk_4A = 180;
    } else {
        this->unk_4A = 255;
    }

    this->scale2 = scale2 * 0.25f;
    this->obj.rot.z = RAND_FLOAT(360.0f);
    this->unk_44 = 0;

    if (Rand_ZeroOne() < 0.3f) {
        this->unk_44 = 1;
        this->unk_4A = 255;
        this->scale2 = scale2 * 0.3f;
    }

    this->scale1 = RAND_FLOAT(0.2f);
    Object_SetInfo(&this->info, this->obj.id);
}

void Effect_Effect343_Spawn(f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffects) - 20; i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Effect_Effect343_Setup(&gEffects[i], xPos, yPos, zPos, scale2);
            break;
        }
    }
}

void Effect_Effect387_Update(Effect387* this) {
    f32 randX;
    f32 randY;
    f32 randOther;
    s32 var_v0;

    var_v0 = 1 - 1;
    if ((gCurrentLevel == LEVEL_FORTUNA) && (gPlayer[0].state != PLAYERSTATE_NEXT)) {
        var_v0 = 4 - 1;
    }

    if (((this->timer_50 & var_v0) == 0) && (gLevelType == LEVELTYPE_PLANET)) {
        randX = RAND_FLOAT_CENTERED(10.0f);
        randY = RAND_FLOAT_CENTERED(10.0f);
        randOther = RAND_FLOAT(0.5f) + 1.0f;
        Effect_Effect343_Spawn(this->obj.pos.x + randX, this->obj.pos.y + randY, this->obj.pos.z,
                               this->scale2 * randOther);
        if (this->timer_50 == 0) {
            Object_Kill(&this->obj, this->sfxSource);
        }
    }
}

void Effect_Effect343_Update(Effect343* this) {
    if (this->unk_44 == 0) {
        this->scale2 *= 1.03f;
        this->unk_4A -= 3;
        if (this->unk_4A < 0) {
            Object_Kill(&this->obj, this->sfxSource);
        }
        this->obj.rot.z += this->unk_48;
        this->vel.y += 0.3f;
        this->vel.x += this->scale1;
    } else {
        this->scale2 *= 1.03f;
        this->unk_4A -= 7;
        if (this->unk_4A < 0) {
            Object_Kill(&this->obj, this->sfxSource);
        }
        this->obj.rot.z += this->unk_48;
        this->vel.y += 0.3f;
        this->vel.x += this->scale1;
    }
}

void Effect_Effect343_Draw(Effect343* this) {
    Graphics_SetScaleMtx(this->scale2);
    if (this->unk_44 == 0) {
        gDPSetPrimColor(gMasterDisp++, 0, 0, 0, 0, 0, this->unk_4A);
        gSPDisplayList(gMasterDisp++, D_102A010);
    } else {
        Matrix_Scale(gGfxMatrix, 1.5f, 1.5f, 1.5f, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, this->unk_4A);
        gSPDisplayList(gMasterDisp++, D_BG_PLANET_20031B0);
    }
}

void EffectFireSmoke_Setup(EffectFireSmoke* this, f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    Effect_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_EFFECT_FIRE_SMOKE_1;

    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;

    this->scale2 = scale2;
    this->scale1 = 0.5f;
    this->unk_4C = 0;
    this->obj.rot.z = RAND_FLOAT(360.0f);

    Object_SetInfo(&this->info, this->obj.id);

    if (gLevelType == LEVELTYPE_PLANET) {
        this->unk_44 = 230;
    } else {
        this->unk_44 = 255;
    }
}

void Effect_Effect340_Setup(Effect340* this, f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    Effect_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_EFFECT_FIRE_SMOKE_2;

    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;

    this->scale2 = scale2;
    this->unk_4C = 3;
    this->scale1 = 0.2f;
    this->obj.rot.z = RAND_FLOAT(360.0f);

    Object_SetInfo(&this->info, this->obj.id);

    if (gLevelType == LEVELTYPE_PLANET) {
        this->unk_44 = 230;
    } else {
        this->unk_44 = 255;
    }
}

void Effect_Effect342_Setup(Effect342* this, f32 xPos, f32 yPos, f32 zPos, f32 scale2, s32 timer50) {
    Effect_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_EFFECT_SMOKE_1;
    this->timer_50 = timer50;

    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;

    this->unk_48 = 3;
    if (Rand_ZeroOne() < 0.5f) {
        this->unk_48 = -this->unk_48;
    }
    this->unk_4A = 255;
    this->scale2 = scale2;
    this->obj.rot.z = RAND_FLOAT(360.0f);

    if ((Rand_ZeroOne() < 0.5f) && (gLevelType == LEVELTYPE_PLANET) && (timer50 != 1)) {
        this->unk_44 = 1;
    }
    if (timer50 == 2) {
        this->unk_44 = 1;
    }
    if (scale2 == 2.2f) {
        this->unk_44 = 0;
    }
    Object_SetInfo(&this->info, this->obj.id);
}

void Effect_Effect342_Spawn(f32 xPos, f32 yPos, f32 zPos, f32 scale2, s32 timer50) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Effect_Effect342_Setup(&gEffects[i], xPos, yPos, zPos, scale2, timer50);
            break;
        }
    }
}

void Effect_FireSmoke_Spawn(f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            EffectFireSmoke_Setup(&gEffects[i], xPos, yPos, zPos, scale2);
            break;
        }
    }
}

void Effect_Effect340_Spawn(f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Effect_Effect340_Setup(&gEffects[i], xPos, yPos, zPos, scale2);
            break;
        }
    }
}

void EffectFireSmoke_Spawn2(f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            EffectFireSmoke_Setup(&gEffects[i], xPos, yPos, zPos, scale2);
            break;
        }
    }
}

void func_effect_8007D074(f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Effect_Effect340_Setup(&gEffects[i], xPos, yPos, zPos, scale2);
            break;
        }
    }
}

void func_effect_8007D0E0(f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    Effect_FireSmoke_Spawn(xPos, yPos, zPos, scale2);
}

void func_effect_8007D10C(f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    Effect_Effect340_Spawn(xPos, yPos, zPos, scale2);
}

void Effect_Effect341_Setup(Effect341* this, f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    Effect_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_EFFECT_FIRE_SMOKE_3;

    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;

    this->scale2 = scale2;
    this->obj.rot.z = RAND_FLOAT(360.0f);

    Object_SetInfo(&this->info, this->obj.id);

    if (gLevelType == LEVELTYPE_PLANET) {
        this->unk_4C = 15;
    }
    this->unk_44 = 180;
}

void Effect_Effect341_Spawn(f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Effect_Effect341_Setup(&gEffects[i], xPos, yPos, zPos, scale2);
            break;
        }
    }
}

void func_effect_8007D24C(f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    if (gLevelType == LEVELTYPE_PLANET) {
        Effect_Effect341_Spawn(xPos, yPos, zPos, scale2);
        Effect_Effect342_Spawn(xPos, scale2 + yPos, zPos, scale2, 9);
    } else {
        func_effect_8007D0E0(xPos, yPos, zPos, scale2);
    }
}

void func_effect_8007D2C8(f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    EffectFireSmoke_Spawn2(xPos, yPos, zPos, scale2);
}

void Effect_Effect339_Update(EffectFireSmoke* this) {
    if (gLevelType == LEVELTYPE_PLANET) {
        if ((gCurrentLevel == LEVEL_KATINA) && (gPlayer[0].state == PLAYERSTATE_LEVEL_COMPLETE)) {
            this->vel.y += 0.1f;
            if (this->timer_50 == 0) {
                this->unk_4C++;
                this->timer_50 = 4;
                if (this->unk_4C > 15) {
                    this->timer_50 = 5;
                }
                if (this->unk_4C > 20) {
                    Object_Kill(&this->obj, this->sfxSource);
                }
            }
        } else {
            if ((gCurrentLevel == LEVEL_MACBETH) && (gPlayer[0].state == PLAYERSTATE_LEVEL_COMPLETE) &&
                (this->vel.x != 0)) {
                Math_SmoothStepToF(&this->vel.x, -1.0f, 1.0f, 1.0f, 0.0f);
                Math_SmoothStepToF(&this->vel.z, 4.0f, 1.0f, 1.0f, 0.0f);
                this->vel.y += 1.7f;
            }
            this->vel.y += 0.3f;
            if (this->timer_50 == 0) {
                this->unk_4C++;
                if (this->unk_4C > 15) {
                    this->timer_50 = 2;
                }
                if (this->unk_4C > 20) {
                    Object_Kill(&this->obj, this->sfxSource);
                }
            }
        }
    } else {
        if (this->timer_50 == 0) {
            this->unk_4C++;
            this->timer_50 = this->unk_46;
            if (this->unk_4C > 13) {
                Object_Kill(&this->obj, this->sfxSource);
            }
        }
        this->unk_44 -= 15;
    }
    if (gLight3Brightness < this->scale1) {
        gLight3Brightness = this->scale1;
        gLight3x = this->obj.pos.x;
        gLight3y = this->obj.pos.y;
        gLight3z = this->obj.pos.z;
        gLight3R = 255;
        gLight3G = 50;
        gLight3B = 0;
    }
    Math_SmoothStepToF(&this->scale1, 0.0f, 1.0f, 0.05f, 0.0f);
}

Gfx* D_800D17A4[] = {
    D_BG_PLANET_200B630, D_BG_PLANET_200B630, D_BG_PLANET_200B630, D_BG_PLANET_200B630, D_BG_PLANET_200A5A0,
    D_BG_PLANET_2009510, D_BG_PLANET_2008480, D_BG_PLANET_20073F0, D_BG_PLANET_2006360, D_BG_PLANET_200C6C0,
    D_BG_PLANET_20052D0, D_BG_PLANET_2004240, D_BG_PLANET_20031B0, D_BG_PLANET_2002120, D_BG_PLANET_2001090,
    D_BG_PLANET_2000000, D_BG_PLANET_2010A30, D_BG_PLANET_20101A0, D_BG_PLANET_200F910, D_BG_PLANET_200F080,
    D_BG_PLANET_200E7F0,
};

f32 D_800D17F8[] = {
    1.0f, 1.1f, 1.1f, 1.2f, 1.2f, 1.3f, 1.3f, 1.4f, 1.4f, 1.5f, 1.5f,
    1.6f, 1.6f, 1.7f, 1.7f, 1.8f, 1.8f, 1.9f, 1.9f, 2.0f, 2.0f,
};

Color_RGBA32 D_800D184C[] = {
    { 255, 255, 255, 255 }, { 255, 0, 0, 255 },     { 255, 40, 40, 255 },   { 255, 80, 80, 255 },
    { 255, 120, 120, 255 }, { 255, 160, 160, 255 }, { 255, 200, 200, 255 }, { 255, 240, 240, 255 },
    { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 },
    { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 255, 255, 255, 255 },
    { 0, 0, 0, 255 },       { 0, 0, 0, 200 },       { 0, 0, 0, 150 },       { 0, 0, 0, 100 },
    { 0, 0, 0, 50 },
};

Gfx* D_800D18A0[] = {
    D_BG_SPACE_20066C0, D_BG_SPACE_20066C0, D_BG_SPACE_2005E30, D_BG_SPACE_20055A0, D_BG_SPACE_2004D10,
    D_BG_SPACE_2004480, D_BG_SPACE_2003BF0, D_BG_SPACE_2003360, D_BG_SPACE_2002AD0, D_BG_SPACE_2002240,
    D_BG_SPACE_20019B0, D_BG_SPACE_2001120, D_BG_SPACE_2000890, D_BG_SPACE_2000000,
};

// Effects 339 to 341
void Effect_FireSmoke_Draw(EffectFireSmoke* this) {
    f32 scale;

    Graphics_SetScaleMtx(this->scale2);

    if (gLevelType == LEVELTYPE_PLANET) {
        gDPSetPrimColor(gMasterDisp++, 0, 0, D_800D184C[this->unk_4C].r, D_800D184C[this->unk_4C].g,
                        D_800D184C[this->unk_4C].b, D_800D184C[this->unk_4C].a);
        scale = D_800D17F8[this->unk_4C] - 0.5f;
        Matrix_Scale(gGfxMatrix, scale, scale, 1.0f, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, D_800D17A4[this->unk_4C]);
        return;
    }

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 100, this->unk_44);

    if (this->unk_4C == 0) {
        Matrix_Scale(gGfxMatrix, 2.5f, 2.5f, 2.5f, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, D_800D18A0[this->unk_4C]);
        return;
    }
    gSPDisplayList(gMasterDisp++, D_800D18A0[this->unk_4C]);
}

void Effect_Effect340_Update(Effect340* this) {
    if (gLevelType == LEVELTYPE_PLANET) {
        this->vel.y += 0.3f;
        if (this->timer_50 == 0) {
            if (this->unk_4C > 15) {
                this->timer_50 = 2;
                this->unk_4C = this->unk_4C + 1;
            } else {
                this->unk_4C = this->unk_4C + 2;
            }
            if (this->unk_4C > 20) {
                Object_Kill(&this->obj, this->sfxSource);
            }
        }
    } else {
        if (this->timer_50 == 0) {
            this->unk_4C++;
            this->timer_50 = 0;
            if (this->unk_4C > 13) {
                Object_Kill(&this->obj, this->sfxSource);
            }
        }
        this->unk_44 -= 15;
    }
    if (gLight3Brightness < this->scale1) {
        gLight3Brightness = this->scale1;
        gLight3x = this->obj.pos.x;
        gLight3y = this->obj.pos.y;
        gLight3z = this->obj.pos.z;
        gLight3R = 255;
        gLight3G = 50;
        gLight3B = 0;
    }
    Math_SmoothStepToF(&this->scale1, 0, 1.0f, 0.1f, 0.0f);
}

void Effect_Effect341_Update(Effect341* this) {
    if (gLevelType == LEVELTYPE_SPACE) {
        Effect_Effect339_Update(this);
        return;
    }
    this->vel.y += 0.3f;
    if (this->timer_50 == 0) {
        this->unk_4C++;
        this->timer_50 = 2;
        if (this->unk_4C >= 20) {
            Object_Kill(&this->obj, this->sfxSource);
        }
    }
    if (this->unk_4C > 15) {
        this->unk_44 -= 20;
    }
}

void Effect_Effect367_Setup(Effect367* this, f32 xPos, f32 yPos, f32 zPos, f32 scale2, f32 scale1, s32 timer50) {
    Effect_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_EFFECT_367;
    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;
    this->unk_44 = 80;
    this->scale2 = scale2;
    this->scale1 = scale1;
    this->timer_50 = timer50;
    Object_SetInfo(&this->info, this->obj.id);
}

void Effect_Effect367_Spawn(f32 xPos, f32 yPos, f32 zPos, f32 scale2, f32 scale1, s32 timer50) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Effect_Effect367_Setup(&gEffects[i], xPos, yPos, zPos, scale2, scale1, timer50);
            break;
        }
    }
}

void Effect_Effect375_Update(Effect375* this) {
    this->scale2 += this->scale1;
    if (this->scale1 > 0.0f) {
        this->scale1 -= 0.01f;
    } else {
        this->scale1 -= 0.001f;
    }
    this->obj.rot.y += this->unk_60.y;
    if (this->scale2 < 0.01f) {
        Object_Kill(&this->obj, this->sfxSource);
    }
}

void Effect_Effect375_Draw(Effect375* this) {
    Graphics_SetScaleMtx(this->scale2);
    RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
    gSPDisplayList(gMasterDisp++, D_CO_6004900);
    RCP_SetupDL(&gMasterDisp, SETUPDL_64);
}

void Effect_Effect374_Update(Effect374* this) {
    Vec3f sp54 = { 0.0f, -10.0f, 0.0f };

    switch (this->state) {
        case 0:
            this->vel.y -= 0.5f;
            if ((this->timer_50 == 0) && ((Object_CheckCollision(1000, &this->obj.pos, &sp54, 1) != 0) ||
                                          (this->obj.pos.y < (gGroundHeight + 10.0f)))) {
                this->vel.y = 0.0f;
                if (this->obj.pos.y < (gGroundHeight + 10.0f)) {
                    this->obj.pos.y = gGroundHeight;
                }
                this->state = 1;
                this->timer_50 = 30;
                this->unk_44 = 192;
                this->scale2 = 2.5f;
                this->scale1 = 2.5f;
                AUDIO_PLAY_SFX(NA_SE_EN_EXPLOSION_M, this->sfxSource, 4);
                func_effect_8007D0E0(this->obj.pos.x, this->obj.pos.y + 30.0f, this->obj.pos.z, 7.0f);
                Effect386_Spawn1(this->obj.pos.x, this->obj.pos.y + 30.0f, this->obj.pos.z, 0.0f, 0.0f, 0.0f, 4.0f, 5);
                if ((this->obj.pos.y < (gGroundHeight + 10.0f)) || (gGroundSurface != SURFACE_WATER)) {
                    PlayerShot_SpawnEffect344(this->obj.pos.x, 3.0f, this->obj.pos.z, this->obj.pos.x, this->obj.pos.z,
                                              0.0f, 0.0f, 90.0f, 5.0f, 0, 0);
                    break;
                }
            }
            break;

        case 1:
            this->scale2 += ((20.0f - this->scale2) * 0.1f);
            if (this->scale2 > 19.0f) {
                this->scale1 -= 0.3f;
                this->unk_44 -= 20;
                if (this->unk_44 < 0) {
                    Object_Kill(&this->obj, this->sfxSource);
                }
            }

            this->obj.rot.y = 180.0f - this->obj.rot.y;

            if ((fabsf(gPlayer[0].trueZpos - this->obj.pos.z) < 40.0f) &&
                (fabsf(gPlayer[0].pos.x - this->obj.pos.x) < 80.0f)) {
                if ((this->obj.pos.y < gPlayer[0].pos.y) &&
                    ((gPlayer[0].pos.y - this->obj.pos.y) < (this->scale2 * 35.0f)) && (gPlayer[0].mercyTimer == 0)) {
                    Player_ApplyDamage(gPlayer, 0, this->info.damage);
                }
            }
            break;
    }
}

void Effect_Effect374_Draw(Effect374* this) {
    switch (this->state) {
        case 0:
            Graphics_SetScaleMtx(this->scale2);
            RCP_SetupDL_60(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
            gSPDisplayList(gMasterDisp++, D_ENMY_PLANET_4008CE0);
            RCP_SetupDL(&gMasterDisp, SETUPDL_64);
            break;

        case 1:
            Matrix_Scale(gGfxMatrix, this->scale1, this->scale2, 2.5f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            RCP_SetupDL_40();
            gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
            gSPDisplayList(gMasterDisp++, D_ENMY_PLANET_4008F70);
            RCP_SetupDL(&gMasterDisp, SETUPDL_64);
            break;
    }
}

void Effect_Effect344_Update(Effect344* this) {
    s32 i;
    f32 x;
    f32 z;
    f32 y;

    if (gGroundType == 4) {
        Ground_801B6E20(this->obj.pos.x, this->obj.pos.z + gPathProgress, &x, &y, &z);
        this->obj.pos.y = y + 3.0f;
        this->obj.rot.x = RAD_TO_DEG(x);
        this->obj.rot.z = RAD_TO_DEG(z);
    }

    if (((this->unk_44 == 1) || (this->unk_44 == 3)) && ((s32) (this->timer_50 % 4U) == 1) && (Rand_ZeroOne() < 0.5f)) {
        func_effect_8007D10C(this->obj.pos.x, this->obj.pos.y + (this->scale2 * 5.0f), this->obj.pos.z + 3.0f,
                             (RAND_FLOAT(0.7f) + 1.0f) * (this->scale2 * 1.2f));
    }

    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        if ((gEffects[i].obj.status == OBJ_ACTIVE) && (gEffects[i].obj.id == OBJ_EFFECT_EXPLOSION_MARK_1) &&
            (i != this->index) && (fabsf(this->obj.pos.z - gEffects[i].obj.pos.z) < 20.0f) &&
            (fabsf(this->obj.pos.x - gEffects[i].obj.pos.x) < 20.0f) &&
            (fabsf(this->obj.pos.y - gEffects[i].obj.pos.y) < 20.0f)) {
            Object_Kill(&this->obj, this->sfxSource);
        }
    }
}

void Effect_Effect345_Update(Effect345* this) {
    if ((gCamCount != 1) && (this->timer_50 == 0)) {
        Object_Kill(&this->obj, this->sfxSource);
    }
}

void Effect_Effect342_Update(Effect342* this) {
    if (this->timer_50 == 0) {
        this->scale2 *= 1.035f;
        this->unk_4A -= 8;
        if (this->unk_4A < 0) {
            Object_Kill(&this->obj, this->sfxSource);
        }
    }
    this->obj.rot.z += this->unk_48;
    if (gLevelType == LEVELTYPE_PLANET) {
        this->vel.y += 0.2f;
    }
}

void Effect_Effect342_Draw(Effect342* this) {
    Graphics_SetScaleMtx(this->scale2);
    if (this->unk_44 == 0) {
        gDPSetPrimColor(gMasterDisp++, 0, 0, 0, 0, 0, this->unk_4A);
    } else {
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, this->unk_4A);
    }
    gSPDisplayList(gMasterDisp++, D_BG_PLANET_2010A30);
}

void Effect_Effect351_Update(Effect351* this) {
    this->scale2 += 0.02f;
    this->unk_4A -= 4;
    if (this->unk_4A < 0) {
        Object_Kill(&this->obj, this->sfxSource);
    }
    this->obj.rot.z += this->unk_48;
    this->vel.y += 0.05f;
}

void Effect_Effect365_Update(Effect365* this) {
    switch (this->state) {
        case 0:
            if (this->unk_4C != 0) {
                Math_SmoothStepToF(&this->scale2, 5.0f, 0.05f, 0.5f, 0.0f);
                this->unk_44 -= 10;
                this->obj.rot.z += this->scale1;
                if (this->unk_44 < 0) {
                    Object_Kill(&this->obj, this->sfxSource);
                }
                break;
            }

            this->scale2 += 0.02f;
            this->unk_44--;

            if (this->unk_44 < 0) {
                Object_Kill(&this->obj, this->sfxSource);
            }

            this->obj.rot.z += this->scale1;
            Math_SmoothStepToF(&this->vel.y, 0.5f, 0.05f, 0.2f, 0.00001f);
            break;

        case 1:
            this->vel.y = 3.0f;
            Math_SmoothStepToF(&this->scale2, 5.0f, 0.05f, 0.5f, 0.0f);
            this->unk_44 -= 10;
            this->obj.rot.z += this->scale1;
            if (this->unk_44 < 0) {
                Object_Kill(&this->obj, this->sfxSource);
            }
            break;
    }
}

void Effect_Effect365_Draw(Effect365* this) {
    Graphics_SetScaleMtx(this->scale2);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, this->unk_44);
    gSPDisplayList(gMasterDisp++, D_BG_PLANET_2010A30);
}

void Effect_Effect367_Update(Effect367* this) {
    if (this->timer_50 == 0) {
        Math_SmoothStepToF(&this->scale2, this->scale1, 0.05f, 100.0f, 0.0f);
        this->unk_44 -= 2;
        if (this->unk_44 < 0) {
            Object_Kill(&this->obj, this->sfxSource);
        }
    }
}

void func_effect_8007E6B8(Effect* this, u32 objId, f32 xPos, f32 yPos, f32 zPos, f32 speed) {
    f32 sp54;
    f32 sp50;
    f32 temp_ft4;
    Vec3f sp40;
    Vec3f sp34;

    Effect_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = objId;
    this->timer_50 = 100;

    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;

    Object_SetInfo(&this->info, this->obj.id);
    sp50 = Math_Atan2F(gPlayer[0].pos.x - xPos, gPlayer[0].trueZpos - zPos);
    temp_ft4 = sqrtf(SQ(gPlayer[0].pos.x - xPos) + SQ(gPlayer[0].trueZpos - zPos));
    sp54 = -Math_Atan2F(gPlayer[0].pos.y - yPos, temp_ft4);

    Matrix_RotateY(gCalcMatrix, sp50, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, sp54, MTXF_APPLY);

    sp40.x = 0.0f;
    sp40.y = 0.0f;
    sp40.z = speed;

    Matrix_MultVec3f(gCalcMatrix, &sp40, &sp34);

    this->vel.x = sp34.x + gPathVelX;
    this->vel.y = sp34.y + gPathVelY;
    this->vel.z = sp34.z - gPathVelZ;

    if ((objId == OBJ_EFFECT_ENEMY_LASER_1) || (objId == OBJ_EFFECT_354)) {
        this->obj.rot.x = RAD_TO_DEG(sp54);
        this->obj.rot.y = RAD_TO_DEG(sp50);
    }

    if (objId == OBJ_EFFECT_356) {
        AUDIO_PLAY_SFX(NA_SE_EN_ENERGY_BEAM, this->sfxSource, 4);
    }

    if (objId == OBJ_EFFECT_376) {
        this->obj.rot.z = RAND_FLOAT(360.0f);
        this->unk_4A = 180;
        this->scale2 = 5.0f;
    } else if ((objId == OBJ_EFFECT_355) || (objId == OBJ_EFFECT_377)) {
        AUDIO_PLAY_SFX(NA_SE_EN_ENERGY_BEAM, this->sfxSource, 4);
    } else {
        AUDIO_PLAY_SFX(NA_SE_EN_SHOT_0, this->sfxSource, 4);
    }
}

void func_effect_8007E93C(Effect* this, u32 objId, f32 xPos, f32 yPos, f32 zPos, f32 speed) {
    f32 sp54;
    f32 sp50;
    f32 temp_ft4;
    Vec3f sp40;
    Vec3f sp34;

    Effect_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = objId;
    this->timer_50 = 100;

    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;

    Object_SetInfo(&this->info, this->obj.id);
    sp50 = Math_Atan2F(gPlayer[0].cam.eye.x - xPos, gPlayer[0].cam.eye.z - zPos);
    temp_ft4 = sqrtf(SQ(gPlayer[0].cam.eye.x - xPos) + SQ(gPlayer[0].cam.eye.z - zPos));
    sp54 = -Math_Atan2F(gPlayer[0].cam.eye.y - yPos, temp_ft4);

    Matrix_RotateY(gCalcMatrix, sp50, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, sp54, MTXF_APPLY);

    sp40.x = 0.0f;
    sp40.y = 0.0f;
    sp40.z = speed;

    Matrix_MultVec3f(gCalcMatrix, &sp40, &sp34);

    this->vel.x = sp34.x + gPathVelX;
    this->vel.y = sp34.y + gPathVelY;
    this->vel.z = sp34.z - gPathVelZ;

    if (objId == OBJ_EFFECT_ENEMY_LASER_1) {
        this->obj.rot.x = RAD_TO_DEG(sp54);
        this->obj.rot.y = RAD_TO_DEG(sp50);
    }

    if (objId == OBJ_EFFECT_356) {
        AUDIO_PLAY_SFX(NA_SE_EN_ENERGY_BEAM, this->sfxSource, 4);
    }

    if (objId == OBJ_EFFECT_376) {
        this->obj.rot.z = RAND_FLOAT(360.0f);
        this->unk_4A = 180;
        this->scale2 = 5.0f;
    } else if ((objId == OBJ_EFFECT_355) || (objId == OBJ_EFFECT_377)) {
        AUDIO_PLAY_SFX(NA_SE_EN_ENERGY_BEAM, this->sfxSource, 4);
    } else {
        AUDIO_PLAY_SFX(NA_SE_EN_SHOT_0, this->sfxSource, 4);
    }
}

void func_effect_8007EBB8(Effect* this, ObjectId objId, f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel,
                          f32 scale2) {
    Effect_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = objId;

    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;

    this->timer_50 = 100;

    this->vel.x = xVel;
    this->vel.y = yVel;
    this->vel.z = zVel;

    this->scale2 = scale2;

    if (objId == OBJ_EFFECT_355) {
        AUDIO_PLAY_SFX(NA_SE_EN_ENERGY_BEAM, this->sfxSource, 4);
    } else {
        AUDIO_PLAY_SFX(NA_SE_EN_SHOT_0, this->sfxSource, 4);
    }
    Object_SetInfo(&this->info, this->obj.id);
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

void func_effect_8007ED54(Effect* this, ObjectId objId, f32 xPos, f32 yPos, f32 zPos, f32 xRot, f32 yRot, f32 zRot,
                          f32 unkX, f32 unkY, f32 unkZ, f32 xVel, f32 yVel, f32 zVel, f32 scale2) {
    Effect_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = objId;

    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;

    this->timer_50 = 100;
    if (gCurrentLevel == LEVEL_AQUAS) {
        this->timer_50 = 75;
    }

    this->vel.x = xVel;
    this->vel.y = yVel;
    this->vel.z = zVel;

    this->obj.rot.x = xRot;
    this->obj.rot.y = yRot;
    this->obj.rot.z = zRot;

    this->unk_60.x = unkX;
    this->unk_60.y = unkY;
    this->unk_60.z = unkZ;

    this->scale2 = scale2;

    if (this->obj.id != OBJ_EFFECT_380) {
        AUDIO_PLAY_SFX(NA_SE_EN_SHOT_0, this->sfxSource, 4);
    }
    Object_SetInfo(&this->info, this->obj.id);
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

void Effect_EnemyLaser(ObjectId objId, f32 xPos, f32 yPos, f32 zPos, f32 speed) {
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

// Unused ?
void func_effect_8007F2FC(Effect* this) {
    if (this->timer_50 == 0) {
        Object_Kill(&this->obj, this->sfxSource);
    }

    if ((this->obj.pos.y < gGroundHeight) && (gLevelType == LEVELTYPE_PLANET)) {
        Object_Kill(&this->obj, this->sfxSource);
    }

    if (gLevelType == LEVELTYPE_PLANET) {
        this->vel.y -= 0.3f;
    }

    if (this->obj.pos.y < gWaterLevel) {
        this->vel.y += 0.2f;
        this->obj.pos.y -= this->vel.y * 0.5f;
        this->obj.pos.x -= this->vel.x * 0.5f;
        this->obj.pos.z -= this->vel.z * 0.5f;
    }

    if ((this->unk_44 == 1) && ((gGameFrameCount % 2) == 0)) {
        func_effect_8007D0E0(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 1.5f);
    }
}

void Effect_Effect346_Update(Effect346* this) {
    if (gCurrentLevel == LEVEL_AQUAS) {
        this->obj.rot.z += 3.5f;
        this->vel.z = 5.0f;

        if (this->unk_44 != 0) {
            Math_SmoothStepToF(&this->scale1, 100.0f, 1.0f, 20.0f, 0.0001f);
        } else {
            Math_SmoothStepToF(&this->scale1, 0.0f, 1.0f, 20.0f, 0.0001f);
        }

        if (this->unk_46 == 0) {
            this->unk_46 = 30;
            this->unk_44++;
            this->unk_44 &= 1;
        } else {
            this->unk_46--;
        }

        if (gPathVelZ < 0.0f) {
            this->vel.z = -10.0f;
        }

        if (this->timer_50 == 0) {
            Object_Kill(&this->obj, this->sfxSource);
        }
    } else {
        this->obj.rot.z += 3.5f;
        if (gLevelType == LEVELTYPE_PLANET) {
            this->vel.y += 0.2f;
        }
        if (this->timer_50 == 0) {
            Object_Kill(&this->obj, this->sfxSource);
        }
    }
}

// Unused ?
void func_effect_8007F5AC(Effect* this) {
    if (this->unk_4C == 0) {
        this->unk_46++;
        if ((this->unk_46 & 0x20) == 0) {
            this->vel.x += 0.5f;
        } else {
            this->vel.x -= 0.5f;
        }

        if ((gGameFrameCount % 2) == 0) {
            this->unk_44--;
            if (this->unk_44 < 20) {
                Object_Kill(&this->obj, this->sfxSource);
            }
        }

        this->scale2 += 0.02f;
        if ((gGameFrameCount & 0x10) == 0) {
            this->scale2 += 0.01f;
        } else {
            this->scale2 -= 0.01f;
        }
    }
}

void Effect_Effect348_Update(Effect348* this) {
    s32 i;
    f32 temp;
    f32 cos;
    f32 sin;
    f32 randfloat;
    f32 x;
    f32 z;
    f32 y;
    f32 yPos;

    Math_SmoothStepToF(&this->scale2, this->scale1, 0.1f, 12.0f, 0.1f);

    this->unk_44 -= 2;
    if (this->unk_44 < 0) {
        Object_Kill(&this->obj, this->sfxSource);
    }

    if (((gGameFrameCount % 4) == 0) && (this->state == 0)) {
        randfloat = RAND_FLOAT(30.0f);
        for (i = 0; i < 36; i += 2) {
            temp = (i * 10.0f * M_DTOR) + randfloat;
            sin = __sinf(temp) * this->scale2 * 8.0f;
            cos = __cosf(temp) * this->scale2 * 8.0f;
            yPos = gGroundHeight + 40.0f;

            if (gGroundType == 4) {
                Ground_801B6E20(this->obj.pos.x + sin, this->obj.pos.z + cos + gPathProgress, &x, &y, &z);
                yPos = y + 30.0f;
            }

            if (gCurrentLevel == LEVEL_AQUAS) {
                Effect_Effect364_Spawn(this->obj.pos.x + sin, yPos, this->obj.pos.z + cos, 20.0f);
            } else if (gCurrentLevel == LEVEL_FORTUNA) {
                Effect_Effect362_Spawn(this->obj.pos.x + sin, yPos, this->obj.pos.z + cos, 20.0f);
            } else if (gCurrentLevel == LEVEL_TITANIA) {
                Effect_Effect359_Spawn(this->obj.pos.x + sin, yPos, this->obj.pos.z + cos, 10.0f, 255, 15, 0);
            }
        }
    }
}

void Effect_Effect349_Update(Effect349* this) {
    s32 i;
    f32 x;
    f32 z;
    f32 y;
    f32 temp;
    f32 cos;
    f32 sin;
    f32 randFloat;
    f32 yPos;

    this->scale2 += this->scale1;
    this->scale1 -= 0.08f;
    if (this->scale1 < 0.1f) {
        this->scale1 = 0.1f;
    }

    this->unk_44 -= 9;
    if (this->unk_44 < 0) {
        Object_Kill(&this->obj, this->sfxSource);
        return;
    }

    if ((gGameFrameCount % 2) == 0) {
        randFloat = RAND_FLOAT(144.0f);
        for (i = 0; i < 5; i++) {
            temp = (i * 72.0f * M_DTOR) + randFloat;
            sin = __sinf(temp) * this->scale2 * 16.0f;
            cos = __cosf(temp) * this->scale2 * 16.0f;
            yPos = gGroundHeight + 10.0f;

            if (gGroundType == 4) {
                Ground_801B6E20(this->obj.pos.x + sin, this->obj.pos.z + cos + gPathProgress, &x, &y, &z);
                yPos = y + 10.0f;
            }

            if (gCurrentLevel == LEVEL_FORTUNA) {
                Effect_Effect362_Spawn(this->obj.pos.x + sin, yPos, this->obj.pos.z + cos, 8.0f);
            } else if (gCurrentLevel == LEVEL_TITANIA) {
                Effect_Effect359_Spawn(this->obj.pos.x + sin, yPos, this->obj.pos.z + cos, 8.0f, 255, 15, 0);
            }
        }
    }
}

void Effect_Effect350_Update(Effect350* this) {
    s32 i;
    f32 temp;
    f32 sin;
    f32 cos;
    f32 randFloat;
    f32 yPos;

    this->scale2 += this->scale1;
    this->scale1 -= .1f;
    if (this->scale1 < 0.1f) {
        this->scale1 = 0.1f;
    }

    this->unk_44 -= 6;
    if (this->unk_44 < 0) {
        Object_Kill(&this->obj, this->sfxSource);
    }

    if (((gGameFrameCount % 2) == 0)) {
        randFloat = RAND_FLOAT(144.0f);
        for (i = 0; i < 10; i++) {
            temp = (i * 36.0f * M_DTOR) + randFloat;
            sin = __sinf(temp) * this->scale2 * 16.0f;
            cos = __cosf(temp) * this->scale2 * 16.0f;
            yPos = gGroundHeight + 10.0f;
            Effect_Effect362_Spawn(this->obj.pos.x + sin, yPos, this->obj.pos.z + cos, 12.0f);
        }
    }
}

bool func_effect_8007FD84(Effect* this) {
    s32 i;
    Actor* actor;

    for (i = 1; i < ARRAY_COUNT(gTeamEventActorIndex); i++) {
        actor = &gActors[gTeamEventActorIndex[i]];
        if (actor->obj.status == OBJ_ACTIVE) {
            if ((actor->iwork[12] >= TEAM_ID_FALCO) && (actor->iwork[12] <= TEAM_ID_BILL) &&
                (fabsf(actor->obj.pos.z - this->obj.pos.z) < 100.0f) &&
                (fabsf(actor->obj.pos.x - this->obj.pos.x) < 100.0f) &&
                (fabsf(actor->obj.pos.y - this->obj.pos.y) < 100.0f)) {
                actor->dmgType = DMG_BEAM;
                actor->dmgPart = 0;
                actor->damage = 10;
                if (this->obj.id == OBJ_EFFECT_354) {
                    actor->damage = 30;
                }
                actor->dmgSource = CS_SHOT_ID;
                return true;
            }
        }
    }
    return false;
}

void Effect_Effect353_354_Update(Effect* this) {
    Vec3f srcVelocity;
    Vec3f destVelocity;
    Vec3f velocity;
    f32 var_fa0 = 0.0f;

    if (this->timer_50 == 0) {
        Object_Kill(&this->obj, this->sfxSource);
        return;
    }

    if (func_effect_8007FD84(this)) {
        Object_Kill(&this->obj, this->sfxSource);
        return;
    }

    if (gPlayer[0].barrelRollAlpha != 0) {
        var_fa0 = 100.0f;
    }

    if (fabsf(gPlayer[0].trueZpos - this->obj.pos.z) < (50.0f + var_fa0)) {
        if ((fabsf(gPlayer[0].pos.x - this->obj.pos.x) < (30.0f + var_fa0)) &&
            (fabsf(gPlayer[0].pos.y - this->obj.pos.y) < (30.0f + var_fa0))) {
            if ((gPlayer[0].barrelRollAlpha != 0) || (gPlayer[0].meteoWarpTimer != 0)) {
                this->obj.rot.y = 90.0f;
                this->obj.rot.x = RAND_FLOAT(360.0f);
                Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
                Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);
                srcVelocity.x = 0.0f;
                srcVelocity.y = 0.0f;
                srcVelocity.z = 100.0f;
                Matrix_MultVec3f(gCalcMatrix, &srcVelocity, &destVelocity);
                this->vel.x = destVelocity.x;
                this->vel.y = destVelocity.y;
                this->vel.z = destVelocity.z;
                gPlayer[0].deflectCount++;
                AUDIO_PLAY_SFX(NA_SE_ROLLING_REFLECT, this->sfxSource, 0);
            }

            if ((gPlayer[0].barrelRollAlpha == 0) && (gPlayer[0].mercyTimer == 0)) {
                Player_ApplyDamage(gPlayer, 0, this->info.damage);
                gPlayer[0].knockback.x = 20.0f;
                if (this->vel.x < 0.0f) {
                    gPlayer[0].knockback.x *= -1.0f;
                }
                if (gCurrentLevel != LEVEL_MACBETH) {
                    gPlayer[0].knockback.y = 20.0f;
                    if (this->vel.y < 0.0f) {
                        gPlayer[0].knockback.y *= -1.0f;
                    }
                }
                Object_Kill(&this->obj, this->sfxSource);
            }
        }
    }

    if (gGroundType == 4) {
        if (Ground_801B6AEC(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + gPathProgress) != 0) {
            Object_Kill(&this->obj, this->sfxSource);
        }
    } else if (this->obj.pos.y < gGroundHeight) {
        Object_Kill(&this->obj, this->sfxSource);
        if (gGroundSurface != SURFACE_WATER) {
            this->obj.pos.y = gGroundHeight;
            func_effect_8007D074(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 2.0f);
        }
    }

    velocity.x = this->vel.x;
    velocity.y = this->vel.y;
    velocity.z = this->vel.z;

    if (gCurrentLevel != LEVEL_MACBETH) {
        if (Object_CheckCollision(1000, &this->obj.pos, &velocity, 2) != 0) {
            func_effect_8007D10C(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 2.0f);
            Object_Kill(&this->obj, this->sfxSource);
        }
    } else if (Macbeth_801A55D4(1000, &this->obj.pos, &velocity, 0) != 0) {
        func_effect_8007D10C(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 2.0f);
        Object_Kill(&this->obj, this->sfxSource);
    }
}

void Effect_Effect355_Update(Effect355* this) {
    Effect_Effect353_354_Update(this);
}

void Effect_Effect377_Update(Effect377* this) {
    Effect_Effect353_354_Update(this);
}

void Effect_Effect356_Update(Effect356* this) {
    Effect_Effect353_354_Update(this);
    this->obj.rot.z += 10.0f;

    this->scale2 = 3.0f;
    if ((gGameFrameCount % 2) != 0) {
        this->scale2 = 3.5f;
    }
}

void Effect_Effect376_Update(Effect376* this) {
    this->obj.rot.z += 8.0f;
    this->scale2 += 0.1f;
    // It seems they forgot that unk_4A is s16 and not a float...
    this->unk_4A -= 3.5f;
    if (this->unk_4A < 50.0f) {
        this->unk_4A = 50;
    }
    func_effect_8007A774(gPlayer, this, 50.0f);
}

void Effect_Effect398_Update(Effect398* this) {
    f32 xRot;
    f32 yRot;
    f32 temp;
    f32 var_fa0 = 0.0f;
    Vec3f srcVelocity;
    Vec3f destVelocity;
    Vec3f sp3C;

    switch (this->state) {
        case 0:
            yRot = Math_Atan2F(gPlayer[0].pos.x - this->obj.pos.x, gPlayer[0].trueZpos - this->obj.pos.z);
            temp = sqrtf(SQ(gPlayer[0].pos.x - this->obj.pos.x) + SQ(gPlayer[0].trueZpos - this->obj.pos.z));
            xRot = -Math_Atan2F(gPlayer[0].pos.y - this->obj.pos.y, temp);
            Matrix_RotateY(gCalcMatrix, yRot, MTXF_NEW);
            Matrix_RotateX(gCalcMatrix, xRot, MTXF_APPLY);
            srcVelocity.y = 0.0f;
            srcVelocity.x = 0.0f;
            srcVelocity.z = 100.0f;
            Matrix_MultVec3f(gCalcMatrix, &srcVelocity, &destVelocity);
            this->vel.x = destVelocity.x + gPathVelX;
            this->vel.y = destVelocity.y + gPathVelY;
            this->vel.z = destVelocity.z - gPathVelZ;
            this->state++;
            break;

        case 1:
            this->obj.rot.z = 360.0f - this->obj.rot.z;
            if (this->timer_50 == 0) {
                Object_Kill(&this->obj, this->sfxSource);
                return;
            }

            if (func_effect_8007FD84(this)) {
                Object_Kill(&this->obj, this->sfxSource);
                return;
            }

            if (gPlayer[0].barrelRollAlpha != 0) {
                var_fa0 = 100.0f;
            }

            if (fabsf(gPlayer[0].trueZpos - this->obj.pos.z) < (50.0f + var_fa0)) {
                if ((fabsf(gPlayer[0].pos.x - this->obj.pos.x) < (30.0f + var_fa0)) &&
                    (fabsf(gPlayer[0].pos.y - this->obj.pos.y) < (30.0f + var_fa0))) {
                    if ((gPlayer[0].barrelRollAlpha != 0) || (gPlayer[0].meteoWarpTimer != 0)) {
                        this->obj.rot.y = 90.0f;
                        this->obj.rot.x = RAND_FLOAT(360.0f);
                        Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
                        Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);
                        srcVelocity.y = 0.0f;
                        srcVelocity.x = 0.0f;
                        srcVelocity.z = 100.0f;
                        Matrix_MultVec3f(gCalcMatrix, &srcVelocity, &destVelocity);
                        this->vel.x = destVelocity.x;
                        this->vel.y = destVelocity.y;
                        this->vel.z = destVelocity.z;
                        gPlayer[0].deflectCount++;
                        AUDIO_PLAY_SFX(NA_SE_ROLLING_REFLECT, this->sfxSource, 0);
                    }

                    if ((gPlayer[0].barrelRollAlpha == 0) && (gPlayer[0].mercyTimer == 0)) {
                        Player_ApplyDamage(gPlayer, 0, this->info.damage);
                        gPlayer[0].knockback.x = 20.0f;
                        if (this->vel.x < 0.0f) {
                            gPlayer[0].knockback.x *= -1.0f;
                        }
                        gPlayer[0].knockback.y = 20.0f;
                        if (this->vel.y < 0.0f) {
                            gPlayer[0].knockback.y *= -1.0f;
                        }
                        Object_Kill(&this->obj, this->sfxSource);
                    }
                }

                if (gGroundType == 4) {
                    if (Ground_801B6AEC(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + gPathProgress) != 0) {
                        Object_Kill(&this->obj, this->sfxSource);
                    }
                } else if (this->obj.pos.y < gGroundHeight) {
                    Object_Kill(&this->obj, this->sfxSource);
                    if (gGroundSurface != SURFACE_WATER) {
                        this->obj.pos.y = gGroundHeight;
                        func_effect_8007D074(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 2.0f);
                    }
                }

                sp3C.x = this->vel.x;
                sp3C.y = this->vel.y;
                sp3C.z = this->vel.z;

                if (Object_CheckCollision(1000, &this->obj.pos, &sp3C, 2) != 0) {
                    func_effect_8007D10C(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 2.0f);
                    Object_Kill(&this->obj, this->sfxSource);
                }
            }
            break;
    }

    func_effect_8007A774(gPlayer, this, 50.0f);
}

void Effect_Effect398_Draw(Effect398* this) {
    switch (this->unk_44) {
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
            gSPDisplayList(gMasterDisp++, aOrbDL);
            break;
    }
}

void Effect_Effect394_Update(Effect394* this) {
    s16 temp_ft2;

    switch (this->unk_78) {
        case 0:
            break;

        case 1:
            this->unk_46--;
            break;

        case 10:
            this->unk_44--;
            if (this->unk_44 <= 0) {
                this->unk_44 = this->unk_46;
            }
            temp_ft2 = (((f32) this->unk_44 / (f32) this->unk_46) * 255.0f);
            this->unk_48 = temp_ft2;
            if (temp_ft2 > 255) {
                this->unk_48 = 255;
            }
            if (this->unk_48 < 32) {
                Object_Kill(&this->obj, this->sfxSource);
            }
            break;

        case 11:
            this->obj.rot.z += this->unk_60.z;
            this->scale2 += 0.07f;
            this->vel.y += 0.2f;
            this->unk_44 += this->unk_46;
            if (this->unk_44 < 10) {
                Object_Kill(&this->obj, this->sfxSource);
            }
            break;

        case 12:
            this->obj.rot.x += this->unk_60.x;
            this->obj.rot.y += this->unk_60.y;
            this->obj.rot.z += this->unk_60.z;
            if ((this->unk_44 == 0) && (this->obj.pos.y < gGroundHeight)) {
                Object_Kill(&this->obj, this->sfxSource);
            }
            if (this->unk_44 != 0) {
                this->unk_44--;
            }
            this->vel.y -= 4.0f;
            break;

        case 16:
            break;

        case 100:
            Effect_Effect365_Update(this);
            break;

        case 101:
            Effect_Effect362_Update(this);
            break;

        case 102:
            Effect_Effect347_Update(this);
            break;
    }
}

void Effect_Effect394_Draw(Effect394* this) {
    static s32 D_800D18E4 = 0;
    s32 i;
    s32 alpha;

    switch (this->unk_7A) {
        case 0:
            if (this->unk_44 != 64) {
                RCP_SetupDL(&gMasterDisp, this->unk_44);
            }
            gSPDisplayList(gMasterDisp++, this->unk_74);
            if (this->unk_44 != 64) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_64);
            }
            break;

        case 1:
            if (this->unk_48 == 0) {
                this->unk_48 = this->unk_46;
            }

            if (this->unk_44 != 64) {
                RCP_SetupDL(&gMasterDisp, this->unk_44);
            }

            alpha = (((f32) this->unk_46 / (f32) this->unk_48) * 255.0f);
            if (alpha > 255) {
                alpha = 255;
            }

            if (alpha < 32) {
                Object_Kill(&this->obj, this->sfxSource);
            } else {
                gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, alpha);
                gSPDisplayList(gMasterDisp++, this->unk_74);
            }

            if (this->unk_44 != 64) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_64);
            }
            break;

        case 10:
            RCP_SetupDL(&gMasterDisp, SETUPDL_65);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, this->unk_48);
            Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, this->scale2, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_TI_A000000);
            RCP_SetupDL(&gMasterDisp, SETUPDL_64);
            break;

        case 11:
            RCP_SetupDL(&gMasterDisp, SETUPDL_68);
            Graphics_SetScaleMtx(this->scale2);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 120, 60, 0, this->unk_44);
            gDPSetEnvColor(gMasterDisp++, 0, 0, 0, 0);
            gSPDisplayList(gMasterDisp++, D_1023750);
            RCP_SetupDL(&gMasterDisp, SETUPDL_64);
            break;

        case 12:
            Graphics_SetScaleMtx(this->scale2);
            RCP_SetupDL(&gMasterDisp, SETUPDL_23);
            gSPDisplayList(gMasterDisp++, D_VE1_9013C20);
            RCP_SetupDL(&gMasterDisp, SETUPDL_64);
            break;

        case 13:
            Graphics_SetScaleMtx(this->scale2);
            RCP_SetupDL(&gMasterDisp, SETUPDL_68);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, this->unk_44);
            gDPSetEnvColor(gMasterDisp++, 36, 45, 28, 0);
            gSPDisplayList(gMasterDisp++, D_1023750);
            RCP_SetupDL(&gMasterDisp, SETUPDL_64);
            break;

        case 14:
            Graphics_SetScaleMtx(this->scale2);
            RCP_SetupDL(&gMasterDisp, SETUPDL_68);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, this->unk_44);
            gDPSetEnvColor(gMasterDisp++, 255, 255, 255, 0);
            gSPDisplayList(gMasterDisp++, D_1023750);
            RCP_SetupDL(&gMasterDisp, SETUPDL_64);
            break;

        case 15:
            Graphics_SetScaleMtx(this->scale2);
            RCP_SetupDL(&gMasterDisp, SETUPDL_68);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, this->unk_4A);
            gDPSetEnvColor(gMasterDisp++, 36, 45, 28, 0);
            gSPDisplayList(gMasterDisp++, D_1023750);
            RCP_SetupDL(&gMasterDisp, SETUPDL_64);
            break;

        case 16:
            Graphics_SetScaleMtx(this->scale2);
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
            this->obj.rot.z += 1.0f;
            break;

        case 17:
            //! DEBUG: some code used for debugging with the 4th controller
            if ((gControllerPress[3].button & U_JPAD) && (D_800D18E4 > 0)) {
                D_800D18E4--;
            }
            if ((gControllerPress[3].button & D_JPAD) && (D_800D18E4 < 12)) {
                D_800D18E4++;
            }

            if (((this->index + gGameFrameCount) % 2) == 0) {
                gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
            } else {
                gDPSetPrimColor(gMasterDisp++, 0, 0, 96, 96, 255, 255);
            }

            Graphics_SetScaleMtx(this->scale2);

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
            Graphics_SetScaleMtx(this->scale2);
            gSPDisplayList(gMasterDisp++, aOrbDL);
            break;
    }
}

void func_effect_800815DC(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        if (((gEffects[i].obj.id == OBJ_EFFECT_366) ||
             ((gEffects[i].obj.id == OBJ_EFFECT_395) && (gEffects[i].state == 1)) ||
             (gEffects[i].obj.id == OBJ_EFFECT_364) || (gEffects[i].obj.id == OBJ_EFFECT_346)) &&
            gEffects[i].obj.status == OBJ_ACTIVE) {
            gEffects[i].obj.status = OBJ_FREE;
            break;
        }
    }
}

void func_effect_8008165C(Effect395* this, f32 xPos, f32 yPos, f32 zPos, f32 scale2, s32 arg5) {
    Effect_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_EFFECT_395;

    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;

    this->scale2 = scale2;
    this->state = arg5;
    Object_SetInfo(&this->info, this->obj.id);
    this->timer_50 = 300;

    switch (this->state) {
        case 4:
            this->unk_4A = 255;
            this->unk_46 = 1;
            break;

        case 5:
            this->vel.x = RAND_FLOAT_CENTERED(20.0f);
            this->vel.y = RAND_FLOAT(20.0f) + 30.0f;
            this->vel.z = RAND_FLOAT(30.0f);

            this->unk_46 = 5;
            this->unk_44 = RAND_FLOAT_CENTERED(20.0f) * 1.5f;
            this->info.unk_14 = 0;
            this->unk_4A = 255;
            break;

        case 6:
            this->unk_4A = 255;
            this->unk_46 = 10;
            break;

        case 7:
            this->vel.y = RAND_FLOAT(7.0f) + 7.0f;
            this->vel.x = RAND_FLOAT_CENTERED(10.0f);
            this->vel.z = RAND_FLOAT_CENTERED(10.0f);

            this->scale2 = (RAND_FLOAT(0.8f) + 0.3f) * scale2;
            this->timer_50 = RAND_INT(50.0f) + 70;
            this->obj.rot.x = RAND_FLOAT(360.0f);

            this->unk_60.x = RAND_FLOAT_CENTERED(30.0f);
            this->unk_60.y = RAND_FLOAT_CENTERED(30.0f);
            this->unk_60.z = RAND_FLOAT_CENTERED(30.0f);

            this->info.unk_14 = 0;
            break;

        case 9:
            this->obj.pos.x += RAND_FLOAT_CENTERED(600.0f);
            this->obj.pos.y += RAND_FLOAT_CENTERED(600.0f);
            this->obj.pos.z += RAND_FLOAT_CENTERED(300.0f) + 300.0f;
            this->scale1 = 0.0f;
            this->scale2 = RAND_FLOAT(1.0f) + 1.0f;
            break;

        case 10:
            this->timer_50 = 10;
            AUDIO_PLAY_SFX(NA_SE_EN_A6BOSS_BEAM, this->sfxSource, 4);
            break;

        case 11:
            this->scale1 = 255.0f;
            this->vel.y = 20.0f;
            if (this->scale2 > 10.0f) {
                this->scale2 = 10.0f;
            }
            break;

        case 12:
            this->scale1 = scale2;
            this->scale2 = 1.0f;
            this->timer_50 = 50;
            this->unk_44 = 100;

            this->obj.pos.x = xPos;
            this->obj.pos.y = yPos;
            this->obj.pos.z = zPos;

            AUDIO_PLAY_SFX(NA_SE_EN_STAR_EXPLOSION, this->sfxSource, 4);
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

f32 D_800D18E8 = 0.0f;
f32 D_800D18EC = 0.0f;

void Effect_Effect395_Update(Effect395* this) {
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

    velocity.x = this->vel.x;
    velocity.y = this->vel.y;
    velocity.z = this->vel.z;

    //! FAKE: Probably some debug stuff printing different messages depending on what state is.
    if ((this->state != 0) && (this->state != 6) && (this->state != 7) && (this->state != 11)) {
        if (gCurrentLevel) {}
        PRINTF("ＺＯ＿ＭＯＶＥ ＨＥＬＰ %d\n");
    }
    if ((this->state != 1) && (this->state != 2) && (this->state != 4) && (this->state != 5) && (this->state != 8) &&
        (this->state != 9)) {
        if (gCurrentLevel) {}
        PRINTF("ＡＣ＿ＭＯＶＥ ＨＥＬＰ %d\n");
    }

    switch (this->state) {
        case 0:
            if (this->timer_50 == 0) {
                Object_Kill(&this->obj, this->sfxSource);
                break;
            }

            if ((gGameFrameCount % 2) == 0) {
                Effect_Effect389_Spawn(RAND_FLOAT_CENTERED(50.0f) + this->obj.pos.x,
                                       RAND_FLOAT_CENTERED(50.0f) + this->obj.pos.y,
                                       RAND_FLOAT_CENTERED(50.0f) + this->obj.pos.z, this->vel.x, this->vel.y,
                                       this->vel.z, RAND_FLOAT(0.05f) + 0.05f, 0);
            }

            if (Object_CheckCollision(this->index, &this->obj.pos, &velocity, 1) != 0) {
                Effect_Effect384_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 3.0f, 7);
                Object_Kill(&this->obj, this->sfxSource);
            }
            sp84 = 50.0f;
            break;

        case 1:
            if (this->timer_50 == 0) {
                Object_Kill(&this->obj, this->sfxSource);
                break;
            }

            this->unk_60.z += 10.0f;
            this->vel.z = 5.0f;

            if ((gGameFrameCount % 8) == 0) {
                this->unk_44++;
                this->unk_44 &= 1;
            }

            if (this->unk_44 == 0) {
                Math_SmoothStepToF(&this->scale2, 0.2f, 0.01f, 0.02f, 0.0f);
            } else {
                Math_SmoothStepToF(&this->scale2, 0.5f, 0.01f, 0.02f, 0.0f);
            }

            if (Object_CheckCollision(this->index, &this->obj.pos, &velocity, 1) != 0) {
                Object_Kill(&this->obj, this->sfxSource);
                func_effect_8007D0E0(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 1.0f);
            }
            break;

        case 2:
            if (this->timer_50 == 0) {
                Object_Kill(&this->obj, this->sfxSource);
                break;
            }

            switch (this->unk_44) {
                case 1:
                case 2:
                    break;

                case 0:
                    Math_SmoothStepToF(&this->scale2, 1.0f, 0.1f, 5.0f, 0.0001f);
                    if (this->scale2 >= 1.0f) {
                        this->unk_44++;
                    }
                    break;

                case 3:
                    Math_SmoothStepToF(&this->scale2, 0.0f, 0.1f, 10.0f, 0.0001f);
                    if (this->scale2 < 0.3f) {
                        Object_Kill(&this->obj, this->sfxSource);
                    }
                    break;
            }

            if ((gGameFrameCount % 4) == 0) {
                Effect_Effect390_Spawn((RAND_FLOAT_CENTERED(this->scale2) * 50.0f) + this->obj.pos.x,
                                       (RAND_FLOAT_CENTERED(this->scale2) * 50.0f) + this->obj.pos.y,
                                       (RAND_FLOAT_CENTERED(this->scale2) * 50.0f) + this->obj.pos.z, this->vel.x,
                                       this->vel.y, this->vel.z, RAND_FLOAT(0.03f) + 0.05f, 10);
            }
            if (Object_CheckCollision(this->index, &this->obj.pos, &velocity, 1) != 0) {
                Effect_Effect384_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 3.0f, 7);
                Object_Kill(&this->obj, this->sfxSource);
            }
            sp84 = 50.0f;
            break;

        case 3:
            this->info.unk_19 = 2;
            if (this->unk_44 != 0) {
                Object_Kill(&this->obj, this->sfxSource);
                func_effect_8007D0E0(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 5.0f);
            } else if (fabsf(gPlayer[0].trueZpos - this->obj.pos.z) < 1000.0f) {
                ActorEvent_SpawnEffect347(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 15.0f);
                Object_Kill(&this->obj, this->sfxSource);
            }
            sp84 = 50.0f;
            break;

        case 4:
            this->scale2 += 0.07f;
            this->unk_4A -= this->unk_46;
            this->obj.rot.z += 3.0f;
            this->vel.y += 0.2f;
            if (this->unk_4A < 0) {
                Object_Kill(&this->obj, this->sfxSource);
            }
            break;

        case 5:
            func_effect_80081A8C(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 5.0f, 6);
            this->unk_4A -= this->unk_46;
            this->obj.rot.x += this->unk_44;
            this->obj.rot.y += this->unk_44;
            this->obj.rot.z += this->unk_44;
            this->vel.y -= 2.0f;
            if ((this->unk_4A < 0) || (this->timer_50 == 0)) {
                Object_Kill(&this->obj, this->sfxSource);
            }
            break;

        case 6:
            this->unk_4A -= this->unk_46;
            Math_SmoothStepToF(&this->scale2, 0.0f, 0.1f, 1.0f, 0.00001f);
            if ((this->unk_4A < 0) || (this->timer_50 == 0)) {
                Object_Kill(&this->obj, this->sfxSource);
            }
            break;

        case 7:
            switch (gCurrentLevel) {
                case LEVEL_AQUAS:
                    if ((gGameFrameCount % 4) == 0) {
                        func_effect_80081A8C(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, this->scale2, 6);
                    }
                    this->obj.rot.x += this->unk_60.x;
                    this->obj.rot.y += this->unk_60.y;
                    this->obj.rot.z += this->unk_60.z;
                    this->vel.y -= 0.5f;
                    if ((this->timer_50 == 0) || (this->obj.pos.y < gGroundHeight)) {
                        Object_Kill(&this->obj, this->sfxSource);
                    }
                    break;

                case LEVEL_ZONESS:
                    if ((gGameFrameCount % 4) == 0) {
                        // clang-format off
                        func_effect_80081A8C(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, this->scale2 * 3.0f, 6);
                        // clang-format on
                    }

                    this->obj.rot.x += this->unk_60.x;
                    this->obj.rot.y += this->unk_60.y;
                    this->obj.rot.z += this->unk_60.z;

                    this->vel.y -= 1.0f;

                    if ((Play_CheckDynaFloorCollision(&posYOut, &unusedOut, this->obj.pos.x, this->obj.pos.y,
                                                      this->obj.pos.z)) ||
                        (this->timer_50 == 0)) {
                        Effect_Effect381_Spawn(this->obj.pos.x, posYOut, this->obj.pos.z, this->scale2);
                        Object_Kill(&this->obj, this->sfxSource);
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

            if (this->unk_44 > 0) {
                velocity.z = 2000.0f;
            }

            Matrix_MultVec3fNoTranslate(gCalcMatrix, &velocity, &velocityDest);

            this->obj.pos.x = gBosses[0].obj.pos.x + velocityDest.x;
            this->obj.pos.y = gBosses[0].obj.pos.y + velocityDest.y;
            this->obj.pos.z = gBosses[0].obj.pos.z + velocityDest.z;

            switch (this->unk_44) {
                case 0:
                    func_effect_80081BEC(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 1.0f, 9);
                    Math_SmoothStepToF(&this->scale2, 6.0f, 0.01f, 0.05f, 0.00001f);
                    if (this->scale2 >= 5.0f) {
                        gEffects[ARRAY_COUNT(gEffects) - 1].obj.status =
                            gEffects[ARRAY_COUNT(gEffects) - 2].obj.status = OBJ_FREE;
                        func_effect_80081BEC(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 1.0f, 10);
                        gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
                        gFillScreenAlpha = gFillScreenAlphaTarget = 255;
                        gFillScreenAlphaTarget = 0;
                        gFillScreenAlphaStep = 25;
                        this->timer_50 = 10;
                        D_800D18EC = 0.0f;
                        D_800D18E8 = 0.0f;
                        gBosses[0].timer_050 = 150;
                        gBosses[0].state = 6;
                        this->unk_44++;
                    }
                    break;

                case 1:
                    Math_SmoothStepToF(&this->scale2, 8.0f, 0.1f, 1.0f, 0.00001f);
                    if (this->timer_50 == 0) {
                        if (gFillScreenAlpha != 0) {
                            gFillScreenRed = gFillScreenGreen = gFillScreenBlue = gFillScreenAlpha = 0;
                        }
                        this->timer_50 = gBosses[0].timer_050;
                        this->unk_44++;
                    }
                    break;

                case 2:
                    if (this->timer_50 == 0) {
                        Math_SmoothStepToF(&this->scale2, 0.0f, 1.0f, 10.0f, 0.00001f);
                        if (this->scale2 == 0.0f) {
                            Object_Kill(&this->obj, this->sfxSource);
                        }
                    } else {
                        Math_SmoothStepToF(&this->scale2, 8.0f, 0.1f, 1.0f, 0.00001f);
                    }
                    break;
            }
            break;

        case 9:
            posXDiff = gBosses[0].obj.pos.x - this->obj.pos.x;
            posYDiff = gBosses[0].obj.pos.y - this->obj.pos.y;
            posZDiff = gBosses[0].obj.pos.z - this->obj.pos.z;

            yRotDeg = Math_RadToDeg(Math_Atan2F(posXDiff, posZDiff));
            xRotDeg = Math_RadToDeg(-Math_Atan2F(posYDiff, sqrtf(SQ(posXDiff) + SQ(posZDiff))));

            Matrix_RotateY(gCalcMatrix, M_DTOR * yRotDeg, MTXF_NEW);
            Matrix_RotateX(gCalcMatrix, M_DTOR * xRotDeg, MTXF_APPLY);

            velocity.x = velocity.y = 0.0f;
            velocity.z = 20.0f;

            Matrix_MultVec3fNoTranslate(gCalcMatrix, &velocity, &velocityDest);

            this->vel.x = velocityDest.x;
            this->vel.y = velocityDest.y;
            this->vel.z = -50.0f;

            this->unk_44++;
            Math_SmoothStepToF(&this->scale1, 255.0f, 1.0f, 20.0f, 0.0f);
            Math_SmoothStepToF(&this->vel.z, -70.0f, 0.01f, 0.1f, 0.0f);
            Math_SmoothStepToF(&this->scale2, 0.0f, 0.1f, 0.5f, 0.00001f);
            if (this->scale2 == 0.0f) {
                Object_Kill(&this->obj, this->sfxSource);
            }
            break;

        case 10:
            switch (this->unk_44) {
                case 0:
                    D_ctx_801779A8[0] = 50.0f;
                    if (this->unk_46 == 10) {
                        gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
                        if (CVarGetInteger("gDisableGorgonFlash", 0) == 0){
                            gFillScreenAlpha = gFillScreenAlphaTarget = 255;
                        }
                        gFillScreenAlphaTarget = 0;
                        gFillScreenAlphaStep = 25;
                        gCameraShake = 50;
                    }
                    if (this->unk_46 == 0) {
                        gFillScreenRed = gFillScreenGreen = gFillScreenBlue = gFillScreenAlpha = 0;
                        this->unk_46 = 50;
                    }
                    if (this->unk_46 != 0) {
                        this->unk_46--;
                    }
                    if (((gGameFrameCount % 16) == 0) && (this->timer_50 == 0)) {
                        D_800D18EC =
                            RAD_TO_DEG(Math_Atan2F(gPlayer[0].cam.eye.x - gBosses[0].obj.pos.x,
                                                   gPlayer[0].cam.eye.z - (gBosses[0].obj.pos.z + gPathProgress)));

                        D_800D18E8 = RAD_TO_DEG(
                            -Math_Atan2F(gPlayer[0].cam.eye.y - gBosses[0].obj.pos.y,
                                         sqrtf(SQ(gPlayer[0].cam.eye.z - (gBosses[0].obj.pos.z + gPathProgress)) +
                                               SQ(gPlayer[0].cam.eye.x - gBosses[0].obj.pos.x))));
                    }
                    if (gBosses[0].timer_050 == 0) {
                        gBosses[0].swork[39] = this->index;
                        this->unk_44 = 1;
                    }
                    break;

                case 1:
                    Math_SmoothStepToF(D_ctx_801779A8, 20.0f, 1.0f, 5.0f, 0.0f);
                    break;
            }

            this->info.unk_14 = 0;

            Math_SmoothStepToAngle(&gBosses[0].obj.rot.x, D_800D18E8, 0.1f, 1.0f, 0.00001f);
            Math_SmoothStepToAngle(&gBosses[0].obj.rot.y, D_800D18EC, 0.1f, 1.0f, 0.00001f);

            this->obj.rot.x = gBosses[0].obj.rot.x;
            this->obj.rot.y = gBosses[0].obj.rot.y;
            this->obj.rot.z += 30.0f;

            Matrix_RotateY(gCalcMatrix, gBosses[0].obj.rot.y * M_DTOR, MTXF_NEW);
            Matrix_RotateX(gCalcMatrix, gBosses[0].obj.rot.x * M_DTOR, MTXF_APPLY);

            velocity.x = velocity.y = 0.0f;
            velocity.z = 250.0f;

            Matrix_MultVec3fNoTranslate(gCalcMatrix, &velocity, &velocityDest);

            this->obj.pos.x = gBosses[0].obj.pos.x + velocityDest.x;
            this->obj.pos.y = gBosses[0].obj.pos.y + velocityDest.y;
            this->obj.pos.z = gBosses[0].obj.pos.z + velocityDest.z;

            if (this->unk_44 == 0) {
                Math_SmoothStepToF(&this->unk_60.x, 5.0f, 0.1f, 1.0f, 0.00001f);
                Math_SmoothStepToF(&this->unk_60.y, 5.0f, 0.1f, 1.0f, 0.00001f);
                Math_SmoothStepToF(&this->unk_60.z, 50.0f, 1.0f, 2.0f, 0.00001f);
            }

            velocity.x = velocity.y = 0.0f;
            velocity.z = fabsf(gPlayer[0].trueZpos - this->obj.pos.z);

            Matrix_MultVec3fNoTranslate(gCalcMatrix, &velocity, &velocityDest);

            if ((((this->timer_50 == 0) &&
                  (fabsf(gPlayer[0].pos.x - (this->obj.pos.x + velocityDest.x)) <= (this->unk_60.x * 50.0f))) &&
                 (fabsf(gPlayer[0].pos.y - (this->obj.pos.y + velocityDest.y)) <= (this->unk_60.y * 50.0f))) &&
                (gPlayer[0].mercyTimer == 0)) {
                Player_ApplyDamage(gPlayer, 0, 40);
            }
            break;

        case 11:
            this->obj.rot.z += 20.0f;
            this->vel.y -= 2.0f;
            if (this->vel.y < (-20.0f)) {
                this->vel.y = -20.0f;
            }

            Math_SmoothStepToF(&this->scale1, 0.0f, 0.1f, 100.0f, 0.00001f);

            if ((this->scale1 < 1.0f) || (this->timer_50 == 0)) {
                Object_Kill(&this->obj, this->sfxSource);
            }
            break;

        case 12:
            Effect_Effect383_Update(this);
            break;
    }

    if ((this->state == 2) && (this->unk_44 == 2)) {
        Effect_Effect353_354_Update(this);
    }
    if ((this->state < 4) && (this->state != 1)) {
        func_effect_8007A774(gPlayer, this, sp84);
    }
}

void Effect_Effect395_Draw(Effect395* this) {
    //! FAKE: Probably some debug stuff printing different messages depending on what unk_4E is.
    if ((this->state != 0) && (this->state != 6)) {
        if (this->unk_4A && this->unk_4A) {}
        PRINTF("ＺＯ＿ＤＩＳＰ ＨＥＬＰ %d\n");
    }
    if ((this->state != 1) && (this->state != 2) && (this->state != 4) && (this->state != 5) && (this->state != 7)) {
        if (this->unk_4A && !this->scale2) {}
        PRINTF("ＡＣ＿ＤＩＳＰ ＨＥＬＰ %d\n");
    }

    // @port: Tag the transform.
    FrameInterpolation_RecordOpenChild(this, this->state);

    switch (this->state) {
        case 0:
            RCP_SetupDL(&gMasterDisp, SETUPDL_49);
            Matrix_Scale(gGfxMatrix, 0.7f, 0.7f, 1.0f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
            gDPSetEnvColor(gMasterDisp++, 32, 32, 255, 255);
            gSPDisplayList(gMasterDisp++, aOrbDL);
            break;

        case 1:
            RCP_SetupDL(&gMasterDisp, SETUPDL_41);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
            Graphics_SetScaleMtx(this->scale2);
            gSPDisplayList(gMasterDisp++, aStarDL);
            break;

        case 2:
            RCP_SetupDL(&gMasterDisp, SETUPDL_49);
            Matrix_Scale(gGfxMatrix, this->scale2, this->scale2, this->scale2, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
            gDPSetEnvColor(gMasterDisp++, 32, 32, 255, 255);
            gSPDisplayList(gMasterDisp++, aOrbDL);
            break;

        case 3:
            RCP_SetupDL_60(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
            gSPDisplayList(gMasterDisp++, aA6SpaceMineDL);
            break;

        case 4:
            Graphics_SetScaleMtx(this->scale2);
            RCP_SetupDL(&gMasterDisp, SETUPDL_68);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 0, 0, 0, this->unk_4A);
            gDPSetEnvColor(gMasterDisp++, 0, 0, 0, 0);
            gSPDisplayList(gMasterDisp++, D_1023750);
            break;

        case 5:
        case 7:
            Graphics_SetScaleMtx(this->scale2);
            RCP_SetupDL(&gMasterDisp, SETUPDL_60);
            if (gCurrentLevel == LEVEL_AQUAS) {
                gSPDisplayList(gMasterDisp++, D_AQ_600A220);
            }
            if (gCurrentLevel == LEVEL_ZONESS) {
                gSPDisplayList(gMasterDisp++, D_ZO_6016880);
            }
            break;

        case 6:
            Graphics_SetScaleMtx(this->scale2);
            if (gCurrentLevel == LEVEL_ZONESS) {
                Graphics_SetScaleMtx(this->scale2);
            }
            RCP_SetupDL(&gMasterDisp, SETUPDL_64);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 0, 255, 0, this->unk_4A);
            gSPDisplayList(gMasterDisp++, D_1023750);
            break;

        case 8:
            RCP_SetupDL(&gMasterDisp, SETUPDL_49);
            Matrix_Scale(gGfxMatrix, this->scale2, this->scale2, this->scale2, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
            gDPSetEnvColor(gMasterDisp++, 255, 0, 128, 255);
            gSPDisplayList(gMasterDisp++, aOrbDL);
            break;

        case 9:
            RCP_SetupDL(&gMasterDisp, SETUPDL_49);
            Matrix_Scale(gGfxMatrix, this->scale2, this->scale2, this->scale2, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, this->scale1);
            gDPSetEnvColor(gMasterDisp++, 255, 255, 128, 255);
            gSPDisplayList(gMasterDisp++, aOrbDL);
            break;

        case 10:
            if (gPlayState != PLAY_PAUSE) {
                Lib_Texture_Scroll(D_A6_6012840, 16, 16, 0);
            }
            RCP_SetupDL(&gMasterDisp, SETUPDL_53);
            Matrix_Scale(gGfxMatrix, this->unk_60.x, this->unk_60.y, this->unk_60.z, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
            gSPDisplayList(gMasterDisp++, D_A6_6012550);
            break;

        case 11:
            RCP_SetupDL(&gMasterDisp, SETUPDL_67);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 111, 111, 111, (s32) this->scale1);
            gDPSetEnvColor(gMasterDisp++, 255, 255, 255, 255);
            Graphics_SetScaleMtx(this->scale2);
            gSPDisplayList(gMasterDisp++, aOrbDL);
            break;

        case 12:
            Effect_Effect383_Draw(this);
            break;
    }

    RCP_SetupDL(&gMasterDisp, SETUPDL_64);

    // @port Pop the transform id.
    FrameInterpolation_RecordCloseChild();
}

void Effect_Effect391_Setup(Effect391* this, f32 xPos, f32 yPos, f32 zPos, f32 arg4, f32 scale) {
    Effect_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_EFFECT_391;

    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;

    this->unk_60.x = scale * 0.8f;
    this->unk_60.y = 1.2f;

    if (arg4 != 0.0f) {
        this->unk_60.y = arg4;
    }
    this->unk_44 = 230;
    this->scale1 = scale;
    this->scale2 = 0.1f;
    Object_SetInfo(&this->info, this->obj.id);
}

void Effect_Effect391_Spawn(f32 xPos, f32 yPos, f32 zPos, f32 arg3, f32 scale) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Effect_Effect391_Setup(&gEffects[i], xPos, yPos, zPos, arg3, scale);
            break;
        }
    }
}

void Effect_Effect391_Update(Effect391* this) {
    s32 pad[2];
    f32 var_fv1;
    s32 var_s2;
    s32 i;

    switch (this->state) {
        case 0:
            if (this->unk_60.y == 1.2f) {
                Math_SmoothStepToF(&this->scale2, this->scale1, 0.5f, this->scale1, 0.01f);
            } else {
                Math_SmoothStepToF(&this->scale2, this->scale1, 1.0f, this->scale1 * 0.1f, 0.01f);
            }

            if (this->scale2 > (this->scale1 * 0.7f)) {
                Math_SmoothStepToF(&this->unk_60.x, this->scale2 * 1.3f, 0.1f, 0.5f, 0.0001f);
            }

            if (this->scale2 == this->scale1) {
                var_s2 = this->scale2 * 5.0f;
                if (var_s2 < 5) {
                    var_s2 = 5;
                }
                if (var_s2 > 10) {
                    var_s2 = 10;
                }
                var_fv1 = this->unk_60.y * 300.0f;
                if (this->unk_60.y == 1.2f) {
                    var_fv1 = this->unk_60.y * 100.0f;
                }
                for (i = 0; i < var_s2; i++) {
                    func_effect_80081BEC(this->obj.pos.x + RAND_FLOAT_CENTERED(this->scale2 * 200.0f),
                                         this->obj.pos.y + var_fv1 + RAND_FLOAT_CENTERED(this->scale2 * 100.0f),
                                         this->obj.pos.z + RAND_FLOAT_CENTERED(this->scale2 * 200.0f),
                                         0.3f - RAND_FLOAT_CENTERED(0.2f), 11);
                }
                this->state++;
            }
            break;

        case 1:
            this->vel.y -= 4.0f;
            Math_SmoothStepToF(&this->scale2, 0.0f, 0.01f, 0.1f, 0.0001f);
            Math_SmoothStepToF(&this->unk_60.x, this->scale2 * 1.3f, 0.1f, 0.5f, 0.0001f);
            this->unk_44 -= 35;
            if (this->unk_44 < 0) {
                Object_Kill(&this->obj, this->sfxSource);
            }
            break;
    }

    this->obj.rot.y = RAD_TO_DEG(
        Math_Atan2F(gPlayer[0].cam.eye.x - this->obj.pos.x, gPlayer[0].cam.eye.z - (this->obj.pos.z + gPathProgress)));
}

void Effect_Effect391_Draw(Effect391* this) {
    RCP_SetupDL_49();
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, this->unk_44);
    gDPSetEnvColor(gMasterDisp++, 36, 45, 28, 255);
    Matrix_Scale(gGfxMatrix, this->unk_60.x, this->scale2 * this->unk_60.y, this->scale2, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_ZO_601BAD0);
    RCP_SetupDL(&gMasterDisp, SETUPDL_64);
}

void Effect_Effect399_Setup(Effect399* this, f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 arg7,
                            s32 arg8) {
    Effect_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_EFFECT_399;
    this->obj.pos.x = xPos;
    this->unk_60.x = xPos;
    this->unk_60.y = yPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;

    this->vel.x = xVel;
    this->vel.y = yVel;
    this->vel.z = zVel;

    this->unk_60.z = arg7;
    this->scale2 = 1.6f;
    this->scale1 = 0.0f;
    this->timer_50 = 100;
    this->unk_44 = arg8;
    Object_SetInfo(&this->info, this->obj.id);
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
                Effect_Effect399_Setup(&gEffects[j], xPos, yPos, zPos, dest.x, dest.y, dest.z, i * 60.0f, i);
                if (i == 0) {
                    AUDIO_PLAY_SFX(NA_SE_EN_MARBLE_BEAM, gEffects[j].sfxSource, 4);
                }
                break;
            }
        }
    }
}

void Effect_Effect399_Update(Effect399* this) {
    Vec3f src;
    Vec3f dest;

    if (this->timer_50 == 0) {
        Object_Kill(&this->obj, this->sfxSource);
        return;
    }

    this->obj.rot.y = RAD_TO_DEG(-gPlayer[0].camYaw);
    this->obj.rot.x = RAD_TO_DEG(gPlayer[0].camPitch);
    this->obj.rot.z += 20.0f;

    Matrix_RotateZ(gCalcMatrix, this->unk_60.z * M_DTOR, MTXF_NEW);
    Matrix_RotateZ(gCalcMatrix, this->unk_46 * M_DTOR, MTXF_APPLY);

    src.x = 0.0f;
    src.y = this->scale1;
    src.z = 0.0f;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

    this->unk_60.x += this->vel.x;
    this->unk_60.y += this->vel.y;

    this->obj.pos.x = this->unk_60.x + dest.x;
    this->obj.pos.y = this->unk_60.y + dest.y;

    this->unk_48 += 2;
    if (this->unk_48 > 20) {
        this->unk_48 = 20;
    }
    this->unk_46 += this->unk_48;

    Math_SmoothStepToF(&this->scale1, 350.0f, 1.0f, 20.0f, 0.00001f);

    if ((this->scale1 >= 349.0f) && (this->timer_50 > 50)) {
        this->timer_50 = 50;
    }
    func_effect_8007A774(gPlayer, this, 100.0f);
}

// RGB Values. Used like an array of [8][3], but only matches this way.
s32 D_800D18F0[] = { 32, 32, 255, 0, 255, 0, 0, 0, 0, 255, 0, 0, 0, 0, 0, 0, 0, 255, 255, 0, 255, 0, 255, 0 };

// Alpha values
s32 D_800D1950[] = { 255, 210, 180, 120, 70, 30, 0, 0 };

void Effect_Effect399_Draw(Effect399* this) {
    s32 tmp;

    if (gCurrentLevel != LEVEL_AQUAS) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_49);
        Matrix_Scale(gGfxMatrix, this->scale2, this->scale2, this->scale2, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
        tmp = this->unk_44 * 4;
        gDPSetEnvColor(gMasterDisp++, D_800D18F0[tmp + 0], D_800D18F0[tmp + 1], D_800D18F0[tmp + 2], 255);
    } else {
        RCP_SetupDL(&gMasterDisp, SETUPDL_49);
        Matrix_Scale(gGfxMatrix, this->scale2, this->scale2, this->scale2, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, D_800D1950[this->unk_44]);
        gDPSetEnvColor(gMasterDisp++, 255, 0, 0, 255);
    }
    gSPDisplayList(gMasterDisp++, aOrbDL);
    RCP_SetupDL(&gMasterDisp, SETUPDL_64);
}
