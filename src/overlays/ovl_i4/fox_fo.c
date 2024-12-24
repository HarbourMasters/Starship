/*
 * File: fox_fo.c
 * System: Fortuna
 * Description: Level: Fortuna
 */

#include "global.h"
#include "assets/ast_fortuna.h"

// Spawns up to 10 enemies from the center base.
void Fortuna_SpawnEnemies(ActorEvent* this) {
    s32 i;
    s32 enemyCount;
    ActorAllRange* enemy = &gActors[10];
    f32 sEnemySpawnAngle[] = { 180.0f, 60.0f, 300.0f };

    for (enemyCount = 0, i = 0; i < 10; i++, enemy++) {
        if (enemy->obj.status != OBJ_FREE) {
            enemyCount++;
        }
    }

    if ((enemyCount < 10) && (this->timer_0C0 == 0)) {
        if (gAllRangeEventTimer < (gAllRangeSpawnEvent - 500)) {
            this->timer_0C0 = 40;

            this->counter_04E++;
            if (this->counter_04E >= 3) {
                this->counter_04E = 0;
            }

            for (i = 0, enemy = &gActors[AI360_ENEMY]; i < 10; i++, enemy++) {
                if (enemy->obj.status == OBJ_FREE) {
                    Actor_Initialize(enemy);
                    enemy->obj.status = OBJ_ACTIVE;
                    enemy->obj.id = OBJ_ACTOR_ALLRANGE;
                    enemy->obj.pos.x = gBosses[0].obj.pos.x;
                    enemy->obj.pos.y = gBosses[0].obj.pos.y + 20.0f;
                    enemy->obj.pos.z = gBosses[0].obj.pos.z;
                    enemy->state = 1;
                    enemy->timer_0BC = 100;
                    enemy->aiType = i + AI360_ENEMY;
                    enemy->aiIndex = -1;

                    if ((i == 3) && (Rand_ZeroOne() < 0.3f)) {
                        enemy->aiIndex = AI360_SLIPPY;
                    }
                    if ((i == 4) && (Rand_ZeroOne() < 0.3f)) {
                        enemy->aiIndex = AI360_PEPPY;
                    }
                    if ((i == 5) && (Rand_ZeroOne() < 0.3f)) {
                        enemy->aiIndex = AI360_FALCO;
                    }

                    enemy->rot_0F4.x = 3.0f;
                    enemy->rot_0F4.y = sEnemySpawnAngle[this->counter_04E];
                    enemy->health = 24;
                    enemy->drawShadow = enemy->iwork[11] = 1;
                    enemy->itemDrop = DROP_SILVER_RING_50p;
                    Object_SetInfo(&enemy->info, enemy->obj.id);
                    AUDIO_PLAY_SFX(NA_SE_EN_ENGINE_01, enemy->sfxSource, 4);
                    break;
                }
            }
        }
    }
    ActorAllRange_UpdateStarWolfEvents(this);
}

void Fortuna_SetupStarWolfFlee(ActorAllRange* this, f32 xPos, f32 yPos, f32 zPos, f32 yRot) {
    s32 health = this->health;

    Actor_Initialize(this);
    this->health = health;
    this->obj.status = OBJ_ACTIVE;
    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;
    this->obj.id = OBJ_ACTOR_ALLRANGE;
    this->aiType = AI360_WOLF;
    this->drawShadow = true;
    this->state = 0;
    this->timer_0BC = 10000;
    this->rot_0F4.y = yRot;
    this->iwork[11] = 1;
    this->rot_0F4.x = 0.0f;
    Object_SetInfo(&this->info, this->obj.id);
    AUDIO_PLAY_SFX(NA_SE_EN_WOLF_ENGINE, this->sfxSource, 4);
}

Vec3f sCsTeamInitialPos[] = {
    { 0.0f, 700.0f, 12000.0f },
    { -300.0f, 1000.0f, 13000.0f },
    { 300.0f, 700.0f, 14000.0f },
};
Vec3f sTeamInitialPos[] = {
    { 1000.0f, 300.0f, 0.0f },
    { -1000.0f, 300.0f, 0 },
    { 0.0f, 500.0f, 0 },
};

void Fortuna_UpdateEvents(ActorEvent* this) {
    s32 i;
    Player* player = &gPlayer[0];
    ActorAllRange* team;
    ActorAllRange* falco = &gActors[AI360_FALCO];
    ActorAllRange* slippy = &gActors[AI360_SLIPPY];
    ActorAllRange* peppy = &gActors[AI360_PEPPY];
    ActorAllRange* wolf = &gActors[AI360_WOLF];
    ActorAllRange* greatFox = &gActors[19];
    s32 pad2[3];

    PRINTF("Enm->work[0]=%d\n", this->iwork[0]);
    PRINTF("tim %d\n", gAllRangeEventTimer);

    if ((player->state == PLAYERSTATE_DOWN) || (player->state == PLAYERSTATE_NEXT)) {
        gAllRangeEventTimer = 20000;
        return;
    }

    if (gAllRangeEventTimer == 50) {
        Radio_PlayMessage(gMsg_ID_9000, RCID_FOX);
    }

    if ((gAllRangeEventTimer + 400) == (0, gAllRangeSpawnEvent)) {
        Radio_PlayMessage(gMsg_ID_9010, RCID_SLIPPY);
    }

    if ((gAllRangeEventTimer + 240) == (0, gAllRangeSpawnEvent)) {
        Radio_PlayMessage(gMsg_ID_9375, RCID_ROB64);
        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 1);
        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 1);
    }

    if ((gAllRangeEventTimer + 100) == (0, gAllRangeSpawnEvent)) {
        Radio_PlayMessage(gMsg_ID_9380, RCID_FOX);
    }

    if (gAllRangeEventTimer == 7160) {
        Radio_PlayMessage(gMsg_ID_9385, RCID_FOX);
    }

    if (gAllRangeEventTimer == 7000) {
        AUDIO_PLAY_SFX(NA_SE_EXPLOSION_DEMO2, gBosses[0].sfxSource, 4);
        AllRange_ClearRadio();
        Radio_PlayMessage(gMsg_ID_9390, RCID_ROB64);
        gAllRangeCountdownScale = 1.0f;
        gShowAllRangeCountdown = 1;
        gAllRangeCountdown[0] = 1;
        gAllRangeCountdown[1] = 4;
        gAllRangeCountdown[2] = 99;
    }

    if (gAllRangeEventTimer == 8036) {
        Radio_PlayMessage(gMsg_ID_9395, RCID_ROB64);
    }

    if (gAllRangeEventTimer == 8540) {
        Radio_PlayMessage(gMsg_ID_9400, RCID_ROB64);
        Audio_PlaySequence(SEQ_PLAYER_BGM, NA_BGM_STAGE_FO, 0, 0);
        gActors[1].aiIndex = gActors[2].aiIndex = gActors[3].aiIndex = gActors[4].aiIndex = gActors[5].aiIndex =
            gActors[6].aiIndex = gActors[7].aiIndex = -1;
    }

    if ((gAllRangeSpawnEvent < gAllRangeEventTimer) && (gAllRangeEventTimer < 9970) && (gStarWolfTeamAlive[0] == 0) &&
        (gStarWolfTeamAlive[1] == 0) && (gStarWolfTeamAlive[2] == 0) && (gStarWolfTeamAlive[3] == 0)) {
        gAllRangeEventTimer = 9970;
    }

    if (gAllRangeEventTimer == 9056) {
        if ((gStarWolfTeamAlive[0] != 0) || (gStarWolfTeamAlive[1] != 0) || (gStarWolfTeamAlive[2] != 0) ||
            ((gStarWolfTeamAlive[3] != 0))) {
            Radio_PlayMessage(gMsg_ID_9405, RCID_ROB64);
        } else {
            gAllRangeEventTimer = 9995;
        }
    }

    if (gAllRangeEventTimer == 9206) {
        gShowAllRangeCountdown = false;
        this->state = 5;
        gPlayer[0].state = PLAYERSTATE_STANDBY;
        this->iwork[0] = 0;
        this->fwork[0] = 0.0f;
        AllRange_ClearRadio();
        for (i = 4; i < 8; i++) {
            Object_Kill(&gActors[i].obj, gActors[i].sfxSource);
        }
    }

    if ((gAllRangeEventTimer == 10000) && ((gStarWolfTeamAlive[0] != 0) || (gStarWolfTeamAlive[1] != 0) ||
                                           (gStarWolfTeamAlive[2] != 0) || (gStarWolfTeamAlive[3] != 0))) {
        Radio_PlayMessage(gMsg_ID_9420, RCID_FOX);
    }

    if (gAllRangeEventTimer == 10100) {
        gShowAllRangeCountdown = 0;
        this->iwork[0] = 0;
        this->state = 6;
        gPlayer[0].state = PLAYERSTATE_LEVEL_COMPLETE;
        gPlayer[0].csState = 0;
        gPlayer[0].unk_000 = 0.0f;

        AllRange_ClearRadio();

        for (i = 4; i < 8; i++) {
            Object_Kill(&gActors[i].obj, gActors[i].sfxSource);
        }

        if ((gStarWolfTeamAlive[0] == 0) && (gStarWolfTeamAlive[1] == 0) && (gStarWolfTeamAlive[2] == 0) &&
            (gStarWolfTeamAlive[3] == 0)) {
            Radio_PlayMessage(gMsg_ID_9411, RCID_FOX);
            gMissionStatus = MISSION_ACCOMPLISHED;
            gPlayer[0].csTimer = 50;
            player->unk_190 = 5.0f;
            player->unk_194 = 5.0f;
            AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, player->sfxSource, 0);
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 30);
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 30);
        } else {
            gMissionStatus = MISSION_COMPLETE;
            gPlayer[0].csTimer = 30;
        }
    }

    switch (this->state) {
        case 0:
            gAllRangeSpawnEvent = TIME_IN_SECONDS(96);

            for (i = 0; i < 6; i++) {
                gSavedStarWolfTeamAlive[i] = true;
                gStarWolfTeamAlive[i] = true;
            }

            gAllRangeEventTimer = 0;
            gStarWolfMsgTimer = 0;

            if (player->state == PLAYERSTATE_ACTIVE) {
                this->state = 2;
                player->pos.x = 0.0f;
                player->pos.z = 8000.0f;
                player->pos.y = 670.0f;

                gAllRangeEventTimer = 200;
                if (gAllRangeCheckpoint != 0) {
                    gAllRangeEventTimer = gAllRangeSpawnEvent - 1;
                    gHitCount = gSavedHitCount;
                }
            } else {
                this->state = 1;
                player->pos.x = 0.0f;
                player->pos.z = 15000.0f;
                player->pos.y = 670.0f;
                player->yRot_114 = 0.0f;

                for (team = &gActors[AI360_FALCO], i = AI360_FALCO; i <= AI360_PEPPY; i++, team++) {
                    team->obj.pos.x = sCsTeamInitialPos[i - 1].x;
                    team->obj.pos.y = sCsTeamInitialPos[i - 1].y;
                    team->obj.pos.z = sCsTeamInitialPos[i - 1].z;
                }
            }
            Camera_UpdateArwing360(player, true);
            break;

        case 1:
            for (team = &gActors[AI360_FALCO], i = AI360_FALCO; i <= AI360_PEPPY; i++, team++) {
                team->fwork[4] = sTeamInitialPos[i - 1].x;
                team->fwork[5] = sTeamInitialPos[i - 1].y;
                team->fwork[6] = sTeamInitialPos[i - 1].z;
                team->state = 3;
                team->timer_0BC = 3;

                if (gCsFrameCount == 264) {
                    team->state = 2;
                    this->state = 2;
                    player->state = PLAYERSTATE_ACTIVE;
                    player->unk_014 = 0.0001f;
                    AUDIO_PLAY_BGM(gBgmSeqId);
                    gLevelStartStatusScreenTimer = 80;
                }
            };
            break;

        case 2:
            Fortuna_SpawnEnemies(this);
            break;

        case 3:
            player->cam.eye.x += wolf->vel.x * 0.23f;
            player->cam.eye.y += wolf->vel.y * 0.23f;
            player->cam.eye.z += wolf->vel.z * 0.23f;

            Math_SmoothStepToF(&player->cam.at.x, wolf->obj.pos.x, 1.0f, 20000.0f, 0.0f);
            Math_SmoothStepToF(&player->cam.at.y, wolf->obj.pos.y, 1.0f, 20000.0f, 0.0f);
            Math_SmoothStepToF(&player->cam.at.z, wolf->obj.pos.z, 1.0f, 20000.0f, 0.0f);
            Math_SmoothStepToF(&player->camRoll, 0.0f, 1.0f, 1000.0f, 0.0f);

            if (gAllRangeEventTimer == (gAllRangeSpawnEvent + 2)) {
                gStarWolfMsgTimer = 883;
                gAllRangeCheckpoint = 1;

                gSavedHitCount = gHitCount;

                for (i = TEAM_ID_FALCO; i <= TEAM_ID_PEPPY; i++) {
                    gSavedTeamShields[i] = gTeamShields[i];
                };
            }

            if ((gControllerPress->button & START_BUTTON) || (gAllRangeEventTimer == (gAllRangeSpawnEvent + 440))) {
                this->state = 2;
                player->state = PLAYERSTATE_ACTIVE;
                Camera_Update360(player, true);
                player->unk_014 = 0.0f;
                D_hud_80161708 = 0;
            }
            gPauseEnabled = false;
            break;

        case 5:
            gAllRangeEventTimer = 9207;
            this->iwork[0]++;
            this->fwork[0] += 10.0f;
            player->cam.eye.x = 300.0f;
            player->cam.eye.y = 300.0f;
            player->cam.eye.z = -1000.0f;
            player->cam.at.x = this->fwork[0] + 300.0f;
            player->cam.at.y = this->fwork[0] + 500.0f;
            player->cam.at.z = -15000.0f;
            player->camRoll = 0.0f;

            if ((this->iwork[0] == 50) && (gStarWolfTeamAlive[0] != 0)) {
                if (gRadioState == 0) {
                    Radio_PlayMessage(gMsg_ID_9431, RCID_WOLF);
                }
                Fortuna_SetupStarWolfFlee(&gActors[AI360_WOLF], player->cam.eye.x - 200.0f, player->cam.eye.y,
                                          player->cam.eye.z, 160.0f);
            }

            if ((this->iwork[0] == 70) && (gStarWolfTeamAlive[1] != 0)) {
                if (gRadioState == 0) {
                    Radio_PlayMessage(gMsg_ID_9432, RCID_LEON);
                }
                Fortuna_SetupStarWolfFlee(&gActors[AI360_LEON], player->cam.eye.x, player->cam.eye.y + 50.0f,
                                          player->cam.eye.z, 160.0f);
            }

            if ((this->iwork[0] == 90) && (gStarWolfTeamAlive[2] != 0)) {
                if (gRadioState == 0) {
                    Radio_PlayMessage(gMsg_ID_9433, RCID_PIGMA);
                }
                Fortuna_SetupStarWolfFlee(&gActors[AI360_PIGMA], player->cam.eye.x - 200.0f, player->cam.eye.y + 200.0f,
                                          player->cam.eye.z, 160.0f);
            }

            if ((this->iwork[0] == 110) && (gStarWolfTeamAlive[3] != 0)) {
                if (gRadioState == 0) {
                    Radio_PlayMessage(gMsg_ID_9434, RCID_ANDREW);
                }
                Fortuna_SetupStarWolfFlee(&gActors[AI360_ANDREW], player->cam.eye.x - 300.0f, player->cam.eye.y,
                                          player->cam.eye.z, 160.0f);
            }

            if (this->iwork[0] == 250) {
                this->state = 2;
                player->state = PLAYERSTATE_ACTIVE;

                Camera_Update360(player, true);

                player->unk_014 = 0.0f;
                D_hud_80161708 = 0;

                for (i = 4; i < 8; i++) {
                    Object_Kill(&gActors[i].obj, gActors[i].sfxSource);
                }

                gShowAllRangeCountdown = 1;
                gAllRangeEventTimer = 9970;
            }
            break;

        case 6:
            this->iwork[0]++;
            if (gMissionStatus == MISSION_COMPLETE) {
                falco->aiIndex = AI360_FOX;
                falco->state = 2;
                slippy->aiIndex = AI360_FOX;
                slippy->state = 2;
                peppy->aiIndex = AI360_FOX;
                peppy->state = 2;
                if (this->iwork[0] == 130) {
                    Vec3f sp50 = { 0.0f, 0.0f, -10000 };

                    Actor_Initialize(greatFox);
                    Matrix_Translate(gCalcMatrix, player->pos.x, player->pos.y, player->trueZpos, MTXF_NEW);
                    Matrix_RotateY(gCalcMatrix, (player->rot.y + player->yRot_114) * M_DTOR, MTXF_APPLY);
                    Matrix_RotateX(gCalcMatrix, player->rot.x * M_DTOR, MTXF_APPLY);
                    Matrix_MultVec3f(gCalcMatrix, &sp50, &greatFox->obj.pos);

                    greatFox->obj.status = OBJ_ACTIVE;
                    greatFox->obj.id = OBJ_ACTOR_ALLRANGE;
                    greatFox->state = 4;
                    greatFox->rot_0F4.y = player->rot.y + player->yRot_114 + 180.0f;
                    greatFox->rot_0F4.x = 15.0f;
                    greatFox->aiType = AI360_GREAT_FOX;
                    greatFox->fwork[1] = 90.0f;
                    greatFox->fwork[0] = 90.0f;
                    Object_SetInfo(&greatFox->info, greatFox->obj.id);
                }
            }
            gSceneSetup = 1;
            gProjectFar = 30000.0f;
            break;

        default:
            break;
    }

    if (gStarWolfMsgTimer != 0) {
        gStarWolfMsgTimer--;
        switch (gStarWolfMsgTimer) {
            case 860:
                if (gStarWolfTeamAlive[0] != 0) {
                    Radio_PlayMessage(gMsg_ID_9250, RCID_WOLF);
                }
                break;

            case 760:
                if (gStarWolfTeamAlive[1] != 0) {
                    Radio_PlayMessage(gMsg_ID_9260, RCID_LEON);
                }
                break;

            case 660:
                if (gStarWolfTeamAlive[2] != 0) {
                    if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                        Radio_PlayMessage(gMsg_ID_9275, RCID_PIGMA);
                    } else {
                        Radio_PlayMessage(gMsg_ID_9270, RCID_PIGMA);
                    }
                }
                break;

            case 540:
                if (gStarWolfTeamAlive[3] != 0) {
                    Radio_PlayMessage(gMsg_ID_9280, RCID_ANDREW);
                }
                break;

            case 380:
                Radio_PlayMessage(gMsg_ID_9285, RCID_FOX);
                break;

            case 240:
                Radio_PlayMessage(gMsg_ID_9385, RCID_FOX);
                break;
        }
    }
}

void Fortuna_ActorDebris_Setup(ActorDebris* this, Vec3f* pos, Vec3f* rot, f32 xVel, f32 yVel, f32 zVel, s32 state) {
    Actor_Initialize(this);
    this->obj.status = OBJ_ACTIVE;
    this->obj.id = OBJ_ACTOR_DEBRIS;
    this->state = state;

    this->obj.pos = *pos;
    this->obj.rot = *rot;

    this->vel.x = xVel;
    this->vel.y = yVel;
    this->vel.z = zVel;

    this->scale = 2.5f;
    this->timer_0BC = RAND_INT(15.0f) + 25.0f;
    this->gravity = 0.5f;
    Object_SetInfo(&this->info, this->obj.id);
}

void Fortuna_ActorDebris_Spawn(Vec3f* pos, Vec3f* rot, f32 xVel, f32 yVel, f32 zVel, s32 state) {
    s32 i;

    for (i = ARRAY_COUNT(gActors) - 1; i >= 30; i--) {
        if (gActors[i].obj.status == 0) {
            Fortuna_ActorDebris_Setup(&gActors[i], pos, rot, xVel, yVel, zVel, state);
            break;
        }
    }
}

void Fortuna_FoRadar_Update(FoRadar* this) {
    this->fwork[0] += 2.0f;
    if (this->state == 2) {
        this->state = 3;
        Fortuna_ActorDebris_Spawn(this->vwork, &this->vwork[6], RAND_FLOAT_CENTERED(50.0f), RAND_FLOAT(10.0f) + 10.0f,
                                  RAND_FLOAT_CENTERED(50.0f), 36);
        Fortuna_ActorDebris_Spawn(&this->vwork[1], &this->vwork[7], RAND_FLOAT_CENTERED(50.0f),
                                  RAND_FLOAT(10.0f) + 10.0f, RAND_FLOAT_CENTERED(50.0f), 36);
        Fortuna_ActorDebris_Spawn(&this->vwork[2], &this->vwork[8], RAND_FLOAT_CENTERED(50.0f),
                                  RAND_FLOAT(10.0f) + 10.0f, RAND_FLOAT_CENTERED(50.0f), 35);
        Fortuna_ActorDebris_Spawn(&this->vwork[3], &this->vwork[9], RAND_FLOAT_CENTERED(50.0f),
                                  RAND_FLOAT(10.0f) + 10.0f, RAND_FLOAT_CENTERED(50.0f), 35);
        Effect386_Spawn1(this->obj.pos.x, this->obj.pos.y + 180.0f, this->obj.pos.z, 0.0f, 0.0f, 0.0f, 5.0f, 10);
        this->itemDrop = DROP_SILVER_RING;
        this->obj.pos.y += 230.0f;
        Actor_Despawn(this);
        this->obj.pos.y -= 230.0f;
    }

    if ((this->dmgType != DMG_NONE) && (this->state == 0)) {
        this->dmgType = DMG_NONE;
        this->state = 1;
        this->info.hitbox = SEGMENTED_TO_VIRTUAL(D_FO_600FF64);
        this->info.targetOffset = 0.0f;
        this->lockOnTimers[TEAM_ID_FOX] = 0;
        this->info.bonus = 0;
        AUDIO_PLAY_SFX(NA_SE_EN_EXPLOSION_M, this->sfxSource, 4);
    }
}

void Fortuna_FoRadar_PostLimbDraw(s32 limbIndex, Vec3f* rot, void* thisx) {
    Vec3f vec = { 0.0f, 0.0f, 0.0f };
    FoRadar* actor = (FoRadar*) thisx;

    if (actor->state == 1) {
        switch (limbIndex) {
            case 1:
                Matrix_MultVec3f(gCalcMatrix, &vec, actor->vwork);
                Matrix_GetYRPAngles(gCalcMatrix, &actor->vwork[6]);
                break;

            case 2:
                Matrix_MultVec3f(gCalcMatrix, &vec, &actor->vwork[1]);
                Matrix_GetYRPAngles(gCalcMatrix, &actor->vwork[7]);
                break;

            case 3:
                Matrix_MultVec3f(gCalcMatrix, &vec, &actor->vwork[2]);
                Matrix_GetYRPAngles(gCalcMatrix, &actor->vwork[8]);
                break;

            case 4:
                Matrix_MultVec3f(gCalcMatrix, &vec, &actor->vwork[3]);
                Matrix_GetYRPAngles(gCalcMatrix, &actor->vwork[9]);
                break;

            case 7:
                Matrix_MultVec3f(gCalcMatrix, &vec, &actor->vwork[4]);
                Matrix_GetYRPAngles(gCalcMatrix, &actor->vwork[10]);
                break;

            case 8:
                Matrix_MultVec3f(gCalcMatrix, &vec, &actor->vwork[5]);
                Matrix_GetYRPAngles(gCalcMatrix, &actor->vwork[11]);
                break;
        }
    }
}

bool Fortuna_FoRadar_OverrideLimbDraw(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    FoRadar* actor = (FoRadar*) thisx;

    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);

    if ((actor->state != 0) && (limbIndex != 8)) {
        *dList = NULL;
    }

    switch (limbIndex) {
        case 1:
        case 2:
            gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
            break;

        case 5:
            rot->x += actor->fwork[0];
            break;

        case 6:
            rot->x += actor->fwork[0];
            break;

        case 7:
            rot->x += actor->fwork[0] * 0.7f;
            break;
    }

    return false;
}

void Fortuna_FoRadar_Draw(FoRadar* this) {
    Vec3f frameTable[20];

    Animation_GetFrameData(&aFoRadarAnim, 0, frameTable);
    Animation_DrawSkeleton(3, aFoRadarSkel, frameTable, Fortuna_FoRadar_OverrideLimbDraw, Fortuna_FoRadar_PostLimbDraw,
                           this, gCalcMatrix);

    if (this->state == 1) {
        this->state = 2;
    }
}

// Explosion seen from space if the mission fails.
void Fortuna_CsExplosion(void) {
    ActorCutscene* actor = &gActors[50];

    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_CUTSCENE;
    actor->obj.pos.x = 0.0f;
    actor->obj.pos.y = 0.0f;
    actor->obj.pos.z = -9000.0f;
    actor->animFrame = ACTOR_CS_FO_EXPLOSION;
    actor->scale = 0.0f;
    Object_SetInfo(&actor->info, actor->obj.id);
}

f32 sLevelCompleteCsActorInitPosX[] = { -200.0f, 200.0f, -50.0f, -2000.0f };
f32 sLevelCompleteCsActorInitPosY[] = { 0.0f, 30.0f, -90.0f, 0.0f };
f32 sLevelCompleteCsActorInitPosZ[] = { -100.0f, -200.0f, -300.0f, 0.0f };

void Fortuna_LevelComplete_CsSpawnTeam(ActorCutscene* this, s32 actorIdx) {
    Actor_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_ACTOR_CUTSCENE;

    this->obj.pos.x = sLevelCompleteCsActorInitPosX[actorIdx] + gPlayer[0].pos.x;
    this->obj.pos.y = sLevelCompleteCsActorInitPosY[actorIdx] + gPlayer[0].pos.y;
    this->obj.pos.z = sLevelCompleteCsActorInitPosZ[actorIdx] + gPlayer[0].trueZpos;

    this->vel.z = gPlayer[0].baseSpeed;

    Object_SetInfo(&this->info, this->obj.id);

    if (actorIdx < 3) {
        this->iwork[11] = 1;
        AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, this->sfxSource, 4);
        if (CVarGetInteger("gTeamFaces", 1) == 1) {
            // @port: Setup team faces
            this->iwork[14] = actorIdx + 2;
        }
    } else {
        this->obj.pos.z = -9500.0f;
        this->animFrame = ACTOR_CS_GREAT_FOX;
        this->vel.z = 22.0f;
        AUDIO_PLAY_SFX(NA_SE_GREATFOX_ENGINE, this->sfxSource, 0);
        AUDIO_PLAY_SFX(NA_SE_GREATFOX_BURNER, this->sfxSource, 0);
    }
}

void Fortuna_LevelComplete(Player* player) {
    s32 i;
    Vec3f src;
    Vec3f dest;
    ActorCutscene* greatFox = &gActors[0];
    ActorCutscene* slippy = &gActors[1];
    ActorCutscene* peppy = &gActors[2];
    ActorCutscene* falco = &gActors[3];
    s32 pad[3];

    if ((player->csState < 10) && (player->csState >= 0)) {
        Math_SmoothStepToF(&player->zRotBarrelRoll, 0.0f, 0.1f, 15.0f, 0.0f);
        Math_SmoothStepToF(&player->zRotBank, 0.0f, 0.1f, 15.0f, 0.0f);
        Math_SmoothStepToF(&player->camRoll, 0.0f, 0.1f, 3.0f, 0.0f);
        Math_SmoothStepToAngle(&player->aerobaticPitch, 0.0f, 0.1f, 20.0f, 0.0f);
        if (gMissionStatus == MISSION_COMPLETE) {
            if (player->pos.y < 700.0f) {
                Math_SmoothStepToF(&player->pos.y, 700.0f, 0.1f, 10.0f, 0.0f);
            }
        } else if (player->pos.y < 500.0f) {
            Math_SmoothStepToF(&player->pos.y, 500.0f, 0.1f, 5.0f, 0.0f);
        }

        Camera_Update360(player, false);
        player->cam.eye.x += player->vel.x * 0.1f;
        player->cam.eye.y += player->vel.y * 0.1f;
        player->cam.eye.z += player->vel.z * 0.1f;
    }

    player->arwing.upperRightFlapYrot = 0.0f;
    player->arwing.upperLeftFlapYrot = 0.0f;
    player->arwing.bottomRightFlapYrot = 0.0f;
    player->arwing.bottomLeftFlapYrot = 0.0f;

    Math_SmoothStepToF(&player->boostSpeed, 0.0f, 0.1f, 1.5f, 0.0f);

    switch (player->csState) {
        case -1:
            player->arwing.drawFace = true;
            player->rot.y = 0.0f;
            player->baseSpeed = 30.0f;
            player->yRot_114 = 180.0f;
            player->rot.x = -7.0f;
            Math_SmoothStepToF(&player->rot.z, 0.0f, 0.05f, 1.0f, 0.0f);
            player->zRotBank = 0.0f;
            player->zRotBarrelRoll = 0.0f;
            player->aerobaticPitch = 0.0f;
            player->cam.eye.x = -200.0f;
            player->cam.eye.y = 100.0f;
            player->cam.eye.z = -1500.0f;
            player->cam.at.x = player->pos.x;
            player->cam.at.y = player->pos.y;
            player->cam.at.z = player->trueZpos;

            if (player->csTimer < 80) {
                gFillScreenAlphaTarget = 255;
                gFillScreenAlphaStep = 10;
                gFillScreenGreen = gFillScreenRed = gFillScreenBlue = 0;
                if (player->csTimer == 0) {
                    player->csTimer = 0;
                    player->csState = 1;
                }
            }
            break;

        case 0:
            if (gMissionStatus == MISSION_COMPLETE) {
                Math_SmoothStepToF(&player->rot.y, 40.0f, 0.1f, 2.5f, 0.0f);
                Math_SmoothStepToF(&player->rot.z, 60.0f, 0.2f, 5.0f, 0.0f);
                Math_SmoothStepToF(&player->rot.x, 0.0f, 0.1f, 2.5f, 0.0f);
            } else {
                player->unk_190 = 2.0f;
                player->cam.eye.y += 3.0f;
                Math_SmoothStepToF(&player->rot.z,
                                   Math_SmoothStepToF(&player->yRot_114,
                                                      Math_RadToDeg(Math_Atan2F(player->pos.x, player->trueZpos)), 0.1f,
                                                      4.0f, 0.0f) *
                                       20.0f,
                                   0.2f, 5.0f, 0.0f);
                Math_SmoothStepToF(&player->rot.x, 0.0f, 0.1f, 2.5f, 0.0f);
            }

            if (player->csTimer == 0) {
                if (gMissionStatus != MISSION_COMPLETE) {
                    player->csTimer = 150;
                    player->csState = -1;
                    player->pos.x = 0.0f;
                    player->boostSpeed = 0.0f;
                    player->baseSpeed = 0.0f;
                    player->pos.y = 350.0f;
                    player->pos.z = -2800.0f;
                } else {
                    player->csTimer = 280;
                    player->csState = 1;
                }
                player->unk_194 = 5.0f;
                player->unk_190 = 5.0f;
                AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, player->sfxSource, 0);
            }
            break;

        case 1:
            player->unk_190 = 2.0f;
            Math_SmoothStepToF(&player->rot.x, 15.0f, 0.1f, 0.4f, 0.0f);
            Math_SmoothStepToF(&player->rot.z, -40.0f, 0.2f, 5.0f, 0.0f);
            Math_SmoothStepToF(&player->rot.y, -120.0f, 0.1f, 2.0f, 0.0f);
            player->baseSpeed += 1.0f;
            if (player->baseSpeed >= 70.0f) {
                player->baseSpeed = 70.0f;
                player->contrailScale += 0.04f;
                if (player->contrailScale > 0.6f) {
                    player->contrailScale = 0.6f;
                }
            }
            if (player->csTimer == 0) {
                player->csState = 2;
                player->csTimer = 1000;
                for (i = 0; i < ARRAY_COUNT(gActors); i++) {
                    Object_Kill(&gActors[i].obj, gActors[i].sfxSource);
                }
                //! FAKE:
                if (((&dest) && (&dest)) && (&dest)) {}

                Audio_StopPlayerNoise(0);
                Audio_KillSfxBySource(player->sfxSource);
                player->draw = false;
                gFillScreenAlpha = 255;
                gFillScreenAlphaTarget = 255;
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
                gFillScreenAlphaStep = 0;
            }
            break;

        case 2:
            if ((gMissionStatus == MISSION_COMPLETE) && (player->csTimer) > 830) {
                gFillScreenAlphaTarget = 0;
                gFillScreenAlphaStep = 8;
            }
            if (player->csTimer == 810) {
                Audio_KillSfxBySource(gBosses[0].sfxSource);
            }
            if (player->csTimer == 830) {
                gFillScreenAlphaTarget = 255;
                gFillScreenAlphaStep = 2;
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
            }

            gBosses[0].swork[0] = 1;

            if ((FoBase_ExplodeCs(&gBosses[0]) == 2) || (gMissionStatus != MISSION_COMPLETE)) {
                Play_ClearObjectData();
                if (gMissionStatus == MISSION_COMPLETE) {
                    player->csState = 10;
                } else {
                    player->csState = 20;
                }

                for (i = 0; i < 200; i++) {
                    gScenery360[i].obj.status = OBJ_FREE;
                }

                Play_SetupStarfield();
                gLevelType = LEVELTYPE_SPACE;
                gGroundType = gBgColor = gFogRed = gFogGreen = gFogBlue = 0;
                gLight1R = gLight2R = D_ctx_80161A70 = 86;
                gLight1G = gLight2G = D_ctx_80161A74 = 58;
                gLight1B = gLight2B = D_ctx_80161A78 = 25;
                gAmbientR = 11;
                gAmbientG = 8;
                gAmbientB = 24;
                gEnvLightxRot = gLight1xRotTarget = gLight1xRotTarget = gLight2xRotTarget = gLight1xRotTarget = -59.0f;
                gEnvLightyRot = gLight1yRotTarget = gLight1yRotTarget = gLight2yRotTarget = gLight1yRotTarget = 58.0f;
                gEnvLightzRot = gLight1zRotTarget = gLight1zRotTarget = gLight2zRotTarget = gLight1zRotTarget = 13.0f;

                if (gMissionStatus == MISSION_COMPLETE) {
                    player->pos.x = 0.0f;
                    player->pos.y = 0.0f;
                    player->rot.x = 0.0f;
                    player->rot.z = 0.0f;
                    player->baseSpeed = 0.0f;
                    player->yRot_114 = 0.0f;
                    player->rot.y = 180.0f;
                    Fortuna_CsExplosion();
                } else {
                    player->pos.x = 0.0f;
                    player->rot.x = 0.0f;
                    player->rot.z = 0.0f;
                    player->yRot_114 = 0.0f;
                    player->baseSpeed = 0.0f;
                    player->cam.at.y = 16.0f;
                    player->pos.y = -100.0f;
                    player->rot.y = 180.0f;
                }
                player->pos.z = -10000.0f;
                gCsFrameCount = 0;
                player->arwing.drawFace = true;
                player->wingPosition = 1;
                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 100);
                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 100);

                Audio_StartPlayerNoise(0);

                if (gMissionStatus == MISSION_COMPLETE) {
                    Fortuna_LevelComplete_CsSpawnTeam(greatFox, 3);
                }
            }
            break;

        case 10:
            player->draw = true;
            gFillScreenAlphaTarget = 0;
            gFillScreenAlphaStep = 4;
            player->cam.eye.x = 400.0f;
            player->cam.eye.y = 0;
            player->cam.eye.z = 0.0f;
            player->cam.at.x = greatFox->obj.pos.x;
            player->cam.at.y = greatFox->obj.pos.y;
            player->cam.at.z = greatFox->obj.pos.z;

            if (gCsFrameCount == 100) {
                player->baseSpeed = 30.0f;
                if (gTeamShields[TEAM_ID_FALCO] > 0) {
                    Fortuna_LevelComplete_CsSpawnTeam(falco, 0);
                }
                if (gTeamShields[TEAM_ID_SLIPPY] > 0) {
                    Fortuna_LevelComplete_CsSpawnTeam(slippy, 1);
                }
                if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                    Fortuna_LevelComplete_CsSpawnTeam(peppy, 2);
                }
            }

            if (gCsFrameCount == 496) {
                player->csState = 11;
                D_ctx_80177A48[0] = 0.01f;
                D_ctx_80177A48[1] = 0.0f;
                D_ctx_80177A48[2] = -400.0f;
                D_ctx_80177A48[3] = 0.0f;
                falco->iwork[TEAM_FACE] = FACE_FALCO;
                slippy->iwork[TEAM_FACE] = FACE_SLIPPY;
                peppy->iwork[TEAM_FACE] = FACE_PEPPY;
            }

            if (gCsFrameCount == 200) {
                if (gMissionStatus == MISSION_COMPLETE) {
                    AUDIO_PLAY_BGM(NA_BGM_COURSE_FAILURE);
                } else {
                    AUDIO_PLAY_BGM(NA_BGM_COURSE_CLEAR);
                }
            }

            if (gCsFrameCount == 420) {
                gLevelClearScreenTimer = 100;
            }
            break;

        case 11:
            D_ctx_80177A48[1] += D_ctx_80177A48[3];
            Matrix_RotateX(gCalcMatrix, -M_DTOR * 10.0f, MTXF_NEW);
            Matrix_RotateY(gCalcMatrix, D_ctx_80177A48[1] * M_DTOR, MTXF_APPLY);
            src.x = 0;
            src.y = 0.0f;
            src.z = D_ctx_80177A48[2];
            Matrix_MultVec3f(gCalcMatrix, &src, player->jointTable);
            gCsCamEyeX = player->jointTable[0].x + player->pos.x;
            gCsCamEyeY = player->jointTable[0].y + player->pos.y;
            gCsCamEyeZ = player->jointTable[0].z + (player->pos.z - 250.0f);
            gCsCamAtX = player->pos.x;
            gCsCamAtY = player->pos.y;
            gCsCamAtZ = player->pos.z - 250.0f;

            Math_SmoothStepToF(D_ctx_80177A48, 0.05f, 1.0f, 0.001f, 0);

            Math_SmoothStepToF(&player->cam.eye.x, gCsCamEyeX, D_ctx_80177A48[0], 20000.0f, 0);
            Math_SmoothStepToF(&player->cam.eye.y, gCsCamEyeY, D_ctx_80177A48[0], 20000.0f, 0);
            Math_SmoothStepToF(&player->cam.eye.z, gCsCamEyeZ, D_ctx_80177A48[0], 20000.0f, 0);

            Math_SmoothStepToF(&player->cam.at.x, gCsCamAtX, D_ctx_80177A48[0], 20000.0f, 0);
            Math_SmoothStepToF(&player->cam.at.y, gCsCamAtY, D_ctx_80177A48[0], 20000.0f, 0);
            Math_SmoothStepToF(&player->cam.at.z, gCsCamAtZ, D_ctx_80177A48[0], 20000.0f, 0);

            Math_SmoothStepToF(&player->baseSpeed, 0.0f, 0.05f, 2.0f, 0);

            Math_SmoothStepToF(&falco->vel.z, 0.0f, 0.05f, 2.0f, 0);
            Math_SmoothStepToF(&slippy->vel.z, 0.0f, 0.05f, 2.0f, 0);
            Math_SmoothStepToF(&peppy->vel.z, 0.0f, 0.05f, 2.0f, 0);
            Math_SmoothStepToF(&greatFox->vel.z, 0.0f, 0.05f, 2.0f, 0);

            if (gCsFrameCount == 500) {
                Radio_PlayMessage(gMsg_ID_20010, RCID_FOX);
            }

            if (gMissionStatus == MISSION_COMPLETE) {
                switch (gCsFrameCount) {
                    case 588:
                        switch (gTeamShields[TEAM_ID_SLIPPY]) {
                            case -1:
                                Radio_PlayMessage(gMsg_ID_20339, RCID_ROB64);
                                break;
                            case 0:
                                Radio_PlayMessage(gMsg_ID_20345, RCID_ROB64);
                                break;
                            default:
                                Radio_PlayMessage(gMsg_ID_9425, RCID_SLIPPY);
                                break;
                        }
                        break;

                    case 735:
                        switch (gTeamShields[TEAM_ID_PEPPY]) {
                            case -1:
                                Radio_PlayMessage(gMsg_ID_20338, RCID_ROB64);
                                break;
                            case 0:
                                Radio_PlayMessage(gMsg_ID_20344, RCID_ROB64);
                                break;
                            default:
                                Radio_PlayMessage(gMsg_ID_9426, RCID_PEPPY);
                                break;
                        }
                        break;

                    case 881:
                        switch (gTeamShields[TEAM_ID_FALCO]) {
                            case -1:
                                Radio_PlayMessage(gMsg_ID_20337, RCID_ROB64);
                                break;
                            case 0:
                                Radio_PlayMessage(gMsg_ID_20340, RCID_ROB64);
                                break;
                            default:
                                Radio_PlayMessage(gMsg_ID_9427, RCID_FALCO);
                                break;
                        }
                        break;
                }
            } else {
                switch (gCsFrameCount) {
                    case 588:
                        switch (gTeamShields[TEAM_ID_SLIPPY]) {
                            case -1:
                                Radio_PlayMessage(gMsg_ID_20339, RCID_ROB64);
                                break;
                            case 0:
                                Radio_PlayMessage(gMsg_ID_20345, RCID_ROB64);
                                break;
                            default:
                                Radio_PlayMessage(gMsg_ID_9428, RCID_SLIPPY);
                                break;
                        }
                        break;

                    case 735:
                        switch (gTeamShields[TEAM_ID_PEPPY]) {
                            case -1:
                                Radio_PlayMessage(gMsg_ID_20338, RCID_ROB64);
                                break;
                            case 0:
                                Radio_PlayMessage(gMsg_ID_20344, RCID_ROB64);
                                break;
                            default:
                                Radio_PlayMessage(gMsg_ID_9429, RCID_PEPPY);
                                break;
                        }
                        break;

                    case 881:
                        switch (gTeamShields[TEAM_ID_FALCO]) {
                            case -1:
                                Radio_PlayMessage(gMsg_ID_20337, RCID_ROB64);
                                break;
                            case 0:
                                Radio_PlayMessage(gMsg_ID_20340, RCID_ROB64);
                                break;
                            default:
                                Radio_PlayMessage(gMsg_ID_9430, RCID_FALCO);
                                break;
                        }
                        break;
                }
            }

            if (gCsFrameCount < 1136) {
                Math_SmoothStepToF(&D_ctx_80177A48[3], 0.55f, 1.0f, 0.02f, 0);
            } else {
                gStarfieldScrollY += 0.3f;
                gStarfieldScrollX += 0.3f;
                Math_SmoothStepToF(&D_ctx_80177A48[3], 0.0f, 1.0f, 0.02f, 0);
                if (gCsFrameCount == 1216) {
                    player->csState = 12;
                    player->csTimer = 1000;
                    D_ctx_80177A48[4] = 1.0f;
                    peppy->vel.y = 0.1f;
                    slippy->vel.y = 0.1f;
                    AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, player->sfxSource, 0);
                    player->unk_194 = 5.0f;
                    player->unk_190 = 5.0f;
                    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 50);
                    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 50);
                }
            }
            break;

        case 12:
            gStarfieldScrollY += 0.3f;
            gStarfieldScrollX += 0.3f;
            player->baseSpeed += 1.0f;
            player->baseSpeed *= 1.15f;
            player->pos.y += D_ctx_80177A48[4];
            D_ctx_80177A48[4] *= 1.19f;
            player->unk_190 = 2.0f;

            if (gTeamShields[TEAM_ID_FALCO] > 0) {
                if (player->csTimer == 980) {
                    AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, falco->sfxSource, 0);
                    falco->vel.y = 1.0f;
                    falco->fwork[29] = 5.0f;
                }
                if (player->csTimer < 980) {
                    falco->vel.z += 1.0f;
                    falco->vel.z *= 1.15f;
                    falco->vel.y *= 1.19f;
                    falco->iwork[11] = 2;
                }
            }

            if ((gTeamShields[TEAM_ID_PEPPY] > 0) && (player->csTimer == 960)) {
                AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, peppy->sfxSource, 0);
                peppy->vel.y = 1.0f;
                peppy->fwork[29] = 5.0f;
            }

            if (player->csTimer < 960) {
                peppy->vel.z += 1.0f;
                peppy->vel.z *= 1.15f;
                peppy->vel.y *= 1.19f;
                peppy->iwork[11] = 2;
            }

            if (gTeamShields[TEAM_ID_SLIPPY] > 0) {
                if (player->csTimer == 940) {
                    AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, slippy->sfxSource, 0);
                    slippy->vel.y = 1.0f;
                    slippy->fwork[29] = 5.0f;
                }

                if (player->csTimer < 940) {
                    slippy->vel.z += 1.0f;
                    slippy->vel.z *= 1.15f;
                    slippy->vel.y *= 1.19f;
                    slippy->iwork[11] = 2;
                }
            }

            if (player->csTimer == 910) {
                greatFox->vel.y = 1.0f;
                greatFox->obj.rot.x = -2.0f;
            }

            if (player->csTimer < 910) {
                greatFox->vel.z += 1.0f;
                greatFox->vel.z *= 1.02f;
                greatFox->vel.y *= 1.06f;
                greatFox->obj.rot.x *= 1.03f;
            }

            if (gCsFrameCount == 1382) {
                player->state = PLAYERSTATE_NEXT;
                player->csTimer = 0;
                gFadeoutType = 4;
                Audio_FadeOutAll(10);
                for (i = 0; i < 6; i++) {
                    gSavedStarWolfTeamAlive[i] = gStarWolfTeamAlive[i];
                }
                gLeveLClearStatus[LEVEL_FORTUNA] = Play_CheckMedalStatus(50) + 1;
            }
            break;

        case 20:
            if (gTeamShields[TEAM_ID_FALCO] > 0) {
                Fortuna_LevelComplete_CsSpawnTeam(falco, 0);
                falco->obj.pos.x = (player->pos.x - 100.0f) - 400.0f;
                falco->obj.pos.y = player->pos.y + 400.0f;
                falco->obj.pos.z = player->trueZpos - 150.0f;
                falco->obj.rot.z = 90.0f;
            }
            if (gTeamShields[TEAM_ID_SLIPPY] > 0) {
                Fortuna_LevelComplete_CsSpawnTeam(slippy, 1);
                slippy->obj.pos.x = player->pos.x + 100.0f + 400.0f;
                slippy->obj.pos.y = player->pos.y + 400.0f;
                slippy->obj.pos.z = player->trueZpos - 150.0f;
                slippy->obj.rot.z = -90.0f;
            }
            if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                Fortuna_LevelComplete_CsSpawnTeam(peppy, 2);
                peppy->obj.pos.x = player->pos.x;
                peppy->obj.pos.y = player->pos.y + 100.0f + 400.0f;
                peppy->obj.pos.z = player->trueZpos - 250.0f;
            }
            Fortuna_LevelComplete_CsSpawnTeam(greatFox, 3);

            greatFox->obj.pos.z = player->pos.z + 400.0f;
            greatFox->vel.z = 0.0f;
            greatFox->info.bonus = 1;
            gCsFrameCount = 0;
            player->csState = 21;
            player->draw = true;

            for (i = 0; i < 9; i++) {
                D_ctx_80177A48[i] = 0.0f;
            }

            D_ctx_80177A48[5] = 94.0f;
            gCsCamAtX = 0.0f;
            gCsCamAtY = 30.0f;
            gCsCamAtZ = 0.0f;

        case 21:
            if (gCsFrameCount < 30) {
                break;
            }

            if (gFillScreenAlpha != 0) {
                gFillScreenAlphaTarget = 0;
                gFillScreenAlphaStep = 1;
            }

            if (gCsFrameCount == 140) {
                player->baseSpeed = 30.0f;
                falco->vel.z = 30.0f;
                slippy->vel.z = 30.0f;
                peppy->vel.z = 30.0f;
                greatFox->vel.z = 30.0f;
            }
            if (gCsFrameCount > 140) {
                Math_SmoothStepToF(&falco->obj.rot.z, 0.0f, 0.03f, 1.2f, 0.0001f);
                Math_SmoothStepToF(&falco->obj.pos.x, -100.0f, 0.03f, 1000.0f, 0.0001f);
                Math_SmoothStepToF(&falco->obj.pos.y, 40.0f, 0.03f, 1000.0f, 0.0001f);
            }
            if (gCsFrameCount > 180) {
                Math_SmoothStepToF(&slippy->obj.rot.z, 0.0f, 0.03f, 1.2f, 0.0001f);
                Math_SmoothStepToF(&slippy->obj.pos.x, 100.0f, 0.03f, 1000.0f, 0.0001f);
                Math_SmoothStepToF(&slippy->obj.pos.y, 40.0f, 0.03f, 1000.0f, 0.0001f);
            }
            if (gCsFrameCount > 220) {
                Math_SmoothStepToF(&peppy->obj.pos.y, 90.0f, 0.03f, 1000.0f, 0.0001f);
            }
            if (gCsFrameCount > 340) {
                Math_SmoothStepToF(&player->pos.y, -10.0f, 0.03f, 1000.0f, 0.0001f);
            }
            if (gCsFrameCount > 530) {
                Radio_PlayMessage(gMsg_ID_20010, RCID_FOX);
                player->pos.y = -10.0f;
                falco->obj.rot.z = 0.0f;
                falco->obj.pos.x = -100.0f;
                falco->obj.pos.y = 40.0f;
                slippy->obj.rot.z = 0.0f;
                slippy->obj.pos.x = 100.0f;
                slippy->obj.pos.y = 40.0f;
                peppy->obj.pos.y = 90.0f;
                player->csState = 22;
            }

            switch (gCsFrameCount) {
                case 140:
                    AUDIO_PLAY_BGM(NA_BGM_COURSE_CLEAR);
                    break;
                case 450:
                    gLevelClearScreenTimer = 100;
                    break;
            }
            src.x = 0.0f;
            src.y = D_ctx_80177A48[7];
            src.z = D_ctx_80177A48[5];
            Matrix_Translate(gCalcMatrix, player->pos.x, 0.0f, player->pos.z + gPathProgress, MTXF_NEW);
            Matrix_RotateY(gCalcMatrix, -(D_ctx_80177A48[4] * M_DTOR), MTXF_APPLY);
            Matrix_MultVec3f(gCalcMatrix, &src, &dest);
            player->cam.eye.x = gCsCamEyeX = dest.x;
            player->cam.eye.y = gCsCamEyeY = dest.y;
            player->cam.eye.z = gCsCamEyeZ = dest.z;
            Math_SmoothStepToF(&gCsCamAtY, 0.0f, 0.005f, 1000.0f, 0.0001f);
            player->cam.at.x = player->pos.x;
            player->cam.at.y = gCsCamAtY;
            player->cam.at.z = player->pos.z + gPathProgress;
            break;

        case 22:
            if ((gCsFrameCount >= 1110) && (gCsFrameCount < 1240)) {
                Math_SmoothStepToF(&player->baseSpeed, 0.0f, 0.02f, 1000.0f, 0.001f);
                Math_SmoothStepToF(&falco->vel.z, 0.0f, 0.02f, 1000.0f, 0.001f);
                Math_SmoothStepToF(&slippy->vel.z, 0.0f, 0.02f, 1000.0f, 0.001f);
                Math_SmoothStepToF(&peppy->vel.z, 0.0f, 0.02f, 1000.0f, 0.001f);
                Math_SmoothStepToF(&greatFox->vel.z, 0.0f, 0.02f, 1000.0f, 0.001f);
            }
            if (gCsFrameCount == 1239) {
                player->baseSpeed = 0.0f;
                falco->vel.z = 0.0f;
                slippy->vel.z = 0.0f;
                peppy->vel.z = 0.0f;
                greatFox->vel.z = 0.0f;
            }

            switch (gCsFrameCount) {
                case 618:
                    switch (gTeamShields[TEAM_ID_SLIPPY]) {
                        case -1:
                            Radio_PlayMessage(gMsg_ID_20339, RCID_ROB64);
                            break;
                        case 0:
                            Radio_PlayMessage(gMsg_ID_20345, RCID_ROB64);
                            break;
                        default:
                            Radio_PlayMessage(gMsg_ID_9428, RCID_SLIPPY);
                            break;
                    }
                    break;

                case 765:
                    switch (gTeamShields[TEAM_ID_PEPPY]) {
                        case -1:
                            Radio_PlayMessage(gMsg_ID_20338, RCID_ROB64);
                            break;
                        case 0:
                            Radio_PlayMessage(gMsg_ID_20344, RCID_ROB64);
                            break;
                        default:
                            Radio_PlayMessage(gMsg_ID_9429, RCID_PEPPY);
                            break;
                    }
                    break;

                case 911:
                    switch (gTeamShields[TEAM_ID_FALCO]) {
                        case -1:
                            Radio_PlayMessage(gMsg_ID_20337, RCID_ROB64);
                            break;
                        case 0:
                            Radio_PlayMessage(gMsg_ID_20340, RCID_ROB64);
                            break;
                        default:
                            Radio_PlayMessage(gMsg_ID_9430, RCID_FALCO);
                            break;
                    }
                    break;

                case 1080:
                    gShowLevelClearStatusScreen = true;
                    break;

                case 1240:
                    if (gTeamShields[TEAM_ID_FALCO] > 0) {
                        AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, falco->sfxSource, 0);
                        falco->fwork[29] = 5.0f;
                        falco->iwork[11] = 2;
                    }
                    break;

                case 1260:
                    if (gTeamShields[TEAM_ID_SLIPPY] > 0) {
                        AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, slippy->sfxSource, 0);
                        slippy->fwork[29] = 5.0f;
                        slippy->iwork[11] = 2;
                    }
                    break;

                case 1280:
                    if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                        AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, peppy->sfxSource, 0);
                        peppy->fwork[29] = 5.0f;
                        peppy->iwork[11] = 2;
                    }
                    gShowLevelClearStatusScreen = false;
                    break;

                case 1300:
                    AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, player->sfxSource, 0);
                    player->unk_190 = 2.0f;
                    player->unk_194 = 5.0f;
                    break;

                case 1350:
                    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 50);
                    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 50);
                    break;
            }

            if ((gCsFrameCount >= 1400)) {
                gFillScreenAlphaTarget = 255;
                gFillScreenAlphaStep = 16;
                if (gFillScreenAlpha == 255) {
                    player->state = PLAYERSTATE_NEXT;
                    player->csTimer = 0;
                    gFadeoutType = 4;
                    Audio_FadeOutAll(10);

                    // clang-format off
                    for (i = 0; i < 6; i++) { \
                        gSavedStarWolfTeamAlive[i] = gStarWolfTeamAlive[i];
                    }
                    // clang-format on

                    gLeveLClearStatus[LEVEL_FORTUNA] = Play_CheckMedalStatus(50) + 1;
                    Play_ClearObjectData();
                    break;
                }
            }

            if (gCsFrameCount > 1060) {
                Math_SmoothStepToF(D_ctx_80177A48, 300.0f, 0.02f, 1000.0f, 0.001f);
                Math_SmoothStepToF(&D_ctx_80177A48[1], -100.0f, 0.02f, 1000.0f, 0.001f);
            } else if (gCsFrameCount > 770) {
                Math_SmoothStepToF(D_ctx_80177A48, 600.0f, 0.02f, 1000.0f, 0.001f);
            } else {
                Math_SmoothStepToF(D_ctx_80177A48, 400.0f, 0.03f, 1000.0f, 0.001f);
            }

            Math_SmoothStepToF(&D_ctx_80177A48[5], D_ctx_80177A48[0], 0.01f, 1000.0f, 0.001f);
            Math_SmoothStepToF(&D_ctx_80177A48[7], D_ctx_80177A48[1], 0.01f, 1000.0f, 0.001f);

            if (gCsFrameCount > 1060) {
                Math_SmoothStepToF(&D_ctx_80177A48[2], -70.0f, 0.05f, 1000.0f, 0.001f);
            } else if (gCsFrameCount < 770) {
                Math_SmoothStepToF(&D_ctx_80177A48[2], 100.0f, 0.05f, 1000.0f, 0.001f);
            }

            Math_SmoothStepToF(&D_ctx_80177A48[6], D_ctx_80177A48[2], 0.01f, 1000.0f, 0.001f);

            if (gCsFrameCount < 1180) {
                Math_SmoothStepToF(&D_ctx_80177A48[8], 0.41f, 0.01f, 10.0f, 0.001f);
            } else {
                Math_SmoothStepToF(&D_ctx_80177A48[8], 0.0f, 0.001f, 1.0f, 0.0001f);
            }

            D_ctx_80177A48[4] += D_ctx_80177A48[8];

            if (D_ctx_80177A48[4] >= 360.0f) {
                D_ctx_80177A48[4] = D_ctx_80177A48[4] - 360.0f;
            }

            if (D_ctx_80177A48[4] < 0.0f) {
                D_ctx_80177A48[4] = D_ctx_80177A48[4] + 360.0f;
            }

            if (gCsFrameCount < 1300) {
                src.x = 0.0f;
                src.y = D_ctx_80177A48[7];
                src.z = D_ctx_80177A48[5];
                Matrix_Translate(gCalcMatrix, player->pos.x, 0.0f, player->pos.z + gPathProgress, MTXF_NEW);
                Matrix_RotateY(gCalcMatrix, -(D_ctx_80177A48[4] * M_DTOR), MTXF_APPLY);
                Matrix_MultVec3f(gCalcMatrix, &src, &dest);
                player->cam.eye.x = gCsCamEyeX = dest.x;
                player->cam.eye.y = gCsCamEyeY = dest.y;
                player->cam.eye.z = gCsCamEyeZ = dest.z;
            }

            if (gCsFrameCount >= 1240) {
                Math_SmoothStepToF(&falco->vel.z, 50.0f, 0.1f, 1000.0f, 0.001f);
            }
            if (gCsFrameCount >= 1260) {
                Math_SmoothStepToF(&slippy->vel.z, 50.0f, 0.1f, 1000.0f, 0.001f);
            }
            if (gCsFrameCount >= 1280) {
                Math_SmoothStepToF(&peppy->vel.z, 50.0f, 0.1f, 1000.0f, 0.001f);
            }
            if (gCsFrameCount >= 1300) {
                Math_SmoothStepToF(&player->baseSpeed, 50.0f, 0.1f, 1000.0f, 0.001f);
                Math_SmoothStepToF(&greatFox->vel.z, 40.0f, 0.1f, 1000.0f, 0.001f);
            }
            Math_SmoothStepToF(&gCsCamAtY, player->pos.y, 0.005f, 1000.0f, 0.0001f);

            player->cam.at.x = gCsCamAtX = player->pos.x;
            player->cam.at.y = gCsCamAtY;
            player->cam.at.z = gCsCamAtZ = player->pos.z - D_ctx_80177A48[6] + gPathProgress;
            break;
    }

    if (player->csState < 20) {
        switch (gCsFrameCount) {
            case 1020:
                gShowLevelClearStatusScreen = true;
                break;
            case 1220:
                gShowLevelClearStatusScreen = false;
                break;
        }
    }

    Matrix_RotateY(gCalcMatrix, (player->yRot_114 + player->rot.y + 180.0f) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -((player->xRot_120 + player->rot.x + player->aerobaticPitch) * M_DTOR), MTXF_APPLY);

    src.x = 0.0f;
    src.y = 0.0f;
    src.z = player->baseSpeed + player->boostSpeed;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

    player->vel.x = dest.x;
    player->vel.z = dest.z;
    player->vel.y = dest.y;
    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;
    player->pos.z += player->vel.z;
    player->trueZpos = player->pos.z;
    player->bankAngle = player->rot.z + player->zRotBank + player->zRotBarrelRoll;
}

void Fortuna_LoadLevelObjects(void) {
    s32 i;
    Actor* actor;
    Sprite* sprite;
    Scenery360* scenery360;
    FoBase* base = &gBosses[0];

    gLevelObjects = SEGMENTED_TO_VIRTUAL(gLevelObjectInits[gCurrentLevel]);

    for (scenery360 = &gScenery360[0], i = 0; i < 1000; i++) {
        if (gLevelObjects[i].id <= OBJ_INVALID) {
            break;
        }
        if (gLevelObjects[i].id < OBJ_SCENERY_MAX) {
            Scenery360_Initialize(scenery360);
            scenery360->obj.status = OBJ_ACTIVE;
            scenery360->obj.id = gLevelObjects[i].id;
            scenery360->obj.pos.x = gLevelObjects[i].xPos;
            scenery360->obj.pos.z = gLevelObjects[i].zPos1;
            scenery360->obj.pos.y = gLevelObjects[i].yPos;
            scenery360->obj.rot.y = gLevelObjects[i].rot.y;
            Object_SetInfo(&scenery360->info, scenery360->obj.id);
            scenery360++;
        }
    }

    for (actor = &gActors[20], i = 0; i < 1000; i++) {
        if (gLevelObjects[i].id <= OBJ_INVALID) {
            break;
        }
        if ((gLevelObjects[i].id >= OBJ_ACTOR_START) && (gLevelObjects[i].id < OBJ_ACTOR_MAX)) {
            Actor_Initialize(actor);
            actor->obj.status = OBJ_INIT;
            actor->obj.id = gLevelObjects[i].id;
            actor->obj.pos.x = gLevelObjects[i].xPos;
            actor->obj.pos.z = gLevelObjects[i].zPos1;
            actor->obj.pos.y = gLevelObjects[i].yPos;
            Object_SetInfo(&actor->info, actor->obj.id);
            actor++;
        }
    }

    for (sprite = &gSprites[0], i = 0; i < 1000; i++) {
        if (gLevelObjects[i].id <= OBJ_INVALID) {
            break;
        }
        if (gLevelObjects[i].id == OBJ_SPRITE_FO_POLE) {
            Sprite_Initialize(sprite);
            sprite->obj.status = OBJ_INIT;
            sprite->obj.id = gLevelObjects[i].id;
            sprite->obj.pos.x = gLevelObjects[i].xPos;
            sprite->obj.pos.z = gLevelObjects[i].zPos1;
            sprite->obj.pos.y = gLevelObjects[i].yPos;
            Object_SetInfo(&sprite->info, sprite->obj.id);
            sprite++;
        }
    }

    Boss_Initialize(base);
    base->obj.status = OBJ_INIT;
    base->obj.pos.x = 0.0f;
    base->obj.pos.y = 0.0f;
    base->obj.pos.z = 0.0f;
    base->obj.id = OBJ_BOSS_FO_BASE;
    Object_SetInfo(&base->info, base->obj.id);
}
