#include "global.h"

void Turret_801A5560(Player* player, PlayerShot* shot, f32 xOffset, f32 yOffset, f32 zOffset, s32 shotId, f32 speed) {
    Vec3f sp4C;
    Vec3f sp40;
    Vec3f sp34;

    PlayerShot_Initialize(shot);
    Matrix_RotateY(gCalcMatrix, player->unk_000 * M_DTOR, 0);
    Matrix_RotateX(gCalcMatrix, player->unk_004 * M_DTOR, 1);
    Matrix_RotateZ(gCalcMatrix, player->unk_0EC * M_DTOR, 1);
    Matrix_RotateY(gCalcMatrix, player->unk_180 * M_DTOR, 1);
    Matrix_RotateX(gCalcMatrix, player->unk_17C * M_DTOR, 1);
    sp4C.x = xOffset;
    sp4C.y = yOffset;
    sp4C.z = zOffset;
    Matrix_MultVec3f(gCalcMatrix, &sp4C, &sp34);
    Matrix_RotateY(gCalcMatrix, player->unk_000 * M_DTOR, 0);
    Matrix_RotateX(gCalcMatrix, player->unk_004 * M_DTOR, 1);
    Matrix_RotateZ(gCalcMatrix, player->unk_0EC * M_DTOR, 1);
    Matrix_RotateY(gCalcMatrix, player->unk_180 * M_DTOR, 1);
    Matrix_RotateX(gCalcMatrix, player->unk_17C * M_DTOR, 1);
    Matrix_RotateY(gCalcMatrix, player->unk_0E8 * M_DTOR, 1);
    Matrix_RotateX(gCalcMatrix, player->unk_0E4 * M_DTOR, 1);
    sp4C.x = sp4C.y = 0.0f;
    sp4C.z = speed;
    Matrix_MultVec3f(gCalcMatrix, &sp4C, &sp40);
    Matrix_GetYRPAngles(gCalcMatrix, &sp4C);
    shot->obj.status = 1;

    shot->vel.x = sp40.x;
    shot->vel.y = sp40.y;
    shot->vel.z = sp40.z;

    shot->obj.pos.x = player->pos.x + sp34.x;
    shot->obj.pos.y = player->pos.y + sp34.y;
    shot->obj.pos.z = player->pos.z + sp34.z;

    shot->obj.rot.x = sp4C.x;
    shot->obj.rot.y = sp4C.y;
    shot->obj.rot.z = sp4C.z;

    shot->unk_48 = player->unk_17C;
    shot->unk_4C = player->unk_180;
    shot->unk_50 = player->unk_004;
    shot->unk_54 = player->unk_000;

    shot->obj.rot.z = player->unk_0EC;
    shot->unk_60 = 0;
    shot->obj.id = shotId;
    shot->unk_64 = 40;
    shot->unk_44 = 1.5f;

    shot->playerNum = player->num;
}

void Turret_801A581C(Player* player, f32 xOffset) {
    s32 i;
    PlayerShot* shot;

    for (i = 0; i < ARRAY_COUNT(gPlayerShots); i++) {
        if (gPlayerShots[i].obj.status == 0) {
            Turret_801A5560(player, &gPlayerShots[i], xOffset, -100.0f, 200.0f, PLAYERSHOT_9, 100.0f);
            func_play_800A6028(gPlayerShots[i].sfxSource, 0x09000000);
            break;
        }
    }
}

void Turret_801A58A8(Player* player) {
    s32 i;

    if (gControllerPress[player->num].button & A_BUTTON) {
        player->timer_244 = 0;
    }
    if (gControllerHold[player->num].button & A_BUTTON) {
        if (player->timer_244 == 0) {
            Turret_801A581C(player, -100.0f);
            Turret_801A581C(player, 100.0f);
            player->unk_1BC = 30;
        }
        player->timer_244++;
        if (player->timer_244 >= 4) {
            player->timer_244 = 0;
        }
    }
    if (player->unk_1BC > 0) {
        player->unk_1BC -= 4;
    } else {
        player->unk_1BC = 0;
    }

    if (gControllerPress[player->num].button & R_TRIG) {
        player->unk_1C0 = 0;
    }

    for (i = 0; i < player->unk_1C0; i++) {
        if ((gActors[i].obj.status == OBJ_ACTIVE) && (gActors[i].obj.id == OBJ_ACTOR_EVENT)) {
            gTexturedLines[i].mode = 3;
            gTexturedLines[i].unk_24 = 1.0f;

            gTexturedLines[i].unk_04.x = player->pos.x;
            gTexturedLines[i].unk_04.y = player->pos.y;
            gTexturedLines[i].unk_04.z = player->pos.z - 100.0f;

            gTexturedLines[i].timer = 2;

            gTexturedLines[i].unk_2C = 255;
            gTexturedLines[i].unk_2D = 255;
            gTexturedLines[i].unk_2E = 255;
            gTexturedLines[i].unk_2F = 255;

            gTexturedLines[i].unk_10.x = gActors[i].obj.pos.x;
            gTexturedLines[i].unk_10.y = gActors[i].obj.pos.y;
            gTexturedLines[i].unk_10.z = gActors[i].obj.pos.z;
        }
    }
    if (gControllerHold[player->num].button & R_TRIG) {
        player->unk_1C0++;
        if (player->unk_1C0 > 60) {
            player->unk_1C0 = 60;
        } else {
            player->unk_1C0 = player->unk_1C0;
        }
    } else {
        player->unk_1C0 = 0;
    }
}

void Turret_801A5AD4(Player* player) {
    f32 sp2C;
    f32 sp28;

    player->pos.x = gActors[player->unk_1B4].obj.pos.x;
    player->pos.y = gActors[player->unk_1B4].obj.pos.y;
    player->pos.z = gActors[player->unk_1B4].obj.pos.z;
    player->unk_000 = gActors[player->unk_1B4].obj.rot.y;
    player->unk_004 = gActors[player->unk_1B4].obj.rot.x;
    player->unk_0EC = gActors[player->unk_1B4].obj.rot.z;
    if (player->unk_1B0 < 2) {
        if (player->unk_1B0 == 0) {
            player->unk_1BC = 200;
            player->unk_1B0++;
        }
        gControllerLock = 10;
        if (player->unk_1BC == 0) {
            gControllerLock = 0;
            player->unk_1B0++;
            gLevelStatusScreenTimer = 50;
        }
    }
    sp2C = (f32) gControllerPress[player->num].stick_x;
    sp28 = -(f32) gControllerPress[player->num].stick_y;
    Math_SmoothStepToF(&player->unk_0E8, -sp2C * 0.35000002f, 0.5f, 2.0f, 0.00001f);
    Math_SmoothStepToF(&player->unk_0E4, -sp28 * 0.3f, 0.5f, 2.0f, 0.00001f);
    player->unk_138 = player->pos.z;
    player->unk_140 = -gActors[player->unk_1B4].vel.z;
    player->unk_144 += player->unk_140;

    D_ctx_80177D08 = player->unk_140;
    D_ctx_80177D20 = player->unk_144;

    if (!(gControllerHold[player->num].button & Z_TRIG) && (sqrtf((sp2C * sp2C) + (sp28 * sp28)) > 55.0f)) {
        if ((gControllerHold[player->num].button & R_CBUTTONS) || (sp2C > 40.0f)) {
            player->unk_008 += 2.0f;
        }
        if ((gControllerHold[player->num].button & L_CBUTTONS) || (sp2C < -40.0f)) {
            player->unk_008 -= 2.0f;
        }
        if ((gControllerHold[player->num].button & U_CBUTTONS) || (sp28 < -40.0f)) {
            player->unk_00C -= 2.0f;
        }
        if ((gControllerHold[player->num].button & D_CBUTTONS) || (sp28 > 40.0f)) {
            player->unk_00C += 2.0f;
        }
    }
    if (player->unk_008 > 30.0f) {
        player->unk_008 = 30.0f;
    }
    if (player->unk_008 < -30.0f) {
        player->unk_008 = -30.0f;
    }
    if (player->unk_00C > 30.0f) {
        player->unk_00C = 30.0f;
    }
    if (player->unk_00C < -30.0f) {
        player->unk_00C = -30.0f;
    }
    player->flags_228 = 0;

    if (player->unk_008 > 20.0f) {
        player->flags_228 |= PFLAG_228_0;
    }
    if (player->unk_008 < -20.0f) {
        player->flags_228 |= PFLAG_228_1;
    }
    if (player->unk_00C > 20.0f) {
        player->flags_228 |= PFLAG_228_3;
    }
    if (player->unk_00C < -20.0f) {
        player->flags_228 |= PFLAG_228_2;
    }
    if (gControllerPress[player->num].button & B_BUTTON) {
        player->unk_008 = player->unk_00C = 0.0f;
    }
    Math_SmoothStepToF(&player->unk_180, -player->unk_008, 0.5f, 3.0f, 0.00001f);
    Math_SmoothStepToF(&player->unk_17C, -player->unk_00C, 0.5f, 3.0f, 0.00001f);
    Turret_801A58A8(player);
}

void Turret_801A5FC0(Player* player) {
    Vec3f sp3C;
    Vec3f sp30;

    sp3C.x = 0.0f;
    sp3C.y = 0.0f;
    sp3C.z = 100.0f;
    Matrix_RotateY(gCalcMatrix, (player->unk_000 + (player->unk_134 * 0.3f)) * M_DTOR, 0);
    Matrix_RotateX(gCalcMatrix, (player->unk_004 + (player->unk_134 * 0.3f)) * M_DTOR, 1);
    Matrix_RotateZ(gCalcMatrix, player->unk_0EC * M_DTOR, 1);
    Matrix_RotateY(gCalcMatrix, player->unk_180 * M_DTOR, 1);
    Matrix_RotateX(gCalcMatrix, player->unk_17C * M_DTOR, 1);
    // unclear what values are being multiplied by 0.0f
    Matrix_RotateY(gCalcMatrix, (0.0f * player->unk_000) * M_DTOR, 1);
    Matrix_RotateX(gCalcMatrix, (0.0f * player->unk_004) * M_DTOR, 1);
    Matrix_MultVec3f(gCalcMatrix, &sp3C, &sp30);
    player->camAt.x = player->pos.x + sp30.x;
    player->camAt.y = player->pos.y + sp30.y;
    player->camAt.z = player->pos.z + D_ctx_80177D20 + sp30.z;
    player->camEye.x = player->pos.x;
    player->camEye.y = player->pos.y;
    player->camEye.z = player->pos.z + D_ctx_80177D20;
}

void Turret_801A6164(Player* player) {
    static f32 D_i6_801A6B80 = -100.0f;

    if (gControllerHold[player->num].button & U_JPAD) {
        D_i6_801A6B80 += 10.0f;
    }
    if (gControllerHold[player->num].button & D_JPAD) {
        D_i6_801A6B80 -= 10.0f;
    }

    Matrix_Push(&gGfxMatrix);
    RCP_SetupDL_36();
    Matrix_Translate(gGfxMatrix, 0.0f, -100.0f, 0.0f, 1);
    Matrix_RotateY(gGfxMatrix, player->unk_0E8 * M_DTOR, 1);
    Matrix_RotateX(gGfxMatrix, -player->unk_0E4 * M_DTOR, 1);
    if (player->unk_1B0 < 2) {
        Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -5000.0f + (player->unk_1BC * 25), 1);
    } else {
        Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -5000.0f, 1);
    }
    Matrix_Scale(gGfxMatrix, 12.0f, 12.0f, 1.0f, 1);
    Matrix_SetGfxMtx(&gMasterDisp);
    Matrix_Pop(&gGfxMatrix);
    RCP_SetupDL_27();
    if ((player->unk_1BC > 20) && (player->unk_1B0 >= 2)) {
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 200, 0, 100, 255);
    } else {
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
    }
    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, -100.0f, -100.0f, -200.0f + player->unk_1BC, 1);
    Matrix_RotateY(gGfxMatrix, player->unk_0E8 * M_DTOR, 1);
    Matrix_RotateX(gGfxMatrix, -player->unk_0E4 * M_DTOR, 1);
    Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 1.0f, 1);
    Matrix_SetGfxMtx(&gMasterDisp);
    Matrix_Pop(&gGfxMatrix);
    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, 100.0f, -100.0f, -200.0f + player->unk_1BC, 1);
    Matrix_RotateY(gGfxMatrix, player->unk_0E8 * M_DTOR, 1);
    Matrix_RotateX(gGfxMatrix, -player->unk_0E4 * M_DTOR, 1);
    Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 1.0f, 1);
    Matrix_SetGfxMtx(&gMasterDisp);
    Matrix_Pop(&gGfxMatrix);
    if ((player->unk_1BC > 20) && (player->unk_1B0 >= 2)) {
        RCP_SetupDL_64();
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 128);
        Matrix_Push(&gGfxMatrix);
        Matrix_Translate(gGfxMatrix, -100.0f, -100.0f, -200.0f + player->unk_1BC, 1);
        Matrix_RotateY(gGfxMatrix, player->unk_0E8 * M_DTOR, 1);
        Matrix_RotateX(gGfxMatrix, -player->unk_0E4 * M_DTOR, 1);
        Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -188.0f, 1);
        Matrix_Scale(gGfxMatrix, 2.0f, 2.0f, 2.0f, 1);
        Matrix_SetGfxMtx(&gMasterDisp);
        Matrix_Pop(&gGfxMatrix);
        Matrix_Push(&gGfxMatrix);
        Matrix_Translate(gGfxMatrix, 100.0f, -100.0f, -200.0f + player->unk_1BC, 1);
        Matrix_RotateY(gGfxMatrix, player->unk_0E8 * M_DTOR, 1);
        Matrix_RotateX(gGfxMatrix, -player->unk_0E4 * M_DTOR, 1);
        Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -188.0f, 1);
        Matrix_Scale(gGfxMatrix, 2.0f, 2.0f, 2.0f, 1);
        Matrix_SetGfxMtx(&gMasterDisp);
        Matrix_Pop(&gGfxMatrix);
    }
}
