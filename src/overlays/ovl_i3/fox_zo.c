/*
 * File: fox_zo.c
 * System: Zoness
 * Description: Level: Zoness
 */

#include "global.h"
#include "assets/ast_enmy_planet.h"
#include "assets/ast_zoness.h"
#include "port/interpolation/FrameInterpolation.h"

#define TRAP_ENEMY_LASERS (1000)

typedef struct {
    f32 id;
    Vec3f tilt;
    Hitbox b;
} TiltHitbox;

#define LIMB_DESTROYED 1000

#define ZO_HITBOX_COUNT ((s32) (bossZO)->info.hitbox[0])
#define ZO_HIT_0(bossZO) ((Hitbox*) ((bossZO)->info.hitbox + 1))
#define ZO_HIT_1(bossZO) ((Hitbox*) (ZO_HIT_0(bossZO) + 1))
#define ZO_HIT_2(bossZO) ((Hitbox*) (ZO_HIT_1(bossZO) + 1))
#define ZO_HIT_3(bossZO) ((TiltHitbox*) (ZO_HIT_2(bossZO) + 1))
#define ZO_HIT_4(bossZO) ((TiltHitbox*) (ZO_HIT_3(bossZO) + 1))
#define ZO_HIT_5(bossZO) ((Hitbox*) (ZO_HIT_4(bossZO) + 1))
#define ZO_HIT_6(bossZO) ((Hitbox*) (ZO_HIT_5(bossZO) + 1))
#define ZO_HIT_7(bossZO) ((Hitbox*) (ZO_HIT_6(bossZO) + 1))
#define ZO_HIT_8(bossZO, index) ((Hitbox*) ((f32*) (ZO_HIT_7(bossZO) + 1) + 6 * (index)))
#define ZO_HIT_10(bossZO, index) ((Hitbox*) ((f32*) (ZO_HIT_8(bossZO, 0) + 2) + 6 * (index)))
#define ZO_HIT_12(bossZO) ((Hitbox*) (ZO_HIT_10(bossZO, 0) + 2))

void Solar_801A7750(void);
void Zoness_801986FC(Boss* this, s32 arg1, f32 xOff, f32 yOff, f32 zOff, f32 yRot);
void Zoness_801989FC(Boss* this);
void Zoness_80198BE8(Boss* this, s32 arg1);
void Zoness_80198ECC(Boss* this);
void Zoness_80198F3C(Boss* this, s32 arg1, s32 arg2);
void Zoness_8019907C(Boss* this);
void Zoness_8019914C(Boss* this, s32 arg1);
void Zoness_801991D0(Boss* this, s32 arg1);
void Zoness_80199394(Boss* this, s32 arg1);
void Zoness_80199470(Boss* this, s32 arg1);
void Zoness_8019962C(Boss* this, f32 arg1);

typedef enum {
    /*  0 */ ZO_LIMB_0,
    /*  1 */ ZO_LIMB_1,
    /*  2 */ ZO_LIMB_2,
    /*  3 */ ZO_LIMB_3,
    /*  4 */ ZO_LIMB_4,
    /*  5 */ ZO_LIMB_5,
    /*  6 */ ZO_LIMB_6,
    /*  7 */ ZO_LIMB_7,
    /*  8 */ ZO_LIMB_8,
    /*  9 */ ZO_LIMB_9,
    /* 10 */ ZO_LIMB_10,
    /* 11 */ ZO_LIMB_11,
    /* 12 */ ZO_LIMB_12,
    /* 13 */ ZO_LIMB_13,
    /* 14 */ ZO_LIMB_14,
    /* 15 */ ZO_LIMB_15,
    /* 16 */ ZO_LIMB_16,
    /* 17 */ ZO_LIMB_17,
    /* 18 */ ZO_LIMB_18,
    /* 19 */ ZO_LIMB_19,
    /* 20 */ ZO_LIMB_20,
    /* 21 */ ZO_LIMB_21,
    /* 22 */ ZO_LIMB_22,
    /* 23 */ ZO_LIMB_23,
    /* 24 */ ZO_LIMB_24,
    /* 25 */ ZO_LIMB_25,
    /* 26 */ ZO_LIMB_26,
    /* 27 */ ZO_LIMB_27,
    /* 28 */ ZO_LIMB_28,
    /* 29 */ ZO_LIMB_29,
    /* 30 */ ZO_LIMB_30,
    /* 31 */ ZO_LIMB_31,
    /* 32 */ ZO_LIMB_32,
    /* 33 */ ZO_LIMB_33,
    /* 34 */ ZO_LIMB_34,
    /* 35 */ ZO_LIMB_35,
    /* 36 */ ZO_LIMB_36,
    /* 37 */ ZO_LIMB_37,
    /* 38 */ ZO_LIMB_38,
    /* 39 */ ZO_LIMB_39,
    /* 40 */ ZO_LIMB_MAX,
} ZoSarumarineLimbs;

typedef enum {
    /*   0 */ ZO_BSF_0,
    /*   1 */ ZO_BSF_1,
    /*   2 */ ZO_BSF_2,
    /*   3 */ ZO_BSF_3,
    /*   4 */ ZO_BSF_4,
    /*   5 */ ZO_BSF_5,
    /*   6 */ ZO_BSF_6,
    /*   7 */ ZO_BSF_7,
    /*   8 */ ZO_BSF_8,
    /*   9 */ ZO_BSF_9,
    /*  10 */ ZO_BSF_10,
    /*  11 */ ZO_BSF_11,
    /*  12 */ ZO_BSF_12,
    /*  13 */ ZO_BSF_13,
    /*  14 */ ZO_BSF_14,
    /*  15 */ ZO_BSF_15,
    /*  16 */ ZO_BSF_16,
    /*  17 */ ZO_BSF_17,
    /*  18 */ ZO_BSF_18,
    /*  19 */ ZO_BSF_19,
    /*  20 */ ZO_BSF_20,
    /*  21 */ ZO_BSF_21,
    /*  22 */ ZO_BSF_22,
    /*  23 */ ZO_BSF_23,
    /*  24 */ ZO_BSF_24,
    /*  25 */ ZO_BSF_25,
    /*  26 */ ZO_BSF_26,
    /*  27 */ ZO_BSF_27,
    /*  28 */ ZO_BSF_28,
    /*  29 */ ZO_BSF_29_X,
    /*  30 */ ZO_BSF_29_Y,
    /*  31 */ ZO_BSF_29_Z,
    /*  32 */ ZO_BSF_32_X,
    /*  33 */ ZO_BSF_32_Y,
    /*  34 */ ZO_BSF_32_Z,
    /*  35 */ ZO_BSF_35,
    /*  36 */ ZO_BSF_36,
    /*  37 */ ZO_BSF_37_X,
    /*  38 */ ZO_BSF_37_Y,
    /*  39 */ ZO_BSF_37_Z,
    /*  40 */ ZO_BSF_40_X,
    /*  41 */ ZO_BSF_40_Y,
    /*  42 */ ZO_BSF_40_Z,
    /*  43 */ ZO_BSF_43_X,
    /*  44 */ ZO_BSF_43_Y,
    /*  45 */ ZO_BSF_43_Z,
    /*  46 */ ZO_BSF_46_X,
    /*  47 */ ZO_BSF_46_Y,
    /*  48 */ ZO_BSF_46_Z,
    /*  49 */ ZO_BSF_49_X,
    /*  50 */ ZO_BSF_49_Y,
    /*  51 */ ZO_BSF_49_Z,
    /*  52 */ ZO_BSF_52_X,
    /*  53 */ ZO_BSF_52_Y,
    /*  54 */ ZO_BSF_52_Z,
    /*  55 */ ZO_BSF_55_X,
    /*  56 */ ZO_BSF_55_Y,
    /*  57 */ ZO_BSF_55_Z,
    /*  58 */ ZO_BSF_58,
    /*  59 */ ZO_BSF_59,
    /*  60 */ ZO_BSF_60_X,
    /*  61 */ ZO_BSF_60_Y,
    /*  62 */ ZO_BSF_60_Z,
    /*  63 */ ZO_BSF_63,
    /*  64 */ ZO_BSF_64,
    /*  65 */ ZO_BSF_65_X,
    /*  66 */ ZO_BSF_65_Y,
    /*  67 */ ZO_BSF_65_Z,
    /*  68 */ ZO_BSF_68_X,
    /*  69 */ ZO_BSF_68_Y,
    /*  70 */ ZO_BSF_68_Z,
    /*  71 */ ZO_BSF_71_X,
    /*  72 */ ZO_BSF_71_Y,
    /*  73 */ ZO_BSF_71_Z,
    /*  74 */ ZO_BSF_74,
    /*  75 */ ZO_BSF_75,
    /*  76 */ ZO_BSF_76,
    /*  77 */ ZO_BSF_77,
    /*  78 */ ZO_BSF_78,
    /*  79 */ ZO_BSF_79,
    /*  80 */ ZO_BSF_80,
    /*  81 */ ZO_BSF_81,
    /*  82 */ ZO_BSF_82,
    /*  83 */ ZO_BSF_83,
    /*  84 */ ZO_BSF_84,
    /*  85 */ ZO_BSF_85,
    /*  86 */ ZO_BSF_86,
    /*  87 */ ZO_BSF_87,
    /*  88 */ ZO_BSF_88,
    /*  89 */ ZO_BSF_89,
    /*  90 */ ZO_BSF_90,
    /*  91 */ ZO_BSF_91,
    /*  92 */ ZO_BSF_92,
    /*  93 */ ZO_BSF_93_X,
    /*  94 */ ZO_BSF_93_Y,
    /*  95 */ ZO_BSF_93_Z,
    /*  96 */ ZO_BSF_96_X,
    /*  97 */ ZO_BSF_96_Y,
    /*  98 */ ZO_BSF_96_Z,
    /*  99 */ ZO_BSF_99_X,
    /* 100 */ ZO_BSF_99_Y,
    /* 101 */ ZO_BSF_99_Z,
    /* 102 */ ZO_BSF_102_X,
    /* 103 */ ZO_BSF_102_Y,
    /* 104 */ ZO_BSF_102_Z,
    /* 105 */ ZO_BSF_105,
    /* 106 */ ZO_BSF_106_X,
    /* 107 */ ZO_BSF_106_Y,
    /* 108 */ ZO_BSF_106_Z,
    /* 109 */ ZO_BSF_109_X,
    /* 110 */ ZO_BSF_109_Y,
    /* 111 */ ZO_BSF_109_Z,
    /* 112 */ ZO_BSF_112,
    /* 113 */ ZO_BSF_113,
    /* 114 */ ZO_BSF_114,
    /* 115 */ ZO_BSF_115,
    /* 116 */ ZO_BSF_116,
    /* 117 */ ZO_BSF_117,
    /* 118 */ ZO_BSF_118,
    /* 119 */ ZO_BSF_119,
    /* 120 */ ZO_BSF_120,
    /* 121 */ ZO_BSF_121,
    /* 122 */ ZO_BSF_122,
    /* 123 */ ZO_BSF_123,
    /* 124 */ ZO_BSF_124,
    /* 125 */ ZO_BSF_125,
    /* 126 */ ZO_BSF_126,
    /* 127 */ ZO_BSF_127,
    /* 128 */ ZO_BSF_128,
    /* 129 */ ZO_BSF_129,
    /* 130 */ ZO_BSF_130,
    /* 131 */ ZO_BSF_131,
    /* 132 */ ZO_BSF_132,
    /* 133 */ ZO_BSF_133,
    /* 134 */ ZO_BSF_134,
    /* 135 */ ZO_BSF_135,
    /* 136 */ ZO_BSF_136,
    /* 137 */ ZO_BSF_137,
    /* 138 */ ZO_BSF_138,
    /* 139 */ ZO_BSF_139,
    /* 140 */ ZO_BSF_140,
    /* 141 */ ZO_BSF_141,
    /* 142 */ ZO_BSF_142,
    /* 143 */ ZO_BSF_143,
    /* 144 */ ZO_BSF_144,
    /* 145 */ ZO_BSF_145,
    /* 146 */ ZO_BSF_146,
    /* 147 */ ZO_BSF_147,
    /* 148 */ ZO_BSF_148,
    /* 149 */ ZO_BSF_149,
    /* 150 */ ZO_BSF_MAX,
} ZoSarumarinebsfwork;

typedef enum {
    /*  0 */ ZO_BSS_0,
    /*  1 */ ZO_BSS_1,
    /*  2 */ ZO_BSS_2,
    /*  3 */ ZO_BSS_3,
    /*  4 */ ZO_BSS_4,
    /*  5 */ ZO_BSS_5,
    /*  6 */ ZO_BSS_6,
    /*  7 */ ZO_BSS_7,
    /*  8 */ ZO_BSS_8,
    /*  9 */ ZO_BSS_9,
    /* 10 */ ZO_BSS_10,
    /* 11 */ ZO_BSS_11,
    /* 12 */ ZO_BSS_12,
    /* 13 */ ZO_BSS_13,
    /* 14 */ ZO_BSS_14,
    /* 15 */ ZO_BSS_15,
    /* 16 */ ZO_BSS_16,
    /* 17 */ ZO_BSS_17,
    /* 18 */ ZO_BSS_18,
    /* 19 */ ZO_BSS_19,
    /* 20 */ ZO_BSS_20,
    /* 21 */ ZO_BSS_21,
    /* 22 */ ZO_BSS_22,
    /* 23 */ ZO_BSS_23,
    /* 24 */ ZO_BSS_24,
    /* 25 */ ZO_BSS_25,
    /* 26 */ ZO_BSS_26,
    /* 27 */ ZO_BSS_27,
    /* 28 */ ZO_BSS_28,
    /* 29 */ ZO_BSS_29,
    /* 30 */ ZO_BSS_30,
    /* 31 */ ZO_BSS_31,
    /* 32 */ ZO_BSS_32,
    /* 33 */ ZO_BSS_33,
    /* 34 */ ZO_BSS_34,
    /* 35 */ ZO_BSS_35,
    /* 36 */ ZO_BSS_36,
    /* 37 */ ZO_BSS_37,
    /* 38 */ ZO_BSS_38,
    /* 39 */ ZO_BSS_39,
    /* 40 */ ZO_BSS_40,
    /* 41 */ ZO_BSS_41,
    /* 42 */ ZO_BSS_42,
    /* 43 */ ZO_BSS_43,
    /* 44 */ ZO_BSS_44,
    /* 45 */ ZO_BSS_45,
    /* 46 */ ZO_BSS_46,
    /* 47 */ ZO_BSS_47,
    /* 48 */ ZO_BSS_48,
    /* 49 */ ZO_BSS_49,
    /* 50 */ ZO_BSS_50,
    /* 51 */ ZO_BSS_51,
    /* 52 */ ZO_BSS_52,
    /* 53 */ ZO_BSS_53,
    /* 54 */ ZO_BSS_54,
    /* 55 */ ZO_BSS_55,
    /* 56 */ ZO_BSS_56,
    /* 57 */ ZO_BSS_57,
    /* 58 */ ZO_BSS_58,
    /* 59 */ ZO_BSS_59,
    /* 60 */ ZO_BSS_60,
    /* 61 */ ZO_BSS_61,
    /* 62 */ ZO_BSS_62,
    /* 63 */ ZO_BSS_63,
    /* 64 */ ZO_BSS_64,
    /* 65 */ ZO_BSS_65,
    /* 66 */ ZO_BSS_66,
    /* 67 */ ZO_BSS_67,
    /* 68 */ ZO_BSS_68,
    /* 69 */ ZO_BSS_69,
    /* 70 */ ZO_BSS_MAX,
} ZoSarumarinebsswork;

typedef enum {
    /*  0 */ ZO_SWK_0,
    /*  1 */ ZO_SWK_1,
    /*  2 */ ZO_SWK_2,
    /*  3 */ ZO_SWK_3,
    /*  4 */ ZO_SWK_4,
    /*  5 */ ZO_SWK_5,
    /*  6 */ ZO_SWK_6,
    /*  7 */ ZO_SWK_7,
    /*  8 */ ZO_SWK_8,
    /*  9 */ ZO_SWK_9,
    /* 10 */ ZO_SWK_10,
    /* 11 */ ZO_SWK_11,
    /* 12 */ ZO_SWK_12,
    /* 13 */ ZO_SWK_13,
    /* 14 */ ZO_SWK_14,
    /* 15 */ ZO_SWK_15,
    /* 16 */ ZO_SWK_16,
    /* 17 */ ZO_SWK_17,
    /* 18 */ ZO_SWK_18,
    /* 19 */ ZO_SWK_19,
    /* 20 */ ZO_SWK_20,
    /* 21 */ ZO_SWK_21,
    /* 22 */ ZO_SWK_22,
    /* 23 */ ZO_SWK_23,
    /* 24 */ ZO_SWK_24,
    /* 25 */ ZO_SWK_25,
    /* 26 */ ZO_SWK_26,
    /* 27 */ ZO_SWK_27,
    /* 28 */ ZO_SWK_28,
    /* 29 */ ZO_SWK_29,
    /* 30 */ ZO_SWK_30,
    /* 31 */ ZO_SWK_31,
    /* 32 */ ZO_SWK_32,
    /* 33 */ ZO_SWK_33,
    /* 34 */ ZO_SWK_34,
    /* 35 */ ZO_SWK_35,
    /* 36 */ ZO_SWK_36,
    /* 37 */ ZO_SWK_37,
    /* 38 */ ZO_SWK_38,
    /* 39 */ ZO_SWK_39,
    /* 40 */ ZO_SWK_MAX,
} ZoSarumarineswork;

typedef enum {
    /*  0 */ ZO_FWK_0,
    /*  1 */ ZO_FWK_1,
    /*  2 */ ZO_FWK_2,
    /*  3 */ ZO_FWK_3,
    /*  4 */ ZO_FWK_4,
    /*  5 */ ZO_FWK_5,
    /*  6 */ ZO_FWK_6,
    /*  7 */ ZO_FWK_7,
    /*  8 */ ZO_FWK_8,
    /*  9 */ ZO_FWK_9,
    /* 10 */ ZO_FWK_10,
    /* 11 */ ZO_FWK_11,
    /* 12 */ ZO_FWK_12,
    /* 13 */ ZO_FWK_13,
    /* 14 */ ZO_FWK_14,
    /* 15 */ ZO_FWK_15,
    /* 16 */ ZO_FWK_16,
    /* 17 */ ZO_FWK_17,
    /* 18 */ ZO_FWK_18,
    /* 19 */ ZO_FWK_19,
    /* 20 */ ZO_FWK_20,
    /* 21 */ ZO_FWK_21,
    /* 22 */ ZO_FWK_22,
    /* 23 */ ZO_FWK_23,
    /* 24 */ ZO_FWK_24,
    /* 25 */ ZO_FWK_25,
    /* 26 */ ZO_FWK_26,
    /* 27 */ ZO_FWK_27,
    /* 28 */ ZO_FWK_28,
    /* 29 */ ZO_FWK_29,
    /* 30 */ ZO_FWK_30,
    /* 31 */ ZO_FWK_31,
    /* 32 */ ZO_FWK_32,
    /* 33 */ ZO_FWK_33,
    /* 34 */ ZO_FWK_34,
    /* 35 */ ZO_FWK_35,
    /* 36 */ ZO_FWK_36,
    /* 37 */ ZO_FWK_37,
    /* 38 */ ZO_FWK_38,
    /* 39 */ ZO_FWK_39,
    /* 40 */ ZO_FWK_40,
    /* 41 */ ZO_FWK_41,
    /* 42 */ ZO_FWK_42,
    /* 43 */ ZO_FWK_43,
    /* 44 */ ZO_FWK_44,
    /* 45 */ ZO_FWK_45,
    /* 46 */ ZO_FWK_46,
    /* 47 */ ZO_FWK_47,
    /* 48 */ ZO_FWK_48,
    /* 49 */ ZO_FWK_49,
    /* 50 */ ZO_FWK_MAX,
} ZoSarumarinefwork;

typedef enum {
    /*  0 */ ZO_VWK_0,
    /*  1 */ ZO_VWK_1,
    /*  2 */ ZO_VWK_2,
    /*  3 */ ZO_VWK_3,
    /*  4 */ ZO_VWK_4,
    /*  5 */ ZO_VWK_5,
    /*  6 */ ZO_VWK_6,
    /*  7 */ ZO_VWK_7,
    /*  8 */ ZO_VWK_8,
    /*  9 */ ZO_VWK_9,
    /* 10 */ ZO_VWK_10,
    /* 11 */ ZO_VWK_11,
    /* 12 */ ZO_VWK_12,
    /* 13 */ ZO_VWK_13,
    /* 14 */ ZO_VWK_14,
    /* 15 */ ZO_VWK_15,
    /* 16 */ ZO_VWK_16,
    /* 17 */ ZO_VWK_17,
    /* 18 */ ZO_VWK_18,
    /* 19 */ ZO_VWK_19,
    /* 20 */ ZO_VWK_20,
    /* 21 */ ZO_VWK_21,
    /* 22 */ ZO_VWK_22,
    /* 23 */ ZO_VWK_23,
    /* 24 */ ZO_VWK_24,
    /* 25 */ ZO_VWK_25,
    /* 26 */ ZO_VWK_26,
    /* 27 */ ZO_VWK_27,
    /* 28 */ ZO_VWK_28,
    /* 29 */ ZO_VWK_29,
    /* 30 */ ZO_VWK_30,
    /* 31 */ ZO_VWK_31,
    /* 32 */ ZO_VWK_32,
    /* 33 */ ZO_VWK_33,
    /* 34 */ ZO_VWK_34,
    /* 35 */ ZO_VWK_35,
    /* 36 */ ZO_VWK_36,
    /* 37 */ ZO_VWK_37,
    /* 38 */ ZO_VWK_38,
    /* 39 */ ZO_VWK_39,
    /* 40 */ ZO_VWK_40,
    /* 41 */ ZO_VWK_41,
    /* 42 */ ZO_VWK_42,
    /* 43 */ ZO_VWK_43,
    /* 44 */ ZO_VWK_44,
    /* 45 */ ZO_VWK_45,
    /* 46 */ ZO_VWK_46,
    /* 47 */ ZO_VWK_47,
    /* 48 */ ZO_VWK_48,
    /* 49 */ ZO_VWK_49,
    /* 50 */ ZO_VWK_MAX,
} ZoSarumarinevwork;

s32 sZoLimbTimers[ZO_LIMB_MAX];
s32 sZoSwork[ZO_BSS_MAX];
f32 sZoFwork[ZO_BSF_MAX];

void Zoness_8018FF50(ZoEnergyBall* this) {
    f32 x;

    this->obj.rot.y = RAD_TO_DEG(
        Math_Atan2F(gPlayer[0].cam.eye.x - this->obj.pos.x, gPlayer[0].cam.eye.z - (this->obj.pos.z + gPathProgress)));
    x = sqrtf(SQ(gPlayer[0].cam.eye.z - (this->obj.pos.z + gPathProgress)) +
              SQ(gPlayer[0].cam.eye.x - this->obj.pos.x));
    this->obj.rot.x = RAD_TO_DEG(-Math_Atan2F(gPlayer[0].cam.eye.y - this->obj.pos.y, x));
}

void Zoness_ActorDebris_Setup(ActorDebris* this, Vec3f* pos, Vec3f* rot, f32 xVel, f32 yVel, f32 zVel, s32 state,
                              f32 scale, s32 timerBC, s32 unk48) {
    Actor_Initialize(this);
    this->obj.status = OBJ_ACTIVE;
    this->obj.id = OBJ_ACTOR_DEBRIS;

    this->state = state;
    this->scale = scale;
    this->work_048 = unk48;
    this->obj.pos = *pos;
    this->obj.rot = *rot;
    this->vel.x = xVel;
    this->vel.y = yVel;
    this->vel.z = zVel;
    this->timer_0BC = timerBC;
    this->gravity = 0.5f;

    Object_SetInfo(&this->info, this->obj.id);
}

void Zoness_ActorDebris_Spawn(Vec3f* pos, Vec3f* rot, f32 xVel, f32 yVel, f32 zVel, s32 state, f32 scale, s32 timerBC,
                              s32 unk48) {
    s32 i;

    for (i = ARRAY_COUNT(gActors) - 1; i > 0; i--) {
        if (gActors[i].obj.status == OBJ_FREE) {
            Zoness_ActorDebris_Setup(&gActors[i], pos, rot, xVel, yVel, zVel, state, scale, timerBC, unk48);
            break;
        }
    }
}

bool Zoness_ZoBird_OverrideLimbDraw(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
    if ((limbIndex >= 4) && (limbIndex < 10)) {
        gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
    }
    return false;
}

void Zoness_ZoBird_PostLimbDraw(s32 limbIndex, Vec3f* rot, void* thisx) {
    Vec3f src = { 0.0f, 0.0f, 0.0f };
    ZoBird* this = (ZoBird*) thisx;

    if (this->state == 1) {
        switch (limbIndex) {
            case 0:
                Matrix_MultVec3f(gCalcMatrix, &src, &this->vwork[0]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[11]);
                break;
            case 1:
                Matrix_MultVec3f(gCalcMatrix, &src, &this->vwork[1]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[12]);
                break;
            case 2:
                Matrix_MultVec3f(gCalcMatrix, &src, &this->vwork[2]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[13]);
                break;
            case 3:
                Matrix_MultVec3f(gCalcMatrix, &src, &this->vwork[3]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[14]);
                break;
            case 4:
                Matrix_MultVec3f(gCalcMatrix, &src, &this->vwork[4]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[15]);
                break;
            case 5:
                Matrix_MultVec3f(gCalcMatrix, &src, &this->vwork[5]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[16]);
                break;
            case 6:
                Matrix_MultVec3f(gCalcMatrix, &src, &this->vwork[6]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[17]);
                break;
            case 7:
                Matrix_MultVec3f(gCalcMatrix, &src, &this->vwork[7]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[18]);
                break;
            case 8:
                Matrix_MultVec3f(gCalcMatrix, &src, &this->vwork[8]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[19]);
                break;
            case 9:
                Matrix_MultVec3f(gCalcMatrix, &src, &this->vwork[9]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[20]);
                break;
            case 10:
                Matrix_MultVec3f(gCalcMatrix, &src, &this->vwork[10]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[21]);
                break;
        }
    }
}

void Zoness_ZoBird_Draw(ZoBird* this) {
    Vec3f frameTable[30];

    Matrix_Scale(gCalcMatrix, this->scale, this->scale, this->scale, MTXF_APPLY);
    Animation_GetFrameData(&aZoBirdAnim, this->animFrame, frameTable);
    Animation_DrawSkeleton(3, aZoBirdSkel, frameTable, Zoness_ZoBird_OverrideLimbDraw, Zoness_ZoBird_PostLimbDraw, this,
                           gCalcMatrix);
}

void Zoness_ZoBird_Update(ZoBird* this) {
    Vec3f src;
    Vec3f dest;
    s32 i;

    switch (this->state) {
        case 0:
            this->health = 20;
            Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
            Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);
            Matrix_RotateZ(gCalcMatrix, this->obj.rot.z * M_DTOR, MTXF_APPLY);
            src.x = src.y = 0.0f;
            src.z = this->fwork[10];
            Matrix_MultVec3f(gCalcMatrix, &src, &dest);
            this->vel.x = dest.x;
            this->vel.y = dest.y;
            this->vel.z = dest.z;
            this->state = 5;
            break;

        case 1:
            for (i = 0; i < 11; i++) {
                Zoness_ActorDebris_Spawn(&this->vwork[i], &this->vwork[i + 11], RAND_FLOAT_CENTERED(20.0f),
                                         RAND_FLOAT(-10.0f), RAND_FLOAT(10.0f), 41, this->scale, 200, i);
            }
            this->itemDrop = DROP_NONE;
            Actor_Despawn(this);
            Object_Kill(&this->obj, this->sfxSource);
            func_effect_8007D0E0(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 4.0f);
            Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_BIRD_DOWN);
            break;
    }

    this->animFrame++;

    if (Animation_GetFrameCount(&aZoBirdAnim) < this->animFrame) {
        this->animFrame = 0;
    }

    if ((this->dmgType != DMG_NONE) && (this->health != 0)) {
        this->dmgType = DMG_NONE;
        if (this->state > 0) {
            this->timer_0C6 = 15;
            this->health -= this->damage;
            AUDIO_PLAY_SFX(NA_SE_EN_BIRD_DAMAGE, this->sfxSource, 4);
            if (this->health <= 0) {
                this->health = 0;
                this->state = 1;
            }
        }
    }
}

void Zoness_80190790(ZoDodora* this) {
    s32 pad[2];
    f32 angle;
    PosRot* zoDodoraPosRotPtr;
    Vec3f src;
    Vec3f dest;
    s32 i;
    Actor* otherActor;

    this->counter_04E++;
    if (this->counter_04E >= 200) {
        this->counter_04E = 0;
    }

    this->fwork[0] += 4.0f;
    this->vel.y = SIN_DEG(this->fwork[0]) * 20.0f;
    this->rot_0F4.x = -this->vel.y * 2.5f;
    this->fwork[1] += 5.0f;
    this->rot_0F4.z = SIN_DEG(this->fwork[1]) * 30.0f;

    for (i = 0, otherActor = &gActors[0]; i < ARRAY_COUNT(gActors); i++, otherActor++) {
        if ((otherActor->obj.status == OBJ_ACTIVE) && (otherActor->obj.id == OBJ_ACTOR_ZO_DODORA_WP_COUNT) &&
            (otherActor->iwork[0] == this->iwork[0])) {
            angle = Math_RadToDeg(
                Math_Atan2F(otherActor->obj.pos.x - this->obj.pos.x, otherActor->obj.pos.z - this->obj.pos.z));

            Math_SmoothStepToAngle(&this->rot_0F4.y, angle, 0.2f, 3.0f, 0.0f);

            if ((fabsf(this->obj.pos.x - otherActor->obj.pos.x) < 500.0f) &&
                (fabsf(this->obj.pos.z - otherActor->obj.pos.z) < 500.0f)) {
                otherActor->obj.status = OBJ_FREE;
                this->iwork[0]++;
            }
            break;
        }
    }

    Matrix_RotateY(gCalcMatrix, this->rot_0F4.y * M_DTOR, MTXF_NEW);

    src.x = 0.f;
    src.y = 0.f;
    src.z = 20.0f;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

    this->vel.x = dest.x;
    this->vel.z = dest.z;

    zoDodoraPosRotPtr = &gZoDodoraPosRots[this->counter_04E];
    zoDodoraPosRotPtr->pos.x = this->obj.pos.x;
    zoDodoraPosRotPtr->pos.y = this->obj.pos.y;
    zoDodoraPosRotPtr->pos.z = this->obj.pos.z;
    zoDodoraPosRotPtr->rot.x = this->rot_0F4.x;
    zoDodoraPosRotPtr->rot.y = this->rot_0F4.y;
    zoDodoraPosRotPtr->rot.z = this->rot_0F4.z;
}

void Zoness_ZoDodora_Update(ZoDodora* this) {
    f32 sp2C;
    s32 sp28;

    if ((this->timer_0C0 == 0) &&
        Play_CheckDynaFloorCollision(&sp2C, &sp28, this->obj.pos.x, this->obj.pos.y - 50.0f, this->obj.pos.z)) {
        Effect_Effect391_Spawn(this->obj.pos.x, sp2C, this->obj.pos.z + 150.0f, 0.0f, 1.7f);
        if (this->vel.y >= 0.0f) {
            AUDIO_PLAY_SFX(NA_SE_OUT_SPLASH_L, this->sfxSource, 4);
        } else {
            AUDIO_PLAY_SFX(NA_SE_IN_SPLASH_L, this->sfxSource, 4);
        }
        this->timer_0C0 = 30;
    }

    Zoness_80190790(this);

    // Invulnerable
    if (this->dmgType != DMG_NONE) {
        this->dmgType = DMG_NONE;
        AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
    }
}

s16 D_i3_801BF56C[20] = {
    0, 190, 180, 170, 160, 150, 140, 130, 120, 110, 100, 90, 80, 70, 60, 50, 40, 30, 20, 10,
};
u8 sZoDodoraPartIdx[20] = {
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
};
Gfx* sZoDodoraParts[3] = { aZoDodoraHeadDL, aZoDodoraBodyDL, aZoDodoraTailDL };

void Zoness_ZoDodora_DrawParts(f32 xPos, f32 yPos, f32 zPos, f32 xRot, f32 yRot, f32 zRot, u8 partIdx,
                               bool colorFlicker) {
    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, xPos, yPos, zPos + gPathProgress, MTXF_APPLY);
    Matrix_RotateY(gGfxMatrix, M_DTOR * yRot, MTXF_APPLY);
    Matrix_RotateX(gGfxMatrix, M_DTOR * xRot, MTXF_APPLY);
    Matrix_RotateZ(gGfxMatrix, M_DTOR * zRot, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, 2.0f, 2.0f, 2.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);

    if (colorFlicker) {
        RCP_SetupDL_64();
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 40, 40, 255, 255);
    }
    gSPDisplayList(gMasterDisp++, sZoDodoraParts[partIdx]);
    Matrix_Pop(&gGfxMatrix);
}

typedef struct {
    f32 count;
    Hitbox boxes[1];
} JntHitbox;

void Zoness_ZoDodora_Draw2(ZoDodora* this) {
    Hitbox* hitbox = (((JntHitbox*) SEGMENTED_TO_VIRTUAL(aZoDodoraHitbox))->boxes);
    s32 i;
    s32 k;
    PosRot* zoDodoraPosRots;

    for (i = this->work_04A = 0; i < 20; i++, hitbox++) {
        k = (D_i3_801BF56C[i] + this->counter_04E) % 200;
        zoDodoraPosRots = &gZoDodoraPosRots[k];

        hitbox->z.offset = zoDodoraPosRots->pos.z - this->obj.pos.z;
        hitbox->y.offset = zoDodoraPosRots->pos.y - this->obj.pos.y;
        hitbox->x.offset = zoDodoraPosRots->pos.x - this->obj.pos.x;

        Zoness_ZoDodora_DrawParts(zoDodoraPosRots->pos.x, zoDodoraPosRots->pos.y, zoDodoraPosRots->pos.z,
                                  zoDodoraPosRots->rot.x, zoDodoraPosRots->rot.y, zoDodoraPosRots->rot.z,
                                  sZoDodoraPartIdx[i], this->timer_0C6 % 2U);

        if (gPlayState != PLAY_PAUSE) {
            Math_SmoothStepToF(&zoDodoraPosRots->pos.y, this->fwork[2], 1.0f, 10.0f, 0.0f);
        }
    }
}

void Zoness_ZoDodora_Draw(ZoDodora* this) {
    Zoness_ZoDodora_Draw2(this);
}

void Zoness_ZoFish_PostLimbDraw(s32 limbIndex, Vec3f* rot, void* thisx) {
    Vec3f sp2C = { 0.0f, 0.0f, 0.0f };
    ZoFish* this = (ZoFish*) thisx;

    if (this->state == 3) {
        switch (limbIndex) {
            case 0:
                Matrix_MultVec3f(gCalcMatrix, &sp2C, this->vwork);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[3]);
                return;
            case 1:
                Matrix_MultVec3f(gCalcMatrix, &sp2C, &this->vwork[1]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[4]);
                return;
            case 2:
                Matrix_MultVec3f(gCalcMatrix, &sp2C, &this->vwork[2]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[5]);
                break;
        }
    }
}

void Zoness_ZoFish_Update(ZoFish* this) {
    Vec3f src;
    Vec3f dest;
    f32 sp7C;
    s32 i;
    f32 var_fs0;
    s32 sp70;

    switch (this->state) {
        case 0:
            this->fwork[3] = this->obj.rot.x;
            this->fwork[1] = RAND_FLOAT_CENTERED(1000.0f);
            this->health = 10;
            this->timer_0BC = 30;
            this->scale = 5.0f;
            this->gravity = 1.0f;
            this->obj.rot.x = 315.0f;
            this->state++;
            break;

        case 1:
            Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
            Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);
            src.x = 0.0f;
            src.y = 0.0f;
            src.z = (this->fwork[3] * 10.0f) + 30.0f;
            Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);
            this->vel.x = dest.x;
            this->vel.y = dest.y;
            this->vel.z = dest.z;
            this->state++;
            break;

        case 2:
            if (this->timer_0BC == 0) {
                this->obj.rot.z += 30.0f;
                if (this->animFrame > 0) {
                    this->animFrame--;
                }
            } else {
                if (this->animFrame < Animation_GetFrameCount(&D_ZO_601AA48)) {
                    this->animFrame++;
                }
            }

            var_fs0 = 5.0f;
            if (this->obj.rot.x < 90.0f) {
                var_fs0 = 1.0f;
            }

            Math_SmoothStepToAngle(&this->obj.rot.x, 45.0f, 0.1f, var_fs0, 0.01f);

            if (this->obj.pos.y < -500.0f) {
                this->obj.rot.x = 0.0f;
                this->gravity = 0.0f;
                this->vel.y = 0.0f;
                Object_Kill(&this->obj, this->sfxSource);
            }

            if (Play_CheckDynaFloorCollision(&sp7C, &sp70, this->obj.pos.x, this->obj.pos.y, this->obj.pos.z) &&
                (this->iwork[0] < 2) && (this->timer_0C0 == 0)) {
                if (var_fs0 == 5.0f) {
                    AUDIO_PLAY_SFX(NA_SE_OUT_SPLASH_L, this->sfxSource, 4);
                } else {
                    AUDIO_PLAY_SFX(NA_SE_IN_SPLASH_L, this->sfxSource, 4);
                }
                this->timer_0C0 = 10;
                this->iwork[0]++;
                Effect_Effect391_Spawn(this->obj.pos.x, sp7C, this->obj.pos.z, 0.0f, 0.7f);
            }
            break;

        case 3:
            for (i = 0; i < 3; i++) {
                Zoness_ActorDebris_Spawn(&this->vwork[i], &this->vwork[3 + i], RAND_FLOAT_CENTERED(20.0f),
                                         RAND_FLOAT(-10.0f), RAND_FLOAT(10.0f), 42, this->scale, 200, i);
            }
            this->itemDrop = DROP_SILVER_RING_25p;
            Actor_Despawn(this);
            func_effect_8007D0E0(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 3.0f);
            AUDIO_PLAY_SFX(NA_SE_EN_EXPLOSION_S, this->sfxSource, 4);
            Object_Kill(&this->obj, this->sfxSource);
            Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_BIRD_DOWN);
            break;
    }

    if ((this->dmgType != DMG_NONE) && (this->health != 0)) {
        this->dmgType = DMG_NONE;
        this->timer_0C6 = 15;
        this->health -= this->damage;
        if (this->health <= 0) {
            this->health = 0;
            this->state = 3;
        }
    }
}

void Zoness_ZoFish_Draw(ZoFish* this) {
    Vec3f frameTable[20];

    Matrix_Scale(gCalcMatrix, this->scale, this->scale, this->scale, MTXF_APPLY);
    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
    Animation_GetFrameData(&D_ZO_601AA48, this->animFrame, frameTable);
    Animation_DrawSkeleton(3, D_ZO_601AB14, frameTable, NULL, Zoness_ZoFish_PostLimbDraw, this, gCalcMatrix);
    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
}

void Zoness_ZoEnergyBall_Init(ZoEnergyBall* this) {
    s32 i;
    Actor* energyBall;

    this->health = 50;
    this->fwork[0] = this->obj.pos.z - 10000.0f;

    for (i = 0, energyBall = &gActors[0]; i < ARRAY_COUNT(gActors); i++, energyBall++) {
        if (energyBall->obj.status == OBJ_FREE) {
            Actor_Initialize(energyBall);
            energyBall->obj.status = OBJ_INIT;
            energyBall->obj.id = OBJ_ACTOR_ZO_ENERGY_BALL;
            energyBall->obj.pos.x = this->obj.pos.x;
            energyBall->obj.pos.y = this->obj.pos.y;
            energyBall->obj.pos.z = this->obj.pos.z;
            energyBall->iwork[0] = this->index + 1;
            Object_SetInfo(&energyBall->info, energyBall->obj.id);
            this->iwork[0] = i;
            break;
        }
    }
    if (i >= ARRAY_COUNT(gActors)) {
        energyBall->obj.status = OBJ_FREE;
    }
}

void Zoness_ZGull_Update(ZGull* this) {
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    Vec3f sp48;
    Vec3f sp3C;
    Actor* otherActor;

    if (this->obj.pos.z < this->fwork[0]) {
        this->state = 1;
    }

    if ((this->dmgType != DMG_NONE) && (this->health != 0)) {
        this->dmgType = DMG_NONE;
        this->timer_0C6 = 15;
        this->health -= this->damage;
        AUDIO_PLAY_SFX(NA_SE_EN_BIRD_DAMAGE, this->sfxSource, 4);
        if (this->health <= 0) {
            this->health = this->itemDrop = 0;
            Actor_Despawn(this);
            this->state = 1;
            AUDIO_PLAY_SFX(NA_SE_EN_BIRD_DOWN, this->sfxSource, 4);
        }
    }

    this->animFrame++;
    if (this->animFrame >= Animation_GetFrameCount(&aFirebirdAnim)) {
        this->animFrame = 0;
    }

    if (this->timer_0BC == 0) {
        this->timer_0BC = 30;
        this->fwork[1] = gPlayer[0].pos.x + RAND_FLOAT_CENTERED(1000.0f);
        this->fwork[2] = gPlayer[0].pos.y + 50.0f + RAND_FLOAT(200.0f);
        this->fwork[3] = gPlayer[0].trueZpos - 1500.0f;
    }

    this->fwork[3] += gPlayer[0].vel.z;

    sp64 = this->fwork[1] - this->obj.pos.x;
    sp60 = this->fwork[2] - this->obj.pos.y;
    sp5C = this->fwork[3] - this->obj.pos.z;

    sp54 = Math_RadToDeg(Math_Atan2F(sp64, sp5C));

    otherActor = &gActors[this->iwork[0]];

    if ((this->state != 0) || (otherActor->obj.status == OBJ_FREE)) {
        this->lockOnTimers[TEAM_ID_FOX] = 0;
        this->info.targetOffset = 0.0f;
        sp54 += 180.0f;
        if (sp54 > 360.0f) {
            sp54 -= 360.0f;
        }
        if (this->timer_0C6 == 0) {
            this->timer_0C6 = 15;
        }
    }

    sp58 = sqrtf(SQ(sp64) + SQ(sp5C));
    sp58 = Math_RadToDeg(-Math_Atan2F(sp60, sp58));
    sp60 = Math_SmoothStepToAngle(&this->obj.rot.y, sp54, 0.2f, 4.0f, 0.0f);

    Math_SmoothStepToAngle(&this->obj.rot.x, sp58, 0.2f, 4.0f, 0.0f);

    sp5C = 330.0f;
    if (sp60 < 0.0f) {
        sp5C = 30.0f;
    }

    Math_SmoothStepToAngle(&this->obj.rot.z, sp5C, 0.2f, 4.0f, 0.0f);
    Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);

    sp48.x = sp48.y = 0.0f;
    sp48.z = 30.0f;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp48, &sp3C);

    this->vel.x = sp3C.x;
    this->vel.y = sp3C.y;
    this->vel.z = sp3C.z - 20.0f;

    if (otherActor->iwork[0] == (this->index + 1)) {
        if (this->state == 0) {
            otherActor->obj.pos.x = this->obj.pos.x;
            otherActor->obj.pos.y = this->obj.pos.y - 50.0f;
            otherActor->obj.pos.z = this->obj.pos.z;
            this->fwork[4] = otherActor->obj.pos.x;
            this->fwork[5] = otherActor->obj.pos.y;
            this->fwork[6] = otherActor->obj.pos.z;
            if (((gGameFrameCount % 16) == 0) && (fabsf(gPlayer[0].pos.x - this->obj.pos.x) < 100.0f)) {
                func_effect_80081BEC(this->fwork[4], this->fwork[5], this->fwork[6], 1.0f, 0);
            }
        } else {
            otherActor->vel.y -= 1.0f;
        }
    }
}

void Zoness_ZGull_Draw(ZGull* this) {
    Animation_GetFrameData(&aFirebirdAnim, this->animFrame, this->vwork);
    Animation_DrawSkeleton(1, aFirebirdSkel, this->vwork, NULL, NULL, &this->index, &gIdentityMatrix);
}

void Zoness_ZoEnergyBall_Init2(ZoEnergyBall* this) {
    /* Unimplemented */
}

void Zoness_ZoEnergyBall_Update(ZoEnergyBall* this) {
    f32 sp4C;
    s32 sp48;

    if ((this->vel.y != 0.0f) && (this->iwork[1] == 0)) {
        this->iwork[1] = 1;
        AUDIO_PLAY_SFX(NA_SE_EN_FALLING_DOWN, this->sfxSource, 4);
    }

    if (Play_CheckDynaFloorCollision(&sp4C, &sp48, this->obj.pos.x, this->obj.pos.y, this->obj.pos.z) &&
        (this->state == 0)) {
        Effect_Effect384_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 20.0f, 7);
        Effect_Effect390_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 0.0f, 0.0f, 0.0f, 0.5f, 50);
        Object_Kill(&this->obj, this->sfxSource);
        this->iwork[0] = 0;
        Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_OB_MINI_BOMB);
    }

    this->fwork[0] += 10.0f;

    Zoness_8018FF50(this);

    if ((gGameFrameCount % 2) == 0) {
        Effect_Effect389_Spawn(RAND_FLOAT_CENTERED(50.0f) + this->obj.pos.x,
                               RAND_FLOAT_CENTERED(50.0f) + this->obj.pos.y,
                               RAND_FLOAT_CENTERED(50.0f) + this->obj.pos.z, this->vel.x, this->vel.y, this->vel.z,
                               RAND_FLOAT(0.05f) + 0.05f, 0);
    }
}

void Zoness_ZoEnergyBall_Draw(ZoEnergyBall* this) {
    RCP_SetupDL_40();
    gSPDisplayList(gMasterDisp++, D_ZO_6019EB0);
    Matrix_RotateY(gGfxMatrix, this->fwork[0] * 0.7f * M_DTOR, MTXF_APPLY);
    Matrix_RotateX(gGfxMatrix, this->fwork[0] * M_DTOR, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_ZO_6023D50);
}

void Zoness_ZoTroika_PostLimbDraw(s32 limbIndex, Vec3f* rot, void* thisx) {
    Vec3f sp24 = { 0.0f, 0.0f, 0.0f };
    ZoTroika* this = (ZoTroika*) thisx;

    if (this->state == 4) {
        switch (limbIndex) {
            case 1:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[0]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[6]);
                break;
            case 2:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[1]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[7]);
                break;
            case 3:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[2]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[8]);
                break;
            case 4:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[3]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[9]);
                break;
            case 8:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[4]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[10]);
                break;
            case 9:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[5]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[11]);
                break;
        }
    }
}

void Zoness_ZoTroika_Draw(ZoTroika* this) {
    Vec3f jointTable[20];

    Matrix_Scale(gCalcMatrix, this->scale, this->scale, this->scale, MTXF_APPLY);
    Animation_GetFrameData(&D_ZO_60195EC, this->animFrame, jointTable);
    Animation_DrawSkeleton(3, D_ZO_6019738, jointTable, NULL, Zoness_ZoTroika_PostLimbDraw, this, gCalcMatrix);
}

void Zoness_ZoTroika_Update(ZoTroika* this) {
    s32 i;
    f32 spB8;
    f32 x;
    f32 y;
    f32 z;
    f32 temp_fs0_2;
    f32 spA4;
    s32 spA0;
    Vec3f sp94;
    Vec3f sp88;
    Vec3f sp7C = { 0.0f, 0.0f, 0.0f };
    Vec3f sp70;

    x = gPlayer[0].pos.x - this->obj.pos.x;
    y = gPlayer[0].pos.y - this->obj.pos.y;
    z = gPlayer[0].trueZpos - this->obj.pos.z;

    spA4 = Math_RadToDeg(Math_Atan2F(x, z));
    temp_fs0_2 = sqrtf(SQ(x) + SQ(z));
    temp_fs0_2 = Math_RadToDeg(-Math_Atan2F(y, temp_fs0_2));

    Math_SmoothStepToAngle(&this->obj.rot.x, temp_fs0_2, 0.1f, 10.0f, 0.00001f);
    Math_SmoothStepToAngle(&this->obj.rot.y, spA4, 0.1f, 10.0f, 0.00001f);

    if ((this->iwork[0] == 0) &&
        (Play_CheckDynaFloorCollision(&spB8, &spA0, this->obj.pos.x, this->obj.pos.y, this->obj.pos.z) != 0)) {
        Effect_Effect391_Spawn(this->obj.pos.x, spB8, this->obj.pos.z + 100.0f, 0.0f, 1.5f);

        this->iwork[0]++;

        if (this->vel.y >= 0.0f) {
            AUDIO_PLAY_SFX(NA_SE_OUT_SPLASH_L, this->sfxSource, 4);
        } else {
            AUDIO_PLAY_SFX(NA_SE_IN_SPLASH_L, this->sfxSource, 4);
        }
    }

    switch (this->state) {
        case 0:
            this->state++;
            this->vel.y = 20.0f;
            this->scale = 2.0f;
            break;

        case 1:
            this->animFrame++;
            if (this->animFrame >= Animation_GetFrameCount(&D_ZO_60195EC)) {
                this->animFrame = 64;
                Math_SmoothStepToF(&this->vel.z, 0.0f, 1.0f, 100.0f, 0.00001f);
                if (this->obj.pos.y < -500.0f) {
                    Object_Kill(&this->obj, this->sfxSource);
                }
            }

            if (this->animFrame == 25) {
                this->fwork[2] = 0.0f;
                this->vel.y = 0.0f;
                this->iwork[1] = 0;
                this->fwork[3] = 150.0f;
                this->state++;
            }
            break;

        case 2:
            if (this->iwork[1] > 20) {
                this->iwork[0] = 0;
                this->state = 3;
                this->vel.y = 50.0f;
                if (this->animFrame == 51) {
                    this->state = 1;
                    this->vel.y = -20.0f;
                }
            } else {
                Math_SmoothStepToF(&this->vel.z, -40.0f, 0.1f, 1.0f, 0.00001f);
                Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
                Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);
                Matrix_RotateZ(gCalcMatrix, this->fwork[2] * M_DTOR, MTXF_APPLY);
                sp70.x = 0.0f;
                sp70.y = this->fwork[3];
                sp70.z = 0.0f;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp70, &sp94);
                sp94.x += this->obj.pos.x;
                sp94.y += this->obj.pos.y;
                sp94.z = this->obj.pos.z - 200.0f;
                sp70.x = 0.0f;
                sp70.y = 0.0f;
                sp70.z = 100.0f;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp70, &sp88);
                func_effect_8007EE68(OBJ_EFFECT_355, &sp94, &sp7C, &sp7C, &sp88, 1.0f);
                this->fwork[2] += 40.0f;
                this->fwork[2] = Math_ModF(this->fwork[2], 360.0f);
                Math_SmoothStepToF(&this->fwork[3], 0.0f, 1.0f, 5.0f, 0.0001f);
                this->iwork[1]++;
            }
            break;

        case 3:
            Math_SmoothStepToF(&this->vel.z, -60.0f, 0.1f, 100.0f, 0.00001f);
            Math_SmoothStepToF(&this->vel.y, -30.0f, 0.1f, 100.0f, 0.00001f);
            this->animFrame++;
            if (this->animFrame == 51) {
                this->fwork[2] = 0.0f;
                this->vel.y = 0.0f;
                this->iwork[1] = 0;
                this->state = 2;
                this->fwork[3] = 150.0f;
            }
            break;

        case 4:
            for (i = 0; i < 6; i++) {
                Zoness_ActorDebris_Spawn(&this->vwork[i], &this->vwork[i + 6], RAND_FLOAT_CENTERED(40.0f),
                                         RAND_FLOAT(-10.0f), RAND_FLOAT(20.0f), 44, this->scale, 200, i);
            }
            this->itemDrop = DROP_BOMB;
            Actor_Despawn(this);
            Object_Kill(&this->obj, this->sfxSource);
            func_effect_8007D0E0(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 10.0f);
            break;
    }

    if ((this->dmgType != DMG_NONE) && (this->state < 3)) {
        if (this->dmgType != DMG_BEAM) {
            BonusText_Display(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + 200.0f, 5);
            gHitCount += 6;
            D_ctx_80177850 = 15;
            this->state = 4;
        }
        this->dmgType = DMG_NONE;
    }
}

void Zoness_ZoShrimp_PostLimbDraw(s32 limbIndex, Vec3f* rot, void* thisx) {
    Vec3f sp24 = { 0.0f, 0.0f, 0.0f };
    ZoShrimp* this = (ZoShrimp*) thisx;

    if (this->state == 2) {
        switch (limbIndex) {
            case 1:
                Matrix_MultVec3f(gCalcMatrix, &sp24, this->vwork);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[5]);
                return;
            case 2:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[1]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[6]);
                return;
            case 3:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[2]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[7]);
                return;
            case 4:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[3]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[8]);
                return;
            case 5:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[4]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[9]);
                break;
        }
    }
}

void Zoness_ZoShrimp_Update(ZoShrimp* this) {
    Vec3f src;
    Vec3f dest;
    f32 sp74;
    s32 sp70;
    s32 i;

    switch (this->state) {
        case 0:
            Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
            Matrix_RotateX(gCalcMatrix, 5.497787f, MTXF_APPLY);
            src.y = 0.0f;
            src.x = 0.0f;
            src.z = (this->obj.rot.x * 10.0f) + 15.0f;
            Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);
            this->vel.x = dest.x;
            this->vel.y = dest.y;
            this->vel.z = dest.z;
            this->health = 10;
            this->state++;
            break;

        case 1:
            Math_SmoothStepToF(&this->vel.y, -30.0f, 0.1f, 1.0f, 0.01f);

            if (this->obj.pos.y < 0.0f) {
                this->iwork[0] = 0;
            }
            if (this->obj.pos.y < -50.0f) {
                Object_Kill(&this->obj, this->sfxSource);
            }

            if (this->vel.y > 0.0f) {
                if (this->animFrame < 17) {
                    this->animFrame++;
                }
            } else {
                if (this->animFrame < Animation_GetFrameCount(&D_ZO_6021ABC)) {
                    this->animFrame++;
                }
            }

            this->obj.rot.x += 20.0f;
            this->obj.rot.x = Math_ModF(this->obj.rot.x, 360.0f);

            if ((this->dmgType != DMG_NONE) && (this->health != 0)) {
                this->dmgType = DMG_NONE;
                this->health -= this->damage;
                if (this->health <= 0) {
                    this->health = 0;
                    this->state++;
                }
            }
            break;

        case 2:
            for (i = 0; i < 5; i++) {
                Zoness_ActorDebris_Spawn(&this->vwork[i], &this->vwork[5 + i], RAND_FLOAT_CENTERED(20.0f),
                                         RAND_FLOAT(-10.0f), RAND_FLOAT(10.0f), 43, this->scale, 200, i);
            }
            this->itemDrop = DROP_NONE;
            Actor_Despawn(this);
            Object_Kill(&this->obj, this->sfxSource);
            func_effect_8007D0E0(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 3.0f);
            Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_BIRD_DOWN);
            break;
    }

    if ((this->iwork[0] == 0) &&
        (Play_CheckDynaFloorCollision(&sp74, &sp70, this->obj.pos.x, this->obj.pos.y, this->obj.pos.z) != 0)) {
        this->iwork[0]++;
        Effect_Effect391_Spawn(this->obj.pos.x, sp74, this->obj.pos.z, 0.0f, 0.7f);
        if (this->vel.y >= 0.0f) {
            AUDIO_PLAY_SFX(NA_SE_OUT_SPLASH_L, this->sfxSource, 4);
        } else {
            AUDIO_PLAY_SFX(NA_SE_IN_SPLASH_L, this->sfxSource, 4);
        }
    }
}

void Zoness_ZoShrimp_Draw(ZoShrimp* this) {
    Vec3f frameTable[20];

    Animation_GetFrameData(&D_ZO_6021ABC, this->animFrame, frameTable);
    Animation_DrawSkeleton(3, D_ZO_6021B88, frameTable, NULL, Zoness_ZoShrimp_PostLimbDraw, this, gCalcMatrix);
}

void Zoness_ZoObnema_PostLimbDraw(s32 limbIndex, Vec3f* rot, void* thisx) {
    Vec3f sp24 = { 0.0f, 0.0f, 0.0f };
    ZoObnema* this = (ZoObnema*) thisx;

    if (this->state == 3) {
        switch (limbIndex) {
            case 1:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[0]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[9]);
                return;
            case 2:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[1]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[10]);
                return;
            case 3:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[2]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[11]);
                return;
            case 4:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[3]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[12]);
                return;
            case 5:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[4]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[13]);
                return;
            case 6:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[5]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[14]);
                return;
            case 7:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[6]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[15]);
                return;
            case 8:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[7]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[16]);
                return;
            case 13:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[8]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[17]);
                break;
        }
    }
}

void Zoness_ZoObnema_Update(ZoObnema* this) {
    s32 i;
    Vec3f src;
    Vec3f dest;
    f32 sp70;
    s32 sp6C;

    switch (this->state) {
        case 0:
            this->obj.pos.y = 380.0f;
            this->state = 1;
            break;

        case 1:
            Math_SmoothStepToF(&this->vel.x, 0.0f, 0.1f, 1.0f, 0.0001);
            Math_SmoothStepToF(&this->vel.z, 0.0f, 0.1f, 1.0f, 0.0001f);
            if (this->timer_0BC == 0) {
                this->animFrame++;
                if (this->animFrame == 5) {
                    Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
                    src.x = 0.0f;
                    src.y = 0.0f;
                    src.z = 50.0f;
                    Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);
                    this->vel.x = dest.x;
                    this->vel.z = dest.z;
                    this->state = 2;
                }
            }
            break;

        case 2:
            Math_SmoothStepToF(&this->vel.x, 0.0f, 0.1f, 1.0f, 0.0001f);
            Math_SmoothStepToF(&this->vel.z, 0.0f, 0.1f, 1.0f, 0.0001f);
            if (this->animFrame < Animation_GetFrameCount(&D_ZO_601AFB8)) {
                this->animFrame++;
            } else {
                this->animFrame = 0;
                this->timer_0BC = 30;
                this->state = 1;
            }
            break;

        case 3:
            for (i = 0; i < 9; i++) {
                Zoness_ActorDebris_Spawn(&this->vwork[i], &this->vwork[9 + i], RAND_FLOAT_CENTERED(40.0f),
                                         RAND_FLOAT(-10.0f), RAND_FLOAT(20.0f), 59, this->scale, 200, i);
            }
            this->itemDrop = DROP_BOMB_33p;
            Actor_Despawn(this);
            Object_Kill(&this->obj, this->sfxSource);
            func_effect_8007D0E0(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 10.0f);
            break;
    }

    if (this->dmgType != DMG_NONE) {
        if (this->dmgType != DMG_BEAM) {
            if ((this->state != 0) && (this->state != 3)) {
                BonusText_Display(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + 200.0f, 2);
                gHitCount += 3;
                D_ctx_80177850 = 15;
                this->state = 3;
            }
        } else {
            AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
        }
        this->dmgType = DMG_NONE;
    }

    if (Play_CheckDynaFloorCollision(&sp70, &sp6C, this->obj.pos.x, this->obj.pos.y - 1000.0f, this->obj.pos.z)) {
        Math_SmoothStepToF(&this->obj.pos.y, sp70 + 300.0f, 0.1f, 20.0f, 0);
    }
}

void Zoness_ZoObnema_Draw(Actor* actor) {
    Vec3f sp28[30];

    Animation_GetFrameData(&D_ZO_601AFB8, actor->animFrame, sp28);
    Animation_DrawSkeleton(2, D_ZO_601B184, sp28, NULL, Zoness_ZoObnema_PostLimbDraw, actor, gCalcMatrix);
}

s32 D_i3_801BF5F0[6] = {
    20, 40, 20, 20, 10, 10,
};
f32 D_i3_801BF608[6] = {
    -45.0f, 0.0f, -45.0f, 0.0f, -45.0f, 0.0f,
};

void Zoness_ZoSarumarine_Init(ZoSarumarine* this) {
    s32 i;

    gBossActive = true;
    gBossFrameCount = 0;
    this->vel.z = -40.0f;

    for (i = 0; i < ZO_LIMB_MAX; i++) {
        sZoLimbTimers[i] = 0;
    }
    for (i = 0; i < ZO_BSS_MAX; i++) {
        sZoSwork[i] = 0;
    }
    for (i = 0; i < ZO_BSF_MAX; i++) {
        sZoFwork[i] = 0.0f;
    }
    sZoFwork[ZO_BSF_32_X] = sZoFwork[ZO_BSF_99_X] = sZoFwork[ZO_BSF_60_X] = sZoFwork[ZO_BSF_52_X] =
        sZoFwork[ZO_BSF_106_X] = sZoFwork[ZO_BSF_93_X] = sZoFwork[ZO_BSF_96_X] = sZoFwork[ZO_BSF_29_X] =
            sZoFwork[ZO_BSF_109_X] = sZoFwork[ZO_BSF_43_X] = sZoFwork[ZO_BSF_102_X] = sZoFwork[ZO_BSF_37_X] =
                sZoFwork[ZO_BSF_46_X] = sZoFwork[ZO_BSF_68_X] = sZoFwork[ZO_BSF_40_X] = sZoFwork[ZO_BSF_65_X] =
                    sZoFwork[ZO_BSF_55_X] = this->obj.pos.x;
    sZoFwork[ZO_BSF_32_Y] = sZoFwork[ZO_BSF_99_Y] = sZoFwork[ZO_BSF_60_Y] = sZoFwork[ZO_BSF_52_Y] =
        sZoFwork[ZO_BSF_106_Y] = sZoFwork[ZO_BSF_93_Y] = sZoFwork[ZO_BSF_96_Y] = sZoFwork[ZO_BSF_29_Y] =
            sZoFwork[ZO_BSF_109_Y] = sZoFwork[ZO_BSF_43_Y] = sZoFwork[ZO_BSF_102_Y] = sZoFwork[ZO_BSF_37_Y] =
                sZoFwork[ZO_BSF_46_Y] = sZoFwork[ZO_BSF_68_Y] = sZoFwork[ZO_BSF_40_Y] = sZoFwork[ZO_BSF_65_Y] =
                    sZoFwork[ZO_BSF_55_Y] = this->obj.pos.y;
    sZoFwork[ZO_BSF_32_Z] = sZoFwork[ZO_BSF_99_Z] = sZoFwork[ZO_BSF_60_Z] = sZoFwork[ZO_BSF_52_Z] =
        sZoFwork[ZO_BSF_106_Z] = sZoFwork[ZO_BSF_93_Z] = sZoFwork[ZO_BSF_96_Z] = sZoFwork[ZO_BSF_29_Z] =
            sZoFwork[ZO_BSF_109_Z] = sZoFwork[ZO_BSF_43_Z] = sZoFwork[ZO_BSF_102_Z] = sZoFwork[ZO_BSF_37_Z] =
                sZoFwork[ZO_BSF_46_Z] = sZoFwork[ZO_BSF_68_Z] = sZoFwork[ZO_BSF_40_Z] = sZoFwork[ZO_BSF_65_Z] =
                    sZoFwork[ZO_BSF_55_Z] = this->obj.pos.z;

    sZoSwork[ZO_BSS_8] = 40;
    sZoSwork[ZO_BSS_9] = 40;
    sZoSwork[ZO_BSS_10] = 40;
    sZoSwork[ZO_BSS_11] = 20;
    sZoSwork[ZO_BSS_12] = 20;
    sZoSwork[ZO_BSS_13] = 61;

    this->health = 300;
    this->obj.pos.y = -1800.0f;
    this->obj.rot.y = 180.0f;

    sZoFwork[ZO_BSF_28] = -2600.0f;
    sZoFwork[ZO_BSF_1] = -130.0f;
    sZoFwork[ZO_BSF_11] = 130.0f;

    sZoFwork[ZO_BSF_26] = 30.0f;
    sZoFwork[ZO_BSF_23] = 30.0f;

    sZoSwork[ZO_BSS_43] = 255;
    sZoSwork[ZO_BSS_44] = 255;
    sZoFwork[ZO_BSF_25] = 0.0f;

    this->timer_050 = 200;
    this->timer_052 = 280;

    sZoSwork[ZO_BSS_37] = 255;

    for (i = 0; i < 2; i++) {
        Actor_Initialize(&gActors[i]);
        gActors[i].obj.status = OBJ_INIT;
        gActors[i].obj.id = OBJ_ACTOR_ZO_CRANE_MAGNET + i;
        gActors[i].obj.pos.x = this->obj.pos.x;
        gActors[i].obj.pos.y = this->obj.pos.y;
        gActors[i].obj.pos.z = this->obj.pos.z;
        Object_SetInfo(&gActors[i].info, gActors[i].obj.id);
    }
    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 40);
    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 40);

    ZO_HIT_3(this)->b.z.offset = ZO_HIT_4(this)->b.z.offset = -561.6f;
    ZO_HIT_8(this, 0)->z.offset = ZO_HIT_8(this, 1)->z.offset = -213.2f;
    ZO_HIT_10(this, 0)->z.offset = ZO_HIT_10(this, 1)->z.offset = -351.0f;
    ZO_HIT_12(this)->z.offset = -883.99994f;
    ZO_HIT_12(this)->z.size = 244.4f;
    ZO_HIT_12(this)->y.offset = 863.19995f;
    ZO_HIT_12(this)->y.size = 171.59999f;
    ZO_HIT_12(this)->x.offset = 0.f;
    ZO_HIT_12(this)->x.size = 93.6f;
}

void Zoness_80193628(Object* obj, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    Vec3f src = { 0.0f, 0.0f, 40.0f };
    Vec3f dest;

    Matrix_RotateY(gCalcMatrix, obj->rot.y * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, obj->rot.x * M_DTOR, MTXF_APPLY);
    Matrix_RotateZ(gCalcMatrix, obj->rot.z * M_DTOR, MTXF_APPLY);
    Matrix_RotateY(gCalcMatrix, M_DTOR * arg5, MTXF_APPLY);
    Matrix_RotateX(gCalcMatrix, M_DTOR * arg4, MTXF_APPLY);
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);
    func_effect_8007F04C(OBJ_EFFECT_ENEMY_LASER_1, arg1 + dest.x + arg6, arg2 + dest.y, arg3 + dest.z, arg4, arg5, 0.0f,
                         obj->rot.x, obj->rot.y, obj->rot.z, dest.x + arg6, dest.y, dest.z, 1.0f);
}

void Zoness_Effect394_Setup(Effect394* this, f32 xPos, f32 yPos, f32 zPos, f32 yRot) {
    Vec3f src;
    Vec3f dest;

    Effect_Initialize(this);
    Matrix_RotateY(gCalcMatrix, M_DTOR * yRot, MTXF_NEW);
    src.x = 0.0f;
    src.y = 0.0f;
    src.z = 10.0f;
    Matrix_MultVec3f(gCalcMatrix, &src, &dest);
    this->vel.x = dest.x;
    this->vel.y = dest.y;
    this->vel.z = dest.z;
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_EFFECT_394;
    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;
    this->unk_44 = 100;
    this->scale2 = 3.0f;
    this->scale1 = RAND_FLOAT_CENTERED(20.0f);
    this->unk_78 = 100;
    this->unk_7A = 14;
    this->obj.rot.z = RAND_FLOAT(360.0f);
    Object_SetInfo(&this->info, this->obj.id);
}

void Zoness_Effect394_Spawn(f32 xPos, f32 yPos, f32 zPos, f32 yRot) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Zoness_Effect394_Setup(&gEffects[i], xPos, yPos, zPos, yRot);
            break;
        }
    }
}

void Zoness_Effect394_Setup2(Effect394* this, f32 xPos, f32 yPos, f32 zPos, f32 yRot, s32 arg5) {
    Vec3f src;
    Vec3f dest;

    Effect_Initialize(this);
    Matrix_RotateY(gCalcMatrix, M_DTOR * yRot, MTXF_NEW);
    src.x = 0.0f;
    src.y = 0.0f;
    src.z = 20.0f;
    Matrix_MultVec3f(gCalcMatrix, &src, &dest);
    this->vel.x = dest.x;
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_EFFECT_394;
    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;
    this->scale2 = 8.0f;
    this->unk_44 = arg5;
    this->scale1 = RAND_FLOAT_CENTERED(200.0f);
    this->obj.rot.z = RAND_FLOAT(360.0f);
    this->state = 1;
    this->unk_78 = 100;
    this->unk_7A = 13;
    Object_SetInfo(&this->info, this->obj.id);
}

void Zoness_Effect394_Spawn2(f32 xPos, f32 yPos, f32 zPos, f32 yRot, s32 arg5) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Zoness_Effect394_Setup2(&gEffects[i], xPos, yPos, zPos, yRot, arg5);
            break;
        }
    }
}

void Zoness_Effect394_Setup3(Effect394* this, f32 xPos, f32 yPos, f32 zPos, f32 scale) {
    Effect_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_EFFECT_394;
    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;
    this->vel.x = RAND_FLOAT_CENTERED(5.0f);
    this->vel.y = RAND_FLOAT_CENTERED(3.0f);

    this->unk_48 = 3;
    if (Rand_ZeroOne() < 0.5f) {
        this->unk_48 = -this->unk_48;
    }
    this->unk_4A = 180;
    this->unk_46 = 8;
    this->unk_78 = 101;
    this->unk_7A = 15;
    this->scale2 = scale * 0.25f;
    this->obj.rot.z = RAND_FLOAT(360.0f);

    if (scale == 6.0f) {
        this->vel.z = gPlayer[0].vel.z * 0.6f;
    }
    Object_SetInfo(&this->info, this->obj.id);
}

void Zoness_Effect394_Spawn3(f32 xPos, f32 yPos, f32 zPos, f32 scale) {
    s32 i;

    for (i = 80; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Zoness_Effect394_Setup3(&gEffects[i], xPos, yPos, zPos, scale);
            break;
        }
    }
}

f32 Zoness_80193CC8(s32 arg0) {
    f32 var_fv1 = arg0 * 0.5f;

    if (var_fv1 > 8.0f) {
        var_fv1 = 8.0f;
    }
    return var_fv1;
}

bool Zoness_ZoSarumarine_OverrideLimbDraw(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    ZoSarumarine* this = (ZoSarumarine*) thisx;

    if (sZoLimbTimers[limbIndex] == LIMB_DESTROYED) {
        *dList = NULL;
    }

    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);

    if (sZoSwork[ZO_BSS_37] != 255) {
        RCP_SetupDL_46();
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, sZoSwork[ZO_BSS_37], sZoSwork[ZO_BSS_37]);
    } else if ((sZoLimbTimers[limbIndex] % 2) == 0) {
        RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
    } else {
        RCP_SetupDL_27();
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
    }

    switch (limbIndex) {
        case ZO_LIMB_1:
            if (sZoFwork[ZO_BSF_0] == 0.0f) {
                rot->x += sZoFwork[ZO_BSF_112];
                rot->y += sZoFwork[ZO_BSF_112];
                rot->z += sZoFwork[ZO_BSF_112];
            } else {
                rot->z += sZoFwork[ZO_BSF_0];
            }
            /* fallthrough */
        case ZO_LIMB_12:
            gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
            break;

        case ZO_LIMB_2:
            rot->x += -sZoFwork[ZO_BSF_114] + sZoFwork[ZO_BSF_1];
            rot->y += -sZoFwork[ZO_BSF_114];
            rot->z += -sZoFwork[ZO_BSF_114] + sZoFwork[ZO_BSF_83];

            pos->x += sZoFwork[ZO_BSF_84];
            pos->y += sZoFwork[ZO_BSF_85];
            break;

        case ZO_LIMB_4:
        case ZO_LIMB_16:
            rot->x += sZoFwork[ZO_BSF_2];
            break;

        case ZO_LIMB_5:
            rot->x += -sZoFwork[ZO_BSF_115];
            rot->y += -sZoFwork[ZO_BSF_115];
            rot->z += -sZoFwork[ZO_BSF_115] + sZoFwork[ZO_BSF_3];
            break;

        case ZO_LIMB_6:
            rot->x += sZoFwork[ZO_BSF_4];
            rot->z += sZoFwork[ZO_BSF_90];

            pos->x += sZoFwork[ZO_BSF_91];
            pos->y += sZoFwork[ZO_BSF_92];
            break;

        case ZO_LIMB_7:
            rot->x -= sZoFwork[ZO_BSF_116];
            rot->y -= sZoFwork[ZO_BSF_116];
            rot->z -= sZoFwork[ZO_BSF_116];

            pos->x += sZoFwork[ZO_BSF_6];
            break;

        case ZO_LIMB_18:
            rot->x += -sZoFwork[ZO_BSF_116];
            rot->y += -sZoFwork[ZO_BSF_116];
            rot->z += -sZoFwork[ZO_BSF_116] + sZoFwork[ZO_BSF_5];
            break;

        case ZO_LIMB_8:
            rot->z += sZoFwork[ZO_BSF_7];
            rot->y += -sZoFwork[ZO_BSF_8];
            break;

        case ZO_LIMB_9:
            rot->z += sZoFwork[ZO_BSF_9];
            rot->y += -sZoFwork[ZO_BSF_10];
            break;

        case ZO_LIMB_10:
            rot->x += sZoFwork[ZO_BSF_11] + sZoFwork[ZO_BSF_113];
            rot->y += -sZoFwork[ZO_BSF_113];
            rot->z += sZoFwork[ZO_BSF_80] + sZoFwork[ZO_BSF_113];

            pos->x += sZoFwork[ZO_BSF_81];
            pos->y += sZoFwork[ZO_BSF_82];
            break;

        case ZO_LIMB_11:
            rot->x += -sZoFwork[ZO_BSF_117];
            rot->y += -sZoFwork[ZO_BSF_117];
            rot->z += -sZoFwork[ZO_BSF_117];

            pos->x += sZoFwork[ZO_BSF_13];
            break;

        case ZO_LIMB_19:
            rot->x += -sZoFwork[ZO_BSF_117];
            rot->y += -sZoFwork[ZO_BSF_117];
            rot->z += -sZoFwork[ZO_BSF_117] + sZoFwork[ZO_BSF_12];
            break;

        case ZO_LIMB_15:
            rot->x += sZoFwork[ZO_BSF_14] - sZoFwork[ZO_BSF_19] - this->obj.rot.y + sZoFwork[ZO_BSF_112];
            rot->y += sZoFwork[ZO_BSF_112];
            rot->z += sZoFwork[ZO_BSF_86] + sZoFwork[ZO_BSF_112];

            pos->x += sZoFwork[ZO_BSF_87];
            pos->y += sZoFwork[ZO_BSF_88];
            break;

        case ZO_LIMB_21:
            rot->x += -sZoFwork[ZO_BSF_116] + sZoFwork[ZO_BSF_15];
            rot->y += -sZoFwork[ZO_BSF_116];
            rot->z += -sZoFwork[ZO_BSF_116];
            break;

        case ZO_LIMB_22:
            pos->x += sZoFwork[ZO_BSF_17] + this->fwork[ZO_FWK_1];
            break;

        case ZO_LIMB_23:
            rot->x += -sZoFwork[ZO_BSF_117] + sZoFwork[ZO_BSF_16];
            rot->y += -sZoFwork[ZO_BSF_117];
            rot->z += -sZoFwork[ZO_BSF_117];
            break;

        case ZO_LIMB_24:
            pos->x += sZoFwork[ZO_BSF_18] + this->fwork[ZO_FWK_2];
            break;

        case ZO_LIMB_25:
            rot->x += sZoFwork[ZO_BSF_19];

            pos->y += sZoFwork[ZO_BSF_105];
            break;
    }
    return false;
}

void Zoness_ZoSarumarine_PostLimbDraw(s32 limbIndex, Vec3f* rot, void* thisx) {
    Vec3f spB4;
    ZoSarumarine* this = (ZoSarumarine*) thisx;
    Vec3f spA4 = { 96.0f, 199.0f, -9.0f };
    Vec3f sp98 = { 50.0f, 150.0f, -20.0f };
    Vec3f sp8C = { 50.0f, 150.0f, 20.0f };
    Vec3f sp80 = { 0.0f, 0.0f, 0.0f };
    Vec3f sp74 = { 210.0f, -50.0f, 0.0f };
    Vec3f sp68 = { 50.0f, 70.0f, 0.0f };
    Vec3f sp5C = { 166.0f, -174.0f, -25.0f };
    Vec3f sp50 = { 166.0f, -174.0f, 25.0f };
    Vec3f sp44 = { 50.0f, 0.0f, 0.0f };
    Vec3f sp38 = { 150.0f, 0.0f, 0.0f };
    Vec3f sp2C = { 0.0f, 0.0f, 0.0f };
    Vec3f sp20 = { 0.0f, 0.0f, 0.0f };
    f32 var_fv1;

    switch (limbIndex) {
        case ZO_LIMB_2:
            Matrix_MultVec3f(gCalcMatrix, &spA4, &spB4);
            sZoFwork[ZO_BSF_32_X] = spB4.x;
            sZoFwork[ZO_BSF_32_Y] = spB4.y;
            sZoFwork[ZO_BSF_32_Z] = spB4.z;
            break;

        case ZO_LIMB_4:
            Matrix_MultVec3f(gCalcMatrix, &sp38, &spB4);
            sZoFwork[ZO_BSF_99_X] = spB4.x;
            sZoFwork[ZO_BSF_99_Y] = spB4.y;
            sZoFwork[ZO_BSF_99_Z] = spB4.z;
            break;

        case ZO_LIMB_5:
            var_fv1 = -1.0f;
            if (sZoFwork[ZO_BSF_4] < 0.0f) {
                var_fv1 = 1.0f;
            }
            sp74.z = fabsf(sZoFwork[ZO_BSF_4] / 10.0f) * var_fv1;
            Matrix_MultVec3f(gCalcMatrix, &sp74, &spB4);
            sZoFwork[ZO_BSF_60_X] = spB4.x;
            sZoFwork[ZO_BSF_60_Y] = spB4.y;
            sZoFwork[ZO_BSF_60_Z] = spB4.z;
            break;

        case ZO_LIMB_6:
            Matrix_MultVec3f(gCalcMatrix, &sp80, &spB4);
            sZoFwork[ZO_BSF_52_X] = spB4.x;
            sZoFwork[ZO_BSF_52_Y] = spB4.y;
            sZoFwork[ZO_BSF_52_Z] = spB4.z;
            break;

        case ZO_LIMB_7:
            Matrix_MultVec3f(gCalcMatrix, &sp2C, &spB4);
            sZoFwork[ZO_BSF_106_X] = spB4.x;
            sZoFwork[ZO_BSF_106_Y] = spB4.y;
            sZoFwork[ZO_BSF_106_Z] = spB4.z;
            break;

        case ZO_LIMB_8:
            Matrix_MultVec3f(gCalcMatrix, &sp44, &spB4);
            sZoFwork[ZO_BSF_93_X] = spB4.x;
            sZoFwork[ZO_BSF_93_Y] = spB4.y;
            sZoFwork[ZO_BSF_93_Z] = spB4.z;
            break;

        case ZO_LIMB_9:
            Matrix_MultVec3f(gCalcMatrix, &sp44, &spB4);
            sZoFwork[ZO_BSF_96_X] = spB4.x;
            sZoFwork[ZO_BSF_96_Y] = spB4.y;
            sZoFwork[ZO_BSF_96_Z] = spB4.z;
            break;

        case ZO_LIMB_10:
            Matrix_MultVec3f(gCalcMatrix, &spA4, &spB4);
            sZoFwork[ZO_BSF_29_X] = spB4.x;
            sZoFwork[ZO_BSF_29_Y] = spB4.y;
            sZoFwork[ZO_BSF_29_Z] = spB4.z;
            break;

        case ZO_LIMB_11:
            Matrix_MultVec3f(gCalcMatrix, &sp20, &spB4);
            sZoFwork[ZO_BSF_109_X] = spB4.x;
            sZoFwork[ZO_BSF_109_Y] = spB4.y;
            sZoFwork[ZO_BSF_109_Z] = spB4.z;
            break;

        case ZO_LIMB_14:
            Matrix_MultVec3f(gCalcMatrix, &sp80, &spB4);
            sZoFwork[ZO_BSF_43_X] = spB4.x;
            sZoFwork[ZO_BSF_43_Y] = spB4.y;
            sZoFwork[ZO_BSF_43_Z] = spB4.z;
            break;

        case ZO_LIMB_16:
            Matrix_MultVec3f(gCalcMatrix, &sp38, &spB4);
            sZoFwork[ZO_BSF_102_X] = spB4.x;
            sZoFwork[ZO_BSF_102_Y] = spB4.y;
            sZoFwork[ZO_BSF_102_Z] = spB4.z;
            break;

        case ZO_LIMB_22:
            Matrix_MultVec3f(gCalcMatrix, &sp98, &spB4);
            sZoFwork[ZO_BSF_37_X] = spB4.x;
            sZoFwork[ZO_BSF_37_Y] = spB4.y;
            sZoFwork[ZO_BSF_37_Z] = spB4.z;
            Matrix_MultVec3f(gCalcMatrix, &sp80, &spB4);
            sZoFwork[ZO_BSF_46_X] = spB4.x;
            sZoFwork[ZO_BSF_46_Y] = spB4.y;
            sZoFwork[ZO_BSF_46_Z] = spB4.z;
            Matrix_MultVec3f(gCalcMatrix, &sp5C, &spB4);
            sZoFwork[ZO_BSF_68_X] = spB4.x;
            sZoFwork[ZO_BSF_68_Y] = spB4.y;
            sZoFwork[ZO_BSF_68_Z] = spB4.z;
            break;

        case ZO_LIMB_24:
            Matrix_MultVec3f(gCalcMatrix, &sp8C, &spB4);
            sZoFwork[ZO_BSF_40_X] = spB4.x;
            sZoFwork[ZO_BSF_40_Y] = spB4.y;
            sZoFwork[ZO_BSF_40_Z] = spB4.z;
            Matrix_MultVec3f(gCalcMatrix, &sp80, &spB4);
            sZoFwork[ZO_BSF_49_X] = spB4.x;
            sZoFwork[ZO_BSF_49_Y] = spB4.y;
            sZoFwork[ZO_BSF_49_Z] = spB4.z;
            Matrix_MultVec3f(gCalcMatrix, &sp50, &spB4);
            sZoFwork[ZO_BSF_71_X] = spB4.x;
            sZoFwork[ZO_BSF_71_Y] = spB4.y;
            sZoFwork[ZO_BSF_71_Z] = spB4.z;
            break;

        case ZO_LIMB_25:
            Matrix_MultVec3f(gCalcMatrix, &sp68, &spB4);
            sZoFwork[ZO_BSF_65_X] = spB4.x;
            sZoFwork[ZO_BSF_65_Y] = spB4.y;
            sZoFwork[ZO_BSF_65_Z] = spB4.z;
            break;

        case ZO_LIMB_36:
            Matrix_MultVec3f(gCalcMatrix, &sp80, &spB4);
            sZoFwork[ZO_BSF_55_X] = spB4.x;
            sZoFwork[ZO_BSF_55_Y] = spB4.y;
            sZoFwork[ZO_BSF_55_Z] = spB4.z;
            break;
    }
}

void Zoness_ZoSarumarine_Draw(ZoSarumarine* this) {
    Matrix_Translate(gCalcMatrix, 0.0f, this->fwork[ZO_FWK_3], 0.0f, MTXF_APPLY);
    Matrix_Scale(gCalcMatrix, 2.6f, 2.6f, 2.6f, MTXF_APPLY);
    Animation_DrawSkeleton(3, aZoSarumarineSkel, this->vwork, Zoness_ZoSarumarine_OverrideLimbDraw,
                           Zoness_ZoSarumarine_PostLimbDraw, this, gCalcMatrix);
}

f32 D_i3_801BF6BC[2] = { -600.0f, -3400.0f };
f32 D_i3_801BF6C4[2] = { 330.0f, 30.0f };
f32 D_i3_801BF6CC[2] = { 250.0f, -250.0f };
f32 D_i3_801BF6D4[2] = { 330.0f, 30.0f };

void Zoness_ZoSarumarine_Update(ZoSarumarine* this) {
    f32 sp134;
    s32 sp130;
    s32 i;
    s32 var_s0;
    s32 sp124;
    f32 sp120;
    f32 sp11C;
    f32 sp118;
    f32 sp114;
    f32 sp110;
    f32 sp10C;
    f32 sp108;
    f32 sp104;
    f32 sp100;
    f32 spFC;
    s32 dmgType;
    f32 padF4;
    s32 j;
    Vec3f spE4;
    Vec3f spD8;
    Vec3f spCC;
    Vec3f spC0;
    Vec3f spB4;
    Vec3f spA8 = { 615.0f, 532.0f, -80.0f };
    Vec3f sp9C = { -615.0f, 532.0f, -80.0f };
    Vec3f sp90 = { 0.0f, 0.0f, 0.0f };
    Vec3f sp84 = { 0.0f, 0.0f, 0.0f };
    Vec3f sp78;
    Vec3f sp6C;
    Vec3f sp60 = { 0.0f, 0.0f, 40.0f };

    PRINTF(" Enm->hitNO %d\n", this->dmgPart);

    gBossFrameCount++;

    if ((this->state != 0) || ((this->state == 0) && (this->timer_050 < 50))) {
        Math_SmoothStepToF(&sZoFwork[ZO_BSF_24], sZoFwork[ZO_BSF_23], 0.1f, 2.0f, 0.00001f);
        Math_SmoothStepToF(&this->obj.pos.y, sZoFwork[ZO_BSF_25], 0.1f, sZoFwork[ZO_BSF_24], 0.00001f);
    }

    if (sZoSwork[ZO_BSS_24] == 0) {
        Math_SmoothStepToF(&sZoFwork[ZO_BSF_27], sZoFwork[ZO_BSF_26], 0.1f, 2.0f, 0.00001f);
        Math_SmoothStepToF(&this->obj.pos.z, gPlayer[0].cam.eye.z - gPathProgress + sZoFwork[ZO_BSF_28], 0.1f,
                           sZoFwork[ZO_BSF_27], 0.00001f);
    }

    if ((gGameFrameCount % 4U) == 0) {
        if ((this->obj.rot.y <= 90.0f) || (this->obj.rot.y >= 270.0f)) {
            sZoSwork[ZO_BSS_43] = this->obj.rot.y;
            if (sZoSwork[ZO_BSS_43] > 270) {
                sZoSwork[ZO_BSS_43] = 360 - sZoSwork[ZO_BSS_43];
            }
            sZoSwork[ZO_BSS_43] *= 2;
            sZoSwork[ZO_BSS_43] = 255 - sZoSwork[ZO_BSS_43];
            if (sZoSwork[ZO_BSS_43] < 0) {
                sZoSwork[ZO_BSS_43] = 0;
            }
            Zoness_Effect394_Spawn2(sZoFwork[ZO_BSF_102_X], sZoFwork[ZO_BSF_102_Y], sZoFwork[ZO_BSF_102_Z],
                                    this->obj.rot.y, sZoSwork[ZO_BSS_43]);
            sZoSwork[ZO_BSS_44] = 255;
        } else {
            sZoSwork[ZO_BSS_44] = (s32) this->obj.rot.y - 180.0f;
            if (sZoSwork[ZO_BSS_44] < 0) {
                sZoSwork[ZO_BSS_44] = -sZoSwork[ZO_BSS_44];
            }
            sZoSwork[ZO_BSS_44] *= 20;
            sZoSwork[ZO_BSS_44] = 255 - sZoSwork[ZO_BSS_44];
            if (sZoSwork[ZO_BSS_44] < 0) {
                sZoSwork[ZO_BSS_44] = 0;
            }
            Zoness_Effect394_Spawn2(sZoFwork[ZO_BSF_99_X], sZoFwork[ZO_BSF_99_Y], sZoFwork[ZO_BSF_99_Z],
                                    this->obj.rot.y, sZoSwork[ZO_BSS_44]);
            sZoSwork[ZO_BSS_43] = 255;
        }
    }

    if (((this->state == 2) || (this->state == 3) || (this->state == 8)) && (gPlayer[0].radioDamageTimer == 2)) {
        if (this->swork[ZO_SWK_8] == 0) {
            Radio_PlayMessage(gMsg_ID_6068, RCID_BOSS_ZONESS);
        }
        this->swork[ZO_SWK_8]++;
        if (this->swork[ZO_SWK_8] >= 5) {
            this->swork[ZO_SWK_8] = 0;
        }
    }

    if ((this->swork[ZO_SWK_9] == 0) && (this->state >= 2) && (this->health != 0)) {
        if (this->swork[ZO_SWK_10] == 0) {
            Effect_Effect382_Spawn(this->obj.pos.x, this->obj.pos.z, 50.0f, 0.0f, 5.0f);
            Effect_Effect382_Spawn(this->obj.pos.x, this->obj.pos.z, 46.0f, 19.0f, 5.0f);
            Effect_Effect382_Spawn(this->obj.pos.x, this->obj.pos.z, 35.0f, 35.0f, 5.0f);
            Effect_Effect382_Spawn(this->obj.pos.x, this->obj.pos.z, 19.0f, 46.0f, 5.0f);
            Effect_Effect382_Spawn(this->obj.pos.x, this->obj.pos.z, 0.0f, 50.0f, 5.0f);
        } else {
            Effect_Effect382_Spawn(this->obj.pos.x, this->obj.pos.z, -50.0f, 0.0f, 5.0f);
            Effect_Effect382_Spawn(this->obj.pos.x, this->obj.pos.z, -46.0f, 19.0f, 5.0f);
            Effect_Effect382_Spawn(this->obj.pos.x, this->obj.pos.z, -35.0f, 35.0f, 5.0f);
            Effect_Effect382_Spawn(this->obj.pos.x, this->obj.pos.z, -19.0f, 46.0f, 5.0f);
            Effect_Effect382_Spawn(this->obj.pos.x, this->obj.pos.z, 0.0f, 50.0f, 5.0f);
        }
        this->swork[ZO_SWK_11]++;
        this->swork[ZO_SWK_11] &= 1;
        this->swork[ZO_SWK_9] = 20;

        if (this->swork[ZO_SWK_11] == 0) {
            this->swork[ZO_SWK_10]++;
            this->swork[ZO_SWK_10] &= 1;
            this->swork[ZO_SWK_9] = 100;
        }
    }

    if (this->swork[ZO_SWK_9] != 0) {
        this->swork[ZO_SWK_9]--;
    }

    switch (this->state) {
        case 0:
            if ((((gGameFrameCount % 8) == 0) || (this->timer_050 == 43)) && (this->swork[ZO_SWK_13] == 0) &&
                ((this->swork[ZO_SWK_12] < 7) || (this->timer_050 == 43))) {
                D_ctx_801779A8[0] = 20;
                if (Play_CheckDynaFloorCollision(&sp134, &sp130, sZoFwork[ZO_BSF_43_X], sZoFwork[ZO_BSF_43_Y] - 300.0f,
                                                 sZoFwork[ZO_BSF_43_Z])) {
                    sp100 = 1.5f;
                    spFC = 2.0f;
                    if (this->timer_050 == 43) {
                        sp100 = 5.0f;
                        spFC = 3.0f;
                        if (sZoSwork[ZO_BSS_55] == 0) {
                            AUDIO_PLAY_BGM(NA_BGM_BOSS_ZO);
                            sZoSwork[ZO_BSS_55] = 1;
                        }
                        Effect_Effect391_Spawn(sZoFwork[ZO_BSF_43_X], sp134, sZoFwork[ZO_BSF_43_Z] + 100.0f, 5.0f,
                                               3.0f);
                        Effect_Effect391_Spawn(sZoFwork[ZO_BSF_43_X], sp134, sZoFwork[ZO_BSF_43_Z] + 100.0f, 5.0f,
                                               3.0f);
                    }

                    Effect_Effect391_Spawn(sZoFwork[ZO_BSF_43_X], sp134, sZoFwork[ZO_BSF_43_Z] + 100.0f, sp100, spFC);

                    if (this->timer_050 == 43) {
                        AUDIO_PLAY_SFX(NA_SE_OUT_SPLASH_L, this->sfxSource, 4);
                    } else {
                        AUDIO_PLAY_SFX(NA_SE_IN_SPLASH_L, this->sfxSource, 4);
                    }
                    this->swork[ZO_SWK_12]++;
                }
            }

            if ((this->timer_050 < 43) && (this->timer_050 >= 31)) {
                D_ctx_801779A8[0] = 20;
            }

            Math_SmoothStepToF(&this->fwork[ZO_FWK_4], 1.0f, 0.1f, 10.0f, 0.0f);

            if (this->timer_050 == 0) {
                if (this->swork[ZO_SWK_3] == 0) {
                    Radio_PlayMessage(gMsg_ID_6069, RCID_BOSS_ZONESS);
                    this->swork[ZO_SWK_3]++;
                }
                Math_SmoothStepToF(&sZoFwork[ZO_BSF_1], sZoFwork[ZO_BSF_74], 0.1f, 2.0f, 0.00001f);
                Math_SmoothStepToF(&sZoFwork[ZO_BSF_11], sZoFwork[ZO_BSF_75], 0.1f, 2.0f, 0.00001f);
                if (this->timer_052 == 0) {
                    this->swork[ZO_SWK_12] = 0;
                    sZoFwork[ZO_BSF_77] = 0.0f;
                    this->swork[ZO_SWK_13] = 1;
                    this->state = 1;
                }
            }
            break;

        case 1:
            Math_SmoothStepToF(&this->fwork[ZO_FWK_4], 100.0f, 0.1f, 1.0f, 0.0f);
            Zoness_8019962C(this, 0.0f);
            Math_SmoothStepToF(&sZoFwork[ZO_BSF_1], sZoFwork[ZO_BSF_74], 0.1f, 2.0f, 0.00001f);
            Math_SmoothStepToF(&sZoFwork[ZO_BSF_11], sZoFwork[ZO_BSF_75], 0.1f, 2.0f, 0.00001f);

            if ((this->timer_050 == 0) && ((gGameFrameCount % 4) == 0)) {
                if (sZoSwork[ZO_BSS_9] != 0) {
                    Zoness_Effect394_Spawn(sZoFwork[ZO_BSF_29_X], sZoFwork[ZO_BSF_29_Y], sZoFwork[ZO_BSF_29_Z],
                                           this->obj.rot.y);
                }
                if (sZoSwork[ZO_BSS_10] != 0) {
                    Zoness_Effect394_Spawn(sZoFwork[ZO_BSF_32_X], sZoFwork[ZO_BSF_32_Y], sZoFwork[ZO_BSF_32_Z],
                                           this->obj.rot.y);
                }

                sZoSwork[ZO_BSS_6]++;
                if (sZoSwork[ZO_BSS_6] > 10) {
                    sZoSwork[ZO_BSS_6] = 0;
                    sZoSwork[ZO_BSS_7]++;
                    this->timer_050 = 30;
                    if ((sZoSwork[ZO_BSS_7] == 1) && (sZoSwork[ZO_BSS_19] == 0)) {
                        sZoFwork[ZO_BSF_74] = 230.0f;
                        sZoFwork[ZO_BSF_75] = -230.0f;
                        Radio_PlayMessage(gMsg_ID_6071, RCID_BOSS_ZONESS);
                    }
                    if ((sZoSwork[ZO_BSS_7] == 1) && (sZoSwork[ZO_BSS_25] != 0) && (sZoSwork[ZO_BSS_29] == 0) &&
                        (sZoSwork[ZO_BSS_19] != 0)) {
                        Radio_PlayMessage(gMsg_ID_6081, RCID_PEPPY);
                        sZoSwork[ZO_BSS_34] = 333;
                    }
                    if ((sZoSwork[ZO_BSS_7] == 1) && (sZoSwork[ZO_BSS_25] == 0) && (sZoSwork[ZO_BSS_19] != 0)) {
                        Radio_PlayMessage(gMsg_ID_6072, RCID_BOSS_ZONESS);
                        sZoSwork[ZO_BSS_25]++;
                        sZoSwork[ZO_BSS_34] = 333;
                    }
                    if (sZoSwork[ZO_BSS_7] >= 2) {
                        sZoSwork[ZO_BSS_7] = 0;
                        this->timer_050 = 0;
                        sZoFwork[ZO_BSF_77] = 0.0f;
                        this->swork[ZO_SWK_4] = 1000;
                        this->state = 3;
                        if (sZoSwork[ZO_BSS_19] == 0) {
                            this->timer_050 = 30;
                            this->swork[ZO_SWK_4] = 0;
                            this->state = 2;
                        }
                    }
                }
            }
            break;

        case 2:
            if (this->timer_050 == 1) {
                sZoSwork[ZO_BSS_20]++;
                sZoFwork[ZO_BSF_77] = 0.0f;
            }
            if (this->timer_050 == 0) {
                Math_SmoothStepToF(&this->fwork[ZO_FWK_4], 100.0f, 0.1f, 1.0f, 0.0f);
                Math_SmoothStepToF(&sZoFwork[ZO_BSF_1], sZoFwork[ZO_BSF_74], 0.2f, 4.0f, 0.00001f);
                Math_SmoothStepToF(&sZoFwork[ZO_BSF_11], sZoFwork[ZO_BSF_75], 0.2f, 4.0f, 0.00001f);
                if ((sZoSwork[ZO_BSS_20] == 0) && (sZoFwork[ZO_BSF_1] == 0.0f)) {
                    this->swork[ZO_SWK_4] = 1000;
                    this->state = 3;
                }
            }
            break;

        case 3:
            if (ZO_HIT_12(this)->z.offset != -883.99994f) {
                ZO_HIT_12(this)->z.offset = -883.99994f; // 13 * 68.0
                ZO_HIT_12(this)->z.size = 244.4f;        // 13 * 18.8
                ZO_HIT_12(this)->y.offset = 863.19995f;  // 13 * 66.4
                ZO_HIT_12(this)->y.size = 171.59999f;    // 13 * 13.2
                ZO_HIT_12(this)->x.offset = 0.0f;
                ZO_HIT_12(this)->x.size = 93.6f; // 13 * 7.2
            }

            Math_SmoothStepToF(&this->fwork[ZO_FWK_4], 100.0f, 0.1f, 1.0f, 0.0f);

            if (this->timer_058 != 0) {
                if ((sZoSwork[ZO_BSS_11] != 0) || (sZoSwork[ZO_BSS_12] != 0)) {
                    Math_SmoothStepToF(&sZoFwork[ZO_BSF_21], sZoFwork[ZO_BSF_20], 0.1f, 2.0f, 0.00001f);
                    Math_SmoothStepToF(&this->obj.pos.x, D_i3_801BF6CC[sZoSwork[ZO_BSS_21]], 0.1f, sZoFwork[ZO_BSF_21],
                                       0.00001f);
                }
                if (sZoSwork[ZO_BSS_24] == 0) {
                    Math_SmoothStepToAngle(&sZoFwork[ZO_BSF_79], sZoFwork[ZO_BSF_78], 0.1f, 2.0f, 0.0001f);
                    Math_SmoothStepToAngle(&this->obj.rot.y, D_i3_801BF6D4[sZoSwork[ZO_BSS_21]], 0.1f,
                                           sZoFwork[ZO_BSF_79], 0.00001f);
                }
            } else {
                this->timer_058 = 100;
                sZoFwork[ZO_BSF_20] = 5.0f;
                sZoFwork[ZO_BSF_21] = sZoFwork[ZO_BSF_79] = 0.0f;
                sZoFwork[ZO_BSF_78] = 2.0f;
                sZoSwork[ZO_BSS_21]++;
                if (sZoSwork[ZO_BSS_21] >= 2) {
                    sZoSwork[ZO_BSS_21] = 0;
                }
            }

            if ((this->swork[ZO_SWK_4] == 0) && ((sZoSwork[ZO_BSS_9] != 0) || (sZoSwork[ZO_BSS_10] != 0))) {
                Zoness_80198ECC(this);
            }
            if ((sZoSwork[ZO_BSS_32] == 0) && (sZoSwork[ZO_BSS_34] == 1) && (sZoSwork[ZO_BSS_24] == 0)) {
                Radio_PlayMessage(gMsg_ID_6080, RCID_PEPPY);
                sZoSwork[ZO_BSS_34] = 500;
            }
            if (sZoSwork[ZO_BSS_4] == 0) {
                sZoSwork[ZO_BSS_4] = 100;
                Zoness_801989FC(this);
            }
            if (sZoSwork[ZO_BSS_24] != 0) {
                sZoSwork[ZO_BSS_20] = 1;

                if (this->swork[ZO_SWK_7] == 0) {
                    this->swork[ZO_SWK_7]++;
                    this->swork[ZO_SWK_7] &= 1;
                    Radio_PlayMessage(gMsg_ID_6078, RCID_BOSS_ZONESS);
                }

                if (this->timer_056 == 0) {
                    this->swork[ZO_SWK_1]++;
                    this->swork[ZO_SWK_1] &= 1;
                    this->timer_056 = 100;
                }

                this->fwork[ZO_FWK_5] += 4.0f;
                this->vel.x = COS_DEG(this->fwork[ZO_FWK_5]) * 40.0f;
                padF4 = Math_Atan2F(this->fwork[ZO_FWK_6] - this->obj.pos.x, gPlayer[0].cam.eye.z - gPathProgress +
                                                                                 D_i3_801BF6BC[this->swork[ZO_SWK_1]] -
                                                                                 this->obj.pos.z);
                padF4 = Math_RadToDeg(padF4);

                Math_SmoothStepToAngle(&this->fwork[ZO_FWK_7], padF4, 0.1f, 100.0f, 0.001f);
                Matrix_RotateY(gCalcMatrix, this->fwork[ZO_FWK_7] * M_DTOR, MTXF_NEW);

                spE4.x = spE4.y = 0.0f;
                spE4.z = 20.0f;

                Matrix_MultVec3fNoTranslate(gCalcMatrix, &spE4, &spCC);

                var_s0 = 0;
                this->vel.z = spCC.z - gPathVelZ;

                if (this->vel.x > 0.0f) {
                    var_s0 = 1;
                }

                if (var_s0 != this->swork[ZO_SWK_2]) {
                    this->swork[ZO_SWK_2] = var_s0;
                    this->fwork[ZO_FWK_8] = 0.0f;
                }

                Math_SmoothStepToF(&this->fwork[ZO_FWK_8], 10.0f, 0.01f, 0.1f, 0.0f);
                Math_SmoothStepToAngle(&this->obj.rot.z, D_i3_801BF6C4[var_s0], 0.1f, this->fwork[ZO_FWK_8], 0.00001f);
                Math_SmoothStepToAngle(&this->obj.rot.y, D_i3_801BF6D4[var_s0], 0.1f, this->fwork[ZO_FWK_8], 0.00001f);

                Matrix_RotateX(gCalcMatrix, -this->obj.rot.x * M_DTOR, MTXF_NEW);
                Matrix_RotateY(gCalcMatrix, -this->obj.rot.y * M_DTOR, MTXF_APPLY);

                spE4.x = gPlayer[0].pos.x - sZoFwork[ZO_BSF_93_X];
                spE4.y = gPlayer[0].pos.y - sZoFwork[ZO_BSF_93_Y];
                spE4.z = gPlayer[0].trueZpos - sZoFwork[ZO_BSF_93_Z];

                Matrix_MultVec3f(gCalcMatrix, &spE4, &spC0);

                sp10C = Math_Atan2F(spC0.x, spC0.z);
                sp10C = Math_RadToDeg(sp10C);

                sp110 = Math_Atan2F(spC0.y, sqrtf(SQ(spC0.x) + SQ(spC0.z)));
                sp110 = Math_RadToDeg(-sp110);

                if ((sp10C > 40.0f) && (sp10C < 180.0f)) {
                    sp10C = 40.0f;
                }
                if ((sp10C < 320.0f) && (sp10C > 180.0f)) {
                    sp10C = 320.0f;
                }
                if ((sp110 > 10.0f) && (sp110 < 180.0f)) {
                    sp110 = 10.0f;
                }
                if ((sp10C < 320.0f) && (sp10C > 180.0f)) {
                    sp110 = 320.0f;
                }

                spE4.x = gPlayer[0].pos.x - sZoFwork[ZO_BSF_96_X];
                spE4.y = gPlayer[0].pos.y - sZoFwork[ZO_BSF_96_Y];
                spE4.z = gPlayer[0].trueZpos - sZoFwork[ZO_BSF_96_Z];

                Matrix_MultVec3f(gCalcMatrix, &spE4, &spB4);

                sp104 = Math_Atan2F(spB4.x, spB4.z);
                sp104 = Math_RadToDeg(sp104);
                sp108 = Math_Atan2F(spB4.y, sqrtf(SQ(spB4.x) + SQ(spB4.z)));
                sp108 = Math_RadToDeg(-sp108);
                if ((sp104 > 40.0f) && (sp104 < 180.0f)) {
                    sp104 = 40.0f;
                }
                if ((sp104 < 320.0f) && (sp104 > 180.0f)) {
                    sp104 = 320.0f;
                }
                if ((sp108 > 10.0f) && (sp108 < 180.0f)) {
                    sp108 = 10.0f;
                }
                if ((sp104 < 320.0f) && (sp104 > 180.0f)) {
                    sp108 = 320.0f;
                }

                Math_SmoothStepToAngle(&sZoFwork[ZO_BSF_8], sp10C, 0.2f, 2.0f, 0.0f);
                Math_SmoothStepToAngle(&sZoFwork[ZO_BSF_7], sp110, 0.2f, 2.0f, 0.0f);
                Math_SmoothStepToAngle(&sZoFwork[ZO_BSF_10], sp104, 0.2f, 2.0f, 0.0f);
                Math_SmoothStepToAngle(&sZoFwork[ZO_BSF_9], sp108, 0.2f, 2.0f, 0.0f);

                Zoness_80198BE8(this, 0);
                Zoness_80198BE8(this, 1);
            }
            break;

        case 4:
            if (this->swork[ZO_SWK_15] == 0) {
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = gFillScreenAlpha = 0;
            }

            Math_SmoothStepToAngle(&this->obj.rot.z, this->fwork[ZO_FWK_9], 0.1f, 100.0f, 0.00001f);
            Math_SmoothStepToAngle(&this->fwork[ZO_FWK_9], 0.0f, 0.1f, 100.0f, 0.00001f);

            if ((sZoSwork[ZO_BSS_11] == 0) && (sZoLimbTimers[ZO_LIMB_7] != LIMB_DESTROYED)) {
                Zoness_80198F3C(this, 0, 46);
                if (sZoFwork[ZO_BSF_17] > -400.0f) {
                    sZoFwork[ZO_BSF_17] -= 10.0f;
                } else {
                    Audio_KillSfxBySource(this->sfxSource);
                    if (this->obj.rot.z > 359.0f) {
                        if (sZoSwork[ZO_BSS_13] != 0) {
                            Zoness_8019907C(this);
                        } else {
                            Zoness_8019914C(this, 0);
                        }
                    }
                }
            }
            if ((sZoSwork[ZO_BSS_12] == 0) && (sZoLimbTimers[ZO_LIMB_11] != LIMB_DESTROYED)) {
                Zoness_80198F3C(this, 1, 49);
                if (sZoFwork[ZO_BSF_18] > -400.0f) {
                    sZoFwork[ZO_BSF_18] -= 10.0f;
                } else {
                    Audio_KillSfxBySource(this->sfxSource);
                    if (this->obj.rot.z < 1.0f) {
                        if (sZoSwork[ZO_BSS_13] != 0) {
                            Zoness_8019907C(this);
                        } else {
                            Zoness_8019914C(this, 1);
                        }
                    }
                }
            }
            break;

        case 5:
            Math_SmoothStepToAngle(&this->obj.rot.z, this->fwork[ZO_FWK_9], 0.1f, 100.0f, 0.00001f);
            Math_SmoothStepToAngle(&this->fwork[ZO_FWK_9], 0.0f, 0.1f, 100.0f, 0.00001f);

            switch (sZoSwork[ZO_BSS_16]) {
                case 0:
                    if (sZoSwork[ZO_BSS_13] != 0) {
                        Zoness_8019962C(this, 180.0f);
                        if (this->obj.rot.y == 180.0f) {
                            if ((sZoSwork[ZO_BSS_11] == 0) && (sZoLimbTimers[ZO_LIMB_7] != LIMB_DESTROYED)) {
                                Zoness_801991D0(this, 0);
                            } else {
                                Zoness_801991D0(this, 1);
                            }
                        }
                    } else {
                        if (sZoSwork[ZO_BSS_36] == 0) {
                            sZoSwork[ZO_BSS_36]++;
                            sZoFwork[ZO_BSF_77] = 0.0f;
                        }
                        Zoness_8019962C(this, 0.0f);
                        if (this->obj.rot.y == 0.0f) {
                            if (sZoSwork[ZO_BSS_11] == 0) {
                                Zoness_8019914C(this, 0);
                            }
                            if (sZoSwork[ZO_BSS_12] == 0) {
                                Zoness_8019914C(this, 1);
                            }
                        }
                    }
                    break;

                case 1:
                    Zoness_80199470(this, 0);
                    break;

                case 2:
                    Zoness_80199470(this, 1);
                    break;

                case 3:
                    if (sZoSwork[ZO_BSS_13] != 0) {
                        if (this->timer_050 == 0) {
                            Math_SmoothStepToF(&sZoFwork[ZO_BSF_4], 0.0f, 1.0f, 5.0f, 0.001f);
                            Math_SmoothStepToF(&sZoFwork[ZO_BSF_3], 0.0f, 1.0f, 3.0f, 0.001f);
                            if (sZoFwork[ZO_BSF_3] == 0.0f) {
                                Zoness_8019962C(this, 0.0f);
                                if (this->obj.rot.y == 0.0f) {
                                    sZoSwork[ZO_BSS_16] = 0;
                                    this->swork[ZO_SWK_4] = 1000;
                                    this->state = 3;
                                }
                            }
                        }
                    } else {
                        if (sZoSwork[ZO_BSS_36] == 0) {
                            sZoSwork[ZO_BSS_36]++;
                            sZoFwork[ZO_BSF_77] = 0.0f;
                        }
                        Zoness_8019962C(this, 0.0f);
                        if (this->obj.rot.y == 0.0f) {
                            sZoSwork[ZO_BSS_16] = 0;
                            sZoSwork[ZO_BSS_36] = 0;
                            sZoFwork[ZO_BSF_77] = 0.0f;
                            this->swork[ZO_SWK_4] = 1000;
                            this->state = 3;
                        }
                    }
                    break;
            }
            break;

        case 6:
            D_ctx_801779A8[0] = 20;
            if (gCameraShake == 0) {
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
                gFillScreenAlpha = gFillScreenAlphaTarget = 255;
                gFillScreenAlphaTarget = 0;
                gFillScreenAlphaStep = 25;
                gCameraShake = (s32) (RAND_FLOAT(20.0f) + 20.0f);
            }
            if (gCameraShake == 29) {
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = gFillScreenAlpha = 0;
            }

            if ((gGameFrameCount % 4U) == 0) {
                spE4.x = RAND_FLOAT_CENTERED(300.0f) + this->obj.pos.x;
                spE4.y = RAND_FLOAT_CENTERED(200.0f) + (this->obj.pos.y + 600.0f);
                spE4.z = this->obj.pos.z - 50.0f;
                spD8.x = this->obj.rot.x;
                spD8.y = Math_ModF(RAND_FLOAT_CENTERED(60.0f) + 360.0f, 360.0f);
                spD8.z = this->obj.rot.z;
                for (i = 0; i < 5; i++) {
                    Zoness_ActorDebris_Spawn(&spE4, &spD8, RAND_FLOAT_CENTERED(30.0f), RAND_FLOAT_CENTERED(20.0f),
                                             RAND_FLOAT_CENTERED(30.0f), 4, 1.0f,
                                             RAND_FLOAT(15.0f) + (this->scale * 10.0f), 0);
                }
            }

            this->vel.x = 0.0f;
            Math_SmoothStepToF(&this->obj.pos.x, 0.0f, 0.1f, 5.0f, 0.00001f);

            if (((gGameFrameCount % 8) == 0) && (Rand_ZeroOne() < 0.5f)) {
                sZoLimbTimers[ZO_LIMB_36] = 15;
                sZoLimbTimers[ZO_LIMB_25] = 15;
            }

            Effect_Effect390_Spawn(sZoFwork[ZO_BSF_55_X], sZoFwork[ZO_BSF_55_Y], sZoFwork[ZO_BSF_55_Z], this->vel.x,
                                   this->vel.y, this->vel.z, 0.2f, 10);
            func_effect_8007D0E0(sZoFwork[ZO_BSF_55_X] + RAND_FLOAT_CENTERED(200.0f),
                                 sZoFwork[ZO_BSF_55_Y] + RAND_RANGE(-160.0f, 640.0f), sZoFwork[ZO_BSF_55_Z], 10.0f);

            if (this->timer_050 == 30) {
                Radio_PlayMessage(gMsg_ID_6079, RCID_BOSS_ZONESS);
            }
            if (this->timer_050 == 0) {
                gEffects[99].obj.status = gEffects[98].obj.status = OBJ_FREE;
                sZoFwork[ZO_BSF_25] = -1000.0f;
                sZoFwork[ZO_BSF_23] = 10.0f;
                gShowBossHealth = false;
                Effect_Effect383_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 80.0f);
                if ((gPlayer[0].state == PLAYERSTATE_ACTIVE) || (gPlayer[0].state == PLAYERSTATE_U_TURN)) {
                    gCsFrameCount = 0;
                    gPlayer[0].state = PLAYERSTATE_LEVEL_COMPLETE;
                    gPlayer[0].csState = gPlayer[0].csTimer = 0;
                    gPlayer[0].rot.y += gPlayer[0].yRot_114;
                    if (gPlayer[0].rot.y > 360.0f) {
                        gPlayer[0].rot.y -= 360.0f;
                    }
                    if (gPlayer[0].rot.y < 0.0f) {
                        gPlayer[0].rot.y += 360.0f;
                    }
                    gPlayer[0].yRot_114 = 0.0f;
                    Boss_CompleteLevel(&gPlayer[0], this->obj.pos.x, 0.0f, this->obj.pos.z);
                }
                this->timer_050 = 70;
                sZoSwork[ZO_BSS_5] = 0;
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = gFillScreenAlpha = 0;
                Boss_AwardBonus(this);
                this->state = 7;
            }
            break;

        case 7:
            D_ctx_801779A8[0] = 20;
            if (((gGameFrameCount % 8) == 0) &&
                (Play_CheckDynaFloorCollision(&sp134, &sp130, this->obj.pos.x, -300.0f, this->obj.pos.z) != 0)) {
                Effect_Effect391_Spawn(RAND_FLOAT_CENTERED(500.0f) + this->obj.pos.x, sp134 - 300.0f,
                                       RAND_FLOAT_CENTERED(3000.0f) + this->obj.pos.z, 5.0f, 2.0f);
            }
            if ((this->timer_050 == 0) || (this->obj.pos.y < -800.0f)) {
                Object_Kill(&this->obj, this->sfxSource);
            }
            break;

        case 8:
            if (sZoSwork[ZO_BSS_18] != 0) {
                if ((sZoSwork[ZO_BSS_27] != 2) && (this->swork[ZO_SWK_5] == 0) && (this->swork[ZO_SWK_6] < 2) &&
                    ((sZoSwork[ZO_BSS_33] == 0) || (sZoSwork[ZO_BSS_33] >= 30))) {
                    sZoSwork[ZO_BSS_18]--;
                }

                Zoness_8019962C(this, 0.0f);

                Math_SmoothStepToF(&sZoFwork[ZO_BSF_1], -130.0f, 0.1f, 2.0f, 0.00001f);
                Math_SmoothStepToF(&sZoFwork[ZO_BSF_11], 130.0f, 0.1f, 2.0f, 0.00001f);

                if (sZoSwork[ZO_BSS_18] < 331) {
                    if (sZoSwork[ZO_BSS_8] != 0) {
                        if ((sZoSwork[ZO_BSS_20] == 0) && (this->swork[ZO_SWK_6] == 1)) {
                            sZoSwork[ZO_BSS_20] = 1;
                            sZoSwork[ZO_BSS_27]++;
                            if (sZoSwork[ZO_BSS_27] >= 3) {
                                sZoSwork[ZO_BSS_27] = 3;
                            }
                        }
                    } else if ((this->swork[ZO_SWK_5] == 0) && (this->swork[ZO_SWK_6] < 2)) {
                        if (sZoSwork[ZO_BSS_33] == 0) {
                            Radio_PlayMessage(gMsg_ID_6077, RCID_BOSS_ZONESS);
                            sZoSwork[ZO_BSS_27] = 3;
                        }
                        sZoSwork[ZO_BSS_33]++;
                        if (sZoSwork[ZO_BSS_33] > 30) {
                            sZoSwork[ZO_BSS_33] = 30;
                            if (sZoSwork[ZO_BSS_20] == 0) {
                                sZoSwork[ZO_BSS_20] = 1;
                            }
                        }
                    }
                }
                if ((sZoSwork[ZO_BSS_27] == 0) && (sZoSwork[ZO_BSS_18] == 400) && (sZoSwork[ZO_BSS_8] != 0)) {
                    Radio_PlayMessage(gMsg_ID_6074, RCID_BOSS_ZONESS);
                    sZoSwork[ZO_BSS_27] = 1;
                    this->swork[ZO_SWK_6] = 30;
                }
                if ((sZoSwork[ZO_BSS_26] == 0) && (sZoSwork[ZO_BSS_18] == 200) && (sZoSwork[ZO_BSS_27] == 3)) {
                    Radio_PlayMessage(gMsg_ID_6075, RCID_BOSS_ZONESS);
                    sZoSwork[ZO_BSS_26]++;
                    this->timer_050 = 100;
                }
                if ((this->timer_050 == 0) && (sZoSwork[ZO_BSS_26] != 0)) {
                    this->timer_050 = 50;
                    sZoFwork[ZO_BSF_37_X] = RAND_RANGE(-330.0f, 770.0f);
                    sZoFwork[ZO_BSF_40_X] = RAND_RANGE(-560.0f, 240.0f);
                    Zoness_801989FC(this);
                }
            } else {
                if (sZoSwork[ZO_BSS_28] == 0) {
                    Radio_PlayMessage(gMsg_ID_6073, RCID_BOSS_ZONESS);
                    sZoSwork[ZO_BSS_28]++;
                }
                sZoFwork[ZO_BSF_25] = 0.0f;
                sZoFwork[ZO_BSF_23] = 3.0f;
                this->timer_054 = 0;
                sZoSwork[ZO_BSS_5] = 0;
                sZoFwork[ZO_BSF_28] = -2600.0f;
                sZoFwork[ZO_BSF_15] = sZoFwork[ZO_BSF_16] = 0.0f;
                sZoSwork[ZO_BSS_18] = 0;

                for (i = 0; i < 2; i++) {
                    Zoness_80199394(this, i);
                }
                this->timer_050 = 100;
                this->state = 0;
            }
            break;
    }
    sZoFwork[ZO_BSF_2] += 20.0f;

    spE4.x = gPlayer[0].pos.x - this->obj.pos.x;
    spE4.z = gPlayer[0].trueZpos - this->obj.pos.z;

    Math_SmoothStepToAngle(&sZoFwork[ZO_BSF_14], Math_RadToDeg(Math_Atan2F(spE4.x, spE4.z)), 0.5f, 100.0f, 0.001f);
    Math_SmoothStepToAngle(&sZoFwork[ZO_BSF_0], sZoFwork[ZO_BSF_76], 0.2f, 4.0f, 0.0001f);

    if ((((gGameFrameCount % 64) == 0) || (sZoSwork[ZO_BSS_22] != 0)) &&
        ((Rand_ZeroOne() < 0.5f) || (sZoSwork[ZO_BSS_22] != 0)) && (sZoSwork[ZO_BSS_23] == 0)) {
        sZoSwork[ZO_BSS_23] = D_i3_801BF5F0[sZoSwork[ZO_BSS_22]];
        sZoFwork[ZO_BSF_76] = D_i3_801BF608[sZoSwork[ZO_BSS_22]];
        if ((sZoSwork[ZO_BSS_22] == 0) && (Rand_ZeroOne() < 0.3f)) {
            sZoSwork[ZO_BSS_23] = 100;
        }
        sZoSwork[ZO_BSS_22]++;
        if (sZoSwork[ZO_BSS_22] >= 6) {
            sZoSwork[ZO_BSS_22] = 0;
        }
    }
    spE4.x = gPlayer[0].pos.x - sZoFwork[ZO_BSF_65_X];
    spE4.z = gPlayer[0].trueZpos - sZoFwork[ZO_BSF_65_Z];
    Math_SmoothStepToAngle(&sZoFwork[ZO_BSF_19], Math_RadToDeg(Math_Atan2F(spE4.x, spE4.z)), 0.1f, 5.0f, 0.0f);

    if ((this->state >= 3) && (this->state < 6)) {
        Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
        Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);

        Matrix_MultVec3f(gCalcMatrix, &spA8, &spD8);
        Matrix_MultVec3f(gCalcMatrix, &sp9C, &spCC);

        sp78 = spD8;
        sp6C = spCC;

        Matrix_RotateX(gCalcMatrix, -this->obj.rot.x * M_DTOR, MTXF_NEW);
        Matrix_RotateY(gCalcMatrix, -this->obj.rot.y * M_DTOR, MTXF_APPLY);

        spE4.x = gPlayer[0].pos.x - (this->obj.pos.x + spD8.x);
        spE4.y = gPlayer[0].pos.y - (this->obj.pos.y + spD8.y);
        spE4.z = gPlayer[0].trueZpos - (this->obj.pos.z + spD8.z);

        Matrix_MultVec3f(gCalcMatrix, &spE4, &spD8);

        sp11C = Math_Atan2F(spD8.x, spD8.z);
        sp11C = Math_RadToDeg(sp11C);

        sp120 = Math_Atan2F(spD8.y, sqrtf(SQ(spD8.x) + SQ(spD8.z)));
        sp120 = Math_RadToDeg(-sp120);

        spE4.x = gPlayer[0].pos.x - (this->obj.pos.x + spCC.x);
        spE4.y = gPlayer[0].pos.y - (this->obj.pos.y + spCC.y);
        spE4.z = gPlayer[0].trueZpos - (this->obj.pos.z + spCC.z);

        Matrix_MultVec3f(gCalcMatrix, &spE4, &spCC);

        sp114 = Math_Atan2F(spCC.x, spCC.z);
        sp114 = Math_RadToDeg(sp114);

        sp118 = Math_Atan2F(spCC.y, sqrtf(SQ(spCC.x) + SQ(spCC.z)));
        sp118 = Math_RadToDeg(-sp118);

        Math_SmoothStepToAngle(&sZoFwork[ZO_BSF_15], sp11C, 0.2f, 2.0f, 0.0f);
        Math_SmoothStepToAngle(&sZoFwork[ZO_BSF_5], sp120, 0.2f, 2.0f, 0.0f);
        Math_SmoothStepToAngle(&sZoFwork[ZO_BSF_16], sp114, 0.2f, 2.0f, 0.0f);
        Math_SmoothStepToAngle(&sZoFwork[ZO_BSF_12], sp118, 0.2f, 2.0f, 0.0f);

        if ((this->obj.rot.y >= 330.0f) || (this->obj.rot.y <= 30.0f) ||
            ((this->obj.rot.y <= 200.0f) && (this->obj.rot.y >= 160.0f))) {
            if ((sZoFwork[ZO_BSF_15] > 315.0f) || (sZoFwork[ZO_BSF_15] < 215.0f)) {
                Zoness_801986FC(this, 0, sp78.x, sp78.y, sp78.z, sZoFwork[ZO_BSF_5]);
            }
            if ((sZoFwork[ZO_BSF_16] < 45.0f) || (sZoFwork[ZO_BSF_16] > 145.0f)) {
                Zoness_801986FC(this, 1, sp6C.x, sp6C.y, sp6C.z, sZoFwork[ZO_BSF_12]);
            }
            Math_SmoothStepToF(&sZoFwork[ZO_BSF_35], 0.0f, 1.0f, 2.0f, 0.00001f);
            Math_SmoothStepToF(&sZoFwork[ZO_BSF_36], 0.0f, 1.0f, 2.0f, 0.00001f);
            Math_SmoothStepToF(&sZoFwork[ZO_BSF_6], sZoFwork[ZO_BSF_35], 0.4f, 100.0f, 0.00001f);
            Math_SmoothStepToF(&sZoFwork[ZO_BSF_13], sZoFwork[ZO_BSF_36], 0.4f, 100.0f, 0.00001f);
        }
    }

    if ((sZoSwork[ZO_BSS_8] == 0) && (sZoLimbTimers[ZO_LIMB_15] != LIMB_DESTROYED)) {
        if ((sZoFwork[ZO_BSF_87] < -570.0f) || (sZoFwork[ZO_BSF_88] > 1600.0f)) {
            sZoLimbTimers[ZO_LIMB_1] = sZoLimbTimers[ZO_LIMB_14] = sZoLimbTimers[ZO_LIMB_15] = LIMB_DESTROYED;
            sZoFwork[ZO_BSF_88] = 100000.0f;
        } else {
            sZoFwork[ZO_BSF_86] += 5.0f;
            sZoFwork[ZO_BSF_87] -= 10.0f;
            sZoFwork[ZO_BSF_88] += 20.0f;
            func_effect_8007D0E0(sZoFwork[ZO_BSF_43_X], sZoFwork[ZO_BSF_43_Y], sZoFwork[ZO_BSF_43_Z], 5.0f);
            if ((Play_CheckDynaFloorCollision(&sp134, &sp130, sZoFwork[ZO_BSF_43_X], sZoFwork[ZO_BSF_43_Y] - 100.0f,
                                              sZoFwork[ZO_BSF_43_Z]) != 0) &&
                (sZoSwork[ZO_BSS_45] == 0)) {
                if (gPlayer) {}
                Effect_Effect391_Spawn(sZoFwork[ZO_BSF_43_X], sp134, sZoFwork[ZO_BSF_43_Z] + 30.0f, 0.0f, 2.0f);
                sZoSwork[ZO_BSS_45]++;
            }
        }
    }

    if ((sZoSwork[ZO_BSS_9] == 0) && (sZoLimbTimers[ZO_LIMB_10] != LIMB_DESTROYED)) {
        if ((sZoFwork[ZO_BSF_81] > 700.0f) || (sZoFwork[ZO_BSF_82] < -400.0f)) {
            sZoLimbTimers[ZO_LIMB_10] = LIMB_DESTROYED;
            ZO_HIT_3(this)->b.z.offset = 100000.0f;
        } else {
            sZoFwork[ZO_BSF_80] -= 5.0f;
            sZoFwork[ZO_BSF_81] += 12.0f;
            sZoFwork[ZO_BSF_82] -= 10.0f;

            func_effect_8007D0E0(sZoFwork[ZO_BSF_29_X], sZoFwork[ZO_BSF_29_Y], sZoFwork[ZO_BSF_29_Z], 5.0f);
            if ((Play_CheckDynaFloorCollision(&sp134, &sp130, sZoFwork[ZO_BSF_29_X], sZoFwork[ZO_BSF_29_Y] - 100.0f,
                                              sZoFwork[ZO_BSF_29_Z]) != 0) &&
                (sZoSwork[ZO_BSS_46] == 0)) {
                Effect_Effect391_Spawn(sZoFwork[ZO_BSF_29_X], sp134, sZoFwork[ZO_BSF_29_Z] + 30.0f, 0.0f, 2.0f);
                sZoSwork[ZO_BSS_46]++;
            }
        }
    }

    if ((sZoSwork[ZO_BSS_10] == 0) && (sZoLimbTimers[ZO_LIMB_2] != LIMB_DESTROYED)) {
        if ((sZoFwork[ZO_BSF_84] > 700.0f) || (sZoFwork[ZO_BSF_85] < -400.0f)) {
            sZoLimbTimers[ZO_LIMB_2] = LIMB_DESTROYED;
            ZO_HIT_4(this)->b.z.offset = 100000.0f;
        } else {
            sZoFwork[ZO_BSF_83] -= 5.0f;
            sZoFwork[ZO_BSF_84] += 12.0f;
            sZoFwork[ZO_BSF_85] -= 10.0f;
            func_effect_8007D0E0(sZoFwork[ZO_BSF_32_X], sZoFwork[ZO_BSF_32_Y], sZoFwork[ZO_BSF_32_Z], 5.0f);
            if ((Play_CheckDynaFloorCollision(&sp134, &sp130, sZoFwork[ZO_BSF_32_X], sZoFwork[ZO_BSF_32_Y] - 100.0f,
                                              sZoFwork[ZO_BSF_32_Z]) != 0) &&
                (sZoSwork[ZO_BSS_47] == 0)) {
                Effect_Effect391_Spawn(sZoFwork[ZO_BSF_32_X], sp134, sZoFwork[ZO_BSF_32_Z] + 30.0f, 0.0f, 2.0f);
                sZoSwork[ZO_BSS_47]++;
            }
        }
    }

    if ((sZoSwork[ZO_BSS_13] < 2) && (sZoLimbTimers[ZO_LIMB_5] != LIMB_DESTROYED)) {
        D_ctx_801779A8[0] = 20;
        if ((gGameFrameCount % 2) == 0) {
            func_effect_8007D0E0(sZoFwork[ZO_BSF_52_X] + RAND_FLOAT_CENTERED(200.0f),
                                 sZoFwork[ZO_BSF_52_Y] + RAND_FLOAT_CENTERED(200.0f),
                                 sZoFwork[ZO_BSF_52_Z] + RAND_FLOAT_CENTERED(100.0f), 5.0f);
        }

        if (this->swork[ZO_SWK_14] != 0) {
            if (sZoLimbTimers[ZO_LIMB_5] == 0) {
                sZoLimbTimers[ZO_LIMB_5] = sZoLimbTimers[ZO_LIMB_6] = 15;
            }
            if (sZoSwork[ZO_BSS_52] == 0) {
                sZoSwork[ZO_BSS_52] = 30;
            }
        } else {
            sZoSwork[ZO_BSS_13] = 0;
            if ((sZoFwork[ZO_BSF_92] < -700.0f) || (sZoFwork[ZO_BSF_91] < -400.0f)) {
                sZoLimbTimers[ZO_LIMB_5] = sZoLimbTimers[ZO_LIMB_6] = LIMB_DESTROYED;
                sZoFwork[ZO_BSF_52_Z] = 100000.0f;
            } else {
                sZoFwork[ZO_BSF_90] -= 2.0f;
                sZoFwork[ZO_BSF_91] -= 5.0f;
                sZoFwork[ZO_BSF_92] -= 5.0f;
                func_effect_8007D0E0(sZoFwork[ZO_BSF_52_X], sZoFwork[ZO_BSF_52_Y], sZoFwork[ZO_BSF_52_Z], 5.0f);
                if ((Play_CheckDynaFloorCollision(&sp134, &sp130, sZoFwork[ZO_BSF_52_X], sZoFwork[ZO_BSF_52_Y] - 100.0f,
                                                  sZoFwork[ZO_BSF_52_Z]) != 0) &&
                    (sZoSwork[ZO_BSS_48] == 0)) {
                    Effect_Effect391_Spawn(sZoFwork[ZO_BSF_52_X], sp134, sZoFwork[ZO_BSF_52_Z] + 100.0f, 0.0f, 2.0f);
                    sZoSwork[ZO_BSS_48]++;
                }
            }
        }
    }

    if (this->dmgType != DMG_NONE) {
        dmgType = this->dmgType;
        this->dmgType = DMG_NONE;
        if (dmgType == DMG_BEAM) {
            AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
        }

        switch (this->dmgPart) {
            case 0:
                if ((sZoSwork[ZO_BSS_8] != 0) && (dmgType == DMG_BOMB) && ((this->state == 3) || (this->state == 8))) {
                    sZoLimbTimers[ZO_LIMB_1] = sZoLimbTimers[ZO_LIMB_14] = sZoLimbTimers[ZO_LIMB_15] = 15;
                    sZoSwork[ZO_BSS_49] = 60;
                    sZoSwork[ZO_BSS_8] -= this->damage;
                    if (sZoSwork[ZO_BSS_8] <= 0) {
                        sZoSwork[ZO_BSS_49] = sZoSwork[ZO_BSS_8] = 0;
                        this->swork[ZO_SWK_5] = 30;
                    }
                }
                break;

            case 3:
                if ((sZoSwork[ZO_BSS_9] != 0) && (this->state == 3) && (dmgType == DMG_BOMB) &&
                    (sZoSwork[ZO_BSS_50] == 0)) {
                    sZoLimbTimers[ZO_LIMB_10] = 15;
                    sZoSwork[ZO_BSS_50] = 50;
                    sZoSwork[ZO_BSS_9] -= this->damage;
                    if (sZoSwork[ZO_BSS_9] <= 0) {
                        sZoSwork[ZO_BSS_50] = sZoSwork[ZO_BSS_9] = 0;
                        spD8.x = sZoFwork[ZO_BSF_29_X];
                        spD8.y = sZoFwork[ZO_BSF_29_Y];
                        spD8.z = sZoFwork[ZO_BSF_29_Z];
                        Effect_SpawnTimedSfxAtPos(&spD8, NA_SE_EN_EXPLOSION_S);
                    }
                }
                break;

            case 4:
                if ((sZoSwork[ZO_BSS_10] != 0) && (this->state == 3) && (dmgType == DMG_BOMB) &&
                    (sZoSwork[ZO_BSS_51] == 0)) {
                    sZoLimbTimers[ZO_LIMB_2] = 15;
                    sZoSwork[ZO_BSS_51] = 50;
                    sZoSwork[ZO_BSS_10] -= this->damage;
                    if (sZoSwork[ZO_BSS_10] <= 0) {
                        sZoSwork[ZO_BSS_51] = sZoSwork[ZO_BSS_10] = 0;
                        spD8.x = sZoFwork[ZO_BSF_32_X];
                        spD8.y = sZoFwork[ZO_BSF_32_Y];
                        spD8.z = sZoFwork[ZO_BSF_32_Z];
                        Effect_SpawnTimedSfxAtPos(&spD8, NA_SE_EN_EXPLOSION_S);
                    }
                }
                break;

            case 5:
                if ((sZoSwork[ZO_BSS_9] != 0) && (this->state == 3) && (dmgType == DMG_BOMB) &&
                    (sZoSwork[ZO_BSS_50] == 0)) {
                    sZoLimbTimers[ZO_LIMB_10] = 15;
                    sZoSwork[ZO_BSS_50] = 50;

                    sZoSwork[ZO_BSS_9] -= this->damage;
                    if (sZoSwork[ZO_BSS_9] <= 0) {
                        sZoSwork[ZO_BSS_50] = sZoSwork[ZO_BSS_9] = 0;
                        spD8.x = sZoFwork[ZO_BSF_29_X];
                        spD8.y = sZoFwork[ZO_BSF_29_Y];
                        spD8.z = sZoFwork[ZO_BSF_29_Z];
                        Effect_SpawnTimedSfxAtPos(&spD8, NA_SE_EN_EXPLOSION_S);
                    }
                }

                if ((sZoSwork[ZO_BSS_10] != 0) && (this->state == 3) && (dmgType == DMG_BOMB) &&
                    (sZoSwork[ZO_BSS_51] == 0)) {
                    sZoLimbTimers[ZO_LIMB_2] = 15;
                    sZoSwork[ZO_BSS_51] = 50;
                    sZoSwork[ZO_BSS_10] -= this->damage;
                    if (sZoSwork[ZO_BSS_10] <= 0) {
                        sZoSwork[ZO_BSS_51] = sZoSwork[ZO_BSS_10] = 0;
                        spD8.x = sZoFwork[ZO_BSF_32_X];
                        spD8.y = sZoFwork[ZO_BSF_32_Y];
                        spD8.z = sZoFwork[ZO_BSF_32_Z];
                        Effect_SpawnTimedSfxAtPos(&spD8, NA_SE_EN_EXPLOSION_S);
                    }
                }
                /* fallthrough */
            case 6:
                if ((this->health != 0) && (sZoSwork[ZO_BSS_9] == 0) && (sZoSwork[ZO_BSS_10] == 0) &&
                    (sZoSwork[ZO_BSS_11] == 0) && (sZoSwork[ZO_BSS_12] == 0) && (sZoSwork[ZO_BSS_13] == 0) &&
                    (this->state == 3)) {
                    sZoLimbTimers[ZO_LIMB_25] = sZoLimbTimers[ZO_LIMB_36] = 15;

                    this->health -= this->damage;
                    if (this->health < 150) {
                        AUDIO_PLAY_SFX(NA_SE_EN_KNOCK_DOWN, this->sfxSource, 4);
                    } else {
                        AUDIO_PLAY_SFX(NA_SE_OB_DAMAGE_M, this->sfxSource, 4);
                    }
                    if (this->health <= 0) {
                        gTeamLowHealthMsgTimer = -1;
                        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 40);
                        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 40);
                        Audio_KillSfxBySource(this->sfxSource);
                        AUDIO_PLAY_SFX(NA_SE_EN_DOWN_IMPACT, this->sfxSource, 4);
                        sZoSwork[ZO_BSS_8] = this->health = sZoSwork[ZO_BSS_24] = 0;
                        this->timer_050 = 100;
                        AUDIO_PLAY_SFX(NA_SE_EN_DOWN_IMPACT, this->sfxSource, 4);
                        sZoFwork[ZO_BSF_27] = 20.0f;
                        sZoFwork[ZO_BSF_26] = 50.0f;
                        sZoFwork[ZO_BSF_28] = -2600.0f;
                        this->state = 6;
                        this->fwork[ZO_FWK_4] = 1.0f;
                    }
                }
                break;

            case 7:
            case 12:
                if ((sZoSwork[ZO_BSS_13] >= 2) && (this->state == 5) && (dmgType == DMG_BOMB)) {
                    sZoLimbTimers[ZO_LIMB_5] = sZoLimbTimers[ZO_LIMB_6] = 15;
                    sZoSwork[ZO_BSS_52] = 30;

                    sZoSwork[ZO_BSS_13] -= this->damage;
                    if (sZoSwork[ZO_BSS_13] < 2) {
                        this->swork[ZO_SWK_14] = 30;
                        sZoSwork[ZO_BSS_13] = 1;
                        Radio_PlayMessage(gMsg_ID_6090, RCID_BOSS_ZONESS);
                        spD8.x = sZoFwork[ZO_BSF_52_X];
                        spD8.y = sZoFwork[ZO_BSF_52_Y];
                        spD8.z = sZoFwork[ZO_BSF_52_Z];
                        Effect_SpawnTimedSfxAtPos(&spD8, NA_SE_EN_SINK_PARTS);
                    }
                }
                break;

            case 8 + 0:
            case 10 + 0:
                if ((sZoSwork[ZO_BSS_11] != 0) && (this->state == 3) && (dmgType == DMG_BOMB) &&
                    (sZoSwork[ZO_BSS_53] == 0)) {
                    sZoLimbTimers[ZO_LIMB_7] = sZoLimbTimers[ZO_LIMB_21] = sZoLimbTimers[ZO_LIMB_22] = 15;
                    sZoSwork[ZO_BSS_53] = 50;

                    sZoSwork[ZO_BSS_11] -= this->damage;
                    if (sZoSwork[ZO_BSS_11] <= 0) {
                        sZoSwork[ZO_BSS_11] = 0;
                        gCameraShake = 30;

                        gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
                        gFillScreenAlpha = gFillScreenAlphaTarget = 255;
                        gFillScreenAlphaTarget = 0;
                        gFillScreenAlphaStep = 25;

                        this->swork[ZO_SWK_15] = 3;

                        spD8.x = sZoFwork[ZO_BSF_106_X];
                        spD8.y = sZoFwork[ZO_BSF_106_Y];
                        spD8.z = sZoFwork[ZO_BSF_106_Z];

                        Effect_SpawnTimedSfxAtPos(&spD8, NA_SE_EN_SINK_PARTS);

                        sZoSwork[ZO_BSS_16] = 0;
                        ZO_HIT_8(this, 0)->z.offset = ZO_HIT_10(this, 0)->z.offset = 100000.0f;
                        this->state = 4;
                        this->fwork[ZO_FWK_9] = 330.0f;
                    }
                }
                break;

            case 8 + 1:
            case 10 + 1:
                if ((sZoSwork[ZO_BSS_12] != 0) && (this->state == 3) && (dmgType == DMG_BOMB) &&
                    (sZoSwork[ZO_BSS_54] == 0)) {
                    sZoLimbTimers[ZO_LIMB_11] = sZoLimbTimers[ZO_LIMB_23] = sZoLimbTimers[ZO_LIMB_24] = 15;
                    sZoSwork[ZO_BSS_54] = 50;

                    sZoSwork[ZO_BSS_12] -= this->damage;
                    if (sZoSwork[ZO_BSS_12] <= 0) {
                        sZoSwork[ZO_BSS_12] = 0;
                        gCameraShake = 30;

                        gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
                        gFillScreenAlpha = gFillScreenAlphaTarget = 255;
                        gFillScreenAlphaTarget = 0;
                        gFillScreenAlphaStep = 25;

                        this->swork[ZO_SWK_15] = 3;

                        spCC.x = sZoFwork[ZO_BSF_109_X];
                        spCC.y = sZoFwork[ZO_BSF_109_Y];
                        spCC.z = sZoFwork[ZO_BSF_109_Z];

                        Effect_SpawnTimedSfxAtPos(&spCC, NA_SE_EN_SINK_PARTS);

                        sZoSwork[ZO_BSS_16] = 0;
                        ZO_HIT_8(this, 1)->z.offset = ZO_HIT_10(this, 1)->z.offset = 100000.0f;
                        this->state = 4;
                        this->fwork[ZO_FWK_9] = 30.0f;
                    }
                }
                break;
        }
    }

    if (sZoSwork[ZO_BSS_0] != 0) {
        sZoSwork[ZO_BSS_0]--;
    }
    if (sZoSwork[ZO_BSS_1] != 0) {
        sZoSwork[ZO_BSS_1]--;
    }
    if (sZoSwork[ZO_BSS_2] != 0) {
        sZoSwork[ZO_BSS_2]--;
    }
    if (sZoSwork[ZO_BSS_3] != 0) {
        sZoSwork[ZO_BSS_3]--;
    }
    if (sZoSwork[ZO_BSS_4] != 0) {
        sZoSwork[ZO_BSS_4]--;
    }
    if (sZoSwork[ZO_BSS_23] != 0) {
        sZoSwork[ZO_BSS_23]--;
    }
    if (sZoSwork[ZO_BSS_34] != 0) {
        sZoSwork[ZO_BSS_34]--;
    }
    if (sZoSwork[ZO_BSS_38] != 0) {
        sZoSwork[ZO_BSS_38]--;
    }
    if (sZoSwork[ZO_BSS_39] != 0) {
        sZoSwork[ZO_BSS_39]--;
    }
    if (sZoSwork[ZO_BSS_40] != 0) {
        sZoSwork[ZO_BSS_40]--;
    }
    if (this->swork[ZO_SWK_14] != 0) {
        this->swork[ZO_SWK_14]--;
    }
    if (this->swork[ZO_SWK_4] != 0) {
        this->swork[ZO_SWK_4]--;
    }
    if (this->swork[ZO_SWK_5] != 0) {
        this->swork[ZO_SWK_5]--;
    }
    if (this->swork[ZO_SWK_15] != 0) {
        this->swork[ZO_SWK_15]--;
    }
    if (this->swork[ZO_SWK_6] > 1) {
        this->swork[ZO_SWK_6]--;
    }

    for (sp124 = 0; sp124 < ZO_LIMB_MAX; sp124++) {
        if ((sZoLimbTimers[sp124] > 0) && (sZoLimbTimers[sp124] < 200)) {
            sZoLimbTimers[sp124]--;
        }
    }
    for (i = ZO_BSS_49, sp124 = 0; sp124 < 6; sp124++, i++) {
        if (sZoSwork[i] != 0) {
            sZoSwork[i]--;
        }
    }

    if (this->state < 4) {
        spD8.x = sZoFwork[ZO_BSF_106_X];
        spD8.y = sZoFwork[ZO_BSF_106_Y];
        spD8.z = sZoFwork[ZO_BSF_106_Z];
        spCC.x = sZoFwork[ZO_BSF_109_X];
        spCC.y = sZoFwork[ZO_BSF_109_Y];
        spCC.z = sZoFwork[ZO_BSF_109_Z];
        if (((sZoSwork[ZO_BSS_53] % 2) != 0) && (sZoSwork[ZO_BSS_11] != 0)) {
            Effect_SpawnTimedSfxAtPos(&spD8, NA_SE_OB_DAMAGE_M);
        }
        if (((sZoSwork[ZO_BSS_54] % 2) != 0) && (sZoSwork[ZO_BSS_12] != 0)) {
            Effect_SpawnTimedSfxAtPos(&spCC, NA_SE_OB_DAMAGE_M);
        }
    }

    if ((sZoSwork[ZO_BSS_50] % 2) != 0) {
        spD8.x = sZoFwork[ZO_BSF_29_X];
        spD8.y = sZoFwork[ZO_BSF_29_Y];
        spD8.z = sZoFwork[ZO_BSF_29_Z];
        Effect_SpawnTimedSfxAtPos(&spD8, NA_SE_EN_DAMAGE_S);
    }
    if ((sZoSwork[ZO_BSS_51] % 2) != 0) {
        spD8.x = sZoFwork[ZO_BSF_32_X];
        spD8.y = sZoFwork[ZO_BSF_32_Y];
        spD8.z = sZoFwork[ZO_BSF_32_Z];
        Effect_SpawnTimedSfxAtPos(&spD8, NA_SE_EN_DAMAGE_S);
    }
    if ((sZoSwork[ZO_BSS_52] % 2) != 0) {
        spD8.x = sZoFwork[ZO_BSF_52_X];
        spD8.y = sZoFwork[ZO_BSF_52_Y];
        spD8.z = sZoFwork[ZO_BSF_52_Z];
        Effect_SpawnTimedSfxAtPos(&spD8, NA_SE_OB_DAMAGE_M);
    }

    if (Play_CheckDynaFloorCollision(&sp134, &sp130, this->obj.pos.x, this->obj.pos.y - 500.0f, this->obj.pos.z) != 0) {
        Math_SmoothStepToF(&this->obj.pos.y, sp134 - 20.0f, 0.1f, this->fwork[ZO_FWK_4], 0.0f);
        this->fwork[ZO_FWK_1] = SIN_DEG(gGameFrameCount * 7.0f) * 12.0f;
        this->fwork[ZO_FWK_2] = COS_DEG(gGameFrameCount * 9.0f) * 12.0f;
        this->fwork[ZO_FWK_3] = SIN_DEG(gGameFrameCount * 10.0f) * 30.0f;

        if ((this->timer_054 == 0) && (sZoSwork[ZO_BSS_5] < 2)) {
            Effect_Effect382_Spawn(this->obj.pos.x, this->obj.pos.z, 50.0f, 0.0f, 5.0f);
            Effect_Effect382_Spawn(this->obj.pos.x, this->obj.pos.z, 46.0f, 19.0f, 5.0f);
            Effect_Effect382_Spawn(this->obj.pos.x, this->obj.pos.z, 35.0f, 35.0f, 5.0f);
            Effect_Effect382_Spawn(this->obj.pos.x, this->obj.pos.z, 19.0f, 46.0f, 5.0f);
            Effect_Effect382_Spawn(this->obj.pos.x, this->obj.pos.z, 0.0f, 50.0f, 5.0f);
            Effect_Effect382_Spawn(this->obj.pos.x, this->obj.pos.z, -50.0f, 0.0f, 5.0f);
            Effect_Effect382_Spawn(this->obj.pos.x, this->obj.pos.z, -46.0f, 19.0f, 5.0f);
            Effect_Effect382_Spawn(this->obj.pos.x, this->obj.pos.z, -35.0f, 35.0f, 5.0f);
            Effect_Effect382_Spawn(this->obj.pos.x, this->obj.pos.z, -19.0f, 46.0f, 5.0f);
            this->timer_054 = 20;
            sZoSwork[ZO_BSS_5]++;
        }
    }

    if (gBossFrameCount == 530) {
        Radio_PlayMessage(gMsg_ID_2225, RCID_SLIPPY);
    }
    if (gBossFrameCount == 686) {
        gShowBossHealth = true;
    }
    if (gBossFrameCount > 686) {
        gBossHealthBar = this->health / 300.0f * 64.0f;
        gBossHealthBar += (s32) ((sZoSwork[ZO_BSS_11] / 20.0f) * 64.0f);
        gBossHealthBar += (s32) ((sZoSwork[ZO_BSS_12] / 20.0f) * 64.0f);
        gBossHealthBar += (s32) ((sZoSwork[ZO_BSS_9] / (20.0f * 2)) * 16.0f);
        gBossHealthBar += (s32) ((sZoSwork[ZO_BSS_10] / (20.0f * 2)) * 16.0f);
        gBossHealthBar += (s32) ((sZoSwork[ZO_BSS_13] / 61.0f) * 31.0f);
    }

    ZO_HIT_0(this)->z.offset = sZoFwork[ZO_BSF_43_Z] - this->obj.pos.z;
    ZO_HIT_0(this)->x.offset = sZoFwork[ZO_BSF_43_X] - this->obj.pos.x;
    ZO_HIT_1(this)->z.offset = sZoFwork[ZO_BSF_43_Z] - this->obj.pos.z;
    ZO_HIT_1(this)->x.offset = sZoFwork[ZO_BSF_43_X] - this->obj.pos.x;

    Animation_GetFrameData(&D_ZO_601996C, 0, this->vwork);

    if (sZoSwork[ZO_BSS_38] != 0) {
        sZoSwork[ZO_BSS_37] -= 10;
        if (sZoSwork[ZO_BSS_37] < 0) {
            sZoSwork[ZO_BSS_37] = 0;
        }
    } else {
        sZoSwork[ZO_BSS_37] += 10;
        if (sZoSwork[ZO_BSS_37] > 255) {
            sZoSwork[ZO_BSS_37] = 255;
        }
    }

    for (j = ZO_BSF_112, i = ZO_BSS_49, sp124 = 0; sp124 < 6; sp124++, i++, j++) {
        sZoFwork[j] = SIN_DEG(sZoSwork[i] * 50.0f) * Zoness_80193CC8(sZoSwork[i]);
    }
}

void Zoness_801986FC(ZoSarumarine* this, s32 arg1, f32 xOff, f32 yOff, f32 zOff, f32 yRot) {
    ZoBall* zoBall = NULL;
    Vec3f src = { 0.0f, 0.0f, 50.0f };
    Vec3f dest = { 0 };
    s32 i = 0;

    if ((sZoSwork[ZO_BSS_0 + arg1] == 0) && (sZoSwork[ZO_BSS_11 + arg1] != 0)) {
        sZoSwork[ZO_BSS_0 + arg1] = 70;
        i = arg1;
        if (arg1 != 0) {
            i = -1;
        }

        if (sZoSwork[ZO_BSS_12 + i] == 0) {
            sZoSwork[ZO_BSS_0 + arg1] = 40;
        }

        for (i = 0, zoBall = &gActors[0]; i < ARRAY_COUNT(gActors); i++, zoBall++) {
            if (zoBall->obj.status == OBJ_FREE) {
                D_ctx_801779A8[0] = 20.0f;
                Actor_Initialize(zoBall);
                zoBall->obj.status = OBJ_INIT;
                zoBall->obj.id = OBJ_ACTOR_ZO_BALL;

                zoBall->obj.pos.x = this->obj.pos.x + xOff;
                zoBall->obj.pos.y = this->obj.pos.y + yOff;
                zoBall->obj.pos.z = this->obj.pos.z + zOff;

                zoBall->health = 10;

                Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
                Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);

                Matrix_RotateY(gCalcMatrix, sZoFwork[ZO_BSF_15 + arg1] * M_DTOR, MTXF_APPLY);
                Matrix_RotateX(gCalcMatrix, M_DTOR * yRot, MTXF_APPLY);

                Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

                zoBall->vel.x = dest.x;
                zoBall->vel.y = dest.y;
                zoBall->vel.z = this->vel.z + dest.z;

                Object_SetInfo(&zoBall->info, zoBall->obj.id);
                sZoFwork[ZO_BSF_35 + arg1] = 40.0f;

                AUDIO_PLAY_SFX(NA_SE_EN_S_BALL_SHOT, this->sfxSource, 4);

                for (i = 0; i < 4; i++) {
                    Zoness_Effect394_Spawn3(zoBall->obj.pos.x + (dest.x * 4.3f), zoBall->obj.pos.y + (dest.y * 4.3f),
                                            zoBall->obj.pos.z + (dest.z * 4.3f) + 100.0f, 30.0f);
                }
                break;
            }
        }
    }

#ifndef AVOID_UB
    // @Bug: checking out of bounds
    // If this passes the boss kills himself, since gActors[60] overflows to gBosses[0].
    if (i >= ARRAY_COUNT(gActors)) {
        zoBall->obj.status = OBJ_FREE;
    }
#endif
}

void Zoness_801989FC(ZoSarumarine* this) {
    s32 i;
    Vec3f sp70 = { 0.0f, 0.0f, 20.0f };
    Vec3f sp64;
    ZoMine* actor246;
    s32 j;

    for (i = 0; i < 2; i++) {
        if (sZoSwork[ZO_BSS_11 + i] != 0) {
            for (j = 0, actor246 = &gActors[0]; j < ARRAY_COUNT(gActors); j++, actor246++) {
                if (actor246->obj.status == OBJ_FREE) {
                    Actor_Initialize(actor246);
                    actor246->obj.status = OBJ_INIT;
                    actor246->obj.id = OBJ_ACTOR_ZO_MINE;

                    actor246->obj.pos.x = sZoFwork[ZO_BSF_37_X + 3 * i];
                    actor246->obj.pos.y = sZoFwork[ZO_BSF_37_Y + 3 * i];
                    actor246->obj.pos.z = sZoFwork[ZO_BSF_37_Z + 3 * i];

                    actor246->obj.rot.y = this->obj.rot.y;
                    actor246->timer_0BC = 300;
                    actor246->health = 10;

                    Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
                    Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);
                    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp70, &sp64);
                    actor246->vel.x = sp64.x;
                    actor246->vel.z = this->vel.z + sp64.z;
                    Object_SetInfo(&actor246->info, actor246->obj.id);
                    AUDIO_PLAY_SFX(NA_SE_EN_MISSILE_SHOT, this->sfxSource, 4);
                    break;
                }
            }
        }
    }
}

void Zoness_80198BE8(ZoSarumarine* this, s32 arg1) {
    s32 i;
    Effect398* effect398;
    Vec3f src = { 0.0f, 0.0f, 100.0f };
    Vec3f dest;

    if ((sZoSwork[ZO_BSS_2 + arg1] == 0) && (sZoSwork[ZO_BSS_39 + arg1] == 0)) {
        if ((arg1 == 0) && (sZoSwork[ZO_BSS_41] == 0)) {
            AUDIO_PLAY_SFX(NA_SE_EN_ZOBOSS_BEAM, this->sfxSource, 4);
        }
        sZoSwork[ZO_BSS_2 + arg1] = 2;
        sZoSwork[ZO_BSS_41 + arg1]++;
        if (sZoSwork[ZO_BSS_41 + arg1] > 10) {
            sZoSwork[ZO_BSS_41 + arg1] = 0;
            sZoSwork[ZO_BSS_39 + arg1] = 30;
            if (arg1 == 1) {
                Audio_KillSfxBySourceAndId(this->sfxSource, NA_SE_EN_ZOBOSS_BEAM);
            }
        }

        for (i = 0, effect398 = &gEffects[0]; i < ARRAY_COUNT(gEffects); i++, effect398++) {
            if (effect398->obj.status == OBJ_FREE) {
                Effect_Initialize(effect398);
                effect398->obj.status = OBJ_INIT;
                effect398->obj.id = OBJ_EFFECT_398;
                effect398->timer_50 = 100;
                effect398->state = 1;
                effect398->scale2 = 1.0f;
                effect398->obj.rot.z = 30.0f;
                effect398->obj.pos.x = sZoFwork[ZO_BSF_93_X + 3 * arg1];
                effect398->obj.pos.y = sZoFwork[ZO_BSF_93_Y + 3 * arg1];
                effect398->obj.pos.z = sZoFwork[ZO_BSF_93_Z + 3 * arg1];
                Matrix_RotateY(gCalcMatrix, sZoFwork[ZO_BSF_8 + 2 * arg1] * M_DTOR, MTXF_NEW);
                Matrix_RotateX(gCalcMatrix, sZoFwork[ZO_BSF_7 + 2 * arg1] * M_DTOR, MTXF_APPLY);
                Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_APPLY);
                Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);
                Matrix_RotateZ(gCalcMatrix, this->obj.rot.z * M_DTOR, MTXF_APPLY);
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);
                effect398->vel.x = dest.x;
                effect398->vel.y = dest.y;
                effect398->vel.z = dest.z - gPathVelZ;
                Object_SetInfo(&effect398->info, effect398->obj.id);
                break;
            }
        }
#ifndef AVOID_UB
        if (i >= ARRAY_COUNT(gActors)) {
            effect398->obj.status = OBJ_FREE;
        }
#endif
    }
}

void Zoness_80198ECC(ZoSarumarine* this) {
    sZoSwork[ZO_BSS_18] = 500;
    this->timer_050 = 100;
    this->timer_054 = 0;
    sZoSwork[ZO_BSS_5] = 0;
    sZoFwork[ZO_BSF_25] = -1200.0f;
    sZoFwork[ZO_BSF_23] = 15.0f;
    sZoFwork[ZO_BSF_28] = -3500.0f;
    sZoFwork[ZO_BSF_77] = 0.0f;
    this->state = 8;
    this->fwork[ZO_FWK_4] = 1.0f;
}

void Zoness_80198F3C(ZoSarumarine* this, s32 arg1, s32 arg2) {
    if (((gGameFrameCount % 8) == 0) && (Rand_ZeroOne() < 0.5f)) {
        sZoLimbTimers[ZO_LIMB_7 + 4 * arg1] = sZoLimbTimers[ZO_LIMB_21 + 2 * arg1] =
            sZoLimbTimers[ZO_LIMB_22 + 2 * arg1] = 15;
    }
    func_effect_8007D0E0(sZoFwork[ZO_BSF_0 + arg2] + RAND_FLOAT_CENTERED(400.0f),
                         sZoFwork[ZO_BSF_1 + arg2] + RAND_RANGE(-160.0f, 640.0f), sZoFwork[ZO_BSF_2 + arg2], 7.0f);
    if ((gGameFrameCount % 2) == 0) {
        Effect_Effect390_Spawn(sZoFwork[ZO_BSF_0 + arg2], sZoFwork[ZO_BSF_1 + arg2], sZoFwork[ZO_BSF_2 + arg2],
                               this->vel.x, this->vel.y, this->vel.z, 0.2f, 10);
    }
}

void Zoness_8019907C(ZoSarumarine* this) {
    if ((sZoSwork[ZO_BSS_9] == 0) && (sZoSwork[ZO_BSS_10] == 0)) {
        if ((sZoSwork[ZO_BSS_31] == 0) && (sZoSwork[ZO_BSS_30] != 0)) {
            Radio_PlayMessage(gMsg_ID_6082, RCID_PEPPY);
            sZoSwork[ZO_BSS_34] = 333;
        }
        if (sZoSwork[ZO_BSS_30] == 0) {
            Radio_PlayMessage(gMsg_ID_6076, RCID_BOSS_ZONESS);
            sZoSwork[ZO_BSS_34] = 333;
            sZoSwork[ZO_BSS_30]++;
        }
        sZoFwork[ZO_BSF_77] = 0.0f;
        this->state = 5;
    } else {
        Zoness_80198ECC(this);
    }
}

void Zoness_8019914C(ZoSarumarine* this, s32 arg1) {
    sZoLimbTimers[ZO_LIMB_7 + 4 * arg1] = sZoLimbTimers[ZO_LIMB_21 + arg1 * 2] = sZoLimbTimers[ZO_LIMB_22 + arg1 * 2] =
        LIMB_DESTROYED;
    sZoFwork[ZO_BSF_77] = 0.0f;
    sZoSwork[ZO_BSS_36] = sZoSwork[ZO_BSS_16] = 0;
    this->swork[ZO_SWK_4] = 1000;
    this->state = 3;
    if ((sZoSwork[ZO_BSS_11] == 0) && (sZoSwork[ZO_BSS_12] == 0)) {
        this->fwork[ZO_FWK_6] = this->obj.pos.x;
        sZoSwork[ZO_BSS_20] = sZoSwork[ZO_BSS_24] = 1;
    }
}

f32 D_i3_801BF73C[2] = { -80.0f, 80.0f };

void Zoness_801991D0(Boss* this, s32 arg1) {
    Math_SmoothStepToF(&sZoFwork[ZO_BSF_4], D_i3_801BF73C[arg1], 1.0f, 5.0f, 0.001f);
    if (sZoFwork[ZO_BSF_4] == D_i3_801BF73C[arg1]) {
        Math_SmoothStepToF(&sZoFwork[ZO_BSF_3], -30.0f, 1.0f, 3.0f, 0.001f);
        if (sZoFwork[ZO_BSF_3] == -30.0f) {
            this->timer_052 = 60;
            sZoSwork[ZO_BSS_36] = 0;
            sZoSwork[ZO_BSS_16] = arg1 + 1;
            sZoFwork[ZO_BSF_77] = 0.0f;
        }
    }

    if (arg1 == 0) { // all divisible by 13
        ZO_HIT_12(this)->z.offset = -556.39996f;
        ZO_HIT_12(this)->z.size = 130.0f;
        ZO_HIT_12(this)->y.offset = 663.0f;
        ZO_HIT_12(this)->y.size = 171.59999f;
        ZO_HIT_12(this)->x.offset = 395.19998f;
        ZO_HIT_12(this)->x.size = 241.79999f;
    } else {
        ZO_HIT_12(this)->z.offset = -556.39996f;
        ZO_HIT_12(this)->z.size = 130.0f;
        ZO_HIT_12(this)->y.offset = 663.0f;
        ZO_HIT_12(this)->y.size = 171.59999f;
        ZO_HIT_12(this)->x.offset = -395.19998f;
        ZO_HIT_12(this)->x.size = 241.79999f;
    }
}

#define ZO_HIT_8_2(bossZO, index) ((Hitbox*) (ZO_HIT_7(bossZO) + 1) + (index))
#define ZO_HIT_10_2(bossZO, index) ((Hitbox*) (ZO_HIT_8(bossZO, 0) + 2) + (index))

void Zoness_80199394(ZoSarumarine* this, s32 arg1) {
    sZoSwork[ZO_BSS_11 + arg1] = 20;

    ZO_HIT_8(this, arg1)->z.offset = -213.2f;
    ZO_HIT_10(this, arg1)->z.offset = -351.0f;
    this->timer_050 = 20;
    sZoFwork[ZO_BSF_17 + arg1] = sZoFwork[ZO_BSF_77] = 0.0f;
    sZoSwork[ZO_BSS_16] = 3;
    AUDIO_PLAY_SFX(NA_SE_EN_COMBINE, this->sfxSource, 4);
}

void Zoness_80199470(ZoSarumarine* this, s32 arg1) {
    if (sZoSwork[ZO_BSS_13] == 0) {
        if (sZoFwork[ZO_BSF_17 + arg1] > -400.0f) {
            sZoFwork[ZO_BSF_17 + arg1] -= 4.0f;
        } else {
            if (sZoSwork[ZO_BSS_36] == 0) {
                sZoSwork[ZO_BSS_36]++;
                sZoFwork[ZO_BSF_77] = 0.0f;
            }
            Zoness_8019962C(this, 0.0f);
            if (this->obj.rot.y == 0.0f) {
                sZoSwork[ZO_BSS_36] = sZoSwork[ZO_BSS_16] = 0;
                sZoFwork[ZO_BSF_77] = 0;
                this->swork[ZO_SWK_4] = 1000;
                this->state = 3;
                if ((sZoSwork[ZO_BSS_11] == 0) && (sZoSwork[ZO_BSS_12] == 0)) {
                    sZoSwork[ZO_BSS_20] = sZoSwork[ZO_BSS_24] = 1;
                }
                Zoness_8019914C(this, arg1);
            }
        }
    } else if ((sZoSwork[ZO_BSS_13] != 1) && (this->timer_052 == 0)) {
        Math_SmoothStepToF(&sZoFwork[ZO_BSF_17 + arg1], 0.0f, 1.0f, 5.0f, 0.001f);
        Math_SmoothStepToF(&sZoFwork[ZO_BSF_3], -30.0f, 1.0f, 3.0f, 0.001f);
        if (sZoFwork[ZO_BSF_17 + arg1] == 0.0f) {
            Zoness_80199394(this, arg1);
        }
    }
}

void Zoness_8019962C(ZoSarumarine* this, f32 arg1) {
    Math_SmoothStepToF(&sZoFwork[ZO_BSF_77], 2.0f, 0.1f, 0.5f, 0.0001f);
    Math_SmoothStepToAngle(&this->obj.rot.y, arg1, 1.0f, sZoFwork[ZO_BSF_77], 0.0001f);
}

void Zoness_ZoBall_Update(ZoBall* this) {
    s32 i;

    if ((this->dmgType != DMG_NONE) && (this->health != 0)) {
        this->health -= this->damage;
        if (this->health <= 0) {
            this->health = 0;
            for (i = 0; i < 5; i++) {
                func_effect_80079618(RAND_FLOAT_CENTERED(50.0f) + this->obj.pos.x,
                                     RAND_FLOAT_CENTERED(50.0f) + this->obj.pos.y,
                                     RAND_FLOAT_CENTERED(50.0f) + this->obj.pos.z, 1.0f);
            }
            func_effect_8007D0E0(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + 200.0f, 5.0f);
            this->itemDrop = DROP_BOMB;
            this->dmgSource = DMG_SRC_2;
            this->obj.pos.z -= 100.0f;
            Actor_Despawn(this);
            Object_Kill(&this->obj, this->sfxSource);
            Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_EXPLOSION_S);
        }
        this->dmgType = DMG_NONE;
    }
    this->fwork[0] += 10.0f;
    Zoness_8018FF50(this);
}

void Zoness_ZoBall_Draw(ZoBall* this) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_70);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
    Matrix_Scale(gGfxMatrix, 2.6f, 2.6f, 2.6f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, aZoBallDL);
}

void Zoness_Effect374_Setup(Effect374* this, f32 xPos, f32 yPos, f32 zPos) {
    Effect_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_EFFECT_374;

    this->state = 1;
    this->timer_50 = 30;
    this->unk_44 = 192;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;
    this->obj.pos.x = xPos;
    this->scale1 = this->scale2 = 2.5f;
    func_effect_8007D0E0(xPos, yPos + 30.0f, zPos, 7.0f);
    Effect386_Spawn1(this->obj.pos.x, this->obj.pos.y + 30.0f, this->obj.pos.z, 0.0f, 0.0f, 0.0f, 4.0f, 5);
    Object_SetInfo(&this->info, this->obj.id);
}

void Zoness_Effect374_Spawn(f32 xPos, f32 yPos, f32 zPos) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Zoness_Effect374_Setup(&gEffects[i], xPos, yPos, zPos);
            break;
        }
    }
}

void Zoness_ZoMine_Update(ZoMine* this) {
    f32 sp3C;
    f32 sp38;
    s32 sp34;

    this->obj.rot.x += 5.0f;

    switch (this->state) {
        case 0:
            if (this->health == 0) {
                this->iwork[0]++;
                this->health = 10;
                this->iwork[1] = 1;
                this->state = 2;
                this->fwork[0] = -50.0f;
            } else {
                this->vel.y = 60.0f;
                this->gravity = 1.0f;
                if (gBosses[0].obj.pos.y < 0.0f) {
                    this->obj.pos.y = -100.0f;
                }
                this->state++;
            }
            break;

        case 1:
            if ((Play_CheckDynaFloorCollision(&sp3C, &sp34, this->obj.pos.x, this->obj.pos.y, this->obj.pos.z) != 0) &&
                (this->iwork[1] == 0)) {
                Effect_Effect391_Spawn(this->obj.pos.x, sp3C, this->obj.pos.z, 0.0f, 0.5f);
                this->iwork[1]++;
                AUDIO_PLAY_SFX(NA_SE_ON_SPLASH_S, this->sfxSource, 4);
            }

            Math_SmoothStepToF(&this->vel.y, -60.0f, 0.5f, 5.0f, 0.00001f);

            if (this->obj.pos.y < -30.0f) {
                this->state++;
                this->vel.y = 0.0f;
                this->gravity = 0.0f;
                this->fwork[0] = 0.0f;
            }
            break;

        case 2:
            this->gravity = 1.0f;
            if (Play_CheckDynaFloorCollision(&sp3C, &sp34, this->obj.pos.x, this->fwork[0] + this->obj.pos.y,
                                             this->obj.pos.z) != 0) {
                this->gravity = 0.0f;
                Math_SmoothStepToF(&this->fwork[0], -50.0f, 0.1f, 2.0f, 0.001f);
                sp38 = 10.0f;
                if (Math_SmoothStepToF(&this->obj.pos.y, sp3C, 0.1f, 5.0f, 0) >= 0.0f) {
                    sp38 = 350.0f;
                }
                Math_SmoothStepToAngle(&this->obj.rot.z, sp38, 0.1f, 1.0f, 0);
            }

            if ((this->dmgType != DMG_NONE) && (this->health != 0)) {
                this->dmgType = DMG_NONE;
                this->itemDrop = DROP_SILVER_RING_50p;
                func_effect_8007D0E0(this->obj.pos.x, this->obj.pos.y + 100.0f, this->obj.pos.z, 7.0f);
                this->dmgSource = DMG_SRC_2;
                this->obj.pos.y += 200.0f;
                Actor_Despawn(this);
                Object_Kill(&this->obj, this->sfxSource);
                Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_OB_EXPLOSION_S);
            } else {
                if ((fabsf(this->obj.pos.z - gPlayer[0].trueZpos) < 800.0f) || (this->dmgType != DMG_NONE)) {
                    Zoness_Effect374_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z);
                    Object_Kill(&this->obj, this->sfxSource);
                    Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_EXPLOSION_M);
                }
            }
            break;
    }

    if ((this->timer_0BC == 0) && (this->iwork[0] == 0)) {
        func_effect_8007D0E0(this->obj.pos.x, this->obj.pos.y + 100.0f, this->obj.pos.z, 7.0f);
        this->itemDrop = DROP_SILVER_RING_50p;
        this->dmgSource = DMG_SRC_2;
        this->obj.pos.y += 200.0f;
        Actor_Despawn(this);
        Object_Kill(&this->obj, this->sfxSource);
    }
}

void Zoness_ZoMine_Draw(ZoMine* this) {
    Matrix_Scale(gGfxMatrix, 2.0f, 2.0f, 2.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_ZO_6025E60);
}

void Zoness_80199E9C(ZoCraneMagnet* this, f32 arg1, f32 arg2) {
    this->obj.pos.x = sZoFwork[ZO_BSF_60_X];
    Math_SmoothStepToF(&this->fwork[0], arg1, 1.0f, arg2, 0.001f);
    this->obj.pos.y = sZoFwork[ZO_BSF_60_Y] + this[0].fwork[0];
    this->obj.pos.z = sZoFwork[ZO_BSF_60_Z];
}

void Zoness_ZoCraneMagnet_Update(ZoCraneMagnet* this) {
    if (sZoSwork[ZO_BSS_13] == 0) {
        this->state = 3;
        this->vel.y = -50.0f;
        this->obj.pos.x = sZoFwork[ZO_BSF_60_X];
        Math_SmoothStepToF(&this->fwork[0], -500.0f, 1.0f, 100.0f, 0.00001f);
        this->obj.pos.z = sZoFwork[ZO_BSF_60_Z];
        if (this->obj.pos.y < -400.0f) {
            Object_Kill(&this->obj, this->sfxSource);
        }
    }

    switch (this->state) {
        case 0:
            this->obj.rot.y += 2.0f;
            Zoness_80199E9C(this, 0.0f, 20.0f);
            switch (sZoSwork[ZO_BSS_16]) {
                case 1:
                    this->fwork[1] = sZoFwork[ZO_BSF_68_Y] - sZoFwork[ZO_BSF_60_Y];
                    AUDIO_PLAY_SFX(NA_SE_EN_PULL_CHAIN1, this->sfxSource, 4);
                    this->state++;
                    break;
                case 2:
                    this->fwork[1] = sZoFwork[ZO_BSF_71_Y] - sZoFwork[ZO_BSF_60_Y];
                    AUDIO_PLAY_SFX(NA_SE_EN_PULL_CHAIN1, this->sfxSource, 4);
                    this->state++;
                    break;
            }
            break;

        case 1:
            if (gBosses[0].timer_052 != 0) {
                this->obj.rot.y += 2.0f;
                Zoness_80199E9C(this, this->fwork[1], 20.0f);
            } else {
                switch (sZoSwork[ZO_BSS_16]) {
                    case 1:
                        this->fwork[1] = sZoFwork[ZO_BSF_68_Y] - sZoFwork[ZO_BSF_60_Y];
                        Zoness_80199E9C(this, this->fwork[1], 20.0f);
                        break;
                    case 2:
                        this->fwork[1] = sZoFwork[ZO_BSF_71_Y] - sZoFwork[ZO_BSF_60_Y];
                        Zoness_80199E9C(this, this->fwork[1], 20.0f);
                        break;
                    case 3:
                        this->obj.rot.y += 2.0f;
                        if (gBosses[0].timer_050 != 0) {
                            Zoness_80199E9C(this, 0.0f, 10.0f);
                        } else {
                            this->state = 0;
                            Audio_KillSfxBySource(this->sfxSource);
                        }
                        break;
                }
            }
            break;
    }

    if (this->dmgType != DMG_NONE) {
        if (this->dmgType == DMG_BEAM) {
            AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
        }
        this->dmgType = DMG_NONE;
    }
}

void Zoness_ZoCraneMagnet_Draw(ZoCraneMagnet* this) {
    f32 var_fv0;
    s32 i;
    s32 j;

    Matrix_Scale(gGfxMatrix, 2.0f, 2.0f, 2.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    RCP_SetupDL_57(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
    gSPDisplayList(gMasterDisp++, D_ZO_601C590);
    RCP_SetupDL_60(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);

    if (((this->state == 1) && (gBosses[0].timer_052 != 0)) || (this->state == 0)) {
        Matrix_RotateY(gGfxMatrix, gGameFrameCount * M_DTOR, MTXF_APPLY);
    }

    var_fv0 = sZoFwork[ZO_BSF_60_Y] + -1.0f * this->fwork[0] - this->obj.pos.y;

    for (i = 1; var_fv0 >= 0.0f; i++) {
        var_fv0 -= 117.0f;
    }

    if (i > 30) {
        i = 30;
    }
    if ((i <= 0) || (this->fwork[0] == 0)) {
        i = 1;
    }

    for (j = 0; j < i; j++) {
        Matrix_Translate(gGfxMatrix, 0.0f, 30.0f, 0.0f, MTXF_APPLY);
        Matrix_RotateY(gGfxMatrix, M_PI / 2, MTXF_APPLY);
        Matrix_Push(&gGfxMatrix);
        Matrix_Scale(gGfxMatrix, 0.75f, 0.75f, 0.75f, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, D_ZO_6018660);
        Matrix_Pop(&gGfxMatrix);
    }
}

void Zoness_8019A4E0(Actor* this, f32 xPos, f32 yPos, f32 zPos, f32 arg4) {
    f32 x = xPos - this->obj.pos.x;
    f32 y = yPos - this->obj.pos.y;
    f32 z = zPos - this->obj.pos.z;
    f32 xAngle;
    f32 yAngle;
    Vec3f src;
    Vec3f dest;

    yAngle = +Math_Atan2F(x, z);
    xAngle = -Math_Atan2F(y, sqrtf(SQ(x) + SQ(z)));

    Matrix_RotateY(gCalcMatrix, yAngle, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, xAngle, MTXF_APPLY);

    src.x = 0.0f;
    src.y = 0.0f;
    src.z = arg4;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

    this->vel.x = dest.x;
    this->vel.y = dest.y;
    this->vel.z = dest.z;
}

void Zoness_ZoSpikeBall_Update(ZoSpikeBall* this) {
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    s32 sp40;
    f32 var_fa0;
    f32 var_fv1;

    if ((gBosses[0].state == 6) || (gBosses[0].state == 7)) {
        Audio_KillSfxBySource(this->sfxSource);
        this->state = 10;
        this->vel.z = 40.0f;
    }

    this->fwork[3] += 10.0f;
    this->fwork[1] = 70.0f;

    switch (this->state) {
        case 0:
            this->obj.pos.x = sZoFwork[ZO_BSF_65_X];
            this->obj.pos.y = sZoFwork[ZO_BSF_65_Y];
            this->obj.pos.z = sZoFwork[ZO_BSF_65_Z];

            if ((sZoSwork[ZO_BSS_20] != 0) && (this->timer_0BC == 0)) {
                if ((sZoSwork[ZO_BSS_8] == 0) && (gBosses[0].state == 8)) {
                    var_fv1 = RAND_FLOAT_CENTERED(3000.0f);
                    var_fa0 = 0.0f;
                } else {
                    var_fv1 = 0.0f;
                    var_fa0 = 100.0f;
                }
                Zoness_8019A4E0(this, gPlayer[0].pos.x + var_fv1, gPlayer[0].pos.y + var_fa0, gPlayer[0].pos.z, 80.0f);
                this->vel.z -= gPathVelZ;
                Zoness_Effect394_Spawn3(sZoFwork[ZO_BSF_65_X], sZoFwork[ZO_BSF_65_Y], sZoFwork[ZO_BSF_65_Z], 30.0f);
                Zoness_Effect394_Spawn3(sZoFwork[ZO_BSF_65_X], sZoFwork[ZO_BSF_65_Y], sZoFwork[ZO_BSF_65_Z], 30.0f);
                Zoness_Effect394_Spawn3(sZoFwork[ZO_BSF_65_X], sZoFwork[ZO_BSF_65_Y], sZoFwork[ZO_BSF_65_Z], 30.0f);

                this->timer_0BC = (s32) ((fabsf(sZoFwork[ZO_BSF_28] - -2600.0f) / 100.0f) + 30.0f);
                this->timer_0C0 = 3;
                AUDIO_PLAY_SFX(NA_SE_EN_M_BALL_SHOT, this->sfxSource, 4);
                this->state++;
            }
            break;

        case 1:
            if (this->timer_0C0 != 0) {
                D_ctx_801779A8[0] = 40.0f;
            }
            this->iwork[0] = 0;
            if (this->timer_0BC == 0) {
                this->vel.x = 0.0f;
                this->vel.z = -gPathVelZ;
                this->gravity = 5.0f;
                this->fwork[5] = this->vel.y * -3.0f;
                if (this->obj.pos.y < -150.0f) {
                    this->gravity = 0.0f;
                    AUDIO_PLAY_SFX(NA_SE_EN_PULL_CHAIN0, this->sfxSource, 4);
                    this->state++;
                }
            }
            break;

        case 2:
            if ((sZoSwork[ZO_BSS_8] == 0) && (gBosses[0].state == 8)) {
                this->fwork[5] = 0.0f;
                this->obj.pos.x = sZoFwork[ZO_BSF_65_X];
                this->obj.pos.y = sZoFwork[ZO_BSF_65_Y];
                this->obj.pos.z = sZoFwork[ZO_BSF_65_Z];
                sp48 = sp4C = 30.0f;
            } else {
                Math_SmoothStepToF(&this->fwork[5], 0.0f, 1.0f, 30.0f, 0.0f);
                sp4C = fabsf(this->obj.pos.x - sZoFwork[ZO_BSF_65_X]);
                sp48 = fabsf(this->obj.pos.z - sZoFwork[ZO_BSF_65_Z]);
                var_fa0 = sqrtf(SQ(sp4C) + SQ(sp48)) * 0.5f;
                Zoness_8019A4E0(this, sZoFwork[ZO_BSF_65_X], sZoFwork[ZO_BSF_65_Y] - var_fa0, sZoFwork[ZO_BSF_65_Z],
                                30.0f);
                this->vel.z -= gPathVelZ;
            }

            if (Object_CheckHitboxCollision(&this->obj.pos, gBosses[0].info.hitbox, &gBosses[0].obj, 0.0f, 0.0f,
                                            0.0f) != 0) {
                this->fwork[6] = 50.0f;
                AUDIO_PLAY_SFX(NA_SE_OB_METAL_BOUND_M, this->sfxSource, 4);
            }
            this->vel.z += this->fwork[6] * 0.8f;
            this->vel.y += this->fwork[6] * 1.4f;

            this->fwork[6] -= 8.0f;
            if (this->fwork[6] < 0.0f) {
                this->fwork[6] = 0.0f;
            }
            if ((sp4C <= 30.0f) && (sp48 <= 30.0f)) {
                this->state = 0;
                Audio_KillSfxBySource(this->sfxSource);
                AUDIO_PLAY_SFX(NA_SE_EN_COMBINE, this->sfxSource, 4);
                this->timer_0BC = 40;
                sZoFwork[ZO_BSF_74] = sZoFwork[ZO_BSF_75] = 0.0f;
                sZoSwork[ZO_BSS_19] = 1;
                sZoSwork[ZO_BSS_20] = this->iwork[0] = sZoSwork[ZO_BSS_20] = 0;
            }
            break;
    }
    Zoness_8018FF50(this);

    if (this->dmgType != DMG_NONE) {
        if (this->dmgType == DMG_BEAM) {
            AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
        }
        this->dmgType = DMG_NONE;
    }

    if (((gGameFrameCount % 8) == 0) && (this->state != 0) && (this->iwork[0] < 8) &&
        (Play_CheckDynaFloorCollision(&sp44, &sp40, this->obj.pos.x, this->obj.pos.y - 100.0f, this->obj.pos.z) != 0)) {
        Effect_Effect391_Spawn(this->obj.pos.x, sp44, this->obj.pos.z, 0.0f, 0.7f);
        this->iwork[0]++;
        if (this->vel.y >= 0.0f) {
            AUDIO_PLAY_SFX(NA_SE_OUT_SPLASH_L, this->sfxSource, 4);
        } else {
            AUDIO_PLAY_SFX(NA_SE_IN_SPLASH_L, this->sfxSource, 4);
        }
    }
}

void Zoness_ZoSpikeBall_Draw(ZoSpikeBall* this) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_fs0;
    f32 temp_fs3;
    f32 temp_fs4;
    f32 temp_fs0_2;
    f32 temp_fs1_2;
    f32 temp_fs0_4;
    f32 var_fs5 = 90.0f;
    s32 i;
    f32 sp94;
    s32 var_s4;

    Matrix_Pop(&gGfxMatrix);
    Matrix_Push(&gGfxMatrix);
    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);

    if ((gBosses[0].state != 6) && (gBosses[0].state != 7)) {
        RCP_SetupDL_60(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
        gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
        temp_fa0 = sZoFwork[ZO_BSF_65_X] - this->obj.pos.x;
        temp_fs0 = sZoFwork[ZO_BSF_65_Y] - this->obj.pos.y;
        temp_fa1 = sZoFwork[ZO_BSF_65_Z] - this->obj.pos.z;

        temp_fs3 = sqrtf(SQ(temp_fa0) + SQ(temp_fs0) + SQ(temp_fa1));
        temp_fs4 = Math_Atan2F(temp_fa0, temp_fa1);
        temp_fs0_2 = -Math_Atan2F(temp_fs0, sqrtf(SQ(temp_fa0) + SQ(temp_fa1)));
        var_s4 = temp_fs3 / 70.0f;
        if (var_s4 > 50) {
            var_s4 = 50;
        }
        if (var_s4 < 0) {
            var_s4 = 0;
        }
        Matrix_Translate(gGfxMatrix, this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + gPathProgress, MTXF_APPLY);
        Matrix_RotateY(gGfxMatrix, temp_fs4, MTXF_APPLY);
        Matrix_RotateX(gGfxMatrix, temp_fs0_2, MTXF_APPLY);
        Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, 0.0f, MTXF_APPLY);

        sp94 = (180.0f / var_s4) + 1.0f;

        // @port: Tag the transform.
        FrameInterpolation_RecordOpenChild("ZoSpikeBall", 0);

        for (i = 0; i < var_s4; i++) {
            temp_fs1_2 = SIN_DEG(i * sp94) * this->fwork[5];
            temp_fs0_4 = COS_DEG(i * sp94) * this->fwork[5] * -0.25f;
            Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, this->fwork[1], MTXF_APPLY);
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, 0.0f, temp_fs1_2, 0.0f, MTXF_APPLY);
            Matrix_RotateX(gGfxMatrix, M_DTOR * temp_fs0_4, MTXF_APPLY);
            Matrix_Push(&gGfxMatrix);
            Matrix_RotateZ(gGfxMatrix, M_DTOR * var_fs5, MTXF_APPLY);
            Matrix_RotateX(gGfxMatrix, M_PI / 2, MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, 1.5f, 1.5f, 1.5f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_ZO_6018660);
            Matrix_Pop(&gGfxMatrix);
            Matrix_Pop(&gGfxMatrix);
            var_fs5 += 90.0f;
        }
        // @port Pop the transform id.
        FrameInterpolation_RecordCloseChild();
    }
    Matrix_Pop(&gGfxMatrix);
    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + gPathProgress, MTXF_APPLY);
    Matrix_RotateY(gGfxMatrix, this->obj.rot.y * M_DTOR, MTXF_APPLY);
    Matrix_RotateX(gGfxMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, 2.6f, 2.6f, 2.6f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    RCP_SetupDL(&gMasterDisp, SETUPDL_70);
    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
    gSPDisplayList(gMasterDisp++, D_ZO_6004380);
    Matrix_RotateY(gGfxMatrix, sZoFwork[ZO_BSF_19] * M_DTOR, MTXF_APPLY);
    Matrix_RotateX(gGfxMatrix, this->fwork[2] * M_DTOR, MTXF_APPLY);
    Matrix_RotateZ(gGfxMatrix, this->fwork[3] * M_DTOR, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    RCP_SetupDL_55();
    gSPDisplayList(gMasterDisp++, D_ZO_601BCC0);
}

Vec3f sTankerContainerInitPos[3] = {
    { 0.0f, 50.0f, -200.0f }, // first position seems unused
    { 0.0f, 50.0f, 200.0f },
    { 0.0f, 50.0f, 600.0f },
};
Vec3f sSupplyCraneContainerInitPos[3] = {
    { 0.0f, 300.0f, 0.0f }, // first position seems unused
    { 0.0f, 300.0f, -200.0f },
    { 0.0f, 300.0f, 300.0f },
};
s32 D_i3_801BF78C[30] = {
    0, 7, 7, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 4, 7, 0, 0, 0, 0, 327, 324, 0, 322, 327, 0, 324, 324, 0, 336, 0,
};
f32 sZoSupplyCraneXRots[8] = { 0.0f, 0.0f, 270.0f, 90.0f, 0.0f, 180.0f, 400.0f, 400.0f };

void Zoness_ZoTanker_Init(ZoTanker* actor) {
    s32 temp_v1;
    s32 containerIdx;
    s32 i;
    s32 j;
    Vec3f containerOffsetPos;
    Vec3f tankerVelSrc;
    Vec3f tankerVelDest;

    actor->obj.pos.y = 120.0f;
    actor->scale = -1.0f;

    Matrix_RotateY(gCalcMatrix, actor->obj.rot.y * M_DTOR, MTXF_NEW);

    tankerVelSrc.x = tankerVelSrc.y = 0.0f;
    tankerVelSrc.z = actor->obj.rot.z;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &tankerVelSrc, &tankerVelDest);

    actor->vel.x = tankerVelDest.x;
    actor->vel.z = tankerVelDest.z;
    actor->obj.rot.z = 0.0f;

    containerIdx = 1;
    if (actor->obj.rot.x >= 100.0f) {
        actor->state = 1;
        actor->iwork[3] = actor->obj.rot.x / 100.0f;
        actor->obj.rot.x = (s32) fabsf(Math_ModF(actor->obj.rot.x, 100.0f));
    }

    for (i = 0, j = 0; (containerIdx < 3) && (i < ARRAY_COUNT(gActors)); i++) {
        if (gActors[i].obj.status == OBJ_FREE) {
            if (actor->state == 0) {
                Matrix_MultVec3f(gCalcMatrix, &sTankerContainerInitPos[containerIdx], &containerOffsetPos);
            } else {
                Matrix_MultVec3f(gCalcMatrix, &sSupplyCraneContainerInitPos[containerIdx], &containerOffsetPos);
            }

            Actor_Initialize(&gActors[i]);
            gActors[i].obj.status = OBJ_INIT;
            if (actor->state == 0) {
                gActors[i].obj.id = OBJ_ACTOR_ZO_CONTAINER;
                gActors[i].iwork[3] = 777;
            } else {
                gActors[i].obj.id = OBJ_ACTOR_ZO_SUPPLYCRANE;
            }

            gActors[i].obj.pos.x = actor->obj.pos.x + containerOffsetPos.x;
            gActors[i].obj.pos.y = actor->obj.pos.y + containerOffsetPos.y;
            gActors[i].obj.pos.z = actor->obj.pos.z + containerOffsetPos.z;

            ((s32*) &actor->iwork[7])[containerIdx] = (s32) (actor->obj.rot.x * 3.0f) + containerIdx;

            gActors[i].obj.rot.y = actor->obj.rot.y;
            gActors[i].iwork[0] = D_i3_801BF78C[((s32*) &actor->iwork[7])[containerIdx]];
            gActors[i].iwork[1] = actor->index;
            gActors[i].iwork[2] = containerIdx;
            Object_SetInfo(&gActors[i].info, gActors[i].obj.id);

            if (actor->state != 0) {
                gActors[i].state = 3;
                if (sZoSupplyCraneXRots[actor->iwork[3]] >= 361.0f) {
                    gActors[i].obj.rot.x = actor->obj.rot.y;
                } else {
                    temp_v1 = (actor->iwork[3] * 2) + j;
                    gActors[i].obj.rot.x = sZoSupplyCraneXRots[temp_v1];
                }
                j++;
            }
            ((uintptr_t*) &actor->iwork[0])[containerIdx] = i;
            containerIdx++;
        }
    }
    actor->obj.rot.x = 0.0f;
    AUDIO_PLAY_SFX(NA_SE_EN_SHIP_ENGINE_L, actor->sfxSource, 4);
}

void Zoness_ZoTanker_Update(ZoTanker* this) {
    f32 sp6C;
    s32 sp68;
    s32 i;
    Vec3f sp58;
    Actor* actor;

    Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);

    switch (this->state) {
        case 0:
            for (i = 1; i < 3; i++) {
                actor = &gActors[this->iwork[i]];
                if ((actor->obj.status != OBJ_FREE) && (actor->iwork[1] == this->index) &&
                    (actor->obj.id == OBJ_ACTOR_ZO_CONTAINER)) {
                    Matrix_MultVec3f(gCalcMatrix, &sTankerContainerInitPos[i], &sp58);
                    actor->obj.pos.x = this->obj.pos.x + sp58.x;
                    actor->obj.pos.y = this->obj.pos.y + sp58.y;
                    actor->obj.pos.z = this->obj.pos.z + sp58.z;
                }
            }
            break;

        case 1:
            for (i = 1; i < 3; i++) {
                actor = &gActors[this->iwork[i]];
                if ((actor->obj.status != OBJ_FREE) && (actor->obj.id == OBJ_ACTOR_ZO_SUPPLYCRANE) &&
                    (actor->iwork[1] == this->index)) {
                    Matrix_MultVec3f(gCalcMatrix, &sSupplyCraneContainerInitPos[i], &sp58);
                    actor->obj.pos.x = this->obj.pos.x + sp58.x;
                    actor->obj.pos.y = this->obj.pos.y + sp58.y;
                    actor->obj.pos.z = this->obj.pos.z + sp58.z;
                }
            }
            break;
    }

    if ((fabsf(this->obj.pos.z - gPlayer[0].trueZpos) < 1000.0f) &&
        Play_CheckDynaFloorCollision(&sp6C, &sp68, this->obj.pos.x, this->obj.pos.y, this->obj.pos.z)) {
        Math_SmoothStepToF(&this->obj.pos.y, sp6C, 0.1f, 4.0f, 0.0f);
    }
}

void Zoness_ZoTanker_Draw(ZoTanker* this) {
    gSPDisplayList(gMasterDisp++, D_ZO_6006360);
}

void Zoness_ZoContainer_Init(ZoContainer* this) {
    if (this->iwork[3] == 0) {
        this->iwork[0] = this->obj.rot.z / 10.0f;
        this->obj.rot.z = 0.0f;
    }
    this->health = 30;
}

ItemDrop sZoContainerItemDrops[10] = { DROP_SILVER_RING, DROP_BOMB,        DROP_LASERS,      DROP_GOLD_RING_1,
                                       DROP_GOLD_RING_2, DROP_GOLD_RING_3, DROP_GOLD_RING_4, DROP_NONE,
                                       DROP_1UP,         TRAP_ENEMY_LASERS };
Vec3f sZoContainerTrapLaserPos[6] = {
    { 5.0f, -10.0f, 0.0f },  { 10.0f, 0.0f, 0.0f },  { 5.0f, 10.0f, 0.0f },
    { -5.0f, -10.0f, 0.0f }, { -10.0f, 0.0f, 0.0f }, { -5.0f, 10.0f, 0.0f },
};

void Zoness_ZoContainer_Update(ZoContainer* this) {
    s32 i;
    s32 j;
    Vec3f spB4;
    Vec3f spA8 = { 0.0f, 0.0f, 0.0f };
    Vec3f sp9C;

    if ((this->dmgType != DMG_NONE) && (this->health != 0)) {
        this->dmgType = DMG_NONE;
        this->timer_0C6 = 15;
        this->health -= this->damage;
        AUDIO_PLAY_SFX(NA_SE_EN_DAMAGE_S, this->sfxSource, 4);
    }

    switch (this->state) {
        case 0:
            if (this->health <= 0) {
                this->health = 0;
                this->state++;
            }
            break;

        case 1:
            for (i = 0; i < 6; i++) {
                Zoness_ActorDebris_Spawn(&this->vwork[i], &this->vwork[6 + i], RAND_FLOAT_CENTERED(50.0f),
                                         RAND_FLOAT(10.0f) + 20.0f, RAND_FLOAT_CENTERED(50.0f), 39, this->scale,
                                         RAND_FLOAT(15.0f) + (this->scale * 10.0f), i);
            }
            for (i = 0; i < 10; i++) {
                func_effect_80079618(RAND_FLOAT_CENTERED(50.0f) + this->obj.pos.x,
                                     RAND_FLOAT_CENTERED(50.0f) + this->obj.pos.y,
                                     RAND_FLOAT_CENTERED(50.0f) + this->obj.pos.z, 2.0f);
            }
            for (i = 0; i < 3; i++) {
                func_effect_8007D0E0(this->obj.pos.x + RAND_FLOAT_CENTERED(50.0f),
                                     this->obj.pos.y + RAND_FLOAT_CENTERED(50.0f) + 20.0f,
                                     this->obj.pos.z + RAND_FLOAT_CENTERED(30.0f), 10.0f + 2 * i);
            }
            this->obj.pos.y += 100.0f;

            if (sZoContainerItemDrops[this->iwork[0]] < 1000) {
                this->itemDrop = sZoContainerItemDrops[this->iwork[0]];
                Actor_Despawn(this);
            } else {
                if (sZoContainerItemDrops[this->iwork[0]] == 1000) {
                    for (i = 0, j = 0; i < 10; i++, j++) {
                        if (j > 5) {
                            j = 0;
                        }
                        spB4.x = sZoContainerTrapLaserPos[j].x + this->obj.pos.x;
                        spB4.y = sZoContainerTrapLaserPos[j].y + this->obj.pos.y;
                        spB4.z = sZoContainerTrapLaserPos[j].z + this->obj.pos.z;
                        sp9C.x = RAND_FLOAT_CENTERED(10.0f);
                        sp9C.y = RAND_FLOAT_CENTERED(10.0f);
                        sp9C.z = 50.0f;
                        func_effect_8007EE68(OBJ_EFFECT_ENEMY_LASER_1, &spB4, &spA8, &spA8, &sp9C, 1.0f);
                    }
                }
                this->itemDrop = DROP_NONE;
                Actor_Despawn(this);
            }
            Object_Kill(&this->obj, this->sfxSource);
            Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_OB_BROKEN_BOX);
            break;
    }
}

void Zoness_ZoContainer_PostLimbDraw(s32 limbIndex, Vec3f* rot, void* thisx) {
    Vec3f sp24 = { 0.0f, 0.0f, 0.0f };
    ZoContainer* this = (ZoContainer*) thisx;

    if (this->state != 0) {
        switch (limbIndex) {
            case 1:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[0]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[6]);
                break;
            case 2:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[1]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[7]);
                break;
            case 3:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[2]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[8]);
                break;
            case 4:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[3]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[9]);
                break;
            case 5:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[4]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[10]);
                break;
            case 6:
                Matrix_MultVec3f(gCalcMatrix, &sp24, &this->vwork[5]);
                Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[11]);
                break;
        }
    }
}

void Zoness_ZoContainer_Draw(ZoContainer* this) {
    Vec3f frameTable[20];

    Animation_GetFrameData(&D_ZO_6018550, 0, frameTable);
    Animation_DrawSkeleton(3, D_ZO_601863C, frameTable, NULL, Zoness_ZoContainer_PostLimbDraw, this, gCalcMatrix);
}

void Zoness_ZoRadarBuoy_Update(ZoRadarBuoy* this) {
    s32 pad;
    f32 sp40;
    f32 sp3C;
    s32 sp38;
    s32 i;
    ZoSearchLight* searchLight;

    switch (this->state) {
        case 0:
            for (i = 0, searchLight = &gActors[0]; i < ARRAY_COUNT(gActors); i++, searchLight++) {
                if (searchLight->obj.status == OBJ_FREE) {
                    Actor_Initialize(searchLight);
                    searchLight->obj.status = OBJ_INIT;
                    searchLight->obj.id = OBJ_ACTOR_ZO_SEARCHLIGHT;
                    searchLight->obj.pos.x = this->obj.pos.x;
                    searchLight->obj.pos.y = this->obj.pos.y;
                    searchLight->obj.pos.z = this->obj.pos.z + 30.0f;
                    searchLight->fwork[0] = 230.0f;
                    searchLight->fwork[1] = 0.8f;
                    searchLight->fwork[2] = 1.0f;
                    searchLight->fwork[3] = 1.0f;
                    searchLight->iwork[0] = this->index + 1;
                    Object_SetInfo(&searchLight->info, searchLight->obj.id);
                    this->iwork[0] = i;
                    break;
                }
            }
            if (i >= ARRAY_COUNT(gActors)) {
                searchLight->obj.status = OBJ_FREE;
            }

            this->health = 10;
            this->state++;
            break;

        case 1:
            if ((this->dmgType != DMG_NONE) && (this->health != 0)) {
                this->dmgType = DMG_NONE;
                this->timer_0C6 = 15;
                this->health -= this->damage;
                if (this->health <= 0) {
                    if (!gMissedZoSearchlight) {
                        BonusText_Display(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + 200.0f, 2);
                        gHitCount += 2;
                    }
                    this->health = this->itemDrop = 0;
                    Actor_Despawn(this);
                    this->state++;
                }
            }
            break;

        case 2:
            this->timer_0C2 = 30000;
            searchLight = &gActors[this->iwork[0]];

            searchLight->iwork[0] = 777;
            Effect_Effect391_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 5.0f, 0.7f);
            func_effect_8007D0E0(this->obj.pos.x, this->obj.pos.y + 50.0f, this->obj.pos.z, 5.0f);
            Object_Kill(&this->obj, this->sfxSource);
            Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_WT_EXPLOSION_S);
            break;
    }

    if ((this->state < 2) &&
        (Play_CheckDynaFloorCollision(&sp40, &sp38, this->obj.pos.x, this->obj.pos.y - 60.0f, this->obj.pos.z) != 0)) {
        this->gravity = 0.0f;
        sp3C = 10.0f;
        if (Math_SmoothStepToF(&this->obj.pos.y, sp40 - 20.0f, 0.1f, 5.0f, 0) >= 0.0f) {
            sp3C = 350.0f;
        }
        Math_SmoothStepToAngle(&this->obj.rot.z, sp3C, 0.1f, 1.0f, 0);
        searchLight = &gActors[this->iwork[0]];
        Math_SmoothStepToAngle(&searchLight->obj.rot.z, sp3C, 0.1f, 1.0f, 0);
        searchLight->obj.pos.y = this->obj.pos.y;
    }
}

void Zoness_ZoRadarBuoy_Draw(ZoRadarBuoy* this) {
    gSPDisplayList(gMasterDisp++, aZoRadarBuoyDL);
}

Vec3f D_i3_801BF8AC = { 230.0f, -50.0f, 0.0f };
Vec3f D_i3_801BF8B8 = { 230.0f, -250.0f, 0.0f };

void Zoness_ZoSupplyCrane_Init(ZoSupplyCrane* this) {
    s32 i;
    s32 sp38;
    Vec3f dest;
    ZoContainer* container;

    this->scale = -1.0f;

    if (this->state != 3) {
        this->iwork[4] = fabsf(Math_ModF(this->obj.rot.z, 10.0f));
        sp38 = fabsf(this->obj.rot.z / 10.0f);
    } else {
        sp38 = this->iwork[0];
        this->state = 0;
    }

    this->fwork[5] = this->obj.rot.x;
    this->obj.rot.x = 0.0f;
    this->obj.rot.z = 0.0f;

    if (this->iwork[4] == 2) {
        this->fwork[0] = -20.0f;
        this->fwork[3] = this->obj.pos.y * 0.5f * -1.0f;
    } else {
        this->fwork[0] = 30.0f;
    }

    Matrix_RotateZ(gCalcMatrix, this->fwork[0] * M_DTOR, MTXF_NEW);
    Matrix_MultVec3f(gCalcMatrix, &D_i3_801BF8AC, &dest);

    this->fwork[1] = dest.x;
    this->fwork[2] = this->fwork[3] + dest.y;

    Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
    Matrix_MultVec3f(gCalcMatrix, &D_i3_801BF8B8, &dest);

    for (i = 0, container = &gActors[0]; i < ARRAY_COUNT(gActors); i++, container++) {
        if (container->obj.status == OBJ_FREE) {
            Actor_Initialize(container);
            container->obj.status = OBJ_INIT;
            container->obj.id = OBJ_ACTOR_ZO_CONTAINER;
            container->obj.pos.x = this->obj.pos.x + dest.x;
            container->obj.pos.y = this->obj.pos.y + dest.y + this->fwork[2];
            container->obj.pos.z = this->obj.pos.z + dest.z + this->fwork[0];
            container->obj.rot.y = this->obj.rot.y;
            container->iwork[0] = sp38;
            container->iwork[3] = 777;
            Object_SetInfo(&container->info, container->obj.id);
            this->iwork[3] = i;
            break;
        }
    }
    if (i >= ARRAY_COUNT(gActors)) {
        container->obj.status = OBJ_FREE;
    }
}

void Zoness_ZoSupplyCrane_Update(ZoSupplyCrane* this) {
    Vec3f sp34;
    Actor* otherActor;

    if ((this->fwork[0] == 30.0f) && (fabsf(this->obj.pos.z - gPlayer[0].trueZpos) < 2500.0f)) {
        Math_SmoothStepToAngle(&this->fwork[6], 10.0f, 0.1f, 1.0f, 0.01f);
        Math_SmoothStepToAngle(&this->obj.rot.y, this->fwork[5], 1.0f, this->fwork[6], 0.01f);
        if (this->fwork[5] != this->obj.rot.y) {
            AUDIO_PLAY_SFX(NA_SE_OB_CRAME_MOTOR, this->sfxSource, 4);
        }
        if (1) {}
    }
    Matrix_RotateZ(gCalcMatrix, this->fwork[0] * M_DTOR, MTXF_NEW);
    Matrix_MultVec3f(gCalcMatrix, &D_i3_801BF8AC, &sp34);

    this->fwork[1] = sp34.x;
    this->fwork[2] = this->fwork[3] + sp34.y;

    otherActor = &gActors[this->iwork[3]];

    switch (this->state) {
        case 0:
            Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
            Matrix_MultVec3f(gCalcMatrix, &D_i3_801BF8B8, &sp34);

            if ((otherActor->obj.status != OBJ_FREE) && (otherActor->obj.id == OBJ_ACTOR_ZO_CONTAINER)) {
                otherActor->obj.pos.x = this->obj.pos.x + sp34.x;
                otherActor->obj.pos.y = this->obj.pos.y + sp34.y + this->fwork[2];
                otherActor->obj.pos.z = this->obj.pos.z + sp34.z;
            } else {
                this->state = 1;
            }

            switch (this->iwork[4]) {
                case 1:
                    if ((this->fwork[5] == this->obj.rot.y) &&
                        (fabsf(this->obj.pos.z - gPlayer[0].trueZpos) < 1000.0f)) {
                        if (otherActor->obj.id == OBJ_ACTOR_ZO_CONTAINER) {
                            otherActor->gravity = 1.0f;
                        }
                        this->state = 1;
                    }
                    break;

                case 2:
                    Math_SmoothStepToF(&this->fwork[3], 0.0f, 1.0f, 5.0f, 0.01f);
                    if (this->fwork[3] == 0.0f) {
                        Math_SmoothStepToF(&this->fwork[0], 30.0f, 1.0f, 5.0f, 0.01f);
                        if (this->fwork[0] == 30.0f) {
                            this->iwork[4] = 0;
                        }
                    }
                    break;
            }
            break;

        case 1:
            this->fwork[4] += 10.0f;
            this->fwork[4] = Math_ModF(this->fwork[4], 360.0f);
            break;
    }

    if (this->fwork[0] >= 30.0f) {
        this->fwork[0] = 30.0f;
    }
    if (this->fwork[0] <= -20.0f) {
        this->fwork[0] = -20.0f;
    }
    if (this->fwork[3] >= 0) {
        this->fwork[3] = 0.0f;
    }
    if (this->fwork[3] <= -450.0f) {
        this->fwork[3] = -450.0f;
    }
}

void Zoness_ZoSupplyCrane_Draw(ZoSupplyCrane* this) {
    f32 var_fv1;
    s32 i;
    s32 var_s1;

    Matrix_Push(&gGfxMatrix);
    Matrix_RotateZ(gGfxMatrix, this->fwork[0] * M_DTOR, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_ZO_601A340);
    Matrix_Pop(&gGfxMatrix);
    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, 0.0f, -320.0f, 0.0f, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, 1.0f, 1.3, 1.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_ZO_6013330);
    Matrix_Pop(&gGfxMatrix);
    Matrix_Push(&gGfxMatrix);
    Matrix_RotateZ(gGfxMatrix, M_PI / 2, MTXF_APPLY);
    Matrix_Translate(gGfxMatrix, -110.0f, 0.0f, 0.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_ZO_601D680);
    Matrix_Pop(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, this->fwork[1], this->fwork[2], 0.0f, MTXF_APPLY);
    Matrix_RotateY(gGfxMatrix, this->fwork[4] * M_DTOR, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, 0.75f, 0.75f, 0.75f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_ZO_601C590);
    RCP_SetupDL_57(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
    Matrix_RotateY(gGfxMatrix, gGameFrameCount * M_DTOR, MTXF_APPLY);

    var_fv1 = (fabsf(this->fwork[3]) * 1.3f) + 50.0f;
    for (var_s1 = 0; var_fv1 > 0.0f; var_s1++) {
        var_fv1 -= 9.3f;
    }

    if (var_s1 > 50) {
        var_s1 = 50;
    }
    if (var_s1 <= 0) {
        var_s1 = 1;
    }

    for (i = 0; i < var_s1; i++) {
        Matrix_Translate(gGfxMatrix, 0.0f, 9.3f, 0.0f, MTXF_APPLY);
        Matrix_RotateY(gGfxMatrix, M_PI / 2, MTXF_APPLY);
        Matrix_Push(&gGfxMatrix);
        Matrix_Scale(gGfxMatrix, 0.5f, 0.5f, 0.5f, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, D_ZO_6018660);
        Matrix_Pop(&gGfxMatrix);
    }
}

f32 D_i3_801BF8C4[2] = { 46.0f, 314.0f };
f32 D_i3_801BF8CC[2] = { 23.0f, 337.0f };

void Zoness_ZoSearchLight_Update(ZoSearchLight* this) {
    this->timer_0C2 = 30000;

    switch (this->state) {
        case 0:
            this->fwork[5] = D_i3_801BF8CC[gGameFrameCount % 2U];
            if (gMissedZoSearchlight) {
                this->fwork[5] = D_i3_801BF8C4[gGameFrameCount % 2U];
                this->iwork[1] = 1;
            }
            this->state++;
            break;

        case 1:
            Math_SmoothStepToF(&this->fwork[6], 10.0f, 0.1f, 1.0f, 0.001f);
            if (this->iwork[0] == 0) {
                Math_SmoothStepToAngle(&this->obj.rot.z, this->fwork[5], 0.1f, this->fwork[6], 0.0001f);
            } else {
                Math_SmoothStepToAngle(&this->fwork[4], this->fwork[5], 0.1f, this->fwork[6], 0.0001f);
            }

            if (gMissedZoSearchlight && (this->iwork[1] == 0)) {
                if (this->fwork[5] < 300.0f) {
                    this->fwork[5] = D_i3_801BF8C4[0];
                } else {
                    this->fwork[5] = D_i3_801BF8C4[1];
                }
                this->iwork[1] = 1;
            }

            if (this->timer_0BC == 0) {
                this->timer_0BC = 45;
                this->fwork[5] = 360.0f - this->fwork[5];
                this->fwork[6] = 0.0f;
            }

            if (this->iwork[0] == 777) {
                this->state++;
            }
            break;

        case 2:
            Math_SmoothStepToF(&this->fwork[1], 0.0f, 0.2f, 1.0f, 0.01f);
            if (this->fwork[1] < 0.6f) {
                Math_SmoothStepToF(&this->fwork[2], 0.0f, 0.5f, 5.0f, 0.01f);
                if (this->fwork[2] == 0.0f) {
                    Object_Kill(&this->obj, this->sfxSource);
                }
            }
            break;
    }
    Zoness_8018FF50(this);
    this->obj.rot.x = 0.0f;
}

void Zoness_ZoSearchLight_Draw(ZoSearchLight* this) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_72);

    if (this->iwork[0] != 0) {
        Matrix_Translate(gGfxMatrix, 0.0f, this->fwork[0], 0.0f, MTXF_APPLY);
        Matrix_RotateZ(gGfxMatrix, (this->fwork[4] + this->obj.rot.z) * M_DTOR, MTXF_APPLY);
        Matrix_Scale(gGfxMatrix, this->fwork[1], this->fwork[2], this->fwork[3], MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        if (gMissedZoSearchlight) {
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 191, 43, 255);
            gDPSetEnvColor(gMasterDisp++, 255, 0, 0, 255);
        } else {
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
            gDPSetEnvColor(gMasterDisp++, 255, 255, 127, 255);
        }
    } else if (gMissedZoSearchlight) {
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 191, 43, 50);
        gDPSetEnvColor(gMasterDisp++, 255, 0, 0, 255);
    } else {
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 50);
        gDPSetEnvColor(gMasterDisp++, 255, 255, 127, 255);
    }
    gSPDisplayList(gMasterDisp++, D_ZO_60181E0);
}

void Zoness_ZoBarrier_Init(ZoBarrier* this) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gActors); i++) {
        if (gActors[i].obj.status == OBJ_FREE) {
            Actor_Initialize(&gActors[i]);
            gActors[i].obj.status = OBJ_ACTIVE;
            gActors[i].obj.id = OBJ_ACTOR_ZO_BARRIER;
            gActors[i].obj.pos.x = this->obj.pos.x;
            gActors[i].obj.pos.y = this->obj.pos.y - 60.0f;
            gActors[i].fwork[2] = gActors[i].obj.pos.y;
            gActors[i].obj.pos.z = this->obj.pos.z;

            gActors[i].state = 1;

            this->work_046 = i + 1;
            Object_SetInfo(&gActors[i].info, gActors[i].obj.id);
            gActors[i].info.hitbox = SEGMENTED_TO_VIRTUAL(aZoBarrierHitbox2);
            break;
        }
    }
}

void Zoness_ZoBarrier_Update(ZoBarrier* this) {
    Actor* otherActor;

    if (this->state == 0) {
        if (this->dmgType != DMG_NONE) {
            this->dmgType = DMG_NONE;
            if (this->dmgPart < 2) {
                AUDIO_PLAY_SFX(NA_SE_OB_WT_WHEEL_ROLL, this->sfxSource, 4);
                if ((this->obj.pos.y + 268.0f) < this->hitPos.y) {
                    this->fwork[1] = 20.0f;
                } else {
                    this->fwork[1] = -20.0f;
                }
                AUDIO_PLAY_SFX(NA_SE_OB_WALL_UP, this->sfxSource, 4);
            } else {
                AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
            }
        }

        if (this->work_046 != 0) {
            otherActor = &gActors[this->work_046 - 1];
            otherActor->obj.pos.y += this->fwork[1] * 0.3f;
            if (otherActor->obj.pos.y > this->fwork[2] + 370.0f) {
                otherActor->obj.pos.y = this->fwork[2] + 370.0f;
            }
        }

        this->fwork[0] += this->fwork[1];
        Math_SmoothStepToF(&this->fwork[1], 0.0f, 1.0f, 1.0f, 0.0f);

        if (this->fwork[1] == 0.0f) {
            Audio_KillSfxBySource(this->sfxSource);
        }
    }
}

bool Zoness_ZoBarrier_OverrideLimbDraw(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    ZoBarrier* this = (ZoBarrier*) thisx;

    switch (this->state) {
        case 0:
            if (limbIndex == 1) {
                pos->y -= 60.0f;
                rot->z -= this->fwork[0];
            }
            if (limbIndex == 3) {
                *dList = NULL;
            }
            break;

        case 1:
            if (limbIndex != 3) {
                *dList = NULL;
            }
            break;
    }
    return false;
}

void Zoness_ZoBarrier_Draw(ZoBarrier* this) {
    Vec3f frameTable[10];

    Animation_GetFrameData(&D_ZO_601FBC4, 0, frameTable);
    Animation_DrawSkeleton(1, aZoBarrierSkel, frameTable, Zoness_ZoBarrier_OverrideLimbDraw, NULL, this,
                           &gIdentityMatrix);
}

void Zoness_LevelStart(Player* player) {
    s32 buttonSave;

    player->bobPhase += 10.0f;
    player->yBob = -SIN_DEG(player->bobPhase) * 0.5f;
    player->rockPhase += 3.0f;
    player->rockAngle = SIN_DEG(player->rockPhase) * 1.5f;
    switch (player->csState) {
        case 0:
            gCsFrameCount = 0;
            player->pos.z += 10000.0f;
            player->cam.eye.x = gCsCamEyeX = player->pos.x;
            player->cam.eye.y = gCsCamEyeY = (player->pos.y * player->unk_148) + 50.0f;
            player->cam.eye.z = gCsCamEyeZ = 400.0f;
            player->cam.at.x = gCsCamAtX = player->pos.x;
            player->cam.at.y = gCsCamAtY = (player->pos.y * player->unk_148) + 20.0f - 230.0f;
            player->cam.at.z = gCsCamAtZ = 0.0f;
            player->csState = 1;
            /* fallthrough */
        case 1:
            Math_SmoothStepToF(&player->pos.z, 0.0f, 0.1f, 48.0f, 0);
            Math_SmoothStepToF(&player->cam.at.y, (player->pos.y * player->unk_148) + 20.0f, 0.1f, 1.0f, 0.0f);
            if (gCsFrameCount >= 230) {
                Math_SmoothStepToF(&player->cam.at.z, player->trueZpos, 0.2f, 20000.0f, 0.0f);
            }

            buttonSave = gControllerHold[gMainController].button;
            gControllerHold[gMainController].button = gBoostButton[gMainController];

            player->csTimer = 60;
            player->boostMeter = 1.0f;
            Player_ArwingBoost(player);

            if (gCsFrameCount > 195) {
                D_ctx_801779A8[0] = 50.0f;
            } else {
                D_ctx_801779A8[0] = 0.0f;
            }

            gControllerHold[gMainController].button = buttonSave;

            if (gCsFrameCount >= 270) {
                AUDIO_PLAY_BGM(NA_BGM_STAGE_ZO);
                gLevelStartStatusScreenTimer = 80;
                player->state = PLAYERSTATE_ACTIVE;
                player->csState = 0;
                player->csTimer = 0;
                player->csEventTimer = 0;
                gLoadLevelObjects = 1;
            }
            break;
    }
    gPathTexScroll += 40.0f;
}

void Zoness_LevelComplete(Player* player) {
    f32 zRot;
    f32 yRot;
    f32 dx;
    f32 dz;
    s32 i;
    Vec3f src;
    Vec3f dest;
    Boss* boss = &gBosses[0];

    switch (player->csState) {
        case 0:
        case 10:
            gCsFrameCount = 0;
            player->aerobaticPitch = 0.0f;
            player->camRoll = 0.0f;
            player->baseSpeed = 40.0f;
            player->draw = true;
            player->arwing.upperRightFlapYrot = player->arwing.upperLeftFlapYrot = player->arwing.bottomRightFlapYrot =
                player->arwing.bottomLeftFlapYrot = player->zRotBarrelRoll = player->zRotBank = player->boostSpeed =
                    0.0f;

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

            D_ctx_80177A48[0] = 0.05f;

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
            Math_SmoothStepToF(&gCsCamEyeY, 250.0f, 1.0f, 20.0f, 0.0f);
            Math_SmoothStepToF(&gCsCamAtY, 240.0f, 1.0f, 20.0f, 0.0f);

            dx = player->pos.x - boss->obj.pos.x;
            dz = (player->pos.z - boss->obj.pos.z) * 0.05f;
            yRot = Math_RadToDeg(-Math_Atan2F(dx, dz));
            zRot = Math_SmoothStepToAngle(&player->rot.y, yRot, 0.5f, 2.0f, 0.0001f) * 30.0f;

            if (gCsFrameCount >= 14) {
                Math_SmoothStepToAngle(&player->rot.z, zRot, 0.1f, 5.0f, 0.0001f);
            } else if (zRot < 0.0f) {
                player->rot.z -= 30.0f;
            } else {
                player->rot.z += 30.0f;
            }

            if (gCsFrameCount >= 140) {
                gFillScreenAlphaTarget = 255;
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
            }
            if (gCsFrameCount == 160) {
                player->csState++;
                Play_ClearObjectData();
                Audio_StopPlayerNoise(0);
                Audio_KillSfxBySource(player->sfxSource);
                gFillScreenAlpha = 250;
                player->csTimer = 20;
                player->arwing.drawFace = true;
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
                player->pos.z = -(gPathProgress + 1500.0f);
                player->csState++;
                Audio_StartPlayerNoise(0);
                AUDIO_PLAY_BGM(NA_BGM_COURSE_CLEAR);
                gDrawGround = true;
                Play_ClearObjectData();
                Solar_801A7750();
                D_ctx_80177A48[1] = 0.0f;
                D_ctx_80177A48[2] = 0.0f;

                if (!gMissedZoSearchlight) {
                    D_ctx_80177A48[1] = 330.0f;
                    player->cam.eye.x = 1350.0f;
                    player->cam.at.x = gCsCamAtX = 1450.0f;
                    D_ctx_80177A48[3] = 800.0f;
                    D_ctx_80177A48[4] = -0.15f;
                    D_ctx_80177A48[5] = -250.0f;
                    player->cam.eye.z = player->pos.z + gPathProgress - 1780.0f;
                } else {
                    player->cam.eye.x = -1500.0f;
                    player->cam.at.x = gCsCamAtX = -1500.0f;
                    D_ctx_80177A48[3] = -800.0f;
                    D_ctx_80177A48[4] = 0.2f;
                    D_ctx_80177A48[5] = 250.0f;
                    player->cam.eye.z = player->pos.z + gPathProgress - 2000.0f;
                }
                player->cam.eye.y = 200.0f;
                player->cam.at.y = gCsCamAtY = player->pos.y;
                player->cam.at.z = gCsCamAtZ = player->pos.z + gPathProgress;
                D_ctx_80177A48[0] = 0.0f;
            }
            break;

        case 3:
            gPathTexScroll += 60.0f;
            gFillScreenAlphaTarget = 0;
            gFillScreenAlphaStep = 4;
            D_ctx_80177A48[1] += D_ctx_80177A48[2];

            Matrix_RotateY(gCalcMatrix, D_ctx_80177A48[1] * M_DTOR, MTXF_NEW);
            src.x = 0.0f;
            src.y = 0.0f;
            src.z = D_ctx_80177A48[3];
            Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

            if (gCsFrameCount < 1180) {
                gCsCamEyeX = dest.x;
                gCsCamEyeY = 200.0f + dest.y;
                gCsCamEyeZ = player->pos.z + gPathProgress + dest.z;
                gCsCamAtX = 0.0f;
                gCsCamAtY = player->pos.y;
                gCsCamAtZ = D_ctx_80177A48[5] + (player->pos.z + gPathProgress);
                Math_SmoothStepToF(&D_ctx_80177A48[5], 250.0f, 1.0f, 1.0f, 0.0f);
            } else {
                gCsCamAtX = 0.0f;
                gCsCamAtY = player->pos.y;
                gCsCamAtZ = player->pos.z + gPathProgress;
            }

            if (gCsFrameCount > 1180) {
                player->baseSpeed += 2.0f;
                player->rot.x += 0.1f;
                Math_SmoothStepToF(&D_ctx_80177A48[2], 0.0f, 1.0f, 0.001f, 0);
                player->unk_190 = 2.0f;

                if (!gMissedZoSearchlight) {
                    Math_SmoothStepToF(&D_ctx_80177A48[0], 1.0f, 1.0f, 0.025f, 0.0f);
                }
            } else {
                Math_SmoothStepToF(&D_ctx_80177A48[2], D_ctx_80177A48[4], 1.0f, 0.001f, 0.0f);
                Math_SmoothStepToF(&D_ctx_80177A48[0], 0.05f, 1.0f, 0.00005f, 0.0f);
            }

            if (gCsFrameCount == 1300) {
                Play_ClearObjectData();
            }
            if (gCsFrameCount > 1270) {
                gFillScreenAlphaTarget = 255;
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
                gFillScreenAlphaStep = 8;
                if (gFillScreenAlpha == 255) {
                    Audio_StopPlayerNoise(0);
                    Audio_FadeOutAll(10);
                    player->state = PLAYERSTATE_NEXT;
                    player->csTimer = 0;
                    gFadeoutType = 4;
                    gLeveLClearStatus[LEVEL_ZONESS] = Play_CheckMedalStatus(250) + 1;
                }
            }
            break;
    }

    PRINTF("Demo_Time %d\n");

    switch (gCsFrameCount) {
        case 320:
            if (!gMissedZoSearchlight) {
                gMissionStatus = MISSION_ACCOMPLISHED;
            }
            gLevelClearScreenTimer = 100;
            break;

        case 380:
            Radio_PlayMessage(gMsg_ID_20010, RCID_FOX);
            break;

        case 468:
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

        case 603:
            switch (gTeamShields[TEAM_ID_PEPPY]) {
                case 0:
                    Radio_PlayMessage(gMsg_ID_20344, RCID_ROB64);
                    break;
                case -1:
                    Radio_PlayMessage(gMsg_ID_20338, RCID_ROB64);
                    break;
                default:
                    if (!gMissedZoSearchlight) {
                        func_demo_80048AC0(TEAM_ID_PEPPY);
                    } else {
                        Radio_PlayMessage(gMsg_ID_6100, RCID_PEPPY);
                    }
                    break;
            }
            break;

        case 738:
            switch (gTeamShields[TEAM_ID_FALCO]) {
                case 0:
                    Radio_PlayMessage(gMsg_ID_20343, RCID_ROB64);
                    break;
                case -1:
                    Radio_PlayMessage(gMsg_ID_20337, RCID_ROB64);
                    break;
                default:
                    Radio_PlayMessage(gMsg_ID_6101, RCID_FALCO);
                    break;
            }
            break;

        case 906:
            gShowLevelClearStatusScreen = true;
            break;

        case 1106:
            gShowLevelClearStatusScreen = false;
            break;

        case 1180:
            AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, player->sfxSource, 0);
            player->unk_190 = player->unk_194 = 5.0f;
            break;

        case 1240:
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 50);
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 50);
            break;

        case 1120:
            if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                gActors[0].state = 2;
            }
            break;

        case 1140:
            if (gTeamShields[TEAM_ID_SLIPPY] > 0) {
                gActors[1].state = 2;
            }
            break;

        case 1160:
            if (gTeamShields[TEAM_ID_FALCO] > 0) {
                gActors[2].state = 2;
            }
            break;
    }

    if (gCsFrameCount >= 1180) {
        player->contrailScale += 0.02f;
        if (player->contrailScale > 0.6f) {
            player->contrailScale = 0.6f;
        }
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
    player->trueZpos = player->pos.z += player->vel.z;
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

void Zoness_8019E5F0(ActorCutscene* this) {
    Vec3f src;
    Vec3f dest;

    switch (this->state) {
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
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
            this->rot_0F4.x += 0.1f;

            this->fwork[21] += 0.2f;
            if (this->fwork[21] > 0.6f) {
                this->fwork[21] = 0.6f;
            }
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
