#include "global.h"
#include "assets/ast_corneria.h"
#include "assets/ast_sector_x.h"
#include "assets/ast_sector_y.h"
#include "assets/ast_sector_z.h"
#include "assets/ast_venom_1.h"
#include "assets/ast_venom_2.h"
#include "assets/ast_katina.h"
#include "assets/ast_fortuna.h"
#include "assets/ast_aquas.h"
#include "assets/ast_bolse.h"
#include "assets/ast_meteo.h"
#include "assets/ast_solar.h"
#include "assets/ast_macbeth.h"
#include "assets/ast_titania.h"
#include "assets/ast_andross.h"
#include "assets/ast_area_6.h"
#include "assets/ast_training.h"
#include "assets/ast_versus.h"
#include "assets/ast_zoness.h"

s32 D_enmy_Timer_80161670[4];
s32 gLastPathChange;
u8 gMissedZoSearchlight;

ObjectInit* gLevelObjectInits[] = {
    D_CO_60371A4, D_ME_6026CC4, D_SX_602A164,      D_A6_6023F64, D_A6_60287A4, D_SY_602E4F4,  D_VE1_6007E74,
    D_SO_601F234, D_ZO_6026714, D_ANDROSS_C035154, D_TR_6006AA4, D_MA_6031000, D_TI_6006C60,  D_AQ_602E5C8,
    D_FO_600EAD4, NULL,         D_KA_6011044,      D_BO_600FF74, D_SZ_6006EB4, D_VE2_6014D94, D_versus_302DE3C,
};
static s32 D_enmy_800CFDF4[] = {
    /*  0 */ OBJ_SCENERY_0,
    /*  1 */ OBJ_ITEM_SILVER_RING,
    /*  2 */ OBJ_ITEM_SILVER_RING,
    /*  3 */ OBJ_ITEM_SILVER_RING,
    /*  4 */ OBJ_ITEM_SILVER_RING,
    /*  5 */ OBJ_ITEM_BOMB,
    /*  6 */ OBJ_ITEM_BOMB,
    /*  7 */ OBJ_ITEM_BOMB,
    /*  8 */ OBJ_ITEM_BOMB,
    /*  9 */ OBJ_ITEM_LASERS,
    /* 10 */ OBJ_ITEM_LASERS,
    /* 11 */ OBJ_ITEM_LASERS,
    /* 12 */ OBJ_ITEM_LASERS,
    /* 13 */ OBJ_ITEM_1UP,
    /* 14 */ OBJ_ITEM_GOLD_RING,
    /* 15 */ OBJ_ITEM_GOLD_RING,
    /* 16 */ OBJ_ITEM_GOLD_RING,
    /* 17 */ OBJ_ITEM_GOLD_RING,
    /* 18 */ OBJ_ITEM_GOLD_RING,
    /* 19 */ OBJ_ITEM_LASERS,
    /* 20 */ OBJ_ITEM_BOMB,
    /* 21 */ OBJ_ITEM_SILVER_RING,
    /* 22 */ OBJ_ITEM_SILVER_RING,
    /* 23 */ OBJ_ITEM_WING_REPAIR,
    /* 24 */ OBJ_SCENERY_0,
    /* 25 */ OBJ_ITEM_SILVER_STAR,
};
static f32 D_enmy_800CFE5C[] = {
    0.0f, 1.0f, 0.5f, 0.33f, 0.25f, 1.0f,  0.5f,  0.33f, 0.25f, 1.0f, 0.5f, 0.33f, 0.25f,
    1.0f, 1.0f, 1.0f, 1.0f,  1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, 0.1f, 1.0f, 1.0f,  1.0f,
};
static Vec3f D_enmy_800CFEC4[] = {
    { 0.0f, 0.0f, 50.0f }, { -50.0f, 0.0f, 0.0f }, { 50.0f, 0.0f, 0.0f },
    { 0.0f, 50.0f, 0.0f }, { 0.0f, 0.0f, -50.0f }, { 0.0f, -50.0f, 0.0f },
};
static Vec3f D_enmy_800CFF0C[] = {
    { 0.0f, 0.0f, 0.0f },   { 0.0f, -90.0f, 0.0f }, { 0.0f, 90.0f, 0.0f },
    { -90.0f, 0.0f, 0.0f }, { 0.0f, 180.0f, 0.0f }, { 90.0f, 0.0f, 0.0f },
};
u32 gWarpRingSfx[] = {
    NA_SE_WARP_RING_1, NA_SE_WARP_RING_2, NA_SE_WARP_RING_3, NA_SE_WARP_RING_4, NA_SE_WARP_RING_5,
    NA_SE_WARP_RING_6, NA_SE_WARP_RING_7, NA_SE_WARP_RING_7, NA_SE_WARP_RING_7,
};

void Object_PlayerSfx(f32* pos, u32 sfxId, s32 playerNum) {
    PRINTF("CHIME SET \n");
    PRINTF("BOMB SET 1\n");
    PRINTF("BOMB SET 2\n");
    PRINTF("center_X        %f\n");
    PRINTF("Enm->obj.pos.x  %f\n");
    if (!gVersusMode) {
        AUDIO_PLAY_SFX(sfxId, gDefaultSfxSource, 4);
    } else {
        AUDIO_PLAY_SFX(sfxId, pos, playerNum);
    }
}

void Object_Kill(Object* obj, f32* sfxSrc) {
    obj->status = OBJ_FREE;
    Audio_KillSfxBySource(sfxSrc);
}

bool func_enmy_80060FE4(Vec3f* arg0, f32 arg1) {
    Vec3f sp2C;
    Vec3f sp20;

    if ((gLevelMode != LEVELMODE_ALL_RANGE) && (gPlayer[0].state_1C8 != PLAYERSTATE_1C8_LEVEL_INTRO)) {
        return true;
    }
    Matrix_RotateY(gCalcMatrix, gPlayer[gPlayerNum].camYaw, MTXF_NEW);
    sp2C.x = arg0->x - gPlayer[gPlayerNum].cam.eye.x;
    sp2C.y = 0.0f;
    sp2C.z = arg0->z - gPlayer[gPlayerNum].cam.eye.z;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp2C, &sp20);

    if ((sp20.z < 1000.0f) && (arg1 < sp20.z) && (fabsf(sp20.x) < (fabsf(sp20.z * 0.5f) + 2000.0f))) {
        return true;
    }
    return false;
}

bool func_enmy_80061148(Vec3f* arg0, f32 arg1) {
    Vec3f sp2C;
    Vec3f sp20;

    if (gLevelMode != LEVELMODE_ALL_RANGE) {
        return true;
    }
    if (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_LEVEL_COMPLETE) {
        return func_enmy_80060FE4(arg0, arg1);
    }
    Matrix_RotateY(gCalcMatrix, gPlayer[gPlayerNum].camYaw, MTXF_NEW);
    sp2C.x = arg0->x - gPlayer[gPlayerNum].cam.eye.x;
    sp2C.y = 0.0f;
    sp2C.z = arg0->z - gPlayer[gPlayerNum].cam.eye.z;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp2C, &sp20);

    if ((sp20.z < 0.0f) && (arg1 < sp20.z) && (fabsf(sp20.x) < (fabsf(sp20.z * 0.5f) + 500.0f))) {
        return true;
    }
    return false;
}

void Object_SetInfo(ObjectInfo* info, u32 objId) {
    *info = gObjectInfo[objId];
    info->hitbox = LOAD_ASSET(gObjectInfo[objId].hitbox);
    if (gLevelMode == LEVELMODE_UNK_2) {
        info->cullDistance += 200.0f;
    }
}

void Scenery_Initialize(Scenery* scenery) {
    s32 i;
    u8* ptr = (u8*) scenery;

    for (i = 0; i < sizeof(Scenery); i++, ptr++) {
        *ptr = 0;
    }
}

void Sprite_Initialize(Sprite* sprite) {
    memset(sprite, 0, sizeof(Sprite));
}

void Actor_Initialize(Actor* actor) {
    memset(actor, 0, sizeof(Actor));
    actor->scale = 1.0f;
}

void Boss_Initialize(Boss* boss) {
    s32 i;
    u8* ptr = (u8*) boss;

    for (i = 0; i < sizeof(Boss); i++, ptr++) {
        *ptr = 0;
    }
    boss->scale = 1.0f;
}

void Item_Initialize(Item* item) {
    s32 i;
    u8* ptr = (u8*) item;

    for (i = 0; i < sizeof(Item); i++, ptr++) {
        *ptr = 0;
    }
}

void Effect_Initialize(Effect* effect) {
    s32 i;
    u8* ptr = (u8*) effect;

    for (i = 0; i < sizeof(Effect); i++, ptr++) {
        *ptr = 0;
    }
    effect->scale2 = 1.0f;
}

void Scenery_Load(Scenery* scenery, ObjectInit* objInit) {
    Scenery_Initialize(scenery);
    scenery->obj.status = OBJ_INIT;
    scenery->obj.pos.z = -objInit->zPos1;
    scenery->obj.pos.z += -3000.0f + objInit->zPos2;
    scenery->obj.pos.x = objInit->xPos;
    scenery->obj.pos.y = objInit->yPos;
    scenery->obj.rot.x = objInit->rot.x;
    scenery->obj.rot.y = objInit->rot.y;
    scenery->obj.rot.z = objInit->rot.z;
    scenery->obj.id = objInit->id;
    Object_SetInfo(&scenery->info, scenery->obj.id);
}

void Sprite_Load(Sprite* sprite, ObjectInit* objInit) {
    Sprite_Initialize(sprite);
    sprite->obj.status = OBJ_INIT;
    sprite->obj.pos.z = -objInit->zPos1;
    sprite->obj.pos.z += -3000.0f + objInit->zPos2;
    sprite->obj.pos.x = objInit->xPos;
    sprite->obj.pos.y = objInit->yPos;
    sprite->obj.rot.y = objInit->rot.y;
    sprite->obj.rot.x = objInit->rot.x;
    sprite->obj.rot.z = objInit->rot.z;
    sprite->obj.id = objInit->id;
    Object_SetInfo(&sprite->info, sprite->obj.id);
}

void Actor_Load(Actor* actor, ObjectInit* objInit) {
    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.pos.z = -objInit->zPos1;
    actor->obj.pos.z += -3000.0f + objInit->zPos2;
    actor->obj.pos.x = objInit->xPos;
    actor->obj.pos.y = objInit->yPos;
    actor->obj.rot.y = objInit->rot.y;
    actor->obj.rot.x = objInit->rot.x;
    actor->obj.rot.z = objInit->rot.z;
    actor->obj.id = objInit->id;
    Object_SetInfo(&actor->info, actor->obj.id);
}

void Boss_Load(Boss* boss, ObjectInit* objInit) {
    Boss_Initialize(boss);
    boss->obj.status = OBJ_INIT;
    boss->obj.pos.z = -objInit->zPos1;
    boss->obj.pos.z += -3000.0f + objInit->zPos2;
    boss->obj.pos.x = objInit->xPos;
    boss->obj.pos.y = objInit->yPos;
    boss->obj.rot.y = objInit->rot.y;
    boss->obj.rot.x = objInit->rot.x;
    boss->obj.rot.z = objInit->rot.z;
    boss->obj.id = objInit->id;
    Object_SetInfo(&boss->info, boss->obj.id);
}

void Item_Load(Item* item, ObjectInit* objInit) {
    Item_Initialize(item);
    item->obj.status = OBJ_INIT;
    item->obj.pos.z = -objInit->zPos1;
    item->obj.pos.z += -3000.0f + objInit->zPos2;
    item->obj.pos.x = objInit->xPos;
    item->obj.pos.y = objInit->yPos;
    item->obj.rot.y = objInit->rot.y;
    item->obj.rot.x = objInit->rot.x;
    item->obj.rot.z = objInit->rot.z;
    item->obj.id = objInit->id;
    item->width = 1.0f;
    Object_SetInfo(&item->info, item->obj.id);
}

void func_enmy_80061958(Effect* effect, f32 xPos, f32 yPos, f32 zPos) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = OBJ_EFFECT_346;
    effect->timer_50 = 50;
    effect->scale2 = 0.2f;
    if (gCurrentLevel == LEVEL_AQUAS) {
        effect->timer_50 = 200;
        effect->scale2 = 0.3f;
        effect->scale1 = RAND_FLOAT(255.0f);
    }
    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;
    effect->obj.rot.z = RAND_FLOAT(360.0f);
    Object_SetInfo(&effect->info, effect->obj.id);
    if (gLevelType == LEVELTYPE_PLANET) {
        effect->info.cullDistance = 100.0f;
    }
}

void func_enmy_80061A4C(void) {
    s32 i;
    f32 x;
    f32 y;
    f32 z;

    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            x = gPlayer[0].pos.x + RAND_FLOAT_CENTERED(400.0f) + (5.0f * gPlayer[0].vel.x);
            y = gPlayer[0].pos.y + RAND_FLOAT_CENTERED(400.0f) + (5.0f * gPlayer[0].vel.y);
            z = -gPathProgress - 500.0f;
            if (gPathVelZ < 0.0f) {
                z = -gPathProgress + 500.0f;
            }
            func_enmy_80061958(&gEffects[i], x, y, z);
            break;
        }
    }
}

void func_enmy_80061B68(void) {
    s32 i;
    f32 x;
    f32 y;
    f32 z;

    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {

            x = gPlayer[0].pos.x + RAND_FLOAT_CENTERED(2000.0f) + (5.0f * gPlayer[0].vel.x);
            y = 0;
            while (y <= gGroundHeight) {
                y = gPlayer[0].pos.y + RAND_FLOAT_CENTERED(2000.0f) + (5.0f * gPlayer[0].vel.y);
            }
            z = -gPathProgress - 3000.0f;
            if (gPathVelZ < 0.0f) {
                z = -gPathProgress + 1000.0f;
            }
            func_enmy_80061958(&gEffects[i], x, y, z);
            break;
        }
    }
}

void func_enmy_80061CD0(void) {
    s32 i;
    f32 x;
    f32 y;
    f32 z;

    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            x = gPlayer[gPlayerNum].pos.x + RAND_FLOAT_CENTERED(3000.0f) + (5.0f * gPlayer[gPlayerNum].vel.x);
            y = gPlayer[gPlayerNum].pos.y + 1000.0f + RAND_FLOAT_CENTERED(500.0f) + (5.0f * gPlayer[gPlayerNum].vel.y);
            z = -gPathProgress - RAND_FLOAT(2000.0f);
            if (gPathVelZ < 0.0f) {
                z = -gPathProgress + 1000.0f;
            }
            func_enmy_80061958(&gEffects[i], x, y, z);
            break;
        }
    }
}

void func_enmy_80061E48(Actor* actor, f32 xPos, f32 yPos, f32 zPos) {
    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_181;
    if (Rand_ZeroOne() < 0.5f) {
        actor->obj.id = OBJ_ACTOR_186;
    }
    if (Rand_ZeroOne() < 0.5f) {
        actor->obj.id = OBJ_ACTOR_182;
    }
    actor->obj.pos.x = xPos;
    actor->obj.pos.y = yPos;
    actor->obj.pos.z = zPos;
    actor->vel.z = 10.0f;
    Object_SetInfo(&actor->info, actor->obj.id);
}

void ActorEvent_Load(Actor* actor, ObjectInit* objInit, s32 index) {
    Vec3f sp24;

    Actor_Initialize(actor);
    actor->obj.status = OBJ_ACTIVE;
    actor->index = index;
    actor->obj.pos.z = -objInit->zPos1;
    actor->obj.pos.z += -3000.0f + objInit->zPos2;
    actor->obj.pos.x = objInit->xPos;
    actor->obj.pos.y = objInit->yPos;
    actor->obj.rot.y = actor->rot_0F4.y = objInit->rot.y;
    actor->obj.rot.x = actor->rot_0F4.x = objInit->rot.x;
    actor->rot_0F4.z = objInit->rot.z;
    actor->obj.id = OBJ_ACTOR_EVENT;
    actor->timer_0C2 = 10;
    actor->eventType = EVID_FFF;
    actor->aiType = objInit->id - ACTOR_EVENT_ID;

    Object_SetInfo(&actor->info, actor->obj.id);
    actor->info.cullDistance = 3000.0f;
    actor->fwork[25] = 20000.0f;
    actor->iwork[1] = gPrevEventActorIndex;
    actor->iwork[10] = gActors[gPrevEventActorIndex].aiType;
    actor->fwork[22] = gArwingSpeed;
    Matrix_RotateZ(gCalcMatrix, -gFormationInitRot.z * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -gFormationInitRot.x * M_DTOR, MTXF_APPLY);
    Matrix_RotateY(gCalcMatrix, -gFormationInitRot.y * M_DTOR, MTXF_APPLY);
    sp24.x = actor->obj.pos.x - gFormationInitPos.x;
    sp24.y = actor->obj.pos.y - gFormationInitPos.y;
    sp24.z = actor->obj.pos.z - gFormationInitPos.z;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp24, &actor->vwork[28]);
    actor->iwork[9] = gFormationLeaderIndex;
    gPrevEventActorIndex = index;
    Actor_Update(actor);
}

void Object_Load(ObjectInit* objInit, f32 xMax, f32 xMin, f32 yMax, f32 yMin) {
    s32 i;

    if ((xMax > objInit->xPos - gPlayer[0].xPath) && (objInit->xPos - gPlayer[0].xPath > xMin) &&
        (yMax > objInit->yPos - gPlayer[0].yPath) && (objInit->yPos - gPlayer[0].yPath > yMin)) {
        if (objInit->id < OBJ_SCENERY_MAX) {
            for (i = 0; i < ARRAY_COUNT(gScenery); i++) {
                if (gScenery[i].obj.status == OBJ_FREE) {
                    Scenery_Load(&gScenery[i], objInit);
                    break;
                }
            }
        }
        if ((objInit->id >= OBJ_SPRITE_START) && (objInit->id < OBJ_SPRITE_MAX)) {
            for (i = 0; i < ARRAY_COUNT(gSprites); i++) {
                if (gSprites[i].obj.status == OBJ_FREE) {
                    Sprite_Load(&gSprites[i], objInit);
                    break;
                }
            }
        }
        if ((objInit->id >= OBJ_ACTOR_START) && (objInit->id < OBJ_ACTOR_MAX)) {
            if ((objInit->id == OBJ_ACTOR_267) || (objInit->id == OBJ_ACTOR_254)) {
                for (i = ARRAY_COUNT(gActors) - 1; i >= 0; i--) {
                    if (gActors[i].obj.status == OBJ_FREE) {
                        Actor_Load(&gActors[i], objInit);
                        break;
                    }
                }
            } else if (objInit->id == OBJ_ACTOR_TEAM_BOSS) {
                for (i = 0; i < 3; i++) {
                    if (gActors[i].obj.status == OBJ_FREE) {
                        Actor_Load(&gActors[i], objInit);
                        break;
                    }
                }
            } else {
                for (i = 4; i < ARRAY_COUNT(gActors); i++) {
                    if (gActors[i].obj.status == OBJ_FREE) {
                        Actor_Load(&gActors[i], objInit);
                        break;
                    }
                }
            }
        }
        if ((objInit->id >= OBJ_BOSS_START) && (objInit->id < OBJ_BOSS_MAX)) {
            for (i = 0; i < ARRAY_COUNT(gBosses); i++) {
                if (gBosses[i].obj.status == OBJ_FREE) {
                    Boss_Load(&gBosses[i], objInit);
                    break;
                }
            }
        }
        if ((objInit->id >= OBJ_ITEM_START) && (objInit->id < OBJ_ITEM_MAX)) {
            for (i = 0; i < ARRAY_COUNT(gItems); i++) {
                if (gItems[i].obj.status == OBJ_FREE) {
                    Item_Load(&gItems[i], objInit);
                    break;
                }
            }
        }
        if (objInit->id >= OBJ_EFFECT_START && objInit->id <= OBJ_ID_MAX) {
            switch (objInit->id) {
                case OBJ_UNK_403:
                    D_MA_801BA1E8 = 99;
                    break;
                case OBJ_UNK_404:
                    D_MA_801BA1E8 = 0;
                    break;
                case OBJ_UNK_405:
                    D_MA_801BA1E8 = 98;
                    break;
                case OBJ_UNK_402:
                    D_Andross_801A7F78 = objInit->rot.z * 0.1f;
                    D_Andross_801A7F60 = -(f32) objInit->rot.x;
                    break;
                case OBJ_UNK_400:
                    gDrawSmallRocks++;
                    break;
                case OBJ_UNK_401:
                    if (gDrawSmallRocks > 0) {
                        gDrawSmallRocks--;
                    }
                    break;
            }
        }
        if (objInit->id > OBJ_ID_MAX) {
            for (i = 0; i < ARRAY_COUNT(gActors); i++) {
                if (gActors[i].obj.status == OBJ_FREE) {
                    ActorEvent_Load(&gActors[i], objInit, i);
                    break;
                }
            }
        }
    }
}

void func_enmy_80062568(void) {
    ObjectInit* objInit;
    s32 var_s0;
    s32 temp = gCurrentLevel; // seems fake
    if (1) {}
    gLevelObjects = LOAD_ASSET(gLevelObjectInits[temp]);
    var_s0 = gSavedObjectLoadIndex - 40;
    objInit = &gLevelObjects[var_s0];

    for (; var_s0 < gSavedObjectLoadIndex; var_s0++, objInit++) {
        Object_Load(objInit, 4000.0f, -4000.0f, 4000.0f, -4000.0f);
    }
}

void Object_LoadLevelObjects(void) {
    ObjectInit* objInit;
    f32 xMax;
    f32 xMin;
    f32 yMax;
    f32 yMin;
    s32 i;
    s32 j;

    if ((gCurrentLevel == LEVEL_METEO) && (gLevelPhase == 1)) {
        gLevelObjects = LOAD_ASSET(D_ME_602B148);
    } else if ((gCurrentLevel == LEVEL_SECTOR_X) && (gLevelPhase == 1)) {
        gLevelObjects = LOAD_ASSET(D_SX_602F18C);
    } else if ((gCurrentLevel == LEVEL_VENOM_ANDROSS) && (gLevelPhase == 1)) {
        gLevelObjects = LOAD_ASSET(D_ANDROSS_C0356A4);
    } else if ((gCurrentLevel == LEVEL_VENOM_1) && (gLevelPhase == 1)) {
        gLevelObjects = LOAD_ASSET(D_VE1_6010088);
    } else {
        gLevelObjects = LOAD_ASSET(gLevelObjectInits[gCurrentLevel]);
    }
    if (gGroundClipMode == 0) {
        for (j = 0; j < gDrawSmallRocks; j++) {
            if (gCurrentLevel == LEVEL_AQUAS) {
                func_enmy_80061B68();
            } else {
                func_enmy_80061A4C();
            }
        }
    }
    if (gCurrentLevel == LEVEL_METEO) {
        yMax = xMax = 10000.0f;
        yMin = xMin = -10000.0f;
    } else if (gCurrentLevel == LEVEL_SECTOR_Y) {
        yMax = xMax = 6000.0f;
        yMin = xMin = -6000.0f;
    } else if (gCurrentLevel == LEVEL_VENOM_1) {
        yMax = xMax = 3500.0f;
        yMin = xMin = -3500.0f;
    } else {
        yMax = xMax = 4000.0f;
        yMin = xMin = -4000.0f;
    }

    if ((gPlayer[0].pathChangeTimer != 0) && (gPlayer[0].pathChangeYaw < 0.0f)) {
        xMax = 10000.0f;
    }
    if ((gPlayer[0].pathChangeTimer != 0) && (gPlayer[0].pathChangeYaw > 0.0f)) {
        xMin = -10000.0f;
    }
    gLastPathChange = 0;

    for (i = 0, objInit = &gLevelObjects[gObjectLoadIndex]; i < 10000; i++, gObjectLoadIndex++, objInit++) {
        if (objInit->id <= OBJ_INVALID) {
            break;
        }
        if (((gPathProgress <= objInit->zPos1) && (objInit->zPos1 <= gPathProgress + 200.0f))) {
            if ((gCurrentLevel == LEVEL_VENOM_1) && (objInit->id >= ACTOR_EVENT_ID)) {
                if (((objInit->rot.y < 180.0f) && (objInit->xPos < gPlayer[0].xPath)) ||
                    ((objInit->rot.y > 180.0f) && (gPlayer[0].xPath < objInit->xPos))) {
                    Object_Load(objInit, xMax, xMin, yMax, yMin);
                }
            } else {
                Object_Load(objInit, xMax, xMin, yMax, yMin);
            }
        } else {
            break;
        }
    }
}

void func_enmy_80062B60(f32 xPos, f32 zPos, s32 state, f32 scale) {
    s32 i;

    if (gLevelType == LEVELTYPE_PLANET) {
        for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
            if (gEffects[i].obj.status == OBJ_FREE) {
                Effect_Initialize(&gEffects[i]);
                gEffects[i].obj.status = OBJ_INIT;
                gEffects[i].obj.id = OBJ_EFFECT_348;
                gEffects[i].obj.pos.x = xPos;
                gEffects[i].obj.pos.y = gGroundHeight + 3.0f;
                gEffects[i].obj.pos.z = zPos;
                gEffects[i].scale2 = 10.0f;
                gEffects[i].scale1 = scale;
                gEffects[i].unk_44 = 80;
                gEffects[i].state = state;
                Object_SetInfo(&gEffects[i].info, gEffects[i].obj.id);
                break;
            }
        }
    }
}

void func_enmy_80062C38(f32 xPos, f32 yPos) {
    s32 i;

    if (gLevelType == LEVELTYPE_PLANET) {
        for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
            if (gEffects[i].obj.status == OBJ_FREE) {
                Effect_Initialize(&gEffects[i]);
                gEffects[i].obj.status = OBJ_INIT;
                gEffects[i].obj.id = OBJ_EFFECT_349;
                gEffects[i].obj.pos.x = xPos;
                gEffects[i].obj.pos.y = gGroundHeight + 3.0f;
                gEffects[i].obj.pos.z = yPos;
                gEffects[i].scale2 = 1.0f;
                gEffects[i].scale1 = 1.3f;
                gEffects[i].unk_44 = 120;
                Object_SetInfo(&gEffects[i].info, gEffects[i].obj.id);
                break;
            }
        }
    }
}

void func_enmy_80062D04(f32 xPos, f32 yPos) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Effect_Initialize(&gEffects[i]);
            gEffects[i].obj.status = OBJ_INIT;
            gEffects[i].obj.id = OBJ_EFFECT_350;
            gEffects[i].obj.pos.x = xPos;
            gEffects[i].obj.pos.y = gGroundHeight + 3.0f;
            gEffects[i].obj.pos.z = yPos;
            gEffects[i].scale2 = 3.0f;
            gEffects[i].scale1 = 2.0f;
            gEffects[i].unk_44 = 120;
            Object_SetInfo(&gEffects[i].info, gEffects[i].obj.id);
            break;
        }
    }
}

bool Object_CheckHitboxCollision(Vec3f* pos, f32* hitboxData, Object* obj, f32 xRot, f32 yRot, f32 zRot) {
    s32 i;
    Vec3f hitRot;
    Vec3f hitPos;
    f32 rotate;
    s32 count;
    Vec3f sp80;
    Vec3f sp74;
    Hitbox* hitbox;

    count = *hitboxData;
    if (count != 0) {
        hitboxData++;
        for (i = 0; i < count; i++, hitboxData += 6) {
            rotate = 0.0f;
            hitRot.x = hitRot.y = hitRot.z = 0.0f;
            if (*hitboxData >= HITBOX_SHADOW) {
                return false;
            }
            if (*hitboxData == HITBOX_ROTATED) {
                rotate = 1.0f;
                hitRot.x = hitboxData[1];
                hitRot.y = hitboxData[2];
                hitRot.z = hitboxData[3];
                hitboxData += 4;
            }
            if ((obj->rot.y == 0.0f) && (obj->rot.z == 0.0f) && (obj->rot.x == 0.0f) && (rotate == 0.0f)) {
                hitPos.x = pos->x;
                hitPos.y = pos->y;
                hitPos.z = pos->z;
            } else {
                Matrix_RotateZ(gCalcMatrix, -hitRot.z * M_DTOR, MTXF_NEW);
                Matrix_RotateX(gCalcMatrix, -hitRot.x * M_DTOR, MTXF_APPLY);
                Matrix_RotateY(gCalcMatrix, -hitRot.y * M_DTOR, MTXF_APPLY);
                Matrix_RotateZ(gCalcMatrix, -obj->rot.z * M_DTOR, MTXF_APPLY);
                Matrix_RotateX(gCalcMatrix, -obj->rot.x * M_DTOR, MTXF_APPLY);
                Matrix_RotateY(gCalcMatrix, -obj->rot.y * M_DTOR, MTXF_APPLY);
                if ((xRot != 0.0f) || (yRot != 0.0f) || (zRot != 0.0f)) {
                    Matrix_RotateZ(gCalcMatrix, -zRot * M_DTOR, MTXF_APPLY);
                    Matrix_RotateX(gCalcMatrix, -xRot * M_DTOR, MTXF_APPLY);
                    Matrix_RotateY(gCalcMatrix, -yRot * M_DTOR, MTXF_APPLY);
                }
                sp80.x = pos->x - obj->pos.x;
                sp80.y = pos->y - obj->pos.y;
                sp80.z = pos->z - obj->pos.z;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp80, &sp74);
                hitPos.x = obj->pos.x + sp74.x;
                hitPos.y = obj->pos.y + sp74.y;
                hitPos.z = obj->pos.z + sp74.z;
            }
            hitbox = (Hitbox*) hitboxData;
            if (((hitbox->z.size + 20.0f) > fabsf(hitbox->z.offset + obj->pos.z - hitPos.z)) &&
                ((hitbox->x.size + 20.0f) > fabsf(hitbox->x.offset + obj->pos.x - hitPos.x)) &&
                ((hitbox->y.size + 10.0f) > fabsf(hitbox->y.offset + obj->pos.y - hitPos.y))) {
                return true;
            }
        }
    }
    return false;
}

bool Object_CheckSingleHitbox(Vec3f* checkPos, f32* hitboxData, Vec3f* hitboxPos) {
    if ((s32) hitboxData[0] != 0) {
        if ((fabsf(hitboxData[1] + hitboxPos->z - checkPos->z) < (hitboxData[2] + 20.0f)) &&
            (fabsf(hitboxData[5] + hitboxPos->x - checkPos->x) < (hitboxData[6] + 20.0f)) &&
            (fabsf(hitboxData[3] + hitboxPos->y - checkPos->y) < (hitboxData[4] + 20.0f))) {
            return true;
        }
    }
    return false;
}

bool Object_CheckPolyCollision(Vec3f* pos, Vec3f* vel, ObjectId objId, Object* obj) {
    Vec3f sp74;
    Vec3f sp68;
    Vec3f relPos;
    Vec3f objPos;
    Vec3f sp44;
    s32 colId;
    s32 pad1[2];
    f32 sp30[2];
    s32 pad2;

    sp74.x = pos->x - obj->pos.x;
    sp74.z = pos->z - obj->pos.z;
    if (((fabsf(sp74.x) < 1100.0f) && (fabsf(sp74.z) < 1100.0f)) || (objId == OBJ_ACTOR_180)) {
        sp74.y = pos->y - obj->pos.y;
        Matrix_RotateY(gCalcMatrix, -obj->rot.y * M_DTOR, MTXF_NEW);
        Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp74, &sp68);
        relPos.x = obj->pos.x + sp68.x;
        relPos.y = obj->pos.y + sp68.y;
        relPos.z = obj->pos.z + sp68.z;
        objPos.x = obj->pos.x;
        objPos.y = obj->pos.y;
        objPos.z = obj->pos.z;
        if ((objId == OBJ_ACTOR_180) || (objId == OBJ_SCENERY_149) || (objId == OBJ_SCENERY_150) ||
            (objId == OBJ_BOSS_FO) || (objId == OBJ_BOSS_SZ) || (objId == OBJ_BOSS_VE2) || (objId == OBJ_BOSS_309) ||
            (objId == OBJ_SCENERY_ME_TUNNEL)) {
            colId = COL1_0;
            if (objId == OBJ_BOSS_VE2) {
                colId = COL1_9;
            }
            if (objId == OBJ_SCENERY_ME_TUNNEL) {
                colId = COL1_1;
            } else if (objId == OBJ_BOSS_FO) {
                colId = COL1_4;
            } else if (objId == OBJ_BOSS_309) {
                colId = COL1_7;
            } else if (objId == OBJ_SCENERY_149) {
                colId = COL1_5;
            } else if (objId == OBJ_SCENERY_150) {
                colId = COL1_6;
            } else if (objId == OBJ_BOSS_SZ) {
                colId = COL1_8;
            }
            if (func_col1_800998FC(&relPos, &objPos, vel, colId, &sp44, sp30) > 0) {
                return true;
            }
        } else {
            colId = COL2_0;
            if (objId == OBJ_SCENERY_2) {
                colId = COL2_2;
            }
            if (objId == OBJ_SCENERY_3) {
                colId = COL2_3;
            }
            if (objId == OBJ_SCENERY_140) {
                colId = COL2_4;
            }
            if (objId == OBJ_SCENERY_141) {
                colId = COL2_6;
            }
            if (objId == OBJ_SCENERY_117) {
                colId = COL2_14;
            } else if ((objId == OBJ_SCENERY_4) || (objId == OBJ_SCENERY_5)) {
                colId = COL2_1;
            }
            if (func_col2_800A3690(&relPos, &objPos, colId, &sp44)) {
                return true;
            }
        }
    }
    return false;
}

s32 Object_CheckCollision(s32 index, Vec3f* pos, Vec3f* vel, s32 mode) {
    Scenery360* scenery360;
    Scenery* scenery;
    Sprite* sprite;
    Boss* boss;
    Actor* actor;
    Vec3f temp;
    s32 i;

    if ((gLevelMode == LEVELMODE_ALL_RANGE) && (gCurrentLevel != LEVEL_KATINA)) {
        scenery360 = gScenery360;
        for (i = 0; i < 200; i++, scenery360++) {
            if (scenery360->obj.status == OBJ_ACTIVE) {
                if ((scenery360->obj.id == OBJ_SCENERY_1) || (scenery360->obj.id == OBJ_SCENERY_3) ||
                    (scenery360->obj.id == OBJ_SCENERY_117) || (scenery360->obj.id == OBJ_SCENERY_141) ||
                    (scenery360->obj.id == OBJ_SCENERY_150) || (scenery360->obj.id == OBJ_SCENERY_149) ||
                    (scenery360->obj.id == OBJ_SCENERY_148) || (scenery360->obj.id == OBJ_SCENERY_140)) {
                    if (Object_CheckPolyCollision(pos, vel, scenery360->obj.id, &scenery360->obj)) {
                        return 999;
                    }
                } else if ((fabsf(pos->x - scenery360->obj.pos.x) < 2000.0f) &&
                           (fabsf(pos->z - scenery360->obj.pos.z) < 2000.0f)) {
                    if (Object_CheckHitboxCollision(pos, scenery360->info.hitbox, &scenery360->obj, 0.0f, 0.0f, 0.0f)) {
                        return 2;
                    }
                }
            }
        }
    }
    scenery = gScenery;
    for (i = 0; (i < ARRAY_COUNT(gScenery)) && (gLevelMode == LEVELMODE_ON_RAILS); i++, scenery++) {
        if (scenery->obj.status == OBJ_ACTIVE) {
            if ((scenery->obj.id == OBJ_SCENERY_1) || (scenery->obj.id == OBJ_SCENERY_4) ||
                (scenery->obj.id == OBJ_SCENERY_5) || (scenery->obj.id == OBJ_SCENERY_2) ||
                (scenery->obj.id == OBJ_SCENERY_ME_TUNNEL) || (scenery->obj.id == OBJ_SCENERY_3)) {
                if (Object_CheckPolyCollision(pos, vel, scenery->obj.id, &scenery->obj)) {
                    return 2;
                }
            } else if ((fabsf(pos->x - scenery->obj.pos.x) < 2000.0f) &&
                       (fabsf(pos->z - scenery->obj.pos.z) < 2000.0f)) {
                if (Object_CheckHitboxCollision(pos, scenery->info.hitbox, &scenery->obj, 0.0f, 0.0f, 0.0f)) {
                    return i + 10;
                }
            }
        }
    }
    sprite = gSprites;
    for (i = 0; i < ARRAY_COUNT(gSprites); i++, sprite++) {
        if ((sprite->obj.status == OBJ_ACTIVE) && (fabsf(pos->x - sprite->obj.pos.x) < 500.0f) &&
            (fabsf(pos->z - sprite->obj.pos.z) < 500.0f) &&
            Object_CheckSingleHitbox(pos, sprite->info.hitbox, &sprite->obj.pos)) {
            if ((sprite->obj.id == OBJ_SPRITE_FO_POLE) || (sprite->obj.id == OBJ_SPRITE_CO_TREE) ||
                (sprite->obj.id == OBJ_SPRITE_CO_TREE)) {
                sprite->destroy = 1;
            }
            return 0;
        }
    }
    if ((mode == 0) || (mode == 2) || (mode == 3)) {
        if (mode != 2) {
            boss = gBosses;
            for (i = 0; i < ARRAY_COUNT(gBosses); i++, boss++) {
                if (boss->obj.status == OBJ_ACTIVE) {
                    if ((boss->obj.id == OBJ_BOSS_FO) || (boss->obj.id == OBJ_BOSS_VE2) ||
                        (boss->obj.id == OBJ_BOSS_SZ) || (boss->obj.id == OBJ_BOSS_309)) {
                        if (Object_CheckPolyCollision(pos, vel, boss->obj.id, &boss->obj)) {
                            return 2;
                        }
                    } else if (boss->obj.id == OBJ_BOSS_310) {
                        temp.x = fabsf(boss->obj.pos.x - pos->x) * (5.0f / 6.0f);
                        temp.y = fabsf(boss->obj.pos.y - pos->y) * 2;
                        temp.z = fabsf(boss->obj.pos.z - pos->z) * (5.0f / 6.0f);
                        if ((VEC3F_MAG(&temp)) < 1500.0f) {
                            boss->dmgType = DMG_BEAM;
                            return 2;
                        }
                    } else {
                        if (boss->obj.id == OBJ_BOSS_KA) {
                            temp.x = fabsf(boss->obj.pos.x - pos->x);
                            temp.y = fabsf(boss->obj.pos.y - 300.0f - pos->y) * 7.42f;
                            temp.z = fabsf(boss->obj.pos.z - pos->z);
                            if ((VEC3F_MAG(&temp)) < 2700.0f) {
                                return 2;
                            }
                        }
                        if ((fabsf(pos->x - boss->obj.pos.x) < 2000.0f) &&
                            (fabsf(pos->z - boss->obj.pos.z) < 2000.0f)) {
                            if (Object_CheckHitboxCollision(pos, boss->info.hitbox, &boss->obj, 0.0f, 0.0f, 0.0f)) {
                                return 2;
                            }
                        }
                    }
                }
            }
        }
        actor = gActors;
        for (i = 0; i < ARRAY_COUNT(gActors); i++, actor++) {
            if ((actor->obj.status >= OBJ_ACTIVE) && (fabsf(pos->x - actor->obj.pos.x) < 1000.0f) &&
                (fabsf(pos->z - actor->obj.pos.z) < 1500.0f) && (index != i) && (actor->info.unk_16 != 2) &&
                !((actor->obj.id == OBJ_ACTOR_ALLRANGE) && (actor->aiType <= AI360_PEPPY)) && (actor->timer_0C2 == 0)) {
                if (actor->obj.id == OBJ_ACTOR_180) {
                    if (Object_CheckPolyCollision(pos, vel, actor->obj.id, &actor->obj)) {
                        return 2;
                    }
                } else if (actor->scale < 0.0f) {
                    if (Object_CheckHitboxCollision(pos, actor->info.hitbox, &actor->obj, actor->vwork[29].x,
                                                    actor->vwork[29].y, actor->vwork[29].z + actor->rot_0F4.z)) {
                        actor->dmgType = DMG_BEAM;
                        actor->damage = 10;
                        actor->dmgPart = -1;
                        actor->hitPos.x = pos->x;
                        actor->hitPos.y = pos->y;
                        actor->hitPos.z = pos->z;
                        return 2;
                    }
                } else if ((mode != 2) && (mode != 3)) {
                    if (Object_CheckSingleHitbox(pos, actor->info.hitbox, &actor->obj.pos)) {
                        actor->dmgType = DMG_BEAM;
                        actor->damage = 10;
                        actor->dmgPart = -1;
                        if (!(((actor->obj.id == OBJ_ACTOR_EVENT) && (actor->iwork[12] != 0)) ||
                              ((actor->obj.id == OBJ_ACTOR_ALLRANGE) &&
                               ((actor->aiType < AI360_10) || (actor->aiType >= AI360_GREAT_FOX))))) {
                            actor->health = 0;
                        }
                        actor->hitPos.x = pos->x;
                        actor->hitPos.y = pos->y;
                        actor->hitPos.z = pos->z;
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

void func_enmy_80063CAC(Scenery* scenery) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gActors); i++) {
        if (gActors[i].obj.status == OBJ_FREE) {
            Actor_Initialize(&gActors[i]);
            gActors[i].obj.status = OBJ_INIT;
            gActors[i].obj.id = OBJ_ACTOR_193;
            gActors[i].obj.pos.x = scenery->obj.pos.x;
            gActors[i].obj.pos.y = scenery->obj.pos.y;
            gActors[i].obj.pos.z = scenery->obj.pos.z;
            gActors[i].obj.rot.y = RAND_FLOAT(360.0f);
            Object_SetInfo(&gActors[i].info, gActors[i].obj.id);
            break;
        }
    }
}

void func_enmy_80063D58(Scenery* scenery) {
    s32 i;

    scenery->obj.pos.y = gGroundHeight;
    for (i = 0; i < ARRAY_COUNT(gSprites); i++) {
        if (gSprites[i].obj.status == OBJ_FREE) {
            Sprite_Initialize(&gSprites[i]);
            gSprites[i].obj.status = OBJ_INIT;
            gSprites[i].obj.id = OBJ_SPRITE_FOG_SHADOW;
            gSprites[i].sceneryId = scenery->obj.id;
            gSprites[i].obj.pos.x = scenery->obj.pos.x;
            gSprites[i].obj.pos.y = 5.0f;
            gSprites[i].obj.pos.z = scenery->obj.pos.z;
            if ((scenery->obj.id == OBJ_SCENERY_0) || (scenery->obj.id == OBJ_SCENERY_6) ||
                (scenery->obj.id == OBJ_SCENERY_7) || (scenery->obj.id == OBJ_SCENERY_56) ||
                (scenery->obj.id == OBJ_SCENERY_20) || (scenery->obj.id == OBJ_SCENERY_21) ||
                (scenery->obj.id == OBJ_SCENERY_22)) {
                gSprites[i].obj.rot.y = scenery->obj.rot.y;
            } else {
                gSprites[i].obj.rot.y = 44.9f;
            }
            Object_SetInfo(&gSprites[i].info, gSprites[i].obj.id);
            break;
        }
    }
}

void func_enmy_80063E5C(Scenery* scenery, f32* hitboxData) {
    s32 i;
    Item* item;

    for (i = 0, item = gItems; i < ARRAY_COUNT(gItems); i++, item++) {
        if (item->obj.status == OBJ_FREE) {
            Item_Initialize(&gItems[i]);
            item->obj.status = OBJ_INIT;
            item->obj.id = OBJ_ITEM_RING_CHECK;
            item->obj.pos.x = scenery->obj.pos.x;
            item->obj.pos.y = scenery->obj.pos.y;
            item->obj.pos.z = scenery->obj.pos.z;
            item->obj.rot.y = scenery->obj.rot.y;
            Object_SetInfo(&item->info, item->obj.id);
            item->info.hitbox = LOAD_ASSET(hitboxData);
            break;
        }
    }
}

void func_enmy_80063F4C(s32 arg0) {
}

void func_enmy_80063F58(Item* item) {
    item->width = item->obj.rot.z * 100.0f;
}

void func_enmy_80063F74(Item* item) {
    item->width = item->obj.rot.z * 100.0f;
}

void Object_Init(s32 index, ObjectId objId) {
    s32 var_a0;
    s32 var_a2;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    PosRot* var_v0;

    switch (objId) {
        case OBJ_SPRITE_CO_SMOKE:
            func_effect_8007A6F0(&gSprites[index].obj.pos, NA_SE_OB_SMOKE);
            break;
        case OBJ_ACTOR_234:
            AUDIO_PLAY_SFX(NA_SE_GREATFOX_ENGINE, gActors[index].sfxSource, 0);
            break;
        case OBJ_SCENERY_54:
            AUDIO_PLAY_SFX(NA_SE_FALL, gScenery[index].sfxSource, 0);
            break;
        case OBJ_ACTOR_TEAM_BOSS:
            ActorTeamBoss_Init(&gActors[index]);
            break;
        case OBJ_ACTOR_235:
            gActors[index].fwork[10] = fabsf(Math_ModF(gActors[index].obj.pos.x, 100.0f));
            break;
        case OBJ_ACTOR_247:
            Zoness_Actor247_Init(&gActors[index]);
            break;
        case OBJ_EFFECT_368:
            if (gCurrentLevel == LEVEL_TITANIA) {
                Ground_801B6E20(gEffects[index].obj.pos.x, gEffects[index].obj.pos.z + gPathProgress, &sp54, &sp4C,
                                &sp50);
                gEffects[index].obj.pos.y = sp4C + 3.0f;
                gEffects[index].obj.rot.x = RAD_TO_DEG(sp54);
                gEffects[index].obj.rot.z = RAD_TO_DEG(sp50);
            } else if (gCurrentLevel == LEVEL_MACBETH) {
                gEffects[index].obj.status = OBJ_FREE;
            }
            break;
        case OBJ_SCENERY_TI_RIB_0:
            func_enmy_80063E5C(&gScenery[index], D_TI_6006940);
            break;
        case OBJ_SCENERY_TI_RIB_1:
            func_enmy_80063E5C(&gScenery[index], D_TI_600695C);
            break;
        case OBJ_SCENERY_TI_RIB_2:
            func_enmy_80063E5C(&gScenery[index], D_TI_6006978);
            break;
        case OBJ_SCENERY_TI_RIB_3:
            func_enmy_80063E5C(&gScenery[index], D_TI_6006994);
            break;
        case OBJ_SCENERY_TI_RIB_4:
            func_enmy_80063E5C(&gScenery[index], D_TI_60069B0);
            break;
        case OBJ_SCENERY_TI_RIB_5:
            func_enmy_80063E5C(&gScenery[index], D_TI_60069CC);
            break;
        case OBJ_SCENERY_TI_RIB_6:
            func_enmy_80063E5C(&gScenery[index], D_TI_60069E8);
            break;
        case OBJ_SCENERY_TI_RIB_7:
            func_enmy_80063E5C(&gScenery[index], D_TI_6006A04);
            break;
        case OBJ_SCENERY_TI_RIB_8:
            func_enmy_80063E5C(&gScenery[index], D_TI_6006A20);
            break;
        case OBJ_SCENERY_23:
            func_enmy_80063CAC(&gScenery[index]);
            break;
        case OBJ_ITEM_CHECKPOINT:
            if (gSavedObjectLoadIndex != 0) {
                gItems[index].obj.status = OBJ_FREE;
            }
            break;
        case OBJ_ITEM_METEO_WARP:
            if (gRingPassCount < 0) {
                gItems[index].obj.status = OBJ_FREE;
            }
            break;
        case OBJ_ITEM_PATH_SPLIT_Y:
        case OBJ_ITEM_PATH_TURN_UP:
        case OBJ_ITEM_PATH_TURN_DOWN:
            func_enmy_80063F74(&gItems[index]);
            break;
        case OBJ_ITEM_PATH_SPLIT_X:
        case OBJ_ITEM_PATH_TURN_LEFT:
            func_enmy_80063F58(&gItems[index]);
            break;
        case OBJ_ITEM_PATH_TURN_RIGHT:
            if (((gRingPassCount >= 7) && (gCurrentLevel == LEVEL_CORNERIA) && (gTeamShields[TEAM_ID_FALCO] > 0)) ||
                (gCurrentLevel != LEVEL_CORNERIA)) {
                func_enmy_80063F58(&gItems[index]);
            } else {
                gItems[index].obj.status = OBJ_FREE;
            }
            break;
        case OBJ_SCENERY_0:
            func_enmy_80063E5C(&gScenery[index], gItemRingCheckHitbox);
            /* fallthrough */
        case OBJ_SCENERY_6:
        case OBJ_SCENERY_7:
        case OBJ_SCENERY_20:
        case OBJ_SCENERY_21:
        case OBJ_SCENERY_22:
        case OBJ_SCENERY_56:
            func_enmy_80063D58(&gScenery[index]);
            break;
        case OBJ_ACTOR_187:
            gActors[index].fwork[0] = gActors[index].obj.pos.x;
            gActors[index].fwork[1] = gActors[index].obj.pos.y;
            gActors[index].obj.rot.z = gActors[index].obj.rot.x;
            gActors[index].obj.rot.x = 0.0f;
            break;
        case OBJ_ACTOR_182:
        case OBJ_ACTOR_186:
            gActors[index].unk_046 = gFogRed;
            gActors[index].unk_048 = gFogNear;
            gActors[index].obj.rot.x = RAND_FLOAT(360.0f);
            gActors[index].obj.rot.y = RAND_FLOAT(360.0f);
            break;
        case OBJ_ACTOR_181:
            gActors[index].obj.rot.x = RAND_FLOAT(360.0f);
            gActors[index].obj.rot.y = RAND_FLOAT(360.0f);
            gActors[index].health = 200;
            break;
        case OBJ_ACTOR_202:
            gActors[index].health = 30;
            break;
        case OBJ_ACTOR_252:
            if (gPlayer[0].pos.z < gActors[index].obj.pos.z) {
                Object_Kill(&gActors[index].obj, gActors[index].sfxSource);
            }
            break;
        case OBJ_ACTOR_239:
            gActors[index].iwork[0] = gZOSnakeWaypointCount;
            gZOSnakeWaypointCount++;
            break;
        case OBJ_ACTOR_236:
            gZOSnakeWaypointCount = 0;
            gActors[index].rot_0F4.x = gActors[index].obj.rot.x;
            gActors[index].rot_0F4.y = gActors[index].obj.rot.y;
            gActors[index].obj.rot.x = gActors[index].obj.rot.y = 0.0f;
            gActors[index].fwork[2] = gActors[index].obj.pos.y;
            var_v0 = gZOSnakePosRots;
            for (var_a0 = 0; var_a0 < 200; var_a0++, var_v0++) {
                var_v0->pos.x = gActors[index].obj.pos.x;
                var_v0->pos.y = gActors[index].obj.pos.y;
                var_v0->pos.z = gActors[index].obj.pos.z;
                var_v0->rot.x = gActors[index].obj.rot.x;
                var_v0->rot.y = gActors[index].obj.rot.y;
                var_v0->rot.z = gActors[index].obj.rot.z;
            }
            break;
        case OBJ_ACTOR_194:
            gActors[index].unk_046 = 100;
            for (var_a0 = 0; var_a0 < 2; var_a0++) {
                if (gActor194Status[var_a0] == 0) {
                    gActor194Status[var_a0] = 1;
                    gActors[index].unk_046 = var_a0;
                    for (var_a2 = 0; var_a2 < 100; var_a2++) {
                        gActor194yPos[var_a0][var_a2] = gActors[index].obj.pos.y;
                        gActor194zPos[var_a0][var_a2] = gActors[index].obj.pos.z;
                    }
                    break;
                }
            }
            if (gActors[index].unk_046 == 100) {
                gActors[index].obj.status = OBJ_FREE;
            }
            break;
        case OBJ_ACTOR_190:
        case OBJ_ACTOR_191:
            AUDIO_PLAY_SFX(NA_SE_EN_MISSILE_ENGINE, gActors[index].sfxSource, 4);
            break;
        case OBJ_ACTOR_192:
            gActors[index].drawShadow = true;
            break;
        case OBJ_BOSS_320:
            Andross_Boss320_Init(&gBosses[index]);
            break;
        case OBJ_BOSS_KA:
            Katina_BossSetup(&gBosses[index]);
            break;
        case OBJ_BOSS_SY:
            SectorY_Boss314_Init(&gBosses[index]);
            break;
        case OBJ_ACTOR_205:
        case OBJ_ACTOR_206:
        case OBJ_ACTOR_208:
        case OBJ_ACTOR_209:
        case OBJ_ACTOR_210:
        case OBJ_ACTOR_211:
        case OBJ_ACTOR_212:
        case OBJ_ACTOR_213:
            Macbeth_80199F8C(&gActors[index]);
            break;
        case OBJ_ACTOR_207:
            Macbeth_801A7D98(&gActors[index]);
            break;
        case OBJ_ACTOR_214:
            Macbeth_801A3E70(&gActors[index]);
            break;
        case OBJ_ACTOR_215:
            Macbeth_801A4660(&gActors[index]);
            break;
        case OBJ_ACTOR_223:
            Macbeth_801A4AF8(&gActors[index]);
            break;
        case OBJ_ACTOR_216:
        case OBJ_ACTOR_217:
            Macbeth_801A5E2C(&gActors[index]);
            break;
        case OBJ_ACTOR_218:
            Macbeth_801A6134(&gActors[index]);
            break;
        case OBJ_SCENERY_65:
            Macbeth_801A65E0(&gScenery[index]);
            break;
        case OBJ_ACTOR_177:
        case OBJ_ACTOR_178:
            Corneria_8018B0B4(&gActors[index]);
            /* fallthrough */
        case OBJ_ACTOR_176:
            gActors[index].health = 24;
            AUDIO_PLAY_SFX(NA_SE_EN_TANK_RB_ENGINE, gActors[index].sfxSource, 4);
            break;
        case OBJ_BOSS_297:
            Meteo_Boss297_Init(&gBosses[index]);
            break;
        case OBJ_BOSS_299:
            Boss299_Init(&gBosses[index]);
            break;
        case OBJ_BOSS_300:
            Boss300_Init(&gBosses[index]);
            break;
        case OBJ_BOSS_292:
            Corneria_Boss292_Init(&gBosses[index]);
            break;
        case OBJ_BOSS_293:
            Corneria_Boss293_Init(&gBosses[index]);
            break;
        case OBJ_BOSS_A6:
            Area6_BossA6_Init(&gBosses[index]);
            break;
        case OBJ_ACTOR_231:
            Titania_Actor231_Init(&gActors[index]);
            break;
        case OBJ_ACTOR_232:
            Titania_8018ADC4(&gActors[index]);
            break;
        case OBJ_ACTOR_233:
            Titania_80189B80(&gActors[index]);
            break;
        case OBJ_ACTOR_229:
            Titania_8018BFB0(&gActors[index]);
            break;
        case OBJ_ACTOR_227:
            Titania_8018E3CC(&gActors[index]);
            break;
        case OBJ_ACTOR_228:
            Titania_8018E5E8(&gActors[index]);
            break;
        case OBJ_SPRITE_TI_CACTUS:
            Titania_8018EFF0(&gSprites[index]);
            break;
        case OBJ_BOSS_TI:
            Titania_Boss306_Init(&gBosses[index]);
            break;
        case OBJ_ACTOR_240:
            Zoness_801915A4(&gActors[index]);
            break;
        case OBJ_ACTOR_241:
            Zoness_80191BB8(&gActors[index]);
            break;
        case OBJ_BOSS_ZO:
            Zoness_BossZo_Init(&gBosses[index]);
            break;
        case OBJ_ACTOR_250:
            Zoness_8019B1F0(&gActors[index]);
            break;
        case OBJ_ACTOR_251:
            Zoness_8019B810(&gActors[index]);
            break;
        case OBJ_ACTOR_253:
            Zoness_8019C200(&gActors[index]);
            break;
        case OBJ_ACTOR_255:
            Aquas_801AD688(&gActors[index]);
            break;
        case OBJ_ACTOR_256:
            Aquas_801AE3AC(&gActors[index]);
            break;
        case OBJ_ACTOR_257:
            Aquas_801AF9FC(&gActors[index]);
            break;
        case OBJ_BOSS_AQ:
            Aquas_BossAq_Init(&gBosses[index]);
            break;
        case OBJ_ACTOR_259:
            Aquas_801B6344(&gActors[index]);
            break;
        case OBJ_ACTOR_262:
            Aquas_801B6E54(&gActors[index]);
            break;
        case OBJ_ACTOR_260:
            Aquas_801B7AF0(&gActors[index]);
            break;
        case OBJ_SCENERY_57:
            Titania_8018F0D8(&gScenery[index]);
            break;
        case OBJ_BOSS_VE1:
            Venom1_Boss319_Init(&gBosses[index]);
            break;
        case OBJ_ACTOR_280:
            Venom1_8019250C(&gActors[index]);
            break;
        case OBJ_ACTOR_281:
        case OBJ_ACTOR_282:
            Venom1_80192CB0(&gActors[index]);
            break;
        case OBJ_ACTOR_283:
            Venom1_80192EA4(&gActors[index]);
            break;
        case OBJ_ACTOR_284:
            Venom1_801933B4(&gActors[index]);
            break;
        case OBJ_ACTOR_265:
            Aquas_801BA57C(&gActors[index]);
            break;
        case OBJ_ACTOR_267:
            Aquas_801BB26C(&gActors[index]);
            break;
    }
}

void Scenery_UpdateTitaniaBones(Scenery* scenery) {
    f32 sp2C;
    f32 sp28;
    f32 sp24;

    if ((gGroundType == 4) && (scenery->state == 0)) {
        Ground_801B6E20(scenery->obj.pos.x, scenery->obj.pos.z + gPathProgress, &sp2C, &sp24, &sp28);
        scenery->obj.pos.y = sp24 + 3.0f;
        scenery->obj.rot.x = RAD_TO_DEG(sp2C);
        scenery->obj.rot.z = RAD_TO_DEG(sp28);
        scenery->state++;
    }
}

void func_enmy_80065380(Actor* actor, f32 xPos, f32 yPos, f32 zPos, f32 arg4, f32 arg5, f32 arg6) {
    Actor_Initialize(actor);
    actor->obj.status = OBJ_ACTIVE;
    actor->obj.id = OBJ_ACTOR_182;
    actor->timer_0BC = RAND_INT(10.0f) + 10;
    actor->timer_0C2 = 30;
    actor->vel.x = arg4;
    actor->vel.y = arg5;
    actor->vel.z = arg6;
    actor->obj.pos.x = xPos;
    actor->obj.pos.y = yPos;
    actor->obj.pos.z = zPos;
    actor->unk_046 = 255;
    actor->unk_048 = 900;
    actor->obj.rot.z = RAND_FLOAT(360.0f);
    actor->obj.rot.y = RAND_FLOAT(360.0f);
    Object_SetInfo(&actor->info, actor->obj.id);
}

void func_enmy_8006546C(f32 xPos, f32 yPos, f32 zPos, f32 arg3, f32 arg4, f32 arg5) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gActors); i++) {
        if (gActors[i].obj.status == OBJ_FREE) {
            func_enmy_80065380(&gActors[i], xPos, yPos, zPos, arg3, arg4, arg5);
            break;
        }
    }
}

void func_enmy_800654E4(Object* obj) {
    f32 temp_fs0;
    f32 temp_fs1;
    s32 var_s1;

    func_effect_8007D2C8(obj->pos.x, obj->pos.y, obj->pos.z, 12.0f);
    for (var_s1 = 0; var_s1 < 4; var_s1++) {
        func_enmy_8006546C(obj->pos.x, obj->pos.y, obj->pos.z, RAND_FLOAT_CENTERED(40.0f), RAND_FLOAT_CENTERED(40.0f),
                           RAND_FLOAT(-20.0f));
    }
}

void func_enmy_800655C8(Actor* actor, f32 xPos, f32 yPos, f32 zPos, s32 arg4) {
    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_190;
    actor->obj.pos.x = xPos;
    actor->obj.pos.y = yPos;
    actor->obj.pos.z = zPos;
    actor->eventType = arg4;
    actor->timer_0BE = 50;
    if (actor->eventType == 1) {
        actor->timer_0BE = 30;
    }
    actor->fwork[5] = 15.0f;
    Object_SetInfo(&actor->info, actor->obj.id);
}

void func_enmy_8006566C(f32 xPos, f32 yPos, f32 zPos, s32 arg3) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gActors); i++) {
        if (gActors[i].obj.status == OBJ_FREE) {
            func_enmy_800655C8(&gActors[i], xPos, yPos, zPos, arg3);
            break;
        }
    }
}

void func_enmy_800656D4(Actor* actor) {
    s32 i;
    s32 j;
    f32 spD4;
    f32 spD0;
    f32 spCC;
    f32 var_fv0;
    s32 spC4;
    s32 var_ra;
    s32 spB4[3];
    s32 spA8[3];
    s32 temp_a3_2;
    Vec3f sp98;
    Vec3f sp8C;
    f32 sp88;
#ifdef AVOID_UB
    f32 sp84 = 0;
#else
    f32 sp84;
#endif
    f32 sp80;
    f32 sp7C;
    f32 sp78;

    var_ra = (gLevelMode == LEVELMODE_ALL_RANGE) ? 2 : 0;

    if (actor->iwork[2] == 0) {
        if (actor->obj.id == OBJ_ACTOR_190) {
            for (i = 0; i < 3; i++) {
                spB4[i] = gTeamShields[i + 1];
                spA8[i] = var_ra + i;
            }
            for (i = 0; i < 3; i++) {
                for (j = i + 1; j < 3; j++) {
                    if (spB4[i] < spB4[j]) {
                        temp_a3_2 = spB4[j];
                        spB4[j] = spB4[i];
                        spB4[i] = temp_a3_2;
                        temp_a3_2 = spA8[j];
                        spA8[j] = spA8[i];
                        spA8[i] = temp_a3_2;
                    }
                }
            }
            switch (gGameFrameCount % 6U) {
                case 0:
                case 1:
                case 2:
                    spC4 = spA8[2];
                    break;
                case 3:
                case 4:
                    spC4 = spA8[1];
                    break;
                case 5:
                    spC4 = spA8[0];
                    break;
            }

            if (gLevelMode == LEVELMODE_ALL_RANGE) {
                if (gTeamShields[spC4 - 1] > 0) {
                    actor->iwork[1] = spC4;
                    goto label;
                } else {
                    actor->iwork[1] = 10000;
                }
            } else {
                if (gTeamShields[spC4 + 1] > 0) {
                    actor->iwork[1] = spC4;
                    goto label;
                } else {
                    actor->iwork[1] = 10000;
                }
            }
        }
        actor->iwork[1] = 10000;
    label:
        actor->iwork[2] = 1;
    }
    spC4 = actor->iwork[1];
    if ((spC4 == var_ra) || ((var_ra + 1) == spC4) || ((var_ra + 2) == spC4)) {
        actor->fwork[29] = gActors[spC4].obj.pos.z;
        actor->fwork[28] = gActors[spC4].obj.pos.y;
        actor->fwork[27] = gActors[spC4].obj.pos.x;
        if ((fabsf(actor->obj.pos.x - gActors[spC4].obj.pos.x) < 400.0f) &&
            (fabsf(actor->obj.pos.z - gActors[spC4].obj.pos.z) < 400.0f)) {
            if (RAND_FLOAT(spC4 - 1) < 0.6f) {
                gActors[spC4].iwork[10] = 1;
            }
        }

    } else {
        actor->fwork[29] = gPlayer[0].trueZpos;
        actor->fwork[28] = gPlayer[0].pos.y;
        actor->fwork[27] = gPlayer[0].pos.x;
    }
    if (actor->timer_0BC != 0) {
        Math_SmoothStepToAngle(&actor->obj.rot.x, 0.0f, 0.3f, 4.0f, 0.001f);
    } else {
        if ((actor->iwork[10] == 0) && ((fabsf(actor->fwork[27] - actor->obj.pos.x) > 300.0f) ||
                                        (fabsf(actor->fwork[29] - actor->obj.pos.z) > 300.0f))) {
            actor->fwork[0] += 5.0f;
            actor->fwork[1] += 8.0f;
            sp88 = actor->fwork[27] - actor->obj.pos.x;
            sp80 = actor->fwork[29] - actor->obj.pos.z;
            sp80 = sqrtf(SQ(sp88) + SQ(sp80)) * 0.2f;
            if (actor->eventType == 1) {
                sp80 = 0.1f;
            }
            spD0 = SIN_DEG(actor->fwork[0]) * sp80;
            sp88 = COS_DEG(actor->fwork[1]) * sp80;
            spD4 = COS_DEG(actor->obj.rot.y) * sp88;
            spCC = -SIN_DEG(actor->obj.rot.y) * sp88;

            sp88 = (actor->fwork[27] + spD4) - actor->obj.pos.x;
            sp84 = (actor->fwork[28] + spD0) - actor->obj.pos.y;
            sp80 = (actor->fwork[29] + spCC) - actor->obj.pos.z;
            sp78 = Math_RadToDeg(Math_Atan2F(sp88, sp80));
            sp80 = sqrtf(SQ(sp88) + SQ(sp80));
            sp7C = Math_RadToDeg(-Math_Atan2F(sp84, sp80));
            sp84 = Math_SmoothStepToAngle(&actor->obj.rot.y, sp78, 0.3f, 4.0f, 0.001f);
            Math_SmoothStepToAngle(&actor->obj.rot.x, sp7C, 0.3f, 4.0f, 0.001f);
        }
        if ((fabsf(actor->fwork[27] - actor->obj.pos.x) < 60.0f) &&
            (fabsf(actor->fwork[28] - actor->obj.pos.y) < 60.0f) &&
            (fabsf(actor->fwork[29] - actor->obj.pos.z) < 60.0f) && ((spC4 == 2) || (spC4 == 3) || (spC4 == 4))) {
            gActors[spC4].dmgType = DMG_BEAM;
            gActors[spC4].damage = 20;
            gActors[spC4].dmgSource = DMG_SRC_2;
            func_effect_8007A6F0(&actor->obj.pos, NA_SE_EN_EXPLOSION_S);
            func_effect_8007D2C8(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, 5.0f);
            Object_Kill(&actor->obj, actor->sfxSource);
        }
    }
    Math_Vec3fFromAngles(&sp98, actor->obj.rot.x, actor->obj.rot.y, actor->fwork[5]);
    actor->vel.x = sp98.x;
    actor->vel.y = sp98.y;
    actor->vel.z = sp98.z - gPathVelZ;
    if (actor->eventType == 0) {
        actor->obj.rot.z += 5.0f;
    }
    if (actor->eventType == 1) {
        if (actor->timer_0BE == 0) {
            actor->timer_0BE = 30;
            Math_Vec3fFromAngles(&sp98, actor->obj.rot.x, actor->obj.rot.y, 120.0f);
            func_effect_8007F04C(OBJ_EFFECT_353, actor->obj.pos.x + sp98.x, actor->obj.pos.y + sp98.y,
                                 actor->obj.pos.z + sp98.z, actor->obj.rot.x, actor->obj.rot.y, actor->obj.rot.z, 0.0f,
                                 0.0f, 0.0f, sp98.x, sp98.y, sp98.z, 1.0f);
        }
        var_fv0 = 330.0f;
        if (sp84 < 0.0f) {
            var_fv0 = 30.0f;
        }
        Math_SmoothStepToAngle(&actor->obj.rot.z, var_fv0, 0.1f, 3.0f, 0.01f);
    }
    if ((gGroundType == 4) && Ground_801B6AEC(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z + gPathProgress)) {
        func_effect_8007D2C8(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, 5.0f);
        Object_Kill(&actor->obj, actor->sfxSource);
    }
    sp8C.x = actor->vel.x;
    sp8C.y = actor->vel.y;
    sp8C.z = actor->vel.z;
    if ((Object_CheckCollision(actor->index, &actor->obj.pos, &sp8C, 1) != 0) || (actor->dmgType != DMG_NONE) ||
        (actor->obj.pos.y < (gGroundHeight + 10.0f)) || (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_LEVEL_COMPLETE)) {
        func_effect_8007D2C8(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, 3.0f);
        Object_Kill(&actor->obj, actor->sfxSource);
        if (actor->dmgType != DMG_NONE) {
            actor->itemDrop = DROP_SILVER_RING_50p;
            if ((gCurrentLevel == LEVEL_CORNERIA)) {
                if (gLevelMode == LEVELMODE_ALL_RANGE) {
                    actor->itemDrop = DROP_SILVER_RING_50p;
                } else {
                    actor->itemDrop = DROP_SILVER_RING_25p;
                }
            }
            if (gCurrentLevel == LEVEL_AREA_6) {
                actor->itemDrop = DROP_SILVER_RING_10p;
            }
            Actor_Despawn(actor);
        }
        func_effect_8007A6F0(&actor->obj.pos, NA_SE_EN_EXPLOSION_S);
    }
    if (gLevelMode == LEVELMODE_ON_RAILS) {
        if (fabsf(actor->obj.pos.z - gPlayer[0].trueZpos) < 100.0f) {
            actor->iwork[10] = 1;
        }
        if (gPlayer[0].cam.eye.z < (actor->obj.pos.z + gPathProgress)) {
            Object_Kill(&actor->obj, actor->sfxSource);
        }
    }
}

void func_enmy_800660F0(Actor* actor) {
    Item* item = gItems;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gItems); i++, item++) {
        if (item->obj.status == OBJ_FREE) {
            Item_Initialize(item);
            item->obj.status = OBJ_INIT;
            item->obj.id = D_enmy_800CFDF4[actor->itemDrop];
            item->obj.pos.x = actor->obj.pos.x;
            item->obj.pos.y = actor->obj.pos.y;
            item->obj.pos.z = actor->obj.pos.z;
            item->timer_4A = 8;
            Object_SetInfo(&item->info, item->obj.id);
            if ((item->obj.id == OBJ_ITEM_SILVER_RING) || (item->obj.id == OBJ_ITEM_BOMB) ||
                (item->obj.id == OBJ_ITEM_LASERS)) {
                item->unk_50 = 90.0f;
            }
            if ((item->obj.id >= OBJ_ITEM_GOLD_RING) || (item->obj.id == OBJ_ITEM_1UP)) {
                item->unk_50 = 90.0f;
                AUDIO_PLAY_SFX(NA_SE_ITEM_APPEAR, gDefaultSfxSource, 4);
                item->timer_48 = 1000;
                if (item->obj.id == OBJ_ITEM_WING_REPAIR) {
                    AUDIO_PLAY_SFX(NA_SE_OB_WING, item->sfxSource, 0);
                }
            }
            break;
        }
    }
}

void Actor_Despawn(Actor* actor) {
    Actor* otherActor;
    s32 i;

    if (gVersusMode) {
        if ((actor->dmgSource >= 1) && (actor->dmgSource < 4 + 1) &&
            !((D_versus_80178768[0] == 0) && (D_versus_80178768[1] == 0) && (D_versus_80178768[2] == 0))) {
            gPlayerScores[actor->dmgSource - 1] += actor->info.bonus;
        }
    } else if (!((actor->obj.id == OBJ_ACTOR_ALLRANGE) && (actor->animFrame == 1))) {
        if ((actor->dmgSource == AI360_FOX + 1) && (actor->info.bonus != 0)) {
            gHitCount += actor->info.bonus;
            D_ctx_80177850 = 15;
            if ((gLevelMode == LEVELMODE_ALL_RANGE) && (gDropHitCountItem != 0)) {
                switch (gDropHitCountItem) {
                    case 9:
                        if (gCurrentLevel == LEVEL_KATINA) {
                            Radio_PlayMessage(gMsg_ID_18031, RCID_BILL);
                        }
                        /* fallthrough */
                    case 4:
                    case 19:
                    case 29:
                        actor->itemDrop = DROP_GOLD_RING_1;
                        break;
                    case 14:
                        actor->itemDrop = DROP_LASERS;
                        break;
                }
                gDropHitCountItem = 0;
            }
            if (actor->obj.id == OBJ_ACTOR_ALLRANGE) {
                if ((actor->aiType >= AI360_WOLF) && (actor->aiType < AI360_KATT)) {
                    AllRange_GetStarWolfHits(actor);
                }
            }
        }
        if (actor->itemDrop) {
            if (D_enmy_800CFE5C[actor->itemDrop] < 0.0f) {
                otherActor = gActors;
                for (i = 0, otherActor = gActors; i < ARRAY_COUNT(gActors); i++, otherActor++) {
                    if ((otherActor->obj.status != OBJ_FREE) && (otherActor->index != actor->index) &&
                        (otherActor->iwork[15] == actor->iwork[15])) {
                        return;
                    }
                }
                func_enmy_800660F0(actor);
                AUDIO_PLAY_SFX(NA_SE_ITEM_APPEAR, gDefaultSfxSource, 4);
            } else if (actor->itemDrop == DROP_TEAM_MESG) {
                if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                    Radio_PlayMessage(gMsg_ID_20261, RCID_PEPPY);
                } else if (gTeamShields[TEAM_ID_SLIPPY] > 0) {
                    Radio_PlayMessage(gMsg_ID_20263, RCID_SLIPPY);
                } else if (gTeamShields[TEAM_ID_FALCO] > 0) {
                    Radio_PlayMessage(gMsg_ID_20262, RCID_FALCO);
                }
            } else if (Rand_ZeroOne() <= D_enmy_800CFE5C[actor->itemDrop]) {
                func_enmy_800660F0(actor);
            }
        }
    }
}

void func_enmy_8006654C(Actor* actor) {
    actor->gravity = 0.4f;
    if (actor->obj.pos.y <= gGroundHeight + 130.0f) {
        actor->obj.pos.y = gGroundHeight + 130.0f;
        actor->vel.y = 0.0f;
    }
    actor->vel.x = SIN_DEG(actor->obj.rot.y) * actor->fwork[0];
    actor->vel.z = COS_DEG(actor->obj.rot.y) * actor->fwork[0];
    switch (actor->state) {
        case 0:
            if (actor->fwork[0] < 20.0f) {
                actor->fwork[0] += 0.5f;
            }
            actor->animFrame++;
            if (Animation_GetFrameCount(&D_CO_6029528) < actor->animFrame) {
                actor->animFrame = 0;
            }
            if ((actor->obj.rot.z < 15.0f) && (actor->animFrame < 20)) {
                actor->obj.rot.z += 1.0f;
            }
            if ((actor->obj.rot.z > -15.0f) && (actor->animFrame > 20)) {
                actor->obj.rot.z -= 1.0f;
            }
            if ((actor->animFrame == 20) || (actor->animFrame == 40)) {
                actor->state++;
                actor->timer_0BC = 20;
            }
            break;
        case 1:
            if (actor->obj.rot.z > 0.0f) {
                actor->obj.rot.z -= 0.5f;
            }
            if (actor->obj.rot.z < 0.0f) {
                actor->obj.rot.z += 0.5f;
            }
            if (actor->fwork[0] > 0.0f) {
                actor->fwork[0] -= 0.3f;
            }
            if (actor->timer_0BC == 0) {
                actor->state = 0;
            }
            break;
    }
    actor->scale = 0.8f;
    if (actor->dmgType != DMG_NONE) {
        actor->obj.status = OBJ_DYING;
        actor->vel.y = RAND_FLOAT(5.0f) + 6.0f;
        if (actor->dmgType == DMG_EXPLOSION) {
            actor->vel.y = -2.0f;
        }
        actor->vel.z = -15.0f;
        actor->gravity = 0.5f;
        func_effect_8007D2C8(actor->obj.pos.x, actor->obj.pos.y + 30.0f, actor->obj.pos.z, 13.0f);
        AUDIO_PLAY_SFX(NA_SE_EN_EXPLOSION_S, actor->sfxSource, 4);
    }
}

void func_enmy_8006684C(Actor* actor) {
    s32 pad;

    if (actor->timer_0BE != 0) {
        actor->vel.z = 0.0f;
        actor->vel.x = 0.0f;
        actor->vel.y = 0.0f;
        if (actor->timer_0BE == 1) {
            Object_Kill(&actor->obj, actor->sfxSource);
            actor->itemDrop = DROP_SILVER_RING;
            Actor_Despawn(actor);
            AUDIO_PLAY_SFX(NA_SE_EN_EXPLOSION_M, actor->sfxSource, 4);
            BonusText_Display(actor->obj.pos.x, actor->obj.pos.y + 250.0f, actor->obj.pos.z, 3);
            gHitCount += 3;
            D_ctx_80177850 = 15;
        }
    } else {
        actor->obj.rot.x += 11.0f;
        actor->obj.rot.y += 7.0f;
        if (actor->vel.y < -3.0f) {
            func_effect_8007BFFC(actor->obj.pos.x, actor->obj.pos.y + 30.0f, actor->obj.pos.z, 0.0f, 0.0f, 0.0f, 7.0f,
                                 5);
            actor->timer_0BE = 3;
        }
    }
}

void func_enmy_800669A0(Actor* actor) {
    if (actor->timer_0BC != 0) {
        if (actor->timer_0BC == 1) {
            Object_Kill(&actor->obj, actor->sfxSource);
        }
    } else {
        actor->obj.rot.y += 5.0f;
        if (actor->dmgType != DMG_NONE) {
            func_effect_8007D0E0(actor->obj.pos.x, actor->obj.pos.y + 130.0f, actor->obj.pos.z, 8.0f);
            func_effect_8007BFFC(actor->obj.pos.x, actor->obj.pos.y + 130.0f, actor->obj.pos.z, 0.0f, 0.0f, 0.0f, 4.0f,
                                 5);
            actor->timer_0BC = 4;
            func_effect_8007A6F0(&actor->obj.pos, NA_SE_OB_EXPLOSION_S);
        }
    }
}

void func_enmy_80066A80(Actor* actor) {
}

void func_enmy_80066A8C(Scenery* scenery) {
    Vec3f sp64;
    Vec3f sp58;
    f32 yf;

    sp64.z = 0.0f;
    sp64.x = -120.0f;
    if (scenery->obj.rot.y > 90.0f) {
        sp64.x = 120.0f;
    }
    for (yf = 0.0f; yf < 680.0f; yf += 100.0f) {
        Matrix_RotateY(gCalcMatrix, scenery->obj.rot.y * M_DTOR, MTXF_NEW);
        Matrix_RotateX(gCalcMatrix, scenery->obj.rot.x * M_DTOR, MTXF_APPLY);
        sp64.y = yf;
        Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp64, &sp58);
        func_effect_8007D0E0(scenery->obj.pos.x + sp58.x, scenery->obj.pos.y + sp58.y, scenery->obj.pos.z + sp58.z,
                             4.0f);
    }
}

void func_enmy_80066C00(Scenery* scenery) {
    Vec3f sp64;
    Vec3f sp58;
    f32 zf;

    sp64.y = 30.0f;
    sp64.x = -100.0f;
    if (scenery->obj.rot.y > 90.0f) {
        sp64.x = 100.0f;
    }
    Matrix_RotateY(gCalcMatrix, scenery->obj.rot.y * M_DTOR, MTXF_NEW);

    for (zf = -180.0f; zf <= 0.0f; zf += 30.0f) {
        sp64.z = zf;
        Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp64, &sp58);
        func_effect_8007D0E0(scenery->obj.pos.x + sp58.x, scenery->obj.pos.y + sp58.y, scenery->obj.pos.z + sp58.z,
                             RAND_FLOAT(1.0f) + 2.0f);
    }
}

void func_enmy_80066D5C(Scenery* scenery) {
    switch (scenery->state) {
        case 1:
            func_enmy_80066C00(scenery);
            scenery->state++;
            AUDIO_PLAY_SFX(NA_SE_EN_DAMAGE_L, scenery->sfxSource, 4);
            break;
        case 2:
            scenery->vel.x += 0.05f;
            scenery->obj.rot.x += scenery->vel.x;
            if (scenery->obj.rot.x >= 90.0f) {
                scenery->obj.rot.x = 90.0f;
                scenery->unk_44 = 40;
                func_enmy_80066A8C(scenery);
                scenery->state = 0;
                gCameraShake = 25;
                AUDIO_PLAY_SFX(NA_SE_EN_METAL_BOUND_M, scenery->sfxSource, 4);
            }
            break;
        case 0:
            break;
    }
}

void func_enmy_80066E80(Scenery* scenery) {
}

void Sprite167_Update(Sprite167* this) {
    this->obj.rot.y += 0.2f;
}

void func_enmy_80066EA8(Scenery* scenery) {
    scenery->obj.rot.y = 0.0f;
    if (gPlayer[0].cam.eye.x < scenery->obj.pos.x) {
        scenery->obj.rot.y = 271.0f;
    }
}

void func_enmy_80066EE4(Sprite* sprite) {
}

void Item_CheckBounds(Item* this) {
    f32 var_fa1;

    if ((gPlayer[0].state_1C8 == PLAYERSTATE_1C8_LEVEL_COMPLETE) || (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_STANDBY)) {
        Object_Kill(&this->obj, this->sfxSource);
    }
    if ((gLevelMode == LEVELMODE_ON_RAILS) && (gLastPathChange == 0)) {
        var_fa1 = 900.0f;
        if (gPlayer[0].form != FORM_ARWING) {
            var_fa1 = 600.0f;
        }
        if (this->obj.pos.x > gPlayer[0].xPath + var_fa1) {
            Math_SmoothStepToF(&this->obj.pos.x, gPlayer[0].xPath + var_fa1, 0.1f, 10.0f, 0.01f);
        }
        if (this->obj.pos.x < gPlayer[0].xPath - var_fa1) {
            Math_SmoothStepToF(&this->obj.pos.x, gPlayer[0].xPath - var_fa1, 0.1f, 10.0f, 0.01f);
        }
    }
    if (this->obj.pos.y > 650.0f) {
        Math_SmoothStepToF(&this->obj.pos.y, 650.0f, 0.1f, 10.0f, 0.01f);
    }
    if (gLevelType == LEVELTYPE_PLANET) {
        if (this->obj.pos.y < gGroundHeight + 70.0f) {
            Math_SmoothStepToF(&this->obj.pos.y, gGroundHeight + 70.0f, 0.1f, 5.0f, 0.01f);
        }
        if ((gCurrentLevel == LEVEL_AQUAS) && gBossActive) {
            this->obj.pos.z += 20.0f;
        }
    } else if (this->obj.pos.y < -500.0f) {
        Math_SmoothStepToF(&this->obj.pos.y, -500.0f, 0.1f, 5.0f, 0.01f);
    }
    if (gVersusMode && (this->index == 0) && (gItems[1].obj.status == OBJ_ACTIVE)) {
        if (fabsf(this->obj.pos.x - gItems[1].obj.pos.x) < 200.0f) {
            if (fabsf(this->obj.pos.z - gItems[1].obj.pos.z) < 200.0f) {
                this->obj.pos.x = this->obj.pos.x - 5.0f;
                this->obj.pos.z = this->obj.pos.z - 5.0f;
                gItems[1].obj.pos.x += 5.0f;
                gItems[1].obj.pos.z += 5.0f;
            }
        }
    }
}

void Item_SpinPickup(Item* this) {
    s32 sparkleMask;
    Vec3f sp40;
    Vec3f sp34;

    Math_SmoothStepToF(&this->unk_50, 10.0f, 1.0f, 2.0f, 0.0f);
    if (this->unk_50 > 30.0f) {
        sparkleMask = 1 - 1;
    } else if (this->unk_50 > 20.0f) {
        sparkleMask = 2 - 1;
    } else {
        sparkleMask = 8 - 1;
    }
    if (!(sparkleMask & gGameFrameCount)) {
        Matrix_RotateY(gCalcMatrix, gGameFrameCount * 23.0f * M_DTOR, MTXF_NEW);
        sp40.x = 50.0f;
        sp40.y = RAND_FLOAT_CENTERED(120.0f);
        sp40.z = 0.0f;
        Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp40, &sp34);
        func_effect_80078E50(this->obj.pos.x + sp34.x, this->obj.pos.y + sp34.y, this->obj.pos.z + sp34.z, 3.0f);
    }
    this->obj.rot.y += this->unk_50;
    this->obj.rot.y = Math_ModF(this->obj.rot.y, 360.0f);
}

void Actor_SetupDebris70(Actor* actor, f32 xPos, f32 yPos, f32 zPos, f32 xRot, f32 yRot, f32 xVel, f32 yVel, f32 zVel) {
    Actor_Initialize(actor);
    actor->obj.status = OBJ_ACTIVE;
    actor->obj.id = OBJ_ACTOR_DEBRIS;
    actor->state = 70;
    actor->obj.pos.x = xPos;
    actor->obj.pos.y = yPos;
    actor->obj.pos.z = zPos;
    actor->obj.rot.x = xRot;
    actor->obj.rot.y = yRot;
    actor->vel.x = xVel;
    actor->vel.y = yVel;
    actor->vel.z = zVel;
    actor->timer_0BC = RAND_INT(15.0f) + 25.0f;
    actor->gravity = 0.5f;
    Object_SetInfo(&actor->info, actor->obj.id);
}

void Actor_SpawnDebris70(f32 xPos, f32 yPos, f32 zPos, f32 xRot, f32 yRot, f32 arg5, f32 arg6, f32 arg7) {
    s32 i;

    for (i = ARRAY_COUNT(gActors) - 1; i >= 50; i--) {
        if (gActors[i].obj.status == OBJ_FREE) {
            Actor_SetupDebris70(&gActors[i], xPos, yPos, zPos, xRot, yRot, arg5, arg6, arg7);
            break;
        }
    }
}

void ActorSupplies_Update(ActorSupplies* this) {
    Player* player = &gPlayer[0];
    s32 i;

    this->obj.rot.y += 1.0f;
    if (gLevelMode == LEVELMODE_ALL_RANGE) {
        if (gCurrentLevel == LEVEL_SECTOR_Z) {
            Math_SmoothStepToF(&this->obj.pos.x, -2000.0f, 0.05f, 60.0f, 0.01f);
            Math_SmoothStepToF(&this->obj.pos.y, -200.0f, 0.05f, 3.0f, 0.01f);
            Math_SmoothStepToF(&this->obj.pos.z, 0.0f, 0.05f, 0.f, 0.01f);
        } else {
            Math_SmoothStepToF(&this->obj.pos.y, 300.0f, 0.05f, 50.0f, 0.01f);
        }
    }
    if (this->dmgType != DMG_NONE) {
        this->dmgType = DMG_NONE;
        this->health -= this->damage;
        if (this->health <= 0) {
            func_effect_8007A6F0(&this->obj.pos, NA_SE_EN_EXPLOSION_S);
            func_effect_8007D2C8(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 5.0f);
            if (((player[0].wings.rightState <= WINGSTATE_BROKEN) || (player[0].wings.leftState <= WINGSTATE_BROKEN)) &&
                (player[0].form != FORM_LANDMASTER)) {
                this->itemDrop = DROP_WING_REPAIR;
            } else if (gPlayer[0].shields < 128) {
                this->itemDrop = DROP_SILVER_STAR;
            } else if ((gLaserStrength[0] == LASERS_SINGLE) && (player[0].form != FORM_LANDMASTER)) {
                this->itemDrop = DROP_LASERS;
            } else {
                this->itemDrop = DROP_BOMB;
            }
            Actor_Despawn(this);
            for (i = 0; i < 6; i++) {
                Actor_SpawnDebris70(D_enmy_800CFEC4[i].x + this->obj.pos.x, D_enmy_800CFEC4[i].y + this->obj.pos.y,
                                    D_enmy_800CFEC4[i].z + this->obj.pos.z, D_enmy_800CFF0C[i].y + this->obj.rot.y,
                                    D_enmy_800CFF0C[i].x + this->obj.rot.x, RAND_FLOAT_CENTERED(40.0f),
                                    RAND_FLOAT(10.0f) + 10.0f, RAND_FLOAT_CENTERED(40.0f));
                func_effect_800794CC(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 0.6f);
            }
            Object_Kill(&this->obj, this->sfxSource);
        }
    }
    gRadarMarks[63].status = 1;
    gRadarMarks[63].type = 103;
    gRadarMarks[63].pos.x = this->obj.pos.x;
    gRadarMarks[63].pos.y = this->obj.pos.y;
    gRadarMarks[63].pos.z = this->obj.pos.z;
    gRadarMarks[63].yRot = 0.0f;
}

void ActorSupplies_Draw(Actor* actor) {
    s32 i;

    Lights_SetOneLight(&gMasterDisp, -60, -60, 60, 150, 150, 150, 20, 20, 20);
    for (i = 0; i < 6; i++) {
        Matrix_Push(&gGfxMatrix);
        Matrix_Translate(gGfxMatrix, D_enmy_800CFEC4[i].x, D_enmy_800CFEC4[i].y, D_enmy_800CFEC4[i].z, MTXF_APPLY);
        Matrix_RotateY(gGfxMatrix, D_enmy_800CFF0C[i].y * M_DTOR, MTXF_APPLY);
        Matrix_RotateX(gGfxMatrix, D_enmy_800CFF0C[i].x * M_DTOR, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, D_10177C0);
        Matrix_Pop(&gGfxMatrix);
    }
    Lights_SetOneLight(&gMasterDisp, gLight1x, gLight1y, gLight1z, gLight1R, gLight1G, gLight1B, gAmbientR, gAmbientG,
                       gAmbientB);
}

void func_enmy_80067A40(void) {
    AUDIO_PLAY_SFX(NA_SE_WING_REPAIR, gPlayer[0].sfxSource, 0);
    if (gPlayer[0].wings.rightState <= WINGSTATE_BROKEN) {
        gRightWingFlashTimer[0] = 1050;
        gPlayer[0].wings.rightState = WINGSTATE_INTACT;
    }
    if (gPlayer[0].wings.leftState <= WINGSTATE_BROKEN) {
        gLeftWingFlashTimer[0] = 1050;
        gPlayer[0].wings.leftState = WINGSTATE_INTACT;
    }
    if (gExpertMode) {
        gRightWingHealth[0] = gLeftWingHealth[0] = 10;
    } else {
        gRightWingHealth[0] = gLeftWingHealth[0] = 60;
    }
}

void Item1up_Update(Item1UP* this) {
    Item_CheckBounds(this);
    Item_SpinPickup(this);
    if (this->collected) {
        Object_Kill(&this->obj, this->sfxSource);
        Object_PlayerSfx(gPlayer[this->playerNum].sfxSource, NA_SE_ONE_UP, this->playerNum);
        if (gCurrentLevel != LEVEL_TRAINING) {
            gLifeCount[this->playerNum]++;
        }
    }
    if (this->timer_48 == 1) {
        Object_Kill(&this->obj, this->sfxSource);
    }
}

void ItemPickup_Update(Item* this) {
    Item_CheckBounds(this);
    Item_SpinPickup(this);
    if (this->state == 0) {
        switch (this->obj.id) {
            case OBJ_ITEM_BOMB:
                this->width = 18.0f;
                if (this->collected) {
                    this->timer_4A = 50;
                    this->state = 1;
                    this->timer_48 = 20;
                    this->unk_50 = 60.0f;
                    gBombCount[this->playerNum]++;
                    Object_PlayerSfx(gPlayer[this->playerNum].sfxSource, NA_SE_BOMB_GET, this->playerNum);
                    Object_PlayerSfx(gPlayer[this->playerNum].sfxSource, NA_SE_BOMB_GAUGE_UP, this->playerNum);
                }
                break;
            case OBJ_ITEM_LASERS:
                this->width = 18.0f;
                if (this->collected) {
                    this->timer_4A = 50;
                    this->state = 1;
                    this->timer_48 = 20;
                    this->unk_50 = 60.0f;
                    gLaserStrength[this->playerNum]++;
                    if (gLaserStrength[this->playerNum] > LASERS_HYPER) {
                        gLaserStrength[this->playerNum] = LASERS_HYPER;
                    }
                    Object_PlayerSfx(gPlayer[this->playerNum].sfxSource, NA_SE_TWIN_LASER_GET, this->playerNum);
                    if (gExpertMode) {
                        gRightWingHealth[this->playerNum] = gLeftWingHealth[this->playerNum] = 10;
                    } else {
                        gRightWingHealth[this->playerNum] = gLeftWingHealth[this->playerNum] = 60;
                    }
                    gRightWingFlashTimer[this->playerNum] = 1030;
                    gLeftWingFlashTimer[this->playerNum] = 1030;
                }
                break;
        }
    } else {
        Math_SmoothStepToF(&this->width, 2.5f, 1.0f, 0.5f, 0.0f);
        this->obj.pos.x += (gPlayer[this->playerNum].pos.x - this->obj.pos.x) * 0.5f;
        if (gPlayer[this->playerNum].form == FORM_LANDMASTER) {
            this->obj.pos.y += ((gPlayer[this->playerNum].pos.y + 50.0f) - this->obj.pos.y) * 0.5f;
        } else {
            this->obj.pos.y += (gPlayer[this->playerNum].pos.y - this->obj.pos.y) * 0.5f;
        }
        this->obj.pos.z += (gPlayer[this->playerNum].trueZpos - this->obj.pos.z) * 0.5f;
        if (this->timer_48 == 0) {
            Object_Kill(&this->obj, this->sfxSource);
        }
    }
}

void ItemLasers_Update(ItemLasers* this) {
    if (!gVersusMode &&
        ((gPlayer[0].wings.leftState <= WINGSTATE_BROKEN) || (gPlayer[0].wings.rightState <= WINGSTATE_BROKEN))) {
        this->obj.id = OBJ_ITEM_WING_REPAIR;
        Object_SetInfo(&this->info, this->obj.id);
        this->timer_48 = 2000;
        AUDIO_PLAY_SFX(NA_SE_OB_WING, this->sfxSource, 0);
    } else {
        ItemPickup_Update(this);
    }
}

void ItemSupplyRing_Update(Item* this) {
    Vec3f sp4C;
    Vec3f sp40;

    switch (this->state) {
        case 0:
            Math_SmoothStepToF(&this->width, 0.4f, 1.0f, 0.05f, 0.0f);
            Item_CheckBounds(this);
            Item_SpinPickup(this);
            if (this->collected) {
                this->state = 1;
                this->timer_48 = 50;
                if (this->obj.id == OBJ_ITEM_SILVER_RING) {
                    gPlayer[this->playerNum].heal += 32;
                    Object_PlayerSfx(gPlayer[this->playerNum].sfxSource, NA_SE_SHIELD_RING, this->playerNum);
                } else if (this->obj.id == OBJ_ITEM_GOLD_RING) {
                    gGoldRingCount[0]++;
                    if (gGoldRingCount[0] == 3) {
                        Object_PlayerSfx(gPlayer[this->playerNum].sfxSource, NA_SE_SHIELD_UPGRADE, this->playerNum);
                    } else if (gGoldRingCount[0] == 6) {
                        Object_PlayerSfx(gPlayer[this->playerNum].sfxSource, NA_SE_ONE_UP, this->playerNum);
                        if (gCurrentLevel != LEVEL_TRAINING) {
                            gLifeCount[this->playerNum]++;
                        }
                        gPlayer[this->playerNum].heal += 32;
                        BonusText_Display(gPlayer[this->playerNum].pos.x, gPlayer[this->playerNum].pos.y,
                                          gPlayer[this->playerNum].trueZpos, BONUS_TEXT_1UP);
                    } else {
                        gPlayer[this->playerNum].heal += 32;
                        Object_PlayerSfx(gPlayer[this->playerNum].sfxSource, NA_SE_GOLD_RING, this->playerNum);
                    }
                } else {
                    gPlayer[this->playerNum].heal += 128;
                    Object_PlayerSfx(gPlayer[this->playerNum].sfxSource, NA_SE_SHIELD_RING_M, this->playerNum);
                }
            }
            if ((this->obj.id == OBJ_ITEM_GOLD_RING) && (this->timer_48 == 1)) {
                Object_Kill(&this->obj, this->sfxSource);
            }
            break;
        case 1:
            if (this->timer_48 > 30) {
                Math_SmoothStepToF(&this->width, 1.0f, 1.0f, 0.06f, 0.0f);
            } else {
                Math_SmoothStepToF(&this->width, 0.0f, 1.0f, 0.06f, 0.0f);
            }
            this->obj.pos.x += (gPlayer[this->playerNum].pos.x - this->obj.pos.x) * 0.5f;
            if (gPlayer[this->playerNum].form == FORM_LANDMASTER) {
                this->obj.pos.y += (gPlayer[this->playerNum].pos.y + 50.0f - this->obj.pos.y) * 0.5f;
            } else {
                this->obj.pos.y += (gPlayer[this->playerNum].pos.y - this->obj.pos.y) * 0.5f;
            }
            if (gPlayer[0].alternateView && (gLevelMode == LEVELMODE_ON_RAILS)) {
                this->obj.pos.z += (gPlayer[this->playerNum].trueZpos - 300.0f - this->obj.pos.z) * 0.3f;
            } else {
                this->obj.pos.z += (gPlayer[this->playerNum].trueZpos - this->obj.pos.z) * 0.5f;
            }
            this->obj.rot.z += 22.0f;
            Math_SmoothStepToAngle(&this->obj.rot.y, Math_RadToDeg(-gPlayer[this->playerNum].camYaw), 0.2f, 10.0f,
                                   0.0f);
            if (this->timer_48 == 0) {
                Object_Kill(&this->obj, this->sfxSource);
            }
            if (this->width > 0.3f) {
                Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
                Matrix_RotateZ(gCalcMatrix, gGameFrameCount * 37.0f * M_DTOR, MTXF_APPLY);
                sp4C.x = 0.0f;
                sp4C.y = this->width * 100.0f;
                sp4C.z = 0.0f;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp4C, &sp40);
                func_effect_80078E50(this->obj.pos.x + sp40.x, this->obj.pos.y + sp40.y, this->obj.pos.z + sp40.z,
                                     3.5f);
            }
            break;
    }
}

void ItemSilverStar_Update(ItemSilverStar* this) {
    ItemSupplyRing_Update(this);
}

void ItemGoldRing_Update(ItemGoldRing* this) {
    ItemSupplyRing_Update(this);
}

void ItemWingRepair_Update(ItemWingRepair* this) {
    Item_CheckBounds(this);
    Item_SpinPickup(this);
    if (this->collected) {
        func_enmy_80067A40();
        Object_Kill(&this->obj, this->sfxSource);
    }
    if (this->timer_48 == 1) {
        Object_Kill(&this->obj, this->sfxSource);
    }
}

void ItemMeteoWarp_Update(ItemMeteoWarp* this) {
    Item_CheckBounds(this);
    if (this->state > 0) {
        if (this->state == 1) {
            this->obj.rot.z -= 10.0f;
            this->obj.pos.x += (gPlayer[this->playerNum].pos.x - this->obj.pos.x) * 0.3f;
            this->obj.pos.y += (gPlayer[this->playerNum].pos.y - this->obj.pos.y) * 0.3f;
            this->obj.pos.z += (gPlayer[this->playerNum].trueZpos - this->obj.pos.z) * 0.3f;
            this->width -= 5.0f;
            if (this->width < 0.0f) {
                this->width = 0.0f;
            }
        }
        this->unk_44 -= 10;
        if (this->unk_44 < 0) {
            Object_Kill(&this->obj, this->sfxSource);
        }
    } else {
        this->width = 100.0f;
        if (gRingPassCount < 0) {
            this->state = 2;
            this->unk_44 = 255;
        } else if (this->collected) {
            this->state = 1;
            this->unk_44 = 255;
            gPlayer[this->playerNum].meteoWarpTimer = 100;
            AUDIO_PLAY_SFX(gWarpRingSfx[gRingPassCount], gPlayer[0].sfxSource, 0);
            if (gRingPassCount == 0) {
                gPlayer[0].boostSpeed = 0.0f;
            }
            gRingPassCount++;
            if (gRingPassCount >= 7) {
                gPlayer[0].state_1C8 = PLAYERSTATE_1C8_ENTER_WARP_ZONE;
                gPlayer[0].csState = 0;
                AUDIO_PLAY_SFX(NA_SE_WARP_HOLE, gDefaultSfxSource, 0);
                gMissionStatus = MISSION_WARP;
                gLeveLClearStatus[gCurrentLevel] = 1;
            }
        }
    }
}

void ItemCheckpoint_Update(ItemCheckpoint* this) {
    s32 i;

    Item_CheckBounds(this);
    this->unk_58 -= this->unk_44;
    if (this->state > 0) {
        this->unk_44++;
        this->obj.pos.x += (gPlayer[this->playerNum].pos.x - this->obj.pos.x) * 0.3f;
        if (gPlayer[this->playerNum].form == FORM_LANDMASTER) {
            this->obj.pos.y += (gPlayer[this->playerNum].pos.y + 50.0f - this->obj.pos.y) * 0.3f;
        } else {
            this->obj.pos.y += (gPlayer[this->playerNum].pos.y - this->obj.pos.y) * 0.3f;
        }
        if (gPlayer[0].alternateView) {
            this->obj.pos.z += (gPlayer[this->playerNum].trueZpos - 200.0f - this->obj.pos.z) * 0.3f;
        } else {
            this->obj.pos.z += (gPlayer[this->playerNum].trueZpos - 100.0f - this->obj.pos.z) * 0.3f;
        }
        if (this->timer_48 == 0) {
            Math_SmoothStepToF(&this->width, 5.0f, 0.2f, 15.0f, 0.01f);
            Math_SmoothStepToF(&this->unk_50, 0.0f, 0.1f, 0.03f, 0.0f);
            Math_SmoothStepToF(&this->unk_54, 4.0f, 0.1f, 0.2f, 0.01f);
        }
        if (this->width <= 6.5f) {
            Object_Kill(&this->obj, this->sfxSource);
        }
    } else {
        this->unk_44 = 2;
        this->unk_50 = 1.0f;
        this->unk_54 = 1.0f;
        this->width = 100.0f;
        if (this->collected) {
            gPlayer[this->playerNum].heal = 128;
            this->state++;
            this->timer_48 = 15;
            gSavedGroundSurface = gGroundSurface;
            gSavedPathProgress = -this->obj.pos.z;
            gSavedPathProgress -= 250.0f;
            gSavedObjectLoadIndex = gObjectLoadIndex;
            gSavedZoSearchlightStatus = gMissedZoSearchlight;
            gSavedHitCount = gHitCount;
            for (i = TEAM_ID_FALCO; i <= TEAM_ID_PEPPY; i++) {
                gSavedTeamShields[i] = gTeamShields[i];
            }
            AUDIO_PLAY_SFX(NA_SE_CHECKPOINT, gDefaultSfxSource, 4);
        }
    }
}

void ItemRingCheck_Update(Item* this) {
    if (this->collected) {
        Object_Kill(&this->obj, this->sfxSource);
        gRingPassCount++;
    }
}

void ItemPathChange_Update(Item* this) {
    gLastPathChange = this->obj.id;
    if (gPlayer[0].state_1C8 != PLAYERSTATE_1C8_ACTIVE) {
        Object_Kill(&this->obj, this->sfxSource);
    } else if (((gCurrentLevel == LEVEL_METEO) || (gCurrentLevel == LEVEL_SECTOR_X)) && (gLevelPhase == 1)) {
        gPlayer[0].state_1C8 = PLAYERSTATE_1C8_LEVEL_COMPLETE;
        gPlayer[0].csState = 0;
        Object_Kill(&this->obj, this->sfxSource);
    } else if (gCurrentLevel == LEVEL_TRAINING) {
        gPlayer[0].state_1C8 = PLAYERSTATE_1C8_START_360;
        gPlayer[0].csState = 0;
        Object_Kill(&this->obj, this->sfxSource);
    } else if (this->state == 0) {
        if (((this->obj.pos.z + gPathProgress) > -2700.0f) && (fabsf(this->obj.pos.x - gPlayer[0].pos.x) < 1000.0f)) {
            switch (this->obj.id) {
                case OBJ_ITEM_PATH_SPLIT_Y:
                case OBJ_ITEM_PATH_TURN_UP:
                case OBJ_ITEM_PATH_TURN_DOWN:
                    break;
                case OBJ_ITEM_PATH_SPLIT_X:
                    gPlayer[0].flags_228 = PFLAG_228_4 | PFLAG_228_5;
                    break;
                case OBJ_ITEM_PATH_TURN_LEFT:
                    gPlayer[0].flags_228 = PFLAG_228_5;
                    break;
                case OBJ_ITEM_PATH_TURN_RIGHT:
                    gPlayer[0].flags_228 = PFLAG_228_4;
                    break;
            }
        }
        if (this->collected) {
            Object_Kill(&this->obj, this->sfxSource);
            gPlayer[0].pathStep = 0.0f;
            gPlayer[0].pathChangeTimer = this->width * 0.05f;
            switch (this->obj.id) {
                case OBJ_ITEM_PATH_SPLIT_X:
                    if (this->obj.pos.x < gPlayer[0].pos.x) {
                        gPlayer[0].pathChangeYaw = -30.0f;
                        gPlayer[0].xPathTarget = gPlayer[0].xPath + this->width;
                    } else {
                        gPlayer[0].pathChangeYaw = 30.0f;
                        gPlayer[0].xPathTarget = gPlayer[0].xPath - this->width;
                    }
                    break;
                case OBJ_ITEM_PATH_TURN_LEFT:
                    gPlayer[0].pathChangeYaw = 30.0f;
                    gPlayer[0].xPathTarget = gPlayer[0].xPath - this->width;
                    break;
                case OBJ_ITEM_PATH_TURN_RIGHT:
                    gPlayer[0].pathChangeYaw = -30.0f;
                    gPlayer[0].xPathTarget = gPlayer[0].xPath + this->width;
                    break;
                case OBJ_ITEM_PATH_SPLIT_Y:
                    if (this->obj.pos.y < gPlayer[0].pos.y) {
                        gPlayer[0].pathChangePitch = 30.0f;
                        gPlayer[0].yPathTarget = gPlayer[0].yPath + this->width;
                    } else {
                        gPlayer[0].pathChangePitch = -30.0f;
                        gPlayer[0].yPathTarget = gPlayer[0].yPath - this->width;
                    }
                    break;
                case OBJ_ITEM_PATH_TURN_UP:
                    gPlayer[0].pathChangePitch = 30.0f;
                    gPlayer[0].yPathTarget = gPlayer[0].yPath + this->width;
                    break;
                case OBJ_ITEM_PATH_TURN_DOWN:
                    gPlayer[0].pathChangePitch = -30.0f;
                    gPlayer[0].yPathTarget = gPlayer[0].yPath - this->width;
                    break;
            }
        }
    }
}

void Sprite_UpdateDoodad(Sprite* this) {
    this->obj.rot.y =
        (Math_Atan2F(gPlayer[0].cam.eye.x - this->obj.pos.x, gPlayer[0].cam.eye.z - (this->obj.pos.z + gPathProgress)) *
         180.0f) /
        M_PI;
    if (this->destroy) {
        this->obj.status = OBJ_FREE;
        func_effect_8007A6F0(&this->obj.pos, NA_SE_OB_EXPLOSION_S);
        switch (this->obj.id) {
            case OBJ_SPRITE_CO_POLE:
                func_effect_8007D074(this->obj.pos.x, this->obj.pos.y + 160.0f, this->obj.pos.z, 4.0f);
                break;
            default:
            case OBJ_SPRITE_TI_CACTUS:
                func_effect_8007D074(this->obj.pos.x, this->obj.pos.y + 96.0f, this->obj.pos.z, 5.0f);
                break;
        }
    }
}

void Object_Dying(s32 index, ObjectId objId) {
    switch (objId) {
        case OBJ_ACTOR_EVENT:
            ActorEvent_Dying(&gActors[index]);
            break;
        case OBJ_ACTOR_ALLRANGE:
            if (gCurrentLevel == LEVEL_VENOM_ANDROSS) {
                Andross_801888F4(&gActors[index]);
            } else {
                func_enmy2_800763A4(&gActors[index]);
            }
            break;
        case OBJ_ACTOR_202:
            func_enmy2_800763A4(&gActors[index]);
            break;
        case OBJ_ACTOR_194:
            Actor194_Dying(&gActors[index]);
            break;
        case OBJ_ACTOR_186:
            Meteo_80187B08(&gActors[index]);
            break;
        case OBJ_ACTOR_181:
            Object_Kill(&gActors[index].obj, gActors[index].sfxSource);
            func_effect_8007D2C8(gActors[index].obj.pos.x, gActors[index].obj.pos.y, gActors[index].obj.pos.z, 20.0f);
            break;
        case OBJ_ACTOR_182:
            Object_Kill(&gActors[index].obj, gActors[index].sfxSource);
            func_effect_8007D2C8(gActors[index].obj.pos.x, gActors[index].obj.pos.y, gActors[index].obj.pos.z, 10.0f);
            Actor_Despawn(&gActors[index]);
            break;
        case OBJ_ACTOR_192:
            func_enmy_8006684C(&gActors[index]);
            break;
        case OBJ_BOSS_TI:
            Titania_801990DC(&gBosses[index]);
            break;
        case OBJ_ACTOR_232:
            Titania_8018B720(&gActors[index]);
            break;
        case OBJ_BOSS_VE1:
            Venom1_80198594(&gBosses[index]);
            break;
    }
}

void Actor_Move(Actor* actor) {
    f32 var_fv0;

    actor->obj.pos.x += actor->vel.x;
    actor->obj.pos.z += actor->vel.z;
    actor->obj.pos.y += actor->vel.y;
    actor->vel.y -= actor->gravity;

    if (!gCullObjects || (actor->obj.id == OBJ_ACTOR_TEAM_BOSS) ||
        ((gCurrentLevel == LEVEL_MACBETH) && (actor->obj.id != OBJ_ACTOR_EVENT))) {
        return;
    }
    var_fv0 = 4000.0f;

    if ((actor->obj.id == OBJ_ACTOR_236) || (gCurrentLevel == LEVEL_MACBETH) ||
        ((actor->obj.id == OBJ_ACTOR_EVENT) && (actor->eventType == EVID_56))) {
        var_fv0 = 8000.0f;
    } else if (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_ENTER_WARP_ZONE) {
        var_fv0 = 100000.0f;
    }
    if (((gPlayer[0].cam.eye.z + actor->info.cullDistance) < (actor->obj.pos.z + gPathProgress)) ||
        ((actor->obj.pos.z + gPathProgress) < -15000.0f) || (actor->obj.pos.y < (gPlayer[0].yPath - var_fv0)) ||
        ((gPlayer[0].yPath + var_fv0) < actor->obj.pos.y) || ((gPlayer[0].xPath + var_fv0) < actor->obj.pos.x) ||
        (actor->obj.pos.x < (gPlayer[0].xPath - var_fv0))) {
        Object_Kill(&actor->obj, actor->sfxSource);
        switch (actor->obj.id) {
            case OBJ_ACTOR_236:
                gZOSnakeWaypointCount = 0;
                break;
            case OBJ_ACTOR_229:
                Titania_8018E3B0(actor);
                break;
            case OBJ_ACTOR_194:
                gActor194Status[actor->unk_046] = 0;
                break;
            case OBJ_ACTOR_EVENT:
                if ((actor->eventType >= EVID_200) && (actor->eventType < EVID_300)) {
                    gActor194Status[actor->unk_046] = 0;
                } else if ((actor->eventType == EVID_SX_WARP_GATE) && (actor->unk_046 != 2)) {
                    gRingPassCount = -1;
                }
                break;
            case OBJ_ACTOR_252:
                gMissedZoSearchlight = true;
                break;
        }
    }
}

void Boss_Move(Boss* boss) {
    boss->obj.pos.x += boss->vel.x;
    boss->obj.pos.y += boss->vel.y;
    boss->obj.pos.z += boss->vel.z;
    boss->vel.y -= boss->gravity;
    if (gCullObjects && ((boss->obj.pos.z + gPathProgress) > (boss->info.cullDistance - gPlayer[0].cam.eye.z))) {
        if (gPlayer[0].cam.eye.z) {} // fake
        Object_Kill(&boss->obj, boss->sfxSource);
    }
}

void Scenery_Move(Scenery* scenery) {
    if (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_LEVEL_INTRO) {
        scenery->obj.pos.z += scenery->effectVel.z;
        if (scenery->info.cullDistance < scenery->obj.pos.z) {
            Object_Kill(&scenery->obj, scenery->sfxSource);
        }
    } else if ((gLevelMode == LEVELMODE_ON_RAILS) && (gBossActive != 2)) {
        f32 temp_fv0 = fabsf(scenery->obj.pos.x - gPlayer[0].cam.eye.x);
        f32 var_fa0 = 500.0f;

        if ((scenery->obj.id == OBJ_SCENERY_6) || (scenery->obj.id == OBJ_SCENERY_7)) {
            var_fa0 = 1000.0f;
        }
        temp_fv0 = ((temp_fv0 - var_fa0) < 0.0f) ? 0.0f : (temp_fv0 - var_fa0) * 1.7f;
        if ((fabsf(gPlayer[0].yRot_114) > 1.0f) || (gCurrentLevel == LEVEL_MACBETH)) {
            temp_fv0 = 0.0f;
        }
        temp_fv0 -= gPlayer[0].cam.eye.z;
        if ((scenery->info.cullDistance - temp_fv0) < (scenery->obj.pos.z + gPathProgress)) {
            Object_Kill(&scenery->obj, scenery->sfxSource);
        }
    }
}

void Sprite_Move(Sprite* sprite) {
    if (gCullObjects) {
        f32 temp_fv0 = fabsf(sprite->obj.pos.x - gPlayer[0].cam.eye.x);
        f32 var_fa0 = 500.0f;

        if (((sprite->obj.id == OBJ_SPRITE_FOG_SHADOW) &&
             ((sprite->sceneryId == OBJ_SCENERY_6) || (sprite->sceneryId == OBJ_SCENERY_7))) ||
            (sprite->obj.id == OBJ_SCENERY_8)) {
            var_fa0 = 1000.0f;
        }
        temp_fv0 = ((temp_fv0 - var_fa0) < 0.0f) ? 0.0f * 1.7f : (temp_fv0 - var_fa0) * 1.7f;
        temp_fv0 -= gPlayer[0].cam.eye.z;
        if ((sprite->info.cullDistance - temp_fv0) < (sprite->obj.pos.z + gPathProgress)) {
            sprite->obj.status = OBJ_FREE;
        }
    }
}

void Effect_Move(Effect* effect) {
    effect->obj.pos.x += effect->vel.x;
    effect->obj.pos.y += effect->vel.y;
    effect->obj.pos.z += effect->vel.z;
    if (gCullObjects) {
        if ((gPlayer[0].cam.eye.z + effect->info.cullDistance) < (effect->obj.pos.z + gPathProgress)) {
            Object_Kill(&effect->obj, effect->sfxSource);
        } else if ((fabsf(effect->obj.pos.y - gPlayer[0].cam.eye.y) > 25000.0f) ||
                   (fabsf(effect->obj.pos.x - gPlayer[0].cam.eye.x) > 25000.0f)) {
            Object_Kill(&effect->obj, effect->sfxSource);
        }
    }
}

void Item_Move(Item* item) {
    if (gCullObjects) {
        f32 temp = (0.0f - gPlayer[0].cam.eye.z);

        if ((item->info.cullDistance - temp) < (item->obj.pos.z + gPathProgress)) {
            Object_Kill(&item->obj, item->sfxSource);
            if ((item->obj.id == OBJ_ITEM_METEO_WARP) && (item->state == 0)) {
                gRingPassCount = -1;
            }
        }
    }
}

void Actor_Update(Actor* this) {
    s32 i;

    if (this->timer_0BC != 0) {
        this->timer_0BC--;
    }
    if (this->timer_0BE != 0) {
        this->timer_0BE--;
    }
    if (this->timer_0C0 != 0) {
        this->timer_0C0--;
    }
    if (this->timer_0C2 != 0) {
        this->timer_0C2--;
    }
    if (this->timer_0C6 != 0) {
        this->timer_0C6--;
    }
    if (gVersusMode) {
        for (i = 0; i < gCamCount; i++) {
            if (this->lockOnTimers[i] != 0) {
                if (!(gControllerHold[i].button & A_BUTTON)) {
                    this->lockOnTimers[i]--;
                }
                gChargeTimers[i] = 0;
            }
        }
    } else if (this->lockOnTimers[TEAM_ID_FOX] != 0) {
        if (!(gControllerHold[gMainController].button & A_BUTTON)) {
            this->lockOnTimers[TEAM_ID_FOX]--;
        }
        gChargeTimers[0] = 0;
    }
    if (this->timer_0C4 != 0) {
        this->timer_0C4--;
    }
    switch (this->obj.status) {
        case OBJ_INIT:
            this->obj.status = OBJ_ACTIVE;
            Object_Init(this->index, this->obj.id);
            if (this->obj.id != OBJ_ACTOR_252) {
                Actor_Move(this);
            }
            break;
        case OBJ_ACTIVE:
            Actor_Move(this);
            if ((this->obj.status != OBJ_FREE) && (this->info.action != NULL)) {
                this->info.action(&this->obj);
            }
            break;
        case OBJ_DYING:
            Actor_Move(this);
            if (this->obj.status != OBJ_FREE) {
                Object_Dying(this->index, this->obj.id);
            }
            break;
    }
}

void Boss_Update(Boss* this) {
    if (this->timer_050 != 0) {
        this->timer_050--;
    }
    if (this->timer_052 != 0) {
        this->timer_052--;
    }
    if (this->timer_054 != 0) {
        this->timer_054--;
    }
    if (this->timer_056 != 0) {
        this->timer_056--;
    }
    if (this->timer_058 != 0) {
        this->timer_058--;
    }
    if (this->timer_05A != 0) {
        this->timer_05A--;
    }
    if (this->timer_05C != 0) {
        this->timer_05C--;
    }
    switch (this->obj.status) {
        case OBJ_INIT:
            this->obj.status = OBJ_ACTIVE;
            Object_Init(this->index, this->obj.id);
            Boss_Move(this);
            break;
        case OBJ_ACTIVE:
            Boss_Move(this);
            if ((this->obj.status != OBJ_FREE) && (this->info.action != NULL)) {
                this->info.action(&this->obj);
            }
            break;
        case OBJ_DYING:
            Boss_Move(this);
            if (this->obj.status != OBJ_FREE) {
                Object_Dying(this->index, this->obj.id);
            }
            break;
    }
}

void Scenery_Update(Scenery* this) {
    if (this->timer_4C != 0) {
        this->timer_4C--;
    }
    switch (this->obj.status) {
        case OBJ_INIT:
            this->obj.status = OBJ_ACTIVE;
            Object_Init(this->index, this->obj.id);
            Scenery_Move(this);
            break;
        case OBJ_ACTIVE:
            Scenery_Move(this);
            if (this->info.action != NULL) {
                this->info.action(&this->obj);
            }
            break;
    }
}

void Sprite_Update(Sprite* this) {
    switch (this->obj.status) {
        case OBJ_INIT:
            this->obj.status = OBJ_ACTIVE;
            Object_Init(this->index, this->obj.id);
            Sprite_Move(this);
            break;
        case OBJ_ACTIVE:
            Sprite_Move(this);
            if (this->info.action != NULL) {
                this->info.action(&this->obj);
            }
            break;
        case OBJ_DYING:
            Sprite_Move(this);
            Object_Dying(this->index, this->obj.id);
            break;
    }
}

void Item_Update(Item* this) {
    if (this->timer_48 != 0) {
        this->timer_48--;
    }
    if (this->timer_4A != 0) {
        this->timer_4A--;
    }
    switch (this->obj.status) {
        case OBJ_INIT:
            this->obj.status = OBJ_ACTIVE;
            Object_Init(this->index, this->obj.id);
            Item_Move(this);
            break;
        case OBJ_ACTIVE:
            Item_Move(this);
            if (this->info.action != NULL) {
                this->info.action(&this->obj);
            }
            break;
    }
}

void Effect_Update(Effect* this) {
    if (this->timer_50 != 0) {
        this->timer_50--;
    }
    switch (this->obj.status) {
        case OBJ_INIT:
            this->obj.status = OBJ_ACTIVE;
            Object_Init(this->index, this->obj.id);
            /* fallthrough */
        case OBJ_ACTIVE:
            Effect_Move(this);
            if ((this->obj.status != OBJ_FREE) && (this->info.action != NULL)) {
                this->info.action(&this->obj);
            }
            break;
    }
}

void TexturedLine_Update(TexturedLine* this) {
    Vec3f sp44;
    Vec3f sp38;
    f32 dx;
    f32 dy;
    f32 dz;

    if (this->timer != 0) {
        this->timer--;
    }
    dx = this->posAA.x - this->posBB.x;
    dy = this->posAA.y - this->posBB.y;
    dz = this->posAA.z - this->posBB.z;
    this->yRot = Math_Atan2F(dx, dz);
    this->xRot = -Math_Atan2F(dy, sqrtf(SQ(dx) + SQ(dz)));
    if (this->mode != 4) {
        this->zScale = sqrtf(SQ(dx) + SQ(dy) + SQ(dz));
    }

    if (gGameState == GSTATE_PLAY) {
        if (((this->mode == 1) || (this->mode == 101) || (this->mode == 50)) &&
            (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_ACTIVE) && (gPlayer[0].hitTimer == 0)) {
            Matrix_RotateX(gCalcMatrix, -this->xRot, MTXF_NEW);
            Matrix_RotateY(gCalcMatrix, -this->yRot, MTXF_APPLY);
            sp44.x = gPlayer[gPlayerNum].pos.x - this->posAA.x;
            sp44.y = gPlayer[gPlayerNum].pos.y - this->posAA.y;
            sp44.z = gPlayer[gPlayerNum].trueZpos - this->posAA.z;
            Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp44, &sp38);
            sp38.x += this->posAA.x;
            sp38.y += this->posAA.y;
            sp38.z += this->posAA.z;
            if ((fabsf(sp38.x - this->posAA.x) < 30.0f) && (fabsf(sp38.y - this->posAA.y) < 30.0f) &&
                (sp38.z < this->posAA.z) && ((this->posAA.z - this->zScale) < sp38.z)) {
                if (gCurrentLevel == LEVEL_AQUAS) {
                    Player_ApplyDamage(&gPlayer[0], 0, 30);
                } else {
                    Player_ApplyDamage(&gPlayer[0], 0, 20);
                }
                if (this->mode < 100) {
                    this->mode = 0;
                }
            }
        }
        if (((this->posAA.z + gPathProgress) > 1000.0f) && (gLevelMode != LEVELMODE_ALL_RANGE)) {
            this->mode = 0;
        }
        if (((this->mode == 3) || (this->mode == 50)) && (this->timer == 0)) {
            this->mode = 0;
        }
    }
}

void TexturedLine_UpdateAll(void) {
    TexturedLine* texLine;
    s32 i;

    for (i = 0, texLine = gTexturedLines; i < ARRAY_COUNT(gTexturedLines); i++, texLine++) {
        if (texLine->mode != 0) {
            TexturedLine_Update(texLine);
        }
    }
}

void Object_Update(void) {
    s32 i;
    s32 pad;
    Scenery360* scenery360;
    Actor* actor;
    Boss* boss;
    Sprite* sprite;
    Scenery* scenery;
    Item* item;
    Effect* effect;

    gCullObjects = false;
    if ((gLevelMode == LEVELMODE_ON_RAILS) &&
        ((gPlayer[0].state_1C8 == PLAYERSTATE_1C8_INIT) || (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_ACTIVE) ||
         (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_DOWN) || (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_ENTER_WARP_ZONE) ||
         (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_START_360) || (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_NEXT))) {
        gCullObjects = true;
    }
    if (gLevelMode != LEVELMODE_ALL_RANGE) {
        if ((gLoadLevelObjects != 0) && (gPlayer[0].state_1C8 != PLAYERSTATE_1C8_LEVEL_INTRO)) {
            Object_LoadLevelObjects();
        }
        for (i = 0, scenery = gScenery; i < ARRAY_COUNT(gScenery); i++, scenery++) {
            if (scenery->obj.status != OBJ_FREE) {
                scenery->index = i;
                Scenery_Update(scenery);
            }
        }
    } else if (gVersusMode) {
        for (i = 0, scenery360 = gScenery360; i < 200; i++, scenery360++) {
            if ((scenery360->obj.status != OBJ_FREE) && (scenery360->obj.id == OBJ_SCENERY_146)) {
                if ((i % 2) != 0) {
                    scenery360->obj.rot.y += 0.5f;
                } else {
                    scenery360->obj.rot.y -= 0.5f;
                }
            }
        }
    }
    for (i = 0, sprite = gSprites; i < ARRAY_COUNT(gSprites); i++, sprite++) {
        if (sprite->obj.status != OBJ_FREE) {
            sprite->index = i;
            Sprite_Update(sprite);
        }
    }
    for (i = 0, boss = gBosses; i < ARRAY_COUNT(gBosses); i++, boss++) {
        if (boss->obj.status != OBJ_FREE) {
            boss->index = i;
            Boss_Update(boss);
        }
    }
    for (i = 0, actor = gActors; i < ARRAY_COUNT(gActors); i++, actor++) {
        if (actor->obj.status != OBJ_FREE) {
            actor->index = i;
            Actor_Update(actor);
        }
    }
    for (i = 0, item = gItems; i < ARRAY_COUNT(gItems); i++, item++) {
        if (item->obj.status != OBJ_FREE) {
            item->index = i;
            Item_Update(item);
        }
    }
    for (i = 0, effect = gEffects; i < ARRAY_COUNT(gEffects); i++, effect++) {
        if (effect->obj.status != OBJ_FREE) {
            effect->index = i;
            Effect_Update(effect);
        }
    }
    TexturedLine_UpdateAll();
    for (i = 0; i < ARRAY_COUNT(D_enmy_Timer_80161670); i++) {
        if (D_enmy_Timer_80161670[i] != 0) {
            D_enmy_Timer_80161670[i]--;
        }
    }
}
