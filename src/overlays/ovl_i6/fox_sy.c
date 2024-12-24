/*
 * File: fox_sy.c
 * System: SectorY
 * Description: Level: Sector Y
 */

#include "global.h"
#include "assets/ast_sector_y.h"

#define SHOGUN_SHIP (0)

typedef void (*BossFuncs)(SyShogun*);

void SectorY_80198244(SyShogun*);
void SectorY_80198ABC(SyShogun*);
void SectorY_80199D64(SyShogun*);
void SectorY_8019AA08(SyShogun*);
void SectorY_8019AEC0(SyShogun*);
void SectorY_8019A434(SyShogun*);
void SectorY_8019A640(SyShogun*);
void SectorY_8019A82C(SyShogun*);
bool SectorY_8019B528(SyShogun*);
bool SectorY_8019B5CC(SyShogun*);
void SectorY_8019B6E8(SyShogun*);
void SectorY_8019BBBC(SyShogun*);
void SectorY_8019BC14(SyShogun*);
void SectorY_8019C194(SyShogun*, f32, f32);
void SectorY_801A0510(ActorCutscene*, s32);
void SectorY_ActorDebris_Setup(Actor*, f32, f32, f32, f32, f32, f32, s32);
void SectorY_ActorDebris_Spawn(f32, f32, f32, f32, f32, f32, s32);

f32 D_i6_801A8440[3];

void SectorY_80197B30(ActorCutscene* this, s32 timer) {
    Actor_Initialize(this);
    this->obj.status = OBJ_ACTIVE;
    this->obj.id = OBJ_ACTOR_CUTSCENE;

    this->obj.pos.x = gPlayer[0].pos.x;
    this->obj.pos.y = gPlayer[0].pos.y;
    this->obj.pos.z = gPlayer[0].pos.z;

    this->fwork[0] = gPlayer[0].baseSpeed;

    this->vel.x = gPlayer[0].vel.x;
    this->vel.y = gPlayer[0].vel.y;
    this->vel.z = gPlayer[0].vel.z;

    this->obj.rot.x = gPlayer[0].xRot_120 + gPlayer[0].rot.x + gPlayer[0].aerobaticPitch;
    this->obj.rot.y = gPlayer[0].yRot_114 + gPlayer[0].rot.y + 180.0f;
    this->obj.rot.z = gPlayer[0].rot.z;

    this->state = 5;
    this->work_04C = timer;
    this->iwork[11] = 1;
    Object_SetInfo(&this->info, this->obj.id);
    AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, this->sfxSource, 4);
}

void SectorY_Effect354_Draw(Effect354* this) {
    RCP_SetupDL_21();
    gSPDisplayList(gMasterDisp++, D_SY_6014A40);
    RCP_SetupDL(&gMasterDisp, SETUPDL_64);
}

void SectorY_Scenery156_Draw(SceneryUnk156* this) {
    /* Unimplemented */
}

void SectorY_SyShogun_Init(SyShogun* this) {
    this->fwork[9] = 0.0f;
    this->swork[33] = 5500;
    this->timer_050 = 10;
    this->timer_058 = 0;

    D_ctx_80177A10[8] = 0;

    if (this->index == 0) {
        this->info.hitbox = SEGMENTED_TO_VIRTUAL(D_SY_60342A0);
        this->health = 150;

        this->swork[28] = 5;
        this->fwork[43] = 3.5f;
        this->fwork[45] = 40.0f;

        if (gPlayer[0].state == PLAYERSTATE_START_360) {
            this->obj.pos.z = -28900.0f;
            gScenery360[SHOGUN_SHIP].obj.pos.z = -30000.0f;
        }

        this->rot_078.y = 0.0f;
        SectorY_8019AEC0(this);
    } else {
        this->fwork[34] = 2.8f;
        this->info.hitbox = SEGMENTED_TO_VIRTUAL(D_SY_6034304);
        this->health = 100;
        this->swork[28] = 0;
        this->swork[25] = 1;
        this->fwork[45] = 35.0f;

        if (this->index == 1) {
            this->rot_078.y = 15.0f;
        } else {
            this->rot_078.y = 345.0f;
        }

        this->vel.x = SIN_DEG(this->rot_078.y) * this->fwork[45] * 0.2f;
        this->vel.z = COS_DEG(this->rot_078.y) * this->fwork[45] * 0.2f;
        SectorY_80198244(this);
        this->timer_056 = 250;
    }

    if (gLevelMode == LEVELMODE_ON_RAILS) {
        if (gPlayer[0].state == PLAYERSTATE_ACTIVE) {
            gPlayer[0].state = PLAYERSTATE_START_360;
            gPlayer[0].csState = 0;
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 50);
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 50);
        }
        Object_Kill(&this->obj, this->sfxSource);
    }
}

void SectorY_80197F18(SyShogun* this) {
    this->swork[20] = 0;
    this->swork[21] = 3;
    this->fwork[9] = 0.0f;
    this->timer_050 = RAND_INT(100.0f) + 60;
    if (this->index != 0) {
        this->timer_050 += 60;
    }
}

void SectorY_80197F84(SyShogun* this) {
    f32 yaw;

    Math_SmoothStepToF(&this->obj.pos.y, 0.0f, 0.5f, 15.0f, 0.1f);
    Math_SmoothStepToF(&this->vel.y, 0.0f, 0.1f, 0.2f, 0.1f);
    Math_SmoothStepToF(&this->vel.z, 0.0f, 0.1f, 0.2f, 0.1f);
    Math_SmoothStepToF(&this->vel.x, 0.0f, 0.1f, 0.2f, 0.1f);
    Math_SmoothStepToAngle(&this->rot_078.x, 0.0f, 0.1f, 4.0f, 0.1f);

    if (SectorY_8019B5CC(this)) {
        Math_SmoothStepToF(&this->obj.pos.y, 1000.0f, 0.1f, 30.0f, 0.1f);
    } else {
        Math_SmoothStepToF(&this->obj.pos.y, 0.0f, 0.1f, 10.0f, 0.1f);
    }

    SectorY_8019B6E8(this);
    if (this->timer_052 == 0) {
        SectorY_8019BC14(this);
    }

    yaw = Math_RadToDeg(Math_Atan2F(this->fwork[18] - this->obj.pos.x, this->fwork[20] - this->obj.pos.z));

    Math_SmoothStepToAngle(&this->rot_078.y, yaw, 0.1f, 8.0f, 0.1f);

    if (this->timer_050 == 0) {
        SectorY_80198244(this);
    }

    if (this->swork[22] == 1) {
        if (ABS(this->vel.x) <= 1.0f && (ABS(this->vel.z) <= 1.0f) &&
            (fabsf(this->fwork[18] - this->obj.pos.x) <= 400.0f) &&
            (fabsf(this->fwork[20] - this->obj.pos.z) <= 1400.0f)) {
            if ((Rand_ZeroOne() < 0.2f) && (this->rot_078.x == 0.0f)) {
                SectorY_8019AA08(this);
            }
            if (Rand_ZeroOne() < 0.2f) {
                SectorY_80198244(this);
            }
        }
    }

    if (SectorY_8019B528(this)) {
        SectorY_80198ABC(this);
    }
}

void SectorY_80198238(SyShogun* this) {
}

void SectorY_80198244(SyShogun* this) {
    f32 speed;

    this->swork[20] = 3;
    this->swork[21] = 1;
    this->timer_056 = (s32) (RAND_FLOAT(500.0f) + 100.0f);
    this->fwork[11] = SIN_DEG(this->rot_078.y) * this->fwork[45];
    this->fwork[13] = COS_DEG(this->rot_078.y) * this->fwork[45];

    speed = ABS(this->vel.x);

    if (speed < 5.0f) {
        Math_SmoothStepToF(&this->vel.x, this->fwork[11], 0.1f, 5.0f, 0.1f);
    }
    speed = ABS(this->vel.z);

    if (speed < 5.0f) {
        Math_SmoothStepToF(&this->vel.z, this->fwork[13], 0.1f, 5.0f, 0.1f);
    }
    this->fwork[10] = 181.0f;
    this->fwork[34] = 2.8f;
    AUDIO_PLAY_SFX(NA_SE_EN_MS_DASH, this->sfxSource, 4);
}

void SectorY_801983E4(SyShogun* this) {
    f32 yAngle;
    f32 xSpeed;
    f32 zSpeed;

    SectorY_8019B6E8(this);

    if (this->timer_052 == 0) {
        SectorY_8019BC14(this);
    }

    Math_SmoothStepToAngle(&this->rot_078.z, 0.0f, 0.1f, 2.0f, 0.1f);
    Math_SmoothStepToAngle(&this->rot_078.x, 0.0f, 0.1f, 2.0f, 0.1f);
    Math_SmoothStepToF(&this->vel.x, this->fwork[11], 0.1f, 0.5f, 0.1f);
    Math_SmoothStepToF(&this->vel.z, this->fwork[13], 0.1f, 0.5f, 0.1f);
    Math_SmoothStepToF(&this->vel.y, 0.0f, 0.1f, 0.2f, 0.1f);

    xSpeed = ABS(this->fwork[18] - this->obj.pos.x);
    zSpeed = ABS(this->fwork[20] - this->obj.pos.z);

    if (this->rot_078.x != 0.0f) {
        Math_SmoothStepToAngle(&this->rot_078.x, this->fwork[10], 0.1f, 6.0f, 0.1f);
        if (this->rot_078.x < 200.0f) {
            this->swork[21] = 1;
            this->fwork[10] = 0.0f;
            this->rot_078.x = 0.0f;
            this->rot_078.y -= 180.0f;
            this->rot_078.z -= 180.0f;
            if (this->rot_078.y < 0.0f) {
                this->rot_078.y += 360.0f;
            }

            if (this->rot_078.z < 0.0f) {
                this->rot_078.z += 360.0f;
            }
            this->fwork[11] = SIN_DEG(this->rot_078.y) * this->fwork[45];
            this->fwork[13] = COS_DEG(this->rot_078.y) * this->fwork[45];
            this->fwork[34] = 2.8f;
        }
    }

    SectorY_8019C194(this, zSpeed, xSpeed);

    if (this->swork[22] == 1) {
        yAngle = gPlayer[0].yRot_114 - 180.0f;
        if (yAngle < 0.0f) {
            yAngle += 360.0f;
        }

        yAngle = this->rot_078.y - yAngle;
        if (yAngle < 0.0f) {
            yAngle += 360.0f;
        }

        if ((zSpeed <= 1300.0f) && (xSpeed <= 800.0f) && (yAngle < 260.0f) && (yAngle > 100.0f) &&
            (this->rot_078.x == 0.0f) && (this->fwork[34] <= 2.0f)) {
            if (Rand_ZeroOne() < 0.2f) {
                SectorY_8019AA08(this);
            }
        }

        if ((zSpeed < 3400.0f) || (xSpeed < 2400.0f)) {
            if (((yAngle >= 60.0f) && (yAngle <= 100.0f)) || ((yAngle <= 300.0f) && (yAngle >= 260.0f))) {
                if (Rand_ZeroOne() < 0.3f) {
                    if (Rand_ZeroOne() < 0.4f) {
                        SectorY_80197F18(this);
                    } else {
                        SectorY_80199D64(this);
                    }
                }
            }

            if (((yAngle > 300.0f) || (yAngle < 60.0f)) && (this->rot_078.x == 0.0f)) {
                if (Rand_ZeroOne() < 0.3f) {
                    if (Rand_ZeroOne() < 0.4f) {
                        SectorY_80197F18(this);
                    } else {
                        SectorY_80199D64(this);
                    }
                } else if (gPlayer[0].state != PLAYERSTATE_U_TURN) {
                    Math_SmoothStepToAngle(&this->rot_078.x, 181.0f, 0.1f, 6.0f, 0.1f);
                    this->swork[21] = 3;
                    this->fwork[11] = SIN_DEG(this->rot_078.y) * (this->fwork[45] + 10.0f);
                    this->fwork[13] = COS_DEG(this->rot_078.y) * (this->fwork[45] + 10.0f);
                    this->fwork[34] = 2.8f;
                }
            }
        }
    }

    if (SectorY_8019B5CC(this)) {
        Math_SmoothStepToF(&this->obj.pos.y, 1000.0f, 0.1f, 30.0f, 0.1f);
    } else {
        Math_SmoothStepToF(&this->obj.pos.y, 0.0f, 0.1f, 5.0f, 0.1f);
    }

    if (this->timer_056 == 0) {
        if (Rand_ZeroOne() <= 0.7f) {
            SectorY_80199D64(this);
        } else {
            SectorY_80197F18(this);
        }
    }

    if (SectorY_8019B528(this)) {
        SectorY_80198ABC(this);
    }
}

void SectorY_80198ABC(SyShogun* this) {
    f32 yAngle = Math_RadToDeg(Math_Atan2F(-this->obj.pos.x, -300.0f - this->obj.pos.z)) - this->rot_078.y;

    if (yAngle < 0.0f) {
        yAngle += 360.0f;
    }

    this->swork[20] = 4;
    this->swork[21] = 3;
    this->fwork[34] = 4.5f;

    this->timer_056 = (s32) (RAND_FLOAT(100.0f) + 100.0f);
    this->timer_050 = 0;

    if (yAngle > 180.0f) {
        this->fwork[27] = 40.0f;
        if (this->index == 0) {
            this->fwork[42] = 1.8f;
        }
    } else {
        this->fwork[27] = 320.0f;
        if (this->index == 0) {
            this->fwork[41] = 1.8f;
        }
    }

    AUDIO_PLAY_SFX(NA_SE_EN_MS_DASH, this->sfxSource, 4);

    switch (D_ctx_80177A10[8]) {
        case 0:
            if (gTeamShields[TEAM_ID_FALCO] > 0) {
                AllRange_PlayMessage(gMsg_ID_14200, RCID_FALCO);
            }
            break;

        case 1:
            if ((gBosses[1].obj.status == OBJ_FREE) && (gBosses[2].obj.status == OBJ_FREE)) {
                AllRange_PlayMessage(gMsg_ID_14320, RCID_BOSS_SECTORY);
            }
            break;

        case 2:
            if ((gTeamShields[TEAM_ID_SLIPPY] > 0) && (gBosses[1].obj.status != OBJ_FREE) &&
                (gBosses[2].obj.status != OBJ_FREE)) {
                AllRange_PlayMessage(gMsg_ID_14220, RCID_SLIPPY);
            }
            break;
    }

    D_ctx_80177A10[8] += (gGameFrameCount % 2U) + 1;
    D_ctx_80177A10[8] %= 4U;
}

void SectorY_80198CE4(SyShogun* this) {
    f32 yAngle;

    SectorY_8019B6E8(this);

    if (this->timer_052 == 0) {
        SectorY_8019BC14(this);
    }

    Math_SmoothStepToAngle(&this->rot_078.z, this->fwork[27], 0.1f, 0.5f, 0.1f);
    Math_SmoothStepToAngle(&this->rot_078.x, 0.0f, 0.1f, 4.0f, 0.1f);
    yAngle = Math_RadToDeg(Math_Atan2F(-this->obj.pos.x, -300.0f - this->obj.pos.z));

    if (this->index != 0) {
        Math_SmoothStepToAngle(&this->rot_078.y, yAngle, 0.1f, 1.0f, 0.1f);
    } else {
        Math_SmoothStepToAngle(&this->rot_078.y, yAngle, 0.1f, 2.0f, 0.1f);
    }

    if (this->index == 0) {
        this->vel.x = SIN_DEG(this->rot_078.y) * (this->fwork[45] + 20.0f);
        this->vel.z = COS_DEG(this->rot_078.y) * (this->fwork[45] + 20.0f);
    } else {
        this->vel.x = SIN_DEG(this->rot_078.y) * this->fwork[45];
        this->vel.z = COS_DEG(this->rot_078.y) * this->fwork[45];
    }

    if (SectorY_8019B5CC(this)) {
        Math_SmoothStepToF(&this->obj.pos.y, 1000.0f, 0.1f, 30.0f, 0.1f);
    } else {
        Math_SmoothStepToF(&this->obj.pos.y, 0.0f, 0.1f, 5.0f, 0.1f);
    }

    Math_SmoothStepToF(&this->vel.y, 0.0f, 0.1f, 0.2f, 0.1f);

    yAngle -= this->rot_078.y;
    if (yAngle < 0.0f) {
        yAngle += 360.0f;
    }

    if (!SectorY_8019B528(this) && ((yAngle <= 20.0f) || (yAngle >= 320.0f))) {
        SectorY_80198244(this);
    }
}

void SectorY_80198F5C(SyShogun* this) {
    Vec3f vec;
    Vec3f sp48;
    f32 xDisplacement;
    f32 zDisplacement;
    s32 i;

    this->timer_05C = 20;
    Effect_Effect390_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, this->vel.x, this->vel.y, this->vel.z,
                           0.1f, 10);
    this->health -= this->damage;

    if (this->health < 0) {
        this->health = 0;
    }

    this->timer_058 = 20;

    if (this->health <= 0) {
        this->animFrame = 0;
        this->swork[36] = 0;
        this->swork[21] = 9;
        this->info.hitbox = SEGMENTED_TO_VIRTUAL(gNoHitbox);

        if (this->index == 0) {
            this->timer_058 = 20000;
            this->vel.x = this->vel.y = this->vel.z = 0.0f;
            if ((gPlayer[0].state == PLAYERSTATE_ACTIVE) || (gPlayer[0].state == PLAYERSTATE_U_TURN)) {
                gCsFrameCount = 0;
                gPlayer[0].state = PLAYERSTATE_LEVEL_COMPLETE;
                gPlayer[0].csTimer = 0;
                gPlayer[0].csState = gPlayer[0].csTimer;
                gPlayer[0].rot.y += gPlayer[0].yRot_114;
                if (gPlayer[0].rot.y > 360.0f) {
                    gPlayer[0].rot.y -= 360.0f;
                }
                if (gPlayer[0].rot.y < 0.0f) {
                    gPlayer[0].rot.y += 360.0f;
                }
                gPlayer[0].yRot_114 = 0.0f;
            }
            AUDIO_PLAY_SFX(NA_SE_EN_DOWN_IMPACT, this->sfxSource, 4);
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 30);
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 30);
            return;
        }

        if ((gBosses[1].obj.status == OBJ_FREE) || (gBosses[2].obj.status == OBJ_FREE)) {
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 20);
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 20);
        }

        for (i = 4; i < ARRAY_COUNT(gActors); i++) {
            if (gActors[i].obj.status == OBJ_FREE) {
                SectorY_80197B30(&gActors[i], this->index);
                D_ctx_80177A10[9] = i;
                break;
            }
        }
        this->timer_058 = 2000;
        this->vel.z = 0.0f;
        this->vel.y = 0.0f;
        this->vel.x = 0.0f;

        if ((gPlayer[0].state == PLAYERSTATE_ACTIVE) || (gPlayer[0].state == PLAYERSTATE_U_TURN)) {
            this->timer_058 = 100;
            gPlayer[0].state = PLAYERSTATE_STANDBY;
            gCsFrameCount = 0;
            xDisplacement = gPlayer[0].cam.eye.x - this->obj.pos.x;
            zDisplacement = gPlayer[0].cam.eye.z - this->obj.pos.z;
            D_ctx_80177A48[8] = Math_RadToDeg(Math_Atan2F(xDisplacement, zDisplacement));
            Matrix_RotateY(gCalcMatrix, D_ctx_80177A48[8] * M_DTOR, MTXF_NEW);
            vec.x = 0.0f;
            vec.y = 0.0f;
            vec.z = 900.0f;
            Matrix_MultVec3f(gCalcMatrix, &vec, &sp48);
            gCsCamEyeX = this->obj.pos.x + sp48.x;
            gCsCamEyeY = this->obj.pos.y + 400.0f;
            gCsCamEyeZ = this->obj.pos.z + sp48.z;
            gCsCamAtX = this->obj.pos.x;
            gCsCamAtY = this->obj.pos.y;
            gCsCamAtZ = this->obj.pos.z;
            D_ctx_80177A48[0] = 0.1f;
            if (Rand_ZeroOne() > 0.5f) {
                D_ctx_80177A48[9] = -3.0f;
                return;
            }
            D_ctx_80177A48[9] = 3.0f;
        }
    } else {
        if (this->index != 0) {
            AUDIO_PLAY_SFX(NA_SE_EN_DAMAGE_S, this->sfxSource, 4);
        } else if (this->health > 70) {
            AUDIO_PLAY_SFX(NA_SE_OB_DAMAGE_M, this->sfxSource, 4);
        } else {
            AUDIO_PLAY_SFX(NA_SE_EN_KNOCK_DOWN, this->sfxSource, 4);
        }

        if ((gBosses[1].obj.status == OBJ_FREE) && (gBosses[2].obj.status == OBJ_FREE)) {
            AllRange_PlayMessage(gMsg_ID_14350, RCID_BOSS_SECTORY);
        }
    }
}

void SectorY_80199438(SyShogun* this) {
    s32 i;
    s32 j;
    Vec3f vec;
    Vec3f sp68;

    if (this->health <= 0) {
        if (this->index == 0) {
            this->vel.x = this->vel.y = this->vel.z = 0.0f;

            if (gCsFrameCount < 61) {
                this->fwork[0] = 0.0f;
            }
            if (gCsFrameCount == 61) {
                Radio_PlayMessage(gMsg_ID_14360, RCID_BOSS_SECTORY);
            }
            if (gCsFrameCount >= 80) {
                this->fwork[0] = 1.0f;
            }
        } else {
            D_ctx_80177A48[8] += D_ctx_80177A48[9];
            Matrix_RotateY(gCalcMatrix, D_ctx_80177A48[8] * M_DTOR, MTXF_NEW);

            vec.x = 0.0f;
            vec.y = 0.0f;
            vec.z = 900.0f;

            Matrix_MultVec3f(gCalcMatrix, &vec, &sp68);

            gCsCamEyeX = this->obj.pos.x + sp68.x;
            gCsCamEyeZ = this->obj.pos.z + sp68.z;

            if ((this->timer_058 == 40) && (gBosses[1].obj.status == OBJ_FREE) && (gBosses[2].obj.status == OBJ_FREE)) {
                Radio_PlayMessage(gMsg_ID_14360, RCID_BOSS_SECTORY);
            }
            if (this->timer_058 > 85) {
                this->fwork[0] = 0.0f;
            }
            if (this->timer_058 < 67) {
                this->fwork[0] = 1.0f;
            }
            if ((this->timer_058 == 60) && (this->swork[19] == 0)) {
                BonusText_Display(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 3);
                gHitCount += 4;
            }
            if (this->timer_058 == 50) {
                AUDIO_PLAY_SFX(NA_SE_EN_MS_EXPLOSION_S, this->sfxSource, 4);
                gControllerRumbleFlags[gMainController] = 1;
                gControllerRumbleTimers[gMainController] = 20;

                D_ctx_80177850 = 15;
                this->swork[36]++;

                Effect386_Spawn1(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, this->vel.x, this->vel.y,
                                 this->vel.z, 8.0f, 10);
                Effect_Effect384_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 8.0f, 5);

                for (i = 10; i < 24; i++) {
                    if (i != 15) {
                        SectorY_ActorDebris_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z,
                                                  RAND_FLOAT_CENTERED(50.0f), RAND_FLOAT_CENTERED(50.0f),
                                                  RAND_FLOAT_CENTERED(50.0f) + this->vel.z, i);
                    }
                }
            }
            Math_SmoothStepToF(&gPlayer[0].cam.eye.x, gCsCamEyeX, D_ctx_80177A48[0], 20000.0f, 0);
            Math_SmoothStepToF(&gPlayer[0].cam.eye.y, gCsCamEyeY, D_ctx_80177A48[0], 20000.0f, 0);
            Math_SmoothStepToF(&gPlayer[0].cam.eye.z, gCsCamEyeZ, D_ctx_80177A48[0], 20000.0f, 0);
            Math_SmoothStepToF(&gPlayer[0].cam.at.x, gCsCamAtX, D_ctx_80177A48[0], 20000.0f, 0);
            Math_SmoothStepToF(&gPlayer[0].cam.at.y, gCsCamAtY, D_ctx_80177A48[0], 20000.0f, 0);
            Math_SmoothStepToF(&gPlayer[0].cam.at.z, gCsCamAtZ, D_ctx_80177A48[0], 20000.0f, 0);
        }

        if (((gGameFrameCount % 4) == 0) && (this->swork[36] == 0)) {
            Effect_Effect390_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, this->vel.x, this->vel.y,
                                   this->vel.z, 0.1f, 5);
        }

        if ((gCsFrameCount == 120) && (this->swork[36] == 0) && (this->index == 0)) {
            if (this->swork[19] == 0) {
                Boss_AwardBonus(this);
            }

            for (i = 0; i < 2; i++) {
                if (gEffects[i].obj.status != OBJ_FREE) {
                    Object_Kill(&gEffects[i].obj, gEffects[i].sfxSource);
                }
            }

            Audio_KillSfxBySource(this->sfxSource);
            gShowBossHealth = false;
            Effect_Effect383_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 40.0f);
            func_effect_8007D0E0(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 30.0f);
            func_enmy_80062B60(this->obj.pos.x, this->obj.pos.z, 0, 120.0f);
            gCameraShake = 25;
            this->swork[36]++;

            for (i = 10; i < 24; i++) {
                if (i != 15) {
                    SectorY_ActorDebris_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z,
                                              RAND_FLOAT_CENTERED(50.0f), RAND_FLOAT_CENTERED(50.0f),
                                              RAND_FLOAT_CENTERED(50.0f) + this->vel.z, i);
                }
            }
            this->timer_058 = 100;
            this->vel.x = this->vel.y = this->vel.z = 0.0f;
        }

        if (this->timer_058 == 1) {
            if (this->index != 0) {
                Object_Kill(&gActors[D_ctx_80177A10[9]].obj, gActors[D_ctx_80177A10[9]].sfxSource);
                if ((gBosses[1].obj.status == OBJ_FREE) || (gBosses[2].obj.status == OBJ_FREE)) {
                    gBosses[0].work_04A = 1;
                    gScenery360[SHOGUN_SHIP].info.dList = aSySaruzinDL;
                    gScenery360[SHOGUN_SHIP].info.drawType = 0;
                } else {
                    gPlayer[0].state = PLAYERSTATE_ACTIVE;
                    Camera_UpdateArwing360(&gPlayer[0], true);
                    gPlayer[0].unk_014 = 0.0f;
                    if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                        AllRange_PlayMessage(gMsg_ID_14230, RCID_PEPPY);
                    }
                }
            }
            Object_Kill(&this->obj, this->sfxSource);
        }
    } else {
        if (this->health < 80) {
            if (this->swork[25] == 0) {
                this->swork[25] = 1;

                for (j = ARRAY_COUNT(gActors) - 1; j >= 0; j--) {
                    if (gActors[j].obj.status == OBJ_FREE) {
                        SectorY_ActorDebris_Setup(&gActors[j], this->fwork[28], this->fwork[29], this->fwork[30],
                                                  RAND_FLOAT_CENTERED(50.0f), RAND_FLOAT_CENTERED(50.0f),
                                                  RAND_FLOAT_CENTERED(50.0f) + this->vel.z, 15);
                        break;
                    }
                }
                func_effect_8007D2C8(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + 30.0f, 4.0f);
                this->info.hitbox = SEGMENTED_TO_VIRTUAL(D_SY_6034304);
                AUDIO_PLAY_SFX(NA_SE_EN_MS_SHIELD_BROKEN, this->sfxSource, 4);
            }
        }
        if (this->health <= 80) {
            this->swork[33] = 3500;
        }
        if (this->health <= 70) {
            this->swork[29] = 31;
        }
        if (this->health <= 50) {
            this->swork[29] = 15;
        }
        if (this->health <= 30) {
            this->swork[29] = 7;
        }
        if (this->health <= 10) {
            this->swork[29] = 3;
        }
    }
}

void SectorY_80199D64(SyShogun* this) {
    if (this->swork[34] >= 2) {
        this->swork[20] = 6;
        this->swork[21] = 1;
        this->fwork[12] = 1000.0f;
        this->fwork[34] = 2.8f;
        this->timer_056 = 0;
        this->vel.y = 0.0f;
    }
}

void SectorY_80199DAC(SyShogun* this) {
    f32 sp34;
    f32 zSpeed;
    f32 xSpeed;
    f32 yAngle;

    SectorY_8019B6E8(this);

    if (this->timer_052 == 0) {
        SectorY_8019BC14(this);
    }

    sp34 = Math_RadToDeg(Math_Atan2F(0.0f - this->obj.pos.x, -300.0f - this->obj.pos.z));

    this->fwork[11] = SIN_DEG(sp34) * (this->fwork[45] + 10.0f);
    this->fwork[13] = COS_DEG(sp34) * (this->fwork[45] + 10.0f);
    this->fwork[10] = sp34;

    Math_SmoothStepToAngle(&this->rot_078.z, 0.0f, 0.1f, 4.0f, 0.1f);
    Math_SmoothStepToAngle(&this->rot_078.y, this->fwork[10], 0.1f, 6.0f, 0.1f);
    Math_SmoothStepToF(&this->obj.pos.y, this->fwork[12], 1.0f, 15.0f, 1.0f);

    if (((ABS(this->obj.pos.y) - this->fwork[12]) <= 1800.0f) && (ABS(this->obj.pos.x) <= 1800.0f) &&
        (ABS(this->obj.pos.z + 300.0f) <= 1800.0f)) {

        this->vel.x = 0.0f;
        this->vel.z = 0.0f;

        Math_SmoothStepToF(&this->obj.pos.x, 0.0f, 0.1f, ABS(this->fwork[11]), 0.1f);
        Math_SmoothStepToF(&this->obj.pos.z, -300.0f, 0.1f, ABS(this->fwork[13]), 0.1f);
        Math_SmoothStepToAngle(&this->rot_078.x, 0.0f, 0.1f, 4.0f, 0.1f);

        this->fwork[10] = 0.0f;

        if (((ABS(this->obj.pos.y) - this->fwork[12]) <= 300.0f) && (ABS(this->obj.pos.x) <= 300.0f) &&
            (ABS(this->obj.pos.z + 300.0f) <= 300.0f)) {
            Math_SmoothStepToF(&this->fwork[43], 3.0f, 0.1f, 0.1f, 0.1f);
            this->swork[21] = 6;
            this->animFrame = 27;
            this->fwork[12] = 320.0f;
            if (this->timer_056 == 0) {
                this->timer_056 = 51;
                AUDIO_PLAY_SFX(NA_SE_EN_MS_DASH, this->sfxSource, 4);
            }
        }
    } else {
        Math_SmoothStepToF(&this->vel.x, this->fwork[11], 0.1f, 0.5f, 0.1f);
        Math_SmoothStepToF(&this->vel.z, this->fwork[13], 0.1f, 0.5f, 0.1f);
        yAngle = gPlayer[0].yRot_114 - 180.0f;
        if (yAngle < 0.0f) {
            yAngle += 360.0f;
        }
        yAngle = this->rot_078.y - yAngle;
        if (yAngle < 0.0f) {
            yAngle += 360.0f;
        }

        zSpeed = ABS(this->fwork[20] - this->obj.pos.z);
        xSpeed = ABS(this->fwork[18] - this->obj.pos.x);

        if (this->rot_078.x != 0.0f) {
            if ((yAngle > 300.0f) || (yAngle < 60.0f)) {
                Math_SmoothStepToAngle(&this->rot_078.x, 181.0f, 0.1f, 6.0f, 0.1f);
            } else {
                Math_SmoothStepToAngle(&this->rot_078.x, 0.0f, 0.1f, 6.0f, 0.1f);
            }
        } else if ((this->swork[22] == 1) && ((yAngle > 300.0f) || (yAngle < 60.0f)) && (Rand_ZeroOne() > 0.2f)) {
            Math_SmoothStepToAngle(&this->rot_078.x, 181.0f, 0.1f, 6.0f, 0.1f);
            this->swork[21] = 3;
            this->fwork[34] = 2.8f;
        }
        if (!SectorY_8019B5CC(this)) {
            SectorY_8019C194(this, zSpeed, xSpeed);
        }
    }

    if (this->timer_056 == 1) {
        sp34 = Rand_ZeroOne();
        if (sp34 >= 0.3f) {
            SectorY_8019A82C(this);
        }
        if (sp34 < 0.2f) {
            SectorY_8019A434(this);
        }
        if ((sp34 < 0.3f) && (sp34 >= 0.2f)) {
            SectorY_8019A640(this);
        }
    }
}

void SectorY_8019A434(SyShogun* this) {
    this->swork[20] = 7;
    this->swork[21] = 5;
    this->timer_056 = (s32) (RAND_FLOAT(130.0f) + 60.0f);
    this->fwork[11] = SIN_DEG(this->rot_078.y) * this->fwork[45];
    this->fwork[13] = COS_DEG(this->rot_078.y) * this->fwork[45];
    this->fwork[12] = 30.0f;
    this->fwork[10] = 181.0f;
    AUDIO_PLAY_SFX(NA_SE_EN_MS_LAND, this->sfxSource, 4);
}

void SectorY_8019A520(SyShogun* this) {
    SectorY_8019B6E8(this);

    if (this->timer_052 == 0) {
        SectorY_8019BC14(this);
    }

    Math_SmoothStepToAngle(&this->rot_078.y, 0.0f, 0.1f, 2.0f, 0.1f);
    Math_SmoothStepToF(&this->vel.x, 0.0f, 0.1f, 0.2f, 0.1f);
    Math_SmoothStepToF(&this->vel.z, 6.0f, 0.1f, 0.2f, 0.1f);
    Math_SmoothStepToF(&this->vel.y, 0.0f, 0.1f, 0.2f, 0.1f);

    if (this->timer_056 == 0) {
        SectorY_8019A640(this);
    } else {
        this->fwork[0] = 1.0f;
    }

    if ((this->animFrame == 0) || (this->animFrame == 27)) {
        AUDIO_PLAY_SFX(NA_SE_EN_HEAVY_WALK, this->sfxSource, 4);
    }
}

void SectorY_8019A640(SyShogun* this) {
    this->swork[20] = 8;
    this->swork[21] = 0;
    this->vel.x = 0.0f;
    this->vel.y = 0.0f;
    this->vel.z = 0.0f;
    this->timer_056 = 80;
}

void SectorY_8019A66C(SyShogun* this) {
    SectorY_8019B6E8(this);

    if (this->timer_052 == 0) {
        SectorY_8019BC14(this);
    }

    if (this->timer_056 == 60) {
        AUDIO_PLAY_SFX(NA_SE_EN_MS_DASH, this->sfxSource, 4);
        this->fwork[34] = 4.5f;
        if (Rand_ZeroOne() > 0.5f) {
            AllRange_PlayMessage(gMsg_ID_14330, RCID_BOSS_SECTORY);
        } else {
            AllRange_PlayMessage(gMsg_ID_14320, RCID_BOSS_SECTORY);
        }
    }

    if (this->timer_056 <= 60) {
        this->fwork[11] = SIN_DEG(this->rot_078.y) * this->fwork[45];
        this->fwork[13] = COS_DEG(this->rot_078.y) * this->fwork[45];
        this->swork[21] = 1;
        Math_SmoothStepToF(&this->fwork[43], 0.0f, 0.1f, 0.1f, 0.1f);
        Math_SmoothStepToF(&this->vel.z, this->fwork[13], 0.1f, 0.5f, 0.5f);
        Math_SmoothStepToF(&this->vel.x, this->fwork[11], 0.1f, 0.5f, 0.5f);
        Math_SmoothStepToF(&this->vel.y, 10.0f, 0.1f, 0.5f, 0.5f);
    }

    if (this->timer_056 == 0) {
        SectorY_80198244(this);
    }
}

void SectorY_8019A82C(SyShogun* this) {
    this->swork[20] = 9;
    this->fwork[9] = 0.0f;
    this->timer_050 = RAND_INT(150.0f) + 340;
    this->timer_056 = 0;
    AllRange_PlayMessage(gMsg_ID_14340, RCID_BOSS_SECTORY);
}

void SectorY_8019A898(SyShogun* this) {
    f32 yAngle1;
    f32 yAngle2;

    SectorY_8019B6E8(this);
    if (this->timer_052 == 0) {
        SectorY_8019BC14(this);
    }

    yAngle1 = Math_RadToDeg(Math_Atan2F(this->fwork[18] - this->obj.pos.x, this->fwork[20] - this->obj.pos.z));
    yAngle2 = yAngle1 - this->rot_078.y;
    if (yAngle2 < 0.0f) {
        yAngle2 += 360.0f;
    }

    this->swork[21] = 6;

    if (((yAngle2 >= 30.0f) && (yAngle2 <= 330.0f)) || ((this->animFrame != 0)) && (this->animFrame != 27)) {
        this->swork[21] = 5;
        Math_SmoothStepToAngle(&this->rot_078.y, yAngle1, 0.1f, 2.0f, 0.1f);
        this->fwork[0] = 1.0f;
        if ((this->animFrame == 0) || (this->animFrame == 27)) {
            AUDIO_PLAY_SFX(NA_SE_EN_HEAVY_WALK, this->sfxSource, 4);
        }
    } else {
        this->timer_056 = 0;
    }

    if (this->timer_050 == 0) {
        SectorY_8019A434(this);
    }
}

void SectorY_8019AA08(SyShogun* this) {
    if (SectorY_8019B5CC(this)) {
        return;
    }

    if ((gBosses[1].obj.status == OBJ_FREE) && (gBosses[2].obj.status == OBJ_FREE)) {
        AllRange_PlayMessage(gMsg_ID_14330, RCID_BOSS_SECTORY);
    }

    if (Rand_ZeroOne() >= 0.5f) {
        this->swork[21] = 7;
        this->swork[31] = 11;
        this->swork[32] = Animation_GetFrameCount(&D_SY_602645C) - 1;

    } else if (this->index == 0) {
        this->swork[21] = 8;
        this->swork[31] = 13;
        this->swork[32] = Animation_GetFrameCount(&D_SY_60258A0) - 1;

    } else {
        return;
    }

    this->swork[20] = 10;
    this->animFrame = 0;
    this->fwork[34] = 2.8f;
}

void SectorY_8019AAF0(SyShogun* this) {
    f32 var_fv1;
    f32 xAngle;
    f32 yAngle;
    f32 var_ft5;
    Vec3f vec;
    Vec3f vel;

    SectorY_8019BBBC(this);

    yAngle = Math_Atan2F(this->fwork[18] - this->obj.pos.x, this->fwork[20] - this->obj.pos.z);
    var_fv1 = 500.0f;
    if (this->health != 0) {
        var_fv1 += 200.0f;
    }

    if ((this->swork[31] >= this->animFrame) && (fabsf(this->obj.pos.z - this->fwork[20]) < (var_fv1 + 1000.0f)) &&
        (fabsf(this->obj.pos.x - this->fwork[18]) < var_fv1)) {
        this->animFrame++;
    }

    if (this->animFrame >= this->swork[32] - 29) {
        if (this->animFrame == this->swork[32] - 29) {
            if (this->swork[31] == 11) {
                AUDIO_PLAY_SFX(NA_SE_EN_MS_PUNCH, this->sfxSource, 4);
            } else {
                AUDIO_PLAY_SFX(NA_SE_EN_MS_KICK, this->sfxSource, 4);
            }
        }

        if (this->animFrame >= (this->swork[32] - 5)) {
            SectorY_80198244(this);
        }
    } else {
        Math_SmoothStepToF(&this->fwork[9], this->fwork[45] + 10.0f, 0.1f, 2.0f, 0.1f);

        var_ft5 = ABS(this->fwork[18] - this->obj.pos.x) + ABS(this->fwork[20] - this->obj.pos.z);
        xAngle = -Math_Atan2F(this->fwork[19] - this->obj.pos.y, var_ft5);
        Matrix_RotateY(gCalcMatrix, yAngle, MTXF_NEW);
        Matrix_RotateX(gCalcMatrix, xAngle, MTXF_APPLY);
        vec.x = 0.0f;
        vec.y = 0.0f;
        vec.z = this->fwork[9];
        Matrix_MultVec3f(gCalcMatrix, &vec, &vel);
        this->vel.z = vel.z;
        this->vel.x = vel.x;
        Math_SmoothStepToAngle(&this->rot_078.y, Math_RadToDeg(yAngle), 0.1f, 6.0f, 0.1f);
    }

    if (this->swork[31] != 11) {

        if ((this->rot_078.z <= 90.0f) || (this->rot_078.z >= 270.0f)) {
            this->fwork[19] += 70.0f;
        } else {
            this->fwork[19] -= 50.0f;
        }
    }

    Math_SmoothStepToF(&this->obj.pos.y, this->fwork[19], 0.1f, 40.0f, 0.1f);

    if (D_edisplay_801615D0.z > 0.0f) {
        this->swork[32] = 0;
    }

    if (SectorY_8019B528(this)) {
        SectorY_80198ABC(this);
    }

    if (this->swork[20] == 10) {
        this->fwork[0] = 0.25f;
    }
    if ((this->swork[20] == 10) && (this->animFrame >= 12)) {
        this->fwork[0] = 1.0f;
    }
}

void SectorY_8019AEC0(SyShogun* this) {
    this->swork[20] = 11;
    this->swork[21] = 8;
    this->vel.x = 0.0f;
    this->vel.y = 0.0f;
    this->vel.z = 0.0f;
    this->work_044 = 0;
}

void SectorY_8019AEEC(SyShogun* this) {
    if ((this->obj.pos.y != 365.0f) && (this->swork[21] != 1)) {
        if (this->work_04A != 0) {
            if (this->work_04A == 1) {
                Audio_PlaySequence(SEQ_PLAYER_BGM, NA_BGM_REAL_BOSS, 0, 0);
                this->work_04A++;
                gPlayer[0].cam.eye.x = 0.0f;
                gPlayer[0].cam.eye.y = 200.0f;
                gPlayer[0].cam.eye.z = -20000.0f;
                gPlayer[0].cam.at.x = 0.0f;
                gPlayer[0].cam.at.y = 300.0f;
                gPlayer[0].cam.at.z = this->obj.pos.z;
                gPlayer[0].camRoll = 0.0f;
                Radio_PlayMessage(gMsg_ID_14300, RCID_BOSS_SECTORY);
                SectorY_801A0510(&gActors[59], 7);
                gActors[59].obj.pos.y = this->obj.pos.y - 202.0f;
                gActors[59].obj.pos.x = this->obj.pos.x;
                gActors[59].obj.pos.z = this->obj.pos.z - 30.0f;
                gActors[59].state = 6;
            }

            if (this->obj.pos.y == 0.0f) {
                AUDIO_PLAY_SFX(NA_SE_LIFT_UP, gDefaultSfxSource, 4);
            }

            Math_SmoothStepToF(&this->obj.pos.y, 365.0f, 0.1f, 5.0f, 0.1f);
            Math_SmoothStepToF(&gActors[59].obj.pos.y, 153.0f, 0.1f, 5.0f, 0.1f);
            Math_SmoothStepToF(&gPlayer[0].cam.eye.z, -28300.0f, 1.0f, 100.0f, 1.0f);

            if (gPlayer[0].cam.eye.z == -28300.0f) {
                Math_SmoothStepToF(&this->fwork[46], 128.0f, 1.0f, 16.0f, 1.0f);
                gBossHealthBar = this->health * 1.7f;
            }

            if (this->obj.pos.y == 365.0f) {
                AUDIO_PLAY_SFX(NA_SE_LIFT_UP_END, gDefaultSfxSource, 4);
                this->timer_050 = 20;
                this->timer_056 = 135;
            }
        }
    } else {
        gPlayer[0].cam.at.z = this->obj.pos.z;

        Math_SmoothStepToF(&gPlayer[0].cam.eye.z, -29000.0f, 1.0f, 5.0f, 1.0f);
        Math_SmoothStepToF(&gPlayer[0].cam.eye.x, 2000.0f, 1.0f, 8.0f, 1.0f);
        Math_SmoothStepToF(&this->fwork[46], 0.0f, 1.0f, 16.0f, 1.0f);

        if (this->timer_050 == 0) {
            this->swork[21] = 0;
        }

        if (this->timer_056 == 95) {
            AUDIO_PLAY_SFX(NA_SE_EN_BURNER_L, gActors[59].sfxSource, 4);
        }
        if (this->timer_056 < 96) {
            Math_SmoothStepToF(&gActors[59].fwork[0], 0.0f, 0.1f, 0.2f, 0.05f);
            if (this->timer_056 > 55) {
                Math_SmoothStepToF(&this->vel.z, 80.0f, 0.1f, 2.0f, 0.5f);
                Math_SmoothStepToF(&gActors[59].vel.z, 80.0f, 0.1f, 2.0f, 0.5f);
                if ((gGameFrameCount % 2) == 0) {
                    Effect_Effect390_Spawn(this->obj.pos.x, this->obj.pos.y - 150.0f, this->obj.pos.z, 0.0f, 0.0f, 0.0f,
                                           0.1f, 5);
                }
            }
        }
        if (this->timer_056 == 55) {
            D_i6_801A8440[0] = this->sfxSource[0];
            D_i6_801A8440[1] = this->sfxSource[1];
            D_i6_801A8440[2] = -500.0f;
            AUDIO_PLAY_SFX(NA_SE_EN_MS_DASH, D_i6_801A8440, 4);
            Audio_KillSfxBySource(gActors[59].sfxSource);
            this->fwork[34] = 4.5f;
            gActors[59].vel.z = -40.0f;
            this->vel.z = 120.0f;
        }
        if (this->timer_056 <= 55) {
            this->swork[21] = 1;
            Math_SmoothStepToF(&this->fwork[43], 0.0f, 0.1f, 0.1f, 0.1f);
            Math_SmoothStepToF(&this->vel.y, 20.0f, 0.1f, 5.0f, 0.5f);
            Math_SmoothStepToF(&gActors[59].vel.z, 0.0f, 0.1f, 1.0f, 0.5f);
        }
        if (this->timer_056 == 0.0f) {
            SectorY_80198244(this);
            this->vel.z = 80.0f;
            this->fwork[13] = 80.0f;
            this->obj.pos.z = -12000.0f;
            gScenery360[SHOGUN_SHIP].obj.pos.z = -20000.0f;
            this->fwork[43] = 0.0f;
            this->vel.y = 0.0f;
            gPlayer[0].state = PLAYERSTATE_ACTIVE;
            Camera_UpdateArwing360(&gPlayer[0], true);
            gPlayer[0].unk_014 = 0.0f;
            this->swork[34]++;
            Radio_PlayMessage(gMsg_ID_14310, RCID_BOSS_SECTORY);
            gBossFrameCount = 0;
        }
    }
}

bool SectorY_8019B528(SyShogun* this) {
    if (this->timer_050 != 0) {
        return false;
    }

    if (this->swork[33] <= ABS(this->obj.pos.x)) {
        return true;
    }

    if (this->swork[33] <= ABS(this->obj.pos.z)) {
        return true;
    }
    return false;
}

bool SectorY_8019B5CC(SyShogun* this) {
    f32 pad;
    Vec3f pos;

    if ((gBosses[1].health != 0) || (gBosses[2].health != 0)) {
        return false;
    }

    if (gLevelMode == LEVELMODE_ON_RAILS) {
        return false;
    }

    Math_Vec3fFromAngles(&pos, this->rot_078.x, this->rot_078.y, 700.0f);

    if ((fabsf(gScenery360[SHOGUN_SHIP].obj.pos.x - (this->obj.pos.x + pos.x)) < 2500.0f) &&
        (fabsf(gScenery360[SHOGUN_SHIP].obj.pos.z - (this->obj.pos.z + pos.z)) < 5000.0f) &&
        (fabsf(gScenery360[SHOGUN_SHIP].obj.pos.y - (this->obj.pos.y + pos.y)) < 1800.0f)) {
        return true;
    }

    return false;
}

void SectorY_8019B6E8(SyShogun* this) {
    f32 var4;
    f32 var3;
    f32 var2;
    f32 var;

    var = ABS(ABS(gPlayer[0].pos.x - this->obj.pos.x) + ABS(gPlayer[0].pos.y - this->obj.pos.y) +
              ABS(gPlayer[0].pos.z - 1000.0f - this->obj.pos.z));

    var2 = ABS(gActors[2].obj.pos.x - this->obj.pos.x) + ABS(gActors[2].obj.pos.y - this->obj.pos.y) +
           ABS(gActors[2].obj.pos.z - this->obj.pos.z);

    var3 = ABS(gActors[3].obj.pos.x - this->obj.pos.x) + ABS(gActors[3].obj.pos.y - this->obj.pos.y) +
           ABS(gActors[3].obj.pos.z - this->obj.pos.z);

    var4 = ABS(gActors[4].obj.pos.x - this->obj.pos.x) + ABS(gActors[4].obj.pos.y - this->obj.pos.y) +
           ABS(gActors[4].obj.pos.z - this->obj.pos.z);

    this->swork[22] = 1;
    this->fwork[18] = gPlayer[0].pos.x;
    this->fwork[19] = gPlayer[0].pos.y;
    this->fwork[20] = gPlayer[0].pos.z;
    this->fwork[24] = gPlayer[0].vel.x;
    this->fwork[25] = gPlayer[0].vel.y;
    this->fwork[26] = gPlayer[0].vel.z;

    if (var2 < var) {
        var = var2;
        this->swork[22]++;
        this->fwork[18] = gActors[2].obj.pos.x;
        this->fwork[19] = gActors[2].obj.pos.y;
        this->fwork[20] = gActors[2].obj.pos.z;
        this->fwork[24] = gActors[2].vel.x;
        this->fwork[25] = gActors[2].vel.y;
        this->fwork[26] = gActors[2].vel.z;
    }

    if (var3 < var) {
        this->swork[22] = 3;
        this->fwork[18] = gActors[3].obj.pos.x;
        this->fwork[19] = gActors[3].obj.pos.y;
        this->fwork[20] = gActors[3].obj.pos.z;
        this->fwork[24] = gActors[3].vel.x;
        this->fwork[25] = gActors[3].vel.y;
        this->fwork[26] = gActors[3].vel.z;
        var = var3;
    }

    if (var4 < var) {
        this->fwork[18] = gActors[4].obj.pos.x;
        this->fwork[19] = gActors[4].obj.pos.y;
        this->fwork[20] = gActors[4].obj.pos.z;
        this->fwork[24] = gActors[4].vel.x;
        this->fwork[25] = gActors[4].vel.y;
        this->fwork[26] = gActors[4].vel.z;
        this->swork[22] = 4;
    }
}

void SectorY_8019BBBC(SyShogun* this) {
    this->fwork[18] = gPlayer[0].pos.x;
    this->fwork[19] = gPlayer[0].pos.y;
    this->fwork[20] = gPlayer[0].pos.z;
    this->fwork[24] = gPlayer[0].vel.x;
    this->fwork[25] = gPlayer[0].vel.y;
    this->fwork[26] = gPlayer[0].vel.z;
}

void SectorY_8019BC14(SyShogun* this) {
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 var_fa0;

    if ((ABS(this->obj.pos.x) >= 11000.0f) || (ABS(this->obj.pos.z) >= 11000.0f)) {
        this->timer_052 = 2;
        return;
    }

    if ((this->swork[0x16] == 1) && (D_edisplay_801615D0.z > 0.0f)) {
        this->timer_052 = 2;
        return;
    }

    if (this->swork[0x16] != 1) {
        var_fa0 = ((ABS(this->fwork[0x12] - this->fwork[1]) + ABS(this->fwork[0x14] - this->fwork[3]) +
                    ABS(this->fwork[0x13] - this->fwork[2])) /
                   140.0f) -
                  2.0f;
        this->fwork[0x12] = this->fwork[0x12] + this->fwork[0x18] * var_fa0;
        this->fwork[0x13] = this->fwork[0x13] + this->fwork[0x19] * var_fa0;
        this->fwork[0x14] = this->fwork[0x14] + this->fwork[0x1A] * var_fa0;
    }

    if ((fabsf(this->fwork[3] - this->fwork[0x14]) > 300.0f) || (fabsf(this->fwork[1] - this->fwork[0x12]) > 300.0f)) {
        sp3C = Math_RadToDeg(
            Math_Atan2F(this->fwork[0x12] - this->fwork[1] - this->rot_078.x, this->fwork[0x14] - this->fwork[3]));
        sp40 = ABS(this->fwork[0x12] - this->fwork[1]) + ABS(this->fwork[0x14] - this->fwork[3]);
        sp40 = Math_RadToDeg(-Math_Atan2F(this->fwork[0x13] - this->fwork[2], sp40));
        sp38 = Math_RadToDeg(Math_Atan2F(this->fwork[1] - this->fwork[0x15], this->fwork[3] - this->fwork[0x17]));
        var_fa0 = ABS(this->fwork[1] - this->fwork[0x15]) + ABS(this->fwork[3] - this->fwork[0x17]);
        var_fa0 = Math_RadToDeg(-Math_Atan2F(this->fwork[2] - this->fwork[0x16], var_fa0));
        sp38 = sp3C - sp38;
        var_fa0 = sp40 - var_fa0;

        if (sp38 < 0.0f) {
            sp38 += 360.0f;
        }
        if (var_fa0 < 0.0f) {
            var_fa0 += 360.0f;
        }

        if (((sp38 < 41.0f) || (sp38 > 319.0f)) && ((var_fa0 < 41.0f) || (var_fa0 > 319.0f))) {
            this->timer_054 = 4;
            this->fwork[4] = 30.0f;

            sp4C = gPlayer[0].pos.x;
            sp48 = gPlayer[0].pos.y;
            sp44 = gPlayer[0].pos.z;

            gPlayer[0].pos.x = this->fwork[0x12];
            gPlayer[0].pos.y = this->fwork[0x13];
            gPlayer[0].trueZpos = gPlayer[0].pos.z = this->fwork[0x14];

            Effect_EnemyLaser(OBJ_EFFECT_354, this->fwork[1], this->fwork[2], this->fwork[3], 100.0f);

            gPlayer[0].pos.x = sp4C;
            gPlayer[0].pos.y = sp48;
            gPlayer[0].trueZpos = gPlayer[0].pos.z = sp44;

            if (this->index == 0) {
                AUDIO_PLAY_SFX(NA_SE_EN_MS_SHOT_L, this->sfxSource, 4);
            } else {
                AUDIO_PLAY_SFX(NA_SE_EN_MS_SHOT_S, this->sfxSource, 4);
            }
        }
    }

    if (this->index == 0) {
        this->timer_052 = RAND_INT(20.0f) + 15;
    } else {
        this->timer_052 = RAND_INT(20.0f) + 25;
    }
}

void SectorY_8019C194(SyShogun* this, f32 zSpeed, f32 xSpeed) {
    f32 sp2C;
    f32 sp28;

    if ((gBossFrameCount > 250) && (this->fwork[34] == 2.8f)) {
        switch (D_ctx_80177A10[8]) {
            case 0:
                if (gTeamShields[TEAM_ID_FALCO] > 0) {
                    AllRange_PlayMessage(gMsg_ID_14200, RCID_FALCO);
                }
                break;

            case 1:
                if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                    AllRange_PlayMessage(gMsg_ID_14210, RCID_PEPPY);
                }
                break;

            case 2:
                if ((gTeamShields[TEAM_ID_SLIPPY] > 0) && (gBosses[1].obj.status != OBJ_FREE) &&
                    (gBosses[2].obj.status != OBJ_FREE)) {
                    AllRange_PlayMessage(gMsg_ID_14220, RCID_SLIPPY);
                }
                break;
        }
        D_ctx_80177A10[8] += (gGameFrameCount % 2U) + 1;
        D_ctx_80177A10[8] %= 4U;
    }

    if ((xSpeed > 800.0f) || (zSpeed > 300.0f)) {
        this->fwork[44] += 8.0f;
        if (this->fwork[44] >= 360.0f) {
            this->fwork[44] = 0.0f;
        }

        if (this->index == 0) {
            sp2C = SIN_DEG(this->fwork[44]) * ABS(this->vel.z * 1.5f);
            this->obj.pos.x += sp2C;

            sp28 = SIN_DEG(this->fwork[44]) * ABS(this->vel.x * 1.5f);
            this->obj.pos.z += sp28;
        } else {
            sp2C = SIN_DEG(this->fwork[44]) * ABS(this->vel.z * 1.2f);
            this->obj.pos.x += sp2C;

            sp28 = SIN_DEG(this->fwork[44]) * ABS(this->vel.x * 1.2f);
            this->obj.pos.z += sp28;
        }

        if (!SectorY_8019B5CC(this)) {
            if (this->index == 0) {
                this->obj.pos.y += SIN_DEG(this->fwork[44]) * 30.0f;
            } else {
                this->obj.pos.y += SIN_DEG(this->fwork[44]) * 10.0f;
            }
        }

        if (this->index == 0) {
            if (ABS(this->vel.z) < ABS(this->vel.x)) {
                sp2C = sp28;
                if ((this->obj.rot.z <= 90.0f) || (this->obj.rot.z >= 270.0f)) {
                    if ((this->obj.rot.y >= 45.0f) && (this->obj.rot.y <= 135.0f)) {
                        sp2C = -sp28;
                    }
                } else {
                    if ((this->obj.rot.y >= 225.0f) && (this->obj.rot.y <= 315.0f)) {
                        sp2C = -sp28;
                    }
                }
            } else {
                if ((this->obj.rot.z <= 90.0f) || (this->obj.rot.z >= 270.0f)) {
                    if ((this->obj.rot.y >= 135.0f) && (this->obj.rot.y <= 225.0f)) {
                        sp2C = -sp2C;
                    }
                } else {
                    if ((this->obj.rot.y <= 45.0f) || (this->obj.rot.y >= 315.0f)) {
                        sp2C = -sp2C;
                    }
                }
            }

            if (sp2C == 0.0f) {
                this->fwork[41] = ABS(sp2C * 0.01f) + 0.8f;
            }
            if (sp2C > 0.0f) {
                if (this->fwork[41] == 0.0f) {
                    this->fwork[41] = ABS(sp2C * 0.01f) + 0.8f;
                    AUDIO_PLAY_SFX(NA_SE_ARWING_BRAKE, this->sfxSource, 4);
                }
            } else if (this->fwork[42] == 0.0f) {
                this->fwork[42] = ABS(sp2C * 0.01f) + 0.8f;
                AUDIO_PLAY_SFX(NA_SE_ARWING_BRAKE, this->sfxSource, 4);
            }
        }
    }
}

BossFuncs D_i6_801A6910[] = {
    SectorY_80197F84, SectorY_80198238, SectorY_80198238, SectorY_801983E4, SectorY_80198CE4, SectorY_80199438,
    SectorY_80199DAC, SectorY_8019A520, SectorY_8019A66C, SectorY_8019A898, SectorY_8019AAF0, SectorY_8019AEEC,
};

void SectorY_SyShogun_Update(SyShogun* this) {
    s32 i;
    f32 sp1E8;
    f32 sp1E4;
    f32 sp1E0;
    f32 sp1DC;
    f32 sp1D8;
    f32 sp1D4;
    s32 sp1D0;
    RadarMark* radarMark;
    Vec3f frameTable[30];
    Vec3f src;
    Vec3f dest;
    s32 pad;

    if (gPlayer[0].state != PLAYERSTATE_START_360) {
        if (this->swork[34] == 1) {
            if (this->health > 0) {
                gScenery360[SHOGUN_SHIP].obj.pos.z += 20.0f;
            }
            if (gScenery360[SHOGUN_SHIP].obj.pos.z == 0.0f) {
                this->swork[34]++;
            }
        }

        if (this->index == 2) {
            if ((ABS(this->obj.pos.x - gBosses[1].obj.pos.x) < 800.0f) &&
                (ABS(this->obj.pos.z - gBosses[1].obj.pos.z) < 800.0f) && (this->health > 0) &&
                (gBosses[1].health > 0)) {
                if (ABS(this->obj.pos.y - gBosses[1].obj.pos.y) <= 800.0f) {
                    this->obj.pos.y += 20.0f;
                    gBosses[1].obj.pos.y -= 20.0f;
                }
            }
        }

        if ((this->fwork[34] <= 1.0f) && (this->fwork[34] > 0.5f)) {
            Audio_KillSfxBySource(this->sfxSource);
        }

        gBossFrameCount++;

        this->fwork[0] = 0.1f;

        if (this->swork[24] != 0) {
            this->swork[24]--;
        }

        if (this->health > 0) {
            D_i6_801A6910[this->swork[20]](this);
        }

        if (this->timer_058 != 0) {
            SectorY_80199438(this);
        }

        if ((this->swork[29] != 0) && !(this->swork[29] & gGameFrameCount)) {
            Effect_Effect390_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, this->vel.x, this->vel.y,
                                   this->vel.z, 0.1f, 5);
        }

        switch (this->swork[21]) {
            case 0:
                this->animFrame = Animation_GetFrameCount(&D_SY_602B778) - 1;
                sp1D0 = Animation_GetFrameData(&D_SY_602B778, this->animFrame, frameTable);
                break;

            case 1:
                this->animFrame = Animation_GetFrameCount(&D_SY_60265B4) - 1;
                sp1D0 = Animation_GetFrameData(&D_SY_60265B4, this->animFrame, frameTable);
                break;

            case 2:
                this->animFrame = Animation_GetFrameCount(&D_SY_6029B48) - 1;
                sp1D0 = Animation_GetFrameData(&D_SY_6029B48, this->animFrame, frameTable);
                break;

            case 3:
                this->animFrame = Animation_GetFrameCount(&D_SY_602B8DC) - 1;
                sp1D0 = Animation_GetFrameData(&D_SY_602B8DC, this->animFrame, frameTable);
                break;

            case 4:
                this->animFrame++;
                if (this->animFrame >= Animation_GetFrameCount(&D_SY_6003348)) {
                    this->animFrame = Animation_GetFrameCount(&D_SY_6003348) - 1;
                }
                sp1D0 = Animation_GetFrameData(&D_SY_6003348, this->animFrame, frameTable);
                break;

            case 5:
                this->animFrame++;
                if (this->animFrame >= Animation_GetFrameCount(&D_SY_602738C)) {
                    this->animFrame = 0;
                }
                sp1D0 = Animation_GetFrameData(&D_SY_602738C, this->animFrame, frameTable);
                break;

            case 6:
                sp1D0 = Animation_GetFrameData(&D_SY_602738C, this->animFrame, frameTable);
                break;

            case 7:
                if (this->animFrame < (Animation_GetFrameCount(&D_SY_602645C) - 1)) {
                    this->animFrame++;
                }
                sp1D0 = Animation_GetFrameData(&D_SY_602645C, this->animFrame, frameTable);
                break;

            case 8:
                if (this->animFrame < (Animation_GetFrameCount(&D_SY_60258A0) - 1)) {
                    this->animFrame++;
                }
                sp1D0 = Animation_GetFrameData(&D_SY_60258A0, this->animFrame, frameTable);
                break;

            case 9:
                this->animFrame++;
                if (this->animFrame >= Animation_GetFrameCount(&D_SY_60034C4)) {
                    this->animFrame = 0;
                }
                sp1D0 = Animation_GetFrameData(&D_SY_60034C4, this->animFrame, frameTable);
                break;
        }

        this->obj.rot.x = this->rot_078.x;
        this->obj.rot.y = this->rot_078.y;
        this->obj.rot.z = this->rot_078.z;

        Matrix_RotateZ(gCalcMatrix, -this->vwork[29].z * M_DTOR, MTXF_NEW);
        Matrix_RotateX(gCalcMatrix, -this->vwork[29].x * M_DTOR, MTXF_APPLY);
        Matrix_RotateY(gCalcMatrix, -this->vwork[29].y * M_DTOR, MTXF_APPLY);

        Matrix_RotateZ(gCalcMatrix, -this->obj.rot.z * M_DTOR, MTXF_APPLY);
        Matrix_RotateX(gCalcMatrix, -this->obj.rot.x * M_DTOR, MTXF_APPLY);
        Matrix_RotateY(gCalcMatrix, -this->obj.rot.y * M_DTOR, MTXF_APPLY);

        if ((this->health > 0) && (this->swork[20] < 10)) {
            src.x = this->fwork[18] - this->obj.pos.x;
            src.y = this->fwork[19] - this->obj.pos.y;
            src.z = this->fwork[20] - this->obj.pos.z;

            Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

            sp1E4 = Math_RadToDeg(Math_Atan2F(dest.x, dest.z));
            sp1E8 = Math_RadToDeg(-Math_Atan2F(dest.y, sqrtf(SQ(dest.x) + SQ(dest.z))));

            if ((sp1E8 > 30.0f) && (sp1E8 <= 180.0f)) {
                sp1E8 = 30.0f;
            }
            if ((sp1E8 < 330.0f) && (sp1E8 > 180.0f)) {
                sp1E8 = 330.0f;
            }
            if ((sp1E4 > 80.0f) && (sp1E4 <= 180.0f)) {
                sp1E4 = 80.0f;
            }
            if ((sp1E4 < 280.0f) && (sp1E4 > 180.0f)) {
                sp1E4 = 280.0f;
            }

            Math_SmoothStepToAngle(&this->fwork[6], sp1E4, 0.2f, 4.0f, 0.1f);
            Math_SmoothStepToAngle(&this->fwork[5], sp1E8, 0.2f, 4.0f, 0.1f);
            Matrix_RotateX(gCalcMatrix, -this->fwork[5] * M_DTOR, MTXF_APPLY);
            Matrix_RotateY(gCalcMatrix, -this->fwork[6] * M_DTOR, MTXF_APPLY);

            src.x = this->fwork[18] - this->obj.pos.x;
            src.y = (this->fwork[19] - this->obj.pos.y) + 20.0f;
            src.z = this->fwork[20] - this->obj.pos.z;

            Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

            sp1E0 = Math_RadToDeg(Math_Atan2F(dest.x, dest.z));
            sp1DC = Math_RadToDeg(-Math_Atan2F(dest.y, sqrtf(SQ(dest.x) + SQ(dest.z))));

            if ((sp1DC > 30.0f) && (sp1DC <= 180.0f)) {
                sp1DC = 30.0f;
            }
            if ((sp1DC < 330.0f) && (sp1DC > 180.0f)) {
                sp1DC = 330.0f;
            }
            if ((sp1E0 > 80.0f) && (sp1E0 <= 180.0f)) {
                sp1E0 = 80.0f;
            }
            if ((sp1E0 < 280.0f) && (sp1E0 > 180.0f)) {
                sp1E0 = 280.0f;
            }

            Math_SmoothStepToAngle(&this->fwork[8], sp1E0, 0.4f, 8.0f, 0.1f);
            Math_SmoothStepToAngle(&this->fwork[7], sp1DC, 0.4f, 8.0f, 0.1f);

            src.x = (this->fwork[18] - this->obj.pos.x) + (COS_DEG(this->obj.rot.y) * 100.0f);
            src.y = (this->fwork[19] - this->obj.pos.y) - 80.0f;
            src.z = this->fwork[20] - this->obj.pos.z;

            Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

            sp1D8 = Math_RadToDeg(Math_Atan2F(dest.x, dest.z));
            sp1D4 = Math_RadToDeg(-Math_Atan2F(dest.y, sqrtf(SQ(dest.x) + SQ(dest.z))));

            if ((sp1D4 > 80.0f) && (sp1D4 <= 180.0f)) {
                sp1D4 = 80.0f;
            }
            if ((sp1D4 < 270.0f) && (sp1D4 > 180.0f)) {
                sp1D4 = 270.0f;
            }
            if ((sp1D8 > 40.0f) && (sp1D8 <= 180.0f)) {
                sp1D8 = 40.0f;
            }
            if ((sp1D8 < 350.0f) && (sp1D8 > 180.0f)) {
                sp1D8 = 350.0f;
            }

            Math_SmoothStepToAngle(&this->fwork[15], sp1D8, 0.2f, 4.0f, 0.1f);
            Math_SmoothStepToAngle(&this->fwork[14], sp1D4, 0.2f, 4.0f, 0.1f);

            Matrix_RotateX(gCalcMatrix, -this->fwork[14] * M_DTOR, MTXF_APPLY);
            Matrix_RotateY(gCalcMatrix, -this->fwork[15] * M_DTOR, MTXF_APPLY);

            src.x = this->fwork[18] - this->obj.pos.x;
            src.y = (this->fwork[19] - this->obj.pos.y) + (COS_DEG(this->obj.rot.z) * 40.0f);
            src.z = (this->fwork[20] - this->obj.pos.z) - (COS_DEG(this->obj.rot.y) * 60.0f);

            Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

            sp1E4 = Math_RadToDeg(Math_Atan2F(dest.x, dest.z));
            sp1E8 = Math_RadToDeg(-Math_Atan2F(dest.y, sqrtf(SQ(dest.x) + SQ(dest.z))));

            if ((sp1E8 > 80.0f) && (sp1E8 <= 180.0f)) {
                sp1E8 = 80.0f;
            }
            if ((sp1E8 < 300.0f) && (sp1E8 > 180.0f)) {
                sp1E8 = 300.0f;
            }
            if ((sp1E4 > 11.0f) && (sp1E4 <= 180.0f)) {
                sp1E4 = 11.0f;
            }
            if ((sp1E4 < 270.0f) && (sp1E4 > 180.0f)) {
                sp1E4 = 270.0f;
            }

            Math_SmoothStepToAngle(&this->fwork[17], sp1E4, 0.2f, 4.0f, 0.1f);
            Math_SmoothStepToAngle(&this->fwork[16], sp1E8, 0.2f, 4.0f, 0.1f);
        } else {
            Math_SmoothStepToAngle(&this->fwork[6], 0.0f, 0.2f, 4.0f, 0.1f);
            Math_SmoothStepToAngle(&this->fwork[5], 0.0f, 0.2f, 4.0f, 0.1f);
            Math_SmoothStepToAngle(&this->fwork[8], 0.0f, 0.4f, 8.0f, 0.1f);
            Math_SmoothStepToAngle(&this->fwork[7], 0.0f, 0.4f, 8.0f, 0.1f);
            Math_SmoothStepToAngle(&this->fwork[15], 0.0f, 0.4f, 8.0f, 0.1f);
            Math_SmoothStepToAngle(&this->fwork[14], 0.0f, 0.4f, 8.0f, 0.1f);
        }
        Math_SmoothStepToF(&this->fwork[4], 0.0f, 0.2f, 10.0f, 0.0f);
        Math_SmoothStepToF(&this->fwork[34], 0.0f, 0.1f, 0.2f, 0.05f);
        Math_SmoothStepToF(&this->fwork[41], 0.0f, 0.1f, 0.05f, 0.05f);
        Math_SmoothStepToF(&this->fwork[42], 0.0f, 0.1f, 0.05f, 0.05f);
        Math_SmoothStepToVec3fArray(frameTable, this->vwork, 1, sp1D0, this->fwork[0], 100.0f, 0.0f);

        if ((this->dmgType != DMG_NONE) && (this->health > 0)) {
            this->dmgType = DMG_NONE;
            if (this->dmgPart == 0) {
                if (this->swork[25] == 0) {
                    this->swork[24] = 15;
                    AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
                } else {
                    SectorY_80198F5C(this);
                }
            } else {
                SectorY_80198F5C(this);
            }
        }

        if (this->index == 0) {
            radarMark = &gRadarMarks[this->index + 1];
            radarMark->enabled = true;
            radarMark->type = 102;
            radarMark->pos.x = this->obj.pos.x;
            radarMark->pos.y = this->obj.pos.y;
            radarMark->pos.z = this->obj.pos.z;
            radarMark->yRot = this->rot_078.y + 180.0f;
        } else {
            radarMark = &gRadarMarks[this->index + 4];
            radarMark->enabled = true;
            radarMark->type = 10;
            radarMark->pos.x = this->obj.pos.x;
            radarMark->pos.y = this->obj.pos.y;
            radarMark->pos.z = this->obj.pos.z;
            radarMark->yRot = this->rot_078.y + 180.0f;
        }

        if (gBossFrameCount == 250) {
            for (i = ARRAY_COUNT(gActors) - 1; i >= 0; i--) {
                if (gActors[i].obj.status == OBJ_ACTIVE) {
                    gTeamEventActorIndex[gActors[i].iwork[12]] = i;
                }
            }
        }
        if ((gBossFrameCount == 250) && (gTeamShields[TEAM_ID_SLIPPY] != 0) && (this->swork[34] == 0)) {
            Radio_PlayMessage(gMsg_ID_2225, RCID_SLIPPY);
        }
        if ((gBossFrameCount == 620) && (this->swork[34] == 0)) {
            gShowBossHealth = true;
        }
        if ((gBossFrameCount >= 350) || (this->swork[34] != 0)) {
            if (this->swork[34] != 0) {
                gBossHealthBar = this->health * 1.7f;
            } else if (gBosses[0].work_04A == 0) {
                gBossHealthBar = (gBosses[1].health + gBosses[2].health) * 1.275f;
            }
        }

        if (D_edisplay_801615D0.z > 0.0f) {
            this->swork[30]++;
            if (this->swork[30] > 300 && ((ABS(D_edisplay_801615D0.z) + ABS(D_edisplay_801615D0.x)) < 3500.0f) &&
                (gRadioState == 0)) {
                if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                    Radio_PlayMessage(gMsg_ID_2282, RCID_PEPPY);
                }
                this->swork[30] = 150;
            }

            if (this->swork[30] > 100) {
                if ((((ABS(D_edisplay_801615D0.z) + ABS(D_edisplay_801615D0.x)) < 500.0f) &&
                     gTeamShields[TEAM_ID_FALCO] > 0)) {
                    Radio_PlayMessage(gMsg_ID_2233, RCID_FALCO);
                }
            }

            if (D_edisplay_801615D0.x > 0.0f) {
                gPlayer[0].flags_228 = PFLAG_228_4;
            } else {
                gPlayer[0].flags_228 = PFLAG_228_5;
            }

        } else {
            this->swork[30] = 0;
        }
    }
}

bool SectorY_8019DC4C(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    SyShogun* boss = (SyShogun*) thisx;
    Vec3f sp10 = { 0.0f, 0.0f, 0.0f };

    if ((boss->timer_05C % 2) == 0) {
        if (boss->index == 1) {
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 100, 100, 255, 255);
        } else {
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 100, 255);
        }
    } else {
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 32, 32, 255, 255);
    }

    switch (limbIndex) {
        case 2:
            rot->z -= boss->fwork[4];
            rot->z += boss->fwork[16];
            rot->y -= boss->fwork[17];
            break;

        case 3:
            rot->z -= boss->fwork[4];
            rot->z += boss->fwork[14];
            rot->x -= boss->fwork[15];
            break;

        case 4:
            *dList = NULL;
            break;

        case 17:
            rot->x += boss->fwork[8];
            rot->y -= boss->fwork[7];
            *dList = D_SY_6014BD0;
            break;

        case 18:
            rot->x += boss->fwork[6];
            rot->y -= boss->fwork[5];
            break;
    }
    return false;
}

bool SectorY_SyShogun_OverrideLimbDraw(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    SyShogun* this = (SyShogun*) thisx;
    Vec3f sp38 = { 0.0f, 0.0f, 0.0f };

    if (this->index != 0) {
        return SectorY_8019DC4C(limbIndex, dList, pos, rot, this);
    }

    if ((this->timer_05C % 2) != 0) {
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 32, 32, 255, 255);
    } else {
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
    }

    switch (limbIndex) {
        case 2:
            rot->z -= this->fwork[4];
            rot->z += this->fwork[16];
            rot->y -= this->fwork[17];
            break;

        case 3:
            rot->z -= this->fwork[4];
            rot->z += this->fwork[14];
            rot->x -= this->fwork[15];
            break;

        case 4:
            if (this->swork[25] == 0) {
                *dList = D_SY_6013600;
                if ((this->swork[24] % 2) != 0) {
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 0, 255, 0, 255);
                }
            } else {
                *dList = NULL;
            }
            break;

        case 17:
            rot->x += this->fwork[8];
            rot->y -= this->fwork[7];
            *dList = D_SY_6014BD0;
            break;

        case 18:
            rot->x += this->fwork[6];
            rot->y -= this->fwork[5];
            break;
    }
    return false;
}

void SectorY_SyShogun_PostLimbDraw(s32 limbIndex, Vec3f* rot, void* thisx) {
    Vec3f sp7C = { 40.0f, -30.0f, 0.0f };
    Vec3f sp70 = { -40.0f, -30.0f, 0.0f };
    Vec3f sp64 = { 0.0f, 0.0f, 0.0f };
    Vec3f sp58 = { 0.0f, 30.0f, -50.0f };
    Vec3f sp4C = { 6.0f, -1.0f, -53.0f };
    Vec3f sp40 = { 0.0f, 0.0f, 66.0f };
    Vec3f sp34 = { 0.0f, 30.0f, -60.0f };
    Vec3f sp28;
    SyShogun* this = (SyShogun*) thisx;

    switch (limbIndex) {
        case 0:
            if (this->index != 0) {
                Matrix_MultVec3f(gCalcMatrix, &sp58, &sp28);
            } else {
                Matrix_MultVec3f(gCalcMatrix, &sp34, &sp28);
            }
            this->fwork[31] = sp28.x;
            this->fwork[32] = sp28.y;
            this->fwork[33] = sp28.z;
            break;

        case 1:
            Matrix_Push(&gCalcMatrix);
            Matrix_MultVec3f(gCalcMatrix, &sp70, &sp28);
            this->fwork[21] = sp28.x;
            this->fwork[22] = sp28.y;
            this->fwork[23] = sp28.z;
            Matrix_Pop(&gCalcMatrix);
            Matrix_MultVec3f(gCalcMatrix, &sp7C, &sp28);
            this->fwork[1] = sp28.x;
            this->fwork[2] = sp28.y;
            this->fwork[3] = sp28.z;
            break;

        case 3:
            if (this->index == 0) {
                Matrix_MultVec3f(gCalcMatrix, &sp4C, &sp28);
                this->fwork[35] = sp28.x;
                this->fwork[36] = sp28.y;
                this->fwork[37] = sp28.z;
            }
            break;

        case 4:
            if (this->index == 0) {
                Matrix_MultVec3f(gCalcMatrix, &sp64, &sp28);
                this->fwork[28] = sp28.x;
                this->fwork[29] = sp28.y;
                this->fwork[30] = sp28.z;
            }
            break;

        case 6:
            if (this->index == 0) {
                Matrix_MultVec3f(gCalcMatrix, &sp40, &sp28);
                this->fwork[38] = sp28.x;
                this->fwork[39] = sp28.y;
                this->fwork[40] = sp28.z;
            }
            break;

        default:
            break;
    }
}

f32 D_i6_801A69AC[20] = { 0.3f,   0.7f,   1.3f,  0.7f,    0.3f,  0.0f,   10.0f, 20.0f,  300.0f, 100.0f,
                          200.0f, 100.0f, 60.0f, -260.0f, 80.0f, 100.0f, 80.0f, 262.0f, 285.0f, 252.0f };

void SectorY_SyShogun_Draw(SyShogun* this) {
    f32 sp9C;
    f32 sp98;
    f32 sp94;
    f32 sp90;
    f32 sp8C;
    f32 sp88;

    if ((this->index != 0) || ((this->swork[24] % 2) != 0) || ((this->timer_05C % 2) != 0)) {
        RCP_SetupDL_30(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
    } else {
        RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
    }

    if ((this->health > 0) || (this->swork[36] == 0)) {
        Animation_DrawSkeleton(2, D_SY_602D140, this->vwork, SectorY_SyShogun_OverrideLimbDraw,
                               SectorY_SyShogun_PostLimbDraw, this, gCalcMatrix);
        if (this->timer_054 != 0) {
            sp9C = D_i6_801A69AC[this->timer_054];
            RCP_SetupDL_49();
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
            gDPSetEnvColor(gMasterDisp++, 255, 48, 0, 255);
            Matrix_Pop(&gGfxMatrix);
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, this->fwork[1], this->fwork[2], this->fwork[3], MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, sp9C, sp9C, sp9C, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, aOrbDL);
        }

        if (this->fwork[34] != 0.0f) {
            RCP_SetupDL_49();
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
            gDPSetEnvColor(gMasterDisp++, 32, 255, 32, 255);
            Matrix_Pop(&gGfxMatrix);
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, this->fwork[31], this->fwork[32], this->fwork[33], MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, this->fwork[34], this->fwork[34], this->fwork[34], MTXF_APPLY);
            Matrix_RotateX(gGfxMatrix, -this->obj.rot.x * M_DTOR, MTXF_APPLY);
            Matrix_RotateZ(gGfxMatrix, -this->obj.rot.z * M_DTOR, MTXF_APPLY);
            sp98 = gPlayer[0].cam.eye.x - this->obj.pos.x;
            sp94 = gPlayer[0].cam.eye.y - this->obj.pos.y;
            sp90 = gPlayer[0].cam.eye.z - (this->obj.pos.z + gPathProgress);
            sp8C = -Math_Atan2F(sp98, sp90);
            sp9C = sqrtf(SQ(sp90) + SQ(sp98));
            sp88 = Math_Atan2F(sp94, sp9C);
            Matrix_RotateY(gGfxMatrix, -sp8C, MTXF_APPLY);
            Matrix_RotateX(gGfxMatrix, -sp88, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, aOrbDL);
        }

        if (this->index == 0) {
            if (this->fwork[41] != 0.0f) {
                RCP_SetupDL_49();
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
                gDPSetEnvColor(gMasterDisp++, 32, 255, 32, 255);
                Matrix_Pop(&gGfxMatrix);
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, this->fwork[35], this->fwork[36], this->fwork[37], MTXF_APPLY);
                Matrix_RotateY(gGfxMatrix, this->obj.rot.y * M_DTOR, MTXF_APPLY);
                Matrix_RotateX(gGfxMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);
                Matrix_RotateZ(gGfxMatrix, this->obj.rot.z * M_DTOR, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, this->fwork[41] * 2.0f, this->fwork[41], this->fwork[41] * 2.0f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, aOrbDL);
            }

            if (this->fwork[42] != 0.0f) {
                RCP_SetupDL_49();
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
                gDPSetEnvColor(gMasterDisp++, 32, 255, 32, 255);
                Matrix_Pop(&gGfxMatrix);
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, this->fwork[38], this->fwork[39], this->fwork[40], MTXF_APPLY);
                Matrix_RotateY(gGfxMatrix, this->obj.rot.y * M_DTOR, MTXF_APPLY);
                Matrix_RotateX(gGfxMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);
                Matrix_RotateZ(gGfxMatrix, this->obj.rot.z * M_DTOR, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, this->fwork[42] * 2.0f, this->fwork[42], this->fwork[42] * 2.0f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, aOrbDL);
            }
        }

        if (this->fwork[43] != 0.0f) {
            RCP_SetupDL_49();
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 0, 0, 0, 255);
            gDPSetEnvColor(gMasterDisp++, 0, 0, 0, 0);
            Matrix_Pop(&gGfxMatrix);
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, this->obj.pos.x, 157.0f, this->obj.pos.z, MTXF_APPLY);
            Matrix_RotateX(gGfxMatrix, M_PI / 2, MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, this->fwork[43], this->fwork[43], this->fwork[43], MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, aOrbDL);
        }

        if (this->fwork[46] != 0.0f) {
            RCP_SetupDL_49();
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, (s32) this->fwork[46], (s32) this->fwork[46], 0,
                            (s32) this->fwork[46]);
            gDPSetEnvColor(gMasterDisp++, 0, 0, 0, 0);
            Matrix_Pop(&gGfxMatrix);
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, this->obj.pos.x + 10.0f, this->obj.pos.y + 70.0f, this->obj.pos.z + 60.0f,
                             MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, 0.4f, 0.2f, 0.2f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, aOrbDL);
            Matrix_Translate(gGfxMatrix, -46.0f, 0, 0, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, aOrbDL);
        }
    }
}

Vec3f D_i6_801A69FC[10] = {
    { 0.0f, -80.0f, 800.0f },      { -500.0f, -100.0f, 400.0f },  { 500.0f, -140.0f, 400.0f },
    { 3250.0f, 600.0f, 3500.0f },  { -2000.0f, 400.0f, 5000.0f }, { 2500.0f, 400.0f, 5000.0f },
    { -1000.0f, 400.0f, 6000.0f }, { 250.0f, 400.0f, 2500.0f },   { -2000.0f, 0.0f, 4000.0f },
    { 2500.0f, 0.0f, 4000.0f },
};

void SectorY_8019EB80(void) {
    ActorCutscene* actor = &gActors[0];
    s32 i;
    s32 actorCount;

    if (gHitCount >= 100) {
        actorCount = 9; // Teammates + Cornerian ships
    } else {
        actorCount = 2; // Teammates only
    }

    Rand_SetSeed(1, 29100, 9786);

    for (i = 0; i <= actorCount; i++, actor++) {
        if (((i == 0) && (gTeamShields[TEAM_ID_PEPPY] <= 0.0f)) ||
            ((i == 1) && (gTeamShields[TEAM_ID_SLIPPY] <= 0.0f)) ||
            ((i == 2) && (gTeamShields[TEAM_ID_FALCO] <= 0.0f))) {
            continue;
        }
        Actor_Initialize(actor);
        actor->obj.status = OBJ_INIT;
        actor->obj.id = OBJ_ACTOR_CUTSCENE;

        actor->obj.pos.x = (D_i6_801A69FC[i].x * 0.5f) + gPlayer[0].pos.x + RAND_FLOAT_CENTERED_SEEDED(2000.0f);
        actor->obj.pos.y = D_i6_801A69FC[i].y + gPlayer[0].pos.y + RAND_FLOAT_SEEDED(1000.0f);
        actor->obj.pos.z = D_i6_801A69FC[i].z + gPlayer[0].pos.z + RAND_FLOAT_SEEDED(1000.0f);

        actor->rot_0F4.z = RAND_FLOAT_CENTERED_SEEDED(200.0f);

        actor->vwork[0].x = (D_i6_801A69FC[i].x * 0.5f) + gPlayer[0].pos.x;
        actor->vwork[0].y = D_i6_801A69FC[i].y + gPlayer[0].pos.y;
        actor->vwork[0].z = D_i6_801A69FC[i].z + gPlayer[0].pos.z;

        actor->state = 1;
        Object_SetInfo(&actor->info, actor->obj.id);

        if (i >= 3) {
            actor->animFrame = ACTOR_CS_SY_SHIP_1_SHRINK;
            actor->rot_0F4.z = 0.0f;
        }
        if (i >= 7) {
            actor->animFrame = ACTOR_CS_SY_SHIP_2;
            actor->scale = 0.125f;
        }
        actor->iwork[11] = 1;

        if (CVarGetInteger("gTeamFaces", 1) == 1) {
            // @port: Setup team faces
            if ((i >= 0) && (i <= 2)) {
                actor->iwork[14] = i + 2;
            }
        }

        AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, actor->sfxSource, 4);
    }
}

void SectorY_LevelComplete(Player* player) {
    s32 i;
    f32 temp1;
    f32 temp2;
    s32 pad[2];
    Vec3f sp60;
    Vec3f sp54;
    SyShogun* boss = &gBosses[0];
    f32 temp_ft1;

    switch (player->csState) {
        case 0:
            gCsFrameCount = 0;
            player->aerobaticPitch = 0.0f;
            player->camRoll = 0.0f;
            player->baseSpeed = 40.0f;
            player->boostSpeed = 0.0f;
            player->arwing.upperRightFlapYrot = player->arwing.upperLeftFlapYrot = player->arwing.bottomRightFlapYrot =
                player->arwing.bottomLeftFlapYrot = player->zRotBarrelRoll = player->zRotBank = 0.0f;
            player->draw = true;
            D_ctx_80177A48[8] = Math_RadToDeg(
                Math_Atan2F(gPlayer[0].cam.eye.x - boss->obj.pos.x, gPlayer[0].cam.eye.z - boss->obj.pos.z));
            Matrix_RotateY(gCalcMatrix, D_ctx_80177A48[8] * M_DTOR, MTXF_NEW);
            sp60.x = 0.0f;
            sp60.y = 0.0f;
            sp60.z = 1400.0f;
            Matrix_MultVec3f(gCalcMatrix, &sp60, &sp54);
            gCsCamEyeX = boss->obj.pos.x + sp54.x;
            gCsCamEyeY = boss->obj.pos.y + 400.0f;
            gCsCamEyeZ = boss->obj.pos.z + sp54.z;
            gCsCamAtX = boss->obj.pos.x;
            gCsCamAtY = boss->obj.pos.y;
            gCsCamAtZ = boss->obj.pos.z;

            for (i = 10; i < ARRAY_COUNT(gActors); i++) {
                if (gActors[i].animFrame == 0) {
                    Object_Kill(&gActors[i].obj, gActors[i].sfxSource);
                }
            }

            Object_Kill(&gActors[2].obj, gActors[2].sfxSource);
            Object_Kill(&gActors[3].obj, gActors[3].sfxSource);
            Object_Kill(&gActors[4].obj, gActors[4].sfxSource);

            player->csState++;

            D_ctx_80177A48[0] = 0.05f;
            if (Rand_ZeroOne() > 0.5f) {
                D_ctx_80177A48[9] = -1.0f;
            } else {
                D_ctx_80177A48[9] = 1.0f;
            }
            break;

        case 1:
            Math_SmoothStepToF(&player->rot.x, 0, 0.1f, 5.0f, 0);
            Math_SmoothStepToF(&player->pos.y, 400.0f, 0.05f, 3.0f, 0);
            temp1 = player->pos.x - boss->obj.pos.x;
            temp2 = player->pos.z - boss->obj.pos.z;
            temp_ft1 = Math_RadToDeg(Math_Atan2F(temp1, temp2));
            temp_ft1 = Math_SmoothStepToAngle(&player->rot.y, temp_ft1, 0.5f, 2.0f, 0.0001f) * 30.0f;
            Math_SmoothStepToAngle(&player->rot.z, -temp_ft1, 0.1f, 5.0f, 0.0001f);

            if (gCsFrameCount < 180) {
                D_ctx_80177A48[8] += D_ctx_80177A48[9];
                Matrix_RotateY(gCalcMatrix, D_ctx_80177A48[8] * M_DTOR, MTXF_NEW);
                sp60.x = 0.0f;
                sp60.y = 0.0f;
                sp60.z = 1400.0f;
                Matrix_MultVec3f(gCalcMatrix, &sp60, &sp54);
                gCsCamEyeX = boss->obj.pos.x + sp54.x;
                gCsCamEyeZ = boss->obj.pos.z + sp54.z;
            }
            temp_ft1 = Math_SmoothStepToAngle(&player->rot.y, 283.0f, 0.1f, 3.0f, 0.0f);
            Math_SmoothStepToF(&player->rot.z, temp_ft1 * 20.0f, 0.1f, 1.0f, 0);

            for (i = 1; i < 4; i++) {
                temp_ft1 = Math_SmoothStepToAngle(&gActors[i].rot_0F4.y, gActors[i].fwork[1], 0.1f, 3.0f, 0.0f);
                Math_SmoothStepToF(&gActors[i].rot_0F4.z, temp_ft1 * 20.0f, 0.1f, 1.0f, 0);
            }

            if (gCsFrameCount >= 180) {
                gFillScreenAlphaTarget = 255;
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
            }
            if (gCsFrameCount == 230) {
                D_ctx_80177A48[0] = 1.0f;
                player->csState++;
                Play_ClearObjectData();
                Audio_StopPlayerNoise(0);
                Audio_KillSfxBySource(player->sfxSource);
                gFillScreenAlpha = 250;
                player->csTimer = 50;
                player->baseSpeed = 0.0f;
                player->rot.x = 0.0f;
                player->rot.y = 0.0f;
                player->rot.z = 0.0f;
            }
            break;

        case 2:
            if (player->csTimer == 0) {
                player->hideShadow = true;
                player->pos.x = 0.0f;
                player->pos.y = 3500.0f;
                player->pos.z = 0.0f;
                player->csState++;
                Audio_StartPlayerNoise(0);
                AUDIO_PLAY_BGM(NA_BGM_COURSE_CLEAR);
                gDrawGround = false;

                for (i = 0; i < 200; i++) {
                    gScenery360[i].obj.status = OBJ_FREE;
                }

                Play_ClearObjectData();
                SectorY_8019EB80();
                D_ctx_80177A48[1] = 10.0f;
                D_ctx_80177A48[2] = 0.5f;
                D_ctx_80177A48[6] = 0.0f;
                D_ctx_80177A48[7] = 25.0f;
                D_ctx_80177A48[8] = 500.0f;
                D_ctx_80177A48[9] = 3600.0f;
                player->arwing.drawFace = true;
            }
            break;

        case 3:
            if ((gCsFrameCount < 720) && gMsgCharIsPrinting) {
                player->arwing.teamFaceXrot = (f32) (gGameFrameCount & 2) * 5.0f;
            }

            gFillScreenAlphaTarget = 0;
            gFillScreenAlphaStep = 4;
            if (gFillScreenAlpha == 0) {
                player->wingPosition = 1;
            }

            if (gCsFrameCount == 343) {
                AUDIO_PLAY_SFX(NA_SE_WING_OPEN, player->sfxSource, 0);
            }
            if (gCsFrameCount == 395) {
                AUDIO_PLAY_SFX(NA_SE_WING_OPEN_END, player->sfxSource, 0);
            }

            D_ctx_80177A48[1] += D_ctx_80177A48[2];
            Matrix_RotateY(gCalcMatrix, D_ctx_80177A48[1] * M_DTOR, MTXF_NEW);
            sp60.y = 0.0f;
            sp60.z = 0.0f;
            sp60.x = D_ctx_80177A48[8];
            Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp60, &sp54);
            Math_SmoothStepToF(&D_ctx_80177A48[9], 3400.0f, 1.0f, 0.1f, 0.0f);

            if (D_ctx_80177A48[1] >= 93.0f) {
                if (gCsFrameCount < 1380) {
                    Math_SmoothStepToF(&D_ctx_80177A48[7], 300.0f, 1.0f, 0.7f, 0.0f);
                } else {
                    D_ctx_80177A48[7] -= 5.0f;
                }
            }

            if (gCsFrameCount >= 640) {
                Math_SmoothStepToF(&D_ctx_80177A48[6], 1.0f, 0.1f, 0.025f, 0.0f);
                Math_SmoothStepToF(&D_ctx_80177A48[8], 1600.0f, 1.0f, D_ctx_80177A48[6], 0.0f);
            } else {
                Math_SmoothStepToF(&D_ctx_80177A48[8], 350.0f, 0.1f, 0.7f, 0.0f);
            }
            gCsCamEyeX = sp54.x;
            gCsCamEyeY = D_ctx_80177A48[9];
            gCsCamEyeZ = 295.0f + sp54.z;
            gCsCamAtX = 0.0f;
            gCsCamAtY = 3500.0f;
            gCsCamAtZ = D_ctx_80177A48[7] + player->pos.z;

            if (gCsFrameCount > 1440) {
                player->baseSpeed += 2.0f;
                player->rot.x += 0.1f;
                Math_SmoothStepToF(&D_ctx_80177A48[2], 0.0f, 1.0f, 0.001f, 0);
                player->unk_190 = 2.0f;
            } else if (D_ctx_80177A48[1] >= 92.0f) {
                Math_SmoothStepToF(&D_ctx_80177A48[2], 0.3f, 1.0f, 0.0018f, 0);
            } else {
                Math_SmoothStepToF(&D_ctx_80177A48[2], 0.01f, 1.0f, 0.0016f, 0);
            }

            if (gCsFrameCount > 1530) {
                gFillScreenAlphaTarget = 255;
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
                gFillScreenAlphaStep = 8;
                if (gFillScreenAlpha == 255) {
                    Audio_FadeOutAll(10);
                    player->state = PLAYERSTATE_NEXT;
                    player->csTimer = 0;
                    gFadeoutType = 4;
                    gLeveLClearStatus[LEVEL_SECTOR_Y] = Play_CheckMedalStatus(150) + 1;
                }
            }
            break;
    }

    switch (gCsFrameCount) {
        case 520:
            if (gHitCount >= 100) {
                gMissionStatus = MISSION_ACCOMPLISHED;
            }
            gLevelClearScreenTimer = 100;
            break;

        case 580:
            if (gHitCount >= 100) {
                Radio_PlayMessage(gMsg_ID_14370, RCID_FOX);
            } else {
                Radio_PlayMessage(gMsg_ID_20010, RCID_FOX);
            }
            break;

        case 725:
            switch (gTeamShields[TEAM_ID_SLIPPY]) {
                case 0:
                    Radio_PlayMessage(gMsg_ID_20345, RCID_ROB64);
                    break;

                case -1:
                    Radio_PlayMessage(gMsg_ID_20333, RCID_ROB64);
                    break;

                default:
                    if (gHitCount >= 100) {
                        Radio_PlayMessage(gMsg_ID_2305, RCID_SLIPPY);
                    } else {
                        func_demo_80048AC0(TEAM_ID_SLIPPY);
                    }
                    break;
            }
            break;

        case 872:
            switch (gTeamShields[TEAM_ID_PEPPY]) {
                case 0:
                    Radio_PlayMessage(gMsg_ID_20344, RCID_ROB64);
                    break;

                case -1:
                    Radio_PlayMessage(gMsg_ID_20332, RCID_ROB64);
                    break;

                default:
                    if (gHitCount >= 100) {
                        Radio_PlayMessage(gMsg_ID_20261, RCID_PEPPY);
                    } else {
                        func_demo_80048AC0(TEAM_ID_PEPPY);
                    }
                    break;
            }
            break;

        case 1018:
            switch (gTeamShields[TEAM_ID_FALCO]) {
                case 0:
                    Radio_PlayMessage(gMsg_ID_20340, RCID_ROB64);
                    break;

                case -1:
                    Radio_PlayMessage(gMsg_ID_20331, RCID_ROB64);
                    break;

                default:
                    if (gHitCount >= 100) {
                        Radio_PlayMessage(gMsg_ID_20262, RCID_FALCO);
                    } else {
                        func_demo_80048AC0(TEAM_ID_FALCO);
                    }
                    break;
            }
            break;

        case 1163:
            gShowLevelClearStatusScreen = true;
            break;

        case 1363:
            gShowLevelClearStatusScreen = false;
            break;

        case 1440:
            AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, player->sfxSource, 0);
            player->unk_194 = 5.0f;
            player->unk_190 = 5.0f;
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 50);
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 50);
            break;

        case 1380:
            if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                gActors[0].state = 2;
            }
            break;

        case 1400:
            if (gTeamShields[TEAM_ID_SLIPPY] > 0) {
                gActors[1].state = 2;
            }
            break;

        case 1420:
            if (gTeamShields[TEAM_ID_FALCO] > 0) {
                gActors[2].state = 2;
            }
            break;
    }

    Matrix_RotateY(gCalcMatrix, (player->yRot_114 + player->rot.y + 180.0f) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -((player->xRot_120 + player->rot.x) * M_DTOR), MTXF_APPLY);
    sp60.x = 0.0f;
    sp60.y = 0.0f;
    sp60.z = player->baseSpeed;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp60, &sp54);
    player->vel.x = sp54.x;
    player->vel.z = sp54.z;
    player->vel.y = sp54.y;
    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;
    player->pos.z += player->vel.z;
    player->trueZpos = player->pos.z;
    player->bankAngle = player->rot.z;
    Math_SmoothStepToF(&player->cam.eye.x, gCsCamEyeX, D_ctx_80177A48[0], 50000.0f, 0.0f);
    Math_SmoothStepToF(&player->cam.eye.y, gCsCamEyeY, D_ctx_80177A48[0], 50000.0f, 0.0f);
    Math_SmoothStepToF(&player->cam.eye.z, gCsCamEyeZ, D_ctx_80177A48[0], 50000.0f, 0.0f);
    Math_SmoothStepToF(&player->cam.at.x, gCsCamAtX, D_ctx_80177A48[0], 50000.0f, 0.0f);
    Math_SmoothStepToF(&player->cam.at.y, gCsCamAtY, D_ctx_80177A48[0], 50000.0f, 0.0f);
    Math_SmoothStepToF(&player->cam.at.z, gCsCamAtZ, D_ctx_80177A48[0], 50000.0f, 0.0f);
    player->bobPhase += 10.0f;
    player->yBob = -SIN_DEG(player->bobPhase) * 0.3f;
    player->rockPhase += 8.0f;
    player->rockAngle = SIN_DEG(player->rockPhase);
}

void SectorY_8019FF00(ActorCutscene* this) {
    Vec3f sp4C;
    Vec3f sp40;
    f32 x;
    f32 z;

    switch (this->state) {
        case 1:
            Math_SmoothStepToF(&this->obj.pos.x, this->vwork[0].x, 0.02f, 2.0f, 0.0001f);
            Math_SmoothStepToF(&this->obj.pos.y, this->vwork[0].y, 0.02f, 2.0f, 0.0001f);
            Math_SmoothStepToF(&this->obj.pos.z, this->vwork[0].z, 0.02f, 2.0f, 0.0001f);
            Math_SmoothStepToF(&this->rot_0F4.z, 0.0f, 0.02f, 0.2f, 0.0001f);
            if ((this->animFrame != 0) && ((((s32) (this->index % 8U) * 10) + 1030) < gCsFrameCount)) {
                this->state = 4;
            }
            break;

        case 2:
            this->state = 3;
            AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, this->sfxSource, 0);
            this->fwork[29] = 5.0f;
            /* fallthrough */
        case 3:
            this->iwork[11] = 2;
            this->fwork[0] += 2.0f;
            this->rot_0F4.x += 0.1f;
            break;

        case 5:
            Math_SmoothStepToF(&this->rot_0F4.x, 0.0f, 0.1f, 5.0f, 0.0f);
            x = this->obj.pos.x - gBosses[this->work_04C].obj.pos.x;
            z = this->obj.pos.z - gBosses[this->work_04C].obj.pos.z;
            Math_SmoothStepToAngle(
                &this->rot_0F4.z,
                Math_SmoothStepToAngle(&this->rot_0F4.y, Math_RadToDeg(Math_Atan2F(x, z)), 0.5f, 2.0f, 0.0001f) * 30.0f,
                0.1f, 5.0f, 0.0001f);
            break;

        case 7:
            this->rot_0F4.y = gPlayer[0].rot.y;
            this->rot_0F4.z = gPlayer[0].rot.z;
            Math_SmoothStepToF(&this->obj.pos.y, 50.0f, 0.1f, 1.0f, 0.0f);
            if (gPlayer[0].rot.y == 0.0f) {
                Math_SmoothStepToF(&this->obj.pos.x, 1300.0f, 1.0f, 2.0f, 0.0f);
            } else {
                if (gCsFrameCount == 540) {
                    this->fwork[29] = 3.8f;
                    AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, this->sfxSource, 0);
                }
                Math_SmoothStepToF(&this->obj.pos.x, 230.0f, 1.0f, 13.0f, 0.0f);
            }
            break;

        case 8:
            Math_SmoothStepToF(&this->obj.pos.y, -100.0f, 0.1f, 1.0f, 0.0f);
            if (gCsFrameCount >= 535) {
                if (gCsFrameCount == 535) {
                    this->fwork[29] = 3.8f;
                    AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, this->sfxSource, 0);
                }
                Math_SmoothStepToF(&this->obj.pos.x, -1000.0f, 1.0f, 20.0f, 0.0f);
                Math_SmoothStepToAngle(&this->rot_0F4.z, 45.0f, 1.0f, 4.0f, 0.0f);
            } else {
                this->rot_0F4.y = gPlayer[0].rot.y;
                this->rot_0F4.z = gPlayer[0].rot.z;
                Math_SmoothStepToF(&this->obj.pos.x, -230.0f, 1.0f, 13.0f, 0.0f);
            }
            break;

        case 9:
            Math_SmoothStepToF(&this->obj.pos.y, -50.0f, 0.1f, 1.0f, 0.0f);
            if (gCsFrameCount >= 525) {
                if (gCsFrameCount == 525) {
                    this->fwork[29] = 3.8f;
                    AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, this->sfxSource, 0);
                }
                Math_SmoothStepToF(&this->obj.pos.x, 1500.0f, 1.0f, 20.0f, 0.0f);
                Math_SmoothStepToAngle(&this->rot_0F4.z, 315.0f, 1.0f, 2.0f, 0.0f);
            } else {
                this->rot_0F4.y = gPlayer[0].rot.y;
                this->rot_0F4.z = gPlayer[0].rot.z;
                Math_SmoothStepToF(&this->obj.pos.x, 150.0f, 1.0f, 13.0f, 0.0f);
            }
            break;
    }

    if (this->state != 6) {
        Matrix_RotateY(gCalcMatrix, (this->rot_0F4.y + 180.0f) * M_DTOR, MTXF_NEW);
        Matrix_RotateX(gCalcMatrix, -(this->rot_0F4.x * M_DTOR), MTXF_APPLY);
        sp4C.x = 0.0f;
        sp4C.y = 0.0f;
        sp4C.z = this->fwork[0];
        Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp4C, &sp40);
        this->vel.x = sp40.x;
        this->vel.y = sp40.y;
        this->vel.z = sp40.z;
        this->obj.rot.x = -this->rot_0F4.x;
        this->obj.rot.y = this->rot_0F4.y + 180.0f;
        this->obj.rot.z = -this->rot_0F4.z;
    }
}

Vec3f D_i6_801A6A74[10] = { { -10100.0f, -300.0f, -600.0f },  { -10300.0f, 1200.0f, -1070.0f },
                            { -10500.0f, 300.0f, 900.0f },    { 9000.0f, 0.0f, 1500.0f },
                            { 5000.0f, -100.0f, -100.0f },    { 1150.0f, -1100.0f, -7500.0f },
                            { -200.0f, -2400.0f, -12650.0f }, { 0.0f, 4000.0f, -600.0f },
                            { -10800.0f, 900.0f, -600.0f },   { -2750.0f, 900.0f, -9150.0f } };

void SectorY_801A0510(ActorCutscene* this, s32 arg1) {
    Actor_Initialize(this);
    this->obj.status = OBJ_ACTIVE;
    this->obj.id = OBJ_ACTOR_CUTSCENE;

    this->obj.pos.x = D_i6_801A6A74[arg1].x;
    this->obj.pos.y = D_i6_801A6A74[arg1].y;
    this->obj.pos.z = D_i6_801A6A74[arg1].z;

    switch (arg1) {
        case 0:
        case 1:
        case 2:
        case 8:
            this->animFrame = ACTOR_CS_SY_ROBOT;
            this->obj.rot.y = 90.0f;
            Object_SetInfo(&this->info, this->obj.id);
            break;

        case 3:
            this->animFrame = ACTOR_CS_SY_SHIP_2;
            this->vel.z = -5.0f;
            this->scale = 1.0f;
            this->obj.rot.y = 180.0f;
            Object_SetInfo(&this->info, this->obj.id);
            break;

        case 4:
            this->animFrame = ACTOR_CS_37;
            this->obj.rot.y = 90.0f;
            Object_SetInfo(&this->info, this->obj.id);
            break;

        case 5:
        case 9:
            this->animFrame = ACTOR_CS_SY_SHIP_1;
            this->obj.rot.y = 180.0f;
            Object_SetInfo(&this->info, this->obj.id);
            break;

        case 6:
            this->animFrame = ACTOR_CS_SY_SHIP_2;
            this->obj.rot.y = 180.0f;
            this->scale = 1.0f;
            Object_SetInfo(&this->info, this->obj.id);
            break;

        case 7:
            this->animFrame = ACTOR_CS_40;
            Object_SetInfo(&this->info, this->obj.id);
            break;

        default:
            break;
    }
}

Vec3f D_i6_801A6AEC[5] = {
    { 100.0f, 50.0f, -200.0f }, { 100.0f, -100.0f, 200.0f }, { 200.0f, -100.0f, 0.0f },
    { 0.0f, 345.0f, 350.0f },   { 90.0f, 87.0f, 93.0f },
};

void SectorY_801A06A4(ActorCutscene* this, s32 teamIdx) {
    if (gTeamShields[1 + teamIdx] > 0) {
        Actor_Initialize(this);
        this->obj.status = OBJ_ACTIVE;
        this->obj.id = OBJ_ACTOR_CUTSCENE;

        this->obj.pos.x = gPlayer[0].pos.x + D_i6_801A6AEC[teamIdx].x;
        this->obj.pos.y = gPlayer[0].pos.y + D_i6_801A6AEC[teamIdx].y;
        this->obj.pos.z = gPlayer[0].pos.z + D_i6_801A6AEC[teamIdx].z;

        this->fwork[0] = gPlayer[0].baseSpeed;
        this->rot_0F4.y = gPlayer[0].rot.y;
        this->rot_0F4.z = gPlayer[0].rot.z;
        this->state = teamIdx + 7;
        this->iwork[11] = 1;
        Object_SetInfo(&this->info, this->obj.id);

        if (CVarGetInteger("gTeamFaces", 1) == 1) {
            // @port: Setup team faces
            this->iwork[14] = teamIdx + 2;
        }

        AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, this->sfxSource, 4);
        AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, this->sfxSource, 0);
    }
}

void SectorY_801A07FC(Actor* actor0, ActorCutscene* actor1) {
    Vec3f src;
    Vec3f dest;

    Actor_Initialize(actor1);
    actor1->obj.status = OBJ_ACTIVE;
    actor1->obj.id = OBJ_ACTOR_CUTSCENE;
    actor0->fwork[6] = 1.8f;
    src.x = -40.0f;
    src.y = 0.0f;
    src.z = 80.0f;
    Matrix_RotateY(gCalcMatrix, actor0->obj.rot.y * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, actor0->obj.rot.x * M_DTOR, MTXF_APPLY);
    Matrix_RotateZ(gCalcMatrix, actor0->obj.rot.z * M_DTOR, MTXF_APPLY);
    Matrix_MultVec3f(gCalcMatrix, &src, &dest);
    actor1->obj.pos.x = actor0->obj.pos.x + dest.x;
    actor1->obj.pos.y = actor0->obj.pos.y + dest.y;
    actor1->obj.pos.z = actor0->obj.pos.z + dest.z;
    Object_SetInfo(&actor1->info, actor1->obj.id);
    Matrix_RotateY(gCalcMatrix, actor0->obj.rot.y * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, actor0->obj.rot.x * M_DTOR, MTXF_APPLY);
    src.x = 0.0f;
    src.y = 0.0f;
    src.z = 160.0f;
    Matrix_MultVec3f(gCalcMatrix, &src, &dest);
    actor1->timer_0BC = 100;
    actor1->vel.x = dest.x;
    actor1->vel.y = dest.y;
    actor1->vel.z = dest.z;
    actor1->obj.rot.x = actor0->obj.rot.x;
    actor1->obj.rot.y = actor0->obj.rot.y;
    actor1->animFrame = ACTOR_CS_42;
    AUDIO_PLAY_SFX(NA_SE_EN_MS_SHOT_S, actor1->sfxSource, 4);
}

void SectorY_801A0A08(ActorCutscene* this, f32 xPos, f32 yPos, f32 zPos, f32 arg4) {
    Actor_Initialize(this);
    this->obj.status = OBJ_ACTIVE;
    this->obj.id = OBJ_ACTOR_CUTSCENE;

    this->fwork[0] = arg4;
    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;
    Object_SetInfo(&this->info, this->obj.id);
    this->timer_0BC = 35;
    this->iwork[0] = 255;
    this->animFrame = ACTOR_CS_43;
    AUDIO_PLAY_SFX(NA_SE_EN_MS_SHOT_S, this->sfxSource, 4);
}

void SectorY_801A0AC0(Player* player) {
    s32 i;
    s32 spB0;
    Vec3f spA4;
    Vec3f sp98;
    f32 sp94;
    f32 sp90;
    f32 sp8C;
    f32 sp88;
    f32 sp84;
    f32 sp80;

    switch (player->csState) {
        case 0:
            gCsFrameCount = 0;
            for (i = 0; i < 5; i++) {
                SectorY_801A0510(&gActors[i + 5], i);
            }
            player->csState = 1;
            player->cam.eye.x = gCsCamEyeX = -2000.0f;
            player->cam.eye.y = gCsCamEyeY = 0.0f;
            player->cam.eye.z = gCsCamEyeZ = -1700.0f;
            player->cam.at.x = gCsCamAtX = gActors[8].obj.pos.x;
            player->cam.at.y = gCsCamAtY = gActors[8].obj.pos.y;
            player->cam.at.z = gCsCamAtZ = gActors[8].obj.pos.z;
            D_ctx_80177A48[0] = 0.0f;
            player->pos.y = 5000.0f;
            player->camRoll = 0.0f;
            player->baseSpeed = 0.0f;
            gActors[5].fwork[2] = gActors[6].fwork[2] = gActors[7].fwork[2] = 0.2f;
            gActors[5].obj.rot.z = 30.0f;
            gActors[6].obj.rot.z = 30.0f;
            gActors[7].obj.rot.z = 320.0f;
            gEnvLightyRot = gLight2yRotTarget = D_ctx_80178524 = gLight1yRot = gLight1yRotTarget = 230.0f;
            gActors[6].fwork[1] = 15.0f;
            /* fallthrough */
        case 1:
            if (gCsFrameCount < 3) {
                gFillScreenAlpha = 255;
            }

            if ((gGameFrameCount & 12) && ((gGameFrameCount % 4) == 0)) {
                spB0 = ((gGameFrameCount & 12) >> 2) + 4;
                for (i = 10; i < ARRAY_COUNT(gActors); i++) {
                    if (gActors[i].obj.status == OBJ_FREE) {
                        SectorY_801A07FC(&gActors[spB0], &gActors[i]);
                        break;
                    }
                }
            }
            if ((gGameFrameCount % 4) == 0) {
                spB0 = ((s32) (gGameFrameCount % 16U) >> 2) + 4;
                if (spB0 == 4) {
                    if (gCsFrameCount < 140) {
                        spB0 = 11;
                    } else {
                        spB0 = 6;
                    }
                }
                sp80 = RAND_FLOAT_CENTERED(3000.0f) + gActors[8].obj.pos.z;

                sp94 = gActors[spB0].obj.pos.x - gActors[8].obj.pos.x;
                sp90 = gActors[spB0].obj.pos.y - gActors[8].obj.pos.y - 200.0f;
                sp8C = gActors[spB0].obj.pos.z - sp80;
                sp84 = Math_RadToDeg(Math_Atan2F(sp94, sp8C));
                sp88 = Math_RadToDeg(-Math_Atan2F(sp90, sqrtf(SQ(sp94) + SQ(sp8C))));
                Matrix_RotateY(gCalcMatrix, M_DTOR * sp84, MTXF_NEW);
                Matrix_RotateX(gCalcMatrix, M_DTOR * sp88, MTXF_APPLY);
                spA4.x = 0.0f;
                spA4.y = 0.0f;
                spA4.z = 100.0f;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &spA4, &sp98);

                for (i = 0; i < 10; i++) {
                    if (gPlayerShots[i].obj.status == SHOT_FREE) {
                        Actor_SetupPlayerShot(PLAYERSHOT_TWIN_LASER, &gPlayerShots[i], CS_SHOT_ID, gActors[8].obj.pos.x,
                                              gActors[8].obj.pos.y - 200.0f, sp80, sp98.x, sp98.y, sp98.z, sp88, sp84,
                                              0.0f);
                        gPlayerShots[i].timer = 200;
                        break;
                    }
                }
            }

            if (gCsFrameCount >= 100) {
                gCsCamAtX = gActors[5].obj.pos.x;
                gCsCamAtY = 0.0f;
                gCsCamAtZ = gActors[5].obj.pos.z;
                Math_SmoothStepToF(D_ctx_80177A48, 1.0f, 1.0f, 0.005f, 0.0f);
                gActors[5].vel.x = gActors[6].vel.x = gActors[7].vel.x = 80.0f;
            }
            if (gCsFrameCount >= 189) {
                gActors[6].vel.z = SIN_DEG((gCsFrameCount * 2) - 378) * gActors[6].fwork[1];
                gActors[6].vel.y = COS_DEG((gCsFrameCount * 2) - 378) * gActors[6].fwork[1];
                gActors[7].vel.z = SIN_DEG((gCsFrameCount * 2) - 378) * -gActors[6].fwork[1];
                gActors[7].vel.y = COS_DEG((gCsFrameCount * 2) - 378) * -gActors[6].fwork[1];
                Math_SmoothStepToF(&gActors[6].fwork[1], 30.0f, 1.0f, 1.0f, 0.0f);
                Math_SmoothStepToAngle(&gActors[6].obj.rot.z, 180.0f, 1.0f, 0.5f, 1.0f);
                Math_SmoothStepToAngle(&gActors[7].obj.rot.z, 181.0f, 1.0f, 0.5f, 1.0f);
            } else {
                if (((gGameFrameCount % 16) == 0) && (gCsFrameCount >= 105) && (gCsFrameCount <= 140)) {

                    for (i = 10; i < ARRAY_COUNT(gActors); i++) {
                        if (gActors[i].obj.status == OBJ_FREE) {
                            SectorY_801A07FC(&gActors[11], &gActors[i]);
                            break;
                        }
                    }
                }
                if (gCsFrameCount >= 140) {
                    Math_SmoothStepToAngle(&gActors[5].obj.rot.z, 0.0f, 1.0f, 1.0f, 0.0f);
                    Math_SmoothStepToAngle(&gActors[6].obj.rot.z, 0.0f, 1.0f, 1.0f, 0.0f);
                    Math_SmoothStepToAngle(&gActors[7].obj.rot.z, 0.0f, 1.0f, 1.0f, 0.0f);
                    Math_SmoothStepToF(&gActors[5].obj.pos.y, 0.0f, 1.0f, 20.0f, 0.0f);
                    Math_SmoothStepToF(&gActors[6].obj.pos.y, -300.0f, 1.0f, 20.0f, 0.0f);
                    Math_SmoothStepToF(&gActors[7].obj.pos.y, 200.0f, 1.0f, 20.0f, 0.0f);
                    Math_SmoothStepToF(&gActors[5].obj.pos.z, -900.0f, 1.0f, 20.0f, 0.0f);
                    Math_SmoothStepToF(&gActors[6].obj.pos.z, -1570.0f, 1.0f, 20.0f, 0.0f);
                    Math_SmoothStepToF(&gActors[7].obj.pos.z, -400.0f, 1.0f, 20.0f, 0.0f);
                } else {
                    Math_SmoothStepToAngle(&gActors[5].obj.rot.z, 30.0f, 1.0f, 1.0f, 0.0f);
                    Math_SmoothStepToAngle(&gActors[6].obj.rot.z, 30.0f, 1.0f, 1.0f, 0.0f);
                    Math_SmoothStepToAngle(&gActors[7].obj.rot.z, 320.0f, 1.0f, 1.0f, 0.0f);
                    Math_SmoothStepToF(&gActors[5].obj.pos.y, -1000.0f, 1.0f, 20.0f, 0.0f);
                    Math_SmoothStepToF(&gActors[6].obj.pos.y, 500.0f, 1.0f, 20.0f, 0.0f);
                    Math_SmoothStepToF(&gActors[7].obj.pos.y, -400.0f, 1.0f, 20.0f, 0.0f);
                    Math_SmoothStepToF(&gActors[5].obj.pos.z, -1200.0f, 1.0f, 20.0f, 0.0f);
                    Math_SmoothStepToF(&gActors[6].obj.pos.z, -2070.0f, 1.0f, 20.0f, 0.0f);
                    Math_SmoothStepToF(&gActors[7].obj.pos.z, -100.0f, 1.0f, 20.0f, 0.0f);
                }
            }

            if (((gGameFrameCount % 2) == 0) && (gCsFrameCount >= 110)) {
                Matrix_RotateY(gCalcMatrix, gActors[8].obj.rot.y * M_DTOR, MTXF_NEW);
                Matrix_RotateX(gCalcMatrix, gActors[8].obj.rot.x * M_DTOR, MTXF_APPLY);
                Matrix_RotateZ(gCalcMatrix, gActors[8].obj.rot.z * M_DTOR, MTXF_APPLY);
                spA4.x = RAND_FLOAT_CENTERED(100.0f) + 1500.0f;
                spA4.y = RAND_FLOAT_CENTERED(500.0f) + -500.0f;
                spA4.z = RAND_FLOAT_CENTERED(5000.0f) + 170.0f;
                Matrix_MultVec3f(gCalcMatrix, &spA4, &sp98);
                Effect_Effect390_Spawn(gActors[8].obj.pos.x + sp98.x, gActors[8].obj.pos.y + sp98.y,
                                       gActors[8].obj.pos.z + sp98.z, gActors[8].vel.x, gActors[8].vel.y,
                                       gActors[8].vel.z, 0.8f, 5);
                func_effect_8007D2C8(gActors[8].obj.pos.x - 2000.0f + RAND_FLOAT_CENTERED(500.0f),
                                     gActors[8].obj.pos.y - 500.0f + RAND_FLOAT_CENTERED(1000.0f),
                                     gActors[8].obj.pos.z + RAND_FLOAT_CENTERED(3000.0f), 8);
            }
            if ((gGameFrameCount & 20) != 0) {
                for (i = 12; i < ARRAY_COUNT(gActors); i++) {
                    if (gActors[i].obj.status == OBJ_FREE) {
                        SectorY_801A0A08(
                            &gActors[i], gActors[8].obj.pos.x + 1000.0f,
                            (gActors[8].obj.pos.y + 2000.0f + ((s32) ((gGameFrameCount % 4U) - 2) * 2000.0f)) +
                                RAND_FLOAT_CENTERED(4000.0f),
                            (gActors[8].obj.pos.z + 4000.0f + ((s32) ((gGameFrameCount % 4U) - 2) * 3000.0f)) +
                                RAND_FLOAT_CENTERED(7000.0f),
                            RAND_FLOAT(10.0f));
                        break;
                    }
                }
            }
            if ((gCsFrameCount >= 240) && (gCsFrameCount < 260)) {
                gActors[9].scale += 32.0f;
                if (gCsFrameCount >= 245) {
                    gActors[9].fwork[4] += 8;
                    gFillScreenRed = 255;
                    gFillScreenGreen = 255;
                    gFillScreenBlue = 255;
                    gFillScreenAlphaTarget = 255;
                } else {
                    gActors[9].fwork[4] = 0.5f;
                }
            }

            switch (gCsFrameCount) {
                case 105:
                    sp94 = -7600.0f - gActors[8].obj.pos.x;
                    sp90 = 900.0f - gActors[8].obj.pos.y;
                    sp8C = -1000.0f - gActors[8].obj.pos.z;
                    sp84 = Math_RadToDeg(Math_Atan2F(sp94, sp8C));
                    sp88 = Math_RadToDeg(-Math_Atan2F(sp90, sqrtf(SQ(sp94) + SQ(sp8C))));
                    Matrix_RotateY(gCalcMatrix, M_DTOR * sp84, MTXF_NEW);
                    Matrix_RotateX(gCalcMatrix, M_DTOR * sp88, MTXF_APPLY);
                    spA4.x = 0.0f;
                    spA4.y = 0.0f;
                    spA4.z = 100.0f;
                    Matrix_MultVec3fNoTranslate(gCalcMatrix, &spA4, &sp98);

                    for (i = 0; i < 11; i++) {
                        if (gPlayerShots[i].obj.status == SHOT_FREE) {
                            Actor_SetupPlayerShot(PLAYERSHOT_TWIN_LASER, &gPlayerShots[i], CS_SHOT_ID,
                                                  gActors[8].obj.pos.x, gActors[8].obj.pos.y, gActors[8].obj.pos.z,
                                                  sp98.x, sp98.y, sp98.z, sp88, sp84, 0.0f);
                            gPlayerShots[i].timer = 174;
                            break;
                        }
                    }

                    SectorY_801A0510(&gActors[11], 8);

                    gActors[11].vel.x = 80.0f;
                    gActors[11].vel.z = -10.0f;
                    gActors[11].fwork[2] = 0.2f;
                    gActors[11].iwork[5] = 0;
                    gActors[11].obj.rot.x = 0.0f;
                    gActors[11].obj.rot.z = 0.0f;
                    break;

                case 145:
                    Effect386_Spawn1(gActors[11].obj.pos.x, gActors[11].obj.pos.y, gActors[11].obj.pos.z,
                                     gActors[11].vel.x, gActors[11].vel.y, gActors[11].vel.z, 8, 10);
                    Effect_Effect384_Spawn(gActors[11].obj.pos.x, gActors[11].obj.pos.y, gActors[11].obj.pos.z, 8, 5);
                    AUDIO_PLAY_SFX(NA_SE_EN_MS_EXPLOSION_S, gActors[11].sfxSource, 4);
                    break;

                case 188:
                    gActors[5].fwork[0] = gActors[6].fwork[0] = gActors[7].fwork[0] = 3.8f;
                    AUDIO_PLAY_SFX(NA_SE_EN_MS_DASH, gActors[5].sfxSource, 4);
                    AUDIO_PLAY_SFX(NA_SE_EN_MS_DASH, gActors[6].sfxSource, 4);
                    AUDIO_PLAY_SFX(NA_SE_EN_MS_DASH, gActors[7].sfxSource, 4);
                    break;

                case 150:
                    Object_Kill(&gActors[11].obj, gActors[11].sfxSource);
                    for (i = 10; i < 24; i++) {
                        SectorY_ActorDebris_Spawn(gActors[11].obj.pos.x, gActors[11].obj.pos.y, gActors[11].obj.pos.z,
                                                  RAND_FLOAT_CENTERED(50.0f), RAND_FLOAT_CENTERED(50.0f),
                                                  RAND_FLOAT_CENTERED(50.0f), i);
                    }
                    break;

                case 155:
                    gActors[7].fwork[0] = 3.8f;
                    AUDIO_PLAY_SFX(NA_SE_EN_MS_DASH, gActors[7].sfxSource, 4);
                    break;

                case 163:
                    gActors[6].fwork[0] = 3.8f;
                    AUDIO_PLAY_SFX(NA_SE_EN_MS_DASH, gActors[6].sfxSource, 4);
                    break;

                case 240:
                    gActors[9].iwork[0] = 255;
                    gActors[9].iwork[1] = 255;
                    gActors[9].iwork[2] = 255;
                    gActors[9].iwork[3] = 240;
                    gActors[9].iwork[4] = 0;
                    gActors[9].iwork[5] = 0;
                    gActors[9].iwork[6] = 255;
                    gActors[9].iwork[7] = 100;
                    AUDIO_PLAY_SFX(NA_SE_EN_STAR_EXPLOSION, gActors[5].sfxSource, 4);
                    D_ctx_801779A8[gMainController] = 100.0f;
                    break;

                case 260:
                    gActors[9].fwork[4] = gActors[9].scale = 1000;
                    gActors[9].obj.pos.x = -8300.0f;
                    gFillScreenRed = 255;
                    gFillScreenGreen = 255;
                    gFillScreenBlue = 255;
                    gFillScreenAlpha = 255;
                    gFillScreenAlphaTarget = 0;
                    Object_Kill(&gActors[8].obj, gActors[8].sfxSource);
                    player->csState++;
                    player->cam.eye.x = gCsCamEyeX = 0.0f;
                    player->cam.eye.y = gCsCamEyeY = 0.0f;
                    player->cam.eye.z = gCsCamEyeZ = 0.0f;
                    player->cam.at.x = gCsCamAtX = -5600.0f;
                    player->cam.at.y = gCsCamAtY = 0.0f;
                    player->cam.at.z = gCsCamAtZ = 0.0f;
                    gActors[5].obj.pos.x = -4800.0f;
                    gActors[5].obj.pos.y = 0.0f;
                    gActors[5].obj.pos.z = 0.0f;
                    gActors[6].vel.y = gActors[6].vel.z = gActors[7].vel.y = gActors[7].vel.z = gActors[5].vel.x =
                        gActors[6].vel.x = gActors[7].vel.x = 0.0f;
                    gActors[5].obj.rot.x = 359.0f;
                    gActors[6].obj.pos.x = -6000.0f;
                    gActors[6].obj.pos.y = 1450.0f;
                    gActors[6].obj.pos.z = -650.0f;
                    gActors[6].obj.rot.x = 359.0f;
                    gActors[6].obj.rot.z = 181.0f;
                    gActors[7].obj.pos.x = -6800.0f;
                    gActors[7].obj.pos.y = -1280.0f;
                    gActors[7].obj.pos.z = 100.0f;
                    gActors[7].obj.rot.x = 359.0f;
                    gActors[7].obj.rot.z = 60.0f;
                    D_ctx_80177A48[0] = 0.0f;
                    D_ctx_80177A48[1] = D_ctx_80177A48[2] = D_ctx_80177A48[3] = D_ctx_80177A48[4] = 0.0f;
                    break;
            }
            break;

        case 2:
            if (gCsFrameCount < 300) {
                gFillScreenRed = 255;
                gFillScreenGreen = 255;
                gFillScreenBlue = 255;
                gFillScreenAlpha = 255;
                gEnvLightyRot = -58.0f;
            }
            if (gCsFrameCount >= 300) {
                Math_SmoothStepToF(&D_ctx_80177A48[1], 120.0f, 0.1f, D_ctx_80177A48[2], 0);
                Math_SmoothStepToF(&D_ctx_80177A48[2], 2.0f, 0.1f, 0.05f, 0);
                Math_SmoothStepToF(&D_ctx_80177A48[3], 100.0f, 1.0f, 1.0f, 0);
                Math_SmoothStepToF(&D_ctx_80177A48[4], 400.0f, 1.0f, 10.0f, 0);
                gCsCamAtX = player->cam.at.x = gActors[5].obj.pos.x;
                Matrix_RotateY(gCalcMatrix, D_ctx_80177A48[1] * M_DTOR, MTXF_NEW);
                spA4.x = D_ctx_80177A48[4] + 400.0f;
                spA4.y = 0.0f;
                spA4.z = 0.0f;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &spA4, &sp98);
                player->cam.eye.x = gCsCamEyeX = sp98.x;
                player->cam.eye.y = gCsCamEyeY = D_ctx_80177A48[3] + sp98.y;
                player->cam.eye.z = gCsCamEyeZ = sp98.z;
            }
            if (gCsFrameCount == 280) {
                gActors[5].iwork[4] = gActors[6].iwork[4] = gActors[7].iwork[4] = 1;
                gActors[5].fwork[5] = gActors[6].fwork[5] = gActors[7].fwork[5] = 80.0f;
                gActors[6].fwork[1] = 60.0f;
                AUDIO_PLAY_SFX(NA_SE_EN_ENGINE_01, gActors[5].sfxSource, 4);
            }
            if ((gCsFrameCount >= 285) && (gActors[9].iwork[3] != 0)) {
                gActors[9].iwork[3] -= 5;
            }
            if (gCsFrameCount >= 280) {
                gActors[6].vel.z = COS_DEG((gCsFrameCount * 2) - 540) * gActors[6].fwork[1];
                gActors[6].vel.y = SIN_DEG((gCsFrameCount * 2) - 540) * -gActors[6].fwork[1];
                gActors[7].vel.z = COS_DEG((gCsFrameCount * 2) - 540) * -gActors[6].fwork[1];
                gActors[7].vel.y = SIN_DEG((gCsFrameCount * 2) - 540) * gActors[6].fwork[1];
                Math_SmoothStepToF(&gActors[6].fwork[1], 0.0f, 1.0f, 1.0f, 1.0f);
                Math_SmoothStepToAngle(&gActors[6].obj.rot.z, 0.0f, 1.0f, 4.0f, 1.0f);
                Math_SmoothStepToAngle(&gActors[7].obj.rot.z, 0.0f, 1.0f, 1.5f, 1.0f);
                Math_SmoothStepToF(&gActors[5].obj.pos.x, 0.0f, 1.0f, gActors[5].fwork[5], 1.0f);
                Math_SmoothStepToF(&gActors[6].obj.pos.x, -320.0f, 1.0f, gActors[6].fwork[5], 1.0f);
                Math_SmoothStepToF(&gActors[7].obj.pos.x, -660.0f, 1.0f, gActors[7].fwork[5], 1.0f);
            }
            if ((gCsFrameCount >= 320) && (gCsFrameCount <= 340)) {
                gActors[5].fwork[5] -= 1.0f;
                gActors[5].iwork[4] = 5;
                gActors[5].iwork[5] = 19;
                if (gActors[5].obj.rot.x >= 320.0f) {
                    gActors[5].obj.rot.x -= 2.0f;
                }
            }
            if ((gCsFrameCount >= 330) && (gCsFrameCount <= 350)) {
                gActors[6].fwork[5] -= 1.0f;
                gActors[6].iwork[4] = 5;
                gActors[6].iwork[5] = 19;
                if (gActors[6].obj.rot.x >= 320.0f) {
                    gActors[6].obj.rot.x -= 2.0f;
                }
            }
            if ((gActors[7].iwork[4] != 3) && (gCsFrameCount >= 340)) {
                gActors[7].fwork[5] -= 1.0f;
                gActors[7].iwork[4] = 5;
                gActors[7].iwork[5] = 19;
                if (gActors[7].obj.rot.x >= 320.0f) {
                    gActors[7].obj.rot.x -= 1.0f;
                }
            }
            if ((gCsFrameCount >= 340) && (gCsFrameCount < 360)) {
                gActors[5].fwork[5] -= 2.8f;
                gActors[5].iwork[4] = 1;
                gActors[5].iwork[5] = 29;
                if (gActors[5].obj.rot.x <= 360.0f) {
                    gActors[5].obj.rot.x += 2.0f;
                }
            }
            if ((gCsFrameCount >= 350) && (gCsFrameCount < 370)) {
                gActors[6].fwork[5] -= 2.8f;
                gActors[6].iwork[4] = 1;
                gActors[6].iwork[5] = 29;
                if (gActors[6].obj.rot.x <= 360.0f) {
                    gActors[6].obj.rot.x += 2.0f;
                }
                if (gActors[6].obj.rot.y >= 60.0f) {
                    gActors[6].obj.rot.y -= 2.0f;
                }
            }
            if ((gCsFrameCount >= 360) && (gCsFrameCount < 370)) {
                gActors[7].fwork[5] -= 2.8f;
                gActors[7].iwork[4] = 3;
                gActors[7].iwork[5] = 29;
                if (gActors[7].obj.rot.x <= 360.0f) {
                    gActors[7].obj.rot.x += 2.0f;
                }
                if (gActors[7].obj.rot.y <= 120.0f) {
                    gActors[7].obj.rot.y += 2.0f;
                }
            }
            if (gCsFrameCount >= 350) {
                if (gActors[5].vel.z > -0.2f) {
                    gActors[5].vel.z -= 0.02f;
                }
                if (gActors[5].vel.x > -2.0f) {
                    gActors[5].vel.x -= 0.2f;
                }
                gActors[9].fwork[4] = 0.0f;
                gActors[9].iwork[0] = gActors[9].iwork[1] = gActors[9].iwork[2] = gActors[9].iwork[3] = 255;
                gActors[9].iwork[4] = 255;
                gActors[9].iwork[5] = 48;
                gActors[9].iwork[6] = 0;
                gActors[9].iwork[7] = 255;
                gActors[9].iwork[8] = 0;
                gActors[9].scale = gActors[9].fwork[4];
            }
            if (gCsFrameCount >= 360) {
                gActors[5].fwork[5] = 0.0f;
                if (gActors[6].vel.z > -2.0f) {
                    gActors[6].vel.z -= 0.2f;
                }
                if (gActors[6].vel.x > -2.0f) {
                    gActors[6].vel.x -= 0.15f;
                }
                if (gActors[7].vel.x > -1.5f) {
                    gActors[7].vel.x -= 0.2f;
                }
            }

            switch (gCsFrameCount) {
                case 340:
                    gActors[5].fwork[0] = 1.8f;
                    AUDIO_PLAY_SFX(NA_SE_EN_MS_DASH, gActors[5].sfxSource, 4);
                    break;

                case 350:
                    gActors[6].fwork[0] = 1.8f;
                    AUDIO_PLAY_SFX(NA_SE_EN_MS_DASH, gActors[6].sfxSource, 4);
                    break;

                case 370:
                    gActors[6].fwork[5] = 0.0f;
                    gActors[7].fwork[5] = 0.0f;
                    break;

                case 360:
                    AUDIO_PLAY_BGM(NA_BGM_START_DEMO_S);
                    break;

                case 389:
                    gActors[5].iwork[4] = 1;
                    gActors[6].vel.x = -2.0f;
                    gActors[6].vel.z = -2.0f;
                    gActors[7].iwork[4] = 4;
                    gActors[7].iwork[5] = 0;
                    gActors[7].vel.x = -1.5f;
                    player->csState++;
                    break;
            }
            break;

        case 3:
            if (gCsFrameCount < 520) {
                Math_SmoothStepToAngle(&D_ctx_80177A48[1], 120.0f, 0.1f, D_ctx_80177A48[2], 0);
                Math_SmoothStepToF(&D_ctx_80177A48[2], 2.0f, 0.1f, 0.05f, 0);
                Math_SmoothStepToF(&D_ctx_80177A48[3], 100.0f, 1.0f, 1.0f, 0);
                Math_SmoothStepToF(&D_ctx_80177A48[4], 400.0f, 1.0f, 10.0f, 0);

                if (gCsFrameCount <= 410) {
                    gCsCamAtX = player->cam.at.x = gActors[5].obj.pos.x;
                }
                Matrix_RotateY(gCalcMatrix, D_ctx_80177A48[1] * M_DTOR, MTXF_NEW);
                spA4.x = D_ctx_80177A48[4] + 400.0f;
                spA4.y = 0.0f;
                spA4.z = 0.0f;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &spA4, &sp98);
                player->cam.eye.x = gCsCamEyeX = sp98.x;
                player->cam.eye.y = gCsCamEyeY = D_ctx_80177A48[3] + sp98.y;
                player->cam.eye.z = gCsCamEyeZ = sp98.z;
            }

            if (gCsFrameCount >= 390) {
                if (gActors[6].iwork[4] != 0) {
                    gActors[6].fwork[0] = 1.8f;
                    AUDIO_PLAY_SFX(NA_SE_EN_MS_DASH, gActors[6].sfxSource, 4);
                    gActors[6].obj.rot.x = (gActors[6].obj.rot.x - 2.0f);
                    if (gActors[6].obj.rot.x <= 320.0f) {
                        gActors[6].iwork[4] = 0;
                        if (gActors[6].obj.rot.y <= 230.0f) {
                            gActors[6].obj.rot.y = (gActors[6].obj.rot.y + 6.0f);
                        }
                    }
                } else {
                    if (gActors[6].obj.rot.x >= 300.0f) {
                        gActors[6].obj.rot.x = (gActors[6].obj.rot.x + 2.0f);
                    }
                    if (gActors[6].obj.rot.x >= 360.0f) {
                        gActors[6].obj.rot.x = 0.0f;
                    }
                    if (gActors[6].obj.rot.y <= 230.0f) {
                        gActors[6].obj.rot.y = (gActors[6].obj.rot.y + 6.0f);
                        if (gActors[6].obj.rot.y > 230.0f) {
                            gActors[6].fwork[0] = 2.8f;
                            AUDIO_PLAY_SFX(NA_SE_EN_MS_DASH, gActors[6].sfxSource, 4);
                        }
                    }
                }
                Math_SmoothStepToF(&gActors[6].vel.x, -40.0f, 1.0f, 1.0f, 1.0f);
                Math_SmoothStepToF(&gActors[6].vel.z, -60.0f, 1.0f, 1.0f, 1.0f);
            }

            if (gCsFrameCount >= 400) {
                if (gActors[7].iwork[5] < 35) {
                    if (gActors[7].iwork[4] == 4) {
                        gActors[7].iwork[5]++;
                    }
                }
                if ((gActors[7].iwork[5] == 35) && (gCsFrameCount == 445)) {
                    gActors[7].iwork[4] = 2;
                    gActors[7].iwork[5] = 0;
                }
            }

            if ((gCsFrameCount >= 380) && (gCsFrameCount <= 460)) {
                Math_SmoothStepToAngle(&gActors[5].obj.rot.y, 30.0f, 1.0f, 0.75f, 0.0f);
            }

            if ((gCsFrameCount > 440) && (player->rot.y != 0.0f)) {
                Math_SmoothStepToF(&gPlayer[0].pos.y, 0.0f, 0.1f, 5.0f, 0.0f);
                Math_SmoothStepToAngle(&player->rot.z,
                                       Math_SmoothStepToAngle(&player->rot.y, 0.0f, 1.0f, 0.7f, 0.0f) * 30.0f, 0.1f,
                                       5.0f, 0);
                Math_SmoothStepToF(&gPlayer[0].pos.x, 0.0f, 1.0f, 13.0f, 0.0f);
            }

            if (player->rot.y == 0.0f) {
                Math_SmoothStepToAngle(&player->rot.z, 0.0f, 1.0f, 0.5f, 0);
                Math_SmoothStepToF(&gPlayer[0].pos.x, 0.0f, 1.0f, 2.0f, 0.0f);
            }

            if (gCsFrameCount >= 445) {
                Math_SmoothStepToF(&gActors[7].vel.z, -40.0f, 1.0f, 1.0f, 1.0f);
                Math_SmoothStepToF(&gActors[7].vel.x, -60.0f, 1.0f, 1.0f, 1.0f);
                if (gActors[7].obj.rot.y <= 230.0f) {
                    gActors[7].obj.rot.y = (gActors[7].obj.rot.y + 6.0f);
                    if (gActors[7].obj.rot.y > 230.0f) {
                        gActors[7].fwork[0] = 2.8f;
                        AUDIO_PLAY_SFX(NA_SE_EN_MS_DASH, gActors[7].sfxSource, 4);
                    }
                }
            }

            if (gCsFrameCount >= 470) {
                Math_SmoothStepToAngle(&gEnvLightyRot, 58.0f, 1.0f, 2.0f, 0.0f);
                gActors[5].obj.rot.y += 1.2f;
                if (gActors[5].iwork[4] != 6) {
                    gActors[5].obj.rot.z -= 0.25f;
                }
                if ((gActors[5].iwork[4] == 6) && (gActors[5].iwork[5] < 80)) {
                    gActors[5].iwork[5]++;
                }

                if ((gCsFrameCount >= 520) && (gCsFrameCount < 550)) {
                    gActors[5].fwork[2] = 0.2f;
                    Math_SmoothStepToF(&gActors[5].vel.z, -10.0f, 1.0f, 1.0f, 1.0f);
                }
                if (gCsFrameCount >= 520) {
                    gCsCamAtX = player->pos.x;
                    gCsCamAtY = player->pos.y;
                    gCsCamAtZ = player->pos.z;
                    gCsCamEyeX = 50.0f;
                    gCsCamEyeY = 10.0f;
                    Math_SmoothStepToF(D_ctx_80177A48, 1.0f, 0.1f, 0.005f, 0.0f);
                }
                if ((gActors[5].iwork[4] == 6) && (gCsFrameCount >= 550) && (gActors[5].obj.rot.y <= 174.0f)) {
                    Math_SmoothStepToAngle(&gActors[5].obj.rot.z, 0.0f, 1.0f, 1.5f, 1.0f);
                    gActors[5].obj.rot.y += 7.0f;
                    if (gActors[5].obj.rot.y > 174.0f) {
                        gActors[5].fwork[0] = 2.8f;
                        AUDIO_PLAY_SFX(NA_SE_EN_MS_DASH, gActors[5].sfxSource, 4);
                    }
                }

                if ((gActors[5].iwork[4] == 6) && (gCsFrameCount == 550)) {
                    Object_Kill(&gActors[10].obj, gActors[10].sfxSource);
                    gLoadLevelObjects = 1;
                }
                if (gCsFrameCount >= 530) {
                    Math_SmoothStepToF(&gActors[5].vel.z, -40.0f, 1.0f, 1.0f, 1.0f);
                    Math_SmoothStepToF(&gActors[5].vel.x, -60.0f, 1.0f, 1.0f, 1.0f);
                    gActors[6].vel.x = gActors[7].vel.x = gActors[6].vel.z = gActors[7].vel.z = 0.0f;
                    gActors[5].iwork[5]++;
                    gActors[5].fwork[2] = 0.15f;
                    Math_SmoothStepToF(&gActors[7].obj.pos.z, -8000.0f, 1.0f, 60.0f, 1.0f);
                    Math_SmoothStepToF(&gActors[7].obj.pos.x, 3000.0f, 1.0f, 60.0f, 1.0f);
                    Math_SmoothStepToF(&gActors[6].obj.pos.z, -8000.0f, 1.0f, 60.0f, 1.0f);
                    Math_SmoothStepToF(&gActors[6].obj.pos.x, -3000.0f, 1.0f, 60.0f, 1.0f);
                }
            }

            switch (gCsFrameCount) {
                case 390:
                    SectorY_801A07FC(&gActors[5], &gActors[10]);
                    gActors[5].vel.x -= 0.25f;
                    gActors[5].vel.z -= 2.0f;
                    break;

                case 420:
                    player->pos.x = 4800.0f;
                    player->pos.y = 300.0f;
                    player->pos.z = 4000.0f;
                    player->baseSpeed = 40.0f;
                    player->rot.y = 80.0f;
                    player->rot.z = 240.0f;

                    for (i = 0; i < 3; i++) {
                        SectorY_801A06A4(&gActors[i], i);
                    }
                    break;

                case 425:
                    gActors[5].vel.x -= 0.5f;
                    gActors[5].vel.z -= 1.5f;
                    Object_Kill(&gActors[10].obj, gActors[10].sfxSource);
                    SectorY_801A07FC(&gActors[5], &gActors[10]);
                    break;

                case 435:
                    Object_Kill(&gActors[10].obj, gActors[10].sfxSource);
                    SectorY_801A07FC(&gActors[5], &gActors[10]);
                    gActors[7].fwork[0] = 1.8f;
                    AUDIO_PLAY_SFX(NA_SE_EN_MS_DASH, gActors[7].sfxSource, 4);
                    break;

                case 458:
                    gActors[7].iwork[4] = 0;
                    break;

                case 450:
                    gActors[5].vel.x -= 0.5f;
                    gActors[5].vel.z -= 1.5f;
                    Object_Kill(&gActors[10].obj, gActors[10].sfxSource);
                    SectorY_801A07FC(&gActors[5], &gActors[10]);
                    gActors[10].timer_0BC = 180;
                    break;

                case 470:
                    gActors[5].iwork[4] = 6;
                    gActors[5].iwork[5] = 0;
                    gActors[5].fwork[0] = 1.8f;
                    break;

                case 530:
                    gActors[5].vel.x = -10.0f;
                    gActors[5].vel.z = -10.0f;
                    break;

                case 545:
                    player->unk_194 = 10.0f;
                    player->unk_190 = 10.0f;
                    AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, player->sfxSource, 0);
                    gControllerRumbleFlags[gMainController] = 1;
                    gControllerRumbleTimers[gMainController] = 5;
                    break;

                case 500:
                case 510:
                    gActors[5].fwork[0] = 1.8f;
                    break;

                case 560:
                    D_ctx_80177A48[0] = 0.1f;
                    gActors[5].vel.x = gActors[5].vel.z = 0.0f;
                    gActors[5].obj.rot.y = gActors[6].obj.rot.y = 180.0f;
                    gActors[7].obj.rot.y = 140.0f;
                    gActors[5].fwork[0] = 2.8f;
                    AUDIO_PLAY_SFX(NA_SE_EN_MS_DASH, gActors[5].sfxSource, 4);
                    player->csState++;
                    break;
            }
            break;

        case 4:
            Math_SmoothStepToAngle(&player->rot.z, 0.0f, 1.0f, 0.5f, 0);
            Math_SmoothStepToF(&gPlayer[0].pos.x, 0.0f, 1.0f, 1.0f, 0.0f);
            Math_SmoothStepToF(D_ctx_80177A48, 1.0f, 0.1f, 0.05f, 0.0f);

            if (gCsFrameCount < 595) {
                Math_SmoothStepToF(&gActors[5].obj.pos.z, -12000.0f, 1.0f, 100.0f, 1.0f);
                Math_SmoothStepToF(&gActors[5].obj.pos.x, 0.0f, 1.0f, 40.0f, 1.0f);
                Math_SmoothStepToF(&gActors[5].obj.pos.y, 13000.0f, 1.0f, 30.0f, 1.0f);
                Math_SmoothStepToAngle(&player->rot.y, 0.0f, 1.0f, 0.5f, 0.0f);
                Math_SmoothStepToF(&player->pos.x, 0.0f, 1.0f, 1.0f, 0.0f);
            } else {
                Math_SmoothStepToF(&gActors[5].obj.pos.z, -12000.0f, 1.0f, 100.0f, 1.0f);
                Math_SmoothStepToF(&gActors[5].obj.pos.x, 300.0f, 1.0f, 50.0f, 1.0f);
                Math_SmoothStepToF(&gActors[5].obj.pos.y, 13000.0f, 1.0f, 50.0f, 1.0f);
            }
            Math_SmoothStepToF(&gActors[6].obj.pos.z, -12000.0f, 1.0f, 40.0f, 1.0f);
            Math_SmoothStepToF(&gActors[6].obj.pos.x, -13000.0f, 1.0f, 80.0f, 1.0f);

            gCsCamAtX = player->pos.x;
            gCsCamAtZ = player->pos.z;

            if (gCsFrameCount < 590) {
                gCsCamAtY = player->pos.y;
            }

            if ((gCsFrameCount >= 590) && (gCsFrameCount < 605)) {
                Math_SmoothStepToF(&gCsCamEyeZ, gActors[0].obj.pos.z, 1.0f, 20.0f, 0.0f);
                Math_SmoothStepToF(&gCsCamEyeX, 0.0f, 1.0f, 4.0f, 0.0f);
                Math_SmoothStepToF(&gCsCamEyeY, (player->pos.y * player->unk_148) + 50.0f, 1.0f, 2.25f, 0.0f);
                Math_SmoothStepToF(&gCsCamAtY, (player->pos.y * player->unk_148) + 20.0f, 1.0f, 1.5f, 0.0f);
            }

            if (gCsFrameCount >= 605) {
                Math_SmoothStepToF(&gCsCamEyeX, 0.0f, 1.0f, 3.0f, 0.0f);
                Math_SmoothStepToF(&gCsCamEyeY, (player->pos.y * player->unk_148) + 50.0f, 1.0f, 2.0f, 0.0f);
                Math_SmoothStepToF(&gCsCamEyeZ, player->pos.z + 400.0f, 1.0f, 80.0f, 0.0f);
                gCsCamAtZ = player->pos.z - 41.0f;
                gCsCamAtY = (player->pos.y * player->unk_148) + 20.0f;
                Math_SmoothStepToF(D_ctx_80177A48, 1.0f, 0.1f, 0.1f, 0);
            }

            switch (gCsFrameCount) {
                case 580:
                    for (i = 6; i < 10; i++) {
                        Object_Kill(&gActors[i].obj, gActors[i].sfxSource);
                    }

                    for (i = 5; i < 7; i++) {
                        SectorY_801A0510(&gActors[i + 2], i);
                    }
                    SectorY_801A0510(&gActors[9], 9);
                    break;

                case 590:
                    Object_Kill(&gActors[0].obj, gActors[0].sfxSource);
                    break;

                case 600:
                    Object_Kill(&gActors[2].obj, gActors[9].sfxSource);
                    Object_Kill(&gActors[1].obj, gActors[8].sfxSource);
                    break;
            }

            if (gCsFrameCount >= 609) {
                gActors[7].obj.pos.z = -7100.0f;
                gActors[8].obj.pos.z = -8100.0f;
                gActors[9].obj.pos.z = -7100.0f;

                D_ctx_80177A48[0] = 1.0f;

                player->pos.z = player->trueZpos = 0.0f;
                player->baseSpeed = gArwingSpeed;

                AUDIO_PLAY_BGM(NA_BGM_STAGE_SY);

                gLevelStartStatusScreenTimer = 100;

                player->state = PLAYERSTATE_ACTIVE;
                player->csState = 0;
                player->csTimer = 0;
                player->csEventTimer = 0;
                gCsCamEyeX = player->pos.x;
                gCsCamEyeY = (player->pos.y * player->unk_148) + 50.0f;
                gCsCamEyeZ = 400.0f;
                gCsCamAtX = player->pos.x;
                gCsCamAtY = (player->pos.y * player->unk_148) + 20.0f;
                gCsCamAtZ = player->trueZpos;
                player->cam.eye.x = player->pos.x;
                player->cam.eye.y = player->pos.y * player->unk_148;
                player->cam.eye.y += 50.0f;
                player->cam.eye.z = 400.0f;
                player->cam.at.x = player->pos.x;
                player->cam.at.y = player->pos.y * player->unk_148;
                player->cam.at.y += 20.0f;
                player->cam.at.z = player->trueZpos - 41.0f;

                for (i = 0; i < 11; i++) {
                    Object_Kill(&gActors[i].obj, gActors[i].sfxSource);
                }
            }
            break;
    }
    Math_SmoothStepToF(&player->cam.eye.x, gCsCamEyeX, D_ctx_80177A48[0], 20000.0f, 0);
    Math_SmoothStepToF(&player->cam.eye.y, gCsCamEyeY, D_ctx_80177A48[0], 20000.0f, 0);
    Math_SmoothStepToF(&player->cam.eye.z, gCsCamEyeZ, D_ctx_80177A48[0], 20000.0f, 0);
    Math_SmoothStepToF(&player->cam.at.x, gCsCamAtX, D_ctx_80177A48[0], 20000.0f, 0);
    Math_SmoothStepToF(&player->cam.at.y, gCsCamAtY, D_ctx_80177A48[0], 20000.0f, 0);
    Math_SmoothStepToF(&player->cam.at.z, gCsCamAtZ, D_ctx_80177A48[0], 20000.0f, 0);
    Matrix_RotateY(gCalcMatrix, (player->rot.y + 180.0f) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -(player->rot.x * M_DTOR), MTXF_APPLY);
    spA4.x = 0.0f;
    spA4.y = 0.0f;
    spA4.z = player->baseSpeed;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &spA4, &sp98);
    player->vel.x = sp98.x;
    player->vel.z = sp98.z;
    player->vel.y = sp98.y;
    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;
    player->pos.z += player->vel.z;
    player->trueZpos = player->pos.z + player->camDist;
}

void SectorY_ActorDebris_Setup(ActorDebris* this, f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel,
                               s32 state) {
    Actor_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_ACTOR_DEBRIS;

    this->state = state;
    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;
    this->vel.x = xVel;
    this->vel.y = yVel;
    this->vel.z = zVel;
    this->scale = 2.5f;
    this->timer_0BC = RAND_INT(15.0f) + 15.0f;
    Object_SetInfo(&this->info, this->obj.id);
}

void SectorY_ActorDebris_Spawn(f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, s32 state) {
    s32 i;

    for (i = ARRAY_COUNT(gActors) - 1; i >= 0; i--) {
        if (gActors[i].obj.status == OBJ_FREE) {
            SectorY_ActorDebris_Setup(&gActors[i], xPos, yPos, zPos, xVel, yVel, zVel, state);
            break;
        }
    }
}

void SectorY_SyRobot_Update(SyRobot* this) {
    f32 sp1E4;
    f32 sp1E0;
    s32 i;
    f32 sp1D8;
    f32 sp1D4;
    f32 sp1D0;
    Vec3f sp68[30];
    Vec3f sp5C;
    Vec3f sp50;
    s32 sp4C = 30;
    s32 pad;

    this->iwork[14] = this->eventType - 48;
    this->info.drawType = 2;

    if (this->iwork[18] != 0) {
        this->iwork[18]--;
    }

    if ((this->work_048 != 0) && (this->work_046 != 3)) {
        switch (this->work_048) {
            case 1:
                this->work_046 = 1;
                this->timer_0BE = 50;
                this->iwork[19] = 0;
                break;

            case 2:
                this->work_046 = 1;
                this->timer_0BE = 20;
                this->iwork[19] = 0;
                break;

            case 3:
                this->work_046 = 2;
                this->animFrame = 0;
                break;

            case 4:
                this->work_046 = 0;
                this->animFrame = 0;
                break;

            case 8:
                this->work_046 = 1;
                this->timer_0BE = 50;
                this->iwork[19] = 1;
                break;

            case 9:
                this->work_046 = 1;
                this->timer_0BE = 20;
                this->iwork[19] = 1;
                break;

            case 10:
                this->work_046 = 1;
                this->timer_0BE = 50;
                this->iwork[19] = -1;
                break;

            case 11:
                this->work_046 = 1;
                this->timer_0BE = 20;
                this->iwork[19] = -1;
                break;

            case 6:
                this->work_046 = 4;
                this->animFrame = 0;
                break;

            case 5:
                this->work_046 = 5;
                this->animFrame = Animation_GetFrameCount(&D_SY_602B778) - 1;
                break;

            case 7:
                this->work_046 = 6;
                this->animFrame = Animation_GetFrameCount(&D_SY_602B778) - 1;
                break;
        }
        this->work_048 = 0;
        this->fwork[15] = 0.0f;
    }

    switch (this->work_046) {
        case 0:
            i = this->iwork[17];
            if (i != 0) {
                if (i == 1) {
                    this->animFrame = Animation_GetFrameCount(&D_SY_60265B4) - 1;
                    sp4C = Animation_GetFrameData(&D_SY_60265B4, this->animFrame, sp68);
                } else if (i == 2) {
                    this->animFrame = Animation_GetFrameCount(&D_SY_602B8DC) - 1;
                    sp4C = Animation_GetFrameData(&D_SY_602B8DC, this->animFrame, sp68);
                }
            } else {
                this->animFrame = Animation_GetFrameCount(&D_SY_602CEB4);
                sp4C = Animation_GetFrameData(&D_SY_602CEB4, this->animFrame, sp68);
            }
            break;

        case 1:
            i = this->iwork[17];
            if (i != 0) {
                if (i == 1) {
                    this->animFrame = Animation_GetFrameCount(&D_SY_60265B4) - 1;
                    sp4C = Animation_GetFrameData(&D_SY_60265B4, this->animFrame, sp68);
                } else if (i == 2) {
                    this->animFrame = Animation_GetFrameCount(&D_SY_602B8DC) - 1;
                    sp4C = Animation_GetFrameData(&D_SY_602B8DC, this->animFrame, sp68);
                }
            } else {
                this->animFrame = Animation_GetFrameCount(&D_SY_602A2CC) - 1;
                sp4C = Animation_GetFrameData(&D_SY_602A2CC, this->animFrame, sp68);
            }

            if (this->timer_0BE == 15) {
                this->timer_0C4 = 4;
                this->fwork[19] = 30.0f;
                if (this->iwork[19] < 0) {
                    ActorEvent_8006F254(this);
                } else {
                    sp1E4 = gPlayer[0].pos.x;
                    sp1E0 = gPlayer[0].pos.y;
                    if (this->iwork[19] != 0) {
                        gPlayer[0].pos.x += RAND_FLOAT_CENTERED(300.0f);
                        gPlayer[0].pos.y += RAND_FLOAT_CENTERED(300.0f);
                    }
                    Effect_EnemyLaser(OBJ_EFFECT_354, this->fwork[16], this->fwork[17], this->fwork[18], 100.0f);
                    gPlayer[0].pos.x = sp1E4;
                    gPlayer[0].pos.y = sp1E0;
                    AUDIO_PLAY_SFX(NA_SE_EN_MS_SHOT_S, this->sfxSource, 4);
                }
                this->work_048 = 0;
            }

            if (this->timer_0BE == 0) {
                this->animFrame = 0;
                this->work_046 = 0;
                this->fwork[15] = 0.0f;
            }
            break;

        case 2:
            if (this->animFrame < (Animation_GetFrameCount(&D_SY_6029B48) - 1)) {
                this->animFrame++;
            }
            sp4C = Animation_GetFrameData(&D_SY_6029B48, this->animFrame, sp68);
            break;

        case 4:
            this->animFrame++;
            if (this->animFrame >= (Animation_GetFrameCount(&D_SY_602B778) - 1)) {
                this->work_046 = 0;
                this->iwork[17] = 0;
                this->fwork[15] = 0.0f;
            }
            sp4C = Animation_GetFrameData(&D_SY_602B778, this->animFrame, sp68);
            break;

        case 5:
        case 6:
            this->animFrame--;
            if (this->animFrame < 8) {
                this->fwork[15] = 0.1f;
                if (this->work_046 == 5) {
                    this->iwork[17] = 1;
                } else {
                    this->iwork[17] = 2;
                }
                this->work_046 = 0;
            }
            sp4C = Animation_GetFrameData(&D_SY_602B778, this->animFrame, sp68);
            break;

        case 3:
            this->animFrame++;
            if (this->animFrame >= Animation_GetFrameCount(&D_SY_6003348)) {
                this->animFrame = Animation_GetFrameCount(&D_SY_6003348) - 1;
            }

            sp4C = Animation_GetFrameData(&D_SY_6003348, this->animFrame, sp68);

            if ((this->timer_0BE % 4U) == 0) {
                func_effect_8007D2C8(RAND_FLOAT_CENTERED(150.0f) + this->obj.pos.x,
                                     RAND_FLOAT_CENTERED(150.0f) + this->obj.pos.y, this->obj.pos.z + 30.0f, 4.0f);
            }

            if (this->timer_0BE == 5U) {
                Effect386_Spawn1(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, this->vel.x, this->vel.y,
                                 this->vel.z, 8.0f, 10);
                Effect_Effect384_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 8.0f, 5);
                AUDIO_PLAY_SFX(NA_SE_EN_MS_EXPLOSION_S, this->sfxSource, 4);
            }

            if (this->timer_0BE == 0) {
                Object_Kill(&this->obj, this->sfxSource);
                Actor_Despawn(this);
                for (i = 10; i < 24; i++) {
                    SectorY_ActorDebris_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z,
                                              RAND_FLOAT_CENTERED(50.0f), RAND_FLOAT_CENTERED(50.0f),
                                              this->vel.z + RAND_FLOAT_CENTERED(50.0f), i);
                }
            }
            break;
    }

    if ((this->work_046 == 1) || (this->work_046 == 2)) {
        Matrix_RotateZ(gCalcMatrix, -this->vwork[29].z * M_DTOR, MTXF_NEW);
        Matrix_RotateX(gCalcMatrix, -this->vwork[29].x * M_DTOR, MTXF_APPLY);
        Matrix_RotateY(gCalcMatrix, -this->vwork[29].y * M_DTOR, MTXF_APPLY);
        Matrix_RotateZ(gCalcMatrix, -this->obj.rot.z * M_DTOR, MTXF_APPLY);
        Matrix_RotateX(gCalcMatrix, -this->obj.rot.x * M_DTOR, MTXF_APPLY);

        if (this->iwork[17] == 0) {
            Matrix_RotateY(gCalcMatrix, -this->obj.rot.y * M_DTOR, MTXF_APPLY);
        }

        sp5C.x = gPlayer[0].pos.x - this->obj.pos.x;
        sp5C.y = gPlayer[0].pos.y - this->obj.pos.y;
        sp5C.z = gPlayer[0].pos.z - this->obj.pos.z;

        Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp5C, &sp50);

        sp1D4 = Math_RadToDeg(Math_Atan2F(sp50.x, sp50.z));
        sp1D8 = Math_RadToDeg(-Math_Atan2F(sp50.y, sqrtf(SQ(sp50.x) + SQ(sp50.z))));

        if ((sp1D8 > 90.0f) && (sp1D8 < 180.0f)) {
            sp1D8 = 90.0f;
        }
        if ((sp1D8 < 270.0f) && (sp1D8 > 180.0f)) {
            sp1D8 = 270.0f;
        }

        if (this->iwork[17] != 0) {
            Math_SmoothStepToAngle(&this->obj.rot.y, sp1D4, 0.1f, 2.0f, 0.0f);
            sp1D0 = sp1D4 - this->obj.rot.y;
            sp1D4 = 0.0f;
        } else {
            if ((sp1D4 > 90.0f) && (sp1D4 < 180.0f)) {
                sp1D4 = 90.0f;
            }
            if ((sp1D4 < 270.0f) && (sp1D4 > 180.0f)) {
                sp1D4 = 270.0f;
            }
            sp1D0 = sp1D4 - this->fwork[0x15];
        }
    } else {
        sp1D0 = sp1D8 = sp1D4 = 0.0f;
    }
    Math_SmoothStepToAngle(&this->fwork[0x15], sp1D4, 0.1f, 2.0f, 0.0f);
    Math_SmoothStepToAngle(&this->fwork[20], sp1D8, 0.1f, 2.0f, 0.0f);

    if (sp1D0 < 0.0f) {
        sp1D0 += 360.0f;
    }

    Math_SmoothStepToAngle(&this->fwork[28], sp1D0, 0.2f, 5.0f, 0.0f);
    Math_SmoothStepToAngle(&this->fwork[29], sp1D8, 0.2f, 5.0f, 0.0f);
    Math_SmoothStepToVec3fArray(sp68, this->vwork, 1, sp4C, this->fwork[15], 100.0f, 0.0f);

    if ((this->work_046 == 6) || (this->work_046 == 5)) {
        Math_SmoothStepToF(&this->fwork[15], 0.3f, 1.0f, 0.05f, 0.0f);
    } else {
        Math_SmoothStepToF(&this->fwork[15], 0.2f, 1.0f, 0.015f, 0.0f);
    }
    Math_SmoothStepToF(&this->fwork[19], 0.0f, 0.2f, 10.0f, 0.0f);

    if (this->iwork[17] != 0) {
        Math_SmoothStepToF(&this->fwork[27], 1.5f, 1.0f, 0.2f, 0.0f);
    } else {
        Math_SmoothStepToF(&this->fwork[27], 0.0f, 1.0f, 0.05f, 0.0f);
    }

    this->info.hitbox = SEGMENTED_TO_VIRTUAL(aSyRobotHitbox);
    if (this->work_046 == 1) {
        this->info.hitbox = SEGMENTED_TO_VIRTUAL(D_SY_603421C);
    }

    i = this->iwork[17];
    if (i != 0) {
        if (i == 1) {
            this->info.hitbox = SEGMENTED_TO_VIRTUAL(aSyRobot4Hitbox);
        } else if (i == 2) {
            this->info.hitbox = SEGMENTED_TO_VIRTUAL(D_SY_60341A8);
        }
    }
    if (this->work_046 == 2) {
        this->info.hitbox = SEGMENTED_TO_VIRTUAL(D_SY_60340C0);
    }

    if ((this->dmgType != DMG_NONE) && (this->work_046 != 3)) {

        if (this->dmgType == DMG_EXPLOSION) {
            this->dmgPart = 1;
        }
        this->dmgType = DMG_NONE;
        if (this->dmgPart == 0) {
            this->iwork[18] = 15;
            AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);

        } else {
            AUDIO_PLAY_SFX(NA_SE_EN_DAMAGE_S, this->sfxSource, 4);
            this->timer_0C6 = 15;
            Effect_Effect390_Spawn(this->hitPos.x, this->hitPos.y, this->hitPos.z, this->vel.x, this->vel.y,
                                   this->vel.z, 0.1f, 10);
            this->health -= this->damage;

            if (this->health <= 0) {
                this->work_046 = 3;
                this->work_048 = 0;
                this->animFrame = 0;
                this->timer_0BE = 50;
                this->fwork[15] = 0.0f;
            }
        }
    }
}

s32 D_i6_801A6B28[3] = { 255, 150, 150 };
s32 D_i6_801A6B34[3] = { 150, 255, 150 };
s32 D_i6_801A6B40[6] = { 150, 150, 255 };

bool SectorY_SyRobot_OverrideLimbDraw(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    SyRobot* actor = (SyRobot*) thisx;

    if (limbIndex == 4) {
        if ((actor->iwork[18] % 2) == 0) {
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, D_i6_801A6B28[actor->iwork[14]], D_i6_801A6B34[actor->iwork[14]],
                            D_i6_801A6B40[actor->iwork[14]], 255);
        } else {
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 0, 255, 0, 255);
        }
    } else {
        if ((actor->timer_0C6 % 2) == 0) {
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, D_i6_801A6B28[actor->iwork[14]], D_i6_801A6B34[actor->iwork[14]],
                            D_i6_801A6B40[actor->iwork[14]], 255);
        } else {
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 64, 64, 255, 255);
        }
    }

    if (limbIndex == 3) {
        rot->z -= actor->fwork[19];
        rot->z += actor->fwork[20];
    }
    if (limbIndex == 17) {
        rot->x += actor->fwork[28];
        rot->y -= actor->fwork[29];
        if (actor->eventType == EVID_SY_ROBOT_1) {
            *dList = D_SY_6014BD0;
        }
    }
    if (limbIndex == 18) {
        rot->x += actor->fwork[21];
    }

    return false;
}

void SectorY_SyRobot_PostLimbDraw(s32 limbIndex, Vec3f* rot, void* thisx) {
    Vec3f src = { 40.0f, -30.0f, 0.0f };
    Vec3f dest;
    SyRobot* actor = (SyRobot*) thisx;

    if (limbIndex == 1) {
        Matrix_MultVec3f(gCalcMatrix, &src, &dest);
        actor->fwork[16] = dest.x;
        actor->fwork[17] = dest.y;
        actor->fwork[18] = dest.z;
    }
}

f32 D_i6_801A6B64[5] = {
    0.3f, 0.7f, 1.3f, 0.7f, 0.3f,
};

void SectorY_SyRobot_Draw(SyRobot* this) {
    f32 scale;

    RCP_SetupDL_30(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
    Animation_DrawSkeleton(2, D_SY_602D140, this->vwork, SectorY_SyRobot_OverrideLimbDraw, SectorY_SyRobot_PostLimbDraw,
                           this, gCalcMatrix);

    if (this->timer_0C4 != 0) {
        scale = D_i6_801A6B64[this->timer_0C4];
        RCP_SetupDL_49();
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
        gDPSetEnvColor(gMasterDisp++, 255, 48, 0, 255);
        Matrix_Pop(&gGfxMatrix);
        Matrix_Push(&gGfxMatrix);
        Matrix_Translate(gGfxMatrix, this->fwork[16], this->fwork[17], this->fwork[18] + gPathProgress, MTXF_APPLY);
        Matrix_Scale(gGfxMatrix, scale, scale, scale, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);

        gSPDisplayList(gMasterDisp++, aOrbDL);
    }
}

void SectorY_SyShip3Destroyed_Update(SyShip3Destroyed* this) {
    Vec3f src;
    Vec3f dest;

    if (this->state == 0) {
        AUDIO_PLAY_SFX(NA_SE_OB_BROKEN_SPARK_L, this->sfxSource, 4);
        this->state++;
    }

    if ((gGameFrameCount % 4) == 0) {
        Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
        Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);
        Matrix_RotateZ(gCalcMatrix, this->obj.rot.z * M_DTOR, MTXF_APPLY);
        src.x = RAND_FLOAT_CENTERED(100.0f) + 500.0f;
        src.y = RAND_FLOAT_CENTERED(900.0f) + -150.0f;
        src.z = 90.0f - RAND_FLOAT(50.0f);
        Matrix_MultVec3f(gCalcMatrix, &src, &dest);
        Effect_Effect390_Spawn(this->obj.pos.x + dest.x, this->obj.pos.y + dest.y, this->obj.pos.z + dest.z,
                               this->effectVel.x, this->effectVel.y, this->effectVel.z, 0.2f, 5);

        src.x = RAND_FLOAT_CENTERED(100.0f) + -500.0f;
        src.y = RAND_FLOAT_CENTERED(900.0f);
        src.z = 80.0f - RAND_FLOAT(50.0f);
        Matrix_MultVec3f(gCalcMatrix, &src, &dest);
        Effect_Effect390_Spawn(this->obj.pos.x + dest.x, this->obj.pos.y + dest.y, this->obj.pos.z + dest.z,
                               this->effectVel.x, this->effectVel.y, this->effectVel.z, 0.2f, 5);

        src.x = RAND_FLOAT_CENTERED(100.0f) + 500.0f;
        src.y = RAND_FLOAT_CENTERED(900.0f) + -50.0f;
        src.z = 1900.0f - RAND_FLOAT(50.0f);
        Matrix_MultVec3f(gCalcMatrix, &src, &dest);
        Effect_Effect390_Spawn(this->obj.pos.x + dest.x, this->obj.pos.y + dest.y, this->obj.pos.z + dest.z,
                               this->effectVel.x, this->effectVel.y, this->effectVel.z, 0.2f, 5);

        src.x = RAND_FLOAT_CENTERED(100.0f) + -1000.0f;
        src.y = RAND_FLOAT_CENTERED(900.0f) + -250.0f;
        src.z = 1100.0f - RAND_FLOAT(50.0f);
        Matrix_MultVec3f(gCalcMatrix, &src, &dest);
        Effect_Effect390_Spawn(this->obj.pos.x + dest.x, this->obj.pos.y + dest.y, this->obj.pos.z + dest.z,
                               this->effectVel.x, this->effectVel.y, this->effectVel.z, 0.2f, 5);
    }
}

void SectorY_SyShip4Destroyed_Update(SyShip2Destroyed* this) {
    Vec3f src;
    Vec3f dest;

    if (this->state == 0) {
        AUDIO_PLAY_SFX(NA_SE_OB_BROKEN_SPARK_L, this->sfxSource, 4);
        this->state++;
    }

    if ((gGameFrameCount % 4) == 0) {
        Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
        Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);
        Matrix_RotateZ(gCalcMatrix, this->obj.rot.z * M_DTOR, MTXF_APPLY);
        src.x = RAND_FLOAT_CENTERED(100.0f) + -800.0f;
        src.y = RAND_FLOAT_CENTERED(300.0f) + -100.0f;
        src.z = RAND_FLOAT_CENTERED(5000.0f) + 500.0f;
        Matrix_MultVec3f(gCalcMatrix, &src, &dest);
        Effect_Effect390_Spawn(this->obj.pos.x + dest.x, this->obj.pos.y + dest.y, this->obj.pos.z + dest.z,
                               this->effectVel.x, this->effectVel.y, this->effectVel.z, 0.3f, 5);
        src.x = RAND_FLOAT_CENTERED(100.0f) + -600.0f;
        src.y = RAND_FLOAT_CENTERED(250.0f) + 300.0f;
        src.z = RAND_FLOAT_CENTERED(1500.0f) + -1650.0f;
        Matrix_MultVec3f(gCalcMatrix, &src, &dest);
        Effect_Effect390_Spawn(this->obj.pos.x + dest.x, this->obj.pos.y + dest.y, this->obj.pos.z + dest.z,
                               this->effectVel.x, this->effectVel.y, this->effectVel.z, 0.2f, 5);
    }
}
