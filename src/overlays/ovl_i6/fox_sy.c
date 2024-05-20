#include "global.h"
#include "assets/ast_sector_y.h"

typedef void (*BossFuncs)(Boss*);

void SectorY_80198244(Boss*);
void SectorY_80198ABC(Boss*);
void SectorY_80199D64(Boss*);
void SectorY_8019AA08(Boss*);
void SectorY_8019AEC0(Boss*);
void SectorY_8019A434(Boss*);
void SectorY_8019A640(Boss*);
void SectorY_8019A82C(Boss*);
bool SectorY_8019B528(Boss*);
bool SectorY_8019B5CC(Boss*);
void SectorY_8019B6E8(Boss*);
void SectorY_8019BBBC(Boss*);
void SectorY_8019BC14(Boss*);
void SectorY_8019C194(Boss*, f32, f32);
void SectorY_801A0510(Actor*, s32);
void SectorY_SetupDebris(Actor*, f32, f32, f32, f32, f32, f32, s32);
void SectorY_SpawnDebris(f32, f32, f32, f32, f32, f32, s32);

f32 D_i6_801A8440[3];

void SectorY_80197B30(Actor* actor, s32 timer) {
    Actor_Initialize(actor);
    actor->obj.status = OBJ_ACTIVE;
    actor->obj.id = OBJ_ACTOR_CUTSCENE;
    actor->obj.pos.x = gPlayer[0].pos.x;
    actor->obj.pos.y = gPlayer[0].pos.y;
    actor->obj.pos.z = gPlayer[0].pos.z;
    actor->fwork[0] = gPlayer[0].baseSpeed;
    actor->vel.x = gPlayer[0].vel.x;
    actor->vel.y = gPlayer[0].vel.y;
    actor->vel.z = gPlayer[0].vel.z;
    actor->obj.rot.x = gPlayer[0].xRot_120 + gPlayer[0].rot.x + gPlayer[0].aerobaticPitch;
    actor->obj.rot.y = gPlayer[0].yRot_114 + gPlayer[0].rot.y + 180.0f;
    actor->obj.rot.z = gPlayer[0].rot.z;
    actor->state = 5;
    actor->timer_04C = timer;
    actor->iwork[11] = 1;
    Object_SetInfo(&actor->info, actor->obj.id);
    AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, actor->sfxSource, 4);
}

void SectorY_80197C64(Effect* effect) {
    RCP_SetupDL_21();
    gSPDisplayList(gMasterDisp++, D_SY_6014A40);
    RCP_SetupDL(&gMasterDisp, SETUPDL_64);
}

void SectorY_80197CB8(Scenery* scenery) {
}

void SectorY_Boss314_Init(Boss314* this) {
    this->fwork[9] = 0.0f;
    this->swork[33] = 5500;
    this->timer_050 = 10;
    this->timer_058 = 0;
    D_ctx_80177A10[8] = 0;

    if (this->index == 0) {
        this->info.hitbox = LOAD_ASSET(D_SY_60342A0);
        this->health = 150;

        this->swork[28] = 5;
        this->fwork[43] = 3.5f;
        this->fwork[45] = 40.0f;

        if (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_START_360) {
            this->obj.pos.z = -28900.0f;
            gScenery360[0].obj.pos.z = -30000.0f;
        }

        this->rot_078.y = 0.0f;
        SectorY_8019AEC0(this);
    } else {
        this->fwork[34] = 2.8f;
        this->info.hitbox = LOAD_ASSET(D_SY_6034304);
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
        if (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_ACTIVE) {
            gPlayer[0].state_1C8 = PLAYERSTATE_1C8_START_360;
            gPlayer[0].csState = 0;
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 50);
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 50);
        }
        Object_Kill(&this->obj, this->sfxSource);
    }
}

void SectorY_80197F18(Boss* boss) {
    boss->swork[20] = 0;
    boss->swork[21] = 3;
    boss->fwork[9] = 0.0f;
    boss->timer_050 = RAND_INT(100.0f) + 60;
    if (boss->index != 0) {
        boss->timer_050 += 60;
    }
}

void SectorY_80197F84(Boss* boss) {
    f32 yaw;

    Math_SmoothStepToF(&boss->obj.pos.y, 0.0f, 0.5f, 15.0f, 0.1f);
    Math_SmoothStepToF(&boss->vel.y, 0.0f, 0.1f, 0.2f, 0.1f);
    Math_SmoothStepToF(&boss->vel.z, 0.0f, 0.1f, 0.2f, 0.1f);
    Math_SmoothStepToF(&boss->vel.x, 0.0f, 0.1f, 0.2f, 0.1f);
    Math_SmoothStepToAngle(&boss->rot_078.x, 0.0f, 0.1f, 4.0f, 0.1f);

    if (SectorY_8019B5CC(boss)) {
        Math_SmoothStepToF(&boss->obj.pos.y, 1000.0f, 0.1f, 30.0f, 0.1f);
    } else {
        Math_SmoothStepToF(&boss->obj.pos.y, 0.0f, 0.1f, 10.0f, 0.1f);
    }

    SectorY_8019B6E8(boss);
    if (boss->timer_052 == 0) {
        SectorY_8019BC14(boss);
    }

    yaw = Math_RadToDeg(Math_Atan2F(boss->fwork[18] - boss->obj.pos.x, boss->fwork[20] - boss->obj.pos.z));

    Math_SmoothStepToAngle(&boss->rot_078.y, yaw, 0.1f, 8.0f, 0.1f);

    if (boss->timer_050 == 0) {
        SectorY_80198244(boss);
    }

    if (boss->swork[22] == 1) {
        if (ABS(boss->vel.x) <= 1.0f && (ABS(boss->vel.z) <= 1.0f) &&
            (fabsf(boss->fwork[18] - boss->obj.pos.x) <= 400.0f) &&
            (fabsf(boss->fwork[20] - boss->obj.pos.z) <= 1400.0f)) {
            if ((Rand_ZeroOne() < 0.2f) && (boss->rot_078.x == 0.0f)) {
                SectorY_8019AA08(boss);
            }
            if (Rand_ZeroOne() < 0.2f) {
                SectorY_80198244(boss);
            }
        }
    }

    if (SectorY_8019B528(boss)) {
        SectorY_80198ABC(boss);
    }
}

void SectorY_80198238(Boss* boss) {
}

void SectorY_80198244(Boss* boss) {
    f32 speed;

    boss->swork[20] = 3;
    boss->swork[21] = 1;
    boss->timer_056 = (s32) (RAND_FLOAT(500.0f) + 100.0f);
    boss->fwork[11] = SIN_DEG(boss->rot_078.y) * boss->fwork[45];
    boss->fwork[13] = COS_DEG(boss->rot_078.y) * boss->fwork[45];
    speed = ABS(boss->vel.x);

    if (speed < 5.0f) {
        Math_SmoothStepToF(&boss->vel.x, boss->fwork[11], 0.1f, 5.0f, 0.1f);
    }
    speed = ABS(boss->vel.z);

    if (speed < 5.0f) {
        Math_SmoothStepToF(&boss->vel.z, boss->fwork[13], 0.1f, 5.0f, 0.1f);
    }
    boss->fwork[10] = 181.0f;
    boss->fwork[34] = 2.8f;
    AUDIO_PLAY_SFX(NA_SE_EN_MS_DASH, boss->sfxSource, 4);
}

void SectorY_801983E4(Boss* boss) {
    f32 yAngle;
    f32 xSpeed;
    f32 zSpeed;

    SectorY_8019B6E8(boss);

    if (boss->timer_052 == 0) {
        SectorY_8019BC14(boss);
    }

    Math_SmoothStepToAngle(&boss->rot_078.z, 0.0f, 0.1f, 2.0f, 0.1f);
    Math_SmoothStepToAngle(&boss->rot_078.x, 0.0f, 0.1f, 2.0f, 0.1f);
    Math_SmoothStepToF(&boss->vel.x, boss->fwork[11], 0.1f, 0.5f, 0.1f);
    Math_SmoothStepToF(&boss->vel.z, boss->fwork[13], 0.1f, 0.5f, 0.1f);
    Math_SmoothStepToF(&boss->vel.y, 0.0f, 0.1f, 0.2f, 0.1f);

    xSpeed = ABS(boss->fwork[18] - boss->obj.pos.x);
    zSpeed = ABS(boss->fwork[20] - boss->obj.pos.z);

    if (boss->rot_078.x != 0.0f) {
        Math_SmoothStepToAngle(&boss->rot_078.x, boss->fwork[10], 0.1f, 6.0f, 0.1f);
        if (boss->rot_078.x < 200.0f) {
            boss->swork[21] = 1;
            boss->fwork[10] = 0.0f;
            boss->rot_078.x = 0.0f;
            boss->rot_078.y -= 180.0f;
            boss->rot_078.z -= 180.0f;
            if (boss->rot_078.y < 0.0f) {
                boss->rot_078.y += 360.0f;
            }

            if (boss->rot_078.z < 0.0f) {
                boss->rot_078.z += 360.0f;
            }
            boss->fwork[11] = SIN_DEG(boss->rot_078.y) * boss->fwork[45];
            boss->fwork[13] = COS_DEG(boss->rot_078.y) * boss->fwork[45];
            boss->fwork[34] = 2.8f;
        }
    }

    SectorY_8019C194(boss, zSpeed, xSpeed);

    if (boss->swork[22] == 1) {
        yAngle = gPlayer[0].yRot_114 - 180.0f;
        if (yAngle < 0.0f) {
            yAngle += 360.0f;
        }

        yAngle = boss->rot_078.y - yAngle;
        if (yAngle < 0.0f) {
            yAngle += 360.0f;
        }

        if ((zSpeed <= 1300.0f) && (xSpeed <= 800.0f) && (yAngle < 260.0f) && (yAngle > 100.0f) &&
            (boss->rot_078.x == 0.0f) && (boss->fwork[34] <= 2.0f)) {
            if (Rand_ZeroOne() < 0.2f) {
                SectorY_8019AA08(boss);
            }
        }

        if ((zSpeed < 3400.0f) || (xSpeed < 2400.0f)) {
            if (((yAngle >= 60.0f) && (yAngle <= 100.0f)) || ((yAngle <= 300.0f) && (yAngle >= 260.0f))) {
                if (Rand_ZeroOne() < 0.3f) {
                    if (Rand_ZeroOne() < 0.4f) {
                        SectorY_80197F18(boss);
                    } else {
                        SectorY_80199D64(boss);
                    }
                }
            }

            if (((yAngle > 300.0f) || (yAngle < 60.0f)) && (boss->rot_078.x == 0.0f)) {
                if (Rand_ZeroOne() < 0.3f) {
                    if (Rand_ZeroOne() < 0.4f) {
                        SectorY_80197F18(boss);
                    } else {
                        SectorY_80199D64(boss);
                    }
                } else if (gPlayer[0].state_1C8 != PLAYERSTATE_1C8_U_TURN) {
                    Math_SmoothStepToAngle(&boss->rot_078.x, 181.0f, 0.1f, 6.0f, 0.1f);
                    boss->swork[21] = 3;
                    boss->fwork[11] = SIN_DEG(boss->rot_078.y) * (boss->fwork[45] + 10.0f);
                    boss->fwork[13] = COS_DEG(boss->rot_078.y) * (boss->fwork[45] + 10.0f);
                    boss->fwork[34] = 2.8f;
                }
            }
        }
    }

    if (SectorY_8019B5CC(boss)) {
        Math_SmoothStepToF(&boss->obj.pos.y, 1000.0f, 0.1f, 30.0f, 0.1f);
    } else {
        Math_SmoothStepToF(&boss->obj.pos.y, 0.0f, 0.1f, 5.0f, 0.1f);
    }

    if (boss->timer_056 == 0) {
        if (Rand_ZeroOne() <= 0.7f) {
            SectorY_80199D64(boss);
        } else {
            SectorY_80197F18(boss);
        }
    }

    if (SectorY_8019B528(boss)) {
        SectorY_80198ABC(boss);
    }
}

void SectorY_80198ABC(Boss* boss) {
    f32 yAngle;

    yAngle = Math_RadToDeg(Math_Atan2F(-boss->obj.pos.x, -300.0f - boss->obj.pos.z)) - boss->rot_078.y;
    if (yAngle < 0.0f) {
        yAngle += 360.0f;
    }

    boss->swork[20] = 4;
    boss->swork[21] = 3;
    boss->fwork[34] = 4.5f;

    boss->timer_056 = (s32) (RAND_FLOAT(100.0f) + 100.0f);
    boss->timer_050 = 0;

    if (yAngle > 180.0f) {
        boss->fwork[27] = 40.0f;
        if (boss->index == 0) {
            boss->fwork[42] = 1.8f;
        }
    } else {
        boss->fwork[27] = 320.0f;
        if (boss->index == 0) {
            boss->fwork[41] = 1.8f;
        }
    }
    AUDIO_PLAY_SFX(NA_SE_EN_MS_DASH, boss->sfxSource, 4);

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

void SectorY_80198CE4(Boss* boss) {
    f32 yAngle;

    SectorY_8019B6E8(boss);

    if (boss->timer_052 == 0) {
        SectorY_8019BC14(boss);
    }

    Math_SmoothStepToAngle(&boss->rot_078.z, boss->fwork[27], 0.1f, 0.5f, 0.1f);
    Math_SmoothStepToAngle(&boss->rot_078.x, 0.0f, 0.1f, 4.0f, 0.1f);
    yAngle = Math_RadToDeg(Math_Atan2F(-boss->obj.pos.x, -300.0f - boss->obj.pos.z));

    if (boss->index != 0) {
        Math_SmoothStepToAngle(&boss->rot_078.y, yAngle, 0.1f, 1.0f, 0.1f);
    } else {
        Math_SmoothStepToAngle(&boss->rot_078.y, yAngle, 0.1f, 2.0f, 0.1f);
    }

    if (boss->index == 0) {
        boss->vel.x = SIN_DEG(boss->rot_078.y) * (boss->fwork[45] + 20.0f);
        boss->vel.z = COS_DEG(boss->rot_078.y) * (boss->fwork[45] + 20.0f);
    } else {
        boss->vel.x = SIN_DEG(boss->rot_078.y) * boss->fwork[45];
        boss->vel.z = COS_DEG(boss->rot_078.y) * boss->fwork[45];
    }

    if (SectorY_8019B5CC(boss)) {
        Math_SmoothStepToF(&boss->obj.pos.y, 1000.0f, 0.1f, 30.0f, 0.1f);
    } else {
        Math_SmoothStepToF(&boss->obj.pos.y, 0.0f, 0.1f, 5.0f, 0.1f);
    }

    Math_SmoothStepToF(&boss->vel.y, 0.0f, 0.1f, 0.2f, 0.1f);

    yAngle -= boss->rot_078.y;
    if (yAngle < 0.0f) {
        yAngle += 360.0f;
    }

    if (!SectorY_8019B528(boss) && ((yAngle <= 20.0f) || (yAngle >= 320.0f))) {
        SectorY_80198244(boss);
    }
}

void SectorY_80198F5C(Boss* boss) {
    Vec3f vec;
    Vec3f sp48;
    f32 xDisplacement;
    f32 zDisplacement;
    s32 i;

    boss->timer_05C = 20;
    func_effect_8007C120(boss->obj.pos.x, boss->obj.pos.y, boss->obj.pos.z, boss->vel.x, boss->vel.y, boss->vel.z, 0.1f,
                         10);
    boss->health -= boss->damage;

    if (boss->health < 0) {
        boss->health = 0;
    }

    boss->timer_058 = 20;

    if (boss->health <= 0) {
        boss->unk_04C = 0;
        boss->swork[36] = 0;
        boss->swork[21] = 9;
        boss->info.hitbox = LOAD_ASSET(gNoHitbox);

        if (boss->index == 0) {
            boss->timer_058 = 20000;
            boss->vel.x = boss->vel.y = boss->vel.z = 0.0f;
            if ((gPlayer[0].state_1C8 == PLAYERSTATE_1C8_ACTIVE) || (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_U_TURN)) {
                gCsFrameCount = 0;
                gPlayer[0].state_1C8 = PLAYERSTATE_1C8_LEVEL_COMPLETE;
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
            AUDIO_PLAY_SFX(NA_SE_EN_DOWN_IMPACT, boss->sfxSource, 4);
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
                SectorY_80197B30(&gActors[i], boss->index);
                D_ctx_80177A10[9] = i;
                break;
            }
        }
        boss->timer_058 = 2000;
        boss->vel.z = 0.0f;
        boss->vel.y = 0.0f;
        boss->vel.x = 0.0f;

        if ((gPlayer[0].state_1C8 == PLAYERSTATE_1C8_ACTIVE) || (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_U_TURN)) {
            boss->timer_058 = 100;
            gPlayer[0].state_1C8 = PLAYERSTATE_1C8_STANDBY;
            gCsFrameCount = 0;
            xDisplacement = gPlayer[0].cam.eye.x - boss->obj.pos.x;
            zDisplacement = gPlayer[0].cam.eye.z - boss->obj.pos.z;
            D_ctx_80177A48[8] = Math_RadToDeg(Math_Atan2F(xDisplacement, zDisplacement));
            Matrix_RotateY(gCalcMatrix, D_ctx_80177A48[8] * M_DTOR, MTXF_NEW);
            vec.x = 0.0f;
            vec.y = 0.0f;
            vec.z = 900.0f;
            Matrix_MultVec3f(gCalcMatrix, &vec, &sp48);
            gCsCamEyeX = boss->obj.pos.x + sp48.x;
            gCsCamEyeY = boss->obj.pos.y + 400.0f;
            gCsCamEyeZ = boss->obj.pos.z + sp48.z;
            gCsCamAtX = boss->obj.pos.x;
            gCsCamAtY = boss->obj.pos.y;
            gCsCamAtZ = boss->obj.pos.z;
            D_ctx_80177A48[0] = 0.1f;
            if (Rand_ZeroOne() > 0.5f) {
                D_ctx_80177A48[9] = -3.0f;
                return;
            }
            D_ctx_80177A48[9] = 3.0f;
        }
    } else {
        if (boss->index != 0) {
            AUDIO_PLAY_SFX(NA_SE_EN_DAMAGE_S, boss->sfxSource, 4);
        } else if (boss->health > 70) {
            AUDIO_PLAY_SFX(NA_SE_OB_DAMAGE_M, boss->sfxSource, 4);
        } else {
            AUDIO_PLAY_SFX(NA_SE_EN_KNOCK_DOWN, boss->sfxSource, 4);
        }

        if ((gBosses[1].obj.status == OBJ_FREE) && (gBosses[2].obj.status == OBJ_FREE)) {
            AllRange_PlayMessage(gMsg_ID_14350, RCID_BOSS_SECTORY);
        }
    }
}

void SectorY_80199438(Boss* boss) {
    s32 i;
    s32 j;
    Vec3f vec;
    Vec3f sp68;

    if (boss->health <= 0) {
        if (boss->index == 0) {
            boss->vel.x = boss->vel.y = boss->vel.z = 0.0f;

            if (gCsFrameCount < 61) {
                boss->fwork[0] = 0.0f;
            }
            if (gCsFrameCount == 61) {
                Radio_PlayMessage(gMsg_ID_14360, RCID_BOSS_SECTORY);
            }
            if (gCsFrameCount >= 80) {
                boss->fwork[0] = 1.0f;
            }
        } else {
            D_ctx_80177A48[8] += D_ctx_80177A48[9];
            Matrix_RotateY(gCalcMatrix, D_ctx_80177A48[8] * M_DTOR, MTXF_NEW);

            vec.x = 0.0f;
            vec.y = 0.0f;
            vec.z = 900.0f;

            Matrix_MultVec3f(gCalcMatrix, &vec, &sp68);

            gCsCamEyeX = boss->obj.pos.x + sp68.x;
            gCsCamEyeZ = boss->obj.pos.z + sp68.z;

            if ((boss->timer_058 == 40) && gBosses[1].obj.status == OBJ_FREE && gBosses[2].obj.status == OBJ_FREE) {
                Radio_PlayMessage(gMsg_ID_14360, RCID_BOSS_SECTORY);
            }
            if (boss->timer_058 > 85) {
                boss->fwork[0] = 0.0f;
            }
            if (boss->timer_058 < 67) {
                boss->fwork[0] = 1.0f;
            }
            if ((boss->timer_058 == 60) && (boss->swork[19] == 0)) {
                BonusText_Display(boss->obj.pos.x, boss->obj.pos.y, boss->obj.pos.z, 3);
                gHitCount += 4;
            }
            if (boss->timer_058 == 50) {
                AUDIO_PLAY_SFX(NA_SE_EN_MS_EXPLOSION_S, boss->sfxSource, 4);
                gControllerRumbleFlags[gMainController] = 1;
                gControllerRumbleTimers[gMainController] = 20;
                D_ctx_80177850 = 15;
                boss->swork[36]++;
                func_effect_8007BFFC(boss->obj.pos.x, boss->obj.pos.y, boss->obj.pos.z, boss->vel.x, boss->vel.y,
                                     boss->vel.z, 8.0f, 10);
                func_effect_8007B344(boss->obj.pos.x, boss->obj.pos.y, boss->obj.pos.z, 8.0f, 5);
                for (i = 10; i < 24; i++) {
                    if (i != 15) {
                        SectorY_SpawnDebris(boss->obj.pos.x, boss->obj.pos.y, boss->obj.pos.z,
                                            RAND_FLOAT_CENTERED(50.0f), RAND_FLOAT_CENTERED(50.0f),
                                            RAND_FLOAT_CENTERED(50.0f) + boss->vel.z, i);
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

        if (((gGameFrameCount % 4) == 0) && (boss->swork[36] == 0)) {
            func_effect_8007C120(boss->obj.pos.x, boss->obj.pos.y, boss->obj.pos.z, boss->vel.x, boss->vel.y,
                                 boss->vel.z, 0.1f, 5);
        }

        if ((gCsFrameCount == 120) && (boss->swork[36] == 0) && (boss->index == 0)) {
            if (boss->swork[19] == 0) {
                Boss_AwardBonus(boss);
            }

            for (i = 0; i < 2; i++) {
                if (gEffects[i].obj.status != OBJ_FREE) {
                    Object_Kill(&gEffects[i].obj, gEffects[i].sfxSource);
                }
            }

            Audio_KillSfxBySource(boss->sfxSource);
            gShowBossHealth = 0;
            func_effect_8007A568(boss->obj.pos.x, boss->obj.pos.y, boss->obj.pos.z, 40.0f);
            func_effect_8007D0E0(boss->obj.pos.x, boss->obj.pos.y, boss->obj.pos.z, 30.0f);
            func_enmy_80062B60(boss->obj.pos.x, boss->obj.pos.z, 0, 120.0f);
            gCameraShake = 25;
            boss->swork[36]++;

            for (i = 10; i < 24; i++) {
                if (i != 15) {
                    SectorY_SpawnDebris(boss->obj.pos.x, boss->obj.pos.y, boss->obj.pos.z, RAND_FLOAT_CENTERED(50.0f),
                                        RAND_FLOAT_CENTERED(50.0f), RAND_FLOAT_CENTERED(50.0f) + boss->vel.z, i);
                }
            }
            boss->timer_058 = 100;
            boss->vel.x = boss->vel.y = boss->vel.z = 0.0f;
        }

        if (boss->timer_058 == 1) {
            if (boss->index != 0) {
                Object_Kill(&gActors[D_ctx_80177A10[9]].obj, gActors[D_ctx_80177A10[9]].sfxSource);
                if ((gBosses[1].obj.status == OBJ_FREE) || (gBosses[2].obj.status == OBJ_FREE)) {
                    gBosses[0].unk_04A = 1;
                    gScenery360[0].info.dList = D_SY_601F3D0;
                    gScenery360[0].info.drawType = 0;
                } else {
                    gPlayer[0].state_1C8 = PLAYERSTATE_1C8_ACTIVE;
                    Camera_UpdateArwing360(&gPlayer[0], 1);
                    gPlayer[0].unk_014 = 0.0f;
                    if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                        AllRange_PlayMessage(gMsg_ID_14230, RCID_PEPPY);
                    }
                }
            }
            Object_Kill(&boss->obj, boss->sfxSource);
        }
    } else {
        if (boss->health < 80) {
            if (boss->swork[25] == 0) {
                boss->swork[25] = 1;

                for (j = ARRAY_COUNT(gActors) - 1; j >= 0; j--) {
                    if (gActors[j].obj.status == OBJ_FREE) {
                        SectorY_SetupDebris(&gActors[j], boss->fwork[28], boss->fwork[29], boss->fwork[30],
                                            RAND_FLOAT_CENTERED(50.0f), RAND_FLOAT_CENTERED(50.0f),
                                            RAND_FLOAT_CENTERED(50.0f) + boss->vel.z, 15);
                        break;
                    }
                }
                func_effect_8007D2C8(boss->obj.pos.x, boss->obj.pos.y, boss->obj.pos.z + 30.0f, 4.0f);
                boss->info.hitbox = LOAD_ASSET(D_SY_6034304);
                AUDIO_PLAY_SFX(NA_SE_EN_MS_SHIELD_BROKEN, boss->sfxSource, 4);
            }
        }
        if (boss->health <= 80) {
            boss->swork[33] = 3500;
        }
        if (boss->health <= 70) {
            boss->swork[29] = 31;
        }
        if (boss->health <= 50) {
            boss->swork[29] = 15;
        }
        if (boss->health <= 30) {
            boss->swork[29] = 7;
        }
        if (boss->health <= 10) {
            boss->swork[29] = 3;
        }
    }
}

void SectorY_80199D64(Boss* boss) {
    if (boss->swork[34] >= 2) {
        boss->swork[20] = 6;
        boss->swork[21] = 1;
        boss->fwork[12] = 1000.0f;
        boss->fwork[34] = 2.8f;
        boss->timer_056 = 0;
        boss->vel.y = 0.0f;
    }
}

void SectorY_80199DAC(Boss* boss) {
    f32 sp34;
    f32 zSpeed;
    f32 xSpeed;
    f32 yAngle;

    SectorY_8019B6E8(boss);
    if (boss->timer_052 == 0) {
        SectorY_8019BC14(boss);
    }

    sp34 = Math_RadToDeg(Math_Atan2F(0.0f - boss->obj.pos.x, -300.0f - boss->obj.pos.z));

    boss->fwork[11] = SIN_DEG(sp34) * (boss->fwork[45] + 10.0f);
    boss->fwork[13] = COS_DEG(sp34) * (boss->fwork[45] + 10.0f);
    boss->fwork[10] = sp34;

    Math_SmoothStepToAngle(&boss->rot_078.z, 0.0f, 0.1f, 4.0f, 0.1f);
    Math_SmoothStepToAngle(&boss->rot_078.y, boss->fwork[10], 0.1f, 6.0f, 0.1f);
    Math_SmoothStepToF(&boss->obj.pos.y, boss->fwork[12], 1.0f, 15.0f, 1.0f);

    if (((ABS(boss->obj.pos.y) - boss->fwork[12]) <= 1800.0f) && (ABS(boss->obj.pos.x) <= 1800.0f) &&
        (ABS(boss->obj.pos.z + 300.0f) <= 1800.0f)) {

        boss->vel.x = 0.0f;
        boss->vel.z = 0.0f;

        Math_SmoothStepToF(&boss->obj.pos.x, 0.0f, 0.1f, ABS(boss->fwork[11]), 0.1f);
        Math_SmoothStepToF(&boss->obj.pos.z, -300.0f, 0.1f, ABS(boss->fwork[13]), 0.1f);
        Math_SmoothStepToAngle(&boss->rot_078.x, 0.0f, 0.1f, 4.0f, 0.1f);

        boss->fwork[10] = 0.0f;

        if (((ABS(boss->obj.pos.y) - boss->fwork[12]) <= 300.0f) && (ABS(boss->obj.pos.x) <= 300.0f) &&
            (ABS(boss->obj.pos.z + 300.0f) <= 300.0f)) {
            Math_SmoothStepToF(&boss->fwork[43], 3.0f, 0.1f, 0.1f, 0.1f);
            boss->swork[21] = 6;
            boss->unk_04C = 27;
            boss->fwork[12] = 320.0f;
            if (boss->timer_056 == 0) {
                boss->timer_056 = 51;
                AUDIO_PLAY_SFX(NA_SE_EN_MS_DASH, boss->sfxSource, 4);
            }
        }
    } else {
        Math_SmoothStepToF(&boss->vel.x, boss->fwork[11], 0.1f, 0.5f, 0.1f);
        Math_SmoothStepToF(&boss->vel.z, boss->fwork[13], 0.1f, 0.5f, 0.1f);
        yAngle = gPlayer[0].yRot_114 - 180.0f;
        if (yAngle < 0.0f) {
            yAngle += 360.0f;
        }
        yAngle = boss->rot_078.y - yAngle;
        if (yAngle < 0.0f) {
            yAngle += 360.0f;
        }

        zSpeed = ABS(boss->fwork[20] - boss->obj.pos.z);
        xSpeed = ABS(boss->fwork[18] - boss->obj.pos.x);

        if (boss->rot_078.x != 0.0f) {
            if ((yAngle > 300.0f) || (yAngle < 60.0f)) {
                Math_SmoothStepToAngle(&boss->rot_078.x, 181.0f, 0.1f, 6.0f, 0.1f);
            } else {
                Math_SmoothStepToAngle(&boss->rot_078.x, 0.0f, 0.1f, 6.0f, 0.1f);
            }
        } else if ((boss->swork[22] == 1) && ((yAngle > 300.0f) || (yAngle < 60.0f)) && (Rand_ZeroOne() > 0.2f)) {
            Math_SmoothStepToAngle(&boss->rot_078.x, 181.0f, 0.1f, 6.0f, 0.1f);
            boss->swork[21] = 3;
            boss->fwork[34] = 2.8f;
        }
        if (!SectorY_8019B5CC(boss)) {
            SectorY_8019C194(boss, zSpeed, xSpeed);
        }
    }

    if (boss->timer_056 == 1) {
        sp34 = Rand_ZeroOne();
        if (sp34 >= 0.3f) {
            SectorY_8019A82C(boss);
        }
        if (sp34 < 0.2f) {
            SectorY_8019A434(boss);
        }
        if ((sp34 < 0.3f) && (sp34 >= 0.2f)) {
            SectorY_8019A640(boss);
        }
    }
}

void SectorY_8019A434(Boss* boss) {
    boss->swork[20] = 7;
    boss->swork[21] = 5;
    boss->timer_056 = (s32) (RAND_FLOAT(130.0f) + 60.0f);
    boss->fwork[11] = SIN_DEG(boss->rot_078.y) * boss->fwork[45];
    boss->fwork[13] = COS_DEG(boss->rot_078.y) * boss->fwork[45];
    boss->fwork[12] = 30.0f;
    boss->fwork[10] = 181.0f;
    AUDIO_PLAY_SFX(NA_SE_EN_MS_LAND, boss->sfxSource, 4);
}

void SectorY_8019A520(Boss* boss) {
    SectorY_8019B6E8(boss);
    if (boss->timer_052 == 0) {
        SectorY_8019BC14(boss);
    }

    Math_SmoothStepToAngle(&boss->rot_078.y, 0.0f, 0.1f, 2.0f, 0.1f);
    Math_SmoothStepToF(&boss->vel.x, 0.0f, 0.1f, 0.2f, 0.1f);
    Math_SmoothStepToF(&boss->vel.z, 6.0f, 0.1f, 0.2f, 0.1f);
    Math_SmoothStepToF(&boss->vel.y, 0.0f, 0.1f, 0.2f, 0.1f);

    if (boss->timer_056 == 0) {
        SectorY_8019A640(boss);
    } else {
        boss->fwork[0] = 1.0f;
    }

    if ((boss->unk_04C == 0) || (boss->unk_04C == 27)) {
        AUDIO_PLAY_SFX(NA_SE_EN_HEAVY_WALK, boss->sfxSource, 4);
    }
}

void SectorY_8019A640(Boss* boss) {
    boss->swork[20] = 8;
    boss->swork[21] = 0;
    boss->vel.x = 0.0f;
    boss->vel.y = 0.0f;
    boss->vel.z = 0.0f;
    boss->timer_056 = 80;
}

void SectorY_8019A66C(Boss* boss) {

    SectorY_8019B6E8(boss);
    if (boss->timer_052 == 0) {
        SectorY_8019BC14(boss);
    }

    if (boss->timer_056 == 60) {
        AUDIO_PLAY_SFX(NA_SE_EN_MS_DASH, boss->sfxSource, 4);
        boss->fwork[34] = 4.5f;
        if (Rand_ZeroOne() > 0.5f) {
            AllRange_PlayMessage(gMsg_ID_14330, RCID_BOSS_SECTORY);
        } else {
            AllRange_PlayMessage(gMsg_ID_14320, RCID_BOSS_SECTORY);
        }
    }

    if (boss->timer_056 <= 60) {
        boss->fwork[11] = SIN_DEG(boss->rot_078.y) * boss->fwork[45];
        boss->fwork[13] = COS_DEG(boss->rot_078.y) * boss->fwork[45];
        boss->swork[21] = 1;
        Math_SmoothStepToF(&boss->fwork[43], 0.0f, 0.1f, 0.1f, 0.1f);
        Math_SmoothStepToF(&boss->vel.z, boss->fwork[13], 0.1f, 0.5f, 0.5f);
        Math_SmoothStepToF(&boss->vel.x, boss->fwork[11], 0.1f, 0.5f, 0.5f);
        Math_SmoothStepToF(&boss->vel.y, 10.0f, 0.1f, 0.5f, 0.5f);
    }

    if (boss->timer_056 == 0) {
        SectorY_80198244(boss);
    }
}

void SectorY_8019A82C(Boss* boss) {
    boss->swork[20] = 9;
    boss->fwork[9] = 0.0f;
    boss->timer_050 = RAND_INT(150.0f) + 340;
    boss->timer_056 = 0;
    AllRange_PlayMessage(gMsg_ID_14340, RCID_BOSS_SECTORY);
}

void SectorY_8019A898(Boss* boss) {
    f32 yAngle1;
    f32 yAngle2;

    SectorY_8019B6E8(boss);
    if (boss->timer_052 == 0) {
        SectorY_8019BC14(boss);
    }

    yAngle1 = Math_RadToDeg(Math_Atan2F(boss->fwork[18] - boss->obj.pos.x, boss->fwork[20] - boss->obj.pos.z));
    yAngle2 = yAngle1 - boss->rot_078.y;
    if (yAngle2 < 0.0f) {
        yAngle2 += 360.0f;
    }

    boss->swork[21] = 6;

    if (((yAngle2 >= 30.0f) && (yAngle2 <= 330.0f)) || ((boss->unk_04C != 0)) && (boss->unk_04C != 27)) {
        boss->swork[21] = 5;
        Math_SmoothStepToAngle(&boss->rot_078.y, yAngle1, 0.1f, 2.0f, 0.1f);
        boss->fwork[0] = 1.0f;
        if ((boss->unk_04C == 0) || (boss->unk_04C == 27)) {
            AUDIO_PLAY_SFX(NA_SE_EN_HEAVY_WALK, boss->sfxSource, 4);
        }
    } else {
        boss->timer_056 = 0;
    }

    if (boss->timer_050 == 0) {
        SectorY_8019A434(boss);
    }
}

void SectorY_8019AA08(Boss* boss) {
    if (SectorY_8019B5CC(boss)) {
        return;
    }

    if ((gBosses[1].obj.status == OBJ_FREE) && (gBosses[2].obj.status == OBJ_FREE)) {
        AllRange_PlayMessage(gMsg_ID_14330, RCID_BOSS_SECTORY);
    }

    if (Rand_ZeroOne() >= 0.5f) {
        boss->swork[21] = 7;
        boss->swork[31] = 11;
        boss->swork[32] = Animation_GetFrameCount(&D_SY_602645C) - 1;

    } else if (boss->index == 0) {
        boss->swork[21] = 8;
        boss->swork[31] = 13;
        boss->swork[32] = Animation_GetFrameCount(&D_SY_60258A0) - 1;

    } else {
        return;
    }

    boss->swork[20] = 10;
    boss->unk_04C = 0;
    boss->fwork[34] = 2.8f;
}

void SectorY_8019AAF0(Boss* boss) {
    f32 var_fv1;
    f32 xAngle;
    f32 yAngle;
    f32 var_ft5;
    Vec3f vec;
    Vec3f vel;

    SectorY_8019BBBC(boss);

    yAngle = Math_Atan2F(boss->fwork[18] - boss->obj.pos.x, boss->fwork[20] - boss->obj.pos.z);
    var_fv1 = 500.0f;
    if (boss->health != 0) {
        var_fv1 += 200.0f;
    }

    if ((boss->swork[31] >= boss->unk_04C) && (fabsf(boss->obj.pos.z - boss->fwork[20]) < (var_fv1 + 1000.0f)) &&
        (fabsf(boss->obj.pos.x - boss->fwork[18]) < var_fv1)) {
        boss->unk_04C++;
    }

    if (boss->unk_04C >= boss->swork[32] - 29) {
        if (boss->unk_04C == boss->swork[32] - 29) {
            if (boss->swork[31] == 11) {
                AUDIO_PLAY_SFX(NA_SE_EN_MS_PUNCH, boss->sfxSource, 4);
            } else {
                AUDIO_PLAY_SFX(NA_SE_EN_MS_KICK, boss->sfxSource, 4);
            }
        }

        if (boss->unk_04C >= (boss->swork[32] - 5)) {
            SectorY_80198244(boss);
        }
    } else {
        Math_SmoothStepToF(&boss->fwork[9], boss->fwork[45] + 10.0f, 0.1f, 2.0f, 0.1f);

        var_ft5 = ABS(boss->fwork[18] - boss->obj.pos.x) + ABS(boss->fwork[20] - boss->obj.pos.z);
        xAngle = -Math_Atan2F(boss->fwork[19] - boss->obj.pos.y, var_ft5);
        Matrix_RotateY(gCalcMatrix, yAngle, MTXF_NEW);
        Matrix_RotateX(gCalcMatrix, xAngle, MTXF_APPLY);
        vec.x = 0.0f;
        vec.y = 0.0f;
        vec.z = boss->fwork[9];
        Matrix_MultVec3f(gCalcMatrix, &vec, &vel);
        boss->vel.z = vel.z;
        boss->vel.x = vel.x;
        Math_SmoothStepToAngle(&boss->rot_078.y, Math_RadToDeg(yAngle), 0.1f, 6.0f, 0.1f);
    }

    if (boss->swork[31] != 11) {

        if ((boss->rot_078.z <= 90.0f) || (boss->rot_078.z >= 270.0f)) {
            boss->fwork[19] += 70.0f;
        } else {
            boss->fwork[19] -= 50.0f;
        }
    }

    Math_SmoothStepToF(&boss->obj.pos.y, boss->fwork[19], 0.1f, 40.0f, 0.1f);

    if (D_edisplay_801615D0.z > 0.0f) {
        boss->swork[32] = 0;
    }

    if (SectorY_8019B528(boss)) {
        SectorY_80198ABC(boss);
    }

    if (boss->swork[20] == 10) {
        boss->fwork[0] = 0.25f;
    }
    if ((boss->swork[20] == 10) && (boss->unk_04C >= 12)) {
        boss->fwork[0] = 1.0f;
    }
}

void SectorY_8019AEC0(Boss* boss) {
    boss->swork[20] = 11;
    boss->swork[21] = 8;
    boss->vel.x = 0.0f;
    boss->vel.y = 0.0f;
    boss->vel.z = 0.0f;
    boss->unk_044 = 0;
}

void SectorY_8019AEEC(Boss* boss) {
    if ((boss->obj.pos.y != 365.0f) && (boss->swork[21] != 1)) {
        if (boss->unk_04A != 0) {
            if (boss->unk_04A == 1) {
                Audio_PlaySequence(SEQ_PLAYER_BGM, NA_BGM_REAL_BOSS, 0, 0);
                boss->unk_04A++;
                gPlayer[0].cam.eye.x = 0.0f;
                gPlayer[0].cam.eye.y = 200.0f;
                gPlayer[0].cam.eye.z = -20000.0f;
                gPlayer[0].cam.at.x = 0.0f;
                gPlayer[0].cam.at.y = 300.0f;
                gPlayer[0].cam.at.z = boss->obj.pos.z;
                gPlayer[0].camRoll = 0.0f;
                Radio_PlayMessage(gMsg_ID_14300, RCID_BOSS_SECTORY);
                SectorY_801A0510(&gActors[59], 7);
                gActors[59].obj.pos.y = boss->obj.pos.y - 202.0f;
                gActors[59].obj.pos.x = boss->obj.pos.x;
                gActors[59].obj.pos.z = boss->obj.pos.z - 30.0f;
                gActors[59].state = 6;
            }

            if (boss->obj.pos.y == 0.0f) {
                AUDIO_PLAY_SFX(NA_SE_LIFT_UP, gDefaultSfxSource, 4);
            }

            Math_SmoothStepToF(&boss->obj.pos.y, 365.0f, 0.1f, 5.0f, 0.1f);
            Math_SmoothStepToF(&gActors[59].obj.pos.y, 153.0f, 0.1f, 5.0f, 0.1f);
            Math_SmoothStepToF(&gPlayer[0].cam.eye.z, -28300.0f, 1.0f, 100.0f, 1.0f);

            if (gPlayer[0].cam.eye.z == -28300.0f) {
                Math_SmoothStepToF(&boss->fwork[46], 128.0f, 1.0f, 16.0f, 1.0f);
                gBossHealthBar = boss->health * 1.7f;
            }

            if (boss->obj.pos.y == 365.0f) {
                AUDIO_PLAY_SFX(NA_SE_LIFT_UP_END, gDefaultSfxSource, 4);
                boss->timer_050 = 20;
                boss->timer_056 = 135;
            }
        }
    } else {
        gPlayer[0].cam.at.z = boss->obj.pos.z;

        Math_SmoothStepToF(&gPlayer[0].cam.eye.z, -29000.0f, 1.0f, 5.0f, 1.0f);
        Math_SmoothStepToF(&gPlayer[0].cam.eye.x, 2000.0f, 1.0f, 8.0f, 1.0f);
        Math_SmoothStepToF(&boss->fwork[46], 0.0f, 1.0f, 16.0f, 1.0f);

        if (boss->timer_050 == 0) {
            boss->swork[21] = 0;
        }

        if (boss->timer_056 == 95) {
            AUDIO_PLAY_SFX(NA_SE_EN_BURNER_L, gActors[59].sfxSource, 4);
        }
        if (boss->timer_056 < 96) {
            Math_SmoothStepToF(&gActors[59].fwork[0], 0.0f, 0.1f, 0.2f, 0.05f);
            if (boss->timer_056 > 55) {
                Math_SmoothStepToF(&boss->vel.z, 80.0f, 0.1f, 2.0f, 0.5f);
                Math_SmoothStepToF(&gActors[59].vel.z, 80.0f, 0.1f, 2.0f, 0.5f);
                if (((gGameFrameCount % 2) == 0)) {
                    func_effect_8007C120(boss->obj.pos.x, boss->obj.pos.y - 150.0f, boss->obj.pos.z, 0.0f, 0.0f, 0.0f,
                                         0.1f, 5);
                }
            }
        }
        if (boss->timer_056 == 55) {
            D_i6_801A8440[0] = boss->sfxSource[0];
            D_i6_801A8440[1] = boss->sfxSource[1];
            D_i6_801A8440[2] = -500.0f;
            AUDIO_PLAY_SFX(NA_SE_EN_MS_DASH, D_i6_801A8440, 4);
            Audio_KillSfxBySource(gActors[59].sfxSource);
            boss->fwork[34] = 4.5f;
            gActors[59].vel.z = -40.0f;
            boss->vel.z = 120.0f;
        }
        if (boss->timer_056 <= 55) {
            boss->swork[21] = 1;
            Math_SmoothStepToF(&boss->fwork[43], 0.0f, 0.1f, 0.1f, 0.1f);
            Math_SmoothStepToF(&boss->vel.y, 20.0f, 0.1f, 5.0f, 0.5f);
            Math_SmoothStepToF(&gActors[59].vel.z, 0.0f, 0.1f, 1.0f, 0.5f);
        }
        if (boss->timer_056 == 0.0f) {
            SectorY_80198244(boss);
            boss->vel.z = 80.0f;
            boss->fwork[13] = 80.0f;
            boss->obj.pos.z = -12000.0f;
            gScenery360[0].obj.pos.z = -20000.0f;
            boss->fwork[43] = 0.0f;
            boss->vel.y = 0.0f;
            gPlayer[0].state_1C8 = PLAYERSTATE_1C8_ACTIVE;
            Camera_UpdateArwing360(&gPlayer[0], 1);
            gPlayer[0].unk_014 = 0.0f;
            boss->swork[34]++;
            Radio_PlayMessage(gMsg_ID_14310, RCID_BOSS_SECTORY);
            gBossFrameCount = 0;
        }
    }
}

bool SectorY_8019B528(Boss* boss) {

    if (boss->timer_050 != 0) {
        return false;
    }

    if (boss->swork[33] <= ABS(boss->obj.pos.x)) {
        return true;
    }

    if (boss->swork[33] <= ABS(boss->obj.pos.z)) {
        return true;
    }
    return false;
}

bool SectorY_8019B5CC(Boss* boss) {
    f32 pad;
    Vec3f pos;

    if ((gBosses[1].health != 0) || (gBosses[2].health != 0)) {
        return false;
    }

    if (gLevelMode == LEVELMODE_ON_RAILS) {
        return false;
    }

    Math_Vec3fFromAngles(&pos, boss->rot_078.x, boss->rot_078.y, 700.0f);

    if ((fabsf(gScenery360[0].obj.pos.x - (boss->obj.pos.x + pos.x)) < 2500.0f) &&
        (fabsf(gScenery360[0].obj.pos.z - (boss->obj.pos.z + pos.z)) < 5000.0f) &&
        (fabsf(gScenery360[0].obj.pos.y - (boss->obj.pos.y + pos.y)) < 1800.0f)) {
        return true;
    }

    return false;
}

void SectorY_8019B6E8(Boss* boss) {
    f32 var4;
    f32 var3;
    f32 var2;
    f32 var;

    var = ABS(ABS(gPlayer[0].pos.x - boss->obj.pos.x) + ABS(gPlayer[0].pos.y - boss->obj.pos.y) +
              ABS(gPlayer[0].pos.z - 1000.0f - boss->obj.pos.z));

    var2 = ABS(gActors[2].obj.pos.x - boss->obj.pos.x) + ABS(gActors[2].obj.pos.y - boss->obj.pos.y) +
           ABS(gActors[2].obj.pos.z - boss->obj.pos.z);

    var3 = ABS(gActors[3].obj.pos.x - boss->obj.pos.x) + ABS(gActors[3].obj.pos.y - boss->obj.pos.y) +
           ABS(gActors[3].obj.pos.z - boss->obj.pos.z);

    var4 = ABS(gActors[4].obj.pos.x - boss->obj.pos.x) + ABS(gActors[4].obj.pos.y - boss->obj.pos.y) +
           ABS(gActors[4].obj.pos.z - boss->obj.pos.z);

    boss->swork[22] = 1;
    boss->fwork[18] = gPlayer[0].pos.x;
    boss->fwork[19] = gPlayer[0].pos.y;
    boss->fwork[20] = gPlayer[0].pos.z;
    boss->fwork[24] = gPlayer[0].vel.x;
    boss->fwork[25] = gPlayer[0].vel.y;
    boss->fwork[26] = gPlayer[0].vel.z;

    if (var2 < var) {
        var = var2;
        boss->swork[22]++;
        boss->fwork[18] = gActors[2].obj.pos.x;
        boss->fwork[19] = gActors[2].obj.pos.y;
        boss->fwork[20] = gActors[2].obj.pos.z;
        boss->fwork[24] = gActors[2].vel.x;
        boss->fwork[25] = gActors[2].vel.y;
        boss->fwork[26] = gActors[2].vel.z;
    }

    if (var3 < var) {
        boss->swork[22] = 3;
        boss->fwork[18] = gActors[3].obj.pos.x;
        boss->fwork[19] = gActors[3].obj.pos.y;
        boss->fwork[20] = gActors[3].obj.pos.z;
        boss->fwork[24] = gActors[3].vel.x;
        boss->fwork[25] = gActors[3].vel.y;
        boss->fwork[26] = gActors[3].vel.z;
        var = var3;
    }

    if (var4 < var) {
        boss->fwork[18] = gActors[4].obj.pos.x;
        boss->fwork[19] = gActors[4].obj.pos.y;
        boss->fwork[20] = gActors[4].obj.pos.z;
        boss->fwork[24] = gActors[4].vel.x;
        boss->fwork[25] = gActors[4].vel.y;
        boss->fwork[26] = gActors[4].vel.z;
        boss->swork[22] = 4;
    }
}

void SectorY_8019BBBC(Boss* boss) {
    boss->fwork[18] = gPlayer[0].pos.x;
    boss->fwork[19] = gPlayer[0].pos.y;
    boss->fwork[20] = gPlayer[0].pos.z;
    boss->fwork[24] = gPlayer[0].vel.x;
    boss->fwork[25] = gPlayer[0].vel.y;
    boss->fwork[26] = gPlayer[0].vel.z;
}

void SectorY_8019BC14(Boss* boss) {
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 var_fa0;

    if ((ABS(boss->obj.pos.x) >= 11000.0f) || (ABS(boss->obj.pos.z) >= 11000.0f)) {
        boss->timer_052 = 2;
        return;
    }

    if ((boss->swork[0x16] == 1) && (D_edisplay_801615D0.z > 0.0f)) {
        boss->timer_052 = 2;
        return;
    }

    if (boss->swork[0x16] != 1) {
        var_fa0 = ((ABS(boss->fwork[0x12] - boss->fwork[1]) + ABS(boss->fwork[0x14] - boss->fwork[3]) +
                    ABS(boss->fwork[0x13] - boss->fwork[2])) /
                   140.0f) -
                  2.0f;
        boss->fwork[0x12] = boss->fwork[0x12] + boss->fwork[0x18] * var_fa0;
        boss->fwork[0x13] = boss->fwork[0x13] + boss->fwork[0x19] * var_fa0;
        boss->fwork[0x14] = boss->fwork[0x14] + boss->fwork[0x1A] * var_fa0;
    }

    if ((fabsf(boss->fwork[3] - boss->fwork[0x14]) > 300.0f) || (fabsf(boss->fwork[1] - boss->fwork[0x12]) > 300.0f)) {
        sp3C = Math_RadToDeg(
            Math_Atan2F(boss->fwork[0x12] - boss->fwork[1] - boss->rot_078.x, boss->fwork[0x14] - boss->fwork[3]));
        sp40 = ABS(boss->fwork[0x12] - boss->fwork[1]) + ABS(boss->fwork[0x14] - boss->fwork[3]);
        sp40 = Math_RadToDeg(-Math_Atan2F(boss->fwork[0x13] - boss->fwork[2], sp40));
        sp38 = Math_RadToDeg(Math_Atan2F(boss->fwork[1] - boss->fwork[0x15], boss->fwork[3] - boss->fwork[0x17]));
        var_fa0 = ABS(boss->fwork[1] - boss->fwork[0x15]) + ABS(boss->fwork[3] - boss->fwork[0x17]);
        var_fa0 = Math_RadToDeg(-Math_Atan2F(boss->fwork[2] - boss->fwork[0x16], var_fa0));
        sp38 = sp3C - sp38;
        var_fa0 = sp40 - var_fa0;

        if (sp38 < 0.0f) {
            sp38 += 360.0f;
        }
        if (var_fa0 < 0.0f) {
            var_fa0 += 360.0f;
        }

        if (((sp38 < 41.0f) || (sp38 > 319.0f)) && ((var_fa0 < 41.0f) || (var_fa0 > 319.0f))) {
            boss->timer_054 = 4;
            boss->fwork[4] = 30.0f;

            sp4C = gPlayer[0].pos.x;
            sp48 = gPlayer[0].pos.y;
            sp44 = gPlayer[0].pos.z;

            gPlayer[0].pos.x = boss->fwork[0x12];
            gPlayer[0].pos.y = boss->fwork[0x13];
            gPlayer[0].trueZpos = gPlayer[0].pos.z = boss->fwork[0x14];

            func_effect_8007F11C(OBJ_EFFECT_354, boss->fwork[1], boss->fwork[2], boss->fwork[3], 100.0f);

            gPlayer[0].pos.x = sp4C;
            gPlayer[0].pos.y = sp48;
            gPlayer[0].trueZpos = gPlayer[0].pos.z = sp44;

            if (boss->index == 0) {
                AUDIO_PLAY_SFX(NA_SE_EN_MS_SHOT_L, boss->sfxSource, 4);
            } else {
                AUDIO_PLAY_SFX(NA_SE_EN_MS_SHOT_S, boss->sfxSource, 4);
            }
        }
    }

    if (boss->index == 0) {
        boss->timer_052 = RAND_INT(20.0f) + 15;
    } else {
        boss->timer_052 = RAND_INT(20.0f) + 25;
    }
}

void SectorY_8019C194(Boss* boss, f32 zSpeed, f32 xSpeed) {
    f32 sp2C;
    f32 sp28;

    if ((gBossFrameCount > 250) && (boss->fwork[34] == 2.8f)) {
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
        boss->fwork[44] += 8.0f;
        if (boss->fwork[44] >= 360.0f) {
            boss->fwork[44] = 0.0f;
        }

        if (boss->index == 0) {
            sp2C = SIN_DEG(boss->fwork[44]) * ABS(boss->vel.z * 1.5f);
            boss->obj.pos.x += sp2C;

            sp28 = SIN_DEG(boss->fwork[44]) * ABS(boss->vel.x * 1.5f);
            boss->obj.pos.z += sp28;
        } else {
            sp2C = SIN_DEG(boss->fwork[44]) * ABS(boss->vel.z * 1.2f);
            boss->obj.pos.x += sp2C;

            sp28 = SIN_DEG(boss->fwork[44]) * ABS(boss->vel.x * 1.2f);
            boss->obj.pos.z += sp28;
        }

        if (!SectorY_8019B5CC(boss)) {
            if (boss->index == 0) {
                boss->obj.pos.y += SIN_DEG(boss->fwork[44]) * 30.0f;
            } else {
                boss->obj.pos.y += SIN_DEG(boss->fwork[44]) * 10.0f;
            }
        }

        if (boss->index == 0) {
            if (ABS(boss->vel.z) < ABS(boss->vel.x)) {
                sp2C = sp28;
                if ((boss->obj.rot.z <= 90.0f) || (boss->obj.rot.z >= 270.0f)) {
                    if ((boss->obj.rot.y >= 45.0f) && (boss->obj.rot.y <= 135.0f)) {
                        sp2C = -sp28;
                    }
                } else {
                    if ((boss->obj.rot.y >= 225.0f) && (boss->obj.rot.y <= 315.0f)) {
                        sp2C = -sp28;
                    }
                }
            } else {
                if ((boss->obj.rot.z <= 90.0f) || (boss->obj.rot.z >= 270.0f)) {
                    if ((boss->obj.rot.y >= 135.0f) && (boss->obj.rot.y <= 225.0f)) {
                        sp2C = -sp2C;
                    }
                } else {
                    if ((boss->obj.rot.y <= 45.0f) || (boss->obj.rot.y >= 315.0f)) {
                        sp2C = -sp2C;
                    }
                }
            }

            if (sp2C == 0.0f) {
                boss->fwork[41] = ABS(sp2C * 0.01f) + 0.8f;
            }
            if (sp2C > 0.0f) {
                if (boss->fwork[41] == 0.0f) {
                    boss->fwork[41] = ABS(sp2C * 0.01f) + 0.8f;
                    AUDIO_PLAY_SFX(NA_SE_ARWING_BRAKE, boss->sfxSource, 4);
                }
            } else if (boss->fwork[42] == 0.0f) {
                boss->fwork[42] = ABS(sp2C * 0.01f) + 0.8f;
                AUDIO_PLAY_SFX(NA_SE_ARWING_BRAKE, boss->sfxSource, 4);
            }
        }
    }
}

static BossFuncs D_i6_801A6910[] = {
    SectorY_80197F84, SectorY_80198238, SectorY_80198238, SectorY_801983E4, SectorY_80198CE4, SectorY_80199438,
    SectorY_80199DAC, SectorY_8019A520, SectorY_8019A66C, SectorY_8019A898, SectorY_8019AAF0, SectorY_8019AEEC,
};

void SectorY_Boss_Update(Boss* boss) {
    s32 i;
    f32 sp1E8;
    f32 sp1E4;
    f32 sp1E0;
    f32 sp1DC;
    f32 sp1D8;
    f32 sp1D4;
    s32 sp1D0;
    RadarMark* radarMark;
    Vec3f sp64[30];
    Vec3f sp58;
    Vec3f sp4C;
    s32 pad;

    if (gPlayer[0].state_1C8 != PLAYERSTATE_1C8_START_360) {
        if (boss->swork[34] == 1) {
            if (boss->health > 0) {
                gScenery360[0].obj.pos.z += 20.0f;
            }
            if (gScenery360[0].obj.pos.z == 0.0f) {
                boss->swork[34]++;
            }
        }
        if (boss->index == 2) {
            if ((ABS(boss->obj.pos.x - gBosses[1].obj.pos.x) < 800.0f) &&
                (ABS(boss->obj.pos.z - gBosses[1].obj.pos.z) < 800.0f) && boss->health > 0 && gBosses[1].health > 0) {
                if (ABS(boss->obj.pos.y - gBosses[1].obj.pos.y) <= 800.0f) {
                    boss->obj.pos.y += 20.0f;
                    gBosses[1].obj.pos.y -= 20.0f;
                }
            }
        }

        if ((boss->fwork[34] <= 1.0f) && (boss->fwork[34] > 0.5f)) {
            Audio_KillSfxBySource(boss->sfxSource);
        }

        gBossFrameCount++;

        boss->fwork[0] = 0.1f;
        if (boss->swork[24] != 0) {
            boss->swork[24]--;
        }
        if (boss->health > 0) {
            D_i6_801A6910[boss->swork[20]](boss);
        }
        if (boss->timer_058 != 0) {
            SectorY_80199438(boss);
        }

        if ((boss->swork[29] != 0) && !(boss->swork[29] & gGameFrameCount)) {
            func_effect_8007C120(boss->obj.pos.x, boss->obj.pos.y, boss->obj.pos.z, boss->vel.x, boss->vel.y,
                                 boss->vel.z, 0.1f, 5);
        }

        switch (boss->swork[21]) {
            case 0:
                boss->unk_04C = Animation_GetFrameCount(&D_SY_602B778) - 1;
                sp1D0 = Animation_GetFrameData(&D_SY_602B778, boss->unk_04C, sp64);
                break;

            case 1:
                boss->unk_04C = Animation_GetFrameCount(&D_SY_60265B4) - 1;
                sp1D0 = Animation_GetFrameData(&D_SY_60265B4, boss->unk_04C, sp64);
                break;

            case 2:
                boss->unk_04C = Animation_GetFrameCount(&D_SY_6029B48) - 1;
                sp1D0 = Animation_GetFrameData(&D_SY_6029B48, boss->unk_04C, sp64);
                break;

            case 3:
                boss->unk_04C = Animation_GetFrameCount(&D_SY_602B8DC) - 1;
                sp1D0 = Animation_GetFrameData(&D_SY_602B8DC, boss->unk_04C, sp64);
                break;

            case 4:
                boss->unk_04C++;
                if (boss->unk_04C >= Animation_GetFrameCount(&D_SY_6003348)) {
                    boss->unk_04C = Animation_GetFrameCount(&D_SY_6003348) - 1;
                }
                sp1D0 = Animation_GetFrameData(&D_SY_6003348, boss->unk_04C, sp64);
                break;

            case 5:
                boss->unk_04C++;
                if (boss->unk_04C >= Animation_GetFrameCount(&D_SY_602738C)) {
                    boss->unk_04C = 0;
                }
                sp1D0 = Animation_GetFrameData(&D_SY_602738C, boss->unk_04C, sp64);
                break;

            case 6:
                sp1D0 = Animation_GetFrameData(&D_SY_602738C, boss->unk_04C, sp64);
                break;

            case 7:
                if (boss->unk_04C < (Animation_GetFrameCount(&D_SY_602645C) - 1)) {
                    boss->unk_04C++;
                }
                sp1D0 = Animation_GetFrameData(&D_SY_602645C, boss->unk_04C, sp64);
                break;

            case 8:
                if (boss->unk_04C < (Animation_GetFrameCount(&D_SY_60258A0) - 1)) {
                    boss->unk_04C++;
                }
                sp1D0 = Animation_GetFrameData(&D_SY_60258A0, boss->unk_04C, sp64);
                break;

            case 9:
                boss->unk_04C++;
                if (boss->unk_04C >= Animation_GetFrameCount(&D_SY_60034C4)) {
                    boss->unk_04C = 0;
                }
                sp1D0 = Animation_GetFrameData(&D_SY_60034C4, boss->unk_04C, sp64);
                break;
        }

        boss->obj.rot.x = boss->rot_078.x;
        boss->obj.rot.y = boss->rot_078.y;
        boss->obj.rot.z = boss->rot_078.z;

        Matrix_RotateZ(gCalcMatrix, -boss->vwork[29].z * M_DTOR, MTXF_NEW);
        Matrix_RotateX(gCalcMatrix, -boss->vwork[29].x * M_DTOR, MTXF_APPLY);
        Matrix_RotateY(gCalcMatrix, -boss->vwork[29].y * M_DTOR, MTXF_APPLY);

        Matrix_RotateZ(gCalcMatrix, -boss->obj.rot.z * M_DTOR, MTXF_APPLY);
        Matrix_RotateX(gCalcMatrix, -boss->obj.rot.x * M_DTOR, MTXF_APPLY);
        Matrix_RotateY(gCalcMatrix, -boss->obj.rot.y * M_DTOR, MTXF_APPLY);

        if ((boss->health > 0) && (boss->swork[20] < 10)) {
            sp58.x = boss->fwork[18] - boss->obj.pos.x;
            sp58.y = boss->fwork[19] - boss->obj.pos.y;
            sp58.z = boss->fwork[20] - boss->obj.pos.z;
            Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp58, &sp4C);
            sp1E4 = Math_RadToDeg(Math_Atan2F(sp4C.x, sp4C.z));
            sp1E8 = Math_RadToDeg(-Math_Atan2F(sp4C.y, sqrtf(SQ(sp4C.x) + SQ(sp4C.z))));

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

            Math_SmoothStepToAngle(&boss->fwork[6], sp1E4, 0.2f, 4.0f, 0.1f);
            Math_SmoothStepToAngle(&boss->fwork[5], sp1E8, 0.2f, 4.0f, 0.1f);
            Matrix_RotateX(gCalcMatrix, -boss->fwork[5] * M_DTOR, MTXF_APPLY);
            Matrix_RotateY(gCalcMatrix, -boss->fwork[6] * M_DTOR, MTXF_APPLY);
            sp58.x = boss->fwork[18] - boss->obj.pos.x;
            sp58.y = (boss->fwork[19] - boss->obj.pos.y) + 20.0f;
            sp58.z = boss->fwork[20] - boss->obj.pos.z;
            Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp58, &sp4C);
            sp1E0 = Math_RadToDeg(Math_Atan2F(sp4C.x, sp4C.z));
            sp1DC = Math_RadToDeg(-Math_Atan2F(sp4C.y, sqrtf(SQ(sp4C.x) + SQ(sp4C.z))));

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

            Math_SmoothStepToAngle(&boss->fwork[8], sp1E0, 0.4f, 8.0f, 0.1f);
            Math_SmoothStepToAngle(&boss->fwork[7], sp1DC, 0.4f, 8.0f, 0.1f);
            sp58.x = (boss->fwork[18] - boss->obj.pos.x) + (COS_DEG(boss->obj.rot.y) * 100.0f);
            sp58.y = (boss->fwork[19] - boss->obj.pos.y) - 80.0f;
            sp58.z = boss->fwork[20] - boss->obj.pos.z;
            Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp58, &sp4C);
            sp1D8 = Math_RadToDeg(Math_Atan2F(sp4C.x, sp4C.z));
            sp1D4 = Math_RadToDeg(-Math_Atan2F(sp4C.y, sqrtf(SQ(sp4C.x) + SQ(sp4C.z))));

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

            Math_SmoothStepToAngle(&boss->fwork[15], sp1D8, 0.2f, 4.0f, 0.1f);
            Math_SmoothStepToAngle(&boss->fwork[14], sp1D4, 0.2f, 4.0f, 0.1f);
            Matrix_RotateX(gCalcMatrix, -boss->fwork[14] * M_DTOR, MTXF_APPLY);
            Matrix_RotateY(gCalcMatrix, -boss->fwork[15] * M_DTOR, MTXF_APPLY);
            sp58.x = boss->fwork[18] - boss->obj.pos.x;
            sp58.y = (boss->fwork[19] - boss->obj.pos.y) + (COS_DEG(boss->obj.rot.z) * 40.0f);
            sp58.z = (boss->fwork[20] - boss->obj.pos.z) - (COS_DEG(boss->obj.rot.y) * 60.0f);
            Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp58, &sp4C);
            sp1E4 = Math_RadToDeg(Math_Atan2F(sp4C.x, sp4C.z));
            sp1E8 = Math_RadToDeg(-Math_Atan2F(sp4C.y, sqrtf(SQ(sp4C.x) + SQ(sp4C.z))));

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

            Math_SmoothStepToAngle(&boss->fwork[17], sp1E4, 0.2f, 4.0f, 0.1f);
            Math_SmoothStepToAngle(&boss->fwork[16], sp1E8, 0.2f, 4.0f, 0.1f);
        } else {
            Math_SmoothStepToAngle(&boss->fwork[6], 0.0f, 0.2f, 4.0f, 0.1f);
            Math_SmoothStepToAngle(&boss->fwork[5], 0.0f, 0.2f, 4.0f, 0.1f);
            Math_SmoothStepToAngle(&boss->fwork[8], 0.0f, 0.4f, 8.0f, 0.1f);
            Math_SmoothStepToAngle(&boss->fwork[7], 0.0f, 0.4f, 8.0f, 0.1f);
            Math_SmoothStepToAngle(&boss->fwork[15], 0.0f, 0.4f, 8.0f, 0.1f);
            Math_SmoothStepToAngle(&boss->fwork[14], 0.0f, 0.4f, 8.0f, 0.1f);
        }
        Math_SmoothStepToF(&boss->fwork[4], 0.0f, 0.2f, 10.0f, 0.0f);
        Math_SmoothStepToF(&boss->fwork[34], 0.0f, 0.1f, 0.2f, 0.05f);
        Math_SmoothStepToF(&boss->fwork[41], 0.0f, 0.1f, 0.05f, 0.05f);
        Math_SmoothStepToF(&boss->fwork[42], 0.0f, 0.1f, 0.05f, 0.05f);
        Math_SmoothStepToVec3fArray(sp64, boss->vwork, 1, sp1D0, boss->fwork[0], 100.0f, 0.0f);

        if ((boss->dmgType != DMG_NONE) && (boss->health > 0)) {
            boss->dmgType = DMG_NONE;
            if (boss->dmgPart == 0) {
                if (boss->swork[25] == 0) {
                    boss->swork[24] = 15;
                    AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, boss->sfxSource, 4);
                } else {
                    SectorY_80198F5C(boss);
                }
            } else {
                SectorY_80198F5C(boss);
            }
        }

        if (boss->index == 0) {
            radarMark = &gRadarMarks[boss->index + 1];
            radarMark->status = 1;
            radarMark->type = 102;
            radarMark->pos.x = boss->obj.pos.x;
            radarMark->pos.y = boss->obj.pos.y;
            radarMark->pos.z = boss->obj.pos.z;
            radarMark->yRot = boss->rot_078.y + 180.0f;
        } else {
            radarMark = &gRadarMarks[boss->index + 4];
            radarMark->status = 1;
            radarMark->type = 10;
            radarMark->pos.x = boss->obj.pos.x;
            radarMark->pos.y = boss->obj.pos.y;
            radarMark->pos.z = boss->obj.pos.z;
            radarMark->yRot = boss->rot_078.y + 180.0f;
        }

        if (gBossFrameCount == 250) {
            for (i = ARRAY_COUNT(gActors) - 1; i >= 0; i--) {
                if (gActors[i].obj.status == OBJ_ACTIVE) {
                    gTeamEventActorIndex[gActors[i].iwork[12]] = i;
                }
            }
        }
        if ((gBossFrameCount == 250) && (gTeamShields[TEAM_ID_SLIPPY] != 0) && (boss->swork[34] == 0)) {
            Radio_PlayMessage(gMsg_ID_2225, RCID_SLIPPY);
        }
        if ((gBossFrameCount == 620) && (boss->swork[34] == 0)) {
            gShowBossHealth = 1;
        }
        if ((gBossFrameCount >= 350) || (boss->swork[34] != 0)) {
            if (boss->swork[34] != 0) {
                gBossHealthBar = boss->health * 1.7f;
            } else if (gBosses[0].unk_04A == 0) {
                gBossHealthBar = (gBosses[1].health + gBosses[2].health) * 1.275f;
            }
        }

        if (D_edisplay_801615D0.z > 0.0f) {
            boss->swork[30]++;
            if (boss->swork[30] > 300 && ((ABS(D_edisplay_801615D0.z) + ABS(D_edisplay_801615D0.x)) < 3500.0f) &&
                (gRadioState == 0)) {
                if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                    Radio_PlayMessage(gMsg_ID_2282, RCID_PEPPY);
                }
                boss->swork[30] = 150;
            }

            if (boss->swork[30] > 100) {
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
            boss->swork[30] = 0;
        }
    }
}

bool SectorY_8019DC4C(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* data) {
    Boss* boss = (Boss*) data;
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

bool SectorY_8019DE10(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* data) {
    Boss* boss = (Boss*) data;
    Vec3f sp38 = { 0.0f, 0.0f, 0.0f };

    if (boss->index != 0) {
        return SectorY_8019DC4C(limbIndex, dList, pos, rot, boss);
    }

    if ((boss->timer_05C % 2) != 0) {
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 32, 32, 255, 255);
    } else {
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
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
            if (boss->swork[25] == 0) {
                *dList = D_SY_6013600;
                if ((boss->swork[24] % 2) != 0) {
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 0, 255, 0, 255);
                }
            } else {
                *dList = NULL;
            }
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

void SectorY_8019E014(s32 limbIndex, Vec3f* rot, void* data) {
    Vec3f sp7C = { 40.0f, -30.0f, 0.0f };
    Vec3f sp70 = { -40.0f, -30.0f, 0.0f };
    Vec3f sp64 = { 0.0f, 0.0f, 0.0f };
    Vec3f sp58 = { 0.0f, 30.0f, -50.0f };
    Vec3f sp4C = { 6.0f, -1.0f, -53.0f };
    Vec3f sp40 = { 0.0f, 0.0f, 66.0f };
    Vec3f sp34 = { 0.0f, 30.0f, -60.0f };
    Vec3f sp28;
    Boss* boss = (Boss*) data;

    switch (limbIndex) {
        case 0:
            if (boss->index != 0) {
                Matrix_MultVec3f(gCalcMatrix, &sp58, &sp28);
            } else {
                Matrix_MultVec3f(gCalcMatrix, &sp34, &sp28);
            }
            boss->fwork[31] = sp28.x;
            boss->fwork[32] = sp28.y;
            boss->fwork[33] = sp28.z;
            break;

        case 1:
            Matrix_Push(&gCalcMatrix);
            Matrix_MultVec3f(gCalcMatrix, &sp70, &sp28);
            boss->fwork[21] = sp28.x;
            boss->fwork[22] = sp28.y;
            boss->fwork[23] = sp28.z;
            Matrix_Pop(&gCalcMatrix);
            Matrix_MultVec3f(gCalcMatrix, &sp7C, &sp28);
            boss->fwork[1] = sp28.x;
            boss->fwork[2] = sp28.y;
            boss->fwork[3] = sp28.z;
            break;

        case 3:
            if (boss->index == 0) {
                Matrix_MultVec3f(gCalcMatrix, &sp4C, &sp28);
                boss->fwork[35] = sp28.x;
                boss->fwork[36] = sp28.y;
                boss->fwork[37] = sp28.z;
            }
            break;

        case 4:
            if (boss->index == 0) {
                Matrix_MultVec3f(gCalcMatrix, &sp64, &sp28);
                boss->fwork[28] = sp28.x;
                boss->fwork[29] = sp28.y;
                boss->fwork[30] = sp28.z;
            }
            break;

        case 6:
            if (boss->index == 0) {
                Matrix_MultVec3f(gCalcMatrix, &sp40, &sp28);
                boss->fwork[38] = sp28.x;
                boss->fwork[39] = sp28.y;
                boss->fwork[40] = sp28.z;
            }
            break;

        default:
            break;
    }
}

static f32 D_i6_801A69AC[20] = { 0.3f,   0.7f,   1.3f,  0.7f,    0.3f,  0.0f,   10.0f, 20.0f,  300.0f, 100.0f,
                                 200.0f, 100.0f, 60.0f, -260.0f, 80.0f, 100.0f, 80.0f, 262.0f, 285.0f, 252.0f };

void SectorY_Boss_Draw(Boss* boss) {
    f32 sp9C;
    f32 sp98;
    f32 sp94;
    f32 sp90;
    f32 sp8C;
    f32 sp88;

    if ((boss->index != 0) || ((boss->swork[24] % 2) != 0) || ((boss->timer_05C % 2) != 0)) {
        RCP_SetupDL_30(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
    } else {
        RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
    }

    if ((boss->health > 0) || (boss->swork[36] == 0)) {
        Animation_DrawSkeleton(2, D_SY_602D140, boss->vwork, SectorY_8019DE10, SectorY_8019E014, boss, gCalcMatrix);
        if (boss->timer_054 != 0) {
            sp9C = D_i6_801A69AC[boss->timer_054];
            RCP_SetupDL_49();
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
            gDPSetEnvColor(gMasterDisp++, 255, 48, 0, 255);
            Matrix_Pop(&gGfxMatrix);
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, boss->fwork[1], boss->fwork[2], boss->fwork[3], MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, sp9C, sp9C, sp9C, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_1024AC0);
        }

        if (boss->fwork[34] != 0.0f) {
            RCP_SetupDL_49();
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
            gDPSetEnvColor(gMasterDisp++, 32, 255, 32, 255);
            Matrix_Pop(&gGfxMatrix);
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, boss->fwork[31], boss->fwork[32], boss->fwork[33], MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, boss->fwork[34], boss->fwork[34], boss->fwork[34], MTXF_APPLY);
            Matrix_RotateX(gGfxMatrix, -boss->obj.rot.x * M_DTOR, MTXF_APPLY);
            Matrix_RotateZ(gGfxMatrix, -boss->obj.rot.z * M_DTOR, MTXF_APPLY);
            sp98 = gPlayer[0].cam.eye.x - boss->obj.pos.x;
            sp94 = gPlayer[0].cam.eye.y - boss->obj.pos.y;
            sp90 = gPlayer[0].cam.eye.z - (boss->obj.pos.z + gPathProgress);
            sp8C = -Math_Atan2F(sp98, sp90);
            sp9C = sqrtf(SQ(sp90) + SQ(sp98));
            sp88 = Math_Atan2F(sp94, sp9C);
            Matrix_RotateY(gGfxMatrix, -sp8C, MTXF_APPLY);
            Matrix_RotateX(gGfxMatrix, -sp88, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_1024AC0);
        }

        if (boss->index == 0) {
            if (boss->fwork[41] != 0.0f) {
                RCP_SetupDL_49();
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
                gDPSetEnvColor(gMasterDisp++, 32, 255, 32, 255);
                Matrix_Pop(&gGfxMatrix);
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, boss->fwork[35], boss->fwork[36], boss->fwork[37], MTXF_APPLY);
                Matrix_RotateY(gGfxMatrix, boss->obj.rot.y * M_DTOR, MTXF_APPLY);
                Matrix_RotateX(gGfxMatrix, boss->obj.rot.x * M_DTOR, MTXF_APPLY);
                Matrix_RotateZ(gGfxMatrix, boss->obj.rot.z * M_DTOR, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, boss->fwork[41] * 2.0f, boss->fwork[41], boss->fwork[41] * 2.0f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_1024AC0);
            }

            if (boss->fwork[42] != 0.0f) {
                RCP_SetupDL_49();
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
                gDPSetEnvColor(gMasterDisp++, 32, 255, 32, 255);
                Matrix_Pop(&gGfxMatrix);
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, boss->fwork[38], boss->fwork[39], boss->fwork[40], MTXF_APPLY);
                Matrix_RotateY(gGfxMatrix, boss->obj.rot.y * M_DTOR, MTXF_APPLY);
                Matrix_RotateX(gGfxMatrix, boss->obj.rot.x * M_DTOR, MTXF_APPLY);
                Matrix_RotateZ(gGfxMatrix, boss->obj.rot.z * M_DTOR, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, boss->fwork[42] * 2.0f, boss->fwork[42], boss->fwork[42] * 2.0f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_1024AC0);
            }
        }

        if (boss->fwork[43] != 0.0f) {
            RCP_SetupDL_49();
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 0, 0, 0, 255);
            gDPSetEnvColor(gMasterDisp++, 0, 0, 0, 0);
            Matrix_Pop(&gGfxMatrix);
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, boss->obj.pos.x, 157.0f, boss->obj.pos.z, MTXF_APPLY);
            Matrix_RotateX(gGfxMatrix, M_PI / 2, MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, boss->fwork[43], boss->fwork[43], boss->fwork[43], MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_1024AC0);
        }

        if (boss->fwork[46] != 0.0f) {
            RCP_SetupDL_49();
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, (s32) boss->fwork[46], (s32) boss->fwork[46], 0,
                            (s32) boss->fwork[46]);
            gDPSetEnvColor(gMasterDisp++, 0, 0, 0, 0);
            Matrix_Pop(&gGfxMatrix);
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, boss->obj.pos.x + 10.0f, boss->obj.pos.y + 70.0f, boss->obj.pos.z + 60.0f,
                             MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, 0.4f, 0.2f, 0.2f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_1024AC0);
            Matrix_Translate(gGfxMatrix, -46.0f, 0, 0, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_1024AC0);
        }
    }
}

static Vec3f D_i6_801A69FC[10] = {
    { 0.0f, -80.0f, 800.0f },      { -500.0f, -100.0f, 400.0f },  { 500.0f, -140.0f, 400.0f },
    { 3250.0f, 600.0f, 3500.0f },  { -2000.0f, 400.0f, 5000.0f }, { 2500.0f, 400.0f, 5000.0f },
    { -1000.0f, 400.0f, 6000.0f }, { 250.0f, 400.0f, 2500.0f },   { -2000.0f, 0.0f, 4000.0f },
    { 2500.0f, 0.0f, 4000.0f },
};

void SectorY_8019EB80(void) {
    Actor* actor = gActors;
    s32 i;
    s32 var_s1;

    if (gHitCount >= 100) {
        var_s1 = 9;
    } else {
        var_s1 = 2;
    }
    Rand_SetSeed(1, 29100, 9786);

    for (i = 0; i <= (var_s1); i++, actor++) {
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
            actor->animFrame = 35;
            actor->rot_0F4.z = 0.0f;
        }
        if (i >= 7) {
            actor->animFrame = 36;
            actor->scale = 0.125f;
        }
        actor->iwork[11] = 1;
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
    Boss* boss = &gBosses[0];
    f32 temp_ft1;

    switch (player->csState) {
        case 0:
            gCsFrameCount = 0;
            player->aerobaticPitch = 0.0f;
            player->camRoll = 0.0f;
            player->baseSpeed = 40.0f;
            player->boostSpeed = 0.0f;
            player->wings.unk_04 = player->wings.unk_0C = player->wings.unk_08 = player->wings.unk_10 =
                player->zRotBarrelRoll = player->zRotBank = 0.0f;
            player->unk_234 = 1;
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
                player->unk_240 = 1;
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
                player->wings.modelId = 1;
            }
            break;

        case 3:
            if ((gCsFrameCount < 720) && gMsgCharIsPrinting) {
                player->wings.unk_30 = (f32) (gGameFrameCount & 2) * 5.0f;
            }

            gFillScreenAlphaTarget = 0;
            gFillScreenAlphaStep = 4;
            if (gFillScreenAlpha == 0) {
                player->unk_204 = 1;
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
                    player->state_1C8 = PLAYERSTATE_1C8_NEXT;
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
            gShowLevelClearStatusScreen = 1;
            break;

        case 1363:
            gShowLevelClearStatusScreen = 0;
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

void SectorY_8019FF00(Actor* actor) {
    Vec3f sp4C;
    Vec3f sp40;
    f32 temp1;
    f32 temp2;

    switch (actor->state) {
        case 1:
            Math_SmoothStepToF(&actor->obj.pos.x, actor->vwork[0].x, 0.02f, 2.0f, 0.0001f);
            Math_SmoothStepToF(&actor->obj.pos.y, actor->vwork[0].y, 0.02f, 2.0f, 0.0001f);
            Math_SmoothStepToF(&actor->obj.pos.z, actor->vwork[0].z, 0.02f, 2.0f, 0.0001f);
            Math_SmoothStepToF(&actor->rot_0F4.z, 0.0f, 0.02f, 0.2f, 0.0001f);
            if ((actor->animFrame != 0) && ((((s32) (actor->index % 8U) * 10) + 1030) < gCsFrameCount)) {
                actor->state = 4;
            }
            break;

        case 2:
            actor->state = 3;
            AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, actor->sfxSource, 0);
            actor->fwork[29] = 5.0f;
            /* fallthrough */
        case 3:
            actor->iwork[11] = 2;
            actor->fwork[0] += 2.0f;
            actor->rot_0F4.x += 0.1f;
            break;

        case 5:
            Math_SmoothStepToF(&actor->rot_0F4.x, 0.0f, 0.1f, 5.0f, 0.0f);
            temp1 = actor->obj.pos.x - gBosses[actor->timer_04C].obj.pos.x;
            temp2 = actor->obj.pos.z - gBosses[actor->timer_04C].obj.pos.z;
            Math_SmoothStepToAngle(&actor->rot_0F4.z,
                                   Math_SmoothStepToAngle(&actor->rot_0F4.y, Math_RadToDeg(Math_Atan2F(temp1, temp2)),
                                                          0.5f, 2.0f, 0.0001f) *
                                       30.0f,
                                   0.1f, 5.0f, 0.0001f);
            break;

        case 7:
            actor->rot_0F4.y = gPlayer[0].rot.y;
            actor->rot_0F4.z = gPlayer[0].rot.z;
            Math_SmoothStepToF(&actor->obj.pos.y, 50.0f, 0.1f, 1.0f, 0.0f);
            if (gPlayer[0].rot.y == 0.0f) {
                Math_SmoothStepToF(&actor->obj.pos.x, 1300.0f, 1.0f, 2.0f, 0.0f);
            } else {
                if (gCsFrameCount == 540) {
                    actor->fwork[29] = 3.8f;
                    AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, actor->sfxSource, 0);
                }
                Math_SmoothStepToF(&actor->obj.pos.x, 230.0f, 1.0f, 13.0f, 0.0f);
            }
            break;

        case 8:
            Math_SmoothStepToF(&actor->obj.pos.y, -100.0f, 0.1f, 1.0f, 0.0f);
            if (gCsFrameCount >= 535) {
                if (gCsFrameCount == 535) {
                    actor->fwork[29] = 3.8f;
                    AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, actor->sfxSource, 0);
                }
                Math_SmoothStepToF(&actor->obj.pos.x, -1000.0f, 1.0f, 20.0f, 0.0f);
                Math_SmoothStepToAngle(&actor->rot_0F4.z, 45.0f, 1.0f, 4.0f, 0.0f);
            } else {
                actor->rot_0F4.y = gPlayer[0].rot.y;
                actor->rot_0F4.z = gPlayer[0].rot.z;
                Math_SmoothStepToF(&actor->obj.pos.x, -230.0f, 1.0f, 13.0f, 0.0f);
            }
            break;

        case 9:
            Math_SmoothStepToF(&actor->obj.pos.y, -50.0f, 0.1f, 1.0f, 0.0f);
            if (gCsFrameCount >= 525) {
                if (gCsFrameCount == 525) {
                    actor->fwork[29] = 3.8f;
                    AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, actor->sfxSource, 0);
                }
                Math_SmoothStepToF(&actor->obj.pos.x, 1500.0f, 1.0f, 20.0f, 0.0f);
                Math_SmoothStepToAngle(&actor->rot_0F4.z, 315.0f, 1.0f, 2.0f, 0.0f);
            } else {
                actor->rot_0F4.y = gPlayer[0].rot.y;
                actor->rot_0F4.z = gPlayer[0].rot.z;
                Math_SmoothStepToF(&actor->obj.pos.x, 150.0f, 1.0f, 13.0f, 0.0f);
            }
            break;
    }

    if (actor->state != 6) {
        Matrix_RotateY(gCalcMatrix, (actor->rot_0F4.y + 180.0f) * M_DTOR, MTXF_NEW);
        Matrix_RotateX(gCalcMatrix, -(actor->rot_0F4.x * M_DTOR), MTXF_APPLY);
        sp4C.x = 0.0f;
        sp4C.y = 0.0f;
        sp4C.z = actor->fwork[0];
        Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp4C, &sp40);
        actor->vel.x = sp40.x;
        actor->vel.y = sp40.y;
        actor->vel.z = sp40.z;
        actor->obj.rot.x = -actor->rot_0F4.x;
        actor->obj.rot.y = actor->rot_0F4.y + 180.0f;
        actor->obj.rot.z = -actor->rot_0F4.z;
    }
}

static Vec3f D_i6_801A6A74[10] = { { -10100.0f, -300.0f, -600.0f },  { -10300.0f, 1200.0f, -1070.0f },
                                   { -10500.0f, 300.0f, 900.0f },    { 9000.0f, 0.0f, 1500.0f },
                                   { 5000.0f, -100.0f, -100.0f },    { 1150.0f, -1100.0f, -7500.0f },
                                   { -200.0f, -2400.0f, -12650.0f }, { 0.0f, 4000.0f, -600.0f },
                                   { -10800.0f, 900.0f, -600.0f },   { -2750.0f, 900.0f, -9150.0f } };

void SectorY_801A0510(Actor* actor, s32 arg1) {

    Actor_Initialize(actor);
    actor->obj.status = OBJ_ACTIVE;
    actor->obj.id = OBJ_ACTOR_CUTSCENE;
    actor->obj.pos.x = D_i6_801A6A74[arg1].x;
    actor->obj.pos.y = D_i6_801A6A74[arg1].y;
    actor->obj.pos.z = D_i6_801A6A74[arg1].z;

    switch (arg1) {
        case 0:
        case 1:
        case 2:
        case 8:
            actor->animFrame = 38;
            actor->obj.rot.y = 90.0f;
            Object_SetInfo(&actor->info, actor->obj.id);
            break;

        case 3:
            actor->animFrame = 36;
            actor->vel.z = -5.0f;
            actor->scale = 1.0f;
            actor->obj.rot.y = 180.0f;
            Object_SetInfo(&actor->info, actor->obj.id);
            break;

        case 4:
            actor->animFrame = 37;
            actor->obj.rot.y = 90.0f;
            Object_SetInfo(&actor->info, actor->obj.id);
            break;

        case 5:
        case 9:
            actor->animFrame = 39;
            actor->obj.rot.y = 180.0f;
            Object_SetInfo(&actor->info, actor->obj.id);
            break;

        case 6:
            actor->animFrame = 36;
            actor->obj.rot.y = 180.0f;
            actor->scale = 1.0f;
            Object_SetInfo(&actor->info, actor->obj.id);
            break;

        case 7:
            actor->animFrame = 40;
            Object_SetInfo(&actor->info, actor->obj.id);
            break;

        default:
            break;
    }
}

static Vec3f D_i6_801A6AEC[5] = {
    { 100.0f, 50.0f, -200.0f }, { 100.0f, -100.0f, 200.0f }, { 200.0f, -100.0f, 0.0f },
    { 0.0f, 345.0f, 350.0f },   { 90.0f, 87.0f, 93.0f },
};

void SectorY_801A06A4(Actor* actor, s32 arg1) {

    if (gTeamShields[1 + arg1] > 0) {
        Actor_Initialize(actor);
        actor->obj.status = OBJ_ACTIVE;
        actor->obj.id = OBJ_ACTOR_CUTSCENE;
        actor->obj.pos.x = gPlayer[0].pos.x + D_i6_801A6AEC[arg1].x;
        actor->obj.pos.y = gPlayer[0].pos.y + D_i6_801A6AEC[arg1].y;
        actor->obj.pos.z = gPlayer[0].pos.z + D_i6_801A6AEC[arg1].z;
        actor->fwork[0] = gPlayer[0].baseSpeed;
        actor->rot_0F4.y = gPlayer[0].rot.y;
        actor->rot_0F4.z = gPlayer[0].rot.z;
        actor->state = arg1 + 7;
        actor->iwork[11] = 1;
        Object_SetInfo(&actor->info, actor->obj.id);
        AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, actor->sfxSource, 4);
        AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, actor->sfxSource, 0);
    }
}

void SectorY_801A07FC(Actor* actor0, Actor* actor1) {
    Vec3f sp3C;
    Vec3f sp30;

    Actor_Initialize(actor1);
    actor1->obj.status = OBJ_ACTIVE;
    actor1->obj.id = OBJ_ACTOR_CUTSCENE;
    actor0->fwork[6] = 1.8f;
    sp3C.x = -40.0f;
    sp3C.y = 0.0f;
    sp3C.z = 80.0f;
    Matrix_RotateY(gCalcMatrix, actor0->obj.rot.y * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, actor0->obj.rot.x * M_DTOR, MTXF_APPLY);
    Matrix_RotateZ(gCalcMatrix, actor0->obj.rot.z * M_DTOR, MTXF_APPLY);
    Matrix_MultVec3f(gCalcMatrix, &sp3C, &sp30);
    actor1->obj.pos.x = actor0->obj.pos.x + sp30.x;
    actor1->obj.pos.y = actor0->obj.pos.y + sp30.y;
    actor1->obj.pos.z = actor0->obj.pos.z + sp30.z;
    Object_SetInfo(&actor1->info, actor1->obj.id);
    Matrix_RotateY(gCalcMatrix, actor0->obj.rot.y * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, actor0->obj.rot.x * M_DTOR, MTXF_APPLY);
    sp3C.x = 0.0f;
    sp3C.y = 0.0f;
    sp3C.z = 160.0f;
    Matrix_MultVec3f(gCalcMatrix, &sp3C, &sp30);
    actor1->timer_0BC = 100;
    actor1->vel.x = sp30.x;
    actor1->vel.y = sp30.y;
    actor1->vel.z = sp30.z;
    actor1->obj.rot.x = actor0->obj.rot.x;
    actor1->obj.rot.y = actor0->obj.rot.y;
    actor1->animFrame = 42;
    AUDIO_PLAY_SFX(NA_SE_EN_MS_SHOT_S, actor1->sfxSource, 4);
}

void SectorY_801A0A08(Actor* actor, f32 xPos, f32 yPos, f32 zPos, f32 arg4) {
    Actor_Initialize(actor);
    actor->obj.status = OBJ_ACTIVE;
    actor->obj.id = OBJ_ACTOR_CUTSCENE;
    actor->fwork[0] = arg4;
    actor->obj.pos.x = xPos;
    actor->obj.pos.y = yPos;
    actor->obj.pos.z = zPos;
    Object_SetInfo(&actor->info, actor->obj.id);
    actor->timer_0BC = 35;
    actor->iwork[0] = 255;
    actor->animFrame = 43;
    AUDIO_PLAY_SFX(NA_SE_EN_MS_SHOT_S, actor->sfxSource, 4);
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
                spB0 = (((gGameFrameCount & 12) >> 2) + 4);
                for (i = 10; i < ARRAY_COUNT(gActors); i++) {
                    if (gActors[i].obj.status == OBJ_FREE) {
                        SectorY_801A07FC(&gActors[spB0], &gActors[i]);
                        break;
                    }
                }
            }
            if (((gGameFrameCount % 4) == 0)) {
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
                func_effect_8007C120(gActors[8].obj.pos.x + sp98.x, gActors[8].obj.pos.y + sp98.y,
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
                    func_effect_8007BFFC(gActors[11].obj.pos.x, gActors[11].obj.pos.y, gActors[11].obj.pos.z,
                                         gActors[11].vel.x, gActors[11].vel.y, gActors[11].vel.z, 8, 10);
                    func_effect_8007B344(gActors[11].obj.pos.x, gActors[11].obj.pos.y, gActors[11].obj.pos.z, 8, 5);
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
                        SectorY_SpawnDebris(gActors[11].obj.pos.x, gActors[11].obj.pos.y, gActors[11].obj.pos.z,
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
                player->state_1C8 = PLAYERSTATE_1C8_ACTIVE;
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

void SectorY_SetupDebris(Actor* actor, f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, s32 state) {
    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_DEBRIS;
    actor->state = state;
    actor->obj.pos.x = xPos;
    actor->obj.pos.y = yPos;
    actor->obj.pos.z = zPos;
    actor->vel.x = xVel;
    actor->vel.y = yVel;
    actor->vel.z = zVel;
    actor->scale = 2.5f;
    actor->timer_0BC = RAND_INT(15.0f) + 15.0f;
    Object_SetInfo(&actor->info, actor->obj.id);
}

void SectorY_SpawnDebris(f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, s32 state) {
    s32 i;

    for (i = ARRAY_COUNT(gActors) - 1; i >= 0; i--) {
        if (gActors[i].obj.status == OBJ_FREE) {
            SectorY_SetupDebris(&gActors[i], xPos, yPos, zPos, xVel, yVel, zVel, state);
            break;
        }
    }
}

void SectorY_Actor204_Update(Actor204* this) {
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

    if ((this->unk_048 != 0) && (this->unk_046 != 3)) {
        switch (this->unk_048) {
            case 1:
                this->unk_046 = 1;
                this->timer_0BE = 50;
                this->iwork[19] = 0;
                break;

            case 2:
                this->unk_046 = 1;
                this->timer_0BE = 20;
                this->iwork[19] = 0;
                break;

            case 3:
                this->unk_046 = 2;
                this->animFrame = 0;
                break;

            case 4:
                this->unk_046 = 0;
                this->animFrame = 0;
                break;

            case 8:
                this->unk_046 = 1;
                this->timer_0BE = 50;
                this->iwork[19] = 1;
                break;

            case 9:
                this->unk_046 = 1;
                this->timer_0BE = 20;
                this->iwork[19] = 1;
                break;

            case 10:
                this->unk_046 = 1;
                this->timer_0BE = 50;
                this->iwork[19] = -1;
                break;

            case 11:
                this->unk_046 = 1;
                this->timer_0BE = 20;
                this->iwork[19] = -1;
                break;

            case 6:
                this->unk_046 = 4;
                this->animFrame = 0;
                break;

            case 5:
                this->unk_046 = 5;
                this->animFrame = Animation_GetFrameCount(&D_SY_602B778) - 1;
                break;

            case 7:
                this->unk_046 = 6;
                this->animFrame = Animation_GetFrameCount(&D_SY_602B778) - 1;
                break;
        }
        this->unk_048 = 0;
        this->fwork[15] = 0.0f;
    }

    switch (this->unk_046) {
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
                    func_effect_8007F11C(OBJ_EFFECT_354, this->fwork[16], this->fwork[17], this->fwork[18], 100.0f);
                    gPlayer[0].pos.x = sp1E4;
                    gPlayer[0].pos.y = sp1E0;
                    AUDIO_PLAY_SFX(NA_SE_EN_MS_SHOT_S, this->sfxSource, 4);
                }
                this->unk_048 = 0;
            }

            if (this->timer_0BE == 0) {
                this->animFrame = 0;
                this->unk_046 = 0;
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
                this->unk_046 = 0;
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
                if (this->unk_046 == 5) {
                    this->iwork[17] = 1;
                } else {
                    this->iwork[17] = 2;
                }
                this->unk_046 = 0;
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
                func_effect_8007BFFC(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, this->vel.x, this->vel.y,
                                     this->vel.z, 8.0f, 10);
                func_effect_8007B344(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 8.0f, 5);
                AUDIO_PLAY_SFX(NA_SE_EN_MS_EXPLOSION_S, this->sfxSource, 4);
            }

            if (this->timer_0BE == 0) {
                Object_Kill(&this->obj, this->sfxSource);
                Actor_Despawn(this);
                for (i = 10; i < 24; i++) {
                    SectorY_SpawnDebris(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, RAND_FLOAT_CENTERED(50.0f),
                                        RAND_FLOAT_CENTERED(50.0f), this->vel.z + RAND_FLOAT_CENTERED(50.0f), i);
                }
            }
            break;
    }

    if ((this->unk_046 == 1) || (this->unk_046 == 2)) {
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

    if ((this->unk_046 == 6) || (this->unk_046 == 5)) {
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

    this->info.hitbox = LOAD_ASSET(D_SY_603405C);
    if (this->unk_046 == 1) {
        this->info.hitbox = LOAD_ASSET(D_SY_603421C);
    }

    i = this->iwork[17];
    if (i != 0) {
        if (i == 1) {
            this->info.hitbox = LOAD_ASSET(D_SY_6034124);
        } else if (i == 2) {
            this->info.hitbox = LOAD_ASSET(D_SY_60341A8);
        }
    }
    if (this->unk_046 == 2) {
        this->info.hitbox = LOAD_ASSET(D_SY_60340C0);
    }

    if ((this->dmgType != DMG_NONE) && (this->unk_046 != 3)) {

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
            func_effect_8007C120(this->hitPos.x, this->hitPos.y, this->hitPos.z, this->vel.x, this->vel.y, this->vel.z,
                                 0.1f, 10);
            this->health -= this->damage;

            if (this->health <= 0) {
                this->unk_046 = 3;
                this->unk_048 = 0;
                this->animFrame = 0;
                this->timer_0BE = 50;
                this->fwork[15] = 0.0f;
            }
        }
    }
}

static s32 D_i6_801A6B28[3] = { 255, 150, 150 };
static s32 D_i6_801A6B34[3] = { 150, 255, 150 };
static s32 D_i6_801A6B40[6] = { 150, 150, 255 };

bool SectorY_801A4A18(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* data) {
    Actor* actor = (Actor*) data;

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
        if (actor->eventType == 48) {
            *dList = D_SY_6014BD0;
        }
    }
    if (limbIndex == 18) {
        rot->x += actor->fwork[21];
    }

    return false;
}

void SectorY_801A4C34(s32 limbIndex, Vec3f* rot, void* data) {
    Vec3f sp2C = { 40.0f, -30.0f, 0.0f };
    Vec3f sp20;
    Actor* actor = (Actor*) data;

    if (limbIndex == 1) {
        Matrix_MultVec3f(gCalcMatrix, &sp2C, &sp20);
        actor->fwork[16] = sp20.x;
        actor->fwork[17] = sp20.y;
        actor->fwork[18] = sp20.z;
    }
}

static f32 D_i6_801A6B64[5] = {
    0.3f, 0.7f, 1.3f, 0.7f, 0.3f,
};

void SectorY_Actor204_Draw(Actor204* this) {
    f32 scale;

    RCP_SetupDL_30(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
    Animation_DrawSkeleton(2, D_SY_602D140, this->vwork, SectorY_801A4A18, SectorY_801A4C34, this, gCalcMatrix);

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

        gSPDisplayList(gMasterDisp++, D_1024AC0);
    }
}

void SectorY_801A4E44(Scenery* scenery) {
    Vec3f sp3C;
    Vec3f sp30;

    if (scenery->state == 0) {
        AUDIO_PLAY_SFX(NA_SE_OB_BROKEN_SPARK_L, scenery->sfxSource, 4);
        scenery->state++;
    }
    if (((gGameFrameCount % 4) == 0)) {
        Matrix_RotateY(gCalcMatrix, scenery->obj.rot.y * M_DTOR, MTXF_NEW);
        Matrix_RotateX(gCalcMatrix, scenery->obj.rot.x * M_DTOR, MTXF_APPLY);
        Matrix_RotateZ(gCalcMatrix, scenery->obj.rot.z * M_DTOR, MTXF_APPLY);
        sp3C.x = RAND_FLOAT_CENTERED(100.0f) + 500.0f;
        sp3C.y = RAND_FLOAT_CENTERED(900.0f) + -150.0f;
        sp3C.z = 90.0f - RAND_FLOAT(50.0f);
        Matrix_MultVec3f(gCalcMatrix, &sp3C, &sp30);
        func_effect_8007C120(scenery->obj.pos.x + sp30.x, scenery->obj.pos.y + sp30.y, scenery->obj.pos.z + sp30.z,
                             scenery->effectVel.x, scenery->effectVel.y, scenery->effectVel.z, 0.2f, 5);
        sp3C.x = RAND_FLOAT_CENTERED(100.0f) + -500.0f;
        sp3C.y = RAND_FLOAT_CENTERED(900.0f);
        sp3C.z = 80.0f - RAND_FLOAT(50.0f);
        Matrix_MultVec3f(gCalcMatrix, &sp3C, &sp30);
        func_effect_8007C120(scenery->obj.pos.x + sp30.x, scenery->obj.pos.y + sp30.y, scenery->obj.pos.z + sp30.z,
                             scenery->effectVel.x, scenery->effectVel.y, scenery->effectVel.z, 0.2f, 5);
        sp3C.x = RAND_FLOAT_CENTERED(100.0f) + 500.0f;
        sp3C.y = RAND_FLOAT_CENTERED(900.0f) + -50.0f;
        sp3C.z = 1900.0f - RAND_FLOAT(50.0f);
        Matrix_MultVec3f(gCalcMatrix, &sp3C, &sp30);
        func_effect_8007C120(scenery->obj.pos.x + sp30.x, scenery->obj.pos.y + sp30.y, scenery->obj.pos.z + sp30.z,
                             scenery->effectVel.x, scenery->effectVel.y, scenery->effectVel.z, 0.2f, 5);
        sp3C.x = RAND_FLOAT_CENTERED(100.0f) + -1000.0f;
        sp3C.y = RAND_FLOAT_CENTERED(900.0f) + -250.0f;
        sp3C.z = 1100.0f - RAND_FLOAT(50.0f);
        Matrix_MultVec3f(gCalcMatrix, &sp3C, &sp30);
        func_effect_8007C120(scenery->obj.pos.x + sp30.x, scenery->obj.pos.y + sp30.y, scenery->obj.pos.z + sp30.z,
                             scenery->effectVel.x, scenery->effectVel.y, scenery->effectVel.z, 0.2f, 5);
    }
}

void SectorY_801A52B8(Scenery* scenery) {
    Vec3f sp44;
    Vec3f sp38;

    if (scenery->state == 0) {
        AUDIO_PLAY_SFX(NA_SE_OB_BROKEN_SPARK_L, scenery->sfxSource, 4);
        scenery->state++;
    }

    if (((gGameFrameCount % 4) == 0)) {
        Matrix_RotateY(gCalcMatrix, scenery->obj.rot.y * M_DTOR, MTXF_NEW);
        Matrix_RotateX(gCalcMatrix, scenery->obj.rot.x * M_DTOR, MTXF_APPLY);
        Matrix_RotateZ(gCalcMatrix, scenery->obj.rot.z * M_DTOR, MTXF_APPLY);
        sp44.x = RAND_FLOAT_CENTERED(100.0f) + -800.0f;
        sp44.y = RAND_FLOAT_CENTERED(300.0f) + -100.0f;
        sp44.z = RAND_FLOAT_CENTERED(5000.0f) + 500.0f;
        Matrix_MultVec3f(gCalcMatrix, &sp44, &sp38);
        func_effect_8007C120(scenery->obj.pos.x + sp38.x, scenery->obj.pos.y + sp38.y, scenery->obj.pos.z + sp38.z,
                             scenery->effectVel.x, scenery->effectVel.y, scenery->effectVel.z, 0.3f, 5);
        sp44.x = RAND_FLOAT_CENTERED(100.0f) + -600.0f;
        sp44.y = RAND_FLOAT_CENTERED(250.0f) + 300.0f;
        sp44.z = RAND_FLOAT_CENTERED(1500.0f) + -1650.0f;
        Matrix_MultVec3f(gCalcMatrix, &sp44, &sp38);
        func_effect_8007C120(scenery->obj.pos.x + sp38.x, scenery->obj.pos.y + sp38.y, scenery->obj.pos.z + sp38.z,
                             scenery->effectVel.x, scenery->effectVel.y, scenery->effectVel.z, 0.2f, 5);
    }
}
