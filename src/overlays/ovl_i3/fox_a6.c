/*
 * File: fox_a6.c
 * System: Area 6
 * Description: Level: Area 6
 */

#include "global.h"
#include "assets/ast_area_6.h"

void Area6_8018A1B0(Boss* bossA6, s32 arg1);
void Area6_8018A2C4(Boss* bossA6);
void Area6_8018A464(Boss* bossA6, s32 arg1);
void Area6_8018B9BC(Boss* bossA6);

// f32 bossA6hit1[] = {
//     10.0f,
//     { { 455.0f, 108.0f }, { 0.0f, 120.0f }, { 0.0f, 120.0f } },
//     {
//         { { 0.0f, 195.0f }, { 0.0f, 147.0f }, { 0.0f, 153.0f } },
//         { { 0.0f, 195.0f }, { 0.0f, 147.0f }, { 0.0f, 153.0f } },
//         { { 0.0f, 195.0f }, { 0.0f, 147.0f }, { 0.0f, 153.0f } },
//     },
//     {
//         { { 0.0f, 50.0f }, { 0.0f, 110.0f }, { 0.0f, 107.0f } },
//         { { 0.0f, 50.0f }, { 0.0f, 110.0f }, { 0.0f, 107.0f } },
//         { { 0.0f, 50.0f }, { 0.0f, 110.0f }, { 0.0f, 107.0f } },
//     },
//     { {
//           200000.0f,
//           { 0.0f, 0.0f, 330.0f },
//           { { 317.0f, 282.0f }, { -10.0f, 325.0f }, { -217.0f, 187.0f } },
//       },
//       {
//           200000.0f,
//           { 0.0f, 0.0f, 90.0f },
//           { { 317.0f, 282.0f }, { -10.0f, 325.0f }, { -217.0f, 187.0f } },
//       },
//       {
//           200000.0f,
//           { 0.0f, 0.0f, 210.0f },
//           { { 317.0f, 282.0f }, { -10.0f, 325.0f }, { -217.0f, 187.0f } },
//       } },
// };

// f32 bossA6hit2[] = {
//     15.0f,
//     { { 455.0f, 108.0f }, { 0.0f, 120.0f }, { 0.0f, 120.0f } },
//     {
//         { { 0.0f, 195.0f }, { 0.0f, 147.0f }, { 0.0f, 153.0f } },
//         { { 0.0f, 195.0f }, { 0.0f, 147.0f }, { 0.0f, 153.0f } },
//         { { 0.0f, 195.0f }, { 0.0f, 147.0f }, { 0.0f, 153.0f } },
//     },
//     {
//         { { 0.0f, 50.0f }, { 0.0f, 110.0f }, { 0.0f, 107.0f } },
//         { { 0.0f, 50.0f }, { 0.0f, 110.0f }, { 0.0f, 107.0f } },
//         { { 0.0f, 50.0f }, { 0.0f, 110.0f }, { 0.0f, 107.0f } },
//     },
//     { { 93.0f, 262.0f }, { 0.0f, 330.0f }, { 0.0f, 341.0f } },
//     { {
//           200000.0f,
//           { 0.0f, 0.0f, 330.0f },
//           { { -188.0f, 90.0f }, { 0.0f, 332.0f }, { -960.0f, 302.0f } },
//       },
//       {
//           200000.0f,
//           { 0.0f, 0.0f, 90.0f },
//           { { -188.0f, 90.0f }, { 0.0f, 332.0f }, { -960.0f, 302.0f } },
//       },
//       {
//           200000.0f,
//           { 0.0f, 0.0f, 210.0f },
//           { { -188.0f, 90.0f }, { 0.0f, 332.0f }, { -960.0f, 302.0f } },
//       } },
//     { {
//           200000.0f,
//           { 0.0f, 0.0f, 330.0f },
//           { { -192.0f, 67.0f }, { 0.0f, 90.0f }, { -575.0f, 187.0f } },
//       },
//       {
//           200000.0f,
//           { 0.0f, 0.0f, 90.0f },
//           { { -192.0f, 67.0f }, { 0.0f, 90.0f }, { -575.0f, 187.0f } },
//       },
//       {
//           200000.0f,
//           { 0.0f, 0.0f, 210.0f },
//           { { -192.0f, 67.0f }, { 0.0f, 90.0f }, { -575.0f, 187.0f } },
//       } },
//     {
//         200000.0f,
//         { 0.0f, 0.0f, 0.0f },
//         { { 74.0f, 12.0f }, { -2.0f, 25.0f }, { -1.0f, 26.0f } },
//     },
// };

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
} BossA6swork;

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
} BossA6fwork;

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
} BossA6vwork;

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
} BossA6bsswork;

typedef struct {
    f32 r[3];
    f32 g[3];
    f32 b[3];
    f32 unk_24;
    f32 unk_28[3];
    f32 unk_34;
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
f32 D_i3_801BF454[4][4] = {
    { 255.0f, 0.0f, 0.0f, 0.0f },
    { 255.0f, 255.0f, 0.0f, 0.0f },
    { 0.0f, 255.0f, 255.0f, 0.0f },
    { 144.0f, 255.0f, 144.0f, 0.0f },
};
f32 D_i3_801BF494[12] = {
    -90.0f, 30.0f, 26.0f, 22.0f, 18.0f, 11.0f, 8.0f, 5.0f, 3.0f, 2.0f, 1.0f, 0.0f,
};

void Area6_80187530(Actor* actor, f32 xPos, f32 yPos, f32 zPos, f32 fwork6, f32 xRot, f32 yRot, s32 timer0BC,
                    s32 unk0B4) {

    (void) "おん\n";
    (void) "おふ\n";
    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_191;
    actor->obj.pos.x = xPos;
    actor->obj.pos.y = yPos;
    actor->obj.pos.z = zPos;
    actor->obj.rot.x = xRot;
    actor->obj.rot.y = yRot;
    actor->timer_0BC = timer0BC;
    actor->timer_0BE = 20;
    actor->unk_0B4 = unk0B4;
    actor->fwork[5] = fwork6;
    Object_SetInfo(&actor->info, actor->obj.id);
    func_effect_8007A6F0(&actor->obj.pos, 0x2903201B);
}

void Area6_801875E4(f32 xPos, f32 yPos, f32 zPos, f32 fwork6, f32 xRot, f32 yRot, s32 timer0BC, s32 unk0B4) {
    s32 i;
    Actor* actor;

    for (i = 0, actor = gActors; i < ARRAY_COUNT(gActors); i++, actor++) {
        if (actor->obj.status == OBJ_FREE) {
            Area6_80187530(actor, xPos, yPos, zPos, fwork6, xRot, yRot, timer0BC, unk0B4);
            D_i3_801C2250[A6_BSS_11] = i + 1;
            break;
        }
    }
}

void Area6_8018767C(Effect* effect) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = OBJ_EFFECT_395;
    effect->obj.pos.x = gBosses[0].obj.pos.x;
    effect->obj.pos.y = gBosses[0].obj.pos.y;
    effect->obj.pos.z = gBosses[0].obj.pos.z + 250.0f;
    effect->state = 8;
    effect->scale2 = 1.0f;
    Object_SetInfo(&effect->info, effect->obj.id);
}

void Area6_80187704(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Area6_8018767C(&gEffects[i]);
            break;
        }
    }
}

void Area6_BossA6_Init(BossA6* this) {
    Hitbox* hitbox;
    s32 i;

    gBossActive = 1;
    D_game_80161A44 = 25000.0f;
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
    AUDIO_PLAY_SFX(0x11002050, this->sfxSource, 4);
}

#ifdef NON_MATCHING
// var_s0 = D_i3_801C2250[A6_BSS_9]; is using the wrong variable, but unclear what correct one is.
// https://decomp.me/scratch/P3kGr
void Area6_80187944(Boss* bossA6) {
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
    Vec3f spC8[5];
    Vec3f spA4[3];
    Vec3f sp98;
    Vec3f sp8C;
    Effect* effect;

    gBossFrameCount++;
    if ((bossA6->state < 6) || ((bossA6->state >= 8) && (bossA6->state < 12))) {
        bossA6->obj.rot.y = RAD_TO_DEG(Math_Atan2F(gPlayer[0].camEye.x - bossA6->obj.pos.x,
                                                   gPlayer[0].camEye.z - (bossA6->obj.pos.z + D_ctx_80177D20)));
        bossA6->obj.rot.x =
            RAD_TO_DEG(-Math_Atan2F(gPlayer[0].camEye.y - bossA6->obj.pos.y,
                                    sqrtf(SQ(gPlayer[0].camEye.z - (bossA6->obj.pos.z + D_ctx_80177D20)) +
                                          SQ(gPlayer[0].camEye.x - bossA6->obj.pos.x))));
    }
    Matrix_RotateY(gCalcMatrix, bossA6->obj.rot.y * M_DTOR, 0);
    Matrix_RotateX(gCalcMatrix, bossA6->obj.rot.x * M_DTOR, 1);
    Matrix_RotateZ(gCalcMatrix, bossA6->obj.rot.z * M_DTOR, 1);
    if ((bossA6->dmgType != DMG_NONE) && (bossA6->health > 0)) {
        bossA6->dmgType = DMG_NONE;
        if (bossA6->fwork[A6_FWK_0] > 5.0f) {
            if ((bossA6->dmgPart == 0) && (bossA6->swork[A6_SWK_25] == 0) && (bossA6->fwork[A6_FWK_29] < 30.0f)) {
                bossA6->timer_05C = 15;
                bossA6->health -= bossA6->damage;

                if (bossA6->health < 390) {
                    AUDIO_PLAY_SFX(0x2943500F, bossA6->sfxSource, 4);
                } else {
                    AUDIO_PLAY_SFX(0x29034003, bossA6->sfxSource, 4);
                }
                if (bossA6->health <= 0) {
                    bossA6->health = 0;
                    func_boss_80042EC0(bossA6);
                    Radio_PlayMessage(gMsg_ID_15252, RCID_SLIPPY);
                    D_ctx_8017796C = -1;
                    D_bg_8015F984 = (D_ctx_80177D20 * 0.00004f) + 0.5f;
                    AUDIO_PLAY_SFX(0x2940D09A, bossA6->sfxSource, 4);
                    gShowBossHealth = 0;
                    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 40);
                    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 40);
                    bossA6->fwork[A6_FWK_5] = 5.0f;
                    bossA6->fwork[A6_FWK_3] = -20000.0f;
                    bossA6->fwork[A6_FWK_1] = 170.0f;
                    bossA6->vel.z = -20.0f;
                    Matrix_MultVec3f(gCalcMatrix, &D_i3_801BECE0, &spA4[0]);
                    Matrix_MultVec3f(gCalcMatrix, &D_i3_801BECEC, &spA4[1]);
                    Matrix_MultVec3f(gCalcMatrix, &D_i3_801BECF8, &spA4[2]);
                    for (i = 0; i < 3; i++) {
                        func_effect_8007D0E0(spA4[i].x + bossA6->obj.pos.x, spA4[i].y + bossA6->obj.pos.y,
                                             spA4[i].z + bossA6->obj.pos.z, 10.0f);
                    }
                    bossA6->timer_052 = 170;

                    D_i3_801C2250[A6_BSS_2_0] = D_i3_801C2250[A6_BSS_2_1] = D_i3_801C2250[A6_BSS_2_2] =
                        bossA6->swork[A6_SWK_33 + 0] = bossA6->swork[A6_SWK_33 + 1] = bossA6->swork[A6_SWK_33 + 2] = 0;
                    gScreenFlashTimer = 4;
                    bossA6->state = 11;
                    AUDIO_PLAY_SFX(0x2940C00A, bossA6->sfxSource, 4);
                    AUDIO_PLAY_SFX(0x3143402E, bossA6->sfxSource, 4);
                }
            }
            if (((bossA6->dmgPart == 4) || (bossA6->dmgPart == 5) || (bossA6->dmgPart == 6)) &&
                (bossA6->swork[A6_SWK_25] != 0)) {
                Area6_8018B9BC(bossA6);
            }
        }
        if ((bossA6->dmgPart == 1) || (bossA6->dmgPart == 2) || (bossA6->dmgPart == 3)) {
            Area6_8018A2C4(bossA6);
        }
        if (bossA6->dmgPart >= 7) {
            AUDIO_PLAY_SFX(0x29121007, bossA6->sfxSource, 4);
        }
    }
    for (i = 0; i < 3; i++) {
        var_s0 = (bossA6->swork[A6_SWK_15 + i] / 10) - 1;
        if (var_s0 < 0) {
            var_s0 = 0;
        }
        Math_SmoothStepToF(&D_i3_801C22F0.r[i], D_i3_801BECB0[var_s0][0], 1.0f, 10.0f, 0);
        Math_SmoothStepToF(&D_i3_801C22F0.g[i], D_i3_801BECB0[var_s0][1], 1.0f, 10.0f, 0);
        Math_SmoothStepToF(&D_i3_801C22F0.b[i], D_i3_801BECB0[var_s0][2], 1.0f, 10.0f, 0);
    }
    if ((bossA6->swork[A6_SWK_15 + 0] == 0) && (bossA6->swork[A6_SWK_15 + 1] == 0) &&
        (bossA6->swork[A6_SWK_15 + 2] == 0) && (bossA6->fwork[A6_FWK_0] != 0) && ((gGameFrameCount % 2) == 0)) {
        func_effect_8007C120(bossA6->obj.pos.x, bossA6->obj.pos.y, bossA6->obj.pos.z + 200.0f, bossA6->vel.x,
                             bossA6->vel.y, bossA6->vel.z, 0.3f, 1);
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
    if ((bossA6->state >= 3) && (bossA6->state < 5) && (bossA6->fwork[A6_FWK_28] == 0.0f)) {
        Math_SmoothStepToAngle(&bossA6->fwork[A6_FWK_9], bossA6->fwork[A6_FWK_32], 0.05f, 0.02f, 0.00001f);
        Math_SmoothStepToAngle(&bossA6->obj.rot.z, bossA6->fwork[A6_FWK_8], 0.05f, bossA6->fwork[A6_FWK_9], 0.00001f);
        if (bossA6->swork[A6_SWK_25] >= 2) {
            if (((gGameFrameCount % 64) == 0) && (Rand_ZeroOne() < 0.5f)) {
                bossA6->fwork[A6_FWK_6] = RAND_FLOAT_CENTERED(500.0f) + gPlayer[0].camEye.x;
            }
            if (((gGameFrameCount % 64) == 0) && (Rand_ZeroOne() < 0.5f)) {
                bossA6->fwork[A6_FWK_7] = RAND_FLOAT_CENTERED(500.0f) + gPlayer[0].camEye.y;
            }
        } else {
            if (((gGameFrameCount % 32) == 0) && (Rand_ZeroOne() < 0.7f)) {
                bossA6->fwork[A6_FWK_6] = RAND_FLOAT_CENTERED(1000.0f) + gPlayer[0].camEye.x;
                bossA6->fwork[A6_FWK_30] = 0.0f;
            }
            if (((gGameFrameCount % 32) == 0) && (Rand_ZeroOne() < 0.7f)) {
                bossA6->fwork[A6_FWK_7] = RAND_FLOAT_CENTERED(1000.0f) + gPlayer[0].camEye.y;
                bossA6->fwork[A6_FWK_31] = 0.0f;
            }
        }
    }
    if (bossA6->state != 0) {
        Math_SmoothStepToF(&bossA6->fwork[A6_FWK_4], bossA6->fwork[A6_FWK_5], 0.1f, 2.0f, 0.00001f);
        Math_SmoothStepToF(&bossA6->obj.pos.z, gPlayer[0].camEye.z - D_ctx_80177D20 + bossA6->fwork[A6_FWK_3], 0.1f,
                           bossA6->fwork[A6_FWK_4], 0.00001f);
        if (bossA6->state < 5) {
            sp120 = 2.0f;
            if (bossA6->swork[A6_SWK_25] == 1) {
                sp120 = 50.0f;
            }
            Math_SmoothStepToF(&bossA6->fwork[A6_FWK_30], sp120, 0.1f, 1.0f, 0.00001f);
            Math_SmoothStepToF(&bossA6->fwork[A6_FWK_31], sp120, 0.1f, 1.0f, 0.00001f);
            Math_SmoothStepToF(&bossA6->obj.pos.x, bossA6->fwork[A6_FWK_6], 0.2f, bossA6->fwork[A6_FWK_30], 0.00001f);
            Math_SmoothStepToF(&bossA6->obj.pos.y, bossA6->fwork[A6_FWK_7], 0.2f, bossA6->fwork[A6_FWK_31], 0.00001f);
        }
        Math_SmoothStepToAngle(&bossA6->fwork[A6_FWK_0], bossA6->fwork[A6_FWK_1], 0.2f, bossA6->fwork[A6_FWK_2],
                               0.00001f);
    }
    Math_SmoothStepToF(&bossA6->fwork[A6_FWK_10 + 0], bossA6->fwork[A6_FWK_13 + 0], 0.1f, bossA6->fwork[A6_FWK_16 + 0],
                       0.0001f);
    Math_SmoothStepToF(&bossA6->fwork[A6_FWK_10 + 1], bossA6->fwork[A6_FWK_13 + 1], 0.1f, bossA6->fwork[A6_FWK_16 + 1],
                       0.0001f);
    Math_SmoothStepToF(&bossA6->fwork[A6_FWK_10 + 2], bossA6->fwork[A6_FWK_13 + 2], 0.1f, bossA6->fwork[A6_FWK_16 + 2],
                       0.0001f);
    Math_SmoothStepToF(&bossA6->fwork[A6_FWK_19 + 0], bossA6->fwork[A6_FWK_22 + 0], 0.1f, 10.0f, 0.00001f);
    Math_SmoothStepToF(&bossA6->fwork[A6_FWK_19 + 1], bossA6->fwork[A6_FWK_22 + 1], 0.1f, 10.0f, 0.00001f);
    Math_SmoothStepToF(&bossA6->fwork[A6_FWK_19 + 2], bossA6->fwork[A6_FWK_22 + 2], 0.1f, 10.0f, 0.00001f);
    if (bossA6->state > 10) {
        bossA6->obj.rot.z += bossA6->fwork[A6_FWK_28];
        bossA6->obj.rot.z = Math_ModF(bossA6->obj.rot.z, 360.0f);
        Math_SmoothStepToF(&bossA6->fwork[A6_FWK_28], 5.0f, 0.1f, 0.2f, 0.0001f);
        for (i = 0; i < 10; i++) {
            func_effect_80079618(bossA6->obj.pos.x + RAND_FLOAT_CENTERED(500.0f),
                                 bossA6->obj.pos.y + RAND_FLOAT_CENTERED(500.0f),
                                 bossA6->obj.pos.z + RAND_FLOAT_CENTERED(100.0f), RAND_FLOAT(4.0f) + 1.0f);
        }
        if (bossA6->timer_05C == 0) {
            bossA6->timer_05C = 15;
        }
        if (((gGameFrameCount % 2) == 0)) {
            Matrix_MultVec3f(gCalcMatrix, &D_i3_801BED04, &spC8[0]);
            Matrix_MultVec3f(gCalcMatrix, &D_i3_801BED10, &spC8[1]);
            Matrix_MultVec3f(gCalcMatrix, &D_i3_801BED1C, &spC8[2]);
            Matrix_MultVec3f(gCalcMatrix, &D_i3_801BED28, &spC8[3]);
            Matrix_MultVec3f(gCalcMatrix, &D_i3_801BED34, &spC8[4]);
            for (i = 0; i < 5; i++) {
                var_s0 = RAND_FLOAT_CENTERED(300.0f);
                if (i == 0) {
                    var_s0 = RAND_FLOAT_CENTERED(100.0f);
                }
                func_effect_8007D0E0(bossA6->obj.pos.x + var_s0 + spC8[i].x, bossA6->obj.pos.y + var_s0 + spC8[i].y,
                                     bossA6->obj.pos.z + spC8[i].z, 10.0f);
            }
        }
        if (((gGameFrameCount % 32) == 0)) {
            func_effect_8007C120(bossA6->obj.pos.x, bossA6->obj.pos.y, bossA6->obj.pos.z + 300.0f, bossA6->vel.x,
                                 bossA6->vel.y, bossA6->vel.z, 0.5f, 70);
        }
    }
    if (((gGameFrameCount % 16) == 0)) {
        dz_114 = fabsf(bossA6->fwork[A6_FWK_3] / -1700.0f);
        if (dz_114 < 1.0f) {
            dz_114 = 1.0f;
        }
        if (dz_114 > 3.0f) {
            dz_114 = 3.0f;
        }
        for (i = 0; i < 3; i++) {
            sp120 = dz_114;
            if (bossA6->swork[A6_SWK_18 + i] != 0) {
                sp120 = 1.0f;
            }
            A6_HIT_1_2(bossA6, i)->z.size = 195.0f * sp120;
            A6_HIT_1_2(bossA6, i)->y.size = 147.0f * sp120;
            A6_HIT_1_2(bossA6, i)->x.size = 153.0f * sp120;
        }
    }
    switch (bossA6->state) {
        case 0:
            bossA6->info.hitbox[0] = 0;

            dx_11C = gPlayer[0].pos.x - bossA6->obj.pos.x;
            dy_118 = gPlayer[0].pos.y - bossA6->obj.pos.y;
            dz_114 = gPlayer[0].pos.z - 700.0f - bossA6->obj.pos.z;
            sp104 = 10.0f;
            if ((bossA6->timer_050 != 0) && (bossA6->timer_050 < 200)) {
                dx_11C = gPlayer[0].camEye.x - bossA6->obj.pos.x;
                dy_118 = gPlayer[0].camEye.y - bossA6->obj.pos.y;
                dz_114 = gPlayer[0].camEye.z - D_ctx_80177D20 + bossA6->fwork[A6_FWK_3] - bossA6->obj.pos.z;
                sp104 = 100.0f;
            }
            yaw_10C = Math_RadToDeg(Math_Atan2F(dx_11C, dz_114));
            pitch_110 = Math_RadToDeg(-Math_Atan2F(dy_118, sqrtf(SQ(dx_11C) + SQ(dz_114))));
            Math_SmoothStepToAngle(&bossA6->unk_078.y, yaw_10C, 1.0f, sp104, 0.00001f);
            Math_SmoothStepToAngle(&bossA6->unk_078.x, pitch_110, 1.0f, sp104, 0.00001f);
            Matrix_RotateY(gCalcMatrix, bossA6->unk_078.y * M_DTOR, 0);
            Matrix_RotateX(gCalcMatrix, bossA6->unk_078.x * M_DTOR, 1);
            sp98.x = sp98.y = 0.0f;
            sp98.z = 30.0f;
            Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp98, &sp8C);
            bossA6->vel.x = sp8C.x;
            bossA6->vel.y = sp8C.y;
            sp98.x = sp98.y = 0.0f;
            sp98.z = 60.0f;
            Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp98, &sp8C);
            bossA6->vel.z = sp8C.z;
            bossA6->fwork[A6_FWK_33] += 30.0f;
            if (bossA6->timer_050 == 0) {
                Math_SmoothStepToF(&D_i3_801C22F0.unk_24, 0.0f, 0.1f, 1.0f, 0);
                if (D_i3_801C22F0.unk_24 < 1.0f) {
                    D_i3_801C22F0.unk_24 = 0.0f;
                    Audio_KillSfxBySource(bossA6->sfxSource);
                    AUDIO_PLAY_SFX(0x19004051, bossA6->sfxSource, 4);
                    bossA6->timer_050 = 20;
                    bossA6->obj.pos.z = gPlayer[0].camEye.z - D_ctx_80177D20 + bossA6->fwork[A6_FWK_3];
                    bossA6->fwork[A6_FWK_6] = bossA6->obj.pos.x = gPlayer[0].camEye.x;
                    bossA6->fwork[A6_FWK_7] = bossA6->obj.pos.y = gPlayer[0].camEye.y;
                    bossA6->state = 2;
                    bossA6->vel.x = 0.0f;
                    bossA6->vel.y = 0.0f;
                    bossA6->vel.z = -40.0f;

                    AUDIO_PLAY_SFX(0x39408092, bossA6->sfxSource, 4);
                }
            }
            break;
        case 1:
            Math_SmoothStepToF(D_ctx_801779A8, 10.0f, 1.0f, 5.0f, 0.0f);
            bossA6->info.hitbox[0] = 0;
            Math_SmoothStepToAngle(&bossA6->obj.rot.z, 0.0f, 1.0f, 10.0f, 0.0001f);
            if (bossA6->obj.rot.z < 1.0f) {
                if (D_i3_801C2250[A6_BSS_27] == 0) {
                    AUDIO_PLAY_SFX(0x39408091, bossA6->sfxSource, 4);
                    D_i3_801C2250[A6_BSS_27] = 1;
                }
                bossA6->obj.rot.z = 0.0f;
                Math_SmoothStepToF(&D_i3_801C22F0.unk_24, 0.0f, 0.1f, 5.0f, 0.0f);
                Math_SmoothStepToF(&bossA6->fwork[A6_FWK_34], 2.0f, 0.1f, 0.1f, 0.0f);
                Math_SmoothStepToF(&bossA6->fwork[A6_FWK_35], 1.2f, 0.1f, 0.1f, 0.0f);
                if (D_i3_801C22F0.unk_24 < 1.0f) {
                    bossA6->fwork[A6_FWK_6] = RAND_FLOAT_CENTERED(1000.0f) + gPlayer[0].camEye.x;
                    bossA6->fwork[A6_FWK_7] = RAND_FLOAT_CENTERED(1000.0f) + gPlayer[0].camEye.y;
                    bossA6->fwork[A6_FWK_3] = -3700.0f + RAND_FLOAT_CENTERED(3000.0f);
                    bossA6->fwork[A6_FWK_34] = 2.0f;
                    bossA6->fwork[A6_FWK_35] = 1.2f;
                    if ((bossA6->swork[A6_SWK_37] == 0) && (bossA6->swork[A6_SWK_33 + 0] == 0) &&
                        (bossA6->swork[A6_SWK_33 + 1] == 0) && (bossA6->swork[A6_SWK_33 + 2] == 0) &&
                        (bossA6->swork[A6_SWK_27 + 0] == 0) && (bossA6->swork[A6_SWK_27 + 1] == 0) &&
                        (bossA6->swork[A6_SWK_27 + 2] == 0)) {
                        bossA6->swork[A6_SWK_37] = 1;
                    }
                    if (bossA6->swork[A6_SWK_37] != 0) {
                        bossA6->swork[A6_SWK_18 + 0] = bossA6->swork[A6_SWK_18 + 1] = bossA6->swork[A6_SWK_18 + 2] = 3;
                        bossA6->fwork[A6_FWK_3] = -1700.0f;
                        if ((bossA6->swork[A6_SWK_25] != 1) && (D_i3_801C2250[A6_BSS_0] != 2)) {
                            bossA6->fwork[A6_FWK_3] = RAND_FLOAT_CENTERED(1000.0f) + -3700.0f;
                        }
                        bossA6->obj.pos.z = gPlayer[0].camEye.z - D_ctx_80177D20 + bossA6->fwork[A6_FWK_3];
                        bossA6->fwork[A6_FWK_6] = bossA6->obj.pos.x = gPlayer[0].camEye.x;
                        bossA6->fwork[A6_FWK_7] = bossA6->obj.pos.y = gPlayer[0].camEye.y;
                    }
                    D_i3_801C22F0.unk_24 = 0.0f;
                    bossA6->timer_050 = 50;
                    bossA6->state = 2;
                    D_i3_801C2250[A6_BSS_8] = 0;
                    AUDIO_PLAY_SFX(0x39408092, bossA6->sfxSource, 4);
                }
            }
            break;
        case 2:
            Math_SmoothStepToF(D_ctx_801779A8, 10.0f, 1.0f, 5.0f, 0.0f);
            if (bossA6->timer_050 == 10) {
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
                gFillScreenAlpha = gFillScreenAlphaTarget = 255;
                gFillScreenAlphaTarget = 0;
                gFillScreenAlphaStep = 25;
                gCameraShake = 50;
            }
            if (bossA6->timer_050 == 0) {
                if (D_i3_801C2250[A6_BSS_8] == 0) {
                    D_i3_801C2250[A6_BSS_8] = 1;
                    gFillScreenRed = gFillScreenGreen = gFillScreenBlue = gFillScreenAlpha = 0;
                }
                Math_SmoothStepToF(&D_i3_801C22F0.unk_24, 255.0f, 0.1f, 10.0f, 0.0f);
                Math_SmoothStepToF(&bossA6->fwork[A6_FWK_34], 1.0f, 0.1f, 0.1f, 0.0f);
                Math_SmoothStepToF(&bossA6->fwork[A6_FWK_35], 1.0f, 0.1f, 0.1f, 0.0f);
                if (D_i3_801C22F0.unk_24 > 254.0f) {
                    D_i3_801C22F0.unk_24 = 255.0f;
                    bossA6->info.hitbox[0] = 10;
                    bossA6->fwork[A6_FWK_34] = bossA6->fwork[A6_FWK_35] = 1.0f;
                    switch (bossA6->swork[A6_SWK_38]) {
                        case 0:
                            bossA6->timer_050 = 100;
                            break;
                        case 1:
                            bossA6->timer_050 = 1399;
                            break;
                    }
                    bossA6->swork[A6_SWK_38] = 0;
                    D_i3_801C2250[A6_BSS_28] = 1;
                    bossA6->state = 4;
                    if (bossA6->swork[A6_SWK_37] != 0) {
                        bossA6->timer_050 = 30;
                        bossA6->swork[A6_SWK_37] = 0;
                        bossA6->fwork[A6_FWK_8] = bossA6->fwork[A6_FWK_9] = 0.0f;
                        if (bossA6->swork[A6_SWK_36] < 2) {
                            bossA6->swork[A6_SWK_36]++;
                        }
                        bossA6->state = 3;
                    }
                    if (D_i3_801C2250[A6_BSS_6] != 0) {
                        if (D_i3_801C2250[A6_BSS_0] != 2) {
                            D_i3_801C2250[A6_BSS_0] = 1;
                        } else {
                            D_i3_801C2250[A6_BSS_0] = 0;
                        }
                    }
                    if ((D_i3_801C2250[A6_BSS_6] == 0) || (D_i3_801C2250[A6_BSS_0] == 0)) {
                        bossA6->fwork[A6_FWK_1] = 90.0f;
                        bossA6->fwork[A6_FWK_2] = 2.0f;
                        AUDIO_PLAY_SFX(0x31404066, bossA6->sfxSource, 4);
                        bossA6->info.hitbox = LOAD_ASSET(D_A6_6028578);
                        D_i3_801C2250[A6_BSS_7] = 0;
                    }
                }
            }
            break;
        case 3:
            if (bossA6->timer_050 == 1) {
                Audio_KillSfxBySource(bossA6->sfxSource);
                if (D_i3_801C2250[A6_BSS_7] == 0) {
                    AUDIO_PLAY_SFX(0x31008069, bossA6->sfxSource, 4);
                    D_i3_801C2250[A6_BSS_7] = 1;
                }
            }
            if (D_i3_801C2250[A6_BSS_0] != 0) {
                if (bossA6->swork[A6_SWK_25] == 1) {
                    bossA6->timer_052 = 30;
                    bossA6->state = 5;
                    bossA6->fwork[A6_FWK_1] = 90.0f;
                    bossA6->fwork[A6_FWK_2] = 2.0f;
                    bossA6->fwork[A6_FWK_37] = 300.0f;
                } else {
                    bossA6->timer_052 = 30;
                    bossA6->state = 8;
                }
            } else {
                if ((bossA6->swork[A6_SWK_36] == 3) && (D_i3_801C2250[A6_BSS_29] == 0)) {
                    Radio_PlayMessage(gMsg_ID_7084, RCID_PEPPY);
                    bossA6->swork[A6_SWK_36] = 4;
                    D_i3_801C2250[A6_BSS_29]++;
                    D_i3_801C2250[A6_BSS_29] &= 1;
                }
                if ((bossA6->swork[A6_SWK_30 + 0] != 0) && (bossA6->swork[A6_SWK_30 + 1] != 0) &&
                    (bossA6->swork[A6_SWK_30 + 2] != 0)) {
                    bossA6->timer_050 = 1500;
                    bossA6->fwork[A6_FWK_1] = 0.0f;
                    D_i3_801C2250[A6_BSS_28] = 0;
                    bossA6->state = 4;
                    bossA6->fwork[A6_FWK_2] = 1.0f;
                    bossA6->info.hitbox = LOAD_ASSET(D_A6_6028454);
                    D_i3_801C2250[A6_BSS_6] = 1;
                    Audio_KillSfxBySource(bossA6->sfxSource);
                    AUDIO_PLAY_SFX(0x31404067, bossA6->sfxSource, 4);
                    bossA6->swork[A6_SWK_30 + 0] = bossA6->swork[A6_SWK_30 + 1] = bossA6->swork[A6_SWK_30 + 2] = 0;
                } else if (bossA6->swork[A6_SWK_30 + 0] == 0) {
                    Area6_8018A1B0(bossA6, 0);
                } else if (bossA6->swork[A6_SWK_30 + 1] == 0) {
                    Area6_8018A1B0(bossA6, 1);
                } else if (bossA6->swork[A6_SWK_30 + 2] == 0) {
                    Area6_8018A1B0(bossA6, 2);
                }
            }
            break;
        case 4:
            if (bossA6->timer_050 == 1400) {
                bossA6->swork[A6_SWK_15 + 0] = bossA6->swork[A6_SWK_15 + 1] = bossA6->swork[A6_SWK_15 + 2] = 40;
                if (bossA6->swork[A6_SWK_25] == 0) {
                    bossA6->swork[A6_SWK_25] = 1;
                }
                bossA6->fwork[A6_FWK_3] = RAND_FLOAT_CENTERED(1000.0f) + -3700.0f;
                if (D_i3_801C2250[A6_BSS_28] == 0) {
                    AUDIO_PLAY_SFX(0x39404068, bossA6->sfxSource, 4);
                }
            }
            Math_SmoothStepToF(&bossA6->fwork[A6_FWK_29], 255.0f, 1.0f, 10.0f, 0.0001f);
            if ((bossA6->swork[A6_SWK_36] == 2) && (bossA6->fwork[A6_FWK_0] == 0.0f) &&
                (D_i3_801C2250[A6_BSS_30] == 0)) {
                Radio_PlayMessage(gMsg_ID_7083, RCID_PEPPY);
                bossA6->swork[A6_SWK_36] = 3;
                D_i3_801C2250[A6_BSS_30]++;
                D_i3_801C2250[A6_BSS_30] &= 1;
            }
            if (((gGameFrameCount % 64) == 0)) {
                bossA6->fwork[A6_FWK_8] = RAND_FLOAT(360.0f);
                bossA6->fwork[A6_FWK_9] = 0.0f;
            }
            if ((bossA6->timer_050 == 0) ||
                ((bossA6->swork[A6_SWK_33 + 0] == 0) && (bossA6->swork[A6_SWK_33 + 1] == 0) &&
                 (bossA6->swork[A6_SWK_33 + 2] == 0) && (bossA6->swork[A6_SWK_27 + 0] == 0) &&
                 (bossA6->swork[A6_SWK_27 + 1] == 0) && (bossA6->swork[A6_SWK_27 + 2] == 0))) {
                bossA6->swork[A6_SWK_37] = 1;
                if (D_i3_801C2250[A6_BSS_6] != 0) {
                    bossA6->state = 1;
                    D_i3_801C2250[A6_BSS_27] = 0;
                } else {
                    bossA6->fwork[A6_FWK_1] = 90.0f;
                    bossA6->timer_050 = 30;
                    bossA6->fwork[A6_FWK_8] = bossA6->fwork[A6_FWK_9] = 0;
                    bossA6->fwork[A6_FWK_2] = 2.0f;
                    AUDIO_PLAY_SFX(0x31404066, bossA6->sfxSource, 4);
                    bossA6->info.hitbox = LOAD_ASSET(D_A6_6028578);
                    D_i3_801C2250[A6_BSS_7] = bossA6->swork[A6_SWK_37] = 0;
                    bossA6->state = 3;
                    if (D_i3_801C2250[A6_BSS_6] == 0) {
                        AUDIO_PLAY_BGM(SEQ_ID_A6_BOSS | SEQ_FLAG);
                    }
                }
            } else if (bossA6->swork[A6_SWK_38] != 0) {
                bossA6->timer_052 = 30;
                bossA6->state = 9;
                bossA6->fwork[A6_FWK_28] = 0.0f;
                D_i3_801C2250[A6_BSS_24] = 0;
                D_i3_801C2250[A6_BSS_27] = 0;
                bossA6->timer_050 = 0;
                bossA6->timer_054 = 0;
                D_i3_801C2250[A6_BSS_34] = 1;
            }
            break;
        case 5:
            if (bossA6->timer_050 == 1) {
                Area6_80187704();
                AUDIO_PLAY_SFX(0x39033093, bossA6->sfxSource, 4);
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
            bossA6->obj.pos.z -= bossA6->fwork[A6_FWK_37];
            Math_SmoothStepToF(&bossA6->fwork[A6_FWK_37], 0.0f, 1.0f, 10.0f, 0.00001f);
            Math_SmoothStepToF(&bossA6->fwork[A6_FWK_3], -6000.0f, 10.0f, 100.0f, 0.00001f);
            var_s0 = D_i3_801C2250[A6_BSS_9];
            // sp68 = &D_i3_801BF454[];
            Math_SmoothStepToF(&D_i3_801C22F0.unk_28[0], D_i3_801BF454[var_s0][0], 0.5f, 100.0f, 0.00001f);
            Math_SmoothStepToF(&D_i3_801C22F0.unk_28[2], D_i3_801BF454[var_s0][1], 0.5f, 100.0f, 0.00001f);
            Math_SmoothStepToF(&D_i3_801C22F0.unk_28[1], D_i3_801BF454[var_s0][2], 0.5f, 100.0f, 0.00001f);
            if (((gGameFrameCount % 16) == 0)) {
                D_i3_801C2250[A6_BSS_9]++;
                D_i3_801C2250[A6_BSS_9] &= 3;
            }
            if (bossA6->timer_050 == 0) {
                bossA6->fwork[A6_FWK_1] = 0.0f;
                bossA6->state = 7;
            }
            break;
        case 7:
            effect = &gEffects[bossA6->swork[A6_SWK_39]];
            Math_SmoothStepToF(&D_i3_801C22F0.unk_28[0], 255.0f, 1.0f, 100.0f, 0.00001f);
            Math_SmoothStepToF(&D_i3_801C22F0.unk_28[2], 255.0f, 1.0f, 100.0f, 0.00001f);
            Math_SmoothStepToF(&D_i3_801C22F0.unk_28[1], 255.0f, 1.0f, 100.0f, 0.00001f);
            if (bossA6->fwork[A6_FWK_0] < 10.0f) {
                effect->unk_60.y = 5.0f - ((10.0f - bossA6->fwork[A6_FWK_0]) * 0.3f);
                effect->unk_60.x = 5.0f - ((10.0f - bossA6->fwork[A6_FWK_0]) * 0.3f);
            }
            if (bossA6->fwork[A6_FWK_0] < 1.0f) {
                Math_SmoothStepToF(&effect->unk_60.x, 0.0f, 0.1f, 1.0f, 0.00001f);
                Math_SmoothStepToF(&effect->unk_60.y, 0.0f, 0.1f, 1.0f, 0.00001f);
                Math_SmoothStepToF(&effect->unk_60.z, 0.0f, 1.0f, 2.0f, 0.00001f);
                if (effect->unk_60.z < 0.2f) {
                    D_i3_801C2250[A6_BSS_0] = 2;
                    bossA6->swork[A6_SWK_37] = 1;
                    bossA6->timer_050 = 20;
                    D_i3_801C22F0.unk_28[0] = D_i3_801C22F0.unk_28[2] = D_i3_801C22F0.unk_28[1] = 255.0f;
                    bossA6->state = 1;
                    D_i3_801C2250[A6_BSS_27] = 0;
                    Object_Kill(&effect->obj, effect->sfxSource);
                }
            }
            break;
        case 8:
            if (bossA6->timer_052 == 0) {
                D_i3_801C2250[A6_BSS_24] = 0;
                bossA6->timer_052 = 300;
                bossA6->timer_054 = 0;
                bossA6->state = 9;
                AUDIO_PLAY_SFX(0x11002050, bossA6->sfxSource, 4);
            }
            break;
        case 9:
            if (bossA6->timer_052 == 0) {
                Audio_KillSfxBySource(bossA6->sfxSource);
                AUDIO_PLAY_SFX(0x19004051, bossA6->sfxSource, 4);
                bossA6->timer_054 = 0;
                bossA6->state = 10;
            } else {
                if (D_i3_801C2250[A6_BSS_34] == 0) {
                    bossA6->obj.rot.z += bossA6->fwork[A6_FWK_28];
                    bossA6->obj.rot.z = Math_ModF(bossA6->obj.rot.z, 360.0f);
                    Math_SmoothStepToF(&bossA6->fwork[A6_FWK_28], 20.0f, 0.1f, 0.5f, 0.0001f);
                }
                if (bossA6->timer_054 == 0) {
                    bossA6->timer_054 = 10;
                    if (D_i3_801C2250[A6_BSS_34] == 0) {
                        bossA6->timer_054 = 30;
                    }
                    sp128 = 6;
                    if (bossA6->swork[A6_SWK_25] == 2) {
                        sp128 = 12;
                    }
                    for (var_s0 = 0; var_s0 < sp128; var_s0++) {
                        Matrix_RotateZ(gCalcMatrix, (360.0f / sp128) * M_DTOR, 1);
                        sp98.x = 0.0f;
                        sp98.y = 400.0f;
                        sp98.z = 0.0f;
                        Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp98, &sp8C);
                        yaw_10C = Math_RadToDeg(Math_Atan2F(sp8C.x, sp8C.z));
                        pitch_110 = Math_RadToDeg(-Math_Atan2F(sp8C.y, sqrtf(SQ(sp8C.x) + SQ(sp8C.z))));
                        spf124 = D_i3_801C2250[A6_BSS_12_0 + var_s0] - 1;
                        if (spf124 < 0) {
                            spf124 = 0;
                        }
                        if ((gActors[spf124].obj.status == OBJ_FREE) || (gActors[spf124].obj.id != OBJ_ACTOR_191) ||
                            (D_i3_801C2250[A6_BSS_24] == 0)) {
                            D_i3_801C2250[A6_BSS_12_0 + var_s0] = 0;
                            spf124 = 0;
                            if (bossA6->swork[A6_SWK_25] == 1) {
                                spf124 = 1;
                            }
                            Area6_801875E4(bossA6->obj.pos.x + sp8C.x, bossA6->obj.pos.y + sp8C.y,
                                           bossA6->obj.pos.z + sp8C.z, 25.0f, pitch_110, yaw_10C, 10, spf124);
                            D_i3_801C2250[A6_BSS_12_0 + var_s0] = D_i3_801C2250[A6_BSS_11];
                        }
                    }
                    D_i3_801C2250[A6_BSS_24] = 1;
                }
            }
            break;
        case 10:
            if (D_i3_801C2250[A6_BSS_34] == 0) {
                bossA6->obj.rot.z += bossA6->fwork[A6_FWK_28];
                bossA6->obj.rot.z = Math_ModF(bossA6->obj.rot.z, 360.0f);
                Math_SmoothStepToF(&bossA6->fwork[A6_FWK_28], 0.0f, 0.1f, 0.5f, 0.0001f);
            }
            if (bossA6->fwork[A6_FWK_28] <= 0.1f) {
                if (D_i3_801C2250[A6_BSS_34] == 0) {
                    bossA6->fwork[A6_FWK_28] = 0.0f;
                    D_i3_801C2250[A6_BSS_0] = 2;
                    bossA6->swork[A6_SWK_37] = 1;
                }
                bossA6->timer_050 = 20;
                D_i3_801C2250[A6_BSS_27] = 0;
                D_i3_801C2250[A6_BSS_34] = 0;
                bossA6->state = 1;
            }
            break;
        case 11:
            if ((bossA6->timer_052 == 160) &&
                ((gPlayer[0].state_1C8 == PLAYERSTATE_1C8_3) || (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_5))) {
                gPlayer[0].state_1C8 = PLAYERSTATE_1C8_7;
                gPlayer[0].unk_1D0 = 0;
            }
            if (bossA6->timer_052 < 50) {
                D_ctx_801779A8[0] = 50.0f;
            } else {
                D_ctx_801779A8[0] = 20.0f;
            }
            if (bossA6->timer_052 == 0) {
                gShowBossHealth = 0;
                Object_Kill(&bossA6->obj, bossA6->sfxSource);
            }
            break;
    }
    Area6_8018A464(bossA6, 0);
    Area6_8018A464(bossA6, 1);
    Area6_8018A464(bossA6, 2);
    for (i = 0; i < 5; i++) {
        if (((gGameFrameCount % 4) == 0)) {
            D_i3_801BF280[i] = RAND_FLOAT_CENTERED(10.0f);
            D_i3_801BF2B0[i] = RAND_FLOAT_CENTERED(10.0f);
            D_i3_801BF2E0[i] = RAND_FLOAT_CENTERED(10.0f);
        }
        Math_SmoothStepToF(&D_i3_801BF1F0[i], D_i3_801BF280[i], 1.0f, 5.0f, 0.001f);
        Math_SmoothStepToF(&D_i3_801BF220[i], D_i3_801BF2B0[i], 1.0f, 5.0f, 0.001f);
        Math_SmoothStepToF(&D_i3_801BF250[i], D_i3_801BF2E0[i], 1.0f, 5.0f, 0.001f);
    }
    A6_HIT_4(bossA6, 0)->z.offset = bossA6->vwork[A6_VWK_4].z;
    A6_HIT_4(bossA6, 0)->y.offset = bossA6->vwork[A6_VWK_4].y;
    A6_HIT_4(bossA6, 0)->x.offset = bossA6->vwork[A6_VWK_4].x;
    A6_HIT_4(bossA6, 1)->z.offset = bossA6->vwork[A6_VWK_5].z;
    A6_HIT_4(bossA6, 1)->y.offset = bossA6->vwork[A6_VWK_5].y;
    A6_HIT_4(bossA6, 1)->x.offset = bossA6->vwork[A6_VWK_5].x;
    A6_HIT_4(bossA6, 2)->z.offset = bossA6->vwork[A6_VWK_6].z;
    A6_HIT_4(bossA6, 2)->y.offset = bossA6->vwork[A6_VWK_6].y;
    A6_HIT_4(bossA6, 2)->x.offset = bossA6->vwork[A6_VWK_6].x;
    if (gBossFrameCount == 600) {
        Radio_PlayMessage(gMsg_ID_2225, RCID_SLIPPY);
    }
    if (gBossFrameCount == 756) {
        gShowBossHealth = 1;
    }
    if (gBossFrameCount > 756) {
        gBossHealthBar = (bossA6->health / 780.0f) * 255.0f;
    }
    for (i = 0; i < 15; i++) {
        if (bossA6->swork[A6_SWK_0 + i] != 0) {
            bossA6->swork[A6_SWK_0 + i]--;
        }
    }
    if (bossA6->fwork[A6_FWK_0] > 20.0f) {
        for (i = 0; i < 3; i++) {
            if (bossA6->swork[A6_SWK_0 + i] == 0) {
                bossA6->swork[A6_SWK_0 + i] = 5;
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
#else
void Area6_80187944(Boss* bossA6);
#pragma GLOBAL_ASM("asm/us/nonmatchings/overlays/ovl_i3/fox_a6/Area6_80187944.s")
#endif

void Area6_8018A1B0(Boss* bossA6, s32 arg1) {
    switch (D_i3_801C2250[A6_BSS_2_0 + arg1]) {
        case 0:
            bossA6->swork[A6_SWK_27 + arg1] = 12;
            D_i3_801C2250[A6_BSS_2_0 + arg1] = 1;
            break;
        case 1:
            bossA6->fwork[A6_FWK_13 + arg1] = 120.0f;
            if (((bossA6->swork[A6_SWK_33 + arg1] == 0) && (D_i3_801C2250[A6_BSS_6] != 0) &&
                 ((bossA6->swork[A6_SWK_15 + 0] != 0) || (bossA6->swork[A6_SWK_15 + 1] != 0) ||
                  (bossA6->swork[A6_SWK_15 + 2] != 0))) ||
                (bossA6->swork[A6_SWK_25] == 0)) {
                bossA6->fwork[A6_FWK_16 + arg1] = 1.0f;
            } else {
                bossA6->fwork[A6_FWK_16 + arg1] = 60.0f;
            }
            if (bossA6->fwork[A6_FWK_10 + arg1] >= 119.0f) {
                bossA6->fwork[A6_FWK_10 + arg1] = 120.0f;
                bossA6->swork[A6_SWK_33 + arg1] = 30;
                bossA6->fwork[A6_FWK_16 + arg1] = 60.0f;
                D_i3_801C2250[A6_BSS_2_0 + arg1] = 0;
                bossA6->swork[A6_SWK_6 + arg1] = 0;
                bossA6->swork[A6_SWK_9 + arg1] = 0;
                bossA6->swork[A6_SWK_30 + arg1] = 1;
                bossA6->swork[A6_SWK_18 + arg1] = 0;
            }
            break;
    }
}

void Area6_8018A2C4(Boss* bossA6) {
    s32 i;
    Vec3f sp58;
    s32 pad1;

    for (i = 0; i < 3; i++) {
        if ((bossA6->dmgPart == i + 1) && (bossA6->state == 4) && (bossA6->fwork[A6_FWK_0] < 20.0f)) {
            if ((bossA6->swork[A6_SWK_18 + i] != 1) && (bossA6->swork[A6_SWK_18 + i] != 3)) {
                bossA6->swork[A6_SWK_0 + i] = 15;
                bossA6->swork[A6_SWK_3 + i] = 40;
                bossA6->swork[A6_SWK_33 + i] -= bossA6->damage;
                if (i == 0) {
                    sp58.x = D_i3_801BF334[0];
                    sp58.y = D_i3_801BF3C4[0];
                    sp58.z = bossA6->obj.pos.z;
                    func_effect_8007A6F0(&sp58, 0x29034003);
                }
                if (i == 1) {
                    sp58.x = D_i3_801BF364[0];
                    sp58.y = D_i3_801BF3F4[0];
                    sp58.z = bossA6->obj.pos.z;
                    func_effect_8007A6F0(&sp58, 0x29034003);
                }
                if (i == 2) {
                    sp58.x = D_i3_801BF394[0];
                    sp58.y = D_i3_801BF424[0];
                    sp58.z = bossA6->obj.pos.z;
                    func_effect_8007A6F0(&sp58, 0x29034003);
                }
                if (bossA6->swork[A6_SWK_33 + i] < 0) {
                    bossA6->swork[A6_SWK_33 + i] = 0;
                }
            }
        }
    }
}

void Area6_8018A464(Boss* bossA6, s32 arg1) {
    s32 i;
    s32 j;
    f32 var_fs0;
    Vec3f spE0;
    f32 temp1;
    f32 temp2;
    f32 temp3;
    f32 temp4;
    f32 temp5;
    f32 temp6;
    f32 temp7;

    A6_HIT_1(bossA6, arg1)->z.offset = bossA6->vwork[A6_VWK_1 + arg1].z;
    A6_HIT_1(bossA6, arg1)->y.offset = bossA6->vwork[A6_VWK_1 + arg1].y;
    A6_HIT_1(bossA6, arg1)->x.offset = bossA6->vwork[A6_VWK_1 + arg1].x;

    if ((D_i3_801C2250[A6_BSS_5] != 0) && (bossA6->timer_056 != 0)) {
        bossA6->timer_050 = 202;
        bossA6->timer_056 = 0;
    }
    switch (bossA6->swork[A6_SWK_18 + arg1]) { /* irregular */
        case 0:
            Math_SmoothStepToF(&bossA6->fwork[A6_FWK_25 + arg1], -90.0f, 0.05f, 2.0f, 0.00001f);
            Math_SmoothStepToF(&bossA6->fwork[A6_FWK_22 + arg1], 0.0f, 0.1f, 10.0f, 0.00001f);
            switch (arg1) {
                case 0:
                    if (bossA6->swork[A6_SWK_33] != 0) {
                        for (i = 1; i < 12; i++) {
                            D_i3_801BEE90[i] = 3.0f;
                            D_i3_801BEEC0[i] = 3.0f;
                            if ((bossA6->swork[A6_SWK_6] == 0) && (bossA6->state != 3)) {
                                bossA6->swork[A6_SWK_6] = 20;
                                D_i3_801BEE00[0].y = RAND_FLOAT_CENTERED(720.0f);
                                if (D_i3_801BEE00[0].y < -20.0f) {
                                    D_i3_801BEE00[0].y = -20.0f;
                                }
                                if (D_i3_801BEE00[0].y > 20.0f) {
                                    D_i3_801BEE00[0].y = 20.0f;
                                }
                                D_i3_801BF3C4[0] = D_i3_801BEE00[0].y;
                            } else if ((bossA6->swork[A6_SWK_6] & 3) == 0) {
                                D_i3_801BF3C4[i] = D_i3_801BEE00[i].y;
                                D_i3_801BEE00[i].y = D_i3_801BF3C4[i - 1];
                                //  temp_ft2;
                            }
                            if (bossA6->swork[A6_SWK_9] == 0) {
                                if ((D_i3_801BEE00[0].y < -20.0f) || (D_i3_801BEE00[0].y > 20.0f)) {
                                    for (i = 0; i < 12; i++) {
                                        Math_SmoothStepToF(&D_i3_801BEE00[i].x, 0.0f, 0.5f, 100.0f, 0.001f);
                                    }
                                } else {
                                    bossA6->swork[A6_SWK_9] = 30;
                                    D_i3_801BEE00[0].x = RAND_FLOAT_CENTERED(30.0f);
                                }
                                D_i3_801BF334[0] = D_i3_801BEE00[0].x;
                            } else if ((bossA6->swork[A6_SWK_9] % 8) == 0) {
                                D_i3_801BF334[i] = D_i3_801BEE00[i].x;
                                D_i3_801BEE00[i].x = D_i3_801BF334[i - 1];
                                //  temp_ft2;
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
                    if (bossA6->swork[A6_SWK_34] != 0) {
                        for (i = 1; i < 12; i++) {
                            D_i3_801BF010[i] = 3.0f;
                            D_i3_801BF040[i] = 3.0f;
                            if (bossA6->swork[A6_SWK_7] == 0) {
                                bossA6->swork[A6_SWK_7] = 20;
                                D_i3_801BEF80[0].y = RAND_FLOAT_CENTERED(720.0f);
                                if (D_i3_801BEF80[0].y < -20.0f) {
                                    D_i3_801BEF80[0].y = -20.0f;
                                }
                                if (D_i3_801BEF80[0].y > 20.0f) {
                                    D_i3_801BEF80[0].y = 20.0f;
                                }
                                D_i3_801BF3F4[0] = D_i3_801BEF80[0].y;
                            } else if ((bossA6->swork[A6_SWK_7] & 3) == 0) {
                                D_i3_801BF3F4[i] = D_i3_801BEF80[i].y;
                                D_i3_801BEF80[i].y = D_i3_801BF3F4[i - 1];
                            }
                            if (bossA6->swork[A6_SWK_10] == 0) {
                                if ((D_i3_801BEF80[0].y < -20.0f) || (D_i3_801BEF80[0].y > 20.0f)) {
                                    for (i = 0; i < 12; i++) {
                                        Math_SmoothStepToF(&D_i3_801BEF80[i].x, 0.0f, 0.5f, 50.0f, 0.001f);
                                    }
                                } else {
                                    bossA6->swork[A6_SWK_10] = 30;
                                    D_i3_801BEF80[0].x = RAND_FLOAT_CENTERED(30.0f);
                                }
                                D_i3_801BF364[0] = D_i3_801BEF80[0].x;
                            } else if ((bossA6->swork[A6_SWK_10] % 8) == 0) {
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
                    if (bossA6->swork[A6_SWK_35] != 0) {
                        for (i = 1; i < 12; i++) {
                            D_i3_801BF190[i] = 3.0f;
                            D_i3_801BF1C0[i] = 3.0f;
                            if (bossA6->swork[A6_SWK_8] == 0) {
                                bossA6->swork[A6_SWK_8] = 20;
                                D_i3_801BF100[0].y = RAND_FLOAT_CENTERED(720.0f);
                                if (D_i3_801BF100[0].y < -20.0f) {
                                    D_i3_801BF100[0].y = -20.0f;
                                }
                                if (D_i3_801BF100[0].y > 20.f) {
                                    D_i3_801BF100[0].y = 20.0f;
                                }
                                D_i3_801BF424[0] = D_i3_801BF100[0].y;
                            } else if ((bossA6->swork[A6_SWK_8] & 3) == 0) {
                                D_i3_801BF424[i] = D_i3_801BF100[i].y;
                                D_i3_801BF100[i].y = D_i3_801BF424[i - 1];
                                // temp_ft2;
                            }
                            if (bossA6->swork[A6_SWK_11] == 0) {
                                if ((D_i3_801BF100[0].y < -20.0f) || (D_i3_801BF100[0].y > 20.0f)) {
                                    for (i = 0; i < 12; i++) {
                                        Math_SmoothStepToF(&D_i3_801BF100[i].x, 0.0f, 0.5f, 50.0f, 0.001f);
                                    }
                                } else {
                                    bossA6->swork[A6_SWK_11] = 30;
                                    D_i3_801BF100[0].x = RAND_RANGE(-12.0f, 18.0f);
                                }
                                D_i3_801BF394[0] = D_i3_801BF100[0].x;
                            } else if ((bossA6->swork[A6_SWK_11] % 8) == 0) {
                                D_i3_801BF394[i] = D_i3_801BF100[i].x;
                                D_i3_801BF100[i].x = D_i3_801BF394[i - 1];
                                // temp_ft2;
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
            if ((bossA6->state >= 3) && (bossA6->fwork[A6_FWK_0] == 0) &&
                ((bossA6->swork[A6_SWK_33] != 0) || (bossA6->swork[A6_SWK_34] != 0) ||
                 (bossA6->swork[A6_SWK_35] != 0)) &&
                (D_i3_801C2250[A6_BSS_5] == 0)) {
                var_fs0 = 0.5f;
                if (bossA6->swork[A6_SWK_25] < 2) {
                    var_fs0 = 0.7f;
                }
                if (((gGameFrameCount % 32) == 0) && (Rand_ZeroOne() < var_fs0) && (D_i3_801C2250[A6_BSS_5] == 0) &&
                    (bossA6->swork[A6_SWK_33 + arg1] != 0)) {
                    if ((Rand_ZeroOne() < 0.2f) || (bossA6->swork[A6_SWK_25] < 2)) {
                        if (bossA6->swork[A6_SWK_18] == 0) {
                            bossA6->swork[A6_SWK_18] = 1;
                        }
                        if (bossA6->swork[A6_SWK_19] == 0) {
                            bossA6->swork[A6_SWK_19] = 1;
                        }
                        if (bossA6->swork[A6_SWK_20] == 0) {
                            bossA6->swork[A6_SWK_20] = 1;
                        }
                        bossA6->swork[A6_SWK_12] = 30;
                        if (bossA6->swork[A6_SWK_33] != 0) {
                            bossA6->swork[A6_SWK_13] = bossA6->swork[A6_SWK_12] + 50;
                        } else {
                            bossA6->swork[A6_SWK_13] = 30;
                        }
                        if (bossA6->swork[A6_SWK_34] != 0) {
                            bossA6->swork[A6_SWK_14] = bossA6->swork[A6_SWK_13] + 50;
                        } else {
                            bossA6->swork[A6_SWK_14] = bossA6->swork[A6_SWK_13];
                        }
                    } else {
                        for (i = 0; i < 3; i++) {
                            if ((i == (gGameFrameCount % 16U)) && (bossA6->swork[A6_SWK_18 + i] == 0)) {
                                bossA6->swork[A6_SWK_12 + i] = 15;
                                bossA6->swork[A6_SWK_18 + i] = 1;
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
            if (bossA6->swork[A6_SWK_12 + arg1] == 0) {
                bossA6->swork[A6_SWK_12 + arg1] =
                    40.0f - ((20.0f - ((bossA6->fwork[A6_FWK_3] * -1.0f) / 150.0f)) * 3.0f);
                if (arg1 == 0) {
                    spE0.x = D_i3_801BF334[0];
                    spE0.y = D_i3_801BF3C4[0];
                    spE0.z = bossA6->obj.pos.z;
                    func_effect_8007A6F0(&spE0, 0x29034065);
                }
                if (arg1 == 1) {
                    spE0.x = D_i3_801BF364[0];
                    spE0.y = D_i3_801BF3F4[0];
                    spE0.z = bossA6->obj.pos.z;
                    func_effect_8007A6F0(&spE0, 0x29034065);
                }
                if (arg1 == 2) {
                    spE0.x = D_i3_801BF394[0];
                    spE0.y = D_i3_801BF424[0];
                    spE0.z = bossA6->obj.pos.z;
                    func_effect_8007A6F0(&spE0, 0x29034065);
                }
                bossA6->swork[A6_SWK_18 + arg1] = 2;
            }
            break;
        case 2:
            D_i3_801C2250[A6_BSS_5] = 50;
            Math_SmoothStepToF(&bossA6->fwork[A6_FWK_25 + arg1], 0.0f, 0.4f, 100.0f, 0.00001f);
            Math_SmoothStepToF(&bossA6->fwork[A6_FWK_22 + arg1],
                               420.0f - ((20.0f - ((bossA6->fwork[A6_FWK_3] * -1.0f) / 150.0f)) * 20.0f), 0.3f, 100.0f,
                               0.00001f);
            if ((bossA6->swork[A6_SWK_12 + arg1] == 0) || (bossA6->swork[A6_SWK_3 + arg1] != 0)) {
                bossA6->swork[A6_SWK_18 + arg1] = 0;
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
            bossA6->timer_050 = 0;
            bossA6->swork[A6_SWK_18] = bossA6->swork[A6_SWK_19] = bossA6->swork[A6_SWK_20] = 4;
            bossA6->fwork[A6_FWK_13] = bossA6->fwork[A6_FWK_14] = bossA6->fwork[A6_FWK_15] = bossA6->fwork[A6_FWK_22] =
                bossA6->fwork[A6_FWK_23] = bossA6->fwork[A6_FWK_24] = 0.0f;
            bossA6->fwork[A6_FWK_10] = bossA6->fwork[A6_FWK_11] = bossA6->fwork[A6_FWK_12] = bossA6->fwork[A6_FWK_19] =
                bossA6->fwork[A6_FWK_20] = bossA6->fwork[A6_FWK_21] = 0.0f;

            bossA6->fwork[A6_FWK_28] = 0.0f;
            bossA6->fwork[A6_FWK_25] = bossA6->fwork[A6_FWK_26] = bossA6->fwork[A6_FWK_27] = -90.0f;
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

void Area6_8018B9BC(Boss* bossA6) {
    s32 i;
    s32 j;
    Vec3f sp94;
    Vec3f sp88;

    if (D_i3_801C2250[A6_BSS_0] == 0) {
        for (i = 3, j = 15; j < 18; j++, i++) {
            if (bossA6->swork[A6_SWK_0 + j] != 0) {
                if ((D_ctx_8017812C != 0) && (gPlayerShots[15].unk_64 > 0)) {
                    bossA6->swork[A6_SWK_0 + j] -= bossA6->damage;
                } else if (i + 1 == bossA6->dmgPart) {
                    bossA6->swork[A6_SWK_0 + j] -= bossA6->damage;
                    if ((D_i3_801C2250[A6_BSS_25] == 0) && (bossA6->swork[A6_SWK_25] == 1) && (Rand_ZeroOne() < 0.4f)) {
                        D_i3_801C2250[A6_BSS_10]++;
                        D_i3_801C2250[A6_BSS_10] &= 1;
                        D_i3_801C2250[A6_BSS_25] = 20;
                    }
                }
                AUDIO_PLAY_SFX(0x29033064, bossA6->sfxSource, 4);
                if (bossA6->swork[A6_SWK_0 + j] <= 0) {
                    bossA6->swork[A6_SWK_0 + j] = 0;
                    Matrix_MultVec3f(gCalcMatrix, &bossA6->vwork[A6_VWK_1 + i], &sp94);
                    func_effect_8007D0E0(bossA6->obj.pos.x + sp94.x, bossA6->obj.pos.y + sp94.y,
                                         bossA6->obj.pos.z + sp94.z, 10.0f);
                    sp88.x = bossA6->obj.pos.x + sp94.x;
                    sp88.y = bossA6->obj.pos.y + sp94.y;
                    sp88.z = bossA6->obj.pos.z + sp94.z;
                    func_effect_8007A6F0(&sp88, 0x2903B009);
                    func_effect_8007C120(bossA6->obj.pos.x, bossA6->obj.pos.y, bossA6->obj.pos.z + 150.0f,
                                         bossA6->vel.x, bossA6->vel.y, bossA6->vel.z, 0.2f, 50);
                }
                if ((bossA6->swork[A6_SWK_15] == 0) && (bossA6->swork[A6_SWK_16] == 0) &&
                    (bossA6->swork[A6_SWK_17] == 0)) {
                    Audio_KillSfxBySource(bossA6->sfxSource);
                    if (bossA6->swork[A6_SWK_25] != 0) {
                        bossA6->swork[A6_SWK_25]--;
                        if (bossA6->swork[A6_SWK_25] != 0) {
                            bossA6->health -= 60;
                        }
                    }
                    if (bossA6->swork[A6_SWK_25] != 0) {
                        bossA6->timer_058 = 50;
                    } else {
                        bossA6->timer_054 = 30;
                        bossA6->fwork[A6_FWK_32] = 20.0f;
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
        RCP_SetupDL(&gMasterDisp, 0x17);
        if (D_i3_801C22F0.unk_24 != 255.0f) {
            RCP_SetupDL(&gMasterDisp, 0x47);
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, (s32) D_i3_801C22F0.unk_24);
        } else if (arg4 != 0) {
            RCP_SetupDL(&gMasterDisp, 0x1B);
            if (arg7 < 18.0f) {
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 255, 255);
            } else {
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 0, 255);
            }
        }
        Matrix_Push(&gGfxMatrix);
        Matrix_Push(&gCalcMatrix);
        Matrix_Copy(gCalcMatrix, &gIdentityMatrix);
        Matrix_RotateZ(gCalcMatrix, M_DTOR * arg1, 1);
        Matrix_Translate(gCalcMatrix, 0.0f, 100.0f, -223.0f, 1);
        Matrix_RotateX(gCalcMatrix, M_DTOR * arg2, 1);
        for (i = 0; i < arg6; i++) {
            Matrix_Push(&gGfxMatrix);
            Matrix_Push(&gCalcMatrix);
            if (i == 11) {
                Matrix_Scale(gCalcMatrix, 1.5f, 1.5f, 1.5f, 1);
                Matrix_Mult(gGfxMatrix, gCalcMatrix, 1);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
                gSPDisplayList(gMasterDisp++, D_A6_600F1F0);
                Matrix_MultVec3f(gCalcMatrix, &sp90, arg3);
            } else {
                Matrix_Scale(gCalcMatrix, 2.0f, 2.0f, 2.0f, 1);
                Matrix_Mult(gGfxMatrix, gCalcMatrix, 1);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                gSPDisplayList(gMasterDisp++, D_A6_6015EE0);
                if (arg6 != 12) {
                    Matrix_MultVec3f(gCalcMatrix, &sp90, arg3);
                }
            }
            Matrix_Pop(&gGfxMatrix);
            Matrix_Pop(&gCalcMatrix);
            Matrix_RotateY(gCalcMatrix, arg0[i].y * M_DTOR, 1);
            Matrix_RotateX(gCalcMatrix, arg0[i].x * M_DTOR, 1);
            Matrix_Translate(gCalcMatrix, 0.0f, 0.0f, arg5, 1);
        }
        Matrix_Pop(&gGfxMatrix);
    }
}

void Area6_8018C0D0(f32* arg0, f32 arg1, Vec3f* arg2, f32 arg3, s32 arg4) {
    s32 i;
    Vec3f spB0 = { 0.0f, 0.0f, 0.0f };
    f32 spAC;
    f32 var_fs3 = 5.0f;

    if (((gGameFrameCount % 2) == 0)) {
        spAC = 0.0f;
    } else {
        spAC = 180.0f;
        var_fs3 = 5.0f - (2.0f * (var_fs3 / 10.0f));
    }
    Matrix_Push(&gGfxMatrix);
    Matrix_Push(&gCalcMatrix);
    Matrix_Copy(gCalcMatrix, &gIdentityMatrix);
    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
    Matrix_RotateZ(gCalcMatrix, (D_i3_801C22F0.unk_34 + arg1) * M_DTOR, 1);
    Matrix_Translate(gCalcMatrix, 0.0f, -360.0f, 120.0f, 1);
    Matrix_RotateX(gCalcMatrix, -(90.0f - arg3) * M_DTOR, 1);
    Matrix_Scale(gCalcMatrix, 0.7f, 0.7f, 0.7f, 1);
    Matrix_SetGfxMtx(&gMasterDisp);
    for (i = 0; i < 5; i++) {
        Matrix_Push(&gGfxMatrix);
        Matrix_Push(&gCalcMatrix);
        if (i == 4) {
            Matrix_RotateX(gCalcMatrix, 80.0f * M_DTOR, 1);
            Matrix_RotateX(gCalcMatrix, (90.0f - arg3) * M_DTOR, 1);
            Matrix_Scale(gCalcMatrix, var_fs3, var_fs3, 1.0f, 1);
            Matrix_Mult(gGfxMatrix, gCalcMatrix, 1);
            Matrix_SetGfxMtx(&gMasterDisp);
            RCP_SetupDL(&gMasterDisp, 0x31);
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, (s32) D_i3_801C22F0.r[arg4], (s32) D_i3_801C22F0.g[arg4],
                            (s32) D_i3_801C22F0.b[arg4], 255);
            gDPSetEnvColor(gMasterDisp++, 255, 0, 0, 255);
            gSPDisplayList(gMasterDisp++, D_1024AC0);
            Matrix_MultVec3f(gCalcMatrix, &spB0, arg2);
        } else {
            RCP_SetupDL(&gMasterDisp, 0x2F);
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 64, 64, 192);
            Matrix_Translate(gCalcMatrix, 0.0f, -60.0f, 0.0f, 1);
            Matrix_Scale(gCalcMatrix, 2.0f, 3.0f, 1.0f, 1);
            Matrix_RotateY(gCalcMatrix, M_DTOR * spAC, 1);
            Matrix_Mult(gGfxMatrix, gCalcMatrix, 1);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_102F5E0);
        }
        Matrix_Pop(&gCalcMatrix);
        Matrix_Pop(&gGfxMatrix);
        Matrix_Translate(gCalcMatrix, 0.0f, -120.0f, 0.0f, 1);
        Matrix_RotateX(gCalcMatrix, -20.0f * M_DTOR, 1);
        Matrix_RotateZ(gCalcMatrix, arg0[i] * M_DTOR, 1);
    }
    Matrix_Pop(&gCalcMatrix);
    Matrix_Pop(&gGfxMatrix);
}

void Area6_8018C54C(Boss* bossA6) {
    Vec3f spD0[30];
    Vec3f spC4;
    Vec3f spB8;
    Vec3f spAC;
    s32 i;
    s32 j;

    if (bossA6->state == 0) {
        RCP_SetupDL(&gMasterDisp, 0x31);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, (s32) D_i3_801C22F0.unk_24);
        gDPSetEnvColor(gMasterDisp++, 255, 255, 0, 255);
        Matrix_Scale(gGfxMatrix, 10.0f, 10.0f, 10.0f, 1);
        Matrix_RotateZ(gGfxMatrix, bossA6->fwork[A6_FWK_33] * M_DTOR, 1);
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, D_101C2E0);
    } else if (D_i3_801C22F0.unk_24 != 0.0f) {
        Animation_GetFrameData(&D_A6_6018994, 0, spD0);
        if (D_i3_801C22F0.unk_24 != 255.0f) {
            RCP_SetupDL(&gMasterDisp, 0x47);
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, (s32) D_i3_801C22F0.unk_24);
            spAC.x = 0.0f;

            if ((gSysFrameCount & 1) == 0) {
                spAC.x = 1.0f;
                if (1) {}
                spAC.x = 0.0f;
            }
            spAC.y = spAC.z = 0.0f;
            Matrix_RotateZ(gCalcMatrix, gGameFrameCount * 6.0f * M_DTOR, 0);
            Matrix_MultVec3f(gCalcMatrix, &spAC, &spB8);
            Matrix_Translate(gGfxMatrix, spB8.x, spB8.y, 0.0f, 1);
            Matrix_Scale(gGfxMatrix, bossA6->unk_3F8, bossA6->unk_3F8, bossA6->unk_3F8, 1);
            Matrix_RotateZ(gGfxMatrix, gGameFrameCount * 10.0f * M_DTOR, 1);
            Matrix_Scale(gGfxMatrix, bossA6->fwork[A6_FWK_34], bossA6->fwork[A6_FWK_35], 1.0f, 1);
            Matrix_RotateZ(gGfxMatrix, -(f32) gGameFrameCount * 10.0f * M_DTOR, 1);
            Matrix_Scale(gGfxMatrix, bossA6->fwork[A6_FWK_34], bossA6->fwork[A6_FWK_35], 1.0f, 1);
        } else {
            RCP_SetupDL(&gMasterDisp, 0x1B);
            if (bossA6->timer_05C & 1) {
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
            } else {
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, (s32) D_i3_801C22F0.unk_28[0], (s32) D_i3_801C22F0.unk_28[2],
                                (s32) D_i3_801C22F0.unk_28[1], 255);
            }
        }
        spD0[3].z -= bossA6->fwork[A6_FWK_0];
        spD0[4].z -= bossA6->fwork[A6_FWK_0];
        spD0[5].z -= bossA6->fwork[A6_FWK_0];
        Animation_DrawSkeleton(1, D_A6_6018BA0, spD0, NULL, NULL, &bossA6->index, &gIdentityMatrix);
        if (bossA6->unk_3F8 >= 1.0f) {
            for (i = 0; i < 3; i++) {
                if ((bossA6->swork[A6_SWK_33 + i] == 0) && (bossA6->state != 3) &&
                    (D_i3_801C2250[A6_BSS_2_0 + i] == 0) && ((gGameFrameCount % 4) == 0) &&
                    (bossA6->swork[A6_SWK_27 + i] != 0) && (gPlayState != 100)) {
                    Matrix_RotateY(gCalcMatrix, bossA6->obj.rot.y * M_DTOR, 0);
                    Matrix_RotateX(gCalcMatrix, bossA6->obj.rot.x * M_DTOR, 1);
                    Matrix_RotateZ(gCalcMatrix, bossA6->obj.rot.z * M_DTOR, 1);
                    Matrix_MultVec3f(gCalcMatrix, &bossA6->vwork[A6_VWK_1] + i, &spC4);
                    func_effect_8007D0E0(bossA6->obj.pos.x + spC4.x, bossA6->obj.pos.y + spC4.y,
                                         bossA6->obj.pos.z + spC4.z, 20.0f);
                    spB8.x = bossA6->obj.pos.x + spC4.x;
                    spB8.y = bossA6->obj.pos.y + spC4.y;
                    spB8.z = bossA6->obj.pos.z + spC4.z;
                    if ((!bossA6) && (!bossA6)) {} // fake
                    if (D_i3_801C2250[A6_BSS_26] == 0) {
                        func_effect_8007A6F0(&spB8, 0x2903B009);
                    }
                    D_i3_801C2250[A6_BSS_26]++;
                    D_i3_801C2250[A6_BSS_26] &= 1;
                    bossA6->swork[A6_SWK_27 + i]--;
                    if (bossA6->swork[A6_SWK_27 + i] <= 0) {
                        bossA6->swork[A6_SWK_18 + i] = 4;
                        bossA6->swork[A6_SWK_38] = 1;
                        bossA6->fwork[A6_FWK_10 + i] = bossA6->fwork[A6_FWK_19 + i] = bossA6->fwork[A6_FWK_13 + i] =
                            bossA6->fwork[A6_FWK_22 + i] = 0.0f;
                        bossA6->fwork[A6_FWK_25 + i] = -90.0f;

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
            Area6_8018BCD4(D_i3_801BED70, 0.0f, bossA6->fwork[A6_FWK_25], &bossA6->vwork[A6_VWK_1],
                           bossA6->swork[A6_SWK_0] & 1, bossA6->fwork[A6_FWK_10] + bossA6->fwork[A6_FWK_19],
                           bossA6->swork[A6_SWK_27], bossA6->fwork[A6_FWK_0]);
            Area6_8018BCD4(D_i3_801BEEF0, -120.0f, bossA6->fwork[A6_FWK_26], &bossA6->vwork[A6_VWK_2],
                           bossA6->swork[A6_SWK_1] & 1, bossA6->fwork[A6_FWK_11] + bossA6->fwork[A6_FWK_20],
                           bossA6->swork[A6_SWK_28], bossA6->fwork[A6_FWK_0]);
            Area6_8018BCD4(D_i3_801BF070, 120.0f, bossA6->fwork[A6_FWK_27], &bossA6->vwork[A6_VWK_3],
                           bossA6->swork[A6_SWK_2] & 1, bossA6->fwork[A6_FWK_12] + bossA6->fwork[A6_FWK_21],
                           bossA6->swork[A6_SWK_29], bossA6->fwork[A6_FWK_0]);
            if ((bossA6->swork[A6_SWK_15] != 0) && (bossA6->state >= 3) && (D_i3_801C22F0.unk_24 == 255.0f) &&
                (D_i3_801C2250[A6_BSS_0] == 0)) {
                Area6_8018C0D0(D_i3_801BF1F0, 0.0f, &bossA6->vwork[A6_VWK_4], bossA6->fwork[A6_FWK_0], 0);
            }
            if ((bossA6->swork[A6_SWK_16] != 0) && (bossA6->state >= 3) && (D_i3_801C22F0.unk_24 == 255.0f) &&
                (D_i3_801C2250[A6_BSS_0] == 0)) {
                Area6_8018C0D0(D_i3_801BF220, -120.0f, &bossA6->vwork[A6_VWK_5], bossA6->fwork[A6_FWK_0], 1);
            }
            if ((bossA6->swork[A6_SWK_17] != 0) && (bossA6->state >= 3) && (D_i3_801C22F0.unk_24 == 255.0f) &&
                (D_i3_801C2250[A6_BSS_0] == 0)) {
                Area6_8018C0D0(D_i3_801BF250, 120.0f, &bossA6->vwork[A6_VWK_6], bossA6->fwork[A6_FWK_0], 2);
            }
            if (bossA6->swork[A6_SWK_25] != 0) {
                j = bossA6->swork[A6_SWK_25] - 1;
                if ((bossA6->timer_058 != 0) && !(bossA6->timer_058 & 3)) {
                    AUDIO_PLAY_SFX(0x29034003, bossA6->sfxSource, 4);
                }
                if (bossA6->timer_058 == 1) {
                    if (bossA6->swork[A6_SWK_25] == 2) {
                        Radio_PlayMessage(gMsg_ID_7085, RCID_FALCO);
                    } else if (bossA6->swork[A6_SWK_25] == 1) {
                        Radio_PlayMessage(gMsg_ID_7086, RCID_SLIPPY);
                    }
                }
                if (bossA6->swork[A6_SWK_22] != D_i3_801BF310[j]) {
                    if (bossA6->swork[A6_SWK_22] < D_i3_801BF310[j]) {
                        bossA6->swork[A6_SWK_22]++;
                    } else {
                        bossA6->swork[A6_SWK_22]--;
                    }
                }
                if (bossA6->swork[A6_SWK_23] != D_i3_801BF31C[j]) {
                    if (bossA6->swork[A6_SWK_23] < D_i3_801BF31C[j]) {
                        bossA6->swork[A6_SWK_23]++;
                    } else {
                        bossA6->swork[A6_SWK_23]--;
                    }
                }
                if (bossA6->swork[A6_SWK_24] != D_i3_801BF328[j]) {
                    if (bossA6->swork[A6_SWK_24] < D_i3_801BF328[j]) {
                        bossA6->swork[A6_SWK_24]++;
                    } else {
                        bossA6->swork[A6_SWK_24]--;
                    }
                }
            } else {
                Math_SmoothStepToF(&bossA6->fwork[A6_FWK_29], 0.0f, 1.0f, 10.0f, 0.0001f);
                if ((bossA6->timer_054 == 0) && (bossA6->swork[A6_SWK_36] == 4) && (D_i3_801C2250[A6_BSS_31] == 0)) {
                    Radio_PlayMessage(gMsg_ID_7087, RCID_PEPPY);
                    bossA6->swork[A6_SWK_36] = 5;
                    D_i3_801C2250[A6_BSS_31]++;
                    D_i3_801C2250[A6_BSS_31] &= 1;
                }
            }
        }
        Matrix_Push(&gGfxMatrix);
        RCP_SetupDL(&gMasterDisp, 0x47);
        Matrix_Translate(gGfxMatrix, 0.0f, 2.0f, 70.0f, 1);
        Matrix_Scale(gGfxMatrix, 1.7f, 1.7f, 1.7f, 1);
        if (bossA6->timer_05C & 1) {
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
        } else {
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, (s32) D_i3_801C22F0.unk_24);
        }
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, D_A6_601B2B0);
        Matrix_Pop(&gGfxMatrix);
        RCP_SetupDL(&gMasterDisp, 0x47);
        if (D_i3_801C22F0.unk_24 != 255.0f) {
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, bossA6->swork[A6_SWK_22], bossA6->swork[A6_SWK_23],
                            bossA6->swork[A6_SWK_24], (s32) D_i3_801C22F0.unk_28[-1]);
        } else {
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, bossA6->swork[A6_SWK_22], bossA6->swork[A6_SWK_23],
                            bossA6->swork[A6_SWK_24], (s32) bossA6->fwork[A6_FWK_29]);
        }
        Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, 74.0f, 1);
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, D_A6_6011910);
        Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, 74.0f, 1);
    }
}

void Area6_8018D3CC(s32 arg0, f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 xRot, f32 yRot,
                    f32 zRot) {
    s32 i;

    for (i = 0; i < 10; i++) {
        if (gPlayerShots[i].obj.status == 0) {
            PlayerShot_Initialize(&gPlayerShots[i]);
            gPlayerShots[i].vel.z = zVel;
            gPlayerShots[i].vel.x = xVel;
            gPlayerShots[i].vel.y = yVel;
            gPlayerShots[i].obj.pos.x = xPos;
            gPlayerShots[i].obj.pos.y = yPos;
            gPlayerShots[i].obj.pos.z = zPos;
            gPlayerShots[i].obj.status = OBJ_INIT;
            gPlayerShots[i].obj.rot.x = xRot + 180.0f;
            gPlayerShots[i].obj.rot.y = yRot;
            gPlayerShots[i].obj.rot.z = -zRot;
            gPlayerShots[i].unk_58 = 1;
            gPlayerShots[i].unk_60 = 0;
            gPlayerShots[i].obj.id = PLAYERSHOT_1;
            gPlayerShots[i].unk_64 = 150;
            gPlayerShots[i].playerNum = 100;

            AUDIO_PLAY_SFX(0x2900000D, gPlayerShots[i].sfxSource, 4);
            break;
        }
    }
}

void Area6_8018D4E0(Actor* actor) {
    s32 i;

    func_effect_8007BFFC(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, 0.0f, 0.0f, 0.0f, 4.0f, 20);
    func_effect_8007D2C8(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, 7.0f);
    func_effect_8007B344(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, 6.0f, 5);
    Object_Kill(&actor->obj, actor->sfxSource);
    for (i = 0; i < 15; i++) {
        func_effect_800794CC(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, 1.0f);
    }
    func_effect_8007A6F0(&actor->obj.pos, 0x2903B009);
}

void Area6_8018D5C8(void) {
    s32 i = 0;

    Actor_Initialize(&gActors[i]);
    gActors[i].obj.status = OBJ_INIT;
    gActors[i].obj.pos.x = 1600.0f;
    gActors[i].obj.pos.y = 3750.0f;
    gActors[i].obj.pos.z = 13000.0f;
    gActors[i].unk_0B6 = 1;
    gActors[i].state = 90;
    gActors[i].fwork[0] = 0.0f;
    gActors[i].obj.id = OBJ_ACTOR_195;
    Object_SetInfo(&gActors[i].info, gActors[i].obj.id);
    AUDIO_PLAY_SFX(0x11030010, gActors[i].sfxSource, 0);
}

void Area6_8018D694(Actor* actor, s32 arg1) {
    Vec3f sp2C[5] = {
        { -150.0f, 0.0f, 200.0f },   { 0.0f, 50.0f, 0.0f },       { 150.0f, -50.0f, 100.0f },
        { -350.0f, 100.0f, 300.0f }, { 100.0f, -300.0f, 100.0f },
    };

    Actor_Initialize(actor);
    actor->obj.status = OBJ_ACTIVE;
    actor->obj.id = OBJ_ACTOR_195;
    actor->obj.pos.x = sp2C[arg1].x + 100.0f;
    actor->obj.pos.y = sp2C[arg1].y + 350.0f;
    actor->obj.pos.z = sp2C[arg1].z + 1000.0f;
    actor->state = 1;
    actor->unk_0B6 = 28;
    actor->iwork[11] = 1;
    actor->unk_0F4.y = 90.0f;
    actor->fwork[0] = 1.5f;
    actor->fwork[7] = RAND_FLOAT_SEEDED(360.0f);
    actor->fwork[8] = RAND_FLOAT_SEEDED(360.0f);
    actor->fwork[9] = RAND_FLOAT_SEEDED(360.0f);
    Object_SetInfo(&actor->info, actor->obj.id);
    AUDIO_PLAY_SFX(0x31000011, actor->sfxSource, 4);
}

void Area6_8018D804(Actor* actor, s32 arg1) {
    Vec3f sp2C[3] = {
        { -200.0f, 0.0f, -500.0f },
        { 200.0f, 30.0f, -600.0f },
        { 50.0f, -90.0f, -700.0f },
    };
    Player* player = &gPlayer[0];

    Actor_Initialize(actor);
    actor->obj.status = OBJ_ACTIVE;
    actor->obj.id = OBJ_ACTOR_195;
    actor->obj.pos.x = sp2C[arg1].x + player->pos.x;
    actor->obj.pos.y = sp2C[arg1].y + player->pos.y;
    actor->obj.pos.z = sp2C[arg1].z + player->pos.z;
    actor->state = 5;
    actor->iwork[11] = 1;
    actor->fwork[0] = 0.0f;
    Object_SetInfo(&actor->info, actor->obj.id);
    AUDIO_PLAY_SFX(0x3100000C, actor->sfxSource, 4);
}

void Area6_8018D920(Vec3f* arg0) {
    f32 sp6C = arg0->x - arg0->x;
    f32 sp68 = arg0->y - arg0->y;
    f32 sp64 = arg0->z - 1000.0f - arg0->z;
    f32 sp60 = Math_RadToDeg(Math_Atan2F(sp6C, sp64));
    f32 sp5C = Math_RadToDeg(-Math_Atan2F(sp68, sqrtf(SQ(sp6C) + SQ(sp64))));
    Vec3f sp50;
    Vec3f sp44;

    Matrix_RotateY(gCalcMatrix, M_DTOR * sp60, 0);
    Matrix_RotateX(gCalcMatrix, M_DTOR * sp5C, 1);
    sp50.x = 0.0f;
    sp50.y = 0.0f;
    sp50.z = 100.0f;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp50, &sp44);
    Area6_8018D3CC(100, arg0->x, arg0->y, arg0->z, sp44.x, sp44.y, sp44.z, sp5C, sp60, 0.0f);
}

void Area6_8018DA58(Actor* actor) {
    Vec3f sp5C;
    Vec3f sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;

    switch (actor->state) { /* irregular */
        case 1:
            actor->fwork[7] += 2.5f;
            actor->unk_0F4.z = SIN_DEG(actor->fwork[7]) * 10.0f;
            actor->fwork[8] += 1.0f;
            actor->obj.pos.y += SIN_DEG(actor->fwork[8]) * 1.5f;
            actor->fwork[9] += 1.0f;
            actor->obj.pos.z += COS_DEG(actor->fwork[9]) * 1.5f;
            break;
        case 2:
            Math_SmoothStepToF(&actor->unk_0F4.z, -180.0f, 0.1f, 3.0f, 0.0f);
            break;
        case 3:
            Math_SmoothStepToF(&actor->unk_0F4.z, -45.0f, 0.05f, 2.0f, 0.0f);
            Math_SmoothStepToAngle(&actor->unk_0F4.y, 340.0f, 0.05f, 2.4f, 0.0f);
            Math_SmoothStepToF(&actor->unk_0F4.x, 3.0f, 0.05f, 1.0f, 0.0f);
            Math_SmoothStepToF(&actor->fwork[0], 30.0f, 0.1f, 3.0f, 0.0f);
            break;
        case 6:
        case 11:
        case 16:
            actor->state++;
            AUDIO_PLAY_SFX(0x09000002, actor->sfxSource, 0);
            actor->fwork[29] = 5.0f;
            /* fallthrough */
        case 7:
        case 12:
        case 17:
            actor->iwork[11] = 2;
            Math_SmoothStepToF(&actor->fwork[0], 50.0f, 0.1f, 3.0f, 0.01f);
            switch (actor->state) {
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
            sp38 = Math_SmoothStepToAngle(&actor->unk_0F4.y, sp3C, 0.5f, 2.0f, 0.0001f) * 30.0f;
            Math_SmoothStepToAngle(&actor->unk_0F4.x, sp40, 0.5f, 2.0f, 0.0001f);
            Math_SmoothStepToAngle(&actor->unk_0F4.z, sp38, 0.1f, 5.0f, 0.0001f);
            break;
        case 91:
            Math_SmoothStepToF(&actor->obj.pos.y, 0.0f, 0.1f, 5.0f, 0.1f);
            Math_SmoothStepToF(&actor->obj.pos.z, 0.0f, 1.0f, 20.0f, 20.0f);
            break;
        case 90:
            break;
    }
    Matrix_RotateY(gCalcMatrix, (actor->unk_0F4.y + 180.0f) * M_DTOR, 0);
    Matrix_RotateX(gCalcMatrix, -(actor->unk_0F4.x * M_DTOR), 1);
    sp5C.x = 0.0f;
    sp5C.y = 0.0f;
    sp5C.z = actor->fwork[0];
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp5C, &sp50);
    actor->vel.x = sp50.x;
    actor->vel.y = sp50.y;
    actor->vel.z = sp50.z;
    actor->obj.rot.x = -actor->unk_0F4.x;
    actor->obj.rot.y = actor->unk_0F4.y + 180.0f;
    actor->obj.rot.z = -actor->unk_0F4.z;
}

void Area6_8018DF74(Player* player) {
    Vec3f sp74;
    Vec3f sp68;
    Vec3f sp5C;
    f32 temp1; // 58
    f32 temp2; // 54
    f32 temp3; // 50
    f32 temp4; // 4C

    switch (player->unk_1D0) {
        case 0:
            gCsFrameCount = 0;
            player->unk_1D0 = 1;
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
            player->unk_0D0 = 30.0f;
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
                Matrix_Translate(gCalcMatrix, 0.0f, 350.0f, D_ctx_80177A48[6], 0);
                Matrix_RotateY(gCalcMatrix, -(D_ctx_80177A48[4] * M_DTOR), 1);
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
                AUDIO_PLAY_SFX(0x09000002, player->sfxSource, 0);
            }
            if (gCsFrameCount >= 460) {
                Math_SmoothStepToF(&player->unk_0D0, 50.0f, 0.1f, 3.0f, 0.01f);
            }
            if (player->pos.z < 30.0f) {
                player->unk_0D0 = player->pos.z = 0.0f;
            }
            if (gCsFrameCount == 540) {
                D_ctx_80178488 = 1;
                gLevelStatusScreenTimer = 50;
                player->pos.x = 0.0f;
                player->pos.z = 0.0f;
                player->pos.y = 350.0f;
                player->unk_0D0 = D_play_80161A54;
                player->unk_1D0 = 0;
                player->timer_1F8 = 0;

                AUDIO_PLAY_BGM(SEQ_ID_AREA_6 | SEQ_FLAG);
                player->state_1C8 = PLAYERSTATE_1C8_3;
            }
            break;
    }
    switch (gCsFrameCount) {
        case 280:
            AUDIO_PLAY_BGM(SEQ_ID_INTRO_51);
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
            func_play_800A6148();
            break;
    }
    Matrix_RotateY(gCalcMatrix, (player->unk_0E8 + player->unk_114 + 180.0f) * M_DTOR, 0);
    Matrix_RotateX(gCalcMatrix, -(player->unk_0E4 * M_DTOR), 1);
    if (player->state_1C8 != PLAYERSTATE_1C8_3) {
        sp74.x = 0.0f;
        sp74.y = 0.0f;
        sp74.z = player->unk_0D0;
        Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp74, &sp68);
        player->vel.x = sp68.x;
        player->vel.z = sp68.z;
        player->vel.y = sp68.y;
        player->pos.x += player->vel.x;
        player->pos.y += player->vel.y;
        player->pos.z += player->vel.z;
        player->unk_138 = player->pos.z;
    }
    player->unk_0F8 = player->unk_0EC + player->unk_12C + player->unk_130;
    Math_SmoothStepToF(&player->camEye.x, gCsCamEyeX, D_ctx_80177A48[0], 50000.0f, 0.001f);
    Math_SmoothStepToF(&player->camEye.y, gCsCamEyeY, D_ctx_80177A48[0], 50000.0f, 0.001f);
    Math_SmoothStepToF(&player->camEye.z, gCsCamEyeZ, D_ctx_80177A48[0], 50000.0f, 0.001f);
    Math_SmoothStepToF(&player->camAt.x, gCsCamAtX, D_ctx_80177A48[1], 50000.0f, 0.001f);
    Math_SmoothStepToF(&player->camAt.y, gCsCamAtY, D_ctx_80177A48[1], 50000.0f, 0.001f);
    Math_SmoothStepToF(&player->camAt.z, gCsCamAtZ, D_ctx_80177A48[1], 50000.0f, 0.001f);
}

void Area6_8018EA88(Actor* actor) {
    Actor_Initialize(actor);
    actor->obj.status = OBJ_ACTIVE;
    actor->obj.id = OBJ_ACTOR_195;
    actor->obj.pos.x = 0.0f;
    actor->obj.pos.y = 0.0f;
    actor->obj.pos.z = gBosses[0].obj.pos.z + 500.0f;
    actor->unk_0B6 = 37;
    actor->state = 100;
    actor->iwork[0] = 255;
    actor->iwork[1] = 255;
    actor->iwork[2] = 255;
    actor->iwork[3] = 240;
    actor->iwork[4] = 0;
    actor->iwork[5] = 0;
    actor->iwork[6] = 255;
    actor->iwork[7] = 100;
    actor->fwork[4] = 1.0f;
    actor->scale = 1.0f;
    Object_SetInfo(&actor->info, actor->obj.id);
}

void Area6_8018EB3C(Actor* actor) {
    Player* player = &gPlayer[0];

    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_195;
    actor->obj.pos.x = player->pos.x;
    actor->obj.pos.y = player->pos.y + 600.0f;
    actor->obj.pos.z = player->pos.z + 2800.0f;
    actor->unk_0B6 = 1;
    actor->state = 100;
    actor->fwork[0] = 0.0f;
    Object_SetInfo(&actor->info, actor->obj.id);
    AUDIO_PLAY_SFX(0x11030010, actor->sfxSource, 0);
    AUDIO_PLAY_SFX(0x31024059, actor->sfxSource, 0);
}

void Area6_8018EC38(Actor* actor, s32 arg1) {
    Vec3f sp2C[3] = {
        { -150.0f, 40.0f, 75.0f },
        { 150.0f, 40.0f, 150.0f },
        { 38.0f, 88.0f, 225.0f },
    };
    Player* player = &gPlayer[0];

    if (gTeamShields[arg1 + 1] > 0) {
        Actor_Initialize(actor);
        actor->obj.status = OBJ_ACTIVE;
        actor->obj.id = OBJ_ACTOR_195;
        actor->obj.pos.x = sp2C[arg1].x + player->pos.x;
        actor->obj.pos.y = sp2C[arg1].y + player->pos.y;
        actor->obj.pos.z = sp2C[arg1].z + player->pos.z;
        actor->state = 100;
        actor->iwork[11] = 1;
        actor->fwork[0] = 0.0f;
        if (arg1 + 1 != 3) {
            actor->iwork[14] = arg1 + 2;
        }
        Object_SetInfo(&actor->info, actor->obj.id);
        AUDIO_PLAY_SFX(0x3100000C, actor->sfxSource, 4);
    }
}

void Area6_8018ED78(Player* player) {
    s32 i;
    Vec3f spf90;
    f32 sp8C;
    f32 sp88;
    f32 sp84;
    Vec3f sp78;
    Vec3f sp6C;
    Actor* actor4 = &gActors[4];
    s32 pad;

    switch (player->unk_1D0) {
        case 0:
            gCsFrameCount = 0;
            player->unk_1D0 = 1;
            player->wings.unk_2C = 1;
            player->unk_194 = 5.0f;
            player->unk_190 = 2.0f;
            player->unk_0D0 = 60.0f;
            AUDIO_PLAY_SFX(0x09000002, player->sfxSource, 0);
            D_ctx_80177A48[3] = 0.0f;
            /* fallthrough */
        case 1:
            Math_SmoothStepToAngle(&player->unk_130, 0.0f, 0.05f, 1.2f, 0.0001f);
            Math_SmoothStepToAngle(&player->unk_12C, 0.0f, 0.05f, 1.2f, 0.0001f);
            Math_SmoothStepToF(&player->unk_034, 0.0f, 0.1f, 3.0f, 0.0f);
            Math_SmoothStepToAngle(&player->unk_4D8, 0.0f, 0.1f, 20.0f, 0.0f);
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
                sp84 = Math_SmoothStepToAngle(&player->unk_0E8, sp8C, 0.5f, 2.0f, 0.0001f) * 30.0f;
                Math_SmoothStepToAngle(&player->unk_0E4, sp88, 0.1f, 5.0f, 0.0001f);
                Math_SmoothStepToAngle(&player->unk_0EC, sp84, 0.1f, 5.0f, 0.0001f);
            }
            if (gCsFrameCount == 60) {
                player->unk_234 = 0;
                player->unk_0D0 = 0.0f;
            }
            Math_SmoothStepToF(&gCsCamEyeX, gBosses[0].obj.pos.x, 0.05f, 1000.0f, 0.001f);
            Math_SmoothStepToF(&gCsCamEyeY, gBosses[0].obj.pos.y, 0.05f, 1000.0f, 0.001f);
            Math_SmoothStepToF(&gCsCamEyeZ, gBosses[0].obj.pos.z + D_ctx_80177D20, 0.05f, 10.0f, 0.0001f);
            player->camEye.x = gCsCamEyeX;
            player->camEye.y = gCsCamEyeY;
            player->camEye.z = gCsCamEyeZ;

            gCsCamAtX = gBosses[0].obj.pos.x;
            gCsCamAtY = gBosses[0].obj.pos.y;
            gCsCamAtZ = gBosses[0].obj.pos.z + D_ctx_80177D20;
            D_ctx_80177A48[0] = 0.04f;
            if (gCsFrameCount == 140) {
                Area6_8018EA88(actor4);
                Area6_8018EA88(&gActors[5]);
                Area6_8018EA88(&gActors[6]);
                actor4->fwork[4] = 0.5f;
            }
            if (gCsFrameCount >= 200) {
                if (gFillScreenAlpha == 255) {
                    player->unk_1D0 = 2;
                    func_play_800A6148();
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
                AUDIO_PLAY_SFX(0x2940F026, gActors[5].sfxSource, 4);
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
                player->unk_234 = 1;
                player->pos.x = 0.0f;
                player->pos.y = 200.0f;
                player->pos.z = 1000.0f;
                player->unk_08C = player->unk_0EC = player->unk_0E8 = player->unk_0E4 = player->unk_0D0 =
                    player->unk_110 = player->unk_034 = player->unk_12C = player->unk_130 = player->unk_4D8 = 0.0f;

                D_bg_8015F984 = (D_ctx_80177D20 * 0.00004f) + 0.5f;
                Area6_8018EC38(&gActors[1], 0);
                Area6_8018EC38(&gActors[2], 1);
                Area6_8018EC38(&gActors[3], 2);
                Area6_8018EB3C(&gActors[0]);
                D_ctx_80177A48[5] = 300.0f;
                D_ctx_80177A48[4] = 0.0f;
                D_ctx_80177A48[9] = 50.0f;
                player->camAt.x = gCsCamAtX = player->pos.x;
                player->camAt.y = gCsCamAtY = 0.0f;
                player->camAt.z = gCsCamAtZ = player->pos.z + 50.0f + D_ctx_80177D20;
            }
            if (gFillScreenAlpha != 0) {
                gFillScreenAlphaTarget = 0;
                gFillScreenAlphaStep = 4;
            } else {
                player->unk_1D0 = 3;
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
                gCsCamAtZ = D_ctx_80177A48[9] + player->pos.z + D_ctx_80177D20;
                D_ctx_80177A48[0] = 0.008f;
            } else {
                Math_SmoothStepToAngle(&D_ctx_80177A48[4], 0.0f, 0.1f, 10.0f, 0.001f);
                Math_SmoothStepToF(&D_ctx_80177A48[5], 0.0f, 0.1f, 1000.0f, 0.001f);
                D_bg_8015F984 -= 0.005f;
                gCsCamAtX += 2.0f;
                player->camAt.x = gCsCamAtX = player->pos.x;
                player->camAt.y = gCsCamAtY = 0.0f;
                player->camAt.z = gCsCamAtZ = D_ctx_80177A48[9] + player->pos.z + D_ctx_80177D20;
            }
            sp78.x = 0.0f;
            sp78.y = 0.0f;
            sp78.z = D_ctx_80177A48[5];
            Matrix_Translate(gCalcMatrix, D_ctx_80177A48[1], 0.0f, D_ctx_80177A48[3] + D_ctx_80177D20, 0);
            Matrix_RotateY(gCalcMatrix, -(D_ctx_80177A48[4] * M_DTOR), 1);
            Matrix_MultVec3f(gCalcMatrix, &sp78, &sp6C);
            player->camEye.x = gCsCamEyeX = sp6C.x;
            player->camEye.y = gCsCamEyeY = sp6C.y;
            player->camEye.z = gCsCamEyeZ = sp6C.z;

            if (gCsFrameCount == 1076) {
                Object_Kill(&gActors[0].obj, gActors[0].sfxSource);
                player->unk_190 = 2.0f;
                player->unk_194 = 5.0f;
                AUDIO_PLAY_SFX(0x09000002, player->sfxSource, 0);
            }
            if (gCsFrameCount >= 1090) {
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
                gFillScreenAlphaTarget = 255;
                gFillScreenAlphaStep = 8;
                if (gFillScreenAlpha == 255) {
                    D_play_800D3180[LEVEL_AREA_6] = Play_CheckMedalStatus(300) + 1;
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
                    D_ctx_80161A94[0] = gGoldRingCount[0];
                    func_8001CA24(0);
                    Audio_KillSfxBySource(player->sfxSource);
                    func_play_800A6148();
                    gNextGameState = GSTATE_PLAY;
                    gNextLevel = LEVEL_VENOM_2;
                    func_hud_80088564();
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
            AUDIO_PLAY_BGM(SEQ_ID_GOOD_END);
            break;
        case 550:
            gLevelClearScreenTimer = 100;
            break;
        case 700:
            D_ctx_80177830 = 1;
            break;
        case 900:
            D_ctx_80177830 = 0;
            break;
        case 940:
            Radio_PlayMessage(gMsg_ID_7093, RCID_FOX);
            break;
        case 1070:
            gActors[1].fwork[29] = 5.0f;
            AUDIO_PLAY_SFX(0x09000002, gActors[1].sfxSource, 0);
            break;
        case 1072:
            gActors[2].fwork[29] = 5.0f;
            AUDIO_PLAY_SFX(0x09000002, gActors[2].sfxSource, 0);
            break;
        case 1074:
            gActors[3].fwork[29] = 5.0f;
            AUDIO_PLAY_SFX(0x09000002, gActors[3].sfxSource, 0);
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
        Math_SmoothStepToF(&player->unk_0D0, 50.0f, 0.1f, 1000.0f, 0.001f);
    }
    Matrix_RotateY(gCalcMatrix, (player->unk_0E8 + player->unk_114 + 180.0f) * M_DTOR, 0);
    Matrix_RotateX(gCalcMatrix, -(player->unk_0E4 * M_DTOR), 1);
    sp78.x = 0.0f;
    sp78.y = 0.0f;
    sp78.z = player->unk_0D0;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp78, &sp6C);
    player->vel.x = sp6C.x;
    player->vel.z = sp6C.z;
    player->vel.y = sp6C.y;
    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;
    player->pos.z += player->vel.z;
    player->unk_138 = player->pos.z;
    player->unk_0F8 = player->unk_0EC + player->unk_12C + player->unk_130;
    Math_SmoothStepToF(&player->camEye.x, gCsCamEyeX, D_ctx_80177A48[0], 50000.0f, 0.0001f);
    Math_SmoothStepToF(&player->camEye.y, gCsCamEyeY, D_ctx_80177A48[0], 50000.0f, 0.0001f);
    Math_SmoothStepToF(&player->camEye.z, gCsCamEyeZ, D_ctx_80177A48[0], 50000.0f, 0.0001f);
    Math_SmoothStepToF(&player->camAt.x, gCsCamAtX, D_ctx_80177A48[0], 50000.0f, 0.0001f);
    Math_SmoothStepToF(&player->camAt.y, gCsCamAtY, D_ctx_80177A48[0], 50000.0f, 0.0001f);
    Math_SmoothStepToF(&player->camAt.z, gCsCamAtZ, D_ctx_80177A48[0], 50000.0f, 0.0001f);
}
