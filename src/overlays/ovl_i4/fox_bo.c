/*
 * File: fox_bo.c
 * System: Bolse
 * Description: Level: Bolse
 */

#include "global.h"
#include "assets/ast_bolse.h"
#include "prevent_bss_reordering.h"

extern s32 dummy200;

struct Dummy200 {
    int x;
};
struct Dummy201 {
    int x;
};
struct Dummy202 {
    int x;
};
struct Dummy203 {
    int x;
};
struct Dummy204 {
    int x;
};
struct Dummy205 {
    int x;
};
struct Dummy206 {
    int x;
};
struct Dummy210 {
    int x;
};
struct Dummy211 {
    int x;
};
struct Dummy212 {
    int x;
};
struct Dummy213 {
    int x;
};
struct Dummy214 {
    int x;
};
struct Dummy215 {
    int x;
};
struct Dummy216 {
    int x;
};
struct Dummy220 {
    int x;
};
struct Dummy221 {
    int x;
};
struct Dummy222 {
    int x;
};
struct Dummy223 {
    int x;
};
struct Dummy224 {
    int x;
};

typedef struct UnkStruct_D_i4_801A03E0 {
    f32 unk_00;
    f32 unk_04;
    f32 unk_08;
    f32 unk_0C;
    f32 unk_10;
    f32 unk_14;
    s32 unk_18;
} UnkStruct_D_i4_801A03E0;

f32 D_i4_801A03D0;
f32 D_i4_801A03D4;
f32 D_i4_801A03D8;
s32 D_BO_801A03DC;
UnkStruct_D_i4_801A03E0 D_i4_801A03E0[6];
UnkStruct_D_i4_801A03E0 D_i4_801A0488[6];
s32 D_i4_801A0530;

Matrix D_BO_8019EE80 = { {
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
} };

f32 D_i4_8019EEC0 = 0.0f;

void Bolse_8018BD60(ActorEvent* this) {
    s32 i;
    ActorAllRange* actor;
    f32 D_i4_8019EEC4[4] = { 8000.0f, -8000.0f, 8000.0f, -8000.0f };
    f32 D_i4_8019EED4[4] = { 8000.0f, 8000.0f, -8000.0f, -8000.0f };

    if (gAllRangeCheckpoint == 0) {
        this->counter_04E++;
        if (this->counter_04E >= 4) {
            this->counter_04E = 0;
        }
        for (actor = &gActors[10], i = 10; i < 16; i++, actor++) {
            if (actor->obj.status == OBJ_FREE) {
                Actor_Initialize(actor);
                actor->obj.status = OBJ_ACTIVE;
                actor->obj.id = OBJ_ACTOR_ALLRANGE;
                actor->obj.pos.x = D_i4_8019EEC4[this->counter_04E];
                actor->obj.pos.y = 1000.0f;
                actor->obj.pos.z = D_i4_8019EED4[this->counter_04E];
                actor->state = 1;
                actor->aiIndex = -1;
                actor->health = 24;
                actor->iwork[11] = 1;
                actor->itemDrop = DROP_SILVER_RING_50p;
                actor->aiType = i;
                Object_SetInfo(&actor->info, actor->obj.id);
                AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, actor->sfxSource, 4);
                break;
            }
        }
    }
    ActorAllRange_UpdateStarWolfEvents(this);
    ActorAllRange_UpdateEnemyEvents(this);
}

f32 D_i4_8019EEE4[] = { -200.0f, -100.0f, -0.0f, 100.0f, 200.0f };

void Bolse_SpawnEnemies(ActorEvent* this, s32 count) {
    s32 i;
    ActorAllRange* enemy;

    for (i = AI360_ENEMY, enemy = &gActors[AI360_ENEMY]; i < count + AI360_ENEMY; i++, enemy++) {
        if (enemy->obj.status == OBJ_FREE) {
            Actor_Initialize(enemy);
            enemy->obj.status = OBJ_ACTIVE;
            enemy->obj.id = OBJ_ACTOR_ALLRANGE;
            enemy->obj.pos.z = 0.0f;

            if (D_i4_801A0530 > 1000) {
                enemy->obj.pos.x = 10000.0f;
                enemy->obj.pos.y = 3000.0f;
            } else {
                enemy->obj.pos.x = D_i4_8019EEE4[this->counter_04E];
                enemy->obj.pos.y = 50.0f;
                AUDIO_PLAY_SFX(NA_SE_EN_PASS, enemy->sfxSource, 4);
                enemy->timer_0BC = 5;
                enemy->timer_0C2 = 100;
                enemy->rot_0F4.x = 90.0f;
            }

            enemy->state = 1;
            enemy->timer_0C4 = 300;
            enemy->aiType = i;
            enemy->aiIndex = -1;

            if (i < AI360_ENEMY + 3) {
                enemy->aiIndex = AI360_SLIPPY;
                gActors[AI360_SLIPPY].aiIndex = -1;
            }

            if ((i == AI360_ENEMY + 7) || (i == AI360_ENEMY + 8)) {
                enemy->aiIndex = AI360_FOX;
            }

            if ((i == AI360_ENEMY + 10) || (i == AI360_ENEMY + 11)) {
                enemy->aiIndex = AI360_PEPPY;
                gActors[AI360_PEPPY].aiIndex = -1;
            }

            if (i == AI360_ENEMY + 12) {
                enemy->aiIndex = AI360_FALCO;
                gActors[AI360_FALCO].aiIndex = -1;
            }

            if ((D_i4_801A0530 > 16000) && ((i == AI360_ENEMY + 13) || (i == AI360_ENEMY + 14))) {
                enemy->aiIndex = AI360_FOX;
            }

            enemy->health = 24;
            enemy->iwork[11] = 1;

            if (D_i4_801A0530 < 16000) {
                enemy->itemDrop = DROP_SILVER_RING_50p;
            }

            Object_SetInfo(&enemy->info, enemy->obj.id);
            AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, enemy->sfxSource, 4);

            this->counter_04E++;
            if (this->counter_04E >= 5) {
                this->counter_04E = 0;
            }
            break;
        }
    }
}

void Bolse_UpdateEventHandler(ActorEvent* this) {
    s32 i = 0;
    Player* player = &gPlayer[0];
    s32 pad;
    Actor* actor;

    gBolseDynamicGround = true;
    D_i4_801A0530++;

    switch (this->state) {
        case 0:
            gAllRangeSpawnEvent = 500000;
            gAllRangeEventTimer = 0;
            gStarWolfMsgTimer = 0;
            this->state = 2;

            if (gAllRangeCheckpoint == 0) {
                gBosses[0].fwork[1] = 0.3f;
                D_BO_801A03DC = 6;
            } else {
                gAllRangeCheckpoint = 1;
                gHitCount = gSavedHitCount;
                gBosses[1].state = 2;
                gAllRangeEventTimer = 3000;
                this->iwork[1] = gHitCount;
            }

            for (i = 0; i < 6; i++) {
                gStarWolfTeamAlive[i] = gSavedStarWolfTeamAlive[i];
            }

        case 2:
            Bolse_8018BD60(this);

            switch (gAllRangeEventTimer) {
                case 300:
                    Radio_PlayMessage(gMsg_ID_11020, RCID_PEPPY);
                    break;
                case 600:
                    Radio_PlayMessage(gMsg_ID_11030, RCID_FALCO);
                    break;
                case 900:
                    Radio_PlayMessage(gMsg_ID_11040, RCID_SLIPPY);
                    break;
                case 1500:
                    Radio_PlayMessage(gMsg_ID_11210, RCID_SLIPPY);
                    break;
                case 1800:
                    Radio_PlayMessage(gMsg_ID_11220, RCID_FALCO);
                    break;
                case 2300:
                    Radio_PlayMessage(gMsg_ID_11240, RCID_SLIPPY);
                    break;
                case 2500:
                    Radio_PlayMessage(gMsg_ID_11230, RCID_PEPPY);
                    break;
            }

            if ((D_i4_801A0530 < 9600) && ((D_i4_801A0530 & 0x400) != 0)) {
                Bolse_SpawnEnemies(this, 8);
            }

            if (gBosses[2].state == 10) {
                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 1);
                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 1);
                if ((gPlayer[0].state == PLAYERSTATE_ACTIVE) || (gPlayer[0].state == PLAYERSTATE_U_TURN)) {
                    gPlayer[0].state = PLAYERSTATE_LEVEL_COMPLETE;
                    gPlayer[0].csTimer = 30;
                    gPlayer[0].csState = 0;
                    gPlayer[0].unk_000 = 0.0f;
                }
                AllRange_ClearRadio();
                this->state = 6;
                AUDIO_PLAY_SFX(NA_SE_EN_ANDROSS_EXPLOSION, this->sfxSource, 0);
                AUDIO_PLAY_SFX(NA_SE_EN_DOWN_IMPACT, this->sfxSource, 4);
                gScreenFlashTimer = 8;

                for (actor = &gActors[10], i = 0; i < 20; i++, actor++) {
                    if (actor->obj.status == OBJ_ACTIVE) {
                        actor->obj.status = OBJ_DYING;
                        actor->timer_0BC = 30;
                    }
                }
            }

            if ((gBosses[1].state == 2) && (gBosses[1].obj.status == OBJ_ACTIVE)) {
                this->iwork[1] = gHitCount;
                this->state = 10;
                this->timer_0BC = 150;
                gPlayer[0].state = PLAYERSTATE_STANDBY;
                AUDIO_PLAY_BGM(NA_BGM_BOSS_BO);
                AllRange_ClearRadio();
                gPlayer[0].cam.eye.x = 400.0f;
                gPlayer[0].cam.eye.y = 50.0f;
                gPlayer[0].cam.eye.z = 3000.0f;
                gPlayer[0].cam.at.x = 0.0f;
                gPlayer[0].cam.at.y = 0.0f;
                gPlayer[0].cam.at.z = 0.0f;
                for (i = 10; i < 30; i++) {
                    Object_Kill(&gActors[i].obj, gActors[i].sfxSource);
                }
            } else if ((gAllRangeCheckpoint == 1) && (((gHitCount - this->iwork[1]) >= 5) || (D_i4_801A0530 == 4000))) {
                gAllRangeCheckpoint = 2;
                this->iwork[1] = gHitCount;
                if ((gStarWolfTeamAlive[0] != 0) || (gStarWolfTeamAlive[1] != 0) || (gStarWolfTeamAlive[2] != 0) ||
                    (gStarWolfTeamAlive[3] != 0)) {
                    gAllRangeSpawnEvent = gAllRangeEventTimer + 120;
                    gStarWolfMsgTimer = 1000;
                }
            }
            break;

        case 3:
            gBolseDynamicGround = false;

            for (i = 0; i < 4; i++) {
                if (gStarWolfTeamAlive[i] != 0) {
                    actor = &gActors[i + 4];
                    break;
                }
                if (i == 3) {
                    this->state = 2;
                    player->state = PLAYERSTATE_ACTIVE;
                    return;
                }
            }

            player->cam.eye.x += actor->vel.x * 0.23f;
            player->cam.eye.y += actor->vel.y * 0.23f;
            player->cam.eye.z += actor->vel.z * 0.23f;

            Math_SmoothStepToF(&player->cam.at.x, actor->obj.pos.x, 1.0f, 20000.0f, 0.0f);
            Math_SmoothStepToF(&player->cam.at.y, actor->obj.pos.y, 1.0f, 20000.0f, 0.0f);
            Math_SmoothStepToF(&player->cam.at.z, actor->obj.pos.z, 1.0f, 20000.0f, 0.0f);
            Math_SmoothStepToF(&player->camRoll, 0.0f, 0.1f, 0.2f, 0);

            if ((gControllerPress->button & START_BUTTON) || ((gAllRangeSpawnEvent + 300) == gAllRangeEventTimer)) {
                this->state = 2;
                player->state = PLAYERSTATE_ACTIVE;
                Camera_Update360(player, true);
                player->unk_014 = 0.0f;
                D_hud_80161708 = 0;
            }
            gPauseEnabled = false;
            break;

        case 10:
            if (gBosses[1].obj.status != 0) {
                if (fabsf(Math_SmoothStepToF(&gBosses[1].scale, 0.0f, 1.0f, 0.05f, 0.001f)) < 0.05f) {
// @bug: i is uninitialized and likely contains stack garbage.
#ifdef AVOID_UB
                    Object_Kill(&gBosses[1].obj, gBosses[1].sfxSource);
#else
                    Object_Kill(&gBosses[1].obj, gBosses[i].sfxSource);
#endif
                    gLight1R = 100;
                    gLight1G = 100;
                    gLight1B = 80;
                    gAmbientR = 0;
                    gAmbientG = 15;
                    gAmbientB = 30;
                }
            }

            gBosses[0].fwork[1] = 0.0f;

            gBosses[0].obj.rot.y = gBosses[0].fwork[1];

            player->cam.eye.x -= 6.0f;
            player->cam.eye.z -= 12.0f;
            player->cam.at.y += 8.0f;

            gPlayer[0].cam.eye.y += 2.0f;

            Math_SmoothStepToF(&player->camRoll, 0.0f, 1.0f, 1000.0f, 0);

            if (this->timer_0BC == 130) {
                Radio_PlayMessage(gMsg_ID_11060, RCID_FALCO);
                gAllRangeCheckpoint = 1;
                gSavedHitCount = gHitCount;
                for (i = TEAM_ID_FALCO; i <= TEAM_ID_PEPPY; i++) {
                    gSavedTeamShields[i] = gTeamShields[i];
                }
            }

            if ((this->timer_0BC % 8) == 0) {
                Bolse_SpawnEnemies(this, 15);
            }

            if (!this->timer_0BC) {
                gAllRangeEventTimer = 3000;
                this->state = 2;
                player->state = PLAYERSTATE_ACTIVE;
                Camera_Update360(player, true);
                player->unk_014 = 0.0f;
                Audio_KillSfxBySource(gBosses[1].sfxSource);
                this->iwork[1] = gHitCount;
            }
            break;

        case 6:
            gActors[AI360_FALCO].aiIndex = 0;
            gActors[AI360_FALCO].state = 2;
            gActors[AI360_SLIPPY].aiIndex = 0;
            gActors[AI360_SLIPPY].state = 2;
            gActors[AI360_PEPPY].aiIndex = 0;
            gActors[AI360_PEPPY].state = 2;
            gActors[AI360_WOLF].aiIndex = gActors[AI360_LEON].aiIndex = gActors[AI360_PIGMA].aiIndex =
                gActors[AI360_ANDREW].aiIndex = -1;
            break;
    }

    if (gStarWolfMsgTimer != 0) {
        gStarWolfMsgTimer--;
        switch (gStarWolfMsgTimer) {
            case 860:
                if (gStarWolfTeamAlive[0] != 0) {
                    Radio_PlayMessage(gMsg_ID_11100, RCID_WOLF);
                }
                break;

            case 760:
                if (gStarWolfTeamAlive[1] != 0) {
                    Radio_PlayMessage(gMsg_ID_11110, RCID_LEON);
                }
                break;

            case 670:
                if (gStarWolfTeamAlive[2] != 0) {
                    Radio_PlayMessage(gMsg_ID_11120, RCID_PIGMA);
                }
                break;
            // @recomp: Fix voice line being cut out
            case 540: // Original value: 550
                if (gStarWolfTeamAlive[3] != 0) {
                    Radio_PlayMessage(gMsg_ID_11130, RCID_ANDREW);
                }
                break;

            case 390:
                if (gLeveLClearStatus[LEVEL_FORTUNA] == 0) {
                    Radio_PlayMessage(gMsg_ID_9285, RCID_FOX);
                } else {
                    Radio_PlayMessage(gMsg_ID_11241, RCID_FOX);
                }
                break;
        }
    }
}

s32 Bolse_8018CC60(Actor* this) {
    Vec3f src;

    if (gAllRangeCheckpoint == 0) {
        this->obj.pos.x = src.x = this->fwork[10];
        this->obj.pos.y = src.y = this->fwork[11];
        this->obj.pos.z = src.z = this->fwork[12];
        Matrix_MultVec3fNoTranslate(&D_BO_8019EE80, &src, &this->obj.pos);
        this->fwork[13] = gBosses[0].obj.rot.y;
    }

    return 0;
}

s32 Bolse_8018CCE8(BoLaserCannon* this) {
    s32 i;
    s32 actorIndex;
    f32 temp_fs0;
    f32 temp_fv0;
    f32 x;
    f32 y;
    f32 z;
    f32 var_fv1 = 10000.0f;
    f32 var_fa0 = 10000.0f;

    actorIndex = 0;

    for (i = 0; i < 4; i += 2) {
        if (i != 0) {
            x = gActors[i].obj.pos.x;
            z = gActors[i].obj.pos.z;
        } else {
            x = gPlayer[0].pos.x;
            z = gPlayer[0].pos.z;
        }

        temp_fs0 = fabsf(x - this->obj.pos.x);
        temp_fv0 = fabsf(z - this->obj.pos.z);

        if (!((var_fv1 < temp_fs0) || (var_fa0 < temp_fv0))) {
            var_fv1 = temp_fs0;
            var_fa0 = temp_fv0;
            actorIndex = i;
            //! FAKE:
            if (gPlayer) {}
        }

        if (i != -1) {
            x = gActors[i + 1].obj.pos.x;
            z = gActors[i + 1].obj.pos.z;
        } else {
            x = gPlayer[0].pos.x;
            z = gPlayer[0].pos.z;
        }

        temp_fs0 = fabsf(x - this->obj.pos.x);
        temp_fv0 = fabsf(z - this->obj.pos.z);

        if (!((var_fv1 < temp_fs0) || (var_fa0 < temp_fv0))) {
            var_fv1 = temp_fs0;
            var_fa0 = temp_fv0;
            actorIndex = i + 1;
        }
    }

    if (actorIndex == 0) {
        x = gPlayer[0].pos.x;
        y = gPlayer[0].pos.y;
        z = gPlayer[0].pos.z;
    } else {
        x = gActors[actorIndex].obj.pos.x;
        y = gActors[actorIndex].obj.pos.y;
        z = gActors[actorIndex].obj.pos.z;
    }
    this->fwork[0] = x;
    this->fwork[1] = y;
    this->fwork[2] = z;
    return 0;
}

s32 Bolse_8018CE5C(BoLaserCannon* this) {
    f32 x;
    f32 y;
    f32 z;

    if (this->iwork[0] == 0) {
        return 0;
    }

    if (((this->index + gGameFrameCount) % 4) == 0) {
        x = this->fwork[0] - this->obj.pos.x + RAND_FLOAT_CENTERED(100.0f);
        y = this->fwork[1] - (this->obj.pos.y + 180.0f) + RAND_FLOAT_CENTERED(100.0f);
        z = this->fwork[2] - this->obj.pos.z;

        this->fwork[6] = Math_RadToDeg(Math_Atan2F(x, z)) - this->obj.rot.y;

        if (this->fwork[6] >= 360.0f) {
            this->fwork[6] -= 360.0f;
        }
        if (this->fwork[6] < 0.0f) {
            this->fwork[6] += 360.0f;
        }
        this->fwork[5] = Math_RadToDeg(Math_Atan2F(y, sqrtf(SQ(x) + SQ(z))));
    }

    Math_SmoothStepToF(&this->rot_0F4.x, this->fwork[5], 0.1f, 4.8f, 0.1f);
    Math_SmoothStepToF(&this->rot_0F4.y, this->fwork[6], 0.1f, 4.8f, 0.1f);

    return 0;
}

bool Bolse_8018D008(BoLaserCannon* this) {
    f32 x;
    f32 y;
    f32 z;

    if (this->iwork[0] == 0) {
        return 0;
    }
    if (this->timer_0BC != 0) {
        return 0;
    }

    x = this->fwork[0] - this->obj.pos.x;
    z = this->fwork[2] - this->obj.pos.z;

    if (fabsf(x) >= 3000.0f) {
        return 0;
    }
    if (fabsf(z) >= 3000.0f) {
        return 0;
    }

    y = Math_RadToDeg(Math_Atan2F(x, z)) - this->obj.rot.y;

    if ((y > 100.0f) && (y < 259.0f)) {
        return false;
    }

    this->timer_0BC = (s32) RAND_FLOAT(20.0f) + 10;

    return true;
}

void Bolse_8018D124(BoLaserCannon* this) {
    Vec3f src;
    Vec3f dest;

    Matrix_RotateY(gCalcMatrix, (this->rot_0F4.y + this->obj.rot.y) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -this->rot_0F4.x * M_DTOR, MTXF_APPLY);

    src.y = 0.0f;
    src.x = 0.0f;
    src.z = gEnemyShotSpeed;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);
    func_effect_8007F04C(OBJ_EFFECT_ENEMY_LASER_1, this->obj.pos.x + dest.x, this->obj.pos.y + 180.0f + dest.y,
                         this->obj.pos.z + dest.z, -this->rot_0F4.x, this->rot_0F4.y + this->obj.rot.y, 0.0f, 0.0f,
                         0.0f, 0.0f, dest.x, dest.y, dest.z, 1.0f);
}

bool Bolse_8018D278(BoLaserCannon* this) {
    s32 i;

    if (this->dmgType == DMG_NONE) {
        return false;
    }

    this->dmgType = DMG_NONE;
    this->obj.pos.y += 150.0f;

    Effect386_Spawn1(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 0.0f, 0.0f, 0.0f, 8.0f, 15);

    for (i = 0; i < 3; i++) {
        if (Rand_ZeroOne() >= 0.5f) {
            Play_SpawnDebris(4, this->obj.pos.x, this->obj.pos.y, this->obj.pos.z);
        }
    }

    Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_EXPLOSION_S);

    this->itemDrop = DROP_SILVER_RING;

    Actor_Despawn(this);
    Object_Kill(&this->obj, this->sfxSource);

    this->info.bonus = 0;
    this->lockOnTimers[TEAM_ID_FOX] = 0;
    this->info.targetOffset = 0.0f;

    return true;
}

void Bolse_BoLaserCannon_Update(BoLaserCannon* this) {
    Bolse_8018CC60(this);
    if ((gPlayer[0].state != PLAYERSTATE_STANDBY) && (gPlayer[0].state != PLAYERSTATE_LEVEL_COMPLETE)) {
        Bolse_8018CCE8(this);
        Bolse_8018CE5C(this);
        if (Bolse_8018D008(this)) {
            Bolse_8018D124(this);
        }
    }
    Bolse_8018D278(this);
    this->iwork[0] = 0;
}

bool Bolse_BoLaserCannon_OverrideLimbDraw(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    BoLaserCannon* actor = (BoLaserCannon*) thisx;

    if (limbIndex == 2) {
        rot->x -= actor->rot_0F4.x;
        rot->y += actor->rot_0F4.y;
    }
    return false;
}

void Bolse_BoLaserCannon_Draw(BoLaserCannon* this) {
    Matrix_Scale(gGfxMatrix, 2.0f, 2.0f, 2.0f, MTXF_APPLY);
    Animation_GetFrameData(&aBoLaserCannonAnim, 0, this->vwork);
    Animation_DrawSkeleton(1, aBoLaserCannonSkel, this->vwork, Bolse_BoLaserCannon_OverrideLimbDraw, NULL, this,
                           &gIdentityMatrix);
    this->iwork[0] = 1;
}

s32 Bolse_8018D4F0(BoShieldReactor* this) {
    s32 i;

    for (i = 0; i < 6; i++) {
        if (D_i4_801A03E0[i].unk_18 == 0) {
            break;
        }
    }

    if (i >= 6) {
        return 0;
    }

    D_i4_801A03E0[i].unk_00 = this->obj.pos.x;
    D_i4_801A03E0[i].unk_04 = this->obj.pos.y + 730.0f;
    D_i4_801A03E0[i].unk_08 = this->obj.pos.z;
    D_i4_801A03E0[i].unk_0C = this->fwork[10];
    D_i4_801A03E0[i].unk_10 = this->fwork[11];
    D_i4_801A03E0[i].unk_14 = this->fwork[12];
    D_i4_801A03E0[i].unk_18 = 1;

    return 0;
}

bool Bolse_8018D584(BoShieldReactor* this) {
    s32 i;

    if (this->dmgType == DMG_NONE) {
        return false;
    }

    if ((this->dmgPart < 2) && (this->state == 0)) {
        this->timer_0C6 = 20;
        this->dmgType = DMG_NONE;
        AUDIO_PLAY_SFX(NA_SE_EN_DAMAGE_M, this->sfxSource, 0);
        this->health += this->damage;

        if (this->health < 100) {
            return false;
        }

        BonusText_Display(this->obj.pos.x, this->obj.pos.y + 730.0f, this->obj.pos.z, 3);
        gHitCount += 4;
        D_ctx_80177850 = 15;
        D_BO_801A03DC--;
        if (1) {}
        this->state = 1;

        Effect386_Spawn1(this->obj.pos.x, this->obj.pos.y + 730.0f, this->obj.pos.z, 0.0f, 0.0f, 0.0f, 10.0f, 15);

        for (i = 0; i < 10; i++) {
            if (!(Rand_ZeroOne() >= 0.5f)) {
                Play_SpawnDebris(4, this->obj.pos.x, this->obj.pos.y + 730.0f, this->obj.pos.z);
            }
        }

        Effect_Effect384_Spawn(this->obj.pos.x, this->obj.pos.y + 730.0f, this->obj.pos.z, 10.0f, 5);
        this->info.hitbox = SEGMENTED_TO_VIRTUAL(D_BO_6011BA4);
        Audio_KillSfxBySourceAndId(this->sfxSource, NA_SE_OB_SPARK_BEAM);
        AUDIO_PLAY_SFX(NA_SE_EN_EXPLOSION_M, this->sfxSource, 0);
    } else {
        Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_REFLECT);
    }

    return true;
}

void Bolse_BoShieldReactor_Update(BoShieldReactor* this) {
    if (gAllRangeCheckpoint != 0) {
        this->state = 1;
    }

    Bolse_8018CC60(this);

    if (this->state == 0) {
        Bolse_8018D4F0(this);
        Bolse_8018D584(this);
    } else {
        this->lockOnTimers[TEAM_ID_FOX] = 0;
        this->info.bonus = 0;
        this->info.targetOffset = 0.0f;
    }
    this->scale = -1.0f;
}

bool Bolse_BoShieldReactor_OverrideLimbDraw(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    BoShieldReactor* actor = (BoShieldReactor*) thisx;

    RCP_SetupDL(&gMasterDisp, SETUPDL_29);
    if (((limbIndex == 1) || (limbIndex == 2)) && ((actor->timer_0C6 % 2) != 0)) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_41);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 64, 64, 255);
    }
    if (((limbIndex == 1) || (limbIndex == 2)) && ((actor->health >= 100) || (gAllRangeCheckpoint != 0))) {
        *dList = NULL;
    }

    return false;
}

void Bolse_BoShieldReactor_Draw(BoShieldReactor* this) {
    Animation_GetFrameData(&aBoShieldReactorAnim, 0, this->vwork);
    Animation_DrawSkeleton(3, aBoShieldReactorSkel, this->vwork, Bolse_BoShieldReactor_OverrideLimbDraw, NULL, this,
                           gCalcMatrix);
}

s32 Bolse_8018D9CC(void) {
    s32 i;
    f32 spA8[17];
    f32 sp64[17];
    s32 j;
    Vtx* sp5C = LOAD_ASSET(D_BO_6011E28);
    Vtx* sp58 = LOAD_ASSET(D_BO_600C0B8);

    for (i = 0; i < 17; i++) {
        if ((i == 0) || (i == 16)) {
            spA8[i] = 0.0f;
            sp64[i] = 0.0f;
        } else {
            spA8[i] = RAND_FLOAT_CENTERED(400.0f);
            sp64[i] = RAND_FLOAT_CENTERED(400.0f);
        }
    }

    for (i = 0; i < 34; i++) {
        j = (sp5C[i].v.ob[2] + 200) / 25;
        sp58[i].v.ob[0] = sp5C[i].v.ob[0] + spA8[j];
        sp58[i].v.ob[1] = sp5C[i].v.ob[1] + sp64[j];
    }
    return 0;
}

s32 Bolse_8018DE8C(BoBase* this) {
    Vec3s D_i4_8019EEF8[26] = {
        { -81, 220, -4 },     { 635, 66, -362 },  { 677, 231, 1063 }, { 370, 340, 650 },   { -191, 478, -616 },
        { 30, 210, -593 },    { 1321, 83, -2 },   { 458, 340, 518 },  { -312, 478, -561 }, { 646, 66, -362 },
        { 660, 183, -1052 },  { 770, 248, 55 },   { -510, 539, -77 }, { 163, 222, 99 },    { 646, 60, 331 },
        { -506, 490, -1041 }, { 777, 248, -77 },  { -504, 581, 77 },  { 52, 216, 650 },    { -1089, 637, 1 },
        { 480, 222, -550 },   { -251, 524, 506 }, { 635, 66, 320 },   { -506, 494, 1034 }, { 304, 222, -583 },
        { -151, 496, 594 },
    };
    s32 index = RAND_FLOAT(26);

    if (!(gGameFrameCount % 2)) { // has to be ! instead of == 0
        Effect_Effect390_Spawn(D_i4_8019EEF8[index].x + this->obj.pos.x,
                               D_i4_8019EEF8[index].y + this->obj.pos.y - 10.0f,
                               D_i4_8019EEF8[index].z + this->obj.pos.z, 0.0f, 0.0f, 0.0f, 0.2f, 20);
    }

    if (!(gGameFrameCount % 5)) {
        Effect386_Spawn1(D_i4_8019EEF8[index].x + this->obj.pos.x, D_i4_8019EEF8[index].y + this->obj.pos.y - 10.0f,
                         D_i4_8019EEF8[index].z + this->obj.pos.z, 0.0f, 0.0f, 0.0f, 8.0f, 10);
    }

    return 0;
}

s32 Bolse_8018E05C(BoBase* this, s32 index) {
    s32 i;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fs2;
    f32 temp_fs3;
    f32 temp_fs4;
    f32 var_fs0;
    bool ret = false;
    Vec3f src;
    Vec3f dest;

    temp_fs4 = D_i4_801A0488[index].unk_08 * 400.0f;
    temp_fs2 = D_i4_801A0488[index].unk_0C;
    temp_fs3 = D_i4_801A0488[index].unk_14;
    temp_fs1 = D_i4_801A0488[index].unk_00;
    var_fs0 = D_i4_801A0488[index].unk_04;

    Matrix_Push(&gGfxMatrix);
    Matrix_RotateX(gCalcMatrix, -temp_fs1 * M_DTOR, MTXF_NEW);

    var_fs0 += this->obj.rot.y;
    if (var_fs0 >= 360.0f) {
        var_fs0 -= 360.0f;
    }

    Matrix_RotateY(gCalcMatrix, (-var_fs0) * M_DTOR, MTXF_APPLY);

    src.x = gPlayer[0].pos.x - (this->obj.pos.x + temp_fs2);
    src.y = gPlayer[0].pos.y - (this->obj.pos.y + 580.0f);
    src.z = gPlayer[0].trueZpos - (this->obj.pos.z + temp_fs3);

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

    if ((fabsf(dest.x) < 100.0f) && (fabsf(dest.y) < 200.0f)) {
        if ((dest.z >= 0.0f) && (dest.z < temp_fs4) && (gPlayer[0].hitTimer == 0)) {
            Player_ApplyDamage(gPlayer, 0, 40);

            if (dest.y > 0.0f) {
                gPlayer[0].knockback.y = 20.0f;
            } else {
                gPlayer[0].knockback.y = -20.0f;
            }

            for (i = 0; i < 5; i++) {
                Effect_Effect389_Spawn(gPlayer[0].pos.x + RAND_FLOAT_CENTERED(30.0f),
                                       gPlayer[0].pos.y + RAND_FLOAT(10.0f),
                                       gPlayer[0].trueZpos + RAND_FLOAT_CENTERED(30.0f), gPlayer[0].vel.x,
                                       gPlayer[0].vel.y + gPlayer[0].knockback.y, gPlayer[0].vel.z,
                                       RAND_FLOAT(0.1f) + 0.1f, gPlayer[0].num + 11);
            }

            Effect386_Spawn1(gPlayer[0].pos.x + RAND_FLOAT_CENTERED(10.0f), gPlayer[0].pos.y + RAND_FLOAT(10.0f),
                             gPlayer[0].trueZpos + RAND_FLOAT_CENTERED(10.0f), 0.0f, 15.0f, 0.0f, 2.0f, 5);
        }
        ret = true;
    }

    Matrix_Pop(&gGfxMatrix);

    return ret;
}

s32 Bolse_8018E3FC(BoBase* this) {
    s32 i;
    s32 j;
    f32 D_i4_8019EF94[6] = { 31.0f, 91.0f, 151.0f, 211.0f, 271.0f, 331.0f };
    f32 D_i4_8019EFAC[6] = { 0.0f, 840.0f, 840.0f, 0.0f, -840.0f, -840.0f };
    f32 D_i4_8019EFC4[6] = { 1000.0f, 500.0f, -500.0f, -1000.0f, -500.0f, 500.0f };
    f32 x;
    f32 y;
    f32 z;
    f32 var_fs0;
    f32 temp;

    for (i = 0; i < 6; i++) {
        if (D_i4_801A03E0[i].unk_18 == 0) {
            D_i4_801A0488[i].unk_18 = 0;
        } else {
            x = D_i4_801A03E0[i].unk_0C - this->obj.pos.x;
            var_fs0 = Math_RadToDeg(Math_Atan2F(x, D_i4_801A03E0[i].unk_14 - this->obj.pos.z));
            if (var_fs0 >= 360.0f) {
                var_fs0 = var_fs0 - 360.0f;
            }
            if (var_fs0 < 0.0f) {
                var_fs0 += 360.0f;
            }
            for (j = 0; j < 6; j++) {
                if (var_fs0 < D_i4_8019EF94[j]) {
                    break;
                } else {
                    continue;
                }
            }

            if (j < 6) {
                x = D_i4_801A03E0[i].unk_0C - (this->obj.pos.x + D_i4_8019EFAC[j]);
                y = D_i4_801A03E0[i].unk_04 - (this->obj.pos.y + 580.0f);
                z = D_i4_801A03E0[i].unk_14 - (this->obj.pos.z + D_i4_8019EFC4[j]);

                var_fs0 = Math_RadToDeg(Math_Atan2F(x, z));

                if (var_fs0 >= 360.0f) {
                    var_fs0 -= 360.0f;
                }
                if (var_fs0 < 0.0f) {
                    var_fs0 += 360.0f;
                }

                z = sqrtf(SQ(x) + SQ(z));
                temp = Math_RadToDeg(Math_Atan2F(y, z));

                D_i4_801A0488[i].unk_0C = D_i4_8019EFAC[j];
                D_i4_801A0488[i].unk_10 = 580.0f;
                D_i4_801A0488[i].unk_14 = D_i4_8019EFC4[j];
                D_i4_801A0488[i].unk_04 = var_fs0;
                D_i4_801A0488[i].unk_00 = 360.0f - temp;
                D_i4_801A0488[i].unk_18 = 1;
                D_i4_801A0488[i].unk_08 = (z / 400.0f);

                Bolse_8018E05C(this, i);

                D_i4_801A03E0[i].unk_18 = 0;
            }
        }
    }

    return 0;
}

void Bolse_BoBase_Update(BoBase* this) {
    if (this->state == 1) {
        Bolse_8018DE8C(this);
    } else if (this->swork[0] == 0) {
        this->fwork[2] += 8.0f;
        if (this->fwork[2] >= 100.0f) {
            this->swork[0] = 1;
            this->fwork[2] = 100.0f;
        }
    } else {
        this->fwork[2] -= 8.0f;
        if (this->fwork[2] <= 0.0f) {
            this->swork[0] = 0;
            this->fwork[2] = 0.0f;
        }
    }

    Bolse_8018D9CC();
    Bolse_8018E3FC(this);

    if (this->fwork[1] != 0.0f) {
        this->obj.rot.y += this->fwork[1];
        if (this->obj.rot.y >= 360.0f) {
            this->obj.rot.y -= 360.0f;
        }
    }

    this->fwork[0] += 2.0f;
    Matrix_RotateY(&D_BO_8019EE80, gBosses[0].obj.rot.y * M_DTOR, MTXF_NEW);
}

void Bolse_BoBase_Draw(BoBase* this) {
    s32 i;
    s32 alpha;

    Matrix_Scale(gGfxMatrix, this->scale, this->scale, this->scale, MTXF_APPLY);

    if (this->vwork[30].y >= 0.0f) {
        gSPDisplayList(gMasterDisp++, D_BO_6002020);
    }

    if ((gGameFrameCount % 2) != 0) {
        alpha = 128;
    } else {
        alpha = 30;
    }

    for (i = 0; i < 6; i++) {
        if (D_i4_801A0488[i].unk_18 == 0) {
            continue;
        }
        Matrix_Push(&gGfxMatrix);
        RCP_SetupDL(&gMasterDisp, SETUPDL_49);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, alpha);
        gDPSetEnvColor(gMasterDisp++, 255, 56, 56, alpha);
        Matrix_Translate(gGfxMatrix, D_i4_801A0488[i].unk_0C, D_i4_801A0488[i].unk_10, D_i4_801A0488[i].unk_14,
                         MTXF_APPLY);
        Matrix_RotateY(gGfxMatrix, D_i4_801A0488[i].unk_04 * M_DTOR, MTXF_APPLY);
        Matrix_RotateX(gGfxMatrix, D_i4_801A0488[i].unk_00 * M_DTOR, MTXF_APPLY);
        Matrix_RotateZ(gGfxMatrix, M_PI / 2, MTXF_APPLY);
        Matrix_Translate(gGfxMatrix, 1.0f, 1.0f, D_i4_801A0488[i].unk_08 * 200.0f, MTXF_APPLY);
        Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, D_i4_801A0488[i].unk_08, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, D_BO_600BF30);
        Matrix_Pop(&gGfxMatrix);
    }
}

f32 D_i4_8019EFDC[] = { 180.0f, -180.0f, 0.0f };
f32 D_i4_8019EFE8[] = { 100.0f, 200.0f, -80.0f };
f32 D_i4_8019EFF4[] = { 400.0f, 800.0f, 1200.0f };
s32 D_i4_8019F000[] = { ACTOR_CS_TEAM_ARWING, ACTOR_CS_TEAM_ARWING, ACTOR_CS_TEAM_ARWING };
f32 D_i4_8019F00C[] = { 0.0f, 80.0f, 150.0f };
f32 D_i4_8019F018[] = { 3.0f, -4.0f, 5.0f, 700.0f, 300.0f, 1000.0f };

void Bolse_8018EAEC(ActorCutscene* this, s32 index) {
    Actor_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_ACTOR_CUTSCENE;
    this->obj.pos.x = D_i4_8019EFDC[index] + gPlayer[0].pos.x;
    this->obj.pos.y = D_i4_8019EFE8[index] + gPlayer[0].pos.y;
    this->obj.pos.z = D_i4_8019EFF4[index] + gPlayer[0].pos.z;
    this->animFrame = D_i4_8019F000[index];
    this->obj.rot.y = 180.0f;
    this->vel.z = -gPlayer[0].baseSpeed;
    this->rot_0F4.z = D_i4_8019F00C[index];
    this->rot_0F4.y = D_i4_8019F018[index];
    Object_SetInfo(&this->info, this->obj.id);
    this->iwork[11] = 1;

    if (CVarGetInteger("gTeamFaces", 1) == 1) {
        // @port: Setup team faces
        this->iwork[14] = index + 2;
    }

    AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, this->sfxSource, 4);
}

void Bolse_8018EC1C(void) {
    ActorCutscene* actor = &gActors[50];

    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.pos.x = 0;
    actor->obj.pos.y = 0.0f;
    actor->obj.pos.z = -9000.0f;
    actor->animFrame = ACTOR_CS_30;
    actor->fwork[20] = 1.0f;
    actor->obj.id = OBJ_ACTOR_CUTSCENE;
    Object_SetInfo(&actor->info, actor->obj.id);
    actor->info.bonus = 1;
}

void Bolse_BoBaseShield_Setup(void) {
    BoBaseShield* boss = &gBosses[1];

    Boss_Initialize(boss);
    boss->obj.status = OBJ_INIT;
    boss->obj.pos.x = 0;
    boss->obj.pos.y = 0.0f;
    boss->obj.pos.z = -9000.0f;
    boss->obj.rot.x = 20.0f;
    boss->scale = 0.15f;
    boss->obj.id = OBJ_BOSS_BO_BASE_SHIELD;
    Object_SetInfo(&boss->info, boss->obj.id);
}

void Bolse_8018ED44(void) {
    ActorCutscene* actor = &gActors[0];
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gActors); actor++, i++) {
        if (actor->obj.status == OBJ_FREE) {
            Actor_Initialize(actor);
            actor->obj.status = OBJ_INIT;
            actor->obj.id = OBJ_ACTOR_CUTSCENE;
            actor->obj.pos.x = RAND_FLOAT_CENTERED(500.0f);
            actor->obj.pos.y = gActors[50].obj.pos.y + RAND_FLOAT(100.0f);
            actor->obj.pos.z = -9000.0f;
            actor->timer_0BC = 50;
            actor->animFrame = ACTOR_CS_31;
            actor->vel.z = 200.0f;
            Object_SetInfo(&actor->info, actor->obj.id);
            AUDIO_PLAY_SFX(NA_SE_EN_SHOT_0, actor->sfxSource, 4);
            break;
        }
    }
}

void Bolse_8018EE4C(f32 x, f32 y) {
    ActorCutscene* actor;
    s32 i;

    for (actor = &gActors[0], i = 0; i < ARRAY_COUNT(gActors); actor++, i++) {
        if (actor->obj.status == OBJ_FREE) {
            Actor_Initialize(actor);
            actor->obj.status = OBJ_INIT;
            actor->obj.id = OBJ_ACTOR_CUTSCENE;
            actor->obj.pos.x = x;
            actor->obj.pos.y = gActors[50].obj.pos.y + y;
            actor->obj.pos.z = -9000.0f;
            actor->timer_0BC = 200;
            actor->animFrame = ACTOR_CS_32;
            actor->vel.z = 80.0f;
            actor->obj.rot.z = RAND_FLOAT_CENTERED(120.0f);
            actor->rot_0F4.z = RAND_FLOAT_CENTERED(1.0f);
            Object_SetInfo(&actor->info, actor->obj.id);
            AUDIO_PLAY_SFX(NA_SE_EN_SHOT_0, actor->sfxSource, 4);
            break;
        }
    }
}

Vec3f D_i4_8019F030[] = {
    { -500.0f, 500.0f, 500.0f },
    { 100.0f, 200.0f, 1500.0f },
    { 8000.0f, 200.0f, 0.0f },
};
Vec3f D_i4_8019F054[] = {
    { -8000.0f, 200.0f, 0.0f },
    { 300.0f, 5000.0f, 0.0f },
};
f32 D_i4_8019F06C[] = { -300.0f, 300.0f, 50.0f };
f32 D_i4_8019F078[] = { -30.0f, -60.0f, -90.0f };
f32 D_i4_8019F084[] = { 200.0f, 260.0f, 400.0f };
f32 D_i4_8019F090[] = { 70.0f, -80.0f, -65.0f };

void Bolse_LevelStart(Player* player) {
    s32 i;
    f32 sp60 = 0.0f;
    Vec3f src;
    Vec3f dest;
    ActorCutscene* actor;
    s32 pad[4];

    switch (player->csState) {
        case 0:
            gLight1R = 100;
            gLight1G = 100;
            gLight1B = 80;

            gAmbientR = 0;
            gAmbientG = 15;
            gAmbientB = 30;

            gStarCount = 1000;

            gCsFrameCount = 0;

            player->pos.x = 0;
            player->pos.z = 0;
            player->pos.y = 0;

            player->baseSpeed = 30.0f;

            if (gTeamShields[TEAM_ID_FALCO] > 0) {
                Bolse_8018EAEC(&gActors[0], 0);
            }
            if (gTeamShields[TEAM_ID_SLIPPY] > 0) {
                Bolse_8018EAEC(&gActors[1], 1);
            }
            if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                Bolse_8018EAEC(&gActors[2], 2);
            }

            Bolse_8018EC1C();
            Bolse_BoBaseShield_Setup();

            D_ctx_80177A48[1] = -13000.0f;
            D_ctx_80177A48[2] = -13000.0f;
            D_ctx_80177A48[4] = -22000.0f;

            gCsCamEyeX = player->pos.x - 150;
            gCsCamEyeY = player->pos.y;
            gCsCamEyeZ = player->pos.z - 500.0f;

            gCsCamAtX = 0.0f;
            gCsCamAtY = player->pos.y;
            gCsCamAtZ = player->pos.z;

            player->csState = 1;
            player->wingPosition = 1;

            D_ctx_80177A48[0] = 1.0f;
            gFillScreenAlpha = gFillScreenAlphaTarget = 255;
            break;

        case 1:
            gFillScreenAlphaTarget = 0;
            gCsCamAtX = 0.0f;
            gCsCamAtY = player->pos.y;
            gCsCamAtZ = player->pos.z;
            D_ctx_80177A48[2] += 4.5f;
            sp60 = SIN_DEG(D_ctx_80177A48[2]) * 10.0f;
            player->rot.z = SIN_DEG(D_ctx_80177A48[2]) * -60.0f;

            if (((gCsFrameCount % 8) == 0) && (Rand_ZeroOne() < 0.5f)) {
                Bolse_8018ED44();
            }

            switch (gCsFrameCount) {
                case 2:
                    Bolse_8018EE4C(600.0f, -100.0f);
                    break;
                case 30:
                    Bolse_8018EE4C(400.0f, 0.0f);
                    break;

                case 40:
                    Bolse_8018EE4C(0.0f, 100.0f);
                    break;

                case 50:
                    Bolse_8018EE4C(-200.0f, 200.0f);
                    break;

                case 70:
                    Bolse_8018EE4C(200.0f, -300.0f);
                    break;

                case 80:
                    Bolse_8018EE4C(700.0f, 400.0f);
                    break;

                case 85:
                    Bolse_8018EE4C(600.0f, -200.0f);
                    break;

                case 100:
                    Bolse_8018EE4C(-500.0f, 0.0f);
                    break;

                case 120:
                    Bolse_8018EE4C(-500.0f, 0.0f);
                    break;

                case 127:
                    Play_ClearObjectData();
                    Bolse_LoadLevelObjects();
                    ActorAllRange_SpawnTeam();

                    player->csState = 2;

                    player->pos.x = 0.0f;
                    player->pos.y = 1400.0f;
                    player->pos.z = 14000.0f;

                    player->rot.x = -8.0f;

                    for (i = 0, actor = &gActors[1]; i < 3; i++, actor++) {
                        actor->obj.pos.x = D_i4_8019F030[i - 1].x + player->pos.x;
                        actor->obj.pos.y = D_i4_8019F030[i - 1].y + player->pos.y;
                        actor->obj.pos.z = D_i4_8019F030[i - 1].z + player->pos.z;
                        actor->rot_0F4.x = 352.0f;
                        actor->state = 1;
                        actor->timer_0BC = 1000;
                    }

                    gCsCamEyeX = -200.0f;
                    gCsCamEyeY = 700.0f;
                    gCsCamEyeZ = 12000.0f;
                    gCsCamAtX = player->pos.x;
                    gCsCamAtY = player->pos.y;
                    gCsCamAtZ = player->pos.z;
                    gStarCount = 300;
                    gDrawGround = true;

                    gLight1R = 200;
                    gLight1G = 80;
                    gLight1B = 110;

                    gAmbientR = 150;
                    gAmbientG = 30;
                    gAmbientB = 30;

                    Radio_PlayMessage(gMsg_ID_11010, RCID_FOX);
            }
            break;

        case 2:
            gCsCamEyeZ += player->vel.z * 0.2f;
            gCsCamAtX = player->pos.x;
            gCsCamAtY = player->pos.y;
            gCsCamAtZ = player->pos.z;

            Math_SmoothStepToF(&player->rot.z, 0.0f, 0.1f, 1.0f, 0.0f);

            if (gCsFrameCount == 200) {
                player->wingPosition = 2;
            }

            if (gCsFrameCount == 270) {
                player->state = PLAYERSTATE_ACTIVE;
                player->baseSpeed = gArwingSpeed;
                player->unk_014 = 0.0001f;

                for (i = 0, actor = &gActors[1]; i < 3; i++, actor++) {
                    actor->fwork[4] = D_i4_8019F054[i - 1].x;
                    actor->fwork[5] = D_i4_8019F054[i - 1].y;
                    actor->fwork[6] = D_i4_8019F054[i - 1].z;
                    actor->state = 3;
                    actor->timer_0BC = 80;
                }
                AUDIO_PLAY_BGM(gBgmSeqId);
                gLevelStartStatusScreenTimer = 80;
            }
            break;
    }

    Matrix_RotateY(gCalcMatrix, (player->rot.y + 180.0f) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -(player->rot.x * M_DTOR), MTXF_APPLY);

    src.x = 0.0f;
    src.y = 0;
    src.z = player->baseSpeed;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

    player->vel.x = dest.x + sp60;
    player->vel.z = dest.z;
    player->vel.y = dest.y;

    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;
    player->pos.z += player->vel.z;

    player->trueZpos = player->pos.z;
    player->bankAngle = (player->rot.z + player->zRotBank) + player->zRotBarrelRoll;

    Math_SmoothStepToF(&player->cam.eye.x, gCsCamEyeX, D_ctx_80177A48[0], 50000.0f, 0);
    Math_SmoothStepToF(&player->cam.eye.y, gCsCamEyeY, D_ctx_80177A48[0], 50000.0f, 0);
    Math_SmoothStepToF(&player->cam.eye.z, gCsCamEyeZ, D_ctx_80177A48[0], 50000.0f, 0);
    Math_SmoothStepToF(&player->cam.at.x, gCsCamAtX, D_ctx_80177A48[0], 50000.0f, 0);
    Math_SmoothStepToF(&player->cam.at.y, gCsCamAtY, D_ctx_80177A48[0], 50000.0f, 0);
    Math_SmoothStepToF(&player->cam.at.z, gCsCamAtZ, D_ctx_80177A48[0], 50000.0f, 0);
}

void Bolse_8018F83C(Actor* this, s32 index) {
    Actor_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_ACTOR_CUTSCENE;
    this->obj.pos.x = D_i4_8019F06C[index] + gPlayer[0].pos.x;
    this->obj.pos.y = D_i4_8019F078[index] + gPlayer[0].pos.y;
    this->obj.pos.z = D_i4_8019F084[index] + gPlayer[0].pos.z;
    this->obj.rot.y = 180.0f;
    this->obj.rot.z = D_i4_8019F090[index];
    this->vel.z = -gPlayer[0].baseSpeed;
    Object_SetInfo(&this->info, this->obj.id);
    this->iwork[11] = 1;

    if (CVarGetInteger("gTeamFaces", 1) == 1) {
        // @port: Setup team faces
        this->iwork[14] = index + 2;
    }

    AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, this->sfxSource, 4);
}

void Bolse_LevelComplete(Player* player) {
    f32 sp8C;
    f32 sp88;
    s32 i;
    Actor* actor50 = &gActors[50];
    Vec3f sp74;
    Vec3f sp68;
    s32 pad;

    Math_SmoothStepToF(&player->boostSpeed, 0.0f, 0.1f, 1.5f, 0.0f);

    sp8C = 100.0f;
    sp88 = 100.0f;

    switch (player->csState) {
        case 0:
            Audio_StopSfxByBankAndSource(1, player->sfxSource);
            gCsFrameCount = 0;
            D_i4_801A03D0 = 100.0f;
            D_i4_801A03D4 = 100.0f;
            D_i4_801A03D8 = 80.0f;

            Math_SmoothStepToF(&player->rot.y, -40.0f, 0.1f, 2.5f, 0.0f);
            Math_SmoothStepToF(&player->rot.z, -60.0f, 0.2f, 5.0f, 0.0f);
            Math_SmoothStepToF(&player->rot.x, 0.0f, 0.1f, 2.5f, 0.0f);

            if (player->csTimer == 0) {
                player->csState = 1;
                player->csTimer = 200;
                AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, player->sfxSource, 0);
                player->unk_194 = 5.0f;
                player->unk_190 = 5.0f;
                gProjectFar = 30000.0f;
            }
            break;

        case 1:
            player->unk_190 = 2.0f;

            Math_SmoothStepToF(&player->rot.x, 15.0f, 0.1f, 0.4f, 0.0f);
            Math_SmoothStepToF(&player->rot.z, 40.0f, 0.2f, 5.0f, 0.0f);
            Math_SmoothStepToF(&player->rot.y, 120.0f, 0.1f, 2.0f, 0.0f);

            player->baseSpeed += 1.0f;
            if (player->baseSpeed >= 70.0f) {
                player->baseSpeed = 70.0f;
            }

            if (player->csTimer == 0) {
                player->csState = 5;
                player->csTimer = 1000;
                Audio_StopPlayerNoise(0);
                Audio_KillSfxBySource(player->sfxSource);
                Play_ClearObjectData();

                for (i = 0; i < 200; i++) {
                    gScenery360[i].obj.status = OBJ_FREE;
                }

                Bolse_8018EC1C();

                player->pos.x = actor50->obj.pos.x;
                player->pos.y = actor50->obj.pos.y;
                player->pos.z = actor50->obj.pos.z - 1000.0f;

                player->rot.x = 0.0f;
                player->rot.z = 0.0f;
                player->rot.y = 0.0f;
                player->yRot_114 = 0.0f;
                player->baseSpeed = 40.0f;

                if (gTeamShields[TEAM_ID_FALCO] > 0) {
                    Bolse_8018F83C(&gActors[0], 0);
                }
                if (gTeamShields[TEAM_ID_SLIPPY] > 0) {
                    Bolse_8018F83C(&gActors[1], 1);
                }
                if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                    Bolse_8018F83C(&gActors[2], 2);
                }

                D_ctx_80177A48[0] = 1.0f;
                gStarCount = 1000;
                gDrawGround = false;
                gCsCamEyeY = 0;
                gCsCamEyeX = 200.0f;
                gCsCamEyeZ = -15000.0f;
                gCsCamAtX = gPlayer[0].pos.x;
                gCsCamAtY = gPlayer[0].pos.y;
                gCsCamAtZ = gPlayer[0].pos.z;
                gFillScreenAlpha = gFillScreenAlphaTarget = 255;
                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 50);
                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 50);
                gCsFrameCount = 0;
                gGroundHeight = -10000.0f;
                player->hideShadow = true;
                player->arwing.drawFace = true;
                AUDIO_PLAY_SFX(NA_SE_EN_ANDROSS_EXPLOSION, actor50->sfxSource, 0);
                Audio_StartPlayerNoise(0);
            }
            break;

        case 5:
            gFillScreenAlpha = gFillScreenAlphaTarget = 0;
            player->csState = 10;

        case 10:
            gCsCamAtX = gPlayer[0].pos.x;
            gCsCamAtY = gPlayer[0].pos.y;
            gCsCamAtZ = gPlayer[0].pos.z;

            actor50->obj.pos.y -= 5;

            if (gCsFrameCount < 92) {
                if ((gGameFrameCount % 2U) == 0) {
                    Effect_Effect389_Spawn(actor50->obj.pos.x + RAND_FLOAT_CENTERED(1000.0f),
                                           actor50->obj.pos.y + 100.0f,
                                           actor50->obj.pos.z + RAND_FLOAT_CENTERED(1000.0f), 0.0f, 0.0f, 0.0f,
                                           RAND_FLOAT(0.4f) + 0.4f, 0.0f);
                }
                if ((gGameFrameCount % 2U) == 0) {
                    //! FAKE:
                    do {
                    } while (0);

                    Effect386_Spawn1(RAND_FLOAT_CENTERED(1000.0f) + actor50->obj.pos.x, actor50->obj.pos.y + 100.0f,
                                     RAND_FLOAT_CENTERED(1000.0f) + actor50->obj.pos.z, 0.0f, 0.0f, 0.0f, 10.0f, 5.0f);
                }
            }

            if ((gCsFrameCount > 110) && (gCsFrameCount < 200)) {
                D_ctx_801779A8[0] = 60.0f;
            }

            switch (gCsFrameCount) {
                case 160:
                    AUDIO_PLAY_BGM(NA_BGM_COURSE_CLEAR);
                    break;

                case 92:
                    gScreenFlashTimer = 8;
                    break;

                case 95:
                    Audio_KillSfxBySource(actor50->sfxSource);
                    AUDIO_PLAY_SFX(NA_SE_EN_BOSS_EXPLOSION, gActors[0].sfxSource, 0);

                    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
                        Object_Kill(&gEffects[i].obj, gEffects[i].sfxSource);
                    }

                    Effect_Effect384_Spawn(actor50->obj.pos.x, actor50->obj.pos.y, actor50->obj.pos.z, 400.0f, 4);
                    break;

                case 100:
                case 105:
                case 110:
                    Effect_Effect384_Spawn(actor50->obj.pos.x, actor50->obj.pos.y, actor50->obj.pos.z, 250.0f, 6);
                    break;

                case 130:
                    for (i = 0; i < 100; i++) {
                        func_effect_80079618(RAND_FLOAT_CENTERED(300.0f) + actor50->obj.pos.x,
                                             actor50->obj.pos.y - RAND_FLOAT(2000.0f),
                                             RAND_FLOAT_CENTERED(300.0f) + actor50->obj.pos.z, 5.11f);
                    };

                    for (i = 0; i < 100; i++) {
                        Effect_Effect357_Spawn95(RAND_FLOAT_CENTERED(300.0f) + actor50->obj.pos.x,
                                                 actor50->obj.pos.y - RAND_FLOAT(2000.0f),
                                                 RAND_FLOAT_CENTERED(300.0f) + actor50->obj.pos.z, 5.11f);
                    };
                    actor50->work_046 = 1;
                    break;

                case 235:
                    player->wingPosition = 1;
                    gLevelClearScreenTimer = 100;
                    break;

                case 240:
                    player->csState++;
                    D_ctx_80177A48[0] = 0;
                    D_ctx_80177A48[5] = 20.0f;
                    D_ctx_80177A48[6] = 0.0f;
                    break;
            }

            if ((gCsFrameCount > 100) && (gCsFrameCount < 200)) {
                gEnvLightxRot = 0.0f;
                sp8C = 255.0f;
                gEnvLightyRot = 16.0f;
                gEnvLightzRot = 0.0f;
                sp88 = 255.0f;
            } else {
                gEnvLightxRot = -80.0f;
                gEnvLightyRot = 60.0f;
                gEnvLightzRot = 0.0f;
            }
            gCsCamEyeZ += gPlayer[0].vel.z * 0.3f;
            break;

        case 11:
            D_ctx_80177A48[5] += D_ctx_80177A48[6];

            if (gCsFrameCount < 680) {
                gCsCamEyeZ += gPlayer[0].vel.z * 0.3f;
                Math_SmoothStepToF(&D_ctx_80177A48[6], 0.7f, 0.1f, 0.005f, 0.0f);
                gActors[0].vel.z = gActors[1].vel.z = gActors[2].vel.z = player->vel.z;
            } else {
                Math_SmoothStepToF(&D_ctx_80177A48[6], 0.0f, 0.1f, 0.005f, 0.0f);
            }

            Math_SmoothStepToF(&player->baseSpeed, 0.0f, 0.1f, 1.5f, 0.0f);
            Math_SmoothStepToF(D_ctx_80177A48, 0.2f, 1.0f, 0.001f, 0.0f);
            Matrix_RotateY(gCalcMatrix, D_ctx_80177A48[5] * M_DTOR, MTXF_NEW);
            Matrix_RotateX(gCalcMatrix, 0, MTXF_APPLY);

            sp74.x = 0.0f;
            sp74.y = 0.0f;
            sp74.z = 800.0f;

            Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp74, &sp68);

            gCsCamEyeX = gPlayer[0].pos.x + sp68.x;
            gCsCamEyeY = gPlayer[0].pos.y + sp68.y;
            gCsCamEyeZ = gPlayer[0].pos.z + 200.0f + sp68.z;
            gCsCamAtX = gPlayer[0].pos.x;
            gCsCamAtY = gPlayer[0].pos.y;
            gCsCamAtZ = gPlayer[0].pos.z + 200.0f;

            switch (gCsFrameCount) {
                case 740:
                    gActors[0].state = 1;
                    break;

                case 760:
                    gActors[1].state = 1;
                    break;

                case 780:
                    gActors[2].state = 1;
                    break;

                case 800:
                    player->csState++;
                    player->csTimer = 50;
                    player->unk_194 = 5.0f;
                    player->unk_190 = 5.0f;
                    AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, player->sfxSource, 0);
                    break;
            }
            break;

        case 12:
            gCsCamAtX = gPlayer[0].pos.x;
            gCsCamAtY = gPlayer[0].pos.y;
            gCsCamAtZ = gPlayer[0].pos.z + 200.0f;

            player->unk_190 = 2.0f;
            player->baseSpeed += 5;

            if (player->csTimer == 30) {
                Audio_FadeOutAll(30);
            }

            if (player->csTimer == 0) {
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
                gFillScreenAlphaTarget = 255;
                if (gFillScreenAlpha == 255) {
                    gSavedGoldRingCount[0] = gGoldRingCount[0];
                    gNextGameState = GSTATE_PLAY;
                    gNextLevel = LEVEL_VENOM_1;
                    Audio_StopPlayerNoise(0);
                    Audio_KillSfxBySource(player->sfxSource);
                    gLeveLClearStatus[LEVEL_BOLSE] = Play_CheckMedalStatus(150) + 1;

                    for (i = TEAM_ID_FALCO; i < TEAM_ID_MAX; i++) {
                        gPrevPlanetTeamShields[i] = gTeamShields[i];
                        gPrevPlanetSavedTeamShields[i] = gSavedTeamShields[i];
                        gSavedTeamShields[i] = gTeamShields[i];
                    }

                    for (i = TEAM_ID_FALCO; i <= TEAM_ID_PEPPY; i++) {
                        if (gPrevPlanetTeamShields[i] == 0) {
                            gPrevPlanetTeamShields[i] = 255;
                        }
                    }
                    HUD_Bolse_Area6_SaveData();
                }
            }
            break;
    }

    switch (gCsFrameCount) {
        case 400:
            gShowLevelClearStatusScreen = true;
            break;

        case 600:
            gShowLevelClearStatusScreen = false;
            break;

        case 620:
            Radio_PlayMessage(gMsg_ID_11200, RCID_FOX);
            break;
    }

    if (actor50->work_046 != 0) {
        Math_SmoothStepToF(&actor50->fwork[20], 3.0f, 0.03f, 0.01f, 0);
        if ((gGameFrameCount % 2U) == 0) {
            Effect_Effect389_Spawn(
                RAND_FLOAT_CENTERED(5000.0f) + actor50->obj.pos.x, RAND_FLOAT_CENTERED(5000.0f) + actor50->obj.pos.y,
                RAND_FLOAT_CENTERED(5000.0f) + actor50->obj.pos.z, 0.0f, 0.0f, 0.0f, RAND_FLOAT(0.8f) + 0.8f, 0);
        }
        if ((gGameFrameCount % 2U) == 0) {
            Effect386_Spawn1(
                RAND_FLOAT_CENTERED(5000.0f) + actor50->obj.pos.x, RAND_FLOAT_CENTERED(5000.0f) + actor50->obj.pos.y,
                RAND_FLOAT_CENTERED(5000.0f) + actor50->obj.pos.z, 0.0f, 0.0f, 0.0f, RAND_FLOAT(10.0f) + 20.0f, 5);
        }
    }

    Math_SmoothStepToF(&D_i4_801A03D0, sp8C, 1.0f, 2.0f, 0.0f);
    Math_SmoothStepToF(&D_i4_801A03D4, sp88, 1.0f, 2.0f, 0.0f);
    Math_SmoothStepToF(&D_i4_801A03D8, 80.0f, 1.0f, 2.0f, 0.0f);

    gLight1R = D_i4_801A03D0;
    gLight1G = D_i4_801A03D4;
    gLight1B = D_i4_801A03D8;

    Matrix_RotateY(gCalcMatrix, (player->yRot_114 + player->rot.y + 180.0f) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -((player->xRot_120 + player->rot.x + player->aerobaticPitch) * M_DTOR), MTXF_APPLY);

    sp74.x = 0.0f;
    sp74.y = 0.0f;
    sp74.z = player->baseSpeed + player->boostSpeed;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp74, &sp68);

    player->vel.x = sp68.x;
    player->vel.z = sp68.z;
    player->vel.y = sp68.y;

    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;
    player->pos.z += player->vel.z;

    player->trueZpos = player->pos.z;
    player->bankAngle = player->rot.z + player->zRotBank + player->zRotBarrelRoll;

    if (player->csState < 10) {
        Math_SmoothStepToF(&player->zRotBarrelRoll, 0.0f, 0.1f, 15.0f, 0.0f);
        Math_SmoothStepToF(&player->zRotBank, 0.0f, 0.1f, 15.0f, 0.0f);
        Math_SmoothStepToF(&player->camRoll, 0.0f, 0.1f, 3.0f, 0.0f);

        Math_SmoothStepToAngle(&player->aerobaticPitch, 0.0f, 0.1f, 20.0f, 0.0f);

        if (player->pos.y < 700.0f) {
            Math_SmoothStepToF(&player->pos.y, 700.0f, 0.1f, 10.0f, 0.0f);
        }

        Camera_Update360(player, false);

        player->cam.eye.x += player->vel.x * 0.1f;
        player->cam.eye.y += player->vel.y * 0.1f;
        player->cam.eye.z += player->vel.z * 0.1f;
    } else {
        Math_SmoothStepToF(&player->cam.eye.x, gCsCamEyeX, D_ctx_80177A48[0], 50000, 0);
        Math_SmoothStepToF(&player->cam.eye.y, gCsCamEyeY, D_ctx_80177A48[0], 50000, 0);
        Math_SmoothStepToF(&player->cam.eye.z, gCsCamEyeZ, D_ctx_80177A48[0], 50000, 0);
        Math_SmoothStepToF(&player->cam.at.x, gCsCamAtX, D_ctx_80177A48[0], 50000, 0);
        Math_SmoothStepToF(&player->cam.at.y, gCsCamAtY, D_ctx_80177A48[0], 50000, 0);
        Math_SmoothStepToF(&player->cam.at.z, gCsCamAtZ, D_ctx_80177A48[0], 50000, 0);
    }
    player->bobPhase += 10.0f;
    player->yBob = -SIN_DEG(player->bobPhase) * 0.3f;
    player->rockPhase += 8.0f;
    player->rockAngle = SIN_DEG(player->rockPhase);
}

void Bolse_Effect397_Setup1(Effect397* this, f32 xPos, f32 yPos, f32 zPos, f32 xRot, f32 yRot) {
    Vec3f src;
    Vec3f dest;

    Effect_Initialize(this);
    this->obj.status = OBJ_ACTIVE;
    this->obj.id = OBJ_EFFECT_397;
    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;
    this->obj.rot.x = xRot;
    this->obj.rot.y = yRot;
    this->scale2 = 1.0f;
    Matrix_RotateY(gCalcMatrix, M_DTOR * yRot, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, M_DTOR * xRot, MTXF_APPLY);
    src.x = 0.0f;
    src.y = 0.0f;
    src.z = 200.0f;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);
    this->vel.x = dest.x;
    this->vel.y = dest.y;
    this->vel.z = dest.z;
    this->timer_50 = 60;
    AUDIO_PLAY_SFX(NA_SE_EN_LONG_BEAM, this->sfxSource, 4);
    Object_SetInfo(&this->info, this->obj.id);
}

void Bolse_Effect397_Spawn1(f32 x, f32 y, f32 z, f32 arg3, f32 arg4) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Bolse_Effect397_Setup1(&gEffects[i], x, y, z, arg3, arg4);
            break;
        }
    }
}

void Bolse_Effect397_Setup2(Effect397* this, f32 x, f32 y, f32 z, f32 scale) {
    Effect_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_EFFECT_397;
    this->obj.pos.x = x;
    this->obj.pos.y = y;
    this->obj.pos.z = z;
    this->state = 1;
    this->scale1 = scale;
    this->unk_44 = 255;
    Object_SetInfo(&this->info, this->obj.id);
    this->info.unk_14 = 1;
}

void Bolse_Effect397_Spawn2(f32 x, f32 y, f32 z, f32 scale) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Bolse_Effect397_Setup2(&gEffects[i], x, y, z, scale);
            break;
        }
    }
}

void Bolse_Effect397_Update(Effect397* this) {
    switch (this->state) {
        case 0:
            if (gPlayer[0].barrelRollAlpha == 0) {
                func_effect_8007A774(gPlayer, this, 150.0f);
            }

            Math_SmoothStepToF(&this->scale2, 30.0f, 1.0f, 10.0f, 0.0f);

            if (this->timer_50 == 0) {
                Object_Kill(&this->obj, this->sfxSource);
            }

            if (this->obj.pos.y < gGroundHeight + 50.0f) {
                Bolse_Effect397_Spawn2(this->obj.pos.x, gGroundHeight + 50.0f, this->obj.pos.z, 3.0f);
                Object_Kill(&this->obj, this->sfxSource);
            }
            break;

        case 1:
            Math_SmoothStepToF(&this->scale2, this->scale1, 0.1f, 20.0f, 0.0f);
            this->unk_44 -= 20;
            if (this->unk_44 < 0) {
                Object_Kill(&this->obj, this->sfxSource);
            }
            break;
    }
}

void Bolse_Effect397_Draw(Effect397* this) {
    switch (this->state) {
        case 0:
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 192);
            Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, this->scale2, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_BO_6006910);
            break;

        case 1:
            RCP_SetupDL(&gMasterDisp, SETUPDL_67);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, this->unk_44);
            gDPSetEnvColor(gMasterDisp++, 0, 128, 255, this->unk_44);
            Matrix_Scale(gGfxMatrix, this->scale2, this->scale2, this->scale2, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, aOrbDL);
            RCP_SetupDL(&gMasterDisp, SETUPDL_64);
            break;
    }
}

f32 D_i4_8019F09C[12] = { 0.0f, 0.0f, 60.0f, 60.0f, 120.0f, 120.0f, 180.0f, 180.0f, 240.0f, 240.0f, 300.0f, 300.0f };

void Bolse_BoBaseCore_Update(BoBaseCore* this) {
    s32 i;
    Vec3f src;
    Vec3f dest;

    if ((gGameFrameCount & 0x18) != 0) {
        Math_SmoothStepToF(&D_i4_8019EEC0, 0.0f, 1.0f, 30.0f, 0);
    } else {
        Math_SmoothStepToF(&D_i4_8019EEC0, 255.0f, 1.0f, 30.0f, 0);
    }

    switch (this->state) {
        case 0:
            if (gAllRangeCheckpoint == 2) {
                this->state = 1;
            }
            this->dmgType = DMG_NONE;
            gBossFrameCount = 0;
            break;

        case 1:
            if (((gHitCount - gActors[0].iwork[1]) >= 5) || (D_i4_801A0530 > 8000)) {
                this->state = 2;
                Radio_PlayMessage(gMsg_ID_11150, RCID_PEPPY);
                this->timer_050 = 1000;
                AUDIO_PLAY_SFX(NA_SE_BO_CORE_APPEAR, this->sfxSource, 0);
            }
            break;

        case 2:
            gBossFrameCount++;
            Math_SmoothStepToF(&this->obj.pos.y, 0.0f, 0.1f, 10.0f, 0);
            this->obj.rot.y += 1.0f;
            if (this->timer_050 == 1) {
                this->timer_050 = 2000;
                Radio_PlayMessage(gMsg_ID_11160, RCID_PEPPY);
                Audio_KillSfxBySourceAndId(this->sfxSource, NA_SE_BO_CORE_APPEAR);
            }
            break;

        case 10:
            Math_SmoothStepToF(&this->obj.pos.y, -500.0f, 0.1f, 5.0f, 0);
            this->obj.rot.y += 1.0f;
            break;
    }

    for (i = 0; i < 8; i++) {
        if (this->swork[12 + i] != 0) {
            this->swork[12 + i]--;
            if (this->swork[12 + i] == 1000) {
                this->swork[12 + i] = 0;
            }
        }
    }

    if (this->state == 2) {
        if (this->dmgType != DMG_NONE) {
            this->dmgType = DMG_NONE;

            if (this->damage >= 16) {
                this->damage = 3;
            }

            if (this->dmgPart < 8) {
                this->swork[this->dmgPart] -= this->damage;
                if (this->swork[this->dmgPart] <= 0) {
                    this->swork[24 + this->dmgPart] = 30;
                    AUDIO_PLAY_SFX(NA_SE_EN_EXPLOSION_M, this->sfxSource, 4);
                    this->swork[36]--;
                    if (this->swork[36] <= 0) {
                        this->state = 10;
                        gBosses[0].state = 1;
                    }
                    this->obj.pos.y += 300.0f;
                    Boss_AwardBonus(this);
                    this->obj.pos.y -= 300.0f;
                } else {
                    this->swork[12 + this->dmgPart] = 20;
                    AUDIO_PLAY_SFX(NA_SE_OB_DAMAGE_M, this->sfxSource, 4);
                }
            }
        }

        Matrix_RotateY(gCalcMatrix, -this->obj.rot.y * M_DTOR, MTXF_NEW);

        for (i = 0; i < 8; i++) {
            if (this->swork[i + 24] != 0) {
                this->swork[i + 24]--;
                if ((gGameFrameCount % 2) == 0) {
                    Effect_FireSmoke_Spawn2(this->vwork[i].x, this->vwork[i].y, this->vwork[i].z,
                                            this->vwork[i].x * 0.2f, 0.0f, this->vwork[i].z * 0.2f, 5.0f);
                }
            }

            if (this->swork[i] <= 0) {
                this->info.hitbox[i * 6 + 4] = -200.0f;
                if (((gGameFrameCount + i) % 8) == 0) {
                    Bolse_Effect397_Spawn1(this->vwork[i].x, this->vwork[i].y, this->vwork[i].z,
                                           RAND_FLOAT_CENTERED(30.0f),
                                           this->obj.rot.y + D_i4_8019F09C[i] + RAND_FLOAT_CENTERED(30.0f));
                    this->swork[i + 12] = 1003;
                }
            } else {
                src.x = this->vwork[i].x - this->obj.pos.x;
                src.y = this->vwork[i].y - this->obj.pos.y;
                src.z = this->vwork[i].z - this->obj.pos.z;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);
                this->info.hitbox[i * 6 + 4] = 50.0f;
                this->info.hitbox[i * 6 + 5] = dest.x;
                this->info.hitbox[i * 6 + 3] = dest.y;
                this->info.hitbox[i * 6 + 1] = dest.z;
            }
        }
    }
}

bool Bolse_BoBaseCore_OverrideLimbDraw(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    BoBaseCore* baseCore = (BoBaseCore*) thisx;

    RCP_SetupDL(&gMasterDisp, SETUPDL_29);

    switch (limbIndex) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            RCP_SetupDL(&gMasterDisp, SETUPDL_41);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, (s32) D_i4_8019EEC0, 255);
            if (baseCore->swork[limbIndex - 1] <= 0) {
                *dList = NULL;
            }
            break;

        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
            if ((baseCore->swork[3 + limbIndex] % 2) != 0) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_41);
                if (baseCore->swork[3 + limbIndex] > 1000) {
                    gDPSetPrimColor(gMasterDisp++, 0, 0, 64, 64, 255, 255);
                } else {
                    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 0, 0, 255);
                }
            }
            if (baseCore->swork[0 + limbIndex - 9] <= 0) {
                *dList = D_BO_6009BC0;
            }
            break;
    }
    return false;
}

void Bolse_BoBaseCore_PostLimbDraw(s32 index, Vec3f* vec, void* thisx) {
    Vec3f src = { 0.0f, 0.0f, 0.0f };
    BoBaseCore* baseCore = (BoBaseCore*) thisx;

    switch (index) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            Matrix_MultVec3f(gCalcMatrix, &src, &baseCore->vwork[index - 1]);
            break;
    }
}

void Bolse_BoBaseCore_Draw(BoBaseCore* this) {
    Animation_GetFrameData(&aBoBaseCoreAnim, 0, this->vwork);
    if (this->state >= 2) {
        Animation_DrawSkeleton(3, aBoBaseCoreSkel, this->vwork, Bolse_BoBaseCore_OverrideLimbDraw,
                               Bolse_BoBaseCore_PostLimbDraw, this, gCalcMatrix);
    } else {
        Animation_DrawSkeleton(3, aBoBaseCoreSkel, this->vwork, NULL, NULL, this, gCalcMatrix);
    }
}

void Bolse_BoBaseShield_Update(BoBaseShield* this) {
    D_i4_801A0530 = 0;

    Math_SmoothStepToF(&this->fwork[0], D_BO_801A03DC * 9.0f + 10.0f, 1.0f, 10.0f, 0.0f);

    Lib_Texture_Scroll(aBoBaseShieldTex, 16, 16, 0);
    Lib_Texture_Scroll(aBoBaseShieldTex, 16, 16, 0);

    switch (this->state) {
        case 2:
            break;

        case 0:
            if (D_BO_801A03DC == 0) {
                this->timer_052 = 130;
                this->state = 1;
                Radio_PlayMessage(gMsg_ID_11050, RCID_FOX);
                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 1);
                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 1);
            }
            break;

        case 1:
            Math_SmoothStepToF(&gBosses[0].fwork[1], 0.0f, 1.0f, 0.01f, 0.001f);
            if (this->timer_052 == 0) {
                this->state = 2;
                AUDIO_PLAY_SFX(NA_SE_OB_BARRIER_RELEASE, this->sfxSource, 0);
            }
            break;
    }

    if (gGroundClipMode == 0) {
        if ((gGameFrameCount % 2) == 0) {
            gLight3Brightness = 0.0f;
        } else {
            gLight3Brightness = 0.5f;
        }
        gLight3x = this->obj.pos.x;
        gLight3y = this->obj.pos.y;
        gLight3z = this->obj.pos.z;
        gLight3R = 255;
        gLight3G = 128;
        gLight3B = 128;
    }
}

void Bolse_BoBaseShield_Draw(BoBaseShield* this) {
    s32 alpha;

    Matrix_Scale(gGfxMatrix, this->scale, this->scale, this->scale, MTXF_APPLY);

    alpha = this->fwork[0];
    if (alpha != 0) {
        if ((gGameFrameCount % 2) == 0) {
            alpha *= 1.7f;
        }
        RCP_SetupDL(&gMasterDisp, SETUPDL_41);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, alpha);
        Matrix_Scale(gGfxMatrix, 1.2f, 0.55f, 1.2f, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, aBoBaseShieldDL);
    }
}

void Bolse_LoadLevelObjects(void) {
    s32 i;
    Actor* actor;
    Boss* boss;
    Scenery360* scenery360;

    gLevelObjects = SEGMENTED_TO_VIRTUAL(gLevelObjectInits[gCurrentLevel]);

    for (scenery360 = gScenery360, i = 0; i < 1000; i++) {
        if (gLevelObjects[i].id < 0) {
            break;
        }
        if (gLevelObjects[i].id < OBJ_SCENERY_MAX) {
            Scenery360_Initialize(scenery360);
            scenery360->obj.status = OBJ_ACTIVE;
            scenery360->obj.id = gLevelObjects[i].id;
            scenery360->sfxSource[0] = scenery360->obj.pos.x = gLevelObjects[i].xPos;
            scenery360->sfxSource[1] = scenery360->obj.pos.y = gLevelObjects[i].yPos;
            scenery360->sfxSource[2] = scenery360->obj.pos.z = -gLevelObjects[i].zPos1;
            scenery360->unk_54 = scenery360->obj.rot.y = gLevelObjects[i].rot.y;
            Object_SetInfo(&scenery360->info, scenery360->obj.id);
            scenery360++;
        }
    }

    for (actor = &gActors[30], i = 0; i < 1000; i++) {
        if (gLevelObjects[i].id < 0) {
            break;
        }
        if ((gLevelObjects[i].id >= OBJ_ACTOR_START) && (gLevelObjects[i].id < OBJ_ACTOR_MAX)) {
            Actor_Initialize(actor);
            actor->obj.status = OBJ_INIT;
            actor->obj.id = gLevelObjects[i].id;
            if ((actor->obj.id == OBJ_ACTOR_BO_SHIELD_REACTOR) && (gAllRangeCheckpoint == 0)) {
                AUDIO_PLAY_SFX(NA_SE_OB_SPARK_BEAM, actor->sfxSource, 0);
            }
            actor->fwork[10] = actor->obj.pos.x = gLevelObjects[i].xPos;
            actor->fwork[11] = actor->obj.pos.y = gLevelObjects[i].yPos;
            actor->fwork[12] = actor->obj.pos.z = -gLevelObjects[i].zPos1;
            actor->fwork[13] = actor->obj.rot.y = gLevelObjects[i].rot.y;
            Object_SetInfo(&actor->info, actor->obj.id);
            actor++;
        }
    }

    boss = &gBosses[0];

    Boss_Initialize(boss);
    boss->obj.status = OBJ_INIT;
    boss->obj.id = OBJ_BOSS_BO_BASE;
    Object_SetInfo(&boss->info, boss->obj.id);

    boss++;

    Boss_Initialize(boss);
    boss->obj.status = OBJ_INIT;
    boss->obj.id = OBJ_BOSS_BO_BASE_SHIELD;
    Object_SetInfo(&boss->info, boss->obj.id);

    boss++;

    Boss_Initialize(boss);
    boss->obj.status = OBJ_INIT;
    boss->obj.id = OBJ_BOSS_BO_BASE_CORE;
    boss->swork[36] = 8;
    boss->obj.pos.y = -700.0f;

    for (i = 0; i < 12; i++) {
        boss->swork[i] = 30;
    }
    Object_SetInfo(&boss->info, boss->obj.id);
}
/*
void Bolse_DrawDynamicGround(void) {
    Vec3f spDC = { 0.0f, 0.0f, 0.0f };
    Vec3f spD0;
    f32 rnd;
    f32 x;
    f32 z;

    gDPSetFogColor(gMasterDisp++, gFogRed, gFogGreen, gFogBlue, gFogAlpha);
    gSPFogPosition(gMasterDisp++, gFogNear, gFogFar);

    if (gBosses[1].obj.status == OBJ_ACTIVE) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_34);
        if ((gGameFrameCount % 2) != 0) {
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 128, 160, 255);
        } else {
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 192, 224, 255);
        }
    } else {
        RCP_SetupDL(&gMasterDisp, SETUPDL_33);
    }

    Matrix_Push(&gGfxMatrix);
    Rand_SetSeed(1, 29100, 9786);
    Matrix_Translate(gGfxMatrix, 0.0f, gCameraShakeY, 0.0f, MTXF_APPLY);
    Matrix_RotateY(gGfxMatrix, gBosses[0].obj.rot.y * M_DTOR, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, 5.0f, 1.0f, 5.0f, MTXF_APPLY);

    for (int i = 0, z = -3200.0f; z <= 3200.0f; z += 800.0f, i++) {
        for (int j = 100, x = -3200.0f; x <= 3200.0f; x += 800.0f, j++) {

            // @port: Tag the transform.
            FrameInterpolation_RecordOpenChild(i, j);

            rnd = Rand_ZeroOneSeeded();
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, x, 0.0f, z, MTXF_APPLY);
            Matrix_MultVec3f(gGfxMatrix, &spDC, &spD0);
            if ((spD0.z < 3000.0f) && (spD0.z > -13000.0f) && (fabsf(spD0.x) < (fabsf(spD0.z * 0.7f) + 3000.0f)) &&
                (fabsf(spD0.y) < (fabsf(spD0.z * 0.5f) + 2000.0f))) {
                if (rnd < 0.3f) {
                    gDPLoadTileTexture(gMasterDisp++, D_BO_6008BB8, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32);
                } else {
                    gDPLoadTileTexture(gMasterDisp++, D_BO_600AD80, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32);
                }
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_BO_600BEC0);
            }
            Matrix_Pop(&gGfxMatrix);
        }
    }
    Matrix_Pop(&gGfxMatrix);

    // @port Pop the transform id.
    FrameInterpolation_RecordCloseChild();
}
*/

void Bolse_DrawDynamicGround(void) {
    Vec3f spDC = { 0.0f, 0.0f, 0.0f };
    Vec3f spD0;
    f32 rnd;
    f32 x;
    f32 z;

    gDPSetFogColor(gMasterDisp++, gFogRed, gFogGreen, gFogBlue, gFogAlpha);
    gSPFogPosition(gMasterDisp++, gFogNear, gFogFar);

    if (gBosses[1].obj.status == OBJ_ACTIVE) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_34);
        if ((gGameFrameCount % 2) != 0) {
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 128, 160, 255);
        } else {
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 192, 224, 255);
        }
    } else {
        RCP_SetupDL(&gMasterDisp, SETUPDL_33);
    }

    Matrix_Push(&gGfxMatrix);
    Rand_SetSeed(1, 29100, 9786);
    Matrix_Translate(gGfxMatrix, 0.0f, gCameraShakeY, 0.0f, MTXF_APPLY);
    Matrix_RotateY(gGfxMatrix, gBosses[0].obj.rot.y * M_DTOR, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, 5.0f, 1.0f, 5.0f, MTXF_APPLY);

    for (int i = 0, z = -3200.0f; z <= 3200.0f; z += 800.0f, i++) {
        for (int j = 100, x = -3200.0f; x <= 3200.0f; x += 800.0f, j++) {
            // @port: Tag the transform.
            FrameInterpolation_RecordOpenChild(i, j);

            rnd = Rand_ZeroOneSeeded();
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, x, 0.0f, z, MTXF_APPLY);
            Matrix_MultVec3f(gGfxMatrix, &spDC, &spD0);
            if ((spD0.z < 3000.0f) && (spD0.z > -13000.0f) && (fabsf(spD0.x) < (fabsf(spD0.z * 0.7f) + 9000.0f)) &&
                (fabsf(spD0.y) < (fabsf(spD0.z * 0.5f) + 4000.0f))) {
                if (rnd < 0.3f) {
                    gDPLoadTileTexture(gMasterDisp++, D_BO_6008BB8, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32);
                } else {
                    gDPLoadTileTexture(gMasterDisp++, D_BO_600AD80, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32);
                }
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_BO_600BEC0);
            }
            Matrix_Pop(&gGfxMatrix);
        }
    }
    Matrix_Pop(&gGfxMatrix);

    // @port Pop the transform id.
    FrameInterpolation_RecordCloseChild();
}
