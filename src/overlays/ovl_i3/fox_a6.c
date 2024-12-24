/*
 * File: fox_a6.c
 * System: Area 6
 * Description: Level: Area 6
 */

#include "global.h"
#include "assets/ast_area_6.h"

void Area6_8018A1B0(Boss* this, s32 arg1);
void Area6_8018A2C4(Boss* this);
void Area6_8018A464(Boss* this, s32 arg1);
void Area6_8018B9BC(Boss* this);

#define A6_HITBOX_COUNT ((s32) (bossA6)->info.hitbox[0])
#define A6_HIT_0(bossA6) ((Hitbox*) ((bossA6)->info.hitbox + 1))
#define A6_HIT_1(bossA6, index) ((Hitbox*) ((f32*) (A6_HIT_0(bossA6) + 1) + 6 * (index)))
#define A6_HIT_1_2(bossA6, index) ((Hitbox*) (A6_HIT_0(bossA6) + 1 + (index)))
#define A6_HIT_4(bossA6, index) ((Hitbox*) ((f32*) (A6_HIT_1(bossA6, 0) + 3) + 6 * (index)))

#define A6_HIT_7_1(bossA6, index) ((TiltHitbox*) ((f32*) (A6_HIT_4(bossA6, 0) + 3) + 10 * (index)))

#define A6_HIT_7_2(bossA6) ((Hitbox*) (A6_HIT_4(bossA6, 0) + 3))
#define A6_HIT_8_2(bossA6, index) ((TiltHitbox*) ((f32*) (A6_HIT_7_2(bossA6) + 1) + 10 * (index)))
#define A6_HIT_11_2(bossA6, index) ((TiltHitbox*) ((f32*) (A6_HIT_8_2(bossA6) + 3) + 10 * (index)))
#define A6_HIT_14_2(bossA6) ((TiltHitbox*) (A6_HIT_11_2(bossA6) + 3))

typedef enum {
    /*  0 */ A6_SWK_0,
    /*  1 */ A6_SWK_1,
    /*  2 */ A6_SWK_2,
    /*  3 */ A6_SWK_3,
    /*  4 */ A6_SWK_4,
    /*  5 */ A6_SWK_5,
    /*  6 */ A6_SWK_6,
    /*  7 */ A6_SWK_7,
    /*  8 */ A6_SWK_8,
    /*  9 */ A6_SWK_9,
    /* 10 */ A6_SWK_10,
    /* 11 */ A6_SWK_11,
    /* 12 */ A6_SWK_12,
    /* 13 */ A6_SWK_13,
    /* 14 */ A6_SWK_14,
    /* 15 */ A6_SWK_15,
    /* 16 */ A6_SWK_16,
    /* 17 */ A6_SWK_17,
    /* 18 */ A6_SWK_18,
    /* 19 */ A6_SWK_19,
    /* 20 */ A6_SWK_20,
    /* 21 */ A6_SWK_21,
    /* 22 */ A6_SWK_22,
    /* 23 */ A6_SWK_23,
    /* 24 */ A6_SWK_24,
    /* 25 */ A6_SWK_25,
    /* 26 */ A6_SWK_26,
    /* 27 */ A6_SWK_27,
    /* 28 */ A6_SWK_28,
    /* 29 */ A6_SWK_29,
    /* 30 */ A6_SWK_30,
    /* 31 */ A6_SWK_31,
    /* 32 */ A6_SWK_32,
    /* 33 */ A6_SWK_33,
    /* 34 */ A6_SWK_34,
    /* 35 */ A6_SWK_35,
    /* 36 */ A6_SWK_36,
    /* 37 */ A6_SWK_37,
    /* 38 */ A6_SWK_38,
    /* 39 */ A6_SWK_39,
    /* 40 */ A6_SWK_MAX,
} A6Gorgonswork;

typedef enum {
    /*  0 */ A6_FWK_0,
    /*  1 */ A6_FWK_1,
    /*  2 */ A6_FWK_2,
    /*  3 */ A6_FWK_3,
    /*  4 */ A6_FWK_4,
    /*  5 */ A6_FWK_5,
    /*  6 */ A6_FWK_6,
    /*  7 */ A6_FWK_7,
    /*  8 */ A6_FWK_8,
    /*  9 */ A6_FWK_9,
    /* 10 */ A6_FWK_10,
    /* 11 */ A6_FWK_11,
    /* 12 */ A6_FWK_12,
    /* 13 */ A6_FWK_13,
    /* 14 */ A6_FWK_14,
    /* 15 */ A6_FWK_15,
    /* 16 */ A6_FWK_16,
    /* 17 */ A6_FWK_17,
    /* 18 */ A6_FWK_18,
    /* 19 */ A6_FWK_19,
    /* 20 */ A6_FWK_20,
    /* 21 */ A6_FWK_21,
    /* 22 */ A6_FWK_22,
    /* 23 */ A6_FWK_23,
    /* 24 */ A6_FWK_24,
    /* 25 */ A6_FWK_25,
    /* 26 */ A6_FWK_26,
    /* 27 */ A6_FWK_27,
    /* 28 */ A6_FWK_28,
    /* 29 */ A6_FWK_29,
    /* 30 */ A6_FWK_30,
    /* 31 */ A6_FWK_31,
    /* 32 */ A6_FWK_32,
    /* 33 */ A6_FWK_33,
    /* 34 */ A6_FWK_34,
    /* 35 */ A6_FWK_35,
    /* 36 */ A6_FWK_36,
    /* 37 */ A6_FWK_37,
    /* 38 */ A6_FWK_38,
    /* 39 */ A6_FWK_39,
    /* 40 */ A6_FWK_40,
    /* 41 */ A6_FWK_41,
    /* 42 */ A6_FWK_42,
    /* 43 */ A6_FWK_43,
    /* 44 */ A6_FWK_44,
    /* 45 */ A6_FWK_45,
    /* 46 */ A6_FWK_46,
    /* 47 */ A6_FWK_47,
    /* 48 */ A6_FWK_48,
    /* 49 */ A6_FWK_49,
    /* 50 */ A6_FWK_MAX,
} A6Gorgonfwork;

typedef enum {
    /*  0 */ A6_VWK_0,
    /*  1 */ A6_VWK_1,
    /*  2 */ A6_VWK_2,
    /*  3 */ A6_VWK_3,
    /*  4 */ A6_VWK_4,
    /*  5 */ A6_VWK_5,
    /*  6 */ A6_VWK_6,
    /*  7 */ A6_VWK_7,
    /*  8 */ A6_VWK_8,
    /*  9 */ A6_VWK_9,
    /* 10 */ A6_VWK_10,
    /* 11 */ A6_VWK_11,
    /* 12 */ A6_VWK_12,
    /* 13 */ A6_VWK_13,
    /* 14 */ A6_VWK_14,
    /* 15 */ A6_VWK_15,
    /* 16 */ A6_VWK_16,
    /* 17 */ A6_VWK_17,
    /* 18 */ A6_VWK_18,
    /* 19 */ A6_VWK_19,
    /* 20 */ A6_VWK_20,
    /* 21 */ A6_VWK_21,
    /* 22 */ A6_VWK_22,
    /* 23 */ A6_VWK_23,
    /* 24 */ A6_VWK_24,
    /* 25 */ A6_VWK_25,
    /* 26 */ A6_VWK_26,
    /* 27 */ A6_VWK_27,
    /* 28 */ A6_VWK_28,
    /* 29 */ A6_VWK_29,
    /* 30 */ A6_VWK_30,
    /* 31 */ A6_VWK_31,
    /* 32 */ A6_VWK_32,
    /* 33 */ A6_VWK_33,
    /* 34 */ A6_VWK_34,
    /* 35 */ A6_VWK_35,
    /* 36 */ A6_VWK_36,
    /* 37 */ A6_VWK_37,
    /* 38 */ A6_VWK_38,
    /* 39 */ A6_VWK_39,
    /* 40 */ A6_VWK_40,
    /* 41 */ A6_VWK_41,
    /* 42 */ A6_VWK_42,
    /* 43 */ A6_VWK_43,
    /* 44 */ A6_VWK_44,
    /* 45 */ A6_VWK_45,
    /* 46 */ A6_VWK_46,
    /* 47 */ A6_VWK_47,
    /* 48 */ A6_VWK_48,
    /* 49 */ A6_VWK_49,
    /* 50 */ A6_VWK_MAX,
} A6Gorgonvwork;

typedef enum {
    /*  0 */ A6_BSS_0,
    /*  1 */ A6_BSS_1,
    /*  2 */ A6_BSS_2_0,
    /*  3 */ A6_BSS_2_1,
    /*  4 */ A6_BSS_2_2,
    /*  5 */ A6_BSS_5,
    /*  6 */ A6_BSS_6,
    /*  7 */ A6_BSS_7,
    /*  8 */ A6_BSS_8,
    /*  9 */ A6_BSS_9,
    /* 10 */ A6_BSS_10,
    /* 11 */ A6_BSS_11,
    /* 12 */ A6_BSS_12_0,
    /* 13 */ A6_BSS_12_1,
    /* 14 */ A6_BSS_12_2,
    /* 15 */ A6_BSS_15,
    /* 16 */ A6_BSS_16,
    /* 17 */ A6_BSS_17,
    /* 18 */ A6_BSS_18,
    /* 19 */ A6_BSS_19,
    /* 20 */ A6_BSS_20,
    /* 21 */ A6_BSS_21,
    /* 22 */ A6_BSS_22,
    /* 23 */ A6_BSS_23,
    /* 24 */ A6_BSS_24,
    /* 25 */ A6_BSS_25,
    /* 26 */ A6_BSS_26,
    /* 27 */ A6_BSS_27,
    /* 28 */ A6_BSS_28,
    /* 29 */ A6_BSS_29,
    /* 30 */ A6_BSS_30,
    /* 31 */ A6_BSS_31,
    /* 32 */ A6_BSS_32,
    /* 33 */ A6_BSS_33,
    /* 34 */ A6_BSS_34,
    /* 35 */ A6_BSS_35,
    /* 36 */ A6_BSS_36,
    /* 37 */ A6_BSS_37,
    /* 38 */ A6_BSS_38,
    /* 39 */ A6_BSS_39,
    /* 40 */ A6_BSS_MAX,
} A6Gorgonbsswork;

typedef struct {
    /* 0x00 */ f32 r[3];
    /* 0x0C */ f32 g[3];
    /* 0x18 */ f32 b[3];
    /* 0x24 */ f32 unk_24;
    /* 0x30 */ f32 unk_28[3];
    /* 0x3C */ f32 unk_34;
} UnkStruct_1C22F0;

typedef struct {
    f32 r, g, b, a;
} Color_RGBAF32;

typedef struct {
    f32 r, g, b;
} Color_RGBF32;

s32 D_i3_801C2250[A6_BSS_MAX];
UnkStruct_1C22F0 D_i3_801C22F0;

f32 D_i3_801BECB0[4][3] = {
    { 255.0f, 0.0f, 0.0f },
    { 255.0f, 63.0f, 63.0f },
    { 255.0f, 127.0f, 127.0f },
    { 255.0f, 255.0f, 255.0f },
};
Vec3f D_i3_801BECE0 = { 497.0f, 287.0f, 169.0f };
Vec3f D_i3_801BECEC = { -497.0f, 287.0f, 169.0f };
Vec3f D_i3_801BECF8 = { -6.0f, -528.0f, 169.0f };
Vec3f D_i3_801BED04 = { 0.0f, 0.0f, 169.0f };
Vec3f D_i3_801BED10 = { 238.0f, 235.0f, 169.0f };
Vec3f D_i3_801BED1C = { 238.0f, -235.0f, 169.0f };
Vec3f D_i3_801BED28 = { -238.0f, 235.0f, 169.0f };
Vec3f D_i3_801BED34 = { -238.0f, -235.0f, 169.0f };
Vec3f D_i3_801BED40[4] = {
    { 0.0f, -300.0f, 300.0f },
    { 500.0f, -300.0f, 300.0f },
    { 270.0f, 45.0f, 135.0f },
    { 0.0f, 135.0f, 235.0f },
};
Vec3f D_i3_801BED70[12] = {
    { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f },
};
Vec3f D_i3_801BEE00[12] = {
    { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f },
};
f32 D_i3_801BEE90[12] = {
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
};
f32 D_i3_801BEEC0[12] = {
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
};
Vec3f D_i3_801BEEF0[12] = {
    { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f },
};
Vec3f D_i3_801BEF80[12] = {
    { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f },
};
f32 D_i3_801BF010[12] = {
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
};
f32 D_i3_801BF040[12] = {
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
};
Vec3f D_i3_801BF070[12] = {
    { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f },
};
Vec3f D_i3_801BF100[12] = {
    { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f },
};
f32 D_i3_801BF190[12] = {
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
};
f32 D_i3_801BF1C0[12] = {
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
};
f32 D_i3_801BF1F0[12] = {
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
};
f32 D_i3_801BF220[12] = {
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
};
f32 D_i3_801BF250[12] = {
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
};
f32 D_i3_801BF280[12] = {
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
};
f32 D_i3_801BF2B0[12] = {
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
};
f32 D_i3_801BF2E0[12] = {
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
};
s32 D_i3_801BF310[3] = { 255, 255, 32 };
s32 D_i3_801BF31C[3] = { 32, 255, 32 };
s32 D_i3_801BF328[3] = { 32, 34, 255 };
f32 D_i3_801BF334[12] = {
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
};
f32 D_i3_801BF364[12] = {
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
};
f32 D_i3_801BF394[12] = {
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
};
f32 D_i3_801BF3C4[12] = {
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
};
f32 D_i3_801BF3F4[12] = {
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
};
f32 D_i3_801BF424[12] = {
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
};
f32 D_i3_801BF454[16] = {
    255.0f, 0.0f, 0.0f, 0.0f, 255.0f, 255.0f, 0.0f, 0.0f, 0.0f, 255.0f, 255.0f, 0.0f, 144.0f, 255.0f, 144.0f, 0.0f,
};
f32 D_i3_801BF494[12] = {
    -90.0f, 30.0f, 26.0f, 22.0f, 18.0f, 11.0f, 8.0f, 5.0f, 3.0f, 2.0f, 1.0f, 0.0f,
};

void Area6_ActorMissileSeekPlayer_Setup(ActorMissileSeekPlayer* this, f32 xPos, f32 yPos, f32 zPos, f32 fwork6,
                                        f32 xRot, f32 yRot, s32 timer0BC, s32 unk0B4) {
    PRINTF("おん\n"); // On
    PRINTF("おふ\n"); // Off
    Actor_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_ACTOR_MISSILE_SEEK_PLAYER;

    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;

    this->obj.rot.x = xRot;
    this->obj.rot.y = yRot;

    this->timer_0BC = timer0BC;
    this->timer_0BE = 20;
    this->eventType = unk0B4;
    this->fwork[5] = fwork6;
    Object_SetInfo(&this->info, this->obj.id);
    Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_BARREL_SHOT);
}

void Area6_ActorMissileSeekPlayer_Spawn(f32 xPos, f32 yPos, f32 zPos, f32 fwork6, f32 xRot, f32 yRot, s32 timer0BC,
                                        s32 unk0B4) {
    s32 i;
    ActorMissileSeekPlayer* missile;

    for (i = 0, missile = &gActors[0]; i < ARRAY_COUNT(gActors); i++, missile++) {
        if (missile->obj.status == OBJ_FREE) {
            Area6_ActorMissileSeekPlayer_Setup(missile, xPos, yPos, zPos, fwork6, xRot, yRot, timer0BC, unk0B4);
            D_i3_801C2250[A6_BSS_11] = i + 1;
            break;
        }
    }
}

void Area6_Effect395_Setup(Effect395* this) {
    Effect_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_EFFECT_395;

    this->obj.pos.x = gBosses[0].obj.pos.x;
    this->obj.pos.y = gBosses[0].obj.pos.y;
    this->obj.pos.z = gBosses[0].obj.pos.z + 250.0f;

    this->state = 8;
    this->scale2 = 1.0f;
    Object_SetInfo(&this->info, this->obj.id);
}

void Area6_Effect395_Spawn(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Area6_Effect395_Setup(&gEffects[i]);
            break;
        }
    }
}

void Area6_A6Gorgon_Init(A6Gorgon* this) {
    Hitbox* hitbox;
    s32 i;

    gBossActive = true;
    gProjectFar = 25000.0f;
    gBossFrameCount = 0;

    this->health = 780;

    this->fwork[A6_FWK_2] = this->fwork[A6_FWK_34] = 2.0f;
    this->fwork[A6_FWK_35] = 1.2f;

    this->swork[A6_SWK_25] = 3;
    this->swork[A6_SWK_15 + 0] = this->swork[A6_SWK_15 + 1] = this->swork[A6_SWK_15 + 2] = 40;
    this->swork[A6_SWK_18 + 0] = this->swork[A6_SWK_18 + 1] = this->swork[A6_SWK_18 + 2] = 3;

    for (i = 0; i < A6_BSS_MAX; i++) {
        D_i3_801C2250[i] = 0;
    }

    D_i3_801C22F0.unk_24 = D_i3_801C22F0.unk_28[0] = D_i3_801C22F0.unk_28[2] = D_i3_801C22F0.unk_28[1] = 255.0f;
    D_i3_801C22F0.unk_34 = 0.0f;

    this->swork[A6_SWK_27 + 0] = this->swork[A6_SWK_27 + 1] = this->swork[A6_SWK_27 + 2] = 0;
    this->swork[A6_SWK_22] = 32;
    this->swork[A6_SWK_23] = 32;
    this->swork[A6_SWK_24] = 255;

    this->fwork[A6_FWK_29] = 255.0f;
    this->fwork[A6_FWK_3] = -1700.0f;
    this->fwork[A6_FWK_5] = 30.0f;
    this->fwork[A6_FWK_32] = 1.0f;

    this->timer_050 = 500;

    A6_HIT_1(this, 0)->z.size = A6_HIT_1(this, 1)->z.size = A6_HIT_1(this, 2)->z.size = 195.0f;
    A6_HIT_1(this, 0)->y.size = A6_HIT_1(this, 1)->y.size = A6_HIT_1(this, 2)->y.size = 147.0f;
    A6_HIT_1(this, 0)->x.size = A6_HIT_1(this, 1)->x.size = A6_HIT_1(this, 2)->x.size = 153.0f;

    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 40);
    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 40);

    AUDIO_PLAY_SFX(NA_SE_EN_SHIELD_ROLL_LEVEL, this->sfxSource, 4);
}

void Area6_A6Gorgon_Update(A6Gorgon* this) {
    s32 i;
    s32 pad;
    s32 var_s0;
    s32 sp128;
    s32 spf124;
    f32 sp120;
    f32 dx_11C;
    f32 dy_118;
    f32 dz_114;
    f32 pitch_110;
    f32 yaw_10C;
    f32 temp2;
    f32 sp104;
    Vec3f spC8[8];
    Vec3f sp98;
    Vec3f sp8C;
    Effect* effect;

    gBossFrameCount++;

    if ((this->state < 6) || ((this->state >= 8) && (this->state < 12))) {
        this->obj.rot.y = RAD_TO_DEG(Math_Atan2F(gPlayer[0].cam.eye.x - this->obj.pos.x,
                                                 gPlayer[0].cam.eye.z - (this->obj.pos.z + gPathProgress)));
        this->obj.rot.x = RAD_TO_DEG(-Math_Atan2F(gPlayer[0].cam.eye.y - this->obj.pos.y,
                                                  sqrtf(SQ(gPlayer[0].cam.eye.z - (this->obj.pos.z + gPathProgress)) +
                                                        SQ(gPlayer[0].cam.eye.x - this->obj.pos.x))));
    }

    Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);
    Matrix_RotateZ(gCalcMatrix, this->obj.rot.z * M_DTOR, MTXF_APPLY);

    if ((this->dmgType != DMG_NONE) && (this->health > 0)) {
        this->dmgType = DMG_NONE;

        if (this->fwork[A6_FWK_0] > 5.0f) {
            if ((this->dmgPart == 0) && (this->swork[A6_SWK_25] == 0) && (this->fwork[A6_FWK_29] < 30.0f)) {
                this->timer_05C = 15;
                this->health -= this->damage;

                if (this->health < 390) {
                    AUDIO_PLAY_SFX(NA_SE_EN_KNOCK_DOWN, this->sfxSource, 4);
                } else {
                    AUDIO_PLAY_SFX(NA_SE_OB_DAMAGE_M, this->sfxSource, 4);
                }

                if (this->health <= 0) {
                    this->health = 0;
                    Boss_AwardBonus(this);
                    Radio_PlayMessage(gMsg_ID_15252, RCID_SLIPPY);

                    gTeamLowHealthMsgTimer = -1;

                    D_bg_8015F984 = (gPathProgress * 0.00004f) + 0.5f;

                    AUDIO_PLAY_SFX(NA_SE_EN_DOWN_IMPACT, this->sfxSource, 4);

                    gShowBossHealth = false;

                    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 40);
                    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 40);

                    this->fwork[A6_FWK_5] = 5.0f;
                    this->fwork[A6_FWK_3] = -20000.0f;
                    this->fwork[A6_FWK_1] = 170.0f;
                    this->vel.z = -20.0f;

                    Matrix_MultVec3f(gCalcMatrix, &D_i3_801BECE0, &spC8[0]);
                    Matrix_MultVec3f(gCalcMatrix, &D_i3_801BECEC, &spC8[1]);
                    Matrix_MultVec3f(gCalcMatrix, &D_i3_801BECF8, &spC8[2]);

                    for (i = 0; i < 3; i++) {
                        func_effect_8007D0E0(spC8[i].x + this->obj.pos.x, spC8[i].y + this->obj.pos.y,
                                             spC8[i].z + this->obj.pos.z, 10.0f);
                    }

                    this->timer_052 = 170;

                    D_i3_801C2250[A6_BSS_2_0] = D_i3_801C2250[A6_BSS_2_1] = D_i3_801C2250[A6_BSS_2_2] =
                        this->swork[A6_SWK_33 + 0] = this->swork[A6_SWK_33 + 1] = this->swork[A6_SWK_33 + 2] = 0;

                    gScreenFlashTimer = 4;

                    this->state = 11;

                    AUDIO_PLAY_SFX(NA_SE_EN_EXPLOSION_L, this->sfxSource, 4);
                    AUDIO_PLAY_SFX(NA_SE_EXPLOSION_DEMO5, this->sfxSource, 4);
                }
            }

            if (((this->dmgPart == 4) || (this->dmgPart == 5) || (this->dmgPart == 6)) &&
                (this->swork[A6_SWK_25] != 0)) {
                Area6_8018B9BC(this);
            }
        }

        if ((this->dmgPart == 1) || (this->dmgPart == 2) || (this->dmgPart == 3)) {
            Area6_8018A2C4(this);
        }
        if (this->dmgPart >= 7) {
            AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
        }
    }

    for (i = 0; i < 3; i++) {
        var_s0 = (this->swork[A6_SWK_15 + i] / 10) - 1;
        if (var_s0 < 0) {
            var_s0 = 0;
        }
        Math_SmoothStepToF(&D_i3_801C22F0.r[i], D_i3_801BECB0[var_s0][0], 1.0f, 10.0f, 0);
        Math_SmoothStepToF(&D_i3_801C22F0.g[i], D_i3_801BECB0[var_s0][1], 1.0f, 10.0f, 0);
        Math_SmoothStepToF(&D_i3_801C22F0.b[i], D_i3_801BECB0[var_s0][2], 1.0f, 10.0f, 0);
    }

    if ((this->swork[A6_SWK_15 + 0] == 0) && (this->swork[A6_SWK_15 + 1] == 0) && (this->swork[A6_SWK_15 + 2] == 0) &&
        (this->fwork[A6_FWK_0] != 0) && !(gGameFrameCount % 2U)) {
        Effect_Effect390_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + 200.0f, this->vel.x, this->vel.y,
                               this->vel.z, 0.3f, 1);
    }

    sp120 = 0.5f;
    if (gBosses[0].swork[A6_SWK_25] == 1) {
        sp120 = 2.0f;
    }

    if (D_i3_801C2250[A6_BSS_10] != 0) {
        D_i3_801C22F0.unk_34 += sp120;
        if (D_i3_801C22F0.unk_34 > 360.0f) {
            D_i3_801C22F0.unk_34 -= 360.0f;
        }
    } else {
        D_i3_801C22F0.unk_34 -= sp120;
        if (D_i3_801C22F0.unk_34 < 0.0f) {
            D_i3_801C22F0.unk_34 += 360.0f;
        }
    }

    if ((this->state >= 3) && (this->state < 5) && (this->fwork[A6_FWK_28] == 0.0f)) {
        Math_SmoothStepToAngle(&this->fwork[A6_FWK_9], this->fwork[A6_FWK_32], 0.05f, 0.02f, 0.00001f);
        Math_SmoothStepToAngle(&this->obj.rot.z, this->fwork[A6_FWK_8], 0.05f, this->fwork[A6_FWK_9], 0.00001f);
        if (this->swork[A6_SWK_25] >= 2) {
            if (!(gGameFrameCount % 64U) && (Rand_ZeroOne() < 0.5f)) {
                this->fwork[A6_FWK_6] = RAND_FLOAT_CENTERED(500.0f) + gPlayer[0].cam.eye.x;
            }
            if (!(gGameFrameCount % 64U) && (Rand_ZeroOne() < 0.5f)) {
                this->fwork[A6_FWK_7] = RAND_FLOAT_CENTERED(500.0f) + gPlayer[0].cam.eye.y;
            }
        } else {
            if (!(gGameFrameCount % 32U) && (Rand_ZeroOne() < 0.7f)) {
                this->fwork[A6_FWK_6] = RAND_FLOAT_CENTERED(1000.0f) + gPlayer[0].cam.eye.x;
                this->fwork[A6_FWK_30] = 0.0f;
            }
            if (!(gGameFrameCount % 32U) && (Rand_ZeroOne() < 0.7f)) {
                this->fwork[A6_FWK_7] = RAND_FLOAT_CENTERED(1000.0f) + gPlayer[0].cam.eye.y;
                this->fwork[A6_FWK_31] = 0.0f;
            }
        }
    }

    if (this->state != 0) {
        Math_SmoothStepToF(&this->fwork[A6_FWK_4], this->fwork[A6_FWK_5], 0.1f, 2.0f, 0.00001f);
        Math_SmoothStepToF(&this->obj.pos.z, gPlayer[0].cam.eye.z - gPathProgress + this->fwork[A6_FWK_3], 0.1f,
                           this->fwork[A6_FWK_4], 0.00001f);
        if (this->state < 5) {
            sp120 = 2.0f;
            if (this->swork[A6_SWK_25] == 1) {
                sp120 = 50.0f;
            }
            Math_SmoothStepToF(&this->fwork[A6_FWK_30], sp120, 0.1f, 1.0f, 0.00001f);
            Math_SmoothStepToF(&this->fwork[A6_FWK_31], sp120, 0.1f, 1.0f, 0.00001f);
            Math_SmoothStepToF(&this->obj.pos.x, this->fwork[A6_FWK_6], 0.2f, this->fwork[A6_FWK_30], 0.00001f);
            Math_SmoothStepToF(&this->obj.pos.y, this->fwork[A6_FWK_7], 0.2f, this->fwork[A6_FWK_31], 0.00001f);
        }
        Math_SmoothStepToAngle(&this->fwork[A6_FWK_0], this->fwork[A6_FWK_1], 0.2f, this->fwork[A6_FWK_2], 0.00001f);
    }

    Math_SmoothStepToF(&this->fwork[A6_FWK_10 + 0], this->fwork[A6_FWK_13 + 0], 0.1f, this->fwork[A6_FWK_16 + 0],
                       0.0001f);
    Math_SmoothStepToF(&this->fwork[A6_FWK_10 + 1], this->fwork[A6_FWK_13 + 1], 0.1f, this->fwork[A6_FWK_16 + 1],
                       0.0001f);
    Math_SmoothStepToF(&this->fwork[A6_FWK_10 + 2], this->fwork[A6_FWK_13 + 2], 0.1f, this->fwork[A6_FWK_16 + 2],
                       0.0001f);
    Math_SmoothStepToF(&this->fwork[A6_FWK_19 + 0], this->fwork[A6_FWK_22 + 0], 0.1f, 10.0f, 0.00001f);
    Math_SmoothStepToF(&this->fwork[A6_FWK_19 + 1], this->fwork[A6_FWK_22 + 1], 0.1f, 10.0f, 0.00001f);
    Math_SmoothStepToF(&this->fwork[A6_FWK_19 + 2], this->fwork[A6_FWK_22 + 2], 0.1f, 10.0f, 0.00001f);

    if (this->state > 10) {
        this->obj.rot.z += this->fwork[A6_FWK_28];
        this->obj.rot.z = Math_ModF(this->obj.rot.z, 360.0f);

        Math_SmoothStepToF(&this->fwork[A6_FWK_28], 5.0f, 0.1f, 0.2f, 0.0001f);

        for (i = 0; i < 10; i++) {
            func_effect_80079618(this->obj.pos.x + RAND_FLOAT_CENTERED(500.0f),
                                 this->obj.pos.y + RAND_FLOAT_CENTERED(500.0f),
                                 this->obj.pos.z + RAND_FLOAT_CENTERED(100.0f), RAND_FLOAT(4.0f) + 1.0f);
        }

        if (this->timer_05C == 0) {
            this->timer_05C = 15;
        }
        if (((gGameFrameCount % 2) == 0)) {
            Matrix_MultVec3f(gCalcMatrix, &D_i3_801BED04, &spC8[3]);
            Matrix_MultVec3f(gCalcMatrix, &D_i3_801BED10, &spC8[4]);
            Matrix_MultVec3f(gCalcMatrix, &D_i3_801BED1C, &spC8[5]);
            Matrix_MultVec3f(gCalcMatrix, &D_i3_801BED28, &spC8[6]);
            Matrix_MultVec3f(gCalcMatrix, &D_i3_801BED34, &spC8[7]);

            for (i = 3; i < 8; i++) {
                var_s0 = RAND_FLOAT_CENTERED(300.0f);
                if (i == 3) {
                    var_s0 = RAND_FLOAT_CENTERED(100.0f);
                }
                func_effect_8007D0E0(this->obj.pos.x + var_s0 + spC8[i].x, this->obj.pos.y + var_s0 + spC8[i].y,
                                     this->obj.pos.z + spC8[i].z, 10.0f);
            }
        }

        if (!(gGameFrameCount % 32U)) {
            Effect_Effect390_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + 300.0f, this->vel.x, this->vel.y,
                                   this->vel.z, 0.5f, 70);
        }
    }

    if ((gGameFrameCount % 16U) == 0) {
        dz_114 = fabsf(this->fwork[A6_FWK_3] / -1700.0f);
        if (dz_114 < 1.0f) {
            dz_114 = 1.0f;
        }
        if (dz_114 > 3.0f) {
            dz_114 = 3.0f;
        }

        for (i = 0; i < 3; i++) {
            sp120 = dz_114;
            if (this->swork[A6_SWK_18 + i] != 0) {
                sp120 = 1.0f;
            }
            A6_HIT_1_2(this, i)->z.size = 195.0f * sp120;
            A6_HIT_1_2(this, i)->y.size = 147.0f * sp120;
            A6_HIT_1_2(this, i)->x.size = 153.0f * sp120;
        }
    }

    switch (this->state) {
        case 0:
            this->info.hitbox[0] = 0;

            dx_11C = gPlayer[0].pos.x - this->obj.pos.x;
            dy_118 = gPlayer[0].pos.y - this->obj.pos.y;
            dz_114 = gPlayer[0].pos.z - 700.0f - this->obj.pos.z;

            sp104 = 10.0f;

            if ((this->timer_050 != 0) && (this->timer_050 < 200)) {
                dx_11C = gPlayer[0].cam.eye.x - this->obj.pos.x;
                dy_118 = gPlayer[0].cam.eye.y - this->obj.pos.y;
                dz_114 = gPlayer[0].cam.eye.z - gPathProgress + this->fwork[A6_FWK_3] - this->obj.pos.z;
                sp104 = 100.0f;
            }

            yaw_10C = Math_Atan2F(dx_11C, dz_114);
            yaw_10C = Math_RadToDeg(yaw_10C);

            pitch_110 = Math_Atan2F(dy_118, sqrtf(SQ(dx_11C) + SQ(dz_114)));
            pitch_110 = Math_RadToDeg(-pitch_110);

            Math_SmoothStepToAngle(&this->rot_078.y, yaw_10C, 1.0f, sp104, 0.00001f);
            Math_SmoothStepToAngle(&this->rot_078.x, pitch_110, 1.0f, sp104, 0.00001f);
            Matrix_RotateY(gCalcMatrix, this->rot_078.y * M_DTOR, MTXF_NEW);
            Matrix_RotateX(gCalcMatrix, this->rot_078.x * M_DTOR, MTXF_APPLY);

            sp98.x = sp98.y = 0.0f;
            sp98.z = 30.0f;

            Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp98, &sp8C);

            this->vel.x = sp8C.x;
            this->vel.y = sp8C.y;

            sp98.x = sp98.y = 0.0f;
            sp98.z = 60.0f;

            Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp98, &sp8C);

            this->vel.z = sp8C.z;
            this->fwork[A6_FWK_33] += 30.0f;

            if (this->timer_050 == 0) {
                Math_SmoothStepToF(&D_i3_801C22F0.unk_24, 0.0f, 0.1f, 1.0f, 0);
                if (D_i3_801C22F0.unk_24 < 1.0f) {
                    D_i3_801C22F0.unk_24 = 0.0f;

                    Audio_KillSfxBySource(this->sfxSource);

                    AUDIO_PLAY_SFX(NA_SE_EN_SHIELD_ROLL_STOP, this->sfxSource, 4);

                    this->timer_050 = 20;
                    this->obj.pos.z = gPlayer[0].cam.eye.z - gPathProgress + this->fwork[A6_FWK_3];
                    this->fwork[A6_FWK_6] = this->obj.pos.x = gPlayer[0].cam.eye.x;
                    this->fwork[A6_FWK_7] = this->obj.pos.y = gPlayer[0].cam.eye.y;
                    this->state = 2;
                    this->vel.x = 0.0f;
                    this->vel.y = 0.0f;
                    this->vel.z = -40.0f;

                    AUDIO_PLAY_SFX(NA_SE_EN_WARP_OUT, this->sfxSource, 4);
                }
            }
            break;

        case 1:
            Math_SmoothStepToF(D_ctx_801779A8, 10.0f, 1.0f, 5.0f, 0.0f);
            this->info.hitbox[0] = 0;
            Math_SmoothStepToAngle(&this->obj.rot.z, 0.0f, 1.0f, 10.0f, 0.0001f);

            if (this->obj.rot.z < 1.0f) {
                if (D_i3_801C2250[A6_BSS_27] == 0) {
                    AUDIO_PLAY_SFX(NA_SE_EN_WARP_IN, this->sfxSource, 4);
                    D_i3_801C2250[A6_BSS_27] = 1;
                }
                this->obj.rot.z = 0.0f;
                Math_SmoothStepToF(&D_i3_801C22F0.unk_24, 0.0f, 0.1f, 5.0f, 0.0f);
                Math_SmoothStepToF(&this->fwork[A6_FWK_34], 2.0f, 0.1f, 0.1f, 0.0f);
                Math_SmoothStepToF(&this->fwork[A6_FWK_35], 1.2f, 0.1f, 0.1f, 0.0f);

                if (D_i3_801C22F0.unk_24 < 1.0f) {
                    this->fwork[A6_FWK_6] = RAND_FLOAT_CENTERED(1000.0f) + gPlayer[0].cam.eye.x;
                    this->fwork[A6_FWK_7] = RAND_FLOAT_CENTERED(1000.0f) + gPlayer[0].cam.eye.y;
                    this->fwork[A6_FWK_3] = -3700.0f + RAND_FLOAT_CENTERED(3000.0f);
                    this->fwork[A6_FWK_34] = 2.0f;
                    this->fwork[A6_FWK_35] = 1.2f;

                    if ((this->swork[A6_SWK_37] == 0) && (this->swork[A6_SWK_33 + 0] == 0) &&
                        (this->swork[A6_SWK_33 + 1] == 0) && (this->swork[A6_SWK_33 + 2] == 0) &&
                        (this->swork[A6_SWK_27 + 0] == 0) && (this->swork[A6_SWK_27 + 1] == 0) &&
                        (this->swork[A6_SWK_27 + 2] == 0)) {
                        this->swork[A6_SWK_37] = 1;
                    }

                    if (this->swork[A6_SWK_37] != 0) {
                        this->swork[A6_SWK_18 + 0] = this->swork[A6_SWK_18 + 1] = this->swork[A6_SWK_18 + 2] = 3;
                        this->fwork[A6_FWK_3] = -1700.0f;
                        if ((this->swork[A6_SWK_25] != 1) && (D_i3_801C2250[A6_BSS_0] != 2)) {
                            this->fwork[A6_FWK_3] = RAND_FLOAT_CENTERED(1000.0f) + -3700.0f;
                        }
                        this->obj.pos.z = gPlayer[0].cam.eye.z - gPathProgress + this->fwork[A6_FWK_3];
                        this->fwork[A6_FWK_6] = this->obj.pos.x = gPlayer[0].cam.eye.x;
                        this->fwork[A6_FWK_7] = this->obj.pos.y = gPlayer[0].cam.eye.y;
                    }

                    D_i3_801C22F0.unk_24 = 0.0f;

                    this->timer_050 = 50;
                    this->state = 2;

                    D_i3_801C2250[A6_BSS_8] = 0;

                    AUDIO_PLAY_SFX(NA_SE_EN_WARP_OUT, this->sfxSource, 4);
                }
            }
            break;

        case 2:
            Math_SmoothStepToF(D_ctx_801779A8, 10.0f, 1.0f, 5.0f, 0.0f);
            if (this->timer_050 == 10) {
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
                gFillScreenAlpha = gFillScreenAlphaTarget = 255;
                gFillScreenAlphaTarget = 0;
                gFillScreenAlphaStep = 25;
                gCameraShake = 50;
            }

            if (this->timer_050 == 0) {
                if (D_i3_801C2250[A6_BSS_8] == 0) {
                    D_i3_801C2250[A6_BSS_8] = 1;
                    gFillScreenRed = gFillScreenGreen = gFillScreenBlue = gFillScreenAlpha = 0;
                }

                Math_SmoothStepToF(&D_i3_801C22F0.unk_24, 255.0f, 0.1f, 10.0f, 0.0f);
                Math_SmoothStepToF(&this->fwork[A6_FWK_34], 1.0f, 0.1f, 0.1f, 0.0f);
                Math_SmoothStepToF(&this->fwork[A6_FWK_35], 1.0f, 0.1f, 0.1f, 0.0f);

                if (D_i3_801C22F0.unk_24 > 254.0f) {
                    D_i3_801C22F0.unk_24 = 255.0f;
                    this->info.hitbox[0] = 10;
                    this->fwork[A6_FWK_34] = this->fwork[A6_FWK_35] = 1.0f;

                    switch (this->swork[A6_SWK_38]) {
                        case 0:
                            this->timer_050 = 100;
                            break;
                        case 1:
                            this->timer_050 = 1399;
                            break;
                    }

                    this->swork[A6_SWK_38] = 0;
                    D_i3_801C2250[A6_BSS_28] = 1;

                    this->state = 4;

                    if (this->swork[A6_SWK_37] != 0) {
                        this->timer_050 = 30;
                        this->swork[A6_SWK_37] = 0;
                        this->fwork[A6_FWK_8] = this->fwork[A6_FWK_9] = 0.0f;
                        if (this->swork[A6_SWK_36] < 2) {
                            this->swork[A6_SWK_36]++;
                        }
                        this->state = 3;
                    }

                    if (D_i3_801C2250[A6_BSS_6] != 0) {
                        if (D_i3_801C2250[A6_BSS_0] != 2) {
                            D_i3_801C2250[A6_BSS_0] = 1;
                        } else {
                            D_i3_801C2250[A6_BSS_0] = 0;
                        }
                    }

                    if ((D_i3_801C2250[A6_BSS_6] == 0) || (D_i3_801C2250[A6_BSS_0] == 0)) {
                        this->fwork[A6_FWK_1] = 90.0f;
                        this->fwork[A6_FWK_2] = 2.0f;
                        AUDIO_PLAY_SFX(NA_SE_EN_COVER_OPEN, this->sfxSource, 4);
                        this->info.hitbox = SEGMENTED_TO_VIRTUAL(D_A6_6028578);
                        D_i3_801C2250[A6_BSS_7] = 0;
                    }
                }
            }
            break;

        case 3:
            if (this->timer_050 == 1) {
                Audio_KillSfxBySource(this->sfxSource);
                if (D_i3_801C2250[A6_BSS_7] == 0) {
                    AUDIO_PLAY_SFX(NA_SE_EN_ENERGY_BALL, this->sfxSource, 4);
                    D_i3_801C2250[A6_BSS_7] = 1;
                }
            }

            if (D_i3_801C2250[A6_BSS_0] != 0) {
                if (this->swork[A6_SWK_25] == 1) {
                    this->timer_052 = 30;
                    this->state = 5;
                    this->fwork[A6_FWK_1] = 90.0f;
                    this->fwork[A6_FWK_2] = 2.0f;
                    this->fwork[A6_FWK_37] = 300.0f;
                } else {
                    this->timer_052 = 30;
                    this->state = 8;
                }
            } else {
                if ((this->swork[A6_SWK_36] == 3) && (D_i3_801C2250[A6_BSS_29] == 0)) {
                    Radio_PlayMessage(gMsg_ID_7084, RCID_PEPPY);
                    this->swork[A6_SWK_36] = 4;
                    D_i3_801C2250[A6_BSS_29]++;
                    D_i3_801C2250[A6_BSS_29] &= 1;
                }

                if ((this->swork[A6_SWK_30 + 0] != 0) && (this->swork[A6_SWK_30 + 1] != 0) &&
                    (this->swork[A6_SWK_30 + 2] != 0)) {
                    this->timer_050 = 1500;
                    this->fwork[A6_FWK_1] = 0.0f;
                    D_i3_801C2250[A6_BSS_28] = 0;
                    this->state = 4;
                    this->fwork[A6_FWK_2] = 1.0f;
                    this->info.hitbox = SEGMENTED_TO_VIRTUAL(aA6GorgonHitbox);
                    D_i3_801C2250[A6_BSS_6] = 1;
                    Audio_KillSfxBySource(this->sfxSource);
                    AUDIO_PLAY_SFX(NA_SE_EN_COVER_CLOSE, this->sfxSource, 4);
                    this->swork[A6_SWK_30 + 0] = this->swork[A6_SWK_30 + 1] = this->swork[A6_SWK_30 + 2] = 0;
                } else if (this->swork[A6_SWK_30 + 0] == 0) {
                    Area6_8018A1B0(this, 0);
                } else if (this->swork[A6_SWK_30 + 1] == 0) {
                    Area6_8018A1B0(this, 1);
                } else if (this->swork[A6_SWK_30 + 2] == 0) {
                    Area6_8018A1B0(this, 2);
                }
            }
            break;

        case 4:
            if (this->timer_050 == 1400) {
                this->swork[A6_SWK_15 + 0] = this->swork[A6_SWK_15 + 1] = this->swork[A6_SWK_15 + 2] = 40;
                if (this->swork[A6_SWK_25] == 0) {
                    this->swork[A6_SWK_25] = 1;
                }
                this->fwork[A6_FWK_3] = RAND_FLOAT_CENTERED(1000.0f) + -3700.0f;
                if (D_i3_801C2250[A6_BSS_28] == 0) {
                    AUDIO_PLAY_SFX(NA_SE_EN_COVER_MOVE_STOP, this->sfxSource, 4);
                }
            }

            Math_SmoothStepToF(&this->fwork[A6_FWK_29], 255.0f, 1.0f, 10.0f, 0.0001f);

            if ((this->swork[A6_SWK_36] == 2) && (this->fwork[A6_FWK_0] == 0.0f) && (D_i3_801C2250[A6_BSS_30] == 0)) {
                Radio_PlayMessage(gMsg_ID_7083, RCID_PEPPY);
                this->swork[A6_SWK_36] = 3;
                D_i3_801C2250[A6_BSS_30]++;
                D_i3_801C2250[A6_BSS_30] &= 1;
            }

            if (!(gGameFrameCount % 64U)) {
                this->fwork[A6_FWK_8] = RAND_FLOAT(360.0f);
                this->fwork[A6_FWK_9] = 0.0f;
            }

            if ((this->timer_050 == 0) || ((this->swork[A6_SWK_33 + 0] == 0) && (this->swork[A6_SWK_33 + 1] == 0) &&
                                           (this->swork[A6_SWK_33 + 2] == 0) && (this->swork[A6_SWK_27 + 0] == 0) &&
                                           (this->swork[A6_SWK_27 + 1] == 0) && (this->swork[A6_SWK_27 + 2] == 0))) {
                this->swork[A6_SWK_37] = 1;

                if (D_i3_801C2250[A6_BSS_6] != 0) {
                    this->state = 1;
                    D_i3_801C2250[A6_BSS_27] = 0;
                } else {
                    this->fwork[A6_FWK_1] = 90.0f;
                    this->timer_050 = 30;
                    this->fwork[A6_FWK_8] = this->fwork[A6_FWK_9] = 0;
                    this->fwork[A6_FWK_2] = 2.0f;

                    AUDIO_PLAY_SFX(NA_SE_EN_COVER_OPEN, this->sfxSource, 4);

                    this->info.hitbox = SEGMENTED_TO_VIRTUAL(D_A6_6028578);

                    D_i3_801C2250[A6_BSS_7] = this->swork[A6_SWK_37] = 0;

                    this->state = 3;

                    if (D_i3_801C2250[A6_BSS_6] == 0) {
                        AUDIO_PLAY_BGM(NA_BGM_BOSS_A6);
                    }
                }
            } else if (this->swork[A6_SWK_38] != 0) {
                this->timer_052 = 30;
                this->state = 9;
                this->fwork[A6_FWK_28] = 0.0f;
                D_i3_801C2250[A6_BSS_24] = 0;
                D_i3_801C2250[A6_BSS_27] = 0;
                this->timer_050 = 0;
                this->timer_054 = 0;
                D_i3_801C2250[A6_BSS_34] = 1;
            }
            break;

        case 5:
            if (this->timer_050 == 1) {
                Area6_Effect395_Spawn();
                AUDIO_PLAY_SFX(NA_SE_EN_A6BOSS_CHARGE, this->sfxSource, 4);
                D_i3_801C2250[A6_BSS_33] = 120;
            }

            if (D_i3_801C2250[A6_BSS_33] != 0) {
                D_i3_801C2250[A6_BSS_33]--;
            }

            if (D_i3_801C2250[A6_BSS_33] == 15) {
                if (D_i3_801C2250[A6_BSS_32] == 0) {
                    if (gTeamShields[TEAM_ID_FALCO] > 0) {
                        Radio_PlayMessage(gMsg_ID_20315, RCID_FALCO);
                    } else if (gTeamShields[TEAM_ID_SLIPPY] > 0) {
                        Radio_PlayMessage(gMsg_ID_20316, RCID_SLIPPY);
                    } else if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                        Radio_PlayMessage(gMsg_ID_20317, RCID_PEPPY);
                    }
                }
                D_i3_801C2250[A6_BSS_32]++;
                D_i3_801C2250[A6_BSS_32] &= 1;
            }
            break;

        case 6:
            this->obj.pos.z -= this->fwork[A6_FWK_37];

            Math_SmoothStepToF(&this->fwork[A6_FWK_37], 0.0f, 1.0f, 10.0f, 0.00001f);
            Math_SmoothStepToF(&this->fwork[A6_FWK_3], -6000.0f, 10.0f, 100.0f, 0.00001f);

            var_s0 = D_i3_801C2250[A6_BSS_9] * 4;

            Math_SmoothStepToF(&D_i3_801C22F0.unk_28[0], D_i3_801BF454[var_s0], 0.5f, 100.0f, 0.00001f);
            Math_SmoothStepToF(&D_i3_801C22F0.unk_28[2], D_i3_801BF454[var_s0 + 1], 0.5f, 100.0f, 0.00001f);
            Math_SmoothStepToF(&D_i3_801C22F0.unk_28[1], D_i3_801BF454[var_s0 + 2], 0.5f, 100.0f, 0.00001f);

            if (((gGameFrameCount % 16) == 0)) {
                D_i3_801C2250[A6_BSS_9]++;
                D_i3_801C2250[A6_BSS_9] &= 3;
            }

            if (this->timer_050 == 0) {
                this->fwork[A6_FWK_1] = 0.0f;
                this->state = 7;
            }
            break;

        case 7:
            effect = &gEffects[this->swork[A6_SWK_39]];

            Math_SmoothStepToF(&D_i3_801C22F0.unk_28[0], 255.0f, 1.0f, 100.0f, 0.00001f);
            Math_SmoothStepToF(&D_i3_801C22F0.unk_28[2], 255.0f, 1.0f, 100.0f, 0.00001f);
            Math_SmoothStepToF(&D_i3_801C22F0.unk_28[1], 255.0f, 1.0f, 100.0f, 0.00001f);

            if (this->fwork[A6_FWK_0] < 10.0f) {
                effect->unk_60.y = 5.0f - ((10.0f - this->fwork[A6_FWK_0]) * 0.3f);
                effect->unk_60.x = 5.0f - ((10.0f - this->fwork[A6_FWK_0]) * 0.3f);
            }

            if (this->fwork[A6_FWK_0] < 1.0f) {
                Math_SmoothStepToF(&effect->unk_60.x, 0.0f, 0.1f, 1.0f, 0.00001f);
                Math_SmoothStepToF(&effect->unk_60.y, 0.0f, 0.1f, 1.0f, 0.00001f);
                Math_SmoothStepToF(&effect->unk_60.z, 0.0f, 1.0f, 2.0f, 0.00001f);

                if (effect->unk_60.z < 0.2f) {
                    D_i3_801C2250[A6_BSS_0] = 2;
                    this->swork[A6_SWK_37] = 1;
                    this->timer_050 = 20;
                    D_i3_801C22F0.unk_28[0] = D_i3_801C22F0.unk_28[2] = D_i3_801C22F0.unk_28[1] = 255.0f;
                    this->state = 1;
                    D_i3_801C2250[A6_BSS_27] = 0;
                    Object_Kill(&effect->obj, effect->sfxSource);
                }
            }
            break;

        case 8:
            if (this->timer_052 == 0) {
                D_i3_801C2250[A6_BSS_24] = 0;
                this->timer_052 = 300;
                this->timer_054 = 0;
                this->state = 9;
                AUDIO_PLAY_SFX(NA_SE_EN_SHIELD_ROLL_LEVEL, this->sfxSource, 4);
            }
            break;

        case 9:
            if (this->timer_052 == 0) {
                Audio_KillSfxBySource(this->sfxSource);
                AUDIO_PLAY_SFX(NA_SE_EN_SHIELD_ROLL_STOP, this->sfxSource, 4);
                this->timer_054 = 0;
                this->state = 10;
            } else {
                if (D_i3_801C2250[A6_BSS_34] == 0) {
                    this->obj.rot.z += this->fwork[A6_FWK_28];
                    this->obj.rot.z = Math_ModF(this->obj.rot.z, 360.0f);
                    Math_SmoothStepToF(&this->fwork[A6_FWK_28], 20.0f, 0.1f, 0.5f, 0.0001f);
                }
                if (this->timer_054 == 0) {
                    this->timer_054 = 10;

                    if (D_i3_801C2250[A6_BSS_34] == 0) {
                        this->timer_054 = 30;
                    }

                    sp128 = 6;
                    if (this->swork[A6_SWK_25] == 2) {
                        sp128 = 12;
                    }

                    for (var_s0 = 0; var_s0 < sp128; var_s0++) {
                        Matrix_RotateZ(gCalcMatrix, (360.0f / sp128) * M_DTOR, MTXF_APPLY);

                        sp98.x = 0.0f;
                        sp98.y = 400.0f;
                        sp98.z = 0.0f;

                        Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp98, &sp8C);

                        yaw_10C = Math_Atan2F(sp8C.x, sp8C.z);
                        yaw_10C = Math_RadToDeg(yaw_10C);

                        pitch_110 = Math_Atan2F(sp8C.y, sqrtf(SQ(sp8C.x) + SQ(sp8C.z)));
                        pitch_110 = Math_RadToDeg(-pitch_110);

                        spf124 = D_i3_801C2250[A6_BSS_12_0 + var_s0] - 1;
                        if (spf124 < 0) {
                            spf124 = 0;
                        }

                        if ((gActors[spf124].obj.status == OBJ_FREE) ||
                            (gActors[spf124].obj.id != OBJ_ACTOR_MISSILE_SEEK_PLAYER) ||
                            (D_i3_801C2250[A6_BSS_24] == 0)) {
                            D_i3_801C2250[A6_BSS_12_0 + var_s0] = 0;

                            spf124 = 0;

                            if (this->swork[A6_SWK_25] == 1) {
                                spf124 = 1;
                            }

                            Area6_ActorMissileSeekPlayer_Spawn(this->obj.pos.x + sp8C.x, this->obj.pos.y + sp8C.y,
                                                               this->obj.pos.z + sp8C.z, 25.0f, pitch_110, yaw_10C, 10,
                                                               spf124);

                            D_i3_801C2250[A6_BSS_12_0 + var_s0] = D_i3_801C2250[A6_BSS_11];
                        }
                    }
                    D_i3_801C2250[A6_BSS_24] = 1;
                }
            }
            break;

        case 10:
            if (D_i3_801C2250[A6_BSS_34] == 0) {
                this->obj.rot.z += this->fwork[A6_FWK_28];
                this->obj.rot.z = Math_ModF(this->obj.rot.z, 360.0f);
                Math_SmoothStepToF(&this->fwork[A6_FWK_28], 0.0f, 0.1f, 0.5f, 0.0001f);
            }

            if (this->fwork[A6_FWK_28] <= 0.1f) {
                if (D_i3_801C2250[A6_BSS_34] == 0) {
                    this->fwork[A6_FWK_28] = 0.0f;
                    D_i3_801C2250[A6_BSS_0] = 2;
                    this->swork[A6_SWK_37] = 1;
                }
                this->timer_050 = 20;
                D_i3_801C2250[A6_BSS_27] = 0;
                D_i3_801C2250[A6_BSS_34] = 0;
                this->state = 1;
            }
            break;

        case 11:
            if ((this->timer_052 == 160) &&
                ((gPlayer[0].state == PLAYERSTATE_ACTIVE) || (gPlayer[0].state == PLAYERSTATE_U_TURN))) {
                gPlayer[0].state = PLAYERSTATE_LEVEL_COMPLETE;
                gPlayer[0].csState = 0;
            }

            if (this->timer_052 < 50) {
                D_ctx_801779A8[0] = 50.0f;
            } else {
                D_ctx_801779A8[0] = 20.0f;
            }

            if (this->timer_052 == 0) {
                gShowBossHealth = false;
                Object_Kill(&this->obj, this->sfxSource);
            }
            break;
    }

    Area6_8018A464(this, 0);
    Area6_8018A464(this, 1);
    Area6_8018A464(this, 2);

    for (i = 0; i < 5; i++) {
        if (!(gGameFrameCount % 4U)) {
            D_i3_801BF280[i] = RAND_FLOAT_CENTERED(10.0f);
            D_i3_801BF2B0[i] = RAND_FLOAT_CENTERED(10.0f);
            D_i3_801BF2E0[i] = RAND_FLOAT_CENTERED(10.0f);
        }
        Math_SmoothStepToF(&D_i3_801BF1F0[i], D_i3_801BF280[i], 1.0f, 5.0f, 0.001f);
        Math_SmoothStepToF(&D_i3_801BF220[i], D_i3_801BF2B0[i], 1.0f, 5.0f, 0.001f);
        Math_SmoothStepToF(&D_i3_801BF250[i], D_i3_801BF2E0[i], 1.0f, 5.0f, 0.001f);
    }

    A6_HIT_4(this, 0)->z.offset = this->vwork[A6_VWK_4].z;
    A6_HIT_4(this, 0)->y.offset = this->vwork[A6_VWK_4].y;
    A6_HIT_4(this, 0)->x.offset = this->vwork[A6_VWK_4].x;
    A6_HIT_4(this, 1)->z.offset = this->vwork[A6_VWK_5].z;
    A6_HIT_4(this, 1)->y.offset = this->vwork[A6_VWK_5].y;
    A6_HIT_4(this, 1)->x.offset = this->vwork[A6_VWK_5].x;
    A6_HIT_4(this, 2)->z.offset = this->vwork[A6_VWK_6].z;
    A6_HIT_4(this, 2)->y.offset = this->vwork[A6_VWK_6].y;
    A6_HIT_4(this, 2)->x.offset = this->vwork[A6_VWK_6].x;

    if (gBossFrameCount == 600) {
        Radio_PlayMessage(gMsg_ID_2225, RCID_SLIPPY);
    }
    if (gBossFrameCount == 756) {
        gShowBossHealth = true;
    }
    if (gBossFrameCount > 756) {
        gBossHealthBar = (this->health / 780.0f) * 255.0f;
    }

    for (i = 0; i < 15; i++) {
        if (this->swork[A6_SWK_0 + i] != 0) {
            this->swork[A6_SWK_0 + i]--;
        }
    }

    if (this->fwork[A6_FWK_0] > 20.0f) {
        for (i = 0; i < 3; i++) {
            if (this->swork[A6_SWK_0 + i] == 0) {
                this->swork[A6_SWK_0 + i] = 5;
            }
        }
    }

    if (D_i3_801C2250[A6_BSS_5] != 0) {
        D_i3_801C2250[A6_BSS_5]--;
    }
    if (D_i3_801C2250[A6_BSS_25] != 0) {
        D_i3_801C2250[A6_BSS_25]--;
    }
}

void Area6_8018A1B0(A6Gorgon* this, s32 arg1) {
    switch (D_i3_801C2250[A6_BSS_2_0 + arg1]) {
        case 0:
            this->swork[A6_SWK_27 + arg1] = 12;
            D_i3_801C2250[A6_BSS_2_0 + arg1] = 1;
            break;

        case 1:
            this->fwork[A6_FWK_13 + arg1] = 120.0f;
            if (((this->swork[A6_SWK_33 + arg1] == 0) && (D_i3_801C2250[A6_BSS_6] != 0) &&
                 ((this->swork[A6_SWK_15 + 0] != 0) || (this->swork[A6_SWK_15 + 1] != 0) ||
                  (this->swork[A6_SWK_15 + 2] != 0))) ||
                (this->swork[A6_SWK_25] == 0)) {
                this->fwork[A6_FWK_16 + arg1] = 1.0f;
            } else {
                this->fwork[A6_FWK_16 + arg1] = 60.0f;
            }

            if (this->fwork[A6_FWK_10 + arg1] >= 119.0f) {
                this->fwork[A6_FWK_10 + arg1] = 120.0f;
                this->swork[A6_SWK_33 + arg1] = 30;
                this->fwork[A6_FWK_16 + arg1] = 60.0f;
                D_i3_801C2250[A6_BSS_2_0 + arg1] = 0;
                this->swork[A6_SWK_6 + arg1] = 0;
                this->swork[A6_SWK_9 + arg1] = 0;
                this->swork[A6_SWK_30 + arg1] = 1;
                this->swork[A6_SWK_18 + arg1] = 0;
            }
            break;
    }
}

void Area6_8018A2C4(A6Gorgon* this) {
    s32 i;
    Vec3f effectPos;

    for (i = 0; i < 3; i++) {
        if ((this->dmgPart == i + 1) && (this->state == 4) && (this->fwork[A6_FWK_0] < 20.0f)) {
            if ((this->swork[A6_SWK_18 + i] != 1) && (this->swork[A6_SWK_18 + i] != 3)) {
                this->swork[A6_SWK_0 + i] = 15;
                this->swork[A6_SWK_3 + i] = 40;
                this->swork[A6_SWK_33 + i] -= this->damage;

                if (i == 0) {
                    effectPos.x = D_i3_801BF334[0];
                    effectPos.y = D_i3_801BF3C4[0];
                    effectPos.z = this->obj.pos.z;
                    Effect_SpawnTimedSfxAtPos(&effectPos, NA_SE_OB_DAMAGE_M);
                }

                if (i == 1) {
                    effectPos.x = D_i3_801BF364[0];
                    effectPos.y = D_i3_801BF3F4[0];
                    effectPos.z = this->obj.pos.z;
                    Effect_SpawnTimedSfxAtPos(&effectPos, NA_SE_OB_DAMAGE_M);
                }

                if (i == 2) {
                    effectPos.x = D_i3_801BF394[0];
                    effectPos.y = D_i3_801BF424[0];
                    effectPos.z = this->obj.pos.z;
                    Effect_SpawnTimedSfxAtPos(&effectPos, NA_SE_OB_DAMAGE_M);
                }

                if (this->swork[A6_SWK_33 + i] < 0) {
                    this->swork[A6_SWK_33 + i] = 0;
                }
            }
        }
    }
}

void Area6_8018A464(A6Gorgon* this, s32 arg1) {
    s32 i;
    s32 j;
    f32 var_fs0;
    Vec3f effectPos;
    s32 pad[7];

    A6_HIT_1(this, arg1)->z.offset = this->vwork[A6_VWK_1 + arg1].z;
    A6_HIT_1(this, arg1)->y.offset = this->vwork[A6_VWK_1 + arg1].y;
    A6_HIT_1(this, arg1)->x.offset = this->vwork[A6_VWK_1 + arg1].x;

    if ((D_i3_801C2250[A6_BSS_5] != 0) && (this->timer_056 != 0)) {
        this->timer_050 = 202;
        this->timer_056 = 0;
    }

    switch (this->swork[A6_SWK_18 + arg1]) {
        case 0:
            Math_SmoothStepToF(&this->fwork[A6_FWK_25 + arg1], -90.0f, 0.05f, 2.0f, 0.00001f);
            Math_SmoothStepToF(&this->fwork[A6_FWK_22 + arg1], 0.0f, 0.1f, 10.0f, 0.00001f);

            switch (arg1) {
                case 0:
                    if (this->swork[A6_SWK_33] != 0) {
                        for (i = 1; i < 12; i++) {
                            D_i3_801BEE90[i] = 3.0f;
                            D_i3_801BEEC0[i] = 3.0f;

                            if ((this->swork[A6_SWK_6] == 0) && (this->state != 3)) {
                                this->swork[A6_SWK_6] = 20;

                                D_i3_801BEE00[0].y = RAND_FLOAT_CENTERED(720.0f);
                                if (D_i3_801BEE00[0].y < -20.0f) {
                                    D_i3_801BEE00[0].y = -20.0f;
                                }
                                if (D_i3_801BEE00[0].y > 20.0f) {
                                    D_i3_801BEE00[0].y = 20.0f;
                                }
                                D_i3_801BF3C4[0] = D_i3_801BEE00[0].y;
                            } else if ((this->swork[A6_SWK_6] & 3) == 0) {
                                D_i3_801BF3C4[i] = D_i3_801BEE00[i].y;
                                D_i3_801BEE00[i].y = D_i3_801BF3C4[i - 1];
                            }

                            if (this->swork[A6_SWK_9] == 0) {
                                if ((D_i3_801BEE00[0].y < -20.0f) || (D_i3_801BEE00[0].y > 20.0f)) {
                                    for (i = 0; i < 12; i++) {
                                        Math_SmoothStepToF(&D_i3_801BEE00[i].x, 0.0f, 0.5f, 100.0f, 0.001f);
                                    }
                                } else {
                                    this->swork[A6_SWK_9] = 30;
                                    D_i3_801BEE00[0].x = RAND_FLOAT_CENTERED(30.0f);
                                }
                                D_i3_801BF334[0] = D_i3_801BEE00[0].x;
                            } else if ((this->swork[A6_SWK_9] % 8) == 0) {
                                D_i3_801BF334[i] = D_i3_801BEE00[i].x;
                                D_i3_801BEE00[i].x = D_i3_801BF334[i - 1];
                            }
                        }

                        for (i = 0; i < 12; i++) {
                            Math_SmoothStepToF(&D_i3_801BED70[i].y, D_i3_801BEE00[i].y, 0.05f, D_i3_801BEEC0[i],
                                               0.001f);
                            Math_SmoothStepToF(&D_i3_801BED70[i].x, D_i3_801BEE00[i].x, 0.05f, D_i3_801BEE90[i],
                                               0.001f);
                            Math_SmoothStepToF(&D_i3_801BEE90[i], 1.0f, 0.03f, 0.05f, 0.001f);
                            Math_SmoothStepToF(&D_i3_801BEEC0[i], 1.0f, 0.03f, 0.05f, 0.001f);
                        }
                    }
                    break;

                case 1:
                    if (this->swork[A6_SWK_34] != 0) {
                        for (i = 1; i < 12; i++) {
                            D_i3_801BF010[i] = 3.0f;
                            D_i3_801BF040[i] = 3.0f;

                            if (this->swork[A6_SWK_7] == 0) {
                                this->swork[A6_SWK_7] = 20;

                                D_i3_801BEF80[0].y = RAND_FLOAT_CENTERED(720.0f);
                                if (D_i3_801BEF80[0].y < -20.0f) {
                                    D_i3_801BEF80[0].y = -20.0f;
                                }
                                if (D_i3_801BEF80[0].y > 20.0f) {
                                    D_i3_801BEF80[0].y = 20.0f;
                                }
                                D_i3_801BF3F4[0] = D_i3_801BEF80[0].y;
                            } else if ((this->swork[A6_SWK_7] & 3) == 0) {
                                D_i3_801BF3F4[i] = D_i3_801BEF80[i].y;
                                D_i3_801BEF80[i].y = D_i3_801BF3F4[i - 1];
                            }

                            if (this->swork[A6_SWK_10] == 0) {
                                if ((D_i3_801BEF80[0].y < -20.0f) || (D_i3_801BEF80[0].y > 20.0f)) {
                                    for (i = 0; i < 12; i++) {
                                        Math_SmoothStepToF(&D_i3_801BEF80[i].x, 0.0f, 0.5f, 50.0f, 0.001f);
                                    }
                                } else {
                                    this->swork[A6_SWK_10] = 30;
                                    D_i3_801BEF80[0].x = RAND_FLOAT_CENTERED(30.0f);
                                }
                                D_i3_801BF364[0] = D_i3_801BEF80[0].x;
                            } else if ((this->swork[A6_SWK_10] % 8) == 0) {
                                D_i3_801BF364[i] = D_i3_801BEF80[i].x;
                                D_i3_801BEF80[i].x = D_i3_801BF364[i - 1];
                            }
                        }

                        for (i = 0; i < 12; i++) {
                            Math_SmoothStepToF(&D_i3_801BEEF0[i].y, D_i3_801BEF80[i].y, 0.05f, D_i3_801BF040[i],
                                               0.001f);
                            Math_SmoothStepToF(&D_i3_801BEEF0[i].x, D_i3_801BEF80[i].x, 0.05f, D_i3_801BF010[i],
                                               0.001f);
                            Math_SmoothStepToF(&D_i3_801BF010[i], 1.0f, 0.03f, 0.05f, 0.001f);
                            Math_SmoothStepToF(&D_i3_801BF040[i], 1.0f, 0.03f, 0.05f, 0.001f);
                        }
                    }
                    break;

                case 2:
                    if (this->swork[A6_SWK_35] != 0) {
                        for (i = 1; i < 12; i++) {
                            D_i3_801BF190[i] = 3.0f;
                            D_i3_801BF1C0[i] = 3.0f;

                            if (this->swork[A6_SWK_8] == 0) {
                                this->swork[A6_SWK_8] = 20;

                                D_i3_801BF100[0].y = RAND_FLOAT_CENTERED(720.0f);
                                if (D_i3_801BF100[0].y < -20.0f) {
                                    D_i3_801BF100[0].y = -20.0f;
                                }
                                if (D_i3_801BF100[0].y > 20.f) {
                                    D_i3_801BF100[0].y = 20.0f;
                                }
                                D_i3_801BF424[0] = D_i3_801BF100[0].y;
                            } else if ((this->swork[A6_SWK_8] & 3) == 0) {
                                D_i3_801BF424[i] = D_i3_801BF100[i].y;
                                D_i3_801BF100[i].y = D_i3_801BF424[i - 1];
                            }

                            if (this->swork[A6_SWK_11] == 0) {
                                if ((D_i3_801BF100[0].y < -20.0f) || (D_i3_801BF100[0].y > 20.0f)) {
                                    for (i = 0; i < 12; i++) {
                                        Math_SmoothStepToF(&D_i3_801BF100[i].x, 0.0f, 0.5f, 50.0f, 0.001f);
                                    }
                                } else {
                                    this->swork[A6_SWK_11] = 30;
                                    D_i3_801BF100[0].x = RAND_RANGE(-12.0f, 18.0f);
                                }
                                D_i3_801BF394[0] = D_i3_801BF100[0].x;
                            } else if ((this->swork[A6_SWK_11] % 8) == 0) {
                                D_i3_801BF394[i] = D_i3_801BF100[i].x;
                                D_i3_801BF100[i].x = D_i3_801BF394[i - 1];
                            }
                        }

                        for (i = 0; i < 12; i++) {
                            Math_SmoothStepToF(&D_i3_801BF070[i].y, D_i3_801BF100[i].y, 0.05f, D_i3_801BF1C0[i],
                                               0.001f);
                            Math_SmoothStepToF(&D_i3_801BF070[i].x, D_i3_801BF100[i].x, 0.05f, D_i3_801BF190[i],
                                               0.001f);
                            Math_SmoothStepToF(&D_i3_801BF190[i], 1.0f, 0.03f, 0.05f, 0.001f);
                            Math_SmoothStepToF(&D_i3_801BF1C0[i], 1.0f, 0.03f, 0.05f, 0.001f);
                        }
                    }
                    break;
            }

            if ((this->state >= 3) && (this->fwork[A6_FWK_0] == 0) &&
                ((this->swork[A6_SWK_33] != 0) || (this->swork[A6_SWK_34] != 0) || (this->swork[A6_SWK_35] != 0)) &&
                (D_i3_801C2250[A6_BSS_5] == 0)) {
                var_fs0 = 0.5f;
                if (this->swork[A6_SWK_25] < 2) {
                    var_fs0 = 0.7f;
                }

                if (((gGameFrameCount % 32) == 0) && (Rand_ZeroOne() < var_fs0) && (D_i3_801C2250[A6_BSS_5] == 0) &&
                    (this->swork[A6_SWK_33 + arg1] != 0)) {
                    if ((Rand_ZeroOne() < 0.2f) || (this->swork[A6_SWK_25] < 2)) {
                        if (this->swork[A6_SWK_18] == 0) {
                            this->swork[A6_SWK_18] = 1;
                        }
                        if (this->swork[A6_SWK_19] == 0) {
                            this->swork[A6_SWK_19] = 1;
                        }
                        if (this->swork[A6_SWK_20] == 0) {
                            this->swork[A6_SWK_20] = 1;
                        }

                        this->swork[A6_SWK_12] = 30;
                        if (this->swork[A6_SWK_33] != 0) {
                            this->swork[A6_SWK_13] = this->swork[A6_SWK_12] + 50;
                        } else {
                            this->swork[A6_SWK_13] = 30;
                        }
                        if (this->swork[A6_SWK_34] != 0) {
                            this->swork[A6_SWK_14] = this->swork[A6_SWK_13] + 50;
                        } else {
                            this->swork[A6_SWK_14] = this->swork[A6_SWK_13];
                        }
                    } else {
                        for (i = 0; i < 3; i++) {
                            if ((i == (gGameFrameCount % 16U)) && (this->swork[A6_SWK_18 + i] == 0)) {
                                this->swork[A6_SWK_12 + i] = 15;
                                this->swork[A6_SWK_18 + i] = 1;
                                i = 3;
                            }
                        }
                    }
                }
            }
            break;

        case 1:
            D_i3_801C2250[A6_BSS_5] = 50;

            for (i = 0; i < 12; i++) {
                if (arg1 == 0) {
                    D_i3_801BEE00[i].x = i * -3.0f;
                    D_i3_801BEE00[i].y = 0.0f;
                    Math_SmoothStepToF(&D_i3_801BED70[i].x, D_i3_801BEE00[i].x, 0.1f, 10.0f, 0.001f);
                    Math_SmoothStepToF(&D_i3_801BED70[i].y, D_i3_801BEE00[i].y, 0.1f, 10.0f, 0.001f);
                }

                if (arg1 == 1) {
                    D_i3_801BEF80[i].x = i * -3.0f;
                    D_i3_801BEF80[i].y = 0.0f;
                    Math_SmoothStepToF(&D_i3_801BEEF0[i].x, D_i3_801BEF80[i].x, 0.1f, 10.0f, 0.001f);
                    Math_SmoothStepToF(&D_i3_801BEEF0[i].y, D_i3_801BEF80[i].y, 0.1f, 10.0f, 0.001f);
                }

                if (arg1 == 2) {
                    D_i3_801BF100[i].x = i * -3.0f;
                    D_i3_801BF100[i].y = 0.0f;
                    Math_SmoothStepToF(&D_i3_801BF070[i].x, D_i3_801BF100[i].x, 0.1f, 10.0f, 0.001f);
                    Math_SmoothStepToF(&D_i3_801BF070[i].y, D_i3_801BF100[i].y, 0.1f, 10.0f, 0.001f);
                }
            }

            if (this->swork[A6_SWK_12 + arg1] == 0) {
                this->swork[A6_SWK_12 + arg1] = 40.0f - ((20.0f - ((this->fwork[A6_FWK_3] * -1.0f) / 150.0f)) * 3.0f);
                if (arg1 == 0) {
                    effectPos.x = D_i3_801BF334[0];
                    effectPos.y = D_i3_801BF3C4[0];
                    effectPos.z = this->obj.pos.z;
                    Effect_SpawnTimedSfxAtPos(&effectPos, NA_SE_EN_ARM_SWING);
                }

                if (arg1 == 1) {
                    effectPos.x = D_i3_801BF364[0];
                    effectPos.y = D_i3_801BF3F4[0];
                    effectPos.z = this->obj.pos.z;
                    Effect_SpawnTimedSfxAtPos(&effectPos, NA_SE_EN_ARM_SWING);
                }

                if (arg1 == 2) {
                    effectPos.x = D_i3_801BF394[0];
                    effectPos.y = D_i3_801BF424[0];
                    effectPos.z = this->obj.pos.z;
                    Effect_SpawnTimedSfxAtPos(&effectPos, NA_SE_EN_ARM_SWING);
                }
                this->swork[A6_SWK_18 + arg1] = 2;
            }
            break;

        case 2:
            D_i3_801C2250[A6_BSS_5] = 50;
            Math_SmoothStepToF(&this->fwork[A6_FWK_25 + arg1], 0.0f, 0.4f, 100.0f, 0.00001f);
            Math_SmoothStepToF(&this->fwork[A6_FWK_22 + arg1],
                               420.0f - ((20.0f - ((this->fwork[A6_FWK_3] * -1.0f) / 150.0f)) * 20.0f), 0.3f, 100.0f,
                               0.00001f);
            if ((this->swork[A6_SWK_12 + arg1] == 0) || (this->swork[A6_SWK_3 + arg1] != 0)) {
                this->swork[A6_SWK_18 + arg1] = 0;
                for (i = 0; i < 12; i++) {
                    if (arg1 == 0) {
                        D_i3_801BEE90[i] = 0.0f;
                        D_i3_801BEEC0[i] = 0.0f;
                    }

                    if (arg1 == 1) {
                        D_i3_801BF010[i] = 0.0f;
                        D_i3_801BF040[i] = 0.0f;
                    }

                    if (arg1 == 2) {
                        D_i3_801BF190[i] = 0.0f;
                        D_i3_801BF1C0[i] = 0.0f;
                    }
                }
            }

            for (i = 0; i < 12; i++) {
                if (arg1 == 0) {
                    D_i3_801BEE00[i].y = 0.0f;
                    D_i3_801BEE00[i].x = D_i3_801BF494[i];
                    Math_SmoothStepToF(&D_i3_801BED70[i].y, D_i3_801BEE00[i].y, 0.3f, 100.0f, 0.00001f);
                    Math_SmoothStepToF(&D_i3_801BED70[i].x, D_i3_801BEE00[i].x, 0.3f, 100.0f, 0.00001f);
                }

                if (arg1 == 1) {
                    D_i3_801BEF80[i].y = 0.0f;
                    D_i3_801BEF80[i].x = D_i3_801BF494[i];
                    Math_SmoothStepToF(&D_i3_801BEEF0[i].y, D_i3_801BEF80[i].y, 0.3f, 100.0f, 0.001f);
                    Math_SmoothStepToF(&D_i3_801BEEF0[i].x, D_i3_801BEF80[i].x, 0.3f, 100.0f, 0.001f);
                }

                if (arg1 == 2) {
                    D_i3_801BF100[i].y = 0.0f;
                    D_i3_801BF100[i].x = D_i3_801BF494[i];
                    Math_SmoothStepToF(&D_i3_801BF070[i].y, D_i3_801BF100[i].y, 0.3f, 100.0f, 0.001f);
                    Math_SmoothStepToF(&D_i3_801BF070[i].x, D_i3_801BF100[i].x, 0.3f, 100.0f, 0.001f);
                }
            }
            break;

        case 3:
            for (i = 0; i < 12; i++) {
                Math_SmoothStepToF(&D_i3_801BEE00[i].y, 0.0f, 0.5f, 50.0f, 0.001f);
                Math_SmoothStepToF(&D_i3_801BEE00[i].x, 0.0f, 0.5f, 50.0f, 0.001f);
                Math_SmoothStepToF(&D_i3_801BEF80[i].y, 0.0f, 0.5f, 50.0f, 0.001f);
                Math_SmoothStepToF(&D_i3_801BEF80[i].x, 0.0f, 0.5f, 50.0f, 0.001f);
                Math_SmoothStepToF(&D_i3_801BF100[i].y, 0.0f, 0.5f, 50.0f, 0.001f);
                Math_SmoothStepToF(&D_i3_801BF100[i].x, 0.0f, 0.5f, 50.0f, 0.001f);
            }

            this->timer_050 = 0;
            this->swork[A6_SWK_18] = this->swork[A6_SWK_19] = this->swork[A6_SWK_20] = 4;
            this->fwork[A6_FWK_13] = this->fwork[A6_FWK_14] = this->fwork[A6_FWK_15] = this->fwork[A6_FWK_22] =
                this->fwork[A6_FWK_23] = this->fwork[A6_FWK_24] = 0.0f;
            this->fwork[A6_FWK_10] = this->fwork[A6_FWK_11] = this->fwork[A6_FWK_12] = this->fwork[A6_FWK_19] =
                this->fwork[A6_FWK_20] = this->fwork[A6_FWK_21] = 0.0f;

            this->fwork[A6_FWK_28] = 0.0f;
            this->fwork[A6_FWK_25] = this->fwork[A6_FWK_26] = this->fwork[A6_FWK_27] = -90.0f;

            for (i = 0; i < 12; i++) {
                D_i3_801BEE00[i].x = 0.0f;
                D_i3_801BEE00[i].y = 0.0f;
                D_i3_801BED70[i].x = 0.0f;
                D_i3_801BED70[i].y = 0.0f;
                D_i3_801BEEC0[i] = D_i3_801BEE90[i] = 3.0f;

                D_i3_801BEF80[i].x = 0.0f;
                D_i3_801BEF80[i].y = 0.0f;
                D_i3_801BEEF0[i].x = 0.0f;
                D_i3_801BEEF0[i].y = 0.0f;
                D_i3_801BF040[i] = D_i3_801BF010[i] = 3.0f;
                3.0f;

                D_i3_801BF100[i].x = 0.0f;
                D_i3_801BF100[i].y = 0.0f;
                D_i3_801BF070[i].x = 0.0f;
                D_i3_801BF070[i].y = 0.0f;
                D_i3_801BF1C0[i] = D_i3_801BF190[i] = 3.0f;
                3.0f;
            }
            break;
    }
}

void Area6_8018B9BC(A6Gorgon* this) {
    s32 i;
    s32 j;
    Vec3f dest;
    Vec3f sfxPos;

    if (D_i3_801C2250[A6_BSS_0] == 0) {
        for (i = 3, j = 15; j < 18; j++, i++) {
            if (this->swork[A6_SWK_0 + j] != 0) {
                if ((gGroundClipMode != 0) && (gPlayerShots[15].timer > 0)) {
                    this->swork[A6_SWK_0 + j] -= this->damage;
                } else if (i + 1 == this->dmgPart) {
                    this->swork[A6_SWK_0 + j] -= this->damage;
                    if ((D_i3_801C2250[A6_BSS_25] == 0) && (this->swork[A6_SWK_25] == 1) && (Rand_ZeroOne() < 0.4f)) {
                        D_i3_801C2250[A6_BSS_10]++;
                        D_i3_801C2250[A6_BSS_10] &= 1;
                        D_i3_801C2250[A6_BSS_25] = 20;
                    }
                }

                AUDIO_PLAY_SFX(NA_SE_EN_SPARK_DAMAGE_M, this->sfxSource, 4);

                if (this->swork[A6_SWK_0 + j] <= 0) {
                    this->swork[A6_SWK_0 + j] = 0;

                    Matrix_MultVec3f(gCalcMatrix, &this->vwork[A6_VWK_1 + i], &dest);
                    func_effect_8007D0E0(this->obj.pos.x + dest.x, this->obj.pos.y + dest.y, this->obj.pos.z + dest.z,
                                         10.0f);

                    sfxPos.x = this->obj.pos.x + dest.x;
                    sfxPos.y = this->obj.pos.y + dest.y;
                    sfxPos.z = this->obj.pos.z + dest.z;

                    Effect_SpawnTimedSfxAtPos(&sfxPos, NA_SE_EN_EXPLOSION_M);
                    Effect_Effect390_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + 150.0f, this->vel.x,
                                           this->vel.y, this->vel.z, 0.2f, 50);
                }

                if ((this->swork[A6_SWK_15] == 0) && (this->swork[A6_SWK_16] == 0) && (this->swork[A6_SWK_17] == 0)) {
                    Audio_KillSfxBySource(this->sfxSource);

                    if (this->swork[A6_SWK_25] != 0) {
                        this->swork[A6_SWK_25]--;
                        if (this->swork[A6_SWK_25] != 0) {
                            this->health -= 60;
                        }
                    }

                    if (this->swork[A6_SWK_25] != 0) {
                        this->timer_058 = 50;
                    } else {
                        this->timer_054 = 30;
                        this->fwork[A6_FWK_32] = 20.0f;
                    }
                }
            }
        }
    }
}

void Area6_8018BCD4(Vec3f* arg0, f32 arg1, f32 arg2, Vec3f* arg3, s32 arg4, f32 arg5, s32 arg6, f32 arg7) {
    s32 i;
    Vec3f sp90 = { 0.0f, 0.0f, 0.0f };

    if (D_i3_801C22F0.unk_24 != 0.0f) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_23);
        if (D_i3_801C22F0.unk_24 != 255.0f) {
            RCP_SetupDL(&gMasterDisp, SETUPDL_71);
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, (s32) D_i3_801C22F0.unk_24);
        } else if (arg4 != 0) {
            RCP_SetupDL(&gMasterDisp, SETUPDL_27);
            if (arg7 < 18.0f) {
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 255, 255);
            } else {
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 0, 255);
            }
        }

        Matrix_Push(&gGfxMatrix);
        Matrix_Push(&gCalcMatrix);
        Matrix_Copy(gCalcMatrix, &gIdentityMatrix);
        Matrix_RotateZ(gCalcMatrix, M_DTOR * arg1, MTXF_APPLY);
        Matrix_Translate(gCalcMatrix, 0.0f, 100.0f, -223.0f, MTXF_APPLY);
        Matrix_RotateX(gCalcMatrix, M_DTOR * arg2, MTXF_APPLY);

        for (i = 0; i < arg6; i++) {
            Matrix_Push(&gGfxMatrix);
            Matrix_Push(&gCalcMatrix);

            // @port: Tag the transform.
            FrameInterpolation_RecordOpenChild(arg0, i);

            if (i == 11) {
                Matrix_Scale(gCalcMatrix, 1.5f, 1.5f, 1.5f, MTXF_APPLY);
                Matrix_Mult(gGfxMatrix, gCalcMatrix, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
                gSPDisplayList(gMasterDisp++, D_A6_600F1F0);
                Matrix_MultVec3f(gCalcMatrix, &sp90, arg3);
            } else {
                Matrix_Scale(gCalcMatrix, 2.0f, 2.0f, 2.0f, MTXF_APPLY);
                Matrix_Mult(gGfxMatrix, gCalcMatrix, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);

                gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                gSPDisplayList(gMasterDisp++, D_A6_6015EE0);

                if (arg6 != 12) {
                    Matrix_MultVec3f(gCalcMatrix, &sp90, arg3);
                }
            }
            Matrix_Pop(&gGfxMatrix);
            Matrix_Pop(&gCalcMatrix);
            Matrix_RotateY(gCalcMatrix, arg0[i].y * M_DTOR, MTXF_APPLY);
            Matrix_RotateX(gCalcMatrix, arg0[i].x * M_DTOR, MTXF_APPLY);
            Matrix_Translate(gCalcMatrix, 0.0f, 0.0f, arg5, MTXF_APPLY);

            // @port Pop the transform id.
            FrameInterpolation_RecordCloseChild();
        }
        Matrix_Pop(&gGfxMatrix);
    }
}

void Area6_8018C0D0(f32* arg0, f32 arg1, Vec3f* arg2, f32 arg3, s32 arg4) {
    s32 i;
    Vec3f spB0 = { 0.0f, 0.0f, 0.0f };
    f32 spAC;
    f32 var_fs3 = 5.0f;

    if ((gGameFrameCount % 2) == 0) {
        spAC = 0.0f;
    } else {
        spAC = 180.0f;
        var_fs3 = 5.0f - (2.0f * (var_fs3 / 10.0f));
    }

    Matrix_Push(&gGfxMatrix);
    Matrix_Push(&gCalcMatrix);
    Matrix_Copy(gCalcMatrix, &gIdentityMatrix);

    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);

    Matrix_RotateZ(gCalcMatrix, (D_i3_801C22F0.unk_34 + arg1) * M_DTOR, MTXF_APPLY);
    Matrix_Translate(gCalcMatrix, 0.0f, -360.0f, 120.0f, MTXF_APPLY);
    Matrix_RotateX(gCalcMatrix, -(90.0f - arg3) * M_DTOR, MTXF_APPLY);
    Matrix_Scale(gCalcMatrix, 0.7f, 0.7f, 0.7f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);

    for (i = 0; i < 5; i++) {
        Matrix_Push(&gGfxMatrix);
        Matrix_Push(&gCalcMatrix);

        // @port: Tag the transform.
        FrameInterpolation_RecordOpenChild(arg0, i);

        if (i == 4) {
            Matrix_RotateX(gCalcMatrix, 80.0f * M_DTOR, MTXF_APPLY);
            Matrix_RotateX(gCalcMatrix, (90.0f - arg3) * M_DTOR, MTXF_APPLY);
            Matrix_Scale(gCalcMatrix, var_fs3, var_fs3, 1.0f, MTXF_APPLY);
            Matrix_Mult(gGfxMatrix, gCalcMatrix, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            RCP_SetupDL(&gMasterDisp, SETUPDL_49);
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, (s32) D_i3_801C22F0.r[arg4], (s32) D_i3_801C22F0.g[arg4],
                            (s32) D_i3_801C22F0.b[arg4], 255);
            gDPSetEnvColor(gMasterDisp++, 255, 0, 0, 255);
            gSPDisplayList(gMasterDisp++, aOrbDL);
            Matrix_MultVec3f(gCalcMatrix, &spB0, arg2);
        } else {
            RCP_SetupDL(&gMasterDisp, SETUPDL_47);
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 64, 64, 192);
            Matrix_Translate(gCalcMatrix, 0.0f, -60.0f, 0.0f, MTXF_APPLY);
            Matrix_Scale(gCalcMatrix, 2.0f, 3.0f, 1.0f, MTXF_APPLY);
            Matrix_RotateY(gCalcMatrix, M_DTOR * spAC, MTXF_APPLY);
            Matrix_Mult(gGfxMatrix, gCalcMatrix, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_102F5E0);
        }
        Matrix_Pop(&gCalcMatrix);
        Matrix_Pop(&gGfxMatrix);
        Matrix_Translate(gCalcMatrix, 0.0f, -120.0f, 0.0f, MTXF_APPLY);
        Matrix_RotateX(gCalcMatrix, -20.0f * M_DTOR, MTXF_APPLY);
        Matrix_RotateZ(gCalcMatrix, arg0[i] * M_DTOR, MTXF_APPLY);

        // @port Pop the transform id.
        FrameInterpolation_RecordCloseChild();
    }
    Matrix_Pop(&gCalcMatrix);
    Matrix_Pop(&gGfxMatrix);
}

void Area6_A6Gorgon_Draw(A6Gorgon* this) {
    Vec3f jointTable[30];
    Vec3f spC4;
    Vec3f spB8;
    Vec3f spAC;
    s32 i;
    s32 j;

    if (this->state == 0) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_49);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, (s32) D_i3_801C22F0.unk_24);
        gDPSetEnvColor(gMasterDisp++, 255, 255, 0, 255);
        Matrix_Scale(gGfxMatrix, 10.0f, 10.0f, 10.0f, MTXF_APPLY);
        Matrix_RotateZ(gGfxMatrix, this->fwork[A6_FWK_33] * M_DTOR, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, aStarDL);
    } else if (D_i3_801C22F0.unk_24 != 0.0f) {
        Animation_GetFrameData(&D_A6_6018994, 0, jointTable);

        if (D_i3_801C22F0.unk_24 != 255.0f) {
            RCP_SetupDL(&gMasterDisp, SETUPDL_71);
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, (s32) D_i3_801C22F0.unk_24);
            spAC.x = 0.0f;

            if (!(gSysFrameCount & 1)) {
                spAC.x = 1.0f;
                if (1) {}
                spAC.x = 0.0f;
            }
            spAC.y = spAC.z = 0.0f;

            Matrix_RotateZ(gCalcMatrix, gGameFrameCount * 6.0f * M_DTOR, MTXF_NEW);
            Matrix_MultVec3f(gCalcMatrix, &spAC, &spB8);
            Matrix_Translate(gGfxMatrix, spB8.x, spB8.y, 0.0f, MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, this->scale, this->scale, this->scale, MTXF_APPLY);
            Matrix_RotateZ(gGfxMatrix, gGameFrameCount * 10.0f * M_DTOR, MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, this->fwork[A6_FWK_34], this->fwork[A6_FWK_35], 1.0f, MTXF_APPLY);
            Matrix_RotateZ(gGfxMatrix, -(f32) gGameFrameCount * 10.0f * M_DTOR, MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, this->fwork[A6_FWK_34], this->fwork[A6_FWK_35], 1.0f, MTXF_APPLY);
        } else {
            RCP_SetupDL(&gMasterDisp, SETUPDL_27);
            if (this->timer_05C & 1) {
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
            } else {
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, (s32) D_i3_801C22F0.unk_28[0], (s32) D_i3_801C22F0.unk_28[2],
                                (s32) D_i3_801C22F0.unk_28[1], 255);
            }
        }

        jointTable[3].z -= this->fwork[A6_FWK_0];
        jointTable[4].z -= this->fwork[A6_FWK_0];
        jointTable[5].z -= this->fwork[A6_FWK_0];

        Animation_DrawSkeleton(1, D_A6_6018BA0, jointTable, NULL, NULL, &this->index, &gIdentityMatrix);

        if (this->scale >= 1.0f) {
            for (i = 0; i < 3; i++) {
                if ((this->swork[A6_SWK_33 + i] == 0) && (this->state != 3) && (D_i3_801C2250[A6_BSS_2_0 + i] == 0) &&
                    ((gGameFrameCount % 4) == 0) && (this->swork[A6_SWK_27 + i] != 0) && (gPlayState != 100)) {
                    Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
                    Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);
                    Matrix_RotateZ(gCalcMatrix, this->obj.rot.z * M_DTOR, MTXF_APPLY);

                    Matrix_MultVec3f(gCalcMatrix, &this->vwork[A6_VWK_1] + i, &spC4);

                    func_effect_8007D0E0(this->obj.pos.x + spC4.x, this->obj.pos.y + spC4.y, this->obj.pos.z + spC4.z,
                                         20.0f);

                    spB8.x = this->obj.pos.x + spC4.x;
                    spB8.y = this->obj.pos.y + spC4.y;
                    spB8.z = this->obj.pos.z + spC4.z;

                    if ((!this) && (!this)) {} // fake

                    if (D_i3_801C2250[A6_BSS_26] == 0) {
                        Effect_SpawnTimedSfxAtPos(&spB8, NA_SE_EN_EXPLOSION_M);
                    }

                    D_i3_801C2250[A6_BSS_26]++;
                    D_i3_801C2250[A6_BSS_26] &= 1;

                    this->swork[A6_SWK_27 + i]--;

                    if (this->swork[A6_SWK_27 + i] <= 0) {
                        this->swork[A6_SWK_18 + i] = 4;
                        this->swork[A6_SWK_38] = 1;
                        this->fwork[A6_FWK_10 + i] = this->fwork[A6_FWK_19 + i] = this->fwork[A6_FWK_13 + i] =
                            this->fwork[A6_FWK_22 + i] = 0.0f;
                        this->fwork[A6_FWK_25 + i] = -90.0f;

                        for (j = 0; j < 12; j++) {
                            if (i == 0) {
                                D_i3_801BED70[j].y = D_i3_801BED70[j].x = D_i3_801BEE00[j].y = D_i3_801BEE00[j].x =
                                    0.0f;
                                D_i3_801BEE90[j] = 3.0f;
                                D_i3_801BEEC0[j] = 3.0f;
                            }

                            if (i == 1) {
                                D_i3_801BEEF0[j].y = D_i3_801BEEF0[j].x = D_i3_801BEF80[j].y = D_i3_801BEF80[j].x =
                                    0.0f;
                                D_i3_801BF010[j] = 3.0f;
                                D_i3_801BF040[j] = 3.0f;
                            }

                            if (i == 2) {
                                D_i3_801BF070[j].y = D_i3_801BF070[j].x = D_i3_801BF100[j].y = D_i3_801BF100[j].x =
                                    0.0f;
                                D_i3_801BF190[j] = 3.0f;
                                D_i3_801BF1C0[j] = 3.0f;
                            }
                        }
                    }
                }
            }
            Area6_8018BCD4(D_i3_801BED70, 0.0f, this->fwork[A6_FWK_25], &this->vwork[A6_VWK_1],
                           this->swork[A6_SWK_0] & 1, this->fwork[A6_FWK_10] + this->fwork[A6_FWK_19],
                           this->swork[A6_SWK_27], this->fwork[A6_FWK_0]);
            Area6_8018BCD4(D_i3_801BEEF0, -120.0f, this->fwork[A6_FWK_26], &this->vwork[A6_VWK_2],
                           this->swork[A6_SWK_1] & 1, this->fwork[A6_FWK_11] + this->fwork[A6_FWK_20],
                           this->swork[A6_SWK_28], this->fwork[A6_FWK_0]);
            Area6_8018BCD4(D_i3_801BF070, 120.0f, this->fwork[A6_FWK_27], &this->vwork[A6_VWK_3],
                           this->swork[A6_SWK_2] & 1, this->fwork[A6_FWK_12] + this->fwork[A6_FWK_21],
                           this->swork[A6_SWK_29], this->fwork[A6_FWK_0]);

            if ((this->swork[A6_SWK_15] != 0) && (this->state >= 3) && (D_i3_801C22F0.unk_24 == 255.0f) &&
                (D_i3_801C2250[A6_BSS_0] == 0)) {
                Area6_8018C0D0(D_i3_801BF1F0, 0.0f, &this->vwork[A6_VWK_4], this->fwork[A6_FWK_0], 0);
            }

            if ((this->swork[A6_SWK_16] != 0) && (this->state >= 3) && (D_i3_801C22F0.unk_24 == 255.0f) &&
                (D_i3_801C2250[A6_BSS_0] == 0)) {
                Area6_8018C0D0(D_i3_801BF220, -120.0f, &this->vwork[A6_VWK_5], this->fwork[A6_FWK_0], 1);
            }

            if ((this->swork[A6_SWK_17] != 0) && (this->state >= 3) && (D_i3_801C22F0.unk_24 == 255.0f) &&
                (D_i3_801C2250[A6_BSS_0] == 0)) {
                Area6_8018C0D0(D_i3_801BF250, 120.0f, &this->vwork[A6_VWK_6], this->fwork[A6_FWK_0], 2);
            }

            if (this->swork[A6_SWK_25] != 0) {
                j = this->swork[A6_SWK_25] - 1;

                if ((this->timer_058 != 0) && !(this->timer_058 & 3)) {
                    AUDIO_PLAY_SFX(NA_SE_OB_DAMAGE_M, this->sfxSource, 4);
                }

                if (this->timer_058 == 1) {
                    if (this->swork[A6_SWK_25] == 2) {
                        Radio_PlayMessage(gMsg_ID_7085, RCID_FALCO);
                    } else if (this->swork[A6_SWK_25] == 1) {
                        Radio_PlayMessage(gMsg_ID_7086, RCID_SLIPPY);
                    }
                }

                if (this->swork[A6_SWK_22] != D_i3_801BF310[j]) {
                    if (this->swork[A6_SWK_22] < D_i3_801BF310[j]) {
                        this->swork[A6_SWK_22]++;
                    } else {
                        this->swork[A6_SWK_22]--;
                    }
                }

                if (this->swork[A6_SWK_23] != D_i3_801BF31C[j]) {
                    if (this->swork[A6_SWK_23] < D_i3_801BF31C[j]) {
                        this->swork[A6_SWK_23]++;
                    } else {
                        this->swork[A6_SWK_23]--;
                    }
                }

                if (this->swork[A6_SWK_24] != D_i3_801BF328[j]) {
                    if (this->swork[A6_SWK_24] < D_i3_801BF328[j]) {
                        this->swork[A6_SWK_24]++;
                    } else {
                        this->swork[A6_SWK_24]--;
                    }
                }
            } else {
                Math_SmoothStepToF(&this->fwork[A6_FWK_29], 0.0f, 1.0f, 10.0f, 0.0001f);
                if ((this->timer_054 == 0) && (this->swork[A6_SWK_36] == 4) && (D_i3_801C2250[A6_BSS_31] == 0)) {
                    Radio_PlayMessage(gMsg_ID_7087, RCID_PEPPY);
                    this->swork[A6_SWK_36] = 5;
                    D_i3_801C2250[A6_BSS_31]++;
                    D_i3_801C2250[A6_BSS_31] &= 1;
                }
            }
        }
        Matrix_Push(&gGfxMatrix);
        RCP_SetupDL(&gMasterDisp, SETUPDL_71);
        Matrix_Translate(gGfxMatrix, 0.0f, 2.0f, 70.0f, MTXF_APPLY);
        Matrix_Scale(gGfxMatrix, 1.7f, 1.7f, 1.7f, MTXF_APPLY);

        if (this->timer_05C & 1) {
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
        } else {
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, (s32) D_i3_801C22F0.unk_24);
        }

        Matrix_SetGfxMtx(&gMasterDisp);

        // @port: Tag the transform.
        FrameInterpolation_RecordOpenChild(this, 0);

        gSPDisplayList(gMasterDisp++, D_A6_601B2B0);

        Matrix_Pop(&gGfxMatrix);

        // @port Pop the transform id.
        FrameInterpolation_RecordCloseChild();

        RCP_SetupDL(&gMasterDisp, SETUPDL_71);
        if (D_i3_801C22F0.unk_24 != 255.0f) {
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, this->swork[A6_SWK_22], this->swork[A6_SWK_23],
                            this->swork[A6_SWK_24], (s32) D_i3_801C22F0.unk_28[-1]);
        } else {
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, this->swork[A6_SWK_22], this->swork[A6_SWK_23],
                            this->swork[A6_SWK_24], (s32) this->fwork[A6_FWK_29]);
        }
        Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, 74.0f, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);

        // @port: Tag the transform.
        FrameInterpolation_RecordOpenChild(this, 1);

        gSPDisplayList(gMasterDisp++, D_A6_6011910);
        Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, 74.0f, MTXF_APPLY);

        // @port Pop the transform id.
        FrameInterpolation_RecordCloseChild();
    }
}

void Area6_8018D3CC(s32 arg0, f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 xRot, f32 yRot,
                    f32 zRot) {
    s32 i;

    for (i = 0; i < 10; i++) {
        if (gPlayerShots[i].obj.status == SHOT_FREE) {
            PlayerShot_Initialize(&gPlayerShots[i]);
            gPlayerShots[i].vel.z = zVel;
            gPlayerShots[i].vel.x = xVel;
            gPlayerShots[i].vel.y = yVel;
            gPlayerShots[i].obj.pos.x = xPos;
            gPlayerShots[i].obj.pos.y = yPos;
            gPlayerShots[i].obj.pos.z = zPos;
            gPlayerShots[i].obj.status = SHOT_ACTIVE;
            gPlayerShots[i].obj.rot.x = xRot + 180.0f;
            gPlayerShots[i].obj.rot.y = yRot;
            gPlayerShots[i].obj.rot.z = -zRot;
            gPlayerShots[i].unk_58 = 1;
            gPlayerShots[i].unk_60 = 0;
            gPlayerShots[i].obj.id = PLAYERSHOT_TWIN_LASER;
            gPlayerShots[i].timer = 150;
            gPlayerShots[i].sourceId = CS_SHOT_ID;

            AUDIO_PLAY_SFX(NA_SE_ARWING_SHOT_F, gPlayerShots[i].sfxSource, 4);
            break;
        }
    }
}

void Area6_8018D4E0(Actor* this) {
    s32 i;

    Effect386_Spawn1(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 0.0f, 0.0f, 0.0f, 4.0f, 20);
    func_effect_8007D2C8(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 7.0f);
    Effect_Effect384_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 6.0f, 5);

    Object_Kill(&this->obj, this->sfxSource);

    for (i = 0; i < 15; i++) {
        Effect_Effect357_Spawn50(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 1.0f);
    }
    Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_EXPLOSION_M);
}

void Area6_8018D5C8(void) {
    s32 i = 0; // Fake ?

    Actor_Initialize(&gActors[i]);
    gActors[i].obj.status = OBJ_INIT;

    gActors[i].obj.pos.x = 1600.0f;
    gActors[i].obj.pos.y = 3750.0f;
    gActors[i].obj.pos.z = 13000.0f;

    gActors[i].animFrame = ACTOR_CS_GREAT_FOX;
    gActors[i].state = 90;
    gActors[i].fwork[0] = 0.0f;
    gActors[i].obj.id = OBJ_ACTOR_CUTSCENE;

    Object_SetInfo(&gActors[i].info, gActors[i].obj.id);
    AUDIO_PLAY_SFX(NA_SE_GREATFOX_ENGINE, gActors[i].sfxSource, 0);
}

void Area6_8018D694(ActorCutscene* this, s32 index) {
    Vec3f commanderSetupPos[5] = {
        { -150.0f, 0.0f, 200.0f },   { 0.0f, 50.0f, 0.0f },       { 150.0f, -50.0f, 100.0f },
        { -350.0f, 100.0f, 300.0f }, { 100.0f, -300.0f, 100.0f },
    };

    Actor_Initialize(this);
    this->obj.status = OBJ_ACTIVE;
    this->obj.id = OBJ_ACTOR_CUTSCENE;

    this->obj.pos.x = commanderSetupPos[index].x + 100.0f;
    this->obj.pos.y = commanderSetupPos[index].y + 350.0f;
    this->obj.pos.z = commanderSetupPos[index].z + 1000.0f;

    this->state = 1;
    this->animFrame = ACTOR_CS_COMMANDER_GLOW;
    this->iwork[11] = 1;
    this->rot_0F4.y = 90.0f;
    this->fwork[0] = 1.5f;
    this->fwork[7] = RAND_FLOAT_SEEDED(360.0f);
    this->fwork[8] = RAND_FLOAT_SEEDED(360.0f);
    this->fwork[9] = RAND_FLOAT_SEEDED(360.0f);

    Object_SetInfo(&this->info, this->obj.id);
    AUDIO_PLAY_SFX(NA_SE_EN_ENGINE_01, this->sfxSource, 4);
}

void Area6_8018D804(ActorCutscene* this, s32 teamIdx) {
    Vec3f sp2C[3] = {
        { -200.0f, 0.0f, -500.0f },
        { 200.0f, 30.0f, -600.0f },
        { 50.0f, -90.0f, -700.0f },
    };
    Player* player = &gPlayer[0];

    Actor_Initialize(this);
    this->obj.status = OBJ_ACTIVE;
    this->obj.id = OBJ_ACTOR_CUTSCENE;

    this->obj.pos.x = sp2C[teamIdx].x + player->pos.x;
    this->obj.pos.y = sp2C[teamIdx].y + player->pos.y;
    this->obj.pos.z = sp2C[teamIdx].z + player->pos.z;

    this->state = 5;
    this->iwork[11] = 1;
    this->fwork[0] = 0.0f;
    Object_SetInfo(&this->info, this->obj.id);

    if (CVarGetInteger("gTeamFaces", 1) == 1) {
        // @port: Setup team faces
        this->iwork[14] = teamIdx + 2;
    }

    AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, this->sfxSource, 4);
}

void Area6_8018D920(Vec3f* pos) {
    f32 sp6C = pos->x - pos->x; // what is this calculation?
    f32 sp68 = pos->y - pos->y;
    f32 sp64 = pos->z - 1000.0f - pos->z;
    f32 yRot = Math_RadToDeg(Math_Atan2F(sp6C, sp64));
    f32 xRot = Math_RadToDeg(-Math_Atan2F(sp68, sqrtf(SQ(sp6C) + SQ(sp64))));
    Vec3f speed;
    Vec3f vel;

    Matrix_RotateY(gCalcMatrix, M_DTOR * yRot, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, M_DTOR * xRot, MTXF_APPLY);

    speed.x = 0.0f;
    speed.y = 0.0f;
    speed.z = 100.0f;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &speed, &vel);
    Area6_8018D3CC(CS_SHOT_ID, pos->x, pos->y, pos->z, vel.x, vel.y, vel.z, xRot, yRot, 0.0f);
}

void Area6_8018DA58(ActorCutscene* this) {
    Vec3f sp5C;
    Vec3f sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;

    switch (this->state) {
        case 1:
            this->fwork[7] += 2.5f;
            this->rot_0F4.z = SIN_DEG(this->fwork[7]) * 10.0f;
            this->fwork[8] += 1.0f;
            this->obj.pos.y += SIN_DEG(this->fwork[8]) * 1.5f;
            this->fwork[9] += 1.0f;
            this->obj.pos.z += COS_DEG(this->fwork[9]) * 1.5f;
            break;

        case 2:
            Math_SmoothStepToF(&this->rot_0F4.z, -180.0f, 0.1f, 3.0f, 0.0f);
            break;

        case 3:
            Math_SmoothStepToF(&this->rot_0F4.z, -45.0f, 0.05f, 2.0f, 0.0f);
            Math_SmoothStepToAngle(&this->rot_0F4.y, 340.0f, 0.05f, 2.4f, 0.0f);
            Math_SmoothStepToF(&this->rot_0F4.x, 3.0f, 0.05f, 1.0f, 0.0f);
            Math_SmoothStepToF(&this->fwork[0], 30.0f, 0.1f, 3.0f, 0.0f);
            break;

        case 6:
        case 11:
        case 16:
            this->state++;
            AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, this->sfxSource, 0);
            this->fwork[29] = 5.0f;
            /* fallthrough */
        case 7:
        case 12:
        case 17:
            this->iwork[11] = 2;
            Math_SmoothStepToF(&this->fwork[0], 50.0f, 0.1f, 3.0f, 0.01f);

            switch (this->state) {
                case 7:
                    sp48 = -100.0f;
                    sp4C = 100.0f;
                    sp44 = -999.0f;
                    break;
                case 12:
                    sp4C = -100.0f;
                    sp48 = -100.0f;
                    sp44 = -999.0f;
                    break;
                case 17:
                    sp48 = -100.0f;
                    sp4C = 100.0f;
                    sp44 = -999.0f;
                    break;
            }

            sp3C = Math_RadToDeg(Math_Atan2F(sp4C, sp44));
            sp40 = Math_RadToDeg(-Math_Atan2F(sp48, sqrtf((sp4C * sp4C) + (sp44 * sp44))));

            if ((sp40 + 40.0f) >= 360.0f) {
                sp40 -= 360.0f;
            }
            if (sp40 > 180.0f) {
                sp40 = 0.0f;
            }

            sp38 = Math_SmoothStepToAngle(&this->rot_0F4.y, sp3C, 0.5f, 2.0f, 0.0001f) * 30.0f;
            Math_SmoothStepToAngle(&this->rot_0F4.x, sp40, 0.5f, 2.0f, 0.0001f);
            Math_SmoothStepToAngle(&this->rot_0F4.z, sp38, 0.1f, 5.0f, 0.0001f);
            break;

        case 91:
            Math_SmoothStepToF(&this->obj.pos.y, 0.0f, 0.1f, 5.0f, 0.1f);
            Math_SmoothStepToF(&this->obj.pos.z, 0.0f, 1.0f, 20.0f, 20.0f);
            break;

        case 90:
            break;
    }

    Matrix_RotateY(gCalcMatrix, (this->rot_0F4.y + 180.0f) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -(this->rot_0F4.x * M_DTOR), MTXF_APPLY);

    sp5C.x = 0.0f;
    sp5C.y = 0.0f;
    sp5C.z = this->fwork[0];

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp5C, &sp50);

    this->vel.x = sp50.x;
    this->vel.y = sp50.y;
    this->vel.z = sp50.z;

    this->obj.rot.x = -this->rot_0F4.x;
    this->obj.rot.y = this->rot_0F4.y + 180.0f;
    this->obj.rot.z = -this->rot_0F4.z;
}

void Area6_LevelStart(Player* player) {
    Vec3f sp74;
    Vec3f sp68;
    Vec3f sp5C;
    f32 temp1;
    f32 temp2;
    f32 temp3;
    f32 temp4;

    switch (player->csState) {
        case 0:
            gCsFrameCount = 0;

            player->csState = 1;

            Rand_SetSeed(1, 29000, 9876);

            Area6_8018D694(&gActors[1], 0);
            Area6_8018D694(&gActors[2], 1);
            Area6_8018D694(&gActors[6], 2);
            Area6_8018D694(&gActors[7], 3);
            Area6_8018D694(&gActors[8], 4);
            Area6_8018D5C8();

            player->pos.x = 0.0f;
            player->pos.y = 350.0f;
            player->pos.z = 16000.0f;
            player->baseSpeed = 30.0f;

            if (gTeamShields[TEAM_ID_FALCO] > 0) {
                Area6_8018D804(&gActors[3], 0);
            }
            if (gTeamShields[TEAM_ID_SLIPPY] > 0) {
                Area6_8018D804(&gActors[4], 1);
            }
            if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                Area6_8018D804(&gActors[5], 2);
            }
            gActors[0].fwork[0] = 20.0f;
            gActors[3].fwork[0] = 30.0f;
            gActors[4].fwork[0] = 30.0f;
            gActors[5].fwork[0] = 30.0f;
            D_ctx_80177A48[4] = 270.0f;
            D_ctx_80177A48[5] = 1000.0f;
            D_ctx_80177A48[6] = 1100.0f;
            D_ctx_80177A48[3] = 0.001f;
            /* fallthrough */
        case 1:
            Math_SmoothStepToF(&gActors[0].obj.pos.y, 0.0f, 0.01f, 10.0f, 0.001f);

            if (gCsFrameCount < 490) {
                sp74.x = 0.0f;
                sp74.y = 0.0f;
                sp74.z = D_ctx_80177A48[5];

                Matrix_Translate(gCalcMatrix, 0.0f, 350.0f, D_ctx_80177A48[6], MTXF_NEW);
                Matrix_RotateY(gCalcMatrix, -(D_ctx_80177A48[4] * M_DTOR), MTXF_APPLY);
                Matrix_MultVec3f(gCalcMatrix, &sp74, &sp68);

                gCsCamEyeX = sp68.x;
                gCsCamEyeY = sp68.y;
                gCsCamEyeZ = sp68.z;

                if (gCsFrameCount < 200) {
                    Math_SmoothStepToF(&D_ctx_80177A48[4], 0.0f, 0.05f, 0.56f, 0.001f);
                    gCsCamAtX = gActors[1].obj.pos.x;
                    gCsCamAtY = gActors[1].obj.pos.y;
                    gCsCamAtZ = gActors[1].obj.pos.z;
                    D_ctx_80177A48[0] = 1.0f;
                    D_ctx_80177A48[1] = 1.0f;
                } else {
                    Math_SmoothStepToF(&D_ctx_80177A48[4], 0.0f, 0.05f, 0.56f, 0.001f);
                    Math_SmoothStepToF(&D_ctx_80177A48[5], 0.0f, 0.003f, 100.0f, 0.001f);
                    Math_SmoothStepToF(&gCsCamAtX, player->pos.x, 0.01f, 20.0f, 0.0001f);
                    Math_SmoothStepToF(&gCsCamAtY, player->pos.y, 0.01f, 20.0f, 0.0001f);
                    Math_SmoothStepToF(&gCsCamAtZ, player->pos.z - 2500.0f, 0.01f, 20.0f, 0.0001f);
                    D_ctx_80177A48[0] = 1.0f;
                    D_ctx_80177A48[1] = 1.0f;
                }
            } else {
                Math_SmoothStepToF(&D_ctx_80177A48[3], 0.1f, 0.3f, 0.1f, 0.00001f);
                temp1 = fabsf(player->pos.x - gCsCamEyeX) * D_ctx_80177A48[3];
                temp2 = fabsf(player->pos.y * player->unk_148 + 50.0f - gCsCamEyeY) * D_ctx_80177A48[3];
                temp3 = fabsf(player->pos.z + 400.0f - gCsCamEyeZ) * D_ctx_80177A48[3];

                gCsCamEyeX += temp1;
                gCsCamEyeY -= temp2;
                gCsCamEyeZ -= temp3;

                temp1 = fabsf(player->pos.x - gCsCamAtX) * D_ctx_80177A48[3];
                temp2 = fabsf(player->pos.y * player->unk_148 + 20.0f - gCsCamAtY) * D_ctx_80177A48[3];
                temp3 = fabsf(player->pos.z - 51.0f - gCsCamAtZ) * D_ctx_80177A48[3];

                gCsCamAtX += temp1;
                gCsCamAtY -= temp2;
                gCsCamAtZ -= temp3;

                D_ctx_80177A48[0] = 1.0f;
                D_ctx_80177A48[1] = 1.0f;
            }

            if (gCsFrameCount == 460) {
                player->unk_190 = 2.0f;
                player->unk_194 = 5.0f;
                AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, player->sfxSource, 0);
            }

            if (gCsFrameCount >= 460) {
                Math_SmoothStepToF(&player->baseSpeed, 50.0f, 0.1f, 3.0f, 0.01f);
            }

            if (player->pos.z < 30.0f) {
                player->baseSpeed = player->pos.z = 0.0f;
            }

            if (gCsFrameCount == 540) {
                gLoadLevelObjects = 1;
                gLevelStartStatusScreenTimer = 50;
                player->pos.x = 0.0f;
                player->pos.z = 0.0f;
                player->pos.y = 350.0f;
                player->baseSpeed = gArwingSpeed;
                player->csState = 0;
                player->csTimer = 0;

                AUDIO_PLAY_BGM(NA_BGM_STAGE_A6);
                player->state = PLAYERSTATE_ACTIVE;
            }
            break;
    }

    switch (gCsFrameCount) {
        case 280:
            AUDIO_PLAY_BGM(NA_BGM_A6_START_DEMO);
            break;

        case 40:
            Radio_PlayMessage(gMsg_ID_7005, RCID_CAIMAN_AREA6);
            break;

        case 155:
            sp5C.x = player->pos.x;
            sp5C.y = player->pos.y;
            sp5C.z = player->pos.z;
            Area6_8018D920(&sp5C);
            break;

        case 176:
            if (gTeamShields[TEAM_ID_FALCO] > 0) {
                Area6_8018D920(&gActors[3].obj.pos);
            }
            break;

        case 187:
            if (gTeamShields[TEAM_ID_SLIPPY] > 0) {
                Area6_8018D920(&gActors[4].obj.pos);
            }
            break;

        case 198:
            if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                Area6_8018D920(&gActors[5].obj.pos);
            }
            break;

        case 199:
            Area6_8018D4E0(&gActors[1]);
            break;

        case 210:
            Radio_PlayMessage(gMsg_ID_7006, RCID_CAIMAN_AREA6);
            break;

        case 240:
            gActors[2].state = 3;
            break;

        case 250:
            gActors[6].state = 3;
            break;

        case 260:
            gActors[7].state = 3;
            break;

        case 270:
            gActors[8].state = 3;
            break;

        case 360:
            Radio_PlayMessage(gMsg_ID_7011, RCID_FALCO);
            break;

        case 430:
            gActors[5].state = 16;
            break;

        case 440:
            gActors[4].state = 11;
            break;

        case 450:
            gActors[3].state = 6;
            break;

        case 480:
            Play_ClearObjectData();
            break;
    }

    Matrix_RotateY(gCalcMatrix, (player->rot.y + player->yRot_114 + 180.0f) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -(player->rot.x * M_DTOR), MTXF_APPLY);

    if (player->state != PLAYERSTATE_ACTIVE) {
        sp74.x = 0.0f;
        sp74.y = 0.0f;
        sp74.z = player->baseSpeed;

        Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp74, &sp68);

        player->vel.x = sp68.x;
        player->vel.z = sp68.z;
        player->vel.y = sp68.y;

        player->pos.x += player->vel.x;
        player->pos.y += player->vel.y;
        player->pos.z += player->vel.z;
        player->trueZpos = player->pos.z;
    }

    player->bankAngle = player->rot.z + player->zRotBank + player->zRotBarrelRoll;

    Math_SmoothStepToF(&player->cam.eye.x, gCsCamEyeX, D_ctx_80177A48[0], 50000.0f, 0.001f);
    Math_SmoothStepToF(&player->cam.eye.y, gCsCamEyeY, D_ctx_80177A48[0], 50000.0f, 0.001f);
    Math_SmoothStepToF(&player->cam.eye.z, gCsCamEyeZ, D_ctx_80177A48[0], 50000.0f, 0.001f);

    Math_SmoothStepToF(&player->cam.at.x, gCsCamAtX, D_ctx_80177A48[1], 50000.0f, 0.001f);
    Math_SmoothStepToF(&player->cam.at.y, gCsCamAtY, D_ctx_80177A48[1], 50000.0f, 0.001f);
    Math_SmoothStepToF(&player->cam.at.z, gCsCamAtZ, D_ctx_80177A48[1], 50000.0f, 0.001f);
}

void Area6_8018EA88(ActorCutscene* this) {
    Actor_Initialize(this);
    this->obj.status = OBJ_ACTIVE;
    this->obj.id = OBJ_ACTOR_CUTSCENE;
    this->obj.pos.x = 0.0f;
    this->obj.pos.y = 0.0f;
    this->obj.pos.z = gBosses[0].obj.pos.z + 500.0f;
    this->animFrame = ACTOR_CS_37;
    this->state = 100;
    this->iwork[0] = 255;
    this->iwork[1] = 255;
    this->iwork[2] = 255;
    this->iwork[3] = 240;
    this->iwork[4] = 0;
    this->iwork[5] = 0;
    this->iwork[6] = 255;
    this->iwork[7] = 100;
    this->fwork[4] = 1.0f;
    this->scale = 1.0f;
    Object_SetInfo(&this->info, this->obj.id);
}

void Area6_8018EB3C(ActorCutscene* this) {
    Player* player = &gPlayer[0];

    Actor_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_ACTOR_CUTSCENE;
    this->obj.pos.x = player->pos.x;
    this->obj.pos.y = player->pos.y + 600.0f;
    this->obj.pos.z = player->pos.z + 2800.0f;
    this->animFrame = ACTOR_CS_GREAT_FOX;
    this->state = 100;
    this->fwork[0] = 0.0f;

    Object_SetInfo(&this->info, this->obj.id);
    AUDIO_PLAY_SFX(NA_SE_GREATFOX_ENGINE, this->sfxSource, 0);
    AUDIO_PLAY_SFX(NA_SE_GREATFOX_BURNER, this->sfxSource, 0);
}

void Area6_8018EC38(ActorCutscene* this, s32 teamIdx) {
    Vec3f sp2C[3] = {
        { -150.0f, 40.0f, 75.0f },
        { 150.0f, 40.0f, 150.0f },
        { 38.0f, 88.0f, 225.0f },
    };
    Player* player = &gPlayer[0];

    if (gTeamShields[teamIdx + 1] > 0) {
        Actor_Initialize(this);
        this->obj.status = OBJ_ACTIVE;
        this->obj.id = OBJ_ACTOR_CUTSCENE;

        this->obj.pos.x = sp2C[teamIdx].x + player->pos.x;
        this->obj.pos.y = sp2C[teamIdx].y + player->pos.y;
        this->obj.pos.z = sp2C[teamIdx].z + player->pos.z;

        this->state = 100;

        this->iwork[11] = 1;
        this->fwork[0] = 0.0f;

        // @port: Setup team faces (original code was omitting Peppy)
        if ((teamIdx + 1 != 3) || (CVarGetInteger("gTeamFaces", 1) == 1)) {
            this->iwork[TEAM_FACE] = teamIdx + 2;
        }

        Object_SetInfo(&this->info, this->obj.id);
        AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, this->sfxSource, 4);
    }
}

void Area6_LevelComplete(Player* player) {
    s32 i;
    Vec3f spf90;
    f32 sp8C;
    f32 sp88;
    f32 sp84;
    Vec3f sp78;
    Vec3f sp6C;
    Actor* actor4 = &gActors[4];
    s32 pad;

    switch (player->csState) {
        case 0:
            gCsFrameCount = 0;
            player->csState = 1;
            player->arwing.drawFace = true;
            player->unk_194 = 5.0f;
            player->unk_190 = 2.0f;
            player->baseSpeed = 60.0f;
            AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, player->sfxSource, 0);
            D_ctx_80177A48[3] = 0.0f;
            /* fallthrough */
        case 1:
            Math_SmoothStepToAngle(&player->zRotBarrelRoll, 0.0f, 0.05f, 1.2f, 0.0001f);
            Math_SmoothStepToAngle(&player->zRotBank, 0.0f, 0.05f, 1.2f, 0.0001f);
            Math_SmoothStepToF(&player->camRoll, 0.0f, 0.1f, 3.0f, 0.0f);
            Math_SmoothStepToAngle(&player->aerobaticPitch, 0.0f, 0.1f, 20.0f, 0.0f);

            if (gCsFrameCount < 60) {
                spf90.x = -100.0f;
                spf90.y = -100.0f;
                spf90.z = -1000.0f;

                sp8C = Math_RadToDeg(Math_Atan2F(spf90.x, spf90.z));
                sp88 = Math_RadToDeg(-Math_Atan2F(spf90.y, sqrtf(SQ(spf90.x) + SQ(spf90.z))));
                if ((sp88 + 40.0f) >= 360.0f) {
                    sp88 -= 360.0f;
                }
                if (sp88 > 180.0f) {
                    sp88 = 0.0f;
                }
                sp84 = Math_SmoothStepToAngle(&player->rot.y, sp8C, 0.5f, 2.0f, 0.0001f) * 30.0f;
                Math_SmoothStepToAngle(&player->rot.x, sp88, 0.1f, 5.0f, 0.0001f);
                Math_SmoothStepToAngle(&player->rot.z, sp84, 0.1f, 5.0f, 0.0001f);
            }

            if (gCsFrameCount == 60) {
                player->draw = false;
                player->baseSpeed = 0.0f;
            }

            Math_SmoothStepToF(&gCsCamEyeX, gBosses[0].obj.pos.x, 0.05f, 1000.0f, 0.001f);
            Math_SmoothStepToF(&gCsCamEyeY, gBosses[0].obj.pos.y, 0.05f, 1000.0f, 0.001f);
            Math_SmoothStepToF(&gCsCamEyeZ, gBosses[0].obj.pos.z + gPathProgress, 0.05f, 10.0f, 0.0001f);

            player->cam.eye.x = gCsCamEyeX;
            player->cam.eye.y = gCsCamEyeY;
            player->cam.eye.z = gCsCamEyeZ;

            gCsCamAtX = gBosses[0].obj.pos.x;
            gCsCamAtY = gBosses[0].obj.pos.y;
            gCsCamAtZ = gBosses[0].obj.pos.z + gPathProgress;

            D_ctx_80177A48[0] = 0.04f;

            if (gCsFrameCount == 140) {
                Area6_8018EA88(actor4);
                Area6_8018EA88(&gActors[5]);
                Area6_8018EA88(&gActors[6]);
                actor4->fwork[4] = 0.5f;
            }

            if (gCsFrameCount >= 200) {
                if (gFillScreenAlpha == 255) {
                    player->csState = 2;
                    Play_ClearObjectData();
                } else {
                    gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
                    gFillScreenAlphaTarget = 255;
                    gFillScreenAlphaStep = 16;
                }
            } else if ((gCsFrameCount == 131) || (gCsFrameCount == 134) || (gCsFrameCount == 137)) {
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
                gFillScreenAlpha = 192;
            } else {
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = gFillScreenAlpha = 0;
            }

            if ((gCsFrameCount == 146) || (gCsFrameCount == 150)) {
                AUDIO_PLAY_SFX(NA_SE_EN_STAR_EXPLOSION, gActors[5].sfxSource, 4);
            }

            if (gCsFrameCount > 146) {
                actor4->iwork[3] -= 4;
                if (actor4->iwork[3] < 0) {
                    actor4->iwork[3] = 0;
                }
                actor4->iwork[7] -= 4;
                if (actor4->iwork[7] < 0) {
                    actor4->iwork[7] = 0;
                }
                Math_SmoothStepToF(&gActors[5].fwork[4], 450.0f, 0.03f, 1000.0f, 1.0f);
                Math_SmoothStepToF(&gActors[5].scale, 450.0f, 0.03f, 1000.0f, 1.0f);
            }

            if (gCsFrameCount > 160) {
                Math_SmoothStepToF(&gActors[6].fwork[4], 350.0f, 0.03f, 1000.0f, 1.0f);
                Math_SmoothStepToF(&gActors[6].scale, 350.0f, 0.03f, 1000.0f, 1.0f);
            }

            if (gCsFrameCount > 140) {
                actor4->obj.pos.x = gActors[5].obj.pos.x = gActors[6].obj.pos.x = gBosses[0].obj.pos.x;
                actor4->obj.pos.y = gActors[5].obj.pos.y = gActors[6].obj.pos.y = gBosses[0].obj.pos.y;
                actor4->obj.pos.z = gActors[5].obj.pos.z = gActors[6].obj.pos.z = gBosses[0].obj.pos.z + 500.0f;
                Math_SmoothStepToF(&actor4->scale, 600.0f, 0.03f, 1000.0f, 0.01f);
            }
            break;

        case 2:
            if (gCsFrameCount < 300) {
                break;
            }

            if (gCsFrameCount == 300) {
                player->draw = true;

                player->pos.x = 0.0f;
                player->pos.y = 200.0f;
                player->pos.z = 1000.0f;

                player->camDist = player->rot.z = player->rot.y = player->rot.x = player->baseSpeed =
                    player->boostSpeed = player->camRoll = player->zRotBank = player->zRotBarrelRoll =
                        player->aerobaticPitch = 0.0f;

                D_bg_8015F984 = (gPathProgress * 0.00004f) + 0.5f;

                Area6_8018EC38(&gActors[1], 0);
                Area6_8018EC38(&gActors[2], 1);
                Area6_8018EC38(&gActors[3], 2);
                Area6_8018EB3C(&gActors[0]);

                D_ctx_80177A48[5] = 300.0f;
                D_ctx_80177A48[4] = 0.0f;
                D_ctx_80177A48[9] = 50.0f;

                player->cam.at.x = gCsCamAtX = player->pos.x;
                player->cam.at.y = gCsCamAtY = 0.0f;
                player->cam.at.z = gCsCamAtZ = player->pos.z + 50.0f + gPathProgress;
            }

            if (gFillScreenAlpha != 0) {
                gFillScreenAlphaTarget = 0;
                gFillScreenAlphaStep = 4;
            } else {
                player->csState = 3;
            }

        case 3:
            Math_SmoothStepToF(&player->pos.y, 0.0f, 0.01f, 10.0f, 0.001f);
            Math_SmoothStepToF(&gActors[1].obj.pos.y, 40.0f, 0.01f, 10.0f, 0.001f);
            Math_SmoothStepToF(&gActors[2].obj.pos.y, 40.0f, 0.01f, 10.0f, 0.001f);
            Math_SmoothStepToF(&gActors[3].obj.pos.y, 88.0f, 0.01f, 10.0f, 0.001f);
            Math_SmoothStepToF(&gActors[0].obj.pos.y, 60.0f, 0.01f, 2.0f, 0.001f);

            if (gCsFrameCount < 1077) {
                D_ctx_80177A48[1] = player->pos.x;
                D_ctx_80177A48[3] = player->pos.z;
            }

            if (gCsFrameCount >= 940) {
                Math_SmoothStepToF(&D_ctx_80177A48[9], 0.0f, 0.01f, 1000.0f, 0.001f);
            }

            if (gCsFrameCount < 1077) {
                D_ctx_80177A48[4] = D_ctx_80177A48[4] + 0.3f;
                if (D_ctx_80177A48[4] >= 360.0f) {
                    D_ctx_80177A48[4] = D_ctx_80177A48[4] - 360.0f;
                }
                if (D_ctx_80177A48[4] < 0.0f) {
                    D_ctx_80177A48[4] = D_ctx_80177A48[4] + 360.0f;
                }
                gCsCamAtX = player->pos.x;
                gCsCamAtY = 0.0f;
                gCsCamAtZ = D_ctx_80177A48[9] + player->pos.z + gPathProgress;
                D_ctx_80177A48[0] = 0.008f;
            } else {
                Math_SmoothStepToAngle(&D_ctx_80177A48[4], 0.0f, 0.1f, 10.0f, 0.001f);
                Math_SmoothStepToF(&D_ctx_80177A48[5], 0.0f, 0.1f, 1000.0f, 0.001f);
                D_bg_8015F984 -= 0.005f;
                gCsCamAtX += 2.0f;
                player->cam.at.x = gCsCamAtX = player->pos.x;
                player->cam.at.y = gCsCamAtY = 0.0f;
                player->cam.at.z = gCsCamAtZ = D_ctx_80177A48[9] + player->pos.z + gPathProgress;
            }

            sp78.x = 0.0f;
            sp78.y = 0.0f;
            sp78.z = D_ctx_80177A48[5];

            Matrix_Translate(gCalcMatrix, D_ctx_80177A48[1], 0.0f, D_ctx_80177A48[3] + gPathProgress, MTXF_NEW);
            Matrix_RotateY(gCalcMatrix, -(D_ctx_80177A48[4] * M_DTOR), MTXF_APPLY);
            Matrix_MultVec3f(gCalcMatrix, &sp78, &sp6C);

            player->cam.eye.x = gCsCamEyeX = sp6C.x;
            player->cam.eye.y = gCsCamEyeY = sp6C.y;
            player->cam.eye.z = gCsCamEyeZ = sp6C.z;

            if (gCsFrameCount == 1076) {
                Object_Kill(&gActors[0].obj, gActors[0].sfxSource);
                player->unk_190 = 2.0f;
                player->unk_194 = 5.0f;
                AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, player->sfxSource, 0);
            }

            if (gCsFrameCount >= 1090) {
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
                gFillScreenAlphaTarget = 255;
                gFillScreenAlphaStep = 8;

                if (gFillScreenAlpha == 255) {
                    gLeveLClearStatus[LEVEL_AREA_6] = Play_CheckMedalStatus(300) + 1;

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
                    gSavedGoldRingCount[0] = gGoldRingCount[0];

                    Audio_StopPlayerNoise(0);
                    Audio_KillSfxBySource(player->sfxSource);

                    Play_ClearObjectData();

                    gNextGameState = GSTATE_PLAY;
                    gNextLevel = LEVEL_VENOM_2;

                    HUD_Bolse_Area6_SaveData();
                }
            }

            if (gCsFrameCount == 1040) {
                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 80);
                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 80);
            }
            break;
    }

    switch (gCsFrameCount) {
        case 380:
            AUDIO_PLAY_BGM(NA_BGM_COURSE_CLEAR);
            break;

        case 550:
            gLevelClearScreenTimer = 100;
            break;

        case 700:
            gShowLevelClearStatusScreen = true;
            break;

        case 900:
            gShowLevelClearStatusScreen = false;
            break;

        case 940:
            Radio_PlayMessage(gMsg_ID_7093, RCID_FOX);
            break;

        case 1070:
            gActors[1].fwork[29] = 5.0f;
            AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, gActors[1].sfxSource, 0);
            break;

        case 1072:
            gActors[2].fwork[29] = 5.0f;
            AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, gActors[2].sfxSource, 0);
            break;

        case 1074:
            gActors[3].fwork[29] = 5.0f;
            AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, gActors[3].sfxSource, 0);
            break;
    }

    if (gCsFrameCount >= 1070) {
        Math_SmoothStepToF(&gActors[1].fwork[0], 50.0f, 0.1f, 1000.0f, 0.001f);
    }
    if (gCsFrameCount >= 1072) {
        Math_SmoothStepToF(&gActors[2].fwork[0], 50.0f, 0.1f, 1000.0f, 0.001f);
    }
    if (gCsFrameCount >= 1074) {
        Math_SmoothStepToF(&gActors[3].fwork[0], 50.0f, 0.1f, 1000.0f, 0.001f);
    }
    if (gCsFrameCount >= 1076) {
        Math_SmoothStepToF(&player->baseSpeed, 50.0f, 0.1f, 1000.0f, 0.001f);
    }

    Matrix_RotateY(gCalcMatrix, (player->rot.y + player->yRot_114 + 180.0f) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -(player->rot.x * M_DTOR), MTXF_APPLY);

    sp78.x = 0.0f;
    sp78.y = 0.0f;
    sp78.z = player->baseSpeed;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp78, &sp6C);

    player->vel.x = sp6C.x;
    player->vel.z = sp6C.z;
    player->vel.y = sp6C.y;

    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;
    player->pos.z += player->vel.z;
    player->trueZpos = player->pos.z;
    player->bankAngle = player->rot.z + player->zRotBank + player->zRotBarrelRoll;

    Math_SmoothStepToF(&player->cam.eye.x, gCsCamEyeX, D_ctx_80177A48[0], 50000.0f, 0.0001f);
    Math_SmoothStepToF(&player->cam.eye.y, gCsCamEyeY, D_ctx_80177A48[0], 50000.0f, 0.0001f);
    Math_SmoothStepToF(&player->cam.eye.z, gCsCamEyeZ, D_ctx_80177A48[0], 50000.0f, 0.0001f);

    Math_SmoothStepToF(&player->cam.at.x, gCsCamAtX, D_ctx_80177A48[0], 50000.0f, 0.0001f);
    Math_SmoothStepToF(&player->cam.at.y, gCsCamAtY, D_ctx_80177A48[0], 50000.0f, 0.0001f);
    Math_SmoothStepToF(&player->cam.at.z, gCsCamAtZ, D_ctx_80177A48[0], 50000.0f, 0.0001f);
}
