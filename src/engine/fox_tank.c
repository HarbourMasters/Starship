#include "global.h"
#include "assets/ast_landmaster.h"
#include "assets/ast_titania.h"
#include "port/hooks/Events.h"

void func_tank_80047754(Player* player);
void func_tank_80047D38(Player* player, f32);
void func_tank_80047E7C(Player* player, f32, f32);
void func_tank_80047FBC(Player* player);
void func_tank_800481F4(Player* player);
s32 func_tank_80046E40(Player* player, f32* hitboxData, s32* index, f32 xPos, f32 yPos, f32 zPos, f32 xRot, f32 yRot,
                       f32 zRot, f32 arg9, f32 argA, f32 argB);

u8 D_800C9F00 = 0;
u8 D_800C9F04 = 0;
u8 D_800C9F08 = 0;
s32 D_800C9F0C = 0; // unused.
f32 D_800C9F10 = 0.0f;
s32 D_800C9F14 = 0;
s32 D_800C9F18[2] = { 0, 0 }; // unused.
f32 D_800C9F20 = 0.0f;
f32 D_800C9F24 = 0.0f;
f32 D_800C9F28 = 0.0f;
Vec3f D_tank_800C9F2C = { 0.0f, 0.0f, 0.0f };
s32 D_800C9F38 = 0; // unused

void func_tank_80043280(u16* text0, u16* text1, f32 zRot) {
    s32 py;
    s32 px;
    s32 i;
    s32 j;
    f32 dy;
    f32 dx;
    s32 pad;
    Vec3f sp80;
    Vec3f sp74;

    Matrix_Push(&gCalcMatrix);
    text0 = SEGMENTED_TO_VIRTUAL(text0);
    text1 = SEGMENTED_TO_VIRTUAL(text1);
    Matrix_RotateZ(gCalcMatrix, M_DTOR * zRot, MTXF_NEW);
    sp74.z = 0.0f;
    for (i = 0, dy = 0.0f; i < 32; i++, dy += 1.0f) {
        for (j = 0, dx = 0.0f; j < 32; j++, dx += 1.0f) {
            sp74.x = dx - 16.0f;
            sp74.y = dy - 16.0f;
            Matrix_MultVec3f(gCalcMatrix, &sp74, &sp80);
            px = (s32) (sp80.x + 16.0f);
            py = (s32) (sp80.y + 16.0f);
            if ((px >= 0) && (px < 32) && (py >= 0) && (py < 32)) {
                text0[px + 32 * py] = text1[j + 32 * i];
            }
        }
    }
    Matrix_Pop(&gCalcMatrix);
    gSPInvalidateTexCache(gMasterDisp++, text0);
}

void Player_UpdateTankCamOnRails(Player* player) {
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    s32 pad44;
    f32 sp40;
    s32 pad3C;

    sp54 = ((player->pos.x - player->xPath) * player->unk_148) + (player->rot.y * 0.5f);
    sp48 = sp54 + (player->rot.y * -5.0f);
    sp40 = player->cam.eye.z - 1000.0f;
    sp54 += player->xPath;
    sp48 += player->xPath;
    if (player->grounded) {
        sp50 = player->pos.y + 100.0f + (-player->rot.x * 5.0f);
        sp4C = player->pos.y + player->rot.x * 10.0f;
        sp50 += player->unk_17C * 0.5f;
        sp4C += player->unk_17C * -5.0f;

        if (0 || (gCurrentLevel == LEVEL_MACBETH) && (D_MA_801BA1E8 == 102)) {
            sp50 = player->pos.y + 45.0f + (-player->rot.x * 5.0f);
            sp4C = player->pos.y + 200.0f + (player->rot.x * 10.0f);
            sp50 += player->unk_17C * 0.2f;
            sp4C += player->unk_17C * -3.0f;
        }
        if (D_MA_801BA1E8 == 99) {
            sp50 = player->pos.y + 40.0f + (-player->rot.x * 5.0f);
            sp4C = player->pos.y + 200.0f + (player->rot.x * 10.0f);
            sp50 += player->unk_17C * 0.2f;
            sp4C += player->unk_17C * -3.0f;
        } else if (D_MA_801BA1E8 == 98) {
            sp50 = player->pos.y + 100.0f;
            sp4C = player->pos.y + (player->rot.x * 10.0f);
            sp4C += player->unk_17C * -3.0f;
        }
    } else {
        sp50 = player->pos.y + 50.0f;
        sp4C = player->pos.y;

        if (0 || (gCurrentLevel == LEVEL_MACBETH) && (D_MA_801BA1E8 == 102)) {
            sp4C = player->pos.y + 150.0f;
        }
        if (D_MA_801BA1E8 == 99) {
            sp4C = player->pos.y + 150.0f;
        }
    }
    if (player->vel.y < -20.0f) {
        Math_SmoothStepToF(&player->cam.at.y, sp4C - 100.0f, 0.2f, player->unk_014 * 20.0f, 0.00001f);
    }
    Math_SmoothStepToF(&player->cam.eye.x, sp54, 0.1f, player->unk_014 * 20.0f, 0.00001f);
    Math_SmoothStepToF(&player->cam.eye.y, sp50, 0.1f, player->unk_014 * 7.0f, 0.00001f);
    Math_SmoothStepToF(&player->cam.at.y, sp4C, 0.1f, player->unk_014 * 7.0f, 0.00001f);
    Math_SmoothStepToF(&player->cam.at.x, sp48, 0.1f, player->unk_014 * 20.0f, 0.00001f);
    Math_SmoothStepToF(&player->cam.eye.z, 200.0f, 0.1f, player->unk_014 * 10.0f, 0.0f);
    Math_SmoothStepToF(&player->cam.at.z, sp40, 1.0f, player->unk_014 * 10.0f, 0.0f);
    Math_SmoothStepToF(&player->camRoll, player->rot.z * -0.4f, 0.1f, 1.0f, 0.01f);
    Math_SmoothStepToF(&player->unk_014, 1.0f, 1.0f, 0.1f, 0.0f);
}

void func_tank_800438E0(Effect* effect, f32 xPos, f32 yPos, f32 zPos, f32 scale) {
    f32 pad[12];

    Effect_Initialize(effect);
    effect->obj.status = OBJ_ACTIVE;
    effect->obj.id = OBJ_EFFECT_357;
    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;
    effect->vel.x = RAND_FLOAT(1.0f) - RAND_FLOAT(2.0f);
    effect->vel.y = RAND_FLOAT(3.0f) - (gPlayer[0].vel.z / 5.0f) + 3.0f;
    effect->vel.z = RAND_FLOAT(3.0f) - (gPlayer[0].vel.z / 5.0f) + 2.0f;
    effect->scale2 = (RAND_FLOAT(0.8f) + 0.3f) * scale;
    effect->timer_50 = RAND_INT(5.0f) + 8;
    effect->obj.rot.x = RAND_FLOAT(360.0f);
    effect->unk_60.x = RAND_FLOAT_CENTERED(30.0f);
    effect->unk_60.y = RAND_FLOAT_CENTERED(30.0f);
    effect->unk_60.z = RAND_FLOAT_CENTERED(30.0f);
    Object_SetInfo(&effect->info, effect->obj.id);
}

void func_tank_80043AA0(f32 xPos, f32 yPos, f32 zPos, f32 scale) {
    s32 i;

    for (i = 50; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            func_tank_800438E0(&gEffects[i], xPos, yPos, zPos, scale);
            break;
        }
    }
}

void func_tank_80043B0C(s32 arg0) {
}

void func_tank_80043B18(Player* player) {
    f32 pad;
    Vec3f sp48;
    Vec3f sp3C;
    f32 sp38;

    Matrix_Translate(gCalcMatrix, 0.0f, player->unk_18C + 30.0f, 0, MTXF_NEW);
    Matrix_RotateY(gCalcMatrix, player->yRot_114 * M_DTOR, MTXF_APPLY);
    Matrix_RotateX(gCalcMatrix, player->rot.x * M_DTOR, MTXF_APPLY);
    Matrix_RotateZ(gCalcMatrix, (player->rot.z + player->rockAngle) * M_DTOR, MTXF_APPLY);
    Matrix_RotateY(gCalcMatrix, (player->rot.y + 180.0f) * M_DTOR, MTXF_APPLY);
    Matrix_RotateZ(gCalcMatrix, -player->zRotBank * M_DTOR, MTXF_APPLY);
    Matrix_Translate(gCalcMatrix, 0.0f, -30.0f, 0, MTXF_APPLY);
    sp48.y = 0.0f;
    sp48.z = -20.0f;
    sp38 = player->yRot_114;
    if (player->rollState != 0) {

        sp48.x = 0.0f;
        sp48.z = RAND_FLOAT_CENTERED(50.0f) + -20.0f;
        if (player->rollRate < 0) {
            sp38 -= 65.0f;
        } else {
            sp38 += 65.0f;
        }
        Matrix_MultVec3f(gCalcMatrix, &sp48, &sp3C);
        if (gCurrentLevel == LEVEL_MACBETH) {
            func_tank_80043AA0(player->pos.x + sp3C.x, player->pos.y + sp3C.y, player->trueZpos + sp3C.z, 0.2f);
        } else {
            if (((gGameFrameCount % 2) == 0)) {
                Titania_Effect368_Spawn(player->pos.x + sp3C.x, player->pos.y + sp3C.y, player->trueZpos + sp3C.z,
                                        player->rot.y + sp38, 1.3f);
            }
            if (((gGameFrameCount % 4) == 0)) {
                Effect_Effect359_Spawn(player->pos.x + sp3C.x, player->pos.y + sp3C.y + 20.0f,
                                       player->trueZpos + sp3C.z, 2.0f, 255, 15, 0);
            }
        }
    } else {
        sp38 += player->zRotBank;
        if (player->zRotBank > -5.0f) {
            sp48.x = 36.0f;
            Matrix_MultVec3f(gCalcMatrix, &sp48, &sp3C);
            if (gCurrentLevel == LEVEL_MACBETH) {
                if ((gGameFrameCount % 2) != 0) {
                    func_tank_80043AA0(player->pos.x + sp3C.x, player->pos.y + sp3C.y, player->trueZpos + sp3C.z, 0.2f);
                }
            } else {
                if (((gGameFrameCount % 2) == 0)) {
                    Titania_Effect368_Spawn(player->pos.x + sp3C.x, player->pos.y + sp3C.y, player->trueZpos + sp3C.z,
                                            player->rot.y + sp38, 1.0f);
                }
                if (((gGameFrameCount % 4) == 0) && (player->baseSpeed >= 5.0f)) {
                    Effect_Effect359_Spawn(player->pos.x + sp3C.x, player->pos.y + sp3C.y + 20.0f,
                                           player->trueZpos + sp3C.z, 2.0f, 255, 15, 0);
                }
            }
        }
        if (player->zRotBank < 5.0f) {
            sp48.x = -36.0f;
            Matrix_MultVec3f(gCalcMatrix, &sp48, &sp3C);
            if (gCurrentLevel == LEVEL_MACBETH) {
                if (((gGameFrameCount % 2) == 0)) {
                    func_tank_80043AA0(player->pos.x + sp3C.x, player->pos.y + sp3C.y, player->trueZpos + sp3C.z, 0.2f);
                }
            } else {
                if (((gGameFrameCount % 2) == 0)) {
                    Titania_Effect368_Spawn(player->pos.x + sp3C.x, player->pos.y + sp3C.y, player->trueZpos + sp3C.z,
                                            player->rot.y + sp38, 1.0f);
                }
                if (((gGameFrameCount % 4) == 0) && (player->baseSpeed >= 5.0f)) {
                    Effect_Effect359_Spawn(player->pos.x + sp3C.x, player->pos.y + sp3C.y + 20.0f,
                                           player->trueZpos + sp3C.z, 2.0f, 255, 15, 0);
                }
            }
        }
    }
}

s32 func_tank_80044120(Hitbox* hitbox, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    Vec3f sp34;
    Vec3f sp28;

    sp34.x = arg1 - arg4;
    sp34.y = arg2 - arg5;
    sp34.z = arg3 - arg6;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp34, &sp28);
    return Play_CheckSingleHitbox(hitbox, arg4, arg5, arg6, sp28.x + arg4, sp28.y + arg5, sp28.z + arg6);
}

void func_tank_800441C8(Player* player, f32* hitboxData, f32 xPos, f32 yPos, f32 zPos, f32 xRot, f32 yRot, f32 zRot) {
    Hitbox* hitbox;
    s32 count;
    s32 i;
    f32 x;
    f32 y;
    f32 z;

    Matrix_RotateY(gCalcMatrix, -yRot * M_DTOR, MTXF_NEW);
    count = *hitboxData++;
    if (count != 0) {
        for (i = 0; i < count; i++, hitboxData += 6) {
            hitbox = (Hitbox*) hitboxData;

            if (player->vel.y <= 0.0f) {
                x = player->pos.x;
                y = player->pos.y - 10.0f;
                z = player->trueZpos;
                if (func_tank_80044120(hitbox, x, y, z, xPos, yPos, zPos)) {
                    player->grounded = true;
                    if (player->vel.y < -20.0f) {
                        player->hitTimer = 20;
                    }
                    player->vel.y = 0.0f;
                    player->pos.y = yPos + 20.0f;
                    Math_SmoothStepToF(&player->rot.x, 0.0f, 0.3f, 5.0f, 0.0f);
                    Math_SmoothStepToF(&player->rot.z, 0.0f, 0.3f, 5.0f, 0.0f);
                }
            } else {
                x = player->pos.x;
                y = player->pos.y + 30.0f;
                z = player->trueZpos;
                if (func_tank_80044120(hitbox, x, y, z, xPos, yPos, zPos)) {
                    player->vel.y = 0.0f;
                    player->pos.y = yPos - 75.0f;
                }
            }
        }
    }
}

void func_tank_800443DC(Player* player) {
    Scenery* scenery;
    s32 i;

    for (i = 0, scenery = gScenery; i < ARRAY_COUNT(gScenery); i++, scenery++) {
        if ((scenery->obj.status == OBJ_ACTIVE) && (scenery->obj.id == OBJ_SCENERY_TI_BRIDGE) &&
            ((player->trueZpos - 2000.0f) < scenery->obj.pos.z)) {
            func_tank_800441C8(player, scenery->info.hitbox, scenery->obj.pos.x, scenery->obj.pos.y, scenery->obj.pos.z,
                               scenery->obj.rot.x, scenery->obj.rot.y, scenery->obj.rot.z);
        }
    }
}

void func_tank_800444BC(Player* player) {
    f32 pad;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;

    sp30 = 5.0f;
    player->grounded = false;
    if (player->gravity < 0.0f) {
        sp30 = 0.0f;
    }
    sp40 = sp3C = 0.0f;
    sp38 = gGroundHeight;
    if (gGroundType == 4) {
        Ground_801B6E20(player->pos.x, player->trueZpos + player->zPath, &sp40, &sp38, &sp3C);
    }
    if (gCurrentLevel == LEVEL_MACBETH) {
        D_MA_801BE250[27] = gGroundHeight;
        D_MA_801BE250[28] = D_MA_801BE250[29] = 0.0f;
        D_800C9F10 = 0.0f;
        func_tank_80047754(player);
        sp38 = D_MA_801BE250[27];
        sp40 = D_MA_801BE250[28];
        sp3C = D_MA_801BE250[29];
    }
    if ((player->pos.y - sp30) < sp38) {
        if (player->vel.y < -10.0f) {
            AUDIO_PLAY_SFX(NA_SE_TANK_BOUND, player->sfxSource, 0);
        }
        player->grounded = true;
        if (player->vel.y < -20.0f) {
            player->hitTimer = 20;
        }
        if (gTiStartLandmaster != 0) {
            gTiStartLandmaster = 0;
            AUDIO_PLAY_BGM(NA_BGM_STAGE_TI);
            Audio_StartPlayerNoise(0);
        }

        player->pos.y = sp38 - 3.0f;
        sp34 = (player->baseSpeed * 0.2f) + 0.2f;
        player->vel.y = -3.0f;

        if ((player->rot_104.x > 0.0f) && (sp40 <= 0.0f)) {
            player->vel.y = player->rot_104.x * 0.5f * player->baseSpeed * 0.035f;
            player->rot.x = player->rot_104.x;
        }
        if (player->gravity < 0.0f) {
            player->vel.y = 2.0f;
            if (player->vel.y) {} // fake?
            player->pos.y += 7.0f;
        }
        player->rot_104.x = RAD_TO_DEG(sp40);
        player->rot_104.z = RAD_TO_DEG(sp3C);
        if (gCurrentLevel == LEVEL_MACBETH) {
            if (player->rot_104.x > 90.0f) {
                player->rot_104.x = -(180 - player->rot_104.x);
            }
            if (player->rot_104.z > 90.0f) {
                player->rot_104.z = -(180 - player->rot_104.z);
            }
        }
        if (player->rot.x < player->rot_104.x) {
            player->rot.x += sp34;
        }
        if (player->rot.x > player->rot_104.x) {
            player->rot.x -= sp34;
        }
        if (player->rot.z < player->rot_104.z) {
            player->rot.z += sp34;
        }
        if (player->rot.z > player->rot_104.z) {
            player->rot.z -= sp34;
        }
    }
    if (gCurrentLevel == LEVEL_TITANIA) {
        func_tank_800443DC(player);
    }
}

void func_tank_80044868(Player* player) {
    f32 pad;
    f32 stickTilt;
    f32 sp2C;

    stickTilt = (gInputPress->stick_y * 0.7f * (CVarGetInteger("gInvertYAxis", 0) == 1 ? -1 : 1)) - 8.0f;
    if (stickTilt < -40.0f) {
        stickTilt = -40.0f;
    }
    if (stickTilt > 0.0f) {
        stickTilt = 0.0f;
    }
    if (player->unk_17C < stickTilt) {
        player->unk_17C += 3.0f;
    }
    if (stickTilt < player->unk_17C) {
        player->unk_17C -= 3.0f;
    }
    if (player->unk_180 < 0.0f) {
        player->unk_180 += 3.0f;
    }
    if (player->unk_180 > 0.0f) {
        player->unk_180 -= 3.0f;
    }
    gPlayerTurnRate = 3.0f;
    gPlayerTurnStickMod = 0.66f;
    stickTilt = gInputPress->stick_x;
    if (stickTilt == 0.0f) {
        Math_SmoothStepToF(&player->rot.y, -stickTilt * gPlayerTurnStickMod, 0.1f, gPlayerTurnRate * 0.5f, 0.1f);
    } else {
        Math_SmoothStepToF(&player->rot.y, -stickTilt * gPlayerTurnStickMod, 0.1f, gPlayerTurnRate, 0.1f);
    }
    player->rot_104.y = player->rot.y;
    sp2C = player->baseSpeed;

    if ((gCurrentLevel == LEVEL_MACBETH) && (sp2C < 3.0f)) {
        sp2C = 3.0f;
    }
    if (player->unk_16C > 0.2f) {
        Math_SmoothStepToF(&player->unk_184, player->baseSpeed * 0.5f, 1.0f, 1.0f, 0.0f);
    }
    if (player->unk_170 > 0.2f) {
        Math_SmoothStepToF(&player->unk_184, -player->baseSpeed * 0.5f, 1.0f, 1.0f, 0.0f);
    }
    if (!(player->unk_170 > 0.2f) && !(player->unk_16C > 0.2f) && player->grounded) {
        Math_SmoothStepToF(&player->unk_184, 0.0f, 1.0f, 0.75f, 0.0f);
    }
    if (player->rollState != 0) {
        if (player->rollRate < 0) {
            player->unk_184 = 15.0f;
        }
        if (player->rollRate > 0) {
            player->unk_184 = -15.0f;
        }
    }
    player->vel.z = -(COS_DEG(player->rot_104.y) * COS_DEG(player->rot_104.x) * sp2C);
    if ((player->vel.x < 20.0f) && (player->rot_104.z < -30.0f)) {
        Math_SmoothStepToF(&player->vel.x, -player->rot_104.z * 0.5f, 0.2f, 3.0f, 0.0f);
        player->unk_184 = 0.0f;
    } else if ((player->vel.x > -20.0f) && (player->rot_104.z > 30.0f)) {
        Math_SmoothStepToF(&player->vel.x, -player->rot_104.z * 0.5f, 0.2f, 3.0f, 0.0f);
        player->unk_184 = 0.0f;
    } else {
        Math_SmoothStepToF(&player->vel.x, player->unk_184 - (SIN_DEG(player->rot_104.y) * sp2C), 0.5f, 5.0f, 0.0f);
    }
    player->vel.z += fabsf((player->unk_184 * 0.4f * player->baseSpeed) / 15.0f);
    if (player->unk_000 == 0) {
        player->vel.z += SIN_DEG(player->rot.x) * player->boostSpeed;
    }
    if (D_800C9F00 != 0) {
        player->vel.z = 2.0f * D_800C9F00;
    }
    player->pos.x += player->vel.x;
    if ((player->xPath + (player->pathWidth - 100.0f)) < player->pos.x) {
        player->flags_228 = PFLAG_228_0;
    }
    if (player->pos.x < (player->xPath - (player->pathWidth - 100.0f))) {
        player->flags_228 = PFLAG_228_1;
    }
    if (player->pathWidth + player->xPath < player->pos.x) {
        player->pos.x = player->pathWidth + player->xPath;
        player->vel.x = 0.0f;
    }
    if (player->pos.x < player->xPath - player->pathWidth) {
        player->pos.x = player->xPath - player->pathWidth;
        player->vel.x = 0.0f;
    }
    player->pos.y += player->vel.y;
    player->vel.y -= player->gravity;

    if (player->vel.y < -50.0f) {
        player->vel.y = -50.0f;
    }
    if (player->vel.y > 20.0f) {
        player->vel.y = 20.0f;
    }
    player->pos.z += player->vel.z;
    if (player->grounded) {
        player->pathHeight = 0.0f;
        player->rockPhase += player->baseSpeed * 5.0f;
        player->rockAngle = SIN_DEG(player->rockPhase) * 0.7f;
        if (D_800C9F04 == 0) {
            if (player->baseSpeed != 0.0f) {
                func_tank_80043B18(player);
            }
            if (player->rollState != 0.0f) {
                func_tank_80043B18(player);
            }
        }
    }
    if (player->baseSpeed > 0.0f) {
        Lib_Texture_Scroll(D_landmaster_3002E80, 32, 32, 0);
        if ((gCurrentLevel == LEVEL_TITANIA) && !gBossActive) {
            func_tank_80043280(D_landmaster_3005EA8, D_TI_6009BB8, gGameFrameCount * -55.0f);
        }
        if ((gCurrentLevel == LEVEL_MACBETH) && (player->state == PLAYERSTATE_LEVEL_COMPLETE)) {
            // Using D_TI_6009BB8 since it's the same texture, D_Tex_800DACB8 might be imported incorrectly.
            func_tank_80043280(D_landmaster_3005EA8, /* D_Tex_800DACB8 */ D_TI_6009BB8, gGameFrameCount * -55.0f);
        }
    }
    if (player->baseSpeed > 10.0f) {
        Lib_Texture_Scroll(D_landmaster_3002E80, 32, 32, 0);
        if ((gCurrentLevel == LEVEL_TITANIA) && !gBossActive) {
            func_tank_80043280(D_landmaster_3005EA8, D_TI_6009BB8, gGameFrameCount * -55.0f);
        }
    }
    Player_DamageEffects(player);
}

void func_tank_80045130(Player* player) {
    Math_SmoothStepToF(&player->unk_170, 0.0f, 1.0f, 0.2f, 0.0f);
    Math_SmoothStepToF(&player->unk_16C, 0.0f, 1.0f, 0.2f, 0.0f);

    if (gInputPress->button & Z_TRIG) {
        player->sfx.bank = 1;
        if ((player->rollInputTimerL != 0) && (player->zRotBank > 0.0f) && (player->boostMeter < 10.0f)) {
            player->rollState = 1;
            player->rollTimer = 15;
            player->baseRollRate = 20;
            player->rollRate = 20;
            player->sfx.roll = 1;
            AUDIO_PLAY_SFX(NA_SE_TANK_SLIDE, player->sfxSource, 0);
        } else {
            player->rollInputTimerL = 10;
        }
    }

    if (gInputPress->button & R_TRIG) {
        player->sfx.bank = 1;
        if ((player->rollInputTimerR != 0) && (player->zRotBank < 0.0f) && (player->boostMeter < 10.0f)) {
            player->rollState = 1;
            player->rollTimer = 15;
            player->baseRollRate = -20;
            player->rollRate = -20;
            player->sfx.roll = 1;
            AUDIO_PLAY_SFX(NA_SE_TANK_SLIDE, player->sfxSource, 0);
        } else {
            player->rollInputTimerR = 10;
        }
    }
    player->unk_18C = fabsf(SIN_DEG(player->zRotBank) * 25.0f);
    player->unk_18C += fabsf(SIN_DEG(player->zRotBarrelRoll) * 20.0f);
}

void func_tank_80045348(Player* player) {
    f32 baseSpeedTarget = 15.0f;
    f32 sp40 = 0;
    f32 sp3C = 0.1f;
    f32 sp38 = 3.5f;
    f32 pad1;
    f32 pad2;
    s16 sp2E = false;

    if (player->unk_19C >= 0) {
        if ((gBoostButton[player->num] & gInputHold->button) && !player->boostCooldown) {
            CALL_CANCELLABLE_EVENT(PlayerActionBoostEvent, player) {
                D_800C9F14++;
                sp2E = true;
                if (D_800C9F24 == 0.0f) {
                    player->unk_190 = player->unk_194 = 4.0f;
                    AUDIO_PLAY_SFX(NA_SE_TANK_DASH, player->sfxSource, 0);
                } else {
                    player->unk_190 = 2.0f;
                }
                baseSpeedTarget = 25.0f;
                sp40 = -200.0f;
                sp3C = 0.2f;
                sp38 = 6.0f;

                D_800C9F24 += 1.0f;
                if (D_ctx_801779A8[player->num] < 25.0f) {
                    D_ctx_801779A8[player->num] = 25.0f;
                }

                Math_SmoothStepToF(&D_ctx_801779A8[player->num], 50.0f, 1.0f, 10.0f, 0.0f);
            }
        } else {
            D_800C9F24 = 0.0f;
        }
        if ((gBrakeButton[player->num] & gInputHold->button) && !player->boostCooldown && !sp2E) {
            CALL_CANCELLABLE_EVENT(PlayerActionBrakeEvent, player) {
                D_800C9F14++;
                baseSpeedTarget = 5.0f;
                sp40 = 100.0f;
                sp3C = 0.2f;
                D_800C9F28 += 1.0f;
                Math_SmoothStepToF(&D_ctx_801779A8[player->num], 25.0f, 1.0f, 5.0f, 0.0f);
            }
        } else {
            D_800C9F28 = 0.0f;
        }
        Math_SmoothStepToF(&player->baseSpeed, baseSpeedTarget, sp3C, sp38, 0.001f);
        Math_SmoothStepToF(&player->camDist, sp40, sp3C, sp38, 0.001f);
    } else if (player->unk_19C == -1) {
        Math_SmoothStepToF(&player->baseSpeed, player->unk_000, 0.1f, 2.0f, 0.01f);
    }
}

void func_tank_80045678(Player* player) {
    static u8 D_800C9F3C = 0;
    f32 temp;
    f32 pad;

    player->gravity = 3.0f;
    if (!(gInputHold->button & Z_TRIG)) {
        Audio_KillSfxBySourceAndId(player->sfxSource, NA_SE_TANK_GO_UP);
        Audio_KillSfxBySourceAndId(player->sfxSource, NA_SE_TANK_SLIDE);
    }
    if ((gInputHold->button & Z_TRIG) && !player->boostCooldown) {
        D_800C9F14++;
        if (D_800C9F20 == 0.0f) {
            AUDIO_PLAY_SFX(NA_SE_TANK_BURNER_HALF, player->sfxSource, 0);
        }
        player->unk_188 = 0.0f;
        player->zRotBank += 4.0f;
        if (player->zRotBank > 50.0f) {
            player->zRotBank = 50.0f;
        }
        Math_SmoothStepToF(&player->unk_170, 1.0f, 1.0f, 0.4f, 0.0f);
        D_800C9F20 += 1.0f;
    } else {
        if (player->zRotBank > 0) {
            player->unk_188 += 1.5f;
            player->zRotBank -= player->unk_188;
            if (player->zRotBank <= 0.0f) {
                player->zRotBank = 0.0f;
                if (player->unk_188 > 3.0f) {
                    player->unk_188 *= -0.4f;
                    player->zRotBank -= player->unk_188;
                }
            }
        }
        D_800C9F20 = 0.0f;
    }
    if (!(gInputHold->button & R_TRIG)) {
        Audio_KillSfxBySourceAndId(player->sfxSource, NA_SE_TANK_GO_UP);
        Audio_KillSfxBySourceAndId(player->sfxSource, NA_SE_TANK_SLIDE);
    }
    if ((gInputHold->button & R_TRIG) && !player->boostCooldown) {
        D_800C9F14++;
        if (player->unk_2C0 == 0.0f) {
            AUDIO_PLAY_SFX(NA_SE_TANK_BURNER_HALF, player->sfxSource, 0);
        }
        player->unk_188 = 0.0f;
        player->zRotBank -= 4.0f;
        if (player->zRotBank < -50.0f) {
            player->zRotBank = -50.0f;
        }
        Math_SmoothStepToF(&player->unk_16C, 1.0f, 1.0f, 0.4f, 0.0f);
        player->unk_2C0 += 1.0f;
    } else {
        if (player->zRotBank < 0.0f) {
            player->unk_188 += 1.5f;
            player->zRotBank += player->unk_188;
            if (player->zRotBank >= 0.0f) {
                player->zRotBank = 0.0f;
                if (player->unk_188 > 3.0f) {
                    player->unk_188 *= -0.4f;
                    player->zRotBank += player->unk_188;
                }
            }
        }
        player->unk_2C0 = 0.0f;
    }
    Math_SmoothStepToF(&player->boostSpeed, 0.0f, 0.1f, 1.0f, 0);
    if ((player->unk_16C > 0.2f) && (player->unk_170 > 0.2f) && (player->radioDamageTimer == 0)) {
        if (D_800C9F3C == 0) {
            D_800C9F3C = 1;
            Audio_KillSfxBySourceAndId(player->sfxSource, NA_SE_TANK_SLIDE);
            Audio_KillSfxBySourceAndId(player->sfxSource, NA_SE_TANK_BURNER_HALF);
            AUDIO_PLAY_SFX(NA_SE_TANK_GO_UP, player->sfxSource, 0);
        }
        player->zRotBank += ((__cosf(gGameFrameCount * M_DTOR * 8.0f) * 10.0f) - player->zRotBank) * 0.1f;

        temp = -gInputPress->stick_y * (CVarGetInteger("gInvertYAxis", 0) == 1 ? -1 : 1);
        Math_SmoothStepToF(&player->rot.x, temp * 0.3f, 0.05f, 5.0f, 0.00001f);
        Math_SmoothStepToF(&player->boostSpeed, 15.0f, 0.5f, 5.0f, 0.0f);
        Math_SmoothStepToF(&player->rot.z, 0.0f, 0.1f, 5.0f, 0.00001f);
        player->gravity = -0.4f;
        player->pathHeight += player->vel.y;

        if (player->pathHeight > 300.0f) {
            player->gravity = 0.0f;
            Math_SmoothStepToF(&player->vel.y, 0.0f, 0.1f, 2.0f, 0);
        }
        if ((gCamCount == 1) && ((gGameFrameCount % 2) == 0)) {
            Effect_Effect359_Spawn(RAND_FLOAT_CENTERED(20.0f) + player->pos.x, player->groundPos.y + 10.0f,
                                   player->trueZpos - 10.0f, RAND_FLOAT(2.0f) + 3.5f, 255, 16, 1);
        }
    } else {
        D_800C9F3C = 0;
        if ((gCamCount == 1) && ((gGameFrameCount % 4) == 0) && (player->rollState == 0)) {
            if ((player->unk_16C > 0.2f) && (player->radioDamageTimer == 0)) {
                Effect_Effect359_Spawn(RAND_FLOAT_CENTERED(10.0f) + (player->pos.x - 57.0f),
                                       player->groundPos.y + 10.0f, player->trueZpos - 10.0f, RAND_FLOAT(1.0f) + 1.5f,
                                       255, 15, 0);
            }
            if ((player->unk_170 > 0.2f) && (player->radioDamageTimer == 0)) {
                Effect_Effect359_Spawn(RAND_FLOAT_CENTERED(10.0f) + (player->pos.x + 57.0f),
                                       player->groundPos.y + 10.0f, player->trueZpos - 10.0f, RAND_FLOAT(1.0f) + 1.5f,
                                       255, 15, 0);
            }
        }
    }
}

void func_tank_80045E7C(Player* player) {
    player->zRotBarrelRoll = Math_ModF(player->zRotBarrelRoll, 360.0f);
    if (player->rollState == 0) {
        if (player->zRotBarrelRoll > 0.0f) {
            player->zRotBarrelRoll -= player->zRotBarrelRoll * 0.1f;
            if (player->zRotBarrelRoll < 0.1f) {
                player->zRotBarrelRoll = 0.0f;
            }
        }
        if (player->zRotBarrelRoll < 0.0f) {
            player->zRotBarrelRoll -= player->zRotBarrelRoll * 0.1f;
            if (player->zRotBarrelRoll > -0.1f) {
                player->zRotBarrelRoll = 0.0f;
            }
        }
    }
    if (player->rollInputTimerL != 0) {
        player->rollInputTimerL--;
    }
    if (player->rollInputTimerR != 0) {
        player->rollInputTimerR--;
    }
    if (player->rollTimer != 0) {
        player->rollTimer--;
    }
    if (player->rollState != 0) {
        player->rollInputTimerR = 0;
        player->rollInputTimerL = 0;
        player->zRotBarrelRoll += player->rollRate;
        if (player->zRotBank > 0.0f) {
            player->zRotBank -= 8.0f;
            if (player->zRotBank < 0.0f) {
                player->zRotBank = 0.0f;
            }
        }
        if (player->zRotBank < 0.0f) {
            player->zRotBank += 8.0f;
            if (player->zRotBank > 0.0f) {
                player->zRotBank = 0.0f;
            }
        }
        if (player->rollTimer == 0) {
            D_ctx_801779A8[player->num] = 25.0f;
            if (player->rollRate > 0) {
                player->rollRate -= 2;
            }
            if (player->rollRate < 0) {
                player->rollRate += 2;
            }
            if (player->rollRate == 0) {
                player->rollState = 0;
                Audio_KillSfxBySourceAndId(player->sfxSource, NA_SE_TANK_SLIDE);
            }
        }
        if ((player->rollTimer >= 5) && (player->hitTimer == 0) && (player->rollState != 9)) {
            if (player->rollRate > 0) {
                player->unk_170 = 1.3f;
            }
            if (player->rollRate < 0) {
                player->unk_16C = 1.3f;
            }
        }
    }
}

void func_tank_800460E0(Player* player, f32* hitboxData, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    s32 i;
    s32 count;

    Matrix_RotateY(gCalcMatrix, -arg6 * M_DTOR, MTXF_NEW);
    count = *hitboxData++;
    if (count != 0) {
        for (i = 0; i < count; i++, hitboxData += 6) {
            Vec3f spf94;
            Vec3f sp88;
            Vec3f sp7C;
            Hitbox* hitbox = (Hitbox*) hitboxData;

            spf94.x = player->pos.x;
            spf94.y = arg3;
            spf94.z = player->trueZpos;

            sp88.x = spf94.x - arg2;
            sp88.y = spf94.y - arg3;
            sp88.z = spf94.z - arg4;
            Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp88, &sp7C);
            if (Play_CheckSingleHitbox(hitbox, arg2, arg3, arg4, sp7C.x + arg2, sp7C.y + arg3, sp7C.z + arg4)) {
                player->groundPos.y = arg3 + 20.0f + 3.0f;
            }
        }
    }
}

void func_tank_80046260(Player* player) {
    Scenery* scenery;
    s32 i;

    for (i = 0, scenery = &gScenery[0]; i < ARRAY_COUNT(gScenery); i++, scenery++) {
        if ((scenery->obj.status == OBJ_ACTIVE) && (scenery->obj.id == OBJ_SCENERY_TI_BRIDGE) &&
            ((player->trueZpos - 2000.0f) < scenery->obj.pos.z) && (scenery->obj.pos.y < player->pos.y)) {
            func_tank_800460E0(player, scenery->info.hitbox, scenery->obj.pos.x, scenery->obj.pos.y, scenery->obj.pos.z,
                               scenery->obj.rot.x, scenery->obj.rot.y, scenery->obj.rot.z);
        }
    }
}

void func_tank_80046358(Player* player) {
    f32 spD4;
    f32 spD0;
    f32 spCC;
    s32 pad[35];
    Vec3f sp34 = { 0.0f, -10.0f, 0.0f };
    s32 pad1;
    s32 pad2;

    player->groundPos.x = player->pos.x;
    player->groundPos.z = player->trueZpos + -20.0f;
    player->groundPos.y = gGroundHeight + 3.0f;
    player->shadowRotX = 0.0f;
    player->shadowRotZ = 0.0f;
    player->groundRotY = 0.0f;
    Ground_801B6E20(player->groundPos.x, player->groundPos.z + player->zPath, &spD4, &spD0, &spCC);
    player->groundPos.y = spD0 + 2.0f;
    player->shadowRotX = spD4;
    player->shadowRotZ = spCC;
}

void func_tank_8004641C(Player* player, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    s32 pad1;
    s32 pad2;
    f32 sp84;
    f32 sp80;
    f32 sp7C;
    Vec3f sp70;
    Vec3f sp64;
    Vec3f sp58;
    Vec3f sp4C;

    Matrix_RotateY(gCalcMatrix, -arg6 * M_DTOR, MTXF_NEW);
    sp70.x = player->vel.x;
    sp70.y = player->vel.y;
    sp70.z = player->vel.z;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp70, &sp4C);
    sp70.x = player->pos.x - arg2;
    sp70.y = player->pos.y - arg3;
    sp70.z = player->trueZpos - arg4;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp70, &sp64);
    sp84 = sp64.x + arg2;
    sp80 = sp64.y + arg3;
    sp7C = sp64.z + arg4;

    if (Play_CheckPolyCollision(arg1, arg2, arg3, arg4, sp84, sp80, sp7C, &sp58, &sp4C)) {
        if (D_MA_801BE250[27] < arg3 + sp58.y) {
            D_MA_801BE250[27] = arg3 + sp58.y;
            if (arg1 == OBJ_SCENERY_MA_WALL_3) {
                player->rollState = 0;
                D_800C9F04 = 1;
            }
        }
        D_MA_801BE250[28] = sp58.x;
        D_MA_801BE250[29] = sp58.z;
    } else if ((arg1 == OBJ_SCENERY_MA_WALL_3) && (D_MA_801BE250[27] == 0.0f) &&
               Play_CheckPolyCollision(arg1, arg2 + 20.0f, arg3, arg4, sp84, sp80, sp7C, &sp58, &sp4C)) {
        player->rollState = 9;
        player->rollTimer = 15;
        if ((arg6 > 90.0f) && (arg6 < 270.0f)) {
            player->rollRate = player->baseRollRate = 20;
        } else {
            player->rollRate = player->baseRollRate = -20;
        }
    }
    if (Play_CheckPolyCollision(arg1, arg2, arg3, arg4, sp84, arg3, sp7C, &sp58, &sp4C) &&
        (D_800C9F10 <= arg3 + sp58.y)) {
        D_800C9F10 = arg3 + sp58.y;
        player->groundPos.x = player->pos.x;
        player->groundPos.y = D_800C9F10 - 2.0f;
        player->shadowRotX = sp58.x;
        player->shadowRotZ = sp58.z;
    }
}

f32 D_800C9F4C[5] = { 0.0f, -1.0f, 1.0f, 0.5f, -0.5f };

void func_tank_80046704(Player* player) {
    s32 pad[7];
    s16 i;
    Scenery* scenery;
    f32 temp1;
    f32 temp2;

    if (D_800C9F00 > 0) {
        D_800C9F00--;
    }
    if (1) {}
    for (i = 0, scenery = gScenery; i < ARRAY_COUNT(gScenery); i++, scenery++) {
        if ((scenery->obj.status == OBJ_ACTIVE) && ((player->trueZpos - 2000.0f) < scenery->obj.pos.z)) {
            if ((scenery->obj.id == OBJ_SCENERY_MA_TERRAIN_BUMP) || (scenery->obj.id == OBJ_SCENERY_MA_FLOOR_1) ||
                (scenery->obj.id == OBJ_SCENERY_MA_FLOOR_2) || (scenery->obj.id == OBJ_SCENERY_MA_FLOOR_3) ||
                (scenery->obj.id == OBJ_SCENERY_MA_FLOOR_4) || (scenery->obj.id == OBJ_SCENERY_MA_WALL_3)) {
                temp1 = scenery->obj.pos.x - player->pos.x;
                temp2 = scenery->obj.pos.z - player->trueZpos;

                if (sqrtf(SQ(temp1) + SQ(temp2)) < 2000.0f) {
                    func_tank_8004641C(player, scenery->obj.id, scenery->obj.pos.x, scenery->obj.pos.y,
                                       scenery->obj.pos.z, scenery->obj.rot.x, scenery->obj.rot.y, scenery->obj.rot.z);
                }
            } else if (scenery->obj.id == OBJ_SCENERY_MA_FLOOR_5) {
                if (((player->pos.x - 820.0f) <= scenery->obj.pos.x) &&
                    (scenery->obj.pos.x <= (player->pos.x + 820.0f)) &&
                    ((player->pos.y - 50.0f) <= scenery->obj.pos.y) &&
                    (scenery->obj.pos.y <= (player->pos.y + 50.0f)) && (player->trueZpos <= scenery->obj.pos.z) &&
                    (scenery->obj.pos.z <= (player->trueZpos + 960.0f))) {
                    D_MA_801BE250[27] = scenery->obj.pos.y;
                    player->groundPos.x = player->pos.x;
                    player->groundPos.y = D_MA_801BE250[27] - 3.0f;
                }
            }
            if ((scenery->obj.id == OBJ_SCENERY_MA_BUILDING_1) || (scenery->obj.id == OBJ_SCENERY_MA_BUILDING_2) ||
                (scenery->obj.id == OBJ_SCENERY_MA_TOWER) || (scenery->obj.id == OBJ_SCENERY_GUILLOTINE_HOUSING) ||
                (scenery->obj.id == OBJ_SCENERY_MA_TRAIN_TRACK_13) || (scenery->obj.id == OBJ_SCENERY_MA_WALL_2) ||
                (scenery->obj.id == OBJ_SCENERY_MA_WALL_3) || (scenery->obj.id == OBJ_SCENERY_MA_WALL_4)) {
                s32 temp_v0;
                s32 sp94;

                temp_v0 = func_tank_80046E40(player, scenery->info.hitbox, &sp94, scenery->obj.pos.x,
                                             scenery->obj.pos.y, scenery->obj.pos.z, scenery->obj.rot.x,
                                             scenery->obj.rot.y, scenery->obj.rot.z, 0.0f, 0.0f, 0.0f);
                switch (temp_v0) {
                    case 0:
                        break;
                    case 1:
                    case 2:
                        Math_SmoothStepToF(&player->baseSpeed, 15.0f, 0.3f, 3.5f, 0.001f);
                        Math_SmoothStepToF(&player->camDist, 0, 0.3f, 3.5f, 0.001f);
                        if (temp_v0 == 1) {
                            player->vel.x = -10.0f;
                        } else {
                            player->vel.x = 10.0f;
                        }
                        player->pos.x = player->basePos.x;
                        player->knockback.x = 2.0f * D_800C9F4C[temp_v0];
                        player->pos.x += (D_800C9F4C[temp_v0] * 5.0f);
                        break;
                    case 3:
                        if ((scenery->obj.id == OBJ_SCENERY_MA_BUILDING_1) ||
                            (scenery->obj.id == OBJ_SCENERY_MA_BUILDING_2) ||
                            (scenery->obj.id == OBJ_SCENERY_GUILLOTINE_HOUSING) ||
                            (scenery->obj.id == OBJ_SCENERY_MA_WALL_2) || (scenery->obj.id == OBJ_SCENERY_MA_WALL_4)) {
                            Player_ApplyDamage(player, temp_v0, 5);
                        }
                        player->baseSpeed = -(D_800C9F00 * 1.5f);
                        player->vel.z = D_800C9F00 * 1.5f;
                        D_800C9F00 = 12;
                        AUDIO_PLAY_SFX(NA_SE_TANK_WALL_HIT, player->sfxSource, 0);
                        break;
                }
                if (scenery->obj.id == OBJ_SCENERY_MA_BUILDING_1) {
                    if (((player->pos.x - 230.0f) <= scenery->obj.pos.x) &&
                        (scenery->obj.pos.x <= (player->pos.x + 230.0f)) &&
                        ((80.0f <= player->pos.y - scenery->obj.pos.y)) &&
                        ((player->pos.y - scenery->obj.pos.y) < 210.0f) &&
                        ((player->trueZpos - 220.0f) <= scenery->obj.pos.z) &&
                        (scenery->obj.pos.z <= (player->trueZpos + 220.0f))) {

                        if (!(((player->pos.x - 210.0f) <= scenery->obj.pos.x) &&
                              (scenery->obj.pos.x <= (player->pos.x + 210.0f))) &&
                            (D_MA_801BE250[27] == 0.f) && (player->vel.y < 0.f)) {
                            player->rollState = 9;
                            player->rollTimer = 15;
                            if ((player->pos.x - 200.0f) <= scenery->obj.pos.x) {
                                player->rollRate = player->baseRollRate = 20;
                            } else {
                                player->rollRate = player->baseRollRate = -20;
                            }
                        } else {
                            D_800C9F04 = 1;
                            D_MA_801BE250[27] = scenery->obj.pos.y + 206.0f;
                            player->rollState = 0;
                        }
                    }
                    if (((player->pos.x - 220.0f) <= scenery->obj.pos.x) &&
                        (scenery->obj.pos.x <= (player->pos.x + 220.0f)) &&
                        ((player->trueZpos - 220.0f) <= scenery->obj.pos.z) &&
                        (scenery->obj.pos.z <= (player->trueZpos + 220.0f)) && (player->pos.y >= 200.0f)) {
                        player->groundPos.y = scenery->obj.pos.y + 204.0f;
                    }
                } else if ((scenery->obj.id == OBJ_SCENERY_MA_TRAIN_TRACK_13) && Macbeth_801A3C20(player->trueZpos)) {
                    if (((player->pos.x - 200.0f) < D_MA_801BE250[21]) &&
                        (D_MA_801BE250[21] < (player->pos.x + 200.0f))) {
                        player->groundPos.y = D_MA_801BE250[22] - 1.0f;
                    }
                }
            }
        }
    }
}

s32 func_tank_80046E40(Player* player, f32* hitboxData, s32* index, f32 xPos, f32 yPos, f32 zPos, f32 xRot, f32 yRot,
                       f32 zRot, f32 arg9, f32 argA, f32 argB) {
    s32 spB4;
    s32 i;
    f32 var_fa0;
    f32 var_fv0;
    f32 var_fv1;
    f32 spA0;
    Vec3f sp94;
    Vec3f sp88;

    spB4 = *hitboxData++;
    if (spB4 != 0) {
        for (i = 0; i < spB4; i++, hitboxData += 6) {
            spA0 = 0;
            if (hitboxData[0] == HITBOX_ROTATED) {
                Matrix_RotateZ(gCalcMatrix, -hitboxData[3] * M_DTOR, MTXF_NEW);
                Matrix_RotateX(gCalcMatrix, -hitboxData[1] * M_DTOR, MTXF_APPLY);
                Matrix_RotateY(gCalcMatrix, -hitboxData[2] * M_DTOR, MTXF_APPLY);
                Matrix_RotateZ(gCalcMatrix, -zRot * M_DTOR, MTXF_APPLY);
                Matrix_RotateX(gCalcMatrix, -xRot * M_DTOR, MTXF_APPLY);
                Matrix_RotateY(gCalcMatrix, -yRot * M_DTOR, MTXF_APPLY);
                hitboxData += 4;
                spA0 = 1.0f;
            } else {
                if (hitboxData[0] == HITBOX_SHADOW) {
                    hitboxData++;
                }
                Matrix_RotateZ(gCalcMatrix, -zRot * M_DTOR, MTXF_NEW);
                Matrix_RotateX(gCalcMatrix, -xRot * M_DTOR, MTXF_APPLY);
                Matrix_RotateY(gCalcMatrix, -yRot * M_DTOR, MTXF_APPLY);
            }
            if ((arg9 != 0) || (argA != 0) || (argB != 0)) {
                Matrix_RotateZ(gCalcMatrix, -argB * M_DTOR, MTXF_APPLY);
                Matrix_RotateX(gCalcMatrix, -arg9 * M_DTOR, MTXF_APPLY);
                Matrix_RotateY(gCalcMatrix, -argA * M_DTOR, MTXF_APPLY);
            }
            if ((yRot == 0.0f) && (zRot == 0.0f) && (xRot == 0.0f) && (spA0 == 0)) {
                var_fv0 = player->hit1.x;
                var_fv1 = player->hit1.y;
                var_fa0 = player->hit1.z;
            } else {
                sp94.x = player->hit1.x - xPos;
                sp94.y = player->hit1.y - yPos;
                sp94.z = player->hit1.z - zPos;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp94, &sp88);
                var_fv0 = sp88.x + xPos;
                var_fv1 = sp88.y + yPos;
                var_fa0 = sp88.z + zPos;
            }
            if (Play_CheckSingleHitbox((Hitbox*) hitboxData, xPos, yPos, zPos, var_fv0, var_fv1, var_fa0)) {
                *index = i + 1;
                return 1;
            }
            if ((yRot == 0.0f) && (zRot == 0.0f) && (xRot == 0.0f) && (spA0 == 0)) {
                var_fv0 = player->hit2.x;
                var_fv1 = player->hit2.y;
                var_fa0 = player->hit2.z;
            } else {
                sp94.x = player->hit2.x - xPos;
                sp94.y = player->hit2.y - yPos;
                sp94.z = player->hit2.z - zPos;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp94, &sp88);
                var_fv0 = sp88.x + xPos;
                var_fv1 = sp88.y + yPos;
                var_fa0 = sp88.z + zPos;
            }
            if (Play_CheckSingleHitbox((Hitbox*) hitboxData, xPos, yPos, zPos, var_fv0, var_fv1, var_fa0)) {
                *index = i + 1;
                return 2;
            }
            if ((yRot == 0.0f) && (zRot == 0.0f) && (xRot == 0.0f) && (spA0 == 0)) {
                var_fv0 = player->hit3.x;
                var_fv1 = player->hit3.y;
                var_fa0 = player->hit3.z;
            } else {
                sp94.x = player->hit3.x - xPos;
                sp94.y = player->hit3.y - yPos;
                sp94.z = player->hit3.z - zPos;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp94, &sp88);
                var_fv0 = sp88.x + xPos;
                var_fv1 = sp88.y + yPos;
                var_fa0 = sp88.z + zPos;
            }
            if (Play_CheckSingleHitbox((Hitbox*) hitboxData, xPos, yPos, zPos, var_fv0, var_fv1, var_fa0)) {
                *index = i + 1;
                if (hitboxData[-1] == HITBOX_SHADOW) {
                    return -1;
                } else {
                    return 3;
                }
            }
            if (hitboxData[-1] == HITBOX_SHADOW) {
                return 0;
            }
            if ((yRot == 0.0f) && (zRot == 0.0f) && (xRot == 0.0f) && (spA0 == 0)) {
                var_fv0 = player->hit4.x;
                var_fv1 = player->hit4.y;
                var_fa0 = player->hit4.z;
            } else {
                sp94.x = player->hit4.x - xPos;
                sp94.y = player->hit4.y - yPos;
                sp94.z = player->hit4.z - zPos;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp94, &sp88);
                var_fv0 = sp88.x + xPos;
                var_fv1 = sp88.y + yPos;
                var_fa0 = sp88.z + zPos;
            }
            if (Play_CheckSingleHitbox((Hitbox*) hitboxData, xPos, yPos, zPos, var_fv0, var_fv1, var_fa0)) {
                *index = i + 1;
                return 4;
            }
        }
    }
    return 0;
}

void Tank_UpdateOnRails(Player* player) {
    s32 pad;

    player->wingPosition = 1;
    func_tank_80045130(player);
    D_800C9F14 = 0;
    func_tank_80045678(player);
    func_tank_80045348(player);
    if (!player->boostCooldown) {
        if (D_800C9F14 != 0) {
            if (D_800C9F14 >= 2) {
                player->boostMeter += 2.0f;
            } else {
                player->boostMeter += 1.0f;
            }
            if (player->boostMeter > 90.0f) {
                player->boostMeter = 90.0f;
                player->boostCooldown = true;
                Audio_KillSfxBySourceAndId(player->sfxSource, NA_SE_TANK_BURNER_HALF);
                Audio_KillSfxBySourceAndId(player->sfxSource, NA_SE_TANK_GO_UP);
            }
        } else {
            if (player->boostMeter > 0.0f) {
                player->boostCooldown = true;
                Audio_KillSfxBySourceAndId(player->sfxSource, NA_SE_TANK_BURNER_HALF);
                Audio_KillSfxBySourceAndId(player->sfxSource, NA_SE_TANK_GO_UP);
            }
        }
    } else {
        player->boostMeter -= 1.0f;
        if (player->boostMeter <= 0.0f) {
            player->boostCooldown = false;
            player->boostMeter = 0.0f;
        }
    }
    Play_dummy_800B41E0(player);
    func_tank_80045E7C(player);
    func_tank_80044868(player);
    D_800C9F04 = 0;
    Player_UpdatePath(player);
    Player_Shoot(player);
    if (gCurrentLevel != LEVEL_MACBETH) {
        Player_CollisionCheck(player);
    } else {
        player->groundPos.x = player->pos.x;
        player->groundPos.z = player->trueZpos + -10.0f;
        player->groundPos.y = gGroundHeight - 4.0f;
        player->shadowRotX = 0.0f;
        player->shadowRotZ = 0.0f;
        player->groundRotY = 0.0f;
        func_tank_800481F4(player);
    }
    if (gCurrentLevel == LEVEL_TITANIA) {
        func_tank_80046358(player);
        func_tank_80046260(player);
    }
    Player_LowHealthAlarm(player);
    if ((player->shields <= 0) && (player->radioDamageTimer != 0)) {
        Player_Down(player);
    }
}

// lots of fake stuff here
void func_tank_80047754(Player* player) {
    u8 sp2F = false;

    if ((D_MA_801BE2F0[5] == 0) && (Macbeth_801A3300(player, player->trueZpos, player->rot.y) == 0)) {
        if (((player->pos.x - 110.0f) < D_MA_801BE250[9]) && (D_MA_801BE250[9] < (player->pos.x + 110.0f)) &&
            ((player->pos.y - 60.0f) < (D_MA_801BE250[2] + 30.0f)) &&
            ((D_MA_801BE250[2] + 30.0f) < (player->pos.y + 60.f))) {
            func_tank_80047D38(player, D_MA_801BE250[2] + 29.0f);
            player->rot.x = D_MA_801BE250[3];
            func_tank_80047FBC(player);
            sp2F = true;
        } else {
            if (((player->pos.x - 150.0f) < D_MA_801BE250[9]) && (D_MA_801BE250[9] < (player->pos.x + 150.0f)) &&
                ((player->pos.y - 60.0f) < (D_MA_801BE250[2] + 30.0f)) &&
                ((D_MA_801BE250[2] + 30.0f) < (player->pos.y + 60.0f))) {
                func_tank_80047E7C(player, D_MA_801BE250[9], D_MA_801BE250[2] + 30.0f);
            }
            if (1) {}
        }
    }
    if (Macbeth_801A3C20(player->trueZpos)) {
        player->rot.x = D_MA_801BE250[23];
        if (((player->pos.x - 200.0f) < D_MA_801BE250[21]) && (D_MA_801BE250[21] < (player->pos.x + 200.0f))) {
            if (((player->pos.y - 60.0f) < D_MA_801BE250[22]) && (D_MA_801BE250[22] < (player->pos.y + 60.0f))) {
                func_tank_80047D38(player, D_MA_801BE250[22]);
            } else {
                if ((100.0f < (D_MA_801BE250[22] - player->pos.y)) && ((D_MA_801BE250[22] - player->pos.y) < 130.0f)) {
                    player->pathHeight = 999.0f;
                    player->pos.y = player->basePos.y - 1.0f;
                }
                goto label_29;
            }
            if (!(((player->pos.x - 65.0f) < D_MA_801BE250[21]) && (D_MA_801BE250[21] < (player->pos.x + 65.0f)))) {
                if (!(((player->pos.x - 100.0f) < D_MA_801BE250[21]) &&
                      (D_MA_801BE250[21] < (player->pos.x + 100.0f)))) {
                    player->grounded = 9;
                    Math_SmoothStepToF(&player->pos.y, D_MA_801BE250[22] + 100.0f, 0.5f, 20.0f, 0);
                    player->vel.y = 2.0f;
                    Math_SmoothStepToF(&player->rot.y, 0.0f, 0.5f, 20.0f, 0);
                    Math_SmoothStepToF(&player->pos.x, D_MA_801BE250[21], 0.02f, 30.0f, 0);
                    Math_SmoothStepToF(&player->zRotBank, -30.0f, 1.0f, 10.0f, 0);
                    D_MA_801BE250[13] += 0; // fake?
                }
                player->unk_188 = 0;
                if (player->pos.x < D_MA_801BE250[21]) {
                    player->vel.x = 0.0f;
                    player->pos.x += 8.0f;
                } else {
                    player->vel.x = 0.0f;
                    player->pos.x -= 8.0f;
                }
            }
        }
    }
label_29:

    if (((D_MA_801BE2F0[5] == 1) || (player->trueZpos < -116467.875f)) &&
        (Macbeth_801A3790(player, player->trueZpos, player->rot.y) == 0)) {
        if (((player->pos.x - 110.0f) < D_MA_801BE250[19]) && (D_MA_801BE250[19] < (player->pos.x + 110.0f)) &&
            ((player->pos.y - 60.0f) < (D_MA_801BE250[12] + 30.0f)) &&
            ((D_MA_801BE250[12] + 30.0f) < (player->pos.y + 60.0f))) {
            sp2F = true;
            func_tank_80047D38(player, D_MA_801BE250[12] + 29.0f);
            player->rot.x = D_MA_801BE250[13]; // not fake, but weird
            player->rot.x = D_MA_801BE250[13];
            func_tank_80047FBC(player);
        } else if (((player->pos.x - 150.0f) < D_MA_801BE250[19]) && (D_MA_801BE250[19] < (player->pos.x + 150.0f)) &&
                   ((player->pos.y - 60.0f) < (D_MA_801BE250[12] + 30.0f)) &&
                   ((D_MA_801BE250[12] + 30.0f) < (player->pos.y + 60.0f))) {
            func_tank_80047E7C(player, D_MA_801BE250[19], D_MA_801BE250[12] + 30.0f);
        }
    }
    if (!sp2F) {
        if (!D_MA_801BE250) {}

        func_tank_80046704(player);
    }
}

void func_tank_80047D38(Player* player, f32 arg1) {
    if ((player->unk_16C > 0.2f) && (player->unk_170 > 0.2f) && (player->radioDamageTimer == 0) &&
        (player->vel.y >= 0.0f)) {
        return;
    }
    if ((player->pos.y - 5.0f) < arg1) {
        if (player->vel.y < -10.0f) {
            AUDIO_PLAY_SFX(NA_SE_TANK_BOUND, player->sfxSource, 0);
            player->hitTimer = 10;
        }
        D_800C9F04 = 1;
        player->grounded = true;
        Math_SmoothStepToF(&player->pos.y, arg1, 0.5f, 30.0f, 0.02f);
        player->groundPos.y = arg1 - 1.0f;
        D_800C9F00 = 0;
        player->vel.y = 0.0f;
    }
}

void func_tank_80047E7C(Player* player, f32 arg1, f32 arg2) {
    player->unk_188 = 0.0f;
    if (player->pos.x < arg1) {
        if (player->zRotBank >= -10.0f) {
            Math_SmoothStepToF(&player->zRotBank, 30.0f, 0.5f, 20.0f, 0);
        } else {
            Math_SmoothStepToF(&player->pos.y, arg2, 0.5f, 30.0f, 0);
            if (player->rollState == 0) {
                player->rollState = 9;
                player->rollTimer = 15;
                player->rollRate = player->baseRollRate = -20;
            }
        }
    } else {
        if (player->zRotBank <= 10.0f) {
            Math_SmoothStepToF(&player->zRotBank, -30.0f, 0.5f, 20.0f, 0);
        } else {
            Math_SmoothStepToF(&player->pos.y, arg2, 0.5f, 30.0f, 0);
            if (player->rollState == 0) {
                player->rollState = 9;
                player->rollTimer = 15;
                player->rollRate = player->baseRollRate = 20;
            }
        }
    }
}

void func_tank_80047FBC(Player* player) {
    f32 temp_fv0;
    f32 temp_fv0_2;

    if (!(D_800C9F08 & 1)) {
        Math_SmoothStepToF(&player->rot.z, -((player->vel.z / 5.0f) * 4.0f), 0.4f, 8.0f, 0.01f);
        if (player->rot.z >= 3.0f) {
            if (gPlayer[0].state != PLAYERSTATE_LEVEL_COMPLETE) {
                AUDIO_PLAY_SFX(NA_SE_RAILWAY_BOUND, player->sfxSource, 0);
            }
            D_800C9F08 |= 1;
        }
    } else {
        Math_SmoothStepToF(&player->rot.z, (player->vel.z / 5.0f) * 4.0f, 0.4f, 8.0f, 0.01f);
        if (player->rot.z <= -3.0f) {
            D_800C9F08 &= (u8) ~1;
        }
    }
    if (!(D_800C9F08 & 8)) {
        if (-player->vel.z / 5.0f > 3.0f) {
            player->pos.y += 3.0f;
        } else {
            player->pos.y += -player->vel.z / 5.0f;
        }
        D_800C9F08 |= 8;
    } else {
        if (-player->vel.z / 5.0f > 2.0f) {
            player->pos.y -= 2.0f;
        } else {
            player->pos.y -= -player->vel.z / 5.0f;
        }
        D_800C9F08 &= (u8) ~8;
    }
}

void func_tank_800481F4(Player* player) {
    s32 pad[17];
    s32 i;
    s32 temp_v0;
    Actor* actor;
    Boss* boss;
    Sprite* sprite;
    Scenery* scenery;
    s32 sp98;
    s32 pad2;
    f32 var_fv1;

    Player_UpdateHitbox(player);
    func_tank_800444BC(player);
    if (player->mercyTimer == 0) {
        for (i = 0, scenery = &gScenery[0]; i < ARRAY_COUNT(gScenery); i++, scenery++) {
            if ((scenery->obj.status == OBJ_ACTIVE) && (scenery->obj.id != OBJ_SCENERY_TI_BRIDGE) &&
                (scenery->obj.id != OBJ_SCENERY_MA_TRAIN_TRACK_13) && (scenery->obj.id != OBJ_SCENERY_MA_BUILDING_1) &&
                (scenery->obj.id != OBJ_SCENERY_MA_BUILDING_2) && (scenery->obj.id != OBJ_SCENERY_GUILLOTINE_HOUSING) &&
                (scenery->obj.id != OBJ_SCENERY_MA_WALL_2) && (scenery->obj.id != OBJ_SCENERY_MA_WALL_3) &&
                (scenery->obj.id != OBJ_SCENERY_MA_WALL_4) && (scenery->obj.id != OBJ_SCENERY_MA_FLOOR_1) &&
                (scenery->obj.id != OBJ_SCENERY_MA_FLOOR_3) && (scenery->obj.id != OBJ_SCENERY_MA_FLOOR_2) &&
                (scenery->obj.id != OBJ_SCENERY_MA_FLOOR_4) && (scenery->obj.id != OBJ_SCENERY_MA_FLOOR_5) &&
                (scenery->obj.id != OBJ_SCENERY_MA_TERRAIN_BUMP) &&
                ((player->trueZpos - 2000.0f) < scenery->obj.pos.z)) {
                var_fv1 = scenery->obj.rot.y;
                if (scenery->info.action == (ObjectFunc) SceneryRotateTowardsCamera) {
                    var_fv1 = 0.0f;
                }
                temp_v0 = Player_CheckHitboxCollision(player, scenery->info.hitbox, &sp98, scenery->obj.pos.x,
                                                      scenery->obj.pos.y, scenery->obj.pos.z, scenery->obj.rot.x,
                                                      var_fv1, scenery->obj.rot.z, 0.0f, 0.0f, 0.0f);
                if (temp_v0 != 0) {
                    if (temp_v0 < 0) {
                        if (temp_v0 == -1) {
                            gLight2colorStep = 40;
                            gLight2RTarget = 20;
                            gLight2GTarget = 20;
                            gLight2BTarget = 20;
                            player->shadowing = 80;
                            if (player->whooshTimer == 0) {
                                AUDIO_PLAY_SFX(NA_SE_PASS, player->sfxSource, 0);
                            }
                            player->whooshTimer += 2;
                            if (player->whooshTimer >= 4) {
                                player->whooshTimer = 4;
                            }
                        } else if (temp_v0 == -2) {
                            AUDIO_PLAY_SFX(NA_SE_PASS, player->sfxSource, 0);
                        }
                    } else {
                        Player_ApplyDamage(player, temp_v0, scenery->info.damage);
                    }
                }
            }
        }

        for (i = 0, boss = &gBosses[0]; i < ARRAY_COUNT(gBosses); i++, boss++) {
            if (boss->obj.status == OBJ_ACTIVE) {
                temp_v0 = Player_CheckHitboxCollision(player, boss->info.hitbox, &sp98, boss->obj.pos.x,
                                                      boss->obj.pos.y, boss->obj.pos.z, boss->obj.rot.x,
                                                      boss->obj.rot.y, boss->obj.rot.z, 0.0f, 0.0f, 0.0f);
                if (temp_v0 != 0) {
                    Player_ApplyDamage(player, temp_v0, boss->info.damage);
                }
            }
        }

        for (i = 0, actor = &gActors[0]; i < ARRAY_COUNT(gActors); i++, actor++) {
            if ((actor->obj.status == OBJ_ACTIVE) && (actor->timer_0C2 == 0)) {
                if (actor->obj.id == OBJ_ACTOR_EVENT) {
                    temp_v0 = Player_CheckHitboxCollision(player, actor->info.hitbox, &sp98, actor->obj.pos.x,
                                                          actor->obj.pos.y, actor->obj.pos.z, actor->obj.rot.x,
                                                          actor->obj.rot.y, actor->obj.rot.z, actor->vwork[29].x,
                                                          actor->vwork[29].y, actor->vwork[29].z + actor->rot_0F4.z);
                    if (temp_v0 != 0) {
                        Player_ApplyDamage(player, temp_v0, actor->info.damage);
                        actor->dmgType = DMG_COLLISION;
                        actor->dmgSource = player->num + 1;
                    }
                } else if (actor->obj.id == OBJ_ACTOR_207) {
                    if (func_tank_80046E40(player, actor->info.hitbox, &sp98, actor->obj.pos.x, actor->obj.pos.y,
                                           actor->obj.pos.z, actor->obj.rot.x, actor->obj.rot.y, actor->obj.rot.z, 0.0f,
                                           0.0f, 0.0f) != 0) {
                        if (player->pos.x < actor->obj.pos.x) {
                            player->knockback.x = (actor->vel.z > 5.0f) ? -5.0f : -1.5f;
                            player->rollState = 8;
                            player->rollTimer = 15;
                            player->rollRate = player->baseRollRate = 20;
                        } else {
                            player->knockback.x = (actor->vel.z > 5.0f) ? 5.0f : 1.5f;
                            player->rollState = 8;
                            player->rollTimer = 15;
                            player->rollRate = player->baseRollRate = -20;
                        }
                        Math_SmoothStepToF(&player->baseSpeed, 15.0f, 0.3f, 3.5f, 0.001f);
                        Math_SmoothStepToF(&player->camDist, 0, 0.3f, 3.5f, 0.001f);
                        player->vel.x = 0.0f;
                        player->vel.y = 30.0f;
                        player->pos.x = player->basePos.x;
                        actor->dmgType = DMG_COLLISION;
                        Player_ApplyDamage(player, 0, 5);
                        player->mercyTimer = 1;
                    }
                } else if ((OBJ_ACTOR_MA_LOCOMOTIVE <= actor->obj.id) && (actor->obj.id <= OBJ_ACTOR_MA_TRAIN_CAR_7)) {
                    if (func_tank_80046E40(player, actor->info.hitbox, &sp98, actor->fwork[25] + actor->obj.pos.x,
                                           actor->fwork[8] + actor->obj.pos.y + 25.0f, actor->obj.pos.z,
                                           actor->fwork[29], actor->fwork[26], actor->obj.rot.z, 0.0f, 0.0f,
                                           0.0f) != 0) {
                        Math_SmoothStepToF(&player->baseSpeed, 15.0f, 0.3f, 3.5f, 0.001f);
                        Math_SmoothStepToF(&player->camDist, 0, 0.3f, 3.5f, 0.001f);
                        if (player->pos.x < (actor->fwork[23] + actor->obj.pos.x)) {
                            player->knockback.x = (actor->vel.z > 5.0f) ? -5.0f : -1.5f;
                            player->rollState = 8;
                            player->rollTimer = 15;
                            player->rollRate = player->baseRollRate = 20;
                        } else {
                            player->knockback.x = (actor->vel.z > 5.0f) ? 5.0f : 1.5f;
                            player->rollState = 8;
                            player->rollTimer = 15;
                            player->rollRate = player->baseRollRate = -20;
                        }
                        player->vel.x = 0.0f;
                        player->vel.y = 30.0f;
                        player->pos.x = player->basePos.x;
                        actor->dmgType = DMG_COLLISION;
                        if (actor->info.damage != 0) {
                            Player_ApplyDamage(player, 0, 20);
                        } else {
                            actor->dmgType = -1;
                        }
                    }
                } else {
                    temp_v0 = Player_CheckHitboxCollision(player, actor->info.hitbox, &sp98, actor->obj.pos.x,
                                                          actor->obj.pos.y, actor->obj.pos.z, actor->obj.rot.x,
                                                          actor->obj.rot.y, actor->obj.rot.z, 0.0f, 0.0f, 0.0f);
                    if (temp_v0 != 0) {
                        actor->dmgType = DMG_COLLISION;
                        if ((actor->obj.id == OBJ_ACTOR_TI_LANDMINE) ||
                            (actor->obj.id == OBJ_ACTOR_MISSILE_SEEK_TEAM)) {
                            actor->dmgType = -1;
                        }
                        if (actor->info.damage) {
                            Player_ApplyDamage(player, temp_v0, actor->info.damage);
                            if (actor->obj.id == OBJ_ACTOR_TI_LANDMINE) {
                                player->knockback.y = 0.0f;
                            }
                        } else {
                            actor->dmgType = -1;
                        }
                    }
                }
            }
        }
        for (i = 0, sprite = &gSprites[0]; i < ARRAY_COUNT(gSprites); i++, sprite++) {
            if (sprite->obj.status == OBJ_ACTIVE) {
                if ((player->trueZpos - 200.0f) < sprite->obj.pos.z) {
                    temp_v0 = Player_CheckHitboxCollision(player, sprite->info.hitbox, &sp98, sprite->obj.pos.x,
                                                          sprite->obj.pos.y, sprite->obj.pos.z, 0.0f, 0.0f, 0.0f, 0.0f,
                                                          0.0f, 0.0f);
                    if (temp_v0 != 0) {
                        if ((sprite->obj.id == OBJ_SPRITE_FO_POLE) || (sprite->obj.id == OBJ_SPRITE_CO_POLE) ||
                            (sprite->obj.id == OBJ_SPRITE_CO_TREE)) {
                            sprite->destroy = true;
                            player->hitTimer = 6;
                            player->hitDirection = 0;
                        } else if (sprite->obj.id == OBJ_SPRITE_TI_CACTUS) {
                            sprite->destroy = true;
                        } else {
                            Player_ApplyDamage(player, temp_v0, sprite->info.damage);
                        }
                    }
                }
            }
        }
    }
    Player_CheckItemCollect(player);
}
