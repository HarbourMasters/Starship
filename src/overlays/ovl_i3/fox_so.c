/*
 * File: fox_so.c
 * System: Solar
 * Description: Level: Solar
 */

#include "global.h"
#include "assets/ast_bg_planet.h"
#include "assets/ast_solar.h"

typedef void (*BossSOfunc)(Boss*);

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
} BossSOswork;

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
} BossSOfwork;

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
} BossSOvwork;

void Solar_801A239C(Boss* bossSO);
void Solar_801A2C3C(Boss* bossSO);
void Solar_801A3468(Boss* bossSO);
void Solar_801A48B8(Boss* bossSO);
void Solar_801A4EC0(Boss* bossSO);
void Solar_801A8DB8(Vec3f* pos, u32 sfxId, f32 zVel);

s32 D_i3_801C2740[10];
f32 D_i3_801C2768[14];
s32 D_i3_801C27A0[8]; // unused? part of previous?

void Solar_8019E7F0(Effect* effect, f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_ACTIVE;
    effect->obj.id = OBJ_EFFECT_392;
    effect->state = 3;
    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;
    effect->obj.rot.z = 180.0f;
    if (Rand_ZeroOne() < 0.5f) {
        effect->obj.rot.y = 180.0f;
    }
    effect->unk_44 = 112;
    effect->scale2 = scale2;
    effect->vel.y = 5.0f;
    Object_SetInfo(&effect->info, effect->obj.id);
    effect->info.unk_14 = 0;
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

void Solar_8019E920(Effect* effect, f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 scale2, s32 state) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_ACTIVE;
    effect->obj.id = OBJ_EFFECT_392;
    effect->state = state;
    if (state == 2) {
        effect->timer_50 = 30;
        effect->unk_4C = 3;
    }
    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;
    effect->vel.x = xVel;
    effect->vel.y = yVel;
    effect->vel.z = zVel;
    effect->obj.rot.z = RAND_FLOAT(360.0f);
    effect->unk_44 = 176;
    effect->scale2 = scale2;
    Object_SetInfo(&effect->info, effect->obj.id);
}

void Solar_8019E9F4(f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 scale2, s32 unk4E) {
    s32 i;

    for (i = 99; i >= 34; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Solar_8019E920(&gEffects[i], xPos, yPos, zPos, xVel, yVel, zVel, scale2, unk4E);
            break;
        }
    }
}

void Solar_8019EA7C(Actor* actor) {
    f32 sp34;
    s32 sp30;

    if (actor->state == 0) {
        actor->vel.z = 20.0f - D_ctx_80177D08;
        actor->fwork[0] = 12.0f;
    } else {
        actor->vel.z = actor->fwork[1] - D_ctx_80177D08;
        if (actor->state == 2) {
            Math_SmoothStepToF(&actor->obj.pos.x, gPlayer[0].pos.x, 1.0f, 100.0f, 10.0f);
        } else {
            actor->fwork[0] = 14.0f;
        }
    }
    if ((actor->unk_046 == 0) || (actor->unk_046 == 1)) {
        actor->unk_046 = 3;
        func_edisplay_8005F0E8(actor->sfxSource, &actor->obj.pos);
        AUDIO_PLAY_SFX(0x11002052, actor->sfxSource, 0);
    }
    if (func_play_800A73E4(&sp34, &sp30, actor->obj.pos.x, -100.0f, actor->obj.pos.z)) {
        D_ctx_801782EC[sp30] = actor->fwork[0];
        D_ctx_801782EC[sp30 + 1] = actor->fwork[0] * 0.95f;
        D_ctx_801782EC[sp30 - 1] = actor->fwork[0] * 0.95f;
        D_ctx_801782EC[sp30 + 2] = actor->fwork[0] * 0.9f;
        D_ctx_801782EC[sp30 - 2] = actor->fwork[0] * 0.9f;
        D_ctx_801782EC[sp30 + 3] = actor->fwork[0] * 0.8f;
        D_ctx_801782EC[sp30 - 3] = actor->fwork[0] * 0.8f;
        if (actor->state != 2) {
            D_ctx_801782EC[sp30 + 4] = actor->fwork[0] * 0.65f;
            D_ctx_801782EC[sp30 - 4] = actor->fwork[0] * 0.65f;
            D_ctx_801782EC[sp30 + 5] = actor->fwork[0] * 0.45f;
            D_ctx_801782EC[sp30 - 5] = actor->fwork[0] * 0.45f;
            D_ctx_801782EC[sp30 + 6] = actor->fwork[0] * 0.2f;
            D_ctx_801782EC[sp30 - 6] = actor->fwork[0] * 0.2f;
            D_ctx_801782EC[sp30 + 7] = actor->fwork[0] * 0.1f;
            D_ctx_801782EC[sp30 - 7] = actor->fwork[0] * 0.1f;
        } else {
            D_ctx_801782EC[sp30 + 4] = actor->fwork[0] * 0.75f;
            D_ctx_801782EC[sp30 - 4] = actor->fwork[0] * 0.75f;
            D_ctx_801782EC[sp30 + 5] = actor->fwork[0] * 0.7f;
            D_ctx_801782EC[sp30 - 5] = actor->fwork[0] * 0.7f;
            D_ctx_801782EC[sp30 + 6] = actor->fwork[0] * 0.65f;
            D_ctx_801782EC[sp30 - 6] = actor->fwork[0] * 0.65f;
            D_ctx_801782EC[sp30 + 7] = actor->fwork[0] * 0.6f;
            D_ctx_801782EC[sp30 - 7] = actor->fwork[0] * 0.6f;
            D_ctx_801782EC[sp30 + 8] = actor->fwork[0] * 0.55f;
            D_ctx_801782EC[sp30 - 8] = actor->fwork[0] * 0.55f;
            D_ctx_801782EC[sp30 + 9] = actor->fwork[0] * 0.4f;
            D_ctx_801782EC[sp30 - 9] = actor->fwork[0] * 0.4f;
            D_ctx_801782EC[sp30 + 10] = actor->fwork[0] * 0.3f;
            D_ctx_801782EC[sp30 - 10] = actor->fwork[0] * 0.3f;
            D_ctx_801782EC[sp30 + 11] = actor->fwork[0] * 0.2f;
            D_ctx_801782EC[sp30 - 11] = actor->fwork[0] * 0.2f;
            D_ctx_801782EC[sp30 + 12] = actor->fwork[0] * 0.1f;
            D_ctx_801782EC[sp30 - 12] = actor->fwork[0] * 0.1f;
        }
    }
    switch (actor->unk_0D0) {
        case 3:
            Solar_801A8DB8(&actor->obj.pos, 0x11002052, actor->vel.z);
            /* fallthrough */
        case 2:
            Object_Kill(&actor->obj, actor->sfxSource);
            break;
    }
}

void Solar_8019EF30(Actor* actor, f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel) {
    Actor_Initialize(actor);
    actor->obj.status = OBJ_ACTIVE;
    actor->obj.id = OBJ_ACTOR_275;
    if (Rand_ZeroOne() < 0.1f) {
        actor->obj.id = OBJ_ACTOR_276;
    }
    actor->obj.pos.x = xPos;
    actor->obj.pos.y = yPos;
    actor->obj.pos.z = zPos;
    actor->unk_0F4.x = RAND_FLOAT(360.0f);
    actor->vel.x = xVel;
    actor->vel.y = yVel;
    actor->vel.z = zVel;
    actor->state = 2;
    actor->timer_0C2 = 8;
    Object_SetInfo(&actor->info, actor->obj.id);
    if (gBossActive != 0) {
        actor->info.bonus = 0;
    }
    AUDIO_PLAY_SFX(0x29000071, actor->sfxSource, 0);
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

void Solar_8019F0B0(Actor* actor, f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel) {
    Actor_Initialize(actor);
    actor->obj.status = OBJ_ACTIVE;
    actor->obj.id = OBJ_ACTOR_277;
    actor->obj.pos.x = xPos;
    actor->obj.pos.y = yPos;
    actor->obj.pos.z = zPos;
    actor->unk_0F4.x = RAND_FLOAT(360.0f);
    actor->vel.x = xVel;
    actor->vel.y = yVel;
    actor->vel.z = zVel;
    actor->state = 2;
    actor->timer_0C2 = 8;
    Object_SetInfo(&actor->info, actor->obj.id);
    if (gBossActive != 0) {
        actor->info.bonus = 0;
    }
    AUDIO_PLAY_SFX(0x29000071, actor->sfxSource, 0);
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

void Solar_8019F20C(Actor* actor) {
    f32 sp8C = 0.0f;
    s32 sp88;
    s32 i;

    if (actor->obj.id == OBJ_ACTOR_277) {
        actor->scale = 2.0f;
    }
    if (actor->obj.id == OBJ_ACTOR_276) {
        actor->unk_0F4.x -= 6.6f;
        actor->unk_0F4.y -= 4.0f;

    } else {
        actor->unk_0F4.x += 3.3f;
        actor->unk_0F4.y += 2.0f;
    }
    switch (actor->state) {
        case 0:
            actor->fwork[0] = actor->obj.pos.y * 0.05f;
            actor->obj.pos.y = -100.0f;
            /* fallthrough */
        case 1:
            actor->state = 2;
            actor->vel.y = actor->fwork[0];
            func_play_800A73E4(&sp8C, &sp88, actor->obj.pos.x, actor->obj.pos.y - 100.0f, actor->obj.pos.z);
            actor->obj.pos.y = sp8C;
            for (i = 0; i < 4; i++) {
                Solar_8019E9F4(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, D_i3_801BF8E0[i],
                               RAND_FLOAT(10.0f) + 10.0f, 0.0f, actor->scale * 5.0f, 1);
            }
            actor->timer_0C2 = 5;
            AUDIO_PLAY_SFX(0x29000071, actor->sfxSource, 0);
            break;
        case 2:
            actor->gravity = 0.5f;
            if (func_play_800A73E4(&sp8C, &sp88, actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z)) {
                Object_Kill(&actor->obj, actor->sfxSource);
                func_effect_8007A6F0(&actor->obj.pos, 0x29000072);
                for (i = 0; i < 4; i++) {
                    Solar_8019E9F4(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, D_i3_801BF8E0[i],
                                   RAND_FLOAT(10.0f) + 10.0f, 0.0f, actor->scale * 5.0f, 1);
                }
            }
            if (actor->timer_0BC == 0) {
                actor->timer_0BC = 5;
                Solar_8019E9F4(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, 0.0f, 0.0f, 0.0f,
                               actor->scale * 6.5f, 2);
            }
            if ((actor->unk_0D0 != 0) || ((actor->obj.id == OBJ_ACTOR_277) && (actor->vel.y < 0.0f))) {
                func_effect_8007D2C8(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, actor->scale * 4.0f);
                Object_Kill(&actor->obj, actor->sfxSource);
                if (actor->obj.id == OBJ_ACTOR_277) {
                    for (i = 0; i < 4; i++) {
                        Solar_8019F038(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z,
                                       D_i3_801BF8F0[i].x + RAND_FLOAT_CENTERED(3.0f),
                                       D_i3_801BF8F0[i].y + RAND_FLOAT_CENTERED(3.0f), RAND_FLOAT(-10.0f) - 10.0f);
                    }
                } else if (actor->obj.id == OBJ_ACTOR_275) {
                    actor->itemDrop = DROP_SILVER_RING;
                } else if (actor->obj.id == OBJ_ACTOR_276) {
                    if (gGoldRingCount[0] != 4) {
                        actor->itemDrop = DROP_GOLD_RING_1;
                    } else {
                        actor->itemDrop = DROP_SILVER_STAR;
                    }
                }
                Actor_Despawn(actor);
                for (i = 0; i < 3; i++) {
                    func_effect_800794CC(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, 0.3f);
                }
                for (i = 0; i < 7; i++) {
                    Solar_8019E9F4(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, RAND_FLOAT_CENTERED(30.0f),
                                   RAND_FLOAT_CENTERED(30.0f), 0.0f, (RAND_FLOAT(2.0f) + 2.0f) * actor->scale, 1);
                }
                func_effect_8007A6F0(&actor->obj.pos, 0x2903A008);
            }
            break;
    }
    actor->obj.rot.y = RAD_TO_DEG(-gPlayer[0].unk_058);
    actor->obj.rot.x = RAD_TO_DEG(gPlayer[0].unk_05C);
    if (((gGameFrameCount % 2) == 0)) {
        actor->unk_0B6++;
        if (actor->unk_0B6 >= 3) {
            actor->unk_0B6 = 0;
        }
    }
}

void Solar_8019F7AC(Actor* actor) {
    if (actor->state != 0) {
        Matrix_Push(&gGfxMatrix);
        Matrix_RotateY(gGfxMatrix, actor->unk_0F4.y * M_DTOR, 1);
        Matrix_RotateX(gGfxMatrix, actor->unk_0F4.x * M_DTOR, 1);
        Matrix_SetGfxMtx(&gMasterDisp);
        switch (actor->obj.id) {
            case OBJ_ACTOR_275:
                gSPDisplayList(gMasterDisp++, D_SO_6017370);
                break;
            case OBJ_ACTOR_276:
                if (((gGameFrameCount % 2) == 0)) {
                    RCP_SetupDL(&gMasterDisp, 0x29);
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 0, 255);
                }
                gSPDisplayList(gMasterDisp++, D_SO_6017090);
                break;
            case OBJ_ACTOR_277:
                gSPDisplayList(gMasterDisp++, D_SO_6016CF0);
                break;
        }

        Matrix_Pop(&gGfxMatrix);
        Graphics_SetScaleMtx(actor->scale * 3.5f);
        RCP_SetupDL(&gMasterDisp, 0x40);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 128, 128, 160);
        gSPDisplayList(gMasterDisp++, D_i3_801BF92C[actor->unk_0B6]);
    }
}

void Solar_8019F99C(Actor* actor, Effect* effect, f32 scale1) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_ACTIVE;
    effect->obj.id = OBJ_EFFECT_392;
    effect->obj.pos.x = effect->vel.x = actor->obj.pos.x;
    effect->obj.pos.y = -2000.0f;
    effect->vel.y = actor->obj.pos.y;
    effect->obj.pos.z = effect->vel.z = actor->obj.pos.z;
    effect->scale1 = scale1;
    effect->unk_60.y = actor->obj.rot.y;
    effect->obj.rot.z = RAND_FLOAT(360.0f);
    effect->unk_44 = 255 - (actor->unk_04E * 8);
    if (effect->unk_44 < 0) {
        effect->unk_44 = 0;
    }
    effect->scale2 = 20.0f - (actor->unk_04E * 0.5f);
    effect->unk_48 = 1;
    Object_SetInfo(&effect->info, effect->obj.id);
}

void Solar_8019FAA4(Boss* bossSO, Effect* effect, f32 xPos, f32 yPos, f32 zPos, f32 yVel, f32 hVelMod) {
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
                Matrix_RotateY(gCalcMatrix, gBosses[0].obj.rot.y * M_DTOR, 0);
                sp44.y = 0.0f;
                sp44.z = 0.0f;
                sp44.x = gBosses[0].fwork[SO_FWK_31] * 5.0f;
                Matrix_MultVec3f(gCalcMatrix, &sp44, &sp38);
                effect->vel.x = sp38.x * hVelMod;
                effect->vel.z = gPlayer[0].vel.z + (sp38.z * hVelMod);
            } else {
                Matrix_RotateZ(gCalcMatrix, bossSO->obj.rot.z * M_DTOR, 0);
                Matrix_RotateX(gCalcMatrix, gBosses[0].obj.rot.x * M_DTOR, 1);
                Matrix_RotateY(gCalcMatrix, gBosses[0].unk_078.y * M_DTOR, 1);
                sp44.x = effect->obj.pos.x - bossSO->obj.pos.x;
                sp44.y = effect->obj.pos.y - bossSO->obj.pos.y;
                sp44.z = effect->obj.pos.z - bossSO->obj.pos.z;
                Matrix_MultVec3f(gCalcMatrix, &sp44, &sp38);
                effect->obj.pos.x = bossSO->obj.pos.x + sp38.x;
                effect->obj.pos.y = bossSO->obj.pos.y + sp38.y;
                effect->obj.pos.z = bossSO->obj.pos.z + sp38.z;
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
    effect->unk_60.y = bossSO->obj.rot.y;
    effect->unk_60.x = 90.0f;
    effect->obj.rot.z = RAND_FLOAT(360.0f);
    effect->unk_44 = 255;
    effect->unk_48 = 1;
    effect->state = 4;
    effect->unk_4C = 5;
    Object_SetInfo(&effect->info, effect->obj.id);
}

void Solar_8019FDE0(Boss* bossSO, Effect* effect, f32 xPos, f32 yPos, f32 zPos, f32 scale2, s32 state) {
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
    effect->unk_60.y = bossSO->obj.rot.y;
    effect->unk_60.x = 0.0f;
    effect->obj.rot.z = RAND_FLOAT(360.0f);
    effect->unk_44 = 255;
    effect->unk_48 = 1;
    effect->state = state + 5;
    Object_SetInfo(&effect->info, effect->obj.id);
    effect->info.damage = 40;
}

void Solar_8019FEE8(Actor* actor, f32 scale1) {
    s32 i;

    for (i = 70; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Solar_8019F99C(actor, &gEffects[i], scale1);
            break;
        }
    }
}

void Solar_8019FF44(Boss* bossSO, f32 xPos, f32 yPos, f32 zPos, f32 yVel, f32 hVelMod) {
    s32 i;

    for (i = 70; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Solar_8019FAA4(bossSO, &gEffects[i], xPos, yPos, zPos, yVel, hVelMod);
            break;
        }
    }
}

void Solar_8019FFC0(Boss* bossSO, f32 xPos, f32 yPos, f32 zPos, f32 scale2, s32 unk4E) {
    s32 i;

    for (i = 70; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Solar_8019FDE0(bossSO, &gEffects[i], xPos, yPos, zPos, scale2, unk4E);
            break;
        }
    }
}

void Solar_801A003C(Actor* actor) {
    switch (actor->state) {
        case 0:
            if (actor->timer_0BE == 0) {
                actor->state = 1;
                actor->timer_0BE = 50;
            } else if (actor->timer_0BC == 0) {
                actor->timer_0BC = 2;
                Solar_8019FEE8(actor, 1000.0f);
                actor->unk_04E++;
            }
            break;
        case 1:
            if (actor->timer_0BE == 0) {
                actor->state = 0;
                actor->timer_0BE = 50;
                actor->unk_04E = 0;
                func_edisplay_8005F0E8(actor->sfxSource, &actor->obj.pos);
                AUDIO_PLAY_SFX(0x19035053, actor->sfxSource, 4);
            }
            break;
    }
}

void Solar_801A0120(Effect* effect) {
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50 = 1.0f;
    s32 sp4C;
    s32 sp48;
    Vec3f sp3C;

    switch (effect->state) {
        case 0:
            Matrix_Translate(gCalcMatrix, effect->vel.x, effect->vel.y, effect->vel.z, 0);
            Matrix_RotateY(gCalcMatrix, effect->unk_60.y * M_DTOR, 1);
            Matrix_RotateX(gCalcMatrix, effect->unk_60.x * M_DTOR, 1);
            sp3C.x = 0.0f;
            sp3C.y = 0.0f;
            sp3C.z = -effect->scale1;
            Matrix_MultVec3f(gCalcMatrix, &sp3C, &effect->obj.pos);
            effect->unk_60.x += 5.0f;
            if (((gGameFrameCount % 2) == 0)) {
                effect->unk_4C++;
                if (effect->unk_4C > 2) {
                    effect->unk_4C = 0;
                }
            }
            if (gPlayer[0].state_1C8 != PLAYERSTATE_1C8_7) {
                func_effect_8007A774(&gPlayer[0], effect, effect->scale2 * 12.0f);
            }
            if (effect->unk_60.x > 190.0f) {
                Object_Kill(&effect->obj, effect->sfxSource);
            }
            sp48 = effect->unk_48;
            if (func_play_800A73E4(&sp5C, &sp4C, effect->obj.pos.x, effect->obj.pos.y, effect->obj.pos.z)) {
                effect->unk_48 = 1;
                if (effect->scale2 == 20.0f) {
                    AUDIO_PLAY_SFX(0x19035054, effect->sfxSource, 4);
                }
            } else {
                effect->unk_48 = 0;
            }
            if (sp48 != effect->unk_48) {
                if (effect->unk_48 != 0) {
                    sp54 = 50.0f;
                } else {
                    sp54 = -50.0f;
                }
                if ((effect->index % 2) != 0) {
                    sp58 = 100.0f;
                } else {
                    sp58 = -100.0f;
                }
                Solar_8019E9F4(effect->obj.pos.x + sp58, effect->obj.pos.y + sp54, effect->obj.pos.z, sp58 * 0.25f,
                               RAND_FLOAT(10.0f) + 20.0f, sp58 * 0.25f, 20.0f, 1);
            }
            break;
        case 1:
            if (effect->timer_50 == 0) {
                effect->timer_50 = 4;
                effect->unk_4C++;
                if (effect->unk_4C >= 6) {
                    effect->unk_4C = 0;
                    Object_Kill(&effect->obj, effect->sfxSource);
                }
            }
            if (effect->scale2 > 10.0f) {
                effect->vel.y -= 2.5f;
            } else if (effect->scale2 > 4.0f) {
                effect->vel.y -= 1.0f;
            }
            break;
        case 2:
            if (effect->timer_50 == 0) {
                Object_Kill(&effect->obj, effect->sfxSource);
            }
            Math_SmoothStepToF(&effect->scale2, 0.0f, 0.1f, 0.2f, 0.0f);
            effect->obj.rot.z += 3.0f;
            effect->vel.y -= 0.3f;
            break;
        case 3:
            Math_SmoothStepToF(&effect->obj.rot.z, -190.0f, 1.0f, 10.0f, 0.0f);
            effect->vel.y -= 0.3f;
            if (effect->obj.rot.z <= -180.0f) {
                Object_Kill(&effect->obj, effect->sfxSource);
            }
            break;
        case 4:
            if (gBosses[0].swork[SO_SWK_0] != 7) {
                Math_SmoothStepToF(&effect->vel.y, -40.0f, 1.0f, 1.0f, 1.0f);
            } else {
                effect->vel.z = gPlayer[0].vel.z;
                Math_SmoothStepToF(&effect->vel.y, -65.0f, 2.0f, 1.0f, 0.5f);
            }
            if (gPlayer[0].state_1C8 != PLAYERSTATE_1C8_7) {
                func_effect_8007A774(&gPlayer[0], effect, effect->scale2 * 12.0f);
            }
            if (effect->obj.pos.y < -20.0f) {
                Object_Kill(&effect->obj, effect->sfxSource);
            }
            effect->obj.rot.z += 6.0f;
            if (effect->obj.rot.z >= 360.0f) {
                effect->obj.rot.z = 0.0f;
            }
            sp48 = effect->unk_48;
            if (func_play_800A73E4(&sp5C, &sp4C, effect->obj.pos.x, effect->obj.pos.y, effect->obj.pos.z)) {
                effect->unk_48 = 1;
                if (effect->scale2 == 20.0f) {
                    AUDIO_PLAY_SFX(0x19035054, effect->sfxSource, 4);
                }
            } else {
                effect->unk_48 = 0;
            }
            if ((sp48 != effect->unk_48) && (effect->unk_48 != 0)) {
                if ((effect->index % 2) != 0) {
                    sp58 = 100.0f;
                } else {
                    sp58 = -100.0f;
                }
                Solar_8019E9F4(effect->obj.pos.x + sp58, effect->obj.pos.y + -50.0f, effect->obj.pos.z, sp58 * 0.25f,
                               RAND_FLOAT(10.0f) + 20.0f, sp58 * 0.25f, 20.0f, 1);
            }
            break;
        case 5:
            effect->unk_4C++;
            if (effect->unk_4C > 2) {
                effect->unk_4C = 0;
            }
            if (effect->unk_60.x < 7.5f) {
                effect->unk_60.x += 0.25f;
            }
            effect->unk_60.z += 10.0f;
            effect->vel.x = SIN_DEG(effect->unk_60.z) * (effect->unk_60.x * 10.0f);
            effect->vel.y = COS_DEG(effect->unk_60.z) * (effect->unk_60.x * 10.0f);
            effect->vel.z = gPlayer[0].vel.z + 15.0f;
            if (gPlayer[0].state_1C8 != PLAYERSTATE_1C8_7) {
                func_effect_8007A774(&gPlayer[0], effect, effect->scale2 * 18.0f);
                if ((effect->unk_4C == 0) && ((effect->scale2 >= 9.8f) || (effect->scale2 <= 4.4f))) {
                    AUDIO_PLAY_SFX(0x31033078, effect->sfxSource, 4);
                }
            } else {
                effect->vel.z += 65.0f;
                if (fabsf(gBosses[0].obj.pos.z - effect->obj.pos.z) >= 2000.0f) {
                    Audio_KillSfxBySourceAndId(effect->sfxSource, 0x31033078);
                }
            }
            break;
        case 6:
            sp50 = -1.0f;
            /* fallthrough */
        case 7:
            effect->unk_4C++;
            if (effect->unk_4C > 2) {
                effect->unk_4C = 0;
            }
            effect->unk_60.z += 20.0f;
            effect->vel.x = SIN_DEG(effect->unk_60.z) * sp50 * 50.0f;
            effect->vel.y = COS_DEG(effect->unk_60.z) * sp50 * 50.0f;
            effect->vel.z = gPlayer[0].vel.z + 80.0f;
            if (gPlayer[0].state_1C8 != PLAYERSTATE_1C8_7) {
                func_effect_8007A774(&gPlayer[0], effect, effect->scale2 * 18.0f);
                if ((effect->unk_4C == 0) && ((effect->scale2 >= 9.8f) || (effect->scale2 <= 4.4f))) {
                    AUDIO_PLAY_SFX(0x31033078, effect->sfxSource, 4);
                }
            } else if (fabsf(gBosses[0].obj.pos.z - effect->obj.pos.z) >= 2000.0f) {
                Audio_KillSfxBySourceAndId(effect->sfxSource, 0x31033078);
            }
            break;
    }
}

void Solar_801A0AF0(Effect* effect) {
    Graphics_SetScaleMtx(effect->scale2);
    switch (effect->state) {
        case 0:
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 128, 128, effect->unk_44);
            gSPDisplayList(gMasterDisp++, D_i3_801BF92C[effect->unk_4C]);
            break;
        case 1:
        case 2:
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 128, 128, effect->unk_44);
            gSPDisplayList(gMasterDisp++, D_i3_801BF944[effect->unk_4C]);
            break;
        case 3:
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 128, 128, effect->unk_44);
            gSPDisplayList(gMasterDisp++, D_SO_601C820);
            break;
        case 4:
        case 5:
        case 6:
        case 7:
            RCP_SetupDL(&gMasterDisp, 0x35);
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 128, 128, effect->unk_44);
            gSPDisplayList(gMasterDisp++, D_i3_801BF92C[effect->unk_4C]);
            RCP_SetupDL(&gMasterDisp, 0x40);
            break;
    }
}

void Solar_801A0CEC(Actor* actor, f32 xPos, f32 zPos, f32 zVel, s32 unkB8) {
    Actor_Initialize(actor);
    actor->obj.status = OBJ_ACTIVE;
    actor->obj.id = OBJ_ACTOR_278;
    actor->obj.pos.x = xPos;
    actor->obj.pos.z = zPos;
    actor->unk_046 = 1;
    actor->state = unkB8;
    actor->vel.z = zVel;
    actor->fwork[1] = zVel;
    if (unkB8 == 2) {
        actor->fwork[0] = 18.0f;
    }
    Object_SetInfo(&actor->info, actor->obj.id);
    actor->info.bonus = 0;
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
    s32 sp2C;

    switch (index) {
        case 0:
            if (D_ctx_80177A10[0] != 0) {
                sp2C = 5;
                D_ctx_80177A10[1] = RAND_INT(10.0f) + 128;
            } else {
                sp2C = 4;
                D_ctx_80177A10[0] = RAND_INT(10.0f) + 128;
            }
            break;
        case 1:
        case 4:
            sp2C = 6;
            break;
        case 2:
            sp2C = 4;
            break;
        case 3:
            sp2C = 5;
            break;
    }
    Actor_Initialize(&gActors[sp2C]);
    gActors[sp2C].obj.status = OBJ_ACTIVE;
    gActors[sp2C].obj.id = OBJ_ACTOR_279;
    Object_SetInfo(&gActors[sp2C].info, gActors[sp2C].obj.id);
    gActors[sp2C].state = 0;
    gActors[sp2C].obj.pos.x = xPos;
    gActors[sp2C].obj.pos.z = zPos;
    gActors[sp2C].obj.rot.y = yRot;
    if (index != 4) {
        gActors[sp2C].obj.pos.y = -80.0f * yPos;
    } else {
        gActors[sp2C].timer_0BC = 0;
        gActors[sp2C].timer_0BE = 50;
        gActors[sp2C].unk_04E = 0;
        gActors[sp2C].obj.pos.y = -1.0f * yPos;
        func_edisplay_8005F0E8(gActors[sp2C].sfxSource, &gActors[sp2C].obj.pos);
        AUDIO_PLAY_SFX(0x19035053, gActors[sp2C].sfxSource, 4);
    }
}

void Solar_801A0FD4(Actor* actor, s32 index) {
    if (gTeamShields[3 - index] > 0) {
        Actor_Initialize(actor);
        actor->obj.status = OBJ_ACTIVE;
        actor->obj.id = OBJ_ACTOR_195;
        actor->obj.pos.x = D_i3_801BF95C[index].x + gPlayer[0].pos.x;
        actor->obj.pos.y = D_i3_801BF95C[index].y + gPlayer[0].pos.y;
        actor->obj.pos.z = D_i3_801BF95C[index].z + gPlayer[0].pos.z;
        actor->state = 0;
        actor->iwork[11] = 1;
        actor->vel.z = 0.0f;
        actor->vel.y = 0.0f;
        actor->obj.rot.x = 0.0f;
        actor->obj.rot.y = 180.0f;
        Object_SetInfo(&actor->info, actor->obj.id);
        AUDIO_PLAY_SFX(0x3100000C, actor->sfxSource, 4);
    }
}

void Solar_801A10F4(Player* player) {
    s32 i;
    Vec3f sp50;
    Vec3f sp44;

    if (D_ctx_80177A10[0] != 0) {
        D_ctx_80177A10[0]--;
    }
    if (D_ctx_80177A10[1] != 0) {
        D_ctx_80177A10[1]--;
    }
    switch (player->unk_1D0) {
        case 0:
            gCsFrameCount = 0;
            Rand_SetSeed(1, 29100, 9786);
            player->unk_1D0 = 1;
            player->camEye.x = -2000.0f;
            gCsCamEyeX = -2800.0f;
            player->camEye.y = gCsCamEyeY = 120.0f;
            player->camEye.z = -1800.0f;
            gCsCamEyeZ = -2800.0f;

            player->camAt.x = gCsCamAtX = -1000.0f;
            player->camAt.y = 1400.0f;
            gCsCamAtY = 400.0f;
            player->camAt.z = gCsCamAtZ = -2300.0f;

            D_ctx_80177A48[0] = 0.0045f;

            player->unk_034 = 0.0f;
            player->unk_0D0 = 0.0f;

            gFillScreenAlpha = 255;
            gFillScreenAlphaTarget = 0;
            Solar_801A0DF8(-750.0f, -2600.0f, 300.0f, 2, 1.0f);
            AUDIO_PLAY_SFX(0x3140807E, player->sfxSource, 0);
            break;
        case 1:
            D_ctx_80177CE8 += 30.0f;
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
            if (((gGameFrameCount % 8) == 0)) {
                Solar_8019E8B8(RAND_FLOAT_CENTERED(6000.0f), RAND_FLOAT_CENTERED(5.0f) - 90.0f,
                               RAND_FLOAT(2000.0f) - 6000.0f + D_ctx_80177D20, RAND_FLOAT(20.0f) + 20.0f);
            }
            if (gCsFrameCount == 380) {
                for (i = 0; i < 100; i++) {
                    Object_Kill(&gEffects[i].obj, gEffects[i].sfxSource);
                }
                Solar_801A0DF8(400.0f, -2800.0f, 340.0f, 1, 1.0f);
            }
            if (gCsFrameCount == 410) {
                player->unk_1D0++;
                player->camEye.x = 200.0f;
                gCsCamEyeX = 800.0f;
                player->camEye.y = 140.0f;
                gCsCamEyeY = player->pos.y + 200.0f;
                player->camEye.z = gCsCamEyeZ = 400.0f;

                player->camAt.x = 400.0f;
                gCsCamAtX = 200.0f;
                player->camAt.y = 140.0f;
                gCsCamAtY = 1200.0f;
                player->camAt.z = -500.0f;

                player->pos.y = 1200.0f;
                player->pos.z = -2500.0f;
                Solar_801A0FD4(&gActors[0], 0);
                Solar_801A0FD4(&gActors[1], 1);
                Solar_801A0FD4(&gActors[2], 2);
                gCsCamAtZ = -3000.0f;
                gCsCamEyeZ = -3400.0f;
                Audio_KillSfxBySourceAndId(player->sfxSource, 0x3140807E);
                AUDIO_PLAY_BGM(SEQ_ID_INTRO_51);
                func_display_80057814(player);
                func_8001C8B8(gPlayerNum);
                D_ctx_80177A48[0] = 0.01f;
            }
            break;
        case 2:
            D_ctx_80177CE8 += 60.0f;
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
            if (player->camEye.z <= -2465.0f) {
                player->unk_1D0++;
                gCsCamEyeY = player->pos.y + 180.0f;
                gCsCamAtX = 0.0f;
                gCsCamEyeX = 0.0f;
                gCsCamAtZ = -2800.0f;
                D_ctx_80177A48[0] = 0.06f;
            }
            break;
        case 3:
            D_ctx_80177CE8 += 60.0f;
            if (((gGameFrameCount % 4) == 0)) {
                Solar_8019E8B8(RAND_FLOAT_CENTERED(6000.0f), -400.0f - ((player->camEye.y - 1380.0f) * 0.3f),
                               RAND_FLOAT_CENTERED(2000.0f) + 500.0f + D_ctx_80177D20, RAND_FLOAT(20.0f) + 20.0f);
            }
            if (gCsFrameCount == 615) {
                func_play_800A6028(player->sfxSource, 0x09000002);
                gActors[0].fwork[29] = gActors[1].fwork[29] = gActors[2].fwork[29] = 5.0f;
                gActors[0].state = 3;
                gActors[1].state = 2;
                gActors[2].state = 1;
                player->timer_1F8 = 3;
                player->unk_190 = 5.0f;
                player->unk_1D0++;
                player->unk_194 = 5.0f;
            }
            break;
        case 4:
            gCsCamEyeX = player->pos.x;
            gCsCamEyeY = player->pos.y;
            gCsCamEyeZ = player->unk_138 + 1000.0f;
            gCsCamAtX = player->pos.x;
            gCsCamAtY = player->pos.y;
            gCsCamAtZ = player->unk_138 + 1100.0f;
            D_ctx_80177A48[0] = 0.03f;
            D_ctx_801779A8[gMainController] = 60.0f;
            player->unk_190 = 2.0f;
            if (player->timer_1F8 == 0) {
                gFillScreenAlphaTarget = 255;
                gFillScreenAlphaStep = 24;
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
            }
            if (gFillScreenAlpha == 255) {
                AUDIO_PLAY_BGM(SEQ_ID_SOLAR | SEQ_FLAG);
                player->pos.z = 0.0f;
                player->unk_0D0 = D_play_80161A54;
                func_play_800A6148();
                gLevelStatusScreenTimer = 50;
                player->state_1C8 = PLAYERSTATE_1C8_3;
                player->unk_1D0 = 0;
                player->pos.y = 350.0f;

                player->camEye.x = player->pos.x;
                player->camEye.y = 50.0f + player->pos.y * player->unk_148;
                player->camEye.z = 30.0f;

                player->camAt.x = player->pos.x;
                player->camAt.y = 20.0f + player->pos.y * player->unk_148;
                player->camAt.z = player->unk_138;

                D_ctx_80177950 = 1.0f;
                func_8001D1C8(0xFF, 3);
                AUDIO_PLAY_SFX(0x4100C023, gDefaultSfxSource, 4);
                D_ctx_80178488 = 1;
                gFillScreenAlphaTarget = 0;
                player->timer_1F8 = 15;
                gPlayer[0].shields = 255;
            }
            break;
        case 10:
            D_ctx_80177CE8 += 60.0f;
            break;
    }
    Math_SmoothStepToF(&player->camEye.x, gCsCamEyeX, D_ctx_80177A48[0], 20000.0f, 0);
    Math_SmoothStepToF(&player->camEye.y, gCsCamEyeY, D_ctx_80177A48[0], 20000.0f, 0);
    Math_SmoothStepToF(&player->camEye.z, gCsCamEyeZ, D_ctx_80177A48[0], 20000.0f, 0);
    Math_SmoothStepToF(&player->camAt.x, gCsCamAtX, D_ctx_80177A48[0], 20000.0f, 0);
    Math_SmoothStepToF(&player->camAt.y, gCsCamAtY, D_ctx_80177A48[0], 20000.0f, 0);
    Math_SmoothStepToF(&player->camAt.z, gCsCamAtZ, D_ctx_80177A48[0], 20000.0f, 0);
    Matrix_RotateY(gCalcMatrix, (player->unk_0E8 + 180.0f) * M_DTOR, 0);
    Matrix_RotateX(gCalcMatrix, -(player->unk_0E4 * M_DTOR), 1);
    sp50.x = 0.f;
    sp50.y = 0.0f;
    sp50.z = player->unk_0D0;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp50, &sp44);
    player->vel.x = sp44.x;
    player->vel.z = sp44.z;
    player->vel.y = sp44.y;
    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;
    player->pos.z += player->vel.z;
    player->unk_138 = player->pos.z + player->unk_08C;
}

void Solar_801A1CD8(Actor* actor, f32 xPos, f32 yPos, f32 zPos, f32 xRot, f32 yRot, f32 zRot, f32 xVel, f32 yVel,
                    f32 zVel, s32 unk46) {
    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_189;
    actor->state = 40;
    actor->unk_046 = unk46;
    actor->unk_04A = 3;
    actor->obj.pos.x = xPos;
    actor->obj.pos.y = yPos;
    actor->obj.pos.z = zPos;
    actor->obj.rot.x = xRot;
    actor->obj.rot.y = yRot;
    actor->obj.rot.z = zRot;
    actor->vel.x = xVel;
    actor->vel.y = yVel;
    actor->vel.z = zVel;
    actor->iwork[0] = 3;

    actor->fwork[0] = RAND_FLOAT_CENTERED(25.0f);
    actor->fwork[1] = RAND_FLOAT_CENTERED(25.0f);
    actor->fwork[2] = RAND_FLOAT_CENTERED(25.0f);
    actor->fwork[5] = 2000.0f;
    actor->gravity = 3.5f;
    actor->scale = 5.5f;
    Object_SetInfo(&actor->info, actor->obj.id);
}

void Solar_801A1E14(f32 xPos, f32 yPos, f32 zPos, f32 xRot, f32 yRot, f32 zRot, f32 xVel, f32 yVel, f32 zVel,
                    s32 unk46) {
    s32 i;

    for (i = 59; i >= 0; i--) {
        if (gActors[i].obj.status == OBJ_FREE) {
            Solar_801A1CD8(&gActors[i], xPos, yPos, zPos, xRot, yRot, zRot, xVel, yVel, zVel, unk46);
            break;
        }
    }
}

void Solar_801A1EB0(Boss* bossSO, f32 xPos, f32 xOffset, f32 yPos, f32 zPos) {
    Solar_8019E9F4(xPos + xOffset, yPos, zPos, 20.0f, RAND_FLOAT(10.0f) + 20.0f, 0.0f, 20.0f, 1);
    Solar_8019E9F4(xPos - xOffset, yPos, zPos, -20.0f, RAND_FLOAT(10.0f) + 20.0f, 0.0f, 20.0f, 1);
}

void Solar_801A1F80(Boss* bossSO) {
    if (gBossActive != 0) {
        bossSO->unk_3F8 = 5.5f;
    }
    if (bossSO->health == 0) {
        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 20);
        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 20);
        gBossActive = 1;
        gBossFrameCount = 0;
        bossSO->health = 600;

        bossSO->unk_3F8 = 0.1f;
        bossSO->fwork[SO_FWK_0] = 1.0f;
        bossSO->swork[SO_SWK_2] = bossSO->swork[SO_SWK_3] = 400;

        bossSO->obj.pos.y = -3000.0f;

        Solar_801A0CEC(&gActors[10], bossSO->obj.pos.x, bossSO->obj.pos.z + 2000.0f, 20.0f, 1);
        D_ctx_801779A8[gMainController] = 10.0f;
        gCameraShake = 120;
        bossSO->fwork[SO_FWK_3] = 2400.0f;
        bossSO->info.hitbox = LOAD_ASSET(D_SO_60231A4);
        bossSO->unk_04C = 0;
        bossSO->swork[SO_SWK_1] = 0;
        bossSO->info.hitbox[8] = bossSO->info.hitbox[12] = bossSO->info.hitbox[14] = bossSO->info.hitbox[18] =
            bossSO->info.hitbox[20] = bossSO->info.hitbox[24] = bossSO->info.hitbox[26] = bossSO->info.hitbox[30] =
                bossSO->info.hitbox[32] = bossSO->info.hitbox[36] = bossSO->info.hitbox[38] = bossSO->info.hitbox[42] =
                    220.0f;
        bossSO->info.hitbox[10] = bossSO->info.hitbox[28] = 467.5f;
        bossSO->info.hitbox[16] = bossSO->info.hitbox[34] = 247.5f;
        bossSO->info.hitbox[22] = bossSO->info.hitbox[40] = 715.0f;

        D_i3_801C2740[0] = 255;
        D_i3_801C2740[1] = 255;
        D_i3_801C2768[3] = D_i3_801C2768[2] = D_i3_801C2768[4] = D_i3_801C2768[5] = D_i3_801C2768[6] =
            D_i3_801C2768[7] = D_i3_801C2768[8] = D_i3_801C2768[9] = D_i3_801C2768[10] = D_i3_801C2768[11] =
                D_i3_801C2768[12] = D_i3_801C2768[13] = 0.0f;
    }
    gActors[10].obj.pos.z = bossSO->obj.pos.z + 2000.0f;
    Math_SmoothStepToF(&bossSO->obj.pos.y, 180.0f, 0.1f, 30.0f, 0.1f);
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
        AUDIO_PLAY_BGM(SEQ_ID_SO_BOSS | SEQ_FLAG);
    }
    if (gBossFrameCount <= 60) {
        Math_SmoothStepToF(&D_ctx_801779A8[gMainController], 120.0f, 1.0f, 3.5f, 0.0f);
    }
    if (gBossFrameCount == 60) {
        gActors[10].unk_0D0 = 3;
        AUDIO_PLAY_SFX(0x19036053, bossSO->sfxSource, 4);
    }
    if (bossSO->timer_050 == 100) {
        bossSO->unk_04C = 0;
        bossSO->swork[SO_SWK_1] = 1;
    }
    if (gBossFrameCount == 150) {
        Solar_801A239C(bossSO);
        bossSO->fwork[SO_FWK_0] = 0.01f;
    }
    if ((gBossFrameCount == 100) && (gTeamShields[TEAM_ID_PEPPY] != 0)) {
        Radio_PlayMessage(gMsg_ID_10300, RCID_PEPPY);
    }
}

void Solar_801A239C(Boss* bossSO) {
    bossSO->swork[SO_SWK_0] = 1;
    if ((bossSO->swork[SO_SWK_2] != 0) || (bossSO->swork[SO_SWK_3] != 0)) {
        if (bossSO->swork[SO_SWK_3] != 0) {
            bossSO->swork[SO_SWK_1] = 3;
        } else {
            bossSO->swork[SO_SWK_1] = 4;
        }
    } else {
        bossSO->swork[SO_SWK_1] = 7;
    }
    bossSO->unk_04C = 0;
}

void Solar_801A23F4(Boss* bossSO) {
    s32 i;
    Vec3f sp58;
    Vec3f sp4C;
    Vec3f sp40;
    Vec3f sp34;

    switch (bossSO->swork[SO_SWK_1]) {
        case 3:
            if ((bossSO->unk_04C == 119) || (bossSO->swork[SO_SWK_3] == 0)) {
                bossSO->unk_04C = 0;
                if (bossSO->swork[SO_SWK_2] != 0) {
                    if (Rand_ZeroOne() >= 0.5f) {
                        bossSO->swork[SO_SWK_1] = 4;
                    } else {
                        bossSO->swork[SO_SWK_1] = 2;
                        bossSO->state = 0;
                        bossSO->unk_078.y = 0.0f;
                    }
                } else if (bossSO->swork[SO_SWK_3] == 0) {
                    bossSO->swork[SO_SWK_1] = 7;
                } else {
                    bossSO->swork[SO_SWK_1] = 5;
                }
            }
            if (bossSO->unk_04C >= 28) {
                bossSO->info.hitbox[38] = 715.0f;
                bossSO->info.hitbox[40] = 440.0f;
                bossSO->info.hitbox[42] = 110.0f;
            }
            if (bossSO->unk_04C == 29) {
                func_edisplay_8005F0E8(bossSO->sfxSource, &bossSO->obj.pos);
                AUDIO_PLAY_SFX(0x19035053, bossSO->sfxSource, 4);
            }
            if (bossSO->unk_04C == 80) {
                AUDIO_PLAY_SFX(0x29432077, bossSO->sfxSource, 4);
            }
            if (bossSO->unk_04C >= 94) {
                bossSO->info.hitbox[38] = 220.0f;
                bossSO->info.hitbox[40] = 715.0f;
                bossSO->info.hitbox[42] = 220.0f;
            }
            break;
        case 4:
            if ((bossSO->unk_04C == 99) || (bossSO->swork[SO_SWK_2] == 0)) {
                bossSO->unk_04C = 0;
                if ((bossSO->swork[SO_SWK_3] != 0) || (bossSO->swork[SO_SWK_2] != 0)) {
                    bossSO->swork[SO_SWK_1] = 5;
                } else {
                    bossSO->swork[SO_SWK_1] = 7;
                }
            }
            if (bossSO->unk_04C > 20) {
                bossSO->info.hitbox[20] = 715.0f;
                bossSO->info.hitbox[22] = 110.0f;
                bossSO->info.hitbox[24] = 275.0f;
            }
            if (bossSO->unk_04C == 10) {
                func_edisplay_8005F0E8(bossSO->sfxSource, &bossSO->obj.pos);
                AUDIO_PLAY_SFX(0x19035053, bossSO->sfxSource, 4);
            }
            if (bossSO->unk_04C == 50) {
                AUDIO_PLAY_SFX(0x29432077, bossSO->sfxSource, 4);
            }
            if (bossSO->unk_04C >= 85) {
                bossSO->info.hitbox[20] = 220.0f;
                bossSO->info.hitbox[22] = 715.0f;
                bossSO->info.hitbox[24] = 220.0f;
            }
            break;
        case 5:
            bossSO->fwork[SO_FWK_3] = 2600.0f;
            Math_SmoothStepToAngle(&bossSO->obj.rot.y, 0.0f, 1.0f, 1.5f, 1.0f);
            if (bossSO->unk_04C == 65) {
                Matrix_RotateX(gCalcMatrix, D_i3_801C2768[0] * M_DTOR, 0);
                Matrix_RotateY(gCalcMatrix, D_i3_801C2768[1] * M_DTOR, 1);
                sp40.x = 0.0f;
                sp40.y = -200.0f;
                sp40.z = 1100.0f;
                Matrix_MultVec3f(gCalcMatrix, &sp40, &sp34);
                for (i = 0; i < 4; i++) {
                    sp58.x = D_i3_801BF8F0[i].x + RAND_FLOAT_CENTERED(2.0f);
                    sp58.y = RAND_FLOAT_CENTERED(2.0f);
                    sp58.z = RAND_FLOAT(10.0f) + 2.5f;
                    Matrix_MultVec3f(gCalcMatrix, &sp58, &sp4C);
                    Solar_8019F038(bossSO->fwork[SO_FWK_4] + sp34.x, bossSO->fwork[SO_FWK_5] + sp34.y,
                                   bossSO->fwork[SO_FWK_6] + sp34.z, sp4C.x, sp4C.y, sp4C.z);
                }
            }
            if (bossSO->unk_04C == 99) {
                if ((bossSO->swork[SO_SWK_2] != 0) || (bossSO->swork[SO_SWK_3] != 0)) {
                    Solar_801A2C3C(bossSO);
                } else {
                    Solar_801A4EC0(bossSO);
                }
            }
            break;
        case 7:
            if (bossSO->unk_04C < 50) {
                if (bossSO->fwork[SO_FWK_31] < 22.0f) {
                    bossSO->fwork[SO_FWK_31] += 0.5f;
                }
                bossSO->obj.rot.y += bossSO->fwork[SO_FWK_31];
            }
            if ((bossSO->unk_04C >= 50) && (bossSO->unk_04C <= 100)) {
                if (bossSO->fwork[SO_FWK_31] > 0.0f) {
                    bossSO->fwork[SO_FWK_31] -= 0.5f;
                }
                bossSO->obj.rot.y += bossSO->fwork[SO_FWK_31];
            }
            if (bossSO->obj.rot.y >= 360.0f) {
                bossSO->obj.rot.y -= 360.0f;
                AUDIO_PLAY_SFX(0x39033079, bossSO->sfxSource, 4);
            }
            if (bossSO->unk_04C == 1) {
                AUDIO_PLAY_SFX(0x39033079, bossSO->sfxSource, 4);
            }
            if (bossSO->unk_04C >= 100) {
                Math_SmoothStepToAngle(&bossSO->obj.rot.y, 0.0f, 1.0f, 2.0f, 1.0f);
                bossSO->fwork[SO_FWK_31] = 0.0f;
            }
            if (bossSO->unk_04C == 120) {
                bossSO->swork[SO_SWK_1] = 5;
                bossSO->unk_04C = 0;
                bossSO->fwork[SO_FWK_0] = 0.1f;
            }
            break;
        case 2:
            if (((bossSO->unk_04C == 89) && (bossSO->state == 2)) || (bossSO->swork[SO_SWK_2] == 0)) {
                bossSO->unk_04C = 0;
                if ((bossSO->swork[SO_SWK_3] != 0) || (bossSO->swork[SO_SWK_2] != 0)) {
                    bossSO->swork[SO_SWK_1] = 5;
                } else {
                    bossSO->swork[SO_SWK_1] = 7;
                }
            }
            if (bossSO->unk_04C == 80) {
                bossSO->unk_078.y += 15.0f;
                bossSO->state++;
                if (bossSO->unk_078.y >= 30.0f) {
                    bossSO->unk_078.y = 0.0f;
                }
            }
            Math_SmoothStepToAngle(&bossSO->obj.rot.y, bossSO->unk_078.y, 1.0f, 1.5f, 1.0f);
            if (bossSO->unk_04C >= 19) {
                bossSO->info.hitbox[20] = 715.0f;
                bossSO->info.hitbox[22] = 440.0f;
                bossSO->info.hitbox[24] = 110.0f;
            }
            if (bossSO->unk_04C == 5) {
                func_edisplay_8005F0E8(bossSO->sfxSource, &bossSO->obj.pos);
                AUDIO_PLAY_SFX(0x19035053, bossSO->sfxSource, 4);
            }
            if (bossSO->unk_04C == 20) {
                AUDIO_PLAY_SFX(0x29432077, bossSO->sfxSource, 4);
            }
            if (bossSO->unk_04C > 36) {
                bossSO->info.hitbox[20] = 220.0f;
                bossSO->info.hitbox[22] = 715.0f;
                bossSO->info.hitbox[24] = 220.0f;
            }
            break;
    }
}

void Solar_801A2C3C(Boss* bossSO) {
    bossSO->swork[SO_SWK_0] = 2;
    bossSO->swork[SO_SWK_1] = 0;
    bossSO->fwork[SO_FWK_0] = 0.05f;
    bossSO->unk_04C = Animation_GetFrameCount(&D_SO_601388C) - 2;
    bossSO->state = 0;
    bossSO->swork[SO_SWK_11] = 15;
}

void Solar_801A2C98(Boss* bossSO) {
    s32 i;

    if (bossSO->swork[SO_SWK_11] != 0) {
        bossSO->swork[SO_SWK_11]--;
    }
    if (bossSO->state == 0) {
        if (bossSO->swork[SO_SWK_11] == 0) {
            bossSO->unk_04C -= 2;
            Math_SmoothStepToF(&bossSO->obj.pos.y, -1000.0f, 0.1f, 10.0f, 0.1f);
            Math_SmoothStepToAngle(&bossSO->obj.rot.y, 181.0f, 1.0f, 3.0f, 1.0f);
            if (bossSO->unk_04C == 50) {
                Solar_801A0CEC(&gActors[10], bossSO->obj.pos.x, bossSO->obj.pos.z + 1000.0f, 20.0f, 1);
                D_80137E84[gMainController] = 1;
                D_Timer_80177BD0[gMainController] = 70;
            }
            if (bossSO->unk_04C == 60) {
                for (i = 0; i < 4; i++) {
                    Solar_8019F038(bossSO->obj.pos.x + 100.0f, 100.0f, bossSO->obj.pos.z + 1100.0f,
                                   D_i3_801BF8F0[i].x + RAND_FLOAT_CENTERED(2.0f),
                                   D_i3_801BF8F0[i].y + 10.0f + RAND_FLOAT_CENTERED(2.0f), RAND_FLOAT(-10.0f) - 10.0f);
                    Solar_8019F038(bossSO->obj.pos.x - 100.0f, 100.0f, bossSO->obj.pos.z + 1100.0f,
                                   D_i3_801BF8F0[i].x + RAND_FLOAT_CENTERED(2.0f),
                                   D_i3_801BF8F0[i].y + 10.0f + RAND_FLOAT_CENTERED(2.0f), RAND_FLOAT(-10.0f) - 10.0f);
                }
            }
            if (bossSO->unk_04C == 20) {
                gActors[10].unk_0D0 = 3;
                AUDIO_PLAY_SFX(0x19036054, bossSO->sfxSource, 4);
            }
            if (bossSO->unk_04C == 0) {
                bossSO->state++;
                bossSO->swork[SO_SWK_11] = 100;
                bossSO->obj.pos.y = -500.0f;
                bossSO->fwork[SO_FWK_3] = 4800.0f;
                bossSO->obj.pos.z = gPlayer[0].unk_138 - bossSO->fwork[SO_FWK_3];
                bossSO->obj.rot.y = -bossSO->obj.rot.y;
            }
        } else {
            bossSO->unk_04C = Animation_GetFrameCount(&D_SO_601388C) - 2;
        }
    } else {
        Math_SmoothStepToAngle(&bossSO->obj.rot.y, 0.0f, 1.0f, 1.5f, 1.0f);
        if (bossSO->swork[SO_SWK_11] == 80) {
            Solar_801A0CEC(&gActors[9], bossSO->obj.pos.x, bossSO->obj.pos.z + 1000.0f, 20.0f, 1);
        }
        if (bossSO->swork[SO_SWK_11] == 0) {
            bossSO->swork[SO_SWK_11] = 220;
        }
        if (bossSO->swork[SO_SWK_11] == 210) {
            bossSO->unk_04C = 0;
            bossSO->swork[SO_SWK_1] = 1;
            bossSO->fwork[SO_FWK_0] = 0.05f;
        }
        if (bossSO->swork[SO_SWK_11] >= 100) {
            Math_SmoothStepToF(&bossSO->obj.pos.y, 180.0f, 0.1f, 10.0f, 0.1f);
        }
        if (bossSO->swork[SO_SWK_11] == 150) {
            Solar_801A3468(bossSO);
        }
        if (bossSO->swork[SO_SWK_11] == 50) {
            gActors[9].unk_0D0 = 3;
            AUDIO_PLAY_SFX(0x19036053, bossSO->sfxSource, 4);
        }
    }
}

void Solar_801A30CC(Boss* bossSO) {
    bossSO->swork[SO_SWK_0] = 3;
    bossSO->swork[SO_SWK_1] = 0;
    bossSO->fwork[SO_FWK_0] = 0.1f;
    bossSO->unk_04C = Animation_GetFrameCount(&D_SO_601388C) - 2;
    bossSO->state = 0;
    bossSO->swork[SO_SWK_11] = 15;
}

void Solar_801A3128(Boss* bossSO) {
    if (bossSO->swork[SO_SWK_11] != 0) {
        bossSO->swork[SO_SWK_11]--;
    }
    if (bossSO->state == 0) {
        if (bossSO->swork[SO_SWK_11] == 0) {
            bossSO->unk_04C -= 2;
            Math_SmoothStepToF(&bossSO->obj.pos.y, -1000.0f, 0.1f, 10.0f, 0.1f);
            if (bossSO->unk_04C == 50) {
                Solar_801A0CEC(&gActors[10], bossSO->obj.pos.x, bossSO->obj.pos.z + 2000.0f, 10.0f, 1);
            }
            if (bossSO->unk_04C == 40) {
                gActors[10].unk_0D0 = 3;
                AUDIO_PLAY_SFX(0x19036054, bossSO->sfxSource, 4);
            }
            if (bossSO->unk_04C == 0) {
                bossSO->state++;
                bossSO->swork[SO_SWK_11] = 100;
                bossSO->obj.pos.y = -500.0f;
                bossSO->fwork[SO_FWK_3] = 2400.0f;
                bossSO->obj.pos.z = gPlayer[0].unk_138 - 2100.0f;
            }
        } else {
            bossSO->unk_04C = Animation_GetFrameCount(&D_SO_601388C) - 2;
        }
    } else {
        if (bossSO->swork[SO_SWK_11] == 80) {
            Solar_801A0CEC(&gActors[9], bossSO->obj.pos.x, bossSO->obj.pos.z + 850.0f, 20.0f, 1);
            D_80137E84[gMainController] = 1;
            D_Timer_80177BD0[gMainController] = 70;
            D_i3_801C2740[2]++;
            if ((D_i3_801C2740[2] % 2) != 0) {
                if (D_i3_801C2740[2] & 2) {
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
        if (bossSO->swork[SO_SWK_11] == 0) {
            bossSO->swork[SO_SWK_11] = 220;
        }
        if (bossSO->swork[SO_SWK_11] == 210) {
            bossSO->unk_04C = 0;
            bossSO->swork[SO_SWK_1] = 1;
        }
        if (bossSO->swork[SO_SWK_11] >= 100) {
            Math_SmoothStepToF(&bossSO->obj.pos.y, 180.0f, 0.1f, 20.0f, 0.1f);
        }
        if (bossSO->swork[SO_SWK_11] == 150) {
            Solar_801A239C(bossSO);
            bossSO->fwork[SO_FWK_0] = 0.01f;
            if ((Rand_ZeroOne() >= 0.4f) && (gTeamShields[TEAM_ID_PEPPY] > 0) && (bossSO->swork[SO_SWK_2] != 0) &&
                (bossSO->swork[SO_SWK_3] != 0)) {
                Radio_PlayMessage(gMsg_ID_10320, RCID_PEPPY);
            }
        }
        if (bossSO->swork[SO_SWK_11] == 50) {
            gActors[9].unk_0D0 = 3;
            AUDIO_PLAY_SFX(0x19036053, bossSO->sfxSource, 4);
        }
    }
}

void Solar_801A3468(Boss* bossSO) {
    bossSO->swork[SO_SWK_0] = 4;
    bossSO->unk_048 = 0;
    if ((bossSO->swork[SO_SWK_2] != 0) || (bossSO->swork[SO_SWK_3] != 0)) {
        if (bossSO->swork[SO_SWK_3] != 0) {
            bossSO->swork[SO_SWK_1] = 3;
        } else {
            bossSO->swork[SO_SWK_1] = 4;
        }
    } else {
        if (Rand_ZeroOne() >= 0.5f) {
            bossSO->unk_048 = 1;
            bossSO->swork[SO_SWK_1] = 5;
        } else {
            bossSO->timer_050 = 0;
            bossSO->swork[SO_SWK_1] = 8;
        }
    }
    bossSO->unk_04C = 0;
    bossSO->fwork[SO_FWK_0] = 0.01f;
}

void Solar_801A3510(Boss* bossSO) {
    s32 i;

    switch (bossSO->swork[SO_SWK_1]) {
        case 3:
            if ((bossSO->unk_04C == 119) || (bossSO->swork[SO_SWK_3] == 0)) {
                bossSO->unk_04C = 0;
                if (bossSO->swork[SO_SWK_2] != 0) {
                    bossSO->swork[SO_SWK_1] = 4;
                } else {
                    bossSO->swork[SO_SWK_1] = 5;
                }
            }
            if (bossSO->unk_04C == 29) {
                func_edisplay_8005F0E8(bossSO->sfxSource, &bossSO->obj.pos);
                AUDIO_PLAY_SFX(0x19035053, bossSO->sfxSource, 4);
            }
            if (bossSO->unk_04C == 80) {
                AUDIO_PLAY_SFX(0x29432077, bossSO->sfxSource, 4);
            }
            if (bossSO->unk_04C == 94) {
                Solar_801A0DF8(bossSO->fwork[SO_FWK_13], bossSO->fwork[SO_FWK_15], RAND_FLOAT_CENTERED(60.0f), 4, 2.0f);
                bossSO->timer_050 = 90;
            }
            break;
        case 4:
            if ((bossSO->unk_04C == 99) || (bossSO->swork[SO_SWK_2] == 0)) {
                bossSO->unk_04C = 0;
                bossSO->swork[SO_SWK_1] = 5;
            }
            Math_SmoothStepToAngle(&bossSO->obj.rot.x, 20.0f, 0.1f, 10.0f, 0.1f);
            if (bossSO->unk_04C == 10) {
                func_edisplay_8005F0E8(bossSO->sfxSource, &bossSO->obj.pos);
                AUDIO_PLAY_SFX(0x19035053, bossSO->sfxSource, 4);
            }
            if (bossSO->unk_04C == 50) {
                AUDIO_PLAY_SFX(0x29432077, bossSO->sfxSource, 4);
            }
            if (bossSO->unk_04C == 60) {
                Solar_801A0D90(bossSO->obj.pos.x, bossSO->obj.pos.z + 1600.0f, 80.0f, 2);
                D_80137E84[gMainController] = 1;
                D_Timer_80177BD0[gMainController] = 100;
            }
            break;
        case 5:
            Math_SmoothStepToAngle(&bossSO->obj.rot.x, 0.0f, 0.1f, 10.0f, 0.1f);
            if (bossSO->unk_04C == 65) {
                for (i = 0; i < 4; i++) {
                    Solar_8019F194(bossSO->obj.pos.x, bossSO->obj.pos.y + 300.0f, bossSO->obj.pos.z + 1000.0f,
                                   D_i3_801BF8F0[i].x + RAND_FLOAT_CENTERED(0.25f),
                                   D_i3_801BF8F0[i].y + RAND_FLOAT_CENTERED(0.25f), RAND_FLOAT(10.0f) + 100.0f);
                }
            }
            if ((bossSO->unk_048 != 0) && (bossSO->unk_04C == 68)) {
                bossSO->swork[SO_SWK_1] = 9;
                bossSO->fwork[SO_FWK_0] = 0.01f;
                bossSO->unk_04C = 20;
            }
            if (bossSO->unk_04C == 99) {
                Solar_801A30CC(bossSO);
            }
            break;
        case 8:
            if (bossSO->unk_04C == 65) {
                AUDIO_PLAY_SFX(0x31033078, bossSO->sfxSource, 4);
                bossSO->timer_050 = 30;
            }
            if (bossSO->timer_050 != 0) {
                bossSO->unk_04C = 65;
            }
            if ((bossSO->unk_04C == 65) && ((gGameFrameCount % 2) == 0)) {
                Solar_8019FFC0(bossSO, bossSO->fwork[SO_FWK_4], bossSO->fwork[SO_FWK_5] - 100.0f,
                               bossSO->fwork[SO_FWK_6] + 600.0f, (bossSO->timer_050 * 0.2f) + 4.0f, 0);
                Solar_801A1EB0(bossSO, bossSO->fwork[SO_FWK_4], 25.0f, bossSO->fwork[SO_FWK_5] - 100.0f,
                               bossSO->fwork[SO_FWK_6] + 300.0f);
            }
            if (bossSO->unk_04C == 75) {
                Audio_KillSfxBySourceAndId(bossSO->sfxSource, 0x31033078);
            }
            if (bossSO->unk_04C == 99) {
                bossSO->swork[SO_SWK_1] = 5;
                bossSO->unk_04C = 0;
            }
            break;
        case 9:
            bossSO->unk_04C++;
            if (bossSO->unk_04C == 66) {
                AUDIO_PLAY_SFX(0x31033078, bossSO->sfxSource, 4);
                bossSO->timer_050 = 30;
            }
            if (bossSO->timer_050 != 0) {
                bossSO->unk_04C = 66;
            }
            if ((bossSO->unk_04C == 66) && ((gGameFrameCount % 2) == 0)) {
                Solar_8019FFC0(bossSO, bossSO->fwork[SO_FWK_4] + 125.0f, bossSO->fwork[SO_FWK_5] - 100.0f,
                               bossSO->fwork[SO_FWK_6] + 600.0f, (bossSO->timer_050 * 0.2f) + 4.0f, 1);
                Solar_8019FFC0(bossSO, bossSO->fwork[SO_FWK_4] - 125.0f, bossSO->fwork[SO_FWK_5] - 100.0f,
                               bossSO->fwork[SO_FWK_6] + 600.0f, (bossSO->timer_050 * 0.2f) + 4.0f, 2);
                Solar_801A1EB0(bossSO, bossSO->fwork[SO_FWK_4], 25.0f, bossSO->fwork[SO_FWK_5] - 100.0f,
                               bossSO->fwork[SO_FWK_6] + 300.0f);
            }
            if (bossSO->unk_04C == 76) {
                Audio_KillSfxBySourceAndId(bossSO->sfxSource, 0x31033078);
            }
            if (bossSO->unk_04C >= 99) {
                Solar_801A30CC(bossSO);
            }
            break;
    }
    if (bossSO->timer_050 == 0) {
        Object_Kill(&gActors[6].obj, gActors[6].sfxSource);
    } else {
        Math_SmoothStepToF(&gActors[6].obj.pos.x, gPlayer[0].pos.x, 0.1f, 10.0f, 0.1f);
    }
}

void Solar_801A3C4C(Boss* bossSO) {
    s32 i;

    if ((bossSO->swork[SO_SWK_2] == 0) && (bossSO->swork[SO_SWK_3] == 0) &&
        ((bossSO->dmgPart == 8) || (bossSO->dmgPart == -1))) {
        bossSO->health -= bossSO->damage;
        if (bossSO->health < 0) {
            bossSO->health = 0;
        }

        bossSO->swork[SO_SWK_10] = 20;
        if (bossSO->health > 0.0f) {
            AUDIO_PLAY_SFX(0x29433074, bossSO->sfxSource, 4);
        }
        if (bossSO) {}
    }
    bossSO->timer_058 = 20;
    if ((bossSO->dmgPart >= 1) && (bossSO->dmgPart <= 3) && (bossSO->swork[SO_SWK_2] != 0)) {
        AUDIO_PLAY_SFX(0x29433074, bossSO->sfxSource, 4);
        bossSO->swork[SO_SWK_2] -= bossSO->damage;
        if (bossSO->swork[SO_SWK_2] < 0) {
            bossSO->swork[SO_SWK_2] = 0;
        }
        if (bossSO->swork[SO_SWK_2] == 0) {
            for (i = 0; i < 6; i++) {
                bossSO->info.hitbox[7 + i] = bossSO->info.hitbox[13 + i] = bossSO->info.hitbox[19 + i] = 0.0f;
            }
            bossSO->swork[SO_SWK_2] = -1;
            Solar_801A48B8(bossSO);
        } else {
            bossSO->swork[SO_SWK_8] = 20;
        }
    }
    if ((bossSO->dmgPart >= 4) && (bossSO->dmgPart <= 6) && (bossSO->swork[SO_SWK_3] != 0)) {
        AUDIO_PLAY_SFX(0x29433074, bossSO->sfxSource, 4);
        bossSO->swork[SO_SWK_3] -= bossSO->damage;
        if (bossSO->swork[SO_SWK_3] < 0) {
            bossSO->swork[SO_SWK_3] = 0;
        }
        if (bossSO->swork[SO_SWK_3] == 0) {
            for (i = 0; i < 6; i++) {
                bossSO->info.hitbox[25 + i] = bossSO->info.hitbox[31 + i] = bossSO->info.hitbox[37 + i] = 0.0f;
            }
            bossSO->swork[SO_SWK_3] = -1;
            Solar_801A48B8(bossSO);
        } else {
            bossSO->swork[SO_SWK_9] = 20;
        }
    }
    if (bossSO->health <= 0) {
        bossSO->unk_04C = 21;
        bossSO->state = 0;
        bossSO->swork[SO_SWK_1] = 1;
        bossSO->fwork[SO_FWK_0] = 0.01f;
        bossSO->info.hitbox = LOAD_ASSET(gHitboxNone);
        bossSO->timer_058 = 20000;
        D_ctx_8017796C = -1;
        gFillScreenRed = gFillScreenGreen = gFillScreenBlue = gFillScreenAlpha = 255;
        gFillScreenAlphaTarget = 0;
        gFillScreenAlphaStep = 255;
        gCsFrameCount = 0;
        D_80137E84[gMainController] = 1;
        D_Timer_80177BD0[gMainController] = 10;
        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 1);
        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 1);
        Audio_KillSfxById(0x4100C023);
        AUDIO_PLAY_SFX(0x2940D09A, bossSO->sfxSource, 4);
        if (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_3) {
            gPlayer[0].state_1C8 = PLAYERSTATE_1C8_7;
            gPlayer[0].timer_1F8 = 0;
            gPlayer[0].unk_1D0 = gPlayer[0].timer_1F8;
            gPlayer[0].unk_0E8 += gPlayer[0].unk_114;
            if (gPlayer[0].unk_0E8 > 360.0f) {
                gPlayer[0].unk_0E8 -= 360.0f;
            }
            if (gPlayer[0].unk_0E8 < 0.0f) {
                gPlayer[0].unk_0E8 += 360.0f;
            }
            gPlayer[0].unk_114 = 0.0f;
        }
        bossSO->fwork[SO_FWK_31] = 0.0f;
        bossSO->fwork[SO_FWK_3] = 2400.0f;
        Radio_PlayMessage(gMsg_ID_15252, RCID_SLIPPY);
    }
}

void Solar_801A4214(Boss* bossSO) {
    s32 i;
    Vec3f sp50;
    Vec3f sp44;

    if (bossSO->health > 0) {
        return;
    }
    Math_SmoothStepToAngle(&bossSO->obj.rot.y, 0.0f, 0.1f, 3.0f, 0.0f);
    Math_SmoothStepToAngle(&bossSO->obj.rot.x, 0.0f, 0.1f, 3.0f, 0.0f);
    if ((bossSO->unk_04C == 52) && (bossSO->swork[SO_SWK_1] == 5)) {
        bossSO->unk_04C = 38;
        bossSO->fwork[SO_FWK_0] = 0.05f;
    }
    Matrix_RotateX(gCalcMatrix, bossSO->fwork[SO_FWK_1] * M_DTOR, 0);
    Matrix_RotateY(gCalcMatrix, -bossSO->fwork[SO_FWK_2] * M_DTOR, 1);
    sp50.x = 0.0f;
    sp50.y = 200.0f;
    sp50.z = 1100.0f;
    Matrix_MultVec3f(gCalcMatrix, &sp50, &sp44);
    if (bossSO->state >= 2) {
        Math_SmoothStepToF(&D_ctx_801779A8[gMainController], 30.0f, 1.0f, 2.5f, 0.0f);
    }
    switch (bossSO->state) {
        case 0:
            if (D_i3_801C2740[0] >= 33) {
                D_i3_801C2740[0] -= 3;
            }
            if (bossSO->timer_058 == 19910) {
                bossSO->state++;
                bossSO->swork[SO_SWK_1] = 5;
                bossSO->unk_04C = 0;
                bossSO->fwork[SO_FWK_0] = 0.05f;
            }
            Math_SmoothStepToF(&bossSO->obj.pos.y, 180.0f, 0.1f, 10.0f, 0.1f);
            break;
        case 1:
            if (bossSO->unk_04C == 51) {
                bossSO->unk_04C = 50;
                bossSO->state++;
                gShowBossHealth = false;
                AUDIO_PLAY_SFX(0x39439076, bossSO->sfxSource, 4);
                Solar_801A1E14(bossSO->fwork[SO_FWK_4], bossSO->fwork[SO_FWK_5] + 300.0f, bossSO->fwork[SO_FWK_6],
                               bossSO->fwork[SO_FWK_1], bossSO->fwork[SO_FWK_2], 73.0f, RAND_FLOAT_CENTERED(50.0f),
                               80.0f, 40.0f, 8);
                D_i3_801C2768[3] = 6.0f;
                D_i3_801C2768[2] = 100.0f;
                gFillScreenAlpha = 255;
                gFillScreenRed = 255;
                gFillScreenGreen = 255;
                gFillScreenBlue = 255;
                gFillScreenAlphaTarget = 0;
                gFillScreenAlphaStep = 4;
                func_boss_80042EC0(bossSO);
                bossSO->swork[SO_SWK_4]++;
                Math_SmoothStepToF(&bossSO->obj.pos.y, 180.0f, 0.1f, 10.0f, 0.1f);
            }
            break;
        case 2:
            if (D_i3_801C2740[0] >= 33) {
                D_i3_801C2740[0] -= 3;
            }
            if (D_i3_801C2740[1] >= 33) {
                Math_SmoothStepToF(&bossSO->obj.pos.y, 180.0f, 0.1f, 10.0f, 0.1f);
                D_i3_801C2740[1] -= 4;
            } else {
                bossSO->state++;
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
                AUDIO_PLAY_SFX(0x2940F026, gActors[5].sfxSource, 4);
                D_ctx_801779A8[gMainController] = 120.0f;
            }
            if (gCsFrameCount == 250) {
                bossSO->state++;
                bossSO->obj.pos.y = -1600.0f;
                for (i = 0; i < 2; i++) {
                    if (gEffects[i].obj.status != OBJ_FREE) {
                        Object_Kill(&gEffects[i].obj, gEffects[i].sfxSource);
                    }
                }
                bossSO->timer_058 = 100;
            }
            break;
        case 4:
            if (bossSO->timer_058 == 1) {
                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 80);
                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 80);
                Object_Kill(&bossSO->obj, bossSO->sfxSource);
            }
            break;
    }
}

void Solar_801A48B8(Boss* bossSO) {
    s32 i;

    AUDIO_PLAY_SFX(0x29434075, bossSO->sfxSource, 4);
    D_80137E84[gMainController] = 1;
    D_Timer_80177BD0[gMainController] = 10;
    if (bossSO->swork[SO_SWK_0] != 6) {
        bossSO->swork[SO_SWK_5] = bossSO->swork[SO_SWK_0];
        bossSO->swork[SO_SWK_6] = bossSO->swork[SO_SWK_1];
        bossSO->swork[SO_SWK_7] = bossSO->unk_04C;
    }
    if ((bossSO->swork[SO_SWK_0] == 4) && (bossSO->unk_04C >= 60) && (bossSO->unk_04C < 67)) {
        for (i = 4; i < 60; i++) {
            if (gActors[i].obj.id == OBJ_ACTOR_278) {
                gActors[i].unk_0D0 = 2;
                break;
            }
        }
    }
    gFillScreenRed = gFillScreenGreen = gFillScreenBlue = gFillScreenAlpha = 255;
    gFillScreenAlphaTarget = 0;
    gFillScreenAlphaStep = 64;
    bossSO->swork[SO_SWK_0] = 6;
    bossSO->swork[SO_SWK_1] = 6;
    bossSO->unk_04C = 0;
    bossSO->fwork[SO_FWK_0] = 0.01f;
    if (((bossSO->swork[SO_SWK_2] > 0) || (bossSO->swork[SO_SWK_3] > 0)) && (gTeamShields[TEAM_ID_SLIPPY] > 0)) {
        Radio_PlayMessage(gMsg_ID_7086, RCID_SLIPPY);
    }
}

void Solar_801A4A34(Boss* bossSO) {
    if (bossSO->swork[SO_SWK_2] < 0) {
        bossSO->swork[SO_SWK_2] = 0;
        Solar_801A1E14(bossSO->fwork[SO_FWK_28], bossSO->fwork[SO_FWK_29], bossSO->fwork[SO_FWK_30],
                       bossSO->fwork[SO_FWK_41], bossSO->fwork[SO_FWK_42], bossSO->fwork[SO_FWK_43],
                       RAND_FLOAT(-25.0f) - 10.0f, RAND_FLOAT(25.0f) + 30.0f, RAND_FLOAT_CENTERED(25.0f) - 50.0f, 0);
        Solar_801A1E14(bossSO->fwork[SO_FWK_22], bossSO->fwork[SO_FWK_23], bossSO->fwork[SO_FWK_24],
                       bossSO->fwork[SO_FWK_47], bossSO->fwork[SO_FWK_48], bossSO->fwork[SO_FWK_49],
                       RAND_FLOAT(-25.0f) - 10.0f, RAND_FLOAT(25.0f) + 30.0f, RAND_FLOAT_CENTERED(25.0f) - 50.0f, 1);
        Solar_801A1E14(bossSO->fwork[SO_FWK_10], bossSO->fwork[SO_FWK_11], bossSO->fwork[SO_FWK_12],
                       bossSO->fwork[SO_FWK_35], bossSO->fwork[SO_FWK_36], bossSO->fwork[SO_FWK_37],
                       RAND_FLOAT(-25.0f) - 10.0f, RAND_FLOAT(25.0f) + 30.0f, RAND_FLOAT_CENTERED(25.0f) - 50.0f, 2);
    }
    if (bossSO->swork[SO_SWK_3] < 0) {
        bossSO->swork[SO_SWK_3] = 0;
        Solar_801A1E14(bossSO->fwork[SO_FWK_25], bossSO->fwork[SO_FWK_26], bossSO->fwork[SO_FWK_27],
                       bossSO->fwork[SO_FWK_38], bossSO->fwork[SO_FWK_39], bossSO->fwork[SO_FWK_40],
                       RAND_FLOAT(25.0f) + 10.0f, RAND_FLOAT(25.0f) + 30.0f, RAND_FLOAT_CENTERED(25.0f) - 50.0f, 5);
        Solar_801A1E14(bossSO->fwork[SO_FWK_19], bossSO->fwork[SO_FWK_20], bossSO->fwork[SO_FWK_21],
                       bossSO->fwork[SO_FWK_44], bossSO->fwork[SO_FWK_45], bossSO->fwork[SO_FWK_46],
                       RAND_FLOAT(25.0f) + 10.0f, RAND_FLOAT(25.0f) + 30.0f, RAND_FLOAT_CENTERED(25.0f) - 50.0f, 4);
        Solar_801A1E14(bossSO->fwork[SO_FWK_7], bossSO->fwork[SO_FWK_8], bossSO->fwork[SO_FWK_9],
                       bossSO->fwork[SO_FWK_32], bossSO->fwork[SO_FWK_33], bossSO->fwork[SO_FWK_34],
                       RAND_FLOAT(25.0f) + 10.0f, RAND_FLOAT(25.0f) + 30.0f, RAND_FLOAT_CENTERED(25.0f) - 50.0f, 3);
    }
    switch (bossSO->unk_04C) {
        case 30:
            AUDIO_PLAY_SFX(0x29433074, bossSO->sfxSource, 4);
            /* fallthrough */
        case 35:
        case 97:
            AUDIO_PLAY_SFX(0x29434075, bossSO->sfxSource, 4);
            break;
    }
    if (bossSO->unk_04C == 119) {
        bossSO->swork[SO_SWK_0] = bossSO->swork[SO_SWK_5];
        bossSO->swork[SO_SWK_1] = bossSO->swork[SO_SWK_6];
        if ((bossSO->swork[SO_SWK_5] == 2) || (bossSO->swork[SO_SWK_5] == 3)) {
            bossSO->unk_04C = bossSO->swork[SO_SWK_7];
        } else {
            bossSO->unk_04C = 0;
        }
        bossSO->fwork[SO_FWK_0] = 0.01f;
    }
}

void Solar_801A4EC0(Boss* bossSO) {
    bossSO->swork[SO_SWK_0] = 7;
    bossSO->swork[SO_SWK_1] = 5;
    bossSO->fwork[SO_FWK_0] = 0.01f;
    bossSO->unk_04C = 0;
    bossSO->state = 0;
    bossSO->fwork[SO_FWK_31] = bossSO->obj.rot.y = 0.0f;
}

void Solar_801A4EF8(Boss* bossSO) {
    s32 i;

    if (bossSO->swork[SO_SWK_11] != 0) {
        bossSO->swork[SO_SWK_11]--;
    }
    switch (bossSO->state) {
        case 0:
            bossSO->unk_04C = 0;
            if (bossSO->fwork[SO_FWK_31] > 20.0f) {
                bossSO->state++;
                bossSO->swork[SO_SWK_11] = 108;
                bossSO->fwork[SO_FWK_0] = 0.01f;
                bossSO->unk_04C = 56;
            }
            if (bossSO->obj.rot.y == 0.0f) {
                AUDIO_PLAY_SFX(0x39033079, bossSO->sfxSource, 4);
            }
            bossSO->fwork[SO_FWK_31] += 0.5f;
            bossSO->obj.rot.y += bossSO->fwork[SO_FWK_31];
            if (bossSO->obj.rot.y >= 360.0f) {
                bossSO->obj.rot.y -= 360.0f;
                AUDIO_PLAY_SFX(0x39033079, bossSO->sfxSource, 4);
            }
            bossSO->unk_078.y = bossSO->obj.rot.y;
            break;
        case 1:
            bossSO->obj.rot.y += bossSO->fwork[SO_FWK_31];
            bossSO->unk_04C = 56;
            if (bossSO->obj.rot.y >= 360.0f) {
                bossSO->obj.rot.y -= 360.0f;
                AUDIO_PLAY_SFX(0x39033079, bossSO->sfxSource, 4);
            }
            if (bossSO->swork[SO_SWK_11] <= 45) {
                Math_SmoothStepToF(&bossSO->obj.pos.y, -1000.0f, 0.1f, 20.0f, 0.1f);
            }
            if (bossSO->swork[SO_SWK_11] == 30) {
                Solar_801A0CEC(&gActors[10], bossSO->obj.pos.x, bossSO->obj.pos.z + 1000.0f, 20.0f, 1);
                D_80137E84[gMainController] = 1;
                D_Timer_80177BD0[gMainController] = 70;
                for (i = 0; i < 4; i++) {
                    Solar_8019F038(bossSO->obj.pos.x + 100.0f, 100.0f, bossSO->obj.pos.z + 1100.0f,
                                   D_i3_801BF8F0[i].x + RAND_FLOAT_CENTERED(2.0f),
                                   D_i3_801BF8F0[i].y + 10.0f + RAND_FLOAT_CENTERED(2.0f), RAND_FLOAT(-10.0f) - 10.0f);
                    Solar_8019F038(bossSO->obj.pos.x - 100.0f, 100.0f, bossSO->obj.pos.z + 1100.0f,
                                   D_i3_801BF8F0[i].x + RAND_FLOAT_CENTERED(2.0f),
                                   D_i3_801BF8F0[i].y + 10.0f + RAND_FLOAT_CENTERED(2.0f), RAND_FLOAT(-10.0f) - 10.0f);
                }
            }
            if (bossSO->swork[SO_SWK_11] == 16) {
                gActors[10].unk_0D0 = 2;
            }
            if (bossSO->obj.pos.y <= -900.0f) {
                bossSO->state++;
                bossSO->swork[SO_SWK_11] = 500;
                bossSO->obj.pos.y = -1500.0f;
                bossSO->fwork[SO_FWK_3] = 4800.0f;
                bossSO->obj.pos.z = gPlayer[0].unk_138 - bossSO->fwork[SO_FWK_3];
                bossSO->swork[SO_SWK_1] = 0;
                bossSO->unk_078.y = bossSO->obj.rot.y = 0.0f;
                bossSO->vel.y = 0.0f;
                bossSO->obj.rot.x = 0.0f;
            }
            bossSO->unk_078.y = bossSO->obj.rot.y;
            break;
        case 2:
            bossSO->unk_04C = 0;
            if (bossSO->swork[SO_SWK_11] == 300) {
                D_80137E84[gMainController] = 1;
                D_Timer_80177BD0[gMainController] = 170;
                gCameraShake = 130;
            }
            if (bossSO->swork[SO_SWK_11] == 200) {
                Solar_801A0CEC(&gActors[9], bossSO->obj.pos.x, bossSO->obj.pos.z + 1000.0f, 20.0f, 1);
            }
            if (bossSO->swork[SO_SWK_11] < 200) {
                bossSO->unk_04C = 98;
                bossSO->unk_078.y += bossSO->fwork[SO_FWK_31];
                if (bossSO->swork[SO_SWK_11] == 170) {
                    AUDIO_PLAY_SFX(0x29432073, bossSO->sfxSource, 4);
                    bossSO->obj.pos.y = -500.0f;
                    gActors[9].unk_0D0 = 2;
                }
                if (bossSO->swork[SO_SWK_11] <= 170) {
                    bossSO->vel.y = COS_DEG(bossSO->obj.rot.x) * 80.0f;
                    bossSO->vel.z = (SIN_DEG(bossSO->obj.rot.x) * 30.0f) + gPlayer[0].vel.z;
                }
                if (bossSO->obj.rot.x < 190.0f) {
                    bossSO->obj.rot.x += 1.0f;
                }
                if (bossSO->swork[SO_SWK_11] == 50) {
                    Solar_801A0CEC(&gActors[10], bossSO->obj.pos.x, bossSO->obj.pos.z + 1000.0f, 80.0f, 2);
                    D_80137E84[gMainController] = 1;
                    D_Timer_80177BD0[gMainController] = 100;
                    gCameraShake = 10;
                }
                if (bossSO->obj.pos.y < -1500.0f) {
                    bossSO->state++;
                    bossSO->swork[SO_SWK_11] = 100;
                    bossSO->obj.pos.y = -500.0f;
                    bossSO->fwork[SO_FWK_3] = 4800.0f;
                    bossSO->obj.pos.z = gPlayer[0].unk_138 - bossSO->fwork[SO_FWK_3];
                    bossSO->unk_04C = 0;
                    bossSO->obj.rot.x = 0.0f;
                    bossSO->fwork[SO_FWK_31] = bossSO->vel.y = bossSO->vel.z = 0.0f;
                    bossSO->obj.rot.y = 330.0f;
                }
            }
            break;
        case 3:
            Math_SmoothStepToAngle(&bossSO->obj.rot.y, 0.0f, 1.0f, 1.5f, 1.0f);
            if (bossSO->swork[SO_SWK_11] == 65) {
                Solar_801A0CEC(&gActors[9], bossSO->obj.pos.x, bossSO->obj.pos.z + 1000.0f, 20.0f, 1);
            }
            if (bossSO->swork[SO_SWK_11] == 0) {
                bossSO->swork[SO_SWK_11] = 220;
            }
            if (bossSO->swork[SO_SWK_11] == 210) {
                bossSO->unk_04C = 0;
                bossSO->swork[SO_SWK_1] = 1;
            }
            if (bossSO->swork[SO_SWK_11] >= 100) {
                Math_SmoothStepToF(&bossSO->obj.pos.y, 180.0f, 0.1f, 10.0f, 0.1f);
            }
            if (bossSO->swork[SO_SWK_11] == 150) {
                Solar_801A3468(bossSO);
                bossSO->fwork[SO_FWK_0] = 0.01f;
            }
            if (bossSO->swork[SO_SWK_11] == 50) {
                gActors[9].unk_0D0 = 2;
            }
            break;
    }
}

void Solar_801A56B8(Boss* bossSO) {
    switch (bossSO->swork[SO_SWK_1]) {
        case 2:
            if (((bossSO->unk_04C == 89) && (bossSO->state == 2)) || (bossSO->swork[SO_SWK_2] == 0)) {
                bossSO->unk_04C = 0;
                bossSO->state = 0;
                bossSO->unk_078.y = 0.0f;
            }
            if (bossSO->unk_04C == 89) {
                bossSO->state++;
                bossSO->unk_078.y += 15.0f;
            }
            Math_SmoothStepToAngle(&bossSO->obj.rot.y, bossSO->unk_078.y, 1.0f, 3.0f, 1.0f);
            if (bossSO->unk_04C > 18) {
                bossSO->info.hitbox[20] = 715.0f;
                bossSO->info.hitbox[22] = 440.0f;
                bossSO->info.hitbox[24] = 110.0f;
            }
            if (bossSO->unk_04C > 36) {
                bossSO->info.hitbox[20] = 220.0f;
                bossSO->info.hitbox[22] = 715.0f;
                bossSO->info.hitbox[24] = 220.0f;
            }
            break;
        case 4:
            if ((bossSO->unk_04C == 99) || (bossSO->swork[SO_SWK_2] == 0)) {
                bossSO->unk_04C = 0;
                if ((bossSO->swork[SO_SWK_3] != 0) || (bossSO->swork[SO_SWK_2] != 0)) {
                    bossSO->swork[SO_SWK_1] = 5;
                } else {
                    bossSO->swork[SO_SWK_1] = 7;
                }
            }
            if (bossSO->unk_04C > 20) {
                bossSO->info.hitbox[20] = 715.0f;
                bossSO->info.hitbox[22] = 110.0f;
                bossSO->info.hitbox[24] = 275.0f;
            }
            if (bossSO->unk_04C > 84) {
                bossSO->info.hitbox[20] = 220.0f;
                bossSO->info.hitbox[22] = 715.0f;
                bossSO->info.hitbox[24] = 220.0f;
            }
            break;
        case 5:
            bossSO->fwork[SO_FWK_3] = 4800.0f;
            if (bossSO->unk_04C == 65) {
                bossSO->timer_050 = 30;
            }
            if (bossSO->timer_050 != 0) {
                bossSO->unk_04C = 65;
            }
            if ((bossSO->unk_04C == 65) && ((gGameFrameCount % 4) == 0)) {
                Solar_8019FFC0(bossSO, bossSO->fwork[SO_FWK_4] + 125.0f, bossSO->fwork[SO_FWK_5] - 100.0f,
                               bossSO->fwork[SO_FWK_6] + 600.0f, ((f32) bossSO->timer_050 * 0.2f) + 4.0f, 1);
                Solar_8019FFC0(bossSO, bossSO->fwork[SO_FWK_4] - 125.0f, bossSO->fwork[SO_FWK_5] - 100.0f,
                               bossSO->fwork[SO_FWK_6] + 600.0f, ((f32) bossSO->timer_050 * 0.2f) + 4.0f, 2);
                Solar_801A1EB0(bossSO, bossSO->fwork[SO_FWK_4], 25.0f, bossSO->fwork[SO_FWK_5] - 100.0f,
                               bossSO->fwork[SO_FWK_6] + 300.0f);
            }
            break;
        case 7:
            if (bossSO->unk_04C < 50) {
                if (bossSO->fwork[SO_FWK_31] < 22.0f) {
                    bossSO->fwork[SO_FWK_31] += 0.5f;
                }
                bossSO->obj.rot.y += bossSO->fwork[SO_FWK_31];
            }
            if ((bossSO->unk_04C >= 50) && (bossSO->unk_04C <= 100)) {
                if (bossSO->fwork[SO_FWK_31] > 0.0f) {
                    bossSO->fwork[SO_FWK_31] -= 0.5f;
                }
                bossSO->obj.rot.y += bossSO->fwork[SO_FWK_31];
            }
            if (bossSO->unk_04C >= 100) {
                Math_SmoothStepToAngle(&bossSO->obj.rot.y, 0.0f, 1.0f, 2.0f, 1.0f);
                bossSO->fwork[SO_FWK_31] = 0.0f;
            }
            if (bossSO->unk_04C == 120) {
                bossSO->swork[SO_SWK_1] = 5;
                bossSO->unk_04C = 0;
                bossSO->fwork[SO_FWK_0] = 0.1f;
            }
            break;
    }
}

BossSOfunc D_i3_801BF980[9] = {
    Solar_801A1F80, Solar_801A23F4, Solar_801A2C98, Solar_801A3128, Solar_801A3510,
    Solar_801A4214, Solar_801A4A34, Solar_801A4EF8, Solar_801A56B8,
};

void Solar_801A5B3C(Boss* bossSO) {
    f32 sp1CC;
    f32 sp1C8;
    f32 sp1C4;
    f32 sp1C0;
    s32 sp1BC;
    s32 sp1B8;
    Vec3f sp50[30];
    Vec3f sp44;
    Vec3f sp38;

    gBossFrameCount++;

    if (bossSO->swork[SO_SWK_9] != 0) {
        bossSO->swork[SO_SWK_9]--;
    }
    if (bossSO->swork[SO_SWK_8] != 0) {
        bossSO->swork[SO_SWK_8]--;
    }
    if (bossSO->swork[SO_SWK_10] != 0) {
        bossSO->swork[SO_SWK_10]--;
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
    if (bossSO->health != 0) {
        Math_SmoothStepToF(&bossSO->obj.pos.z, gPlayer[0].unk_138 - bossSO->fwork[SO_FWK_3], 1.0f, 60.0f, 1.0f);
    } else {
        Math_SmoothStepToF(&bossSO->obj.pos.z, -(D_ctx_80177D20 + 2600.0f), 1.0f, 40.0f, 1.0f);
    }
    if (bossSO->swork[SO_SWK_2] != 0) {
        bossSO->info.hitbox[7] = bossSO->fwork[SO_FWK_12] - bossSO->obj.pos.z;
        bossSO->info.hitbox[9] = bossSO->fwork[SO_FWK_11] - bossSO->obj.pos.y;
        bossSO->info.hitbox[11] = bossSO->fwork[SO_FWK_10] - bossSO->obj.pos.x;
        bossSO->info.hitbox[13] = bossSO->fwork[SO_FWK_24] - bossSO->obj.pos.z;
        bossSO->info.hitbox[15] = bossSO->fwork[SO_FWK_23] - bossSO->obj.pos.y;
        bossSO->info.hitbox[17] = bossSO->fwork[SO_FWK_22] - bossSO->obj.pos.x;
        Matrix_RotateY(gCalcMatrix, -bossSO->obj.rot.y * M_DTOR, 0);
        sp44.x = bossSO->fwork[SO_FWK_28] - bossSO->obj.pos.x;
        sp44.y = bossSO->fwork[SO_FWK_29] - bossSO->obj.pos.y;
        sp44.z = bossSO->fwork[SO_FWK_30] - bossSO->obj.pos.z;
        Matrix_MultVec3f(gCalcMatrix, &sp44, &sp38);
        bossSO->info.hitbox[19] = sp38.z;
        bossSO->info.hitbox[21] = sp38.y;
        bossSO->info.hitbox[23] = sp38.x;
    }
    if (bossSO->swork[SO_SWK_3] != 0) {
        bossSO->info.hitbox[25] = bossSO->fwork[SO_FWK_9] - bossSO->obj.pos.z;
        bossSO->info.hitbox[27] = bossSO->fwork[SO_FWK_8] - bossSO->obj.pos.y;
        bossSO->info.hitbox[29] = bossSO->fwork[SO_FWK_7] - bossSO->obj.pos.x;
        bossSO->info.hitbox[31] = bossSO->fwork[SO_FWK_21] - bossSO->obj.pos.z;
        bossSO->info.hitbox[33] = bossSO->fwork[SO_FWK_20] - bossSO->obj.pos.y;
        bossSO->info.hitbox[35] = bossSO->fwork[SO_FWK_19] - bossSO->obj.pos.x;
        bossSO->info.hitbox[37] = bossSO->fwork[SO_FWK_27] - bossSO->obj.pos.z;
        bossSO->info.hitbox[39] = bossSO->fwork[SO_FWK_26] - bossSO->obj.pos.y;
        bossSO->info.hitbox[41] = bossSO->fwork[SO_FWK_25] - bossSO->obj.pos.x;
    }
    if (((gGameFrameCount % 8) == 0) && (bossSO->fwork[SO_FWK_3] < 4800.0f)) {
        if (func_play_800A73E4(&sp1C0, &sp1B8, bossSO->obj.pos.x, bossSO->obj.pos.y - 160.0f, bossSO->obj.pos.z)) {
            Solar_801A1EB0(bossSO, bossSO->obj.pos.x, 50.0f, sp1C0 - 170.0f, bossSO->obj.pos.z + 100.0f);
        }
        if ((bossSO->swork[SO_SWK_2] != 0) && func_play_800A73E4(&sp1C0, &sp1B8, bossSO->fwork[SO_FWK_16],
                                                                 bossSO->fwork[SO_FWK_17], bossSO->fwork[SO_FWK_18])) {
            Solar_801A1EB0(bossSO, bossSO->fwork[SO_FWK_16], 50.0f, sp1C0 - 150.f, bossSO->fwork[SO_FWK_18] + 150.0f);
        }
        if ((bossSO->swork[SO_SWK_3] != 0) && func_play_800A73E4(&sp1C0, &sp1B8, bossSO->fwork[SO_FWK_13],
                                                                 bossSO->fwork[SO_FWK_14], bossSO->fwork[SO_FWK_15])) {
            Solar_801A1EB0(bossSO, bossSO->fwork[SO_FWK_13], 50.0f, sp1C0 - 150.0f, bossSO->fwork[SO_FWK_15] + 150.0f);
        }
    }
    if ((((gGameFrameCount % 4) == 0) || (bossSO->fwork[SO_FWK_31] != 0.0f)) &&
        ((bossSO->swork[SO_SWK_0] != 7) || ((gGameFrameCount % 2) == 0))) {
        if ((bossSO->swork[SO_SWK_2] == 0) && ((bossSO->health > 0) || (bossSO->state < 2))) {
            Solar_8019FF44(bossSO, bossSO->fwork[SO_FWK_10], bossSO->fwork[SO_FWK_11], bossSO->fwork[SO_FWK_12],
                           bossSO->fwork[SO_FWK_31] - 20.0f, -1.0f);
        }
        if ((bossSO->swork[SO_SWK_3] == 0) && ((bossSO->health > 0) || (bossSO->state < 2))) {
            Solar_8019FF44(bossSO, bossSO->fwork[SO_FWK_7], bossSO->fwork[SO_FWK_8], bossSO->fwork[SO_FWK_9],
                           bossSO->fwork[SO_FWK_31] - 20.0f, 1.0f);
        }
    }
    Math_SmoothStepToF(&bossSO->fwork[0], 1.0f, 0.01f, 0.01f, 0.0f);
    if ((bossSO->health > 0) || (bossSO->swork[SO_SWK_0] == 0)) {
        D_i3_801BF980[bossSO->swork[SO_SWK_0]](bossSO);
    }
    if (bossSO->timer_058 != 0) {
        Solar_801A4214(bossSO);
    }
    switch (bossSO->swork[SO_SWK_1]) {
        case 0:
            bossSO->unk_04C++;
            if (bossSO->unk_04C == 75) {
                AUDIO_PLAY_SFX(0x29432073, bossSO->sfxSource, 4);
            }
            if (bossSO->unk_04C >= Animation_GetFrameCount(&D_SO_601388C)) {
                if (bossSO->health != 0) {
                    bossSO->unk_04C = 0;
                    bossSO->swork[SO_SWK_1]++;
                    bossSO->fwork[SO_FWK_0] = 0.01f;
                } else {
                    bossSO->unk_04C = Animation_GetFrameCount(&D_SO_601388C) - 1;
                }
            }
            sp1BC = Animation_GetFrameData(&D_SO_601388C, bossSO->unk_04C, sp50);
            break;
        case 1:
            bossSO->unk_04C++;
            if (bossSO->unk_04C >= Animation_GetFrameCount(&D_SO_600D3DC)) {
                bossSO->unk_04C = 0;
            }
            sp1BC = Animation_GetFrameData(&D_SO_600D3DC, bossSO->unk_04C, sp50);
            break;
        case 2:
            bossSO->unk_04C++;
            if (bossSO->unk_04C >= Animation_GetFrameCount(&D_SO_600E2C4)) {
                bossSO->unk_04C = 0;
            }
            sp1BC = Animation_GetFrameData(&D_SO_600E2C4, bossSO->unk_04C, sp50);
            break;
        case 3:
            bossSO->unk_04C++;
            if (bossSO->unk_04C >= Animation_GetFrameCount(&D_SO_600F744)) {
                bossSO->unk_04C = 0;
            }
            sp1BC = Animation_GetFrameData(&D_SO_600F744, bossSO->unk_04C, sp50);
            break;
        case 4:
            bossSO->unk_04C++;
            if (bossSO->unk_04C >= Animation_GetFrameCount(&D_SO_600C15C)) {
                bossSO->unk_04C = 0;
            }
            sp1BC = Animation_GetFrameData(&D_SO_600C15C, bossSO->unk_04C, sp50);
            break;
        case 5:
        case 8:
        case 9:
            bossSO->unk_04C++;
            if ((bossSO->unk_04C == 45) && (bossSO->health != 0)) {
                AUDIO_PLAY_SFX(0x29432073, bossSO->sfxSource, 4);
            }
            if (bossSO->unk_04C >= Animation_GetFrameCount(&D_SO_6012C00)) {
                bossSO->unk_04C = 0;
            }
            sp1BC = Animation_GetFrameData(&D_SO_6012C00, bossSO->unk_04C, sp50);
            break;
        case 6:
            bossSO->unk_04C++;
            if (bossSO->unk_04C >= Animation_GetFrameCount(&D_SO_600B1B4)) {
                bossSO->unk_04C = 0;
            }
            sp1BC = Animation_GetFrameData(&D_SO_600B1B4, bossSO->unk_04C, sp50);
            break;
        case 7:
            bossSO->unk_04C++;
            if (bossSO->unk_04C >= Animation_GetFrameCount(&D_SO_6009D30)) {
                bossSO->unk_04C = 0;
            }
            sp1BC = Animation_GetFrameData(&D_SO_6009D30, bossSO->unk_04C, sp50);
            break;
    }
    Matrix_RotateZ(gCalcMatrix, -bossSO->vwork[SO_VWK_29].z * M_DTOR, 0);
    Matrix_RotateX(gCalcMatrix, -bossSO->vwork[SO_VWK_29].x * M_DTOR, 1);
    Matrix_RotateY(gCalcMatrix, -bossSO->vwork[SO_VWK_29].y * M_DTOR, 1);
    Matrix_RotateZ(gCalcMatrix, -bossSO->obj.rot.z * M_DTOR, 1);
    Matrix_RotateX(gCalcMatrix, -bossSO->obj.rot.x * M_DTOR, 1);
    Matrix_RotateY(gCalcMatrix, -bossSO->obj.rot.y * M_DTOR, 1);
    if ((bossSO->health > 0) && (bossSO->swork[SO_SWK_0] == 1)) {
        sp44.x = gPlayer[0].pos.x - bossSO->obj.pos.x;
        sp44.y = gPlayer[0].pos.y - bossSO->obj.pos.y;
        sp44.z = gPlayer[0].pos.z - bossSO->obj.pos.z;
        Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp44, &sp38);
        sp1C4 = Math_RadToDeg(Math_Atan2F(sp38.x, sp38.z));
        sp1CC = sqrtf(SQ(sp38.x) + SQ(sp38.z));
        sp1C8 = Math_RadToDeg(-Math_Atan2F(sp38.y, sp1CC));
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
    Math_SmoothStepToVec3fArray(sp50, bossSO->vwork, 1, sp1BC, bossSO->fwork[SO_FWK_0], 100.0f, 0.0f);
    if ((bossSO->dmgType != DMG_NONE) && (bossSO->health > 0)) {
        bossSO->dmgType = DMG_NONE;
        AUDIO_PLAY_SFX(0x29121007, bossSO->sfxSource, 4);
        if (!((bossSO->swork[SO_SWK_0] == 0) || (bossSO->swork[SO_SWK_0] == 2) || (bossSO->swork[SO_SWK_0] == 3) ||
              (bossSO->swork[SO_SWK_0] == 6) || ((bossSO->swork[SO_SWK_0] == 7) && (bossSO->state == 2)))) {
            Solar_801A3C4C(bossSO);
        }
    }
    if (gBossFrameCount == 400) {
        gShowBossHealth = true;
    }
    if (gBossFrameCount >= 400) {
        gBossHealthBar = (bossSO->health + bossSO->swork[SO_SWK_2] + bossSO->swork[SO_SWK_3]) * (255.0f / 1400.0f);
    }
}

bool Solar_801A68A8(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    Boss* this = thisx;
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

void Solar_801A6BDC(s32 limbIndex, Vec3f* rot, void* thisx) {
    Boss* this = thisx;
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
        default:
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

void Solar_801A71B8(Boss* bossSO) {
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

    Matrix_Scale(gCalcMatrix, bossSO->unk_3F8, bossSO->unk_3F8, bossSO->unk_3F8, 1);
    if (gBossActive != 0) {
        Animation_DrawSkeleton(2, D_SO_600E470, bossSO->vwork, Solar_801A68A8, Solar_801A6BDC, bossSO, gCalcMatrix);
    }
    if (bossSO->health <= 0) {
        RCP_SetupDL_49();
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
        gDPSetEnvColor(gMasterDisp++, 255, 192, 0, 255);
        Matrix_Pop(&gGfxMatrix);
        Matrix_Push(&gGfxMatrix);
        Matrix_Translate(gGfxMatrix, bossSO->obj.pos.x, bossSO->obj.pos.y, bossSO->obj.pos.z - 500.0f + D_ctx_80177D20,
                         1);
        Matrix_Scale(gGfxMatrix, D_i3_801C2768[3], D_i3_801C2768[2], 1.0f, 1);
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, D_1024AC0);
        for (i = 0; i < 9; i++) {
            Matrix_Pop(&gGfxMatrix);
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, bossSO->obj.pos.x + spE8[i].x, bossSO->obj.pos.y + spE8[i].y,
                             bossSO->obj.pos.z + D_ctx_80177D20 + spE8[i].z, 1);
            Matrix_RotateY(gGfxMatrix, spC4[i] * M_DTOR, 1);
            Matrix_RotateX(gGfxMatrix, spA0[i] * M_DTOR, 1);
            Matrix_Scale(gGfxMatrix, D_i3_801C2768[4 + i], 100.0f, 1.0f, 1);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_1024AC0);
        }
        if (D_i3_801C2768[13] > 0.0f) {
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 192, 64, 255);
            Matrix_Pop(&gGfxMatrix);
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, bossSO->obj.pos.x, bossSO->obj.pos.y + 230.0f,
                             bossSO->obj.pos.z - 300.0f + D_ctx_80177D20, 1);
            Matrix_RotateX(gGfxMatrix, M_DTOR * 5.0f, 1);
            Matrix_Scale(gGfxMatrix, D_i3_801C2768[13], 1.0f, D_i3_801C2768[13], 1);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_BG_PLANET_20112C0);
            Matrix_Scale(gGfxMatrix, 0.6f, 1.0f, 0.6f, 1);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_BG_PLANET_20112C0);
            Matrix_Pop(&gGfxMatrix);
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, bossSO->obj.pos.x, bossSO->obj.pos.y + 270.0f,
                             (bossSO->obj.pos.z - 300.0f) + D_ctx_80177D20, 1);
            Matrix_RotateX(gGfxMatrix, -3.0f * M_DTOR, 1);
            Matrix_Scale(gGfxMatrix, D_i3_801C2768[13], 1.0f, D_i3_801C2768[13], 1);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_BG_PLANET_20112C0);
            Matrix_Scale(gGfxMatrix, 0.6f, 1.0f, 0.6f, 1);
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
    Actor* actor = gActors;
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
        actor->obj.id = OBJ_ACTOR_195;

        actor->obj.pos.x = D_i3_801BFB30[i].x / 2.0f + gPlayer[0].pos.x;
        actor->obj.pos.y = D_i3_801BFB30[i].y + gPlayer[0].pos.y;
        actor->obj.pos.z = D_i3_801BFB30[i].z + gPlayer[0].pos.z;
        actor->state = 1;
        Object_SetInfo(&actor->info, actor->obj.id);
        actor->iwork[11] = 1;
        AUDIO_PLAY_SFX(0x3100000C, actor->sfxSource, 4);
    }
}

void Solar_801A7930(Player* player) {
    s32 i;
    f32 sp78;
    f32 sp74;
    f32 dx;
    f32 dz;
    Vec3f sp60;
    Vec3f sp54;
    Boss* bossSO = &gBosses[0];

    switch (player->unk_1D0) {
        case 0:
            gCsFrameCount = 0;
            player->unk_034 = player->unk_4D8 = 0.0f;
            player->unk_0D0 = 40.0f;

            player->wings.unk_04 = player->wings.unk_0C = player->wings.unk_08 = player->wings.unk_10 =
                player->unk_130 = player->unk_12C = player->unk_110 = 0.0f;
            player->unk_234 = 1;
            gCsCamEyeX = player->camEye.x;
            gCsCamEyeY = player->camEye.y;
            gCsCamEyeZ = player->camEye.z;
            gCsCamAtX = player->camAt.x;
            gCsCamAtY = player->camAt.y;
            gCsCamAtZ = player->camAt.z;
            for (i = 10; i < 60; i++) {
                if (gActors[i].unk_0B6 == 0) {
                    Object_Kill(&gActors[i].obj, gActors[i].sfxSource);
                }
            }
            Object_Kill(&gActors[2].obj, gActors[2].sfxSource);
            Object_Kill(&gActors[3].obj, gActors[3].sfxSource);
            Object_Kill(&gActors[4].obj, gActors[4].sfxSource);
            player->unk_1D0 = 1;
            D_ctx_80177A48[0] = 0.1f;
            if (Rand_ZeroOne() > 0.5f) {
                D_ctx_80177A48[9] = -1.0f;
            } else {
                D_ctx_80177A48[9] = 1.0f;
            }
            break;
        case 1:
            D_ctx_80177CE8 += 30.0f;
            Math_SmoothStepToF(&player->unk_0E4, 0.0f, 0.1f, 5.0f, 0.0f);
            Math_SmoothStepToF(&player->pos.y, 200.0f, 0.05f, 10.0f, 0.0f);
            dx = player->pos.x - bossSO->obj.pos.x;
            dz = (player->pos.z - bossSO->obj.pos.z) * 0.05f;
            sp78 = Math_RadToDeg(-Math_Atan2F(dx, dz));
            Math_SmoothStepToF(&gCsCamEyeY, 300.0f, 1.0f, 20.0f, 0.0f);
            Math_SmoothStepToF(&gCsCamAtY, 290.0f, 1.0f, 20.0f, 0.0f);
            sp74 = Math_SmoothStepToAngle(&player->unk_0E8, sp78, 0.5f, 2.0f, 0.0001f) * 30.0f;
            if (gCsFrameCount >= 14) {
                Math_SmoothStepToAngle(&player->unk_0EC, sp74, 0.1f, 5.0f, 0.0001f);
                gCsCamAtX = 0.0f;
                gCsCamEyeX = 0.0f;
            } else if (sp74 < 0.0f) {
                player->unk_0EC -= 30.0f;
            } else {
                player->unk_0EC += 30.0f;
            }
            if (gCsFrameCount >= 200) {
                player->unk_0E4 += 1.0f;
                player->unk_0E8 += 1.0f;
                player->unk_0EC += 1.0f;
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
                player->unk_1D0++;
                func_play_800A6148();
                func_8001CA24(0);
                Audio_KillSfxBySource(player->sfxSource);
                gFillScreenAlpha = 250;
                player->timer_1F8 = 20;
                player->unk_0D0 = 0.0f;
                player->unk_0E4 = 0.0f;
                player->unk_0E8 = 0.0f;
                player->unk_0EC = 0.0f;
            }
            break;
        case 2:
            D_ctx_80177CE8 += 60.0f;
            if (player->timer_1F8 == 0) {
                player->pos.x = 0.0f;
                player->pos.y = 200.0f;
                player->pos.z = -(D_ctx_80177D20 - 500.0f);
                player->unk_1D0++;
                player->wings.unk_2C = 1;
                func_8001C8B8(0);
                AUDIO_PLAY_BGM(SEQ_ID_GOOD_END);
                D_ctx_80177A98 = 1;
                func_play_800A6148();
                D_ctx_80177A48[1] = 0.0f;
                D_ctx_80177A48[2] = 0.0f;
                player->camEye.x = 0.0f;
                player->camEye.y = player->pos.y + 80.0f;
                player->camEye.z = player->pos.z + D_ctx_80177D20 - 4000.0f;
                gCsCamEyeZ = player->pos.z + D_ctx_80177D20 - 4900.0f;
                player->camAt.x = gCsCamAtX = 0.0f;
                player->camAt.y = gCsCamAtY = 200.0f;
                player->camAt.z = gCsCamAtZ = player->pos.z + D_ctx_80177D20;
                D_ctx_80177A48[0] = 0.0f;
                Object_Kill(&gActors[4].obj, gActors[4].sfxSource);
                Object_Kill(&gActors[5].obj, gActors[5].sfxSource);
            }
            break;
        case 3:
            D_ctx_80177CE8 += 60.0f;
            gFillScreenAlphaTarget = 0;
            gFillScreenAlphaStep = 4;
            if (D_ctx_801782F8) {
                player->wings.unk_30 = (s32) (gGameFrameCount % 2U) * 5.0f;
            }
            switch (gCsFrameCount) {
                case 450:
                    Solar_801A0DF8(-1200.0f, -(D_ctx_80177D20 + 2500.0f), 90.0f, 2, 1.0f);
                    break;
                case 545:
                    Solar_801A0DF8(1400.0f, -(D_ctx_80177D20 + 3250.0f), -90.0f, 3, 1.0f);
                    break;
                case 550:
                    Object_Kill(&gActors[4].obj, gActors[4].sfxSource);
                    break;
                case 645:
                    Object_Kill(&gActors[5].obj, gActors[5].sfxSource);
                    break;
                case 700:
                    player->unk_1D0++;
                    Solar_801A7750();
                    D_i3_801C2768[3] = 1000.0f;
                    break;
            }
            if ((gCsFrameCount >= 520) && (gCsFrameCount < 605)) {
                Math_SmoothStepToF(&player->pos.x, 400.0f, 0.1f, 10.0f, 0.1f);
            }
            if ((gCsFrameCount >= 520) && (gCsFrameCount < 570)) {
                Math_SmoothStepToAngle(&player->unk_0EC, -30.0f, 0.1f, 5.0f, 0.1f);
            }
            if ((gCsFrameCount >= 570) && (gCsFrameCount < 605)) {
                Math_SmoothStepToAngle(&player->unk_0EC, 0.0f, 0.1f, 5.0f, 0.1f);
            }
            if ((gCsFrameCount >= 605) && (gCsFrameCount < 620)) {
                player->unk_0EC += 30.0f;
            }
            if ((gCsFrameCount >= 620) && (gCsFrameCount < 640)) {
                Math_SmoothStepToAngle(&player->unk_0EC, 45.0f, 0.1f, 5.0f, 0.0f);
            }
            if (gCsFrameCount >= 640) {
                Math_SmoothStepToAngle(&player->unk_0EC, 0.0f, 0.3f, 7.0f, 0.0f);
            }
            if (gCsFrameCount >= 585) {
                Math_SmoothStepToF(&player->pos.x, 0.0f, 0.2f, 9.0f, 0);
            }
            if (gCsFrameCount >= 600) {
                Math_SmoothStepToF(&player->pos.y, 950.0f, 0.1f, 10.0f, 0.0001f);
            }
            Math_SmoothStepToF(&player->pos.z, -(D_ctx_80177D20 + 4350.0f), 1.0f, 20.0f, 0.0001f);
            if (gCsFrameCount >= 620) {
                Math_SmoothStepToF(&player->camEye.x, 0.0f, 1.0f, 10.0f, 0);
                Math_SmoothStepToF(&player->camEye.y, player->pos.y + 52.0f, 1.0f, 16.0f, 0.0f);
                Math_SmoothStepToF(&player->camEye.z, (player->pos.z + D_ctx_80177D20) - 50.0f, 1.0f, 21.5f, 0.0f);
            }
            player->camAt.x = gCsCamAtX = player->pos.x;
            player->camAt.y = gCsCamAtY = player->pos.y;
            player->camAt.z = gCsCamAtZ = player->pos.z + D_ctx_80177D20;
            break;
        case 4:
            D_ctx_80177CE8 += 60.0f;
            gFillScreenAlphaTarget = 0;
            gFillScreenAlphaStep = 4;
            D_ctx_80177A48[1] += D_ctx_80177A48[2] * 0.8f;
            Matrix_RotateY(gCalcMatrix, D_ctx_80177A48[1] * M_DTOR, 0);
            sp60.x = 0.0f;
            sp60.y = 0.0f;
            sp60.z = -700.0f;
            Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp60, &sp54);
            if (gCsFrameCount < 1440) {
                gCsCamEyeX = sp54.x;
                gCsCamEyeY = D_i3_801C2768[3] + sp54.y;
                gCsCamEyeZ = player->pos.z + D_ctx_80177D20 + sp54.z;
                gCsCamAtX = 0.0f;
                gCsCamAtY = player->pos.y + 75.0f;
                Math_SmoothStepToF(&D_i3_801C2768[3], 500.0f, 0.1f, 1.0f, 0.0001f);
                gCsCamAtZ = player->pos.z + D_ctx_80177D20 + 200.0f;
                if (gCsFrameCount >= 1400) {
                    gCsCamAtZ -= (gCsFrameCount * 8) - 11200;
                }
            } else {
                Math_SmoothStepToF(&gCsCamEyeX, 0.0f, 0.1f, 1.0f, 0.0001f);
                gCsCamAtX = 0.0f;
                gCsCamAtY = player->pos.y + 75.0f;
                gCsCamAtZ = player->pos.z + D_ctx_80177D20 + 200.0f - ((gCsFrameCount * 8) - 11200);
            }
            if (gCsFrameCount > 1460) {
                player->unk_0D0 += 2.0f;
                player->unk_0E4 += 0.2f;
                Math_SmoothStepToF(&D_ctx_80177A48[2], 0.0f, 1.0f, 0.001f, 0);
                player->unk_190 = 2.0f;
            } else {
                Math_SmoothStepToF(&D_ctx_80177A48[2], 0.23f, 1.0f, 0.001f, 0.0f);
                Math_SmoothStepToF(&D_ctx_80177A48[0], 0.5f, 0.1f, 0.0005f, 0.0f);
            }
            if (gCsFrameCount == 1560) {
                func_play_800A6148();
            }
            if (gCsFrameCount > 1530) {
                gFillScreenAlphaTarget = 255;
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
                gFillScreenAlphaStep = 8;
                if (gFillScreenAlpha == 255) {
                    func_8001CA24(0);
                    Audio_FadeOutAll(10);
                    player->state_1C8 = PLAYERSTATE_1C8_6;
                    player->timer_1F8 = 0;
                    D_ctx_8017837C = 4;
                    D_play_800D3180[LEVEL_SOLAR] = Play_CheckMedalStatus(100) + 1;
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
                    func_demo_80048AC0(2);
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
                    func_demo_80048AC0(3);
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
                    func_demo_80048AC0(1);
                    break;
            }
            break;
        case 1186:
            D_ctx_80177830 = 1;
            break;
        case 1386:
            D_ctx_80177830 = 0;
            break;
        case 1460:
            AUDIO_PLAY_SFX(0x09000002, player->sfxSource, 0);
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
    Matrix_RotateY(gCalcMatrix, (player->unk_114 + player->unk_0E8 + 180.0f) * M_DTOR, 0);
    Matrix_RotateX(gCalcMatrix, -((player->unk_120 + player->unk_0E4) * M_DTOR), 1);
    sp60.x = 0.0f;
    sp60.y = 0.0f;
    sp60.z = player->unk_0D0;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp60, &sp54);
    player->vel.x = sp54.x;
    player->vel.z = sp54.z;
    player->vel.y = sp54.y;

    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;
    player->pos.z += player->vel.z;

    player->unk_138 = player->pos.z;
    player->unk_0F8 = player->unk_0EC;
    Math_SmoothStepToF(&player->camEye.x, gCsCamEyeX, D_ctx_80177A48[0], 50000.0f, 0.0f);
    Math_SmoothStepToF(&player->camEye.y, gCsCamEyeY, D_ctx_80177A48[0], 50000.0f, 0.0f);
    Math_SmoothStepToF(&player->camEye.z, gCsCamEyeZ, D_ctx_80177A48[0], 50000.0f, 0.0f);
    Math_SmoothStepToF(&player->camAt.x, gCsCamAtX, D_ctx_80177A48[0], 50000.0f, 0.0f);
    Math_SmoothStepToF(&player->camAt.y, gCsCamAtY, D_ctx_80177A48[0], 50000.0f, 0.0f);
    Math_SmoothStepToF(&player->camAt.z, gCsCamAtZ, D_ctx_80177A48[0], 50000.0f, 0.0f);
    player->unk_088 += 10.0f;
    player->unk_080 = -SIN_DEG(player->unk_088) * 0.3f;
    player->unk_0F4 += 8.0f;
    player->unk_0F0 = SIN_DEG(player->unk_0F4);
}

void Solar_801A8BE8(Actor* actor) {
    Vec3f sp3C;
    Vec3f sp30;

    switch (actor->state) {
        case 4:
            break;
        case 1:
            if ((actor->unk_0B6 != 0) && ((((s32) (actor->index % 8U) * 10) + 1030) < gCsFrameCount)) {
                actor->state = 4;
            }
            break;
        case 2:
            actor->state = 3;
            AUDIO_PLAY_SFX(0x09000002, actor->sfxSource, 0);
            actor->fwork[29] = 5.0f;
            /* fallthrough */
        case 3:
            actor->iwork[11] = 2;
            actor->fwork[0] += 2.0f;
            actor->unk_0F4.x += 0.2f;
            break;
    }
    Matrix_RotateY(gCalcMatrix, (actor->unk_0F4.y + 180.0f) * M_DTOR, 0);
    Matrix_RotateX(gCalcMatrix, -(actor->unk_0F4.x * M_DTOR), 1);
    sp3C.x = 0.0f;
    sp3C.y = 0.0f;
    sp3C.z = actor->fwork[0];
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp3C, &sp30);
    actor->vel.x = sp30.x;
    actor->vel.y = sp30.y;
    actor->vel.z = sp30.z;
    actor->obj.rot.x = -actor->unk_0F4.x;
    actor->obj.rot.y = actor->unk_0F4.y + 180.0f;

    actor->obj.rot.z = -actor->unk_0F4.z;
}

void Solar_801A8DB8(Vec3f* pos, u32 sfxId, f32 zVel) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            func_effect_8007A5F8(&gEffects[i], pos, sfxId);
            gEffects[i].vel.z = zVel;
            break;
        }
    }
}
