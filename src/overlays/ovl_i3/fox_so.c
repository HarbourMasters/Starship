/*
 * File: fox_so.c
 * System: Solar
 * Description: Level: Solar
 */

#include "global.h"
#include "assets/ast_bg_planet.h"
#include "assets/ast_solar.h"

typedef void (*SoVulkainfunc)(SoVulkain*);

typedef enum {
    /*  0 */ SO_SWK_0,
    /*  1 */ SO_SWK_1,
    /*  2 */ SO_SWK_2,
    /*  3 */ SO_SWK_3,
    /*  4 */ SO_SWK_4,
    /*  5 */ SO_SWK_5,
    /*  6 */ SO_SWK_6,
    /*  7 */ SO_SWK_7,
    /*  8 */ SO_SWK_8,
    /*  9 */ SO_SWK_9,
    /* 10 */ SO_SWK_10,
    /* 11 */ SO_SWK_11,
    /* 12 */ SO_SWK_12,
    /* 13 */ SO_SWK_13,
    /* 14 */ SO_SWK_14,
    /* 15 */ SO_SWK_15,
    /* 16 */ SO_SWK_16,
    /* 17 */ SO_SWK_17,
    /* 18 */ SO_SWK_18,
    /* 19 */ SO_SWK_19,
    /* 20 */ SO_SWK_20,
    /* 21 */ SO_SWK_21,
    /* 22 */ SO_SWK_22,
    /* 23 */ SO_SWK_23,
    /* 24 */ SO_SWK_24,
    /* 25 */ SO_SWK_25,
    /* 26 */ SO_SWK_26,
    /* 27 */ SO_SWK_27,
    /* 28 */ SO_SWK_28,
    /* 29 */ SO_SWK_29,
    /* 30 */ SO_SWK_30,
    /* 31 */ SO_SWK_31,
    /* 32 */ SO_SWK_32,
    /* 33 */ SO_SWK_33,
    /* 34 */ SO_SWK_34,
    /* 35 */ SO_SWK_35,
    /* 36 */ SO_SWK_36,
    /* 37 */ SO_SWK_37,
    /* 38 */ SO_SWK_38,
    /* 39 */ SO_SWK_39,
    /* 40 */ SO_SWK_MAX,
} SoVulkainswork;

typedef enum {
    /*  0 */ SO_FWK_0,
    /*  1 */ SO_FWK_1,
    /*  2 */ SO_FWK_2,
    /*  3 */ SO_FWK_3,
    /*  4 */ SO_FWK_4,
    /*  5 */ SO_FWK_5,
    /*  6 */ SO_FWK_6,
    /*  7 */ SO_FWK_7,
    /*  8 */ SO_FWK_8,
    /*  9 */ SO_FWK_9,
    /* 10 */ SO_FWK_10,
    /* 11 */ SO_FWK_11,
    /* 12 */ SO_FWK_12,
    /* 13 */ SO_FWK_13,
    /* 14 */ SO_FWK_14,
    /* 15 */ SO_FWK_15,
    /* 16 */ SO_FWK_16,
    /* 17 */ SO_FWK_17,
    /* 18 */ SO_FWK_18,
    /* 19 */ SO_FWK_19,
    /* 20 */ SO_FWK_20,
    /* 21 */ SO_FWK_21,
    /* 22 */ SO_FWK_22,
    /* 23 */ SO_FWK_23,
    /* 24 */ SO_FWK_24,
    /* 25 */ SO_FWK_25,
    /* 26 */ SO_FWK_26,
    /* 27 */ SO_FWK_27,
    /* 28 */ SO_FWK_28,
    /* 29 */ SO_FWK_29,
    /* 30 */ SO_FWK_30,
    /* 31 */ SO_FWK_31,
    /* 32 */ SO_FWK_32,
    /* 33 */ SO_FWK_33,
    /* 34 */ SO_FWK_34,
    /* 35 */ SO_FWK_35,
    /* 36 */ SO_FWK_36,
    /* 37 */ SO_FWK_37,
    /* 38 */ SO_FWK_38,
    /* 39 */ SO_FWK_39,
    /* 40 */ SO_FWK_40,
    /* 41 */ SO_FWK_41,
    /* 42 */ SO_FWK_42,
    /* 43 */ SO_FWK_43,
    /* 44 */ SO_FWK_44,
    /* 45 */ SO_FWK_45,
    /* 46 */ SO_FWK_46,
    /* 47 */ SO_FWK_47,
    /* 48 */ SO_FWK_48,
    /* 49 */ SO_FWK_49,
    /* 50 */ SO_FWK_MAX,
} SoVulkainfwork;

typedef enum {
    /*  0 */ SO_VWK_0,
    /*  1 */ SO_VWK_1,
    /*  2 */ SO_VWK_2,
    /*  3 */ SO_VWK_3,
    /*  4 */ SO_VWK_4,
    /*  5 */ SO_VWK_5,
    /*  6 */ SO_VWK_6,
    /*  7 */ SO_VWK_7,
    /*  8 */ SO_VWK_8,
    /*  9 */ SO_VWK_9,
    /* 10 */ SO_VWK_10,
    /* 11 */ SO_VWK_11,
    /* 12 */ SO_VWK_12,
    /* 13 */ SO_VWK_13,
    /* 14 */ SO_VWK_14,
    /* 15 */ SO_VWK_15,
    /* 16 */ SO_VWK_16,
    /* 17 */ SO_VWK_17,
    /* 18 */ SO_VWK_18,
    /* 19 */ SO_VWK_19,
    /* 20 */ SO_VWK_20,
    /* 21 */ SO_VWK_21,
    /* 22 */ SO_VWK_22,
    /* 23 */ SO_VWK_23,
    /* 24 */ SO_VWK_24,
    /* 25 */ SO_VWK_25,
    /* 26 */ SO_VWK_26,
    /* 27 */ SO_VWK_27,
    /* 28 */ SO_VWK_28,
    /* 29 */ SO_VWK_29,
    /* 30 */ SO_VWK_30,
    /* 31 */ SO_VWK_31,
    /* 32 */ SO_VWK_32,
    /* 33 */ SO_VWK_33,
    /* 34 */ SO_VWK_34,
    /* 35 */ SO_VWK_35,
    /* 36 */ SO_VWK_36,
    /* 37 */ SO_VWK_37,
    /* 38 */ SO_VWK_38,
    /* 39 */ SO_VWK_39,
    /* 40 */ SO_VWK_40,
    /* 41 */ SO_VWK_41,
    /* 42 */ SO_VWK_42,
    /* 43 */ SO_VWK_43,
    /* 44 */ SO_VWK_44,
    /* 45 */ SO_VWK_45,
    /* 46 */ SO_VWK_46,
    /* 47 */ SO_VWK_47,
    /* 48 */ SO_VWK_48,
    /* 49 */ SO_VWK_49,
    /* 50 */ SO_VWK_MAX,
} SoVulkainvwork;

void Solar_801A239C(SoVulkain* this);
void Solar_801A2C3C(SoVulkain* this);
void Solar_801A3468(SoVulkain* this);
void Solar_801A48B8(SoVulkain* this);
void Solar_801A4EC0(SoVulkain* this);
void Solar_801A8DB8(Vec3f* pos, u32 sfxId, f32 zVel);

s32 D_i3_801C2740[10];
f32 D_i3_801C2768[14];
s32 D_i3_801C27A0[8]; // unused? part of previous?

void Solar_8019E7F0(Effect392* this, f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    Effect_Initialize(this);
    this->obj.status = OBJ_ACTIVE;
    this->obj.id = OBJ_EFFECT_392;
    this->state = 3;

    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;

    this->obj.rot.z = 180.0f;

    if (Rand_ZeroOne() < 0.5f) {
        this->obj.rot.y = 180.0f;
    }

    this->unk_44 = 112;
    this->scale2 = scale2;
    this->vel.y = 5.0f;
    Object_SetInfo(&this->info, this->obj.id);
    this->info.unk_14 = 0;
}

void Solar_8019E8B8(f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Solar_8019E7F0(&gEffects[i], xPos, yPos, zPos, scale2);
            break;
        }
    }
}

void Solar_8019E920(Effect392* this, f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 scale2,
                    s32 state) {
    Effect_Initialize(this);
    this->obj.status = OBJ_ACTIVE;
    this->obj.id = OBJ_EFFECT_392;

    this->state = state;
    if (state == 2) {
        this->timer_50 = 30;
        this->unk_4C = 3;
    }
    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;
    this->vel.x = xVel;
    this->vel.y = yVel;
    this->vel.z = zVel;
    this->obj.rot.z = RAND_FLOAT(360.0f);
    this->unk_44 = 176;
    this->scale2 = scale2;
    Object_SetInfo(&this->info, this->obj.id);
}

void Solar_8019E9F4(f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 scale2, s32 unk4E) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 34; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Solar_8019E920(&gEffects[i], xPos, yPos, zPos, xVel, yVel, zVel, scale2, unk4E);
            break;
        }
    }
}

void Solar_SoWave_Update(SoWave* this) {
    f32 sp34;
    s32 sp30;

    if (this->state == 0) {
        this->vel.z = 20.0f - gPathVelZ;
        this->fwork[0] = 12.0f;
    } else {
        this->vel.z = this->fwork[1] - gPathVelZ;
        if (this->state == 2) {
            Math_SmoothStepToF(&this->obj.pos.x, gPlayer[0].pos.x, 1.0f, 100.0f, 10.0f);
        } else {
            this->fwork[0] = 14.0f;
        }
    }

    if ((this->work_046 == 0) || (this->work_046 == 1)) {
        this->work_046 = 3;
        Object_SetSfxSourceToPos(this->sfxSource, &this->obj.pos);
        AUDIO_PLAY_SFX(NA_SE_OB_MAGMA_WAVE, this->sfxSource, 0);
    }

    if (Play_CheckDynaFloorCollision(&sp34, &sp30, this->obj.pos.x, -100.0f, this->obj.pos.z)) {
        D_ctx_801782EC[sp30] = this->fwork[0];
        D_ctx_801782EC[sp30 + 1] = this->fwork[0] * 0.95f;
        D_ctx_801782EC[sp30 - 1] = this->fwork[0] * 0.95f;
        D_ctx_801782EC[sp30 + 2] = this->fwork[0] * 0.9f;
        D_ctx_801782EC[sp30 - 2] = this->fwork[0] * 0.9f;
        D_ctx_801782EC[sp30 + 3] = this->fwork[0] * 0.8f;
        D_ctx_801782EC[sp30 - 3] = this->fwork[0] * 0.8f;

        if (this->state != 2) {
            D_ctx_801782EC[sp30 + 4] = this->fwork[0] * 0.65f;
            D_ctx_801782EC[sp30 - 4] = this->fwork[0] * 0.65f;
            D_ctx_801782EC[sp30 + 5] = this->fwork[0] * 0.45f;
            D_ctx_801782EC[sp30 - 5] = this->fwork[0] * 0.45f;
            D_ctx_801782EC[sp30 + 6] = this->fwork[0] * 0.2f;
            D_ctx_801782EC[sp30 - 6] = this->fwork[0] * 0.2f;
            D_ctx_801782EC[sp30 + 7] = this->fwork[0] * 0.1f;
            D_ctx_801782EC[sp30 - 7] = this->fwork[0] * 0.1f;
        } else {
            D_ctx_801782EC[sp30 + 4] = this->fwork[0] * 0.75f;
            D_ctx_801782EC[sp30 - 4] = this->fwork[0] * 0.75f;
            D_ctx_801782EC[sp30 + 5] = this->fwork[0] * 0.7f;
            D_ctx_801782EC[sp30 - 5] = this->fwork[0] * 0.7f;
            D_ctx_801782EC[sp30 + 6] = this->fwork[0] * 0.65f;
            D_ctx_801782EC[sp30 - 6] = this->fwork[0] * 0.65f;
            D_ctx_801782EC[sp30 + 7] = this->fwork[0] * 0.6f;
            D_ctx_801782EC[sp30 - 7] = this->fwork[0] * 0.6f;
            D_ctx_801782EC[sp30 + 8] = this->fwork[0] * 0.55f;
            D_ctx_801782EC[sp30 - 8] = this->fwork[0] * 0.55f;
            D_ctx_801782EC[sp30 + 9] = this->fwork[0] * 0.4f;
            D_ctx_801782EC[sp30 - 9] = this->fwork[0] * 0.4f;
            D_ctx_801782EC[sp30 + 10] = this->fwork[0] * 0.3f;
            D_ctx_801782EC[sp30 - 10] = this->fwork[0] * 0.3f;
            D_ctx_801782EC[sp30 + 11] = this->fwork[0] * 0.2f;
            D_ctx_801782EC[sp30 - 11] = this->fwork[0] * 0.2f;
            D_ctx_801782EC[sp30 + 12] = this->fwork[0] * 0.1f;
            D_ctx_801782EC[sp30 - 12] = this->fwork[0] * 0.1f;
        }
    }

    switch (this->dmgType) {
        case 3:
            Solar_801A8DB8(&this->obj.pos, NA_SE_OB_MAGMA_WAVE, this->vel.z);
            /* fallthrough */
        case 2:
            Object_Kill(&this->obj, this->sfxSource);
            break;
    }
}

void Solar_8019EF30(Actor* this, f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel) {
    Actor_Initialize(this);
    this->obj.status = OBJ_ACTIVE;
    this->obj.id = OBJ_ACTOR_SO_ROCK_1;

    if (Rand_ZeroOne() < 0.1f) {
        this->obj.id = OBJ_ACTOR_SO_ROCK_2;
    }

    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;

    this->rot_0F4.x = RAND_FLOAT(360.0f);

    this->vel.x = xVel;
    this->vel.y = yVel;
    this->vel.z = zVel;

    this->state = 2;
    this->timer_0C2 = 8;

    Object_SetInfo(&this->info, this->obj.id);

    if (gBossActive) {
        this->info.bonus = 0;
    }
    AUDIO_PLAY_SFX(NA_SE_OB_SOROCK_APPEAR, this->sfxSource, 0);
}

void Solar_8019F038(f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel) {
    s32 i;

    for (i = 4; i < ARRAY_COUNT(gActors); i++) {
        if (gActors[i].obj.status == OBJ_FREE) {
            Solar_8019EF30(&gActors[i], xPos, yPos, zPos, xVel, yVel, zVel);
            break;
        }
    }
}

void Solar_8019F0B0(SoRock1* this, f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel) {
    Actor_Initialize(this);
    this->obj.status = OBJ_ACTIVE;
    this->obj.id = OBJ_ACTOR_SO_ROCK_3;

    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;
    this->rot_0F4.x = RAND_FLOAT(360.0f);
    this->vel.x = xVel;
    this->vel.y = yVel;
    this->vel.z = zVel;
    this->state = 2;
    this->timer_0C2 = 8;

    Object_SetInfo(&this->info, this->obj.id);

    if (gBossActive) {
        this->info.bonus = 0;
    }
    AUDIO_PLAY_SFX(NA_SE_OB_SOROCK_APPEAR, this->sfxSource, 0);
}

void Solar_8019F194(f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel) {
    s32 i;

    for (i = 4; i < ARRAY_COUNT(gActors); i++) {
        if (gActors[i].obj.status == OBJ_FREE) {
            Solar_8019F0B0(&gActors[i], xPos, yPos, zPos, xVel, yVel, zVel);
            break;
        }
    }
}

f32 D_i3_801BF8E0[4] = { 10.0f, 6.0f, -6.0f, -10.0f };
Vec3f D_i3_801BF8F0[4] = {
    { 10.0f, 7.0f, 0.0f },
    { -10.0f, 7.0f, 0.0f },
    { 7.0f, 10.0f, 0.0f },
    { -7.0f, 10.0f, 0.0f },
};
Vec3f D_i3_801BF920 = { 0.0f, 0.0f, 0.0f };
Gfx* D_i3_801BF92C[6] = {
    D_BG_PLANET_200B630, D_BG_PLANET_200A5A0, D_BG_PLANET_2009510, D_SO_60084C0, D_SO_6008D40, D_SO_6007C40,
};
Gfx* D_i3_801BF944[6] = {
    D_SO_601B790, D_SO_601B790, D_SO_601A700, D_SO_6019670, D_SO_60185E0, D_SO_6017550,
};
Vec3f D_i3_801BF95C[3] = {
    { 0.0f, 30.0f, 480.0f },
    { -180.0f, 0.0f, 240.0f },
    { 180.0f, 0.0f, 240.0f },
};

// Actors OBJ_ACTOR_SO_ROCK_1 to OBJ_ACTOR_SO_ROCK_3
void Solar_SoRock_Update(SoRock1* this) {
    f32 sp8C = 0.0f;
    s32 sp88;
    s32 i;

    if (this->obj.id == OBJ_ACTOR_SO_ROCK_3) {
        this->scale = 2.0f;
    }
    if (this->obj.id == OBJ_ACTOR_SO_ROCK_2) {
        this->rot_0F4.x -= 6.6f;
        this->rot_0F4.y -= 4.0f;
    } else {
        this->rot_0F4.x += 3.3f;
        this->rot_0F4.y += 2.0f;
    }

    switch (this->state) {
        case 0:
            this->fwork[0] = this->obj.pos.y * 0.05f;
            this->obj.pos.y = -100.0f;
            /* fallthrough */
        case 1:
            this->state = 2;
            this->vel.y = this->fwork[0];
            Play_CheckDynaFloorCollision(&sp8C, &sp88, this->obj.pos.x, this->obj.pos.y - 100.0f, this->obj.pos.z);
            this->obj.pos.y = sp8C;
            for (i = 0; i < 4; i++) {
                Solar_8019E9F4(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, D_i3_801BF8E0[i],
                               RAND_FLOAT(10.0f) + 10.0f, 0.0f, this->scale * 5.0f, 1);
            }
            this->timer_0C2 = 5;
            AUDIO_PLAY_SFX(NA_SE_OB_SOROCK_APPEAR, this->sfxSource, 0);
            break;

        case 2:
            this->gravity = 0.5f;

            if (Play_CheckDynaFloorCollision(&sp8C, &sp88, this->obj.pos.x, this->obj.pos.y, this->obj.pos.z)) {
                Object_Kill(&this->obj, this->sfxSource);
                Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_OB_SOROCK_DISAPPEAR);
                for (i = 0; i < 4; i++) {
                    Solar_8019E9F4(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, D_i3_801BF8E0[i],
                                   RAND_FLOAT(10.0f) + 10.0f, 0.0f, this->scale * 5.0f, 1);
                }
            }

            if (this->timer_0BC == 0) {
                this->timer_0BC = 5;
                Solar_8019E9F4(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 0.0f, 0.0f, 0.0f, this->scale * 6.5f,
                               2);
            }

            if ((this->dmgType != DMG_NONE) || ((this->obj.id == OBJ_ACTOR_SO_ROCK_3) && (this->vel.y < 0.0f))) {
                func_effect_8007D2C8(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, this->scale * 4.0f);
                Object_Kill(&this->obj, this->sfxSource);

                if (this->obj.id == OBJ_ACTOR_SO_ROCK_3) {
                    for (i = 0; i < 4; i++) {
                        Solar_8019F038(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z,
                                       D_i3_801BF8F0[i].x + RAND_FLOAT_CENTERED(3.0f),
                                       D_i3_801BF8F0[i].y + RAND_FLOAT_CENTERED(3.0f), RAND_FLOAT(-10.0f) - 10.0f);
                    }
                } else if (this->obj.id == OBJ_ACTOR_SO_ROCK_1) {
                    this->itemDrop = DROP_SILVER_RING;
                } else if (this->obj.id == OBJ_ACTOR_SO_ROCK_2) {
                    if (gGoldRingCount[0] != 4) {
                        this->itemDrop = DROP_GOLD_RING_1;
                    } else {
                        this->itemDrop = DROP_SILVER_STAR;
                    }
                }

                Actor_Despawn(this);

                for (i = 0; i < 3; i++) {
                    Effect_Effect357_Spawn50(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 0.3f);
                }
                for (i = 0; i < 7; i++) {
                    Solar_8019E9F4(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, RAND_FLOAT_CENTERED(30.0f),
                                   RAND_FLOAT_CENTERED(30.0f), 0.0f, (RAND_FLOAT(2.0f) + 2.0f) * this->scale, 1);
                }
                Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_EXPLOSION_S);
            }
            break;
    }

    this->obj.rot.y = RAD_TO_DEG(-gPlayer[0].camYaw);
    this->obj.rot.x = RAD_TO_DEG(gPlayer[0].camPitch);

    if ((gGameFrameCount % 2) == 0) {
        this->animFrame++;
        if (this->animFrame >= 3) {
            this->animFrame = 0;
        }
    }
}

// Actors OBJ_ACTOR_SO_ROCK_1 to OBJ_ACTOR_SO_ROCK_3
void Solar_SoRock_Draw(SoRock1* this) {
    if (this->state != 0) {
        Matrix_Push(&gGfxMatrix);
        Matrix_RotateY(gGfxMatrix, this->rot_0F4.y * M_DTOR, MTXF_APPLY);
        Matrix_RotateX(gGfxMatrix, this->rot_0F4.x * M_DTOR, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);

        switch (this->obj.id) {
            case OBJ_ACTOR_SO_ROCK_1:
                gSPDisplayList(gMasterDisp++, aSoRock1DL);
                break;

            case OBJ_ACTOR_SO_ROCK_2:
                if ((gGameFrameCount % 2) == 0) {
                    RCP_SetupDL(&gMasterDisp, SETUPDL_41);
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 0, 255);
                }
                gSPDisplayList(gMasterDisp++, aSoRock2DL);
                break;

            case OBJ_ACTOR_SO_ROCK_3:
                gSPDisplayList(gMasterDisp++, aSoRock3DL);
                break;
        }

        Matrix_Pop(&gGfxMatrix);
        Graphics_SetScaleMtx(this->scale * 3.5f);
        RCP_SetupDL(&gMasterDisp, SETUPDL_64);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 128, 128, 160);
        gSPDisplayList(gMasterDisp++, D_i3_801BF92C[this->animFrame]);
    }
}

void Solar_8019F99C(SoProminence* this, Effect392* effect, f32 scale1) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_ACTIVE;
    effect->obj.id = OBJ_EFFECT_392;

    effect->obj.pos.x = effect->vel.x = this->obj.pos.x;
    effect->obj.pos.y = -2000.0f;
    effect->vel.y = this->obj.pos.y;
    effect->obj.pos.z = effect->vel.z = this->obj.pos.z;
    effect->scale1 = scale1;
    effect->unk_60.y = this->obj.rot.y;
    effect->obj.rot.z = RAND_FLOAT(360.0f);

    effect->unk_44 = 255 - (this->counter_04E * 8);
    if (effect->unk_44 < 0) {
        effect->unk_44 = 0;
    }

    effect->scale2 = 20.0f - (this->counter_04E * 0.5f);
    effect->unk_48 = 1;
    Object_SetInfo(&effect->info, effect->obj.id);
}

void Solar_8019FAA4(SoVulkain* this, Effect392* effect, f32 xPos, f32 yPos, f32 zPos, f32 yVel, f32 hVelMod) {
    Vec3f sp44;
    Vec3f sp38;
    Vec3f sp2C = D_i3_801BF920;

    Effect_Initialize(effect);
    effect->obj.status = OBJ_ACTIVE;
    effect->obj.id = OBJ_EFFECT_392;
    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;
    effect->vel.y = yVel;
    effect->vel.x = 0.0f;
    effect->scale2 = 10.0f;

    if (gBossHealthBar != 0) {
        if (gBosses[0].fwork[SO_FWK_31] > 0.0f) {
            if (gBosses[0].swork[SO_SWK_0] != 7) {
                Matrix_RotateY(gCalcMatrix, gBosses[0].obj.rot.y * M_DTOR, MTXF_NEW);

                sp44.y = 0.0f;
                sp44.z = 0.0f;
                sp44.x = gBosses[0].fwork[SO_FWK_31] * 5.0f;

                Matrix_MultVec3f(gCalcMatrix, &sp44, &sp38);

                effect->vel.x = sp38.x * hVelMod;
                effect->vel.z = gPlayer[0].vel.z + (sp38.z * hVelMod);
            } else {
                Matrix_RotateZ(gCalcMatrix, this->obj.rot.z * M_DTOR, MTXF_NEW);
                Matrix_RotateX(gCalcMatrix, gBosses[0].obj.rot.x * M_DTOR, MTXF_APPLY);
                Matrix_RotateY(gCalcMatrix, gBosses[0].rot_078.y * M_DTOR, MTXF_APPLY);

                sp44.x = effect->obj.pos.x - this->obj.pos.x;
                sp44.y = effect->obj.pos.y - this->obj.pos.y;
                sp44.z = effect->obj.pos.z - this->obj.pos.z;

                Matrix_MultVec3f(gCalcMatrix, &sp44, &sp38);

                effect->obj.pos.x = this->obj.pos.x + sp38.x;
                effect->obj.pos.y = this->obj.pos.y + sp38.y;
                effect->obj.pos.z = this->obj.pos.z + sp38.z;

                effect->vel.z = gPlayer[0].vel.z;
                effect->vel.y = yVel;

                if (gBosses[0].state >= 2) {
                    effect->scale2 = 15.0f;
                }
            }
        } else {
            effect->vel.z = gPlayer[0].vel.z;
        }
    } else {
        effect->vel.x = RAND_FLOAT_CENTERED(30.0f);
        effect->vel.z = RAND_FLOAT_CENTERED(30.0f);
    }
    effect->unk_60.y = this->obj.rot.y;
    effect->unk_60.x = 90.0f;
    effect->obj.rot.z = RAND_FLOAT(360.0f);
    effect->unk_44 = 255;
    effect->unk_48 = 1;
    effect->state = 4;
    effect->unk_4C = 5;
    Object_SetInfo(&effect->info, effect->obj.id);
}

void Solar_8019FDE0(SoVulkain* this, Effect392* effect, f32 xPos, f32 yPos, f32 zPos, f32 scale2, s32 state) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_ACTIVE;
    effect->obj.id = OBJ_EFFECT_392;

    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;

    if (state != 0) {
        effect->vel.z = gPlayer[0].vel.z + 80.0f;
    } else {
        effect->vel.z = gPlayer[0].vel.z + 15.0f;
    }
    effect->scale2 = scale2;
    effect->unk_60.y = this->obj.rot.y;
    effect->unk_60.x = 0.0f;
    effect->obj.rot.z = RAND_FLOAT(360.0f);
    effect->unk_44 = 255;
    effect->unk_48 = 1;
    effect->state = state + 5;
    Object_SetInfo(&effect->info, effect->obj.id);
    effect->info.damage = 40;
}

void Solar_8019FEE8(SoProminence* this, f32 scale1) {
    s32 i;

    for (i = 70; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Solar_8019F99C(this, &gEffects[i], scale1);
            break;
        }
    }
}

void Solar_8019FF44(SoVulkain* this, f32 xPos, f32 yPos, f32 zPos, f32 yVel, f32 hVelMod) {
    s32 i;

    for (i = 70; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Solar_8019FAA4(this, &gEffects[i], xPos, yPos, zPos, yVel, hVelMod);
            break;
        }
    }
}

void Solar_8019FFC0(SoVulkain* this, f32 xPos, f32 yPos, f32 zPos, f32 scale2, s32 unk4E) {
    s32 i;

    for (i = 70; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Solar_8019FDE0(this, &gEffects[i], xPos, yPos, zPos, scale2, unk4E);
            break;
        }
    }
}

void Solar_SoProminence_Update(SoProminence* this) {
    switch (this->state) {
        case 0:
            if (this->timer_0BE == 0) {
                this->state = 1;
                this->timer_0BE = 50;
            } else if (this->timer_0BC == 0) {
                this->timer_0BC = 2;
                Solar_8019FEE8(this, 1000.0f);
                this->counter_04E++;
            }
            break;

        case 1:
            if (this->timer_0BE == 0) {
                this->state = 0;
                this->timer_0BE = 50;
                this->counter_04E = 0;
                Object_SetSfxSourceToPos(this->sfxSource, &this->obj.pos);
                AUDIO_PLAY_SFX(NA_SE_EN_OUT_PROMINENCE, this->sfxSource, 4);
            }
            break;
    }
}

void Solar_Effect392_Update(Effect392* this) {
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50 = 1.0f;
    s32 sp4C;
    s32 sp48;
    Vec3f sp3C;

    switch (this->state) {
        case 0:
            Matrix_Translate(gCalcMatrix, this->vel.x, this->vel.y, this->vel.z, MTXF_NEW);
            Matrix_RotateY(gCalcMatrix, this->unk_60.y * M_DTOR, MTXF_APPLY);
            Matrix_RotateX(gCalcMatrix, this->unk_60.x * M_DTOR, MTXF_APPLY);

            sp3C.x = 0.0f;
            sp3C.y = 0.0f;
            sp3C.z = -this->scale1;

            Matrix_MultVec3f(gCalcMatrix, &sp3C, &this->obj.pos);

            this->unk_60.x += 5.0f;

            if ((gGameFrameCount % 2) == 0) {
                this->unk_4C++;
                if (this->unk_4C > 2) {
                    this->unk_4C = 0;
                }
            }

            if (gPlayer[0].state != PLAYERSTATE_LEVEL_COMPLETE) {
                func_effect_8007A774(&gPlayer[0], this, this->scale2 * 12.0f);
            }

            if (this->unk_60.x > 190.0f) {
                Object_Kill(&this->obj, this->sfxSource);
            }

            sp48 = this->unk_48;

            if (Play_CheckDynaFloorCollision(&sp5C, &sp4C, this->obj.pos.x, this->obj.pos.y, this->obj.pos.z)) {
                this->unk_48 = 1;
                if (this->scale2 == 20.0f) {
                    AUDIO_PLAY_SFX(NA_SE_EN_IN_PROMINENCE, this->sfxSource, 4);
                }
            } else {
                this->unk_48 = 0;
            }

            if (sp48 != this->unk_48) {
                if (this->unk_48 != 0) {
                    sp54 = 50.0f;
                } else {
                    sp54 = -50.0f;
                }

                if ((this->index % 2) != 0) {
                    sp58 = 100.0f;
                } else {
                    sp58 = -100.0f;
                }

                Solar_8019E9F4(this->obj.pos.x + sp58, this->obj.pos.y + sp54, this->obj.pos.z, sp58 * 0.25f,
                               RAND_FLOAT(10.0f) + 20.0f, sp58 * 0.25f, 20.0f, 1);
            }
            break;

        case 1:
            if (this->timer_50 == 0) {
                this->timer_50 = 4;
                this->unk_4C++;
                if (this->unk_4C >= 6) {
                    this->unk_4C = 0;
                    Object_Kill(&this->obj, this->sfxSource);
                }
            }

            if (this->scale2 > 10.0f) {
                this->vel.y -= 2.5f;
            } else if (this->scale2 > 4.0f) {
                this->vel.y -= 1.0f;
            }
            break;

        case 2:
            if (this->timer_50 == 0) {
                Object_Kill(&this->obj, this->sfxSource);
            }
            Math_SmoothStepToF(&this->scale2, 0.0f, 0.1f, 0.2f, 0.0f);
            this->obj.rot.z += 3.0f;
            this->vel.y -= 0.3f;
            break;

        case 3:
            Math_SmoothStepToF(&this->obj.rot.z, -190.0f, 1.0f, 10.0f, 0.0f);
            this->vel.y -= 0.3f;
            if (this->obj.rot.z <= -180.0f) {
                Object_Kill(&this->obj, this->sfxSource);
            }
            break;

        case 4:
            if (gBosses[0].swork[SO_SWK_0] != 7) {
                Math_SmoothStepToF(&this->vel.y, -40.0f, 1.0f, 1.0f, 1.0f);
            } else {
                this->vel.z = gPlayer[0].vel.z;
                Math_SmoothStepToF(&this->vel.y, -65.0f, 2.0f, 1.0f, 0.5f);
            }

            if (gPlayer[0].state != PLAYERSTATE_LEVEL_COMPLETE) {
                func_effect_8007A774(&gPlayer[0], this, this->scale2 * 12.0f);
            }

            if (this->obj.pos.y < -20.0f) {
                Object_Kill(&this->obj, this->sfxSource);
            }

            this->obj.rot.z += 6.0f;
            if (this->obj.rot.z >= 360.0f) {
                this->obj.rot.z = 0.0f;
            }

            sp48 = this->unk_48;

            if (Play_CheckDynaFloorCollision(&sp5C, &sp4C, this->obj.pos.x, this->obj.pos.y, this->obj.pos.z)) {
                this->unk_48 = 1;
                if (this->scale2 == 20.0f) {
                    AUDIO_PLAY_SFX(NA_SE_EN_IN_PROMINENCE, this->sfxSource, 4);
                }
            } else {
                this->unk_48 = 0;
            }

            if ((sp48 != this->unk_48) && (this->unk_48 != 0)) {
                if ((this->index % 2) != 0) {
                    sp58 = 100.0f;
                } else {
                    sp58 = -100.0f;
                }
                Solar_8019E9F4(this->obj.pos.x + sp58, this->obj.pos.y + -50.0f, this->obj.pos.z, sp58 * 0.25f,
                               RAND_FLOAT(10.0f) + 20.0f, sp58 * 0.25f, 20.0f, 1);
            }
            break;

        case 5:
            this->unk_4C++;
            if (this->unk_4C > 2) {
                this->unk_4C = 0;
            }

            if (this->unk_60.x < 7.5f) {
                this->unk_60.x += 0.25f;
            }
            this->unk_60.z += 10.0f;

            this->vel.x = SIN_DEG(this->unk_60.z) * (this->unk_60.x * 10.0f);
            this->vel.y = COS_DEG(this->unk_60.z) * (this->unk_60.x * 10.0f);
            this->vel.z = gPlayer[0].vel.z + 15.0f;

            if (gPlayer[0].state != PLAYERSTATE_LEVEL_COMPLETE) {
                func_effect_8007A774(&gPlayer[0], this, this->scale2 * 18.0f);
                if ((this->unk_4C == 0) && ((this->scale2 >= 9.8f) || (this->scale2 <= 4.4f))) {
                    AUDIO_PLAY_SFX(NA_SE_EN_SOBOSS_BREATH, this->sfxSource, 4);
                }
            } else {
                this->vel.z += 65.0f;
                if (fabsf(gBosses[0].obj.pos.z - this->obj.pos.z) >= 2000.0f) {
                    Audio_KillSfxBySourceAndId(this->sfxSource, NA_SE_EN_SOBOSS_BREATH);
                }
            }
            break;

        case 6:
            sp50 = -1.0f;
            /* fallthrough */
        case 7:
            this->unk_4C++;
            if (this->unk_4C > 2) {
                this->unk_4C = 0;
            }

            this->unk_60.z += 20.0f;

            this->vel.x = SIN_DEG(this->unk_60.z) * sp50 * 50.0f;
            this->vel.y = COS_DEG(this->unk_60.z) * sp50 * 50.0f;
            this->vel.z = gPlayer[0].vel.z + 80.0f;

            if (gPlayer[0].state != PLAYERSTATE_LEVEL_COMPLETE) {
                func_effect_8007A774(&gPlayer[0], this, this->scale2 * 18.0f);
                if ((this->unk_4C == 0) && ((this->scale2 >= 9.8f) || (this->scale2 <= 4.4f))) {
                    AUDIO_PLAY_SFX(NA_SE_EN_SOBOSS_BREATH, this->sfxSource, 4);
                }
            } else if (fabsf(gBosses[0].obj.pos.z - this->obj.pos.z) >= 2000.0f) {
                Audio_KillSfxBySourceAndId(this->sfxSource, NA_SE_EN_SOBOSS_BREATH);
            }
            break;
    }
}

void Solar_Effect392_Draw(Effect392* this) {
    Graphics_SetScaleMtx(this->scale2);
    switch (this->state) {
        case 0:
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 128, 128, this->unk_44);
            gSPDisplayList(gMasterDisp++, D_i3_801BF92C[this->unk_4C]);
            break;
        case 1:
        case 2:
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 128, 128, this->unk_44);
            gSPDisplayList(gMasterDisp++, D_i3_801BF944[this->unk_4C]);
            break;
        case 3:
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 128, 128, this->unk_44);
            gSPDisplayList(gMasterDisp++, D_SO_601C820);
            break;
        case 4:
        case 5:
        case 6:
        case 7:
            RCP_SetupDL(&gMasterDisp, SETUPDL_53);
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 128, 128, this->unk_44);
            gSPDisplayList(gMasterDisp++, D_i3_801BF92C[this->unk_4C]);
            RCP_SetupDL(&gMasterDisp, SETUPDL_64);
            break;
    }
}

void Solar_801A0CEC(SoWave* this, f32 xPos, f32 zPos, f32 zVel, s32 unkB8) {
    Actor_Initialize(this);
    this->obj.status = OBJ_ACTIVE;
    this->obj.id = OBJ_ACTOR_SO_WAVE;

    this->obj.pos.x = xPos;
    this->obj.pos.z = zPos;
    this->work_046 = 1;
    this->state = unkB8;
    this->vel.z = zVel;
    this->fwork[1] = zVel;
    if (unkB8 == 2) {
        this->fwork[0] = 18.0f;
    }
    Object_SetInfo(&this->info, this->obj.id);
    this->info.bonus = 0;
}

void Solar_801A0D90(f32 xPos, f32 zPos, f32 zVel, s32 unkB8) {
    s32 i;

    for (i = 4; i < ARRAY_COUNT(gActors); i++) {
        if (gActors[i].obj.status == OBJ_FREE) {
            Solar_801A0CEC(&gActors[i], xPos, zPos, zVel, unkB8);
            break;
        }
    }
}

void Solar_801A0DF8(f32 xPos, f32 zPos, f32 yRot, s32 index, f32 yPos) {
    s32 actorIndex;

    switch (index) {
        case 0:
            if (D_ctx_80177A10[0] != 0) {
                actorIndex = 5;
                D_ctx_80177A10[1] = RAND_INT(10.0f) + 128;
            } else {
                actorIndex = 4;
                D_ctx_80177A10[0] = RAND_INT(10.0f) + 128;
            }
            break;
        case 1:
        case 4:
            actorIndex = 6;
            break;
        case 2:
            actorIndex = 4;
            break;
        case 3:
            actorIndex = 5;
            break;
    }
    Actor_Initialize(&gActors[actorIndex]);

    gActors[actorIndex].obj.status = OBJ_ACTIVE;
    gActors[actorIndex].obj.id = OBJ_ACTOR_SO_PROMINENCE;

    Object_SetInfo(&gActors[actorIndex].info, gActors[actorIndex].obj.id);

    gActors[actorIndex].state = 0;
    gActors[actorIndex].obj.pos.x = xPos;
    gActors[actorIndex].obj.pos.z = zPos;
    gActors[actorIndex].obj.rot.y = yRot;

    if (index != 4) {
        gActors[actorIndex].obj.pos.y = -80.0f * yPos;
    } else {
        gActors[actorIndex].timer_0BC = 0;
        gActors[actorIndex].timer_0BE = 50;
        gActors[actorIndex].counter_04E = 0;
        gActors[actorIndex].obj.pos.y = -1.0f * yPos;
        Object_SetSfxSourceToPos(gActors[actorIndex].sfxSource, &gActors[actorIndex].obj.pos);
        AUDIO_PLAY_SFX(NA_SE_EN_OUT_PROMINENCE, gActors[actorIndex].sfxSource, 4);
    }
}

void Solar_801A0FD4(ActorCutscene* this, s32 index) {
    if (gTeamShields[3 - index] > 0) {
        Actor_Initialize(this);
        this->obj.status = OBJ_ACTIVE;
        this->obj.id = OBJ_ACTOR_CUTSCENE;

        this->obj.pos.x = D_i3_801BF95C[index].x + gPlayer[0].pos.x;
        this->obj.pos.y = D_i3_801BF95C[index].y + gPlayer[0].pos.y;
        this->obj.pos.z = D_i3_801BF95C[index].z + gPlayer[0].pos.z;

        this->state = 0;
        this->iwork[11] = 1;
        this->vel.z = 0.0f;
        this->vel.y = 0.0f;
        this->obj.rot.x = 0.0f;
        this->obj.rot.y = 180.0f;
        Object_SetInfo(&this->info, this->obj.id);
        AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, this->sfxSource, 4);
    }
}

void Solar_LevelStart(Player* player) {
    s32 i;
    Vec3f sp50;
    Vec3f sp44;

    if (D_ctx_80177A10[0] != 0) {
        D_ctx_80177A10[0]--;
    }
    if (D_ctx_80177A10[1] != 0) {
        D_ctx_80177A10[1]--;
    }

    switch (player->csState) {
        case 0:
            gCsFrameCount = 0;
            Rand_SetSeed(1, 29100, 9786);
            player->csState = 1;
            player->cam.eye.x = -2000.0f;
            gCsCamEyeX = -2800.0f;
            player->cam.eye.y = gCsCamEyeY = 120.0f;
            player->cam.eye.z = -1800.0f;
            gCsCamEyeZ = -2800.0f;

            player->cam.at.x = gCsCamAtX = -1000.0f;
            player->cam.at.y = 1400.0f;
            gCsCamAtY = 400.0f;
            player->cam.at.z = gCsCamAtZ = -2300.0f;

            D_ctx_80177A48[0] = 0.0045f;

            player->camRoll = 0.0f;
            player->baseSpeed = 0.0f;

            gFillScreenAlpha = 255;
            gFillScreenAlphaTarget = 0;
            Solar_801A0DF8(-750.0f, -2600.0f, 300.0f, 2, 1.0f);
            AUDIO_PLAY_SFX(NA_SE_OB_MAGMA_BUBBLE, player->sfxSource, 0);
            break;

        case 1:
            gPathTexScroll += 30.0f;

            if (gCsFrameCount == 140) {
                Solar_801A0DF8(-400.0f, -2000.0f, 45.0f, 3, 1.0f);
            }
            if (gCsFrameCount == 280) {
                Solar_801A0DF8(-1730.0f, -2300.0f, 250.0f, 1, 1.0f);
            }

            if (gCsFrameCount == 100) {
                Object_Kill(&gActors[4].obj, gActors[4].sfxSource);
            }
            if (gCsFrameCount == 240) {
                Object_Kill(&gActors[5].obj, gActors[5].sfxSource);
            }
            if (gCsFrameCount == 380) {
                Object_Kill(&gActors[6].obj, gActors[6].sfxSource);
            }

            if (gCsFrameCount < 3) {
                gFillScreenAlpha = 255;
            }

            if (gCsFrameCount == 370) {
                gFillScreenAlphaTarget = 255;
                gFillScreenRed = 255;
                gFillScreenGreen = 255;
                gFillScreenBlue = 255;
                gFillScreenAlphaStep = 8;
            }

            if ((gGameFrameCount % 8) == 0) {
                Solar_8019E8B8(RAND_FLOAT_CENTERED(6000.0f), RAND_FLOAT_CENTERED(5.0f) - 90.0f,
                               RAND_FLOAT(2000.0f) - 6000.0f + gPathProgress, RAND_FLOAT(20.0f) + 20.0f);
            }

            if (gCsFrameCount == 380) {
                for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
                    Object_Kill(&gEffects[i].obj, gEffects[i].sfxSource);
                }
                Solar_801A0DF8(400.0f, -2800.0f, 340.0f, 1, 1.0f);
            }

            if (gCsFrameCount == 410) {
                player->csState++;
                player->cam.eye.x = 200.0f;
                gCsCamEyeX = 800.0f;
                player->cam.eye.y = 140.0f;
                gCsCamEyeY = player->pos.y + 200.0f;
                player->cam.eye.z = gCsCamEyeZ = 400.0f;

                player->cam.at.x = 400.0f;
                gCsCamAtX = 200.0f;
                player->cam.at.y = 140.0f;
                gCsCamAtY = 1200.0f;
                player->cam.at.z = -500.0f;

                player->pos.y = 1200.0f;
                player->pos.z = -2500.0f;

                Solar_801A0FD4(&gActors[0], 0);
                Solar_801A0FD4(&gActors[1], 1);
                Solar_801A0FD4(&gActors[2], 2);

                gCsCamAtZ = -3000.0f;
                gCsCamEyeZ = -3400.0f;

                Audio_KillSfxBySourceAndId(player->sfxSource, NA_SE_OB_MAGMA_BUBBLE);

                AUDIO_PLAY_BGM(NA_BGM_SO_START_DEMO);

                Display_SetupPlayerSfxPos(player);
                Audio_StartPlayerNoise(gPlayerNum);

                D_ctx_80177A48[0] = 0.01f;
            }
            break;

        case 2:
            gPathTexScroll += 60.0f;
            gFillScreenAlphaTarget = 0;
            gFillScreenAlphaStep = 8;

            Math_SmoothStepToF(D_ctx_80177A48, 0.02f, 1.0f, 0.0000003f, 0.0f);

            if (gCsFrameCount == 525) {
                Radio_PlayMessage(gMsg_ID_10010, RCID_FOX);
            }
            if (gCsFrameCount == 550) {
                Object_Kill(&gActors[5].obj, gActors[5].sfxSource);
                Solar_801A0DF8(30.0f, -1500.0f, 160.0f, 3, 2.0f);
            }

            if (player->cam.eye.z <= -2465.0f) {
                player->csState++;
                gCsCamEyeY = player->pos.y + 180.0f;
                gCsCamAtX = 0.0f;
                gCsCamEyeX = 0.0f;
                gCsCamAtZ = -2800.0f;
                D_ctx_80177A48[0] = 0.06f;
            }
            break;

        case 3:
            gPathTexScroll += 60.0f;

            if ((gGameFrameCount % 4) == 0) {
                Solar_8019E8B8(RAND_FLOAT_CENTERED(6000.0f), -400.0f - ((player->cam.eye.y - 1380.0f) * 0.3f),
                               RAND_FLOAT_CENTERED(2000.0f) + 500.0f + gPathProgress, RAND_FLOAT(20.0f) + 20.0f);
            }

            if (gCsFrameCount == 615) {
                Play_PlaySfxFirstPlayer(player->sfxSource, NA_SE_ARWING_BOOST);
                gActors[0].fwork[29] = gActors[1].fwork[29] = gActors[2].fwork[29] = 5.0f;
                gActors[0].state = 3;
                gActors[1].state = 2;
                gActors[2].state = 1;
                player->csTimer = 3;
                player->unk_190 = 5.0f;
                player->csState++;
                player->unk_194 = 5.0f;
            }
            break;

        case 4:
            gCsCamEyeX = player->pos.x;
            gCsCamEyeY = player->pos.y;
            gCsCamEyeZ = player->trueZpos + 1000.0f;

            gCsCamAtX = player->pos.x;
            gCsCamAtY = player->pos.y;
            gCsCamAtZ = player->trueZpos + 1100.0f;

            D_ctx_80177A48[0] = 0.03f;
            D_ctx_801779A8[gMainController] = 60.0f;

            player->unk_190 = 2.0f;

            if (player->csTimer == 0) {
                gFillScreenAlphaTarget = 255;
                gFillScreenAlphaStep = 24;
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
            }

            if (gFillScreenAlpha == 255) {
                AUDIO_PLAY_BGM(NA_BGM_STAGE_SO);
                player->pos.z = 0.0f;
                player->baseSpeed = gArwingSpeed;
                Play_ClearObjectData();
                gLevelStartStatusScreenTimer = 50;
                player->state = PLAYERSTATE_ACTIVE;
                player->csState = 0;
                player->pos.y = 350.0f;

                player->cam.eye.x = player->pos.x;
                player->cam.eye.y = 50.0f + player->pos.y * player->unk_148;
                player->cam.eye.z = 30.0f;

                player->cam.at.x = player->pos.x;
                player->cam.at.y = 20.0f + player->pos.y * player->unk_148;
                player->cam.at.z = player->trueZpos;

                D_ctx_80177950 = 1.0f;
                Audio_SetHeatAlarmParams(255, 3);
                AUDIO_PLAY_SFX(NA_SE_OVERHEAT_ALARM, gDefaultSfxSource, 4);
                gLoadLevelObjects = 1;
                gFillScreenAlphaTarget = 0;
                player->csTimer = 15;
                gPlayer[0].shields = 255;
            }
            break;

        case 10:
            gPathTexScroll += 60.0f;
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

    sp50.x = 0.f;
    sp50.y = 0.0f;
    sp50.z = player->baseSpeed;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp50, &sp44);

    player->vel.x = sp44.x;
    player->vel.z = sp44.z;
    player->vel.y = sp44.y;

    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;
    player->pos.z += player->vel.z;
    player->trueZpos = player->pos.z + player->camDist;
}

void Solar_801A1CD8(ActorDebris* this, f32 xPos, f32 yPos, f32 zPos, f32 xRot, f32 yRot, f32 zRot, f32 xVel, f32 yVel,
                    f32 zVel, s32 unk46) {
    Actor_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_ACTOR_DEBRIS;

    this->state = 40;
    this->work_046 = unk46;
    this->work_04A = 3;

    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;

    this->obj.rot.x = xRot;
    this->obj.rot.y = yRot;
    this->obj.rot.z = zRot;

    this->vel.x = xVel;
    this->vel.y = yVel;
    this->vel.z = zVel;

    this->iwork[0] = 3;

    this->fwork[0] = RAND_FLOAT_CENTERED(25.0f);
    this->fwork[1] = RAND_FLOAT_CENTERED(25.0f);
    this->fwork[2] = RAND_FLOAT_CENTERED(25.0f);
    this->fwork[5] = 2000.0f;
    this->gravity = 3.5f;
    this->scale = 5.5f;
    Object_SetInfo(&this->info, this->obj.id);
}

void Solar_801A1E14(f32 xPos, f32 yPos, f32 zPos, f32 xRot, f32 yRot, f32 zRot, f32 xVel, f32 yVel, f32 zVel,
                    s32 unk46) {
    s32 i;

    for (i = ARRAY_COUNT(gActors) - 1; i >= 0; i--) {
        if (gActors[i].obj.status == OBJ_FREE) {
            Solar_801A1CD8(&gActors[i], xPos, yPos, zPos, xRot, yRot, zRot, xVel, yVel, zVel, unk46);
            break;
        }
    }
}

void Solar_801A1EB0(SoVulkain* this, f32 xPos, f32 xOffset, f32 yPos, f32 zPos) {
    Solar_8019E9F4(xPos + xOffset, yPos, zPos, 20.0f, RAND_FLOAT(10.0f) + 20.0f, 0.0f, 20.0f, 1);
    Solar_8019E9F4(xPos - xOffset, yPos, zPos, -20.0f, RAND_FLOAT(10.0f) + 20.0f, 0.0f, 20.0f, 1);
}

void Solar_801A1F80(SoVulkain* this) {
    if (gBossActive) {
        this->scale = 5.5f;
    }

    if (this->health == 0) {
        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 20);
        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 20);
        gBossActive = true;
        gBossFrameCount = 0;
        this->health = 600;

        this->scale = 0.1f;
        this->fwork[SO_FWK_0] = 1.0f;
        this->swork[SO_SWK_2] = this->swork[SO_SWK_3] = 400;

        this->obj.pos.y = -3000.0f;

        Solar_801A0CEC(&gActors[10], this->obj.pos.x, this->obj.pos.z + 2000.0f, 20.0f, 1);

        D_ctx_801779A8[gMainController] = 10.0f;

        gCameraShake = 120;

        this->fwork[SO_FWK_3] = 2400.0f;
        this->info.hitbox = SEGMENTED_TO_VIRTUAL(D_SO_60231A4);
        this->animFrame = 0;
        this->swork[SO_SWK_1] = 0;
        this->info.hitbox[8] = this->info.hitbox[12] = this->info.hitbox[14] = this->info.hitbox[18] =
            this->info.hitbox[20] = this->info.hitbox[24] = this->info.hitbox[26] = this->info.hitbox[30] =
                this->info.hitbox[32] = this->info.hitbox[36] = this->info.hitbox[38] = this->info.hitbox[42] = 220.0f;
        this->info.hitbox[10] = this->info.hitbox[28] = 467.5f;
        this->info.hitbox[16] = this->info.hitbox[34] = 247.5f;
        this->info.hitbox[22] = this->info.hitbox[40] = 715.0f;

        D_i3_801C2740[0] = 255;
        D_i3_801C2740[1] = 255;
        D_i3_801C2768[3] = D_i3_801C2768[2] = D_i3_801C2768[4] = D_i3_801C2768[5] = D_i3_801C2768[6] =
            D_i3_801C2768[7] = D_i3_801C2768[8] = D_i3_801C2768[9] = D_i3_801C2768[10] = D_i3_801C2768[11] =
                D_i3_801C2768[12] = D_i3_801C2768[13] = 0.0f;
    }

    gActors[10].obj.pos.z = this->obj.pos.z + 2000.0f;

    Math_SmoothStepToF(&this->obj.pos.y, 180.0f, 0.1f, 30.0f, 0.1f);

    if (gFogRed > 96) {
        gFogRed--;
    }
    if (gFogGreen > 96) {
        gFogGreen--;
    }
    if (gFogBlue > 64) {
        gFogBlue--;
    }

    if (gBossFrameCount == 30) {
        AUDIO_PLAY_BGM(NA_BGM_BOSS_SO);
    }

    if (gBossFrameCount <= 60) {
        Math_SmoothStepToF(&D_ctx_801779A8[gMainController], 120.0f, 1.0f, 3.5f, 0.0f);
    }

    if (gBossFrameCount == 60) {
        gActors[10].dmgType = DMG_COLLISION;
        AUDIO_PLAY_SFX(NA_SE_EN_OUT_MAGMA, this->sfxSource, 4);
    }

    if (this->timer_050 == 100) {
        this->animFrame = 0;
        this->swork[SO_SWK_1] = 1;
    }

    if (gBossFrameCount == 150) {
        Solar_801A239C(this);
        this->fwork[SO_FWK_0] = 0.01f;
    }

    if ((gBossFrameCount == 100) && (gTeamShields[TEAM_ID_PEPPY] != 0)) {
        Radio_PlayMessage(gMsg_ID_10300, RCID_PEPPY);
    }
}

void Solar_801A239C(SoVulkain* this) {
    this->swork[SO_SWK_0] = 1;
    if ((this->swork[SO_SWK_2] != 0) || (this->swork[SO_SWK_3] != 0)) {
        if (this->swork[SO_SWK_3] != 0) {
            this->swork[SO_SWK_1] = 3;
        } else {
            this->swork[SO_SWK_1] = 4;
        }
    } else {
        this->swork[SO_SWK_1] = 7;
    }
    this->animFrame = 0;
}

void Solar_801A23F4(SoVulkain* this) {
    s32 i;
    Vec3f sp58;
    Vec3f sp4C;
    Vec3f sp40;
    Vec3f sp34;

    switch (this->swork[SO_SWK_1]) {
        case 3:
            if ((this->animFrame == 119) || (this->swork[SO_SWK_3] == 0)) {
                this->animFrame = 0;
                if (this->swork[SO_SWK_2] != 0) {
                    if (Rand_ZeroOne() >= 0.5f) {
                        this->swork[SO_SWK_1] = 4;
                    } else {
                        this->swork[SO_SWK_1] = 2;
                        this->state = 0;
                        this->rot_078.y = 0.0f;
                    }
                } else if (this->swork[SO_SWK_3] == 0) {
                    this->swork[SO_SWK_1] = 7;
                } else {
                    this->swork[SO_SWK_1] = 5;
                }
            }

            if (this->animFrame >= 28) {
                this->info.hitbox[38] = 715.0f;
                this->info.hitbox[40] = 440.0f;
                this->info.hitbox[42] = 110.0f;
            }

            if (this->animFrame == 29) {
                Object_SetSfxSourceToPos(this->sfxSource, &this->obj.pos);
                AUDIO_PLAY_SFX(NA_SE_EN_OUT_PROMINENCE, this->sfxSource, 4);
            }

            if (this->animFrame == 80) {
                AUDIO_PLAY_SFX(NA_SE_EN_SOBOSS_SWING, this->sfxSource, 4);
            }

            if (this->animFrame >= 94) {
                this->info.hitbox[38] = 220.0f;
                this->info.hitbox[40] = 715.0f;
                this->info.hitbox[42] = 220.0f;
            }
            break;

        case 4:
            if ((this->animFrame == 99) || (this->swork[SO_SWK_2] == 0)) {
                this->animFrame = 0;
                if ((this->swork[SO_SWK_3] != 0) || (this->swork[SO_SWK_2] != 0)) {
                    this->swork[SO_SWK_1] = 5;
                } else {
                    this->swork[SO_SWK_1] = 7;
                }
            }

            if (this->animFrame > 20) {
                this->info.hitbox[20] = 715.0f;
                this->info.hitbox[22] = 110.0f;
                this->info.hitbox[24] = 275.0f;
            }

            if (this->animFrame == 10) {
                Object_SetSfxSourceToPos(this->sfxSource, &this->obj.pos);
                AUDIO_PLAY_SFX(NA_SE_EN_OUT_PROMINENCE, this->sfxSource, 4);
            }

            if (this->animFrame == 50) {
                AUDIO_PLAY_SFX(NA_SE_EN_SOBOSS_SWING, this->sfxSource, 4);
            }

            if (this->animFrame >= 85) {
                this->info.hitbox[20] = 220.0f;
                this->info.hitbox[22] = 715.0f;
                this->info.hitbox[24] = 220.0f;
            }
            break;

        case 5:
            this->fwork[SO_FWK_3] = 2600.0f;

            Math_SmoothStepToAngle(&this->obj.rot.y, 0.0f, 1.0f, 1.5f, 1.0f);

            if (this->animFrame == 65) {
                Matrix_RotateX(gCalcMatrix, D_i3_801C2768[0] * M_DTOR, MTXF_NEW);
                Matrix_RotateY(gCalcMatrix, D_i3_801C2768[1] * M_DTOR, MTXF_APPLY);
                sp40.x = 0.0f;
                sp40.y = -200.0f;
                sp40.z = 1100.0f;
                Matrix_MultVec3f(gCalcMatrix, &sp40, &sp34);

                for (i = 0; i < 4; i++) {
                    sp58.x = D_i3_801BF8F0[i].x + RAND_FLOAT_CENTERED(2.0f);
                    sp58.y = RAND_FLOAT_CENTERED(2.0f);
                    sp58.z = RAND_FLOAT(10.0f) + 2.5f;
                    Matrix_MultVec3f(gCalcMatrix, &sp58, &sp4C);
                    Solar_8019F038(this->fwork[SO_FWK_4] + sp34.x, this->fwork[SO_FWK_5] + sp34.y,
                                   this->fwork[SO_FWK_6] + sp34.z, sp4C.x, sp4C.y, sp4C.z);
                }
            }

            if (this->animFrame == 99) {
                if ((this->swork[SO_SWK_2] != 0) || (this->swork[SO_SWK_3] != 0)) {
                    Solar_801A2C3C(this);
                } else {
                    Solar_801A4EC0(this);
                }
            }
            break;

        case 7:
            if (this->animFrame < 50) {
                if (this->fwork[SO_FWK_31] < 22.0f) {
                    this->fwork[SO_FWK_31] += 0.5f;
                }
                this->obj.rot.y += this->fwork[SO_FWK_31];
            }

            if ((this->animFrame >= 50) && (this->animFrame <= 100)) {
                if (this->fwork[SO_FWK_31] > 0.0f) {
                    this->fwork[SO_FWK_31] -= 0.5f;
                }
                this->obj.rot.y += this->fwork[SO_FWK_31];
            }

            if (this->obj.rot.y >= 360.0f) {
                this->obj.rot.y -= 360.0f;
                AUDIO_PLAY_SFX(NA_SE_EN_SOBOSS_ROLL, this->sfxSource, 4);
            }

            if (this->animFrame == 1) {
                AUDIO_PLAY_SFX(NA_SE_EN_SOBOSS_ROLL, this->sfxSource, 4);
            }
            if (this->animFrame >= 100) {
                Math_SmoothStepToAngle(&this->obj.rot.y, 0.0f, 1.0f, 2.0f, 1.0f);
                this->fwork[SO_FWK_31] = 0.0f;
            }

            if (this->animFrame == 120) {
                this->swork[SO_SWK_1] = 5;
                this->animFrame = 0;
                this->fwork[SO_FWK_0] = 0.1f;
            }
            break;

        case 2:
            if (((this->animFrame == 89) && (this->state == 2)) || (this->swork[SO_SWK_2] == 0)) {
                this->animFrame = 0;

                if ((this->swork[SO_SWK_3] != 0) || (this->swork[SO_SWK_2] != 0)) {
                    this->swork[SO_SWK_1] = 5;
                } else {
                    this->swork[SO_SWK_1] = 7;
                }
            }

            if (this->animFrame == 80) {
                this->rot_078.y += 15.0f;
                this->state++;
                if (this->rot_078.y >= 30.0f) {
                    this->rot_078.y = 0.0f;
                }
            }

            Math_SmoothStepToAngle(&this->obj.rot.y, this->rot_078.y, 1.0f, 1.5f, 1.0f);

            if (this->animFrame >= 19) {
                this->info.hitbox[20] = 715.0f;
                this->info.hitbox[22] = 440.0f;
                this->info.hitbox[24] = 110.0f;
            }

            if (this->animFrame == 5) {
                Object_SetSfxSourceToPos(this->sfxSource, &this->obj.pos);
                AUDIO_PLAY_SFX(NA_SE_EN_OUT_PROMINENCE, this->sfxSource, 4);
            }

            if (this->animFrame == 20) {
                AUDIO_PLAY_SFX(NA_SE_EN_SOBOSS_SWING, this->sfxSource, 4);
            }

            if (this->animFrame > 36) {
                this->info.hitbox[20] = 220.0f;
                this->info.hitbox[22] = 715.0f;
                this->info.hitbox[24] = 220.0f;
            }
            break;
    }
}

void Solar_801A2C3C(SoVulkain* this) {
    this->swork[SO_SWK_0] = 2;
    this->swork[SO_SWK_1] = 0;
    this->fwork[SO_FWK_0] = 0.05f;
    this->animFrame = Animation_GetFrameCount(&D_SO_601388C) - 2;
    this->state = 0;
    this->swork[SO_SWK_11] = 15;
}

void Solar_801A2C98(SoVulkain* this) {
    s32 i;

    if (this->swork[SO_SWK_11] != 0) {
        this->swork[SO_SWK_11]--;
    }

    if (this->state == 0) {
        if (this->swork[SO_SWK_11] == 0) {
            this->animFrame -= 2;

            Math_SmoothStepToF(&this->obj.pos.y, -1000.0f, 0.1f, 10.0f, 0.1f);
            Math_SmoothStepToAngle(&this->obj.rot.y, 181.0f, 1.0f, 3.0f, 1.0f);

            if (this->animFrame == 50) {
                Solar_801A0CEC(&gActors[10], this->obj.pos.x, this->obj.pos.z + 1000.0f, 20.0f, 1);
                gControllerRumbleFlags[gMainController] = 1;
                gControllerRumbleTimers[gMainController] = 70;
            }

            if (this->animFrame == 60) {
                for (i = 0; i < 4; i++) {
                    Solar_8019F038(this->obj.pos.x + 100.0f, 100.0f, this->obj.pos.z + 1100.0f,
                                   D_i3_801BF8F0[i].x + RAND_FLOAT_CENTERED(2.0f),
                                   D_i3_801BF8F0[i].y + 10.0f + RAND_FLOAT_CENTERED(2.0f), RAND_FLOAT(-10.0f) - 10.0f);
                    Solar_8019F038(this->obj.pos.x - 100.0f, 100.0f, this->obj.pos.z + 1100.0f,
                                   D_i3_801BF8F0[i].x + RAND_FLOAT_CENTERED(2.0f),
                                   D_i3_801BF8F0[i].y + 10.0f + RAND_FLOAT_CENTERED(2.0f), RAND_FLOAT(-10.0f) - 10.0f);
                }
            }

            if (this->animFrame == 20) {
                gActors[10].dmgType = DMG_COLLISION;
                AUDIO_PLAY_SFX(NA_SE_EN_IN_MAGMA, this->sfxSource, 4);
            }

            if (this->animFrame == 0) {
                this->state++;
                this->swork[SO_SWK_11] = 100;
                this->obj.pos.y = -500.0f;
                this->fwork[SO_FWK_3] = 4800.0f;
                this->obj.pos.z = gPlayer[0].trueZpos - this->fwork[SO_FWK_3];
                this->obj.rot.y = -this->obj.rot.y;
            }
        } else {
            this->animFrame = Animation_GetFrameCount(&D_SO_601388C) - 2;
        }
    } else {
        Math_SmoothStepToAngle(&this->obj.rot.y, 0.0f, 1.0f, 1.5f, 1.0f);

        if (this->swork[SO_SWK_11] == 80) {
            Solar_801A0CEC(&gActors[9], this->obj.pos.x, this->obj.pos.z + 1000.0f, 20.0f, 1);
        }

        if (this->swork[SO_SWK_11] == 0) {
            this->swork[SO_SWK_11] = 220;
        }

        if (this->swork[SO_SWK_11] == 210) {
            this->animFrame = 0;
            this->swork[SO_SWK_1] = 1;
            this->fwork[SO_FWK_0] = 0.05f;
        }

        if (this->swork[SO_SWK_11] >= 100) {
            Math_SmoothStepToF(&this->obj.pos.y, 180.0f, 0.1f, 10.0f, 0.1f);
        }

        if (this->swork[SO_SWK_11] == 150) {
            Solar_801A3468(this);
        }

        if (this->swork[SO_SWK_11] == 50) {
            gActors[9].dmgType = DMG_COLLISION;
            AUDIO_PLAY_SFX(NA_SE_EN_OUT_MAGMA, this->sfxSource, 4);
        }
    }
}

void Solar_801A30CC(SoVulkain* this) {
    this->swork[SO_SWK_0] = 3;
    this->swork[SO_SWK_1] = 0;
    this->fwork[SO_FWK_0] = 0.1f;
    this->animFrame = Animation_GetFrameCount(&D_SO_601388C) - 2;
    this->state = 0;
    this->swork[SO_SWK_11] = 15;
}

void Solar_801A3128(SoVulkain* this) {
    if (this->swork[SO_SWK_11] != 0) {
        this->swork[SO_SWK_11]--;
    }

    if (this->state == 0) {
        if (this->swork[SO_SWK_11] == 0) {
            this->animFrame -= 2;

            Math_SmoothStepToF(&this->obj.pos.y, -1000.0f, 0.1f, 10.0f, 0.1f);

            if (this->animFrame == 50) {
                Solar_801A0CEC(&gActors[10], this->obj.pos.x, this->obj.pos.z + 2000.0f, 10.0f, 1);
            }

            if (this->animFrame == 40) {
                gActors[10].dmgType = DMG_COLLISION;
                AUDIO_PLAY_SFX(NA_SE_EN_IN_MAGMA, this->sfxSource, 4);
            }

            if (this->animFrame == 0) {
                this->state++;
                this->swork[SO_SWK_11] = 100;
                this->obj.pos.y = -500.0f;
                this->fwork[SO_FWK_3] = 2400.0f;
                this->obj.pos.z = gPlayer[0].trueZpos - 2100.0f;
            }
        } else {
            this->animFrame = Animation_GetFrameCount(&D_SO_601388C) - 2;
        }
    } else {
        if (this->swork[SO_SWK_11] == 80) {
            Solar_801A0CEC(&gActors[9], this->obj.pos.x, this->obj.pos.z + 850.0f, 20.0f, 1);

            gControllerRumbleFlags[gMainController] = 1;
            gControllerRumbleTimers[gMainController] = 70;

            D_i3_801C2740[2]++;

            if ((D_i3_801C2740[2] % 2) != 0) {
                if ((D_i3_801C2740[2] & 2) != 0) {
                    if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                        Radio_PlayMessage(gMsg_ID_20317, RCID_PEPPY);
                    }
                } else {
                    if (gTeamShields[TEAM_ID_FALCO] > 0) {
                        Radio_PlayMessage(gMsg_ID_20271, RCID_FALCO);
                    }
                }
            }
        }

        if (this->swork[SO_SWK_11] == 0) {
            this->swork[SO_SWK_11] = 220;
        }

        if (this->swork[SO_SWK_11] == 210) {
            this->animFrame = 0;
            this->swork[SO_SWK_1] = 1;
        }

        if (this->swork[SO_SWK_11] >= 100) {
            Math_SmoothStepToF(&this->obj.pos.y, 180.0f, 0.1f, 20.0f, 0.1f);
        }

        if (this->swork[SO_SWK_11] == 150) {
            Solar_801A239C(this);
            this->fwork[SO_FWK_0] = 0.01f;
            if ((Rand_ZeroOne() >= 0.4f) && (gTeamShields[TEAM_ID_PEPPY] > 0) && (this->swork[SO_SWK_2] != 0) &&
                (this->swork[SO_SWK_3] != 0)) {
                Radio_PlayMessage(gMsg_ID_10320, RCID_PEPPY);
            }
        }

        if (this->swork[SO_SWK_11] == 50) {
            gActors[9].dmgType = DMG_COLLISION;
            AUDIO_PLAY_SFX(NA_SE_EN_OUT_MAGMA, this->sfxSource, 4);
        }
    }
}

void Solar_801A3468(SoVulkain* this) {
    this->swork[SO_SWK_0] = 4;
    this->work_048 = 0;

    if ((this->swork[SO_SWK_2] != 0) || (this->swork[SO_SWK_3] != 0)) {
        if (this->swork[SO_SWK_3] != 0) {
            this->swork[SO_SWK_1] = 3;
        } else {
            this->swork[SO_SWK_1] = 4;
        }
    } else {
        if (Rand_ZeroOne() >= 0.5f) {
            this->work_048 = 1;
            this->swork[SO_SWK_1] = 5;
        } else {
            this->timer_050 = 0;
            this->swork[SO_SWK_1] = 8;
        }
    }
    this->animFrame = 0;
    this->fwork[SO_FWK_0] = 0.01f;
}

void Solar_801A3510(SoVulkain* this) {
    s32 i;

    switch (this->swork[SO_SWK_1]) {
        case 3:
            if ((this->animFrame == 119) || (this->swork[SO_SWK_3] == 0)) {
                this->animFrame = 0;
                if (this->swork[SO_SWK_2] != 0) {
                    this->swork[SO_SWK_1] = 4;
                } else {
                    this->swork[SO_SWK_1] = 5;
                }
            }

            if (this->animFrame == 29) {
                Object_SetSfxSourceToPos(this->sfxSource, &this->obj.pos);
                AUDIO_PLAY_SFX(NA_SE_EN_OUT_PROMINENCE, this->sfxSource, 4);
            }

            if (this->animFrame == 80) {
                AUDIO_PLAY_SFX(NA_SE_EN_SOBOSS_SWING, this->sfxSource, 4);
            }

            if (this->animFrame == 94) {
                Solar_801A0DF8(this->fwork[SO_FWK_13], this->fwork[SO_FWK_15], RAND_FLOAT_CENTERED(60.0f), 4, 2.0f);
                this->timer_050 = 90;
            }
            break;

        case 4:
            if ((this->animFrame == 99) || (this->swork[SO_SWK_2] == 0)) {
                this->animFrame = 0;
                this->swork[SO_SWK_1] = 5;
            }

            Math_SmoothStepToAngle(&this->obj.rot.x, 20.0f, 0.1f, 10.0f, 0.1f);

            if (this->animFrame == 10) {
                Object_SetSfxSourceToPos(this->sfxSource, &this->obj.pos);
                AUDIO_PLAY_SFX(NA_SE_EN_OUT_PROMINENCE, this->sfxSource, 4);
            }

            if (this->animFrame == 50) {
                AUDIO_PLAY_SFX(NA_SE_EN_SOBOSS_SWING, this->sfxSource, 4);
            }

            if (this->animFrame == 60) {
                Solar_801A0D90(this->obj.pos.x, this->obj.pos.z + 1600.0f, 80.0f, 2);
                gControllerRumbleFlags[gMainController] = 1;
                gControllerRumbleTimers[gMainController] = 100;
            }
            break;

        case 5:
            Math_SmoothStepToAngle(&this->obj.rot.x, 0.0f, 0.1f, 10.0f, 0.1f);
            if (this->animFrame == 65) {
                for (i = 0; i < 4; i++) {
                    Solar_8019F194(this->obj.pos.x, this->obj.pos.y + 300.0f, this->obj.pos.z + 1000.0f,
                                   D_i3_801BF8F0[i].x + RAND_FLOAT_CENTERED(0.25f),
                                   D_i3_801BF8F0[i].y + RAND_FLOAT_CENTERED(0.25f), RAND_FLOAT(10.0f) + 100.0f);
                }
            }

            if ((this->work_048 != 0) && (this->animFrame == 68)) {
                this->swork[SO_SWK_1] = 9;
                this->fwork[SO_FWK_0] = 0.01f;
                this->animFrame = 20;
            }

            if (this->animFrame == 99) {
                Solar_801A30CC(this);
            }
            break;

        case 8:
            if (this->animFrame == 65) {
                AUDIO_PLAY_SFX(NA_SE_EN_SOBOSS_BREATH, this->sfxSource, 4);
                this->timer_050 = 30;
            }

            if (this->timer_050 != 0) {
                this->animFrame = 65;
            }

            if ((this->animFrame == 65) && (gGameFrameCount % 2) == 0) {
                Solar_8019FFC0(this, this->fwork[SO_FWK_4], this->fwork[SO_FWK_5] - 100.0f,
                               this->fwork[SO_FWK_6] + 600.0f, (this->timer_050 * 0.2f) + 4.0f, 0);
                Solar_801A1EB0(this, this->fwork[SO_FWK_4], 25.0f, this->fwork[SO_FWK_5] - 100.0f,
                               this->fwork[SO_FWK_6] + 300.0f);
            }

            if (this->animFrame == 75) {
                Audio_KillSfxBySourceAndId(this->sfxSource, NA_SE_EN_SOBOSS_BREATH);
            }
            if (this->animFrame == 99) {
                this->swork[SO_SWK_1] = 5;
                this->animFrame = 0;
            }
            break;

        case 9:
            this->animFrame++;
            if (this->animFrame == 66) {
                AUDIO_PLAY_SFX(NA_SE_EN_SOBOSS_BREATH, this->sfxSource, 4);
                this->timer_050 = 30;
            }

            if (this->timer_050 != 0) {
                this->animFrame = 66;
            }

            if ((this->animFrame == 66) && ((gGameFrameCount % 2) == 0)) {
                Solar_8019FFC0(this, this->fwork[SO_FWK_4] + 125.0f, this->fwork[SO_FWK_5] - 100.0f,
                               this->fwork[SO_FWK_6] + 600.0f, (this->timer_050 * 0.2f) + 4.0f, 1);
                Solar_8019FFC0(this, this->fwork[SO_FWK_4] - 125.0f, this->fwork[SO_FWK_5] - 100.0f,
                               this->fwork[SO_FWK_6] + 600.0f, (this->timer_050 * 0.2f) + 4.0f, 2);
                Solar_801A1EB0(this, this->fwork[SO_FWK_4], 25.0f, this->fwork[SO_FWK_5] - 100.0f,
                               this->fwork[SO_FWK_6] + 300.0f);
            }

            if (this->animFrame == 76) {
                Audio_KillSfxBySourceAndId(this->sfxSource, NA_SE_EN_SOBOSS_BREATH);
            }

            if (this->animFrame >= 99) {
                Solar_801A30CC(this);
            }
            break;
    }

    if (this->timer_050 == 0) {
        Object_Kill(&gActors[6].obj, gActors[6].sfxSource);
    } else {
        Math_SmoothStepToF(&gActors[6].obj.pos.x, gPlayer[0].pos.x, 0.1f, 10.0f, 0.1f);
    }
}

void Solar_801A3C4C(SoVulkain* this) {
    s32 i;

    if ((this->swork[SO_SWK_2] == 0) && (this->swork[SO_SWK_3] == 0) &&
        ((this->dmgPart == 8) || (this->dmgPart == -1))) {
        this->health -= this->damage;
        if (this->health < 0) {
            this->health = 0;
        }

        this->swork[SO_SWK_10] = 20;
        if (this->health > 0.0f) {
            AUDIO_PLAY_SFX(NA_SE_EN_SOBOSS_DAMAGE, this->sfxSource, 4);
        }
        if (this) {} //! FAKE
    }

    this->timer_058 = 20;

    if ((this->dmgPart >= 1) && (this->dmgPart <= 3) && (this->swork[SO_SWK_2] != 0)) {
        AUDIO_PLAY_SFX(NA_SE_EN_SOBOSS_DAMAGE, this->sfxSource, 4);

        this->swork[SO_SWK_2] -= this->damage;
        if (this->swork[SO_SWK_2] < 0) {
            this->swork[SO_SWK_2] = 0;
        }
        if (this->swork[SO_SWK_2] == 0) {
            for (i = 0; i < 6; i++) {
                this->info.hitbox[7 + i] = this->info.hitbox[13 + i] = this->info.hitbox[19 + i] = 0.0f;
            }
            this->swork[SO_SWK_2] = -1;
            Solar_801A48B8(this);
        } else {
            this->swork[SO_SWK_8] = 20;
        }
    }

    if ((this->dmgPart >= 4) && (this->dmgPart <= 6) && (this->swork[SO_SWK_3] != 0)) {
        AUDIO_PLAY_SFX(NA_SE_EN_SOBOSS_DAMAGE, this->sfxSource, 4);

        this->swork[SO_SWK_3] -= this->damage;
        if (this->swork[SO_SWK_3] < 0) {
            this->swork[SO_SWK_3] = 0;
        }
        if (this->swork[SO_SWK_3] == 0) {
            for (i = 0; i < 6; i++) {
                this->info.hitbox[25 + i] = this->info.hitbox[31 + i] = this->info.hitbox[37 + i] = 0.0f;
            }
            this->swork[SO_SWK_3] = -1;
            Solar_801A48B8(this);
        } else {
            this->swork[SO_SWK_9] = 20;
        }
    }

    if (this->health <= 0) {
        this->animFrame = 21;
        this->state = 0;
        this->swork[SO_SWK_1] = 1;
        this->fwork[SO_FWK_0] = 0.01f;
        this->info.hitbox = SEGMENTED_TO_VIRTUAL(gNoHitbox);
        this->timer_058 = 20000;

        gTeamLowHealthMsgTimer = -1;

        gFillScreenRed = gFillScreenGreen = gFillScreenBlue = gFillScreenAlpha = 255;
        gFillScreenAlphaTarget = 0;
        gFillScreenAlphaStep = 255;

        gCsFrameCount = 0;

        gControllerRumbleFlags[gMainController] = 1;
        gControllerRumbleTimers[gMainController] = 10;

        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 1);
        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 1);

        Audio_KillSfxById(NA_SE_OVERHEAT_ALARM);

        AUDIO_PLAY_SFX(NA_SE_EN_DOWN_IMPACT, this->sfxSource, 4);

        if (gPlayer[0].state == PLAYERSTATE_ACTIVE) {
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
        this->fwork[SO_FWK_31] = 0.0f;
        this->fwork[SO_FWK_3] = 2400.0f;
        Radio_PlayMessage(gMsg_ID_15252, RCID_SLIPPY);
    }
}

void Solar_801A4214(SoVulkain* this) {
    s32 i;
    Vec3f sp50;
    Vec3f sp44;

    if (this->health > 0) {
        return;
    }

    Math_SmoothStepToAngle(&this->obj.rot.y, 0.0f, 0.1f, 3.0f, 0.0f);
    Math_SmoothStepToAngle(&this->obj.rot.x, 0.0f, 0.1f, 3.0f, 0.0f);

    if ((this->animFrame == 52) && (this->swork[SO_SWK_1] == 5)) {
        this->animFrame = 38;
        this->fwork[SO_FWK_0] = 0.05f;
    }

    Matrix_RotateX(gCalcMatrix, this->fwork[SO_FWK_1] * M_DTOR, MTXF_NEW);
    Matrix_RotateY(gCalcMatrix, -this->fwork[SO_FWK_2] * M_DTOR, MTXF_APPLY);

    sp50.x = 0.0f;
    sp50.y = 200.0f;
    sp50.z = 1100.0f;

    Matrix_MultVec3f(gCalcMatrix, &sp50, &sp44);

    if (this->state >= 2) {
        Math_SmoothStepToF(&D_ctx_801779A8[gMainController], 30.0f, 1.0f, 2.5f, 0.0f);
    }

    switch (this->state) {
        case 0:
            if (D_i3_801C2740[0] >= 33) {
                D_i3_801C2740[0] -= 3;
            }

            if (this->timer_058 == 19910) {
                this->state++;
                this->swork[SO_SWK_1] = 5;
                this->animFrame = 0;
                this->fwork[SO_FWK_0] = 0.05f;
            }

            Math_SmoothStepToF(&this->obj.pos.y, 180.0f, 0.1f, 10.0f, 0.1f);
            break;

        case 1:
            if (this->animFrame == 51) {
                this->animFrame = 50;
                this->state++;

                gShowBossHealth = false;

                AUDIO_PLAY_SFX(NA_SE_EN_SOBOSS_DOWN, this->sfxSource, 4);

                Solar_801A1E14(this->fwork[SO_FWK_4], this->fwork[SO_FWK_5] + 300.0f, this->fwork[SO_FWK_6],
                               this->fwork[SO_FWK_1], this->fwork[SO_FWK_2], 73.0f, RAND_FLOAT_CENTERED(50.0f), 80.0f,
                               40.0f, 8);

                D_i3_801C2768[3] = 6.0f;
                D_i3_801C2768[2] = 100.0f;

                gFillScreenAlpha = 255;
                gFillScreenRed = 255;
                gFillScreenGreen = 255;
                gFillScreenBlue = 255;
                gFillScreenAlphaTarget = 0;
                gFillScreenAlphaStep = 4;

                Boss_AwardBonus(this);

                this->swork[SO_SWK_4]++;

                Math_SmoothStepToF(&this->obj.pos.y, 180.0f, 0.1f, 10.0f, 0.1f);
            }
            break;

        case 2:
            if (D_i3_801C2740[0] >= 33) {
                D_i3_801C2740[0] -= 3;
            }
            if (D_i3_801C2740[1] >= 33) {
                Math_SmoothStepToF(&this->obj.pos.y, 180.0f, 0.1f, 10.0f, 0.1f);
                D_i3_801C2740[1] -= 4;
            } else {
                this->state++;
            }
            break;

        case 3:
            if ((gCsFrameCount >= 205) && (D_i3_801C2768[5] < 1.0f)) {
                D_i3_801C2768[5] += 0.1f;
            }
            if ((gCsFrameCount >= 207) && (D_i3_801C2768[9] < 1.0f)) {
                D_i3_801C2768[9] += 0.1f;
            }
            if ((gCsFrameCount >= 209) && (D_i3_801C2768[10] < 1.0f)) {
                D_i3_801C2768[10] += 0.1f;
            }
            if ((gCsFrameCount >= 211) && (D_i3_801C2768[7] < 1.0f)) {
                D_i3_801C2768[7] += 0.1f;
            }
            if ((gCsFrameCount >= 213) && (D_i3_801C2768[8] < 1.0f)) {
                D_i3_801C2768[8] += 0.1f;
            }
            if ((gCsFrameCount >= 215) && (D_i3_801C2768[11] < 1.0f)) {
                D_i3_801C2768[11] += 0.1f;
            }
            if ((gCsFrameCount >= 217) && (D_i3_801C2768[12] < 1.0f)) {
                D_i3_801C2768[12] += 0.1f;
            }
            if ((gCsFrameCount >= 219) && (D_i3_801C2768[4] < 1.0f)) {
                D_i3_801C2768[4] += 0.1f;
            }
            if ((gCsFrameCount >= 221) && (D_i3_801C2768[6] < 1.0f)) {
                D_i3_801C2768[6] += 0.2f;
            }
            if ((gCsFrameCount >= 226) && (D_i3_801C2768[13] < 380.0f)) {
                D_i3_801C2768[13] += 30.0f;
            }
            if (gCsFrameCount >= 238) {
                D_i3_801C2768[13] = 0.0f;
            }

            if (gCsFrameCount == 230) {
                AUDIO_PLAY_SFX(NA_SE_EN_STAR_EXPLOSION, gActors[5].sfxSource, 4);
                D_ctx_801779A8[gMainController] = 120.0f;
            }

            if (gCsFrameCount == 250) {
                this->state++;
                this->obj.pos.y = -1600.0f;
                for (i = 0; i < 2; i++) {
                    if (gEffects[i].obj.status != OBJ_FREE) {
                        Object_Kill(&gEffects[i].obj, gEffects[i].sfxSource);
                    }
                }
                this->timer_058 = 100;
            }
            break;

        case 4:
            if (this->timer_058 == 1) {
                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 80);
                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 80);
                Object_Kill(&this->obj, this->sfxSource);
            }
            break;
    }
}

void Solar_801A48B8(SoVulkain* this) {
    s32 i;

    AUDIO_PLAY_SFX(NA_SE_EN_SOBOSS_BROKEN, this->sfxSource, 4);

    gControllerRumbleFlags[gMainController] = 1;
    gControllerRumbleTimers[gMainController] = 10;

    if (this->swork[SO_SWK_0] != 6) {
        this->swork[SO_SWK_5] = this->swork[SO_SWK_0];
        this->swork[SO_SWK_6] = this->swork[SO_SWK_1];
        this->swork[SO_SWK_7] = this->animFrame;
    }

    if ((this->swork[SO_SWK_0] == 4) && (this->animFrame >= 60) && (this->animFrame < 67)) {
        for (i = 4; i < ARRAY_COUNT(gActors); i++) {
            if (gActors[i].obj.id == OBJ_ACTOR_SO_WAVE) {
                gActors[i].dmgType = DMG_EXPLOSION;
                break;
            }
        }
    }
    gFillScreenRed = gFillScreenGreen = gFillScreenBlue = gFillScreenAlpha = 255;
    gFillScreenAlphaTarget = 0;
    gFillScreenAlphaStep = 64;

    this->swork[SO_SWK_0] = 6;
    this->swork[SO_SWK_1] = 6;
    this->animFrame = 0;
    this->fwork[SO_FWK_0] = 0.01f;

    if (((this->swork[SO_SWK_2] > 0) || (this->swork[SO_SWK_3] > 0)) && (gTeamShields[TEAM_ID_SLIPPY] > 0)) {
        Radio_PlayMessage(gMsg_ID_7086, RCID_SLIPPY);
    }
}

void Solar_801A4A34(SoVulkain* this) {
    if (this->swork[SO_SWK_2] < 0) {
        this->swork[SO_SWK_2] = 0;
        Solar_801A1E14(this->fwork[SO_FWK_28], this->fwork[SO_FWK_29], this->fwork[SO_FWK_30], this->fwork[SO_FWK_41],
                       this->fwork[SO_FWK_42], this->fwork[SO_FWK_43], RAND_FLOAT(-25.0f) - 10.0f,
                       RAND_FLOAT(25.0f) + 30.0f, RAND_FLOAT_CENTERED(25.0f) - 50.0f, 0);
        Solar_801A1E14(this->fwork[SO_FWK_22], this->fwork[SO_FWK_23], this->fwork[SO_FWK_24], this->fwork[SO_FWK_47],
                       this->fwork[SO_FWK_48], this->fwork[SO_FWK_49], RAND_FLOAT(-25.0f) - 10.0f,
                       RAND_FLOAT(25.0f) + 30.0f, RAND_FLOAT_CENTERED(25.0f) - 50.0f, 1);
        Solar_801A1E14(this->fwork[SO_FWK_10], this->fwork[SO_FWK_11], this->fwork[SO_FWK_12], this->fwork[SO_FWK_35],
                       this->fwork[SO_FWK_36], this->fwork[SO_FWK_37], RAND_FLOAT(-25.0f) - 10.0f,
                       RAND_FLOAT(25.0f) + 30.0f, RAND_FLOAT_CENTERED(25.0f) - 50.0f, 2);
    }

    if (this->swork[SO_SWK_3] < 0) {
        this->swork[SO_SWK_3] = 0;
        Solar_801A1E14(this->fwork[SO_FWK_25], this->fwork[SO_FWK_26], this->fwork[SO_FWK_27], this->fwork[SO_FWK_38],
                       this->fwork[SO_FWK_39], this->fwork[SO_FWK_40], RAND_FLOAT(25.0f) + 10.0f,
                       RAND_FLOAT(25.0f) + 30.0f, RAND_FLOAT_CENTERED(25.0f) - 50.0f, 5);
        Solar_801A1E14(this->fwork[SO_FWK_19], this->fwork[SO_FWK_20], this->fwork[SO_FWK_21], this->fwork[SO_FWK_44],
                       this->fwork[SO_FWK_45], this->fwork[SO_FWK_46], RAND_FLOAT(25.0f) + 10.0f,
                       RAND_FLOAT(25.0f) + 30.0f, RAND_FLOAT_CENTERED(25.0f) - 50.0f, 4);
        Solar_801A1E14(this->fwork[SO_FWK_7], this->fwork[SO_FWK_8], this->fwork[SO_FWK_9], this->fwork[SO_FWK_32],
                       this->fwork[SO_FWK_33], this->fwork[SO_FWK_34], RAND_FLOAT(25.0f) + 10.0f,
                       RAND_FLOAT(25.0f) + 30.0f, RAND_FLOAT_CENTERED(25.0f) - 50.0f, 3);
    }

    switch (this->animFrame) {
        case 30:
            AUDIO_PLAY_SFX(NA_SE_EN_SOBOSS_DAMAGE, this->sfxSource, 4);
            /* fallthrough */
        case 35:
        case 97:
            AUDIO_PLAY_SFX(NA_SE_EN_SOBOSS_BROKEN, this->sfxSource, 4);
            break;
    }

    if (this->animFrame == 119) {
        this->swork[SO_SWK_0] = this->swork[SO_SWK_5];
        this->swork[SO_SWK_1] = this->swork[SO_SWK_6];
        if ((this->swork[SO_SWK_5] == 2) || (this->swork[SO_SWK_5] == 3)) {
            this->animFrame = this->swork[SO_SWK_7];
        } else {
            this->animFrame = 0;
        }
        this->fwork[SO_FWK_0] = 0.01f;
    }
}

void Solar_801A4EC0(SoVulkain* this) {
    this->swork[SO_SWK_0] = 7;
    this->swork[SO_SWK_1] = 5;
    this->fwork[SO_FWK_0] = 0.01f;
    this->animFrame = 0;
    this->state = 0;
    this->fwork[SO_FWK_31] = this->obj.rot.y = 0.0f;
}

void Solar_801A4EF8(SoVulkain* this) {
    s32 i;

    if (this->swork[SO_SWK_11] != 0) {
        this->swork[SO_SWK_11]--;
    }

    switch (this->state) {
        case 0:
            this->animFrame = 0;
            if (this->fwork[SO_FWK_31] > 20.0f) {
                this->state++;
                this->swork[SO_SWK_11] = 108;
                this->fwork[SO_FWK_0] = 0.01f;
                this->animFrame = 56;
            }

            if (this->obj.rot.y == 0.0f) {
                AUDIO_PLAY_SFX(NA_SE_EN_SOBOSS_ROLL, this->sfxSource, 4);
            }

            this->fwork[SO_FWK_31] += 0.5f;

            this->obj.rot.y += this->fwork[SO_FWK_31];
            if (this->obj.rot.y >= 360.0f) {
                this->obj.rot.y -= 360.0f;
                AUDIO_PLAY_SFX(NA_SE_EN_SOBOSS_ROLL, this->sfxSource, 4);
            }
            this->rot_078.y = this->obj.rot.y;
            break;

        case 1:
            this->obj.rot.y += this->fwork[SO_FWK_31];
            this->animFrame = 56;
            if (this->obj.rot.y >= 360.0f) {
                this->obj.rot.y -= 360.0f;
                AUDIO_PLAY_SFX(NA_SE_EN_SOBOSS_ROLL, this->sfxSource, 4);
            }

            if (this->swork[SO_SWK_11] <= 45) {
                Math_SmoothStepToF(&this->obj.pos.y, -1000.0f, 0.1f, 20.0f, 0.1f);
            }

            if (this->swork[SO_SWK_11] == 30) {
                Solar_801A0CEC(&gActors[10], this->obj.pos.x, this->obj.pos.z + 1000.0f, 20.0f, 1);

                gControllerRumbleFlags[gMainController] = 1;
                gControllerRumbleTimers[gMainController] = 70;

                for (i = 0; i < 4; i++) {
                    Solar_8019F038(this->obj.pos.x + 100.0f, 100.0f, this->obj.pos.z + 1100.0f,
                                   D_i3_801BF8F0[i].x + RAND_FLOAT_CENTERED(2.0f),
                                   D_i3_801BF8F0[i].y + 10.0f + RAND_FLOAT_CENTERED(2.0f), RAND_FLOAT(-10.0f) - 10.0f);
                    Solar_8019F038(this->obj.pos.x - 100.0f, 100.0f, this->obj.pos.z + 1100.0f,
                                   D_i3_801BF8F0[i].x + RAND_FLOAT_CENTERED(2.0f),
                                   D_i3_801BF8F0[i].y + 10.0f + RAND_FLOAT_CENTERED(2.0f), RAND_FLOAT(-10.0f) - 10.0f);
                }
            }

            if (this->swork[SO_SWK_11] == 16) {
                gActors[10].dmgType = DMG_EXPLOSION;
            }
            if (this->obj.pos.y <= -900.0f) {
                this->state++;
                this->swork[SO_SWK_11] = 500;
                this->obj.pos.y = -1500.0f;
                this->fwork[SO_FWK_3] = 4800.0f;
                this->obj.pos.z = gPlayer[0].trueZpos - this->fwork[SO_FWK_3];
                this->swork[SO_SWK_1] = 0;
                this->rot_078.y = this->obj.rot.y = 0.0f;
                this->vel.y = 0.0f;
                this->obj.rot.x = 0.0f;
            }
            this->rot_078.y = this->obj.rot.y;
            break;

        case 2:
            this->animFrame = 0;

            if (this->swork[SO_SWK_11] == 300) {
                gControllerRumbleFlags[gMainController] = 1;
                gControllerRumbleTimers[gMainController] = 170;
                gCameraShake = 130;
            }

            if (this->swork[SO_SWK_11] == 200) {
                Solar_801A0CEC(&gActors[9], this->obj.pos.x, this->obj.pos.z + 1000.0f, 20.0f, 1);
            }

            if (this->swork[SO_SWK_11] < 200) {
                this->animFrame = 98;
                this->rot_078.y += this->fwork[SO_FWK_31];

                if (this->swork[SO_SWK_11] == 170) {
                    AUDIO_PLAY_SFX(NA_SE_EN_SOBOSS_CRY, this->sfxSource, 4);
                    this->obj.pos.y = -500.0f;
                    gActors[9].dmgType = DMG_EXPLOSION;
                }

                if (this->swork[SO_SWK_11] <= 170) {
                    this->vel.y = COS_DEG(this->obj.rot.x) * 80.0f;
                    this->vel.z = (SIN_DEG(this->obj.rot.x) * 30.0f) + gPlayer[0].vel.z;
                }

                if (this->obj.rot.x < 190.0f) {
                    this->obj.rot.x += 1.0f;
                }

                if (this->swork[SO_SWK_11] == 50) {
                    Solar_801A0CEC(&gActors[10], this->obj.pos.x, this->obj.pos.z + 1000.0f, 80.0f, 2);
                    gControllerRumbleFlags[gMainController] = 1;
                    gControllerRumbleTimers[gMainController] = 100;
                    gCameraShake = 10;
                }

                if (this->obj.pos.y < -1500.0f) {
                    this->state++;
                    this->swork[SO_SWK_11] = 100;
                    this->obj.pos.y = -500.0f;
                    this->fwork[SO_FWK_3] = 4800.0f;
                    this->obj.pos.z = gPlayer[0].trueZpos - this->fwork[SO_FWK_3];
                    this->animFrame = 0;
                    this->obj.rot.x = 0.0f;
                    this->fwork[SO_FWK_31] = this->vel.y = this->vel.z = 0.0f;
                    this->obj.rot.y = 330.0f;
                }
            }
            break;

        case 3:
            Math_SmoothStepToAngle(&this->obj.rot.y, 0.0f, 1.0f, 1.5f, 1.0f);
            if (this->swork[SO_SWK_11] == 65) {
                Solar_801A0CEC(&gActors[9], this->obj.pos.x, this->obj.pos.z + 1000.0f, 20.0f, 1);
            }
            if (this->swork[SO_SWK_11] == 0) {
                this->swork[SO_SWK_11] = 220;
            }
            if (this->swork[SO_SWK_11] == 210) {
                this->animFrame = 0;
                this->swork[SO_SWK_1] = 1;
            }
            if (this->swork[SO_SWK_11] >= 100) {
                Math_SmoothStepToF(&this->obj.pos.y, 180.0f, 0.1f, 10.0f, 0.1f);
            }
            if (this->swork[SO_SWK_11] == 150) {
                Solar_801A3468(this);
                this->fwork[SO_FWK_0] = 0.01f;
            }
            if (this->swork[SO_SWK_11] == 50) {
                gActors[9].dmgType = DMG_EXPLOSION;
            }
            break;
    }
}

void Solar_801A56B8(SoVulkain* this) {
    switch (this->swork[SO_SWK_1]) {
        case 2:
            if (((this->animFrame == 89) && (this->state == 2)) || (this->swork[SO_SWK_2] == 0)) {
                this->animFrame = 0;
                this->state = 0;
                this->rot_078.y = 0.0f;
            }
            if (this->animFrame == 89) {
                this->state++;
                this->rot_078.y += 15.0f;
            }

            Math_SmoothStepToAngle(&this->obj.rot.y, this->rot_078.y, 1.0f, 3.0f, 1.0f);

            if (this->animFrame > 18) {
                this->info.hitbox[20] = 715.0f;
                this->info.hitbox[22] = 440.0f;
                this->info.hitbox[24] = 110.0f;
            }
            if (this->animFrame > 36) {
                this->info.hitbox[20] = 220.0f;
                this->info.hitbox[22] = 715.0f;
                this->info.hitbox[24] = 220.0f;
            }
            break;

        case 4:
            if ((this->animFrame == 99) || (this->swork[SO_SWK_2] == 0)) {
                this->animFrame = 0;
                if ((this->swork[SO_SWK_3] != 0) || (this->swork[SO_SWK_2] != 0)) {
                    this->swork[SO_SWK_1] = 5;
                } else {
                    this->swork[SO_SWK_1] = 7;
                }
            }

            if (this->animFrame > 20) {
                this->info.hitbox[20] = 715.0f;
                this->info.hitbox[22] = 110.0f;
                this->info.hitbox[24] = 275.0f;
            }
            if (this->animFrame > 84) {
                this->info.hitbox[20] = 220.0f;
                this->info.hitbox[22] = 715.0f;
                this->info.hitbox[24] = 220.0f;
            }
            break;

        case 5:
            this->fwork[SO_FWK_3] = 4800.0f;

            if (this->animFrame == 65) {
                this->timer_050 = 30;
            }

            if (this->timer_050 != 0) {
                this->animFrame = 65;
            }

            if ((this->animFrame == 65) && ((gGameFrameCount % 4) == 0)) {
                Solar_8019FFC0(this, this->fwork[SO_FWK_4] + 125.0f, this->fwork[SO_FWK_5] - 100.0f,
                               this->fwork[SO_FWK_6] + 600.0f, ((f32) this->timer_050 * 0.2f) + 4.0f, 1);
                Solar_8019FFC0(this, this->fwork[SO_FWK_4] - 125.0f, this->fwork[SO_FWK_5] - 100.0f,
                               this->fwork[SO_FWK_6] + 600.0f, ((f32) this->timer_050 * 0.2f) + 4.0f, 2);
                Solar_801A1EB0(this, this->fwork[SO_FWK_4], 25.0f, this->fwork[SO_FWK_5] - 100.0f,
                               this->fwork[SO_FWK_6] + 300.0f);
            }
            break;

        case 7:
            if (this->animFrame < 50) {
                if (this->fwork[SO_FWK_31] < 22.0f) {
                    this->fwork[SO_FWK_31] += 0.5f;
                }
                this->obj.rot.y += this->fwork[SO_FWK_31];
            }
            if ((this->animFrame >= 50) && (this->animFrame <= 100)) {
                if (this->fwork[SO_FWK_31] > 0.0f) {
                    this->fwork[SO_FWK_31] -= 0.5f;
                }
                this->obj.rot.y += this->fwork[SO_FWK_31];
            }
            if (this->animFrame >= 100) {
                Math_SmoothStepToAngle(&this->obj.rot.y, 0.0f, 1.0f, 2.0f, 1.0f);
                this->fwork[SO_FWK_31] = 0.0f;
            }
            if (this->animFrame == 120) {
                this->swork[SO_SWK_1] = 5;
                this->animFrame = 0;
                this->fwork[SO_FWK_0] = 0.1f;
            }
            break;
    }
}

SoVulkainfunc D_i3_801BF980[9] = {
    Solar_801A1F80, Solar_801A23F4, Solar_801A2C98, Solar_801A3128, Solar_801A3510,
    Solar_801A4214, Solar_801A4A34, Solar_801A4EF8, Solar_801A56B8,
};

void Solar_SoVulkain_Update(SoVulkain* this) {
    f32 sp1CC;
    f32 sp1C8;
    f32 sp1C4;
    f32 sp1C0;
    s32 sp1BC;
    s32 sp1B8;
    Vec3f frameTable[30];
    Vec3f src;
    Vec3f dest;

    gBossFrameCount++;

    if (this->swork[SO_SWK_9] != 0) {
        this->swork[SO_SWK_9]--;
    }
    if (this->swork[SO_SWK_8] != 0) {
        this->swork[SO_SWK_8]--;
    }
    if (this->swork[SO_SWK_10] != 0) {
        this->swork[SO_SWK_10]--;
    }

    if ((gBossFrameCount == 200) && (gTeamShields[TEAM_ID_FALCO] != 0)) {
        Radio_PlayMessage(gMsg_ID_10310, RCID_FALCO);
    }
    if ((gBossFrameCount == 300) && (gTeamShields[TEAM_ID_SLIPPY] != 0)) {
        Radio_PlayMessage(gMsg_ID_4092, RCID_SLIPPY);
    }
    if ((gBossFrameCount == 450) && (gTeamShields[TEAM_ID_PEPPY] != 0)) {
        Radio_PlayMessage(gMsg_ID_10320, RCID_PEPPY);
    }

    if (this->health != 0) {
        Math_SmoothStepToF(&this->obj.pos.z, gPlayer[0].trueZpos - this->fwork[SO_FWK_3], 1.0f, 60.0f, 1.0f);
    } else {
        Math_SmoothStepToF(&this->obj.pos.z, -(gPathProgress + 2600.0f), 1.0f, 40.0f, 1.0f);
    }

    if (this->swork[SO_SWK_2] != 0) {
        this->info.hitbox[7] = this->fwork[SO_FWK_12] - this->obj.pos.z;
        this->info.hitbox[9] = this->fwork[SO_FWK_11] - this->obj.pos.y;
        this->info.hitbox[11] = this->fwork[SO_FWK_10] - this->obj.pos.x;
        this->info.hitbox[13] = this->fwork[SO_FWK_24] - this->obj.pos.z;
        this->info.hitbox[15] = this->fwork[SO_FWK_23] - this->obj.pos.y;
        this->info.hitbox[17] = this->fwork[SO_FWK_22] - this->obj.pos.x;

        Matrix_RotateY(gCalcMatrix, -this->obj.rot.y * M_DTOR, MTXF_NEW);

        src.x = this->fwork[SO_FWK_28] - this->obj.pos.x;
        src.y = this->fwork[SO_FWK_29] - this->obj.pos.y;
        src.z = this->fwork[SO_FWK_30] - this->obj.pos.z;

        Matrix_MultVec3f(gCalcMatrix, &src, &dest);

        this->info.hitbox[19] = dest.z;
        this->info.hitbox[21] = dest.y;
        this->info.hitbox[23] = dest.x;
    }
    if (this->swork[SO_SWK_3] != 0) {
        this->info.hitbox[25] = this->fwork[SO_FWK_9] - this->obj.pos.z;
        this->info.hitbox[27] = this->fwork[SO_FWK_8] - this->obj.pos.y;
        this->info.hitbox[29] = this->fwork[SO_FWK_7] - this->obj.pos.x;
        this->info.hitbox[31] = this->fwork[SO_FWK_21] - this->obj.pos.z;
        this->info.hitbox[33] = this->fwork[SO_FWK_20] - this->obj.pos.y;
        this->info.hitbox[35] = this->fwork[SO_FWK_19] - this->obj.pos.x;
        this->info.hitbox[37] = this->fwork[SO_FWK_27] - this->obj.pos.z;
        this->info.hitbox[39] = this->fwork[SO_FWK_26] - this->obj.pos.y;
        this->info.hitbox[41] = this->fwork[SO_FWK_25] - this->obj.pos.x;
    }

    if (((gGameFrameCount % 8) == 0) && (this->fwork[SO_FWK_3] < 4800.0f)) {
        if (Play_CheckDynaFloorCollision(&sp1C0, &sp1B8, this->obj.pos.x, this->obj.pos.y - 160.0f, this->obj.pos.z)) {
            Solar_801A1EB0(this, this->obj.pos.x, 50.0f, sp1C0 - 170.0f, this->obj.pos.z + 100.0f);
        }

        if ((this->swork[SO_SWK_2] != 0) &&
            Play_CheckDynaFloorCollision(&sp1C0, &sp1B8, this->fwork[SO_FWK_16], this->fwork[SO_FWK_17],
                                         this->fwork[SO_FWK_18])) {
            Solar_801A1EB0(this, this->fwork[SO_FWK_16], 50.0f, sp1C0 - 150.f, this->fwork[SO_FWK_18] + 150.0f);
        }

        if ((this->swork[SO_SWK_3] != 0) &&
            Play_CheckDynaFloorCollision(&sp1C0, &sp1B8, this->fwork[SO_FWK_13], this->fwork[SO_FWK_14],
                                         this->fwork[SO_FWK_15])) {
            Solar_801A1EB0(this, this->fwork[SO_FWK_13], 50.0f, sp1C0 - 150.0f, this->fwork[SO_FWK_15] + 150.0f);
        }
    }

    if ((((gGameFrameCount % 4) == 0) || (this->fwork[SO_FWK_31] != 0.0f)) &&
        ((this->swork[SO_SWK_0] != 7) || ((gGameFrameCount % 2) == 0))) {
        if ((this->swork[SO_SWK_2] == 0) && ((this->health > 0) || (this->state < 2))) {
            Solar_8019FF44(this, this->fwork[SO_FWK_10], this->fwork[SO_FWK_11], this->fwork[SO_FWK_12],
                           this->fwork[SO_FWK_31] - 20.0f, -1.0f);
        }
        if ((this->swork[SO_SWK_3] == 0) && ((this->health > 0) || (this->state < 2))) {
            Solar_8019FF44(this, this->fwork[SO_FWK_7], this->fwork[SO_FWK_8], this->fwork[SO_FWK_9],
                           this->fwork[SO_FWK_31] - 20.0f, 1.0f);
        }
    }

    Math_SmoothStepToF(&this->fwork[0], 1.0f, 0.01f, 0.01f, 0.0f);

    if ((this->health > 0) || (this->swork[SO_SWK_0] == 0)) {
        D_i3_801BF980[this->swork[SO_SWK_0]](this);
    }

    if (this->timer_058 != 0) {
        Solar_801A4214(this);
    }

    switch (this->swork[SO_SWK_1]) {
        case 0:
            this->animFrame++;
            if (this->animFrame == 75) {
                AUDIO_PLAY_SFX(NA_SE_EN_SOBOSS_CRY, this->sfxSource, 4);
            }
            if (this->animFrame >= Animation_GetFrameCount(&D_SO_601388C)) {
                if (this->health != 0) {
                    this->animFrame = 0;
                    this->swork[SO_SWK_1]++;
                    this->fwork[SO_FWK_0] = 0.01f;
                } else {
                    this->animFrame = Animation_GetFrameCount(&D_SO_601388C) - 1;
                }
            }
            sp1BC = Animation_GetFrameData(&D_SO_601388C, this->animFrame, frameTable);
            break;

        case 1:
            this->animFrame++;
            if (this->animFrame >= Animation_GetFrameCount(&D_SO_600D3DC)) {
                this->animFrame = 0;
            }
            sp1BC = Animation_GetFrameData(&D_SO_600D3DC, this->animFrame, frameTable);
            break;

        case 2:
            this->animFrame++;
            if (this->animFrame >= Animation_GetFrameCount(&D_SO_600E2C4)) {
                this->animFrame = 0;
            }
            sp1BC = Animation_GetFrameData(&D_SO_600E2C4, this->animFrame, frameTable);
            break;

        case 3:
            this->animFrame++;
            if (this->animFrame >= Animation_GetFrameCount(&D_SO_600F744)) {
                this->animFrame = 0;
            }
            sp1BC = Animation_GetFrameData(&D_SO_600F744, this->animFrame, frameTable);
            break;

        case 4:
            this->animFrame++;
            if (this->animFrame >= Animation_GetFrameCount(&D_SO_600C15C)) {
                this->animFrame = 0;
            }
            sp1BC = Animation_GetFrameData(&D_SO_600C15C, this->animFrame, frameTable);
            break;

        case 5:
        case 8:
        case 9:
            this->animFrame++;
            if ((this->animFrame == 45) && (this->health != 0)) {
                AUDIO_PLAY_SFX(NA_SE_EN_SOBOSS_CRY, this->sfxSource, 4);
            }
            if (this->animFrame >= Animation_GetFrameCount(&D_SO_6012C00)) {
                this->animFrame = 0;
            }
            sp1BC = Animation_GetFrameData(&D_SO_6012C00, this->animFrame, frameTable);
            break;

        case 6:
            this->animFrame++;
            if (this->animFrame >= Animation_GetFrameCount(&D_SO_600B1B4)) {
                this->animFrame = 0;
            }
            sp1BC = Animation_GetFrameData(&D_SO_600B1B4, this->animFrame, frameTable);
            break;

        case 7:
            this->animFrame++;
            if (this->animFrame >= Animation_GetFrameCount(&D_SO_6009D30)) {
                this->animFrame = 0;
            }
            sp1BC = Animation_GetFrameData(&D_SO_6009D30, this->animFrame, frameTable);
            break;
    }
    Matrix_RotateZ(gCalcMatrix, -this->vwork[SO_VWK_29].z * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -this->vwork[SO_VWK_29].x * M_DTOR, MTXF_APPLY);
    Matrix_RotateY(gCalcMatrix, -this->vwork[SO_VWK_29].y * M_DTOR, MTXF_APPLY);

    Matrix_RotateZ(gCalcMatrix, -this->obj.rot.z * M_DTOR, MTXF_APPLY);
    Matrix_RotateX(gCalcMatrix, -this->obj.rot.x * M_DTOR, MTXF_APPLY);
    Matrix_RotateY(gCalcMatrix, -this->obj.rot.y * M_DTOR, MTXF_APPLY);

    if ((this->health > 0) && (this->swork[SO_SWK_0] == 1)) {
        src.x = gPlayer[0].pos.x - this->obj.pos.x;
        src.y = gPlayer[0].pos.y - this->obj.pos.y;
        src.z = gPlayer[0].pos.z - this->obj.pos.z;

        Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

        sp1C4 = Math_RadToDeg(Math_Atan2F(dest.x, dest.z));
        sp1CC = sqrtf(SQ(dest.x) + SQ(dest.z));
        sp1C8 = Math_RadToDeg(-Math_Atan2F(dest.y, sp1CC));

        if ((sp1C8 > 30.0f) && (sp1C8 <= 180.0f)) {
            sp1C8 = 30.0f;
        }
        if ((sp1C8 < 330.0f) && (sp1C8 > 180.0f)) {
            sp1C8 = 330.0f;
        }
        if ((sp1C4 > 40.0f) && (sp1C4 <= 180.0f)) {
            sp1C4 = 40.0f;
        }
        if ((sp1C4 < 320.0f) && (sp1C4 > 180.0f)) {
            sp1C4 = 320.0f;
        }
        Math_SmoothStepToAngle(&D_i3_801C2768[1], sp1C4, 0.2f, 4.0f, 0.1f);
        Math_SmoothStepToAngle(&D_i3_801C2768[0], sp1C8, 0.2f, 4.0f, 0.1f);
    } else {
        Math_SmoothStepToAngle(&D_i3_801C2768[1], 0.0f, 0.2f, 4.0f, 0.1f);
        Math_SmoothStepToAngle(&D_i3_801C2768[0], 0.0f, 0.2f, 4.0f, 0.1f);
    }

    Math_SmoothStepToVec3fArray(frameTable, this->vwork, 1, sp1BC, this->fwork[SO_FWK_0], 100.0f, 0.0f);

    if ((this->dmgType != DMG_NONE) && (this->health > 0)) {
        this->dmgType = DMG_NONE;
        AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
        if (!((this->swork[SO_SWK_0] == 0) || (this->swork[SO_SWK_0] == 2) || (this->swork[SO_SWK_0] == 3) ||
              (this->swork[SO_SWK_0] == 6) || ((this->swork[SO_SWK_0] == 7) && (this->state == 2)))) {
            Solar_801A3C4C(this);
        }
    }

    if (gBossFrameCount == 400) {
        gShowBossHealth = true;
    }
    if (gBossFrameCount >= 400) {
        gBossHealthBar = (this->health + this->swork[SO_SWK_2] + this->swork[SO_SWK_3]) * (255.0f / 1400.0f);
    }
}

bool Solar_SoVulkain_OverrideLimbDraw(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    SoVulkain* this = (SoVulkain*) thisx;
    Vec3f sp58 = { 0.0f, 0.0f, 0.0f };
    Vec3f sp4C = { 10.0f, 0.0f, 0.0f };
    Vec3f sp40 = { -10.0f, 0.0f, 0.0f };

    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, D_i3_801C2740[1], D_i3_801C2740[0], D_i3_801C2740[0], 255);

    if (this->fwork[SO_FWK_3] < 4800.0f) {
        RCP_SetupDL_30(64, 32, 32, gFogAlpha, gFogNear, gFogFar);
    } else {
        RCP_SetupDL_30(16, 16, 16, gFogAlpha, gFogNear, gFogFar);
    }

    switch (limbIndex) {
        case 11:
            rot->y -= D_i3_801C2768[1];
            rot->z += D_i3_801C2768[0];
            /* fallthrough */
        case 1:
            if (this->swork[SO_SWK_4] != 0) {
                *dList = NULL;
            } else if (this->swork[SO_SWK_10] != 0) {
                if ((this->swork[SO_SWK_10] % 2) != 0) {
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 32, 32, 128, 255);
                    rot->z += 3.0f;
                } else {
                    rot->z -= 3.0f;
                }
            }
            break;

        case 2:
        case 3:
        case 4:
            if (this->swork[SO_SWK_2] == 0) {
                *dList = NULL;
            }

            if ((this->swork[SO_SWK_8] % 2U) != 0) {
                if ((this->swork[SO_SWK_8] % 2U) != 0) {
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 32, 32, 128, 255);
                    rot->y += 3.0f;
                } else {
                    rot->y -= 3.0f;
                }
            }
            break;

        case 5:
        case 6:
        case 7:
            if (this->swork[SO_SWK_3] == 0) {
                *dList = NULL;
            }
            if ((this->swork[SO_SWK_9] % 2U) != 0) {
                if ((this->swork[SO_SWK_9] % 2U) != 0) {
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 32, 32, 128, 255);
                    rot->y += 3.0f;
                } else {
                    rot->y -= 3.0f;
                }
            }
            break;
    }
    return false;
}

void Solar_SoVulkain_PostLimbDraw(s32 limbIndex, Vec3f* rot, void* thisx) {
    SoVulkain* this = (SoVulkain*) thisx;
    Vec3f spA0 = { 90.0f, 0.0f, -10.0f };
    Vec3f sp94 = { 135.0f, 0.0f, -40.0f };
    Vec3f sp88 = { 106.0f, 0.0f, 0.0f };
    Vec3f sp7C = { 75.0f, 0.0f, 0.0f };
    Vec3f sp70 = { 85.0f, 0.0f, 0.0f };
    Vec3f sp64 = { 10.0f, 2.0f, 0.0f };
    Vec3f sp58 = { 10.0f, -2.0f, 0.0f };
    Vec3f sp4C = { 0.0f, 0.05f, 0.0f };
    Vec3f sp40 = { 0.0f, -0.05f, 0.0f };
    Vec3f sp34 = { 0.0f, 0.0f, 0.0f };
    Vec3f sp28;

    switch (limbIndex) {
        case 11:
            Matrix_MultVec3f(gCalcMatrix, &sp34, &sp28);
            this->fwork[SO_FWK_4] = sp28.x;
            this->fwork[SO_FWK_5] = sp28.y;
            this->fwork[SO_FWK_6] = sp28.z;
            Matrix_GetYRPAngles(gCalcMatrix, &sp28);
            this->fwork[SO_FWK_1] = sp28.x;
            this->fwork[SO_FWK_2] = sp28.y;
            break;

        case 2:
            if (this->swork[SO_SWK_2] > 0) {
                Matrix_Push(&gCalcMatrix);
                Matrix_MultVec3f(gCalcMatrix, &sp88, &sp28);
                this->fwork[SO_FWK_28] = sp28.x;
                this->fwork[SO_FWK_29] = sp28.y;
                this->fwork[SO_FWK_30] = sp28.z;
                Matrix_Pop(&gCalcMatrix);
                Matrix_MultVec3f(gCalcMatrix, &spA0, &sp28);
                this->fwork[SO_FWK_16] = sp28.x;
                this->fwork[SO_FWK_17] = sp28.y;
                this->fwork[SO_FWK_18] = sp28.z;
            }

            if (this->swork[SO_SWK_2] < 0) {
                Matrix_MultVec3f(gCalcMatrix, &sp34, &sp28);
                this->fwork[SO_FWK_28] = sp28.x;
                this->fwork[SO_FWK_29] = sp28.y;
                this->fwork[SO_FWK_30] = sp28.z;
                Matrix_GetYRPAngles(gCalcMatrix, (Vec3f*) &this->fwork[SO_FWK_41]);
            }
            break;

        case 3:
            if (this->swork[SO_SWK_2] > 0) {
                Matrix_MultVec3f(gCalcMatrix, &sp7C, &sp28);
                this->fwork[SO_FWK_22] = sp28.x;
                this->fwork[SO_FWK_23] = sp28.y;
                this->fwork[SO_FWK_24] = sp28.z;
            }
            if (this->swork[SO_SWK_2] < 0) {
                Matrix_MultVec3f(gCalcMatrix, &sp34, &sp28);
                this->fwork[SO_FWK_22] = sp28.x;
                this->fwork[SO_FWK_23] = sp28.y;
                this->fwork[SO_FWK_24] = sp28.z;
                Matrix_GetYRPAngles(gCalcMatrix, (Vec3f*) &this->fwork[SO_FWK_47]);
            }
            break;

        case 4:
            if (this->swork[SO_SWK_2] > 0) {
                Matrix_MultVec3f(gCalcMatrix, &sp70, &sp28);
                this->fwork[SO_FWK_10] = sp28.x;
                this->fwork[SO_FWK_11] = sp28.y;
                this->fwork[SO_FWK_12] = sp28.z;
                Matrix_GetYRPAngles(gCalcMatrix, (Vec3f*) &this->fwork[SO_FWK_35]);
            } else {
                if (gBosses[0].swork[SO_SWK_0] != 7) {
                    Matrix_MultVec3f(gCalcMatrix, &sp64, &sp28);
                } else {
                    Matrix_MultVec3f(gCalcMatrix, &sp4C, &sp28);
                }
                this->fwork[SO_FWK_10] = sp28.x;
                this->fwork[SO_FWK_11] = sp28.y;
                this->fwork[SO_FWK_12] = sp28.z;
            }
            break;

        case 5:
            if (this->swork[SO_SWK_3] > 0) {
                Matrix_Push(&gCalcMatrix);
                Matrix_MultVec3f(gCalcMatrix, &sp88, &sp28);
                this->fwork[SO_FWK_25] = sp28.x;
                this->fwork[SO_FWK_26] = sp28.y;
                this->fwork[SO_FWK_27] = sp28.z;
                Matrix_Pop(&gCalcMatrix);
                Matrix_MultVec3f(gCalcMatrix, &spA0, &sp28);
                this->fwork[SO_FWK_13] = sp28.x;
                this->fwork[SO_FWK_14] = sp28.y;
                this->fwork[SO_FWK_15] = sp28.z;
                Matrix_GetYRPAngles(gCalcMatrix, (Vec3f*) &this->fwork[SO_FWK_38]);
            }
            if (this->swork[SO_SWK_3] < 0) {
                Matrix_MultVec3f(gCalcMatrix, &sp34, &sp28);
                this->fwork[SO_FWK_25] = sp28.x;
                this->fwork[SO_FWK_26] = sp28.y;
                this->fwork[SO_FWK_27] = sp28.z;
            }
            break;

        case 6:
            if (this->swork[SO_SWK_3] > 0) {
                Matrix_MultVec3f(gCalcMatrix, &sp7C, &sp28);
                this->fwork[SO_FWK_19] = sp28.x;
                this->fwork[SO_FWK_20] = sp28.y;
                this->fwork[SO_FWK_21] = sp28.z;
            }
            if (this->swork[SO_SWK_3] < 0) {
                Matrix_MultVec3f(gCalcMatrix, &sp34, &sp28);
                this->fwork[SO_FWK_19] = sp28.x;
                this->fwork[SO_FWK_20] = sp28.y;
                this->fwork[SO_FWK_21] = sp28.z;
                Matrix_GetYRPAngles(gCalcMatrix, (Vec3f*) &this->fwork[SO_FWK_44]);
            }
            break;

        case 7:
            if (this->swork[SO_SWK_3] > 0) {
                Matrix_MultVec3f(gCalcMatrix, &sp70, &sp28);
                this->fwork[SO_FWK_7] = sp28.x;
                this->fwork[SO_FWK_8] = sp28.y;
                this->fwork[SO_FWK_9] = sp28.z;
                Matrix_GetYRPAngles(gCalcMatrix, (Vec3f*) &this->fwork[SO_FWK_32]);
            } else {
                if (gBosses[0].swork[SO_SWK_0] != 7) {
                    Matrix_MultVec3f(gCalcMatrix, &sp58, &sp28);
                } else {
                    Matrix_MultVec3f(gCalcMatrix, &sp40, &sp28);
                }
                this->fwork[SO_FWK_7] = sp28.x;
                this->fwork[SO_FWK_8] = sp28.y;
                this->fwork[SO_FWK_9] = sp28.z;
            }
            break;
    }
}

void Solar_SoVulkain_Draw(SoVulkain* this) {
    s32 i;
    Vec3f spE8[9] = {
        { 150.0f, 300.0f, 100.0f },  { -100.0f, 200.0f, 100.0f }, { 50.0f, 100.0f, 100.0f },
        { 0.0f, 0.0f, -500.0f },     { 790.0f, 630.0f, -600.0f }, { 280.0f, 140.0f, 500.0f },
        { -210.0f, 110.0f, 500.0f }, { -460.0f, 260.0f, 500.0f }, { 380.0f, 290.0f, 500.0f },
    };
    f32 spC4[9] = {
        -1.0f, -0.3f, -2.0f, 121.0f, 209.0f, 183.0f, 181.0f, 167.0f, 182.0f,
    };
    f32 spA0[9] = {
        -89.0f, -90.0f, -88.0f, -36.0f, -73.0f, -95.0f, -91.0f, -83.0f, -91.0f,
    };

    Matrix_Scale(gCalcMatrix, this->scale, this->scale, this->scale, MTXF_APPLY);

    if (gBossActive) {
        Animation_DrawSkeleton(2, D_SO_600E470, this->vwork, Solar_SoVulkain_OverrideLimbDraw,
                               Solar_SoVulkain_PostLimbDraw, this, gCalcMatrix);
    }

    if (this->health <= 0) {
        RCP_SetupDL_49();
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
        gDPSetEnvColor(gMasterDisp++, 255, 192, 0, 255);
        Matrix_Pop(&gGfxMatrix);
        Matrix_Push(&gGfxMatrix);
        Matrix_Translate(gGfxMatrix, this->obj.pos.x, this->obj.pos.y, this->obj.pos.z - 500.0f + gPathProgress,
                         MTXF_APPLY);
        Matrix_Scale(gGfxMatrix, D_i3_801C2768[3], D_i3_801C2768[2], 1.0f, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, aOrbDL);

        for (i = 0; i < 9; i++) {
            Matrix_Pop(&gGfxMatrix);
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, this->obj.pos.x + spE8[i].x, this->obj.pos.y + spE8[i].y,
                             this->obj.pos.z + gPathProgress + spE8[i].z, MTXF_APPLY);
            Matrix_RotateY(gGfxMatrix, spC4[i] * M_DTOR, MTXF_APPLY);
            Matrix_RotateX(gGfxMatrix, spA0[i] * M_DTOR, MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, D_i3_801C2768[4 + i], 100.0f, 1.0f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, aOrbDL);
        }

        if (D_i3_801C2768[13] > 0.0f) {
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 192, 64, 255);
            Matrix_Pop(&gGfxMatrix);
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, this->obj.pos.x, this->obj.pos.y + 230.0f,
                             this->obj.pos.z - 300.0f + gPathProgress, MTXF_APPLY);
            Matrix_RotateX(gGfxMatrix, M_DTOR * 5.0f, MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, D_i3_801C2768[13], 1.0f, D_i3_801C2768[13], MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_BG_PLANET_20112C0);
            Matrix_Scale(gGfxMatrix, 0.6f, 1.0f, 0.6f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_BG_PLANET_20112C0);
            Matrix_Pop(&gGfxMatrix);
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, this->obj.pos.x, this->obj.pos.y + 270.0f,
                             (this->obj.pos.z - 300.0f) + gPathProgress, MTXF_APPLY);
            Matrix_RotateX(gGfxMatrix, -3.0f * M_DTOR, MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, D_i3_801C2768[13], 1.0f, D_i3_801C2768[13], MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_BG_PLANET_20112C0);
            Matrix_Scale(gGfxMatrix, 0.6f, 1.0f, 0.6f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_BG_PLANET_20112C0);
        }
    }
}

Vec3f D_i3_801BFAF4[5] = {
    { 0.0f, 10.0f, 20.0f },   { 300.0f, 100.0f, 200.0f }, { 100.0f, 60.0f, -260.0f },
    { 80.0f, 100.0f, 80.0f }, { 262.0f, 285.0f, 252.0f },
};

Vec3f D_i3_801BFB30[3] = {
    { 0.0f, 50.0f, 500.0f },
    { -500.0f, 0.0f, 250.0f },
    { 500.0f, 0.0f, 250.0f },
};

void Solar_801A7750(void) {
    ActorCutscene* actor = &gActors[0];
    s32 i;

    Rand_SetSeed(1, 29100, 9786);

    for (i = 0; i < 3; i++, actor++) {
        if ((i == 0) && (gTeamShields[TEAM_ID_PEPPY] <= 0.0f)) {
            continue;
        }
        if ((i == 1) && (gTeamShields[TEAM_ID_SLIPPY] <= 0.0f)) {
            continue;
        }
        if ((i == 2) && (gTeamShields[TEAM_ID_FALCO] <= 0.0f)) {
            continue;
        }

        Actor_Initialize(actor);
        actor->obj.status = OBJ_INIT;
        actor->obj.id = OBJ_ACTOR_CUTSCENE;

        actor->obj.pos.x = D_i3_801BFB30[i].x / 2.0f + gPlayer[0].pos.x;
        actor->obj.pos.y = D_i3_801BFB30[i].y + gPlayer[0].pos.y;
        actor->obj.pos.z = D_i3_801BFB30[i].z + gPlayer[0].pos.z;
        actor->state = 1;
        Object_SetInfo(&actor->info, actor->obj.id);
        actor->iwork[11] = 1;

        if (CVarGetInteger("gTeamFaces", 1) == 1) {
            // @port: Setup team faces
            actor->iwork[14] = i + 2;
        }

        AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, actor->sfxSource, 4);
    }
}

void Solar_LevelComplete(Player* player) {
    s32 i;
    f32 sp78;
    f32 sp74;
    f32 dx;
    f32 dz;
    Vec3f sp60;
    Vec3f sp54;
    SoVulkain* boss = &gBosses[0];

    switch (player->csState) {
        case 0:
            gCsFrameCount = 0;
            player->camRoll = player->aerobaticPitch = 0.0f;
            player->baseSpeed = 40.0f;

            player->arwing.upperRightFlapYrot = player->arwing.upperLeftFlapYrot = player->arwing.bottomRightFlapYrot =
                player->arwing.bottomLeftFlapYrot = player->zRotBarrelRoll = player->zRotBank = player->boostSpeed =
                    0.0f;
            player->draw = true;

            gCsCamEyeX = player->cam.eye.x;
            gCsCamEyeY = player->cam.eye.y;
            gCsCamEyeZ = player->cam.eye.z;

            gCsCamAtX = player->cam.at.x;
            gCsCamAtY = player->cam.at.y;
            gCsCamAtZ = player->cam.at.z;

            for (i = 10; i < ARRAY_COUNT(gActors); i++) {
                if (gActors[i].animFrame == 0) {
                    Object_Kill(&gActors[i].obj, gActors[i].sfxSource);
                }
            }

            Object_Kill(&gActors[2].obj, gActors[2].sfxSource);
            Object_Kill(&gActors[3].obj, gActors[3].sfxSource);
            Object_Kill(&gActors[4].obj, gActors[4].sfxSource);

            player->csState = 1;

            D_ctx_80177A48[0] = 0.1f;
            if (Rand_ZeroOne() > 0.5f) {
                D_ctx_80177A48[9] = -1.0f;
            } else {
                D_ctx_80177A48[9] = 1.0f;
            }
            break;

        case 1:
            gPathTexScroll += 30.0f;

            Math_SmoothStepToF(&player->rot.x, 0.0f, 0.1f, 5.0f, 0.0f);
            Math_SmoothStepToF(&player->pos.y, 200.0f, 0.05f, 10.0f, 0.0f);

            dx = player->pos.x - boss->obj.pos.x;
            dz = (player->pos.z - boss->obj.pos.z) * 0.05f;
            sp78 = Math_RadToDeg(-Math_Atan2F(dx, dz));

            Math_SmoothStepToF(&gCsCamEyeY, 300.0f, 1.0f, 20.0f, 0.0f);
            Math_SmoothStepToF(&gCsCamAtY, 290.0f, 1.0f, 20.0f, 0.0f);

            sp74 = Math_SmoothStepToAngle(&player->rot.y, sp78, 0.5f, 2.0f, 0.0001f) * 30.0f;

            if (gCsFrameCount >= 14) {
                Math_SmoothStepToAngle(&player->rot.z, sp74, 0.1f, 5.0f, 0.0001f);
                gCsCamAtX = 0.0f;
                gCsCamEyeX = 0.0f;
            } else if (sp74 < 0.0f) {
                player->rot.z -= 30.0f;
            } else {
                player->rot.z += 30.0f;
            }

            if (gCsFrameCount >= 200) {
                player->rot.x += 1.0f;
                player->rot.y += 1.0f;
                player->rot.z += 1.0f;
            }

            if (gCsFrameCount >= 230) {
                gFillScreenAlphaTarget = 255;
                gFillScreenRed = gFillScreenBlue = gFillScreenGreen = 255;
            }

            if (gCsFrameCount == 230) {
                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 50);
                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 50);
            }

            if (gCsFrameCount == 400) {
                player->csState++;
                Play_ClearObjectData();
                Audio_StopPlayerNoise(0);
                Audio_KillSfxBySource(player->sfxSource);
                gFillScreenAlpha = 250;
                player->csTimer = 20;
                player->baseSpeed = 0.0f;
                player->rot.x = 0.0f;
                player->rot.y = 0.0f;
                player->rot.z = 0.0f;
            }
            break;

        case 2:
            gPathTexScroll += 60.0f;
            if (player->csTimer == 0) {
                player->pos.x = 0.0f;
                player->pos.y = 200.0f;
                player->pos.z = -(gPathProgress - 500.0f);
                player->csState++;
                player->arwing.drawFace = true;

                Audio_StartPlayerNoise(0);

                AUDIO_PLAY_BGM(NA_BGM_COURSE_CLEAR);

                gDrawGround = true;

                Play_ClearObjectData();

                D_ctx_80177A48[1] = 0.0f;
                D_ctx_80177A48[2] = 0.0f;

                player->cam.eye.x = 0.0f;
                player->cam.eye.y = player->pos.y + 80.0f;
                player->cam.eye.z = player->pos.z + gPathProgress - 4000.0f;

                gCsCamEyeZ = player->pos.z + gPathProgress - 4900.0f;

                player->cam.at.x = gCsCamAtX = 0.0f;
                player->cam.at.y = gCsCamAtY = 200.0f;
                player->cam.at.z = gCsCamAtZ = player->pos.z + gPathProgress;

                D_ctx_80177A48[0] = 0.0f;
                Object_Kill(&gActors[4].obj, gActors[4].sfxSource);
                Object_Kill(&gActors[5].obj, gActors[5].sfxSource);
            }
            break;

        case 3:
            gPathTexScroll += 60.0f;
            gFillScreenAlphaTarget = 0;
            gFillScreenAlphaStep = 4;

            if (gMsgCharIsPrinting) {
                player->arwing.teamFaceXrot = (s32) (gGameFrameCount % 2U) * 5.0f;
            }

            switch (gCsFrameCount) {
                case 450:
                    Solar_801A0DF8(-1200.0f, -(gPathProgress + 2500.0f), 90.0f, 2, 1.0f);
                    break;

                case 545:
                    Solar_801A0DF8(1400.0f, -(gPathProgress + 3250.0f), -90.0f, 3, 1.0f);
                    break;

                case 550:
                    Object_Kill(&gActors[4].obj, gActors[4].sfxSource);
                    break;

                case 645:
                    Object_Kill(&gActors[5].obj, gActors[5].sfxSource);
                    break;

                case 700:
                    player->csState++;
                    Solar_801A7750();
                    D_i3_801C2768[3] = 1000.0f;
                    break;
            }

            if ((gCsFrameCount >= 520) && (gCsFrameCount < 605)) {
                Math_SmoothStepToF(&player->pos.x, 400.0f, 0.1f, 10.0f, 0.1f);
            }
            if ((gCsFrameCount >= 520) && (gCsFrameCount < 570)) {
                Math_SmoothStepToAngle(&player->rot.z, -30.0f, 0.1f, 5.0f, 0.1f);
            }
            if ((gCsFrameCount >= 570) && (gCsFrameCount < 605)) {
                Math_SmoothStepToAngle(&player->rot.z, 0.0f, 0.1f, 5.0f, 0.1f);
            }
            if ((gCsFrameCount >= 605) && (gCsFrameCount < 620)) {
                player->rot.z += 30.0f;
            }
            if ((gCsFrameCount >= 620) && (gCsFrameCount < 640)) {
                Math_SmoothStepToAngle(&player->rot.z, 45.0f, 0.1f, 5.0f, 0.0f);
            }
            if (gCsFrameCount >= 640) {
                Math_SmoothStepToAngle(&player->rot.z, 0.0f, 0.3f, 7.0f, 0.0f);
            }
            if (gCsFrameCount >= 585) {
                Math_SmoothStepToF(&player->pos.x, 0.0f, 0.2f, 9.0f, 0);
            }
            if (gCsFrameCount >= 600) {
                Math_SmoothStepToF(&player->pos.y, 950.0f, 0.1f, 10.0f, 0.0001f);
            }

            Math_SmoothStepToF(&player->pos.z, -(gPathProgress + 4350.0f), 1.0f, 20.0f, 0.0001f);

            if (gCsFrameCount >= 620) {
                Math_SmoothStepToF(&player->cam.eye.x, 0.0f, 1.0f, 10.0f, 0);
                Math_SmoothStepToF(&player->cam.eye.y, player->pos.y + 52.0f, 1.0f, 16.0f, 0.0f);
                Math_SmoothStepToF(&player->cam.eye.z, (player->pos.z + gPathProgress) - 50.0f, 1.0f, 21.5f, 0.0f);
            }
            player->cam.at.x = gCsCamAtX = player->pos.x;
            player->cam.at.y = gCsCamAtY = player->pos.y;
            player->cam.at.z = gCsCamAtZ = player->pos.z + gPathProgress;
            break;

        case 4:
            gPathTexScroll += 60.0f;

            gFillScreenAlphaTarget = 0;
            gFillScreenAlphaStep = 4;

            D_ctx_80177A48[1] += D_ctx_80177A48[2] * 0.8f;

            Matrix_RotateY(gCalcMatrix, D_ctx_80177A48[1] * M_DTOR, MTXF_NEW);

            sp60.x = 0.0f;
            sp60.y = 0.0f;
            sp60.z = -700.0f;

            Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp60, &sp54);

            if (gCsFrameCount < 1440) {
                gCsCamEyeX = sp54.x;
                gCsCamEyeY = D_i3_801C2768[3] + sp54.y;
                gCsCamEyeZ = player->pos.z + gPathProgress + sp54.z;
                gCsCamAtX = 0.0f;
                gCsCamAtY = player->pos.y + 75.0f;
                Math_SmoothStepToF(&D_i3_801C2768[3], 500.0f, 0.1f, 1.0f, 0.0001f);
                gCsCamAtZ = player->pos.z + gPathProgress + 200.0f;

                if (gCsFrameCount >= 1400) {
                    gCsCamAtZ -= (gCsFrameCount * 8) - 11200;
                }
            } else {
                Math_SmoothStepToF(&gCsCamEyeX, 0.0f, 0.1f, 1.0f, 0.0001f);
                gCsCamAtX = 0.0f;
                gCsCamAtY = player->pos.y + 75.0f;
                gCsCamAtZ = player->pos.z + gPathProgress + 200.0f - ((gCsFrameCount * 8) - 11200);
            }

            if (gCsFrameCount > 1460) {
                player->baseSpeed += 2.0f;
                player->rot.x += 0.2f;
                Math_SmoothStepToF(&D_ctx_80177A48[2], 0.0f, 1.0f, 0.001f, 0);
                player->unk_190 = 2.0f;
            } else {
                Math_SmoothStepToF(&D_ctx_80177A48[2], 0.23f, 1.0f, 0.001f, 0.0f);
                Math_SmoothStepToF(&D_ctx_80177A48[0], 0.5f, 0.1f, 0.0005f, 0.0f);
            }

            if (gCsFrameCount == 1560) {
                Play_ClearObjectData();
            }

            if (gCsFrameCount > 1530) {
                gFillScreenAlphaTarget = 255;
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
                gFillScreenAlphaStep = 8;
                if (gFillScreenAlpha == 255) {
                    Audio_StopPlayerNoise(0);
                    Audio_FadeOutAll(10);
                    player->state = PLAYERSTATE_NEXT;
                    player->csTimer = 0;
                    gFadeoutType = 4;
                    gLeveLClearStatus[LEVEL_SOLAR] = Play_CheckMedalStatus(100) + 1;
                }
            }
            break;
    }

    switch (gCsFrameCount) {
        case 440:
            gLevelClearScreenTimer = 100;
            break;

        case 640:
            Radio_PlayMessage(gMsg_ID_20010, RCID_FOX);
            break;

        case 728:
            switch (gTeamShields[TEAM_ID_SLIPPY]) {
                case 0:
                    Radio_PlayMessage(gMsg_ID_20345, RCID_ROB64);
                    break;
                case -1:
                    Radio_PlayMessage(gMsg_ID_20339, RCID_ROB64);
                    break;
                default:
                    func_demo_80048AC0(TEAM_ID_SLIPPY);
                    break;
            }
            break;

        case 875:
            switch (gTeamShields[TEAM_ID_PEPPY]) {
                case 0:
                    Radio_PlayMessage(gMsg_ID_20344, RCID_ROB64);
                    break;
                case -1:
                    Radio_PlayMessage(gMsg_ID_20338, RCID_ROB64);
                    break;
                default:
                    func_demo_80048AC0(TEAM_ID_PEPPY);
                    break;
            }
            break;

        case 1021:
            switch (gTeamShields[TEAM_ID_FALCO]) {
                case 0:
                    Radio_PlayMessage(gMsg_ID_20343, RCID_ROB64);
                    break;
                case -1:
                    Radio_PlayMessage(gMsg_ID_20337, RCID_ROB64);
                    break;
                default:
                    func_demo_80048AC0(TEAM_ID_FALCO);
                    break;
            }
            break;

        case 1186:
            gShowLevelClearStatusScreen = true;
            break;

        case 1386:
            gShowLevelClearStatusScreen = false;
            break;

        case 1460:
            AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, player->sfxSource, 0);
            player->unk_190 = player->unk_194 = 5.0f;
            break;

        case 1400:
            if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                gActors[0].state = 2;
            }
            break;

        case 1500:
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 50);
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 50);
            break;

        case 1420:
            if (gTeamShields[TEAM_ID_SLIPPY] > 0) {
                gActors[1].state = 2;
            }
            break;

        case 1440:
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

void Solar_801A8BE8(ActorCutscene* this) {
    Vec3f src;
    Vec3f dest;

    switch (this->state) {
        case 4:
            break;
        case 1:
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
            this->rot_0F4.x += 0.2f;
            break;
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

void Solar_801A8DB8(Vec3f* pos, u32 sfxId, f32 zVel) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Effect_SetupTimedSfxAtPos(&gEffects[i], pos, sfxId);
            gEffects[i].vel.z = zVel;
            break;
        }
    }
}
