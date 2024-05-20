/*
 * File: fox_ve1.c
 * System: Venom1
 * Description: Level: Venom 1
 */

#include "global.h"
#include "assets/ast_ve1_boss.h"

typedef struct {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E[4];
    /* 0x16 */ s16 unk_16;
} UnkStruct_i1_8019A820; // size = 0x18

typedef struct {
    /* 0x00 */ s16 unk_00;
    /* 0x0A */ s16 unk_02[5];
    /* 0x0C */ Vec3f unk_0C[3];
    /* 0x30 */ Vec3f unk_30[3];
    /* 0x3C */ char pad54[0xC]; // Vec3f?
    /* 0x60 */ f32 unk_60;
    /* 0x64 */ f32 unk_64;
    /* 0x68 */ f32 unk_68;
    /* 0x6C */ f32 unk_6C;
    /* 0x70 */ f32 unk_70;
    /* 0x74 */ f32 unk_74;
    /* 0x78 */ f32 unk_78;
    /* 0x7C */ u16 unk_7C;
} UnkStruct_i1_8019B838; // size = 0x80

typedef struct {
    /* 0x0 */ f32 unk_0;
    /* 0x4 */ s16 unk_4;
    /* 0x6 */ s16 unk_6;
} UnkStruct_i1_8019AE00; // size = 0x8

typedef struct {
    /* 0x0 */ s16 unk_0;
    /* 0x2 */ u8 unk_2;
} UnkStruct_i1_8019ACF8; // size = 0x4

typedef struct {
    /* 0x0 */ s16 limb;
    /* 0x4 */ Gfx* dList;
    /* 0x8 */ s16 index;
    /* 0xA */ s16 flag;
} UnkStruct_i1_8019A748; // size = 0xC

typedef struct {
    /* 0x0 */ Vec3f offset;
    /* 0xC */ f32 size;
} UnkStruct_i1_8019A058; // size = 0x10

typedef struct {
    /* 0x0 */ UnkStruct_i1_8019ACF8* unk_0;
    /* 0x4 */ s32 unk_4;
} UnkStruct_i1_8019AD2C; // size = 0x8

typedef struct {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
    /* 0xC */ f32 unk_C;
} UnkStruct_i1_80199B40; // size = 0x10

UnkStruct_i1_80199B40 D_i1_80199B40[5][5] = {
    {
        { 500.0f, 424.0f, 334.0f, 0.0f },
        { 500.0f, 112.0f, 328.0f, 0.0f },
        { 787.0f, 600.0f, -29.0f, 0.0f },
        { 800.0f, 291.0f, -298.0f, 0.0f },
        { 800.0f, 724.0f, -500.0f, 0.0f },
    },
    {
        { 500.0f, 501.0f, 267.0f, 0.0f },
        { 770.0f, 182.0f, -80.0f, 0.0f },
        { 500.0f, 710.0f, -497.0f, 0.0f },
        { 800.0f, 90.0f, -625.0f, 0.0f },
        { 800.0f, 422.0f, -1100.0f, 0.0f },
    },
    {
        { 500.0f, 424.0f, 334.0f, 0.0f },
        { 500.0f, 112.0f, 328.0f, 0.0f },
        { 787.0f, 600.0f, -29.0f, 0.0f },
        { 800.0f, 291.0f, -298.0f, 0.0f },
        { 800.0f, 724.0f, -500.0f, 0.0f },
    },
    {
        { 500.0f, 501.0f, 267.0f, 0.0f },
        { 770.0f, 182.0f, -80.0f, 0.0f },
        { 500.0f, 710.0f, -497.0f, 0.0f },
        { 800.0f, 90.0f, -625.0f, 0.0f },
        { 800.0f, 422.0f, -1100.0f, 0.0f },
    },
    {
        { 500.0f, 424.0f, 334.0f, 0.0f },
        { 500.0f, 112.0f, 328.0f, 0.0f },
        { 787.0f, 600.0f, -29.0f, 0.0f },
        { 800.0f, 291.0f, -298.0f, 0.0f },
        { 800.0f, 724.0f, -500.0f, 0.0f },
    },
};
UnkStruct_i1_80199B40 D_i1_80199CD0[5][5] = {
    {
        { -770.0f, 96.0f, 916.0f, 0.0f },
        { -500.0f, 478.0f, 394.0f, 0.0f },
        { -500.0f, 78.0f, -12.0f, 0.0f },
        { -800.0f, 364.0f, -464.0f, 0.0f },
        { -870.0f, 708.0f, -600.0f, 0.0f },
    },
    {
        { -500.0f, 792.0f, 701.0f, 0.0f },
        { -770.0f, 509.0f, 659.0f, 0.0f },
        { -500.0f, 416.0f, -32.0f, 0.0f },
        { -800.0f, 681.0f, -700.0f, 0.0f },
        { -800.0f, 121.0f, -485.0f, 0.0f },
    },
    {
        { -770.0f, 96.0f, 916.0f, 0.0f },
        { -500.0f, 478.0f, 394.0f, 0.0f },
        { -500.0f, 78.0f, -12.0f, 0.0f },
        { -800.0f, 364.0f, -464.0f, 0.0f },
        { -870.0f, 708.0f, -600.0f, 0.0f },
    },
    {
        { -500.0f, 792.0f, 701.0f, 0.0f },
        { -770.0f, 509.0f, 659.0f, 0.0f },
        { -500.0f, 416.0f, -32.0f, 0.0f },
        { -800.0f, 681.0f, -700.0f, 0.0f },
        { -800.0f, 121.0f, -485.0f, 0.0f },
    },
    {
        { -770.0f, 96.0f, 916.0f, 0.0f },
        { -500.0f, 478.0f, 394.0f, 0.0f },
        { -500.0f, 78.0f, -12.0f, 0.0f },
        { -800.0f, 364.0f, -464.0f, 0.0f },
        { -870.0f, 708.0f, -600.0f, 0.0f },
    },
};
s16 D_i1_80199E60[5] = { 1, 2, 2, 2, 3 };
UnkStruct_i1_80199B40 D_i1_80199E6C[5][5] = {
    {
        { 200.0f, -197.0f, 0.0f, 0.0f },
        { -200.0f, -197.0f, 175.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 0.0f },
    },
    {
        { 28.0f, -197.0f, 0.0f, 0.0f },
        { 263.0f, -197.0f, 305.0f, 0.0f },
        { -277.0f, -197.0f, 681.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 0.0f },
    },
    {
        { 145.0f, -197.0f, 0.0f, 0.0f },
        { -300.0f, -197.0f, 129.0f, 0.0f },
        { 145.0f, -197.0f, 480.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 0.0f },
    },
    {
        { 263.0f, -197.0f, 0.0f, 0.0f },
        { -183.0f, -197.0f, 23.0f, 0.0f },
        { -18.0f, -197.0f, 376.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 0.0f },
    },
    {
        { 28.0f, -197.0f, 0.0f, 0.0f },
        { 263.0f, -197.0f, 329.0f, 0.0f },
        { -324.0f, -197.0f, 376.0f, 0.0f },
        { 51.0f, -197.0f, 611.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 0.0f },
    },
};

s16 D_i1_8019B7F0[33];
UnkStruct_i1_8019B838 D_i1_8019B838[17];
s32 D_i1_8019C0B8;
s32 D_i1_8019C0BC;
s32 D_i1_8019C0C0;

const char D_i1_8019B2B0[] = "--アタックオフ!!\n"; //--Attack off!!
const char D_i1_8019B2C4[] = "--レベルアップ!!\n"; //--Level Up!
const char D_i1_8019B2D8[] = "wk_f00=<%10.3f>\n";

f32 Venom1_801920F0(f32* arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32* arg5) {
    f32 temp;

    *arg5 = arg1 - *arg0;

    if (*arg5 > 180.0f) {
        do {
            *arg5 -= 360.0f;
        } while (*arg5 > 180.0f);
    } else if (*arg5 < -180.0f) {
        do {
            *arg5 += 360.0f;
        } while (*arg5 < -180.0f);
    }

    temp = *arg5;

    if (temp != 0.0f) {
        temp *= arg2;

        if ((arg4 <= temp) || ((temp <= -arg4))) {
            if (arg3 < temp) {
                temp = arg3;
            } else if (-arg3 > temp) {
                temp = -arg3;
            }
            *arg0 += temp;
        } else {
            if (temp < arg4) {
                temp = arg4;
                *arg0 += arg4;

                if (arg1 < *arg0) {
                    *arg0 = arg1;
                }
            } else if (-arg4 < temp) {
                temp = -arg4;
                *arg0 += -arg4;

                if (*arg0 < arg1) {
                    *arg0 = arg1;
                }
            }
        }
    }

    if (*arg0 >= 360.0f) {
        *arg0 = *arg0 - 360.0f;
    } else if (*arg0 < 0.0f) {
        *arg0 = *arg0 + 360.0f;
    }

    return temp;
}

void Venom1_BossTrigger1_Update(Ve1BossTrigger1* this) {
    Boss* boss = &gBosses[0];
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gBosses); i++, boss++) {
        if ((boss->obj.status != OBJ_FREE) && (boss->obj.id == OBJ_BOSS_VE1)) {
            if (boss->obj.pos.z <= this->obj.pos.z) {
                D_i1_8019C0B8 = (s32) this->obj.rot.x + 1;
                this->obj.status = OBJ_FREE;
            }
            break;
        }
    }
}

void Venom1_BossTrigger2_Update(Ve1BossTrigger2* this) {
    Boss* boss = &gBosses[0];
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gBosses); i++, boss++) {
        if ((boss->obj.status != OBJ_FREE) && (boss->obj.id == OBJ_BOSS_VE1)) {
            if (boss->obj.pos.z <= this->obj.pos.z) {
                D_i1_8019C0B8 = 0;
                this->obj.status = OBJ_FREE;
            }
            break;
        }
    }
}

void Venom1_BossTrigger3_Update(Ve1BossTrigger3* this) {
    Boss* boss = &gBosses[0];
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gBosses); i++, boss++) {
        if ((boss->obj.status != OBJ_FREE) && (boss->obj.id == OBJ_BOSS_VE1)) {
            if (boss->obj.pos.z <= this->obj.pos.z) {
                D_i1_8019C0BC = (s32) this->obj.rot.x + 1;
                this->obj.status = OBJ_FREE;
            }
            break;
        }
    }
}

void Venom1_BossTrigger4_Update(Ve1BossTrigger4* this) {
    Boss* boss = &gBosses[0];
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gBosses); i++, boss++) {
        if ((boss->obj.status != OBJ_FREE) && (boss->obj.id == OBJ_BOSS_VE1)) {
            if (boss->obj.pos.z <= this->obj.pos.z) {
                D_i1_8019C0C0 = 1;
                this->obj.status = OBJ_FREE;
            }
            break;
        }
    }
}

void Venom1_801924A8(Scenery* scenery) {
    switch (scenery->state) {
        case 0:
            if (gPlayer[0].pos.z < scenery->obj.pos.z) {
                gDrawBackdrop = 0;
                gDrawGround = false;

                scenery->state++;
            }

        case 1:
            break;
    }
}

void Venom1_8019250C(Actor* actor) {
}

void Venom1_80192518(Actor* actor) {
    Scenery* scenery;
    f32 var_ft4;
    f32 var_ft5;
    s32 i;
    Vec3f src;
    Vec3f dest;
    f32 temp_fv1_2;
    Effect* effect;

    if (actor->dmgType == DMG_BEAM) {
        actor->dmgType = DMG_NONE;
        func_effect_8007A6F0(&actor->obj.pos, NA_SE_EN_REFLECT);
    }

    if ((actor->state == 1) || (actor->state == 2) || (actor->state == 3)) {
        Matrix_RotateY(gCalcMatrix, actor->obj.rot.y * M_DTOR, MTXF_NEW);
        Matrix_RotateX(gCalcMatrix, actor->obj.rot.x * M_DTOR, MTXF_APPLY);
        Matrix_RotateZ(gCalcMatrix, actor->obj.rot.z * M_DTOR, MTXF_APPLY);
    }

    switch (actor->state) {
        case 0:
        case 4:
            break;

        case 1:
            var_ft5 = 450.0f;
            var_ft4 = 0.0f;

            scenery = &gScenery[0];

            for (i = 0; i < ARRAY_COUNT(gScenery); i++, scenery++) {
                if ((scenery->obj.id == OBJ_SCENERY_128) || (scenery->obj.id == OBJ_SCENERY_129) ||
                    (scenery->obj.id == OBJ_SCENERY_130)) {
                    if (((actor->obj.pos.z + 1100.0f - scenery->obj.pos.z) < 2200.0f) &&
                        ((actor->obj.pos.z + 1100.0f - scenery->obj.pos.z) > 0.0f)) {
                        switch (scenery->obj.id) {
                            case OBJ_SCENERY_128:
                            case OBJ_SCENERY_130:
                                break;

                            case OBJ_SCENERY_129:
                                var_ft5 = 600.0f;
                                break;
                        }

                        var_ft4 = scenery->obj.pos.x;
                        break;
                    }
                }
            }
            actor->fwork[0] = 0.0f;

            if ((actor->obj.pos.x + var_ft4) < 0.0f) {
                actor->fwork[1] = 896.0f - (var_ft4 - var_ft5 - actor->obj.pos.x);
                actor->obj.pos.x = var_ft4 - var_ft5;

            } else {
                actor->fwork[1] = 896.0f + (var_ft4 + var_ft5 - actor->obj.pos.x);
                actor->obj.pos.x = var_ft4 + var_ft5;
            }

            actor->timer_0BC = actor->iwork[2];
            AUDIO_PLAY_SFX(NA_SE_OB_POLE_MOVE, actor->sfxSource, 0);
            actor->state = 2;

        case 2:
            if (actor->timer_0BC == 0) {
                src.x = temp_fv1_2 = Math_SmoothStepToF(&actor->fwork[0], actor->fwork[1], 0.7f, 80.0f, 0.01f);
                src.y = 0.0f;
                src.z = 0.0f;

                Matrix_MultVec3f(gCalcMatrix, &src, &dest);

                actor->obj.pos.x += dest.x;
                actor->obj.pos.y += dest.y;
                actor->obj.pos.z += dest.z;

                effect = func_effect_8007783C(OBJ_EFFECT_394);

                if (effect != NULL) {
                    effect->unk_7A = 11;
                    effect->unk_78 = effect->unk_7A;
                    effect->obj.status = OBJ_ACTIVE;

                    effect->obj.pos.x = RAND_FLOAT_CENTERED(3.0f) + actor->obj.pos.x;
                    effect->obj.pos.y = RAND_FLOAT_CENTERED(3.0f) + actor->obj.pos.y;
                    effect->obj.pos.z = RAND_FLOAT_CENTERED(3.0f) + actor->obj.pos.z + 80.0f;

                    effect->scale2 = 8.0f;

                    effect->obj.rot.z = RAND_FLOAT(360.0f);

                    effect->vel.x = RAND_FLOAT_CENTERED(5.0f);
                    effect->vel.y = RAND_FLOAT_CENTERED(3.0f) + 10.0f;

                    effect->unk_44 = 100;
                    effect->unk_46 = -5;
                    effect->unk_60.z = 3;

                    if (Rand_ZeroOne() < 0.5f) {
                        effect->unk_60.z = -effect->unk_60.z;
                    }

                    if ((actor->iwork[0] % 2) != 0) {
                        effect->vel.y = -effect->vel.y;
                    }
                }

                if (fabs(temp_fv1_2) <= 5.0) {
                    actor->timer_0BE = 30;
                    actor->state++;
                    actor->fwork[2] = actor->obj.pos.x;
                    actor->fwork[3] = actor->obj.pos.y;
                    actor->fwork[4] = actor->obj.pos.z;
                }
            }
            break;

        case 3:
            src.x = __sinf((((30 - actor->timer_0BE) % 10) / 10.0f) * M_PI * 2) * 5.0f;
            src.y = 0.0f;
            src.z = 0.0f;

            Matrix_MultVec3f(gCalcMatrix, &src, &dest);

            actor->obj.pos.x = actor->fwork[2] + dest.x;
            actor->obj.pos.y = actor->fwork[3] + dest.y;
            actor->obj.pos.z = actor->fwork[4] + dest.z;

            if (actor->timer_0BE == 0) {
                actor->state++;
            }
            break;
    }

    actor->iwork[0]++;
}

void Venom1_80192AA4(Actor* actor) {
    static Vec3f D_i1_80199FFC = { 0.0f, 460.0f, 0.0f };
    Vec3f src;
    Vec3f dest;
    f32 y;

    Matrix_RotateY(gCalcMatrix, actor->obj.rot.y * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, actor->obj.rot.x * M_DTOR, MTXF_APPLY);

    if ((actor->obj.rot.y <= 30.0f) || (actor->obj.rot.y >= 330.0f)) {
        for (D_i1_80199FFC.x = -80.0f; D_i1_80199FFC.x <= 80.0f; D_i1_80199FFC.x += 40.0f) {
            Matrix_MultVec3fNoTranslate(gCalcMatrix, &D_i1_80199FFC, &dest);
        }
    } else {
        src.z = 0.0f;
        src.x = -80.0f;
        if (actor->obj.rot.y > 90.0f) {
            src.x = 80.0f;
        }
        for (y = 0.0f; y <= 450.0f; y += 50.0f) {
            Matrix_RotateY(gCalcMatrix, actor->obj.rot.y * M_DTOR, MTXF_NEW);
            Matrix_RotateX(gCalcMatrix, actor->obj.rot.x * M_DTOR, MTXF_APPLY);
            src.y = y;
            Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);
        }
    }
}

Gfx* D_VE1_8019A008[17] = {
    D_VE1_90150A0, D_VE1_9015BB0, D_VE1_9015900, D_VE1_9000000, D_VE1_9022A20, D_VE1_9021630,
    D_VE1_9015480, D_VE1_90007F0, D_VE1_9014DF0, D_VE1_9022D80, D_VE1_901E350, D_VE1_901F990,
    D_VE1_901F6D0, D_VE1_9021900, D_VE1_901FC40, D_VE1_9021B80, D_VE1_9013880,
};
s16 D_i1_8019A04C[3][2] = { { -2500, 300 }, { -1000, 0 }, { -5000, 0 } };
UnkStruct_i1_8019A058 D_i1_8019A058[33] = {
    { { 56.0f, 35.0f, 5.0f }, 70.0f },    { { 64.0f, -86.0f, 5.0f }, 60.0f },   { { 54.0f, 0.0f, 2.0f }, 50.0f },
    { { 54.0f, 4.0f, -2.0f }, 50.0f },    { { 0.0f, 0.0f, 0.0f }, 0.0f },       { { 56.0f, 35.0f, -5.0f }, 70.0f },
    { { 64.0f, -86.0f, -5.0f }, 60.0f },  { { 54.0f, 0.0f, -2.0f }, 50.0f },    { { 54.0f, 0.0f, 2.0f }, 50.0f },
    { { 0.0f, 0.0f, 0.0f }, 0.0f },       { { 24.0f, 18.0f, 4.0f }, 50.0f },    { { 126.0f, -8.0f, 7.0f }, 80.0f },
    { { 23.0f, 10.0f, 0.0f }, 40.0f },    { { 101.0f, 12.0f, 2.0f }, 50.0f },   { { 56.0f, 0.0f, -3.0f }, 50.0f },
    { { 0.0f, 0.0f, 0.0f }, 0.0f },       { { 24.0f, 18.0f, -4.0f }, 50.0f },   { { 126.0f, -8.0f, -7.0f }, 80.0f },
    { { 23.0f, 10.0f, 0.0f }, 40.0f },    { { 101.0f, 12.0f, -2.0f }, 50.0f },  { { 56.0f, 0.0f, 3.0f }, 50.0f },
    { { 0.0f, 0.0f, 0.0f }, 0.0f },       { { 0.0f, 0.0f, 0.0f }, 0.0f },       { { 74.0f, -3.0f, -6.0f }, 60.0f },
    { { 0.0f, 0.0f, 0.0f }, 0.0f },       { { 74.0f, -3.0f, 6.0f }, 60.0f },    { { 44.0f, 0.0f, 0.0f }, 70.0f },
    { { 108.0f, 0.0f, 0.0f }, 160.0f },   { { 0.0f, 0.0f, 0.0f }, 0.0f },       { { 134.0f, 70.0f, 84.0f }, 70.0f },
    { { 134.0f, -70.0f, 84.0f }, 70.0f }, { { 122.0f, 81.0f, -73.0f }, 80.0f }, { { 122.0f, -81.0f, -73.0f }, 80.0f },
};
UnkStruct_i1_8019A058 D_i1_8019A268[33] = {
    { { 54.0f, -83.0f, 9.0f }, 50.0f }, { { 46.0f, 34.0f, 9.0f }, 60.0f },   { { 48.0f, 0.0f, 9.0f }, 50.0f },
    { { 3.0f, 0.0f, 9.0f }, 30.0f },    { { 70.0f, 0.0f, 6.0f }, 30.0f },    { { 54.0f, -83.0f, -8.0f }, 50.0f },
    { { 46.0f, 34.0f, -8.0f }, 60.0f }, { { 48.0f, 0.0f, -8.0f }, 50.0f },   { { 3.0f, 0.0f, -8.0f }, 30.0f },
    { { 70.0f, 0.0f, -6.0f }, 30.0f },  { { 48.0f, 7.0f, -6.0f }, 50.0f },   { { 156.0f, -3.0f, -6.0f }, 70.0f },
    { { 27.0f, 12.0f, -6.0f }, 40.0f }, { { 100.0f, 18.0f, -6.0f }, 40.0f }, { { 0.0f, 0.0f, -6.0f }, 40.0f },
    { { 80.0f, 2.0f, -6.0f }, 40.0f },  { { 48.0f, 7.0f, 6.0f }, 50.0f },    { { 156.0f, -3.0f, 6.0f }, 70.0f },
    { { 27.0f, 12.0f, 6.0f }, 40.0f },  { { 100.0f, 18.0f, 6.0f }, 50.0f },  { { 0.0f, 0.0f, 6.0f }, 40.0f },
    { { 80.0f, 2.0f, 6.0f }, 40.0f },   { { -4.0f, 6.0f, -6.0f }, 50.0f },   { { 89.0f, -3.0f, -6.0f }, 50.0f },
    { { -4.0f, 6.0f, 6.0f }, 50.0f },   { { 89.0f, -3.0f, 6.0f }, 50.0f },   { { 0.0f, 0.0f, 0.0f }, 50.0f },
    { { 166.0f, 0.0f, 0.0f }, 110.0f }, { { 5.0f, 0.0f, 0.0f }, 60.0f },     { { 115.0f, 0.0f, 0.0f }, 90.0f },
    { { 0.0f, 0.0f, 0.0f }, 0.0f },     { { 0.0f, 0.0f, 0.0f }, 0.0f },      { { 0.0f, 0.0f, 0.0f }, 0.0f },
};
s16 D_i1_8019A478[17][4] = {
    { 1, 0, 2, 0 },   { 2, 2, 1, 0 },   { 3, 3, 2, 0 },   { 4, 5, 2, 0 },   { 5, 7, 1, 0 },   { 6, 8, 2, 0 },
    { 7, 10, 2, 0 },  { 8, 12, 2, 0 },  { 9, 14, 2, 0 },  { 10, 16, 2, 0 }, { 11, 18, 2, 0 }, { 12, 20, 2, 0 },
    { 16, 22, 2, 0 }, { 17, 24, 2, 0 }, { 20, 26, 1, 0 }, { 21, 27, 2, 0 }, { 25, 29, 4, 0 },
};
s16 D_i1_8019A500[33] = {
    0, 0, 1, 2, 2, 3, 3, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13, 14, 15, 15, 16, 16, 16, 16,
};
Vec3f D_i1_8019A544[43] = {
    { 66.0f, -84.0f, 11.0f },  { 64.0f, -10.0f, -11.0f },  { 69.0f, 54.0f, 11.0f },     { 20.0f, 0.0f, -2.0f },
    { 85.0f, 0.0f, 3.0f },     { 11.0f, 0.0f, 30.0f },     { 63.0f, 0.0f, -12.0f },     { 66.0f, -84.0f, -11.0f },
    { 64.0f, -10.0f, -11.0f }, { 69.0f, 54.0f, -11.0f },   { 20.0f, 0.0f, 2.0f },       { 85.0f, 0.0f, -3.0f },
    { 11.0f, 0.0f, -30.0f },   { 63.0f, 0.0f, 12.0f },     { 40.0f, -18.0f, -6.0f },    { 108.0f, 6.0f, -6.0f },
    { 179.0f, -31.0f, -6.0f }, { 24.0f, -1.0f, -6.0f },    { 92.0f, -7.0f, -6.0f },     { 20.0f, -4.0f, -6.0f },
    { 57.0f, -4.0f, -6.0f },   { 40.0f, -18.0f, 6.0f },    { 108.0f, 6.0f, 6.0f },      { 179.0f, -31.0f, 6.0f },
    { 24.0f, -1.0f, 6.0f },    { 92.0f, -7.0f, 6.0f },     { 20.0f, -4.0f, 6.0f },      { 77.0f, -4.0f, 6.0f },
    { 58.0f, 29.0f, -6.0f },   { 41.0f, -33.0f, -6.0f },   { 109.0f, -22.0f, -6.0f },   { 58.0f, 29.0f, 6.0f },
    { 41.0f, -33.0f, 6.0f },   { 109.0f, -22.0f, 6.0f },   { 24.0f, 0.0f, 0.0f },       { 81.0f, 0.0f, -38.0f },
    { 81.0f, 0.0f, 38.0f },    { 205.0f, -21.0f, 0.0f },   { 58.0f, -21.0f, 98.0f },    { 58.0f, -21.0f, -98.0f },
    { 134.0f, 0.0f, -24.0f },  { 104.0f, 106.0f, -24.0f }, { 104.0f, -106.0f, -24.0f },
};
UnkStruct_i1_8019A748 D_i1_8019A748[18] = {
    { 1, D_VE1_90150A0, 0, 0 },   { 2, D_VE1_9015BB0, 1, 0 },   { 3, D_VE1_9015900, 2, 0 },
    { 4, D_VE1_9000000, 3, 0 },   { 5, D_VE1_9022A20, 4, 0 },   { 6, D_VE1_9021630, 5, 0 },
    { 7, D_VE1_9015480, 6, 0 },   { 8, D_VE1_90007F0, 7, 0 },   { 9, D_VE1_9014DF0, 8, 0 },
    { 10, D_VE1_9022D80, 9, 0 },  { 11, D_VE1_901E350, 10, 0 }, { 12, D_VE1_901F990, 11, 0 },
    { 13, D_VE1_9024750, 15, 1 }, { 16, D_VE1_901F6D0, 12, 0 }, { 17, D_VE1_9021900, 13, 0 },
    { 20, D_VE1_901FC40, 14, 0 }, { 21, D_VE1_9021B80, 15, 0 }, { 25, D_VE1_9013880, 16, 0 },
};
UnkStruct_i1_8019A820 D_i1_8019A820[17] = {
    { 1, 50, 0, 3, 1, 2, 5, -1, -1, -1, -1, 1 },      { 2, 60, 3, 2, 0, 2, 5, 0, -1, -1, -1, 1 },
    { 3, 100, 5, 2, 0, 1, 5, 1, -1, -1, -1, 1 },      { 4, 50, 7, 3, 4, 5, 5, -1, -1, -1, -1, 1 },
    { 5, 60, 10, 2, 3, 5, 5, 3, -1, -1, -1, 1 },      { 6, 100, 12, 2, 3, 4, 5, 4, -1, -1, -1, 1 },
    { 7, 40, 14, 3, -1, -1, 5, -1, -1, -1, -1, 1 },   { 8, 50, 17, 2, 6, -1, 5, 6, -1, -1, -1, 1 },
    { 9, 60, 19, 2, 7, -1, 5, 7, -1, -1, -1, 1 },     { 10, 40, 21, 3, -1, -1, 5, -1, -1, -1, -1, 1 },
    { 11, 50, 24, 2, 9, -1, 5, 9, -1, -1, -1, 1 },    { 12, 60, 26, 2, 10, -1, 5, 10, -1, -1, -1, 1 },
    { 16, 100, 28, 3, 8, -1, 5, 8, -1, -1, -1, 1 },   { 17, 100, 31, 3, 11, -1, 5, 11, -1, -1, -1, 1 },
    { 20, 150, 34, 3, -1, -1, 5, -1, -1, -1, -1, 1 }, { 21, 250, 37, 3, -1, -1, 5, 14, 16, 12, 13, 1 },
    { 25, 200, 40, 3, -1, -1, 5, 2, 5, -1, -1, 1 },
};
f32 D_VE1_8019A9B8[199] = {
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
};
Animation* D_i1_8019ACD4[9] = {
    &D_VE1_9018BD0, &D_VE1_901A4B8, &D_VE1_901BDA8, &D_VE1_901DA38, &D_VE1_9024738,
    &D_VE1_9024738, &D_VE1_9018BD0, &D_VE1_9010FC4, NULL,
};
UnkStruct_i1_8019ACF8 D_i1_8019ACF8[2] = { { 0, 1 }, { -1, 0 } };
UnkStruct_i1_8019ACF8 D_i1_8019AD00[4] = { { 1, 0 }, { 2, 1 }, { 3, 0 }, { -1, 0 } };
UnkStruct_i1_8019ACF8 D_i1_8019AD10[3] = { { 4, 0 }, { 5, 0 }, { -1, 0 } };
UnkStruct_i1_8019ACF8 D_i1_8019AD1C[2] = { { 7, 0 }, { -1, 0 } };
UnkStruct_i1_8019ACF8 D_i1_8019AD24[2] = { { 6, 1 }, { -1, 0 } };
UnkStruct_i1_8019AD2C D_i1_8019AD2C[5] = {
    { D_i1_8019ACF8, 0 }, { D_i1_8019AD00, 0 }, { D_i1_8019AD10, 0 }, { D_i1_8019AD24, 0 }, { D_i1_8019AD1C, 0 },
};
s16 D_i1_8019AD54[3] = { 0, 1, -1 };
Vec3f D_i1_8019AD5C = { 162.0f, 50.0f, 0.0f };
u8 D_i1_8019AD68[24] = {
    0, 33, 64, 97, 128, 143, 161, 192, 223, 255, 234, 213, 192, 171, 153, 129, 108, 87, 66, 45, 22, 0, 0, 0,
};
s16 D_i1_8019AD80[16][4] = {
    { 0, 0, 0, 1 }, { 1, 0, 0, 1 }, { 0, 1, 0, 1 }, { 0, 0, 8, 1 }, { 0, 0, 0, 1 }, { 0, 1, 0, 1 },
    { 0, 0, 0, 1 }, { 0, 0, 0, 1 }, { 0, 1, 0, 1 }, { 0, 0, 8, 1 }, { 0, 0, 0, 1 }, { 0, 1, 0, 1 },
    { 0, 0, 0, 1 }, { 1, 0, 0, 1 }, { 0, 1, 0, 1 }, { 0, 0, 8, 1 },
};
UnkStruct_i1_8019AE00 D_i1_8019AE00[4] = {
    { 270.0f, 3, 2 },
    { 90.0f, 2, 3 },
    { 180.0f, 0, 1 },
    { 0.0f, 1, 0 },
};
f32 D_i1_8019AE20[6] = {
    258.0f, 0.0f, 0.0f, 133.0f, 0.0f, 0.0f,
};
Vec3f D_i1_8019AE38 = { 130.0f, 0.0f, 0.0f };

void Venom1_80192CB0(Actor* actor) {
    actor->iwork[0] = actor->obj.rot.x;
    actor->obj.rot.x = 0.0f;
}

void Venom1_80192CD4(Actor* actor) {
    if (actor->dmgType == DMG_BEAM) {
        actor->dmgType = DMG_NONE;
        func_effect_8007A6F0(&actor->obj.pos, NA_SE_EN_REFLECT);
    }

    if (actor->iwork[1] > 0) {
        gControllerRumbleFlags[0] = 1;
        actor->iwork[1]--;
    }

    switch (actor->state) {
        case 1:
            actor->timer_0BC = actor->iwork[0];

        case 2:
            if (actor->timer_0BC <= 0) {
                actor->state++;
            }
            break;

        case 3:
            actor->state++;

        case 4:
            actor->fwork[0] += 0.05f;
            actor->obj.rot.x += actor->fwork[0];

            if (actor->obj.rot.x >= 90.0f) {
                gCameraShake = 12;
                Venom1_80192AA4(actor);
                actor->iwork[1] = 5;
                actor->obj.rot.x = 90.0f;
                AUDIO_PLAY_SFX(NA_SE_OB_POLE_BOUND, actor->sfxSource, 0);
                actor->state++;
            }
            break;

        case 0:
        case 5:
            break;
    }
}

void Venom1_80192E2C(Actor* actor) {
    Matrix_Scale(gGfxMatrix, 1.0f, 0.5f, 1.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_VE1_901DA50);
}

void Venom1_80192EA4(Actor* actor) {
}

void Venom1_80192EB0(Actor* actor) {
    Scenery* scenery;
    Vec3f sp50;
    Vec3f sp44;
    f32 sp40;
    Effect* effect;
    s32 i;
    f32 var_ft4;

    Matrix_RotateY(gCalcMatrix, actor->obj.rot.y * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, actor->obj.rot.x * M_DTOR, MTXF_APPLY);
    Matrix_RotateZ(gCalcMatrix, actor->obj.rot.z * M_DTOR, MTXF_APPLY);

    switch (actor->state) {
        case 0:
        case 4:
            break;
        case 1:
            var_ft4 = 0.0f;
            scenery = gScenery;

            for (i = 0; i < ARRAY_COUNT(gScenery); i++, scenery++) {
                if (((scenery->obj.id == OBJ_SCENERY_128) || (scenery->obj.id == OBJ_SCENERY_129) ||
                     (scenery->obj.id == OBJ_SCENERY_130)) &&
                    ((actor->obj.pos.z + 1100.0f - scenery->obj.pos.z) < 2200.0f) &&
                    ((actor->obj.pos.z + 1100.0f - scenery->obj.pos.z) > 0.0f)) {
                    var_ft4 = scenery->obj.pos.y;
                    break;
                }
            }
            actor->fwork[0] = 0.0f;
            actor->fwork[1] = 1237.0f - (var_ft4 - actor->obj.pos.y);
            actor->obj.pos.y = var_ft4 + 1.0f;
            actor->timer_0BC = actor->iwork[1];
            AUDIO_PLAY_SFX(NA_SE_OB_POLE_MOVE, actor->sfxSource, 0);
            actor->state = 2;

        case 2:
            if (actor->timer_0BC == 0) {
                sp50.y = sp40 = Math_SmoothStepToF(&actor->fwork[0], actor->fwork[1], 0.7f, 80.0f, 0.01f);
                sp50.x = 0.0f;
                sp50.z = 0.0f;

                Matrix_MultVec3f(gCalcMatrix, &sp50, &sp44);
                actor->obj.pos.x += sp44.x;
                actor->obj.pos.y += sp44.y;
                actor->obj.pos.z += sp44.z;
                effect = func_effect_8007783C(OBJ_EFFECT_394);
                if (effect != NULL) {
                    effect->unk_7A = 11;
                    effect->unk_78 = effect->unk_7A;
                    effect->obj.status = OBJ_ACTIVE;
                    effect->obj.pos.x = actor->obj.pos.x + RAND_FLOAT_CENTERED(3.0f);
                    effect->obj.pos.y = actor->obj.pos.y + RAND_FLOAT_CENTERED(3.0f);
                    effect->obj.pos.z = actor->obj.pos.z + RAND_FLOAT_CENTERED(3.0f) + 80.0f;
                    effect->scale2 = 8.0f;
                    effect->obj.rot.z = RAND_FLOAT(360.0f);
                    effect->vel.x = RAND_FLOAT_CENTERED(5.0f);
                    effect->vel.y = 10.0f + RAND_FLOAT_CENTERED(3);
                    effect->unk_44 = 100;
                    effect->unk_46 = -5;
                    effect->unk_60.z = 3.0f;
                    if (Rand_ZeroOne() < 0.5f) {
                        effect->unk_60.z = -effect->unk_60.z;
                    }
                    if ((actor->iwork[0] % 2) != 0) {
                        effect->vel.y = -effect->vel.y;
                    }
                }

                if (fabs(sp40) <= 5.0) {
                    actor->timer_0BE = 30;
                    actor->state++;
                    actor->fwork[2] = actor->obj.pos.x;
                    actor->fwork[3] = actor->obj.pos.y;
                    actor->fwork[4] = actor->obj.pos.z;
                }
            }
            break;
        case 3:
            sp50.x = 0.0f;
            sp50.y = __sinf((((30 - actor->timer_0BE) % 10) / 10.0f) * M_PI * 2) * 5.0f;
            sp50.z = 0.0f;
            Matrix_MultVec3f(gCalcMatrix, &sp50, &sp44);
            actor->obj.pos.x = actor->fwork[2] + sp44.x;
            actor->obj.pos.y = actor->fwork[3] + sp44.y;
            actor->obj.pos.z = actor->fwork[4] + sp44.z;
            if (actor->timer_0BE == 0) {
                actor->state++;
            }
            break;
    }
    if (actor->dmgType == DMG_BEAM) {
        actor->dmgType = DMG_NONE;
        func_effect_8007A6F0(&actor->obj.pos, NA_SE_EN_REFLECT);
    }
    actor->iwork[0]++;
}

void Venom1_801933B4(Actor* actor) {
    actor->scale = -1.0f;
    actor->obj.pos.y += 488.0f;
}

void Venom1_801933DC(Actor* actor) {
    f32* hitboxData;

    if (actor->dmgType == DMG_BEAM) {
        actor->dmgType = DMG_NONE;
        AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, actor->sfxSource, 0);
    }

    if ((actor->animFrame == 38) || (actor->animFrame == 58)) {
        AUDIO_PLAY_SFX(NA_SE_OB_ARM_SWING, actor->sfxSource, 0);
    }
    Animation_GetFrameData(&D_VE1_900D098, actor->animFrame, actor->vwork);

    if (actor->animFrame < (Animation_GetFrameCount(&D_VE1_900D098) - 1)) {
        actor->animFrame++;
    } else {
        actor->animFrame = 0;
    }
    hitboxData = actor->info.hitbox;
    hitboxData[1 + (10 * 0) + 7] = actor->vwork[3].y;
    hitboxData[1 + (10 * 1) + 7] = -actor->vwork[2].y;
}

void Venom1_801934D0(Actor* actor) {
    Matrix_Translate(gGfxMatrix, 0.0f, -488.0f, 0.0f, MTXF_APPLY);
    Animation_DrawSkeleton(0, D_VE1_900D164, actor->vwork, NULL, NULL, actor, &gIdentityMatrix);
}

void Venom1_80193540(Scenery* scenery) {
    if (((gPlayer[0].trueZpos - scenery->obj.pos.z) <= 3500.0f) && ((gGameFrameCount % 4) == 0)) {
        func_effect_8007C120(scenery->obj.pos.x, scenery->obj.pos.y, scenery->obj.pos.z, 0.0f, 0.0f, 0.0f, 0.2f, 10);
    }
}

void Venom1_Boss319_Init(Boss319* this) {
    s32 i;
    s32 var_v0;
    s32 j;

    gGroundClipMode = 1;
    D_i1_8019C0B8 = 0;
    D_i1_8019C0BC = 0;
    D_i1_8019C0C0 = 0;
    gBossActive = true;
    this->drawShadow = true;
    this->fwork[2] = D_i1_8019A04C[this->swork[13]][0];
    this->fwork[14] = D_i1_8019A04C[this->swork[13]][1];
    this->health = 100;
    this->fwork[9] = 1.0f;

    this->swork[22] = this->swork[21] = 0;

    this->fwork[13] = this->fwork[12] = this->fwork[6] = D_i1_8019AE00[this->swork[21]].unk_0;
    this->fwork[17] = this->obj.rot.y;
    this->obj.rot.y = 0.0f;

    for (i = 0; i < ARRAY_COUNTU(D_i1_8019B838); i++) {
        D_i1_8019B838[i].unk_00 = D_i1_8019A820[i].unk_02;
        D_i1_8019B838[i].unk_02[0] = 0;

        for (j = 0; j < 5; j++) {
            D_i1_8019B838[i].unk_02[j] = 0;
        }
        for (j = 0; j < 3; j++) {
            D_i1_8019B838[i].unk_0C[j].x = D_i1_8019B838[i].unk_0C[j].y = D_i1_8019B838[i].unk_0C[j].z = 0.0f;
        }
        for (j = 0; j < 3; j++) {
            D_i1_8019B838[i].unk_30[j].x = D_i1_8019B838[i].unk_30[j].y = D_i1_8019B838[i].unk_30[j].z = 0.0f;
        }
        D_i1_8019B838[i].unk_74 = D_i1_8019B838[i].unk_78 = 0.0f;
        D_i1_8019B838[i].unk_7C = 0;
    }
    this->fwork[11] = 1.0f;
    for (i = 0; i < 33U; i++) {
        D_i1_8019B7F0[i] = 0;
    }
    var_v0 = 0;
    for (i = 0; i < ARRAY_COUNTU(D_i1_8019B838); i++) {
        var_v0 += D_i1_8019A820[i].unk_02;
    }
    this->swork[29] = this->swork[30] = var_v0 + 100;
    Animation_GetFrameData(D_i1_8019ACD4[this->swork[5]], 0, this->vwork);
    AUDIO_PLAY_BGM(NA_BGM_BOSS_VE);
}

bool Venom1_801937F4(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    Boss* this = thisx;
    s32 override;
    s32 i;
    s32 lum;
    s32 blue;
    s32 green;
    s32 red;

    if (limbIndex == 0) {
        rot->y += this->fwork[17];
    } else if (limbIndex == 20) {
        rot->x += this->fwork[6];
        while (rot->x < 0.0f) {
            rot->x += 360.0f;
        }
        while (rot->x >= 360.0f) {
            rot->x -= 360.0f;
        }
    }
    override = false;
    for (i = 0; i < 18; i++) {
        if (limbIndex == D_i1_8019A748[i].limb) {
            Matrix_Translate(gCalcMatrix, pos->x, pos->y, pos->z, MTXF_APPLY);
            Matrix_RotateZ(gCalcMatrix, rot->z * M_DTOR, MTXF_APPLY);
            Matrix_RotateY(gCalcMatrix, rot->y * M_DTOR, MTXF_APPLY);
            Matrix_RotateX(gCalcMatrix, rot->x * M_DTOR, MTXF_APPLY);
            Matrix_Mult(gGfxMatrix, gCalcMatrix, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            if (!(D_i1_8019B838[D_i1_8019A748[i].index].unk_7C & 1)) {
                if (D_i1_8019B838[D_i1_8019A748[i].index].unk_00 > 0) {
                    if ((D_i1_8019B838[D_i1_8019A748[i].index].unk_02[2] & 2) == 2) {
                        RCP_SetupDL(&gMasterDisp, SETUPDL_30);
                        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
                        if (*dList != NULL) {
                            gSPDisplayList(gMasterDisp++, *dList);
                        }
                        RCP_SetupDL(&gMasterDisp, SETUPDL_29);
                    } else if (i == 15) {
                        RCP_SetupDL(&gMasterDisp, SETUPDL_30);
                        blue = 255 - (s32) this->fwork[16];
                        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, blue, blue, 255);
                        if (*dList != NULL) {
                            gSPDisplayList(gMasterDisp++, *dList);
                        }
                        RCP_SetupDL(&gMasterDisp, SETUPDL_29);
                    } else {
                        if (*dList != NULL) {
                            gSPDisplayList(gMasterDisp++, *dList);
                        }
                    }
                } else if (!D_i1_8019A748[i].flag) {
                    blue = D_i1_8019B838[D_i1_8019A748[i].index].unk_74;
                    if ((blue != 0) && ((gGameFrameCount & 2) == 2)) {
                        green = D_i1_8019B838[D_i1_8019A748[i].index].unk_6C;
                        red = D_i1_8019B838[D_i1_8019A748[i].index].unk_64;
                        if (*dList != NULL) {
                            RCP_SetupDL(&gMasterDisp, SETUPDL_31);
                            if (blue > 128) {
                                blue = 128;
                            }
                            if (green > 128) {
                                green = 128;
                            }
                            if (red > 128) {
                                red = 128;
                            }
                            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, red, green, blue, 255);
                            gDPSetEnvColor(gMasterDisp++, 255, 255, 255, 0);
                            gSPDisplayList(gMasterDisp++, D_i1_8019A748[i].dList);
                            RCP_SetupDL(&gMasterDisp, SETUPDL_29);
                        }
                    } else {
                        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
                        gSPDisplayList(gMasterDisp++, D_i1_8019A748[i].dList);
                    }
                } else {
                    RCP_SetupDL(&gMasterDisp, SETUPDL_34);
                    lum = D_i1_8019AD68[(s32) this->fwork[8]];
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, lum, lum, lum, 255);
                    gSPDisplayList(gMasterDisp++, D_i1_8019A748[i].dList);
                    RCP_SetupDL(&gMasterDisp, SETUPDL_29);
                }
            }
            override = true;
            break;
        }
    }
    return override;
}

void Venom1_80193D64(s32 limbIndex, Vec3f* rot, void* thisx) {
    s32 spBC;
    Boss* this = thisx;
    Vec3f spAC;
    UnkStruct_i1_8019A058* var_s1;
    UnkStruct_i1_8019B838* var_s7;
    UnkStruct_i1_8019A820* var_s6;
    f32* var_s0;
    s32 temp_s3;
    s32 var_s4;
    s32 temp1;
    s32 temp2;

    var_s0 = this->info.hitbox;
    *var_s0++ = 33.0f;
    for (spBC = 0; spBC < ARRAY_COUNTU(D_i1_8019B838); spBC++) {
        temp_s3 = D_i1_8019A478[spBC][2];
        if (limbIndex == D_i1_8019A478[spBC][0]) {
            temp1 = D_i1_8019A478[spBC][1];
            if (D_i1_8019B838[spBC].unk_00 > 0) {
                var_s1 = &D_i1_8019A058[temp1];
            } else {
                var_s1 = &D_i1_8019A268[temp1];
            }

            for (var_s4 = 0; var_s4 < temp_s3; var_s4++, var_s0 += 6, var_s1++) {
                Matrix_MultVec3f(gCalcMatrix, &var_s1->offset, &spAC);
                var_s0[0] = spAC.z;
                var_s0[1] = var_s1->size;
                var_s0[2] = spAC.y;
                var_s0[3] = var_s1->size;
                var_s0[4] = spAC.x;
                var_s0[5] = var_s1->size;
            }
            break;
        } else {
            temp1 = temp_s3 * 2 + temp_s3 * 4; //  seems fake
            var_s0 += temp1;
        }
    }
    var_s6 = D_i1_8019A820;
    var_s7 = D_i1_8019B838;
    for (spBC = 0; spBC < ARRAY_COUNTU(D_i1_8019B838); spBC++, var_s6++, var_s7++) {
        if (limbIndex == var_s6->unk_00) {
            if (var_s7->unk_7C & 8) {
                temp2 = var_s6->unk_04;
                for (var_s4 = 0; var_s4 < var_s6->unk_06; var_s4++) {
                    Matrix_MultVec3f(gCalcMatrix, &D_i1_8019A544[temp2 + var_s4], &var_s7->unk_0C[var_s4]);
                }
                var_s7->unk_7C &= ~8;
                var_s7->unk_7C |= 0x10;
            }
            if (var_s7->unk_7C & 0x20) {
                Matrix_MultVec3f(gCalcMatrix, &D_tank_800C9F2C, &var_s7->unk_0C[0]);
                Matrix_GetYRPAngles(gCalcMatrix, &var_s7->unk_30[0]);
                var_s7->unk_7C &= ~0x20;
                var_s7->unk_7C |= 0x40;
            }
            if (var_s7->unk_7C & 0x100) {
                var_s7->unk_7C &= ~0x100;
                var_s7->unk_7C |= 0x200;
            }
            if (var_s7->unk_7C & 0x800) {
                Matrix_MultVec3f(gCalcMatrix, &D_tank_800C9F2C, &var_s7->unk_0C[1]);
                var_s7->unk_7C &= ~0x800;
                var_s7->unk_7C |= 0x1000;
            }
        }
    }

    switch (limbIndex) {
        case 7:
            if ((this->swork[11] % 2) != 0) {
                Matrix_MultVec3f(gCalcMatrix, &D_i1_8019AD5C, (Vec3f*) &this->fwork[3]);
                this->swork[11] &= ~1;
            }
            break;
        case 10:
            if (this->swork[11] & 2) {
                Matrix_MultVec3f(gCalcMatrix, &D_i1_8019AD5C, (Vec3f*) &this->fwork[3]);
                this->swork[11] &= ~2;
            }
            break;
        case 21:
            if (this->swork[11] & 4) {
                Matrix_MultVec3f(gCalcMatrix, &D_i1_8019AE38, (Vec3f*) &this->fwork[3]);
                this->swork[11] &= ~4;
            }
            break;
    }
    RCP_SetupDL(&gMasterDisp, SETUPDL_64);
    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
    var_s6 = D_i1_8019A820;
    var_s7 = D_i1_8019B838;
    for (spBC = 0; spBC < ARRAY_COUNTU(D_i1_8019B838); spBC++, var_s6++, var_s7++) {
        if ((limbIndex == var_s6->unk_00) && (var_s7->unk_7C & 0x200) && !((gGameFrameCount + spBC) & 2)) {
            temp2 = var_s6->unk_04;
            for (var_s4 = 0; var_s4 < var_s6->unk_06; var_s4++) {
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, D_i1_8019A544[temp2 + var_s4].x + var_s7->unk_0C[var_s4].x,
                                 D_i1_8019A544[temp2 + var_s4].y + var_s7->unk_0C[var_s4].y,
                                 D_i1_8019A544[temp2 + var_s4].z + var_s7->unk_0C[var_s4].z, MTXF_APPLY);
                Graphics_SetScaleMtx(2.0f);
                Matrix_RotateY(gGfxMatrix, var_s7->unk_30[var_s4].y * M_DTOR, MTXF_APPLY);
                Matrix_RotateX(gGfxMatrix, var_s7->unk_30[var_s4].x * M_DTOR, MTXF_APPLY);
                Matrix_RotateZ(gGfxMatrix, var_s7->unk_30[var_s4].z * M_DTOR, MTXF_APPLY);
                if (((s32) var_s7->unk_30[var_s4].z % 2) != 0) {
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
                } else {
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 96, 96, 255, 255);
                }
                Matrix_Scale(gGfxMatrix, 4.0f, 4.0f, 1.0f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_VE1_900DF20);
                Matrix_Pop(&gGfxMatrix);
            }
        }
    }
    RCP_SetupDL(&gMasterDisp, SETUPDL_29);
}

#ifdef NON_MATCHING
// Lots of problems with loop at 2082. Seems related to spE8. https://decomp.me/scratch/gOy2L
void Venom1_Boss_Update(Boss* boss) {
    s32 is0;
    Vec3f sp118[27];
    Actor* actor;
    Effect* effect;
    Vec3f sp104;
    Vec3f spF8;
    s32 spF4;
    f32 temp_fv1;
    f32 var_fv0;
    s32 spE8;
    s32 spE4;
    s32 is5;
    s32 ia0;
    s32 is1;
    s32 is3;
    s32 is2;
    f32 spCC;
    s32 is4;
    s32 is7;
    s32 pad1;
    f32 pad2;
    s32 spB8;
    s32 spB4;
    f32 temp_fs0;

    spE8 = 0;
    spE4 = 0;
    spB8 = 0;
    spB4 = 0;
    gBossFrameCount++;
    if (boss->state >= 3) {
        D_i1_8019C0B8 = 0;
        D_i1_8019C0BC = 0;
    }
    boss->swork[32]++;
    if (boss->swork[31] == 0) {
        switch (boss->swork[32]) {
            case 901:
                if ((gTeamShields[TEAM_ID_SLIPPY] > 0) && (gRadioState == 0)) {
                    Radio_PlayMessage(gMsg_ID_4092, RCID_SLIPPY);
                }
                break;
            case 1001:
                if (gTeamShields[TEAM_ID_SLIPPY] > 0) {
                    gShowBossHealth = 1;
                    gBossHealthBar = 255;
                    boss->swork[32] = 0;
                    boss->swork[31]++;
                }
                break;
        }
    }
    for (spF4 = 0; spF4 < ARRAY_COUNTU(D_i1_8019B838); spF4++) {
        if (D_i1_8019B838[spF4].unk_02[2] > 0) {
            D_i1_8019B838[spF4].unk_02[2]--;
        }
    }
    if (boss->swork[10] > 0) {
        boss->swork[10]--;
    }
    if (boss->swork[28] > 0) {
        gControllerRumbleFlags[0] = 1;
        boss->swork[28]--;
    }
    if (boss->swork[16] > 0) {
        boss->swork[16]--;
    }
    if ((boss->swork[16] & 3) == 1) {
        for (spF4 = 0; spF4 < (RAND_INT(5.0f) + 2); spF4++) {
            effect = func_effect_8007783C(OBJ_EFFECT_394);
            if (effect != NULL) {
                effect->obj.pos.x = boss->obj.pos.x + RAND_FLOAT_CENTERED(400.0f);
                effect->obj.pos.y = boss->obj.pos.y + 1250.0f;
                effect->obj.pos.z = boss->obj.pos.z + RAND_FLOAT_CENTERED(400.0f);
                effect->obj.rot.x = RAND_FLOAT(360.0f);
                effect->obj.rot.y = RAND_FLOAT(360.0f);
                effect->obj.rot.z = RAND_FLOAT(360.0f);
                effect->vel.x = RAND_FLOAT_CENTERED(5.0f);
                effect->vel.y = RAND_FLOAT_CENTERED(5.0f);
                effect->vel.z = RAND_FLOAT_CENTERED(5.0f);
                effect->unk_60.x = 5.0f + RAND_FLOAT_CENTERED(1.0f);
                effect->unk_60.y = 5.0f + RAND_FLOAT_CENTERED(1.0f);
                effect->unk_60.z = 5.0f + RAND_FLOAT_CENTERED(1.0f);
                effect->unk_78 = 12;
                effect->unk_7A = 12;
            }
        }
    }
    if (boss->swork[10] & 2) {
        effect = func_effect_8007783C(OBJ_EFFECT_394);
        if (effect != NULL) {
            effect->obj.status = OBJ_ACTIVE;
            effect->unk_78 = effect->unk_7A = 11;
            effect->obj.pos.x = boss->obj.pos.x + 125.0f;
            effect->obj.pos.y = boss->obj.pos.y;
            effect->obj.pos.z = boss->obj.pos.z;
            effect->scale2 = 10.0f;
            effect->obj.rot.z = RAND_FLOAT(360.0f);
            effect->vel.x = RAND_FLOAT_CENTERED(5.0f);
            effect->vel.y = RAND_FLOAT_CENTERED(3.f);
            effect->unk_44 = 100;
            effect->unk_46 = -3;
            effect->unk_60.z = 3.0f;
            if (Rand_ZeroOne() < 0.5f) {
                effect->unk_60.z = -effect->unk_60.z;
            }
        }
        effect = func_effect_8007783C(OBJ_EFFECT_394);
        if (effect != NULL) {
            effect->obj.status = OBJ_ACTIVE;
            effect->unk_78 = effect->unk_7A = 11;
            effect->obj.pos.x = boss->obj.pos.x - 125.0f;
            effect->obj.pos.y = boss->obj.pos.y;
            effect->obj.pos.z = boss->obj.pos.z;
            effect->obj.rot.z = RAND_FLOAT(360.0f);
            effect->scale2 = 10.0f;
            effect->vel.x = RAND_FLOAT_CENTERED(5.0f);
            effect->vel.y = RAND_FLOAT_CENTERED(3.f);
            effect->unk_44 = 100;
            effect->unk_46 = -3;
            effect->unk_60.z = 3.0f;
            if (Rand_ZeroOne() < 0.5f) {
                effect->unk_48 = -effect->unk_48;
            }
            effect->unk_4A = 50;
        }
    }
    if (boss->state <= 0) {
        switch (boss->swork[20]) {
            case 0:
                break;
            case 1:
                boss->fwork[13] = D_i1_8019AE00[boss->swork[21]].unk_0;
                boss->swork[22] = boss->swork[21];
                boss->swork[20]++;
                /* fallthrough */
            case 2:

                boss->fwork[14] = 0.0f;
                boss->swork[20]++;
                /* fallthrough */
            case 3:
                Math_SmoothStepToF(&boss->fwork[14], 12.0f, 1.0f, 1.0f, 0.01f);
                Venom1_801920F0(&boss->fwork[6], boss->fwork[13], 1.0f, boss->fwork[14], 0.01f, &spCC);
                if (fabsf(spCC) <= 45.0f) {
                    boss->fwork[12] = boss->fwork[13] + (SIGN_OF(spCC) * 20.0f);
                    boss->swork[20]++;
                }
                break;
            case 4:
                Math_SmoothStepToF(&boss->fwork[14], 12.0f, 1.0f, 1.0f, 0.01f);
                Math_SmoothStepToAngle(&boss->fwork[12], boss->fwork[13], 1.0f, boss->fwork[14] / 5.0f, 0.01f);
                if (fabsf(Math_SmoothStepToAngle(&boss->fwork[6], boss->fwork[12], 1.0f, boss->fwork[14], 0.01f)) <
                    2.0f) {
                    boss->swork[20] = 0;
                }
                break;
        }
    }
    Matrix_RotateY(gCalcMatrix, boss->obj.rot.y * M_DTOR, MTXF_NEW);

    for (spF4 = 0; spF4 < ARRAY_COUNTU(D_i1_8019B838); spF4++) {
        if (D_i1_8019B838[spF4].unk_74 < D_i1_8019B838[spF4].unk_78) {
            Math_SmoothStepToF(&D_i1_8019B838[spF4].unk_74, D_i1_8019B838[spF4].unk_78, 1.0f, 10.0f, 0.01f);
        } else {
            Math_SmoothStepToF(&D_i1_8019B838[spF4].unk_74, D_i1_8019B838[spF4].unk_78, 1.0f, 4.0f, 0.01f);
        }
        if (D_i1_8019B838[spF4].unk_64 < D_i1_8019B838[spF4].unk_68) {
            Math_SmoothStepToF(&D_i1_8019B838[spF4].unk_64, D_i1_8019B838[spF4].unk_68, 1.0f, 10.0f, 0.01f);
        } else {
            Math_SmoothStepToF(&D_i1_8019B838[spF4].unk_64, D_i1_8019B838[spF4].unk_68, 1.0f, 4.0f, 0.01f);
        }
        if (D_i1_8019B838[spF4].unk_6C < D_i1_8019B838[spF4].unk_70) {
            Math_SmoothStepToF(&D_i1_8019B838[spF4].unk_6C, D_i1_8019B838[spF4].unk_70, 1.0f, 10.0f, 0.01f);
        } else {
            Math_SmoothStepToF(&D_i1_8019B838[spF4].unk_6C, D_i1_8019B838[spF4].unk_70, 1.0f, 4.0f, 0.01f);
        }
        if (D_i1_8019B838[spF4].unk_7C & 4) {
            if (D_i1_8019B838[spF4].unk_02[1] <= 0) {
                D_i1_8019B838[spF4].unk_7C |= 8;
                if (D_i1_8019B838[spF4].unk_02[0] == 8) {
                    is4 = D_i1_8019A820[spF4].unk_08;
                    if ((is4 != -1) && (D_i1_8019B838[is4].unk_00 > 0)) {
                        D_i1_8019B838[is4].unk_00 = -1;
                        D_i1_8019B838[is4].unk_02[0] = 16;
                        D_i1_8019B838[is4].unk_02[1] = D_i1_8019A820[spF4].unk_0C;
                        D_i1_8019B838[is4].unk_7C |= 4;
                        AUDIO_PLAY_SFX(NA_SE_EN_EXPLOSION_S, boss->sfxSource, 4);
                        AUDIO_PLAY_SFX(NA_SE_EN_VEBOSS_BROKEN, boss->sfxSource, 4);
                    }
                    is4 = D_i1_8019A820[spF4].unk_0A;
                    if (is4 != -1) {
                        if (D_i1_8019B838[is4].unk_00 > 0) {
                            D_i1_8019B838[is4].unk_00 = -1;
                            D_i1_8019B838[is4].unk_02[0] = 16;
                            D_i1_8019B838[is4].unk_02[1] = D_i1_8019A820[spF4].unk_0C;

                            D_i1_8019B838[is4].unk_7C |= 4;
                        }
                    }
                }
                D_i1_8019B838[spF4].unk_02[0]--;
                if (D_i1_8019B838[spF4].unk_02[0] <= 0) {
                    D_i1_8019B838[spF4].unk_7C &= ~4;
                }
            } else {
                D_i1_8019B838[spF4].unk_02[1]--;
            }
        }
        if (D_i1_8019B838[spF4].unk_7C & 0x10) {
            if ((spF4 != 14) || (D_i1_8019B838[spF4].unk_00 <= 0)) {
                is4 = D_i1_8019B838[spF4].unk_02[0];
                for (is7 = 0; is7 < D_i1_8019A820[spF4].unk_06; is7++) {
                    Matrix_MultVec3f(gCalcMatrix, &D_i1_8019B838[spF4].unk_0C[is7], &spF8);
                    spF8.x += boss->obj.pos.x + RAND_FLOAT_CENTERED(60.0f);
                    spF8.y += boss->obj.pos.y + RAND_FLOAT_CENTERED(60.0f);
                    spF8.z += boss->obj.pos.z;
                    if (D_i1_8019AD80[is4][2] > 0) {
                        func_effect_8007D2C8(spF8.x, spF8.y, spF8.z, D_i1_8019AD80[is4][2]);
                    }
                    for (is1 = 0; is1 < D_i1_8019AD80[is4][0]; is1++) {
                        actor = Game_SpawnActor(OBJ_ACTOR_DEBRIS);
                        if (actor != NULL) {
                            actor->obj.status = OBJ_ACTIVE;
                            actor->obj.pos.x = spF8.x + RAND_FLOAT_CENTERED(60.0f);
                            actor->obj.pos.y = spF8.y + RAND_FLOAT_CENTERED(60.0f);

                            actor->obj.pos.z = spF8.z;
                            actor->obj.rot.x = RAND_FLOAT(360.0f);
                            actor->obj.rot.y = RAND_FLOAT(360.0f);
                            actor->obj.rot.z = RAND_FLOAT(360.0f);
                            actor->state = 50;
                            actor->iwork[0] = 0;
                            if (spF4 == 14) {
                                actor->iwork[1] = 1;
                            } else {
                                actor->iwork[1] = 0;
                            }
                            actor->vel.x = RAND_FLOAT_CENTERED(5.0f);
                            actor->vel.y = RAND_FLOAT_CENTERED(2.0f);
                            actor->vel.z = 20.0f + RAND_FLOAT_CENTERED(2.0f);
                            actor->fwork[0] = 5.0f + RAND_FLOAT_CENTERED(1.0f);
                            actor->fwork[1] = 5.0f + RAND_FLOAT_CENTERED(1.0f);
                            actor->fwork[2] = 5.0f + RAND_FLOAT_CENTERED(1.0f);
                            actor->gravity = 1.0f;
                        }
                    }
                    for (is1 = 0; is1 < D_i1_8019AD80[is4][1]; is1++) {
                        actor = Game_SpawnActor(OBJ_ACTOR_DEBRIS);
                        if (actor != NULL) {
                            actor->obj.status = OBJ_ACTIVE;
                            actor->obj.pos.x = spF8.x + RAND_FLOAT_CENTERED(60.0f);
                            actor->obj.pos.y = spF8.y + RAND_FLOAT_CENTERED(60.0f);
                            actor->obj.pos.z = spF8.z;
                            actor->obj.rot.x = RAND_FLOAT(360.0f);
                            actor->obj.rot.y = RAND_FLOAT(360.0f);
                            actor->obj.rot.z = RAND_FLOAT(360.0f);
                            actor->state = 50;
                            actor->iwork[0] = 1;
                            if (spF4 == 14) {
                                actor->iwork[1] = 1;
                            } else {
                                actor->iwork[1] = 0;
                            }
                            actor->vel.x = RAND_FLOAT_CENTERED(20.0f);
                            actor->vel.y = 5.0f + RAND_FLOAT_CENTERED(20.0f);
                            actor->vel.z = 20.0f + RAND_FLOAT_CENTERED(2.0f);

                            actor->fwork[0] = 5.0f + RAND_FLOAT_CENTERED(1.0f);
                            actor->fwork[1] = 5.0f + RAND_FLOAT_CENTERED(1.0f);
                            actor->fwork[2] = 5.0f + RAND_FLOAT_CENTERED(1.0f);
                            actor->gravity = 1.0f;
                        }
                    }
                }
            } else {
                for (is7 = 0; is7 < D_i1_8019A820[spF4].unk_06; is7++) {
                    Matrix_MultVec3f(gCalcMatrix, &D_i1_8019B838[spF4].unk_0C[is7], &spF8);
                    spF8.x += boss->obj.pos.x + RAND_FLOAT_CENTERED(60.0f);
                    spF8.y += boss->obj.pos.y + RAND_FLOAT_CENTERED(60.0f);
                    spF8.z += boss->obj.pos.z;
                    for (is1 = 0; is1 < 5; is1++) {
                        actor = Game_SpawnActor(OBJ_ACTOR_DEBRIS);
                        if (actor != NULL) {
                            actor->obj.status = OBJ_ACTIVE;
                            actor->obj.pos.x = spF8.x + RAND_FLOAT_CENTERED(60.0f);
                            actor->obj.pos.y = spF8.y + RAND_FLOAT_CENTERED(60.0f);
                            actor->obj.pos.z = spF8.z;

                            actor->obj.rot.x = RAND_FLOAT(360.0f);
                            actor->obj.rot.y = RAND_FLOAT(360.0f);
                            actor->obj.rot.z = RAND_FLOAT(360.0f);
                            actor->state = 50;
                            actor->iwork[0] = 1;
                            actor->iwork[1] = 1;
                            actor->vel.x = RAND_FLOAT_CENTERED(20.0f);
                            actor->vel.y = 5.0f + RAND_FLOAT_CENTERED(20.0f);
                            actor->vel.z = 20.0f + RAND_FLOAT_CENTERED(2.0f);
                            actor->fwork[0] = 5.0f + RAND_FLOAT_CENTERED(1.0f);
                            actor->fwork[1] = 5.0f + RAND_FLOAT_CENTERED(1.0f);
                            actor->fwork[2] = 5.0f + RAND_FLOAT_CENTERED(1.0f);
                            actor->gravity = 1.0f;
                        }
                    }
                }
            }
            D_i1_8019B838[spF4].unk_7C &= ~0x10;
        }
        if (D_i1_8019B838[spF4].unk_7C & 0x40) {
            actor = Game_SpawnActor(OBJ_ACTOR_DEBRIS);
            if (actor != NULL) {
                actor->obj.status = OBJ_ACTIVE;
                actor->obj.pos.x = boss->obj.pos.x + D_i1_8019B838[spF4].unk_0C[0].x;
                actor->obj.pos.y = boss->obj.pos.y + D_i1_8019B838[spF4].unk_0C[0].y;
                actor->obj.pos.z = boss->obj.pos.z + D_i1_8019B838[spF4].unk_0C[0].z;
                actor->obj.rot.x = D_i1_8019B838[spF4].unk_30[0].x;
                actor->obj.rot.y = D_i1_8019B838[spF4].unk_30[0].y;
                actor->obj.rot.z = D_i1_8019B838[spF4].unk_30[0].z;
                actor->state = 57;
                actor->iwork[0] = 0;
                actor->unk_048 = spF4;
                if (boss->swork[25] == 0) {
                    actor->vel.x = RAND_FLOAT_CENTERED(5.0f);
                    actor->vel.y = 10.0f + RAND_FLOAT_CENTERED(2.0f);
                    actor->vel.z = 10.0f + RAND_FLOAT_CENTERED(2.0f);
                    actor->fwork[0] = 5.0f + RAND_FLOAT_CENTERED(1.0f);
                    actor->fwork[1] = 5.0f + RAND_FLOAT_CENTERED(1.0f);
                    actor->fwork[2] = 5.0f + RAND_FLOAT_CENTERED(1.0f);
                } else {
                    Matrix_RotateY(gCalcMatrix, RAND_FLOAT(2.0f) * M_PI, MTXF_NEW);
                    sp104.x = 15.0f + RAND_FLOAT(10.0f);
                    sp104.z = 0.0f;
                    sp104.y = 0.0f;
                    Matrix_MultVec3f(gCalcMatrix, &sp104, &spF8);
                    actor->vel.x = spF8.x;
                    actor->vel.y = 15.0f + RAND_FLOAT_CENTERED(10.0f);
                    actor->vel.z = spF8.z;
                    actor->fwork[0] = 20.0f + RAND_FLOAT_CENTERED(1.0f);
                    actor->fwork[1] = 20.0f + RAND_FLOAT_CENTERED(1.0f);
                    actor->fwork[2] = 20.0f + RAND_FLOAT_CENTERED(1.0f);
                }
                actor->gravity = 2.0f;
            }
            for (is1 = 0; is1 < 6; is1++) {
                actor = Game_SpawnActor(OBJ_ACTOR_DEBRIS);
                if (actor != NULL) {
                    actor->obj.status = OBJ_ACTIVE;
                    actor->obj.pos.x = boss->obj.pos.x + D_i1_8019B838[spF4].unk_0C[0].x;
                    actor->obj.pos.y = boss->obj.pos.y + D_i1_8019B838[spF4].unk_0C[0].y;
                    actor->obj.pos.z = boss->obj.pos.z + D_i1_8019B838[spF4].unk_0C[0].z;
                    actor->obj.rot.x = RAND_FLOAT(360.0f);
                    actor->obj.rot.y = RAND_FLOAT(360.0f);
                    actor->obj.rot.z = RAND_FLOAT(360.0f);
                    actor->state = 50;
                    actor->iwork[0] = RAND_INT(2) + 2;
                    if (boss->swork[25] == 0) {
                        actor->vel.x = RAND_FLOAT_CENTERED(6.0f);
                        actor->vel.y = RAND_FLOAT_CENTERED(6.0f);
                        actor->vel.z = 40.0f + RAND_FLOAT_CENTERED(2.0f);
                        actor->fwork[0] = 5.0f + RAND_FLOAT_CENTERED(1.0f);
                        actor->fwork[1] = 5.0f + RAND_FLOAT_CENTERED(1.0f);
                        actor->fwork[2] = 5.0f + RAND_FLOAT_CENTERED(1.0f);
                    } else {
                        Matrix_RotateY(gCalcMatrix, RAND_FLOAT(2.0f) * M_PI, MTXF_NEW);
                        sp104.x = RAND_FLOAT(10.0f) + 15.0f;
                        sp104.z = 0.0f;
                        sp104.y = 0.0f;
                        Matrix_MultVec3f(gCalcMatrix, &sp104, &spF8);
                        actor->vel.x = spF8.x;
                        actor->vel.y = 30.0f + RAND_FLOAT_CENTERED(10.0f);
                        actor->vel.z = spF8.z;
                        actor->fwork[0] = 20.0f + RAND_FLOAT_CENTERED(1.0f);
                        actor->fwork[1] = 20.0f + RAND_FLOAT_CENTERED(1.0f);
                        actor->fwork[2] = 20.0f + RAND_FLOAT_CENTERED(1.0f);
                        actor->gravity = 1.0f;
                    }
                }
            }
            D_i1_8019B838[spF4].unk_7C &= ~0x40;
            D_i1_8019B838[spF4].unk_7C |= 1;
        }
        if (D_i1_8019B838[spF4].unk_7C & 0x80) {
            if (D_i1_8019B838[spF4].unk_02[4] <= 0) {
                D_i1_8019B838[spF4].unk_78 = 128.0f;
                D_i1_8019B838[spF4].unk_68 = D_i1_8019B838[spF4].unk_70 = 16.0f;

                D_i1_8019B838[spF4].unk_7C |= 0x100;
                if (D_i1_8019B838[spF4].unk_02[3] == 7) {
                    for (is7 = 0; is7 < 4; is7++) {
                        is4 = D_i1_8019A820[spF4].unk_0E[is7];
                        if (is4 != -1) {
                            D_i1_8019B838[is4].unk_02[3] = 8;
                            D_i1_8019B838[is4].unk_02[4] = D_i1_8019A820[spF4].unk_16;
                            D_i1_8019B838[is4].unk_7C |= 0x80;
                        }
                    }
                }
                for (is7 = 0; is7 < D_i1_8019A820[spF4].unk_06; is7++) {
                    D_i1_8019B838[spF4].unk_0C[is7].x = RAND_DOUBLE_CENTERED(4.0);
                    D_i1_8019B838[spF4].unk_0C[is7].y = RAND_DOUBLE_CENTERED(4.0);
                    D_i1_8019B838[spF4].unk_0C[is7].z = RAND_DOUBLE_CENTERED(4.0);
                    D_i1_8019B838[spF4].unk_30[is7].x = RAND_FLOAT(360.0f);
                    D_i1_8019B838[spF4].unk_30[is7].y = RAND_FLOAT(360.0f);
                    D_i1_8019B838[spF4].unk_30[is7].z = RAND_FLOAT(360.0f);
                }
                D_i1_8019B838[spF4].unk_02[3]--;
                if (D_i1_8019B838[spF4].unk_02[3] <= 0) {
                    D_i1_8019B838[spF4].unk_68 = D_i1_8019B838[spF4].unk_70 = D_i1_8019B838[spF4].unk_78 = 0.0f;
                    D_i1_8019B838[spF4].unk_7C &= ~0x80;
                }
            } else {
                D_i1_8019B838[spF4].unk_02[4]--;
            }
        }
        if (D_i1_8019B838[spF4].unk_7C & 0x200) {
            D_i1_8019B838[spF4].unk_7C &= ~0x200;
        }
        if (D_i1_8019B838[spF4].unk_7C & 0x1000) {
            Matrix_MultVec3f(gCalcMatrix, &D_tank_800C9F2C, &spF8);
            spF8.x += boss->obj.pos.x + D_i1_8019B838[spF4].unk_0C[1].x + RAND_FLOAT_CENTERED(60.0f);
            spF8.y += boss->obj.pos.y + D_i1_8019B838[spF4].unk_0C[1].y + RAND_FLOAT_CENTERED(60.0f);
            spF8.z += boss->obj.pos.z + D_i1_8019B838[spF4].unk_0C[1].z;
            func_effect_8007D2C8(spF8.x, spF8.y, spF8.z, D_i1_8019B838[spF4].unk_60);
            D_i1_8019B838[spF4].unk_7C &= ~0x1000;
        }
    }
    if ((boss->state == 0) || (boss->state == 1)) {
        is4 = 0;
        for (spF4 = 0; spF4 < ARRAY_COUNTU(D_i1_8019B838); spF4++) {
            if (D_i1_8019B838[spF4].unk_00 <= 0) {
                is4++;
            }
        }
        if ((boss->state == 0) && (boss->swork[20] == 0)) {
            if (is4 > 0) {
                if (boss->swork[21] < (is4 - 1) / 5) {
                    boss->swork[21] = (is4 - 1) / 5;
                    boss->swork[20] = 1;
                }
            }
            if (D_i1_8019C0C0 == 1) {
                D_i1_8019C0C0 = 0;
                if (boss->swork[21] < 5) {
                    boss->swork[21]++;
                    boss->swork[20] = 1;
                }
            }
        }
        if (is4 == 17) {
            boss->swork[9] = 2;
            boss->swork[22] = 4;
            boss->fwork[6] = boss->fwork[12] = boss->fwork[13] = 0.0f;
        } else if ((is4 == 16) && (boss->state == 0)) {
            boss->swork[9] = 1;
            boss->fwork[16] = 0.0f;
            boss->fwork[15] = 255.0f;

            if (boss->swork[22] < 3) {
                boss->swork[22] = 3;
            }
        }
    }
    if (boss->dmgType == DMG_BEAM) {
        boss->dmgType = DMG_NONE;
        switch (boss->state) {
            case 0:
            case 1:
                is4 = D_i1_8019A500[boss->dmgPart];
                if (D_i1_8019B838[is4].unk_00 > 0) {
                    if ((is4 != 14) || (boss->state != 0)) {
                        D_i1_8019B838[is4].unk_00 -= boss->damage;
                        D_i1_8019B838[is4].unk_02[2] = 15;

                        if (D_i1_8019B838[is4].unk_00 <= 0) {
                            AUDIO_PLAY_SFX(NA_SE_EN_EXPLOSION_S, boss->sfxSource, 4);
                            AUDIO_PLAY_SFX(NA_SE_EN_VEBOSS_BROKEN, boss->sfxSource, 4);
                            D_i1_8019B838[is4].unk_00 = -1;
                            D_i1_8019B838[is4].unk_02[0] = 16;
                            D_i1_8019B838[is4].unk_02[1] = 0;
                            D_i1_8019B838[is4].unk_7C |= 0xC;
                        } else {
                            AUDIO_PLAY_SFX(NA_SE_EN_DAMAGE_S, boss->sfxSource, 4);
                            if (is4 == 14) {
                                D_i1_8019B838[is4].unk_7C |= 8;
                            }
                        }
                    } else {
                        AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, boss->sfxSource, 4);
                    }
                } else {
                    AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, boss->sfxSource, 4);
                }
                break;
            case 2:
                if (D_i1_8019A500[boss->dmgPart] == 15) {
                    AUDIO_PLAY_SFX(NA_SE_EN_VEBOSS_DAMAGE, boss->sfxSource, 4);
                    D_i1_8019B838[15].unk_02[2] = 10;
                    D_i1_8019B838[15].unk_02[3] = 0;
                    D_i1_8019B838[15].unk_7C |= 0x80;
                    if (boss->health > 0) {
                        boss->health -= boss->damage;
                        boss->timer_05A = 18;

                        if (boss->health <= 0) {
                            gScreenFlashTimer = 8;
                            gTeamLowHealthMsgTimer = -1;
                            gKillEventActors = true;
                            AUDIO_PLAY_SFX(NA_SE_EN_DOWN_IMPACT, boss->sfxSource, 4);
                            boss->health = 0;
                        }
                    }
                } else {
                    AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, boss->sfxSource, 4);
                }
                break;
        }
    }
    switch (boss->state) {
        case 0:
        case 1:
            for (spF4 = 0; spF4 < 33U; spF4++) {
                if (((gGameFrameCount % 4) == 0) && (D_i1_8019B7F0[spF4] != 0)) {
                    is4 = D_i1_8019A500[spF4];
                    if ((D_i1_8019B838[is4].unk_00 > 0) && ((is4 != 14) || (boss->state != 0))) {
                        D_i1_8019B838[is4].unk_00 -= 2;
                        if (D_i1_8019B838[is4].unk_00 <= 0) {
                            D_i1_8019B838[is4].unk_00 = -1;
                            D_i1_8019B838[is4].unk_02[0] = 16;
                            D_i1_8019B838[is4].unk_02[1] = 0;
                            D_i1_8019B838[is4].unk_7C |= 0xC;
                            AUDIO_PLAY_SFX(NA_SE_EN_EXPLOSION_S, boss->sfxSource, 4);
                            AUDIO_PLAY_SFX(NA_SE_EN_VEBOSS_BROKEN, boss->sfxSource, 4);
                        } else if (is4 == 14) {
                            D_i1_8019B838[is4].unk_7C |= 8;
                        }
                    }
                    D_i1_8019B7F0[spF4] = 0;
                }
            }
            break;
        case 2:
            if (((gGameFrameCount % 4) == 0) && (boss->timer_05A == 0)) {
                for (spF4 = 0; spF4 < 33U; spF4++) {
                    if ((D_i1_8019A500[spF4] == 15) && (D_i1_8019B7F0[spF4] != 0)) {
                        AUDIO_PLAY_SFX(NA_SE_EN_VEBOSS_DAMAGE, boss->sfxSource, 4);
                        D_i1_8019B838[15].unk_02[3] = 10;
                        D_i1_8019B838[15].unk_02[4] = 0;
                        D_i1_8019B838[15].unk_7C |= 0x80;
                        if (boss->health > 0) {
                            boss->health -= 10;
                            boss->timer_05A = 35;
                            if (boss->health <= 0) {
                                gScreenFlashTimer = 8;
                                gTeamLowHealthMsgTimer = -1;
                                gKillEventActors = true;
                                AUDIO_PLAY_SFX(NA_SE_EN_DOWN_IMPACT, boss->sfxSource, 4);
                                boss->health = 0;
                            }
                        }
                    }
                    D_i1_8019B7F0[spF4] = 0;
                }
            }

            break;
    }
    is4 = 0;
    for (spF4 = 0; spF4 < 17; spF4++) {
        is4 += (D_i1_8019B838[spF4].unk_00 < 0) ? 0 : D_i1_8019B838[spF4].unk_00;
    }
    boss->swork[30] = boss->health + is4;
    gBossHealthBar = 255.0f * boss->swork[30] / boss->swork[29];
    switch (boss->state) {
        case 4:
        case 5:
            break;
        case 1:
            boss->fwork[6] += 5.0f;
            Math_SmoothStepToF(&boss->fwork[16], boss->fwork[15], 1.0f, 4.0f, 0.01f);
            break;
        case 2:
            boss->fwork[9] = 200.0f / (boss->health + 100.0f);
            boss->fwork[8] -= boss->fwork[9];
            if (boss->fwork[8] < 0.0f) {
                boss->fwork[8] = 22.0f;
            }
            break;
        case 3:
            boss->fwork[9] = 200.0f / ((2.0f * boss->health) + 100.0f);
            boss->fwork[8] -= boss->fwork[9];
            if (boss->fwork[8] <= 0.0f) {
                boss->fwork[8] = 22.0f;
            }
            break;
    }
    switch (boss->swork[6]) {
        case 0:
            temp_fs0 = gPlayer[0].trueZpos + boss->fwork[2];
            if (boss->swork[15] == 0) {
                if (boss->obj.pos.z >= temp_fs0) {
                    if (boss->obj.pos.z > (gPlayer[0].trueZpos - 200.0f)) {
                        var_fv0 = Math_SmoothStepToF(&boss->obj.pos.z, temp_fs0, 0.5f, 35.0f, 0.01f);
                    } else {
                        var_fv0 = Math_SmoothStepToF(&boss->obj.pos.z, temp_fs0, 0.4f, 10.0f, 0.01f);
                    }
                } else {
                    var_fv0 = Math_SmoothStepToF(&boss->obj.pos.z, temp_fs0, 0.2f, 25.0f, 0.01f);
                }
                boss->fwork[11] = (-40.0f + var_fv0) / -40.0f;
                if (boss->fwork[11] < 0.8f) {
                    boss->fwork[11] = 0.8f;
                }
                if (fabsf(var_fv0) <= 2.0f) {
                    boss->swork[15] = 1;
                    boss->swork[14] = D_i1_8019A04C[boss->swork[13]][1];
                }
            } else {
                if ((gPlayer[0].pos.z - boss->obj.pos.z < 500.0f) || (gPlayer[0].pos.z - boss->obj.pos.z > 8000.0f)) {
                    boss->swork[14] = 0;
                }
                if (boss->swork[14] <= 0) {
                    boss->swork[15] = 0;
                    boss->swork[13]++;
                    if (boss->swork[13] >= 3U) {
                        boss->swork[13] = 0;
                    }
                    boss->fwork[2] = D_i1_8019A04C[boss->swork[13]][0];
                    boss->swork[14] = D_i1_8019A04C[boss->swork[13]][1];
                } else {
                    boss->swork[14]--;
                }
            }
            boss->vel.z = -40.0f;
            break;
        case 1:
            if ((boss->vel.y <= -10.0f) && (boss->swork[5] != 5)) {
                spE8 = 1;
            }
            if (boss->obj.pos.y < 0.f) {
                boss->obj.pos.y = 0.f;
                boss->vel.y = 0.f;
                boss->gravity = 0.f;
                boss->swork[6] = 2;
                boss->swork[10] = 16;
                gCameraShake = 40;
                boss->swork[23] = RAND_FLOAT(5.0f);
                AUDIO_PLAY_SFX(NA_SE_OB_VEBOSS_LAND, boss->sfxSource, 4);
                spB8 = 3;
                boss->swork[28] = 5;
            }
            break;
        case 2:
            boss->vel.z *= 0.7f;
            break;
        case 4:
            temp_fs0 = gPlayer[0].pos.z + boss->fwork[2];
            if (temp_fs0 <= boss->obj.pos.z) {
                var_fv0 = Math_SmoothStepToF(&boss->obj.pos.z, temp_fs0, 0.4f, 20.0f, 0.01f);
            } else {
                var_fv0 = Math_SmoothStepToF(&boss->obj.pos.z, temp_fs0, 0.2f, 30.0f, 0.01f);
            }
            if (boss->state < 4) {
                boss->fwork[11] = (-40.0f + var_fv0) / -40.0f;
                if (boss->fwork[11] < 0.8f) {
                    boss->fwork[11] = 0.8f;
                }
            }
            temp_fs0 = gPlayer[0].trueZpos + boss->fwork[2] - boss->obj.pos.z;
            if ((fabsf(temp_fs0) <= 70.0f) && (boss->state == 3)) {
                boss->swork[5] = D_i1_8019AD2C[4].unk_0[0].unk_0;
                boss->swork[4] = boss->swork[4];
                boss->fwork[0] = 0.0f;
                boss->fwork[10] = 0.0f;
                boss->fwork[11] = 1.0f;
                boss->swork[7] = 2;
                boss->swork[9] = 4;
                boss->swork[1] = 4;
                boss->swork[2] = 0;
                boss->swork[6] = 5;
                boss->timer_050 = 3;
                boss->timer_052 = 150;
            }
            boss->vel.z = -40.0f;
            break;
        case 5:
            boss->vel.z = gPlayer[0].vel.z;
            break;
        case 3:
            Math_SmoothStepToF(&boss->vel.z, 0.0f, 0.5f, 0.3f, 0.01f);
            break;
        case 6:
            break;
    }
    switch (boss->swork[5]) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            Animation_GetFrameData(D_i1_8019ACD4[boss->swork[5]], boss->fwork[10], sp118);
            break;
        case 8:
            break;
    }
    if ((boss->swork[5] == 0) || (boss->swork[5] == 1) || (boss->swork[5] == 3)) {
        if (1) {}
        switch (boss->swork[27]) {
            case 0:
                if (boss->fwork[10] > 14.0f) {
                    AUDIO_PLAY_SFX(NA_SE_OB_VEBOSS_WALK, boss->sfxSource, 4);
                    boss->swork[27]++;
                }
                break;
            case 1:
                if (boss->fwork[10] > 45.0f) {
                    AUDIO_PLAY_SFX(NA_SE_OB_VEBOSS_WALK, boss->sfxSource, 4);
                    boss->swork[27]++;
                }
                break;
            case 2:
                break;
        }
    }
    switch (boss->swork[5]) {
        case 0:
        case 1:
        case 3:
        case 4:
        case 5:
        case 6:
            break;
        case 7:
            if (boss->timer_052 >= 37) {
                if (boss->timer_050 == 1) {
                    boss->swork[11] |= 4;
                } else if (boss->timer_050 == 0) {
                    spF8.x = boss->obj.pos.x + boss->fwork[3];
                    spF8.y = boss->obj.pos.y + boss->fwork[4];
                    spF8.z = boss->obj.pos.z + boss->fwork[5];
                    func_effect_8007D2C8(spF8.x, spF8.y, spF8.z, 5.0f);
                    boss->timer_050 = 3;
                }
            }
            switch (boss->timer_052) {
                case 126:
                    D_i1_8019B838[6].unk_7C |= 0x800;
                    D_i1_8019B838[6].unk_60 = 10.0f;
                    break;
                case 123:
                    D_i1_8019B838[6].unk_7C |= 0x20;
                    break;
                case 122:
                    gCameraShake = 20;
                    boss->swork[28] = 7;
                    AUDIO_PLAY_SFX(NA_SE_OB_VEBOSS_BOUND, boss->sfxSource, 4);
                    D_i1_8019B838[2].unk_60 = 5.0f;
                    D_i1_8019B838[2].unk_7C |= 0x800;
                    D_i1_8019B838[5].unk_7C |= 0x800;
                    D_i1_8019B838[5].unk_60 = 5.0f;
                    break;
                case 121:
                    D_i1_8019B838[8].unk_7C |= 0x800;
                    D_i1_8019B838[8].unk_60 = 10.0f;
                    break;
                case 119:
                    D_i1_8019B838[8].unk_7C |= 0x20;
                    break;
                case 118:
                    gCameraShake = 30;
                    boss->swork[28] = 7;
                    AUDIO_PLAY_SFX(NA_SE_OB_VEBOSS_BOUND, boss->sfxSource, 4);
                    D_i1_8019B838[8].unk_7C |= 0x800;
                    D_i1_8019B838[8].unk_60 = 10.0f;
                    break;
                case 115:
                    D_i1_8019B838[7].unk_7C |= 0x20;
                    break;
                case 91:
                    boss->swork[28] = 7;
                    AUDIO_PLAY_SFX(NA_SE_OB_VEBOSS_BOUND, boss->sfxSource, 4);
                    break;
                case 78:
                    boss->swork[28] = 7;
                    AUDIO_PLAY_SFX(NA_SE_OB_VEBOSS_BOUND, boss->sfxSource, 4);
                    gCameraShake = 20;
                    D_i1_8019B838[10].unk_7C |= 0x800;
                    D_i1_8019B838[10].unk_60 = 10.0f;
                    break;
                case 69:
                    D_i1_8019B838[9].unk_7C |= 0x20;
                    break;
                case 66:
                    boss->swork[28] = 7;
                    AUDIO_PLAY_SFX(NA_SE_OB_VEBOSS_BOUND, boss->sfxSource, 4);
                    D_i1_8019B838[11].unk_7C |= 0x20;
                    break;
                case 65:
                    D_i1_8019B838[2].unk_7C |= 0x20;
                    break;
                case 63:
                    D_i1_8019B838[10].unk_7C |= 0x20;
                    break;
                case 62:
                    D_i1_8019B838[1].unk_7C |= 0x20;
                    break;
                case 61:
                    D_i1_8019B838->unk_7C |= 0x20;
                    break;
                case 60:
                    spF8.x = boss->obj.pos.x + boss->fwork[3];
                    spF8.y = boss->obj.pos.y + boss->fwork[4];
                    spF8.z = boss->obj.pos.z + boss->fwork[5];
                    func_effect_8007BFFC(spF8.x, spF8.y, spF8.z, 0, 0, 0, 25.0f, 5);
                    gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
                    gFillScreenAlpha = gFillScreenAlphaTarget = 255;
                    break;
                case 59:
                    gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
                    gFillScreenAlpha = gFillScreenAlphaTarget = 128;
                    break;
                case 58:
                    gFillScreenAlpha = gFillScreenAlphaTarget = 0;
                    break;
                case 50:
                    boss->swork[25] = 1;
                    for (spF4 = 0; spF4 < ARRAY_COUNTU(D_i1_8019B838); spF4++) {
                        if (!(D_i1_8019B838[spF4].unk_7C & 1)) {
                            D_i1_8019B838[spF4].unk_7C |= 0x20;
                        }
                    }
                    break;
                case 49:
                    Boss_AwardBonus(boss);
                    gShowBossHealth = 0;
                    boss->swork[28] = 9;
                    AUDIO_PLAY_SFX(NA_SE_OB_VEBOSS_BOUND, boss->sfxSource, 4);
                    boss->swork[26] = 1;
                    boss->info.hitbox = gNoHitbox;
                    boss->drawShadow = false;
                    func_effect_8007A568(boss->obj.pos.x, boss->obj.pos.y + 10.0f, boss->obj.pos.z, 40.0f);
                    gCameraShake = 40;
                    break;
                case 12:
                    gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
                    gFillScreenAlpha = 0;
                    gFillScreenAlphaTarget = 255;
                    gFillScreenAlphaStep = 5;
                    boss->obj.status = OBJ_DYING;
                    boss->timer_052 = 80;
                    break;
            }
            break;
        case 2:
            if (boss->fwork[10] >= 16.0f) {
                switch (boss->swork[18]) {
                    case 0:
                        boss->swork[18]++;
                        boss->swork[11] |= 1;
                        break;
                    case 1:
                        AUDIO_PLAY_SFX(NA_SE_OB_VEBOSS_ATTACK, boss->sfxSource, 4);
                        gCameraShake = 40;
                        boss->swork[28] = 5;
                        spB8 = spB4 = 1;
                        boss->swork[18]++;
                        break;
                    case 2:
                        break;
                }
            }
            if (boss->fwork[10] >= 43.0f) {
                switch (boss->swork[19]) {
                    case 0:
                        boss->swork[19]++;
                        boss->swork[11] |= 2;
                        break;
                    case 1:
                        spB4 = 1;
                        AUDIO_PLAY_SFX(NA_SE_OB_VEBOSS_ATTACK, boss->sfxSource, 4);
                        gCameraShake = 40;
                        boss->swork[28] = 5;
                        spB8 = 2;
                        boss->swork[19]++;
                        break;
                    case 2:
                        break;
                }
            }
            break;
    }
    switch (boss->swork[7]) {
        case 0:
            if (boss->fwork[11] < 0.9f) {
                Math_SmoothStepToF(&boss->fwork[0], 0.2f, 0.5f, 0.05f, 0.01f);
                Math_SmoothStepToVec3fArray(sp118, boss->vwork, 1, 27, boss->fwork[0], 360.0f, 0.01f);
            } else {
                Math_SmoothStepToF(&boss->fwork[0], 1.0f, 0.5f, 0.05f, 0.01f);
                Math_SmoothStepToVec3fArray(sp118, boss->vwork, 1, 27, boss->fwork[0], 360.0f, 0.01f);
            }
            break;
        case 1:
            Math_SmoothStepToF(&boss->fwork[0], 1.0f, 0.1f, 0.05f, 0.01f);
            Math_SmoothStepToVec3fArray(sp118, boss->vwork, 1, 27, boss->fwork[0], 360.0f, 0.01f);
            break;
        case 2:
            Math_SmoothStepToF(&boss->fwork[0], 0.7f, 0.07f, 0.05f, 0.01f);
            Math_SmoothStepToVec3fArray(sp118, boss->vwork, 1, 27, boss->fwork[0], 45.0f, 0.01f);
            break;
    }
    switch (boss->swork[5]) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 6:
            boss->fwork[10] += boss->fwork[11];
            if ((s32) boss->fwork[10] >= Animation_GetFrameCount(D_i1_8019ACD4[boss->swork[5]])) {
                spE8 = 1;
            }
            break;
        case 4:
            if ((s32) boss->fwork[10] == 17) {
                if (gPlayer[0].vel.z < 0.0f) {
                    boss->vel.z = 2.0f * gPlayer[0].vel.z;
                } else {
                    boss->vel.z = 0.0f;
                }
                boss->swork[6] = 1;
                boss->gravity = 3.0f;
                boss->vel.y = 30.0f;
            }
            if (boss->fwork[10] < (Animation_GetFrameCount(D_i1_8019ACD4[boss->swork[5]]) - 1)) {
                boss->fwork[10] += 1.0f;
            }
            break;
        case 5:
            if ((s32) boss->fwork[10] == 2) {
                boss->swork[17] = 5;
            }
            if (boss->fwork[10] > 1.0f) {
                boss->fwork[10] += -1.0f;
            } else if (boss->swork[17] > 0) {
                boss->swork[17]--;
            } else {
                spE8 = 1;
            }
            break;
        case 7:
            if (boss->fwork[10] < (Animation_GetFrameCount(D_i1_8019ACD4[boss->swork[5]]) - 1.0f)) {
                boss->fwork[10] += boss->fwork[11];
                Math_SmoothStepToF(&boss->fwork[11], 0.5f, 0.7f, 0.02f, 0.01f);
                if (boss->fwork[11] < 0.7f) {
                    boss->fwork[11] = 0.7f;
                }
            } else {
                boss->swork[9] = 5;
            }
            break;
        case 8:
            break;
    }
    temp_fv1 = gPlayer[0].pos.z - boss->obj.pos.z;
    // is0 = boss->swork[1];
    // is5 = boss->swork[2];
    pad1 = spE8; // probably fake, but unclear how to resolve
    if ((pad1 != 0) && (D_i1_8019AD2C[boss->swork[1]].unk_0[boss->swork[2]].unk_2 & 1) && (boss->swork[3] != 0)) {
        spE4 = 1;
        if (boss->swork[3] > 0) {
            boss->swork[3]--;
        }
    }

    if ((D_i1_8019C0BC != 0) && (boss->state >= 3)) {
        D_i1_8019C0BC = 0;
    }
    if ((D_i1_8019C0BC != 0) && (boss->swork[1] != 2) && (boss->state < 3)) {
        pad1 |= 2;
        spE4 = 1;
    }
    if (pad1 != 0) {
        is0 = boss->swork[1];
        is5 = boss->swork[2] - spE4 + 1;
        is1 = boss->swork[4];
        if (D_i1_8019C0BC != 0) {
            if (temp_fv1 < 5000.0f) {
                boss->swork[24] = D_i1_8019C0BC - 1;
                is5 = 0;
                is0 = 2;
            } else {
                pad1 &= ~2;
            }
            D_i1_8019C0BC = 0;
        }
        if (((pad1 & 1) == 1) && (D_i1_8019AD2C[is0].unk_0[is5].unk_0 == -1)) {
            is5 = 0;
            spE8 = pad1;
            do {
                is4 = 0;
                is1 = boss->swork[4] + 1;
                is0 = D_i1_8019AD54[is1];
                if (is0 == -1) {
                    is0 = D_i1_8019AD54[0];
                    is1 = 0;
                }
                if (((is0 == 2) && (temp_fv1 < 5000.0f)) || ((is0 == 1) && (D_i1_8019C0B8 == 0)) ||
                    ((is0 == 0) && (D_i1_8019C0B8 == 1))) {
                    boss->swork[4] = is1;
                    is4 = 1;
                }
                if (D_i1_8019C0B8 >= 2) {
                    is3 = ((D_i1_8019C0B8 - 1) / 10);
                    ia0 = ((D_i1_8019C0B8 - 1) % 10);
                    switch (is0) {
                        case 1:
                            if (is3 > 0) {
                                boss->swork[3] = is3 - 1;
                            } else {
                                is4 = 1;
                                boss->swork[4] = is1;
                            }
                            break;
                        case 0:
                            if (ia0 > 0) {
                                boss->swork[3] = ia0 - 1;
                            } else {
                                is4 = 1;
                                boss->swork[4] = is1;
                            }
                            break;
                        case 3:
                            boss->swork[3] = -1;
                            break;
                    }
                }
                if ((is0 == 0) && (D_i1_8019C0B8 == 1)) {
                    D_i1_8019C0B8 = 0;
                }
            } while (is4 != 0);
            pad1 = spE8;
        }
        is2 = D_i1_8019AD2C[is0].unk_0[is5].unk_0;
        if (pad1 != 0) {
            boss->swork[27] = 0;

            switch (is2) {
                case 2:
                    boss->swork[23] = RAND_FLOAT(2.0f);
                    boss->swork[18] = 0;
                    boss->swork[19] = 0;
                    /* fallthrough */
                case 3:
                    if ((is2 == 3) && (D_i1_8019C0B8 == 2)) {
                        is2 = 2;
                        is5--;
                        boss->swork[18] = 0;
                        boss->swork[19] = 0;
                    }
                    /* fallthrough */
                case 0:
                case 1:
                    boss->swork[6] = 0;
                    boss->fwork[10] = 0;
                    if (boss->swork[5] == 5) {
                        boss->fwork[0] = 0;
                        boss->swork[7] = 1;

                    } else {
                        boss->swork[7] = 0;
                    }
                    break;
                case 4:
                    AUDIO_PLAY_SFX(NA_SE_OB_VEBOSS_JUMP, boss->sfxSource, 4);
                    boss->swork[7] = 1;
                    boss->fwork[10] = 0;
                    boss->gravity = 0;
                    boss->fwork[0] = 0;
                    break;
                case 5:
                    boss->fwork[10] = Animation_GetFrameCount(D_i1_8019ACD4[boss->swork[5]]) - 1;
                    boss->swork[7] = 1;
                    boss->gravity = 0;
                    boss->fwork[0] = 0;
                    break;
                case 6:
                    boss->fwork[10] = 0;
                    break;
                case 7:
                    break;
            }
            boss->swork[4] = is1;
            boss->swork[1] = is0;
            boss->swork[2] = is5;
            boss->swork[5] = is2;
        }
    }
    if ((boss->health <= 0) && (boss->state == 2) && (boss->swork[1] != 2) && (boss->obj.pos.y <= 0)) {
        boss->swork[5] = D_i1_8019AD2C[3].unk_0[0].unk_0;
        boss->swork[4] = boss->swork[4];
        boss->swork[9] = 3;
        boss->swork[3] = -1;
        boss->fwork[10] = 0;
        boss->fwork[11] = 1.0f;
        boss->fwork[2] = -2000.0f;
        boss->swork[7] = 0;
        boss->swork[1] = 3;
        boss->swork[2] = 0;
        boss->swork[6] = 4;

        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 0);
        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 0);
    }
    if ((spB4 == 1) || (spB4 == 2)) {
        effect = func_effect_8007783C(OBJ_EFFECT_394);
        if (effect != NULL) {
            Matrix_MultVec3f(gCalcMatrix, (Vec3f*) &boss->fwork[3], &spF8);
            effect->unk_78 = effect->unk_7A = 11;
            effect->obj.pos.x = boss->obj.pos.x + spF8.x;
            effect->obj.pos.y = boss->obj.pos.y + spF8.y;
            effect->obj.pos.z = boss->obj.pos.z + spF8.z;
            effect->scale2 = 8.0f;

            effect->obj.rot.z = RAND_FLOAT(360.0f);
            effect->vel.x = RAND_FLOAT_CENTERED(5.0f);
            effect->vel.y = RAND_FLOAT_CENTERED(3.0f);
            effect->unk_60.z = 3.0f + RAND_FLOAT(2.0f);
            effect->unk_44 = 100;
            effect->unk_46 = -5;
            if (Rand_ZeroOne() < 0.5f) {
                effect->unk_60.z = -effect->unk_60.z;
            }
        }
    }
    switch (spB8) {
        case 1:
            is3 = 0;
            actor = gActors;
            is4 = boss->swork[23];
            temp_fs0 = boss->obj.pos.z;
            var_fv0 = -1500.0f;
            for (spF4 = 0; spF4 < ARRAY_COUNT(gActors); spF4++, actor++) {
                if (actor->obj.status == OBJ_FREE) {

                    while ((is3 <= boss->swork[22]) &&
                           ((temp_fs0 + D_i1_80199CD0[is4][is3].z) >= (var_fv0 + gPlayer[0].trueZpos))) {
                        is3++;
                    }
                    if (is3 <= boss->swork[22]) {
                        Actor_Initialize(actor);
                        actor->obj.status = OBJ_ACTIVE;
                        actor->obj.id = OBJ_ACTOR_280;
                        actor->obj.pos.x = D_i1_80199CD0[is4][is3].x;
                        actor->obj.pos.y = D_i1_80199CD0[is4][is3].y;
                        actor->obj.pos.z = D_i1_80199CD0[is4][is3].z + boss->obj.pos.z;
                        actor->state = 1;
                        Object_SetInfo(&actor->info, actor->obj.id);
                    }
                    is3++;
                    if (is3 > boss->swork[22]) {
                        break;
                    }
                }
                boss->swork[16] = 8;
            }

            break;
        case 2:
            is3 = 0;
            actor = gActors;
            is4 = boss->swork[23];
            temp_fs0 = boss->obj.pos.z;
            var_fv0 = -1500.0f;
            for (spF4 = 0; spF4 < ARRAY_COUNT(gActors); spF4++, actor++) {
                if (actor->obj.status == OBJ_FREE) {

                    while ((is3 > boss->swork[22]) &&
                           (gPlayer[0].pos.z + var_fv0) <= (temp_fs0 + D_i1_80199CD0[is4][is3].z)) {
                        is3++;
                    }
                    if (is3 <= boss->swork[22]) {
                        Actor_Initialize(actor);
                        actor->obj.status = OBJ_ACTIVE;
                        actor->obj.id = OBJ_ACTOR_280;
                        actor->obj.pos.x = D_i1_80199CD0[is4][is3].x;
                        actor->obj.pos.y = D_i1_80199CD0[is4][is3].y;
                        actor->obj.pos.z = D_i1_80199CD0[is4][is3].z + boss->obj.pos.z;
                        actor->obj.rot.y = 180.0f;
                        actor->state = 1;
                        Object_SetInfo(&actor->info, actor->obj.id);
                    }
                    is3++;
                    if (is3 > boss->swork[22]) {
                        break;
                    }
                }
            }
            boss->swork[16] = 8;
            break;
        case 3:
            if (boss->swork[24] == 1) {
                is3 = 0;
                actor = gActors;
                is4 = boss->swork[23];
                temp_fs0 = boss->obj.pos.z;
                var_fv0 = (gPlayer[0].pos.z + -1500.0f);
                for (spF4 = 0; spF4 < ARRAY_COUNT(gActors); spF4++, actor++) {
                    if (actor->obj.status == OBJ_FREE) {
                        while ((is3 > D_i1_80199E60[is4]) && (var_fv0) <= (temp_fs0 + D_i1_80199E6C[is4][is3].z)) {
                            is3++;
                        }
                        if (is3 <= D_i1_80199E60[is4]) {
                            Actor_Initialize(actor);
                            actor->obj.status = OBJ_ACTIVE;
                            actor->obj.id = OBJ_ACTOR_283;
                            actor->obj.pos.x = D_i1_80199E6C[is4][is3].x;
                            actor->obj.pos.y = D_i1_80199E6C[is4][is3].y;
                            actor->obj.pos.z = D_i1_80199E6C[is4][is3].z + boss->obj.pos.z;
                            actor->state = 1;
                            Object_SetInfo(&actor->info, actor->obj.id);
                        }
                        is3++;
                        if (is3 > D_i1_80199E60[is4]) {
                            break;
                        }
                    }
                }
            }
            actor = gActors;
            for (spF4 = 0; spF4 < ARRAY_COUNT(gActors); spF4++, actor++) {
                if (((actor->obj.id == OBJ_ACTOR_281) || (actor->obj.id == OBJ_ACTOR_282)) && (actor->state == 0) &&
                    (100.f <= (actor->obj.pos.z - boss->obj.pos.z)) &&
                    ((actor->obj.pos.z - boss->obj.pos.z) <= 2400.0f)) {
                    actor->state = 1;
                }
            }
            boss->swork[16] = 8;
    }
}
#else
void Venom1_Boss_Update(Boss* boss);
#pragma GLOBAL_ASM("asm/us/rev1/nonmatchings/overlays/ovl_i1/fox_ve1/Venom1_Boss_Update.s")
#endif

void Venom1_80198310(Boss* boss) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_65);
    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 0, 0, 0, 255);
    gDPSetEnvColor(gMasterDisp++, 0, 0, 0, 0);
    Matrix_Translate(gGfxMatrix, 0.0f, -5.0f + gCameraShakeY, 0.0f, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, 10.0f, 0.0f, 8.0f, MTXF_APPLY);
    Matrix_RotateX(gGfxMatrix, -90.0f * M_DTOR, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_1024AC0);
}

void Venom1_80198414(void) {
    s32 i;

    for (i = TEAM_ID_FALCO; i < ARRAY_COUNT(gTeamShields); i++) {
        gPrevPlanetTeamShields[i] = gSavedTeamShields[i];
        gPrevPlanetSavedTeamShields[i] = gSavedTeamShields[i];
        gSavedTeamShields[i] = gTeamShields[i];
    }
    gBgColor = 0xFFFF; // 248, 248, 248
    gNextGameState = GSTATE_PLAY;
    gNextLevel = LEVEL_VENOM_2;
    gNextLevelPhase = 2;
    D_ctx_80177C94 = gGoldRingCount[0];
    D_ctx_80177C9C = gPlayer[0].shields + 1;
    D_ctx_80177CA4 = gHitCount;
    D_ctx_80177CAC = gPlayer[0].wings.rightState;
    D_ctx_80177CB4 = gPlayer[0].wings.leftState;
    D_ctx_80177CBC = gRightWingHealth[0];
    D_ctx_80177CC4 = gLeftWingHealth[0];
    Audio_StopPlayerNoise(0);
    Audio_KillSfxBySource(gPlayer[0].sfxSource);
}

void Venom1_80198594(Boss* boss) {
    boss->obj.pos.z = gPlayer[0].pos.z;
    if ((boss->timer_052 <= 0) && (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_ACTIVE)) {
        Venom1_80198414();
    }
}

void Venom1_Boss_Draw(Boss* boss) {
    if (boss->swork[26] == 0) {
        Animation_DrawSkeleton(0, D_VE1_901C0F4, boss->vwork, Venom1_801937F4, Venom1_80193D64, boss, &gIdentityMatrix);
    }
    boss->state = boss->swork[9];
}

void Venom1_8019864C(PlayerShot* shot) {
    s32 i;
    s32 j;
    s32 count;
    f32* hitboxData;
    Boss* boss;
    Vec3f sp88;
    f32 temp_fs1;
    Vec3f sp78;
    Vec3f diff;

    boss = gBosses;
    for (i = 0; i < ARRAY_COUNT(gBosses); i++, boss++) {
        if ((boss->obj.id == OBJ_BOSS_VE1) && (boss->obj.status == OBJ_ACTIVE) && (boss->timer_05A == 0)) {
            temp_fs1 = shot->scale * 30.0f;
            hitboxData = boss->info.hitbox;
            count = *hitboxData++;
            if (count != 0) {
                for (j = 0; j < count; j++, hitboxData += 6) {
                    if (hitboxData[1] > -100.0f) {
                        Matrix_RotateZ(gCalcMatrix, -boss->obj.rot.z * M_DTOR, MTXF_NEW);
                        Matrix_RotateX(gCalcMatrix, -boss->obj.rot.x * M_DTOR, MTXF_APPLY);
                        Matrix_RotateY(gCalcMatrix, -boss->obj.rot.y * M_DTOR, MTXF_APPLY);

                        sp88.x = shot->obj.pos.x - boss->obj.pos.x;
                        sp88.y = shot->obj.pos.y - boss->obj.pos.y;
                        sp88.z = shot->obj.pos.z - boss->obj.pos.z;

                        Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp88, &sp78);

                        diff.x = hitboxData[4] - sp78.x;
                        diff.y = hitboxData[2] - sp78.y;
                        diff.z = hitboxData[0] - sp78.z;
                        diff.z *= 0.6f;

                        D_i1_8019B7F0[j] = ((VEC3F_MAG(&diff)) < temp_fs1) ? 1 : 0;
                    }
                }
            }
        }
    }
}

void Venom1_LevelStart(Player* player) {
    func_hud_80096A74(player);
}
