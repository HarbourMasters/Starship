/*
 * File: spawner.c
 * System: Spawner
 * Description: Spawner module meant to help documenting the rest of the code
 * by being able to spawn Scenery, Sprites, Actors, Bosses, Items, Effects and Events.
 * This is not part of the original game.
 */

#include "global.h"
#include "sf64object.h"

typedef enum ObjType {
    /* 0 */ OBJ_SPAWN_SCENERY,
    /* 1 */ OBJ_SPAWN_SCENERY_360,
    /* 2 */ OBJ_SPAWN_SPRITE,
    /* 3 */ OBJ_SPAWN_ACTOR,
    /* 4 */ OBJ_SPAWN_BOSS,
    /* 5 */ OBJ_SPAWN_ITEM,
    /* 6 */ OBJ_SPAWN_EFFECT,
    /* 7 */ OBJ_SPAWN_EVENT,
    /* 8 */ OBJ_SPAWN_MAX
} ObjType;

typedef struct ObjCount {
    s32 actor;
    s32 boss;
    s32 scenery;
    s32 sprite;
    s32 effect;
    s32 item;
} ObjCount;

static int sObjId = 0;
static int sObjType = 0;

static int sTextXpos = 239;
static int sTextYpos = 173;

static OSContPad* sContPress;
static OSContPad* sContHold;

void Scenery_Load(Scenery* this, ObjectInit* objInit);
void Sprite_Load(Sprite* this, ObjectInit* objInit);
void Item_Load(Item* this, ObjectInit* objInit);
void Boss_Load(Boss* this, ObjectInit* objInit);

void Spawner_Actor(int actorId) {
    if ((gControllerPress[0].button & L_TRIG) && (actorId >= OBJ_ACTOR_CO_GARUDA_1) &&
        (actorId <= OBJ_ACTOR_SUPPLIES)) {
        Vec3f* reticlePos = &D_display_801613E0[0];
        Actor* actorSpawn = Game_SpawnActor(actorId);

        if (actorSpawn != NULL) {
            actorSpawn->obj.pos.x = reticlePos->x * 1.7f;
            actorSpawn->obj.pos.y = 200.0f;
            actorSpawn->obj.pos.z = gPlayer[0].pos.z - 1500.0f - (reticlePos->y * 1.7f);
            actorSpawn->state = 0;
        }
    }
}

void Spawner_Boss(int bossId) {
    if ((gControllerPress[0].button & L_TRIG) && (bossId >= OBJ_BOSS_CO_GRANGA) && (bossId <= OBJ_BOSS_AND_BRAIN)) {
        Vec3f* reticlePos = &D_display_801613E0[0];
        ObjectInit objInit;
        s32 i;

        objInit.zPos1 = objInit.zPos2 = 0;
        objInit.xPos = reticlePos->x * 1.7f;
        objInit.yPos = 200.0f;
        objInit.rot.x = objInit.rot.y = objInit.rot.z = 0;
        objInit.id = bossId;

        for (i = 0; i < ARRAY_COUNT(gBosses); i++) {
            if (gBosses[i].obj.status == OBJ_FREE) {
                Boss_Load(&gBosses[i], &objInit);
                gBosses[i].obj.pos.z = gPlayer[0].pos.z - 1500.0f - (reticlePos->y * 1.7f);
                break;
            }
        }
    }
}

void Spawner_Scenery(int sceneryId) {
    if ((gControllerPress[0].button & L_TRIG) && (sceneryId >= OBJ_SCENERY_CO_STONE_ARCH) &&
        (sceneryId <= OBJ_SCENERY_VE2_MOUNTAIN)) {
        Vec3f* reticlePos = &D_display_801613E0[0];
        ObjectInit objInit;
        s32 i;

        objInit.zPos1 = objInit.zPos2 = 0;
        objInit.xPos = reticlePos->x * 1.7f;
        objInit.yPos = 200.0f;
        objInit.rot.x = objInit.rot.y = objInit.rot.z = 0;
        objInit.id = sceneryId;

        for (i = 0; i < ARRAY_COUNT(gScenery); i++) {
            if (gScenery[i].obj.status == OBJ_FREE) {
                Scenery_Load(&gScenery[i], &objInit);
                gScenery[i].obj.pos.z = gPlayer[0].pos.z - 1500.0f - (reticlePos->y * 4.7f);
                break;
            }
        }
    }
}

void Spawner_Scenery360(s32 scenery360Id) {
    if ((gControllerPress[0].button & L_TRIG) && (scenery360Id >= OBJ_SCENERY_AND_PATH_INTERSECTION) &&
        (scenery360Id <= OBJ_SCENERY_VE2_MOUNTAIN)) {
        Vec3f* reticlePos = &D_display_801613E0[0];
        s32 i;

        for (i = 0; i < 200; i++) {
            if (gScenery360[i].obj.status == OBJ_FREE) {
                Scenery360_Initialize(&gScenery360[i]);
                gScenery360[i].obj.status = OBJ_ACTIVE;
                gScenery360[i].obj.id = scenery360Id;

                gScenery360[i].obj.pos.x = +reticlePos->x * 5.0f;
                gScenery360[i].obj.pos.z = -reticlePos->y * 5.0f;

                if (gLevelType == LEVELTYPE_PLANET) {
                    gScenery360[i].obj.pos.y = gGroundHeight;
                } else {
                    gScenery360[i].obj.pos.y = gPlayer[0].pos.y;
                }

                gScenery360[i].obj.rot.y = 0;
                Object_SetInfo(&gScenery360[i].info, gScenery360[i].obj.id);
                break;
            }
        }
    }
}

void Spawner_Sprite(int spriteId) {
    if ((gControllerPress[0].button & L_TRIG) && (spriteId >= OBJ_SPRITE_CO_POLE) &&
        (spriteId <= OBJ_SPRITE_GFOX_TARGET)) {
        Vec3f* reticlePos = &D_display_801613E0[0];
        ObjectInit objInit;
        s32 i;

        objInit.zPos1 = objInit.zPos2 = 0;
        objInit.xPos = reticlePos->x * 1.7f;
        objInit.yPos = 200.0f;
        objInit.rot.x = objInit.rot.y = objInit.rot.z = 0;
        objInit.id = spriteId;

        for (i = 0; i < ARRAY_COUNT(gSprites); i++) {
            if (gSprites[i].obj.status == OBJ_FREE) {
                Sprite_Load(&gSprites[i], &objInit);
                gSprites[i].obj.pos.z = gPlayer[0].pos.z - 1500.0f - (reticlePos->y * 1.7f);
                break;
            }
        }
    }
}

void Spawner_Item(int itemId) {
    if ((gControllerPress[0].button & L_TRIG) && (itemId >= OBJ_ITEM_LASERS) && (itemId <= OBJ_ITEM_TRAINING_RING)) {
        Vec3f* reticlePos = &D_display_801613E0[0];
        ObjectInit objInit;
        s32 i;

        objInit.zPos1 = objInit.zPos2 = 0;
        objInit.xPos = reticlePos->x * 1.7f;
        objInit.yPos = 200.0f;
        objInit.rot.x = objInit.rot.y = objInit.rot.z = 0;
        objInit.id = itemId;

        for (i = 0; i < ARRAY_COUNT(gItems); i++) {
            if (gItems[i].obj.status == OBJ_FREE) {
                Item_Load(&gItems[i], &objInit);
                gItems[i].obj.pos.z = gPlayer[0].pos.z - 1500.0f - (reticlePos->y * 1.7f);
                break;
            }
        }
    }
}

void Spawner_Event(int eventId) {
    if (gControllerPress[0].button & L_TRIG) {
        Vec3f* reticlePos = &D_display_801613E0[0];
        ObjectInit objInit;
        s32 i;

        for (i = 0; i < ARRAY_COUNT(gActors); i++) {
            if (gActors[i].obj.status == OBJ_FREE) {
                objInit.zPos1 = gPlayer[0].pos.z - 1500.0f - (reticlePos->y * 1.7f);
                objInit.zPos2 = gPlayer[0].pos.z - 1500.0f - (reticlePos->y * 1.7f) + 300.0f;
                objInit.xPos = reticlePos->x * 1.7f;
                objInit.yPos = 200.0f;
                objInit.rot.x = 0;
                objInit.rot.y = 0;
                objInit.rot.z = 0;
                objInit.id = ACTOR_EVENT_ID + eventId;
                ActorEvent_Load(&gActors[i], &objInit, i);
                gActors[i].obj.pos.z = gPlayer[0].pos.z - 1500.0f - (reticlePos->y * 1.7f);
                break;
            }
        }
    }
}

void Spawner_Effect(int effectId) {
    if ((gControllerPress[0].button & L_TRIG) && (effectId >= OBJ_EFFECT_FIRE_SMOKE_1) && (effectId < OBJ_ID_MAX)) {
        Vec3f* reticlePos = &D_display_801613E0[0];
        s32 i;

        for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
            if (gEffects[i].obj.status == OBJ_FREE) {
                Effect_Initialize(&gEffects[i]);
                gEffects[i].obj.status = OBJ_INIT;
                gEffects[i].obj.id = effectId;
                gEffects[i].obj.pos.x = reticlePos->x * 1.7f;
                gEffects[i].obj.pos.y = 200.0f;
                gEffects[i].obj.pos.z = gPlayer[0].pos.z - 1000.0f - (reticlePos->y * 1.7f);
                gEffects[i].vel.x = 0;
                gEffects[i].vel.y = 0;
                gEffects[i].vel.z = 0;
                gEffects[i].obj.rot.x = 0;
                gEffects[i].obj.rot.y = 0;
                gEffects[i].obj.rot.z = 0;
                // gEffects[i].timer_50 = 200;
                Object_SetInfo(&gEffects[i].info, gEffects[i].obj.id);
                break;
            }
        }
    }
}

ObjCount Spawner_ObjCount(void) {
    ObjCount counter = { 0, 0, 0, 0, 0, 0 };
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gActors); i++) {
        if (gActors[i].obj.status != OBJ_FREE) {
            counter.actor++;
        }
    }
    for (i = 0; i < ARRAY_COUNT(gBosses); i++) {
        if (gBosses[i].obj.status != OBJ_FREE) {
            counter.boss++;
        }
    }
    for (i = 0; i < ARRAY_COUNT(gScenery); i++) {
        if (gScenery[i].obj.status != OBJ_FREE) {
            counter.scenery++;
        }
    }
    if (gLevelMode == LEVELMODE_ALL_RANGE) {
        for (i = 0; i < 200; i++) {
            if (gScenery360[i].obj.status != OBJ_FREE) {
                counter.scenery++;
            }
        }
    }
    for (i = 0; i < ARRAY_COUNT(gSprites); i++) {
        if (gSprites[i].obj.status != OBJ_FREE) {
            counter.sprite++;
        }
    }
    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        if (gEffects[i].obj.status != OBJ_FREE) {
            counter.effect++;
        }
    }
    for (i = 0; i < ARRAY_COUNT(gItems); i++) {
        if (gItems[i].obj.status != OBJ_FREE) {
            counter.item++;
        }
    }
    return counter;
}

void Spawner_ObjKill(void) {
    s32 i;

    for (i = 0; i <= ARRAY_COUNT(gActors); i++) {
        Object_Kill(&gActors[i].obj, gActors[i].sfxSource);
    }
    for (i = 0; i <= ARRAY_COUNT(gBosses); i++) {
        Object_Kill(&gBosses[i].obj, gBosses[i].sfxSource);
    }
    for (i = 0; i <= ARRAY_COUNT(gScenery); i++) {
        Object_Kill(&gScenery[i].obj, gScenery[i].sfxSource);
    }
    for (i = 0; i <= ARRAY_COUNT(gSprites); i++) {
        Sprite_Initialize(&gSprites[i]);
    }
    for (i = 0; i <= ARRAY_COUNT(gEffects); i++) {
        Object_Kill(&gEffects[i].obj, gEffects[i].sfxSource);
    }
    for (i = 0; i <= ARRAY_COUNT(gItems); i++) {
        Object_Kill(&gItems[i].obj, gItems[i].sfxSource);
    }
    if (gLevelMode == LEVELMODE_ALL_RANGE) {
        for (i = 0; i < 200; i++) {
            gScenery360[i].obj.status = OBJ_FREE;
        }
    }
}

// Use this function to add code that eases your documentation work!
void Spawner_Playground(void) {
    Player* player = &gPlayer[0];

    player->mercyTimer = 100;
    gLaserStrength[0] = 2;
    gBombCount[0] = 9;
    gLifeCount[0] = 9;

#if 0
    if (gControllerPress[0].button & L_JPAD) {
        gArwingSpeed -= 50;
    } else if (gControllerPress[0].button & R_JPAD) {
        gArwingSpeed += 50;
    }
#endif
}

void Spawner(void) {
    static bool sFreeze = true;
    static s32 sHoldTimer = 0;
    ObjCount counter;

    /* Prevent execution before gameplay */
    if ((gGameState != GSTATE_PLAY) || (gPlayState <= PLAY_INIT)) {
        return;
    }

    Spawner_Playground();

    /* Object Selector */
    sContPress = &gControllerPress[gMainController];
    sContHold = &gControllerHold[gMainController];

    if (sContHold->button & (L_JPAD | R_JPAD)) {
        sHoldTimer++;
    } else {
        sHoldTimer = 0;
    }

    if (((sContHold->button & L_JPAD) && (sHoldTimer > 15)) || (sContPress->button & L_JPAD)) {
        sObjId--;
    } else if (((sContHold->button & R_JPAD) && (sHoldTimer > 15)) || (sContPress->button & R_JPAD)) {
        sObjId++;
    } else if (gControllerPress[0].button & D_JPAD) {
        sFreeze ^= 1; // Freeze arwing.
    } else if (gControllerPress[0].button & U_JPAD) {
        Spawner_ObjKill();
    } else if (gControllerPress[0].button & R_CBUTTONS) {
        sObjType++;
        switch (sObjType) {
            case OBJ_SPAWN_EVENT:
                sObjId = EVID_VENOM_FIGHTER_1;
                break;
            case OBJ_SPAWN_SCENERY:
                sObjId = OBJ_SCENERY_CO_STONE_ARCH;
                break;
            case OBJ_SPAWN_SCENERY_360:
                sObjId = OBJ_SCENERY_AND_PATH_INTERSECTION;
                break;
            case OBJ_SPAWN_SPRITE:
                sObjId = OBJ_SPRITE_CO_POLE;
                break;
            case OBJ_SPAWN_ACTOR:
                sObjId = OBJ_ACTOR_CO_GARUDA_1;
                break;
            case OBJ_SPAWN_BOSS:
                sObjId = OBJ_BOSS_CO_GRANGA;
                break;
            case OBJ_SPAWN_ITEM:
                sObjId = OBJ_ITEM_LASERS;
                break;
            case OBJ_SPAWN_EFFECT:
                sObjId = OBJ_EFFECT_FIRE_SMOKE_1;
                break;
            default:
                sObjId = 0;
                break;
        }
    }

    if (sObjId < 0) {
        sObjId = 0;
    }

    if (sObjType >= OBJ_SPAWN_MAX) {
        sObjType = OBJ_SPAWN_SCENERY;
    }

    /* Freeze arwing */
    if (sFreeze) {
        gPlayer[0].baseSpeed = 0;
    } else {
        gPlayer[0].baseSpeed = gArwingSpeed;
    }

    RCP_SetupDL(&gMasterDisp, SETUPDL_83_OPTIONAL);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);

    /* Spawners */
    switch (sObjType) {
        case OBJ_SPAWN_SCENERY:
            Graphics_DisplaySmallText(10, 220, 1.0f, 1.0f, "SCENERY:");
            Graphics_DisplaySmallNumber(80, 220, sObjId);
            Spawner_Scenery(sObjId);
            break;
        case OBJ_SPAWN_SCENERY_360:
            Graphics_DisplaySmallText(10, 220, 1.0f, 1.0f, "SCENERY360:");
            Graphics_DisplaySmallNumber(100, 220, sObjId);
            Spawner_Scenery360(sObjId);
            break;
        case OBJ_SPAWN_SPRITE:
            Graphics_DisplaySmallText(10, 220, 1.0f, 1.0f, "SPRITE:");
            Graphics_DisplaySmallNumber(65, 220, sObjId);
            Spawner_Sprite(sObjId);
            break;
        case OBJ_SPAWN_ACTOR:
            Graphics_DisplaySmallText(10, 220, 1.0f, 1.0f, "ACTOR:");
            Graphics_DisplaySmallNumber(60, 220, sObjId);
            Spawner_Actor(sObjId);
            break;
        case OBJ_SPAWN_BOSS:
            Graphics_DisplaySmallText(10, 220, 1.0f, 1.0f, "BOSS:");
            Graphics_DisplaySmallNumber(55, 220, sObjId);
            Spawner_Boss(sObjId);
            break;
        case OBJ_SPAWN_ITEM:
            Graphics_DisplaySmallText(10, 220, 1.0f, 1.0f, "ITEM:");
            Graphics_DisplaySmallNumber(50, 220, sObjId);
            Spawner_Item(sObjId);
            break;
        case OBJ_SPAWN_EFFECT:
            Graphics_DisplaySmallText(10, 220, 1.0f, 1.0f, "EFFECT:");
            Graphics_DisplaySmallNumber(65, 220, sObjId);
            Spawner_Effect(sObjId);
            break;
        case OBJ_SPAWN_EVENT:
            Graphics_DisplaySmallText(10, 220, 1.0f, 1.0f, "EVENT:");
            Graphics_DisplaySmallNumber(60, 220, sObjId);
            Spawner_Event(sObjId);
            break;
        default:
            break;
    }

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    Graphics_DisplaySmallText(sTextXpos - 8, sTextYpos + 00, 1.0f, 1.0f, "SCENERY:");
    Graphics_DisplaySmallText(sTextXpos - 4, sTextYpos + 10, 1.0f, 1.0f, "SPRITES:");
    Graphics_DisplaySmallText(sTextXpos + 0, sTextYpos + 20, 1.0f, 1.0f, "ACTORS:");
    Graphics_DisplaySmallText(sTextXpos + 0, sTextYpos + 30, 1.0f, 1.0f, "BOSSES:");
    Graphics_DisplaySmallText(sTextXpos + 12, sTextYpos + 40, 1.0f, 1.0f, "ITEMS:");
    Graphics_DisplaySmallText(sTextXpos - 8, sTextYpos + 50, 1.0f, 1.0f, "EFFECTS:");

    counter = Spawner_ObjCount();

    Graphics_DisplaySmallNumber(sTextXpos + 55, sTextYpos + 00, counter.scenery);
    Graphics_DisplaySmallNumber(sTextXpos + 55, sTextYpos + 10, counter.sprite);
    Graphics_DisplaySmallNumber(sTextXpos + 55, sTextYpos + 20, counter.actor);
    Graphics_DisplaySmallNumber(sTextXpos + 55, sTextYpos + 30, counter.boss);
    Graphics_DisplaySmallNumber(sTextXpos + 55, sTextYpos + 40, counter.item);
    Graphics_DisplaySmallNumber(sTextXpos + 55, sTextYpos + 50, counter.effect);
}
