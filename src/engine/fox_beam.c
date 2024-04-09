#include "global.h"
#include "assets/ast_landmaster.h"
#include "assets/ast_aquas.h"
#include "assets/ast_great_fox.h"
#include "assets/ast_versus.h"

static Vec3f D_beam_8015F950;

void func_beam_80035D30(Effect* effect, f32 xPos, f32 yPos, f32 zPos) {
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

void func_beam_80035DEC(f32 xPos, f32 yPos, f32 zPos) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            func_beam_80035D30(&gEffects[i], xPos, yPos, zPos);
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

void func_beam_80035E78(PlayerShot* shot) {
    f32 var_fs0;
    f32 var_fv0;
    f32 var_fv1;
    s32 var_v0;

    if (shot->unk_5C == 0) {
        shot->vel.x = shot->vel.y = shot->vel.z = shot->obj.rot.x = shot->obj.rot.y = shot->obj.rot.z = 0.0f;
        shot->unk_44 = 1.0f;
        shot->unk_5C = 1;
        shot->unk_64 = 30;
        shot->unk_58 = 150;
        func_8001CE28(shot->playerNum, shot->sfxSource);
        gScreenFlashTimer = 4;
        if (shot->obj.pos.y < (gGroundLevel + 450.0f)) {
            gCameraShake = 15;
            if (gGroundType == GROUNDTYPE_WATER) {
                func_effect_8007D9DC(shot->obj.pos.x, gGroundLevel + 2.0f, shot->obj.pos.z, shot->unk_48 * 0.1f,
                                     shot->unk_48 * 3.0f, 0);
                func_effect_8007D9DC(shot->obj.pos.x, gGroundLevel + 2.0f, shot->obj.pos.z, shot->unk_48 * 0.1f,
                                     shot->unk_48 * 3.0f, 5);
                func_effect_8007D9DC(shot->obj.pos.x, gGroundLevel + 2.0f, shot->obj.pos.z, shot->unk_48 * 0.1f,
                                     shot->unk_48 * 3.0f, 10);
                func_effect_8007ADF4(shot->obj.pos.x, gGroundLevel, shot->obj.pos.z, shot->unk_48 * 0.05f,
                                     shot->unk_48 * 0.5f);
                func_effect_8007A6F0(&shot->obj.pos, 0x19000014);
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
            func_effect_8007B550(shot->obj.pos.x, gGroundLevel + 6.0f, shot->obj.pos.z, shot->unk_48 * (1.5f + var_fv1),
                                 var_fv0);
        }

        if (gVersusMode) {
            var_v0 = shot->playerNum + 10;
        } else {
            var_v0 = 0;
        }
        func_effect_8007B344(shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z, shot->unk_48 * 1.5f, var_v0);
        if (D_ctx_80178294 != 0) {
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

void func_beam_80036318(PlayerShot* shot) {
    s32 var_v0_2;
    s32 i;

    if (shot->obj.id == PLAYERSHOT_4) {
        Object_Kill(&shot->obj, shot->sfxSource);
        return;
    }
    shot->obj.pos.z = D_ctx_80178498; // strange order on the globals
    shot->obj.pos.y = D_ctx_801784A0;
    shot->obj.pos.x = D_ctx_8017849C;
    if ((shot->obj.id == PLAYERSHOT_3) ||
        ((gCurrentLevel != LEVEL_AQUAS) && (shot->obj.id == PLAYERSHOT_8) && (shot->unk_5C != 0))) {
        if (shot->obj.id == PLAYERSHOT_8) {
            shot->obj.id = PLAYERSHOT_3;
            shot->unk_5C = 0;
        }
        func_beam_80035E78(shot);
    } else if (shot->obj.id == PLAYERSHOT_8) {
        shot->unk_44 = 7.5f;
        for (i = 0; i < ARRAY_COUNT(gActors); i++) {
            gActors[i].timer_0CA[shot->playerNum] = 0;
        }
        shot->vel.x = shot->vel.y = shot->vel.z = 0.0f;
        if (gCurrentLevel == LEVEL_AQUAS) {
            D_ctx_80178360 = D_ctx_80178364 = D_ctx_80178368 = 0;
            func_effect_8007B344(shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z, 10.0f, 4);
            func_effect_8007C120(shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z, 0.0f, 0.0f, 0.0f, 0.3f, 30);
        } else {

            if (gVersusMode) {
                var_v0_2 = shot->playerNum + 10;
            } else {
                var_v0_2 = 12;
            }
            func_effect_8007B344(shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z, 10.0f, var_v0_2);
            func_effect_8007D2C8(shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z, 4.0f);
        }
    } else {
        shot->obj.status = 2;
        shot->unk_60 = 0;
    }
}

void func_beam_80036528(Effect* effect, f32 xPos, f32 yPos, f32 zPos, f32 yRot, f32 xRot, f32 scale, s32 unk44,
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
    func_play_800A6070(effect->sfxSource, 0x29000000);
}

void func_beam_800365E4(f32 xPos, f32 yPos, f32 zPos, f32 arg3, f32 arg4, f32 arg5, f32 yRot, f32 xRot, f32 scale,
                        s32 unk44, s32 time) {
    s32 i;

    if ((D_ctx_801784AC != 4) && (gLevelType == LEVELTYPE_PLANET) && (gGroundType != GROUNDTYPE_WATER) &&
        (gCurrentLevel != LEVEL_SOLAR) && (gCurrentLevel != LEVEL_BOLSE) && (gCurrentLevel != LEVEL_TRAINING) &&
        (gCurrentLevel != LEVEL_ZONESS)) {
        for (i = 0; i < 50; i++) {
            if (gEffects[i].obj.status == OBJ_FREE) {
                func_beam_80036528(&gEffects[i], xPos, yPos, zPos, yRot, xRot, scale, unk44, time);
                break;
            }
        }
    }
}

void func_beam_800366CC(Effect* effect, f32 xPos, f32 yPos, f32 zPos, f32 yRot, f32 scale) {
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
    func_play_800A6070(effect->sfxSource, 0x29000000);
}

void func_beam_80036770(f32 xPos, f32 yPos, f32 zPos, f32 yRot, f32 scale) {
    s32 i;

    if ((D_ctx_801784AC != 4) && (gLevelType == LEVELTYPE_PLANET) && (gGroundType <= GROUNDTYPE_GRASS) &&
        (gCurrentLevel != LEVEL_TRAINING) && (gCurrentLevel != LEVEL_SOLAR) && (gCurrentLevel != LEVEL_ZONESS)) {
        for (i = 0; i < 50; i++) {
            if (gEffects[i].obj.status == OBJ_FREE) {
                func_beam_800366CC(&gEffects[i], xPos, yPos, zPos, yRot, scale);
                func_effect_8007D10C(xPos, yPos, zPos, 2.0f);
                break;
            }
        }
    }
    if (gCurrentLevel == LEVEL_BOLSE) {
        func_effect_8007D10C(xPos, yPos, zPos, 2.0f);
    }
}

s32 func_beam_80036874(PlayerShot* shot, f32* hitboxData, Object* obj) {
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
            if ((shot->playerNum < 4) &&
                ((gLaserStrength[shot->playerNum] != LASERS_SINGLE) || (shot->obj.id == PLAYERSHOT_8))) {
                xySizeMod += 30.0f;
            }
            hitboxData++;
            for (i = 0; i < count; i++, hitboxData += 6) {
                rotateBox = 0.0f;
                boxRotZ = 0.0f;
                boxRotY = 0.0f;
                boxRotX = 0.0f;
                if (hitboxData[0] >= HITBOX_TYPE_3) {
                    return 0;
                }
                if (hitboxData[0] == HITBOX_TYPE_2) {
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
                    Matrix_RotateZ(gCalcMatrix, -boxRotZ * M_DTOR, 0);
                    Matrix_RotateX(gCalcMatrix, -boxRotX * M_DTOR, 1);
                    Matrix_RotateY(gCalcMatrix, -boxRotY * M_DTOR, 1);
                    Matrix_RotateZ(gCalcMatrix, -obj->rot.z * M_DTOR, 1);
                    Matrix_RotateX(gCalcMatrix, -obj->rot.x * M_DTOR, 1);
                    Matrix_RotateY(gCalcMatrix, -obj->rot.y * M_DTOR, 1);
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
                    if (shot->obj.id == PLAYERSHOT_4) {
                        Object_Kill(&shot->obj, shot->sfxSource);
                        return 0;
                    }
                    if ((obj->id < 176) || (obj->id >= 292)) {
                        func_beam_80036318(shot);
                    }
                    if ((obj->id == 15) || ((obj->id == 22) && (i == 0)) || ((obj->id == 10) && (i == 0)) ||
                        ((obj->id == 13) && (i == 0)) || ((obj->id == 12) && (i < 3)) || (obj->id == 16) ||
                        (obj->id == 14)) {
                        if (shot->obj.pos.x - (obj->pos.x + hitbox->x.offset) < -hitbox->x.size) {
                            if (hitbox->z.size + (obj->pos.z + hitbox->z.offset) < shot->obj.pos.z) {
                                shot->obj.pos.z = hitbox->z.size + (obj->pos.z + hitbox->z.offset) - 5.0f;
                            }
                            func_beam_800365E4((hitbox->x.offset + obj->pos.x) - (hitbox->x.size + 2.0f),
                                               shot->obj.pos.y, shot->obj.pos.z, obj->pos.x, obj->pos.z, obj->rot.y,
                                               obj->rot.y + 90.0f, 0.0f, 2.0f, 1, 20);
                            return i + 1;
                        }
                        if (hitbox->x.size < shot->obj.pos.x - (obj->pos.x + hitbox->x.offset)) {
                            if ((hitbox->z.size + (obj->pos.z + hitbox->z.offset)) < shot->obj.pos.z) {
                                shot->obj.pos.z = hitbox->z.size + (obj->pos.z + hitbox->z.offset) - 5.0f;
                            }
                            func_beam_800365E4(hitbox->x.size + (hitbox->x.offset + obj->pos.x) + 2.0f, shot->obj.pos.y,
                                               shot->obj.pos.z, obj->pos.x, obj->pos.z, obj->rot.y, obj->rot.y + 90.0f,
                                               0.0f, 2.0f, 1, 20);
                            return i + 1;
                        }
                        if (((hitbox->y.size + (obj->pos.y + hitbox->y.offset)) - 10.0f) <= shot->obj.pos.y) {
                            shot->obj.pos.y = ((hitbox->y.size + (obj->pos.y + hitbox->y.offset)) - 10.0f);
                        }
                        func_beam_800365E4(shot->obj.pos.x, shot->obj.pos.y,
                                           hitbox->z.size + (obj->pos.z + hitbox->z.offset) + 20.0f, obj->pos.x,
                                           obj->pos.z, 0.0f, 0.0f, 0.0f, 2.0f, 1, 20);
                        return i + 1;
                    }
                    if (obj->id < 161) {
                        func_effect_8007A6F0(&shot->obj.pos, 0x29121007);
                    }
                    return i + 1;
                }
            }
        }
    }
    return 0;
}

s32 func_beam_80036F88(PlayerShot* shot, Actor* actor) {
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
                xySizeMod = fabsf((actor->obj.pos.z + D_ctx_80177D20) / 50.0f) + 10.0f;
                if ((shot->playerNum < 4) &&
                    ((gLaserStrength[shot->playerNum] != LASERS_SINGLE) || (shot->obj.id == PLAYERSHOT_8))) {
                    xySizeMod += 30.0f;
                }
            }
            for (i = 0; i < count; i++, hitboxData += 6) {
                if (actor->info.unk_16 == 1) {
                    shotPx = shot->obj.pos.x;
                    shotPy = shot->obj.pos.y;
                    shotPz = shot->obj.pos.z;
                } else {
                    if (hitboxData[0] == HITBOX_TYPE_2) {
                        Matrix_RotateZ(gCalcMatrix, -hitboxData[3] * M_DTOR, 0);
                        Matrix_RotateX(gCalcMatrix, -hitboxData[1] * M_DTOR, 1);
                        Matrix_RotateY(gCalcMatrix, -hitboxData[2] * M_DTOR, 1);
                        Matrix_RotateZ(gCalcMatrix, -actor->obj.rot.z * M_DTOR, 1);
                        Matrix_RotateX(gCalcMatrix, -actor->obj.rot.x * M_DTOR, 1);
                        Matrix_RotateY(gCalcMatrix, -actor->obj.rot.y * M_DTOR, 1);
                        hitboxData += 4;
                    } else {
                        Matrix_RotateZ(gCalcMatrix, -actor->obj.rot.z * M_DTOR, 0);
                        Matrix_RotateX(gCalcMatrix, -actor->obj.rot.x * M_DTOR, 1);
                        Matrix_RotateY(gCalcMatrix, -actor->obj.rot.y * M_DTOR, 1);
                    }
                    if (((actor->vwork[29].z != 0.0f) || (actor->vwork[29].x != 0.0f) || (actor->unk_0F4.z != 0.0f) ||
                         (actor->vwork[29].y != 0.0f)) &&
                        (actor->unk_0B4 != 31)) {
                        Matrix_RotateZ(gCalcMatrix, -(actor->vwork[29].z + actor->unk_0F4.z) * M_DTOR, 1);
                        Matrix_RotateX(gCalcMatrix, -actor->vwork[29].x * M_DTOR, 1);
                        Matrix_RotateY(gCalcMatrix, -actor->vwork[29].y * M_DTOR, 1);
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

bool func_beam_80037438(PlayerShot* shot, Actor* actor) {
    Object* shotx = &shot->obj;
    f32 temp_fv1 = actor->obj.pos.x - shotx->pos.x;
    f32 temp_fa0 = actor->obj.pos.z - shotx->pos.z;
    f32 var_fa1;
    f32* hitboxData = actor->info.hitbox;

    if (((s32) hitboxData[0] != 0) && (sqrtf(SQ(temp_fv1) + SQ(temp_fa0)) <= 500.0f)) {
        if (shot->playerNum < 4) {
            temp_fv1 = actor->obj.pos.x - gPlayer[0].camEye.x;
            temp_fa0 = actor->obj.pos.z + D_ctx_80177D20 - gPlayer[0].camEye.z;
            var_fa1 = (sqrtf(SQ(temp_fv1) + SQ(temp_fa0)) / 50.0f) + 20.0f + 10.0f;
            if (var_fa1 > 200.0f) {
                var_fa1 = 200.0f;
            }
            if (shotx->id == PLAYERSHOT_8) {
                var_fa1 = 30.0f;
            } else if (gLaserStrength[shot->playerNum] != LASERS_SINGLE) {
                var_fa1 += 30.0f;
            }
            if (fabsf(hitboxData[1] + actor->obj.pos.z - shotx->pos.z) < (hitboxData[2] + var_fa1)) {
                if (fabsf(hitboxData[3] + actor->obj.pos.y - shotx->pos.y) < (hitboxData[4] + var_fa1)) {
                    if (fabsf(hitboxData[5] + actor->obj.pos.x - shotx->pos.x) < (hitboxData[6] + var_fa1)) {
                        return true;
                    }
                }
            }
        } else {
            if (fabsf(hitboxData[1] + actor->obj.pos.z - shotx->pos.z) < hitboxData[2]) {
                if (fabsf(hitboxData[3] + actor->obj.pos.y - shotx->pos.y) < hitboxData[4]) {
                    if (fabsf(hitboxData[5] + actor->obj.pos.x - shotx->pos.x) < hitboxData[6]) {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

bool func_beam_80037698(PlayerShot* shot, Sprite* sprite) {
    f32* temp_v0 = sprite->info.hitbox;

    if (((s32) temp_v0[0] != 0) && (fabsf(temp_v0[1] + sprite->obj.pos.z - shot->obj.pos.z) < temp_v0[2]) &&
        (fabsf(temp_v0[3] + sprite->obj.pos.y - shot->obj.pos.y) < temp_v0[4]) &&
        (fabsf(temp_v0[5] + sprite->obj.pos.x - shot->obj.pos.x) < temp_v0[6])) {
        return true;
    }
    return false;
}

bool func_beam_8003774C(PlayerShot* shot, ObjectId objId, Object* obj) {
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
        (objId == OBJ_BOSS_313) || (objId == ACTOR_EVENT_ID) || (objId == OBJ_80_39)) {
        Matrix_RotateY(gCalcMatrix, -obj->rot.y * M_DTOR, 0);
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
            case OBJ_80_4:
            case OBJ_80_5:
                objId = COL2_1;
                useCol2 = true;
                break;
            case OBJ_80_149:
                objId = COL1_5;
                break;
            case OBJ_80_150:
                objId = COL1_6;
                break;
            case OBJ_BOSS_308:
                objId = COL1_4;
                break;
            case OBJ_BOSS_312:
                objId = COL1_9;
                break;
            case OBJ_BOSS_309:
                objId = COL1_7;
                break;
            case ACTOR_EVENT_ID:
                objId = COL1_3;
                break;
            case OBJ_BOSS_313:
                objId = COL1_8;
                break;
            case OBJ_80_39:
                objId = COL1_1;
                break;
            case OBJ_80_120:
                objId = COL2_18;
                useCol2 = true;
                break;
            case OBJ_80_143:
                objId = COL2_17;
                useCol2 = true;
                break;
            case OBJ_80_124:
                objId = COL2_15;
                useCol2 = true;
                break;
            case OBJ_80_126:
                objId = COL2_16;
                useCol2 = true;
                break;
            case OBJ_80_47:
                objId = COL2_7;
                useCol2 = true;
                break;
            case OBJ_80_2:
                objId = COL2_2;
                useCol2 = true;
                break;
            case OBJ_80_3:
            case OBJ_80_69:
                objId = COL2_3;
                useCol2 = true;
                break;
            case OBJ_80_140:
                objId = COL2_4;
                useCol2 = true;
                break;
            case OBJ_80_141:
                objId = COL2_6;
                useCol2 = true;
                break;
            case OBJ_80_117:
                objId = COL2_14;
                useCol2 = true;
                break;
            case OBJ_80_70:
                objId = COL2_8;
                useCol2 = true;
                break;
            case OBJ_80_72:
                objId = COL2_9;
                useCol2 = true;
                break;
            case OBJ_80_71:
                objId = COL2_10;
                useCol2 = true;
                break;
            case OBJ_80_73:
                objId = COL2_11;
                useCol2 = true;
                break;
            case OBJ_80_67:
                objId = COL2_12;
                useCol2 = true;
                break;
            case OBJ_80_74:
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
                if (shot->obj.id == PLAYERSHOT_4) {
                    Object_Kill(&shot->obj, shot->sfxSource);
                    return false;
                }
                func_beam_80036318(shot);
                func_effect_8007A6F0(&shot->obj.pos, 0x29121007);
                if (gCurrentLevel == LEVEL_METEO) {
                    Matrix_RotateY(gCalcMatrix, obj->rot.y * M_DTOR, 0);
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
            if (shot->obj.id == PLAYERSHOT_4) {
                Object_Kill(&shot->obj, shot->sfxSource);
                return false;
            }
            func_beam_80036318(shot);
            func_effect_8007A6F0(&shot->obj.pos, 0x29121007);
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

void func_beam_80037CF4(PlayerShot* shot, Actor* actor, s32 hitIndex) {
    Vec3f sp44 = { 0.0f, 0.0f, -100.0f };
    Vec3f sp38;

    actor->unk_0D0 = 1;
    actor->unk_0D2 = hitIndex - 1;
    actor->timer_0C2 = 2;
    actor->damage = 10;
    if ((shot->playerNum < 4) && (gPlayer[shot->playerNum].form != FORM_LANDMASTER)) {
        switch (gLaserStrength[shot->playerNum]) {
            case LASERS_TWIN:
                actor->damage = 12;
                break;
            case LASERS_HYPER:
                actor->damage = 15;
                break;
        }
    } else if ((shot->playerNum >= 100) && (gCurrentLevel == LEVEL_SECTOR_X)) {
        if ((gActors[shot->playerNum - 100].obj.id == 200) && (gActors[shot->playerNum - 100].iwork[12] == 5)) {
            actor->damage = 30;
        }
    }
    if (shot->obj.id == PLAYERSHOT_9) {
        actor->damage = 100;
    } else if (shot->obj.id == PLAYERSHOT_8) {
        if (gCurrentLevel == LEVEL_AQUAS) {
            actor->damage = 31;
        } else {
            actor->unk_0D0 = 2;
            actor->damage = 30;
            actor->timer_0CA[shot->playerNum] = 0;
        }
    }
    actor->unk_0D4 = shot->playerNum + 1;
    actor->unk_0D8.x = shot->obj.pos.x;
    actor->unk_0D8.y = shot->obj.pos.y;
    actor->unk_0D8.z = shot->obj.pos.z;
    if (((actor->obj.id == OBJ_ACTOR_EVENT) && (actor->unk_0D2 == 0) &&
         ((actor->unk_0B4 == 48) || (actor->unk_0B4 == 49) || (actor->unk_0B4 == 50))) ||
        ((actor->obj.id == OBJ_ACTOR_ALLRANGE) && (actor->fwork[23] > 1.0f)) ||
        ((actor->obj.id == OBJ_ACTOR_EVENT) && (actor->unk_0D2 == 0) && (actor->unk_0B4 == 67)) ||
        ((actor->obj.id == OBJ_ACTOR_261) && (shot->obj.id != PLAYERSHOT_8) &&
         ((actor->state < 3) || (actor->state >= 5))) ||
        ((actor->obj.id == OBJ_ACTOR_260) && (shot->obj.id != PLAYERSHOT_8) && (actor->timer_0BC != 0))) {
        if ((actor->obj.id == OBJ_ACTOR_261) && (actor->state < 2)) {
            actor->state = 2;
        }
        if ((shot->obj.id == PLAYERSHOT_8) || (shot->obj.id == PLAYERSHOT_3)) {
            func_beam_80036318(shot);
        } else {
            shot->unk_64 = 25;
            shot->obj.rot.y += 90.0f;
            shot->obj.rot.x = RAND_FLOAT(360.0f);
            Matrix_RotateY(gCalcMatrix, shot->obj.rot.y * M_DTOR, 0);
            Matrix_RotateX(gCalcMatrix, shot->obj.rot.x * M_DTOR, 1);
            Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp44, &sp38);
            shot->vel.x = sp38.x;
            shot->vel.y = sp38.y;
            shot->vel.z = sp38.z;
            shot->obj.pos.x += shot->vel.x * 5.0f;
            shot->obj.pos.y += shot->vel.y * 5.0f;
            shot->obj.pos.z += shot->vel.z * 5.0f;
            actor->timer_0C2 = 3;
            func_effect_80078E50(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, 8.0f);
            AUDIO_PLAY_SFX(0x29121007, actor->sfxSource, 4);
            func_play_800A668C(D_ctx_8017849C, D_ctx_801784A0, D_ctx_80178498);
        }
    } else {
        func_beam_80036318(shot);
    }
}

void func_beam_80038140(PlayerShot* shot) {
    s32 i;
    s32 temp_v0;
    s32 spA4;
    Vec3f test;
    f32 sp94;
    Vec3f sp88;
    Vec3f sp7C;
    Actor* actor;
    Boss* boss;
    Object_58* obj58;
    Sprite* sprite;
    Object_80* obj80;
    Effect* effect;
    bool sp60;
    Player* player;

    sp60 = true;
    if (shot->obj.id == PLAYERSHOT_4) {
        sp60 = false;
    }
    if (sp60) {
        for (i = 0, effect = gEffects; i < 100; i++, effect++) {
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
        for (i = 0, actor = gActors; i < 60; i++, actor++) {
            if ((actor->obj.status >= OBJ_ACTIVE) && (actor->timer_0C2 == 0)) {
                switch (actor->obj.id) {
                    case OBJ_ACTOR_180:
                        if (func_beam_8003774C(shot, actor->obj.id, &actor->obj)) {
                            actor->unk_0D0 = 1;
                            actor->unk_0D2 = shot->playerNum;
                            return;
                        }
                        break;
                    case OBJ_ACTOR_EVENT:
                        if (actor->unk_0B4 == 42) {
                            if (func_beam_8003774C(shot, ACTOR_EVENT_ID, &actor->obj)) {
                                actor->unk_0D0 = 1;
                                actor->unk_0D2 = shot->playerNum;
                                return;
                            }
                        } else if (actor->unk_0B4 == 63) {
                            test.x = fabsf(actor->obj.pos.x - shot->obj.pos.x);
                            test.y = fabsf(actor->obj.pos.y - shot->obj.pos.y);
                            test.z = fabsf(actor->obj.pos.z - shot->obj.pos.z);
                            if (VEC3F_MAG(&test) < 1000.0f) {
                                func_beam_80037CF4(shot, actor, 0);
                            }
                        } else {
                            temp_v0 = func_beam_80036F88(shot, actor);
                            if (temp_v0 != 0) {
                                func_beam_80037CF4(shot, actor, temp_v0);
                                return;
                            }
                        }
                        break;
                    default:
                        if (actor->info.unk_16 != 0) {
                            if (actor->obj.id == OBJ_ACTOR_ALLRANGE) {
                                if ((actor->aiType >= AI360_WOLF) && (actor->aiType < AI360_10) &&
                                    (((gCurrentLevel == LEVEL_VENOM_2) && (shot->playerNum < 104)) ||
                                     ((gCurrentLevel != LEVEL_VENOM_2) && (shot->playerNum == 0))) &&
                                    (shot->obj.id != PLAYERSHOT_8) &&
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
                            temp_v0 = func_beam_80037438(shot, actor);
                            if (temp_v0 != 0) {
                                func_beam_80037CF4(shot, actor, temp_v0);
                                return;
                            }
                        } else {
                            temp_v0 = func_beam_80036874(shot, actor->info.hitbox, &actor->obj);
                            if (temp_v0 != 0) {
                                func_beam_80037CF4(shot, actor, temp_v0);
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
                if (gVersusMode && (shot->playerNum < 4) &&
                    !((gLaserStrength[shot->playerNum] == LASERS_SINGLE) && (shot->obj.id != PLAYERSHOT_8))) {
                    test.x = 100.0f;
                }
                if (player->unk_280 >= 100) {
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
                if ((i != shot->playerNum) &&
                    ((player->state_1C8 == PLAYERSTATE_1C8_3) || (player->state_1C8 == PLAYERSTATE_1C8_4)) &&
                    (fabsf(player->unk_138 - shot->obj.pos.z) < test.z) &&
                    (fabsf(player->pos.x - shot->obj.pos.x) < test.x) &&
                    (fabsf(player->pos.y - shot->obj.pos.y) < test.y)) {
                    if (player->unk_280 >= 100) {
                        shot->obj.rot.y = player->unk_0E8 + player->unk_114 + 180.0f + 90.0f;
                        shot->obj.rot.x = RAND_FLOAT(360.0f);
                        Matrix_RotateY(gCalcMatrix, shot->obj.rot.y * M_DTOR, 0);
                        Matrix_RotateX(gCalcMatrix, shot->obj.rot.x * M_DTOR, 1);
                        sp88.x = sp88.y = 0.0f;
                        sp88.z = -133.33333f;
                        Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp88, &sp7C);
                        shot->vel.x = sp7C.x;
                        shot->vel.y = sp7C.y;
                        shot->vel.z = sp7C.z;
                        shot->obj.pos.x += 2.0f * shot->vel.x;
                        shot->obj.pos.y += 2.0f * shot->vel.y;
                        shot->obj.pos.z += 2.0f * shot->vel.z;
                        shot->unk_64 = 5;
                        AUDIO_PLAY_SFX(0x09007011, player->sfxSource, 0);
                        func_effect_80078E50(player->pos.x, player->pos.y, player->unk_138, 8.0f);
                    } else {
                        func_beam_80036318(shot);
                        if (player->unk_1F4 == 0) {
                            if (gPlayer[0].form == 3) {
                                Player_ApplyDamage(player, 0, 60);
                            } else {
                                Player_ApplyDamage(player, 0, 20);
                            }
                            player->unk_284 = 1;
                            if (gCamCount != 1) {
                                player->unk_288 = shot->playerNum + 1;
                            }
                            player->unk_0D8.x = shot->vel.x * 0.1f;
                            player->unk_0D8.y = shot->vel.y * 0.1f;
                            player->unk_0D8.z = shot->vel.z * 0.1f;
                            if (player->form != FORM_ON_FOOT) {
                                func_effect_8007D1E0(player->pos.x, player->pos.y, player->unk_138, 2.0f);
                            }
                        }
                    }
                }
            }
        }
    }
    if ((D_ctx_801784AC == 4) && Ground_801B6AEC(shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z + D_ctx_80177D20)) {
        func_beam_80036318(shot);
        if (shot->obj.id != PLAYERSHOT_4) {
            func_effect_8007A900(shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z, 2.0f, 255, 15, 0);
        }
    }
    if ((D_ctx_80178294 != 0) && func_play_800A73E4(&sp94, &spA4, shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z)) {
        func_beam_80036318(shot);
        if (shot->obj.id != PLAYERSHOT_4) {
            func_effect_8007B228(shot->obj.pos.x, sp94, shot->obj.pos.z, 1.0f);
        }
    }

    if ((gLevelMode == LEVELMODE_ALL_RANGE) && (shot->playerNum < 110)) {
        for (i = 0, obj58 = gObjects58; i < 200; i++, obj58++) {
            if (obj58->obj.status == OBJ_ACTIVE) {
                if ((obj58->obj.id == OBJ_80_117) || (obj58->obj.id == OBJ_80_141) || (obj58->obj.id == OBJ_80_149) ||
                    (obj58->obj.id == OBJ_80_150) || (obj58->obj.id == OBJ_80_148) || (obj58->obj.id == OBJ_80_143) ||
                    (obj58->obj.id == OBJ_80_160) || (obj58->obj.id == OBJ_80_1) || (obj58->obj.id == OBJ_80_3) ||
                    (obj58->obj.id == OBJ_80_140)) {
                    func_beam_8003774C(shot, obj58->obj.id, &obj58->obj);
                } else {
                    func_beam_80036874(shot, obj58->info.hitbox, &obj58->obj);
                }
            }
        }
    } else {
        for (i = 0, obj80 = gObjects80; i < 50; i++, obj80++) {
            if (obj80->obj.status == OBJ_ACTIVE) {
                if ((obj80->obj.id == OBJ_80_1) || (obj80->obj.id == OBJ_80_39) || (obj80->obj.id == OBJ_80_4) ||
                    (obj80->obj.id == OBJ_80_5) || (obj80->obj.id == OBJ_80_120) || (obj80->obj.id == OBJ_80_124) ||
                    (obj80->obj.id == OBJ_80_126) || (obj80->obj.id == OBJ_80_47) || (obj80->obj.id == OBJ_80_2) ||
                    (obj80->obj.id == OBJ_80_3) || (obj80->obj.id == OBJ_80_67) || (obj80->obj.id == OBJ_80_74) ||
                    (obj80->obj.id == OBJ_80_3)) {
                    func_beam_8003774C(shot, obj80->obj.id, &obj80->obj);
                } else {
                    temp_v0 = func_beam_80036874(shot, obj80->info.hitbox, &obj80->obj);
                    if (temp_v0 != 0) {
                        obj80->dmgType = 1;
                        obj80->dmgPart = temp_v0 - 1;
                    }
                }
            }
        }
    }
    if (sp60) {
        for (i = 0, sprite = gSprites; i < 40; i++, sprite++) {
            if (sprite->obj.status == OBJ_ACTIVE) {
                if (sprite->obj.id != OBJ_SPRITE_TI_CACTUS) {
                    if (func_beam_80037698(shot, sprite)) {
                        sprite->unk_46 = 1;
                    }
                } else {
                    if (func_beam_80036874(shot, sprite->info.hitbox, &sprite->obj) != 0) {
                        sprite->unk_46 = 1;
                    }
                }
            }
        }
    }
    for (i = 0, boss = gBosses; i < 4; i++, boss++) {
        if ((boss->obj.status == OBJ_ACTIVE) && (boss->timer_05A == 0)) {
            if ((boss->obj.id == OBJ_BOSS_308) || (boss->obj.id == OBJ_BOSS_312) || (boss->obj.id == OBJ_BOSS_309) ||
                (boss->obj.id == OBJ_BOSS_313)) {
                func_beam_8003774C(shot, boss->obj.id, &boss->obj);
            } else if (boss->obj.id == OBJ_BOSS_310) {
                test.x = fabsf(boss->obj.pos.x - shot->obj.pos.x) * .8333333f;
                test.y = fabsf(boss->obj.pos.y - shot->obj.pos.y) * 2;
                test.z = fabsf(boss->obj.pos.z - shot->obj.pos.z) * 0.8333333f;
                if (VEC3F_MAG(&test) < 1500.0f) {
                    if (shot->obj.id == PLAYERSHOT_4) {
                        Object_Kill(&shot->obj, shot->sfxSource);
                    } else {
                        boss->dmgType = DMG_BEAM;
                        func_beam_80036318(shot);
                        AUDIO_PLAY_SFX(0x29001062, shot->sfxSource, 4);
                    }
                }
            } else {
                if (boss->obj.id == OBJ_BOSS_316) {
                    test.x = fabsf(boss->obj.pos.x - shot->obj.pos.x);
                    test.y = fabsf(boss->obj.pos.y - 300.0f - shot->obj.pos.y) * 7.42f;
                    test.z = fabsf(boss->obj.pos.z - shot->obj.pos.z);
                    if (VEC3F_MAG(&test) < 2700.0f) {
                        if (shot->obj.id == PLAYERSHOT_4) {
                            Object_Kill(&shot->obj, shot->sfxSource);
                        } else {
                            boss->dmgType = DMG_BEAM;
                            boss->dmgPart = 100;
                            AUDIO_PLAY_SFX(0x29121007, shot->sfxSource, 4);
                            func_beam_80036318(shot);
                        }
                    }
                }
                temp_v0 = func_beam_80036874(shot, boss->info.hitbox, &boss->obj);
                if (temp_v0 != 0) {
                    if (shot->obj.id == PLAYERSHOT_4) {
                        Object_Kill(&shot->obj, shot->sfxSource);
                    } else {
                        if ((boss->obj.id == OBJ_BOSS_316) && (shot->playerNum != 0)) {
                            break;
                        }
                        boss->dmgType = DMG_BEAM;
                        if (shot->obj.id == PLAYERSHOT_3) {
                            boss->dmgType = DMG_BOMB;
                            boss->damage = 20;
                        } else if (shot->obj.id == PLAYERSHOT_8) {
                            if (gCurrentLevel == LEVEL_AQUAS) {
                                boss->damage = 31;
                            } else {
                                boss->damage = 30;
                            }
                        } else {
                            boss->damage = 10;
                            if (shot->playerNum < 4) {
                                switch (gLaserStrength[shot->playerNum]) {
                                    case LASERS_SINGLE:
                                    case LASERS_TWIN:
                                        break;
                                    case LASERS_HYPER:
                                        boss->damage = 15;
                                        break;
                                }
                            }
                        }
                        if (boss->obj.id == OBJ_BOSS_314) {
                            boss->swork[19] = shot->playerNum;
                        }
                        boss->dmgPart = temp_v0 - 1;
                        if (boss->obj.id == OBJ_BOSS_301) {
                            boss->swork[5] = shot->obj.id;
                        } else if (boss->obj.id == OBJ_BOSS_319) {
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

void func_beam_80038F34(PlayerShot* shot) {
    Vec3f sp4C = { 0.0f, 0.0f, 0.0f };
    s32 sp48 = 0;

    Matrix_Translate(gGfxMatrix, shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z + D_ctx_80177D20, 1);
    Matrix_MultVec3f(gGfxMatrix, &sp4C, &D_beam_8015F950);
    if ((D_beam_8015F950.z < 0.0f) && (D_beam_8015F950.z > -10000.0f)) {
        if (fabsf(D_beam_8015F950.x) < (fabsf(D_beam_8015F950.z * 0.5f) + 500.0f)) {
            if (fabsf(D_beam_8015F950.y) < (fabsf(D_beam_8015F950.z * 0.5f) + 500.0f)) {
                sp48 = 1;
            }
        }
    }
    if (!sp48) {
        if (!gVersusMode) {
            Object_Kill(&shot->obj, shot->sfxSource);
            return;
        }
    } else {
        shot->obj.rot.y = -gPlayer[gPlayerNum].unk_058;
        Matrix_RotateY(gGfxMatrix, shot->obj.rot.y, 1);
        Matrix_Scale(gGfxMatrix, 2.0f, 2.0f, 2.0f, 1);
        if (shot->obj.id == PLAYERSHOT_7) {
            Matrix_Scale(gGfxMatrix, 0.2f, 0.2f, 0.2f, 1);
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
                Matrix_Scale(gGfxMatrix, 1.5f, 0.7f, 1.0f, 1);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_1025800);
                break;
        }
    }
}

void func_beam_80039210(PlayerShot* shot) {
    f32 var_fv0;
    f32 var_fv1;
    u8 var_a1;
    f32 sp70;
    Gfx* sp6C;

    sp6C = D_101AED0;
    if (gCamCount < 4) {
        RCP_SetupDL_21();
        sp70 = 9.0f;
        if ((shot->unk_58 == 0) || ((gCurrentLevel == LEVEL_METEO) && (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_2))) {
            var_fv0 = 4.0f;
            var_fv1 = 20.0f;
        } else {
            var_fv0 = 2.0f;
            var_fv1 = 10.0f;
        }
        if ((gLaserStrength[0] > LASERS_SINGLE) && (shot->unk_58 == 0)) {
            switch (gLaserStrength[0]) {
                case LASERS_TWIN:
                    break;
                case LASERS_HYPER:
                    sp6C = D_101AD20;
                    break;
            }
            if (gCurrentLevel == LEVEL_AQUAS) {
                sp70 = 4.0f;
            }
            Matrix_Scale(gGfxMatrix, var_fv0, var_fv0, var_fv1, 1);
            Matrix_RotateY(gGfxMatrix, M_PI, 1);
            Matrix_Translate(gGfxMatrix, sp70, 0.f, 0.0f, 1);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, sp6C);
            Matrix_Translate(gGfxMatrix, -(2.0f * sp70), 0.0f, 0.f, 1);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, sp6C);
        } else {
            var_a1 = 0;
            if ((gCurrentLevel != LEVEL_KATINA) && (shot->playerNum >= 104) && (shot->playerNum != 108)) {
                if (gActors[shot->playerNum - 100].obj.id != 200) {
                    var_a1 = 1;
                } else if (gActors[shot->playerNum - 100].iwork[12] == 5) {
                    var_a1 = 2;
                }
            } else if (gCurrentLevel == LEVEL_KATINA) {
                if (gPlayer[0].state_1C8 != PLAYERSTATE_1C8_2) {
                    if (shot->playerNum >= 104) {
                        if (gActors[shot->playerNum - 100].unk_0B6 == 0) {
                            var_a1 = 1;
                        }
                        if (gActors[shot->playerNum - 100].unk_0B6 == 2) {
                            var_a1 = 2;
                        }
                    }
                } else if (gActors[shot->playerNum - 100].unk_0B6 == 34) {
                    var_a1 = 1;
                }
            }
            switch (var_a1) {
                case 0:
                    Matrix_Scale(gGfxMatrix, var_fv0, var_fv0, var_fv1, 1);
                    Matrix_RotateY(gGfxMatrix, M_PI, 1);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_101AED0);
                    break;
                case 1:
                    Matrix_Translate(gGfxMatrix, 0.0f, 0.f, 150.0f, 1);
                    Matrix_Scale(gGfxMatrix, 0.7f, 0.7f, 1.5f, 1);
                    Matrix_RotateY(gGfxMatrix, M_PI, 1);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_101ABD0);
                    break;
                case 2:
                    Matrix_Scale(gGfxMatrix, var_fv0, var_fv0, var_fv1, 1);
                    Matrix_RotateY(gGfxMatrix, M_PI, 1);
                    Matrix_Translate(gGfxMatrix, 25.0f, 0.0f, 0.f, 1);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_101AED0);
                    sp6C = D_101AED0;
                    Matrix_Translate(gGfxMatrix, -50.0f, 0.0f, 0.f, 1);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, sp6C);
                    break;
                case 3:
                    Matrix_Push(&gGfxMatrix);
                    Matrix_Translate(gGfxMatrix, 50.0f, 0.0f, 150.0f, 1);
                    Matrix_Scale(gGfxMatrix, 0.7f, 0.7f, 1.5f, 1);
                    Matrix_RotateY(gGfxMatrix, M_PI, 1);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_101ABD0);
                    Matrix_Pop(&gGfxMatrix);
                    Matrix_Translate(gGfxMatrix, -50.0f, 0.0f, 150.0f, 1);
                    Matrix_Scale(gGfxMatrix, 0.7f, 0.7f, 1.5f, 1);
                    Matrix_RotateY(gGfxMatrix, M_PI, 1);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_101ABD0);
                    break;
            }
        }
    } else {
        RCP_SetupDL_64();
        switch (shot->playerNum) {
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
        Matrix_Scale(gGfxMatrix, 6.0f, 4.0f, 10.0f, 1);
        Matrix_RotateY(gGfxMatrix, M_PI, 1);
        Matrix_SetGfxMtx(&gMasterDisp);
        if (gLaserStrength[shot->playerNum] != LASERS_SINGLE) {
            Matrix_Translate(gGfxMatrix, 6.0f, 0.0f, 0.0f, 1);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_versus_302D120);
            Matrix_Translate(gGfxMatrix, -12.0f, 0.0f, 0.0f, 1);
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
void func_beam_80039A50(PlayerShot* shot) {
    Vec3f sp11C = { 0.0f, 0.0f, 0.0f };
    s32 pad[4];
    f32 var_fv1;
    s32 sp104 = 0;

    Matrix_Translate(gGfxMatrix, shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z + D_ctx_80177D20, 1);
    Matrix_MultVec3f(gGfxMatrix, &sp11C, &D_beam_8015F950);
    if ((D_beam_8015F950.z < 0.0f) && (D_beam_8015F950.z > -10000.0f)) {
        var_fv1 = fabsf(D_beam_8015F950.x); // probably fake. The use of temps was likely different
        if (var_fv1 < (fabsf(D_beam_8015F950.z * 0.5f) + 500.0f)) {
            if (fabsf(D_beam_8015F950.y) < (fabsf(D_beam_8015F950.z * 0.5f) + 500.0f)) {
                sp104 = 1;
            }
        }
    }
    if (!sp104) {
        if ((shot->obj.id != PLAYERSHOT_3) && (shot->unk_64 < 10) && !gVersusMode) {
            Object_Kill(&shot->obj, shot->sfxSource);
        }
    } else {
        if ((shot->obj.id == PLAYERSHOT_5) || (shot->obj.id == PLAYERSHOT_6) || (shot->obj.id == PLAYERSHOT_7)) {
            shot->obj.rot.y = RAD_TO_DEG(-gPlayer[gPlayerNum].unk_058);
            shot->obj.rot.x = RAD_TO_DEG(gPlayer[gPlayerNum].unk_05C);
        }
        if (shot->obj.id != PLAYERSHOT_2) {
            Matrix_RotateY(gGfxMatrix, shot->obj.rot.y * M_DTOR, 1);
            Matrix_RotateX(gGfxMatrix, shot->obj.rot.x * M_DTOR, 1);
            Matrix_RotateZ(gGfxMatrix, shot->obj.rot.z * M_DTOR, 1);
            if ((shot->obj.id == PLAYERSHOT_3) && (shot->unk_5C == 0)) {
                Matrix_RotateZ(gGfxMatrix, shot->unk_34 * M_DTOR, 1);
                Matrix_RotateY(gGfxMatrix, shot->unk_30 * M_DTOR, 1);
                Matrix_RotateX(gGfxMatrix, shot->unk_2C * M_DTOR, 1);
            }
        }
        Matrix_Translate(gGfxMatrix, 0.f, 0.f, D_800C9BD8[shot->obj.id], 1);
        Matrix_SetGfxMtx(&gMasterDisp);
        switch (shot->obj.id) {
            case PLAYERSHOT_0:
            case PLAYERSHOT_1:
                func_beam_80039210(shot);
                break;
            case PLAYERSHOT_3:
                if (shot->unk_5C == 0) {
                    RCP_SetupDL(&gMasterDisp, 0x1D);
                    gSPDisplayList(gMasterDisp++, D_10231A0);
                    Matrix_Pop(&gGfxMatrix);
                    Matrix_Push(&gGfxMatrix);
                    Matrix_Translate(gGfxMatrix, shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z + D_ctx_80177D20, 1);
                    Matrix_RotateY(gGfxMatrix, -gPlayer[gPlayerNum].unk_058, 1);
                    Matrix_RotateX(gGfxMatrix, gPlayer[gPlayerNum].unk_05C, 1);
                    Matrix_RotateZ(gGfxMatrix, gGameFrameCount * 40.0f * M_DTOR, 1);
                    if (((gGameFrameCount % 2) == 0)) {
                        Matrix_Scale(gGfxMatrix, 1.7f, 1.7f, 1.7f, 1);
                    } else {
                        Matrix_Scale(gGfxMatrix, 1.2f, 1.2f, 1.2f, 1);
                    }
                    RCP_SetupDL(&gMasterDisp, 0x31);
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
                    if (gVersusMode) {
                        switch (shot->playerNum) {
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
                    Matrix_Scale(gGfxMatrix, shot->unk_44, shot->unk_44, shot->unk_44, 1);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    if (gVersusMode) {
                        RCP_SetupDL_49();
                        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, shot->unk_58);
                        switch (shot->playerNum) {
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
            case PLAYERSHOT_5:
                gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                RCP_SetupDL_40();
                if (gVersusMode) {
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
                    gDPSetEnvColor(gMasterDisp++, D_800C9C00[shot->playerNum], D_800C9C04[shot->playerNum],
                                   D_800C9C08[shot->playerNum], 255);
                    RCP_SetupDL(&gMasterDisp, 0x31);
                    if (gLaserStrength[shot->playerNum] != LASERS_SINGLE) {
                        Matrix_RotateZ(gGfxMatrix, gGameFrameCount * 48.0f * M_DTOR, 1);
                        Matrix_Push(&gGfxMatrix);
                        Matrix_Translate(gGfxMatrix, 0.f, 50.0f, 0.0f, 1);
                        Matrix_RotateZ(gGfxMatrix, gGameFrameCount * 70.0f * M_DTOR, 1);
                        Matrix_Scale(gGfxMatrix, 2.0f, 2.0f, 2.0f, 1);
                        Matrix_SetGfxMtx(&gMasterDisp);
                        gSPDisplayList(gMasterDisp++, D_versus_301AD60);
                        Matrix_Pop(&gGfxMatrix);
                        Matrix_Translate(gGfxMatrix, 0.0f, -50.0f, 0.0f, 1);
                        Matrix_RotateZ(gGfxMatrix, gGameFrameCount * 70.0f * M_DTOR, 1);
                        Matrix_Scale(gGfxMatrix, 2.0f, 2.0f, 2.0f, 1);
                        Matrix_SetGfxMtx(&gMasterDisp);
                        gSPDisplayList(gMasterDisp++, D_versus_301AD60);
                    } else {
                        if (((gGameFrameCount % 2) == 0)) {
                            var_fv1 = M_PI;
                        } else {
                            var_fv1 = 0.0f;
                        }
                        Matrix_RotateY(gGfxMatrix, var_fv1, 1);
                        Matrix_RotateZ(gGfxMatrix, 30.0f * M_DTOR, 1);
                        Matrix_Scale(gGfxMatrix, 2.0f, 2.0f, 2.0f, 1);
                        Matrix_SetGfxMtx(&gMasterDisp);
                        gSPDisplayList(gMasterDisp++, D_versus_301AD60);
                    }
                } else {
                    if (((gGameFrameCount % 2) == 0)) {
                        var_fv1 = M_PI;
                    } else {
                        var_fv1 = 0.0f;
                    }
                    Matrix_RotateY(gGfxMatrix, var_fv1, 1);
                    Matrix_RotateZ(gGfxMatrix, 30.0f * M_DTOR, 1);
                    Matrix_Scale(gGfxMatrix, 1.0f, 0.65f, 1.0f, 1);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    RCP_SetupDL_68();
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
                    gDPSetEnvColor(gMasterDisp++, 0, 255, 0, 0);
                    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                    gSPDisplayList(gMasterDisp++, D_landmaster_3006940);
                }
                break;
            case PLAYERSHOT_6:
            case PLAYERSHOT_7:
                Matrix_Scale(gGfxMatrix, shot->unk_44, shot->unk_44, shot->unk_44, 1);
                Matrix_SetGfxMtx(&gMasterDisp);
                RCP_SetupDL(&gMasterDisp, 0x31);
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
                gDPSetEnvColor(gMasterDisp++, D_800C9C00[shot->playerNum], D_800C9C04[shot->playerNum],
                               D_800C9C08[shot->playerNum], 255);
                if (gLaserStrength[shot->playerNum] != LASERS_SINGLE) {
                    Matrix_RotateZ(gGfxMatrix, gGameFrameCount * 48.0f * M_DTOR, 1);
                    Matrix_Push(&gGfxMatrix);
                    Matrix_Translate(gGfxMatrix, 0.f, 40.0f, 0.0f, 1);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_versus_301AEF0);
                    Matrix_Pop(&gGfxMatrix);
                    Matrix_Translate(gGfxMatrix, 0.f, -40.0f, 0.0f, 1);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_versus_301AEF0);
                } else {
                    gSPDisplayList(gMasterDisp++, D_versus_301AEF0);
                }
                break;
            case PLAYERSHOT_8:
                Matrix_RotateY(gGfxMatrix, M_PI, 1);
                Matrix_SetGfxMtx(&gMasterDisp);
                if (gCurrentLevel == LEVEL_AQUAS) {
                    RCP_SetupDL(&gMasterDisp, 0x3C);
                    gSPDisplayList(gMasterDisp++, D_AQ_600DB80);
                    Matrix_Pop(&gGfxMatrix);
                    Matrix_Push(&gGfxMatrix);
                    Matrix_Translate(gGfxMatrix, shot->obj.pos.x, gGroundLevel, shot->obj.pos.z + D_ctx_80177D20, 1);
                    Matrix_Scale(gGfxMatrix, shot->unk_2C, shot->unk_30, shot->unk_34, 1);
                    RCP_SetupDL(&gMasterDisp, 0x31);
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 32, 32, 0, shot->unk_58);
                    gDPSetEnvColor(gMasterDisp++, 32, 16, 16, shot->unk_58);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_1024AC0);
                } else if (shot->unk_5C == 0) {
                    if (!(shot->unk_44 > 1.5f)) {
                        Matrix_Pop(&gGfxMatrix);
                        Matrix_Push(&gGfxMatrix);
                        Matrix_Translate(gGfxMatrix, shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z + D_ctx_80177D20,
                                         1);
                        Matrix_RotateY(gGfxMatrix, -gPlayer[gPlayerNum].unk_058, 1);
                        Matrix_RotateX(gGfxMatrix, gPlayer[gPlayerNum].unk_05C, 1);
                        Matrix_Push(&gGfxMatrix);
                        Matrix_Scale(gGfxMatrix, 20.0f, 20.0f, 20.0f, 1);
                        RCP_SetupDL(&gMasterDisp, 0x31);
                        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
                        if (gVersusMode) {
                            switch (shot->playerNum) {
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
                        Matrix_RotateZ(gGfxMatrix, gGameFrameCount * 53.0f * M_DTOR, 1);
                        Matrix_SetGfxMtx(&gMasterDisp);
                        gSPDisplayList(gMasterDisp++, D_101C2E0);
                        Matrix_RotateZ(gGfxMatrix, gGameFrameCount * -53.0f * 2.0f * M_DTOR, 1);
                        Matrix_SetGfxMtx(&gMasterDisp);
                        gSPDisplayList(gMasterDisp++, D_101C2E0);
                        Matrix_Pop(&gGfxMatrix);
                        if (((gGameFrameCount % 2) == 0)) {
                            Matrix_Scale(gGfxMatrix, 1.7f, 1.7f, 1.7f, 1);
                        } else {
                            Matrix_Scale(gGfxMatrix, 1.3f, 1.3f, 1.3f, 1);
                        }
                        Matrix_SetGfxMtx(&gMasterDisp);
                        gSPDisplayList(gMasterDisp++, D_1024AC0);
                    }
                } else {
                    RCP_SetupDL(&gMasterDisp, 0x1D);
                    gSPDisplayList(gMasterDisp++, D_10231A0);
                    Matrix_Pop(&gGfxMatrix);
                    Matrix_Push(&gGfxMatrix);
                    Matrix_Translate(gGfxMatrix, shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z + D_ctx_80177D20, 1);
                    Matrix_RotateY(gGfxMatrix, -gPlayer[gPlayerNum].unk_058, 1);
                    Matrix_RotateX(gGfxMatrix, gPlayer[gPlayerNum].unk_05C, 1);
                    if (((gGameFrameCount % 2) == 0)) {
                        Matrix_Scale(gGfxMatrix, 1.2f, 1.2f, 1.2f, 1);
                    } else {
                        Matrix_Scale(gGfxMatrix, 1.5f, 1.5f, 1.5f, 1);
                    }
                    RCP_SetupDL(&gMasterDisp, 0x31);
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 0, 255);
                    gDPSetEnvColor(gMasterDisp++, 255, 128, 128, 255);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_1024AC0);
                }
                break;
            case PLAYERSHOT_9:
                Matrix_RotateY(gGfxMatrix, M_PI, 1);
                Matrix_Scale(gGfxMatrix, 3.0f, 3.0f, 20.0f, 1);
                Matrix_SetGfxMtx(&gMasterDisp);
                RCP_SetupDL_40();
                gSPDisplayList(gMasterDisp++, D_GREAT_FOX_E00DFB0);
                break;
        }
    }
}

void func_beam_8003AF88(PlayerShot* shot) {
    switch (shot->obj.status) {
        case 1:
            func_beam_80039A50(shot);
            break;
        case 2:
            func_beam_80038F34(shot);
            break;
    }
}

void func_beam_8003AFD8(PlayerShot* shot) {
    shot->unk_60++;
    if (shot->unk_60 > 2) {
        Object_Kill(&shot->obj, shot->sfxSource);
    }
}

void func_beam_8003B00C(PlayerShot* shot, Player* player) {
    Vec3f sp5C;
    Vec3f sp50;
    Vec3f sp44;
    Vec3f sp38;
    switch (shot->unk_5C) {
        case 0:
            Matrix_RotateY(gCalcMatrix, (player->unk_114 + player->unk_0E8 + 180.0f) * M_DTOR, 0);
            Matrix_RotateX(gCalcMatrix, -(player->unk_0E4 * M_DTOR), 1);
            Matrix_RotateZ(gCalcMatrix, -((player->unk_0F8 + player->unk_0F0) * M_DTOR), 1);
            Matrix_Translate(gCalcMatrix, player->unk_084, player->unk_080, 0.0f, 1);
            sp5C.x = 0.0f;
            sp5C.y = 0.0f;
            sp5C.z = player->unk_0D0 + 200.0f;
            Matrix_MultVec3f(gCalcMatrix, &sp5C, &sp50);
            shot->vel.x = sp50.x;
            shot->vel.y = sp50.y;
            shot->vel.z = sp50.z - player->unk_110;
            sp5C.x = shot->unk_54;
            sp5C.y = -15.0f;
            sp5C.z = 0.0f;
            Matrix_MultVec3f(gCalcMatrix, &sp5C, &sp44);
            shot->unk_48 = player->pos.x + sp44.x;
            shot->unk_4C = player->pos.y + sp44.y;
            shot->unk_50 = player->unk_138 + sp44.z;
            shot->unk_44 += 200.0f;
            if (shot->unk_44 > 5000.0f) {
                shot->unk_44 = 5000.0f;
            }
            for (sp5C.z = 0.0f; sp5C.z <= shot->unk_44; sp5C.z += 200.0f) {
                Matrix_MultVec3f(gCalcMatrix, &sp5C, &sp38);
                D_ctx_80178498 = shot->obj.pos.z;
                D_ctx_801784A0 = shot->obj.pos.y;
                D_ctx_8017849C = shot->obj.pos.x;
                shot->obj.pos.x = player->pos.x + sp38.x;
                shot->obj.pos.y = player->pos.y + sp38.y;
                shot->obj.pos.z = player->unk_138 + sp38.z;
                Matrix_Push(&gCalcMatrix);
                func_beam_80038140(shot);
                Matrix_Pop(&gCalcMatrix);
                if (shot->obj.pos.y < gGroundLevel) {
                    shot->unk_5C = 0;
                    func_beam_80036770(shot->obj.pos.x, gGroundLevel + 2.0f, shot->obj.pos.z, shot->obj.rot.y, 2.0f);
                    break;
                } else if (shot->unk_5C == 2) {
                    shot->unk_5C = 0;
                    break;
                }
            }
            shot->unk_64 = 30;
            shot->obj.rot.y = player->unk_0E8 + player->unk_114;
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
                func_play_800A668C(D_ctx_8017849C, D_ctx_801784A0, D_ctx_80178498);
            }
            if ((fabsf(shot->obj.pos.x - shot->unk_48) < 200.0f) && (fabsf(shot->obj.pos.y - shot->unk_4C) < 200.0f) &&
                (fabsf(shot->obj.pos.z - shot->unk_50) < 200.0f)) {
                Object_Kill(&shot->obj, shot->sfxSource);
                return;
            }
            break;
    }
    if (shot->unk_64 == 0) {
        Object_Kill(&shot->obj, shot->sfxSource);
    }
    if (shot->unk_5C == 1) {
        if (shot->obj.pos.y < gGroundLevel) {
            func_beam_80036318(shot);
            func_beam_80036770(shot->obj.pos.x, gGroundLevel + 2.0f, shot->obj.pos.z, shot->obj.rot.y, 2.0f);
            if (gCurrentLevel == LEVEL_FORTUNA) {
                func_effect_8007BC7C(shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z, 3.0f);
                func_effect_8007BC7C(shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z, 3.0f);
                func_effect_8007BC7C(shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z, 3.0f);
            }
        }
        func_beam_80038140(shot);
    }
}

void func_beam_8003B55C(PlayerShot* shot, s32 index) {
    Vec3f sp44;
    Vec3f sp38;

    if ((gGroundType == GROUNDTYPE_WATER) && (shot->obj.pos.y < (gGroundLevel + 50.0f)) && (index == 0)) {
        func_effect_8007ACE0(shot->obj.pos.x, gGroundLevel, shot->obj.pos.z, 0.1f, 1.5f, shot->obj.rot.y + 20.0f);
        func_effect_8007ACE0(shot->obj.pos.x, gGroundLevel, shot->obj.pos.z, 0.1f, 1.5f, shot->obj.rot.y - 20.0f);
    }
    if ((shot->obj.pos.y < gGroundLevel) && (D_ctx_801784AC != 4)) {
        func_beam_80036318(shot);
        shot->obj.pos.y = gGroundLevel + 2;
        if (gCurrentLevel == LEVEL_BOLSE) {
            func_effect_8007A6F0(&shot->obj.pos, 0x29121007);
        }
        if ((gCamCount != 4) && (gCurrentLevel != LEVEL_AQUAS)) {
            if ((shot->playerNum == 0) && (gLaserStrength[0] != LASERS_SINGLE) &&
                (gPlayer[0].form != FORM_LANDMASTER)) {
                Matrix_RotateY(gCalcMatrix, shot->obj.rot.y * M_DTOR, 0);
                Matrix_RotateX(gCalcMatrix, shot->obj.rot.x * M_DTOR, 1);
                Matrix_RotateZ(gCalcMatrix, shot->obj.rot.z * M_DTOR, 1);
                sp44.y = sp44.z = 0.0f;
                sp44.x = 40.0f;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp44, &sp38);
                func_beam_80036770(shot->obj.pos.x + sp38.x, gGroundLevel + 2.0f, shot->obj.pos.z + sp38.z,
                                   shot->obj.rot.y, 2.0f);
                sp44.x = -40.0f;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp44, &sp38);
                func_beam_80036770(shot->obj.pos.x + sp38.x, gGroundLevel + 2.0f, shot->obj.pos.z + sp38.z,
                                   shot->obj.rot.y, 2.0f);
            } else {
                func_beam_80036770(shot->obj.pos.x, gGroundLevel + 2.0f, shot->obj.pos.z, shot->obj.rot.y, 2.0f);
            }
        }
        if (gGroundType == GROUNDTYPE_WATER) {
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
    if (shot->unk_64 == 0) {
        Object_Kill(&shot->obj, shot->sfxSource);
        return;
    } else if ((shot->playerNum < 110) || ((shot->unk_64 % 2) != 0)) {
        func_beam_80038140(shot);
    }
}

void func_beam_8003BA80(PlayerShot* shot) {
    func_beam_8003B55C(shot, 0);
}

void func_beam_8003BAA0(PlayerShot* shot) {
    func_beam_8003B55C(shot, 0);
    shot->unk_58 = 0;
}

void func_beam_8003BACC(PlayerShot* shot) {
    Vec3f sp3C;
    Vec3f sp30;
    Vec3f sp24;

    func_beam_8003B55C(shot, 0);
    sp3C.x = shot->obj.pos.x;
    sp3C.y = shot->obj.pos.y;
    sp3C.z = shot->obj.pos.z;
    sp30.x = 0.0f;
    sp30.y = 0.0f;
    sp30.z = 0.0f;
    if (!func_col2_800A3690(&sp3C, &sp30, COL2_5, &sp24)) {
        func_beam_80036318(shot);
    }
    shot->unk_58 = 0;
}

bool func_beam_8003BB4C(PlayerShot* shot) {
    s32 i;
    s32 j;
    f32 var_fa0;
    Actor* actor;
    Player* player;

    if (gLevelMode == LEVELMODE_ON_RAILS) {
        var_fa0 = 300.0f;
    } else {
        var_fa0 = 200.0f;
    }
    for (i = 0, actor = gActors; i < 60; i++, actor++) {
        if ((actor->obj.status == OBJ_ACTIVE) && (actor->info.unk_1C != 0.0f) &&
            ((actor->timer_0CA[shot->playerNum] == 0) && (fabsf(shot->obj.pos.x - actor->obj.pos.x) <= var_fa0) &&
             (fabsf(shot->obj.pos.y - (actor->obj.pos.y + actor->info.unk_1C)) <= var_fa0) &&
             (fabsf(shot->obj.pos.z - actor->obj.pos.z) <= var_fa0))) {
            actor->timer_0CA[shot->playerNum] = 20;
            func_enmy_80060F30(gPlayer[shot->playerNum].sfxSource, 0x49008027, shot->playerNum);
            for (j = 0; j < ARRAY_COUNT(gPlayerShots); j++) {
                if (gPlayerShots[j].obj.id == PLAYERSHOT_4) {
                    Object_Kill(&gPlayerShots[j].obj, gPlayerShots[j].sfxSource);
                }
            }
            D_display_801615B8[shot->playerNum] = 3.0f;
            D_display_801615A8[shot->playerNum] = 300.0f;
            return true;
        }
    }
    if (gVersusMode) {
        for (i = 0, player = gPlayer; i < gCamCount; i++, player++) {
            if ((player->state_1C8 == PLAYERSTATE_1C8_3) && (player->unk_4DC == 0) && (player->form != FORM_ON_FOOT) &&
                (i != shot->playerNum) && (D_ctx_80177B00[i][shot->playerNum] == 0) &&
                (fabsf(shot->obj.pos.x - player->pos.x) <= var_fa0) &&
                (fabsf(shot->obj.pos.y - player->pos.y) <= var_fa0) &&
                (fabsf(shot->obj.pos.z - player->unk_138) <= var_fa0)) {
                D_ctx_80177B00[0][shot->playerNum] = D_ctx_80177B00[1][shot->playerNum] =
                    D_ctx_80177B00[2][shot->playerNum] = D_ctx_80177B00[3][shot->playerNum] = 0;
                D_ctx_80177B00[i][shot->playerNum] = 20;
                func_enmy_80060F30(gPlayer[shot->playerNum].sfxSource, 0x49008027, shot->playerNum);
                for (j = 0; j < ARRAY_COUNT(gPlayerShots); j++) {
                    if (gPlayerShots[j].obj.id == PLAYERSHOT_4) {
                        Object_Kill(&gPlayerShots[j].obj, gPlayerShots[j].sfxSource);
                    }
                }
                D_display_801615B8[shot->playerNum] = 3.0f;
                D_display_801615A8[shot->playerNum] = 300.0f;
                return true;
            }
        }
    }
    return false;
}

void func_beam_8003BEF4(PlayerShot* shot) {
    if (gVersusMode) {
        if ((shot->obj.pos.y < gGroundLevel) || func_beam_8003BB4C(shot) ||
            !(gControllerHold[shot->playerNum].button & A_BUTTON) || (shot->unk_64 == 0)) {
            Object_Kill(&shot->obj, shot->sfxSource);
        }
    } else {
        if ((shot->obj.pos.y < gGroundLevel) || func_beam_8003BB4C(shot) ||
            !(gControllerHold[gMainController].button & A_BUTTON) || (shot->unk_64 == 0)) {
            Object_Kill(&shot->obj, shot->sfxSource);
        }
    }
    func_beam_80038140(shot);
}

void func_beam_8003C008(PlayerShot* shot) {
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
            if (boss->obj.id == OBJ_BOSS_316) {
                var_s6 = gGameFrameCount % 8U;
                var_fs2 = shot->unk_44 * 40.0f;
            } else {
                var_s6 = gGameFrameCount % 16U;
                var_fs2 = shot->unk_44 * 30.0f;
            }
            hitboxData = boss->info.hitbox;
            count = *hitboxData++;
            if (count != 0) {
                for (j = 0; j < count; j++, hitboxData += 6) {
                    if (hitboxData[0] == HITBOX_TYPE_2) {
                        Matrix_RotateZ(gCalcMatrix, -hitboxData[3] * M_DTOR, 0);
                        Matrix_RotateX(gCalcMatrix, -hitboxData[1] * M_DTOR, 1);
                        Matrix_RotateY(gCalcMatrix, -hitboxData[2] * M_DTOR, 1);
                        Matrix_RotateZ(gCalcMatrix, -boss->obj.rot.z * M_DTOR, 1);
                        Matrix_RotateX(gCalcMatrix, -boss->obj.rot.x * M_DTOR, 1);
                        Matrix_RotateY(gCalcMatrix, -boss->obj.rot.y * M_DTOR, 1);
                        hitboxData += 4;
                    } else {
                        Matrix_RotateZ(gCalcMatrix, -boss->obj.rot.z * M_DTOR, 0);
                        Matrix_RotateX(gCalcMatrix, -boss->obj.rot.x * M_DTOR, 1);
                        Matrix_RotateY(gCalcMatrix, -boss->obj.rot.y * M_DTOR, 1);
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

void func_beam_8003C3D8(PlayerShot* shot) {
    static u8 D_800C9C18[4] = { 255, 255, 32, 32 };
    static u8 D_800C9C1C[4] = { 255, 32, 255, 32 };
    static u8 D_800C9C20[4] = { 32, 32, 32, 255 };
    f32 var_fv0;

    D_ctx_80178370 = shot->obj.pos.x;
    D_ctx_80178374 = shot->obj.pos.y;
    D_ctx_80178378 = shot->obj.pos.z;
    if (gVersusMode) {
        D_ctx_80178360 = D_800C9C18[shot->playerNum];
        D_ctx_80178364 = D_800C9C1C[shot->playerNum];
        D_ctx_80178368 = D_800C9C20[shot->playerNum];
    } else {
        D_ctx_80178360 = 90;
        D_ctx_80178364 = 90;
        D_ctx_80178368 = 255;
    }
    var_fv0 = 0.7f;
    if (shot->unk_5C != 0) {
        var_fv0 = 1.0f;
    }
    Math_SmoothStepToF(&D_ctx_8017836C, var_fv0, 1.0f, 0.08f, 0.001f);
}

void func_beam_8003C4D0(PlayerShot* shot, s32 damage) {
    s32 i;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    s32 pad[2];
    Actor* actor;
    Sprite* sprite;
    Object_80* obj80;
    Effect* effect;
    Player* player;
    f32 temp_fs2 = shot->unk_44 * 60.0f;

    for (i = 0, obj80 = gObjects80; i < 50; i++, obj80++) {
        if ((obj80->obj.status == OBJ_ACTIVE) && (obj80->obj.id == OBJ_80_56)) {
            sp68 = obj80->obj.pos.x - shot->obj.pos.x;
            sp64 = obj80->obj.pos.y - shot->obj.pos.y;
            sp60 = obj80->obj.pos.z - shot->obj.pos.z;
            if (sqrtf(SQ(sp68) + SQ(sp64) + SQ(sp60)) < temp_fs2) {
                obj80->dmgType = 2;
            }
            obj80->dmgPart = 0;
        }
    }
    for (i = 0, sprite = gSprites; i < 40; i++, sprite++) {
        if ((sprite->obj.status == OBJ_ACTIVE) &&
            ((sprite->obj.id == OBJ_SPRITE_FO_POLE) || (sprite->obj.id == OBJ_SPRITE_TI_CACTUS) ||
             (sprite->obj.id == OBJ_SPRITE_CO_POLE) || (sprite->obj.id == OBJ_SPRITE_CO_TREE))) {
            sp68 = sprite->obj.pos.x - shot->obj.pos.x;
            sp64 = sprite->obj.pos.y - shot->obj.pos.y;
            sp60 = sprite->obj.pos.z - shot->obj.pos.z;
            if (sqrtf(SQ(sp68) + SQ(sp64) + SQ(sp60)) < temp_fs2) {
                sprite->unk_46 = 1;
            }
        }
    }
    actor = gActors;
    for (i = 0; i < 60; i++, actor++) {
        if ((actor->obj.status == OBJ_ACTIVE) && (actor->timer_0C2 == 0) &&
            !((gCurrentLevel == LEVEL_MACBETH) && (OBJ_ACTOR_205 <= actor->obj.id) &&
              (actor->obj.id < OBJ_ACTOR_214)) &&
            !((actor->obj.id == OBJ_ACTOR_EVENT) && (actor->iwork[12] != 0)) &&
            ((actor->scale >= 0.0f) || (actor->obj.id == OBJ_ACTOR_271))) {
            sp68 = actor->obj.pos.x - shot->obj.pos.x;
            sp64 = actor->obj.pos.y - shot->obj.pos.y;
            sp60 = actor->obj.pos.z - shot->obj.pos.z;
            if ((gLevelMode == 0) && (sp60 < 0.0f)) {
                sp60 *= 0.6f;
            }
            actor->unk_0D8.x = shot->obj.pos.x;
            actor->unk_0D8.y = shot->obj.pos.y;
            actor->unk_0D8.z = shot->obj.pos.z;
            if (sqrtf(SQ(sp68) + SQ(sp64) + SQ(sp60)) < temp_fs2) {
                if ((actor->obj.id == OBJ_ACTOR_193) || (actor->obj.id == OBJ_ACTOR_186) ||
                    (actor->obj.id == OBJ_ACTOR_190) || (actor->obj.id == OBJ_ACTOR_202) ||
                    (actor->obj.id == OBJ_ACTOR_201) || (actor->obj.id == OBJ_ACTOR_187) ||
                    ((actor->obj.id == OBJ_ACTOR_EVENT) && (actor->unk_0B4 == 78)) ||
                    ((actor->obj.id == OBJ_ACTOR_EVENT) && (actor->unk_0B4 == 38)) ||
                    (actor->obj.id == OBJ_ACTOR_196)) {
                    actor->unk_0D0 = 2;
                    actor->unk_0D2 = 0;
                    actor->unk_0D4 = shot->playerNum + 1;
                    actor->damage = damage;

                    if (actor->info.bonus != 0) {
                        shot->bonus++;
                    }
                } else if ((actor->obj.id == OBJ_ACTOR_EVENT) && (actor->scale >= 0.5f) && (damage > 30)) {
                    actor->unk_0D4 = shot->playerNum + 1;
                    actor->vel.x = sp68 * 0.03f;
                    actor->vel.y = sp64 * 0.03f;
                    actor->vel.z = sp60 * 0.03f;
                    actor->obj.status = OBJ_DYING;
                    actor->timer_0BC = RAND_INT(15.0f) + 10;
                    actor->timer_0BE = 0;
                    actor->timer_04C = 4;
                    actor->obj.rot.x = Math_ModF(actor->obj.rot.x, 360.0f);
                    if (actor->info.bonus != 0) {
                        shot->bonus++;
                    }
                } else {
                    actor->unk_0D0 = 2;
                    actor->unk_0D2 = 0;
                    actor->unk_0D4 = shot->playerNum + 1;
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
        func_beam_8003C008(shot);
    }
    effect = gEffects;
    for (i = 0; i < 100; i++, effect++) {
        if (effect->obj.status == OBJ_ACTIVE) {
            sp68 = effect->obj.pos.x - shot->obj.pos.x;
            sp64 = effect->obj.pos.y - shot->obj.pos.y;
            sp60 = effect->obj.pos.z - shot->obj.pos.z;
            if (sqrtf(SQ(sp68) + SQ(sp64) + SQ(sp60)) < temp_fs2) {
                if (effect->info.unk_16 == 0) {
                    Object_Kill(&effect->obj, effect->sfxSource);
                }
                if (effect->info.unk_16 == 2) {
                    effect->obj.pos.x += sp68 * 0.03f;
                    if (!((gLevelType == LEVELTYPE_PLANET) && (effect->obj.pos.y < 100.0f))) {
                        effect->obj.pos.y += sp64 * 0.03f;
                    }
                    effect->obj.pos.z += sp60 * 0.03f;
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
        for (i = 0, player = gPlayer; i < gCamCount; i++, player++) {
            if ((i != shot->playerNum) && (player->state_1C8 == PLAYERSTATE_1C8_3) && (player->unk_1F4 == 0)) {
                sp68 = player->pos.x - shot->obj.pos.x;
                sp64 = player->pos.y - shot->obj.pos.y;
                sp60 = player->unk_138 - shot->obj.pos.z;
                if (sqrtf(SQ(sp68) + SQ(sp64) + SQ(sp60)) < temp_fs2) {
                    player->unk_288 = shot->playerNum + 1;
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

void func_beam_8003CC08(PlayerShot* shot) {
    Vec3f test;
    f32 var_ft5;

    switch (shot->unk_5C) {
        case 0:
            if (shot->unk_64 == 0) {
                func_beam_80035E78(shot);
                break;
            }
            if ((shot->obj.pos.y < gGroundLevel) && (D_ctx_801784AC != 4)) {
                func_beam_80035E78(shot);
                break;
            }
            if ((gPlayer[shot->playerNum].form == FORM_LANDMASTER) || (gPlayer[shot->playerNum].form == FORM_ON_FOOT)) {
                shot->vel.y -= 1.0f;
                Math_SmoothStepToF(&shot->obj.rot.x, -90.0f, 0.05f, 1.0f, 0.0f);
            }
            if (shot->unk_64 < 25) {
                if (gVersusMode) {
                    if (gControllerPress[shot->playerNum].button & gBombButton[shot->playerNum]) {
                        func_beam_80035E78(shot);
                        break;
                    }
                } else {
                    if (gControllerPress[gMainController].button & gBombButton[shot->playerNum]) {
                        func_beam_80035E78(shot);
                        break;
                    }
                }
            }
            if (!((gCurrentLevel == LEVEL_VENOM_ANDROSS) && (gBosses[0].obj.status == OBJ_ACTIVE) &&
                  (gBosses[0].state == 17))) {
                func_beam_80038140(shot);
            }
            func_beam_8003C3D8(shot);
            break;
        case 1:
            D_ctx_8017812C = 2;
            shot->obj.rot.y += 1.0f;
            Math_SmoothStepToF(&shot->unk_44, shot->unk_48, 0.05f, 1.5f, 0.001f);
            if ((shot->unk_64 > 0) && (shot->unk_64 < 30)) {
                if (!gVersusMode &&
                    ((gPlayer[0].state_1C8 == PLAYERSTATE_1C8_3) || (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_5))) {
                    test.x = gPlayer[0].pos.x - shot->obj.pos.x;
                    test.y = gPlayer[0].pos.y - shot->obj.pos.y;
                    test.z = gPlayer[0].unk_138 - shot->obj.pos.z;
                    var_ft5 = VEC3F_MAG(&test) * 0.01f;
                    if (var_ft5 > 60.0f) {
                        var_ft5 = 60.0f;
                    }
                    var_ft5 = 60.0f - var_ft5;
                    Math_SmoothStepToF(&D_ctx_801779A8[gMainController], var_ft5 + 5.0f, 1.0f, 3.0f, 0.0f);
                }
                func_beam_8003C3D8(shot);
            }
            if (shot->unk_64 == 0) {
                shot->unk_58 -= 8;
                if (shot->unk_58 < 0) {
                    shot->unk_58 = 0;
                    Object_Kill(&shot->obj, shot->sfxSource);
                    D_ctx_8017812C = 0;
                }
            }
            func_beam_8003C4D0(shot, 50);
            break;
    }
}

static Vec3f D_800C9C24 = { 0.0f, 0.0f, 0.0f };
void func_beam_8003CF90(PlayerShot* shot) {
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

    if ((shot->obj.pos.y < gGroundLevel) || (shot->unk_64 == 1)) {
        if ((gGroundType == GROUNDTYPE_WATER) && (shot->obj.pos.y < gGroundLevel)) {
            shot->unk_48 = 10.0f;
            func_effect_8007D9DC(shot->obj.pos.x, gGroundLevel + 2.0f, shot->obj.pos.z, shot->unk_48 * 0.1f,
                                 shot->unk_48 * 3.0f, 0);
            func_effect_8007D9DC(shot->obj.pos.x, gGroundLevel + 2.0f, shot->obj.pos.z, shot->unk_48 * 0.1f,
                                 shot->unk_48 * 3.0f, 5);
            func_effect_8007ADF4(shot->obj.pos.x, gGroundLevel, shot->obj.pos.z, shot->unk_48 * 0.05f,
                                 shot->unk_48 * 0.5f);
            func_effect_8007A6F0(&shot->obj.pos, 0x19000014);
        }
        func_beam_80036318(shot);
    } else {
        var_a3 = 0;
        if (shot->unk_60 == 0) {
            for (i = 0, actor = gActors; i < 60; i++, actor++) {
                if ((actor->obj.status == OBJ_ACTIVE) && (actor->info.unk_1C != 0.0f) &&
                    (actor->timer_0CA[shot->playerNum] != 0)) {
                    var_a3 = 1;
                    actor->timer_0CA[shot->playerNum] = 2;
                    D_800C9C24 = actor->obj.pos;
                    D_800C9C24.y += actor->info.unk_1C;
                }
            }
            for (i = 0, player = gPlayer; i < gCamCount; i++, player++) {
                if (((player->state_1C8 == PLAYERSTATE_1C8_3) || (player->state_1C8 == PLAYERSTATE_1C8_5)) &&
                    (D_ctx_80177B00[i][shot->playerNum] != 0)) {
                    var_a3 = 1;
                    D_ctx_80177B00[i][shot->playerNum] = 2;
                    D_800C9C24.x = player->pos.x;
                    if (player->form == FORM_ARWING) {
                        D_800C9C24.y = player->pos.y;
                    } else {
                        D_800C9C24.y = player->pos.y + 30.0f;
                    }
                    D_800C9C24.z = player->unk_138;
                }
            }
            if (var_a3 != 0) {
                sp6C = shot->obj.pos.x - D_800C9C24.x;
                sp68 = shot->obj.pos.y - D_800C9C24.y;
                sp64 = shot->obj.pos.z - D_800C9C24.z;
                sp58 = Math_RadToDeg(Math_Atan2F(sp6C, sp64));
                sp5C = Math_RadToDeg(-Math_Atan2F(sp68, sqrtf(SQ(sp6C) + SQ(sp64))));
                if (shot->unk_30 >= 360.0f) {
                    shot->unk_30 -= 360.0f;
                }
                if (shot->unk_30 < 0.0f) {
                    shot->unk_30 += 360.0f;
                }
                if (shot->unk_2C >= 360.0f) {
                    shot->unk_2C -= 360.0f;
                }
                if (shot->unk_2C < 0.0f) {
                    shot->unk_2C += 360.0f;
                }
                Math_SmoothStepToAngle(&shot->unk_30, sp58, 1.0f, shot->unk_50, 0.0f);
                Math_SmoothStepToAngle(&shot->unk_2C, sp5C, 1.0f, shot->unk_50, 0.0f);
                shot->unk_64 = 30;
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
        if (!((gPlayer[shot->playerNum].form == FORM_LANDMASTER) && (shot->unk_60 != 0))) {
            Vec3f sp44;
            Vec3f sp38;

            shot->obj.rot.y = shot->unk_30;
            shot->obj.rot.x = shot->unk_2C;
            Matrix_RotateY(gCalcMatrix, shot->obj.rot.y * M_DTOR, 0);
            Matrix_RotateX(gCalcMatrix, shot->obj.rot.x * M_DTOR, 1);
            sp44.x = sp44.y = 0.0f;
            sp44.z = -(shot->unk_54 + 40.0f);
            Matrix_MultVec3f(gCalcMatrix, &sp44, &sp38);
            shot->vel.x = sp38.x;
            shot->vel.y = sp38.y;
            shot->vel.z = sp38.z;
        }
        func_beam_80038140(shot);
        D_ctx_80178370 = shot->obj.pos.x;
        D_ctx_80178374 = shot->obj.pos.y;
        D_ctx_80178378 = shot->obj.pos.z;
        D_ctx_80178360 = 90;
        D_ctx_80178364 = 180;
        D_ctx_80178368 = 90;
        Math_SmoothStepToF(&D_ctx_8017836C, 0.6f, 1.0f, 0.08f, 0.001f);
    }
}

void func_beam_8003D54C(PlayerShot* shot, s32 index) {
    s32 teamId;
    s32 bonus;

    shot->obj.pos.x += shot->vel.x;
    shot->obj.pos.y += shot->vel.y;
    shot->obj.pos.z += shot->vel.z;
    switch (shot->obj.id) {
        case PLAYERSHOT_0:
            func_beam_8003B55C(shot, index);
            break;
        case PLAYERSHOT_1:
        case PLAYERSHOT_9:
            func_beam_8003B55C(shot, index);
            break;
        case PLAYERSHOT_2:
            func_beam_8003B00C(shot, &gPlayer[shot->playerNum]);
            break;
        case PLAYERSHOT_3:
            func_beam_8003CC08(shot);
            break;
        case PLAYERSHOT_4:
            func_beam_8003BEF4(shot);
            break;
        case PLAYERSHOT_5:
            func_beam_8003BA80(shot);
            break;
        case PLAYERSHOT_6:
            func_beam_8003BAA0(shot);
            break;
        case PLAYERSHOT_7:
            func_beam_8003BACC(shot);
            break;
        case PLAYERSHOT_8:
            if (shot->unk_44 > 1.5f) {
                func_beam_8003C4D0(shot, 30);
                if (shot->bonus != 0) {
                    if (gVersusMode) {
                        D_ctx_80177C30[shot->playerNum] += shot->bonus;
                    } else {
                        bonus = shot->bonus;
                        if (shot->bonus > 10) {
                            bonus = BONUS_TEXT_GREAT;
                        }
                        BonusText_Display(shot->obj.pos.x, shot->obj.pos.y, shot->obj.pos.z, bonus);
                        gHitCount += shot->bonus;
                    }
                    if ((shot->bonus >= 7) && (gBossActive == 0) && (gLevelMode == LEVELMODE_ON_RAILS) &&
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
                func_effect_8007A6F0(&shot->obj.pos, 0x0903502E);
            } else if (gCurrentLevel == LEVEL_AQUAS) {
                Aquas_801ABA40(shot);
            } else {
                func_beam_8003CF90(shot);
            }
            break;
    }
}

void func_beam_8003D854(PlayerShot* shot) {
    s32 i;
    s32 var_s5;

    switch (shot->obj.status) {
        case 0:
            break;
        case 1:
            var_s5 = 1;
            switch (shot->obj.id) {
                case PLAYERSHOT_9:
                    var_s5 = 4;
                    break;
                case PLAYERSHOT_0:
                case PLAYERSHOT_1:
                    if ((shot->unk_58 == 0) || (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_2)) {
                        var_s5 = 4;
                    } else {
                        var_s5 = 3;
                    }
                    break;
                case PLAYERSHOT_5:
                    var_s5 = 2;
                    break;
            }
            for (i = 0; i < var_s5 && (shot->obj.status == 1); i++) {
                if (shot->unk_64 > 0) {
                    shot->unk_64--;
                }
                D_ctx_80178498 = shot->obj.pos.z;
                D_ctx_801784A0 = shot->obj.pos.y;
                D_ctx_8017849C = shot->obj.pos.x;
                func_beam_8003D54C(shot, i);
            }
            break;
        case 2:
            func_beam_8003AFD8(shot);
            break;
    }
}

void PlayerShot_Update(void) {
    s32 i;

    for (i = 0; i < 16; i++) {
        gPlayerShots[i].index = i;
        func_beam_8003D854(&gPlayerShots[i]);
    }
}

void PlayerShot_Draw(void) {
    s32 i;

    for (i = 0; i < 16; i++) {
        gPlayerShots[i].index = i;
        if (gPlayerShots[i].obj.status != 0) {
            if (!((gReflectY < 0) && (gPlayerShots[i].obj.rot.x < -10.0f))) {
                Matrix_Push(&gGfxMatrix);
                func_beam_8003AF88(&gPlayerShots[i]);
                Matrix_Pop(&gGfxMatrix);
            }
            if (gReflectY > 0) {
                func_edisplay_8005F290(gPlayerShots[i].sfxSource, &D_beam_8015F950);
            }
        }
    }
}
