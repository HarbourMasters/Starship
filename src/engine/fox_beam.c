#include "global.h"
#include "assets/ast_landmaster.h"
#include "assets/ast_aquas.h"
#include "assets/ast_great_fox.h"
#include "assets/ast_versus.h"

static Vec3f sShotViewPos;

void PlayerShot_SetupEffect351(Effect* effect, f32 xPos, f32 yPos, f32 zPos) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = OBJ_EFFECT_351;
    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;
    effect->vel.z = 0.0f;
    effect->scale2 = 0.3f;
    effect->unk_4A = 100;
    effect->unk_48 = 3;

    if (Rand_ZeroOne() < 0.5f) {
        effect->unk_48 = -effect->unk_48;
    }
    Object_SetInfo(&effect->info, effect->obj.id);
}

void PlayerShot_SpawnEffect351(f32 xPos, f32 yPos, f32 zPos) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            PlayerShot_SetupEffect351(&gEffects[i], xPos, yPos, zPos);
            break;
        }
    }
}

void PlayerShot_Initialize(PlayerShot* shot) {
    s32 i;
    u8* ptr = (u8*) shot;

    for (i = 0; i < sizeof(PlayerShot); i++, ptr++) {
        *ptr = 0;
    }
}

void PlayerShot_ExplodeBomb(PlayerShot* shot) {
    f32 var_fs0;
    f32 var_fv0;
    f32 var_fv1;
    s32 var_v0;

    if (shot->unk_5C == 0) {
        shot->vel.x = shot->vel.y = shot->vel.z = shot->obj.rot.x = shot->obj.rot.y = shot->obj.rot.z = 0.0f;
        shot->scale = 1.0f;
        shot->unk_5C = 1;
        shot->timer = 30;
        shot->unk_58 = 150;
        Audio_PlayBombExplodeSfx(shot->sourceId, shot->sfxSource);
        gScreenFlashTimer = 4;
        if (shot->obj.pos.y < (gGroundHeight + 450.0f)) {
            gCameraShake = 15;
            if (gGroundSurface == SURFACE_WATER) {
                func_effect_8007D9DC(shot->obj.pos.x, gGroundHeight + 2.0f, shot->obj.pos.z, shot->unk_48 * 0.1f,
                                     shot->unk_48 * 3.0f, 0);
                func_effect_8007D9DC(shot->obj.pos.x, gGroundHeight + 2.0f, shot->obj.pos.z, shot->unk_48 * 0.1f,
                                     shot->unk_48 * 3.0f, 5);
                func_effect_8007D9DC(shot->obj.pos.x, gGroundHeight + 2.0f, shot->obj.pos.z, shot->unk_48 * 0.1f,
                                     shot->unk_48 * 3.0f, 10);
                func_effect_8007ADF4(shot->obj.pos.x, gGroundHeight, shot->obj.pos.z, shot->unk_48 * 0.05f,
                                     shot->unk_48 * 0.5f);
                func_effect_8007A6F0(&shot->obj.pos, NA_SE_OB_WATER_BOUND_M);
            } else {
                func_enmy_80062B60(shot->obj.pos.x, shot->obj.pos.z, 0, shot->unk_48 * 3.0f);
            }
        }
        if (gCurrentLevel == LEVEL_BOLSE) {
            var_fv0 = 180.0f - (shot->obj.pos.y / 20.0f);
            if (var_fv0 < 50.0f) {
                var_fv0 = 50.0f;
            }
            var_fv1 = shot->obj.pos.y / 1000.0f;
            if (var_fv1 > 2.0f) {
                var_fv1 = 2.0f;
            }
            func_effect_8007B550(shot->obj.pos.x, gGroundHeight + 6.0f, shot->obj.pos.z,
                                 shot->unk_48 * (1.5f + var_fv1), var_fv0);
        }

        if (gVersusMode) {
            var_v0 = shot->sourceId + 10;
        } else {
            var_v0 = 0;
        }
        func_effect_8007B344(shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z, shot->unk_48 * 1.5f, var_v0);
        if (gUseDynaFloor) {
            var_fs0 = 5.0f;
            if (shot->obj.pos.y > 300.0f) {
                var_fs0 = 1.0f;
            } else if (shot->obj.pos.y > 200.0f) {
                var_fs0 = 2.0f;
            } else if (shot->obj.pos.y > 100.0f) {
                var_fs0 = 3.0f;
            } else if (shot->obj.pos.y > 0.0f) {
                var_fs0 = 4.0f;
            }
            var_fs0 *= 2.0f;
            func_effect_8007AFD0(shot->obj.pos.x, shot->obj.pos.z, 50.0f, 0.0f, var_fs0);
            func_effect_8007AFD0(shot->obj.pos.x, shot->obj.pos.z, 46.0f, 19.0f, var_fs0);
            func_effect_8007AFD0(shot->obj.pos.x, shot->obj.pos.z, 35.0f, 35.0f, var_fs0);
            func_effect_8007AFD0(shot->obj.pos.x, shot->obj.pos.z, 19.0f, 46.0f, var_fs0);
            func_effect_8007AFD0(shot->obj.pos.x, shot->obj.pos.z, 0.0f, 50.0f, var_fs0);
            func_effect_8007AFD0(shot->obj.pos.x, shot->obj.pos.z, -50.0f, 0.0f, var_fs0);
            func_effect_8007AFD0(shot->obj.pos.x, shot->obj.pos.z, -46.0f, 19.0f, var_fs0);
            func_effect_8007AFD0(shot->obj.pos.x, shot->obj.pos.z, -35.0f, 35.0f, var_fs0);
            func_effect_8007AFD0(shot->obj.pos.x, shot->obj.pos.z, -19.0f, 46.0f, var_fs0);
        }
    }
}

void PlayerShot_Impact(PlayerShot* shot) {
    s32 var_v0_2;
    s32 i;

    if (shot->obj.id == PLAYERSHOT_LOCK_SEARCH) {
        Object_Kill(&shot->obj, shot->sfxSource);
        return;
    }
    shot->obj.pos.z = gShotHitPosZ; // strange order on the globals
    shot->obj.pos.y = gShotHitPosY;
    shot->obj.pos.x = gShotHitPosX;
    if ((shot->obj.id == PLAYERSHOT_BOMB) ||
        ((gCurrentLevel != LEVEL_AQUAS) && (shot->obj.id == PLAYERSHOT_LOCK_ON) && (shot->unk_5C != 0))) {
        if (shot->obj.id == PLAYERSHOT_LOCK_ON) {
            shot->obj.id = PLAYERSHOT_BOMB;
            shot->unk_5C = 0;
        }
        PlayerShot_ExplodeBomb(shot);
    } else if (shot->obj.id == PLAYERSHOT_LOCK_ON) {
        shot->scale = 7.5f;
        for (i = 0; i < ARRAY_COUNT(gActors); i++) {
            gActors[i].lockOnTimers[shot->sourceId] = 0;
        }
        shot->vel.x = shot->vel.y = shot->vel.z = 0.0f;
        if (gCurrentLevel == LEVEL_AQUAS) {
            gLight3R = gLight3G = gLight3B = 0;
            func_effect_8007B344(shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z, 10.0f, 4);
            func_effect_8007C120(shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z, 0.0f, 0.0f, 0.0f, 0.3f, 30);
        } else {
            if (gVersusMode) {
                var_v0_2 = shot->sourceId + 10;
            } else {
                var_v0_2 = 12;
            }
            func_effect_8007B344(shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z, 10.0f, var_v0_2);
            func_effect_8007D2C8(shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z, 4.0f);
        }
    } else {
        shot->obj.status = SHOT_HITMARK;
        shot->unk_60 = 0;
    }
}

void PlayerShot_SetupEffect344(Effect* effect, f32 xPos, f32 yPos, f32 zPos, f32 yRot, f32 xRot, f32 scale, s32 unk44,
                               s32 time) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = OBJ_EFFECT_344;
    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;
    effect->obj.rot.y = yRot;
    effect->obj.rot.x = xRot;
    effect->scale2 = scale * 0.5f;
    effect->unk_44 = unk44;
    effect->unk_46 = 80;
    effect->timer_50 = time;
    Object_SetInfo(&effect->info, effect->obj.id);
    Play_PlaySfxNoPlayer(effect->sfxSource, NA_SE_EXPLOSION_S);
}

void PlayerShot_SpawnEffect344(f32 xPos, f32 yPos, f32 zPos, f32 arg3, f32 arg4, f32 arg5, f32 yRot, f32 xRot,
                               f32 scale, s32 unk44, s32 time) {
    s32 i;

    if ((gGroundType != 4) && (gLevelType == LEVELTYPE_PLANET) && (gGroundSurface != SURFACE_WATER) &&
        (gCurrentLevel != LEVEL_SOLAR) && (gCurrentLevel != LEVEL_BOLSE) && (gCurrentLevel != LEVEL_TRAINING) &&
        (gCurrentLevel != LEVEL_ZONESS)) {
        for (i = 0; i < 50; i++) {
            if (gEffects[i].obj.status == OBJ_FREE) {
                PlayerShot_SetupEffect344(&gEffects[i], xPos, yPos, zPos, yRot, xRot, scale, unk44, time);
                break;
            }
        }
    }
}

void PlayerShot_SetupEffect345(Effect* effect, f32 xPos, f32 yPos, f32 zPos, f32 yRot, f32 scale) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = OBJ_EFFECT_345;
    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;
    effect->obj.rot.y = yRot;
    effect->scale2 = scale * 0.5f;
    effect->timer_50 = 80;
    Object_SetInfo(&effect->info, effect->obj.id);
    Play_PlaySfxNoPlayer(effect->sfxSource, NA_SE_EXPLOSION_S);
}

void PlayerShot_HitGround(f32 xPos, f32 yPos, f32 zPos, f32 yRot, f32 scale) {
    s32 i;

    if ((gGroundType != 4) && (gLevelType == LEVELTYPE_PLANET) && (gGroundSurface <= SURFACE_GRASS) &&
        (gCurrentLevel != LEVEL_TRAINING) && (gCurrentLevel != LEVEL_SOLAR) && (gCurrentLevel != LEVEL_ZONESS)) {
        for (i = 0; i < 50; i++) {
            if (gEffects[i].obj.status == OBJ_FREE) {
                PlayerShot_SetupEffect345(&gEffects[i], xPos, yPos, zPos, yRot, scale);
                func_effect_8007D10C(xPos, yPos, zPos, 2.0f);
                break;
            }
        }
    }
    if (gCurrentLevel == LEVEL_BOLSE) {
        func_effect_8007D10C(xPos, yPos, zPos, 2.0f);
    }
}

s32 PlayerShot_CheckObjectHitbox(PlayerShot* shot, f32* hitboxData, Object* obj) {
    s32 count;
    f32 shotPx;
    f32 shotPy;
    f32 shotPz;
    f32 xySizeMod;
    f32 boxRotX;
    f32 boxRotY;
    f32 boxRotZ;
    f32 rotateBox;
    f32 checkDist;
    Vec3f spAC;
    Vec3f spA0;
    s32 i;
    Hitbox* hitbox;

    checkDist = 2000.0f;
    if ((gCurrentLevel == LEVEL_KATINA) || (gCurrentLevel == LEVEL_SECTOR_Y)) {
        checkDist = 5000.0f;
    } else if (gCurrentLevel == LEVEL_ZONESS) {
        checkDist = 3500.0f;
    }

    if ((fabsf(shot->obj.pos.z - obj->pos.z) < checkDist) && (fabsf(shot->obj.pos.x - obj->pos.x) < checkDist) &&
        (fabsf(shot->obj.pos.y - obj->pos.y) < checkDist)) {
        count = *hitboxData;
        if (count != 0) {
            xySizeMod = 10.0f;
            if ((shot->sourceId < 4) &&
                ((gLaserStrength[shot->sourceId] != LASERS_SINGLE) || (shot->obj.id == PLAYERSHOT_LOCK_ON))) {
                xySizeMod += 30.0f;
            }
            hitboxData++;
            for (i = 0; i < count; i++, hitboxData += 6) {
                rotateBox = 0.0f;
                boxRotZ = 0.0f;
                boxRotY = 0.0f;
                boxRotX = 0.0f;
                if (hitboxData[0] >= HITBOX_SHADOW) {
                    return 0;
                }
                if (hitboxData[0] == HITBOX_ROTATED) {
                    rotateBox = 1.0f;
                    boxRotX = hitboxData[1];
                    boxRotY = hitboxData[2];
                    boxRotZ = hitboxData[3];
                    hitboxData += 4;
                }
                if ((obj->rot.y == 0.0f) && (obj->rot.z == 0.0f) && (obj->rot.x == 0.0f) && (rotateBox == 0.0f)) {
                    shotPx = shot->obj.pos.x;
                    shotPy = shot->obj.pos.y;
                    shotPz = shot->obj.pos.z;
                } else {
                    Matrix_RotateZ(gCalcMatrix, -boxRotZ * M_DTOR, MTXF_NEW);
                    Matrix_RotateX(gCalcMatrix, -boxRotX * M_DTOR, MTXF_APPLY);
                    Matrix_RotateY(gCalcMatrix, -boxRotY * M_DTOR, MTXF_APPLY);
                    Matrix_RotateZ(gCalcMatrix, -obj->rot.z * M_DTOR, MTXF_APPLY);
                    Matrix_RotateX(gCalcMatrix, -obj->rot.x * M_DTOR, MTXF_APPLY);
                    Matrix_RotateY(gCalcMatrix, -obj->rot.y * M_DTOR, MTXF_APPLY);
                    spAC.x = shot->obj.pos.x - obj->pos.x;
                    spAC.y = shot->obj.pos.y - obj->pos.y;
                    spAC.z = shot->obj.pos.z - obj->pos.z;
                    Matrix_MultVec3fNoTranslate(gCalcMatrix, &spAC, &spA0);
                    shotPx = obj->pos.x + spA0.x;
                    shotPy = obj->pos.y + spA0.y;
                    shotPz = obj->pos.z + spA0.z;
                }
                hitbox = (Hitbox*) hitboxData;
                if ((fabsf(hitbox->z.offset + obj->pos.z - shotPz) < (hitbox->z.size + 50.0f)) &&
                    (fabsf(hitbox->x.offset + obj->pos.x - shotPx) < (hitbox->x.size + xySizeMod)) &&
                    (fabsf(hitbox->y.offset + obj->pos.y - shotPy) < (hitbox->y.size + xySizeMod))) {
                    if (shot->obj.id == PLAYERSHOT_LOCK_SEARCH) {
                        Object_Kill(&shot->obj, shot->sfxSource);
                        return 0;
                    }
                    if (!((obj->id >= OBJ_ACTOR_START) && (obj->id < OBJ_ACTOR_MAX))) {
                        PlayerShot_Impact(shot);
                    }
                    if ((obj->id == OBJ_SCENERY_15) || ((obj->id == OBJ_SCENERY_22) && (i == 0)) ||
                        ((obj->id == OBJ_SCENERY_10) && (i == 0)) || ((obj->id == OBJ_SCENERY_13) && (i == 0)) ||
                        ((obj->id == OBJ_SCENERY_12) && (i < 3)) || (obj->id == OBJ_SCENERY_16) ||
                        (obj->id == OBJ_SCENERY_14)) {
                        if (shot->obj.pos.x - (obj->pos.x + hitbox->x.offset) < -hitbox->x.size) {
                            if (hitbox->z.size + (obj->pos.z + hitbox->z.offset) < shot->obj.pos.z) {
                                shot->obj.pos.z = hitbox->z.size + (obj->pos.z + hitbox->z.offset) - 5.0f;
                            }
                            PlayerShot_SpawnEffect344((hitbox->x.offset + obj->pos.x) - (hitbox->x.size + 2.0f),
                                                      shot->obj.pos.y, shot->obj.pos.z, obj->pos.x, obj->pos.z,
                                                      obj->rot.y, obj->rot.y + 90.0f, 0.0f, 2.0f, 1, 20);
                            return i + 1;
                        }
                        if (hitbox->x.size < shot->obj.pos.x - (obj->pos.x + hitbox->x.offset)) {
                            if ((hitbox->z.size + (obj->pos.z + hitbox->z.offset)) < shot->obj.pos.z) {
                                shot->obj.pos.z = hitbox->z.size + (obj->pos.z + hitbox->z.offset) - 5.0f;
                            }
                            PlayerShot_SpawnEffect344(hitbox->x.size + (hitbox->x.offset + obj->pos.x) + 2.0f,
                                                      shot->obj.pos.y, shot->obj.pos.z, obj->pos.x, obj->pos.z,
                                                      obj->rot.y, obj->rot.y + 90.0f, 0.0f, 2.0f, 1, 20);
                            return i + 1;
                        }
                        if (((hitbox->y.size + (obj->pos.y + hitbox->y.offset)) - 10.0f) <= shot->obj.pos.y) {
                            shot->obj.pos.y = ((hitbox->y.size + (obj->pos.y + hitbox->y.offset)) - 10.0f);
                        }
                        PlayerShot_SpawnEffect344(shot->obj.pos.x, shot->obj.pos.y,
                                                  hitbox->z.size + (obj->pos.z + hitbox->z.offset) + 20.0f, obj->pos.x,
                                                  obj->pos.z, 0.0f, 0.0f, 0.0f, 2.0f, 1, 20);
                        return i + 1;
                    }
                    if (obj->id < OBJ_SCENERY_MAX) {
                        func_effect_8007A6F0(&shot->obj.pos, NA_SE_EN_REFLECT);
                    }
                    return i + 1;
                }
            }
        }
    }
    return 0;
}

s32 PlayerShot_CheckEventHitbox(PlayerShot* shot, Actor* actor) {
    s32 i;
    f32* hitboxData;
    f32 shotPx;
    f32 shotPy;
    f32 shotPz;
    f32 xySizeMod;
    Vec3f sp7C;
    Vec3f sp70;
    Hitbox* hitbox;
    s32 count;

    if ((fabsf(shot->obj.pos.z - actor->obj.pos.z) < 2000.0f) &&
        (fabsf(shot->obj.pos.y - actor->obj.pos.y) < 2000.0f) &&
        (fabsf(shot->obj.pos.x - actor->obj.pos.x) < 2000.0f)) {
        hitboxData = actor->info.hitbox;
        count = *hitboxData++;
        if (count != 0) {
            xySizeMod = 0.0f;
            if (actor->info.unk_16 == 1) {
                xySizeMod = fabsf((actor->obj.pos.z + gPathProgress) / 50.0f) + 10.0f;
                if ((shot->sourceId < 4) &&
                    ((gLaserStrength[shot->sourceId] != LASERS_SINGLE) || (shot->obj.id == PLAYERSHOT_LOCK_ON))) {
                    xySizeMod += 30.0f;
                }
            }
            for (i = 0; i < count; i++, hitboxData += 6) {
                if (actor->info.unk_16 == 1) {
                    shotPx = shot->obj.pos.x;
                    shotPy = shot->obj.pos.y;
                    shotPz = shot->obj.pos.z;
                } else {
                    if (hitboxData[0] == HITBOX_ROTATED) {
                        Matrix_RotateZ(gCalcMatrix, -hitboxData[3] * M_DTOR, MTXF_NEW);
                        Matrix_RotateX(gCalcMatrix, -hitboxData[1] * M_DTOR, MTXF_APPLY);
                        Matrix_RotateY(gCalcMatrix, -hitboxData[2] * M_DTOR, MTXF_APPLY);
                        Matrix_RotateZ(gCalcMatrix, -actor->obj.rot.z * M_DTOR, MTXF_APPLY);
                        Matrix_RotateX(gCalcMatrix, -actor->obj.rot.x * M_DTOR, MTXF_APPLY);
                        Matrix_RotateY(gCalcMatrix, -actor->obj.rot.y * M_DTOR, MTXF_APPLY);
                        hitboxData += 4;
                    } else {
                        Matrix_RotateZ(gCalcMatrix, -actor->obj.rot.z * M_DTOR, MTXF_NEW);
                        Matrix_RotateX(gCalcMatrix, -actor->obj.rot.x * M_DTOR, MTXF_APPLY);
                        Matrix_RotateY(gCalcMatrix, -actor->obj.rot.y * M_DTOR, MTXF_APPLY);
                    }
                    if (((actor->vwork[29].z != 0.0f) || (actor->vwork[29].x != 0.0f) || (actor->rot_0F4.z != 0.0f) ||
                         (actor->vwork[29].y != 0.0f)) &&
                        (actor->eventType != EVID_31)) {
                        Matrix_RotateZ(gCalcMatrix, -(actor->vwork[29].z + actor->rot_0F4.z) * M_DTOR, MTXF_APPLY);
                        Matrix_RotateX(gCalcMatrix, -actor->vwork[29].x * M_DTOR, MTXF_APPLY);
                        Matrix_RotateY(gCalcMatrix, -actor->vwork[29].y * M_DTOR, MTXF_APPLY);
                    }
                    sp7C.x = shot->obj.pos.x - actor->obj.pos.x;
                    sp7C.y = shot->obj.pos.y - actor->obj.pos.y;
                    sp7C.z = shot->obj.pos.z - actor->obj.pos.z;
                    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp7C, &sp70);
                    shotPx = actor->obj.pos.x + sp70.x;
                    shotPy = actor->obj.pos.y + sp70.y;
                    shotPz = actor->obj.pos.z + sp70.z;
                }
                hitbox = (Hitbox*) hitboxData;
                if ((fabsf(hitbox->z.offset + actor->obj.pos.z - shotPz) < (hitbox->z.size + 50.0f)) &&
                    (fabsf(hitbox->x.offset + actor->obj.pos.x - shotPx) < (hitbox->x.size + xySizeMod)) &&
                    (fabsf(hitbox->y.offset + actor->obj.pos.y - shotPy) < (hitbox->y.size + xySizeMod))) {
                    return i + 1;
                }
            }
        }
    }
    return 0;
}

s32 PlayerShot_CheckActorHitbox(PlayerShot* shot, Actor* actor) {
    Object* shotx = &shot->obj;
    f32 temp_fv1 = actor->obj.pos.x - shotx->pos.x;
    f32 temp_fa0 = actor->obj.pos.z - shotx->pos.z;
    f32 var_fa1;
    f32* hitboxData = actor->info.hitbox;

    if (((s32) hitboxData[0] != 0) && (sqrtf(SQ(temp_fv1) + SQ(temp_fa0)) <= 500.0f)) {
        if (shot->sourceId < 4) {
            temp_fv1 = actor->obj.pos.x - gPlayer[0].cam.eye.x;
            temp_fa0 = actor->obj.pos.z + gPathProgress - gPlayer[0].cam.eye.z;
            var_fa1 = (sqrtf(SQ(temp_fv1) + SQ(temp_fa0)) / 50.0f) + 20.0f + 10.0f;
            if (var_fa1 > 200.0f) {
                var_fa1 = 200.0f;
            }
            if (shotx->id == PLAYERSHOT_LOCK_ON) {
                var_fa1 = 30.0f;
            } else if (gLaserStrength[shot->sourceId] != LASERS_SINGLE) {
                var_fa1 += 30.0f;
            }
            if (fabsf(hitboxData[1] + actor->obj.pos.z - shotx->pos.z) < (hitboxData[2] + var_fa1)) {
                if (fabsf(hitboxData[3] + actor->obj.pos.y - shotx->pos.y) < (hitboxData[4] + var_fa1)) {
                    if (fabsf(hitboxData[5] + actor->obj.pos.x - shotx->pos.x) < (hitboxData[6] + var_fa1)) {
                        return 1;
                    }
                }
            }
        } else {
            if (fabsf(hitboxData[1] + actor->obj.pos.z - shotx->pos.z) < hitboxData[2]) {
                if (fabsf(hitboxData[3] + actor->obj.pos.y - shotx->pos.y) < hitboxData[4]) {
                    if (fabsf(hitboxData[5] + actor->obj.pos.x - shotx->pos.x) < hitboxData[6]) {
                        return 1;
                    }
                }
            }
        }
    }

    return 0;
}

bool PlayerShot_CheckSpriteHitbox(PlayerShot* shot, Sprite* sprite) {
    f32* temp_v0 = sprite->info.hitbox;

    if (((s32) temp_v0[0] != 0) && (fabsf(temp_v0[1] + sprite->obj.pos.z - shot->obj.pos.z) < temp_v0[2]) &&
        (fabsf(temp_v0[3] + sprite->obj.pos.y - shot->obj.pos.y) < temp_v0[4]) &&
        (fabsf(temp_v0[5] + sprite->obj.pos.x - shot->obj.pos.x) < temp_v0[6])) {
        return true;
    }
    return false;
}

bool PlayerShot_CheckPolyCollision(PlayerShot* shot, ObjectId objId, Object* obj) {
    Vec3f sp7C;
    Vec3f sp70;
    Vec3f sp64;
    Vec3f sp58;
    Vec3f sp4C;
    f32 sp44[2];
    Vec3f sp38;
    bool useCol2;
    s32 pad1;

    sp7C.x = obj->pos.x - shot->obj.pos.x;
    sp7C.z = obj->pos.z - shot->obj.pos.z;
    // undefined behavior: if this check fails, the function returns no value
    if (((fabsf(sp7C.x) < 1100.0f) && (fabsf(sp7C.z) < 1100.0f) && (shot->obj.pos.y < 900.0f)) ||
        (objId == OBJ_BOSS_SZ) || (objId == ACTOR_EVENT_ID) || (objId == OBJ_SCENERY_ME_TUNNEL)) {
        Matrix_RotateY(gCalcMatrix, -obj->rot.y * M_DTOR, MTXF_NEW);
        sp7C.x = shot->obj.pos.x - obj->pos.x;
        sp7C.y = shot->obj.pos.y - obj->pos.y;
        sp7C.z = shot->obj.pos.z - obj->pos.z;
        Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp7C, &sp70);
        sp7C.x = shot->vel.x;
        sp7C.y = shot->vel.y;
        sp7C.z = shot->vel.z;
        Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp7C, &sp38);
        sp64.x = obj->pos.x + sp70.x;
        sp64.y = obj->pos.y + sp70.y;
        sp64.z = obj->pos.z + sp70.z;
        sp58.x = obj->pos.x;
        sp58.y = obj->pos.y;
        sp58.z = obj->pos.z;
        useCol2 = false;
        switch (objId) {
            case OBJ_ACTOR_180:
                objId = COL1_0;
                break;
            case OBJ_SCENERY_4:
            case OBJ_SCENERY_5:
                objId = COL2_1;
                useCol2 = true;
                break;
            case OBJ_SCENERY_149:
                objId = COL1_5;
                break;
            case OBJ_SCENERY_150:
                objId = COL1_6;
                break;
            case OBJ_BOSS_FO:
                objId = COL1_4;
                break;
            case OBJ_BOSS_VE2:
                objId = COL1_9;
                break;
            case OBJ_BOSS_309:
                objId = COL1_7;
                break;
            case ACTOR_EVENT_ID:
                objId = COL1_3;
                break;
            case OBJ_BOSS_SZ:
                objId = COL1_8;
                break;
            case OBJ_SCENERY_ME_TUNNEL:
                objId = COL1_1;
                break;
            case OBJ_SCENERY_120:
                objId = COL2_18;
                useCol2 = true;
                break;
            case OBJ_SCENERY_143:
                objId = COL2_17;
                useCol2 = true;
                break;
            case OBJ_SCENERY_124:
                objId = COL2_15;
                useCol2 = true;
                break;
            case OBJ_SCENERY_126:
                objId = COL2_16;
                useCol2 = true;
                break;
            case OBJ_SCENERY_47:
                objId = COL2_7;
                useCol2 = true;
                break;
            case OBJ_SCENERY_2:
                objId = COL2_2;
                useCol2 = true;
                break;
            case OBJ_SCENERY_3:
            case OBJ_SCENERY_69:
                objId = COL2_3;
                useCol2 = true;
                break;
            case OBJ_SCENERY_140:
                objId = COL2_4;
                useCol2 = true;
                break;
            case OBJ_SCENERY_141:
                objId = COL2_6;
                useCol2 = true;
                break;
            case OBJ_SCENERY_117:
                objId = COL2_14;
                useCol2 = true;
                break;
            case OBJ_SCENERY_70:
                objId = COL2_8;
                useCol2 = true;
                break;
            case OBJ_SCENERY_72:
                objId = COL2_9;
                useCol2 = true;
                break;
            case OBJ_SCENERY_71:
                objId = COL2_10;
                useCol2 = true;
                break;
            case OBJ_SCENERY_73:
                objId = COL2_11;
                useCol2 = true;
                break;
            case OBJ_SCENERY_67:
                objId = COL2_12;
                useCol2 = true;
                break;
            case OBJ_SCENERY_74:
                objId = COL2_13;
                useCol2 = true;
                break;
            default:
                objId = COL2_0;
                useCol2 = true;
                break;
        }
        if (!useCol2) {
            if (func_col1_800998FC(&sp64, &sp58, &sp38, objId, &sp4C, sp44) > 0) {
                if (shot->obj.id == PLAYERSHOT_LOCK_SEARCH) {
                    Object_Kill(&shot->obj, shot->sfxSource);
                    return false;
                }
                PlayerShot_Impact(shot);
                func_effect_8007A6F0(&shot->obj.pos, NA_SE_EN_REFLECT);
                if (gCurrentLevel == LEVEL_METEO) {
                    Matrix_RotateY(gCalcMatrix, obj->rot.y * M_DTOR, MTXF_NEW);
                    sp7C.x = sp4C.x - obj->pos.x;
                    sp7C.y = sp4C.y - obj->pos.y;
                    sp7C.z = sp4C.z - obj->pos.z;
                    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp7C, &sp70);
                    shot->obj.pos.x = obj->pos.x + sp70.x;
                    shot->obj.pos.y = obj->pos.y + sp70.y;
                    shot->obj.pos.z = obj->pos.z + sp70.z;
                }
                if (gCurrentLevel == LEVEL_FORTUNA) {
                    func_effect_8007BC7C(shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z, 3.0f);
                    func_effect_8007BC7C(shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z, 3.0f);
                }
                return true;
            }
        } else if (func_col2_800A3690(&sp64, &sp58, objId, &sp4C)) {
            if (shot->obj.id == PLAYERSHOT_LOCK_SEARCH) {
                Object_Kill(&shot->obj, shot->sfxSource);
                return false;
            }
            PlayerShot_Impact(shot);
            func_effect_8007A6F0(&shot->obj.pos, NA_SE_EN_REFLECT);
            if (gCurrentLevel == LEVEL_FORTUNA) {
                func_effect_8007BC7C(shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z, 3.0f);
                func_effect_8007BC7C(shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z, 3.0f);
            }
            return true;
        }
        return false;
    }
    // return false;
}

void PlayerShot_ApplyDamageToActor(PlayerShot* shot, Actor* actor, s32 hitIndex) {
    Vec3f sp44 = { 0.0f, 0.0f, -100.0f };
    Vec3f sp38;

    actor->dmgType = DMG_BEAM;
    actor->dmgPart = hitIndex - 1;
    actor->timer_0C2 = 2;
    actor->damage = 10;
    if ((shot->sourceId < 4) && (gPlayer[shot->sourceId].form != FORM_LANDMASTER)) {
        switch (gLaserStrength[shot->sourceId]) {
            case LASERS_TWIN:
                actor->damage = 12;
                break;
            case LASERS_HYPER:
                actor->damage = 15;
                break;
        }
    } else if ((shot->sourceId >= NPC_SHOT_ID) && (gCurrentLevel == LEVEL_SECTOR_X)) {
        if ((gActors[shot->sourceId - NPC_SHOT_ID].obj.id == OBJ_ACTOR_EVENT) &&
            (gActors[shot->sourceId - NPC_SHOT_ID].iwork[12] == TEAM_ID_BILL)) {
            actor->damage = 30;
        }
    }
    if (shot->obj.id == PLAYERSHOT_GFOX_LASER) {
        actor->damage = 100;
    } else if (shot->obj.id == PLAYERSHOT_LOCK_ON) {
        if (gCurrentLevel == LEVEL_AQUAS) {
            actor->damage = 31;
        } else {
            actor->dmgType = DMG_EXPLOSION;
            actor->damage = 30;
            actor->lockOnTimers[shot->sourceId] = 0;
        }
    }
    actor->dmgSource = shot->sourceId + 1;
    actor->hitPos.x = shot->obj.pos.x;
    actor->hitPos.y = shot->obj.pos.y;
    actor->hitPos.z = shot->obj.pos.z;
    if (((actor->obj.id == OBJ_ACTOR_EVENT) && (actor->dmgPart == 0) &&
         ((actor->eventType == EVID_48) || (actor->eventType == EVID_49) || (actor->eventType == EVID_50))) ||
        ((actor->obj.id == OBJ_ACTOR_ALLRANGE) && (actor->fwork[23] > 1.0f)) ||
        ((actor->obj.id == OBJ_ACTOR_EVENT) && (actor->dmgPart == 0) &&
         (actor->eventType == EVID_METEO_PYRAMID_SHIP)) ||
        ((actor->obj.id == OBJ_ACTOR_261) && (shot->obj.id != PLAYERSHOT_LOCK_ON) &&
         ((actor->state < 3) || (actor->state >= 5))) ||
        ((actor->obj.id == OBJ_ACTOR_260) && (shot->obj.id != PLAYERSHOT_LOCK_ON) && (actor->timer_0BC != 0))) {
        if ((actor->obj.id == OBJ_ACTOR_261) && (actor->state < 2)) {
            actor->state = 2;
        }
        if ((shot->obj.id == PLAYERSHOT_LOCK_ON) || (shot->obj.id == PLAYERSHOT_BOMB)) {
            PlayerShot_Impact(shot);
        } else {
            shot->timer = 25;
            shot->obj.rot.y += 90.0f;
            shot->obj.rot.x = RAND_FLOAT(360.0f);
            Matrix_RotateY(gCalcMatrix, shot->obj.rot.y * M_DTOR, MTXF_NEW);
            Matrix_RotateX(gCalcMatrix, shot->obj.rot.x * M_DTOR, MTXF_APPLY);
            Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp44, &sp38);
            shot->vel.x = sp38.x;
            shot->vel.y = sp38.y;
            shot->vel.z = sp38.z;
            shot->obj.pos.x += shot->vel.x * 5.0f;
            shot->obj.pos.y += shot->vel.y * 5.0f;
            shot->obj.pos.z += shot->vel.z * 5.0f;
            actor->timer_0C2 = 3;
            func_effect_80078E50(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, 8.0f);
            AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, actor->sfxSource, 4);
            Play_SpawnHitmark(gShotHitPosX, gShotHitPosY, gShotHitPosZ);
        }
    } else {
        PlayerShot_Impact(shot);
    }
}

void PlayerShot_CollisionCheck(PlayerShot* shot) {
    s32 i;
    s32 temp_v0;
    s32 spA4;
    Vec3f test;
    f32 sp94;
    Vec3f sp88;
    Vec3f sp7C;
    Actor* actor;
    Boss* boss;
    Scenery360* scenery360;
    Sprite* sprite;
    Scenery* scenery;
    Effect* effect;
    bool sp60;
    Player* player;

    sp60 = true;
    if (shot->obj.id == PLAYERSHOT_LOCK_SEARCH) {
        sp60 = false;
    }
    if (sp60) {
        for (i = 0, effect = gEffects; i < ARRAY_COUNT(gEffects); i++, effect++) {
            if ((effect->obj.status >= OBJ_ACTIVE) && (effect->info.unk_19 != 0) &&
                (fabsf(shot->obj.pos.z - effect->obj.pos.z) < 200.0f) &&
                (fabsf(shot->obj.pos.x - effect->obj.pos.x) < 100.0f) &&
                (fabsf(shot->obj.pos.y - effect->obj.pos.y) < 100.0f)) {
                if (effect->info.unk_19 == 2) {
                    effect->unk_44 = 1;
                } else {
                    Object_Kill(&effect->obj, effect->sfxSource);
                }
            }
        }
        for (i = 0, actor = gActors; i < ARRAY_COUNT(gActors); i++, actor++) {
            if ((actor->obj.status >= OBJ_ACTIVE) && (actor->timer_0C2 == 0)) {
                switch (actor->obj.id) {
                    case OBJ_ACTOR_180:
                        if (PlayerShot_CheckPolyCollision(shot, actor->obj.id, &actor->obj)) {
                            actor->dmgType = DMG_BEAM;
                            actor->dmgPart = shot->sourceId;
                            return;
                        }
                        break;
                    case OBJ_ACTOR_EVENT:
                        if (actor->eventType == EVID_42) {
                            if (PlayerShot_CheckPolyCollision(shot, ACTOR_EVENT_ID, &actor->obj)) {
                                actor->dmgType = DMG_BEAM;
                                actor->dmgPart = shot->sourceId;
                                return;
                            }
                        } else if (actor->eventType == EVID_63) {
                            test.x = fabsf(actor->obj.pos.x - shot->obj.pos.x);
                            test.y = fabsf(actor->obj.pos.y - shot->obj.pos.y);
                            test.z = fabsf(actor->obj.pos.z - shot->obj.pos.z);
                            if (VEC3F_MAG(&test) < 1000.0f) {
                                PlayerShot_ApplyDamageToActor(shot, actor, 0);
                            }
                        } else {
                            temp_v0 = PlayerShot_CheckEventHitbox(shot, actor);
                            if (temp_v0 != 0) {
                                PlayerShot_ApplyDamageToActor(shot, actor, temp_v0);
                                return;
                            }
                        }
                        break;
                    default:
                        if (actor->info.unk_16 != 0) {
                            if (actor->obj.id == OBJ_ACTOR_ALLRANGE) {
                                if ((actor->aiType >= AI360_WOLF) && (actor->aiType < AI360_10) &&
                                    (((gCurrentLevel == LEVEL_VENOM_2) &&
                                      (shot->sourceId <= NPC_SHOT_ID + AI360_PEPPY)) ||
                                     ((gCurrentLevel != LEVEL_VENOM_2) && (shot->sourceId == AI360_FOX))) &&
                                    (shot->obj.id != PLAYERSHOT_LOCK_ON) &&
                                    (fabsf(actor->obj.pos.x - shot->obj.pos.x) < 500.0f) &&
                                    (fabsf(actor->obj.pos.y - shot->obj.pos.y) < 300.0f) &&
                                    (fabsf(actor->obj.pos.z - shot->obj.pos.z) < 500.0f)) {
                                    if (gCurrentLevel == LEVEL_VENOM_2) {
                                        actor->iwork[17] = 1;
                                    } else if (Rand_ZeroOne() < 0.1f) {
                                        actor->iwork[17] = 1;
                                    }
                                }
                            }
                            temp_v0 = PlayerShot_CheckActorHitbox(shot, actor);
                            if (temp_v0 != 0) {
                                PlayerShot_ApplyDamageToActor(shot, actor, temp_v0);
                                return;
                            }
                        } else {
                            temp_v0 = PlayerShot_CheckObjectHitbox(shot, actor->info.hitbox, &actor->obj);
                            if (temp_v0 != 0) {
                                PlayerShot_ApplyDamageToActor(shot, actor, temp_v0);
                                return;
                            }
                        }
                        break;
                }
            }
        }
        if (gLevelMode == LEVELMODE_ALL_RANGE) {
            for (i = 0, player = gPlayer; i < gCamCount; i++, player++) {
                test.x = 50.0f;
                if (gVersusMode && (shot->sourceId < 4) &&
                    ((gLaserStrength[shot->sourceId] != LASERS_SINGLE) || (shot->obj.id == PLAYERSHOT_LOCK_ON))) {
                    test.x = 100.0f;
                }
                if (player->barrelRollAlpha >= 100) {
                    test.x = 150.0f;
                }
                if (player->form == FORM_LANDMASTER) {
                    test.x *= 2.0f;
                    test.y = test.x + 50.0f;
                } else if (player->form == FORM_ON_FOOT) {
                    test.y = test.x + 50.0f;
                } else {
                    test.y = test.x;
                }
                test.z = test.x;
                if ((i != shot->sourceId) &&
                    ((player->state_1C8 == PLAYERSTATE_1C8_ACTIVE) || (player->state_1C8 == PLAYERSTATE_1C8_DOWN)) &&
                    (fabsf(player->trueZpos - shot->obj.pos.z) < test.z) &&
                    (fabsf(player->pos.x - shot->obj.pos.x) < test.x) &&
                    (fabsf(player->pos.y - shot->obj.pos.y) < test.y)) {
                    if (player->barrelRollAlpha >= 100) {
                        shot->obj.rot.y = player->rot.y + player->yRot_114 + 180.0f + 90.0f;
                        shot->obj.rot.x = RAND_FLOAT(360.0f);
                        Matrix_RotateY(gCalcMatrix, shot->obj.rot.y * M_DTOR, MTXF_NEW);
                        Matrix_RotateX(gCalcMatrix, shot->obj.rot.x * M_DTOR, MTXF_APPLY);
                        sp88.x = sp88.y = 0.0f;
                        sp88.z = -400.0f / 3.0f;
                        Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp88, &sp7C);
                        shot->vel.x = sp7C.x;
                        shot->vel.y = sp7C.y;
                        shot->vel.z = sp7C.z;
                        shot->obj.pos.x += 2.0f * shot->vel.x;
                        shot->obj.pos.y += 2.0f * shot->vel.y;
                        shot->obj.pos.z += 2.0f * shot->vel.z;
                        shot->timer = 5;
                        AUDIO_PLAY_SFX(NA_SE_ROLLING_REFLECT, player->sfxSource, 0);
                        func_effect_80078E50(player->pos.x, player->pos.y, player->trueZpos, 8.0f);
                    } else {
                        PlayerShot_Impact(shot);
                        if (player->hitTimer == 0) {
                            if (gPlayer[0].form == FORM_ON_FOOT) {
                                Player_ApplyDamage(player, 0, 60);
                            } else {
                                Player_ApplyDamage(player, 0, 20);
                            }
                            player->unk_284 = 1;
                            if (gCamCount != 1) {
                                player->attacker = shot->sourceId + 1;
                            }
                            player->knockback.x = shot->vel.x * 0.1f;
                            player->knockback.y = shot->vel.y * 0.1f;
                            player->knockback.z = shot->vel.z * 0.1f;
                            if (player->form != FORM_ON_FOOT) {
                                func_effect_8007D1E0(player->pos.x, player->pos.y, player->trueZpos, 2.0f);
                            }
                        }
                    }
                }
            }
        }
    }
    if ((gGroundType == 4) && Ground_801B6AEC(shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z + gPathProgress)) {
        PlayerShot_Impact(shot);
        if (shot->obj.id != PLAYERSHOT_LOCK_SEARCH) {
            func_effect_8007A900(shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z, 2.0f, 255, 15, 0);
        }
    }
    if (gUseDynaFloor &&
        Play_CheckDynaFloorCollision(&sp94, &spA4, shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z)) {
        PlayerShot_Impact(shot);
        if (shot->obj.id != PLAYERSHOT_LOCK_SEARCH) {
            func_effect_8007B228(shot->obj.pos.x, sp94, shot->obj.pos.z, 1.0f);
        }
    }

    if ((gLevelMode == LEVELMODE_ALL_RANGE) && (shot->sourceId < 110)) {
        for (i = 0, scenery360 = gScenery360; i < 200; i++, scenery360++) {
            if (scenery360->obj.status == OBJ_ACTIVE) {
                if ((scenery360->obj.id == OBJ_SCENERY_117) || (scenery360->obj.id == OBJ_SCENERY_141) ||
                    (scenery360->obj.id == OBJ_SCENERY_149) || (scenery360->obj.id == OBJ_SCENERY_150) ||
                    (scenery360->obj.id == OBJ_SCENERY_148) || (scenery360->obj.id == OBJ_SCENERY_143) ||
                    (scenery360->obj.id == OBJ_SCENERY_160) || (scenery360->obj.id == OBJ_SCENERY_1) ||
                    (scenery360->obj.id == OBJ_SCENERY_3) || (scenery360->obj.id == OBJ_SCENERY_140)) {
                    PlayerShot_CheckPolyCollision(shot, scenery360->obj.id, &scenery360->obj);
                } else {
                    PlayerShot_CheckObjectHitbox(shot, scenery360->info.hitbox, &scenery360->obj);
                }
            }
        }
    } else {
        for (i = 0, scenery = gScenery; i < ARRAY_COUNT(gScenery); i++, scenery++) {
            if (scenery->obj.status == OBJ_ACTIVE) {
                if ((scenery->obj.id == OBJ_SCENERY_1) || (scenery->obj.id == OBJ_SCENERY_ME_TUNNEL) ||
                    (scenery->obj.id == OBJ_SCENERY_4) || (scenery->obj.id == OBJ_SCENERY_5) ||
                    (scenery->obj.id == OBJ_SCENERY_120) || (scenery->obj.id == OBJ_SCENERY_124) ||
                    (scenery->obj.id == OBJ_SCENERY_126) || (scenery->obj.id == OBJ_SCENERY_47) ||
                    (scenery->obj.id == OBJ_SCENERY_2) || (scenery->obj.id == OBJ_SCENERY_3) ||
                    (scenery->obj.id == OBJ_SCENERY_67) || (scenery->obj.id == OBJ_SCENERY_74) ||
                    (scenery->obj.id == OBJ_SCENERY_3)) {
                    PlayerShot_CheckPolyCollision(shot, scenery->obj.id, &scenery->obj);
                } else {
                    temp_v0 = PlayerShot_CheckObjectHitbox(shot, scenery->info.hitbox, &scenery->obj);
                    if (temp_v0 != 0) {
                        scenery->dmgType = DMG_BEAM;
                        scenery->dmgPart = temp_v0 - 1;
                    }
                }
            }
        }
    }
    if (sp60) {
        for (i = 0, sprite = gSprites; i < ARRAY_COUNT(gSprites); i++, sprite++) {
            if (sprite->obj.status == OBJ_ACTIVE) {
                if (sprite->obj.id != OBJ_SPRITE_TI_CACTUS) {
                    if (PlayerShot_CheckSpriteHitbox(shot, sprite)) {
                        sprite->destroy = 1;
                    }
                } else {
                    if (PlayerShot_CheckObjectHitbox(shot, sprite->info.hitbox, &sprite->obj) != 0) {
                        sprite->destroy = 1;
                    }
                }
            }
        }
    }
    for (i = 0, boss = gBosses; i < ARRAY_COUNT(gBosses); i++, boss++) {
        if ((boss->obj.status == OBJ_ACTIVE) && (boss->timer_05A == 0)) {
            if ((boss->obj.id == OBJ_BOSS_FO) || (boss->obj.id == OBJ_BOSS_VE2) || (boss->obj.id == OBJ_BOSS_309) ||
                (boss->obj.id == OBJ_BOSS_SZ)) {
                PlayerShot_CheckPolyCollision(shot, boss->obj.id, &boss->obj);
            } else if (boss->obj.id == OBJ_BOSS_310) {
                test.x = fabsf(boss->obj.pos.x - shot->obj.pos.x) * .8333333f;
                test.y = fabsf(boss->obj.pos.y - shot->obj.pos.y) * 2;
                test.z = fabsf(boss->obj.pos.z - shot->obj.pos.z) * 0.8333333f;
                if (VEC3F_MAG(&test) < 1500.0f) {
                    if (shot->obj.id == PLAYERSHOT_LOCK_SEARCH) {
                        Object_Kill(&shot->obj, shot->sfxSource);
                    } else {
                        boss->dmgType = DMG_BEAM;
                        PlayerShot_Impact(shot);
                        AUDIO_PLAY_SFX(NA_SE_EN_BARRIER_REFLECT, shot->sfxSource, 4);
                    }
                }
            } else {
                if (boss->obj.id == OBJ_BOSS_KA) {
                    test.x = fabsf(boss->obj.pos.x - shot->obj.pos.x);
                    test.y = fabsf(boss->obj.pos.y - 300.0f - shot->obj.pos.y) * 7.42f;
                    test.z = fabsf(boss->obj.pos.z - shot->obj.pos.z);
                    if (VEC3F_MAG(&test) < 2700.0f) {
                        if (shot->obj.id == PLAYERSHOT_LOCK_SEARCH) {
                            Object_Kill(&shot->obj, shot->sfxSource);
                        } else {
                            boss->dmgType = DMG_BEAM;
                            boss->dmgPart = 100;
                            AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, shot->sfxSource, 4);
                            PlayerShot_Impact(shot);
                        }
                    }
                }
                temp_v0 = PlayerShot_CheckObjectHitbox(shot, boss->info.hitbox, &boss->obj);
                if (temp_v0 != 0) {
                    if (shot->obj.id == PLAYERSHOT_LOCK_SEARCH) {
                        Object_Kill(&shot->obj, shot->sfxSource);
                    } else {
                        if ((boss->obj.id == OBJ_BOSS_KA) && (shot->sourceId != TEAM_ID_FOX)) {
                            break;
                        }
                        boss->dmgType = DMG_BEAM;
                        if (shot->obj.id == PLAYERSHOT_BOMB) {
                            boss->dmgType = DMG_BOMB;
                            boss->damage = 20;
                        } else if (shot->obj.id == PLAYERSHOT_LOCK_ON) {
                            if (gCurrentLevel == LEVEL_AQUAS) {
                                boss->damage = 31;
                            } else {
                                boss->damage = 30;
                            }
                        } else {
                            boss->damage = 10;
                            if (shot->sourceId < 4) {
                                switch (gLaserStrength[shot->sourceId]) {
                                    case LASERS_SINGLE:
                                    case LASERS_TWIN:
                                        break;
                                    case LASERS_HYPER:
                                        boss->damage = 15;
                                        break;
                                }
                            }
                        }
                        if (boss->obj.id == OBJ_BOSS_SY) {
                            boss->swork[19] = shot->sourceId;
                        }
                        boss->dmgPart = temp_v0 - 1;
                        if (boss->obj.id == OBJ_BOSS_301) {
                            boss->swork[5] = shot->obj.id;
                        } else if (boss->obj.id == OBJ_BOSS_VE1) {
                            boss->fwork[47] = shot->obj.pos.x;
                            boss->fwork[48] = shot->obj.pos.y;
                            boss->fwork[49] = shot->obj.pos.z;
                        }
                    }
                }
            }
        }
    }
}

void PlayerShot_DrawHitmark(PlayerShot* shot) {
    Vec3f sp4C = { 0.0f, 0.0f, 0.0f };
    s32 isDrawn = false;

    Matrix_Translate(gGfxMatrix, shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z + gPathProgress, MTXF_APPLY);
    Matrix_MultVec3f(gGfxMatrix, &sp4C, &sShotViewPos);
    if ((sShotViewPos.z < 0.0f) && (sShotViewPos.z > -10000.0f)) {
        if (fabsf(sShotViewPos.x) < (fabsf(sShotViewPos.z * 0.5f) + 500.0f)) {
            if (fabsf(sShotViewPos.y) < (fabsf(sShotViewPos.z * 0.5f) + 500.0f)) {
                isDrawn = true;
            }
        }
    }
    if (!isDrawn) {
        if (!gVersusMode) {
            Object_Kill(&shot->obj, shot->sfxSource);
            return;
        }
    } else {
        shot->obj.rot.y = -gPlayer[gPlayerNum].camYaw;
        Matrix_RotateY(gGfxMatrix, shot->obj.rot.y, MTXF_APPLY);
        Matrix_Scale(gGfxMatrix, 2.0f, 2.0f, 2.0f, MTXF_APPLY);
        if (shot->obj.id == PLAYERSHOT_7) {
            Matrix_Scale(gGfxMatrix, 0.2f, 0.2f, 0.2f, MTXF_APPLY);
        }
        Matrix_SetGfxMtx(&gMasterDisp);
        RCP_SetupDL_40();
        switch (shot->unk_60) {
            case 0:
                gSPDisplayList(gMasterDisp++, D_1026090);
                break;
            case 1:
                gSPDisplayList(gMasterDisp++, D_1025800);
                break;
            case 2:
                Matrix_Scale(gGfxMatrix, 1.5f, 0.7f, 1.0f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_1025800);
                break;
        }
    }
}

void PlayerShot_DrawLaser(PlayerShot* shot) {
    f32 width;
    f32 length;
    u8 var_a1;
    f32 twinLaserSeparation;
    Gfx* dList;

    dList = D_101AED0;
    if (gCamCount < 4) {
        RCP_SetupDL_21();
        twinLaserSeparation = 9.0f;
        if ((shot->unk_58 == 0) ||
            ((gCurrentLevel == LEVEL_METEO) && (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_LEVEL_INTRO))) {
            width = 4.0f;
            length = 20.0f;
        } else {
            width = 2.0f;
            length = 10.0f;
        }
        if ((gLaserStrength[0] > LASERS_SINGLE) && (shot->unk_58 == 0)) {
            switch (gLaserStrength[0]) {
                case LASERS_TWIN:
                    break;
                case LASERS_HYPER:
                    dList = D_101AD20;
                    break;
            }
            if (gCurrentLevel == LEVEL_AQUAS) {
                twinLaserSeparation = 4.0f;
            }
            Matrix_Scale(gGfxMatrix, width, width, length, MTXF_APPLY);
            Matrix_RotateY(gGfxMatrix, M_PI, MTXF_APPLY);
            Matrix_Translate(gGfxMatrix, twinLaserSeparation, 0.f, 0.0f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, dList);
            Matrix_Translate(gGfxMatrix, -(2.0f * twinLaserSeparation), 0.0f, 0.f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, dList);
        } else {
            var_a1 = 0;
            if ((gCurrentLevel != LEVEL_KATINA) && (shot->sourceId > NPC_SHOT_ID + AI360_PEPPY) &&
                (shot->sourceId != NPC_SHOT_ID + AI360_KATT)) {
                if (gActors[shot->sourceId - NPC_SHOT_ID].obj.id != OBJ_ACTOR_EVENT) {
                    var_a1 = 1;
                } else if (gActors[shot->sourceId - NPC_SHOT_ID].iwork[12] == TEAM_ID_BILL) {
                    var_a1 = 2;
                }
            } else if (gCurrentLevel == LEVEL_KATINA) {
                if (gPlayer[0].state_1C8 != PLAYERSTATE_1C8_LEVEL_INTRO) {
                    if (shot->sourceId > NPC_SHOT_ID + AI360_PEPPY) {
                        if (gActors[shot->sourceId - NPC_SHOT_ID].animFrame == 0) {
                            var_a1 = 1;
                        }
                        if (gActors[shot->sourceId - NPC_SHOT_ID].animFrame == 2) {
                            var_a1 = 2;
                        }
                    }
                } else if (gActors[shot->sourceId - NPC_SHOT_ID].animFrame == 34) {
                    var_a1 = 1;
                }
            }
            switch (var_a1) {
                case 0:
                    Matrix_Scale(gGfxMatrix, width, width, length, MTXF_APPLY);
                    Matrix_RotateY(gGfxMatrix, M_PI, MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_101AED0);
                    break;
                case 1:
                    Matrix_Translate(gGfxMatrix, 0.0f, 0.f, 150.0f, MTXF_APPLY);
                    Matrix_Scale(gGfxMatrix, 0.7f, 0.7f, 1.5f, MTXF_APPLY);
                    Matrix_RotateY(gGfxMatrix, M_PI, MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_101ABD0);
                    break;
                case 2:
                    Matrix_Scale(gGfxMatrix, width, width, length, MTXF_APPLY);
                    Matrix_RotateY(gGfxMatrix, M_PI, MTXF_APPLY);
                    Matrix_Translate(gGfxMatrix, 25.0f, 0.0f, 0.f, MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_101AED0);
                    dList = D_101AED0;
                    Matrix_Translate(gGfxMatrix, -50.0f, 0.0f, 0.f, MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, dList);
                    break;
                case 3:
                    Matrix_Push(&gGfxMatrix);
                    Matrix_Translate(gGfxMatrix, 50.0f, 0.0f, 150.0f, MTXF_APPLY);
                    Matrix_Scale(gGfxMatrix, 0.7f, 0.7f, 1.5f, MTXF_APPLY);
                    Matrix_RotateY(gGfxMatrix, M_PI, MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_101ABD0);
                    Matrix_Pop(&gGfxMatrix);
                    Matrix_Translate(gGfxMatrix, -50.0f, 0.0f, 150.0f, MTXF_APPLY);
                    Matrix_Scale(gGfxMatrix, 0.7f, 0.7f, 1.5f, MTXF_APPLY);
                    Matrix_RotateY(gGfxMatrix, M_PI, MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_101ABD0);
                    break;
            }
        }
    } else {
        RCP_SetupDL_64();
        switch (shot->sourceId) {
            case 0:
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 32, 255);
                break;
            case 1:
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 100, 200, 255);
                break;
            case 2:
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 32, 255, 32, 255);
                break;
            case 3:
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 32, 32, 255, 255);
                break;
        }
        Matrix_Scale(gGfxMatrix, 6.0f, 4.0f, 10.0f, MTXF_APPLY);
        Matrix_RotateY(gGfxMatrix, M_PI, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        if (gLaserStrength[shot->sourceId] != LASERS_SINGLE) {
            Matrix_Translate(gGfxMatrix, 6.0f, 0.0f, 0.0f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_versus_302D120);
            Matrix_Translate(gGfxMatrix, -12.0f, 0.0f, 0.0f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_versus_302D120);
        } else {
            gSPDisplayList(gMasterDisp++, D_versus_302D120);
        }
    }
}

static f32 D_800C9BD8[10] = { 100.0f, 100.0f, 0.0f, 0.0f, 0.0f, 50.0f, 0.0f, 40.0f, 30.0f, 100.0f };
static u8 D_800C9C00[4] = { 255, 255, 32, 32 };
static u8 D_800C9C04[4] = { 255, 32, 255, 32 };
static u8 D_800C9C08[4] = { 32, 32, 32, 255 };
void PlayerShot_DrawShot(PlayerShot* shot) {
    Vec3f sp11C = { 0.0f, 0.0f, 0.0f };
    s32 pad[4];
    f32 var_fv1;
    s32 isDrawn = false;

    Matrix_Translate(gGfxMatrix, shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z + gPathProgress, MTXF_APPLY);
    Matrix_MultVec3f(gGfxMatrix, &sp11C, &sShotViewPos);
    if ((sShotViewPos.z < 0.0f) && (sShotViewPos.z > -10000.0f)) {
        var_fv1 = fabsf(sShotViewPos.x); // probably fake. The use of temps was likely different
        if (var_fv1 < (fabsf(sShotViewPos.z * 0.5f) + 500.0f)) {
            if (fabsf(sShotViewPos.y) < (fabsf(sShotViewPos.z * 0.5f) + 500.0f)) {
                isDrawn = true;
            }
        }
    }
    if (!isDrawn) {
        if ((shot->obj.id != PLAYERSHOT_BOMB) && (shot->timer < 10) && !gVersusMode) {
            Object_Kill(&shot->obj, shot->sfxSource);
        }
    } else {
        if ((shot->obj.id == PLAYERSHOT_TANK) || (shot->obj.id == PLAYERSHOT_ON_FOOT) ||
            (shot->obj.id == PLAYERSHOT_7)) {
            shot->obj.rot.y = RAD_TO_DEG(-gPlayer[gPlayerNum].camYaw);
            shot->obj.rot.x = RAD_TO_DEG(gPlayer[gPlayerNum].camPitch);
        }
        if (shot->obj.id != PLAYERSHOT_2) {
            Matrix_RotateY(gGfxMatrix, shot->obj.rot.y * M_DTOR, MTXF_APPLY);
            Matrix_RotateX(gGfxMatrix, shot->obj.rot.x * M_DTOR, MTXF_APPLY);
            Matrix_RotateZ(gGfxMatrix, shot->obj.rot.z * M_DTOR, MTXF_APPLY);
            if ((shot->obj.id == PLAYERSHOT_BOMB) && (shot->unk_5C == 0)) {
                Matrix_RotateZ(gGfxMatrix, shot->vec_2C.z * M_DTOR, MTXF_APPLY);
                Matrix_RotateY(gGfxMatrix, shot->vec_2C.y * M_DTOR, MTXF_APPLY);
                Matrix_RotateX(gGfxMatrix, shot->vec_2C.x * M_DTOR, MTXF_APPLY);
            }
        }
        Matrix_Translate(gGfxMatrix, 0.f, 0.f, D_800C9BD8[shot->obj.id], MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        switch (shot->obj.id) {
            case PLAYERSHOT_SINGLE_LASER:
            case PLAYERSHOT_TWIN_LASER:
                PlayerShot_DrawLaser(shot);
                break;
            case PLAYERSHOT_BOMB:
                if (shot->unk_5C == 0) {
                    RCP_SetupDL(&gMasterDisp, SETUPDL_29);
                    gSPDisplayList(gMasterDisp++, D_10231A0);
                    Matrix_Pop(&gGfxMatrix);
                    Matrix_Push(&gGfxMatrix);
                    Matrix_Translate(gGfxMatrix, shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z + gPathProgress,
                                     MTXF_APPLY);
                    Matrix_RotateY(gGfxMatrix, -gPlayer[gPlayerNum].camYaw, MTXF_APPLY);
                    Matrix_RotateX(gGfxMatrix, gPlayer[gPlayerNum].camPitch, MTXF_APPLY);
                    Matrix_RotateZ(gGfxMatrix, gGameFrameCount * 40.0f * M_DTOR, MTXF_APPLY);
                    if (((gGameFrameCount % 2) == 0)) {
                        Matrix_Scale(gGfxMatrix, 1.7f, 1.7f, 1.7f, MTXF_APPLY);
                    } else {
                        Matrix_Scale(gGfxMatrix, 1.2f, 1.2f, 1.2f, MTXF_APPLY);
                    }
                    RCP_SetupDL(&gMasterDisp, SETUPDL_49);
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
                    if (gVersusMode) {
                        switch (shot->sourceId) {
                            case 0:
                                gDPSetEnvColor(gMasterDisp++, 255, 255, 32, 128);
                                break;
                            case 1:
                                gDPSetEnvColor(gMasterDisp++, 255, 32, 32, 128);
                                break;
                            case 2:
                                gDPSetEnvColor(gMasterDisp++, 32, 255, 32, 128);
                                break;
                            case 3:
                                gDPSetEnvColor(gMasterDisp++, 32, 32, 255, 128);
                                break;
                        }
                    } else {
                        gDPSetEnvColor(gMasterDisp++, 0, 128, 255, 255);
                    }
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_1024AC0);
                } else {
                    Matrix_Scale(gGfxMatrix, shot->scale, shot->scale, shot->scale, MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    if (gVersusMode) {
                        RCP_SetupDL_49();
                        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, shot->unk_58);
                        switch (shot->sourceId) {
                            case 0:
                                gDPSetEnvColor(gMasterDisp++, 255, 255, 32, shot->unk_58);
                                break;
                            case 1:
                                gDPSetEnvColor(gMasterDisp++, 255, 32, 32, shot->unk_58);
                                break;
                            case 2:
                                gDPSetEnvColor(gMasterDisp++, 32, 255, 32, shot->unk_58);
                                break;
                            case 3:
                                gDPSetEnvColor(gMasterDisp++, 32, 32, 255, shot->unk_58);
                                break;
                        }
                    } else {
                        RCP_SetupDL_64_2();
                        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, shot->unk_58);
                    }
                    gSPDisplayList(gMasterDisp++, D_1031EC0);
                }
                break;
            case PLAYERSHOT_TANK:
                gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                RCP_SetupDL_40();
                if (gVersusMode) {
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
                    gDPSetEnvColor(gMasterDisp++, D_800C9C00[shot->sourceId], D_800C9C04[shot->sourceId],
                                   D_800C9C08[shot->sourceId], 255);
                    RCP_SetupDL(&gMasterDisp, SETUPDL_49);
                    if (gLaserStrength[shot->sourceId] != LASERS_SINGLE) {
                        Matrix_RotateZ(gGfxMatrix, gGameFrameCount * 48.0f * M_DTOR, MTXF_APPLY);
                        Matrix_Push(&gGfxMatrix);
                        Matrix_Translate(gGfxMatrix, 0.f, 50.0f, 0.0f, MTXF_APPLY);
                        Matrix_RotateZ(gGfxMatrix, gGameFrameCount * 70.0f * M_DTOR, MTXF_APPLY);
                        Matrix_Scale(gGfxMatrix, 2.0f, 2.0f, 2.0f, MTXF_APPLY);
                        Matrix_SetGfxMtx(&gMasterDisp);
                        gSPDisplayList(gMasterDisp++, D_versus_301AD60);
                        Matrix_Pop(&gGfxMatrix);
                        Matrix_Translate(gGfxMatrix, 0.0f, -50.0f, 0.0f, MTXF_APPLY);
                        Matrix_RotateZ(gGfxMatrix, gGameFrameCount * 70.0f * M_DTOR, MTXF_APPLY);
                        Matrix_Scale(gGfxMatrix, 2.0f, 2.0f, 2.0f, MTXF_APPLY);
                        Matrix_SetGfxMtx(&gMasterDisp);
                        gSPDisplayList(gMasterDisp++, D_versus_301AD60);
                    } else {
                        if (((gGameFrameCount % 2) == 0)) {
                            var_fv1 = M_PI;
                        } else {
                            var_fv1 = 0.0f;
                        }
                        Matrix_RotateY(gGfxMatrix, var_fv1, MTXF_APPLY);
                        Matrix_RotateZ(gGfxMatrix, 30.0f * M_DTOR, MTXF_APPLY);
                        Matrix_Scale(gGfxMatrix, 2.0f, 2.0f, 2.0f, MTXF_APPLY);
                        Matrix_SetGfxMtx(&gMasterDisp);
                        gSPDisplayList(gMasterDisp++, D_versus_301AD60);
                    }
                } else {
                    if (((gGameFrameCount % 2) == 0)) {
                        var_fv1 = M_PI;
                    } else {
                        var_fv1 = 0.0f;
                    }
                    Matrix_RotateY(gGfxMatrix, var_fv1, MTXF_APPLY);
                    Matrix_RotateZ(gGfxMatrix, 30.0f * M_DTOR, MTXF_APPLY);
                    Matrix_Scale(gGfxMatrix, 1.0f, 0.65f, 1.0f, MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    RCP_SetupDL_68();
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
                    gDPSetEnvColor(gMasterDisp++, 0, 255, 0, 0);
                    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                    gSPDisplayList(gMasterDisp++, D_landmaster_3006940);
                }
                break;
            case PLAYERSHOT_ON_FOOT:
            case PLAYERSHOT_7:
                Matrix_Scale(gGfxMatrix, shot->scale, shot->scale, shot->scale, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                RCP_SetupDL(&gMasterDisp, SETUPDL_49);
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
                gDPSetEnvColor(gMasterDisp++, D_800C9C00[shot->sourceId], D_800C9C04[shot->sourceId],
                               D_800C9C08[shot->sourceId], 255);
                if (gLaserStrength[shot->sourceId] != LASERS_SINGLE) {
                    Matrix_RotateZ(gGfxMatrix, gGameFrameCount * 48.0f * M_DTOR, MTXF_APPLY);
                    Matrix_Push(&gGfxMatrix);
                    Matrix_Translate(gGfxMatrix, 0.f, 40.0f, 0.0f, MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_versus_301AEF0);
                    Matrix_Pop(&gGfxMatrix);
                    Matrix_Translate(gGfxMatrix, 0.f, -40.0f, 0.0f, MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_versus_301AEF0);
                } else {
                    gSPDisplayList(gMasterDisp++, D_versus_301AEF0);
                }
                break;
            case PLAYERSHOT_LOCK_ON:
                Matrix_RotateY(gGfxMatrix, M_PI, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                if (gCurrentLevel == LEVEL_AQUAS) {
                    RCP_SetupDL(&gMasterDisp, SETUPDL_60);
                    gSPDisplayList(gMasterDisp++, D_AQ_600DB80);
                    Matrix_Pop(&gGfxMatrix);
                    Matrix_Push(&gGfxMatrix);
                    Matrix_Translate(gGfxMatrix, shot->obj.pos.x, gGroundHeight, shot->obj.pos.z + gPathProgress,
                                     MTXF_APPLY);
                    Matrix_Scale(gGfxMatrix, shot->vec_2C.x, shot->vec_2C.y, shot->vec_2C.z, MTXF_APPLY);
                    RCP_SetupDL(&gMasterDisp, SETUPDL_49);
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 32, 32, 0, shot->unk_58);
                    gDPSetEnvColor(gMasterDisp++, 32, 16, 16, shot->unk_58);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_1024AC0);
                } else if (shot->unk_5C == 0) {
                    if (shot->scale > 1.5f) {
                        break;
                    }
                    Matrix_Pop(&gGfxMatrix);
                    Matrix_Push(&gGfxMatrix);
                    Matrix_Translate(gGfxMatrix, shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z + gPathProgress,
                                     MTXF_APPLY);
                    Matrix_RotateY(gGfxMatrix, -gPlayer[gPlayerNum].camYaw, MTXF_APPLY);
                    Matrix_RotateX(gGfxMatrix, gPlayer[gPlayerNum].camPitch, MTXF_APPLY);
                    Matrix_Push(&gGfxMatrix);
                    Matrix_Scale(gGfxMatrix, 20.0f, 20.0f, 20.0f, MTXF_APPLY);
                    RCP_SetupDL(&gMasterDisp, SETUPDL_49);
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
                    if (gVersusMode) {
                        switch (shot->sourceId) {
                            case 0:
                                gDPSetEnvColor(gMasterDisp++, 255, 255, 32, 255);
                                break;
                            case 1:
                                gDPSetEnvColor(gMasterDisp++, 255, 32, 32, 255);
                                break;
                            case 2:
                                gDPSetEnvColor(gMasterDisp++, 32, 255, 32, 255);
                                break;
                            case 3:
                                gDPSetEnvColor(gMasterDisp++, 32, 32, 255, 255);
                                break;
                        }
                    } else {
                        gDPSetEnvColor(gMasterDisp++, 0, 255, 0, 255);
                    }
                    Matrix_RotateZ(gGfxMatrix, gGameFrameCount * 53.0f * M_DTOR, MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_101C2E0);
                    Matrix_RotateZ(gGfxMatrix, gGameFrameCount * -53.0f * 2.0f * M_DTOR, MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_101C2E0);
                    Matrix_Pop(&gGfxMatrix);
                    if (((gGameFrameCount % 2) == 0)) {
                        Matrix_Scale(gGfxMatrix, 1.7f, 1.7f, 1.7f, MTXF_APPLY);
                    } else {
                        Matrix_Scale(gGfxMatrix, 1.3f, 1.3f, 1.3f, MTXF_APPLY);
                    }
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_1024AC0);
                } else {
                    RCP_SetupDL(&gMasterDisp, SETUPDL_29);
                    gSPDisplayList(gMasterDisp++, D_10231A0);
                    Matrix_Pop(&gGfxMatrix);
                    Matrix_Push(&gGfxMatrix);
                    Matrix_Translate(gGfxMatrix, shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z + gPathProgress,
                                     MTXF_APPLY);
                    Matrix_RotateY(gGfxMatrix, -gPlayer[gPlayerNum].camYaw, MTXF_APPLY);
                    Matrix_RotateX(gGfxMatrix, gPlayer[gPlayerNum].camPitch, MTXF_APPLY);
                    if (((gGameFrameCount % 2) == 0)) {
                        Matrix_Scale(gGfxMatrix, 1.2f, 1.2f, 1.2f, MTXF_APPLY);
                    } else {
                        Matrix_Scale(gGfxMatrix, 1.5f, 1.5f, 1.5f, MTXF_APPLY);
                    }
                    RCP_SetupDL(&gMasterDisp, SETUPDL_49);
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 0, 255);
                    gDPSetEnvColor(gMasterDisp++, 255, 128, 128, 255);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_1024AC0);
                }
                break;
            case PLAYERSHOT_GFOX_LASER:
                Matrix_RotateY(gGfxMatrix, M_PI, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, 3.0f, 3.0f, 20.0f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                RCP_SetupDL_40();
                gSPDisplayList(gMasterDisp++, D_GREAT_FOX_E00DFB0);
                break;
        }
    }
}

void PlayerShot_Draw(PlayerShot* shot) {
    switch (shot->obj.status) {
        case SHOT_ACTIVE:
            PlayerShot_DrawShot(shot);
            break;
        case SHOT_HITMARK:
            PlayerShot_DrawHitmark(shot);
            break;
    }
}

void PlayerShot_UpdateHitmark(PlayerShot* shot) {
    shot->unk_60++;
    if (shot->unk_60 > 2) {
        Object_Kill(&shot->obj, shot->sfxSource);
    }
}

void PlayerShot_UpdateShot2(PlayerShot* shot, Player* player) {
    Vec3f sp5C;
    Vec3f sp50;
    Vec3f sp44;
    Vec3f sp38;

    switch (shot->unk_5C) {
        case 0:
            Matrix_RotateY(gCalcMatrix, (player->yRot_114 + player->rot.y + 180.0f) * M_DTOR, MTXF_NEW);
            Matrix_RotateX(gCalcMatrix, -(player->rot.x * M_DTOR), MTXF_APPLY);
            Matrix_RotateZ(gCalcMatrix, -((player->bankAngle + player->rockAngle) * M_DTOR), MTXF_APPLY);
            Matrix_Translate(gCalcMatrix, player->xShake, player->yBob, 0.0f, MTXF_APPLY);
            sp5C.x = 0.0f;
            sp5C.y = 0.0f;
            sp5C.z = player->baseSpeed + 200.0f;
            Matrix_MultVec3f(gCalcMatrix, &sp5C, &sp50);
            shot->vel.x = sp50.x;
            shot->vel.y = sp50.y;
            shot->vel.z = sp50.z - player->boostSpeed;
            sp5C.x = shot->unk_54;
            sp5C.y = -15.0f;
            sp5C.z = 0.0f;
            Matrix_MultVec3f(gCalcMatrix, &sp5C, &sp44);
            shot->unk_48 = player->pos.x + sp44.x;
            shot->unk_4C = player->pos.y + sp44.y;
            shot->unk_50 = player->trueZpos + sp44.z;
            shot->scale += 200.0f;
            if (shot->scale > 5000.0f) {
                shot->scale = 5000.0f;
            }
            for (sp5C.z = 0.0f; sp5C.z <= shot->scale; sp5C.z += 200.0f) {
                Matrix_MultVec3f(gCalcMatrix, &sp5C, &sp38);
                gShotHitPosZ = shot->obj.pos.z;
                gShotHitPosY = shot->obj.pos.y;
                gShotHitPosX = shot->obj.pos.x;
                shot->obj.pos.x = player->pos.x + sp38.x;
                shot->obj.pos.y = player->pos.y + sp38.y;
                shot->obj.pos.z = player->trueZpos + sp38.z;
                Matrix_Push(&gCalcMatrix);
                PlayerShot_CollisionCheck(shot);
                Matrix_Pop(&gCalcMatrix);
                if (shot->obj.pos.y < gGroundHeight) {
                    shot->unk_5C = 0;
                    PlayerShot_HitGround(shot->obj.pos.x, gGroundHeight + 2.0f, shot->obj.pos.z, shot->obj.rot.y, 2.0f);
                    break;
                } else if (shot->unk_5C == 2) {
                    shot->unk_5C = 0;
                    break;
                }
            }
            shot->timer = 30;
            shot->obj.rot.y = player->rot.y + player->yRot_114;
            if (!(gControllerHold->button & U_CBUTTONS) && !(gControllerHold->button & A_BUTTON)) {
                shot->unk_5C = 1;
            }
            break;
        case 1:
            shot->unk_48 += shot->vel.x;
            shot->unk_4C += shot->vel.y;
            shot->unk_50 += shot->vel.z;
            break;
        case 2:
            shot->obj.pos.x -= shot->vel.x;
            shot->obj.pos.y -= shot->vel.y;
            shot->obj.pos.z -= shot->vel.z;
            shot->unk_48 += shot->vel.x;
            shot->unk_4C += shot->vel.y;
            shot->unk_50 += shot->vel.z;
            if (((gGameFrameCount % 4) == 0)) {
                Play_SpawnHitmark(gShotHitPosX, gShotHitPosY, gShotHitPosZ);
            }
            if ((fabsf(shot->obj.pos.x - shot->unk_48) < 200.0f) && (fabsf(shot->obj.pos.y - shot->unk_4C) < 200.0f) &&
                (fabsf(shot->obj.pos.z - shot->unk_50) < 200.0f)) {
                Object_Kill(&shot->obj, shot->sfxSource);
                return;
            }
            break;
    }
    if (shot->timer == 0) {
        Object_Kill(&shot->obj, shot->sfxSource);
    }
    if (shot->unk_5C == 1) {
        if (shot->obj.pos.y < gGroundHeight) {
            PlayerShot_Impact(shot);
            PlayerShot_HitGround(shot->obj.pos.x, gGroundHeight + 2.0f, shot->obj.pos.z, shot->obj.rot.y, 2.0f);
            if (gCurrentLevel == LEVEL_FORTUNA) {
                func_effect_8007BC7C(shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z, 3.0f);
                func_effect_8007BC7C(shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z, 3.0f);
                func_effect_8007BC7C(shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z, 3.0f);
            }
        }
        PlayerShot_CollisionCheck(shot);
    }
}

void PlayerShot_UpdateBeam(PlayerShot* shot, s32 index) {
    Vec3f sp44;
    Vec3f sp38;

    if ((gGroundSurface == SURFACE_WATER) && (shot->obj.pos.y < (gGroundHeight + 50.0f)) && (index == 0)) {
        func_effect_8007ACE0(shot->obj.pos.x, gGroundHeight, shot->obj.pos.z, 0.1f, 1.5f, shot->obj.rot.y + 20.0f);
        func_effect_8007ACE0(shot->obj.pos.x, gGroundHeight, shot->obj.pos.z, 0.1f, 1.5f, shot->obj.rot.y - 20.0f);
    }
    if ((shot->obj.pos.y < gGroundHeight) && (gGroundType != 4)) {
        PlayerShot_Impact(shot);
        shot->obj.pos.y = gGroundHeight + 2;
        if (gCurrentLevel == LEVEL_BOLSE) {
            func_effect_8007A6F0(&shot->obj.pos, NA_SE_EN_REFLECT);
        }
        if ((gCamCount != 4) && (gCurrentLevel != LEVEL_AQUAS)) {
            if ((shot->sourceId == TEAM_ID_FOX) && (gLaserStrength[0] != LASERS_SINGLE) &&
                (gPlayer[0].form != FORM_LANDMASTER)) {
                Matrix_RotateY(gCalcMatrix, shot->obj.rot.y * M_DTOR, MTXF_NEW);
                Matrix_RotateX(gCalcMatrix, shot->obj.rot.x * M_DTOR, MTXF_APPLY);
                Matrix_RotateZ(gCalcMatrix, shot->obj.rot.z * M_DTOR, MTXF_APPLY);
                sp44.y = sp44.z = 0.0f;
                sp44.x = 40.0f;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp44, &sp38);
                PlayerShot_HitGround(shot->obj.pos.x + sp38.x, gGroundHeight + 2.0f, shot->obj.pos.z + sp38.z,
                                     shot->obj.rot.y, 2.0f);
                sp44.x = -40.0f;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp44, &sp38);
                PlayerShot_HitGround(shot->obj.pos.x + sp38.x, gGroundHeight + 2.0f, shot->obj.pos.z + sp38.z,
                                     shot->obj.rot.y, 2.0f);
            } else {
                PlayerShot_HitGround(shot->obj.pos.x, gGroundHeight + 2.0f, shot->obj.pos.z, shot->obj.rot.y, 2.0f);
            }
        }
        if (gGroundSurface == SURFACE_WATER) {
            Object_Kill(&shot->obj, shot->sfxSource);
            return;
        }
        if (gCurrentLevel == LEVEL_FORTUNA) {
            func_effect_8007BC7C(shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z, 3.0f);
            func_effect_8007BC7C(shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z, 3.0f);
            func_effect_8007BC7C(shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z, 3.0f);
        }
        if (gCurrentLevel == LEVEL_AQUAS) {
            func_effect_8007B8F8(shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z, 3.0f);
            func_effect_8007B8F8(shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z, 3.0f);
            func_effect_8007B8F8(shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z, 3.0f);
            Aquas_801AC8A8(RAND_FLOAT_CENTERED(10.0f) + shot->obj.pos.x, RAND_FLOAT_CENTERED(10.0f) + shot->obj.pos.y,
                           shot->obj.pos.z, 0.8f, 0);
            Aquas_801AC8A8(RAND_FLOAT_CENTERED(10.0f) + shot->obj.pos.x, RAND_FLOAT_CENTERED(10.0f) + shot->obj.pos.y,
                           shot->obj.pos.z, 0.8f, 0);
            Aquas_801AC8A8(RAND_FLOAT_CENTERED(10.0f) + shot->obj.pos.x, RAND_FLOAT_CENTERED(10.0f) + shot->obj.pos.y,
                           shot->obj.pos.z, 0.8f, 0);
        }
    }
    if (shot->timer == 0) {
        Object_Kill(&shot->obj, shot->sfxSource);
        return;
    }
    if ((shot->sourceId < NPC_SHOT_ID + AI360_10) || ((shot->timer % 2) != 0)) {
        PlayerShot_CollisionCheck(shot);
    }
}

void PlayerShot_UpdateTank(PlayerShot* shot) {
    PlayerShot_UpdateBeam(shot, 0);
}

void PlayerShot_UpdateOnFoot(PlayerShot* shot) {
    PlayerShot_UpdateBeam(shot, 0);
    shot->unk_58 = 0;
}

void PlayerShot_UpdateShot7(PlayerShot* shot) {
    Vec3f sp3C;
    Vec3f sp30;
    Vec3f sp24;

    PlayerShot_UpdateBeam(shot, 0);
    sp3C.x = shot->obj.pos.x;
    sp3C.y = shot->obj.pos.y;
    sp3C.z = shot->obj.pos.z;
    sp30.x = 0.0f;
    sp30.y = 0.0f;
    sp30.z = 0.0f;
    if (!func_col2_800A3690(&sp3C, &sp30, COL2_5, &sp24)) {
        PlayerShot_Impact(shot);
    }
    shot->unk_58 = 0;
}

bool PlayerShot_FindLockTarget(PlayerShot* shot) {
    s32 i;
    s32 j;
    f32 lockRange;
    Actor* actor;
    Player* player;

    if (gLevelMode == LEVELMODE_ON_RAILS) {
        lockRange = 300.0f;
    } else {
        lockRange = 200.0f;
    }
    for (i = 0, actor = gActors; i < ARRAY_COUNT(gActors); i++, actor++) {
        if ((actor->obj.status == OBJ_ACTIVE) && (actor->info.targetOffset != 0.0f) &&
            ((actor->lockOnTimers[shot->sourceId] == 0) && (fabsf(shot->obj.pos.x - actor->obj.pos.x) <= lockRange) &&
             (fabsf(shot->obj.pos.y - (actor->obj.pos.y + actor->info.targetOffset)) <= lockRange) &&
             (fabsf(shot->obj.pos.z - actor->obj.pos.z) <= lockRange))) {
            actor->lockOnTimers[shot->sourceId] = 20;
            Object_PlayerSfx(gPlayer[shot->sourceId].sfxSource, NA_SE_LOCK_ON, shot->sourceId);
            for (j = 0; j < ARRAY_COUNT(gPlayerShots); j++) {
                if (gPlayerShots[j].obj.id == PLAYERSHOT_LOCK_SEARCH) {
                    Object_Kill(&gPlayerShots[j].obj, gPlayerShots[j].sfxSource);
                }
            }
            D_display_801615B8[shot->sourceId] = 3.0f;
            D_display_801615A8[shot->sourceId] = 300.0f;
            return true;
        }
    }
    if (gVersusMode) {
        for (i = 0, player = gPlayer; i < gCamCount; i++, player++) {
            if ((player->state_1C8 == PLAYERSTATE_1C8_ACTIVE) && !player->somersault &&
                (player->form != FORM_ON_FOOT) && (i != shot->sourceId) && (gVsLockOnTimers[i][shot->sourceId] == 0) &&
                (fabsf(shot->obj.pos.x - player->pos.x) <= lockRange) &&
                (fabsf(shot->obj.pos.y - player->pos.y) <= lockRange) &&
                (fabsf(shot->obj.pos.z - player->trueZpos) <= lockRange)) {
                gVsLockOnTimers[0][shot->sourceId] = gVsLockOnTimers[1][shot->sourceId] =
                    gVsLockOnTimers[2][shot->sourceId] = gVsLockOnTimers[3][shot->sourceId] = 0;
                gVsLockOnTimers[i][shot->sourceId] = 20;
                Object_PlayerSfx(gPlayer[shot->sourceId].sfxSource, NA_SE_LOCK_ON, shot->sourceId);
                for (j = 0; j < ARRAY_COUNT(gPlayerShots); j++) {
                    if (gPlayerShots[j].obj.id == PLAYERSHOT_LOCK_SEARCH) {
                        Object_Kill(&gPlayerShots[j].obj, gPlayerShots[j].sfxSource);
                    }
                }
                D_display_801615B8[shot->sourceId] = 3.0f;
                D_display_801615A8[shot->sourceId] = 300.0f;
                return true;
            }
        }
    }
    return false;
}

void PlayerShot_SearchLockOnTarget(PlayerShot* shot) {
    if (gVersusMode) {
        if ((shot->obj.pos.y < gGroundHeight) || PlayerShot_FindLockTarget(shot) ||
            !(gControllerHold[shot->sourceId].button & A_BUTTON) || (shot->timer == 0)) {
            Object_Kill(&shot->obj, shot->sfxSource);
        }
    } else {
        if ((shot->obj.pos.y < gGroundHeight) || PlayerShot_FindLockTarget(shot) ||
            !(gControllerHold[gMainController].button & A_BUTTON) || (shot->timer == 0)) {
            Object_Kill(&shot->obj, shot->sfxSource);
        }
    }
    PlayerShot_CollisionCheck(shot);
}

void PlayerShot_CheckBossHitbox(PlayerShot* shot) {
    s32 i;
    s32 j;
    f32* hitboxData;
    Boss* boss;
    Vec3f test;
    f32 var_fs2;
    Vec3f sp8C;
    Vec3f sp80;
    s32 var_s6;
    s32 count;

    boss = gBosses;
    for (i = 0; i < ARRAY_COUNT(gBosses); i++, boss++) {
        if ((boss->obj.status == OBJ_ACTIVE) && (boss->timer_05A == 0)) {
            if (boss->obj.id == OBJ_BOSS_KA) {
                var_s6 = gGameFrameCount % 8U;
                var_fs2 = shot->scale * 40.0f;
            } else {
                var_s6 = gGameFrameCount % 16U;
                var_fs2 = shot->scale * 30.0f;
            }
            hitboxData = boss->info.hitbox;
            count = *hitboxData++;
            if (count != 0) {
                for (j = 0; j < count; j++, hitboxData += 6) {
                    if (hitboxData[0] == HITBOX_ROTATED) {
                        Matrix_RotateZ(gCalcMatrix, -hitboxData[3] * M_DTOR, MTXF_NEW);
                        Matrix_RotateX(gCalcMatrix, -hitboxData[1] * M_DTOR, MTXF_APPLY);
                        Matrix_RotateY(gCalcMatrix, -hitboxData[2] * M_DTOR, MTXF_APPLY);
                        Matrix_RotateZ(gCalcMatrix, -boss->obj.rot.z * M_DTOR, MTXF_APPLY);
                        Matrix_RotateX(gCalcMatrix, -boss->obj.rot.x * M_DTOR, MTXF_APPLY);
                        Matrix_RotateY(gCalcMatrix, -boss->obj.rot.y * M_DTOR, MTXF_APPLY);
                        hitboxData += 4;
                    } else {
                        Matrix_RotateZ(gCalcMatrix, -boss->obj.rot.z * M_DTOR, MTXF_NEW);
                        Matrix_RotateX(gCalcMatrix, -boss->obj.rot.x * M_DTOR, MTXF_APPLY);
                        Matrix_RotateY(gCalcMatrix, -boss->obj.rot.y * M_DTOR, MTXF_APPLY);
                    }
                    if ((j == var_s6) && (hitboxData[1] > -100.0f) && (hitboxData[3] > -100.0f)) {
                        sp8C.x = shot->obj.pos.x - boss->obj.pos.x;
                        sp8C.y = shot->obj.pos.y - boss->obj.pos.y;
                        sp8C.z = shot->obj.pos.z - boss->obj.pos.z;
                        Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp8C, &sp80);
                        test.x = (hitboxData[4] + boss->obj.pos.x) - (boss->obj.pos.x + sp80.x);
                        test.y = (hitboxData[2] + boss->obj.pos.y) - (boss->obj.pos.y + sp80.y);
                        test.z = (hitboxData[0] + boss->obj.pos.z) - (boss->obj.pos.z + sp80.z);
                        if ((gLevelMode == LEVELMODE_ON_RAILS) && (test.z < 0.0f)) {
                            test.z *= 0.6f;
                        }
                        if (VEC3F_MAG(&test) < var_fs2) {
                            boss->dmgPart = j;
                            boss->dmgType = DMG_BOMB;
                            boss->damage = 20;
                        }
                    }
                }
            }
        }
    }
}

void PlayerShot_SetBombLight(PlayerShot* shot) {
    static u8 sPlayerReds[4] = { 255, 255, 32, 32 };
    static u8 sPlayerGreens[4] = { 255, 32, 255, 32 };
    static u8 sPlayerBlues[4] = { 32, 32, 32, 255 };
    f32 brightness;

    gLight3x = shot->obj.pos.x;
    gLight3y = shot->obj.pos.y;
    gLight3z = shot->obj.pos.z;
    if (gVersusMode) {
        gLight3R = sPlayerReds[shot->sourceId];
        gLight3G = sPlayerGreens[shot->sourceId];
        gLight3B = sPlayerBlues[shot->sourceId];
    } else {
        gLight3R = 90;
        gLight3G = 90;
        gLight3B = 255;
    }
    brightness = 0.7f;
    if (shot->unk_5C != 0) {
        brightness = 1.0f;
    }
    Math_SmoothStepToF(&gLight3Brightness, brightness, 1.0f, 0.08f, 0.001f);
}

void PlayerShot_ApplyExplosionDamage(PlayerShot* shot, s32 damage) {
    s32 i;
    f32 dx;
    f32 dy;
    f32 dz;
    s32 pad[2];
    Actor* actor;
    Sprite* sprite;
    Scenery* scenery;
    Effect* effect;
    Player* player;
    f32 radius = shot->scale * 60.0f;

    scenery = gScenery;
    for (i = 0; i < ARRAY_COUNT(gScenery); i++, scenery++) {
        if ((scenery->obj.status == OBJ_ACTIVE) && (scenery->obj.id == OBJ_SCENERY_56)) {
            dx = scenery->obj.pos.x - shot->obj.pos.x;
            dy = scenery->obj.pos.y - shot->obj.pos.y;
            dz = scenery->obj.pos.z - shot->obj.pos.z;
            if (sqrtf(SQ(dx) + SQ(dy) + SQ(dz)) < radius) {
                scenery->dmgType = DMG_EXPLOSION;
            }
            scenery->dmgPart = 0;
        }
    }
    sprite = gSprites;
    for (i = 0; i < ARRAY_COUNT(gSprites); i++, sprite++) {
        if ((sprite->obj.status == OBJ_ACTIVE) &&
            ((sprite->obj.id == OBJ_SPRITE_FO_POLE) || (sprite->obj.id == OBJ_SPRITE_TI_CACTUS) ||
             (sprite->obj.id == OBJ_SPRITE_CO_POLE) || (sprite->obj.id == OBJ_SPRITE_CO_TREE))) {
            dx = sprite->obj.pos.x - shot->obj.pos.x;
            dy = sprite->obj.pos.y - shot->obj.pos.y;
            dz = sprite->obj.pos.z - shot->obj.pos.z;
            if (sqrtf(SQ(dx) + SQ(dy) + SQ(dz)) < radius) {
                sprite->destroy = 1;
            }
        }
    }
    actor = gActors;
    for (i = 0; i < ARRAY_COUNT(gActors); i++, actor++) {
        if ((actor->obj.status == OBJ_ACTIVE) && (actor->timer_0C2 == 0) &&
            !((gCurrentLevel == LEVEL_MACBETH) && (OBJ_ACTOR_205 <= actor->obj.id) &&
              (actor->obj.id < OBJ_ACTOR_214)) &&
            !((actor->obj.id == OBJ_ACTOR_EVENT) && (actor->iwork[12] != 0)) &&
            ((actor->scale >= 0.0f) || (actor->obj.id == OBJ_ACTOR_271))) {
            dx = actor->obj.pos.x - shot->obj.pos.x;
            dy = actor->obj.pos.y - shot->obj.pos.y;
            dz = actor->obj.pos.z - shot->obj.pos.z;
            if ((gLevelMode == LEVELMODE_ON_RAILS) && (dz < 0.0f)) {
                dz *= 0.6f;
            }
            actor->hitPos.x = shot->obj.pos.x;
            actor->hitPos.y = shot->obj.pos.y;
            actor->hitPos.z = shot->obj.pos.z;
            if (sqrtf(SQ(dx) + SQ(dy) + SQ(dz)) < radius) {
                if ((actor->obj.id == OBJ_ACTOR_193) || (actor->obj.id == OBJ_ACTOR_186) ||
                    (actor->obj.id == OBJ_ACTOR_190) || (actor->obj.id == OBJ_ACTOR_202) ||
                    (actor->obj.id == OBJ_ACTOR_201) || (actor->obj.id == OBJ_ACTOR_187) ||
                    ((actor->obj.id == OBJ_ACTOR_EVENT) && (actor->eventType == EVID_SUPPLY_CRATE)) ||
                    ((actor->obj.id == OBJ_ACTOR_EVENT) && (actor->eventType == EVID_SX_WARP_GATE)) ||
                    (actor->obj.id == OBJ_ACTOR_196)) {
                    actor->dmgType = DMG_EXPLOSION;
                    actor->dmgPart = 0;
                    actor->dmgSource = shot->sourceId + 1;
                    actor->damage = damage;

                    if (actor->info.bonus != 0) {
                        shot->bonus++;
                    }
                } else if ((actor->obj.id == OBJ_ACTOR_EVENT) && (actor->scale >= 0.5f) && (damage > 30)) {
                    actor->dmgSource = shot->sourceId + 1;
                    actor->vel.x = dx * 0.03f;
                    actor->vel.y = dy * 0.03f;
                    actor->vel.z = dz * 0.03f;
                    actor->obj.status = OBJ_DYING;
                    actor->timer_0BC = RAND_INT(15.0f) + 10;
                    actor->timer_0BE = 0;
                    actor->timer_04C = 4;
                    actor->obj.rot.x = Math_ModF(actor->obj.rot.x, 360.0f);
                    if (actor->info.bonus != 0) {
                        shot->bonus++;
                    }
                } else {
                    actor->dmgType = DMG_EXPLOSION;
                    actor->dmgPart = 0;
                    actor->dmgSource = shot->sourceId + 1;
                    actor->damage = damage;
                    if (actor->info.bonus != 0) {
                        shot->bonus++;
                    }
                }
            }
        }
    }
    if (gCurrentLevel == LEVEL_MACBETH) {
        Macbeth_801AD144(shot);
    } else if (gCurrentLevel == LEVEL_VENOM_1) {
        Venom1_8019864C(shot);
    } else {
        PlayerShot_CheckBossHitbox(shot);
    }
    effect = gEffects;
    for (i = 0; i < ARRAY_COUNT(gEffects); i++, effect++) {
        if (effect->obj.status == OBJ_ACTIVE) {
            dx = effect->obj.pos.x - shot->obj.pos.x;
            dy = effect->obj.pos.y - shot->obj.pos.y;
            dz = effect->obj.pos.z - shot->obj.pos.z;
            if (sqrtf(SQ(dx) + SQ(dy) + SQ(dz)) < radius) {
                if (effect->info.unk_16 == 0) {
                    Object_Kill(&effect->obj, effect->sfxSource);
                }
                if (effect->info.unk_16 == 2) {
                    effect->obj.pos.x += dx * 0.03f;
                    if (!((gLevelType == LEVELTYPE_PLANET) && (effect->obj.pos.y < 100.0f))) {
                        effect->obj.pos.y += dy * 0.03f;
                    }
                    effect->obj.pos.z += dz * 0.03f;
                    if ((effect->obj.id == OBJ_EFFECT_392) && (effect->state == 0)) {
                        effect->state = 1;
                        effect->unk_44 = 176;
                        effect->unk_4C = 0;
                        effect->vel.x = effect->vel.y = effect->vel.z = 0.0f;
                        effect->scale2 = 20.0f;
                    }
                }
            }
        }
    }
    if (gVersusMode) {
        player = gPlayer;
        for (i = 0; i < gCamCount; i++, player++) {
            if ((i != shot->sourceId) && (player->state_1C8 == PLAYERSTATE_1C8_ACTIVE) && (player->hitTimer == 0)) {
                dx = player->pos.x - shot->obj.pos.x;
                dy = player->pos.y - shot->obj.pos.y;
                dz = player->trueZpos - shot->obj.pos.z;
                if (sqrtf(SQ(dx) + SQ(dy) + SQ(dz)) < radius) {
                    player->attacker = shot->sourceId + 1;
                    switch (player->form) {
                        case FORM_ARWING:
                            Player_ApplyDamage(player, 0, 80);
                            break;
                        case FORM_LANDMASTER:
                            Player_ApplyDamage(player, 0, 60);
                            break;
                        case FORM_ON_FOOT:
                            Player_ApplyDamage(player, 0, 180);
                            break;
                    }
                }
            }
        }
    }
}

void PlayerShot_UpdateBomb(PlayerShot* shot) {
    Vec3f test;
    f32 var_ft5;

    switch (shot->unk_5C) {
        case 0:
            if (shot->timer == 0) {
                PlayerShot_ExplodeBomb(shot);
                break;
            }
            if ((shot->obj.pos.y < gGroundHeight) && (gGroundType != 4)) {
                PlayerShot_ExplodeBomb(shot);
                break;
            }
            if ((gPlayer[shot->sourceId].form == FORM_LANDMASTER) || (gPlayer[shot->sourceId].form == FORM_ON_FOOT)) {
                shot->vel.y -= 1.0f;
                Math_SmoothStepToF(&shot->obj.rot.x, -90.0f, 0.05f, 1.0f, 0.0f);
            }
            if (shot->timer < 25) {
                if (gVersusMode) {
                    if (gControllerPress[shot->sourceId].button & gBombButton[shot->sourceId]) {
                        PlayerShot_ExplodeBomb(shot);
                        break;
                    }
                } else {
                    if (gControllerPress[gMainController].button & gBombButton[shot->sourceId]) {
                        PlayerShot_ExplodeBomb(shot);
                        break;
                    }
                }
            }
            if (!((gCurrentLevel == LEVEL_VENOM_ANDROSS) && (gBosses[0].obj.status == OBJ_ACTIVE) &&
                  (gBosses[0].state == 17))) {
                PlayerShot_CollisionCheck(shot);
            }
            PlayerShot_SetBombLight(shot);
            break;
        case 1:
            gGroundClipMode = 2;
            shot->obj.rot.y += 1.0f;
            Math_SmoothStepToF(&shot->scale, shot->unk_48, 0.05f, 1.5f, 0.001f);
            if ((shot->timer > 0) && (shot->timer < 30)) {
                if (!gVersusMode && ((gPlayer[0].state_1C8 == PLAYERSTATE_1C8_ACTIVE) ||
                                     (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_U_TURN))) {
                    test.x = gPlayer[0].pos.x - shot->obj.pos.x;
                    test.y = gPlayer[0].pos.y - shot->obj.pos.y;
                    test.z = gPlayer[0].trueZpos - shot->obj.pos.z;
                    var_ft5 = VEC3F_MAG(&test) * 0.01f;
                    if (var_ft5 > 60.0f) {
                        var_ft5 = 60.0f;
                    }
                    var_ft5 = 60.0f - var_ft5;
                    Math_SmoothStepToF(&D_ctx_801779A8[gMainController], var_ft5 + 5.0f, 1.0f, 3.0f, 0.0f);
                }
                PlayerShot_SetBombLight(shot);
            }
            if (shot->timer == 0) {
                shot->unk_58 -= 8;
                if (shot->unk_58 < 0) {
                    shot->unk_58 = 0;
                    Object_Kill(&shot->obj, shot->sfxSource);
                    gGroundClipMode = 0;
                }
            }
            PlayerShot_ApplyExplosionDamage(shot, 50);
            break;
    }
}

static Vec3f sLockOnPos = { 0.0f, 0.0f, 0.0f };
void PlayerShot_UpdateLockOnShot(PlayerShot* shot) {
    s32 i;
    s32 var_a3;
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    Actor* actor;
    Player* player;

    if ((shot->obj.pos.y < gGroundHeight) || (shot->timer == 1)) {
        if ((gGroundSurface == SURFACE_WATER) && (shot->obj.pos.y < gGroundHeight)) {
            shot->unk_48 = 10.0f;
            func_effect_8007D9DC(shot->obj.pos.x, gGroundHeight + 2.0f, shot->obj.pos.z, shot->unk_48 * 0.1f,
                                 shot->unk_48 * 3.0f, 0);
            func_effect_8007D9DC(shot->obj.pos.x, gGroundHeight + 2.0f, shot->obj.pos.z, shot->unk_48 * 0.1f,
                                 shot->unk_48 * 3.0f, 5);
            func_effect_8007ADF4(shot->obj.pos.x, gGroundHeight, shot->obj.pos.z, shot->unk_48 * 0.05f,
                                 shot->unk_48 * 0.5f);
            func_effect_8007A6F0(&shot->obj.pos, NA_SE_OB_WATER_BOUND_M);
        }
        PlayerShot_Impact(shot);
    } else {
        var_a3 = 0;
        if (shot->unk_60 == 0) {
            for (i = 0, actor = gActors; i < ARRAY_COUNT(gActors); i++, actor++) {
                if ((actor->obj.status == OBJ_ACTIVE) && (actor->info.targetOffset != 0.0f) &&
                    (actor->lockOnTimers[shot->sourceId] != 0)) {
                    var_a3 = 1;
                    actor->lockOnTimers[shot->sourceId] = 2;
                    sLockOnPos = actor->obj.pos;
                    sLockOnPos.y += actor->info.targetOffset;
                }
            }
            for (i = 0, player = gPlayer; i < gCamCount; i++, player++) {
                if (((player->state_1C8 == PLAYERSTATE_1C8_ACTIVE) || (player->state_1C8 == PLAYERSTATE_1C8_U_TURN)) &&
                    (gVsLockOnTimers[i][shot->sourceId] != 0)) {
                    var_a3 = 1;
                    gVsLockOnTimers[i][shot->sourceId] = 2;
                    sLockOnPos.x = player->pos.x;
                    if (player->form == FORM_ARWING) {
                        sLockOnPos.y = player->pos.y;
                    } else {
                        sLockOnPos.y = player->pos.y + 30.0f;
                    }
                    sLockOnPos.z = player->trueZpos;
                }
            }
            if (var_a3 != 0) {
                sp6C = shot->obj.pos.x - sLockOnPos.x;
                sp68 = shot->obj.pos.y - sLockOnPos.y;
                sp64 = shot->obj.pos.z - sLockOnPos.z;
                sp58 = Math_RadToDeg(Math_Atan2F(sp6C, sp64));
                sp5C = Math_RadToDeg(-Math_Atan2F(sp68, sqrtf(SQ(sp6C) + SQ(sp64))));
                if (shot->vec_2C.y >= 360.0f) {
                    shot->vec_2C.y -= 360.0f;
                }
                if (shot->vec_2C.y < 0.0f) {
                    shot->vec_2C.y += 360.0f;
                }
                if (shot->vec_2C.x >= 360.0f) {
                    shot->vec_2C.x -= 360.0f;
                }
                if (shot->vec_2C.x < 0.0f) {
                    shot->vec_2C.x += 360.0f;
                }
                Math_SmoothStepToAngle(&shot->vec_2C.y, sp58, 1.0f, shot->unk_50, 0.0f);
                Math_SmoothStepToAngle(&shot->vec_2C.x, sp5C, 1.0f, shot->unk_50, 0.0f);
                shot->timer = 30;
            } else {
                shot->unk_60 = 1;
            }
        }
        Math_SmoothStepToF(&shot->unk_50, 360.0f, 1.0f, 3.0f, 0.f);
        if (shot->unk_60 != 0) {
            Math_SmoothStepToF(&shot->unk_54, 169.0f, 1.0f, 13.0f, 0.f);
        } else {
            Math_SmoothStepToF(&shot->unk_54, 91.0f, 1.0f, 7.7999997f, 0.f);
        }
        if (!((gPlayer[shot->sourceId].form == FORM_LANDMASTER) && (shot->unk_60 != 0))) {
            Vec3f sp44;
            Vec3f sp38;

            shot->obj.rot.y = shot->vec_2C.y;
            shot->obj.rot.x = shot->vec_2C.x;
            Matrix_RotateY(gCalcMatrix, shot->obj.rot.y * M_DTOR, MTXF_NEW);
            Matrix_RotateX(gCalcMatrix, shot->obj.rot.x * M_DTOR, MTXF_APPLY);
            sp44.x = sp44.y = 0.0f;
            sp44.z = -(shot->unk_54 + 40.0f);
            Matrix_MultVec3f(gCalcMatrix, &sp44, &sp38);
            shot->vel.x = sp38.x;
            shot->vel.y = sp38.y;
            shot->vel.z = sp38.z;
        }
        PlayerShot_CollisionCheck(shot);
        gLight3x = shot->obj.pos.x;
        gLight3y = shot->obj.pos.y;
        gLight3z = shot->obj.pos.z;
        gLight3R = 90;
        gLight3G = 180;
        gLight3B = 90;
        Math_SmoothStepToF(&gLight3Brightness, 0.6f, 1.0f, 0.08f, 0.001f);
    }
}

void PlayerShot_UpdateShot(PlayerShot* shot, s32 index) {
    s32 teamId;
    s32 bonus;

    shot->obj.pos.x += shot->vel.x;
    shot->obj.pos.y += shot->vel.y;
    shot->obj.pos.z += shot->vel.z;
    switch (shot->obj.id) {
        case PLAYERSHOT_SINGLE_LASER:
            PlayerShot_UpdateBeam(shot, index);
            break;
        case PLAYERSHOT_TWIN_LASER:
        case PLAYERSHOT_GFOX_LASER:
            PlayerShot_UpdateBeam(shot, index);
            break;
        case PLAYERSHOT_2:
            PlayerShot_UpdateShot2(shot, &gPlayer[shot->sourceId]);
            break;
        case PLAYERSHOT_BOMB:
            PlayerShot_UpdateBomb(shot);
            break;
        case PLAYERSHOT_LOCK_SEARCH:
            PlayerShot_SearchLockOnTarget(shot);
            break;
        case PLAYERSHOT_TANK:
            PlayerShot_UpdateTank(shot);
            break;
        case PLAYERSHOT_ON_FOOT:
            PlayerShot_UpdateOnFoot(shot);
            break;
        case PLAYERSHOT_7:
            PlayerShot_UpdateShot7(shot);
            break;
        case PLAYERSHOT_LOCK_ON:
            if (shot->scale > 1.5f) {
                PlayerShot_ApplyExplosionDamage(shot, 30);
                if (shot->bonus != 0) {
                    if (gVersusMode) {
                        gPlayerScores[shot->sourceId] += shot->bonus;
                    } else {
                        bonus = shot->bonus;
                        if (shot->bonus > 10) {
                            bonus = BONUS_TEXT_GREAT;
                        }
                        BonusText_Display(shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z, bonus);
                        gHitCount += shot->bonus;
                    }
                    if ((shot->bonus >= 7) && !gBossActive && (gLevelMode == LEVELMODE_ON_RAILS) &&
                        ((gTeamShields[TEAM_ID_FALCO] > 0) || (gTeamShields[TEAM_ID_SLIPPY] > 0) ||
                         (gTeamShields[TEAM_ID_PEPPY] > 0))) {
                        do {
                            teamId = RAND_INT(2.9f) + 1;
                        } while (gTeamShields[teamId] <= 0);
                        switch (teamId) {
                            case TEAM_ID_FALCO:
                                Radio_PlayMessage(gMsg_ID_7100, RCID_FALCO);
                                break;
                            case TEAM_ID_SLIPPY:
                                Radio_PlayMessage(gMsg_ID_15252, RCID_SLIPPY);
                                break;
                            case TEAM_ID_PEPPY:
                                Radio_PlayMessage(gMsg_ID_17160, RCID_PEPPY);
                                break;
                        }
                    }
                }
                Object_Kill(&shot->obj, shot->sfxSource);
                func_effect_8007A6F0(&shot->obj.pos, NA_SE_SPREAD_EXPLOSION);
            } else if (gCurrentLevel == LEVEL_AQUAS) {
                Aquas_801ABA40(shot);
            } else {
                PlayerShot_UpdateLockOnShot(shot);
            }
            break;
    }
}

void PlayerShot_Update(PlayerShot* shot) {
    s32 i;
    s32 ticks;

    switch (shot->obj.status) {
        case SHOT_FREE:
            break;
        case SHOT_ACTIVE:
            ticks = 1;
            switch (shot->obj.id) {
                case PLAYERSHOT_GFOX_LASER:
                    ticks = 4;
                    break;
                case PLAYERSHOT_SINGLE_LASER:
                case PLAYERSHOT_TWIN_LASER:
                    if ((shot->unk_58 == 0) || (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_LEVEL_INTRO)) {
                        ticks = 4;
                    } else {
                        ticks = 3;
                    }
                    break;
                case PLAYERSHOT_TANK:
                    ticks = 2;
                    break;
            }
            for (i = 0; i < ticks && (shot->obj.status == SHOT_ACTIVE); i++) {
                if (shot->timer > 0) {
                    shot->timer--;
                }
                gShotHitPosZ = shot->obj.pos.z;
                gShotHitPosY = shot->obj.pos.y;
                gShotHitPosX = shot->obj.pos.x;
                PlayerShot_UpdateShot(shot, i);
            }
            break;
        case SHOT_HITMARK:
            PlayerShot_UpdateHitmark(shot);
            break;
    }
}

void PlayerShot_UpdateAll(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gPlayerShots); i++) {
        gPlayerShots[i].index = i;
        PlayerShot_Update(&gPlayerShots[i]);
    }
}

void PlayerShot_DrawAll(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gPlayerShots); i++) {
        gPlayerShots[i].index = i;
        if (gPlayerShots[i].obj.status != SHOT_FREE) {
            if (!((gReflectY < 0) && (gPlayerShots[i].obj.rot.x < -10.0f))) {
                Matrix_Push(&gGfxMatrix);
                PlayerShot_Draw(&gPlayerShots[i]);
                Matrix_Pop(&gGfxMatrix);
            }
            if (gReflectY > 0) {
                Object_SetSfxSourceToView(gPlayerShots[i].sfxSource, &sShotViewPos);
            }
        }
    }
}
