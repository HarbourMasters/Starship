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

UNK_TYPE D_800D2F50 = 0;
s32 D_800D2F54 = 0;
f32 D_800D2F58 = 0.0f;
f32 D_800D2F5C = 0.0f;
f32 D_800D2F60 = 0.0f;
f32 D_800D2F64 = 0.0f;
u8 D_play_800D2F68 = false;
u8 D_800D2F6C[20] = {
    PLANET_CORNERIA, PLANET_METEO,      PLANET_SECTOR_X, PLANET_AREA_6,   PLANET_AREA_6,
    PLANET_SECTOR_Y, SAVE_SLOT_VENOM_1, SAVE_SLOT_SOLAR, PLANET_ZONESS,   SAVE_SLOT_VENOM_1,
    PLANET_CORNERIA, PLANET_MACBETH,    PLANET_TITANIA,  PLANET_AQUAS,    PLANET_FORTUNA,
    PLANET_METEO,    PLANET_KATINA,     PLANET_BOLSE,    PLANET_SECTOR_Z, SAVE_SLOT_VENOM_2,
};

u8 gSavedZoSearchlightStatus;
f32 D_play_80161A54;
s32 D_play_80161A58;
s32 D_play_80161A5C;
u16 gScreenFlashTimer;
u16 gDropHitCountItem;
s32 D_play_80161A64;
EnvSettings* sEnvSettings;

#define MEM_ARRAY_ALLOCATE(arr, count) ((arr) = Memory_Allocate((count) * sizeof(*(arr))))

bool Play_CheckMedalStatus(u16 hitCount) {
    if ((gTeamShields[TEAM_ID_SLIPPY] > 0) && (gTeamShields[TEAM_ID_PEPPY] > 0) && (gTeamShields[TEAM_ID_FALCO] > 0) &&
        (gHitCount >= hitCount)) {
        return true;
    } else {
        return false;
    }
}

void func_play_800A3FB0(void) {
    D_800D2F64 = 0.0f;
}

s32 Play_GetMaxShields(void) {
    if (gGoldRingCount[0] >= 3) {
        return 383;
    }
    return 255;
}

void func_play_800A3FEC(void) {
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

    D_ctx_801782FC++;
    switch (gCurrentLevel) {
        case LEVEL_SOLAR:
            if ((gGameFrameCount % 2) != 0) {
                spB4 = LOAD_ASSET(D_SO_6001C50);
            } else {
                spB4 = LOAD_ASSET(D_SO_6004500);
            }
            spB0 = LOAD_ASSET(D_SO_6022760);
            spA8 = 15;
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
            spA8 = 7;
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
        if ((D_ctx_801782FC & spA8) == (i & spA8)) {
            *var_s5 = RAND_FLOAT(sp90);
            *var_s4 = 0.0f;
        }
        *var_s0 += *var_s1;
        *var_s1 -= 0.5f;
        if (*var_s0 < 0.0f) {
            *var_s1 = *var_s0 = 0.0f;
        }
        spB4[*spB0].n.ob[1] = (s16) *var_s3 + (s16) *var_s0;
        Matrix_RotateZ(gCalcMatrix, *var_s3 * sp88 * M_DTOR, 0);
        spC4.x = 120.0f;
        spC4.y = 0.0f;
        spC4.z = 0.0f;
        Matrix_MultVec3fNoTranslate(gCalcMatrix, &spC4, &spB8);
        spB4[*spB0].n.n[0] = spB8.x;
        spB4[*spB0].n.n[1] = spB8.y;
        spB4[*spB0].n.n[2] = spB8.z;
    }
}

void func_play_800A4460(Player* player) {
    if ((gCurrentLevel == LEVEL_VENOM_ANDROSS) && (gBosses[0].obj.status == OBJ_ACTIVE) && (gBosses[0].state == 17)) {
        player->unk_060 = SIN_DEG(player->unk_0F4 * 0.7f) * 0.5f;
        player->unk_088 += 13.0f;
        player->unk_0F4 += 20.0f;
        player->unk_080 = -SIN_DEG(player->unk_088) * 5.0f;
        player->unk_0F0 = SIN_DEG(player->unk_0F4) * 10.0f;
    } else {
        player->unk_060 = SIN_DEG(player->unk_0F4 * 0.7f) * 0.5f;
        player->unk_088 += 10.0f;
        player->unk_0F4 += 8.0f;
        if ((gLevelType == LEVELTYPE_PLANET) || ((player->cockpitView == 1) && (gLevelMode == LEVELMODE_ON_RAILS))) {
            player->unk_080 = -SIN_DEG(player->unk_088) * 0.5f;
            if ((player->wings.rightState <= WINGSTATE_BROKEN) || (player->wings.leftState <= WINGSTATE_BROKEN)) {
                player->unk_0F0 = SIN_DEG(player->unk_0F4) * 5.0f;
            } else {
                player->unk_0F0 = SIN_DEG(player->unk_0F4) * 1.5f;
            }
        }
    }
}

void func_play_800A46A0(Player* player) {
    s32 var_v1;
    f32 sp40;

    if ((player->cockpitView == 0) || (gLevelMode == LEVELMODE_ALL_RANGE)) {
        if (player->wings.rightState <= WINGSTATE_BROKEN) {
            if (((gGameFrameCount % 2U) == 0) && (D_ctx_80177D70[player->num] != 0)) {
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
            if (((gGameFrameCount % 2U) == 0) && (D_ctx_80177D88[player->num] != 0)) {
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
        if ((player->cockpitView == 0) || (gLevelMode == LEVELMODE_ALL_RANGE)) {
            sp40 = 0.0f;
            if (player->form == FORM_LANDMASTER) {
                sp40 = 30.0f;
            }
            if ((gGameFrameCount & var_v1) == 0) {
                func_effect_8007D10C(player->pos.x + RAND_FLOAT_CENTERED(10.0f),
                                     player->pos.y + sp40 + RAND_FLOAT(10.0f),
                                     player->unk_138 + RAND_FLOAT_CENTERED(10.0f), 2.2f);
            }
            if (((gGameFrameCount & (var_v1 >> 2)) == 0) && (Rand_ZeroOne() < 0.5f)) {
                func_effect_8007C484(player->pos.x + RAND_FLOAT_CENTERED(30.0f),
                                     player->pos.y + sp40 + RAND_FLOAT(10.0f),
                                     player->unk_138 + RAND_FLOAT_CENTERED(30.0f), player->vel.x, player->vel.y,
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

void func_play_800A4C40(Player* player) {
    Vec3f sp54 = { -65.0f, -22.0f, -65.0f };
    Vec3f sp48 = { 65.0f, -22.0f, -65.0f };
    Vec3f sp3C;
    Vec3f sp30;

    if (gGroundType == GROUNDTYPE_WATER) {
        Matrix_Translate(gCalcMatrix, player->pos.x, player->pos.y, player->unk_138, 0);
        Matrix_RotateY(gCalcMatrix, (player->unk_114 + player->unk_0E8 + 180.0f) * M_DTOR, 1);
        Matrix_RotateX(gCalcMatrix, -((player->unk_0E4 + player->unk_4D8) * M_DTOR), 1);
        Matrix_RotateZ(gCalcMatrix, -(player->unk_0F8 * M_DTOR), 1);
        Matrix_MultVec3f(gCalcMatrix, &sp54, &sp3C);
        Matrix_MultVec3f(gCalcMatrix, &sp48, &sp30);
        if (player->pos.y < (gGroundLevel + 100.0f)) {
            if ((sp3C.y < gGroundLevel + 80.0f) && ((gGameFrameCount % 2) == 0)) {
                if (D_play_80161A64) {}
                func_effect_8007ACE0(sp3C.x, gGroundLevel, sp3C.z, 0.1f, 2.0f,
                                     player->unk_0E8 + player->unk_114 + 20.0f);
            }
            if ((sp30.y < gGroundLevel + 80.0f) && ((gGameFrameCount % 2) == 0)) {
                func_effect_8007ACE0(sp30.x, gGroundLevel, sp30.z, 0.1f, 2.0f,
                                     player->unk_0E8 + player->unk_114 - 20.0f);
            }
        }
        if ((sp30.y < gGroundLevel + 80.0f) || (sp3C.y < gGroundLevel + 80.0f)) {
            if (D_play_80161A64 == 0) {
                D_play_80161A64 = 1;
                AUDIO_PLAY_SFX(0x1100000B, player->sfxSource, 0);
            }
        } else {
            D_play_80161A64 = 0;
            Audio_KillSfxBySourceAndId(player->sfxSource, 0x1100000B);
        }
    }
}

void Object_58_Initialize(Object_58* obj58) {
    s32 i;
    u8* ptr = (u8*) obj58;

    for (i = 0; i < sizeof(Object_58); i++, ptr++) {
        *ptr = 0;
    }
}

void func_play_800A4F7C(void) {
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
            if (D_ctx_801778AC == 2) {
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
        if (gLevelObjects[j].id == OBJ_80_147) {
            Object_58_Initialize(&gObjects58[i]);
            gObjects58[i].obj.status = OBJ_ACTIVE;
            gObjects58[i].obj.id = gLevelObjects[j].id;
            gObjects58[i].obj.pos.x = gLevelObjects[j].xPos;
            gObjects58[i].obj.pos.z = gLevelObjects[j].zPos1;
            gObjects58[i].obj.pos.y = gLevelObjects[j].yPos;
            Object_SetInfo(&gObjects58[i].info, gObjects58[i].obj.id);
            i++;
        }
    }
    for (i = 5, j = 0; i < 199; j++) {
        if (gLevelObjects[j].id <= OBJ_INVALID) {
            break;
        }
        if (gLevelObjects[j].id != OBJ_80_147) {
            Object_58_Initialize(&gObjects58[i]);
            gObjects58[i].obj.status = OBJ_ACTIVE;
            gObjects58[i].obj.id = gLevelObjects[j].id;
            gObjects58[i].obj.pos.x = gLevelObjects[j].xPos;
            gObjects58[i].obj.pos.z = gLevelObjects[j].zPos1;
            gObjects58[i].obj.pos.y = gLevelObjects[j].yPos;
            gObjects58[i].obj.rot.y = gLevelObjects[j].rot.y;
            Object_SetInfo(&gObjects58[i].info, gObjects58[i].obj.id);
            i++;
        }
    }
}

void func_play_800A5330(void) {
}

void func_play_800A5338(void) {
    Sprite* sprite;
    Object_58* obj58;
    s32 i;
    s32 j;

    gLevelObjects = LOAD_ASSET(D_CO_603B074);

    for (j = 0, obj58 = gObjects58; j < 200; j++) {
        if (gLevelObjects[j].id <= OBJ_INVALID) {
            break;
        }
        if (gLevelObjects[j].id < OBJ_SPRITE_CO_POLE) {
            Object_58_Initialize(obj58);
            obj58->obj.status = OBJ_ACTIVE;
            obj58->obj.id = gLevelObjects[j].id;
            obj58->obj.pos.x = gLevelObjects[j].xPos;
            obj58->obj.pos.z = gLevelObjects[j].zPos1;
            obj58->obj.pos.y = gLevelObjects[j].yPos;
            obj58->obj.rot.y = gLevelObjects[j].rot.y;
            Object_SetInfo(&obj58->info, obj58->obj.id);
            if (obj58->obj.id == OBJ_80_1) {
                obj58->info.dList = D_CO_6020760;
            }
            obj58++;
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

void func_play_800A55B0(void) {
    Object_58* obj58;
    s32 i;
    s32 j;

    gLevelObjects = LOAD_ASSET(D_SY_6030B14);

    for (j = 0, obj58 = gObjects58; j < 200; j++) {
        if (gLevelObjects[j].id <= OBJ_INVALID) {
            break;
        }
        if (gLevelObjects[j].id < OBJ_SPRITE_CO_POLE) {
            Object_58_Initialize(obj58);
            obj58->obj.status = OBJ_ACTIVE;
            obj58->obj.id = gLevelObjects[j].id;
            obj58->obj.pos.x = gLevelObjects[j].xPos;
            obj58->obj.pos.z = gLevelObjects[j].zPos1;
            obj58->obj.pos.y = gLevelObjects[j].yPos;
            obj58->obj.rot.y = gLevelObjects[j].rot.y;
            Object_SetInfo(&obj58->info, obj58->obj.id);
            obj58++;
        }
    }
    i = 0; // fake?
    Boss_Initialize(&gBosses[i]);
    gBosses[i].obj.status = OBJ_INIT;
    gBosses[i].obj.pos.x = 0.0f;
    gBosses[i].obj.pos.y = 0.0f;
    gBosses[i].obj.pos.z = 0.0f;
    gBosses[i].obj.id = OBJ_BOSS_314;
    Object_SetInfo(&gBosses[i].info, gBosses[i].obj.id);
    i = 1;
    Boss_Initialize(&gBosses[i]);
    gBosses[i].obj.status = OBJ_INIT;
    gBosses[i].obj.pos.x = 0.0f;
    gBosses[i].obj.pos.y = 0.0f;
    gBosses[i].obj.pos.z = 0.0f;
    gBosses[i].obj.id = OBJ_BOSS_314;
    Object_SetInfo(&gBosses[i].info, gBosses[i].obj.id);
    i = 2;
    Boss_Initialize(&gBosses[i]);
    gBosses[i].obj.status = OBJ_INIT;
    gBosses[i].obj.pos.x = 0.0f;
    gBosses[i].obj.pos.y = 0.0f;
    gBosses[i].obj.pos.z = 0.0f;
    gBosses[i].obj.id = OBJ_BOSS_314;
    Object_SetInfo(&gBosses[i].info, gBosses[i].obj.id);
}

void func_play_800A57E0(void) {
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

    D_ctx_80178410 = 0;
    gLevelStage = 0;
    gMissedZoSearchlight = false;
    gSavedZoSearchlightStatus = false;
    gOverlayStage = 0;
    gAllRangeCheckpoint = D_ctx_80177CA0 = 0;
    D_ctx_80177CB0 = 0.0f;
    gSavedHitCount = gCsFrameCount = gLevelStatusScreenTimer = gLevelClearScreenTimer = gRadioState = 0;
    D_ctx_8017782C = 1;
    if (((gCurrentLevel == LEVEL_VENOM_2) && (gNextLevelStage == 2)) || (gCurrentLevel == LEVEL_VENOM_ANDROSS)) {
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

EnvSettings* D_800D2F98[21] = {
    &D_CO_6037160, &D_ME_6026C80, &D_SX_602A120,      &D_A6_6023F20, &D_A6_6028760, &D_SY_602E4B0,  &D_VE1_6007E30,
    &D_SO_601F1F0, &D_ZO_60266D0, &D_ANDROSS_C035110, &D_TR_6006A60, &D_MA_6030E30, &D_TI_6005000,  &D_AQ_602E540,
    &D_FO_600EA90, NULL,          &D_KA_6011000,      &D_BO_600FF30, &D_SZ_6006E70, &D_VE2_6014D50, &D_versus_302DD70,
};

void func_play_800A594C(void) {
    if (gVersusMode) {
        switch (gVersusStage) {
            case 0:
                sEnvSettings = LOAD_ASSET(&D_versus_302DD70);
                break;
            case 1:
                sEnvSettings = LOAD_ASSET(&D_versus_302DDB4);
                break;
            case 2:
                sEnvSettings = LOAD_ASSET(&D_versus_302DDF8);
                break;
        }
    } else {
        sEnvSettings = LOAD_ASSET(D_800D2F98[gCurrentLevel]);
    }
    if (D_ctx_8017782C == 0) {
        if (gCurrentLevel == LEVEL_SOLAR) {
            func_8001D1C8(0xFF, 1);
            AUDIO_PLAY_SFX(0x4100C023, gDefaultSfxSource, 4);
            Audio_KillSfxBySourceAndId(gPlayer[0].sfxSource, 0x3140807E);
        }
    } else if (gCurrentLevel == LEVEL_AQUAS) {
        sEnvSettings = LOAD_ASSET(&D_AQ_602E584);
    }
    gBgmSeqId = sEnvSettings->seqId;
    gLevelType = sEnvSettings->type;
    D_ctx_801784AC = sEnvSettings->unk_04;
    gBgColor = sEnvSettings->bgColor;
    gFogRed = sEnvSettings->fogR;
    gFogGreen = sEnvSettings->fogG;
    gFogBlue = sEnvSettings->fogB;
    gFogNear = sEnvSettings->fogN;
    gFogFar = sEnvSettings->fogF;
    gLight1R = gLight2R = D_ctx_80161A70 = sEnvSettings->lightR;
    gLight1G = gLight2G = D_ctx_80161A74 = sEnvSettings->lightG;
    gLight1B = gLight2B = D_ctx_80161A78 = sEnvSettings->lightB;
    gAmbientR = sEnvSettings->ambR;
    gAmbientG = sEnvSettings->ambG;
    gAmbientB = sEnvSettings->ambB;
    D_ctx_801784D0 = D_ctx_801784F8 = D_ctx_80178520 = D_ctx_801784B8 = D_ctx_801784C4 = sEnvSettings->unk_20.x;
    D_ctx_801784D4 = D_ctx_801784FC = D_ctx_80178524 = D_ctx_801784BC = D_ctx_801784C8 = sEnvSettings->unk_20.y;
    D_ctx_801784D8 = D_ctx_80178500 = D_ctx_80178528 = D_ctx_801784C0 = D_ctx_801784CC = sEnvSettings->unk_20.z;
    D_game_80161A44 = 12800.0f;
    D_ctx_80178540 = 40;
    D_ctx_80178544 = 40;
    D_game_80161A3C = 45.0f;
}

void func_play_800A5D6C(void) {
    u32 i;

    MEM_ARRAY_ALLOCATE(D_ctx_80178288, 1000);
    MEM_ARRAY_ALLOCATE(D_ctx_80178290, 1000);
    MEM_ARRAY_ALLOCATE(D_ctx_80178298, 1000);
    Rand_SetSeed(1, 29000, 9876);
    for (i = 0; i < 1000; i++) {
        D_ctx_80178288[i] = RAND_FLOAT_SEEDED(480.0f) - 80.0f;
        D_ctx_80178290[i] = RAND_FLOAT_SEEDED(360.0f) - 60.0f;
        D_ctx_80178298[i] = FILL_COLOR(D_bg_800C9C3C[i % ARRAY_COUNT(D_bg_800C9C3C)]);
    }
}

void func_play_800A5EBC(void) {
    func_play_800A5D6C();
    gGroundLevel = -25000.0f;
    D_ctx_80178410 = 600;
    if (gCurrentLevel == LEVEL_AREA_6) {
        D_ctx_80178410 = 300;
    }
    if (gCurrentLevel == LEVEL_UNK_15) {
        D_ctx_80178410 = 400;
    }
    if (gGameState != GSTATE_PLAY) {
        D_ctx_80178410 = 800;
    }
    if (gCurrentLevel == LEVEL_FORTUNA) {
        D_ctx_80178410 = 500;
    }
    if (gVersusMode) {
        D_ctx_80178410 = 0;
    }
    if (gCurrentLevel == LEVEL_BOLSE) {
        D_ctx_80178410 = 300;
        gGroundLevel = -0.0f;
    }
    if (gCurrentLevel == LEVEL_TRAINING) {
        D_ctx_80178410 = 800;
        gGroundLevel = -0.0f;
    }
}

void func_play_800A5FA0(f32* sfxSrc, u32 sfxId, s32 mode) {
    if (!gVersusMode) {
        AUDIO_PLAY_SFX(sfxId, sfxSrc, 0);
    } else {
        AUDIO_PLAY_SFX(sfxId, sfxSrc, mode);
    }
}

void func_play_800A6028(f32* sfxSrc, u32 sfxId) {
    AUDIO_PLAY_SFX(sfxId, sfxSrc, 0);
}

void func_play_800A6070(f32* sfxSrc, u32 sfxId) {
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

void func_play_800A6148(void) {
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
    for (i = 0; i < ARRAY_COUNT(gObjects80); i++) {
        Object_Kill(&gObjects80[i].obj, gObjects80[i].sfxSource);
        Object_80_Initialize(&gObjects80[i]);
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
    D_ctx_801782B8 = D_ctx_801782BC = D_ctx_801782C0 = D_ctx_801782D0 = gBossActive = D_ctx_8017828C = D_ctx_8017812C =
        D_ctx_80177E70 = D_ctx_80177E78 = gRingPassCount = 0;
    D_ctx_80177F10.x = D_ctx_80177F10.y = D_ctx_80177F10.z = D_ctx_80177E88.x = D_ctx_80177E88.y = D_ctx_80177E88.z =
        0.0f;
    for (i = 0; i < ARRAY_COUNT(gTeamArrowsViewPos); i++) {
        gTeamArrowsViewPos[i].x = gTeamArrowsViewPos[i].y = gTeamArrowsViewPos[i].z = 100.0f;
    }
    for (i = 0; i < ARRAY_COUNT(D_ctx_80176878); i++) {
        D_ctx_80176550[i] = 0;
        for (j = 0; j < ARRAY_COUNT(*D_ctx_80176878); j++) {
            D_ctx_80176878[i][j] = -5000.0f;
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
    Math_SmoothStepToF(&D_ctx_8017836C, 0.0f, 1.0f, 0.04f, 0.001f);
    if (gScreenFlashTimer != 0) {
        gScreenFlashTimer--;
        if (gScreenFlashTimer & 2) {
            gFillScreenRed = 255;
            gFillScreenGreen = 255;
            gFillScreenBlue = 255;
            gFillScreenAlpha = 254;
        } else {
            gFillScreenAlpha = 0;
        }
    }
}

void func_play_800A668C(f32 xPos, f32 yPos, f32 zPos) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gPlayerShots); i++) {
        if (gPlayerShots[i].obj.status == 0) {
            PlayerShot_Initialize(&gPlayerShots[i]);
            gPlayerShots[i].obj.status = 2;
            gPlayerShots[i].unk_60 = 0;
            gPlayerShots[i].obj.pos.x = xPos;
            gPlayerShots[i].obj.pos.y = yPos;
            gPlayerShots[i].obj.pos.z = zPos;
            break;
        }
    }
}

void func_play_800A670C(Actor* actor, s32 state, f32 xPos, f32 yPos, f32 zPos) {
    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_189;
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

void func_play_800A69F8(s32 state, f32 xPos, f32 yPos, f32 zPos) {
    s32 i;

    if (!gVersusMode) {
        for (i = ARRAY_COUNT(gActors) - 1; i >= 10; i--) {
            if (gActors[i].obj.status == OBJ_FREE) {
                func_play_800A670C(&gActors[i], state, xPos, yPos, zPos);
                break;
            }
        }
    }
}

// has to be int. s32 and u32 don't match
bool func_play_800A6A74(void) {
    return gGoldRingCount[0] && gGoldRingCount[1] && gGoldRingCount[2] && gGoldRingCount[3];
}

void Player_DamageWings(Player* player, s32 side, s32 damage) {
    if ((player->form == FORM_ARWING) && (D_ctx_80177AB8[player->num] < 1.0f)) {
        if (side == 1) {
            D_ctx_80177D40[player->num] = 30;
            if (player->wings.rightState == WINGSTATE_INTACT) {
                gRightWingHealth[player->num] -= damage;
                if (gRightWingHealth[player->num] <= 0) {
                    func_play_800A69F8(1, player->hit1.x, player->hit1.y, player->hit1.z);
                    player->wings.rightState = WINGSTATE_BROKEN;
                    func_effect_8007D0E0(player->hit1.x, player->hit1.y, player->hit1.z, 2.0f);
                    D_ctx_80177D70[player->num] = 50;
                    func_play_800A5FA0(player->sfxSource, 0x0900A02C, player->num);
                    if (gAllRangeWingRepairTimer == 0) {
                        gAllRangeWingRepairTimer = 1000;
                    }
                }
            }
        } else if (side == 2) {
            D_ctx_80177D58[player->num] = 30;
            if (player->wings.leftState == WINGSTATE_INTACT) {
                gLeftWingHealth[player->num] -= damage;
                if (gLeftWingHealth[player->num] <= 0) {
                    func_play_800A69F8(0, player->hit2.x, player->hit2.y, player->hit2.z);
                    player->wings.leftState = WINGSTATE_BROKEN;
                    func_effect_8007D0E0(player->hit2.x, player->hit2.y, player->hit2.z, 2.0f);
                    D_ctx_80177D88[player->num] = 50;
                    func_play_800A5FA0(player->sfxSource, 0x0900A02C, player->num);
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
        player->timer_220 = 4;
    }
    player->unk_284 = 0;
    player->unk_1F4 = 20;
    if (player->unk_1A4 > 40) {
        sp34 = (player->unk_110 * 0.3f) + 20.0f;
        player->timer_498 = 5;
    } else if ((gCurrentLevel == LEVEL_VENOM_ANDROSS) && (gBossActive == 0)) {
        player->timer_498 = 3;
    } else if ((gCurrentLevel == LEVEL_VENOM_1) || (gCurrentLevel == LEVEL_AQUAS)) {
        player->timer_498 = 5;
    } else {
        player->timer_498 = 20;
    }
    if (D_ctx_80177AD0[player->num] != 0) {
        func_play_800A5FA0(player->sfxSource, 0x0903900E, player->num);
        D_ctx_80177AE8[player->num] = 5;
        D_ctx_80177AB8[player->num] = 2.0f;
        player->damage = 0;
    } else {
        if (player->shields != 0) {
            if (player->shields < 50) {
                AUDIO_PLAY_SFX(0x49008011, gDefaultSfxSource, 4);
            } else if (player->shields < 100) {
                AUDIO_PLAY_SFX(0x49008010, gDefaultSfxSource, 4);
            }
        }
        if (damage < 25) {
            func_play_800A5FA0(player->sfxSource, 0x0903900E, player->num);
        } else {
            func_play_800A5FA0(player->sfxSource, 0x0903A00F, player->num);
        }
    }
    Matrix_RotateY(gCalcMatrix, player->unk_114 * M_DTOR, 0);
    Matrix_RotateZ(gCalcMatrix, player->unk_0F8 * M_DTOR, 1);
    sp44.z = 0.0f;
    switch (player->unk_21C) {
        case 0:
            player->timer_224 = 20;
            player->unk_0D8.x = 0.f;
            player->unk_0D8.y = 0.f;
            player->unk_0D8.z = 0.f;
            break;
        case 1:
            sp44.x = -sp34;
            sp44.y = 0.0f;

            Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp44, &sp38);
            player->unk_0D8.x = sp38.x;
            player->unk_0D8.y = sp38.y;
            player->unk_0D8.z = sp38.z;
            func_play_800A668C(player->hit1.x - player->vel.x, player->hit1.y, player->hit1.z - player->vel.z);
            Player_DamageWings(player, 1, 20);
            break;
        case 2:
            sp44.x = sp34;
            sp44.y = 0.0f;

            Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp44, &sp38);
            player->unk_0D8.x = sp38.x;
            player->unk_0D8.y = sp38.y;
            player->unk_0D8.z = sp38.z;
            func_play_800A668C(player->hit2.x - player->vel.x, player->hit2.y, player->hit2.z - player->vel.z);
            Player_DamageWings(player, 2, 20);
            break;
        case 3:
            player->timer_224 = 20;
            func_play_800A668C(player->hit4.x - player->vel.x, player->hit4.y, player->hit4.z - player->vel.z);
            if (player->form != FORM_LANDMASTER) {
                sp44.x = 0.0f;
                sp44.y = -sp34;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp44, &sp38);
                player->unk_0D8.x = sp38.x;
                player->unk_0D8.y = sp38.y;
                player->unk_0D8.z = sp38.z;
            }
            if (Rand_ZeroOne() < 0.5f) {
                Player_DamageWings(player, 1, 15);
            } else {
                Player_DamageWings(player, 2, 15);
            }
            break;
        case 4:
            player->timer_224 = 20;
            func_play_800A668C(player->hit3.x - player->vel.x, player->hit3.y, player->hit3.z - player->vel.z);
            sp44.x = 0.0f;
            sp44.y = sp34;
            Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp44, &sp38);
            player->unk_0D8.x = sp38.x;
            player->unk_0D8.y = sp38.y;
            player->unk_0D8.z = sp38.z;
            if (Rand_ZeroOne() < 0.5f) {
                Player_DamageWings(player, 1, 15);
            } else {
                Player_DamageWings(player, 2, 15);
            }
            break;
    }
    if ((gCurrentLevel == LEVEL_VENOM_1) && (player->unk_1A4 == 42)) {
        if (player->pos.x > 0.0f) {
            player->unk_0D8.x = -30.0f;
        } else {
            player->unk_0D8.x = 30.0f;
        }
        player->timer_498 = 10;
    }
}

f32 D_800D2FEC[5] = {
    0.0f, 0.5f, -0.5f, 0.5f, -0.5f,
};

void func_play_800A729C(Player* player, u32 arg1, f32 arg2, f32 arg3) {
    player->unk_21C = arg1;
    switch (arg1) {
        case 1:
        case 2:
            player->pos.x = player->unk_090.x;
            player->unk_0D8.x = 0.0f;
            player->pos.x += D_800D2FEC[player->unk_21C];
            if (player->form == FORM_LANDMASTER) {
                player->pos.x -= D_800D2FEC[player->unk_21C];
            }
            Math_SmoothStepToF(&player->unk_0D0, 2.0f, 1.0f, 2.0f, 0.00001f);
            break;
        case 3:
        case 4:
            player->pos.z = player->unk_090.z;
            player->unk_0D8.z = 0.0f;
            player->pos.z += D_800D2FEC[player->unk_21C];
            if (player->form == FORM_LANDMASTER) {
                player->pos.z += D_800D2FEC[player->unk_21C];
            }
            player->unk_138 = player->pos.z;
            Math_SmoothStepToF(&player->unk_0D0, 2.0f, 1.0f, 2.0f, 0.00001f);
            break;
        case 0:
        case 5:
            break;
    }
}

bool func_play_800A73E4(f32* arg0, s32* arg1, f32 xPos, f32 yPos, f32 zPos) {
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
    sp98 = (s32) ((zPos + D_ctx_80177D20 + 1500.0f + 2400.0f) / 300.0f);
    if ((sp9C < 0) || (sp9C >= 16) || (sp98 < 0) || (sp98 >= 16)) {
        return false;
    }
    sp90 = Math_ModF(xPos + 2400.0f, 300.0f);
    sp94 = Math_ModF(zPos + D_ctx_80177D20 + 1500.0f + 2400.0f, 300.0f);
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
    sp48 = (-temp1 - crx * xPos - crz * (zPos + D_ctx_80177D20 + 1500.0f)) / cry;
    if (yPos < sp48) {
        *arg0 = sp48;
        *arg1 = sp8C;
        return true;
    }
    return false;
}

bool func_play_800A78C4(Hitbox* hitbox, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    if ((fabsf(hitbox->z.offset + arg3 - arg6) < (hitbox->z.size + D_ctx_8017853C)) &&
        (fabsf(hitbox->x.offset + arg1 - arg4) < (hitbox->x.size + D_ctx_8017853C)) &&
        (fabsf(hitbox->y.offset + arg2 - arg5) < (hitbox->y.size + D_ctx_8017853C))) {
        return true;
    }
    return false;
}

s32 func_play_800A7974(Player* player, f32* hitboxData, s32* index, f32 xPos, f32 yPos, f32 zPos, f32 xRot, f32 yRot,
                       f32 zRot, f32 arg9, f32 argA, f32 argB) {
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
            if (*hitboxData == HITBOX_TYPE_2) {
                Matrix_RotateZ(gCalcMatrix, -hitboxData[3] * M_DTOR, 0);
                Matrix_RotateX(gCalcMatrix, -hitboxData[1] * M_DTOR, 1);
                Matrix_RotateY(gCalcMatrix, -hitboxData[2] * M_DTOR, 1);
                Matrix_RotateZ(gCalcMatrix, -zRot * M_DTOR, 1);
                Matrix_RotateX(gCalcMatrix, -xRot * M_DTOR, 1);
                Matrix_RotateY(gCalcMatrix, -yRot * M_DTOR, 1);
                hitboxData += 4;
                spA0 = 1;
            } else {
                if (*hitboxData >= HITBOX_TYPE_3) {
                    hitboxData++;
                }
                Matrix_RotateZ(gCalcMatrix, -zRot * M_DTOR, 0);
                Matrix_RotateX(gCalcMatrix, -xRot * M_DTOR, 1);
                Matrix_RotateY(gCalcMatrix, -yRot * M_DTOR, 1);
            }
            if (!((arg9 == 0) && (argA == 0) && (argB == 0))) {
                Matrix_RotateZ(gCalcMatrix, -argB * M_DTOR, 1);
                Matrix_RotateX(gCalcMatrix, -arg9 * M_DTOR, 1);
                Matrix_RotateY(gCalcMatrix, -argA * M_DTOR, 1);
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
            if (func_play_800A78C4((Hitbox*) hitboxData, xPos, yPos, zPos, var_fv0, var_fv1, var_fa0)) {
                *index = i + 1;
                if (hitboxData[-1] == HITBOX_TYPE_3) {
                    return -1;
                }
                if (hitboxData[-1] == HITBOX_TYPE_4) {
                    return -2;
                }
                return 3;
            }
            if (hitboxData[-1] < HITBOX_TYPE_3) {
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
                if (func_play_800A78C4((Hitbox*) hitboxData, xPos, yPos, zPos, var_fv0, var_fv1, var_fa0)) {
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
                if (func_play_800A78C4((Hitbox*) hitboxData, xPos, yPos, zPos, var_fv0, var_fv1, var_fa0)) {
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
                if (func_play_800A78C4((Hitbox*) hitboxData, xPos, yPos, zPos, var_fv0, var_fv1, var_fa0)) {
                    *index = i + 1;
                    return 2;
                }
            }
        }
    }
    return 0;
}

bool func_play_800A8054(ObjectId objId, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, Vec3f* arg7,
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
        case OBJ_80_4:
        case OBJ_80_5:
            colId = COL2_1;
            useCol2 = true;
            break;
        case OBJ_80_149:
            colId = COL1_5;
            break;
        case OBJ_80_150:
            colId = COL1_6;
            break;
        case OBJ_BOSS_308:
            colId = COL1_4;
            break;
        case OBJ_BOSS_312:
            colId = COL1_9;
            break;
        case OBJ_BOSS_309:
            colId = COL1_7;
            break;
        case ACTOR_EVENT_ID:
            colId = COL1_3;
            break;
        case OBJ_BOSS_313:
            colId = COL1_8;
            break;
        case OBJ_80_39:
            colId = COL1_1;
            break;
        case OBJ_80_120:
            colId = COL2_18;
            useCol2 = true;
            break;
        case OBJ_80_124:
            colId = COL2_15;
            useCol2 = true;
            break;
        case OBJ_80_126:
            colId = COL2_16;
            useCol2 = true;
            break;
        case OBJ_80_47:
            colId = COL2_7;
            useCol2 = true;
            break;
        case OBJ_80_2:
            colId = COL2_2;
            useCol2 = true;
            break;
        case OBJ_80_3:
        case OBJ_80_69:
            colId = COL2_3;
            useCol2 = true;
            break;
        case OBJ_80_143:
            colId = COL2_17;
            useCol2 = true;
            break;
        case OBJ_80_140:
            colId = COL2_4;
            useCol2 = true;
            break;
        case OBJ_80_141:
            colId = COL2_6;
            useCol2 = true;
            break;
        case OBJ_80_117:
            colId = COL2_14;
            useCol2 = true;
            break;
        case OBJ_80_70:
            colId = COL2_8;
            useCol2 = true;
            break;
        case OBJ_80_72:
            colId = COL2_9;
            useCol2 = true;
            break;
        case OBJ_80_71:
            colId = COL2_10;
            useCol2 = true;
            break;
        case OBJ_80_73:
            colId = COL2_11;
            useCol2 = true;
            break;
        case OBJ_80_67:
            colId = COL2_12;
            useCol2 = true;
            break;
        case OBJ_80_74:
            colId = COL2_13;
            useCol2 = true;
            break;
        case OBJ_80_118:
        case OBJ_80_119:
        case OBJ_80_121:
        case OBJ_80_122:
        case OBJ_80_123:
        case OBJ_80_125:
        case OBJ_80_127:
        case OBJ_80_128:
        case OBJ_80_129:
        case OBJ_80_130:
        case OBJ_80_131:
        case OBJ_80_132:
        case OBJ_80_133:
        case OBJ_80_134:
        case OBJ_80_135:
        case OBJ_80_136:
        case OBJ_80_137:
        case OBJ_80_138:
        case OBJ_80_139:
        case OBJ_80_142:
        case OBJ_80_144:
        case OBJ_80_145:
        case OBJ_80_146:
        case OBJ_80_147:
        case OBJ_80_148:
        case OBJ_80_40:
        case OBJ_80_41:
        case OBJ_80_42:
        case OBJ_80_43:
        case OBJ_80_44:
        case OBJ_80_45:
        case OBJ_80_46:
        case OBJ_80_48:
        case OBJ_80_49:
        case OBJ_80_50:
        case OBJ_80_51:
        case OBJ_80_52:
        case OBJ_80_53:
        case OBJ_80_54:
        case OBJ_80_55:
        case OBJ_80_56:
        case OBJ_80_57:
        case OBJ_80_58:
        case OBJ_80_59:
        case OBJ_80_60:
        case OBJ_80_61:
        case OBJ_80_62:
        case OBJ_80_63:
        case OBJ_80_64:
        case OBJ_80_65:
        case OBJ_80_66:
        case OBJ_80_68:
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

// arg5 could be Vec3f (not Vec3f*)
s32 func_play_800A8304(Player* player, ObjectId objId, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    Vec3f sp84;
    Vec3f sp78;
    Vec3f sp6C;
    Vec3f sp60;
    Vec3f sp54;

    sp84.x = arg2;
    sp84.y = arg3;
    sp84.z = arg4;
    Matrix_RotateY(gCalcMatrix, -arg6 * M_DTOR, 0);
    sp78.x = player->vel.x;
    sp78.y = player->vel.y;
    sp78.z = player->vel.z;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp78, &sp54);
    if ((player->form == FORM_LANDMASTER) || (player->form == FORM_ON_FOOT)) {
        sp78.x = player->pos.x - sp84.x;
        sp78.y = player->pos.y - sp84.y;
        sp78.z = player->unk_138 - sp84.z;
        Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp78, &sp6C);
        if (func_play_800A8054(objId, sp84.x, sp84.y, sp84.z, sp6C.x + sp84.x, sp6C.y + sp84.y, sp6C.z + sp84.z, &sp60,
                               &sp54)) {
            player->pos.y = sp60.y;
            player->unk_104 = Math_RadToDeg(sp60.x);
            player->unk_10C = Math_RadToDeg(sp60.z);
            player->vel.y = 0.0f;
            if (player->form == FORM_ON_FOOT) {
                player->vel.y = -5.0f;
            }
            player->unk_1D4 = 1;
            return 5;
        }
        return 0;
    }
    sp78.x = player->hit3.x - sp84.x;
    sp78.y = player->hit3.y - sp84.y;
    sp78.z = player->hit3.z - sp84.z;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp78, &sp6C);
    if (func_play_800A8054(objId, sp84.x, sp84.y, sp84.z, sp6C.x + sp84.x, sp6C.y + sp84.y, sp6C.z + sp84.z, &sp60,
                           &sp54)) {
        return 3;
    }
    sp78.x = player->hit4.x - sp84.x;
    sp78.y = player->hit4.y - sp84.y;
    sp78.z = player->hit4.z - sp84.z;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp78, &sp6C);
    if (func_play_800A8054(objId, sp84.x, sp84.y, sp84.z, sp6C.x + sp84.x, sp6C.y + sp84.y, sp6C.z + sp84.z, &sp60,
                           &sp54)) {
        return 4;
    }
    sp78.x = player->hit1.x - sp84.x;
    sp78.y = player->hit1.y - sp84.y;
    sp78.z = player->hit1.z - sp84.z;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp78, &sp6C);
    if (func_play_800A8054(objId, sp84.x, sp84.y, sp84.z, sp6C.x + sp84.x, sp6C.y + sp84.y, sp6C.z + sp84.z, &sp60,
                           &sp54)) {
        return 1;
    }
    sp78.x = player->hit2.x - sp84.x;
    sp78.y = player->hit2.y - sp84.y;
    sp78.z = player->hit2.z - sp84.z;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp78, &sp6C);
    if (func_play_800A8054(objId, sp84.x, sp84.y, sp84.z, sp6C.x + sp84.x, sp6C.y + sp84.y, sp6C.z + sp84.z, &sp60,
                           &sp54)) {
        return 2;
    }
    return 0;
}

void func_play_800A86E4(Player* player) {
    s32 i;
    Item* item;
    s32 sp6C;

    for (i = 0, item = gItems; i < ARRAY_COUNT(gItems); i++, item++) {
        if ((item->obj.status == OBJ_ACTIVE) &&
            ((player->state_1C8 == PLAYERSTATE_1C8_3) || (player->state_1C8 == PLAYERSTATE_1C8_5)) &&
            (item->timer_4A == 0) &&
            func_play_800A7974(player, item->info.hitbox, &sp6C, item->obj.pos.x, item->obj.pos.y, item->obj.pos.z,
                               0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f)) {
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

void func_play_800A8804(Player* playerA, Player* playerB) {
    if (playerA->timer_498 == 0) {
        Player_ApplyDamage(playerA, 0, D_800D3000[playerA->form][playerB->form]);
        playerA->unk_288 = playerB->num + 1;
        playerB->unk_288 = playerA->num + 1;
    }
}

void func_play_800A887C(Player* player) {
    Vec3f sp3C;

    Matrix_Translate(gCalcMatrix, player->pos.x, player->pos.y, player->unk_138, 0);
    if (player->form == FORM_LANDMASTER) {
        player->unk_10C = 0.0f;
        player->unk_104 = 0.0f;

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
        Matrix_RotateY(gCalcMatrix, (player->unk_114 + 180.0f) * M_DTOR, 1);
        Matrix_RotateZ(gCalcMatrix, -(player->unk_0F8 * M_DTOR), 1);
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

void func_play_800A8BA4(Player* player) {
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
    Object_80* obj80; // A0
    Player* opponent; // 9C
    s32 sp98;
    f32 sp94;
    s32 sp90;
    f32 sp8C;

    func_play_800A887C(player);
    if (D_ctx_801784AC == 4) {
        switch (player->form) {
            case FORM_LANDMASTER:
                func_tank_800444BC(player);
                break;
            case FORM_BLUE_MARINE:
                if (Ground_801B6AEC(player->pos.x, player->pos.y - 12.0f, player->unk_138 + player->unk_144)) {
                    Ground_801B6E20(player->pos.x, player->unk_138 + player->unk_144, &spE8, &spE0, &spE4);
                    player->pos.y = spE0 + 10.0f;
                }
                break;
        }
    } else if (player->form == FORM_ARWING) {
        if ((player->hit1.y < (gGroundLevel + 13.0f)) && (player->state_1C8 != PLAYERSTATE_1C8_4)) {
            if (gGroundType == GROUNDTYPE_WATER) {
                player->unk_1F4 = 7;
                player->unk_0E4 = (player->unk_0D0 + player->unk_110) * 0.5f;
            } else {
                Player_ApplyDamage(player, 1, 21);
            }
            if (gCurrentLevel == LEVEL_FORTUNA) {
                func_effect_8007BC7C(player->hit1.x, player->hit1.y, player->hit1.z, 6.0f);
                func_effect_8007BC7C(player->hit1.x, player->hit1.y, player->hit1.z, 6.0f);
                func_effect_8007BC7C(player->hit1.x, player->hit1.y, player->hit1.z, 6.0f);
            }
        }
        if ((player->hit2.y < (gGroundLevel + 13.0f)) && (player->state_1C8 != PLAYERSTATE_1C8_4)) {
            if (gGroundType == GROUNDTYPE_WATER) {
                player->unk_1F4 = 7;
                player->unk_0E4 = (player->unk_0D0 + player->unk_110) * 0.5f;
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
            Object_58* obj58;

            sp8C = 1100.0f;
            if ((gCurrentLevel == LEVEL_SECTOR_Y) || (gCurrentLevel == LEVEL_VENOM_ANDROSS)) {
                sp8C = 4000.0f;
            }
            for (i = 0, obj58 = gObjects58; i < 200; i++, obj58++) {
                if (obj58->obj.status == OBJ_ACTIVE) {
                    spC8.x = obj58->obj.pos.x - player->pos.x;
                    spC8.z = obj58->obj.pos.z - player->unk_138;
                    if (sqrtf(SQ(spC8.x) + SQ(spC8.z)) < sp8C) {
                        if ((obj58->obj.id == OBJ_80_117) || (obj58->obj.id == OBJ_80_143) ||
                            (obj58->obj.id == OBJ_80_141) || (obj58->obj.id == OBJ_80_149) ||
                            (obj58->obj.id == OBJ_80_150) || (obj58->obj.id == OBJ_80_148) ||
                            (obj58->obj.id == OBJ_80_160) || (obj58->obj.id == OBJ_80_1) ||
                            (obj58->obj.id == OBJ_80_3) || (obj58->obj.id == OBJ_80_140)) {
                            temp_v0 = func_play_800A8304(player, obj58->obj.id, obj58->obj.pos.x, obj58->obj.pos.y,
                                                         obj58->obj.pos.z, obj58->obj.rot.x, obj58->obj.rot.y,
                                                         obj58->obj.rot.z);
                            if (temp_v0 != 0) {
                                if ((player->form == FORM_LANDMASTER) || (player->form == FORM_ON_FOOT)) {
                                    func_play_800A729C(player, temp_v0, obj58->obj.pos.x, obj58->obj.pos.z);
                                } else {
                                    Player_ApplyDamage(player, temp_v0, obj58->info.damage);
                                }
                            }
                            if ((gCurrentLevel == LEVEL_FORTUNA) || (gCurrentLevel == LEVEL_VENOM_2)) {
                                temp_v0 = func_play_800A7974(player, obj58->info.hitbox, &sp98, obj58->obj.pos.x,
                                                             obj58->obj.pos.y, obj58->obj.pos.z, obj58->obj.rot.x,
                                                             obj58->obj.rot.y, obj58->obj.rot.z, 0.0f, 0.0f, 0.0f);
                                if ((temp_v0 != 0) && (temp_v0 < 0)) {
                                    if (player->unk_22C == 0) {
                                        func_effect_8007A6F0(&obj58->obj.pos, 0x19000001);
                                    }
                                    player->unk_22C += 2;
                                    if (player->unk_22C >= 4) {
                                        player->unk_22C = 4;
                                    }
                                }
                            }
                        } else {
                            temp_v0 = func_play_800A7974(player, obj58->info.hitbox, &sp98, obj58->obj.pos.x,
                                                         obj58->obj.pos.y, obj58->obj.pos.z, obj58->obj.rot.x,
                                                         obj58->obj.rot.y, obj58->obj.rot.z, 0.0f, 0.0f, 0.0f);
                            if (temp_v0 != 0) {
                                if (temp_v0 < 0) {
                                    if (player->unk_22C == 0) {
                                        func_effect_8007A6F0(&obj58->obj.pos, 0x19000001);
                                    }
                                    player->unk_22C += 2;
                                    if (player->unk_22C >= 4) {
                                        player->unk_22C = 4;
                                    }
                                } else if ((player->form == FORM_LANDMASTER) || (player->form == FORM_ON_FOOT)) {
                                    func_play_800A729C(player, temp_v0, obj58->obj.pos.x, obj58->obj.pos.z);
                                } else {
                                    Player_ApplyDamage(player, temp_v0, obj58->info.damage);
                                    if (obj58->obj.id == OBJ_80_131) {
                                        Matrix_RotateY(gCalcMatrix, (obj58->obj.rot.y + 180.0f) * M_DTOR, 0);
                                        Matrix_MultVec3f(gCalcMatrix, &D_800D3040[sp98 - 1], &spBC);
                                        player->unk_0D8.x = spBC.x;
                                        player->unk_0D8.y = spBC.y;
                                        player->unk_0D8.z = spBC.z;

                                        player->unk_0E8 = player->unk_0E4 = 0.0f;
                                        player->pos.x = player->unk_090.x;
                                        player->pos.y = player->unk_090.y;
                                        player->pos.z = player->unk_090.z;
                                        player->unk_114 = obj58->obj.rot.y + 180.0f;
                                        player->timer_498 = 5;
                                    }
                                    if ((obj58->obj.id == OBJ_80_135) || (obj58->obj.id == OBJ_80_136)) {
                                        if (obj58->obj.id == OBJ_80_135) {
                                            Matrix_RotateY(gCalcMatrix, (obj58->obj.rot.y + 180.0f) * M_DTOR, 0);
                                            Matrix_MultVec3f(gCalcMatrix, &D_800D3088[sp98 - 1], &spBC);
                                        } else {
                                            Matrix_RotateY(gCalcMatrix, obj58->obj.rot.y * M_DTOR, 0);
                                            Matrix_MultVec3f(gCalcMatrix, &D_800D30B8[sp98 - 1], &spBC);
                                        }
                                        player->unk_0D8.x = spBC.x;
                                        player->unk_0D8.y = spBC.y;
                                        player->unk_0D8.z = spBC.z;
                                        player->unk_0E8 = 0.0f;
                                        player->unk_0E4 = 0.0f;
                                        player->pos.x = player->unk_090.x;
                                        player->pos.y = player->unk_090.y;
                                        player->pos.z = player->unk_090.z;
                                        if (obj58->obj.id == OBJ_80_135) {
                                            player->unk_114 = obj58->obj.rot.y + 180.0f;
                                        } else {
                                            player->unk_114 = obj58->obj.rot.y;
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
            for (i = 0, obj80 = gObjects80; i < ARRAY_COUNT(gObjects80); i++, obj80++) {
                if ((obj80->obj.status == OBJ_ACTIVE) && (obj80->obj.id != OBJ_80_58) &&
                    (obj80->obj.id != OBJ_80_105) && (obj80->obj.id != OBJ_80_59) && (obj80->obj.id != OBJ_80_60) &&
                    (obj80->obj.id != OBJ_80_61) && (obj80->obj.id != OBJ_80_66) && (obj80->obj.id != OBJ_80_67) &&
                    (obj80->obj.id != OBJ_80_70) && (obj80->obj.id != OBJ_80_72) && (obj80->obj.id != OBJ_80_71) &&
                    (obj80->obj.id != OBJ_80_73) && (obj80->obj.id != OBJ_80_74) && (obj80->obj.id != OBJ_80_69) &&
                    ((player->unk_138 - 2000.0f) < obj80->obj.pos.z)) {
                    if ((obj80->obj.id == OBJ_80_1) || (obj80->obj.id == OBJ_80_4) || (obj80->obj.id == OBJ_80_5) ||
                        (obj80->obj.id == OBJ_80_47) || (obj80->obj.id == OBJ_80_117) ||
                        (obj80->obj.id == OBJ_80_120) || (obj80->obj.id == OBJ_80_124) ||
                        (obj80->obj.id == OBJ_80_126) || (obj80->obj.id == OBJ_80_2) || (obj80->obj.id == OBJ_80_3)) {
                        spC8.x = obj80->obj.pos.x - player->pos.x;
                        spC8.z = obj80->obj.pos.z - player->unk_138;
                        if (sqrtf(SQ(spC8.x) + SQ(spC8.z)) < 1100.0f) {
                            temp_v0 = func_play_800A8304(player, obj80->obj.id, obj80->obj.pos.x, obj80->obj.pos.y,
                                                         obj80->obj.pos.z, obj80->obj.rot.x, obj80->obj.rot.y,
                                                         obj80->obj.rot.z);
                            if (temp_v0 != 0) {
                                Player_ApplyDamage(player, temp_v0, obj80->info.damage);
                            }
                        }
                    } else {
                        padB0 = obj80->obj.rot.y;
                        if (obj80->info.action == (ObjectFunc) func_enmy_80066EA8) {
                            padB0 = 0.0f;
                        }
                        temp_v0 = func_play_800A7974(player, obj80->info.hitbox, &sp98, obj80->obj.pos.x,
                                                     obj80->obj.pos.y, obj80->obj.pos.z, obj80->obj.rot.x, padB0,
                                                     obj80->obj.rot.z, 0.0f, 0.0f, 0.0f);
                        if (temp_v0 != 0) {
                            if (temp_v0 < 0) {
                                if (temp_v0 == -1) {
                                    D_ctx_80178540 = 40;
                                    D_ctx_80178570 = 20;
                                    D_ctx_80178574 = 20;
                                    D_ctx_80178578 = 20;
                                    player->unk_23C = 80;
                                }
                                if (player->unk_22C == 0) {
                                    AUDIO_PLAY_SFX(0x19000001, obj80->sfxSource, 0);
                                }
                                player->unk_22C += 2;
                                if (player->unk_22C >= 4) {
                                    player->unk_22C = 4;
                                }
                            } else if (obj80->obj.id == OBJ_80_54) {
                                if (player->unk_22C == 0) {
                                    AUDIO_PLAY_SFX(0x19832019, obj80->sfxSource, 0);
                                }
                                player->unk_22C += 2;
                                if (player->unk_22C >= 4) {
                                    player->unk_22C = 4;
                                }
                            } else {
                                Player_ApplyDamage(player, temp_v0, obj80->info.damage);
                                if ((obj80->obj.id == OBJ_80_48) || (obj80->obj.id == OBJ_80_55) ||
                                    (obj80->obj.id == OBJ_80_49)) {
                                    Matrix_RotateY(gCalcMatrix, obj80->obj.rot.y * M_DTOR, 0);
                                    spC8.x = -(player->unk_0D0 + player->unk_110) * 0.7f;
                                    spC8.y = 0.0f;
                                    spC8.z = 0.0f;

                                    Matrix_MultVec3f(gCalcMatrix, &spC8, &spBC);
                                    player->unk_0D8.x = spBC.x;
                                    player->unk_0D8.y = spBC.y;
                                    player->pos.x = player->unk_090.x;
                                    player->timer_498 = 5;
                                } else if (obj80->obj.id == OBJ_80_50) {
                                    if (player->pos.x < obj80->obj.pos.x) {
                                        player->unk_0D8.x = -30.0f;
                                        player->unk_0E8 = 45.0f;
                                    } else {
                                        player->unk_0D8.x = 30.0f;
                                        player->unk_0E8 = -45.0f;
                                    }
                                    player->unk_0D8.y = 0.0f;
                                    player->pos.x = player->unk_090.x;
                                    player->timer_498 = 5;
                                } else if (obj80->obj.id == OBJ_80_131) {
                                    Matrix_RotateY(gCalcMatrix, (obj80->obj.rot.y + 180.0f) * M_DTOR, 0);
                                    Matrix_RotateZ(gCalcMatrix, -obj80->obj.rot.z * M_DTOR, 1);
                                    Matrix_MultVec3f(gCalcMatrix, &D_800D3040[sp98 - 1], &spBC);
                                    player->unk_0D8.x = spBC.x;
                                    player->unk_0D8.y = spBC.y;
                                    player->unk_0E8 = 0.0f;
                                    player->unk_0E4 = 0.0f;
                                    player->timer_498 = 5;
                                    player->pos.x = player->unk_090.x;
                                    player->pos.y = player->unk_090.y;
                                }
                            }
                        }
                    }
                }
            }
        }
        for (i = 0, boss = gBosses; i < ARRAY_COUNT(gBosses); i++, boss++) {
            if (boss->obj.status == OBJ_ACTIVE) {
                if ((boss->obj.id == OBJ_BOSS_312) || (boss->obj.id == OBJ_BOSS_308) ||
                    (boss->obj.id == OBJ_BOSS_313) || (boss->obj.id == OBJ_BOSS_309)) {
                    temp_v0 = func_play_800A8304(player, boss->obj.id, boss->obj.pos.x, boss->obj.pos.y,
                                                 boss->obj.pos.z, boss->obj.rot.x, boss->obj.rot.y, boss->obj.rot.z);
                    if (temp_v0 != 0) {
                        Player_ApplyDamage(player, temp_v0, boss->info.damage);
                        break;
                    }
                }
                if (boss->obj.id == OBJ_BOSS_310) {
                    spfD4.x = fabsf(boss->obj.pos.x - player->pos.x) * .8333333f;
                    spfD4.y = fabsf(boss->obj.pos.y - player->pos.y) * 2;
                    spfD4.z = fabsf(boss->obj.pos.z - player->unk_138) * 0.8333333f;
                    if ((VEC3F_MAG(&spfD4)) < 1500.0f) {
                        Player_ApplyDamage(player, 0, boss->info.damage);
                        player->unk_110 = 0.0f;
                        player->timer_498 = 5;
                        player->unk_0D8.y = 30.0f;
                        boss->dmgType = DMG_BEAM;
                        func_effect_8007BFFC(player->pos.x + RAND_FLOAT_CENTERED(10.0f),
                                             player->pos.y + RAND_FLOAT(10.0f),
                                             player->unk_138 + RAND_FLOAT_CENTERED(10.0f), 0.0f, 15.0f, 0.0f, 2.0f, 5);
                        for (j = 0; j < 10; j++) {
                            func_effect_8007C484(
                                player->pos.x + RAND_FLOAT_CENTERED(30.0f), player->pos.y + RAND_FLOAT(10.0f),
                                player->unk_138 + RAND_FLOAT_CENTERED(30.0f), player->vel.x, 20.0f + player->vel.y,
                                player->vel.z, RAND_FLOAT(0.1f) + 0.1f, player->num + 11);
                        }
                        break;
                    }
                } else {
                    if (boss->obj.id == OBJ_BOSS_316) {
                        spfD4.x = fabsf(boss->obj.pos.x - player->pos.x);
                        spfD4.y = fabsf(boss->obj.pos.y - 300.0f - player->pos.y) * 7.42f;
                        spfD4.z = fabsf(boss->obj.pos.z - player->unk_138);
                        if ((VEC3F_MAG(&spfD4)) < 2700.0f) {
                            Player_ApplyDamage(player, 3, boss->info.damage);
                        }
                    }
                    temp_v0 = func_play_800A7974(player, boss->info.hitbox, &sp98, boss->obj.pos.x, boss->obj.pos.y,
                                                 boss->obj.pos.z, boss->obj.rot.x, boss->obj.rot.y, boss->obj.rot.z,
                                                 0.0f, 0.0f, 0.0f);
                    if (temp_v0 != 0) {
                        if (temp_v0 < 0) {
                            if (player->unk_22C == 0) {
                                AUDIO_PLAY_SFX(0x19000001, boss->sfxSource, 0);
                            }
                            player->unk_22C += 2;
                            if (player->unk_22C >= 4) {
                                player->unk_22C = 4;
                            }
                        } else {
                            if ((boss->obj.id == OBJ_BOSS_320) && (boss->timer_056 != 0) && (sp98 == 5)) {
                                break;
                            }
                            Player_ApplyDamage(player, temp_v0, boss->info.damage);
                            if ((boss->obj.id == OBJ_BOSS_303) && ((boss->state == 2) || (boss->state == 3)) &&
                                (sp98 >= 9)) {
                                player->unk_0D8.y = -100.0f;
                            }
                            if ((boss->obj.id == OBJ_BOSS_320) && (sp98 < 5)) {
                                player->unk_0D8.x = boss->fwork[14];
                                player->unk_0D8.y = boss->fwork[15];
                            }
                        }
                    }
                }
            }
        }
        for (i = 0, actor = gActors; i < ARRAY_COUNT(gActors); i++, actor++) {
            if ((actor->obj.status == OBJ_ACTIVE) && (actor->timer_0C2 == 0)) {
                if (actor->obj.id == OBJ_ACTOR_180) {
                    temp_v0 =
                        func_play_800A8304(player, actor->obj.id, actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z,
                                           actor->obj.rot.x, actor->obj.rot.y, actor->obj.rot.z);
                    if (temp_v0 != 0) {
                        Player_ApplyDamage(player, temp_v0, actor->info.damage);
                    }
                } else if (actor->obj.id == OBJ_ACTOR_EVENT) {
                    if (actor->unk_0B4 == 42) {
                        temp_v0 =
                            func_play_800A8304(player, ACTOR_EVENT_ID, actor->obj.pos.x, actor->obj.pos.y,
                                               actor->obj.pos.z, actor->obj.rot.x, actor->obj.rot.y, actor->obj.rot.z);
                        if (temp_v0 != 0) {
                            Player_ApplyDamage(player, temp_v0, actor->info.damage);
                        }
                    } else if (actor->unk_0B4 == EINFO_63) {
                        spfD4.x = fabsf(actor->obj.pos.x - player->pos.x);
                        spfD4.y = fabsf(actor->obj.pos.y - player->pos.y);
                        spfD4.z = fabsf(actor->obj.pos.z - player->unk_138);
                        if ((VEC3F_MAG(&spfD4)) < 900.0f) {
                            Player_ApplyDamage(player, 0, actor->info.damage);
                            actor->unk_0D0 = 3;
                        }
                    } else {
                        temp_v0 = func_play_800A7974(player, actor->info.hitbox, &sp98, actor->obj.pos.x,
                                                     actor->obj.pos.y, actor->obj.pos.z, actor->obj.rot.x,
                                                     actor->obj.rot.y, actor->obj.rot.z, actor->vwork[29].x,
                                                     actor->vwork[29].y, actor->vwork[29].z + actor->unk_0F4.z);
                        if (temp_v0 != 0) {
                            if ((temp_v0 < 0) && (actor->unk_0B4 == EINFO_38)) {
                                actor->info.hitbox = LOAD_ASSET(D_SX_6032328);
                                if (gRingPassCount >= 0) {
                                    actor->unk_046 = 2;
                                    gRingPassCount++;
                                    if (gRingPassCount == 3) {
                                        Radio_PlayMessage(gMsg_ID_5504, RCID_FALCO);
                                    }
                                    AUDIO_PLAY_SFX(D_enmy_800CFF54[gRingPassCount], gPlayer[0].sfxSource, 0);
                                    AUDIO_PLAY_SFX(0x49008025, gDefaultSfxSource, 4);
                                }
                            } else if (temp_v0 < 0) {
                                if (player->unk_22C == 0) {
                                    AUDIO_PLAY_SFX(0x19000001, actor->sfxSource, 0);
                                }
                                player->unk_22C += 2;
                                if (player->unk_22C >= 4) {
                                    player->unk_22C = 4;
                                }
                            } else {
                                Player_ApplyDamage(player, temp_v0, actor->info.damage);
                                actor->unk_0D0 = 3;
                                actor->unk_0D4 = player->num + 1;
                            }
                        }
                    }
                } else if ((actor->obj.id >= OBJ_ACTOR_205) && (actor->obj.id < OBJ_ACTOR_214)) {
                    temp_v0 =
                        func_play_800A7974(player, actor->info.hitbox, &sp98, actor->fwork[25] + actor->obj.pos.x,
                                           actor->fwork[8] + actor->obj.pos.y + 25.0f, actor->obj.pos.z,
                                           actor->fwork[29], actor->fwork[26], actor->obj.rot.z, 0.0f, 0.0f, 0.0f);
                    if (temp_v0 != 0) {
                        actor->unk_0D0 = 3;
                        if (actor->info.damage) {
                            Player_ApplyDamage(player, temp_v0, actor->info.damage);
                        } else {
                            actor->unk_0D0 = -1;
                        }
                    }
                } else {
                    temp_v0 = func_play_800A7974(player, actor->info.hitbox, &sp98, actor->obj.pos.x, actor->obj.pos.y,
                                                 actor->obj.pos.z, actor->obj.rot.x, actor->obj.rot.y, actor->obj.rot.z,
                                                 0.0f, 0.0f, 0.0f);
                    if (temp_v0 != 0) {
                        if (temp_v0 < 0) {
                            if (player->unk_22C == 0) {
                                AUDIO_PLAY_SFX(0x19000001, actor->sfxSource, 0);
                            }
                            player->unk_22C += 2;
                            if (player->unk_22C >= 4) {
                                player->unk_22C = 4;
                            }
                        } else {
                            actor->unk_0D0 = 3;
                            if (actor->obj.id == OBJ_ACTOR_190) {
                                actor->unk_0D0 = -1;
                            }
                            if (actor->info.damage) {
                                Player_ApplyDamage(player, temp_v0, actor->info.damage);
                                if (actor->obj.id == OBJ_ACTOR_225) {
                                    player->unk_0D8.y = 0.0f;
                                }
                            } else {
                                actor->unk_0D0 = -1;
                            }
                        }
                    }
                }
            }
        }
        for (i = 0, sprite = gSprites; i < ARRAY_COUNT(gSprites); i++, sprite++) {
            if (sprite->obj.status == OBJ_ACTIVE) {
                if ((player->unk_138 - 200.0f) < sprite->obj.pos.z) {
                    temp_v0 =
                        func_play_800A7974(player, sprite->info.hitbox, &sp98, sprite->obj.pos.x, sprite->obj.pos.y,
                                           sprite->obj.pos.z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
                    if (temp_v0 != 0) {
                        if ((sprite->obj.id == OBJ_SPRITE_FO_POLE) || (sprite->obj.id == OBJ_SPRITE_CO_POLE) ||
                            (sprite->obj.id == OBJ_SPRITE_TI_CACTUS) || (sprite->obj.id == OBJ_SPRITE_CO_TREE)) {
                            sprite->unk_46 = 1;
                            player->unk_1F4 = 6;
                            player->unk_21C = 0;
                        } else {
                            Player_ApplyDamage(player, temp_v0, sprite->info.damage);
                        }
                    }
                }
            }
        }
    }
    func_play_800A86E4(player);
    if (gCamCount == 4) {
        for (opponent = &gPlayer[3], i = 3; i >= 0; i--, opponent--) {
            if ((i != gPlayerNum) && (opponent->state_1C8 == PLAYERSTATE_1C8_3)) {
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
                if ((fabsf(opponent->unk_138 - player->unk_138) <= spBC.z) &&
                    (fabsf(opponent->pos.y - player->pos.y) <= spBC.y) &&
                    (fabsf(opponent->pos.x - player->pos.x) <= spBC.x)) {
                    if ((player->form == FORM_ON_FOOT) && (opponent->form == FORM_ON_FOOT)) {
                        player->pos.x = player->unk_090.x;
                        player->pos.y = player->unk_090.y;
                        player->pos.z = player->unk_138 = player->unk_090.z;
                        opponent->pos.x = opponent->unk_090.x;
                        opponent->pos.y = opponent->unk_090.y;
                        opponent->pos.z = opponent->unk_138 = opponent->unk_090.z;
                        player->unk_0D8.x = (player->pos.x - opponent->unk_090.x) * 0.5f;
                        player->unk_0D8.z = (player->unk_138 - opponent->unk_138) * 0.5f;
                        opponent->unk_0D8.x = -player->unk_0D8.x;
                        opponent->unk_0D8.z = -player->unk_0D8.z;
                        opponent->unk_0D0 = player->unk_0D0 = 2.0f;
                    } else {
                        func_play_800A8804(player, opponent);
                        func_play_800A8804(opponent, player);
                    }
                }
            }
        }
    }
    if (D_ctx_80178294 != 0) {
        if (func_play_800A73E4(&sp94, &sp90, player->hit4.x, player->hit4.y, player->hit4.z)) {
            if (gCurrentLevel == LEVEL_ZONESS) {
                player->unk_0E4 = (player->unk_0D0 + player->unk_110) * 0.8f;
                player->unk_1F4 = 15;
                func_effect_8007B228(player->hit4.x, sp94, player->hit4.z, 1.0f);
            } else {
                if (player->unk_1F4 == 0) {
                    Player_ApplyDamage(player, 4, 10);
                }
                player->unk_0D8.y = 30.0f;
                player->unk_0E4 = (player->unk_0D0 + player->unk_110) * 0.8f;
            }
            if (player->state_1C8 == PLAYERSTATE_1C8_4) {
                player->timer_220 = 2;
                func_effect_8007AFD0(player->pos.x, player->unk_138, 30.0f, 0.0f, 5.0f);
                func_effect_8007AFD0(player->pos.x, player->unk_138, -30.0f, 0.0f, 5.0f);
            }
        }
        if (func_play_800A73E4(&sp94, &sp90, player->pos.x + ((player->hit1.x - player->pos.x) * 1.5f),
                               player->pos.y + (player->hit1.y - player->pos.y) * 1.5f, player->hit1.z)) {
            if (gCurrentLevel == LEVEL_ZONESS) {
                func_effect_8007B228(player->pos.x + (player->hit1.x - player->pos.x) * 1.5f, sp94, player->hit1.z,
                                     1.0f);
            } else {
                if (player->unk_1F4 == 0) {
                    Player_ApplyDamage(player, 1, 10);
                }
                player->unk_0D8.y = 30.0f;
            }
        }
        if (func_play_800A73E4(&sp94, &sp90, player->pos.x + ((player->hit2.x - player->pos.x) * 1.5f),
                               player->pos.y + (player->hit2.y - player->pos.y) * 1.5f, player->hit2.z)) {
            if (gCurrentLevel == LEVEL_ZONESS) {
                func_effect_8007B228(player->pos.x + (player->hit2.x - player->pos.x) * 1.5f, sp94, player->hit2.z,
                                     1.0f);
            } else {
                if (player->unk_1F4 == 0) {
                    Player_ApplyDamage(player, 2, 40);
                }
                player->unk_0D8.y = 30.0f;
            }
        }
    }
}

void func_play_800AA800(Player* player) {
    s32 sp144;
    Object_58* obj58;
    Object_80* obj80;
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
        player->unk_064 = player->pos.x;
        player->unk_06C = player->unk_138 - player->pos.y;
        if (D_ctx_801784AC != 4) {
            if (gCamCount == 1) {
                player->unk_068 = gGroundLevel + 3.0f;
            } else {
                player->unk_068 = gGroundLevel;
                if (player->form == FORM_ON_FOOT) {
                    player->unk_06C = player->unk_138;
                }
            }
            player->unk_248 = player->unk_24C = player->unk_070 = 0.0f;
        }
        sp100 = 0.0f;
        spFC = 0.0f;
        spF8 = 0.0f;
        if (gCamCount != 1) {
            if (player->form == FORM_ON_FOOT) {
                for (sp144 = 0; sp144 < 200; sp144++) {
                    obj58 = &gObjects58[sp144];
                    if ((obj58->obj.status == OBJ_ACTIVE) &&
                        ((obj58->obj.id == OBJ_80_143) || (obj58->obj.id == OBJ_80_140) ||
                         (obj58->obj.id == OBJ_80_141)) &&
                        (fabsf(obj58->obj.pos.x - player->pos.x) < 2000.0f) &&
                        (fabsf(obj58->obj.pos.z - player->unk_138) < 2000.0f)) {
                        spC8.x = obj58->obj.pos.x;
                        spC8.y = obj58->obj.pos.y;
                        spC8.z = obj58->obj.pos.z;
                        spD4.x = player->pos.x;
                        spD4.y = gGroundLevel;
                        spD4.z = player->unk_138;
                        colId = COL2_4;
                        if (obj58->obj.id == OBJ_80_141) {
                            colId = COL2_6;
                        } else if (obj58->obj.id == OBJ_80_143) {
                            colId = COL2_17;
                        }
                        if (func_col2_800A3690(&spD4, &spC8, colId, &spBC)) {
                            player->unk_068 = spBC.y + 1.0f;
                            player->unk_248 = spBC.x;
                            player->unk_24C = spBC.z;
                            break;
                        }
                    }
                }
            }
        } else {
            if ((gLevelMode == LEVELMODE_ALL_RANGE) && (gLevelType == LEVELTYPE_PLANET)) {
                player->unk_064 = player->pos.x;
                player->unk_06C = player->unk_138;
                for (sp144 = 0, obj58 = gObjects58; sp144 < 200; sp144++, obj58++) {
                    if ((obj58->obj.status == OBJ_ACTIVE) &&
                        ((obj58->obj.id == OBJ_80_150) || (obj58->obj.id == OBJ_80_149) ||
                         (obj58->obj.id == OBJ_80_148) || (obj58->obj.id == OBJ_80_1) || (obj58->obj.id == OBJ_80_3)) &&
                        (fabsf(obj58->obj.pos.x - player->pos.x) < 2500.0f) &&
                        (fabsf(obj58->obj.pos.z - player->unk_138) < 2500.0f)) {
                        tempx = obj58->obj.pos.x;
                        tempy = obj58->obj.pos.y;
                        tempz = obj58->obj.pos.z;
                        sp120 = obj58->obj.rot.y;
                        Matrix_RotateY(gCalcMatrix, -sp120 * M_DTOR, 0);
                        spEC.x = player->pos.x - tempx;
                        spEC.y = 0.0f;
                        spEC.z = player->unk_138 - tempz;
                        Matrix_MultVec3fNoTranslate(gCalcMatrix, &spEC, &spE0);
                        spD4.x = spE0.x + tempx;
                        spD4.y = spE0.y + tempy;
                        spD4.z = spE0.z + tempz;
                        spC8.x = tempx;
                        spC8.y = tempy;
                        spC8.z = tempz;

                        if ((obj58->obj.id == OBJ_80_149) || (obj58->obj.id == OBJ_80_150)) {
                            if (obj58->obj.id == OBJ_80_149) {
                                colId = COL1_5;
                            } else {
                                colId = COL1_6;
                            }
                            if (func_col1_800998FC(&spD4, &spC8, &sp9C, colId, &spB0, spA8) > 0) {
                                player->unk_068 = spB0.y;
                                player->unk_248 = spA8[0];
                                player->unk_24C = spA8[1];
                                player->unk_070 = DEG_TO_RAD(sp120);
                            }
                        } else {
                            colId = COL2_0;
                            if (obj58->obj.id == OBJ_80_3) {
                                colId = COL2_3;
                            }
                            if (func_col2_800A3690(&spD4, &spC8, colId, &spBC)) {
                                player->unk_068 = spBC.y;
                                player->unk_248 = spBC.x;
                                player->unk_24C = spBC.z;
                                player->unk_070 = DEG_TO_RAD(sp120);
                            }
                        }
                    }
                }
            }
            for (sp144 = 0, obj80 = gObjects80;
                 (sp144 < 50) && (gLevelMode == LEVELMODE_ON_RAILS) && (gCurrentLevel != LEVEL_VENOM_1);
                 sp144++, obj80++) {
                if ((obj80->obj.status == OBJ_ACTIVE) && ((player->unk_138 - 3000.0f) < obj80->obj.pos.z) &&
                    (obj80->obj.id != OBJ_80_0) && (obj80->obj.id != OBJ_80_8)) {
                    tempx = obj80->obj.pos.x;
                    tempy = obj80->obj.pos.y;
                    tempz = obj80->obj.pos.z;
                    sp120 = obj80->obj.rot.y;
                    if ((obj80->obj.id == OBJ_80_3) || (obj80->obj.id == OBJ_80_2) || (obj80->obj.id == OBJ_80_47) ||
                        (obj80->obj.id == OBJ_80_4) || (obj80->obj.id == OBJ_80_5)) {
                        Matrix_RotateY(gCalcMatrix, -sp120 * M_DTOR, 0);
                        for (var_fs1 = var_fs0 = -50.0f; var_fs0 > -500.0f; var_fs0 -= 5.0f, var_fs1 -= 5.0f) {
                            spEC.x = player->pos.x - tempx;
                            spEC.y = player->pos.y + var_fs0 - tempy;
                            spEC.z = player->unk_138 + var_fs1 - tempz;
                            Matrix_MultVec3fNoTranslate(gCalcMatrix, &spEC, &spE0);
                            if ((player->pos.y + var_fs0) <= gGroundLevel) {
                                break;
                            }
                            spD4.x = spE0.x + tempx;
                            spD4.y = spE0.y + tempy;
                            spD4.z = spE0.z + tempz;
                            spC8.x = tempx;
                            spC8.y = tempy;
                            spC8.z = tempz;

                            colId = COL2_0;

                            if (obj80->obj.id == OBJ_80_47) {
                                colId = COL2_7;
                            }
                            if (obj80->obj.id == OBJ_80_2) {
                                colId = COL2_2;
                            } else if (obj80->obj.id == OBJ_80_3) {
                                colId = COL2_3;
                            } else if ((obj80->obj.id == OBJ_80_4) || (obj80->obj.id == OBJ_80_5)) {
                                colId = COL2_1;
                            }
                            if (func_col2_800A3690(&spD4, &spC8, colId, &spBC)) {
                                player->unk_068 = spBC.y;
                                player->unk_06C = player->unk_138 + var_fs1;
                                player->unk_248 = spBC.x;
                                player->unk_24C = spBC.z;
                                player->unk_070 = DEG_TO_RAD(sp120);
                                break;
                            }
                        }
                    } else {
                        hitboxData = obj80->info.hitbox;
                        count = *hitboxData;
                        if (count != 0) {
                            if (obj80->info.action == (ObjectFunc) func_enmy_80066EA8) {
                                sp120 = 0.0f;
                            }
                            hitboxData++;
                            for (i = 0; i < count; i++, hitboxData += 6) {
                                if (*hitboxData >= HITBOX_TYPE_3) {
                                    break;
                                }

                                if (*hitboxData == HITBOX_TYPE_2) {
                                    sp100 = hitboxData[1];
                                    spFC = hitboxData[2];
                                    spF8 = hitboxData[3];
                                    hitboxData += 4;
                                    Matrix_RotateZ(gCalcMatrix, -spF8 * M_DTOR, 0);
                                    Matrix_RotateX(gCalcMatrix, -sp100 * M_DTOR, 1);
                                    Matrix_RotateY(gCalcMatrix, -spFC * M_DTOR, 1);
                                    Matrix_RotateY(gCalcMatrix, -sp120 * M_DTOR, 1);
                                } else {
                                    Matrix_RotateY(gCalcMatrix, -sp120 * M_DTOR, 0);
                                }
                                hitbox = (Hitbox*) hitboxData;
                                for (var_fs0 = var_fs1 = -50.0f; var_fs0 > -500.0f; var_fs0 -= 5.0f, var_fs1 -= 5.0f) {
                                    spEC.x = player->pos.x - tempx;
                                    spEC.y = player->pos.y + var_fs0 - tempy;
                                    spEC.z = player->unk_138 + var_fs1 - tempz;
                                    Matrix_MultVec3fNoTranslate(gCalcMatrix, &spEC, &spE0);
                                    tempx2 = spE0.x + tempx;
                                    tempy2 = spE0.y + tempy;
                                    tempz2 = spE0.z + tempz;
                                    if (spEC.y + tempy <= gGroundLevel) {
                                        break;
                                    }

                                    if (func_play_800A78C4(hitbox, tempx, tempy, tempz, tempx2, tempy2, tempz2)) {
                                        if (gGroundLevel < player->unk_068) {
                                            player->unk_068 = spEC.y + 15.0f + tempy;
                                            player->unk_06C = spEC.z + 10.0f + tempz;
                                            player->unk_248 = DEG_TO_RAD(sp100);
                                            player->unk_070 = DEG_TO_RAD(sp120);
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

void func_play_800AB2AC(void) {
    u8* ptr = (u8*) gPlayer;
    u32 i;

    for (i = 0; i < gCamCount * sizeof(Player); i++, ptr++) {
        *ptr = 0;
    }
}

void func_play_800AB304(Player* player) {
    u8* ptr = (u8*) player;
    u32 i;

    for (i = 0; i < sizeof(Player); i++, ptr++) {
        *ptr = 0;
    }
}

void func_play_800AB334(void) {
    Vtx* mesh;
    u8* ptr;
    s32 i;
    f32* fptr;

    switch (gCurrentLevel) {
        case LEVEL_TRAINING:
            Audio_SetAudioSpec(0, 28);
            D_ctx_8017796C = -1;
            break;
        case LEVEL_VENOM_1:
            Audio_SetAudioSpec(0, 6);
            break;
        case LEVEL_VENOM_2:
            Audio_SetAudioSpec(0, 6);
            break;
        case LEVEL_VENOM_ANDROSS:
            Audio_SetAudioSpec(0, 15);
            Audio_SetBaseSfxReverb(0);
            D_ctx_8017796C = -1;
            break;
    }
    D_ctx_80178294 = 0;
    switch (gCurrentLevel) {
        case LEVEL_SECTOR_Z:
            gGreatFoxIntact = true;
            break;
        case LEVEL_METEO:
        case LEVEL_SECTOR_X:
            if (gLevelStage == 1) {
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
            D_ctx_80177A98 = 0;
            D_ctx_80177AB0 = 6;
            D_Andross_801A7F58 = D_Andross_801A7F60 = D_Andross_801A7F68 = D_Andross_801A7F70 = D_Andross_801A7F78 =
                0.0f;
            break;
        case LEVEL_AQUAS:
            D_80137E78 = 3;
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
            MEM_ARRAY_ALLOCATE(D_ctx_801782C4, 200);
            ptr = (u8*) D_ctx_801782C4;
            for (i = 0; i < 200 * sizeof(*D_ctx_801782C4); i++, ptr++) {
                *ptr = 0;
            }
            D_ctx_801784A4 = 0;
            /* fallthrough */
        case LEVEL_SOLAR:
            D_ctx_80178294 = 1;
            gGroundLevel = -20000.0f;
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

void func_play_800AB964(void) {
    s32 i;
    s32 j;

    D_versus_80178754 = 0;
    for (i = 0; i < 4; i++) {
        D_ctx_80177DB8[i] = 0;
        for (j = 0; j < 10; j++) {
            D_ctx_80177DD0[i][j] = 0;
        }
        gLaserStrength[i] = LASERS_SINGLE;
        gBombCount[i] = 0;
    }
    D_ctx_80177E7C = D_ctx_80177E74 = 0;
}

void func_play_800ABA08(void) {
    s32 i;

    func_play_800AB964();
    for (i = 0; i < 4; i++) {
        gPlayerNum = i;
        func_play_800AB304(&gPlayer[i]);
        func_play_800B0F50(&gPlayer[i]);
        func_play_800B44C4(&gPlayer[i]);
        func_play_800B7184(&gPlayer[i], 1);
    }
    func_play_800A6148();
}

void Play_Init(void) {
    s32 i;

    D_play_80161A54 = 40.0f;
    for (i = 0; i < 4; i++) {
        gControllerRumble[i] = 0;
    }

    if (gExpertMode) {
        gEnemyShotSpeed = 200;
    } else {
        gEnemyShotSpeed = 100;
    }
    gPauseEnabled = 0;
    D_80137E78 = 2;
    D_ctx_80177C70 = 0;
    D_display_800CA234 = NULL;
    D_display_Timer_800CA238 = 0;
    Audio_KillSfxById(0x11403076);
    Audio_KillSfxById(0x49000014);
    Memory_FreeAll();
    D_ctx_80177C78 = D_ctx_80177C8C = gShowBossHealth = gStarWolfMsgTimer = gAllRangeWingRepairTimer =
        gAllRangeWingRepairSent = 0;
    D_display_800CA220 = 0;
    D_ctx_80177830 = 0;
    if (gCurrentLevel != LEVEL_VERSUS) {
        gOverlayStage = 0;
    }
    D_game_80161A2C = 1;
    D_ctx_80177A98 = D_ctx_80177AB0 = 1;
    D_ctx_80177AC8 = D_800D2F54 = 0;
    D_display_800CA230 = D_800D2F58 = 0.0f;
    gLevelMode = LEVELMODE_ON_RAILS;
    D_ctx_80177CE8 = D_bg_8015F968 = 0.0f;
    D_hud_800D1970 = gVersusMode = D_ctx_80178300 = gChangeTo360 = 0;
    if (gCurrentLevel >= LEVEL_FORTUNA) {
        gLevelMode = LEVELMODE_ALL_RANGE;
        if (gCurrentLevel == LEVEL_VERSUS) {
            gVersusMode = true;
            func_play_800AB964();
        }
    }
    if ((gCurrentLevel == LEVEL_VENOM_ANDROSS) && (gLevelStage == 1)) {
        gLevelMode = LEVELMODE_ALL_RANGE;
    }
    D_ctx_80177E7C = 0;
    func_play_800A594C();
    gDropHitCountItem = D_ctx_8017796C = D_Timer_80177B44 = D_ctx_80177B4C = gAllRangeEventTimer = gAllRangeFrameCount =
        gBossActive = gGameFrameCount = gCameraShake = D_ctx_801782FC = gBossFrameCount = gCallTimer =
            gAllRangeSupplyTimer = gNextPlanetPath = 0;

    if (gCurrentLevel == LEVEL_SECTOR_X) {
        gNextPlanetPath = 1;
    }
    D_ctx_80177CC0 = -25000.0f;
    D_ctx_80177950 = 1.0f;
    if ((gCurrentLevel == LEVEL_VENOM_2) && (gLevelStage == 2)) {
        gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
    } else {
        gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
    }
    gScreenFlashTimer = D_ctx_80178360 = D_ctx_80178364 = D_ctx_80178368 = D_hud_80161704 = D_hud_80161708 =
        gFillScreenAlpha = D_ctx_80177C50 = gShowAllRangeCountdown = D_ctx_80177B6C = 0;

    gCsFrameCount = 0;
    gFillScreenAlpha = gFillScreenAlphaTarget = 255;

    gFillScreenAlphaStep = 16;
    D_ctx_8017836C = 0.0f;
    D_bg_8015F960 = 0.0f;
    gGroundLevel = 0.0f;
    D_ctx_80178414 = D_ctx_80178420 = D_ctx_80178424 = D_ctx_80178428 = D_ctx_8017842C = D_ctx_80178430 = 0.0f;

    if ((gLevelType == LEVELTYPE_SPACE) || (gCurrentLevel == LEVEL_TRAINING)) {
        func_play_800A5EBC();
        if (gCurrentLevel != LEVEL_TRAINING) {
            D_ctx_80177A98 = 0;
        }
    } else {
        D_ctx_80178410 = 0;
    }
    gFogAlpha = 255;
    D_ctx_801784E8 = 5.0f;
    D_ctx_80178510 = 5.0f;
    D_ctx_80178538 = 5.0f;
    func_play_800A6148();
    D_ctx_801782C8 = 0;
    if (gCurrentLevel == LEVEL_TITANIA) {
        Ground_801B5110(0.0f, 0.0f, 200.0f);
    }
    if (gCurrentLevel == LEVEL_AQUAS) {
        D_ctx_80177CC0 = 1000.0f;
    }
    D_ctx_80178488 = false;
    gCamCount = 1;
    if (gCurrentLevel == LEVEL_VERSUS) {
        gCamCount = 4;
    }
    for (i = TEAM_ID_FALCO; i < TEAM_ID_MAX; i++) {
        gTeamShields[i] = gSavedTeamShields[i];
    }
    MEM_ARRAY_ALLOCATE(gPlayer, gCamCount);
    func_play_800AB2AC();
    for (i = 0; i < gCamCount; i++) {
        gPlayer[i].state_1C8 = PLAYERSTATE_1C8_1;
        gPlayerFillScreenAlphas[i] = D_ctx_801783C0[i] = 0;
        D_Timer_80177BD0[i] = 0;
        D_ctx_80177C30[i] = 0;
    }
    if (gLevelMode == LEVELMODE_ALL_RANGE) {
        MEM_ARRAY_ALLOCATE(gObjects58, 200);
        for (i = 0; i < 200; i++) {
            gObjects58[i].obj.status = OBJ_FREE;
        }
        switch (gCurrentLevel) {
            case LEVEL_SECTOR_Z:
                if (D_ctx_8017782C == 0) {
                    SectorZ_8019EA68();
                    func_360_8002F180();
                }
                break;
            case LEVEL_FORTUNA:
                Fortuna_8018BA2C();
                func_360_8002F180();
                break;
            case LEVEL_KATINA:
                Katina_80198930();
                if (D_ctx_8017782C == 0) {
                    func_360_8002F180();
                }
                break;
            case LEVEL_BOLSE:
                if (D_ctx_8017782C == 0) {
                    Bolse_80191ED8();
                    func_360_8002F180();
                }
                break;
            case LEVEL_VENOM_2:
                Venom2_80196968();
                if (gLevelStage == 0) {
                    func_360_8002F180();
                }
                break;
            case LEVEL_VENOM_ANDROSS:
                if (gLevelStage == 1) {
                    if (gAllRangeCheckpoint == 0) {
                        Andross_801878A8();
                    } else {
                        Andross_801961AC();
                    }
                }
                break;
            case LEVEL_VERSUS:
                func_play_800A4F7C();
                D_ctx_8017796C = -1;
                break;
        }
    }
    func_play_800AB334();
}

void func_play_800AC290(Player* player, PlayerShot* shot, f32 arg2, f32 arg3, PlayerShotId shotId, f32 arg5) {
    Vec3f sp44;
    Vec3f sp38;
    Vec3f sp2C;

    PlayerShot_Initialize(shot);
    Matrix_RotateY(gCalcMatrix, (player->unk_114 + player->unk_0E8 + 180.0f) * M_DTOR, 0);
    Matrix_RotateX(gCalcMatrix, -((player->unk_120 + player->unk_0E4 + player->unk_4D8) * M_DTOR), 1);
    Matrix_RotateZ(gCalcMatrix, -((player->unk_0F8 + player->unk_0F0) * M_DTOR), 1);
    Matrix_Translate(gCalcMatrix, player->unk_084, player->unk_080, 0.0f, 1);
    if (gVersusMode && (shotId <= PLAYERSHOT_1)) {
        arg5 *= 0.5f;
    }
    sp44.x = 0.0f;
    sp44.y = 0.0f;
    sp44.z = arg5;
    Matrix_MultVec3f(gCalcMatrix, &sp44, &sp38);
    sp44.x = arg2;
    sp44.y = -5.0f + arg3;
    sp44.z = 0.0f;
    Matrix_MultVec3f(gCalcMatrix, &sp44, &sp2C);
    shot->obj.status = 1;
    shot->vel.x = sp38.x;
    shot->vel.y = sp38.y;
    shot->vel.z = sp38.z;
    shot->unk_60 = 0;
    shot->obj.id = shotId;

    if (!gVersusMode) {
        shot->unk_64 = 35;
    } else {
        shot->unk_64 = 37;
    }
    if (shot->obj.id == PLAYERSHOT_4) {
        shot->obj.pos.x = player->pos.x + sp2C.x;
        shot->obj.pos.y = player->pos.y + sp2C.y;
        shot->obj.pos.z = player->unk_138 + sp2C.z;
        shot->unk_64 = 38;
    } else {
        shot->obj.pos.x = player->pos.x + sp2C.x + (sp38.x * 1.2);
        shot->obj.pos.y = player->pos.y + sp2C.y + (sp38.y * 1.2);
        shot->obj.pos.z = player->unk_138 + sp2C.z + (sp38.z * 1.2f);
    }
    shot->obj.rot.x = player->unk_120 + player->unk_0E4 + player->unk_4D8;
    shot->obj.rot.y = player->unk_0E8 + player->unk_114;
    shot->obj.rot.z = player->unk_0F8;
    if (shotId == PLAYERSHOT_8) {
        if (gCurrentLevel == LEVEL_AQUAS) {
            shot->unk_58 = RAND_INT(360.0f);
            shot->unk_60 = RAND_INT(360.0f);
            shot->unk_2C = player->unk_0E4 + player->unk_4D8;
            shot->unk_30 = player->unk_0E8;
            shot->unk_34 = player->unk_0F8;
            shot->unk_5C = D_ctx_80178494;
        } else {
            shot->unk_30 = player->unk_0E8 + player->unk_114;
            shot->unk_2C = player->unk_0E4 + player->unk_4D8;
            if (arg5 <= 65.0f) {
                shot->unk_5C = 1;
            }
            shot->unk_64 = 30;
        }
    }
    shot->playerNum = player->num;
}

void func_play_800AC650(Player* player, PlayerShot* shot, PlayerShotId shotId, f32 arg3) {
    Vec3f sp54;
    Vec3f sp48;
    Vec3f sp3C;

    PlayerShot_Initialize(shot);
    Matrix_RotateX(gCalcMatrix, player->unk_0E4 * M_DTOR, 0);
    Matrix_RotateZ(gCalcMatrix, (player->unk_0EC + player->unk_0F0) * M_DTOR, 1);
    Matrix_RotateY(gCalcMatrix, player->unk_114 * M_DTOR, 1);
    Matrix_RotateY(gCalcMatrix, (player->unk_0E8 + 180.0f) * M_DTOR, 1);
    Matrix_RotateZ(gCalcMatrix, (-player->unk_12C - player->unk_130) * M_DTOR, 1);
    Matrix_RotateY(gCalcMatrix, -player->unk_180 * M_DTOR, 1);
    Matrix_RotateX(gCalcMatrix, player->unk_17C * M_DTOR, 1);
    sp54.x = 0;
    sp54.y = 0;
    sp54.z = arg3;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp54, &sp48);
    Matrix_Translate(gCalcMatrix, 0.0f, player->unk_18C + 30.0f, 0, 0);
    Matrix_RotateX(gCalcMatrix, player->unk_0E4 * M_DTOR, 1);
    Matrix_RotateZ(gCalcMatrix, (player->unk_0EC + player->unk_0F0) * M_DTOR, 1);
    Matrix_RotateY(gCalcMatrix, player->unk_114 * M_DTOR, 1);
    Matrix_RotateY(gCalcMatrix, (player->unk_0E8 + 180.0f) * M_DTOR, 1);
    Matrix_RotateZ(gCalcMatrix, (-player->unk_12C - player->unk_130) * M_DTOR, 1);
    Matrix_Translate(gCalcMatrix, 0.0f, -30.0f, 0, 1);
    Matrix_Translate(gCalcMatrix, player->unk_084, player->unk_080, 0.0f, 1);
    Matrix_Translate(gCalcMatrix, 0.0f, 51.0f, -4.0f, 1);
    Matrix_RotateY(gCalcMatrix, -player->unk_180 * M_DTOR, 1);
    Matrix_RotateX(gCalcMatrix, player->unk_17C * M_DTOR, 1);
    sp54.x = 0;
    sp54.y = 7;
    sp54.z = 0;
    Matrix_MultVec3f(gCalcMatrix, &sp54, &sp3C);
    shot->vel.x = sp48.x;
    shot->vel.y = sp48.y;
    shot->vel.z = sp48.z;
    shot->obj.pos.x = player->pos.x + sp3C.x;
    shot->obj.pos.y = player->pos.y + sp3C.y;
    shot->obj.pos.z = player->unk_138 + sp3C.z;
    shot->obj.status = 1;
    shot->unk_2C = -player->unk_17C;
    shot->unk_30 = -player->unk_180;
    shot->unk_34 = player->unk_12C;
    shot->obj.rot.x = player->unk_0E4 + player->unk_120;
    shot->obj.rot.y = player->unk_0E8 + player->unk_114;
    shot->obj.rot.z = player->unk_0EC;
    shot->unk_64 = 40;
    shot->obj.id = shotId;

    shot->playerNum = player->num;
    if (shotId == PLAYERSHOT_8) {
        if (arg3 <= 65.0f) {
            shot->unk_5C = 1;
        }
        shot->unk_64 = 30;
        shot->unk_30 = player->unk_0E8 + player->unk_114;
    }
}

void func_play_800ACA40(Player* player) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gPlayerShots) - 1; i++) {
        if (gPlayerShots[i].obj.status == 0) {
            func_play_800AC650(player, &gPlayerShots[i], PLAYERSHOT_5, 100.0f);
            func_play_800A5FA0(player->sfxSource, 0x09000014, player->num);
            player->unk_1A0 = 2;
            break;
        }
    }
}

void func_play_800ACABC(Player* player) {
    s32 i;
    LaserStrength laser = gLaserStrength[gPlayerNum];

    if (player->wings.unk_14 > -8.0f) {
        laser = LASERS_SINGLE;
    }
    switch (laser) {
        case LASERS_SINGLE:
            for (i = 0; i < ARRAY_COUNT(gPlayerShots) - 1; i++) {
                if (gPlayerShots[i].obj.status == 0) {
                    func_play_800AC290(player, &gPlayerShots[i], 0.0f, 0.0f, PLAYERSHOT_0, 400.0f / 3.0f);
                    func_play_800A5FA0(player->sfxSource, 0x09400000, player->num);
                    D_ctx_80177AA0[player->num] = 0.5f;
                    break;
                }
            }
            break;
        case LASERS_TWIN:
        case LASERS_HYPER:
            for (i = 0; i < ARRAY_COUNT(gPlayerShots) - 1; i++) {
                if (gPlayerShots[i].obj.status == 0) {
                    func_play_800AC290(player, &gPlayerShots[i], 0.0f, -10.0f, PLAYERSHOT_1, 400.0f / 3.0f);
                    if (laser == LASERS_TWIN) {
                        func_play_800A5FA0(player->sfxSource, 0x0940800C, player->num);
                        D_ctx_80177AA0[player->num] = 0.5f;
                    } else {
                        func_play_800A5FA0(player->sfxSource, 0x0940802B, player->num);
                        D_ctx_80177AA0[player->num] = 0.75f;
                    }
                    break;
                }
            }
            break;
    }
}

void func_play_800ACC7C(Player* player) {
    if ((gBombCount[player->num] != 0) && (gBombButton[player->num] & gInputPress->button) &&
        (gPlayerShots[ARRAY_COUNT(gPlayerShots) - 1].obj.status == OBJ_FREE)) {
        if (gVersusMode) {
            gBombCount[player->num] = 0;
        } else {
            gBombCount[player->num]--;
        }
        if (player->form == FORM_ARWING) {
            func_play_800AC290(player, &gPlayerShots[ARRAY_COUNT(gPlayerShots) - 1], 0.0f, 0.0f, PLAYERSHOT_3, 180.0f);
        } else if (player->form == FORM_LANDMASTER) {
            func_play_800AC650(player, &gPlayerShots[ARRAY_COUNT(gPlayerShots) - 1], PLAYERSHOT_3, 180.0f);
        } else {
            func_play_800ACDC0(player, &gPlayerShots[ARRAY_COUNT(gPlayerShots) - 1], PLAYERSHOT_3);
        }
        gPlayerShots[ARRAY_COUNT(gPlayerShots) - 1].unk_48 = 30.0f;
        gPlayerShots[ARRAY_COUNT(gPlayerShots) - 1].unk_60 = 0;
        func_8001CB80(player->num, 1);
        func_8001CCDC(player->num, gPlayerShots[ARRAY_COUNT(gPlayerShots) - 1].sfxSource);
    }
}

void func_play_800ACDC0(Player* player, PlayerShot* shot, PlayerShotId shotId) {
    Vec3f sp5C;
    Vec3f sp50;
    Vec3f sp44;

    PlayerShot_Initialize(shot);
    Matrix_RotateY(gCalcMatrix, (player->unk_114 + player->unk_0E8 + player->unk_134 + 180.0f) * M_DTOR, 0);
    Matrix_RotateX(gCalcMatrix, -((player->unk_0E4 + player->unk_134) * M_DTOR), 1);
    Matrix_RotateZ(gCalcMatrix, -((player->unk_0F8 + player->unk_0F0 + player->unk_134) * M_DTOR), 1);
    Matrix_RotateX(gCalcMatrix, player->unk_154 * M_DTOR, 1);
    sp5C.x = 0.0f;
    sp5C.y = 0.0f;
    if (shotId == PLAYERSHOT_3) {
        sp5C.z = 100.0f;
    } else {
        sp5C.z = 150.0f;
    }
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp5C, &sp50);
    Matrix_RotateY(gCalcMatrix, (player->unk_114 + player->unk_0E8 + player->unk_134 + 180.0f) * M_DTOR, 0);
    Matrix_RotateX(gCalcMatrix, -((player->unk_0E4 + player->unk_134) * M_DTOR), 1);
    Matrix_RotateZ(gCalcMatrix, -((player->unk_0F8 + player->unk_0F0 + player->unk_134) * M_DTOR), 1);
    Matrix_Translate(gCalcMatrix, 0.0f, player->unk_080, 0, 1);
    Matrix_Translate(gCalcMatrix, -10.0f, 25.0f, 0.0f, 1);
    Matrix_RotateX(gCalcMatrix, player->unk_154 * M_DTOR, 1);
    sp5C.x = 0.0f;
    sp5C.y = 0.0f;
    sp5C.z = 0;
    Matrix_MultVec3f(gCalcMatrix, &sp5C, &sp44);
    shot->vel.x = sp50.x;
    shot->vel.y = sp50.y;
    shot->vel.z = sp50.z;
    shot->obj.pos.x = player->pos.x + sp44.x;
    shot->obj.pos.y = player->pos.y + sp44.y;
    shot->obj.pos.z = player->unk_138 + sp44.z;

    shot->unk_44 = 1.0f;

    shot->obj.status = 1;
    shot->obj.id = shotId;
    shot->unk_64 = 30;
    shot->unk_58 = 1;

    shot->playerNum = player->num;
}

void func_play_800AD094(Player* player) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gPlayerShots); i++) {
        if (gPlayerShots[i].obj.status == 0) {
            func_play_800ACDC0(player, &gPlayerShots[i], PLAYERSHOT_6);
            func_play_800A5FA0(player->sfxSource, 0x09000014, player->num);
            player->timer_1F8 = 2;
            player->unk_180 = 10.0f;
            break;
        }
    }
}

bool func_play_800AD118(s32 playerNum) {
    Actor* actor;
    s32 i;

    for (i = 0, actor = gActors; i < ARRAY_COUNT(gActors); i++, actor++) {
        if ((actor->obj.status == OBJ_ACTIVE) && (actor->timer_0CA[playerNum] != 0)) {
            return false;
        }
    }
    if (gVersusMode) {
        for (i = 0; i < gCamCount; i++) {
            if (((gPlayer[playerNum].state_1C8 == PLAYERSTATE_1C8_3) ||
                 (gPlayer[playerNum].state_1C8 == PLAYERSTATE_1C8_5)) &&
                (D_ctx_80177B00[i][playerNum] != 0)) {
                return false;
            }
        }
    }
    return true;
}

bool func_play_800AD1F4(Player* player) {
    bool var_a2;
    s32 i;

    if (gInputHold->button & A_BUTTON) {
        gChargeTimers[player->num]++;
        if (gChargeTimers[player->num] > 21) {
            gChargeTimers[player->num] = 21;
        }
        if (gChargeTimers[player->num] == 20) {
            func_enmy_80060F30(player->sfxSource, 0x0900302D, player->num);
        }
        if ((!(gInputHold->button & R_TRIG) || !(gInputHold->button & Z_TRIG) || (player->form != FORM_ARWING) ||
             (player->state_1C8 != PLAYERSTATE_1C8_3)) &&
            ((gGameFrameCount % 4) == 0) && func_play_800AD118(player->num)) {
            if (gChargeTimers[player->num] > 20) {
                for (i = 0; i < 13; i++) {
                    if (gPlayerShots[i].obj.status == 0) {
                        if (player->form == FORM_ARWING) {
                            func_play_800AC290(player, &gPlayerShots[i], 0.0f, 0.0f, PLAYERSHOT_4, 400.0f);
                        } else {
                            func_play_800AC650(player, &gPlayerShots[i], PLAYERSHOT_4, 400.0f);
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
            if ((gActors[i].obj.status == OBJ_ACTIVE) && (gActors[i].timer_0CA[player->num] != 0)) {
                if ((gPlayerShots[14 - player->num].obj.status == 0) ||
                    (gPlayerShots[14 - player->num].obj.id != PLAYERSHOT_8) ||
                    ((gPlayerShots[14 - player->num].obj.id == PLAYERSHOT_8) &&
                     (gPlayerShots[14 - player->num].unk_60 != 0))) {
                    if (player->form == FORM_ARWING) {
                        func_play_800AC290(player, &gPlayerShots[14 - player->num], 0.0f, 0.0f, PLAYERSHOT_8, 70.0f);
                    } else {
                        func_play_800AC650(player, &gPlayerShots[14 - player->num], PLAYERSHOT_8, 70.0f);
                    }
                    func_enmy_80060F30(player->sfxSource, 0x09007029, player->num);
                    D_Timer_80177BD0[player->num] = 5;
                    return true;
                }
                break;
            }
        }
        if (gChargeTimers[player->num] > 10) {
            if ((gPlayerShots[14 - player->num].obj.status == 0) ||
                (gPlayerShots[14 - player->num].obj.id != PLAYERSHOT_8) ||
                ((gPlayerShots[14 - player->num].obj.id == PLAYERSHOT_8) &&
                 (gPlayerShots[14 - player->num].unk_44 > 1.0f))) {
                if (player->form == FORM_ARWING) {
                    func_play_800AC290(player, &gPlayerShots[14 - player->num], 0.0f, 0.0f, PLAYERSHOT_8, 70.0f);
                } else {
                    func_play_800AC650(player, &gPlayerShots[14 - player->num], PLAYERSHOT_8, 70.0f);
                }
                func_enmy_80060F30(player->sfxSource, 0x09007029, player->num);
                gChargeTimers[player->num] = 0;
                D_Timer_80177BD0[player->num] = 5;
                return true;
            }
        }
        gChargeTimers[player->num] = 0;
    }
    if (gInputPress->button & B_BUTTON) {
        var_a2 = false;
        for (i = 0; i < ARRAY_COUNT(gActors); i++) {
            if ((gActors[i].obj.status == OBJ_ACTIVE) && (gActors[i].timer_0CA[player->num] != 0)) {
                var_a2 = true;
                break;
            }
        }
        for (i = 0; i < gCamCount; i++) {
            if (D_ctx_80177B00[i][player->num] != 0) {
                var_a2 = true;
                break;
            }
        }
        if (var_a2 != 0) {
            if ((gBombCount[player->num] != 0) && (gPlayerShots[ARRAY_COUNT(gPlayerShots) - 1].obj.status == 0)) {
                gBombCount[player->num]--;
                if (player->form == FORM_ARWING) {
                    func_play_800AC290(player, &gPlayerShots[ARRAY_COUNT(gPlayerShots) - 1], 0.0f, 0.0f, PLAYERSHOT_8,
                                       60.0f);
                } else {
                    func_play_800AC650(player, &gPlayerShots[ARRAY_COUNT(gPlayerShots) - 1], PLAYERSHOT_8, 60.0f);
                }
                gPlayerShots[ARRAY_COUNT(gPlayerShots) - 1].unk_48 = 30.0f;
                gPlayerShots[ARRAY_COUNT(gPlayerShots) - 1].unk_60 = 0;
                func_8001CB80(player->num, 1);
                func_8001CCDC(player->num, gPlayerShots[ARRAY_COUNT(gPlayerShots) - 1].sfxSource);
                return true;
            }
        }
    }
    return false;
}

void func_play_800AD7F0(Player* player) {
    switch (player->form) {
        case FORM_ARWING:
            if ((player->wings.rightState <= WINGSTATE_BROKEN) || (player->wings.leftState <= WINGSTATE_BROKEN)) {
                gLaserStrength[player->num] = LASERS_SINGLE;
            }
            if (!func_play_800AD1F4(player)) {
                if (gLaserStrength[gPlayerNum] > LASERS_SINGLE) {
                    Math_SmoothStepToF(&player->wings.unk_14, -10.0f, 1.0f, 0.5f, 0.0f);
                } else {
                    Math_SmoothStepToF(&player->wings.unk_14, 0.0f, 1.0f, 0.5f, 0.0f);
                }
                if (gShootButton[player->num] & gInputPress->button) {
                    func_play_800ACABC(player);
                    player->timer_244 = 8;
                }
                if (player->timer_244 != 0) {
                    player->timer_244--;
                    if ((gShootButton[player->num] & gInputHold->button) && ((player->timer_244 & 3) == 0)) {
                        func_play_800ACABC(player);
                    }
                }
                func_play_800ACC7C(player);
            }
            break;
        case FORM_LANDMASTER:
            if (!func_play_800AD1F4(player)) {
                if (gShootButton[player->num] & gInputPress->button) {
                    func_play_800ACA40(player);
                }
                func_play_800ACC7C(player);
            }
            break;
        case FORM_ON_FOOT:
            if (gInputPress->button & A_BUTTON) {
                player->timer_244 = 0;
            }
            if (gInputHold->button & A_BUTTON) {
                if (player->timer_244 == 0) {
                    func_play_800AD094(player);
                }
                player->timer_244++;
                if (player->timer_244 > 4) {
                    player->timer_244 = 0;
                }
            }
            func_play_800ACC7C(player);
            break;
    }
}

void func_play_800ADA28(Player* player) {
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
        if (player->unk_12C < 70.0f) {
            Math_SmoothStepToF(&player->wings.unk_04, -70.0f, 0.3f, 100.0f, 0.0f);
            Math_SmoothStepToF(&player->wings.unk_08, -70.0f, 0.3f, 100.0f, 0.f);
            Math_SmoothStepToF(&player->wings.unk_0C, 70.0f, 0.3f, 100.0f, 0.f);
            Math_SmoothStepToF(&player->wings.unk_10, 70.0f, 0.3f, 100.0f, 0.f);
            if (player->pos.y < (gGroundLevel + 70.0f)) {
                player->pos.y += 6.0f;
            }
        }
    }

    if ((gInputHold->button & R_TRIG) && !(gInputHold->button & Z_TRIG)) {
        sp3C = -90.0f;
        sp38 = 0.2f;
        if (player->unk_12C > -70.0f) {
            Math_SmoothStepToF(&player->wings.unk_04, 70.0f, 0.3f, 100.0f, 0.0f);
            Math_SmoothStepToF(&player->wings.unk_08, 70.0f, 0.3f, 100.0f, 0.0f);
            Math_SmoothStepToF(&player->wings.unk_0C, -70.0f, 0.3f, 100.0f, 0.0f);
            Math_SmoothStepToF(&player->wings.unk_10, -70.0f, 0.3f, 100.0f, 0.0f);
            if (player->pos.y < (gGroundLevel + 70.0f)) {
                player->pos.y += 6.0f;
            }
        }
    }
    Math_SmoothStepToF(&player->unk_12C, sp3C, sp38, 10.0f, 0.f);
    if (gInputPress->button & Z_TRIG) {
        player->sfx.bank = 1;
        if (player->timer_1E0 != 0) {
            player->unk_1DC = 1;
            player->timer_1E8 = 10;
            player->unk_1EC = player->unk_1F0 = 30;
            player->sfx.roll = 1;
        } else {
            player->timer_1E0 = 10;
        }
    }
    if (gInputPress->button & R_TRIG) {
        player->sfx.bank = 1;
        if (player->timer_1E4 != 0) {
            player->unk_1DC = 1;
            player->timer_1E8 = 10;
            player->unk_1EC = player->unk_1F0 = -30;
            player->sfx.roll = 1;
        } else {
            player->timer_1E4 = 10;
        }
    }
}

void func_play_800ADD98(Player* player) {
    Math_SmoothStepToF(&player->unk_170, 0.0f, 1.0f, 0.2f, 0.0f);
    Math_SmoothStepToF(&player->unk_16C, 0.0f, 1.0f, 0.2f, 0.0f);
    if (gInputPress->button & Z_TRIG) {
        if ((player->timer_1E0 != 0) && (player->unk_12C > 0.0f) && (player->unk_2BC < 10.0f)) {
            player->unk_1DC = 1;
            player->timer_1E8 = 15;
            player->unk_1EC = player->unk_1F0 = 20;
        } else {
            player->timer_1E0 = 10;
        }
    }
    if (gInputPress->button & R_TRIG) {
        if ((player->timer_1E4 != 0) && (player->unk_12C < 0.0f) && (player->unk_2BC < 10.0f)) {
            player->unk_1DC = 1;
            player->timer_1E8 = 15;
            player->unk_1EC = player->unk_1F0 = -20;
        } else {
            player->timer_1E4 = 10;
        }
    }
    player->unk_18C = fabsf(SIN_DEG(player->unk_12C) * 25.0f);
    player->unk_18C += fabsf(SIN_DEG(player->unk_130) * 20.0f);
}

void func_play_800ADF58(Player* player) {
    f32 temp_fv0;
    f32 temp_fv0_2;
    s32 temp_v0;

    player->unk_140 = -player->vel.z;
    player->unk_144 += -player->vel.z;
    D_ctx_80177D08 = -player->vel.z;
    D_ctx_80177D20 = player->unk_144;
    D_ctx_80177CE8 += player->unk_140;
    if (D_ctx_801784AC == 4) {
        D_ctx_80177CC8 = player->unk_140;
    }
    if ((gBossActive == 0) && (player->unk_144 > 500000.0f)) {
        player->unk_144 = 0.0f;
        player->pos.z = 0.0f;
        D_ctx_80177DC8 = 0;
        func_play_800A6148();
    }
    player->unk_138 = player->pos.z + player->unk_08C;
    player->unk_0F8 = player->unk_0EC + player->unk_12C + player->unk_130;

    while (1) {
        if (player->unk_0F8 > 360.0f) {
            player->unk_0F8 -= 360.0f;
        } else {
            break;
        }
    }
    while (1) {
        if (player->unk_0F8 < -360.0f) {
            player->unk_0F8 += 360.0f;
        } else {
            break;
        }
    }
    if (gCurrentLevel == LEVEL_UNK_15) {
        Math_SmoothStepToF(&player->unk_0B4, 10.0f, 0.1f, 0.5f, 0.0001f);
        player->pos.x += Math_SmoothStepToF(&player->unk_0AC, player->unk_0B8, 0.1f, player->unk_0B4, 0.0001f);
        player->pos.y += Math_SmoothStepToF(&player->unk_0B0, player->unk_0BC, 0.1f, player->unk_0B4, 0.0001f);
    } else {
        Math_SmoothStepToF(&player->unk_0B4, D_ctx_80177D08 * 0.54f, 0.1f, 2.0f, 0.0001f);
        D_ctx_801779E4 = Math_SmoothStepToF(&player->unk_0AC, player->unk_0B8, 0.1f, player->unk_0B4, 0.0001f);
        D_ctx_801779F4 = Math_SmoothStepToF(&player->unk_0B0, player->unk_0BC, 0.1f, player->unk_0B4, 0.0001f);
    }
    if (player->timer_210 != 0) {
        player->timer_210--;
        Math_SmoothStepToF(&player->unk_114, player->unk_118, 0.03f, 0.5f, 0.0001f);
        Math_SmoothStepToF(&player->unk_120, player->unk_124, 0.03f, 0.5f, 0.0001f);
    } else {
        Math_SmoothStepToF(&player->unk_114, 0.0f, 0.03f, 0.5f, 0.0001f);
        Math_SmoothStepToF(&player->unk_120, 0.0f, 0.03f, 0.5f, 0.0001f);
    }
}

void func_play_800AE278(Player* player) {
    f32 var_fv1;
    bool var_v0 = false;

    if (gCamCount != 1) {
        if (player->pos.x > 12000.0f) {
            var_v0 = true;
            player->pos.x -= 24000.0f;
            player->camEye.x -= 24000.0f;
            player->camAt.x -= 24000.0f;
        }
        if (player->pos.x < -12000.0f) {
            var_v0 = true;
            player->pos.x += 24000.0f;
            player->camEye.x += 24000.0f;
            player->camAt.x += 24000.0f;
        }

        if (player->pos.z > 12000.0f) {
            var_v0 = true;
            player->pos.z -= 24000.0f;
            player->camEye.z -= 24000.0f;
            player->camAt.z -= 24000.0f;
        }
        if (player->pos.z < -12000.0f) {
            var_v0 = true;
            player->pos.z += 24000.0f;
            player->camEye.z += 24000.0f;
            player->camAt.z += 24000.0f;
        }
        if (var_v0) {
            D_ctx_80177B00[player->num][0] = D_ctx_80177B00[player->num][1] = D_ctx_80177B00[player->num][2] =
                D_ctx_80177B00[player->num][3] = 0;
        }
    } else {
        var_fv1 = 12500.0f;
        if (gCurrentLevel == LEVEL_CORNERIA) {
            var_fv1 = 8000.0f;
        } else if (gCurrentLevel == LEVEL_BOLSE) {
            var_fv1 = 10000.0f;
        } else if (gCurrentLevel == LEVEL_SECTOR_Z) {
            var_fv1 = 20000.0f;
        } else if ((gCurrentLevel == LEVEL_VENOM_ANDROSS) && (D_ctx_80177AB0 >= 4)) {
            var_fv1 = 100000.0f;
        }
        if ((var_fv1 < fabsf(player->pos.x)) || (var_fv1 < fabsf(player->pos.z))) {
            player->state_1C8 = PLAYERSTATE_1C8_5;
            player->unk_19C = 0;
            player->unk_1D0 = 0;
            player->unk_000 = 0.0f;
            player->unk_004 = 0.0f;
        }
    }
}

void func_play_800AE4A4(Player* player) {
    f32 sp7C;
    f32 sp78;
    f32 var_fa0;
    f32 var_fa1;
    f32 var_fv0;
    f32 var_fv1;
    f32 temp;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    Vec3f sp4C;
    Vec3f sp40;

    D_ctx_80177968 = 2.3f;
    D_ctx_80177970 = 0.68f;
    sp7C = -gInputPress->stick_x;
    sp78 = gInputPress->stick_y;
    Math_SmoothStepToAngle(&player->unk_4D8, 0.0f, 0.1f, 5.0f, 0.01f);
    Matrix_RotateZ(gCalcMatrix, -player->unk_12C * M_DTOR, 0);
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
    var_fa0 = 0.1f;
    if ((player->unk_12C > 10.0f) && (sp7C > 0)) {
        D_ctx_80177968 *= 2.0f;
        var_fa0 = 0.2f;
    }
    if ((player->unk_12C < -10.0f) && (sp7C < 0)) {
        D_ctx_80177968 *= 2.0f;
        var_fa0 = 0.2f;
    }
    Math_SmoothStepToF(&player->unk_0E8, sp7C * D_ctx_80177970, var_fa0, D_ctx_80177968, 0.03f);
    var_fa0 = 0.03f;
    if ((player->unk_12C > 10.0f) && (sp7C > 0)) {
        var_fa0 = 0.05f;
    }
    if ((player->unk_12C < -10.0f) && (sp7C < 0)) {
        var_fa0 = 0.05f;
    }
    Math_SmoothStepToF(&player->unk_11C, player->unk_0E8 * var_fa0, 0.1f, 0.8f, 0.05f);
    player->unk_114 += player->unk_11C;
    if (player->unk_114 >= 360.0f) {
        player->unk_114 -= 360.0f;
    }
    if (player->unk_114 < 0.0f) {
        player->unk_114 += 360.0f;
    }
    D_ctx_80177968 = 2.3f;
    var_fa1 = 0.1f;
    temp = -sp78 * D_ctx_80177970;
    if ((temp <= 0.0f) && (player->pos.y < (gGroundLevel + 50.0f))) {
        D_ctx_80177968 *= 2.0f;
        temp = 0.0f;
        var_fa1 = 0.2f;
    }
    Math_SmoothStepToF(&player->unk_0E4, temp, var_fa1, D_ctx_80177968, 0.03f);
    var_fv1 = 1.5f;
    if (player->pos.y < (gGroundLevel + 70.0f)) {
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
    Math_SmoothStepToF(&player->unk_0EC, sp7C * 0.6f * var_fv1, 0.1f, var_fv0, 0.03f);
    player->unk_0F8 = player->unk_0EC + player->unk_12C + player->unk_130;
    Matrix_RotateY(gCalcMatrix, (player->unk_114 + player->unk_0E8 + 180.0f) * M_DTOR, 0);
    Matrix_RotateX(gCalcMatrix, -((player->unk_120 + player->unk_0E4 + player->unk_4D8) * M_DTOR), 1);
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
    sp4C.z = player->unk_0D0 + player->unk_110;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp4C, &sp40);
    player->vel.x = sp40.x;
    player->vel.z = sp40.z;
    player->vel.y = sp40.y;
    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;
    if ((player->unk_0A0 < player->pos.y) && (player->vel.y >= 0.0f)) {
        Math_SmoothStepToF(&player->pos.y, player->unk_0A0, 0.1f, fabsf(player->vel.y * 1.5f) + 5.0f, 0.0f);
    }
    if ((player->pos.y < player->unk_0A4) && (player->vel.y <= 0.0f)) {
        if (player->unk_0A4 >= 0.0f) {
            player->pos.y = player->unk_0A4;
        } else {
            Math_SmoothStepToF(&player->pos.y, player->unk_0A4, 0.1f, fabsf(player->vel.y * 1.5f) + 5.0f, 0.0f);
        }
    }
    player->pos.z += player->vel.z;
    if (player->unk_0A0 - 100.0f < player->pos.y) {
        player->flags_228 = PFLAG_228_3;
    }
    if (player->pos.y < -(player->unk_0A0 - 100.0f)) {
        player->flags_228 = PFLAG_228_2;
    }
    func_play_800AE278(player);
    player->unk_138 = player->pos.z;
    func_play_800A4460(player);
    func_play_800A46A0(player);
}

void func_play_800AECAC(Player* player) {
    f32 temp;
    f32 sp58;
    Vec3f sp4C;
    Vec3f sp40;

    sp58 = 60.0f;
    if (gVersusMode) {
        D_ctx_80177B00[player->num][0] = D_ctx_80177B00[player->num][1] = D_ctx_80177B00[player->num][2] =
            D_ctx_80177B00[player->num][3] = 0;
    }
    if (player->unk_4D8 > 240.0f) {
        sp58 = -50.0f;
    }
    Math_SmoothStepToF(&player->wings.unk_04, sp58, 0.3f, 100.0f, 0.0f);
    Math_SmoothStepToF(&player->wings.unk_08, sp58, 0.3f, 100.0f, 0.0f);
    Math_SmoothStepToF(&player->wings.unk_0C, sp58, 0.3f, 100.0f, 0.0f);
    Math_SmoothStepToF(&player->wings.unk_10, sp58, 0.3f, 100.0f, 0.0f);
    if (player->unk_4D8 < 180.0f) {
        player->pos.y += 2.0f;
    }
    player->unk_2B4 = true;
    if (gLevelMode == LEVELMODE_ON_RAILS) {
        player->unk_2BC += 2.0f;
    } else {
        player->unk_2BC += 1.0f;
    }
    if (player->unk_2BC > 90.0f) {
        player->unk_2BC = 90.0f;
    }
    player->unk_190 = 2;
    Math_SmoothStepToF(&player->unk_4D8, 360.0f, 0.1f, 5.0f, 0.001f);
    if (player->unk_4D8 > 350.0f) {
        player->unk_4DC = 0;
        if (gLevelMode != LEVELMODE_ON_RAILS) {
            player->unk_018 = 0.05f;
            player->unk_014 = 0.05f;
        } else {
            player->cockpitView = player->savedCockpitView;
            if (player->cockpitView != 0) {
                player->unk_014 = 0.0f;
            }
        }
    }
    Math_SmoothStepToF(&player->unk_0EC, 0.0f, 0.1f, 5.0f, 0.0f);
    Math_SmoothStepToF(&player->unk_0E4, 0.0f, 0.1f, 5.0f, 0.0f);
    temp = -gInputPress->stick_x * 0.68f;
    Math_SmoothStepToF(&player->unk_0E8, temp, 0.1f, 2.0f, 0.0f);
    player->unk_0F8 = player->unk_0EC + player->unk_12C + player->unk_130;
    Matrix_RotateY(gCalcMatrix, (player->unk_114 + player->unk_0E8 + 180.0f) * M_DTOR, 0);
    Matrix_RotateX(gCalcMatrix, -((player->unk_120 + player->unk_0E4 + player->unk_4D8) * M_DTOR), 1);
    sp4C.x = 0.0f;
    sp4C.y = 0.0f;
    sp4C.z = player->unk_0D0;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp4C, &sp40);
    player->vel.x = sp40.x;
    player->vel.z = sp40.z;
    player->vel.y = sp40.y;
    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;
    if (player->pos.y < player->unk_0A4 + player->unk_0B0) {
        player->pos.y = player->unk_0A4 + player->unk_0B0;
        player->vel.y = 0.0f;
    }
    player->pos.z += player->vel.z;
    player->unk_138 = player->pos.z;
    func_play_800A46A0(player);
}

void func_play_800AF07C(Player* player) {
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

    D_ctx_80177968 = 2.3f;
    D_ctx_80177970 = 0.68f;

    if ((gInputPress->stick_x != 0) || (gInputPress->stick_y != 0)) {
        D_ctx_80177970 = 0.68f; //! FAKE ?
    }

    stickX = -gInputPress->stick_x;
    stickY = +gInputPress->stick_y;

    Math_SmoothStepToAngle(&player->unk_4D8, 0.0f, 0.1f, 5.0f, 0.01f);

    if (player->cockpitView != 0) {
        Matrix_RotateZ(gCalcMatrix, player->unk_12C * M_DTOR, 0);

        sp68.z = 0.0f;
        sp68.x = stickX;
        sp68.y = stickY;

        Matrix_MultVec3f(gCalcMatrix, &sp68, &sp5C);

        stickX = sp5C.x;
        stickY = sp5C.y;
    } else {
        Matrix_RotateZ(gCalcMatrix, (-player->unk_12C) * M_DTOR, 0);

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

    if ((player->unk_12C > 10.0f) && (stickX > 0)) {
        sp84 = 0.2f;
        D_ctx_80177968 *= 2.0f;
    }
    if ((player->unk_12C < (-10.0f)) && (stickX < 0)) {
        sp84 = 0.2f;
        D_ctx_80177968 *= 2.0f;
    }
    if (player->unk_1DC != 0) {
        sp84 = 0.2f;
        D_ctx_80177968 = 6.8999996f;
    }

    Math_SmoothStepToF(&player->unk_0E8, stickX * D_ctx_80177970, sp84, D_ctx_80177968, 0.03f);

    D_ctx_80177968 = 2.3f;
    sp84 = 0.1f;
    var_fa1 = -stickY * D_ctx_80177970;

    if ((var_fa1 <= 0.0f) && (player->pos.y < (gGroundLevel + 50.0f))) {
        var_fa1 = 0.0f;
        sp84 = 0.2f;
        D_ctx_80177968 *= 2.0f;
    }

    Math_SmoothStepToF(&player->unk_0E4, var_fa1, sp84, D_ctx_80177968, 0.03f);

    var_fv1 = 1.0f;
    if (player->pos.y < (gGroundLevel + 70.0f)) {
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

    Math_SmoothStepToF(&player->unk_0EC, (stickX * 0.6f) * var_fv1, 0.1f, var_fv0, 0.03f);
    Matrix_RotateY(gCalcMatrix, (player->unk_0E8 + 180.0f) * M_DTOR, 0);
    Matrix_RotateX(gCalcMatrix, -((player->unk_0E4 + player->unk_4D8) * M_DTOR), 1);

    sp68.x = 0.0f;
    sp68.y = 0.0f;
    sp68.z = player->unk_0D0;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp68, &sp44);

    sp44.x *= 1.4f;
    sp44.y *= 1.4f;

    Matrix_RotateY(gCalcMatrix, player->unk_114 * M_DTOR, 0);
    Matrix_RotateX(gCalcMatrix, player->unk_120 * M_DTOR, 1);
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp44, &sp5C);

    sp68.x = 0.0f;
    sp68.y = 0.0f;
    sp68.z = -player->unk_110;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp68, &sp50);

    player->vel.x = (sp5C.x + sp50.x) * player->unk_150;
    player->vel.y = (sp5C.y + sp50.y) * player->unk_150;
    player->vel.z = sp5C.z + sp50.z;

    if (gCurrentLevel == LEVEL_VENOM_ANDROSS) {
        player->vel.z += D_Andross_801A7F58;
    }
    sp68.x = 0.0f;
    sp68.y = 0.0f;
    sp68.z = -player->unk_110;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp68, &sp50);

    if (player->wings.rightState <= WINGSTATE_BROKEN) {
        player->vel.x += 2.5f;
        player->vel.y -= 2.5f;
    }
    if (player->wings.leftState <= WINGSTATE_BROKEN) {
        player->vel.x -= 2.5f;
        player->vel.y -= 2.5f;
    }

    if (player->pos.x > (player->unk_0AC + (player->unk_09C - 100.0f))) {
        player->flags_228 = PFLAG_228_0;
    }
    if (player->pos.x < (player->unk_0AC - (player->unk_09C - 100.0f))) {
        player->flags_228 = PFLAG_228_1;
    }
    if (player->pos.y > (player->unk_0B0 + (player->unk_0A0 - 100.0f))) {
        player->flags_228 = PFLAG_228_3;
    }
    if (player->pos.y < (player->unk_0B0 - (player->unk_0A0 - 100.0f))) {
        player->flags_228 = PFLAG_228_2;
    }

    player->pos.x += player->vel.x;

    if (player->pos.x > (player->unk_09C + player->unk_0AC)) {
        player->pos.x = player->unk_09C + player->unk_0AC;
        player->vel.x = 0.0f;
        player->unk_0D8.x = 0.0f;
    }
    if (player->pos.x < (player->unk_0AC - player->unk_09C)) {
        player->pos.x = player->unk_0AC - player->unk_09C;
        player->vel.x = 0.0f;
        player->unk_0D8.x = 0.0f;
    }

    player->pos.y += player->vel.y;

    if (player->pos.y > (player->unk_0A0 + player->unk_0B0)) {
        player->pos.y = player->unk_0A0 + player->unk_0B0;
        player->vel.y = 0.0f;
        player->unk_0D8.y = 0.0f;
    }
    if (player->pos.y < (player->unk_0A4 + player->unk_0B0)) {
        player->pos.y = player->unk_0A4 + player->unk_0B0;
        player->vel.y = 0.0f;
        player->unk_0D8.y = 0.0f;
    }

    player->pos.z += player->vel.z;

    func_play_800A4460(player);
}

void func_play_800AF928(Player* player) {
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
    D_ctx_80177968 = 3.0f;
    D_ctx_80177970 = 0.6666f;
    sp5C = gInputPress->stick_x;
    if (sp5C == 0) {
        Math_SmoothStepToF(&player->unk_0E8, -sp5C * D_ctx_80177970, 0.1f, D_ctx_80177968 * 0.5f, 0.1f);
    } else {
        Math_SmoothStepToF(&player->unk_0E8, -sp5C * D_ctx_80177970, 0.1f, D_ctx_80177968, 0.1f);
    }
    player->unk_108 = player->unk_0E8;
    var_fa0 = 0.03f;
    var_fa1 = 1.5f;
    if ((player->unk_12C > 10.0f) && (sp5C < 0.0f)) {
        var_fa0 = 0.1f;
        var_fa1 = 4.0f;
    }
    if ((player->unk_12C < -10.0f) && (sp5C > 0.0f)) {
        var_fa0 = 0.1f;
        var_fa1 = 4.0f;
    }
    if (player->unk_1DC != 0) {
        if ((player->unk_1EC > 0) && (sp5C < 0.0f)) {
            var_fa0 = 0.2f;
            var_fa1 = 20.0f;
        }
        if ((player->unk_1EC < 0) && (sp5C > 0.0f)) {
            var_fa0 = 0.2f;
            var_fa1 = 20.0f;
        }
    }
    Math_SmoothStepToF(&player->unk_11C, player->unk_0E8 * var_fa0, 0.1f, var_fa1, 0.05f);
    player->unk_114 += player->unk_11C;
    player->unk_114 = Math_ModF(player->unk_114, 360.0f);
    Matrix_RotateX(gCalcMatrix, player->unk_104 * M_DTOR, 0);
    Matrix_RotateZ(gCalcMatrix, player->unk_10C * M_DTOR, 1);
    Matrix_RotateY(gCalcMatrix, (player->unk_114 + player->unk_0E8 + 180.0f) * M_DTOR, 1);
    sp44.x = 0.0f;
    sp44.y = 0.0f;
    sp44.z = player->unk_0D0;
    sp44.z -= fabsf((player->unk_184 * 0.4f * player->unk_0D0) / 15.0f);
    sp44.z += SIN_DEG(player->unk_000) * player->unk_110;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp44, &sp38);
    player->vel.x = sp38.x;
    player->vel.z = sp38.z;
    if (player->unk_16C > 0.2f) {
        Math_SmoothStepToF(&player->unk_184, player->unk_0D0 * 0.5f, 1.0f, 1.0f, 0);
    }
    if (player->unk_170 > 0.2f) {
        Math_SmoothStepToF(&player->unk_184, -player->unk_0D0 * 0.5f, 1.0f, 1.0f, 0);
    }
    if (!(player->unk_170 > 0.2f) && !(player->unk_16C > 0.2f) && (player->unk_1D4 != 0)) {
        Math_SmoothStepToF(&player->unk_184, 0.0f, 1.0f, 0.75f, 0.0f);
    }
    if (player->unk_1DC != 0) {
        if (player->unk_1EC < 0) {
            player->unk_184 = 15.0f;
        }
        if (player->unk_1EC > 0) {
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
    player->vel.y -= player->unk_0D4;
    player->pos.y += player->vel.y;
    if (player->unk_1D4 != 0) {
        Math_SmoothStepToAngle(&player->unk_0E4, player->unk_104, 0.2f, 5.0f, 0.005f);
        Math_SmoothStepToAngle(&player->unk_0EC, player->unk_10C, 0.2f, 5.0f, 0.005f);
        Math_SmoothStepToF(&player->unk_000, 0.0f, 0.1f, 5.0f, 0.00001f);
    }
    player->unk_1D4 = 0;
    if (player->pos.y <= gGroundLevel - 5.0f) {
        player->pos.y = gGroundLevel - 5.0f;
        if (player->vel.y < -20.0f) {
            player->unk_1F4 = 20;
        }
        player->vel.y = 0.0f;
        player->unk_1D4 = 1;
    }
    if (player->vel.y < -80.0f) {
        player->vel.y = -80.0f;
    }
    if (player->vel.y > 20.0f) {
        player->vel.y = 20.0f;
    }
    player->pos.z += player->vel.z;
    func_play_800AE278(player);
    player->unk_138 = player->pos.z;
    player->unk_0F8 = player->unk_0EC + player->unk_12C + player->unk_130;
    if (player->unk_1D4 != 0) {
        player->unk_0F4 += player->unk_0D0 * 5.0f;
        player->unk_0F0 = SIN_DEG(player->unk_0F4) * 0.7f;
    }
    func_play_800A46A0(player);
}

f32 D_800D30F4[4] = { 3.0f, 4.0f, 5.0f, 3.0f };
f32 D_800D3104[4] = { 0.2f, 0.25f, 0.3f, 0.2f };

void func_play_800B00C0(Player* player) {
    f32 sp2C = 0.0f;
    f32 sp28 = 0.7f;
    f32 sp24 = 0.1f;

    if (gInputHold->button & R_TRIG) {
        sp2C = 16.0f;
        sp28 = D_800D30F4[gPlayerNum];
        sp24 = D_800D3104[gPlayerNum];
    }
    Math_SmoothStepToF(&player->unk_0D0, sp2C, 1.0f, 1.0f, 0.00001f);
    Math_SmoothStepToF(&player->unk_008, sp28, 0.1f, sp24, 0.00001f);
}

void func_play_800B0194(Player* player) {
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

    player->unk_034 = 0.0f;
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
    D_ctx_80177968 = 3.0f;
    D_ctx_80177970 = 0.666f;
    sp74 = gInputPress->stick_x;
    sp70 = gInputPress->stick_y;
    Math_SmoothStepToF(&player->unk_0E8, -sp74 * D_ctx_80177970 * 0.6f, 0.5f, D_ctx_80177968, 0.001f);
    Math_SmoothStepToF(&player->unk_0EC, -sp74 * D_ctx_80177970 * 0.2f * player->unk_0D0 / 15.0f, 0.2f, 5.0f, 0.001f);
    player->unk_0F8 = player->unk_0EC;
    if ((sp74 != 0.0f) || (sp70 != 0.0f)) {
        Math_SmoothStepToF(&player->unk_15C, sp74 * D_ctx_80177970, 0.9f, 2.0f * D_ctx_80177968, 0.1f);
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
    player->unk_108 = player->unk_0E8;
    if (player->unk_0D0 < 1.5f) {
        var_fv0 = 0.12f;
        var_fa0 = 3.0f;
    } else {
        var_fv0 = 0.08f;
        var_fa0 = 1.5f;
    }
    Math_SmoothStepToF(&player->unk_11C, -sp74 * D_ctx_80177970 * var_fv0, 0.2f, var_fa0, 0.0f);
    player->unk_114 += player->unk_11C;
    player->unk_114 = Math_ModF(player->unk_114, 360.0f);
    Matrix_RotateX(gCalcMatrix, player->unk_104 * M_DTOR, 0);
    Matrix_RotateZ(gCalcMatrix, player->unk_10C * M_DTOR, 1);
    Matrix_RotateY(gCalcMatrix, (player->unk_114 + player->unk_0E8 + 180.0f) * M_DTOR, 1);
    sp58.x = 0.0f;
    sp58.y = 0.0f;
    sp58.z = player->unk_0D0;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp58, &sp4C);
    player->vel.x = sp4C.x;
    player->vel.z = sp4C.z;
    player->pos.x += player->vel.x;
    if ((player->pos.y < 40.0f) || (player->pos.y > 670.0f)) {
        player->unk_10C = 0.0f;
        player->unk_104 = 0.0f;
    }
    Math_SmoothStepToAngle(&player->unk_0FC, player->unk_104, 0.15f, 15.0f, 0.005f);
    Math_SmoothStepToAngle(&player->unk_100, player->unk_10C, 0.15f, 15.0f, 0.005f);
    if (player->unk_1D4 != 0) {
        if (player->unk_0D0 > 1.0f) {
            player->unk_00C += player->unk_008;
            if ((s32) player->unk_00C >= Animation_GetFrameCount(&D_versus_301CFEC)) {
                player->unk_00C = 0.0f;
            }
            player->unk_080 = 2.0f * SIN_DEG((player->unk_20C + 7) * 24.0f);
            if (player->unk_080 < -0.5f) {
                player->unk_080 = -0.5f;
            }
            player->unk_080 -= 3.0f;
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
            sp64 = player->unk_0D0;
            if (gGameFrameCount & 4) {
                sp64 = 2.0f * player->unk_0D0;
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
            Math_SmoothStepToF(&player->unk_080, -3.0f, 0.1f, 2.0f, 0.1f);
            Math_SmoothStepToF(&player->unk_164, 0.0f, 0.03f, 1.0f, 0.0001f);
            Math_SmoothStepToF(&player->unk_168, 0.0f, 0.03f, 1.0f, 0.0001f);
            player->unk_20C = 0;
            player->unk_00C = 0.0f;
        }
    }
    if (player->unk_1D4 == 0) {
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
    player->unk_0D4 = 2.0f;
    if ((gInputPress->button & Z_TRIG) && (player->unk_1D4 != 0)) {
        player->vel.y = 12.0f;
    }
    if ((gInputHold->button & Z_TRIG) && (player->vel.y > 0.0f)) {
        player->unk_0D4 = 1.5f;
    }
    player->unk_1D4 = 0;
    player->vel.y -= player->unk_0D4;
    player->pos.y += player->vel.y;
    if (player->pos.y <= gGroundLevel) {
        player->unk_1D4 = 1;
        player->pos.y = 0.0f;
        player->vel.y = 0.0f;
        player->unk_0E4 += (player->pos.y - player->unk_0E4) * 0.05f;
    }
    if (player->vel.y < -50.0f) {
        player->vel.y = -50.0f;
    }
    if (player->vel.y > 20.0f) {
        player->vel.y = 20.0f;
    }
    player->pos.z += player->vel.z;
    func_play_800AE278(player);
    player->unk_138 = player->pos.z;
}

f32 D_800D3114[4] = { 10000.0f, -10000.0f, 10000.0f, -10000.0f };
f32 D_800D3124[4] = { 10000.0f, -10000.0f, -10000.0f, 10000.0f };
f32 D_800D3134[8] = {
    // unused? possibly two f32[4]?
    500.0f, -500.0f, 500.0f, -500.0f, 500.0f, -500.0f, -500.0f, 500.0f,
};
f32 D_800D3154[4] = { 45.0f, -135.0f, 135.0f, -45.0f };

void func_play_800B0F50(Player* playerx) {
    s32 j;
    Vec3f* sp38;
    ObjectInit* objInit;
    s32 i;
    s16 sp2E;
    Player* player = playerx; // fake?

    D_ctx_80177BAC = 0;
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
    D_Timer_80177A00[gPlayerNum] = D_Timer_80177A38[gPlayerNum] = D_Timer_80177A70[gPlayerNum] =
        D_Timer_80177A88[gPlayerNum] = D_ctx_80177AE8[gPlayerNum] = D_ctx_80177AD0[gPlayerNum] =
            gChargeTimers[gPlayerNum] = D_ctx_80177B00[gPlayerNum][0] = D_ctx_80177B00[gPlayerNum][1] =
                D_ctx_80177B00[gPlayerNum][2] = D_ctx_80177B00[gPlayerNum][3] = 0;
    D_ctx_80177D40[gPlayerNum] = D_ctx_80177D58[gPlayerNum] = D_ctx_80177D70[gPlayerNum] = D_ctx_80177D88[gPlayerNum] =
        D_ctx_80177990[gPlayerNum] = D_ctx_801779A8[gPlayerNum] = D_ctx_80177AA0[gPlayerNum] = 0.0f;
    D_ctx_80177AB8[gPlayerNum] = 0.0f;
    player->unk_190 = 1.0f;
    player->unk_194 = 1.0f;
    gRadioState = D_ctx_80177D68 = D_ctx_801782A4 = 0;
    D_ctx_8017853C = D_ctx_80177D50 = 0.0f;
    player->camEye.z = 400.0f;
    player->unk_148 = 0.77699995f;
    player->unk_14C = 0.77699995f;
    player->unk_01C = 1.0f;
    player->unk_068 = -1000.0f;
    player->camAt.z = player->camEye.z - 1000.0f;
    D_ctx_80177950 = 1.0f;
    if ((gLevelType == LEVELTYPE_SPACE) && (gCurrentLevel != LEVEL_BOLSE)) {
        player->unk_240 = 1;
        player->unk_0A8 = 3000.0f;
        player->unk_09C = 700.0f;
        player->unk_0A0 = 612.0f;
        player->unk_0A4 = -544.0f;
        if (gCurrentLevel == LEVEL_UNK_15) {
            player->unk_0A0 = 3000.0f;
            player->unk_0A4 = -3000.0f;
        }
    } else {
        player->unk_09C = 700.0f;
        player->unk_0A0 = 680.0f;
        player->unk_0A4 = gGroundLevel + 40.0f;
        player->unk_0A8 = 3000.0f;
    }
    player->unk_0D0 = D_play_80161A54;
    player->pos.y = 350.0f;
    switch (gCurrentLevel) {
        case LEVEL_MACBETH:
        case LEVEL_TITANIA:
            player->form = FORM_LANDMASTER;
            player->unk_014 = 1.0f;
            player->unk_14C = 0.67f;
            player->unk_148 = 0.67f;
            player->unk_0D0 = 15.0f;
            player->unk_0D4 = 3.0f;
            player->unk_09C = 500.0f;
            player->unk_0A0 = 500.0f;
            player->unk_0A4 = -500.0f;
            if (gCurrentLevel == LEVEL_TITANIA) {
                player->pos.y = 150.0f;
            } else {
                player->pos.y = 0.0f;
            }
            break;
        case LEVEL_AQUAS:
            player->form = FORM_BLUE_MARINE;
            player->unk_0D4 = 0.0f;
            player->unk_09C = 700.0f;
            player->unk_0D0 = 20.0f;
            player->unk_0A0 = 720.0f;
            player->unk_0A4 = gGroundLevel + 30.0f;
            break;
        case LEVEL_SOLAR:
        case LEVEL_ZONESS:
            player->unk_0A4 = -450.0f;
            break;
    }
    if (gCurrentLevel != LEVEL_CORNERIA) {
        gSavedGroundType = GROUNDTYPE_GRASS;
    }
    gGoldRingCount[0] = D_ctx_80161A94[0];
    do {
        if (gGoldRingCount[0] > 3) {
            gGoldRingCount[0] -= 3;
        }
    } while (gGoldRingCount[0] > 3);

    if (gGoldRingCount[0] == 3) {
        gGoldRingCount[0] = 0;
    }
    gHitCount = gSavedHitCount;
    if ((gCurrentLevel == LEVEL_VENOM_ANDROSS) || ((gCurrentLevel == LEVEL_VENOM_2) && (gLevelStage == 2))) {
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
    D_ctx_80177DC8 = D_ctx_80177CA0;
    gGroundType = gSavedGroundType;
    D_ctx_80177D20 = player->unk_144 = D_ctx_80177CB0;
    player->pos.z = player->unk_138 = -player->unk_144;
    if ((D_ctx_80177CA0 > 0) && (gLevelMode == LEVELMODE_ON_RAILS)) {
        if (gCurrentLevel == LEVEL_MACBETH) {
            sp2E = D_ctx_80177DC8;
            Macbeth_801AD080();
            D_ctx_80177DC8 = sp2E;
        }
        func_enmy_80062568();
    }
    if (player->form == FORM_LANDMASTER) {
        player->pos.z -= 200.0f;
        player->unk_138 -= 200.0f;
    }
    player->camEye.y = (player->pos.y * player->unk_148) + 10.0f;
    player->camEye.x = player->pos.x * player->unk_148;

    gPlayerCamAt.x = gPlayerCamAt.y = gPlayerCamAt.z = gPlayerCamEye.x = gPlayerCamEye.y = gPlayerCamEye.z = 0.0f;

    if (gVersusMode) {
        gLaserStrength[gPlayerNum] = LASERS_SINGLE;
        player->pos.y = 500.0f;
        player->pos.x = D_800D3114[gPlayerNum];
        player->pos.z = D_800D3124[gPlayerNum];
        player->unk_114 = D_800D3154[gPlayerNum];
        player->form = D_ctx_80177870[gPlayerNum];
        switch (player->form) {
            case FORM_ARWING:
                break;
            case FORM_LANDMASTER:
                player->pos.y = 0.0f;
                player->unk_0D0 = 15.0f;
                player->unk_0D4 = 3.0f;
                break;
            case FORM_ON_FOOT:
                player->pos.y = 0.0f;
                player->unk_0D0 = 15.0f;
                player->unk_068 = 0;
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
        func_play_800B7184(player, 1);
    }
    player->state_1C8 = PLAYERSTATE_1C8_3;
    player->unk_204 = gLevelType;
    if ((gLevelMode == LEVELMODE_ALL_RANGE) && !gVersusMode) {
        player->pos.z = 8000.0f;
        player->pos.y = 670.0f;
        player->unk_0A0 = 730.0f;
        player->unk_204 = 2;
        if ((gCurrentLevel == LEVEL_VENOM_ANDROSS) && (gLevelStage == 1)) {
            player->pos.x = -7910.0f;
            player->pos.y = 300.0f;

            player->pos.z = -11808.0f;
            player->unk_114 = 188.0f;
            player->unk_240 = 1;
        }
        func_play_800B63BC(player, 1);
    } else {
        player->unk_014 = 1.0f;
        player->unk_018 = 1.0f;
    }
    if ((D_ctx_8017782C != 0) && (D_ctx_80177CA0 == 0)) {
        D_play_800D3180[gCurrentLevel] = 0;
        for (j = 0; j < 10; j++) {
            D_ctx_80177A10[j] = 0;
            D_ctx_80177A48[j] = 0.0f;
        }
        D_ctx_8017782C = 0;
        gAllRangeCheckpoint = 0;
        switch (gCurrentLevel) {
            case LEVEL_CORNERIA:
                player->state_1C8 = PLAYERSTATE_1C8_2;
                player->unk_204 = 1;
                gGroundType = gSavedGroundType = GROUNDTYPE_WATER;
                func_play_800A3FB0();
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
                player->state_1C8 = PLAYERSTATE_1C8_2;
                break;
            case LEVEL_METEO:
                player->state_1C8 = PLAYERSTATE_1C8_2;
                break;
        }
    } else {
        if (!gVersusMode && !((gCurrentLevel == LEVEL_VENOM_2) && (gLevelStage == 2))) {
            gLevelStatusScreenTimer = 80;
        }

        if (gCurrentLevel == LEVEL_BOLSE) {
            D_ctx_80177A98 = 1;
        }

        if ((gCurrentLevel == LEVEL_MACBETH) && (D_ctx_80177CA0 == 0)) {
            player->pos.z = -4115.0f;
            D_ctx_80177D20 = player->unk_144 = 3932.0f;

            D_ctx_80177DC8 = 40;
            gLevelObjects = LOAD_ASSET(gLevelObjectInits[gCurrentLevel]);
            for (objInit = gLevelObjects, i = 0; i < D_ctx_80177DC8; i++, objInit++) {
                Object_Load(objInit, 4000.0f, -4000.0f, 4000.0f, -4000.0f);
            }
            Macbeth_801ACFBC();
        }
    }
    if (player->state_1C8 == PLAYERSTATE_1C8_2) {
        player->unk_234 = 1;
        switch (gCurrentLevel) {
            case LEVEL_CORNERIA:
                AUDIO_PLAY_BGM(SEQ_ID_CO_INTRO);
                break;
            case LEVEL_METEO:
                AUDIO_PLAY_BGM(SEQ_ID_ME_INTRO);
                break;
            case LEVEL_FORTUNA:
            case LEVEL_BOLSE:
            case LEVEL_VENOM_2:
                AUDIO_PLAY_BGM(SEQ_ID_INTRO_51);
                break;
            case LEVEL_VENOM_1:
                AUDIO_PLAY_BGM(SEQ_ID_VENOM_1 | SEQ_FLAG);
                break;
            case LEVEL_KATINA:
                AUDIO_PLAY_BGM(SEQ_ID_INTRO_51);
                break;
            case LEVEL_TITANIA:
                AUDIO_PLAY_BGM(SEQ_ID_INTRO_45);
                break;
            case LEVEL_ZONESS:
            case LEVEL_SECTOR_X:
            case LEVEL_VENOM_ANDROSS:
            case LEVEL_TRAINING:
            case LEVEL_MACBETH:
            default:
                AUDIO_PLAY_BGM(SEQ_ID_INTRO_44);
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
        gGoldRingCount[0] = D_ctx_80161A94[0] = gTotalHits = 0;
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
                         (player->state_1C8 != PLAYERSTATE_1C8_2))) {
        func_8001C8B8(gPlayerNum);
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

void func_play_800B2130(Player* player) {
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
    player->unk_130 = Math_ModF(player->unk_130, 360.0f);
    if (player->unk_280 > 0) {
        player->unk_280 -= 30;
        if (player->unk_280 <= 0) {
            player->unk_280 = 0;
        }
    }
    if (player->timer_27C == 0) {
        if (player->unk_1DC == 0) {
            Math_SmoothStepToF(&player->unk_130, 0.0f, 0.1f, 10.0f, 0.00001f);
        }
        if (player->timer_1E0 != 0) {
            player->timer_1E0--;
        }
        if (player->timer_1E4 != 0) {
            player->timer_1E4--;
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
        if (player->unk_1DC != 0) {
            player->timer_1E4 = 0;
            player->timer_1E0 = 0;
            player->unk_150 = 1.5f;
            player->unk_130 += player->unk_1EC;
            if (player->timer_1E8 == 0) {
                if (player->unk_1EC > 0) {
                    player->unk_1EC -= 5;
                }
                if (player->unk_1EC < 0) {
                    player->unk_1EC += 5;
                }
                if (player->unk_1EC == 0) {
                    player->unk_1DC = 0;
                }
            } else if (player->unk_280 < 180) {
                player->unk_280 += 100;
                if (player->unk_280 > 180) {
                    player->unk_280 = 180;
                }
            }
        }
    }
}

void func_play_800B22C0(Player* player) {
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

    player->unk_130 = Math_ModF(player->unk_130, 360.0f);
    if (player->unk_1DC == 0) {
        temp_fv0 = player->unk_130;
        if (player->unk_130 > 0.0f) {
            player->unk_130 -= (player->unk_130 * 0.1f);
            if (player->unk_130 < 0.1f) {
                player->unk_130 = 0.0f;
            }
        }
        if (player->unk_130 < 0.0f) {
            player->unk_130 -= player->unk_130 * 0.1f;
            if (player->unk_130 > -0.1f) {
                player->unk_130 = 0.0f;
            }
        }
    }
    temp_v0 = player->timer_1E0;
    if (player->timer_1E0 != 0) {
        player->timer_1E0--;
    }
    if (player->timer_1E4 != 0) {
        player->timer_1E4--;
    }
    if (player->timer_1E8 != 0) {
        player->timer_1E8--;
    }
    if (player->unk_1DC != 0) {
        player->timer_1E4 = 0;
        player->timer_1E0 = 0;
        player->unk_130 += player->unk_1EC;
        if (player->unk_12C > 0.0f) {
            player->unk_12C -= 8.0f;
            if (player->unk_12C < 0.0f) {
                player->unk_12C = 0.0f;
            }
        }
        if (player->unk_12C < 0.0f) {
            player->unk_12C += 8.0f;
            if (player->unk_12C > 0.0f) {
                player->unk_12C = 0.0f;
            }
        }
        if (player->timer_1E8 == 0) {
            if (player->unk_1EC > 0) {
                player->unk_1EC -= 2;
            }
            if (player->unk_1EC < 0) {
                player->unk_1EC += 2;
            }
            if (player->unk_1EC == 0) {
                player->unk_1DC = 0;
            }
        } else {
            Math_SmoothStepToF(&D_ctx_801779A8[player->num], 30.0f, 1.0f, 30.0f, 0.0f);
        }
        if ((player->timer_1E8 >= 5) && (player->timer_498 == 0)) {
            if (player->unk_1EC > 0) {
                player->unk_170 = 1.3f;
            }
            if (player->unk_1EC < 0) {
                player->unk_16C = 1.3f;
            }
        }
        if (gVersusMode) {
            D_ctx_80177B00[player->num][0] = D_ctx_80177B00[player->num][1] = D_ctx_80177B00[player->num][2] =
                D_ctx_80177B00[player->num][3] = 0;
        }
    }
}

void func_play_800B2574(Player* player) {
    f32 sp2C;
    f32 sp28;
    s32 var;

    if ((player->unk_2BC != 0.0f) && (gInputHold->button & gBrakeButton[player->num]) &&
        (gInputHold->button & gBoostButton[player->num])) {
        player->unk_2B4 = true;
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
    if (D_Timer_80177A70[gPlayerNum] != 0) {
        D_Timer_80177A70[gPlayerNum]--;
    }

    if (D_Timer_80177A88[gPlayerNum] != 0) {
        D_Timer_80177A88[gPlayerNum]--;
    }
    if ((player->unk_4DC == 0) && (D_ctx_80177AB0 < 5)) {
        if (var >= -50) {
            D_Timer_80177A70[gPlayerNum] = 5;
        }
        if ((D_Timer_80177A70[gPlayerNum] > 0) && (D_Timer_80177A70[gPlayerNum] < 5) &&
            (D_Timer_80177A88[gPlayerNum] != 0)) {
            player->unk_4DC = 1;
            if (gLevelMode == LEVELMODE_ON_RAILS) {
                player->savedCockpitView = player->cockpitView;
                player->cockpitView = 0;
            }
            player->unk_014 = player->unk_018 = 0.0f;
            if (player->unk_4D8 > 340.0f) {
                player->unk_4D8 -= 360.0f;
            }
            return;
        }
    }
    if (player->timer_27C != 0) {
        player->timer_27C--;
        player->unk_2B4 = true;
        if (gRingPassCount > 0) {
            Math_SmoothStepToF(&D_ctx_801779A8[player->num], gRingPassCount * 10.0f, 1.0f, 5.0f, 0.0f);
        }
        player->unk_110 += 0.3f;
        Math_SmoothStepToF(&player->unk_08C, -130.0f, 0.2f, 10.0f, 0.0f);
        player->unk_130 -= player->unk_258;
        player->unk_258 = player->unk_258 + 0.2f;
        if (player->unk_258 > 50.0f) {
            player->unk_258 = 50.0f;
        }
        if (((gGameFrameCount % 2) == 0) && (gBlurAlpha > 64)) {
            if (1) {}
            gBlurAlpha--;
        }
    } else {
        player->unk_258 = 0.0f;
        if (gBlurAlpha < 255) {
            gBlurAlpha += 4;
            if (gBlurAlpha >= 252) {
                gBlurAlpha = 255;
            }
        }
        if (!(gInputHold->button & gBrakeButton[player->num]) && !(gInputHold->button & gBoostButton[player->num])) {
            player->unk_2B4 = true;
            if (player->unk_2BC == 0.0f) {
                player->unk_2B4 = false;
            }
        }
        if ((gInputHold->button & gBoostButton[player->num]) && !(gInputHold->button & gBrakeButton[player->num]) &&
            (player->state_1C8 != PLAYERSTATE_1C8_5) && !player->unk_2B4) {
            if (player->unk_2BC == 0.0f) {
                func_play_800A5FA0(player->sfxSource, 0x09000002, player->num);
                player->unk_194 = 5.0f;
                player->unk_190 = 5.0f;
                if (gBoostButton[player->num] & gInputPress->button) {
                    D_Timer_80177A88[gPlayerNum] = 5;
                }
            }
            if (gLevelType == LEVELTYPE_PLANET) {
                player->wings.unk_28 += (35.0f - player->wings.unk_28) * 0.1f;
                Math_SmoothStepToF(&player->wings.unk_04, 0.0f, 0.5f, 100.0f, 0.0f);
                Math_SmoothStepToF(&player->wings.unk_08, 0.0f, 0.5f, 100.0f, 0.0f);
                Math_SmoothStepToF(&player->wings.unk_0C, 0.0f, 0.5f, 100.0f, 0.0f);
                Math_SmoothStepToF(&player->wings.unk_10, 0.0f, 0.5f, 100.0f, 0.0f);
            }
            player->unk_2BC += sp28;
            if (player->unk_2BC > 90.0f) {
                player->unk_2BC = 90.0f;
                player->unk_2B4 = true;
            }
            player->unk_25C += 0.04f;
            if (player->unk_25C > 0.6f) {
                player->unk_25C = 0.6f;
            }
            player->unk_190 = 2.0f;
            player->unk_110 += 2.0f;
            if (player->unk_110 > 30.0f) {
                player->unk_110 = 30.0f;
            }
            Math_SmoothStepToF(&player->unk_08C, -400.0f, 0.1f, 30.0f, 0.0f);
            player->sfx.boost = 1;
            Math_SmoothStepToF(&D_ctx_801779A8[player->num], 50.0f, 1.0f, 10.0f, 0.0f);
        } else {
            if (player->unk_2BC > 0.0f) {
                player->unk_2BC -= sp2C;
                if (player->unk_2BC <= 0.0f) {
                    player->unk_2BC = 0.0f;
                    player->unk_2B4 = false;
                }
            }
            if (player->unk_110 > 0.0f) {
                player->unk_110 -= 1.0f;
                if (player->unk_110 < 0.0f) {
                    player->unk_110 = 0.0f;
                }
            }
        }
    }
}

void func_play_800B2BE0(Player* player) {
    func_play_800B2574(player);
}

void func_play_800B2C00(Player* player) {
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
    if (D_Timer_80177A00[gPlayerNum] != 0) {
        D_Timer_80177A00[gPlayerNum]--;
    }
    if (D_Timer_80177A38[gPlayerNum] != 0) {
        D_Timer_80177A38[gPlayerNum]--;
    }
    if (var >= -50) {
        D_Timer_80177A00[gPlayerNum] = 5;
    }
    if ((D_Timer_80177A00[gPlayerNum] > 0) && (D_Timer_80177A00[gPlayerNum] < 5) && (D_ctx_80177AB0 < 5) &&
        (D_Timer_80177A38[gPlayerNum] != 0)) {
        D_Timer_80177A00[gPlayerNum] = 0;
        D_Timer_80177A38[gPlayerNum] = 0;
        player->state_1C8 = PLAYERSTATE_1C8_5;
        player->unk_1D0 = 0;
        player->unk_19C = 1;
        player->unk_000 = 0.0f;
        player->unk_004 = 0.0f;
        player->unk_194 = 5.0f;
        player->unk_190 = 5.0f;
        if (gCurrentLevel == LEVEL_CORNERIA) {
            D_ctx_80177B6C++;
        }
    }
    if ((gInputHold->button & gBrakeButton[player->num]) && !(gInputHold->button & gBoostButton[player->num]) &&
        (player->state_1C8 != PLAYERSTATE_1C8_5) && !player->unk_2B4) {
        if (player->unk_2BC == 0.0f) {
            func_play_800A5FA0(player->sfxSource, 0x09000003, player->num);
            if ((gLevelMode == LEVELMODE_ALL_RANGE) && (gInputPress->button & gBrakeButton[player->num])) {
                D_Timer_80177A38[gPlayerNum] = 5;
            }
        }
        if (gLevelType == LEVELTYPE_PLANET) {
            Math_SmoothStepToF(&player->wings.unk_04, 90.0f, 0.2f, 100.0f, 0.0f);
            Math_SmoothStepToF(&player->wings.unk_08, -90.0f, 0.2f, 100.0f, 0.0f);
            Math_SmoothStepToF(&player->wings.unk_0C, 90.0f, 0.2f, 100.0f, 0.0f);
            Math_SmoothStepToF(&player->wings.unk_10, -90.0f, 0.2f, 100.0f, 0.0f);
        }
        player->unk_2BC += sp30;
        if (player->unk_2BC > 90.0f) {
            player->unk_2B4 = true;
            player->unk_2BC = 90.0f;
        }
        player->unk_190 = 0.3f;
        player->unk_110 -= 1.0f;
        if (player->unk_110 < -20.0f) {
            player->unk_110 = -20.0f;
        }
        Math_SmoothStepToF(&player->unk_08C, 180.0f, 0.1f, 10.0f, 0.0f);
        player->sfx.brake = 1;
        Math_SmoothStepToF(&D_ctx_801779A8[player->num], 25.0f, 1.0f, 5.0f, 0.0f);
    } else if (player->unk_2BC > 0.0f) {
        player->unk_2BC -= sp34;
        if (player->unk_2BC <= 0.0f) {
            player->unk_2BC = 0.0f;
            player->unk_2B4 = false;
        }
        if (player->unk_110 < 0.0f) {
            player->unk_110 += 0.5f;
            if (player->unk_110 > 0.0f) {
                player->unk_110 = 0.0f;
            }
        }
    }
    Math_SmoothStepToF(&player->unk_08C, 0.0f, 0.1f, 5.0f, 0.0f);
}

void func_play_800B3010(Player* player) {
    f32 sp2C;

    if (!player->unk_2B8) {
        Math_SmoothStepToF(&player->unk_2BC, 0.0f, 1.0f, 1.0f, 0.0f);
    }
    player->unk_2B8 = false;
    if (player->unk_2BC == 0.0f) {
        player->unk_2B4 = false;
    } else if (!(gInputHold->button & Z_TRIG) && !(gInputHold->button & R_TRIG) &&
               !(gInputHold->button & gBoostButton[player->num]) && !(gInputHold->button & gBrakeButton[player->num])) {
        player->unk_2B4 = true;
    }
    sp2C = 20.0f;
    if ((gInputHold->button & gBoostButton[player->num]) && !player->unk_2B4) {
        if (player->unk_2BC == 0.0f) {
            player->unk_194 = 4.0f;
            player->unk_190 = 4.0f;
            func_play_800A5FA0(player->sfxSource, 0x09000002, player->num);
        }
        Math_SmoothStepToF(&D_ctx_801779A8[player->num], 30.0f, 1.0f, 10.0f, 0.0f);
        player->unk_190 = 2.0f;
        sp2C = 35.0f;
        player->unk_2B8 = true;
        Math_SmoothStepToF(&player->unk_2BC, 90.0f, 1.0f, 1.0f, 0.0f);
        if (player->unk_2BC >= 90.0f) {
            player->unk_2B4 = true;
        }
    }
    if ((gInputHold->button & gBrakeButton[player->num]) && !player->unk_2B4) {
        if (player->unk_2BC == 0.0f) {
            func_play_800A5FA0(player->sfxSource, 0x09000003, player->num);
        }
        Math_SmoothStepToF(&D_ctx_801779A8[player->num], 20.0f, 1.0f, 10.0f, 0.0f);
        sp2C = 5.0f;
        player->unk_2B8 = true;
        Math_SmoothStepToF(&player->unk_2BC, 90.0f, 1.0f, 1.0f, 0.0f);
        if (player->unk_2BC >= 90.0f) {
            player->unk_2B4 = true;
        }
    }
    Math_SmoothStepToF(&player->unk_0D0, sp2C, 0.1f, 2.0f, 0.001f);
}

void func_play_800B3314(Player* player) {
    f32 temp;
    f32 temp2;

    player->unk_0D4 = 3.0f;
    if ((gInputHold->button & Z_TRIG) && !player->unk_2B4) {
        if (player->unk_2BC == 0.0f) {
            func_play_800A5FA0(player->sfxSource, 0x09000002, player->num);
        }
        player->unk_188 = 0.0f;
        player->unk_12C += 4.0f;
        if (player->unk_12C > 50.0f) {
            player->unk_12C = 50.0f;
        }
        Math_SmoothStepToF(&player->unk_170, 1.0f, 1.0f, 0.4f, 0.0f);
        player->unk_2B8 = true;
        Math_SmoothStepToF(&player->unk_2BC, 90.0f, 1.0f, 0.7f, 0.0f);
        if (player->unk_2BC >= 90.0f) {
            player->unk_2B4 = true;
        }
    } else {
        if (player->unk_12C > 0.0f) {
            player->unk_188 += 1.5f;
            player->unk_12C -= player->unk_188;
            if (player->unk_12C <= 0.0f) {
                player->unk_12C = 0.0f;
                if (player->unk_188 > 3.0f) {
                    player->unk_188 *= -0.4f;
                    player->unk_12C -= player->unk_188;
                }
            }
        }
    }
    if ((gInputHold->button & R_TRIG) && !player->unk_2B4) {
        if (player->unk_2BC == 0.0f) {
            func_play_800A5FA0(player->sfxSource, 0x09000002, player->num);
        }
        player->unk_188 = 0.0f;
        player->unk_12C -= 4.0f;
        if (player->unk_12C < -50.0f) {
            player->unk_12C = -50.0f;
        }
        Math_SmoothStepToF(&player->unk_16C, 1.0f, 1.0f, 0.4f, 0.0f);
        player->unk_2B8 = true;
        Math_SmoothStepToF(&player->unk_2BC, 90.0f, 1.0f, 0.7f, 0.0f);
        if (player->unk_2BC >= 90.0f) {
            player->unk_2B4 = true;
        }
    } else if (player->unk_12C < 0.0f) {
        player->unk_188 += 1.5f;
        player->unk_12C += player->unk_188;
        if (player->unk_12C >= 0.0f) {
            player->unk_12C = 0.0f;
            if (player->unk_188 > 3.0f) {
                player->unk_188 *= -0.4f;
                player->unk_12C += player->unk_188;
            }
        }
    }
    if ((player->unk_16C > 0.2f) && (player->unk_170 > 0.2f) && (player->timer_220 == 0)) {
        player->unk_12C += (((__cosf(gGameFrameCount * M_DTOR * 8.0f) * 10.0f) - player->unk_12C) * 0.1f);
        Math_SmoothStepToAngle(&player->unk_0E4, 0.0f, 0.05f, 5.0f, 0.00001f);
        Math_SmoothStepToAngle(&player->unk_0EC, 0.0f, 0.05f, 5.0f, 0.00001f);
        temp = gInputPress->stick_y;
        Math_SmoothStepToF(&player->unk_000, temp * 0.5f, 0.05f, 5.0f, 0.00001f);
        Math_SmoothStepToF(&player->unk_110, 30.0f, 0.5f, 5.0f, 0.0f);
        player->unk_0D4 = -0.4f;
        Math_SmoothStepToF(&D_ctx_801779A8[player->num], 30.0f, 1.0f, 10.0f, 0.0f);
        if ((gCamCount == 1) && ((gGameFrameCount % 2) == 0)) {
            func_effect_8007BC7C(RAND_FLOAT_CENTERED(20.0f) + player->pos.x, player->unk_068 + 10.0f,
                                 player->unk_138 - 10.0f, RAND_FLOAT(2.0f) + 4.0f);
        }
    } else if ((gCamCount == 1) && ((gGameFrameCount % 4) == 0) && (player->unk_1DC == 0)) {
        if ((player->unk_16C > 0.2f) && (player->timer_220 == 0)) {
            func_effect_8007BC7C(RAND_FLOAT_CENTERED(10.0f) + (player->pos.x - 57.0f), player->unk_068 + 10.0f,
                                 player->unk_138 - 10.0f, RAND_FLOAT(2.0f) + 3.0f);
        }
        if ((player->unk_170 > 0.2f) && (player->timer_220 == 0)) {
            func_effect_8007BC7C(RAND_FLOAT_CENTERED(10.0f) + (player->pos.x + 57.0f), player->unk_068 + 10.0f,
                                 player->unk_138 - 10.0f, RAND_FLOAT(2.0f) + 3.0f);
        }
    }
}

s32 D_800D3164[6] = {
    1, 1, -1, 1, -1, 1,
};

void func_play_800B39E0(Player* player) {
    s32 i;

    player->unk_084 = 0.0f;
    player->unk_090.x = player->pos.x;
    player->unk_090.y = player->pos.y;
    player->unk_090.z = player->pos.z;
    if (player->timer_1F8 != 0) {
        player->timer_1F8--;
    }
    if (player->timer_1FC != 0) {
        player->timer_1FC--;
    }
    if (player->timer_220 != 0) {
        player->timer_220--;
    }
    if (player->timer_498 != 0) {
        player->timer_498--;
    }
    if (player->timer_224 != 0) {
        player->timer_224--;
    }
    if (gVersusMode) {
        for (i = 0; i < gCamCount; i++) {
            if ((D_ctx_80177B00[player->num][i] != 0) && !(gControllerHold[i].button & A_BUTTON)) {
                D_ctx_80177B00[player->num][i]--;
            }
        }
    }
    if (D_ctx_80177D40[player->num] != 0) {
        D_ctx_80177D40[player->num]--;
        if (D_ctx_80177D40[player->num] == 1000) {
            D_ctx_80177D40[player->num] = 0;
        }
    }
    if (D_ctx_80177D58[player->num] != 0) {
        D_ctx_80177D58[player->num]--;
        if (D_ctx_80177D58[player->num] == 1000) {
            D_ctx_80177D58[player->num] = 0;
        }
    }
    if (D_ctx_80177D88[player->num] != 0) {
        D_ctx_80177D88[player->num]--;
    }
    if (D_ctx_80177D70[player->num] != 0) {
        D_ctx_80177D70[player->num]--;
    }
    if (D_ctx_80177AE8[player->num] != 0) {
        D_ctx_80177AE8[player->num]--;
        Math_SmoothStepToF(&D_ctx_80177AB8[player->num], 128.0f, 1.0f, 40.0f, 0.01f);
    } else {
        Math_SmoothStepToF(&D_ctx_80177AB8[player->num], 0.0f, 1.0f, 10.0f, 0.01f);
    }
    Math_SmoothStepToF(&D_ctx_80177AA0[player->num], 0.0f, 1.0f, 0.4f, 0.01f);
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
                D_ctx_80177DB8[gPlayerNum]++;
            } else {
                D_ctx_80177DB8[gPlayerNum]--;
            }
        }
        player->timer_278--;
    }
    if (player->unk_1F4 > 0) {
        if (player->unk_1F4 > 3) {
            *D_ctx_80177984 = 1;
        }
        player->unk_1F4--;
        if (player->form == FORM_ARWING) {
            player->unk_134 = (SIN_DEG(player->unk_1F4 * 400.0f) * player->unk_1F4) * D_800D3164[player->unk_21C];
            if (player->state_1C8 == PLAYERSTATE_1C8_3) {
                player->unk_084 =
                    (SIN_DEG(player->unk_1F4 * 400.0f) * player->unk_1F4) * D_800D3164[player->unk_21C] * 0.8f;
            }
        } else {
            player->unk_134 =
                (SIN_DEG(player->unk_1F4 * 400.0f) * player->unk_1F4) * D_800D3164[player->unk_21C] * 1.5f;
            player->unk_084 = 0.0f;
        }
        if ((gLevelMode != LEVELMODE_UNK_2) &&
            ((player->unk_0D8.x != 0.f) || (player->unk_0D8.y != 0.f) || (player->unk_0D8.z != 0.f)) &&
            ((player->unk_1A4 >= 40) || (player->unk_1A4 == 21))) {
            player->unk_2B4 = true;
            player->unk_0E4 = 0;
            player->unk_0E8 = 0;
            Math_SmoothStepToF(&player->unk_110, 0, 1.0f, 5.0f, 0);
        }
        if (player->unk_1F4 == 0) {
            player->unk_134 = 0;
        }
    }
    player->pos.x += player->unk_0D8.x;
    player->pos.y += player->unk_0D8.y;
    if (gLevelMode == LEVELMODE_ALL_RANGE) {
        player->pos.z += player->unk_0D8.z;
        Math_SmoothStepToF(&player->unk_0D8.z, 0, 0.1f, 1.0f, 0.5f);
    }
    Math_SmoothStepToF(&player->unk_0D8.x, 0, 0.1f, 1.0f, 0.5f);
    Math_SmoothStepToF(&player->unk_0D8.y, 0, 0.1f, 1.0f, 0.5f);
    player->unk_25C -= 0.02f;
    if (player->unk_25C < 0.0f) {
        player->unk_25C = 0.0f;
    }
}

void func_play_800B40AC(Player* player) {
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
            Audio_KillSfxById(0x41007012);
        }
    }
}

void func_play_800B415C(Player* player) {
    s32 var_v0;

    func_play_800B40AC(player);

    if (player->shields < 128) {
        if (player->shields > 80) {
            var_v0 = 64 - 1;
        } else if (player->shields > 40) {
            var_v0 = 32 - 1;
        } else {
            var_v0 = 16 - 1;
        }
        if ((gGameFrameCount & var_v0) == 0) {
            func_enmy_80060F30(player->sfxSource, 0x49001026, player->num);
        }
    }
}

void func_play_800B41E0(Player* player) {
}

void func_play_800B41EC(Player* player) {
    player->state_1C8 = PLAYERSTATE_1C8_4;
    if (!gVersusMode) {
        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 1);
        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 1);
        AUDIO_PLAY_BGM(SEQ_ID_DEATH);
    }
    if (gCurrentLevel == LEVEL_SOLAR) {
        Audio_KillSfxById(0x4100C023);
    }
    func_8001CA24(player->num);
    func_play_800A5FA0(player->sfxSource, 0x0900C010, player->num);
    player->shields = 0;
    player->unk_1D0 = 0;
    player->unk_1F4 = 0;
    player->timer_220 = 0;
    player->unk_134 = 0.0f;
    D_game_80161A2C = 0;
}

void func_play_800B42B0(Player* player) {
    switch (player->form) {
        case FORM_ARWING:
            if (player->timer_1F8 != 0) {
                gInputPress->stick_x = 0;
                gInputPress->stick_y = 0;
                gInputPress->button = 0;
                gInputHold->button = gBoostButton[player->num];
                player->unk_2BC = 1.0f;
            }
            func_play_800ADA28(player);
            func_play_800B2574(player);
            func_play_800B2C00(player);
            func_play_800B41E0(player);
            func_play_800B2130(player);
            if (player->unk_4DC != 0) {
                func_play_800AECAC(player);
            } else {
                func_play_800AF07C(player);
            }
            func_play_800ADF58(player);
            func_play_800AD7F0(player);
            func_play_800A8BA4(player);
            func_play_800A46A0(player);
            func_play_800A4C40(player);
            func_play_800AA800(player);
            func_play_800B415C(player);
            if ((player->shields <= 0) && (player->timer_220 != 0)) {
                func_play_800B41EC(player);
                player->vel.x *= 0.2f;
                player->vel.y = 5.0f;
                player->unk_0E4 = player->unk_0E8 = 0.0f;
                player->cockpitView = 0;
                player->timer_1F8 = 20;
                if (gLevelType == LEVELTYPE_SPACE) {
                    player->timer_1F8 = 40;
                }
                player->timer_1FC = 120;
            }
            break;
        case FORM_LANDMASTER:
            func_tank_80047504(player);
            break;
        case FORM_BLUE_MARINE:
            Aquas_801ACE50(player);
            Aquas_801AD328(player);
            func_play_800B41E0(player);
            Aquas_801AACF8(player);
            func_play_800ADF58(player);
            Aquas_801AC274(player);
            func_play_800A8BA4(player);
            func_play_800AA800(player);
            func_play_800B415C(player);
            if ((player->shields <= 0) && (player->timer_220 != 0)) {
                func_play_800B41EC(player);
            }
            break;
    }
}

void func_play_800B44C4(Player* player) {
    switch (player->form) {
        case FORM_ARWING:
            func_play_800ADA28(player);
            func_play_800B2574(player);
            func_play_800B2C00(player);
            func_play_800B41E0(player);
            func_play_800B2130(player);
            if (player->unk_4DC != 0) {
                func_play_800AECAC(player);
            } else {
                func_play_800AE4A4(player);
            }
            func_play_800AD7F0(player);
            func_play_800A8BA4(player);
            func_play_800A4C40(player);
            func_play_800AA800(player);
            func_play_800B415C(player);
            if ((player->shields <= 0) && (player->timer_220 != 0)) {
                func_play_800B41EC(player);
                player->vel.y = 5.0f;
                if (gLevelType == LEVELTYPE_SPACE) {
                    player->vel.y = 0.0f;
                }
                player->timer_1F8 = 20;
                player->timer_1FC = 120;
                player->unk_000 = 0.0f;
                player->unk_004 = 1.0f;
                if (player->unk_0E8 < 0.0f) {
                    player->unk_004 = -1.0f;
                }
                player->unk_0E4 = 0.0f;
                player->unk_4D8 = 0.0f;
            }
            break;
        case FORM_LANDMASTER:
            func_play_800ADD98(player);
            func_play_800B3314(player);
            func_play_800B3010(player);
            func_play_800B41E0(player);
            func_play_800B22C0(player);
            func_play_800AF928(player);
            func_play_800AD7F0(player);
            func_play_800A8BA4(player);
            func_play_800AA800(player);
            func_play_800B415C(player);
            if ((player->shields <= 0) && (player->timer_220 != 0)) {
                func_play_800B41EC(player);
            }
            break;
        case FORM_BLUE_MARINE:
            Aquas_801BEC80(player);
            break;
        case FORM_ON_FOOT:
            func_play_800B00C0(player);
            func_play_800B0194(player);
            func_play_800AD7F0(player);
            func_play_800A8BA4(player);
            func_play_800AA800(player);
            func_play_800B415C(player);
            if ((player->shields <= 0) && (player->timer_220 != 0)) {
                func_play_800B41EC(player);
            }
            break;
    }
}

void func_play_800B46F8(Player* player) {
    s32 teamId;

    if ((player->state_1C8 == PLAYERSTATE_1C8_3) && (D_ctx_8017796C >= 0)) {
        D_ctx_8017796C++;
        if (D_ctx_8017796C > 960) {
            D_ctx_8017796C = 0;
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
void Player_Update1(Player* player) {
    f32 sp1CC;
    f32 sp1C8;
    s32 sp1C4;
    s32 i;
    Vec3f sp58[30];
    s32 pad;

    if (gVersusMode) {
        gInputHold = &gControllerHold[player->num];
        gInputPress = &gControllerPress[player->num];
        D_ctx_80177984 = &D_80137E84[player->num];
    } else {
        gInputHold = &gControllerHold[gMainController];
        gInputPress = &gControllerPress[gMainController];
        D_ctx_80177984 = &D_80137E84[gMainController];
    }

    D_ctx_80177990[player->num] += (s32) D_ctx_801779A8[player->num];
    Math_SmoothStepToF(&D_ctx_801779A8[player->num], 0.0f, 1.0f, 1.5f, 0.0f);
    if (D_ctx_80177990[player->num] >= 100) {
        D_ctx_80177990[player->num] -= 100;
        *D_ctx_80177984 = 1;
    }
    if (D_Timer_80177BD0[player->num] != 0) {
        D_Timer_80177BD0[player->num]--;
        if (((gGameFrameCount % 2) == 0)) {
            *D_ctx_80177984 = 1;
        }
    }
    if (player->state_1C8 >= PLAYERSTATE_1C8_2) {
        func_play_800B39E0(player);
    }
    player->flags_228 = 0;
    if ((player->state_1C8 >= PLAYERSTATE_1C8_2) && (player->form == FORM_ARWING) && !gVersusMode) {
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
    sp1C4 = player->unk_22C;
    if (sp1C4 != 0) {
        player->unk_22C--;
    }
    switch (player->state_1C8) {
        case PLAYERSTATE_1C8_0:
            player->unk_234 = 0;
            D_game_80161A2C = 0;
            gPauseEnabled = 0;
            break;
        case PLAYERSTATE_1C8_1:
            func_play_800B0F50(player);
            gFillScreenAlphaTarget = 0;
            gPauseEnabled = 0;
            break;
        case PLAYERSTATE_1C8_2:
            D_game_80161A2C = 0;
            gPauseEnabled = 0;
            player->wings.unk_2C = 1;
            func_demo_8004A52C(player);
            break;
        case PLAYERSTATE_1C8_3:
            D_game_80161A2C = 1;
            func_play_800B46F8(player);
            player->wings.unk_2C = 0;
            D_hud_80161704 = 255;
            if ((!gVersusMode || (D_ctx_80177E7C != 0)) && (player->unk_4DC == 0) &&
                (gInputPress->button & U_CBUTTONS) &&
                ((player->form == FORM_ARWING) || (gVersusMode && (player->form == FORM_LANDMASTER)))) {
                if (player->cockpitView = 1 - player->cockpitView) {
                    AUDIO_PLAY_SFX(0x4900002C, gDefaultSfxSource, 4);
                } else {
                    AUDIO_PLAY_SFX(0x4900002D, gDefaultSfxSource, 4);
                    if (gLevelMode == LEVELMODE_ON_RAILS) {
                        player->unk_034 = 0.0f;
                    }
                }
                player->unk_014 = 0.1f;
            }
            switch (gLevelMode) {
                case LEVELMODE_ON_RAILS:
                    D_ctx_80178488 = true;
                    func_play_800B42B0(player);
                    player->unk_234 = 1;
                    break;
                case LEVELMODE_ALL_RANGE:
                    if (!gVersusMode) {
                        func_play_800B44C4(player);
                        player->unk_234 = 1;
                    } else if (D_ctx_80177E7C != 0) {
                        if (gPlayerInactive[player->num] == true) {
                            do {
                                sp1C4 = RAND_INT(3.9f);
                            } while (gPlayerInactive[sp1C4]);
                            player->unk_288 = sp1C4 + 1;
                            player->state_1C8 = PLAYERSTATE_1C8_13;
                            player->unk_1D0 = 0;
                            func_play_800B5FBC(player, player->unk_288 - 1, 1);
                        } else {
                            if (D_ctx_80177E7C == 1) {
                                D_ctx_80177E7C += 1;
                                for (i = 0; i < 4; i++) {
                                    func_play_800A5FA0(gPlayer[i].sfxSource, 0x09000002, gPlayer[i].num);
                                    gPlayer[i].unk_190 = gPlayer[i].unk_194 = 5.0f;
                                }
                            }
                            func_play_800B44C4(player);
                            player->unk_234 = 1;
                        }
                    } else {
                        gInputPress->stick_x = gInputPress->stick_y = 0;
                        D_ctx_80177844 = 0;
                        gPauseEnabled = 0;
                    }
                    break;
                case LEVELMODE_UNK_2:
                    D_ctx_80178488 = true;
                    Turret_801A5AD4(player);
                    func_play_800A8BA4(player);
                    break;
            }
            break;
        case PLAYERSTATE_1C8_4:
            func_demo_8004E3D8(player);
            break;
        case PLAYERSTATE_1C8_5:
            if (gVersusMode) {
                D_ctx_80177B00[player->num][0] = D_ctx_80177B00[player->num][1] = D_ctx_80177B00[player->num][2] =
                    D_ctx_80177B00[player->num][3] = 0;
            }
            player->wings.unk_2C = 1;
            Math_SmoothStepToF(&player->wings.unk_04, 0.0f, 0.1f, 5.0f, 0);
            Math_SmoothStepToF(&player->wings.unk_08, 0.0f, 0.1f, 5.0f, 0);
            Math_SmoothStepToF(&player->wings.unk_0C, 0.0f, 0.1f, 5.0f, 0);
            Math_SmoothStepToF(&player->wings.unk_10, 0.0f, 0.1f, 5.0f, 0);
            func_play_800B40AC(player);
            func_demo_8004CCC0(player);
            if (gCurrentLevel == LEVEL_KATINA) {
                func_play_800A8BA4(player);
            } else {
                func_play_800A887C(player);
                func_play_800A86E4(player);
            }
            break;
        case PLAYERSTATE_1C8_7:
            player->cockpitView = 0;
            gPauseEnabled = 0;
            func_play_800B40AC(player);
            func_demo_8004C930(player);
            func_play_800A4C40(player);
            D_game_80161A2C = gChargeTimers[player->num] = 0;
            break;
        case PLAYERSTATE_1C8_8:
            gPauseEnabled = 0;
            func_play_800B40AC(player);
            func_demo_80049C0C(player);
            D_game_80161A2C = 0;
            break;
        case PLAYERSTATE_1C8_9:
            gPauseEnabled = 0;
            func_play_800B40AC(player);
            func_demo_8004AAF4(player);
            func_play_800B2130(player);
            gChargeTimers[player->num] = player->cockpitView = D_game_80161A2C = 0;
            break;
        case PLAYERSTATE_1C8_10:
            gPauseEnabled = 0;
            func_360_8002E700(player);
            D_game_80161A2C = 0;
            break;
        case PLAYERSTATE_1C8_11:
            Andross_8018C390(player);
            func_play_800B40AC(player);
            break;
        case PLAYERSTATE_1C8_12:
            break;
        case PLAYERSTATE_1C8_13:
            player->unk_234 = 0;
            if (gPlayerInactive[player->num] == true) {
                func_play_800B5FBC(player, player->unk_288 - 1, 0);
            } else if ((D_ctx_80177E74 == 0) && (player->unk_1D0 != 0)) {
                player->unk_1D0 = 0;
                func_play_800AB304(player);
                func_play_800B0F50(player);
                func_play_800B44C4(player);
                func_play_800B7184(player, 1);
                func_play_800A5FA0(player->sfxSource, 0x09000002, player->num);
                player->unk_190 = player->unk_194 = 5.0f;
            } else if (player->unk_288 >= 0) {
                if (player->unk_288 == 0) {
                    player->unk_288 = 1;
                }
                func_play_800B5FBC(player, player->unk_288 - 1, 0);
            }
            break;
        case PLAYERSTATE_1C8_6:
            D_game_80161A2C = 0;
            if (!gVersusMode) {
                gPauseEnabled = 0;
            }
            player->unk_234 = 0;
            player->vel.z = player->vel.x = player->vel.y = player->unk_0D8.x = player->unk_0D8.y = 0.0f;

            if ((gLevelMode == LEVELMODE_ALL_RANGE) && (D_ctx_8017837C == 7)) {
                player->camEye.x += 1.0f;
                player->camEye.z += 1.5f;
            }
            if ((gCurrentLevel == LEVEL_ZONESS) || (gCurrentLevel == LEVEL_SOLAR)) {
                Math_SmoothStepToF(&player->camEye.y, 500.0f, 0.05f, 10.0f, 0.0f);
                Math_SmoothStepToF(&player->camEye.z, player->unk_138 + D_ctx_80177D20 + 500.0f, 0.05f, 20.0f, 0.0f);
            }
            if (player->timer_1F8 == 0) {
                if (gCamCount == 4) {
                    player->state_1C8 = PLAYERSTATE_1C8_13;
                    player->timer_1F8 = 200;
                } else {
                    gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
                    gFillScreenAlphaTarget = 255;
                }
                if (gFillScreenAlpha == 255) {
                    func_play_800A6148();
                    D_ctx_80177D20 = gPlayer[0].unk_144 = 0.0f;
                    gPlayerFillScreenAlphas[0] = 0;
                    gShowAllRangeCountdown = gRadioState = 0;
                    Audio_ClearVoice();
                    Audio_SetBaseSfxReverb(0);
                    D_ctx_80161A94[0] = gGoldRingCount[0];
                    if (gCurrentLevel == LEVEL_VENOM_ANDROSS) {
                        if (1) {}
                        if (1) {}
                        if (1) {}
                        if (1) {}
                        if (1) {}
                        D_ctx_80177C94 = gGoldRingCount[0];
                    }
                    if (D_ctx_8017837C != 4) {
                        if (D_ctx_8017837C != 7) {
                            gDrawMode = DRAW_NONE;
                        } else if (gCurrentLevel == LEVEL_TRAINING) {
                            gGameState = GSTATE_MENU;
                            gNextGameStateTimer = 2;
                            gOptionMenuStatus = OPTION_WAIT;
                            gDrawMode = DRAW_NONE;
                            D_game_80161A34 = 7;
                            D_ctx_80178410 = 0;
                        } else {
                            if ((gCurrentLevel == LEVEL_SECTOR_X) || (gCurrentLevel == LEVEL_METEO)) {
                                gLevelStage = 0;
                            }
                            if (gLifeCount[gPlayerNum] < 0) {
                                gNextGameState = GSTATE_GAME_OVER;
                                D_ctx_80161A94[0] = 0;
                            } else {
                                gPlayState = PLAY_INIT;
                            }
                            gBombCount[gPlayerNum] = 3;
                            gLaserStrength[gPlayerNum] = LASERS_SINGLE;
                            D_ctx_80178488 = true;
                            gDrawMode = DRAW_NONE;
                        }
                    } else {
                        gNextGameState = GSTATE_MAP;
                        D_game_80161A34 = 7;
                        gDrawMode = DRAW_NONE;
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
    Math_SmoothStepToF(&player->unk_09C, sp1C8, 1.0f, 10.0f, 0.0f);
    if (player->form == FORM_ARWING) {
        Math_SmoothStepToF(&player->unk_194, player->unk_190, 0.5f, 5.0f, 0.0f);
        if (player->unk_2B4 && (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_3)) {
            player->unk_190 = 0.5f;
        } else {
            player->unk_190 = 1.0f;
        }

    } else if (player->form == FORM_LANDMASTER) {
        Math_SmoothStepToF(&player->unk_194, player->unk_190, 0.5f, 0.5f, 0.0f);
        player->unk_190 = 0.0f;
    }
}

void func_play_800B56BC(Player* player) {
    f32 var_fv1;
    f32 var_fv0;
    f32 temp;

    gCsCamEyeX = (player->pos.x - player->unk_0AC) * player->unk_148;
    if (((player->form == FORM_ARWING) && (player->state_1C8 == PLAYERSTATE_1C8_3)) ||
        (player->state_1C8 == PLAYERSTATE_1C8_5)) {
        gCsCamEyeY = (player->pos.y - player->unk_0B0) * player->unk_148;
    }
    var_fv1 = gInputPress->stick_x;
    var_fv0 = -gInputPress->stick_y;

    if ((player->state_1C8 != PLAYERSTATE_1C8_3) || (player->unk_4DC != 0)) {
        var_fv0 = 0.0f;
        var_fv1 = 0;
    }
    Math_SmoothStepToF(&player->unk_030, var_fv1 * 1.6f, 0.1f, 3.0f, 0.05f);
    if (gLevelType == LEVELTYPE_SPACE) {
        Math_SmoothStepToF(&player->unk_02C, var_fv0 * 0.8f, 0.1f, 3.0f, 0.05f);
    } else if (player->pos.y < (gGroundLevel + 50.0f)) {
        Math_SmoothStepToF(&player->unk_02C, var_fv0 * 0.3f, 0.1f, 3.0f, 0.05f);
    } else {
        Math_SmoothStepToF(&player->unk_02C, 2.0f * var_fv0, 0.1f, 4.0f, 0.05f);
    }
    gCsCamEyeX -= player->unk_030 * 1.5f;
    gCsCamEyeY -= player->unk_02C - 50.0f;
    gCsCamAtX = (player->pos.x - player->unk_0AC) * player->unk_14C;
    gCsCamAtX += player->unk_084 * -2.0f;
    gCsCamAtX -= player->unk_030 * 0.5f;
    gCsCamAtY = ((player->pos.y - player->unk_0B0) * player->unk_14C) + 20.0f;
    gCsCamAtY += player->unk_060 * 5.0f;
    gCsCamAtY -= player->unk_02C * 0.25f;
    switch (D_800D2F54) {
        case 0:
            Math_SmoothStepToF(&D_800D2F58, 0.0f, 0.4f, 10.0f, 0);
            break;
        case 1:
            Math_SmoothStepToF(&D_800D2F58, 200.0f, 0.4f, 10.0f, 0);
            break;
    }
    gCsCamEyeX += player->unk_0AC;
    gCsCamAtX += player->unk_0AC;
    gCsCamEyeY += player->unk_0B0 + D_800D2F58;
    gCsCamAtZ = (player->unk_138 + D_ctx_80177D20) - 1.0f;
    gCsCamEyeZ = 400.0f + D_800D2F58;
    if (D_ctx_80177C70 == 2) {
        gCsCamEyeZ -= 50.0f;
    }
    if (player->unk_4DC != 0) {
        gCsCamEyeZ += 200.0f;
        gCsCamAtY = (player->pos.y - player->unk_0B0) * 0.9f;
        Math_SmoothStepToF(&player->camEye.z, gCsCamEyeZ, 0.1f, 8.0f, 0.0f);
        Math_SmoothStepToF(&player->unk_018, 0.2f, 1.0f, 0.05f, 0.0f);
    } else {
        Math_SmoothStepToF(&player->camEye.z, gCsCamEyeZ, 0.2f, 20.0f, 0.0f);
        Math_SmoothStepToF(&player->unk_018, 1.0f, 1.0f, 0.05f, 0.0f);
    }
    gCsCamAtY += player->unk_0B0 + (D_800D2F58 * 0.5f);
    Math_SmoothStepToF(&player->camEye.x, gCsCamEyeX, player->unk_014, 1000.0f, 0.0f);
    Math_SmoothStepToF(&player->camEye.y, gCsCamEyeY, player->unk_018, 1000.0f, 0.0f);
    Math_SmoothStepToF(&player->camAt.x, gCsCamAtX, player->unk_014, 1000.0f, 0.0f);
    Math_SmoothStepToF(&player->camAt.y, gCsCamAtY, player->unk_018, 1000.0f, 0.0f);
    Math_SmoothStepToF(&player->camAt.z, gCsCamAtZ, player->unk_014, 1000.0f, 0.0f);
    Math_SmoothStepToF(&player->unk_014, 1.0f, 1.0f, 0.05f, 0.0f);
    temp = -player->unk_0EC;
    if (gLevelType == LEVELTYPE_PLANET) {
        Math_SmoothStepToF(&player->unk_034, temp * 0.3f, 0.1f, 1.5f, 0.0f);
    } else if (gLevelType == LEVELTYPE_SPACE) {
        Math_SmoothStepToF(&player->unk_034, temp * 0.2f, 0.1f, 1.5f, 0.0f);
    }
}

void func_play_800B5D30(Player* player, s32 arg1) {
    Vec3f sp4C;
    Vec3f sp40;
    s32 pad;
    s32 pad2;
    s32 pad3;

    Matrix_RotateY(gCalcMatrix, (player->unk_0E8 + player->unk_134) * M_DTOR * 0.75f, 0);
    Matrix_RotateX(gCalcMatrix, (player->unk_0E4 + player->unk_134) * M_DTOR * 0.75f, 1);
    sp4C.x = 0;
    sp4C.y = 0;
    sp4C.z = -1000.0f;
    Matrix_MultVec3f(gCalcMatrix, &sp4C, &sp40);
    gCsCamEyeX = player->pos.x;
    gCsCamEyeY = player->pos.y + player->unk_080;
    gCsCamEyeZ = player->unk_138 + D_ctx_80177D20;
    gCsCamAtX = player->pos.x + sp40.x;
    gCsCamAtY = player->pos.y + player->unk_080 + sp40.y;
    gCsCamAtZ = player->unk_138 + D_ctx_80177D20 + sp40.z;
    Math_SmoothStepToF(&player->camEye.x, gCsCamEyeX, player->unk_014, 100.0f, 0.0f);
    Math_SmoothStepToF(&player->camEye.y, gCsCamEyeY, player->unk_014, 100.0f, 0.0f);
    Math_SmoothStepToF(&player->camEye.z, gCsCamEyeZ, player->unk_014, 50.0f, 0.0f);
    Math_SmoothStepToF(&player->camAt.x, gCsCamAtX, player->unk_014, 100.0f, 0.0f);
    Math_SmoothStepToF(&player->camAt.y, gCsCamAtY, player->unk_014, 100.0f, 0.0f);
    Math_SmoothStepToF(&player->camAt.z, gCsCamAtZ, player->unk_014, 100.0f, 0.0f);
    Math_SmoothStepToF(&player->unk_014, 1.0f, 1.0f, 0.05f, 0);
    player->unk_034 = -(player->unk_0F8 + player->unk_0F0);
    if (arg1 != 0) {
        player->camEye.x = gCsCamEyeX;
        player->camEye.y = gCsCamEyeY;
        player->camEye.z = gCsCamEyeZ;
        player->camAt.x = gCsCamAtX;
        player->camAt.y = gCsCamAtY;
        player->camAt.z = gCsCamAtZ;
    }
}

void func_play_800B5FBC(Player* player, s32 playerNum, bool arg2) {
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
            if ((gPlayer[playerNum].state_1C8 != PLAYERSTATE_1C8_13) && !gPlayerInactive[playerNum]) {
                break;
            }
        }
        if (i > 90) {
            playerNum = 0;
        }
        player->unk_288 = playerNum + 1;
        Matrix_RotateY(gCalcMatrix, gPlayer[playerNum].unk_114 * M_DTOR, 0);
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
        player->camEye.x = gPlayer[playerNum].pos.x + sp4C.x;
        player->camEye.y = gPlayer[playerNum].pos.y + 50.0f;
        player->camEye.z = gPlayer[playerNum].unk_138 + sp4C.z;
    }
    player->camAt.x = gPlayer[playerNum].pos.x;
    player->camAt.y = gPlayer[playerNum].pos.y;
    player->camAt.z = gPlayer[playerNum].unk_138;
    switch (gPlayer[playerNum].form) {
        case FORM_ARWING:
            player->camEye.x += gPlayer[playerNum].vel.x * 0.5f;
            player->camEye.z += gPlayer[playerNum].vel.z * 0.5f;
            break;
        case FORM_LANDMASTER:
            player->camEye.x += gPlayer[playerNum].vel.x * 0.7f;
            player->camEye.z += gPlayer[playerNum].vel.z * 0.7f;
            break;
        case FORM_ON_FOOT:
            player->camEye.x += gPlayer[playerNum].vel.x * 0.7f;
            player->camEye.z += gPlayer[playerNum].vel.z * 0.7f;
            player->camEye.y = gPlayer[playerNum].unk_068 + 20.0f;
            player->camAt.y = gPlayer[playerNum].unk_068 + 20.0f;
            break;
    }
    Math_SmoothStepToF(&player->unk_034, 0.0f, 0.05f, 5.0f, 0.00001f);
}

void func_play_800B63BC(Player* player, s32 arg1) {
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

    Matrix_RotateY(gCalcMatrix, (player->unk_114 + (player->unk_134 * 0.2f)) * M_DTOR, 0);
    Matrix_RotateX(gCalcMatrix, player->unk_134 * 0.2f * M_DTOR, 1);
    sp74.x = 0.0f;
    sp74.y = 0.0f;
    if (player->cockpitView != 0) {
        sp74.z = 1000.0f - player->unk_08C;
    } else {
        sp74.z = 300.0f - player->unk_08C;
    }
    if (player->unk_4DC != 0) {
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

    atX = player->pos.x + player->unk_134;

    var_fv0 = (player->unk_4DC != 0) ? 1.0f : 0.79f;
    atY = (player->pos.y * (var_fv0)) + player->unk_134 + (player->unk_060 * 5.0f);
    atY += (player->unk_02C * 0.5f);
    if (player->state_1C8 == PLAYERSTATE_1C8_5) {
        atY = player->pos.y;
    }
    atZ = player->pos.z;
    Math_SmoothStepToF(&player->unk_028, 2.0f * player->unk_0E8, 0.05f, 2.0f, 0.02f);
    sp74.x = -player->unk_028;
    sp74.y = 0.0f;
    sp74.z = 0.f;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp74, &sp68);
    eyeX += sp68.x;
    eyeZ += sp68.z;
    atX += sp68.x;
    atZ += sp68.z;
    if (player->state_1C8 == PLAYERSTATE_1C8_3) {
        Math_SmoothStepToF(&player->camEye.x, eyeX, player->unk_014, 30000.0f, 0);
        Math_SmoothStepToF(&player->camEye.y, eyeY, player->unk_014, 30000.0f, 0);
        Math_SmoothStepToF(&player->camEye.z, eyeZ, player->unk_014, 30000.0f, 0);
        Math_SmoothStepToF(&player->unk_034, player->unk_0E8 * -0.3f, 0.1f, 1.0f, 0);
        Math_SmoothStepToF(&player->unk_014, 0.2f, 0.1f, 0.005f, 0.0f);
    }
    Math_SmoothStepToF(&player->camAt.x, atX, player->unk_01C, 30000.0f, 0);
    Math_SmoothStepToF(&player->camAt.y, atY, player->unk_018, 30000.0f, 0);
    Math_SmoothStepToF(&player->camAt.z, atZ, player->unk_01C, 30000.0f, 0);
    Math_SmoothStepToF(&player->unk_018, 0.2f, 0.1f, 0.005f, 0);
    Math_SmoothStepToF(&player->unk_01C, 1.0f, 0.1f, 0.005f, 0);
    if (arg1 != 0) {
        player->camEye.x = eyeX;
        player->camEye.y = eyeY;
        player->camEye.z = eyeZ;
        player->camAt.x = atX;
        player->camAt.y = atY;
        player->camAt.z = atZ;
    }
}

void func_play_800B6848(Player* player, s32 arg1) {
    Vec3f sp54;
    Vec3f sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;

    Matrix_RotateX(gCalcMatrix, player->unk_0E4 * M_DTOR, 0);
    Matrix_RotateZ(gCalcMatrix, player->unk_0EC * M_DTOR, 1);
    Matrix_RotateY(gCalcMatrix, (player->unk_114 + (player->unk_134 * 0.2f)) * M_DTOR, 1);
    Matrix_RotateX(gCalcMatrix, player->unk_134 * 0.2f * M_DTOR, 1);
    sp54.x = 0.0f;
    if (player->cockpitView) {
        sp54.y = 150.0f;
        sp54.z = 500.0f - player->unk_08C;
    } else {
        sp54.y = 100.0f;
        sp54.z = 250.0f - player->unk_08C;
    }
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp54, &sp48);
    if (player->cockpitView) {
        Math_SmoothStepToF(&player->unk_02C, -player->unk_17C * 3.0f + 30.0f, 0.2f, 8.0f, 0.001f);
    } else {
        Math_SmoothStepToF(&player->unk_02C, -player->unk_17C * 3.0f, 0.2f, 8.0f, 0.001f);
    }
    sp44 = player->pos.x + sp48.x;
    sp40 = player->pos.y + sp48.y - (player->unk_02C * 0.6f);
    sp3C = player->pos.z + sp48.z;

    player->camAt.x = player->pos.x + player->unk_134;
    player->camAt.y = player->pos.y + 60.0f + player->unk_02C + player->unk_134;
    player->camAt.z = player->pos.z;
    Math_SmoothStepToF(&player->unk_028, 2.0f * player->unk_0E8, 0.05f, 2.0f, 0.02f);
    sp54.x = -player->unk_028;
    sp54.y = 0.0f;
    sp54.z = 0.0f;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp54, &sp48);
    sp44 += sp48.x;
    sp3C += sp48.z;
    player->camAt.x += sp48.x;
    player->camAt.z += sp48.z;
    Math_SmoothStepToF(&player->camEye.x, sp44, 0.1f, 200.0f, 0.001f);
    Math_SmoothStepToF(&player->camEye.y, sp40, 0.1f, 200.0f, 0.001f);
    Math_SmoothStepToF(&player->camEye.z, sp3C, 0.1f, 200.0f, 0.001f);
    Math_SmoothStepToF(&player->unk_034, player->unk_12C * -0.1f, 0.1f, 1.0f, 0.01f);
    if (arg1 != 0) {
        player->camEye.x = sp44;
        player->camEye.y = sp40;
        player->camEye.z = sp3C;
    }
}

void func_play_800B6BFC(Player* player, s32 arg1) {
    Vec3f sp64;
    Vec3f sp58;
    Vec3f sp4C;

    Matrix_RotateX(gCalcMatrix, player->unk_0FC * M_DTOR, 0);
    Matrix_RotateZ(gCalcMatrix, player->unk_100 * M_DTOR, 1);
    Matrix_RotateY(gCalcMatrix, (player->unk_114 + (player->unk_134 * 0.02f)) * M_DTOR, 1);
    Matrix_RotateX(gCalcMatrix, player->unk_134 * 0.02f * M_DTOR, 1);
    sp64.x = 0.0f;
    sp64.y = 20.0f;
    sp64.z = 60.0f - player->unk_08C;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp64, &sp58);
    Math_SmoothStepToF(&player->unk_02C, -player->unk_158 * 0.5f, 0.07f, 3.0f, 0.001f);

    sp4C.x = player->pos.x + sp58.x;
    sp4C.y = (player->unk_068 + 10.0f + sp58.y) - (player->unk_02C * 0.8f);
    sp4C.z = player->pos.z + sp58.z;

    player->camAt.x = player->pos.x + player->unk_134 * 0.1f;
    player->camAt.y = player->unk_068 + (player->pos.y - player->unk_068) * 0.4f + 18.0f + player->unk_02C * 1.5f +
                      player->unk_134 * 0.1f;
    player->camAt.z = player->pos.z;

    Math_SmoothStepToF(&player->unk_028, player->unk_0E8 * (player->unk_0D0 + 5.0f) * 0.04f, 0.05f, 2.0f, 0.02f);
    sp64.x = -player->unk_028;
    sp64.y = 0.0f;
    sp64.z = 0.0f;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp64, &sp58);
    sp4C.x += sp58.x;
    sp4C.z += sp58.z;
    player->camAt.x += sp58.x;
    player->camAt.z += sp58.z;

    Math_SmoothStepToF(&player->camEye.x, sp4C.x, 0.3f, 65.0f, 0.001f);
    Math_SmoothStepToF(&player->camEye.y, sp4C.y, 0.3f, 65.0f, 0.001f);
    Math_SmoothStepToF(&player->camEye.z, sp4C.z, 0.3f, 65.0f, 0.001f);
    Math_SmoothStepToF(&player->unk_034, player->unk_12C * -0.1f, 0.1f, 1.0f, 0.01f);
    if (arg1 != 0) {
        player->camEye.x = sp4C.x;
        player->camEye.y = sp4C.y;
        player->camEye.z = sp4C.z;
    }
}

void func_play_800B6F50(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 var_ft5;
    f32 sp20;

    sp28 = -Math_Atan2F(arg0 - arg3, arg2 - arg5);
    var_ft5 = sqrtf(SQ(arg2 - arg5) + SQ(arg0 - arg3));
    sp2C = -Math_Atan2F(arg1 - arg4, var_ft5);
    if (sp28 >= M_PI / 2) {
        sp28 -= M_PI;
    }
    if (sp28 <= -M_PI / 2) {
        sp28 += M_PI;
    }
    var_ft5 = 0.0f;
    if (gCurrentLevel == LEVEL_UNK_15) {
        var_ft5 = gPlayer[0].camEye.y * 0.03f;
    }
    sp30 = (2.0f * (-sp2C * (-8.0f / 3.0f * M_RTOD))) + 3000.0f + D_ctx_80178430 + var_ft5;
    sp34 = (2.0f * (sp28 * (-8.0f / 3.0f * M_RTOD))) + 3000.0f + D_ctx_8017842C;
    sp20 = D_ctx_80178420;
    D_ctx_80178420 = Math_ModF(sp34, 480.0f);
    D_ctx_80178424 = Math_ModF(sp30, 360.0f);
    if ((gGameState == GSTATE_PLAY) && (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_2) && (gCurrentLevel == LEVEL_METEO)) {
        if (fabsf(D_ctx_80178420 - sp20) < 50.0f) {
            D_bg_8015F96C = 0.0f;
            if (fabsf(D_ctx_80178420 - sp20) > 3.0f) {
                D_bg_8015F96C = fabsf(D_ctx_80178420 - sp20 - 3.0f) * 0.5f;
            }
        }
    }
}

void func_play_800B7184(Player* player, s32 arg1) {
    switch (player->form) {
        case FORM_ON_FOOT:
            func_play_800B6BFC(player, arg1);
            break;
        case FORM_LANDMASTER:
            func_play_800B6848(player, arg1);
            break;
        case FORM_ARWING:
            func_play_800B63BC(player, arg1);
            break;
    }
}

void Player_Update2(Player* player) {
    switch (player->state_1C8) {
        case PLAYERSTATE_1C8_3:
            switch (gLevelMode) {
                case LEVELMODE_ON_RAILS:
                    if (player->form == FORM_ARWING) {
                        if (player->cockpitView == 0) {
                            func_play_800B56BC(player);
                        } else {
                            func_play_800B5D30(player, 0);
                        }
                    } else if (player->form == FORM_LANDMASTER) {
                        func_tank_80043468(player);
                    } else if (player->form == FORM_BLUE_MARINE) {
                        Aquas_801AA8E8(player);
                    }
                    break;
                case LEVELMODE_ALL_RANGE:
                    func_play_800B7184(player, 0);
                    break;
                case LEVELMODE_UNK_2:
                    Turret_801A5FC0(player);
                    break;
            }
            break;
        case PLAYERSTATE_1C8_5:
            player->unk_034 -= player->unk_034 * 0.1f;
            func_play_800B7184(player, 0);
            break;
        case PLAYERSTATE_1C8_4:
            if ((gLevelMode == LEVELMODE_ON_RAILS) && (player->form == FORM_ARWING)) {
                player->camEye.x += (player->pos.x - player->camEye.x) * 0.1f;
                player->camEye.y += (player->pos.y - player->camEye.y) * 0.1f;
                player->camEye.z -= player->vel.z * 0.2f;
                if (player->unk_1D0 != 0) {
                    player->camEye.z -= player->vel.z * 0.2f;
                }
                player->camAt.x += (player->pos.x - player->camAt.x) * 0.1f;
                player->camAt.y += (player->pos.y - player->camAt.y) * 0.1f;
                player->camAt.z = player->unk_138 + D_ctx_80177D20 - 1.0f;
            }
            break;
        case PLAYERSTATE_1C8_6:
        case PLAYERSTATE_1C8_7:
            break;
    }
}

void func_play_800B73E0(Player* player) {
    Vec3f sp44;
    Vec3f sp38;
    f32 pad;

    if ((gCurrentLevel == LEVEL_AQUAS) && (gPlayer[0].state_1C8 != PLAYERSTATE_1C8_2)) {
        D_ctx_801784D4 = D_ctx_801784C8 = D_ctx_801784C8 = D_ctx_801784FC = D_ctx_801784C8 = 110.0f;
        if (gGameFrameCount & 0x20) {
            D_ctx_801784D4 = D_ctx_801784C8 = D_ctx_801784C8 = D_ctx_801784FC = D_ctx_801784C8 = 90.0f;
        }
        D_ctx_801784E8 = D_ctx_80178510 = D_ctx_80178538 = 1.0f;
    }
    Math_SmoothStepToAngle(&D_ctx_801784B8, D_ctx_801784C4, 1.0f, D_ctx_801784E8, 0.0f);
    Math_SmoothStepToAngle(&D_ctx_801784BC, D_ctx_801784C8, 1.0f, D_ctx_801784E8, 0.0f);
    Math_SmoothStepToAngle(&D_ctx_801784C0, D_ctx_801784CC, 1.0f, D_ctx_801784E8, 0.0f);

    if (gLight2R < D_ctx_80178570) {
        gLight2R += D_ctx_80178540;
        if (D_ctx_80178570 < gLight2R) {
            gLight2R = D_ctx_80178570;
        }
    }
    if (D_ctx_80178570 < gLight2R) {
        gLight2R -= D_ctx_80178540;
        if (gLight2R < D_ctx_80178570) {
            gLight2R = D_ctx_80178570;
        }
    }
    if (gLight2G < D_ctx_80178574) {
        gLight2G += D_ctx_80178540;
        if (D_ctx_80178574 < gLight2G) {
            gLight2G = D_ctx_80178574;
        }
    }
    if (D_ctx_80178574 < gLight2G) {
        gLight2G -= D_ctx_80178540;
        if (gLight2G < D_ctx_80178574) {
            gLight2G = D_ctx_80178574;
        }
    }
    if (gLight2B < D_ctx_80178578) {
        gLight2B += D_ctx_80178540;
        if (D_ctx_80178578 < gLight2B) {
            gLight2B = D_ctx_80178578;
        }
    }
    if (D_ctx_80178578 < gLight2B) {
        gLight2B -= D_ctx_80178540;
        if (gLight2B < D_ctx_80178578) {
            gLight2B = D_ctx_80178578;
        }
    }
    Math_SmoothStepToAngle(&D_ctx_801784EC, D_ctx_801784F8, 1.0f, D_ctx_80178510, 0.0f);
    Math_SmoothStepToAngle(&D_ctx_801784F0, D_ctx_801784FC, 1.0f, D_ctx_80178510, 0.0f);
    Math_SmoothStepToAngle(&D_ctx_801784F4, D_ctx_80178500, 1.0f, D_ctx_80178510, 0.0f);
    D_ctx_801784F8 = D_ctx_801784C4 = D_ctx_801784D0;
    D_ctx_801784FC = D_ctx_801784C8 = D_ctx_801784D4;
    D_ctx_80178500 = D_ctx_801784CC = D_ctx_801784D8;
    D_ctx_801784E8 = 5.0f;
    D_ctx_80178570 = gLight1R;
    D_ctx_80178574 = gLight1G;
    D_ctx_80178578 = gLight1B;
    pad = player->unk_034;
    Matrix_RotateZ(gCalcMatrix, M_DTOR * pad, 0);
    Matrix_RotateX(gCalcMatrix, -player->unk_05C, 1);
    Matrix_RotateY(gCalcMatrix, player->unk_058, 1);
    Matrix_Push(&gCalcMatrix);
    Matrix_RotateX(gCalcMatrix, M_DTOR * D_ctx_801784B8, 1);
    Matrix_RotateY(gCalcMatrix, M_DTOR * D_ctx_801784BC, 1);
    Matrix_RotateZ(gCalcMatrix, M_DTOR * D_ctx_801784C0, 1);
    sp44.x = 0.0f;
    sp44.y = 0.0f;
    sp44.z = 100.0f;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp44, &sp38);
    gLight1x = sp38.x;
    gLight1y = sp38.y;
    gLight1z = sp38.z;
    Matrix_Pop(&gCalcMatrix);
    Matrix_RotateX(gCalcMatrix, M_DTOR * D_ctx_801784EC, 1);
    Matrix_RotateY(gCalcMatrix, M_DTOR * D_ctx_801784F0, 1);
    Matrix_RotateZ(gCalcMatrix, M_DTOR * D_ctx_801784F4, 1);
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp44, &sp38);
    gLight2x = sp38.x;
    gLight2y = sp38.y;
    gLight2z = sp38.z;
}

void Play_UpdateLevel(void) {
#ifdef AVOID_UB
    s32 var_v0_2 = 0;
    s32 sp40;
    f32 sp3C;
    u8 var_a0;
    u8 sp3A = 0;
#else
    s32 var_v0_2;
    s32 sp40;
    f32 sp3C;
    u8 var_a0;
    u8 sp3A;
#endif

    switch (gCurrentLevel) {
        case LEVEL_TRAINING:
            if (gLevelMode == LEVELMODE_ALL_RANGE) {
                Training_8019949C();
            }
            break;
        case LEVEL_VERSUS:
            func_versus_800C26C8();
            D_ctx_80177844++;
            if ((D_ctx_80177844 == 200) && (gLaserStrength[0] == LASERS_SINGLE) &&
                (gLaserStrength[1] == LASERS_SINGLE) && (gLaserStrength[2] == LASERS_SINGLE) &&
                (gLaserStrength[3] == LASERS_SINGLE)) {
                func_play_800B852C(OBJ_ITEM_LASERS, &gItems[0]);
            }
            if ((D_ctx_80177844 == 400) && (gBombCount[0] == 0) && (gBombCount[1] == 0) && (gBombCount[2] == 0) &&
                (gBombCount[3] == 0)) {
                func_play_800B852C(OBJ_ITEM_BOMB, &gItems[1]);
            }
            if (D_ctx_80177844 == 500) {
                D_ctx_80177844 = 0;
            }
            break;
        case LEVEL_VENOM_2:
            if ((gPlayer[0].state_1C8 != PLAYERSTATE_1C8_7) && (gLevelStage == 2)) {
                gPlayer[0].state_1C8 = PLAYERSTATE_1C8_7;
                gPlayer[0].unk_1D0 = 0;
                gPlayer[0].unk_234 = 1;
                gPlayer[0].pos.z = 15000.0f;
                func_play_800B7184(gPlayer, 1);
                gFillScreenAlpha = 255;
                gFillScreenAlphaStep = 255;
                gFillScreenAlphaTarget = 255;

                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
            }
            break;
        case LEVEL_VENOM_ANDROSS:
            Andross_8018BDD8();
            gGroundLevel = -25000.0f;
            gPlayer[0].unk_0A0 = 612.0f;
            gPlayer[0].unk_0A4 = -544.0f;
            if (D_Timer_80177B44 != 0) {
                D_Timer_80177B44--;
                if (D_Timer_80177B44 == 0) {
                    Andross_80189214();
                }
            }
            break;
        case LEVEL_METEO:
            Texture_Scroll(D_102FF08, 8, 8, 1);
            /* fallthrough */
        case LEVEL_SECTOR_X:
            if (gLevelStage == 1) {
                gBlurAlpha = 128;
                if (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_7) {
                    Math_SmoothStepToF(&D_bg_8015F960, 0.0f, 1.0f, 1.0f, 0.0f);
                } else {
                    Math_SmoothStepToF(&D_bg_8015F960, 128.0f, 1.0f, 1.0f, 0.0f);
                }
            }
            if ((gCurrentLevel == LEVEL_SECTOR_X) && (gLevelStage == 0) && (gRingPassCount == 4)) {
                gRingPassCount++;
                gPlayer[0].state_1C8 = PLAYERSTATE_1C8_8;
                gPlayer[0].unk_1D0 = 0;
                gOverlayStage = 1;
                AUDIO_PLAY_SFX(0x1900602A, gDefaultSfxSource, 0);
                gNextPlanetPath = 2;
                D_play_800D3180[gCurrentLevel] = 1;
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
            func_play_800A3FEC();

            for (D_ctx_80177CE8; D_ctx_80177CE8 >= 10.0f; D_ctx_80177CE8 -= 10.0f) {
                Texture_Scroll(D_SO_6005710, 32, 32, 1);
            }
            if (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_6) {
                Texture_Scroll(D_SO_6005710, 32, 32, 1);
            }
            Texture_Mottle(D_SO_601E1E8, D_SO_6020F60, 3);

            if (gPlayer[0].pos.y > 600.0f) {
                var_v0_2 = 8 - 1;
                sp3A = 5;
            } else if (gPlayer[0].pos.y > 500.0f) {
                var_v0_2 = 8 - 1;
                sp3A = 4;
            } else if (gPlayer[0].pos.y > 400.0f) {
                var_v0_2 = 4 - 1;
                sp3A = 3;
            } else if (gPlayer[0].pos.y > 300.0f) {
                var_v0_2 = 4 - 1;
                sp3A = 2;
            } else if (gPlayer[0].pos.y > 200.0f) {
                var_v0_2 = 2 - 1;
                sp3A = 1;
            } else if (gPlayer[0].pos.y > 100.0f) {
                var_v0_2 = 1 - 1;
                sp3A = 0;
            } else {
                var_v0_2 = 1 - 1;
#ifdef AVOID_UB
                sp3A = 0;
#endif
            }

            if ((gPlayer[0].state_1C8 == PLAYERSTATE_1C8_3) && !(gGameFrameCount & var_v0_2)) {
                gPlayer[0].shields--;
                if (gPlayer[0].shields <= 0) {
                    gPlayer[0].shields = 0;
                }
                if (gPlayer[0].heal == 0) {
                    if (gPlayer[0].shields == 50) {
                        AUDIO_PLAY_SFX(0x49008011, gDefaultSfxSource, 4);
                    } else if (gPlayer[0].shields == 100) {
                        AUDIO_PLAY_SFX(0x49008010, gDefaultSfxSource, 4);
                    }
                }
            }
            var_a0 = MIN(gPlayer[0].shields, 255);
            func_8001D1C8(var_a0, sp3A);
            if (((gGameFrameCount % 8) == 0) && (gPlayer[0].state_1C8 != PLAYERSTATE_1C8_7)) {
                Solar_8019E8B8(RAND_FLOAT_CENTERED(6000.0f), -80.0f,
                               gPlayer[0].unk_138 + (RAND_FLOAT(2000.0f) + -6000.0f),
                               RAND_FLOAT(10.0f) + 20.0f); // check
            }
            func_hud_8008C104(D_SO_60229A4, D_SO_6010198);
            if (gPlayer[0].shields == 0) {
                D_ctx_80177B4C = 1;
            }
            break;
        case LEVEL_ZONESS:
            func_play_800A3FEC();
            for (D_ctx_80177CE8; D_ctx_80177CE8 >= 20.0f; D_ctx_80177CE8 -= 20.0f) {
                Texture_Scroll(D_ZO_602C2CC, 32, 32, 1);
            }
            if (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_6) {
                Texture_Scroll(D_ZO_602C2CC, 32, 32, 1);
            }
            func_hud_8008C104(D_ZO_602C2CC, D_ZO_600D990);
            if (func_play_800A73E4(&sp3C, &sp40, gPlayer[0].camEye.x, gPlayer[0].camEye.y,
                                   gPlayer[0].camEye.z - D_ctx_80177D20)) {
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
        Player_Update1(&gPlayer[i]);
    }
    Object_Update();
    PlayerShot_Update();
    BonusText_Update();
    for (i = 0; i < gCamCount; i++) {
        gPlayer[i].num = gPlayerNum = i;
        Player_Update2(&gPlayer[i]);
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

u8 D_800D317C = 255;

void func_play_800B852C(ObjectId objId, Item* item) {
    u8 sp1F = (u8) RAND_FLOAT(5.0f);

    if (D_800D317C == sp1F) {
        D_ctx_80177844 -= 1;
    } else {
        D_800D317C = sp1F;
        if (item->obj.status == OBJ_FREE) {
            Item_Initialize(item);
            item->obj.status = OBJ_INIT;
            item->obj.pos.x = gObjects58[sp1F].obj.pos.x;
            item->obj.pos.y = gObjects58[sp1F].obj.pos.y;
            item->obj.pos.z = gObjects58[sp1F].obj.pos.z;
            item->obj.id = objId;
            Object_SetInfo(&item->info, item->obj.id);
        }
    }
}

void func_play_800B86A4(f32* arg0) {
    *arg0 += D_ctx_80177D20 + 15000.0f;
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
    Math_SmoothStepToF(&D_game_80161A3C, sp34, 0.1f, 5.0f, 0.0f);
    if (gChangeTo360) {
        gChangeTo360 = false;
        gLevelMode = LEVELMODE_ALL_RANGE;
        if (gCurrentLevel != LEVEL_VENOM_ANDROSS) {
            MEM_ARRAY_ALLOCATE(gObjects58, 200);
        }
        for (i = 0; i < 200; i++) {
            gObjects58[i].obj.status = OBJ_FREE;
        }
        func_play_800A6148();
        if (gCurrentLevel == LEVEL_CORNERIA) {
            func_play_800A5338();
        } else if (gCurrentLevel == LEVEL_SECTOR_Y) {
            func_play_800A55B0();
        } else if (gCurrentLevel == LEVEL_VENOM_ANDROSS) {
            func_play_800A57E0();
        } else if (gCurrentLevel == LEVEL_TRAINING) {
            Training_80198C50();
        }
        func_play_800B86A4(&gPlayer[0].pos.z);
        func_play_800B86A4(&gPlayer[0].unk_138);
        gPlayer[0].camEye.z += 15000.0f;
        gPlayer[0].camAt.z += 15000.0f;
        gPlayer[0].unk_144 = gPlayer[0].unk_140 = D_ctx_80177D08 = D_ctx_80177D20 = 0.0f;
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
            D_800D2F5C = gVolumeSettings[0];
            D_800D2F60 = gVolumeSettings[1];
            D_800D2F64 = gVolumeSettings[2];
            gPlayState = PLAY_UPDATE;
            break;
        case PLAY_UPDATE:
            if ((gLevelStatusScreenTimer != 0) || (gLevelClearScreenTimer != 0)) {
                gPauseEnabled = false;
            } else {
                gPauseEnabled = true;
            }
            gDrawMode = DRAW_PLAY;
            Play_Update();
            if ((gControllerPress[gMainController].button & START_BUTTON) &&
                (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_2) &&
                gSaveFile.save.data.planet[D_800D2F6C[gCurrentLevel]].normalClear) {
                Audio_ClearVoice();
                Audio_SetBaseSfxReverb(0);
                func_play_800A6148();
                for (i = 0; i < gCamCount; i++) {
                    Audio_KillSfxBySource(gPlayer[i].sfxSource);
                    func_8001CA24(i);
                }
                gPlayState = PLAY_INIT;
                gDrawMode = gVersusMode = 0;
                gCamCount = 1;
                gBgColor = 0;
                gCsFrameCount = gLevelClearScreenTimer = gLevelStatusScreenTimer = gRadioState = 0;
                D_ctx_8017782C = 0;
            }
            if (gVersusMode) {
                func_versus_800C1E9C();
            }
            if ((gControllerPress[gMainController].button & START_BUTTON) && gPauseEnabled) {
                func_8001D638(1);
                gPlayState = PLAY_PAUSE;
                D_ctx_80177868 = 4;
                D_ctx_80178484 = 100000;
            }
            break;
        case PLAY_PAUSE:
            if (!gVersusMode) {
                if ((gControllerPress[gMainController].button & R_TRIG) && (gPlayer[0].form != FORM_BLUE_MARINE) &&
                    (gPlayer[0].state_1C8 != PLAYERSTATE_1C8_0)) {
                    if (gShowCrosshairs[0] = 1 - gShowCrosshairs[0]) {
                        AUDIO_PLAY_SFX(0x49000019, gDefaultSfxSource, 4);
                    } else {
                        AUDIO_PLAY_SFX(0x4900101A, gDefaultSfxSource, 4);
                    }
                }
            } else {
                for (i = 0; i < 4; i++) {
                    if ((gControllerPress[i].button & R_TRIG) && (gPlayer[i].form != FORM_ON_FOOT)) {
                        if (gShowCrosshairs[i] = 1 - gShowCrosshairs[i]) {
                            func_enmy_80060F30(gPlayer[i].sfxSource, 0x49000019, i);
                        } else {
                            func_enmy_80060F30(gPlayer[i].sfxSource, 0x4900101A, i);
                        }
                    }
                }
            }
            if ((D_ctx_80177868 == 4) && (gControllerPress[gMainController].button & START_BUTTON) &&
                (gPauseEnabled != 0)) {
                func_8001D638(0);
                gPlayState = PLAY_UPDATE;
                gDrawMode = DRAW_PLAY;
            }
            gPauseEnabled = 1;
            break;
    }
}
