/*
 * File: fox_ti.c
 * System: Titania
 * Description: Level: Titania
 */

#include "global.h"
#include "assets/ast_bg_planet.h"
#include "assets/ast_titania.h"
#include "assets/ast_7_ti_1.h"
#include "assets/ast_7_ti_2.h"
#include "assets/ast_8_ti.h"
#include "assets/ast_9_ti.h"
#include "assets/ast_A_ti.h"
#include "assets/ast_landmaster.h"
#include "assets/ast_enmy_planet.h"

typedef struct {
    /* 0x00 */ PosRot unk_00;
    /* 0x18 */ u16 unk_18;
} UnkStruct_i5_801BD738; // size = 0x1C

typedef struct {
    /* 0x00 */ PosRot unk_00;
    /* 0x18 */ Vec3f unk_18;
    /* 0x24 */ s16 unk_24;
    /* 0x26 */ u16 unk_26;
} UnkStruct_i5_801BBF00; // size = 0x28

typedef struct {
    s32 unk_00;
    s32 unk_04;
    Actor* actor;
    s32 unk_0C;
} UnkStruct_i5_801B8198; // size = 0x10

s32* D_i5_801BBEF0;
f32* D_i5_801BBEF4;
s32* D_i5_801BBEF8;
UnkStruct_i5_801BBF00 D_i5_801BBF00[67];
Vec3f D_i5_801BC978[92];
Vec3f D_i5_801BCDC8[92];
Vec3f D_i5_801BD218[92];
s16 D_i5_801BD668[34];
f32 D_i5_801BD6B0[34];
UnkStruct_i5_801BD738 D_i5_801BD738[3][9];
PosRot D_i5_801BDA30[10];
f32 D_i5_801BDB20[3][151];

f32 D_i5_801B7360[25][4] = {
    { 165.0f, 120.0f, 0.0f, 90.0f },    { 127.5f, 7.5f, 0.0f, 90.0f },      { 7.5f, -112.5f, 0.0f, 90.0f },
    { 255.0f, 285.0f, -60.0f, 60.0f },  { 255.0f, 285.0f, 60.0f, 60.0f },   { 247.5f, 120.0f, -90.0f, 75.0f },
    { 247.5f, 120.0f, 90.0f, 75.0f },   { 217.5f, -75.0f, -135.0f, 90.0f }, { 217.5f, -75.0f, 135.0f, 90.0f },
    { 90.0f, -172.5f, -157.5f, 60.0f }, { 90.0f, -172.5f, 157.5f, 60.0f },  { 72.0f, 12.0f, -3.0f, 30.0f },
    { 124.5f, 12.0f, -3.0f, 22.5f },    { 84.0f, 19.5f, -3.0f, 45.0f },     { 72.0f, 12.0f, 3.0f, 37.5f },
    { 124.5f, 12.0f, 3.0f, 22.5f },     { 84.0f, 19.5f, 3.0f, 45.0f },      { 277.5f, -55.5f, -31.5f, 30.0f },
    { 187.5f, -63.0f, -33.0f, 45.0f },  { 60.0f, -25.5f, -33.0f, 67.5f },   { 117.0f, -3.0f, -18.0f, 45.0f },
    { 277.5f, -55.5f, 31.5f, 30.0f },   { 187.5f, -63.0f, 33.0f, 45.0f },   { 60.0f, -25.5f, 33.0f, 67.5f },
    { 117.0f, -3.0f, 18.0f, 45.0f }
};

u8 D_i5_801B74F0[9][3] = {
    { 13, 0, 11 }, { 1, 11, 2 }, { 2, 13, 1 }, { 3, 14, 2 }, { 4, 16, 1 },
    { 5, 17, 3 },  { 6, 20, 1 }, { 7, 21, 3 }, { 8, 24, 1 },
};

bool D_i5_801B750C[3] = { false, false, false };

f32 D_i5_801B7518[2] = { 20.0f, 60.0f };

void Titania_80188F30(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        D_i5_801B750C[i] = false;
    }
    D_MA_801BA1E8 = 99;
}

void Titania_Effect368_Update(Effect368* this) {
    if (this->timer_50 == 0) {
        this->unk_44 -= 16;
        if (this->unk_44 < 17) {
            Object_Kill(&this->obj, this->sfxSource);
        }
    }
}

void Titania_Effect368_Draw(Effect368* this) {
    Matrix_Scale(gGfxMatrix, this->scale2 * 0.5f, this->scale2, this->scale2, MTXF_APPLY);
    Matrix_RotateX(gGfxMatrix, -(M_DTOR * 90), MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, this->unk_44);
    gSPDisplayList(gMasterDisp++, D_landmaster_3007E70);
}

void Titania_Effect368_Setup(Effect368* this, f32 xPos, f32 yPos, f32 zPos, f32 yRot, f32 scale2) {
    Effect_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_EFFECT_368;
    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;
    this->obj.rot.y = yRot;
    this->scale2 = scale2;
    this->timer_50 = 25;
    this->unk_44 = 255;
    Object_SetInfo(&this->info, this->obj.id);
}

void Titania_Effect368_Spawn(f32 xPos, f32 yPos, f32 zPos, f32 yRot, f32 scale2) {
    s32 i;

    for (i = 50; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Titania_Effect368_Setup(&gEffects[i], xPos, yPos, zPos, yRot, scale2);
            break;
        }
    }
}

void Titania_TiTerrain_Update(TiTerrain* this) {
    Ground_801B49D0(this);
}

Vec3f D_i5_801B7520 = { -150.0f, 0.0f, 0.0f };

void Titania_TiDesertRover_PostLimbDraw(s32 limbIndex, Vec3f* rot, void* data) {
    TiDesertRover* this = (TiDesertRover*) data;

    if (limbIndex == 2) {
        Matrix_MultVec3f(gCalcMatrix, &D_i5_801B7520, (Vec3f*) &this->fwork[0]);
    }
}

void Titania_801891F4(TiDesertRover* this) {
    f32 temp_fs0;
    f32 temp_fs1;
    f32 var_fv1;
    f32 temp;
    f32 temp2;

    temp_fs0 = gPlayer[0].pos.x - this->obj.pos.x;
    temp_fs1 = (gPlayer[0].trueZpos + gPlayer[0].camDist) - this->obj.pos.z;

    var_fv1 = Math_RadToDeg(Math_Atan2F(temp_fs0, temp_fs1));

    if ((var_fv1 > 45.0f) && (var_fv1 < 180.0f)) {
        var_fv1 = 45.0f;
    }
    if ((var_fv1 < 315.0f) && (var_fv1 > 180.0f)) {
        var_fv1 = 315.0f;
    }

    Math_SmoothStepToAngle(&this->obj.rot.y, var_fv1, 0.2f, 6.0f, 0.01f);
    temp_fs0 = (this->obj.pos.x + this->fwork[0]) - gPlayer[0].pos.x;
    temp2 = (this->obj.pos.y + this->fwork[1]) - (gPlayer[0].pos.y + 30.0f);
    temp_fs1 = ((this->obj.pos.z + this->fwork[2]) - gPlayer[0].trueZpos) + gPlayer[0].camDist;
    temp = sqrtf(SQ(temp_fs0) + SQ(temp_fs1));
    Math_SmoothStepToAngle(&this->fwork[5], Math_RadToDeg(Math_Atan2F(temp2, temp)), 0.2f, 5.0f, 0.01f);
}

void Titania_80189380(TiDesertRover* this) {
    Vec3f sp8C;
    Vec3f sp80;
    Vec3f sp74;
    Vec3f sp68;
    Vec3f sp5C;
    Vec3f sp50;
    Vec3f sp44;
    Vec3f pad;

    sp50.x = this->fwork[0];
    sp50.y = this->fwork[1];
    sp50.z = this->fwork[2];

    sp44.x = gPlayer[0].pos.x - this->obj.pos.x;
    sp44.y = gPlayer[0].pos.y - this->obj.pos.y;
    sp44.z = gPlayer[0].pos.z - this->obj.pos.z;

    Matrix_RotateZ(gCalcMatrix, -this->obj.rot.z * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -this->obj.rot.x * M_DTOR, MTXF_APPLY);
    Matrix_RotateY(gCalcMatrix, -this->obj.rot.y * M_DTOR, MTXF_APPLY);

    Matrix_MultVec3f(gCalcMatrix, &sp44, &sp8C);

    Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);
    Matrix_RotateZ(gCalcMatrix, this->obj.rot.z * M_DTOR, MTXF_APPLY);

    Matrix_MultVec3f(gCalcMatrix, &sp50, &sp8C);

    sp80.x = this->obj.pos.x + sp8C.x;
    sp80.y = this->obj.pos.y + sp8C.y;
    sp80.z = this->obj.pos.z + sp8C.z;

    sp74.x = this->fwork[5];
    sp74.y = this->obj.rot.y;
    sp74.z = 0.0f;

    sp68.x = this->obj.rot.x;
    sp68.y = this->obj.rot.y;
    sp68.z = this->obj.rot.z;

    sp5C.x = 0.0f;
    sp5C.y = 0.0f;
    sp5C.z = 70.0f;

    func_effect_8007EE68(OBJ_EFFECT_ENEMY_LASER_1, &sp80, &sp74, &sp68, &sp5C, 1.0f);
    sp80.y += 20.0f;
    func_effect_8007EE68(OBJ_EFFECT_ENEMY_LASER_1, &sp80, &sp74, &sp68, &sp5C, 1.0f);
}

Vec3f D_i5_801B752C = { -50.0f, 0.0f, -20.0f };
Vec3f D_i5_801B7538 = { 50.0f, 0.0f, -20.0f };

void Titania_TiDesertRover_Update(TiDesertRover* this) {
    Vec3f sp54;
    Vec3f sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;

    this->iwork[2]++;

    switch (this->state) {
        case 0:
            AUDIO_PLAY_SFX(NA_SE_EN_TANK_ENGINE, this->sfxSource, 4);
            if (this->obj.rot.z > 1.0f) {
                this->iwork[0] = 1;
            }
            this->state = 1;
            /* fallthrough */
        case 1:
            this->fwork[7] = 20.0f;
            if (fabsf(this->obj.pos.z - gPlayer[0].trueZpos) < 3000.0f) {
                this->state = 2;
                this->timer_0BC = 30;
            }
            break;

        case 2:
            if (this->iwork[0] == 1) {
                this->fwork[7] = 5.0f;
                if (fabsf(this->obj.pos.z - gPlayer[0].trueZpos) < 200.0f) {
                    this->fwork[7] = 0.0f;
                }
                Titania_801891F4(this);
            }

            if (this->timer_0BC == 0) {
                this->timer_0BC = 40;
                Titania_80189380(this);
                if ((fabsf(this->obj.pos.z - gPlayer[0].trueZpos) > 200.0f) && (this->iwork[0] == 1)) {
                    this->fwork[6] = -10.0f;
                }
            }
            break;
    }

    Ground_801B6E20(this->obj.pos.x, this->obj.pos.z + gPathProgress, &sp44, &sp3C, &sp40);
    this->obj.pos.y = sp3C;

    if (this->obj.rot.x < sp44 * M_RTOD) {
        this->obj.rot.x += 2.0f;
    }
    if (sp44 * M_RTOD < this->obj.rot.x) {
        this->obj.rot.x -= 2.0f;
    }

    if (this->obj.rot.z < sp40 * M_RTOD) {
        this->obj.rot.z += 2.0f;
    }
    if (sp40 * M_RTOD < this->obj.rot.z) {
        this->obj.rot.z -= 2.0f;
    }

    Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
    Matrix_Push(&gCalcMatrix);

    if (((this->iwork[2] % 2) == 0) && ((this->obj.pos.z + gPathProgress) > -3800.0f)) {
        Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);
        Matrix_RotateZ(gCalcMatrix, this->obj.rot.z * M_DTOR, MTXF_APPLY);
        Matrix_MultVec3fNoTranslate(gCalcMatrix, &D_i5_801B752C, &sp48);
        Titania_Effect368_Spawn(this->obj.pos.x + sp48.x, this->obj.pos.y + sp48.y, this->obj.pos.z + sp48.z,
                                this->obj.pos.y, 1.3f);
        Matrix_MultVec3fNoTranslate(gCalcMatrix, &D_i5_801B7538, &sp48);
        Titania_Effect368_Spawn(this->obj.pos.x + sp48.x, this->obj.pos.y + sp48.y, this->obj.pos.z + sp48.z,
                                this->obj.pos.y, 1.3f);
    }

    Math_SmoothStepToF(&this->fwork[6], this->fwork[7], 0.1f, 2.0f, 0.00001f);
    Matrix_Pop(&gCalcMatrix);

    sp54.x = 0.0f;
    sp54.y = 0.0f;
    sp54.z = this->fwork[6];

    Matrix_MultVec3f(gCalcMatrix, &sp54, &sp48);

    this->vel.x = sp48.x;
    this->vel.y = sp48.y;
    this->vel.z = sp48.z;

    if (this->dmgType > DMG_NONE) {
        if (Rand_ZeroOne() <= 0.25f) {
            this->itemDrop = DROP_SILVER_RING_50p;
        } else {
            this->itemDrop = DROP_NONE;
        }
        Actor_Despawn(this);
        this->info.bonus = 0;
        func_effect_8007D2C8(this->obj.pos.x, this->obj.pos.y + 30.0f, this->obj.pos.z, 8.0f);
        Effect_Effect390_Spawn(this->obj.pos.x, this->obj.pos.y + 30.0f, this->obj.pos.z, this->vel.x, this->vel.y,
                               this->vel.z, 0.1f, 30);
        Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_EXPLOSION_S);
        Object_Kill(&this->obj, this->sfxSource);
    }
}

void Titania_TiDesertRover_Draw(TiDesertRover* this) {
    Animation_GetFrameData(&aTi1DesertRoverAnim, 0, this->vwork);
    this->vwork[3].z = this->fwork[5] + 270.0f;
    Animation_DrawSkeleton(1, aTi1DesertRoverSkel, this->vwork, NULL, Titania_TiDesertRover_PostLimbDraw, this,
                           &gIdentityMatrix);
}

Vec3f D_i5_801B7544 = { 0.0f, -50.0f, 178.0f };

void Titania_TiFekuda_Init(TiFekuda* this) {
    f32 sp2C;

    Ground_801B6E20(this->obj.pos.x, this->obj.pos.z + gPathProgress, &sp2C, &this->obj.pos.y, &sp2C);
    this->health = 10;
    this->info.hitbox = SEGMENTED_TO_VIRTUAL(aTiFekudaHitbox);
    Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);
    Matrix_RotateZ(gCalcMatrix, this->obj.rot.z * M_DTOR, MTXF_APPLY);
    Matrix_MultVec3f(gCalcMatrix, &D_i5_801B7544, (Vec3f*) &this->fwork[0]);
    this->fwork[0] += this->obj.pos.x;
    this->fwork[1] += this->obj.pos.y;
    this->fwork[2] += this->obj.pos.z;
}

void Titania_TiFekuda_Update(TiFekuda* this) {
    static Vec3f D_i5_801B7550 = { 0.0f, -50.0f, 178.0f };
    static Vec3f D_i5_801B755C = { 0.0f, 0.0f, 90.0f };
    Vec3f sp64;
    Vec3f sp58;
    Vec3f sp4C;
    Vec3f sp40;
    f32 temp;

    if (this->health > 0) {
        if (this->dmgType != DMG_NONE) {
            this->dmgType = DMG_NONE;
            this->timer_0C6 = 15;
            this->health -= this->damage;
            if (this->health <= 0) {
                this->health = 0;
                AUDIO_PLAY_SFX(NA_SE_EN_EXPLOSION_S, this->sfxSource, 4);
                this->lockOnTimers[TEAM_ID_FOX] = this->itemDrop = 0;
                this->info.targetOffset = 0.0f;
                Actor_Despawn(this);
                this->info.bonus = 0;
                this->info.hitbox = SEGMENTED_TO_VIRTUAL(D_TI_6006924);
                func_effect_8007D0E0(this->fwork[0], this->fwork[1], this->fwork[2], 2.0f);
            }
        }

        if (this->timer_0BC >= 15) {
            sp4C.x = gPlayer[0].pos.x - this->obj.pos.x;
            sp4C.y = (gPlayer[0].pos.y + 30.0f) - this->obj.pos.y;
            sp4C.z = gPlayer[0].pos.z - this->obj.pos.z;
            Matrix_RotateZ(gCalcMatrix, -this->obj.rot.z * M_DTOR, MTXF_NEW);
            Matrix_RotateX(gCalcMatrix, -this->obj.rot.x * M_DTOR, MTXF_APPLY);
            Matrix_RotateY(gCalcMatrix, -this->obj.rot.y * M_DTOR, MTXF_APPLY);
            Matrix_MultVec3f(gCalcMatrix, &sp4C, &sp64);
            sp58.x = sp64.x - D_i5_801B7550.x;
            sp58.y = sp64.y - D_i5_801B7550.y;
            sp58.z = sp64.z - D_i5_801B7550.z;
            temp = sqrtf(SQ(sp58.x) + SQ(sp58.z));
            this->fwork[5] = Math_RadToDeg(-Math_Atan2F(sp58.y, temp));
            this->fwork[6] = Math_RadToDeg(Math_Atan2F(sp58.x, sp58.z));
            Math_SmoothStepToAngle(&this->fwork[3], this->fwork[5], 0.2f, 5.0f, 0.01f);
            Math_SmoothStepToAngle(&this->fwork[4], this->fwork[6], 0.2f, 5.0f, 0.01f);

            if ((this->fwork[4] > 45.0f) && (this->fwork[4] < 180.0f)) {
                this->fwork[4] = 45.0f;
            }
            if ((this->fwork[4] < 315.0f) && (this->fwork[4] > 180.0f)) {
                this->fwork[4] = 315.0f;
            }

            if ((this->fwork[3] > 45.0f) && (this->fwork[3] < 180.0f)) {
                this->fwork[3] = 45.0f;
            }
            if ((this->fwork[3] < 315.0f) && (this->fwork[3] > 180.0f)) {
                this->fwork[3] = 315.0f;
            }
        }

        Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
        Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);
        Matrix_RotateZ(gCalcMatrix, this->obj.rot.z * M_DTOR, MTXF_APPLY);

        Matrix_MultVec3f(gCalcMatrix, &D_i5_801B7550, &sp64);

        sp40.x = this->fwork[3];
        sp40.y = this->fwork[4];
        sp40.z = 0.0f;

        if ((this->timer_0BC < 15) && ((this->timer_0BC % 7) == 0)) {
            func_effect_8007EE68(OBJ_EFFECT_ENEMY_LASER_1, (Vec3f*) &this->fwork[0], &sp40, &this->obj.rot,
                                 &D_i5_801B755C, 1.0f);
            if (this->timer_0BC == 0) {
                this->timer_0BC = 90;
            }
        }
    } else if (((gGameFrameCount % 8) == 0) && (Rand_ZeroOne() < 0.5f)) {
        AUDIO_PLAY_SFX(NA_SE_EN_BROKEN_SPARK, this->sfxSource, 4);
        Effect_Effect390_Spawn(this->fwork[0], this->fwork[1], this->fwork[2], 0.0f, 0.0f, 0.0f, 0.1f, 7);
        this->timer_0C6 = 4;
    }
}

void Titania_TiFekuda_Draw(TiFekuda* this) {
    gSPDisplayList(gMasterDisp++, aTi1FekudaDL);
    Matrix_Translate(gGfxMatrix, 0.0f, -50.0f, 178.0f, MTXF_APPLY);
    Matrix_RotateY(gGfxMatrix, this->fwork[4] * M_DTOR, MTXF_APPLY);
    Matrix_RotateX(gGfxMatrix, this->fwork[3] * M_DTOR, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    if (this->health != 0) {
        gSPDisplayList(gMasterDisp++, aTi1FekudaGun1DL);
        RCP_SetupDL(&gMasterDisp, SETUPDL_33);
        gSPDisplayList(gMasterDisp++, aTi1FekudaGun2DL);
    }
}

f32 sTiBoulderHitbox[7] = { 1.0f, 0.0f, 25.0f, 0.0f, 12.0f, 0.0f, 12.0f };

Gfx* D_TI_801B7584[10] = {
    D_TI1_700DDF0, D_TI1_700D9B0, D_TI1_700DF70, D_TI1_700DC50, D_TI1_700DED0,
    D_TI1_700DAD0, D_TI1_700DBB0, D_TI1_700E030, D_TI1_700D880, D_TI1_700D740,
};

void Titania_TiBoulder_Setup(TiBoulder* this, f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel) {
    Actor_Initialize(this);
    this->obj.status = OBJ_ACTIVE;
    this->obj.id = OBJ_ACTOR_TI_BOULDER;
    this->timer_0BC = RAND_INT(20.0f) + 20;
    this->timer_0C2 = 8;
    this->vel.x = xVel;
    this->vel.y = yVel;
    this->vel.z = zVel;
    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;
    this->scale = RAND_FLOAT(0.2f) + 0.3f;
    Object_SetInfo(&this->info, this->obj.id);
    this->info.hitbox = SEGMENTED_TO_VIRTUAL(sTiBoulderHitbox);
}

void Titania_TiBoulder_Spawn(f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gActors); i++) {
        if (gActors[i].obj.status == OBJ_FREE) {
            Titania_TiBoulder_Setup(&gActors[i], xPos, yPos, zPos, xVel, yVel, zVel);
            gActors[i].info.damage = 0;
            break;
        }
    }
}

void Titania_TiBoulder_Spawn2(TiBoulder* this) {
    s32 i;

    for (i = 0; i < 4; i++) {
        Titania_TiBoulder_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, RAND_FLOAT_CENTERED(40.0f),
                                RAND_FLOAT_CENTERED(40.0f), RAND_FLOAT(-20.0f));
    }
}

void Titania_TiBoulder_Update(TiBoulder* this) {
    f32 temp_fv0;
    f32 temp_fv1;
    f32 sp4C;
    f32 sp48;
    f32 sp44;

    this->drawShadow = true;

    if ((this->scale != 1.0f) && (this->dmgType == DMG_COLLISION)) {
        Object_Kill(&this->obj, this->sfxSource);
    }

    if (this->dmgType != DMG_NONE) {
        this->dmgType = DMG_NONE;
        this->timer_0C6 = 15;
        this->health += this->damage;
        if (this->scale == 1.0f) {
            if (this->health >= 10) {
                Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_OB_EXPLOSION_S);
                if ((Actor*) this->iwork[0] != NULL) {
                    ((Actor*) this->iwork[0])->iwork[this->iwork[1]] = 0;
                }
                Effect_Effect359_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 8.0f, 255, 8, 1);
                if (Rand_ZeroOne() < 0.3f) {
                    this->itemDrop = DROP_SILVER_RING;
                } else {
                    Titania_TiBoulder_Spawn2(this);
                    this->itemDrop = DROP_NONE;
                }
                Actor_Despawn(this);
                this->info.bonus = 0;
            }
            Object_Kill(&this->obj, this->sfxSource);
        } else {
            Effect_Effect359_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 8.0f, 255, 8, 1);
            Object_Kill(&this->obj, this->sfxSource);

            if ((Actor*) this->iwork[0] != NULL) {
                ((Actor*) this->iwork[0])->iwork[this->iwork[1]] = 0;
            }
        }
    }

    if (this->work_046 == 2) {
        this->gravity = 0.0f;
        Ground_801B6E20(this->obj.pos.x, this->obj.pos.z + gPathProgress, &sp4C, &sp44, &sp48);
        this->fwork[0] = sp4C;
        this->fwork[1] = sp44;
        this->fwork[2] = sp48;
        return;
    }

    this->gravity = 3.0f;
    Ground_801B6E20(this->obj.pos.x, this->obj.pos.z + gPathProgress, &sp4C, &sp44, &sp48);
    this->fwork[0] = sp4C;
    this->fwork[1] = sp44;
    this->fwork[2] = sp48;
    temp_fv1 = (this->scale * 50.0f);

    if (this->obj.pos.y > sp44 + temp_fv1) {
        this->work_046 = 0;
    } else {
        this->obj.pos.y = sp44 + temp_fv1;
        if (this->work_046 == 0) {
            if (this->vel.y < -6.0f) {
                AUDIO_PLAY_SFX(NA_SE_OB_BOUND_M, this->sfxSource, 4);
            }
            if (this->vel.y < 0.0f) {
                this->vel.y = -this->vel.y * 0.2f;
            }
            this->vel.x -= (10.0f * sp48) / (M_DTOR * 90);
            this->vel.z += (10.0f * sp4C) / (M_DTOR * 90);
            if (this->vel.y < 10.0f) {
                this->vel.y = 0.0f;
            }
            this->work_046 = 1;
        } else {
            if ((s32) sp48 == 0) {
                this->vel.x *= 0.9;
            }
            if ((s32) sp4C == 0) {
                this->vel.z *= 0.9;
            }
            this->vel.y = 0.0f;
        }
        this->vel.x -= (3.0f * sp48) / (M_DTOR * 90);
        this->vel.z += (3.0f * sp4C) / (M_DTOR * 90);
    }

    temp_fv1 = this->scale * 314.0f;

    if (this->vel.x != 0.0f) {
        this->obj.rot.x += ((sqrtf(SQ(this->vel.x) + SQ(this->vel.z)) * 360.0f) / temp_fv1) * SIGN_OF(this->vel.x);
    } else {
        this->obj.rot.x += ((sqrtf(SQ(this->vel.x) + SQ(this->vel.z)) * 360.0f) / temp_fv1) * SIGN_OF(this->vel.z);
    }

    this->obj.rot.y = Math_RadToDeg(Math_Atan2F(this->vel.x, this->vel.z));

    if (this->obj.rot.y >= 180.0f) {
        this->obj.rot.y -= 180.0f;
    }
    if (this->obj.rot.y < 0) {
        this->obj.rot.y += 180.0f;
    }
}

void Titania_TiBoulder_Draw(TiBoulder* this) {
    if (this->scale != 1.0f) {
        Matrix_Scale(gGfxMatrix, this->scale, this->scale, this->scale, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
    }
    gSPDisplayList(gMasterDisp++, aTiBoulderDL);
}

void Titania_TiLandmine_Update(TiLandmine* this) {
    f32 sp3C;
    f32 sp38;
    f32 sp34;

    switch (this->state) {
        case 0:
            this->gravity = 1.0f;
            Ground_801B6E20(this->obj.pos.x, this->obj.pos.z + gPathProgress, &sp3C, &sp34, &sp38);
            if (this->obj.pos.y <= (sp34 + 3.0f)) {
                AUDIO_PLAY_SFX(NA_SE_OB_SAND_BOUND_S, this->sfxSource, 4);
                this->obj.pos.y = sp34 + 3.0f;
                this->obj.rot.x = sp3C * (M_RTOD);
                this->obj.rot.z = sp38 * (M_RTOD);
                this->vel.y = 0.0f;
                this->gravity = 0.0f;
                this->state++;
            }
            break;

        case 1:
            break;
    }

    switch (this->dmgType) {
        case 1:
            AUDIO_PLAY_SFX(NA_SE_EN_MABOSS_REFLECT, this->sfxSource, 4);
            break;

        case 2:
            this->itemDrop = DROP_NONE;
            Actor_Despawn(this);
            this->info.bonus = 0;
            func_effect_8007D2C8(this->obj.pos.x, this->obj.pos.y + 10.0f, this->obj.pos.z, 6.0f);
            Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_EXPLOSION_M);
            Object_Kill(&this->obj, this->sfxSource);
            break;

        case 3:
            Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_EXPLOSION_M);
            func_effect_8007D2C8(this->obj.pos.x, this->obj.pos.y + 50.0f, this->obj.pos.z, (10.0f / 3.0f));
            gPlayer[0].vel.y = 20.0f;
            gPlayer[0].pos.y += 15.0f;
            gPlayer[0].rollState = 1;
            gPlayer[0].rollTimer = 15;
            gPlayer[0].rollRate = 20;
            if (this->obj.pos.x < gPlayer[0].pos.x) {
                gPlayer[0].rollRate = -20;
            }
            Object_Kill(&this->obj, this->sfxSource);
            break;
    }
    this->dmgType = DMG_NONE;
}

Vec3f D_i5_801B75AC = { -70.0f, 50.0f, 212.0f };
Vec3f D_i5_801B75B8 = { 70.0f, 50.0f, 212.0f };

void Titania_TiRasco_Init(TiRasco* this) {
    Vec3f sp68[2];
    s32 i;
    s32 k;
    Actor* actorPtr;
    f32 sp58;
    f32 sp54;

    this->fwork[0] = this->obj.rot.z;
    this->fwork[1] = this->obj.rot.x;

    this->obj.rot.z = 0.0f;
    this->obj.rot.x = 0.0f;

    Ground_801B6E20(this->obj.pos.x, this->obj.pos.z + gPathProgress, &sp54, &sp58, &sp54);

    this->obj.pos.y = sp58;

    Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &D_i5_801B75AC, &sp68[0]);
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &D_i5_801B75B8, &sp68[1]);

    k = 0;

    for (actorPtr = &gActors[0], i = 0; i < ARRAY_COUNT(gActors); i++, actorPtr++) {
        if (actorPtr->obj.status == OBJ_FREE) {
            Actor_Initialize(actorPtr);
            actorPtr->obj.status = OBJ_INIT;
            actorPtr->obj.id = OBJ_ACTOR_TI_BOULDER;
            actorPtr->obj.pos.x = this->obj.pos.x + sp68[k].x;
            actorPtr->obj.pos.y = this->obj.pos.y + sp68[k].y;
            actorPtr->obj.pos.z = this->obj.pos.z + sp68[k].z;
            actorPtr->work_046 = 2;
            actorPtr->iwork[0] = (uintptr_t) this;
            actorPtr->iwork[1] = k;
            Object_SetInfo(&actorPtr->info, actorPtr->obj.id);
            this->iwork[k] = (uintptr_t) actorPtr;
            k++;
            if (k >= 2) {
                break;
            }
        }
    }

    this->health = 40;

    if (k < 2) {
        for (i = 0; i < k; i++) {
            Object_Kill(&gActors[this->iwork[k]].obj, gActors[this->iwork[k]].sfxSource);
        }
        Object_Kill(&this->obj, this->sfxSource);
    }
}

bool Titania_8018AFD4(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    *dList = NULL;
    return false;
}

bool Titania_TiRasco_OverrideLimbDraw(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    if ((limbIndex == 2) || (limbIndex == 3) || (limbIndex == 4)) {
        Matrix_Translate(gCalcMatrix, pos->x, pos->y, pos->z, MTXF_APPLY);
        Matrix_RotateZ(gCalcMatrix, rot->z * M_DTOR, MTXF_APPLY);
        Matrix_RotateY(gCalcMatrix, rot->y * M_DTOR, MTXF_APPLY);
        Matrix_RotateX(gCalcMatrix, rot->x * M_DTOR, MTXF_APPLY);
        Matrix_Mult(gGfxMatrix, gCalcMatrix, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        RCP_SetupDL(&gMasterDisp, SETUPDL_33);
        gSPDisplayList(gMasterDisp++, *dList);
        RCP_SetupDL(&gMasterDisp, SETUPDL_29);
        return true;
    } else {
        return false;
    }
}

Vec3f D_i5_801B75C4 = { 110.0f, 0.0f, 0.0f };

void Titania_TiRasco_PostLimbDraw(s32 limbIndex, Vec3f* rot, void* thisx) {
    TiRasco* this = (TiRasco*) thisx;

    switch (limbIndex) {
        case 2:
            Matrix_MultVec3f(gCalcMatrix, &D_i5_801B75C4, (Vec3f*) &this->fwork[3]);
            break;
        case 4:
            Matrix_MultVec3f(gCalcMatrix, &D_i5_801B75C4, (Vec3f*) &this->fwork[6]);
            break;
    }
}

s16 D_i5_801B75D0[] = {
    1, 2, 3, 4, 5, 6, 7, 10, 12, 13,
};

void Titania_8018B1B4(s32 limbIndex, Vec3f* rot, void* thisx) {
    s32 i;
    PosRot* var_a2;

    var_a2 = LOAD_ASSET(D_i5_801BDA30);

    for (i = 0; i < 10; i++, var_a2++) {
        if (limbIndex == D_i5_801B75D0[i]) {
            Matrix_MultVec3f(gCalcMatrix, &D_tank_800C9F2C, &var_a2->pos);
            Matrix_GetYRPAngles(gCalcMatrix, &var_a2->rot);
            break;
        }
    }
}

void Titania_TiRasco_Update(TiRasco* this) {
    Vec3f src;
    Vec3f dest;
    Actor* sp3C = this->iwork[0];
    Actor* sp38 = this->iwork[1];

    if (this->dmgType > DMG_NONE) {
        this->dmgType = DMG_NONE;
        if (this->health > 0) {
            this->health -= this->damage;
            if (this->health <= 0) {
                this->health = this->itemDrop = 0;
                Actor_Despawn(this);
                this->info.bonus = 0;
            }
        }
        this->timer_0C6 = 10;
    }

    switch (this->state) {
        case 0:
            if ((gPlayer[0].pos.z - this->obj.pos.z) < this->fwork[0]) {
                this->state++;
            }
            break;

        case 1:
            Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
            if ((this->animFrame >= 26) && (this->animFrame <= 53) && (sp3C != NULL)) {
                if (this->animFrame == 26) {
                    sp3C->work_046 = 2;
                    sp3C->vel.x = 0.0f;
                    sp3C->vel.y = 0.0f;
                    sp3C->vel.z = 0.0f;
                } else if (this->animFrame == 53) {
                    src.x = 0.0f;
                    src.y = this->fwork[1];
                    src.z = 20.0f;
                    Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);
                    sp3C->vel.x = dest.x;
                    sp3C->vel.y = dest.y;
                    sp3C->vel.z = dest.z;
                    sp3C->work_046 = 0;
                    sp3C->iwork[0] = (uintptr_t) NULL;
                    this->iwork[0] = (uintptr_t) NULL;
                }
                src.x = this->fwork[3];
                src.y = this->fwork[4] + 50.0f;
                src.z = this->fwork[5];
                Matrix_MultVec3f(gCalcMatrix, &src, &dest);
                sp3C->obj.pos.x = this->obj.pos.x + dest.x;
                sp3C->obj.pos.y = this->obj.pos.y + dest.y;
                sp3C->obj.pos.z = this->obj.pos.z + dest.z;
            }

            if ((this->animFrame >= 26) && (this->animFrame <= 57) && (sp38 != NULL)) {
                if (this->animFrame == 26) {
                    sp38->work_046 = 2;
                    sp38->vel.x = 0.0f;
                    sp38->vel.y = 0.0f;
                    sp38->vel.z = 0.0f;
                } else if (this->animFrame == 57) {
                    AUDIO_PLAY_SFX(NA_SE_EN_THROW_S, this->sfxSource, 4);
                    src.x = 0.0f;
                    src.y = this->fwork[1];
                    src.z = 20.0f;
                    Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);
                    sp38->vel.x = dest.x;
                    sp38->vel.y = dest.y;
                    sp38->vel.z = dest.z;
                    sp38->work_046 = 0;
                    sp38->iwork[0] = (uintptr_t) NULL;
                    this->iwork[1] = (uintptr_t) NULL;
                }
                src.x = this->fwork[6];
                src.y = this->fwork[7] + 50.0f;
                src.z = this->fwork[8];
                Matrix_MultVec3f(gCalcMatrix, &src, &dest);
                sp38->obj.pos.x = this->obj.pos.x + dest.x;
                sp38->obj.pos.y = this->obj.pos.y + dest.y;
                sp38->obj.pos.z = this->obj.pos.z + dest.z;
            }

            if (++this->animFrame >= Animation_GetFrameCount(&aTiRascoAnim)) {
                this->state++;
            }
            break;

        case 2:
            break;
    }

    if (this->health == 0) {
        this->obj.status = OBJ_DYING;
        Animation_GetFrameData(&aTiRascoAnim, this->animFrame, this->vwork);
        Animation_DrawSkeleton(0, aTiRascoSkel, this->vwork, Titania_8018AFD4, Titania_8018B1B4, this,
                               &gIdentityMatrix);
        func_effect_8007D2C8(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 10.0f);
        this->lockOnTimers[TEAM_ID_FOX] = 0;
        this->info.targetOffset = 0.0f;
    }
}

void Titania_TiRasco_Draw(TiRasco* this) {
    Animation_GetFrameData(&aTiRascoAnim, this->animFrame, this->vwork);
    Animation_DrawSkeleton(0, aTiRascoSkel, this->vwork, Titania_TiRasco_OverrideLimbDraw, Titania_TiRasco_PostLimbDraw,
                           this, &gIdentityMatrix);
}

void Titania_TiRasco_Dying(TiRasco* this) {
    PosRot* var_s1;
    Actor* actorPtr;
    s32 i;
    Vec3f sp70;

    Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);

    var_s1 = LOAD_ASSET(D_i5_801BDA30);

    for (i = 0; i < 10; i++, var_s1++) {
        actorPtr = Game_SpawnActor(OBJ_ACTOR_DEBRIS);
        if (actorPtr != NULL) {
            actorPtr->obj.status = OBJ_ACTIVE;
            actorPtr->state = 46;
            actorPtr->work_048 = i;
            Matrix_MultVec3f(gCalcMatrix, &var_s1->pos, &sp70);
            actorPtr->obj.pos.x = this->obj.pos.x + sp70.x;
            actorPtr->obj.pos.y = this->obj.pos.y + sp70.y;
            actorPtr->obj.pos.z = this->obj.pos.z + sp70.z;
            actorPtr->obj.rot.x = this->obj.rot.x + var_s1->rot.x;
            actorPtr->obj.rot.y = this->obj.rot.y + var_s1->rot.y;
            actorPtr->obj.rot.z = this->obj.rot.z + var_s1->rot.z;
            actorPtr->gravity = 1.0f;
            actorPtr->vel.x = sp70.x * 0.05f;
            actorPtr->vel.y = 20.0f;
            actorPtr->vel.z = sp70.z * 0.05f;
            actorPtr->fwork[0] = RAND_FLOAT(4.0f) - 6.0f;
            actorPtr->fwork[1] = RAND_FLOAT(4.0f) - 6.0f;
            actorPtr->fwork[2] = RAND_FLOAT(4.0f) - 6.0f;
        }
    }

    actorPtr = (Actor*) this->iwork[0];
    if (actorPtr != NULL) {
        actorPtr->iwork[0] = (uintptr_t) NULL;
        this->iwork[0] = (uintptr_t) NULL;
        actorPtr->work_046 = 0;
    }

    actorPtr = (Actor*) this->iwork[1];
    if (actorPtr != NULL) {
        actorPtr->work_046 = 0;
        actorPtr->iwork[0] = (uintptr_t) NULL;
        this->iwork[1] = (uintptr_t) NULL;
    }
    Object_Kill(&this->obj, this->sfxSource);
}

void Titania_TiBomb_Init(TiBomb* this) {
    f32 sp24;

    Ground_801B6E20(this->obj.pos.x, this->obj.pos.z + gPathProgress, &sp24, &this->obj.pos.y, &sp24);
    this->obj.rot.x = this->obj.rot.y = this->obj.rot.z = 0.0f;
    this->obj.pos.y -= 20.0f;
}

void Titania_TiBomb_Update(TiBomb* this) {
    f32 var_fa0;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 temp_fa1;

    this->drawShadow = true;

    switch (this->state) {
        case 0:
            sp44 = gPlayer[0].pos.x - this->obj.pos.x;
            sp40 = gPlayer[0].pos.y - this->obj.pos.y;
            sp3C = gPlayer[0].pos.z - this->obj.pos.z;

            if (this->timer_0BE == 7) {
                this->iwork[0] = 2;
                AUDIO_PLAY_SFX(NA_SE_OB_BOMB_ALARM_LAST, this->sfxSource, 0);
            }

            if (this->timer_0BE == 0) {
                temp_fa1 = SQ(sp44) + SQ(sp40) + SQ(sp3C);
                if (temp_fa1 < SQ(166.25f)) {
                    this->timer_0BE = 8;
                } else if (temp_fa1 < SQ(600.0f)) {
                    this->timer_0BE = 0;
                    if (this->timer_0BC == 0) {
                        AUDIO_PLAY_SFX(NA_SE_OB_BOMB_ALARM, this->sfxSource, 4);
                        this->iwork[0] = 1 - this->iwork[0];
                        this->timer_0BC = 5;
                    }
                } else {
                    this->iwork[0] = 0;
                }
            }

            if (this->timer_0BE == 1) {
                func_effect_8007D2C8(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 10.0f);
                Object_Kill(&this->obj, this->sfxSource);
                Player_ApplyDamage(gPlayer, 0, 60);

                gPlayer[0].vel.y = 20.0f;
                gPlayer[0].pos.y += 15.0f;
                gPlayer[0].rollState = 1;
                gPlayer[0].rollTimer = 15;
                gPlayer[0].rollRate = 20;

                if (this->obj.pos.x < gPlayer[0].pos.x) {
                    gPlayer[0].rollRate = -20;
                }
            }
            break;

        case 1:
            Ground_801B6E20(this->obj.pos.x, this->obj.pos.z + gPathProgress, &sp4C, &sp50, &sp48);
            this->fwork[0] = sp50;
            this->fwork[1] = sp4C;
            this->fwork[2] = sp48;
            if (this->vel.y <= 0.0f) {
                this->itemDrop = DROP_NONE;
                Actor_Despawn(this);
                Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_EXPLOSION_M);
                func_effect_8007D2C8(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 10.0f);
                Object_Kill(&this->obj, this->sfxSource);
            }
            break;
    }

    if (fabsf(this->vel.x) > 130.0f) {
        var_fa0 = SIGN_OF(this->vel.x) * 130.0f;
    } else {
        var_fa0 = this->vel.x;
    }

    this->obj.rot.z = (-var_fa0 / 130.0f) * 90.0f;

    if (fabsf(this->vel.z) > 130.0f) {
        var_fa0 = SIGN_OF(this->vel.z) * 130.0f;
    } else {
        var_fa0 = this->vel.z;
    }

    this->obj.rot.x = (var_fa0 / 130.0f) * 90.0f;

    if (this->dmgType == DMG_BEAM) {
        AUDIO_PLAY_SFX(NA_SE_METALBOMB_REFLECT, this->sfxSource, 4);
        sp44 = this->obj.pos.x - this->hitPos.x;
        sp40 = fabsf(sp44);
        this->dmgType = DMG_NONE;
        this->state = 1;
        this->timer_0BC = 0;
        this->timer_0BE = 0;
        this->iwork[0] = 0;
        this->vel.x += sp44 * 0.5f * 0.8f;
        this->vel.z -= (80.0f - sp40) * 0.8f;
        this->vel.y += 34.0f;
        this->gravity = 2.0f;
    }
}

s32 D_i5_801B75E4[3][3] = {
    { 15, 255, 255 },
    { 0, 255, 0 },
    { 0, 0, 0 },
};

Gfx* D_TI_801B7608[10] = {
    D_TI1_7005280, D_TI1_7003C50, D_TI1_7003E30, D_TI1_7004370, D_TI1_7004560,
    D_TI1_7003A90, D_TI1_7005420, D_TI1_7003FC0, D_TI1_7002930, D_TI1_7002490,
};

void Titania_TiBomb_Draw(TiBomb* this) {
    s32 index;

    RCP_SetupDL(&gMasterDisp, SETUPDL_30);
    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
    Matrix_Scale(gGfxMatrix, 1.5f, 1.5f, 1.5f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, aTi1Bomb1DL);
    RCP_SetupDL(&gMasterDisp, SETUPDL_34);
    index = this->iwork[0];
    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, D_i5_801B75E4[0][index], D_i5_801B75E4[1][index],
                    D_i5_801B75E4[2][index], 255);
    gSPDisplayList(gMasterDisp++, aTi1Bomb2DL);
}

void Titania_TiDesertCrawler_Init(TiDesertCrawler* this) {
    UnkStruct_i5_801BD738* temp_a1;
    s32 index;
    s32 i;

    for (i = 0; i < 3; i++) {
        if (!D_i5_801B750C[i]) {
            D_i5_801B750C[i] = true;
            this->iwork[0] = i;
            break;
        }
    }

    if (i == 3) {
        Object_Kill(&this->obj, this->sfxSource);
        return;
    }

    index = this->iwork[0];
    this->info.hitbox = D_i5_801BDB20[index];
    this->health = 80;
    this->iwork[8] = 1;
    temp_a1 = D_i5_801BD738[index];

    for (i = 0; i < 9; i++) {
        temp_a1[i].unk_00.pos.x = temp_a1[i].unk_00.pos.y = temp_a1[i].unk_00.pos.z = temp_a1[i].unk_00.rot.x =
            temp_a1[i].unk_00.rot.y = temp_a1[i].unk_00.rot.z = 0.0f;
        temp_a1[i].unk_18 = 0;
    }
}

bool Titania_8018C118(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    *dList = NULL;
    return false;
}

s16 D_i5_801B7630[9][2] = {
    { 1, 0 }, { 2, 1 }, { 3, 0 }, { 4, 1 }, { 5, 1 }, { 6, 0 }, { 7, 1 }, { 8, 0 }, { 13, 1 },
};

bool Titania_TiDesertCrawler_OverrideLimbDraw(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    TiDesertCrawler* this = (TiDesertCrawler*) thisx;
    s32 sp58;
    s32 i;
    s32 sp50;

    sp50 = this->iwork[0];
    sp58 = false;

    for (i = 0; i < 9; i++) {
        if (limbIndex == D_i5_801B7630[i][0]) {
            if (!(D_i5_801BD738[sp50][i].unk_18 & 1)) {
                Matrix_Translate(gCalcMatrix, pos->x, pos->y, pos->z, MTXF_APPLY);
                sp58 = true;
                Matrix_RotateZ(gCalcMatrix, rot->z * M_DTOR, MTXF_APPLY);
                Matrix_RotateY(gCalcMatrix, rot->y * M_DTOR, MTXF_APPLY);
                Matrix_RotateX(gCalcMatrix, rot->x * M_DTOR, MTXF_APPLY);
                Matrix_Mult(gGfxMatrix, gCalcMatrix, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);

                if ((limbIndex == 13) && (this->iwork[5] & 2) && (this->iwork[6] == 0)) {
                    RCP_SetupDL(&gMasterDisp, SETUPDL_30);
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
                    gSPDisplayList(gMasterDisp++, *dList);
                    RCP_SetupDL(&gMasterDisp, SETUPDL_29);
                } else {
                    gSPDisplayList(gMasterDisp++, *dList);
                }
            } else {
                *dList = NULL;
            }
        }
    }

    return sp58;
}

void Titania_TiDesertCrawler_PostLimbDraw(s32 limbIndex, Vec3f* rot, void* thisx) {
    TiDesertCrawler* this = (TiDesertCrawler*) thisx;

    if ((limbIndex == 13) && !(D_i5_801BD738[this->iwork[0]][8].unk_18 & 1)) {
        gSPDisplayList(gMasterDisp++, D_TI1_7002490);
    }
}

Vec3f D_i5_801B7654 = { 387.0f, 0.0f, 0.0f };
Vec3f D_i5_801B7660 = { 199.5f, 0.0f, 0.0f };

void Titania_8018C3D8(s32 limbIndex, Vec3f* rot, void* thisx) {
    s32 i;
    s32 j;
    Vec3f sp54;
    Vec3f sp48;
    UnkStruct_i5_801BD738* var_s0;
    s32 var_t0;
    f32* var_v0_2;
    f32* var_s0_2;
    s32 temp;
    Actor* this = (Actor*) thisx;

    var_s0 = D_i5_801BD738[this->iwork[0]];
    var_s0[8].unk_18 |= 2;

    for (i = 0; i < 9U; i++, var_s0++) {
        if ((limbIndex == D_i5_801B7630[i][0]) && (var_s0->unk_18 & 2)) {
            Matrix_MultVec3f(gCalcMatrix, &D_tank_800C9F2C, &var_s0->unk_00.pos);
            Matrix_GetYRPAngles(gCalcMatrix, &var_s0->unk_00.rot);
            var_s0->unk_18 &= ~2;
            break;
        }
    }

    this->fwork[27] = D_i5_801BD738[this->iwork[0]][8].unk_00.pos.y;

    switch (this->iwork[2]) {
        case 0:
            switch (limbIndex) {
                case 1:
                    Matrix_MultVec3f(gCalcMatrix, &D_i5_801B7660, (Vec3f*) &this->fwork[12]);
                    break;
                case 3:
                    Matrix_MultVec3f(gCalcMatrix, &D_i5_801B7660, (Vec3f*) &this->fwork[9]);
                    break;
                case 5:
                    Matrix_MultVec3f(gCalcMatrix, &D_i5_801B7654, (Vec3f*) &this->fwork[3]);
                    break;
                case 7:
                    Matrix_MultVec3f(gCalcMatrix, &D_i5_801B7654, (Vec3f*) &this->fwork[6]);
                    break;
            }
            break;

        case 1:
            switch (limbIndex) {
                case 1:
                    Matrix_MultVec3f(gCalcMatrix, &D_tank_800C9F2C, (Vec3f*) &this->fwork[12]);
                    break;
                case 3:
                    Matrix_MultVec3f(gCalcMatrix, &D_tank_800C9F2C, (Vec3f*) &this->fwork[9]);
                    break;
                case 5:
                    Matrix_MultVec3f(gCalcMatrix, &D_tank_800C9F2C, (Vec3f*) &this->fwork[3]);
                    break;
                case 7:
                    Matrix_MultVec3f(gCalcMatrix, &D_tank_800C9F2C, (Vec3f*) &this->fwork[6]);
                    break;
            }
            break;
    }

    var_v0_2 = this->info.hitbox;

    if (this->iwork[8] != 0) {
        var_v0_2[0] = 25.0f;
        var_v0_2++;

        for (i = 0; i < 9U; i++) {
            var_t0 = D_i5_801B74F0[i][2];
            if (limbIndex == D_i5_801B74F0[i][0]) {
                temp = D_i5_801B74F0[i][1];
                for (j = 0; j < var_t0; j++) {
                    var_s0_2 = D_i5_801B7360[temp + j];
                    sp54.x = var_s0_2[0];
                    sp54.y = var_s0_2[1];
                    sp54.z = var_s0_2[2];
                    Matrix_MultVec3f(gCalcMatrix, &sp54, &sp48);
                    var_v0_2[0] = sp48.z;
                    var_v0_2[1] = var_s0_2[3];
                    var_v0_2[2] = sp48.y;
                    var_v0_2[3] = var_s0_2[3];
                    var_v0_2[4] = sp48.x;
                    var_v0_2[5] = var_s0_2[3];
                    var_v0_2 += 6;
                }
                break;
            }
            var_v0_2 += var_t0 * 6;
        }
    } else {
        var_v0_2[0] = 0.0f;
    }
}

void Titania_8018C72C(TiDesertCrawler* this) {
    s32 i;
    f32 sp30;

    this->state = 8;
    AUDIO_PLAY_SFX(NA_SE_EN_KANI_STOP, this->sfxSource, 4);

    for (i = 0; i < 9; i++) {
        D_i5_801BD738[this->iwork[0]][i].unk_18 |= 2;
    }

    sp30 = this->vwork[0].y;
    this->vwork[0].y += this->fwork[26];
    Animation_DrawSkeleton(0, aTi1DesertCrawlerSkel, this->vwork, Titania_8018C118, Titania_8018C3D8, this,
                           &gIdentityMatrix);
    this->vwork[0].y = sp30;
    this->iwork[7] = 0;
    this->iwork[8] = 0;
}

Vec3f D_i5_801B766C = { 0.0f, 0.0f, 15.0f };

void Titania_TiDesertCrawler_Update(TiDesertCrawler* this) {
    s32 i;
    f32 sp170;
    f32 temp_fs0;
    Actor* actorPtr;
    UnkStruct_i5_801BD738* var_s1;
    Vec3f sp158;
    Vec3f spA4[15];
    f32 spA0;
    f32 sp9C;
    f32 sp98;
    Vec3f sp8C;
    f32 sp88;
    f32 x;
    f32 y;
    f32 z;
    s32 pad;

    this->iwork[7]++;
    sp88 = gPlayer[0].trueZpos - this->obj.pos.z;

    if (this->iwork[4] > 0) {
        this->iwork[4]--;
    } else if ((gPlayer[0].grounded != 0) && (this->iwork[3] > 0)) {
        gControllerRumbleFlags[0] = 1;
        this->iwork[3]--;
    }

    if (this->iwork[5] > 0) {
        this->iwork[5]--;
    }

    if (this->iwork[6] > 0) {
        this->iwork[6]--;
    }

    if ((this->health > 0) && (this->dmgType > DMG_NONE) && (this->dmgType != DMG_COLLISION) && (this->state >= 3)) {
        if ((this->health > 0) && (this->dmgPart >= 0) && (this->dmgPart < 3)) {
            this->iwork[5] = 10;

            if (this->state == 4) {
                Audio_KillSfxBySourceAndId(this->sfxSource, NA_SE_EN_KANI_MOTOR);
                this->timer_0BC = 20;
                this->fwork[24] = 1.0f;
                this->fwork[23] = this->animFrame;
            }

            this->health -= this->damage;
            if (this->health <= 0) {
                BonusText_Display(this->obj.pos.x, this->obj.pos.y, this->fwork[27] + this->obj.pos.z, 3);
                gHitCount += 3;
                this->health = this->itemDrop = 0;
                Actor_Despawn(this);
                this->info.bonus = 0;
                this->timer_0BC = 20;
                this->animFrame = 0;
                this->fwork[15] = 0.0f;
            } else {
                AUDIO_PLAY_SFX(NA_SE_EN_SNAKE_DAMAGE, this->sfxSource, 4);
            }
        } else if (this->dmgType == DMG_BEAM) {
            Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_REFLECT);
        }
        this->dmgType = DMG_NONE;
    }

    switch (this->state) {
        case 0:
            AUDIO_PLAY_SFX(NA_SE_EN_HEAVY_JUMP, this->sfxSource, 4);
            this->rot_0F4.y = this->obj.rot.y;
            this->obj.rot.y = 180.0f;
            this->obj.pos.y += 125.0f;
            this->gravity = 1.0f;
            this->drawShadow = true;
            this->vel.y = 20.0f;
            this->vel.z = -70.0f;
            Animation_GetFrameData(&D_TI1_700733C, 0, this->vwork);
            Animation_DrawSkeleton(1, aTi1DesertCrawlerSkel, this->vwork, Titania_8018C118, Titania_8018C3D8, this,
                                   &gIdentityMatrix);
            this->state = 1;
            break;

        case 1:
            Ground_801B6E20(this->obj.pos.x, this->obj.pos.z + gPlayer->zPath, &spA0, &sp9C, &sp98);
            this->fwork[0] = sp9C;
            this->fwork[1] = spA0;
            this->fwork[2] = sp98;
            Animation_GetFrameData(&D_TI1_700733C, 0, spA4);
            Math_SmoothStepToVec3fArray(spA4, this->vwork, 1, 15, 0.2f, 10.0f, 0.01f);
            Animation_DrawSkeleton(1, aTi1DesertCrawlerSkel, this->vwork, Titania_8018C118, Titania_8018C3D8, this,
                                   &gIdentityMatrix);
            if (this->obj.pos.z <= gPlayer[0].pos.z) {
                Math_SmoothStepToAngle(&this->obj.rot.y, this->rot_0F4.y, 0.2f, 10.0f, 0.01f);
            }
            if ((this->obj.pos.y + this->fwork[7] + this->fwork[26]) <= sp9C) {
                AUDIO_PLAY_SFX(NA_SE_EN_HEAVY_BOUND, this->sfxSource, 4);
                this->fwork[16] = this->obj.pos.y = sp9C;
                this->rot_0F4.x = spA0 * M_RTOD;
                this->rot_0F4.z = sp98 * M_RTOD;
                this->gravity = 0.0f;
                this->vel.x = this->vel.y = this->vel.z = 0.0f;
                this->timer_0BC = 10;
                x = this->obj.pos.x + this->fwork[6];
                y = this->obj.pos.y + this->fwork[7] + this->fwork[26];
                z = this->obj.pos.z + this->fwork[8];
                Effect_Effect359_Spawn(x, y, z, 20.0f, 255, 8, 0);
                x = this->obj.pos.x + this->fwork[3];
                y = this->obj.pos.y + this->fwork[4] + this->fwork[26];
                z = this->obj.pos.z + this->fwork[5];
                Effect_Effect359_Spawn(x, y, z, 20.0f, 255, 8, 0);
                sp88 = fabsf(sp88);
                if (sp88 < 5000.0f) {
                    this->iwork[4] = (s32) (sp88 / 200.0f);
                    this->iwork[3] = (s32) ((5000.0f - sp88) / 714.0f);
                }
                this->state = 2;
            }
            this->fwork[15] = 0.0f;
            Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_NEW);
            Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_APPLY);
            Matrix_RotateZ(gCalcMatrix, this->obj.rot.z * M_DTOR, MTXF_APPLY);
            Matrix_MultVec3f(gCalcMatrix, (Vec3f*) &this->fwork[12], &sp8C);
            this->fwork[12] = sp8C.x;
            this->fwork[13] = sp8C.y;
            this->fwork[14] = sp8C.z;
            Matrix_MultVec3f(gCalcMatrix, (Vec3f*) &this->fwork[9], &sp8C);
            this->fwork[9] = sp8C.x;
            this->fwork[10] = sp8C.y;
            this->fwork[11] = sp8C.z;
            Matrix_MultVec3f(gCalcMatrix, (Vec3f*) &this->fwork[3], &sp8C);
            this->fwork[3] = sp8C.x;
            this->fwork[4] = sp8C.y;
            this->fwork[5] = sp8C.z;
            Matrix_MultVec3f(gCalcMatrix, (Vec3f*) &this->fwork[6], &sp8C);
            this->fwork[6] = sp8C.x;
            this->fwork[7] = sp8C.y;
            this->fwork[8] = sp8C.z;
            break;

        case 2:
            Math_SmoothStepToAngle(&this->obj.rot.x, this->rot_0F4.x, 0.5f, 5.0f, 0.01f);
            Math_SmoothStepToAngle(&this->obj.rot.z, this->rot_0F4.z, 0.5f, 5.0f, 0.01f);
            this->obj.pos.y = this->fwork[0] = this->fwork[16];
            this->fwork[1] = this->rot_0F4.x;
            this->fwork[2] = this->rot_0F4.z;
            Animation_GetFrameData(&D_TI1_7007234, 0, spA4);
            Math_SmoothStepToVec3fArray(spA4, this->vwork, 1, 15, 0.5f, 7.0f, 0.1f);
            temp_fs0 = this->vwork[0].y;
            this->vwork[0].y += this->fwork[26];
            Animation_DrawSkeleton(0, aTi1DesertCrawlerSkel, this->vwork, Titania_8018C118, Titania_8018C3D8, this,
                                   &gIdentityMatrix);
            this->vwork[0].y = temp_fs0;
            this->fwork[15] = 0.0f;
            if (this->timer_0BC == 0) {
                this->timer_0BC = 15;
                this->state++;
                AUDIO_PLAY_SFX(NA_SE_EN_KANI_MOTOR, this->sfxSource, 4);
            }
            Math_SmoothStepToF(&this->fwork[26], -60.0f, this->fwork[15], 500.0f, 0.01f);
            break;

        case 3:
            if (this->timer_0BC == 0) {
                this->state = 4;
            }
            Animation_GetFrameData(&D_TI1_70067C4, this->animFrame, spA4);
            Math_SmoothStepToVec3fArray(spA4, this->vwork, 1, 15, 0.1f, 3.0f, 0.01f);
            temp_fs0 = this->vwork[0].y;
            this->vwork[0].y += this->fwork[26];
            Animation_DrawSkeleton(0, aTi1DesertCrawlerSkel, this->vwork, Titania_8018C118, Titania_8018C3D8, this,
                                   &gIdentityMatrix);
            this->vwork[0].y = temp_fs0;
            this->fwork[15] = 0.0f;
            Math_SmoothStepToF(&this->fwork[26], -60.0f, 0.0f, 500.0f, 0.01f);
            if (this->health <= 0) {
                this->state = 5;
                this->animFrame = 0;
                this->timer_0BC = 30;
                this->iwork[6] = 30;
                this->fwork[15] = 0.0f;
            }
            break;

        case 4:
            Ground_801B6E20(this->obj.pos.x, this->obj.pos.z + gPathProgress, &spA0, &sp9C, &sp98);
            this->fwork[0] = sp9C;
            this->fwork[1] = spA0;
            this->fwork[2] = sp98;
            this->obj.pos.y = sp9C;
            Math_SmoothStepToAngle(&this->obj.rot.x, spA0 * M_RTOD, 0.1f, 1.0f, 0.01f);
            Math_SmoothStepToAngle(&this->obj.rot.z, sp98 * M_RTOD, 0.1f, 1.0f, 0.01f);

            if (this->timer_0BC == 0) {
                if (((this->animFrame == 40) || (this->animFrame == 80)) && (this->timer_0BC == 0)) {
                    AUDIO_PLAY_SFX(NA_SE_EN_HEAVY_WALK1, this->sfxSource, 4);
                }
                Math_SmoothStepToF(&this->fwork[15], 1.0f, 0.7f, 0.1f, 0.01f);
                this->animFrame++;
                if (this->animFrame >= Animation_GetFrameCount(&D_TI1_70067C4)) {
                    this->animFrame = 0;
                }
                if ((this->fwork[4] > 0.0f) || (this->fwork[7] > 0.0f)) {
                    Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
                    Matrix_MultVec3f(gCalcMatrix, &D_i5_801B766C, &sp158);
                    this->obj.pos.x += sp158.x;
                    this->obj.pos.z += sp158.z;
                }
            } else {
                Math_SmoothStepToF(&this->fwork[15], 0.0f, 1.0f, 0.2f, 0.01f);
                Math_SmoothStepToF(&this->fwork[24], 0.0f, 1.0f, 0.1f, 0.01f);
                this->fwork[23] += this->fwork[24];
                if (Animation_GetFrameCount(&D_TI1_70067C4) <= this->fwork[23]) {
                    this->fwork[23] = 0.0f;
                }
                this->animFrame = this->fwork[23];
                if (this->timer_0BC == 1) {
                    AUDIO_PLAY_SFX(NA_SE_EN_KANI_MOTOR, this->sfxSource, 4);
                }
            }

            Animation_GetFrameData(&D_TI1_70067C4, this->animFrame, spA4);
            Math_SmoothStepToVec3fArray(spA4, this->vwork, 1, 15, this->fwork[15], 360.0f, 0.01f);
            temp_fs0 = this->vwork[0].y;
            this->vwork[0].y += this->fwork[26];
            Animation_DrawSkeleton(0, aTi1DesertCrawlerSkel, this->vwork, Titania_8018C118, Titania_8018C3D8, this,
                                   &gIdentityMatrix);
            this->vwork[0].y = temp_fs0;
            Math_SmoothStepToF(&this->fwork[26], -60.0f, this->fwork[15], 500.0f, 0.01f);

            if (this->health <= 0) {
                this->iwork[6] = 300;
                this->state = 5;
                this->animFrame = 0;
                this->timer_0BC = 30;
                this->fwork[15] = 0.0f;
                AUDIO_PLAY_SFX(NA_SE_EN_KANI_STOP, this->sfxSource, 4);
            }
            break;

        case 5:
            Math_SmoothStepToF(&this->fwork[15], 1.0f, 1.0f, 0.015f, 0.01f);
            Animation_GetFrameData(&D_TI1_7007130, this->animFrame, spA4);
            Math_SmoothStepToVec3fArray(spA4, this->vwork, 1, 15, this->fwork[15], 360.0f, 0.01f);
            Math_SmoothStepToF(&this->fwork[26], -40.0f, this->fwork[15], 500.0f, 0.01f);
            temp_fs0 = this->vwork[0].y;
            this->vwork[0].y += this->fwork[26];
            Animation_DrawSkeleton(0, aTi1DesertCrawlerSkel, this->vwork, Titania_8018C118, Titania_8018C3D8, this,
                                   &gIdentityMatrix);
            this->vwork[0].y = temp_fs0;
            this->animFrame++;
            if (this->animFrame >= Animation_GetFrameCount(&D_TI1_7007130)) {
                this->animFrame = 0;
            }
            if (this->timer_0BC == 0) {
                this->state = 6;
                this->animFrame = 0;
                this->fwork[15] = 0.0f;
            }
            break;

        case 6:
            if (this->animFrame == 18) {
                this->iwork[8] = 0;
            }
            this->iwork[2] = 1;
            Math_SmoothStepToF(&this->fwork[15], 1.0f, 1.0f, 0.005f, 0.01f);
            Animation_GetFrameData(&D_TI1_7006F74, this->animFrame, spA4);
            Math_SmoothStepToVec3fArray(spA4, this->vwork, 1, 15, this->fwork[15], 360.0f, 0.01f);
            temp_fs0 = this->vwork[0].y;
            this->vwork[0].y += this->fwork[26];
            Animation_DrawSkeleton(0, aTi1DesertCrawlerSkel, this->vwork, Titania_8018C118, Titania_8018C3D8, this,
                                   &gIdentityMatrix);
            this->vwork[0].y = temp_fs0;
            if (this->animFrame == 21) {
                Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
                Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);
                Matrix_RotateZ(gCalcMatrix, this->obj.rot.z * M_DTOR, MTXF_APPLY);

                Matrix_MultVec3f(gCalcMatrix, (Vec3f*) &this->fwork[12], &sp158);
                Effect_Effect359_Spawn(this->obj.pos.x + sp158.x, this->obj.pos.y + sp158.y, this->obj.pos.z + sp158.z,
                                       20.0f, 255, 8, 0);
                Matrix_MultVec3f(gCalcMatrix, (Vec3f*) &this->fwork[9], &sp158);
                Effect_Effect359_Spawn(this->obj.pos.x + sp158.x, this->obj.pos.y + sp158.y, this->obj.pos.z + sp158.z,
                                       20.0f, 255, 8, 0);
                Matrix_MultVec3f(gCalcMatrix, (Vec3f*) &this->fwork[3], &sp158);
                Effect_Effect359_Spawn(this->obj.pos.x + sp158.x, this->obj.pos.y + sp158.y, this->obj.pos.z + sp158.z,
                                       20.0f, 255, 8, 0);
                Matrix_MultVec3f(gCalcMatrix, (Vec3f*) &this->fwork[6], &sp158);
                Effect_Effect359_Spawn(this->obj.pos.x + sp158.x, this->obj.pos.y + sp158.y, this->obj.pos.z + sp158.z,
                                       20.0f, 255, 8, 0);
                AUDIO_PLAY_SFX(NA_SE_OB_METAL_BOUND_M, this->sfxSource, 4);
            }

            if ((this->timer_0BC % 8) == 0) {
                Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
                Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);
                Matrix_RotateZ(gCalcMatrix, this->obj.rot.z * M_DTOR, MTXF_APPLY);
                Matrix_MultVec3f(gCalcMatrix, (Vec3f*) &this->fwork[12], &sp158);
                func_effect_8007D2C8(this->obj.pos.x + sp158.x, this->obj.pos.y + sp158.y, this->obj.pos.z + sp158.z,
                                     1.5f);
                Matrix_MultVec3f(gCalcMatrix, (Vec3f*) &this->fwork[9], &sp158);
                func_effect_8007D2C8(this->obj.pos.x + sp158.x, this->obj.pos.y + sp158.y, this->obj.pos.z + sp158.z,
                                     1.5f);
                Matrix_MultVec3f(gCalcMatrix, (Vec3f*) &this->fwork[3], &sp158);
                func_effect_8007D2C8(this->obj.pos.x + sp158.x, this->obj.pos.y + sp158.y, this->obj.pos.z + sp158.z,
                                     1.5f);
                Matrix_MultVec3f(gCalcMatrix, (Vec3f*) &this->fwork[6], &sp158);
                func_effect_8007D2C8(this->obj.pos.x + sp158.x, this->obj.pos.y + sp158.y, this->obj.pos.z + sp158.z,
                                     1.5f);
            }

            if (this->animFrame < (Animation_GetFrameCount(&D_TI1_7006F74) - 1)) {
                this->animFrame++;
            } else {
                Titania_8018C72C(this);
            }
            break;

        case 7:
            Animation_GetFrameData(&D_TI1_7006F74, this->animFrame, spA4);
            Math_SmoothStepToVec3fArray(spA4, this->vwork, 1, 15, this->fwork[15], 360.0f, 0.01f);
            break;

        case 8:
            switch (this->iwork[7]) {
                case 1:
                    for (i = 0; i < 9U; i++) {
                        D_i5_801BD738[this->iwork[0]][i].unk_18 |= 1;
                    }
                    AUDIO_PLAY_SFX(NA_SE_EN_EXPLOSION_L, this->sfxSource, 4);
                    gCameraShake = 20;
                    gControllerRumbleTimers[0] = 16;
                    Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
                    Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);
                    Matrix_RotateZ(gCalcMatrix, this->obj.rot.z * M_DTOR, MTXF_APPLY);
                    func_effect_8007D2C8(this->obj.pos.x, this->fwork[27] + this->obj.pos.y, this->obj.pos.z, 15.0f);
                    var_s1 = D_i5_801BD738[this->iwork[0]];
                    for (i = 0; i < 9U; i++, var_s1++) {
                        actorPtr = Game_SpawnActor(OBJ_ACTOR_DEBRIS);
                        if ((actorPtr != NULL) && D_i5_801B7630[i][1] == 1) {
                            actorPtr->state = 47;
                            actorPtr->work_048 = i;
                            Matrix_MultVec3f(gCalcMatrix, &var_s1->unk_00.pos, &sp158);
                            actorPtr->obj.pos.x = this->obj.pos.x + sp158.x;
                            actorPtr->obj.pos.y = this->obj.pos.y + sp158.y;
                            actorPtr->obj.pos.z = this->obj.pos.z + sp158.z;
                            actorPtr->obj.rot.x = var_s1->unk_00.rot.x + this->obj.rot.x;
                            actorPtr->obj.rot.y = var_s1->unk_00.rot.y + this->obj.rot.y;
                            actorPtr->obj.rot.z = var_s1->unk_00.rot.z + this->obj.rot.z;
                            sp170 = Math_Atan2F(var_s1->unk_00.pos.z, var_s1->unk_00.pos.x);
                            actorPtr->vel.x = __sinf(sp170) * (7.0f + RAND_FLOAT(5.0f));
                            actorPtr->vel.z = __cosf(sp170) * (7.0f + RAND_FLOAT(5.0f));
                            actorPtr->vel.y = 7.0f + RAND_FLOAT(10.0f);
                            actorPtr->iwork[0] = 1;
                            actorPtr->iwork[1] = 1;
                            if (i != 8) {
                                actorPtr->fwork[0] =
                                    ((Rand_ZeroOne() < 0.5f) ? -1.0f : 1.0f) * (4.0f + RAND_FLOAT(3.0f));
                                actorPtr->fwork[1] =
                                    ((Rand_ZeroOne() < 0.5f) ? -1.0f : 1.0f) * (4.0f + RAND_FLOAT(3.0f));
                                actorPtr->fwork[2] =
                                    ((Rand_ZeroOne() < 0.5f) ? -1.0f : 1.0f) * (4.0f + RAND_FLOAT(3.0f));
                            } else {
                                actorPtr->fwork[0] =
                                    ((Rand_ZeroOne() < 0.5f) ? -1.0f : 1.0f) * (RAND_FLOAT(1.0f) + 0.5f);
                                actorPtr->fwork[1] =
                                    ((Rand_ZeroOne() < 0.5f) ? -1.0f : 1.0f) * (RAND_FLOAT(1.0f) + 0.5f);
                                actorPtr->fwork[2] =
                                    ((Rand_ZeroOne() < 0.5f) ? -1.0f : 1.0f) * (RAND_FLOAT(1.0f) + 0.5f);
                            }
                            actorPtr->gravity = 0.8f;
                        }

                        if (i == 8) {
                            actorPtr = Game_SpawnActor(OBJ_ACTOR_DEBRIS);
                            if (actorPtr != NULL) {
                                actorPtr->state = 47;
                                actorPtr->work_048 = 9;
                                Matrix_MultVec3f(gCalcMatrix, &var_s1->unk_00.pos, &sp158);
                                actorPtr->obj.pos.x = this->obj.pos.x + sp158.x;
                                actorPtr->obj.pos.y = this->obj.pos.y + sp158.y;
                                actorPtr->obj.pos.z = this->obj.pos.z + sp158.z;
                                actorPtr->obj.rot.x = var_s1->unk_00.rot.x + this->obj.rot.x;
                                actorPtr->obj.rot.y = var_s1->unk_00.rot.y + this->obj.rot.y;
                                actorPtr->obj.rot.z = var_s1->unk_00.rot.z + this->obj.rot.z;
                                sp170 = Math_Atan2F(var_s1->unk_00.pos.z, var_s1->unk_00.pos.x);
                                actorPtr->vel.x = __sinf(sp170) * (7.0f + RAND_FLOAT(5.0f));
                                actorPtr->vel.z = __cosf(sp170) * (7.0f + RAND_FLOAT(5.0f));
                                actorPtr->vel.y = 7.0f + RAND_FLOAT(10.0f);
                                actorPtr->iwork[0] = 1;
                                actorPtr->iwork[1] = 1;
                                actorPtr->fwork[0] = ((Rand_ZeroOne() < 0.5f) ? -1.0f : 1.0f) * RAND_FLOAT(0.7f);
                                actorPtr->fwork[1] = ((Rand_ZeroOne() < 0.5f) ? -1.0f : 1.0f) * RAND_FLOAT(0.7f);
                                actorPtr->fwork[2] = ((Rand_ZeroOne() < 0.5f) ? -1.0f : 1.0f) * RAND_FLOAT(0.7f);
                                actorPtr->gravity = 0.8f;
                            }
                        }
                    }
                    break;

                case 4:
                    gFillScreenRed = gFillScreenGreen = gFillScreenBlue = gFillScreenAlpha = 255;
                    gFillScreenAlphaTarget = 0;
                    gFillScreenAlphaStep = 64;
                    break;

                case 5:
                    D_i5_801B750C[this->iwork[0]] = false;
                    Object_Kill(&this->obj, this->sfxSource);
                    break;
            }
            break;
    }

    if (this->health > 0) {
        this->info.targetOffset = this->fwork[27];
    } else {
        this->lockOnTimers[TEAM_ID_FOX] = 0;
        this->info.targetOffset = 0.0f;
    }
    this->dmgType = DMG_NONE;
}

void Titania_TiDesertCrawler_Draw(TiDesertCrawler* this) {
    f32 sp34;

    if ((this->iwork[6] % 2) != 0) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_31);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 127, 0, 0, 255);
        gDPSetEnvColor(gMasterDisp++, 255, 255, 255, 255);
    }
    sp34 = this->vwork[0].y;
    this->vwork[0].y += this->fwork[26];
    Animation_DrawSkeleton(0, aTi1DesertCrawlerSkel, this->vwork, Titania_TiDesertCrawler_OverrideLimbDraw,
                           Titania_TiDesertCrawler_PostLimbDraw, this, &gIdentityMatrix);
    this->vwork[0].y = sp34;
}

void Titania_8018E3B0(TiDesertCrawler* this) {
    D_i5_801B750C[this->iwork[0]] = false;
}

Vec3f D_i5_801B7678 = { 0.0f, 388.0f, 103.0f };
Vec3f D_i5_801B7684 = { 0.0f, 0.0f, 0.0f }; // unused

void Titania_TiDelphor_Init(TiDelphor* this) {
    Actor* delphorHead;
    f32 sp40;
    Vec3f sp34;
    s32 i;

    Ground_801B6E20(this->obj.pos.x, this->obj.pos.z + gPathProgress, &sp40, &this->obj.pos.y, &sp40);

    this->obj.pos.y -= 20.0f;
    delphorHead = &gActors[0];

    for (i = 0; i < ARRAY_COUNT(gActors); i++, delphorHead++) {
        if (delphorHead->obj.status == OBJ_FREE) {
            Actor_Initialize(delphorHead);
            delphorHead->obj.status = OBJ_INIT;
            delphorHead->obj.id = OBJ_ACTOR_TI_DELPHOR_HEAD;
            Object_SetInfo(&delphorHead->info, delphorHead->obj.id);
            delphorHead->iwork[4] = (uintptr_t) this;
            this->iwork[0] = (uintptr_t) delphorHead;
            delphorHead->fwork[6] = D_i5_801B7518[0];
            delphorHead->obj.rot.x = (D_i5_801B7518[0] + D_i5_801B7518[1]) * 0.5f;
            Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
            Matrix_MultVec3f(gCalcMatrix, &D_i5_801B7678, &sp34);
            delphorHead->obj.pos.x = this->fwork[0] = this->obj.pos.x + sp34.x;
            delphorHead->obj.pos.y = this->fwork[1] = this->obj.pos.y + sp34.y;
            delphorHead->obj.pos.z = this->fwork[2] = this->obj.pos.z + sp34.z;
            delphorHead->obj.rot.y = this->obj.rot.y;
            break;
        }
    }

    if (i == 60) {
        Object_Kill(&this->obj, this->sfxSource);
    }
}

void Titania_TiDelphor_Update(TiDelphor* this) {
    this->iwork[1]++;
    if ((this->iwork[0] == (uintptr_t) NULL) && ((this->iwork[1] & 3) == 0)) {
        Effect_Effect390_Spawn(this->fwork[0], this->fwork[1], this->fwork[2], 0.0f, 0.0f, 0.0f, 0.0625f, 10);
    }
}

void Titania_TiDelphor_Draw(TiDelphor* this) {
    gSPDisplayList(gMasterDisp++, aTiDelphorDL);
}

void Titania_TiDelphorHead_Init(TiDelphorHead* this) {
    this->health = 100;
}

void Titania_TiDelphorHead_Update(TiDelphorHead* this) {
    f32 spA4;
    f32 spA0;
    f32 sp9C;
    Vec3f sp90;
    Vec3f sp84;
    f32 sp80;
    f32 sp7C;
    Effect* temp_v0_3;
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    Effect* temp_v0_4;
    f32 sp54;
    s32 i;
    TexturedLine* temp_v0_2;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    s32 index;

    sp9C = gPlayer[0].pos.x - this->obj.pos.x;
    spA0 = (gPlayer[0].pos.y - this->obj.pos.y) - 30.0f;
    spA4 = gPlayer[0].trueZpos - this->obj.pos.z;

    switch (this->state) {
        case 0:
            if (Math_SmoothStepToAngle(&this->obj.rot.x, this->fwork[6], 0.2f, 1.0f, 0.01f) == 0.0f) {
                this->iwork[1] = 1 - this->iwork[1];
                this->fwork[6] = D_i5_801B7518[this->iwork[1]];
            }

            if (spA4 <= 2500.0f) {
                this->state++;
            }
            break;

        case 1:
            this->fwork[7] = Math_Atan2F(sp9C, spA4) * M_RTOD;
            this->fwork[6] = -Math_Atan2F(spA0, sqrtf(SQ(sp9C) + SQ(spA4))) * M_RTOD;

            Math_SmoothStepToAngle(&this->obj.rot.y, this->fwork[7], 0.1f, 1.3333334f, 0.01f);
            Math_SmoothStepToAngle(&this->obj.rot.x, this->fwork[6], 0.1f, 1.3333334f, 0.01f);
            break;

        case 2:
            if (this->obj.rot.y < 0.0f) {
                this->obj.rot.y += 360.0f;
            } else if (this->obj.rot.y >= 360.0f) {
                this->obj.rot.y -= 360.0f;
            }
            if (this->obj.rot.y > 180.0f) {
                this->fwork[8] = 90.0f;
            } else {
                this->fwork[8] = 270.0f;
            }

            this->fwork[9] = 0.0f;
            this->timer_0BC = 10;

            func_effect_8007D0E0(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 10.0f);

            this->iwork[2] = 1;

            index = this->iwork[3];
            if (index > 0) {
                gTexturedLines[index - 1].mode = 0;
            }
            this->state++;
            break;

        case 3:
            Math_SmoothStepToF(&this->fwork[9], 5.0f, 0.05f, 0.5f, 0.01f);
            Math_SmoothStepToAngle(&this->obj.rot.z, this->fwork[8], 1.0f, this->fwork[9], 0.01f);

            if (this->timer_0BC == 0) {
                this->gravity = 0.5f;
            }
            if (this->timer_0BE == 0) {
                func_effect_8007D0E0(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 10.0f);
                this->timer_0BE = 10;
            }

            Ground_801B6E20(this->obj.pos.x, this->obj.pos.z + gPathProgress, &sp80, &sp7C, &sp80);

            if (this->obj.pos.y < (94.0f + sp7C)) {
                spA4 = fabsf(spA4);
                if (spA4 < 5000.0f) {
                    this->iwork[7] = (s32) (spA4 / 200.0f);
                    this->iwork[8] = (s32) ((5000.0f - spA4) / 714.0f);
                }
                AUDIO_PLAY_SFX(NA_SE_EN_METAL_BOUND_M, this->sfxSource, 4);
                this->vel.y = 0.0f;
                this->gravity = 0.0f;
                this->obj.pos.y = 94.0f + sp7C;
                this->state++;
            }
            break;

        case 4:
            if (this->iwork[7] > 0) {
                this->iwork[7]--;
            } else if ((gPlayer[0].grounded != 0) && (this->iwork[8] > 0)) {
                gControllerRumbleFlags[0] = 1;
                this->iwork[8]--;
            }
            break;
    }

    if ((this->state == 0) || (this->state == 1)) {
        Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
        Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);

        sp90.x = 0.0f;
        sp90.y = 39.0f;
        sp90.z = 115.0f;

        Matrix_MultVec3f(gCalcMatrix, &sp90, &sp84);

        this->fwork[0] = sp84.x;
        this->fwork[1] = sp84.y;
        this->fwork[2] = sp84.z;

        sp90.x = 0.0f;
        sp90.y = 39.0f;
        sp90.z = 3115.0f;

        Matrix_MultVec3f(gCalcMatrix, &sp90, &sp84);

        this->fwork[3] = sp84.x;
        this->fwork[4] = sp84.y;
        this->fwork[5] = sp84.z;

        if (this->dmgType > DMG_NONE) {
            this->dmgType = DMG_NONE;
            this->timer_0C6 = 10;
            if (this->health > 0) {
                this->health -= this->damage;
                if (this->health <= 0) {
                    BonusText_Display(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + this->fwork[27], 2);
                    gHitCount += 2;
                    this->lockOnTimers[TEAM_ID_FOX] = this->health = this->itemDrop = 0;
                    this->info.targetOffset = 0.0f;
                    Actor_Despawn(this);
                    this->info.bonus = 0;
                    ((Actor*) this->iwork[4])->iwork[0] = 0;
                    this->iwork[5] = 0;
                    this->state = 2;
                }
            }
        }
    }

    if (this->iwork[3] == 0) {
        for (i = 0; i < ARRAY_COUNT(gTexturedLines); i++) {
            if (gTexturedLines[i].mode == 0) {
                this->iwork[3] = i + 1;
                break;
            }
        }
    }

    sp68 = (this->fwork[3] - this->fwork[0]) / 3000.0f;
    sp64 = (this->fwork[4] - this->fwork[1]) / 3000.0f;
    sp60 = (this->fwork[5] - this->fwork[2]) / 3000.0f;
    sp40 = this->obj.pos.x + this->fwork[0];
    sp44 = this->obj.pos.y + this->fwork[1];
    sp48 = this->obj.pos.z + this->fwork[2];

    for (i = 0; i <= 3000; i += 50) {
        sp5C = (sp68 * i) + sp40;
        sp54 = (sp60 * i) + sp48;
        Ground_801B6E20(sp5C, sp54 + gPathProgress, &sp74, &sp70, &sp6C);
        if ((sp64 * i) + sp44 < sp70) {
            break;
        }
    }

    if (this->iwork[2] == 0) {
        index = this->iwork[3] - 1;

        gTexturedLines[index].mode = 101;
        gTexturedLines[index].posAA.x = this->obj.pos.x + this->fwork[0];
        gTexturedLines[index].posAA.y = this->obj.pos.y + this->fwork[1];
        gTexturedLines[index].posAA.z = this->obj.pos.z + this->fwork[2];
        gTexturedLines[index].prim.r = 255;
        gTexturedLines[index].prim.g = 255;
        gTexturedLines[index].prim.b = 0;
        gTexturedLines[index].prim.a = 255;
        gTexturedLines[index].posBB.x = sp5C;
        gTexturedLines[index].posBB.y = sp70;
        gTexturedLines[index].posBB.z = sp54;
        gTexturedLines[index].xyScale = 3.0f;

        if (this->timer_0C0 == 0) {
            gTexturedLines[index].prim.r = 255;
            gTexturedLines[index].prim.g = 255;
            gTexturedLines[index].prim.b = 64;
        } else {
            gTexturedLines[index].prim.r = 255;
            gTexturedLines[index].prim.g = 100;
            gTexturedLines[index].prim.b = 0;
        }

        if (i <= 3000) {
            if (this->timer_0C0 == 0) {
                Effect_Effect341_Spawn(sp5C, sp70 + 5.0f, sp54, 2.0f);
            }

            temp_v0_3 = (Effect*) this->iwork[5];

            if (temp_v0_3 == NULL) {
                temp_v0_4 = Effect_Load(OBJ_EFFECT_TIMED_SFX);
                if (temp_v0_4 != NULL) {
                    temp_v0_4->obj.status = OBJ_ACTIVE;
                    temp_v0_4->obj.pos.x = sp5C;
                    temp_v0_4->obj.pos.y = sp70 + 5.0f;
                    temp_v0_4->obj.pos.z = sp54;
                    temp_v0_4->timer_50 = 2;
                    this->iwork[5] = (uintptr_t) temp_v0_4;
                    AUDIO_PLAY_SFX(NA_SE_EN_LASER_BEAM, temp_v0_4->sfxSource, 4);
                }
            } else {
                temp_v0_3->obj.pos.x = sp5C;
                temp_v0_3->obj.pos.y = sp70 + 5.0f;
                temp_v0_3->obj.pos.z = sp54;
                temp_v0_3->timer_50 = 2;
            }
        } else {
            this->iwork[5] = 0;
        }

        if (this->timer_0C0 == 0) {
            this->timer_0C0 = 3;
        }
    }
}

void Titania_TiDelphorHead_Draw(Actor* this) {
    gSPDisplayList(gMasterDisp++, D_TI1_7008930);
    if ((this->timer_0C6 % 2) == 0) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_34);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 220, 220, 220, 255);
    } else {
        RCP_SetupDL(&gMasterDisp, SETUPDL_22);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 0, 0, 0, 255);
    }
    gSPDisplayList(gMasterDisp++, D_TI1_7009510);
}

void Titania_TiCactus_Init(TiCactus* this) {
    f32 sp24;
    f32 sp20;

    Ground_801B6E20(this->obj.pos.x, this->obj.pos.z + gPathProgress, &sp20, &sp24, &sp20);
    this->obj.pos.y = sp24;
}

void Titania_Cactus_Update(TiCactus* this) {
    this->obj.rot.y =
        Math_Atan2F(gPlayer[0].cam.eye.x - this->obj.pos.x, gPlayer[0].cam.eye.z - (this->obj.pos.z + gPathProgress)) *
        M_RTOD;
    if (this->destroy) {
        func_effect_8007D074(this->obj.pos.x, this->obj.pos.y + 96.0f, this->obj.pos.z, 4.0f);
        this->obj.status = OBJ_FREE;
        Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_OB_EXPLOSION_S);
    }
}

void Titania_TiPillar_Init(TiPillar* this) {
    if (this->obj.rot.x != 0.0f) {
        if (this->obj.rot.x >= 10000.0f) {
            this->unk_44 = 1;
            this->obj.rot.x -= 10000.0f;
        }
        this->vel.y = this->obj.rot.x;
        this->obj.rot.x = 0.0f;
    }
    this->vel.z = this->obj.pos.x;
}

Vec3f D_i5_801B7690 = { 0.0f, 460.0f, 0.0f };

Gfx* D_TI_801B769C[39] = {
    D_TI2_7009700, D_TI2_7004E80, D_TI2_70049C0, D_TI2_70045D0, D_TI_A001FA0, D_TI_900FE80, D_TI_80018D0,  D_TI_9005450,
    NULL,          D_TI_8009000,  D_TI_A002170,  D_TI_8001FB0,  D_TI_90058A0, D_TI_90042A0, D_TI_90043D0,  D_TI_90044E0,
    D_TI_90045F0,  D_TI_80020D0,  D_TI2_7003F00, D_TI_8001D20,  D_TI_8001E20, NULL,         D_TI_80011C0,  D_TI_8002360,
    D_TI_90051C0,  D_TI_8003640,  D_TI_900FC60,  D_TI_900FD70,  D_TI_9005600, D_TI_8001630, D_TI_80014A0,  D_TI_9005040,
    D_TI2_7004400, D_TI2_7009890, D_TI_8001A80,  D_TI_A001DB0,  D_TI_A001EC0, D_TI_A001BE0, D_TI2_7004270,
};

void Titania_8018F134(TiPillar* this) {
    Vec3f sp7C;
    Vec3f sp70;
    f32 i;
    f32* j = &D_i5_801B7690.x;

    switch (this->unk_44) {
        case 0:
            Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
            Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);

            if ((this->obj.rot.y <= 30.0f) || (this->obj.rot.y >= 330.0f)) {
                for (*j = -80.0f; *j <= 80.0f; *j += 40.0f) {
                    Matrix_MultVec3fNoTranslate(gCalcMatrix, &D_i5_801B7690, &sp70);
                    Effect_Effect359_Spawn(this->obj.pos.x + sp70.x, this->obj.pos.y + sp70.y, this->obj.pos.z + sp70.z,
                                           10.0f, 255, 15, 0);
                }
            } else {
                sp7C.z = 0.0f;
                sp7C.x = -80.0f;
                if (this->obj.rot.y > 90.0f) {
                    sp7C.x = 80.0f;
                }

                for (i = 0.0f; i <= 450.0f; i += 50.0f) {
                    Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
                    Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);
                    sp7C.y = i;
                    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp7C, &sp70);
                    Effect_Effect359_Spawn(this->obj.pos.x + sp70.x, this->obj.pos.y + sp70.y, this->obj.pos.z + sp70.z,
                                           10.0f, 255, 15, 0);
                }
            }
            break;

        case 1:
            Matrix_RotateZ(gCalcMatrix, this->obj.rot.z * M_DTOR, MTXF_NEW);
            sp7C.z = 0.0f;
            sp7C.x = 0.0f;
            for (i = 0.0f; i <= 450.0f; i += 50.0f) {
                sp7C.y = i;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp7C, &sp70);
                Effect_Effect359_Spawn(this->obj.pos.x + sp70.x, this->obj.pos.y + sp70.y, this->obj.pos.z + sp70.z,
                                       10.0f, 255, 15, 0);
            }
            break;
    }
}

void Titania_TiPillar_Update(TiPillar* this) {
    f32 zDist;

    switch (this->state) {
        case 0:
            zDist = gPlayer[0].pos.z - this->obj.pos.z;
            if ((this->vel.y != 0.0f) && (zDist < this->vel.y)) {
                if ((this->unk_44 == 1) && (this->obj.pos.x < gPlayer[0].pos.x)) {
                    this->unk_44 = 2;
                }
                this->state++;
            }
            break;

        case 1:
            this->state++;
            /* fallthrough */
        case 2:
            this->vel.x += 0.05f;
            switch (this->unk_44) {
                case 0:
                    this->obj.rot.x += this->vel.x;
                    if (this->obj.rot.x >= 90.0f) {
                        this->obj.rot.x = 90.0f;
                        this->state++;
                        gControllerRumbleTimers[0] = 7;
                        gCameraShake = 12;
                        Titania_8018F134(this);
                        AUDIO_PLAY_SFX(NA_SE_EN_METAL_BOUND_M, this->sfxSource, 4);
                    }
                    break;

                case 1:
                    this->obj.rot.z += this->vel.x;
                    if (this->obj.rot.z >= 90.0f) {
                        this->obj.rot.z = 90.0f;
                        gControllerRumbleTimers[0] = 7;
                        gCameraShake = 12;
                        Titania_8018F134(this);
                        AUDIO_PLAY_SFX(NA_SE_EN_METAL_BOUND_M, this->sfxSource, 4);
                        this->state++;
                    }
                    break;

                case 2:
                    this->obj.rot.z -= this->vel.x;
                    if (this->obj.rot.z <= -90.0f) {
                        this->obj.rot.z = -90.0f;
                        gControllerRumbleTimers[0] = 7;
                        gCameraShake = 12;
                        Titania_8018F134(this);
                        AUDIO_PLAY_SFX(NA_SE_EN_METAL_BOUND_M, this->sfxSource, 4);
                        this->state++;
                    }
                    break;
            }
            break;

        case 3:
            break;
    }

    if (this->unk_44 != 0) {
        if (this->obj.rot.z == 0.0f) {
            this->obj.pos.x = this->vel.z;
            this->info.hitbox = SEGMENTED_TO_VIRTUAL(aTiPillarHitbox);
        } else if (this->obj.rot.z > 0.0f) {
            this->obj.pos.x = this->vel.z - 75.0f;
            this->info.hitbox = SEGMENTED_TO_VIRTUAL(D_TI_6006C28);
        } else {
            this->obj.pos.x = this->vel.z + 75.0f;
            this->info.hitbox = SEGMENTED_TO_VIRTUAL(D_TI_6006C0C);
        }
    }
}

void Titania_TiPillar_Draw(TiPillar* this) {
    switch (this->unk_44) {
        case 0:
            if (this->unk_44 == 0) {
                gSPDisplayList(gMasterDisp++, D_TI1_7002270);
            } else {
                gSPDisplayList(gMasterDisp++, D_TI1_7000A80);
            }
            break;

        case 1:
        case 2:
            if (this->obj.rot.z != 0.0f) {
                if (this->obj.rot.z > 0.0f) {
                    Matrix_Translate(gGfxMatrix, 75.0f, 0.0f, 0.0f, MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);
                } else {
                    Matrix_Translate(gGfxMatrix, -75.0f, 0.0f, 0.0f, MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);
                }
            }

            if (this->unk_44 == 0) { // Can never be true, this condition is never going to pass.
                gSPDisplayList(gMasterDisp++, D_TI1_7002270);
            } else {
                gSPDisplayList(gMasterDisp++, D_TI1_7000A80);
            }
            break;
    }
}

void Titania_TiGoras_Init(TiGoras* this) {
    s32 pad[2];
    f32* sp1C;
    s32 i;
    s32* var_a1_2;
    UnkStruct_i5_801BBF00* var_v1;

    if (this->swork[0] < 4) {
        this->swork[0]++;
        gSceneSetup = this->swork[0];
        this->timer_050 = 1;
    }

    if (this->timer_050 != 0) {
        this->obj.status = OBJ_INIT;
        return;
    }

    gBossActive = true;
    this->fwork[2] = 1.0f;
    this->fwork[4] = 730.0f;

    for (i = 0; i < ARRAY_COUNT(D_i5_801BD668); i++) {
        D_i5_801BD668[i] = 0;
        D_i5_801BD6B0[i] = 0.0f;
    }

    this->fwork[49] = this->obj.rot.y;
    this->obj.rot.y = 0.0f;

    for (var_v1 = D_i5_801BBF00, i = 0; i < ARRAY_COUNTU(D_i5_801BBF00); i++, var_v1++) {
        var_v1->unk_26 = 0;
        var_v1->unk_00.pos.x = var_v1->unk_00.pos.y = var_v1->unk_00.pos.z = var_v1->unk_00.rot.x =
            var_v1->unk_00.rot.y = var_v1->unk_00.rot.z = var_v1->unk_18.x = var_v1->unk_18.y = var_v1->unk_18.z = 0.0f;
    }

    for (i = 0; i < ARRAY_COUNT(D_i5_801BD218); i++) {
        D_i5_801BD218[i].x = D_i5_801BD218[i].y = D_i5_801BD218[i].z = 0.0f;
        D_i5_801BCDC8[i].x = D_i5_801BCDC8[i].y = D_i5_801BCDC8[i].z = 0.0f;
        D_i5_801BC978[i].x = D_i5_801BC978[i].y = D_i5_801BC978[i].z = 0.0f;
    }

    this->swork[9] = 50;
    this->swork[10] = 50;
    this->swork[11] = 50;
    this->swork[12] = 50;
    this->swork[21] = 100;

    sp1C = D_i5_801BBEF4 = Memory_Allocate(76 * sizeof(f32));
    var_a1_2 = D_i5_801BBEF0 = Memory_Allocate(50 * sizeof(s32));

    for (i = 0; i < 50; i++, var_a1_2++) {
        *var_a1_2 = 0;
    }

    for (i = 0; i < 76; i++, sp1C++) {
        *sp1C = 0.0f;
    }

    D_i5_801BBEF8 = LOAD_ASSET(D_TI_8000FC0);
}

bool Titania_8018FC70(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    f32 sp24;

    if (D_i5_801BBEF0[30] != 0) {
        sp24 = (D_i5_801BBEF0[30] / 15.0f) * D_i5_801BBEF0[32];
        rot->z += SIN_DEG((D_i5_801BBEF0[30] / (f32) D_i5_801BBEF0[31]) * 360.0f) * sp24;
    }

    switch (limbIndex) {
        case 0:
            Matrix_Translate(gCalcMatrix, D_i5_801BBEF4[36], D_i5_801BBEF4[37], D_i5_801BBEF4[38], MTXF_APPLY);
            Matrix_RotateY(gCalcMatrix, D_i5_801BBEF4[64] * M_DTOR, MTXF_APPLY);
            break;

        case 1:
        case 2:
        case 3:
            rot->z += D_i5_801BBEF4[66];
            break;
    }
    Matrix_Translate(gCalcMatrix, pos->x, pos->y, pos->z, MTXF_APPLY);
    Matrix_RotateZ(gCalcMatrix, rot->z * M_DTOR, MTXF_APPLY);
    Matrix_RotateY(gCalcMatrix, rot->y * M_DTOR, MTXF_APPLY);
    Matrix_RotateX(gCalcMatrix, rot->x * M_DTOR, MTXF_APPLY);
    Matrix_Mult(gGfxMatrix, gCalcMatrix, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);

    switch (limbIndex) {
        case 1:
        case 2:
        case 3:
        case 7:
            RCP_SetupDL(&gMasterDisp, SETUPDL_30);
            if ((D_i5_801BBEF0[30] % 2) != 0) {
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
            } else {
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
            }

            if (*dList != NULL) {
                gSPDisplayList(gMasterDisp++, *dList);
            }
            break;

        case 8:
        case 9:
        case 10:
        case 11:
            RCP_SetupDL(&gMasterDisp, SETUPDL_61);
            if ((D_i5_801BBEF0[30] % 2) != 0) {
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
            } else {
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
            }

            gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);

            if (*dList != NULL) {
                gSPDisplayList(gMasterDisp++, *dList);
            }
            RCP_SetupDL(&gMasterDisp, SETUPDL_29);
            break;
    }
    return true;
}

f32 D_i5_801B7738[14] = { -1.0f,  -1.0f,  -1.0f,  -1.0f,  -1.0f,   -1.0f,  -1.0f,
                          871.0f, 580.0f, 637.0f, 637.0f, 1000.0f, 380.0f, 1400.0f };

u8 D_i5_801B7770[][6] = {
    { 1, 0, 0, 0, 0, 4 },    { 2, 0, 0, 0, 0, 5 },    { 3, 0, 0, 0, 0, 3 },    { 4, 0, 0, 0, 0, 6 },
    { 5, 0, 0, 0, 0, 7 },    { 7, 0, 2, 0, 2, 10 },   { 8, 0, 2, 0, 2, 10 },   { 9, 0, 2, 0, 2, 10 },
    { 10, 0, 3, 0, 3, 9 },   { 11, 0, 3, 17, 3, 37 }, { 12, 1, 3, 27, 3, 2 },  { 13, 1, 3, 27, 3, 2 },
    { 14, 1, 3, 27, 3, 2 },  { 15, 1, 3, 27, 3, 2 },  { 16, 0, 4, 0, 4, 9 },   { 17, 0, 4, 18, 4, 37 },
    { 18, 1, 4, 28, 4, 2 },  { 19, 1, 4, 28, 4, 2 },  { 20, 1, 4, 28, 4, 2 },  { 21, 1, 4, 28, 4, 2 },
    { 22, 0, 1, 0, 1, 10 },  { 23, 0, 1, 0, 1, 10 },  { 24, 0, 1, 0, 1, 10 },  { 25, 2, 0, 0, 0, 11 },
    { 26, 2, 0, 0, 0, 12 },  { 27, 0, 0, 0, 0, 0 },   { 28, 0, 0, 0, 0, 13 },  { 29, 0, 0, 0, 0, 14 },
    { 30, 0, 0, 0, 0, 14 },  { 31, 0, 0, 0, 0, 15 },  { 32, 0, 0, 1, 0, 16 },  { 33, 0, 0, 5, 0, 17 },
    { 34, 0, 0, 2, 0, 18 },  { 35, 1, 0, 0, 0, 19 },  { 36, 0, 0, 6, 0, 20 },  { 37, 0, 0, 3, 0, 18 },
    { 38, 1, 0, 0, 0, 19 },  { 39, 0, 0, 4, 0, 20 },  { 51, 2, 0, 0, 0, 22 },  { 55, 0, 2, 8, 2, 1 },
    { 56, 1, 2, 26, 2, 2 },  { 57, 1, 2, 26, 2, 2 },  { 58, 1, 2, 26, 2, 2 },  { 59, 1, 2, 26, 2, 2 },
    { 61, 0, 1, 9, 1, 1 },   { 62, 1, 1, 25, 1, 2 },  { 63, 1, 1, 25, 1, 2 },  { 64, 1, 1, 25, 1, 2 },
    { 65, 1, 1, 25, 1, 2 },  { 66, 3, 0, 0, 0, 23 },  { 70, 0, 0, 12, 0, 24 }, { 71, 0, 0, 7, 0, 25 },
    { 72, 0, 0, 0, 0, 26 },  { 73, 0, 0, 0, 0, 26 },  { 74, 0, 0, 0, 0, 26 },  { 75, 0, 0, 0, 0, 26 },
    { 76, 0, 0, 0, 0, 27 },  { 78, 0, 0, 15, 0, 28 }, { 80, 0, 0, 13, 0, 29 }, { 81, 0, 0, 11, 0, 30 },
    { 84, 0, 0, 10, 0, 31 }, { 85, 0, 0, 0, 0, 32 },  { 86, 1, 0, 0, 0, 33 },  { 87, 0, 0, 16, 0, 34 },
    { 88, 0, 0, 19, 0, 35 }, { 89, 0, 0, 20, 0, 36 }, { 90, 0, 0, 5, 0, 38 },
};

u8 D_i5_801B7904[92] = {
    29, 30, 31, 32, 33, 0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  2,  2,  2,  3,  3,  4,  4,
    5,  5,  6,  6,  6,  6,  6,  6,  6,  6,  7,  7,  7,  7,  7,  28, 8,  8,  8,  8,  8,  9,  9,
    9,  10, 10, 10, 11, 11, 12, 12, 13, 14, 15, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 17, 17,
    18, 19, 20, 20, 20, 20, 20, 20, 21, 21, 21, 21, 21, 21, 22, 22, 23, 24, 25, 26, 27,
};

s16 D_i5_801B7960[][4] = {
    { 3, 7, 12, 90 },  { 1, 9, 12, 90 },  { 1, 9, 12, 90 },  { 1, 7, 12, 90 }, { 1, 7, 12, 90 },  { 1, 7, 12, 90 },
    { 2, 14, 30, 90 }, { 2, 14, 12, 90 }, { 2, 14, 12, 90 }, { 2, 7, 6, 90 },  { 2, 7, 6, 90 },   { 1, 7, 6, 90 },
    { 1, 7, 6, 90 },   { 0, 7, 6, 90 },   { 1, 7, 6, 90 },   { 1, 7, 6, 90 },  { 2, 14, 12, 90 }, { 2, 14, 12, 90 },
    { 1, 7, 6, 90 },   { 1, 7, 6, 90 },   { 0, 0, 0, 0 },    { 0, 0, 0, 0 },   { 0, 0, 0, 0 },    { 0, 0, 0, 0 },
    { 2, 1, 2, 67 },   { 2, 1, 2, 67 },   { 2, 1, 2, 67 },   { 2, 1, 2, 67 },  { 0, 0, 0, 0 },    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },    { 0, 0, 0, 0 },    { 0, 0, 0, 0 },    { 0, 0, 0, 0 },
};

f32 D_i5_801B7A70[86][4] = {
    { 99.0f, 9.0f, 0.0f, 0.0f },        { 99.0f, 9.0f, 0.0f, 0.0f },      { 45.0f, 26.0f, 0.0f, 0.0f },
    { 45.0f, 26.0f, 0.0f, 0.0f },       { 21.0f, 42.0f, 0.0f, 0.0f },     { 50.0f, -3.0f, 0.0f, 24.0f },
    { 103.0f, 2.0f, 0.0f, 24.0f },      { 143.0f, -1.0f, 0.0f, 12.0f },   { 173.0f, 0.0f, 0.0f, 15.0f },
    { 68.0f, -8.0f, 0.0f, 29.0f },      { 69.0f, -7.0f, 0.0f, 29.0f },    { 28.0f, -7.0f, 0.0f, 29.0f },
    { 55.0f, -1.0f, 0.0f, 34.0f },      { 27.0f, 126.0f, 0.0f, 40.0f },   { 35.0f, 56.0f, -2.0f, 30.0f },
    { 28.0f, -3.0f, -2.0f, 29.0f },     { 28.0f, -3.0f, 2.0f, 29.0f },    { 35.0f, 56.0f, 2.0f, 30.0f },
    { 27.0f, 126.0f, 0.0f, 40.0f },     { 106.0f, 22.0f, 0.0f, 35.0f },   { 41.0f, 4.0f, 2.0f, 35.0f },
    { 9.0f, -27.0f, 0.0f, 30.0f },      { 17.0f, 32.0f, 0.0f, 40.0f },    { 106.0f, 22.0f, 0.0f, 35.0f },
    { 41.0f, 4.0f, -2.0f, 35.0f },      { 29.0f, -8.0f, 0.0f, 15.0f },    { 26.0f, 11.0f, 0.0f, 25.0f },
    { 36.0f, 10.0f, 6.0f, 18.0f },      { 36.0f, 10.0f, -6.0f, 18.0f },   { 29.0f, 12.0f, -49.0f, 25.0f },
    { 29.0f, 12.0f, 49.0f, 25.0f },     { 25.0f, 1.0f, 0.0f, 40.0f },     { 85.0f, -10.0f, 0.0f, 25.0f },
    { 36.0f, -40.0f, 0.0f, 20.0f },     { 36.0f, -40.0f, 0.0f, 20.0f },   { 36.0f, -40.0f, 0.0f, 20.0f },
    { 99.0f, 9.0f, 0.0f, 35.0f },       { 23.0f, 6.0f, 0.0f, 30.0f },     { 180.0f, 28.0f, -11.0f, 32.0f },
    { 36.0f, -40.0f, 0.0f, 20.0f },     { 36.0f, -40.0f, 0.0f, 20.0f },   { 36.0f, -40.0f, 0.0f, 20.0f },
    { 99.0f, 9.0f, 0.0f, 35.0f },       { 23.0f, 6.0f, 0.0f, 30.0f },     { 123.0f, -98.0f, -179.0f, 25.0f },
    { 102.0f, -75.0f, -128.0f, 30.0f }, { 89.0f, -42.0f, -84.0f, 40.0f }, { 123.0f, -98.0f, 179.0f, 25.0f },
    { 102.0f, -75.0f, 128.0f, 30.0f },  { 89.0f, -42.0f, 58.0f, 40.0f },  { -2.0f, 20.0f, -47.0f, 34.0f },
    { 13.0f, 52.0f, -54.0f, 35.0f },    { -2.0f, 20.0f, 47.0f, 34.0f },   { 13.0f, 52.0f, 54.0f, 35.0f },
    { 26.0f, 68.0f, 0.0f, 35.0f },      { 75.0f, 39.0f, -60.0f, 40.0f },  { 75.0f, 39.0f, 60.0f, 40.0f },
    { 120.0f, 16.0f, 0.0f, 25.0f },     { 85.0f, 26.0f, 0.0f, 30.0f },    { 45.0f, 26.0f, 0.0f, 35.0f },
    { -25.0f, 11.0f, 0.0f, 35.0f },     { 94.0f, 0.0f, 0.0f, 30.0f },     { 34.0f, 1.0f, 0.0f, 35.0f },
    { 120.0f, 16.0f, 0.0f, 25.0f },     { 85.0f, 26.0f, 0.0f, 30.0f },    { 45.0f, 26.0f, 0.0f, 35.0f },
    { -25.0f, 11.0f, 0.0f, 35.0f },     { 94.0f, 0.0f, 0.0f, 30.0f },     { 34.0f, 1.0f, 0.0f, 35.0f },
    { 6.0f, 4.0f, 0.0f, 25.0f },        { 30.0f, 12.0f, 0.0f, 25.0f },    { 50.0f, -32.0f, 47.0f, 20.0f },
    { 52.0f, -22.0f, 11.0f, 20.0f },    { 53.0f, -19.0f, -23.0f, 20.0f }, { 12.0f, 7.0f, -18.0f, 20.0f },
    { 12.0f, 0.0f, 17.0f, 20.0f },      { 11.0f, -3.0f, 49.0f, 20.0f },   { 50.0f, -32.0f, -47.0f, 20.0f },
    { 52.0f, -22.0f, -11.0f, 20.0f },   { 53.0f, -19.0f, 23.0f, 20.0f },  { 12.0f, 7.0f, 18.0f, 20.0f },
    { 12.0f, 0.0f, -17.0f, 20.0f },     { 11.0f, -3.0f, -49.0f, 20.0f },  { 98.0f, 40.0f, 25.0f, 0.0f },
    { 78.0f, 40.0f, -25.0f, 0.0f },     { 21.0f, 42.0f, 0.0f, 40.0f },
};

s16 D_i5_801B7FD0[45][4] = {
    { 61, 1, 1, 44 },  { 55, 2, 1, 39 },  { 10, 3, 1, 8 },   { 16, 4, 1, 14 },  { 51, 0, 1, 38 },  { 28, 5, 4, 26 },
    { 29, 9, 1, 27 },  { 30, 10, 1, 28 }, { 31, 11, 1, 29 }, { 32, 12, 1, 30 }, { 34, 13, 3, 32 }, { 37, 16, 3, 35 },
    { 39, 19, 2, 37 }, { 90, 21, 2, 66 }, { 36, 23, 2, 34 }, { 1, 25, 1, 0 },   { 2, 26, 1, 1 },   { 4, 27, 1, 3 },
    { 5, 28, 1, 4 },   { 71, 29, 4, 51 }, { 7, 33, 1, 5 },   { 8, 34, 1, 6 },   { 9, 35, 1, 7 },   { 55, 36, 3, 39 },
    { 24, 39, 1, 22 }, { 23, 40, 1, 21 }, { 23, 41, 1, 20 }, { 61, 42, 2, 44 }, { 85, 44, 3, 60 }, { 81, 47, 3, 59 },
    { 70, 50, 2, 50 }, { 80, 52, 2, 58 }, { 85, 54, 1, 61 }, { 78, 55, 1, 57 }, { 87, 56, 1, 63 }, { 10, 57, 4, 8 },
    { 11, 61, 2, 9 },  { 16, 63, 4, 14 }, { 17, 67, 2, 15 }, { 88, 69, 1, 64 }, { 89, 70, 1, 65 }, { 25, 71, 6, 23 },
    { 26, 77, 6, 24 }, { 86, 83, 2, 62 }, { 51, 85, 1, 38 },
};

s16 D_i5_801B8138[9] = { 12, 15, 18, 45, 48, 51, 78, 84, 102 };

s16 D_i5_801B814C[9] = { 21, 24, 27, 54, 57, 60, 81, 87, 105 };

s32 D_i5_801B8160[14] = {
    28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 89, 90,
};

UnkStruct_i5_801B8198 D_i5_801B8198[33] = {
    { 61, 0, NULL, 0 },  { 22, 30, NULL, 0 }, { 21, 30, NULL, 0 }, { 20, 30, NULL, 0 }, { 44, 25, NULL, 0 },
    { 45, 20, NULL, 0 }, { 46, 15, NULL, 0 }, { 47, 10, NULL, 0 }, { 48, 5, NULL, 0 },  { 57, 0, NULL, 0 },
    { 5, 30, NULL, 0 },  { 6, 30, NULL, 0 },  { 7, 30, NULL, 0 },  { 39, 25, NULL, 0 }, { 40, 20, NULL, 0 },
    { 41, 15, NULL, 0 }, { 42, 10, NULL, 0 }, { 43, 5, NULL, 0 },  { 63, 0, NULL, 0 },  { 8, 30, NULL, 0 },
    { 9, 30, NULL, 0 },  { 10, 25, NULL, 0 }, { 11, 20, NULL, 0 }, { 12, 15, NULL, 0 }, { 13, 10, NULL, 0 },
    { 50, 5, NULL, 0 },  { 14, 30, NULL, 0 }, { 15, 30, NULL, 0 }, { 16, 25, NULL, 0 }, { 17, 20, NULL, 0 },
    { 18, 15, NULL, 0 }, { 19, 10, NULL, 0 }, { 58, 5, NULL, 0 },
};

f32 aTiGorasHitbox[517] = {
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
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f
};

f32 D_i5_801B8BBC[5][4] = { { 36.0f, -40.0f, 0.0f, 20.0f },
                            { 99.0f, 9.0f, 0.0f, 0.0f },
                            { 99.0f, 9.0f, 0.0f, 35.0f },
                            { 23.0f, 6.0f, 0.0f, 30.0f },
                            { 180.0f, 28.0f, -11.0f, 32.0f } };

u8 D_i5_801B8C0C[21] = {
    0, 0, 0, 0, 0, 0, 3, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2,
};

s32 D_i5_801B8C24[4][4] = {
    { 1, 0, 1, 0 },
    { 2, 0, 1, 1 },
    { 3, 0, 1, 2 },
    { 7, 1, 4, 3 },
};

f32 D_i5_801B8C64[7][4] = {
    { 45.0f, 26.0f, 0.0f, 0.0f },  { 120.0f, 16.0f, 0.0f, 25.0f }, { 85.0f, 26.0f, 0.0f, 30.0f },
    { 45.0f, 26.0f, 0.0f, 35.0f }, { -25.0f, 11.0f, 0.0f, 35.0f }, { 94.0f, 0.0f, 0.0f, 30.0f },
    { 34.0f, 1.0f, 0.0f, 35.0f },
};

s32 D_i5_801B8CD4[2][4] = {
    { 1, 0, 5, 0 },
    { 2, 4, 2, 5 },
};

s32 D_i5_801B8CF4[3] = { 0, 7, 14 };

Vec3f D_i5_801B8D00 = { 104.0f, 23.0f, 0.0f };
Vec3f D_i5_801B8D0C = { 5.0f, 0.0f, 0.0f };
Vec3f D_i5_801B8D18 = { 0.0f, 0.0f, 30.0f };
Vec3f D_i5_801B8D24 = { 54.0f, 0.0f, 0.0f };
Vec3f D_i5_801B8D30 = { 47.0f, 0.0f, 0.0f };
Vec3f D_i5_801B8D3C = { 158.0f, 4.0f, 0.0f };
Vec3f D_i5_801B8D48 = { 0.0f, 0.0f, 60.0f };

void Titania_8019002C(s32 limbIndex, Vec3f* rot, void* thisx) {
    TiGoras* this = (TiGoras*) thisx;
    s32 i;
    s32 j;
    s32* var_s6;
    f32* var_s0;
    Vec3f sp80;
    Vec3f sp74;
    s32 temp_s3;
    Vec3f sp64;
    s32 temp;

    for (i = 0; i < 4; i++) {
        var_s6 = D_i5_801B8C24[i];
        temp_s3 = var_s6[2];
        if (limbIndex == var_s6[0]) {
            var_s0 = &aTiGorasHitbox[D_i5_801B8CF4[D_i5_801BBEF0[25]] * 6 + var_s6[3] * 6 + 1];
            temp = var_s6[1];

            for (j = 0; j < temp_s3; j++) {
                sp80.x = D_i5_801B8BBC[temp + j][0];
                sp80.y = D_i5_801B8BBC[temp + j][1];
                sp80.z = D_i5_801B8BBC[temp + j][2];
                Matrix_MultVec3f(gCalcMatrix, &sp80, &sp74);
                var_s0[0] = sp74.z;
                var_s0[1] = D_i5_801B8BBC[temp + j][3];
                var_s0[2] = sp74.y;
                var_s0[3] = D_i5_801B8BBC[temp + j][3];
                var_s0[4] = sp74.x;
                var_s0[5] = D_i5_801B8BBC[temp + j][3];
                var_s0 += 6;
            }
        }
    }

    if (limbIndex == 7) {
        Matrix_Push(&gGfxMatrix);
        Matrix_Translate(gGfxMatrix, 180.0f, 36.0f, 0.0f, MTXF_APPLY);
        Matrix_RotateX(gGfxMatrix, -(M_DTOR * 90.0f), MTXF_APPLY);
        Matrix_RotateZ(gGfxMatrix, -(M_DTOR * 90.0f), MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, D_ENMY_PLANET_40018A0);
        Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -47.0f, MTXF_APPLY);
        Matrix_GetYRPAngles(gGfxMatrix, &sp64);
        Matrix_RotateZ(gGfxMatrix, -sp64.z * M_DTOR, MTXF_APPLY);
        Matrix_RotateX(gGfxMatrix, -sp64.x * M_DTOR, MTXF_APPLY);
        Matrix_RotateY(gGfxMatrix, -sp64.y * M_DTOR, MTXF_APPLY);
        Matrix_Scale(gGfxMatrix, D_i5_801BBEF4[74], D_i5_801BBEF4[74], 1.0f, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        RCP_SetupDL(&gMasterDisp, SETUPDL_72);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
        gDPSetEnvColor(gMasterDisp++, 255, 0, 0, 255);
        gSPDisplayList(gMasterDisp++, aOrbDL);
        RCP_SetupDL(&gMasterDisp, SETUPDL_30);
        Matrix_Pop(&gGfxMatrix);
        Matrix_MultVec3f(gCalcMatrix, &D_i5_801B8D3C, (Vec3f*) &this->fwork[29]);
    }
}

bool Titania_801903A0(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    f32 sp24;
    s32 sp20;

    if (limbIndex == 0) {
        if (D_i5_801BBEF0[25] == 1) {
            Matrix_Translate(gCalcMatrix, D_i5_801BBEF4[39], D_i5_801BBEF4[40], D_i5_801BBEF4[41], MTXF_APPLY);
            Matrix_RotateY(gCalcMatrix, D_i5_801BBEF4[54] * M_DTOR, MTXF_APPLY);
        } else {
            Matrix_Translate(gCalcMatrix, D_i5_801BBEF4[42], D_i5_801BBEF4[43], D_i5_801BBEF4[44], MTXF_APPLY);
            Matrix_RotateY(gCalcMatrix, D_i5_801BBEF4[56] * M_DTOR, MTXF_APPLY);
        }
    }

    if (D_i5_801BBEF0[25] == 1) {
        sp20 = D_i5_801BBEF0[33] % 2U;
        if (D_i5_801BBEF0[33] != 0) {
            sp24 = (D_i5_801BBEF0[33] / 15.0f) * D_i5_801BBEF0[37];
            rot->z += SIN_DEG((D_i5_801BBEF0[33] / (f32) D_i5_801BBEF0[35]) * 360.0f) * sp24;
        }
    } else {
        sp20 = D_i5_801BBEF0[34] % 2U;
        if (D_i5_801BBEF0[34] != 0) {
            sp24 = (D_i5_801BBEF0[34] / 15.0f) * D_i5_801BBEF0[38];
            rot->z += SIN_DEG((D_i5_801BBEF0[34] / (f32) D_i5_801BBEF0[36]) * 360.0f) * sp24;
        }
    }
    Matrix_Translate(gCalcMatrix, pos->x, pos->y, pos->z, MTXF_APPLY);
    Matrix_RotateZ(gCalcMatrix, rot->z * M_DTOR, MTXF_APPLY);
    Matrix_RotateY(gCalcMatrix, rot->y * M_DTOR, MTXF_APPLY);
    Matrix_RotateX(gCalcMatrix, rot->x * M_DTOR, MTXF_APPLY);
    Matrix_Mult(gGfxMatrix, gCalcMatrix, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);

    switch (limbIndex) {
        case 1:
        case 2:
            RCP_SetupDL(&gMasterDisp, SETUPDL_30);
            if ((sp20 % 2) != 0) {
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
            } else {
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
            }

            if (*dList != NULL) {
                gSPDisplayList(gMasterDisp++, *dList);
            }
            break;

        case 3:
        case 4:
        case 5:
        case 6:
            RCP_SetupDL(&gMasterDisp, SETUPDL_61);
            if ((sp20 % 2) != 0) {
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
            } else {
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
            }

            gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);

            if (*dList != NULL) {
                gSPDisplayList(gMasterDisp++, *dList);
            }
            RCP_SetupDL(&gMasterDisp, SETUPDL_29);
            break;
    }
    return true;
}

void Titania_8019081C(s32 limbIndex, Vec3f* rot, void* thisx) {
    s32 i;
    s32 j;
    f32* var_s0;
    s32 temp_s3;
    Vec3f sp5C;
    Vec3f sp50;
    s32 temp;

    for (i = 0; i < 2; i++) {
        temp_s3 = D_i5_801B8CD4[i][2];
        if (limbIndex == D_i5_801B8CD4[i][0]) {
            var_s0 = &aTiGorasHitbox[D_i5_801B8CF4[D_i5_801BBEF0[25]] * 6 + D_i5_801B8CD4[i][3] * 6 + 1];
            temp = D_i5_801B8CD4[i][1];
            for (j = 0; j < temp_s3; j++) {
                sp5C.x = D_i5_801B8C64[temp + j][0];
                sp5C.y = D_i5_801B8C64[temp + j][1];
                sp5C.z = D_i5_801B8C64[temp + j][2];

                Matrix_MultVec3f(gCalcMatrix, &sp5C, &sp50);

                var_s0[0] = sp50.z;
                var_s0[1] = D_i5_801B8C64[temp + j][3];
                var_s0[2] = sp50.y;
                var_s0[3] = D_i5_801B8C64[temp + j][3];
                var_s0[4] = sp50.x;
                var_s0[5] = D_i5_801B8C64[temp + j][3];
                var_s0 += 6;
            }
        }
    }

    if (limbIndex == 1) {
        // FAKE
        if (1) {}
        switch ((s32) D_i5_801BBEF0[25]) {
            case 0:
                Matrix_MultVec3f(gCalcMatrix, &D_i5_801B8D00, (Vec3f*) &D_i5_801BBEF4[68]);
                break;
            case 1:
                Matrix_MultVec3f(gCalcMatrix, &D_i5_801B8D00, (Vec3f*) &D_i5_801BBEF4[71]);
                break;
        }
    }
}

#ifdef NON_MATCHING
// float regalloc starting with the spherical angle calculation
// https://decomp.me/scratch/9ewO1

bool Titania_80190A08(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    Vec3f spCC;
    Vec3f spC0;
    // f32 spBC;
    // f32 padB8;
    Vec3f padB4; // Vec3f? Seems kind of wasteful
    s32 i;
    TiGoras* this = (TiGoras*) thisx;
    s32 spA8;
    s32 temp_v1;
    s32 spA0;
    f32 sp9C;
    s32 ret = false;
    Vec3f sp8C;
    s32 sp88;
    Vec3f sp7C;
    Vec3f sp70;
    s32 sp6C;
    f32 sp68;
    // f32 pad64;
    // f32 sp60;
    Vec3f sp5C; // Vec3f?
    s32 sp58;

    if (limbIndex == 0) {
        rot->y += this->fwork[0x31];
    }

    for (i = 0; i < ARRAY_COUNT(D_i5_801B7770); i++) {
        if (limbIndex == D_i5_801B7770[i][0]) {
            if (D_i5_801BBF00[i].unk_26 & 4) {
                *dList = NULL;
            } else {
                switch (limbIndex) {
                    case 7:
                    case 8:
                    case 9:
                        rot->z += D_i5_801BBEF4[8];
                        break;

                    case 22:
                    case 23:
                    case 24:
                        rot->z += D_i5_801BBEF4[6];
                        break;

                    case 25:
                    case 26:
                        if (D_i5_801BBEF4[2] != 0.0f) {
                            rot->z += D_i5_801BBEF4[2];
                            if (D_i5_801BBEF4[3] != 0.0f) {
                                rot->z += __sinf((D_i5_801BBEF4[3] / D_i5_801BBEF4[5]) * 360.0f * M_DTOR) *
                                          D_i5_801BBEF4[3] / 6.0f;
                            }
                        }
                        break;

                    case 89:
                        rot->x += D_i5_801BBEF4[13];
                        break;
                }

                sp88 = 0;

                switch (limbIndex) {
                    case 55:
                        if (this->fwork[0x28] != 0.0f) {
                            sp88 = 1;
                        }
                        break;
                    case 61:
                        if (this->fwork[39] != 0.0f) {
                            sp88 = 2;
                        }
                        break;
                    case 71:
                        if (this->fwork[38] != 0.0f) {
                            sp88 = 3;
                        }
                        break;
                }

                if (sp88 != 0) {
                    Matrix_GetYRPAngles(gCalcMatrix, &spCC);
                }

                sp9C = 0.0f;
                temp_v1 = D_i5_801B7770[i][3] - 1;
                spA0 = (temp_v1 != -1) && (D_i5_801BD668[temp_v1] != 0);

                if (spA0 != 0) {
                    spA8 = D_i5_801B7960[temp_v1][0];
                    sp9C = ((__sinf(D_i5_801BD6B0[temp_v1] * M_DTOR) * D_i5_801BD668[temp_v1]) /
                            D_i5_801B7960[temp_v1][1]) *
                           D_i5_801B7960[temp_v1][2];
                    switch (spA8) {
                        case 0:
                            break;

                        case 1:
                            spC0.x = 0.0f;
                            spC0.z = spC0.y = sp9C;
                            break;

                        case 2:
                            if (sp88 == 0) {
                                Matrix_RotateZ(gCalcMatrix, sp9C * M_DTOR, MTXF_APPLY);
                                Matrix_RotateY(gCalcMatrix, sp9C * M_DTOR, MTXF_APPLY);
                            }
                            break;

                        case 3:
                            rot->y += sp9C;
                            break;

                        case 4:
                            padB4.z = sp9C;
                            break;
                    }
                }

                Matrix_Translate(gCalcMatrix, pos->x, pos->y, pos->z, MTXF_APPLY);

                if (sp88 != 0) {
                    Matrix_RotateZ(gCalcMatrix, D_i5_801BBF00[i].unk_18.z * M_DTOR, MTXF_APPLY);
                    Matrix_RotateY(gCalcMatrix, D_i5_801BBF00[i].unk_18.y * M_DTOR, MTXF_APPLY);
                    Matrix_RotateX(gCalcMatrix, D_i5_801BBF00[i].unk_18.x * M_DTOR, MTXF_APPLY);
                } else {
                    rot->z += D_i5_801BBF00[i].unk_18.z;
                    rot->y += D_i5_801BBF00[i].unk_18.y;
                    rot->x += D_i5_801BBF00[i].unk_18.x;
                }

                if (sp88 != 0) {
                    Matrix_Push(&gCalcMatrix);
                    Matrix_RotateZ(gCalcMatrix, rot->z * M_DTOR, MTXF_APPLY);
                    Matrix_RotateY(gCalcMatrix, rot->y * M_DTOR, MTXF_APPLY);
                    Matrix_RotateX(gCalcMatrix, rot->x * M_DTOR, MTXF_APPLY);
                    Matrix_GetYRPAngles(gCalcMatrix, &sp8C);
                    Matrix_MultVec3f(gCalcMatrix, &D_tank_800C9F2C, &sp7C);

                    if ((limbIndex == 71) && (this->fwork[0x2E] != 0.0f)) {
                        sp70.x = (gPlayer[0].pos.x - (this->obj.pos.x + sp7C.x)) * this->fwork[0x2E];
                        sp70.y = (gPlayer[0].pos.y + 50.0f) - (this->obj.pos.y + sp7C.y);
                        sp70.z = (gPlayer[0].trueZpos - (this->obj.pos.z + sp7C.z)) * this->fwork[0x2E];

                        // Regalloc starts here
                        sp5C.y = Math_Atan2F(sp70.x, sp70.z) * M_RTOD;
                        sp5C.x = -Math_Atan2F(sp70.y, sqrtf(SQ(sp70.x) + SQ(sp70.z))) * M_RTOD;

                    } else {
                        sp70.x = gPlayer[0].pos.x - (this->obj.pos.x + sp7C.x);
                        sp70.y = (gPlayer[0].pos.y + 30.0f) - (this->obj.pos.y + sp7C.y);
                        sp70.z = gPlayer[0].trueZpos - (this->obj.pos.z + sp7C.z);

                        sp5C.y = Math_Atan2F(sp70.x, sp70.z) * M_RTOD;
                        sp5C.x = -Math_Atan2F(sp70.y, sqrtf(SQ(sp70.x) + SQ(sp70.z))) * M_RTOD;
                    }

                    Matrix_Pop(&gCalcMatrix);

                    Matrix_RotateZ(gCalcMatrix, -(spCC.z * M_DTOR), MTXF_APPLY);
                    Matrix_RotateX(gCalcMatrix, -(spCC.x * M_DTOR), MTXF_APPLY);
                    Matrix_RotateY(gCalcMatrix, -(spCC.y * M_DTOR), MTXF_APPLY);

                    switch (limbIndex) {
                        case 55:
                            if (D_i5_801BBEF0[15] == 1) {
                                D_i5_801BBEF4[20] = 0.0f;
                                D_i5_801BBEF4[21] = sp5C.y - 90.0f;
                                D_i5_801BBEF4[22] = -sp5C.x;
                                D_i5_801BBEF0[15] = 0;
                            }
                            D_i5_801BBEF4[29] = 0.0f;
                            D_i5_801BBEF4[30] = sp5C.y - 90.0f;
                            D_i5_801BBEF4[31] = -sp5C.x;

                            sp8C.x = 0.0f;

                            Math_SmoothStepToAngle(&sp8C.y, D_i5_801BBEF4[21], this->fwork[40], 360.0f, 0.01f);
                            Math_SmoothStepToAngle(&sp8C.z, D_i5_801BBEF4[22], this->fwork[40], 360.0f, 0.01f);
                            break;

                        case 61:
                            if (D_i5_801BBEF0[14] == 1) {
                                D_i5_801BBEF4[17] = 0.0f;
                                D_i5_801BBEF4[18] = sp5C.y - 90.0f;
                                D_i5_801BBEF4[19] = -sp5C.x;
                                D_i5_801BBEF0[14] = 0;
                            }
                            D_i5_801BBEF4[26] = 0.0f;
                            D_i5_801BBEF4[27] = sp5C.y - 90.0f;
                            D_i5_801BBEF4[28] = -sp5C.x;

                            sp8C.x = 0.0f;

                            Math_SmoothStepToAngle(&sp8C.y, D_i5_801BBEF4[18], this->fwork[39], 360.0f, 0.01f);
                            Math_SmoothStepToAngle(&sp8C.z, D_i5_801BBEF4[19], this->fwork[39], 360.0f, 0.01f);
                            break;

                        case 71:
                            if (D_i5_801BBEF0[13] == 1) {
                                D_i5_801BBEF4[14] = 0.0f;
                                D_i5_801BBEF4[15] = sp5C.y + 90.0f;
                                D_i5_801BBEF4[16] = sp5C.x + 180.0f;
                                D_i5_801BBEF0[13] = 0;
                            }

                            D_i5_801BBEF4[24] = sp5C.y + 90.0f;
                            D_i5_801BBEF4[25] = sp5C.x + 180.0f;

                            while (D_i5_801BBEF4[24] >= 270.0f) {
                                D_i5_801BBEF4[24] -= 360.0f;
                            }

                            while (D_i5_801BBEF4[24] < -90.0f) {
                                D_i5_801BBEF4[24] += 360.0f;
                            }

                            if (D_i5_801BBEF4[24] < -45.0f) {
                                D_i5_801BBEF4[24] = -45.0f;
                            }
                            if (D_i5_801BBEF4[24] > 225.0f) {
                                D_i5_801BBEF4[24] = 225.0f;
                            }

                            sp8C.x = 0.0f;

                            Math_SmoothStepToAngle(&sp8C.y, D_i5_801BBEF4[15], this->fwork[38], 360.0f, 0.01f);
                            Math_SmoothStepToAngle(&sp8C.z, D_i5_801BBEF4[16], this->fwork[38], 360.0f, 0.01f);
                            break;
                    }
                    Matrix_RotateY(gCalcMatrix, (sp8C.y + sp9C) * M_DTOR, MTXF_APPLY);
                    Matrix_RotateZ(gCalcMatrix, (sp8C.z + sp9C) * M_DTOR, MTXF_APPLY);
                    Matrix_RotateX(gCalcMatrix, sp8C.x * M_DTOR, MTXF_APPLY);
                } else {
                    Matrix_RotateZ(gCalcMatrix, rot->z * M_DTOR, MTXF_APPLY);
                    Matrix_RotateY(gCalcMatrix, rot->y * M_DTOR, MTXF_APPLY);
                    Matrix_RotateX(gCalcMatrix, rot->x * M_DTOR, MTXF_APPLY);
                }

                sp6C = 0;

                if ((limbIndex == 51) || (limbIndex == 66)) {
                    if (D_i5_801BBEF0[1] != 0) {
                        sp68 = 1.1f - (fabsf(__sinf(((f32) D_i5_801BBEF0[0] / D_i5_801BBEF0[1]) * 360.0f * M_DTOR))) *
                                          D_i5_801BBEF4[0];
                        Matrix_Push(&gCalcMatrix);
                        Matrix_Scale(gCalcMatrix, sp68, sp68, sp68, MTXF_APPLY);
                        sp6C = 1;
                    }
                }

                if (spA0 != 0) {
                    switch (spA8) {
                        case 1:
                            Matrix_Push(&gCalcMatrix);
                            Matrix_Translate(gCalcMatrix, spC0.x, spC0.y, spC0.z, MTXF_APPLY);
                            break;
                        case 4:
                            Matrix_Push(&gCalcMatrix);
                            Matrix_Translate(gCalcMatrix, 40.0f, 0.0f, 0.0f, MTXF_APPLY);
                            Matrix_RotateZ(gCalcMatrix, padB4.z * M_DTOR, MTXF_APPLY);
                            Matrix_Translate(gCalcMatrix, -40.0f, 0.0f, 0.0f, MTXF_APPLY);
                            break;
                    }
                }
                Matrix_Mult(gGfxMatrix, gCalcMatrix, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);

                sp58 = 0;

                switch (D_i5_801B7770[i][1]) {
                    case 0:
                        break;

                    case 1:
                        RCP_SetupDL(&gMasterDisp, SETUPDL_61);
                        gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                        break;

                    case 2:
                        RCP_SetupDL(&gMasterDisp, SETUPDL_58);
                        gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                        break;

                    case 3:
                        RCP_SetupDL(&gMasterDisp, SETUPDL_34);
                        break;
                }

                if ((this->swork[22] & 1) ||
                    ((D_i5_801B7770[i][2] != 0) && (this->swork[D_i5_801B7770[i][2] + 4] & 1))) {
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
                    sp58 = 1;
                }

                if (*dList != NULL) {
                    gSPDisplayList(gMasterDisp++, *dList);
                }

                if (D_i5_801B7770[i][1] > 0) {
                    RCP_SetupDL(&gMasterDisp, SETUPDL_30);
                } else {
                    gDPPipeSync(gMasterDisp++);
                }

                if (sp58 == 1) {
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
                }

                if (sp6C != 0) {
                    Matrix_Pop(&gCalcMatrix);
                }

                if ((spA0 != 0) && ((spA8 == 1) || (spA8 == 4))) {
                    Matrix_Pop(&gCalcMatrix);
                }
                Matrix_SetGfxMtx(&gMasterDisp);
                ret = true;
            }
            break;
        }
    }
    return ret;
}
#else
#pragma GLOBAL_ASM("asm/us/rev1/nonmatchings/overlays/ovl_i5/fox_ti/Titania_80190A08.s")
bool Titania_80190A08(s32, Gfx**, Vec3f*, Vec3f*, void*);
#endif

void Titania_80191AE8(s32 limbIndex, Vec3f* rot, void* thisx) {
    TiGoras* this = (TiGoras*) thisx;
    f32* var_s0_2;
    Vec3f spB4;
    Vec3f spA8;
    s32 pad[2];
    f32* var_s1;
    UnkStruct_i5_801BBF00* var_s0 = D_i5_801BBF00;
    s32 temp_s4;
    s16 temp_s6;
    s32 i;
    s32 j;
    s32 cond;
    Vec3f sp78;

    for (i = 0; i < ARRAY_COUNTU(D_i5_801B7770); i++, var_s0++) {
        if ((var_s0->unk_26 & 1) && (limbIndex == D_i5_801B7770[i][0])) {
            Matrix_MultVec3f(gCalcMatrix, &D_tank_800C9F2C, &var_s0->unk_00.pos);
            Matrix_GetYRPAngles(gCalcMatrix, &var_s0->unk_00.rot);
            var_s0->unk_26 &= ~1;
            break;
        }
    }

    var_s0_2 = aTiGorasHitbox;
    *(var_s0_2++) = 86.0f;

    for (i = 0; i < ARRAY_COUNTU(D_i5_801B7FD0); i++) {
        temp_s4 = D_i5_801B7FD0[i][2];
        if (limbIndex == D_i5_801B7FD0[i][0]) {

            temp_s6 = D_i5_801B7FD0[i][1];
            cond = (D_i5_801BBF00[D_i5_801B7FD0[i][3]].unk_26 & 0xC);
            cond = !(cond || ((i >= 20) && (i < 23) && (this->state == 10)));

            for (j = 0; j < temp_s4; j++) {
                if (cond && (D_i5_801BBEF0[8] == 0 || i != 23 || j != 2)) {
                    var_s1 = D_i5_801B7A70[temp_s6 + j];
                    spB4.x = var_s1[0];
                    spB4.y = var_s1[1];
                    spB4.z = var_s1[2];
                    Matrix_MultVec3f(gCalcMatrix, &spB4, &spA8);
                    *var_s0_2++ = spA8.z;
                    *var_s0_2++ = var_s1[3];
                    *var_s0_2++ = spA8.y;
                    *var_s0_2++ = var_s1[3];
                    *var_s0_2++ = spA8.x;
                    *var_s0_2++ = var_s1[3];
                } else {
                    *var_s0_2++ = 10000.0f;
                    *var_s0_2++ = 0.0f;
                    *var_s0_2++ = 10000.0f;
                    *var_s0_2++ = 0.0f;
                    *var_s0_2++ = 0.0f;
                    *var_s0_2++ = 0.0f;
                }
            }

            if (i < 5) {
                continue;
            }
            break;
        }
        var_s0_2 += temp_s4 * 6;
    }

    switch (limbIndex) {
        case 3:
            Matrix_MultVec3f(gCalcMatrix, &D_i5_801B8D30, (Vec3f*) &this->fwork[17]);
            break;
        case 10:
            Matrix_MultVec3f(gCalcMatrix, &D_i5_801B8D00, (Vec3f*) &D_i5_801BBEF4[68]);
            break;
        case 16:
            Matrix_MultVec3f(gCalcMatrix, &D_i5_801B8D00, (Vec3f*) &D_i5_801BBEF4[71]);
            break;
        case 71:
            Matrix_GetYRPAngles(gCalcMatrix, (Vec3f*) &this->fwork[20]);
            break;
        case 61:
            Matrix_MultVec3f(gCalcMatrix, &D_i5_801B8D3C, (Vec3f*) &this->fwork[0x17]);
            Matrix_GetYRPAngles(gCalcMatrix, (Vec3f*) &this->fwork[0x1A]);
            break;

        case 55:
            if (D_i5_801BBEF0[8] == 0) {
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, 180.0f, 36.0f, 0.0f, MTXF_APPLY);
                Matrix_RotateX(gGfxMatrix, -(M_DTOR * 90.0f), MTXF_APPLY);
                Matrix_RotateZ(gGfxMatrix, -(M_DTOR * 90.0f), MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_ENMY_PLANET_40018A0);
                Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -47.0f, MTXF_APPLY);
                Matrix_GetYRPAngles(gGfxMatrix, &sp78);
                Matrix_RotateZ(gGfxMatrix, -sp78.z * M_DTOR, MTXF_APPLY);
                Matrix_RotateX(gGfxMatrix, -sp78.x * M_DTOR, MTXF_APPLY);
                Matrix_RotateY(gGfxMatrix, -sp78.y * M_DTOR, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, D_i5_801BBEF4[74], D_i5_801BBEF4[74], 1.0f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                RCP_SetupDL(&gMasterDisp, SETUPDL_72);
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
                gDPSetEnvColor(gMasterDisp++, 255, 0, 0, 255);
                gSPDisplayList(gMasterDisp++, aOrbDL);
                RCP_SetupDL(&gMasterDisp, SETUPDL_30);
                Matrix_Pop(&gGfxMatrix);
                Matrix_MultVec3f(gCalcMatrix, &D_i5_801B8D3C, (Vec3f*) &this->fwork[29]);
                break;
            }
            Matrix_MultVec3f(gCalcMatrix, &D_i5_801B8D3C, (Vec3f*) &this->fwork[29]);
            Matrix_GetYRPAngles(gCalcMatrix, (Vec3f*) &this->fwork[32]);
            break;

        case 34:
            Matrix_MultVec3f(gCalcMatrix, &D_i5_801B8D24, (Vec3f*) &this->fwork[5]);
            break;
        case 37:
            Matrix_MultVec3f(gCalcMatrix, &D_i5_801B8D24, (Vec3f*) &this->fwork[8]);
            break;
        default:
            break;
    }
}

void Titania_80192118(TiGoras* this) {
    Vec3f sp54;
    Effect* effect;
    f32 temp_ft2;
    f32 temp_ft4;
    f32 temp_fa1;
    f32 temp_fv1;

    if (D_i5_801BBEF0[30] > 0) {
        D_i5_801BBEF0[30]--;
    }

    if (D_i5_801BBEF0[33] > 0) {
        D_i5_801BBEF0[33]--;
    }

    if (D_i5_801BBEF0[34] > 0) {
        D_i5_801BBEF0[34]--;
    }

    if (D_i5_801BBEF0[29] > 0) {
        D_i5_801BBEF0[29]--;
    }

    if ((this->state == 3) || (this->state == 4)) {
        Math_SmoothStepToF(&D_i5_801BBEF4[36], D_i5_801BBEF4[51], 0.5f, 10.0f, 0.01f);
        Math_SmoothStepToF(&D_i5_801BBEF4[37], D_i5_801BBEF4[52], 0.5f, 10.0f, 0.01f);
        Math_SmoothStepToF(&D_i5_801BBEF4[38], D_i5_801BBEF4[53], 0.5f, 10.0f, 0.01f);
        Math_SmoothStepToF(&D_i5_801BBEF4[39], D_i5_801BBEF4[45], 0.5f, 10.0f, 0.01f);
        Math_SmoothStepToF(&D_i5_801BBEF4[40], D_i5_801BBEF4[46], 0.5f, 10.0f, 0.01f);
        Math_SmoothStepToF(&D_i5_801BBEF4[41], D_i5_801BBEF4[47], 0.5f, 10.0f, 0.01f);
        Math_SmoothStepToF(&D_i5_801BBEF4[42], D_i5_801BBEF4[48], 0.5f, 10.0f, 0.01f);
        Math_SmoothStepToF(&D_i5_801BBEF4[43], D_i5_801BBEF4[49], 0.5f, 10.0f, 0.01f);
        Math_SmoothStepToF(&D_i5_801BBEF4[44], D_i5_801BBEF4[50], 0.5f, 10.0f, 0.01f);
        Math_SmoothStepToAngle(&D_i5_801BBEF4[64], D_i5_801BBEF4[65], 0.5f, 3.0f, 0.01f);
        Math_SmoothStepToAngle(&D_i5_801BBEF4[54], D_i5_801BBEF4[55], 0.5f, 3.0f, 0.01f);
        Math_SmoothStepToAngle(&D_i5_801BBEF4[56], D_i5_801BBEF4[63], 0.5f, 3.0f, 0.01f);
    }

    switch (this->state) {
        case 0:
            D_i5_801BBEF4[36] = D_i5_801BBEF4[51] = 120.0f;
            D_i5_801BBEF4[37] = D_i5_801BBEF4[52] = -250.0f;
            D_i5_801BBEF4[38] = D_i5_801BBEF4[53] = -300.0f;
            D_i5_801BBEF4[39] = D_i5_801BBEF4[45] = -200.0f;
            D_i5_801BBEF4[40] = D_i5_801BBEF4[46] = -290.0f;
            D_i5_801BBEF4[41] = D_i5_801BBEF4[47] = 0.0f;
            D_i5_801BBEF4[42] = D_i5_801BBEF4[48] = -40.0f;
            D_i5_801BBEF4[43] = D_i5_801BBEF4[49] = -80.0f;
            D_i5_801BBEF4[44] = D_i5_801BBEF4[50] = -40.0f;
            D_i5_801BBEF4[57] = D_i5_801BBEF4[36] + this->obj.pos.x;
            D_i5_801BBEF4[58] = D_i5_801BBEF4[38] + this->obj.pos.z;
            D_i5_801BBEF4[59] = D_i5_801BBEF4[39] + this->obj.pos.x;
            D_i5_801BBEF4[60] = D_i5_801BBEF4[41] + this->obj.pos.z;
            D_i5_801BBEF4[61] = D_i5_801BBEF4[42] + this->obj.pos.x;
            D_i5_801BBEF4[62] = D_i5_801BBEF4[44] + this->obj.pos.z;
            D_i5_801BBEF4[54] = D_i5_801BBEF4[55] = 70.0f;
            D_i5_801BBEF4[56] = D_i5_801BBEF4[63] = -80.0f;
            D_i5_801BBEF4[64] = D_i5_801BBEF4[65] = 0.0f;
            D_i5_801BBEF4[66] = 48.0f;
            D_i5_801BBEF4[67] = 48.0f;
            D_i5_801BBEF0[22] = 0;
            D_i5_801BBEF0[23] = 0;
            D_i5_801BBEF0[24] = 0;
            this->swork[1] = 1;
            break;

        case 1:
            Animation_GetFrameData(&D_TI_A0002BC, 0, &D_i5_801BC978[0]);
            Animation_GetFrameData(&D_TI_A0002BC, 0, &D_i5_801BCDC8[0]);
            Animation_GetFrameData(&D_TI_A0002BC, 0, &D_i5_801BC978[8]);
            Animation_GetFrameData(&D_TI_A0002BC, 0, &D_i5_801BCDC8[8]);
            Animation_GetFrameData(&D_TI_A000934, 0, &D_i5_801BC978[16]);
            Animation_GetFrameData(&D_TI_A000934, 0, &D_i5_801BCDC8[16]);

            if ((gPlayer[0].trueZpos - this->obj.pos.z) <= 450.0f) {
                gPlayer[0].unk_19C = -1;
                gPlayer[0].unk_000 = 0.0f;
                this->swork[1] = 2;
                this->swork[31] = 0;
                this->swork[30]++;
            }
            break;

        case 2:
            if (this->dmgType == DMG_BEAM) {
                switch (D_i5_801B8C0C[this->dmgPart]) {
                    case 0:
                        D_i5_801BBEF0[30] = 15;
                        AUDIO_PLAY_SFX(NA_SE_EN_DAMAGE_S, this->sfxSource, 4);
                        break;
                    case 1:
                        D_i5_801BBEF0[33] = 15;
                        AUDIO_PLAY_SFX(NA_SE_EN_DAMAGE_S, this->sfxSource, 4);
                        break;
                    case 2:
                        D_i5_801BBEF0[34] = 15;
                        AUDIO_PLAY_SFX(NA_SE_EN_DAMAGE_S, this->sfxSource, 4);
                        break;
                }
            }
            if (this->dmgType == DMG_BOMB) {
                if ((this->dmgPart == 5) || (this->dmgPart == 7) || (this->dmgPart == 14)) {
                    switch (D_i5_801B8C0C[this->dmgPart]) {
                        case 0:
                            D_i5_801BBEF0[30] = 15;
                            break;
                        case 1:
                            D_i5_801BBEF0[33] = 15;
                            break;
                        case 2:
                            D_i5_801BBEF0[34] = 15;
                            break;
                    }
                }
            }

            if (this->dmgType != DMG_NONE) {
                D_i5_801BBEF0[48]++;
            }

            if ((D_i5_801BBEF0[48] >= 3) || (this->swork[31] >= 90)) {
                D_i5_801BBEF4[45] = -240.0f;
                D_i5_801BBEF4[46] = -40.0f;
                D_i5_801BBEF4[47] = -200.0f;
                D_i5_801BBEF4[48] = 240.0f;
                D_i5_801BBEF4[49] = -40.0f;
                D_i5_801BBEF4[50] = -200.0f;
                D_i5_801BBEF4[51] = 0.0f;
                D_i5_801BBEF4[52] = -200.0f;
                D_i5_801BBEF4[53] = -450.0f;
                D_i5_801BBEF4[55] = 0.0f;
                D_i5_801BBEF4[63] = 0.0f;
                this->vel.z = gPlayer[0].vel.z;
                D_i5_801BBEF0[27] = 100;
                D_i5_801BBEF0[29] = 30;
                D_i5_801BBEF0[31] = 5;
                D_i5_801BBEF0[32] = 2;
                D_i5_801BBEF0[35] = 5;
                D_i5_801BBEF0[37] = 2;
                D_i5_801BBEF0[36] = 5;
                D_i5_801BBEF0[38] = 2;
                gPlayer[0].unk_19C = 0;
                this->swork[1] = 3;
                AUDIO_PLAY_BGM(NA_BGM_BOSS_TI);
            }
            break;

        case 3:
            if (D_i5_801BBEF0[22] == 37) {
                sp54.x = (this->obj.pos.x + D_i5_801BBEF4[39]) + D_i5_801BBEF4[68];
                sp54.y = 0.0f;
                sp54.z = (this->obj.pos.z + D_i5_801BBEF4[41]) + D_i5_801BBEF4[70];
                Effect_SpawnTimedSfxAtPos(&sp54, NA_SE_EN_BOSS_ATTACK);
                this->swork[39] = 5;
                gCameraShake = 5;
            }

            if (D_i5_801BBEF0[23] == 37) {
                sp54.x = (this->obj.pos.x + D_i5_801BBEF4[42]) + D_i5_801BBEF4[71];
                sp54.y = 0.0f;
                sp54.z = (this->obj.pos.z + D_i5_801BBEF4[44]) + D_i5_801BBEF4[73];
                Effect_SpawnTimedSfxAtPos(&sp54, NA_SE_EN_BOSS_ATTACK);
                this->swork[39] = 5;
                gCameraShake = 5;
            }

            if (this->dmgType == DMG_BEAM) {
                switch (D_i5_801B8C0C[this->dmgPart]) {
                    case 0:
                        D_i5_801BBEF0[30] = 15;
                        D_i5_801BBEF0[27] -= this->damage;
                        AUDIO_PLAY_SFX(NA_SE_EN_DAMAGE_S, this->sfxSource, 4);
                        break;

                    case 1:
                        D_i5_801BBEF0[33] = 15;
                        D_i5_801BBEF0[27] -= this->damage;
                        AUDIO_PLAY_SFX(NA_SE_EN_DAMAGE_S, this->sfxSource, 4);
                        break;

                    case 2:
                        D_i5_801BBEF0[34] = 15;
                        D_i5_801BBEF0[27] -= this->damage;
                        AUDIO_PLAY_SFX(NA_SE_EN_DAMAGE_S, this->sfxSource, 4);
                        break;
                }
                this->dmgType = DMG_NONE;
            }

            if ((this->dmgType == DMG_BOMB) &&
                ((this->dmgPart == 5) || (this->dmgPart == 7) || (this->dmgPart == 14))) {
                this->dmgType = DMG_NONE;

                switch (D_i5_801B8C0C[this->dmgPart]) {
                    case 0:
                        D_i5_801BBEF0[30] = 15;

                        D_i5_801BBEF0[27] -= this->damage;
                        break;

                    case 1:
                        D_i5_801BBEF0[33] = 15;

                        D_i5_801BBEF0[27] -= this->damage;
                        break;

                    case 2:
                        D_i5_801BBEF0[34] = 15;

                        D_i5_801BBEF0[27] -= this->damage;
                        break;
                }
            }

            Math_SmoothStepToF(&this->vel.z, gPlayer[0].vel.z, 0.7f, 1.0f, 0.01f);
            Math_SmoothStepToF(&this->obj.pos.x, gPlayer[0].pos.x, 0.1f, 6.0f, 0.01f);
            Math_SmoothStepToF(&this->obj.pos.z, gPlayer[0].trueZpos - 450.0f, 0.1f, 1.0f, 0.01f);

            Animation_GetFrameData(&D_TI_A000D50, D_i5_801BBEF0[24] >> 1, &D_i5_801BC978[16]);

            switch (D_i5_801BBEF0[39]) {
                case 0:
                    Animation_GetFrameData(&D_TI_A000858, D_i5_801BBEF0[22] >> 1, &D_i5_801BC978[0]);
                    break;
                case 1:
                    Animation_GetFrameData(&D_TI_A00047C, D_i5_801BBEF0[22] >> 1, &D_i5_801BC978[0]);
                    break;
            }

            switch (D_i5_801BBEF0[40]) {
                case 0:
                    Animation_GetFrameData(&D_TI_A000858, D_i5_801BBEF0[23] >> 1, &D_i5_801BC978[8]);
                    break;
                case 1:
                    Animation_GetFrameData(&D_TI_A00047C, D_i5_801BBEF0[23] >> 1, &D_i5_801BC978[8]);
                    break;
            }
            Math_SmoothStepToVec3fArray(&D_i5_801BC978[0], &D_i5_801BCDC8[0], 1, 8, 0.5f, 360.0f, 0.01f);
            Math_SmoothStepToVec3fArray(&D_i5_801BC978[8], &D_i5_801BCDC8[8], 1, 8, 0.5f, 360.0f, 0.01f);
            Math_SmoothStepToVec3fArray(&D_i5_801BC978[16], &D_i5_801BCDC8[16], 1, 13, 0.5f, 5.0f, 0.01f);
            D_i5_801BBEF0[24]++;
            D_i5_801BBEF0[22]++;
            D_i5_801BBEF0[23]++;

            if (D_i5_801BBEF0[24] >= (Animation_GetFrameCount(&D_TI_A000D50) * 2)) {
                D_i5_801BBEF0[24] = 0;
            }

            switch (D_i5_801BBEF0[39]) {
                case 0:
                    if (D_i5_801BBEF0[22] >= (Animation_GetFrameCount(&D_TI_A000858) * 2)) {
                        D_i5_801BBEF0[22] = 0;
                    }
                    break;

                case 1:
                    if (D_i5_801BBEF0[22] >= (Animation_GetFrameCount(&D_TI_A00047C) * 2)) {
                        D_i5_801BBEF0[22] = 0;
                    }
                    break;
            }

            switch (D_i5_801BBEF0[40]) {
                case 0:
                    if (D_i5_801BBEF0[23] >= (Animation_GetFrameCount(&D_TI_A000858) * 2)) {
                        D_i5_801BBEF0[23] = 0;
                    }
                    break;
                case 1:
                    if (D_i5_801BBEF0[23] >= (Animation_GetFrameCount(&D_TI_A00047C) * 2)) {
                        D_i5_801BBEF0[23] = 0;
                    }
                    break;
            }

            D_i5_801BBEF4[51] = SIN_DEG((((s32) (this->swork[38] % 128U) * 360.0f) / 128)) * 40.0f;

            switch (D_i5_801BBEF0[28]) {
                case 0:
                    if (D_i5_801BBEF0[29] == 0) {
                        D_i5_801BBEF0[28] = 1;
                    }
                    break;

                case 1:
                    if (D_i5_801BBEF0[22] == 0) {
                        D_i5_801BBEF0[39] = 1;
                        D_i5_801BBEF4[45] = 0.0f;
                        D_i5_801BBEF4[47] = 0.0f;
                        D_i5_801BBEF4[55] = RAND_FLOAT(2.0f) - 1.0f;
                        D_i5_801BBEF0[28] = 2;
                    }
                    break;

                case 2:
                    if (D_i5_801BBEF0[22] == 0) {
                        D_i5_801BBEF0[39] = 0;
                        D_i5_801BBEF4[45] = -240.0f + RAND_FLOAT(30.0f) - 15.0f;
                        D_i5_801BBEF4[47] = -200.0f + RAND_FLOAT(20.0f);
                        D_i5_801BBEF4[55] = RAND_FLOAT(20.0f);
                        D_i5_801BBEF0[28] = 3;
                    }
                    break;

                case 3:
                    if (D_i5_801BBEF0[23] == 0) {
                        D_i5_801BBEF0[40] = 1;
                        D_i5_801BBEF4[48] = 0.0f;
                        D_i5_801BBEF4[50] = 0.0f;
                        D_i5_801BBEF4[63] = RAND_FLOAT(2.0f) - 1.0f;
                        D_i5_801BBEF0[28] = 4;
                    }
                    break;

                case 4:
                    if (D_i5_801BBEF0[23] == 0) {
                        D_i5_801BBEF0[40] = 0;
                        D_i5_801BBEF4[48] = 240.0f + RAND_FLOAT(30.0f) - 15.0f;
                        D_i5_801BBEF4[50] = -200.0f + RAND_FLOAT(20.0f);
                        D_i5_801BBEF4[63] = -Rand_ZeroOne() * 20.0f;
                        D_i5_801BBEF0[28] = 1;
                    }
                    break;

                default:
                    break;
            }

            if (D_i5_801BBEF0[27] <= 0) {
                D_i5_801BBEF4[45] = -90.0f;
                D_i5_801BBEF4[46] = -70.0f;
                D_i5_801BBEF4[47] = -250.0f;
                D_i5_801BBEF4[48] = 90.0f;
                D_i5_801BBEF4[49] = -70.0f;
                D_i5_801BBEF4[50] = -250.0f;
                D_i5_801BBEF4[51] = 0.0f;
                D_i5_801BBEF4[52] = -100.0f;
                D_i5_801BBEF4[53] = -350.0f;
                D_i5_801BBEF4[63] = 0.0f;
                D_i5_801BBEF4[55] = D_i5_801BBEF4[63];

                AUDIO_PLAY_SFX(NA_SE_EN_APPEAR_SAND, this->sfxSource, 4);
                AUDIO_PLAY_SFX(NA_SE_EN_TIBOSS_DM_CRY, this->sfxSource, 4);

                this->swork[1] = 4;
                this->timer_050 = 120;

                D_i5_801BBEF0[22] = 0;
                D_i5_801BBEF0[23] = 0;
                D_i5_801BBEF0[24] = 0;

                this->swork[31] = 0;
                this->fwork[0] = 0.0f;
                this->swork[30]++;
            }
            break;

        case 4:
            this->vel.z = gPlayer[0].vel.z;

            Animation_GetFrameData(&D_TI_8000D80, D_i5_801BBEF0[22] >> 1, &D_i5_801BC978[0]);
            Animation_GetFrameData(&D_TI_8000D80, D_i5_801BBEF0[23] >> 1, &D_i5_801BC978[8]);
            Animation_GetFrameData(&D_TI_8000708, D_i5_801BBEF0[24] >> 1, &D_i5_801BC978[16]);

            Math_SmoothStepToF(&this->fwork[0], 0.5f, 0.05f, 0.05f, 0.01f);

            Math_SmoothStepToVec3fArray(&D_i5_801BC978[0], &D_i5_801BCDC8[0], 1, 8, this->fwork[0], 360.0f, 0.01f);
            Math_SmoothStepToVec3fArray(&D_i5_801BC978[8], &D_i5_801BCDC8[8], 1, 8, this->fwork[0], 360.0f, 0.01f);
            Math_SmoothStepToVec3fArray(&D_i5_801BC978[16], &D_i5_801BCDC8[16], 1, 13, this->fwork[0], 360.0f, 0.01f);

            if (this->timer_050 <= 120) {
                if (D_i5_801BBEF0[22] < ((Animation_GetFrameCount(&D_TI_8000D80) * 2) - 1)) {
                    D_i5_801BBEF0[22]++;
                }
            }
            if (this->timer_050 < 108) {
                if (D_i5_801BBEF0[23] < ((Animation_GetFrameCount(&D_TI_8000D80) * 2) - 1)) {
                    D_i5_801BBEF0[23]++;
                }
            }
            if (this->timer_050 <= 120) {
                if (D_i5_801BBEF0[24] < ((Animation_GetFrameCount(&D_TI_8000708) * 2) - 1)) {
                    D_i5_801BBEF0[24]++;
                }
            }
            if (this->timer_050 == 0) {
                this->swork[1] = 5;
                this->timer_050 = 90;
            }
            break;
    }

    if ((this->state >= 3) && (this->state < 5)) {
        if ((this->state != 4) || (this->swork[31] < 100)) {
            temp_ft2 = this->obj.pos.x + D_i5_801BBEF4[36];
            temp_ft4 = this->obj.pos.z + D_i5_801BBEF4[38];

            temp_fa1 = D_i5_801BBEF4[57] - temp_ft2;
            temp_fv1 = D_i5_801BBEF4[58] - temp_ft4;

            if ((s32) sqrtf(SQ(temp_fa1) + SQ(temp_fv1)) > 50.0f) {
                effect = Effect_Load(OBJ_EFFECT_394);
                if (effect != NULL) {
                    effect->obj.status = OBJ_ACTIVE;
                    effect->unk_7A = 10;
                    effect->unk_78 = effect->unk_7A;
                    effect->obj.pos.x = temp_ft2;
                    effect->obj.pos.y = this->obj.pos.y;
                    effect->obj.pos.z = temp_ft4;

                    effect->obj.rot.y = (Math_Atan2F(-temp_fv1, temp_fa1) * M_RTOD) - 90.0f;
                    effect->info.unk_14 = -1;
                    effect->unk_46 = 70;
                    effect->scale2 = sqrtf(SQ(temp_fa1) + SQ(temp_fv1)) / 26.0f;
                }
                D_i5_801BBEF4[57] = temp_ft2;
                D_i5_801BBEF4[58] = temp_ft4;
            }

            if ((this->swork[38] & 3) == 0) {
                Effect_Effect359_Spawn(temp_ft2, this->obj.pos.y, temp_ft4, 10.0f, 192, 16, 0);
            }
        }

        if ((this->state != 4) || (this->swork[31] < 90)) {
            temp_ft2 = this->obj.pos.x + D_i5_801BBEF4[39];
            temp_ft4 = this->obj.pos.z + D_i5_801BBEF4[41];

            temp_fa1 = D_i5_801BBEF4[59] - temp_ft2;
            temp_fv1 = D_i5_801BBEF4[60] - temp_ft4;

            if ((s32) sqrtf(SQ(temp_fa1) + SQ(temp_fv1)) > 50.0f) {
                effect = Effect_Load(OBJ_EFFECT_394);
                if (effect != NULL) {
                    effect->obj.status = OBJ_ACTIVE;
                    effect->unk_7A = 10;
                    effect->unk_78 = effect->unk_7A;
                    effect->obj.pos.x = temp_ft2;
                    effect->obj.pos.y = this->obj.pos.y;
                    effect->obj.pos.z = temp_ft4;

                    effect->obj.rot.y = (Math_Atan2F(-temp_fv1, temp_fa1) * M_RTOD) - 90.0f;
                    effect->info.unk_14 = -1;
                    effect->unk_46 = 50;
                    effect->scale2 = sqrtf(SQ(temp_fa1) + SQ(temp_fv1)) / 26.0f;
                }
                D_i5_801BBEF4[59] = temp_ft2;
                D_i5_801BBEF4[60] = temp_ft4;
            }

            if ((this->swork[38] & 3) == 0) {
                Effect_Effect359_Spawn(temp_ft2, this->obj.pos.y, temp_ft4, 10.0f, 192, 16, 0);
            }
        }

        if ((this->state != 4) || (this->swork[31] < 102)) {
            temp_ft2 = this->obj.pos.x + D_i5_801BBEF4[42];
            temp_ft4 = this->obj.pos.z + D_i5_801BBEF4[44];

            temp_fa1 = D_i5_801BBEF4[61] - temp_ft2;
            temp_fv1 = D_i5_801BBEF4[62] - temp_ft4;

            if ((s32) sqrtf(SQ(temp_fa1) + SQ(temp_fv1)) > 50.0f) {
                effect = Effect_Load(OBJ_EFFECT_394);
                if (effect != NULL) {
                    effect->state = 10;
                    effect->unk_7A = 10;
                    effect->unk_78 = effect->unk_7A;
                    effect->obj.pos.x = temp_ft2;
                    effect->obj.pos.y = this->obj.pos.y;
                    effect->obj.pos.z = temp_ft4;

                    effect->obj.rot.y = (Math_Atan2F(-temp_fv1, temp_fa1) * M_RTOD) - 90.0f;
                    effect->info.unk_14 = -1;
                    effect->unk_46 = 50;
                    effect->scale2 = sqrtf(SQ(temp_fa1) + SQ(temp_fv1)) / 26.0f;
                }
                D_i5_801BBEF4[61] = temp_ft2;
                D_i5_801BBEF4[62] = temp_ft4;
            }

            if ((this->swork[38] & 3) == 0) {
                Effect_Effect359_Spawn(temp_ft2, this->obj.pos.y, temp_ft4, 10.0f, 192, 16, 0);
            }
        }
    }
    this->dmgType = DMG_NONE;
}

void Titania_80193B30(TiGoras* this) {
    if (this->state == this->swork[1]) {
        if (this->swork[1] != 11) {
            this->swork[1] = 11;
        } else {
            this->swork[1] = 9;
        }
    }

    switch (this->swork[1]) {
        case 8:
            if ((this->swork[11] <= 0) && (this->swork[12] <= 0)) {
                if (this->swork[35] == 0) {
                    this->swork[1] = 12;
                } else {
                    this->swork[1] = 11;
                }
            }
            break;

        case 10:
            if (D_i5_801BBEF0[8] != 0) {
                this->swork[1] = 12;
            }
            break;

        case 11:
            if (this->swork[35] == 0) {
                this->swork[1] = 8;
            }
            break;
    }

    if (this->swork[1] != 7) {
        this->swork[36]++;
    } else {
        this->swork[36] = 0;
    }

    if (this->swork[36] >= 2) {
        this->swork[1] = 7;
        this->swork[36] = 0;
    }

    if (this->swork[1] == 8) {
        this->swork[3] = 2;
    } else {
        this->swork[3] = 1;
    }

    D_i5_801BBEF4[11] = D_i5_801B7738[this->swork[1]];

    switch (this->swork[1]) {
        case 7:
        case 8:
        case 9:
        case 10:
            if (this->fwork[35] != 1.0f) {
                D_i5_801BBEF0[13] = 1;
                this->fwork[35] = 1.0f;
                D_i5_801BBEF4[32] = 10.0f;
                D_i5_801BBEF4[33] = 10.0f;
            }
            break;

        case 11:
            this->fwork[35] = 0.0f;
            break;

        case 12:
            this->fwork[35] = 0.0f;
            break;
    }

    switch (this->swork[1]) {
        case 7:
            if (this->swork[9] > 0) {
                this->fwork[36] = 1.0f;
                D_i5_801BBEF0[14] = 1;
                D_i5_801BBEF4[34] = 1.0f;
            }
            if ((this->swork[10] > 0) && (D_i5_801BBEF0[8] != 0)) {
                this->fwork[37] = 1.0f;
                D_i5_801BBEF0[15] = 1;
                D_i5_801BBEF4[35] = 1.0f;
            }
            this->swork[34] = 1;
            break;

        case 8:
            this->swork[34] = 1;
            break;

        case 9:
            this->swork[34] = 1;
            break;

        case 10:
            this->swork[34] = 1;
            break;

        case 11:
            this->swork[34] = 1;
            this->swork[24] = 1;
            this->fwork[45] = 230.0f;
            break;

        case 12:
            this->swork[34] = 2;
            this->fwork[48] = 0.0f;
            break;

        default:
            break;
    }
}

const s16 D_i5_801BAA50[19] = {
    0, 1, 91, 34, 90, 68, 33, 32, 31, 30, 29, 53, 37, 36, 35, 47, 40, 39, 38,
};

const s16 D_i5_801BAA78[34] = {
    0, 0, 0, 0, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

const s16 D_i5_801BAABC[4][10] = {
    { 22, 21, 20, 44, 45, 46, 47, 48, 57, -1 },
    { 5, 6, 7, 39, 40, 41, 42, 43, 63, -1 },
    { 8, 9, 10, 11, 12, 13, 50, -1, 0, 0 },
    { 14, 15, 16, 17, 18, 19, 58, -1, 0, 0 },
};

const s16 D_i5_801BAB0C[4][10] = {
    { 0, 0, 0, 5, 5, 5, 5, 5, 5, -1 },
    { 0, 0, 0, 5, 5, 5, 5, 5, 5, -1 },
    { 0, 5, 5, 5, 5, 5, 5, -1, 0, 0 },
    { 0, 5, 5, 5, 5, 5, 5, -1, 0, 0 },
};

const char D_i5_801BAB5C[] = "Enm->chpt=<%d>\n";

#ifdef NON_MATCHING
// https://decomp.me/scratch/KiTNa
// Regalloc in the random ternary. Can't be a temp as it's too low on stack

// Titania_TiGoras_Attack ?
void Titania_80193DF0(TiGoras* this) {
    Vec3f spD4;
    Vec3f spC8;
    Actor* actor;
    Effect* effect;
    s32 var_v1;
    s32 spB8;
    s32 i;
    s32 j;
    f32 temp_f;
    s32 pad;
    s32 spA4;
    s32 pad2;
    f32 sp9C;
    Vec3f sp90;
    Vec3f sp84;

    Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);

    for (i = 0; i < ARRAY_COUNTU(D_i5_801BBF00); i++) {
        if (D_i5_801BBF00[i].unk_26 & 0x10) {
            if ((i == 39) && (D_i5_801BBEF0[8] == 0)) {
                this->swork[37] |= 0x10 | 0x8;
                D_i5_801BBEF0[44] = 0;
                D_i5_801BBEF0[8] = -1;
                D_i5_801BBEF0[41] = 1;
                actor = Game_SpawnActor(OBJ_ACTOR_TEAM_BOSS);
                if (actor != NULL) {
                    Matrix_MultVec3f(gCalcMatrix, &D_i5_801BBF00[i].unk_00.pos, &spC8);
                    actor->obj.pos.x = this->obj.pos.x + spC8.x;
                    actor->obj.pos.y = this->obj.pos.y + spC8.y;
                    actor->obj.pos.z = this->obj.pos.z + spC8.z;
                    actor->obj.rot.x = this->obj.rot.x + D_i5_801BBF00[i].unk_00.rot.x;
                    actor->obj.rot.y = this->obj.rot.y + D_i5_801BBF00[i].unk_00.rot.y;
                    actor->obj.rot.z = this->obj.rot.z + D_i5_801BBF00[i].unk_00.rot.z;
                }
            }
            D_i5_801BBF00[i].unk_26 &= ~16;
        }

        if (D_i5_801BBF00[i].unk_26 & 2) {
            actor = Game_SpawnActor(OBJ_ACTOR_DEBRIS);
            if (actor != NULL) {
                actor->state = 40;
                actor->work_046 = D_i5_801B7770[i][5];
                actor->work_048 = D_i5_801B7770[i][1];
                if (D_i5_801B7770[i][0] == 85) {
                    actor->fwork[0] = 5.0f;
                    actor->fwork[1] = 5.0f;

                    actor->obj.pos.x = this->obj.pos.x + D_i5_801BBF00[i].unk_00.pos.x;
                    actor->obj.pos.y = this->obj.pos.y + D_i5_801BBF00[i].unk_00.pos.y;
                    actor->obj.pos.z = this->obj.pos.z + D_i5_801BBF00[i].unk_00.pos.z;

                    actor->obj.rot.x = this->obj.rot.x + D_i5_801BBF00[i].unk_00.rot.x;
                    actor->obj.rot.y = this->obj.rot.y + D_i5_801BBF00[i].unk_00.rot.y;
                    actor->obj.rot.z = this->obj.rot.z + D_i5_801BBF00[i].unk_00.rot.z;

                    Matrix_Push(&gCalcMatrix);
                    Matrix_RotateY(gCalcMatrix, 0.0f, MTXF_NEW);
                    Matrix_MultVec3f(gCalcMatrix, &D_i5_801B8D18, &spC8);
                    Matrix_Pop(&gCalcMatrix);

                    actor->vel.x = spC8.x;
                    actor->vel.y = 5.0f;
                    actor->vel.z = spC8.z;

                    actor->gravity = 0.8f;
                } else {
                    actor->fwork[0] = 10.0f + RAND_FLOAT(10.0f);
                    actor->fwork[1] = 10.0f + RAND_FLOAT(10.0f);

                    actor->obj.pos.x = this->obj.pos.x + D_i5_801BBF00[i].unk_00.pos.x;
                    actor->obj.pos.y = this->obj.pos.y + D_i5_801BBF00[i].unk_00.pos.y;
                    actor->obj.pos.z = this->obj.pos.z + D_i5_801BBF00[i].unk_00.pos.z;

                    actor->obj.rot.x = this->obj.rot.x + D_i5_801BBF00[i].unk_00.rot.x;
                    actor->obj.rot.y = this->obj.rot.y + D_i5_801BBF00[i].unk_00.rot.y;
                    actor->obj.rot.z = this->obj.rot.z + D_i5_801BBF00[i].unk_00.rot.z;

                    Matrix_Push(&gCalcMatrix);
                    Matrix_RotateY(gCalcMatrix, RAND_FLOAT(360.0f) * M_DTOR, MTXF_NEW);
                    Matrix_MultVec3f(gCalcMatrix, &D_i5_801B8D0C, &spC8);
                    Matrix_Pop(&gCalcMatrix);

                    actor->vel.x = spC8.x;
                    // pad2 = ((Rand_ZeroOne() < 0.5f) ? -1 : 1);
                    actor->vel.y = ((Rand_ZeroOne() < 0.5f) ? -1 : 1) * (15.0f + RAND_FLOAT(2.0f));
                    actor->vel.z = spC8.z;
                    actor->gravity = 2.5f;
                }
            }
            D_i5_801BBF00[i].unk_26 = 4;
            AUDIO_PLAY_SFX(NA_SE_EN_EXPLOSION_M, this->sfxSource, 4);
        }
    }

    if (this->fwork[38] != 0.0f) {
        Math_SmoothStepToF(&D_i5_801BBEF4[15], D_i5_801BBEF4[24], 1.0f, D_i5_801BBEF4[32], 0.01f);
        Math_SmoothStepToAngle(&D_i5_801BBEF4[16], D_i5_801BBEF4[25], 1.0f, D_i5_801BBEF4[33], 0.01f);
    }
    if (this->fwork[39] != 0.0f) {
        Math_SmoothStepToAngle(&D_i5_801BBEF4[18], D_i5_801BBEF4[27], 1.0f, D_i5_801BBEF4[34], 0.01f);
        Math_SmoothStepToAngle(&D_i5_801BBEF4[19], D_i5_801BBEF4[28], 1.0f, D_i5_801BBEF4[34], 0.01f);
    }
    if (this->fwork[40] != 0.0f) {
        Math_SmoothStepToAngle(&D_i5_801BBEF4[21], D_i5_801BBEF4[30], 1.0f, D_i5_801BBEF4[35], 0.01f);
        Math_SmoothStepToAngle(&D_i5_801BBEF4[22], D_i5_801BBEF4[31], 1.0f, D_i5_801BBEF4[35], 0.01f);
    }

    Math_SmoothStepToF(&this->fwork[38], this->fwork[35], 1.0f, 0.3f, 0.01f);
    Math_SmoothStepToF(&this->fwork[39], this->fwork[36], 0.2f, 0.5f, 0.01f);
    Math_SmoothStepToF(&this->fwork[40], this->fwork[37], 0.2f, 0.5f, 0.01f);

    if (D_i5_801BBEF0[6] > 0) {
        D_i5_801BBEF0[6]--;
        if (D_i5_801BBEF0[6] == 0) {
            for (i = 0; i < ARRAY_COUNTU(D_i5_801BBF00); i++) {
                D_i5_801BBF00[i].unk_18.x = D_i5_801BBF00[i].unk_18.y = D_i5_801BBF00[i].unk_18.z = 0.0f;
            }
        }
    }

    for (i = 0; i < 4; i++) {
        if (this->swork[5 + i] > 0) {
            this->swork[5 + i]--;
        }
    }

    for (i = 0; i < ARRAY_COUNT(D_i5_801BD668); i++) {
        if (D_i5_801BD668[i] > 0) {
            D_i5_801BD6B0[i] += D_i5_801B7960[i][3];
            D_i5_801BD668[i]--;
        }
    }

    if (this->swork[22] > 0) {
        this->swork[22]--;
    }
    if (this->swork[28] != 0) {
        if (this->swork[27] > 0) {
            this->swork[27]--;
        }
    }

    if (D_i5_801BBEF0[2] > 0) {
        D_i5_801BBEF0[2]--;
    }

    if (D_i5_801BBEF0[4] > 0) {
        D_i5_801BBEF0[4]--;
    }

    if ((D_i5_801BBEF0[3] != 0) &&
        (Math_SmoothStepToAngle(&D_i5_801BBEF4[6], D_i5_801BBEF4[7], 1.0f, 8.0f, 0.01f) == 0.0f)) {
        if (D_i5_801BBEF4[7] == 48.0f) {
            D_i5_801BBEF4[7] = 0.0f;
        } else {
            D_i5_801BBEF4[7] = 48.0f;
            D_i5_801BBEF0[3]--;
        }
    }

    if ((D_i5_801BBEF0[5] != 0) &&
        (Math_SmoothStepToAngle(&D_i5_801BBEF4[8], D_i5_801BBEF4[9], 1.0f, 8.0f, 0.01f) == 0.0f)) {
        if (D_i5_801BBEF4[9] == 48.0f) {
            D_i5_801BBEF4[9] = 0.0f;
        } else {
            D_i5_801BBEF4[9] = 48.0f;
            D_i5_801BBEF0[5]--;
        }
    }

    if (D_i5_801BBEF0[6] != 0) {
        for (i = 0; i < ARRAY_COUNTU(D_i5_801BBF00); i++) {
            for (j = 0; j < ARRAY_COUNT(D_i5_801B8160); j++) {
                if (D_i5_801B7770[i][0] == D_i5_801B8160[j]) {
                    break;
                }
            }
            if (this->animFrame) {}

            if (j == ARRAY_COUNT(D_i5_801B8160)) {
                D_i5_801BBF00[i].unk_18.z = RAND_FLOAT(5.0f) - 2.5f;
            }
        }
    }

    for (i = 0; i < 4; i++) {
        if ((this->swork[9 + i] > 0) && (this->swork[9 + i] <= 10)) {
            D_i5_801BD668[24 + i] = 1;
        }
    }

    if ((this->state >= 7) && (this->state < 14) && (this->dmgType == DMG_BEAM) &&
        (D_i5_801BAA78[D_i5_801B7904[this->dmgPart]] == 2) && (D_i5_801BBEF0[8] == 0)) {
        AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
        this->dmgType = DMG_NONE;
    }
    if ((this->state >= 7) && (this->state < 14)) {
        if (this->dmgType == DMG_BEAM) {
            this->dmgType = DMG_NONE;
            D_i5_801BD668[D_i5_801B7904[this->dmgPart]] = D_i5_801B7960[D_i5_801B7904[this->dmgPart]][1];
            D_i5_801BD6B0[D_i5_801B7904[this->dmgPart]] = 0;

            if ((D_i5_801B7904[this->dmgPart] == 6) && (this->state == 11)) {
                D_i5_801BD668[D_i5_801B7904[this->dmgPart]] = 0;
            }

            if (D_i5_801BAA78[D_i5_801B7904[this->dmgPart]] != 0) {
                AUDIO_PLAY_SFX(NA_SE_EN_TIBOSS_DM_CRY, this->sfxSource, 4);
                this->swork[D_i5_801BAA78[D_i5_801B7904[this->dmgPart]] + 4] = 20;
                if (this->swork[D_i5_801BAA78[D_i5_801B7904[this->dmgPart]] + 8] > 0) {
                    this->swork[D_i5_801BAA78[D_i5_801B7904[this->dmgPart]] + 8] -= this->damage;
                    if (this->swork[D_i5_801BAA78[D_i5_801B7904[this->dmgPart]] + 8] <= 0) {
                        this->swork[D_i5_801BAA78[D_i5_801B7904[this->dmgPart]] + 8] = 0;
                        D_i5_801BBEF0[6] = 40;
                        D_i5_801BBEF4[10] = 2.0f;
                    }
                }
                pad = 0;
                for (i = 0; i < 4; i++) {
                    if (this->swork[9 + i] <= 0) {
                        pad++;
                    }
                }
                if ((pad == 3) && (D_i5_801BBEF0[8] == 0)) {
                    D_i5_801BBF00[39].unk_26 |= 0x10 | 0x1;
                }
                if (pad == 4) {
                    D_i5_801BBEF0[41] = 0;
                    this->swork[28] = 1;
                    this->swork[27] = 80;
                    this->swork[35]++;
                }
            } else if ((gBossHealthBar > 0) && (D_i5_801B7904[this->dmgPart] == 23) && (this->swork[29] != 0) &&
                       (this->swork[21] > 0)) {
                this->swork[21] -= this->damage;
                if (this->swork[21] <= 0) {
                    gTeamLowHealthMsgTimer = -1;
                    this->swork[21] = 0;
                    gScreenFlashTimer = 8;
                    AUDIO_PLAY_SFX(NA_SE_EN_DOWN_IMPACT, this->sfxSource, 4);
                } else {
                    AUDIO_PLAY_SFX(NA_SE_EN_TIBOSS_DM_CRY, this->sfxSource, 4);

                    if (this->swork[21] <= 10) {
                        D_i5_801BBEF0[1] = 15;
                    } else if (this->swork[21] <= 20) {
                        D_i5_801BBEF0[1] = 20;
                    }
                }
                gBossHealthBar = (s32) ((this->swork[21] * 255.0f) / 100.0f);
                this->swork[22] = 20;
                D_i5_801BBEF0[6] = 20;

                D_i5_801BBEF4[10] = 4.0f;
            } else if (D_i5_801B7904[this->dmgPart] == 28) {
                this->swork[37] |= 4;
                D_i5_801BBEF0[43] = 0;
            } else {
                AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
            }
        }

        if ((this->dmgType == DMG_BOMB) && (this->dmgPart == 1) && (D_i5_801BBEF0[8] == 0)) {
            this->dmgType = DMG_NONE;
        }
        if (this->dmgType == DMG_BOMB) {
            this->dmgType = DMG_NONE;
            switch (this->dmgPart) {
                case 0:
                case 1:
                case 2:
                case 3:
                    AUDIO_PLAY_SFX(NA_SE_EN_TIBOSS_DM_CRY, this->sfxSource, 4);
                    this->swork[this->dmgPart + 5] = 20;

                    if (this->swork[this->dmgPart + 9] <= 0) {
                        break;
                    }

                    this->swork[this->dmgPart + 9] -= this->damage;

                    if (this->swork[this->dmgPart + 9] <= 0) {
                        this->swork[this->dmgPart + 9] = 0;
                        D_i5_801BBEF0[6] = 40;
                        D_i5_801BBEF4[10] = 2.0f;
                        pad = 0;

                        for (i = 0; i < 4; i++) {
                            if (this->swork[9 + i] <= 0) {
                                pad++;
                            }
                        }

                        if ((pad == 3) && (D_i5_801BBEF0[8] == 0)) {
                            D_i5_801BBF00[39].unk_26 |= 0x11;
                        }
                        if (pad == 4) {
                            D_i5_801BBEF0[41] = 0;
                            this->swork[28] = 1;
                            this->swork[27] = 80;
                            this->swork[35]++;
                        }
                    }
                    break;

                case 4:
                    if ((gBossHealthBar > 0) && (this->swork[29] != 0) && (this->swork[21] > 0)) {
                        AUDIO_PLAY_SFX(NA_SE_EN_TIBOSS_DM_CRY, this->sfxSource, 4);

                        this->swork[21] -= this->damage;

                        if (this->swork[21] <= 0) {
                            this->swork[21] = 0;
                            gScreenFlashTimer = 8;
                            gTeamLowHealthMsgTimer = -1;
                            AUDIO_PLAY_SFX(NA_SE_EN_DOWN_IMPACT, this->sfxSource, 4);
                        } else {
                            AUDIO_PLAY_SFX(NA_SE_EN_TIBOSS_DM_CRY, this->sfxSource, 4);

                            if (this->swork[21] < 11) {
                                D_i5_801BBEF0[1] = 15;
                            } else if (this->swork[21] < 21) {
                                D_i5_801BBEF0[1] = 20;
                            }
                        }
                        gBossHealthBar = (s32) ((this->swork[21] * 255.0f) / 100.0f);
                        this->swork[22] = 20;
                        D_i5_801BBEF0[6] = 20;
                        D_i5_801BBEF4[10] = 4.0f;
                    }
                    break;
            }
        }
    }

    if ((this->state >= 6) && (this->state < 14) && (D_i5_801BBEF0[1] != 0)) {
        D_i5_801BBEF0[0]++;
        if (D_i5_801BBEF0[0] >= D_i5_801BBEF0[1]) {
            D_i5_801BBEF0[0] -= D_i5_801BBEF0[1];
        }
    }

    switch (this->swork[28]) {
        case 1:
            if (this->swork[27] == 0) {
                this->swork[28]++;
            }
            break;

        case 2:
            D_i5_801BBF00[61].unk_26 = 3;
            D_i5_801BBEF4[2] = 0.0f;
            D_i5_801BBEF4[1] = 20.0f;
            this->swork[28]++;
            AUDIO_PLAY_SFX(NA_SE_EN_HEART_OPEN, this->sfxSource, 4);
            AUDIO_PLAY_SFX(NA_SE_EN_HEARTBEAT, this->sfxSource, 4);
            break;

        case 3:
            D_i5_801BBEF4[2] += D_i5_801BBEF4[1];
            D_i5_801BBEF4[1] += 4.0;
            if (D_i5_801BBEF4[2] >= 116.0f) {
                this->swork[28]++;
                D_i5_801BBEF4[3] = 40.0f;
                D_i5_801BBEF4[5] = 5.0f;
                D_i5_801BBEF4[4] = 20.0f;
                this->swork[29] = 1;
                this->swork[37] |= 1;
                AUDIO_PLAY_SFX(NA_SE_EN_DAMAGE_S, this->sfxSource, 4);
            }
            break;

        case 4:
            D_i5_801BBEF4[3]--;
            if (D_i5_801BBEF4[3] == 0) {
                this->swork[27] = 300;
                this->swork[28]++;
            }
            break;

        case 5:
            if (this->swork[27] == 0) {
                D_i5_801BBEF4[3] = 40.0f;
                D_i5_801BBEF4[5] = 5.0f;
                D_i5_801BBEF4[4] = 20.0f;
                this->swork[28]++;
            }
            break;

        case 6:
            D_i5_801BBEF4[3] -= 1;
            if (D_i5_801BBEF4[3] == 0) {
                D_i5_801BBEF4[1] = -40.0f;
                D_i5_801BBEF4[4] = 0.0f;
                this->swork[28]++;
            }
            break;

        case 7:
            D_i5_801BBEF4[2] += D_i5_801BBEF4[1];
            D_i5_801BBEF4[1] -= 3.0;
            if (D_i5_801BBEF4[2] <= 0.0f) {
                Audio_KillSfxBySourceAndId(this->sfxSource, NA_SE_EN_HEARTBEAT);
                this->swork[29] = 0;
                D_i5_801BBEF4[2] = 0.0f;
                this->swork[28]++;
            }
            break;

        case 8:
            AUDIO_PLAY_SFX(NA_SE_EN_GATHER_PARTS, this->sfxSource, 4);

            for (i = 0; i < 33; i++) {
                actor = Game_SpawnActor(OBJ_ACTOR_DEBRIS);
                if (actor != NULL) {
                    actor->state = 40;
                    actor->obj.pos.x = 0.0f;
                    actor->obj.pos.y = 0.0f;
                    actor->obj.pos.z = this->obj.pos.z + 2000.0f;
                    actor->info.cullDistance = 5000.0f;
                    actor->work_046 = D_i5_801B7770[D_i5_801B8198[i].unk_00][5];
                    actor->work_048 = D_i5_801B7770[D_i5_801B8198[i].unk_00][1];
                    D_i5_801B8198[i].unk_0C = D_i5_801B8198[i].unk_04;
                    actor->vel.z = this->vel.z;
                    D_i5_801BBF00[D_i5_801B8198[i].unk_00].unk_26 |= 1;
                }
                D_i5_801B8198[i].actor = actor;
            }
            this->swork[28]++;
            break;

        case 9:
            for (i = 0; i < 33; i++) {
                actor = D_i5_801B8198[i].actor;
                if (actor != NULL) {
                    pad2 = D_i5_801B8198[i].unk_00;
                    actor->obj.pos.x = this->obj.pos.x + (D_i5_801BBF00[pad2].unk_00.pos.x * 2.0f);
                    actor->obj.pos.y = this->obj.pos.y + D_i5_801BBF00[pad2].unk_00.pos.y;
                }
            }
            this->swork[28]++;
            break;

        case 10:
            Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
            spA4 = 0;

            for (i = 0; i < 33; i++) {
                actor = D_i5_801B8198[i].actor;
                if (actor != NULL) {
                    if (D_i5_801B8198[i].unk_0C == 0) {
                        pad2 = D_i5_801B8198[i].unk_00;
                        Matrix_MultVec3f(gCalcMatrix, &D_i5_801BBF00[pad2].unk_00.pos, &spC8);

                        sp9C =
                            fabsf(Math_SmoothStepToF(&actor->obj.pos.x, this->obj.pos.x + spC8.x, 1.0f, 40.0f, 0.01f));
                        sp9C +=
                            fabsf(Math_SmoothStepToF(&actor->obj.pos.y, this->obj.pos.y + spC8.y, 1.0f, 40.0f, 0.01f));
                        sp9C +=
                            fabsf(Math_SmoothStepToF(&actor->obj.pos.z, this->obj.pos.z + spC8.z, 1.0f, 90.0f, 0.01f));

                        actor->obj.rot.x += 20.0f;
                        actor->obj.rot.y += 20.0f;
                        actor->obj.rot.z += 20.0f;

                        if (sp9C <= 25.0f) {
                            D_i5_801BBF00[D_i5_801B8198[i].unk_00].unk_26 = 8;
                            Object_Kill(&actor->obj, actor->sfxSource);
                            D_i5_801B8198[i].actor = NULL;
                        }
                    } else if (D_i5_801B8198[i].unk_0C > 0) {
                        D_i5_801B8198[i].unk_0C--;
                    }
                } else {
                    spA4++;
                }
            }

            if (spA4 == 33) {
                this->swork[28]++;
            }
            break;

        case 11:
            for (i = 0; i < 33U; i++) {
                D_i5_801BBF00[D_i5_801B8198[i].unk_00].unk_26 = 0;
            }

            for (i = 0; i < 4; i++) {
                this->swork[9 + i] = 30;
                this->swork[13 + i] = 0;
                this->swork[17 + i] = 0;
            }

            this->swork[28] = 0;
            this->swork[37] |= 2;
            break;

        case 0:
            break;
    }

    Math_SmoothStepToAngle(&D_i5_801BBEF4[13], D_i5_801BBEF4[12], 0.5f, 1.5f, 0.01f);
    spB8 = 0;

    switch (this->state) {
        case 7:
            Animation_GetFrameData(&D_TI2_70084CC, this->animFrame >> 1, D_i5_801BC978);
            break;
        case 8:
            Animation_GetFrameData(&D_TI2_7003EE8, this->animFrame >> 1, D_i5_801BC978);
            break;
        case 9:
            Animation_GetFrameData(&D_TI_8008FE8, this->animFrame >> 1, D_i5_801BC978);
            break;
        case 10:
            Animation_GetFrameData(&D_TI2_700E244, this->animFrame >> 1, D_i5_801BC978);
            break;
        case 11:
        case 13:
            Animation_GetFrameData(&D_TI_9004288, this->animFrame >> 1, D_i5_801BC978);
            break;
        case 12:
            Animation_GetFrameData(&D_TI_A009990, this->animFrame >> 1, D_i5_801BC978);
            break;
    }

    pad2 = this->swork[34];

    switch (pad2) {
        case 0:
            break;
        case 1:
            Animation_GetFrameData(&D_TI2_70096EC, (s32) this->fwork[48] >> 1, D_i5_801BD218);
            // might need to copy individual values
            for (i = 0; i < 19; i++) {
                D_i5_801BC978[D_i5_801BAA50[i]] = D_i5_801BD218[D_i5_801BAA50[i]];
            }
            break;

        case 2:
            Animation_GetFrameData(&D_TI_A009990, (s32) this->fwork[48] >> 1, D_i5_801BD218);
            for (i = 0; i < 19; i++) {
                D_i5_801BC978[D_i5_801BAA50[i]] = D_i5_801BD218[D_i5_801BAA50[i]];
            }
            break;
    }

    if ((this->state >= 7) && (this->state <= 12) && ((this->fwork[9] > 0.0f) || (this->fwork[6] > 0.0f))) {
        if (this->state == 12) {
            if ((this->fwork[9] > 0.0f) && (this->fwork[6] > 0.0f)) {
                Math_SmoothStepToF(&this->obj.pos.x, gPlayer[0].pos.x, 0.1f, 10.0f, 0.01f);
            } else {
                Math_SmoothStepToF(&this->obj.pos.x, gPlayer[0].pos.x, 0.1f, 4.0f, 0.01f);
            }
        } else {
            Math_SmoothStepToF(&this->obj.pos.x, gPlayer[0].pos.x, 0.1f, 3.0f, 0.01f);
        }
    }

    switch (this->state) {
        case 5:
            if (this->timer_050 == 0) {
                D_i5_801BBEF0[0] = 0;
                D_i5_801BBEF0[1] = 25;
                D_i5_801BBEF4[0] = 0.25f;

                this->obj.pos.x = gPlayer[0].pos.x;
                this->obj.pos.z = gPlayer[0].trueZpos - 1070.0f;
                this->vel.z = 0.0f;

                Animation_GetFrameData(&D_TI_900FC4C, 0, D_i5_801BCDC8);

                D_i5_801BBEF4[8] = 48.0f;
                D_i5_801BBEF4[9] = 48.0f;

                this->fwork[35] = 1.0f;

                D_i5_801BBEF0[13] = 1;
                D_i5_801BBEF4[32] = 10.0f;
                D_i5_801BBEF4[33] = 10.0f;

                this->swork[1] = 6;

                D_i5_801BBEF4[11] = D_i5_801B7738[this->swork[1]];

                this->swork[31] = 0;
                this->swork[30]++;

                for (i = 0; i < ARRAY_COUNTU(D_i5_801BBF00); i++) {
                    D_i5_801BBF00[i].unk_26 = 1;
                    D_i5_801BBF00[i].unk_24 = -1;
                }
            }
            break;

        case 6:
            this->fwork[47] = (f32) this->animFrame / (f32) (Animation_GetFrameCount(&D_TI_900FC4C) * 2);

            if ((this->animFrame == 0) || (this->animFrame == 68) || (this->animFrame == 96) ||
                (this->animFrame == 149)) {
                AUDIO_PLAY_SFX(NA_SE_EN_APPEAR_SAND, this->sfxSource, 4);
            }

            temp_f = gPlayer[0].trueZpos - this->obj.pos.z - 530.0f;
            if (temp_f < 0.0f) {
                this->obj.pos.z += temp_f;
            }

            if (this->animFrame == 26) {
                gPlayer[0].unk_19C = -1;
                gPlayer[0].unk_000 = 0.0f;
            }

            for (i = 0; i < ARRAY_COUNTU(D_i5_801BBF00); i++) {
                if ((D_i5_801BBF00[i].unk_24 < 0) && ((this->obj.pos.y + D_i5_801BBF00[i].unk_00.pos.y) > 0.0f)) {
                    D_i5_801BBF00[i].unk_24 = 30;
                }
                if (D_i5_801BBF00[i].unk_24 > 0) {
                    D_i5_801BBF00[i].unk_24--;
                    if (!(D_i5_801BBF00[i].unk_24 & 1)) { // prefer == 0
                        Effect_Effect359_Spawn(this->obj.pos.x + D_i5_801BBF00[i].unk_00.pos.x,
                                               this->obj.pos.y + D_i5_801BBF00[i].unk_00.pos.y,
                                               this->obj.pos.z + D_i5_801BBF00[i].unk_00.pos.z, 7.0f, 160, 16, 0);
                    }
                }
                if (D_i5_801BBF00[i].unk_24 != 0) {
                    D_i5_801BBF00[i].unk_26 = 1;
                }
            }

            Animation_GetFrameData(&D_TI_900FC4C, this->animFrame >> 1, D_i5_801BC978);
            Math_SmoothStepToF(&this->fwork[0], 0.5f, 1.0f, 0.02f, 0.0f);
            Math_SmoothStepToVec3fArray(D_i5_801BC978, D_i5_801BCDC8, 1, 92, this->fwork[0], 360.0f, 0.01f);
            this->animFrame++;

            if (this->animFrame >= (Animation_GetFrameCount(&D_TI_900FC4C) * 2)) {
                AUDIO_PLAY_SFX(NA_SE_EN_TIBOSS_AT_CRY, this->sfxSource, 4);
                gPlayer[0].unk_19C = 0;
                this->animFrame = 0;
                this->fwork[48] = 0;
                Animation_GetFrameData(&D_TI2_70084CC, 0, D_i5_801BC978);
                this->swork[31] = 0;
                this->swork[30]++;
                this->vel.z = -15.0f;
                spB8 = 1;
            }
            break;

        case 7:
            if (this->swork[9] > 0) {
                for (i = 0; i < 9; i++) {
                    if (this->animFrame == D_i5_801B8138[i]) {
                        sp90.x = this->obj.pos.x + this->fwork[23];
                        sp90.y = this->obj.pos.y + this->fwork[24];
                        sp90.z = this->obj.pos.z + this->fwork[25];
                        sp84.x = -this->fwork[28];
                        sp84.y = this->fwork[27] + 90.0f;
                        sp84.z = 0.0f;
                        func_effect_8007EE68(OBJ_EFFECT_ENEMY_LASER_1, &sp90, &sp84, &D_tank_800C9F2C, &D_i5_801B8D48,
                                             1.0f);
                    }
                }
            }

            if ((this->swork[10] > 0) && ((D_i5_801BBEF0[41] == 2) || (D_i5_801BBEF0[8] != 0))) {
                for (i = 0; i < 9; i++) {
                    if (this->animFrame == D_i5_801B814C[i]) {
                        sp90.x = this->obj.pos.x + this->fwork[29];
                        sp90.y = this->obj.pos.y + this->fwork[30];
                        sp90.z = this->obj.pos.z + this->fwork[31];
                        sp84.x = -this->fwork[34];
                        sp84.y = this->fwork[33] + 90.0f;
                        sp84.z = 0.0f;
                        func_effect_8007EE68(OBJ_EFFECT_ENEMY_LASER_1, &sp90, &sp84, &D_tank_800C9F2C, &D_i5_801B8D48,
                                             1.0f);
                    }
                }
            }

            if (D_i5_801BBEF0[41] == 1) {
                D_i5_801BBEF0[41] = 2;
            }

            if (D_i5_801BBEF0[2] == 0) {
                D_i5_801BBEF4[7] = 48;
                D_i5_801BBEF0[2] = 90;
                D_i5_801BBEF0[3] = 2;
            }

            if (D_i5_801BBEF0[8] != 0) {
                if (D_i5_801BBEF0[4] == 0) {
                    D_i5_801BBEF4[9] = 48;
                    D_i5_801BBEF0[4] = 90;
                    D_i5_801BBEF0[5] = 2;
                }
            } else {
                D_i5_801BBEF4[8] = 48;
                D_i5_801BBEF4[9] = 48;
            }

            Math_SmoothStepToF(&this->fwork[0], 0.5f, 1.0f, 0.02f, 0.0f);
            Math_SmoothStepToVec3fArray(D_i5_801BC978, D_i5_801BCDC8, 1, 92, this->fwork[0], 360.0f, 0.01f);

            this->animFrame++;
            if (this->animFrame >= (Animation_GetFrameCount(&D_TI2_70084CC) * 2)) {
                this->fwork[36] = 0.0f;
                this->fwork[37] = 0.0f;
                spB8 = 1;
            }
            break;

        case 8:
            if ((this->animFrame == 0) && (this->swork[11] <= 0)) {
                this->animFrame = 62;
            }
            if ((this->animFrame == 62) && (this->swork[12] <= 0)) {
                this->animFrame = (Animation_GetFrameCount(&D_TI2_7003EE8) * 2) - 1;
                D_i5_801BBEF4[12] = 0.0f;
            }
            if (this->animFrame == 98) {
                D_i5_801BBEF4[12] = 0.0f;
            }
            if ((this->animFrame == 22) || (this->animFrame == 80)) {
                AUDIO_PLAY_SFX(NA_SE_EN_TIBOSS_AT_CRY, this->sfxSource, 4);
            }
            if (((this->animFrame >= 0) && (this->animFrame < 18)) ||
                ((this->animFrame >= 62) && (this->animFrame < 80))) {
                D_i5_801BBEF4[12] =
                    Math_Atan2F(gPlayer[0].pos.x - this->obj.pos.x, gPlayer[0].pos.z - this->obj.pos.z) * M_RTOD;
                D_i5_801BBEF4[11] = __cosf(D_i5_801BBEF4[12] * M_DTOR) * 580.0f;
            }
            if ((this->animFrame >= 37) && (this->animFrame < 41) && (this->swork[11] > 0)) {
                spD4.x = this->obj.pos.x + D_i5_801BBEF4[68];
                spD4.y = 0.0f;
                spD4.z = this->obj.pos.z + D_i5_801BBEF4[70];
                if (this->animFrame & 1) {
                    Effect_Effect359_Spawn(spD4.x, 0.0f, spD4.z, 10.0f, 255, 8, 0);
                }
                if (this->animFrame == 38) {
                    Effect_SpawnTimedSfxAtPos(&spD4, NA_SE_EN_BOSS_ATTACK);
                    this->swork[39] = 5;
                    gCameraShake = 20;
                }
            }
            if ((this->animFrame >= 97) && (this->animFrame < 101) && (this->swork[12] > 0)) {
                spD4.x = this->obj.pos.x + D_i5_801BBEF4[71];
                spD4.y = 0.0f;
                spD4.z = this->obj.pos.z + D_i5_801BBEF4[73];
                if (this->animFrame & 1) {
                    Effect_Effect359_Spawn(spD4.x, 0.0f, spD4.z, 10.0f, 255, 8, 0);
                }
                if (this->animFrame == 98) {
                    Effect_SpawnTimedSfxAtPos(&spD4, NA_SE_EN_BOSS_ATTACK);
                    this->swork[39] = 5;
                    gCameraShake = 20;
                }
            }

            Math_SmoothStepToF(&this->fwork[0], 0.5f, 1.0f, 0.02f, 0.0f);
            Math_SmoothStepToVec3fArray(D_i5_801BC978, D_i5_801BCDC8, 1, 92, this->fwork[0], 360.0f, 0.01f);

            this->animFrame++;
            if (this->animFrame >= (Animation_GetFrameCount(&D_TI2_7003EE8) * 2)) {
                spB8 = 1;
            }
            break;

        case 9:
            Math_SmoothStepToF(&this->fwork[0], 0.5f, 1.0f, 0.02f, 0.0f);
            Math_SmoothStepToVec3fArray(D_i5_801BC978, D_i5_801BCDC8, 1, 92, this->fwork[0], 360.0f, 0.01f);

            this->animFrame++;
            if (this->animFrame >= (Animation_GetFrameCount(&D_TI_8008FE8) * 2)) {
                spB8 = 1;
            }
            break;

        case 10:
            Math_SmoothStepToF(&this->fwork[0], 0.5f, 1.0f, 0.02f, 0.0f);
            Math_SmoothStepToVec3fArray(D_i5_801BC978, D_i5_801BCDC8, 1, 92, this->fwork[0], 360.0f, 0.01f);

            this->animFrame++;
            if (this->animFrame >= (Animation_GetFrameCount(&D_TI2_700E244) * 2)) {
                spB8 = 1;
            }
            break;

        case 11:
            if (D_i5_801BBEF0[26] > 0) {
                D_i5_801BBEF0[26]--;
            }

            if (D_i5_801BBEF0[16] > 0) {
                D_i5_801BBEF0[16]--;
            }

            if (D_i5_801BBEF0[17] > 0) {
                D_i5_801BBEF0[17]--;
            }
            if (this->animFrame == 0) {
                AUDIO_PLAY_SFX(NA_SE_EN_BOSS_CHARGE, this->sfxSource, 4);
            }
            if (this->animFrame == 15) {
                D_i5_801BBEF0[16] = 25;
            }
            if ((this->animFrame >= 44) && (this->animFrame < 51)) {
                D_i5_801BBEF0[7]++;
            }
            if (this->animFrame == 43) {
                D_i5_801BBEF0[7] = 0;
                D_i5_801BBEF4[11] = 1300.0f;
            }
            if (this->animFrame == 51) {
                D_i5_801BBEF0[7] = 0;
            }

            // pad = this->animFrame == 45;
            if (this->animFrame == 45) {
                AUDIO_PLAY_SFX(NA_SE_EN_BOSS_BEAM0, this->sfxSource, 4);
                this->swork[32] = 0;
                this->fwork[42] = 0.0f;
                this->fwork[41] = 40.0f;
                D_i5_801BBEF0[26] = 3;
                this->swork[25] = 1;
                D_i5_801BBEF0[17] = 3;
                D_i5_801BBEF0[13] = 1;
                D_i5_801BBEF4[32] = 1.0f;
                D_i5_801BBEF4[33] = 1.0f;
                for (i = 0; i < 4; i++) {
                    if (D_i5_801BBEF0[9 + i] == 0) {
                        for (j = 0; j < ARRAY_COUNT(gTexturedLines); j++) {
                            if (gTexturedLines[j].mode == 0) {
                                gTexturedLines[j].mode = 1;
                                D_i5_801BBEF0[9 + i] = j + 1;
                                break;
                            }
                        }
                    }
                }
            }
            if (this->animFrame == 130) {
                for (i = 0; i < 4; i++) {
                    gTexturedLines[D_i5_801BBEF0[9 + i] - 1].mode = 0;
                }

                this->swork[32] = 0;
                Audio_KillSfxBySourceAndId(this->sfxSource, NA_SE_EN_BOSS_BEAM0);
                this->swork[25] = 0;
                this->fwork[41] = 0.0f;
                this->fwork[42] = 0.0f;
            }
            if (this->animFrame == 53) {
                this->swork[32] = 1;
            }
            if (this->animFrame == 120) {
                this->swork[32] = 0;
            }

            if (D_i5_801BBEF0[26] != 0) {
                gFillScreenRed = 255;
                gFillScreenGreen = 255;
                gFillScreenBlue = 255;
                gFillScreenAlpha = (D_i5_801BBEF0[26] * 255.0f) / 3.0f;
            }

            if ((this->animFrame >= 54) && (this->animFrame < 120)) {
                this->fwork[46] += 0.04f;
                if (this->fwork[46] > 1.0f) {
                    this->fwork[46] = 1.0f;
                }
            }
            if (this->animFrame == 51) {
                D_i5_801BBEF4[32] = 360.0f;
                D_i5_801BBEF4[33] = 10.0f;
                this->fwork[46] = 0.3f;
            }

            if (this->fwork[46] == 1.0f) {
                D_i5_801BBEF4[33] = 0.01f;
                D_i5_801BBEF4[32] = 0.5f;
            }

            if (this->animFrame == 52) {
                D_i5_801BBEF4[32] = 0.0f;
            }
            if (this->animFrame == 120) {
                this->fwork[46] = 0.0f;
            }
            if ((this->animFrame >= 51) && (this->animFrame < 120)) {
                this->fwork[35] = 1.0f;
            } else {
                this->fwork[35] = 0.0f;
            }

            if ((this->animFrame >= 45) && (this->animFrame < 47)) {
                this->fwork[41] += 20.0f;
                this->fwork[42] += 1050.0f;
            }
            if (this->animFrame >= 47) {
                if (this->fwork[41] > 40.0f) {
                    this->fwork[41] -= 20.0f;
                }
            }
            if ((this->animFrame >= 126) && (this->animFrame < 129)) {
                this->fwork[41] *= 0.5f;
            }
            if (this->animFrame >= 128) {
                this->fwork[42] *= 0.3f;
            }
            if (this->animFrame >= 129) {
                this->fwork[42] *= 0.5f;
                this->fwork[41] *= 0.5f;
            }

            if (this->swork[24] != 0) {
                Math_SmoothStepToF(&this->fwork[45], 0.0f, 0.8f, 2.5f, 0.01f);
                if (this->fwork[43] == 0.0f) {
                    this->fwork[43] = 1.0f;
                }
                Math_SmoothStepToF(&this->fwork[43], 0.0f, 1.0f, 0.1f, 0.001f);
                if (this->animFrame == 30) {
                    this->fwork[41] = 0.0f;
                    this->fwork[42] = 0.0f;
                    this->swork[24] = 0;
                    Audio_KillSfxBySourceAndId(this->sfxSource, NA_SE_EN_BOSS_CHARGE);
                }
            }

            Math_SmoothStepToF(&this->fwork[0], 0.5f, 1.0f, 0.02f, 0.0f);
            Math_SmoothStepToVec3fArray(D_i5_801BC978, D_i5_801BCDC8, 1, 92, this->fwork[0], 360.0f, 0.01f);

            this->animFrame++;
            if (this->animFrame >= (Animation_GetFrameCount(&D_TI_9004288) * 2)) {
                this->swork[24] = 0;
                this->fwork[43] = 0.0f;
                this->swork[25] = 0;
                spB8 = 1;
            }
            break;

        case 12:
            this->swork[33] = 1;

            if ((this->animFrame >= 38) && (this->animFrame < 141)) {
                this->fwork[1] = ((this->animFrame - 38) * 360.0f) / 102.0f;
            }

            Math_SmoothStepToAngle(&this->fwork[49], this->fwork[1], 0.5f, 180.0f, 0.0f);
            Math_SmoothStepToF(&this->fwork[0], 0.5f, 1.0f, 0.02f, 0.0f);
            Math_SmoothStepToVec3fArray(D_i5_801BC978, D_i5_801BCDC8, 1, 92, this->fwork[0], 360.0f, 0.01f);

            this->animFrame++;
            if (this->animFrame >= (Animation_GetFrameCount(&D_TI_A009990) * 2)) {
                this->swork[33] = 0;
                this->fwork[48] = 0;
                spB8 = 1;
            }
            break;

        case 13:
            if (this->swork[34] == 2) {
                if ((this->fwork[48] >= 38.0f) && (this->fwork[48] <= 140.0f)) {
                    this->fwork[1] = ((this->fwork[48] - 38.0f) * 360.0f) / 102.0f;
                }
                Math_SmoothStepToAngle(&this->fwork[49], this->fwork[1], 0.5f, 180.0f, 0.0f);
            }

            Math_SmoothStepToF(&this->fwork[0], 0.5f, 1.0f, 0.02f, 0.01f);
            Math_SmoothStepToVec3fArray(D_i5_801BC978, D_i5_801BCDC8, 1, 92, this->fwork[0], 360.0f, 0.01f);

            if (this->swork[38] & 1) {
                this->animFrame++;
            }

            D_i5_801BBEF0[6] = 2;

            if (this->animFrame == 30) {
                Audio_KillSfxBySourceAndId(this->sfxSource, NA_SE_EN_HEARTBEAT);
                D_i5_801BBEF0[7] = 0;
                this->obj.status = OBJ_DYING;
                D_i5_801BBEF4[12] = 0.0f;
                this->fwork[35] = 0.0f;
                this->work_044 = 0;
                this->timer_050 = 280;
                D_i5_801BBEF0[16] = 0;
                D_i5_801BBEF0[17] = 0;
                this->swork[23] = 0;
                D_i5_801BBEF0[6] = 80;
                D_i5_801BBEF0[7] = 0;
                for (i = 0; i < ARRAY_COUNTU(D_i5_801BBF00); i++) {
                    if (!(D_i5_801BBF00[i].unk_26 & 4)) {
                        D_i5_801BBF00[i].unk_26 = 3;
                    }
                }
            }
            break;
    }

    pad2 = this->swork[34];
    switch (pad2) {
        case 0:
            break;

        case 1:
            this->fwork[48] += this->fwork[2];
            if (Animation_GetFrameCount(&D_TI2_70096EC) * 2 <= this->fwork[48]) {
                this->fwork[48] -= Animation_GetFrameCount(&D_TI2_70096EC) * 2;
            } else if (this->fwork[48] < 0.0f) {
                this->fwork[48] = this->fwork[48] + (Animation_GetFrameCount(&D_TI2_70096EC) * 2 - 1.0f);
            }
            break;

        case 2:
            this->fwork[48] += 1.0f;
            if (Animation_GetFrameCount(&D_TI_A009990) * 2 <= this->fwork[48]) {
                if (this->state == 13) {
                    this->fwork[0] = 0.0f;
                    this->swork[34] = 1;
                    this->fwork[48] = 0;
                } else {
                    this->fwork[48] = 0;
                }
            }
            break;
    }

    if (spB8 == 1) {
        this->animFrame = 0;
        this->fwork[0] = 0.0f;

        this->swork[3]--;
        if (this->swork[3] <= 0) {
            this->swork[1] = 7 + RAND_INT(6.0f);
            Titania_80193B30(this);
        }

        this->swork[4]++;

        if (this->swork[37] & 0x18) {
            D_i5_801BBEF0[44]++;
        }

        D_i5_801BBEF0[42] = 0;

        pad2 = this->swork[1];
        switch (pad2) {
            case 7:
                if (this->swork[37] & 2) {
                    pad = 0;
                    for (i = 0; i < 4; i++) {
                        if (this->swork[9 + i] <= 0) {
                            pad++;
                        }
                    }

                    if ((pad != 4) && gTeamShields[TEAM_ID_PEPPY] > 0) {
                        Radio_PlayMessage(gMsg_ID_4095, RCID_PEPPY);
                    }
                    this->swork[37] &= ~2;
                }
                break;

            case 9:
                if (this->swork[37] & 1) {
                    if ((this->swork[29] != 0) && gTeamShields[TEAM_ID_FALCO] > 0) {
                        Radio_PlayMessage(gMsg_ID_4099, RCID_FALCO);
                    }
                    this->swork[37] &= ~1;
                }
                break;
        }
    }

    while (this->fwork[49] >= 360.0f) {
        this->fwork[49] -= 360.0f;
    }

    while (this->fwork[49] < 0.0f) {
        this->fwork[49] += 360.0f;
    }

    for (i = 0; i < 4; i++) {
        if (this->swork[9 + i] == 0) {
            var_v1 = this->swork[17 + i];
            if (this->swork[13 + i] == D_i5_801BAB0C[i][var_v1]) {
                do {
                    D_i5_801BBF00[D_i5_801BAABC[i][var_v1]].unk_26 = 3;
                    this->swork[17 + i]++;
                    var_v1++;
                } while (D_i5_801BAB0C[i][var_v1] == 0);
                if (D_i5_801BAB0C[i][var_v1] == -1) {
                    this->swork[9 + i] = -1;
                } else {
                    this->swork[13 + i] = 0;
                }
            } else {
                this->swork[13 + i]++;
            }
        }
    }

    if ((this->state != 13) && (this->swork[21] <= 0)) {
        this->swork[1] = 13;
        this->animFrame = 0;
        if (this->swork[25] != 0) {
            Audio_KillSfxBySourceAndId(this->sfxSource, NA_SE_EN_BOSS_BEAM0);
            this->swork[25] = 0;
        }
        if (this->swork[24] != 0) {
            Audio_KillSfxBySourceAndId(this->sfxSource, NA_SE_EN_BOSS_CHARGE);
            this->swork[24] = 0;
        }
    }
    if (this->state >= 7) {
        if ((this->fwork[15] <= 0.0f) && (this->fwork[9] > 0.0f)) {
            effect = Effect_Load(OBJ_EFFECT_394);
            if (effect != NULL) {
                Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
                Matrix_MultVec3f(gCalcMatrix, (Vec3f*) &this->fwork[8], &spC8);
                effect->obj.status = OBJ_ACTIVE;
                effect->unk_78 = effect->unk_7A = 0;
                effect->obj.pos.x = this->obj.pos.x + spC8.x;
                effect->obj.pos.y = this->obj.pos.y + 3.0f;
                effect->obj.pos.z = this->obj.pos.z + spC8.z;
                effect->obj.rot.y = this->fwork[49] + -44.0f;
                effect->unk_44 = 53;
                effect->info.cullDistance = 400.0f;
                effect->info.unk_14 = -1;
                effect->unk_74 = D_TI2_7009A80;
            }
        }

        if ((this->fwork[12] <= 0.0f) && (this->fwork[6] > 0.0f)) {
            effect = Effect_Load(OBJ_EFFECT_394);
            if (effect != NULL) {
                Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
                Matrix_MultVec3f(gCalcMatrix, (Vec3f*) &this->fwork[5], &spC8);
                effect->obj.status = OBJ_ACTIVE;
                effect->unk_78 = effect->unk_7A = 0;
                effect->obj.pos.x = this->obj.pos.x + spC8.x;
                effect->obj.pos.y = this->obj.pos.y + 3.0f;
                effect->obj.pos.z = this->obj.pos.z + spC8.z;
                effect->obj.rot.y = this->fwork[49] + 44.0f;
                effect->unk_44 = 53;
                effect->info.cullDistance = 400.0f;
                effect->info.unk_14 = -1;
                effect->unk_74 = D_TI2_7009A80;
            }
        }
    }

    if ((this->state == 6) && ((this->animFrame == 134) || (this->animFrame == 188))) {
        AUDIO_PLAY_SFX(NA_SE_EN_HEAVY_WALK2, this->sfxSource, 4);
        this->swork[39] = 4;
        gCameraShake = 7;
    }
    if (this->state >= 7) {
        if (((this->fwork[15] > 0.0f) && (this->fwork[9] <= 0.0f)) ||
            ((this->fwork[12] > 0.0f) && (this->fwork[6] <= 0.0f))) {
            AUDIO_PLAY_SFX(NA_SE_EN_HEAVY_WALK2, this->sfxSource, 4);
            if (this->state == 12) {
                this->swork[39] = 4;
                gCameraShake = 20;
            } else {
                this->swork[39] = 2;
                gCameraShake = 5;
            }
        }
        this->fwork[12] = this->fwork[6];
        this->fwork[15] = this->fwork[9];
    }
    if ((this->state >= 7) && (D_i5_801B7738[this->state] > 0.0f)) {
        // Can use temp here
        temp_f = Math_SmoothStepToF(&this->obj.pos.z, gPlayer[0].pos.z - D_i5_801BBEF4[11], 0.1f, 14.0f, 0.001f);
        this->fwork[2] = (((-temp_f / 14.0f) * 1.2f) + 1.0f) * 2.0f;
        this->vel.z = -12.0f;
    }
    this->dmgType = DMG_NONE;
}
#else
#pragma GLOBAL_ASM("asm/us/rev1/nonmatchings/overlays/ovl_i5/fox_ti/Titania_80193DF0.s")
void Titania_80193DF0(Boss*);
#endif

s16 D_i5_801B8D54[4] = { 30, 35, 60, 70 };

void Titania_TiGoras_Update(Boss* boss) {
    Vec3f sp3C;

    boss->swork[38]++;

    if ((boss->dmgType != DMG_NONE) &&
        (((boss->state >= 0) && (boss->state <= 1)) || ((boss->state >= 4) && (boss->state <= 6)))) {
        AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, boss->sfxSource, 4);
        boss->dmgType = DMG_NONE;
    }
    if ((gPlayer[0].grounded != 0) && (boss->swork[39] > 0)) {
        gControllerRumbleFlags[0] = 1;
        boss->swork[39]--;
    }

    if (boss->swork[28] == 2) {
        if (gTeamShields[TEAM_ID_PEPPY] > 0) {
            Radio_PlayMessage(gMsg_ID_4091, RCID_PEPPY);
        }
        D_i5_801BBEF0[42] = 1;
    }

    if (D_i5_801BBEF0[45] >= 2) {
        D_i5_801BBEF0[45]--;
    }

    if (boss->swork[30] == 4) {
        if ((boss->swork[37] & 8) && (D_i5_801BBEF0[44] == 0)) {
            Radio_PlayMessage(gMsg_ID_4110, RCID_SLIPPY);
            boss->swork[37] &= ~8;
        }
        if ((boss->swork[37] & 0x10) && (D_i5_801BBEF0[44] >= 2) && (gRadioState == 0)) {
            Radio_PlayMessage(gMsg_ID_4092, RCID_SLIPPY);
            boss->swork[37] &= ~0x10;
            D_i5_801BBEF0[45] = 101;
        }

        if (D_i5_801BBEF0[45] == 1) {
            gBossHealthBar = ((boss->swork[21] * 255.0f) / 100.0f);
            gShowBossHealth = true;
            D_i5_801BBEF0[45] = 0;
        }
    }

    if ((boss->state >= 3) && (boss->state <= 13)) {
        gBossFrameCount++;
    }

    switch (boss->state) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            Titania_80192118(boss);
            break;
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
            Titania_80193DF0(boss);
            break;
    }

    switch (boss->swork[30]) {
        case 0:
            switch (boss->swork[31]) {
                case 1:
                    Radio_PlayMessage(gMsg_ID_20266, RCID_FOX);
                    break;
                case 80:
                    gTeamShields[TEAM_ID_SLIPPY] = 1;
                    Radio_PlayMessage(gMsg_ID_4112, RCID_SLIPPY);
                    gTeamShields[TEAM_ID_SLIPPY] = -2;
                    break;
                case 240:
                    gTeamShields[TEAM_ID_SLIPPY] = 1;
                    Radio_PlayMessage(gMsg_ID_4093, RCID_SLIPPY);
                    gTeamShields[TEAM_ID_SLIPPY] = -2;
                    break;
            }
            break;

        case 1:
            if (boss->swork[31] == 1) {
                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 90);
                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 90);
            }
            break;

        case 2:
            if (boss->swork[31] == 11) {
                gTeamShields[TEAM_ID_SLIPPY] = 1;
                Radio_PlayMessage(gMsg_ID_4111, RCID_SLIPPY);
                gTeamShields[TEAM_ID_SLIPPY] = -2;
            }
            break;

        case 3:
            switch (boss->swork[31]) {
                case 1:
                    break;
                case 50:
                    if (gTeamShields[TEAM_ID_FALCO] > 0) {
                        Radio_PlayMessage(gMsg_ID_4094, RCID_FALCO);
                    }
                default:
                    break;
            }
            break;

        case 4:
            if (boss->swork[35] == 0) {
                if (D_i5_801BBEF0[42] == 0) {
                    switch (boss->swork[4]) {
                        case 1:
                            if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                                Radio_PlayMessage(gMsg_ID_4095, RCID_PEPPY);
                            }
                            D_i5_801BBEF0[42] = 1;
                            break;

                        case 3:
                            if ((D_i5_801BBEF0[8] == 0) && (gTeamShields[TEAM_ID_FALCO] > 0)) {
                                Radio_PlayMessage(gMsg_ID_4097, RCID_FALCO);
                            }
                            D_i5_801BBEF0[42] = 1;
                            break;

                        default:
                            break;
                    }

                    if (boss->swork[4] >= 4 && !(D_i5_801BBEF0[46] & 1)) {
                        if ((gTeamShields[TEAM_ID_FALCO] > 0) && (D_i5_801BBEF0[8] == 0) && (gRadioState == 0) &&
                            (boss->swork[10] >= 2)) {
                            gTeamShields[TEAM_ID_SLIPPY] = 1;
                            Radio_PlayMessage(gMsg_ID_4098, RCID_SLIPPY);
                            gTeamShields[TEAM_ID_SLIPPY] = -2;
                            D_i5_801BBEF0[46] |= 1;
                        }
                        D_i5_801BBEF0[42] = 1;
                    }
                }
            }

            if (boss->swork[37] & 4) {
                D_i5_801BBEF0[43]++;
                switch (D_i5_801BBEF0[43]) {
                    case 1:
                        gTeamShields[TEAM_ID_SLIPPY] = 1;
                        Radio_PlayMessage(gMsg_ID_20190, RCID_SLIPPY);
                        gTeamShields[TEAM_ID_SLIPPY] = -2;
                        break;
                    case 80:
                        if (gTeamShields[TEAM_ID_FALCO] > 0) {
                            Radio_PlayMessage(gMsg_ID_4096, RCID_FALCO);
                        }
                        boss->swork[37] &= ~4;
                        break;
                    default:
                        break;
                }
            }
            break;
    }

    if ((boss->state != 5) && ((boss->state != 4) || (boss->swork[31] <= 100)) && (D_i5_801BBEF0[8] == 0)) {
        Math_SmoothStepToF(&D_i5_801BBEF4[74], D_i5_801BBEF4[75], 0.5f, 0.04f, 0.01f);
        if (D_i5_801BBEF4[74] == D_i5_801BBEF4[74]) {
            if ((boss->swork[38] % 2) != 0) {
                D_i5_801BBEF4[75] = 0.7f;
                D_i5_801BBEF4[74] = D_i5_801BBEF4[75];
            } else {
                D_i5_801BBEF4[75] = 0.6f;
                D_i5_801BBEF4[74] = D_i5_801BBEF4[75];
            }
        }

        if ((D_i5_801BBEF0[49] >= 25) && (((D_i5_801BBEF0[49] - 25) % 2) == 0)) {
            D_i5_801BBEF4[74] = RAND_FLOAT(0.4f) + 0.9f;
            D_i5_801BBEF4[75] = 0.6f;
        }
        if (D_i5_801BBEF0[49] == 0) {
            sp3C.x = boss->fwork[29] + boss->obj.pos.x;
            sp3C.y = boss->fwork[30] + boss->obj.pos.y;
            sp3C.z = boss->fwork[31] + boss->obj.pos.z;
            Effect_SpawnTimedSfxAtPos(&sp3C, NA_SE_ARWING_DASH);
            D_i5_801BBEF0[49] = D_i5_801B8D54[RAND_INT(4.0f)];
            D_i5_801BBEF4[74] = RAND_FLOAT(0.4f) + 0.9f;
            D_i5_801BBEF4[75] = 0.6f;
        }
        if (D_i5_801BBEF0[49] > 0) {
            D_i5_801BBEF0[49]--;
        }
    }
    boss->swork[31]++;
}

f32 D_i5_801B8D5C[2][25] = {
    0.0f,  0.03f,  0.06f, 0.12f, 0.18f, 0.25f, 0.425f, 0.6f, 0.775f, 0.95f, 1.125f, 1.3f, 1.475f,
    1.65f, 1.825f, 2.0f,  1.8f,  1.6f,  1.4f,  1.2f,   1.0f, 0.8f,   0.6f,  0.4f,   0.2f, 0.0f,
    0.8f,  1.6f,   2.4f,  3.2f,  4.0f,  3.4f,  3.2f,   3.0f, 2.8f,   2.4f,  2.2f,   2.0f, 1.8f,
    1.6f,  1.4f,   1.2f,  1.0f,  0.8f,  0.6f,  0.4f,   0.2f, 0.0f,   0.0f,  0.0f,
};

f32 D_i5_801B8E24[4][2] = {
    { -1.0f, 1.0f },
    { 1.0f, 1.0f },
    { -1.0f, -1.0f },
    { 1.0f, -1.0f },
};

void Titania_TiGoras_Draw(TiGoras* boss) {
    TexturedLine* temp_v0_6;
    f32 sp120;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fs2;
    f32 temp_fv0;
    s32 pad;
    f32 stack;
    s32 i;
    s32 j;
    Vec3f spF4;
    Vec3f spE8;
    s32 temp_v1_28;
    f32 half = 0.5f;
    s32 temp;

    Matrix_Push(&gGfxMatrix);
    RCP_SetupDL(&gMasterDisp, SETUPDL_30);
    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);

    switch (boss->state) {
        case 0:
            break;

        case 1:
        case 2:
        case 3:
        case 4:
            Matrix_Push(&gGfxMatrix);
            D_i5_801BBEF0[25] = 0;
            Animation_DrawSkeleton(0, D_TI_A000EDC, &D_i5_801BCDC8[16], Titania_8018FC70, Titania_8019002C, boss,
                                   &gIdentityMatrix);
            Matrix_Pop(&gGfxMatrix);
            aTiGorasHitbox[0] = 22.0f;
            Matrix_Push(&gGfxMatrix);
            D_i5_801BBEF0[25] = 1;
            Animation_DrawSkeleton(0, D_TI_A000568, &D_i5_801BCDC8[0], Titania_801903A0, Titania_8019081C, boss,
                                   &gIdentityMatrix);
            Matrix_Pop(&gGfxMatrix);
            Matrix_Push(&gGfxMatrix);
            D_i5_801BBEF0[25] = 2;
            Animation_DrawSkeleton(0, D_TI_A000568, &D_i5_801BCDC8[8], Titania_801903A0, Titania_8019081C, boss,
                                   &gIdentityMatrix);
            Matrix_Pop(&gGfxMatrix);
            break;

        case 6:
            Animation_DrawSkeleton(0, D_TI_A001A70, D_i5_801BCDC8, Titania_80190A08, Titania_80191AE8, boss,
                                   &gIdentityMatrix);
            break;

        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
            Animation_DrawSkeleton(0, D_TI_A001A70, D_i5_801BCDC8, Titania_80190A08, Titania_80191AE8, boss,
                                   &gIdentityMatrix);
            break;
    }

    Matrix_Pop(&gGfxMatrix);

    if (boss->obj.status != OBJ_DYING) {
        switch (boss->state) {
            case 6:
                Matrix_Push(&gGfxMatrix);

                RCP_SetupDL(&gMasterDisp, SETUPDL_69);

                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 0, 0, 0, 255);
                gDPSetEnvColor(gMasterDisp++, 0, 0, 0, 0);

                Matrix_RotateX(gGfxMatrix, -M_PI / 2, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, boss->fwork[47] * 10.0f, boss->fwork[47] * 10.0f, 1.0f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);

                gSPDisplayList(gMasterDisp++, aOrbDL);

                Matrix_Pop(&gGfxMatrix);
                break;

            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
                Matrix_Push(&gGfxMatrix);

                RCP_SetupDL(&gMasterDisp, SETUPDL_69);

                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 0, 0, 0, 255);
                gDPSetEnvColor(gMasterDisp++, 0, 0, 0, 0);

                Matrix_RotateX(gGfxMatrix, -M_PI / 2, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, 10.0f, 10.0f, 1.0f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);

                gSPDisplayList(gMasterDisp++, aOrbDL);

                Matrix_Pop(&gGfxMatrix);
                break;
        }

        if (boss->state == 11) {
            if (boss->swork[24] != 0) {
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, boss->fwork[17], boss->fwork[18], boss->fwork[19] + 50.0f, MTXF_APPLY);
                RCP_SetupDL_14();

                for (i = 0; i < 3; i++) {
                    sp120 = (boss->fwork[43] + i) / 3.0f;
                    temp_fs2 = boss->fwork[45] * sp120;
                    temp_fv0 = 1.0f - sp120;
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, (s32) (temp_fv0 * 255.0f),
                                    (s32) ((temp_fv0 * 128.0f) + 127.0f), (s32) ((temp_fv0 * 60.0f) + 195.0f),
                                    (s32) ((temp_fv0 * 155.0f) + 100.0f));
                    for (j = 0; j < 360; j += 45) {
                        Matrix_Push(&gGfxMatrix);
                        Matrix_RotateZ(gGfxMatrix, (j + boss->fwork[43] * 360.0f) * M_DTOR, MTXF_APPLY);
                        Matrix_Translate(gGfxMatrix, temp_fs2, 0.0f, 0.0f, MTXF_APPLY);
                        Matrix_SetGfxMtx(&gMasterDisp);
                        gSPDisplayList(gMasterDisp++, D_Gfx_800D94D0);
                        Matrix_Pop(&gGfxMatrix);
                    }
                }
                Matrix_Pop(&gGfxMatrix);
            }
            Matrix_Translate(gGfxMatrix, boss->fwork[17], boss->fwork[18], boss->fwork[19], MTXF_APPLY);

            if (D_i5_801BBEF0[7] != 0) {
                Matrix_Push(&gGfxMatrix);
                sp120 = D_i5_801BBEF0[7] * 16.0f;
                RCP_SetupDL(&gMasterDisp, SETUPDL_64);
                Matrix_RotateX(gGfxMatrix, M_PI / 2, MTXF_APPLY);
                Matrix_Push(&gGfxMatrix);
                Matrix_Scale(gGfxMatrix, sp120, 1.0f, sp120, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 120, 255, 220, D_i5_801BBEF0[7] * 50);
                gSPDisplayList(gMasterDisp++, D_BG_PLANET_20112C0);
                Matrix_Pop(&gGfxMatrix);

                if (D_i5_801BBEF0[7] > 0) {
                    sp120 = (D_i5_801BBEF0[7] - 1) * 24.0f;
                    Matrix_Scale(gGfxMatrix, sp120, 1.0f, sp120, MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 120, 255, 220, D_i5_801BBEF0[7] * 50);
                    gSPDisplayList(gMasterDisp++, D_BG_PLANET_20112C0);
                }
                Matrix_Pop(&gGfxMatrix);
            }

            if (D_i5_801BBEF0[16] > 0) {
                temp = D_i5_801BBEF0[16] - 1;
                Matrix_Push(&gGfxMatrix);

                Matrix_RotateY(gGfxMatrix, (boss->fwork[21] - 90.0f) * M_DTOR, MTXF_APPLY);
                Matrix_RotateX(gGfxMatrix, (boss->fwork[22] - 180.0f) * M_DTOR, MTXF_APPLY);
                Matrix_RotateZ(gGfxMatrix, (boss->fwork[20] + ((boss->animFrame - 15) * 15.6f)) * M_DTOR, MTXF_APPLY);

                Matrix_Scale(gGfxMatrix, D_i5_801B8D5C[0][temp], D_i5_801B8D5C[0][temp], D_i5_801B8D5C[1][temp],
                             MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                RCP_SetupDL(&gMasterDisp, SETUPDL_49);
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 178);
                gDPSetEnvColor(gMasterDisp++, 0, 128, 60, 0);
                gSPDisplayList(gMasterDisp++, D_TI2_7005300);

                Matrix_Pop(&gGfxMatrix);
            }

            if (D_i5_801BBEF0[17] > 0) {
                Matrix_Push(&gGfxMatrix);

                Matrix_RotateY(gGfxMatrix, (boss->fwork[21] - 90.0f) * M_DTOR, MTXF_APPLY);
                Matrix_RotateX(gGfxMatrix, (boss->fwork[22] - 180.0f) * M_DTOR, MTXF_APPLY);
                Matrix_RotateZ(gGfxMatrix, (boss->fwork[20] + ((boss->animFrame - 15) * 15.6f)) * M_DTOR * 3.0f,
                               MTXF_APPLY);

                Matrix_Scale(gGfxMatrix, 4.0f, 4.0f, 4.0f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);

                RCP_SetupDL(&gMasterDisp, SETUPDL_49);

                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, (s32) ((D_i5_801BBEF0[17] * 89.0f) / 3.0f));
                gDPSetEnvColor(gMasterDisp++, 0, 128, 60, 0);
                gSPDisplayList(gMasterDisp++, D_TI2_7005300);

                Matrix_Pop(&gGfxMatrix);
            }

            if (boss->swork[25] != 0) {
                sp120 = boss->fwork[41] / 40.0f;
                temp_fs2 = boss->fwork[42] / 700.0f;
                Matrix_RotateY(gGfxMatrix, (boss->fwork[21] - 90.0f) * M_DTOR, MTXF_APPLY);
                Matrix_RotateX(gGfxMatrix, (boss->fwork[22] - 180.0f) * M_DTOR, MTXF_APPLY);
                Matrix_RotateZ(gGfxMatrix, (boss->fwork[20] - ((s32) (boss->swork[38] % 8U) * 43.0f)) * M_DTOR,
                               MTXF_APPLY);
                Matrix_Push(&gGfxMatrix);
                Matrix_Scale(gGfxMatrix, half * sp120, half * sp120, temp_fs2, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                RCP_SetupDL(&gMasterDisp, SETUPDL_72);
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 178);
                gDPSetEnvColor(gMasterDisp++, 0, 128, 60, 0);
                gSPDisplayList(gMasterDisp++, D_TI_8000D90);

                Matrix_Pop(&gGfxMatrix);
                Matrix_Scale(gGfxMatrix, sp120, sp120, temp_fs2, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);

                gDPPipeSync(gMasterDisp++);
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 64);
                gDPSetEnvColor(gMasterDisp++, 0, 128, 110, 0);
                gSPDisplayList(gMasterDisp++, D_TI_8000D90);

                Matrix_RotateY(gCalcMatrix, (boss->fwork[21] - 90.0f) * M_DTOR, MTXF_NEW);
                Matrix_RotateX(gCalcMatrix, (boss->fwork[22] - 180.0f) * M_DTOR, MTXF_APPLY);
                Matrix_RotateZ(gCalcMatrix, (boss->fwork[20] + boss->fwork[42]) * M_DTOR, MTXF_APPLY);

                temp_fs0 = boss->obj.pos.x + boss->fwork[17];
                temp_fs1 = boss->obj.pos.y + boss->fwork[18];
                temp_fs2 = boss->obj.pos.z + boss->fwork[19];

                for (i = 0; i < 4; i++) {
                    if (D_i5_801BBEF0[9 + i] != 0) {
                        temp_v1_28 = D_i5_801BBEF0[9 + i] - 1;

                        spF4.x = D_i5_801B8E24[i][0] * boss->fwork[41];
                        spF4.y = D_i5_801B8E24[i][1] * boss->fwork[41];
                        spF4.z = boss->fwork[42];

                        Matrix_MultVec3f(gCalcMatrix, &spF4, &spE8);
                        gTexturedLines[temp_v1_28].posAA.x = temp_fs0;
                        gTexturedLines[temp_v1_28].posAA.y = temp_fs1;
                        gTexturedLines[temp_v1_28].posAA.z = temp_fs2;
                        gTexturedLines[temp_v1_28].posBB.x = temp_fs0 + spE8.x;
                        gTexturedLines[temp_v1_28].posBB.y = temp_fs1 + spE8.y;
                        gTexturedLines[temp_v1_28].posBB.z = temp_fs2 + spE8.z;
                        if (boss->swork[32] == 0) {
                            gTexturedLines[temp_v1_28].mode = 0;
                        } else {
                            gTexturedLines[temp_v1_28].mode = 1;
                        }
                        gTexturedLines[temp_v1_28].prim.r = 0;
                        gTexturedLines[temp_v1_28].prim.b = 0;
                        gTexturedLines[temp_v1_28].prim.g = 0;
                        gTexturedLines[temp_v1_28].prim.a = 0;
                        gTexturedLines[temp_v1_28].xyScale = 1;
                    }
                }
            }
        }
        boss->state = boss->swork[1];
    }
}

Vec3f D_i5_801B8E44 = { 3.0f, 0.0f, 0.0f };

void Titania_TiGoras_Dying(TiGoras* this) {
    s32 i;
    Vec3f sp60;
    ActorDebris* debris;

    if (this->work_044 == 0) {
        AUDIO_PLAY_SFX(NA_SE_EN_TIBOSS_DW_CRY, this->sfxSource, 4);

        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 50);
        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 50);

        Effect_Effect383_Spawn(this->obj.pos.x, this->obj.pos.y + 250.0f, this->obj.pos.z, 40.0f);
        Boss_AwardBonus(this);

        gShowBossHealth = false;

        debris = &gActors[0];
        for (i = 0; i < ARRAY_COUNT(gActors); i++, debris++) {
            if ((debris->obj.status == OBJ_ACTIVE) && (debris->obj.id == OBJ_ACTOR_DEBRIS) && (debris->state == 40)) {
                debris->gravity = 0.2f;
            }
        }

        for (i = 0; i < ARRAY_COUNTU(D_i5_801BBF00); i++) {
            if (!(D_i5_801BBF00[i].unk_26 & 4)) {
                debris = Game_SpawnActor(OBJ_ACTOR_DEBRIS);
                if (debris != NULL) {
                    debris->state = 40;

                    debris->work_046 = D_i5_801B7770[i][5];
                    debris->work_048 = D_i5_801B7770[i][1];

                    Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
                    Matrix_MultVec3f(gCalcMatrix, &D_i5_801BBF00[i].unk_00.pos, &sp60);

                    debris->obj.pos.x = this->obj.pos.x + sp60.x;
                    debris->obj.pos.y = this->obj.pos.y + sp60.y;
                    debris->obj.pos.z = this->obj.pos.z + sp60.z;

                    debris->obj.rot.x = D_i5_801BBF00[i].unk_00.rot.x + this->obj.rot.x;
                    debris->obj.rot.y = D_i5_801BBF00[i].unk_00.rot.y + this->obj.rot.y;
                    debris->obj.rot.z = D_i5_801BBF00[i].unk_00.rot.z + this->obj.rot.z;

                    if (i == 51) {
                        debris->vel.x = RAND_FLOAT(10.0f) - 5.0f;
                        debris->vel.y = 30.0f;
                        debris->vel.z = -30.0f;
                        debris->gravity = 0.1f;
                    } else {
                        debris->fwork[0] = ((Rand_ZeroOne() < 0.5f) ? -1 : 1) * (RAND_FLOAT(5.0f) + 5.0f);
                        debris->fwork[1] = ((Rand_ZeroOne() < 0.5f) ? -1 : 1) * (RAND_FLOAT(5.0f) + 5.0f);
                        Matrix_Push(&gCalcMatrix);
                        Matrix_RotateY(gCalcMatrix, RAND_FLOAT(360.0f) * M_DTOR, MTXF_NEW);
                        Matrix_MultVec3f(gCalcMatrix, &D_i5_801B8E44, &sp60);
                        Matrix_Pop(&gCalcMatrix);
                        debris->vel.x = sp60.x;
                        debris->vel.y = SIGN_OF(D_i5_801BBF00[i].unk_00.pos.y - 250.0f) - RAND_FLOAT(0.5f) + 0.5f;
                        debris->vel.z = (this->vel.z * 0.5f) + sp60.z;
                        debris->gravity = 0.1f;
                    }
                }
                D_i5_801BBF00[i].unk_26 = 4;
            }
        }
        this->work_044 = 1;
    } else {
        this->obj.pos.z = gPlayer[0].pos.z;
    }

    switch (this->timer_050) {
        case 100:
            debris = Game_SpawnActor(OBJ_ACTOR_DEBRIS);
            if (debris != NULL) {
                debris->fwork[0] = ((Rand_ZeroOne() < 0.5f) ? -1 : 1) * (RAND_FLOAT(1.0f) + 1.0f);
                debris->fwork[1] = ((Rand_ZeroOne() < 0.5f) ? -1 : 1) * (RAND_FLOAT(1.0f) + 1.0f);

                debris->state = 40;

                debris->work_046 = 25;
                debris->work_048 = 0;
                debris->work_04A = 4 | 2;

                debris->fwork[3] = 0.0f;
                debris->fwork[4] = -200.0f;

                debris->obj.pos.x = gPlayer[0].pos.x;
                debris->obj.pos.y = 500.0f;
                debris->obj.pos.z = gPlayer[0].trueZpos + debris->fwork[4];

                debris->obj.rot.y = (RAND_FLOAT(5.0f) + 90.0f) - 2.5f;
                debris->obj.rot.z = (RAND_FLOAT(5.0f) + 180.0f) - 2.5f;

                debris->vel.y = -10.0f;
                debris->gravity = 0.8f;
            }
            break;

        case 120:
            debris = Game_SpawnActor(OBJ_ACTOR_DEBRIS);
            if (debris != NULL) {
                debris->fwork[0] = ((Rand_ZeroOne() < 0.5f) ? -1 : 1) * (RAND_FLOAT(5.0f) + 5.0f);
                debris->fwork[1] = ((Rand_ZeroOne() < 0.5f) ? -1 : 1) * (RAND_FLOAT(5.0f) + 5.0f);

                debris->state = 40;

                debris->work_046 = 2;
                debris->work_048 = 1;
                debris->work_04A = 4 | 2;

                debris->iwork[1] = (s32) 1;
                debris->fwork[3] = -150.0f;
                debris->fwork[4] = -200.0f;
                debris->fwork[5] = 200.0f;

                debris->obj.pos.x = gPlayer[0].pos.x + debris->fwork[3];
                debris->obj.pos.y = 500.0f;
                debris->obj.pos.z = gPlayer[0].trueZpos + debris->fwork[4];

                debris->obj.rot.z = 90.0f;
                debris->vel.y = -10.0f;
                debris->gravity = 0.8f;
            }
            break;

        case 140:
            debris = Game_SpawnActor(OBJ_ACTOR_DEBRIS);
            if (debris != NULL) {
                debris->fwork[0] = ((Rand_ZeroOne() < 0.5f) ? -1 : 1) * (RAND_FLOAT(1.0f) + 1.0f);
                debris->fwork[1] = ((Rand_ZeroOne() < 0.5f) ? -1 : 1) * (RAND_FLOAT(1.0f) + 1.0f);

                debris->state = 40;

                debris->work_046 = 2;
                debris->work_048 = 1;
                debris->work_04A = 4 | 2;

                debris->iwork[1] = 2;
                debris->fwork[3] = 100.0f;
                debris->fwork[4] = -100.0f;
                debris->fwork[5] = 200.0f;

                debris->obj.pos.x = gPlayer[0].pos.x + debris->fwork[3];
                debris->obj.pos.y = 500.0f;
                debris->obj.pos.z = gPlayer[0].trueZpos + debris->fwork[4];

                debris->obj.rot.z = 90.0f;
                debris->vel.y = -10.0f;
                debris->gravity = 0.8f;
            }
            break;
    }

    if ((this->timer_050 == 0) && (gPlayer[0].state == PLAYERSTATE_ACTIVE)) {
        Object_Kill(&this->obj, this->sfxSource);
        gPlayer[0].state = PLAYERSTATE_LEVEL_COMPLETE;
        gPlayer[0].csState = 0;
    }
}
