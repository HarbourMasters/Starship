#include "PortEnhancements.h"
#include "global.h"
#include "hit64.h"
#include "mods.h"
#include "hud.h"

#define INIT_EVENT_IDS
#include "port/hooks/Events.h"

bool gBackToMap = false;

void OnDisplayUpdatePost(IEvent* event) {
#if DEBUG_BOSS_KILLER == 1
    KillBoss();
#endif

    if (CVarGetInteger("gDebugSpeedControl", 0) == 1) {
        Player* player = gPlayer;
        static s32 prevSpeed;
        static bool debugFreeze = false;

        if (gControllerPress[0].button & L_JPAD) {
            player->baseSpeed -= 50;
        } else if (gControllerPress[0].button & R_JPAD) {
            player->baseSpeed += 50;
        }

        if ((!debugFreeze) && (gControllerPress[0].button & D_JPAD)) {
            prevSpeed = player->baseSpeed;
            player->baseSpeed = 0;
            debugFreeze = true;
        } else if ((debugFreeze) && (gControllerPress[0].button & D_JPAD)) {
            player->baseSpeed = prevSpeed;
            debugFreeze = false;
        }
    }

    if (CVarGetInteger("gDebugJumpToMap", 0) == 1) {
        Player* pl = &gPlayer[0];

        if ((gGameState != GSTATE_PLAY) || (gPlayState <= PLAY_INIT)) {
            return;
        }

        if ((gControllerHold[0].button & Z_TRIG) && (gControllerHold[0].button & R_TRIG) &&
            (gControllerPress[0].button & U_CBUTTONS)) {
                gShowLevelClearStatusScreen = false;
                gLevelStartStatusScreenTimer = 0;
                gStarCount = 0;
                gGameState = GSTATE_MAP;
                gNextGameStateTimer = 2;
                gMapState = 0;
                gLastGameState = GSTATE_NONE;
                gDrawMode = DRAW_NONE;
                gControllerLock = 3;
                gBackToMap = true;
                gPlayerGlareAlphas[0] = 0;
        }
    }

    if (CVarGetInteger("gDebugWarpZone", 0) == 1) {
        if ((gGameState != GSTATE_PLAY) || (gPlayState <= PLAY_INIT)) {
            return;
        }
        if (gControllerPress[0].button & L_TRIG) {
            if ((gCurrentLevel != LEVEL_SECTOR_X) && (gCurrentLevel != LEVEL_METEO)) {
                return;
            }
            if (gCurrentLevel == LEVEL_SECTOR_X) {
                gRingPassCount++;
                gPlayer[0].state = PLAYERSTATE_ENTER_WARP_ZONE;
                gPlayer[0].csState = 0;
                gSceneSetup = 1;
                AUDIO_PLAY_SFX(NA_SE_WARP_HOLE, gDefaultSfxSource, 0);
                gMissionStatus = MISSION_WARP;
                gLeveLClearStatus[gCurrentLevel] = 1;
            } else {
                gPlayer[0].state = PLAYERSTATE_ENTER_WARP_ZONE;
                gPlayer[0].csState = 0;
                AUDIO_PLAY_SFX(NA_SE_WARP_HOLE, gDefaultSfxSource, 0);
                gMissionStatus = MISSION_WARP;
                gLeveLClearStatus[gCurrentLevel] = 1;
            }
        }
    }

    if (CVarGetInteger("gDebugNoCollision", 0) == 1) {
        if ((gGameState != GSTATE_PLAY) || (gPlayState <= PLAY_INIT)) {
            return;
        }
        gPlayer->mercyTimer = 1000;
    }

    if (CVarGetInteger("gDebugLevelComplete", 0) == 1) {
        Player* pl = &gPlayer[0];
        if ((gGameState != GSTATE_PLAY) || (gPlayState <= PLAY_INIT)) {
            return;
        }

        if (gControllerPress[0].button & L_TRIG) {
            pl->state = PLAYERSTATE_LEVEL_COMPLETE;
            gMissionStatus = MISSION_ACCOMPLISHED;
        }
    }

    if (CVarGetInteger("gDebugJumpToAllRange", 0) == 1) {
        Player* pl2 = &gPlayer[0];

        if ((gLevelMode != LEVELMODE_ALL_RANGE) && (gControllerPress[0].button & L_TRIG)) {
            pl2->state = PLAYERSTATE_START_360;
        }
    }

    // Cheats start here

    if (CVarGetInteger("gInfiniteLives", 0) == 1) {
        if ((gGameState != GSTATE_PLAY) || (gPlayState <= PLAY_INIT)) {
            return;
        }
        gLifeCount[0] = 9;
    }

    if (CVarGetInteger("gInfiniteBombs", 0) == 1) {
        if ((gGameState != GSTATE_PLAY) || (gPlayState <= PLAY_INIT)) {
            return;
        }
        gBombCount[0] = 9;
    }

    if (CVarGetInteger("gHyperLaser", 0) == 1) {
        if ((gGameState != GSTATE_PLAY) || (gPlayState <= PLAY_INIT)) {
            return;
        }
        gLaserStrength[0] = LASERS_HYPER;
    }

    if (CVarGetInteger("gScoreEditor", 0) == 1) {
        if ((gGameState != GSTATE_PLAY) || (gPlayState <= PLAY_INIT)) {
            return;
        }
        gHitCount = CVarGetInteger("gScoreEditValue", 1);
    }
    Hit64_Main();
    // ground testing
#if 0
    RCP_SetupDL(&gMasterDisp, SETUPDL_83);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);
    Graphics_DisplaySmallText(10, 210, 1.0f, 1.0f, "STICK_X:");
    Graphics_DisplaySmallNumber(60, 210, (int) ABS(gInputPress->stick_x));
    Graphics_DisplaySmallText(10, 220, 1.0f, 1.0f, "STICK_Y:");
    Graphics_DisplaySmallNumber(60, 220, (int) ABS(gInputPress->stick_y));
    if (gInputPress->stick_x < 0) Graphics_DisplaySmallText(110, 210, 1.0f, 1.0f, "NEG:");
    if (gInputPress->stick_y < 0) Graphics_DisplaySmallText(110, 220, 1.0f, 1.0f, "NEG:");
#endif
}

void OnGameUpdatePost(IEvent* event) {
#if MODS_RAM_MOD == 1
    RamMod_Update();
#endif
    if (CVarGetInteger("gSpawnerMod", 0) == 1) {
        Spawner();
    }
}

void RefillBoostMeter(Player* player) {
    if (player->boostMeter > 1.0f) {
        player->boostMeter = 1.0f;
    }
}
void OnPlayerUpdatePost(PlayerPostUpdateEvent* event) {
    if (CVarGetInteger("gInfiniteBoost", 0) == 1) {
        if (event->player->boostSpeed < 0.0f) {
            event->player->boostSpeed += 0.5f;
            if (event->player->boostSpeed > 0.0f) {
                event->player->boostSpeed = 0.0f;
            }
        }
    }
}

void OnPlayerBoost(PlayerActionBoostEvent* event) {
    if (CVarGetInteger("gInfiniteBoost", 0) == 1) {
        RefillBoostMeter(event->player);
    }
}
void OnPlayerBrake(PlayerActionBrakeEvent* event) {
    if (CVarGetInteger("gInfiniteBoost", 0) == 1) {
        RefillBoostMeter(event->player);
    }
}

void OnPlayerShootPost(PlayerActionPostShootEvent* event) {
    event->shot->timer *= CVarGetInteger("gLaserRangeMult", 100) / 100.0f;
}

void OnItemGoldRingDraw(ObjectDrawPostSetupEvent* event) {
    if (event->type != OBJECT_TYPE_ITEM) {
        return;
    }

    Item* item = (Item*) event->object;
    if (item->obj.id != OBJ_ITEM_GOLD_RING || CVarGetInteger("gRestoreBetaCoin", 0) != 1) {
        return;
    }

    event->event.cancelled = true;
    RCP_SetupDL(&gMasterDisp, SETUPDL_29_POINT);
    Graphics_SetScaleMtx(item->width * 2.0f);
    gSPDisplayList(gMasterDisp++, D_101D870);
}

void OnItemGoldRingUpdate(ObjectUpdateEvent* event){
    if (event->type != OBJECT_TYPE_ITEM) {
        return;
    }

    Item* item = (Item*) event->object;
    if (item->obj.id != OBJ_ITEM_GOLD_RING || CVarGetInteger("gRestoreBetaCoin", 0) != 1) {
        return;
    }

    Item_CheckBounds(item);
    switch (item->state) {
        case 0:
            if (item->collected) {
                item->state = 1;
                item->timer_48 = 0;
                gGoldRingCount[0]++;
                if (gGoldRingCount[0] == 3) {
                    Object_PlayerSfx(gPlayer[item->playerNum].sfxSource, NA_SE_SHIELD_UPGRADE, item->playerNum);
                } else if (gGoldRingCount[0] == 6) {
                    Object_PlayerSfx(gPlayer[item->playerNum].sfxSource, NA_SE_ONE_UP, item->playerNum);
                    if (gCurrentLevel != LEVEL_TRAINING) {
                        gLifeCount[item->playerNum]++;
                    }
                    gPlayer[item->playerNum].heal += 32;
                    BonusText_Display(gPlayer[item->playerNum].pos.x, gPlayer[item->playerNum].pos.y,
                                      gPlayer[item->playerNum].trueZpos, BONUS_TEXT_1UP);
                } else {
                    gPlayer[item->playerNum].heal += 32;
                    Object_PlayerSfx(gPlayer[item->playerNum].sfxSource, NA_SE_GOLD_RING, item->playerNum);
                }
            }

            if (item->timer_48 == 1) {
                Object_Kill(&item->obj, item->sfxSource);
            }
            break;

        case 1:
            ItemSupplyRing_Update(item);
            break;
    }
}

static const char* sBoostGaugeArrow[] = {
    sBoostGaugeArrow0,
    sBoostGaugeArrow1,
    sBoostGaugeArrow2,
    sBoostGaugeArrow3,
    sBoostGaugeArrow4,
    sBoostGaugeArrow5,
    sBoostGaugeArrow6,
    sBoostGaugeArrow7,
    sBoostGaugeArrow8,
};

void OnBoostGaugeDraw(IEvent* event){
    bool restore = CVarGetInteger("gRestoreOldBoostGauge", 0) == 1;

    if(!restore){
        return;
    }

    event->cancelled = true;
    u8 step = MIN(8, (u8) ((gPlayer[0].boostMeter / 90.0f) * ARRAY_COUNT(sBoostGaugeArrow)));
    f32 x = 70;
    f32 y = 30;

    RCP_SetupDL(&gMasterDisp, SETUPDL_76_POINT);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
    Lib_TextureRect_CI8(&gMasterDisp, D_1012290, D_10126B0, 48, 22, OTRGetRectDimensionFromRightEdge(SCREEN_WIDTH - x), y, 1.0f, 1.0f);
    Lib_TextureRect_CI8(&gMasterDisp, D_10126F0, D_1012750, 24, 4, OTRGetRectDimensionFromRightEdge(SCREEN_WIDTH - (x - 9)), y + 3, 1.0f, 1.0f);
    Lib_TextureRect_RGBA16(&gMasterDisp, sBoostGaugeArrow[step], 32, 32, OTRGetRectDimensionFromRightEdge(SCREEN_WIDTH - (x - 6)), y - 1, 0.9f, 0.9f);
}

void OnBombCounterDraw(IEvent* ev){
    bool restore = CVarGetInteger("gRestoreOldBoostGauge", 0) == 1;
    if(!restore){
        return;
    }

    ev->cancelled = true;
    HUD_BombCounter_Draw(253.0f, 18.0f);
}

void OnLivesCounterDraw(IEvent* ev){
    bool restore = CVarGetInteger("gRestoreOldBoostGauge", 0) == 1;
    if(!restore){
        return;
    }
    ev->cancelled = true;

    HUD_LivesCount2_Draw(258.0f, SCREEN_HEIGHT - 20, gLifeCount[gPlayerNum]);
}

void PortEnhancements_Init() {
    PortEnhancements_Register();

    // Register event listeners
    REGISTER_LISTENER(DisplayPostUpdateEvent, OnDisplayUpdatePost, EVENT_PRIORITY_NORMAL);
    REGISTER_LISTENER(GamePostUpdateEvent, OnGameUpdatePost, EVENT_PRIORITY_NORMAL);
    REGISTER_LISTENER(PlayerPostUpdateEvent, OnPlayerUpdatePost, EVENT_PRIORITY_NORMAL);
    REGISTER_LISTENER(DrawBoostGaugeHUDEvent, OnBoostGaugeDraw, EVENT_PRIORITY_NORMAL);
    REGISTER_LISTENER(DrawLivesCounterHUDEvent, OnLivesCounterDraw, EVENT_PRIORITY_NORMAL);
    REGISTER_LISTENER(DrawBombCounterHUDEvent, OnBombCounterDraw, EVENT_PRIORITY_NORMAL);

    REGISTER_LISTENER(ObjectUpdateEvent, OnItemGoldRingUpdate, EVENT_PRIORITY_NORMAL);
    REGISTER_LISTENER(ObjectDrawPostSetupEvent, OnItemGoldRingDraw, EVENT_PRIORITY_NORMAL);

    // Register Action listeners
    REGISTER_LISTENER(PlayerActionBoostEvent, OnPlayerBoost, EVENT_PRIORITY_NORMAL);
    REGISTER_LISTENER(PlayerActionBrakeEvent, OnPlayerBrake, EVENT_PRIORITY_NORMAL);
    REGISTER_LISTENER(PlayerActionPostShootEvent, OnPlayerShootPost, EVENT_PRIORITY_NORMAL);
}

void PortEnhancements_Register() {
    // Register engine events
    REGISTER_EVENT(DisplayPreUpdateEvent);
    REGISTER_EVENT(DisplayPostUpdateEvent);

    REGISTER_EVENT(GamePreUpdateEvent);
    REGISTER_EVENT(GamePostUpdateEvent);

    REGISTER_EVENT(PlayerPreUpdateEvent);
    REGISTER_EVENT(PlayerPostUpdateEvent);

    REGISTER_EVENT(DrawRadarHUDEvent);
    REGISTER_EVENT(DrawBoostGaugeHUDEvent);
    REGISTER_EVENT(DrawBombCounterHUDEvent);
    REGISTER_EVENT(DrawIncomingMsgHUDEvent);
    REGISTER_EVENT(DrawGoldRingsHUDEvent);
    REGISTER_EVENT(DrawLivesCounterHUDEvent);
    REGISTER_EVENT(DrawTrainingRingPassCountHUDEvent);
    REGISTER_EVENT(DrawEdgeArrowsHUDEvent);
    REGISTER_EVENT(DrawBossHealthHUDEvent);
    REGISTER_EVENT(DrawGlobalHUDPreEvent);
    REGISTER_EVENT(DrawGlobalHUDPostEvent);

    // Register item events
    REGISTER_EVENT(ItemDropEvent);

    // Register actor events
    REGISTER_EVENT(ObjectInitEvent);
    REGISTER_EVENT(ObjectUpdateEvent);
    REGISTER_EVENT(ObjectDrawPreSetupEvent);
    REGISTER_EVENT(ObjectDrawPostSetupEvent);
    REGISTER_EVENT(ObjectDestroyEvent);

    // Register player action events
    REGISTER_EVENT(PlayerActionBoostEvent);
    REGISTER_EVENT(PlayerActionBrakeEvent);

    REGISTER_EVENT(PlayerActionPreShootEvent);
    REGISTER_EVENT(PlayerActionPostShootEvent);

    REGISTER_EVENT(PlayerActionPreShootChargedEvent);
    REGISTER_EVENT(PlayerActionPostShootChargedEvent);

    REGISTER_EVENT(PlayerActionPreBombEvent);
    REGISTER_EVENT(PlayerActionPostBombEvent);
}

void PortEnhancements_Exit() {
    // TODO: Unregister event listeners
}