#include "prevent_bss_reordering.h"
#include "global.h"
#include "fox_map.h"
#include "assets/ast_corneria.h"
#include "assets/ast_training.h"
#include "assets/ast_sector_x.h"
#include "assets/ast_sector_y.h"
#include "assets/ast_sector_z.h"
#include "assets/ast_aquas.h"
#include "assets/ast_bolse.h"
#include "assets/ast_meteo.h"
#include "assets/ast_macbeth.h"
#include "assets/ast_katina.h"
#include "assets/ast_venom_1.h"
#include "assets/ast_venom_2.h"
#include "assets/ast_fortuna.h"
#include "assets/ast_titania.h"
#include "assets/ast_andross.h"
#include "assets/ast_solar.h"
#include "assets/ast_arwing.h"
#include "assets/ast_versus.h"
#include "assets/ast_area_6.h"
#include "assets/ast_zoness.h"

UNK_TYPE D_800D2F50 = 0; // unused
s32 sOverheadCam = 0;
f32 sOverheadCamDist = 0.0f;
f32 sMusicVolume = 0.0f;
f32 sVoiceVolume = 0.0f;
f32 sSfxVolume = 0.0f;
u8 gVenomHardClear = 0;
u8 sSaveSlotFromLevel[20] = {
    PLANET_CORNERIA, PLANET_METEO,      PLANET_SECTOR_X, PLANET_AREA_6,   PLANET_AREA_6,
    PLANET_SECTOR_Y, SAVE_SLOT_VENOM_1, SAVE_SLOT_SOLAR, PLANET_ZONESS,   SAVE_SLOT_VENOM_1,
    PLANET_CORNERIA, PLANET_MACBETH,    PLANET_TITANIA,  PLANET_AQUAS,    PLANET_FORTUNA,
    PLANET_METEO,    PLANET_KATINA,     PLANET_BOLSE,    PLANET_SECTOR_Z, SAVE_SLOT_VENOM_2,
};

u8 gSavedZoSearchlightStatus;
f32 gArwingSpeed;
s32 D_play_80161A58; // unused
s32 D_play_80161A5C; // saved hit count for venom -> andross
u16 gScreenFlashTimer;
u16 gDropHitCountItem;
s32 sPlayWingSplashSfx;
Environment* sEnvironment;

#define MEM_ARRAY_ALLOCATE(arr, count) ((arr) = Memory_Allocate((count) * sizeof(*(arr))))

bool Play_CheckMedalStatus(u16 hitCount) {
    if ((gTeamShields[TEAM_ID_SLIPPY] > 0) && (gTeamShields[TEAM_ID_PEPPY] > 0) && (gTeamShields[TEAM_ID_FALCO] > 0) &&
        (gHitCount >= hitCount)) {
        return true;
    } else {
        return false;
    }
}

// This sets a variable related to SFX volume to 0, but that variable is never read from
void Play_dummy_MuteSfx(void) {
    sSfxVolume = 0.0f;
}

s32 Play_GetMaxShields(void) {
    if (gGoldRingCount[0] >= 3) {
        return 383;
    }
    return 255;
}

void Play_UpdateDynaFloor(void) {
    Vec3f spC4;
    Vec3f spB8;
    Vtx* spB4;
    u16* spB0;
    s32 i;
    s32 spA8;
    f32* var_s3;
    f32* var_s5;
    f32* var_s4;
    f32* var_s0;
    f32* var_s1;
    f32 sp90;
    f32 sp8C;
    f32 sp88;
    f32 sp84;

    gDynaFloorTimer++;
    switch (gCurrentLevel) {
        case LEVEL_SOLAR:
            if ((gGameFrameCount % 2) != 0) {
                spB4 = LOAD_ASSET(D_SO_6001C50);
            } else {
                spB4 = LOAD_ASSET(D_SO_6004500);
            }
            spB0 = LOAD_ASSET(D_SO_6022760);
            spA8 = 16 - 1;
            sp90 = 70.0f;
            sp8C = 0.1f;
            sp88 = 2.2f;
            sp84 = 0.5f;
            break;
        case LEVEL_ZONESS:
            if ((gGameFrameCount % 2) != 0) {
                spB4 = LOAD_ASSET(D_ZO_6009ED0);
            } else {
                spB4 = LOAD_ASSET(D_ZO_600C780);
            }
            spB0 = LOAD_ASSET(D_ZO_602AC50);
            spA8 = 8 - 1;
            sp90 = 40.0f;
            sp8C = 0.2f;
            sp88 = 1.0f;
            sp84 = 2.0f;
            break;
    }
    var_s3 = D_ctx_801782CC;
    var_s5 = D_ctx_801782D4;
    var_s4 = D_ctx_801782DC;
    var_s0 = D_ctx_801782E4;
    var_s1 = D_ctx_801782EC;
    for (i = 0; i < 17 * 17; i++, var_s3++, var_s5++, var_s4++, var_s0++, var_s1++, spB0++) {
        Math_SmoothStepToF(var_s3, *var_s5, sp8C, *var_s4, 0.0f);
        Math_SmoothStepToF(var_s4, 100.0f, 1.0f, sp84, 0.0f);
        if ((gDynaFloorTimer & spA8) == (i & spA8)) {
            *var_s5 = RAND_FLOAT(sp90);
            *var_s4 = 0.0f;
        }
        *var_s0 += *var_s1;
        *var_s1 -= 0.5f;
        if (*var_s0 < 0.0f) {
            *var_s1 = *var_s0 = 0.0f;
        }
        spB4[*spB0].n.ob[1] = (s16) *var_s3 + (s16) *var_s0;
        Matrix_RotateZ(gCalcMatrix, *var_s3 * sp88 * M_DTOR, MTXF_NEW);
        spC4.x = 120.0f;
        spC4.y = 0.0f;
        spC4.z = 0.0f;
        Matrix_MultVec3fNoTranslate(gCalcMatrix, &spC4, &spB8);
        spB4[*spB0].n.n[0] = spB8.x;
        spB4[*spB0].n.n[1] = spB8.y;
        spB4[*spB0].n.n[2] = spB8.z;
    }
}

void Player_WingEffects(Player* player) {
    if ((gCurrentLevel == LEVEL_VENOM_ANDROSS) && (gBosses[0].obj.status == OBJ_ACTIVE) && (gBosses[0].state == 17)) {
        player->xRock = SIN_DEG(player->rockPhase * 0.7f) * 0.5f;
        player->bobPhase += 13.0f;
        player->rockPhase += 20.0f;
        player->yBob = -SIN_DEG(player->bobPhase) * 5.0f;
        player->rockAngle = SIN_DEG(player->rockPhase) * 10.0f;
    } else {
        player->xRock = SIN_DEG(player->rockPhase * 0.7f) * 0.5f;
        player->bobPhase += 10.0f;
        player->rockPhase += 8.0f;
        if ((gLevelType == LEVELTYPE_PLANET) ||
            ((player->alternateView == true) && (gLevelMode == LEVELMODE_ON_RAILS))) {
            player->yBob = -SIN_DEG(player->bobPhase) * 0.5f;
            if ((player->wings.rightState <= WINGSTATE_BROKEN) || (player->wings.leftState <= WINGSTATE_BROKEN)) {
                player->rockAngle = SIN_DEG(player->rockPhase) * 5.0f;
            } else {
                player->rockAngle = SIN_DEG(player->rockPhase) * 1.5f;
            }
        }
    }
}

void Player_DamageEffects(Player* player) {
    s32 var_v1;
    f32 sp40;

    if (!player->alternateView || (gLevelMode == LEVELMODE_ALL_RANGE)) {
        if (player->wings.rightState <= WINGSTATE_BROKEN) {
            if (((gGameFrameCount % 2U) == 0) && (gRightWingDebrisTimer[player->num] != 0)) {
                func_effect_8007D10C(RAND_FLOAT_CENTERED(10.0f) + player->hit1.x, RAND_FLOAT(5.0f) + player->hit1.y,
                                     player->hit1.z, 1.0f);
            }
            if (((gGameFrameCount % 2U) == 0) && (Rand_ZeroOne() < 0.5f) && !gVersusMode) {
                func_effect_8007C484(RAND_FLOAT_CENTERED(5.0f) + player->hit1.x, RAND_FLOAT(5.0f) + player->hit1.y,
                                     player->hit1.z, player->vel.x, player->vel.y, player->vel.z,
                                     RAND_FLOAT(0.02f) + 0.02f, player->num + 1);
            }
        }
        if (player->wings.leftState <= WINGSTATE_BROKEN) {
            if (((gGameFrameCount % 2U) == 0) && (gLeftWingDebrisTimer[player->num] != 0)) {
                func_effect_8007D10C(RAND_FLOAT_CENTERED(10.0f) + player->hit2.x, RAND_FLOAT(5.0f) + player->hit2.y,
                                     player->hit2.z, 1.0f);
            }
            if (((gGameFrameCount % 2U) == 0) && (Rand_ZeroOne() < 0.5f) && !gVersusMode) {
                func_effect_8007C484(RAND_FLOAT_CENTERED(5.0f) + player->hit2.x, RAND_FLOAT(5.0f) + player->hit2.y,
                                     player->hit2.z, player->vel.x, player->vel.y, player->vel.z,
                                     RAND_FLOAT(0.02f) + 0.02f, player->num + 1);
            }
        }
    }
    var_v1 = 7;
    if (player->shields < 64) {
        if (player->shields > 16) {
            var_v1 = 16 - 1;
        }
        if (player->shields > 32) {
            var_v1 = 32 - 1;
        }
        if (player->shields > 48) {
            var_v1 = 64 - 1;
        }
        if (!player->alternateView || (gLevelMode == LEVELMODE_ALL_RANGE)) {
            sp40 = 0.0f;
            if (player->form == FORM_LANDMASTER) {
                sp40 = 30.0f;
            }
            if ((gGameFrameCount & var_v1) == 0) {
                func_effect_8007D10C(player->pos.x + RAND_FLOAT_CENTERED(10.0f),
                                     player->pos.y + sp40 + RAND_FLOAT(10.0f),
                                     player->trueZpos + RAND_FLOAT_CENTERED(10.0f), 2.2f);
            }
            if (((gGameFrameCount & (var_v1 >> 2)) == 0) && (Rand_ZeroOne() < 0.5f)) {
                func_effect_8007C484(player->pos.x + RAND_FLOAT_CENTERED(30.0f),
                                     player->pos.y + sp40 + RAND_FLOAT(10.0f),
                                     player->trueZpos + RAND_FLOAT_CENTERED(30.0f), player->vel.x, player->vel.y,
                                     player->vel.z, 0.04f + RAND_FLOAT(0.03f), player->num + 1);
                if (player->timer_224 == 0) {
                    player->timer_224 = 2;
                }
            }
        } else if (((gGameFrameCount & (var_v1 >> 2)) == 0) && (Rand_ZeroOne() < 0.5f) && (player->timer_224 == 0)) {
            player->timer_224 = 2;
        }
    }
}

void Player_WaterEffects(Player* player) {
    Vec3f sp54 = { -65.0f, -22.0f, -65.0f };
    Vec3f sp48 = { 65.0f, -22.0f, -65.0f };
    Vec3f sp3C;
    Vec3f sp30;

    if (gGroundSurface == SURFACE_WATER) {
        Matrix_Translate(gCalcMatrix, player->pos.x, player->pos.y, player->trueZpos, MTXF_NEW);
        Matrix_RotateY(gCalcMatrix, (player->yRot_114 + player->rot.y + 180.0f) * M_DTOR, MTXF_APPLY);
        Matrix_RotateX(gCalcMatrix, -((player->rot.x + player->aerobaticPitch) * M_DTOR), MTXF_APPLY);
        Matrix_RotateZ(gCalcMatrix, -(player->bankAngle * M_DTOR), MTXF_APPLY);
        Matrix_MultVec3f(gCalcMatrix, &sp54, &sp3C);
        Matrix_MultVec3f(gCalcMatrix, &sp48, &sp30);
        if (player->pos.y < (gGroundHeight + 100.0f)) {
            if ((sp3C.y < gGroundHeight + 80.0f) && ((gGameFrameCount % 2) == 0)) {
                if (sPlayWingSplashSfx) {}
                func_effect_8007ACE0(sp3C.x, gGroundHeight, sp3C.z, 0.1f, 2.0f,
                                     player->rot.y + player->yRot_114 + 20.0f);
            }
            if ((sp30.y < gGroundHeight + 80.0f) && ((gGameFrameCount % 2) == 0)) {
                func_effect_8007ACE0(sp30.x, gGroundHeight, sp30.z, 0.1f, 2.0f,
                                     player->rot.y + player->yRot_114 - 20.0f);
            }
        }
        if ((sp30.y < gGroundHeight + 80.0f) || (sp3C.y < gGroundHeight + 80.0f)) {
            if (!sPlayWingSplashSfx) {
                sPlayWingSplashSfx = true;
                AUDIO_PLAY_SFX(NA_SE_SPLASH_LEVEL_S, player->sfxSource, 0);
            }
        } else {
            sPlayWingSplashSfx = false;
            Audio_KillSfxBySourceAndId(player->sfxSource, NA_SE_SPLASH_LEVEL_S);
        }
    }
}

void Scenery360_Initialize(Scenery360* scenery360) {
    s32 i;
    u8* ptr = (u8*) scenery360;

    for (i = 0; i < sizeof(Scenery360); i++, ptr++) {
        *ptr = 0;
    }
}

void Play_InitVsStage(void) {
    s16 temp_v0;
    s16 temp_v0_2;
    s32 var_s1;
    s32 var_s1_2;
    s32 i;
    s32 j;
    s32 var_s4_2;

    switch (gVersusStage) {
        case VS_STAGE_CORNERIA:
            gLevelObjects = LOAD_ASSET(D_versus_302DE3C);
            break;
        case VS_STAGE_KATINA:
            gLevelObjects = LOAD_ASSET(D_versus_302E0E4);
            break;
        case VS_STAGE_SECTOR_Z:
            if (gVsMatchType == 2) {
                gLevelObjects = LOAD_ASSET(D_versus_302E378);
            } else {
                gLevelObjects = LOAD_ASSET(D_versus_302E170);
            }
            break;
    }
    for (i = 0, j = 0; i < 199; j++) {
        if (gLevelObjects[j].id <= OBJ_INVALID) {
            break;
        }
        if (gLevelObjects[j].id == OBJ_SCENERY_147) {
            Scenery360_Initialize(&gScenery360[i]);
            gScenery360[i].obj.status = OBJ_ACTIVE;
            gScenery360[i].obj.id = gLevelObjects[j].id;
            gScenery360[i].obj.pos.x = gLevelObjects[j].xPos;
            gScenery360[i].obj.pos.z = gLevelObjects[j].zPos1;
            gScenery360[i].obj.pos.y = gLevelObjects[j].yPos;
            Object_SetInfo(&gScenery360[i].info, gScenery360[i].obj.id);
            i++;
        }
    }
    for (i = 5, j = 0; i < 199; j++) {
        if (gLevelObjects[j].id <= OBJ_INVALID) {
            break;
        }
        if (gLevelObjects[j].id != OBJ_SCENERY_147) {
            Scenery360_Initialize(&gScenery360[i]);
            gScenery360[i].obj.status = OBJ_ACTIVE;
            gScenery360[i].obj.id = gLevelObjects[j].id;
            gScenery360[i].obj.pos.x = gLevelObjects[j].xPos;
            gScenery360[i].obj.pos.z = gLevelObjects[j].zPos1;
            gScenery360[i].obj.pos.y = gLevelObjects[j].yPos;
            gScenery360[i].obj.rot.y = gLevelObjects[j].rot.y;
            Object_SetInfo(&gScenery360[i].info, gScenery360[i].obj.id);
            i++;
        }
    }
}

void Play_dummy_800A5330(void) {
}

void Play_Setup360_CO(void) {
    Sprite* sprite;
    Scenery360* scenery360;
    s32 i;
    s32 j;

    gLevelObjects = LOAD_ASSET(D_CO_603B074);

    for (j = 0, scenery360 = gScenery360; j < 200; j++) {
        if (gLevelObjects[j].id <= OBJ_INVALID) {
            break;
        }
        if (gLevelObjects[j].id < OBJ_SCENERY_MAX) {
            Scenery360_Initialize(scenery360);
            scenery360->obj.status = OBJ_ACTIVE;
            scenery360->obj.id = gLevelObjects[j].id;
            scenery360->obj.pos.x = gLevelObjects[j].xPos;
            scenery360->obj.pos.z = gLevelObjects[j].zPos1;
            scenery360->obj.pos.y = gLevelObjects[j].yPos;
            scenery360->obj.rot.y = gLevelObjects[j].rot.y;
            Object_SetInfo(&scenery360->info, scenery360->obj.id);
            if (scenery360->obj.id == OBJ_SCENERY_1) {
                scenery360->info.dList = D_CO_6020760;
            }
            scenery360++;
        }
    }

    for (j = 0, sprite = gSprites; j < ARRAY_COUNT(gSprites); j++) {
        if (gLevelObjects[j].id <= OBJ_INVALID) {
            break;
        }
        if (gLevelObjects[j].id == OBJ_SPRITE_CO_TREE) {
            Sprite_Initialize(sprite);
            sprite->obj.status = OBJ_INIT;
            sprite->obj.id = gLevelObjects[j].id;
            sprite->obj.pos.x = gLevelObjects[j].xPos;
            sprite->obj.pos.z = gLevelObjects[j].zPos1;
            sprite->obj.pos.y = gLevelObjects[j].yPos;
            Object_SetInfo(&sprite->info, sprite->obj.id);
            sprite++;
        }
    }
    i = 0; // fake?
    Boss_Initialize(&gBosses[i]);
    gBosses[i].obj.status = OBJ_INIT;
    gBosses[i].obj.pos.x = 0.0f;
    gBosses[i].obj.pos.y = 0.0f;
    gBosses[i].obj.pos.z = 0.0f;
    gBosses[i].obj.id = OBJ_BOSS_292;
    Object_SetInfo(&gBosses[i].info, gBosses[i].obj.id);
}

void Play_Setup360_SY(void) {
    Scenery360* scenery360;
    s32 i;
    s32 j;

    gLevelObjects = LOAD_ASSET(D_SY_6030B14);

    for (j = 0, scenery360 = gScenery360; j < 200; j++) {
        if (gLevelObjects[j].id <= OBJ_INVALID) {
            break;
        }
        if (gLevelObjects[j].id < OBJ_SCENERY_MAX) {
            Scenery360_Initialize(scenery360);
            scenery360->obj.status = OBJ_ACTIVE;
            scenery360->obj.id = gLevelObjects[j].id;
            scenery360->obj.pos.x = gLevelObjects[j].xPos;
            scenery360->obj.pos.z = gLevelObjects[j].zPos1;
            scenery360->obj.pos.y = gLevelObjects[j].yPos;
            scenery360->obj.rot.y = gLevelObjects[j].rot.y;
            Object_SetInfo(&scenery360->info, scenery360->obj.id);
            scenery360++;
        }
    }
    i = 0; // fake?
    Boss_Initialize(&gBosses[i]);
    gBosses[i].obj.status = OBJ_INIT;
    gBosses[i].obj.pos.x = 0.0f;
    gBosses[i].obj.pos.y = 0.0f;
    gBosses[i].obj.pos.z = 0.0f;
    gBosses[i].obj.id = OBJ_BOSS_SY;
    Object_SetInfo(&gBosses[i].info, gBosses[i].obj.id);
    i = 1;
    Boss_Initialize(&gBosses[i]);
    gBosses[i].obj.status = OBJ_INIT;
    gBosses[i].obj.pos.x = 0.0f;
    gBosses[i].obj.pos.y = 0.0f;
    gBosses[i].obj.pos.z = 0.0f;
    gBosses[i].obj.id = OBJ_BOSS_SY;
    Object_SetInfo(&gBosses[i].info, gBosses[i].obj.id);
    i = 2;
    Boss_Initialize(&gBosses[i]);
    gBosses[i].obj.status = OBJ_INIT;
    gBosses[i].obj.pos.x = 0.0f;
    gBosses[i].obj.pos.y = 0.0f;
    gBosses[i].obj.pos.z = 0.0f;
    gBosses[i].obj.id = OBJ_BOSS_SY;
    Object_SetInfo(&gBosses[i].info, gBosses[i].obj.id);
}

void Play_Setup360_AND(void) {
    s32 i = 0; // fake?

    Boss_Initialize(&gBosses[i]);
    gBosses[i].obj.status = OBJ_INIT;
    gBosses[i].obj.pos.x = 0.0f;
    gBosses[i].obj.pos.y = 0.0f;
    gBosses[i].obj.pos.z = 0.0f;
    gBosses[i].obj.id = OBJ_BOSS_321;
    Object_SetInfo(&gBosses[i].info, gBosses[i].obj.id);
}

void Play_Setup(void) {
    s32 i;

    gStarCount = 0;
    gLevelPhase = 0;
    gMissedZoSearchlight = false;
    gSavedZoSearchlightStatus = false;
    gSceneSetup = 0;
    gAllRangeCheckpoint = gSavedObjectLoadIndex = 0;
    gSavedPathProgress = 0.0f;
    gSavedHitCount = gCsFrameCount = gLevelStartStatusScreenTimer = gLevelClearScreenTimer = gRadioState = 0;
    D_ctx_8017782C = 1;
    if (((gCurrentLevel == LEVEL_VENOM_2) && (gNextLevelPhase == 2)) || (gCurrentLevel == LEVEL_VENOM_ANDROSS)) {
        return;
    }
    for (i = 1; i < 4; i++) {
        if (gSavedTeamShields[i] < 0) {
            if (gSavedTeamShields[i] == -1) {
                gSavedTeamShields[i] = 0;
            }
        } else if (gSavedTeamShields[i] == 0) {
            gSavedTeamShields[i] = 255;
        }
    }
}

Environment* D_800D2F98[21] = {
    &D_CO_6037160, &D_ME_6026C80, &D_SX_602A120,      &D_A6_6023F20, &D_A6_6028760, &D_SY_602E4B0,  &D_VE1_6007E30,
    &D_SO_601F1F0, &D_ZO_60266D0, &D_ANDROSS_C035110, &D_TR_6006A60, &D_MA_6030E30, &D_TI_6005000,  &D_AQ_602E540,
    &D_FO_600EA90, NULL,          &D_KA_6011000,      &D_BO_600FF30, &D_SZ_6006E70, &D_VE2_6014D50, &D_versus_302DD70,
};

void Play_InitEnvironment(void) {
    if (gVersusMode) {
        switch (gVersusStage) {
            case 0:
                sEnvironment = LOAD_ASSET(D_versus_302DD70);
                break;
            case 1:
                sEnvironment = LOAD_ASSET(D_versus_302DDB4);
                break;
            case 2:
                sEnvironment = LOAD_ASSET(D_versus_302DDF8);
                break;
        }
    } else {
        sEnvironment = LOAD_ASSET(D_800D2F98[gCurrentLevel]);
    }
    if (!D_ctx_8017782C) {
        if (gCurrentLevel == LEVEL_SOLAR) {
            Audio_SetHeatAlarmParams(255, 1);
            AUDIO_PLAY_SFX(NA_SE_OVERHEAT_ALARM, gDefaultSfxSource, 4);
            Audio_KillSfxBySourceAndId(gPlayer[0].sfxSource, NA_SE_OB_MAGMA_BUBBLE);
        }
    } else if (gCurrentLevel == LEVEL_AQUAS) {
        sEnvironment = LOAD_ASSET(D_AQ_602E584);
    }
    gBgmSeqId = sEnvironment->seqId;
    gLevelType = sEnvironment->type;
    gGroundType = sEnvironment->unk04;
    gBgColor = sEnvironment->bgColor;
    gFogRed = sEnvironment->fogR;
    gFogGreen = sEnvironment->fogG;
    gFogBlue = sEnvironment->fogB;
    gFogNear = sEnvironment->fogN;
    gFogFar = sEnvironment->fogF;
    gLight1R = gLight2R = D_ctx_80161A70 = sEnvironment->lightR;
    gLight1G = gLight2G = D_ctx_80161A74 = sEnvironment->lightG;
    gLight1B = gLight2B = D_ctx_80161A78 = sEnvironment->lightB;
    gAmbientR = sEnvironment->ambR;
    gAmbientG = sEnvironment->ambG;
    gAmbientB = sEnvironment->ambB;
    gEnvLightxRot = gLight2xRotTarget = D_ctx_80178520 = gLight1xRot = gLight1xRotTarget = sEnvironment->lightDir.x;
    gEnvLightyRot = gLight2yRotTarget = D_ctx_80178524 = gLight1yRot = gLight1yRotTarget = sEnvironment->lightDir.y;
    gEnvLightzRot = gLight2zRotTarget = D_ctx_80178528 = gLight1zRot = gLight1zRotTarget = sEnvironment->lightDir.z;
    gProjectFar = 12800.0f;
    gLight2colorStep = 40;
    D_ctx_80178544 = 40;
    gFovY = 45.0f;
}

void Play_GenerateStarfield(void) {
    u32 i;

    MEM_ARRAY_ALLOCATE(gStarOffsetsX, 1000);
    MEM_ARRAY_ALLOCATE(gStarOffsetsY, 1000);
    MEM_ARRAY_ALLOCATE(gStarFillColors, 1000);
    Rand_SetSeed(1, 29000, 9876);
    for (i = 0; i < 1000; i++) {
        gStarOffsetsX[i] = RAND_FLOAT_SEEDED(480.0f) - 80.0f;
        gStarOffsetsY[i] = RAND_FLOAT_SEEDED(360.0f) - 60.0f;
        gStarFillColors[i] = FILL_COLOR(gStarColors[i % ARRAY_COUNT(gStarColors)]);
    }
}

void Play_SetupStarfield(void) {
    Play_GenerateStarfield();
    gGroundHeight = -25000.0f;
    gStarCount = 600;
    if (gCurrentLevel == LEVEL_AREA_6) {
        gStarCount = 300;
    }
    if (gCurrentLevel == LEVEL_UNK_15) {
        gStarCount = 400;
    }
    if (gGameState != GSTATE_PLAY) {
        gStarCount = 800;
    }
    if (gCurrentLevel == LEVEL_FORTUNA) {
        gStarCount = 500;
    }
    if (gVersusMode) {
        gStarCount = 0;
    }
    if (gCurrentLevel == LEVEL_BOLSE) {
        gStarCount = 300;
        gGroundHeight = -0.0f;
    }
    if (gCurrentLevel == LEVEL_TRAINING) {
        gStarCount = 800;
        gGroundHeight = -0.0f;
    }
}

void Player_PlaySfx(f32* sfxSrc, u32 sfxId, s32 mode) {
    if (!gVersusMode) {
        AUDIO_PLAY_SFX(sfxId, sfxSrc, 0);
    } else {
        AUDIO_PLAY_SFX(sfxId, sfxSrc, mode);
    }
}

void Play_PlaySfxFirstPlayer(f32* sfxSrc, u32 sfxId) {
    AUDIO_PLAY_SFX(sfxId, sfxSrc, 0);
}

void Play_PlaySfxNoPlayer(f32* sfxSrc, u32 sfxId) {
    AUDIO_PLAY_SFX(sfxId, sfxSrc, 4);
}

void BonusText_Initialize(BonusText* bonus) {
    s32 i;
    u8* ptr = (u8*) bonus;

    for (i = 0; i < sizeof(BonusText); i++, ptr++) {
        *ptr = 0;
    }
}

void TexturedLine_Initialize(TexturedLine* texLine) {
    s32 i;
    u8* ptr = (u8*) texLine;

    for (i = 0; i < sizeof(TexturedLine); i++, ptr++) {
        *ptr = 0;
    }
}

void RadarMark_Initialize(RadarMark* radarMark) {
    s32 i;
    u8* ptr = (u8*) radarMark;

    for (i = 0; i < sizeof(RadarMark); i++, ptr++) {
        *ptr = 0;
    }
}

void Play_ClearObjectData(void) {
    s16 i;
    s16 j;

    for (i = 0; i < ARRAY_COUNT(gBonusText); i++) {
        BonusText_Initialize(&gBonusText[i]);
    }
    for (i = 0; i < ARRAY_COUNT(gRadarMarks); i++) {
        RadarMark_Initialize(&gRadarMarks[i]);
    }
    for (i = 0; i < ARRAY_COUNT(gTexturedLines); i++) {
        TexturedLine_Initialize(&gTexturedLines[i]);
    }
    for (i = 0; i < ARRAY_COUNT(gScenery); i++) {
        Object_Kill(&gScenery[i].obj, gScenery[i].sfxSource);
        Scenery_Initialize(&gScenery[i]);
    }
    for (i = 0; i < ARRAY_COUNT(gSprites); i++) {
        Sprite_Initialize(&gSprites[i]);
    }
    for (i = 0; i < ARRAY_COUNT(gActors); i++) {
        Object_Kill(&gActors[i].obj, gActors[i].sfxSource);
        Actor_Initialize(&gActors[i]);
    }
    for (i = 0; i < ARRAY_COUNT(gBosses); i++) {
        Object_Kill(&gBosses[i].obj, gBosses[i].sfxSource);
        Boss_Initialize(&gBosses[i]);
    }
    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        Object_Kill(&gEffects[i].obj, gEffects[i].sfxSource);
        Effect_Initialize(&gEffects[i]);
    }
    for (i = 0; i < ARRAY_COUNT(gItems); i++) {
        Object_Kill(&gItems[i].obj, gItems[i].sfxSource);
        Item_Initialize(&gItems[i]);
    }
    for (i = 0; i < ARRAY_COUNT(gPlayerShots); i++) {
        Object_Kill(&gPlayerShots[i].obj, gPlayerShots[i].sfxSource);
        PlayerShot_Initialize(&gPlayerShots[i]);
    }
    gDrawSmallRocks = D_ctx_801782BC = D_ctx_801782C0 = D_ctx_801782D0 = gBossActive = gKillEventActors =
        gGroundClipMode = gPrevEventActorIndex = gFormationLeaderIndex = gRingPassCount = 0;
    gFormationInitPos.x = gFormationInitPos.y = gFormationInitPos.z = gFormationInitRot.x = gFormationInitRot.y =
        gFormationInitRot.z = 0.0f;
    for (i = 0; i < ARRAY_COUNT(gTeamArrowsViewPos); i++) {
        gTeamArrowsViewPos[i].x = gTeamArrowsViewPos[i].y = gTeamArrowsViewPos[i].z = 100.0f;
    }
    for (i = 0; i < ARRAY_COUNT(gActor194yPos); i++) {
        gActor194Status[i] = 0;
        for (j = 0; j < ARRAY_COUNT(*gActor194yPos); j++) {
            gActor194yPos[i][j] = -5000.0f;
        }
    }
}

void Play_UpdateFillScreen(void) {
    if (gFillScreenAlpha != gFillScreenAlphaTarget) {
        if (gFillScreenAlpha < gFillScreenAlphaTarget) {
            gFillScreenAlpha += gFillScreenAlphaStep;
            if (gFillScreenAlpha >= gFillScreenAlphaTarget) {
                gFillScreenAlpha = gFillScreenAlphaTarget;
            }
        } else {
            gFillScreenAlpha -= gFillScreenAlphaStep;
            if (gFillScreenAlphaTarget >= gFillScreenAlpha) {
                gFillScreenAlpha = gFillScreenAlphaTarget;
            }
        }
    }
    gFillScreenAlphaStep = 16;
    Math_SmoothStepToF(&gLight3Brightness, 0.0f, 1.0f, 0.04f, 0.001f);
    if (gScreenFlashTimer != 0) {
        gScreenFlashTimer--;
        if ((gScreenFlashTimer & 2) != 0) {
            gFillScreenRed = 255;
            gFillScreenGreen = 255;
            gFillScreenBlue = 255;
            gFillScreenAlpha = 254;
        } else {
            gFillScreenAlpha = 0;
        }
    }
}

void Play_SpawnHitmark(f32 xPos, f32 yPos, f32 zPos) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gPlayerShots); i++) {
        if (gPlayerShots[i].obj.status == SHOT_FREE) {
            PlayerShot_Initialize(&gPlayerShots[i]);
            gPlayerShots[i].obj.status = SHOT_HITMARK;
            gPlayerShots[i].unk_60 = 0;
            gPlayerShots[i].obj.pos.x = xPos;
            gPlayerShots[i].obj.pos.y = yPos;
            gPlayerShots[i].obj.pos.z = zPos;
            break;
        }
    }
}

void Play_SetupDebris(Actor* actor, s32 state, f32 xPos, f32 yPos, f32 zPos) {
    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_DEBRIS;
    actor->state = state;
    actor->obj.pos.x = xPos;
    actor->obj.pos.y = yPos;
    actor->obj.pos.z = zPos;
    actor->gravity = 0.5f;
    if ((state == 0) || (state == 1)) {
        actor->vel.y = RAND_FLOAT(5.0f) + 10.0f;
        actor->vel.x = 10.0f;

        if (state == 0) {
            actor->vel.x = -10.0f;
        }
        actor->timer_0BC = 15;
    } else {
        if (gLevelType == LEVELTYPE_PLANET) {
            actor->vel.y = RAND_FLOAT(7.0f) + 7.0f;
            actor->vel.x = RAND_FLOAT_CENTERED(10.0f);
            actor->vel.z = RAND_FLOAT(5.0f) + 5.0f;
            if (gLevelMode == LEVELMODE_ALL_RANGE) {
                actor->vel.z = RAND_FLOAT_CENTERED(10.0f);
            }
            actor->timer_0BC = RAND_INT(10.0f) + 10;
        } else {
            actor->vel.x = RAND_FLOAT_CENTERED(10.0f);
            actor->vel.y = RAND_FLOAT_CENTERED(10.0f);
            actor->vel.z = RAND_FLOAT_CENTERED(10.0f);
            actor->timer_0BC = RAND_INT(25.0f) + 25;
            actor->gravity = 0.0f;
        }
        if (state == 2) {
            actor->scale = RAND_FLOAT(1.5f) + 0.75f;
        } else if (state == 4) {
            actor->scale = RAND_FLOAT(0.8f) + 0.3f;
            actor->timer_0BC = RAND_INT(50.0f) + 70;
        }
        actor->obj.rot.x = RAND_FLOAT(360.0f);
    }
    Object_SetInfo(&actor->info, actor->obj.id);
}

void Play_SpawnDebris(s32 state, f32 xPos, f32 yPos, f32 zPos) {
    s32 i;

    if (!gVersusMode) {
        for (i = ARRAY_COUNT(gActors) - 1; i >= 10; i--) {
            if (gActors[i].obj.status == OBJ_FREE) {
                Play_SetupDebris(&gActors[i], state, xPos, yPos, zPos);
                break;
            }
        }
    }
}

// Unused. Were gold rings in vs mode?
bool Player_CheckAllGoldRings(void) {
    return gGoldRingCount[0] && gGoldRingCount[1] && gGoldRingCount[2] && gGoldRingCount[3];
}

void Player_DamageWings(Player* player, s32 side, s32 damage) {
    if ((player->form == FORM_ARWING) && (gShieldAlpha[player->num] < 1.0f)) {
        if (side == 1) {
            gRightWingFlashTimer[player->num] = 30;
            if (player->wings.rightState == WINGSTATE_INTACT) {
                gRightWingHealth[player->num] -= damage;
                if (gRightWingHealth[player->num] <= 0) {
                    Play_SpawnDebris(1, player->hit1.x, player->hit1.y, player->hit1.z);
                    player->wings.rightState = WINGSTATE_BROKEN;
                    func_effect_8007D0E0(player->hit1.x, player->hit1.y, player->hit1.z, 2.0f);
                    gRightWingDebrisTimer[player->num] = 50;
                    Player_PlaySfx(player->sfxSource, NA_SE_ARWING_WING_BROKEN, player->num);
                    if (gAllRangeWingRepairTimer == 0) {
                        gAllRangeWingRepairTimer = 1000;
                    }
                }
            }
        } else if (side == 2) {
            gLeftWingFlashTimer[player->num] = 30;
            if (player->wings.leftState == WINGSTATE_INTACT) {
                gLeftWingHealth[player->num] -= damage;
                if (gLeftWingHealth[player->num] <= 0) {
                    Play_SpawnDebris(0, player->hit2.x, player->hit2.y, player->hit2.z);
                    player->wings.leftState = WINGSTATE_BROKEN;
                    func_effect_8007D0E0(player->hit2.x, player->hit2.y, player->hit2.z, 2.0f);
                    gLeftWingDebrisTimer[player->num] = 50;
                    Player_PlaySfx(player->sfxSource, NA_SE_ARWING_WING_BROKEN, player->num);
                    if (gAllRangeWingRepairTimer == 0) {
                        gAllRangeWingRepairTimer = 1000;
                    }
                }
            }
        }
    }
}

void Player_ApplyDamage(Player* player, s32 direction, s32 damage) {
    Vec3f sp44;
    Vec3f sp38;
    f32 sp34 = 20.0f;

    player->unk_1A4 = damage;
    player->unk_21C = direction;
    if ((damage == 39) || (damage == 41) || (damage == 42) || (damage == 43)) {
        damage = 40;
    }
    if (gExpertMode) {
        player->damage = damage * 2;
    } else {
        player->damage = damage;
    }
    if (player->damage != 0) {
        player->radioDamageTimer = 4;
    }
    player->unk_284 = 0;
    player->hitTimer = 20;
    if (player->unk_1A4 > 40) {
        sp34 = (player->boostSpeed * 0.3f) + 20.0f;
        player->timer_498 = 5;
    } else if ((gCurrentLevel == LEVEL_VENOM_ANDROSS) && !gBossActive) {
        player->timer_498 = 3;
    } else if ((gCurrentLevel == LEVEL_VENOM_1) || (gCurrentLevel == LEVEL_AQUAS)) {
        player->timer_498 = 5;
    } else {
        player->timer_498 = 20;
    }
    if (gHasShield[player->num]) {
        Player_PlaySfx(player->sfxSource, NA_SE_DAMAGE_S, player->num);
        gShieldTimer[player->num] = 5;
        gShieldAlpha[player->num] = 2.0f;
        player->damage = 0;
    } else {
        if (player->shields != 0) {
            if (player->shields < 50) {
                AUDIO_PLAY_SFX(NA_SE_SHIELD_WARNING1, gDefaultSfxSource, 4);
            } else if (player->shields < 100) {
                AUDIO_PLAY_SFX(NA_SE_SHIELD_WARNING0, gDefaultSfxSource, 4);
            }
        }
        if (damage < 25) {
            Player_PlaySfx(player->sfxSource, NA_SE_DAMAGE_S, player->num);
        } else {
            Player_PlaySfx(player->sfxSource, NA_SE_DAMAGE_L, player->num);
        }
    }
    Matrix_RotateY(gCalcMatrix, player->yRot_114 * M_DTOR, MTXF_NEW);
    Matrix_RotateZ(gCalcMatrix, player->bankAngle * M_DTOR, MTXF_APPLY);
    sp44.z = 0.0f;
    switch (player->unk_21C) {
        case 0:
            player->timer_224 = 20;
            player->knockback.x = 0.f;
            player->knockback.y = 0.f;
            player->knockback.z = 0.f;
            break;
        case 1:
            sp44.x = -sp34;
            sp44.y = 0.0f;

            Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp44, &sp38);
            player->knockback.x = sp38.x;
            player->knockback.y = sp38.y;
            player->knockback.z = sp38.z;
            Play_SpawnHitmark(player->hit1.x - player->vel.x, player->hit1.y, player->hit1.z - player->vel.z);
            Player_DamageWings(player, 1, 20);
            break;
        case 2:
            sp44.x = sp34;
            sp44.y = 0.0f;

            Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp44, &sp38);
            player->knockback.x = sp38.x;
            player->knockback.y = sp38.y;
            player->knockback.z = sp38.z;
            Play_SpawnHitmark(player->hit2.x - player->vel.x, player->hit2.y, player->hit2.z - player->vel.z);
            Player_DamageWings(player, 2, 20);
            break;
        case 3:
            player->timer_224 = 20;
            Play_SpawnHitmark(player->hit4.x - player->vel.x, player->hit4.y, player->hit4.z - player->vel.z);
            if (player->form != FORM_LANDMASTER) {
                sp44.x = 0.0f;
                sp44.y = -sp34;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp44, &sp38);
                player->knockback.x = sp38.x;
                player->knockback.y = sp38.y;
                player->knockback.z = sp38.z;
            }
            if (Rand_ZeroOne() < 0.5f) {
                Player_DamageWings(player, 1, 15);
            } else {
                Player_DamageWings(player, 2, 15);
            }
            break;
        case 4:
            player->timer_224 = 20;
            Play_SpawnHitmark(player->hit3.x - player->vel.x, player->hit3.y, player->hit3.z - player->vel.z);
            sp44.x = 0.0f;
            sp44.y = sp34;
            Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp44, &sp38);
            player->knockback.x = sp38.x;
            player->knockback.y = sp38.y;
            player->knockback.z = sp38.z;
            if (Rand_ZeroOne() < 0.5f) {
                Player_DamageWings(player, 1, 15);
            } else {
                Player_DamageWings(player, 2, 15);
            }
            break;
    }
    if ((gCurrentLevel == LEVEL_VENOM_1) && (player->unk_1A4 == 42)) {
        if (player->pos.x > 0.0f) {
            player->knockback.x = -30.0f;
        } else {
            player->knockback.x = 30.0f;
        }
        player->timer_498 = 10;
    }
}

f32 D_800D2FEC[5] = {
    0.0f, 0.5f, -0.5f, 0.5f, -0.5f,
};

void Player_GroundedCollision(Player* player, u32 arg1, f32 arg2, f32 arg3) {
    player->unk_21C = arg1;
    switch (arg1) {
        case 1:
        case 2:
            player->pos.x = player->basePos.x;
            player->knockback.x = 0.0f;
            player->pos.x += D_800D2FEC[player->unk_21C];
            if (player->form == FORM_LANDMASTER) {
                player->pos.x -= D_800D2FEC[player->unk_21C];
            }
            Math_SmoothStepToF(&player->baseSpeed, 2.0f, 1.0f, 2.0f, 0.00001f);
            break;
        case 3:
        case 4:
            player->pos.z = player->basePos.z;
            player->knockback.z = 0.0f;
            player->pos.z += D_800D2FEC[player->unk_21C];
            if (player->form == FORM_LANDMASTER) {
                player->pos.z += D_800D2FEC[player->unk_21C];
            }
            player->trueZpos = player->pos.z;
            Math_SmoothStepToF(&player->baseSpeed, 2.0f, 1.0f, 2.0f, 0.00001f);
            break;
        case 0:
        case 5:
            break;
    }
}

bool Play_CheckDynaFloorCollision(f32* arg0, s32* arg1, f32 xPos, f32 yPos, f32 zPos) {
    Vtx* spA4;
    u16* spA0;
    s32 sp9C;
    s32 sp98;
    f32 sp94;
    f32 sp90;
    s32 sp8C;
    f32 x0;
    f32 y0;
    f32 z0;
    f32 x1;
    f32 y1;
    f32 z1;
    f32 x2;
    f32 y2;
    f32 z2;
    f32 temp1;
    f32 dz21;
    f32 dx10;
    f32 dx21;
    f32 dy10;
    f32 dy21;
    f32 dz10;
    f32 sp48;
    f32 crz;
    f32 cry;
    f32 crx;

    switch (gCurrentLevel) {
        case LEVEL_SOLAR:
            spA4 = LOAD_ASSET(D_SO_6001C50);
            spA0 = LOAD_ASSET(D_SO_6022760);
            break;
        case LEVEL_ZONESS:
            spA4 = LOAD_ASSET(D_ZO_6009ED0);
            spA0 = LOAD_ASSET(D_ZO_602AC50);
            break;
        default:
            return false;
    }

    sp9C = (s32) ((xPos + 2400.0f) / 300.0f);
    sp98 = (s32) ((zPos + gPathProgress + 1500.0f + 2400.0f) / 300.0f);
    if ((sp9C < 0) || (sp9C >= 16) || (sp98 < 0) || (sp98 >= 16)) {
        return false;
    }
    sp90 = Math_ModF(xPos + 2400.0f, 300.0f);
    sp94 = Math_ModF(zPos + gPathProgress + 1500.0f + 2400.0f, 300.0f);
    sp8C = (sp98 * 17) + sp9C;
    x0 = spA4[spA0[sp8C]].n.ob[0] * 3.0f;
    y0 = spA4[spA0[sp8C]].n.ob[1] * 2.0f;
    z0 = spA4[spA0[sp8C]].n.ob[2] * 3.0f;
    if (sp90 < sp94) {
        x1 = spA4[spA0[sp8C + 18]].n.ob[0] * 3.0f;
        y1 = spA4[spA0[sp8C + 18]].n.ob[1] * 2.0f;
        z1 = spA4[spA0[sp8C + 18]].n.ob[2] * 3.0f;
        x2 = spA4[spA0[sp8C + 17]].n.ob[0] * 3.0f;
        y2 = spA4[spA0[sp8C + 17]].n.ob[1] * 2.0f;
        z2 = spA4[spA0[sp8C + 17]].n.ob[2] * 3.0f;
    } else {
        x1 = spA4[spA0[sp8C + 1]].n.ob[0] * 3.0f;
        y1 = spA4[spA0[sp8C + 1]].n.ob[1] * 2.0f;
        z1 = spA4[spA0[sp8C + 1]].n.ob[2] * 3.0f;
        x2 = spA4[spA0[sp8C + 18]].n.ob[0] * 3.0f;
        y2 = spA4[spA0[sp8C + 18]].n.ob[1] * 2.0f;
        z2 = spA4[spA0[sp8C + 18]].n.ob[2] * 3.0f;
    }
    dx10 = x1 - x0;
    dx21 = x2 - x1;
    dy10 = y1 - y0;

    dy21 = y2 - y1;
    dz10 = z1 - z0;
    dz21 = z2 - z1;

    crx = (dy10 * dz21) - (dz10 * dy21);
    cry = (dz10 * dx21) - (dx10 * dz21);
    crz = (dx10 * dy21) - (dy10 * dx21);

    temp1 = -crx * x0 - cry * y0 - crz * z0;
    sp48 = (-temp1 - crx * xPos - crz * (zPos + gPathProgress + 1500.0f)) / cry;
    if (yPos < sp48) {
        *arg0 = sp48;
        *arg1 = sp8C;
        return true;
    }
    return false;
}

bool Play_CheckSingleHitbox(Hitbox* hitbox, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    if ((fabsf(hitbox->z.offset + arg3 - arg6) < (hitbox->z.size + D_ctx_8017853C)) &&
        (fabsf(hitbox->x.offset + arg1 - arg4) < (hitbox->x.size + D_ctx_8017853C)) &&
        (fabsf(hitbox->y.offset + arg2 - arg5) < (hitbox->y.size + D_ctx_8017853C))) {
        return true;
    }
    return false;
}

s32 Player_CheckHitboxCollision(Player* player, f32* hitboxData, s32* index, f32 xPos, f32 yPos, f32 zPos, f32 xRot,
                                f32 yRot, f32 zRot, f32 arg9, f32 argA, f32 argB) {
    s32 count;
    s32 i;
    f32 var_fv0;
    f32 var_fv1;
    f32 var_fa0;
    f32 spA0;
    Vec3f sp94;
    Vec3f sp88;

    count = *hitboxData;
    if (count != 0) {
        hitboxData++;
        for (i = 0; i < count; i++, hitboxData += 6) {
            spA0 = 0;
            if (*hitboxData == HITBOX_ROTATED) {
                Matrix_RotateZ(gCalcMatrix, -hitboxData[3] * M_DTOR, MTXF_NEW);
                Matrix_RotateX(gCalcMatrix, -hitboxData[1] * M_DTOR, MTXF_APPLY);
                Matrix_RotateY(gCalcMatrix, -hitboxData[2] * M_DTOR, MTXF_APPLY);
                Matrix_RotateZ(gCalcMatrix, -zRot * M_DTOR, MTXF_APPLY);
                Matrix_RotateX(gCalcMatrix, -xRot * M_DTOR, MTXF_APPLY);
                Matrix_RotateY(gCalcMatrix, -yRot * M_DTOR, MTXF_APPLY);
                hitboxData += 4;
                spA0 = 1;
            } else {
                if (*hitboxData >= HITBOX_SHADOW) {
                    hitboxData++;
                }
                Matrix_RotateZ(gCalcMatrix, -zRot * M_DTOR, MTXF_NEW);
                Matrix_RotateX(gCalcMatrix, -xRot * M_DTOR, MTXF_APPLY);
                Matrix_RotateY(gCalcMatrix, -yRot * M_DTOR, MTXF_APPLY);
            }
            if (!((arg9 == 0) && (argA == 0) && (argB == 0))) {
                Matrix_RotateZ(gCalcMatrix, -argB * M_DTOR, MTXF_APPLY);
                Matrix_RotateX(gCalcMatrix, -arg9 * M_DTOR, MTXF_APPLY);
                Matrix_RotateY(gCalcMatrix, -argA * M_DTOR, MTXF_APPLY);
            }
            if ((yRot == 0.0f) && (zRot == 0.0f) && (xRot == 0.0f) && (spA0 == 0)) {
                var_fv0 = player->hit3.x;
                var_fv1 = player->hit3.y;
                var_fa0 = player->hit3.z;
            } else {
                sp94.x = player->hit3.x - xPos;
                sp94.y = player->hit3.y - yPos;
                sp94.z = player->hit3.z - zPos;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp94, &sp88);
                var_fv0 = sp88.x + xPos;
                var_fv1 = sp88.y + yPos;
                var_fa0 = sp88.z + zPos;
            }
            if (Play_CheckSingleHitbox((Hitbox*) hitboxData, xPos, yPos, zPos, var_fv0, var_fv1, var_fa0)) {
                *index = i + 1;
                if (hitboxData[-1] == HITBOX_SHADOW) {
                    return -1;
                }
                if (hitboxData[-1] == HITBOX_WHOOSH) {
                    return -2;
                }
                return 3;
            }
            if (hitboxData[-1] < HITBOX_SHADOW) {
                if ((yRot == 0.0f) && (zRot == 0.0f) && (xRot == 0.0f) && (spA0 == 0)) {
                    var_fv0 = player->hit4.x;
                    var_fv1 = player->hit4.y;
                    var_fa0 = player->hit4.z;
                } else {
                    sp94.x = player->hit4.x - xPos;
                    sp94.y = player->hit4.y - yPos;
                    sp94.z = player->hit4.z - zPos;
                    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp94, &sp88);
                    var_fv0 = sp88.x + xPos;
                    var_fv1 = sp88.y + yPos;
                    var_fa0 = sp88.z + zPos;
                }
                if (Play_CheckSingleHitbox((Hitbox*) hitboxData, xPos, yPos, zPos, var_fv0, var_fv1, var_fa0)) {
                    *index = i + 1;
                    return 4;
                }
                if ((yRot == 0.0f) && (zRot == 0.0f) && (xRot == 0.0f) && (spA0 == 0)) {
                    var_fv0 = player->hit1.x;
                    var_fv1 = player->hit1.y;
                    var_fa0 = player->hit1.z;
                } else {
                    sp94.x = player->hit1.x - xPos;
                    sp94.y = player->hit1.y - yPos;
                    sp94.z = player->hit1.z - zPos;
                    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp94, &sp88);
                    var_fv0 = sp88.x + xPos;
                    var_fv1 = sp88.y + yPos;
                    var_fa0 = sp88.z + zPos;
                }
                if (Play_CheckSingleHitbox((Hitbox*) hitboxData, xPos, yPos, zPos, var_fv0, var_fv1, var_fa0)) {
                    *index = i + 1;
                    return 1;
                }
                if ((yRot == 0.0f) && (zRot == 0.0f) && (xRot == 0.0f) && (spA0 == 0)) {
                    var_fv0 = player->hit2.x;
                    var_fv1 = player->hit2.y;
                    var_fa0 = player->hit2.z;
                } else {
                    sp94.x = player->hit2.x - xPos;
                    sp94.y = player->hit2.y - yPos;
                    sp94.z = player->hit2.z - zPos;
                    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp94, &sp88);
                    var_fv0 = sp88.x + xPos;
                    var_fv1 = sp88.y + yPos;
                    var_fa0 = sp88.z + zPos;
                }
                if (Play_CheckSingleHitbox((Hitbox*) hitboxData, xPos, yPos, zPos, var_fv0, var_fv1, var_fa0)) {
                    *index = i + 1;
                    return 2;
                }
            }
        }
    }
    return 0;
}

bool Play_CheckPolyCollision(ObjectId objId, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, Vec3f* arg7,
                             Vec3f* arg8) {
    Vec3f sp54;
    Vec3f sp48;
    Vec3f sp3C;
    f32 sp34[2] = { 0, 0 };
    s32 colId;
    bool useCol2;

    sp54.x = arg4;
    sp54.y = arg5;
    sp54.z = arg6;
    sp48.x = arg1;
    sp48.y = arg2;
    sp48.z = arg3;

    useCol2 = false;
    switch (objId) {
        case OBJ_ACTOR_180:
            colId = COL1_0;
            break;
        case OBJ_SCENERY_4:
        case OBJ_SCENERY_5:
            colId = COL2_1;
            useCol2 = true;
            break;
        case OBJ_SCENERY_149:
            colId = COL1_5;
            break;
        case OBJ_SCENERY_150:
            colId = COL1_6;
            break;
        case OBJ_BOSS_FO:
            colId = COL1_4;
            break;
        case OBJ_BOSS_VE2:
            colId = COL1_9;
            break;
        case OBJ_BOSS_309:
            colId = COL1_7;
            break;
        case ACTOR_EVENT_ID:
            colId = COL1_3;
            break;
        case OBJ_BOSS_SZ:
            colId = COL1_8;
            break;
        case OBJ_SCENERY_ME_TUNNEL:
            colId = COL1_1;
            break;
        case OBJ_SCENERY_120:
            colId = COL2_18;
            useCol2 = true;
            break;
        case OBJ_SCENERY_124:
            colId = COL2_15;
            useCol2 = true;
            break;
        case OBJ_SCENERY_126:
            colId = COL2_16;
            useCol2 = true;
            break;
        case OBJ_SCENERY_47:
            colId = COL2_7;
            useCol2 = true;
            break;
        case OBJ_SCENERY_2:
            colId = COL2_2;
            useCol2 = true;
            break;
        case OBJ_SCENERY_3:
        case OBJ_SCENERY_69:
            colId = COL2_3;
            useCol2 = true;
            break;
        case OBJ_SCENERY_143:
            colId = COL2_17;
            useCol2 = true;
            break;
        case OBJ_SCENERY_140:
            colId = COL2_4;
            useCol2 = true;
            break;
        case OBJ_SCENERY_141:
            colId = COL2_6;
            useCol2 = true;
            break;
        case OBJ_SCENERY_117:
            colId = COL2_14;
            useCol2 = true;
            break;
        case OBJ_SCENERY_70:
            colId = COL2_8;
            useCol2 = true;
            break;
        case OBJ_SCENERY_72:
            colId = COL2_9;
            useCol2 = true;
            break;
        case OBJ_SCENERY_71:
            colId = COL2_10;
            useCol2 = true;
            break;
        case OBJ_SCENERY_73:
            colId = COL2_11;
            useCol2 = true;
            break;
        case OBJ_SCENERY_67:
            colId = COL2_12;
            useCol2 = true;
            break;
        case OBJ_SCENERY_74:
            colId = COL2_13;
            useCol2 = true;
            break;
        case OBJ_SCENERY_118:
        case OBJ_SCENERY_119:
        case OBJ_SCENERY_121:
        case OBJ_SCENERY_122:
        case OBJ_SCENERY_123:
        case OBJ_SCENERY_125:
        case OBJ_SCENERY_127:
        case OBJ_SCENERY_128:
        case OBJ_SCENERY_129:
        case OBJ_SCENERY_130:
        case OBJ_SCENERY_131:
        case OBJ_SCENERY_132:
        case OBJ_SCENERY_133:
        case OBJ_SCENERY_134:
        case OBJ_SCENERY_135:
        case OBJ_SCENERY_136:
        case OBJ_SCENERY_137:
        case OBJ_SCENERY_138:
        case OBJ_SCENERY_139:
        case OBJ_SCENERY_142:
        case OBJ_SCENERY_144:
        case OBJ_SCENERY_145:
        case OBJ_SCENERY_146:
        case OBJ_SCENERY_147:
        case OBJ_SCENERY_148:
        case OBJ_SCENERY_40:
        case OBJ_SCENERY_41:
        case OBJ_SCENERY_42:
        case OBJ_SCENERY_43:
        case OBJ_SCENERY_44:
        case OBJ_SCENERY_45:
        case OBJ_SCENERY_46:
        case OBJ_SCENERY_48:
        case OBJ_SCENERY_49:
        case OBJ_SCENERY_50:
        case OBJ_SCENERY_51:
        case OBJ_SCENERY_52:
        case OBJ_SCENERY_53:
        case OBJ_SCENERY_54:
        case OBJ_SCENERY_55:
        case OBJ_SCENERY_56:
        case OBJ_SCENERY_57:
        case OBJ_SCENERY_58:
        case OBJ_SCENERY_59:
        case OBJ_SCENERY_60:
        case OBJ_SCENERY_61:
        case OBJ_SCENERY_62:
        case OBJ_SCENERY_63:
        case OBJ_SCENERY_64:
        case OBJ_SCENERY_65:
        case OBJ_SCENERY_66:
        case OBJ_SCENERY_68:
        default:
            colId = COL2_0;
            useCol2 = true;
            break;
    }

    if (!useCol2) {
        if (func_col1_800998FC(&sp54, &sp48, arg8, colId, &sp3C, sp34) > 0) {
            return true;
        }
    } else {
        if (func_col2_800A3690(&sp54, &sp48, colId, arg7)) {
            return true;
        }
    }
    return false;
}

s32 Player_CheckPolyCollision(Player* player, ObjectId objId, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6,
                              f32 arg7) {
    Vec3f sp84;
    Vec3f sp78;
    Vec3f sp6C;
    Vec3f sp60;
    Vec3f sp54;

    sp84.x = arg2;
    sp84.y = arg3;
    sp84.z = arg4;
    Matrix_RotateY(gCalcMatrix, -arg6 * M_DTOR, MTXF_NEW);
    sp78.x = player->vel.x;
    sp78.y = player->vel.y;
    sp78.z = player->vel.z;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp78, &sp54);
    if ((player->form == FORM_LANDMASTER) || (player->form == FORM_ON_FOOT)) {
        sp78.x = player->pos.x - sp84.x;
        sp78.y = player->pos.y - sp84.y;
        sp78.z = player->trueZpos - sp84.z;
        Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp78, &sp6C);
        if (Play_CheckPolyCollision(objId, sp84.x, sp84.y, sp84.z, sp6C.x + sp84.x, sp6C.y + sp84.y, sp6C.z + sp84.z,
                                    &sp60, &sp54)) {
            player->pos.y = sp60.y;
            player->rot_104.x = Math_RadToDeg(sp60.x);
            player->rot_104.z = Math_RadToDeg(sp60.z);
            player->vel.y = 0.0f;
            if (player->form == FORM_ON_FOOT) {
                player->vel.y = -5.0f;
            }
            player->grounded = true;
            return 5;
        } else {
            return 0;
        }
    }
    sp78.x = player->hit3.x - sp84.x;
    sp78.y = player->hit3.y - sp84.y;
    sp78.z = player->hit3.z - sp84.z;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp78, &sp6C);
    if (Play_CheckPolyCollision(objId, sp84.x, sp84.y, sp84.z, sp6C.x + sp84.x, sp6C.y + sp84.y, sp6C.z + sp84.z, &sp60,
                                &sp54)) {
        return 3;
    }
    sp78.x = player->hit4.x - sp84.x;
    sp78.y = player->hit4.y - sp84.y;
    sp78.z = player->hit4.z - sp84.z;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp78, &sp6C);
    if (Play_CheckPolyCollision(objId, sp84.x, sp84.y, sp84.z, sp6C.x + sp84.x, sp6C.y + sp84.y, sp6C.z + sp84.z, &sp60,
                                &sp54)) {
        return 4;
    }
    sp78.x = player->hit1.x - sp84.x;
    sp78.y = player->hit1.y - sp84.y;
    sp78.z = player->hit1.z - sp84.z;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp78, &sp6C);
    if (Play_CheckPolyCollision(objId, sp84.x, sp84.y, sp84.z, sp6C.x + sp84.x, sp6C.y + sp84.y, sp6C.z + sp84.z, &sp60,
                                &sp54)) {
        return 1;
    }
    sp78.x = player->hit2.x - sp84.x;
    sp78.y = player->hit2.y - sp84.y;
    sp78.z = player->hit2.z - sp84.z;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp78, &sp6C);
    if (Play_CheckPolyCollision(objId, sp84.x, sp84.y, sp84.z, sp6C.x + sp84.x, sp6C.y + sp84.y, sp6C.z + sp84.z, &sp60,
                                &sp54)) {
        return 2;
    }
    return 0;
}

void Player_CheckItemCollect(Player* player) {
    s32 i;
    Item* item;
    s32 sp6C;

    for (i = 0, item = gItems; i < ARRAY_COUNT(gItems); i++, item++) {
        if ((item->obj.status == OBJ_ACTIVE) &&
            ((player->state_1C8 == PLAYERSTATE_1C8_ACTIVE) || (player->state_1C8 == PLAYERSTATE_1C8_U_TURN)) &&
            (item->timer_4A == 0) &&
            Player_CheckHitboxCollision(player, item->info.hitbox, &sp6C, item->obj.pos.x, item->obj.pos.y,
                                        item->obj.pos.z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f)) {
            item->collected = true;
            item->playerNum = gPlayerNum;
        }
    }
}

s32 D_800D3000[4][4] = {
    { 20, 40, 0, 0 },
    { 20, 20, 0, 0 },
    { 0, 0, 0, 0 },
    { 80, 120, 0, 0 },
};
Vec3f D_800D3040[6] = {
    { 0.0f, -20.0f, 0.0f }, { -17.5f, -17.5f, 0.0f }, { -17.5f, 17.5f, 0.0f },
    { 0.0f, 20.0f, 0.0f },  { 17.5f, 17.5f, 0.0f },   { 17.5f, -17.5f, 0.0f },
};
Vec3f D_800D3088[4] = {
    { 0.0f, -20.0f, 0.0f },
    { 0.0f, 20.0f, 0.0f },
    { 20.0f, 0.0f, 0.0f },
    { -20.0f, 0.0f, 0.0f },
};
Vec3f D_800D30B8[4] = {
    { 0.0f, -20.0f, 0.0f },
    { 0.0f, 20.0f, 0.0f },
    { -20.0f, 0.0f, 0.0f },
    { 20.0f, 0.0f, 0.0f },
};

void Player_Collide(Player* playerA, Player* playerB) {
    if (playerA->timer_498 == 0) {
        Player_ApplyDamage(playerA, 0, D_800D3000[playerA->form][playerB->form]);
        playerA->attacker = playerB->num + 1;
        playerB->attacker = playerA->num + 1;
    }
}

void Player_UpdateHitbox(Player* player) {
    Vec3f sp3C;

    Matrix_Translate(gCalcMatrix, player->pos.x, player->pos.y, player->trueZpos, MTXF_NEW);
    if (player->form == FORM_LANDMASTER) {
        player->rot_104.z = 0.0f;
        player->rot_104.x = 0.0f;

        sp3C.x = -40.0f;
        sp3C.y = 40.0f;
        sp3C.z = 0.0f;
        Matrix_MultVec3f(gCalcMatrix, &sp3C, &player->hit2);
        sp3C.x = 40.0f;
        Matrix_MultVec3f(gCalcMatrix, &sp3C, &player->hit1);
        sp3C.x = 0.0f;
        sp3C.z = -40.0f;
        Matrix_MultVec3f(gCalcMatrix, &sp3C, &player->hit3);
        sp3C.z = 40.0f;
        Matrix_MultVec3f(gCalcMatrix, &sp3C, &player->hit4);
    }
    if ((player->form == FORM_ON_FOOT) || (player->form == FORM_UNK_4)) {
        sp3C.x = 20.0f;
        sp3C.y = 20.0f;
        sp3C.z = 0.0f;
        Matrix_MultVec3f(gCalcMatrix, &sp3C, &player->hit2);
        sp3C.x = -20.0f;
        Matrix_MultVec3f(gCalcMatrix, &sp3C, &player->hit1);
        sp3C.x = 0.0f;
        sp3C.z = -20.0f;
        Matrix_MultVec3f(gCalcMatrix, &sp3C, &player->hit3);
        sp3C.z = 20.0f;
        Matrix_MultVec3f(gCalcMatrix, &sp3C, &player->hit4);
    }
    if ((player->form == FORM_ARWING) || (player->form == FORM_BLUE_MARINE)) {
        Matrix_RotateY(gCalcMatrix, (player->yRot_114 + 180.0f) * M_DTOR, MTXF_APPLY);
        Matrix_RotateZ(gCalcMatrix, -(player->bankAngle * M_DTOR), MTXF_APPLY);
        sp3C.y = 0.0f;
        sp3C.z = 0.0f;
        if (player->wings.leftState == WINGSTATE_INTACT) {
            sp3C.x = 40.0f;
        } else {
            sp3C.y = -10.0f;
            sp3C.x = 30.0f;
        }
        if (player->form == FORM_BLUE_MARINE) {
            sp3C.x = 24.0f;
        }
        Matrix_MultVec3f(gCalcMatrix, &sp3C, &player->hit2);

        if (player->wings.rightState == WINGSTATE_INTACT) {
            sp3C.x = -40.0f;
        } else {
            sp3C.x = -30.0f;
        }
        if (player->form == FORM_BLUE_MARINE) {
            sp3C.x = -24.0f;
        }
        Matrix_MultVec3f(gCalcMatrix, &sp3C, &player->hit1);

        sp3C.x = 0.0f;
        sp3C.y = 24.0f;
        Matrix_MultVec3f(gCalcMatrix, &sp3C, &player->hit3);
        sp3C.y = -24.0f;
        Matrix_MultVec3f(gCalcMatrix, &sp3C, &player->hit4);
    }
}

void Player_CollisionCheck(Player* player) {
    s32 i;
    s32 j;
    s32 temp_v0;
    f32 spE8;
    f32 spE4;
    f32 spE0;
    Vec3f spfD4;
    Vec3f spC8;
    Vec3f spBC;
    f32 padB8;        // B8
    Actor* actor;     // B4
    f32 padB0;        // B0
    Boss* boss;       // AC
    Sprite* sprite;   // A8
    s32 pad;          // A4
    Scenery* scenery; // A0
    Player* opponent; // 9C
    s32 sp98;
    f32 sp94;
    s32 sp90;
    f32 sp8C;

    Player_UpdateHitbox(player);
    if (gGroundType == 4) {
        switch (player->form) {
            case FORM_LANDMASTER:
                func_tank_800444BC(player);
                break;
            case FORM_BLUE_MARINE: // This should probably be FORM_ON_FOOT
                if (Ground_801B6AEC(player->pos.x, player->pos.y - 12.0f, player->trueZpos + player->zPath)) {
                    Ground_801B6E20(player->pos.x, player->trueZpos + player->zPath, &spE8, &spE0, &spE4);
                    player->pos.y = spE0 + 10.0f;
                }
                break;
        }
    } else if (player->form == FORM_ARWING) {
        if ((player->hit1.y < (gGroundHeight + 13.0f)) && (player->state_1C8 != PLAYERSTATE_1C8_DOWN)) {
            if (gGroundSurface == SURFACE_WATER) {
                player->hitTimer = 7;
                player->rot.x = (player->baseSpeed + player->boostSpeed) * 0.5f;
            } else {
                Player_ApplyDamage(player, 1, 21);
            }
            if (gCurrentLevel == LEVEL_FORTUNA) {
                func_effect_8007BC7C(player->hit1.x, player->hit1.y, player->hit1.z, 6.0f);
                func_effect_8007BC7C(player->hit1.x, player->hit1.y, player->hit1.z, 6.0f);
                func_effect_8007BC7C(player->hit1.x, player->hit1.y, player->hit1.z, 6.0f);
            }
        }
        if ((player->hit2.y < (gGroundHeight + 13.0f)) && (player->state_1C8 != PLAYERSTATE_1C8_DOWN)) {
            if (gGroundSurface == SURFACE_WATER) {
                player->hitTimer = 7;
                player->rot.x = (player->baseSpeed + player->boostSpeed) * 0.5f;
            } else {
                Player_ApplyDamage(player, 2, 21);
            }
            if (gCurrentLevel == LEVEL_FORTUNA) {
                func_effect_8007BC7C(player->hit2.x, player->hit2.y, player->hit2.z, 6.0f);
                func_effect_8007BC7C(player->hit2.x, player->hit2.y, player->hit2.z, 6.0f);
                func_effect_8007BC7C(player->hit2.x, player->hit2.y, player->hit2.z, 6.0f);
            }
        }
    } else if ((player->form == FORM_LANDMASTER) && !gVersusMode) {
        func_tank_800444BC(player);
    }

    if ((player->timer_498 == 0) || ((gCamCount != 1) && (player->form != FORM_ARWING))) {
        if (gLevelMode == LEVELMODE_ALL_RANGE) {
            Scenery360* scenery360;

            sp8C = 1100.0f;
            if ((gCurrentLevel == LEVEL_SECTOR_Y) || (gCurrentLevel == LEVEL_VENOM_ANDROSS)) {
                sp8C = 4000.0f;
            }
            for (i = 0, scenery360 = gScenery360; i < 200; i++, scenery360++) {
                if (scenery360->obj.status == OBJ_ACTIVE) {
                    spC8.x = scenery360->obj.pos.x - player->pos.x;
                    spC8.z = scenery360->obj.pos.z - player->trueZpos;
                    if (sqrtf(SQ(spC8.x) + SQ(spC8.z)) < sp8C) {
                        if ((scenery360->obj.id == OBJ_SCENERY_117) || (scenery360->obj.id == OBJ_SCENERY_143) ||
                            (scenery360->obj.id == OBJ_SCENERY_141) || (scenery360->obj.id == OBJ_SCENERY_149) ||
                            (scenery360->obj.id == OBJ_SCENERY_150) || (scenery360->obj.id == OBJ_SCENERY_148) ||
                            (scenery360->obj.id == OBJ_SCENERY_160) || (scenery360->obj.id == OBJ_SCENERY_1) ||
                            (scenery360->obj.id == OBJ_SCENERY_3) || (scenery360->obj.id == OBJ_SCENERY_140)) {
                            temp_v0 = Player_CheckPolyCollision(player, scenery360->obj.id, scenery360->obj.pos.x,
                                                                scenery360->obj.pos.y, scenery360->obj.pos.z,
                                                                scenery360->obj.rot.x, scenery360->obj.rot.y,
                                                                scenery360->obj.rot.z);
                            if (temp_v0 != 0) {
                                if ((player->form == FORM_LANDMASTER) || (player->form == FORM_ON_FOOT)) {
                                    Player_GroundedCollision(player, temp_v0, scenery360->obj.pos.x,
                                                             scenery360->obj.pos.z);
                                } else {
                                    Player_ApplyDamage(player, temp_v0, scenery360->info.damage);
                                }
                            }
                            if ((gCurrentLevel == LEVEL_FORTUNA) || (gCurrentLevel == LEVEL_VENOM_2)) {
                                temp_v0 = Player_CheckHitboxCollision(
                                    player, scenery360->info.hitbox, &sp98, scenery360->obj.pos.x,
                                    scenery360->obj.pos.y, scenery360->obj.pos.z, scenery360->obj.rot.x,
                                    scenery360->obj.rot.y, scenery360->obj.rot.z, 0.0f, 0.0f, 0.0f);
                                if ((temp_v0 != 0) && (temp_v0 < 0)) {
                                    if (player->whooshTimer == 0) {
                                        func_effect_8007A6F0(&scenery360->obj.pos, NA_SE_PASS);
                                    }
                                    player->whooshTimer += 2;
                                    if (player->whooshTimer >= 4) {
                                        player->whooshTimer = 4;
                                    }
                                }
                            }
                        } else {
                            temp_v0 = Player_CheckHitboxCollision(
                                player, scenery360->info.hitbox, &sp98, scenery360->obj.pos.x, scenery360->obj.pos.y,
                                scenery360->obj.pos.z, scenery360->obj.rot.x, scenery360->obj.rot.y,
                                scenery360->obj.rot.z, 0.0f, 0.0f, 0.0f);
                            if (temp_v0 != 0) {
                                if (temp_v0 < 0) {
                                    if (player->whooshTimer == 0) {
                                        func_effect_8007A6F0(&scenery360->obj.pos, NA_SE_PASS);
                                    }
                                    player->whooshTimer += 2;
                                    if (player->whooshTimer >= 4) {
                                        player->whooshTimer = 4;
                                    }
                                } else if ((player->form == FORM_LANDMASTER) || (player->form == FORM_ON_FOOT)) {
                                    Player_GroundedCollision(player, temp_v0, scenery360->obj.pos.x,
                                                             scenery360->obj.pos.z);
                                } else {
                                    Player_ApplyDamage(player, temp_v0, scenery360->info.damage);
                                    if (scenery360->obj.id == OBJ_SCENERY_131) {
                                        Matrix_RotateY(gCalcMatrix, (scenery360->obj.rot.y + 180.0f) * M_DTOR,
                                                       MTXF_NEW);
                                        Matrix_MultVec3f(gCalcMatrix, &D_800D3040[sp98 - 1], &spBC);
                                        player->knockback.x = spBC.x;
                                        player->knockback.y = spBC.y;
                                        player->knockback.z = spBC.z;

                                        player->rot.y = player->rot.x = 0.0f;
                                        player->pos.x = player->basePos.x;
                                        player->pos.y = player->basePos.y;
                                        player->pos.z = player->basePos.z;
                                        player->yRot_114 = scenery360->obj.rot.y + 180.0f;
                                        player->timer_498 = 5;
                                    }
                                    if ((scenery360->obj.id == OBJ_SCENERY_135) ||
                                        (scenery360->obj.id == OBJ_SCENERY_136)) {
                                        if (scenery360->obj.id == OBJ_SCENERY_135) {
                                            Matrix_RotateY(gCalcMatrix, (scenery360->obj.rot.y + 180.0f) * M_DTOR,
                                                           MTXF_NEW);
                                            Matrix_MultVec3f(gCalcMatrix, &D_800D3088[sp98 - 1], &spBC);
                                        } else {
                                            Matrix_RotateY(gCalcMatrix, scenery360->obj.rot.y * M_DTOR, MTXF_NEW);
                                            Matrix_MultVec3f(gCalcMatrix, &D_800D30B8[sp98 - 1], &spBC);
                                        }
                                        player->knockback.x = spBC.x;
                                        player->knockback.y = spBC.y;
                                        player->knockback.z = spBC.z;
                                        player->rot.y = 0.0f;
                                        player->rot.x = 0.0f;
                                        player->pos.x = player->basePos.x;
                                        player->pos.y = player->basePos.y;
                                        player->pos.z = player->basePos.z;
                                        if (scenery360->obj.id == OBJ_SCENERY_135) {
                                            player->yRot_114 = scenery360->obj.rot.y + 180.0f;
                                        } else {
                                            player->yRot_114 = scenery360->obj.rot.y;
                                        }
                                        player->timer_498 = 5;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else {
            for (i = 0, scenery = gScenery; i < ARRAY_COUNT(gScenery); i++, scenery++) {
                if ((scenery->obj.status == OBJ_ACTIVE) && (scenery->obj.id != OBJ_SCENERY_58) &&
                    (scenery->obj.id != OBJ_SCENERY_105) && (scenery->obj.id != OBJ_SCENERY_59) &&
                    (scenery->obj.id != OBJ_SCENERY_60) && (scenery->obj.id != OBJ_SCENERY_61) &&
                    (scenery->obj.id != OBJ_SCENERY_66) && (scenery->obj.id != OBJ_SCENERY_67) &&
                    (scenery->obj.id != OBJ_SCENERY_70) && (scenery->obj.id != OBJ_SCENERY_72) &&
                    (scenery->obj.id != OBJ_SCENERY_71) && (scenery->obj.id != OBJ_SCENERY_73) &&
                    (scenery->obj.id != OBJ_SCENERY_74) && (scenery->obj.id != OBJ_SCENERY_69) &&
                    ((player->trueZpos - 2000.0f) < scenery->obj.pos.z)) {
                    if ((scenery->obj.id == OBJ_SCENERY_1) || (scenery->obj.id == OBJ_SCENERY_4) ||
                        (scenery->obj.id == OBJ_SCENERY_5) || (scenery->obj.id == OBJ_SCENERY_47) ||
                        (scenery->obj.id == OBJ_SCENERY_117) || (scenery->obj.id == OBJ_SCENERY_120) ||
                        (scenery->obj.id == OBJ_SCENERY_124) || (scenery->obj.id == OBJ_SCENERY_126) ||
                        (scenery->obj.id == OBJ_SCENERY_2) || (scenery->obj.id == OBJ_SCENERY_3)) {
                        spC8.x = scenery->obj.pos.x - player->pos.x;
                        spC8.z = scenery->obj.pos.z - player->trueZpos;
                        if (sqrtf(SQ(spC8.x) + SQ(spC8.z)) < 1100.0f) {
                            temp_v0 = Player_CheckPolyCollision(
                                player, scenery->obj.id, scenery->obj.pos.x, scenery->obj.pos.y, scenery->obj.pos.z,
                                scenery->obj.rot.x, scenery->obj.rot.y, scenery->obj.rot.z);
                            if (temp_v0 != 0) {
                                Player_ApplyDamage(player, temp_v0, scenery->info.damage);
                            }
                        }
                    } else {
                        padB0 = scenery->obj.rot.y;
                        if (scenery->info.action == (ObjectFunc) func_enmy_80066EA8) {
                            padB0 = 0.0f;
                        }
                        temp_v0 = Player_CheckHitboxCollision(
                            player, scenery->info.hitbox, &sp98, scenery->obj.pos.x, scenery->obj.pos.y,
                            scenery->obj.pos.z, scenery->obj.rot.x, padB0, scenery->obj.rot.z, 0.0f, 0.0f, 0.0f);
                        if (temp_v0 != 0) {
                            if (temp_v0 < 0) {
                                if (temp_v0 == -1) {
                                    gLight2colorStep = 40;
                                    gLight2RTarget = 20;
                                    gLight2GTarget = 20;
                                    gLight2BTarget = 20;
                                    player->shadowing = 80;
                                }
                                if (player->whooshTimer == 0) {
                                    AUDIO_PLAY_SFX(NA_SE_PASS, scenery->sfxSource, 0);
                                }
                                player->whooshTimer += 2;
                                if (player->whooshTimer >= 4) {
                                    player->whooshTimer = 4;
                                }
                            } else if (scenery->obj.id == OBJ_SCENERY_54) {
                                if (player->whooshTimer == 0) {
                                    AUDIO_PLAY_SFX(NA_SE_IN_SPLASH_L, scenery->sfxSource, 0);
                                }
                                player->whooshTimer += 2;
                                if (player->whooshTimer >= 4) {
                                    player->whooshTimer = 4;
                                }
                            } else {
                                Player_ApplyDamage(player, temp_v0, scenery->info.damage);
                                if ((scenery->obj.id == OBJ_SCENERY_48) || (scenery->obj.id == OBJ_SCENERY_55) ||
                                    (scenery->obj.id == OBJ_SCENERY_49)) {
                                    Matrix_RotateY(gCalcMatrix, scenery->obj.rot.y * M_DTOR, MTXF_NEW);
                                    spC8.x = -(player->baseSpeed + player->boostSpeed) * 0.7f;
                                    spC8.y = 0.0f;
                                    spC8.z = 0.0f;

                                    Matrix_MultVec3f(gCalcMatrix, &spC8, &spBC);
                                    player->knockback.x = spBC.x;
                                    player->knockback.y = spBC.y;
                                    player->pos.x = player->basePos.x;
                                    player->timer_498 = 5;
                                } else if (scenery->obj.id == OBJ_SCENERY_50) {
                                    if (player->pos.x < scenery->obj.pos.x) {
                                        player->knockback.x = -30.0f;
                                        player->rot.y = 45.0f;
                                    } else {
                                        player->knockback.x = 30.0f;
                                        player->rot.y = -45.0f;
                                    }
                                    player->knockback.y = 0.0f;
                                    player->pos.x = player->basePos.x;
                                    player->timer_498 = 5;
                                } else if (scenery->obj.id == OBJ_SCENERY_131) {
                                    Matrix_RotateY(gCalcMatrix, (scenery->obj.rot.y + 180.0f) * M_DTOR, MTXF_NEW);
                                    Matrix_RotateZ(gCalcMatrix, -scenery->obj.rot.z * M_DTOR, MTXF_APPLY);
                                    Matrix_MultVec3f(gCalcMatrix, &D_800D3040[sp98 - 1], &spBC);
                                    player->knockback.x = spBC.x;
                                    player->knockback.y = spBC.y;
                                    player->rot.y = 0.0f;
                                    player->rot.x = 0.0f;
                                    player->timer_498 = 5;
                                    player->pos.x = player->basePos.x;
                                    player->pos.y = player->basePos.y;
                                }
                            }
                        }
                    }
                }
            }
        }
        for (i = 0, boss = gBosses; i < ARRAY_COUNT(gBosses); i++, boss++) {
            if (boss->obj.status == OBJ_ACTIVE) {
                if ((boss->obj.id == OBJ_BOSS_VE2) || (boss->obj.id == OBJ_BOSS_FO) || (boss->obj.id == OBJ_BOSS_SZ) ||
                    (boss->obj.id == OBJ_BOSS_309)) {
                    temp_v0 =
                        Player_CheckPolyCollision(player, boss->obj.id, boss->obj.pos.x, boss->obj.pos.y,
                                                  boss->obj.pos.z, boss->obj.rot.x, boss->obj.rot.y, boss->obj.rot.z);
                    if (temp_v0 != 0) {
                        Player_ApplyDamage(player, temp_v0, boss->info.damage);
                        break;
                    }
                }
                if (boss->obj.id == OBJ_BOSS_310) {
                    spfD4.x = fabsf(boss->obj.pos.x - player->pos.x) * .8333333f;
                    spfD4.y = fabsf(boss->obj.pos.y - player->pos.y) * 2;
                    spfD4.z = fabsf(boss->obj.pos.z - player->trueZpos) * 0.8333333f;
                    if ((VEC3F_MAG(&spfD4)) < 1500.0f) {
                        Player_ApplyDamage(player, 0, boss->info.damage);
                        player->boostSpeed = 0.0f;
                        player->timer_498 = 5;
                        player->knockback.y = 30.0f;
                        boss->dmgType = DMG_BEAM;
                        func_effect_8007BFFC(player->pos.x + RAND_FLOAT_CENTERED(10.0f),
                                             player->pos.y + RAND_FLOAT(10.0f),
                                             player->trueZpos + RAND_FLOAT_CENTERED(10.0f), 0.0f, 15.0f, 0.0f, 2.0f, 5);
                        for (j = 0; j < 10; j++) {
                            func_effect_8007C484(
                                player->pos.x + RAND_FLOAT_CENTERED(30.0f), player->pos.y + RAND_FLOAT(10.0f),
                                player->trueZpos + RAND_FLOAT_CENTERED(30.0f), player->vel.x, 20.0f + player->vel.y,
                                player->vel.z, RAND_FLOAT(0.1f) + 0.1f, player->num + 11);
                        }
                        break;
                    }
                } else {
                    if (boss->obj.id == OBJ_BOSS_KA) {
                        spfD4.x = fabsf(boss->obj.pos.x - player->pos.x);
                        spfD4.y = fabsf(boss->obj.pos.y - 300.0f - player->pos.y) * 7.42f;
                        spfD4.z = fabsf(boss->obj.pos.z - player->trueZpos);
                        if ((VEC3F_MAG(&spfD4)) < 2700.0f) {
                            Player_ApplyDamage(player, 3, boss->info.damage);
                        }
                    }
                    temp_v0 = Player_CheckHitboxCollision(player, boss->info.hitbox, &sp98, boss->obj.pos.x,
                                                          boss->obj.pos.y, boss->obj.pos.z, boss->obj.rot.x,
                                                          boss->obj.rot.y, boss->obj.rot.z, 0.0f, 0.0f, 0.0f);
                    if (temp_v0 != 0) {
                        if (temp_v0 < 0) {
                            if (player->whooshTimer == 0) {
                                AUDIO_PLAY_SFX(NA_SE_PASS, boss->sfxSource, 0);
                            }
                            player->whooshTimer += 2;
                            if (player->whooshTimer >= 4) {
                                player->whooshTimer = 4;
                            }
                        } else {
                            if ((boss->obj.id == OBJ_BOSS_320) && (boss->timer_056 != 0) && (sp98 == 5)) {
                                break;
                            }
                            Player_ApplyDamage(player, temp_v0, boss->info.damage);
                            if ((boss->obj.id == OBJ_BOSS_303) && ((boss->state == 2) || (boss->state == 3)) &&
                                (sp98 >= 9)) {
                                player->knockback.y = -100.0f;
                            }
                            if ((boss->obj.id == OBJ_BOSS_320) && (sp98 < 5)) {
                                player->knockback.x = boss->fwork[14];
                                player->knockback.y = boss->fwork[15];
                            }
                        }
                    }
                }
            }
        }
        for (i = 0, actor = gActors; i < ARRAY_COUNT(gActors); i++, actor++) {
            if ((actor->obj.status == OBJ_ACTIVE) && (actor->timer_0C2 == 0)) {
                if (actor->obj.id == OBJ_ACTOR_180) {
                    temp_v0 = Player_CheckPolyCollision(player, actor->obj.id, actor->obj.pos.x, actor->obj.pos.y,
                                                        actor->obj.pos.z, actor->obj.rot.x, actor->obj.rot.y,
                                                        actor->obj.rot.z);
                    if (temp_v0 != 0) {
                        Player_ApplyDamage(player, temp_v0, actor->info.damage);
                    }
                } else if (actor->obj.id == OBJ_ACTOR_EVENT) {
                    if (actor->eventType == EVID_42) {
                        temp_v0 = Player_CheckPolyCollision(player, ACTOR_EVENT_ID, actor->obj.pos.x, actor->obj.pos.y,
                                                            actor->obj.pos.z, actor->obj.rot.x, actor->obj.rot.y,
                                                            actor->obj.rot.z);
                        if (temp_v0 != 0) {
                            Player_ApplyDamage(player, temp_v0, actor->info.damage);
                        }
                    } else if (actor->eventType == EVID_63) {
                        spfD4.x = fabsf(actor->obj.pos.x - player->pos.x);
                        spfD4.y = fabsf(actor->obj.pos.y - player->pos.y);
                        spfD4.z = fabsf(actor->obj.pos.z - player->trueZpos);
                        if ((VEC3F_MAG(&spfD4)) < 900.0f) {
                            Player_ApplyDamage(player, 0, actor->info.damage);
                            actor->dmgType = DMG_COLLISION;
                        }
                    } else {
                        temp_v0 = Player_CheckHitboxCollision(
                            player, actor->info.hitbox, &sp98, actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z,
                            actor->obj.rot.x, actor->obj.rot.y, actor->obj.rot.z, actor->vwork[29].x,
                            actor->vwork[29].y, actor->vwork[29].z + actor->rot_0F4.z);
                        if (temp_v0 != 0) {
                            if ((temp_v0 < 0) && (actor->eventType == EVID_SX_WARP_GATE)) {
                                actor->info.hitbox = LOAD_ASSET(D_SX_6032328);
                                if (gRingPassCount >= 0) {
                                    actor->unk_046 = 2;
                                    gRingPassCount++;
                                    if (gRingPassCount == 3) {
                                        Radio_PlayMessage(gMsg_ID_5504, RCID_FALCO);
                                    }
                                    AUDIO_PLAY_SFX(gWarpRingSfx[gRingPassCount], gPlayer[0].sfxSource, 0);
                                    AUDIO_PLAY_SFX(NA_SE_RING_PASS, gDefaultSfxSource, 4);
                                }
                            } else if (temp_v0 < 0) {
                                if (player->whooshTimer == 0) {
                                    AUDIO_PLAY_SFX(NA_SE_PASS, actor->sfxSource, 0);
                                }
                                player->whooshTimer += 2;
                                if (player->whooshTimer >= 4) {
                                    player->whooshTimer = 4;
                                }
                            } else {
                                Player_ApplyDamage(player, temp_v0, actor->info.damage);
                                actor->dmgType = DMG_COLLISION;
                                actor->dmgSource = player->num + 1;
                            }
                        }
                    }
                } else if ((OBJ_ACTOR_205 <= actor->obj.id) && (actor->obj.id <= OBJ_ACTOR_213)) {
                    temp_v0 = Player_CheckHitboxCollision(
                        player, actor->info.hitbox, &sp98, actor->fwork[25] + actor->obj.pos.x,
                        actor->fwork[8] + actor->obj.pos.y + 25.0f, actor->obj.pos.z, actor->fwork[29],
                        actor->fwork[26], actor->obj.rot.z, 0.0f, 0.0f, 0.0f);
                    if (temp_v0 != 0) {
                        actor->dmgType = DMG_COLLISION;
                        if (actor->info.damage) {
                            Player_ApplyDamage(player, temp_v0, actor->info.damage);
                        } else {
                            actor->dmgType = -1;
                        }
                    }
                } else {
                    temp_v0 = Player_CheckHitboxCollision(player, actor->info.hitbox, &sp98, actor->obj.pos.x,
                                                          actor->obj.pos.y, actor->obj.pos.z, actor->obj.rot.x,
                                                          actor->obj.rot.y, actor->obj.rot.z, 0.0f, 0.0f, 0.0f);
                    if (temp_v0 != 0) {
                        if (temp_v0 < 0) {
                            if (player->whooshTimer == 0) {
                                AUDIO_PLAY_SFX(NA_SE_PASS, actor->sfxSource, 0);
                            }
                            player->whooshTimer += 2;
                            if (player->whooshTimer >= 4) {
                                player->whooshTimer = 4;
                            }
                        } else {
                            actor->dmgType = DMG_COLLISION;
                            if (actor->obj.id == OBJ_ACTOR_190) {
                                actor->dmgType = -1;
                            }
                            if (actor->info.damage) {
                                Player_ApplyDamage(player, temp_v0, actor->info.damage);
                                if (actor->obj.id == OBJ_ACTOR_225) {
                                    player->knockback.y = 0.0f;
                                }
                            } else {
                                actor->dmgType = -1;
                            }
                        }
                    }
                }
            }
        }
        for (i = 0, sprite = gSprites; i < ARRAY_COUNT(gSprites); i++, sprite++) {
            if (sprite->obj.status == OBJ_ACTIVE) {
                if ((player->trueZpos - 200.0f) < sprite->obj.pos.z) {
                    temp_v0 = Player_CheckHitboxCollision(player, sprite->info.hitbox, &sp98, sprite->obj.pos.x,
                                                          sprite->obj.pos.y, sprite->obj.pos.z, 0.0f, 0.0f, 0.0f, 0.0f,
                                                          0.0f, 0.0f);
                    if (temp_v0 != 0) {
                        if ((sprite->obj.id == OBJ_SPRITE_FO_POLE) || (sprite->obj.id == OBJ_SPRITE_CO_POLE) ||
                            (sprite->obj.id == OBJ_SPRITE_TI_CACTUS) || (sprite->obj.id == OBJ_SPRITE_CO_TREE)) {
                            sprite->destroy = 1;
                            player->hitTimer = 6;
                            player->unk_21C = 0;
                        } else {
                            Player_ApplyDamage(player, temp_v0, sprite->info.damage);
                        }
                    }
                }
            }
        }
    }
    Player_CheckItemCollect(player);
    if (gCamCount == 4) {
        for (opponent = &gPlayer[3], i = 3; i >= 0; i--, opponent--) {
            if ((i != gPlayerNum) && (opponent->state_1C8 == PLAYERSTATE_1C8_ACTIVE)) {
                spC8.x = 25.0f;
                if (player->form == FORM_ON_FOOT) {
                    spC8.x = 4.0f;
                }
                spC8.y = 25.0f;
                if (opponent->form == FORM_ON_FOOT) {
                    spC8.y = 4.0f;
                }
                spBC.x = spBC.z = spC8.x + spC8.y;
                spC8.x = 23.0f;
                if (player->form == FORM_ON_FOOT) {
                    spC8.x = 7.0f;
                }
                spC8.y = 23.0f;
                if (opponent->form == FORM_ON_FOOT) {
                    spC8.y = 7.0f;
                }
                spBC.y = spC8.x + spC8.y;
                if ((fabsf(opponent->trueZpos - player->trueZpos) <= spBC.z) &&
                    (fabsf(opponent->pos.y - player->pos.y) <= spBC.y) &&
                    (fabsf(opponent->pos.x - player->pos.x) <= spBC.x)) {
                    if ((player->form == FORM_ON_FOOT) && (opponent->form == FORM_ON_FOOT)) {
                        player->pos.x = player->basePos.x;
                        player->pos.y = player->basePos.y;
                        player->pos.z = player->trueZpos = player->basePos.z;
                        opponent->pos.x = opponent->basePos.x;
                        opponent->pos.y = opponent->basePos.y;
                        opponent->pos.z = opponent->trueZpos = opponent->basePos.z;
                        player->knockback.x = (player->pos.x - opponent->basePos.x) * 0.5f;
                        player->knockback.z = (player->trueZpos - opponent->trueZpos) * 0.5f;
                        opponent->knockback.x = -player->knockback.x;
                        opponent->knockback.z = -player->knockback.z;
                        opponent->baseSpeed = player->baseSpeed = 2.0f;
                    } else {
                        Player_Collide(player, opponent);
                        Player_Collide(opponent, player);
                    }
                }
            }
        }
    }
    if (gUseDynaFloor) {
        if (Play_CheckDynaFloorCollision(&sp94, &sp90, player->hit4.x, player->hit4.y, player->hit4.z)) {
            if (gCurrentLevel == LEVEL_ZONESS) {
                player->rot.x = (player->baseSpeed + player->boostSpeed) * 0.8f;
                player->hitTimer = 15;
                func_effect_8007B228(player->hit4.x, sp94, player->hit4.z, 1.0f);
            } else {
                if (player->hitTimer == 0) {
                    Player_ApplyDamage(player, 4, 10);
                }
                player->knockback.y = 30.0f;
                player->rot.x = (player->baseSpeed + player->boostSpeed) * 0.8f;
            }
            if (player->state_1C8 == PLAYERSTATE_1C8_DOWN) {
                player->radioDamageTimer = 2;
                func_effect_8007AFD0(player->pos.x, player->trueZpos, 30.0f, 0.0f, 5.0f);
                func_effect_8007AFD0(player->pos.x, player->trueZpos, -30.0f, 0.0f, 5.0f);
            }
        }
        if (Play_CheckDynaFloorCollision(&sp94, &sp90, player->pos.x + ((player->hit1.x - player->pos.x) * 1.5f),
                                         player->pos.y + (player->hit1.y - player->pos.y) * 1.5f, player->hit1.z)) {
            if (gCurrentLevel == LEVEL_ZONESS) {
                func_effect_8007B228(player->pos.x + (player->hit1.x - player->pos.x) * 1.5f, sp94, player->hit1.z,
                                     1.0f);
            } else {
                if (player->hitTimer == 0) {
                    Player_ApplyDamage(player, 1, 10);
                }
                player->knockback.y = 30.0f;
            }
        }
        if (Play_CheckDynaFloorCollision(&sp94, &sp90, player->pos.x + ((player->hit2.x - player->pos.x) * 1.5f),
                                         player->pos.y + (player->hit2.y - player->pos.y) * 1.5f, player->hit2.z)) {
            if (gCurrentLevel == LEVEL_ZONESS) {
                func_effect_8007B228(player->pos.x + (player->hit2.x - player->pos.x) * 1.5f, sp94, player->hit2.z,
                                     1.0f);
            } else {
                if (player->hitTimer == 0) {
                    Player_ApplyDamage(player, 2, 40);
                }
                player->knockback.y = 30.0f;
            }
        }
    }
}

void Player_FloorCheck(Player* player) {
    s32 sp144;
    Scenery360* scenery360;
    Scenery* scenery;
    s32 count;
    s32 colId;
    s32 i;
    f32 tempx;
    f32 tempy;
    f32 tempz;
    f32 sp120;
    f32* hitboxData;
    Hitbox* hitbox;
    f32 var_fs0;
    f32 var_fs1;
    f32 tempx2;
    f32 tempy2;
    f32 tempz2;
    f32 sp100;
    f32 spFC;
    f32 spF8;
    Vec3f spEC;
    Vec3f spE0;
    Vec3f spD4;
    Vec3f spC8;
    Vec3f spBC;
    Vec3f spB0;
    f32 spA8[2];
    Vec3f sp9C = { 0.0f, -10.0f, 0.0f };
    Vec3f* rot;
    s32 pad3;
    s32 pad4;

    if (player->unk_240 == 0) {
        player->groundPos.x = player->pos.x;
        player->groundPos.z = player->trueZpos - player->pos.y;
        if (gGroundType != 4) {
            if (gCamCount == 1) {
                player->groundPos.y = gGroundHeight + 3.0f;
            } else {
                player->groundPos.y = gGroundHeight;
                if (player->form == FORM_ON_FOOT) {
                    player->groundPos.z = player->trueZpos;
                }
            }
            player->unk_248 = player->unk_24C = player->groundRotY = 0.0f;
        }
        sp100 = 0.0f;
        spFC = 0.0f;
        spF8 = 0.0f;
        if (gCamCount != 1) {
            if (player->form == FORM_ON_FOOT) {
                for (sp144 = 0; sp144 < 200; sp144++) {
                    scenery360 = &gScenery360[sp144];
                    if ((scenery360->obj.status == OBJ_ACTIVE) &&
                        ((scenery360->obj.id == OBJ_SCENERY_143) || (scenery360->obj.id == OBJ_SCENERY_140) ||
                         (scenery360->obj.id == OBJ_SCENERY_141)) &&
                        (fabsf(scenery360->obj.pos.x - player->pos.x) < 2000.0f) &&
                        (fabsf(scenery360->obj.pos.z - player->trueZpos) < 2000.0f)) {
                        spC8.x = scenery360->obj.pos.x;
                        spC8.y = scenery360->obj.pos.y;
                        spC8.z = scenery360->obj.pos.z;
                        spD4.x = player->pos.x;
                        spD4.y = gGroundHeight;
                        spD4.z = player->trueZpos;
                        colId = COL2_4;
                        if (scenery360->obj.id == OBJ_SCENERY_141) {
                            colId = COL2_6;
                        } else if (scenery360->obj.id == OBJ_SCENERY_143) {
                            colId = COL2_17;
                        }
                        if (func_col2_800A3690(&spD4, &spC8, colId, &spBC)) {
                            player->groundPos.y = spBC.y + 1.0f;
                            player->unk_248 = spBC.x;
                            player->unk_24C = spBC.z;
                            break;
                        }
                    }
                }
            }
        } else {
            if ((gLevelMode == LEVELMODE_ALL_RANGE) && (gLevelType == LEVELTYPE_PLANET)) {
                player->groundPos.x = player->pos.x;
                player->groundPos.z = player->trueZpos;
                for (sp144 = 0, scenery360 = gScenery360; sp144 < 200; sp144++, scenery360++) {
                    if ((scenery360->obj.status == OBJ_ACTIVE) &&
                        ((scenery360->obj.id == OBJ_SCENERY_150) || (scenery360->obj.id == OBJ_SCENERY_149) ||
                         (scenery360->obj.id == OBJ_SCENERY_148) || (scenery360->obj.id == OBJ_SCENERY_1) ||
                         (scenery360->obj.id == OBJ_SCENERY_3)) &&
                        (fabsf(scenery360->obj.pos.x - player->pos.x) < 2500.0f) &&
                        (fabsf(scenery360->obj.pos.z - player->trueZpos) < 2500.0f)) {
                        tempx = scenery360->obj.pos.x;
                        tempy = scenery360->obj.pos.y;
                        tempz = scenery360->obj.pos.z;
                        sp120 = scenery360->obj.rot.y;
                        Matrix_RotateY(gCalcMatrix, -sp120 * M_DTOR, MTXF_NEW);
                        spEC.x = player->pos.x - tempx;
                        spEC.y = 0.0f;
                        spEC.z = player->trueZpos - tempz;
                        Matrix_MultVec3fNoTranslate(gCalcMatrix, &spEC, &spE0);
                        spD4.x = spE0.x + tempx;
                        spD4.y = spE0.y + tempy;
                        spD4.z = spE0.z + tempz;
                        spC8.x = tempx;
                        spC8.y = tempy;
                        spC8.z = tempz;

                        if ((scenery360->obj.id == OBJ_SCENERY_149) || (scenery360->obj.id == OBJ_SCENERY_150)) {
                            if (scenery360->obj.id == OBJ_SCENERY_149) {
                                colId = COL1_5;
                            } else {
                                colId = COL1_6;
                            }
                            if (func_col1_800998FC(&spD4, &spC8, &sp9C, colId, &spB0, spA8) > 0) {
                                player->groundPos.y = spB0.y;
                                player->unk_248 = spA8[0];
                                player->unk_24C = spA8[1];
                                player->groundRotY = DEG_TO_RAD(sp120);
                            }
                        } else {
                            colId = COL2_0;
                            if (scenery360->obj.id == OBJ_SCENERY_3) {
                                colId = COL2_3;
                            }
                            if (func_col2_800A3690(&spD4, &spC8, colId, &spBC)) {
                                player->groundPos.y = spBC.y;
                                player->unk_248 = spBC.x;
                                player->unk_24C = spBC.z;
                                player->groundRotY = DEG_TO_RAD(sp120);
                            }
                        }
                    }
                }
            }
            for (sp144 = 0, scenery = gScenery;
                 (sp144 < 50) && (gLevelMode == LEVELMODE_ON_RAILS) && (gCurrentLevel != LEVEL_VENOM_1);
                 sp144++, scenery++) {
                if ((scenery->obj.status == OBJ_ACTIVE) && ((player->trueZpos - 3000.0f) < scenery->obj.pos.z) &&
                    (scenery->obj.id != OBJ_SCENERY_0) && (scenery->obj.id != OBJ_SCENERY_8)) {
                    tempx = scenery->obj.pos.x;
                    tempy = scenery->obj.pos.y;
                    tempz = scenery->obj.pos.z;
                    sp120 = scenery->obj.rot.y;
                    if ((scenery->obj.id == OBJ_SCENERY_3) || (scenery->obj.id == OBJ_SCENERY_2) ||
                        (scenery->obj.id == OBJ_SCENERY_47) || (scenery->obj.id == OBJ_SCENERY_4) ||
                        (scenery->obj.id == OBJ_SCENERY_5)) {
                        Matrix_RotateY(gCalcMatrix, -sp120 * M_DTOR, MTXF_NEW);
                        for (var_fs1 = var_fs0 = -50.0f; var_fs0 > -500.0f; var_fs0 -= 5.0f, var_fs1 -= 5.0f) {
                            spEC.x = player->pos.x - tempx;
                            spEC.y = player->pos.y + var_fs0 - tempy;
                            spEC.z = player->trueZpos + var_fs1 - tempz;
                            Matrix_MultVec3fNoTranslate(gCalcMatrix, &spEC, &spE0);
                            if ((player->pos.y + var_fs0) <= gGroundHeight) {
                                break;
                            }
                            spD4.x = spE0.x + tempx;
                            spD4.y = spE0.y + tempy;
                            spD4.z = spE0.z + tempz;
                            spC8.x = tempx;
                            spC8.y = tempy;
                            spC8.z = tempz;

                            colId = COL2_0;

                            if (scenery->obj.id == OBJ_SCENERY_47) {
                                colId = COL2_7;
                            }
                            if (scenery->obj.id == OBJ_SCENERY_2) {
                                colId = COL2_2;
                            } else if (scenery->obj.id == OBJ_SCENERY_3) {
                                colId = COL2_3;
                            } else if ((scenery->obj.id == OBJ_SCENERY_4) || (scenery->obj.id == OBJ_SCENERY_5)) {
                                colId = COL2_1;
                            }
                            if (func_col2_800A3690(&spD4, &spC8, colId, &spBC)) {
                                player->groundPos.y = spBC.y;
                                player->groundPos.z = player->trueZpos + var_fs1;
                                player->unk_248 = spBC.x;
                                player->unk_24C = spBC.z;
                                player->groundRotY = DEG_TO_RAD(sp120);
                                break;
                            }
                        }
                    } else {
                        hitboxData = scenery->info.hitbox;
                        count = *hitboxData;
                        if (count != 0) {
                            if (scenery->info.action == (ObjectFunc) func_enmy_80066EA8) {
                                sp120 = 0.0f;
                            }
                            hitboxData++;
                            for (i = 0; i < count; i++, hitboxData += 6) {
                                if (*hitboxData >= HITBOX_SHADOW) {
                                    break;
                                }

                                if (*hitboxData == HITBOX_ROTATED) {
                                    sp100 = hitboxData[1];
                                    spFC = hitboxData[2];
                                    spF8 = hitboxData[3];
                                    hitboxData += 4;
                                    Matrix_RotateZ(gCalcMatrix, -spF8 * M_DTOR, MTXF_NEW);
                                    Matrix_RotateX(gCalcMatrix, -sp100 * M_DTOR, MTXF_APPLY);
                                    Matrix_RotateY(gCalcMatrix, -spFC * M_DTOR, MTXF_APPLY);
                                    Matrix_RotateY(gCalcMatrix, -sp120 * M_DTOR, MTXF_APPLY);
                                } else {
                                    Matrix_RotateY(gCalcMatrix, -sp120 * M_DTOR, MTXF_NEW);
                                }
                                hitbox = (Hitbox*) hitboxData;
                                for (var_fs0 = var_fs1 = -50.0f; var_fs0 > -500.0f; var_fs0 -= 5.0f, var_fs1 -= 5.0f) {
                                    spEC.x = player->pos.x - tempx;
                                    spEC.y = player->pos.y + var_fs0 - tempy;
                                    spEC.z = player->trueZpos + var_fs1 - tempz;
                                    Matrix_MultVec3fNoTranslate(gCalcMatrix, &spEC, &spE0);
                                    tempx2 = spE0.x + tempx;
                                    tempy2 = spE0.y + tempy;
                                    tempz2 = spE0.z + tempz;
                                    if (spEC.y + tempy <= gGroundHeight) {
                                        break;
                                    }

                                    if (Play_CheckSingleHitbox(hitbox, tempx, tempy, tempz, tempx2, tempy2, tempz2)) {
                                        if (gGroundHeight < player->groundPos.y) {
                                            player->groundPos.y = spEC.y + 15.0f + tempy;
                                            player->groundPos.z = spEC.z + 10.0f + tempz;
                                            player->unk_248 = DEG_TO_RAD(sp100);
                                            player->groundRotY = DEG_TO_RAD(sp120);
                                        }
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void Player_InitializeAll(void) {
    u8* ptr = (u8*) gPlayer;
    u32 i;

    for (i = 0; i < gCamCount * sizeof(Player); i++, ptr++) {
        *ptr = 0;
    }
}

void Player_Initialize(Player* player) {
    u8* ptr = (u8*) player;
    u32 i;

    for (i = 0; i < sizeof(Player); i++, ptr++) {
        *ptr = 0;
    }
}

void Play_InitLevel(void) {
    Vtx* mesh;
    u8* ptr;
    s32 i;
    f32* fptr;

    switch (gCurrentLevel) {
        case LEVEL_TRAINING:
            AUDIO_SET_SPEC(SFXCHAN_0, AUDIOSPEC_28);
            gTeamLowHealthMsgTimer = -1;
            break;
        case LEVEL_VENOM_1:
            AUDIO_SET_SPEC(SFXCHAN_0, AUDIOSPEC_6);
            break;
        case LEVEL_VENOM_2:
            AUDIO_SET_SPEC(SFXCHAN_0, AUDIOSPEC_6);
            break;
        case LEVEL_VENOM_ANDROSS:
            AUDIO_SET_SPEC(SFXCHAN_0, AUDIOSPEC_15);
            Audio_SetEnvSfxReverb(0);
            gTeamLowHealthMsgTimer = -1;
            break;
    }
    gUseDynaFloor = 0;
    switch (gCurrentLevel) {
        case LEVEL_SECTOR_Z:
            gGreatFoxIntact = true;
            break;
        case LEVEL_METEO:
        case LEVEL_SECTOR_X:
            if (gLevelPhase == 1) {
                gFogRed = 178;
                gFogGreen = 190;
                gFogBlue = 90;
                gLight1R = 200;
                gLight1G = 200;
                gLight1B = 120;
                gAmbientR = 0;
                gAmbientG = 50;
                gAmbientB = 100;
            }
            break;
        case LEVEL_VENOM_ANDROSS:
            gDrawGround = false;
            gDrawBackdrop = 6;
            D_Andross_801A7F58 = D_Andross_801A7F60 = D_Andross_801A7F68 = D_Andross_801A7F70 = D_Andross_801A7F78 =
                0.0f;
            break;
        case LEVEL_AQUAS:
            gVIsPerFrame = 3;
            D_bg_8015F970 = 1600.0f;
            D_AQ_801C4188 = 128.0f;
            Aquas_801A9824();
            break;
        case LEVEL_TITANIA:
            Titania_80188F30();
            gTeamShields[TEAM_ID_SLIPPY] = -2;
            break;
        case LEVEL_MACBETH:
            Macbeth_80199920();
            break;
        case LEVEL_ZONESS:
            MEM_ARRAY_ALLOCATE(gZOSnakePosRots, 200);
            ptr = (u8*) gZOSnakePosRots;
            for (i = 0; i < 200 * sizeof(*gZOSnakePosRots); i++, ptr++) {
                *ptr = 0;
            }
            gZOSnakeWaypointCount = 0;
            /* fallthrough */
        case LEVEL_SOLAR:
            gUseDynaFloor = true;
            gGroundHeight = -20000.0f;
            fptr = MEM_ARRAY_ALLOCATE(D_ctx_801782CC, 17 * 17);
            for (i = 0; i < 17 * 17; i++, fptr++) {
                *fptr = 0.0f;
            }
            fptr = MEM_ARRAY_ALLOCATE(D_ctx_801782D4, 17 * 17);
            for (i = 0; i < 17 * 17; i++, fptr++) {
                *fptr = 0.0f;
            }
            fptr = MEM_ARRAY_ALLOCATE(D_ctx_801782DC, 17 * 17);
            for (i = 0; i < 17 * 17; i++, fptr++) {
                *fptr = 0.0f;
            }
            fptr = MEM_ARRAY_ALLOCATE(D_ctx_801782E4, 17 * 17);
            for (i = 0; i < 17 * 17; i++, fptr++) {
                *fptr = 0.0f;
            }
            fptr = MEM_ARRAY_ALLOCATE(D_ctx_801782EC, 17 * 17);
            for (i = 0; i < 17 * 17; i++, fptr++) {
                *fptr = 0.0f;
            }

            switch (gCurrentLevel) {
                case LEVEL_SOLAR:
                    mesh = LOAD_ASSET(D_SO_6001C50);
                    break;
                case LEVEL_ZONESS:
                    mesh = LOAD_ASSET(D_ZO_6009ED0);
                    break;
            }
            for (i = 0; i < 17 * 17; i++, mesh++) {
                if (mesh->v.ob[0] == 800) {
                    mesh->v.ob[0] = 1400;
                }
                if (mesh->v.ob[0] == -800) {
                    mesh->v.ob[0] = -1400;
                }
                if (mesh->v.ob[2] == -800) {
                    mesh->v.ob[2] = -1400;
                }
            }

            switch (gCurrentLevel) {
                case LEVEL_SOLAR:
                    mesh = LOAD_ASSET(D_SO_6004500);
                    break;
                case LEVEL_ZONESS:
                    mesh = LOAD_ASSET(D_ZO_600C780);
                    break;
            }
            for (i = 0; i < 17 * 17; i++, mesh++) {
                if (mesh->v.ob[0] == 800) {
                    mesh->v.ob[0] = 1400;
                }
                if (mesh->v.ob[0] == -800) {
                    mesh->v.ob[0] = -1400;
                }
                if (mesh->v.ob[2] == -800) {
                    mesh->v.ob[2] = -1400;
                }
            }
            break;
    }
}

void Player_ResetVsData(void) {
    s32 i;
    s32 j;

    gVsMatchState = 0;
    for (i = 0; i < 4; i++) {
        gVsPoints[i] = 0;
        for (j = 0; j < 10; j++) {
            gVsKills[i][j] = 0;
        }
        gLaserStrength[i] = LASERS_SINGLE;
        gBombCount[i] = 0;
    }
    gVsMatchStart = gVsMatchOver = 0;
}

void Player_InitVersus(void) {
    s32 i;

    Player_ResetVsData();
    for (i = 0; i < 4; i++) {
        gPlayerNum = i;
        Player_Initialize(&gPlayer[i]);
        Player_Setup(&gPlayer[i]);
        Player_Update360(&gPlayer[i]);
        Camera_Update360(&gPlayer[i], 1);
    }
    Play_ClearObjectData();
}

void Play_Init(void) {
    s32 i;

    gArwingSpeed = 40.0f;
    for (i = 0; i < ARRAY_COUNT(gControllerRumbleEnabled); i++) {
        gControllerRumbleEnabled[i] = 0;
    }

    if (gExpertMode) {
        gEnemyShotSpeed = 200;
    } else {
        gEnemyShotSpeed = 100;
    }
    gPauseEnabled = 0;
    gVIsPerFrame = 2;
    D_ctx_80177C70 = 0;
    gTeamHelpActor = NULL;
    gTeamHelpTimer = 0;
    Audio_KillSfxById(NA_SE_OB_ROUTE_EXPLOSION1);
    Audio_KillSfxById(NA_SE_DEMO_SIREN);
    Memory_FreeAll();
    gTraining360MsgTimer = gTraining360MsgIndex = gShowBossHealth = gStarWolfMsgTimer = gAllRangeWingRepairTimer =
        gAllRangeSuppliesSent = 0;
    D_display_800CA220 = 0;
    gShowLevelClearStatusScreen = 0;
    if (gCurrentLevel != LEVEL_VERSUS) {
        gSceneSetup = 0;
    }
    gShowHud = 1;
    gDrawGround = gDrawBackdrop = 1;
    gAqDrawMode = sOverheadCam = 0;
    gCamDistortion = sOverheadCamDist = 0.0f;
    gLevelMode = LEVELMODE_ON_RAILS;
    gPathTexScroll = D_bg_8015F968 = 0.0f;
    D_hud_800D1970 = gVersusMode = gHideRadio = gChangeTo360 = false;
    if (gCurrentLevel >= LEVEL_FORTUNA) {
        gLevelMode = LEVELMODE_ALL_RANGE;
        if (gCurrentLevel == LEVEL_VERSUS) {
            gVersusMode = true;
            Player_ResetVsData();
        }
    }
    if ((gCurrentLevel == LEVEL_VENOM_ANDROSS) && (gLevelPhase == 1)) {
        gLevelMode = LEVELMODE_ALL_RANGE;
    }
    gVsMatchStart = 0;
    Play_InitEnvironment();
    gDropHitCountItem = gTeamLowHealthMsgTimer = gStartAndrossFightTimer = gSoShieldsEmpty = gAllRangeEventTimer =
        gAllRangeFrameCount = gBossActive = gGameFrameCount = gCameraShake = gDynaFloorTimer = gBossFrameCount =
            gCallTimer = gAllRangeSupplyTimer = gMissionStatus = 0;

    if (gCurrentLevel == LEVEL_SECTOR_X) {
        gMissionStatus = MISSION_ACCOMPLISHED;
    }
    gWaterLevel = -25000.0f;
    D_ctx_80177950 = 1.0f;
    if ((gCurrentLevel == LEVEL_VENOM_2) && (gLevelPhase == 2)) {
        gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
    } else {
        gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
    }
    gScreenFlashTimer = gLight3R = gLight3G = gLight3B = D_hud_80161704 = D_hud_80161708 = gFillScreenAlpha =
        gCircleWipeFrame = gShowAllRangeCountdown = gCoUturnCount = 0;

    gCsFrameCount = 0;
    gFillScreenAlpha = gFillScreenAlphaTarget = 255;

    gFillScreenAlphaStep = 16;
    gLight3Brightness = 0.0f;
    gWarpZoneBgAlpha = 0.0f;
    gGroundHeight = 0.0f;
    gStarWarpDistortion = gStarfieldX = gStarfieldY = gStarfieldRoll = gStarfieldScrollX = gStarfieldScrollY = 0.0f;

    if ((gLevelType == LEVELTYPE_SPACE) || (gCurrentLevel == LEVEL_TRAINING)) {
        Play_SetupStarfield();
        if (gCurrentLevel != LEVEL_TRAINING) {
            gDrawGround = false;
        }
    } else {
        gStarCount = 0;
    }
    gFogAlpha = 255;
    gLight1rotStep = 5.0f;
    gLight2rotStep = 5.0f;
    D_ctx_80178538 = 5.0f;
    Play_ClearObjectData();
    D_ctx_801782C8 = 0;
    if (gCurrentLevel == LEVEL_TITANIA) {
        Ground_801B5110(0.0f, 0.0f, 200.0f);
    }
    if (gCurrentLevel == LEVEL_AQUAS) {
        gWaterLevel = 1000.0f;
    }
    gLoadLevelObjects = false;
    gCamCount = 1;
    if (gCurrentLevel == LEVEL_VERSUS) {
        gCamCount = 4;
    }
    for (i = TEAM_ID_FALCO; i < TEAM_ID_MAX; i++) {
        gTeamShields[i] = gSavedTeamShields[i];
    }
    MEM_ARRAY_ALLOCATE(gPlayer, gCamCount);
    Player_InitializeAll();
    for (i = 0; i < gCamCount; i++) {
        gPlayer[i].state_1C8 = PLAYERSTATE_1C8_INIT;
        gPlayerGlareAlphas[i] = D_ctx_801783C0[i] = 0;
        gControllerRumbleTimers[i] = 0;
        gPlayerScores[i] = 0;
    }
    if (gLevelMode == LEVELMODE_ALL_RANGE) {
        MEM_ARRAY_ALLOCATE(gScenery360, 200);
        for (i = 0; i < 200; i++) {
            gScenery360[i].obj.status = OBJ_FREE;
        }
        switch (gCurrentLevel) {
            case LEVEL_SECTOR_Z:
                if (!D_ctx_8017782C) {
                    SectorZ_8019EA68();
                    ActorAllRange_SpawnTeam();
                }
                break;
            case LEVEL_FORTUNA:
                Fortuna_8018BA2C();
                ActorAllRange_SpawnTeam();
                break;
            case LEVEL_KATINA:
                Katina_Init();
                if (!D_ctx_8017782C) {
                    ActorAllRange_SpawnTeam();
                }
                break;
            case LEVEL_BOLSE:
                if (!D_ctx_8017782C) {
                    Bolse_80191ED8();
                    ActorAllRange_SpawnTeam();
                }
                break;
            case LEVEL_VENOM_2:
                Venom2_80196968();
                if (gLevelPhase == 0) {
                    ActorAllRange_SpawnTeam();
                }
                break;
            case LEVEL_VENOM_ANDROSS:
                if (gLevelPhase == 1) {
                    if (gAllRangeCheckpoint == 0) {
                        Andross_801878A8();
                    } else {
                        Andross_801961AC();
                    }
                }
                break;
            case LEVEL_VERSUS:
                Play_InitVsStage();
                gTeamLowHealthMsgTimer = -1;
                break;
        }
    }
    Play_InitLevel();
}

void Player_SetupArwingShot(Player* player, PlayerShot* shot, f32 arg2, f32 arg3, PlayerShotId shotId, f32 speed) {
    Vec3f sp44;
    Vec3f sp38;
    Vec3f sp2C;

    PlayerShot_Initialize(shot);
    Matrix_RotateY(gCalcMatrix, (player->yRot_114 + player->rot.y + 180.0f) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -((player->xRot_120 + player->rot.x + player->aerobaticPitch) * M_DTOR), MTXF_APPLY);
    Matrix_RotateZ(gCalcMatrix, -((player->bankAngle + player->rockAngle) * M_DTOR), MTXF_APPLY);
    Matrix_Translate(gCalcMatrix, player->xShake, player->yBob, 0.0f, MTXF_APPLY);
    if (gVersusMode && (shotId <= PLAYERSHOT_TWIN_LASER)) {
        speed *= 0.5f;
    }
    sp44.x = 0.0f;
    sp44.y = 0.0f;
    sp44.z = speed;
    Matrix_MultVec3f(gCalcMatrix, &sp44, &sp38);
    sp44.x = arg2;
    sp44.y = -5.0f + arg3;
    sp44.z = 0.0f;
    Matrix_MultVec3f(gCalcMatrix, &sp44, &sp2C);
    shot->obj.status = SHOT_ACTIVE;
    shot->vel.x = sp38.x;
    shot->vel.y = sp38.y;
    shot->vel.z = sp38.z;
    shot->unk_60 = 0;
    shot->obj.id = shotId;

    if (!gVersusMode) {
        shot->timer = 35;
    } else {
        shot->timer = 37;
    }
    if (shot->obj.id == PLAYERSHOT_LOCK_SEARCH) {
        shot->obj.pos.x = player->pos.x + sp2C.x;
        shot->obj.pos.y = player->pos.y + sp2C.y;
        shot->obj.pos.z = player->trueZpos + sp2C.z;
        shot->timer = 38;
    } else {
        shot->obj.pos.x = player->pos.x + sp2C.x + (sp38.x * 1.2);
        shot->obj.pos.y = player->pos.y + sp2C.y + (sp38.y * 1.2);
        shot->obj.pos.z = player->trueZpos + sp2C.z + (sp38.z * 1.2f);
    }
    shot->obj.rot.x = player->xRot_120 + player->rot.x + player->aerobaticPitch;
    shot->obj.rot.y = player->rot.y + player->yRot_114;
    shot->obj.rot.z = player->bankAngle;
    if (shotId == PLAYERSHOT_LOCK_ON) {
        if (gCurrentLevel == LEVEL_AQUAS) {
            shot->unk_58 = RAND_INT(360.0f);
            shot->unk_60 = RAND_INT(360.0f);
            shot->vec_2C.x = player->rot.x + player->aerobaticPitch;
            shot->vec_2C.y = player->rot.y;
            shot->vec_2C.z = player->bankAngle;
            shot->unk_5C = D_ctx_80178494;
        } else {
            shot->vec_2C.y = player->rot.y + player->yRot_114;
            shot->vec_2C.x = player->rot.x + player->aerobaticPitch;
            if (speed <= 65.0f) {
                shot->unk_5C = 1;
            }
            shot->timer = 30;
        }
    }
    shot->sourceId = player->num;
}

void Player_SetupTankShot(Player* player, PlayerShot* shot, PlayerShotId shotId, f32 speed) {
    Vec3f sp54;
    Vec3f sp48;
    Vec3f sp3C;

    PlayerShot_Initialize(shot);
    Matrix_RotateX(gCalcMatrix, player->rot.x * M_DTOR, MTXF_NEW);
    Matrix_RotateZ(gCalcMatrix, (player->rot.z + player->rockAngle) * M_DTOR, MTXF_APPLY);
    Matrix_RotateY(gCalcMatrix, player->yRot_114 * M_DTOR, MTXF_APPLY);
    Matrix_RotateY(gCalcMatrix, (player->rot.y + 180.0f) * M_DTOR, MTXF_APPLY);
    Matrix_RotateZ(gCalcMatrix, (-player->zRotBank - player->zRotBarrelRoll) * M_DTOR, MTXF_APPLY);
    Matrix_RotateY(gCalcMatrix, -player->unk_180 * M_DTOR, MTXF_APPLY);
    Matrix_RotateX(gCalcMatrix, player->unk_17C * M_DTOR, MTXF_APPLY);
    sp54.x = 0;
    sp54.y = 0;
    sp54.z = speed;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp54, &sp48);
    Matrix_Translate(gCalcMatrix, 0.0f, player->unk_18C + 30.0f, 0, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, player->rot.x * M_DTOR, MTXF_APPLY);
    Matrix_RotateZ(gCalcMatrix, (player->rot.z + player->rockAngle) * M_DTOR, MTXF_APPLY);
    Matrix_RotateY(gCalcMatrix, player->yRot_114 * M_DTOR, MTXF_APPLY);
    Matrix_RotateY(gCalcMatrix, (player->rot.y + 180.0f) * M_DTOR, MTXF_APPLY);
    Matrix_RotateZ(gCalcMatrix, (-player->zRotBank - player->zRotBarrelRoll) * M_DTOR, MTXF_APPLY);
    Matrix_Translate(gCalcMatrix, 0.0f, -30.0f, 0, MTXF_APPLY);
    Matrix_Translate(gCalcMatrix, player->xShake, player->yBob, 0.0f, MTXF_APPLY);
    Matrix_Translate(gCalcMatrix, 0.0f, 51.0f, -4.0f, MTXF_APPLY);
    Matrix_RotateY(gCalcMatrix, -player->unk_180 * M_DTOR, MTXF_APPLY);
    Matrix_RotateX(gCalcMatrix, player->unk_17C * M_DTOR, MTXF_APPLY);
    sp54.x = 0;
    sp54.y = 7;
    sp54.z = 0;
    Matrix_MultVec3f(gCalcMatrix, &sp54, &sp3C);
    shot->vel.x = sp48.x;
    shot->vel.y = sp48.y;
    shot->vel.z = sp48.z;
    shot->obj.pos.x = player->pos.x + sp3C.x;
    shot->obj.pos.y = player->pos.y + sp3C.y;
    shot->obj.pos.z = player->trueZpos + sp3C.z;
    shot->obj.status = SHOT_ACTIVE;
    shot->vec_2C.x = -player->unk_17C;
    shot->vec_2C.y = -player->unk_180;
    shot->vec_2C.z = player->zRotBank;
    shot->obj.rot.x = player->rot.x + player->xRot_120;
    shot->obj.rot.y = player->rot.y + player->yRot_114;
    shot->obj.rot.z = player->rot.z;
    shot->timer = 40;
    shot->obj.id = shotId;

    shot->sourceId = player->num;
    if (shotId == PLAYERSHOT_LOCK_ON) {
        if (speed <= 65.0f) {
            shot->unk_5C = 1;
        }
        shot->timer = 30;
        shot->vec_2C.y = player->rot.y + player->yRot_114;
    }
}

void Player_TankCannon(Player* player) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gPlayerShots) - 1; i++) {
        if (gPlayerShots[i].obj.status == SHOT_FREE) {
            Player_SetupTankShot(player, &gPlayerShots[i], PLAYERSHOT_TANK, 100.0f);
            Player_PlaySfx(player->sfxSource, NA_SE_TANK_SHOT, player->num);
            player->unk_1A0 = 2;
            break;
        }
    }
}

void Player_ArwingLaser(Player* player) {
    s32 i;
    LaserStrength laser = gLaserStrength[gPlayerNum];

    if (player->wings.unk_14 > -8.0f) {
        laser = LASERS_SINGLE;
    }
    switch (laser) {
        case LASERS_SINGLE:
            for (i = 0; i < ARRAY_COUNT(gPlayerShots) - 1; i++) {
                if (gPlayerShots[i].obj.status == SHOT_FREE) {
                    Player_SetupArwingShot(player, &gPlayerShots[i], 0.0f, 0.0f, PLAYERSHOT_SINGLE_LASER,
                                           400.0f / 3.0f);
                    Player_PlaySfx(player->sfxSource, NA_SE_ARWING_SHOT, player->num);
                    gMuzzleFlashScale[player->num] = 0.5f;
                    break;
                }
            }
            break;
        case LASERS_TWIN:
        case LASERS_HYPER:
            for (i = 0; i < ARRAY_COUNT(gPlayerShots) - 1; i++) {
                if (gPlayerShots[i].obj.status == SHOT_FREE) {
                    Player_SetupArwingShot(player, &gPlayerShots[i], 0.0f, -10.0f, PLAYERSHOT_TWIN_LASER,
                                           400.0f / 3.0f);
                    if (laser == LASERS_TWIN) {
                        Player_PlaySfx(player->sfxSource, NA_SE_ARWING_TWIN_LASER, player->num);
                        gMuzzleFlashScale[player->num] = 0.5f;
                    } else {
                        Player_PlaySfx(player->sfxSource, NA_SE_ARWING_TWIN_LASER2, player->num);
                        gMuzzleFlashScale[player->num] = 0.75f;
                    }
                    break;
                }
            }
            break;
    }
}

void Player_SmartBomb(Player* player) {
    if ((gBombCount[player->num] != 0) && (gBombButton[player->num] & gInputPress->button) &&
        (gPlayerShots[ARRAY_COUNT(gPlayerShots) - 1].obj.status == SHOT_FREE)) {
        if (gVersusMode) {
            gBombCount[player->num] = 0;
        } else {
            gBombCount[player->num]--;
        }
        if (player->form == FORM_ARWING) {
            Player_SetupArwingShot(player, &gPlayerShots[ARRAY_COUNT(gPlayerShots) - 1], 0.0f, 0.0f, PLAYERSHOT_BOMB,
                                   180.0f);
        } else if (player->form == FORM_LANDMASTER) {
            Player_SetupTankShot(player, &gPlayerShots[ARRAY_COUNT(gPlayerShots) - 1], PLAYERSHOT_BOMB, 180.0f);
        } else {
            Player_SetupOnFootShot(player, &gPlayerShots[ARRAY_COUNT(gPlayerShots) - 1], PLAYERSHOT_BOMB);
        }
        gPlayerShots[ARRAY_COUNT(gPlayerShots) - 1].unk_48 = 30.0f;
        gPlayerShots[ARRAY_COUNT(gPlayerShots) - 1].unk_60 = 0;
        Audio_InitBombSfx(player->num, 1);
        Audio_PlayBombFlightSfx(player->num, gPlayerShots[ARRAY_COUNT(gPlayerShots) - 1].sfxSource);
    }
}

void Player_SetupOnFootShot(Player* player, PlayerShot* shot, PlayerShotId shotId) {
    Vec3f sp5C;
    Vec3f sp50;
    Vec3f sp44;

    PlayerShot_Initialize(shot);
    Matrix_RotateY(gCalcMatrix, (player->yRot_114 + player->rot.y + player->damageShake + 180.0f) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -((player->rot.x + player->damageShake) * M_DTOR), MTXF_APPLY);
    Matrix_RotateZ(gCalcMatrix, -((player->bankAngle + player->rockAngle + player->damageShake) * M_DTOR), MTXF_APPLY);
    Matrix_RotateX(gCalcMatrix, player->unk_154 * M_DTOR, MTXF_APPLY);
    sp5C.x = 0.0f;
    sp5C.y = 0.0f;
    if (shotId == PLAYERSHOT_BOMB) {
        sp5C.z = 100.0f;
    } else {
        sp5C.z = 150.0f;
    }
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp5C, &sp50);
    Matrix_RotateY(gCalcMatrix, (player->yRot_114 + player->rot.y + player->damageShake + 180.0f) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -((player->rot.x + player->damageShake) * M_DTOR), MTXF_APPLY);
    Matrix_RotateZ(gCalcMatrix, -((player->bankAngle + player->rockAngle + player->damageShake) * M_DTOR), MTXF_APPLY);
    Matrix_Translate(gCalcMatrix, 0.0f, player->yBob, 0, MTXF_APPLY);
    Matrix_Translate(gCalcMatrix, -10.0f, 25.0f, 0.0f, MTXF_APPLY);
    Matrix_RotateX(gCalcMatrix, player->unk_154 * M_DTOR, MTXF_APPLY);
    sp5C.x = 0.0f;
    sp5C.y = 0.0f;
    sp5C.z = 0;
    Matrix_MultVec3f(gCalcMatrix, &sp5C, &sp44);
    shot->vel.x = sp50.x;
    shot->vel.y = sp50.y;
    shot->vel.z = sp50.z;
    shot->obj.pos.x = player->pos.x + sp44.x;
    shot->obj.pos.y = player->pos.y + sp44.y;
    shot->obj.pos.z = player->trueZpos + sp44.z;

    shot->scale = 1.0f;

    shot->obj.status = SHOT_ACTIVE;
    shot->obj.id = shotId;
    shot->timer = 30;
    shot->unk_58 = 1;

    shot->sourceId = player->num;
}

void Player_OnFootGun(Player* player) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gPlayerShots); i++) {
        if (gPlayerShots[i].obj.status == SHOT_FREE) {
            Player_SetupOnFootShot(player, &gPlayerShots[i], PLAYERSHOT_ON_FOOT);
            Player_PlaySfx(player->sfxSource, NA_SE_TANK_SHOT, player->num);
            player->csTimer = 2;
            player->unk_180 = 10.0f;
            break;
        }
    }
}

bool Player_CanLockOn(s32 playerNum) {
    Actor* actor;
    s32 i;

    for (i = 0, actor = gActors; i < ARRAY_COUNT(gActors); i++, actor++) {
        if ((actor->obj.status == OBJ_ACTIVE) && (actor->lockOnTimers[playerNum] != 0)) {
            return false;
        }
    }
    if (gVersusMode) {
        for (i = 0; i < gCamCount; i++) {
            if (((gPlayer[playerNum].state_1C8 == PLAYERSTATE_1C8_ACTIVE) ||
                 (gPlayer[playerNum].state_1C8 == PLAYERSTATE_1C8_U_TURN)) &&
                (gVsLockOnTimers[i][playerNum] != 0)) {
                return false;
            }
        }
    }
    return true;
}

bool Player_UpdateLockOn(Player* player) {
    bool hasBombTarget;
    s32 i;

    if (gInputHold->button & A_BUTTON) {
        gChargeTimers[player->num]++;
        if (gChargeTimers[player->num] > 21) {
            gChargeTimers[player->num] = 21;
        }
        if (gChargeTimers[player->num] == 20) {
            Object_PlayerSfx(player->sfxSource, NA_SE_LOCK_SEARCH, player->num);
        }
        if (!((gInputHold->button & R_TRIG) && (gInputHold->button & Z_TRIG) && (player->form == FORM_ARWING) &&
              (player->state_1C8 == PLAYERSTATE_1C8_ACTIVE)) &&
            ((gGameFrameCount % 4) == 0) && Player_CanLockOn(player->num)) {
            if (gChargeTimers[player->num] > 20) {
                for (i = 0; i < 13; i++) { // bug? should be 11
                    if (gPlayerShots[i].obj.status == SHOT_FREE) {
                        if (player->form == FORM_ARWING) {
                            Player_SetupArwingShot(player, &gPlayerShots[i], 0.0f, 0.0f, PLAYERSHOT_LOCK_SEARCH,
                                                   400.0f);
                        } else {
                            Player_SetupTankShot(player, &gPlayerShots[i], PLAYERSHOT_LOCK_SEARCH, 400.0f);
                        }
                        return true;
                    }
                }
            }
        }
    } else {
        if (gChargeTimers[player->num] != 0) {
            gChargeTimers[player->num]--;
        }
    }

    if (gInputPress->button & A_BUTTON) {
        for (i = 0; i < ARRAY_COUNT(gActors); i++) {
            if ((gActors[i].obj.status == OBJ_ACTIVE) && (gActors[i].lockOnTimers[player->num] != 0)) {
                if ((gPlayerShots[14 - player->num].obj.status == SHOT_FREE) ||
                    (gPlayerShots[14 - player->num].obj.id != PLAYERSHOT_LOCK_ON) ||
                    ((gPlayerShots[14 - player->num].obj.id == PLAYERSHOT_LOCK_ON) &&
                     (gPlayerShots[14 - player->num].unk_60 != 0))) {
                    if (player->form == FORM_ARWING) {
                        Player_SetupArwingShot(player, &gPlayerShots[14 - player->num], 0.0f, 0.0f, PLAYERSHOT_LOCK_ON,
                                               70.0f);
                    } else {
                        Player_SetupTankShot(player, &gPlayerShots[14 - player->num], PLAYERSHOT_LOCK_ON, 70.0f);
                    }
                    Object_PlayerSfx(player->sfxSource, NA_SE_LOCK_ON_LASER, player->num);
                    gControllerRumbleTimers[player->num] = 5;
                    return true;
                }
                break;
            }
        }
        if (gChargeTimers[player->num] > 10) {
            if ((gPlayerShots[14 - player->num].obj.status == SHOT_FREE) ||
                (gPlayerShots[14 - player->num].obj.id != PLAYERSHOT_LOCK_ON) ||
                ((gPlayerShots[14 - player->num].obj.id == PLAYERSHOT_LOCK_ON) &&
                 (gPlayerShots[14 - player->num].scale > 1.0f))) {
                if (player->form == FORM_ARWING) {
                    Player_SetupArwingShot(player, &gPlayerShots[14 - player->num], 0.0f, 0.0f, PLAYERSHOT_LOCK_ON,
                                           70.0f);
                } else {
                    Player_SetupTankShot(player, &gPlayerShots[14 - player->num], PLAYERSHOT_LOCK_ON, 70.0f);
                }
                Object_PlayerSfx(player->sfxSource, NA_SE_LOCK_ON_LASER, player->num);
                gChargeTimers[player->num] = 0;
                gControllerRumbleTimers[player->num] = 5;
                return true;
            }
        }
        gChargeTimers[player->num] = 0;
    }
    if (gInputPress->button & B_BUTTON) {
        hasBombTarget = false;
        for (i = 0; i < ARRAY_COUNT(gActors); i++) {
            if ((gActors[i].obj.status == OBJ_ACTIVE) && (gActors[i].lockOnTimers[player->num] != 0)) {
                hasBombTarget = true;
                break;
            }
        }
        for (i = 0; i < gCamCount; i++) {
            if (gVsLockOnTimers[i][player->num] != 0) {
                hasBombTarget = true;
                break;
            }
        }
        if (hasBombTarget && (gBombCount[player->num] != 0) &&
            (gPlayerShots[ARRAY_COUNT(gPlayerShots) - 1].obj.status == SHOT_FREE)) {
            gBombCount[player->num]--;
            if (player->form == FORM_ARWING) {
                Player_SetupArwingShot(player, &gPlayerShots[ARRAY_COUNT(gPlayerShots) - 1], 0.0f, 0.0f,
                                       PLAYERSHOT_LOCK_ON, 60.0f);
            } else {
                Player_SetupTankShot(player, &gPlayerShots[ARRAY_COUNT(gPlayerShots) - 1], PLAYERSHOT_LOCK_ON, 60.0f);
            }
            gPlayerShots[ARRAY_COUNT(gPlayerShots) - 1].unk_48 = 30.0f;
            gPlayerShots[ARRAY_COUNT(gPlayerShots) - 1].unk_60 = 0;
            Audio_InitBombSfx(player->num, 1);
            Audio_PlayBombFlightSfx(player->num, gPlayerShots[ARRAY_COUNT(gPlayerShots) - 1].sfxSource);
            return true;
        }
    }
    return false;
}

void Player_Shoot(Player* player) {
    switch (player->form) {
        case FORM_ARWING:
            if ((player->wings.rightState <= WINGSTATE_BROKEN) || (player->wings.leftState <= WINGSTATE_BROKEN)) {
                gLaserStrength[player->num] = LASERS_SINGLE;
            }
            if (!Player_UpdateLockOn(player)) {
                if (gLaserStrength[gPlayerNum] > LASERS_SINGLE) {
                    Math_SmoothStepToF(&player->wings.unk_14, -10.0f, 1.0f, 0.5f, 0.0f);
                } else {
                    Math_SmoothStepToF(&player->wings.unk_14, 0.0f, 1.0f, 0.5f, 0.0f);
                }
                if (gShootButton[player->num] & gInputPress->button) {
                    Player_ArwingLaser(player);
                    player->shotTimer = 8;
                }
                if (player->shotTimer != 0) {
                    player->shotTimer--;
                    if ((gShootButton[player->num] & gInputHold->button) && ((player->shotTimer & 3) == 0)) {
                        Player_ArwingLaser(player);
                    }
                }
                Player_SmartBomb(player);
            }
            break;
        case FORM_LANDMASTER:
            if (!Player_UpdateLockOn(player)) {
                if (gShootButton[player->num] & gInputPress->button) {
                    Player_TankCannon(player);
                }
                Player_SmartBomb(player);
            }
            break;
        case FORM_ON_FOOT:
            if (gInputPress->button & A_BUTTON) {
                player->shotTimer = 0;
            }
            if (gInputHold->button & A_BUTTON) {
                if (player->shotTimer == 0) {
                    Player_OnFootGun(player);
                }
                player->shotTimer++;
                if (player->shotTimer > 4) {
                    player->shotTimer = 0;
                }
            }
            Player_SmartBomb(player);
            break;
    }
}

void Player_ArwingBank(Player* player) {
    f32 sp3C;
    f32 sp38;

    sp3C = 0.0f;
    if ((player->wings.rightState <= WINGSTATE_BROKEN) && (player->wings.leftState == WINGSTATE_INTACT)) {
        sp3C = -17.0f;
    } else if ((player->wings.leftState <= WINGSTATE_BROKEN) && (player->wings.rightState == WINGSTATE_INTACT)) {
        sp3C = 17.0f;
    }
    sp38 = 0.1f;
    if ((gInputHold->button & Z_TRIG) && !(gInputHold->button & R_TRIG)) {
        sp3C = 90.0f;
        sp38 = 0.2f;
        if (player->zRotBank < 70.0f) {
            Math_SmoothStepToF(&player->wings.unk_04, -70.0f, 0.3f, 100.0f, 0.0f);
            Math_SmoothStepToF(&player->wings.unk_08, -70.0f, 0.3f, 100.0f, 0.f);
            Math_SmoothStepToF(&player->wings.unk_0C, 70.0f, 0.3f, 100.0f, 0.f);
            Math_SmoothStepToF(&player->wings.unk_10, 70.0f, 0.3f, 100.0f, 0.f);
            if (player->pos.y < (gGroundHeight + 70.0f)) {
                player->pos.y += 6.0f;
            }
        }
    }

    if ((gInputHold->button & R_TRIG) && !(gInputHold->button & Z_TRIG)) {
        sp3C = -90.0f;
        sp38 = 0.2f;
        if (player->zRotBank > -70.0f) {
            Math_SmoothStepToF(&player->wings.unk_04, 70.0f, 0.3f, 100.0f, 0.0f);
            Math_SmoothStepToF(&player->wings.unk_08, 70.0f, 0.3f, 100.0f, 0.0f);
            Math_SmoothStepToF(&player->wings.unk_0C, -70.0f, 0.3f, 100.0f, 0.0f);
            Math_SmoothStepToF(&player->wings.unk_10, -70.0f, 0.3f, 100.0f, 0.0f);
            if (player->pos.y < (gGroundHeight + 70.0f)) {
                player->pos.y += 6.0f;
            }
        }
    }
    Math_SmoothStepToF(&player->zRotBank, sp3C, sp38, 10.0f, 0.f);
    if (gInputPress->button & Z_TRIG) {
        player->sfx.bank = 1;
        if (player->barrelInputTimerL != 0) {
            player->barrelRoll = 1;
            player->timer_1E8 = 10;
            player->rollRate = player->baseRollRate = 30;
            player->sfx.roll = 1;
        } else {
            player->barrelInputTimerL = 10;
        }
    }
    if (gInputPress->button & R_TRIG) {
        player->sfx.bank = 1;
        if (player->barrelInputTimerR != 0) {
            player->barrelRoll = 1;
            player->timer_1E8 = 10;
            player->rollRate = player->baseRollRate = -30;
            player->sfx.roll = 1;
        } else {
            player->barrelInputTimerR = 10;
        }
    }
}

void Player_UseTankJets(Player* player) {
    Math_SmoothStepToF(&player->unk_170, 0.0f, 1.0f, 0.2f, 0.0f);
    Math_SmoothStepToF(&player->unk_16C, 0.0f, 1.0f, 0.2f, 0.0f);
    if (gInputPress->button & Z_TRIG) {
        if ((player->barrelInputTimerL != 0) && (player->zRotBank > 0.0f) && (player->boostMeter < 10.0f)) {
            player->barrelRoll = 1;
            player->timer_1E8 = 15;
            player->rollRate = player->baseRollRate = 20;
        } else {
            player->barrelInputTimerL = 10;
        }
    }
    if (gInputPress->button & R_TRIG) {
        if ((player->barrelInputTimerR != 0) && (player->zRotBank < 0.0f) && (player->boostMeter < 10.0f)) {
            player->barrelRoll = 1;
            player->timer_1E8 = 15;
            player->rollRate = player->baseRollRate = -20;
        } else {
            player->barrelInputTimerR = 10;
        }
    }
    player->unk_18C = fabsf(SIN_DEG(player->zRotBank) * 25.0f);
    player->unk_18C += fabsf(SIN_DEG(player->zRotBarrelRoll) * 20.0f);
}

void Player_UpdatePath(Player* player) {
    f32 temp_fv0;
    f32 temp_fv0_2;
    s32 temp_v0;

    player->zPathVel = -player->vel.z;
    player->zPath += -player->vel.z;
    gPathVelZ = -player->vel.z;
    gPathProgress = player->zPath;
    gPathTexScroll += player->zPathVel;
    if (gGroundType == 4) {
        gPathGroundScroll = player->zPathVel;
    }
    if (!gBossActive && (player->zPath > 500000.0f)) {
        player->zPath = 0.0f;
        player->pos.z = 0.0f;
        gObjectLoadIndex = 0;
        Play_ClearObjectData();
    }
    player->trueZpos = player->pos.z + player->camDist;
    player->bankAngle = player->rot.z + player->zRotBank + player->zRotBarrelRoll;

    while (true) {
        if (player->bankAngle > 360.0f) {
            player->bankAngle -= 360.0f;
        } else {
            break;
        }
    }
    while (true) {
        if (player->bankAngle < -360.0f) {
            player->bankAngle += 360.0f;
        } else {
            break;
        }
    }
    if (gCurrentLevel == LEVEL_UNK_15) {
        Math_SmoothStepToF(&player->pathStep, 10.0f, 0.1f, 0.5f, 0.0001f);
        player->pos.x += Math_SmoothStepToF(&player->xPath, player->xPathTarget, 0.1f, player->pathStep, 0.0001f);
        player->pos.y += Math_SmoothStepToF(&player->yPath, player->yPathTarget, 0.1f, player->pathStep, 0.0001f);
    } else {
        Math_SmoothStepToF(&player->pathStep, gPathVelZ * 0.54f, 0.1f, 2.0f, 0.0001f);
        gPathVelX = Math_SmoothStepToF(&player->xPath, player->xPathTarget, 0.1f, player->pathStep, 0.0001f);
        gPathVelY = Math_SmoothStepToF(&player->yPath, player->yPathTarget, 0.1f, player->pathStep, 0.0001f);
    }
    if (player->pathChangeTimer != 0) {
        player->pathChangeTimer--;
        Math_SmoothStepToF(&player->yRot_114, player->pathChangeYaw, 0.03f, 0.5f, 0.0001f);
        Math_SmoothStepToF(&player->xRot_120, player->pathChangePitch, 0.03f, 0.5f, 0.0001f);
    } else {
        Math_SmoothStepToF(&player->yRot_114, 0.0f, 0.03f, 0.5f, 0.0001f);
        Math_SmoothStepToF(&player->xRot_120, 0.0f, 0.03f, 0.5f, 0.0001f);
    }
}

void Player_CheckBounds360(Player* player) {
    f32 var_fv1;
    bool var_v0 = false;

    if (gCamCount != 1) {
        if (player->pos.x > 12000.0f) {
            var_v0 = true;
            player->pos.x -= 24000.0f;
            player->cam.eye.x -= 24000.0f;
            player->cam.at.x -= 24000.0f;
        }
        if (player->pos.x < -12000.0f) {
            var_v0 = true;
            player->pos.x += 24000.0f;
            player->cam.eye.x += 24000.0f;
            player->cam.at.x += 24000.0f;
        }

        if (player->pos.z > 12000.0f) {
            var_v0 = true;
            player->pos.z -= 24000.0f;
            player->cam.eye.z -= 24000.0f;
            player->cam.at.z -= 24000.0f;
        }
        if (player->pos.z < -12000.0f) {
            var_v0 = true;
            player->pos.z += 24000.0f;
            player->cam.eye.z += 24000.0f;
            player->cam.at.z += 24000.0f;
        }
        if (var_v0) {
            gVsLockOnTimers[player->num][0] = gVsLockOnTimers[player->num][1] = gVsLockOnTimers[player->num][2] =
                gVsLockOnTimers[player->num][3] = 0;
        }
    } else {
        var_fv1 = 12500.0f;
        if (gCurrentLevel == LEVEL_CORNERIA) {
            var_fv1 = 8000.0f;
        } else if (gCurrentLevel == LEVEL_BOLSE) {
            var_fv1 = 10000.0f;
        } else if (gCurrentLevel == LEVEL_SECTOR_Z) {
            var_fv1 = 20000.0f;
        } else if ((gCurrentLevel == LEVEL_VENOM_ANDROSS) && (gDrawBackdrop >= 4)) {
            var_fv1 = 100000.0f;
        }
        if ((var_fv1 < fabsf(player->pos.x)) || (var_fv1 < fabsf(player->pos.z))) {
            player->state_1C8 = PLAYERSTATE_1C8_U_TURN;
            player->unk_19C = 0;
            player->csState = 0;
            player->unk_000 = 0.0f;
            player->unk_004 = 0.0f;
        }
    }
}

void Player_MoveArwing360(Player* player) {
    f32 sp7C;
    f32 sp78;
    f32 scale;
    f32 var_fa1;
    f32 var_fv0;
    f32 var_fv1;
    f32 temp;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    Vec3f sp4C;
    Vec3f sp40;

    gPlayerTurnRate = 2.3f;
    gPlayerTurnStickMod = 0.68f;
    sp7C = -gInputPress->stick_x;
    sp78 = gInputPress->stick_y;
    Math_SmoothStepToAngle(&player->aerobaticPitch, 0.0f, 0.1f, 5.0f, 0.01f);
    Matrix_RotateZ(gCalcMatrix, -player->zRotBank * M_DTOR, MTXF_NEW);
    sp4C.x = sp7C * 0.75f;
    sp4C.y = sp78 * 0.75f;
    sp4C.z = 0.0f;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp4C, &sp40);
    sp60 = sp40.y;
    sp5C = sp58 = 0.0f;
    if (sp40.x < -5.0f) {
        sp5C = -sp40.x;
    }
    if (sp40.x > 5.0f) {
        sp58 = sp40.x;
    }

    Math_SmoothStepToF(&player->wings.unk_28, 0.0f, 0.1f, 100.0f, 0.0f);
    Math_SmoothStepToF(&player->wings.unk_04, -sp60 + sp5C, 0.1f, 100.0f, 0.0f);
    Math_SmoothStepToF(&player->wings.unk_08, -sp60 - sp5C, 0.1f, 100.0f, 0.0f);
    Math_SmoothStepToF(&player->wings.unk_0C, -sp60 + sp58, 0.1f, 100.0f, 0.0f);
    Math_SmoothStepToF(&player->wings.unk_10, -sp60 - sp58, 0.1f, 100.0f, 0.0f);
    scale = 0.1f;
    if ((player->zRotBank > 10.0f) && (sp7C > 0)) {
        gPlayerTurnRate *= 2.0f;
        scale = 0.2f;
    }
    if ((player->zRotBank < -10.0f) && (sp7C < 0)) {
        gPlayerTurnRate *= 2.0f;
        scale = 0.2f;
    }
    Math_SmoothStepToF(&player->rot.y, sp7C * gPlayerTurnStickMod, scale, gPlayerTurnRate, 0.03f);
    scale = 0.03f;
    if ((player->zRotBank > 10.0f) && (sp7C > 0)) {
        scale = 0.05f;
    }
    if ((player->zRotBank < -10.0f) && (sp7C < 0)) {
        scale = 0.05f;
    }
    Math_SmoothStepToF(&player->yRotVel_11C, player->rot.y * scale, 0.1f, 0.8f, 0.05f);
    player->yRot_114 += player->yRotVel_11C;
    if (player->yRot_114 >= 360.0f) {
        player->yRot_114 -= 360.0f;
    }
    if (player->yRot_114 < 0.0f) {
        player->yRot_114 += 360.0f;
    }
    gPlayerTurnRate = 2.3f;
    var_fa1 = 0.1f;
    temp = -sp78 * gPlayerTurnStickMod;
    if ((temp <= 0.0f) && (player->pos.y < (gGroundHeight + 50.0f))) {
        gPlayerTurnRate *= 2.0f;
        temp = 0.0f;
        var_fa1 = 0.2f;
    }
    Math_SmoothStepToF(&player->rot.x, temp, var_fa1, gPlayerTurnRate, 0.03f);
    var_fv1 = 1.5f;
    if (player->pos.y < (gGroundHeight + 70.0f)) {
        var_fv1 = 0.8f;
    }
    if (!((gInputHold->button & R_TRIG) && (gInputHold->button & Z_TRIG)) &&
        !(!(gInputHold->button & R_TRIG) && !(gInputHold->button & Z_TRIG))) {
        var_fv1 = 0.1f;
    }
    var_fv0 = 4.0f;
    if (sp7C == 0) {
        var_fv0 = 1.0f;
    }
    Math_SmoothStepToF(&player->rot.z, sp7C * 0.6f * var_fv1, 0.1f, var_fv0, 0.03f);
    player->bankAngle = player->rot.z + player->zRotBank + player->zRotBarrelRoll;
    Matrix_RotateY(gCalcMatrix, (player->yRot_114 + player->rot.y + 180.0f) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -((player->xRot_120 + player->rot.x + player->aerobaticPitch) * M_DTOR), MTXF_APPLY);
    sp4C.x = 0.0f;
    sp4C.y = 0.0f;
    if (player->wings.rightState <= WINGSTATE_BROKEN) {
        sp4C.x -= 2.5f;
        sp4C.y -= 2.5f;
    }
    if (player->wings.leftState <= WINGSTATE_BROKEN) {
        sp4C.x += 2.5f;
        sp4C.y -= 2.5f;
    }
    sp4C.z = player->baseSpeed + player->boostSpeed;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp4C, &sp40);
    player->vel.x = sp40.x;
    player->vel.z = sp40.z;
    player->vel.y = sp40.y;
    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;
    if ((player->pathHeight < player->pos.y) && (player->vel.y >= 0.0f)) {
        Math_SmoothStepToF(&player->pos.y, player->pathHeight, 0.1f, fabsf(player->vel.y * 1.5f) + 5.0f, 0.0f);
    }
    if ((player->pos.y < player->pathFloor) && (player->vel.y <= 0.0f)) {
        if (player->pathFloor >= 0.0f) {
            player->pos.y = player->pathFloor;
        } else {
            Math_SmoothStepToF(&player->pos.y, player->pathFloor, 0.1f, fabsf(player->vel.y * 1.5f) + 5.0f, 0.0f);
        }
    }
    player->pos.z += player->vel.z;
    if (player->pathHeight - 100.0f < player->pos.y) {
        player->flags_228 = PFLAG_228_3;
    }
    if (player->pos.y < -(player->pathHeight - 100.0f)) {
        player->flags_228 = PFLAG_228_2;
    }
    Player_CheckBounds360(player);
    player->trueZpos = player->pos.z;
    Player_WingEffects(player);
    Player_DamageEffects(player);
}

void Player_PerformLoop(Player* player) {
    f32 temp;
    f32 sp58;
    Vec3f sp4C;
    Vec3f sp40;

    sp58 = 60.0f;
    if (gVersusMode) {
        gVsLockOnTimers[player->num][0] = gVsLockOnTimers[player->num][1] = gVsLockOnTimers[player->num][2] =
            gVsLockOnTimers[player->num][3] = 0;
    }
    if (player->aerobaticPitch > 240.0f) {
        sp58 = -50.0f;
    }
    Math_SmoothStepToF(&player->wings.unk_04, sp58, 0.3f, 100.0f, 0.0f);
    Math_SmoothStepToF(&player->wings.unk_08, sp58, 0.3f, 100.0f, 0.0f);
    Math_SmoothStepToF(&player->wings.unk_0C, sp58, 0.3f, 100.0f, 0.0f);
    Math_SmoothStepToF(&player->wings.unk_10, sp58, 0.3f, 100.0f, 0.0f);
    if (player->aerobaticPitch < 180.0f) {
        player->pos.y += 2.0f;
    }
    player->boostCooldown = true;
    if (gLevelMode == LEVELMODE_ON_RAILS) {
        player->boostMeter += 2.0f;
    } else {
        player->boostMeter += 1.0f;
    }
    if (player->boostMeter > 90.0f) {
        player->boostMeter = 90.0f;
    }
    player->unk_190 = 2;
    Math_SmoothStepToF(&player->aerobaticPitch, 360.0f, 0.1f, 5.0f, 0.001f);
    if (player->aerobaticPitch > 350.0f) {
        player->somersault = false;
        if (gLevelMode != LEVELMODE_ON_RAILS) {
            player->unk_018 = 0.05f;
            player->unk_014 = 0.05f;
        } else {
            player->alternateView = player->savedAlternateView;
            if (player->alternateView) {
                player->unk_014 = 0.0f;
            }
        }
    }
    Math_SmoothStepToF(&player->rot.z, 0.0f, 0.1f, 5.0f, 0.0f);
    Math_SmoothStepToF(&player->rot.x, 0.0f, 0.1f, 5.0f, 0.0f);
    temp = -gInputPress->stick_x * 0.68f;
    Math_SmoothStepToF(&player->rot.y, temp, 0.1f, 2.0f, 0.0f);
    player->bankAngle = player->rot.z + player->zRotBank + player->zRotBarrelRoll;
    Matrix_RotateY(gCalcMatrix, (player->yRot_114 + player->rot.y + 180.0f) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -((player->xRot_120 + player->rot.x + player->aerobaticPitch) * M_DTOR), MTXF_APPLY);
    sp4C.x = 0.0f;
    sp4C.y = 0.0f;
    sp4C.z = player->baseSpeed;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp4C, &sp40);
    player->vel.x = sp40.x;
    player->vel.z = sp40.z;
    player->vel.y = sp40.y;
    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;
    if (player->pos.y < player->pathFloor + player->yPath) {
        player->pos.y = player->pathFloor + player->yPath;
        player->vel.y = 0.0f;
    }
    player->pos.z += player->vel.z;
    player->trueZpos = player->pos.z;
    Player_DamageEffects(player);
}

void Player_MoveArwingOnRails(Player* player) {
    f32 stickX;
    f32 stickY;
    f32 var_fa0;
    f32 var_fa1;
    f32 var_fv0;
    f32 var_fv1;
    f32 sp84;
    s32 pad;
    f32 sp7C;
    f32 sp78;
    f32 sp74;
    Vec3f sp68;
    Vec3f sp5C;
    Vec3f sp50;
    Vec3f sp44;

    gPlayerTurnRate = 2.3f;
    gPlayerTurnStickMod = 0.68f;

    if ((gInputPress->stick_x != 0) || (gInputPress->stick_y != 0)) {
        gPlayerTurnStickMod = 0.68f; //! FAKE ?
    }

    stickX = -gInputPress->stick_x;
    stickY = +gInputPress->stick_y;

    Math_SmoothStepToAngle(&player->aerobaticPitch, 0.0f, 0.1f, 5.0f, 0.01f);

    if (player->alternateView) {
        Matrix_RotateZ(gCalcMatrix, player->zRotBank * M_DTOR, MTXF_NEW);

        sp68.z = 0.0f;
        sp68.x = stickX;
        sp68.y = stickY;

        Matrix_MultVec3f(gCalcMatrix, &sp68, &sp5C);

        stickX = sp5C.x;
        stickY = sp5C.y;
    } else {
        Matrix_RotateZ(gCalcMatrix, (-player->zRotBank) * M_DTOR, MTXF_NEW);

        sp68.z = 0.0f;
        sp68.x = stickX * 0.75f;
        sp68.y = stickY * 0.75f;

        Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp68, &sp5C);

        sp7C = sp5C.y;
        sp78 = (sp74 = 0.0f);

        if (sp5C.x < -5.0f) {
            sp78 = -sp5C.x;
        }
        if (sp5C.x > 5.0f) {
            sp74 = sp5C.x;
        }
        Math_SmoothStepToF(&player->wings.unk_28, 0.0f, 0.1f, 100.0f, 0.0f);
        Math_SmoothStepToF(&player->wings.unk_04, (-sp7C) + sp78, 0.1f, 100.0f, 0.0f);
        Math_SmoothStepToF(&player->wings.unk_08, (-sp7C) - sp78, 0.1f, 100.0f, 0.0f);
        Math_SmoothStepToF(&player->wings.unk_0C, (-sp7C) + sp74, 0.1f, 100.0f, 0.0f);
        Math_SmoothStepToF(&player->wings.unk_10, (-sp7C) - sp74, 0.1f, 100.0f, 0.0f);
    }

    sp84 = 0.1f;

    if ((player->zRotBank > 10.0f) && (stickX > 0)) {
        sp84 = 0.2f;
        gPlayerTurnRate *= 2.0f;
    }
    if ((player->zRotBank < (-10.0f)) && (stickX < 0)) {
        sp84 = 0.2f;
        gPlayerTurnRate *= 2.0f;
    }
    if (player->barrelRoll != 0) {
        sp84 = 0.2f;
        gPlayerTurnRate = 6.8999996f; // 690.0f * 0.01f
    }

    Math_SmoothStepToF(&player->rot.y, stickX * gPlayerTurnStickMod, sp84, gPlayerTurnRate, 0.03f);

    gPlayerTurnRate = 2.3f;
    sp84 = 0.1f;
    var_fa1 = -stickY * gPlayerTurnStickMod;

    if ((var_fa1 <= 0.0f) && (player->pos.y < (gGroundHeight + 50.0f))) {
        var_fa1 = 0.0f;
        sp84 = 0.2f;
        gPlayerTurnRate *= 2.0f;
    }

    Math_SmoothStepToF(&player->rot.x, var_fa1, sp84, gPlayerTurnRate, 0.03f);

    var_fv1 = 1.0f;
    if (player->pos.y < (gGroundHeight + 70.0f)) {
        var_fv1 = 0.8f;
    }

    if (!((gInputHold->button & R_TRIG) && (gInputHold->button & Z_TRIG)) &&
        !(!(gInputHold->button & R_TRIG) && !(gInputHold->button & Z_TRIG))) {
        var_fv1 = 0.1f;
    }

    var_fv0 = 4.0f;
    if (stickX == 0) {
        var_fv0 = 1.0f;
    }

    Math_SmoothStepToF(&player->rot.z, (stickX * 0.6f) * var_fv1, 0.1f, var_fv0, 0.03f);
    Matrix_RotateY(gCalcMatrix, (player->rot.y + 180.0f) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -((player->rot.x + player->aerobaticPitch) * M_DTOR), MTXF_APPLY);

    sp68.x = 0.0f;
    sp68.y = 0.0f;
    sp68.z = player->baseSpeed;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp68, &sp44);

    sp44.x *= 1.4f;
    sp44.y *= 1.4f;

    Matrix_RotateY(gCalcMatrix, player->yRot_114 * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, player->xRot_120 * M_DTOR, MTXF_APPLY);
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp44, &sp5C);

    sp68.x = 0.0f;
    sp68.y = 0.0f;
    sp68.z = -player->boostSpeed;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp68, &sp50);

    player->vel.x = (sp5C.x + sp50.x) * player->unk_150;
    player->vel.y = (sp5C.y + sp50.y) * player->unk_150;
    player->vel.z = sp5C.z + sp50.z;

    if (gCurrentLevel == LEVEL_VENOM_ANDROSS) {
        player->vel.z += D_Andross_801A7F58;
    }
    sp68.x = 0.0f;
    sp68.y = 0.0f;
    sp68.z = -player->boostSpeed;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp68, &sp50);

    if (player->wings.rightState <= WINGSTATE_BROKEN) {
        player->vel.x += 2.5f;
        player->vel.y -= 2.5f;
    }
    if (player->wings.leftState <= WINGSTATE_BROKEN) {
        player->vel.x -= 2.5f;
        player->vel.y -= 2.5f;
    }

    if (player->pos.x > (player->xPath + (player->pathWidth - 100.0f))) {
        player->flags_228 = PFLAG_228_0;
    }
    if (player->pos.x < (player->xPath - (player->pathWidth - 100.0f))) {
        player->flags_228 = PFLAG_228_1;
    }
    if (player->pos.y > (player->yPath + (player->pathHeight - 100.0f))) {
        player->flags_228 = PFLAG_228_3;
    }
    if (player->pos.y < (player->yPath - (player->pathHeight - 100.0f))) {
        player->flags_228 = PFLAG_228_2;
    }

    player->pos.x += player->vel.x;

    if (player->pos.x > (player->pathWidth + player->xPath)) {
        player->pos.x = player->pathWidth + player->xPath;
        player->vel.x = 0.0f;
        player->knockback.x = 0.0f;
    }
    if (player->pos.x < (player->xPath - player->pathWidth)) {
        player->pos.x = player->xPath - player->pathWidth;
        player->vel.x = 0.0f;
        player->knockback.x = 0.0f;
    }

    player->pos.y += player->vel.y;

    if (player->pos.y > (player->pathHeight + player->yPath)) {
        player->pos.y = player->pathHeight + player->yPath;
        player->vel.y = 0.0f;
        player->knockback.y = 0.0f;
    }
    if (player->pos.y < (player->pathFloor + player->yPath)) {
        player->pos.y = player->pathFloor + player->yPath;
        player->vel.y = 0.0f;
        player->knockback.y = 0.0f;
    }

    player->pos.z += player->vel.z;

    Player_WingEffects(player);
}

void Player_MoveTank360(Player* player) {
    f32 sp5C;
    f32 var_fa0;
    f32 var_fa1;
    f32 var_fv1;
    Vec3f sp44;
    Vec3f sp38;

    var_fv1 = (gInputPress->stick_y * 0.7f) - 8.0f;
    if (var_fv1 < -40.0f) {
        var_fv1 = -40.0f;
    }
    if (var_fv1 > 0) {
        var_fv1 = 0;
    }
    if (var_fv1 > player->unk_17C) {
        player->unk_17C += 3.0f;
    }
    if (var_fv1 < player->unk_17C) {
        player->unk_17C -= 3.0f;
    }
    if (player->unk_180 < 0) {
        player->unk_180 += 3.0f;
    }
    if (player->unk_180 > 0) {
        player->unk_180 -= 3.0f;
    }
    gPlayerTurnRate = 3.0f;
    gPlayerTurnStickMod = 0.6666f;
    sp5C = gInputPress->stick_x;
    if (sp5C == 0) {
        Math_SmoothStepToF(&player->rot.y, -sp5C * gPlayerTurnStickMod, 0.1f, gPlayerTurnRate * 0.5f, 0.1f);
    } else {
        Math_SmoothStepToF(&player->rot.y, -sp5C * gPlayerTurnStickMod, 0.1f, gPlayerTurnRate, 0.1f);
    }
    player->rot_104.y = player->rot.y;
    var_fa0 = 0.03f;
    var_fa1 = 1.5f;
    if ((player->zRotBank > 10.0f) && (sp5C < 0.0f)) {
        var_fa0 = 0.1f;
        var_fa1 = 4.0f;
    }
    if ((player->zRotBank < -10.0f) && (sp5C > 0.0f)) {
        var_fa0 = 0.1f;
        var_fa1 = 4.0f;
    }
    if (player->barrelRoll != 0) {
        if ((player->rollRate > 0) && (sp5C < 0.0f)) {
            var_fa0 = 0.2f;
            var_fa1 = 20.0f;
        }
        if ((player->rollRate < 0) && (sp5C > 0.0f)) {
            var_fa0 = 0.2f;
            var_fa1 = 20.0f;
        }
    }
    Math_SmoothStepToF(&player->yRotVel_11C, player->rot.y * var_fa0, 0.1f, var_fa1, 0.05f);
    player->yRot_114 += player->yRotVel_11C;
    player->yRot_114 = Math_ModF(player->yRot_114, 360.0f);
    Matrix_RotateX(gCalcMatrix, player->rot_104.x * M_DTOR, MTXF_NEW);
    Matrix_RotateZ(gCalcMatrix, player->rot_104.z * M_DTOR, MTXF_APPLY);
    Matrix_RotateY(gCalcMatrix, (player->yRot_114 + player->rot.y + 180.0f) * M_DTOR, MTXF_APPLY);
    sp44.x = 0.0f;
    sp44.y = 0.0f;
    sp44.z = player->baseSpeed;
    sp44.z -= fabsf((player->unk_184 * 0.4f * player->baseSpeed) / 15.0f);
    sp44.z += SIN_DEG(player->unk_000) * player->boostSpeed;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp44, &sp38);
    player->vel.x = sp38.x;
    player->vel.z = sp38.z;
    if (player->unk_16C > 0.2f) {
        Math_SmoothStepToF(&player->unk_184, player->baseSpeed * 0.5f, 1.0f, 1.0f, 0);
    }
    if (player->unk_170 > 0.2f) {
        Math_SmoothStepToF(&player->unk_184, -player->baseSpeed * 0.5f, 1.0f, 1.0f, 0);
    }
    if (!(player->unk_170 > 0.2f) && !(player->unk_16C > 0.2f) && player->grounded) {
        Math_SmoothStepToF(&player->unk_184, 0.0f, 1.0f, 0.75f, 0.0f);
    }
    if (player->barrelRoll != 0) {
        if (player->rollRate < 0) {
            player->unk_184 = 15.0f;
        }
        if (player->rollRate > 0) {
            player->unk_184 = -15.0f;
        }
    }
    sp44.x = -player->unk_184;
    sp44.y = 0;
    sp44.z = 0;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp44, &sp38);
    player->pos.x += sp38.x;
    player->pos.z += sp38.z;
    player->pos.x += player->vel.x;
    player->vel.y -= player->gravity;
    player->pos.y += player->vel.y;
    if (player->grounded) {
        Math_SmoothStepToAngle(&player->rot.x, player->rot_104.x, 0.2f, 5.0f, 0.005f);
        Math_SmoothStepToAngle(&player->rot.z, player->rot_104.z, 0.2f, 5.0f, 0.005f);
        Math_SmoothStepToF(&player->unk_000, 0.0f, 0.1f, 5.0f, 0.00001f);
    }
    player->grounded = false;
    if (player->pos.y <= gGroundHeight - 5.0f) {
        player->pos.y = gGroundHeight - 5.0f;
        if (player->vel.y < -20.0f) {
            player->hitTimer = 20;
        }
        player->vel.y = 0.0f;
        player->grounded = true;
    }
    if (player->vel.y < -80.0f) {
        player->vel.y = -80.0f;
    }
    if (player->vel.y > 20.0f) {
        player->vel.y = 20.0f;
    }
    player->pos.z += player->vel.z;
    Player_CheckBounds360(player);
    player->trueZpos = player->pos.z;
    player->bankAngle = player->rot.z + player->zRotBank + player->zRotBarrelRoll;
    if (player->grounded) {
        player->rockPhase += player->baseSpeed * 5.0f;
        player->rockAngle = SIN_DEG(player->rockPhase) * 0.7f;
    }
    Player_DamageEffects(player);
}

f32 D_800D30F4[4] = { 3.0f, 4.0f, 5.0f, 3.0f };
f32 D_800D3104[4] = { 0.2f, 0.25f, 0.3f, 0.2f };

void Player_OnFootUpdateSpeed(Player* player) {
    f32 sp2C = 0.0f;
    f32 sp28 = 0.7f;
    f32 sp24 = 0.1f;

    if (gInputHold->button & R_TRIG) {
        sp2C = 16.0f;
        sp28 = D_800D30F4[gPlayerNum];
        sp24 = D_800D3104[gPlayerNum];
    }
    Math_SmoothStepToF(&player->baseSpeed, sp2C, 1.0f, 1.0f, 0.00001f);
    Math_SmoothStepToF(&player->unk_008, sp28, 0.1f, sp24, 0.00001f);
}

void Player_MoveOnFoot(Player* player) {
    Vec3f sp78[30];
    f32 sp74;
    f32 sp70;
    f32 var_fv0;
    f32 var_fa0;
    f32 sp64;
    Vec3f sp58;
    Vec3f sp4C;
    Vec3f* sp48;
    s32 sp44;
    s32 pad;

    player->camRoll = 0.0f;
    var_fa0 = 0.0f;
    if (player->pos.y > 10.0f) {
        var_fa0 = 20.0f;
    }
    if (player->pos.y > 300.0f) {
        var_fa0 = 40.0f;
    }
    sp74 = gInputPress->stick_y * 0.8f;
    if (sp74 < -40.0f) {
        sp74 = -40.0f;
    }
    if (var_fa0 < sp74) {
        sp74 = var_fa0;
    }
    Math_SmoothStepToF(&player->unk_154, sp74, 0.1f, 3.0f, 0.00001f);
    Math_SmoothStepToF(&player->unk_180, 0.0f, 0.15f, 5.0f, 0.00001f);
    Math_SmoothStepToF(&player->unk_158, sp74, 0.2f, 5.0f, 0.00001f);
    gPlayerTurnRate = 3.0f;
    gPlayerTurnStickMod = 0.666f;
    sp74 = gInputPress->stick_x;
    sp70 = gInputPress->stick_y;
    Math_SmoothStepToF(&player->rot.y, -sp74 * gPlayerTurnStickMod * 0.6f, 0.5f, gPlayerTurnRate, 0.001f);
    Math_SmoothStepToF(&player->rot.z, -sp74 * gPlayerTurnStickMod * 0.2f * player->baseSpeed / 15.0f, 0.2f, 5.0f,
                       0.001f);
    player->bankAngle = player->rot.z;
    if ((sp74 != 0.0f) || (sp70 != 0.0f)) {
        Math_SmoothStepToF(&player->unk_15C, sp74 * gPlayerTurnStickMod, 0.9f, 2.0f * gPlayerTurnRate, 0.1f);
        Math_SmoothStepToF(&player->unk_164, sp74 * 0.3f, 0.1f, 10.0f, 0.00001f);
        Math_SmoothStepToF(&player->unk_168, -sp74 * 0.3f, 0.1f, 10.0f, 0.00001f);
    } else {
        if (((gGameFrameCount % 16U) == 0) && (Rand_ZeroOne() < 0.5f)) {
            player->unk_17C = RAND_FLOAT_CENTERED(100.0f);
        }
        if (((gGameFrameCount % 16U) == 3) && (Rand_ZeroOne() < 0.5f)) {
            player->unk_174 = RAND_RANGE(-10.0f, 40.0f);
        }
        if (((gGameFrameCount % 16U) == 10) && (Rand_ZeroOne() < 0.5f)) {
            player->unk_178 = RAND_RANGE(-10.0f, 40.0f);
        }
        Math_SmoothStepToF(&player->unk_15C, player->unk_17C, 0.15f, 10.0f, 0.00001f);
        Math_SmoothStepToF(&player->unk_164, player->unk_174, 0.1f, 10.0f, 0.00001f);
        Math_SmoothStepToF(&player->unk_168, player->unk_178, 0.1f, 10.0f, 0.00001f);
    }
    player->rot_104.y = player->rot.y;
    if (player->baseSpeed < 1.5f) {
        var_fv0 = 0.12f;
        var_fa0 = 3.0f;
    } else {
        var_fv0 = 0.08f;
        var_fa0 = 1.5f;
    }
    Math_SmoothStepToF(&player->yRotVel_11C, -sp74 * gPlayerTurnStickMod * var_fv0, 0.2f, var_fa0, 0.0f);
    player->yRot_114 += player->yRotVel_11C;
    player->yRot_114 = Math_ModF(player->yRot_114, 360.0f);
    Matrix_RotateX(gCalcMatrix, player->rot_104.x * M_DTOR, MTXF_NEW);
    Matrix_RotateZ(gCalcMatrix, player->rot_104.z * M_DTOR, MTXF_APPLY);
    Matrix_RotateY(gCalcMatrix, (player->yRot_114 + player->rot.y + 180.0f) * M_DTOR, MTXF_APPLY);
    sp58.x = 0.0f;
    sp58.y = 0.0f;
    sp58.z = player->baseSpeed;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp58, &sp4C);
    player->vel.x = sp4C.x;
    player->vel.z = sp4C.z;
    player->pos.x += player->vel.x;
    if ((player->pos.y < 40.0f) || (player->pos.y > 670.0f)) {
        player->rot_104.z = 0.0f;
        player->rot_104.x = 0.0f;
    }
    Math_SmoothStepToAngle(&player->xRot_0FC, player->rot_104.x, 0.15f, 15.0f, 0.005f);
    Math_SmoothStepToAngle(&player->zRot_0FC, player->rot_104.z, 0.15f, 15.0f, 0.005f);
    if (player->grounded) {
        if (player->baseSpeed > 1.0f) {
            player->unk_00C += player->unk_008;
            if ((s32) player->unk_00C >= Animation_GetFrameCount(&D_versus_301CFEC)) {
                player->unk_00C = 0.0f;
            }
            player->yBob = 2.0f * SIN_DEG((player->unk_20C + 7) * 24.0f);
            if (player->yBob < -0.5f) {
                player->yBob = -0.5f;
            }
            player->yBob -= 3.0f;
            player->unk_20C = player->unk_00C;
            switch (gPlayerNum) {
                case 0:
                    sp44 = Animation_GetFrameData(&D_versus_301CFEC, player->unk_20C, sp78);
                    break;
                case 1:
                    sp44 = Animation_GetFrameData(&D_versus_301D888, player->unk_20C, sp78);
                    break;
                case 2:
                    sp44 = Animation_GetFrameData(&D_versus_301E19C, player->unk_20C, sp78);
                    break;
                case 3:
                    sp44 = Animation_GetFrameData(&D_versus_301C3A8, player->unk_20C, sp78);
                    break;
            }
            Math_SmoothStepToVec3fArray(sp78, player->jointTable, 1, sp44, 1.0f, player->unk_010, 0.01f);
            if (player->unk_010 < 50.0f) {
                player->unk_010 += 2.0f;
            }
            sp64 = player->baseSpeed;
            if (gGameFrameCount & 4) {
                sp64 = 2.0f * player->baseSpeed;
            }
            Math_SmoothStepToF(&player->unk_164, sp64, 0.5f, 20.0f, 0.0001f);
            Math_SmoothStepToF(&player->unk_168, sp64, 0.5f, 20.0f, 0.0001f);
        } else {
            if (player->unk_010 > 0.0f) {
                player->unk_010 -= 5.0f;
                if (player->unk_010 <= 0.0f) {
                    player->unk_010 = 0.0f;
                }
            }
            switch (gPlayerNum) {
                case 0:
                    sp48 = LOAD_ASSET(D_versus_302E56C);
                    break;
                case 1:
                    sp48 = LOAD_ASSET(D_versus_302E830);
                    break;
                case 2:
                    sp48 = LOAD_ASSET(D_versus_302E74C);
                    break;
                case 3:
                    sp48 = LOAD_ASSET(D_versus_302E65C);
                    break;
            }
            Math_SmoothStepToVec3fArray(sp48, player->jointTable, 1, 24, 0.2f, 10.0f, 0.01f);
            Math_SmoothStepToF(&player->yBob, -3.0f, 0.1f, 2.0f, 0.1f);
            Math_SmoothStepToF(&player->unk_164, 0.0f, 0.03f, 1.0f, 0.0001f);
            Math_SmoothStepToF(&player->unk_168, 0.0f, 0.03f, 1.0f, 0.0001f);
            player->unk_20C = 0;
            player->unk_00C = 0.0f;
        }
    }
    if (!player->grounded) {
        switch (gPlayerNum) {
            case 0:
                sp48 = LOAD_ASSET(D_versus_302E95C);
                break;
            case 1:
                sp48 = LOAD_ASSET(D_versus_302EC20);
                break;
            case 2:
                sp48 = LOAD_ASSET(D_versus_302EB3C);
                break;
            case 3:
                sp48 = LOAD_ASSET(D_versus_302EA4C);
                break;
        }
        Math_SmoothStepToVec3fArray(sp48, player->jointTable, 1, 24, 0.2f, 10.0f, 0.01f);
    }
    player->gravity = 2.0f;
    if ((gInputPress->button & Z_TRIG) && player->grounded) {
        player->vel.y = 12.0f;
    }
    if ((gInputHold->button & Z_TRIG) && (player->vel.y > 0.0f)) {
        player->gravity = 1.5f;
    }
    player->grounded = false;
    player->vel.y -= player->gravity;
    player->pos.y += player->vel.y;
    if (player->pos.y <= gGroundHeight) {
        player->grounded = true;
        player->pos.y = 0.0f;
        player->vel.y = 0.0f;
        player->rot.x += (player->pos.y - player->rot.x) * 0.05f;
    }
    if (player->vel.y < -50.0f) {
        player->vel.y = -50.0f;
    }
    if (player->vel.y > 20.0f) {
        player->vel.y = 20.0f;
    }
    player->pos.z += player->vel.z;
    Player_CheckBounds360(player);
    player->trueZpos = player->pos.z;
}

f32 D_800D3114[4] = { 10000.0f, -10000.0f, 10000.0f, -10000.0f };
f32 D_800D3124[4] = { 10000.0f, -10000.0f, -10000.0f, 10000.0f };
f32 D_800D3134[8] = {
    // unused? possibly two f32[4]?
    500.0f, -500.0f, 500.0f, -500.0f, 500.0f, -500.0f, -500.0f, 500.0f,
};
f32 D_800D3154[4] = { 45.0f, -135.0f, 135.0f, -45.0f };

void Player_Setup(Player* playerx) {
    s32 j;
    Vec3f* sp38;
    ObjectInit* objInit;
    s32 i;
    s16 sp2E;
    Player* player = playerx; // fake?

    gTiStartLandmaster = 0;
    player->shields = 255;
    if (gVersusMode) {
        switch (gHandicap[gPlayerNum]) {
            case 1:
                player->shields = 191;
                break;
            case 2:
                player->shields = 127;
                break;
        }
    }
    player->wings.rightState = WINGSTATE_INTACT;
    player->wings.leftState = WINGSTATE_INTACT;
    if (gExpertMode) {
        gLeftWingHealth[gPlayerNum] = 10;
        gRightWingHealth[gPlayerNum] = 10;
    } else {
        gLeftWingHealth[gPlayerNum] = 60;
        gRightWingHealth[gPlayerNum] = 60;
    }
    gUturnDownTimers[gPlayerNum] = gUturnBrakeTimers[gPlayerNum] = gLoopDownTimers[gPlayerNum] =
        gLoopBoostTimers[gPlayerNum] = gShieldTimer[gPlayerNum] = gHasShield[gPlayerNum] = gChargeTimers[gPlayerNum] =
            gVsLockOnTimers[gPlayerNum][0] = gVsLockOnTimers[gPlayerNum][1] = gVsLockOnTimers[gPlayerNum][2] =
                gVsLockOnTimers[gPlayerNum][3] = 0;
    gRightWingFlashTimer[gPlayerNum] = gLeftWingFlashTimer[gPlayerNum] = gRightWingDebrisTimer[gPlayerNum] =
        gLeftWingDebrisTimer[gPlayerNum] = D_ctx_80177990[gPlayerNum] = D_ctx_801779A8[gPlayerNum] =
            gMuzzleFlashScale[gPlayerNum] = 0.0f;
    gShieldAlpha[gPlayerNum] = 0.0f;
    player->unk_190 = 1.0f;
    player->unk_194 = 1.0f;
    gRadioState = gRadioMsgRadioId = gCurrentRadioPortrait = 0;
    D_ctx_8017853C = gRadioTextBoxScaleY = 0.0f;
    player->cam.eye.z = 400.0f;
    player->unk_148 = 0.77699995f; // 77.7f *0.01f
    player->unk_14C = 0.77699995f;
    player->unk_01C = 1.0f;
    player->groundPos.y = -1000.0f;
    player->cam.at.z = player->cam.eye.z - 1000.0f;
    D_ctx_80177950 = 1.0f;
    if ((gLevelType == LEVELTYPE_SPACE) && (gCurrentLevel != LEVEL_BOLSE)) {
        player->unk_240 = 1;
        player->unk_0A8 = 3000.0f;
        player->pathWidth = 700.0f;
        player->pathHeight = 612.0f;
        player->pathFloor = -544.0f;
        if (gCurrentLevel == LEVEL_UNK_15) {
            player->pathHeight = 3000.0f;
            player->pathFloor = -3000.0f;
        }
    } else {
        player->pathWidth = 700.0f;
        player->pathHeight = 680.0f;
        player->pathFloor = gGroundHeight + 40.0f;
        player->unk_0A8 = 3000.0f;
    }
    player->baseSpeed = gArwingSpeed;
    player->pos.y = 350.0f;
    switch (gCurrentLevel) {
        case LEVEL_MACBETH:
        case LEVEL_TITANIA:
            player->form = FORM_LANDMASTER;
            player->unk_014 = 1.0f;
            player->unk_14C = 0.67f;
            player->unk_148 = 0.67f;
            player->baseSpeed = 15.0f;
            player->gravity = 3.0f;
            player->pathWidth = 500.0f;
            player->pathHeight = 500.0f;
            player->pathFloor = -500.0f;
            if (gCurrentLevel == LEVEL_TITANIA) {
                player->pos.y = 150.0f;
            } else {
                player->pos.y = 0.0f;
            }
            break;
        case LEVEL_AQUAS:
            player->form = FORM_BLUE_MARINE;
            player->gravity = 0.0f;
            player->pathWidth = 700.0f;
            player->baseSpeed = 20.0f;
            player->pathHeight = 720.0f;
            player->pathFloor = gGroundHeight + 30.0f;
            break;
        case LEVEL_SOLAR:
        case LEVEL_ZONESS:
            player->pathFloor = -450.0f;
            break;
    }
    if (gCurrentLevel != LEVEL_CORNERIA) {
        gSavedGroundSurface = SURFACE_GRASS;
    }
    gGoldRingCount[0] = gSavedGoldRingCount[0];
    do {
        if (gGoldRingCount[0] > 3) {
            gGoldRingCount[0] -= 3;
        }
    } while (gGoldRingCount[0] > 3);

    if (gGoldRingCount[0] == 3) {
        gGoldRingCount[0] = 0;
    }
    gHitCount = gSavedHitCount;
    if ((gCurrentLevel == LEVEL_VENOM_ANDROSS) || ((gCurrentLevel == LEVEL_VENOM_2) && (gLevelPhase == 2))) {
        if (D_ctx_80177C9C != 0) {
            player->shields = D_ctx_80177C9C - 1;
            gGoldRingCount[0] = D_ctx_80177C94;
            player->wings.rightState = D_ctx_80177CAC;
            player->wings.leftState = D_ctx_80177CB4;
            gRightWingHealth[0] = D_ctx_80177CBC;
            gLeftWingHealth[0] = D_ctx_80177CC4;
            if (gCurrentLevel == LEVEL_VENOM_ANDROSS) {
                D_ctx_80177C94 = D_ctx_80177CAC = D_ctx_80177CB4 = D_ctx_80177CBC = D_ctx_80177CC4 = D_ctx_80177C9C = 0;
            }
        }
        gHitCount = gSavedHitCount = D_ctx_80177CA4;
    }
    D_hud_80161720[0] = 0.0f;
    D_hud_80161720[1] = 0.0f;
    D_hud_80161720[2] = 0.0f;
    gDisplayedHitCount = gHitCount;
    D_hud_80161730 = 0;
    gMissedZoSearchlight = gSavedZoSearchlightStatus;
    gObjectLoadIndex = gSavedObjectLoadIndex;
    gGroundSurface = gSavedGroundSurface;
    gPathProgress = player->zPath = gSavedPathProgress;
    player->pos.z = player->trueZpos = -player->zPath;
    if ((gSavedObjectLoadIndex > 0) && (gLevelMode == LEVELMODE_ON_RAILS)) {
        if (gCurrentLevel == LEVEL_MACBETH) {
            sp2E = gObjectLoadIndex;
            Macbeth_801AD080();
            gObjectLoadIndex = sp2E;
        }
        func_enmy_80062568();
    }
    if (player->form == FORM_LANDMASTER) {
        player->pos.z -= 200.0f;
        player->trueZpos -= 200.0f;
    }
    player->cam.eye.y = (player->pos.y * player->unk_148) + 10.0f;
    player->cam.eye.x = player->pos.x * player->unk_148;

    gPlayCamAt.x = gPlayCamAt.y = gPlayCamAt.z = gPlayCamEye.x = gPlayCamEye.y = gPlayCamEye.z = 0.0f;

    if (gVersusMode) {
        gLaserStrength[gPlayerNum] = LASERS_SINGLE;
        player->pos.y = 500.0f;
        player->pos.x = D_800D3114[gPlayerNum];
        player->pos.z = D_800D3124[gPlayerNum];
        player->yRot_114 = D_800D3154[gPlayerNum];
        player->form = gPlayerForms[gPlayerNum];
        switch (player->form) {
            case FORM_ARWING:
                break;
            case FORM_LANDMASTER:
                player->pos.y = 0.0f;
                player->baseSpeed = 15.0f;
                player->gravity = 3.0f;
                break;
            case FORM_ON_FOOT:
                player->pos.y = 0.0f;
                player->baseSpeed = 15.0f;
                player->groundPos.y = 0;
                switch (gPlayerNum) {
                    case 0:
                        sp38 = LOAD_ASSET(D_versus_302E56C);
                        break;
                    case 1:
                        sp38 = LOAD_ASSET(D_versus_302E830);
                        break;
                    case 2:
                        sp38 = LOAD_ASSET(D_versus_302E74C);
                        break;
                    case 3:
                        sp38 = LOAD_ASSET(D_versus_302E65C);
                        break;
                }
                for (j = 0; j < 30; j++, sp38++) {
                    player->jointTable[j] = *sp38;
                }
                break;
        }
        Camera_Update360(player, 1);
    }
    player->state_1C8 = PLAYERSTATE_1C8_ACTIVE;
    player->unk_204 = gLevelType;
    if ((gLevelMode == LEVELMODE_ALL_RANGE) && !gVersusMode) {
        player->pos.z = 8000.0f;
        player->pos.y = 670.0f;
        player->pathHeight = 730.0f;
        player->unk_204 = 2;
        if ((gCurrentLevel == LEVEL_VENOM_ANDROSS) && (gLevelPhase == 1)) {
            player->pos.x = -7910.0f;
            player->pos.y = 300.0f;

            player->pos.z = -11808.0f;
            player->yRot_114 = 188.0f;
            player->unk_240 = 1;
        }
        Camera_UpdateArwing360(player, 1);
    } else {
        player->unk_014 = 1.0f;
        player->unk_018 = 1.0f;
    }
    if (D_ctx_8017782C && (gSavedObjectLoadIndex == 0)) {
        gLeveLClearStatus[gCurrentLevel] = 0;
        for (j = 0; j < 10; j++) {
            D_ctx_80177A10[j] = 0;
            D_ctx_80177A48[j] = 0.0f;
        }
        D_ctx_8017782C = 0;
        gAllRangeCheckpoint = 0;
        switch (gCurrentLevel) {
            case LEVEL_CORNERIA:
                player->state_1C8 = PLAYERSTATE_1C8_LEVEL_INTRO;
                player->unk_204 = 1;
                gGroundSurface = gSavedGroundSurface = SURFACE_WATER;
                Play_dummy_MuteSfx();
                break;
            case LEVEL_BOLSE:
                player->unk_204 = 1;
                D_BO_801A03DC = 6;
                /* fallthrough */
            case LEVEL_SECTOR_X:
            case LEVEL_AREA_6:
            case LEVEL_SECTOR_Y:
            case LEVEL_VENOM_1:
            case LEVEL_SOLAR:
            case LEVEL_ZONESS:
            case LEVEL_MACBETH:
            case LEVEL_TITANIA:
            case LEVEL_AQUAS:
            case LEVEL_FORTUNA:
            case LEVEL_KATINA:
            case LEVEL_SECTOR_Z:
            case LEVEL_VENOM_2:
                player->state_1C8 = PLAYERSTATE_1C8_LEVEL_INTRO;
                break;
            case LEVEL_METEO:
                player->state_1C8 = PLAYERSTATE_1C8_LEVEL_INTRO;
                break;
        }
    } else {
        if (!gVersusMode && !((gCurrentLevel == LEVEL_VENOM_2) && (gLevelPhase == 2))) {
            gLevelStartStatusScreenTimer = 80;
        }

        if (gCurrentLevel == LEVEL_BOLSE) {
            gDrawGround = true;
        }

        if ((gCurrentLevel == LEVEL_MACBETH) && (gSavedObjectLoadIndex == 0)) {
            player->pos.z = -4115.0f;
            gPathProgress = player->zPath = 3932.0f;

            gObjectLoadIndex = 40;
            gLevelObjects = LOAD_ASSET(gLevelObjectInits[gCurrentLevel]);
            for (objInit = gLevelObjects, i = 0; i < gObjectLoadIndex; i++, objInit++) {
                Object_Load(objInit, 4000.0f, -4000.0f, 4000.0f, -4000.0f);
            }
            Macbeth_801ACFBC();
        }
    }
    if (player->state_1C8 == PLAYERSTATE_1C8_LEVEL_INTRO) {
        player->unk_234 = 1;
        switch (gCurrentLevel) {
            case LEVEL_CORNERIA:
                AUDIO_PLAY_BGM(NA_BGM_START_DEMO);
                break;
            case LEVEL_METEO:
                AUDIO_PLAY_BGM(NA_BGM_ME_START_DEMO);
                break;
            case LEVEL_FORTUNA:
            case LEVEL_BOLSE:
            case LEVEL_VENOM_2:
                AUDIO_PLAY_BGM(NA_BGM_FO_START_DEMO);
                break;
            case LEVEL_VENOM_1:
                AUDIO_PLAY_BGM(NA_BGM_STAGE_VE1);
                break;
            case LEVEL_KATINA:
                AUDIO_PLAY_BGM(NA_BGM_KA_START_DEMO);
                break;
            case LEVEL_TITANIA:
                AUDIO_PLAY_BGM(NA_BGM_START_DEMO_M);
                break;
            case LEVEL_ZONESS:
            case LEVEL_SECTOR_X:
            case LEVEL_VENOM_ANDROSS:
            case LEVEL_TRAINING:
            case LEVEL_MACBETH:
            default:
                AUDIO_PLAY_BGM(NA_BGM_START_DEMO_S);
                break;
            case LEVEL_AREA_6:
            case LEVEL_SECTOR_Y:
            case LEVEL_AQUAS:
            case LEVEL_SECTOR_Z:
            case LEVEL_SOLAR:
                break;
        }
    } else if (!gVersusMode && (gBgmSeqId != SEQ_ID_NONE) &&
               ((gLevelMode != LEVELMODE_ALL_RANGE) || (gAllRangeCheckpoint == 0))) {
        AUDIO_PLAY_BGM(gBgmSeqId);
    }
    gLevelClearScreenTimer = gBossHealthBar = D_ctx_80177850 = 0;

    if ((gCurrentLevel == LEVEL_TRAINING)) {
        D_ctx_80177824 = 1;
    }
    if (D_ctx_80177824 && !gVersusMode) {
        for (j = TEAM_ID_FALCO; j < TEAM_ID_MAX; j++) {
            gTeamShields[j] = gSavedTeamShields[j] = gPrevPlanetTeamShields[j] = gPrevPlanetSavedTeamShields[j] = 255;
        }
        for (j = 0; j < 6; j++) {
            gStarWolfTeamAlive[j] = gSavedStarWolfTeamAlive[j] = 1;
        }
        gLaserStrength[gPlayerNum] = LASERS_SINGLE;
        gGoldRingCount[0] = gSavedGoldRingCount[0] = gTotalHits = 0;
        gLifeCount[gPlayerNum] = 2;
        gBombCount[gPlayerNum] = 3;
        gGreatFoxIntact = true;
        if (gCamCount == (gPlayerNum + 1)) {
            D_hud_80161720[0] = 0.0f;
            D_hud_80161720[1] = 0.0f;
            D_hud_80161720[2] = 0.0f;
            gDisplayedHitCount = 0;
            gHitCount = 0;
            D_ctx_80177824 = 0;
        }
    }
    if ((gCurrentLevel == LEVEL_TRAINING)) {
        D_ctx_80177824 = 1;
    }
    player->sfx.levelType = gLevelType;
    player->sfx.form = player->form;
    func_display_80057814(player);
    if (!gVersusMode && (((gCurrentLevel != LEVEL_TITANIA) && (gCurrentLevel != LEVEL_SOLAR)) || gVersusMode ||
                         (player->state_1C8 != PLAYERSTATE_1C8_LEVEL_INTRO))) {
        Audio_StartPlayerNoise(gPlayerNum);
    }
    if ((player->form == FORM_ARWING) && !gVersusMode) {
        switch (player->unk_204) {
            case 0:
                Animation_GetFrameData(&D_arwing_3015AF4, 0, player->jointTable);
                break;
            case 1:
                Animation_GetFrameData(&D_arwing_3015C28, 0, player->jointTable);
                break;
            case 2:
                Animation_GetFrameData(&D_arwing_30163C4, 0, player->jointTable);
                break;
        }
    }
    if (gLaserStrength[gPlayerNum] > LASERS_SINGLE) {
        player->wings.unk_14 = -10.0f;
    }
    gPauseEnabled = 0;
}

void Player_UpdateArwingRoll(Player* player) {
    s32 temp_t6;
    s32 temp_t7;
    s32 temp_t8;
    s32 temp_t9;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 var_v0;

    Math_SmoothStepToF(&player->unk_150, 1.0f, 0.05f, 10.0f, 0.0001f);
    player->zRotBarrelRoll = Math_ModF(player->zRotBarrelRoll, 360.0f);
    if (player->barrelRollAlpha > 0) {
        player->barrelRollAlpha -= 30;
        if (player->barrelRollAlpha <= 0) {
            player->barrelRollAlpha = 0;
        }
    }
    if (player->meteoWarpTimer == 0) {
        if (player->barrelRoll == 0) {
            Math_SmoothStepToF(&player->zRotBarrelRoll, 0.0f, 0.1f, 10.0f, 0.00001f);
        }
        if (player->barrelInputTimerL != 0) {
            player->barrelInputTimerL--;
        }
        if (player->barrelInputTimerR != 0) {
            player->barrelInputTimerR--;
        }
        if (player->timer_214 != 0) {
            player->timer_214--;
        }
        if (player->timer_218 != 0) {
            player->timer_218--;
        }
        if (player->timer_1E8 != 0) {
            player->timer_1E8--;
        }
        if (player->barrelRoll != 0) {
            player->barrelInputTimerR = 0;
            player->barrelInputTimerL = 0;
            player->unk_150 = 1.5f;
            player->zRotBarrelRoll += player->rollRate;
            if (player->timer_1E8 == 0) {
                if (player->rollRate > 0) {
                    player->rollRate -= 5;
                }
                if (player->rollRate < 0) {
                    player->rollRate += 5;
                }
                if (player->rollRate == 0) {
                    player->barrelRoll = 0;
                }
            } else if (player->barrelRollAlpha < 180) {
                player->barrelRollAlpha += 100;
                if (player->barrelRollAlpha > 180) {
                    player->barrelRollAlpha = 180;
                }
            }
        }
    }
}

void Player_UpdateTankRoll(Player* player) {
    f32 temp_fv0;
    f32 temp_fv0_2;
    s32* temp_v1;
    s32 temp_t3;
    s32 temp_t4;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 var_v0;

    player->zRotBarrelRoll = Math_ModF(player->zRotBarrelRoll, 360.0f);
    if (player->barrelRoll == 0) {
        temp_fv0 = player->zRotBarrelRoll;
        if (player->zRotBarrelRoll > 0.0f) {
            player->zRotBarrelRoll -= (player->zRotBarrelRoll * 0.1f);
            if (player->zRotBarrelRoll < 0.1f) {
                player->zRotBarrelRoll = 0.0f;
            }
        }
        if (player->zRotBarrelRoll < 0.0f) {
            player->zRotBarrelRoll -= player->zRotBarrelRoll * 0.1f;
            if (player->zRotBarrelRoll > -0.1f) {
                player->zRotBarrelRoll = 0.0f;
            }
        }
    }
    temp_v0 = player->barrelInputTimerL;
    if (player->barrelInputTimerL != 0) {
        player->barrelInputTimerL--;
    }
    if (player->barrelInputTimerR != 0) {
        player->barrelInputTimerR--;
    }
    if (player->timer_1E8 != 0) {
        player->timer_1E8--;
    }
    if (player->barrelRoll != 0) {
        player->barrelInputTimerR = 0;
        player->barrelInputTimerL = 0;
        player->zRotBarrelRoll += player->rollRate;
        if (player->zRotBank > 0.0f) {
            player->zRotBank -= 8.0f;
            if (player->zRotBank < 0.0f) {
                player->zRotBank = 0.0f;
            }
        }
        if (player->zRotBank < 0.0f) {
            player->zRotBank += 8.0f;
            if (player->zRotBank > 0.0f) {
                player->zRotBank = 0.0f;
            }
        }
        if (player->timer_1E8 == 0) {
            if (player->rollRate > 0) {
                player->rollRate -= 2;
            }
            if (player->rollRate < 0) {
                player->rollRate += 2;
            }
            if (player->rollRate == 0) {
                player->barrelRoll = 0;
            }
        } else {
            Math_SmoothStepToF(&D_ctx_801779A8[player->num], 30.0f, 1.0f, 30.0f, 0.0f);
        }
        if ((player->timer_1E8 >= 5) && (player->timer_498 == 0)) {
            if (player->rollRate > 0) {
                player->unk_170 = 1.3f;
            }
            if (player->rollRate < 0) {
                player->unk_16C = 1.3f;
            }
        }
        if (gVersusMode) {
            gVsLockOnTimers[player->num][0] = gVsLockOnTimers[player->num][1] = gVsLockOnTimers[player->num][2] =
                gVsLockOnTimers[player->num][3] = 0;
        }
    }
}

void Player_ArwingBoost(Player* player) {
    f32 sp2C;
    f32 sp28;
    s32 var;

    if ((player->boostMeter != 0.0f) && (gInputHold->button & gBrakeButton[player->num]) &&
        (gInputHold->button & gBoostButton[player->num])) {
        player->boostCooldown = true;
    }
    if (gLevelMode == LEVELMODE_ON_RAILS) {
        sp28 = 3.0f;
        sp2C = 0.5f;

    } else {
        sp28 = 1.5f;
        sp2C = 0.35f;
    }
    player->sfx.boost = 0;
    var = gInputPress->stick_y; // fake?
    if (gLoopDownTimers[gPlayerNum] != 0) {
        gLoopDownTimers[gPlayerNum]--;
    }

    if (gLoopBoostTimers[gPlayerNum] != 0) {
        gLoopBoostTimers[gPlayerNum]--;
    }
    if (!player->somersault && (gDrawBackdrop < 5)) {
        if (var >= -50) {
            gLoopDownTimers[gPlayerNum] = 5;
        }
        if ((gLoopDownTimers[gPlayerNum] > 0) && (gLoopDownTimers[gPlayerNum] < 5) &&
            (gLoopBoostTimers[gPlayerNum] != 0)) {
            player->somersault = true;
            if (gLevelMode == LEVELMODE_ON_RAILS) {
                player->savedAlternateView = player->alternateView;
                player->alternateView = false;
            }
            player->unk_014 = player->unk_018 = 0.0f;
            if (player->aerobaticPitch > 340.0f) {
                player->aerobaticPitch -= 360.0f;
            }
            return;
        }
    }
    if (player->meteoWarpTimer != 0) {
        player->meteoWarpTimer--;
        player->boostCooldown = true;
        if (gRingPassCount > 0) {
            Math_SmoothStepToF(&D_ctx_801779A8[player->num], gRingPassCount * 10.0f, 1.0f, 5.0f, 0.0f);
        }
        player->boostSpeed += 0.3f;
        Math_SmoothStepToF(&player->camDist, -130.0f, 0.2f, 10.0f, 0.0f);
        player->zRotBarrelRoll -= player->meteoWarpSpinSpeed;
        player->meteoWarpSpinSpeed = player->meteoWarpSpinSpeed + 0.2f;
        if (player->meteoWarpSpinSpeed > 50.0f) {
            player->meteoWarpSpinSpeed = 50.0f;
        }
        if (((gGameFrameCount % 2) == 0) && (gBlurAlpha > 64)) {
            if (1) {}
            gBlurAlpha--;
        }
    } else {
        player->meteoWarpSpinSpeed = 0.0f;
        if (gBlurAlpha < 255) {
            gBlurAlpha += 4;
            if (gBlurAlpha >= 252) {
                gBlurAlpha = 255;
            }
        }
        if (!(gInputHold->button & gBrakeButton[player->num]) && !(gInputHold->button & gBoostButton[player->num])) {
            player->boostCooldown = true;
            if (player->boostMeter == 0.0f) {
                player->boostCooldown = false;
            }
        }
        if ((gInputHold->button & gBoostButton[player->num]) && !(gInputHold->button & gBrakeButton[player->num]) &&
            (player->state_1C8 != PLAYERSTATE_1C8_U_TURN) && !player->boostCooldown) {
            if (player->boostMeter == 0.0f) {
                Player_PlaySfx(player->sfxSource, NA_SE_ARWING_BOOST, player->num);
                player->unk_194 = 5.0f;
                player->unk_190 = 5.0f;
                if (gBoostButton[player->num] & gInputPress->button) {
                    gLoopBoostTimers[gPlayerNum] = 5;
                }
            }
            if (gLevelType == LEVELTYPE_PLANET) {
                player->wings.unk_28 += (35.0f - player->wings.unk_28) * 0.1f;
                Math_SmoothStepToF(&player->wings.unk_04, 0.0f, 0.5f, 100.0f, 0.0f);
                Math_SmoothStepToF(&player->wings.unk_08, 0.0f, 0.5f, 100.0f, 0.0f);
                Math_SmoothStepToF(&player->wings.unk_0C, 0.0f, 0.5f, 100.0f, 0.0f);
                Math_SmoothStepToF(&player->wings.unk_10, 0.0f, 0.5f, 100.0f, 0.0f);
            }
            player->boostMeter += sp28;
            if (player->boostMeter > 90.0f) {
                player->boostMeter = 90.0f;
                player->boostCooldown = true;
            }
            player->contrailScale += 0.04f;
            if (player->contrailScale > 0.6f) {
                player->contrailScale = 0.6f;
            }
            player->unk_190 = 2.0f;
            player->boostSpeed += 2.0f;
            if (player->boostSpeed > 30.0f) {
                player->boostSpeed = 30.0f;
            }
            Math_SmoothStepToF(&player->camDist, -400.0f, 0.1f, 30.0f, 0.0f);
            player->sfx.boost = 1;
            Math_SmoothStepToF(&D_ctx_801779A8[player->num], 50.0f, 1.0f, 10.0f, 0.0f);
        } else {
            if (player->boostMeter > 0.0f) {
                player->boostMeter -= sp2C;
                if (player->boostMeter <= 0.0f) {
                    player->boostMeter = 0.0f;
                    player->boostCooldown = false;
                }
            }
            if (player->boostSpeed > 0.0f) {
                player->boostSpeed -= 1.0f;
                if (player->boostSpeed < 0.0f) {
                    player->boostSpeed = 0.0f;
                }
            }
        }
    }
}

// Unused
void Player_ArwingBoost2(Player* player) {
    Player_ArwingBoost(player);
}

void Player_ArwingBrake(Player* player) {
    f32 sp34;
    f32 sp30;
    s32 var;

    if (gLevelMode == LEVELMODE_ON_RAILS) {
        sp30 = 3.0f;
        sp34 = 0.5f;
    } else {
        sp30 = 1.5f;
        sp34 = 0.35f;
    }
    player->sfx.brake = 0;
    var = gInputPress->stick_y; // fake?
    if (gUturnDownTimers[gPlayerNum] != 0) {
        gUturnDownTimers[gPlayerNum]--;
    }
    if (gUturnBrakeTimers[gPlayerNum] != 0) {
        gUturnBrakeTimers[gPlayerNum]--;
    }
    if (var >= -50) {
        gUturnDownTimers[gPlayerNum] = 5;
    }
    if ((gUturnDownTimers[gPlayerNum] > 0) && (gUturnDownTimers[gPlayerNum] < 5) && (gDrawBackdrop < 5) &&
        (gUturnBrakeTimers[gPlayerNum] != 0)) {
        gUturnDownTimers[gPlayerNum] = 0;
        gUturnBrakeTimers[gPlayerNum] = 0;
        player->state_1C8 = PLAYERSTATE_1C8_U_TURN;
        player->csState = 0;
        player->unk_19C = 1;
        player->unk_000 = 0.0f;
        player->unk_004 = 0.0f;
        player->unk_194 = 5.0f;
        player->unk_190 = 5.0f;
        if (gCurrentLevel == LEVEL_CORNERIA) {
            gCoUturnCount++;
        }
    }
    if ((gInputHold->button & gBrakeButton[player->num]) && !(gInputHold->button & gBoostButton[player->num]) &&
        (player->state_1C8 != PLAYERSTATE_1C8_U_TURN) && !player->boostCooldown) {
        if (player->boostMeter == 0.0f) {
            Player_PlaySfx(player->sfxSource, NA_SE_ARWING_BRAKE, player->num);
            if ((gLevelMode == LEVELMODE_ALL_RANGE) && (gInputPress->button & gBrakeButton[player->num])) {
                gUturnBrakeTimers[gPlayerNum] = 5;
            }
        }
        if (gLevelType == LEVELTYPE_PLANET) {
            Math_SmoothStepToF(&player->wings.unk_04, 90.0f, 0.2f, 100.0f, 0.0f);
            Math_SmoothStepToF(&player->wings.unk_08, -90.0f, 0.2f, 100.0f, 0.0f);
            Math_SmoothStepToF(&player->wings.unk_0C, 90.0f, 0.2f, 100.0f, 0.0f);
            Math_SmoothStepToF(&player->wings.unk_10, -90.0f, 0.2f, 100.0f, 0.0f);
        }
        player->boostMeter += sp30;
        if (player->boostMeter > 90.0f) {
            player->boostCooldown = true;
            player->boostMeter = 90.0f;
        }
        player->unk_190 = 0.3f;
        player->boostSpeed -= 1.0f;
        if (player->boostSpeed < -20.0f) {
            player->boostSpeed = -20.0f;
        }
        Math_SmoothStepToF(&player->camDist, 180.0f, 0.1f, 10.0f, 0.0f);
        player->sfx.brake = 1;
        Math_SmoothStepToF(&D_ctx_801779A8[player->num], 25.0f, 1.0f, 5.0f, 0.0f);
    } else if (player->boostMeter > 0.0f) {
        player->boostMeter -= sp34;
        if (player->boostMeter <= 0.0f) {
            player->boostMeter = 0.0f;
            player->boostCooldown = false;
        }
        if (player->boostSpeed < 0.0f) {
            player->boostSpeed += 0.5f;
            if (player->boostSpeed > 0.0f) {
                player->boostSpeed = 0.0f;
            }
        }
    }
    Math_SmoothStepToF(&player->camDist, 0.0f, 0.1f, 5.0f, 0.0f);
}

void Player_TankBoostBrake(Player* player) {
    f32 sp2C;

    if (!player->boostActive) {
        Math_SmoothStepToF(&player->boostMeter, 0.0f, 1.0f, 1.0f, 0.0f);
    }
    player->boostActive = false;
    if (player->boostMeter == 0.0f) {
        player->boostCooldown = false;
    } else if (!(gInputHold->button & Z_TRIG) && !(gInputHold->button & R_TRIG) &&
               !(gInputHold->button & gBoostButton[player->num]) && !(gInputHold->button & gBrakeButton[player->num])) {
        player->boostCooldown = true;
    }
    sp2C = 20.0f;
    if ((gInputHold->button & gBoostButton[player->num]) && !player->boostCooldown) {
        if (player->boostMeter == 0.0f) {
            player->unk_194 = 4.0f;
            player->unk_190 = 4.0f;
            Player_PlaySfx(player->sfxSource, NA_SE_ARWING_BOOST, player->num);
        }
        Math_SmoothStepToF(&D_ctx_801779A8[player->num], 30.0f, 1.0f, 10.0f, 0.0f);
        player->unk_190 = 2.0f;
        sp2C = 35.0f;
        player->boostActive = true;
        Math_SmoothStepToF(&player->boostMeter, 90.0f, 1.0f, 1.0f, 0.0f);
        if (player->boostMeter >= 90.0f) {
            player->boostCooldown = true;
        }
    }
    if ((gInputHold->button & gBrakeButton[player->num]) && !player->boostCooldown) {
        if (player->boostMeter == 0.0f) {
            Player_PlaySfx(player->sfxSource, NA_SE_ARWING_BRAKE, player->num);
        }
        Math_SmoothStepToF(&D_ctx_801779A8[player->num], 20.0f, 1.0f, 10.0f, 0.0f);
        sp2C = 5.0f;
        player->boostActive = true;
        Math_SmoothStepToF(&player->boostMeter, 90.0f, 1.0f, 1.0f, 0.0f);
        if (player->boostMeter >= 90.0f) {
            player->boostCooldown = true;
        }
    }
    Math_SmoothStepToF(&player->baseSpeed, sp2C, 0.1f, 2.0f, 0.001f);
}

void Player_UpdateTankJets(Player* player) {
    f32 temp;
    f32 temp2;

    player->gravity = 3.0f;
    if ((gInputHold->button & Z_TRIG) && !player->boostCooldown) {
        if (player->boostMeter == 0.0f) {
            Player_PlaySfx(player->sfxSource, NA_SE_ARWING_BOOST, player->num);
        }
        player->unk_188 = 0.0f;
        player->zRotBank += 4.0f;
        if (player->zRotBank > 50.0f) {
            player->zRotBank = 50.0f;
        }
        Math_SmoothStepToF(&player->unk_170, 1.0f, 1.0f, 0.4f, 0.0f);
        player->boostActive = true;
        Math_SmoothStepToF(&player->boostMeter, 90.0f, 1.0f, 0.7f, 0.0f);
        if (player->boostMeter >= 90.0f) {
            player->boostCooldown = true;
        }
    } else {
        if (player->zRotBank > 0.0f) {
            player->unk_188 += 1.5f;
            player->zRotBank -= player->unk_188;
            if (player->zRotBank <= 0.0f) {
                player->zRotBank = 0.0f;
                if (player->unk_188 > 3.0f) {
                    player->unk_188 *= -0.4f;
                    player->zRotBank -= player->unk_188;
                }
            }
        }
    }
    if ((gInputHold->button & R_TRIG) && !player->boostCooldown) {
        if (player->boostMeter == 0.0f) {
            Player_PlaySfx(player->sfxSource, NA_SE_ARWING_BOOST, player->num);
        }
        player->unk_188 = 0.0f;
        player->zRotBank -= 4.0f;
        if (player->zRotBank < -50.0f) {
            player->zRotBank = -50.0f;
        }
        Math_SmoothStepToF(&player->unk_16C, 1.0f, 1.0f, 0.4f, 0.0f);
        player->boostActive = true;
        Math_SmoothStepToF(&player->boostMeter, 90.0f, 1.0f, 0.7f, 0.0f);
        if (player->boostMeter >= 90.0f) {
            player->boostCooldown = true;
        }
    } else if (player->zRotBank < 0.0f) {
        player->unk_188 += 1.5f;
        player->zRotBank += player->unk_188;
        if (player->zRotBank >= 0.0f) {
            player->zRotBank = 0.0f;
            if (player->unk_188 > 3.0f) {
                player->unk_188 *= -0.4f;
                player->zRotBank += player->unk_188;
            }
        }
    }
    if ((player->unk_16C > 0.2f) && (player->unk_170 > 0.2f) && (player->radioDamageTimer == 0)) {
        player->zRotBank += (((__cosf(gGameFrameCount * M_DTOR * 8.0f) * 10.0f) - player->zRotBank) * 0.1f);
        Math_SmoothStepToAngle(&player->rot.x, 0.0f, 0.05f, 5.0f, 0.00001f);
        Math_SmoothStepToAngle(&player->rot.z, 0.0f, 0.05f, 5.0f, 0.00001f);
        temp = gInputPress->stick_y;
        Math_SmoothStepToF(&player->unk_000, temp * 0.5f, 0.05f, 5.0f, 0.00001f);
        Math_SmoothStepToF(&player->boostSpeed, 30.0f, 0.5f, 5.0f, 0.0f);
        player->gravity = -0.4f;
        Math_SmoothStepToF(&D_ctx_801779A8[player->num], 30.0f, 1.0f, 10.0f, 0.0f);
        if ((gCamCount == 1) && ((gGameFrameCount % 2) == 0)) {
            func_effect_8007BC7C(RAND_FLOAT_CENTERED(20.0f) + player->pos.x, player->groundPos.y + 10.0f,
                                 player->trueZpos - 10.0f, RAND_FLOAT(2.0f) + 4.0f);
        }
    } else if ((gCamCount == 1) && ((gGameFrameCount % 4) == 0) && (player->barrelRoll == 0)) {
        if ((player->unk_16C > 0.2f) && (player->radioDamageTimer == 0)) {
            func_effect_8007BC7C(RAND_FLOAT_CENTERED(10.0f) + (player->pos.x - 57.0f), player->groundPos.y + 10.0f,
                                 player->trueZpos - 10.0f, RAND_FLOAT(2.0f) + 3.0f);
        }
        if ((player->unk_170 > 0.2f) && (player->radioDamageTimer == 0)) {
            func_effect_8007BC7C(RAND_FLOAT_CENTERED(10.0f) + (player->pos.x + 57.0f), player->groundPos.y + 10.0f,
                                 player->trueZpos - 10.0f, RAND_FLOAT(2.0f) + 3.0f);
        }
    }
}

s32 D_800D3164[6] = {
    1, 1, -1, 1, -1, 1,
};

void Player_UpdateEffects(Player* player) {
    s32 i;

    player->xShake = 0.0f;
    player->basePos.x = player->pos.x;
    player->basePos.y = player->pos.y;
    player->basePos.z = player->pos.z;
    if (player->csTimer != 0) {
        player->csTimer--;
    }
    if (player->csEventTimer != 0) {
        player->csEventTimer--;
    }
    if (player->radioDamageTimer != 0) {
        player->radioDamageTimer--;
    }
    if (player->timer_498 != 0) {
        player->timer_498--;
    }
    if (player->timer_224 != 0) {
        player->timer_224--;
    }
    if (gVersusMode) {
        for (i = 0; i < gCamCount; i++) {
            if ((gVsLockOnTimers[player->num][i] != 0) && !(gControllerHold[i].button & A_BUTTON)) {
                gVsLockOnTimers[player->num][i]--;
            }
        }
    }
    if (gRightWingFlashTimer[player->num] != 0) {
        gRightWingFlashTimer[player->num]--;
        if (gRightWingFlashTimer[player->num] == 1000) {
            gRightWingFlashTimer[player->num] = 0;
        }
    }
    if (gLeftWingFlashTimer[player->num] != 0) {
        gLeftWingFlashTimer[player->num]--;
        if (gLeftWingFlashTimer[player->num] == 1000) {
            gLeftWingFlashTimer[player->num] = 0;
        }
    }
    if (gLeftWingDebrisTimer[player->num] != 0) {
        gLeftWingDebrisTimer[player->num]--;
    }
    if (gRightWingDebrisTimer[player->num] != 0) {
        gRightWingDebrisTimer[player->num]--;
    }
    if (gShieldTimer[player->num] != 0) {
        gShieldTimer[player->num]--;
        Math_SmoothStepToF(&gShieldAlpha[player->num], 128.0f, 1.0f, 40.0f, 0.01f);
    } else {
        Math_SmoothStepToF(&gShieldAlpha[player->num], 0.0f, 1.0f, 10.0f, 0.01f);
    }
    Math_SmoothStepToF(&gMuzzleFlashScale[player->num], 0.0f, 1.0f, 0.4f, 0.01f);
    if ((player->form == FORM_LANDMASTER) && (player->unk_1A0 != 0)) {
        player->unk_1A0--;
    }
    player->unk_200 = player->timer_224 & 1;
    if (player->timer_224 != 0) {
        gFillScreenAlphaStep = 8;
    }
    if (player->timer_224 == 19) {
        gFillScreenAlpha = 128;
        gFillScreenRed = 255;
        gFillScreenGreen = gFillScreenBlue = 0;
    }
    if (player->timer_278 != 0) {
        if ((player->timer_278 % 8) == 0) {
            if (player->timer_278 & 8) {
                gVsPoints[gPlayerNum]++;
            } else {
                gVsPoints[gPlayerNum]--;
            }
        }
        player->timer_278--;
    }
    if (player->hitTimer > 0) {
        if (player->hitTimer > 3) {
            *gControllerRumble = 1;
        }
        player->hitTimer--;
        if (player->form == FORM_ARWING) {
            player->damageShake = (SIN_DEG(player->hitTimer * 400.0f) * player->hitTimer) * D_800D3164[player->unk_21C];
            if (player->state_1C8 == PLAYERSTATE_1C8_ACTIVE) {
                player->xShake =
                    (SIN_DEG(player->hitTimer * 400.0f) * player->hitTimer) * D_800D3164[player->unk_21C] * 0.8f;
            }
        } else {
            player->damageShake =
                (SIN_DEG(player->hitTimer * 400.0f) * player->hitTimer) * D_800D3164[player->unk_21C] * 1.5f;
            player->xShake = 0.0f;
        }
        if ((gLevelMode != LEVELMODE_UNK_2) &&
            ((player->knockback.x != 0.f) || (player->knockback.y != 0.f) || (player->knockback.z != 0.f)) &&
            ((player->unk_1A4 >= 40) || (player->unk_1A4 == 21))) {
            player->boostCooldown = true;
            player->rot.x = 0;
            player->rot.y = 0;
            Math_SmoothStepToF(&player->boostSpeed, 0, 1.0f, 5.0f, 0);
        }
        if (player->hitTimer == 0) {
            player->damageShake = 0;
        }
    }
    player->pos.x += player->knockback.x;
    player->pos.y += player->knockback.y;
    if (gLevelMode == LEVELMODE_ALL_RANGE) {
        player->pos.z += player->knockback.z;
        Math_SmoothStepToF(&player->knockback.z, 0, 0.1f, 1.0f, 0.5f);
    }
    Math_SmoothStepToF(&player->knockback.x, 0, 0.1f, 1.0f, 0.5f);
    Math_SmoothStepToF(&player->knockback.y, 0, 0.1f, 1.0f, 0.5f);
    player->contrailScale -= 0.02f;
    if (player->contrailScale < 0.0f) {
        player->contrailScale = 0.0f;
    }
}

void Player_UpdateShields(Player* player) {
    if (player->damage > 0) {
        player->damage -= 2;
        if (player->damage <= 0) {
            player->damage = 0;
        }
        player->shields -= 2;
        if (player->shields <= 0) {
            player->shields = 0;
            player->damage = 0;
        }
    }
    if (player->heal > 0) {
        player->damage = 0;
        player->heal -= 2;
        if (player->heal <= 0) {
            player->heal = 0;
        }
        player->shields += 2;
        if (player->shields >= Play_GetMaxShields()) {
            player->shields = Play_GetMaxShields();
            player->heal = 0;
            Audio_KillSfxById(NA_SE_TEAM_SHIELD_UP);
        }
    }
}

void Player_LowHealthAlarm(Player* player) {
    s32 var_v0;

    Player_UpdateShields(player);

    if (player->shields < 128) {
        if (player->shields > 80) {
            var_v0 = 64 - 1;
        } else if (player->shields > 40) {
            var_v0 = 32 - 1;
        } else {
            var_v0 = 16 - 1;
        }
        if ((gGameFrameCount & var_v0) == 0) {
            Object_PlayerSfx(player->sfxSource, NA_SE_SHIELD_BUZZER, player->num);
        }
    }
}

void Play_dummy_800B41E0(Player* player) {
}

void Player_Down(Player* player) {
    player->state_1C8 = PLAYERSTATE_1C8_DOWN;
    if (!gVersusMode) {
        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 1);
        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 1);
        AUDIO_PLAY_BGM(NA_BGM_PLAYER_DOWN);
    }
    if (gCurrentLevel == LEVEL_SOLAR) {
        Audio_KillSfxById(NA_SE_OVERHEAT_ALARM);
    }
    Audio_StopPlayerNoise(player->num);
    Player_PlaySfx(player->sfxSource, NA_SE_ARWING_DOWN, player->num);
    player->shields = 0;
    player->csState = 0;
    player->hitTimer = 0;
    player->radioDamageTimer = 0;
    player->damageShake = 0.0f;
    gShowHud = 0;
}

void Player_UpdateOnRails(Player* player) {
    switch (player->form) {
        case FORM_ARWING:
            if (player->csTimer != 0) {
                gInputPress->stick_x = 0;
                gInputPress->stick_y = 0;
                gInputPress->button = 0;
                gInputHold->button = gBoostButton[player->num];
                player->boostMeter = 1.0f;
            }
            Player_ArwingBank(player);
            Player_ArwingBoost(player);
            Player_ArwingBrake(player);
            Play_dummy_800B41E0(player);
            Player_UpdateArwingRoll(player);
            if (player->somersault) {
                Player_PerformLoop(player);
            } else {
                Player_MoveArwingOnRails(player);
            }
            Player_UpdatePath(player);
            Player_Shoot(player);
            Player_CollisionCheck(player);
            Player_DamageEffects(player);
            Player_WaterEffects(player);
            Player_FloorCheck(player);
            Player_LowHealthAlarm(player);
            if ((player->shields <= 0) && (player->radioDamageTimer != 0)) {
                Player_Down(player);
                player->vel.x *= 0.2f;
                player->vel.y = 5.0f;
                player->rot.x = player->rot.y = 0.0f;
                player->alternateView = false;
                player->csTimer = 20;
                if (gLevelType == LEVELTYPE_SPACE) {
                    player->csTimer = 40;
                }
                player->csEventTimer = 120;
            }
            break;
        case FORM_LANDMASTER:
            Tank_UpdateOnRails(player);
            break;
        case FORM_BLUE_MARINE:
            Aquas_BlueMarineBoost(player);
            Aquas_BlueMarineBrake(player);
            Play_dummy_800B41E0(player);
            Aquas_BlueMarineMove(player);
            Player_UpdatePath(player);
            Aquas_BlueMarineShoot(player);
            Player_CollisionCheck(player);
            Player_FloorCheck(player);
            Player_LowHealthAlarm(player);
            if ((player->shields <= 0) && (player->radioDamageTimer != 0)) {
                Player_Down(player);
            }
            break;
    }
}

void Player_Update360(Player* player) {
    switch (player->form) {
        case FORM_ARWING:
            Player_ArwingBank(player);
            Player_ArwingBoost(player);
            Player_ArwingBrake(player);
            Play_dummy_800B41E0(player);
            Player_UpdateArwingRoll(player);
            if (player->somersault) {
                Player_PerformLoop(player);
            } else {
                Player_MoveArwing360(player);
            }
            Player_Shoot(player);
            Player_CollisionCheck(player);
            Player_WaterEffects(player);
            Player_FloorCheck(player);
            Player_LowHealthAlarm(player);
            if ((player->shields <= 0) && (player->radioDamageTimer != 0)) {
                Player_Down(player);
                player->vel.y = 5.0f;
                if (gLevelType == LEVELTYPE_SPACE) {
                    player->vel.y = 0.0f;
                }
                player->csTimer = 20;
                player->csEventTimer = 120;
                player->unk_000 = 0.0f;
                player->unk_004 = 1.0f;
                if (player->rot.y < 0.0f) {
                    player->unk_004 = -1.0f;
                }
                player->rot.x = 0.0f;
                player->aerobaticPitch = 0.0f;
            }
            break;
        case FORM_LANDMASTER:
            Player_UseTankJets(player);
            Player_UpdateTankJets(player);
            Player_TankBoostBrake(player);
            Play_dummy_800B41E0(player);
            Player_UpdateTankRoll(player);
            Player_MoveTank360(player);
            Player_Shoot(player);
            Player_CollisionCheck(player);
            Player_FloorCheck(player);
            Player_LowHealthAlarm(player);
            if ((player->shields <= 0) && (player->radioDamageTimer != 0)) {
                Player_Down(player);
            }
            break;
        case FORM_BLUE_MARINE:
            Aquas_Update360(player);
            break;
        case FORM_ON_FOOT:
            Player_OnFootUpdateSpeed(player);
            Player_MoveOnFoot(player);
            Player_Shoot(player);
            Player_CollisionCheck(player);
            Player_FloorCheck(player);
            Player_LowHealthAlarm(player);
            if ((player->shields <= 0) && (player->radioDamageTimer != 0)) {
                Player_Down(player);
            }
            break;
    }
}

void Player_LowHealthMsg(Player* player) {
    s32 teamId;

    if ((player->state_1C8 == PLAYERSTATE_1C8_ACTIVE) && (gTeamLowHealthMsgTimer >= 0)) {
        gTeamLowHealthMsgTimer++;
        if (gTeamLowHealthMsgTimer > 32 * 30) {
            gTeamLowHealthMsgTimer = 0;
            if (1) {}
            if ((player->shields < 64) && ((gTeamShields[TEAM_ID_FALCO] > 0) || (gTeamShields[TEAM_ID_PEPPY] > 0) ||
                                           (gTeamShields[TEAM_ID_SLIPPY] > 0))) {
                do {
                    do {
                        teamId = RAND_INT(2.9f) + 1;
                    } while (gTeamShields[teamId] <= 0);
                } while (0); // macro?
                switch (teamId) {
                    case 1:
                        if (Rand_ZeroOne() < 0.5f) {
                            Radio_PlayMessage(gMsg_ID_20306, RCID_FALCO);
                        } else {
                            Radio_PlayMessage(gMsg_ID_20309, RCID_FALCO);
                        }
                        break;
                    case 2:
                        if (Rand_ZeroOne() < 0.5f) {
                            Radio_PlayMessage(gMsg_ID_20305, RCID_SLIPPY);
                        } else {
                            Radio_PlayMessage(gMsg_ID_20308, RCID_SLIPPY);
                        }
                        break;
                    case 3:
                        if (Rand_ZeroOne() < 0.5f) {
                            Radio_PlayMessage(gMsg_ID_20304, RCID_PEPPY);
                        } else {
                            Radio_PlayMessage(gMsg_ID_20307, RCID_PEPPY);
                        }
                        break;
                }
            }
        }
    }
}

// lots of fakery
void Player_Update(Player* player) {
    f32 sp1CC;
    f32 sp1C8;
    s32 sp1C4;
    s32 i;
    Vec3f sp58[30];
    s32 pad;

    if (gVersusMode) {
        gInputHold = &gControllerHold[player->num];
        gInputPress = &gControllerPress[player->num];
        gControllerRumble = &gControllerRumbleFlags[player->num];
    } else {
        gInputHold = &gControllerHold[gMainController];
        gInputPress = &gControllerPress[gMainController];
        gControllerRumble = &gControllerRumbleFlags[gMainController];
    }

    D_ctx_80177990[player->num] += (s32) D_ctx_801779A8[player->num];
    Math_SmoothStepToF(&D_ctx_801779A8[player->num], 0.0f, 1.0f, 1.5f, 0.0f);
    if (D_ctx_80177990[player->num] >= 100) {
        D_ctx_80177990[player->num] -= 100;
        *gControllerRumble = 1;
    }
    if (gControllerRumbleTimers[player->num] != 0) {
        gControllerRumbleTimers[player->num]--;
        if ((gGameFrameCount % 2) == 0) {
            *gControllerRumble = 1;
        }
    }
    if (player->state_1C8 > PLAYERSTATE_1C8_INIT) {
        Player_UpdateEffects(player);
    }
    player->flags_228 = 0;
    if ((player->state_1C8 > PLAYERSTATE_1C8_INIT) && (player->form == FORM_ARWING) && !gVersusMode) {
        switch (player->unk_204) {
            case 0:
                sp1C4 = Animation_GetFrameData(&D_arwing_3015AF4, 0, sp58);
                break;
            case 1:
                sp1C4 = Animation_GetFrameData(&D_arwing_3015C28, 0, sp58);
                break;
            case 2:
                sp1C4 = Animation_GetFrameData(&D_arwing_30163C4, 0, sp58);
                break;
        }
        Math_SmoothStepToVec3fArray(sp58, player->jointTable, 1, sp1C4, 0.1f, 1.3f, 0.0f);
    }
    player->sfx.bank = player->sfx.roll = 0;
    sp1C4 = player->whooshTimer;
    if (sp1C4 != 0) {
        player->whooshTimer--;
    }
    switch (player->state_1C8) {
        case PLAYERSTATE_1C8_STANDBY:
            player->unk_234 = 0;
            gShowHud = 0;
            gPauseEnabled = 0;
            break;
        case PLAYERSTATE_1C8_INIT:
            Player_Setup(player);
            gFillScreenAlphaTarget = 0;
            gPauseEnabled = 0;
            break;
        case PLAYERSTATE_1C8_LEVEL_INTRO:
            gShowHud = 0;
            gPauseEnabled = 0;
            player->wings.modelId = 1;
            Cutscene_LevelStart(player);
            break;
        case PLAYERSTATE_1C8_ACTIVE:
            gShowHud = 1;
            Player_LowHealthMsg(player);
            player->wings.modelId = 0;
            D_hud_80161704 = 255;
            if ((!gVersusMode || (gVsMatchStart != 0)) && !player->somersault && (gInputPress->button & U_CBUTTONS) &&
                ((player->form == FORM_ARWING) || (gVersusMode && (player->form == FORM_LANDMASTER)))) {
                if (player->alternateView = 1 - player->alternateView) {
                    AUDIO_PLAY_SFX(NA_SE_VIEW_MOVE_IN, gDefaultSfxSource, 4);
                } else {
                    AUDIO_PLAY_SFX(NA_SE_VIEW_MOVE_OUT, gDefaultSfxSource, 4);
                    if (gLevelMode == LEVELMODE_ON_RAILS) {
                        player->camRoll = 0.0f;
                    }
                }
                player->unk_014 = 0.1f;
            }
            switch (gLevelMode) {
                case LEVELMODE_ON_RAILS:
                    gLoadLevelObjects = true;
                    Player_UpdateOnRails(player);
                    player->unk_234 = 1;
                    break;
                case LEVELMODE_ALL_RANGE:
                    if (!gVersusMode) {
                        Player_Update360(player);
                        player->unk_234 = 1;
                    } else if (gVsMatchStart != 0) {
                        if (gPlayerInactive[player->num] == true) {
                            do {
                                sp1C4 = RAND_INT(3.9f);
                            } while (gPlayerInactive[sp1C4]);
                            player->attacker = sp1C4 + 1;
                            player->state_1C8 = PLAYERSTATE_1C8_VS_STANDBY;
                            player->csState = 0;
                            Camera_FollowPlayer(player, player->attacker - 1, 1);
                        } else {
                            if (gVsMatchStart == 1) {
                                gVsMatchStart++;
                                for (i = 0; i < 4; i++) {
                                    Player_PlaySfx(gPlayer[i].sfxSource, NA_SE_ARWING_BOOST, gPlayer[i].num);
                                    gPlayer[i].unk_190 = gPlayer[i].unk_194 = 5.0f;
                                }
                            }
                            Player_Update360(player);
                            player->unk_234 = 1;
                        }
                    } else {
                        gInputPress->stick_x = gInputPress->stick_y = 0;
                        gVsItemSpawnTimer = 0;
                        gPauseEnabled = 0;
                    }
                    break;
                case LEVELMODE_UNK_2:
                    gLoadLevelObjects = true;
                    Turret_Update(player);
                    Player_CollisionCheck(player);
                    break;
            }
            break;
        case PLAYERSTATE_1C8_DOWN:
            Cutscene_PlayerDown(player);
            break;
        case PLAYERSTATE_1C8_U_TURN:
            if (gVersusMode) {
                gVsLockOnTimers[player->num][0] = gVsLockOnTimers[player->num][1] = gVsLockOnTimers[player->num][2] =
                    gVsLockOnTimers[player->num][3] = 0;
            }
            player->wings.modelId = 1;
            Math_SmoothStepToF(&player->wings.unk_04, 0.0f, 0.1f, 5.0f, 0);
            Math_SmoothStepToF(&player->wings.unk_08, 0.0f, 0.1f, 5.0f, 0);
            Math_SmoothStepToF(&player->wings.unk_0C, 0.0f, 0.1f, 5.0f, 0);
            Math_SmoothStepToF(&player->wings.unk_10, 0.0f, 0.1f, 5.0f, 0);
            Player_UpdateShields(player);
            Cutscene_UTurn(player);
            if (gCurrentLevel == LEVEL_KATINA) {
                Player_CollisionCheck(player);
            } else {
                Player_UpdateHitbox(player);
                Player_CheckItemCollect(player);
            }
            break;
        case PLAYERSTATE_1C8_LEVEL_COMPLETE:
            player->alternateView = false;
            gPauseEnabled = false;
            Player_UpdateShields(player);
            Cutscene_LevelComplete(player);
            Player_WaterEffects(player);
            gShowHud = gChargeTimers[player->num] = 0;
            break;
        case PLAYERSTATE_1C8_ENTER_WARP_ZONE:
            gPauseEnabled = 0;
            Player_UpdateShields(player);
            Cutscene_EnterWarpZone(player);
            gShowHud = 0;
            break;
        case PLAYERSTATE_1C8_START_360:
            gPauseEnabled = 0;
            Player_UpdateShields(player);
            Cutscene_AllRangeMode(player);
            Player_UpdateArwingRoll(player);
            gChargeTimers[player->num] = player->alternateView = gShowHud = 0;
            break;
        case PLAYERSTATE_1C8_GFOX_REPAIR:
            gPauseEnabled = 0;
            AllRange_GreatFoxRepair(player);
            gShowHud = 0;
            break;
        case PLAYERSTATE_1C8_ANDROSS_MOUTH:
            Andross_8018C390(player);
            Player_UpdateShields(player);
            break;
        case PLAYERSTATE_1C8_12:
            break;
        case PLAYERSTATE_1C8_VS_STANDBY:
            player->unk_234 = 0;
            if (gPlayerInactive[player->num] == true) {
                Camera_FollowPlayer(player, player->attacker - 1, 0);
            } else if ((gVsMatchOver == 0) && (player->csState != 0)) {
                player->csState = 0;
                Player_Initialize(player);
                Player_Setup(player);
                Player_Update360(player);
                Camera_Update360(player, 1);
                Player_PlaySfx(player->sfxSource, NA_SE_ARWING_BOOST, player->num);
                player->unk_190 = player->unk_194 = 5.0f;
            } else if (player->attacker >= 0) {
                if (player->attacker == 0) {
                    player->attacker = 1;
                }
                Camera_FollowPlayer(player, player->attacker - 1, 0);
            }
            break;
        case PLAYERSTATE_1C8_NEXT:
            gShowHud = 0;
            if (!gVersusMode) {
                gPauseEnabled = 0;
            }
            player->unk_234 = 0;
            player->vel.z = player->vel.x = player->vel.y = player->knockback.x = player->knockback.y = 0.0f;

            if ((gLevelMode == LEVELMODE_ALL_RANGE) && (gFadeoutType == 7)) {
                player->cam.eye.x += 1.0f;
                player->cam.eye.z += 1.5f;
            }
            if ((gCurrentLevel == LEVEL_ZONESS) || (gCurrentLevel == LEVEL_SOLAR)) {
                Math_SmoothStepToF(&player->cam.eye.y, 500.0f, 0.05f, 10.0f, 0.0f);
                Math_SmoothStepToF(&player->cam.eye.z, player->trueZpos + gPathProgress + 500.0f, 0.05f, 20.0f, 0.0f);
            }
            if (player->csTimer == 0) {
                if (gCamCount == 4) {
                    player->state_1C8 = PLAYERSTATE_1C8_VS_STANDBY;
                    player->csTimer = 200;
                } else {
                    gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
                    gFillScreenAlphaTarget = 255;
                }
                if (gFillScreenAlpha == 255) {
                    Play_ClearObjectData();
                    gPathProgress = gPlayer[0].zPath = 0.0f;
                    gPlayerGlareAlphas[0] = 0;
                    gShowAllRangeCountdown = gRadioState = 0;
                    Audio_ClearVoice();
                    Audio_SetEnvSfxReverb(0);
                    gSavedGoldRingCount[0] = gGoldRingCount[0];
                    if (gCurrentLevel == LEVEL_VENOM_ANDROSS) {
                        D_ctx_80177C94 = gGoldRingCount[0];
                    }
                    switch (gFadeoutType) {
                        case 7:
                            if (gCurrentLevel == LEVEL_TRAINING) {
                                gGameState = GSTATE_MENU;
                                gNextGameStateTimer = 2;
                                gOptionMenuStatus = OPTION_WAIT;
                                gDrawMode = DRAW_NONE;
                                gLastGameState = GSTATE_PLAY;
                                gStarCount = 0;
                            } else {
                                if ((gCurrentLevel == LEVEL_SECTOR_X) || (gCurrentLevel == LEVEL_METEO)) {
                                    gLevelPhase = 0;
                                }
                                if (gLifeCount[gPlayerNum] < 0) {
                                    gNextGameState = GSTATE_GAME_OVER;
                                    gSavedGoldRingCount[0] = 0;
                                } else {
                                    gPlayState = PLAY_INIT;
                                }
                                gBombCount[gPlayerNum] = 3;
                                gLaserStrength[gPlayerNum] = LASERS_SINGLE;
                                gLoadLevelObjects = true;
                                gDrawMode = DRAW_NONE;
                            }
                            break;
                        case 4:
                            gNextGameState = GSTATE_MAP;
                            gLastGameState = GSTATE_PLAY;
                            gDrawMode = DRAW_NONE;
                            break;
                        default:
                            gDrawMode = DRAW_NONE;
                            break;
                    }
                    if (1) {}
                }
            }
            break;
        default:
            break;
    }
    if ((D_ctx_80177C70 == 0) && (player->form == FORM_ARWING)) {
        sp1CC = 0.77699995f;
        sp1C8 = 1100.0f;
    } else if (D_ctx_80177C70 == 2) {
        sp1CC = 0.77699995f;
        sp1C8 = 1100.0f;
    } else {
        sp1CC = 0.74f;
        sp1C8 = 700.0f;
    }
    Math_SmoothStepToF(&player->unk_148, sp1CC, 1.0f, 0.05f, 0.0f);
    Math_SmoothStepToF(&player->unk_14C, sp1CC, 1.0f, 0.05f, 0.0f);
    Math_SmoothStepToF(&player->pathWidth, sp1C8, 1.0f, 10.0f, 0.0f);
    if (player->form == FORM_ARWING) {
        Math_SmoothStepToF(&player->unk_194, player->unk_190, 0.5f, 5.0f, 0.0f);
        if (player->boostCooldown && (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_ACTIVE)) {
            player->unk_190 = 0.5f;
        } else {
            player->unk_190 = 1.0f;
        }

    } else if (player->form == FORM_LANDMASTER) {
        Math_SmoothStepToF(&player->unk_194, player->unk_190, 0.5f, 0.5f, 0.0f);
        player->unk_190 = 0.0f;
    }
}

void Camera_UpdateArwingOnRails(Player* player) {
    f32 var_fv1;
    f32 var_fv0;
    f32 temp;

    gCsCamEyeX = (player->pos.x - player->xPath) * player->unk_148;
    if (((player->form == FORM_ARWING) && (player->state_1C8 == PLAYERSTATE_1C8_ACTIVE)) ||
        (player->state_1C8 == PLAYERSTATE_1C8_U_TURN)) {
        gCsCamEyeY = (player->pos.y - player->yPath) * player->unk_148;
    }
    var_fv1 = gInputPress->stick_x;
    var_fv0 = -gInputPress->stick_y;

    if ((player->state_1C8 != PLAYERSTATE_1C8_ACTIVE) || player->somersault) {
        var_fv0 = 0.0f;
        var_fv1 = 0;
    }
    Math_SmoothStepToF(&player->unk_030, var_fv1 * 1.6f, 0.1f, 3.0f, 0.05f);
    if (gLevelType == LEVELTYPE_SPACE) {
        Math_SmoothStepToF(&player->unk_02C, var_fv0 * 0.8f, 0.1f, 3.0f, 0.05f);
    } else if (player->pos.y < (gGroundHeight + 50.0f)) {
        Math_SmoothStepToF(&player->unk_02C, var_fv0 * 0.3f, 0.1f, 3.0f, 0.05f);
    } else {
        Math_SmoothStepToF(&player->unk_02C, 2.0f * var_fv0, 0.1f, 4.0f, 0.05f);
    }
    gCsCamEyeX -= player->unk_030 * 1.5f;
    gCsCamEyeY -= player->unk_02C - 50.0f;
    gCsCamAtX = (player->pos.x - player->xPath) * player->unk_14C;
    gCsCamAtX += player->xShake * -2.0f;
    gCsCamAtX -= player->unk_030 * 0.5f;
    gCsCamAtY = ((player->pos.y - player->yPath) * player->unk_14C) + 20.0f;
    gCsCamAtY += player->xRock * 5.0f;
    gCsCamAtY -= player->unk_02C * 0.25f;
    switch (sOverheadCam) {
        case 0:
            Math_SmoothStepToF(&sOverheadCamDist, 0.0f, 0.4f, 10.0f, 0);
            break;
        case 1:
            Math_SmoothStepToF(&sOverheadCamDist, 200.0f, 0.4f, 10.0f, 0);
            break;
    }
    gCsCamEyeX += player->xPath;
    gCsCamAtX += player->xPath;
    gCsCamEyeY += player->yPath + sOverheadCamDist;
    gCsCamAtZ = player->trueZpos + gPathProgress - 1.0f;
    gCsCamEyeZ = 400.0f + sOverheadCamDist;
    if (D_ctx_80177C70 == 2) {
        gCsCamEyeZ -= 50.0f;
    }
    if (player->somersault) {
        gCsCamEyeZ += 200.0f;
        gCsCamAtY = (player->pos.y - player->yPath) * 0.9f;
        Math_SmoothStepToF(&player->cam.eye.z, gCsCamEyeZ, 0.1f, 8.0f, 0.0f);
        Math_SmoothStepToF(&player->unk_018, 0.2f, 1.0f, 0.05f, 0.0f);
    } else {
        Math_SmoothStepToF(&player->cam.eye.z, gCsCamEyeZ, 0.2f, 20.0f, 0.0f);
        Math_SmoothStepToF(&player->unk_018, 1.0f, 1.0f, 0.05f, 0.0f);
    }
    gCsCamAtY += player->yPath + (sOverheadCamDist * 0.5f);
    Math_SmoothStepToF(&player->cam.eye.x, gCsCamEyeX, player->unk_014, 1000.0f, 0.0f);
    Math_SmoothStepToF(&player->cam.eye.y, gCsCamEyeY, player->unk_018, 1000.0f, 0.0f);
    Math_SmoothStepToF(&player->cam.at.x, gCsCamAtX, player->unk_014, 1000.0f, 0.0f);
    Math_SmoothStepToF(&player->cam.at.y, gCsCamAtY, player->unk_018, 1000.0f, 0.0f);
    Math_SmoothStepToF(&player->cam.at.z, gCsCamAtZ, player->unk_014, 1000.0f, 0.0f);
    Math_SmoothStepToF(&player->unk_014, 1.0f, 1.0f, 0.05f, 0.0f);
    temp = -player->rot.z;
    if (gLevelType == LEVELTYPE_PLANET) {
        Math_SmoothStepToF(&player->camRoll, temp * 0.3f, 0.1f, 1.5f, 0.0f);
    } else if (gLevelType == LEVELTYPE_SPACE) {
        Math_SmoothStepToF(&player->camRoll, temp * 0.2f, 0.1f, 1.5f, 0.0f);
    }
}

void Camera_UpdateCockpitOnRails(Player* player, s32 arg1) {
    Vec3f sp4C;
    Vec3f sp40;
    s32 pad;
    s32 pad2;
    s32 pad3;

    Matrix_RotateY(gCalcMatrix, (player->rot.y + player->damageShake) * M_DTOR * 0.75f, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, (player->rot.x + player->damageShake) * M_DTOR * 0.75f, MTXF_APPLY);
    sp4C.x = 0;
    sp4C.y = 0;
    sp4C.z = -1000.0f;
    Matrix_MultVec3f(gCalcMatrix, &sp4C, &sp40);
    gCsCamEyeX = player->pos.x;
    gCsCamEyeY = player->pos.y + player->yBob;
    gCsCamEyeZ = player->trueZpos + gPathProgress;
    gCsCamAtX = player->pos.x + sp40.x;
    gCsCamAtY = player->pos.y + player->yBob + sp40.y;
    gCsCamAtZ = player->trueZpos + gPathProgress + sp40.z;
    Math_SmoothStepToF(&player->cam.eye.x, gCsCamEyeX, player->unk_014, 100.0f, 0.0f);
    Math_SmoothStepToF(&player->cam.eye.y, gCsCamEyeY, player->unk_014, 100.0f, 0.0f);
    Math_SmoothStepToF(&player->cam.eye.z, gCsCamEyeZ, player->unk_014, 50.0f, 0.0f);
    Math_SmoothStepToF(&player->cam.at.x, gCsCamAtX, player->unk_014, 100.0f, 0.0f);
    Math_SmoothStepToF(&player->cam.at.y, gCsCamAtY, player->unk_014, 100.0f, 0.0f);
    Math_SmoothStepToF(&player->cam.at.z, gCsCamAtZ, player->unk_014, 100.0f, 0.0f);
    Math_SmoothStepToF(&player->unk_014, 1.0f, 1.0f, 0.05f, 0);
    player->camRoll = -(player->bankAngle + player->rockAngle);
    if (arg1 != 0) {
        player->cam.eye.x = gCsCamEyeX;
        player->cam.eye.y = gCsCamEyeY;
        player->cam.eye.z = gCsCamEyeZ;
        player->cam.at.x = gCsCamAtX;
        player->cam.at.y = gCsCamAtY;
        player->cam.at.z = gCsCamAtZ;
    }
}

void Camera_FollowPlayer(Player* player, s32 playerNum, bool arg2) {
    u8 i;
    u8 var_v0;
    Vec3f sp58;
    Vec3f sp4C;

    var_v0 = 0x7F;
    if (gPlayer[playerNum].form == FORM_LANDMASTER) {
        var_v0 = 0xFF;
    }
    if (((var_v0 & gGameFrameCount) == (gPlayerNum * 32)) || arg2) {
        for (i = 0; i < 100; i++) {
            playerNum = RAND_INT(3.9f);
            if ((gPlayer[playerNum].state_1C8 != PLAYERSTATE_1C8_VS_STANDBY) && !gPlayerInactive[playerNum]) {
                break;
            }
        }
        if (i > 90) {
            playerNum = 0;
        }
        player->attacker = playerNum + 1;
        Matrix_RotateY(gCalcMatrix, gPlayer[playerNum].yRot_114 * M_DTOR, MTXF_NEW);
        switch (gPlayer[playerNum].form) {
            case FORM_ARWING:
                sp58.x = 300.0f;
                sp58.z = -800.0f;
                break;
            case FORM_LANDMASTER:
                sp58.x = 300.0f;
                sp58.z = -400.0f;
                break;
            case FORM_ON_FOOT:
                sp58.x = 100.0f;
                sp58.z = -300.0f;
                break;
        }
        if (Rand_ZeroOne() < 0.5f) {
            sp58.x *= -1.0f;
        }
        sp58.y = 0.0f;
        Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp58, &sp4C);
        player->cam.eye.x = gPlayer[playerNum].pos.x + sp4C.x;
        player->cam.eye.y = gPlayer[playerNum].pos.y + 50.0f;
        player->cam.eye.z = gPlayer[playerNum].trueZpos + sp4C.z;
    }
    player->cam.at.x = gPlayer[playerNum].pos.x;
    player->cam.at.y = gPlayer[playerNum].pos.y;
    player->cam.at.z = gPlayer[playerNum].trueZpos;
    switch (gPlayer[playerNum].form) {
        case FORM_ARWING:
            player->cam.eye.x += gPlayer[playerNum].vel.x * 0.5f;
            player->cam.eye.z += gPlayer[playerNum].vel.z * 0.5f;
            break;
        case FORM_LANDMASTER:
            player->cam.eye.x += gPlayer[playerNum].vel.x * 0.7f;
            player->cam.eye.z += gPlayer[playerNum].vel.z * 0.7f;
            break;
        case FORM_ON_FOOT:
            player->cam.eye.x += gPlayer[playerNum].vel.x * 0.7f;
            player->cam.eye.z += gPlayer[playerNum].vel.z * 0.7f;
            player->cam.eye.y = gPlayer[playerNum].groundPos.y + 20.0f;
            player->cam.at.y = gPlayer[playerNum].groundPos.y + 20.0f;
            break;
    }
    Math_SmoothStepToF(&player->camRoll, 0.0f, 0.05f, 5.0f, 0.00001f);
}

void Camera_UpdateArwing360(Player* player, s32 arg1) {
    Vec3f sp74;
    Vec3f sp68;
    f32 temp1;
    f32 temp2;
    f32 temp3;
    f32 var_fv0;
    f32 eyeX;
    f32 eyeY;
    f32 eyeZ;
    f32 atX;
    f32 atY;
    f32 atZ;

    Matrix_RotateY(gCalcMatrix, (player->yRot_114 + (player->damageShake * 0.2f)) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, player->damageShake * 0.2f * M_DTOR, MTXF_APPLY);
    sp74.x = 0.0f;
    sp74.y = 0.0f;
    if (player->alternateView) {
        sp74.z = 1000.0f - player->camDist;
    } else {
        sp74.z = 300.0f - player->camDist;
    }
    if (player->somersault) {
        sp74.z += 500.0f;
    }
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp74, &sp68);
    if (!gVersusMode) {
        var_fv0 = -gInputPress->stick_y;
    } else {
        var_fv0 = -gControllerPress[player->num].stick_y;
    }
    Math_SmoothStepToF(&player->unk_02C, var_fv0, 0.05f, 5.0f, 0.0f);
    eyeX = player->pos.x + sp68.x;
    eyeY = (player->pos.y * player->unk_148) + 50.0f;
    eyeY -= (player->unk_02C * 1.5f);
    eyeZ = player->pos.z + sp68.z;

    atX = player->pos.x + player->damageShake;

    var_fv0 = (player->somersault) ? 1.0f : 0.79f;
    atY = (player->pos.y * (var_fv0)) + player->damageShake + (player->xRock * 5.0f);
    atY += (player->unk_02C * 0.5f);
    if (player->state_1C8 == PLAYERSTATE_1C8_U_TURN) {
        atY = player->pos.y;
    }
    atZ = player->pos.z;
    Math_SmoothStepToF(&player->unk_028, 2.0f * player->rot.y, 0.05f, 2.0f, 0.02f);
    sp74.x = -player->unk_028;
    sp74.y = 0.0f;
    sp74.z = 0.f;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp74, &sp68);
    eyeX += sp68.x;
    eyeZ += sp68.z;
    atX += sp68.x;
    atZ += sp68.z;
    if (player->state_1C8 == PLAYERSTATE_1C8_ACTIVE) {
        Math_SmoothStepToF(&player->cam.eye.x, eyeX, player->unk_014, 30000.0f, 0);
        Math_SmoothStepToF(&player->cam.eye.y, eyeY, player->unk_014, 30000.0f, 0);
        Math_SmoothStepToF(&player->cam.eye.z, eyeZ, player->unk_014, 30000.0f, 0);
        Math_SmoothStepToF(&player->camRoll, player->rot.y * -0.3f, 0.1f, 1.0f, 0);
        Math_SmoothStepToF(&player->unk_014, 0.2f, 0.1f, 0.005f, 0.0f);
    }
    Math_SmoothStepToF(&player->cam.at.x, atX, player->unk_01C, 30000.0f, 0);
    Math_SmoothStepToF(&player->cam.at.y, atY, player->unk_018, 30000.0f, 0);
    Math_SmoothStepToF(&player->cam.at.z, atZ, player->unk_01C, 30000.0f, 0);
    Math_SmoothStepToF(&player->unk_018, 0.2f, 0.1f, 0.005f, 0);
    Math_SmoothStepToF(&player->unk_01C, 1.0f, 0.1f, 0.005f, 0);
    if (arg1 != 0) {
        player->cam.eye.x = eyeX;
        player->cam.eye.y = eyeY;
        player->cam.eye.z = eyeZ;
        player->cam.at.x = atX;
        player->cam.at.y = atY;
        player->cam.at.z = atZ;
    }
}

void Camera_UpdateTank360(Player* player, s32 arg1) {
    Vec3f sp54;
    Vec3f sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;

    Matrix_RotateX(gCalcMatrix, player->rot.x * M_DTOR, MTXF_NEW);
    Matrix_RotateZ(gCalcMatrix, player->rot.z * M_DTOR, MTXF_APPLY);
    Matrix_RotateY(gCalcMatrix, (player->yRot_114 + (player->damageShake * 0.2f)) * M_DTOR, MTXF_APPLY);
    Matrix_RotateX(gCalcMatrix, player->damageShake * 0.2f * M_DTOR, MTXF_APPLY);
    sp54.x = 0.0f;
    if (player->alternateView) {
        sp54.y = 150.0f;
        sp54.z = 500.0f - player->camDist;
    } else {
        sp54.y = 100.0f;
        sp54.z = 250.0f - player->camDist;
    }
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp54, &sp48);
    if (player->alternateView) {
        Math_SmoothStepToF(&player->unk_02C, -player->unk_17C * 3.0f + 30.0f, 0.2f, 8.0f, 0.001f);
    } else {
        Math_SmoothStepToF(&player->unk_02C, -player->unk_17C * 3.0f, 0.2f, 8.0f, 0.001f);
    }
    sp44 = player->pos.x + sp48.x;
    sp40 = player->pos.y + sp48.y - (player->unk_02C * 0.6f);
    sp3C = player->pos.z + sp48.z;

    player->cam.at.x = player->pos.x + player->damageShake;
    player->cam.at.y = player->pos.y + 60.0f + player->unk_02C + player->damageShake;
    player->cam.at.z = player->pos.z;
    Math_SmoothStepToF(&player->unk_028, 2.0f * player->rot.y, 0.05f, 2.0f, 0.02f);
    sp54.x = -player->unk_028;
    sp54.y = 0.0f;
    sp54.z = 0.0f;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp54, &sp48);
    sp44 += sp48.x;
    sp3C += sp48.z;
    player->cam.at.x += sp48.x;
    player->cam.at.z += sp48.z;
    Math_SmoothStepToF(&player->cam.eye.x, sp44, 0.1f, 200.0f, 0.001f);
    Math_SmoothStepToF(&player->cam.eye.y, sp40, 0.1f, 200.0f, 0.001f);
    Math_SmoothStepToF(&player->cam.eye.z, sp3C, 0.1f, 200.0f, 0.001f);
    Math_SmoothStepToF(&player->camRoll, player->zRotBank * -0.1f, 0.1f, 1.0f, 0.01f);
    if (arg1 != 0) {
        player->cam.eye.x = sp44;
        player->cam.eye.y = sp40;
        player->cam.eye.z = sp3C;
    }
}

void Camera_UpdateOnFoot360(Player* player, s32 arg1) {
    Vec3f sp64;
    Vec3f sp58;
    Vec3f sp4C;

    Matrix_RotateX(gCalcMatrix, player->xRot_0FC * M_DTOR, MTXF_NEW);
    Matrix_RotateZ(gCalcMatrix, player->zRot_0FC * M_DTOR, MTXF_APPLY);
    Matrix_RotateY(gCalcMatrix, (player->yRot_114 + (player->damageShake * 0.02f)) * M_DTOR, MTXF_APPLY);
    Matrix_RotateX(gCalcMatrix, player->damageShake * 0.02f * M_DTOR, MTXF_APPLY);
    sp64.x = 0.0f;
    sp64.y = 20.0f;
    sp64.z = 60.0f - player->camDist;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp64, &sp58);
    Math_SmoothStepToF(&player->unk_02C, -player->unk_158 * 0.5f, 0.07f, 3.0f, 0.001f);

    sp4C.x = player->pos.x + sp58.x;
    sp4C.y = player->groundPos.y + 10.0f + sp58.y - (player->unk_02C * 0.8f);
    sp4C.z = player->pos.z + sp58.z;

    player->cam.at.x = player->pos.x + player->damageShake * 0.1f;
    player->cam.at.y = player->groundPos.y + (player->pos.y - player->groundPos.y) * 0.4f + 18.0f +
                       player->unk_02C * 1.5f + player->damageShake * 0.1f;
    player->cam.at.z = player->pos.z;

    Math_SmoothStepToF(&player->unk_028, player->rot.y * (player->baseSpeed + 5.0f) * 0.04f, 0.05f, 2.0f, 0.02f);
    sp64.x = -player->unk_028;
    sp64.y = 0.0f;
    sp64.z = 0.0f;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp64, &sp58);
    sp4C.x += sp58.x;
    sp4C.z += sp58.z;
    player->cam.at.x += sp58.x;
    player->cam.at.z += sp58.z;

    Math_SmoothStepToF(&player->cam.eye.x, sp4C.x, 0.3f, 65.0f, 0.001f);
    Math_SmoothStepToF(&player->cam.eye.y, sp4C.y, 0.3f, 65.0f, 0.001f);
    Math_SmoothStepToF(&player->cam.eye.z, sp4C.z, 0.3f, 65.0f, 0.001f);
    Math_SmoothStepToF(&player->camRoll, player->zRotBank * -0.1f, 0.1f, 1.0f, 0.01f);
    if (arg1 != 0) {
        player->cam.eye.x = sp4C.x;
        player->cam.eye.y = sp4C.y;
        player->cam.eye.z = sp4C.z;
    }
}

void Camera_SetStarfieldPos(f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt) {
    f32 sp34;
    f32 sp30;
    f32 pitch;
    f32 yaw;
    f32 tempf;
    f32 sp20;

    yaw = -Math_Atan2F(xEye - xAt, zEye - zAt);
    tempf = sqrtf(SQ(zEye - zAt) + SQ(xEye - xAt));
    pitch = -Math_Atan2F(yEye - yAt, tempf);
    if (yaw >= M_PI / 2) {
        yaw -= M_PI;
    }
    if (yaw <= -M_PI / 2) {
        yaw += M_PI;
    }
    tempf = 0.0f;
    if (gCurrentLevel == LEVEL_UNK_15) {
        tempf = gPlayer[0].cam.eye.y * 0.03f;
    }
    sp30 = (-pitch * (-8.0f / 3.0f * M_RTOD) * 2.0f) + 3000.0f + gStarfieldScrollY + tempf;
    sp34 = (yaw * (-8.0f / 3.0f * M_RTOD) * 2.0f) + 3000.0f + gStarfieldScrollX;
    sp20 = gStarfieldX;
    gStarfieldX = Math_ModF(sp34, SCREEN_WIDTH * 1.5f);
    gStarfieldY = Math_ModF(sp30, SCREEN_HEIGHT * 1.5f);
    if ((gGameState == GSTATE_PLAY) && (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_LEVEL_INTRO) &&
        (gCurrentLevel == LEVEL_METEO)) {
        if (fabsf(gStarfieldX - sp20) < 50.0f) {
            D_bg_8015F96C = 0.0f;
            if (fabsf(gStarfieldX - sp20) > 3.0f) {
                D_bg_8015F96C = fabsf(gStarfieldX - sp20 - 3.0f) * 0.5f;
            }
        }
    }
}

void Camera_Update360(Player* player, s32 arg1) {
    switch (player->form) {
        case FORM_ON_FOOT:
            Camera_UpdateOnFoot360(player, arg1);
            break;
        case FORM_LANDMASTER:
            Camera_UpdateTank360(player, arg1);
            break;
        case FORM_ARWING:
            Camera_UpdateArwing360(player, arg1);
            break;
    }
}

void Camera_Update(Player* player) {
    switch (player->state_1C8) {
        case PLAYERSTATE_1C8_ACTIVE:
            switch (gLevelMode) {
                case LEVELMODE_ON_RAILS:
                    if (player->form == FORM_ARWING) {
                        if (!player->alternateView) {
                            Camera_UpdateArwingOnRails(player);
                        } else {
                            Camera_UpdateCockpitOnRails(player, 0);
                        }
                    } else if (player->form == FORM_LANDMASTER) {
                        Player_UpdateTankCamOnRails(player);
                    } else if (player->form == FORM_BLUE_MARINE) {
                        Aquas_UpdateCamera(player);
                    }
                    break;
                case LEVELMODE_ALL_RANGE:
                    Camera_Update360(player, 0);
                    break;
                case LEVELMODE_UNK_2:
                    Turret_UpdateCamera(player);
                    break;
            }
            break;
        case PLAYERSTATE_1C8_U_TURN:
            player->camRoll -= player->camRoll * 0.1f;
            Camera_Update360(player, 0);
            break;
        case PLAYERSTATE_1C8_DOWN:
            if ((gLevelMode == LEVELMODE_ON_RAILS) && (player->form == FORM_ARWING)) {
                player->cam.eye.x += (player->pos.x - player->cam.eye.x) * 0.1f;
                player->cam.eye.y += (player->pos.y - player->cam.eye.y) * 0.1f;
                player->cam.eye.z -= player->vel.z * 0.2f;
                if (player->csState != 0) {
                    player->cam.eye.z -= player->vel.z * 0.2f;
                }
                player->cam.at.x += (player->pos.x - player->cam.at.x) * 0.1f;
                player->cam.at.y += (player->pos.y - player->cam.at.y) * 0.1f;
                player->cam.at.z = player->trueZpos + gPathProgress - 1.0f;
            }
            break;
        case PLAYERSTATE_1C8_NEXT:
        case PLAYERSTATE_1C8_LEVEL_COMPLETE:
            break;
    }
}

void Camera_SetupLights(Player* player) {
    Vec3f sp44;
    Vec3f sp38;
    f32 pad;

    if ((gCurrentLevel == LEVEL_AQUAS) && (gPlayer[0].state_1C8 != PLAYERSTATE_1C8_LEVEL_INTRO)) {
        gEnvLightyRot = gLight1yRotTarget = gLight1yRotTarget = gLight2yRotTarget = gLight1yRotTarget = 110.0f;
        if ((gGameFrameCount & 0x20) != 0) {
            gEnvLightyRot = gLight1yRotTarget = gLight1yRotTarget = gLight2yRotTarget = gLight1yRotTarget = 90.0f;
        }
        gLight1rotStep = gLight2rotStep = D_ctx_80178538 = 1.0f;
    }
    Math_SmoothStepToAngle(&gLight1xRot, gLight1xRotTarget, 1.0f, gLight1rotStep, 0.0f);
    Math_SmoothStepToAngle(&gLight1yRot, gLight1yRotTarget, 1.0f, gLight1rotStep, 0.0f);
    Math_SmoothStepToAngle(&gLight1zRot, gLight1zRotTarget, 1.0f, gLight1rotStep, 0.0f);

    if (gLight2R < gLight2RTarget) {
        gLight2R += gLight2colorStep;
        if (gLight2RTarget < gLight2R) {
            gLight2R = gLight2RTarget;
        }
    }
    if (gLight2RTarget < gLight2R) {
        gLight2R -= gLight2colorStep;
        if (gLight2R < gLight2RTarget) {
            gLight2R = gLight2RTarget;
        }
    }
    if (gLight2G < gLight2GTarget) {
        gLight2G += gLight2colorStep;
        if (gLight2GTarget < gLight2G) {
            gLight2G = gLight2GTarget;
        }
    }
    if (gLight2GTarget < gLight2G) {
        gLight2G -= gLight2colorStep;
        if (gLight2G < gLight2GTarget) {
            gLight2G = gLight2GTarget;
        }
    }
    if (gLight2B < gLight2BTarget) {
        gLight2B += gLight2colorStep;
        if (gLight2BTarget < gLight2B) {
            gLight2B = gLight2BTarget;
        }
    }
    if (gLight2BTarget < gLight2B) {
        gLight2B -= gLight2colorStep;
        if (gLight2B < gLight2BTarget) {
            gLight2B = gLight2BTarget;
        }
    }
    Math_SmoothStepToAngle(&gLight2xRot, gLight2xRotTarget, 1.0f, gLight2rotStep, 0.0f);
    Math_SmoothStepToAngle(&gLight2yRot, gLight2yRotTarget, 1.0f, gLight2rotStep, 0.0f);
    Math_SmoothStepToAngle(&gLight2zRot, gLight2zRotTarget, 1.0f, gLight2rotStep, 0.0f);
    gLight2xRotTarget = gLight1xRotTarget = gEnvLightxRot;
    gLight2yRotTarget = gLight1yRotTarget = gEnvLightyRot;
    gLight2zRotTarget = gLight1zRotTarget = gEnvLightzRot;
    gLight1rotStep = 5.0f;
    gLight2RTarget = gLight1R;
    gLight2GTarget = gLight1G;
    gLight2BTarget = gLight1B;
    pad = player->camRoll;
    Matrix_RotateZ(gCalcMatrix, M_DTOR * pad, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -player->camPitch, MTXF_APPLY);
    Matrix_RotateY(gCalcMatrix, player->camYaw, MTXF_APPLY);
    Matrix_Push(&gCalcMatrix);
    Matrix_RotateX(gCalcMatrix, M_DTOR * gLight1xRot, MTXF_APPLY);
    Matrix_RotateY(gCalcMatrix, M_DTOR * gLight1yRot, MTXF_APPLY);
    Matrix_RotateZ(gCalcMatrix, M_DTOR * gLight1zRot, MTXF_APPLY);
    sp44.x = 0.0f;
    sp44.y = 0.0f;
    sp44.z = 100.0f;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp44, &sp38);
    gLight1x = sp38.x;
    gLight1y = sp38.y;
    gLight1z = sp38.z;
    Matrix_Pop(&gCalcMatrix);
    Matrix_RotateX(gCalcMatrix, M_DTOR * gLight2xRot, MTXF_APPLY);
    Matrix_RotateY(gCalcMatrix, M_DTOR * gLight2yRot, MTXF_APPLY);
    Matrix_RotateZ(gCalcMatrix, M_DTOR * gLight2zRot, MTXF_APPLY);
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp44, &sp38);
    gLight2x = sp38.x;
    gLight2y = sp38.y;
    gLight2z = sp38.z;
}

void Play_UpdateLevel(void) {
    s32 cycleMask;
    s32 sp40;
    f32 sp3C;
    u8 shields;
    u8 heightParam;

    switch (gCurrentLevel) {
        case LEVEL_TRAINING:
            if (gLevelMode == LEVELMODE_ALL_RANGE) {
                Training_8019949C();
            }
            break;
        case LEVEL_VERSUS:
            func_versus_800C26C8();
            gVsItemSpawnTimer++;
            if ((gVsItemSpawnTimer == 200) && (gLaserStrength[0] == LASERS_SINGLE) &&
                (gLaserStrength[1] == LASERS_SINGLE) && (gLaserStrength[2] == LASERS_SINGLE) &&
                (gLaserStrength[3] == LASERS_SINGLE)) {
                Play_SpawnVsItem(OBJ_ITEM_LASERS, &gItems[0]);
            }
            if ((gVsItemSpawnTimer == 400) && (gBombCount[0] == 0) && (gBombCount[1] == 0) && (gBombCount[2] == 0) &&
                (gBombCount[3] == 0)) {
                Play_SpawnVsItem(OBJ_ITEM_BOMB, &gItems[1]);
            }
            if (gVsItemSpawnTimer == 500) {
                gVsItemSpawnTimer = 0;
            }
            break;
        case LEVEL_VENOM_2:
            if ((gPlayer[0].state_1C8 != PLAYERSTATE_1C8_LEVEL_COMPLETE) && (gLevelPhase == 2)) {
                gPlayer[0].state_1C8 = PLAYERSTATE_1C8_LEVEL_COMPLETE;
                gPlayer[0].csState = 0;
                gPlayer[0].unk_234 = 1;
                gPlayer[0].pos.z = 15000.0f;
                Camera_Update360(gPlayer, 1);
                gFillScreenAlpha = 255;
                gFillScreenAlphaStep = 255;
                gFillScreenAlphaTarget = 255;

                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
            }
            break;
        case LEVEL_VENOM_ANDROSS:
            Andross_8018BDD8();
            gGroundHeight = -25000.0f;
            gPlayer[0].pathHeight = 612.0f;
            gPlayer[0].pathFloor = -544.0f;
            if (gStartAndrossFightTimer != 0) {
                gStartAndrossFightTimer--;
                if (gStartAndrossFightTimer == 0) {
                    Andross_80189214();
                }
            }
            break;
        case LEVEL_METEO:
            Texture_Scroll(D_102FF08, 8, 8, 1);
            /* fallthrough */
        case LEVEL_SECTOR_X:
            if (gLevelPhase == 1) {
                gBlurAlpha = 128;
                if (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_LEVEL_COMPLETE) {
                    Math_SmoothStepToF(&gWarpZoneBgAlpha, 0.0f, 1.0f, 1.0f, 0.0f);
                } else {
                    Math_SmoothStepToF(&gWarpZoneBgAlpha, 128.0f, 1.0f, 1.0f, 0.0f);
                }
            }
            if ((gCurrentLevel == LEVEL_SECTOR_X) && (gLevelPhase == 0) && (gRingPassCount == 4)) {
                gRingPassCount++;
                gPlayer[0].state_1C8 = PLAYERSTATE_1C8_ENTER_WARP_ZONE;
                gPlayer[0].csState = 0;
                gSceneSetup = 1;
                AUDIO_PLAY_SFX(NA_SE_WARP_HOLE, gDefaultSfxSource, 0);
                gMissionStatus = MISSION_WARP;
                gLeveLClearStatus[gCurrentLevel] = 1;
            }
            break;
        case LEVEL_CORNERIA:
            func_hud_8008C104(D_CO_603EB38, D_CO_6028A60);
            if ((gGameFrameCount % 2) != 0) {
                Texture_Scroll(D_CO_600CBD8, 64, 32, 3);
            }
            break;
        case LEVEL_AQUAS:
            func_hud_8008C104(D_AQ_603158C, D_AQ_602ACC0);
            break;
        case LEVEL_SOLAR:
            Play_UpdateDynaFloor();

            for (gPathTexScroll; gPathTexScroll >= 10.0f; gPathTexScroll -= 10.0f) {
                Texture_Scroll(D_SO_6005710, 32, 32, 1);
            }
            if (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_NEXT) {
                Texture_Scroll(D_SO_6005710, 32, 32, 1);
            }
            Texture_Mottle(D_SO_601E1E8, D_SO_6020F60, 3);

            if (gPlayer[0].pos.y > 600.0f) {
                cycleMask = 8 - 1;
                heightParam = 5;
            } else if (gPlayer[0].pos.y > 500.0f) {
                cycleMask = 8 - 1;
                heightParam = 4;
            } else if (gPlayer[0].pos.y > 400.0f) {
                cycleMask = 4 - 1;
                heightParam = 3;
            } else if (gPlayer[0].pos.y > 300.0f) {
                cycleMask = 4 - 1;
                heightParam = 2;
            } else if (gPlayer[0].pos.y > 200.0f) {
                cycleMask = 2 - 1;
                heightParam = 1;
            } else if (gPlayer[0].pos.y > 100.0f) {
                cycleMask = 1 - 1;
                heightParam = 0;
            } else {
                cycleMask = 1 - 1;
#ifdef AVOID_UB
                heightParam = 0;
#endif
            }

            if ((gPlayer[0].state_1C8 == PLAYERSTATE_1C8_ACTIVE) && ((gGameFrameCount & cycleMask) == 0)) {
                gPlayer[0].shields--;
                if (gPlayer[0].shields <= 0) {
                    gPlayer[0].shields = 0;
                }
                if (gPlayer[0].heal == 0) {
                    if (gPlayer[0].shields == 50) {
                        AUDIO_PLAY_SFX(NA_SE_SHIELD_WARNING1, gDefaultSfxSource, 4);
                    } else if (gPlayer[0].shields == 100) {
                        AUDIO_PLAY_SFX(NA_SE_SHIELD_WARNING0, gDefaultSfxSource, 4);
                    }
                }
            }
            shields = MIN(gPlayer[0].shields, 255);
            Audio_SetHeatAlarmParams(shields, heightParam);
            if (((gGameFrameCount % 8) == 0) && (gPlayer[0].state_1C8 != PLAYERSTATE_1C8_LEVEL_COMPLETE)) {
                Solar_8019E8B8(RAND_FLOAT_CENTERED(6000.0f), -80.0f,
                               gPlayer[0].trueZpos + (RAND_FLOAT(2000.0f) + -6000.0f),
                               RAND_FLOAT(10.0f) + 20.0f); // check
            }
            func_hud_8008C104(D_SO_60229A4, D_SO_6010198);
            if (gPlayer[0].shields == 0) {
                gSoShieldsEmpty = 1;
            }
            break;
        case LEVEL_ZONESS:
            Play_UpdateDynaFloor();
            for (gPathTexScroll; gPathTexScroll >= 20.0f; gPathTexScroll -= 20.0f) {
                Texture_Scroll(D_ZO_602C2CC, 32, 32, 1);
            }
            if (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_NEXT) {
                Texture_Scroll(D_ZO_602C2CC, 32, 32, 1);
            }
            func_hud_8008C104(D_ZO_602C2CC, D_ZO_600D990);
            if (Play_CheckDynaFloorCollision(&sp3C, &sp40, gPlayer[0].cam.eye.x, gPlayer[0].cam.eye.y,
                                             gPlayer[0].cam.eye.z - gPathProgress)) {
                gLight1R = 0;
                gLight1G = 7;
                gLight1B = 10;
                gAmbientR = gAmbientG = gAmbientB = 0;
                gFogNear = 990;
                gFogFar = 994;
                gBgColor = 0x43; // 0, 8, 8
            } else {
                gBgColor = 0x4107; // 64, 32, 24
                gLight1R = 90;
                gLight1G = 100;
                gLight1B = 50;
                gAmbientR = 10;
                gAmbientG = 20;
                gAmbientB = 0;
                gFogNear = 996;
                gFogFar = 1000;
            }
            break;
    }
}

void Play_Update(void) {
    s32 i;

    Play_UpdateFillScreen();
    for (i = TEAM_ID_FALCO; i <= TEAM_ID_PEPPY; i++) {
        if (gTeamDamage[i] > 0) {
            gTeamDamage[i] -= 2;
            gTeamShields[i] -= 2;
            if (gTeamShields[i] <= 0) {
                gTeamShields[i] = -1;
            }
        }
    }
    for (i = 0; i < gCamCount; i++) {
        gPlayer[i].num = gPlayerNum = i;
        Player_Update(&gPlayer[i]);
    }
    Object_Update();
    PlayerShot_UpdateAll();
    BonusText_Update();
    for (i = 0; i < gCamCount; i++) {
        gPlayer[i].num = gPlayerNum = i;
        Camera_Update(&gPlayer[i]);
    }
    gCameraShakeY = 0.0f;
    if (gCameraShake != 0) {
        f32 var_fv1;

        gCameraShake--;
        var_fv1 = gCameraShake;
        if (var_fv1 > 20.0f) {
            var_fv1 = 20.0f;
        }
        gCameraShakeY = var_fv1 * SIN_DEG(gGameFrameCount * 70.0f);
    }
    Play_UpdateLevel();
}

u8 sVsItemSpawnIndex = -1;

void Play_SpawnVsItem(ObjectId objId, Item* item) {
    u8 spawnIndex = (u8) RAND_FLOAT(5.0f);

    if (sVsItemSpawnIndex == spawnIndex) {
        gVsItemSpawnTimer--;
    } else {
        sVsItemSpawnIndex = spawnIndex;
        if (item->obj.status == OBJ_FREE) {
            Item_Initialize(item);
            item->obj.status = OBJ_INIT;
            item->obj.pos.x = gScenery360[spawnIndex].obj.pos.x;
            item->obj.pos.y = gScenery360[spawnIndex].obj.pos.y;
            item->obj.pos.z = gScenery360[spawnIndex].obj.pos.z;
            item->obj.id = objId;
            Object_SetInfo(&item->info, item->obj.id);
        }
    }
}

void Play_SetupZPos360(f32* zPos) {
    *zPos += gPathProgress + 15000.0f;
}

void Play_Main(void) {
    s32 pad1;
    s32 pad2;
    s32 pad3;
    s32 i;
    f32 sp34;

    switch (D_ctx_80177C70) {
        case 0:
            sp34 = 45.0f;
            break;
        case 1:
            sp34 = 45.0f;
            break;
        case 2:
            sp34 = 55.0f;
            break;
    }
    Math_SmoothStepToF(&gFovY, sp34, 0.1f, 5.0f, 0.0f);
    if (gChangeTo360) {
        gChangeTo360 = false;
        gLevelMode = LEVELMODE_ALL_RANGE;
        if (gCurrentLevel != LEVEL_VENOM_ANDROSS) {
            MEM_ARRAY_ALLOCATE(gScenery360, 200);
        }
        for (i = 0; i < 200; i++) {
            gScenery360[i].obj.status = OBJ_FREE;
        }
        Play_ClearObjectData();
        if (gCurrentLevel == LEVEL_CORNERIA) {
            Play_Setup360_CO();
        } else if (gCurrentLevel == LEVEL_SECTOR_Y) {
            Play_Setup360_SY();
        } else if (gCurrentLevel == LEVEL_VENOM_ANDROSS) {
            Play_Setup360_AND();
        } else if (gCurrentLevel == LEVEL_TRAINING) {
            Training_Setup360();
        }
        Play_SetupZPos360(&gPlayer[0].pos.z);
        Play_SetupZPos360(&gPlayer[0].trueZpos);
        gPlayer[0].cam.eye.z += 15000.0f;
        gPlayer[0].cam.at.z += 15000.0f;
        gPlayer[0].zPath = gPlayer[0].zPathVel = gPathVelZ = gPathProgress = 0.0f;
    }
    if (gPlayState != PLAY_PAUSE) {
        (void) "play_time = %d\n";
        gGameFrameCount++;
    }
    switch (gPlayState) {
        case PLAY_STANDBY:
            if (gNextGameStateTimer == 0) {
                gPlayState = PLAY_INIT;
            }
            break;
        case PLAY_INIT:
            Play_Init();
            sMusicVolume = gVolumeSettings[AUDIO_TYPE_MUSIC];
            sVoiceVolume = gVolumeSettings[AUDIO_TYPE_VOICE];
            sSfxVolume = gVolumeSettings[AUDIO_TYPE_SFX];
            gPlayState = PLAY_UPDATE;
            break;
        case PLAY_UPDATE:
            if ((gLevelStartStatusScreenTimer != 0) || (gLevelClearScreenTimer != 0)) {
                gPauseEnabled = false;
            } else {
                gPauseEnabled = true;
            }
            gDrawMode = DRAW_PLAY;
            Play_Update();
            if ((gControllerPress[gMainController].button & START_BUTTON) &&
                (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_LEVEL_INTRO) &&
                gSaveFile.save.data.planet[sSaveSlotFromLevel[gCurrentLevel]].normalClear) {
                Audio_ClearVoice();
                Audio_SetEnvSfxReverb(0);
                Play_ClearObjectData();
                for (i = 0; i < gCamCount; i++) {
                    Audio_KillSfxBySource(gPlayer[i].sfxSource);
                    Audio_StopPlayerNoise(i);
                }
                gPlayState = PLAY_INIT;
                gDrawMode = gVersusMode = 0;
                gCamCount = 1;
                gBgColor = 0;
                gCsFrameCount = gLevelClearScreenTimer = gLevelStartStatusScreenTimer = gRadioState = 0;
                D_ctx_8017782C = 0;
            }
            if (gVersusMode) {
                Versus_Main();
            }
            if ((gControllerPress[gMainController].button & START_BUTTON) && gPauseEnabled) {
                Audio_PlayPauseSfx(1);
                gPlayState = PLAY_PAUSE;
                D_ctx_80177868 = 4;
                D_ctx_80178484 = 100000;
            }
            break;
        case PLAY_PAUSE:
            if (!gVersusMode) {
                if ((gControllerPress[gMainController].button & R_TRIG) && (gPlayer[0].form != FORM_BLUE_MARINE) &&
                    (gPlayer[0].state_1C8 != PLAYERSTATE_1C8_STANDBY)) {
                    if (gShowCrosshairs[0] = 1 - gShowCrosshairs[0]) {
                        AUDIO_PLAY_SFX(NA_SE_MAP_WINDOW_OPEN, gDefaultSfxSource, 4);
                    } else {
                        AUDIO_PLAY_SFX(NA_SE_MAP_WINDOW_CLOSE, gDefaultSfxSource, 4);
                    }
                }
            } else {
                for (i = 0; i < 4; i++) {
                    if ((gControllerPress[i].button & R_TRIG) && (gPlayer[i].form != FORM_ON_FOOT)) {
                        if (gShowCrosshairs[i] = 1 - gShowCrosshairs[i]) {
                            Object_PlayerSfx(gPlayer[i].sfxSource, NA_SE_MAP_WINDOW_OPEN, i);
                        } else {
                            Object_PlayerSfx(gPlayer[i].sfxSource, NA_SE_MAP_WINDOW_CLOSE, i);
                        }
                    }
                }
            }
            if ((D_ctx_80177868 == 4) && (gControllerPress[gMainController].button & START_BUTTON) &&
                (gPauseEnabled != 0)) {
                Audio_PlayPauseSfx(0);
                gPlayState = PLAY_UPDATE;
                gDrawMode = DRAW_PLAY;
            }
            gPauseEnabled = 1;
            break;
    }
}
