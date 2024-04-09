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

s32 D_enmy2_800CFF80[4] = { 0, 0, 0, 0 };
s32 gCallVoiceParam = 0;
s32 gCallTimer;

void ActorEvent_SetMessage(u16* msg, s32 character) {
    PRINTF("Enm->obj.pos.y + tmp_xyz.y=<%10.3f>\n");
    if ((gRadioState == 0) || (D_ctx_80177D68 != character)) {
        Radio_PlayMessage(msg, character);
    }
}

void func_enmy2_8006A800(Effect* effect, f32 xPos, f32 yPos, f32 zPos, f32 arg4) {
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
    effect->scale2 = arg4 * 0.25f;
    effect->scale1 = 0.3f;

    if (arg4 < 10.0f) {
        effect->scale1 = 0.1f;
    }

    effect->obj.rot.z = RAND_FLOAT(360.0f);
    Object_SetInfo(&effect->info, effect->obj.id);
}

void func_enmy2_8006A900(f32 xPos, f32 yPos, f32 zPos, f32 arg3) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            func_enmy2_8006A800(&gEffects[i], xPos, yPos, zPos, arg3);
            break;
        }
    }
}

void Actor237_Update(Actor237* this) {
}

void Actor237_Draw(Actor237* this) {
}

void Ovj54_8006A984(Effect* effect, f32 xPos, f32 yPos, f32 zPos) {
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
            Ovj54_8006A984(&gEffects[i], xPos, yPos, zPos);
            break;
        }
    }
}

void Obj54_Update(Object80_54* this) {
    Vec3f sp24;
    Vec3f sp18;

    Texture_Scroll(D_CO_60038F8, 32, 32, 1);
    if ((gGameFrameCount % 4) == 0) {
        Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, 0);

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
    sp2C = this->obj.pos.z + D_ctx_80177D20;
    this->obj.rot.y = Math_RadToDeg(Math_Atan2F(gPlayer[0].camEye.x - this->obj.pos.x, gPlayer[0].camEye.z - sp2C));
    this->obj.rot.x =
        -Math_RadToDeg(Math_Atan2F(gPlayer[0].camEye.y - this->obj.pos.y,
                                   sqrtf(SQ(gPlayer[0].camEye.z - sp2C) + SQ(gPlayer[0].camEye.x - this->obj.pos.x))));
}

void Actor202_Update(Actor202* this) {
    bool sp34;

    this->gravity = 1.5f;
    sp34 = false;
    this->obj.rot.y = Math_RadToDeg(
        Math_Atan2F(gPlayer[gPlayerNum].pos.x - this->obj.pos.x, gPlayer[gPlayerNum].unk_138 - this->obj.pos.z));
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
            this->unk_0B6++;

            if (this->unk_0B6 >= 30) {
                this->unk_0B6 = 0;
            }

            if (this->unk_0B6 == 21) {
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
                this->unk_0B6++;
                if (this->unk_0B6 >= 30) {
                    this->unk_0B6 = 29;
                }
            } else {
                this->unk_0B6--;
                if (this->unk_0B6 < 0) {
                    this->unk_0B6 = 0;
                }
            }

            if (sp34) {
                this->state = 0;
            }
            break;
    }

    if (this->unk_0D0 != 0) {
        this->health -= 10;
        if ((this->health <= 0) || (this->unk_0D0 >= 2)) {
            func_effect_8007D2C8(this->obj.pos.x, this->obj.pos.y + 180.0f, this->obj.pos.z, 10.0f);
            func_effect_8007BFFC(this->obj.pos.x, this->obj.pos.y + 180.0f, this->obj.pos.z, this->vel.x, this->vel.y,
                                 this->vel.z, 8.0f, 30);
            Object_Kill(&this->obj, this->sfxSource);
            func_effect_8007A6F0(&this->obj.pos, 0x2903A008);
            gHitCount += this->info.bonus;
            D_ctx_80177850 = 15;
        } else {
            this->unk_0D0 = 0;
            this->timer_0C6 = 20;
            AUDIO_PLAY_SFX(0x2903300E, this->sfxSource, 4);
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

void Actor194_Init(Actor194* this) {
    Vec3f sp34;
    s32 temp_hi;

    this->unk_04E++;

    if (this->unk_04E >= 100) {
        this->unk_04E = 0;
    }

    D_ctx_80176558[this->unk_046][this->unk_04E] = this->obj.pos.x;
    D_ctx_80176878[this->unk_046][this->unk_04E] = this->obj.pos.y;
    D_ctx_80176B98[this->unk_046][this->unk_04E] = this->obj.pos.z;
    D_ctx_80176EB8[this->unk_046][this->unk_04E] = this->obj.rot.x;
    D_ctx_801771D8[this->unk_046][this->unk_04E] = this->obj.rot.y;
    D_ctx_80177500[this->unk_046][this->unk_04E] = this->obj.rot.z;

    this->obj.rot.x -= 10.0f;
    this->obj.rot.y += 3.0f;
    this->obj.rot.z += 5.0f;

    Math_Vec3fFromAngles(&sp34, this->obj.rot.x, this->obj.rot.y, 40.0f);

    this->vel.x = sp34.x;
    this->vel.y = sp34.y;
    this->vel.z = sp34.z;

    if ((this->timer_0BC == 0) && ((gGameFrameCount % 4) == 0)) {
        temp_hi = (D_800CFF94[this->unk_04A] + this->unk_04E) % 100;
        if (this->unk_04A == 0) {
            func_effect_8007D2C8(D_ctx_80176558[this->unk_046][temp_hi], D_ctx_80176878[this->unk_046][temp_hi],
                                 D_ctx_80176B98[this->unk_046][temp_hi], 7.0f);
        } else {
            func_effect_8007D2C8(D_ctx_80176558[this->unk_046][temp_hi], D_ctx_80176878[this->unk_046][temp_hi],
                                 D_ctx_80176B98[this->unk_046][temp_hi], 4.0f);
        }

        AUDIO_PLAY_SFX(0x2903B009, this->sfxSource, 4);
        this->unk_04A++;

        if (this->unk_04A > 15) {
            Object_Kill(&this->obj, this->sfxSource);
            D_ctx_80176550[this->unk_046] = 0;
            gHitCount += this->info.bonus;
            D_ctx_80177850 = 15;
        }
    }
}

void Actor194_8006B46C(Actor194* this, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, u8 arg7, f32 arg8,
                       s32 arg9) {
    Vec3f sp34 = { 0.0f, 0.0f, 0.0f };

    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, arg1, arg2, arg3 + D_ctx_80177D20, 1);

    if (arg7 != 1) {
        Matrix_RotateY(gGfxMatrix, M_DTOR * arg5, 1);
        Matrix_RotateX(gGfxMatrix, M_DTOR * arg4, 1);
        Matrix_RotateZ(gGfxMatrix, M_DTOR * arg6, 1);
    }

    Matrix_Scale(gGfxMatrix, arg8, arg8, 1.0f, 1);
    Matrix_SetGfxMtx(&gMasterDisp);

    if (arg7 != 1) {
        RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
        if ((arg7 == 0) && (this->timer_0CA[0] != 0)) {
            sp34.y += this->info.unk_1C;
            Matrix_MultVec3f(gGfxMatrix, &sp34, D_display_80161578);
            if (D_display_80161578->z > -500.0f) {
                this->timer_0CA[0] = 0;
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
        temp_hi = (D_800CFF94[var_s0] + this->unk_04E) % 100;
        Actor194_8006B46C(this, D_ctx_80176558[this->unk_046][temp_hi], D_ctx_80176878[this->unk_046][temp_hi],
                          D_ctx_80176B98[this->unk_046][temp_hi], D_ctx_80176EB8[this->unk_046][temp_hi],
                          D_ctx_801771D8[this->unk_046][temp_hi], D_ctx_80177500[this->unk_046][temp_hi],
                          D_800CFFB4[var_s0], D_800CFFC4[var_s0], this->timer_0C6 % 2U);
    }
}

void Obj42_Update(Object80_42* this) {
    this->obj.pos.x += this->vel.x;
    this->obj.pos.y += this->vel.y;
    this->obj.pos.z += this->vel.z;

    switch (this->state) {
        case 0:
            this->vel.y -= 1.0f;

            if (this->obj.pos.y < gGroundLevel + 40.0f) {
                this->obj.pos.y = gGroundLevel + 40.0f;
                AUDIO_PLAY_SFX(0x19130003, this->sfxSource, 0);
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
            if (fabsf((this->obj.pos.z + this->fwork[10]) - gPlayer[0].unk_138) < 3000.0f) {
                this->state = 2;
                this->timer_0BC = 20;
                this->vel.z = 0.0f;
                this->vel.x = 0.0f;
            }
            break;

        case 2:
            if (this->timer_0BC == 0) {
                this->state = 3;
                this->unk_0B6 = 1;
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
            if (this->obj.pos.y < (gGroundLevel + 10.0f)) {
                this->obj.pos.y = gGroundLevel;
                this->state = 4;
                this->unk_0B6 = 0;
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

    if ((this->obj.pos.y <= (gGroundLevel + 10.0f)) && ((gGameFrameCount % 8) == 0)) {
        func_enmy2_8006BB1C(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z);
    }

    if (((gGameFrameCount % 8) == 0)) {
        func_enmy2_8006A900(RAND_FLOAT_CENTERED(50.0f) + this->obj.pos.x, this->obj.pos.y + 10.0f,
                            RAND_FLOAT_CENTERED(50.0f) + this->obj.pos.z, 0.5f);
    }

    if ((this->unk_0D0 != 0) && (this->unk_0B6 != 0)) {
        func_effect_8007BFFC(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 0.0f, this->vel.y, 0.0f, 3.0f, 5);
        Object_Kill(&this->obj, this->sfxSource);
        this->itemDrop = DROP_SILVER_RING;
        Actor_Despawn(this);
    }
    this->unk_0D0 = 0;
}

static f32 D_800D001C[5] = { 0.0f, 30.0f, 60.0f, -60.0f, -30.0f }; // could be in-function
void func_enmy2_8006BF7C(f32 xPos, f32 yPos, f32 zPos) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_800D001C); i++) {
        func_enmy2_8006A900(xPos + D_800D001C[i], yPos, zPos, 6.0f);
    }
}

static Vec3f D_800D0030 = { 0.0f, -10.0f, 0.0f }; // could be in-function
void Actor189_Update(Actor189* this) {
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    s32 sp40;

    switch (this->state) {
        case 40:
            if (this->unk_04A & 4) {
                this->obj.pos.x = gPlayer[0].pos.x + this->fwork[3];
                this->obj.pos.z = gPlayer[0].unk_138 + this->fwork[4];
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
                                AUDIO_PLAY_SFX(0x19000024, this->sfxSource, 4);
                                break;
                            case 25:
                                AUDIO_PLAY_SFX(0x29003031, this->sfxSource, 4);
                                break;
                        }
                    }
                    Math_SmoothStepToF(&this->fwork[0], 0.0f, 0.8f, 1.0f, 0.01f);
                    Math_SmoothStepToF(&this->fwork[1], 0.0f, 0.8f, 1.0f, 0.01f);
                    Math_SmoothStepToF(&this->fwork[2], 0.0f, 0.8f, 1.0f, 0.01f);
                    Math_SmoothStepToF(&this->vel.x, 0.0f, 0.5f, 1.0f, 0.01f);
                    this->obj.pos.y = 0.0f;
                    this->iwork[0] += 1;
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

            Ground_801B6E20(this->obj.pos.x, this->obj.pos.z + D_ctx_80177D20, &sp4C, &sp48, &sp4C);

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
            Ground_801B6E20(this->obj.pos.x, this->obj.pos.z + D_ctx_80177D20, &sp4C, &sp48, &sp4C);

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
            if (((this->timer_0BC == 0) || (func_enmy_8006351C(this->index, &this->obj.pos, &D_800D0030, 1) != 0) ||
                 (this->obj.pos.y < (gGroundLevel + 10.0f))) &&
                (this->timer_0BE == 0)) {
                func_effect_8007B8F8(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + 50.0f, this->scale * 10.0f);
                Object_Kill(&this->obj, this->sfxSource);
                func_effect_8007A6F0(&this->obj.pos, 0x2903A008);
            }
            break;

        case 56:
            Math_SmoothStepToF(&this->scale, 0.0f, 0.1f, 2.0f, 0.0001f);
            if (((this->timer_0BC == 0) || (func_enmy_8006351C(this->index, &this->obj.pos, &D_800D0030, 1) != 0) ||
                 (this->obj.pos.y < (gGroundLevel + 10.0f))) &&
                (this->timer_0BE == 0)) {
                func_effect_8007B8F8(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + 50.0f, this->scale * 10.0f);
                Object_Kill(&this->obj, this->sfxSource);
                func_effect_8007A6F0(&this->obj.pos, 0x2903A008);
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

            if (((this->timer_0BC == 0) || (func_enmy_8006351C(this->index, &this->obj.pos, &D_800D0030, 1) != 0) ||
                 (this->obj.pos.y < (gGroundLevel + 10.0f))) &&
                (this->timer_0BE == 0)) {
                func_effect_8007B8F8(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + 50.0f, this->scale * 10.0f);
                Object_Kill(&this->obj, this->sfxSource);
                func_effect_8007A6F0(&this->obj.pos, 0x2903A008);
            }
            break;

        case 54:
            if (((this->timer_0BC == 0) || (func_enmy_8006351C(this->index, &this->obj.pos, &D_800D0030, 1) != 0) ||
                 (this->obj.pos.y < (gGroundLevel + 10.0f))) &&
                (this->timer_0BE == 0)) {
                func_effect_8007B8F8(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + 70.0f, this->scale * 20.0f);
                func_effect_8007B8F8(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + 70.0f, this->scale * 20.0f);
                Object_Kill(&this->obj, this->sfxSource);
                func_effect_8007A6F0(&this->obj.pos, 0x2903A008);
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
            if (func_enmy_8006351C(this->index, &this->obj.pos, &D_tank_800C9F2C, 1) != 0) {
                this->vel.x *= -0.7f;
            }
            if (this->obj.pos.y < gGroundLevel) {
                Object_Kill(&this->obj, this->sfxSource);
            }
            break;

        case 57:
            this->obj.rot.x += this->fwork[0];
            this->obj.rot.y += this->fwork[1];
            this->obj.rot.z += this->fwork[2];

            if (func_enmy_8006351C(this->index, &this->obj.pos, &D_tank_800C9F2C, 1) != 0) {
                this->vel.x *= -0.7f;
            }

            if (this->obj.pos.y < gGroundLevel) {
                if (this->iwork[0] >= 3) {
                    this->vel.y = 0.0f;
                    this->gravity = 0.0f;
                    this->fwork[2] = 0.0f;
                    this->fwork[1] = 0.0f;
                    this->fwork[0] = 0.0f;
                } else {
                    this->iwork[0]++;
                    this->vel.y = -this->vel.y * 0.7f;
                    this->obj.pos.y = gGroundLevel;
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
                if ((this->timer_0BC == 0) || (func_enmy_8006351C(this->index, &this->obj.pos, &D_800D0030, 1) != 0) ||
                    (this->obj.pos.y < (gGroundLevel + 10.0f))) {
                    Object_Kill(&this->obj, this->sfxSource);
                }
            } else if (this->state == 39) {
                if (((this->timer_0BC == 0) || (func_enmy_8006351C(this->index, &this->obj.pos, &D_800D0030, 1) != 0) ||
                     (this->obj.pos.y < (gGroundLevel + 10.0f))) &&
                    (this->timer_0BE == 0)) {
                    func_effect_8007D0E0(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 10.0f);
                    Object_Kill(&this->obj, this->sfxSource);
                    func_effect_8007A6F0(&this->obj.pos, 0x2903A008);
                }
            } else if (((this->state >= 41) && (this->state < 45)) || (this->state == 59)) {
                if (((this->timer_0BC == 0) ||
                     (func_enmy_8006351C(this->index, &this->obj.pos, &D_800D0030, 1) != 0)) &&
                    (this->timer_0BE == 0)) {
                    func_effect_8007D0E0(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 2.0f * this->scale);
                    Object_Kill(&this->obj, this->sfxSource);
                    func_effect_8007A6F0(&this->obj.pos, 0x2903A008);
                }
                if (func_play_800A73E4(&sp44, &sp40, this->obj.pos.x, this->obj.pos.y, this->obj.pos.z)) {
                    func_effect_8007B228(this->obj.pos.x, sp44, this->obj.pos.z, 2.0f);
                    Object_Kill(&this->obj, this->sfxSource);
                }
            } else if (this->state >= 10) {
                if ((this->timer_0BC & 3) == 0) {
                    func_effect_8007D0E0(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, this->scale);
                }
                if (((this->timer_0BC == 0) || (func_enmy_8006351C(this->index, &this->obj.pos, &D_800D0030, 1) != 0) ||
                     (this->obj.pos.y < (gGroundLevel + 10.0f))) &&
                    (this->timer_0BE == 0)) {
                    func_effect_8007BFFC(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, this->vel.x, this->vel.y,
                                         this->vel.z, this->scale * 1.5f, 4);
                    Object_Kill(&this->obj, this->sfxSource);
                    func_effect_8007A6F0(&this->obj.pos, 0x2903A008);
                }
            } else {
                if ((this->state == 3) && ((this->timer_0BC % 8) == 0)) {
                    func_effect_8007D0E0(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 1.5f);
                }
                if ((func_enmy_8006351C(this->index, &this->obj.pos, &D_800D0030, 1) != 0) ||
                    (this->obj.pos.y < (gGroundLevel + 10.0f))) {
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

void func_enmy2_8006D0F4(Actor* actor) {
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

    for (i = 0; i < ARRAY_COUNT(gObjects80); i++) {
        if ((gObjects80[i].obj.status == OBJ_ACTIVE) && ((gPlayer[0].unk_138 - 3000.0f) < gObjects80[i].obj.pos.z)) {
            hitboxData = D_edata_800CF964[gObjects80[i].obj.id];
            count = *hitboxData;
            if (count != 0) {
                Matrix_RotateY(gCalcMatrix, -gObjects80[i].obj.rot.y * M_DTOR, 0);

                spA8.x = actor->obj.pos.x - gObjects80[i].obj.pos.x;
                spA8.y = actor->obj.pos.y - gObjects80[i].obj.pos.y;
                spA8.z = actor->obj.pos.z - gObjects80[i].obj.pos.z;

                Matrix_MultVec3fNoTranslate(gCalcMatrix, &spA8, &sp9C);

                temp_fs0 = gObjects80[i].obj.pos.x + sp9C.x;
                temp_fs1 = gObjects80[i].obj.pos.y + sp9C.y;
                temp_fs2 = gObjects80[i].obj.pos.z + sp9C.z;
                hitboxData++;

                for (j = 0; j < count; j++) {
                    hitbox = (Hitbox*) hitboxData;
                    if (func_play_800A78C4(hitbox, gObjects80[i].obj.pos.x, gObjects80[i].obj.pos.y,
                                           gObjects80[i].obj.pos.z, temp_fs0, temp_fs1, temp_fs2)) {
                        D_ctx_80161A7C = 10;
                        D_ctx_80161A80 = 10;
                        D_ctx_80161A84 = 10;
                        actor->unk_0C8 = 5;
                    }
                    hitboxData += 6;
                }
            }
        }
    }
}

void Obj39_Update(Object80_39* this) {
    this->obj.rot.z += 1.0f;
}

static UnkStruct_D003C D_800D003C[108] = {
    /*   0 */ { D_ENMY_PLANET_40068F0, gDefaultCubeHitbox100, 1.0f, 100.0f, 3000.0f, 1, 0, 1, 0, 1.0f, 1 },
    /*   1 */ { D_ENMY_PLANET_4006E90, gDefaultCubeHitbox100, 1.0f, 100.0f, 3000.0f, 1, 0, 1, 0, 1.0f, 1 },
    /*   2 */ { NULL, gDefaultCubeHitbox100, 1.0f, 20000.0f, 3000.0f, 1, 0, 2, 0, 0.0f, 0 },
    /*   3 */ { D_ENMY_PLANET_4009800, gDefaultCubeHitbox100, 1.5f, 100.0f, 3000.0f, 1, 0, 0, 0, 1.0f, 1 },
    /*   4 */ { D_ENMY_PLANET_40073C0, gDefaultCubeHitbox100, 1.0f, 100.0f, 3000.0f, 1, 0, 1, 0, 1.0f, 1 },
    /*   5 */ { D_ENMY_PLANET_4007AF0, gDefaultCubeHitbox100, 1.0f, 100.0f, 3000.0f, 1, 0, 1, 0, 1.0f, 1 },
    /*   6 */ { NULL, gDefaultCubeHitbox100, 1.0f, 100.0f, 3000.0f, 1, 0, 0, 0, 1.0f, 1 },
    /*   7 */ { D_CO_6011F90, gDefaultCubeHitbox100, 1.0f, 100.0f, 3000.0f, 1, 0, 1, 0, 0.0f, 1 },
    /*   8 */ { D_ENMY_PLANET_4000710, gDefaultCubeHitbox100, 1.0f, 100.0f, 3000.0f, 2, 0, 1, 1, 1.0f, 1 },
    /*   9 */ { NULL, gDefaultCubeHitbox100, 1.5f, 100.0f, 3000.0f, 1, 0, 6, 0, 1.0f, 1 },
    /*  10 */ { D_ENMY_SPACE_400BD20, gDefaultCubeHitbox200, 2.0f, 100.0f, 3000.0f, 1, 0, 1, 0, 1.0f, 1 },
    /*  11 */ { D_ENMY_SPACE_4001310, gDefaultCubeHitbox100, 1.5f, 100.0f, 3000.0f, 1, 0, 6, 0, 1.0f, 1 },
    /*  12 */ { D_ENMY_SPACE_400B390, gDefaultCubeHitbox100, 2.0f, 100.0f, 3000.0f, 1, 0, 1, 0, 1.0f, 1 },
    /*  13 */ { D_ME_6018C00, gDefaultCubeHitbox100, 2.5f, 100.0f, 3000.0f, 1, 0, 1, 0, 1.0f, 1 },
    /*  14 */ { D_ME_601F2A0, gDefaultCubeHitbox400, 7.0f, 100.0f, 3000.0f, 1, 0, 1, 0, 1.0f, 1 },
    /*  15 */ { D_ENMY_SPACE_400AAE0, gDefaultCubeHitbox100, 1.5f, 100.0f, 3000.0f, 1, 0, 1, 0, 1.0f, 1 },
    /*  16 */ { D_ENMY_SPACE_4000650, gDefaultCubeHitbox100, 1.5f, 100.0f, 3000.0f, 1, 0, 6, 0, 1.0f, 1 },
    /*  17 */ { D_A6_6016190, D_A6_60282A0, -2.0f, 2100.0f, 3000.0f, 0, 0, 7, 0, 0.0f, 5 },
    /*  18 */ { D_SX_6023500, gDefaultCubeHitbox200, 2.0f, 100.0f, 3000.0f, 1, 0, 1, 0, 1.0f, 1 },
    /*  19 */ { D_SX_6022DF0, gDefaultCubeHitbox100, 1.5f, 100.0f, 3000.0f, 1, 0, 1, 0, 1.0f, 1 },
    /*  20 */ { NULL, gDefaultCubeHitbox100, 1.0f, 100.0f, 3000.0f, 2, 1, 1, 0, 0.0f, 1 },
    /*  21 */ { NULL, gDefaultCubeHitbox200, 2.0f, 100.0f, 3000.0f, 1, 0, 1, 0, 0.0f, 1 },
    /*  22 */ { NULL, gDefaultCubeHitbox100, 1.5f, 100.0f, 3000.0f, 1, 0, 1, 0, 0.0f, 1 },
    /*  23 */ { D_ENMY_SPACE_4008FA0, gDefaultCubeHitbox100, 1.5f, 100.0f, 3000.0f, 1, 0, 1, 0, 1.0f, 1 },
    /*  24 */ { D_SX_60285F0, D_SX_603298C, -1.0f, 2100.0f, 3001.0f, 0, 0, 0, 0, 0.0f, 1 },
    /*  25 */ { D_SX_600AF70, D_SX_6032904, -1.0f, 2100.0f, 3001.0f, 0, 0, 0, 0, 0.0f, 1 },
    /*  26 */ { D_SX_6023E30, D_SX_6032970, -1.0f, 2100.0f, 3001.0f, 0, 0, 0, 0, 0.0f, 1 },
    /*  27 */ { NULL, D_SX_603285C, 2.5f, 100.0f, 3000.0f, 2, 0, 0, 0, 1.0f, 1 },
    /*  28 */ { D_SX_6001CE0, D_SX_6032938, 3.0f, 100.0f, 3000.0f, 2, 0, 0, 0, 1.0f, 1 },
    /*  29 */ { D_SX_6000840, D_SX_6032954, 1.0f, 100.0f, 3000.0f, 2, 1, 0, 0, 1.0f, 1 },
    /*  30 */ { D_A6_6012A40, D_A6_6028254, -2.0f, 2100.0f, 3001.0f, 0, 0, 7, 0, 0.0f, 2 },
    /*  31 */ { NULL, D_A6_60280E0, -2.0f, 2100.0f, 3001.0f, 0, 0, 0, 0, 0.0f, 3 },
    /*  32 */ { D_SX_6009950, D_SX_6032878, -1.0f, 2100.0f, 3001.0f, 0, 0, 0, 0, 0.0f, 1 },
    /*  33 */ { NULL, gDefaultCubeHitbox200, 2.0f, 100.0f, 3000.0f, 1, 0, 0, 0, 0.0f, 1 },
    /*  34 */ { D_SX_600B2B0, D_SX_6032894, -1.0f, 2100.0f, 3001.0f, 0, 0, 0, 0, 0.0f, 1 },
    /*  35 */ { D_SX_600A2E0, D_SX_60328B0, -1.0f, 2100.0f, 3001.0f, 0, 0, 0, 0, 0.0f, 1 },
    /*  36 */ { NULL, gDefaultCubeHitbox400, 2.0f, 200.0f, 3000.0f, 1, 0, 1, 0, 1.0f, 1 },
    /*  37 */ { D_SX_600B830, gDefaultCubeHitbox100, 1.5f, 100.0f, 3000.0f, 1, 0, 1, 0, 1.0f, 1 },
    /*  38 */ { NULL, D_SX_603238C, 1.0f, 500.0f, 3000.0f, 1, 0, 0, 0, 0.0f, 1 },
    /*  39 */ { D_SX_6020D20, D_SX_60328CC, -1.0f, 2100.0f, 3001.0f, 0, 0, 0, 0, 0.0f, 1 },
    /*  40 */ { NULL, gHitboxNone, 1.0f, 100.0f, 3001.0f, 2, 0, 0, 0, 0.0f, 1 },
    /*  41 */ { D_SY_60097E0, D_SY_6034478, -1.0f, 10000.0f, 3001.0f, 0, 0, 0, 0, 0.0f, 1 },
    /*  42 */ { D_SY_601D730, D_SY_603450C, -1.0f, 10000.0f, 3001.0f, 0, 0, 0, 0, 0.0f, 1 },
    /*  43 */ { NULL, gDefaultCubeHitbox100, 1.0f, 20000.0f, 3000.0f, 1, 0, 2, 0, 0.0f, 0 },
    /*  44 */ { D_SY_60102C0, D_SY_6034588, -1.0f, 10000.0f, 3001.0f, 0, 0, 0, 0, 0.0f, 1 },
    /*  45 */ { D_ME_6017B60, gDefaultCubeHitbox200, -1.0f, 300.0f, 3001.0f, 0, 0, 0, 0, 1.0f, 1 },
    /*  46 */ { D_ZO_6004D00, gDefaultCubeHitbox200, 1.0f, 100.0f, 3000.0f, 1, 0, 4, 0, 1.0f, 1 },
    /*  47 */ { D_ME_601A880, gDefaultCubeHitbox100, -1.0f, 100.0f, 3000.0f, 1, 0, 0, 0, 0.0f, 1 },
    /*  48 */ { NULL, D_SY_603405C, 0.3f, 100.0f, 3000.0f, 0, 0, 1, 0, 1.0f, 1 },
    /*  49 */ { NULL, D_SY_603405C, 0.3f, 100.0f, 3000.0f, 0, 0, 1, 0, 1.0f, 1 },
    /*  50 */ { NULL, D_SY_603405C, 0.3f, 100.0f, 3000.0f, 0, 0, 1, 0, 1.0f, 1 },
    /*  51 */ { D_SY_6015D60, D_SY_6034124, 2.0f, 100.0f, 3000.0f, 0, 0, 1, 0, 1.0f, 1 },
    /*  52 */ { NULL, D_ZO_602C1A0, -1.0f, 1000.0f, 3000.0f, 0, 0, 0, 0, 0.0f, 1 },
    /*  53 */ { D_SX_600B540, D_SX_60328E8, -1.0f, 2100.0f, 3001.0f, 0, 0, 0, 0, 0.0f, 1 },
    /*  54 */ { D_ENMY_SPACE_4000EC0, gDefaultCubeHitbox100, 1.5f, 100.0f, 3000.0f, 1, 0, 1, 0, 1.0f, 1 },
    /*  55 */ { D_ENMY_SPACE_4008D50, gDefaultCubeHitbox100, 1.5f, 100.0f, 3000.0f, 1, 0, 1, 0, 1.0f, 1 },
    /*  56 */ { NULL, gHitboxNone, -1.0f, 2000.0f, 3000.0f, 0, 0, 3, 0, 0.0f, 1 },
    /*  57 */ { D_SY_60102C0, gHitboxNone, -1.0f, 10000.0f, 3001.0f, 0, 0, 0, 0, 0.0f, 1 },
    /*  58 */ { D_SY_601F3D0, gHitboxNone, -1.0f, 10000.0f, 3001.0f, 0, 0, 0, 0, 0.0f, 1 },
    /*  59 */ { D_SY_6022B10, gHitboxNone, 2.0f, 100.0f, 3000.0f, 0, 0, 1, 0, 0.0f, 1 },
    /*  60 */ { D_SY_60209F0, gHitboxNone, 2.0f, 100.0f, 3000.0f, 0, 0, 1, 0, 0.0f, 1 },
    /*  61 */ { D_ME_6019430, gDefaultCubeHitbox200, 2.5f, 100.0f, 3000.0f, 1, 0, 0, 0, 1.0f, 1 },
    /*  62 */ { D_ME_6018960, gDefaultCubeHitbox100, 2.5f, 100.0f, 3000.0f, 1, 0, 0, 0, 1.0f, 1 },
    /*  63 */ { D_ME_6009F50, gHitboxNone, -1.0f, 100.0f, 3000.0f, 1, 0, 0, 0, 0.0f, 1 },
    /*  64 */ { NULL, gDefaultCubeHitbox200, 3.0f, 100.0f, 3000.0f, 1, 0, 0, 0, 1.0f, 1 },
    /*  65 */ { D_ME_600C2A0, gDefaultCubeHitbox200, -1.0f, 100.0f, 8000.0f, 1, 0, 0, 0, 0.0f, 1 },
    /*  66 */ { D_ME_600BD40, gDefaultCubeHitbox100, -1.0f, 100.0f, 8000.0f, 1, 0, 0, 0, 0.0f, 1 },
    /*  67 */ { NULL, D_ME_602F604, 3.0f, 100.0f, 3000.0f, 2, 0, 1, 0, 1.0f, 1 },
    /*  68 */ { D_SY_60205D0, D_SY_603445C, 3.0f, 100.0f, 3000.0f, 1, 0, 0, 0, 1.0f, 1 },
    /*  69 */ { D_SY_60036A0, D_SY_6034664, -1.0f, 10000.0f, 3001.0f, 0, 0, 0, 0, 0.0f, 1 },
    /*  70 */ { D_SY_601AD70, gHitboxNone, 4.0f, 100.0f, 3000.0f, 0, 0, 1, 0, 0.0f, 1 },
    /*  71 */ { D_arwing_3007650, gHitboxNone, 1.0f, 100.0f, 3000.0f, 2, 0, 5, 0, 0.0f, 1 },
    /*  72 */ { D_SY_60034D0, D_SY_60347D4, 3.0f, 100.0f, 3000.0f, 1, 0, 0, 0, 0.0f, 1 },
    /*  73 */ { D_SY_6005360, D_SY_6034770, -1.0f, 10000.0f, 3001.0f, 0, 0, 0, 0, 0.0f, 1 },
    /*  74 */ { D_SY_600F6C0, D_SY_60347F0, -1.0f, 10000.0f, 3001.0f, 0, 0, 0, 0, 0.0f, 1 },
    /*  75 */ { D_SY_601B610, gHitboxNone, -1.0f, 10000.0f, 3001.0f, 0, 0, 1, 0, 0.0f, 1 },
    /*  76 */ { D_SY_601C6A0, gHitboxNone, -1.0f, 10000.0f, 3001.0f, 0, 0, 1, 0, 0.0f, 1 },
    /*  77 */ { D_SY_60188D0, D_SY_603486C, 3.0f, 100.0f, 3001.0f, 0, 0, 1, 0, 0.0f, 1 },
    /*  78 */ { NULL, gDefaultCubeHitbox150, 1.0f, 100.0f, 3000.0f, 2, 0, 0, 0, 1.0f, 0 },
    /*  79 */ { NULL, D_ZO_602C294, 1.0f, 100.0f, 3000.0f, 0, 0, 0, 0, 1.0f, 1 },
    /*  80 */ { NULL, D_VE1_601B474, -1.0f, 100.0f, 3000.0f, 2, 0, 0, 0, 0.0f, 1 },
    /*  81 */ { NULL, gHitboxNone, -1.0f, 100.0f, 3000.0f, 0, 0, 0, 0, 0.0f, 1 },
    /*  82 */ { NULL, gDefaultCubeHitbox100, 2.0f, 100.0f, 3000.0f, 1, 0, 1, 0, 1.0f, 1 },
    /*  83 */ { NULL, D_AQ_6030B4C, 1.0f, 100.0f, 3000.0f, 2, 0, 0, 0, 60.0f, 1 },
    /*  84 */ { D_VE1_9012180, D_VE1_601B43C, -1.0f, 100.0f, 3000.0f, 0, 0, 0, 0, 0.0f, 1 },
    /*  85 */ { NULL, gDefaultCubeHitbox100, 1.0f, 20000.0f, 3000.0f, 1, 0, 2, 0, 0.0f, 0 },
    /*  86 */ { NULL, gDefaultCubeHitbox100, 1.0f, 20000.0f, 3000.0f, 1, 0, 2, 0, 0.0f, 0 },
    /*  87 */ { D_VE1_900EFC0, gHitboxNone, 1.0f, 100.0f, 3000.0f, 1, 1, 0, 0, 0.0f, 1 },
    /*  88 */ { NULL, D_AQ_6030B30, 1.0f, 100.0f, 3000.0f, 1, 0, 0, 0, 1.0f, 1 },
    /*  89 */ { NULL, D_AQ_6030B14_f32, 1.0f, 100.0f, 3000.0f, 1, 0, 0, 0, 1.0f, 1 },
    /*  90 */ { D_MA_601C520, D_MA_60368FC, 1.0f, 100.0f, 3000.0f, 1, 0, 0, 0, 0.0f, 1 },
    /*  91 */ { D_MA_600AF40, D_MA_60368E0, -1.0f, 100.0f, 3000.0f, 1, 0, 0, 0, 0.0f, 1 },
    /*  92 */ { D_WZ_7000C40, gWarpZoneEvent92Hitbox, -1.0f, 2100.0f, 3001.0f, 0, 0, 0, 0, 0.0f, 1 },
    /*  93 */ { D_WZ_70010E0, gWarpZoneEvent93Hitbox, -1.0f, 2100.0f, 3001.0f, 0, 0, 0, 0, 0.0f, 1 },
    /*  94 */ { D_WZ_7000E80, gWarpZoneEvent94Hitbox, 2.5f, 100.0f, 3000.0f, 1, 0, 0, 0, 1.0f, 1 },
    /*  95 */ { D_WZ_70008F0, gDefaultCubeHitbox100, -1.0f, 100.0f, 8000.0f, 1, 0, 0, 0, 0.0f, 0 },
    /*  96 */ { D_WZ_7000280, gWarpZoneEvent96Hitbox, -1.0f, 1000.0f, 3000.0f, 1, 0, 0, 0, 0.0f, 0 },
    /*  97 */ { D_ME_600AC70, gDefaultCubeHitbox100, -1.0f, 100.0f, 3000.0f, 1, 0, 0, 0, 0.0f, 1 },
    /*  98 */ { D_MA_601A2B0, D_MA_60364C0, 1.0f, 100.0f, 3000.0f, 1, 1, 0, 0, 0.0f, 1 },
    /*  99 */ { D_VE1_6002500, D_VE1_601B944, -1.0f, 100.0f, 3000.0f, 0, 0, 0, 0, 0.0f, 1 },
    /* 100 */ { D_VE1_60043F0, gHitboxNone, -1.0f, 100.0f, 3000.0f, 0, 0, 0, 0, 0.0f, 1 },
    /* 101 */ { D_VE1_6004310, gHitboxNone, -1.0f, 100.0f, 3000.0f, 0, 0, 0, 0, 0.0f, 1 },
    /* 102 */ { D_TR_6002740, D_TR_6009D18, -1.0f, 100.0f, 3000.0f, 0, 0, 0, 0, 0.0f, 1 },
    /* 103 */ { NULL, gHitboxNone, -1.0f, 500.0f, 3000.0f, 0, 0, 0, 0, 0.0f, 0 },
    /* 104 */ { NULL, gHitboxNone, -1.0f, 500.0f, 3000.0f, 0, 0, 0, 0, 0.0f, 0 },
    /* 105 */ { NULL, gDefaultCubeHitbox200, 1.0f, 100.0f, 3000.0f, 0, 0, 0, 0, 1.0f, 1 },
    /* 106 */ { NULL, gDefaultCubeHitbox100, 1.0f, 100.0f, 3000.0f, 0, 0, 6, 0, 0.0f, 0 },
    /* 107 */ { D_MA_6002890, D_MA_60368E0, -1.0f, 100.0f, 3000.0f, 1, 0, 0, 0, 0.0f, 1 },
};
static u8 D_800D0DBC[6][4] = {
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
            if (this->info.unk_10 > 10000.0f) {
                this->info.unk_10 = 100.0f;
            }
            break;

        case EV_OPC(EVOP_INIT_ACTOR):
            Audio_KillSfxBySource(this->sfxSource);
            this->unk_0B4 = actorScript[this->aiIndex + 1];

            if (this->unk_0B4 == EINFO_40) {
                this->timer_0C2 = 10000;
            } else {
                this->timer_0C2 = 0;
            }

            this->fwork[11] = 0.0f;
            this->fwork[12] = 0.0f;

            if ((this->unk_0B4 == EINFO_64) || (this->unk_0B4 == EINFO_81)) {
                this->fwork[15] = 0.0f;
            } else if (this->unk_0B4 == EINFO_79) {
                this->info.drawType = 2;
            }

            this->health = actorScript[this->aiIndex] & 0x1FF;
            this->aiIndex += 2;

            if ((this->unk_0B4 >= EINFO_200) && (this->unk_0B4 < EINFO_300)) {
                this->unk_046 = 100;
                this->info.hitbox = gDefaultCubeHitbox200;
                this->info.unk_1C = 1.0f;

                for (i = 0; i < 2; i++) {
                    if (D_ctx_80176550[i] == 0) {
                        D_ctx_80176550[i] = 1;
                        this->unk_046 = i;
                        for (j = 0; j < 100; j++) {
                            D_ctx_80176878[i][j] = this->obj.pos.y;
                            D_ctx_80176B98[i][j] = this->obj.pos.z;
                        }
                        if (this->unk_0B4 == EINFO_200) {
                            AUDIO_PLAY_SFX(0x11032049, this->sfxSource, 4);
                        }
                        break;
                    }
                }

                if (this->unk_046 == 100) {
                    Object_Kill(&this->obj, this->sfxSource);
                }
            }

            if ((this->unk_0B4 == EINFO_2) || (this->unk_0B4 == EINFO_43)) {
                this->unk_0C9 = 1;
                this->iwork[11] = 1;
            }

            if (this->unk_0B4 == EINFO_81) {
                this->unk_0C9 = 1;
            }

            if (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_3) {
                if (this->unk_0B4 == EINFO_86) {
                    Audio_PlayFanfare(SEQ_ID_KATT, 20, 10, 10);
                }
                if (this->unk_0B4 == EINFO_85) {
                    Audio_PlayFanfare(SEQ_ID_BILL, 20, 10, 10);
                }
            }

            if (this->unk_0B4 == EINFO_103) {
                this->unk_0B6 = 0;
            }

            if (this->unk_0B4 == EINFO_104) {
                this->unk_0B6 = Animation_GetFrameCount(D_VE2_6014658) - 1;
            }

            if (this->unk_0B4 < EINFO_200) {
                this->info.hitbox = LOAD_ASSET(D_800D003C[this->unk_0B4].hitbox);
                this->scale = D_800D003C[this->unk_0B4].scale;
                this->info.unk_16 = D_800D003C[this->unk_0B4].info_unk_16;
                this->info.unk_14 = D_800D003C[this->unk_0B4].info_unk_14;
                this->info.unk_19 = D_800D003C[this->unk_0B4].info_unk_19;
                this->info.unk_1C = D_800D003C[this->unk_0B4].info_unk_1C;
                this->info.bonus = D_800D003C[this->unk_0B4].bonus;

                if (this->unk_0B4 == EINFO_78) {
                    this->info.damage = 0;
                }

                this->info.unk_10 = D_800D003C[this->unk_0B4].info_unk_10;
                this->fwork[25] = D_800D003C[this->unk_0B4].unk_10;

                switch (D_800D003C[this->unk_0B4].sfx) {
                    case 1:
                        if (!((gCurrentLevel == LEVEL_SOLAR) || (this->unk_0B4 == EINFO_6) ||
                              ((gCurrentLevel == LEVEL_CORNERIA) && (this->unk_0B4 == EINFO_8)))) {
                            AUDIO_PLAY_SFX(0x31000011, this->sfxSource, 4);
                        }
                        break;
                    case 2:
                        AUDIO_PLAY_SFX(0x3100000C, this->sfxSource, 4);
                        break;
                    case 3:
                        AUDIO_PLAY_SFX(0x11030010, this->sfxSource, 0);
                        break;
                    case 4:
                        AUDIO_PLAY_SFX(0x31012039, this->sfxSource, 4);
                        break;
                    case 5:
                        AUDIO_PLAY_SFX(0x1900302B, this->sfxSource, 0);
                        break;
                    case 6:
                        AUDIO_PLAY_SFX(0x31000014, this->sfxSource, 4);
                        break;
                    case 7:
                        AUDIO_PLAY_SFX(0x31000015, this->sfxSource, 4);
                        break;
                }

                if (gPlayer[0].unk_138 < this->obj.pos.z) {
                    this->info.unk_10 = 3000.0f;
                }

                if (this->info.unk_16 == 0) {
                    this->obj.rot.z = this->fwork[23] = this->unk_0F4.z;
                    if (this->unk_0B4 != EINFO_31) {
                        this->unk_0F4.z = 0.0f;
                    }
                }
            }
            ActorEvent_ProcessScript(this);
            break;

        case EV_OPC(EVOP_SET_TEAM_ID):
            this->iwork[12] = actorScript[this->aiIndex + 1];

            if (this->iwork[12] <= TEAM_ID_PEPPY) {
                D_enmy2_800CFF80[this->iwork[12]] = this->index;
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

        case EV_OPC(EVOP_SET_TO_IWORK_9):
            D_ctx_80177E78 = this->index;
            D_ctx_80177F10.x = this->obj.pos.x;
            D_ctx_80177F10.y = this->obj.pos.y;
            D_ctx_80177F10.z = this->obj.pos.z;
            D_ctx_80177E88.x = this->obj.rot.x;
            D_ctx_80177E88.y = this->obj.rot.y;
            D_ctx_80177E88.z = this->obj.rot.z;
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
                this->info.hitbox = SEGMENTED_TO_VIRTUAL(gDefaultCubeHitbox200);
                this->state = EVSTATE_ME_AS_CLOSE;
                this->aiIndex += 2;
                break;
            }

            this->unk_048 = actorScript[this->aiIndex + 1];

            if (this->unk_048 == EVACT_3) {
                this->timer_04C = 4;
            }

            if (this->unk_048 == EVACT_13) {
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
            Audio_SetBaseSfxReverb(actorScript[this->aiIndex + 1]);
            this->aiIndex += 2;
            ActorEvent_ProcessScript(this);
            break;

        case EV_OPC(EVOP_PLAY_MSG):
            msg = Message_PtrFromId(actorScript[this->aiIndex + 1]);
            if ((msg != NULL) && (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_3)) {
                Radio_PlayMessage(msg, actorScript[this->aiIndex] & 0x1FF);
            }
            this->aiIndex += 2;
            ActorEvent_ProcessScript(this);
            break;

        case EV_OPC(EVOP_SET_GROUND):
            if ((gGroundType == GROUNDTYPE_WATER) && (actorScript[this->aiIndex + 1] != 2)) {
                Audio_KillSfxBySourceAndId(gPlayer[0].sfxSource, 0x1100000B);
            }
            gGroundType = actorScript[this->aiIndex + 1];
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
                this->unk_0D0 = 1;
                this->damage = actorScript[this->aiIndex] & 0x1FF;
                this->unk_0D4 = 100;
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
                    gTexturedLines[i].unk_28 = 3.0f;
                    gTexturedLines[i].unk_04.x = this->obj.pos.x - this->vel.x;
                    gTexturedLines[i].unk_04.y = this->obj.pos.y - this->vel.y;
                    gTexturedLines[i].unk_04.z = this->obj.pos.z - this->vel.z;
                    gTexturedLines[i].unk_2C = D_800D0DBC[actorScript[this->aiIndex + 1]][0];
                    gTexturedLines[i].unk_2D = D_800D0DBC[actorScript[this->aiIndex + 1]][1];
                    gTexturedLines[i].unk_2E = D_800D0DBC[actorScript[this->aiIndex + 1]][2];
                    gTexturedLines[i].unk_2F = D_800D0DBC[actorScript[this->aiIndex + 1]][3];
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

        case EV_OPC(EVOP_SET_STATE_6):
            this->state = EVSTATE_6;
            this->timer_0BC = actorScript[this->aiIndex + 1];
            this->fwork[24] = actorScript[this->aiIndex] & 0x1FF;
            this->aiIndex += 2;
            break;

        case EV_OPC(EVOP_SET_STATE_7):
            this->state = EVSTATE_7;
            this->timer_0BC = actorScript[this->aiIndex + 1];
            this->fwork[24] = actorScript[this->aiIndex] & 0x1FF;
            this->aiIndex += 2;
            break;

        case EV_OPC(EVOP_SET_STATE_8):
            this->state = EVSTATE_8;
            this->timer_0BC = actorScript[this->aiIndex + 1];
            this->fwork[24] = actorScript[this->aiIndex] & 0x1FF;
            this->aiIndex += 2;
            break;

        case EV_OPC(EVOP_SET_STATE_9):
            this->state = EVSTATE_9;
            this->timer_0BC = actorScript[this->aiIndex + 1];
            this->fwork[24] = actorScript[this->aiIndex] & 0x1FF;
            this->aiIndex += 2;
            break;

        case EV_OPC(EVOP_SET_TARGET):
            this->state = EVSTATE_WAIT;
            this->iwork[1] = D_enmy2_800CFF80[actorScript[this->aiIndex] & 0x1FF];
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

        case EV_OPC(EVOP_SET_STATE_14):
            this->state = EVSTATE_14;
            this->timer_0BC = actorScript[this->aiIndex + 1];
            this->fwork[24] = actorScript[this->aiIndex] & 0x1FF;
            this->aiIndex += 2;
            break;

        case EV_OPC(EVOP_SET_STATE_15):
            this->state = EVSTATE_15;
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

        case EV_OPC(EVOP_SET_IWORK_13):
            this->timer_0C0 = actorScript[this->aiIndex + 1];
            this->iwork[13] = 1;
            this->aiIndex += 2;
            ActorEvent_ProcessScript(this);
            break;

        case EV_OPC(EVOP_CLEAR_IWORK_13):
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
        gTexturedLines[this->iwork[8]].unk_10.x = this->obj.pos.x;
        gTexturedLines[this->iwork[8]].unk_10.y = this->obj.pos.y;
        gTexturedLines[this->iwork[8]].unk_10.z = this->obj.pos.z;
    }
}

void ActorEvent_8006EAC4(Effect* effect, f32 xPos, f32 yPos, f32 zPos) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = OBJ_EFFECT_374;

    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;

    effect->timer_50 = 20;
    Object_SetInfo(&effect->info, effect->obj.id);
    AUDIO_PLAY_SFX(0x2900201D, effect->sfxSource, 4);
}

void ActorEvent_8006EB64(f32 xPos, f32 yPos, f32 zPos) {
    s32 i;

    for (i = 50; i < ARRAY_COUNT(gEffects); i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            ActorEvent_8006EAC4(&gEffects[i], xPos, yPos, zPos);
            break;
        }
    }
}

void ActorEvent_8006EBC0(Actor* actor, f32 xPos, f32 yPos, f32 zPos) {
    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_225;

    actor->obj.pos.x = xPos;
    actor->obj.pos.y = yPos;
    actor->obj.pos.z = zPos;

    Object_SetInfo(&actor->info, actor->obj.id);
    actor->info.unk_16 = 2;
    AUDIO_PLAY_SFX(0x2900201D, actor->sfxSource, 4);
}

void ActorEvent_8006EC60(f32 xPos, f32 yPos, f32 zPos) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gActors); i++) {
        if (gActors[i].obj.status == OBJ_FREE) {
            ActorEvent_8006EBC0(&gActors[i], xPos, yPos, zPos);
            break;
        }
    }
}

void func_enmy2_8006ECBC(PlayerShotId objId, PlayerShot* shot, s32 unk0E4, f32 xPos, f32 yPos, f32 zPos, f32 arg6,
                         f32 arg7, f32 arg8, f32 xRot, f32 yRot, f32 zRot) {
    PlayerShot_Initialize(shot);
    shot->obj.status = 1;

    shot->vel.z = arg8;
    shot->vel.x = arg6;
    shot->vel.y = arg7;

    shot->obj.pos.x = xPos;
    shot->obj.pos.y = yPos;
    shot->obj.pos.z = zPos;

    shot->obj.rot.x = xRot + 180.0f;
    shot->obj.rot.y = yRot;
    shot->obj.rot.z = -zRot;

    shot->obj.id = objId;
    shot->unk_58 = 1;
    shot->unk_60 = 0;

    if (objId == PLAYERSHOT_9) {
        shot->unk_64 = 120;
    } else {
        shot->unk_64 = 30;
    }
    shot->playerNum = unk0E4 + 100;

    if (gLevelMode == LEVELMODE_ALL_RANGE) {
        if (unk0E4 + 100 <= AI360_PEPPY + 100) {
            AUDIO_PLAY_SFX(0x2900000D, shot->sfxSource, 4);
        } else {
            AUDIO_PLAY_SFX(0x29002002, shot->sfxSource, 4);
        }
    } else if ((unk0E4 < 60) && (gActors[unk0E4].obj.id == OBJ_ACTOR_EVENT) && (gActors[unk0E4].iwork[12] > 0)) {
        AUDIO_PLAY_SFX(0x2900000D, shot->sfxSource, 4);
    } else if (unk0E4 + 100 == 200) {
        shot->playerNum = 100;
        AUDIO_PLAY_SFX(0x19030037, shot->sfxSource, 0);
    } else {
        AUDIO_PLAY_SFX(0x29002002, shot->sfxSource, 4);
    }
}

void func_enmy2_8006EEFC(s32 unk0E4, f32 xPos, f32 yPos, f32 zPos, f32 arg4, f32 arg5, f32 arg6, f32 xRot, f32 yRot,
                         f32 zRot) {
    s32 i;

    for (i = 0; i < 10; i++) {
        if (gPlayerShots[i].obj.status == 0) {
            func_enmy2_8006ECBC(PLAYERSHOT_1, &gPlayerShots[i], unk0E4, xPos, yPos, zPos, arg4, arg5, arg6, xRot, yRot,
                                zRot);
            break;
        }
    }
}

void func_enmy2_8006EFA0(s32 unk0E4, f32 xPos, f32 yPos, f32 zPos, f32 arg4, f32 arg5, f32 arg6, f32 xRot, f32 yRot,
                         f32 zRot) {
    s32 i;

    for (i = 0; i < 10; i++) {
        if (gPlayerShots[i].obj.status == 0) {
            func_enmy2_8006ECBC(PLAYERSHOT_9, &gPlayerShots[i], unk0E4, xPos, yPos, zPos, arg4, arg5, arg6, xRot, yRot,
                                zRot);
            break;
        }
    }
}

void ActorEvent_8006F044(Effect* effect, f32 xPos, f32 yPos, f32 zPos, f32 arg4) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = OBJ_EFFECT_347;

    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;

    effect->scale1 = arg4;
    effect->unk_44 = 100;
    Object_SetInfo(&effect->info, effect->obj.id);
    func_effect_8007A6F0(&effect->obj.pos, 0x2903B009);
}

void ActorEvent_8006F0D8(f32 xPos, f32 yPos, f32 zPos, f32 arg3) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            ActorEvent_8006F044(&gEffects[i], xPos, yPos, zPos, arg3);
            break;
        }
    }
}

void ActorEvent_8006F140(Effect* effect, f32 xPos, f32 yPos, f32 zPos, f32 arg4) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = OBJ_EFFECT_394;

    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;

    effect->scale1 = arg4;
    effect->unk_44 = 100;
    effect->unk_78 = 102;
    effect->unk_7A = 18;
    Object_SetInfo(&effect->info, effect->obj.id);
    effect->info.damage = 40;
    func_effect_8007A6F0(&effect->obj.pos, 0x2903B009);
}

void ActorEvent_8006F1EC(f32 xPos, f32 yPos, f32 zPos, f32 arg3) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            ActorEvent_8006F140(&gEffects[i], xPos, yPos, zPos, arg3);
            break;
        }
    }
}

void ActorEvent_8006F254(ActorEvent* this) {
    Vec3f sp54;
    Vec3f sp48;

    Matrix_RotateY(gCalcMatrix, this->vwork[29].y * M_DTOR, 0);
    Matrix_RotateX(gCalcMatrix, this->vwork[29].x * M_DTOR, 1);
    Matrix_RotateZ(gCalcMatrix, (this->vwork[29].z + this->unk_0F4.z) * M_DTOR, 1);
    Matrix_RotateY(gCalcMatrix, this->unk_0F4.y * M_DTOR, 1);
    Matrix_RotateX(gCalcMatrix, this->unk_0F4.x * M_DTOR, 1);

    sp54.x = 0.0f;
    sp54.y = 0.0f;
    sp54.z = gEnemyShotSpeed;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp54, &sp48);
    func_effect_8007F04C(OBJ_EFFECT_353, this->obj.pos.x + sp48.x, this->obj.pos.y + sp48.y, this->obj.pos.z + sp48.z,
                         this->obj.rot.x, this->obj.rot.y, this->obj.rot.z, this->vwork[29].x, this->vwork[29].y,
                         this->vwork[29].z + this->unk_0F4.z, sp48.x, sp48.y, sp48.z, 1.0f);
}

void ActorEvent_ProcessActions(ActorEvent* this) {
    s32 var_v1;
    Vec3f sp78;
    Vec3f sp6C;
    Sprite* sprite;

    if ((gPlayer[0].state_1C8 == PLAYERSTATE_1C8_3) && (this->unk_0B4 != EINFO_52) && (this->unk_0B4 != EINFO_103) &&
        (this->unk_0B4 != EINFO_104) && (this->unk_0B4 != EINFO_48) && (this->unk_0B4 != EINFO_49) &&
        (this->unk_0B4 != EINFO_50)) {
        switch (this->unk_048) {
            case EVACT_NONE:
                break;

            case EVACT_1:
                ActorEvent_8006F254(this);
                this->unk_048 = EVACT_NONE;
                break;

            case EVACT_2:
                if (this->obj.pos.z < (gPlayer[0].unk_138 - 600.0f)) {
                    func_effect_8007F11C(OBJ_EFFECT_353, this->obj.pos.x, this->obj.pos.y, this->obj.pos.z,
                                         gEnemyShotSpeed);
                }
                this->unk_048 = EVACT_NONE;
                break;

            case EVACT_3:
                if (this->timer_0BE == 0) {
                    this->timer_0BE = 6;
                    sp78.x = 0.0f;
                    sp78.y = 0.0f;
                    sp78.z = 100.0f;
                    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp78, &sp6C);
                    func_enmy2_8006EEFC(this->index, this->obj.pos.x + (sp6C.x * 1.5), this->obj.pos.y + (sp6C.y * 1.5),
                                        this->obj.pos.z + (sp6C.z * 1.5), sp6C.x, sp6C.y, sp6C.z, this->unk_0F4.x,
                                        this->unk_0F4.y, this->vwork[29].z + this->unk_0F4.z);
                    this->timer_0C2 = 2;
                    this->timer_04C--;
                    if (this->timer_04C <= 0) {
                        this->unk_048 = EVACT_NONE;
                    }
                }
                break;

            case EVACT_4:
                ActorEvent_8006EB64(this->obj.pos.x, this->obj.pos.y - 20.0f, this->obj.pos.z);
                this->unk_048 = EVACT_NONE;
                break;

            case EVACT_5:
                Matrix_RotateY(gCalcMatrix, this->vwork[29].y * M_DTOR, 0);
                Matrix_RotateX(gCalcMatrix, this->vwork[29].x * M_DTOR, 1);
                Matrix_RotateZ(gCalcMatrix, (this->vwork[29].z + this->unk_0F4.z) * M_DTOR, 1);
                Matrix_RotateY(gCalcMatrix, this->unk_0F4.y * M_DTOR, 1);
                Matrix_RotateX(gCalcMatrix, this->unk_0F4.x * M_DTOR, 1);

                sp78.x = 0.0f;
                sp78.y = 0.0f;
                sp78.z = gEnemyShotSpeed;

                Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp78, &sp6C);
                func_effect_8007F04C(OBJ_EFFECT_355, this->obj.pos.x + sp6C.x, this->obj.pos.y + sp6C.y,
                                     this->obj.pos.z + sp6C.z, this->obj.rot.x, this->obj.rot.y, this->obj.rot.z,
                                     this->vwork[29].x, this->vwork[29].y, this->vwork[29].z + this->unk_0F4.z, sp6C.x,
                                     sp6C.y, sp6C.z, 1.0f);
                this->unk_048 = EVACT_NONE;
                break;

            case EVACT_6:
                if (this->obj.pos.z < (gPlayer[0].unk_138 - 600.0f)) {
                    func_effect_8007F11C(OBJ_EFFECT_355, this->obj.pos.x, this->obj.pos.y, this->obj.pos.z,
                                         gEnemyShotSpeed);
                }
                this->unk_048 = EVACT_NONE;
                break;

            case EVACT_7:
                if (this->obj.pos.z < (gPlayer[0].unk_138 - 600.0f)) {
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
                    ActorEvent_8006F1EC(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 12.0f);
                } else {
                    ActorEvent_8006F0D8(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 40.0f);
                }
                Object_Kill(&this->obj, this->sfxSource);
                break;

            case EVACT_10:
                if (gCurrentLevel == LEVEL_AQUAS) {
                    ActorEvent_8006F1EC(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 6.0f);
                } else {
                    ActorEvent_8006F0D8(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 15.0f);
                }
                Object_Kill(&this->obj, this->sfxSource);
                break;

            case EVACT_11:
                func_effect_8007BFFC(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, this->vel.x, this->vel.y,
                                     this->vel.z, this->scale * 3.0f, 15);
                Actor_Despawn(this);
                Object_Kill(&this->obj, this->sfxSource);
                func_effect_8007A6F0(&this->obj.pos, 0x2903B009);
                break;

            case EVACT_DESPAWN:
                Actor_Despawn(this);
                Object_Kill(&this->obj, this->sfxSource);
                break;

            case EVACT_13:
                if (this->timer_0BE > 25) {
                    Math_SmoothStepToF(&this->fwork[15], 90.0f, 0.2f, 8.0f, 0.01f);
                }
                if (this->timer_0BE < 25) {
                    Math_SmoothStepToF(&this->fwork[15], 0.0f, 0.2f, 8.0f, 0.01f);
                }
                if (this->timer_0BE == 30) {
                    ActorEvent_8006EC60(this->obj.pos.x, this->obj.pos.y - 50.0f, this->obj.pos.z);
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
                if (this->obj.pos.z < (gPlayer[0].camEye.z - 600.0f)) {
                    func_effect_8007F20C(OBJ_EFFECT_353, this->obj.pos.x, this->obj.pos.y, this->obj.pos.z,
                                         gEnemyShotSpeed);
                }
                this->unk_048 = EVACT_NONE;
                break;

            case EVACT_GFOX_COVER_FIRE:
                for (var_v1 = 0, sprite = gSprites; var_v1 < 40; var_v1++, sprite++) {

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
                        Matrix_RotateY(gCalcMatrix, M_DTOR * sp54, 0);
                        Matrix_RotateX(gCalcMatrix, M_DTOR * sp58, 1);
                        sp6C.x = 0.0f;
                        sp6C.y = 0.0f;
                        sp6C.z = 50.0f;
                        Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp6C, &sp78);
                        func_enmy2_8006EFA0(100, this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, sp78.x, sp78.y,
                                            sp78.z, sp58, sp54, 0.0f);
                        break;
                    }
                }

                this->unk_048 = EVACT_NONE;
                break;

            case EVACT_19:
                func_effect_80083D2C(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 40.0f);
                this->unk_048 = EVACT_NONE;
                break;
        }
    }
}

void ActorEvent_8006FE28(ActorEvent* this) {
    if ((fabsf(this->obj.pos.x - gPlayer[0].pos.x) < 100.0f) && (fabsf(this->obj.pos.y - gPlayer[0].pos.y) < 100.0f) &&
        (fabsf(this->obj.pos.z - gPlayer[0].unk_138) < 50.0f)) {
        func_enmy_80067A40();
        Audio_KillSfxBySourceAndId(this->sfxSource, 0x1900302B);
        Object_Kill(&this->obj, this->sfxSource);
    }
}

void ActorEvent_8006FEEC(ActorEvent* this) {
    s32 i;

    if ((this->unk_0D0 != 0) && (this->health != 0)) {
        this->unk_0D0 = 0;
        this->timer_0C6 = 15;
        this->health -= this->damage;

        if (this->health <= 0) {
            for (i = 3; i < 11; i++) {
                Zoness_801900FC(&this->vwork[i], &this->vwork[i + 11], RAND_FLOAT_CENTERED(20.0f), RAND_FLOAT(-10.0f),
                                RAND_FLOAT(10.0f), 41, this->scale, 200, i);
            }
            this->itemDrop = DROP_NONE;
            Actor_Despawn(this);
            Object_Kill(&this->obj, this->sfxSource);
            func_effect_8007A6F0(&this->obj.pos, 0x29018036);
            func_effect_8007D2C8(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 4.0f);
        } else {
            AUDIO_PLAY_SFX(0x29033037, this->sfxSource, 4);
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
        this->unk_0D0 = 0;
        return true;
    }
    return false;
}

void ActorEvent_800701E0(ActorEvent* this) {
    Vec3f sp3C;
    f32 var_fv1;
    f32 temp_fv1;

    if (ActorEvent_800700A4(this)) {
        return;
    }
    if ((this->unk_0D0 != 0) && (this->unk_0B4 == EINFO_67) && (this->unk_0D2 == 0)) {
        this->unk_0D0 = 0;
    }

    if ((this->unk_0D0 != 0) && (this->unk_0B4 == EINFO_83) && (this->timer_0C2 >= 2)) {
        this->unk_0D0 = 0;
    }

    if ((this->unk_0D0 != 0) &&
        (((this->unk_0B4 == EINFO_64) && (this->unk_0D2 == 2)) || (this->unk_0B4 != EINFO_64))) {
        if (this->iwork[12] >= TEAM_ID_KATT) {
            this->damage = 0;
        }

        if ((this->iwork[12] >= TEAM_ID_FALCO) && (this->iwork[12] <= TEAM_ID_PEPPY)) {
            gTeamShields[this->iwork[12]] -= this->damage;
        } else if ((this->unk_0B4 == EINFO_83) && ((this->damage == 30) || (this->damage == 31))) {
            this->health = 0;
        } else {
            this->health -= this->damage;
        }

        if (this->health <= 0) {
            if (this->unk_0B4 == EINFO_106) {
                BonusText_Display(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 3);
                if (1) {}
                gHitCount += 4;
                D_ctx_80177850 = 15;
            }

            if (this->unk_0B4 != EINFO_83) {
                if ((this->unk_0B4 == EINFO_6) && (gCurrentLevel == LEVEL_SOLAR)) {
                    AUDIO_PLAY_SFX(0x29018036, this->sfxSource, 4);
                } else {
                    AUDIO_PLAY_SFX(0x2903700B, this->sfxSource, 4);
                }

                this->obj.status = OBJ_DYING;
                var_fv1 = 0.7f;

                if (gLevelType == LEVELTYPE_SPACE) {
                    var_fv1 = 0.3f;
                }

                if (((Rand_ZeroOne() < var_fv1) || (this->iwork[12] != 0)) && (this->info.unk_14 == 0) &&
                    (this->unk_0B4 != EINFO_13) && (this->unk_0B4 != EINFO_14) && (this->unk_0B4 != EINFO_61) &&
                    (this->damage <= 30) && (this->unk_0B4 != EINFO_62) && (this->unk_0B4 != EINFO_64) &&
                    (this->unk_0B4 != EINFO_72) && (this->unk_0B4 != EINFO_68)) {
                    func_effect_8007D2C8(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, this->scale * 4.0f);
                    this->unk_0D0 = 0;
                }

                this->timer_0C2 = 10;
                this->timer_0BE = 0;
                this->unk_046 = 255;
                this->unk_048 = 900;
                this->unk_0C9 = 1;

                if (gLevelType == LEVELTYPE_PLANET) {
                    this->timer_04C = RAND_INT(2.9f);
                    if (this->unk_0B4 == EINFO_2) {
                        this->timer_04C = 1;
                        if (this->obj.pos.x < this->unk_0D8.x) {
                            func_play_800A69F8(1, this->obj.pos.x + 20.0f, this->obj.pos.y, this->obj.pos.z);
                            this->fwork[17] = 777.0f;
                        } else {
                            func_play_800A69F8(0, this->obj.pos.x - 20.0f, this->obj.pos.y, this->obj.pos.z);
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
                        if (((this->obj.pos.z + D_ctx_80177D20) > -3000.0f) && (this->vel.z > 0.0f)) {
                            this->vel.z = RAND_FLOAT(-10.0f);
                        }
                    }

                    if (this->unk_0B4 == EINFO_90) {
                        this->timer_04C = 999;
                    }
                } else {
                    switch (this->unk_0B4) {
                        case EINFO_13:
                            func_enmy_800654E4(&this->obj);
                            break;

                        case EINFO_61:
                            Meteo_8018CCF8(this);
                            break;

                        case EINFO_27:
                            this->obj.pos.y -= this->vel.y;
                            this->obj.status = OBJ_ACTIVE;
                            func_effect_8007D0E0(this->obj.pos.x - this->vel.x, this->obj.pos.y + 30.0f,
                                                 this->obj.pos.z - this->vel.z, this->scale * 5.0f);
                            this->unk_0D0 = 0;
                            this->timer_0C2 = 10000;
                            this->info.unk_1C = 0.0f;
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

            if (this->unk_0B4 == EINFO_82) {
                AUDIO_PLAY_SFX(0x11000055, this->sfxSource, 0);
                this->unk_0D0 = 1;
                func_effect_8007C688(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 3.0f, 60);
            }
        } else {
            this->timer_0C6 = 20;
            if ((this->unk_0B4 == EINFO_6) && (gCurrentLevel == LEVEL_SOLAR)) {
                AUDIO_PLAY_SFX(0x29033037, this->sfxSource, 4);
            } else if (this->health < 20) {
                AUDIO_PLAY_SFX(0x2943500F, this->sfxSource, 4);
            } else {
                AUDIO_PLAY_SFX(0x2903300E, this->sfxSource, 4);
            }

            if ((this->unk_0B4 != EINFO_13) && (this->unk_0B4 != EINFO_61) && (this->unk_0B4 != EINFO_83)) {
                func_effect_8007D10C(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, this->scale * 1.5f);
            }

            if (((gLevelMode == LEVELMODE_ALL_RANGE) || (gLevelMode == LEVELMODE_UNK_2)) &&
                (this->unk_0B4 != EINFO_21) && (this->unk_0B4 != EINFO_23)) {
                this->fwork[13] = 20.0f;
                if (this->obj.pos.x < this->unk_0D8.x) {
                    this->fwork[13] *= -1.0f;
                }
            }

            if (this->unk_0D4 == 1) {
                switch (this->iwork[12]) {
                    case TEAM_ID_FALCO:
                        if (this->unk_0D0 == 3) {
                            ActorEvent_SetMessage(gMsg_ID_20210, RCID_FALCO);
                        } else {
                            ActorEvent_SetMessage(gMsg_ID_20060, RCID_FALCO);
                        }
                        break;

                    case TEAM_ID_PEPPY:
                        if (this->unk_0D0 == 3) {
                            ActorEvent_SetMessage(gMsg_ID_20200, RCID_PEPPY);
                        } else {
                            ActorEvent_SetMessage(gMsg_ID_20070, RCID_PEPPY);
                        }
                        break;

                    case TEAM_ID_SLIPPY:
                        if (this->unk_0D0 == 3) {
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
            this->unk_0D0 = 0;
        }
    }
    if ((this->iwork[12] == 0) && (this->iwork[13] == 0) && (this->info.unk_16 != 2) &&
        (gLevelType == LEVELTYPE_SPACE)) {
        sp3C.x = this->vel.x;
        sp3C.y = this->vel.y;
        sp3C.z = this->vel.z;

        if ((func_enmy_8006351C(this->index, &this->obj.pos, &sp3C, 0) != 0) ||
            (this->obj.pos.y < (gGroundLevel + 20.0f))) {
            this->obj.status = OBJ_DYING;
            this->obj.pos.z -= this->vel.z;
            this->unk_0D0 = 1;
            if (this->unk_0B4 == EINFO_13) {
                this->obj.id = OBJ_ACTOR_182;
                func_enmy_800654E4(&this->obj);
            }

            if (this->unk_0B4 == EINFO_61) {
                Meteo_8018CCF8(this);
            }
        }
    }
}

void ActorEvent_80070BA8(ActorEvent* this) {
    if (this->unk_0D0 != 0) {
        this->unk_0D0 = 0;
        if ((this->unk_0B4 != EINFO_17) || ((this->unk_0B4 == EINFO_17) && (this->unk_0D2 == 0))) {
            this->timer_0C6 = 10;
            func_effect_8007C120(this->unk_0D8.x, this->unk_0D8.y, this->unk_0D8.z, this->vel.x, this->vel.y,
                                 this->vel.z, 0.2f, 10);
            this->health -= this->damage;
            AUDIO_PLAY_SFX(0x29033064, this->sfxSource, 4);
            if (this->health <= 0) {
                BonusText_Display(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, this->info.bonus);
                gHitCount += this->info.bonus + 1;
                D_ctx_80177850 = 15;
            }
        } else {
            AUDIO_PLAY_SFX(0x29121007, this->sfxSource, 4);
        }
    }
}

void ActorEvent_80070CEC(ActorEvent* this) {
    if (this->iwork[3] < 200) {
        this->aiIndex = this->iwork[3] * 2;
        this->iwork[0] = 0;
        this->iwork[2] = 0;
        ActorEvent_ProcessScript(this);
    } else {
        this->aiType = this->iwork[3] - 200;
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

    if (this->iwork[2] >= 100) {
        if (fabsf(this->obj.pos.z - gPlayer[0].unk_138) <= ((this->iwork[2] - 100) * 100.0f)) {
            ActorEvent_80070CEC(this);
        }
        return;
    }

    switch (this->iwork[2]) {
        case EVC_NONE:
            break;

        case EVC_1:
            if ((gActors[this->iwork[1]].obj.status != OBJ_ACTIVE) || (gActors[this->iwork[1]].health <= 0) ||
                (this->iwork[10] != gActors[this->iwork[1]].aiType)) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_TEAM_COUNT_3:
            if (var_v1 == 3) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_TEAM_COUNT_2:
            if (var_v1 == 2) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_TEAM_COUNT_1:
            if (var_v1 == 1) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_TEAM_COUNT_0:
            if (var_v1 == 0) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_FALCO_ACTIVE:
            if (gTeamShields[TEAM_ID_FALCO] > 0) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_PEPPY_ACTIVE:
            if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_SLIPPY_ACTIVE:
            if (gTeamShields[TEAM_ID_SLIPPY] > 0) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_CLOSE_LEFT_100:
            if (((this->obj.pos.x - gPlayer[0].pos.x) <= 100.0f) && ((this->obj.pos.x - gPlayer[0].pos.x) >= 0.0f)) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_CLOSE_LEFT_400:
            if (((this->obj.pos.x - gPlayer[0].pos.x) <= 400.0f) && ((this->obj.pos.x - gPlayer[0].pos.x) >= 0.0f)) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_CLOSE_LEFT_700:
            if (((this->obj.pos.x - gPlayer[0].pos.x) <= 700.0f) && ((this->obj.pos.x - gPlayer[0].pos.x) >= 0.0f)) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_CLOSE_LEFT_200:
            if (((this->obj.pos.x - gPlayer[0].pos.x) <= 200.0f) && ((this->obj.pos.x - gPlayer[0].pos.x) >= 0.0f)) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_CLOSE_RIGHT_100:
            if (((this->obj.pos.x - gPlayer[0].pos.x) >= -100.0f) && ((this->obj.pos.x - gPlayer[0].pos.x) <= 0.0f)) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_CLOSE_RIGHT_400:
            if (((this->obj.pos.x - gPlayer[0].pos.x) >= -400.0f) && ((this->obj.pos.x - gPlayer[0].pos.x) <= 0.0f)) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_CLOSE_RIGHT_700:
            if (((this->obj.pos.x - gPlayer[0].pos.x) >= -700.0f) && ((this->obj.pos.x - gPlayer[0].pos.x) <= 0.0f)) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_CLOSE_RIGHT_200:
            if (((this->obj.pos.x - gPlayer[0].pos.x) >= -200.0f) && ((this->obj.pos.x - gPlayer[0].pos.x) <= 0.0f)) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_CLOSE_ABOVE_100:
            if (((this->obj.pos.y - gPlayer[0].pos.y) <= 100.0f) && ((this->obj.pos.y - gPlayer[0].pos.y) >= 0.0f)) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_CLOSE_ABOVE_400:
            if (((this->obj.pos.y - gPlayer[0].pos.y) <= 400.0f) && ((this->obj.pos.y - gPlayer[0].pos.y) >= 0.0f)) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_CLOSE_ABOVE_700:
            if (((this->obj.pos.y - gPlayer[0].pos.y) <= 700.0f) && ((this->obj.pos.y - gPlayer[0].pos.y) >= 0.0f)) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_CLOSE_ABOVE_200:
            if (((this->obj.pos.y - gPlayer[0].pos.y) <= 200.0f) && ((this->obj.pos.y - gPlayer[0].pos.y) >= 0.0f)) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_CLOSE_BELOW_100:
            if (((this->obj.pos.y - gPlayer[0].pos.y) >= -100.0f) && ((this->obj.pos.y - gPlayer[0].pos.y) <= 0.0f)) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_CLOSE_BELOW_400:
            if (((this->obj.pos.y - gPlayer[0].pos.y) >= -400.0f) && ((this->obj.pos.y - gPlayer[0].pos.y) <= 0.0f)) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_CLOSE_BELOW_700:
            if (((this->obj.pos.y - gPlayer[0].pos.y) >= -700.0f) && ((this->obj.pos.y - gPlayer[0].pos.y) <= 0.0f)) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_CLOSE_BELOW_200:
            if (((this->obj.pos.y - gPlayer[0].pos.y) >= -200.0f) && ((this->obj.pos.y - gPlayer[0].pos.y) <= 0.0f)) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_HEALTH_100p:
            if (gPlayer[0].shields >= Play_GetMaxShields()) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_HEALTH_75p:
            if (gPlayer[0].shields >= (Play_GetMaxShields() * 3 / 4)) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_HEALTH_50p:
            if (gPlayer[0].shields >= (Play_GetMaxShields() / 2)) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_HEALTH_25p:
            if (gPlayer[0].shields >= (Play_GetMaxShields() / 4)) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_HEALTH_0p:
            if (gPlayer[0].shields == 0) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_UNK270_5PLUS:
            if (gPlayer[0].unk_270 >= 5) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_UNK270_NONZERO:
            if (gPlayer[0].unk_270 != 0) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_UNK270_ZERO:
            if (gPlayer[0].unk_270 == 0) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_UNK250_GREATER_168:
            if (gPlayer[0].unk_250 >= 16.8f) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_UNK250_LESS_84:
            if (gPlayer[0].unk_250 <= 8.4f) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_SINGLE_LASER:
            if (gPlayer[0].wings.unk_14 > -8.0f) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_TWIN_LASER:
            if ((gPlayer[0].wings.unk_14 < -8.0f) && (gLaserStrength[0] == LASERS_TWIN)) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_HYPER_LASER:
            if ((gPlayer[0].wings.unk_14 < -8.0f) && (gLaserStrength[0] == LASERS_HYPER)) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_UNK3_LASER:
            if ((gPlayer[0].wings.unk_14 < -8.0f) && (gLaserStrength[0] == LASERS_UNK_3)) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_SHOT_CLOSE_150:
            for (i = 0; i < ARRAY_COUNT(gPlayerShots); i++) {
                if ((gPlayerShots[i].obj.status == 1) &&
                    (fabsf(this->obj.pos.x - gPlayerShots[i].obj.pos.x) < 150.0f) &&
                    (fabsf(this->obj.pos.y - gPlayerShots[i].obj.pos.y) < 150.0f) &&
                    (fabsf(this->obj.pos.z - gPlayerShots[i].obj.pos.z) < 150.0f)) {
                    ActorEvent_80070CEC(this);
                    break;
                }
            }
            break;

        case EVC_SHOT_CLOSE_300:
            for (i = 0; i < ARRAY_COUNT(gPlayerShots); i++) {
                if ((gPlayerShots[i].obj.status == 1) &&
                    (fabsf(this->obj.pos.x - gPlayerShots[i].obj.pos.x) < 300.0f) &&
                    (fabsf(this->obj.pos.y - gPlayerShots[i].obj.pos.y) < 300.0f) &&
                    (fabsf(this->obj.pos.z - gPlayerShots[i].obj.pos.z) < 300.0f)) {
                    ActorEvent_80070CEC(this);
                    break;
                }
            }
            break;

        case EVC_41:
            if ((gActors[this->iwork[9]].obj.status != OBJ_ACTIVE) ||
                ((gActors[this->iwork[9]].scale < 0.0f) && (this->health <= 0))) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_42:
            for (i = 0; i < ARRAY_COUNT(gActors); i++) {
                if ((gActors[i].obj.status == OBJ_ACTIVE) && (gActors[i].obj.id == OBJ_ACTOR_EVENT) &&
                    (gActors[i].iwork[13] != 0) && (i != this->index) && (this->index == gActors[i].iwork[9])) {
                    return;
                }
            }
            ActorEvent_80070CEC(this);
            break;

        case EVC_43:
            for (i = 0; i < ARRAY_COUNT(gActors); i++) {
                if ((gActors[i].obj.status == OBJ_ACTIVE) && (gActors[i].obj.id == OBJ_ACTOR_EVENT) &&
                    (gActors[i].iwork[13] != 0) && (i != this->index) && (this->index == gActors[i].iwork[9])) {
                    ActorEvent_80070CEC(this);
                    break;
                }
            }
            break;

        case EVC_TOOK_DAMAGE:
            if (this->unk_0D0 != 0) {
                ActorEvent_80070CEC(this);
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
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_46:
            for (i = 0, otherActor = gActors; i < ARRAY_COUNT(gActors); i++, otherActor++) {
                if (((otherActor->obj.status == OBJ_DYING) || (otherActor->obj.status == OBJ_FREE)) &&
                    (otherActor->iwork[15] == this->iwork[15]) && (otherActor->iwork[16] != 0)) {
                    ActorEvent_80070CEC(this);
                }
            }
            break;

        case EVC_PRESS_CRIGHT:
            if (gControllerPress[gMainController].button & R_CBUTTONS) {
                func_8001AF40(0);
                gCallVoiceParam = 0;
                gCallTimer = 0;
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_WING_BROKEN:
            if ((gPlayer[0].wings.rightState <= WINGSTATE_BROKEN) || (gPlayer[0].wings.leftState <= WINGSTATE_BROKEN)) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_ME_CLEAR:
            if (D_play_800D3180[LEVEL_METEO] != 0) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_FO_CLEAR:
            if (D_play_800D3180[LEVEL_FORTUNA] != 0) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_SX_CLEAR:
            if (D_play_800D3180[LEVEL_SECTOR_X] != 0) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_TI_CLEAR:
            if (D_play_800D3180[LEVEL_TITANIA] != 0) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_BO_CLEAR:
            if (D_play_800D3180[LEVEL_BOLSE] != 0) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_SY_CLEAR:
            if (D_play_800D3180[LEVEL_SECTOR_Y] != 0) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_KA_CLEAR:
            if (D_play_800D3180[LEVEL_KATINA] != 0) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_SO_CLEAR:
            if (D_play_800D3180[LEVEL_SOLAR] != 0) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_MA_CLEAR:
            if (D_play_800D3180[LEVEL_MACBETH] != 0) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_AQ_CLEAR:
            if (D_play_800D3180[LEVEL_AQUAS] != 0) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_ZO_CLEAR:
            if (D_play_800D3180[LEVEL_ZONESS] != 0) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_SZ_CLEAR:
            if (D_play_800D3180[LEVEL_SECTOR_Z] != 0) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_A6_CLEAR:
            if (D_play_800D3180[LEVEL_AREA_6] != 0) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_62:
            if (D_enmy_Timer_80161670[this->iwork[12]] == 0) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_63:
            if (D_enmy_Timer_80161670[this->iwork[12]] != 0) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_MISSED_SEARCHLIGHT:
            if (gMissedZoSearchlight) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_30_HITS:
            if (gHitCount >= 30) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_80_HITS:
            if (gHitCount >= 80) {
                ActorEvent_80070CEC(this);
            }
            break;

        case EVC_EXPERT_MODE:
            if (gExpertMode) {
                ActorEvent_80070CEC(this);
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

    Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, 0);
    Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, 1);
    Matrix_RotateZ(gCalcMatrix, this->obj.rot.z * M_DTOR, 1);

    if (this->unk_0B4 == EINFO_30) {
        rInd = RAND_FLOAT(ARRAY_COUNT(D_800D1074) - 1.1f); // off by 1 error?
        Matrix_MultVec3fNoTranslate(gCalcMatrix, &D_800D1074[rInd], &sp38);
    }

    if (this->unk_0B4 == EINFO_17) {
        rInd = RAND_FLOAT(ARRAY_COUNT(D_800D0DD4) - 0.1f);
        Matrix_MultVec3fNoTranslate(gCalcMatrix, &D_800D0DD4[rInd], &sp38);
    }

    if (this->unk_0B4 == EINFO_31) {
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
        AUDIO_PLAY_SFX(0x2903B009, this->sfxSource, 4);
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
            if (this->unk_0D0 != 0) {
                if (this->unk_0D0 == 2) {
                    this->damage = 3;
                }

                if ((this->unk_0D4 >= 101) && (gActors[this->unk_0D4 - 101].unk_0B4 == 85)) {
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
                    this->info.hitbox = (f32*) LOAD_ASSET(D_SX_6032408);
                    AUDIO_PLAY_SFX(0x1900000D, this->sfxSource, 0);
                } else {
                    AUDIO_PLAY_SFX(0x2903300E, this->sfxSource, 0);
                }
                this->unk_0D0 = 0;
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

void ActorEvent_800722EC(Effect* effect, f32 xPos, f32 yPos, f32 zPos, f32 yRot) {
    Vec3f sp2C;
    Vec3f sp20;

    Effect_Initialize(effect);
    Matrix_RotateY(gCalcMatrix, M_DTOR * yRot, 0);
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

void ActorEvent_8007240C(f32 xPos, f32 yPos, f32 zPos, f32 yRot) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            ActorEvent_800722EC(&gEffects[i], xPos, yPos, zPos, yRot);
            break;
        }
    }
}

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
        var_fv1 = Math_RadToDeg(Math_Atan2F(gPlayer[0].pos.x - this->obj.pos.x, gPlayer[0].unk_138 - this->obj.pos.z));
    } else if (this->iwork[6] != 0) {
        var_fv1 = this->unk_0F4.y;
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

    if ((gPlayer[0].state_1C8 == PLAYERSTATE_1C8_7) || (D_ctx_8017828C != 0)) {
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
    } else {
        if (((this->unk_0B4 == EINFO_17) || (this->unk_0B4 == EINFO_30) || (this->unk_0B4 == EINFO_31)) &&
            (this->health <= 0)) {
            ActorEvent_80071DC0(this);
            return;
        }
        if (this->unk_0B4 == EINFO_300) {
            gPlayer[0].unk_1A4 = this->index;
            this->timer_0C2 = 100;
        } else if (this->unk_0B4 >= EINFO_200) {
            this->unk_04E++;

            if (this->unk_04E >= 100) {
                this->unk_04E = 0;
            }

            D_ctx_80176558[this->unk_046][this->unk_04E] = this->obj.pos.x;
            D_ctx_80176878[this->unk_046][this->unk_04E] = this->obj.pos.y;
            D_ctx_80176B98[this->unk_046][this->unk_04E] = this->obj.pos.z;
            D_ctx_80176EB8[this->unk_046][this->unk_04E] = this->obj.rot.x;
            D_ctx_801771D8[this->unk_046][this->unk_04E] = this->obj.rot.y;
            D_ctx_80177500[this->unk_046][this->unk_04E] = this->obj.rot.z;

            if (this->unk_0D0 != 0) {
                this->unk_0D0 = 0;
                this->timer_0C6 = 20;
                this->health -= this->damage;

                AUDIO_PLAY_SFX(0x29034041, this->sfxSource, 4);

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

        if ((this->unk_0B4 == EINFO_27) && (this->timer_0C2 != 0)) {
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

            case EVSTATE_6:
            case EVSTATE_7:
            case EVSTATE_14:
            case EVSTATE_15:
                spF0 = this->obj.pos.x;
                spEC = this->obj.pos.y;
                spE8 = this->obj.pos.z;

                if ((this->unk_0B4 == EINFO_33) || (this->unk_0B4 == EINFO_68)) {
                    Matrix_RotateZ(gCalcMatrix, -(this->vwork[29].z + this->unk_0F4.z) * M_DTOR, 0);
                    Matrix_RotateX(gCalcMatrix, -this->vwork[29].x * M_DTOR, 1);
                    Matrix_RotateY(gCalcMatrix, -this->vwork[29].y * M_DTOR, 1);

                    if ((this->state == EVSTATE_14) || (this->state == EVSTATE_15)) {
                        spB8.x = gPlayer[0].camEye.x - spF0;
                        spB8.y = gPlayer[0].camEye.y - (spEC + 25.0f);
                        spB8.z = (gPlayer[0].camEye.z * 15.0f) - spE8;
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
                        Matrix_RotateY(gCalcMatrix, this->vwork[29].y * M_DTOR, 0);
                        Matrix_RotateX(gCalcMatrix, this->vwork[29].x * M_DTOR, 1);
                        Matrix_RotateZ(gCalcMatrix, (this->vwork[29].z + this->unk_0F4.z) * M_DTOR, 1);

                        spB8.x = 0.0f;
                        spB8.y = 25.0f;
                        spB8.z = 0.0f;

                        Matrix_MultVec3fNoTranslate(gCalcMatrix, &spB8, &spA0);
                        Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, 1);
                        Matrix_RotateX(gCalcMatrix, this->fwork[15] * M_DTOR, 1);

                        spB8.x = 0.0f;
                        spB8.y = 0.0f;
                        spB8.z = gEnemyShotSpeed;

                        Matrix_MultVec3fNoTranslate(gCalcMatrix, &spB8, &spAC);

                        if (this->unk_0B4 == EINFO_68) {
                            var_fv0 = 80.0f;
                        } else {
                            var_fv0 = 0.0f;
                        }

                        func_effect_8007F04C(OBJ_EFFECT_353, this->obj.pos.x + spAC.x + spA0.x,
                                             this->obj.pos.y + spAC.y + spA0.y + var_fv0,
                                             this->obj.pos.z + spAC.z + spA0.z, this->fwork[15], this->obj.rot.y,
                                             this->obj.rot.z, this->vwork[29].x, this->vwork[29].y,
                                             this->vwork[29].z + this->unk_0F4.z, spAC.x, spAC.y, spAC.z, 1.0f);
                        this->fwork[16] = -15.0f;
                    }
                } else {
                    if ((this->state == EVSTATE_14) || (this->state == EVSTATE_15)) {
                        spCC = gPlayer[0].camEye.x;
                        spC8 = gPlayer[0].camEye.y;
                        spC4 = gPlayer[0].camEye.z;
                    } else {
                        spCC = gPlayer[0].pos.x;
                        spC8 = gPlayer[0].pos.y;
                        spC4 = gPlayer[0].pos.z;
                    }

                    Math_SmoothStepToAngle(&this->vwork[29].z, 0.0f, 0.1f, 5.0f, 0.0001f);
                    Math_SmoothStepToAngle(&this->unk_0F4.z, 0.0f, 0.1f, 5.0f, 0.0001f);

                    spE0 = Math_RadToDeg(Math_Atan2F(spCC - spF0, spC4 - spE8));

                    if ((this->state == EVSTATE_7) || (this->state == EVSTATE_15)) {
                        spE0 += 180.0f;
                        if (spE0 > 360.0f) {
                            spE0 -= 360.0f;
                        }
                    }

                    spE4 = Math_RadToDeg(-Math_Atan2F(spC8 - spEC, sqrtf(SQ(spCC - spF0) + SQ(spC4 - spE8))));
                    spEC = Math_SmoothStepToAngle(&this->unk_0F4.y, spE0, 0.2f, this->fwork[24], 0.0001f);

                    Math_SmoothStepToAngle(&this->unk_0F4.x, spE4, 0.2f, this->fwork[24], 0.0001f);

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
            case EVSTATE_8:
            case EVSTATE_9:
                spF0 = this->obj.pos.x;
                spEC = this->obj.pos.y;
                spE8 = this->obj.pos.z;

                spE0 = Math_RadToDeg(Math_Atan2F(gActors[this->iwork[1]].obj.pos.x + spDC - spF0,
                                                 gActors[this->iwork[1]].obj.pos.z + spD4 - spE8));
                if (this->state == EVSTATE_7) {
                    spE0 += 180.0f;
                    if (spE0 > 360.0f) {
                        spE0 -= 360.0f;
                    }
                }

                spE4 = Math_RadToDeg(-Math_Atan2F(gActors[this->iwork[1]].obj.pos.y + spD8 - spEC,
                                                  sqrtf(SQ(gActors[this->iwork[1]].obj.pos.x + spDC - spF0) +
                                                        SQ(gActors[this->iwork[1]].obj.pos.z + spD4 - spE8))));
                spEC = Math_SmoothStepToAngle(&this->unk_0F4.y, spE0, 0.2f, this->fwork[24], 0.0001f);

                Math_SmoothStepToAngle(&this->unk_0F4.x, spE4, 0.2f, this->fwork[24], 0.0001f);

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
                this->unk_0F4.x += this->fwork[3];
                this->fwork[2] -= this->fwork[3];
                if (this->fwork[2] <= 0.0f) {
                    ActorEvent_ProcessScript(this);
                }
                break;

            case EVSTATE_F4_MINUS_X:
                this->unk_0F4.x -= this->fwork[3];
                this->fwork[2] -= this->fwork[3];
                if (this->fwork[2] <= 0.0f) {
                    ActorEvent_ProcessScript(this);
                }
                break;

            case EVSTATE_F4_PLUS_Y:
                this->unk_0F4.y += this->fwork[3];
                this->fwork[2] -= this->fwork[3];
                if (this->fwork[2] <= 0.0f) {
                    ActorEvent_ProcessScript(this);
                }
                break;

            case EVSTATE_F4_MINUS_Y:
                this->unk_0F4.y -= this->fwork[3];
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
                    this->info.hitbox = (f32*) LOAD_ASSET(D_ME_602F638);
                    ActorEvent_ProcessScript(this);
                }
                break;

            case EVSTATE_ME_AS_CLOSE:
                if (Math_SmoothStepToF(&this->fwork[15], 0.0f, 0.3f, 10.0f, 1.0f) == 0.0f) {
                    ActorEvent_ProcessScript(this);
                }
                break;

            case EVSTATE_TEAM_RETREAT:
                Math_SmoothStepToAngle(&this->unk_0F4.x, 270.0f, 0.1f, 2.0f, 0.0f);
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
                Matrix_RotateY(gCalcMatrix, gActors[this->iwork[9]].obj.rot.y * M_DTOR, 0);
                Matrix_RotateX(gCalcMatrix, gActors[this->iwork[9]].obj.rot.x * M_DTOR, 1);
                Matrix_RotateZ(gCalcMatrix, gActors[this->iwork[9]].obj.rot.z * M_DTOR, 1);
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

        if (this->unk_0F4.x >= 360.0f) {
            this->unk_0F4.x -= 360.0f;
        }
        if (this->unk_0F4.x < 0.0f) {
            this->unk_0F4.x += 360.0f;
        }
        if (this->unk_0F4.y >= 360.0f) {
            this->unk_0F4.y -= 360.0f;
        }
        if (this->unk_0F4.y < 0.0f) {
            this->unk_0F4.y += 360.0f;
        }

        if (this->iwork[6] != 0) {
            if ((gLevelMode == LEVELMODE_UNK_2) && (this->unk_0B4 == EINFO_200)) {
                Math_SmoothStepToAngle(&this->obj.rot.x, this->unk_0F4.x, 0.1f, 10.0f, 0.00001f);
                Math_SmoothStepToAngle(&this->obj.rot.y, this->unk_0F4.y, 0.1f, 10.0f, 0.00001f);
            } else {
                Math_SmoothStepToAngle(&this->obj.rot.x, this->unk_0F4.x, 0.2f, 100.0f, 0.00001f);
                Math_SmoothStepToAngle(&this->obj.rot.y, this->unk_0F4.y, 0.2f, 100.0f, 0.00001f);
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
            if ((this->unk_0B4 == EINFO_13) || (this->unk_0B4 == EINFO_14) || (this->unk_0B4 == EINFO_61) ||
                (this->unk_0B4 == EINFO_62) || (this->unk_0B4 == EINFO_63) || (this->unk_0B4 == EINFO_64) ||
                (this->unk_0B4 == EINFO_65) || (this->unk_0B4 == EINFO_66) || (this->unk_0B4 == EINFO_94) ||
                (this->unk_0B4 == EINFO_95) || (this->unk_0B4 == EINFO_97)) {
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
        Matrix_RotateZ(gCalcMatrix, (this->vwork[29].z + this->unk_0F4.z) * M_DTOR, 0);
        Matrix_RotateY(gCalcMatrix, this->unk_0F4.y * M_DTOR, 1);
        Matrix_RotateX(gCalcMatrix, this->unk_0F4.x * M_DTOR, 1);

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
            if ((gCurrentLevel == LEVEL_SECTOR_Y) && (D_ctx_80177D08 < 0.0f)) {
                this->vel.z -= D_ctx_80177D08;
            }
        }

        if (this->iwork[5] == EV_ZMODE(EMZ_PLAYER)) {
            this->vel.z -= D_ctx_80177D08;
        }

        if (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_8) {
            this->vel.z = 100.0f;
        }

        ActorEvent_ProcessTriggers(this);
        ActorEvent_ProcessActions(this);
        ActorEvent_UpdateTexLines(this);

        if (this->unk_0B4 == EINFO_38) {
            ActorEvent_800720E8(this);
        } else {
            if (this->scale <= -1.999f) {
                ActorEvent_80070BA8(this);
            } else {
                if ((this->unk_0D0 == 1) && (this->scale < 0.5f) && (this->unk_0B4 != EINFO_48) &&
                    (this->unk_0B4 != EINFO_49) && (this->unk_0B4 != EINFO_50)) {
                    this->unk_0D0 = 0;
                    if (gCurrentLevel == LEVEL_METEO) {
                        AUDIO_PLAY_SFX(0x2902107D, this->sfxSource, 4);
                    } else {
                        AUDIO_PLAY_SFX(0x29121007, this->sfxSource, 4);
                    }
                }

                if ((this->unk_0B4 < EINFO_200) && (this->unk_0B4 != EINFO_78) && (this->scale >= 0.5f)) {
                    switch (this->unk_0B4) {
                        case EINFO_71:
                            ActorEvent_8006FE28(this);
                            break;
                        case EINFO_79:
                            ActorEvent_8006FEEC(this);
                            break;
                        default:
                            ActorEvent_800701E0(this);
                            break;
                    }
                }
            }
        }
        switch (this->unk_0B4) {
            case EINFO_92:
            case EINFO_93:
            case EINFO_94:
            case EINFO_95:
            case EINFO_96:
                if (((gGameFrameCount % 8) == 0)) {
                    this->fwork[18] = RAND_FLOAT(255.0f);
                    this->fwork[19] = RAND_FLOAT(255.0f);
                    this->fwork[20] = RAND_FLOAT(255.0f);
                }
                Math_SmoothStepToF(&this->fwork[15], this->fwork[18], 1.0f, 10.0f, 0.0f);
                Math_SmoothStepToF(&this->fwork[16], this->fwork[19], 1.0f, 10.0f, 0.0f);
                Math_SmoothStepToF(&this->fwork[17], this->fwork[20], 1.0f, 10.0f, 0.0f);
                break;

            case EINFO_46:
                if (func_play_800A73E4(&spEC, &spFC, this->obj.pos.x, -100.0f, this->obj.pos.z)) {
                    spF0 = 10.0f;

                    if (Math_SmoothStepToF(&this->obj.pos.y, spEC, 0.5f, 7.0f, 0.0f) >= 0.0f) {
                        spF0 = 350.0f;
                        if (((gGameFrameCount % 4) == 0)) {
                            ActorEvent_8007240C(this->obj.pos.x, spEC, this->obj.pos.z, this->obj.rot.y);
                            AUDIO_PLAY_SFX(0x19800017, this->sfxSource, 4);
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
                this->obj.rot.y = this->unk_0F4.y;
                break;

            case EINFO_31:
                this->obj.rot.z = gGameFrameCount;
                break;

            case EINFO_21:
            case EINFO_22:
                this->obj.rot.z = gGameFrameCount * 3.0f;
                break;

            case EINFO_3:
                this->unk_0C9 = 1;
                this->obj.rot.y -= 10.0f;
                break;

            case EINFO_6:
                this->unk_0B6++;
                if (gCurrentLevel == LEVEL_SOLAR) {
                    if (this->unk_0B6 >= Animation_GetFrameCount(D_SO_600636C)) {
                        this->unk_0B6 = 0;
                    }
                    if (((s32) gGameFrameCount % 3) == 0) {
                        Solar_8019E9F4(this->obj.pos.x, this->obj.pos.y - 20, this->obj.pos.z - 180.0f, 0.0f,
                                       RAND_FLOAT(20.0f) * -1.0f, 0.0f, 4.0f, 2);
                    }
                } else if (this->unk_0B6 >= Animation_GetFrameCount(D_ENMY_PLANET_40057AC)) {
                    this->unk_0B6 = 0;
                }
                break;

            case EINFO_9:
                this->unk_0B6++;
                if (this->unk_0B6 >= Animation_GetFrameCount(D_ENMY_PLANET_40001A4)) {
                    this->unk_0B6 = 0;
                }
                if (this->iwork[6] == 0) {
                    this->obj.rot.y = 0.0f;
                }
                break;

            case EINFO_48:
            case EINFO_49:
            case EINFO_50:
                SectorY_Actor204_Update(this);
                break;

            case EINFO_52:
                ActorEvent_80072474(this);
                break;

            case EINFO_78:
                ActorSupplies_Update(this);
                break;

            case EINFO_79:
                if (this->timer_0C4 == 0) {
                    this->unk_0B6 += 1;
                    if (Animation_GetFrameCount(D_ZO_600E5EC) < this->unk_0B6) {
                        this->unk_0B6 = 0;
                    }
                }
                break;

            case EINFO_80: {
                Effect* effect;
                Vec3f sp90;
                Vec3f sp84;
                Vec3f sp78;
                s32 sp74;

                switch (this->unk_046) {
                    case 1:
                        break;

                    case 0:
                        Matrix_RotateZ(gCalcMatrix, this->unk_0F4.z * M_DTOR, 0);
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
                                    Matrix_RotateY(gCalcMatrix, (RAND_FLOAT(180.0f) + 180.0f) * M_DTOR, 0);
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
                        Matrix_RotateZ(gCalcMatrix, this->unk_0F4.z * M_DTOR, 0);
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

                            if (gGameFrameCount & 4) {
                                effect->vel.y = -effect->vel.y;
                            }
                        }
                    }
                }
            } break;

            case EINFO_81:
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

            case EINFO_83:
                if (this->health <= 0) {
                    if (this->unk_0B6 == 20) {
                        spD4 = this->obj.pos.z;
                        spD8 = this->obj.pos.y;

                        this->obj.pos.y += 80.0f;
                        this->obj.pos.z += 40.0f;
                        Actor_Despawn(this);
                        this->obj.pos.y = spD8;
                        this->obj.pos.z = spD4;
                    }

                    if ((this->unk_0B6 >= 18) && (this->unk_0B6 < 24)) {
                        func_effect_8007BC7C(this->obj.pos.x, this->obj.pos.y + 80.0f, this->obj.pos.z + 60.0f, 20.0f);
                    }

                    if (this->unk_0B6 < 49) {
                        this->unk_0B6++;
                        if (this->unk_0B6 >= 49) {
                            this->unk_0B6 = 49;
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

            case EINFO_88:
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

            case EINFO_103:
            case EINFO_104:
                Andross_80187530(this);
                break;

            case EINFO_106:
                this->unk_0B6++;
                if (this->unk_0B6 >= 6) {
                    this->unk_0B6 = 0;
                }
                break;
        }

        if (gLevelMode == LEVELMODE_ALL_RANGE) {
            D_ctx_80177F20[this->index + 1] = this->obj.pos.x;
            D_ctx_80178028[this->index + 1] = this->obj.pos.z;
            D_ctx_80178130[this->index + 1] = Math_ModF(this->unk_0F4.y, 360.0f) + 180.0f;
            D_ctx_80178238[this->index + 1] = 1;
        }
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
        var_s1 = (s32) (this->health * 0.6375f);
        if (var_s1 > 255) {
            var_s1 = 255;
        }
        if (var_s1 < 0) {
            var_s1 = 1.0f / 70.925f;
        }

        Matrix_Translate(gCalcMatrix, pos->x, pos->y, pos->z, 1);
        Matrix_RotateZ(gCalcMatrix, rot->z * M_DTOR, 1);
        Matrix_RotateY(gCalcMatrix, rot->y * M_DTOR, 1);
        Matrix_RotateX(gCalcMatrix, rot->x * M_DTOR, 1);
        Matrix_Mult(gGfxMatrix, gCalcMatrix, 1);
        Matrix_SetGfxMtx(&gMasterDisp);

        if (*dList != NULL) {
            RCP_SetupDL(&gMasterDisp, 0x22);
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, var_s1, var_s1, 255);
            gSPDisplayList(gMasterDisp++, *dList);
            RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
        }
        return true;
    }
    return false;
}

void ActorEvent_80074E3C(ActorEvent* this) {
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

s32 Obj111_Draw(Object80_111* this) {
    RCP_SetupDL(&gMasterDisp, 0x3C);
    gSPDisplayList(gMasterDisp++, D_SY_601AD70);
    RCP_SetupDL(&gMasterDisp, 0x40);
    return 0;
}

void ActorEvent_Draw(ActorEvent* this) {
    Vec3f sp114[31];
    f32 sp40;
    s16 temp_s0;
    s32 pad;

    if (this->timer_0C6 && (this->unk_0B4 != EINFO_90) && (this->unk_0B4 != EINFO_68) && (this->unk_0B4 != EINFO_72)) {
        if ((this->unk_0B4 != EINFO_13) && (this->unk_0B4 != EINFO_14) && (this->unk_0B4 != EINFO_61) &&
            (this->unk_0B4 != EINFO_62) && (this->unk_0B4 != EINFO_83) && (this->unk_0B4 != EINFO_98) &&
            (this->scale > 0.5f) && (this->timer_0C6 >= 9) && ((this->timer_0C6 & 3) == 0) &&
            (gPlayState != PLAY_PAUSE)) {
            func_effect_8007C120(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, this->vel.x, this->vel.y,
                                 this->vel.z, this->scale * 0.07f, 3);
        }

        if ((this->unk_0B4 != EINFO_21) && (this->unk_0B4 != EINFO_23) && (this->unk_0B4 != EINFO_79) &&
            (this->unk_0B4 != EINFO_83) && (this->unk_0B4 != EINFO_27) && (this->unk_0B4 != EINFO_51) &&
            (this->unk_0B4 != EINFO_13) && (this->unk_0B4 != EINFO_72) && (this->unk_0B4 != EINFO_28) &&
            (this->scale > 0.5f)) {
            sp40 = SIN_DEG(this->timer_0C6 * 400.0f) * this->timer_0C6;
            Matrix_RotateY(gGfxMatrix, M_DTOR * sp40, 1);
            Matrix_RotateX(gGfxMatrix, M_DTOR * sp40, 1);
            Matrix_RotateZ(gGfxMatrix, M_DTOR * sp40, 1);
            Matrix_SetGfxMtx(&gMasterDisp);
        }
    }

    if ((this->obj.status == OBJ_DYING) && (this->timer_0BE != 0)) {
        RCP_SetupDL_27();
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
    }

    if ((this->unk_0B4 == EINFO_29) || (this->unk_0B4 == EINFO_59) || (this->unk_0B4 == EINFO_60)) {
        RCP_SetupDL_60(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
    } else if ((this->unk_0B4 == EINFO_82) || (this->unk_0B4 == EINFO_90) ||
               ((this->unk_0B4 == EINFO_6) && (gCurrentLevel == LEVEL_SOLAR))) {
        if ((this->timer_0C6 % 2) == 0) {
            RCP_SetupDL(&gMasterDisp, 0x39);
        } else {
            RCP_SetupDL(&gMasterDisp, 0x3D);
        }
    }

    switch (this->unk_0B4) {
        case EINFO_92:
        case EINFO_93:
        case EINFO_94:
        case EINFO_95:
        case EINFO_96:
            RCP_SetupDL(&gMasterDisp, 0x22);
            gDPSetTextureFilter(gMasterDisp++, G_TF_POINT);
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, (s32) this->fwork[15], (s32) this->fwork[16],
                            (s32) this->fwork[17], 255);
            gSPDisplayList(gMasterDisp++, D_800D003C[this->unk_0B4].dList);
            gDPSetTextureFilter(gMasterDisp++, G_TF_BILERP);
            break;
        default:
            if ((this->unk_0B4 < EINFO_200) && (D_800D003C[this->unk_0B4].dList != NULL)) {
                gSPDisplayList(gMasterDisp++, D_800D003C[this->unk_0B4].dList);
            }

            switch (this->unk_0B4) {
                case EINFO_56:
                    func_demo_800515C4();
                    break;

                case EINFO_0:
                    this->iwork[11] = 1;
                    func_edisplay_8005ADAC(this);
                    break;

                case EINFO_2:
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

                case EINFO_43:
                    if (gLevelType == LEVELTYPE_PLANET) {
                        gSPDisplayList(gMasterDisp++, D_ENMY_PLANET_40018A0);
                    } else {
                        gSPDisplayList(gMasterDisp++, D_ENMY_SPACE_4007870);
                    }
                    func_edisplay_8005ADAC(this);
                    break;

                case EINFO_5:
                    this->iwork[11] = 1;
                    func_edisplay_8005ADAC(this);
                    break;

                case EINFO_6:
                    if (gCurrentLevel == LEVEL_SOLAR) {
                        gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                        Animation_GetFrameData(D_SO_600636C, this->unk_0B6, sp114);
                        Animation_DrawSkeleton(1, D_SO_6006558, sp114, NULL, NULL, this, &gIdentityMatrix);
                        gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
                    } else {
                        Animation_GetFrameData(D_ENMY_PLANET_40057AC, this->unk_0B6, sp114);
                        Animation_DrawSkeleton(1, D_ENMY_PLANET_40058B8, sp114, NULL, NULL, this, &gIdentityMatrix);
                    }
                    break;

                case EINFO_7:
                    this->iwork[11] = 1;
                    func_edisplay_8005ADAC(this);
                    break;

                case EINFO_9:
                    Matrix_Translate(gGfxMatrix, 0.0f, -30.0f, 0.0f, 1);
                    Animation_GetFrameData(D_ENMY_PLANET_40001A4, this->unk_0B6, sp114);
                    Animation_DrawSkeleton(1, D_ENMY_PLANET_4000270, sp114, NULL, NULL, this, &gIdentityMatrix);
                    break;

                case EINFO_18:
                    if (this->fwork[0] > 0.1f) {
                        this->iwork[11] = 1;
                        Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -30.0f, 1);
                        Matrix_Scale(gGfxMatrix, 2.5f, 2.5f, 2.5f, 1);
                        func_edisplay_8005B1E8(this, 2);
                    }
                    break;

                case EINFO_19:
                    if (this->fwork[0] > 0.1f) {
                        this->iwork[11] = 1;
                        Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -30.0f, 1);
                        Matrix_Scale(gGfxMatrix, 2.5f, 2.5f, 2.5f, 1);
                        func_edisplay_8005B1E8(this, 2);
                    }
                    break;

                case EINFO_20:
                    RCP_SetupDL_60(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
                    gSPDisplayList(gMasterDisp++, D_A6_601A120);
                    break;

                case EINFO_21:
                    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                    gSPDisplayList(gMasterDisp++, D_A6_6018BF0);
                    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
                    Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -30.0f, 1);
                    this->iwork[11] = 1;
                    func_edisplay_8005B1E8(this, 2);
                    break;

                case EINFO_22:
                    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                    gSPDisplayList(gMasterDisp++, D_A6_6019730);
                    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
                    Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -30.0f, 1);
                    this->iwork[11] = 1;
                    func_edisplay_8005B1E8(this, 2);
                    break;

                case EINFO_27:
                    if (this->timer_0C2 != 0) {
                        if (((this->timer_0C2 & 3) == 0) && (gPlayState != PLAY_PAUSE)) {
                            func_effect_8007D0E0(RAND_FLOAT_CENTERED(200.0f) + this->obj.pos.x,
                                                 RAND_FLOAT_CENTERED(200.0f) + this->obj.pos.y,
                                                 RAND_FLOAT_CENTERED(200.0f) + this->obj.pos.z,
                                                 RAND_FLOAT(1.5f) + 2.5f);
                        }
                        RCP_SetupDL(&gMasterDisp, 0x39);
                        gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
                        gSPDisplayList(gMasterDisp++, D_SX_6001950);
                    } else {
                        gSPDisplayList(gMasterDisp++, D_SX_60066F0);
                    }
                    break;

                case EINFO_31:
                    Matrix_RotateX(gGfxMatrix, M_PI / 2, 1);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_A6_600E0C0);
                    break;

                case EINFO_33:
                    Animation_GetFrameData(D_ENMY_SPACE_400A30C, this->unk_0B6, sp114);
                    Matrix_RotateY(gGfxMatrix, M_PI, 1);
                    Matrix_Scale(gGfxMatrix, 1.5f, 1.5f, 1.5f, 1);
                    Animation_DrawSkeleton(1, D_ENMY_SPACE_400A398, sp114, ActorEvent_OverrideLimbDraw1, NULL, this,
                                           &gIdentityMatrix);
                    Math_SmoothStepToF(&this->fwork[16], 0.0f, 0.3f, 2.0f, 0.0001f);
                    break;

                case EINFO_36:
                    Animation_GetFrameData(D_TI1_700CAF4, this->unk_0B6, sp114);
                    sp114[2].z += this->fwork[15];
                    Animation_DrawSkeleton(1, D_TI1_700CB60, sp114, NULL, NULL, this, &gIdentityMatrix);
                    break;

                case EINFO_38:
                    ActorEvent_80074E3C(this);
                    break;

                case EINFO_48:
                case EINFO_49:
                case EINFO_50:
                    SectorY_Actor204_Draw(this);
                    break;

                case EINFO_52:
                    Animation_GetFrameData(D_ZO_601F874, this->unk_0B6, sp114);
                    sp114[2].z -= this->fwork[15];
                    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                    Matrix_Scale(gGfxMatrix, 2.6f, 2.6f, 2.6f, 1);
                    Animation_DrawSkeleton(1, D_ZO_601F920, sp114, NULL, NULL, this, &gIdentityMatrix);
                    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
                    break;

                case EINFO_64:
                    Matrix_Push(&gGfxMatrix);
                    Matrix_RotateX(gGfxMatrix, this->unk_0F4.x * M_DTOR, 1);
                    Matrix_RotateY(gGfxMatrix, this->unk_0F4.y * M_DTOR, 1);
                    Matrix_Push(&gGfxMatrix);
                    Matrix_Translate(gGfxMatrix, 0.0f, this->fwork[15], 0.0f, 1);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_ME_600CAA0);
                    Matrix_Pop(&gGfxMatrix);
                    gSPDisplayList(gMasterDisp++, D_ME_600C130);
                    Matrix_Translate(gGfxMatrix, 0.0f, -this->fwork[15], 0.0f, 1);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_ME_600C740);
                    Matrix_Pop(&gGfxMatrix);
                    break;

                case EINFO_67:
                    gSPDisplayList(gMasterDisp++, D_ME_6008AA0);
                    RCP_SetupDL(&gMasterDisp, 0x35);
                    gSPDisplayList(gMasterDisp++, D_ME_6009E30);
                    break;

                case EINFO_78:
                    ActorSupplies_Draw(this);
                    break;

                case EINFO_79:
                    temp_s0 = this->state;
                    this->state = 2; // actor 235 state
                    Zoness_80190430(this);
                    this->state = temp_s0;
                    break;

                case EINFO_80:
                    Matrix_Scale(gGfxMatrix, 0.6f, 0.6f, 0.6f, 1);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_VE1_9011200);
                    break;

                case EINFO_81:
                    if (this->fwork[15] > 0.001f) {
                        Matrix_Scale(gGfxMatrix, this->fwork[15], this->fwork[15], this->fwork[15], 1);
                        Matrix_SetGfxMtx(&gMasterDisp);
                        Texture_BlendRGBA16(this->fwork[16], 16 * 11, D_VE1_9003890, D_VE1_9003DF0, D_VE1_9003330);
                        gSPDisplayList(gMasterDisp++, D_VE1_9002CF0);
                    }
                    break;

                case EINFO_82:
                    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                    gSPDisplayList(gMasterDisp++, D_MA_600DA10);
                    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
                    break;

                case EINFO_83:
                    Matrix_Scale(gGfxMatrix, 3.0f, 3.0f, 3.0f, 1);
                    Animation_GetFrameData(D_AQ_602201C, this->unk_0B6, sp114);
                    Animation_DrawSkeleton(1, D_AQ_60220E8, sp114, NULL, NULL, this, &gIdentityMatrix);
                    break;

                case EINFO_85:
                    gSPDisplayList(gMasterDisp++, D_D00B880);
                    func_edisplay_8005ADAC(this);
                    break;

                case EINFO_86:
                    gSPDisplayList(gMasterDisp++, D_D009A40);
                    func_edisplay_8005ADAC(this);
                    break;

                case EINFO_88:
                    RCP_SetupDL(&gMasterDisp, 0x16);
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, this->unk_046, this->unk_046, this->unk_046, 255);
                    gSPDisplayList(gMasterDisp++, D_AQ_6008970);
                    break;

                case EINFO_89:
                    RCP_SetupDL(&gMasterDisp, 0x15);
                    gSPDisplayList(gMasterDisp++, D_AQ_6000E10);
                    break;

                case EINFO_103:
                case EINFO_104:
                    Andross_8018769C(this);
                    break;

                case EINFO_105:
                    RCP_SetupDL(&gMasterDisp, 0x23);
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 0, 0, 0, 143);
                    gDPSetEnvColor(gMasterDisp++, 0, 0, 0, 0);
                    gSPDisplayList(gMasterDisp++, D_WZ_7000000);
                    break;

                case EINFO_106:
                    Animation_GetFrameData(D_ENMY_SPACE_4000080, this->unk_0B6, sp114);
                    Animation_DrawSkeleton(1, D_ENMY_SPACE_400014C, sp114, NULL, NULL, this, &gIdentityMatrix);
                    break;

                case 0xFFF:
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

    if (actor->unk_0B4 == EINFO_27) {
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

        if (((actor->timer_0BC % 4U) == 1) && (actor->unk_0B4 != EINFO_13) && (actor->unk_0B4 != EINFO_61)) {
            func_effect_8007D24C(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, 2.2f);
        }

        if ((D_ctx_80178294 != 0) &&
            func_play_800A73E4(&sp58, &sp5C, actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z)) {
            func_effect_8007BFFC(actor->obj.pos.x, sp58 + 20.0f, actor->obj.pos.z, 0.0f, 0.0f, 0.0f,
                                 actor->scale * 3.0f, 5);
            func_effect_8007B228(actor->obj.pos.x, sp58, actor->obj.pos.z, 2.0f);
            actor->timer_0BE = 2;
            func_effect_8007A6F0(&actor->obj.pos, 0x2903A008);
            return;
        }

        if (D_ctx_801784AC == 4) {
            if (Ground_801B6AEC(actor->obj.pos.x, actor->obj.pos.y - 10.0f, actor->obj.pos.z + D_ctx_80177D20) != 0) {
                func_effect_8007D2C8(actor->obj.pos.x, actor->obj.pos.y + 20.0f, actor->obj.pos.z, actor->scale * 6.0f);
                func_effect_8007BFFC(actor->obj.pos.x - actor->vel.x, actor->obj.pos.y + 30.0f,
                                     actor->obj.pos.z - actor->vel.z, 0.0f, 0.0f, 0.0f, actor->scale * 4.0f, 20);
                func_enmy_80062C38(actor->obj.pos.x, actor->obj.pos.z);
                actor->timer_0BE = 2;
                func_effect_8007A6F0(&actor->obj.pos, 0x2903A008);
                return;
            }
        } else {
            sp4C.x = actor->vel.x;
            sp4C.y = actor->vel.y;
            sp4C.z = actor->vel.z;

            sp60 = func_enmy_8006351C(actor->index, &actor->obj.pos, &sp4C, 0);

            if ((sp60 != 0) || (actor->obj.pos.y < (gGroundLevel + 30.0f))) {
                if ((Rand_ZeroOne() < 0.5f) && (actor->timer_04C < 3) && (gLevelType == LEVELTYPE_PLANET) &&
                    (sp60 != 999) && (gGroundType != GROUNDTYPE_WATER) &&
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
                        func_effect_8007A6F0(&actor->obj.pos, 0x2903B009);
                    } else {
                        func_effect_8007A6F0(&actor->obj.pos, 0x2903A008);
                    }

                    if ((actor->obj.id == OBJ_ACTOR_EVENT) && (actor->unk_0B4 == EINFO_2)) {
                        if (actor->fwork[17] < 360.0f) {
                            func_play_800A69F8(1, actor->obj.pos.x + 20.0f, actor->obj.pos.y, actor->obj.pos.z);
                            actor->fwork[17] = 777.0f;
                        }
                        if (actor->fwork[18] < 360.0f) {
                            func_play_800A69F8(0, actor->obj.pos.x - 20.0f, actor->obj.pos.y, actor->obj.pos.z);
                            actor->fwork[18] = 777.0f;
                        }
                    }
                } else {
                    if ((actor->obj.pos.y < (gGroundLevel + 30.0f)) && (gLevelType == LEVELTYPE_PLANET)) {
                        actor->vel.z = 0.0f;
                        if (gGroundType == GROUNDTYPE_WATER) {
                            func_effect_8007D9DC(actor->obj.pos.x, gGroundLevel + 2.0f, actor->obj.pos.z, 3.0f, 20.0f,
                                                 0);
                            func_effect_8007D9DC(actor->obj.pos.x, gGroundLevel + 2.0f, actor->obj.pos.z, 3.0f, 20.0f,
                                                 10);
                            func_effect_8007D9DC(actor->obj.pos.x, gGroundLevel + 2.0f, actor->obj.pos.z, 3.0f, 20.0f,
                                                 20);
                            func_effect_8007ADF4(actor->obj.pos.x, gGroundLevel, actor->obj.pos.z, 0.1f, 3.0f);
                        } else {
                            func_beam_800365E4(actor->obj.pos.x, 3.0f, actor->obj.pos.z, actor->obj.pos.x,
                                               actor->obj.pos.z, 0.0f, 0.0f, 90.0f, 6.5f, 0, 0);
                        }
                        func_effect_8007C120(actor->obj.pos.x, 20.0f, actor->obj.pos.z, 0.0f, 0.0f, 0.0f,
                                             actor->scale * 0.05f, 30);
                        if ((gCurrentLevel == LEVEL_FORTUNA) || (gCurrentLevel == LEVEL_VENOM_2)) {
                            func_effect_8007C688(actor->obj.pos.x, gGroundLevel + 30.0f, actor->obj.pos.z, 3.0f, 60);
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
                                    func_play_800A69F8(4, actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z);
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
                        func_effect_8007A6F0(&actor->obj.pos, 0x2903B009);
                    } else {
                        func_effect_8007A6F0(&actor->obj.pos, 0x2903A008);
                    }
                }
            }
        }
        if ((actor->unk_0D0 != 0) || (actor->timer_0BC == 0) ||
            ((actor->itemDrop != DROP_NONE) && (actor->obj.id != OBJ_ACTOR_ALLRANGE))) {
            if (gLevelMode == LEVELMODE_ALL_RANGE) {
                for (var_s0 = 0; var_s0 < 4; var_s0++) {
                    if (Rand_ZeroOne() < 0.7f) {
                        if (gCurrentLevel == LEVEL_FORTUNA) {
                            func_play_800A69F8(4, actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z);
                        } else {
                            func_effect_800794CC(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, 1.0f);
                        }
                    }
                }

                func_effect_8007BFFC(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, actor->vel.x, actor->vel.y,
                                     actor->vel.z, 5.0f, 15);
                func_effect_8007D0E0(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z - actor->vel.z, 8.0f);
            } else {
                if ((actor->unk_0B4 != EINFO_13) && (actor->unk_0B4 != EINFO_61)) {
                    func_effect_8007D0E0(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z - actor->vel.z,
                                         actor->scale * 5.0f);
                }

                if (actor->unk_0B4 == EINFO_36) {
                    func_effect_8007BFFC(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, actor->vel.x,
                                         actor->vel.y, actor->vel.z, 5.0f, 15);
                }
            }

            actor->timer_0BE = 2;

            if ((actor->obj.id == OBJ_ACTOR_ALLRANGE) && (actor->aiType < AI360_KATT)) {
                func_effect_8007A6F0(&actor->obj.pos, 0x2903B009);
            } else {
                func_effect_8007A6F0(&actor->obj.pos, 0x2903A008);
            }
        }
    }

    if (gLevelMode == LEVELMODE_ALL_RANGE) {
        D_ctx_80177F20[actor->index + 1] = actor->obj.pos.x;
        D_ctx_80178028[actor->index + 1] = actor->obj.pos.z;
        D_ctx_80178130[actor->index + 1] = actor->unk_0F4.y + 180.0f;
    }

    if (actor->obj.id == OBJ_ACTOR_ALLRANGE) {
        func_360_8002EE64(actor);
    }
}

void ActorEvent_Dying(ActorEvent* this) {
    if ((this->unk_0B4 == EINFO_48) || (this->unk_0B4 == EINFO_49) || (this->unk_0B4 == EINFO_50)) {
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
    func_demo_800515C4();
}
