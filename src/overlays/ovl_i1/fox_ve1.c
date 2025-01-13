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
    /* 0x7C */ u16 flag;
} GoleMechLimbInfo; // size = 0x80

typedef struct {
    /* 0x0 */ f32 unk_0;
    /* 0x4 */ s16 unk_4;
    /* 0x6 */ s16 unk_6;
} UnkStruct_i1_8019AE00; // size = 0x8

typedef struct {
    /* 0x0 */ s16 index;
    /* 0x2 */ u8 unk_2; // enabled? finished? some sort of flag?
} GoleMechAnimInfo;     // size = 0x4

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
    /* 0x0 */ GoleMechAnimInfo* anim;
    /* 0x4 */ s32 pad;
} GoleMechAnimList; // size = 0x8

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
GoleMechLimbInfo sGoleMechLimbInfo[17];
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
        if ((boss->obj.status != OBJ_FREE) && (boss->obj.id == OBJ_BOSS_VE1_GOLEMECH)) {
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
        if ((boss->obj.status != OBJ_FREE) && (boss->obj.id == OBJ_BOSS_VE1_GOLEMECH)) {
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
        if ((boss->obj.status != OBJ_FREE) && (boss->obj.id == OBJ_BOSS_VE1_GOLEMECH)) {
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
        if ((boss->obj.status != OBJ_FREE) && (boss->obj.id == OBJ_BOSS_VE1_GOLEMECH)) {
            if (boss->obj.pos.z <= this->obj.pos.z) {
                D_i1_8019C0C0 = 1;
                this->obj.status = OBJ_FREE;
            }
            break;
        }
    }
}

void Venom1_Ve1TempleEntrance_Update(Ve1TempleEntrance* this) {
    switch (this->state) {
        case 0:
            if (gPlayer[0].pos.z < this->obj.pos.z) {
                gDrawBackdrop = 0;
                gDrawGround = false;

                this->state++;
            }

        case 1:
            break;
    }
}

void Venom1_Ve1Pillar1_Init(Ve1Pillar1* this) {
}

void Venom1_Ve1Pillar1_Update(Ve1Pillar1* this) {
    Scenery* templeInterior;
    f32 var_ft4;
    f32 var_ft5;
    s32 i;
    Vec3f src;
    Vec3f dest;
    f32 temp_fv1_2;
    Effect* effect;

    if (this->dmgType == DMG_BEAM) {
        this->dmgType = DMG_NONE;
        Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_REFLECT);
    }

    if ((this->state == 1) || (this->state == 2) || (this->state == 3)) {
        Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
        Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);
        Matrix_RotateZ(gCalcMatrix, this->obj.rot.z * M_DTOR, MTXF_APPLY);
    }

    switch (this->state) {
        case 0:
        case 4:
            break;

        case 1:
            var_ft5 = 450.0f;
            var_ft4 = 0.0f;

            templeInterior = &gScenery[0];
            for (i = 0; i < ARRAY_COUNT(gScenery); i++, templeInterior++) {
                if ((templeInterior->obj.id == OBJ_SCENERY_VE1_TEMPLE_INTERIOR_1) ||
                    (templeInterior->obj.id == OBJ_SCENERY_VE1_TEMPLE_INTERIOR_2) ||
                    (templeInterior->obj.id == OBJ_SCENERY_VE1_TEMPLE_INTERIOR_3)) {
                    if (((this->obj.pos.z + 1100.0f - templeInterior->obj.pos.z) < 2200.0f) &&
                        ((this->obj.pos.z + 1100.0f - templeInterior->obj.pos.z) > 0.0f)) {
                        switch (templeInterior->obj.id) {
                            case OBJ_SCENERY_VE1_TEMPLE_INTERIOR_1:
                            case OBJ_SCENERY_VE1_TEMPLE_INTERIOR_3:
                                break;

                            case OBJ_SCENERY_VE1_TEMPLE_INTERIOR_2:
                                var_ft5 = 600.0f;
                                break;
                        }

                        var_ft4 = templeInterior->obj.pos.x;
                        break;
                    }
                }
            }
            this->fwork[0] = 0.0f;

            if ((this->obj.pos.x + var_ft4) < 0.0f) {
                this->fwork[1] = 896.0f - (var_ft4 - var_ft5 - this->obj.pos.x);
                this->obj.pos.x = var_ft4 - var_ft5;

            } else {
                this->fwork[1] = 896.0f + (var_ft4 + var_ft5 - this->obj.pos.x);
                this->obj.pos.x = var_ft4 + var_ft5;
            }

            this->timer_0BC = this->iwork[2];
            AUDIO_PLAY_SFX(NA_SE_OB_POLE_MOVE, this->sfxSource, 0);
            this->state = 2;

        case 2:
            if (this->timer_0BC == 0) {
                src.x = temp_fv1_2 = Math_SmoothStepToF(&this->fwork[0], this->fwork[1], 0.7f, 80.0f, 0.01f);
                src.y = 0.0f;
                src.z = 0.0f;

                Matrix_MultVec3f(gCalcMatrix, &src, &dest);

                this->obj.pos.x += dest.x;
                this->obj.pos.y += dest.y;
                this->obj.pos.z += dest.z;

                effect = Effect_Load(OBJ_EFFECT_394);

                if (effect != NULL) {
                    effect->unk_7A = 11;
                    effect->unk_78 = effect->unk_7A;
                    effect->obj.status = OBJ_ACTIVE;

                    effect->obj.pos.x = RAND_FLOAT_CENTERED(3.0f) + this->obj.pos.x;
                    effect->obj.pos.y = RAND_FLOAT_CENTERED(3.0f) + this->obj.pos.y;
                    effect->obj.pos.z = RAND_FLOAT_CENTERED(3.0f) + this->obj.pos.z + 80.0f;

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

                    if ((this->iwork[0] % 2) != 0) {
                        effect->vel.y = -effect->vel.y;
                    }
                }

                if (fabs(temp_fv1_2) <= 5.0) {
                    this->timer_0BE = 30;
                    this->state++;
                    this->fwork[2] = this->obj.pos.x;
                    this->fwork[3] = this->obj.pos.y;
                    this->fwork[4] = this->obj.pos.z;
                }
            }
            break;

        case 3:
            src.x = __sinf((((30 - this->timer_0BE) % 10) / 10.0f) * M_PI * 2) * 5.0f;
            src.y = 0.0f;
            src.z = 0.0f;

            Matrix_MultVec3f(gCalcMatrix, &src, &dest);

            this->obj.pos.x = this->fwork[2] + dest.x;
            this->obj.pos.y = this->fwork[3] + dest.y;
            this->obj.pos.z = this->fwork[4] + dest.z;

            if (this->timer_0BE == 0) {
                this->state++;
            }
            break;
    }

    this->iwork[0]++;
}

void Venom1_80192AA4(Actor* this) {
    static Vec3f D_i1_80199FFC = { 0.0f, 460.0f, 0.0f };
    Vec3f src;
    Vec3f dest;
    f32 y;

    Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);

    if ((this->obj.rot.y <= 30.0f) || (this->obj.rot.y >= 330.0f)) {
        for (D_i1_80199FFC.x = -80.0f; D_i1_80199FFC.x <= 80.0f; D_i1_80199FFC.x += 40.0f) {
            Matrix_MultVec3fNoTranslate(gCalcMatrix, &D_i1_80199FFC, &dest);
        }
    } else {
        src.z = 0.0f;
        src.x = -80.0f;
        if (this->obj.rot.y > 90.0f) {
            src.x = 80.0f;
        }
        for (y = 0.0f; y <= 450.0f; y += 50.0f) {
            Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
            Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);
            src.y = y;
            Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);
        }
    }
}

void Venom1_Ve1Pillar2_3_Init(Actor* this) {
    this->iwork[0] = this->obj.rot.x;
    this->obj.rot.x = 0.0f;
}

void Venom1_Pillar2_3_Update(Actor* this) {
    if (this->dmgType == DMG_BEAM) {
        this->dmgType = DMG_NONE;
        Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_REFLECT);
    }

    if (this->iwork[1] > 0) {
        gControllerRumbleFlags[0] = 1;
        this->iwork[1]--;
    }

    switch (this->state) {
        case 1:
            this->timer_0BC = this->iwork[0];

        case 2:
            if (this->timer_0BC <= 0) {
                this->state++;
            }
            break;

        case 3:
            this->state++;

        case 4:
            this->fwork[0] += 0.05f;
            this->obj.rot.x += this->fwork[0];

            if (this->obj.rot.x >= 90.0f) {
                gCameraShake = 12;
                Venom1_80192AA4(this);
                this->iwork[1] = 5;
                this->obj.rot.x = 90.0f;
                AUDIO_PLAY_SFX(NA_SE_OB_POLE_BOUND, this->sfxSource, 0);
                this->state++;
            }
            break;

        case 0:
        case 5:
            break;
    }
}

void Venom1_Ve1Pillar2_Draw(Ve1Pillar2* this) {
    Matrix_Scale(gGfxMatrix, 1.0f, 0.5f, 1.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, aVe1Pillar3DL);
}

void Venom1_Ve1Pillar4_Init(Ve1Pillar4* this) {
}

void Venom1_Ve1Pillar4_Update(Ve1Pillar4* this) {
    Scenery* templeInterior;
    Vec3f sp50;
    Vec3f sp44;
    f32 sp40;
    Effect* effect394;
    s32 i;
    f32 var_ft4;

    Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);
    Matrix_RotateZ(gCalcMatrix, this->obj.rot.z * M_DTOR, MTXF_APPLY);

    switch (this->state) {
        case 0:
        case 4:
            break;

        case 1:
            var_ft4 = 0.0f;

            templeInterior = &gScenery[0];
            for (i = 0; i < ARRAY_COUNT(gScenery); i++, templeInterior++) {
                if (((templeInterior->obj.id == OBJ_SCENERY_VE1_TEMPLE_INTERIOR_1) ||
                     (templeInterior->obj.id == OBJ_SCENERY_VE1_TEMPLE_INTERIOR_2) ||
                     (templeInterior->obj.id == OBJ_SCENERY_VE1_TEMPLE_INTERIOR_3)) &&
                    ((this->obj.pos.z + 1100.0f - templeInterior->obj.pos.z) < 2200.0f) &&
                    ((this->obj.pos.z + 1100.0f - templeInterior->obj.pos.z) > 0.0f)) {
                    var_ft4 = templeInterior->obj.pos.y;
                    break;
                }
            }
            this->fwork[0] = 0.0f;
            this->fwork[1] = 1237.0f - (var_ft4 - this->obj.pos.y);
            this->obj.pos.y = var_ft4 + 1.0f;
            this->timer_0BC = this->iwork[1];
            AUDIO_PLAY_SFX(NA_SE_OB_POLE_MOVE, this->sfxSource, 0);
            this->state = 2;

        case 2:
            if (this->timer_0BC == 0) {
                sp50.y = sp40 = Math_SmoothStepToF(&this->fwork[0], this->fwork[1], 0.7f, 80.0f, 0.01f);
                sp50.x = 0.0f;
                sp50.z = 0.0f;

                Matrix_MultVec3f(gCalcMatrix, &sp50, &sp44);
                this->obj.pos.x += sp44.x;
                this->obj.pos.y += sp44.y;
                this->obj.pos.z += sp44.z;
                effect394 = Effect_Load(OBJ_EFFECT_394);
                if (effect394 != NULL) {
                    effect394->unk_7A = 11;
                    effect394->unk_78 = effect394->unk_7A;
                    effect394->obj.status = OBJ_ACTIVE;
                    effect394->obj.pos.x = this->obj.pos.x + RAND_FLOAT_CENTERED(3.0f);
                    effect394->obj.pos.y = this->obj.pos.y + RAND_FLOAT_CENTERED(3.0f);
                    effect394->obj.pos.z = this->obj.pos.z + RAND_FLOAT_CENTERED(3.0f) + 80.0f;
                    effect394->scale2 = 8.0f;
                    effect394->obj.rot.z = RAND_FLOAT(360.0f);
                    effect394->vel.x = RAND_FLOAT_CENTERED(5.0f);
                    effect394->vel.y = 10.0f + RAND_FLOAT_CENTERED(3);
                    effect394->unk_44 = 100;
                    effect394->unk_46 = -5;
                    effect394->unk_60.z = 3.0f;
                    if (Rand_ZeroOne() < 0.5f) {
                        effect394->unk_60.z = -effect394->unk_60.z;
                    }
                    if ((this->iwork[0] % 2) != 0) {
                        effect394->vel.y = -effect394->vel.y;
                    }
                }

                if (fabs(sp40) <= 5.0) {
                    this->timer_0BE = 30;
                    this->state++;
                    this->fwork[2] = this->obj.pos.x;
                    this->fwork[3] = this->obj.pos.y;
                    this->fwork[4] = this->obj.pos.z;
                }
            }
            break;

        case 3:
            sp50.x = 0.0f;
            sp50.y = __sinf((((30 - this->timer_0BE) % 10) / 10.0f) * M_PI * 2) * 5.0f;
            sp50.z = 0.0f;

            Matrix_MultVec3f(gCalcMatrix, &sp50, &sp44);

            this->obj.pos.x = this->fwork[2] + sp44.x;
            this->obj.pos.y = this->fwork[3] + sp44.y;
            this->obj.pos.z = this->fwork[4] + sp44.z;

            if (this->timer_0BE == 0) {
                this->state++;
            }
            break;
    }

    if (this->dmgType == DMG_BEAM) {
        this->dmgType = DMG_NONE;
        Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_REFLECT);
    }
    this->iwork[0]++;
}

void Venom1_Ve1MonkeyStatue_Init(Ve1MonkeyStatue* this) {
    this->scale = -1.0f;
    this->obj.pos.y += 488.0f;
}

void Venom1_Ve1MonkeyStatue_Update(Ve1MonkeyStatue* this) {
    f32* hitboxData;

    if (this->dmgType == DMG_BEAM) {
        this->dmgType = DMG_NONE;
        AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 0);
    }

    if ((this->animFrame == 38) || (this->animFrame == 58)) {
        AUDIO_PLAY_SFX(NA_SE_OB_ARM_SWING, this->sfxSource, 0);
    }
    Animation_GetFrameData(&aVe1MonkeyStatueAnim, this->animFrame, this->vwork);

    if (this->animFrame < (Animation_GetFrameCount(&aVe1MonkeyStatueAnim) - 1)) {
        this->animFrame++;
    } else {
        this->animFrame = 0;
    }

    hitboxData = this->info.hitbox;
    hitboxData[1 + (10 * 0) + 7] = this->vwork[3].y;
    hitboxData[1 + (10 * 1) + 7] = -this->vwork[2].y;
}

void Venom1_Ve1MonkeyStatue_Draw(Ve1MonkeyStatue* this) {
    Matrix_Translate(gGfxMatrix, 0.0f, -488.0f, 0.0f, MTXF_APPLY);
    Animation_DrawSkeleton(0, aVe1MonkeyStatueSkel, this->vwork, NULL, NULL, this, &gIdentityMatrix);
}

void Venom1_Ve1Generator_Update(Ve1Generator* this) {
    if (((gPlayer[0].trueZpos - this->obj.pos.z) <= 3500.0f) && ((gGameFrameCount % 4) == 0)) {
        Effect_Effect390_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 0.0f, 0.0f, 0.0f, 0.2f, 10);
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
f32 aVe1GolemechHitbox[199] = {
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

GoleMechAnimInfo sVe1GolemethAnim1[2] = { { 0, 1 }, { -1, 0 } };
GoleMechAnimInfo sVe1GolemethAnim2[4] = { { 1, 0 }, { 2, 1 }, { 3, 0 }, { -1, 0 } };
GoleMechAnimInfo sVe1GolemethAnim3[3] = { { 4, 0 }, { 5, 0 }, { -1, 0 } };
GoleMechAnimInfo sVe1GolemethAnim4[2] = { { 7, 0 }, { -1, 0 } };
GoleMechAnimInfo sVe1GolemethAnim5[2] = { { 6, 1 }, { -1, 0 } };

GoleMechAnimList sVe1GolemethAnimList[5] = {
    { sVe1GolemethAnim1, 0 }, { sVe1GolemethAnim2, 0 }, { sVe1GolemethAnim3, 0 },
    { sVe1GolemethAnim5, 0 }, { sVe1GolemethAnim4, 0 },
};

s16 D_i1_8019AD54[3] = { 0, 1, -1 };

Vec3f D_i1_8019AD5C = { 162.0f, 50.0f, 0.0f };

u8 D_i1_8019AD68[24] = {
    0, 33, 64, 97, 128, 143, 161, 192, 223, 255, 234, 213, 192, 171, 153, 129, 108, 87, 66, 45, 22, 0, 0, 0,
};

typedef struct {
    s16 unk_0;
    s16 unk_2;
    s16 unk_4;
    s16 unk_6;
} UnkStruct_i1_8019AD80;

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

void Venom1_Ve1Golemech_Init(Ve1Golemech* this) {
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

    for (i = 0; i < ARRAY_COUNTU(sGoleMechLimbInfo); i++) {
        sGoleMechLimbInfo[i].unk_00 = D_i1_8019A820[i].unk_02;
        sGoleMechLimbInfo[i].unk_02[0] = 0;

        for (j = 0; j < ARRAY_COUNT(sGoleMechLimbInfo->unk_02); j++) {
            sGoleMechLimbInfo[i].unk_02[j] = 0;
        }
        for (j = 0; j < ARRAY_COUNT(sGoleMechLimbInfo->unk_0C); j++) {
            sGoleMechLimbInfo[i].unk_0C[j].x = sGoleMechLimbInfo[i].unk_0C[j].y = sGoleMechLimbInfo[i].unk_0C[j].z =
                0.0f;
        }
        for (j = 0; j < ARRAY_COUNT(sGoleMechLimbInfo->unk_30); j++) {
            sGoleMechLimbInfo[i].unk_30[j].x = sGoleMechLimbInfo[i].unk_30[j].y = sGoleMechLimbInfo[i].unk_30[j].z =
                0.0f;
        }
        sGoleMechLimbInfo[i].unk_74 = sGoleMechLimbInfo[i].unk_78 = 0.0f;
        sGoleMechLimbInfo[i].flag = 0;
    }

    this->fwork[11] = 1.0f;

    for (i = 0; i < ARRAY_COUNTU(D_i1_8019B7F0); i++) {
        D_i1_8019B7F0[i] = 0;
    }

    for (var_v0 = 0, i = 0; i < ARRAY_COUNTU(sGoleMechLimbInfo); i++) {
        var_v0 += D_i1_8019A820[i].unk_02;
    }
    this->swork[29] = this->swork[30] = var_v0 + 100;
    Animation_GetFrameData(D_i1_8019ACD4[this->swork[5]], 0, this->vwork);
    AUDIO_PLAY_BGM(NA_BGM_BOSS_VE);
}

bool Venom1_801937F4(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    Ve1Golemech* this = (Ve1Golemech*) thisx;
    bool override;
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

    for (i = 0; i < ARRAY_COUNT(D_i1_8019A748); i++) {
        if (limbIndex == D_i1_8019A748[i].limb) {
            Matrix_Translate(gCalcMatrix, pos->x, pos->y, pos->z, MTXF_APPLY);
            Matrix_RotateZ(gCalcMatrix, rot->z * M_DTOR, MTXF_APPLY);
            Matrix_RotateY(gCalcMatrix, rot->y * M_DTOR, MTXF_APPLY);
            Matrix_RotateX(gCalcMatrix, rot->x * M_DTOR, MTXF_APPLY);
            Matrix_Mult(gGfxMatrix, gCalcMatrix, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);

            if (!(sGoleMechLimbInfo[D_i1_8019A748[i].index].flag & 1)) {
                if (sGoleMechLimbInfo[D_i1_8019A748[i].index].unk_00 > 0) {
                    if ((sGoleMechLimbInfo[D_i1_8019A748[i].index].unk_02[2] & 2) == 2) {
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
                    blue = sGoleMechLimbInfo[D_i1_8019A748[i].index].unk_74;
                    if ((blue != 0) && ((gGameFrameCount & 2) == 2)) {
                        green = sGoleMechLimbInfo[D_i1_8019A748[i].index].unk_6C;
                        red = sGoleMechLimbInfo[D_i1_8019A748[i].index].unk_64;
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
    Ve1Golemech* this = (Ve1Golemech*) thisx;
    Vec3f spAC;
    UnkStruct_i1_8019A058* var_s1;
    GoleMechLimbInfo* var_s7;
    UnkStruct_i1_8019A820* var_s6;
    f32* var_s0;
    s32 temp_s3;
    s32 var_s4;
    s32 temp1;
    s32 temp2;

    var_s0 = this->info.hitbox;
    *var_s0++ = 33.0f;
    for (spBC = 0; spBC < ARRAY_COUNTU(sGoleMechLimbInfo); spBC++) {
        temp_s3 = D_i1_8019A478[spBC][2];
        if (limbIndex == D_i1_8019A478[spBC][0]) {
            temp1 = D_i1_8019A478[spBC][1];
            if (sGoleMechLimbInfo[spBC].unk_00 > 0) {
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
    var_s7 = sGoleMechLimbInfo;

    for (spBC = 0; spBC < ARRAY_COUNTU(sGoleMechLimbInfo); spBC++, var_s6++, var_s7++) {
        if (limbIndex == var_s6->unk_00) {
            if (var_s7->flag & 8) {
                temp2 = var_s6->unk_04;
                for (var_s4 = 0; var_s4 < var_s6->unk_06; var_s4++) {
                    Matrix_MultVec3f(gCalcMatrix, &D_i1_8019A544[temp2 + var_s4], &var_s7->unk_0C[var_s4]);
                }
                var_s7->flag &= ~8;
                var_s7->flag |= 0x10;
            }
            if (var_s7->flag & 0x20) {
                Matrix_MultVec3f(gCalcMatrix, &D_tank_800C9F2C, &var_s7->unk_0C[0]);
                Matrix_GetYRPAngles(gCalcMatrix, &var_s7->unk_30[0]);
                var_s7->flag &= ~0x20;
                var_s7->flag |= 0x40;
            }
            if (var_s7->flag & 0x100) {
                var_s7->flag &= ~0x100;
                var_s7->flag |= 0x200;
            }
            if (var_s7->flag & 0x800) {
                Matrix_MultVec3f(gCalcMatrix, &D_tank_800C9F2C, &var_s7->unk_0C[1]);
                var_s7->flag &= ~0x800;
                var_s7->flag |= 0x1000;
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
    var_s7 = sGoleMechLimbInfo;

    for (spBC = 0; spBC < ARRAY_COUNTU(sGoleMechLimbInfo); spBC++, var_s6++, var_s7++) {
        if ((limbIndex == var_s6->unk_00) && (var_s7->flag & 0x200) && !((gGameFrameCount + spBC) & 2)) {
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

void Venom1_Ve1Golemech_Update(Ve1Golemech* this) {
    GoleMechAnimInfo* animation;
    Vec3f sp118[27];
    Actor* actor;
    Effect* effect;
    Vec3f sp104;
    Vec3f spF8;
    s32 spF4;
    s32 is0;
    s32 ia0;
    s32 spE8;
    s32 spE4;
    s32 is1;
    s32 is3;
    s32 is2;
    s32 is4;
    s32 is5;
    f32 spCC;
    s32 temp;
    f32 temp_fv1;
    f32 var_fv0;
    s32 is7;
    s32 spB8;
    s32 spB4;
    f32 temp_fs0;

    spE8 = 0;
    spE4 = 0;
    spB8 = 0;
    spB4 = 0;

    gBossFrameCount++;

    if (this->state >= 3) {
        D_i1_8019C0B8 = 0;
        D_i1_8019C0BC = 0;
    }

    this->swork[32]++;

    if (this->swork[31] == 0) {
        switch (this->swork[32]) {
            case 901:
                if ((gTeamShields[TEAM_ID_SLIPPY] > 0) && (gRadioState == 0)) {
                    Radio_PlayMessage(gMsg_ID_4092, RCID_SLIPPY);
                }
                break;

            case 1001:
                if (gTeamShields[TEAM_ID_SLIPPY] > 0) {
                    gShowBossHealth = true;
                    gBossHealthBar = 255;
                    this->swork[32] = 0;
                    this->swork[31]++;
                }
                break;
        }
    }

    for (spF4 = 0; spF4 < ARRAY_COUNTU(sGoleMechLimbInfo); spF4++) {
        if (sGoleMechLimbInfo[spF4].unk_02[2] > 0) {
            sGoleMechLimbInfo[spF4].unk_02[2]--;
        }
    }

    if (this->swork[10] > 0) {
        this->swork[10]--;
    }

    if (this->swork[28] > 0) {
        gControllerRumbleFlags[0] = 1;
        this->swork[28]--;
    }

    if (this->swork[16] > 0) {
        this->swork[16]--;
    }

    if ((this->swork[16] & 3) == 1) {
        for (spF4 = 0; spF4 < (RAND_INT(5.0f) + 2); spF4++) {
            effect = Effect_Load(OBJ_EFFECT_394);
            if (effect != NULL) {
                effect->obj.pos.x = this->obj.pos.x + RAND_FLOAT_CENTERED(400.0f);
                effect->obj.pos.y = this->obj.pos.y + 1250.0f;
                effect->obj.pos.z = this->obj.pos.z + RAND_FLOAT_CENTERED(400.0f);
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

    if (this->swork[10] & 2) {
        effect = Effect_Load(OBJ_EFFECT_394);
        if (effect != NULL) {
            effect->unk_78 = effect->unk_7A = 11;
            effect->obj.status = OBJ_ACTIVE;
            effect->obj.pos.x = this->obj.pos.x + 125.0f;
            effect->obj.pos.y = this->obj.pos.y;
            effect->obj.pos.z = this->obj.pos.z;
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

        effect = Effect_Load(OBJ_EFFECT_394);
        if (effect != NULL) {
            effect->unk_78 = effect->unk_7A = 11;
            effect->obj.status = OBJ_ACTIVE;
            effect->obj.pos.x = this->obj.pos.x - 125.0f;
            effect->obj.pos.y = this->obj.pos.y;
            effect->obj.pos.z = this->obj.pos.z;
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

    if (this->state <= 0) {
        switch (this->swork[20]) {
            case 0:
                break;

            case 1:
                this->fwork[13] = D_i1_8019AE00[this->swork[21]].unk_0;
                this->swork[22] = this->swork[21];
                this->swork[20]++;

            case 2:
                this->fwork[14] = 0.0f;
                this->swork[20]++;

            case 3:
                Math_SmoothStepToF(&this->fwork[14], 12.0f, 1.0f, 1.0f, 0.01f);
                Venom1_801920F0(&this->fwork[6], this->fwork[13], 1.0f, this->fwork[14], 0.01f, &spCC);
                if (fabsf(spCC) <= 45.0f) {
                    this->fwork[12] = this->fwork[13] + (SIGN_OF(spCC) * 20.0f);
                    this->swork[20]++;
                }
                break;

            case 4:
                Math_SmoothStepToF(&this->fwork[14], 12.0f, 1.0f, 1.0f, 0.01f);
                Math_SmoothStepToAngle(&this->fwork[12], this->fwork[13], 1.0f, this->fwork[14] / 5.0f, 0.01f);
                if (fabsf(Math_SmoothStepToAngle(&this->fwork[6], this->fwork[12], 1.0f, this->fwork[14], 0.01f)) <
                    2.0f) {
                    this->swork[20] = 0;
                }
                break;
        }
    }

    Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, 0);

    for (spF4 = 0; spF4 < ARRAY_COUNTU(sGoleMechLimbInfo); spF4++) {
        if (sGoleMechLimbInfo[spF4].unk_74 < sGoleMechLimbInfo[spF4].unk_78) {
            Math_SmoothStepToF(&sGoleMechLimbInfo[spF4].unk_74, sGoleMechLimbInfo[spF4].unk_78, 1.0f, 10.0f, 0.01f);
        } else {
            Math_SmoothStepToF(&sGoleMechLimbInfo[spF4].unk_74, sGoleMechLimbInfo[spF4].unk_78, 1.0f, 4.0f, 0.01f);
        }
        if (sGoleMechLimbInfo[spF4].unk_64 < sGoleMechLimbInfo[spF4].unk_68) {
            Math_SmoothStepToF(&sGoleMechLimbInfo[spF4].unk_64, sGoleMechLimbInfo[spF4].unk_68, 1.0f, 10.0f, 0.01f);
        } else {
            Math_SmoothStepToF(&sGoleMechLimbInfo[spF4].unk_64, sGoleMechLimbInfo[spF4].unk_68, 1.0f, 4.0f, 0.01f);
        }
        if (sGoleMechLimbInfo[spF4].unk_6C < sGoleMechLimbInfo[spF4].unk_70) {
            Math_SmoothStepToF(&sGoleMechLimbInfo[spF4].unk_6C, sGoleMechLimbInfo[spF4].unk_70, 1.0f, 10.0f, 0.01f);
        } else {
            Math_SmoothStepToF(&sGoleMechLimbInfo[spF4].unk_6C, sGoleMechLimbInfo[spF4].unk_70, 1.0f, 4.0f, 0.01f);
        }

        if (sGoleMechLimbInfo[spF4].flag & 4) {
            if (sGoleMechLimbInfo[spF4].unk_02[1] <= 0) {
                sGoleMechLimbInfo[spF4].flag |= 8;
                if (sGoleMechLimbInfo[spF4].unk_02[0] == 8) {
                    is4 = D_i1_8019A820[spF4].unk_08;
                    if ((is4 != -1) && (sGoleMechLimbInfo[is4].unk_00 > 0)) {
                        sGoleMechLimbInfo[is4].unk_00 = -1;
                        sGoleMechLimbInfo[is4].unk_02[0] = 16;
                        sGoleMechLimbInfo[is4].unk_02[1] = D_i1_8019A820[spF4].unk_0C;
                        sGoleMechLimbInfo[is4].flag |= 4;
                        AUDIO_PLAY_SFX(NA_SE_EN_EXPLOSION_S, this->sfxSource, 4);
                        AUDIO_PLAY_SFX(NA_SE_EN_VEBOSS_BROKEN, this->sfxSource, 4);
                    }

                    is4 = D_i1_8019A820[spF4].unk_0A;
                    if (is4 != -1) {
                        if (sGoleMechLimbInfo[is4].unk_00 > 0) {
                            sGoleMechLimbInfo[is4].unk_00 = -1;
                            sGoleMechLimbInfo[is4].unk_02[0] = 16;
                            sGoleMechLimbInfo[is4].unk_02[1] = D_i1_8019A820[spF4].unk_0C;
                            sGoleMechLimbInfo[is4].flag |= 4;
                        }
                    }
                }

                sGoleMechLimbInfo[spF4].unk_02[0]--;
                if (sGoleMechLimbInfo[spF4].unk_02[0] <= 0) {
                    sGoleMechLimbInfo[spF4].flag &= ~4;
                }
            } else {
                sGoleMechLimbInfo[spF4].unk_02[1]--;
            }
        }

        if (sGoleMechLimbInfo[spF4].flag & 0x10) {
            if ((spF4 != 14) || (sGoleMechLimbInfo[spF4].unk_00 <= 0)) {
                is4 = sGoleMechLimbInfo[spF4].unk_02[0];
                for (is7 = 0; is7 < D_i1_8019A820[spF4].unk_06; is7++) {
                    Matrix_MultVec3f(gCalcMatrix, &sGoleMechLimbInfo[spF4].unk_0C[is7], &spF8);
                    spF8.x += this->obj.pos.x + RAND_FLOAT_CENTERED(60.0f);
                    spF8.y += this->obj.pos.y + RAND_FLOAT_CENTERED(60.0f);
                    spF8.z += this->obj.pos.z;

                    is3 = D_i1_8019AD80[is4][2];
                    if (is3 > 0) {
                        func_effect_8007D2C8(spF8.x, spF8.y, spF8.z, is3);
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
                    Matrix_MultVec3f(gCalcMatrix, &sGoleMechLimbInfo[spF4].unk_0C[is7], &spF8);
                    spF8.x += this->obj.pos.x + RAND_FLOAT_CENTERED(60.0f);
                    spF8.y += this->obj.pos.y + RAND_FLOAT_CENTERED(60.0f);
                    spF8.z += this->obj.pos.z;

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
            sGoleMechLimbInfo[spF4].flag &= ~0x10;
        }

        if (sGoleMechLimbInfo[spF4].flag & 0x40) {
            actor = Game_SpawnActor(OBJ_ACTOR_DEBRIS);
            if (actor != NULL) {
                actor->obj.status = OBJ_ACTIVE;
                actor->obj.pos.x = this->obj.pos.x + sGoleMechLimbInfo[spF4].unk_0C[0].x;
                actor->obj.pos.y = this->obj.pos.y + sGoleMechLimbInfo[spF4].unk_0C[0].y;

                actor->obj.pos.z = this->obj.pos.z + sGoleMechLimbInfo[spF4].unk_0C[0].z;
                actor->obj.rot.x = sGoleMechLimbInfo[spF4].unk_30[0].x;
                actor->obj.rot.y = sGoleMechLimbInfo[spF4].unk_30[0].y;
                actor->obj.rot.z = sGoleMechLimbInfo[spF4].unk_30[0].z;
                actor->state = 57;
                actor->iwork[0] = 0;
                actor->work_048 = spF4;

                if (this->swork[25] == 0) {
                    actor->vel.x = RAND_FLOAT_CENTERED(5.0f);
                    actor->vel.y = 10.0f + RAND_FLOAT_CENTERED(2.0f);
                    actor->vel.z = 10.0f + RAND_FLOAT_CENTERED(2.0f);
                    actor->fwork[0] = 5.0f + RAND_FLOAT_CENTERED(1.0f);
                    actor->fwork[1] = 5.0f + RAND_FLOAT_CENTERED(1.0f);
                    actor->fwork[2] = 5.0f + RAND_FLOAT_CENTERED(1.0f);
                } else {
                    Matrix_RotateY(gCalcMatrix, RAND_FLOAT(2.0f) * M_PI, 0);
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
                    actor->obj.pos.x = this->obj.pos.x + sGoleMechLimbInfo[spF4].unk_0C[0].x;
                    actor->obj.pos.y = this->obj.pos.y + sGoleMechLimbInfo[spF4].unk_0C[0].y;
                    actor->obj.pos.z = this->obj.pos.z + sGoleMechLimbInfo[spF4].unk_0C[0].z;
                    actor->obj.rot.x = RAND_FLOAT(360.0f);
                    actor->obj.rot.y = RAND_FLOAT(360.0f);
                    actor->obj.rot.z = RAND_FLOAT(360.0f);
                    actor->state = 50;
                    actor->iwork[0] = RAND_INT(2) + 2;

                    if (this->swork[25] == 0) {
                        actor->vel.x = RAND_FLOAT_CENTERED(6.0f);
                        actor->vel.y = RAND_FLOAT_CENTERED(6.0f);
                        actor->vel.z = 40.0f + RAND_FLOAT_CENTERED(2.0f);
                        actor->fwork[0] = 5.0f + RAND_FLOAT_CENTERED(1.0f);
                        actor->fwork[1] = 5.0f + RAND_FLOAT_CENTERED(1.0f);
                        actor->fwork[2] = 5.0f + RAND_FLOAT_CENTERED(1.0f);
                    } else {
                        Matrix_RotateY(gCalcMatrix, RAND_FLOAT(2.0f) * M_PI, 0);
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

            sGoleMechLimbInfo[spF4].flag &= ~0x40;
            sGoleMechLimbInfo[spF4].flag |= 1;
        }

        if (sGoleMechLimbInfo[spF4].flag & 0x80) {
            if (sGoleMechLimbInfo[spF4].unk_02[4] <= 0) {
                sGoleMechLimbInfo[spF4].unk_78 = 128.0f;
                sGoleMechLimbInfo[spF4].unk_68 = (sGoleMechLimbInfo[spF4].unk_70 = 16.0f);
                sGoleMechLimbInfo[spF4].flag |= 0x100;
                if (sGoleMechLimbInfo[spF4].unk_02[3] == 7) {
                    for (is7 = 0; is7 < ARRAY_COUNT(D_i1_8019A820->unk_0E); is7++) {
                        is4 = D_i1_8019A820[spF4].unk_0E[is7];
                        if (is4 != -1) {
                            sGoleMechLimbInfo[is4].unk_02[3] = 8;
                            sGoleMechLimbInfo[is4].unk_02[4] = D_i1_8019A820[spF4].unk_16;
                            sGoleMechLimbInfo[is4].flag |= 0x80;
                        }
                    }
                }

                for (is7 = 0; is7 < D_i1_8019A820[spF4].unk_06; is7++) {
                    sGoleMechLimbInfo[spF4].unk_0C[is7].x = RAND_DOUBLE_CENTERED(4.0);
                    sGoleMechLimbInfo[spF4].unk_0C[is7].y = RAND_DOUBLE_CENTERED(4.0);
                    sGoleMechLimbInfo[spF4].unk_0C[is7].z = RAND_DOUBLE_CENTERED(4.0);
                    sGoleMechLimbInfo[spF4].unk_30[is7].x = RAND_FLOAT(360.0f);
                    sGoleMechLimbInfo[spF4].unk_30[is7].y = RAND_FLOAT(360.0f);
                    sGoleMechLimbInfo[spF4].unk_30[is7].z = RAND_FLOAT(360.0f);
                }

                sGoleMechLimbInfo[spF4].unk_02[3]--;
                if (sGoleMechLimbInfo[spF4].unk_02[3] <= 0) {
                    sGoleMechLimbInfo[spF4].unk_68 =
                        (sGoleMechLimbInfo[spF4].unk_70 = (sGoleMechLimbInfo[spF4].unk_78 = 0.0f));
                    sGoleMechLimbInfo[spF4].flag &= ~0x80;
                }
            } else {
                sGoleMechLimbInfo[spF4].unk_02[4]--;
            }
        }

        if (sGoleMechLimbInfo[spF4].flag & 0x200) {
            sGoleMechLimbInfo[spF4].flag &= ~0x200;
        }

        if (sGoleMechLimbInfo[spF4].flag & 0x1000) {
            Matrix_MultVec3f(gCalcMatrix, &D_tank_800C9F2C, &spF8);
            spF8.x += (this->obj.pos.x + sGoleMechLimbInfo[spF4].unk_0C[1].x) + RAND_FLOAT_CENTERED(60.0f);
            spF8.y += (this->obj.pos.y + sGoleMechLimbInfo[spF4].unk_0C[1].y) + RAND_FLOAT_CENTERED(60.0f);
            spF8.z += this->obj.pos.z + sGoleMechLimbInfo[spF4].unk_0C[1].z;
            func_effect_8007D2C8(spF8.x, spF8.y, spF8.z, sGoleMechLimbInfo[spF4].unk_60);
            sGoleMechLimbInfo[spF4].flag &= ~0x1000;
        }
    }

    switch (this->state) {
        case 0:
        case 1:
            is4 = 0;
            for (spF4 = 0; spF4 < ARRAY_COUNTU(sGoleMechLimbInfo); spF4++) {
                if (sGoleMechLimbInfo[spF4].unk_00 <= 0) {
                    is4++;
                }
            }

            if ((this->state == 0) && (this->swork[20] == 0)) {
                if ((is4 > 0) && (this->swork[21] < ((is4 - 1) / 5))) {
                    this->swork[21] = (is4 - 1) / 5;
                    this->swork[20] = 1;
                }
                if (D_i1_8019C0C0 == 1) {
                    D_i1_8019C0C0 = 0;
                    if (this->swork[21] < 5) {
                        this->swork[21]++;
                        this->swork[20] = 1;
                    }
                }
            }

            if (is4 == 17) {
                this->swork[9] = 2;
                this->swork[22] = 4;
                this->fwork[6] = (this->fwork[12] = (this->fwork[13] = 0.0f));
            } else if ((is4 == 16) && (this->state == 0)) {
                this->swork[9] = 1;
                this->fwork[16] = 0.0f;
                this->fwork[15] = 255.0f;
                if (this->swork[22] < 3) {
                    this->swork[22] = 3;
                }
            }
    }

    if (this->dmgType == DMG_BEAM) {
        this->dmgType = DMG_NONE;
        switch (this->state) {
            case 0:
            case 1:
                is4 = D_i1_8019A500[this->dmgPart];
                if (sGoleMechLimbInfo[is4].unk_00 > 0) {
                    if ((is4 != 14) || (this->state != 0)) {
                        sGoleMechLimbInfo[is4].unk_00 -= this->damage;
                        sGoleMechLimbInfo[is4].unk_02[2] = 15;
                        if (sGoleMechLimbInfo[is4].unk_00 <= 0) {
                            AUDIO_PLAY_SFX(NA_SE_EN_EXPLOSION_S, this->sfxSource, 4);
                            AUDIO_PLAY_SFX(NA_SE_EN_VEBOSS_BROKEN, this->sfxSource, 4);
                            sGoleMechLimbInfo[is4].unk_00 = -1;
                            sGoleMechLimbInfo[is4].unk_02[0] = 16;
                            sGoleMechLimbInfo[is4].unk_02[1] = 0;
                            sGoleMechLimbInfo[is4].flag |= 0xC;
                        } else {
                            AUDIO_PLAY_SFX(NA_SE_EN_DAMAGE_S, this->sfxSource, 4);
                            if (is4 == 14) {
                                sGoleMechLimbInfo[is4].flag |= 8;
                            }
                        }
                    } else {
                        AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
                    }
                } else {
                    AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
                }
                break;

            case 2:
                is4 = D_i1_8019A500[this->dmgPart];
                if (is4 == 15) {
                    AUDIO_PLAY_SFX(NA_SE_EN_VEBOSS_DAMAGE, this->sfxSource, 4);
                    sGoleMechLimbInfo[15].unk_02[3] = 10;
                    sGoleMechLimbInfo[15].unk_02[4] = 0;
                    sGoleMechLimbInfo[15].flag |= 0x80;

                    if (this->health > 0) {
                        this->health -= this->damage;
                        this->timer_05A = 18;
                        if (this->health <= 0) {
                            gScreenFlashTimer = 8;
                            gTeamLowHealthMsgTimer = -1;
                            gKillEventActors = true;
                            AUDIO_PLAY_SFX(NA_SE_EN_DOWN_IMPACT, this->sfxSource, 4);
                            this->health = 0;
                        }
                    }
                } else {
                    AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
                }
                break;
        }
    }

    switch (this->state) {
        case 0:
        case 1:
            for (spF4 = 0; spF4 < ARRAY_COUNT(D_i1_8019A500); spF4++) {
                if (((gGameFrameCount % 4) == 0) && (D_i1_8019B7F0[spF4] != 0)) {
                    is4 = D_i1_8019A500[spF4];
                    if ((sGoleMechLimbInfo[is4].unk_00 > 0) && ((is4 != 14) || (this->state != 0))) {
                        sGoleMechLimbInfo[is4].unk_00 -= 2;
                        if (sGoleMechLimbInfo[is4].unk_00 <= 0) {
                            sGoleMechLimbInfo[is4].unk_00 = -1;
                            sGoleMechLimbInfo[is4].unk_02[0] = 16;
                            sGoleMechLimbInfo[is4].unk_02[1] = 0;
                            sGoleMechLimbInfo[is4].flag |= 0xC;
                            AUDIO_PLAY_SFX(NA_SE_EN_EXPLOSION_S, this->sfxSource, 4);
                            AUDIO_PLAY_SFX(NA_SE_EN_VEBOSS_BROKEN, this->sfxSource, 4);
                        } else if (is4 == 14) {
                            sGoleMechLimbInfo[is4].flag |= 8;
                        }
                    }
                    D_i1_8019B7F0[spF4] = 0;
                }
            }
            break;

        case 2:
            if (((gGameFrameCount % 4) == 0) && (this->timer_05A == 0)) {
                for (spF4 = 0; spF4 < ARRAY_COUNT(D_i1_8019A500); spF4++) {
                    is4 = D_i1_8019A500[spF4];
                    if ((is4 == 15) && (D_i1_8019B7F0[spF4] != 0)) {
                        AUDIO_PLAY_SFX(NA_SE_EN_VEBOSS_DAMAGE, this->sfxSource, 4);
                        sGoleMechLimbInfo[15].unk_02[3] = 10;
                        sGoleMechLimbInfo[15].unk_02[4] = 0;
                        sGoleMechLimbInfo[15].flag |= 0x80;
                        if (this->health > 0) {
                            this->health -= 10;
                            this->timer_05A = 35;
                            if (this->health <= 0) {
                                gScreenFlashTimer = 8;
                                gTeamLowHealthMsgTimer = -1;
                                gKillEventActors = true;
                                AUDIO_PLAY_SFX(NA_SE_EN_DOWN_IMPACT, this->sfxSource, 4);
                                this->health = 0;
                            }
                        }
                    }
                    D_i1_8019B7F0[spF4] = 0;
                }
            }
            break;
    }

    is4 = 0;
    for (spF4 = 0; spF4 < ARRAY_COUNTU(sGoleMechLimbInfo); spF4++) {
        is4 += sGoleMechLimbInfo[spF4].unk_00 < 0 ? 0 : sGoleMechLimbInfo[spF4].unk_00;
    }

    this->swork[30] = this->health + is4;

    gBossHealthBar = (255.0f * this->swork[30]) / this->swork[29];

    switch (this->state) {
        case 4:
        case 5:
            break;

        case 1:
            this->fwork[6] += 5.0f;
            Math_SmoothStepToF(&this->fwork[16], this->fwork[15], 1.0f, 4.0f, 0.01f);
            break;

        case 2:
            this->fwork[9] = 200.0f / (this->health + 100.0f);
            this->fwork[8] -= this->fwork[9];
            if (this->fwork[8] < 0.0f) {
                this->fwork[8] = 22.0f;
            }
            break;

        case 3:
            this->fwork[9] = 200.0f / ((2.0f * this->health) + 100.0f);
            this->fwork[8] -= this->fwork[9];
            if (this->fwork[8] <= 0.0f) {
                this->fwork[8] = 22.0f;
            }
            break;
    }

    switch (this->swork[6]) {
        case 0:
            temp_fs0 = gPlayer[0].trueZpos + this->fwork[2];

            if (this->swork[15] == 0) {
                if (this->obj.pos.z >= temp_fs0) {
                    if (this->obj.pos.z > (gPlayer[0].trueZpos - 200.0f)) {
                        var_fv0 = Math_SmoothStepToF(&this->obj.pos.z, temp_fs0, 0.5f, 35.0f, 0.01f);
                    } else {
                        var_fv0 = Math_SmoothStepToF(&this->obj.pos.z, temp_fs0, 0.4f, 10.0f, 0.01f);
                    }
                } else {
                    var_fv0 = Math_SmoothStepToF(&this->obj.pos.z, temp_fs0, 0.2f, 25.0f, 0.01f);
                }

                this->fwork[11] = (-40.0f + var_fv0) / -40.0f;
                if (this->fwork[11] < 0.8f) {
                    this->fwork[11] = 0.8f;
                }

                if (fabsf(var_fv0) <= 2.0f) {
                    this->swork[15] = 1;
                    this->swork[14] = D_i1_8019A04C[this->swork[13]][1];
                }
            } else {
                if (((gPlayer[0].pos.z - this->obj.pos.z) < 500.0f) ||
                    ((gPlayer[0].pos.z - this->obj.pos.z) > 8000.0f)) {
                    this->swork[14] = 0;
                }
                if (this->swork[14] <= 0) {
                    this->swork[15] = 0;
                    this->swork[13]++;
                    if (this->swork[13] >= 3U) {
                        this->swork[13] = 0;
                    }
                    this->fwork[2] = D_i1_8019A04C[this->swork[13]][0];
                    this->swork[14] = D_i1_8019A04C[this->swork[13]][1];
                } else {
                    this->swork[14]--;
                }
            }
            this->vel.z = -40.0f;
            break;

        case 1:
            if ((this->vel.y <= -10.0f) && (this->swork[5] != 5)) {
                spE8 = 1;
            }

            if (this->obj.pos.y < 0.f) {
                this->obj.pos.y = 0.f;
                this->vel.y = 0.f;
                this->gravity = 0.f;
                this->swork[6] = 2;
                this->swork[10] = 16;
                gCameraShake = 40;
                this->swork[23] = RAND_FLOAT(5.0f);
                AUDIO_PLAY_SFX(NA_SE_OB_VEBOSS_LAND, this->sfxSource, 4);
                spB8 = 3;
                this->swork[28] = 5;
            }
            break;

        case 2:
            this->vel.z *= 0.7f;
            break;

        case 4:
            temp_fs0 = gPlayer[0].pos.z + this->fwork[2];
            if (temp_fs0 <= this->obj.pos.z) {
                var_fv0 = Math_SmoothStepToF(&this->obj.pos.z, temp_fs0, 0.4f, 20.0f, 0.01f);
            } else {
                var_fv0 = Math_SmoothStepToF(&this->obj.pos.z, temp_fs0, 0.2f, 30.0f, 0.01f);
            }

            if (this->state < 4) {
                this->fwork[11] = ((-40.0f) + var_fv0) / (-40.0f);
                if (this->fwork[11] < 0.8f) {
                    this->fwork[11] = 0.8f;
                }
            }

            temp_fs0 = gPlayer[0].trueZpos + this->fwork[2] - this->obj.pos.z;

            if ((fabsf(temp_fs0) <= 70.0f) && (this->state == 3)) {
                animation = sVe1GolemethAnimList[4].anim;
                is2 = animation->index;
                is1 = this->swork[4];
                this->fwork[0] = 0.0f;
                this->fwork[10] = 0.0f;
                this->fwork[11] = 1.0f;
                this->swork[7] = 2;
                this->swork[9] = 4;
                this->swork[1] = 4;
                this->swork[2] = 0;
                this->swork[6] = 5;
                this->swork[4] = is1;
                this->swork[5] = is2;
                this->timer_050 = 3;
                this->timer_052 = 150;
            }
            this->vel.z = -40.0f;
            break;

        case 5:
            this->vel.z = gPlayer[0].vel.z;
            break;

        case 3:
            Math_SmoothStepToF(&this->vel.z, 0.0f, 0.5f, 0.3f, 0.01f);
            break;

        case 6:
            break;
    }

    switch (this->swork[5]) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            Animation_GetFrameData(D_i1_8019ACD4[this->swork[5]], this->fwork[10], sp118);
            break;

        case 8:
            break;
    }

    switch (this->swork[5]) {
        case 0:
        case 1:
        case 3:
            switch (this->swork[27]) {
                case 0:
                    if (this->fwork[10] > 14.0f) {
                        AUDIO_PLAY_SFX(NA_SE_OB_VEBOSS_WALK, this->sfxSource, 4);
                        this->swork[27]++;
                    }
                    break;

                case 1:
                    if (this->fwork[10] > 45.0f) {
                        AUDIO_PLAY_SFX(NA_SE_OB_VEBOSS_WALK, this->sfxSource, 4);
                        this->swork[27]++;
                    }
                    break;

                case 2:
                    break;
            }
            break;
    }

    switch (this->swork[5]) {
        case 0:
        case 1:
        case 3:
        case 4:
        case 5:
        case 6:
            break;

        case 7:
            if (this->timer_052 >= 37) {
                if (this->timer_050 == 1) {
                    this->swork[11] |= 4;
                } else if (this->timer_050 == 0) {
                    spF8.x = this->obj.pos.x + this->fwork[3];
                    spF8.y = this->obj.pos.y + this->fwork[4];
                    spF8.z = this->obj.pos.z + this->fwork[5];
                    func_effect_8007D2C8(spF8.x, spF8.y, spF8.z, 5.0f);
                    this->timer_050 = 3;
                }
            }

            switch (this->timer_052) {
                case 126:
                    sGoleMechLimbInfo[6].flag |= 0x800;
                    sGoleMechLimbInfo[6].unk_60 = 10.0f;
                    break;

                case 123:
                    sGoleMechLimbInfo[6].flag |= 0x20;
                    break;

                case 122:
                    gCameraShake = 20;
                    this->swork[28] = 7;
                    AUDIO_PLAY_SFX(NA_SE_OB_VEBOSS_BOUND, this->sfxSource, 4);
                    sGoleMechLimbInfo[2].unk_60 = 5.0f;
                    sGoleMechLimbInfo[2].flag |= 0x800;
                    sGoleMechLimbInfo[5].flag |= 0x800;
                    sGoleMechLimbInfo[5].unk_60 = 5.0f;
                    break;

                case 121:
                    sGoleMechLimbInfo[8].flag |= 0x800;
                    sGoleMechLimbInfo[8].unk_60 = 10.0f;
                    break;

                case 119:
                    sGoleMechLimbInfo[8].flag |= 0x20;
                    break;

                case 118:
                    gCameraShake = 30;
                    this->swork[28] = 7;
                    AUDIO_PLAY_SFX(NA_SE_OB_VEBOSS_BOUND, this->sfxSource, 4);
                    sGoleMechLimbInfo[8].flag |= 0x800;
                    sGoleMechLimbInfo[8].unk_60 = 10.0f;
                    break;

                case 115:
                    sGoleMechLimbInfo[7].flag |= 0x20;
                    break;

                case 91:
                    this->swork[28] = 7;
                    AUDIO_PLAY_SFX(NA_SE_OB_VEBOSS_BOUND, this->sfxSource, 4);
                    break;

                case 78:
                    this->swork[28] = 7;
                    AUDIO_PLAY_SFX(NA_SE_OB_VEBOSS_BOUND, this->sfxSource, 4);
                    gCameraShake = 20;
                    sGoleMechLimbInfo[10].flag |= 0x800;
                    sGoleMechLimbInfo[10].unk_60 = 10.0f;
                    break;

                case 69:
                    sGoleMechLimbInfo[9].flag |= 0x20;
                    break;

                case 66:
                    this->swork[28] = 7;
                    AUDIO_PLAY_SFX(NA_SE_OB_VEBOSS_BOUND, this->sfxSource, 4);
                    sGoleMechLimbInfo[11].flag |= 0x20;
                    break;

                case 65:
                    sGoleMechLimbInfo[2].flag |= 0x20;
                    break;

                case 63:
                    sGoleMechLimbInfo[10].flag |= 0x20;
                    break;

                case 62:
                    sGoleMechLimbInfo[1].flag |= 0x20;
                    break;

                case 61:
                    sGoleMechLimbInfo->flag |= 0x20;
                    break;

                case 60:
                    spF8.x = this->obj.pos.x + this->fwork[3];
                    spF8.y = this->obj.pos.y + this->fwork[4];
                    spF8.z = this->obj.pos.z + this->fwork[5];
                    Effect386_Spawn1(spF8.x, spF8.y, spF8.z, 0, 0, 0, 25.0f, 5);
                    gFillScreenRed = (gFillScreenGreen = (gFillScreenBlue = 255));
                    gFillScreenAlpha = (gFillScreenAlphaTarget = 255);
                    break;

                case 59:
                    gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
                    gFillScreenAlpha = gFillScreenAlphaTarget = 128;
                    break;

                case 58:
                    gFillScreenAlpha = (gFillScreenAlphaTarget = 0);
                    break;

                case 50:
                    this->swork[25] = 1;
                    for (spF4 = 0; spF4 < ARRAY_COUNTU(sGoleMechLimbInfo); spF4++) {
                        if (!(sGoleMechLimbInfo[spF4].flag & 1)) {
                            sGoleMechLimbInfo[spF4].flag |= 0x20;
                        }
                    }
                    break;

                case 49:
                    Boss_AwardBonus(this);
                    gShowBossHealth = false;
                    this->swork[28] = 9;
                    AUDIO_PLAY_SFX(NA_SE_OB_VEBOSS_BOUND, this->sfxSource, 4);
                    this->swork[26] = 1;
                    this->info.hitbox = gNoHitbox;
                    this->drawShadow = false;
                    Effect_Effect383_Spawn(this->obj.pos.x, this->obj.pos.y + 10.0f, this->obj.pos.z, 40.0f);
                    gCameraShake = 40;
                    break;

                case 12:
                    gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
                    gFillScreenAlpha = 0;
                    gFillScreenAlphaTarget = 255;
                    gFillScreenAlphaStep = 5;
                    this->obj.status = OBJ_DYING;
                    this->timer_052 = 80;
                    break;
            }
            break;

        case 2:
            if (this->fwork[10] >= 16.0f) {
                switch (this->swork[18]) {
                    case 0:
                        this->swork[11] |= 1;
                        this->swork[18]++;
                        break;

                    case 1:
                        AUDIO_PLAY_SFX(NA_SE_OB_VEBOSS_ATTACK, this->sfxSource, 4);
                        gCameraShake = 40;
                        this->swork[28] = 5;
                        spB8 = 1;
                        spB4 = 1;
                        this->swork[18]++;
                        break;

                    case 2:
                        break;
                }
            }

            if (this->fwork[10] >= 43.0f) {
                switch (this->swork[19]) {
                    case 0:
                        this->swork[11] |= 2;
                        this->swork[19]++;
                        break;

                    case 1:
                        AUDIO_PLAY_SFX(NA_SE_OB_VEBOSS_ATTACK, this->sfxSource, 4);
                        gCameraShake = 40;
                        this->swork[28] = 5;
                        spB8 = 2;
                        spB4 = 1;
                        this->swork[19]++;
                        break;

                    case 2:
                        break;
                }
            }
            break;
    }

    switch (this->swork[7]) {
        case 0:
            if (this->fwork[11] < 0.9f) {
                Math_SmoothStepToF(&this->fwork[0], 0.2f, 0.5f, 0.05f, 0.01f);
                Math_SmoothStepToVec3fArray(sp118, this->vwork, 1, 27, this->fwork[0], 360.0f, 0.01f);
            } else {
                Math_SmoothStepToF(&this->fwork[0], 1.0f, 0.5f, 0.05f, 0.01f);
                Math_SmoothStepToVec3fArray(sp118, this->vwork, 1, 27, this->fwork[0], 360.0f, 0.01f);
            }
            break;

        case 1:
            Math_SmoothStepToF(&this->fwork[0], 1.0f, 0.1f, 0.05f, 0.01f);
            Math_SmoothStepToVec3fArray(sp118, this->vwork, 1, 27, this->fwork[0], 360.0f, 0.01f);
            break;

        case 2:
            Math_SmoothStepToF(&this->fwork[0], 0.7f, 0.07f, 0.05f, 0.01f);
            Math_SmoothStepToVec3fArray(sp118, this->vwork, 1, 27, this->fwork[0], 45.0f, 0.01f);
            break;
    }

    switch (this->swork[5]) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 6:
            this->fwork[10] += this->fwork[11];
            if ((s32) this->fwork[10] >= Animation_GetFrameCount(D_i1_8019ACD4[this->swork[5]])) {
                spE8 = 1;
            }
            break;

        case 4:
            if ((s32) this->fwork[10] == 17) {
                if (gPlayer[0].vel.z < 0) {
                    this->vel.z = 2.0f * gPlayer[0].vel.z;
                } else {
                    this->vel.z = 0.0f;
                }
                this->swork[6] = 1;
                this->gravity = 3.0f;
                this->vel.y = 30.0f;
            }
            if (this->fwork[10] < (Animation_GetFrameCount(D_i1_8019ACD4[this->swork[5]]) - 1)) {
                this->fwork[10] += 1.0f;
            }
            break;

        case 5:
            if (((s32) this->fwork[10]) == 2) {
                this->swork[17] = 5;
            }
            if (this->fwork[10] > 1.0f) {
                this->fwork[10] += -1.0f;
            } else if (this->swork[17] > 0) {
                this->swork[17]--;
            } else {
                spE8 = 1;
            }
            break;

        case 7:
            if (this->fwork[10] < (Animation_GetFrameCount(D_i1_8019ACD4[this->swork[5]]) - 1.0f)) {
                this->fwork[10] += this->fwork[11];
                Math_SmoothStepToF(&this->fwork[11], 0.5f, 0.7f, 0.02f, 0.01f);
                if (this->fwork[11] < 0.7f) {
                    this->fwork[11] = 0.7f;
                }
            } else {
                this->swork[9] = 5;
            }
            break;

        case 8:
            break;
    }

    temp_fv1 = gPlayer[0].pos.z - this->obj.pos.z;

    if (spE8 != 0) {
        animation = sVe1GolemethAnimList[this->swork[1]].anim;
        if (((this->swork[2] + animation)->unk_2 & 1) && (this->swork[3] != 0)) {
            spE4 = 1;
            if (this->swork[3] > 0) {
                this->swork[3]--;
            }
        }
    }

    if ((D_i1_8019C0BC != 0) && (this->state >= 3)) {
        D_i1_8019C0BC = (this->fwork[10] > 14.0f) * 0; //! FAKE
    }

    if (((D_i1_8019C0BC != 0) && (this->swork[1] != 2)) && (this->state < 3)) {
        spE8 |= 2;
        spE4 = 1;
    }

    if (spE8 != 0) {
        is0 = this->swork[1];
        animation = sVe1GolemethAnimList[is0].anim;
        is5 = (this->swork[2] - spE4) + 1;
        is1 = this->swork[4];
        if (D_i1_8019C0BC != 0) {
            if (temp_fv1 < 5000.0f) {
                this->swork[24] = D_i1_8019C0BC - 1;
                is5 = 0;
                is0 = 2;
                animation = sVe1GolemethAnimList[is0].anim;
            } else {
                spE8 &= ~2;
            }
            D_i1_8019C0BC = 0;
        }

        if (((spE8 & 1) == 1) && ((animation + is5)->index == -1)) {
            do {
                is5 = 0;
                is4 = 0;
                is1 = this->swork[4] + 1;

                if (D_i1_8019AD54[is1] == -1) {
                    is1 = 0;
                }

                is0 = D_i1_8019AD54[is1];
                if ((((is0 == 2) && (temp_fv1 < 5000.0f)) || ((is0 == 1) && (D_i1_8019C0B8 == 0))) ||
                    ((is0 == 0) && (D_i1_8019C0B8 == 1))) {
                    this->swork[4] = is1;
                    is4 = 1;
                }

                if (D_i1_8019C0B8 >= 2) {
                    is3 = (D_i1_8019C0B8 - 1) / 10;
                    ia0 = (D_i1_8019C0B8 - 1) % 10;
                    switch (is0) {
                        case 1:
                            if (is3 > 0) {
                                this->swork[3] = is3 - 1;
                            } else {
                                is4 = 1;
                                this->swork[4] = is1;
                            }
                            break;

                        case 0:
                            if (ia0 > 0) {
                                this->swork[3] = ia0 - 1;
                            } else {
                                is4 = 1;
                                this->swork[4] = is1;
                            }
                            break;

                        case 3:
                            this->swork[3] = -1;
                            break;
                    }
                }

                if ((is0 == 0) && (D_i1_8019C0B8 == 1)) {
                    D_i1_8019C0B8 = 0;
                }
            } while (is4 != 0);
        }

        animation = sVe1GolemethAnimList[is0].anim;
        is2 = (is5 + animation)->index;

        if (spE8 != 0) {
            this->swork[27] = 0;

            switch (is2) {
                case 2:
                    this->swork[23] = RAND_FLOAT(2.0f);
                    this->swork[18] = 0;
                    this->swork[19] = 0;

                case 3:
                    if ((is2 == 3) && (D_i1_8019C0B8 == 2)) {
                        is2 = 2;
                        is5--;
                        this->swork[18] = 0;
                        this->swork[19] = 0;
                    }

                case 0:

                case 1:
                    this->swork[6] = 0;
                    this->fwork[10] = 0;
                    if (this->swork[5] == 5) {
                        this->fwork[0] = 0;
                        this->swork[7] = 1;
                    } else {
                        this->swork[7] = 0;
                    }
                    break;

                case 4:
                    AUDIO_PLAY_SFX(NA_SE_OB_VEBOSS_JUMP, this->sfxSource, 4);
                    this->swork[7] = 1;
                    this->fwork[10] = 0;
                    this->gravity = 0;
                    this->fwork[0] = 0;
                    break;

                case 5:
                    this->fwork[10] = Animation_GetFrameCount(D_i1_8019ACD4[this->swork[5]]) - 1;
                    this->swork[7] = 1;
                    this->gravity = 0;
                    this->fwork[0] = 0;
                    break;

                case 6:
                    this->fwork[10] = 0;
                    break;

                case 7:
                    break;
            }

            this->swork[4] = is1;
            this->swork[1] = is0;
            this->swork[2] = is5;
            this->swork[5] = is2;
        }
    }

    if ((this->health <= 0) && (this->state == 2) && (this->swork[1] != 2) && (this->obj.pos.y <= 0)) {
        animation = sVe1GolemethAnimList[3].anim;
        is2 = animation->index;
        is1 = this->swork[4];
        this->swork[9] = 3;
        this->swork[3] = -1;
        this->fwork[10] = 0;
        this->fwork[11] = 1.0f;
        this->fwork[2] = -2000.0f;
        this->swork[7] = 0;
        this->swork[1] = 3;
        this->swork[2] = 0;
        this->swork[5] = is2;
        this->swork[4] = is1;
        this->swork[6] = 4;
        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 0);
        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 0);
    }

    switch (spB4) {
        case 1:
        case 2:
            effect = Effect_Load(OBJ_EFFECT_394);
            if (effect != NULL) {
                Matrix_MultVec3f(gCalcMatrix, (Vec3f*) (&this->fwork[3]), &spF8);
                effect->unk_78 = (effect->unk_7A = 11);
                effect->obj.pos.x = this->obj.pos.x + spF8.x;
                effect->obj.pos.y = this->obj.pos.y + spF8.y;
                effect->obj.pos.z = this->obj.pos.z + spF8.z;
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
            break;
    }

    switch (spB8) {
        case 1:
            is3 = 0;
            actor = &gActors[0];
            is4 = this->swork[23];
            temp_fs0 = this->obj.pos.z;
            var_fv0 = -1500.0f;

            for (spF4 = 0; spF4 < ARRAY_COUNT(gActors); spF4++, actor++) {
                if (actor->obj.status == OBJ_FREE) {
                    while ((is3 <= this->swork[22]) &&
                           ((temp_fs0 + D_i1_80199CD0[is4][is3].z) >= (var_fv0 + gPlayer[0].trueZpos))) {
                        is3++;
                    }

                    if (is3 <= this->swork[22]) {
                        Actor_Initialize(actor);
                        actor->obj.status = OBJ_ACTIVE;
                        actor->obj.id = OBJ_ACTOR_VE1_PILLAR_1;
                        actor->obj.pos.x = D_i1_80199CD0[is4][is3].x;
                        actor->obj.pos.y = D_i1_80199CD0[is4][is3].y;
                        actor->obj.pos.z = D_i1_80199CD0[is4][is3].z + this->obj.pos.z;
                        actor->state = 1;
                        Object_SetInfo(&actor->info, actor->obj.id);
                    }
                    is3++;
                    if (is3 > this->swork[22]) {
                        break;
                    }
                }
                this->swork[16] = 8;
            }
            break;

        case 2:
            is3 = 0;
            actor = &gActors[0];
            is4 = this->swork[23];
            temp_fs0 = this->obj.pos.z;
            var_fv0 = -1500.0f;
            for (spF4 = 0; spF4 < ARRAY_COUNT(gActors); spF4++, actor++) {
                if (actor->obj.status == OBJ_FREE) {
                    while ((is3 < this->swork[22]) &&
                           ((D_i1_80199B40[is4][is3].z + temp_fs0) >= (gPlayer[0].pos.z + var_fv0))) {
                        is3++;
                    }

                    if (is3 <= this->swork[22]) {
                        Actor_Initialize(actor);
                        actor->obj.status = OBJ_ACTIVE;
                        actor->obj.id = OBJ_ACTOR_VE1_PILLAR_1;
                        actor->obj.pos.x = D_i1_80199B40[is4][is3].x;
                        actor->obj.pos.y = D_i1_80199B40[is4][is3].y;
                        actor->obj.pos.z = D_i1_80199B40[is4][is3].z + this->obj.pos.z;
                        actor->obj.rot.y = 180.0f;
                        actor->state = 1;
                        Object_SetInfo(&actor->info, actor->obj.id);
                    }

                    is3++;
                    if (is3 > this->swork[22]) {
                        break;
                    }
                }
            }
            this->swork[16] = 8;
            break;

        case 3:
            if (this->swork[24] == 1) {
                is3 = 0;
                actor = &gActors[0];
                is4 = this->swork[23];
                temp_fs0 = this->obj.pos.z;
                var_fv0 = gPlayer[0].pos.z + (-1500.0f);

                for (spF4 = 0; spF4 < ARRAY_COUNT(gActors); spF4++, actor++) {
                    if (actor->obj.status == OBJ_FREE) {
                        while ((is3 < D_i1_80199E60[is4]) && ((D_i1_80199E6C[is4][is3].z + temp_fs0) >= var_fv0)) {
                            is3++;
                        }

                        if (is3 <= D_i1_80199E60[is4]) {
                            Actor_Initialize(actor);
                            actor->obj.status = OBJ_ACTIVE;
                            actor->obj.id = OBJ_ACTOR_VE1_PILLAR_4;
                            actor->obj.pos.x = D_i1_80199E6C[is4][is3].x;
                            actor->obj.pos.y = D_i1_80199E6C[is4][is3].y;
                            actor->obj.pos.z = D_i1_80199E6C[is4][is3].z + this->obj.pos.z;
                            actor->state = 1;
                            Object_SetInfo(&actor->info, actor->obj.id);
                        }

                        if (++is3 > D_i1_80199E60[is4]) {
                            break;
                        }
                    }
                }
            }

            for (actor = &gActors[0], spF4 = 0; spF4 < ARRAY_COUNT(gActors); spF4++, actor++) {
                if (((((actor->obj.id == OBJ_ACTOR_VE1_PILLAR_2) || (actor->obj.id == OBJ_ACTOR_VE1_PILLAR_3)) &&
                      (actor->state == 0)) &&
                     (100.f <= (actor->obj.pos.z - this->obj.pos.z))) &&
                    ((actor->obj.pos.z - this->obj.pos.z) <= 2400.0f)) {
                    actor->state = 1;
                }
            }
            this->swork[16] = 8;
    }
}

void Venom1_Ve1Golemech_SetShadow(Ve1Golemech* this) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_65);
    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 0, 0, 0, 255);
    gDPSetEnvColor(gMasterDisp++, 0, 0, 0, 0);
    Matrix_Translate(gGfxMatrix, 0.0f, -5.0f + gCameraShakeY, 0.0f, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, 10.0f, 0.0f, 8.0f, MTXF_APPLY);
    Matrix_RotateX(gGfxMatrix, -90.0f * M_DTOR, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, aOrbDL);
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
    D_ctx_80177CAC = gPlayer[0].arwing.rightWingState;
    D_ctx_80177CB4 = gPlayer[0].arwing.leftWingState;
    D_ctx_80177CBC = gRightWingHealth[0];
    D_ctx_80177CC4 = gLeftWingHealth[0];
    Audio_StopPlayerNoise(0);
    Audio_KillSfxBySource(gPlayer[0].sfxSource);
}

void Venom1_Ve1Golemech_Dying(Ve1Golemech* this) {
    this->obj.pos.z = gPlayer[0].pos.z;
    if ((this->timer_052 <= 0) && (gPlayer[0].state == PLAYERSTATE_ACTIVE)) {
        Venom1_80198414();
    }
}

void Venom1_Ve1Golemech_Draw(Ve1Golemech* this) {
    if (this->swork[26] == 0) {
        Animation_DrawSkeleton(0, D_VE1_901C0F4, this->vwork, Venom1_801937F4, Venom1_80193D64, this, &gIdentityMatrix);
    }
    this->state = this->swork[9];
}

void Venom1_8019864C(PlayerShot* shot) {
    s32 i;
    s32 j;
    s32 count;
    f32* hitboxData;
    Ve1Golemech* golemech = &gBosses[0];
    Vec3f sp88;
    f32 temp_fs1;
    Vec3f sp78;
    Vec3f diff;

    for (i = 0; i < ARRAY_COUNT(gBosses); i++, golemech++) {
        if ((golemech->obj.id == OBJ_BOSS_VE1_GOLEMECH) && (golemech->obj.status == OBJ_ACTIVE) &&
            (golemech->timer_05A == 0)) {
            temp_fs1 = shot->scale * 30.0f;
            hitboxData = golemech->info.hitbox;
            count = *hitboxData++;
            if (count != 0) {
                for (j = 0; j < count; j++, hitboxData += 6) {
                    if (hitboxData[1] > -100.0f) {
                        Matrix_RotateZ(gCalcMatrix, -golemech->obj.rot.z * M_DTOR, MTXF_NEW);
                        Matrix_RotateX(gCalcMatrix, -golemech->obj.rot.x * M_DTOR, MTXF_APPLY);
                        Matrix_RotateY(gCalcMatrix, -golemech->obj.rot.y * M_DTOR, MTXF_APPLY);

                        sp88.x = shot->obj.pos.x - golemech->obj.pos.x;
                        sp88.y = shot->obj.pos.y - golemech->obj.pos.y;
                        sp88.z = shot->obj.pos.z - golemech->obj.pos.z;

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
    Venom1_LevelStart2(player);
}
