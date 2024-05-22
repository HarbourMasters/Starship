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

void func_enmy2_8006A800(Effect* effect, f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    Effect_Initialize(effect);

    effect->obj.status = OBJ_INIT;
    effect->obj.id = OBJ_EFFECT_361;
    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;
    effect->unk_48 = 3;

    if (Rand_ZeroOne() < 0.5f) {
        effect->unk_48 = -effect->unk_48;
    }

    effect->unk_4A = 100;
    effect->scale2 = scale2 * 0.25f;
    effect->scale1 = 0.3f;

    if (scale2 < 10.0f) {
        effect->scale1 = 0.1f;
    }

    effect->obj.rot.z = RAND_FLOAT(360.0f);
    Object_SetInfo(&effect->info, effect->obj.id);
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
}

void Actor237_Draw(Actor237* this) {
}

void Obj54_8006A984(Effect* effect, f32 xPos, f32 yPos, f32 zPos) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = OBJ_EFFECT_365;

    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;

    effect->unk_44 = 40;
    effect->scale2 = 5.0f;
    effect->scale1 = RAND_FLOAT_CENTERED(2.0f);
    effect->vel.y = 10.0f;
    effect->obj.rot.z = RAND_FLOAT(360.0f);
    Object_SetInfo(&effect->info, effect->obj.id);
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

void Scenery54_Update(Scenery_54* this) {
    Vec3f sp24;
    Vec3f sp18;

    Texture_Scroll(D_CO_60038F8, 32, 32, 1);
    if ((gGameFrameCount % 4) == 0) {
        Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);

        sp18.x = RAND_FLOAT_CENTERED(700.0f);
        sp18.y = RAND_FLOAT(50.0f);
        sp18.z = 700.0f;

        Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp18, &sp24);
        Obj54_8006AA3C(this->obj.pos.x + sp24.x, this->obj.pos.y + sp24.y + 50.0f, this->obj.pos.z + sp24.z);
    }
}

bool Actor201_8006ABA4(Actor201* this) {
    if ((fabsf(this->obj.pos.x - gPlayer[0].pos.x) < 700.0f) && (fabsf(this->obj.pos.y - gPlayer[0].pos.y) < 700.0f)) {
        return true;
    }
    return false;
}

void Actor201_Update(Actor201* this) {
    f32 sp2C;

    if (Actor201_8006ABA4(this) && (this->timer_0BC == 0)) {
        func_effect_8007F11C(OBJ_EFFECT_353, this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, gEnemyShotSpeed);
        this->timer_0BC = 20;
    }
    sp2C = this->obj.pos.z + gPathProgress;
    this->obj.rot.y = Math_RadToDeg(Math_Atan2F(gPlayer[0].cam.eye.x - this->obj.pos.x, gPlayer[0].cam.eye.z - sp2C));
    this->obj.rot.x = -Math_RadToDeg(
        Math_Atan2F(gPlayer[0].cam.eye.y - this->obj.pos.y,
                    sqrtf(SQ(gPlayer[0].cam.eye.z - sp2C) + SQ(gPlayer[0].cam.eye.x - this->obj.pos.x))));
}

void Actor202_Update(Actor202* this) {
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

    if (((gGameFrameCount % 32) == 0)) {
        func_effect_8007F11C(OBJ_EFFECT_353, this->obj.pos.x, this->obj.pos.y + 180.0f, this->obj.pos.z,
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
            func_effect_8007BFFC(this->obj.pos.x, this->obj.pos.y + 180.0f, this->obj.pos.z, this->vel.x, this->vel.y,
                                 this->vel.z, 8.0f, 30);
            Object_Kill(&this->obj, this->sfxSource);
            func_effect_8007A6F0(&this->obj.pos, NA_SE_EN_EXPLOSION_S);
            gHitCount += this->info.bonus;
            D_ctx_80177850 = 15;
        } else {
            this->dmgType = DMG_NONE;
            this->timer_0C6 = 20;
            AUDIO_PLAY_SFX(NA_SE_EN_DAMAGE_S, this->sfxSource, 4);
            func_effect_8007D1E0(this->obj.pos.x, this->obj.pos.y + 180.0f, this->obj.pos.z, 5.0f);
        }
    }
}

void Actor194_Update(Actor194* this) {
}

static s16 D_800CFF94[16] = {
    0, 98, 96, 94, 92, 90, 88, 86, 84, 82, 80, 78, 76, 74, 72, 70,
};
static u8 D_800CFFB4[16] = { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2 };
static f32 D_800CFFC4[16] = {
    1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.99f, 0.98f, 0.94f, 0.88f, 0.8f, 1.0f,
};
static Gfx* D_800D0004[3] = { D_ENMY_SPACE_4000170, D_ENMY_SPACE_40084D0, D_ENMY_SPACE_400A630 };

void Actor194_Dying(Actor194* this) {
    Vec3f sp34;
    s32 temp_hi;

    this->counter_04E++;

    if (this->counter_04E >= 100) {
        this->counter_04E = 0;
    }

    gActor194xPos[this->unk_046][this->counter_04E] = this->obj.pos.x;
    gActor194yPos[this->unk_046][this->counter_04E] = this->obj.pos.y;
    gActor194zPos[this->unk_046][this->counter_04E] = this->obj.pos.z;
    gActor194xRot[this->unk_046][this->counter_04E] = this->obj.rot.x;
    gActor194yRot[this->unk_046][this->counter_04E] = this->obj.rot.y;
    gActor194zRot[this->unk_046][this->counter_04E] = this->obj.rot.z;

    this->obj.rot.x -= 10.0f;
    this->obj.rot.y += 3.0f;
    this->obj.rot.z += 5.0f;

    Math_Vec3fFromAngles(&sp34, this->obj.rot.x, this->obj.rot.y, 40.0f);

    this->vel.x = sp34.x;
    this->vel.y = sp34.y;
    this->vel.z = sp34.z;

    if ((this->timer_0BC == 0) && ((gGameFrameCount % 4) == 0)) {
        temp_hi = (D_800CFF94[this->unk_04A] + this->counter_04E) % 100;
        if (this->unk_04A == 0) {
            func_effect_8007D2C8(gActor194xPos[this->unk_046][temp_hi], gActor194yPos[this->unk_046][temp_hi],
                                 gActor194zPos[this->unk_046][temp_hi], 7.0f);
        } else {
            func_effect_8007D2C8(gActor194xPos[this->unk_046][temp_hi], gActor194yPos[this->unk_046][temp_hi],
                                 gActor194zPos[this->unk_046][temp_hi], 4.0f);
        }

        AUDIO_PLAY_SFX(NA_SE_EN_EXPLOSION_M, this->sfxSource, 4);
        this->unk_04A++;

        if (this->unk_04A > 15) {
            Object_Kill(&this->obj, this->sfxSource);
            gActor194Status[this->unk_046] = 0;
            gHitCount += this->info.bonus;
            D_ctx_80177850 = 15;
        }
    }
}

void Actor194_8006B46C(Actor194* this, f32 xTrans, f32 yTrans, f32 zTrans, f32 xRot, f32 yRot, f32 zRot, u8 arg7,
                       f32 scale, s32 arg9) {
    Vec3f sp34 = { 0.0f, 0.0f, 0.0f };

    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, xTrans, yTrans, zTrans + gPathProgress, MTXF_APPLY);

    if (arg7 != 1) {
        Matrix_RotateY(gGfxMatrix, M_DTOR * yRot, MTXF_APPLY);
        Matrix_RotateX(gGfxMatrix, M_DTOR * xRot, MTXF_APPLY);
        Matrix_RotateZ(gGfxMatrix, M_DTOR * zRot, MTXF_APPLY);
    }

    Matrix_Scale(gGfxMatrix, scale, scale, 1.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);

    if (arg7 != 1) {
        RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
        if ((arg7 == 0) && (this->lockOnTimers[TEAM_ID_FOX] != 0)) {
            sp34.y += this->info.targetOffset;
            Matrix_MultVec3f(gGfxMatrix, &sp34, &gLockOnTargetViewPos[TEAM_ID_FOX]);
            if (gLockOnTargetViewPos[TEAM_ID_FOX].z > -500.0f) {
                this->lockOnTimers[TEAM_ID_FOX] = 0;
            }
        }
    } else {
        RCP_SetupDL_60(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
    }

    if (arg9 != 0) {
        RCP_SetupDL_64();
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
    }

    gSPDisplayList(gMasterDisp++, D_800D0004[arg7]);
    Matrix_Pop(&gGfxMatrix);
    RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
}

void Actor194_Draw(Actor194* this) {
    s16 var_s0;
    s16 temp_hi;

    for (var_s0 = this->unk_04A; var_s0 < 16; var_s0++) {
        temp_hi = (D_800CFF94[var_s0] + this->counter_04E) % 100;
        Actor194_8006B46C(this, gActor194xPos[this->unk_046][temp_hi], gActor194yPos[this->unk_046][temp_hi],
                          gActor194zPos[this->unk_046][temp_hi], gActor194xRot[this->unk_046][temp_hi],
                          gActor194yRot[this->unk_046][temp_hi], gActor194zRot[this->unk_046][temp_hi],
                          D_800CFFB4[var_s0], D_800CFFC4[var_s0], this->timer_0C6 % 2U);
    }
}

void Scenery42_Update(Scenery_42* this) {
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

void func_enmy2_8006BA64(Effect* effect, f32 xPos, f32 yPos, f32 zPos) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = OBJ_EFFECT_375;

    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;

    effect->scale2 = 0.0f;
    effect->scale1 = 0.12f;
    effect->obj.rot.y = RAND_FLOAT(360.0f);
    effect->unk_60.y = RAND_FLOAT_CENTERED(3.0f);
    Object_SetInfo(&effect->info, effect->obj.id);
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

void Actor196_Update(Actor196* this) {
    Vec3f sp44;

    switch (this->state) {
        case 0:
            this->fwork[10] = RAND_FLOAT_CENTERED(1000.0f);
            this->state = 1;
            break;

        case 1:
            switch (this->unk_046) {
                case 0:
                    this->fwork[0] += 2.0f;
                    if (this->fwork[0] > 10.0f) {
                        this->unk_046 = 1;
                    }
                    break;

                case 1:
                    this->fwork[0] -= 2.0f;
                    if (this->fwork[0] < -10.0f) {
                        this->unk_046 = 0;
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
                func_effect_8007F11C(OBJ_EFFECT_353, this->obj.pos.x, this->obj.pos.y, this->obj.pos.z,
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
        func_effect_8007BFFC(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 0.0f, this->vel.y, 0.0f, 3.0f, 5);
        Object_Kill(&this->obj, this->sfxSource);
        this->itemDrop = DROP_SILVER_RING;
        Actor_Despawn(this);
    }
    this->dmgType = DMG_NONE;
}

static f32 D_800D001C[5] = { 0.0f, 30.0f, 60.0f, -60.0f, -30.0f }; // could be in-function
void func_enmy2_8006BF7C(f32 xPos, f32 yPos, f32 zPos) {
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

static Vec3f D_800D0030 = { 0.0f, -10.0f, 0.0f }; // could be in-function
void ActorDebris_Update(ActorDebris* this) {
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    s32 sp40;

    switch (this->state) {
        case 40:
            if (this->unk_04A & 4) {
                this->obj.pos.x = gPlayer[0].pos.x + this->fwork[3];
                this->obj.pos.z = gPlayer[0].trueZpos + this->fwork[4];
            }

            this->obj.rot.x += this->fwork[0];
            this->obj.rot.y += this->fwork[1];
            this->obj.rot.z += this->fwork[2];

            if (((this->unk_04A % 2U) == 1) && ((this->timer_0BC & 3) == 0)) {
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
                    if (this->unk_04A & 4) {
                        switch (this->unk_046) {
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
                        if (this->unk_04A & 2) {
                            this->vel.y = this->vel.y * -0.05f;
                        } else {
                            this->vel.y = this->vel.y * -0.3f;
                        }
                    }
                }
                this->unk_04A &= ~4;
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
                if ((this->iwork[1] == 1) && ((this->unk_048 == 8) || (this->unk_048 == 9))) {
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
                func_effect_8007B8F8(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + 50.0f, this->scale * 10.0f);
                Object_Kill(&this->obj, this->sfxSource);
                func_effect_8007A6F0(&this->obj.pos, NA_SE_EN_EXPLOSION_S);
            }
            break;

        case 56:
            Math_SmoothStepToF(&this->scale, 0.0f, 0.1f, 2.0f, 0.0001f);
            if (((this->timer_0BC == 0) || (Object_CheckCollision(this->index, &this->obj.pos, &D_800D0030, 1) != 0) ||
                 (this->obj.pos.y < (gGroundHeight + 10.0f))) &&
                (this->timer_0BE == 0)) {
                func_effect_8007B8F8(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + 50.0f, this->scale * 10.0f);
                Object_Kill(&this->obj, this->sfxSource);
                func_effect_8007A6F0(&this->obj.pos, NA_SE_EN_EXPLOSION_S);
            }
            break;

        case 58:
            if (this->unk_046 == 0) {
                this->unk_046++;
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
                func_effect_8007B8F8(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + 50.0f, this->scale * 10.0f);
                Object_Kill(&this->obj, this->sfxSource);
                func_effect_8007A6F0(&this->obj.pos, NA_SE_EN_EXPLOSION_S);
            }
            break;

        case 54:
            if (((this->timer_0BC == 0) || (Object_CheckCollision(this->index, &this->obj.pos, &D_800D0030, 1) != 0) ||
                 (this->obj.pos.y < (gGroundHeight + 10.0f))) &&
                (this->timer_0BE == 0)) {
                func_effect_8007B8F8(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + 70.0f, this->scale * 20.0f);
                func_effect_8007B8F8(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + 70.0f, this->scale * 20.0f);
                Object_Kill(&this->obj, this->sfxSource);
                func_effect_8007A6F0(&this->obj.pos, NA_SE_EN_EXPLOSION_S);
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
            if (this->unk_046 == 0) {
                this->unk_046++;
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
                    func_effect_8007A6F0(&this->obj.pos, NA_SE_EN_EXPLOSION_S);
                }
            } else if (((this->state >= 41) && (this->state < 45)) || (this->state == 59)) {
                if (((this->timer_0BC == 0) ||
                     (Object_CheckCollision(this->index, &this->obj.pos, &D_800D0030, 1) != 0)) &&
                    (this->timer_0BE == 0)) {
                    func_effect_8007D0E0(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 2.0f * this->scale);
                    Object_Kill(&this->obj, this->sfxSource);
                    func_effect_8007A6F0(&this->obj.pos, NA_SE_EN_EXPLOSION_S);
                }
                if (Play_CheckDynaFloorCollision(&sp44, &sp40, this->obj.pos.x, this->obj.pos.y, this->obj.pos.z)) {
                    func_effect_8007B228(this->obj.pos.x, sp44, this->obj.pos.z, 2.0f);
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
                    func_effect_8007BFFC(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, this->vel.x, this->vel.y,
                                         this->vel.z, this->scale * 1.5f, 4);
                    Object_Kill(&this->obj, this->sfxSource);
                    func_effect_8007A6F0(&this->obj.pos, NA_SE_EN_EXPLOSION_S);
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
                        func_effect_8007BC7C(RAND_FLOAT_CENTERED(10.0f) + this->obj.pos.x, this->obj.pos.y,
                                             this->obj.pos.z, 1.0f);
                        func_effect_8007BC7C(RAND_FLOAT_CENTERED(10.0f) + this->obj.pos.x, this->obj.pos.y,
                                             this->obj.pos.z, 1.0f);
                        func_effect_8007BC7C(RAND_FLOAT_CENTERED(10.0f) + this->obj.pos.x, this->obj.pos.y,
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

void MeteoTunnel_Update(MeteoTunnel* this) {
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

static EventActorInfo sEventActorInfo[108] = {
    /*   0 */ { D_ENMY_PLANET_40068F0, gCubeHitbox100, 1.0f, 100.0f, 3000.0f, 1, 0, EISFX_EN_ENGINE_01, 0, 1.0f, 1 },
    /*   1 */ { D_ENMY_PLANET_4006E90, gCubeHitbox100, 1.0f, 100.0f, 3000.0f, 1, 0, EISFX_EN_ENGINE_01, 0, 1.0f, 1 },
    /*   2 */ { NULL, gCubeHitbox100, 1.0f, 20000.0f, 3000.0f, 1, 0, EISFX_ARWING_ENGINE_FG, 0, 0.0f, 0 },
    /*   3 */ { D_ENMY_PLANET_4009800, gCubeHitbox100, 1.5f, 100.0f, 3000.0f, 1, 0, EISFX_NONE, 0, 1.0f, 1 },
    /*   4 */ { D_ENMY_PLANET_40073C0, gCubeHitbox100, 1.0f, 100.0f, 3000.0f, 1, 0, EISFX_EN_ENGINE_01, 0, 1.0f, 1 },
    /*   5 */ { D_ENMY_PLANET_4007AF0, gCubeHitbox100, 1.0f, 100.0f, 3000.0f, 1, 0, EISFX_EN_ENGINE_01, 0, 1.0f, 1 },
    /*   6 */ { NULL, gCubeHitbox100, 1.0f, 100.0f, 3000.0f, 1, 0, EISFX_NONE, 0, 1.0f, 1 },
    /*   7 */ { D_CO_6011F90, gCubeHitbox100, 1.0f, 100.0f, 3000.0f, 1, 0, EISFX_EN_ENGINE_01, 0, 0.0f, 1 },
    /*   8 */ { D_ENMY_PLANET_4000710, gCubeHitbox100, 1.0f, 100.0f, 3000.0f, 2, 0, EISFX_EN_ENGINE_01, 1, 1.0f, 1 },
    /*   9 */ { NULL, gCubeHitbox100, 1.5f, 100.0f, 3000.0f, 1, 0, EISFX_EN_ALIEN_FLY, 0, 1.0f, 1 },
    /*  10 */ { D_ENMY_SPACE_400BD20, gCubeHitbox200, 2.0f, 100.0f, 3000.0f, 1, 0, EISFX_EN_ENGINE_01, 0, 1.0f, 1 },
    /*  11 */ { D_ENMY_SPACE_4001310, gCubeHitbox100, 1.5f, 100.0f, 3000.0f, 1, 0, EISFX_EN_ALIEN_FLY, 0, 1.0f, 1 },
    /*  12 */ { D_ENMY_SPACE_400B390, gCubeHitbox100, 2.0f, 100.0f, 3000.0f, 1, 0, EISFX_EN_ENGINE_01, 0, 1.0f, 1 },
    /*  13 */ { D_ME_6018C00, gCubeHitbox100, 2.5f, 100.0f, 3000.0f, 1, 0, EISFX_EN_ENGINE_01, 0, 1.0f, 1 },
    /*  14 */ { D_ME_601F2A0, gCubeHitbox400, 7.0f, 100.0f, 3000.0f, 1, 0, EISFX_EN_ENGINE_01, 0, 1.0f, 1 },
    /*  15 */ { D_ENMY_SPACE_400AAE0, gCubeHitbox100, 1.5f, 100.0f, 3000.0f, 1, 0, EISFX_EN_ENGINE_01, 0, 1.0f, 1 },
    /*  16 */ { D_ENMY_SPACE_4000650, gCubeHitbox100, 1.5f, 100.0f, 3000.0f, 1, 0, EISFX_EN_ALIEN_FLY, 0, 1.0f, 1 },
    /*  17 */ { D_A6_6016190, D_A6_60282A0, -2.0f, 2100.0f, 3000.0f, 0, 0, EISFX_EN_SPACE_SHIP, 0, 0.0f, 5 },
    /*  18 */ { D_SX_6023500, gCubeHitbox200, 2.0f, 100.0f, 3000.0f, 1, 0, EISFX_EN_ENGINE_01, 0, 1.0f, 1 },
    /*  19 */ { D_SX_6022DF0, gCubeHitbox100, 1.5f, 100.0f, 3000.0f, 1, 0, EISFX_EN_ENGINE_01, 0, 1.0f, 1 },
    /*  20 */ { NULL, gCubeHitbox100, 1.0f, 100.0f, 3000.0f, 2, 1, EISFX_EN_ENGINE_01, 0, 0.0f, 1 },
    /*  21 */ { NULL, gCubeHitbox200, 2.0f, 100.0f, 3000.0f, 1, 0, EISFX_EN_ENGINE_01, 0, 0.0f, 1 },
    /*  22 */ { NULL, gCubeHitbox100, 1.5f, 100.0f, 3000.0f, 1, 0, EISFX_EN_ENGINE_01, 0, 0.0f, 1 },
    /*  23 */ { D_ENMY_SPACE_4008FA0, gCubeHitbox100, 1.5f, 100.0f, 3000.0f, 1, 0, EISFX_EN_ENGINE_01, 0, 1.0f, 1 },
    /*  24 */ { D_SX_60285F0, D_SX_603298C, -1.0f, 2100.0f, 3001.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  25 */ { D_SX_600AF70, D_SX_6032904, -1.0f, 2100.0f, 3001.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  26 */ { D_SX_6023E30, D_SX_6032970, -1.0f, 2100.0f, 3001.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  27 */ { NULL, D_SX_603285C, 2.5f, 100.0f, 3000.0f, 2, 0, EISFX_NONE, 0, 1.0f, 1 },
    /*  28 */ { D_SX_6001CE0, D_SX_6032938, 3.0f, 100.0f, 3000.0f, 2, 0, EISFX_NONE, 0, 1.0f, 1 },
    /*  29 */ { D_SX_6000840, D_SX_6032954, 1.0f, 100.0f, 3000.0f, 2, 1, EISFX_NONE, 0, 1.0f, 1 },
    /*  30 */ { D_A6_6012A40, D_A6_6028254, -2.0f, 2100.0f, 3001.0f, 0, 0, EISFX_EN_SPACE_SHIP, 0, 0.0f, 2 },
    /*  31 */ { NULL, D_A6_60280E0, -2.0f, 2100.0f, 3001.0f, 0, 0, EISFX_NONE, 0, 0.0f, 3 },
    /*  32 */ { D_SX_6009950, D_SX_6032878, -1.0f, 2100.0f, 3001.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  33 */ { NULL, gCubeHitbox200, 2.0f, 100.0f, 3000.0f, 1, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  34 */ { D_SX_600B2B0, D_SX_6032894, -1.0f, 2100.0f, 3001.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  35 */ { D_SX_600A2E0, D_SX_60328B0, -1.0f, 2100.0f, 3001.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  36 */ { NULL, gCubeHitbox400, 2.0f, 200.0f, 3000.0f, 1, 0, EISFX_EN_ENGINE_01, 0, 1.0f, 1 },
    /*  37 */ { D_SX_600B830, gCubeHitbox100, 1.5f, 100.0f, 3000.0f, 1, 0, EISFX_EN_ENGINE_01, 0, 1.0f, 1 },
    /*  38 */ { NULL, D_SX_603238C, 1.0f, 500.0f, 3000.0f, 1, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  39 */ { D_SX_6020D20, D_SX_60328CC, -1.0f, 2100.0f, 3001.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  40 */ { NULL, gNoHitbox, 1.0f, 100.0f, 3001.0f, 2, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  41 */ { D_SY_60097E0, D_SY_6034478, -1.0f, 10000.0f, 3001.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  42 */ { D_SY_601D730, D_SY_603450C, -1.0f, 10000.0f, 3001.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  43 */ { NULL, gCubeHitbox100, 1.0f, 20000.0f, 3000.0f, 1, 0, EISFX_ARWING_ENGINE_FG, 0, 0.0f, 0 },
    /*  44 */ { D_SY_60102C0, D_SY_6034588, -1.0f, 10000.0f, 3001.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  45 */ { D_ME_6017B60, gCubeHitbox200, -1.0f, 300.0f, 3001.0f, 0, 0, EISFX_NONE, 0, 1.0f, 1 },
    /*  46 */ { D_ZO_6004D00, gCubeHitbox200, 1.0f, 100.0f, 3000.0f, 1, 0, EISFX_EN_SHIP_ENGINE_S, 0, 1.0f, 1 },
    /*  47 */ { D_ME_601A880, gCubeHitbox100, -1.0f, 100.0f, 3000.0f, 1, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  48 */ { NULL, D_SY_603405C, 0.3f, 100.0f, 3000.0f, 0, 0, EISFX_EN_ENGINE_01, 0, 1.0f, 1 },
    /*  49 */ { NULL, D_SY_603405C, 0.3f, 100.0f, 3000.0f, 0, 0, EISFX_EN_ENGINE_01, 0, 1.0f, 1 },
    /*  50 */ { NULL, D_SY_603405C, 0.3f, 100.0f, 3000.0f, 0, 0, EISFX_EN_ENGINE_01, 0, 1.0f, 1 },
    /*  51 */ { D_SY_6015D60, D_SY_6034124, 2.0f, 100.0f, 3000.0f, 0, 0, EISFX_EN_ENGINE_01, 0, 1.0f, 1 },
    /*  52 */ { NULL, D_ZO_602C1A0, -1.0f, 1000.0f, 3000.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  53 */ { D_SX_600B540, D_SX_60328E8, -1.0f, 2100.0f, 3001.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  54 */ { D_ENMY_SPACE_4000EC0, gCubeHitbox100, 1.5f, 100.0f, 3000.0f, 1, 0, EISFX_EN_ENGINE_01, 0, 1.0f, 1 },
    /*  55 */ { D_ENMY_SPACE_4008D50, gCubeHitbox100, 1.5f, 100.0f, 3000.0f, 1, 0, EISFX_EN_ENGINE_01, 0, 1.0f, 1 },
    /*  56 */ { NULL, gNoHitbox, -1.0f, 2000.0f, 3000.0f, 0, 0, EISFX_GREATFOX_ENGINE, 0, 0.0f, 1 },
    /*  57 */ { D_SY_60102C0, gNoHitbox, -1.0f, 10000.0f, 3001.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  58 */ { D_SY_601F3D0, gNoHitbox, -1.0f, 10000.0f, 3001.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  59 */ { D_SY_6022B10, gNoHitbox, 2.0f, 100.0f, 3000.0f, 0, 0, EISFX_EN_ENGINE_01, 0, 0.0f, 1 },
    /*  60 */ { D_SY_60209F0, gNoHitbox, 2.0f, 100.0f, 3000.0f, 0, 0, EISFX_EN_ENGINE_01, 0, 0.0f, 1 },
    /*  61 */ { D_ME_6019430, gCubeHitbox200, 2.5f, 100.0f, 3000.0f, 1, 0, EISFX_NONE, 0, 1.0f, 1 },
    /*  62 */ { D_ME_6018960, gCubeHitbox100, 2.5f, 100.0f, 3000.0f, 1, 0, EISFX_NONE, 0, 1.0f, 1 },
    /*  63 */ { D_ME_6009F50, gNoHitbox, -1.0f, 100.0f, 3000.0f, 1, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  64 */ { NULL, gCubeHitbox200, 3.0f, 100.0f, 3000.0f, 1, 0, EISFX_NONE, 0, 1.0f, 1 },
    /*  65 */ { D_ME_600C2A0, gCubeHitbox200, -1.0f, 100.0f, 8000.0f, 1, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  66 */ { D_ME_600BD40, gCubeHitbox100, -1.0f, 100.0f, 8000.0f, 1, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  67 */ { NULL, D_ME_602F604, 3.0f, 100.0f, 3000.0f, 2, 0, EISFX_EN_ENGINE_01, 0, 1.0f, 1 },
    /*  68 */ { D_SY_60205D0, D_SY_603445C, 3.0f, 100.0f, 3000.0f, 1, 0, EISFX_NONE, 0, 1.0f, 1 },
    /*  69 */ { D_SY_60036A0, D_SY_6034664, -1.0f, 10000.0f, 3001.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  70 */ { D_SY_601AD70, gNoHitbox, 4.0f, 100.0f, 3000.0f, 0, 0, EISFX_EN_ENGINE_01, 0, 0.0f, 1 },
    /*  71 */ { D_arwing_3007650, gNoHitbox, 1.0f, 100.0f, 3000.0f, 2, 0, EISFX_OB_WING, 0, 0.0f, 1 },
    /*  72 */ { D_SY_60034D0, D_SY_60347D4, 3.0f, 100.0f, 3000.0f, 1, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  73 */ { D_SY_6005360, D_SY_6034770, -1.0f, 10000.0f, 3001.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  74 */ { D_SY_600F6C0, D_SY_60347F0, -1.0f, 10000.0f, 3001.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  75 */ { D_SY_601B610, gNoHitbox, -1.0f, 10000.0f, 3001.0f, 0, 0, EISFX_EN_ENGINE_01, 0, 0.0f, 1 },
    /*  76 */ { D_SY_601C6A0, gNoHitbox, -1.0f, 10000.0f, 3001.0f, 0, 0, EISFX_EN_ENGINE_01, 0, 0.0f, 1 },
    /*  77 */ { D_SY_60188D0, D_SY_603486C, 3.0f, 100.0f, 3001.0f, 0, 0, EISFX_EN_ENGINE_01, 0, 0.0f, 1 },
    /*  78 */ { NULL, gCubeHitbox150, 1.0f, 100.0f, 3000.0f, 2, 0, EISFX_NONE, 0, 1.0f, 0 },
    /*  79 */ { NULL, D_ZO_602C294, 1.0f, 100.0f, 3000.0f, 0, 0, EISFX_NONE, 0, 1.0f, 1 },
    /*  80 */ { NULL, D_VE1_601B474, -1.0f, 100.0f, 3000.0f, 2, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  81 */ { NULL, gNoHitbox, -1.0f, 100.0f, 3000.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  82 */ { NULL, gCubeHitbox100, 2.0f, 100.0f, 3000.0f, 1, 0, EISFX_EN_ENGINE_01, 0, 1.0f, 1 },
    /*  83 */ { NULL, D_AQ_6030B4C, 1.0f, 100.0f, 3000.0f, 2, 0, EISFX_NONE, 0, 60.0f, 1 },
    /*  84 */ { D_VE1_9012180, D_VE1_601B43C, -1.0f, 100.0f, 3000.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  85 */ { NULL, gCubeHitbox100, 1.0f, 20000.0f, 3000.0f, 1, 0, EISFX_ARWING_ENGINE_FG, 0, 0.0f, 0 },
    /*  86 */ { NULL, gCubeHitbox100, 1.0f, 20000.0f, 3000.0f, 1, 0, EISFX_ARWING_ENGINE_FG, 0, 0.0f, 0 },
    /*  87 */ { D_VE1_900EFC0, gNoHitbox, 1.0f, 100.0f, 3000.0f, 1, 1, EISFX_NONE, 0, 0.0f, 1 },
    /*  88 */ { NULL, D_AQ_6030B30, 1.0f, 100.0f, 3000.0f, 1, 0, EISFX_NONE, 0, 1.0f, 1 },
    /*  89 */ { NULL, D_AQ_6030B14_f32, 1.0f, 100.0f, 3000.0f, 1, 0, EISFX_NONE, 0, 1.0f, 1 },
    /*  90 */ { D_MA_601C520, D_MA_60368FC, 1.0f, 100.0f, 3000.0f, 1, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  91 */ { D_MA_600AF40, D_MA_60368E0, -1.0f, 100.0f, 3000.0f, 1, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  92 */ { D_WZ_7000C40, gWarpZoneEvent92Hitbox, -1.0f, 2100.0f, 3001.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  93 */ { D_WZ_70010E0, gWarpZoneEvent93Hitbox, -1.0f, 2100.0f, 3001.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  94 */ { D_WZ_7000E80, gWarpZoneEvent94Hitbox, 2.5f, 100.0f, 3000.0f, 1, 0, EISFX_NONE, 0, 1.0f, 1 },
    /*  95 */ { D_WZ_70008F0, gCubeHitbox100, -1.0f, 100.0f, 8000.0f, 1, 0, EISFX_NONE, 0, 0.0f, 0 },
    /*  96 */ { D_WZ_7000280, gWarpZoneEvent96Hitbox, -1.0f, 1000.0f, 3000.0f, 1, 0, EISFX_NONE, 0, 0.0f, 0 },
    /*  97 */ { D_ME_600AC70, gCubeHitbox100, -1.0f, 100.0f, 3000.0f, 1, 0, EISFX_NONE, 0, 0.0f, 1 },
    /*  98 */ { D_MA_601A2B0, D_MA_60364C0, 1.0f, 100.0f, 3000.0f, 1, 1, EISFX_NONE, 0, 0.0f, 1 },
    /*  99 */ { D_VE1_6002500, D_VE1_601B944, -1.0f, 100.0f, 3000.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /* 100 */ { D_VE1_60043F0, gNoHitbox, -1.0f, 100.0f, 3000.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /* 101 */ { D_VE1_6004310, gNoHitbox, -1.0f, 100.0f, 3000.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /* 102 */ { D_TR_6002740, D_TR_6009D18, -1.0f, 100.0f, 3000.0f, 0, 0, EISFX_NONE, 0, 0.0f, 1 },
    /* 103 */ { NULL, gNoHitbox, -1.0f, 500.0f, 3000.0f, 0, 0, EISFX_NONE, 0, 0.0f, 0 },
    /* 104 */ { NULL, gNoHitbox, -1.0f, 500.0f, 3000.0f, 0, 0, EISFX_NONE, 0, 0.0f, 0 },
    /* 105 */ { NULL, gCubeHitbox200, 1.0f, 100.0f, 3000.0f, 0, 0, EISFX_NONE, 0, 1.0f, 1 },
    /* 106 */ { NULL, gCubeHitbox100, 1.0f, 100.0f, 3000.0f, 0, 0, EISFX_EN_ALIEN_FLY, 0, 0.0f, 0 },
    /* 107 */ { D_MA_6002890, D_MA_60368E0, -1.0f, 100.0f, 3000.0f, 1, 0, EISFX_NONE, 0, 0.0f, 1 },
};

static Color_RGBA32 sEventTexLineColors[6] = {
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

            if ((this->eventType == EVID_64) || (this->eventType == EVID_81)) {
                this->fwork[15] = 0.0f;
            } else if (this->eventType == EVID_79) {
                this->info.drawType = 2;
            }

            this->health = actorScript[this->aiIndex] & 0x1FF;
            this->aiIndex += 2;

            if ((this->eventType >= EVID_200) && (this->eventType < EVID_300)) {
                this->unk_046 = 100;
                this->info.hitbox = gCubeHitbox200;
                this->info.targetOffset = 1.0f;

                for (i = 0; i < 2; i++) {
                    if (gActor194Status[i] == 0) {
                        gActor194Status[i] = 1;
                        this->unk_046 = i;
                        for (j = 0; j < 100; j++) {
                            gActor194yPos[i][j] = this->obj.pos.y;
                            gActor194zPos[i][j] = this->obj.pos.z;
                        }
                        if (this->eventType == EVID_200) {
                            AUDIO_PLAY_SFX(NA_SE_EN_SPACE_SNAKE, this->sfxSource, 4);
                        }
                        break;
                    }
                }

                if (this->unk_046 == 100) {
                    Object_Kill(&this->obj, this->sfxSource);
                }
            }

            if ((this->eventType == EVID_2) || (this->eventType == EVID_TEAMMATE)) {
                this->drawShadow = true;
                this->iwork[11] = 1;
            }

            if (this->eventType == EVID_81) {
                this->drawShadow = true;
            }

            if (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_ACTIVE) {
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
                this->animFrame = Animation_GetFrameCount(&D_VE2_6014658) - 1;
            }

            if (this->eventType < EVID_200) {
                this->info.hitbox = LOAD_ASSET(sEventActorInfo[this->eventType].hitbox);
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
                        if (!((gCurrentLevel == LEVEL_SOLAR) || (this->eventType == EVID_6) ||
                              ((gCurrentLevel == LEVEL_CORNERIA) && (this->eventType == EVID_8)))) {
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
                    if (this->eventType != EVID_31) {
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

            this->unk_048 = actorScript[this->aiIndex + 1];

            if (this->unk_048 == EVACT_3) {
                this->timer_04C = 4;
            }

            if (this->unk_048 == EVACT_TI_DROP_MINE) {
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
            if ((msg != NULL) && (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_ACTIVE)) {
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
    actor->obj.id = OBJ_ACTOR_225;

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
    func_effect_8007A6F0(&effect->obj.pos, NA_SE_EN_EXPLOSION_M);
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
    func_effect_8007A6F0(&effect->obj.pos, NA_SE_EN_EXPLOSION_M);
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
    func_effect_8007F04C(OBJ_EFFECT_353, this->obj.pos.x + sp48.x, this->obj.pos.y + sp48.y, this->obj.pos.z + sp48.z,
                         this->obj.rot.x, this->obj.rot.y, this->obj.rot.z, this->vwork[29].x, this->vwork[29].y,
                         this->vwork[29].z + this->rot_0F4.z, sp48.x, sp48.y, sp48.z, 1.0f);
}

void ActorEvent_ProcessActions(ActorEvent* this) {
    s32 i;
    Vec3f sp78;
    Vec3f sp6C;
    Sprite* sprite;

    if ((gPlayer[0].state_1C8 == PLAYERSTATE_1C8_ACTIVE) && (this->eventType != EVID_52) &&
        (this->eventType != EVID_ANDROSS_GATE) && (this->eventType != EVID_ANDROSS_GATE_2) &&
        (this->eventType != EVID_48) && (this->eventType != EVID_49) && (this->eventType != EVID_50)) {
        switch (this->unk_048) {
            case EVACT_NONE:
                break;

            case EVACT_1: // shoot forward
                ActorEvent_8006F254(this);
                this->unk_048 = EVACT_NONE;
                break;

            case EVACT_2: // shoot at player
                if (this->obj.pos.z < (gPlayer[0].trueZpos - 600.0f)) {
                    func_effect_8007F11C(OBJ_EFFECT_353, this->obj.pos.x, this->obj.pos.y, this->obj.pos.z,
                                         gEnemyShotSpeed);
                }
                this->unk_048 = EVACT_NONE;
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
                    this->timer_04C--;
                    if (this->timer_04C <= 0) {
                        this->unk_048 = EVACT_NONE;
                    }
                }
                break;

            case EVACT_4: // shoot blue energy balls
                ActorEvent_SpawnEffect374(this->obj.pos.x, this->obj.pos.y - 20.0f, this->obj.pos.z);
                this->unk_048 = EVACT_NONE;
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
                this->unk_048 = EVACT_NONE;
                break;

            case EVACT_6:
                if (this->obj.pos.z < (gPlayer[0].trueZpos - 600.0f)) {
                    func_effect_8007F11C(OBJ_EFFECT_355, this->obj.pos.x, this->obj.pos.y, this->obj.pos.z,
                                         gEnemyShotSpeed);
                }
                this->unk_048 = EVACT_NONE;
                break;

            case EVACT_7:
                if (this->obj.pos.z < (gPlayer[0].trueZpos - 600.0f)) {
                    func_effect_8007F11C(OBJ_EFFECT_356, this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 60.0f);
                }
                this->unk_048 = EVACT_NONE;
                break;

            case EVACT_8:
                sp6C.x = gPlayer[0].pos.x;
                sp6C.y = gPlayer[0].pos.y;
                gPlayer[0].pos.x += RAND_FLOAT_CENTERED(300.0f);
                gPlayer[0].pos.y += RAND_FLOAT_CENTERED(300.0f);
                func_effect_8007F11C(OBJ_EFFECT_353, this->obj.pos.x, this->obj.pos.y, this->obj.pos.z,
                                     gEnemyShotSpeed);
                gPlayer[0].pos.x = sp6C.x;
                gPlayer[0].pos.y = sp6C.y;
                this->unk_048 = EVACT_NONE;
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
                func_effect_8007BFFC(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, this->vel.x, this->vel.y,
                                     this->vel.z, this->scale * 3.0f, 15);
                Actor_Despawn(this);
                Object_Kill(&this->obj, this->sfxSource);
                func_effect_8007A6F0(&this->obj.pos, NA_SE_EN_EXPLOSION_M);
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
                    this->unk_048 = EVACT_NONE;
                }
                break;

            case EVACT_16:
                func_effect_8007F11C(OBJ_EFFECT_353, this->obj.pos.x + 190.0f, this->obj.pos.y + 90.0f,
                                     this->obj.pos.z + 220.0f, gEnemyShotSpeed);
                func_effect_8007F11C(OBJ_EFFECT_353, this->obj.pos.x - 190.0f, this->obj.pos.y + 90.0f,
                                     this->obj.pos.z + 220.0f, gEnemyShotSpeed);
                this->unk_048 = EVACT_NONE;
                break;

            case EVACT_17:
                if (this->obj.pos.z < (gPlayer[0].cam.eye.z - 600.0f)) {
                    func_effect_8007F20C(OBJ_EFFECT_353, this->obj.pos.x, this->obj.pos.y, this->obj.pos.z,
                                         gEnemyShotSpeed);
                }
                this->unk_048 = EVACT_NONE;
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

                this->unk_048 = EVACT_NONE;
                break;

            case EVACT_19: // projectile ring used by bee enemies
                func_effect_80083D2C(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 40.0f);
                this->unk_048 = EVACT_NONE;
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
                Zoness_SpawnDebris(&this->vwork[i], &this->vwork[i + 11], RAND_FLOAT_CENTERED(20.0f),
                                   RAND_FLOAT(-10.0f), RAND_FLOAT(10.0f), 41, this->scale, 200, i);
            }
            this->itemDrop = DROP_NONE;
            Actor_Despawn(this);
            Object_Kill(&this->obj, this->sfxSource);
            func_effect_8007A6F0(&this->obj.pos, NA_SE_EN_BIRD_DOWN);
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
    if ((this->dmgType != DMG_NONE) && (this->eventType == EVID_METEO_PYRAMID_SHIP) && (this->dmgPart == 0)) {
        this->dmgType = DMG_NONE;
    }

    if ((this->dmgType != DMG_NONE) && (this->eventType == EVID_AQ_CLAM) && (this->timer_0C2 >= 2)) {
        this->dmgType = DMG_NONE;
    }

    if ((this->dmgType != DMG_NONE) &&
        (((this->eventType == EVID_64) && (this->dmgPart == 2)) || (this->eventType != EVID_64))) {
        if (this->iwork[12] >= TEAM_ID_KATT) {
            this->damage = 0;
        }

        if ((this->iwork[12] >= TEAM_ID_FALCO) && (this->iwork[12] <= TEAM_ID_PEPPY)) {
            gTeamShields[this->iwork[12]] -= this->damage;
        } else if ((this->eventType == EVID_AQ_CLAM) && ((this->damage == 30) || (this->damage == 31))) {
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

            if (this->eventType != EVID_AQ_CLAM) {
                if ((this->eventType == EVID_6) && (gCurrentLevel == LEVEL_SOLAR)) {
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
                    (this->eventType != EVID_13) && (this->eventType != EVID_14) && (this->eventType != EVID_61) &&
                    (this->damage <= 30) && (this->eventType != EVID_62) && (this->eventType != EVID_64) &&
                    (this->eventType != EVID_72) && (this->eventType != EVID_68)) {
                    func_effect_8007D2C8(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, this->scale * 4.0f);
                    this->dmgType = DMG_NONE;
                }

                this->timer_0C2 = 10;
                this->timer_0BE = 0;
                this->unk_046 = 255;
                this->unk_048 = 900;
                this->drawShadow = true;

                if (gLevelType == LEVELTYPE_PLANET) {
                    this->timer_04C = RAND_INT(2.9f);
                    if (this->eventType == EVID_2) {
                        this->timer_04C = 1;
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

                    if (this->eventType == EVID_90) {
                        this->timer_04C = 999;
                    }
                } else {
                    switch (this->eventType) {
                        case EVID_13:
                            func_enmy_800654E4(&this->obj);
                            break;

                        case EVID_61:
                            Meteo_8018CCF8(this);
                            break;

                        case EVID_27:
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
                            this->timer_04C = 2;
                            this->vel.y = RAND_FLOAT_CENTERED(20.0f);
                            this->vel.x = RAND_FLOAT_CENTERED(20.0f);
                            this->vel.z = 0.0f;
                            break;
                    }
                }
            }

            if (this->eventType == EVID_82) {
                AUDIO_PLAY_SFX(NA_SE_OB_SMOKE, this->sfxSource, 0);
                this->dmgType = DMG_BEAM;
                func_effect_8007C688(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 3.0f, 60);
            }
        } else {
            this->timer_0C6 = 20;
            if ((this->eventType == EVID_6) && (gCurrentLevel == LEVEL_SOLAR)) {
                AUDIO_PLAY_SFX(NA_SE_EN_BIRD_DAMAGE, this->sfxSource, 4);
            } else if (this->health < 20) {
                AUDIO_PLAY_SFX(NA_SE_EN_KNOCK_DOWN, this->sfxSource, 4);
            } else {
                AUDIO_PLAY_SFX(NA_SE_EN_DAMAGE_S, this->sfxSource, 4);
            }

            if ((this->eventType != EVID_13) && (this->eventType != EVID_61) && (this->eventType != EVID_AQ_CLAM)) {
                func_effect_8007D10C(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, this->scale * 1.5f);
            }

            if (((gLevelMode == LEVELMODE_ALL_RANGE) || (gLevelMode == LEVELMODE_UNK_2)) &&
                (this->eventType != EVID_A6_MISSILE) && (this->eventType != EVID_23)) {
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
            if (this->eventType == EVID_13) {
                this->obj.id = OBJ_ACTOR_182;
                func_enmy_800654E4(&this->obj);
            }

            if (this->eventType == EVID_61) {
                Meteo_8018CCF8(this);
            }
        }
    }
}

void ActorEvent_80070BA8(ActorEvent* this) {
    if (this->dmgType != DMG_NONE) {
        this->dmgType = DMG_NONE;
        if ((this->eventType != EVID_17) || ((this->eventType == EVID_17) && (this->dmgPart == 0))) {
            this->timer_0C6 = 10;
            func_effect_8007C120(this->hitPos.x, this->hitPos.y, this->hitPos.z, this->vel.x, this->vel.y, this->vel.z,
                                 0.2f, 10);
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
    s32 var_v1 = 0;
    s32 var_v1_4;
    Actor* otherActor;

    for (i = TEAM_ID_FALCO; i <= TEAM_ID_PEPPY; i++) {
        if (gTeamShields[i] > 0) {
            var_v1++;
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
            if (var_v1 == 3) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_TEAM_COUNT_2:
            if (var_v1 == 2) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_TEAM_COUNT_1:
            if (var_v1 == 1) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_TEAM_COUNT_0:
            if (var_v1 == 0) {
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
            if (gPlayer[0].wings.unk_14 > -8.0f) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_TWIN_LASER:
            if ((gPlayer[0].wings.unk_14 < -8.0f) && (gLaserStrength[0] == LASERS_TWIN)) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_HYPER_LASER:
            if ((gPlayer[0].wings.unk_14 < -8.0f) && (gLaserStrength[0] == LASERS_HYPER)) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_UNK3_LASER:
            if ((gPlayer[0].wings.unk_14 < -8.0f) && (gLaserStrength[0] == LASERS_UNK_3)) {
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
            var_v1_4 = 7;
            switch (gCurrentLevel) {
                case LEVEL_CORNERIA:
                    break;
                case LEVEL_SECTOR_X:
                    var_v1_4 = 4;
                    break;
                case LEVEL_TITANIA:
                    var_v1_4 = 9;
                    break;
            }

            if (!((gCurrentLevel == LEVEL_CORNERIA) && (gTeamShields[TEAM_ID_FALCO] <= 0)) &&
                (gRingPassCount >= var_v1_4)) {
                ActorEvent_TriggerBranch(this);
            }
            break;

        case EVC_ATTACK_GROUP_CLEARED:
            for (i = 0, otherActor = gActors; i < ARRAY_COUNT(gActors); i++, otherActor++) {
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
            if ((gPlayer[0].wings.rightState <= WINGSTATE_BROKEN) || (gPlayer[0].wings.leftState <= WINGSTATE_BROKEN)) {
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
static Vec3f D_800D0DD4[56] = {
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
static Vec3f D_800D1074[24] = {
    { 100.0f, 55.0f, 450.0f },     { 117.0f, 57.0f, 738.0f },    { 14.0f, 31.0f, 894.0f },
    { 204.0f, 0.0f, -72.0f },      { 204.0f, 33.0f, -253.0f },   { 344.0f, 0.0f, -295.0f },
    { 344.0f, -51.0f, -457.0f },   { 87.0f, 124.0f, -699.0f },   { 169.0f, -40.0f, -564.0f },
    { 113.0f, -147.0f, -367.0f },  { 112.0f, -146.0f, -13.0f },  { 69.0f, -118.0f, 158.0f },
    { -100.0f, 55.0f, 450.0f },    { -117.0f, 57.0f, 738.0f },   { -14.0f, 31.0f, 894.0f },
    { -204.0f, 0.0f, -72.0f },     { -204.0f, 33.0f, -253.0f },  { -344.0f, 0.0f, -295.0f },
    { -344.0f, -51.0f, -457.0f },  { -87.0f, 124.0f, -699.0f },  { -169.0f, -40.0f, -564.0f },
    { -113.0f, -147.0f, -367.0f }, { -112.0f, -146.0f, -13.0f }, { -69.0f, -118.0f, 158.0f },
};
static Vec3f D_800D1194[21] = {
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

    if (this->eventType == EVID_30) {
        rInd = RAND_FLOAT(ARRAY_COUNT(D_800D1074) - 1.1f); // off by 1 error?
        Matrix_MultVec3fNoTranslate(gCalcMatrix, &D_800D1074[rInd], &sp38);
    }

    if (this->eventType == EVID_17) {
        rInd = RAND_FLOAT(ARRAY_COUNT(D_800D0DD4) - 0.1f);
        Matrix_MultVec3fNoTranslate(gCalcMatrix, &D_800D0DD4[rInd], &sp38);
    }

    if (this->eventType == EVID_31) {
        rInd = RAND_FLOAT(ARRAY_COUNT(D_800D1194) - 0.1f);
        Matrix_MultVec3fNoTranslate(gCalcMatrix, &D_800D1194[rInd], &sp38);
    }

    if (((gGameFrameCount % 2) == 0)) {
        func_effect_8007C120(this->obj.pos.x + sp38.x, this->obj.pos.y + sp38.y, this->obj.pos.z + sp38.z, this->vel.x,
                             this->vel.y, this->vel.z, 0.3f, 20);
    }

    if (((gGameFrameCount % 8) == 0)) {
        func_effect_8007BFFC(this->obj.pos.x + sp38.x, this->obj.pos.y + sp38.y, this->obj.pos.z + sp38.z, this->vel.x,
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
    switch (this->unk_046) {
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
                    this->unk_046 = 1;
                    this->info.hitbox = LOAD_ASSET(D_SX_6032408);
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

    if (this->unk_048 != EVACT_NONE) {
        switch (this->unk_048) {
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
        this->unk_048 = EVACT_NONE;
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

static Vec3f D_800D1290 = { 0.0f, 837.00006f, 0.0f }; // could be in-function
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

    if ((gPlayer[0].state_1C8 == PLAYERSTATE_1C8_LEVEL_COMPLETE) || gKillEventActors) {
        Object_Kill(&this->obj, this->sfxSource);
        return;
    }

    if (this->state == EVSTATE_1000) {
        this->obj.rot.y += this->fwork[15];
        this->obj.rot.x += this->fwork[16];
        if (((gGameFrameCount % 16) == 0)) {
            func_effect_8007C120(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, this->vel.x, this->vel.y,
                                 this->vel.z, 0.3f, 10);
        }
        return;
    }
    if (((this->eventType == EVID_17) || (this->eventType == EVID_30) || (this->eventType == EVID_31)) &&
        (this->health <= 0)) {
        ActorEvent_80071DC0(this);
        return;
    }
    if (this->eventType == EVID_300) {
        gPlayer[0].unk_1A4 = this->index;
        this->timer_0C2 = 100;
    } else if (this->eventType >= EVID_200) {
        this->counter_04E++;

        if (this->counter_04E >= 100) {
            this->counter_04E = 0;
        }

        gActor194xPos[this->unk_046][this->counter_04E] = this->obj.pos.x;
        gActor194yPos[this->unk_046][this->counter_04E] = this->obj.pos.y;
        gActor194zPos[this->unk_046][this->counter_04E] = this->obj.pos.z;
        gActor194xRot[this->unk_046][this->counter_04E] = this->obj.rot.x;
        gActor194yRot[this->unk_046][this->counter_04E] = this->obj.rot.y;
        gActor194zRot[this->unk_046][this->counter_04E] = this->obj.rot.z;

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
                this->obj.id = OBJ_ACTOR_194;
            }
        }
    }

    if ((this->eventType == EVID_27) && (this->timer_0C2 != 0)) {
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

            if ((this->eventType == EVID_33) || (this->eventType == EVID_68)) {
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

                    if (this->eventType == EVID_68) {
                        var_fv0 = 80.0f;
                    } else {
                        var_fv0 = 0.0f;
                    }

                    func_effect_8007F04C(OBJ_EFFECT_353, this->obj.pos.x + spAC.x + spA0.x,
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
        if ((gLevelMode == LEVELMODE_UNK_2) && (this->eventType == EVID_200)) {
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
        if ((this->eventType == EVID_13) || (this->eventType == EVID_14) || (this->eventType == EVID_61) ||
            (this->eventType == EVID_62) || (this->eventType == EVID_63) || (this->eventType == EVID_64) ||
            (this->eventType == EVID_65) || (this->eventType == EVID_66) || (this->eventType == EVID_94) ||
            (this->eventType == EVID_95) || (this->eventType == EVID_97)) {
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

    if (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_ENTER_WARP_ZONE) {
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
            if ((this->dmgType == DMG_BEAM) && (this->scale < 0.5f) && (this->eventType != EVID_48) &&
                (this->eventType != EVID_49) && (this->eventType != EVID_50)) {
                this->dmgType = DMG_NONE;
                if (gCurrentLevel == LEVEL_METEO) {
                    AUDIO_PLAY_SFX(NA_SE_ROCK_REFLECT, this->sfxSource, 4);
                } else {
                    AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
                }
            }

            if ((this->eventType < EVID_200) && (this->eventType != EVID_SUPPLY_CRATE) && (this->scale >= 0.5f)) {
                switch (this->eventType) {
                    case EVID_WING_REPAIR:
                        ActorEvent_8006FE28(this);
                        break;
                    case EVID_79:
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
        case EVID_92:
        case EVID_93:
        case EVID_94:
        case EVID_95:
        case EVID_96:
            if (((gGameFrameCount % 8) == 0)) {
                this->fwork[18] = RAND_FLOAT(255.0f);
                this->fwork[19] = RAND_FLOAT(255.0f);
                this->fwork[20] = RAND_FLOAT(255.0f);
            }
            Math_SmoothStepToF(&this->fwork[15], this->fwork[18], 1.0f, 10.0f, 0.0f);
            Math_SmoothStepToF(&this->fwork[16], this->fwork[19], 1.0f, 10.0f, 0.0f);
            Math_SmoothStepToF(&this->fwork[17], this->fwork[20], 1.0f, 10.0f, 0.0f);
            break;

        case EVID_46:
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

        case EVID_31:
            this->obj.rot.z = gGameFrameCount;
            break;

        case EVID_A6_MISSILE:
        case EVID_A6_ROCKET:
            this->obj.rot.z = gGameFrameCount * 3.0f;
            break;

        case EVID_3:
            this->drawShadow = true;
            this->obj.rot.y -= 10.0f;
            break;

        case EVID_6:
            this->animFrame++;
            if (gCurrentLevel == LEVEL_SOLAR) {
                if (this->animFrame >= Animation_GetFrameCount(&D_SO_600636C)) {
                    this->animFrame = 0;
                }
                if ((gGameFrameCount % 3) == 0) {
                    Solar_8019E9F4(this->obj.pos.x, this->obj.pos.y - 20, this->obj.pos.z - 180.0f, 0.0f,
                                   RAND_FLOAT(20.0f) * -1.0f, 0.0f, 4.0f, 2);
                }
            } else if (this->animFrame >= Animation_GetFrameCount(&D_ENMY_PLANET_40057AC)) {
                this->animFrame = 0;
            }
            break;

        case EVID_9:
            this->animFrame++;
            if (this->animFrame >= Animation_GetFrameCount(&D_ENMY_PLANET_40001A4)) {
                this->animFrame = 0;
            }
            if (this->iwork[6] == 0) {
                this->obj.rot.y = 0.0f;
            }
            break;

        case EVID_48:
        case EVID_49:
        case EVID_50:
            SectorY_Actor204_Update(this);
            break;

        case EVID_52:
            ActorEvent_80072474(this);
            break;

        case EVID_SUPPLY_CRATE:
            ActorSupplies_Update(this);
            break;

        case EVID_79:
            if (this->timer_0C4 == 0) {
                this->animFrame++;
                if (Animation_GetFrameCount(&D_ZO_600E5EC) < this->animFrame) {
                    this->animFrame = 0;
                }
            }
            break;

        case EVID_80: {
            Effect* effect;
            Vec3f sp90;
            Vec3f sp84;
            Vec3f sp78;
            s32 sp74;

            switch (this->unk_046) {
                case 1:
                    break;

                case 0:
                    Matrix_RotateZ(gCalcMatrix, this->rot_0F4.z * M_DTOR, MTXF_NEW);
                    Matrix_MultVec3fNoTranslate(gCalcMatrix, &D_800D1290, &sp90);

                    if ((this->obj.pos.y + sp90.y) > -30.0f) {
                        for (sp74 = 0; sp74 < 7; sp74++) {
                            effect = func_effect_8007783C(OBJ_EFFECT_394);

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
                        this->unk_046++;
                    }
                    break;
            }

            if ((fabsf(this->fwork[0]) > 10.0f) && ((gGameFrameCount % 2) == 0)) {
                effect = func_effect_8007783C(OBJ_EFFECT_394);
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

                    if (gGameFrameCount & 2) {
                        effect->vel.y = -effect->vel.y;
                    }
                }

                if (((gGameFrameCount % 4) == 0)) {
                    effect = func_effect_8007783C(OBJ_EFFECT_394);
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

        case EVID_81:
            Math_SmoothStepToF(&this->fwork[15], 1.0f, 0.1f, 0.1f, 0.001f);

            if (this->fwork[15] > 0.5f) {
                this->info.hitbox = (f32*) LOAD_ASSET(D_VE1_601B4C4);
            }

            if (this->unk_046 == 0) {
                this->fwork[16] += 4.0f;
                if (this->fwork[16] >= 100.0f) {
                    this->unk_046 = 1;
                    this->fwork[16] = 100.0f;
                }
            } else {
                this->fwork[16] -= 4.0f;
                if (this->fwork[16] <= 0.0f) {
                    this->unk_046 = 0;
                    this->fwork[16] = 0.0f;
                }
            }
            break;

        case EVID_AQ_CLAM:
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
                    func_effect_8007BC7C(this->obj.pos.x, this->obj.pos.y + 80.0f, this->obj.pos.z + 60.0f, 20.0f);
                }

                if (this->animFrame < 49) {
                    this->animFrame++;
                    if (this->animFrame >= 49) {
                        this->animFrame = 49;
                    }
                    if ((gGameFrameCount % 2) != 0) {
                        Aquas_801AC8A8(RAND_FLOAT_CENTERED(100.0f) + this->obj.pos.x,
                                       RAND_FLOAT(50.0f) + this->obj.pos.y,
                                       RAND_FLOAT_CENTERED(100.0f) + this->obj.pos.z, 1.0f, 0);
                    }
                }
                this->timer_0C2 = 10000;
            }
            break;

        case EVID_AQ_STARFISH:
            if (this->unk_04A == 0) {
                this->unk_046 += 4;
                if (this->unk_046 >= 255) {
                    this->unk_046 = 255;
                    this->unk_04A = 1;
                }
            } else {
                this->unk_046 -= 4;
                if (this->unk_046 <= 0) {
                    this->unk_046 = 0;
                    this->unk_04A = 0;
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

    if (gLevelMode == LEVELMODE_ALL_RANGE) {
        D_ctx_80177F20[this->index + 1] = this->obj.pos.x;
        D_ctx_80178028[this->index + 1] = this->obj.pos.z;
        D_ctx_80178130[this->index + 1] = Math_ModF(this->rot_0F4.y, 360.0f) + 180.0f;
        D_ctx_80178238[this->index + 1] = 1;
    }
}

static UNK_TYPE D_800D129C[140] = { 0 }; // unused

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

void ActorEvent_DrawEVID_SX_WARP_GATE(ActorEvent* this) {
    Vec3f sp30[10];

    Animation_GetFrameData(D_SX_6013820, 0, sp30);
    sp30[6].y += this->fwork[15];
    sp30[5].z += this->fwork[16] + (s32) ((this->timer_0BE >> 2) % 2U);
    sp30[4].z -= this->fwork[16] + (s32) ((this->timer_0BE >> 2) % 2U);
    Animation_DrawSkeleton(1, D_SX_601390C, sp30, ActorEvent_OverrideLimbDraw2, NULL, this, &gIdentityMatrix);
}

bool ActorEvent_OverrideLimbDraw3(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    gSPClearGeometryMode(gMasterDisp++, G_TEXTURE_GEN);
    if ((limbIndex == 3) || (limbIndex == 5)) {
        gSPTexture(gMasterDisp++, 5000, 5000, 0, G_TX_RENDERTILE, G_ON);
        gSPSetGeometryMode(gMasterDisp++, G_TEXTURE_GEN);
    }
    return false;
}

s32 Scenery111_Draw(Scenery_111* this) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_60);
    gSPDisplayList(gMasterDisp++, D_SY_601AD70);
    RCP_SetupDL(&gMasterDisp, SETUPDL_64);
    return 0;
}

void ActorEvent_Draw(ActorEvent* this) {
    Vec3f sp114[31];
    f32 sp40;
    s16 temp_s0;
    s32 pad;

    if (this->timer_0C6 && (this->eventType != EVID_90) && (this->eventType != EVID_68) &&
        (this->eventType != EVID_72)) {
        if ((this->eventType != EVID_13) && (this->eventType != EVID_14) && (this->eventType != EVID_61) &&
            (this->eventType != EVID_62) && (this->eventType != EVID_AQ_CLAM) && (this->eventType != EVID_98) &&
            (this->scale > 0.5f) && (this->timer_0C6 >= 9) && ((this->timer_0C6 & 3) == 0) &&
            (gPlayState != PLAY_PAUSE)) {
            func_effect_8007C120(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, this->vel.x, this->vel.y,
                                 this->vel.z, this->scale * 0.07f, 3);
        }

        if ((this->eventType != EVID_A6_MISSILE) && (this->eventType != EVID_23) && (this->eventType != EVID_79) &&
            (this->eventType != EVID_AQ_CLAM) && (this->eventType != EVID_27) && (this->eventType != EVID_51) &&
            (this->eventType != EVID_13) && (this->eventType != EVID_72) && (this->eventType != EVID_28) &&
            (this->scale > 0.5f)) {
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

    if ((this->eventType == EVID_29) || (this->eventType == EVID_59) || (this->eventType == EVID_60)) {
        RCP_SetupDL_60(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
    } else if ((this->eventType == EVID_82) || (this->eventType == EVID_90) ||
               ((this->eventType == EVID_6) && (gCurrentLevel == LEVEL_SOLAR))) {
        if ((this->timer_0C6 % 2) == 0) {
            RCP_SetupDL(&gMasterDisp, SETUPDL_57);
        } else {
            RCP_SetupDL(&gMasterDisp, SETUPDL_61);
        }
    }

    switch (this->eventType) {
        case EVID_92:
        case EVID_93:
        case EVID_94:
        case EVID_95:
        case EVID_96:
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
                case EVID_56:
                    Cutscene_DrawGreatFox();
                    break;

                case EVID_0:
                    this->iwork[11] = 1;
                    Actor_DrawEngineAndContrails(this);
                    break;

                case EVID_2:
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
                    func_edisplay_8005B388(this);
                    break;

                case EVID_TEAMMATE:
                    if (gLevelType == LEVELTYPE_PLANET) {
                        gSPDisplayList(gMasterDisp++, D_ENMY_PLANET_40018A0);
                    } else {
                        gSPDisplayList(gMasterDisp++, D_ENMY_SPACE_4007870);
                    }
                    Actor_DrawEngineAndContrails(this);
                    break;

                case EVID_5:
                    this->iwork[11] = 1;
                    Actor_DrawEngineAndContrails(this);
                    break;

                case EVID_6:
                    if (gCurrentLevel == LEVEL_SOLAR) {
                        gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                        Animation_GetFrameData(D_SO_600636C, this->animFrame, sp114);
                        Animation_DrawSkeleton(1, D_SO_6006558, sp114, NULL, NULL, this, &gIdentityMatrix);
                        gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
                    } else {
                        Animation_GetFrameData(D_ENMY_PLANET_40057AC, this->animFrame, sp114);
                        Animation_DrawSkeleton(1, D_ENMY_PLANET_40058B8, sp114, NULL, NULL, this, &gIdentityMatrix);
                    }
                    break;

                case EVID_7:
                    this->iwork[11] = 1;
                    Actor_DrawEngineAndContrails(this);
                    break;

                case EVID_9:
                    Matrix_Translate(gGfxMatrix, 0.0f, -30.0f, 0.0f, MTXF_APPLY);
                    Animation_GetFrameData(D_ENMY_PLANET_40001A4, this->animFrame, sp114);
                    Animation_DrawSkeleton(1, D_ENMY_PLANET_4000270, sp114, NULL, NULL, this, &gIdentityMatrix);
                    break;

                case EVID_18:
                    if (this->fwork[0] > 0.1f) {
                        this->iwork[11] = 1;
                        Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -30.0f, MTXF_APPLY);
                        Matrix_Scale(gGfxMatrix, 2.5f, 2.5f, 2.5f, MTXF_APPLY);
                        Actor_DrawEngineGlow(this, 2);
                    }
                    break;

                case EVID_19:
                    if (this->fwork[0] > 0.1f) {
                        this->iwork[11] = 1;
                        Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -30.0f, MTXF_APPLY);
                        Matrix_Scale(gGfxMatrix, 2.5f, 2.5f, 2.5f, MTXF_APPLY);
                        Actor_DrawEngineGlow(this, 2);
                    }
                    break;

                case EVID_20:
                    RCP_SetupDL_60(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
                    gSPDisplayList(gMasterDisp++, D_A6_601A120);
                    break;

                case EVID_A6_MISSILE:
                    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                    gSPDisplayList(gMasterDisp++, D_A6_6018BF0);
                    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
                    Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -30.0f, MTXF_APPLY);
                    this->iwork[11] = 1;
                    Actor_DrawEngineGlow(this, 2);
                    break;

                case EVID_A6_ROCKET:
                    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                    gSPDisplayList(gMasterDisp++, D_A6_6019730);
                    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
                    Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -30.0f, MTXF_APPLY);
                    this->iwork[11] = 1;
                    Actor_DrawEngineGlow(this, 2);
                    break;

                case EVID_27:
                    if (this->timer_0C2 != 0) {
                        if (((this->timer_0C2 & 3) == 0) && (gPlayState != PLAY_PAUSE)) {
                            func_effect_8007D0E0(RAND_FLOAT_CENTERED(200.0f) + this->obj.pos.x,
                                                 RAND_FLOAT_CENTERED(200.0f) + this->obj.pos.y,
                                                 RAND_FLOAT_CENTERED(200.0f) + this->obj.pos.z,
                                                 RAND_FLOAT(1.5f) + 2.5f);
                        }
                        RCP_SetupDL(&gMasterDisp, SETUPDL_57);
                        gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
                        gSPDisplayList(gMasterDisp++, D_SX_6001950);
                    } else {
                        gSPDisplayList(gMasterDisp++, D_SX_60066F0);
                    }
                    break;

                case EVID_31:
                    Matrix_RotateX(gGfxMatrix, M_PI / 2, MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_A6_600E0C0);
                    break;

                case EVID_33:
                    Animation_GetFrameData(D_ENMY_SPACE_400A30C, this->animFrame, sp114);
                    Matrix_RotateY(gGfxMatrix, M_PI, MTXF_APPLY);
                    Matrix_Scale(gGfxMatrix, 1.5f, 1.5f, 1.5f, MTXF_APPLY);
                    Animation_DrawSkeleton(1, D_ENMY_SPACE_400A398, sp114, ActorEvent_OverrideLimbDraw1, NULL, this,
                                           &gIdentityMatrix);
                    Math_SmoothStepToF(&this->fwork[16], 0.0f, 0.3f, 2.0f, 0.0001f);
                    break;

                case EVID_36:
                    Animation_GetFrameData(D_TI1_700CAF4, this->animFrame, sp114);
                    sp114[2].z += this->fwork[15];
                    Animation_DrawSkeleton(1, D_TI1_700CB60, sp114, NULL, NULL, this, &gIdentityMatrix);
                    break;

                case EVID_SX_WARP_GATE:
                    ActorEvent_DrawEVID_SX_WARP_GATE(this);
                    break;

                case EVID_48:
                case EVID_49:
                case EVID_50:
                    SectorY_Actor204_Draw(this);
                    break;

                case EVID_52:
                    Animation_GetFrameData(D_ZO_601F874, this->animFrame, sp114);
                    sp114[2].z -= this->fwork[15];
                    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                    Matrix_Scale(gGfxMatrix, 2.6f, 2.6f, 2.6f, MTXF_APPLY);
                    Animation_DrawSkeleton(1, D_ZO_601F920, sp114, NULL, NULL, this, &gIdentityMatrix);
                    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
                    break;

                case EVID_64:
                    Matrix_Push(&gGfxMatrix);
                    Matrix_RotateX(gGfxMatrix, this->rot_0F4.x * M_DTOR, MTXF_APPLY);
                    Matrix_RotateY(gGfxMatrix, this->rot_0F4.y * M_DTOR, MTXF_APPLY);
                    Matrix_Push(&gGfxMatrix);
                    Matrix_Translate(gGfxMatrix, 0.0f, this->fwork[15], 0.0f, MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_ME_600CAA0);
                    Matrix_Pop(&gGfxMatrix);
                    gSPDisplayList(gMasterDisp++, D_ME_600C130);
                    Matrix_Translate(gGfxMatrix, 0.0f, -this->fwork[15], 0.0f, MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_ME_600C740);
                    Matrix_Pop(&gGfxMatrix);
                    break;

                case EVID_METEO_PYRAMID_SHIP:
                    gSPDisplayList(gMasterDisp++, D_ME_6008AA0);
                    RCP_SetupDL(&gMasterDisp, SETUPDL_53);
                    gSPDisplayList(gMasterDisp++, D_ME_6009E30);
                    break;

                case EVID_SUPPLY_CRATE:
                    ActorSupplies_Draw(this);
                    break;

                case EVID_79:
                    temp_s0 = this->state;
                    this->state = 2; // actor 235 state
                    Zoness_80190430(this);
                    this->state = temp_s0;
                    break;

                case EVID_80:
                    Matrix_Scale(gGfxMatrix, 0.6f, 0.6f, 0.6f, MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_VE1_9011200);
                    break;

                case EVID_81:
                    if (this->fwork[15] > 0.001f) {
                        Matrix_Scale(gGfxMatrix, this->fwork[15], this->fwork[15], this->fwork[15], MTXF_APPLY);
                        Matrix_SetGfxMtx(&gMasterDisp);
                        Texture_BlendRGBA16(this->fwork[16], 16 * 11, D_VE1_9003890, D_VE1_9003DF0, D_VE1_9003330);
                        gSPDisplayList(gMasterDisp++, D_VE1_9002CF0);
                    }
                    break;

                case EVID_82:
                    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                    gSPDisplayList(gMasterDisp++, D_MA_600DA10);
                    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
                    break;

                case EVID_AQ_CLAM:
                    Matrix_Scale(gGfxMatrix, 3.0f, 3.0f, 3.0f, MTXF_APPLY);
                    Animation_GetFrameData(D_AQ_602201C, this->animFrame, sp114);
                    Animation_DrawSkeleton(1, D_AQ_60220E8, sp114, NULL, NULL, this, &gIdentityMatrix);
                    break;

                case EVID_BILL:
                    gSPDisplayList(gMasterDisp++, D_D00B880);
                    Actor_DrawEngineAndContrails(this);
                    break;

                case EVID_KATT:
                    gSPDisplayList(gMasterDisp++, D_D009A40);
                    Actor_DrawEngineAndContrails(this);
                    break;

                case EVID_AQ_STARFISH:
                    RCP_SetupDL(&gMasterDisp, SETUPDL_22);
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, this->unk_046, this->unk_046, this->unk_046, 255);
                    gSPDisplayList(gMasterDisp++, D_AQ_6008970);
                    break;

                case EVID_89:
                    RCP_SetupDL(&gMasterDisp, SETUPDL_21);
                    gSPDisplayList(gMasterDisp++, D_AQ_6000E10);
                    break;

                case EVID_ANDROSS_GATE:
                case EVID_ANDROSS_GATE_2:
                    Andross_8018769C(this);
                    break;

                case EVID_SX_WARP_ENMY:
                    RCP_SetupDL(&gMasterDisp, SETUPDL_35);
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 0, 0, 0, 143);
                    gDPSetEnvColor(gMasterDisp++, 0, 0, 0, 0);
                    gSPDisplayList(gMasterDisp++, D_WZ_7000000);
                    break;

                case EVID_KILLER_BEE:
                    Animation_GetFrameData(D_ENMY_SPACE_4000080, this->animFrame, sp114);
                    Animation_DrawSkeleton(1, D_ENMY_SPACE_400014C, sp114, NULL, NULL, this, &gIdentityMatrix);
                    break;

                case EVID_FFF:
                    this->timer_0C2 = 10;
                    break;
            }

            if ((gReflectY > 0) && ((this->iwork[12] >= TEAM_ID_FALCO) && (this->iwork[12] < TEAM_ID_MAX))) {
                Vec3f sp58 = { 0.0f, 0.0f, 0.0f };

                if ((this->iwork[12] == TEAM_ID_KATT) || (this->iwork[12] == TEAM_ID_BILL)) {
                    Matrix_MultVec3f(gGfxMatrix, &sp58, &gTeamArrowsViewPos[this->iwork[12] + 4]);
                } else {
                    Matrix_MultVec3f(gGfxMatrix, &sp58, &gTeamArrowsViewPos[this->iwork[12]]);
                }
            }
            break;
    }
}

void func_enmy2_800763A4(Actor* actor) {
    s32 var_s0;
    s32 sp60;
    s32 sp5C;
    f32 sp58;
    Vec3f sp4C;
    s32 pad;

    if (actor->eventType == EVID_27) {
        actor->obj.pos.y -= actor->vel.y;
        actor->obj.status = OBJ_ACTIVE;
        func_effect_8007D0E0(actor->obj.pos.x - actor->vel.x, actor->obj.pos.y + 30.0f, actor->obj.pos.z - actor->vel.z,
                             actor->scale * 5.0f);
        actor->timer_0C2 = 10000;
        return;
    }

    if (actor->timer_0BE != 0) {
        actor->vel.z = 0.0f;
        actor->vel.x = 0.0f;
        actor->vel.y = 0.0f;

        if (actor->timer_0BE == 1) {
            Object_Kill(&actor->obj, actor->sfxSource);
            Actor_Despawn(actor);

            if (gLevelMode == LEVELMODE_ALL_RANGE) {
                D_ctx_80177F20[actor->index + 1] = actor->obj.pos.x;
                D_ctx_80178028[actor->index + 1] = actor->obj.pos.z;
                D_ctx_80178130[actor->index + 1] = 1001.0f;
            }
            return;
        }
    } else {
        if ((gLevelType == LEVELTYPE_PLANET) || (gCurrentLevel == LEVEL_BOLSE)) {
            actor->gravity = 0.4f;
        }
        switch (actor->timer_04C) {
            case 0:
            case 1:
                if ((actor->index % 2) != 0) {
                    actor->obj.rot.z -= 8.0f;
                } else {
                    actor->obj.rot.z += 8.0f;
                }
                break;

            case 2:
                actor->obj.rot.y += 5.0f;
                actor->obj.rot.x += 7.3f;
                break;

            case 3:
                actor->obj.rot.y += 6.0f;
                actor->obj.rot.x += 18.3f;
                actor->gravity = 0.7f;
                break;

            case 4:
                actor->obj.rot.x += (-90.0f - actor->obj.rot.x) * 0.1f;
                break;
        }

        if (((actor->timer_0BC % 4U) == 1) && (actor->eventType != EVID_13) && (actor->eventType != EVID_61)) {
            func_effect_8007D24C(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, 2.2f);
        }

        if (gUseDynaFloor &&
            Play_CheckDynaFloorCollision(&sp58, &sp5C, actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z)) {
            func_effect_8007BFFC(actor->obj.pos.x, sp58 + 20.0f, actor->obj.pos.z, 0.0f, 0.0f, 0.0f,
                                 actor->scale * 3.0f, 5);
            func_effect_8007B228(actor->obj.pos.x, sp58, actor->obj.pos.z, 2.0f);
            actor->timer_0BE = 2;
            func_effect_8007A6F0(&actor->obj.pos, NA_SE_EN_EXPLOSION_S);
            return;
        }

        if (gGroundType == 4) {
            if (Ground_801B6AEC(actor->obj.pos.x, actor->obj.pos.y - 10.0f, actor->obj.pos.z + gPathProgress) != 0) {
                func_effect_8007D2C8(actor->obj.pos.x, actor->obj.pos.y + 20.0f, actor->obj.pos.z, actor->scale * 6.0f);
                func_effect_8007BFFC(actor->obj.pos.x - actor->vel.x, actor->obj.pos.y + 30.0f,
                                     actor->obj.pos.z - actor->vel.z, 0.0f, 0.0f, 0.0f, actor->scale * 4.0f, 20);
                func_enmy_80062C38(actor->obj.pos.x, actor->obj.pos.z);
                actor->timer_0BE = 2;
                func_effect_8007A6F0(&actor->obj.pos, NA_SE_EN_EXPLOSION_S);
                return;
            }
        } else {
            sp4C.x = actor->vel.x;
            sp4C.y = actor->vel.y;
            sp4C.z = actor->vel.z;

            sp60 = Object_CheckCollision(actor->index, &actor->obj.pos, &sp4C, 0);

            if ((sp60 != 0) || (actor->obj.pos.y < (gGroundHeight + 30.0f))) {
                if ((Rand_ZeroOne() < 0.5f) && (actor->timer_04C < 3) && (gLevelType == LEVELTYPE_PLANET) &&
                    (sp60 != 999) && (gGroundSurface != SURFACE_WATER) &&
                    ((actor->vel.z < -20.0f) || (actor->vel.z > 0.0f))) {
                    if (gCurrentLevel == LEVEL_FORTUNA) {
                        func_enmy2_8006BF7C(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z - actor->vel.z);
                        func_enmy_80062C38(actor->obj.pos.x, actor->obj.pos.z);
                    }

                    actor->obj.pos.y -= actor->vel.y;
                    actor->vel.y = RAND_FLOAT(10.0f);
                    actor->timer_04C = 3;

                    if (gLevelMode == LEVELMODE_ALL_RANGE) {
                        func_effect_8007D2C8(actor->obj.pos.x - actor->vel.x, actor->obj.pos.y,
                                             actor->obj.pos.z - actor->vel.z, actor->scale * 3.0f);
                    }

                    func_effect_8007D2C8(actor->obj.pos.x - actor->vel.x, actor->obj.pos.y,
                                         actor->obj.pos.z - actor->vel.z, actor->scale * 3.0f);

                    if ((actor->obj.id == OBJ_ACTOR_ALLRANGE) && (actor->aiType < AI360_KATT)) {
                        func_effect_8007A6F0(&actor->obj.pos, NA_SE_EN_EXPLOSION_M);
                    } else {
                        func_effect_8007A6F0(&actor->obj.pos, NA_SE_EN_EXPLOSION_S);
                    }

                    if ((actor->obj.id == OBJ_ACTOR_EVENT) && (actor->eventType == EVID_2)) {
                        if (actor->fwork[17] < 360.0f) {
                            Play_SpawnDebris(1, actor->obj.pos.x + 20.0f, actor->obj.pos.y, actor->obj.pos.z);
                            actor->fwork[17] = 777.0f;
                        }
                        if (actor->fwork[18] < 360.0f) {
                            Play_SpawnDebris(0, actor->obj.pos.x - 20.0f, actor->obj.pos.y, actor->obj.pos.z);
                            actor->fwork[18] = 777.0f;
                        }
                    }
                } else {
                    if ((actor->obj.pos.y < (gGroundHeight + 30.0f)) && (gLevelType == LEVELTYPE_PLANET)) {
                        actor->vel.z = 0.0f;
                        if (gGroundSurface == SURFACE_WATER) {
                            func_effect_8007D9DC(actor->obj.pos.x, gGroundHeight + 2.0f, actor->obj.pos.z, 3.0f, 20.0f,
                                                 0);
                            func_effect_8007D9DC(actor->obj.pos.x, gGroundHeight + 2.0f, actor->obj.pos.z, 3.0f, 20.0f,
                                                 10);
                            func_effect_8007D9DC(actor->obj.pos.x, gGroundHeight + 2.0f, actor->obj.pos.z, 3.0f, 20.0f,
                                                 20);
                            func_effect_8007ADF4(actor->obj.pos.x, gGroundHeight, actor->obj.pos.z, 0.1f, 3.0f);
                        } else {
                            PlayerShot_SpawnEffect344(actor->obj.pos.x, 3.0f, actor->obj.pos.z, actor->obj.pos.x,
                                                      actor->obj.pos.z, 0.0f, 0.0f, 90.0f, 6.5f, 0, 0);
                        }
                        func_effect_8007C120(actor->obj.pos.x, 20.0f, actor->obj.pos.z, 0.0f, 0.0f, 0.0f,
                                             actor->scale * 0.05f, 30);
                        if ((gCurrentLevel == LEVEL_FORTUNA) || (gCurrentLevel == LEVEL_VENOM_2)) {
                            func_effect_8007C688(actor->obj.pos.x, gGroundHeight + 30.0f, actor->obj.pos.z, 3.0f, 60);
                            if (gCurrentLevel == LEVEL_FORTUNA) {
                                func_enmy_80062C38(actor->obj.pos.x, actor->obj.pos.z);
                            }
                        }
                    }

                    actor->obj.pos.y -= actor->vel.y;
                    func_effect_8007D0E0(actor->obj.pos.x - actor->vel.x, actor->obj.pos.y + 30.0f,
                                         actor->obj.pos.z - actor->vel.z, actor->scale * 5.0f);
                    if (gLevelMode == LEVELMODE_ALL_RANGE) {
                        func_effect_8007BFFC(actor->obj.pos.x, actor->obj.pos.y + 30.0f, actor->obj.pos.z, actor->vel.x,
                                             10.0f, actor->vel.z, actor->scale * 3.0f, 20);
                        if (sp60 == 999) {
                            func_effect_8007C688(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z,
                                                 actor->scale * 3.0f, 70);
                        }
                        for (var_s0 = 0; var_s0 < 4; var_s0++) {
                            if (Rand_ZeroOne() < 0.7f) {
                                if (gCurrentLevel == LEVEL_FORTUNA) {
                                    Play_SpawnDebris(4, actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z);
                                } else {
                                    func_effect_800794CC(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, 1.0f);
                                }
                            }
                        }
                    } else {
                        func_effect_8007BFFC(actor->obj.pos.x - actor->vel.x, actor->obj.pos.y + 30.0f,
                                             (actor->obj.pos.z - actor->vel.z) + 48.0f, 0.0f, 0.0f, 0.0f,
                                             actor->scale * 3.0f, 5);
                    }

                    actor->timer_0BE = 2;

                    if ((actor->obj.id == OBJ_ACTOR_ALLRANGE) && (actor->aiType < AI360_KATT)) {
                        func_effect_8007A6F0(&actor->obj.pos, NA_SE_EN_EXPLOSION_M);
                    } else {
                        func_effect_8007A6F0(&actor->obj.pos, NA_SE_EN_EXPLOSION_S);
                    }
                }
            }
        }
        if ((actor->dmgType != DMG_NONE) || (actor->timer_0BC == 0) ||
            ((actor->itemDrop != DROP_NONE) && (actor->obj.id != OBJ_ACTOR_ALLRANGE))) {
            if (gLevelMode == LEVELMODE_ALL_RANGE) {
                for (var_s0 = 0; var_s0 < 4; var_s0++) {
                    if (Rand_ZeroOne() < 0.7f) {
                        if (gCurrentLevel == LEVEL_FORTUNA) {
                            Play_SpawnDebris(4, actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z);
                        } else {
                            func_effect_800794CC(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, 1.0f);
                        }
                    }
                }

                func_effect_8007BFFC(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, actor->vel.x, actor->vel.y,
                                     actor->vel.z, 5.0f, 15);
                func_effect_8007D0E0(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z - actor->vel.z, 8.0f);
            } else {
                if ((actor->eventType != EVID_13) && (actor->eventType != EVID_61)) {
                    func_effect_8007D0E0(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z - actor->vel.z,
                                         actor->scale * 5.0f);
                }

                if (actor->eventType == EVID_36) {
                    func_effect_8007BFFC(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, actor->vel.x,
                                         actor->vel.y, actor->vel.z, 5.0f, 15);
                }
            }

            actor->timer_0BE = 2;

            if ((actor->obj.id == OBJ_ACTOR_ALLRANGE) && (actor->aiType < AI360_KATT)) {
                func_effect_8007A6F0(&actor->obj.pos, NA_SE_EN_EXPLOSION_M);
            } else {
                func_effect_8007A6F0(&actor->obj.pos, NA_SE_EN_EXPLOSION_S);
            }
        }
    }

    if (gLevelMode == LEVELMODE_ALL_RANGE) {
        D_ctx_80177F20[actor->index + 1] = actor->obj.pos.x;
        D_ctx_80178028[actor->index + 1] = actor->obj.pos.z;
        D_ctx_80178130[actor->index + 1] = actor->rot_0F4.y + 180.0f;
    }

    if (actor->obj.id == OBJ_ACTOR_ALLRANGE) {
        ActorAllRange_SetShadowData(actor);
    }
}

void ActorEvent_Dying(ActorEvent* this) {
    if ((this->eventType == EVID_48) || (this->eventType == EVID_49) || (this->eventType == EVID_50)) {
        SectorY_Actor204_Update(this);
    } else {
        func_enmy2_800763A4(this);
    }
}

void Actor234_Update(Actor234* this) {
    Vec3f sp24;

    Math_Vec3fFromAngles(&sp24, this->obj.rot.x, this->obj.rot.y, 50.0f);
    this->vel.x = sp24.x;
    this->vel.y = sp24.y;
    this->vel.z = sp24.z;
}

void Actor234_Draw(Actor234* this) {
    Cutscene_DrawGreatFox();
}
