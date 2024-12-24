#include "global.h"
#include "assets/ast_arwing.h"
#include "assets/ast_training.h"
#include "assets/ast_corneria.h"
#include "assets/ast_meteo.h"
#include "assets/ast_warp_zone.h"
#include "assets/ast_allies.h"
#include "assets/ast_sector_x.h"
#include "assets/ast_sector_y.h"
#include "assets/ast_aquas.h"
#include "assets/ast_macbeth.h"
#include "assets/ast_venom_1.h"
#include "assets/ast_venom_2.h"
#include "assets/ast_titania.h"
#include "assets/ast_7_ti_1.h"
#include "assets/ast_andross.h"
#include "assets/ast_area_6.h"
#include "assets/ast_enmy_space.h"
#include "assets/ast_enmy_planet.h"
#include "assets/ast_solar.h"
#include "assets/ast_ve1_boss.h"
#include "assets/ast_zoness.h"

s32 gTeamEventActorIndex[4] = { 0, 0, 0, 0 };
s32 gCallVoiceParam = 0;
s32 gCallTimer;

void ActorEvent_SetMessage(u16* msg, s32 character) {
    PRINTF("Enm->obj.pos.y + tmp_xyz.y=<%10.3f>\n");
    if ((gRadioState == 0) || (gRadioMsgRadioId != character)) {
        Radio_PlayMessage(msg, character);
    }
}

void func_enmy2_8006A800(Effect361* this, f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    Effect_Initialize(this);

    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_EFFECT_361;
    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;
    this->unk_48 = 3;

    if (Rand_ZeroOne() < 0.5f) {
        this->unk_48 = -this->unk_48;
    }

    this->unk_4A = 100;
    this->scale2 = scale2 * 0.25f;
    this->scale1 = 0.3f;

    if (scale2 < 10.0f) {
        this->scale1 = 0.1f;
    }

    this->obj.rot.z = RAND_FLOAT(360.0f);
    Object_SetInfo(&this->info, this->obj.id);
}

void func_enmy2_8006A900(f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            func_enmy2_8006A800(&gEffects[i], xPos, yPos, zPos, scale2);
            break;
        }
    }
}

void Actor237_Update(Actor237* this) {
    /* Unimplemented */
}

void Actor237_Draw(Actor237* this) {
    /* Unimplemented */
}

void Obj54_8006A984(Effect365* this, f32 xPos, f32 yPos, f32 zPos) {
    Effect_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_EFFECT_365;

    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;

    this->unk_44 = 40;
    this->scale2 = 5.0f;
    this->scale1 = RAND_FLOAT_CENTERED(2.0f);
    this->vel.y = 10.0f;
    this->obj.rot.z = RAND_FLOAT(360.0f);
    Object_SetInfo(&this->info, this->obj.id);
}

void Obj54_8006AA3C(f32 xPos, f32 yPos, f32 zPos) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Obj54_8006A984(&gEffects[i], xPos, yPos, zPos);
            break;
        }
    }
}

void CoWaterfall_Update(CoWaterfall* this) {
    Vec3f sp24;
    Vec3f sp18;

    Lib_Texture_Scroll(D_CO_60038F8, 32, 32, 1);
    if ((gGameFrameCount % 4) == 0) {
        Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);

        sp18.x = RAND_FLOAT_CENTERED(700.0f);
        sp18.y = RAND_FLOAT(50.0f);
        sp18.z = 700.0f;

        Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp18, &sp24);
        Obj54_8006AA3C(this->obj.pos.x + sp24.x, this->obj.pos.y + sp24.y + 50.0f, this->obj.pos.z + sp24.z);
    }
}

bool MeteoBall_IsCloseToPlayer(MeteoBall* this) {
    if ((fabsf(this->obj.pos.x - gPlayer[0].pos.x) < 700.0f) && (fabsf(this->obj.pos.y - gPlayer[0].pos.y) < 700.0f)) {
        return true;
    }
    return false;
}

// Unused Meteo Ball
void MeteoBall_Update(MeteoBall* this) {
    f32 sp2C;

    if (MeteoBall_IsCloseToPlayer(this) && (this->timer_0BC == 0)) {
        Effect_EnemyLaser(OBJ_EFFECT_ENEMY_LASER_1, this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, gEnemyShotSpeed);
        this->timer_0BC = 20;
    }
    sp2C = this->obj.pos.z + gPathProgress;
    this->obj.rot.y = Math_RadToDeg(Math_Atan2F(gPlayer[0].cam.eye.x - this->obj.pos.x, gPlayer[0].cam.eye.z - sp2C));
    this->obj.rot.x = -Math_RadToDeg(
        Math_Atan2F(gPlayer[0].cam.eye.y - this->obj.pos.y,
                    sqrtf(SQ(gPlayer[0].cam.eye.z - sp2C) + SQ(gPlayer[0].cam.eye.x - this->obj.pos.x))));
}

void MeHopBot_Update(MeHopBot* this) {
    bool sp34;

    this->gravity = 1.5f;

    sp34 = false;

    this->obj.rot.y = Math_RadToDeg(
        Math_Atan2F(gPlayer[gPlayerNum].pos.x - this->obj.pos.x, gPlayer[gPlayerNum].trueZpos - this->obj.pos.z));
    if (this->obj.pos.y < -500.0f) {
        this->obj.pos.y = -500.0f;
        this->vel.y = 0.0f;
        this->vel.x = 0.0f;
        this->vel.z = 0.0f;
        sp34 = true;
        this->iwork[1] = true;
    }

    if ((gGameFrameCount % 32) == 0) {
        Effect_EnemyLaser(OBJ_EFFECT_ENEMY_LASER_1, this->obj.pos.x, this->obj.pos.y + 180.0f, this->obj.pos.z,
                          gEnemyShotSpeed);
    }

    switch (this->state) {
        case 0:
            this->animFrame++;

            if (this->animFrame >= 30) {
                this->animFrame = 0;
            }

            if (this->animFrame == 21) {
                this->state = 1;

                this->vel.y = 40.0f;
                this->vel.z = -40.0f;
                this->vel.x = 10.0f;

                this->iwork[0] = 1 - this->iwork[0];

                if (this->iwork[0]) {
                    this->vel.x *= -1.0f;
                }

                if (this->iwork[1]) {
                    this->vel.x = 0.0f;
                    this->vel.z = -20.0f;
                }
            }
            break;

        case 1:
            if (this->vel.y > 10.0f) {
                this->animFrame++;
                if (this->animFrame >= 30) {
                    this->animFrame = 29;
                }
            } else {
                this->animFrame--;
                if (this->animFrame < 0) {
                    this->animFrame = 0;
                }
            }

            if (sp34) {
                this->state = 0;
            }
            break;
    }

    if (this->dmgType != DMG_NONE) {
        this->health -= 10;
        if ((this->health <= 0) || (this->dmgType >= DMG_EXPLOSION)) {
            func_effect_8007D2C8(this->obj.pos.x, this->obj.pos.y + 180.0f, this->obj.pos.z, 10.0f);
            Effect386_Spawn1(this->obj.pos.x, this->obj.pos.y + 180.0f, this->obj.pos.z, this->vel.x, this->vel.y,
                             this->vel.z, 8.0f, 30);
            Object_Kill(&this->obj, this->sfxSource);
            Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_EXPLOSION_S);
            gHitCount += this->info.bonus;
            D_ctx_80177850 = 15;
        } else {
            this->dmgType = DMG_NONE;
            this->timer_0C6 = 20;
            AUDIO_PLAY_SFX(NA_SE_EN_DAMAGE_S, this->sfxSource, 4);
            Effect_Effect341_Spawn(this->obj.pos.x, this->obj.pos.y + 180.0f, this->obj.pos.z, 5.0f);
        }
    }
}

void MeMora_Update(MeMora* this) {
}

s16 D_800CFF94[16] = {
    0, 98, 96, 94, 92, 90, 88, 86, 84, 82, 80, 78, 76, 74, 72, 70,
};
u8 gMeMoraPartIdx[16] = { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2 };
f32 gMeMoraScale[16] = {
    1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.99f, 0.98f, 0.94f, 0.88f, 0.8f, 1.0f,
};
Gfx* gMemoraPartDL[3] = { aEnmySpMeMora1DL, aEnmySpMeMora2DL, aEnmySpMeMora3DL };

void MeMora_Dying(MeMora* this) {
    Vec3f sp34;
    s32 index;

    this->counter_04E++;

    if (this->counter_04E >= 100) {
        this->counter_04E = 0;
    }

    gMeMoraXpos[this->work_046][this->counter_04E] = this->obj.pos.x;
    gMeMoraYpos[this->work_046][this->counter_04E] = this->obj.pos.y;
    gMeMoraZpos[this->work_046][this->counter_04E] = this->obj.pos.z;
    gMeMoraXrot[this->work_046][this->counter_04E] = this->obj.rot.x;
    gMeMoraYrot[this->work_046][this->counter_04E] = this->obj.rot.y;
    gMeMoraZrot[this->work_046][this->counter_04E] = this->obj.rot.z;

    this->obj.rot.x -= 10.0f;
    this->obj.rot.y += 3.0f;
    this->obj.rot.z += 5.0f;

    Math_Vec3fFromAngles(&sp34, this->obj.rot.x, this->obj.rot.y, 40.0f);

    this->vel.x = sp34.x;
    this->vel.y = sp34.y;
    this->vel.z = sp34.z;

    if ((this->timer_0BC == 0) && ((gGameFrameCount % 4) == 0)) {
        index = (D_800CFF94[this->work_04A] + this->counter_04E) % 100;
        if (this->work_04A == 0) {
            func_effect_8007D2C8(gMeMoraXpos[this->work_046][index], gMeMoraYpos[this->work_046][index],
                                 gMeMoraZpos[this->work_046][index], 7.0f);
        } else {
            func_effect_8007D2C8(gMeMoraXpos[this->work_046][index], gMeMoraYpos[this->work_046][index],
                                 gMeMoraZpos[this->work_046][index], 4.0f);
        }

        AUDIO_PLAY_SFX(NA_SE_EN_EXPLOSION_M, this->sfxSource, 4);
        this->work_04A++;

        if (this->work_04A > 15) {
            Object_Kill(&this->obj, this->sfxSource);
            gMeMoraStatus[this->work_046] = 0;
            gHitCount += this->info.bonus;
            D_ctx_80177850 = 15;
        }
    }
}

void Memora_DrawParts(MeMora* this, f32 xTrans, f32 yTrans, f32 zTrans, f32 xRot, f32 yRot, f32 zRot, u8 partIdx,
                      f32 scale, bool colorFlicker) {
    Vec3f src = { 0.0f, 0.0f, 0.0f };

    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, xTrans, yTrans, zTrans + gPathProgress, MTXF_APPLY);

    if (partIdx != 1) {
        Matrix_RotateY(gGfxMatrix, M_DTOR * yRot, MTXF_APPLY);
        Matrix_RotateX(gGfxMatrix, M_DTOR * xRot, MTXF_APPLY);
        Matrix_RotateZ(gGfxMatrix, M_DTOR * zRot, MTXF_APPLY);
    }

    Matrix_Scale(gGfxMatrix, scale, scale, 1.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);

    if (partIdx != 1) {
        RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
        if ((partIdx == 0) && (this->lockOnTimers[TEAM_ID_FOX] != 0)) {
            src.y += this->info.targetOffset;
            Matrix_MultVec3f(gGfxMatrix, &src, &gLockOnTargetViewPos[TEAM_ID_FOX]);
            if (gLockOnTargetViewPos[TEAM_ID_FOX].z > -500.0f) {
                this->lockOnTimers[TEAM_ID_FOX] = 0;
            }
        }
    } else {
        RCP_SetupDL_60(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
    }

    if (colorFlicker) {
        RCP_SetupDL_64();
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
    }

    gSPDisplayList(gMasterDisp++, gMemoraPartDL[partIdx]);
    Matrix_Pop(&gGfxMatrix);
    RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
}

void MeMora_Draw(MeMora* this) {
    s16 i;
    s16 j;

    for (i = this->work_04A; i < ARRAY_COUNT(D_800CFF94); i++) {
        j = (D_800CFF94[i] + this->counter_04E) % 100;
        Memora_DrawParts(this, gMeMoraXpos[this->work_046][j], gMeMoraYpos[this->work_046][j],
                         gMeMoraZpos[this->work_046][j], gMeMoraXrot[this->work_046][j], gMeMoraYrot[this->work_046][j],
                         gMeMoraZrot[this->work_046][j], gMeMoraPartIdx[i], gMeMoraScale[i], this->timer_0C6 % 2U);
    }
}

void CoIBeam_Update(CoIBeam* this) {
    this->obj.pos.x += this->vel.x;
    this->obj.pos.y += this->vel.y;
    this->obj.pos.z += this->vel.z;

    switch (this->state) {
        case 0:
            this->vel.y -= 1.0f;

            if (this->obj.pos.y < gGroundHeight + 40.0f) {
                this->obj.pos.y = gGroundHeight + 40.0f;
                AUDIO_PLAY_SFX(NA_SE_EN_METAL_BOUND_M, this->sfxSource, 0);
                this->state = 2;
                this->vel.y = 0.0f;
            }
            break;

        case 2:
            break;

        case 1:
            this->obj.rot.x += 10.0f;
            break;
    }
}

void func_enmy2_8006BA64(Effect375* this, f32 xPos, f32 yPos, f32 zPos) {
    Effect_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_EFFECT_375;

    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;

    this->scale2 = 0.0f;
    this->scale1 = 0.12f;
    this->obj.rot.y = RAND_FLOAT(360.0f);
    this->unk_60.y = RAND_FLOAT_CENTERED(3.0f);
    Object_SetInfo(&this->info, this->obj.id);
}

void func_enmy2_8006BB1C(f32 xPos, f32 yPos, f32 zPos) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            func_enmy2_8006BA64(&gEffects[i], xPos, yPos, zPos);
            break;
        }
    }
}

void CoMoleMissile_Update(CoMoleMissile* this) {
    Vec3f sp44;

    switch (this->state) {
        case 0:
            this->fwork[10] = RAND_FLOAT_CENTERED(1000.0f);
            this->state = 1;
            break;

        case 1:
            switch (this->work_046) {
                case 0:
                    this->fwork[0] += 2.0f;
                    if (this->fwork[0] > 10.0f) {
                        this->work_046 = 1;
                    }
                    break;

                case 1:
                    this->fwork[0] -= 2.0f;
                    if (this->fwork[0] < -10.0f) {
                        this->work_046 = 0;
                    }
                    break;
            }

            Math_Vec3fFromAngles(&sp44, this->obj.rot.x, this->obj.rot.y, 10.0f);
            this->vel.x = sp44.x;
            this->vel.y = sp44.y;
            this->vel.z = sp44.z;
            if (fabsf((this->obj.pos.z + this->fwork[10]) - gPlayer[0].trueZpos) < 3000.0f) {
                this->state = 2;
                this->timer_0BC = 20;
                this->vel.z = 0.0f;
                this->vel.x = 0.0f;
            }
            break;

        case 2:
            if (this->timer_0BC == 0) {
                this->state = 3;
                this->animFrame = 1;
                this->obj.pos.y += 30.0f;
                this->timer_0BC = 30;
                this->vel.y = 30.0f;
                this->gravity = 1.0f;
            }
            break;

        case 3:
            if (this->timer_0BC == 1) {
                Effect_EnemyLaser(OBJ_EFFECT_ENEMY_LASER_1, this->obj.pos.x, this->obj.pos.y, this->obj.pos.z,
                                  gEnemyShotSpeed);
            }

            if (this->vel.y < 12.0f) {
                Math_SmoothStepToF(&this->obj.rot.x, 180.0f, 0.1f, 7.0f, 0.01f);
            }
            if (this->obj.pos.y < (gGroundHeight + 10.0f)) {
                this->obj.pos.y = gGroundHeight;
                this->state = 4;
                this->animFrame = 0;
                this->vel.y = 0.0f;
                this->gravity = 0.0f;
                this->obj.rot.x = 0.0f;
            }
            break;

        case 4:
            if (this->timer_0BC == 0) {
                this->state = 0;
                this->obj.rot.y = RAND_FLOAT(360.0f);
            }
            break;
    }

    if ((this->obj.pos.y <= (gGroundHeight + 10.0f)) && ((gGameFrameCount % 8) == 0)) {
        func_enmy2_8006BB1C(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z);
    }

    if ((gGameFrameCount % 8) == 0) {
        func_enmy2_8006A900(RAND_FLOAT_CENTERED(50.0f) + this->obj.pos.x, this->obj.pos.y + 10.0f,
                            RAND_FLOAT_CENTERED(50.0f) + this->obj.pos.z, 0.5f);
    }

    if ((this->dmgType != DMG_NONE) && (this->animFrame != 0)) {
        Effect386_Spawn1(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 0.0f, this->vel.y, 0.0f, 3.0f, 5);
        Object_Kill(&this->obj, this->sfxSource);
        this->itemDrop = DROP_SILVER_RING;
        Actor_Despawn(this);
    }
    this->dmgType = DMG_NONE;
}

void func_enmy2_8006BF7C(f32 xPos, f32 yPos, f32 zPos) {
    static f32 D_800D001C[5] = { 0.0f, 30.0f, 60.0f, -60.0f, -30.0f };
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_800D001C); i++) {
        func_enmy2_8006A900(xPos + D_800D001C[i], yPos, zPos, 6.0f);
    }
}

typedef enum DebrisType {
    DEBRIS_0,
    DEBRIS_1,
    DEBRIS_2,
    DEBRIS_3,
    DEBRIS_4,
    DEBRIS_10,
    DEBRIS_34,
    DEBRIS_35,
    DEBRIS_36,
    DEBRIS_37,
    DEBRIS_38, // unused
    DEBRIS_39,
    DEBRIS_40,
    DEBRIS_41,
    DEBRIS_42,
    DEBRIS_43,
    DEBRIS_44,
    DEBRIS_45,
    DEBRIS_46,
    DEBRIS_47,
    DEBRIS_48,
    DEBRIS_49,
    DEBRIS_50,
    DEBRIS_51,
    DEBRIS_52,
    DEBRIS_53,
    DEBRIS_54,
    DEBRIS_55,
    DEBRIS_56,
    DEBRIS_57,
    DEBRIS_58,
    DEBRIS_59,
    DEBRIS_70 = 70,
} DebrisType;

Vec3f D_800D0030 = { 0.0f, -10.0f, 0.0f }; // could be in-function

void ActorDebris_Update(ActorDebris* this) {
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    s32 sp40;

    switch (this->state) {
        case 40:
            if (this->work_04A & 4) {
                this->obj.pos.x = gPlayer[0].pos.x + this->fwork[3];
                this->obj.pos.z = gPlayer[0].trueZpos + this->fwork[4];
            }

            this->obj.rot.x += this->fwork[0];
            this->obj.rot.y += this->fwork[1];
            this->obj.rot.z += this->fwork[2];

            if (((this->work_04A % 2U) == 1) && ((this->timer_0BC & 3) == 0)) {
                func_effect_8007D0E0(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, this->scale);
            }

            if ((this->fwork[5] + this->obj.pos.y) < 0.0f) {
                if (this->iwork[0] >= 2) {
                    this->fwork[2] = 0.0f;
                    this->fwork[1] = 0.0f;
                    this->fwork[0] = 0.0f;
                    this->vel.x = 0.0f;
                    this->vel.y = 0.0f;
                    this->vel.z = 0.0f;
                    this->gravity = 0.0f;
                } else {
                    if (this->work_04A & 4) {
                        switch (this->work_046) {
                            case 2:
                                AUDIO_PLAY_SFX(NA_SE_OB_SAND_BOUND_S, this->sfxSource, 4);
                                break;
                            case 25:
                                AUDIO_PLAY_SFX(NA_SE_OB_SAND_BOUND_M, this->sfxSource, 4);
                                break;
                        }
                    }
                    Math_SmoothStepToF(&this->fwork[0], 0.0f, 0.8f, 1.0f, 0.01f);
                    Math_SmoothStepToF(&this->fwork[1], 0.0f, 0.8f, 1.0f, 0.01f);
                    Math_SmoothStepToF(&this->fwork[2], 0.0f, 0.8f, 1.0f, 0.01f);
                    Math_SmoothStepToF(&this->vel.x, 0.0f, 0.5f, 1.0f, 0.01f);
                    this->obj.pos.y = 0.0f;
                    this->iwork[0]++;
                    if (this->vel.y < 0.0f) {
                        if (this->work_04A & 2) {
                            this->vel.y = this->vel.y * -0.05f;
                        } else {
                            this->vel.y = this->vel.y * -0.3f;
                        }
                    }
                }
                this->work_04A &= ~4;
            }
            break;

        case 45:
            this->obj.rot.y += this->fwork[0];
            this->obj.rot.z += this->fwork[1];
            break;

        case 46:
            this->obj.rot.x += this->fwork[0];
            this->obj.rot.y += this->fwork[1];
            this->obj.rot.z += this->fwork[2];

            Ground_801B6E20(this->obj.pos.x, this->obj.pos.z + gPathProgress, &sp4C, &sp48, &sp4C);

            if (this->obj.pos.y < sp48) {
                this->obj.pos.y = sp48;
                this->iwork[2]++;
                if (this->iwork[2] >= 2) {
                    this->vel.x = 0.0f;
                    this->vel.y = 0.0f;
                    this->vel.z = 0.0f;
                    this->fwork[0] = 0.0f;
                    this->fwork[1] = 0.0f;
                    this->fwork[2] = 0.0f;
                    this->gravity = 0.0f;
                } else {
                    this->vel.y = -this->vel.y * 0.3f;
                }
            }
            break;

        case 47:
            Ground_801B6E20(this->obj.pos.x, this->obj.pos.z + gPathProgress, &sp4C, &sp48, &sp4C);

            if (this->obj.pos.y < this->fwork[3] + (-100.0f + sp48)) {
                this->obj.pos.y = this->fwork[3] + sp48;
                this->iwork[0] = 0;
                this->iwork[2] = 1;
                this->vel.x = 0.0f;
                this->vel.y = 0.0f;
                this->vel.z = 0.0f;
                this->gravity = 0.0f;
                this->fwork[0] = 0.0f;
                this->fwork[1] = 0.0f;
                this->fwork[2] = 0.0f;
            }

            this->obj.rot.x += this->fwork[0];
            this->obj.rot.y += this->fwork[1];
            this->obj.rot.z += this->fwork[2];

            if ((this->iwork[0] == 1) && ((gGameFrameCount % 8) == 0)) {
                func_effect_8007D0E0(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 2.0f);
            }

            if (this->iwork[2] == 1) {
                if ((this->iwork[1] == 1) && ((this->work_048 == 8) || (this->work_048 == 9))) {
                    func_effect_8007D2C8(this->obj.pos.x, sp48 + 20.0f, this->obj.pos.z, 8.0f);
                }
                Object_Kill(&this->obj, this->sfxSource);
            }
            break;

        case 48:
        case 49:
        case 51:
        case 52:
        case 53:
        case 55:
            if (((this->timer_0BC == 0) || (Object_CheckCollision(this->index, &this->obj.pos, &D_800D0030, 1) != 0) ||
                 (this->obj.pos.y < (gGroundHeight + 10.0f))) &&
                (this->timer_0BE == 0)) {
                Effect_Effect364_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + 50.0f, this->scale * 10.0f);
                Object_Kill(&this->obj, this->sfxSource);
                Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_EXPLOSION_S);
            }
            break;

        case 56:
            Math_SmoothStepToF(&this->scale, 0.0f, 0.1f, 2.0f, 0.0001f);
            if (((this->timer_0BC == 0) || (Object_CheckCollision(this->index, &this->obj.pos, &D_800D0030, 1) != 0) ||
                 (this->obj.pos.y < (gGroundHeight + 10.0f))) &&
                (this->timer_0BE == 0)) {
                Effect_Effect364_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + 50.0f, this->scale * 10.0f);
                Object_Kill(&this->obj, this->sfxSource);
                Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_EXPLOSION_S);
            }
            break;

        case 58:
            if (this->work_046 == 0) {
                this->work_046++;
                this->fwork[0] = RAND_FLOAT_CENTERED(30.0f);
                this->fwork[1] = RAND_FLOAT_CENTERED(30.0f);
                this->fwork[2] = RAND_FLOAT_CENTERED(30.0f);
            }

            this->obj.rot.x += this->fwork[0];
            this->obj.rot.y += this->fwork[1];
            this->obj.rot.z += this->fwork[2];

            if (((this->timer_0BC == 0) || (Object_CheckCollision(this->index, &this->obj.pos, &D_800D0030, 1) != 0) ||
                 (this->obj.pos.y < (gGroundHeight + 10.0f))) &&
                (this->timer_0BE == 0)) {
                Effect_Effect364_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + 50.0f, this->scale * 10.0f);
                Object_Kill(&this->obj, this->sfxSource);
                Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_EXPLOSION_S);
            }
            break;

        case 54:
            if (((this->timer_0BC == 0) || (Object_CheckCollision(this->index, &this->obj.pos, &D_800D0030, 1) != 0) ||
                 (this->obj.pos.y < (gGroundHeight + 10.0f))) &&
                (this->timer_0BE == 0)) {
                Effect_Effect364_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + 70.0f, this->scale * 20.0f);
                Effect_Effect364_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + 70.0f, this->scale * 20.0f);
                Object_Kill(&this->obj, this->sfxSource);
                Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_EXPLOSION_S);
            }
            break;

        case 50:
            if ((this->iwork[0] == 2) && (this->timer_0BC == 0)) {
                func_effect_8007D2C8(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 5.0f);
                this->timer_0BC = 4;
            }
            this->obj.rot.x += this->fwork[0];
            this->obj.rot.y += this->fwork[1];
            this->obj.rot.z += this->fwork[2];
            if (Object_CheckCollision(this->index, &this->obj.pos, &D_tank_800C9F2C, 1) != 0) {
                this->vel.x *= -0.7f;
            }
            if (this->obj.pos.y < gGroundHeight) {
                Object_Kill(&this->obj, this->sfxSource);
            }
            break;

        case 57:
            this->obj.rot.x += this->fwork[0];
            this->obj.rot.y += this->fwork[1];
            this->obj.rot.z += this->fwork[2];

            if (Object_CheckCollision(this->index, &this->obj.pos, &D_tank_800C9F2C, 1) != 0) {
                this->vel.x *= -0.7f;
            }

            if (this->obj.pos.y < gGroundHeight) {
                if (this->iwork[0] >= 3) {
                    this->vel.y = 0.0f;
                    this->gravity = 0.0f;
                    this->fwork[2] = 0.0f;
                    this->fwork[1] = 0.0f;
                    this->fwork[0] = 0.0f;
                } else {
                    this->iwork[0]++;
                    this->vel.y = -this->vel.y * 0.7f;
                    this->obj.pos.y = gGroundHeight;
                    this->fwork[0] *= 0.5f;
                    this->fwork[1] *= 0.5f;
                    this->fwork[2] *= 0.5f;
                }
            }
            break;

        default:
            if (this->work_046 == 0) {
                this->work_046++;
                this->fwork[10] = RAND_FLOAT_CENTERED(30.0f);
                this->fwork[11] = RAND_FLOAT_CENTERED(30.0f);
                this->fwork[12] = RAND_FLOAT_CENTERED(30.0f);
            }

            this->obj.rot.x += this->fwork[10];
            this->obj.rot.y += this->fwork[11];
            this->obj.rot.z += this->fwork[12];

            if (this->state == 70) {
                if ((this->timer_0BC == 0) ||
                    (Object_CheckCollision(this->index, &this->obj.pos, &D_800D0030, 1) != 0) ||
                    (this->obj.pos.y < (gGroundHeight + 10.0f))) {
                    Object_Kill(&this->obj, this->sfxSource);
                }
            } else if (this->state == 39) {
                if (((this->timer_0BC == 0) ||
                     (Object_CheckCollision(this->index, &this->obj.pos, &D_800D0030, 1) != 0) ||
                     (this->obj.pos.y < (gGroundHeight + 10.0f))) &&
                    (this->timer_0BE == 0)) {
                    func_effect_8007D0E0(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 10.0f);
                    Object_Kill(&this->obj, this->sfxSource);
                    Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_EXPLOSION_S);
                }
            } else if (((this->state >= 41) && (this->state < 45)) || (this->state == 59)) {
                if (((this->timer_0BC == 0) ||
                     (Object_CheckCollision(this->index, &this->obj.pos, &D_800D0030, 1) != 0)) &&
                    (this->timer_0BE == 0)) {
                    func_effect_8007D0E0(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 2.0f * this->scale);
                    Object_Kill(&this->obj, this->sfxSource);
                    Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_EXPLOSION_S);
                }
                if (Play_CheckDynaFloorCollision(&sp44, &sp40, this->obj.pos.x, this->obj.pos.y, this->obj.pos.z)) {
                    Effect_Effect381_Spawn(this->obj.pos.x, sp44, this->obj.pos.z, 2.0f);
                    Object_Kill(&this->obj, this->sfxSource);
                }
            } else if (this->state >= 10) {
                if ((this->timer_0BC & 3) == 0) {
                    func_effect_8007D0E0(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, this->scale);
                }
                if (((this->timer_0BC == 0) ||
                     (Object_CheckCollision(this->index, &this->obj.pos, &D_800D0030, 1) != 0) ||
                     (this->obj.pos.y < (gGroundHeight + 10.0f))) &&
                    (this->timer_0BE == 0)) {
                    Effect386_Spawn1(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, this->vel.x, this->vel.y,
                                     this->vel.z, this->scale * 1.5f, 4);
                    Object_Kill(&this->obj, this->sfxSource);
                    Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_EXPLOSION_S);
                }
            } else {
                if ((this->state == 3) && ((this->timer_0BC % 8) == 0)) {
                    func_effect_8007D0E0(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 1.5f);
                }
                if ((Object_CheckCollision(this->index, &this->obj.pos, &D_800D0030, 1) != 0) ||
                    (this->obj.pos.y < (gGroundHeight + 10.0f))) {
                    if (gLevelType == LEVELTYPE_SPACE) {
                        func_effect_8007D0E0(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 2.0f);
                        Object_Kill(&this->obj, this->sfxSource);
                        return;
                    }

                    this->vel.y *= -0.2f;
                    this->obj.pos.y += this->vel.y * 5.0f;
                    this->iwork[0]++;

                    if (this->iwork[0] >= 2) {
                        Object_Kill(&this->obj, this->sfxSource);
                    }

                    if ((this->state != 2) && (this->state != 4)) {
                        func_enmy2_8006BF7C(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z);
                    } else if (gCurrentLevel == LEVEL_FORTUNA) {
                        Effect_Effect362_Spawn(RAND_FLOAT_CENTERED(10.0f) + this->obj.pos.x, this->obj.pos.y,
                                               this->obj.pos.z, 1.0f);
                        Effect_Effect362_Spawn(RAND_FLOAT_CENTERED(10.0f) + this->obj.pos.x, this->obj.pos.y,
                                               this->obj.pos.z, 1.0f);
                        Effect_Effect362_Spawn(RAND_FLOAT_CENTERED(10.0f) + this->obj.pos.x, this->obj.pos.y,
                                               this->obj.pos.z, 1.0f);
                    }
                }

                if (this->state == 4) {
                    if ((gCurrentLevel == LEVEL_KATINA) && (this->timer_0BC == 0)) {
                        Object_Kill(&this->obj, this->sfxSource);
                    }
                } else {
                    if ((this->timer_0BC % 2) != 0) {
                        func_effect_8007D24C(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 1.0f);
                    }
                    if ((gLevelType == LEVELTYPE_SPACE) && (this->timer_0BC == 0)) {
                        Object_Kill(&this->obj, this->sfxSource);
                    }
                }
            }
            break;
    }
}

// Appears to be a collision check for scenery shadow boxes
void func_enmy2_8006D0F4(Actor* this) {
    s32 i;
    s32 j;
    f32* hitboxData;
    Vec3f spA8;
    Vec3f sp9C;
    s32 temp_fs0;
    s32 temp_fs1;
    s32 temp_fs2;
    s32 count;
    Hitbox* hitbox;

    D_ctx_80161A7C = 110;
    D_ctx_80161A80 = 110;
    D_ctx_80161A84 = 110;
    D_ctx_80178544 = 40;

    for (i = 0; i < ARRAY_COUNT(gScenery); i++) {
        if ((gScenery[i].obj.status == OBJ_ACTIVE) && ((gPlayer[0].trueZpos - 3000.0f) < gScenery[i].obj.pos.z)) {
            hitboxData = D_edata_800CF964[gScenery[i].obj.id];
            count = *hitboxData;
            if (count != 0) {
                Matrix_RotateY(gCalcMatrix, -gScenery[i].obj.rot.y * M_DTOR, MTXF_NEW);

                spA8.x = this->obj.pos.x - gScenery[i].obj.pos.x;
                spA8.y = this->obj.pos.y - gScenery[i].obj.pos.y;
                spA8.z = this->obj.pos.z - gScenery[i].obj.pos.z;

                Matrix_MultVec3fNoTranslate(gCalcMatrix, &spA8, &sp9C);

                temp_fs0 = gScenery[i].obj.pos.x + sp9C.x;
                temp_fs1 = gScenery[i].obj.pos.y + sp9C.y;
                temp_fs2 = gScenery[i].obj.pos.z + sp9C.z;
                hitboxData++;

                for (j = 0; j < count; j++) {
                    hitbox = (Hitbox*) hitboxData;
                    if (Play_CheckSingleHitbox(hitbox, gScenery[i].obj.pos.x, gScenery[i].obj.pos.y,
                                               gScenery[i].obj.pos.z, temp_fs0, temp_fs1, temp_fs2)) {
                        D_ctx_80161A7C = 10;
                        D_ctx_80161A80 = 10;
                        D_ctx_80161A84 = 10;
                        this->unk_0C8 = 5;
                    }
                    hitboxData += 6;
                }
            }
        }
    }
}

void MeteoTunnel_Update(MeTunnel* this) {
    this->obj.rot.z += 1.0f;
}

typedef enum EventInfoSfx {
    /*  0 */ EISFX_NONE,
    /*  1 */ EISFX_EN_ENGINE_01,
    /*  2 */ EISFX_ARWING_ENGINE_FG,
    /*  3 */ EISFX_GREATFOX_ENGINE,
    /*  4 */ EISFX_EN_SHIP_ENGINE_S,
    /*  5 */ EISFX_OB_WING,
    /*  6 */ EISFX_EN_ALIEN_FLY,
    /*  7 */ EISFX_EN_SPACE_SHIP,
} EventInfoSfx;

typedef struct {
    /* 0x00 */ Gfx* dList;
    /* 0x04 */ f32* hitbox;
    /* 0x08 */ f32 scale;
    /* 0x0C */ f32 cullDistance;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ u8 info_unk_16;
    /* 0x15 */ u8 info_unk_14;
    /* 0x16 */ u8 sfx;
    /* 0x17 */ u8 info_unk_19;
    /* 0x18 */ f32 targetOffset;
    /* 0x1C */ u8 bonus;
} EventActorInfo; // size = 0x20

// clang-format off

EventActorInfo sEventActorInfo[108] = {
    /*  EVID_VENOM_FIGHTER_1 */ { aVenomFighter1DL, gCubeHitbox100, 1.0f, 100.0f, 3000.0f, 1, 0, EISFX_EN_ENGINE_01, 0, 1.0f, 1 },
    /*  EVID_VENOM_FIGHTER_2 */ { aVenomFighter2DL, gCubeHitbox100, 1.0f, 100.0f, 3000.0f, 1, 0, EISFX_EN_ENGINE_01, 0, 1.0f, 1 },
    /*  EVID_VENOM_FIGHTER_2 */ { NULL, gCubeHitbox100, 1.0f, 20000.0f, 3000.0f, 1, 0, EISFX_ARWING_ENGINE_FG, 0, 0.0f, 0 },
    /*  EVID_ME_SLIPPY */ { aSpyEyeDL, gCubeHitbox100, 1.5f, 100.0f, 3000.0f, 1, 0, EISFX_NONE, 0, 1.0f, 1 },
    /*  EVID_SPY_EYE */ { aGrangaFighter1DL, gCubeHitbox100, 1.0f, 100.0f, 3000.0f, 1, 0, EISFX_EN_ENGINE_01, 0, 1.0f, 1 },
    /*  EVID_GRANGA_FIGHTER_2 */ { aGrangaFighter2DL, gCubeHitbox100, 1.0f, 100.0f, 3000.0f, 1, 0, EISFX_EN_ENGINE_01, 0, 1.0f, 1 },
    /*  EVID_FIREBIRD */ { NULL, gCubeHitbox100, 1.0f, 100.0f, 3000.0f, 1, 0, EISFX_NONE, 0, 1.0f, 1 },
    /*  EVID_CORNERIAN_FIGHTER */ { aCoCornerianFighterDL, gCubeHitbox100, 1.0f, 100.0f, 3000.0f, 1, 0, EISFX_EN_ENGINE_01, 0, 0.0f, 1 },
    /*  EVID_VENOM_TANK */ { aVenomTankDL, gCubeHitbox100, 1.0f, 100.0f, 3000.0f, 2, 0, EISFX_EN_ENGINE_01, 1, 1.0f, 1 },
    /*  EVID_TRIPOD */ { NULL, gCubeHitbox100, 1.5f, 100.0f, 3000.0f, 1, 0, EISFX_EN_ALIEN_FLY, 0, 1.0f, 1 },
    /*  EVID_ATTACKER_1 */ { aAttacker1DL, gCubeHitbox200, 2.0f, 100.0f, 3000.0f, 1, 0, EISFX_EN_ENGINE_01, 0, 1.0f, 1 },
    /*  EVID_ATTACKER_2 */ { aAttacker2DL, gCubeHitbox100, 1.5f, 100.0f, 3000.0f, 1, 0, EISFX_EN_ALIEN_FLY, 0, 1.0f, 1 },
    /*  EVID_ATTACKER_3 */ { aAttacker3DL, gCubeHitbox100, 2.0f, 100.0f, 3000.0f, 1, 0, EISFX_EN_ENGINE_01, 0, 1.0f, 1 },
    /*  EVID_ME_METEOR_1 */ { aMeMeteor1DL, gCubeHitbox100, 2.5f, 100.0f, 3000.0f, 1, 0, EISFX_EN_ENGINE_01, 0, 1.0f, 1 },
    /*  EVID_ME_METEOR_2 */ { aMeMeteor2DL, gCubeHitbox400, 7.0f, 100.0f, 3000.0f, 1, 0, EISFX_EN_ENGINE_01, 0, 1.0f, 1 },
    /*  EVID_COMMANDER */ { aCommanderDL, gCubeHitbox100, 1.5f, 100.0f, 3000.0f, 1, 0, EISFX_EN_ENGINE_01, 0, 1.0f, 1 },
    /*  EVID_SPIDER */ { aSpiderDL, gCubeHitbox100, 1.5f, 100.0f, 3000.0f, 1, 0, EISFX_EN_ALIEN_FLY, 0, 1.0f, 1 },
    /*  EVID_ZERAM_CLASS_CRUISER */ { aA6ZeramClassCruiserDL, aA6ZeramClassCruiserHitbox, -2.0f, 2100.0f, 3000.0f, 0, 0, EISFX_EN_SPACE_SHIP, 0, 0.0f, 5 },
    /*  EVID_SX_SPY_EYE */ { aSxSpyEyeDL, gCubeHitbox200, 2.0f, 100.0f, 3000.0f, 1, 0, EISFX_EN_ENGINE_01, 0, 1.0f, 1 },
    /*  EVID_SX_CANINE */ { aSxCanineDL, gCubeHitbox100, 1.5f, 100.0f, 3000.0f, 1, 0, EISFX_EN_ENGINE_01, 0, 1.0f, 1 },
    /*  EVID_SPACE_MINE */ { NULL, gCubeHitbox100, 1.0f, 100.0f, 3000.0f, 2, 1, EISFX_EN_ENGINE_01, 0, 0.0f, 1 },
    /*  EVID_A6_NINJIN_MISSILE */ { NULL, gCubeHitbox200, 2.0f, 100.0f, 3000.0f, 1, 0, EISFX_EN_ENGINE_01, 0, 0.0f, 1 },
    /*  EVID_A6_ROCKET */ { NULL, gCubeHitbox100, 1.5f, 100.0f, 3000.0f, 1, 0, EISFX_EN_ENGINE_01, 0, 0.0f, 1 },
    /*  EVID_VENOM_FIGHTER_3 */ { aVenomFighter3DL, gCubeHitbox100, 1.5f, 100.0f, 3000.0f, 1, 0, EISFX_EN_ENGINE_01, 0, 1.0f, 1 },
    /*  EVID_SX_BASE_DEBRIS_1 */ { aSxBaseDebris1DL, aSxBaseDebris1Hitbox, -1.0f, 2100.0f, 3001.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  EVID_SX_BASE_WALL_1 */ { aSxBaseWall1DL, aSxBaseWall1Hitbox, -1.0f, 2100.0f, 3001.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  EVID_SX_BASE_DEBRIS_2 */ { aSxBaseDebris2DL, aSxBaseDebris2Hitbox, -1.0f, 2100.0f, 3001.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  EVID_SX_LASER */ { NULL, aSxLaserHitbox, 2.5f, 100.0f, 3000.0f, 2, 0, EISFX_NONE, 0, 1.0f, 1 },
    /*  EVID_SX_WATCH_POST */ { aSxWatchPostDL, aSxWatchPostHitbox, 3.0f, 100.0f, 3000.0f, 2, 0, EISFX_NONE, 0, 1.0f, 1 },
    /*  EVID_SX_SPACE_MINE */ { aSxSpaceMineDL, aSxSpaceMineHitbox, 1.0f, 100.0f, 3000.0f, 2, 1, EISFX_NONE, 0, 1.0f, 1 },
    /*  EVID_A6_HARLOCK_FRIGATE */ { aA6HarlockFrigateDL, aA6HarlockFrigateHitbox, -2.0f, 2100.0f, 3001.0f, 0, 0, EISFX_EN_SPACE_SHIP, 0, 0.0f, 2 },
    /*  EVID_A6_UMBRA_STATION */ { NULL, aA6UmbraStationHitbox, -2.0f, 2100.0f, 3001.0f, 0, 0, EISFX_NONE, 0, 0.0f, 3 },
    /*  EVID_SX_BASE_FLOOR_1 */ { aSxBaseFloor1DL, aSxBaseFloor1Hitbox, -1.0f, 2100.0f, 3001.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  EVID_CRUISER_GUN */ { NULL, gCubeHitbox200, 2.0f, 100.0f, 3000.0f, 1, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  EVID_SX_BASE_WALL_2 */ { aSxBaseWall2DL, aSxBaseWall2Hitbox, -1.0f, 2100.0f, 3001.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  EVID_SX_BASE_WALL_3 */ { aSxBaseWall3DL, aSxBaseWall3Hitbox, -1.0f, 2100.0f, 3001.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  EVID_TI_BOMBER */ { NULL, gCubeHitbox400, 2.0f, 200.0f, 3000.0f, 1, 0, EISFX_EN_ENGINE_01, 0, 1.0f, 1 },
    /*  EVID_SX_BORZOI_FIGHTER */ { aSxBorzoiFighterDL, gCubeHitbox100, 1.5f, 100.0f, 3000.0f, 1, 0, EISFX_EN_ENGINE_01, 0, 1.0f, 1 },
    /*  EVID_SX_WARP_GATE */ { NULL, aSxWarpGateHitbox, 1.0f, 500.0f, 3000.0f, 1, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  EVID_SX_BASE_WALL_TILE_1 */ { aSxBaseWallTile1DL, aSxBaseWallTile1Hitbox, -1.0f, 2100.0f, 3001.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  EVID_EVENT_HANDLER */ { NULL, gNoHitbox, 1.0f, 100.0f, 3001.0f, 2, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  EVID_SY_SHIP_1 */ { aSyShip1DL, aSyShip1Hitbox, -1.0f, 10000.0f, 3001.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  EVID_SY_SHIP_2 */ { aSyShip2DL, aSyShip2Hitbox, -1.0f, 10000.0f, 3001.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  EVID_TEAMMATE */ { NULL, gCubeHitbox100, 1.0f, 20000.0f, 3000.0f, 1, 0, EISFX_ARWING_ENGINE_FG, 0, 0.0f, 0 },
    /*  EVID_SY_SHIP_3 */ { aSyShip3DL, aSyShip3Hitbox, -1.0f, 10000.0f, 3001.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  EVID_ME_METEOR_3 */ { aMeMeteor3DL, gCubeHitbox200, -1.0f, 300.0f, 3001.0f, 0, 0, EISFX_NONE, 0, 1.0f, 1 },
    /*  EVID_ZO_PATROL_BOAT */ { aZoPatrolBoatDL, gCubeHitbox200, 1.0f, 100.0f, 3000.0f, 1, 0, EISFX_EN_SHIP_ENGINE_S, 0, 1.0f, 1 },
    /*  EVID_ME_SECRET_MARKER_1 */ { aMeSecretMarker1DL, gCubeHitbox100, -1.0f, 100.0f, 3000.0f, 1, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  EVID_SY_ROBOT_1 */ { NULL, aSyRobotHitbox, 0.3f, 100.0f, 3000.0f, 0, 0, EISFX_EN_ENGINE_01, 0, 1.0f, 1 },
    /*  EVID_SY_ROBOT_2 */ { NULL, aSyRobotHitbox, 0.3f, 100.0f, 3000.0f, 0, 0, EISFX_EN_ENGINE_01, 0, 1.0f, 1 },
    /*  EVID_SY_ROBOT_3 */ { NULL, aSyRobotHitbox, 0.3f, 100.0f, 3000.0f, 0, 0, EISFX_EN_ENGINE_01, 0, 1.0f, 1 },
    /*  EVID_SY_ROBOT_4 */ { aSyRobot4DL, aSyRobot4Hitbox, 2.0f, 100.0f, 3000.0f, 0, 0, EISFX_EN_ENGINE_01, 0, 1.0f, 1 },
    /*  EVID_SARUMARINE_PERISCOPE */ { NULL, aZoSarumarinePeriscopeHitbox, -1.0f, 1000.0f, 3000.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  EVID_SX_BASE_WALL_4 */ { aSxBaseWall4DL, aSxBaseWall4Hitbox, -1.0f, 2100.0f, 3001.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  EVID_GAMMA_ON */ { aGammaOnDL, gCubeHitbox100, 1.5f, 100.0f, 3000.0f, 1, 0, EISFX_EN_ENGINE_01, 0, 1.0f, 1 },
    /*  EVID_GAMMA_OFF */ { aGammaOffDL, gCubeHitbox100, 1.5f, 100.0f, 3000.0f, 1, 0, EISFX_EN_ENGINE_01, 0, 1.0f, 1 },
    /*  EVID_TI_GREAT_FOX */ { NULL, gNoHitbox, -1.0f, 2000.0f, 3000.0f, 0, 0, EISFX_GREATFOX_ENGINE, 0, 0.0f, 1 },
    /*  EVID_SY_SHIP_3_2 */ { aSyShip3DL, gNoHitbox, -1.0f, 10000.0f, 3001.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  EVID_SY_SARUZIN */ { aSySaruzinDL, gNoHitbox, -1.0f, 10000.0f, 3001.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  EVID_SY_ROBOT_SPRITE_SIDE */ { aSyRobotSpriteSideDL, gNoHitbox, 2.0f, 100.0f, 3000.0f, 0, 0, EISFX_EN_ENGINE_01, 0, 0.0f, 1 },
    /*  EVID_SY_ROBOT_SPRITE_FRONT */ { aSyRobotSpriteFrontDL, gNoHitbox, 2.0f, 100.0f, 3000.0f, 0, 0, EISFX_EN_ENGINE_01, 0, 0.0f, 1 },
    /*  EVID_ME_METEOR_4 */ { aMeMeteor4DL, gCubeHitbox200, 2.5f, 100.0f, 3000.0f, 1, 0, EISFX_NONE, 0, 1.0f, 1 },
    /*  EVID_ME_METEOR_5 */ { aMeMeteor5DL, gCubeHitbox100, 2.5f, 100.0f, 3000.0f, 1, 0, EISFX_NONE, 0, 1.0f, 1 },
    /*  EVID_ME_BIG_METEOR */ { aMeBigMeteorDL, gNoHitbox, -1.0f, 100.0f, 3000.0f, 1, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  EVID_ME_ROCK_GULL */ { NULL, gCubeHitbox200, 3.0f, 100.0f, 3000.0f, 1, 0, EISFX_NONE, 0, 1.0f, 1 },
    /*  EVID_ME_METEOR_6 */ { aMeMeteor6DL, gCubeHitbox200, -1.0f, 100.0f, 8000.0f, 1, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  EVID_ME_SECRET_MARKER_2 */ { aMeSecretMarker2DL, gCubeHitbox100, -1.0f, 100.0f, 8000.0f, 1, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  EVID_ME_FLIP_BOT */ { NULL, aMeFlipBotHitbox, 3.0f, 100.0f, 3000.0f, 2, 0, EISFX_EN_ENGINE_01, 0, 1.0f, 1 },
    /*  EVID_SY_LASER_TURRET */ { aSyLaserTurretDL, aSyLaserTurretHitbox, 3.0f, 100.0f, 3000.0f, 1, 0, EISFX_NONE, 0, 1.0f, 1 },
    /*  EVID_SY_SHIP_DESTROYED */ { aSyShip3DestroyedDL, aSyShip3DestroyedHitbox, -1.0f, 10000.0f, 3001.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  EVID_SY_DEBRIS */ { aSyDebrisDL, gNoHitbox, 4.0f, 100.0f, 3000.0f, 0, 0, EISFX_EN_ENGINE_01, 0, 0.0f, 1 },
    /*  EVID_ITEM_WING_REPAIR */ { aArwingItemLasersDL, gNoHitbox, 1.0f, 100.0f, 3000.0f, 2, 0, EISFX_OB_WING, 0, 0.0f, 1 },
    /*  EVID_SY_SHIP_WINDOWS */ { aSyShipWindowsDL, aSyShipWindowsHitbox, 3.0f, 100.0f, 3000.0f, 1, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  EVID_SY_SHIP_4 */ { aSyShip4DL, aSyShip4Hitbox, -1.0f, 10000.0f, 3001.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  EVID_SY_SHIP_4_DESTROYED */ { aSyShip4DestroyedDL, aSyShip4DestroyedHitbox, -1.0f, 10000.0f, 3001.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  EVID_SY_SHIP_2_SPRITE */ { aSyShip2SpriteDL, gNoHitbox, -1.0f, 10000.0f, 3001.0f, 0, 0, EISFX_EN_ENGINE_01, 0, 0.0f, 1 },
    /*  EVID_SY_SHIP_3_SPRITE */ { aSyShip3SpriteDL, gNoHitbox, -1.0f, 10000.0f, 3001.0f, 0, 0, EISFX_EN_ENGINE_01, 0, 0.0f, 1 },
    /*  EVID_SY_SHIP_MISSILE */ { aSyShipMissileDL, aSyShipMissileHitbox, 3.0f, 100.0f, 3001.0f, 0, 0, EISFX_EN_ENGINE_01, 0, 0.0f, 1 },
    /*  EVID_SUPPLY_CRATE */ { NULL, gCubeHitbox150, 1.0f, 100.0f, 3000.0f, 2, 0, EISFX_NONE, 0, 1.0f, 0 },
    /*  EVID_ZO_BIRD */ { NULL, aZoBirdHitbox, 1.0f, 100.0f, 3000.0f, 0, 0, EISFX_NONE, 0, 1.0f, 1 },
    /*  EVID_VE1_PILLAR */ { NULL, D_VE1_601B474, -1.0f, 100.0f, 3000.0f, 2, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  EVID_VE1_BLOCKER */ { NULL, gNoHitbox, -1.0f, 100.0f, 3000.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  EVID_MA_LASER_TURRET */ { NULL, gCubeHitbox100, 2.0f, 100.0f, 3000.0f, 1, 0, EISFX_EN_ENGINE_01, 0, 1.0f, 1 },
    /*  EVID_AQ_OYSTER */ { NULL, aAqOysterEvHitbox, 1.0f, 100.0f, 3000.0f, 2, 0, EISFX_NONE, 0, 60.0f, 1 },
    /*  EVID_VE1_PILLAR_5 */ { aVe1Pillar5DL, aVe1Pillar5Hitbox, -1.0f, 100.0f, 3000.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  EVID_BILL */ { NULL, gCubeHitbox100, 1.0f, 20000.0f, 3000.0f, 1, 0, EISFX_ARWING_ENGINE_FG, 0, 0.0f, 0 },
    /*  EVID_KATT */ { NULL, gCubeHitbox100, 1.0f, 20000.0f, 3000.0f, 1, 0, EISFX_ARWING_ENGINE_FG, 0, 0.0f, 0 },
    /*  EVID_VE1_TEMPLE_BG */ { aVe1TempleBgDL, gNoHitbox, 1.0f, 100.0f, 3000.0f, 1, 1, EISFX_NONE, 0, 0.0f, 1 },
    /*  EVID_AQ_STARFISH */ { NULL, aAqStarfishHitbox, 1.0f, 100.0f, 3000.0f, 1, 0, EISFX_NONE, 0, 1.0f, 1 },
    /*  EVID_AQ_SHELL */ { NULL, aAqShellHitbox, 1.0f, 100.0f, 3000.0f, 1, 0, EISFX_NONE, 0, 1.0f, 1 },
    /*  EVID_MA_RAILROAD_CART */ { aMaRailroadCartDL, aMaRailroadCartHitbox, 1.0f, 100.0f, 3000.0f, 1, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  EVID_MA_GUILLOTINE_1 */ { aMaGuillotine1DL, aMaGuillotineHitbox, -1.0f, 100.0f, 3000.0f, 1, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  EVID_WZ_PILLAR_1 */ { aWzPillar1DL, aWzPillar1Hitbox, -1.0f, 2100.0f, 3001.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  EVID_WZ_PILLAR_2 */ { aWzPillar2DL, aWzPillar2Hitbox, -1.0f, 2100.0f, 3001.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  EVID_WZ_METEOR_1 */ { aWzMeteor1DL, aWzMeteor1Hitbox, 2.5f, 100.0f, 3000.0f, 1, 0, EISFX_NONE, 0, 1.0f, 1 },
    /*  EVID_WZ_METEOR_2 */ { aWzMeteor2DL, gCubeHitbox100, -1.0f, 100.0f, 8000.0f, 1, 0, EISFX_NONE, 0, 0.0f, 0 },
    /*  EVID_WZ_GATE */ { aWzGateDL, aWzGateHitbox, -1.0f, 1000.0f, 3000.0f, 1, 0, EISFX_NONE, 0, 0.0f, 0 },
    /*  EVID_ME_METEOR_7 */ { aMeMeteor7DL, gCubeHitbox100, -1.0f, 100.0f, 3000.0f, 1, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  EVID_MA_BOULDER */ { aMaBoulderDL, aMaBoulderHitbox, 1.0f, 100.0f, 3000.0f, 1, 1, EISFX_NONE, 0, 0.0f, 1 },
    /*  EVID_VE1_ENEMY_GATE */ { aVe1EnemyGateDL, aVe1EnemyGateHitbox, -1.0f, 100.0f, 3000.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /* EVID_ENEMY_GATE_DOOR_RIGHT */ { aVe1EnemyGateDoorRightDL, gNoHitbox, -1.0f, 100.0f, 3000.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /* EVID_ENEMY_GATE_DOOR_LEFT */ { aVe1EnemyGateDoorLeftDL, gNoHitbox, -1.0f, 100.0f, 3000.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /* EVID_TR_BARRIER */ { aTrBarrierDL, aTrBarrierHitbox, -1.0f, 100.0f, 3000.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /* EVID_ANDROSS_GATE */ { NULL, gNoHitbox, -1.0f, 500.0f, 3000.0f, 0, 0, EISFX_NONE, 0, 0.0f, 0 },
    /* EVID_ANDROSS_GATE_2 */ { NULL, gNoHitbox, -1.0f, 500.0f, 3000.0f, 0, 0, EISFX_NONE, 0, 0.0f, 0 },
    /* EVID_SX_WARP_ENMY */ { NULL, gCubeHitbox200, 1.0f, 100.0f, 3000.0f, 0, 0, EISFX_NONE, 0, 1.0f, 1 },
    /* EVID_KILLER_BEE */ { NULL, gCubeHitbox100, 1.0f, 100.0f, 3000.0f, 0, 0, EISFX_EN_ALIEN_FLY, 0, 0.0f, 0 },
    /* EVID_MA_GUILLOTINE_2 */ { aMaGuillotine2DL, aMaGuillotineHitbox, -1.0f, 100.0f, 3000.0f, 1, 0, EISFX_NONE, 0, 0.0f, 1 },
};

// clang-format on

Color_RGBA32 sEventTexLineColors[6] = {
    // could be in-function
    { 255, 255, 255, 255 }, { 160, 160, 255, 255 }, { 80, 80, 255, 255 },
    { 80, 255, 80, 255 },   { 255, 80, 80, 255 },   { 255, 255, 80, 255 },
};

void ActorEvent_ProcessScript(ActorEvent* this) {
    u16** levelScripts;
    u16* actorScript;
    u16* msg;
    u16* test;
    s32 i;
    s32 j;

    switch (gCurrentLevel) {
        case LEVEL_VENOM_ANDROSS:
            levelScripts = (uint16_t**) LOAD_ASSET(D_ANDROSS_C037E3C);
            break;
        case LEVEL_CORNERIA:
            levelScripts = (uint16_t**) LOAD_ASSET(D_CO_603D9E8);
            break;
        case LEVEL_METEO:
            levelScripts = (uint16_t**) LOAD_ASSET(D_ME_602F3AC);
            break;
        case LEVEL_AQUAS:
            levelScripts = (uint16_t**) LOAD_ASSET(D_AQ_60308B8);
            break;
        case LEVEL_TITANIA:
            levelScripts = (uint16_t**) LOAD_ASSET(D_TI_600631C);
            break;
        case LEVEL_SECTOR_X:
            levelScripts = (uint16_t**) LOAD_ASSET(D_SX_60320D0);
            break;
        case LEVEL_UNK_4:
            levelScripts = (uint16_t**) LOAD_ASSET(D_A6_60289FC);
            break;
        case LEVEL_AREA_6:
            levelScripts = (uint16_t**) LOAD_ASSET(D_A6_6027F50);
            break;
        case LEVEL_SECTOR_Y:
            levelScripts = (uint16_t**) LOAD_ASSET(D_SY_6032E18);
            break;
        case LEVEL_SOLAR:
            levelScripts = (uint16_t**) LOAD_ASSET(D_SO_6020DD0);
            break;
        case LEVEL_ZONESS:
            levelScripts = (uint16_t**) LOAD_ASSET(D_ZO_602AAC0);
            break;
        case LEVEL_VENOM_1:
            levelScripts = (uint16_t**) LOAD_ASSET(D_VE1_601B1E4);
            break;
        case LEVEL_MACBETH:
            levelScripts = (uint16_t**) LOAD_ASSET(D_MA_60381D8);
            break;
        case LEVEL_TRAINING:
            levelScripts = (uint16_t**) LOAD_ASSET(D_TR_6009B34);
            break;
        default:
            levelScripts = (uint16_t**) LOAD_ASSET(D_CO_603D9E8);
            break;
    }
    actorScript = LOAD_ASSET(levelScripts[this->aiType]);

    switch (EV_OPC_MASK(actorScript[this->aiIndex])) {
        case EV_OPC(EVOP_STOP_SCRIPT):
            this->state = EVSTATE_SCRIPT_END;
            if (this->info.cullDistance > 10000.0f) {
                this->info.cullDistance = 100.0f;
            }
            break;

        case EV_OPC(EVOP_INIT_ACTOR):
            Audio_KillSfxBySource(this->sfxSource);
            this->eventType = actorScript[this->aiIndex + 1];

            if (this->eventType == EVID_EVENT_HANDLER) {
                this->timer_0C2 = 10000;
            } else {
                this->timer_0C2 = 0;
            }

            this->fwork[11] = 0.0f;
            this->fwork[12] = 0.0f;

            if ((this->eventType == EVID_ME_ROCK_GULL) || (this->eventType == EVID_VE1_BLOCKER)) {
                this->fwork[15] = 0.0f;
            } else if (this->eventType == EVID_ZO_BIRD) {
                this->info.drawType = 2;
            }

            this->health = actorScript[this->aiIndex] & 0x1FF;
            this->aiIndex += 2;

            if ((this->eventType >= EVID_200) && (this->eventType < EVID_300)) {
                this->work_046 = 100;
                this->info.hitbox = gCubeHitbox200;
                this->info.targetOffset = 1.0f;

                for (i = 0; i < 2; i++) {
                    if (gMeMoraStatus[i] == 0) {
                        gMeMoraStatus[i] = 1;
                        this->work_046 = i;
                        for (j = 0; j < 100; j++) {
                            gMeMoraYpos[i][j] = this->obj.pos.y;
                            gMeMoraZpos[i][j] = this->obj.pos.z;
                        }
                        if (this->eventType == EVID_200) {
                            AUDIO_PLAY_SFX(NA_SE_EN_SPACE_SNAKE, this->sfxSource, 4);
                        }
                        break;
                    }
                }

                if (this->work_046 == 100) {
                    Object_Kill(&this->obj, this->sfxSource);
                }
            }

            if ((this->eventType == EVID_ME_SLIPPY) || (this->eventType == EVID_TEAMMATE)) {
                this->drawShadow = true;
                this->iwork[11] = 1;
            }

            if (this->eventType == EVID_VE1_BLOCKER) {
                this->drawShadow = true;
            }

            if (gPlayer[0].state == PLAYERSTATE_ACTIVE) {
                if (this->eventType == EVID_KATT) {
                    Audio_PlayFanfare(NA_BGM_KATT, 20, 10, 10);
                }
                if (this->eventType == EVID_BILL) {
                    Audio_PlayFanfare(NA_BGM_BILL, 20, 10, 10);
                }
            }

            if (this->eventType == EVID_ANDROSS_GATE) {
                this->animFrame = 0;
            }

            if (this->eventType == EVID_ANDROSS_GATE_2) {
                this->animFrame = Animation_GetFrameCount(&aVe2AndrossGateAnim) - 1;
            }

            if (this->eventType < EVID_200) {
                this->info.hitbox = SEGMENTED_TO_VIRTUAL(sEventActorInfo[this->eventType].hitbox);
                this->scale = sEventActorInfo[this->eventType].scale;
                this->info.unk_16 = sEventActorInfo[this->eventType].info_unk_16;
                this->info.unk_14 = sEventActorInfo[this->eventType].info_unk_14;
                this->info.unk_19 = sEventActorInfo[this->eventType].info_unk_19;
                this->info.targetOffset = sEventActorInfo[this->eventType].targetOffset;
                this->info.bonus = sEventActorInfo[this->eventType].bonus;

                if (this->eventType == EVID_SUPPLY_CRATE) {
                    this->info.damage = 0;
                }

                this->info.cullDistance = sEventActorInfo[this->eventType].cullDistance;
                this->fwork[25] = sEventActorInfo[this->eventType].unk_10;

                switch (sEventActorInfo[this->eventType].sfx) {
                    case EISFX_EN_ENGINE_01:
                        if (!((gCurrentLevel == LEVEL_SOLAR) || (this->eventType == EVID_FIREBIRD) ||
                              ((gCurrentLevel == LEVEL_CORNERIA) && (this->eventType == EVID_VENOM_TANK)))) {
                            AUDIO_PLAY_SFX(NA_SE_EN_ENGINE_01, this->sfxSource, 4);
                        }
                        break;
                    case EISFX_ARWING_ENGINE_FG:
                        AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, this->sfxSource, 4);
                        break;
                    case EISFX_GREATFOX_ENGINE:
                        AUDIO_PLAY_SFX(NA_SE_GREATFOX_ENGINE, this->sfxSource, 0);
                        break;
                    case EISFX_EN_SHIP_ENGINE_S:
                        AUDIO_PLAY_SFX(NA_SE_EN_SHIP_ENGINE_S, this->sfxSource, 4);
                        break;
                    case EISFX_OB_WING:
                        AUDIO_PLAY_SFX(NA_SE_OB_WING, this->sfxSource, 0);
                        break;
                    case EISFX_EN_ALIEN_FLY:
                        AUDIO_PLAY_SFX(NA_SE_EN_ALIEN_FLY, this->sfxSource, 4);
                        break;
                    case EISFX_EN_SPACE_SHIP:
                        AUDIO_PLAY_SFX(NA_SE_EN_SPACE_SHIP, this->sfxSource, 4);
                        break;
                }

                if (gPlayer[0].trueZpos < this->obj.pos.z) {
                    this->info.cullDistance = 3000.0f;
                }

                if (this->info.unk_16 == 0) {
                    this->obj.rot.z = this->fwork[23] = this->rot_0F4.z;
                    if (this->eventType != EVID_A6_UMBRA_STATION) {
                        this->rot_0F4.z = 0.0f;
                    }
                }
            }
            ActorEvent_ProcessScript(this);
            break;

        case EV_OPC(EVOP_SET_TEAM_ID):
            this->iwork[12] = actorScript[this->aiIndex + 1];

            if (this->iwork[12] <= TEAM_ID_PEPPY) {
                gTeamEventActorIndex[this->iwork[12]] = this->index;
            }

            this->aiIndex += 2;
            ActorEvent_ProcessScript(this);
            break;

        case EV_OPC(EVOP_ADD_TO_GROUP):
            this->iwork[15] = actorScript[this->aiIndex + 1];
            this->iwork[16] = actorScript[this->aiIndex] & 0x1FF;
            this->aiIndex += 2;
            ActorEvent_ProcessScript(this);
            break;

        case EV_OPC(EVOP_SET_AS_LEADER):
            gFormationLeaderIndex = this->index;
            gFormationInitPos.x = this->obj.pos.x;
            gFormationInitPos.y = this->obj.pos.y;
            gFormationInitPos.z = this->obj.pos.z;
            gFormationInitRot.x = this->obj.rot.x;
            gFormationInitRot.y = this->obj.rot.y;
            gFormationInitRot.z = this->obj.rot.z;
            this->aiIndex += 2;
            ActorEvent_ProcessScript(this);
            break;

        case EV_OPC(EVOP_SET_ACTION):
            if (actorScript[this->aiIndex + 1] == EVACT_ME_AS_OPEN) {
                this->state = EVSTATE_ME_AS_OPEN;
                this->fwork[11] = 0.0f;
                this->aiIndex += 2;
                break;
            }

            if (actorScript[this->aiIndex + 1] == EVACT_ME_AS_CLOSE) {
                this->info.hitbox = SEGMENTED_TO_VIRTUAL(gCubeHitbox200);
                this->state = EVSTATE_ME_AS_CLOSE;
                this->aiIndex += 2;
                break;
            }

            this->work_048 = actorScript[this->aiIndex + 1];

            if (this->work_048 == EVACT_3) {
                this->work_04C = 4;
            }

            if (this->work_048 == EVACT_TI_DROP_MINE) {
                this->timer_0BE = 50;
            }

            this->aiIndex += 2;
            ActorEvent_ProcessScript(this);
            break;

        case EV_OPC(EVOP_DROP_ITEM):
            this->itemDrop = actorScript[this->aiIndex + 1];
            this->aiIndex += 2;
            ActorEvent_ProcessScript(this);
            break;

        case EV_OPC(EVOP_SET_REVERB):
            Audio_SetEnvSfxReverb(actorScript[this->aiIndex + 1]);
            this->aiIndex += 2;
            ActorEvent_ProcessScript(this);
            break;

        case EV_OPC(EVOP_PLAY_MSG):
            msg = Message_PtrFromId(actorScript[this->aiIndex + 1]);
            if ((msg != NULL) && (gPlayer[0].state == PLAYERSTATE_ACTIVE)) {
                Radio_PlayMessage(msg, actorScript[this->aiIndex] & 0x1FF);
            }
            this->aiIndex += 2;
            ActorEvent_ProcessScript(this);
            break;

        case EV_OPC(EVOP_SET_SURFACE):
            if ((gGroundSurface == SURFACE_WATER) && (actorScript[this->aiIndex + 1] != 2)) {
                Audio_KillSfxBySourceAndId(gPlayer[0].sfxSource, NA_SE_SPLASH_LEVEL_S);
            }
            gGroundSurface = actorScript[this->aiIndex + 1];
            this->aiIndex += 2;
            ActorEvent_ProcessScript(this);
            this->obj.status = OBJ_FREE;
            break;

        case EV_OPC(EVOP_SET_CALL):
            gCallVoiceParam = actorScript[this->aiIndex] & 0x1FF;
            gCallTimer = actorScript[this->aiIndex + 1];
            this->aiIndex += 2;
            ActorEvent_ProcessScript(this);
            break;

        case EV_OPC(EVOP_RESTORE_TEAM):
            gTeamShields[actorScript[this->aiIndex + 1]] = 255;
            this->aiIndex += 2;
            ActorEvent_ProcessScript(this);
            break;

        case EV_OPC(EVOP_PLAY_SFX):
            Audio_PlayEventSfx(this->sfxSource, actorScript[this->aiIndex + 1]);
            this->aiIndex += 2;
            ActorEvent_ProcessScript(this);
            break;

        case EV_OPC(EVOP_STOP_SFX):
            Audio_StopEventSfx(this->sfxSource, actorScript[this->aiIndex + 1]);
            this->aiIndex += 2;
            ActorEvent_ProcessScript(this);
            break;

        case EV_OPC(EVOP_STOP_BGM):
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 50);
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 50);
            this->aiIndex += 2;
            ActorEvent_ProcessScript(this);
            break;

        case EV_OPC(EVOP_DAMAGE_TEAM):
            if (this->iwork[12] == actorScript[this->aiIndex + 1]) {
                this->dmgType = DMG_BEAM;
                this->damage = actorScript[this->aiIndex] & 0x1FF;
                this->dmgSource = DMG_SRC_100;
            } else {
                gTeamDamage[actorScript[this->aiIndex + 1]] = actorScript[this->aiIndex] & 0x1FF;
            }
            this->aiIndex += 2;
            ActorEvent_ProcessScript(this);
            break;

        case EV_OPC(EVOP_MAKE_TEXLINE):
            this->iwork[7] = 1;
            for (i = 0; i < ARRAY_COUNT(gTexturedLines); i++) {
                if (gTexturedLines[i].mode == 0) {
                    gTexturedLines[i].mode = 1;
                    gTexturedLines[i].xyScale = 3.0f;
                    gTexturedLines[i].posAA.x = this->obj.pos.x - this->vel.x;
                    gTexturedLines[i].posAA.y = this->obj.pos.y - this->vel.y;
                    gTexturedLines[i].posAA.z = this->obj.pos.z - this->vel.z;
                    gTexturedLines[i].prim.r = sEventTexLineColors[actorScript[this->aiIndex + 1]].r;
                    gTexturedLines[i].prim.g = sEventTexLineColors[actorScript[this->aiIndex + 1]].g;
                    gTexturedLines[i].prim.b = sEventTexLineColors[actorScript[this->aiIndex + 1]].b;
                    gTexturedLines[i].prim.a = sEventTexLineColors[actorScript[this->aiIndex + 1]].a;
                    this->iwork[8] = i;
                    break;
                }
            }
            this->aiIndex += 2;
            ActorEvent_ProcessScript(this);
            break;

        case EV_OPC(EVOP_STOP_TEXLINE):
            this->iwork[7] = 0;
            this->aiIndex += 2;
            ActorEvent_ProcessScript(this);
            break;

        case EV_OPC(EVOP_PURSUE_PLAYER):
            this->state = EVSTATE_PURSUE_PLAYER;
            this->timer_0BC = actorScript[this->aiIndex + 1];
            this->fwork[24] = actorScript[this->aiIndex] & 0x1FF;
            this->aiIndex += 2;
            break;

        case EV_OPC(EVOP_FLEE_PLAYER):
            this->state = EVSTATE_FLEE_PLAYER;
            this->timer_0BC = actorScript[this->aiIndex + 1];
            this->fwork[24] = actorScript[this->aiIndex] & 0x1FF;
            this->aiIndex += 2;
            break;

        case EV_OPC(EVOP_PURSUE_TARGET):
            this->state = EVSTATE_PURSUE_TARGET;
            this->timer_0BC = actorScript[this->aiIndex + 1];
            this->fwork[24] = actorScript[this->aiIndex] & 0x1FF;
            this->aiIndex += 2;
            break;

        case EV_OPC(EVOP_FLEE_TARGET):
            this->state = EVSTATE_FLEE_TARGET;
            this->timer_0BC = actorScript[this->aiIndex + 1];
            this->fwork[24] = actorScript[this->aiIndex] & 0x1FF;
            this->aiIndex += 2;
            break;

        case EV_OPC(EVOP_SET_TARGET):
            this->state = EVSTATE_WAIT;
            this->iwork[1] = gTeamEventActorIndex[actorScript[this->aiIndex] & 0x1FF];
            this->fwork[17] = actorScript[this->aiIndex + 1];
            this->timer_0BC = 0;
            this->aiIndex += 2;
            break;

        case EV_OPC(EVOP_CHASE_TARGET):
            this->state = EVSTATE_CHASE_TARGET;
            this->timer_0BC = actorScript[this->aiIndex + 1];
            this->fwork[24] = actorScript[this->aiIndex] & 0x1FF;
            this->aiIndex += 2;
            break;

        case EV_OPC(EVOP_PURSUE_CAMERA):
            this->state = EVSTATE_PURSUE_CAMERA;
            this->timer_0BC = actorScript[this->aiIndex + 1];
            this->fwork[24] = actorScript[this->aiIndex] & 0x1FF;
            this->aiIndex += 2;
            break;

        case EV_OPC(EVOP_FLEE_CAMERA):
            this->state = EVSTATE_FLEE_CAMERA;
            this->timer_0BC = actorScript[this->aiIndex + 1];
            this->fwork[24] = actorScript[this->aiIndex] & 0x1FF;
            this->aiIndex += 2;
            break;

        case EV_OPC(EVOP_SET_TRIGGER):
            this->iwork[2] = actorScript[this->aiIndex + 1];
            this->iwork[3] = actorScript[this->aiIndex] & 0x1FF;
            this->aiIndex += 2;
            ActorEvent_ProcessScript(this);
            break;

        case EV_OPC(EVOP_LOOP):
            if (actorScript[this->aiIndex + 1] < this->iwork[0]) {
                this->aiIndex += 2;
                this->iwork[0] = 0;
            } else if ((actorScript[this->aiIndex] & 0x1FF) < 200) {
                this->aiIndex = (actorScript[this->aiIndex] & 0x1FF) * 2;
                this->iwork[0]++;
            } else {
                this->aiType = (actorScript[this->aiIndex] & 0x1FF) - 200;
                this->aiIndex = 0;
                this->iwork[0] = 0;
            }
            ActorEvent_ProcessScript(this);
            break;

        case EV_OPC(EVOP_SET_WAIT):
            this->state = EVSTATE_WAIT;
            this->timer_0BC = actorScript[this->aiIndex + 1];
            this->aiIndex += 2;
            break;

        case EV_OPC(EVOP_SET_SPEED):
            this->fwork[0] = actorScript[this->aiIndex] & 0x7F;
            this->fwork[1] = this->fwork[0];
            this->iwork[5] = EV_ZMODE_MASK(actorScript[this->aiIndex]);
            this->timer_0BC = actorScript[this->aiIndex + 1];
            this->state = EVSTATE_WAIT;
            this->aiIndex += 2;
            break;

        case EV_OPC(EVOP_SET_BASE_ZVEL):
            this->fwork[22] = actorScript[this->aiIndex + 1] & 0xFF;
            this->aiIndex += 2;
            ActorEvent_ProcessScript(this);
            break;

        case EV_OPC(EVOP_SET_ACCEL):
            this->fwork[1] = actorScript[this->aiIndex] & 0x7F;
            this->iwork[5] = EV_ZMODE_MASK(actorScript[this->aiIndex]);
            this->timer_0BC = actorScript[this->aiIndex + 1];
            this->state = EVSTATE_WAIT;
            this->aiIndex += 2;
            break;

        case EV_OPC(EVOP_START_FORMATION):
            this->timer_0C0 = actorScript[this->aiIndex + 1];
            this->iwork[13] = 1;
            this->aiIndex += 2;
            ActorEvent_ProcessScript(this);
            break;

        case EV_OPC(EVOP_STOP_FORMATION):
            this->iwork[13] = 0;
            this->aiIndex += 2;
            ActorEvent_ProcessScript(this);
            break;

        case EV_OPC(EVOP_F4_PLUS_X):
            this->state = EVSTATE_F4_PLUS_X;
            this->fwork[2] = actorScript[this->aiIndex] & 0x1FF;
            this->fwork[3] = actorScript[this->aiIndex + 1] * 0.1f;
            this->aiIndex += 2;
            break;

        case EV_OPC(EVOP_F4_MINUS_X):
            this->state = EVSTATE_F4_MINUS_X;
            this->fwork[2] = actorScript[this->aiIndex] & 0x1FF;
            this->fwork[3] = actorScript[this->aiIndex + 1] * 0.1f;
            this->aiIndex += 2;
            break;

        case EV_OPC(EVOP_F4_PLUS_Y):
            this->state = EVSTATE_F4_PLUS_Y;
            this->fwork[2] = actorScript[this->aiIndex] & 0x1FF;
            this->fwork[3] = actorScript[this->aiIndex + 1] * 0.1f;
            this->aiIndex += 2;
            break;

        case EV_OPC(EVOP_F4_MINUS_Y):
            this->state = EVSTATE_F4_MINUS_Y;
            this->fwork[2] = actorScript[this->aiIndex] & 0x1FF;
            this->fwork[3] = actorScript[this->aiIndex + 1] * 0.1f;
            this->aiIndex += 2;
            break;

        case EV_OPC(EVOP_ROT_PLUS_X):
            this->fwork[4] = actorScript[this->aiIndex] & 0x1FF;
            this->fwork[5] = actorScript[this->aiIndex + 1] * 0.1f;
            this->fwork[6] = 1.0f;
            this->aiIndex += 2;
            ActorEvent_ProcessScript(this);
            break;

        case EV_OPC(EVOP_ROT_MINUS_X):
            this->fwork[4] = actorScript[this->aiIndex] & 0x1FF;
            this->fwork[5] = actorScript[this->aiIndex + 1] * 0.1f;
            this->fwork[6] = -1.0f;
            this->aiIndex += 2;
            ActorEvent_ProcessScript(this);
            break;

        case EV_OPC(EVOP_ROT_PLUS_Y):
            this->fwork[7] = actorScript[this->aiIndex] & 0x1FF;
            this->fwork[8] = actorScript[this->aiIndex + 1] * 0.1f;
            this->fwork[9] = 1.0f;
            this->aiIndex += 2;
            ActorEvent_ProcessScript(this);
            break;

        case EV_OPC(EVOP_ROT_MINUS_Y):
            this->fwork[7] = actorScript[this->aiIndex] & 0x1FF;
            this->fwork[8] = actorScript[this->aiIndex + 1] * 0.1f;
            this->fwork[9] = -1.0f;
            this->aiIndex += 2;
            ActorEvent_ProcessScript(this);
            break;

        case EV_OPC(EVOP_ROT_PLUS_Z):
            this->fwork[10] = actorScript[this->aiIndex] & 0x1FF;
            this->fwork[11] = actorScript[this->aiIndex + 1] * 0.1f;
            this->fwork[12] = 1.0f;
            this->aiIndex += 2;
            ActorEvent_ProcessScript(this);
            break;

        case EV_OPC(EVOP_ROT_MINUS_Z):
            this->fwork[10] = actorScript[this->aiIndex] & 0x1FF;
            this->fwork[11] = actorScript[this->aiIndex + 1] * 0.1f;
            this->fwork[12] = -1.0f;
            this->aiIndex += 2;
            ActorEvent_ProcessScript(this);
            break;

        case EV_OPC(EVOP_SET_ROTATE):
            this->iwork[6] = 1;
            this->aiIndex += 2;
            ActorEvent_ProcessScript(this);
            break;

        case EV_OPC(EVOP_STOP_ROTATE):
            this->iwork[6] = 0;
            this->aiIndex += 2;
            ActorEvent_ProcessScript(this);
            break;
    }
}

void ActorEvent_UpdateTexLines(ActorEvent* this) {
    if ((this->iwork[7] != 0) && (gTexturedLines[this->iwork[8]].mode != 0)) {
        gTexturedLines[this->iwork[8]].posBB.x = this->obj.pos.x;
        gTexturedLines[this->iwork[8]].posBB.y = this->obj.pos.y;
        gTexturedLines[this->iwork[8]].posBB.z = this->obj.pos.z;
    }
}

void ActorEvent_SetupEffect374(Effect* effect, f32 xPos, f32 yPos, f32 zPos) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = OBJ_EFFECT_374;

    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;

    effect->timer_50 = 20;
    Object_SetInfo(&effect->info, effect->obj.id);
    AUDIO_PLAY_SFX(NA_SE_EN_FALLING_DOWN, effect->sfxSource, 4);
}

void ActorEvent_SpawnEffect374(f32 xPos, f32 yPos, f32 zPos) {
    s32 i;

    for (i = 50; i < ARRAY_COUNT(gEffects); i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            ActorEvent_SetupEffect374(&gEffects[i], xPos, yPos, zPos);
            break;
        }
    }
}

void ActorEvent_SetupTIMine(Actor* actor, f32 xPos, f32 yPos, f32 zPos) {
    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_TI_LANDMINE;

    actor->obj.pos.x = xPos;
    actor->obj.pos.y = yPos;
    actor->obj.pos.z = zPos;

    Object_SetInfo(&actor->info, actor->obj.id);
    actor->info.unk_16 = 2;
    AUDIO_PLAY_SFX(NA_SE_EN_FALLING_DOWN, actor->sfxSource, 4);
}

void ActorEvent_SpawnTIMine(f32 xPos, f32 yPos, f32 zPos) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gActors); i++) {
        if (gActors[i].obj.status == OBJ_FREE) {
            ActorEvent_SetupTIMine(&gActors[i], xPos, yPos, zPos);
            break;
        }
    }
}

void Actor_SetupPlayerShot(PlayerShotId objId, PlayerShot* shot, s32 actorId, f32 xPos, f32 yPos, f32 zPos, f32 xVel,
                           f32 yVel, f32 zVel, f32 xRot, f32 yRot, f32 zRot) {
    PlayerShot_Initialize(shot);
    shot->obj.status = SHOT_ACTIVE;

    shot->vel.z = zVel;
    shot->vel.x = xVel;
    shot->vel.y = yVel;

    shot->obj.pos.x = xPos;
    shot->obj.pos.y = yPos;
    shot->obj.pos.z = zPos;

    shot->obj.rot.x = xRot + 180.0f;
    shot->obj.rot.y = yRot;
    shot->obj.rot.z = -zRot;

    shot->obj.id = objId;
    shot->unk_58 = 1;
    shot->unk_60 = 0;

    if (objId == PLAYERSHOT_GFOX_LASER) {
        shot->timer = 120;
    } else {
        shot->timer = 30;
    }
    shot->sourceId = actorId + NPC_SHOT_ID;

    if (gLevelMode == LEVELMODE_ALL_RANGE) {
        if (actorId + NPC_SHOT_ID <= AI360_PEPPY + NPC_SHOT_ID) {
            AUDIO_PLAY_SFX(NA_SE_ARWING_SHOT_F, shot->sfxSource, 4);
        } else {
            AUDIO_PLAY_SFX(NA_SE_EN_SHOT_0, shot->sfxSource, 4);
        }
    } else if ((actorId < ARRAY_COUNT(gActors)) && (gActors[actorId].obj.id == OBJ_ACTOR_EVENT) &&
               (gActors[actorId].iwork[12] >= TEAM_ID_FALCO)) {
        AUDIO_PLAY_SFX(NA_SE_ARWING_SHOT_F, shot->sfxSource, 4);
    } else if (actorId + NPC_SHOT_ID == CS_SHOT_ID + NPC_SHOT_ID) {
        shot->sourceId = CS_SHOT_ID;
        AUDIO_PLAY_SFX(NA_SE_GREATFOX_SHOT_DEMO, shot->sfxSource, 0);
    } else {
        AUDIO_PLAY_SFX(NA_SE_EN_SHOT_0, shot->sfxSource, 4);
    }
}

void Actor_SpawnPlayerLaser(s32 actorId, f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 xRot, f32 yRot,
                            f32 zRot) {
    s32 i;

    for (i = 0; i < 10; i++) {
        if (gPlayerShots[i].obj.status == SHOT_FREE) {
            Actor_SetupPlayerShot(PLAYERSHOT_TWIN_LASER, &gPlayerShots[i], actorId, xPos, yPos, zPos, xVel, yVel, zVel,
                                  xRot, yRot, zRot);
            break;
        }
    }
}

void Actor_SpawnGreatFoxLaser(s32 actorId, f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 xRot,
                              f32 yRot, f32 zRot) {
    s32 i;

    for (i = 0; i < 10; i++) {
        if (gPlayerShots[i].obj.status == SHOT_FREE) {
            Actor_SetupPlayerShot(PLAYERSHOT_GFOX_LASER, &gPlayerShots[i], actorId, xPos, yPos, zPos, xVel, yVel, zVel,
                                  xRot, yRot, zRot);
            break;
        }
    }
}

void ActorEvent_SetupEffect347(Effect* effect, f32 xPos, f32 yPos, f32 zPos, f32 scale1) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = OBJ_EFFECT_347;

    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;

    effect->scale1 = scale1;
    effect->unk_44 = 100;
    Object_SetInfo(&effect->info, effect->obj.id);
    Effect_SpawnTimedSfxAtPos(&effect->obj.pos, NA_SE_EN_EXPLOSION_M);
}

void ActorEvent_SpawnEffect347(f32 xPos, f32 yPos, f32 zPos, f32 scale1) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            ActorEvent_SetupEffect347(&gEffects[i], xPos, yPos, zPos, scale1);
            break;
        }
    }
}

void ActorEvent_SetupEffect394(Effect* effect, f32 xPos, f32 yPos, f32 zPos, f32 scale1) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = OBJ_EFFECT_394;

    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;

    effect->scale1 = scale1;
    effect->unk_44 = 100;
    effect->unk_78 = 102;
    effect->unk_7A = 18;
    Object_SetInfo(&effect->info, effect->obj.id);
    effect->info.damage = 40;
    Effect_SpawnTimedSfxAtPos(&effect->obj.pos, NA_SE_EN_EXPLOSION_M);
}

void ActorEvent_SpawnEffect394(f32 xPos, f32 yPos, f32 zPos, f32 scale1) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            ActorEvent_SetupEffect394(&gEffects[i], xPos, yPos, zPos, scale1);
            break;
        }
    }
}

void ActorEvent_8006F254(ActorEvent* this) {
    Vec3f sp54;
    Vec3f sp48;

    Matrix_RotateY(gCalcMatrix, this->vwork[29].y * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, this->vwork[29].x * M_DTOR, MTXF_APPLY);
    Matrix_RotateZ(gCalcMatrix, (this->vwork[29].z + this->rot_0F4.z) * M_DTOR, MTXF_APPLY);
    Matrix_RotateY(gCalcMatrix, this->rot_0F4.y * M_DTOR, MTXF_APPLY);
    Matrix_RotateX(gCalcMatrix, this->rot_0F4.x * M_DTOR, MTXF_APPLY);

    sp54.x = 0.0f;
    sp54.y = 0.0f;
    sp54.z = gEnemyShotSpeed;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp54, &sp48);
    func_effect_8007F04C(OBJ_EFFECT_ENEMY_LASER_1, this->obj.pos.x + sp48.x, this->obj.pos.y + sp48.y,
                         this->obj.pos.z + sp48.z, this->obj.rot.x, this->obj.rot.y, this->obj.rot.z, this->vwork[29].x,
                         this->vwork[29].y, this->vwork[29].z + this->rot_0F4.z, sp48.x, sp48.y, sp48.z, 1.0f);
}

void ActorEvent_ProcessActions(ActorEvent* this) {
    s32 i;
    Vec3f sp78;
    Vec3f sp6C;
    Sprite* sprite;

    if ((gPlayer[0].state == PLAYERSTATE_ACTIVE) && (this->eventType != EVID_SARUMARINE_PERISCOPE) &&
        (this->eventType != EVID_ANDROSS_GATE) && (this->eventType != EVID_ANDROSS_GATE_2) &&
        (this->eventType != EVID_SY_ROBOT_1) && (this->eventType != EVID_SY_ROBOT_2) &&
        (this->eventType != EVID_SY_ROBOT_3)) {
        switch (this->work_048) {
            case EVACT_NONE:
                break;

            case EVACT_1: // shoot forward
                ActorEvent_8006F254(this);
                this->work_048 = EVACT_NONE;
                break;

            case EVACT_2: // shoot at player
                if (this->obj.pos.z < (gPlayer[0].trueZpos - 600.0f)) {
                    Effect_EnemyLaser(OBJ_EFFECT_ENEMY_LASER_1, this->obj.pos.x, this->obj.pos.y, this->obj.pos.z,
                                      gEnemyShotSpeed);
                }
                this->work_048 = EVACT_NONE;
                break;

            case EVACT_3: // ally shoots forward
                if (this->timer_0BE == 0) {
                    this->timer_0BE = 6;
                    sp78.x = 0.0f;
                    sp78.y = 0.0f;
                    sp78.z = 100.0f;
                    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp78, &sp6C);
                    Actor_SpawnPlayerLaser(this->index, this->obj.pos.x + (sp6C.x * 1.5),
                                           this->obj.pos.y + (sp6C.y * 1.5), this->obj.pos.z + (sp6C.z * 1.5), sp6C.x,
                                           sp6C.y, sp6C.z, this->rot_0F4.x, this->rot_0F4.y,
                                           this->vwork[29].z + this->rot_0F4.z);
                    this->timer_0C2 = 2;
                    this->work_04C--;
                    if (this->work_04C <= 0) {
                        this->work_048 = EVACT_NONE;
                    }
                }
                break;

            case EVACT_4: // shoot blue energy balls
                ActorEvent_SpawnEffect374(this->obj.pos.x, this->obj.pos.y - 20.0f, this->obj.pos.z);
                this->work_048 = EVACT_NONE;
                break;

            case EVACT_5:
                Matrix_RotateY(gCalcMatrix, this->vwork[29].y * M_DTOR, MTXF_NEW);
                Matrix_RotateX(gCalcMatrix, this->vwork[29].x * M_DTOR, MTXF_APPLY);
                Matrix_RotateZ(gCalcMatrix, (this->vwork[29].z + this->rot_0F4.z) * M_DTOR, MTXF_APPLY);
                Matrix_RotateY(gCalcMatrix, this->rot_0F4.y * M_DTOR, MTXF_APPLY);
                Matrix_RotateX(gCalcMatrix, this->rot_0F4.x * M_DTOR, MTXF_APPLY);

                sp78.x = 0.0f;
                sp78.y = 0.0f;
                sp78.z = gEnemyShotSpeed;

                Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp78, &sp6C);
                func_effect_8007F04C(OBJ_EFFECT_355, this->obj.pos.x + sp6C.x, this->obj.pos.y + sp6C.y,
                                     this->obj.pos.z + sp6C.z, this->obj.rot.x, this->obj.rot.y, this->obj.rot.z,
                                     this->vwork[29].x, this->vwork[29].y, this->vwork[29].z + this->rot_0F4.z, sp6C.x,
                                     sp6C.y, sp6C.z, 1.0f);
                this->work_048 = EVACT_NONE;
                break;

            case EVACT_6:
                if (this->obj.pos.z < (gPlayer[0].trueZpos - 600.0f)) {
                    Effect_EnemyLaser(OBJ_EFFECT_355, this->obj.pos.x, this->obj.pos.y, this->obj.pos.z,
                                      gEnemyShotSpeed);
                }
                this->work_048 = EVACT_NONE;
                break;

            case EVACT_7:
                if (this->obj.pos.z < (gPlayer[0].trueZpos - 600.0f)) {
                    Effect_EnemyLaser(OBJ_EFFECT_356, this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 60.0f);
                }
                this->work_048 = EVACT_NONE;
                break;

            case EVACT_8:
                sp6C.x = gPlayer[0].pos.x;
                sp6C.y = gPlayer[0].pos.y;
                gPlayer[0].pos.x += RAND_FLOAT_CENTERED(300.0f);
                gPlayer[0].pos.y += RAND_FLOAT_CENTERED(300.0f);
                Effect_EnemyLaser(OBJ_EFFECT_ENEMY_LASER_1, this->obj.pos.x, this->obj.pos.y, this->obj.pos.z,
                                  gEnemyShotSpeed);
                gPlayer[0].pos.x = sp6C.x;
                gPlayer[0].pos.y = sp6C.y;
                this->work_048 = EVACT_NONE;
                break;

            case EVACT_9:
                if (gCurrentLevel == LEVEL_AQUAS) {
                    ActorEvent_SpawnEffect394(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 12.0f);
                } else {
                    ActorEvent_SpawnEffect347(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 40.0f);
                }
                Object_Kill(&this->obj, this->sfxSource);
                break;

            case EVACT_10:
                if (gCurrentLevel == LEVEL_AQUAS) {
                    ActorEvent_SpawnEffect394(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 6.0f);
                } else {
                    ActorEvent_SpawnEffect347(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 15.0f);
                }
                Object_Kill(&this->obj, this->sfxSource);
                break;

            case EVACT_11:
                Effect386_Spawn1(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, this->vel.x, this->vel.y,
                                 this->vel.z, this->scale * 3.0f, 15);
                Actor_Despawn(this);
                Object_Kill(&this->obj, this->sfxSource);
                Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_EXPLOSION_M);
                break;

            case EVACT_DESPAWN:
                Actor_Despawn(this);
                Object_Kill(&this->obj, this->sfxSource);
                break;

            case EVACT_TI_DROP_MINE:
                if (this->timer_0BE > 25) {
                    Math_SmoothStepToF(&this->fwork[15], 90.0f, 0.2f, 8.0f, 0.01f);
                }
                if (this->timer_0BE < 25) {
                    Math_SmoothStepToF(&this->fwork[15], 0.0f, 0.2f, 8.0f, 0.01f);
                }
                if (this->timer_0BE == 30) {
                    ActorEvent_SpawnTIMine(this->obj.pos.x, this->obj.pos.y - 50.0f, this->obj.pos.z);
                }
                if (this->timer_0BE == 0) {
                    this->work_048 = EVACT_NONE;
                }
                break;

            case EVACT_16:
                Effect_EnemyLaser(OBJ_EFFECT_ENEMY_LASER_1, this->obj.pos.x + 190.0f, this->obj.pos.y + 90.0f,
                                  this->obj.pos.z + 220.0f, gEnemyShotSpeed);
                Effect_EnemyLaser(OBJ_EFFECT_ENEMY_LASER_1, this->obj.pos.x - 190.0f, this->obj.pos.y + 90.0f,
                                  this->obj.pos.z + 220.0f, gEnemyShotSpeed);
                this->work_048 = EVACT_NONE;
                break;

            case EVACT_17:
                if (this->obj.pos.z < (gPlayer[0].cam.eye.z - 600.0f)) {
                    func_effect_8007F20C(OBJ_EFFECT_ENEMY_LASER_1, this->obj.pos.x, this->obj.pos.y, this->obj.pos.z,
                                         gEnemyShotSpeed);
                }
                this->work_048 = EVACT_NONE;
                break;

            case EVACT_GFOX_COVER_FIRE:
                for (i = 0, sprite = gSprites; i < ARRAY_COUNT(gSprites); i++, sprite++) {
                    if ((sprite->obj.status == OBJ_ACTIVE) && (sprite->obj.id == OBJ_SPRITE_GFOX_TARGET)) {
                        f32 sp64;
                        f32 sp60;
                        f32 sp5C;
                        f32 sp58;
                        f32 sp54;

                        sprite->obj.status = OBJ_FREE;
                        sp64 = sprite->obj.pos.x - this->obj.pos.x;
                        sp60 = sprite->obj.pos.y - this->obj.pos.y;
                        sp5C = sprite->obj.pos.z - this->obj.pos.z;
                        sp54 = Math_Atan2F(sp64, sp5C);
                        sp54 = Math_RadToDeg(sp54);
                        sp58 = -Math_Atan2F(sp60, sqrtf(SQ(sp64) + SQ(sp5C)));
                        sp58 = Math_RadToDeg(sp58);
                        Matrix_RotateY(gCalcMatrix, M_DTOR * sp54, MTXF_NEW);
                        Matrix_RotateX(gCalcMatrix, M_DTOR * sp58, MTXF_APPLY);
                        sp6C.x = 0.0f;
                        sp6C.y = 0.0f;
                        sp6C.z = 50.0f;
                        Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp6C, &sp78);
                        Actor_SpawnGreatFoxLaser(CS_SHOT_ID, this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, sp78.x,
                                                 sp78.y, sp78.z, sp58, sp54, 0.0f);
                        break;
                    }
                }

                this->work_048 = EVACT_NONE;
                break;

            case EVACT_19: // projectile ring used by bee enemies
                func_effect_80083D2C(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 40.0f);
                this->work_048 = EVACT_NONE;
                break;
        }
    }
}

void ActorEvent_8006FE28(ActorEvent* this) {
    if ((fabsf(this->obj.pos.x - gPlayer[0].pos.x) < 100.0f) && (fabsf(this->obj.pos.y - gPlayer[0].pos.y) < 100.0f) &&
        (fabsf(this->obj.pos.z - gPlayer[0].trueZpos) < 50.0f)) {
        func_enmy_80067A40();
        Audio_KillSfxBySourceAndId(this->sfxSource, NA_SE_OB_WING);
        Object_Kill(&this->obj, this->sfxSource);
    }
}

void ActorEvent_8006FEEC(ActorEvent* this) {
    s32 i;

    if ((this->dmgType != DMG_NONE) && (this->health != 0)) {
        this->dmgType = DMG_NONE;
        this->timer_0C6 = 15;
        this->health -= this->damage;

        if (this->health <= 0) {
            for (i = 3; i < 11; i++) {
                Zoness_ActorDebris_Spawn(&this->vwork[i], &this->vwork[i + 11], RAND_FLOAT_CENTERED(20.0f),
                                         RAND_FLOAT(-10.0f), RAND_FLOAT(10.0f), 41, this->scale, 200, i);
            }
            this->itemDrop = DROP_NONE;
            Actor_Despawn(this);
            Object_Kill(&this->obj, this->sfxSource);
            Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_BIRD_DOWN);
            func_effect_8007D2C8(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 4.0f);
        } else {
            AUDIO_PLAY_SFX(NA_SE_EN_BIRD_DAMAGE, this->sfxSource, 4);
        }
    }
}

bool ActorEvent_800700A4(ActorEvent* this) {
    if ((this->state != EVSTATE_TEAM_RETREAT) && (this->iwork[12] >= TEAM_ID_FALCO) &&
        (this->iwork[12] <= TEAM_ID_PEPPY) && (gTeamShields[this->iwork[12]] <= 0)) {
        this->state = EVSTATE_TEAM_RETREAT;
        this->iwork[2] = 0;
        this->fwork[10] = 360.0f;
        this->fwork[11] = 20.0f;
        gTeamShields[this->iwork[12]] = 1;

        switch (this->iwork[12]) {
            case TEAM_ID_FALCO:
                Radio_PlayMessage(gMsg_ID_20220, RCID_FALCO);
                break;
            case TEAM_ID_SLIPPY:
                Radio_PlayMessage(gMsg_ID_20222, RCID_SLIPPY);
                break;
            case TEAM_ID_PEPPY:
                Radio_PlayMessage(gMsg_ID_20221, RCID_PEPPY);
                break;
        }
        gTeamShields[this->iwork[12]] = -1;
        gTeamDamage[this->iwork[12]] = 0;
        this->timer_0C2 = 5000;
        this->dmgType = DMG_NONE;
        return true;
    }
    return false;
}

void ActorEvent_800701E0(ActorEvent* this) {
    Vec3f sp3C;
    f32 chance;
    f32 temp_fv1;

    if (ActorEvent_800700A4(this)) {
        return;
    }
    if ((this->dmgType != DMG_NONE) && (this->eventType == EVID_ME_FLIP_BOT) && (this->dmgPart == 0)) {
        this->dmgType = DMG_NONE;
    }

    if ((this->dmgType != DMG_NONE) && (this->eventType == EVID_AQ_OYSTER) && (this->timer_0C2 >= 2)) {
        this->dmgType = DMG_NONE;
    }

    if ((this->dmgType != DMG_NONE) &&
        (((this->eventType == EVID_ME_ROCK_GULL) && (this->dmgPart == 2)) || (this->eventType != EVID_ME_ROCK_GULL))) {
        if (this->iwork[12] >= TEAM_ID_KATT) {
            this->damage = 0;
        }

        if ((this->iwork[12] >= TEAM_ID_FALCO) && (this->iwork[12] <= TEAM_ID_PEPPY)) {
            gTeamShields[this->iwork[12]] -= this->damage;
        } else if ((this->eventType == EVID_AQ_OYSTER) && ((this->damage == 30) || (this->damage == 31))) {
            this->health = 0;
        } else {
            this->health -= this->damage;
        }

        if (this->health <= 0) {
            if (this->eventType == EVID_KILLER_BEE) {
                BonusText_Display(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 3);
                if (1) {}
                gHitCount += 4;
                D_ctx_80177850 = 15;
            }

            if (this->eventType != EVID_AQ_OYSTER) {
                if ((this->eventType == EVID_FIREBIRD) && (gCurrentLevel == LEVEL_SOLAR)) {
                    AUDIO_PLAY_SFX(NA_SE_EN_BIRD_DOWN, this->sfxSource, 4);
                } else {
                    AUDIO_PLAY_SFX(NA_SE_EN_CRASH_DOWN, this->sfxSource, 4);
                }

                this->obj.status = OBJ_DYING;
                chance = 0.7f;

                if (gLevelType == LEVELTYPE_SPACE) {
                    chance = 0.3f;
                }

                if (((Rand_ZeroOne() < chance) || (this->iwork[12] != 0)) && (this->info.unk_14 == 0) &&
                    (this->eventType != EVID_ME_METEOR_1) && (this->eventType != EVID_ME_METEOR_2) &&
                    (this->eventType != EVID_ME_METEOR_4) && (this->damage <= 30) &&
                    (this->eventType != EVID_ME_METEOR_5) && (this->eventType != EVID_ME_ROCK_GULL) &&
                    (this->eventType != EVID_SY_SHIP_WINDOWS) && (this->eventType != EVID_SY_LASER_TURRET)) {
                    func_effect_8007D2C8(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, this->scale * 4.0f);
                    this->dmgType = DMG_NONE;
                }

                this->timer_0C2 = 10;
                this->timer_0BE = 0;
                this->work_046 = 255;
                this->work_048 = 900;
                this->drawShadow = true;

                if (gLevelType == LEVELTYPE_PLANET) {
                    this->work_04C = RAND_INT(2.9f);
                    if (this->eventType == EVID_ME_SLIPPY) {
                        this->work_04C = 1;
                        if (this->obj.pos.x < this->hitPos.x) {
                            Play_SpawnDebris(1, this->obj.pos.x + 20.0f, this->obj.pos.y, this->obj.pos.z);
                            this->fwork[17] = 777.0f;
                        } else {
                            Play_SpawnDebris(0, this->obj.pos.x - 20.0f, this->obj.pos.y, this->obj.pos.z);
                            this->fwork[18] = 777.0f;
                        }
                    }
                    this->timer_0BC = 300;

                    if (gLevelMode != LEVELMODE_ALL_RANGE) {
                        this->vel.x *= 0.5f;
                        this->vel.y = RAND_FLOAT(5.0f);
                        if (this->vel.z < 0.0f) {
                            this->vel.z = this->vel.z;
                        } else {
                            this->vel.z = this->vel.z * 0.3f;
                        }
                        if (((this->obj.pos.z + gPathProgress) > -3000.0f) && (this->vel.z > 0.0f)) {
                            this->vel.z = RAND_FLOAT(-10.0f);
                        }
                    }

                    if (this->eventType == EVID_MA_RAILROAD_CART) {
                        this->work_04C = 999;
                    }
                } else {
                    switch (this->eventType) {
                        case EVID_ME_METEOR_1:
                            func_enmy_800654E4(&this->obj);
                            break;

                        case EVID_ME_METEOR_4:
                            Meteo_Effect346_Spawn(this);
                            break;

                        case EVID_SX_LASER:
                            this->obj.pos.y -= this->vel.y;
                            this->obj.status = OBJ_ACTIVE;
                            func_effect_8007D0E0(this->obj.pos.x - this->vel.x, this->obj.pos.y + 30.0f,
                                                 this->obj.pos.z - this->vel.z, this->scale * 5.0f);
                            this->dmgType = DMG_NONE;
                            this->timer_0C2 = 10000;
                            this->info.targetOffset = 0.0f;
                            gHitCount += this->info.bonus;
                            D_ctx_80177850 = 15;
                            break;

                        default:
                            this->timer_0BC = 35;
                            this->work_04C = 2;
                            this->vel.y = RAND_FLOAT_CENTERED(20.0f);
                            this->vel.x = RAND_FLOAT_CENTERED(20.0f);
                            this->vel.z = 0.0f;
                            break;
                    }
                }
            }

            if (this->eventType == EVID_MA_LASER_TURRET) {
                AUDIO_PLAY_SFX(NA_SE_OB_SMOKE, this->sfxSource, 0);
                this->dmgType = DMG_BEAM;
                Effect_Effect387_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 3.0f, 60);
            }
        } else {
            this->timer_0C6 = 20;
            if ((this->eventType == EVID_FIREBIRD) && (gCurrentLevel == LEVEL_SOLAR)) {
                AUDIO_PLAY_SFX(NA_SE_EN_BIRD_DAMAGE, this->sfxSource, 4);
            } else if (this->health < 20) {
                AUDIO_PLAY_SFX(NA_SE_EN_KNOCK_DOWN, this->sfxSource, 4);
            } else {
                AUDIO_PLAY_SFX(NA_SE_EN_DAMAGE_S, this->sfxSource, 4);
            }

            if ((this->eventType != EVID_ME_METEOR_1) && (this->eventType != EVID_ME_METEOR_4) &&
                (this->eventType != EVID_AQ_OYSTER)) {
                func_effect_8007D10C(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, this->scale * 1.5f);
            }

            if (((gLevelMode == LEVELMODE_ALL_RANGE) || (gLevelMode == LEVELMODE_TURRET)) &&
                (this->eventType != EVID_A6_NINJIN_MISSILE) && (this->eventType != EVID_VENOM_FIGHTER_3)) {
                this->fwork[13] = 20.0f;
                if (this->obj.pos.x < this->hitPos.x) {
                    this->fwork[13] *= -1.0f;
                }
            }

            if (this->dmgSource == TEAM_ID_FOX + 1) {
                switch (this->iwork[12]) {
                    case TEAM_ID_FALCO:
                        if (this->dmgType == DMG_COLLISION) {
                            ActorEvent_SetMessage(gMsg_ID_20210, RCID_FALCO);
                        } else {
                            ActorEvent_SetMessage(gMsg_ID_20060, RCID_FALCO);
                        }
                        break;

                    case TEAM_ID_PEPPY:
                        if (this->dmgType == DMG_COLLISION) {
                            ActorEvent_SetMessage(gMsg_ID_20200, RCID_PEPPY);
                        } else {
                            ActorEvent_SetMessage(gMsg_ID_20070, RCID_PEPPY);
                        }
                        break;

                    case TEAM_ID_SLIPPY:
                        if (this->dmgType == DMG_COLLISION) {
                            ActorEvent_SetMessage(gMsg_ID_20190, RCID_SLIPPY);
                        } else {
                            ActorEvent_SetMessage(gMsg_ID_20080, RCID_SLIPPY);
                        }
                        break;

                    case TEAM_ID_KATT:
                        ActorEvent_SetMessage(gMsg_ID_20084, RCID_KATT);
                        break;

                    case TEAM_ID_BILL:
                        ActorEvent_SetMessage(gMsg_ID_20085, RCID_BILL);
                        break;
                }
            }
            this->dmgType = DMG_NONE;
        }
    }
    if ((this->iwork[12] == 0) && (this->iwork[13] == 0) && (this->info.unk_16 != 2) &&
        (gLevelType == LEVELTYPE_SPACE)) {
        sp3C.x = this->vel.x;
        sp3C.y = this->vel.y;
        sp3C.z = this->vel.z;

        if ((Object_CheckCollision(this->index, &this->obj.pos, &sp3C, 0) != 0) ||
            (this->obj.pos.y < (gGroundHeight + 20.0f))) {
            this->obj.status = OBJ_DYING;
            this->obj.pos.z -= this->vel.z;
            this->dmgType = DMG_BEAM;
            if (this->eventType == EVID_ME_METEOR_1) {
                this->obj.id = OBJ_ACTOR_ME_METEOR_2;
                func_enmy_800654E4(&this->obj);
            }

            if (this->eventType == EVID_ME_METEOR_4) {
                Meteo_Effect346_Spawn(this);
            }
        }
    }
}

void ActorEvent_80070BA8(ActorEvent* this) {
    if (this->dmgType != DMG_NONE) {
        this->dmgType = DMG_NONE;
        if ((this->eventType != EVID_ZERAM_CLASS_CRUISER) ||
            ((this->eventType == EVID_ZERAM_CLASS_CRUISER) && (this->dmgPart == 0))) {
            this->timer_0C6 = 10;
            Effect_Effect390_Spawn(this->hitPos.x, this->hitPos.y, this->hitPos.z, this->vel.x, this->vel.y,
                                   this->vel.z, 0.2f, 10);
            this->health -= this->damage;
            AUDIO_PLAY_SFX(NA_SE_EN_SPARK_DAMAGE_M, this->sfxSource, 4);
            if (this->health <= 0) {
                BonusText_Display(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, this->info.bonus);
                gHitCount += this->info.bonus + 1;
                D_ctx_80177850 = 15;
            }
        } else {
            AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
        }
    }
}

void ActorEvent_TriggerBranch(ActorEvent* this) {
    if (this->iwork[3] < EV_CHANGE_AI) {
        this->aiIndex = this->iwork[3] * 2;
        this->iwork[0] = 0;
        this->iwork[2] = 0;
        ActorEvent_ProcessScript(this);
    } else {
        this->aiType = this->iwork[3] - EV_CHANGE_AI;
        this->aiIndex = 0;
        this->iwork[0] = 0;
        this->iwork[2] = 0;
        ActorEvent_ProcessScript(this);
    }
}

void ActorEvent_ProcessTriggers(ActorEvent* this) {
    s32 i;
    s32 teamAliveCount = 0;
    s32 ringRequirement;
    Actor* otherActor;

    for (i = TEAM_ID_FALCO; i <= TEAM_ID_PEPPY; i++) {
        if (gTeamShields[i] > 0) {
            teamAliveCount++;
        }
    }

    if (this->iwork[2] >= EVC_CLOSE_Z) {
        if (fabsf(this->obj.pos.z - gPlayer[0].trueZpos) <= ((this->iwork[2] - EVC_CLOSE_Z) * 100.0f)) {
            ActorEvent_TriggerBranch(this);
        }
        return;
    }

    switch (this->iwork[2]) {
        case EVC_NONE:
            break;

        case EVC_NO_TARGET:
            if ((gActors[this->iwork[1]].obj.status != OBJ_ACTIVE) || (gActors[this->iwork[1]].health <= 0) ||
                (this->iwork[10] != gActors[this->iwork[1]].aiType)) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_TEAM_COUNT_3:
            if (teamAliveCount == 3) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_TEAM_COUNT_2:
            if (teamAliveCount == 2) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_TEAM_COUNT_1:
            if (teamAliveCount == 1) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_TEAM_COUNT_0:
            if (teamAliveCount == 0) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_FALCO_ACTIVE:
            if (gTeamShields[TEAM_ID_FALCO] > 0) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_PEPPY_ACTIVE:
            if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_SLIPPY_ACTIVE:
            if (gTeamShields[TEAM_ID_SLIPPY] > 0) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_CLOSE_LEFT_100:
            if (((this->obj.pos.x - gPlayer[0].pos.x) <= 100.0f) && ((this->obj.pos.x - gPlayer[0].pos.x) >= 0.0f)) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_CLOSE_LEFT_400:
            if (((this->obj.pos.x - gPlayer[0].pos.x) <= 400.0f) && ((this->obj.pos.x - gPlayer[0].pos.x) >= 0.0f)) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_CLOSE_LEFT_700:
            if (((this->obj.pos.x - gPlayer[0].pos.x) <= 700.0f) && ((this->obj.pos.x - gPlayer[0].pos.x) >= 0.0f)) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_CLOSE_LEFT_200:
            if (((this->obj.pos.x - gPlayer[0].pos.x) <= 200.0f) && ((this->obj.pos.x - gPlayer[0].pos.x) >= 0.0f)) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_CLOSE_RIGHT_100:
            if (((this->obj.pos.x - gPlayer[0].pos.x) >= -100.0f) && ((this->obj.pos.x - gPlayer[0].pos.x) <= 0.0f)) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_CLOSE_RIGHT_400:
            if (((this->obj.pos.x - gPlayer[0].pos.x) >= -400.0f) && ((this->obj.pos.x - gPlayer[0].pos.x) <= 0.0f)) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_CLOSE_RIGHT_700:
            if (((this->obj.pos.x - gPlayer[0].pos.x) >= -700.0f) && ((this->obj.pos.x - gPlayer[0].pos.x) <= 0.0f)) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_CLOSE_RIGHT_200:
            if (((this->obj.pos.x - gPlayer[0].pos.x) >= -200.0f) && ((this->obj.pos.x - gPlayer[0].pos.x) <= 0.0f)) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_CLOSE_ABOVE_100:
            if (((this->obj.pos.y - gPlayer[0].pos.y) <= 100.0f) && ((this->obj.pos.y - gPlayer[0].pos.y) >= 0.0f)) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_CLOSE_ABOVE_400:
            if (((this->obj.pos.y - gPlayer[0].pos.y) <= 400.0f) && ((this->obj.pos.y - gPlayer[0].pos.y) >= 0.0f)) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_CLOSE_ABOVE_700:
            if (((this->obj.pos.y - gPlayer[0].pos.y) <= 700.0f) && ((this->obj.pos.y - gPlayer[0].pos.y) >= 0.0f)) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_CLOSE_ABOVE_200:
            if (((this->obj.pos.y - gPlayer[0].pos.y) <= 200.0f) && ((this->obj.pos.y - gPlayer[0].pos.y) >= 0.0f)) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_CLOSE_BELOW_100:
            if (((this->obj.pos.y - gPlayer[0].pos.y) >= -100.0f) && ((this->obj.pos.y - gPlayer[0].pos.y) <= 0.0f)) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_CLOSE_BELOW_400:
            if (((this->obj.pos.y - gPlayer[0].pos.y) >= -400.0f) && ((this->obj.pos.y - gPlayer[0].pos.y) <= 0.0f)) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_CLOSE_BELOW_700:
            if (((this->obj.pos.y - gPlayer[0].pos.y) >= -700.0f) && ((this->obj.pos.y - gPlayer[0].pos.y) <= 0.0f)) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_CLOSE_BELOW_200:
            if (((this->obj.pos.y - gPlayer[0].pos.y) >= -200.0f) && ((this->obj.pos.y - gPlayer[0].pos.y) <= 0.0f)) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_HEALTH_100p:
            if (gPlayer[0].shields >= Play_GetMaxShields()) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_HEALTH_75p:
            if (gPlayer[0].shields >= (Play_GetMaxShields() * 3 / 4)) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_HEALTH_50p:
            if (gPlayer[0].shields >= (Play_GetMaxShields() / 2)) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_HEALTH_25p:
            if (gPlayer[0].shields >= (Play_GetMaxShields() / 4)) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_HEALTH_0p:
            if (gPlayer[0].shields == 0) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_UNK270_5PLUS:
            if (gPlayer[0].unk_270 >= 5) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_UNK270_NONZERO:
            if (gPlayer[0].unk_270 != 0) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_UNK270_ZERO:
            if (gPlayer[0].unk_270 == 0) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_UNK250_GREATER_168:
            if (gPlayer[0].unk_250 >= 16.8f) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_UNK250_LESS_84:
            if (gPlayer[0].unk_250 <= 8.4f) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_SINGLE_LASER:
            if (gPlayer[0].arwing.laserGunsYpos > -8.0f) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_TWIN_LASER:
            if ((gPlayer[0].arwing.laserGunsYpos < -8.0f) && (gLaserStrength[0] == LASERS_TWIN)) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_HYPER_LASER:
            if ((gPlayer[0].arwing.laserGunsYpos < -8.0f) && (gLaserStrength[0] == LASERS_HYPER)) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_UNK3_LASER:
            if ((gPlayer[0].arwing.laserGunsYpos < -8.0f) && (gLaserStrength[0] == LASERS_UNK_3)) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_SHOT_CLOSE_150:
            for (i = 0; i < ARRAY_COUNT(gPlayerShots); i++) {
                if ((gPlayerShots[i].obj.status == SHOT_ACTIVE) &&
                    (fabsf(this->obj.pos.x - gPlayerShots[i].obj.pos.x) < 150.0f) &&
                    (fabsf(this->obj.pos.y - gPlayerShots[i].obj.pos.y) < 150.0f) &&
                    (fabsf(this->obj.pos.z - gPlayerShots[i].obj.pos.z) < 150.0f)) {
                    ActorEvent_TriggerBranch(this);
                    break;
                }
            }
            break;

        case EVC_SHOT_CLOSE_300:
            for (i = 0; i < ARRAY_COUNT(gPlayerShots); i++) {
                if ((gPlayerShots[i].obj.status == SHOT_ACTIVE) &&
                    (fabsf(this->obj.pos.x - gPlayerShots[i].obj.pos.x) < 300.0f) &&
                    (fabsf(this->obj.pos.y - gPlayerShots[i].obj.pos.y) < 300.0f) &&
                    (fabsf(this->obj.pos.z - gPlayerShots[i].obj.pos.z) < 300.0f)) {
                    ActorEvent_TriggerBranch(this);
                    break;
                }
            }
            break;

        case EVC_NO_LEADER:
            if ((gActors[this->iwork[9]].obj.status != OBJ_ACTIVE) ||
                ((gActors[this->iwork[9]].scale < 0.0f) && (this->health <= 0))) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_NO_FOLLOWER:
            for (i = 0; i < ARRAY_COUNT(gActors); i++) {
                if ((gActors[i].obj.status == OBJ_ACTIVE) && (gActors[i].obj.id == OBJ_ACTOR_EVENT) &&
                    (gActors[i].iwork[13] != 0) && (i != this->index) && (this->index == gActors[i].iwork[9])) {
                    return;
                }
            }
            ActorEvent_TriggerBranch(this);
            break;

        case EVC_HAS_FOLLOWER:
            for (i = 0; i < ARRAY_COUNT(gActors); i++) {
                if ((gActors[i].obj.status == OBJ_ACTIVE) && (gActors[i].obj.id == OBJ_ACTOR_EVENT) &&
                    (gActors[i].iwork[13] != 0) && (i != this->index) && (this->index == gActors[i].iwork[9])) {
                    ActorEvent_TriggerBranch(this);
                    break;
                }
            }
            break;

        case EVC_TOOK_DAMAGE:
            if (this->dmgType != DMG_NONE) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_PASSED_ALL_RINGS:
            ringRequirement = 7;
            switch (gCurrentLevel) {
                case LEVEL_CORNERIA:
                    break;
                case LEVEL_SECTOR_X:
                    ringRequirement = 4;
                    break;
                case LEVEL_TITANIA:
                    ringRequirement = 9;
                    break;
            }

            // Abort if Falco is dead or the requirement is not met.
            if (((gCurrentLevel == LEVEL_CORNERIA) && (gTeamShields[TEAM_ID_FALCO] <= 0)) ||
                (gRingPassCount < ringRequirement)) {
                break;
            }

            ActorEvent_TriggerBranch(this);
            break;

        case EVC_ATTACK_GROUP_CLEARED:
            for (i = 0, otherActor = &gActors[0]; i < ARRAY_COUNT(gActors); i++, otherActor++) {
                if (((otherActor->obj.status == OBJ_DYING) || (otherActor->obj.status == OBJ_FREE)) &&
                    (otherActor->iwork[15] == this->iwork[15]) && (otherActor->iwork[16] != 0)) {
                    ActorEvent_TriggerBranch(this);
                }
            }
            break;

        case EVC_PRESS_CRIGHT:
            if (gControllerPress[gMainController].button & R_CBUTTONS) {
                Audio_SetUnkVoiceParam(0);
                gCallVoiceParam = 0;
                gCallTimer = 0;
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_WING_BROKEN:
            if ((gPlayer[0].arwing.rightWingState <= WINGSTATE_BROKEN) ||
                (gPlayer[0].arwing.leftWingState <= WINGSTATE_BROKEN)) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_ME_CLEAR:
            if (gLeveLClearStatus[LEVEL_METEO] != 0) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_FO_CLEAR:
            if (gLeveLClearStatus[LEVEL_FORTUNA] != 0) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_SX_CLEAR:
            if (gLeveLClearStatus[LEVEL_SECTOR_X] != 0) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_TI_CLEAR:
            if (gLeveLClearStatus[LEVEL_TITANIA] != 0) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_BO_CLEAR:
            if (gLeveLClearStatus[LEVEL_BOLSE] != 0) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_SY_CLEAR:
            if (gLeveLClearStatus[LEVEL_SECTOR_Y] != 0) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_KA_CLEAR:
            if (gLeveLClearStatus[LEVEL_KATINA] != 0) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_SO_CLEAR:
            if (gLeveLClearStatus[LEVEL_SOLAR] != 0) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_MA_CLEAR:
            if (gLeveLClearStatus[LEVEL_MACBETH] != 0) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_AQ_CLEAR:
            if (gLeveLClearStatus[LEVEL_AQUAS] != 0) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_ZO_CLEAR:
            if (gLeveLClearStatus[LEVEL_ZONESS] != 0) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_SZ_CLEAR:
            if (gLeveLClearStatus[LEVEL_SECTOR_Z] != 0) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_A6_CLEAR:
            if (gLeveLClearStatus[LEVEL_AREA_6] != 0) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_NOT_CHASED:
            if (D_enmy_Timer_80161670[this->iwork[12]] == 0) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_CHASED:
            if (D_enmy_Timer_80161670[this->iwork[12]] != 0) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_MISSED_SEARCHLIGHT:
            if (gMissedZoSearchlight) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_30_HITS:
            if (gHitCount >= 30) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_80_HITS:
            if (gHitCount >= 80) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_EXPERT_MODE:
            if (gExpertMode) {
                ActorEvent_TriggerBranch(this);
            }
            break;
    }
}

// could be in-function, but probably weren't
Vec3f D_800D0DD4[56] = {
    { 158.0f, 256.0f, 1513.0f },   { 384.0f, 42.0f, 1187.0f },   { 284.0f, 129.0f, 769.0f },
    { 482.0f, 19.0f, 769.0f },     { 386.0f, 105.0f, 253.0f },   { 221.0f, 209.0f, 33.0f },
    { 78.0f, 263.0f, 637.0f },     { 78.0f, 263.0f, 76.0f },     { 18.0f, 263.0f, 1683.0f },
    { 106.0f, 98.0f, 1655.0f },    { 196.0f, -11.0f, 1365.0f },  { 104.0f, -175.0f, 1236.0f },
    { 313.0f, -175.0f, 972.0f },   { 456.0f, -132.0f, 695.0f },  { 157.0f, -360.0f, 904.0f },
    { 186.0f, -263.0f, 354.0f },   { 186.0f, -130.0f, 307.0f },  { 692.0f, 16.0f, 190.0f },
    { 337.0f, 120.0f, -297.0f },   { 337.0f, 373.0f, -242.0f },  { 240.0f, 359.0f, -611.0f },
    { 504.0f, 447.0f, -611.0f },   { 656.0f, 506.0f, -829.0f },  { 73.0f, 337.0f, -426.0f },
    { 73.0f, 548.0f, -411.0f },    { 65.0f, 391.0f, -1237.0f },  { 193.0f, 250.0f, -1026.0f },
    { 292.0f, 271.0f, -587.0f },   { -158.0f, 256.0f, 1513.0f }, { -384.0f, 42.0f, 1187.0f },
    { -284.0f, 129.0f, 769.0f },   { -482.0f, 19.0f, 769.0f },   { -386.0f, 105.0f, 253.0f },
    { -221.0f, 209.0f, 33.0f },    { -78.0f, 263.0f, 637.0f },   { -78.0f, 263.0f, 76.0f },
    { -18.0f, 263.0f, 1683.0f },   { -106.0f, 98.0f, 1655.0f },  { -196.0f, -11.0f, 1365.0f },
    { -104.0f, -175.0f, 1236.0f }, { -313.0f, -175.0f, 972.0f }, { -456.0f, -132.0f, 695.0f },
    { -157.0f, -360.0f, 904.0f },  { -186.0f, -263.0f, 354.0f }, { -186.0f, -130.0f, 307.0f },
    { -692.0f, 16.0f, 190.0f },    { -337.0f, 120.0f, -297.0f }, { -337.0f, 373.0f, -242.0f },
    { -240.0f, 359.0f, -611.0f },  { -504.0f, 447.0f, -611.0f }, { -656.0f, 506.0f, -829.0f },
    { -73.0f, 337.0f, -426.0f },   { -73.0f, 548.0f, -411.0f },  { -65.0f, 391.0f, -1237.0f },
    { -193.0f, 250.0f, -1026.0f }, { -292.0f, 271.0f, -587.0f },
};
Vec3f D_800D1074[24] = {
    { 100.0f, 55.0f, 450.0f },     { 117.0f, 57.0f, 738.0f },    { 14.0f, 31.0f, 894.0f },
    { 204.0f, 0.0f, -72.0f },      { 204.0f, 33.0f, -253.0f },   { 344.0f, 0.0f, -295.0f },
    { 344.0f, -51.0f, -457.0f },   { 87.0f, 124.0f, -699.0f },   { 169.0f, -40.0f, -564.0f },
    { 113.0f, -147.0f, -367.0f },  { 112.0f, -146.0f, -13.0f },  { 69.0f, -118.0f, 158.0f },
    { -100.0f, 55.0f, 450.0f },    { -117.0f, 57.0f, 738.0f },   { -14.0f, 31.0f, 894.0f },
    { -204.0f, 0.0f, -72.0f },     { -204.0f, 33.0f, -253.0f },  { -344.0f, 0.0f, -295.0f },
    { -344.0f, -51.0f, -457.0f },  { -87.0f, 124.0f, -699.0f },  { -169.0f, -40.0f, -564.0f },
    { -113.0f, -147.0f, -367.0f }, { -112.0f, -146.0f, -13.0f }, { -69.0f, -118.0f, 158.0f },
};
Vec3f D_800D1194[21] = {
    { 764.0f, 13.0f, 71.0f },    { 390.0f, 13.0f, 67.0f },    { 390.0f, 332.0f, 67.0f },   { 504.0f, 508.0f, 67.0f },
    { 251.0f, 508.0f, 67.0f },   { -35.0f, 341.0f, 67.0f },   { -35.0f, 673.0f, 67.0f },   { -354.0f, 594.0f, 67.0f },
    { -354.0f, 273.0f, 67.0f },  { -695.0f, 97.0f, 67.0f },   { -378.0f, -57.0f, 67.0f },  { -378.0f, -266.0f, 67.0f },
    { -475.0f, -518.0f, 67.0f }, { -255.0f, -518.0f, 67.0f }, { -112.0f, -375.0f, 67.0f }, { -46.0f, -628.0f, 67.0f },
    { -97.0f, -375.0f, 67.0f },  { 207.0f, -639.0f, 67.0f },  { 437.0f, -474.0f, 67.0f },  { 591.0f, -210.0f, 67.0f },
    { 453.0f, 420.0f, 67.0f },
};

void ActorEvent_80071DC0(ActorEvent* this) {
    s32 rInd;
    Vec3f sp38;

    Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);
    Matrix_RotateZ(gCalcMatrix, this->obj.rot.z * M_DTOR, MTXF_APPLY);

    if (this->eventType == EVID_A6_HARLOCK_FRIGATE) {
        rInd = RAND_FLOAT(ARRAY_COUNT(D_800D1074) - 1.1f); // off by 1 error?
        Matrix_MultVec3fNoTranslate(gCalcMatrix, &D_800D1074[rInd], &sp38);
    }

    if (this->eventType == EVID_ZERAM_CLASS_CRUISER) {
        rInd = RAND_FLOAT(ARRAY_COUNT(D_800D0DD4) - 0.1f);
        Matrix_MultVec3fNoTranslate(gCalcMatrix, &D_800D0DD4[rInd], &sp38);
    }

    if (this->eventType == EVID_A6_UMBRA_STATION) {
        rInd = RAND_FLOAT(ARRAY_COUNT(D_800D1194) - 0.1f);
        Matrix_MultVec3fNoTranslate(gCalcMatrix, &D_800D1194[rInd], &sp38);
    }

    if (((gGameFrameCount % 2) == 0)) {
        Effect_Effect390_Spawn(this->obj.pos.x + sp38.x, this->obj.pos.y + sp38.y, this->obj.pos.z + sp38.z,
                               this->vel.x, this->vel.y, this->vel.z, 0.3f, 20);
    }

    if (((gGameFrameCount % 8) == 0)) {
        Effect386_Spawn1(this->obj.pos.x + sp38.x, this->obj.pos.y + sp38.y, this->obj.pos.z + sp38.z, this->vel.x,
                         this->vel.y, this->vel.z, 10.0f, 9);
    }

    if (((gGameFrameCount % 16) == 0)) {
        AUDIO_PLAY_SFX(NA_SE_EN_EXPLOSION_M, this->sfxSource, 4);
    }

    this->vel.y -= 0.1f;
    this->vel.z = 0.0f;
    this->obj.rot.x += 0.2f;
    this->obj.rot.z += 0.3f;

    if (((gGameFrameCount % 8) == 0) && (Rand_ZeroOne() < 0.5f)) {
        this->timer_0C6 = 4;
    }
}

void ActorEvent_800720E8(ActorEvent* this) {
    switch (this->work_046) {
        case 0:
            if (this->dmgType != DMG_NONE) {
                if (this->dmgType == DMG_EXPLOSION) {
                    this->damage = 3;
                }

                if ((this->dmgSource >= NPC_SHOT_ID + 1) &&
                    (gActors[this->dmgSource - NPC_SHOT_ID - 1].eventType == EVID_BILL)) {
                    this->damage = 20;
                }

                this->health -= this->damage;
                this->fwork[16] += 0.2f;
                this->timer_0BC = 5;

                if (this->timer_0BE < 20) {
                    this->timer_0BE += 5;
                }

                if (this->health <= 0) {
                    this->work_046 = 1;
                    this->info.hitbox = SEGMENTED_TO_VIRTUAL(D_SX_6032408);
                    AUDIO_PLAY_SFX(NA_SE_OB_GATE_OPEN, this->sfxSource, 0);
                } else {
                    AUDIO_PLAY_SFX(NA_SE_EN_DAMAGE_S, this->sfxSource, 0);
                }
                this->dmgType = DMG_NONE;
            }
            break;

        case 1:
        case 2:
            Math_SmoothStepToF(&this->fwork[16], 130.0f, 0.2f, 8.0f, 0.001f);
            if (this->fwork[16] > 45.0f) {
                Math_SmoothStepToF(&this->fwork[15], 90.0f, 0.2f, 10.0f, 0.001f);
            }
            break;
    }
}

void ActorEvent_SetupEffect365(Effect* effect, f32 xPos, f32 yPos, f32 zPos, f32 yRot) {
    Vec3f sp2C;
    Vec3f sp20;

    Effect_Initialize(effect);
    Matrix_RotateY(gCalcMatrix, M_DTOR * yRot, MTXF_NEW);
    sp2C.x = 0.0f;
    sp2C.y = 0.0f;
    sp2C.z = 20.0f;
    Matrix_MultVec3f(gCalcMatrix, &sp2C, &sp20);
    effect->vel.x = sp20.x;
    effect->obj.status = OBJ_INIT;
    effect->obj.id = OBJ_EFFECT_365;
    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;
    effect->unk_44 = 250;
    effect->scale2 = 2.0f;
    effect->scale1 = RAND_FLOAT_CENTERED(200.0f);
    effect->obj.rot.z = RAND_FLOAT(360.0f);
    effect->unk_4C = effect->state = 1;
    Object_SetInfo(&effect->info, effect->obj.id);
}

void ActorEvent_SpawnEffect365(f32 xPos, f32 yPos, f32 zPos, f32 yRot) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            ActorEvent_SetupEffect365(&gEffects[i], xPos, yPos, zPos, yRot);
            break;
        }
    }
}

// turn for the purpose of shooting?
void ActorEvent_80072474(ActorEvent* this) {
    f32 var_fv1;

    if (this->work_048 != EVACT_NONE) {
        switch (this->work_048) {
            case EVACT_1:
                this->fwork[16] = 45.0f;
                break;
            case EVACT_2:
                this->fwork[16] = 0.0f;
                break;
            case EVACT_3:
                this->iwork[15] = 1;
                break;
            case EVACT_4:
                this->iwork[15] = 0;
                break;
        }
        this->work_048 = EVACT_NONE;
    }

    if (this->iwork[15] != 0) {
        var_fv1 = Math_RadToDeg(Math_Atan2F(gPlayer[0].pos.x - this->obj.pos.x, gPlayer[0].trueZpos - this->obj.pos.z));
    } else if (this->iwork[6] != 0) {
        var_fv1 = this->rot_0F4.y;
    } else {
        var_fv1 = 0.0f;
    }
    Math_SmoothStepToAngle(&this->obj.rot.y, var_fv1, 0.2f, 3.0f, 0.0f);
    Math_SmoothStepToAngle(&this->fwork[15], this->fwork[16], 0.5f, 8.0f, 0.0f);
}

Vec3f D_800D1290 = { 0.0f, 837.00006f, 0.0f }; // could be in-function

void ActorEvent_Update(ActorEvent* this) {
    s32 spFC;
    f32 var_fv0;
    s32 var_s0;
    f32 spF0;
    f32 spEC;
    f32 spE8;
    f32 spE4;
    f32 spE0;
    f32 spDC = 0.0f;
    f32 spD8 = 0.0f;
    f32 spD4 = 0.0f;
    s32 index;
    f32 spCC;
    f32 spC8;
    f32 spC4;
    Vec3f spB8;
    Vec3f spAC;
    Vec3f spA0;

    if ((gPlayer[0].state == PLAYERSTATE_LEVEL_COMPLETE) || gKillEventActors) {
        Object_Kill(&this->obj, this->sfxSource);
        return;
    }

    if (this->state == EVSTATE_1000) {
        this->obj.rot.y += this->fwork[15];
        this->obj.rot.x += this->fwork[16];
        if ((gGameFrameCount % 16) == 0) {
            Effect_Effect390_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, this->vel.x, this->vel.y,
                                   this->vel.z, 0.3f, 10);
        }
        return;
    }
    if (((this->eventType == EVID_ZERAM_CLASS_CRUISER) || (this->eventType == EVID_A6_HARLOCK_FRIGATE) ||
         (this->eventType == EVID_A6_UMBRA_STATION)) &&
        (this->health <= 0)) {
        ActorEvent_80071DC0(this);
        return;
    }
    if (this->eventType == EVID_300) {
        gPlayer[0].dmgType = this->index;
        this->timer_0C2 = 100;
    } else if (this->eventType >= EVID_200) {
        this->counter_04E++;

        if (this->counter_04E >= 100) {
            this->counter_04E = 0;
        }

        gMeMoraXpos[this->work_046][this->counter_04E] = this->obj.pos.x;
        gMeMoraYpos[this->work_046][this->counter_04E] = this->obj.pos.y;
        gMeMoraZpos[this->work_046][this->counter_04E] = this->obj.pos.z;
        gMeMoraXrot[this->work_046][this->counter_04E] = this->obj.rot.x;
        gMeMoraYrot[this->work_046][this->counter_04E] = this->obj.rot.y;
        gMeMoraZrot[this->work_046][this->counter_04E] = this->obj.rot.z;

        if (this->dmgType != DMG_NONE) {
            this->dmgType = DMG_NONE;
            this->timer_0C6 = 20;
            this->health -= this->damage;

            AUDIO_PLAY_SFX(NA_SE_EN_SNAKE_DAMAGE, this->sfxSource, 4);

            if (this->health <= 0) {
                this->timer_0C6 = 200;
                this->obj.status = OBJ_DYING;
                func_effect_8007D2C8(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 8.0f);
                this->obj.status = OBJ_DYING;
                this->timer_0BC = 20;
                this->obj.id = OBJ_ACTOR_ME_MORA;
            }
        }
    }

    if ((this->eventType == EVID_SX_LASER) && (this->timer_0C2 != 0)) {
        this->state = EVSTATE_READY;
    }

    switch (this->state) {
        case EVSTATE_READY:
            ActorEvent_ProcessScript(this);
            break;

        case EVSTATE_WAIT:
            if (this->timer_0BC == 0) {
                ActorEvent_ProcessScript(this);
            }
            break;

        case EVSTATE_PURSUE_PLAYER:
        case EVSTATE_FLEE_PLAYER:
        case EVSTATE_PURSUE_CAMERA:
        case EVSTATE_FLEE_CAMERA:
            spF0 = this->obj.pos.x;
            spEC = this->obj.pos.y;
            spE8 = this->obj.pos.z;

            if ((this->eventType == EVID_CRUISER_GUN) || (this->eventType == EVID_SY_LASER_TURRET)) {
                Matrix_RotateZ(gCalcMatrix, -(this->vwork[29].z + this->rot_0F4.z) * M_DTOR, MTXF_NEW);
                Matrix_RotateX(gCalcMatrix, -this->vwork[29].x * M_DTOR, MTXF_APPLY);
                Matrix_RotateY(gCalcMatrix, -this->vwork[29].y * M_DTOR, MTXF_APPLY);

                if ((this->state == EVSTATE_PURSUE_CAMERA) || (this->state == EVSTATE_FLEE_CAMERA)) {
                    spB8.x = gPlayer[0].cam.eye.x - spF0;
                    spB8.y = gPlayer[0].cam.eye.y - (spEC + 25.0f);
                    spB8.z = (gPlayer[0].cam.eye.z * 15.0f) - spE8;
                } else {
                    spB8.x = gPlayer[0].pos.x - spF0;
                    spB8.y = gPlayer[0].pos.y - (spEC + 25.0f);
                    spB8.z = gPlayer[0].pos.z + (gPlayer[0].vel.z * 15.0f) - spE8;
                }

                Matrix_MultVec3fNoTranslate(gCalcMatrix, &spB8, &spAC);

                spE0 = Math_RadToDeg(Math_Atan2F(spAC.x, spAC.z));
                spE4 = Math_RadToDeg(-Math_Atan2F(spAC.y, sqrtf(SQ(spAC.x) + SQ(spAC.z))));
                spFC = 0;

                if ((spE4 < 305.0f) && (spE4 >= 180.0f)) {
                    spE4 = 305.0f;
                    spFC++;
                }

                if ((spE4 > 30.0f) && (spE4 <= 180.0f)) {
                    spE4 = 30.0f;
                    spFC++;
                }

                this->obj.rot.x = 0.0f;

                Math_SmoothStepToAngle(&this->obj.rot.y, spE0, 0.2f, this->fwork[24], 0.001f);
                Math_SmoothStepToAngle(&this->fwork[15], spE4, 0.2f, this->fwork[24], 0.001f);

                if (((this->timer_0BC % 32) == 0) && (spFC == 0)) {
                    Matrix_RotateY(gCalcMatrix, this->vwork[29].y * M_DTOR, MTXF_NEW);
                    Matrix_RotateX(gCalcMatrix, this->vwork[29].x * M_DTOR, MTXF_APPLY);
                    Matrix_RotateZ(gCalcMatrix, (this->vwork[29].z + this->rot_0F4.z) * M_DTOR, MTXF_APPLY);

                    spB8.x = 0.0f;
                    spB8.y = 25.0f;
                    spB8.z = 0.0f;

                    Matrix_MultVec3fNoTranslate(gCalcMatrix, &spB8, &spA0);
                    Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_APPLY);
                    Matrix_RotateX(gCalcMatrix, this->fwork[15] * M_DTOR, MTXF_APPLY);

                    spB8.x = 0.0f;
                    spB8.y = 0.0f;
                    spB8.z = gEnemyShotSpeed;

                    Matrix_MultVec3fNoTranslate(gCalcMatrix, &spB8, &spAC);

                    if (this->eventType == EVID_SY_LASER_TURRET) {
                        var_fv0 = 80.0f;
                    } else {
                        var_fv0 = 0.0f;
                    }

                    func_effect_8007F04C(OBJ_EFFECT_ENEMY_LASER_1, this->obj.pos.x + spAC.x + spA0.x,
                                         this->obj.pos.y + spAC.y + spA0.y + var_fv0, this->obj.pos.z + spAC.z + spA0.z,
                                         this->fwork[15], this->obj.rot.y, this->obj.rot.z, this->vwork[29].x,
                                         this->vwork[29].y, this->vwork[29].z + this->rot_0F4.z, spAC.x, spAC.y, spAC.z,
                                         1.0f);
                    this->fwork[16] = -15.0f;
                }
            } else {
                if ((this->state == EVSTATE_PURSUE_CAMERA) || (this->state == EVSTATE_FLEE_CAMERA)) {
                    spCC = gPlayer[0].cam.eye.x;
                    spC8 = gPlayer[0].cam.eye.y;
                    spC4 = gPlayer[0].cam.eye.z;
                } else {
                    spCC = gPlayer[0].pos.x;
                    spC8 = gPlayer[0].pos.y;
                    spC4 = gPlayer[0].pos.z;
                }

                Math_SmoothStepToAngle(&this->vwork[29].z, 0.0f, 0.1f, 5.0f, 0.0001f);
                Math_SmoothStepToAngle(&this->rot_0F4.z, 0.0f, 0.1f, 5.0f, 0.0001f);

                spE0 = Math_RadToDeg(Math_Atan2F(spCC - spF0, spC4 - spE8));

                if ((this->state == EVSTATE_FLEE_PLAYER) || (this->state == EVSTATE_FLEE_CAMERA)) {
                    spE0 += 180.0f;
                    if (spE0 > 360.0f) {
                        spE0 -= 360.0f;
                    }
                }

                spE4 = Math_RadToDeg(-Math_Atan2F(spC8 - spEC, sqrtf(SQ(spCC - spF0) + SQ(spC4 - spE8))));
                spEC = Math_SmoothStepToAngle(&this->rot_0F4.y, spE0, 0.2f, this->fwork[24], 0.0001f);

                Math_SmoothStepToAngle(&this->rot_0F4.x, spE4, 0.2f, this->fwork[24], 0.0001f);

                if (this->iwork[6] != 0) {
                    var_fv0 = 330.0f;
                    if (spEC < 0.0f) {
                        var_fv0 = 30.0f;
                    }
                    Math_SmoothStepToAngle(&this->fwork[23], var_fv0, 0.1f, 5.0f, 0.01f);
                }
            }

            if (this->timer_0BC == 0) {
                ActorEvent_ProcessScript(this);
            }
            break;

        case EVSTATE_CHASE_TARGET:
            spDC = SIN_DEG((this->index * 45) + gGameFrameCount) * this->fwork[17];
            spD8 = COS_DEG((this->index * 45) + (gGameFrameCount * 2)) * this->fwork[17];
            index = this->iwork[1];
            index = gActors[index].iwork[12];
            D_enmy_Timer_80161670[index] = 5;
        /* fallthrough */
        case EVSTATE_PURSUE_TARGET:
        case EVSTATE_FLEE_TARGET:
            spF0 = this->obj.pos.x;
            spEC = this->obj.pos.y;
            spE8 = this->obj.pos.z;

            spE0 = Math_RadToDeg(Math_Atan2F(gActors[this->iwork[1]].obj.pos.x + spDC - spF0,
                                             gActors[this->iwork[1]].obj.pos.z + spD4 - spE8));
            if (this->state == EVSTATE_FLEE_PLAYER) { // bug? should be EVSTATE_FLEE_TARGET?
                spE0 += 180.0f;
                if (spE0 > 360.0f) {
                    spE0 -= 360.0f;
                }
            }

            spE4 = Math_RadToDeg(-Math_Atan2F(gActors[this->iwork[1]].obj.pos.y + spD8 - spEC,
                                              sqrtf(SQ(gActors[this->iwork[1]].obj.pos.x + spDC - spF0) +
                                                    SQ(gActors[this->iwork[1]].obj.pos.z + spD4 - spE8))));
            spEC = Math_SmoothStepToAngle(&this->rot_0F4.y, spE0, 0.2f, this->fwork[24], 0.0001f);

            Math_SmoothStepToAngle(&this->rot_0F4.x, spE4, 0.2f, this->fwork[24], 0.0001f);

            if (this->iwork[6] != 0) {
                var_fv0 = 310.0f;
                if (spEC < 0.0f) {
                    var_fv0 = 50.0f;
                }

                Math_SmoothStepToAngle(&this->fwork[23], var_fv0, 0.1f, 5.0f, 0.01f);
            }

            if (this->timer_0BC == 0) {
                ActorEvent_ProcessScript(this);
            }
            break;

        case EVSTATE_F4_PLUS_X:
            this->rot_0F4.x += this->fwork[3];
            this->fwork[2] -= this->fwork[3];
            if (this->fwork[2] <= 0.0f) {
                ActorEvent_ProcessScript(this);
            }
            break;

        case EVSTATE_F4_MINUS_X:
            this->rot_0F4.x -= this->fwork[3];
            this->fwork[2] -= this->fwork[3];
            if (this->fwork[2] <= 0.0f) {
                ActorEvent_ProcessScript(this);
            }
            break;

        case EVSTATE_F4_PLUS_Y:
            this->rot_0F4.y += this->fwork[3];
            this->fwork[2] -= this->fwork[3];
            if (this->fwork[2] <= 0.0f) {
                ActorEvent_ProcessScript(this);
            }
            break;

        case EVSTATE_F4_MINUS_Y:
            this->rot_0F4.y -= this->fwork[3];
            this->fwork[2] -= this->fwork[3];
            if (this->fwork[2] <= 0.0f) {
                ActorEvent_ProcessScript(this);
            }
            break;

        case EVSTATE_ME_AS_OPEN:
            var_s0 = 0;
            if (Math_SmoothStepToAngle(&this->obj.rot.x, 0.0f, 0.3f, 10.0f, 1.0f) == 0.0f) {
                var_s0++;
            }

            if (Math_SmoothStepToAngle(&this->obj.rot.y, 0.0f, 0.3f, 10.0f, 1.0f) == 0.0f) {
                var_s0++;
            }

            if (Math_SmoothStepToF(&this->fwork[15], 40.0f, 0.3f, 10.0f, 1.0f) == 0.0f) {
                var_s0++;
            }

            if (var_s0 == 3) {
                this->info.hitbox = LOAD_ASSET(D_ME_602F638);
                ActorEvent_ProcessScript(this);
            }
            break;

        case EVSTATE_ME_AS_CLOSE:
            if (Math_SmoothStepToF(&this->fwork[15], 0.0f, 0.3f, 10.0f, 1.0f) == 0.0f) {
                ActorEvent_ProcessScript(this);
            }
            break;

        case EVSTATE_TEAM_RETREAT:
            Math_SmoothStepToAngle(&this->rot_0F4.x, 270.0f, 0.1f, 2.0f, 0.0f);
            gTeamShields[this->iwork[12]] = -1;
            gTeamDamage[this->iwork[12]] = 0;
            break;

        case EVSTATE_SCRIPT_END:
            break;
    }

    if (this->iwork[13] != 0) {
        if (gActors[this->iwork[9]].obj.status != OBJ_ACTIVE) {
            this->iwork[13] = 0;
        } else {
            Matrix_RotateY(gCalcMatrix, gActors[this->iwork[9]].obj.rot.y * M_DTOR, MTXF_NEW);
            Matrix_RotateX(gCalcMatrix, gActors[this->iwork[9]].obj.rot.x * M_DTOR, MTXF_APPLY);
            Matrix_RotateZ(gCalcMatrix, gActors[this->iwork[9]].obj.rot.z * M_DTOR, MTXF_APPLY);
            Matrix_MultVec3fNoTranslate(gCalcMatrix, &this->vwork[28], &spAC);
            this->obj.pos.x = gActors[this->iwork[9]].obj.pos.x + spAC.x;
            this->obj.pos.y = gActors[this->iwork[9]].obj.pos.y + spAC.y;
            this->obj.pos.z = gActors[this->iwork[9]].obj.pos.z + spAC.z;
            this->vwork[29].x = gActors[this->iwork[9]].obj.rot.x;
            this->vwork[29].y = gActors[this->iwork[9]].obj.rot.y;
            this->vwork[29].z = gActors[this->iwork[9]].obj.rot.z;
            if (this->timer_0C0 == 0) {
                this->iwork[13] = 0;
            }
        }
    }

    Math_SmoothStepToF(&this->fwork[0], this->fwork[1], 0.1f, 5.0f, 0.0001f);

    if (this->rot_0F4.x >= 360.0f) {
        this->rot_0F4.x -= 360.0f;
    }
    if (this->rot_0F4.x < 0.0f) {
        this->rot_0F4.x += 360.0f;
    }
    if (this->rot_0F4.y >= 360.0f) {
        this->rot_0F4.y -= 360.0f;
    }
    if (this->rot_0F4.y < 0.0f) {
        this->rot_0F4.y += 360.0f;
    }

    if (this->iwork[6] != 0) {
        if ((gLevelMode == LEVELMODE_TURRET) && (this->eventType == EVID_200)) {
            Math_SmoothStepToAngle(&this->obj.rot.x, this->rot_0F4.x, 0.1f, 10.0f, 0.00001f);
            Math_SmoothStepToAngle(&this->obj.rot.y, this->rot_0F4.y, 0.1f, 10.0f, 0.00001f);
        } else {
            Math_SmoothStepToAngle(&this->obj.rot.x, this->rot_0F4.x, 0.2f, 100.0f, 0.00001f);
            Math_SmoothStepToAngle(&this->obj.rot.y, this->rot_0F4.y, 0.2f, 100.0f, 0.00001f);
        }
    }

    if (this->fwork[4] > 0.0f) {
        this->fwork[4] -= this->fwork[5];
        this->obj.rot.x += this->fwork[5] * this->fwork[6];
        if (this->obj.rot.x >= 360.0f) {
            this->obj.rot.x -= 360.0f;
        }
        if (this->obj.rot.x < 0.0f) {
            this->obj.rot.x += 360.0f;
        }
    }

    if (this->fwork[7] > 0.0f) {
        this->fwork[7] -= this->fwork[8];
        this->obj.rot.y += this->fwork[8] * this->fwork[9];
        if (this->obj.rot.y >= 360.0f) {
            this->obj.rot.y = this->obj.rot.y - 360.0f;
        }
        if (this->obj.rot.y < 0.0f) {
            this->obj.rot.y += 360.0f;
        }
    }

    if (this->fwork[10] > 0.0f) {
        if ((this->eventType == EVID_ME_METEOR_1) || (this->eventType == EVID_ME_METEOR_2) ||
            (this->eventType == EVID_ME_METEOR_4) || (this->eventType == EVID_ME_METEOR_5) ||
            (this->eventType == EVID_ME_BIG_METEOR) || (this->eventType == EVID_ME_ROCK_GULL) ||
            (this->eventType == EVID_ME_METEOR_6) || (this->eventType == EVID_ME_SECRET_MARKER_2) ||
            (this->eventType == EVID_WZ_METEOR_1) || (this->eventType == EVID_WZ_METEOR_2) ||
            (this->eventType == EVID_ME_METEOR_7)) {
            this->obj.rot.y -= this->fwork[11] * this->fwork[12];
            this->obj.rot.x += this->fwork[11] * this->fwork[12];
        } else {
            this->fwork[10] -= this->fwork[11];
            this->fwork[23] += this->fwork[11] * this->fwork[12];
        }
    }

    if (this->fwork[23] >= 360.0f) {
        this->fwork[23] -= 360.0f;
    }
    if (this->fwork[23] < 0.0f) {
        this->fwork[23] += 360.0f;
    }

    Math_SmoothStepToAngle(&this->obj.rot.z, this->fwork[23], 0.2f, 100.0f, 0.0001f);
    Matrix_RotateZ(gCalcMatrix, (this->vwork[29].z + this->rot_0F4.z) * M_DTOR, MTXF_NEW);
    Matrix_RotateY(gCalcMatrix, this->rot_0F4.y * M_DTOR, MTXF_APPLY);
    Matrix_RotateX(gCalcMatrix, this->rot_0F4.x * M_DTOR, MTXF_APPLY);

    spB8.x = 0.0f;
    spB8.y = 0.0f;
    spB8.z = this->fwork[0];

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &spB8, &spAC);

    this->vel.x = this->fwork[13] + spAC.x;
    this->vel.y = this->fwork[14] + spAC.y;
    this->vel.z = spAC.z;

    this->fwork[13] -= this->fwork[13] * 0.1f;
    this->fwork[14] -= this->fwork[14] * 0.1f;

    if (this->iwork[5] == EV_ZMODE(EMZ_RELATIVE)) {
        this->vel.z -= this->fwork[22];
        if ((gCurrentLevel == LEVEL_SECTOR_Y) && (gPathVelZ < 0.0f)) {
            this->vel.z -= gPathVelZ;
        }
    }

    if (this->iwork[5] == EV_ZMODE(EMZ_PLAYER)) {
        this->vel.z -= gPathVelZ;
    }

    if (gPlayer[0].state == PLAYERSTATE_ENTER_WARP_ZONE) {
        this->vel.z = 100.0f;
    }

    ActorEvent_ProcessTriggers(this);
    ActorEvent_ProcessActions(this);
    ActorEvent_UpdateTexLines(this);

    if (this->eventType == EVID_SX_WARP_GATE) {
        ActorEvent_800720E8(this);
    } else {
        if (this->scale <= -1.999f) {
            ActorEvent_80070BA8(this);
        } else {
            if ((this->dmgType == DMG_BEAM) && (this->scale < 0.5f) && (this->eventType != EVID_SY_ROBOT_1) &&
                (this->eventType != EVID_SY_ROBOT_2) && (this->eventType != EVID_SY_ROBOT_3)) {
                this->dmgType = DMG_NONE;
                if (gCurrentLevel == LEVEL_METEO) {
                    AUDIO_PLAY_SFX(NA_SE_ROCK_REFLECT, this->sfxSource, 4);
                } else {
                    AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
                }
            }

            if ((this->eventType < EVID_200) && (this->eventType != EVID_SUPPLY_CRATE) && (this->scale >= 0.5f)) {
                switch (this->eventType) {
                    case EVID_ITEM_WING_REPAIR:
                        ActorEvent_8006FE28(this);
                        break;
                    case EVID_ZO_BIRD:
                        ActorEvent_8006FEEC(this);
                        break;
                    default:
                        ActorEvent_800701E0(this);
                        break;
                }
            }
        }
    }
    switch (this->eventType) {
        case EVID_WZ_PILLAR_1:
        case EVID_WZ_PILLAR_2:
        case EVID_WZ_METEOR_1:
        case EVID_WZ_METEOR_2:
        case EVID_WZ_GATE:
            if ((gGameFrameCount % 8) == 0) {
                this->fwork[18] = RAND_FLOAT(255.0f);
                this->fwork[19] = RAND_FLOAT(255.0f);
                this->fwork[20] = RAND_FLOAT(255.0f);
            }
            Math_SmoothStepToF(&this->fwork[15], this->fwork[18], 1.0f, 10.0f, 0.0f);
            Math_SmoothStepToF(&this->fwork[16], this->fwork[19], 1.0f, 10.0f, 0.0f);
            Math_SmoothStepToF(&this->fwork[17], this->fwork[20], 1.0f, 10.0f, 0.0f);
            break;

        case EVID_ZO_PATROL_BOAT:
            if (Play_CheckDynaFloorCollision(&spEC, &spFC, this->obj.pos.x, -100.0f, this->obj.pos.z)) {
                spF0 = 10.0f;

                if (Math_SmoothStepToF(&this->obj.pos.y, spEC, 0.5f, 7.0f, 0.0f) >= 0.0f) {
                    spF0 = 350.0f;
                    if (((gGameFrameCount % 4) == 0)) {
                        ActorEvent_SpawnEffect365(this->obj.pos.x, spEC, this->obj.pos.z, this->obj.rot.y);
                        AUDIO_PLAY_SFX(NA_SE_IN_SPLASH_S, this->sfxSource, 4);
                    }
                }

                Math_SmoothStepToAngle(&this->obj.rot.x, spF0, 0.1f, 1.0f, 0.0f);

                if ((this->state == EVSTATE_F4_PLUS_Y) || (this->state == EVSTATE_F4_MINUS_Y)) {
                    var_fv0 = this->fwork[3] * 20.0f;
                    if (this->state == EVSTATE_F4_PLUS_Y) {
                        var_fv0 *= -1.0f;
                    }
                    Math_SmoothStepToAngle(&this->obj.rot.z, var_fv0, 0.1f, 3.0f, 0.0f);
                }
            }
            this->obj.rot.y = this->rot_0F4.y;
            break;

        case EVID_A6_UMBRA_STATION:
            this->obj.rot.z = gGameFrameCount;
            break;

        case EVID_A6_NINJIN_MISSILE:
        case EVID_A6_ROCKET:
            this->obj.rot.z = gGameFrameCount * 3.0f;
            break;

        case EVID_SPY_EYE:
            this->drawShadow = true;
            this->obj.rot.y -= 10.0f;
            break;

        case EVID_FIREBIRD:
            this->animFrame++;
            if (gCurrentLevel == LEVEL_SOLAR) {
                if (this->animFrame >= Animation_GetFrameCount(&aSoGoreAnim)) {
                    this->animFrame = 0;
                }
                if ((gGameFrameCount % 3) == 0) {
                    Solar_8019E9F4(this->obj.pos.x, this->obj.pos.y - 20, this->obj.pos.z - 180.0f, 0.0f,
                                   RAND_FLOAT(20.0f) * -1.0f, 0.0f, 4.0f, 2);
                }
            } else if (this->animFrame >= Animation_GetFrameCount(&aFirebirdAnim)) {
                this->animFrame = 0;
            }
            break;

        case EVID_TRIPOD:
            this->animFrame++;
            if (this->animFrame >= Animation_GetFrameCount(&aTripodAnim)) {
                this->animFrame = 0;
            }
            if (this->iwork[6] == 0) {
                this->obj.rot.y = 0.0f;
            }
            break;

        case EVID_SY_ROBOT_1:
        case EVID_SY_ROBOT_2:
        case EVID_SY_ROBOT_3:
            SectorY_SyRobot_Update(this);
            break;

        case EVID_SARUMARINE_PERISCOPE:
            ActorEvent_80072474(this);
            break;

        case EVID_SUPPLY_CRATE:
            ActorSupplies_Update(this);
            break;

        case EVID_ZO_BIRD:
            if (this->timer_0C4 == 0) {
                this->animFrame++;
                if (Animation_GetFrameCount(&aZoBirdAnim) < this->animFrame) {
                    this->animFrame = 0;
                }
            }
            break;

        case EVID_VE1_PILLAR: {
            Effect* effect;
            Vec3f sp90;
            Vec3f sp84;
            Vec3f sp78;
            s32 sp74;

            switch (this->work_046) {
                case 1:
                    break;

                case 0:
                    Matrix_RotateZ(gCalcMatrix, this->rot_0F4.z * M_DTOR, MTXF_NEW);
                    Matrix_MultVec3fNoTranslate(gCalcMatrix, &D_800D1290, &sp90);

                    if ((this->obj.pos.y + sp90.y) > -30.0f) {
                        for (sp74 = 0; sp74 < 7; sp74++) {
                            effect = Effect_Load(OBJ_EFFECT_394);

                            if (effect != NULL) {
                                effect->unk_78 = effect->unk_7A = 12;
                                effect->obj.status = OBJ_ACTIVE;
                                effect->obj.pos.x = this->obj.pos.x + sp90.x;
                                effect->obj.pos.y = this->obj.pos.y + sp90.y;
                                effect->obj.pos.z = this->obj.pos.z;
                                effect->obj.rot.x = RAND_FLOAT(360.0f);
                                effect->obj.rot.y = RAND_FLOAT(360.0f);
                                effect->obj.rot.z = RAND_FLOAT(360.0f);
                                sp84.x = RAND_FLOAT(25.0f) + 30.0f;
                                sp84.y = RAND_FLOAT(25.0f) + 20.0f;
                                sp84.z = 0.0f;
                                effect->unk_44 = 10;
                                effect->scale2 = 1.0f;
                                Matrix_RotateY(gCalcMatrix, (RAND_FLOAT(180.0f) + 180.0f) * M_DTOR, MTXF_NEW);
                                Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp84, &sp78);
                                effect->vel.x = sp78.x;
                                effect->vel.y = sp78.y;
                                effect->vel.z = sp78.z;
                                effect->unk_60.x = RAND_FLOAT_CENTERED(1.0f) + 5.0f;
                                effect->unk_60.y = RAND_FLOAT_CENTERED(1.0f) + 5.0f;
                                effect->unk_60.z = RAND_FLOAT_CENTERED(1.0f) + 5.0f;
                            }
                        }
                        this->work_046++;
                    }
                    break;
            }

            if ((fabsf(this->fwork[0]) > 10.0f) && ((gGameFrameCount % 2) == 0)) {
                effect = Effect_Load(OBJ_EFFECT_394);
                if (effect != NULL) {
                    Matrix_RotateZ(gCalcMatrix, this->rot_0F4.z * M_DTOR, MTXF_NEW);
                    Matrix_MultVec3fNoTranslate(gCalcMatrix, &D_800D1290, &sp90);

                    effect->unk_78 = effect->unk_7A = 11;

                    effect->obj.status = OBJ_ACTIVE;

                    effect->obj.pos.x = this->obj.pos.x + RAND_FLOAT_CENTERED(3.0f) + sp90.x;
                    effect->obj.pos.y = this->obj.pos.y + RAND_FLOAT_CENTERED(3.0f) + sp90.y;
                    effect->obj.pos.z = this->obj.pos.z + RAND_FLOAT_CENTERED(3.0f) + 180.0f;

                    effect->scale2 = 9.0f;
                    effect->obj.rot.z = RAND_FLOAT(360.0f);
                    effect->vel.x = RAND_FLOAT_CENTERED(5.0f);
                    effect->vel.y = RAND_FLOAT_CENTERED(3.0f) + 30.0f;
                    effect->unk_44 = 100;
                    effect->unk_46 = -8;
                    effect->unk_60.z = 3;

                    if (Rand_ZeroOne() < 0.5f) {
                        effect->unk_60.z = -effect->unk_60.z;
                    }

                    if ((gGameFrameCount & 2) != 0) {
                        effect->vel.y = -effect->vel.y;
                    }
                }

                if (((gGameFrameCount % 4) == 0)) {
                    effect = Effect_Load(OBJ_EFFECT_394);
                    if (effect != NULL) {
                        effect->unk_78 = effect->unk_7A = 11;
                        effect->obj.status = OBJ_ACTIVE;
                        effect->obj.pos.x = RAND_FLOAT_CENTERED(3.0f) + this->obj.pos.x;
                        effect->obj.pos.y = RAND_FLOAT_CENTERED(5.0f) + this->obj.pos.y + 50.0f;
                        effect->obj.pos.z = RAND_FLOAT_CENTERED(3.0f) + this->obj.pos.z + 200.0f;
                        effect->scale2 = 9.0f;
                        effect->obj.rot.z = RAND_FLOAT(360.0f);
                        effect->vel.x = RAND_FLOAT_CENTERED(5.0f);
                        effect->vel.y = RAND_FLOAT_CENTERED(3.0f) + 10.0f;
                        effect->unk_44 = 100;
                        effect->unk_46 = -8;
                        effect->unk_60.z = 3;

                        if (Rand_ZeroOne() < 0.5f) {
                            effect->unk_60.z = -effect->unk_60.z;
                        }

                        if ((gGameFrameCount & 4) != 0) {
                            effect->vel.y = -effect->vel.y;
                        }
                    }
                }
            }
        } break;

        case EVID_VE1_BLOCKER:
            Math_SmoothStepToF(&this->fwork[15], 1.0f, 0.1f, 0.1f, 0.001f);

            if (this->fwork[15] > 0.5f) {
                this->info.hitbox = SEGMENTED_TO_VIRTUAL(D_VE1_601B4C4);
            }

            if (this->work_046 == 0) {
                this->fwork[16] += 4.0f;
                if (this->fwork[16] >= 100.0f) {
                    this->work_046 = 1;
                    this->fwork[16] = 100.0f;
                }
            } else {
                this->fwork[16] -= 4.0f;
                if (this->fwork[16] <= 0.0f) {
                    this->work_046 = 0;
                    this->fwork[16] = 0.0f;
                }
            }
            break;

        case EVID_AQ_OYSTER:
            if (this->health <= 0) {
                if (this->animFrame == 20) {
                    spD4 = this->obj.pos.z;
                    spD8 = this->obj.pos.y;

                    this->obj.pos.y += 80.0f;
                    this->obj.pos.z += 40.0f;
                    Actor_Despawn(this);
                    this->obj.pos.y = spD8;
                    this->obj.pos.z = spD4;
                }

                if ((this->animFrame >= 18) && (this->animFrame < 24)) {
                    Effect_Effect362_Spawn(this->obj.pos.x, this->obj.pos.y + 80.0f, this->obj.pos.z + 60.0f, 20.0f);
                }

                if (this->animFrame < 49) {
                    this->animFrame++;
                    if (this->animFrame >= 49) {
                        this->animFrame = 49;
                    }
                    if ((gGameFrameCount % 2) != 0) {
                        Aquas_Effect366_Spawn(RAND_FLOAT_CENTERED(100.0f) + this->obj.pos.x,
                                              RAND_FLOAT(50.0f) + this->obj.pos.y,
                                              RAND_FLOAT_CENTERED(100.0f) + this->obj.pos.z, 1.0f, 0);
                    }
                }
                this->timer_0C2 = 10000;
            }
            break;

        case EVID_AQ_STARFISH:
            if (this->work_04A == 0) {
                this->work_046 += 4;
                if (this->work_046 >= 255) {
                    this->work_046 = 255;
                    this->work_04A = 1;
                }
            } else {
                this->work_046 -= 4;
                if (this->work_046 <= 0) {
                    this->work_046 = 0;
                    this->work_04A = 0;
                }
            }
            break;

        case EVID_ANDROSS_GATE:
        case EVID_ANDROSS_GATE_2:
            Andross_80187530(this);
            break;

        case EVID_KILLER_BEE:
            this->animFrame++;
            if (this->animFrame >= 6) {
                this->animFrame = 0;
            }
            break;
    }

    // Unused early RadarMark implementation?
    /*
    if (gLevelMode == LEVELMODE_ALL_RANGE) {
        D_ctx_80177F20[this->index + 1] = this->obj.pos.x;
        D_ctx_80178028[this->index + 1] = this->obj.pos.z;
        D_ctx_80178130[this->index + 1] = Math_ModF(this->rot_0F4.y, 360.0f) + 180.0f;
        D_ctx_80178238[this->index + 1] = 1;
    }
    */
}

UNK_TYPE D_800D129C[140] = { 0 }; // unused

bool ActorEvent_OverrideLimbDraw1(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    Actor* this = thisx;

    if (limbIndex == 1) {
        pos->x += this->fwork[16];
    }
    if (limbIndex == 2) {
        rot->z -= this->fwork[15];
    }
    return false;
}

bool ActorEvent_OverrideLimbDraw2(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    Actor* this = thisx;
    s32 var_s1;

    if (limbIndex == 5) {
        var_s1 = (s32) (this->health * (255.0f / 400.0f));
        if (var_s1 > 255) {
            var_s1 = 255;
        }
        if (var_s1 < 0) {
            var_s1 = 1.0f / 70.925f;
        }

        Matrix_Translate(gCalcMatrix, pos->x, pos->y, pos->z, MTXF_APPLY);
        Matrix_RotateZ(gCalcMatrix, rot->z * M_DTOR, MTXF_APPLY);
        Matrix_RotateY(gCalcMatrix, rot->y * M_DTOR, MTXF_APPLY);
        Matrix_RotateX(gCalcMatrix, rot->x * M_DTOR, MTXF_APPLY);
        Matrix_Mult(gGfxMatrix, gCalcMatrix, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);

        if (*dList != NULL) {
            RCP_SetupDL(&gMasterDisp, SETUPDL_34);
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, var_s1, var_s1, 255);
            gSPDisplayList(gMasterDisp++, *dList);
            RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
        }
        return true;
    }
    return false;
}

void ActorEvent_SxWarpGate_Draw(ActorEvent* this) {
    Vec3f frameTable[10];

    Animation_GetFrameData(&D_SX_6013820, 0, frameTable);
    frameTable[6].y += this->fwork[15];
    frameTable[5].z += this->fwork[16] + (s32) ((this->timer_0BE >> 2) % 2U);
    frameTable[4].z -= this->fwork[16] + (s32) ((this->timer_0BE >> 2) % 2U);
    Animation_DrawSkeleton(1, D_SX_601390C, frameTable, ActorEvent_OverrideLimbDraw2, NULL, this, &gIdentityMatrix);
}

bool ActorEvent_OverrideLimbDraw3(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    gSPClearGeometryMode(gMasterDisp++, G_TEXTURE_GEN);
    if ((limbIndex == 3) || (limbIndex == 5)) {
        gSPTexture(gMasterDisp++, 5000, 5000, 0, G_TX_RENDERTILE, G_ON);
        gSPSetGeometryMode(gMasterDisp++, G_TEXTURE_GEN);
    }
    return false;
}

s32 SyShipDebris_Draw(SyShipDebris* this) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_60);
    gSPDisplayList(gMasterDisp++, aSyDebrisDL);
    RCP_SetupDL(&gMasterDisp, SETUPDL_64);
    return 0;
}

void ActorEvent_Draw(ActorEvent* this) {
    s32 pad2[3];
    Vec3f frameTable[30];
    f32 sp40;
    s16 savedState;
    s32 pad;

    if (this->timer_0C6 && (this->eventType != EVID_MA_RAILROAD_CART) && (this->eventType != EVID_SY_LASER_TURRET) &&
        (this->eventType != EVID_SY_SHIP_WINDOWS)) {
        if ((this->eventType != EVID_ME_METEOR_1) && (this->eventType != EVID_ME_METEOR_2) &&
            (this->eventType != EVID_ME_METEOR_4) && (this->eventType != EVID_ME_METEOR_5) &&
            (this->eventType != EVID_AQ_OYSTER) && (this->eventType != EVID_MA_BOULDER) && (this->scale > 0.5f) &&
            (this->timer_0C6 >= 9) && ((this->timer_0C6 & 3) == 0) && (gPlayState != PLAY_PAUSE)) {
            Effect_Effect390_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, this->vel.x, this->vel.y,
                                   this->vel.z, this->scale * 0.07f, 3);
        }

        if ((this->eventType != EVID_A6_NINJIN_MISSILE) && (this->eventType != EVID_VENOM_FIGHTER_3) &&
            (this->eventType != EVID_ZO_BIRD) && (this->eventType != EVID_AQ_OYSTER) &&
            (this->eventType != EVID_SX_LASER) && (this->eventType != EVID_SY_ROBOT_4) &&
            (this->eventType != EVID_ME_METEOR_1) && (this->eventType != EVID_SY_SHIP_WINDOWS) &&
            (this->eventType != EVID_SX_WATCH_POST) && (this->scale > 0.5f)) {
            sp40 = SIN_DEG(this->timer_0C6 * 400.0f) * this->timer_0C6;
            Matrix_RotateY(gGfxMatrix, M_DTOR * sp40, MTXF_APPLY);
            Matrix_RotateX(gGfxMatrix, M_DTOR * sp40, MTXF_APPLY);
            Matrix_RotateZ(gGfxMatrix, M_DTOR * sp40, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
        }
    }

    if ((this->obj.status == OBJ_DYING) && (this->timer_0BE != 0)) {
        RCP_SetupDL_27();
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
    }

    if ((this->eventType == EVID_SX_SPACE_MINE) || (this->eventType == EVID_SY_ROBOT_SPRITE_SIDE) ||
        (this->eventType == EVID_SY_ROBOT_SPRITE_FRONT)) {
        RCP_SetupDL_60(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
    } else if ((this->eventType == EVID_MA_LASER_TURRET) || (this->eventType == EVID_MA_RAILROAD_CART) ||
               ((this->eventType == EVID_FIREBIRD) && (gCurrentLevel == LEVEL_SOLAR))) {
        if ((this->timer_0C6 % 2) == 0) {
            RCP_SetupDL(&gMasterDisp, SETUPDL_57);
        } else {
            RCP_SetupDL(&gMasterDisp, SETUPDL_61);
        }
    }

    switch (this->eventType) {
        case EVID_WZ_PILLAR_1:
        case EVID_WZ_PILLAR_2:
        case EVID_WZ_METEOR_1:
        case EVID_WZ_METEOR_2:
        case EVID_WZ_GATE:
            RCP_SetupDL(&gMasterDisp, SETUPDL_34);
            gDPSetTextureFilter(gMasterDisp++, G_TF_POINT);
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, (s32) this->fwork[15], (s32) this->fwork[16],
                            (s32) this->fwork[17], 255);
            gSPDisplayList(gMasterDisp++, sEventActorInfo[this->eventType].dList);
            gDPSetTextureFilter(gMasterDisp++, G_TF_BILERP);
            break;

        default:
            if ((this->eventType < EVID_200) && (sEventActorInfo[this->eventType].dList != NULL)) {
                gSPDisplayList(gMasterDisp++, sEventActorInfo[this->eventType].dList);
            }

            switch (this->eventType) {
                case EVID_TI_GREAT_FOX:
                    Cutscene_DrawGreatFox();
                    break;

                case EVID_VENOM_FIGHTER_1:
                    this->iwork[11] = 1;
                    Actor_DrawEngineAndContrails(this);
                    break;

                case EVID_ME_SLIPPY:
                    this->fwork[15] -= this->fwork[15] * 0.1f;
                    this->fwork[26] -= this->fwork[26] * 0.1f;
                    this->fwork[16] -= this->fwork[16] * 0.1f;
                    this->fwork[27] -= this->fwork[27] * 0.1f;

                    if (this->obj.rot.z > 0.0f) {
                        this->fwork[15] += (this->obj.rot.z * 0.7f - this->fwork[15]) * 0.2f;
                        this->fwork[26] += (-this->obj.rot.z * 0.7f - this->fwork[26]) * 0.2f;
                    }

                    if (this->obj.rot.z < 0.0f) {
                        this->fwork[16] += (-this->obj.rot.z * 0.7f - this->fwork[16]) * 0.2f;
                        this->fwork[27] += (this->obj.rot.z * 0.7f - this->fwork[27]) * 0.2f;
                    }
                    ActorTeamArwing_Draw(this);
                    break;

                case EVID_TEAMMATE:
                    if (gLevelType == LEVELTYPE_PLANET) {
                        gSPDisplayList(gMasterDisp++, D_ENMY_PLANET_40018A0);
                    } else {
                        gSPDisplayList(gMasterDisp++, D_ENMY_SPACE_4007870);
                    }
                    Actor_DrawEngineAndContrails(this);
                    break;

                case EVID_GRANGA_FIGHTER_2:
                    this->iwork[11] = 1;
                    Actor_DrawEngineAndContrails(this);
                    break;

                case EVID_FIREBIRD:
                    if (gCurrentLevel == LEVEL_SOLAR) {
                        gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                        Animation_GetFrameData(&aSoGoreAnim, this->animFrame, frameTable);
                        Animation_DrawSkeleton(1, aSoGoreSkel, frameTable, NULL, NULL, this, &gIdentityMatrix);
                        gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
                    } else {
                        Animation_GetFrameData(&aFirebirdAnim, this->animFrame, frameTable);
                        Animation_DrawSkeleton(1, aFirebirdSkel, frameTable, NULL, NULL, this, &gIdentityMatrix);
                    }
                    break;

                case EVID_CORNERIAN_FIGHTER:
                    this->iwork[11] = 1;
                    Actor_DrawEngineAndContrails(this);
                    break;

                case EVID_TRIPOD:
                    Matrix_Translate(gGfxMatrix, 0.0f, -30.0f, 0.0f, MTXF_APPLY);
                    Animation_GetFrameData(&aTripodAnim, this->animFrame, frameTable);
                    Animation_DrawSkeleton(1, aTripodSkel, frameTable, NULL, NULL, this, &gIdentityMatrix);
                    break;

                case EVID_SX_SPY_EYE:
                    if (this->fwork[0] > 0.1f) {
                        this->iwork[11] = 1;
                        Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -30.0f, MTXF_APPLY);
                        Matrix_Scale(gGfxMatrix, 2.5f, 2.5f, 2.5f, MTXF_APPLY);
                        Actor_DrawEngineGlow(this, EG_GREEN);
                    }
                    break;

                case EVID_SX_CANINE:
                    if (this->fwork[0] > 0.1f) {
                        this->iwork[11] = 1;
                        Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -30.0f, MTXF_APPLY);
                        Matrix_Scale(gGfxMatrix, 2.5f, 2.5f, 2.5f, MTXF_APPLY);
                        Actor_DrawEngineGlow(this, EG_GREEN);
                    }
                    break;

                case EVID_SPACE_MINE:
                    RCP_SetupDL_60(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
                    gSPDisplayList(gMasterDisp++, aA6SpaceMineDL);
                    break;

                case EVID_A6_NINJIN_MISSILE:
                    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                    gSPDisplayList(gMasterDisp++, aA6NinjinMissileDL);
                    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
                    Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -30.0f, MTXF_APPLY);
                    this->iwork[11] = 1;
                    Actor_DrawEngineGlow(this, EG_GREEN);
                    break;

                case EVID_A6_ROCKET:
                    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                    gSPDisplayList(gMasterDisp++, aA6RocketDL);
                    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
                    Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -30.0f, MTXF_APPLY);
                    this->iwork[11] = 1;
                    Actor_DrawEngineGlow(this, EG_GREEN);
                    break;

                case EVID_SX_LASER:
                    if (this->timer_0C2 != 0) {
                        if (((this->timer_0C2 & 3) == 0) && (gPlayState != PLAY_PAUSE)) {
                            func_effect_8007D0E0(RAND_FLOAT_CENTERED(200.0f) + this->obj.pos.x,
                                                 RAND_FLOAT_CENTERED(200.0f) + this->obj.pos.y,
                                                 RAND_FLOAT_CENTERED(200.0f) + this->obj.pos.z,
                                                 RAND_FLOAT(1.5f) + 2.5f);
                        }
                        RCP_SetupDL(&gMasterDisp, SETUPDL_57);
                        gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
                        gSPDisplayList(gMasterDisp++, aSxLaserDestroyedDL);
                    } else {
                        gSPDisplayList(gMasterDisp++, aSxLaserDL);
                    }
                    break;

                case EVID_A6_UMBRA_STATION:
                    Matrix_RotateX(gGfxMatrix, M_PI / 2, MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, aA6UmbraStationDL);
                    break;

                case EVID_CRUISER_GUN:
                    Animation_GetFrameData(&aCruiserGunAnim, this->animFrame, frameTable);
                    Matrix_RotateY(gGfxMatrix, M_PI, MTXF_APPLY);
                    Matrix_Scale(gGfxMatrix, 1.5f, 1.5f, 1.5f, MTXF_APPLY);
                    Animation_DrawSkeleton(1, aCruiserGunSkel, frameTable, ActorEvent_OverrideLimbDraw1, NULL, this,
                                           &gIdentityMatrix);
                    Math_SmoothStepToF(&this->fwork[16], 0.0f, 0.3f, 2.0f, 0.0001f);
                    break;

                case EVID_TI_BOMBER:
                    Animation_GetFrameData(&aTiBomberAnim, this->animFrame, frameTable);
                    frameTable[2].z += this->fwork[15];
                    Animation_DrawSkeleton(1, aTiBomberSkel, frameTable, NULL, NULL, this, &gIdentityMatrix);
                    break;

                case EVID_SX_WARP_GATE:
                    ActorEvent_SxWarpGate_Draw(this);
                    break;

                case EVID_SY_ROBOT_1:
                case EVID_SY_ROBOT_2:
                case EVID_SY_ROBOT_3:
                    SectorY_SyRobot_Draw(this);
                    break;

                case EVID_SARUMARINE_PERISCOPE:
                    Animation_GetFrameData(&aZoSarumarinePeriscopeAnim, this->animFrame, frameTable);
                    frameTable[2].z -= this->fwork[15];
                    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                    Matrix_Scale(gGfxMatrix, 2.6f, 2.6f, 2.6f, MTXF_APPLY);
                    Animation_DrawSkeleton(1, aZoSarumarinePeriscopeSkel, frameTable, NULL, NULL, this,
                                           &gIdentityMatrix);
                    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
                    break;

                case EVID_ME_ROCK_GULL:
                    Matrix_Push(&gGfxMatrix);
                    Matrix_RotateX(gGfxMatrix, this->rot_0F4.x * M_DTOR, MTXF_APPLY);
                    Matrix_RotateY(gGfxMatrix, this->rot_0F4.y * M_DTOR, MTXF_APPLY);
                    Matrix_Push(&gGfxMatrix);
                    Matrix_Translate(gGfxMatrix, 0.0f, this->fwork[15], 0.0f, MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, aMeRockGull1DL);
                    Matrix_Pop(&gGfxMatrix);
                    gSPDisplayList(gMasterDisp++, aMeRockGull2DL);
                    Matrix_Translate(gGfxMatrix, 0.0f, -this->fwork[15], 0.0f, MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, aMeRockGull3DL);
                    Matrix_Pop(&gGfxMatrix);
                    break;

                case EVID_ME_FLIP_BOT:
                    gSPDisplayList(gMasterDisp++, aMeFlipBot1DL);
                    RCP_SetupDL(&gMasterDisp, SETUPDL_53);
                    gSPDisplayList(gMasterDisp++, aMeFlipBot2DL);
                    break;

                case EVID_SUPPLY_CRATE:
                    ActorSupplies_Draw(this);
                    break;

                case EVID_ZO_BIRD:
                    savedState = this->state;
                    this->state = 2;
                    Zoness_ZoBird_Draw(this);
                    this->state = savedState;
                    break;

                case EVID_VE1_PILLAR:
                    Matrix_Scale(gGfxMatrix, 0.6f, 0.6f, 0.6f, MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, aVe1PillarDL);
                    break;

                case EVID_VE1_BLOCKER:
                    if (this->fwork[15] > 0.001f) {
                        Matrix_Scale(gGfxMatrix, this->fwork[15], this->fwork[15], this->fwork[15], MTXF_APPLY);
                        Matrix_SetGfxMtx(&gMasterDisp);
                        Texture_BlendRGBA16(this->fwork[16], 16 * 11, D_VE1_9003890, D_VE1_9003DF0, D_VE1_9003330);
                        gSPDisplayList(gMasterDisp++, aVe1BlockerDL);
                    }
                    break;

                case EVID_MA_LASER_TURRET:
                    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                    gSPDisplayList(gMasterDisp++, aMaLaserTurretDL);
                    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
                    break;

                case EVID_AQ_OYSTER:
                    Matrix_Scale(gGfxMatrix, 3.0f, 3.0f, 3.0f, MTXF_APPLY);
                    Animation_GetFrameData(&aAqOysterAnim, this->animFrame, frameTable);
                    Animation_DrawSkeleton(1, aAqOysterSkel, frameTable, NULL, NULL, this, &gIdentityMatrix);
                    break;

                case EVID_BILL:
                    gSPDisplayList(gMasterDisp++, aBillShipDL);
                    Actor_DrawEngineAndContrails(this);
                    break;

                case EVID_KATT:
                    gSPDisplayList(gMasterDisp++, aKattShipDL);
                    Actor_DrawEngineAndContrails(this);
                    break;

                case EVID_AQ_STARFISH:
                    RCP_SetupDL(&gMasterDisp, SETUPDL_22);
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, this->work_046, this->work_046, this->work_046, 255);
                    gSPDisplayList(gMasterDisp++, aAqStarfishDL);
                    break;

                case EVID_AQ_SHELL:
                    RCP_SetupDL(&gMasterDisp, SETUPDL_21);
                    gSPDisplayList(gMasterDisp++, aAqShellDL);
                    break;

                case EVID_ANDROSS_GATE:
                case EVID_ANDROSS_GATE_2:
                    Andross_Gate_Draw(this);
                    break;

                case EVID_SX_WARP_ENMY:
                    RCP_SetupDL(&gMasterDisp, SETUPDL_35);
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 0, 0, 0, 143);
                    gDPSetEnvColor(gMasterDisp++, 0, 0, 0, 0);
                    gSPDisplayList(gMasterDisp++, aWzSxEnemy1DL);
                    break;

                case EVID_KILLER_BEE:
                    Animation_GetFrameData(&aKillerBeeAnim, this->animFrame, frameTable);
                    Animation_DrawSkeleton(1, aKillerBeeSkel, frameTable, NULL, NULL, this, &gIdentityMatrix);
                    break;

                case EVID_FFF:
                    this->timer_0C2 = 10;
                    break;
            }

            if ((gReflectY > 0) && ((this->iwork[12] >= TEAM_ID_FALCO) && (this->iwork[12] < TEAM_ID_MAX))) {
                Vec3f src = { 0.0f, 0.0f, 0.0f };

                if ((this->iwork[12] == TEAM_ID_KATT) || (this->iwork[12] == TEAM_ID_BILL)) {
                    Matrix_MultVec3f(gGfxMatrix, &src, &gTeamArrowsViewPos[this->iwork[12] + 4]);
                } else {
                    Matrix_MultVec3f(gGfxMatrix, &src, &gTeamArrowsViewPos[this->iwork[12]]);
                }
            }
            break;
    }
}

void func_enmy2_800763A4(Actor* this) {
    s32 i;
    s32 sp60;
    s32 triangleIndex;
    f32 floorHeight;
    Vec3f vel;
    s32 pad;

    if (this->eventType == EVID_SX_LASER) {
        this->obj.pos.y -= this->vel.y;
        this->obj.status = OBJ_ACTIVE;
        func_effect_8007D0E0(this->obj.pos.x - this->vel.x, this->obj.pos.y + 30.0f, this->obj.pos.z - this->vel.z,
                             this->scale * 5.0f);
        this->timer_0C2 = 10000;
        return;
    }

    if (this->timer_0BE != 0) {
        this->vel.z = 0.0f;
        this->vel.x = 0.0f;
        this->vel.y = 0.0f;

        if (this->timer_0BE == 1) {
            Object_Kill(&this->obj, this->sfxSource);
            Actor_Despawn(this);

            // Unused early RadarMark implementation?
            /*
            if (gLevelMode == LEVELMODE_ALL_RANGE) {
                D_ctx_80177F20[this->index + 1] = this->obj.pos.x;
                D_ctx_80178028[this->index + 1] = this->obj.pos.z;
                D_ctx_80178130[this->index + 1] = 1001.0f;
            }
            */
            return;
        }
    } else {
        if ((gLevelType == LEVELTYPE_PLANET) || (gCurrentLevel == LEVEL_BOLSE)) {
            this->gravity = 0.4f;
        }

        switch (this->work_04C) {
            case 0:
            case 1:
                if ((this->index % 2) != 0) {
                    this->obj.rot.z -= 8.0f;
                } else {
                    this->obj.rot.z += 8.0f;
                }
                break;

            case 2:
                this->obj.rot.y += 5.0f;
                this->obj.rot.x += 7.3f;
                break;

            case 3:
                this->obj.rot.y += 6.0f;
                this->obj.rot.x += 18.3f;
                this->gravity = 0.7f;
                break;

            case 4:
                this->obj.rot.x += (-90.0f - this->obj.rot.x) * 0.1f;
                break;
        }

        if (((this->timer_0BC % 4U) == 1) && (this->eventType != EVID_ME_METEOR_1) &&
            (this->eventType != EVID_ME_METEOR_4)) {
            func_effect_8007D24C(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 2.2f);
        }

        if (gUseDynaFloor && Play_CheckDynaFloorCollision(&floorHeight, &triangleIndex, this->obj.pos.x,
                                                          this->obj.pos.y, this->obj.pos.z)) {
            Effect386_Spawn1(this->obj.pos.x, floorHeight + 20.0f, this->obj.pos.z, 0.0f, 0.0f, 0.0f,
                             this->scale * 3.0f, 5);
            Effect_Effect381_Spawn(this->obj.pos.x, floorHeight, this->obj.pos.z, 2.0f);
            this->timer_0BE = 2;
            Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_EXPLOSION_S);
            return;
        }

        if (gGroundType == 4) {
            if (Ground_801B6AEC(this->obj.pos.x, this->obj.pos.y - 10.0f, this->obj.pos.z + gPathProgress) != 0) {
                func_effect_8007D2C8(this->obj.pos.x, this->obj.pos.y + 20.0f, this->obj.pos.z, this->scale * 6.0f);
                Effect386_Spawn1(this->obj.pos.x - this->vel.x, this->obj.pos.y + 30.0f, this->obj.pos.z - this->vel.z,
                                 0.0f, 0.0f, 0.0f, this->scale * 4.0f, 20);
                func_enmy_80062C38(this->obj.pos.x, this->obj.pos.z);
                this->timer_0BE = 2;
                Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_EXPLOSION_S);
                return;
            }
        } else {
            vel.x = this->vel.x;
            vel.y = this->vel.y;
            vel.z = this->vel.z;

            sp60 = Object_CheckCollision(this->index, &this->obj.pos, &vel, 0);

            if ((sp60 != 0) || (this->obj.pos.y < (gGroundHeight + 30.0f))) {
                if ((Rand_ZeroOne() < 0.5f) && (this->work_04C < 3) && (gLevelType == LEVELTYPE_PLANET) &&
                    (sp60 != 999) && (gGroundSurface != SURFACE_WATER) &&
                    ((this->vel.z < -20.0f) || (this->vel.z > 0.0f))) {
                    if (gCurrentLevel == LEVEL_FORTUNA) {
                        func_enmy2_8006BF7C(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z - this->vel.z);
                        func_enmy_80062C38(this->obj.pos.x, this->obj.pos.z);
                    }

                    this->obj.pos.y -= this->vel.y;
                    this->vel.y = RAND_FLOAT(10.0f);
                    this->work_04C = 3;

                    if (gLevelMode == LEVELMODE_ALL_RANGE) {
                        func_effect_8007D2C8(this->obj.pos.x - this->vel.x, this->obj.pos.y,
                                             this->obj.pos.z - this->vel.z, this->scale * 3.0f);
                    }

                    func_effect_8007D2C8(this->obj.pos.x - this->vel.x, this->obj.pos.y, this->obj.pos.z - this->vel.z,
                                         this->scale * 3.0f);

                    if ((this->obj.id == OBJ_ACTOR_ALLRANGE) && (this->aiType < AI360_KATT)) {
                        Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_EXPLOSION_M);
                    } else {
                        Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_EXPLOSION_S);
                    }

                    if ((this->obj.id == OBJ_ACTOR_EVENT) && (this->eventType == EVID_ME_SLIPPY)) {
                        if (this->fwork[17] < 360.0f) {
                            Play_SpawnDebris(1, this->obj.pos.x + 20.0f, this->obj.pos.y, this->obj.pos.z);
                            this->fwork[17] = 777.0f;
                        }
                        if (this->fwork[18] < 360.0f) {
                            Play_SpawnDebris(0, this->obj.pos.x - 20.0f, this->obj.pos.y, this->obj.pos.z);
                            this->fwork[18] = 777.0f;
                        }
                    }
                } else {
                    if ((this->obj.pos.y < (gGroundHeight + 30.0f)) && (gLevelType == LEVELTYPE_PLANET)) {
                        this->vel.z = 0.0f;
                        if (gGroundSurface == SURFACE_WATER) {
                            Effect_Effect367_Spawn(this->obj.pos.x, gGroundHeight + 2.0f, this->obj.pos.z, 3.0f, 20.0f,
                                                   0);
                            Effect_Effect367_Spawn(this->obj.pos.x, gGroundHeight + 2.0f, this->obj.pos.z, 3.0f, 20.0f,
                                                   10);
                            Effect_Effect367_Spawn(this->obj.pos.x, gGroundHeight + 2.0f, this->obj.pos.z, 3.0f, 20.0f,
                                                   20);
                            Effect_Effect372_Spawn2(this->obj.pos.x, gGroundHeight, this->obj.pos.z, 0.1f, 3.0f);
                        } else {
                            PlayerShot_SpawnEffect344(this->obj.pos.x, 3.0f, this->obj.pos.z, this->obj.pos.x,
                                                      this->obj.pos.z, 0.0f, 0.0f, 90.0f, 6.5f, 0, 0);
                        }
                        Effect_Effect390_Spawn(this->obj.pos.x, 20.0f, this->obj.pos.z, 0.0f, 0.0f, 0.0f,
                                               this->scale * 0.05f, 30);
                        if ((gCurrentLevel == LEVEL_FORTUNA) || (gCurrentLevel == LEVEL_VENOM_2)) {
                            Effect_Effect387_Spawn(this->obj.pos.x, gGroundHeight + 30.0f, this->obj.pos.z, 3.0f, 60);
                            if (gCurrentLevel == LEVEL_FORTUNA) {
                                func_enmy_80062C38(this->obj.pos.x, this->obj.pos.z);
                            }
                        }
                    }

                    this->obj.pos.y -= this->vel.y;
                    func_effect_8007D0E0(this->obj.pos.x - this->vel.x, this->obj.pos.y + 30.0f,
                                         this->obj.pos.z - this->vel.z, this->scale * 5.0f);
                    if (gLevelMode == LEVELMODE_ALL_RANGE) {
                        Effect386_Spawn1(this->obj.pos.x, this->obj.pos.y + 30.0f, this->obj.pos.z, this->vel.x, 10.0f,
                                         this->vel.z, this->scale * 3.0f, 20);
                        if (sp60 == 999) {
                            Effect_Effect387_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z,
                                                   this->scale * 3.0f, 70);
                        }
                        for (i = 0; i < 4; i++) {
                            if (Rand_ZeroOne() < 0.7f) {
                                if (gCurrentLevel == LEVEL_FORTUNA) {
                                    Play_SpawnDebris(4, this->obj.pos.x, this->obj.pos.y, this->obj.pos.z);
                                } else {
                                    Effect_Effect357_Spawn50(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 1.0f);
                                }
                            }
                        }
                    } else {
                        Effect386_Spawn1(this->obj.pos.x - this->vel.x, this->obj.pos.y + 30.0f,
                                         (this->obj.pos.z - this->vel.z) + 48.0f, 0.0f, 0.0f, 0.0f, this->scale * 3.0f,
                                         5);
                    }

                    this->timer_0BE = 2;

                    if ((this->obj.id == OBJ_ACTOR_ALLRANGE) && (this->aiType < AI360_KATT)) {
                        Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_EXPLOSION_M);
                    } else {
                        Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_EXPLOSION_S);
                    }
                }
            }
        }
        if ((this->dmgType != DMG_NONE) || (this->timer_0BC == 0) ||
            ((this->itemDrop != DROP_NONE) && (this->obj.id != OBJ_ACTOR_ALLRANGE))) {
            if (gLevelMode == LEVELMODE_ALL_RANGE) {
                for (i = 0; i < 4; i++) {
                    if (Rand_ZeroOne() < 0.7f) {
                        if (gCurrentLevel == LEVEL_FORTUNA) {
                            Play_SpawnDebris(4, this->obj.pos.x, this->obj.pos.y, this->obj.pos.z);
                        } else {
                            Effect_Effect357_Spawn50(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 1.0f);
                        }
                    }
                }

                Effect386_Spawn1(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, this->vel.x, this->vel.y,
                                 this->vel.z, 5.0f, 15);
                func_effect_8007D0E0(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z - this->vel.z, 8.0f);
            } else {
                if ((this->eventType != EVID_ME_METEOR_1) && (this->eventType != EVID_ME_METEOR_4)) {
                    func_effect_8007D0E0(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z - this->vel.z,
                                         this->scale * 5.0f);
                }

                if (this->eventType == EVID_TI_BOMBER) {
                    Effect386_Spawn1(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, this->vel.x, this->vel.y,
                                     this->vel.z, 5.0f, 15);
                }
            }

            this->timer_0BE = 2;

            if ((this->obj.id == OBJ_ACTOR_ALLRANGE) && (this->aiType < AI360_KATT)) {
                Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_EXPLOSION_M);
            } else {
                Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_EXPLOSION_S);
            }
        }
    }

    // Unused early RadarMark implementation?
    /*
    if (gLevelMode == LEVELMODE_ALL_RANGE) {
        D_ctx_80177F20[this->index + 1] = this->obj.pos.x;
        D_ctx_80178028[this->index + 1] = this->obj.pos.z;
        D_ctx_80178130[this->index + 1] = this->rot_0F4.y + 180.0f;
    }
    */

    if (this->obj.id == OBJ_ACTOR_ALLRANGE) {
        ActorAllRange_SetShadowData(this);
    }
}

void ActorEvent_Dying(ActorEvent* this) {
    if ((this->eventType == EVID_SY_ROBOT_1) || (this->eventType == EVID_SY_ROBOT_2) ||
        (this->eventType == EVID_SY_ROBOT_3)) {
        SectorY_SyRobot_Update(this);
    } else {
        func_enmy2_800763A4(this);
    }
}

void TiGreatFox_Update(TiGreatFox* this) {
    Vec3f sp24;

    Math_Vec3fFromAngles(&sp24, this->obj.rot.x, this->obj.rot.y, 50.0f);
    this->vel.x = sp24.x;
    this->vel.y = sp24.y;
    this->vel.z = sp24.z;
}

void TiGreatFox_Draw(TiGreatFox* this) {
    Cutscene_DrawGreatFox();
}
