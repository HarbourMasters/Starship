/*
 * File: fox_sx.c
 * System: Sector Z
 * Description: Level: Sector Z
 */

#include "global.h"
#include "assets/ast_sector_z.h"

#define MISSILE_TARGET_X (4)
#define MISSILE_TARGET_Y (5)
#define MISSILE_TARGET_Z (6)

typedef enum SzActors {
    /* 0 */ SZ_GREAT_FOX,
    /* 10 */ SZ_MISSILE_CENTER = AI360_ENEMY,
    /* 11 */ SZ_MISSILE_LEFT,
    /* 12 */ SZ_MISSILE_RIGHT,
    /* 13 */ SZ_ESCORT_1,
    /* 14 */ SZ_ESCORT_2,
    /* 15 */ SZ_ESCORT_3,
    /* 16 */ SZ_ESCORT_4,
} SzActors;

s32 sMissileDestroyCount;
bool sKattEnabled;

Vec3f sMissileWaveInitPos[] = {
    { 0.0f, 0.0f, 35000.0f },
    { -2000.0f, 0.0f, 35000.0f },
    { 2000.0f, 0.0f, 35000.0f },
};

// Relative to the missile
Vec3f sMissileEscortOffsetPos[] = {
    { -700.0f, -200.0f, 200.0f },
    { 500.0f, 200.0f, -300.0f },
    { 300.0f, -300.0f, -200.0f },
    { 200.0f, 400.0f, 500.0f },
};

void SectorZ_MissileExplode(ActorAllRange* this, bool shotDown) {
    s32 i;

    gScreenFlashTimer = 8;

    Object_Kill(&this->obj, this->sfxSource);
    Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_MS_EXPLOSION_S);

    for (i = 0; i < 20; i++) {
        Effect_Effect357_Spawn50(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 1.0f);
        func_effect_80079618(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 1.0f);
    }

    Effect386_Spawn1(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 0.0f, 0.0f, 0.0f, 20.0f, 30);
    Effect_Effect384_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 20.0f, 5);

    if (shotDown) {
        sMissileDestroyCount++;
        if ((sMissileDestroyCount >= 6) &&
            ((gPlayer[0].state == PLAYERSTATE_ACTIVE) || (gPlayer[0].state == PLAYERSTATE_U_TURN))) {
            gCsFrameCount = 0;
            gPlayer[0].state = PLAYERSTATE_LEVEL_COMPLETE;
            gPlayer[0].csState = 1000;
            gActors[SZ_GREAT_FOX].state = 6;
            gPlayer[0].csTimer = 30;
            AUDIO_PLAY_SFX(NA_SE_GREATFOX_ENGINE, gActors[SZ_GREAT_FOX].sfxSource, 0);
            AUDIO_PLAY_SFX(NA_SE_GREATFOX_BURNER, gActors[SZ_GREAT_FOX].sfxSource, 0);
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 1);
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 1);
        }

        // Check for Katt's appearance
        if ((sMissileDestroyCount == 3) && (gLeveLClearStatus[LEVEL_ZONESS] != 0)) {
            gAllRangeSpawnEvent = gAllRangeEventTimer + 110;
        }
    }
}

void SectorZ_FireSmokeEffectSetup(EffectFireSmoke* this, f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel,
                                  f32 scale) {
    Effect_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_EFFECT_FIRE_SMOKE_1;

    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;

    this->vel.x = xVel;
    this->vel.y = yVel;
    this->vel.z = zVel;

    this->scale2 = scale;
    this->scale1 = 0.5f;

    this->unk_4C = 2;
    this->obj.rot.z = RAND_FLOAT(360.0f);

    Object_SetInfo(&this->info, this->obj.id);

    this->unk_44 = 255;
    this->unk_46 = 2;
}

void SectorZ_FireSmokeEffectSpawn(f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 scale) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == 0) {
            SectorZ_FireSmokeEffectSetup(&gEffects[i], xPos, yPos, zPos, xVel, yVel, zVel, scale);
            break;
        }
    }
}

void SectorZ_Missile_Update(ActorAllRange* this) {
    // clang-format off
    f32 x;
    f32 y;
    f32 z;
    f32 xPitch;
    f32 yPitch;

    this->iwork[9]++;

    PRINTF("MISS_MOVE_TIME %d\n", this->iwork[9]);

    switch (this->iwork[9]) {
        case 600:
            Radio_PlayMessage(gMsg_ID_16080, RCID_ROB64);
            break;

        case 1000:
            Radio_PlayMessage(gMsg_ID_16085, RCID_ROB64);
            break;

        case 1200:
            Radio_PlayMessage(gMsg_ID_16090, RCID_ROB64);
            break;
    }

    /* Leftover from a test or commented out code? */
    /* =========================================== */
    x = gBosses[SZ_GREAT_FOX].obj.pos.x - this->obj.pos.x;
    y = gBosses[SZ_GREAT_FOX].obj.pos.y - this->obj.pos.y; // Optimized out?
    z = gBosses[SZ_GREAT_FOX].obj.pos.z - this->obj.pos.z;
    SIN_DEG(gGameFrameCount);
    if (x && z) {} //! FAKE
    /* =========================================== */

    if (this->aiType < 100) {
        if (x && z) {} //! FAKE
        z = fabsf(this->fwork[6] - this->obj.pos.z); //! FAKE

        // Escorts wooble movement
        xPitch = SIN_DEG((this->index * 45) + gGameFrameCount) * 5000.0f;
        yPitch = COS_DEG((this->index * 45) + (gGameFrameCount * 2)) * 5000.0f;
    } else {
        // For missile
        xPitch = yPitch = 0.0f;
    }

    this->fwork[MISSILE_TARGET_X] = gBosses[SZ_GREAT_FOX].obj.pos.x + xPitch + 400.0f;
    this->fwork[MISSILE_TARGET_Y] = gBosses[SZ_GREAT_FOX].obj.pos.y + yPitch + 100.0f;
    this->fwork[MISSILE_TARGET_Z] = gBosses[SZ_GREAT_FOX].obj.pos.z;

    this->fwork[3] = 1.4f;

    // Missile hit check
    if ((fabsf(this->fwork[MISSILE_TARGET_X] - this->obj.pos.x) < 800.0f) &&
        (fabsf(this->fwork[MISSILE_TARGET_Y] - this->obj.pos.y) < 800.0f) &&
        (fabsf(this->fwork[MISSILE_TARGET_Z] - this->obj.pos.z) < 800.0f)) {
        SectorZ_MissileExplode(this, false);
        gCameraShake = 25;
        gBosses[SZ_GREAT_FOX].dmgType = DMG_MISSILE;
        if ((gPlayer[0].state == PLAYERSTATE_ACTIVE) || (gPlayer[0].state == PLAYERSTATE_U_TURN)) {
            gPlayer[0].state = PLAYERSTATE_LEVEL_COMPLETE;
            gPlayer[0].csState = 0;
            gActors[SZ_GREAT_FOX].state = -31072;
            return;
        }
    }

    s32 bugFixCond;
    if (CVarGetInteger("gSzMissileBug", 0) == 1) {
        bugFixCond = 0;
    } else {
        bugFixCond = (gPlayer[0].state == PLAYERSTATE_GFOX_REPAIR);
    }

    // Level complete trigger check
    if (((fabsf(this->fwork[MISSILE_TARGET_Z] - this->obj.pos.z) < 2000.0f) &&
         (((gPlayer[0].cam.eye.z < 0.0f) || (D_edisplay_801615D0.y < 0.0f)) ||
          bugFixCond)) &&
        (((gPlayer[0].state == PLAYERSTATE_ACTIVE) || bugFixCond) ||
         (gPlayer[0].state == PLAYERSTATE_U_TURN))) {
        gPlayer[0].state = PLAYERSTATE_LEVEL_COMPLETE;
        gPlayer[0].csState = 100;
        gActors[SZ_GREAT_FOX].state = -31072;
    }
    // clang-format on
}

void SectorZ_SpawnMissile(ActorAllRange* this, s32 missileWaveIdx) {
    Actor_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_ACTOR_ALLRANGE;
    this->aiType = AI360_MISSILE;

    this->obj.pos.x = sMissileWaveInitPos[missileWaveIdx].x;
    this->obj.pos.y = sMissileWaveInitPos[missileWaveIdx].y;
    this->obj.pos.z = sMissileWaveInitPos[missileWaveIdx].z;

    this->state = 5;
    this->rot_0F4.y = 180.0f;

    Object_SetInfo(&this->info, this->obj.id);

    this->health = 250;
    this->info.drawType = 2;
    this->info.hitbox = SEGMENTED_TO_VIRTUAL(aSZMissileHitbox);
    this->fwork[1] = 25.0f;
    this->fwork[29] = 2.0f;

    AUDIO_PLAY_SFX(NA_SE_EN_PUNCH_ENGINE, this->sfxSource, 4);
}

// Enemies that follow the missile
void SectorZ_SpawnMissileEscort(ActorAllRange* this, s32 enemyIndex) {
    Actor_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_ACTOR_ALLRANGE;
    this->aiType = enemyIndex + AI360_ENEMY + 3;

    this->obj.pos.x = gActors[SZ_MISSILE_CENTER].obj.pos.x + sMissileEscortOffsetPos[enemyIndex].x;
    this->obj.pos.y = gActors[SZ_MISSILE_CENTER].obj.pos.y + sMissileEscortOffsetPos[enemyIndex].y;
    this->obj.pos.z = gActors[SZ_MISSILE_CENTER].obj.pos.z + sMissileEscortOffsetPos[enemyIndex].z;

    this->state = 5;
    this->rot_0F4.y = 180.0f;

    Object_SetInfo(&this->info, this->obj.id);

    this->fwork[1] = gActors[SZ_MISSILE_CENTER].fwork[1];
    this->iwork[11] = 1;
}

void SectorZ_Katt_Init(void) {
    ActorAllRange* katt = &gActors[AI360_KATT];

    Actor_Initialize(katt);
    katt->obj.status = OBJ_ACTIVE;
    katt->obj.id = OBJ_ACTOR_ALLRANGE;

    katt->obj.pos.x = 0.0f;
    katt->obj.pos.y = 4500.0f;
    katt->obj.pos.z = 30000.0f;

    katt->aiType = AI360_KATT;
    katt->aiIndex = AI360_ENEMY + 2;
    katt->health = 10000;
    katt->rot_0F4.y = 180.0f;
    katt->state = 0;
    katt->timer_0BC = 250;
    katt->rot_0F4.x = -20.0f;
    katt->iwork[11] = 1;
    katt->obj.rot.z = 90.0f;

    Object_SetInfo(&katt->info, katt->obj.id);

    katt->info.targetOffset = 0.0f;

    AUDIO_PLAY_SFX(NA_SE_EN_ENGINE_01, katt->sfxSource, 4);
}

void SectorZ_KattCutscene(ActorCutscene* this) {
    if (gAllRangeEventTimer == gAllRangeSpawnEvent) {
        SectorZ_Katt_Init();
        gCsFrameCount = 0;

        this->timer_0BC = 400;
        this->state = 3;

        gPlayer[0].state = PLAYERSTATE_STANDBY;

        Audio_PlayFanfare(NA_BGM_KATT, 20, 10, 10);
        AllRange_ClearRadio();

        gPlayer[0].cam.eye.x = 250.0f;
        gPlayer[0].cam.eye.y = 2500.0f;
        gPlayer[0].cam.eye.z = 25000.0f;

        gPlayer[0].cam.at.x = gActors[8].obj.pos.x;
        gPlayer[0].cam.at.y = gActors[8].obj.pos.y;
        gPlayer[0].cam.at.z = gActors[8].obj.pos.z;

        sKattEnabled = true;
    }
}

void SectorZ_EnemyUpdate(ActorAllRange* this) {
    s32 i;
    Vec3f src;
    Vec3f dest;
    ActorAllRange* actor;

    if (gAllRangeEventTimer >= 0) {
        if (gTeamShields[AI360_FALCO] > 0) {
            if (gActors[AI360_FALCO].iwork[2] == AI360_FOX) {
                if (gActors[AI360_ENEMY].obj.status == 2) {
                    if (gActors[AI360_FALCO].aiIndex != AI360_ENEMY) {
                        Radio_PlayMessage(gMsg_ID_16040, RCID_FALCO);
                    }
                    gActors[AI360_FALCO].aiIndex = AI360_ENEMY;
                } else {
                    gActors[AI360_FALCO].aiIndex = AI360_ENEMY + 3;
                }
            } else {
                gActors[AI360_FALCO].aiIndex = -1;
            }
        }

        if (gTeamShields[AI360_PEPPY] > 0) {
            if (gActors[AI360_PEPPY].iwork[2] == AI360_FOX) {
                if (gActors[AI360_ENEMY + 2].obj.status == 2) {
                    if (gActors[AI360_PEPPY].aiIndex != AI360_ENEMY + 2) {
                        Radio_PlayMessage(gMsg_ID_16046, RCID_PEPPY);
                    }
                    gActors[AI360_PEPPY].aiIndex = AI360_ENEMY + 2;
                } else {
                    gActors[AI360_PEPPY].aiIndex = AI360_ENEMY + 5;
                }
            } else {
                gActors[AI360_PEPPY].aiIndex = -1;
            }
        }

        if (sKattEnabled) {
            if (gActors[SZ_MISSILE_LEFT].obj.status == 2) {
                if (gActors[8].aiIndex != AI360_ENEMY + 1) {
                    Radio_PlayMessage(gMsg_ID_16135, RCID_KATT);
                }
                gActors[AI360_KATT].aiIndex = AI360_ENEMY + 1;
            } else {
                gActors[AI360_KATT].aiIndex = -1;
            }
        } else if (gTeamShields[AI360_SLIPPY] > 0) {
            if (gActors[AI360_SLIPPY].iwork[2] == AI360_FOX) {
                if (gActors[SZ_MISSILE_LEFT].obj.status == 2) {
                    if (gActors[AI360_SLIPPY].aiIndex != AI360_ENEMY + 1) {
                        Radio_PlayMessage(gMsg_ID_16047, RCID_SLIPPY);
                    }
                    gActors[AI360_SLIPPY].aiIndex = AI360_ENEMY + 1;
                } else {
                    gActors[AI360_SLIPPY].aiIndex = AI360_ENEMY + 4;
                }
            } else {
                gActors[AI360_SLIPPY].aiIndex = -1;
            }
        }
    }

    if (gAllRangeEventTimer == 100) {
        Radio_PlayMessage(gMsg_ID_16030, RCID_FALCO);
    }

    if (((this->timer_0C0 == 0) && (gPlayer[0].state != PLAYERSTATE_STANDBY)) &&
        ((gAllRangeEventTimer < 200) || ((gAllRangeEventTimer > 4000) && (gAllRangeEventTimer < 4200)))) {
        this->timer_0C0 = 5;

        actor = &gActors[SZ_ESCORT_1];

        src.x = 0.0f;
        src.y = 0.0f;
        src.z = -17000.0f;

        for (i = 0; i < 20; i++, actor++) {
            if (actor->obj.status == 0) {
                Actor_Initialize(actor);

                actor->obj.status = OBJ_ACTIVE;
                actor->obj.id = OBJ_ACTOR_ALLRANGE;

                Matrix_RotateY(gCalcMatrix, (this->counter_04E * 18.0f) * M_DTOR, MTXF_NEW);
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

                actor->obj.pos.x = dest.x;
                actor->obj.pos.y = RAND_FLOAT(1000.0f) + 300.0f;
                actor->obj.pos.z = dest.z;

                actor->rot_0F4.y = this->counter_04E * 18.0f;
                actor->state = 3;
                actor->aiType = i + AI360_ENEMY + 3;
                actor->aiIndex = -1;

                if (gAllRangeEventTimer >= 0) {
                    if (((i + 13) == 23) || ((i + 13) == 24)) {
                        actor->aiIndex = AI360_SLIPPY;
                        actor->state = 2;
                    }
                    if ((i + 13) == 25) {
                        actor->aiIndex = AI360_FOX;
                        actor->state = 2;
                    }
                    if (((i + 13) == 26) || ((i + 13) == 27)) {
                        actor->aiIndex = AI360_PEPPY;
                        actor->state = 2;
                    }
                    if ((i + 13) == 28) {
                        actor->aiIndex = AI360_FALCO;
                        actor->state = 2;
                    }
                }
                actor->health = 24;
                actor->iwork[11] = 1;
                actor->itemDrop = DROP_SILVER_RING_50p;
                actor->timer_0C2 = 30;
                Object_SetInfo(&actor->info, actor->obj.id);
                AUDIO_PLAY_SFX(NA_SE_EN_ENGINE_01, actor->sfxSource, 4);
                this->counter_04E++;
                break;
            }
        }
    }

    switch (gAllRangeEventTimer) {
        case 5850:
            Radio_PlayMessage(gMsg_ID_16110, RCID_ROB64);
            break;

        case 6000:
            SectorZ_SpawnMissile(&gActors[SZ_MISSILE_RIGHT], 2);
            SectorZ_SpawnMissile(&gActors[SZ_MISSILE_LEFT], 1);
            SectorZ_SpawnMissile(&gActors[SZ_MISSILE_CENTER], 0);
            gRadarMissileAlarmTimer = 580;
            break;

        case 3850:
            Radio_PlayMessage(gMsg_ID_16100, RCID_ROB64);
            break;

        case 4000:
            SectorZ_SpawnMissile(&gActors[SZ_MISSILE_LEFT], 1);
            SectorZ_SpawnMissile(&gActors[SZ_MISSILE_CENTER], 0);
            gRadarMissileAlarmTimer = 580;
            break;

        case 2000:
            gRadarMissileAlarmTimer = 490;
            SectorZ_SpawnMissile(&gActors[SZ_MISSILE_CENTER], 0);

            gActors[SZ_MISSILE_CENTER].fwork[1] = 10.0f;
            gActors[SZ_MISSILE_CENTER].obj.pos.z = 25000.0f;

            SectorZ_SpawnMissileEscort(&gActors[SZ_ESCORT_1], 0);
            SectorZ_SpawnMissileEscort(&gActors[SZ_ESCORT_2], 1);
            SectorZ_SpawnMissileEscort(&gActors[SZ_ESCORT_3], 2);
            SectorZ_SpawnMissileEscort(&gActors[SZ_ESCORT_4], 3);

            gPlayer[0].state = PLAYERSTATE_STANDBY;

            this->state = 10;
            this->fwork[10] = 0.0f;

            gPlayer[0].camRoll = 15.0f;

            gPlayer[0].cam.eye.x = gActors[SZ_MISSILE_CENTER].obj.pos.x - 25000.0f;
            gPlayer[0].cam.eye.y = gActors[SZ_MISSILE_CENTER].obj.pos.y;
            gPlayer[0].cam.eye.z = gActors[SZ_MISSILE_CENTER].obj.pos.z;

            gPlayer[0].cam.at.x = gActors[SZ_MISSILE_CENTER].obj.pos.x;
            gPlayer[0].cam.at.y = gActors[SZ_MISSILE_CENTER].obj.pos.y;
            gPlayer[0].cam.at.z = gActors[SZ_MISSILE_CENTER].obj.pos.z;

            this->timer_0BC = 10000;
            gFillScreenAlpha = gFillScreenAlphaTarget = 255;
            gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
            AUDIO_PLAY_BGM(NA_BGM_BOSS_SZ);
            break;
    }

    ActorAllRange_UpdateEnemyEvents(this);
    SectorZ_KattCutscene(this);
}

bool SectorZ_GFoxArwingRepair(Player* player) {
    // clang-format off
    if (player->state == PLAYERSTATE_ACTIVE) {
        if ((player->yRot_114 > 30.0f) && 
            (player->yRot_114 < 150.0f) && 
            (fabsf(player->pos.x - 1270.0f) < 450.0f) &&
            (fabsf(player->pos.y - 265.0f) < 100.0f) && 
            (fabsf(player->trueZpos) < 172.0f)) {
            player->state = PLAYERSTATE_GFOX_REPAIR;
            player->csState = 0;
            gActors[SZ_GREAT_FOX].state = 20;
            gAllRangeEventTimer--;
            return true;
        }
    }
    return false;
    // clang-format on
}

void SectorZ_UpdateEvents(ActorAllRange* this) {
    s32 i;
    Player* player;
    ActorCutscene* katt;
    s32 pad;
    f32 D_i4_8019F514[5] = { -200.0f, -100.0f, -0.0f, 100.0f, 200.0f }; // unused

    player = &gPlayer[0];

    switch ((s32) this->state) {
        case 0:
            sKattEnabled = sMissileDestroyCount = 0;
            gSzMissileR = 63.0f;
            gSzMissileG = 255.0f;
            gSzMissileB = 158.0f;
            gProjectFar = 30000.0f;
            gAllRangeEventTimer = 0;
            this->state = 2;
            if (gAllRangeCheckpoint != 0) {
                gHitCount = gSavedHitCount;
            }
            gAllRangeSpawnEvent = 1000000;

        case 2:
            if (!SectorZ_GFoxArwingRepair(player)) {
                SectorZ_EnemyUpdate(this);

                switch (this->timer_0BE) {
                    case 548:
                        Radio_PlayMessage(gMsg_ID_16050, RCID_ROB64);
                        break;

                    case 385:
                        Radio_PlayMessage(gMsg_ID_16055, RCID_ROB64);
                        break;

                    case 235:
                        Radio_PlayMessage(gMsg_ID_16060, RCID_FOX);
                        break;

                    case 130:
                        break;
                }
            }
            break;

        case 20:
            gAllRangeEventTimer--;
            break;

        case 3:
            katt = &gActors[AI360_KATT];

            gCsFrameCount++;
            if (gCsFrameCount == 3) {
                Effect_Effect393_Spawn(katt->obj.pos.x, katt->obj.pos.y, katt->obj.pos.z, 30.0f);
            }
            player->cam.eye.x += katt->vel.x * 0.23f;
            player->cam.eye.y += katt->vel.y * 0.23f;
            player->cam.eye.z += katt->vel.z * 0.23f;

            Math_SmoothStepToF(&player->cam.at.x, katt->obj.pos.x, 1.0f, 20000.0f, 0);
            Math_SmoothStepToF(&player->cam.at.y, katt->obj.pos.y, 1.0f, 20000.0f, 0);
            Math_SmoothStepToF(&player->cam.at.z, katt->obj.pos.z, 1.0f, 20000.0f, 0);
            Math_SmoothStepToF(&player->camRoll, 0, 1.0f, 1000.0f, 0);

            switch (this->timer_0BC) {
                case 370:
                    Radio_PlayMessage(gMsg_ID_16120, RCID_KATT);
                    break;

                case 261:
                    Radio_PlayMessage(gMsg_ID_16125, RCID_FALCO);
                    break;

                case 140:
                    gRadioState = 0;
                    Radio_PlayMessage(gMsg_ID_16130, RCID_KATT);
                    break;

                case 260:
                    katt->fwork[7] = 360.0f;
                    katt->fwork[8] = 0.0f;
                    break;

                case 230:
                    katt->fwork[7] = 0.0f;
                    katt->fwork[8] = 359.999f;
                    break;
            }

            if (this->timer_0BC == 70) {
                this->state = 2;
                player->state = PLAYERSTATE_ACTIVE;
                Camera_Update360(player, true);
                player->unk_014 = 0.0f;
            }
            break;

        case 6:
            gActors[1].aiIndex = AI360_FOX;
            gActors[1].state = 2;
            gActors[2].aiIndex = AI360_FOX;
            gActors[2].state = 2;
            gActors[3].aiIndex = AI360_FOX;
            gActors[3].state = 2;

            for (i = 10; i < ARRAY_COUNT(gActors); i++) {
#ifdef AVOID_UB
                if (gActors[i].obj.status == OBJ_FREE) {
                    continue;
                }
#endif
                gActors[i].aiIndex = -1;
                gActors[i].state = 3;
            }
            break;

        case 10:
            gFillScreenAlpha = gFillScreenAlphaTarget = 0;
            switch (this->timer_0BC) {
                case 9800:
                    AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, gActors[SZ_MISSILE_CENTER].sfxSource, 0);
                    gActors[SZ_MISSILE_CENTER].fwork[29] = 12.0f;
                    break;

                case 9780:
                    gActors[SZ_ESCORT_1].aiIndex = -1;
                    gActors[SZ_ESCORT_1].state = 3;
                    break;

                case 9740:
                    gActors[SZ_ESCORT_2].aiIndex = -1;
                    gActors[SZ_ESCORT_2].state = 3;
                    break;

                case 9730:
                    gActors[SZ_ESCORT_3].aiIndex = -1;
                    gActors[SZ_ESCORT_3].state = 3;
                    break;

                case 9710:
                    gActors[SZ_ESCORT_4].aiIndex = -1;
                    gActors[SZ_ESCORT_4].state = 3;
                    break;
            }

            Math_SmoothStepToF(&player->cam.at.x, gActors[SZ_MISSILE_CENTER].obj.pos.x, 0.2, 500.0f, 0.0f);
            Math_SmoothStepToF(&player->cam.at.y, gActors[SZ_MISSILE_CENTER].obj.pos.y, 0.2, 500.0f, 0.0f);
            Math_SmoothStepToF(&player->cam.at.z, gActors[SZ_MISSILE_CENTER].obj.pos.z, 0.2, 500.0f, 0.0f);

            if (this->timer_0BC < 9800) {
                Math_SmoothStepToF(&gActors[SZ_MISSILE_CENTER].fwork[1], 80.0f, 0.1, 10.0f, 0);
                Math_SmoothStepToF(&gActors[SZ_MISSILE_CENTER].fwork[29], 3.0f, 0.1, 1.0f, 0);
            } else {
                Math_SmoothStepToF(&this->fwork[10], 700.0f, 1, 5.0f, 0.0f);
                Math_SmoothStepToF(&player->cam.eye.x, gActors[SZ_MISSILE_CENTER].obj.pos.x - 300.0f, 0.07f,
                                   this->fwork[10], 0);
                Math_SmoothStepToF(&player->cam.eye.y, gActors[SZ_MISSILE_CENTER].obj.pos.y, 0.07f, this->fwork[10], 0);
                Math_SmoothStepToF(&player->cam.eye.z, gActors[SZ_MISSILE_CENTER].obj.pos.z + 500.0f, 0.05f, 50.0f, 0);
                Math_SmoothStepToF(&gActors[SZ_MISSILE_CENTER].fwork[29], 2.0f, 0.1f, 1.0f, 0);
            }

            if (this->timer_0BC < 9680) {
                this->state = 2;
                player->state = PLAYERSTATE_ACTIVE;
                Camera_Update360(player, true);
                player->unk_014 = 0.0f;
                gActors[SZ_MISSILE_CENTER].fwork[1] = 25.0f;
                gActors[SZ_MISSILE_CENTER].fwork[29] = 5.0f;
                gActors[SZ_MISSILE_CENTER].obj.pos.z = 35000.0f;
                gActors[SZ_MISSILE_CENTER].iwork[9] = 0;
                gPlayer[0].camRoll = 0.0f;
                this->timer_0BE = 550;
            }
            break;

        case 100000:
            break;
    }

    if ((gGameFrameCount & 0x18) == 0) {
        Math_SmoothStepToF(&gSzMissileR, 63.0f, 1.0f, 9.450001f, 0);
        Math_SmoothStepToF(&gSzMissileG, 255.0f, 1.0f, 35.25f, 0);
        Math_SmoothStepToF(&gSzMissileB, 158.0f, 1.0f, 21.6f, 0);
    } else {
        Math_SmoothStepToF(&gSzMissileR, 0.0f, 1.0f, 3.15f, 0);
        Math_SmoothStepToF(&gSzMissileG, 20.0f, 1.0f, 11.75f, 0);
        Math_SmoothStepToF(&gSzMissileB, 14.0f, 1.0f, 7.2000003f, 0);
    }
}

Vec3f sInitialCsObjectPos[] = {
    { 1000.0f, 1000.0f, 1000.0f },  { 0.0f, -700.0f, 1500.0f },       { 2000.0f, -500.0f, 2500.0f },
    { -500.0f, 500.0f, -3000.0f },  { -2000.0f, -1000.0f, -1000.0f }, { -1000.0f, 1700.0f, -1500.0f },
    { 2000.0f, 2500.0f, -2500.0f },
};

// Objects around the great fox during the initial cutscene
void SectorZ_CsObjectInit(void) {
    ActorCutscene* actor = &gActors[1];
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sInitialCsObjectPos); i++, actor++) {
        Actor_Initialize(actor);
        actor->obj.status = OBJ_INIT;
        actor->obj.id = OBJ_ACTOR_CUTSCENE;
        actor->animFrame = ACTOR_CS_SZ_SPACE_JUNK;
        actor->obj.pos.x = sInitialCsObjectPos[i].x;
        actor->obj.pos.y = sInitialCsObjectPos[i].y;
        actor->obj.pos.z = sInitialCsObjectPos[i].z;
        actor->obj.rot.y = RAND_FLOAT(360.0f);
        actor->vel.x = 5.0f;
        Object_SetInfo(&actor->info, actor->obj.id);
    }
}

void SectorZ_CsGreatFoxInit(void) {
    ActorCutscene* greatFox = &gActors[SZ_GREAT_FOX];

    Actor_Initialize(greatFox);
    greatFox->obj.status = OBJ_INIT;
    greatFox->obj.id = OBJ_ACTOR_CUTSCENE;
    greatFox->obj.pos.x = 5000.0f;
    greatFox->obj.pos.y = 0.0f;
    greatFox->obj.pos.z = 0.0f;
    greatFox->obj.rot.y = 270.0f;
    greatFox->animFrame = ACTOR_CS_GREAT_FOX;
    greatFox->vel.x = -20.0f;
    Object_SetInfo(&greatFox->info, greatFox->obj.id);
    AUDIO_PLAY_SFX(NA_SE_GREATFOX_ENGINE, greatFox->sfxSource, 0);
}

Vec3f sInitialCsEnemyPos[] = {
    { 150.0f, 150.0f, 50.0f }, { -150.0f, -150.0f, 50.0f }, { -150.0f, 150.0f, 50.0f }, { 150.0f, -150.0f, 50.0f }
};

f32 sInitialCsEnemyZrot[] = { -30.0f, 20.0f, 30.0f, -40.0f };

// Enemies during the initial cutscene
void SectorZ_CsEnemies(ActorCutscene* this, s32 index) {
    Actor_Initialize(this);
    this->obj.status = OBJ_ACTIVE;
    this->obj.id = OBJ_ACTOR_CUTSCENE;

    this->obj.pos.x = gPlayer[0].cam.eye.x + sInitialCsEnemyPos[index].x;
    this->obj.pos.y = gPlayer[0].cam.eye.y + sInitialCsEnemyPos[index].y;
    this->obj.pos.z = gPlayer[0].cam.eye.z + sInitialCsEnemyPos[index].z;

    this->vel.z = -30.0f;
    this->vel.y = -10.0f;

    this->obj.rot.y = 180.0f;
    this->obj.rot.x = 10.0f;
    this->obj.rot.z = sInitialCsEnemyZrot[index];

    this->animFrame = ACTOR_CS_SZ_INVADER;
    this->iwork[11] = 1;
    Object_SetInfo(&this->info, this->obj.id);
    AUDIO_PLAY_SFX(NA_SE_EN_ENGINE_01, this->sfxSource, 4);
}

Vec3f sTeamCsOffsetPos[] = {
    { 200.0f, 0.0f, 0.0f }, { 200.0f, 0.0f, 0.0f }, { 200.0f, 0.0f, 0.0f }, { 200.0f, 0.0f, 0.0f }
};

void SectorZ_CsTeamInit(ActorCutscene* this, s32 index) {
    ActorCutscene* greatFox = &gActors[SZ_GREAT_FOX];

    Actor_Initialize(this);
    this->obj.status = OBJ_ACTIVE;
    this->obj.id = OBJ_ACTOR_CUTSCENE;

    this->obj.pos.x = greatFox->obj.pos.x + sTeamCsOffsetPos[index].x;
    this->obj.pos.y = greatFox->obj.pos.y - 500.0f;
    this->obj.pos.z = greatFox->obj.pos.z + sTeamCsOffsetPos[index].z;

    this->vel.x = -gArwingSpeed;
    this->obj.rot.y = 270.0f;

    Object_SetInfo(&this->info, this->obj.id);

    if (CVarGetInteger("gTeamFaces", 1) == 1) {
        // @port: Setup team faces
        switch (index) {
            case 0: // Slippy
                this->iwork[14] = index + 3;
                break;
            case 1: // Falco
                this->iwork[14] = index + 1;
                break;
            case 2: // Peppy
                this->iwork[14] = index + 2;
                break;
        }
    }

    AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, this->sfxSource, 4);
    AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, this->sfxSource, 0);

    this->fwork[29] = 5.0f;
}

// Relative to the player
Vec3f sTeamSetupOffsetPos[] = {
    { 0.0f, 20000.0f, 0.0f }, { -1000.0f, 100.0f, 500.0f }, { -1300.0f, -50.0f, 0.0f }, { -1600.0f, 50.0f, -500.0f }
};

void SectorZ_TeamSetup(void) {
    TeamId i;
    ActorAllRange* team;

    for (i = TEAM_ID_FOX, team = &gActors[0]; i <= TEAM_ID_PEPPY; i++, team++) {
        if ((i <= TEAM_ID_FOX) || (gTeamShields[i] > 0)) {
            Actor_Initialize(team);
            team->obj.status = OBJ_ACTIVE;
            team->obj.id = OBJ_ACTOR_ALLRANGE;

            Object_SetInfo(&team->info, team->obj.id);

            if (i == TEAM_ID_FOX) {
                team->aiType = AI360_EVENT_HANDLER;
            } else {
                team->obj.pos.x = gPlayer[0].pos.x + sTeamSetupOffsetPos[i].x;
                team->obj.pos.y = gPlayer[0].pos.y + sTeamSetupOffsetPos[i].y;
                team->obj.pos.z = gPlayer[0].pos.z + sTeamSetupOffsetPos[i].z;
                team->aiType = i;
                team->state = 2;
                team->rot_0F4.y = 270.0f;
                team->health = 255;
                team->iwork[11] = 1;

                AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, team->sfxSource, 4);

                team->info.hitbox = SEGMENTED_TO_VIRTUAL(gTeamHitbox);
                team->info.unk_16 = 0;
                team->info.targetOffset = 0.0f;
            }
        }
    }
}

void SectorZ_LevelStart(Player* player) {
    s32 i;
    s32 j;
    Vec3f src;
    Vec3f dest;
    ActorCutscene* greatFox = &gActors[SZ_GREAT_FOX];

    gAllRangeEventTimer = 0;

    switch (player->csState) {
        case 0:
            gCsFrameCount = 0;

            player->csState++;

            SectorZ_CsGreatFoxInit();
            SectorZ_CsObjectInit();

            gCsCamEyeX = 0.0f;
            gCsCamEyeY = 0.0f;
            gCsCamEyeZ = 6000.0f;
            gCsCamAtX = 2500.0f;
            gCsCamAtY = 0.0f;
            gCsCamAtZ = 0.0f;
            D_ctx_80177A48[0] = 1.0f;

            player->draw = false;
            player->baseSpeed = 0.0f;
            player->camRoll = -20.0f;

            gProjectFar = 30000.0f;

        case 1:
            if (gCsFrameCount < 7) {
                gFillScreenAlpha = 255;
            }

            gCsCamAtX -= 10.0f;
            gCsCamEyeZ -= 7.0f;

            if (gCsFrameCount == 320) {
                player->csState = 2;
                greatFox->vel.x = -10.0f;
                greatFox->obj.pos.x = 1000.0f;
                gCsCamEyeX = 0.0f;
                gCsCamEyeY = 0.0f;
                gCsCamEyeZ = 17000.0f;
                gCsCamAtX = 0.0f;
                gCsCamAtY = 0.0f;
                gCsCamAtZ = 0.0f;
                gFillScreenAlpha = 255;
            }
            break;

        case 2:
            gFillScreenAlpha = 0;
            player->camRoll += 0.05f;

            for (i = 30; i < 34; i++) {
                Math_SmoothStepToF(&gActors[i].vel.x, -5.0f, 0.1f, 0.1, 0.0f);
                Math_SmoothStepToF(&gActors[i].vel.y, 5.0f, 0.1f, 0.1, 0.0f);
                Math_SmoothStepToF(&gActors[i].obj.rot.x, -10.0f, 0.1f, 0.2f, 0.0f);
                Math_SmoothStepToF(&gActors[i].obj.rot.z, 0.0f, 0.1f, 0.3f, 0.0f);
            }

            if (gCsFrameCount == 500) {
                gCsFrameCount = 520;

                player->csState++;

                greatFox->vel.x = 0.0f;

                greatFox->obj.pos.z = 0.0f;
                greatFox->obj.pos.y = 0.0f;
                greatFox->obj.pos.x = 0.0f;

                player->camRoll = 0.0f;

                player->cam.eye.x = gCsCamEyeX = greatFox->obj.pos.x - 2800.0f;
                player->cam.eye.y = gCsCamEyeY = greatFox->obj.pos.y + 1400.0f;
                player->cam.eye.z = gCsCamEyeZ = greatFox->obj.pos.z + 700.0f;

                player->cam.at.x = gCsCamAtX = greatFox->obj.pos.x - 1000.0f;
                player->cam.at.y = gCsCamAtY = greatFox->obj.pos.y;
                player->cam.at.z = gCsCamAtZ = greatFox->obj.pos.z;

                D_ctx_80177A48[0] = 0.0f;
                gFillScreenAlpha = 255;

                for (i = 0; i < 4; i++) {
                    Object_Kill(&gActors[i + 30].obj, gActors[i + 30].sfxSource);
                }

                player->pos.x = greatFox->obj.pos.x + 200.0f;
                player->pos.y = greatFox->obj.pos.y - 480.0f;
                player->pos.z = greatFox->obj.pos.z;

                AUDIO_PLAY_BGM(NA_BGM_SZ_START_DEMO);
            }
            break;

        case 3:
            gFillScreenAlpha = 0;
            gCsCamEyeX = -1250.0f;
            gCsCamEyeY = -395.0f;

            gCsCamAtX = player->pos.x;
            gCsCamAtY = player->pos.y;
            gCsCamAtZ = player->pos.z;

            Math_SmoothStepToF(D_ctx_80177A48, 0.05f, 1.0f, 0.0005f, 0.0f);

            gActors[30].obj.rot.x -= 0.65f;
            gActors[31].obj.rot.x -= 0.65f;
            gActors[32].obj.rot.x -= 0.65f;
            gActors[30].iwork[11] = 2;
            gActors[31].iwork[11] = 2;
            gActors[32].iwork[11] = 2;
            gActors[30].obj.rot.y += 0.5f;
            gActors[31].obj.rot.y -= 0.4f;
            gActors[32].obj.rot.y += 0.6f;
            gActors[30].vel.z += 0.325f;
            gActors[31].vel.z -= 0.26f;
            gActors[32].vel.z += 0.39000002f;
            gActors[30].obj.rot.z += 0.2f;
            gActors[31].obj.rot.z -= 0.3f;
            gActors[32].obj.rot.z -= 0.3f;
            gActors[30].vel.y += 0.4f;
            gActors[31].vel.y += 0.27f;
            gActors[32].vel.y += 0.4f;

            if (gCsFrameCount > 760) {
                player->rot.x += 0.25f;
            }

            if (gCsFrameCount > 765) {
                gCsCamEyeZ += 3.0f;
                Math_SmoothStepToF(D_ctx_80177A48, 0.9f, 1.0f, 0.07f, 0.0f);
            } else {
                gCsCamEyeZ = 0.0f;
            }

            if (gCsFrameCount == 800) {
                for (i = 0; i < ARRAY_COUNT(gActors); i++) {
                    Object_Kill(&gActors[i].obj, gActors[i].sfxSource);
                }
                SectorZ_LoadLevelObjects();
                SectorZ_TeamSetup();
            }

            if (gCsFrameCount == 820) {
                Audio_KillSfxById(NA_SE_DEMO_SIREN);
                player->state = PLAYERSTATE_ACTIVE;
                player->unk_01C = player->unk_018 = player->unk_014 = 0.f;
                AUDIO_PLAY_BGM(gBgmSeqId);
                gLevelStartStatusScreenTimer = 50;
            }
            break;
    }

    switch (gCsFrameCount) {
        case 20:
            AUDIO_PLAY_SFX(NA_SE_DEMO_SIREN, gDefaultSfxSource, 4);
            break;

        case 330:
            Radio_PlayMessage(gMsg_ID_16010, RCID_ROB64);
            break;

        case 80:
            break;

        case 370:
            SectorZ_CsEnemies(&gActors[30], 0);
            break;

        case 390:
            SectorZ_CsEnemies(&gActors[31], 1);
            break;

        case 405:
            SectorZ_CsEnemies(&gActors[32], 2);
            break;

        case 425:
            SectorZ_CsEnemies(&gActors[33], 3);
            break;

        case 560:
            Radio_PlayMessage(gMsg_ID_16020, RCID_FOX);
            break;

        case 700:
            if (gTeamShields[TEAM_ID_SLIPPY] > 0) {
                SectorZ_CsTeamInit(&gActors[30], 0);
            }
            break;

        case 720:
            if (gTeamShields[TEAM_ID_FALCO] > 0) {
                SectorZ_CsTeamInit(&gActors[31], 1);
            }
            break;

        case 740:
            if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                SectorZ_CsTeamInit(&gActors[32], 2);
            }
            break;

        case 760:
            player->unk_194 = 5.0f;
            player->unk_190 = 5.0f;
            player->yRot_114 = 90.0f;
            player->baseSpeed = gArwingSpeed;
            player->draw = true;
            AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, player->sfxSource, 0);
            break;
    }

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

f32 sCsTeamXpos[] = { -300.0f, 350.0f, -50.0f, 800.0f };

f32 sCsTeamYpos[] = { 0.0f, -30.0f, -90.0f, -550.0f };

f32 sCsTeamZpos[] = { -200.0f, -250.0f, -500.0f, 5000.0f };

void SectorZ_CsLevelCompleteTeamInit(ActorCutscene* this, s32 index) {
    f32 direction;

    direction = 1.0f;
    if (!gGreatFoxIntact) {
        direction = -1.0f;
    }

    Actor_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_ACTOR_CUTSCENE;

    this->obj.pos.x = sCsTeamXpos[index] * direction;
    this->obj.pos.y = sCsTeamYpos[index];
    this->obj.pos.z = sCsTeamZpos[index];

    this->fwork[0] = gPlayer[0].baseSpeed;
    this->rot_0F4.y = gPlayer[0].rot.y;

    Object_SetInfo(&this->info, this->obj.id);

    if (index < 3) {
        this->iwork[11] = 1;
        AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, this->sfxSource, 4);

        // @port set team faces
        this->iwork[14] = index + 2;
    } else {
        this->animFrame = ACTOR_CS_GREAT_FOX;
        this->fwork[0] = 20.0f;
        AUDIO_PLAY_SFX(NA_SE_GREATFOX_ENGINE, this->sfxSource, 0);
        AUDIO_PLAY_SFX(NA_SE_GREATFOX_BURNER, this->sfxSource, 0);
    }
}

void SectorZ_CsLevelCompleteKattInit(void) {
    ActorCutscene* katt = &gActors[AI360_KATT];

    Actor_Initialize(katt);
    katt->obj.status = OBJ_INIT;
    katt->obj.id = OBJ_ACTOR_CUTSCENE;

    katt->obj.pos.x = gBosses[SZ_GREAT_FOX].obj.pos.x + 700.0f;
    katt->obj.pos.y = gBosses[SZ_GREAT_FOX].obj.pos.y - 1000.0f;
    katt->obj.pos.z = gBosses[SZ_GREAT_FOX].obj.pos.z - 1000.0f;

    katt->rot_0F4.y = 180.0f;
    katt->rot_0F4.x = 20.0f;

    katt->obj.rot.x = -20.0f;
    katt->obj.rot.y = 180.0f;
    katt->obj.rot.y *= 2.0f;
    katt->obj.rot.z = -katt->rot_0F4.z;

    katt->fwork[0] = 30.0f;
    katt->animFrame = ACTOR_CS_KATT;
    katt->iwork[11] = 1;
    katt->state = 10;
    katt->timer_0BC = 130;

    Object_SetInfo(&katt->info, katt->obj.id);
    AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, katt->sfxSource, 4);
}

void SectorZ_LevelComplete(Player* player) {
    s32 i;
    Vec3f src;
    Vec3f dest;
    ActorCutscene* greatFoxCs = &gActors[SZ_GREAT_FOX];
    ActorCutscene* falco = &gActors[1];
    ActorCutscene* peppy = &gActors[2];
    ActorCutscene* slippy = &gActors[3];
    SzGreatFox* greatFox = &gBosses[SZ_GREAT_FOX];
    f32 direction;

    PRINTF("Enm->time0 %d\n");
    PRINTF("time0 %d\n");
    PRINTF("Demo_Time=%d\n", gGameFrameCount);

    direction = 1.0f;
    if (!gGreatFoxIntact) {
        direction = -1.0f;
    }

    Math_SmoothStepToF(&player->boostSpeed, 0.0f, 0.1f, 1.5f, 0.0f);

    switch (player->csState) {
        case 1000:
            Math_SmoothStepToF(&player->rot.y, -40.0f, 0.1f, 2.5f, 0);
            Math_SmoothStepToF(&player->rot.z, -60.0f, 0.2f, 5.0f, 0);
            Math_SmoothStepToF(&player->rot.x, 0, 0.1f, 2.5f, 0);
            if (player->csTimer == 0) {
                player->csState = 1001;
                player->csTimer = 100;
                AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, player->sfxSource, 0);
                player->unk_194 = 5.0f;
                player->unk_190 = 5.0f;
                gProjectFar = 30000.0f;
            }
            break;

        case 1001:
            player->unk_190 = 2.0f;

            Math_SmoothStepToF(&player->rot.x, 15.0f, 0.1f, 0.4f, 0);
            Math_SmoothStepToF(&player->rot.z, 40.0f, 0.2f, 5.0f, 0);
            Math_SmoothStepToF(&player->rot.y, 120.0f, 0.1f, 2.0f, 0);

            player->baseSpeed += 1.0f;
            if (player->baseSpeed >= 70.0f) {
                player->baseSpeed = 70.0f;
            }

            if (player->csTimer == 0) {
                gPlayer[0].csState = 0;
            }
            break;

        case 100:
            gCsCamEyeX = greatFox->obj.pos.x;
            gCsCamEyeY = greatFox->obj.pos.y;
            gCsCamEyeZ = greatFox->obj.pos.z + 4000.0f;

            gCsCamAtX = greatFox->obj.pos.x;
            gCsCamAtY = greatFox->obj.pos.y;
            gCsCamAtZ = greatFox->obj.pos.z;

            D_ctx_80177A48[0] = 1.0f;
            gProjectFar = 30000.0f;

            player->draw = false;
            player->baseSpeed = 0.0f;
            player->camRoll = 0.0f;

            if (greatFox->state != 0) {
                player->csState = 0;
            }
            break;

        case 0:
            gCsFrameCount = 0;

            player->draw = false;

            gCsCamEyeX = greatFox->obj.pos.x;
            gCsCamEyeY = greatFox->obj.pos.y;
            gCsCamEyeZ = greatFox->obj.pos.z + 4000.0f;

            D_ctx_80177A48[0] = 1.0f;

            player->csState = 1;

            gProjectFar = 30000.0f;

            player->csTimer = 550;
            player->baseSpeed = 0.0f;
            player->camRoll = 0.0f;

            gFillScreenAlphaTarget = 255;
            gFillScreenAlpha = gFillScreenAlphaTarget;

            for (i = 0; i < ARRAY_COUNT(gActors); i++) {
                Object_Kill(&gActors[i].obj, gActors[i].sfxSource);
            }
            AUDIO_PLAY_SFX(NA_SE_GREATFOX_BURNER, greatFox->sfxSource, 0);
            break;

        case 1:
            gFillScreenAlphaTarget = 0;
            gFillScreenAlpha = 0;

            Math_SmoothStepToAngle(&greatFox->rot_078.x, 20.0f, 0.03f, greatFox->fwork[1], 0.0f);
            Math_SmoothStepToAngle(&greatFox->rot_078.y, 180.0f, 0.03f, greatFox->fwork[2], 0.0f);
            Math_SmoothStepToAngle(&greatFox->rot_078.z, 30.0f, 0.03f, greatFox->fwork[3], 0.0f);
            Math_SmoothStepToF(&greatFox->fwork[0], 20.0f, 0.05f, 0.3f, 0.0f);
            Math_SmoothStepToF(&greatFox->fwork[1], 0.07f, 1.0f, 0.07f, 0.0f);
            Math_SmoothStepToF(&greatFox->fwork[2], 0.5f, 1.0f, 0.05f, 0.0f);
            Math_SmoothStepToF(&greatFox->fwork[3], 0.7f, 1.0f, 0.7f, 0.0f);

            if ((gCsFrameCount == 100) && gGreatFoxIntact) {
                AUDIO_PLAY_BGM(NA_BGM_COURSE_CLEAR);
            }

            if ((gCsFrameCount == 210) && gGreatFoxIntact) {
                gLevelClearScreenTimer = 100;
                gMissionStatus = MISSION_ACCOMPLISHED;
            }

            if ((gCsFrameCount == 230) && sKattEnabled) {
                SectorZ_CsLevelCompleteKattInit();
            }

            gCsCamAtX = greatFox->obj.pos.x;
            gCsCamAtY = greatFox->obj.pos.y + (gCameraShakeY * 2.0f);
            gCsCamAtZ = greatFox->obj.pos.z;

            if (player->csTimer == 0) {
                player->csState = 2;
            }
            break;

        case 2:
            gFillScreenAlphaTarget = 0;
            gFillScreenAlpha = 0;

            if (player->csTimer == 0) {
                if (!gGreatFoxIntact) {
                    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 50);
                    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 50);
                }

                gCsFrameCount = 1280;

                player->csState = 10;
                player->csTimer = 1000;

                Audio_StopPlayerNoise(0);
                Audio_KillSfxBySource(player->sfxSource);
                Play_ClearObjectData();

                player->pos.x = 0.0f;
                player->pos.y = 0.0f;
                player->pos.z = 0.0f;

                player->rot.x = 0.0f;
                player->draw = true;
                player->rot.y = 180.0f;
                player->rot.z = 0.0f;
                player->yRot_114 = 0.0f;
                player->aerobaticPitch = 0.0f;
                player->baseSpeed = 40.0f;

                gCsCamEyeX = 0.0f - (200.0f * direction);
                gCsCamEyeY = player->pos.y;
                gCsCamEyeZ = player->pos.z + 12000.0f;
                gCsCamAtX = player->pos.x;
                gCsCamAtY = player->pos.y;
                gCsCamAtZ = player->pos.z;

                if (gTeamShields[TEAM_ID_FALCO] > 0) {
                    SectorZ_CsLevelCompleteTeamInit(falco, 0);
                }
                if (gTeamShields[TEAM_ID_SLIPPY] > 0) {
                    SectorZ_CsLevelCompleteTeamInit(slippy, 1);
                }
                if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                    SectorZ_CsLevelCompleteTeamInit(peppy, 2);
                }
                SectorZ_CsLevelCompleteTeamInit(greatFoxCs, 3);
                gFillScreenAlpha = gFillScreenAlphaTarget = 255;
            }
            break;

        case 10:
            gFillScreenAlpha = gFillScreenAlphaTarget = 0;
            gCsCamAtX = player->pos.x;
            gCsCamAtY = player->pos.y;
            gCsCamAtZ = player->pos.z;

            if (gCsFrameCount == 1620) {
                player->csState++;
                D_ctx_80177A48[0] = 0.0f;
                D_ctx_80177A48[1] = 0.0f;
                D_ctx_80177A48[2] = 0.0f;
                D_ctx_80177A48[3] = 300.0f;

                for (i = 0; i < 200; i++) {
                    gScenery360[i].obj.status = OBJ_FREE;
                }
            }
            break;

        case 11:
            Matrix_RotateY(gCalcMatrix, D_ctx_80177A48[1] * M_DTOR, MTXF_NEW);
            D_ctx_80177A48[1] += D_ctx_80177A48[2] * direction;

            src.x = -800.0f * direction;
            src.y = D_ctx_80177A48[3];
            src.z = 0.0f;

            Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

            Math_SmoothStepToF(&player->baseSpeed, 0, 0.05f, 1.0f, 0);
            Math_SmoothStepToF(&falco->fwork[0], 0, 0.05f, 1.0f, 0);
            Math_SmoothStepToF(&slippy->fwork[0], 0, 0.05f, 1.0f, 0);
            Math_SmoothStepToF(&peppy->fwork[0], 0.0f, 0.05f, 1.0f, 0);
            Math_SmoothStepToF(&greatFoxCs->fwork[0], 0.0f, 0.05f, 1.0f, 0);
            Math_SmoothStepToF(D_ctx_80177A48, 0.02f, 1.0f, 0.001f, 0);

            if (gCsFrameCount > 2000) {
                Math_SmoothStepToF(&D_ctx_80177A48[3], 50.0f, 0.05f, 1.5f, 0);
            }

            if (gCsFrameCount < 2330) {
                Math_SmoothStepToF(&D_ctx_80177A48[2], 0.5f, 1.0f, 0.008f, 0);
            } else {
                Math_SmoothStepToF(&D_ctx_80177A48[2], 0.0f, 1.0f, 0.002f, 0);
            }

            if (gCsFrameCount > 2510) {
                player->baseSpeed += 2.0f;
                player->rot.x += 0.1f;
                player->unk_190 = 2.0f;
            }

            if (gCsFrameCount > 2550) {
                Math_SmoothStepToF(&D_ctx_80177A48[0], 0.1f, 1.0f, 0.005f, 0);
            } else {
                gCsCamEyeX = greatFoxCs->obj.pos.x - (800.0f * direction) + dest.x;
                gCsCamEyeY = greatFoxCs->obj.pos.y + 550.0f + dest.y;
                gCsCamEyeZ = greatFoxCs->obj.pos.z + 2430.0f + dest.z;
            }

            gCsCamAtX = greatFoxCs->obj.pos.x - (800.0f * direction);
            gCsCamAtY = greatFoxCs->obj.pos.y + 550.0f;
            gCsCamAtZ = greatFoxCs->obj.pos.z + 2430.0f - 250.0f;

            if (gCsFrameCount == 2660) {
                Audio_FadeOutAll(50);
            }

            if (gCsFrameCount > 2710) {
                gFillScreenAlphaTarget = 255;
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
                gFillScreenAlphaStep = 8;
                if (gFillScreenAlpha == 255) {
                    player->state = PLAYERSTATE_NEXT;
                    player->csTimer = 0;
                    gFadeoutType = 4;
                    gLeveLClearStatus[LEVEL_SECTOR_Z] = Play_CheckMedalStatus(100) + 1;
                }
            }
            break;
    }

    if (gGreatFoxIntact) {
        switch (gCsFrameCount) {
            case 1729:
                Radio_PlayMessage(gMsg_ID_16250, RCID_ROB64);
                break;

            case 1847:
                switch (gTeamShields[TEAM_ID_FALCO]) {
                    case -1:
                        Radio_PlayMessage(gMsg_ID_20337, RCID_ROB64);
                        break;

                    case 0:
                        Radio_PlayMessage(gMsg_ID_20343, RCID_ROB64);
                        break;

                    default:
                        Radio_PlayMessage(gMsg_ID_16260, RCID_FALCO);
                        break;
                }
                break;

            case 1984:
                switch (gTeamShields[TEAM_ID_PEPPY]) {
                    case -1:
                        Radio_PlayMessage(gMsg_ID_20338, RCID_ROB64);
                        break;

                    case 0:
                        Radio_PlayMessage(gMsg_ID_20344, RCID_ROB64);
                        break;

                    default:
                        Radio_PlayMessage(gMsg_ID_16270, RCID_PEPPY);
                        break;
                }
                break;

            case 2130:
                switch (gTeamShields[TEAM_ID_SLIPPY]) {
                    case -1:
                        Radio_PlayMessage(gMsg_ID_20339, RCID_ROB64);
                        break;

                    case 0:
                        Radio_PlayMessage(gMsg_ID_20345, RCID_ROB64);
                        break;

                    default:
                        Radio_PlayMessage(gMsg_ID_16280, RCID_SLIPPY);
                        break;
                }
                break;
        }
    } else {
        switch (gCsFrameCount) {
            case 1729:
                Radio_PlayMessage(gMsg_ID_16210, RCID_ROB64);
                break;

            case 1847:
                switch (gTeamShields[TEAM_ID_FALCO]) {
                    case -1:
                        Radio_PlayMessage(gMsg_ID_20337, RCID_ROB64);
                        break;

                    case 0:
                        Radio_PlayMessage(gMsg_ID_20343, RCID_ROB64);
                        break;

                    default:
                        Radio_PlayMessage(gMsg_ID_16220, RCID_FALCO);
                        break;
                }
                break;

            case 1984:
                switch (gTeamShields[TEAM_ID_PEPPY]) {
                    case -1:
                        Radio_PlayMessage(gMsg_ID_20338, RCID_ROB64);
                        break;

                    case 0:
                        Radio_PlayMessage(gMsg_ID_20344, RCID_ROB64);
                        break;

                    default:
                        Radio_PlayMessage(gMsg_ID_16230, RCID_PEPPY);
                        break;
                }
                break;

            case 2130:
                switch (gTeamShields[TEAM_ID_SLIPPY]) {
                    case -1:
                        Radio_PlayMessage(gMsg_ID_20339, RCID_ROB64);
                        break;

                    case 0:
                        Radio_PlayMessage(gMsg_ID_20345, RCID_ROB64);
                        break;

                    default:
                        Radio_PlayMessage(gMsg_ID_16240, RCID_SLIPPY);
                        break;
                }
                break;
        }
    }

    switch (gCsFrameCount) {
        case 1640:
            Radio_PlayMessage(gMsg_ID_16200, RCID_FOX);
            break;

        case 2277:
            gShowLevelClearStatusScreen = true;
            break;

        case 2477:
            gShowLevelClearStatusScreen = false;
            break;

        case 1370:
            if (gGreatFoxIntact) {
                gMissionStatus = MISSION_ACCOMPLISHED;
            } else {
                AUDIO_PLAY_BGM(NA_BGM_COURSE_FAILURE);
                gMissionStatus = MISSION_COMPLETE;
            }
            break;

        case 1560:
            if (!gGreatFoxIntact) {
                gLevelClearScreenTimer = 100;
            }
            break;

        case 1700:
            player->wingPosition = gLevelType;
            break;

        case 2450:
            peppy->state = 1;
            break;

        case 2470:
            slippy->state = 1;
            break;

        case 2490:
            falco->state = 1;
            break;

        case 2510:
            AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, player->sfxSource, 0);
            player->unk_190 = player->unk_194 = 5.0f;
            break;

        case 2550:
            greatFoxCs->state = 1;
            break;
    }

    Matrix_RotateY(gCalcMatrix, (player->yRot_114 + player->rot.y + 180.0f) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -(((player->xRot_120 + player->rot.x) + player->aerobaticPitch) * M_DTOR), MTXF_APPLY);

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

    Math_SmoothStepToF(&player->zRotBarrelRoll, 0.0f, 0.1f, 15.0f, 0.0f);
    Math_SmoothStepToF(&player->zRotBank, 0.0f, 0.1f, 15.0f, 0.0f);
    Math_SmoothStepToF(&player->camRoll, 0.0f, 0.1f, 3.0f, 0.0f);
    Math_SmoothStepToAngle(&player->aerobaticPitch, 0.0f, 0.1f, 20.0f, 0.0f);

    if (player->csState >= 1000) {
        if (player->pos.y < 700.0f) {
            Math_SmoothStepToF(&player->pos.y, 700.0f, 0.1f, 10.0f, 0.0f);
        }
        Camera_Update360(player, false);
        player->cam.eye.x += player->vel.x * 0.1f;
        player->cam.eye.y += player->vel.y * 0.1f;
        player->cam.eye.z += player->vel.z * 0.1f;
    } else {
        Math_SmoothStepToF(&player->cam.eye.x, gCsCamEyeX, D_ctx_80177A48[0], 50000.0f, 0.0f);
        Math_SmoothStepToF(&player->cam.eye.y, gCsCamEyeY, D_ctx_80177A48[0], 50000.0f, 0.0f);
        Math_SmoothStepToF(&player->cam.eye.z, gCsCamEyeZ, D_ctx_80177A48[0], 50000.0f, 0.0f);
        Math_SmoothStepToF(&player->cam.at.x, gCsCamAtX, D_ctx_80177A48[0], 50000.0f, 0.0f);
        Math_SmoothStepToF(&player->cam.at.y, gCsCamAtY, D_ctx_80177A48[0], 50000.0f, 0.0f);
        Math_SmoothStepToF(&player->cam.at.z, gCsCamAtZ, D_ctx_80177A48[0], 50000.0f, 0.0f);
    }

    player->bobPhase += 10.0f;
    player->yBob = -SIN_DEG(player->bobPhase) * 0.3f;
    player->rockPhase += 8.0f;
    player->rockAngle = SIN_DEG(player->rockPhase);
}

void SectorZ_LevelCompleteCsUpdate(ActorCutscene* this) {
    Vec3f src;
    Vec3f dest;

    switch (this->state) {
        case 1:
            this->state = 2;
            AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, this->sfxSource, 0);
            this->fwork[29] = 5.0f;

        case 2:
            this->iwork[11] = 2;
            this->fwork[0] += 2.0f;
            this->rot_0F4.x += this->fwork[1];
            Math_SmoothStepToF(&this->fwork[1], 0.1f, 1.0f, 0.01f, 0.0f);
            break;

        case 10:
            if (this->timer_0BC == 0) {
                this->state = 11;
            }
            break;

        case 11:
            Math_SmoothStepToF(&this->rot_0F4.x, 215.0f, 0.1f, 7.0f, 0.0f);
            Math_SmoothStepToF(&this->fwork[0], 10.0f, 0.1f, 1.5f, 0.0f);
            Math_SmoothStepToAngle(&this->rot_0F4.y, 140.0f, 0.1f, 1.0f, 0.0f);
            if (this->rot_0F4.x > 180.0f) {
                this->state = 12;
            }
            break;

        case 12:
            Math_SmoothStepToAngle(&this->rot_0F4.x, 218.0f, 0.1f, 7.0f, 0.0f);
            Math_SmoothStepToAngle(&this->rot_0F4.y, 147.0f, 0.1f, 1.0f, 0.0f);
            Math_SmoothStepToF(&this->rot_0F4.z, 170.0f, 0.03f, 3.0f, 0.0f);
            Math_SmoothStepToF(&this->fwork[0], 20.0f, 0.1f, 1.0f, 0.0f);
            break;
    }

    if (this->animFrame == ACTOR_CS_KATT) {
        switch (gCsFrameCount) {
            case 290:
                if (gTeamShields[TEAM_ID_FALCO] > 0) {
                    Radio_PlayMessage(gMsg_ID_16150, RCID_KATT);
                }
                break;

            case 430:
                AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, this->sfxSource, 0);
                this->fwork[29] = 8.0f;
                break;

            case 400:
                if (gGreatFoxIntact) {
                    Radio_PlayMessage(gMsg_ID_16160, RCID_KATT);
                } else {
                    Radio_PlayMessage(gMsg_ID_16165, RCID_KATT);
                }
                break;
        }

        if (gCsFrameCount > 430) {
            this->fwork[29] = 3.0f;
            Math_SmoothStepToF(&this->rot_0F4.z, 500.0f, 0.1f, 20.0f, 0.0f);
            Math_SmoothStepToF(&this->fwork[0], 40.0f, 0.1f, 3.0f, 0.0f);

            if ((gCsFrameCount < 460) && ((gCsFrameCount & 3) == 0)) {
                Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
                Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);
                Matrix_RotateZ(gCalcMatrix, this->obj.rot.z * M_DTOR, MTXF_APPLY);
                src.x = 0.0f;
                src.y = 70.0f;
                src.z = -70.0f;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);
                Effect_Effect393_Spawn(this->obj.pos.x + dest.x, this->obj.pos.y + dest.y, this->obj.pos.z + dest.z,
                                       3.1f);
            }
        }
    }

    Matrix_RotateY(gCalcMatrix, (this->rot_0F4.y + 180.0f) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -(this->rot_0F4.x * M_DTOR), MTXF_APPLY);

    src.x = 0.0f;
    src.y = 0.0f;
    src.z = this->fwork[0];

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

    this->vel.x = dest.x;
    this->vel.y = dest.y;
    this->vel.z = dest.z;

    this->obj.rot.x = -this->rot_0F4.x;
    this->obj.rot.y = this->rot_0F4.y + 180.0f;
    this->obj.rot.z = -this->rot_0F4.z;
}

void SectorZ_SpaceJunkUpdate(SzSpaceJunk* this) {
    s32 i;

    this->obj.rot.x += this->rot_0F4.x;
    this->obj.rot.y += this->rot_0F4.y;

    if (this->dmgType != DMG_NONE) {
        this->timer_0C6 = 20;
        this->dmgType = DMG_NONE;
        this->health -= this->damage;
        AUDIO_PLAY_SFX(NA_SE_EN_DAMAGE_S, this->sfxSource, 4);

        if (this->health <= 0) {
            Effect386_Spawn1(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 0.0f, 0.0f, 0.0f, 5.0f, 10);
            Actor_Despawn(this);
            BonusText_Display(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 2);

            gHitCount += 3;
            D_ctx_80177850 = 15;

            for (i = 0; i < 6; i++) {
                Effect_Effect357_Spawn50(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 1.0f);
            }

            Object_Kill(&this->obj, this->sfxSource);
            Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_OB_EXPLOSION_S);
        }
    }
}

void SectorZ_SpaceJunkDraw(SzSpaceJunk* this) {
    gSPDisplayList(gMasterDisp++, aSzSpaceJunk2DL);
    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
    RCP_SetupDL(&gMasterDisp, SETUPDL_57);
    gSPDisplayList(gMasterDisp++, aSzSpaceJunk4DL);
    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
}

Vec3f sFireSmokeOffsetPos[] = { { 612.0f, 409.0f, 386.0f }, { 1027.0f, 141.0f, 383.0f }, { 375.0f, 292.0f, 380.0f },
                                { -4.0f, 80.0f, 380.0f },   { 314.0f, 80.0f, 385.0f },   { 565.0f, 300.0f, 385.0f },
                                { 600.0f, 385.0f, 380.0f }, { 776.0f, 245.0f, 384.0f },  { 376.0f, 123.0f, 384.0f },
                                { 428.0f, 174.0f, 383.0f }, { 722.0f, 306.0f, 383.0f },  { 530.0f, 380.0f, 385.0f } };

void SectorZ_SzGreatFox_Update(SzGreatFox* this) {
    s32 i;
    s32 j;
    f32 x;
    f32 y;
    f32 z;
    Vec3f src;
    Vec3f dest;

    if (this->dmgType == DMG_MISSILE) {
        this->dmgType = DMG_NONE;
        this->timer_050 = 10;
        this->timer_052 = 60;
        this->state = 1;
        AUDIO_PLAY_SFX(NA_SE_OB_BROKEN_SPARK_L, this->sfxSource, 0);
    }

    if (this->timer_050 == 1) {
        gGreatFoxIntact = false;
    }

    if (this->timer_050 == 5) {
        x = this->obj.pos.x + 400.0f;
        y = this->obj.pos.y + 200.0f;
        z = this->obj.pos.z + 1000.0f;

        // Effects for broken pieces
        for (i = 0; i < 25; i++) {
            Effect_Effect357_Spawn50(x + RAND_FLOAT_CENTERED(300.0f), y + RAND_FLOAT_CENTERED(100.0f), z, 2.0f);
            func_effect_80079618(x + RAND_FLOAT_CENTERED(300.0f), y + RAND_FLOAT_CENTERED(100.0f), z, 2.0f);
        }
        Effect386_Spawn1(x, y, z, 0.0f, 0.0f, 0.0f, 20.0f, 30);
    }

    if (this->timer_052 != 0) {
        for (j = 0; j < 1; j++) {
            i = RAND_INT(11.99f);
            SectorZ_FireSmokeEffectSpawn(sFireSmokeOffsetPos[i].x + this->obj.pos.x,
                                         sFireSmokeOffsetPos[i].y + this->obj.pos.y,
                                         sFireSmokeOffsetPos[i].z + this->obj.pos.z, RAND_FLOAT_CENTERED(5.0f),
                                         RAND_FLOAT_CENTERED(5.0f), 10.0f, RAND_FLOAT(2.0f) + 4.0f);
        }
    }

    Matrix_RotateY(gCalcMatrix, (this->rot_078.y + 180.0f) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -(this->rot_078.x * M_DTOR), MTXF_APPLY);

    src.x = 0.0f;
    src.y = 0.0f;
    src.z = this->fwork[0];

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

    this->vel.x = dest.x;
    this->vel.y = dest.y;
    this->vel.z = dest.z;

    this->obj.rot.x = -this->rot_078.x;
    this->obj.rot.y = this->rot_078.y + 180.0f;
    this->obj.rot.z = -this->rot_078.z;

    if (!gGreatFoxIntact) {
        Matrix_RotateY(gCalcMatrix, (this->obj.rot.y - 270.0f) * M_DTOR, MTXF_NEW);
        Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);
        Matrix_RotateZ(gCalcMatrix, this->obj.rot.z * M_DTOR, MTXF_APPLY);
        Matrix_MultVec3fNoTranslate(gCalcMatrix, &sFireSmokeOffsetPos[RAND_INT(11.99f)], &dest);
        Effect_Effect389_Spawn(this->obj.pos.x + dest.x, this->obj.pos.y + dest.y, this->obj.pos.z + dest.z,
                               this->vel.x, this->vel.y, this->vel.z, RAND_FLOAT(0.1f) + 0.15f, 0);

        if (((gGameFrameCount % 7) == 0) && (Rand_ZeroOne() < 0.5f)) {
            SectorZ_FireSmokeEffectSpawn(this->obj.pos.x + dest.x, this->obj.pos.y + dest.y, this->obj.pos.z + dest.z,
                                         this->vel.x, this->vel.y, this->vel.z + 5.0f, RAND_FLOAT(2.0f) + 4.0f);
        }
    }
}

void SectorZ_SzGreatFox_Draw(SzGreatFox* this) {
    gSPFogPosition(gMasterDisp++, gFogNear, 1005);
    Cutscene_DrawGreatFox();
}

void SectorZ_LoadLevelObjects(void) {
    s32 i;
    s32 j;
    Actor* actor;
    Scenery360* scenery360;
    SzGreatFox* greatFox = &gBosses[SZ_GREAT_FOX];

    gLevelObjects = SEGMENTED_TO_VIRTUAL(gLevelObjectInits[gCurrentLevel]);

    Rand_SetSeed(1, 29000, 9876);

    for (scenery360 = gScenery360, i = 0; i < 1000; i++) {
        if (gLevelObjects[i].id <= OBJ_INVALID) {
            break;
        }

        if (gLevelObjects[i].id < OBJ_SCENERY_MAX) {
            Scenery360_Initialize(scenery360);
            scenery360->obj.status = OBJ_ACTIVE;
            scenery360->obj.id = gLevelObjects[i].id;
            scenery360->obj.pos.x = gLevelObjects[i].xPos;
            scenery360->obj.pos.y = gLevelObjects[i].yPos;
            scenery360->obj.pos.z = -gLevelObjects[i].zPos1;
            scenery360->obj.rot.y = gLevelObjects[i].rot.y;
            Object_SetInfo(&scenery360->info, scenery360->obj.id);
            scenery360++;
        }
    }

    if (CVarGetInteger("gSzActorFix", 0) == 1) {
        j = 48;
    } else {
        j = 50;
    }

    for (actor = &gActors[j], i = 0; i < 1000; i++) {
        if (gLevelObjects[i].id <= OBJ_INVALID) {
            break;
        }

        if ((gLevelObjects[i].id >= OBJ_ACTOR_START) && (gLevelObjects[i].id < OBJ_ACTOR_MAX)) {
            Actor_Initialize(actor);
            actor->obj.status = OBJ_INIT;
            actor->obj.id = gLevelObjects[i].id;
            actor->obj.pos.x = gLevelObjects[i].xPos;
            actor->obj.pos.y = gLevelObjects[i].yPos;
            actor->obj.pos.z = -gLevelObjects[i].zPos1;
            actor->health = 24;
            actor->rot_0F4.x = RAND_FLOAT_CENTERED(4.0f);
            actor->rot_0F4.y = RAND_FLOAT_CENTERED(4.0f);
            Object_SetInfo(&actor->info, actor->obj.id);
            actor->itemDrop = DROP_SILVER_RING;

#ifdef AVOID_UB
            if (j++ >= ARRAY_COUNT(gActors) - 1) {
#else
            if (j++ >= ARRAY_COUNT(gActors)) {
#endif
                break;
            }
            actor++;
        }
    }
    Boss_Initialize(greatFox);
    greatFox->obj.status = OBJ_INIT;

    greatFox->obj.pos.x = 0.0f;
    greatFox->obj.pos.y = 0.0f;
    greatFox->obj.pos.z = 0.0f;

    greatFox->rot_078.y = 90.0f;

    greatFox->obj.rot.x = -greatFox->rot_078.x;
    greatFox->obj.rot.y = greatFox->rot_078.y + 180.0f;
    greatFox->obj.rot.z = -greatFox->rot_078.z;

    greatFox->obj.id = OBJ_BOSS_SZ_GREAT_FOX;
    Object_SetInfo(&greatFox->info, greatFox->obj.id);
    AUDIO_PLAY_SFX(NA_SE_GREATFOX_ENGINE, greatFox->sfxSource, 0);
}
