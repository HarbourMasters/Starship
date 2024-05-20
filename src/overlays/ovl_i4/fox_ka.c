/*
 * File: fox_ka.c
 * System: Katina
 * Description: Level: Katina
 */

#include "global.h"
#include "assets/ast_katina.h"

Vec3f D_i4_8019F0F0[] = { { 7000.0f, 500.0f, -50 }, { 7700.0f, 550.0f, -50.0f }, { 6000.0f, 300.0f, 1950.0f } };
Vec3f D_i4_8019F114[] = { { -30.0f, 0.0f, 0.0f }, { -30.0f, 0.0f, 0.0f }, { 0.0f, 5.0f, -40.0f } };
Vec3f D_i4_8019F138[] = { { 0.0f, -135.0f, -5.0f }, { 0.0f, -135.0f, 15.0f }, { -10.0f, 135.0f, 0.0f } };
s32 D_i4_8019F15C[] = { 33, 34, 33 };
Vec3f D_i4_8019F168[] = { { 700.0f, 50.0f, -700.0f }, { -500.0f, 150.0f, -500 }, { 100.0f, 100.0f, -1200.0f } };
f32 D_i4_8019F18C[] = { 200.0f, 160.0f, 185.0f };
u8 D_i4_8019F198[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
s32 sEnemySpawnTargets[] = {
    -1,
    AI360_10 + 1,
    -1,
    AI360_10 + 3,
    -1,
    AI360_10 + 5,
    -1,
    AI360_10 + 7,
    -1,
    AI360_10 + 9,
    AI360_10,
    AI360_10 + 1,
    AI360_10 + 2,
    AI360_10 + 3,
    AI360_10 + 4,
    AI360_10 + 5,
    AI360_10 + 6,
    AI360_10 + 7,
    AI360_10 + 8,
    AI360_10 + 9,
    AI360_10,
    AI360_10 + 1,
    AI360_10 + 2,
    AI360_10 + 3,
    AI360_10 + 4,
    AI360_10 + 5,
    AI360_10 + 6,
    AI360_10 + 7,
    AI360_10 + 8,
    AI360_10 + 9,
    AI360_10,
    AI360_10 + 1,
    AI360_10 + 2,
    AI360_10 + 3,
    AI360_10 + 4,
    AI360_SLIPPY,
    AI360_SLIPPY,
    4,
    3,
    2,
};
f32 D_i4_8019F260[] = { 377.0f, -600.0f, 700.0f };
f32 D_i4_8019F26C[] = { 50.0f, -50.0f, -100.0f };
f32 D_i4_8019F278[] = { 100.0f, 500.0f, 260.0f };
f32 D_i4_8019F284[] = { -600.0f, 60.0f, 120.0f };
f32 D_i4_8019F290[] = { 60.0f, 262.0f, 285.0f };
f32 D_i4_8019F29C[] = { 252.0f, -1000.0f, 0.0f, 1000.0f };
f32 D_i4_8019F2AC[] = { 0.0f, 1000.0f, 1000.0f, 1000.0f };
f32 D_i4_8019F2BC[] = { 1000.0f, 0.0f, 1000.0, -500.0f };
f32 D_i4_8019F2CC[] = { -1000.0f, 180.0f, 180.0f, 180.0f };
f32 D_i4_8019F2DC[] = { 180.0f, 0.0f, 0.0f, 0.0f, 0.0f };
s32 D_i4_8019F2F0[] = {
    100000, 100000, 100000, 100000, 1, 16, 15, 8, 3, 7, 12, 2, 5, 14, 9, 4, 10, 13, 6, 11,
};
Vec3f sCsLevelCompleteActorPos[] = {
    { 500.0f, -100.0f, 500.0f },    { -500.0f, -70.0f, 500.0f },    { 0.0f, -140.0f, 1000.0f },
    { -500.0f, -200.0f, 1000.0f },  { 1000.0f, -230.0f, 1500.0f },  { -1500.0f, -300.0f, 2300.0f },
    { -500.0f, -250.0f, 2000.0f },  { 500.0f, -300.0f, 2200.0f },   { 1500.0f, -280.0f, 2100.0f },
    { -2000.0f, -400.0f, 2600.0f }, { -1000.0f, -450.0f, 2800.0f }, { 0.0f, -350.0f, 2700.0f },
    { 1000.0f, -380.0f, 2600.0f },  { 2000.0f, -420.0f, 2500.0f },  { -2500.0f, -500.0f, 1100.0f },
    { -1500.0f, -600.0f, 1200.0f }, { -500.0f, -650.0f, 1100.0f },  { 500.0f, -550.0f, 1300.0f },
    { 1500.0f, -750.0f, 1200.0f },  { 2500.0f, -600.0f, 1000.0f }
};
u8 D_i4_8019F430[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
s32 D_i4_8019F444[] = {
    20, -1, 22, -1, 24, -1, 26, -1, 28, -1, -1, 11, -1, 13, -1, 15, -1, 17, -1, 19,
};
s32 D_i4_801A0540;
f32 D_i4_801A0544;
f32 D_i4_801A0548;
f32 D_i4_801A054C;
f32 D_i4_801A0550;
f32 D_i4_801A0554;
f32 D_i4_801A0558;

void Katina_EnemyDraw(ActorAllRange*);
void Katina_EnemyUpdate(ActorAllRange*);
void Katina_801981F8(Actor*);

typedef enum KaActorIwork {
    /* 0 */ KA_ACTOR_IWORK_0,
    /* 1 */ KA_ACTOR_IWORK_1,
    /* 2 */ KA_ACTOR_IWORK_2,
    /* 4 */ KA_ACTOR_IWORK_4 = 4,
    /* 5 */ KA_ACTOR_IWORK_5,
    /* 8 */ KA_ACTOR_IWORK_8 = 8,
    /* 11 */ KA_ACTOR_IWORK_11 = 11,
    /* 23 */ KA_ACTOR_LOW_POLY = 23,
} KaActorIwork;

typedef enum KaActorFwork {
    /* 0 */ KA_ACTOR_FWORK_0,
    /* 1 */ KA_ACTOR_FWORK_1,
    /* 2 */ KA_ACTOR_FWORK_2,
    /* 3 */ KA_ACTOR_FWORK_3,
    /* 4 */ KA_ACTOR_FWORK_4,
    /* 5 */ KA_ACTOR_FWORK_5,
    /* 6 */ KA_ACTOR_FWORK_6,
    /* 7 */ KA_ACTOR_FWORK_7,
    /* 8 */ KA_ACTOR_FWORK_8,
    /* 9 */ KA_ACTOR_FWORK_9,
    /* 10 */ KA_ACTOR_FWORK_10,
    /* 11 */ KA_ACTOR_FWORK_11,
    /* 12 */ KA_ACTOR_FWORK_12,
    /* 13 */ KA_ACTOR_FWORK_13,
    /* 14 */ KA_ACTOR_FWORK_14,
    /* 19 */ KA_ACTOR_FWORK_19 = 19,
    /* 20 */ KA_ACTOR_FWORK_20,
    /* 21 */ KA_ACTOR_FWORK_21,
    /* 29 */ KA_ACTOR_FWORK_29 = 29,
} KaActorFwork;

typedef enum KaBosses {
    /* 0 */ KA_BOSS_BASE,
    /* 1 */ KA_BOSS_SAUCERER
} KaBosses;

typedef enum KaBossSwork {
    /* 0 */ BOSS_HATCH_1_FLASH_TIMER,
    /* 1 */ BOSS_HATCH_2_FLASH_TIMER,
    /* 2 */ BOSS_HATCH_3_FLASH_TIMER,
    /* 3 */ BOSS_HATCH_4_FLASH_TIMER,
    /* 4 */ BOSS_CORE_FLASH_TIMER,
    /* 5 */ BOSS_SWORK_5,
    /* 6 */ BOSS_SWORK_6,
    /* 7 */ BOSS_SWORK_7,
    /* 8 */ BOSS_SWORK_8,
    /* 9 */ BOSS_SWORK_9,
    /* 10 */ BOSS_HATCH_1_HP,
    /* 11 */ BOSS_HATCH_2_HP,
    /* 12 */ BOSS_HATCH_3_HP,
    /* 13 */ BOSS_HATCH_4_HP,
    /* 14 */ BOSS_CORE_HP,
    /* 15 */ BOSS_HATCH_DESTROY_COUNT,
    /* 16 */ BOSS_CORE_TIMER
} KaBossSwork;

typedef enum KaBossFwork {
    /* 0 */ BOSS_HATCH_1_ANGLE,
    /* 1 */ BOSS_HATCH_2_ANGLE,
    /* 2 */ BOSS_HATCH_3_ANGLE,
    /* 3 */ BOSS_HATCH_4_ANGLE,
    /* 4 */ BOSS_CORE_LEVEL,
    /* 5 */ BOSS_HATCH_1_ANGLE_TARGET,
    /* 6 */ BOSS_HATCH_2_ANGLE_TARGET,
    /* 7 */ BOSS_HATCH_3_ANGLE_TARGET,
    /* 8 */ BOSS_HATCH_4_ANGLE_TARGET,
    /* 9 */ BOSS_CORE_TARGET_LEVEL,
    /* 10 */ BOSS_MOVEMENT_SPEED,
    /* 11 */ BOSS_Y_ROT_SPEED,
    /* 12 */ BOSS_Y_ROT_SPEED_TARGET,
    /* 13 */ BOSS_FWORK_13,
    /* 14 */ BOSS_LASER_LIGHT_SCALE,
    /* 15 */ BOSS_LASER_LENGTH
} KaBossFwork;

typedef enum KaBaseStates {
    /* 0 */ KA_BOSS_BASE_IDLE,
    /* 1 */ KA_BASE_STATE_1,
    /* 2 */ KA_BASE_STATE_2
} KaBaseStates;

typedef enum KaSaucererStates {
    /* 0 */ SAUCERER_STAND_BY,
    /* 1 */ SAUCERER_CS_APPROACH_BASE,
    /* 2 */ SAUCERER_CS_CLOSE_UP,
    /* 3 */ SAUCERER_CS_OPEN_HATCHES_START,
    /* 4 */ SAUCERER_CS_OPEN_HATCHES_END,
    /* 5 */ SAUCERER_CS_SEND_ENEMIES,
    /* 6 */ SAUCERER_OPEN_HATCHES,
    /* 7 */ SAUCERER_SEND_ENEMIES,
    /* 10 */ SAUCERER_LOWER_CORE = 10,
    /* 11 */ SAUCERER_LASER_CHARGE_START,
    /* 12 */ SAUCERER_CS_LASER_CHARGE_END,
    /* 15 */ SAUCERER_CS_ROTATE = 15,
    /* 16 */ SAUCERER_CS_LASER_FIRE_START,
    /* 17 */ SAUCERER_CS_LASER_FIRE_END,
    /* 18 */ SAUCERER_CS_LASER_HIT,
    /* 20 */ SAUCERER_DEFEAT = 20,
    /* 21 */ SAUCERER_CS_FALL_TO_GROUND,
} KaSaucererStates;

// Particle effects visible while the Saucerer is charging it's laser
void Katina_LaserEnergyParticlesSetup(Effect358* this, f32 x, f32 y, f32 z, f32 x2, f32 y2, f32 z2) {
    f32 yRot;
    f32 xRot;
    f32 distXZ;
    Vec3f src;
    Vec3f dest;

    Effect_Initialize(this);
    this->obj.status = OBJ_ACTIVE;
    this->obj.id = OBJ_EFFECT_358;

    this->obj.pos.x = x;
    this->obj.pos.y = y;
    this->obj.pos.z = z;

    xRot = Math_Atan2F(x2 - x, z2 - z);
    distXZ = sqrtf(SQ(x2 - x) + SQ(z2 - z));
    yRot = -Math_Atan2F(y2 - y, distXZ);

    Matrix_RotateY(gCalcMatrix, xRot, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, yRot, MTXF_APPLY);

    src.x = 0.0f;
    src.y = 0.0f;
    src.z = 30.0f;

    Matrix_MultVec3f(gCalcMatrix, &src, &dest);

    this->unk_60.x = dest.x;
    this->unk_60.y = dest.y;
    this->unk_60.z = dest.z;

    Object_SetInfo(&this->info, this->obj.id);
}

// Particle effects visible while the Saucerer is charging it's laser
void Katina_LaserEnergyParticlesSpawn(f32 x, f32 y, f32 z, f32 x2, f32 y2, f32 z2) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Katina_LaserEnergyParticlesSetup(&gEffects[i], x, y, z, x2, y2, z2);
            break;
        }
    }
}

void Katina_LaserEnergyParticlesUpdate(Effect358* this) {
    this->vel.x = this->unk_60.x * this->scale1;
    this->vel.y = this->unk_60.y * this->scale1;
    this->vel.z = this->unk_60.z * this->scale1;

    Math_SmoothStepToF(&this->scale1, 1.0f, 1.0f, 0.02f, 0.0f);

    if (this->unk_44 < 253) {
        this->unk_44 += 3;
    }

    if ((fabsf(this->obj.pos.x - gBosses[KA_BOSS_SAUCERER].obj.pos.x) <= 30.0f) &&
        (fabsf(this->obj.pos.z - gBosses[KA_BOSS_SAUCERER].obj.pos.z) <= 30.0f)) {
        Object_Kill(&this->obj, this->sfxSource);
    }
}

void Katina_LaserEnergyParticlesDraw(Effect358* this) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_67);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 48, 48, 255, this->unk_44);
    gDPSetEnvColor(gMasterDisp++, 0, 0, 0, this->unk_44);

    Matrix_Scale(gGfxMatrix, 0.4f, 0.4f, 0.4f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);

    gSPDisplayList(gMasterDisp++, D_1024AC0);

    RCP_SetupDL(&gMasterDisp, SETUPDL_64);
}

// Explosion/Fire effect with smoke.
void Katina_FireSmokeEffectSetup(EffectFireSmoke* this, f32 x, f32 y, f32 z, f32 xVel, f32 yVel, f32 zVel, f32 scale) {
    Effect_Initialize(this);

    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_EFFECT_FIRE_SMOKE;

    this->obj.pos.x = x;
    this->obj.pos.y = y;
    this->obj.pos.z = z;

    this->vel.x = xVel;
    this->vel.y = yVel;
    this->vel.z = zVel;

    this->scale2 = scale;
    this->scale1 = 0.5f;

    this->unk_4C = 2;
    this->obj.rot.z = RAND_FLOAT(360.0f);

    Object_SetInfo(&this->info, this->obj.id);

    this->unk_44 = 230;
}

// Explosion/Fire effect with smoke.
void Katina_FireSmokeEffectSpawn(f32 x, f32 y, f32 z, f32 xVel, f32 yVel, f32 zVel, f32 scale) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Katina_FireSmokeEffectSetup(&gEffects[i], x, y, z, xVel, yVel, zVel, scale);
            break;
        }
    }
}

/**
 * Start cutscene where Bill is seen chasing an enemy
 * while one of his teammates defeats it.
 */
void Katina_StartCutsceneUpdate(void) {
    ActorCutscene* actor = &gActors[4];
    s32 i;
    Vec3f dest;

    Matrix_RotateY(gCalcMatrix, -(M_PI / 4), MTXF_NEW);

    for (i = 0; i < 3; i++, actor++) {
        if (actor->obj.status == OBJ_FREE) {
            Actor_Initialize(actor);
            actor->obj.status = OBJ_INIT;
            actor->obj.id = OBJ_ACTOR_CUTSCENE;
            Matrix_MultVec3fNoTranslate(gCalcMatrix, &D_i4_8019F0F0[i], &actor->obj.pos);
            actor->obj.rot = D_i4_8019F138[i];
            Matrix_MultVec3fNoTranslate(gCalcMatrix, &D_i4_8019F114[i], &dest);
            actor->vel.x = dest.x;
            actor->vel.y = dest.y;
            actor->vel.z = dest.z;
            actor->animFrame = D_i4_8019F15C[i];
            actor->drawShadow = true;
            actor->iwork[KA_ACTOR_IWORK_11] = 1;
            Object_SetInfo(&actor->info, actor->obj.id);
            AUDIO_PLAY_SFX(NA_SE_EN_ENGINE_01, actor->sfxSource, 4);
        }
    }
}

void Katina_LevelStart(Player* player) {
    s32 j;
    s32 i;
    Vec3f src;
    Vec3f dest;
    Actor* actor;

    gAllRangeEventTimer = 0;

    if (player->csState != 0) {
        Katina_801981F8(&gActors[4]);
    }

    switch (player->csState) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
            break;

        case 0:
            gCsFrameCount = 0;

            Katina_StartCutsceneUpdate();

            gCsCamEyeX = 3535.0f;
            gCsCamEyeY = 500.0f;
            gCsCamEyeZ = 3535.0f;
            gCsCamAtX = gActors[4].obj.pos.x;
            gCsCamAtY = gActors[4].obj.pos.y;
            gCsCamAtZ = gActors[4].obj.pos.z;

            player->csState = 11;
            D_ctx_80177A48[0] = 1.0f;
            break;

        case 11:
            gCsCamAtX = gActors[4].obj.pos.x;
            gCsCamAtY = gActors[4].obj.pos.y;
            gCsCamAtZ = gActors[4].obj.pos.z;

            gActors[4].obj.rot.z -= 0.2f;
            gActors[5].obj.rot.z += 0.3f;
            gActors[6].obj.rot.z += 0.7f;

            if (gCsFrameCount == 100) {
                gCsFrameCount = 80;
                player->csState = 12;
            }
            break;

        case 12:
            gActors[4].vel.y += 0.3f;
            gActors[4].vel.z += 0.7f;
            gActors[4].obj.rot.z -= 1.0f;

            if (gCsFrameCount == 120) {
                ActorAllRange_SpawnTeam();
                player->csState = 13;
                player->pos.x = 0.0f;
                player->pos.y = 1300.0f;
                player->pos.z = 10000.0f;
                player->rot.x = -10.0f;

                for (i = 1, actor = &gActors[1]; i <= 3; i++, actor++) {
                    actor->obj.pos.x = D_i4_8019F168[i - 1].x + player->pos.x;
                    actor->obj.pos.y = D_i4_8019F168[i - 1].y + player->pos.y;
                    actor->obj.pos.z = D_i4_8019F168[i - 1].z + player->pos.z;
                    actor->rot_0F4.y = D_i4_8019F18C[i - 1];
                    actor->rot_0F4.x = -10.0f;
                    actor->state = 1;
                    actor->timer_0BC = 1000;
                }
            }
            break;

        case 13:
            player->cam.at.x = gCsCamAtX = player->pos.x;
            player->cam.at.y = gCsCamAtY = player->pos.y;
            player->cam.at.z = gCsCamAtZ = player->pos.z;
            player->cam.eye.x = gCsCamEyeX = 100.0f;
            player->cam.eye.z = gCsCamEyeZ = 7000.0f;

            if (gCsFrameCount == 240) {
                Object_Kill(&gActors[4].obj, gActors[4].sfxSource);
                Object_Kill(&gActors[6].obj, gActors[6].sfxSource);
                player->state_1C8 = PLAYERSTATE_1C8_ACTIVE;
                player->unk_014 = 0.0001f;

                AUDIO_PLAY_BGM(gBgmSeqId);

                gLevelStartStatusScreenTimer = 80;

                for (actor = &gActors[1], i = 1; i <= 3; i++, actor++) {
                    actor->timer_0BC = 0;
                }
                gAllRangeEventTimer = -610;
            }
            break;
    }

    src.x = 0.0f;
    src.y = 0.0f;
    src.z = 100.0f;

    switch (gCsFrameCount) {
        case 15:
            Radio_PlayMessage(gMsg_ID_18000, RCID_BILL);
            break;

        case 10:
        case 20:
        case 25:
        case 40:
            actor = &gActors[5];
            Matrix_RotateY(gCalcMatrix, actor->obj.rot.y * M_DTOR, MTXF_NEW);
            Matrix_RotateX(gCalcMatrix, actor->obj.rot.x * M_DTOR, MTXF_APPLY);
            Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);
            Actor_SpawnPlayerLaser(5, actor->obj.pos.x + (dest.x * 1.5), actor->obj.pos.y + (dest.y * 1.5),
                                   actor->obj.pos.z + (dest.z * 1.5), dest.x, dest.y, dest.z, actor->obj.rot.x,
                                   actor->obj.rot.y, actor->obj.rot.z);
            break;

        case 35:
        case 41:
        case 44:
            actor = &gActors[6];
            Matrix_RotateY(gCalcMatrix, actor->obj.rot.y * M_DTOR, MTXF_NEW);
            Matrix_RotateX(gCalcMatrix, actor->obj.rot.x * M_DTOR, MTXF_APPLY);
            Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);
            Actor_SpawnPlayerLaser(6, actor->obj.pos.x + (dest.x * 1.5), actor->obj.pos.y + (dest.y * 1.5),
                                   actor->obj.pos.z + (dest.z * 1.5), dest.x, dest.y, dest.z, actor->obj.rot.x,
                                   actor->obj.rot.y, actor->obj.rot.z);
            break;

        case 45:
            func_effect_8007D2C8(gActors[5].obj.pos.x, gActors[5].obj.pos.y, gActors[5].obj.pos.z, 10.0f);

            for (j = 0; j < 10; j++) {
                func_effect_800794CC(gActors[5].obj.pos.x, gActors[5].obj.pos.y, gActors[5].obj.pos.z, 1.0f);
            }

            func_effect_8007A6F0(&gActors[5].obj.pos, NA_SE_EN_EXPLOSION_M);
            break;

        case 47:
            Object_Kill(&gActors[5].obj, gActors[5].sfxSource);
            break;
    }

    Matrix_RotateY(gCalcMatrix, (player->rot.y + player->yRot_114 + 180.0f) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -(player->rot.x * M_DTOR), MTXF_APPLY);

    src.x = 0;
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

    Math_SmoothStepToF(&player->cam.eye.x, gCsCamEyeX, D_ctx_80177A48[0], 50000.0f, 0.0f);
    Math_SmoothStepToF(&player->cam.eye.y, gCsCamEyeY, D_ctx_80177A48[0], 50000.0f, 0.0f);
    Math_SmoothStepToF(&player->cam.eye.z, gCsCamEyeZ, D_ctx_80177A48[0], 50000.0f, 0.0f);
    Math_SmoothStepToF(&player->cam.at.x, gCsCamAtX, D_ctx_80177A48[0], 50000.0f, 0.0f);
    Math_SmoothStepToF(&player->cam.at.y, gCsCamAtY, D_ctx_80177A48[0], 50000.0f, 0.0f);
    Math_SmoothStepToF(&player->cam.at.z, gCsCamAtZ, D_ctx_80177A48[0], 50000.0f, 0.0f);
}

void Katina_BaseUpdate(Frontlinebase* this) {
    s32 i;
    f32 posX;
    Vec3f src;
    Vec3f dest;
    Actor* actor;

    switch (this->state) {
        case KA_BOSS_BASE_IDLE:
            break;

        case KA_BASE_STATE_1:
            this->timer_050 = 4;
            this->state++;
            func_effect_8007B344(this->obj.pos.x, this->obj.pos.y + 250.0f, this->obj.pos.z + 600.0f, 71.0f, 5);
            gCameraShake = 25;
            gLight1R = 255;
            gLight1G = 0;
            gLight1B = 0;

        case KA_BASE_STATE_2:
            if (this->timer_050 == 1) {
                src.x = 0.0f;
                src.y = 0.0f;
                src.z = 500.0f;

                for (posX = 50.0f, i = 0; posX < 600.0f; i++) {
                    Matrix_RotateY(gCalcMatrix, i * 13.0f * M_DTOR, MTXF_NEW);
                    Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

                    if (dest.z > 0.0f) {
                        func_effect_8007953C(dest.x, posX, dest.z, 1.3f);
                        posX += 6.25f;
                        src.z -= 6.0f;
                    }
                }

                // Kill all active enemy and ally actors
                for (actor = &gActors[AI360_10], i = 10; i < ARRAY_COUNT(gActors); i++, actor++) {
                    if (actor->obj.status == OBJ_ACTIVE) {
                        actor->obj.status = OBJ_DYING;
                        actor->timer_0BC = 30;
                    }
                }
            }

            for (i = 0; i < 1; i++) {
                Katina_FireSmokeEffectSpawn(RAND_FLOAT_CENTERED(700.0f) + this->obj.pos.x,
                                            RAND_FLOAT_CENTERED(400.0f) + (this->obj.pos.y + 200.0f),
                                            RAND_FLOAT_CENTERED(700.0f) + this->obj.pos.z, RAND_FLOAT_CENTERED(50.0f),
                                            RAND_FLOAT(40.0f) + 30.0f, RAND_FLOAT_CENTERED(50.0f),
                                            RAND_FLOAT(10.0f) + 10.0f);
            }
            break;
    }

    if (this->dmgType != DMG_NONE) {
        this->dmgType = DMG_NONE;
        AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
    }
}

void Katina_Base_Draw(Frontlinebase* this) {
    gSPFogPosition(gMasterDisp++, gFogNear, 1002);
    Matrix_Translate(gGfxMatrix, 0.0f, 20.0f, 0.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);

    if (this->state == KA_BOSS_BASE_IDLE) {
        gSPDisplayList(gMasterDisp++, aKaFLBaseDL);
    } else {
        RCP_SetupDL(&gMasterDisp, SETUPDL_57);
        gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
        gSPDisplayList(gMasterDisp++, aKaFLBaseDestroyedDL);
    }
}

void Katina_BossSetup(Saucerer* this) {
    this->swork[BOSS_HATCH_1_HP] = 100;
    this->swork[BOSS_HATCH_2_HP] = 100;
    this->swork[BOSS_HATCH_3_HP] = 100;
    this->swork[BOSS_HATCH_4_HP] = 100;
    this->swork[BOSS_CORE_HP] = 400;
    this->fwork[BOSS_CORE_TARGET_LEVEL] = 850.0f;
    this->fwork[BOSS_CORE_LEVEL] = 850.0f;
    this->vwork[0].y = 1000.0f;
}

void Katina_Hatch_Destroy(Saucerer* this, s32 hatchIdx) {
    s32 i;
    Vec3f pos;

    func_effect_8007D2C8(this->obj.pos.x + (this->vwork[hatchIdx + 1].x * 1.3f),
                         this->obj.pos.y + (this->vwork[hatchIdx + 1].y * 1.3f),
                         this->obj.pos.z + (this->vwork[hatchIdx + 1].z * 1.3f), 15.0f);
    this->swork[hatchIdx + 5] = 60;

    for (i = 0; i < 20; i++) {
        func_effect_800794CC(this->obj.pos.x + RAND_FLOAT_CENTERED(300.0f) + (this->vwork[hatchIdx + 1].x * 1.3f),
                             this->obj.pos.y + RAND_FLOAT_CENTERED(300.0f) + (this->vwork[hatchIdx + 1].y * 1.3f),
                             this->obj.pos.z + RAND_FLOAT_CENTERED(300.0f) + (this->vwork[hatchIdx + 1].z * 1.3f),
                             1.55f);
    }

    pos.x = this->obj.pos.x + (this->vwork[hatchIdx + 1].x * 1.3f);
    pos.y = this->obj.pos.y + (this->vwork[hatchIdx + 1].y * 1.3f);
    pos.z = this->obj.pos.z + (this->vwork[hatchIdx + 1].z * 1.3f);

    func_effect_8007A6F0(&pos, NA_SE_EN_EXPLOSION_M);

    this->swork[BOSS_HATCH_DESTROY_COUNT]++;

    BonusText_Display(pos.x, pos.y - 300.0f, pos.z, 5);

    gHitCount += 6;
    D_ctx_80177850 = 15;
}

void Katina_BossHandleDamage(Saucerer* this) {
    s32 i;
    s32 pad;
    Vec3f src;
    Vec3f dest;
    Vec3f sfxSource;
    f32 y;

    if (this->dmgType != DMG_NONE) {
        this->dmgType = DMG_NONE;

        if (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_STANDBY) {
            return;
        }

        switch (this->dmgPart) {
            case 0:
            case 1:
            case 2:
            case 3:
                if (this->swork[10 + this->dmgPart] > 0) {
                    this->swork[00 + this->dmgPart] = 20;
                    this->swork[10 + this->dmgPart] -= this->damage;

                    sfxSource.x = (this->vwork[1 + this->dmgPart].x * 1.3f) + this->obj.pos.x;
                    sfxSource.y = (this->vwork[1 + this->dmgPart].y * 1.3f) + this->obj.pos.y;
                    sfxSource.z = (this->vwork[1 + this->dmgPart].z * 1.3f) + this->obj.pos.z;

                    func_effect_8007A6F0(&sfxSource, NA_SE_OB_DAMAGE_M);

                    if (this->swork[10 + this->dmgPart] <= 0) {
                        this->swork[10 + this->dmgPart] = 0;
                        Katina_Hatch_Destroy(this, this->dmgPart);
                    }
                }
                break;

            case 4:
            case 5:
            case 6:
            case 7:
                if ((this->swork[BOSS_CORE_HP] > 0) && (this->state > 10)) {
                    this->swork[BOSS_CORE_FLASH_TIMER] = 20;
                    this->swork[BOSS_CORE_HP] -= this->damage;

                    if (this->swork[BOSS_CORE_HP] < 100) {
                        func_effect_8007A6F0(&this->obj.pos, NA_SE_EN_KNOCK_DOWN);
                    } else {
                        func_effect_8007A6F0(&this->obj.pos, NA_SE_OB_DAMAGE_M);
                    }

                    if (this->swork[BOSS_CORE_HP] <= 0) {
                        // OBJ_EFFECT_FIRE_SMOKE
                        func_effect_8007D2C8(this->obj.pos.x, this->obj.pos.y - 1000.0f, this->obj.pos.z, 15.0f);

                        y = 0.0f;

                        this->swork[BOSS_SWORK_9] = 80;

                        src.x = 0.0f;
                        src.y = 0.0f;
                        src.z = 50.0f;

                        for (i = 0; i < 130; i++, y += 5.0f, src.z += 1.4f) {
                            Matrix_RotateY(gCalcMatrix, i * 35.0f * M_DTOR, MTXF_NEW);
                            Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

                            // Broken pieces of the core
                            // OBJ_EFFECT_357
                            func_effect_800794CC(this->obj.pos.x + dest.x, this->obj.pos.y - 1200.0f + y,
                                                 this->obj.pos.z + dest.z, 1.6f);
                        }

                        AUDIO_PLAY_SFX(NA_SE_EN_DOWN_IMPACT, this->sfxSource, 4);

                        gScreenFlashTimer = 8;
                        this->state = 20;
                        this->timer_050 = 50;

                        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 50);
                        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 50);

                        Radio_PlayMessage(gMsg_ID_18066, RCID_BILL);

                        this->obj.pos.y -= 1000.0f;

                        Boss_AwardBonus(this);

                        this->obj.pos.y += 1000.0f;
                    }
                }
                break;
        }
    }

    if (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_ACTIVE) {
        if ((gGameFrameCount % 16) == 0) {
            for (i = 0; i < 4; i++) {
                if ((this->swork[10 + i] <= 0) && (Rand_ZeroOne() < 0.2f)) {
                    func_effect_8007BFFC((this->vwork[1 + i].x * 1.3f) + this->obj.pos.x,
                                         (this->vwork[1 + i].y * 1.3f) + this->obj.pos.y,
                                         (this->vwork[1 + i].z * 1.3f) + this->obj.pos.z, this->vel.x, this->vel.y,
                                         this->vel.z, 7.0f, 5);
                }
            }
        }
    }

    for (i = 0; i < 5; i++) {
        if (this->swork[5 + i] != 0) {
            this->swork[5 + i]--;
            if (i < 4) {
                Katina_FireSmokeEffectSpawn(this->vwork[1 + i].x * 1.3f + this->obj.pos.x,
                                            this->vwork[1 + i].y * 1.1f + this->obj.pos.y,
                                            this->vwork[1 + i].z * 1.3f + this->obj.pos.z, this->vwork[1 + i].x * 0.05f,
                                            this->vwork[1 + i].y * 0.05f, this->vwork[1 + i].z * 0.05f, 15.0f);
            } else {
                Katina_FireSmokeEffectSpawn(this->obj.pos.x, this->obj.pos.y - 700.0f, this->obj.pos.z, 0.0f, -40.0f,
                                            0.0f, 10.0f);
            }
        }
    }
}

void Katina_BossSpawnEnemies(Saucerer* this, Vec3f* pos, f32 arg2) {
    s32 i;
    ActorAllRange* actor = &gActors[20];

    for (i = 10; i < 49; i++, actor++) {
        if (actor->obj.status == OBJ_FREE) {
            Actor_Initialize(actor);
            actor->obj.status = OBJ_ACTIVE;
            actor->obj.id = OBJ_ACTOR_ALLRANGE;

            actor->obj.pos.x = this->obj.pos.x + pos->x;
            actor->obj.pos.y = this->obj.pos.y + pos->y;
            actor->obj.pos.z = this->obj.pos.z + pos->z;

            actor->state = 1;
            actor->timer_0BC = 20;
            actor->rot_0F4.y = arg2;
            actor->rot_0F4.x = -30.0f;

            actor->aiType = i + AI360_10;
            actor->animFrame = D_i4_8019F198[i - 10];
            actor->aiIndex = sEnemySpawnTargets[i - 10];

            actor->health = 24;
            if (actor->animFrame >= 2) {
                actor->health = 1000;
            }

            actor->drawShadow = true;

            if (D_i4_801A0540 < 9600) {
                actor->itemDrop = DROP_SILVER_RING_10p;
            }

            actor->timer_0C2 = 30;
            actor->timer_0C4 = 400;

            Object_SetInfo(&actor->info, actor->obj.id);

            AUDIO_PLAY_SFX(NA_SE_EN_PASS, actor->sfxSource, 4);

            actor->info.action = (ObjectFunc) Katina_EnemyUpdate;
            actor->info.draw = (ObjectFunc) Katina_EnemyDraw;
            break;
        }
    }
}

/**
 * Sets the angle for the enemies coming out of the Saucerer
 */
void Katina_SetOutcomingEnemyAngle(Saucerer* this) {
    f32 angle;
    f32 distY;
    s32 i;

    for (i = 0, angle = 360.0f; i < 4; i++) {
        if (this->swork[i + BOSS_HATCH_1_HP] > 0) {
            distY = this->obj.rot.y + angle;
            if (distY > 360.0f) {
                distY -= 360.0f;
            }
            Katina_BossSpawnEnemies(this, &this->vwork[i + 1], distY);
        }
        angle -= 90.0f;
    }
}

void Katina_BossUpdate(Saucerer* this) {
    s32 i;
    s32 rotCount;
    s32 enemyCount;
    s32 pad[2];
    f32 angle;
    f32 scale;
    Vec3f src;
    Vec3f dest;
    s32 pad3;
    Actor* actor;

    gBossFrameCount++;

    enemyCount = 0;

    for (i = 10, actor = &gActors[i]; i < ARRAY_COUNT(gActors); i++, actor++) {
        if ((actor->obj.status == OBJ_ACTIVE) && (actor->animFrame == 0)) {
            enemyCount++;
        }
    }

    if (this->swork[BOSS_CORE_TIMER] != 0) {
        this->swork[BOSS_CORE_TIMER]--;
    }

    /**
     * Summon core if all hatches are destroyed or after 3 minutes from Saucerer appearance.
     */
    if ((((this->swork[BOSS_HATCH_1_HP] <= 0) && (this->swork[BOSS_HATCH_2_HP] <= 0) &&
          (this->swork[BOSS_HATCH_3_HP] <= 0) && (this->swork[BOSS_HATCH_4_HP] <= 0)) ||
         (this->swork[BOSS_CORE_TIMER] == 1)) &&
        (this->state < 10)) {
        this->state = 10;
        this->timer_050 = 50;
    }

    if (this->timer_054 == 1) {
        Radio_PlayMessage(gMsg_ID_18040, RCID_BILL);
    }

    switch (this->state) {
        // Send Saucerer whether you killed 10 enemies or after 2 minutes of gameplay
        case SAUCERER_STAND_BY:
            if ((gHitCount >= 10) || (gAllRangeEventTimer > 3840)) {
                if ((D_edisplay_801615D0.y < 0.0f)) {
                    this->state = 1;

                    this->vwork[0].y = 2000.0f;

                    this->drawShadow = true;

                    AUDIO_PLAY_SFX(NA_SE_EARTHQUAKE, this->sfxSource, 0);

                    D_i4_801A0548 = 100.0f;
                    D_i4_801A0544 = 100.0f;
                    D_i4_801A0550 = 70.0f;
                    D_i4_801A054C = 70.0f;
                    D_i4_801A0558 = 50.0f;
                    D_i4_801A0554 = 50.0f;

                    this->fwork[BOSS_Y_ROT_SPEED_TARGET] = 0.4f;
                    this->fwork[BOSS_MOVEMENT_SPEED] = 10.0f;

                    Radio_PlayMessage(gMsg_ID_18030, RCID_BILL);

                    AUDIO_PLAY_SFX(NA_SE_KA_UFO_ENGINE, this->sfxSource, 0);
                }
            }
            break;

        /**
         * Wait for Saucerer to be near the base to start cutscene.
         * Set checkpoint.
         */
        case SAUCERER_CS_APPROACH_BASE:
            if ((gPlayer[0].state_1C8 == PLAYERSTATE_1C8_ACTIVE) || (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_U_TURN)) {
                if (this->obj.pos.z < 4500.0f) {
                    this->state++;

                    gPlayer[0].state_1C8 = PLAYERSTATE_1C8_STANDBY;

                    gPlayer[0].cam.eye.x = -900.0f;
                    gPlayer[0].cam.eye.y = 100.0f;
                    gPlayer[0].cam.eye.z = 1400.0f;

                    gPlayer[0].cam.at.x = -730.0f;
                    gPlayer[0].cam.at.y = 130.0f;
                    gPlayer[0].cam.at.z = 1160.0f;

                    gPlayer[0].camRoll = 0.0f;

                    this->obj.pos.x = -4500.0f;
                    this->obj.pos.z = 4500.0f;

                    this->timer_050 = 500;
                    this->fwork[BOSS_MOVEMENT_SPEED] = 60.0f;

                    // Checkpoint reached
                    gAllRangeCheckpoint = 1;
                    gSavedHitCount = gHitCount;
                    for (i = TEAM_ID_FALCO; i <= TEAM_ID_PEPPY; i++) {
                        gSavedTeamShields[i] = gTeamShields[i];
                    }

                    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 10);
                    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 10);
                }
            }
            break;

        case SAUCERER_CS_CLOSE_UP:
            gPlayer[0].cam.at.y += 0.2f;

            Math_SmoothStepToF(&D_ctx_801779A8[gMainController], 30.0f, 1.0f, 1.65f, 0.0f);

            if (this->timer_050 == 460) {
                D_i4_801A0548 = 10.0f;
                D_i4_801A0550 = 7.0f;
                D_i4_801A0558 = 5.0f;
            }

            Math_SmoothStepToF(&D_i4_801A0544, D_i4_801A0548, 1.0f, 4.0f, 0);
            Math_SmoothStepToF(&D_i4_801A054C, D_i4_801A0550, 1.0f, 2.8f, 0);
            Math_SmoothStepToF(&D_i4_801A0554, D_i4_801A0558, 1.0f, 2.0f, 0);

            gLight1R = D_i4_801A0544;
            gLight1G = D_i4_801A054C;
            gLight1B = D_i4_801A0554;

            if (this->timer_050 == 170) {
                this->state++;

                gPlayer[0].cam.eye.x = -2500.0f;
                gPlayer[0].cam.eye.y = 250.0f;
                gPlayer[0].cam.eye.z = 2500.0f;
                gPlayer[0].cam.at.x = 0.0f;
                gPlayer[0].cam.at.y = 1000.0f;
                gPlayer[0].cam.at.z = 0.0f;

                this->drawShadow = false;

                this->obj.pos.x = -500.0f;
                this->obj.pos.z = 500.0f;

                gLight1R = 50;
                gLight1G = 35;
                gLight1B = 25;

                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 50);
                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 50);

                this->timer_050 = 80;
                this->fwork[BOSS_Y_ROT_SPEED_TARGET] = 0.0f;
                this->obj.rot.y = 217.0f;

                for (i = 10; i < ARRAY_COUNT(gActors); i++) {
                    if (gActors[i].animFrame == 0) {
                        Object_Kill(&gActors[i].obj, gActors[i].sfxSource);
                    }
                }
            }
            break;

        case SAUCERER_CS_OPEN_HATCHES_START:
            if (this->timer_050 == 0) {
                this->state++;
                this->timer_050 = 60;
                AUDIO_PLAY_SFX(NA_SE_KA_UFO_HATCH_OPEN, this->sfxSource, 0);
                this->fwork[BOSS_HATCH_1_ANGLE_TARGET] = 30.0f;
                this->fwork[BOSS_HATCH_2_ANGLE_TARGET] = 30.0f;
                this->fwork[BOSS_HATCH_3_ANGLE_TARGET] = 30.0f;
                this->fwork[BOSS_HATCH_4_ANGLE_TARGET] = 30.0f;
            }
            break;

        case SAUCERER_CS_OPEN_HATCHES_END:
            if (this->timer_050 == 0) {
                this->state++;
                this->timer_050 = 100;
                this->timer_052 = 310;
                AUDIO_PLAY_SFX(NA_SE_KA_UFO_HATCH_STOP, this->sfxSource, 0);
            }
            break;

        /**
         * Cutscene: Boss music starts, enemies coming out of the Saucerer.
         * Return control to the player after cutscene ends and close the hatches.
         */
        case SAUCERER_CS_SEND_ENEMIES:
            if (this->timer_050 == 1) {
                AUDIO_PLAY_BGM(NA_BGM_BOSS_KA);
            }

            if ((this->timer_050 == 0) && ((this->timer_052 % 16) == 0)) {
                Katina_SetOutcomingEnemyAngle(this);
            }

            if (this->timer_052 == 0) {
                AUDIO_PLAY_SFX(NA_SE_KA_UFO_HATCH_CLOSE, this->sfxSource, 0);

                this->state++;

                if (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_STANDBY) {
                    gPlayer[0].state_1C8 = PLAYERSTATE_1C8_ACTIVE;
                    Camera_Update360(&gPlayer[0], 1);
                }

                gPlayer[0].unk_014 = 0.0f;

                // Close hatches.
                this->fwork[BOSS_HATCH_1_ANGLE_TARGET] = 0.0f;
                this->fwork[BOSS_HATCH_2_ANGLE_TARGET] = 0.0f;
                this->fwork[BOSS_HATCH_3_ANGLE_TARGET] = 0.0f;
                this->fwork[BOSS_HATCH_4_ANGLE_TARGET] = 0.0f;
                this->fwork[BOSS_Y_ROT_SPEED_TARGET] = 0.4f;
                this->fwork[BOSS_MOVEMENT_SPEED] = 0.0f;

                Radio_PlayMessage(gMsg_ID_18035, RCID_FALCO);

                this->timer_052 = 70;
                this->timer_054 = 200;
                this->timer_056 = 1280;

                this->swork[BOSS_CORE_TIMER] = 5760;

                gBossFrameCount = 0;

                D_i4_801A0540 = 0;
            }
            break;

        /**
         * Open hatches for 10 seconds when there's less
         * than 30 enemies or after 40 seconds have passed
         */
        case SAUCERER_OPEN_HATCHES:
            if (this->timer_052 == 1) {
                AUDIO_PLAY_SFX(NA_SE_KA_UFO_HATCH_STOP, this->sfxSource, 0);
            }

            if (this->timer_050 == 0) {
                this->timer_050 = RAND_INT(100.0f) + 100;
                this->vwork[0].x = RAND_FLOAT_CENTERED(10000.0f);
                this->vwork[0].z = RAND_FLOAT_CENTERED(10000.0f);
            }

            Math_SmoothStepToF(&this->fwork[BOSS_MOVEMENT_SPEED], 30.0f, 0.1f, 0.5f, 0.0f);

            if ((enemyCount < 30) || (this->timer_056 == 0)) {
                this->state = 7;
                this->timer_050 = 300;

                AUDIO_PLAY_SFX(NA_SE_KA_UFO_HATCH_OPEN, this->sfxSource, 0);

                this->fwork[BOSS_Y_ROT_SPEED_TARGET] = 0.0f;
                this->fwork[BOSS_HATCH_4_ANGLE_TARGET] = 30.0f;
                this->fwork[BOSS_HATCH_3_ANGLE_TARGET] = 30.0f;
                this->fwork[BOSS_HATCH_2_ANGLE_TARGET] = 30.0f;
                this->fwork[BOSS_HATCH_1_ANGLE_TARGET] = 30.0f;

                Radio_PlayMessage(gMsg_ID_18045, RCID_BILL);
            }
            break;

        /**
         * Send out more enemies.
         * Close hatches after 10 seconds.
         */
        case SAUCERER_SEND_ENEMIES:
            Math_SmoothStepToF(&this->fwork[10], 0.0f, 0.1f, 0.5f, 0.0f);

            if ((this->timer_050 < 200) && ((this->timer_050 % 16) == 0)) {
                Katina_SetOutcomingEnemyAngle(this);
            }

            if (this->timer_050 == 240) {
                AUDIO_PLAY_SFX(NA_SE_KA_UFO_HATCH_STOP, this->sfxSource, 0);
            }

            if (this->timer_050 == 0) {
                this->state = 6;
                this->fwork[BOSS_HATCH_4_ANGLE_TARGET] = 0.0f;
                this->fwork[BOSS_HATCH_3_ANGLE_TARGET] = 0.0f;
                this->fwork[BOSS_HATCH_2_ANGLE_TARGET] = 0.0f;
                this->fwork[BOSS_HATCH_1_ANGLE_TARGET] = 0.0f;
                this->timer_056 = 1920;
                this->timer_052 = 70;
                AUDIO_PLAY_SFX(NA_SE_KA_UFO_HATCH_CLOSE, this->sfxSource, 0);
            }
            break;

        // Start countdown and lower down core.
        case SAUCERER_LOWER_CORE:
            if (this->timer_050 == 0) {
                this->fwork[BOSS_CORE_TARGET_LEVEL] = 200.0f;
                AUDIO_PLAY_SFX(NA_SE_KA_UFO_CORE_OPEN, this->sfxSource, 0);
                Audio_KillSfxBySourceAndId(this->sfxSource, NA_SE_KA_UFO_ENGINE);
                this->state = 11;
                this->timer_050 = 100;
                Radio_PlayMessage(gMsg_ID_18050, RCID_BILL);
                gAllRangeCountdownScale = 1.0f;
                gShowAllRangeCountdown = true;
                gAllRangeCountdown[0] = 1;
                gAllRangeCountdown[1] = 1;
                gAllRangeCountdown[2] = 30;
            }
            break;

        // Set a 1 minute timer for Saucerer attack.
        case SAUCERER_LASER_CHARGE_START:
            if (this->timer_050 == 0) {
                AUDIO_PLAY_SFX(NA_SE_KA_UFO_HATCH_STOP, this->sfxSource, 0);
                this->state = 12;
                this->timer_050 = 1928;
                Radio_PlayMessage(gMsg_ID_18055, RCID_BILL);
                AUDIO_PLAY_SFX(NA_SE_KA_UFO_LONG_CHARGE, this->sfxSource, 0);
            }
            break;

        /**
         * Start Saucerer attack after 13 seconds from Bill's warning
         * Start cutscene for base destruction.
         */
        case SAUCERER_CS_LASER_CHARGE_END:
            if (this->timer_050 == 400) {
                Radio_PlayMessage(gMsg_ID_18065, RCID_BILL);
            }

            this->vwork[0].x = 0.0f;
            this->vwork[0].z = 0.0f;

            Math_SmoothStepToF(&this->fwork[BOSS_MOVEMENT_SPEED], 5.0f, 0.1f, 0.5f, 0.0f);

            if ((this->timer_050 == 0) && ((gPlayer[0].state_1C8 == PLAYERSTATE_1C8_ACTIVE) ||
                                           (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_U_TURN))) {
                gShowAllRangeCountdown = false;
                this->timer_050 = 1000;
                this->state = 15;
                this->obj.rot.y = 0.0f;

                this->obj.pos.y = 3500.0f;
                this->obj.pos.x = 0.0f;
                this->obj.pos.z = 0.0f;

                this->fwork[BOSS_Y_ROT_SPEED_TARGET] = 0.0f;
                this->fwork[BOSS_MOVEMENT_SPEED] = 0.0f;

                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 50);
                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 50);

                gPlayer[0].state_1C8 = PLAYERSTATE_1C8_STANDBY;

                gPlayer[0].camRoll = 0.0f;

                gPlayer[0].cam.eye.x = this->obj.pos.x;
                gPlayer[0].cam.eye.y = 600.0f;
                gPlayer[0].cam.eye.z = this->obj.pos.z + 5000.0f;

                gPlayer[0].cam.at.x = this->obj.pos.x;
                gPlayer[0].cam.at.y = this->obj.pos.y - 500.0f;
                gPlayer[0].cam.at.z = this->obj.pos.z;
            }
            break;

        // Rotate Saucerer into fire position.
        case SAUCERER_CS_ROTATE:
            if (this->timer_050 == 700) {
                Radio_PlayMessage(gMsg_ID_18070, RCID_BILL);
            }

            if (this->timer_050 == 580) {
                Radio_PlayMessage(gMsg_ID_18075, RCID_FOX);
            }

            if (this->timer_050 == 500) {
                gPlayer[0].state_1C8 = PLAYERSTATE_1C8_LEVEL_COMPLETE;
                gPlayer[0].csState = 100;
                gPlayer[0].unk_234 = 0;
                gCsFrameCount = 5000;
            }

            Math_SmoothStepToF(&this->obj.pos.y, 3000.0f, 0.02f, 0.5f, 0.0f);
            Math_SmoothStepToF(&this->obj.rot.x, 180.0f, 0.02f, 0.3f, 0.0f);
            Math_SmoothStepToF(&this->fwork[BOSS_FWORK_13], 180.0f, 0.02f, 0.2f, 0.0f);
            Math_SmoothStepToF(&gPlayer[0].cam.eye.z, this->obj.pos.z + 8000.0f, 0.05f, 3.0f, 0.0f);
            Math_SmoothStepToF(&gPlayer[0].cam.eye.y, this->obj.pos.y - 1000.0f, 0.05f, 2.0f, 0.0f);

            gPlayer[0].cam.at.y = this->obj.pos.y - 500.0f;

            this->drawShadow = false;

            if (this->timer_050 == 260) {
                this->obj.pos.y = 3000.0f;
                this->obj.rot.y = 0.0f;
                this->obj.rot.x = 180.0f;
                this->fwork[BOSS_FWORK_13] = 15.0f;

                gPlayer[0].state_1C8 = PLAYERSTATE_1C8_STANDBY;
                gPlayer[0].cam.eye.x = this->obj.pos.x;
                gPlayer[0].cam.eye.y = 600.0f;
                gPlayer[0].cam.eye.z = this->obj.pos.z - 1500.0f;
                gPlayer[0].cam.at.x = this->obj.pos.x;
                gPlayer[0].cam.at.y = this->obj.pos.y - 300.0f;
                gPlayer[0].cam.at.z = this->obj.pos.z;

                this->state = 16;
                this->timer_050 = 130;
                this->timer_052 = 1000;

                D_i4_801A0548 = 100.0f;
                D_i4_801A0544 = 100.0f;
                D_i4_801A0550 = 70.0f;
                D_i4_801A054C = 70.0f;
                D_i4_801A0558 = 50.0f;
                D_i4_801A0554 = 50.0f;

                Audio_KillSfxBySourceAndId(this->sfxSource, NA_SE_KA_UFO_LONG_CHARGE);
                AUDIO_PLAY_SFX(NA_SE_KA_UFO_LAST_CHARGE, this->sfxSource, 0);
            }
            break;

        // Cutscene: Close up, start Saucerer attack.
        case SAUCERER_CS_LASER_FIRE_START:
            Math_SmoothStepToF(&D_ctx_801779A8[gMainController], 30.0f, 1.0f, 1.6f, 0.0f);
            Math_SmoothStepToF(&gPlayer[0].cam.eye.z, 0.0f, 0.05f, 5.0f, 0.0f);
            this->fwork[BOSS_FWORK_13] += 0.1f;
            Math_SmoothStepToF(&gEnvLightyRot, 200.0f, 1.0f, 0.5f, 0.0f);

            scale = 0.5f;

            D_i4_801A0548 = 0.0f;
            D_i4_801A0550 = 100.0f;
            D_i4_801A0558 = 255.0f;

            rotCount = 0;

            if (this->timer_050 == 0) {
                rotCount = 4;
                Math_SmoothStepToF(&this->fwork[BOSS_LASER_LIGHT_SCALE], 10.0f, 0.02f, 0.05f, 0.0f);
            } else if (this->timer_050 < 40) {
                rotCount = 2;
                Math_SmoothStepToF(&this->fwork[BOSS_LASER_LIGHT_SCALE], 10.0f, 0.02f, 0.05f, 0.0f);
            } else if (this->timer_050 < 80) {
                D_i4_801A0550 = 0.0f;
                rotCount = 1;
                scale = 3.0f;
            }

            Math_SmoothStepToF(&D_i4_801A0544, D_i4_801A0548, 1.0f, scale, 0);
            Math_SmoothStepToF(&D_i4_801A054C, D_i4_801A0550, 1.0f, scale, 0);
            Math_SmoothStepToF(&D_i4_801A0554, D_i4_801A0558, 1.0f, scale, 0);

            gLight1R = D_i4_801A0544;
            gLight1G = D_i4_801A054C;
            gLight1B = D_i4_801A0554;

            for (i = 0; i < rotCount; i++) {
                Matrix_RotateY(gCalcMatrix, RAND_FLOAT(2.0f) * M_PI, MTXF_NEW);
                src.x = 0.0f;
                src.y = 0.0f;
                src.z = RAND_FLOAT(400.0f) + 300.0f;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);
                Katina_LaserEnergyParticlesSpawn(this->obj.pos.x + dest.x, this->obj.pos.y - 500.0f,
                                                 this->obj.pos.z + dest.z, this->obj.pos.x, this->obj.pos.y - 500.0f,
                                                 this->obj.pos.z);
            }

            if ((this->timer_052 == 700) || (this->timer_052 == 697)) {
                i = gGameFrameCount % 64U;
                Object_Kill(&gEffects[i].obj, gEffects[i].sfxSource);
                func_effect_8007B344(this->obj.pos.x, this->obj.pos.y - 600.0f, this->obj.pos.z, 90.0f, 0);
                AUDIO_PLAY_SFX(NA_SE_KA_UFO_BEAM, this->sfxSource, 0);
            }

            if (this->timer_052 == 690) {
                this->state = 17;

                for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
                    if (gEffects[i].obj.id == OBJ_EFFECT_358) {
                        Object_Kill(&gEffects[i].obj, gEffects[i].sfxSource);
                    }
                }

                gPlayer[0].cam.eye.x = this->obj.pos.x;
                gPlayer[0].cam.eye.y = 300.0f;
                gPlayer[0].cam.eye.z = this->obj.pos.z + 2000.0f;

                gPlayer[0].cam.at.x = this->obj.pos.x;
                gPlayer[0].cam.at.y = 1500.0f;
                gPlayer[0].cam.at.z = this->obj.pos.z;

                gEnvLightyRot = 60.0f;

                gLight1R = 100;
                gLight1G = 70;
                gLight1B = 50;

                this->timer_050 = 10;
                this->fwork[BOSS_LASER_LIGHT_SCALE] = 20.0f;
            }
            break;

        // Cutscene: Saucerer fires laser to the base.
        case SAUCERER_CS_LASER_FIRE_END:
            this->fwork[BOSS_FWORK_13] += 0.1f;

            Math_SmoothStepToF(&gPlayer[0].cam.at.y, 525.0f, 0.3f, 50.0f, 0.0f);
            Math_SmoothStepToF(&this->fwork[BOSS_LASER_LENGTH], 8.0f, 1.0f, 2.0f, 0.0f);

            if (this->timer_050 == 1) {
                gBosses[KA_BOSS_BASE].state = 1;
                this->state = 18;
                this->timer_050 = 50;
                AUDIO_PLAY_SFX(NA_SE_EXPLOSION_DEMO3, this->sfxSource, 0);
            }
            break;

        // Cutscene: Base is hit by Saucerer's laser.
        case SAUCERER_CS_LASER_HIT:
            Math_SmoothStepToF(&D_ctx_801779A8[gMainController], 100.0f, 1.0f, 100.0f, 0.0f);
            Math_SmoothStepToF(&gPlayer[0].cam.at.y, 525.0f, 0.3f, 50.0f, 0.0f);

            if (this->timer_050 == 0) {
                gFillScreenAlphaTarget = 255;
                gFillScreenRed = 255;
                gFillScreenGreen = 255;
                gFillScreenBlue = 255;

                if (gFillScreenAlpha == 255) {
                    gPlayer[0].state_1C8 = PLAYERSTATE_1C8_LEVEL_COMPLETE;
                    gPlayer[0].csState = 2;
                    gPlayer[0].unk_234 = 1;

                    gCsFrameCount = 200;

                    Audio_StopPlayerNoise(0);
                    Audio_KillSfxBySource(&gPlayer[0].sfxSource[0]);

                    gPlayer[0].csTimer = 50;
                    gPlayer[0].baseSpeed = 0.0f;
                    gPlayer[0].yRot_114 = 0.0f;

                    gPlayer[0].rot.z = gPlayer[0].rot.y = gPlayer[0].rot.x = gPlayer[0].xRot_120 = gPlayer[0].yRot_114;

                    Play_ClearObjectData();

                    gEnvLightyRot = 60.0f;

                    gLight1R = 100;
                    gLight1G = 70;
                    gLight1B = 50;
                }
            }
            break;

        // Saucerer core destroyed, setup for MISSION_ACCOMPLISHED.
        case SAUCERER_DEFEAT:
            gShowAllRangeCountdown = false;

            Math_SmoothStepToF(&this->fwork[BOSS_MOVEMENT_SPEED], 0.0f, 0.1f, 3.0f, 0.0f);

            if ((this->timer_050 == 0) && ((gPlayer[0].state_1C8 == PLAYERSTATE_1C8_ACTIVE) ||
                                           (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_U_TURN))) {
                gPlayer[0].state_1C8 = PLAYERSTATE_1C8_LEVEL_COMPLETE;
                gPlayer[0].csState = 0;
                gMissionStatus = MISSION_ACCOMPLISHED;
                this->obj.pos.z = 0.0f;
                this->health = -1;
                this->fwork[BOSS_MOVEMENT_SPEED] = 0.0f;
                this->state++;
                this->timer_050 = 1000;
                this->obj.rot.y = 30.0f;
                this->obj.pos.x = -4000.0f;
                this->rot_078.z = 7.0f;

                AUDIO_PLAY_SFX(NA_SE_KA_UFO_FALLING, this->sfxSource, 0);

                for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
                    Object_Kill(&gEffects[i].obj, gEffects[i].sfxSource);
                }
            }
            break;

        // Cutscene: Saucerer falling to the ground.
        case SAUCERER_CS_FALL_TO_GROUND:
            Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
            Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);

            this->obj.pos.z += this->rot_078.z;

            if (this->timer_050 == 820) {
                AUDIO_PLAY_SFX(NA_SE_KA_UFO_BOUND, this->sfxSource, 0);
            }

            if (this->timer_050 > 820) {
                this->obj.rot.x += 0.075f;
                this->gravity = 0.1f;
                if (this->vel.y < -10.0f) {
                    this->vel.y = -10.0f;
                }
                src.x = RAND_FLOAT_CENTERED(3000.0f);
                src.y = -800.0f;
                src.z = RAND_FLOAT_CENTERED(3000.0f);
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);
                func_effect_800794CC(this->obj.pos.x + dest.x, this->obj.pos.y + dest.y, this->obj.pos.z + dest.z,
                                     1.55f);
            } else {
                this->obj.rot.x -= 0.06f;
                this->vel.y = 0.0f;
                this->gravity = 0.0f;
                Math_SmoothStepToF(&this->rot_078.z, 0.0f, 1.0f, 1.0f, 0.0f);
                Katina_FireSmokeEffectSpawn(
                    this->obj.pos.x + 2000.0f + RAND_FLOAT(500.0f), (this->obj.pos.y - 500.0f) + RAND_FLOAT(500.0f),
                    this->obj.pos.z + 600.0f + RAND_FLOAT(1000.0f), 0.0f, 20.0f, 0.0f, RAND_FLOAT(20.0f) + 15.0f);
            }

            if (((gGameFrameCount % 2) != 0) || (this->timer_050 > 850)) {
                src.x = RAND_FLOAT_CENTERED(4000.0f);
                src.y = RAND_FLOAT_CENTERED(600.0f) + -300.0f;
                src.z = RAND_FLOAT_CENTERED(4000.0f);
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);
                Katina_FireSmokeEffectSpawn(this->obj.pos.x + dest.x, this->obj.pos.y + dest.y,
                                            this->obj.pos.z + dest.z, 0.0f, 5.0f, 0.0f, RAND_FLOAT(15.0f) + 10.0f);
            }
            break;
    }

    if (this->state != 0) {
        angle = 360.0f;

        for (i = 0; i < 4; i++) {
            Matrix_RotateY(gCalcMatrix, (this->obj.rot.y + angle) * M_DTOR, MTXF_NEW);
            src.x = 0.0f;
            src.y = -550.0f;
            src.z = 850.0f;
            Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &this->vwork[1 + i]);
            angle -= 90.0f;
        }

        Math_SmoothStepToF(&this->fwork[BOSS_Y_ROT_SPEED], this->fwork[BOSS_Y_ROT_SPEED_TARGET], 0.1f, 0.01f, 0.0f);
        this->obj.rot.y += this->fwork[BOSS_Y_ROT_SPEED];

        if (this->obj.rot.y > 360.0f) {
            this->obj.rot.y -= 360.0f;
        }
        if (this->obj.rot.y < 0.0f) {
            this->obj.rot.y += 360.0f;
        }

        gRadarMarks[64].status = 1;
        gRadarMarks[64].type = 101;
        gRadarMarks[64].pos.x = this->obj.pos.x;
        gRadarMarks[64].pos.y = this->obj.pos.y;
        gRadarMarks[64].pos.z = this->obj.pos.z;
        gRadarMarks[64].yRot = this->rot_078.y + 180.0f;

        if (this->state < 6) {
            Math_SmoothStepToF(&this->obj.pos.x, this->vwork[0].x, 0.01f, this->fwork[BOSS_MOVEMENT_SPEED], 0);
            Math_SmoothStepToF(&this->obj.pos.y, this->vwork[0].y, 0.01f, this->fwork[BOSS_MOVEMENT_SPEED], 0);
            Math_SmoothStepToF(&this->obj.pos.z, this->vwork[0].z, 0.01f, this->fwork[BOSS_MOVEMENT_SPEED], 0);
        } else {
            Math_SmoothStepToAngle(
                &this->rot_078.y,
                Math_RadToDeg(Math_Atan2F(this->vwork[0].x - this->obj.pos.x, this->vwork[0].z - this->obj.pos.z)),
                0.5f, 1.5f, 0.0001f);
            this->vel.x = SIN_DEG(this->rot_078.y) * this->fwork[BOSS_MOVEMENT_SPEED];
            this->vel.z = COS_DEG(this->rot_078.y) * this->fwork[BOSS_MOVEMENT_SPEED];
        }

        for (i = 0; i < 10; i++) {
            if (this->swork[i] != 0) {
                this->swork[i]--;
            }
        }

        if (this->swork[BOSS_HATCH_1_HP] != 0) {
            Math_SmoothStepToF(&this->fwork[BOSS_HATCH_1_ANGLE], this->fwork[BOSS_HATCH_1_ANGLE_TARGET], 0.03f, 0.5f,
                               0);
        }
        if (this->swork[BOSS_HATCH_2_HP] != 0) {
            Math_SmoothStepToF(&this->fwork[BOSS_HATCH_2_ANGLE], this->fwork[BOSS_HATCH_2_ANGLE_TARGET], 0.03f, 0.5f,
                               0);
        }
        if (this->swork[BOSS_HATCH_3_HP] != 0) {
            Math_SmoothStepToF(&this->fwork[BOSS_HATCH_3_ANGLE], this->fwork[BOSS_HATCH_3_ANGLE_TARGET], 0.03f, 0.5f,
                               0);
        }
        if (this->swork[BOSS_HATCH_4_HP] != 0) {
            Math_SmoothStepToF(&this->fwork[BOSS_HATCH_4_ANGLE], this->fwork[BOSS_HATCH_4_ANGLE_TARGET], 0.03f, 0.5f,
                               0);
        }
        if (this->swork[BOSS_CORE_HP] != 0) {
            Math_SmoothStepToF(&this->fwork[BOSS_CORE_LEVEL], this->fwork[BOSS_CORE_TARGET_LEVEL], 0.05f, 5.0f, 0);
        }

        this->info.hitbox[2] = this->fwork[BOSS_HATCH_1_ANGLE];
        this->info.hitbox[12] = this->fwork[BOSS_HATCH_2_ANGLE];
        this->info.hitbox[22] = this->fwork[BOSS_HATCH_3_ANGLE];
        this->info.hitbox[32] = this->fwork[BOSS_HATCH_4_ANGLE];
        this->info.hitbox[43] = this->fwork[BOSS_CORE_LEVEL] - 200.0f + -750.0f;
        this->info.hitbox[49] = this->fwork[BOSS_CORE_LEVEL] - 200.0f + -850.0f;
        this->info.hitbox[55] = this->fwork[BOSS_CORE_LEVEL] - 200.0f + -950.0f;
        this->info.hitbox[61] = this->fwork[BOSS_CORE_LEVEL] - 200.0f + -1200.0f;

        Katina_BossHandleDamage(this);
    }
}

bool Katina_BossOverrideLimbDraw(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* data) {
    Saucerer* boss = (Saucerer*) data;

    RCP_SetupDL(&gMasterDisp, SETUPDL_29);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 40, 40, 255, 255);

    switch (limbIndex) {
        case 1:
            rot->y += boss->fwork[BOSS_HATCH_1_ANGLE];

            if ((boss->swork[BOSS_HATCH_1_FLASH_TIMER] % 2) != 0) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_30);
            }

            if (boss->swork[BOSS_HATCH_1_HP] <= 0) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_57);
                gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                *dList = aKaDestroyedHatchDL;
            }
            break;

        case 2:
            rot->y += boss->fwork[BOSS_HATCH_2_ANGLE];

            if ((boss->swork[BOSS_HATCH_2_FLASH_TIMER] % 2) != 0) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_30);
            }

            if (boss->swork[BOSS_HATCH_2_HP] <= 0) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_57);
                gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                *dList = aDestroyedHatch2DL;
            }
            break;

        case 3:
            rot->y += boss->fwork[BOSS_HATCH_3_ANGLE];

            if ((boss->swork[BOSS_HATCH_3_FLASH_TIMER] % 2) != 0) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_30);
            }

            if (boss->swork[BOSS_HATCH_3_HP] <= 0) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_57);
                gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                *dList = aDestroyedHatch3DL;
            }
            break;

        case 4:
            rot->y -= boss->fwork[BOSS_HATCH_4_ANGLE];

            if ((boss->swork[BOSS_HATCH_4_FLASH_TIMER] % 2) != 0) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_30);
            }

            if (boss->swork[BOSS_HATCH_4_HP] <= 0) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_57);
                gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                *dList = aDestroyedHatch4DL;
            }
            break;

        case 9:
            pos->x -= boss->fwork[BOSS_CORE_LEVEL];

            if ((boss->swork[BOSS_CORE_FLASH_TIMER] % 2) != 0) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_30);
            }

            if (boss->swork[BOSS_CORE_HP] <= 0) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_57);
                gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                *dList = aDestroyedCoreDL;
            }
            break;

        case 10:
            if (boss->health < 0) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_57);
                gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                *dList = aKaDestroyedSaucererDL;
            }
            break;
    }
    return 0;
}

void Katina_BossDraw(Saucerer* this) {
    Vec3f jointTable[30];

    if (this->state != 0) {
        if (this->state < 20) {
            gSPFogPosition(gMasterDisp++, gFogNear, 1002);
        } else {
            gSPFogPosition(gMasterDisp++, gFogNear, 1006);
        }

        Matrix_RotateY(gGfxMatrix, this->fwork[BOSS_FWORK_13] * M_DTOR, MTXF_APPLY);

        Animation_GetFrameData(&D_KA_60105D8, 0, jointTable);
        Animation_DrawSkeleton(1, D_KA_6010744, jointTable, Katina_BossOverrideLimbDraw, NULL, this, &gIdentityMatrix);

        gSPFogPosition(gMasterDisp++, gFogNear, gFogFar);

        if (this->fwork[BOSS_LASER_LIGHT_SCALE] > 0.0f) {
            RCP_SetupDL(&gMasterDisp, SETUPDL_67);
            Matrix_Push(&gGfxMatrix);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
            gDPSetEnvColor(gMasterDisp++, 0, 255, 255, 255);
            Matrix_Translate(gGfxMatrix, 0.0f, 500.0f, 0.0f, MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, this->fwork[BOSS_LASER_LIGHT_SCALE], this->fwork[BOSS_LASER_LIGHT_SCALE],
                         this->fwork[BOSS_LASER_LIGHT_SCALE], MTXF_APPLY);
            Matrix_RotateX(gGfxMatrix, -90 * M_DTOR, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_1024AC0);
            Matrix_Pop(&gGfxMatrix);

            Matrix_Push(&gGfxMatrix);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 64);
            gDPSetEnvColor(gMasterDisp++, 0, 255, 255, 64);
            Matrix_Translate(gGfxMatrix, 0.0f, 500.0f, 0.0f, MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, this->fwork[BOSS_LASER_LIGHT_SCALE] * 3.0f,
                         this->fwork[BOSS_LASER_LIGHT_SCALE] * 3.0f, this->fwork[BOSS_LASER_LIGHT_SCALE] * 3.0f,
                         MTXF_APPLY);
            Matrix_RotateX(gGfxMatrix, -90 * M_DTOR, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_1024AC0);
            Matrix_Pop(&gGfxMatrix);
        }

        if (this->fwork[BOSS_LASER_LENGTH] > 0.0f) {
            RCP_SetupDL(&gMasterDisp, SETUPDL_41);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 128);
            Matrix_RotateX(gGfxMatrix, M_PI, MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, 0.3f, this->fwork[BOSS_LASER_LENGTH], 0.3f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_KA_600BFB0);
        }
    }
}

/**
 * Updates the arwing position of the teammates while
 * leaving the stage in the context of a succeeded mission.
 */
void Katina_SFTeamMissionAccomUpdate(ActorCutscene* this, s32 idx) {
    Actor_Initialize(this);

    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_ACTOR_CUTSCENE;

    this->obj.pos.x = D_i4_8019F260[idx + 1] + gPlayer[0].pos.x;
    this->obj.pos.y = D_i4_8019F26C[idx + 1] + gPlayer[0].pos.y;
    this->obj.pos.z = D_i4_8019F278[idx + 1] + gPlayer[0].pos.z;

    this->rot_0F4.y = D_i4_8019F284[idx + 1];

    this->fwork[KA_ACTOR_FWORK_1] = D_i4_8019F290[idx + 1];
    this->fwork[KA_ACTOR_FWORK_0] = 40.0f;

    Object_SetInfo(&this->info, this->obj.id);

    this->iwork[KA_ACTOR_IWORK_11] = 1;

    AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, this->sfxSource, 4);
}

/**
 * Updates the arwing position of the teammates while
 * fleeing the stage in the context of a failed mission.
 */
void Katina_SFTeamFleeUpdate(ActorCutscene* this, s32 idx) {
    Actor_Initialize(this);

    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_ACTOR_CUTSCENE;

    this->obj.pos.x = D_i4_8019F29C[idx + 1];
    this->obj.pos.y = D_i4_8019F2AC[idx + 1];
    this->obj.pos.z = D_i4_8019F2BC[idx + 1];

    this->rot_0F4.y = D_i4_8019F2CC[idx + 1];

    this->fwork[KA_ACTOR_FWORK_1] = D_i4_8019F2DC[idx + 1];
    this->fwork[KA_ACTOR_FWORK_0] = 40.0f;

    Object_SetInfo(&this->info, this->obj.id);

    this->iwork[KA_ACTOR_IWORK_11] = 1;

    AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, this->sfxSource, 4);
}

/**
 * Updates the actor positions that follow
 * fox at the level complete cutscene.
 */
void Katina_SFTeam_LevelComplete_Update(void) {
    s32 i;
    s32 numActors;
    ActorCutscene* actor = &gActors[0];

    Rand_SetSeed(1, 29100, 9786);

    if (gMissionStatus != MISSION_COMPLETE) {
        numActors = 19;
    } else {
        numActors = 2;
    }

    for (i = 0; i <= numActors; i++, actor++) {
        if ((D_i4_8019F2F0[i] >= gKaAllyKillCount) && ((i >= 3) || (gTeamShields[i + 1] > 0))) {
            Actor_Initialize(actor);
            actor->obj.status = OBJ_INIT;
            actor->obj.id = OBJ_ACTOR_CUTSCENE;

            actor->obj.pos.x =
                (sCsLevelCompleteActorPos[i].x * 0.5f) + gPlayer[0].pos.x + RAND_FLOAT_CENTERED_SEEDED(2000.0f);
            actor->obj.pos.y = (sCsLevelCompleteActorPos[i].y + gPlayer[0].pos.y) - RAND_FLOAT_SEEDED(1000.0f);
            actor->obj.pos.z = (sCsLevelCompleteActorPos[i].z + gPlayer[0].pos.z) + RAND_FLOAT_SEEDED(1000.0f);

            actor->rot_0F4.z = RAND_FLOAT_CENTERED_SEEDED(200.0f);

            actor->vwork[0].x = (sCsLevelCompleteActorPos[i].x * 0.5f) + gPlayer[0].pos.x;
            actor->vwork[0].y = sCsLevelCompleteActorPos[i].y + gPlayer[0].pos.y;
            actor->vwork[0].z = sCsLevelCompleteActorPos[i].z + gPlayer[0].pos.z;

            actor->state = 1;

            if (i >= 3) {
                actor->animFrame = 33;
            }

            Object_SetInfo(&actor->info, actor->obj.id);

            actor->iwork[KA_ACTOR_IWORK_11] = 1;

            AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, actor->sfxSource, 4);
        }
    }
}

void Katina_LevelComplete(Player* player) {
    s32 i;
    Saucerer* boss = &gBosses[KA_BOSS_SAUCERER];
    Vec3f src;
    Vec3f dest;
    f32 angle;

    player->wings.unk_10 = 0.0f;
    player->wings.unk_0C = 0.0f;
    player->wings.unk_08 = 0.0f;
    player->wings.unk_04 = 0.0f;

    player->aerobaticPitch = 0.0f;

    D_ctx_80177A48[0] = 1.0f;

    switch (player->csState) {
        case 0:
            Audio_StopSfxByBankAndSource(1, &player->sfxSource[0]);
            gCsFrameCount = 0;
            player->unk_234 = 1;

            player->pos.x = boss->obj.pos.x;
            player->pos.y = 800.0f;
            player->pos.z = boss->obj.pos.z;

            player->yRot_114 = player->xRot_120 = player->rot.x = player->camRoll = player->aerobaticPitch = 0.0f;
            player->rot.y = 120.0f;
            player->baseSpeed = 40.0f;

            gCsCamEyeX = boss->obj.pos.x + 5000.0f;
            gCsCamEyeY = 750.0f;
            gCsCamEyeZ = boss->obj.pos.z;
            gCsCamAtX = boss->obj.pos.x;
            gCsCamAtY = 1000.0f;
            gCsCamAtZ = boss->obj.pos.z;
            for (i = 10; i < ARRAY_COUNT(gActors); i++) {
                if (gActors[i].animFrame == 0) {
                    Object_Kill(&gActors[i].obj, gActors[i].sfxSource);
                }
            }

            player->csState++;

            if (gTeamShields[TEAM_ID_FALCO] > 0) {
                Katina_SFTeamMissionAccomUpdate(&gActors[1], 0);
            }

            if (gTeamShields[TEAM_ID_SLIPPY] > 0) {
                Katina_SFTeamMissionAccomUpdate(&gActors[2], 1);
            }

            if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                Katina_SFTeamMissionAccomUpdate(&gActors[3], 2);
            }
            break;

        case 1:
            gCsCamEyeX += 10.0f;
            gCsCamAtX = boss->obj.pos.x;
            gCsCamAtY = 1000.0f;
            gCsCamAtZ = boss->obj.pos.z;

            Math_SmoothStepToF(&player->rot.z, Math_SmoothStepToAngle(&player->rot.y, 283.0f, 0.1f, 3.0f, 0.0f) * 20.0f,
                               0.1f, 1.0f, 0.0f);

            for (i = 1; i < 4; i++) {
                angle = Math_SmoothStepToAngle(&gActors[i].rot_0F4.y, gActors[i].fwork[1], 0.1f, 3.0f, 0.0f);
                Math_SmoothStepToF(&gActors[i].rot_0F4.z, angle * 20.0f, 0.1f, 1.0f, 0.0f);
            }

            if (gCsFrameCount >= 200) {
                player->rot.x += 1.0f;
                player->rot.y += 1.0f;
                player->rot.z += 1.0f;
            }

            if (gCsFrameCount >= 225) {
                gActors[1].rot_0F4.x += 1.0f;
                gActors[1].rot_0F4.z += 1.0f;
                gActors[2].rot_0F4.x += 1.0f;
                gActors[2].rot_0F4.z -= 1.0f;
                gActors[3].rot_0F4.x += 1.0f;
                gActors[3].rot_0F4.z += 1.0f;
            }

            if (gCsFrameCount >= 225) {
                gFillScreenAlphaTarget = 255;
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
            }

            if (gCsFrameCount == 250) {
                player->csState = 2;
                Play_ClearObjectData();
                Audio_StopPlayerNoise(0);
                Audio_KillSfxBySource(&player->sfxSource[0]);
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
                player->pos.z = 150.0f;

                player->csState = 3;

                Audio_StartPlayerNoise(0);

                if (gMissionStatus != MISSION_COMPLETE) {
                    AUDIO_PLAY_BGM(NA_BGM_COURSE_CLEAR);
                } else {
                    AUDIO_PLAY_BGM(NA_BGM_COURSE_FAILURE);
                }

                gDrawGround = false;
                D_ctx_80177A48[1] = 0.0f;
                D_ctx_80177A48[2] = 0.0f;

                Katina_SFTeam_LevelComplete_Update();
                Play_dummy_MuteSfx();

                gCsFrameCount = 0;
            }
            break;

        case 3:
            gFillScreenAlphaTarget = 0;
            gFillScreenAlphaStep = 2;

            D_ctx_80177A48[1] -= D_ctx_80177A48[2];

            Matrix_RotateY(gCalcMatrix, D_ctx_80177A48[1] * M_DTOR, MTXF_NEW);

            src.x = -1000.0f;
            src.y = 0.0f;
            src.z = 0.0f;

            Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

            gCsCamEyeX = dest.x;
            gCsCamEyeY = 3600.0f;
            gCsCamEyeZ = 500.0f + dest.z;
            gCsCamAtX = 0.0f;
            gCsCamAtY = 3500.0f;
            gCsCamAtZ = player->pos.z + 500;

            if (gCsFrameCount > 1010) {
                player->baseSpeed += 2.0f;
                player->rot.x += 0.1f;
                Math_SmoothStepToF(&D_ctx_80177A48[2], 0.0f, 1.0f, 0.001f, 0);
                player->unk_190 = 2.0f;
                player->contrailScale += 0.04f;
                if (player->contrailScale > 0.6f) {
                    player->contrailScale = 0.6f;
                }
            } else {
                Math_SmoothStepToF(&D_ctx_80177A48[2], 0.2f, 1.0f, 0.005f, 0);
            }

            if (gCsFrameCount == 1050) {
                Audio_FadeOutAll(50);
            }

            if (gCsFrameCount > 1100) {
                gFillScreenAlphaTarget = 255;
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
                gFillScreenAlphaStep = 8;
                if (gFillScreenAlpha == 255) {
                    player->state_1C8 = PLAYERSTATE_1C8_NEXT;
                    player->csTimer = 0;
                    gFadeoutType = 4;
                    gLeveLClearStatus[LEVEL_KATINA] = Play_CheckMedalStatus(150) + 1;
                }
            }

            switch (gCsFrameCount) {
                case 190:
                    gLevelClearScreenTimer = 100;
                    break;

                case 350:
                    gShowLevelClearStatusScreen = 1;
                    break;

                case 550:
                    gShowLevelClearStatusScreen = 0;
                    break;

                case 1010:
                    AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, &player->sfxSource[0], 0);
                    player->unk_190 = player->unk_194 = 5.0f;
                    break;

                case 950:
                    gActors[0].state = 2;
                    break;

                case 970:
                    gActors[1].state = 2;
                    break;

                case 990:
                    gActors[2].state = 2;
                    break;

                case 570:
                    if (gMissionStatus != MISSION_COMPLETE) {
                        if (gKaAllyKillCount == 0) {
                            Radio_PlayMessage(gMsg_ID_18100, RCID_BILL);
                        } else {
                            Radio_PlayMessage(gMsg_ID_18090, RCID_BILL);
                        }
                    } else {
                        Radio_PlayMessage(gMsg_ID_18080, RCID_FOX);
                    }
                    break;

                case 700:
                    if (gMissionStatus != MISSION_COMPLETE) {
                        if (gKaAllyKillCount == 0) {
                            Radio_PlayMessage(gMsg_ID_18105, RCID_FOX);
                        } else {
                            Radio_PlayMessage(gMsg_ID_18095, RCID_FOX);
                        }
                    } else {
                        Radio_PlayMessage(gMsg_ID_18085, RCID_PEPPY);
                    }
                    break;
            }
            break;

        case 100:
            Katina_SFTeamFleeUpdate(&gActors[1], 0);
            if (gTeamShields[TEAM_ID_FALCO] > 0) {
                Katina_SFTeamFleeUpdate(&gActors[2], 1);
            }

            if (gTeamShields[TEAM_ID_SLIPPY] > 0) {
                Katina_SFTeamFleeUpdate(&gActors[3], 2);
            }

            if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                Katina_SFTeamFleeUpdate(&gActors[4], 3);
            }
            player->csState++;
            break;

        case 101:
            gActors[1].rot_0F4.y += 0.1f;
            gActors[1].rot_0F4.x += 0.1f;
            gActors[2].rot_0F4.y -= 0.007f;
            gActors[2].rot_0F4.x += 0.12f;
            gActors[3].rot_0F4.y -= 0.09f;
            gActors[3].rot_0F4.x += 0.09f;
            gActors[4].rot_0F4.y += 0.001f;
            gActors[4].rot_0F4.x += 0.08f;
            break;
    }

    Matrix_RotateY(gCalcMatrix, (player->yRot_114 + player->rot.y + 180.0f) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -((player->xRot_120 + player->rot.x) * M_DTOR), MTXF_APPLY);

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

    player->bankAngle = player->rot.z;
    player->trueZpos = player->pos.z;

    if (player->csState < 100) {
        Math_SmoothStepToF(&player->cam.eye.x, gCsCamEyeX, D_ctx_80177A48[0], 50000.0f, 0);
        Math_SmoothStepToF(&player->cam.eye.y, gCsCamEyeY, D_ctx_80177A48[0], 50000.0f, 0);
        Math_SmoothStepToF(&player->cam.eye.z, gCsCamEyeZ, D_ctx_80177A48[0], 50000.0f, 0);
        Math_SmoothStepToF(&player->cam.at.x, gCsCamAtX, D_ctx_80177A48[0], 50000.0f, 0);
        Math_SmoothStepToF(&player->cam.at.y, gCsCamAtY, D_ctx_80177A48[0], 50000.0f, 0);
        Math_SmoothStepToF(&player->cam.at.z, gCsCamAtZ, D_ctx_80177A48[0], 50000.0f, 0);
    }

    player->bobPhase += 10.0f;
    player->yBob = -SIN_DEG(player->bobPhase) * 0.3f;
    player->rockPhase += 8.0f;
    player->rockAngle = SIN_DEG(player->rockPhase);
}

// Makes your teammates fly towards the camera after defeating the Saucerer.
void Katina_SFTeamFlyTowardsCamera(ActorCutscene* this) {
    Vec3f src;
    Vec3f dest;

    switch (this->state) {
        case 1:
            Math_SmoothStepToF(&this->obj.pos.x, this->vwork[0].x, 0.02f, 2.0f, 0.0001f);
            Math_SmoothStepToF(&this->obj.pos.y, this->vwork[0].y, 0.02f, 2.0f, 0.0001f);
            Math_SmoothStepToF(&this->obj.pos.z, this->vwork[0].z, 0.02f, 2.0f, 0.0001f);
            Math_SmoothStepToF(&this->rot_0F4.z, 0.0f, 0.02f, 0.2f, 0.0001f);

            if ((this->animFrame != 0) && ((((s32) (this->index % 8U) * 10) + 800) < gCsFrameCount)) {
                this->state = 4;
            }
            break;

        case 2:
            this->state = 3;
            AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, this->sfxSource, 0);
            this->fwork[KA_ACTOR_FWORK_29] = 5.0f;

        case 3:
            this->iwork[KA_ACTOR_IWORK_11] = 2;
            this->fwork[KA_ACTOR_FWORK_0] += 2.0f;
            this->rot_0F4.x += 0.1f;
            this->fwork[KA_ACTOR_FWORK_21] += 0.4f;
            if (this->fwork[KA_ACTOR_FWORK_21] > 0.6f) {
                this->fwork[KA_ACTOR_FWORK_21] = 0.6f;
            }
            break;

        case 4:
            Math_SmoothStepToF(&this->rot_0F4.z, 120.0f, 0.1f, 3.0f, 0.0001f);
            this->obj.pos.x += this->fwork[KA_ACTOR_FWORK_1];
            this->obj.pos.y += this->fwork[KA_ACTOR_FWORK_1];
            this->fwork[KA_ACTOR_FWORK_1] -= 0.5f;
            break;
    }

    Matrix_RotateY(gCalcMatrix, (this->rot_0F4.y + 180.0f) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -(this->rot_0F4.x * M_DTOR), MTXF_APPLY);

    src.x = 0.0f;
    src.y = 0.0f;
    src.z = this->fwork[KA_ACTOR_FWORK_0];

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

    this->vel.x = dest.x;
    this->vel.y = dest.y;
    this->vel.z = dest.z;

    this->obj.rot.x = -this->rot_0F4.x;
    this->obj.rot.y = this->rot_0F4.y + 180.0f;
    this->obj.rot.z = -this->rot_0F4.z;
}

void Katina_801981F8(Actor* this) {
    s32 i;
    ActorAllRange* actor;
    Vec3f src;
    Vec3f dest;
    s32 pad;

    if ((this->timer_0C0 == 0) && (gPlayer[0].state_1C8 != PLAYERSTATE_1C8_STANDBY)) {
        this->timer_0C0 = 2;
        src.x = 0.0f;
        src.y = 0.0f;
        src.z = -5000.0f;

        if (gBosses[KA_BOSS_SAUCERER].state != 0) {
            src.z = -10000.0f;
        }

        // Spawn actors 10 to 20 as Cornerian Fighters, 20 to 29 as enemies.
        for (i = 0, actor = &gActors[AI360_10]; i < 20; i++, actor++) {
            if (actor->obj.status == OBJ_FREE) {
                Actor_Initialize(actor);

                actor->animFrame = D_i4_8019F430[i];

                if ((actor->animFrame != 0) || (gBosses[KA_BOSS_SAUCERER].state == 0)) {
                    actor->obj.status = OBJ_ACTIVE;
                    actor->obj.id = OBJ_ACTOR_ALLRANGE;

                    Matrix_RotateY(gCalcMatrix, this->counter_04E * 18.0f * M_DTOR, MTXF_NEW);
                    Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

                    actor->obj.pos.x = dest.x;
                    actor->obj.pos.y = RAND_FLOAT(1000.0f) + 300.0f;
                    actor->obj.pos.z = dest.z;

                    actor->rot_0F4.y = this->counter_04E * 18.0f;
                    actor->state = 1;
                    actor->aiType = i + AI360_10;
                    actor->aiIndex = D_i4_8019F444[i];
                    actor->rot_0F4.x = 3.0f;
                    actor->health = 24;

                    if (actor->animFrame >= 2) {
                        actor->health = 1000;
                    }

                    actor->iwork[KA_ACTOR_IWORK_11] = 1;
                    actor->drawShadow = true;

                    if (D_i4_801A0540 < 9600) {
                        actor->itemDrop = DROP_SILVER_RING_10p;
                    }

                    actor->timer_0C2 = 30;
                    Object_SetInfo(&actor->info, actor->obj.id);

                    if (actor->animFrame == 1) {
                        actor->info.targetOffset = 0.0f;
                        actor->info.bonus = 0;
                        AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, actor->sfxSource, 4);
                    }
                    actor->info.action = (ObjectFunc) Katina_EnemyUpdate;
                    actor->info.draw = (ObjectFunc) Katina_EnemyDraw;
                    this->counter_04E++;
                }
                break;
            }
        }
    }
}

void Katina_BillFighterInit(void) {
    ActorAllRange* actor = &gActors[AI360_BILL];

    Actor_Initialize(actor);

    actor->obj.status = OBJ_ACTIVE;
    actor->obj.pos.x = 0;
    actor->obj.pos.y = 1000.0f;
    actor->state = 1;
    actor->aiType = AI360_BILL;
    actor->aiIndex = AI360_10 + 17;
    actor->animFrame = 2;
    actor->health = 1000;
    actor->iwork[KA_ACTOR_IWORK_11] = 1;
    actor->drawShadow = true;
    actor->timer_0C2 = 30;
    actor->obj.id = OBJ_ACTOR_ALLRANGE;

    Object_SetInfo(&actor->info, actor->obj.id);

    actor->info.targetOffset = 0.0f;
    actor->info.bonus = 0;

    AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, actor->sfxSource, 4);
}

void Katina_UpdateEvents(ActorAllRange* this) {
    s32 pad[4];
    f32 D_i4_8019F494[5] = { -200.0f, -100.0f, -0.0f, 100.0f, 200.0f };

    switch (this->state) {
        case 0:
            gProjectFar = 30000.0f;
            D_i4_801A0540 = 0;
            gKaKilledAlly = gKaAllyKillCount = 0;
            this->state = 2;

            if (gAllRangeCheckpoint != 0) {
                gHitCount = gSavedHitCount;

                gBosses[KA_BOSS_SAUCERER].state = 6;
                gBosses[KA_BOSS_SAUCERER].obj.pos.x = 0.0f;
                gBosses[KA_BOSS_SAUCERER].obj.pos.z = 0.0f;
                gBosses[KA_BOSS_SAUCERER].obj.pos.y = 2000.0f;

                AUDIO_PLAY_SFX(NA_SE_KA_UFO_ENGINE, gBosses[KA_BOSS_SAUCERER].sfxSource, 0);

                gAllRangeEventTimer = 20000;

                gBosses[KA_BOSS_SAUCERER].swork[BOSS_CORE_TIMER] = 5760;

                gKaKilledAlly = 1;

                AUDIO_PLAY_BGM(NA_BGM_BOSS_KA);
            }
            Katina_BillFighterInit();

        case 2:
            D_i4_801A0540++;
            PRINTF("KT_time %d\n", D_i4_801A0540);
            Katina_801981F8(this);
            break;

        case 6:
            gActors[AI360_FALCO].aiIndex = AI360_FOX;
            gActors[AI360_FALCO].state = 2;
            gActors[AI360_SLIPPY].aiIndex = AI360_FOX;
            gActors[AI360_SLIPPY].state = 2;
            gActors[AI360_PEPPY].aiIndex = AI360_FOX;
            gActors[AI360_PEPPY].state = 2;
            break;
    }

    if (gBosses[KA_BOSS_SAUCERER].state < 15) {
        switch (gAllRangeEventTimer) {
            case -500:
                Radio_PlayMessage(gMsg_ID_18005, RCID_BILL);
                break;

            case -390:
                Radio_PlayMessage(gMsg_ID_18006, RCID_FOX);
                break;

            case -220:
                Radio_PlayMessage(gMsg_ID_18007, RCID_BILL);
                break;

            case -30:
                Radio_PlayMessage(gMsg_ID_18010, RCID_SLIPPY);
                break;
        }

        if (gBosses[KA_BOSS_SAUCERER].state == 12) {
            if (((gAllRangeEventTimer % 256) == 0) && (Rand_ZeroOne() < 0.5f)) {
                AllRange_PlayMessage(gMsg_ID_18060, RCID_BILL);
            }
        } else if ((gAllRangeEventTimer > 500) && (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_ACTIVE) &&
                   ((gAllRangeEventTimer % 512) == 0)) {
            switch (RAND_INT(3.99f)) {
                case 0:
                    AllRange_PlayMessage(gMsg_ID_18020, RCID_BILL);
                    break;

                case 1:
                    AllRange_PlayMessage(gMsg_ID_18021, RCID_BILL);
                    break;

                case 2:
                    AllRange_PlayMessage(gMsg_ID_18022, RCID_BILL);
                    break;

                case 3:
                    AllRange_PlayMessage(gMsg_ID_18025, RCID_FALCO);
                    break;
            }
        }
    }
}

void Katina_Init(void) {
    Frontlinebase* base = &gBosses[KA_BOSS_BASE];
    Saucerer* saucerer = &gBosses[KA_BOSS_SAUCERER];

    Boss_Initialize(saucerer);
    saucerer->obj.status = OBJ_INIT;
    saucerer->obj.pos.x = -15000.0f;
    saucerer->obj.pos.y = 3240.0f;
    saucerer->obj.pos.z = 15000.0f;
    saucerer->obj.id = OBJ_BOSS_KA;
    Object_SetInfo(&saucerer->info, saucerer->obj.id);

    Boss_Initialize(base);
    base->obj.status = OBJ_INIT;
    base->obj.pos.x = 0.0f;
    base->obj.pos.y = 0.0f;
    base->obj.pos.z = 0.0f;
    base->obj.id = OBJ_BOSS_KA_BASE;
    Object_SetInfo(&base->info, base->obj.id);
}

bool Katina_IsActorCloseToBase(Actor* this, f32 posX, f32 posY) {
    if ((fabsf(gBosses[KA_BOSS_BASE].obj.pos.x - (this->obj.pos.x + (posX * 650.0f))) < 1500.0f) &&
        (fabsf(gBosses[KA_BOSS_BASE].obj.pos.z - (this->obj.pos.z + (posY * 650.0f))) < 1500.0f) &&
        (fabsf(gBosses[KA_BOSS_BASE].obj.pos.y - this->obj.pos.y) < 700.0f)) {
        return true;
    } else {
        return false;
    }
}

void Katina_EnemyUpdate(ActorAllRange* this) {
    bool actorCloseToBase;
    s32 state;
    s32 pad;
    f32 xVel;
    f32 yVel;
    f32 zVel;
    f32 xDist;
    f32 yDist;
    f32 xRand;
    f32 yRand;
    f32 zRand;
    f32 xAngle;
    f32 yAngle;
    f32 zAngle;
    f32 xPos;
    f32 yPos;
    f32 zPos;
    f32 xSin;
    f32 ySin;
    f32 xCos;
    f32 yCos;
    RadarMark* radarMark;
    s32 pad2[9];

    zPos = 0.0f;
    yPos = 0.0f;
    xPos = 0.0f;

    Math_SmoothStepToF(&this->fwork[KA_ACTOR_FWORK_10], 0.0f, 0.1f, 0.2f, 0.1f);
    Math_SmoothStepToF(&this->fwork[KA_ACTOR_FWORK_9], this->fwork[KA_ACTOR_FWORK_10], 0.1f, 2.0f, 0.1f);

    state = 0;

    this->iwork[KA_ACTOR_IWORK_5] = 0;

    switch (this->state) {
        case 1:
            this->fwork[KA_ACTOR_FWORK_1] = 40.0f;
            if (this->timer_0BC == 0) {
                this->state = 3;
            }
            break;

        case 2:
            state = 1;
            xDist = fabsf(this->fwork[KA_ACTOR_FWORK_4] - this->obj.pos.x);
            yDist = fabsf(this->fwork[KA_ACTOR_FWORK_6] - this->obj.pos.z);

            if (this->aiIndex <= -1) {
                this->state = 3;
            } else {
                if (this->aiType >= AI360_10) {
                    xPos = SIN_DEG((this->index * 45) + gGameFrameCount) * 200.0f;
                    yPos = COS_DEG((this->index * 45) + (gGameFrameCount * 2)) * 200.0f;
                    zPos = SIN_DEG((this->index * 45) + gGameFrameCount) * 200.0f;
                }

                this->fwork[KA_ACTOR_FWORK_4] = gActors[this->aiIndex].obj.pos.x + xPos;
                this->fwork[KA_ACTOR_FWORK_5] = gActors[this->aiIndex].obj.pos.y + yPos;
                this->fwork[KA_ACTOR_FWORK_6] = gActors[this->aiIndex].obj.pos.z + zPos;
                this->fwork[KA_ACTOR_FWORK_1] = gActors[this->aiIndex].fwork[0] + 10.0f;

                if (this->fwork[KA_ACTOR_FWORK_1] < 30.0f) {
                    this->fwork[KA_ACTOR_FWORK_1] = 30.0f;
                }

                this->fwork[KA_ACTOR_FWORK_3] = 1.4f;

                if (this->aiIndex > -1) {
                    if (yDist < 800.0f) {
                        if (xDist < 800.0f) {
                            this->fwork[KA_ACTOR_FWORK_1] = gActors[this->aiIndex].fwork[0] - 5.0f;
                        }
                    } else if (this->timer_0C0 == 0) {
                        this->timer_0C0 = RAND_INT(200.0f) + 200;
                        this->fwork[KA_ACTOR_FWORK_10] = 20.0f;
                    }

                    if ((yDist < 1500.0f) && (xDist < 1500.0f)) {
                        this->iwork[KA_ACTOR_IWORK_4]++;
                        this->iwork[KA_ACTOR_IWORK_5] = 1;

                        if ((((this->index + gGameFrameCount) & 11) == 0) && (Rand_ZeroOne() < 0.1f) &&
                            func_360_80031900(this) && (gActors[0].state == 2)) {
                            this->iwork[KA_ACTOR_IWORK_0] = true;
                        }
                    } else {
                        this->iwork[KA_ACTOR_IWORK_4] = 0;
                    }

                    if ((this->aiIndex >= AI360_FALCO) &&
                        ((gActors[this->aiIndex].obj.status == OBJ_DYING) || (gActors[this->aiIndex].state == 6) ||
                         gActors[this->aiIndex].obj.status == OBJ_FREE)) {
                        this->state = 3;
                    }
                }
            }
            break;

        case 3:
            state = 1;

            if (this->timer_0BC == 0) {
                this->fwork[KA_ACTOR_FWORK_3] = 1.2f;
                this->fwork[KA_ACTOR_FWORK_1] = 40.0f;
                yRand = RAND_FLOAT(1000.0f);

                if (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_STANDBY) {
                    xRand = RAND_FLOAT_CENTERED(5000.0f);
                    zRand = RAND_FLOAT_CENTERED(5000.0f);
                } else {
                    xRand = RAND_FLOAT_CENTERED(10000.0f);
                    zRand = RAND_FLOAT_CENTERED(10000.0f);
                }

                this->fwork[KA_ACTOR_FWORK_4] = xRand;
                this->fwork[KA_ACTOR_FWORK_5] = yRand;
                this->fwork[KA_ACTOR_FWORK_6] = zRand;
                this->timer_0BC = RAND_INT(20.0f) + 10;
            }

            if (this->timer_0C0 == 0) {
                this->timer_0C0 = RAND_INT(200.0f) + 200;
                this->fwork[KA_ACTOR_FWORK_10] = 30.0f;
            }

            if ((this->aiIndex >= AI360_FALCO) && (gActors[this->aiIndex].obj.status == OBJ_ACTIVE)) {
                this->state = 2;
                this->iwork[KA_ACTOR_IWORK_2] = AI360_FOX;
            }
            break;
    }

    xSin = SIN_DEG(this->obj.rot.x);
    xCos = COS_DEG(this->obj.rot.x);
    ySin = SIN_DEG(this->obj.rot.y);
    yCos = COS_DEG(this->obj.rot.y);

    if (state != 0) {
        xRand = this->fwork[KA_ACTOR_FWORK_4] - this->obj.pos.x;
        yRand = this->fwork[KA_ACTOR_FWORK_5] - this->obj.pos.y;
        zRand = this->fwork[KA_ACTOR_FWORK_6] - this->obj.pos.z;

        if (((this->index + gGameFrameCount) % 8) == 0) {
            this->fwork[KA_ACTOR_FWORK_19] = Math_RadToDeg(Math_Atan2F(xRand, zRand));
            xAngle = sqrtf(SQ(xRand) + SQ(zRand));
            this->fwork[KA_ACTOR_FWORK_20] = Math_RadToDeg(Math_Atan2F(yRand, xAngle));
        }

        xAngle = this->fwork[KA_ACTOR_FWORK_20];

        actorCloseToBase = Katina_IsActorCloseToBase(this, ySin, yCos);

        if (actorCloseToBase) {
            xAngle += 40.0f * actorCloseToBase;
            if (xAngle >= 360.0f) {
                xAngle -= 360.0f;
            }

            if (xAngle < 0.0f) {
                xAngle += 360.0f;
            }
        } else if ((this->obj.pos.y < (gGroundHeight + 50.0f)) && (xAngle > 180.0f)) {
            xAngle = 0.0f;
            this->rot_0F4.x = 0.0f;
        }

        Math_SmoothStepToAngle(&this->rot_0F4.x, xAngle, 0.5f, this->fwork[KA_ACTOR_FWORK_2], 0.0001f);

        yAngle = Math_SmoothStepToAngle(&this->rot_0F4.y, this->fwork[KA_ACTOR_FWORK_19], 0.5f,
                                        this->fwork[KA_ACTOR_FWORK_2], 0.0001f) *
                 30.0f;

        if (yAngle < 0.0f) {
            zAngle = yAngle * -1.0f;
        } else {
            zAngle = 360.0f - yAngle;
        }
        Math_SmoothStepToAngle(&this->obj.rot.z, zAngle, 0.1f, 3.0f, 0.01f);
    }
    this->obj.rot.x = -this->rot_0F4.x;
    this->obj.rot.y = this->rot_0F4.y;

    Math_SmoothStepToF(&this->fwork[KA_ACTOR_FWORK_0], this->fwork[KA_ACTOR_FWORK_1], 0.2f, 1.0f, 0.1f);
    Math_SmoothStepToF(&this->fwork[KA_ACTOR_FWORK_2], this->fwork[KA_ACTOR_FWORK_3], 1.0f, 0.1f, 0.1f);

    zVel = (this->fwork[KA_ACTOR_FWORK_0] + this->fwork[KA_ACTOR_FWORK_9]) * xCos;
    yVel = (this->fwork[KA_ACTOR_FWORK_0] + this->fwork[KA_ACTOR_FWORK_9]) * -xSin;
    xVel = ySin * zVel;
    zVel = yCos * zVel;

    this->vel.x = this->fwork[KA_ACTOR_FWORK_13] + xVel;
    this->vel.y = this->fwork[KA_ACTOR_FWORK_14] + yVel;
    this->vel.z = this->fwork[KA_ACTOR_FWORK_12] + zVel;

    this->fwork[KA_ACTOR_FWORK_13] -= this->fwork[KA_ACTOR_FWORK_13] * 0.1f;
    this->fwork[KA_ACTOR_FWORK_14] -= this->fwork[KA_ACTOR_FWORK_14] * 0.1f;
    this->fwork[KA_ACTOR_FWORK_12] -= this->fwork[KA_ACTOR_FWORK_12] * 0.1f;

    if ((this->obj.pos.y < gGroundHeight + 40.0f) && (this->vel.y < 0.0f)) {
        this->obj.pos.y = gGroundHeight + 40.0f;
        this->vel.y = 0.0f;
    }

    if (this->iwork[KA_ACTOR_IWORK_0]) {
        this->iwork[KA_ACTOR_IWORK_0] = false;

        yVel = -xSin * 200.0f * 0.5f;
        xVel = +xCos * 200.0f * 0.5f;
        zVel = +xCos * 200.0f * 0.5f;

        Actor_SpawnPlayerLaser(this->aiType, this->obj.pos.x + (ySin * xVel * 1.5f), this->obj.pos.y + (yVel * 1.5f),
                               this->obj.pos.z + (yCos * zVel * 1.5f), ySin * (xCos * 200.0f * 0.5f),
                               -xSin * 200.0f * 0.5f, yCos * (xCos * 200.0f * 0.5f), this->obj.rot.x, this->obj.rot.y,
                               this->obj.rot.z);
    }

    ActorAllRange_ApplyDamage(this);

    radarMark = &gRadarMarks[this->index];
    radarMark->status = 1;
    radarMark->type = this->aiType;
    radarMark->pos.x = this->obj.pos.x;
    radarMark->pos.y = this->obj.pos.y;
    radarMark->pos.z = this->obj.pos.z;
    radarMark->yRot = this->rot_0F4.y + 180.0f;

    if (this->iwork[KA_ACTOR_IWORK_8] != 0) {
        this->iwork[KA_ACTOR_IWORK_8]--;
    }
}

void Katina_EnemyDraw(ActorAllRange* this) {
    s32 pad3[3];
    f32 angle;
    Vec3f D_i4_8019F4A8 = { 0.0f, 0.0f, 0.0f };
    Vec3f pad[30];

    if (((this->index + gSysFrameCount) % 8) == 0) {
        this->iwork[KA_ACTOR_LOW_POLY] = true;
        if ((fabsf(this->obj.pos.x - gPlayer[0].cam.eye.x) < 4500.0f) &&
            (fabsf(this->obj.pos.z - gPlayer[0].cam.eye.z) < 4500.0f)) {
            this->iwork[KA_ACTOR_LOW_POLY] = false;
        }
    }

    if ((this->iwork[KA_ACTOR_IWORK_8] != 0) && (this->aiType < AI360_GREAT_FOX)) {
        angle = SIN_DEG(this->iwork[KA_ACTOR_IWORK_8] * 400.0f) * this->iwork[KA_ACTOR_IWORK_8];
        Matrix_RotateY(gGfxMatrix, M_DTOR * angle, MTXF_APPLY);
        Matrix_RotateX(gGfxMatrix, M_DTOR * angle, MTXF_APPLY);
        Matrix_RotateZ(gGfxMatrix, M_DTOR * angle, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
    }

    if (this->iwork[KA_ACTOR_LOW_POLY]) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_34);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 80, 64, 64, 255);
    } else {
        RCP_SetupDL(&gMasterDisp, SETUPDL_29);
    }

    if ((this->timer_0C6 % 2) == 0) {
        gSPFogPosition(gMasterDisp++, gFogNear, 1005);
    }

    switch (this->animFrame) {
        case 0:
            if (this->iwork[KA_ACTOR_LOW_POLY]) {
                gSPDisplayList(gMasterDisp++, aKaEnemy1LowPolyDL);
            } else {
                gSPDisplayList(gMasterDisp++, aKaEnemy1DL);
            }
            break;

        case 1:
            gSPDisplayList(gMasterDisp++, aKaCornerianFighterDL);
            Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -60.0f, MTXF_APPLY);
            Actor_DrawEngineGlow(this, 0);
            break;
    }
}
