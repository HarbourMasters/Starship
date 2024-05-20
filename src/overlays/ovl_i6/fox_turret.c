#include "global.h"

void Turret_SetupShot(Player* player, PlayerShot* shot, f32 xOffset, f32 yOffset, f32 zOffset, s32 shotId, f32 speed) {
    Vec3f sp4C;
    Vec3f sp40;
    Vec3f sp34;

    PlayerShot_Initialize(shot);
    Matrix_RotateY(gCalcMatrix, player->unk_000 * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, player->unk_004 * M_DTOR, MTXF_APPLY);
    Matrix_RotateZ(gCalcMatrix, player->rot.z * M_DTOR, MTXF_APPLY);
    Matrix_RotateY(gCalcMatrix, player->unk_180 * M_DTOR, MTXF_APPLY);
    Matrix_RotateX(gCalcMatrix, player->unk_17C * M_DTOR, MTXF_APPLY);
    sp4C.x = xOffset;
    sp4C.y = yOffset;
    sp4C.z = zOffset;
    Matrix_MultVec3f(gCalcMatrix, &sp4C, &sp34);
    Matrix_RotateY(gCalcMatrix, player->unk_000 * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, player->unk_004 * M_DTOR, MTXF_APPLY);
    Matrix_RotateZ(gCalcMatrix, player->rot.z * M_DTOR, MTXF_APPLY);
    Matrix_RotateY(gCalcMatrix, player->unk_180 * M_DTOR, MTXF_APPLY);
    Matrix_RotateX(gCalcMatrix, player->unk_17C * M_DTOR, MTXF_APPLY);
    Matrix_RotateY(gCalcMatrix, player->rot.y * M_DTOR, MTXF_APPLY);
    Matrix_RotateX(gCalcMatrix, player->rot.x * M_DTOR, MTXF_APPLY);
    sp4C.x = sp4C.y = 0.0f;
    sp4C.z = speed;
    Matrix_MultVec3f(gCalcMatrix, &sp4C, &sp40);
    Matrix_GetYRPAngles(gCalcMatrix, &sp4C);
    shot->obj.status = SHOT_ACTIVE;

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

    shot->obj.rot.z = player->rot.z;
    shot->unk_60 = 0;
    shot->obj.id = shotId;
    shot->timer = 40;
    shot->scale = 1.5f;

    shot->sourceId = player->num;
}

void Turret_GreatFoxLaser(Player* player, f32 xOffset) {
    s32 i;
    PlayerShot* shot;

    for (i = 0; i < ARRAY_COUNT(gPlayerShots); i++) {
        if (gPlayerShots[i].obj.status == SHOT_FREE) {
            Turret_SetupShot(player, &gPlayerShots[i], xOffset, -100.0f, 200.0f, PLAYERSHOT_GFOX_LASER, 100.0f);
            Play_PlaySfxFirstPlayer(gPlayerShots[i].sfxSource, NA_SE_TURRET_SHOT);
            break;
        }
    }
}

void Turret_Shoot(Player* player) {
    s32 i;

    if (gControllerPress[player->num].button & A_BUTTON) {
        player->shotTimer = 0;
    }
    // Fires two great fox lasers. Offsets match up with the possible guns in Draw.
    if (gControllerHold[player->num].button & A_BUTTON) {
        if (player->shotTimer == 0) {
            Turret_GreatFoxLaser(player, -100.0f);
            Turret_GreatFoxLaser(player, 100.0f);
            player->turretRecoil = 30;
        }
        player->shotTimer++;
        if (player->shotTimer >= 4) {
            player->shotTimer = 0;
        }
    }
    if (player->turretRecoil > 0) {
        player->turretRecoil -= 4;
    } else {
        player->turretRecoil = 0;
    }

    // Fires the lock on attack? The code is missing if so
    if (gControllerPress[player->num].button & R_TRIG) {
        player->turretLockOnCount = 0;
    }

    // Draws a textured line to each Event Actor in sequence as R is held. Some sort of charged lock on attack?
    for (i = 0; i < player->turretLockOnCount; i++) {
        if ((gActors[i].obj.status == OBJ_ACTIVE) && (gActors[i].obj.id == OBJ_ACTOR_EVENT)) {
            gTexturedLines[i].mode = 3;
            gTexturedLines[i].zScale = 1.0f;

            gTexturedLines[i].posAA.x = player->pos.x;
            gTexturedLines[i].posAA.y = player->pos.y;
            gTexturedLines[i].posAA.z = player->pos.z - 100.0f;

            gTexturedLines[i].timer = 2;

            gTexturedLines[i].prim.r = 255;
            gTexturedLines[i].prim.g = 255;
            gTexturedLines[i].prim.b = 255;
            gTexturedLines[i].prim.a = 255;

            gTexturedLines[i].posBB.x = gActors[i].obj.pos.x;
            gTexturedLines[i].posBB.y = gActors[i].obj.pos.y;
            gTexturedLines[i].posBB.z = gActors[i].obj.pos.z;
        }
    }
    if (gControllerHold[player->num].button & R_TRIG) {
        player->turretLockOnCount++;
        if (player->turretLockOnCount > ARRAY_COUNT(gActors)) {
            player->turretLockOnCount = ARRAY_COUNT(gActors);
        } else {
            player->turretLockOnCount = player->turretLockOnCount;
        }
    } else {
        player->turretLockOnCount = 0;
    }
}

void Turret_Update(Player* player) {
    f32 sp2C;
    f32 sp28;

    // The player follows the turret actor. Possibly the great fox
    player->pos.x = gActors[player->turretActor].obj.pos.x;
    player->pos.y = gActors[player->turretActor].obj.pos.y;
    player->pos.z = gActors[player->turretActor].obj.pos.z;
    player->unk_000 = gActors[player->turretActor].obj.rot.y;
    player->unk_004 = gActors[player->turretActor].obj.rot.x;
    player->rot.z = gActors[player->turretActor].obj.rot.z;

    // Disables controls for 50 frames. some sort of big charged attack?
    if (player->turretState < 2) {
        if (player->turretState == 0) {
            player->turretRecoil = 200;
            player->turretState++;
        }
        gControllerLock = 10;
        if (player->turretRecoil == 0) {
            gControllerLock = 0;
            player->turretState++;
            gLevelStartStatusScreenTimer = 50;
        }
    }

    // The control stick may have moved a targeting cursor
    sp2C = (f32) gControllerPress[player->num].stick_x;
    sp28 = -(f32) gControllerPress[player->num].stick_y;
    Math_SmoothStepToF(&player->rot.y, -sp2C * 0.35000002f, 0.5f, 2.0f, 0.00001f);
    Math_SmoothStepToF(&player->rot.x, -sp28 * 0.3f, 0.5f, 2.0f, 0.00001f);
    player->trueZpos = player->pos.z;
    player->zPathVel = -gActors[player->turretActor].vel.z;
    player->zPath += player->zPathVel;

    gPathVelZ = player->zPathVel;
    gPathProgress = player->zPath;

    // These appear to move the camera around unless locked in place with Z
    if (!(gControllerHold[player->num].button & Z_TRIG) && (sqrtf(SQ(sp2C) + SQ(sp28)) > 55.0f)) {
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

    // the B button recenters the view straight ahead
    if (gControllerPress[player->num].button & B_BUTTON) {
        player->unk_008 = player->unk_00C = 0.0f;
    }
    Math_SmoothStepToF(&player->unk_180, -player->unk_008, 0.5f, 3.0f, 0.00001f);
    Math_SmoothStepToF(&player->unk_17C, -player->unk_00C, 0.5f, 3.0f, 0.00001f);
    Turret_Shoot(player);
}

void Turret_UpdateCamera(Player* player) {
    Vec3f sp3C;
    Vec3f sp30;

    sp3C.x = 0.0f;
    sp3C.y = 0.0f;
    sp3C.z = 100.0f;
    Matrix_RotateY(gCalcMatrix, (player->unk_000 + (player->damageShake * 0.3f)) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, (player->unk_004 + (player->damageShake * 0.3f)) * M_DTOR, MTXF_APPLY);
    Matrix_RotateZ(gCalcMatrix, player->rot.z * M_DTOR, MTXF_APPLY);
    Matrix_RotateY(gCalcMatrix, player->unk_180 * M_DTOR, MTXF_APPLY);
    Matrix_RotateX(gCalcMatrix, player->unk_17C * M_DTOR, MTXF_APPLY);
    // unclear what values are being multiplied by 0.0f
    Matrix_RotateY(gCalcMatrix, (0.0f * player->unk_000) * M_DTOR, MTXF_APPLY);
    Matrix_RotateX(gCalcMatrix, (0.0f * player->unk_004) * M_DTOR, MTXF_APPLY);
    Matrix_MultVec3f(gCalcMatrix, &sp3C, &sp30);
    player->cam.at.x = player->pos.x + sp30.x;
    player->cam.at.y = player->pos.y + sp30.y;
    player->cam.at.z = player->pos.z + gPathProgress + sp30.z;
    player->cam.eye.x = player->pos.x;
    player->cam.eye.y = player->pos.y;
    player->cam.eye.z = player->pos.z + gPathProgress;
}

void Turret_Draw(Player* player) {
    static f32 D_i6_801A6B80 = -100.0f;

    // Probably a Y-offset adjustment, for debug?
    if (gControllerHold[player->num].button & U_JPAD) {
        D_i6_801A6B80 += 10.0f;
    }
    if (gControllerHold[player->num].button & D_JPAD) {
        D_i6_801A6B80 -= 10.0f;
    }

    Matrix_Push(&gGfxMatrix);
    // Possibly the targeting cursor. During the big attack, it would come back to the player before moving outward
    RCP_SetupDL_36();
    Matrix_Translate(gGfxMatrix, 0.0f, -100.0f, 0.0f, MTXF_APPLY);
    Matrix_RotateY(gGfxMatrix, player->rot.y * M_DTOR, MTXF_APPLY);
    Matrix_RotateX(gGfxMatrix, -player->rot.x * M_DTOR, MTXF_APPLY);
    if (player->turretState < 2) {
        Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -5000.0f + (player->turretRecoil * 25), MTXF_APPLY);
    } else {
        Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -5000.0f, MTXF_APPLY);
    }
    Matrix_Scale(gGfxMatrix, 12.0f, 12.0f, 1.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    Matrix_Pop(&gGfxMatrix);

    // Likely displayed the turrets guns. They are 100 units to the left and right of the player and 100 units below
    RCP_SetupDL_27();
    if ((player->turretRecoil > 20) && (player->turretState >= 2)) {
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 200, 0, 100, 255);
    } else {
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
    }
    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, -100.0f, -100.0f, -200.0f + player->turretRecoil, MTXF_APPLY);
    Matrix_RotateY(gGfxMatrix, player->rot.y * M_DTOR, MTXF_APPLY);
    Matrix_RotateX(gGfxMatrix, -player->rot.x * M_DTOR, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 1.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    Matrix_Pop(&gGfxMatrix);
    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, 100.0f, -100.0f, -200.0f + player->turretRecoil, MTXF_APPLY);
    Matrix_RotateY(gGfxMatrix, player->rot.y * M_DTOR, MTXF_APPLY);
    Matrix_RotateX(gGfxMatrix, -player->rot.x * M_DTOR, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 1.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    Matrix_Pop(&gGfxMatrix);

    // Likely drew muzzle flashes. This suggests the guns were 188 long
    if ((player->turretRecoil > 20) && (player->turretState >= 2)) {
        RCP_SetupDL_64();
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 128);
        Matrix_Push(&gGfxMatrix);
        Matrix_Translate(gGfxMatrix, -100.0f, -100.0f, -200.0f + player->turretRecoil, MTXF_APPLY);
        Matrix_RotateY(gGfxMatrix, player->rot.y * M_DTOR, MTXF_APPLY);
        Matrix_RotateX(gGfxMatrix, -player->rot.x * M_DTOR, MTXF_APPLY);
        Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -188.0f, MTXF_APPLY);
        Matrix_Scale(gGfxMatrix, 2.0f, 2.0f, 2.0f, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        Matrix_Pop(&gGfxMatrix);
        Matrix_Push(&gGfxMatrix);
        Matrix_Translate(gGfxMatrix, 100.0f, -100.0f, -200.0f + player->turretRecoil, MTXF_APPLY);
        Matrix_RotateY(gGfxMatrix, player->rot.y * M_DTOR, MTXF_APPLY);
        Matrix_RotateX(gGfxMatrix, -player->rot.x * M_DTOR, MTXF_APPLY);
        Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -188.0f, MTXF_APPLY);
        Matrix_Scale(gGfxMatrix, 2.0f, 2.0f, 2.0f, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        Matrix_Pop(&gGfxMatrix);
    }
}
