#include "global.h"
#include "assets/ast_katina.h"
#include "assets/ast_venom_2.h"
#include "assets/ast_fortuna.h"
#include "assets/ast_star_wolf.h"
#include "assets/ast_allies.h"
#include "assets/ast_bolse.h"
#include "assets/ast_versus.h"
#include "assets/ast_enmy_planet.h"
#include "assets/ast_sector_z.h"

typedef enum ActorAllRangeState {
    STATE360_0,
    STATE360_1,
    STATE360_2,
    STATE360_3,
    STATE360_4,
    STATE360_5,
    STATE360_6,
    STATE360_7,
    STATE360_8,
    STATE360_9,
    STATE360_10,
    STATE360_11,
    STATE360_12,
    STATE360_13,
    STATE360_14,
    STATE360_15,
    STATE360_16,
    STATE360_17,
    STATE360_18,
    STATE360_19,
} ActorAllRangeState;

s32 gAllRangeSupplyTimer;
s32 sStarWolfKillTimer;
s16 gStarWolfMsgTimer;
s32 gAllRangeWingRepairTimer;
s32 gAllRangeSuppliesSent;
f32 gSzMissileR;
f32 gSzMissileG;
f32 gSzMissileB;
u8 gKaKilledAlly;
u8 gKaAllyKillCount;
s32 gAllRangeCheckpoint;
s32 gAllRangeEventTimer;
s32 gAllRangeCountdown[3];
bool gShowAllRangeCountdown;
s32 gAllRangeFrameCount;
f32 gAllRangeCountdownScale;

void AllRange_GetStarWolfHits(Actor* this) {
    s32 hits = 0;

    PRINTF("time=%d\n");
    PRINTF("time=%d\n");
    PRINTF("time=%d\n");
    PRINTF("time=%d\n");
    PRINTF("time=%d\n");

    if (gCurrentLevel == LEVEL_VENOM_2) {
        if (gAllRangeFrameCount < 128 * 30) {
            hits = 50;
        } else if (gAllRangeFrameCount < 192 * 30) {
            hits = 30;
        } else if (gAllRangeFrameCount < 256 * 30) {
            hits = 20;
        } else if (gAllRangeFrameCount < 320 * 30) {
            hits = 10;
        }
    } else {
        if (gAllRangeFrameCount < 128 * 30) {
            hits = 10;
        } else if (gAllRangeFrameCount < 192 * 30) {
            hits = 5;
        } else if (gAllRangeFrameCount < 256 * 30) {
            hits = 2;
        } else if (gAllRangeFrameCount < 320 * 30) {
            hits = 1;
        }
    }
    if (hits != 0) {
        BonusText_Display(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, hits);
    }
    gHitCount += hits;
    D_ctx_80177850 = 15;
}

bool AllRange_PlayMessage(u16* msg, RadioCharacterId rcid) {
    if ((gRadioState == 0) && (gPlayer[0].state != PLAYERSTATE_STANDBY)) {
        Radio_PlayMessage(msg, rcid);
        return true;
    } else {
        return false;
    }
}

void AllRange_DrawCountdown(void) {
    if (gShowAllRangeCountdown) {
        s32 seconds = gAllRangeCountdown[1];

        HUD_DrawCountdown(gAllRangeCountdown, gAllRangeCountdownScale);
        if ((gAllRangeCountdown[0] == 0) && (seconds != gAllRangeCountdown[1]) && (gAllRangeCountdown[1] < 15)) {
            AUDIO_PLAY_SFX(NA_SE_COUNTDOWN, gDefaultSfxSource, 4);
        }
    }
}

void BoBase_Update(BoBase* this) {
    OvlI4_CallFunction(OVLCALL_BO_BASE_UPDATE, this);
}

void BoBase_Draw(BoBase* this) {
    OvlI4_CallFunction(OVLCALL_BO_BASE_DRAW, this);
}

void BoBaseShield_Update(BoBaseShield* this) {
    OvlI4_CallFunction(OVLCALL_BO_BASE_SHIELD_UPDATE, this);
}

void BoBaseShield_Draw(BoBaseShield* this) {
    OvlI4_CallFunction(OVLCALL_BO_BASE_SHIELD_DRAW, this);
}

void BoShieldReactor_Update(BoShieldReactor* this) {
    OvlI4_CallFunction(OVLCALL_BO_SHIELD_REACTOR_UPDATE, this);
}

void BoShieldReactor_Draw(BoShieldReactor* this) {
    OvlI4_CallFunction(OVLCALL_BO_SHIELD_REACTOR_DRAW, this);
}

void BoLaserCannon_Update(BoLaserCannon* this) {
    OvlI4_CallFunction(OVLCALL_BO_LASER_CANNON_UPDATE, this);
}

void BoLaserCannon_Draw(BoLaserCannon* this) {
    OvlI4_CallFunction(OVLCALL_BO_LASER_CANNON_DRAW, this);
}

void AllRange_GreatFoxRepair(Player* player) {
    Vec3f src;
    Vec3f dest;

    gCsFrameCount++;

    switch (player->csState) {
        case 0:
            player->hitTimer = player->mercyTimer = player->damage = player->barrelRollAlpha = player->boostMeter =
                player->boostCooldown = player->somersault = gCsFrameCount = 0;
            player->zRotBarrelRoll = player->camRoll = player->boostSpeed = player->camDist = player->knockback.x =
                player->knockback.y = player->knockback.z = player->damageShake = player->aerobaticPitch = 0.0f;

            gCsCamEyeX = 1673.0f;
            gCsCamEyeY = 337.0f;
            if (player->pos.z < 0.0f) {
                gCsCamEyeZ = -480.0f;
            } else {
                gCsCamEyeZ = 480.0f;
            }
            player->rot.y = 0.0f;
            player->pos.x = 2100.0f;
            player->baseSpeed = 30.0f;
            player->rot.x = -8.0f;
            player->yRot_114 = 90.0f;
            gCsCamAtX = 2100.0f;
            player->pos.y = 450.0f;
            gCsCamAtY = 450.0f;
            player->pos.z = 0.0f;
            gCsCamAtZ = 0.0f;
            D_ctx_80177A48[0] = 1.0f;
            player->arwing.drawFace = true;
            player->csState++;
            break;

        case 1:
            if (gCsFrameCount >= 47) {
                gFillScreenAlphaTarget = 255;
                gFillScreenAlphaStep = 32;
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
            }
            if (gCsFrameCount >= 64) {
                player->csState++;
                player->baseSpeed = 0.0f;
            }
            break;

        case 2:
            if (gFillScreenAlpha == 255) {
                gFillScreenAlphaTarget = 0;
                player->pos.x = 400.0f;
                player->pos.y = -420.0f;
                player->pos.z = 0.0f;
                player->rot.z = 0.0f;
                gCsCamEyeX = -683.0f;
                gCsCamEyeY = -346.0f;
                gCsCamEyeZ = 305.0f;

                player->shields = Play_GetMaxShields();
                player->arwing.rightWingState = WINGSTATE_INTACT;
                player->arwing.leftWingState = WINGSTATE_INTACT;

                if (gExpertMode) {
                    gRightWingHealth[0] = gLeftWingHealth[0] = 10;
                } else {
                    gRightWingHealth[0] = gLeftWingHealth[0] = 60;
                }
                AUDIO_PLAY_SFX(NA_SE_SHIELD_RING, gDefaultSfxSource, 4);
                player->csState++;
            }
            break;

        case 3:
            gFillScreenAlphaStep = 32;
            gCsCamEyeZ -= 1.0f;
            if (gFillScreenAlpha == 0) {
                player->unk_190 = player->unk_194 = 5.0f;
                player->yRot_114 = 90.0f;
                player->baseSpeed = gArwingSpeed;
                player->csState++;
                AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, player->sfxSource, 0);
            }
            break;

        case 4:
            gCsCamEyeZ -= 1.0f;
            gCsCamEyeX -= 1.0f;
            player->rot.x += 0.4f;
            if (gCsFrameCount >= 130) {
                player->state = PLAYERSTATE_ACTIVE;
                player->arwing.drawFace = false;
                player->unk_014 = 0;
                player->unk_018 = 0;
                player->unk_01C = 0;
                gActors[0].state = STATE360_2;
            }
            break;
    }
    gCsCamAtX = player->pos.x;
    gCsCamAtY = player->pos.y;
    gCsCamAtZ = player->pos.z;
    Math_SmoothStepToF(&player->rot.z, 0.0f, 0.1f, 2.0f, 0);
    Math_SmoothStepToF(&player->zRotBank, 0.0f, 0.1f, 3.0f, 0);
    Matrix_RotateY(gCalcMatrix, (player->rot.y + player->yRot_114 + 180.0f) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -(player->rot.x * M_DTOR), MTXF_APPLY);
    src.x = 0.0f;
    src.y = 0.0f;
    src.z = player->baseSpeed;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);
    player->vel.x = dest.x;
    player->vel.z = dest.z;
    player->vel.y = dest.y;
    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;
    player->pos.z += player->vel.z;
    player->trueZpos = player->pos.z;
    player->bankAngle = player->rot.z + player->zRotBank + player->zRotBarrelRoll;
    Math_SmoothStepToF(&player->cam.eye.x, gCsCamEyeX, D_ctx_80177A48[0], 50000.0f, 0);
    Math_SmoothStepToF(&player->cam.eye.y, gCsCamEyeY, D_ctx_80177A48[0], 50000.0f, 0);
    Math_SmoothStepToF(&player->cam.eye.z, gCsCamEyeZ, D_ctx_80177A48[0], 50000.0f, 0);
    Math_SmoothStepToF(&player->cam.at.x, gCsCamAtX, D_ctx_80177A48[0], 50000.0f, 0);
    Math_SmoothStepToF(&player->cam.at.y, gCsCamAtY, D_ctx_80177A48[0], 50000.0f, 0);
    Math_SmoothStepToF(&player->cam.at.z, gCsCamAtZ, D_ctx_80177A48[0], 50000.0f, 0);
}

void AllRange_FortunaIntro(Player* player) {
    Vec3f sp24;

    Math_Vec3fFromAngles(&sp24, 0.0f, player->yRot_114 + 180.0f, 40.0f);
    player->vel.x = sp24.x;
    player->vel.z = sp24.z;
    player->vel.y = sp24.y;
    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;
    player->pos.z += player->vel.z;
    player->trueZpos = player->pos.z;
    player->cam.eye.x = -200.0f;
    player->cam.eye.y = 500.0f;
    player->cam.eye.z = 7000.0f;
    player->cam.at.x = player->pos.x;
    player->cam.at.y = player->pos.y;
    player->cam.at.z = player->pos.z;
}

void AllRange_ClearRadio(void) {
    sStarWolfKillTimer = gRadioState = gActors[1].iwork[1] = gActors[2].iwork[1] = gActors[3].iwork[1] = 0;
}

void ActorAllRange_SetShadowData(Actor* this) {
    s32 i;
    s32 colId;
    Scenery360* scenery360;
    Vec3f temp1;
    f32 temp4;
    f32 temp5;
    Vec3f src;
    Vec3f dest;
    Vec3f spCC;
    Vec3f spC0;
    Vec3f spB4;
    Vec3f spA8;
    f32 spA0[2];
    Vec3f sp94 = { 0.0f, -10.0f, 0.0f };
    s32 pad[2];

    this->fwork[25] = this->fwork[26] = this->fwork[28] = this->fwork[27] = 0.0f;

    if (this->drawShadow && (gLevelMode == LEVELMODE_ALL_RANGE) && (gLevelType == LEVELTYPE_PLANET)) {
        for (i = 0, scenery360 = gScenery360; i < 200; i++, scenery360++) {
            if ((scenery360->obj.status == OBJ_ACTIVE) &&
                ((scenery360->obj.id == OBJ_SCENERY_FO_MOUNTAIN_3) ||
                 (scenery360->obj.id == OBJ_SCENERY_FO_MOUNTAIN_2) ||
                 (scenery360->obj.id == OBJ_SCENERY_FO_MOUNTAIN_1) || (scenery360->obj.id == OBJ_SCENERY_CO_BUMP_1) ||
                 (scenery360->obj.id == OBJ_SCENERY_CO_BUMP_3)) &&
                (fabsf(scenery360->obj.pos.x - this->obj.pos.x) < 2500.0f) &&
                (fabsf(scenery360->obj.pos.z - this->obj.pos.z) < 2500.0f)) {
                temp1.x = scenery360->obj.pos.x;
                temp1.y = scenery360->obj.pos.y;
                temp1.z = scenery360->obj.pos.z;
                temp4 = scenery360->obj.rot.y;

                Matrix_RotateY(gCalcMatrix, -temp4 * M_DTOR, MTXF_NEW);
                src.x = this->obj.pos.x - temp1.x;
                src.y = 0.0f;
                src.z = this->obj.pos.z - temp1.z;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);
                spC0.x = temp1.x;
                spC0.y = temp1.y;

                spCC.x = dest.x + temp1.x;
                spC0.z = temp1.z; // fake? weird ordering
                spCC.y = dest.y + temp1.y;
                spCC.z = dest.z + temp1.z;

                if ((scenery360->obj.id == OBJ_SCENERY_FO_MOUNTAIN_2) ||
                    (scenery360->obj.id == OBJ_SCENERY_FO_MOUNTAIN_3)) {
                    if (scenery360->obj.id == OBJ_SCENERY_FO_MOUNTAIN_2) {
                        colId = COL1_5;
                    } else {
                        colId = COL1_6;
                    }
                    if (func_col1_800998FC(&spCC, &spC0, &sp94, colId, &spA8, spA0) > 0) {
                        this->fwork[25] = spA8.y;
                        this->fwork[26] = spA0[0];
                        this->fwork[28] = spA0[1];
                        this->fwork[27] = DEG_TO_RAD(temp4);
                    }
                } else {
                    colId = COL2_0;
                    if (scenery360->obj.id == OBJ_SCENERY_CO_BUMP_3) {
                        colId = COL2_3;
                    }
                    if (func_col2_800A3690(&spCC, &spC0, colId, &spB4)) {
                        this->fwork[25] = spB4.y;
                        this->fwork[26] = spB4.x;
                        this->fwork[28] = spB4.z;
                        this->fwork[27] = DEG_TO_RAD(temp4);
                    }
                }
            }
        }
    }
}

Vec3f sTeamSpawnPos[4] = {
    { 0.0f, 20000.0f, 0.0f },
    { 0.0f, 700.0f, 6500.0f },
    { -300.0f, 800.0f, 6800.0f },
    { 300.0f, 900.0f, 7200.0f },
};
AllRangeAi sTeamAi[4] = { AI360_FOX, AI360_FALCO, AI360_SLIPPY, AI360_PEPPY };
s32 sTeamSpawnTargets[4] = { -1, AI360_ENEMY, AI360_ENEMY + 1, AI360_ENEMY + 2 };
s32 sTeamSpawnTargetsKA[4] = { -1, AI360_ENEMY + 11, AI360_ENEMY + 13, AI360_ENEMY + 15 };

void ActorAllRange_SpawnTeam(void) {
    ActorAllRange* actor;
    s32 i;
    s32 temp = 4;

    for (i = 0, actor = &gActors[0]; i < temp; i++, actor++) {
        if ((i > 0) && (gTeamShields[i] <= 0)) {
            continue;
        }

        Actor_Initialize(actor);
        actor->obj.status = OBJ_ACTIVE;
        actor->obj.id = OBJ_ACTOR_ALLRANGE;
        Object_SetInfo(&actor->info, actor->obj.id);

        if (i == 0) {
            actor->aiType = AI360_EVENT_HANDLER;
        } else {
            actor->obj.pos.x = sTeamSpawnPos[i].x;
            actor->obj.pos.y = sTeamSpawnPos[i].y;
            actor->obj.pos.z = sTeamSpawnPos[i].z;
            actor->aiType = sTeamAi[i];
            if (gCurrentLevel == LEVEL_KATINA) {
                actor->aiIndex = sTeamSpawnTargetsKA[i];
            } else {
                actor->aiIndex = sTeamSpawnTargets[i];
            }

            actor->state = STATE360_2;
            actor->rot_0F4.y = 180.0f;

            if (actor->aiIndex <= -1) {
                actor->state = STATE360_3;
            }

            actor->health = 50;

            if ((gLevelType == LEVELTYPE_PLANET) || (gCurrentLevel == LEVEL_BOLSE)) {
                actor->drawShadow = true;
            }

            actor->iwork[11] = 1;

            if (actor->aiType <= AI360_PEPPY) {
                AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, actor->sfxSource, 4);
                actor->info.hitbox = SEGMENTED_TO_VIRTUAL(gTeamHitbox);
                actor->info.targetOffset = 0.0f;
                actor->info.bonus = 0;
            } else {
                AUDIO_PLAY_SFX(NA_SE_EN_ENGINE_01, actor->sfxSource, 4);
            }
        }
    }
}

Vec3f sStarWolfSpawnPos[4] = {
    { 9500.0f, 5000.0f, 9500.0f },
    { 10000.0f, 5000.0f, 10000.0f },
    { 10000.0f, 5000.0f, 9500.0f },
    { 9500.0f, 5000.0f, 10000.0f },
};
s32 sStarWolfSpawnTargets[4] = { AI360_FOX, AI360_FALCO, AI360_PEPPY, AI360_SLIPPY };
f32 sStarWolfVE2SpawnRot[4] = { 330.0f, 90.0f, 280.0f, 70.0f };
s32 gAllRangeSpawnEvent = 96 * 30;

void ActorAllRange_SpawnStarWolf(void) {
    ActorAllRange* actor;
    s32 i;

    for (i = 0, actor = &gActors[4]; i < ARRAY_COUNT(sStarWolfSpawnPos); i++, actor++) {
        if (gStarWolfTeamAlive[i] != 0) {
            Actor_Initialize(actor);
            actor->obj.status = OBJ_ACTIVE;
            actor->obj.pos.x = sStarWolfSpawnPos[i].x;
            actor->obj.pos.y = sStarWolfSpawnPos[i].y;
            actor->obj.pos.z = sStarWolfSpawnPos[i].z;
            actor->obj.id = OBJ_ACTOR_ALLRANGE;
            actor->aiType = i + AI360_WOLF;
            actor->aiIndex = sStarWolfSpawnTargets[i];
            gActors[actor->aiIndex].aiIndex = -1;
            actor->health = 100;
            actor->drawShadow = true;
            actor->rot_0F4.y = 225.0f;
            actor->state = STATE360_0;
            actor->timer_0BC = 250;
            actor->rot_0F4.x = -20.0f;
            actor->iwork[11] = 1;

            if (gCurrentLevel == LEVEL_VENOM_2) {
                actor->obj.rot.z = sStarWolfVE2SpawnRot[i];
                actor->itemDrop = DROP_SILVER_STAR;
            }

            Object_SetInfo(&actor->info, actor->obj.id);

            if (gCurrentLevel == LEVEL_VENOM_2) {
                AUDIO_PLAY_SFX(NA_SE_EN_WOLF_ENGINE2, actor->sfxSource, 4);
            } else {
                AUDIO_PLAY_SFX(NA_SE_EN_WOLF_ENGINE, actor->sfxSource, 4);
            }
        }
    }
}

void ActorAllRange_PlayMessage(u16* msg, RadioCharacterId character) {
    if (!gHideRadio && (gActors[0].state == STATE360_2) && (gPlayer[0].state != PLAYERSTATE_STANDBY)) {
        Radio_PlayMessage(msg, character);
    }
}

void ActorAllRange_StarWolfDefeatMesg(u16* msg, RadioCharacterId character) {
    if ((gStarWolfTeamAlive[0] + gStarWolfTeamAlive[1] + gStarWolfTeamAlive[2] + gStarWolfTeamAlive[3]) == 0) {
        gRadioState = 0;
    }
    ActorAllRange_PlayMessage(msg, character);
}

void ActorAllRange_UpdateStarWolfEvents(ActorAllRange* this) {
    ActorAllRange* actor;
    s32 i;

    if (sStarWolfKillTimer != 0) {
        sStarWolfKillTimer--;
        if ((sStarWolfKillTimer == 0) && (gCurrentLevel != LEVEL_BOLSE) &&
            ((gStarWolfTeamAlive[0] + gStarWolfTeamAlive[1] + gStarWolfTeamAlive[2] + gStarWolfTeamAlive[3]) == 1)) {
            Radio_PlayMessage(gMsg_ID_19465, RCID_FOX);
        }
    }
    if ((gAllRangeEventTimer + 100 == (0, gAllRangeSpawnEvent)) && (gCurrentLevel != LEVEL_VENOM_2)) {
        // fake?
        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 30);
        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 30);
    }
    if (gAllRangeEventTimer == gAllRangeSpawnEvent) {
        ActorAllRange_SpawnStarWolf();
        this->state = STATE360_3;
        gPlayer[0].state = PLAYERSTATE_STANDBY;
        if ((gCurrentLevel == LEVEL_VENOM_2) || (gCurrentLevel == LEVEL_BOLSE)) {
            gPlayer[0].camRoll = 20.0f;
        }
        AUDIO_PLAY_BGM(NA_BGM_STARWOLF);
        AllRange_ClearRadio();
        if ((gCurrentLevel == LEVEL_FORTUNA) || (gCurrentLevel == LEVEL_VENOM_2)) {
            gPlayer[0].cam.eye.x = 4500.0f;
        } else if (gCurrentLevel == LEVEL_BOLSE) {
            gPlayer[0].cam.eye.x = 5500.0f;
        }
        gPlayer[0].cam.eye.y = 2500.0f;
        gPlayer[0].cam.eye.z = 5000.0f;
        gPlayer[0].cam.at.x = gActors[AI360_WOLF].obj.pos.x;
        gPlayer[0].cam.at.y = gActors[AI360_WOLF].obj.pos.y;
        gPlayer[0].cam.at.z = gActors[AI360_WOLF].obj.pos.z;
    }
    if ((gAllRangeEventTimer > gAllRangeSpawnEvent) && (gStarWolfMsgTimer == 0)) {
        gAllRangeFrameCount++;
        for (i = AI360_FALCO, actor = &gActors[AI360_FALCO]; i <= AI360_ANDREW; i++, actor++) {
            if ((actor->obj.status == OBJ_ACTIVE) && (actor->state == STATE360_2) && (actor->health < 70) &&
                (actor->timer_0C6 != 0) && (actor->dmgSource == AI360_FOX + 1)) {
                if ((gActors[actor->aiIndex].state == STATE360_3) && (gActors[actor->aiIndex].aiType <= AI360_ANDREW)) {
                    gActors[actor->aiIndex].iwork[2] = AI360_FOX;
                    gActors[actor->aiIndex].state = STATE360_2;
                    gActors[actor->aiIndex].aiIndex = actor->aiType;
                    if (gTeamHelpActor == &gActors[actor->aiIndex]) {
                        gTeamHelpActor = NULL;
                        gTeamHelpTimer = 0;
                    }
                    if (gActors[actor->aiIndex].iwork[3] == 0) {
                        switch (gActors[actor->aiIndex].aiType) {
                            case AI360_FALCO:
                                ActorAllRange_PlayMessage(gMsg_ID_9160, RCID_FALCO);
                                break;
                            case AI360_SLIPPY:
                                ActorAllRange_PlayMessage(gMsg_ID_9170, RCID_SLIPPY);
                                break;
                            case AI360_PEPPY:
                                ActorAllRange_PlayMessage(gMsg_ID_9180, RCID_PEPPY);
                                break;
                        }
                        gActors[actor->aiIndex].iwork[3] = 200;
                    }
                }
                if (actor->aiType == AI360_WOLF) {
                    if (gCurrentLevel != LEVEL_VENOM_2) {
                        actor->state = STATE360_3;
                        actor->counter_04E = 300;
                    }
                } else {
                    actor->state = STATE360_3;
                    actor->aiIndex = -1;
                }
            }
        }
        if (gTeamShields[TEAM_ID_FALCO] <= 0) {
            gActors[AI360_LEON].aiIndex = AI360_FOX;
        }
        if (gTeamShields[TEAM_ID_SLIPPY] <= 0) {
            gActors[AI360_ANDREW].aiIndex = AI360_FOX;
        }
        if (gTeamShields[TEAM_ID_PEPPY] <= 0) {
            gActors[AI360_PIGMA].aiIndex = AI360_FOX;
        }
    }
}

void ActorAllRange_ChooseNewTarget(ActorAllRange* this) {
    ActorAllRange* team;
    ActorAllRange* enemy;
    bool alreadyTaken;
    TeamId teamId;
    AllRangeAi enemyId;

    for (enemyId = AI360_ENEMY, enemy = &gActors[AI360_ENEMY]; enemyId < ARRAY_COUNT(gActors); enemyId++, enemy++) {
        if ((enemy->obj.status == OBJ_ACTIVE) && (enemy->obj.id == OBJ_ACTOR_ALLRANGE) && (enemy->animFrame == 0) &&
            (enemy->aiIndex <= -1)) {
            alreadyTaken = false;
            for (teamId = AI360_FALCO, team = &gActors[AI360_FALCO]; teamId <= AI360_PEPPY; teamId++, team++) {
                if ((teamId != this->index) && (enemyId == team->aiIndex)) {
                    alreadyTaken = true;
                }
            }
            if (!alreadyTaken) {
                this->aiIndex = enemyId;
                this->state = STATE360_2;
                this->iwork[2] = AI360_FOX;
                break;
            }
        }
    }
}

void ActorAllRange_UpdateEnemyEvents(Actor* this) {
    ActorAllRange* enemy;
    s32 i;

    for (i = 0, enemy = &gActors[AI360_ENEMY]; i < 50; i++, enemy++) {
        if ((enemy->obj.status == OBJ_DYING) && (enemy->aiIndex >= AI360_FALCO) && (enemy->aiIndex <= AI360_PEPPY)) {
            ActorAllRange* enemy2;
            s32 j;

#ifdef AVOID_UB
            for (j = 0, enemy2 = &gActors[AI360_ENEMY]; j < 50; j++, enemy2++) {
#else
            for (j = 0, enemy2 = &gActors[AI360_ENEMY]; j <= 50; j++, enemy2++) { // bug? should be <
#endif
                if ((enemy2->obj.status == OBJ_ACTIVE) && (enemy2->state == STATE360_2) &&
                    (enemy2->aiIndex == enemy->aiIndex)) {
                    return;
                }
            }
            if (gTeamShields[enemy->aiIndex] > 0) {
                ActorAllRange_ChooseNewTarget(&gActors[enemy->aiIndex]);
                if ((enemy->iwork[5] != 0) && (enemy->dmgSource == AI360_FOX + 1) &&
                    (gActors[enemy->aiIndex].iwork[3] == 0)) {
                    if (gTeamHelpActor == &gActors[enemy->aiIndex]) {
                        gTeamHelpActor = NULL;
                        gTeamHelpTimer = 0;
                    }
                    switch (gActors[enemy->aiIndex].aiType) {
                        case AI360_FALCO:
                            ActorAllRange_PlayMessage(gMsg_ID_9160, RCID_FALCO);
                            break;
                        case AI360_SLIPPY:
                            ActorAllRange_PlayMessage(gMsg_ID_9170, RCID_SLIPPY);
                            break;
                        case AI360_PEPPY:
                            ActorAllRange_PlayMessage(gMsg_ID_9180, RCID_PEPPY);
                            break;
                    }
                    gActors[enemy->aiIndex].iwork[3] = 200;
                    gActors[enemy->aiIndex].timer_0C4 = 600;
                }
            }
        }
    }
}

bool AllRange_SupplyEvent(void) {
    switch (gCurrentLevel) {
        case LEVEL_FORTUNA:
            return gAllRangeEventTimer == gAllRangeSpawnEvent + 2400;
        case LEVEL_BOLSE:
            return gBosses[2].swork[36] == 4;
        case LEVEL_KATINA:
            return gBosses[1].swork[15] == 2;
    }
    return false;
}

void ActorAllRange_SpawnSupplies(Actor* this) {
    ActorSupplies* supplies;
    s32 i;

    if ((gCallTimer != 0) && (gControllerPress[gMainController].button & R_CBUTTONS)) {
        Audio_SetUnkVoiceParam(0);
        gCallVoiceParam = 0;
        gCallTimer = 0;
        Radio_PlayMessage(gMsg_ID_20230, RCID_ROB64);
        gAllRangeSupplyTimer = 160;
    }

    if (gAllRangeSupplyTimer != 0) {
        gAllRangeSupplyTimer--;
        if (gAllRangeSupplyTimer == 0) {
            for (i = 20, supplies = &gActors[20]; i < 60; i++, supplies++) {
                if (supplies->obj.status == OBJ_FREE) {
                    Actor_Initialize(supplies);
                    supplies->obj.status = OBJ_INIT;
                    supplies->obj.id = OBJ_ACTOR_SUPPLIES;
                    if (gCurrentLevel == LEVEL_SECTOR_Z) {
                        supplies->obj.pos.x = 200.0f;
                        supplies->obj.pos.y = -500.0f;
                        supplies->obj.pos.z = 0.0f;
                        AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, supplies->sfxSource, 0);
                        supplies->timer_0C2 = 50;
                    } else {
                        supplies->obj.pos.x = 0.0f;
                        supplies->obj.pos.y = 3000.0f;
                        supplies->obj.pos.z = 5000.0f;
                        supplies->timer_0C2 = 50;
                    }
                    Object_SetInfo(&supplies->info, supplies->obj.id);
                    break;
                }
            }
        }
    }

    if ((gPlayer[0].state == PLAYERSTATE_ACTIVE) && !gAllRangeSuppliesSent) {
        if (gAllRangeWingRepairTimer != 0) {
            gAllRangeWingRepairTimer--;
        }
        if ((gPlayer[0].shields < 64) || AllRange_SupplyEvent() || (gAllRangeWingRepairTimer == 1)) {
            gCallTimer = 60;
            gAllRangeSuppliesSent = true;
        }
    }
}

void ActorAllRange_UpdateEvents(Actor* this) {
    if ((gPlayer[0].state == PLAYERSTATE_DOWN) || (gPlayer[0].state == PLAYERSTATE_NEXT)) {
        Object_Kill(&this->obj, this->sfxSource);
        return;
    }

    gAllRangeEventTimer++;

    switch (gCurrentLevel) {
        case LEVEL_FORTUNA:
            Fortuna_UpdateEvents(this);
            break;
        case LEVEL_KATINA:
            Katina_UpdateEvents(this);
            break;
        case LEVEL_BOLSE:
            Bolse_UpdateEventHandler(this);
            break;
        case LEVEL_SECTOR_Z:
            SectorZ_UpdateEvents(this);
            break;
        case LEVEL_VENOM_2:
            Venom2_UpdateEvents(this);
            break;
    }
    ActorAllRange_SpawnSupplies(this);
}

/**
 *  Checks whether an actor is close to Scenery objects or Bosses in Space Levels.
 *  Return values:
 *  1: Object nearby is found below the actor
 * -1: Object nearby is found above the actor
 *  0: No objects found
 */
s32 ActorAllRange_CheckObjectNearbySpace(Actor* this) {
    Boss* boss;
    f32 temp_ft4;
    f32 temp_ft5;
    s32 i;
    f32 sinY;
    f32 cosY;

    if (gLevelMode == LEVELMODE_ON_RAILS) {
        return 0;
    }

    sinY = SIN_DEG(this->obj.rot.y);
    cosY = COS_DEG(this->obj.rot.y);

    temp_ft4 = this->fwork[9] * 10.0f + (sinY * 650.0f);
    temp_ft5 = this->fwork[9] * 10.0f + (cosY * 650.0f);

    for (i = 0; i < 200; i++) {
        if ((gScenery360[i].obj.status == OBJ_ACTIVE) &&
            (fabsf(gScenery360[i].obj.pos.x - (this->obj.pos.x + temp_ft4)) < 1000.0f) &&
            (fabsf(gScenery360[i].obj.pos.z - (this->obj.pos.z + temp_ft5)) < 1000.0f)) {
            if (fabsf(gScenery360[i].obj.pos.y - this->obj.pos.y) < 1000.0f) {
                if (gScenery360[i].obj.pos.y < this->obj.pos.y) {
                    return 1;
                } else {
                    return -1;
                }
            }
        }
    }

    boss = &gBosses[0];
    // Check if the actor is close to the Great Fox in Sector Z.
    if ((gCurrentLevel == LEVEL_SECTOR_Z) && (fabsf(boss->obj.pos.x - (this->obj.pos.x + temp_ft4)) < 2000.0f) &&
        (fabsf(boss->obj.pos.z - (this->obj.pos.z + temp_ft5)) < 2000.0f)) {
        if (fabsf(boss->obj.pos.y - this->obj.pos.y) < 1500.0f) {
            if (boss->obj.pos.y < this->obj.pos.y) {
                return 1;
            } else {
                return -1;
            }
        }
    }
    return 0;
}

/**
 *  Checks whether an actor is close to Scenery objects or specific Bosses.
 *  Return values:
 *  1: Object nearby is found below the actor
 * -1: Object nearby is found above the actor
 *  0: No objects found
 */
s32 ActorAllRange_CheckObjectNearby(ActorAllRange* this) {
    Scenery360* scenery360;
    s32 i;
    f32 distThreshold;
    f32 sinRotY;
    f32 cosRotY;
    f32 xOffset;
    f32 zOffset;
    f32 yDistThreshold;
    Boss* boss = &gBosses[0];
    s32 pad[4];

    if (gPlayer[0].state == PLAYERSTATE_LEVEL_INTRO) {
        return 0;
    }

    if ((gLevelType == LEVELTYPE_SPACE) && (gCurrentLevel != LEVEL_BOLSE)) {
        return ActorAllRange_CheckObjectNearbySpace(this);
    }

    sinRotY = SIN_DEG(this->obj.rot.y);
    cosRotY = COS_DEG(this->obj.rot.y);

    xOffset = this->fwork[9] * 10.0f + (sinRotY * 650.0f);
    zOffset = this->fwork[9] * 10.0f + (cosRotY * 650.0f);

    if (gLevelMode == LEVELMODE_ALL_RANGE) {
        for (i = 0, scenery360 = gScenery360; i < 200; i++, scenery360++) {
            if ((scenery360->obj.status == OBJ_ACTIVE) &&
                (fabsf(scenery360->obj.pos.x - (this->obj.pos.x + xOffset)) < 1200.0f) &&
                (fabsf(scenery360->obj.pos.z - (this->obj.pos.z + zOffset)) < 1200.0f) && (this->obj.pos.y < 650.0f)) {
                return 1;
            }
        }
    }

    distThreshold = 1200.0f;
    yDistThreshold = 650.0f;

    if (this->aiType <= AI360_ANDREW) {
        yDistThreshold = 720.0f;
    }

    if (boss->obj.id == OBJ_BOSS_CO_CARRIER) {
        yDistThreshold = 350.0f;
    } else if (boss->obj.id == OBJ_BOSS_BO_BASE) {
        distThreshold = 2000.0f;
        yDistThreshold = 750.0f;
    } else if (boss->obj.id == OBJ_BOSS_KA_FLBASE) {
        distThreshold = 1500.0f;
        yDistThreshold = 700.0f;
    }

    if ((fabsf(boss->obj.pos.x - (this->obj.pos.x + xOffset)) < distThreshold) &&
        (fabsf(boss->obj.pos.z - (this->obj.pos.z + zOffset)) < distThreshold) &&
        (fabsf(boss->obj.pos.y - this->obj.pos.y) < yDistThreshold)) {
        return 1;
    } else {
        return 0;
    }
}

void ActorAllRange_ApplyDamage(ActorAllRange* this) {
    bool var_a1;
    Vec3f src;
    Vec3f dest;

    if (this->dmgType != DMG_NONE) {
        if (this->aiType == AI360_GREAT_FOX) {
            this->dmgType = DMG_NONE;
        }
        if ((this->dmgType >= DMG_EXPLOSION) && (this->aiType >= AI360_WOLF) && (this->aiType <= AI360_ANDREW)) {
            this->damage = 10;
            this->timer_0C2 = 10;
        }
        if (((this->aiType <= AI360_PEPPY) || (this->aiType == AI360_BILL) || (this->aiType == AI360_KATT)) &&
            (this->dmgType == DMG_EXPLOSION)) {
            this->dmgType = DMG_NONE;
        }

        if ((this->dmgType == DMG_EXPLOSION) && (this->fwork[22] > 0.0f)) {
            this->dmgType = DMG_NONE;
        }

        if (this->fwork[23] > 1.0f) {
            this->dmgType = DMG_NONE;
        }

        if (this->dmgType != DMG_NONE) {
            var_a1 = false;
            if ((this->animFrame == 3) ||
                ((gCurrentLevel == LEVEL_BOLSE) && (gBosses[1].obj.status != OBJ_FREE) &&
                 (this->aiType >= AI360_WOLF)) ||
                ((gCurrentLevel == LEVEL_VENOM_2) && (this->aiType >= AI360_WOLF) && (this->aiType < AI360_ENEMY) &&
                 (this->dmgType == DMG_EXPLOSION))) {
                this->damage = DMG_NONE;
                var_a1 = true;
                if (gCurrentLevel == LEVEL_BOLSE) {
                    this->dmgSource = 0;
                }
            }
            if (this->aiType >= AI360_WOLF) {
                if (!((this->dmgType == DMG_COLLISION) && (this->aiType == AI360_WOLF)) &&
                    !((this->aiType == AI360_MISSILE) && (this->dmgType == DMG_EXPLOSION))) {
                    this->health -= this->damage;
                }
            } else if ((this->aiType <= AI360_PEPPY) && (this->state != STATE360_6)) {
                if (this->aiType == AI360_FALCO) {
                    gTeamDamage[this->aiType] = this->damage;
                } else {
                    gTeamDamage[this->aiType] = this->damage * 2;
                }
            }

            if (this->health <= 0) {
                this->health = 0;
                if (this->aiType == AI360_MISSILE) {
                    SectorZ_MissileExplode(this, true);
                    if (this->dmgSource == AI360_FOX + 1) {
                        if (gActors[AI360_KATT].obj.status == OBJ_ACTIVE) {
                            Radio_PlayMessage(gMsg_ID_16140, RCID_KATT);
                        }
                        BonusText_Display(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 10);
                        gHitCount += 11;
                        D_ctx_80177850 = 15;
                    } else {
                        switch (this->dmgSource) {
                            case AI360_FALCO + NPC_SHOT_ID + 1:
                                Radio_PlayMessage(gMsg_ID_16170, RCID_FALCO);
                                break;
                            case AI360_SLIPPY + NPC_SHOT_ID + 1:
                                Radio_PlayMessage(gMsg_ID_16180, RCID_SLIPPY);
                                break;
                            case AI360_PEPPY + NPC_SHOT_ID + 1:
                                Radio_PlayMessage(gMsg_ID_16175, RCID_PEPPY);
                                break;
                            case AI360_KATT + NPC_SHOT_ID + 1:
                                Radio_PlayMessage(gMsg_ID_16185, RCID_KATT);
                                break;
                        }
                    }
                    return;
                }
                this->timer_0C6 = 50;
                this->iwork[8] = 20;
                this->obj.status = OBJ_DYING;
                this->fwork[23] = 0.0f;

                func_effect_8007D2C8(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 4.0f);
                AUDIO_PLAY_SFX(NA_SE_EN_CRASH_DOWN, this->sfxSource, 4);

                this->timer_0C2 = 10;
                this->timer_0BE = 0;
                this->work_04C = RAND_INT(2.9f);

                switch (RAND_INT(4.0f)) {
                    case 0:
                        this->timer_0BC = 0;
                        break;
                    case 1:
                        this->timer_0BC = 50;
                        break;
                    case 2:
                        this->timer_0BC = 200;
                        break;
                    case 3:
                        this->timer_0BC = 300;
                        break;
                }

                if (gCurrentLevel == LEVEL_VENOM_ANDROSS) {
                    this->timer_0BC = 70;
                }

                if ((gLevelType == LEVELTYPE_SPACE) && (gCurrentLevel != LEVEL_BOLSE)) {
                    if (Rand_ZeroOne() < 0.5f) {
                        this->timer_0BC = 10;
                    } else {
                        this->timer_0BC = RAND_INT(50.0f);
                    }
                }

                if ((this->aiType >= AI360_WOLF) && (this->aiType <= AI360_ANDREW)) {
                    this->timer_0BC = RAND_INT(40.0f) + 60.0f;
                }

                if (this->damage >= 20) {
                    this->timer_0BC = 0;
                }

                if ((gCurrentLevel == LEVEL_KATINA) && (this->animFrame == 1) && (this->dmgSource == AI360_FOX + 1)) {
                    if (gKaAllyKillCount < 2) {
                        ActorAllRange_PlayMessage(gMsg_ID_18018, RCID_BILL);
                    }
                    gKaAllyKillCount++;
                }
                switch (this->aiType) {
                    case AI360_WOLF:
                        gStarWolfTeamAlive[0] = 0;
                        if (gCurrentLevel == LEVEL_VENOM_2) {
                            ActorAllRange_StarWolfDefeatMesg(gMsg_ID_19458, RCID_WOLF);
                        } else {
                            ActorAllRange_StarWolfDefeatMesg(gMsg_ID_9365, RCID_WOLF);
                        }
                        break;

                    case AI360_LEON:
                        gStarWolfTeamAlive[1] = 0;
                        if (gCurrentLevel == LEVEL_VENOM_2) {
                            ActorAllRange_StarWolfDefeatMesg(gMsg_ID_19459, RCID_LEON);
                        } else {
                            ActorAllRange_StarWolfDefeatMesg(gMsg_ID_9366, RCID_LEON);
                        }
                        break;

                    case AI360_PIGMA:
                        gStarWolfTeamAlive[2] = 0;
                        if (gCurrentLevel == LEVEL_VENOM_2) {
                            ActorAllRange_StarWolfDefeatMesg(gMsg_ID_19460, RCID_PIGMA);
                        } else {
                            ActorAllRange_StarWolfDefeatMesg(gMsg_ID_9367, RCID_PIGMA);
                        }
                        break;

                    case AI360_ANDREW:
                        gStarWolfTeamAlive[3] = 0;
                        if (gCurrentLevel == LEVEL_VENOM_2) {
                            ActorAllRange_StarWolfDefeatMesg(gMsg_ID_19461, RCID_ANDREW);
                        } else {
                            ActorAllRange_StarWolfDefeatMesg(gMsg_ID_9368, RCID_ANDREW);
                        }
                        break;
                }

                if ((this->aiType >= AI360_WOLF) && (this->aiType <= AI360_ANDREW)) {
                    sStarWolfKillTimer = 150;
                }

                switch (this->dmgSource) {
                    case AI360_FOX + 1:
                        if (this->aiType >= AI360_ENEMY) {
                            switch (this->iwork[2]) {
                                case AI360_FALCO:
                                    ActorAllRange_PlayMessage(gMsg_ID_20170, RCID_FALCO);
                                    break;
                                case AI360_SLIPPY:
                                    ActorAllRange_PlayMessage(gMsg_ID_20150, RCID_SLIPPY);
                                    break;
                                case AI360_PEPPY:
                                    ActorAllRange_PlayMessage(gMsg_ID_20160, RCID_PEPPY);
                                    break;
                            }
                        }
                        break;
                    case AI360_FALCO + NPC_SHOT_ID + 1:
                    case AI360_SLIPPY + NPC_SHOT_ID + 1:
                    case AI360_PEPPY + NPC_SHOT_ID + 1:
                        if ((this->aiType >= AI360_WOLF) && (this->aiType <= AI360_ANDREW)) {
                            if ((gStarWolfTeamAlive[0] + gStarWolfTeamAlive[1] + gStarWolfTeamAlive[2] +
                                 gStarWolfTeamAlive[3]) == 0) {
                                switch (this->dmgSource) {
                                    case AI360_FALCO + NPC_SHOT_ID + 1:
                                        Radio_PlayMessage(gMsg_ID_9438, RCID_FALCO);
                                        break;
                                    case AI360_SLIPPY + NPC_SHOT_ID + 1:
                                        Radio_PlayMessage(gMsg_ID_9436, RCID_SLIPPY);
                                        break;
                                    case AI360_PEPPY + NPC_SHOT_ID + 1:
                                        Radio_PlayMessage(gMsg_ID_9437, RCID_PEPPY);
                                        break;
                                }
                            } else {
                                gActors[this->dmgSource - NPC_SHOT_ID - 1].iwork[1] = 80;
                            }
                        } else {
                            gActors[this->dmgSource - NPC_SHOT_ID - 1].iwork[1] = 80;
                        }
                        break;
                }
            } else {
                if (var_a1) {
                    AUDIO_PLAY_SFX(NA_SE_EN_BARRIER_REFLECT, this->sfxSource, 4);
                    this->iwork[7] = 3;
                    this->iwork[18] = 5;
                    this->iwork[8] = 15;
                    if (Rand_ZeroOne() < 0.5f) {
                        this->fwork[8] = 0.0f;
                        this->fwork[7] = 360.0f;
                    } else {
                        this->fwork[7] = 0.0f;
                        this->fwork[8] = 359.999f;
                    }
                } else {
                    this->timer_0C6 = 20;
                    this->iwork[8] = 20;
                }

                if (this->aiType == AI360_MISSILE) {
                    AUDIO_PLAY_SFX(NA_SE_OB_DAMAGE_M, this->sfxSource, 4);
                } else if (this->iwork[7] == 0) {
                    AUDIO_PLAY_SFX(NA_SE_EN_DAMAGE_S, this->sfxSource, 4);
                }

                func_effect_8007D10C(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 1.5f);

                if (this->aiType < AI360_GREAT_FOX) {
                    Matrix_RotateY(gCalcMatrix, this->rot_0F4.y * M_DTOR, MTXF_NEW);
                    src.x = 30.0f;
                    if (Rand_ZeroOne() < 0.5f) {
                        src.x = -30.0f;
                    }
                    src.y = RAND_FLOAT_CENTERED(30.0f);
                    src.z = 0.0f;
                    if (this->iwork[7] != 0) {
                        src.x *= 1.5f;
                        src.y = 30.0f;

                        if ((this->obj.pos.y > 100.0f) && (Rand_ZeroOne() < 0.5f)) {
                            src.y = -30.0f;
                        }
                    }
                    Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);
                    this->fwork[13] = dest.x;
                    this->fwork[14] = dest.y;
                    this->fwork[12] = dest.z;
                }

                if ((gRadioState == 0) && (gActors[0].obj.status == OBJ_ACTIVE)) {
                    if (this->dmgType == DMG_COLLISION) {
                        switch (this->aiType) {
                            case AI360_FALCO:
                                ActorAllRange_PlayMessage(gMsg_ID_20210, RCID_FALCO);
                                break;
                            case AI360_PEPPY:
                                ActorAllRange_PlayMessage(gMsg_ID_20200, RCID_PEPPY);
                                break;
                            case AI360_SLIPPY:
                                ActorAllRange_PlayMessage(gMsg_ID_20190, RCID_SLIPPY);
                                break;
                            case AI360_KATT:
                                ActorAllRange_PlayMessage(gMsg_ID_20084, RCID_KATT);
                                break;
                        }
                    } else if (this->dmgSource <= AI360_PEPPY + 101) {
                        if (this->aiType >= AI360_WOLF) {
                            if (this->dmgSource == AI360_FOX + 1) {
                                if ((gCurrentLevel == LEVEL_KATINA) && (this->animFrame == 1) && !gKaKilledAlly) {
                                    gKaKilledAlly = true;
                                    Radio_PlayMessage(gMsg_ID_18015, RCID_BILL);
                                } else if (this->aiType == AI360_KATT) {
                                    ActorAllRange_PlayMessage(gMsg_ID_20084, RCID_KATT);
                                } else if (this->aiType == AI360_BILL) {
                                    ActorAllRange_PlayMessage(gMsg_ID_20085, RCID_BILL);
                                } else if (gCurrentLevel == LEVEL_VENOM_2) {
                                    switch (this->aiType) {
                                        case AI360_WOLF:
                                            ActorAllRange_PlayMessage(gMsg_ID_19454, RCID_WOLF);
                                            break;
                                        case AI360_LEON:
                                            ActorAllRange_PlayMessage(gMsg_ID_19455, RCID_LEON);
                                            break;
                                        case AI360_PIGMA:
                                            ActorAllRange_PlayMessage(gMsg_ID_19456, RCID_PIGMA);
                                            break;
                                        case AI360_ANDREW:
                                            ActorAllRange_PlayMessage(gMsg_ID_19457, RCID_ANDREW);
                                            break;
                                    }
                                }
                            }
                        } else if (this->dmgSource == AI360_FOX + 1) {
                            switch (this->aiType) {
                                case AI360_FALCO:
                                    ActorAllRange_PlayMessage(gMsg_ID_20060, RCID_FALCO);
                                    break;
                                case AI360_PEPPY:
                                    ActorAllRange_PlayMessage(gMsg_ID_20070, RCID_PEPPY);
                                    break;
                                case AI360_SLIPPY:
                                    ActorAllRange_PlayMessage(gMsg_ID_20080, RCID_SLIPPY);
                                    break;
                            }
                        }
                    } else if ((this->aiType <= AI360_PEPPY) && (this->iwork[6] != 0) &&
                               (this->iwork[2] != AI360_FOX)) {
                        switch (this->aiType) {
                            case AI360_FALCO:
                                if (gTeamShields[TEAM_ID_FALCO] >= 90) {
                                    ActorAllRange_PlayMessage(gMsg_ID_9130, RCID_FALCO);
                                } else {
                                    Radio_PlayMessage(gMsg_ID_9151, RCID_FALCO);
                                }
                                if ((gTeamHelpActor == NULL) || (gTeamShields[this->aiType] <= 50)) {
                                    gTeamHelpActor = this;
                                    gTeamHelpTimer = 320;
                                }
                                break;

                            case AI360_SLIPPY:
                                if (gTeamShields[TEAM_ID_SLIPPY] >= 90) {
                                    ActorAllRange_PlayMessage(gMsg_ID_9140, RCID_SLIPPY);
                                } else {
                                    Radio_PlayMessage(gMsg_ID_9152, RCID_SLIPPY);
                                }
                                if ((gTeamHelpActor == NULL) || (gTeamShields[this->aiType] <= 50)) {
                                    gTeamHelpActor = this;
                                    gTeamHelpTimer = 320;
                                }
                                break;

                            case AI360_PEPPY:
                                if (gTeamShields[TEAM_ID_PEPPY] >= 90) {
                                    ActorAllRange_PlayMessage(gMsg_ID_9150, RCID_PEPPY);
                                } else {
                                    Radio_PlayMessage(gMsg_ID_9153, RCID_PEPPY);
                                }
                                if ((gTeamHelpActor == NULL) || (gTeamShields[this->aiType] <= 50)) {
                                    gTeamHelpActor = this;
                                    gTeamHelpTimer = 320;
                                }
                                break;
                        }
                    }
                }
            }
            this->dmgType = DMG_NONE;
        }
    }
}

void ActorAllRange_CheckPlayerNearby(ActorAllRange* this) {
    if ((gPlayer[0].state == PLAYERSTATE_ACTIVE) && (this->iwork[24] != 0) &&
        (fabsf(this->obj.pos.x - gPlayer[0].pos.x) < 1000.0f) &&
        (fabsf(this->obj.pos.y - gPlayer[0].pos.y) < 1000.0f) &&
        (fabsf(this->obj.pos.z - gPlayer[0].trueZpos) < 1000.0f)) {
        this->iwork[10]++;
    } else {
        this->iwork[10] = 0;
    }
}

bool func_360_80031900(ActorAllRange* this) {
    Vec3f src;
    Vec3f dest;

    Matrix_RotateY(gCalcMatrix, -this->obj.rot.y * M_DTOR, MTXF_NEW);

    src.x = this->fwork[4] - this->obj.pos.x;
    src.y = 0.0f;
    src.z = this->fwork[6] - this->obj.pos.z;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

    if (dest.z > 0.0f) {
        return true;
    } else {
        return false;
    }
}

Vec3f sSectorZRetreatPath[6] = {
    { 8000.0f, 500.0f, 0.0f }, { 5000.0f, 400.0f, 0.0f }, { 2000.0f, 300.0f, 0.0f },
    { -500.0f, 250.0f, 0.0f }, { 0.0f, 250.0f, 0.0f },    { 0.0f, 250.0f, 0.0f },
};

void ActorAllRange_Update(ActorAllRange* this) {
    u8 sp10F;
    s32 objectNearby;
    s32 sp104;
    s32 temp_v0_27;
    RadarMark* radarMark;
    f32 spF8;
    f32 spF4;
    f32 spF0;
    f32 spEC;
    f32 spE8;
    f32 spE4;
    f32 spE0;
    f32 spDC;
    f32 spD8;
    f32 spD4;
    f32 spD0;
    f32 spCC;
    f32 spC8;
    f32 spC4;
    f32 spC0;
    f32 spBC;
    f32 spB8;
    f32 spB4;
    Vec3f spA8;
    Vec3f sp9C;
    Vec3f sp90;
    Vec3f sp84 = { 60.0f, 0.0f, -170.0f };
    Vec3f sp78 = { -60.0f, 0.0f, -170.0f };
    s32 pad[3];

    if (this->aiType == AI360_EVENT_HANDLER) {
        this->timer_0C2 = 10;
        this->info.targetOffset = 0.0f;
        ActorAllRange_UpdateEvents(this);
        return;
    }
    if ((this->iwork[17] != 0) && (this->iwork[16] == STATE360_0) && (this->aiType >= AI360_WOLF)) {
        switch (RAND_INT(3.9f)) {
            case 0:
            case 1:
                if (gCurrentLevel == LEVEL_VENOM_2) {
                    this->iwork[16] = STATE360_10;
                }
                break;

            case 2:
                this->iwork[16] = STATE360_8;
                break;

            case 3:
                this->iwork[16] = STATE360_7;
                break;
        }

        this->iwork[17] = 0;
        if (this->iwork[18] != 0) {
            this->iwork[18]--;
            this->iwork[16] = STATE360_0;
        }
    }

    if ((this->lockOnTimers[TEAM_ID_FOX] != 0) && (gCurrentLevel != LEVEL_VENOM_2) && (this->aiType < AI360_ENEMY) &&
        (this->lockOnTimers[TEAM_ID_FOX] < 5) && ((gGameFrameCount % 32) == 0)) {
        this->iwork[16] = STATE360_10;
    }

    if ((this->iwork[16] != STATE360_0) && (this->state < STATE360_7)) {
        this->state = this->iwork[16];
        switch (this->state) {
            case STATE360_7:
            case STATE360_8:
                if (this->rot_0F4.x > 180.0f) {
                    this->rot_0F4.x -= 360.0f;
                }
                this->work_046 = 0;
                break;
            case STATE360_9:
                this->timer_0BC = RAND_INT(20.0f) + 30;
                if (Rand_ZeroOne() < 0.5f) {
                    this->fwork[19] = this->obj.rot.y + 50.0f;
                } else {
                    this->fwork[19] = this->obj.rot.y - 50.0f;
                }
                if (this->fwork[19] >= 360.0f) {
                    this->fwork[19] -= 360.0f;
                }
                if (this->fwork[19] < 0.0f) {
                    this->fwork[19] += 360.0f;
                }
                break;
            case STATE360_10:
                this->timer_0BC = 35;
                if (Rand_ZeroOne() < 0.5f) {
                    this->fwork[7] = 360.0f;
                    this->fwork[8] = 0.0f;
                    this->iwork[15] = 1;
                } else {
                    this->fwork[7] = 0.0f;
                    this->fwork[8] = 359.999f;
                    this->iwork[15] = -1;
                }
                this->iwork[19] = 1;
                break;
        }
    }
    this->iwork[16] = STATE360_0;
    spCC = spC8 = spC4 = 0.0f;

    if (this->iwork[7] != 0) {
        this->iwork[7]--;
        this->fwork[22] = 1.0f;
    }

    if (this->iwork[3] != 0) {
        this->iwork[3]--;
    }

    Math_SmoothStepToF(&this->fwork[10], 0.0f, 0.1f, 0.2f, 0.00001f);
    Math_SmoothStepToF(&this->fwork[9], this->fwork[10], 0.1f, 2.0f, 0.00001f);

    if (this->fwork[10] > 0.1f) {
        this->iwork[11] = 2;
    } else {
        this->iwork[11] = 1;
    }

    if (this->aiType < AI360_ENEMY) {
        ActorAllRange_CheckPlayerNearby(this);
        if (this->iwork[10] == 200) {
            switch (this->aiType) {
                case AI360_WOLF:
                case AI360_LEON:
                case AI360_PIGMA:
                case AI360_ANDREW:
                case AI360_KATT:
                    break;

                case AI360_FALCO:
                    if (gPlayer[0].shields < (Play_GetMaxShields() / 2)) {
                        Radio_PlayMessage(gMsg_ID_20298, RCID_FALCO);
                    } else if (Rand_ZeroOne() < 0.5f) {
                        Radio_PlayMessage(gMsg_ID_20280, RCID_FALCO);
                    } else {
                        Radio_PlayMessage(gMsg_ID_20301, RCID_FALCO);
                    }
                    break;

                case AI360_SLIPPY:
                    if (gPlayer[0].shields < (Play_GetMaxShields() / 2)) {
                        Radio_PlayMessage(gMsg_ID_20297, RCID_SLIPPY);
                    } else if (Rand_ZeroOne() < 0.5f) {
                        Radio_PlayMessage(gMsg_ID_20282, RCID_SLIPPY);
                    } else {
                        Radio_PlayMessage(gMsg_ID_20300, RCID_SLIPPY);
                    }
                    break;

                case AI360_PEPPY:
                    if (gPlayer[0].shields < (Play_GetMaxShields() / 2)) {
                        Radio_PlayMessage(gMsg_ID_20296, RCID_PEPPY);
                    } else if (Rand_ZeroOne() < 0.5f) {
                        Radio_PlayMessage(gMsg_ID_20281, RCID_PEPPY);
                    } else {
                        Radio_PlayMessage(gMsg_ID_20299, RCID_PEPPY);
                    }
                    break;

                case AI360_BILL:
                    Radio_PlayMessage(gMsg_ID_18120, RCID_BILL);
                    break;
            }
        }
    }

    sp104 = 0;
    this->iwork[5] = 0;
    if ((this->aiType >= AI360_FALCO) && (this->aiType <= AI360_PEPPY) && (gTeamShields[this->aiType] <= 0) &&
        (this->state != STATE360_6)) {
        this->state = STATE360_6;
        if (this->timer_0C2 < 100) {
            gTeamShields[this->aiType] = 1;
            switch (this->aiType) {
                case AI360_FALCO:
                    Radio_PlayMessage(gMsg_ID_20220, RCID_FALCO);
                    break;
                case AI360_SLIPPY:
                    Radio_PlayMessage(gMsg_ID_20222, RCID_SLIPPY);
                    break;
                case AI360_PEPPY:
                    Radio_PlayMessage(gMsg_ID_20221, RCID_PEPPY);
                    break;
            }
            this->fwork[29] = 5.0f;
            this->fwork[7] = 360.0f;
            this->fwork[8] = 0.0f;
            AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, this->sfxSource, 0);
            this->work_046 = 0;
        }
        gTeamShields[this->aiType] = -1;
        gTeamDamage[this->aiType] = 0;
        this->iwork[1] = 0;
        this->timer_0C2 = 10000;
    }

    switch (this->state) {
        case STATE360_6:
            this->timer_0C2 = 10000;
            this->iwork[11] = 2;
            this->fwork[1] = 45.0f;
            this->fwork[3] = 2.0f;
            gTeamShields[this->aiType] = -1;
            gTeamDamage[this->aiType] = 0;
            if (gCurrentLevel == LEVEL_SECTOR_Z) {
                this->fwork[4] = sSectorZRetreatPath[this->work_046].x;
                this->fwork[5] = sSectorZRetreatPath[this->work_046].y;
                this->fwork[6] = sSectorZRetreatPath[this->work_046].z;
                if ((fabsf(this->obj.pos.x - sSectorZRetreatPath[this->work_046].x) < 800.0f) &&
                    (fabsf(this->obj.pos.z - sSectorZRetreatPath[this->work_046].z) < 800.0f)) {
                    this->work_046++;
                    if (this->work_046 >= 4) {
                        Object_Kill(&this->obj, this->sfxSource);
                    }
                }
            } else {
                this->fwork[5] = 20000.0f;
                if (this->obj.pos.y > 3000.0f) {
                    Object_Kill(&this->obj, this->sfxSource);
                }
            }
            sp104 = 2;
            break;
        case STATE360_5:
            SectorZ_Missile_Update(this);
            sp104 = 1;
            break;

        case STATE360_0:
            if (gPlayer[0].state != PLAYERSTATE_START_360) {
                this->fwork[0] = this->fwork[1] = 40.0f;

                if (gActors[0].state == STATE360_5) {
                    Math_SmoothStepToF(&this->rot_0F4.x, 30.0f, 0.1f, 0.5f, 0.0f);
                    this->fwork[1] = 200.0f;
                }

                if (this->timer_0BC == 0) {
                    if (this->aiType == AI360_WOLF) {
                        this->state = STATE360_3;
                        if (gCurrentLevel == LEVEL_VENOM_2) {
                            this->counter_04E = 200;
                        } else {
                            this->counter_04E = 200;
                        }
                    } else {
                        this->state = STATE360_2;
                        if (this->aiType == AI360_KATT) {
                            this->fwork[7] = 360.0f;
                            this->fwork[8] = 0.0f;
                        }
                    }
                }
                Math_SmoothStepToAngle(&this->obj.rot.z, 0.0f, 0.03f, 0.5f, 0.0f);
            }
            break;
        case STATE360_1:
            this->fwork[1] = 40.0f;

            if ((this->timer_0BC < 35) && (gCurrentLevel == LEVEL_FORTUNA)) {
                Math_SmoothStepToF(&this->rot_0F4.x, 15.0f, 0.1f, 1.0f, 0.0f);
            }

            if (this->timer_0BC == 0) {
                this->state = STATE360_3;
                if ((gCurrentLevel == LEVEL_BOLSE) && (this->aiIndex > -1)) {
                    this->state = STATE360_2;
                }
            }
            break;
        case STATE360_2:
            sp104 = 1;
            spF8 = 800.0f;
            spF4 = 1500.0f;
            spF0 = 0.4f;
            spEC = fabsf(this->fwork[4] - this->obj.pos.x);
            spE8 = fabsf(this->fwork[6] - this->obj.pos.z);
            sp10F = 0xB;

            if (this->aiType == AI360_FALCO) {
                spF0 = 0.5f;
            } else if ((this->animFrame != 2) && (this->animFrame == 3)) {
                spF0 = 0.5f;
            }

            if (this->aiIndex == AI360_FOX) {
                spF0 = 0.2f;
            }

            if (this->aiIndex <= -1) {
                this->state = STATE360_3;
            } else {
                if (gActors[this->aiIndex].aiType == AI360_MISSILE) {
                    spF0 = 0.8f;
                    spF4 = spF8 = 3000.0f;
                    this->fwork[3] = 2.0f;
                }

                if (this->aiIndex == AI360_FOX) {
                    if (gCurrentLevel != LEVEL_VENOM_2) {
                        if ((gPlayer[0].somersault && (this->iwork[4] > 10)) ||
                            ((gCurrentLevel == LEVEL_BOLSE) && (gPlayer[0].state == PLAYERSTATE_STANDBY))) {
                            this->state = STATE360_3;
                            this->counter_04E = 300;
                            this->timer_0BC = 160;
                            if (this->aiType == AI360_WOLF) {
                                ActorAllRange_PlayMessage(gMsg_ID_9369, RCID_WOLF);
                            }
                            break;
                        } else if ((this->iwork[4] > 200) && (gPlayer[0].dmgEffectTimer != 0)) {
                            this->iwork[4] = 100;
                            break;
                        }
                    }

                    if ((this->aiType >= AI360_WOLF) && (this->aiType != AI360_KATT) &&
                        !((gCurrentLevel == LEVEL_VENOM_2) && (this->aiType == AI360_WOLF))) {
                        spCC = SIN_DEG((this->index * 45) + gGameFrameCount) * 100.0f;
                        spC8 = COS_DEG((this->index * 45) + (gGameFrameCount * 2)) * 100.0f;
                        spC4 = SIN_DEG((this->index * 45) + gGameFrameCount) * 100.0f;
                    }
                    if (!gPlayer[0].somersault) {
                        this->fwork[4] = gPlayer[0].pos.x + spCC;
                        this->fwork[5] = gPlayer[0].pos.y + spC8;
                        this->fwork[6] = gPlayer[0].trueZpos + spC4;
                        this->fwork[1] = gPlayer[0].baseSpeed + 10.0f;
                    }
                    if ((gActors[0].state == STATE360_6) && (this->aiType <= AI360_PEPPY)) {
                        this->fwork[3] = 3.0f;
                        this->fwork[1] = gPlayer[0].baseSpeed - 5.0f;
                        this->iwork[11] = 2;
                    } else if ((gCurrentLevel == LEVEL_VENOM_2) && (this->aiType >= AI360_WOLF)) {
                        this->fwork[3] = 1.6f;
                        this->fwork[1] = 55.0f;
                    } else {
                        this->fwork[3] = 1.2f;
                    }

                    spF4 = 2000.0f;
                    spF8 = 700.0f;

                    if (gCurrentLevel == LEVEL_VENOM_2) {
                        spF0 = 0.5f;
                        sp10F = 3;
                    } else {
                        spF0 = 0.7f;
                    }
                } else if (this->aiIndex != AI360_GREAT_FOX) {
                    if (this->aiType >= AI360_ENEMY) {
                        spCC = SIN_DEG((this->index * 45) + gGameFrameCount) * 200.0f;
                        spC8 = COS_DEG((this->index * 45) + (gGameFrameCount * 2)) * 200.0f;
                        spC4 = SIN_DEG((this->index * 45) + gGameFrameCount) * 200.0f;
                    }

                    this->fwork[4] = gActors[this->aiIndex].obj.pos.x + spCC;
                    this->fwork[5] = gActors[this->aiIndex].obj.pos.y + spC8;
                    this->fwork[6] = gActors[this->aiIndex].obj.pos.z + spC4;

                    if ((gCurrentLevel == LEVEL_VENOM_2) && (this->aiType >= AI360_WOLF)) {
                        this->fwork[1] = 55.0f;
                        this->fwork[3] = 1.6f;
                    } else if ((gCurrentLevel == LEVEL_FORTUNA) && (this->aiType > AI360_ENEMY)) {
                        this->fwork[3] = 1.4f;
                        this->fwork[1] = 50.0f;
                    } else {
                        this->fwork[1] = gActors[this->aiIndex].fwork[0] + 10.0f;
                        if (this->fwork[1] < 30.0f) {
                            this->fwork[1] = 30.0f;
                        }
                        this->fwork[3] = 1.4f;
                    }
                } else {
                    this->fwork[4] = gBosses[0].obj.pos.x;
                    this->fwork[5] = gBosses[0].obj.pos.y + 400.0f;
                    this->fwork[6] = gBosses[0].obj.pos.z;
                    this->fwork[1] = 40.0f;
                }
                if ((this->aiIndex > -1) && (this->aiIndex != AI360_GREAT_FOX) && (gActors[0].state != STATE360_6)) {
                    if (spE8 < spF8) {
                        if (spEC < spF8) {
                            if (this->aiIndex != AI360_FOX) {
                                this->fwork[1] = gActors[this->aiIndex].fwork[0] - 5.0f;
                            } else {
                                this->fwork[1] = gPlayer[0].baseSpeed - 5.0f;
                                if ((gCurrentLevel == LEVEL_VENOM_2) && (gPlayer[0].state == PLAYERSTATE_U_TURN) &&
                                    (gPlayer[0].aerobaticPitch > 100.0f)) {
                                    this->iwork[16] = STATE360_8;
                                }
                            }
                        }
                    } else if (this->timer_0C0 == 0) {
                        this->timer_0C0 = RAND_INT(200.0f) + 200;
                        this->fwork[10] = 20.0f;
                    }

                    if ((spE8 < spF4) && (spEC < spF4)) {
                        this->iwork[4]++;
                        this->iwork[5] = 1;
                        if (!((this->index + gGameFrameCount) & sp10F) && (Rand_ZeroOne() < spF0) &&
                            func_360_80031900(this) &&
                            ((gActors[0].state == STATE360_2) || (gCurrentLevel == LEVEL_TRAINING))) {
                            if ((this->aiIndex == AI360_FOX) && (gCurrentLevel != LEVEL_TRAINING)) {
                                if ((this->iwork[4] > 250) && (gCurrentLevel != LEVEL_VENOM_ANDROSS)) {
                                    if ((Rand_ZeroOne() < 0.5f) || (gCurrentLevel == LEVEL_VENOM_2)) {
                                        this->iwork[4] = 0;
                                        switch (this->aiType) {
                                            case AI360_WOLF:
                                                AllRange_PlayMessage(gMsg_ID_19450, RCID_WOLF);
                                                break;
                                            case AI360_LEON:
                                                AllRange_PlayMessage(gMsg_ID_19451, RCID_LEON);
                                                break;
                                            case AI360_PIGMA:
                                                AllRange_PlayMessage(gMsg_ID_19452, RCID_PIGMA);
                                                break;
                                            case AI360_ANDREW:
                                                AllRange_PlayMessage(gMsg_ID_19453, RCID_ANDREW);
                                                break;
                                        }
                                    } else {
                                        AllRange_PlayMessage(gMsg_ID_2233, RCID_FALCO);
                                    }
                                }
                                this->iwork[0] = 1;
                            } else {
                                this->iwork[0] = 1;
                            }
                        }

                        if ((gRadioState == 0) && (this->timer_0C4 == 0) && (gAllRangeEventTimer > 700) &&
                            (gStarWolfMsgTimer == 0) && (gActors[0].obj.status == OBJ_ACTIVE)) {
                            this->timer_0C4 = 600;
                            if (Rand_ZeroOne() < 0.5f) {
                                gActors[this->aiIndex].iwork[6]++;
                                switch (this->aiIndex) {
                                    case AI360_FALCO:
                                        if ((gCurrentLevel == LEVEL_VENOM_2) && (Rand_ZeroOne() < 0.5f)) {
                                            ActorAllRange_PlayMessage(gMsg_ID_19462, RCID_FALCO);
                                        } else if ((gActors[this->aiIndex].iwork[6] >= 3) && (Rand_ZeroOne() < 0.5f)) {
                                            ActorAllRange_PlayMessage(gMsg_ID_20310, RCID_FALCO);
                                        } else {
                                            ActorAllRange_PlayMessage(gMsg_ID_9100, RCID_FALCO);
                                        }
                                        gActors[this->aiIndex].iwork[2] = this->aiType;
                                        if ((gTeamHelpActor == NULL) || (gTeamShields[this->aiIndex] <= 50)) {
                                            gTeamHelpActor = &gActors[this->aiIndex];
                                            gTeamHelpTimer = 320;
                                        }
                                        break;

                                    case AI360_SLIPPY:
                                        if ((gCurrentLevel == LEVEL_VENOM_2) && (Rand_ZeroOne() < 0.5f)) {
                                            ActorAllRange_PlayMessage(gMsg_ID_19463, RCID_SLIPPY);
                                        } else if ((gActors[this->aiIndex].iwork[6] >= 3) && (Rand_ZeroOne() < 0.5f)) {
                                            ActorAllRange_PlayMessage(gMsg_ID_20311, RCID_SLIPPY);
                                        } else {
                                            ActorAllRange_PlayMessage(gMsg_ID_9110, RCID_SLIPPY);
                                        }
                                        gActors[this->aiIndex].iwork[2] = this->aiType;
                                        if ((gTeamHelpActor == NULL) || (gTeamShields[this->aiIndex] <= 50)) {
                                            gTeamHelpActor = &gActors[this->aiIndex];
                                            gTeamHelpTimer = 320;
                                        }
                                        break;

                                    case AI360_PEPPY:
                                        if ((gCurrentLevel == LEVEL_VENOM_2) && (Rand_ZeroOne() < 0.5f)) {
                                            ActorAllRange_PlayMessage(gMsg_ID_19464, RCID_PEPPY);
                                        } else if ((gActors[this->aiIndex].iwork[6] >= 3) && (Rand_ZeroOne() < 0.5f)) {
                                            ActorAllRange_PlayMessage(gMsg_ID_20312, RCID_PEPPY);
                                        } else {
                                            ActorAllRange_PlayMessage(gMsg_ID_9120, RCID_PEPPY);
                                        }
                                        gActors[this->aiIndex].iwork[2] = this->aiType;
                                        if ((gTeamHelpActor == NULL) || (gTeamShields[this->aiIndex] <= 50)) {
                                            gTeamHelpActor = &gActors[this->aiIndex];
                                            gTeamHelpTimer = 320;
                                        }
                                        break;

                                    case AI360_WOLF:
                                        if (gStarWolfTeamAlive[0] != 0) {
                                            ActorAllRange_PlayMessage(gMsg_ID_9330, RCID_WOLF);
                                        }
                                        break;

                                    case AI360_LEON:
                                        if (gStarWolfTeamAlive[1] != 0) {
                                            ActorAllRange_PlayMessage(gMsg_ID_9340, RCID_LEON);
                                        }
                                        break;

                                    case AI360_PIGMA:
                                        if (gStarWolfTeamAlive[2] != 0) {
                                            ActorAllRange_PlayMessage(gMsg_ID_9350, RCID_PIGMA);
                                        }
                                        break;

                                    case AI360_ANDREW:
                                        if (gStarWolfTeamAlive[3] != 0) {
                                            ActorAllRange_PlayMessage(gMsg_ID_9360, RCID_ANDREW);
                                        }
                                        break;
                                }
                            } else {
                                switch (this->aiType) {
                                    case AI360_FALCO:
                                        if ((gCurrentLevel == LEVEL_FORTUNA) && (Rand_ZeroOne() < 0.5f)) {
                                            ActorAllRange_PlayMessage(gMsg_ID_9211, RCID_FALCO);
                                        } else {
                                            ActorAllRange_PlayMessage(gMsg_ID_9190, RCID_FALCO);
                                        }
                                        gActors[this->aiIndex].iwork[2] = AI360_FALCO;
                                        break;

                                    case AI360_SLIPPY:
                                        if ((gCurrentLevel == LEVEL_FORTUNA) && (Rand_ZeroOne() < 0.5f)) {
                                            ActorAllRange_PlayMessage(gMsg_ID_9212, RCID_SLIPPY);
                                        } else {
                                            ActorAllRange_PlayMessage(gMsg_ID_9200, RCID_SLIPPY);
                                        }
                                        gActors[this->aiIndex].iwork[2] = AI360_SLIPPY;
                                        break;

                                    case AI360_PEPPY:
                                        if ((gCurrentLevel == LEVEL_FORTUNA) && (Rand_ZeroOne() < 0.5f)) {
                                            ActorAllRange_PlayMessage(gMsg_ID_9213, RCID_PEPPY);
                                        } else {
                                            ActorAllRange_PlayMessage(gMsg_ID_9210, RCID_PEPPY);
                                        }
                                        gActors[this->aiIndex].iwork[2] = AI360_PEPPY;
                                        break;

                                    case AI360_WOLF:
                                        if (gCurrentLevel != LEVEL_VENOM_2) {
                                            if (this->iwork[6] == 0) {
                                                this->iwork[6] = 1;
                                                ActorAllRange_PlayMessage(gMsg_ID_9289, RCID_WOLF);
                                            } else if (this->iwork[4] > 150) {
                                                if (Rand_ZeroOne() < 0.5f) {
                                                    this->iwork[4] = 0;
                                                    ActorAllRange_PlayMessage(gMsg_ID_9290, RCID_WOLF);
                                                } else {
                                                    ActorAllRange_PlayMessage(gMsg_ID_2233, RCID_FALCO);
                                                }
                                            } else {
                                                ActorAllRange_PlayMessage(gMsg_ID_9322, RCID_WOLF);
                                            }
                                        }
                                        break;

                                    case AI360_LEON:
                                        if (gCurrentLevel == LEVEL_VENOM_2) {
                                            if ((Rand_ZeroOne() < 0.5f) && (this->aiIndex == AI360_FALCO)) {
                                                ActorAllRange_PlayMessage(gMsg_ID_9323, RCID_LEON);
                                            } else {
                                                ActorAllRange_PlayMessage(gMsg_ID_19451, RCID_LEON);
                                            }
                                        } else if ((Rand_ZeroOne() < 0.5f) && (this->aiIndex == AI360_FALCO)) {
                                            ActorAllRange_PlayMessage(gMsg_ID_9323, RCID_LEON);
                                        } else {
                                            ActorAllRange_PlayMessage(gMsg_ID_9300, RCID_LEON);
                                        }
                                        break;

                                    case AI360_PIGMA:
                                        if (gCurrentLevel == LEVEL_VENOM_2) {
                                            if ((Rand_ZeroOne() < 0.5f) && (this->aiIndex == AI360_PEPPY)) {
                                                ActorAllRange_PlayMessage(gMsg_ID_9324, RCID_PIGMA);
                                            } else {
                                                ActorAllRange_PlayMessage(gMsg_ID_19452, RCID_PIGMA);
                                            }
                                        } else if ((Rand_ZeroOne() < 0.5f) && (this->aiIndex == AI360_PEPPY)) {
                                            ActorAllRange_PlayMessage(gMsg_ID_9324, RCID_PIGMA);
                                        } else {
                                            ActorAllRange_PlayMessage(gMsg_ID_9310, RCID_PIGMA);
                                        }
                                        break;

                                    case AI360_ANDREW:
                                        if (gCurrentLevel == LEVEL_VENOM_2) {
                                            if ((Rand_ZeroOne() < 0.5f) && (this->aiIndex == AI360_SLIPPY)) {
                                                ActorAllRange_PlayMessage(gMsg_ID_9325, RCID_ANDREW);
                                            } else {
                                                ActorAllRange_PlayMessage(gMsg_ID_19453, RCID_ANDREW);
                                            }
                                        } else if ((Rand_ZeroOne() < 0.5f) && (this->aiIndex == AI360_SLIPPY)) {
                                            ActorAllRange_PlayMessage(gMsg_ID_9325, RCID_ANDREW);
                                        } else {
                                            ActorAllRange_PlayMessage(gMsg_ID_9320, RCID_ANDREW);
                                        }
                                        break;
                                }
                            }
                        }
                    } else {
                        this->iwork[4] = 0;
                    }
                    if ((this->aiIndex >= AI360_FALCO) && ((gActors[this->aiIndex].obj.status == OBJ_DYING) ||
                                                           (gActors[this->aiIndex].state == STATE360_6) ||
                                                           (gActors[this->aiIndex].obj.status == OBJ_FREE))) {
                        this->state = STATE360_3;
                        if (gCurrentLevel == LEVEL_BOLSE) {
                            ActorAllRange_ChooseNewTarget(this);
                        }
                    }
                }
            }
            break;
        case STATE360_3:
            sp104 = 1;
            if (this->timer_0BC == 0) {
                if ((this->aiType < AI360_ENEMY) || (gCurrentLevel == LEVEL_BOLSE)) {
                    if (gCurrentLevel == LEVEL_VENOM_2) {
                        if (this->aiType >= AI360_WOLF) {
                            this->fwork[3] = 1.6f;
                            this->fwork[1] = 55.0f;
                        } else {
                            this->fwork[3] = 1.4f;
                            this->fwork[1] = 50.0f;
                        }
                    } else {
                        this->fwork[3] = 1.2f;
                        this->fwork[1] = 40.0f;
                    }
                } else {
                    this->fwork[3] = 1.0f;
                    this->fwork[1] = 38.0f;
                }
                if ((gCurrentLevel == LEVEL_SECTOR_Z) && (gActors[0].state == STATE360_10)) {
                    this->fwork[10] = 30.0f;
                }

                if ((gLevelType == LEVELTYPE_SPACE) && (gCurrentLevel != LEVEL_BOLSE)) {
                    if ((gCurrentLevel == LEVEL_SECTOR_Z) && (this->aiType == AI360_KATT)) {
                        spE4 = RAND_FLOAT_CENTERED(0.0f);
                        spE0 = RAND_FLOAT_CENTERED(500.0f);
                        spDC = RAND_FLOAT_CENTERED(5000.0f) + 12000.0f;
                    } else {
                        spE4 = RAND_FLOAT_CENTERED(15000.0f);
                        spE0 = RAND_FLOAT_CENTERED(1000.0f);
                        spDC = RAND_FLOAT_CENTERED(15000.0f);
                    }
                } else {
                    spE4 = RAND_FLOAT_CENTERED(10000.0f);
                    if ((gCurrentLevel == LEVEL_BOLSE) || (gCurrentLevel == LEVEL_KATINA) ||
                        (gCurrentLevel == LEVEL_VENOM_2)) {
                        spE0 = RAND_FLOAT(1000.0f);
                    } else {
                        spE0 = 0.0f;
                    }
                    spDC = RAND_FLOAT_CENTERED(10000.0f);
                    if ((gCurrentLevel == LEVEL_KATINA) && (gPlayer[0].state == PLAYERSTATE_STANDBY)) {
                        spE4 = RAND_FLOAT_CENTERED(5000.0f);
                        spDC = RAND_FLOAT_CENTERED(5000.0f);
                    }
                }

                if ((fabsf(this->obj.pos.x - spE4) > 2000.0f) || (fabsf(this->obj.pos.z - spDC) > 2000.0f)) {
                    this->fwork[4] = spE4;
                    this->fwork[5] = spE0;
                    this->fwork[6] = spDC;
                    this->timer_0BC = RAND_INT(20.0f) + 10;
                }
            }

            if (this->timer_0C0 == 0) {
                this->timer_0C0 = RAND_INT(200.0f) + 200;
                this->fwork[10] = 30.0f;
            }

            if ((this->aiIndex >= AI360_FALCO) && (gActors[this->aiIndex].obj.id == OBJ_ACTOR_ALLRANGE) &&
                (gActors[this->aiIndex].timer_0C2 == 0) && (gActors[this->aiIndex].obj.status == OBJ_ACTIVE)) {
                this->state = STATE360_2;
                this->iwork[2] = AI360_FOX;
            }

            if (this->aiIndex == AI360_FOX) {
                if (this->counter_04E != 0) {
                    this->counter_04E--;
                }
                if (this->counter_04E == 0) {
                    this->state = STATE360_2;
                    this->iwork[2] = AI360_FOX;
                }
            }
            break;
        case STATE360_7:
            this->fwork[1] = 40.0f;
            Math_SmoothStepToF(&this->rot_0F4.x, 360.0f, 0.1f, 5.0f, 0.0001f);
            Math_SmoothStepToAngle(&this->obj.rot.z, 0.0f, 0.1f, 3.0f, 0.01f);
            if (this->rot_0F4.x > 350.0f) {
                this->state = STATE360_3;
            }
            break;
        case STATE360_8:
            this->fwork[1] = 40.0f;
            if ((this->index % 2) != 0) {
                Math_SmoothStepToAngle(&this->obj.rot.z, 355.0f, 0.1f, 3.0f, 0.01f);
            } else {
                Math_SmoothStepToAngle(&this->obj.rot.z, 5.0f, 0.1f, 3.0f, 0.01f);
            }

            switch (this->work_046) {
                case 0:
                    Math_SmoothStepToF(&this->rot_0F4.x, 200.0f, 0.1f, 6.0f, 0.0001f);
                    if (this->rot_0F4.x > 190.0f) {
                        this->rot_0F4.y += 190.0f;
                        if (this->rot_0F4.y >= 360.0f) {
                            this->rot_0F4.y -= 360.0f;
                        }
                        this->rot_0F4.x = 360.0f - (this->rot_0F4.x - 180.0f);
                        this->obj.rot.z += 180.0f;
                        if (this->obj.rot.z >= 360.0f) {
                            this->obj.rot.z -= 360.0f;
                        }
                        this->timer_0BC = 40;
                        this->work_046++;
                    }
                    this->obj.pos.y -= 3.0f;
                    break;
                case 1:
                    if (this->timer_0BC == 0) {
                        this->state = STATE360_3;
                    }
                    break;
            }
            break;
        case STATE360_9:
            this->fwork[1] = 40.0f;
            if (Math_SmoothStepToAngle(&this->rot_0F4.y, this->fwork[19], 0.5f, 5.0f, 0.0f) < 0.0f) {
                spD0 = 70.0f;
            } else {
                spD0 = 290.0f;
            }
            Math_SmoothStepToAngle(&this->obj.rot.z, spD0, 0.1f, 15.0f, 0.01f);
            if (this->timer_0BC == 0) {
                this->state = STATE360_3;
            }
            break;
        case STATE360_10:
            sp104 = 1;
            if (this->timer_0BC == 0) {
                this->state = STATE360_3;
            }
            if (this->timer_0BC > 20) {
                Math_SmoothStepToF(&this->fwork[23], 180.0f, 1.0f, 60.0f, 0.0f);
            }
            break;
    }

    if (sp104 != 0) {
        s32 var_v0 = 4 - 1;

        spE4 = this->fwork[4] - this->obj.pos.x;
        spE0 = this->fwork[5] - this->obj.pos.y;
        spDC = this->fwork[6] - this->obj.pos.z;

        if (gCurrentLevel == LEVEL_VENOM_2) {
            var_v0 = 2 - 1;
        }
        if (((this->index + gGameFrameCount) & var_v0) == 0) {
            this->fwork[19] = Math_RadToDeg(Math_Atan2F(spE4, spDC));
            this->fwork[20] = Math_RadToDeg(Math_Atan2F(spE0, sqrtf(SQ(spE4) + SQ(spDC))));
        }

        spD8 = this->fwork[20];
        spD4 = this->fwork[19];
        objectNearby = 0;

        if (sp104 == 1) {
            if (this->aiType < AI360_GREAT_FOX) {
                objectNearby = ActorAllRange_CheckObjectNearby(this);
                if ((objectNearby != 0) && (this->aiType < AI360_ENEMY) && (this->timer_0BE == 0) &&
                    ((this->fwork[7] < 0.01f) || (this->fwork[7] > 359.9f))) {
                    this->timer_0BE = RAND_INT(200.0f) + 200;
                    if (Rand_ZeroOne() < 0.5f) {
                        this->fwork[8] = 0.0f;
                        this->fwork[7] = 360.0f;
                    } else {
                        this->fwork[7] = 0.0f;
                        this->fwork[8] = 359.999f;
                    }
                }
            }

            if (objectNearby != 0) {
                if ((this->aiType < AI360_ENEMY) || (gCurrentLevel != LEVEL_FORTUNA)) {
                    spD8 += 40.0f * objectNearby;
                } else {
                    spD8 += 20.0f * objectNearby;
                }
                if (spD8 >= 360.0f) {
                    spD8 -= 360.0f;
                }
                if (spD8 < 0.0f) {
                    spD8 += 360.0f;
                }
            } else if ((this->obj.pos.y < (gGroundHeight + 50.0f)) && (spD8 > 180.0f)) {
                spD8 = 0.0f;
                this->rot_0F4.x = 0.0f;
            }
        }

        Math_SmoothStepToAngle(&this->rot_0F4.x, spD8, 0.5f, this->fwork[2], 0.0001f);

        spD0 = Math_SmoothStepToAngle(&this->rot_0F4.y, spD4, 0.5f, this->fwork[2], 0.0001f) * 30.0f;
        if (spD0 < 0.0f) {
            spD0 = spD0 * -1.0f;
        } else {
            spD0 = 360.0f - spD0;
        }

        if ((this->fwork[7] > 0.01f) && (this->fwork[7] < 359.9f)) {
            if ((((gGameFrameCount + 15) % 32) == 0) && (gCurrentLevel != LEVEL_VENOM_2)) {
                this->lockOnTimers[TEAM_ID_FOX] = 0;
            }
        } else {
            Math_SmoothStepToAngle(&this->obj.rot.z, spD0, 0.1f, 3.0f, 0.01f);
            this->iwork[19] = 0;
        }
    }

    if (this->iwork[19] != 0) {
        Math_SmoothStepToF(&this->fwork[7], this->fwork[8], 1.0f, 60.0f, 0.01f);
    } else {
        Math_SmoothStepToF(&this->fwork[7], this->fwork[8], 0.2f, 30.0f, 0.01f);
    }

    if ((this->fwork[7] > 0.01f) && (this->fwork[7] < 359.9f)) {
        Math_SmoothStepToAngle(&this->obj.rot.z, this->fwork[7], 0.2f, 100.0f, 0.01f);
        if ((this->aiType == AI360_KATT) && ((gGameFrameCount % 2) == 0)) {
            if ((this->fwork[7] > 10.0f) && (this->fwork[7] < 350.0f)) {
                Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
                Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);
                Matrix_RotateZ(gCalcMatrix, this->obj.rot.z * M_DTOR, MTXF_APPLY);
                spA8.x = 0.0f;
                spA8.y = 70.0f;
                spA8.z = -70.0f;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &spA8, &sp9C);
                Effect_Effect393_Spawn(this->obj.pos.x + sp9C.x, this->obj.pos.y + sp9C.y, this->obj.pos.z + sp9C.z,
                                       3.1f);
            }
        }
    }
    this->obj.rot.x = -this->rot_0F4.x;
    this->obj.rot.y = this->rot_0F4.y;
    Math_SmoothStepToF(&this->fwork[0], this->fwork[1], 0.2f, 1.0f, 0.1f);
    Math_SmoothStepToF(&this->fwork[2], this->fwork[3], 1.0f, 0.1f, 0.1f);

    spC0 = SIN_DEG(this->obj.rot.x);
    spB8 = COS_DEG(this->obj.rot.x);
    spBC = SIN_DEG(this->obj.rot.y);
    spB4 = COS_DEG(this->obj.rot.y);

    sp9C.z = (this->fwork[0] + this->fwork[9]) * spB8;
    sp9C.y = (this->fwork[0] + this->fwork[9]) * -spC0;
    sp9C.x = spBC * sp9C.z;
    sp9C.z = spB4 * sp9C.z;

    this->vel.x = this->fwork[13] + sp9C.x;
    this->vel.y = this->fwork[14] + sp9C.y;
    this->vel.z = this->fwork[12] + sp9C.z;

    this->fwork[13] -= (this->fwork[13] * 0.1f);
    this->fwork[14] -= (this->fwork[14] * 0.1f);
    this->fwork[12] -= (this->fwork[12] * 0.1f);
    if ((this->obj.pos.y < gGroundHeight + 40.0f) && (this->vel.y < 0.0f)) {
        this->obj.pos.y = gGroundHeight + 40.0f;
        this->vel.y = 0.0f;
    }

    if (this->iwork[0] != 0) {
        this->iwork[0] = 0;

        sp90.z = spB8 * 200.0f * 0.5f;
        sp90.y = -spC0 * 200.0f * 0.5f;
        sp90.x = spBC * sp90.z;
        sp90.z = spB4 * sp90.z;

        if ((gCurrentLevel == LEVEL_VENOM_2) && (this->aiType >= AI360_WOLF)) {
            Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
            Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);
            Matrix_RotateZ(gCalcMatrix, this->obj.rot.z * M_DTOR, MTXF_APPLY);
            spA8.y = 0.0f;
            spA8.z = 0.0f;
            if (Rand_ZeroOne() < 0.8f) {
                spA8.x = 60.0f;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &spA8, &sp9C);
                Actor_SpawnPlayerLaser(this->aiType, this->obj.pos.x + sp9C.x + (sp90.x * 1.5f),
                                       this->obj.pos.y + sp9C.y + (sp90.y * 1.5f),
                                       this->obj.pos.z + sp9C.z + (sp90.z * 1.5f), sp90.x, sp90.y, sp90.z,
                                       this->obj.rot.x, this->obj.rot.y, this->obj.rot.z);
            }
            if (Rand_ZeroOne() < 0.8f) {
                spA8.x = -60.0f;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &spA8, &sp9C);
                Actor_SpawnPlayerLaser(this->aiType, this->obj.pos.x + sp9C.x + (sp90.x * 1.5f),
                                       this->obj.pos.y + sp9C.y + (sp90.y * 1.5f),
                                       this->obj.pos.z + sp9C.z + (sp90.z * 1.5f), sp90.x, sp90.y, sp90.z,
                                       this->obj.rot.x, this->obj.rot.y, this->obj.rot.z);
            }
        } else {
            Actor_SpawnPlayerLaser(this->aiType, this->obj.pos.x + (sp90.x * 1.5f), this->obj.pos.y + (sp90.y * 1.5f),
                                   this->obj.pos.z + (sp90.z * 1.5f), sp90.x, sp90.y, sp90.z, this->obj.rot.x,
                                   this->obj.rot.y, this->obj.rot.z);
        }
    }

    ActorAllRange_ApplyDamage(this);

    radarMark = &gRadarMarks[this->index];
    radarMark->enabled = true;

    if (this->aiType == AI360_MISSILE) {
        radarMark->type = 100;
    } else {
        radarMark->type = this->aiType;
    }
    if (gCurrentLevel == LEVEL_TRAINING) {
        radarMark->type = 4;
    }

    radarMark->pos.x = this->obj.pos.x;
    radarMark->pos.y = this->obj.pos.y;
    radarMark->pos.z = this->obj.pos.z;
    radarMark->yRot = this->rot_0F4.y + 180.0f;
    if (this->iwork[1] != 0) {
        this->iwork[1]--;
        if ((this->iwork[1] == 0) && (gActors[0].state == STATE360_2) && (gRadioState == 0)) {
            switch (this->aiType) {
                case AI360_FALCO:
                    ActorAllRange_PlayMessage(gMsg_ID_9220, RCID_FALCO);
                    break;
                case AI360_SLIPPY:
                    ActorAllRange_PlayMessage(gMsg_ID_9230, RCID_SLIPPY);
                    break;
                case AI360_PEPPY:
                    if ((Rand_ZeroOne() < 0.1f) && (gCurrentLevel == LEVEL_KATINA)) {
                        ActorAllRange_PlayMessage(gMsg_ID_18150, RCID_PEPPY);
                    } else {
                        ActorAllRange_PlayMessage(gMsg_ID_9240, RCID_PEPPY);
                    }
                    break;
            }
        }
    }

    if ((gCurrentLevel != LEVEL_KATINA) && (gCurrentLevel != LEVEL_VENOM_ANDROSS) && (this->timer_0C2 == 0)) {
        if (((this->aiType >= AI360_ENEMY) && (this->aiType < AI360_GREAT_FOX)) ||
            ((this->aiType >= AI360_WOLF) && (this->aiType < AI360_ENEMY) && (this->timer_0C6 != 0))) {
            s32 var_a3 = 0;

            if (((gCurrentLevel == LEVEL_BOLSE) || (gCurrentLevel == LEVEL_SECTOR_Z)) && (this->timer_0C6 == 0)) {
                var_a3 = 3;
            }

            sp90.x = this->vel.x;
            sp90.y = this->vel.y;
            sp90.z = this->vel.z;
            temp_v0_27 = Object_CheckCollision(this->index, &this->obj.pos, &sp90, var_a3);
            if (temp_v0_27 != 0) {
                this->obj.pos.x -= this->vel.x;
                this->obj.pos.y -= this->vel.y;
                this->obj.pos.z -= this->vel.z;
                if ((temp_v0_27 >= 2) && (this->aiType > AI360_ENEMY)) {
                    this->timer_0BE = 2;
                    this->obj.status = OBJ_DYING;
                    this->itemDrop = DROP_NONE;
                    Effect386_Spawn1(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 0.0f, 0.0f, 0.0f, 5.0f, 15);
                    Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_EXPLOSION_S);
                } else {
                    this->dmgType = DMG_BEAM;
                    this->damage = 10;
                    this->health = 0;
                    ActorAllRange_ApplyDamage(this);
                }
            }
        }
    }

    if (gCurrentLevel == LEVEL_FORTUNA) {
        ActorAllRange_SetShadowData(this);
    } else if (gCurrentLevel == LEVEL_VENOM_ANDROSS) {
        this->work_04A++;
        if (this->work_04A >= Animation_GetFrameCount(&D_VE2_600C200)) {
            this->work_04A = 0;
        }
    }

    Math_SmoothStepToF(&this->fwork[22], 0.0f, 0.8f, 0.05f, 1e-7f);
    Math_SmoothStepToF(&this->fwork[23], 0.0f, 1.0f, 30.0f, 0.01f);

    if (this->iwork[8] != 0) {
        this->iwork[8]--;
    }
}

void ActorAllRange_DrawShield(ActorAllRange* this) {
    f32 sp24;
    s32 alpha;

    if (this->fwork[22] > 0) {
        Matrix_Push(&gGfxMatrix);
        sp24 = 3.5f;
        alpha = (s32) (this->fwork[22] * 60.0f);
        if (gCurrentLevel == LEVEL_VENOM_2) {
            sp24 *= 1.5f;
        }
        Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -30.0f, MTXF_APPLY);
        Matrix_Scale(gGfxMatrix, sp24, sp24 * 0.5f, sp24, MTXF_APPLY);
        Matrix_RotateY(gGfxMatrix, gGameFrameCount * 3.0f * M_DTOR, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        RCP_SetupDL(&gMasterDisp, SETUPDL_41);
        if (gCurrentLevel == LEVEL_KATINA) {
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 128, 255, 255, alpha);
        } else if (gCurrentLevel == LEVEL_BOLSE) {
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 128, 128, alpha);
        } else {
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 48, 255, 255, alpha);
        }
        gSPDisplayList(gMasterDisp++, D_1031630);
        Matrix_Pop(&gGfxMatrix);
    }
}

void ActorAllRange_DrawBarrelRoll(ActorAllRange* this) {
    s32 alpha;

    if (this->fwork[23] > 1.0f) {
        Matrix_Push(&gGfxMatrix);
        alpha = this->fwork[23];
        Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -30.0f, MTXF_APPLY);
        Matrix_RotateZ(gGfxMatrix, -this->obj.rot.z * M_DTOR, MTXF_APPLY);
        Matrix_RotateX(gGfxMatrix, -this->obj.rot.x * M_DTOR, MTXF_APPLY);
        Matrix_RotateY(gGfxMatrix, M_DTOR * -this->obj.rot.y - gPlayer[0].camYaw, MTXF_APPLY);
        Matrix_RotateX(gGfxMatrix, gPlayer[0].camPitch, MTXF_APPLY);
        Matrix_RotateZ(gGfxMatrix, gGameFrameCount * 20.0f * this->iwork[15] * M_DTOR, MTXF_APPLY);

        if (this->iwork[15] < 0) {
            Matrix_RotateX(gGfxMatrix, M_PI, MTXF_APPLY);
        }

        Matrix_Scale(gGfxMatrix, 2.0f, 2.0f, 2.0f, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        RCP_SetupDL(&gMasterDisp, SETUPDL_67);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, alpha);
        gDPSetEnvColor(gMasterDisp++, 0, 0, 160, alpha);
        gSPDisplayList(gMasterDisp++, aBarrelRollTex);
        Matrix_Pop(&gGfxMatrix);
    }
}

bool ActorAllRange_MissileOverrideLimbDraw(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    ActorAllRange* this = (ActorAllRange*) thisx;

    if ((this->timer_0C6 % 2) != 0) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_34);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 128, 128, 255);
    } else {
        RCP_SetupDL(&gMasterDisp, SETUPDL_29);
    }

    if ((limbIndex == 1) || (limbIndex == 3)) {
        rot->z += gGameFrameCount * 3.0f;
    }
    if ((limbIndex == 1) || (limbIndex == 2)) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_34);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, (s32) gSzMissileR, (s32) gSzMissileG, (s32) gSzMissileB, 255);
    }
    return false;
}

void ActorAllRange_Draw(ActorAllRange* this) {
    f32 sp38;
    s32 pad[3];
    Vec3f sp1E4 = { 0.0f, 0.0f, 0.0f };
    Vec3f jointTable[30];
    f32 pad2;

    if (this->aiType != AI360_EVENT_HANDLER) {
        if ((this->iwork[8] != 0) && (this->aiType < AI360_GREAT_FOX)) {
            pad2 = SIN_DEG(this->iwork[8] * 400.0f);
            sp38 = this->iwork[8] * pad2;
            Matrix_RotateY(gGfxMatrix, M_DTOR * sp38, MTXF_APPLY);
            Matrix_RotateX(gGfxMatrix, M_DTOR * sp38, MTXF_APPLY);
            Matrix_RotateZ(gGfxMatrix, M_DTOR * sp38, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
        }

        if ((this->timer_0C6 % 2) == 0) {
            RCP_SetupDL(&gMasterDisp, SETUPDL_29);
            gSPFogPosition(gMasterDisp++, gFogNear, 1005);
        }

        switch (this->aiType) {
            case AI360_FOX:
            case AI360_FALCO:
            case AI360_SLIPPY:
            case AI360_PEPPY:
                Matrix_Push(&gGfxMatrix);
                ActorTeamArwing_Draw(this);
                Matrix_Pop(&gGfxMatrix);
                ActorAllRange_DrawBarrelRoll(this);
                break;

            case AI360_WOLF:
            case AI360_LEON:
            case AI360_PIGMA:
            case AI360_ANDREW:
                if (gCurrentLevel == LEVEL_VENOM_2) {
                    gSPDisplayList(gMasterDisp++, aStarWolfUpgradedShipDL);
                    Matrix_Push(&gGfxMatrix);
                    Matrix_Translate(gGfxMatrix, 30.0f, 0.0f, -60.0f, MTXF_APPLY);
                    Actor_DrawEngineGlow(this, EG_GREEN);
                    Matrix_Pop(&gGfxMatrix);
                    Matrix_Push(&gGfxMatrix);
                    Matrix_Translate(gGfxMatrix, -30.0f, 0.0f, -60.0f, MTXF_APPLY);
                    Actor_DrawEngineGlow(this, EG_GREEN);
                    Matrix_Pop(&gGfxMatrix);
                    ActorAllRange_DrawBarrelRoll(this);
                    ActorAllRange_DrawShield(this);
                } else {
                    gSPDisplayList(gMasterDisp++, aStarWolfStandardShipDL);
                    Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -60.0f, MTXF_APPLY);
                    if (gCurrentLevel == LEVEL_BOLSE) {
                        Actor_DrawEngineGlow(this, EG_ORANGE);
                    } else {
                        Actor_DrawEngineGlow(this, EG_GREEN);
                    }
                }
                break;

            case AI360_KATT:
                gSPDisplayList(gMasterDisp++, aKattShipDL);
                Actor_DrawEngineAndContrails(this);
                break;

            case AI360_BILL:
                gSPDisplayList(gMasterDisp++, aBillShipDL);
                Actor_DrawEngineAndContrails(this);
                break;

            case AI360_GREAT_FOX:
                Display_SetSecondLight(&this->obj.pos);
                this->animFrame = 1;
                ActorCutscene_Draw(this);
                break;

            case AI360_MISSILE:
                Animation_GetFrameData(&aSzMissileAnim, 0, jointTable);
                Animation_DrawSkeleton(3, aSzMissileSkel, jointTable, ActorAllRange_MissileOverrideLimbDraw, NULL, this,
                                       gCalcMatrix);
                Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -400.0f, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, this->fwork[29], this->fwork[29], this->fwork[29], MTXF_APPLY);
                Actor_DrawEngineGlow(this, EG_ORANGE);
                break;

            default:
                if (gCurrentLevel == LEVEL_FORTUNA) {
                    Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, 60.0f, MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_FO_6006BE0);
                    Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -100.0f, MTXF_APPLY);
                    Matrix_Scale(gGfxMatrix, 1.5f, 1.5f, 1.5f, MTXF_APPLY);
                    Actor_DrawEngineGlow(this, EG_GREEN);
                } else if (gCurrentLevel == LEVEL_KATINA) {
                    switch (this->animFrame) {
                        case 0:
                            gSPDisplayList(gMasterDisp++, aKaEnemyLowPolyDL);
                            break;
                        case 1:
                            gSPDisplayList(gMasterDisp++, aKaCornerianFighterDL);
                            Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -60.0f, MTXF_APPLY);
                            Actor_DrawEngineGlow(this, EG_RED);
                            break;
                        case 3:
                            gSPDisplayList(gMasterDisp++, aKaEnemyDL);
                            Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, 30.0f, MTXF_APPLY);
                            ActorAllRange_DrawShield(this);
                            break;
                    }
                } else if (gCurrentLevel == LEVEL_SECTOR_Z) {
                    gSPDisplayList(gMasterDisp++, aSzInvaderIIIDL);
                    Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -60.0f, MTXF_APPLY);
                    Actor_DrawEngineGlow(this, EG_GREEN);
                } else if (gCurrentLevel == LEVEL_BOLSE) {
                    gSPDisplayList(gMasterDisp++, D_BO_6008770);
                    Matrix_Push(&gGfxMatrix);
                    Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -60.0f, MTXF_APPLY);
                    Actor_DrawEngineGlow(this, EG_GREEN);
                    Matrix_Pop(&gGfxMatrix);
                    ActorAllRange_DrawShield(this);
                } else if (gCurrentLevel == LEVEL_VENOM_ANDROSS) {
                    Animation_GetFrameData(&D_VE2_600C200, this->work_04A, this->vwork);
                    Matrix_Scale(gGfxMatrix, 10.0f, 10.0f, 10.0f, MTXF_APPLY);
                    Animation_DrawSkeleton(0, D_VE2_600C2AC, this->vwork, NULL, NULL, this, &gIdentityMatrix);
                } else if (gCurrentLevel == LEVEL_VERSUS) {
                    gSPDisplayList(gMasterDisp++, D_versus_3015740);
                } else if (gCurrentLevel == LEVEL_TRAINING) {
                    if (this->aiIndex == AI360_FOX) {
                        gSPDisplayList(gMasterDisp++, aStarWolfStandardShipDL);
                        Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -60.0f, MTXF_APPLY);
                        Actor_DrawEngineGlow(this, EG_ORANGE);
                    } else {
                        gSPDisplayList(gMasterDisp++, aVenomFighter1DL);
                        Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -60.0f, MTXF_APPLY);
                        Actor_DrawEngineGlow(this, EG_GREEN);
                    }
                }
                break;
        }
    }
}
