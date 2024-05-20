/*
 * File: fox_me.c
 * System: Meteo
 * Description: Level: Meteo
 */

#include "global.h"
#include "assets/ast_meteo.h"

Vec3f D_i2_80195430[] = {
    { 122.0, -5.0, -1200.0 },   { 122.0, -103.0, -727.0 }, { 142.0, -323.0, -848.0 }, { 362.0, -59.0, -435.0 },
    { 692.0, -84.0, -308.0 },   { 1000.0, -7.0, -308.0 },  { 164.0, -700.0, -308.0 }, { 263.0, -370.0, -11.0 },
    { 307.0, -95.0, 36.0 },     { 307.0, -95.0, 36.0 },    { -122.0, -5.0, -1200.0 }, { -122.0, -103.0, -727.0 },
    { -142.0, -323.0, -848.0 }, { -362.0, -59.0, -435.0 }, { -692.0, -84.0, -308.0 }, { -1000.0, -7.0, -308.0 },
    { -164.0, -700.0, -308.0 }, { -263.0, -370.0, -11.0 }, { -307.0, -95.0, 36.0 },   { -307.0, -95.0, 36.0 },
};

s32 D_i2_80195520[] = { 80, 70, 60, 50, 0 };

f32 D_i2_80195534[] = { 0.15f, 0.45f, 0.75f, 1.3f, 0.75f, 0.45f, 0.15f, 0.0f };

f32 D_i2_80195554[] = { 101.0f, 96.0f, 85.0f, 80.0f, 69.0f, 64.0f, 53.0f, 48.0f, 37.0f, 32.0f, 21.0f, 16.0f };

f32 D_i2_80195584[] = { 180.0f, -180.0f, 0.0f, -1500.0f };

f32 D_i2_80195594[] = { 50.0f, 100.0f, -50.0f, 0.0f };

f32 D_i2_801955A4[] = { 240.0f, 480.0f, 720.0f, -5000.0f };

s32 D_i2_801955B4[] = { 0, 0, 0, 1 };

Vec3f D_i2_801955C4 = { 0.0f, 0.0f, 100.0f };

Vec3f D_i2_801955D0[] = { 2000.0f, 2000.0f,  2000.0f, -2000.0f, 2000.0f,  2000.0f,
                          0.0f,    -3000.0f, 3000.0f, 5000.0f,  -3000.0f, -3000.0f };

f32 D_i2_80195600[] = { 75.0f, -80.0f, 85.0f, 0.0f };

Vec3f D_i2_80195610[] = {
    { 200.0f, -10.0f, 200.0f },
    { -200.0f, 20.0f, 200.0f },
    { 0.0f, 50.0f, 400.0f },
    { -2000.0f, -1000.0f, 0.0f },
};

void Meteo_80187530(Actor* actor) {
    if (actor->dmgType == DMG_BEAM) {
        actor->dmgType = DMG_NONE;
        func_effect_8007A6F0(&actor->obj.pos, NA_SE_ROCK_REFLECT);
    }
}

void Meteo_8018756C(Actor* actor) {
    Vec3f vec;

    if (actor->dmgType != DMG_NONE) {
        actor->dmgType = DMG_NONE;
        actor->health -= actor->damage;
        if (actor->health <= 0) {
            actor->obj.status = OBJ_DYING;
        }
    }

    actor->obj.rot.y += 2.0f;
    actor->obj.rot.x += 1.3f;

    vec.x = actor->vel.x;
    vec.y = actor->vel.y;
    vec.z = actor->vel.z;

    if ((Object_CheckCollision(actor->index, &actor->obj.pos, &vec, 0) != 0) ||
        (actor->obj.pos.y < (gGroundHeight + 20.0f))) {
        actor->obj.status = OBJ_DYING;
    }
    Meteo_80187530(actor);
}

void Meteo_80187650(Actor* actor) {
    Vec3f vec;

    actor->obj.rot.y += 1.7f;
    actor->obj.rot.x += 3.3f;
    actor->unk_046 -= 15;

    if (actor->unk_046 < 0) {
        actor->unk_046 = 0;
    }

    actor->unk_048 += 8;
    if (actor->unk_048 > 995) {
        actor->unk_048 = 995;
    }

    if ((actor->timer_0BC % 4U) == 1) {
        func_effect_8007D0E0(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, 6.0f);
    }

    if (actor->dmgType != DMG_NONE) {
        func_effect_8007A6F0(&actor->obj.pos, NA_SE_EN_EXPLOSION_S);
        func_effect_8007D2C8(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, 10.0f);
        Object_Kill(&actor->obj, actor->sfxSource);
    }

    if (actor->timer_0C2 == 0) {
        vec.x = actor->vel.x;
        vec.y = actor->vel.y;
        vec.z = actor->vel.z;
        if ((Object_CheckCollision(actor->index, &actor->obj.pos, &vec, 0) != 0) ||
            (actor->obj.pos.y < (gGroundHeight + 20.0f))) {
            func_effect_8007D2C8(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, 10.0f);
            actor->obj.status = OBJ_DYING;
        }
    }

    Meteo_80187530(actor);
}

void Meteo_801877C4(Actor* actor) {
    Vec3f sp44;
    Vec3f sp38;

    actor->obj.rot.z += 1.0f;

    Matrix_RotateZ(gCalcMatrix, actor->obj.rot.z * M_DTOR, MTXF_NEW);

    sp38.x = 0.0f;
    sp38.y = -1100.0f;
    sp38.z = 0.0f;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp38, &sp44);

    actor->obj.pos.x = actor->fwork[0] + sp44.x;
    actor->obj.pos.y = actor->fwork[1] + sp44.y;

    if (actor->dmgType != DMG_NONE) {
        Actor_Despawn(actor);
        func_effect_8007A6F0(&actor->obj.pos, NA_SE_EN_EXPLOSION_S);
        Object_Kill(&actor->obj, actor->sfxSource);
        func_effect_8007D0E0(actor->obj.pos.x, actor->obj.pos.y + 30.0f, actor->obj.pos.z, 5.0f);
        func_effect_8007BFFC(actor->obj.pos.x, actor->obj.pos.y + 30.0f, actor->obj.pos.z, 0.0f, 0.0f, 0.0f, 3.0f, 10);
    }

    if (actor->timer_0BC == 0) {
        actor->timer_0BC = 40;
        if (actor->obj.pos.z < (gPlayer[0].trueZpos - 1000.0f)) {
            func_effect_8007F11C(OBJ_EFFECT_353, actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, 120.0f);
        }
    }
}

void Meteo_8018795C(Actor* actor) {
    Vec3f vec;
    s32 pad[2];

    actor->obj.rot.y += 7.0f;
    actor->obj.rot.x += 3.3f;

    if (actor->dmgType != DMG_NONE) {
        Actor_Despawn(actor);
        func_effect_8007A6F0(&actor->obj.pos, NA_SE_EN_EXPLOSION_S);
        Object_Kill(&actor->obj, actor->sfxSource);
        func_effect_8007D0E0(actor->obj.pos.x - actor->vel.x, actor->obj.pos.y, actor->obj.pos.z - actor->vel.z, 8.0f);
        func_effect_8007BFFC(actor->obj.pos.x - actor->vel.x, actor->obj.pos.y + 30.0f, actor->obj.pos.z - actor->vel.z,
                             0.0f, 0.0f, 0.0f, 4.0f, 10);
    }

    if (((gGameFrameCount % 8) == 0)) {
        Math_Vec3fFromAngles(&vec, actor->obj.rot.x, actor->obj.rot.y, 100.0f);
        func_effect_8007F04C(OBJ_EFFECT_353, actor->obj.pos.x + (vec.x * 3.0f), actor->obj.pos.y + (vec.y * 3.0f),
                             actor->obj.pos.z + (vec.z * 3.0f), actor->obj.rot.x, actor->obj.rot.y, actor->obj.rot.z,
                             0.0f, 0.0f, 0.0f, vec.x, vec.y, vec.z, 1.0f);
    }
}

void Meteo_80187B08(Actor* actor) {
    actor->obj.rot.y += 7.0f;
    actor->obj.rot.x += 3.3f;

    actor->unk_046 -= 11;

    if (actor->unk_046 < 0) {
        actor->unk_046 = 0;
    }

    actor->unk_048 += 4;
    if (actor->unk_048 > 995) {
        actor->unk_048 = 995;
    }

    if ((actor->timer_0BC & 3) == 0) {
        func_effect_8007D0E0(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, 6.0f);
    }

    if ((actor->dmgType != DMG_NONE) || (actor->timer_0BC == 0)) {
        func_effect_8007A6F0(&actor->obj.pos, NA_SE_EN_EXPLOSION_S);
        Object_Kill(&actor->obj, actor->sfxSource);
        func_effect_8007D0E0(actor->obj.pos.x - actor->vel.x, actor->obj.pos.y, actor->obj.pos.z - actor->vel.z, 8.0f);
        func_effect_8007BFFC(actor->obj.pos.x - actor->vel.x, actor->obj.pos.y + 30.0f, actor->obj.pos.z - actor->vel.z,
                             0.0f, 0.0f, 0.0f, 4.0f, 10);
    }
}

void Meteo_80187C68(Actor* actor, f32 x, f32 y, f32 z, f32 arg4, f32 xRot, f32 yRot, s32 timerBC, s32 arg8, s32 objId) {
    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.id = objId;

    actor->obj.pos.x = x;
    actor->obj.pos.y = y;
    actor->obj.pos.z = z;

    actor->obj.rot.x = xRot;
    actor->obj.rot.y = yRot;

    actor->timer_0BC = timerBC;
    actor->timer_0BE = 20;
    actor->eventType = arg8;
    actor->fwork[5] = arg4;
    Object_SetInfo(&actor->info, actor->obj.id);
}

void Meteo_80187D08(f32 x, f32 y, f32 z, f32 arg3, f32 xRot, f32 yRot, s32 arg6, s32 arg7, s32 objId) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gActors); i++) {
        if (gActors[i].obj.status == OBJ_FREE) {
            Meteo_80187C68(&gActors[i], x, y, z, arg3, xRot, yRot, arg6, arg7, objId);
            return;
        }
    }
}

void Meteo_80187D98(Effect* effect, f32 x, f32 y, f32 z, f32 arg4, bool arg5) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = OBJ_EFFECT_369;

    effect->obj.pos.x = x;
    effect->obj.pos.y = y;
    effect->obj.pos.z = z;

    effect->unk_60.z = arg4;
    effect->unk_48 = arg5;
    effect->obj.rot.x = 45.0f;

    if (arg5) {
        effect->obj.rot.x = -45.0f;
    }

    Object_SetInfo(&effect->info, effect->obj.id);
}

void Meteo_80187E38(f32 x, f32 y, f32 z, f32 arg3) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Meteo_80187D98(&gEffects[i], x, y, z, arg3, 0);
            AUDIO_PLAY_SFX(NA_SE_EN_S_BEAM_SHOT, gEffects[i].sfxSource, 4);
            break;
        }
    }

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Meteo_80187D98(&gEffects[i], x, y, z, arg3, 1);
            break;
        }
    }

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Meteo_80187D98(&gEffects[i], x, y, z, arg3 + 90.0f, 0);
            break;
        }
    }

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Meteo_80187D98(&gEffects[i], x, y, z, arg3 + 90.0f, 1);
            break;
        }
    }
}

void Meteo_80187FF8(Effect* effect, f32 x, f32 y, f32 z) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = OBJ_EFFECT_371;

    effect->obj.pos.x = x;
    effect->obj.pos.y = y;
    effect->obj.pos.z = z;

    effect->unk_44 = 128;
    effect->vel.z = 50.0f;
    effect->scale2 = 1.0f;
    Object_SetInfo(&effect->info, effect->obj.id);
}

void Meteo_80188088(Boss* boss) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Meteo_80187FF8(&gEffects[i], boss->obj.pos.x + 700.0f, boss->obj.pos.y, boss->obj.pos.z + 1235.0f);
            AUDIO_PLAY_SFX(NA_SE_EN_RNG_BEAM_SHOT, gEffects[i].sfxSource, 4);
            break;
        }
    }

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Meteo_80187FF8(&gEffects[i], boss->obj.pos.x - 700.0f, boss->obj.pos.y, boss->obj.pos.z + 1235.0f);
            break;
        }
    }
}

void Meteo_801881A8(Effect* effect, f32 x, f32 y, f32 z, f32 zRot, s32 arg5) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = OBJ_EFFECT_370;

    effect->obj.pos.x = x;
    effect->obj.pos.y = y;
    effect->obj.pos.z = z;

    effect->obj.rot.z = zRot;

    effect->state = arg5;
    Object_SetInfo(&effect->info, effect->obj.id);
}

void Meteo_80188228(f32 x, f32 y, f32 z, f32 zRot) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Meteo_801881A8(&gEffects[i], x, y, z, zRot, 0);
            break;
        }
    }
}

void Meteo_80188298(f32 x, f32 y, f32 z, f32 zRot) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Meteo_801881A8(&gEffects[i], x, y, z, zRot, -1);
            AUDIO_PLAY_SFX(NA_SE_EN_GRN_BEAM_SHOT, gEffects[i].sfxSource, 4);
            break;
        }
    }
}

void Meteo_80188344(Boss* boss) {
    Vec3f src;
    Vec3f dest;
    f32 temp;

    if (boss->state < 5) {
        boss->obj.pos.x = gBosses[0].obj.pos.x;
        boss->obj.pos.y = gBosses[0].obj.pos.y;
        boss->obj.pos.z = gBosses[0].obj.pos.z;
        boss->obj.rot.x = gBosses[0].obj.rot.x;
        boss->obj.rot.y = gBosses[0].obj.rot.y;
        boss->obj.rot.z = gBosses[0].obj.rot.z + boss->rot_078.z + 45.0f + 180.0f;
    }

    switch (boss->state) {
        case 0:
            boss->timer_050 = 150;
            boss->rot_078.z += 2.5f;
            break;

        case 1:
            temp = fabsf(90.0f - boss->rot_078.z) * 0.1f;
            if (temp > 2.5f) {
                temp = 2.5f;
            }

            boss->rot_078.z += temp;

            if (boss->timer_050 == 0) {
                boss->state = 2;
                boss->dmgType = DMG_NONE;
            }
            break;

        case 2:
            if (boss->dmgType == DMG_BEAM) {
                boss->dmgType = DMG_NONE;
                boss->timer_054 = 5;
                boss->swork[0] += 32;

                Audio_SetTransposeAndPlaySfx(boss->sfxSource, NA_SE_EN_GRN_BEAM_CHARGE, boss->unk_04A);

                boss->unk_04A++;
                if (boss->unk_04A > 7) {
                    boss->unk_04A = 7;
                }

                if (boss->swork[0] >= 255) {
                    boss->unk_04A = 0;
                    Audio_KillSfxBySource(boss->sfxSource);
                    if (boss->swork[1] == 0) {
                        boss->swork[1]++;
                        Radio_PlayMessage(gMsg_ID_3315, RCID_PEPPY);
                    }

                    boss->swork[0] = 0;

                    Matrix_RotateZ(gCalcMatrix, (boss->obj.rot.z - 45.0f) * M_DTOR, MTXF_NEW);

                    src.x = 0.0f;
                    src.y = 156.0f;
                    src.z = 930.0f;

                    Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

                    Meteo_80188298(boss->obj.pos.x + dest.x, boss->obj.pos.y + dest.y, boss->obj.pos.z + dest.z,
                                   boss->obj.rot.z - 45.0f);
                    Meteo_80188228(boss->obj.pos.x - dest.x, boss->obj.pos.y - dest.y, boss->obj.pos.z + dest.z,
                                   boss->obj.rot.z - 45.0f);
                    Meteo_80188228(boss->obj.pos.x + dest.y, boss->obj.pos.y - dest.x, boss->obj.pos.z + dest.z,
                                   (boss->obj.rot.z - 45.0f) + 90.0f);
                }
            }
            break;

        case 3:
            boss->timer_050 = 30;
            boss->state = 4;
            boss->timer_05C = 15;
            boss->swork[0] = 0;
            break;

        case 4:
            if (boss->timer_050 == 0) {
                func_effect_8007D2C8(boss->obj.pos.x, boss->obj.pos.y, boss->obj.pos.z + 500.0f, 30.0f);
                func_effect_8007BFFC(boss->obj.pos.x, boss->obj.pos.y, boss->obj.pos.z + 500.0f, 0.0f, 0.0f, 0.0f,
                                     20.0f, 30);
                boss->state = 5;

                boss->info.cullDistance = 1000.0f;

                Audio_KillSfxBySourceAndId(boss->sfxSource, NA_SE_EN_GRN_BEAM_CHARGE);
                AUDIO_PLAY_SFX(NA_SE_EN_MEBOSS_SHIELD, boss->sfxSource, 4);
            }
            break;

        case 5:
            boss->obj.rot.z -= 3.0f;
            if (boss->vel.z < 5.0f) {
                boss->vel.z = boss->vel.z + 1.0f;
            }
            break;
    }

    if (boss->rot_078.z >= 360.0f) {
        boss->rot_078.z -= 360.0f;
    }
    if (boss->rot_078.z < 0.0f) {
        boss->rot_078.z += 360.0f;
    }
}

void Meteo_801887D0(Boss* boss) {
    s32 i;

    if ((boss->timer_054 % 2) != 0) {
        RCP_SetupDL_27();
        gDPSetPrimColor(gMasterDisp++, 0, 0, 0, 255, 0, 255);
    }

    Matrix_RotateZ(gGfxMatrix, (M_PI / 4), MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_ME_60240B0);
    RCP_SetupDL_64();

    for (i = 1; i < 4; i++) {
        if (boss->swork[0] != 0) {
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, boss->swork[0]);
            Matrix_Push(&gGfxMatrix);
            Matrix_RotateZ(gGfxMatrix, M_DTOR * 90.0f * i, MTXF_APPLY);
            Matrix_Translate(gGfxMatrix, 0.0f, 156.0f, 930.0f, MTXF_APPLY);

            if ((gGameFrameCount % 2) != 0) {
                Matrix_Scale(gGfxMatrix, 6.0f, 9.0f, 5.0f, MTXF_APPLY);
            } else {
                Matrix_Scale(gGfxMatrix, 4.0f, 7.0f, 5.0f, MTXF_APPLY);
            }

            Matrix_RotateZ(gGfxMatrix, 1.5707964f, MTXF_APPLY); // (M_PI / 2) does not match
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_ME_60263F0);
            Matrix_Pop(&gGfxMatrix);
        }
    }
}

void Meteo_Boss297_Init(Boss297* this) {
    s32 i;

    AUDIO_PLAY_BGM(gBossBgms[gCurrentLevel]);

    gBossActive = true;

    this->swork[2] = 40;
    this->swork[3] = 40;
    this->swork[4] = 40;
    this->swork[5] = 40;
    this->swork[7] = 180;
    this->swork[8] = 180;
    this->swork[6] = 150;
    this->fwork[0] = -10.0f;
    this->fwork[9] = -3000.0f;
    this->fwork[15] = 8.0f;

    i = this->unk_044 = 1;

    Boss_Initialize(&gBosses[i]);

    gBosses[i].obj.status = OBJ_INIT;
    gBosses[i].obj.id = OBJ_BOSS_298;
    gBosses[i].obj.pos.x = this->obj.pos.x;
    gBosses[i].obj.pos.y = this->obj.pos.y;
    gBosses[i].obj.pos.z = this->obj.pos.z;

    Object_SetInfo(&gBosses[i].info, gBosses[i].obj.id);
    Radio_PlayMessage(gMsg_ID_3300, RCID_BOSS_METEO);
    AUDIO_PLAY_SFX(NA_SE_EN_BURNER_L, this->sfxSource, 4);
}

void Meteo_80188B84(Effect* effect, f32 x, f32 y, f32 z, f32 xRot, f32 yRot, f32 arg6, f32 arg7) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = OBJ_EFFECT_369;

    effect->obj.pos.x = x;
    effect->obj.pos.y = y;
    effect->obj.pos.z = z;

    effect->obj.rot.x = xRot;
    effect->obj.rot.y = yRot;
    effect->unk_60.z = arg6;

    effect->timer_50 = 20;
    effect->scale2 = arg7;
    effect->state = 1;
    effect->unk_44 = 128;
    Object_SetInfo(&effect->info, effect->obj.id);
}

void Meteo_80188C2C(f32 x, f32 y, f32 z, f32 xRot, f32 yRot, f32 arg5, f32 arg6) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Meteo_80188B84(&gEffects[i], x, y, z, xRot, yRot, arg5, arg6);
            return;
        }
    }
}

void Meteo_80188CAC(Effect* effect) {
    Vec3f src;
    Vec3f dest;

    if (effect->state == 0) {
        switch (effect->unk_48) {
            case 0:
                effect->obj.rot.x -= 15.0f;
                if (effect->obj.rot.x <= -45.0f) {
                    effect->unk_48 = 1;
                }
                break;

            case 1:
                effect->obj.rot.x += 15.0f;
                if (effect->obj.rot.x >= 45.0f) {
                    effect->unk_48 = 0;
                }
                break;
        }

        effect->unk_44 = 255;
        effect->scale2 = 1.0f;
        effect->unk_60.z += 20.0f;

        Matrix_RotateZ(gCalcMatrix, effect->unk_60.z * M_DTOR, MTXF_NEW);
        Matrix_RotateX(gCalcMatrix, effect->obj.rot.x * M_DTOR, MTXF_APPLY);

        src.x = 0.0f;
        src.y = 0.0f;
        src.z = 80.0f;

        Matrix_MultVec3f(gCalcMatrix, &src, &dest);

        effect->vel.x = dest.x;
        effect->vel.y = dest.y;
        effect->vel.z = dest.z;

        Meteo_80188C2C(effect->obj.pos.x, effect->obj.pos.y, effect->obj.pos.z, effect->obj.rot.x, effect->obj.rot.y,
                       effect->unk_60.z, 1.0f);
    } else if (effect->timer_50 == 0) {
        Object_Kill(&effect->obj, effect->sfxSource);
    }

    func_effect_8007A774(gPlayer, effect, 90.0f);
}

void Meteo_80188E8C(Effect* effect, f32 x, f32 y, f32 z, f32 xRot, f32 yRot, f32 zRot, f32 scale) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = OBJ_EFFECT_370;

    effect->obj.pos.x = x;
    effect->obj.pos.y = y;
    effect->obj.pos.z = z;

    effect->obj.rot.x = xRot;
    effect->obj.rot.y = yRot;
    effect->obj.rot.z = zRot;

    effect->scale2 = scale;
    effect->state = 1;
    effect->unk_44 = 128;
    Object_SetInfo(&effect->info, effect->obj.id);
}

void Meteo_80188F2C(f32 x, f32 y, f32 z, f32 xRot, f32 yRot, f32 arg5, f32 scale) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Meteo_80188E8C(&gEffects[i], x, y, z, xRot, yRot, arg5, scale);
            return;
        }
    }
}

void Meteo_80188FAC(Effect* effect) {
    Vec3f src;
    Vec3f dest;

    if (effect->state != 1) {
        effect->obj.rot.x = 10.0f;
        effect->obj.rot.z += 20.0f;

        Matrix_RotateZ(gCalcMatrix, effect->obj.rot.z * M_DTOR, MTXF_NEW);
        Matrix_RotateX(gCalcMatrix, effect->obj.rot.x * M_DTOR, MTXF_APPLY);

        src.x = 0.0f;
        src.y = 0.0f;
        src.z = 80.0f;

        Matrix_MultVec3f(gCalcMatrix, &src, &dest);

        effect->vel.x = dest.x;
        effect->vel.y = dest.y;
        effect->vel.z = dest.z;

        if (((gGameFrameCount % 2) == 0)) {
            Meteo_80188F2C(effect->obj.pos.x, effect->obj.pos.y, effect->obj.pos.z, effect->obj.rot.x,
                           effect->obj.rot.y, effect->obj.rot.z, 5.0f);
        }
    } else {
        effect->unk_44 -= 8;
        if (effect->unk_44 < 0) {
            Object_Kill(&effect->obj, effect->sfxSource);
        }
    }
    func_effect_8007A774(gPlayer, effect, 60.0f);
}

void Meteo_80189114(Effect* effect) {
    if (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_LEVEL_COMPLETE) {
        Object_Kill(&effect->obj, effect->sfxSource);
    }

    effect->scale2 += 0.5f;
    if (effect->scale2 > 10.0f) {
        effect->scale2 = 10.0f;
    }

    effect->obj.rot.z += 35.0f;
    if (effect->obj.pos.x < gPlayer[0].pos.x) {
        effect->obj.pos.x += 1.5f;
        if (effect->vel.x < 40.0f) {
            effect->vel.x += 2.0f;
        }
    }

    if (gPlayer[0].pos.x < effect->obj.pos.x) {
        effect->obj.pos.x -= 1.5f;
        if (effect->vel.x > -40.0f) {
            effect->vel.x -= 2.0f;
        }
    }

    if (effect->obj.pos.y < gPlayer[0].pos.y) {
        effect->obj.pos.y += 1.5f;
        if (effect->vel.y < 40.0f) {
            effect->vel.y += 2.0f;
        }
    }

    if (gPlayer[0].pos.y < effect->obj.pos.y) {
        effect->obj.pos.y -= 1.5f;
        if (effect->vel.y > -40.0f) {
            effect->vel.y -= 2.0f;
        }
    }

    func_effect_8007A774(gPlayer, effect, 100.0f);
}

void Meteo_801892F0(Boss* boss, s32 arg1) {
    Vec3f dest;
    Vec3f src;

    func_effect_8007A6F0(&boss->obj.pos, NA_SE_EN_EXPLOSION_M);

    if (arg1 == 7) {
        func_effect_8007D2C8(boss->obj.pos.x, boss->obj.pos.y + 330.0f, boss->obj.pos.z + 1020.0f, 15.0f);
        func_effect_8007BFFC(boss->obj.pos.x, boss->obj.pos.y + 330.0f, boss->obj.pos.z + 1020.0f, 0.0f, 0.0f, 0.0f,
                             7.0f, 20);
    }

    if (arg1 == 5) {
        func_effect_8007D2C8(boss->obj.pos.x, boss->obj.pos.y - 330.0f, boss->obj.pos.z + 1020.0f, 15.0f);
        func_effect_8007BFFC(boss->obj.pos.x, boss->obj.pos.y - 330.0f, boss->obj.pos.z + 1020.0f, 0.0f, 0.0f, 0.0f,
                             7.0f, 20);
    }

    if (arg1 == 4) {
        func_effect_8007D2C8(boss->obj.pos.x, boss->obj.pos.y, boss->obj.pos.z + 300.0f, 20.0f);
        func_effect_8007BFFC(boss->obj.pos.x, boss->obj.pos.y, boss->obj.pos.z + 300.0f, 0.0f, 0.0f, 0.0f, 10.0f, 25);
    }

    if (arg1 < 4) {
        Matrix_RotateY(gCalcMatrix, boss->obj.rot.y * M_DTOR, MTXF_NEW);
        Matrix_RotateX(gCalcMatrix, boss->obj.rot.x * M_DTOR, MTXF_APPLY);
        Matrix_RotateZ(gCalcMatrix, boss->obj.rot.z * M_DTOR, MTXF_APPLY);
        Matrix_RotateZ(gCalcMatrix, M_DTOR * 90.0f * arg1, MTXF_APPLY);

        src.x = 0.0f;
        src.y = 200.0f;
        src.z = 500.0f;

        Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

        func_effect_8007D2C8(boss->obj.pos.x + dest.x, boss->obj.pos.y + dest.y, boss->obj.pos.z + dest.z, 10.0f);
        func_effect_8007BFFC(boss->obj.pos.x + dest.x, boss->obj.pos.y + dest.y, boss->obj.pos.z + dest.z, 0.0f, 0.0f,
                             0.0f, 5.0f, 15);
    }
}

void Meteo_80189624(void) {
    if ((gGameFrameCount % 2) != 0) {
        gLight1xRot = gLight1xRotTarget = 0.0f;
        gLight1yRot = gLight1yRotTarget = 5.0f;
        gLight1zRot = gLight1zRotTarget = 0.0f;
        gLight2xRot = gLight2xRotTarget = 0.0f;
        gLight2yRot = gLight2yRotTarget = 100.0f;
        gLight2zRot = gLight2zRotTarget = 0.0f;
    } else {
        gLight1xRot = gLight1xRotTarget = 0.0f;
        gLight1yRot = gLight1yRotTarget = -5.0f;
        gLight1zRot = gLight1zRotTarget = 0.0f;
        gLight2xRot = gLight2xRotTarget = 0.0f;
        gLight2yRot = gLight2yRotTarget = 110.0f;
        gLight2zRot = gLight2zRotTarget = 0.0f;
    }
}

void Meteo_8018978C(Boss* boss) {
    f32 sp7C;
    f32 rand;
    s32 i;
    s32 var_v0;

    Vec3f src;
    Vec3f dest;

    gBossFrameCount++;

    Matrix_RotateY(gCalcMatrix, boss->obj.rot.y * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, boss->obj.rot.x * M_DTOR, MTXF_APPLY);
    Matrix_RotateZ(gCalcMatrix, boss->obj.rot.z * M_DTOR, MTXF_APPLY);

    if ((gGameFrameCount & 0x10) != 0) {
        boss->swork[19] += 32;
        if (boss->swork[19] > 128) {
            boss->swork[19] = 128;
        }
    } else {
        boss->swork[19] -= 32;
        if (boss->swork[19] < 0) {
            boss->swork[19] = 0;
        }
    }

    if ((gGameFrameCount & 0x38) == 0) {
        boss->fwork[3] = D_i2_80195534[gGameFrameCount % 8U];
        boss->fwork[4] = D_i2_80195534[gGameFrameCount % 8U];
        boss->fwork[5] = D_i2_80195534[gGameFrameCount % 8U];
        boss->fwork[6] = D_i2_80195534[gGameFrameCount % 8U];
    }

    if (((gGameFrameCount + 20) & 0x38) == 0) {
        boss->fwork[7] = D_i2_80195534[(gGameFrameCount + 20) % 8U];
        boss->fwork[8] = D_i2_80195534[(gGameFrameCount + 20) % 8U];
    }

    if (boss->swork[9] != 0) {
        boss->swork[9]--;
    }

    if (boss->swork[10] != 0) {
        boss->swork[10]--;
    }

    if (boss->swork[11] != 0) {
        boss->swork[11]--;
    }

    if (boss->swork[12] != 0) {
        boss->swork[12]--;
    }

    if (boss->swork[13] != 0) {
        boss->swork[13]--;
    }

    if (boss->swork[14] != 0) {
        boss->swork[14]--;
    }

    if (boss->swork[15] != 0) {
        boss->swork[15]--;
    }

    if (boss->swork[0] > 5) {
        boss->swork[0]--;
        if (boss->swork[0] == 5) {
            Audio_KillSfxBySourceAndId(boss->sfxSource, NA_SE_EN_BURNER_L);
        }
    }

    if (boss->swork[1] > 5) {
        boss->swork[1] = boss->swork[1] - 1;
        if (boss->swork[1] == 5) {
            Audio_KillSfxBySourceAndId(boss->sfxSource, NA_SE_EN_BURNER_L);
        }
    }

    if (boss->dmgType != DMG_NONE) {
        boss->dmgType = DMG_NONE;
        if ((boss->dmgPart != 7) && (boss->dmgPart >= 5) && (boss->dmgPart != 5)) {
            AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, boss->sfxSource, 4);
        }

        if ((boss->state >= 2) && (boss->state < 20)) {
            if ((boss->dmgPart < 5) && (boss[0].fwork[17 + boss->dmgPart] > 0.5f)) {
                if (boss[0].swork[boss->dmgPart + 2] != 0) {
                    AUDIO_PLAY_SFX(NA_SE_OB_DAMAGE_M, boss->sfxSource, 4);

                    boss[0].swork[9 + boss->dmgPart] = 20;
                    boss[0].swork[2 + boss->dmgPart] -= boss->damage;

                    if (boss[0].swork[2 + boss->dmgPart] <= 0) {
                        boss[0].swork[2 + boss->dmgPart] = 0;
                        Meteo_801892F0(boss, boss->dmgPart);
                        boss->swork[20]++;
                        if (boss->swork[20] == 2) {
                            Radio_PlayMessage(gMsg_ID_17160, RCID_PEPPY);
                        }
                        if (boss->swork[20] == 3) {
                            Radio_PlayMessage(gMsg_ID_3371, RCID_BOSS_METEO);
                        }
                        if (boss->swork[20] == 4) {
                            Radio_PlayMessage(gMsg_ID_3320, RCID_BOSS_METEO);
                        }
                    }
                } else {
                    AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, boss->sfxSource, 4);
                }
            }

            if (boss->state >= 9) {
                if (boss->dmgPart == 5) {
                    if ((boss->swork[7] != 0) && (boss->fwork[22] > 0.8f)) {
                        AUDIO_PLAY_SFX(NA_SE_EN_KNOCK_DOWN, boss->sfxSource, 4);
                        boss->swork[14] = 20;
                        boss->swork[7] -= boss->damage;
                        if (boss->swork[7] <= 0) {
                            boss->swork[7] = 0;
                            Meteo_801892F0(boss, boss->dmgPart);
                        }
                    } else {
                        AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, boss->sfxSource, 4);
                    }
                }

                if (boss->dmgPart == 7) {
                    if ((boss->swork[8] != 0) && (boss->fwork[23] > 0.8f)) {
                        AUDIO_PLAY_SFX(NA_SE_EN_KNOCK_DOWN, boss->sfxSource, 4);
                        boss->swork[15] = 20;
                        boss->swork[8] -= boss->damage;
                        if (boss->swork[8] <= 0) {
                            boss->swork[8] = 0;
                            Meteo_801892F0(boss, boss->dmgPart);
                        }
                    } else {
                        AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, boss->sfxSource, 4);
                    }
                }

                if (boss->swork[7] <= 0) {
                    if (boss->swork[8] <= 0) {
                        Boss_AwardBonus(boss);

                        boss->state = 20;
                        boss->timer_050 = 300;
                        boss->timer_052 = 260;
                        boss->vel.x = 0.0f;
                        boss->vel.y = 0.0f;

                        if ((gPlayer[0].state_1C8 == PLAYERSTATE_1C8_ACTIVE) ||
                            (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_U_TURN)) {
                            gPlayer[0].state_1C8 = PLAYERSTATE_1C8_LEVEL_COMPLETE;
                            gPlayer[0].csState = 0;
                            gCsFrameCount = 0;
                        }

                        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 50);
                        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 50);
                        AUDIO_PLAY_SFX(NA_SE_EN_DOWN_IMPACT, boss->sfxSource, 4);
                        gScreenFlashTimer = 8;
                    }
                }
            }
        }
    }

    sp7C = boss->obj.pos.z + gPathProgress;

    if (boss->state >= 3) {
        if (boss->state < 20) {
            Math_SmoothStepToF(&boss->vel.z, -gArwingSpeed, 0.1f, 2.0f, 0.0f);
            if ((boss->fwork[9] + 200.0f) < sp7C) {
                Math_SmoothStepToF(&boss->vel.z, -60.0f, 0.1f, 4.0f, 0.0f);
            }
            if (sp7C < (boss->fwork[9] - 300.0f)) {
                Math_SmoothStepToF(&boss->vel.z, 20.0f, 0.1f, 4.0f, 0.0f);
            }
        }
    }

    if ((boss->state >= 3) && (boss->state < 20)) {
        switch (boss->swork[16]) {
            case 0:
                if (boss->vel.y > 0.0f) {
                    boss->vel.y -= 0.2f;
                }
                if (boss->vel.y < 0.0f) {
                    boss->vel.y += 0.2f;
                }

                if (boss->timer_054 == 0) {
                    boss->timer_054 = 20;
                    boss->fwork[13] = 7.0f;
                    if (boss->obj.pos.y > 0.0f) {
                        boss->fwork[13] = -7.0f;
                    }
                    boss->timer_054 = RAND_INT(30.0f) + 40.0f;
                    boss->swork[16] = 1;
                }
                break;

            case 1:
                if (boss->fwork[13] < boss->vel.y) {
                    boss->vel.y = boss->vel.y - 0.2f;
                }

                if (boss->vel.y < boss->fwork[13]) {
                    boss->vel.y += 0.2f;
                }

                if (boss->timer_054 == 0) {
                    boss->swork[16] = 0;
                    boss->timer_054 = RAND_INT(30.0f) + 40.0f;
                }
                break;
        }

        switch (boss->swork[17]) {
            case 0:
                if (boss->vel.x > 0.0f) {
                    boss->vel.x = boss->vel.x - 0.2f;
                }

                if (boss->vel.x < 0.0f) {
                    boss->vel.x += 0.2f;
                }

                if (boss->timer_056 == 0) {
                    boss->timer_056 = 20;
                    boss->fwork[14] = 7.0f;
                    if (boss->obj.pos.x > 0.0f) {
                        boss->fwork[14] = -7.0f;
                    }
                    boss->timer_056 = RAND_INT(40.0f) + 50.0f;
                    boss->swork[17] = 1;
                }
                break;

            case 1:
                if (boss->fwork[14] < boss->vel.x) {
                    boss->vel.x = boss->vel.x - 0.2f;
                }
                if (boss->vel.x < boss->fwork[14]) {
                    boss->vel.x += 0.2f;
                }
                if (boss->timer_056 == 0) {
                    boss->swork[17] = 0;
                    boss->timer_056 = RAND_INT(40.0f) + 50.0f;
                }
                break;
        }
    }

    if (boss->swork[18] != 0) {
        s32 objId;

        if (func_hud_8008AC54(0) >= 4) {
            objId = OBJ_ACTOR_191;
        } else {
            objId = OBJ_ACTOR_190;
        }

        AUDIO_PLAY_SFX(NA_SE_EN_BARREL_SHOT, boss->sfxSource, 4);

        src.x = 0.0f;
        src.y = 330.0f;
        src.z = -1022.0f;

        Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

        if (boss->swork[18] == 1) {
            Meteo_80187D08(boss->obj.pos.x + dest.x, boss->obj.pos.y + dest.y, boss->obj.pos.z + dest.z, 50.0f, 270.0f,
                           0.0f, 30, 0, objId);
        } else {
            Meteo_80187D08(boss->obj.pos.x + dest.x, boss->obj.pos.y + dest.y, boss->obj.pos.z + dest.z, 50.0f, 0.0f,
                           0.0f, 0, 0, objId);
        }

        src.y = -330.0f;

        Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

        if (boss->swork[18] == 1) {
            Meteo_80187D08(boss->obj.pos.x + dest.x, boss->obj.pos.y + dest.y, boss->obj.pos.z + dest.z, 50.0f, 90.0f,
                           0.0f, 30, 0, objId);
        } else {
            Meteo_80187D08(boss->obj.pos.x + dest.x, boss->obj.pos.y + dest.y, boss->obj.pos.z + dest.z, 50.0f, 0.0f,
                           0.0f, 0, 0, objId);
        }
        boss->swork[18] = 0;
    }

    if ((sp7C < 200.0f) && (sp7C > -1500.0f)) {
        gLight2xRotTarget = 0.0f;
        gLight2yRotTarget = 150.0f;
        gLight2zRotTarget = 0.0f;
    }

    switch (boss->state) {
        case 0:
            boss->swork[0] = 10;
            boss->swork[1] = 10;

            boss->obj.pos.y += ((0.0f - boss->obj.pos.y) * boss->fwork[1]);
            boss->vel.z = boss->fwork[0] - gPathVelZ;

            if (sp7C < boss->fwork[9]) {
                boss->state = 1;
                boss->fwork[1] = 0.0f;
            }

            if (sp7C < -1000.0f) {
                if (boss->fwork[1] < 0.005f) {
                    boss->fwork[1] = boss->fwork[1] + 0.0001f;
                }
            }
            break;

        case 1:
            boss->obj.pos.y += ((0.0f - boss->obj.pos.y) * boss->fwork[1]);
            boss->vel.z = boss->fwork[0] - gPathVelZ;

            if (boss->fwork[0] < 0.0f) {
                boss->fwork[0] += 0.5f;
                if (boss->fwork[0] >= 0.0f) {
                    boss->state = 2;
                    boss->timer_050 = 50;
                    gBosses[boss->unk_044].state = 1;
                }
            }

            if (boss->fwork[1] < 0.005f) {
                boss->fwork[1] = boss->fwork[1] + 0.0001f;
            }
            break;

        case 2:
            boss->obj.pos.y += ((0.0f - boss->obj.pos.y) * boss->fwork[1]);
            boss->vel.z = boss->fwork[0] - gPathVelZ;

            if (boss->fwork[1] < 0.05f) {
                boss->fwork[1] = boss->fwork[1] + 0.0004f;
            }

            if (boss->timer_050 == 0) {
                boss->state = 3;
                boss->timer_050 = 50;
                boss->timer_058 = 100;
                Radio_PlayMessage(gMsg_ID_3310, RCID_BOSS_METEO);
            }
            break;

        case 3:
            if (boss->timer_052 == 0) {
                rand = Rand_ZeroOne();
                boss->fwork[9] = -3000.0f;
                if (rand < 0.3f) {
                    boss->fwork[9] = -2000.0f;
                }
                if (rand > 0.7f) {
                    boss->fwork[9] = -4000.0f;
                }
                boss->timer_052 = 80;
            } else if (boss->vel.z < -50.0f) {
                if (boss->swork[0] == 5) {
                    AUDIO_PLAY_SFX(NA_SE_EN_BURNER_L, boss->sfxSource, 4);
                }

                if (boss->swork[0] < 10) {
                    boss->swork[0] += 2;
                    if (boss->swork[0] > 10) {
                        boss->swork[0] = 10;
                    }
                }

                if (boss->swork[1] < 10) {
                    boss->swork[1] += 2;
                    if (boss->swork[1] > 10) {
                        boss->swork[1] = 10;
                    }
                }
            }

            if (gBosses[boss->unk_044].state < 3) {
                var_v0 = 0;
                if (boss->swork[2] == 0) {
                    var_v0 = 1;
                    boss->obj.rot.z += 0.1f;
                }
                if (boss->swork[3] == 0) {
                    var_v0++;
                    boss->obj.rot.z += 0.1f;
                }
                if (boss->swork[4] == 0) {
                    var_v0++;
                    boss->obj.rot.z += 0.1f;
                }
                if (boss->swork[5] == 0) {
                    var_v0++;
                    boss->obj.rot.z += 0.1f;
                }
                if (var_v0 == 4) {
                    gBosses[boss->unk_044].state = 3;
                    boss->state = 4;
                    boss->timer_050 = 250;
                    boss->timer_05A = 30;
                    boss->fwork[10] = 0;
                }

                if ((boss->timer_050 == 0) && (gBosses[boss->unk_044].state == 2)) {
                    boss->fwork[2] = 90.0f;
                    boss->timer_050 = D_i2_80195520[var_v0] + 45;
                    AUDIO_PLAY_SFX(NA_SE_EN_SHIELD_ROLL, boss->sfxSource, 4);
                }

                if (boss->fwork[2] > 0.0f) {
                    boss->fwork[2] -= 2.0f;
                    gBosses[boss->unk_044].rot_078.z -= 2.0f;
                }
            }

            if (boss->timer_058 == 0) {
                boss->timer_058 = RAND_INT(80.0f) + 180.0f;
                boss->swork[18] = 1;
            }
            break;

        case 4:
            boss->fwork[9] = -3000.0f;
            if (boss->fwork[10] < 0.02f) {
                boss->fwork[10] += 0.0002f;
            }
            boss->obj.rot.z += ((0.0f - boss->obj.rot.z) * boss->fwork[10]);
            if (boss->timer_050 == 100) {
                Radio_PlayMessage(gMsg_ID_3321, RCID_BOSS_METEO);
            }
            if (boss->timer_050 == 0) {
                boss->state = 5;
                boss->timer_050 = 70;
            }
            break;

        case 5:
            boss->obj.rot.z += ((0.0f - boss->obj.rot.z) * 0.02f);

            if (boss->timer_050 == 1) {
                AUDIO_PLAY_SFX(NA_SE_EN_S_BEAM_CHARGE, boss->sfxSource, 4);
            }

            if (boss->timer_050 == 0) {
                gLight1xRotTarget = 0.0f;
                gLight1yRotTarget = 5.0f;
                gLight1zRotTarget = 0.0f;
                gLight2xRotTarget = 0.0f;
                gLight2yRotTarget = 100.0f;
                gLight2zRotTarget = 0.0f;
                gLight1rotStep = 5.0f;
                gLight2rotStep = 5.0f;

                if (boss->fwork[11] < 70.0f) {
                    boss->fwork[11] += 1.0f;
                    if (boss->fwork[11] > 20.0f) {
                        boss->fwork[11] += 1.0f;
                    }
                } else {
                    boss->state = 6;
                    boss->timer_050 = 75;
                }

                if (boss->fwork[11] > 30.0f) {
                    Meteo_80189624();
                }
            }
            break;

        case 6:
            boss->obj.rot.z = boss->obj.rot.z + ((0.0f - boss->obj.rot.z) * 0.02f);
            Math_SmoothStepToF(&boss->fwork[0x15], 4.0f, 1.0f, 0.1f, 0.0f);

            if (gPlayer[0].state_1C8 != PLAYERSTATE_1C8_NEXT) {
                gFillScreenRed = gFillScreenAlpha = gFillScreenGreen = gFillScreenBlue = 0;

                if ((boss->timer_050 == 10) || (boss->timer_050 == 30) || (boss->timer_050 == 50) ||
                    (boss->timer_050 == 70)) {
                    gFillScreenAlpha = 150;
                    gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
                    Meteo_80187E38(boss->obj.pos.x, boss->obj.pos.y, boss->obj.pos.z + 1300.0f,
                                   boss->fwork[12] + boss->obj.rot.z);
                    boss->fwork[12] = RAND_FLOAT(360.0f);
                }
                if ((boss->timer_050 == 13) || (boss->timer_050 == 33) || (boss->timer_050 == 53) ||
                    (boss->timer_050 == 73)) {
                    gFillScreenAlpha = 150;
                    gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
                }
                if (boss->timer_050 == 0) {
                    boss->state = 7;
                    AUDIO_PLAY_SFX(NA_SE_EN_S_BEAM_END, boss->sfxSource, 4);
                }
                Meteo_80189624();
            }
            break;

        case 7:
            if (boss->fwork[11] > 26.0f) {
                Meteo_80189624();
            }

            if (boss->fwork[11] > 0.0f) {
                boss->fwork[11] -= 2.0f;
                if (boss->fwork[11] <= 0.0f) {
                    boss->fwork[11] = 0.0f;
                    Audio_KillSfxBySource(boss->sfxSource);
                    if (boss->swork[6] == 0) {
                        boss->state = 8;

                        boss->timer_050 = 190;
                        boss->timer_052 = 230;

                        boss->fwork[10] = 0.0f;
                        boss->fwork[22] = 0.0f;
                        boss->fwork[23] = 0.0f;
                        gCsFrameCount = 0;
                        Radio_PlayMessage(gMsg_ID_3322, RCID_BOSS_METEO);
                        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 1);
                        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 1);
                    } else {
                        boss->state = 5;
                        boss->timer_050 = 70;
                    }
                }
            }
            break;

        case 8:
            gCsFrameCount++;
            if (gCsFrameCount == 130) {
                Radio_PlayMessage(gMsg_ID_3330, RCID_BOSS_METEO);
            }
            if (gCsFrameCount == 300) {
                PRINTF("msg_03340\n");
                Radio_PlayMessage(gMsg_ID_3340, RCID_FALCO);
            }

            if (gCsFrameCount == 400) {
                AUDIO_PLAY_BGM(NA_BGM_REAL_BOSS);
                if (gTeamShields[TEAM_ID_FALCO] > 0) {
                    Radio_PlayMessage(gMsg_ID_3345, RCID_BOSS_METEO);
                } else {
                    Radio_PlayMessage(gMsg_ID_3350, RCID_BOSS_METEO);
                }
            }

            if (boss->timer_050 == 0) {
                if (boss->fwork[10] < 0.02f) {
                    boss->fwork[10] = boss->fwork[10] + 0.0002f;
                }

                boss->obj.rot.x += (-180.0f - boss->obj.rot.x) * boss->fwork[10];

                if (boss->timer_052 != 0) {
                    if (boss->swork[0] == 5) {
                        AUDIO_PLAY_SFX(NA_SE_EN_BURNER_L, boss->sfxSource, 4);
                    }
                    if (boss->swork[0] < 10) {
                        boss->swork[0] += 2;
                        if (boss->swork[0] > 10) {
                            boss->swork[0] = 10;
                        }
                    }
                }

                if (boss->obj.rot.x < -178.0f) {
                    boss->state = 9;
                    boss->timer_050 = 0;
                    boss->fwork[15] = 8.0f;
                    AUDIO_PLAY_SFX(NA_SE_EN_RNG_BEAM_CHARGE, boss->sfxSource, 4);
                }
            }
            break;

        case 9:
            boss->obj.rot.x += (-180.0f - boss->obj.rot.x) * boss->fwork[10];
            if ((boss->timer_050 > 50) && (boss->timer_050 <= 64)) {
                boss->fwork[22] -= 0.1f;
                if (boss->fwork[22] < 0.0f) {
                    boss->fwork[22] = 0.0f;
                }
                boss->fwork[23] -= 0.1f;
                if (boss->fwork[23] < 0.0f) {
                    boss->fwork[23] = 0.0f;
                }
            }

            if (boss->timer_050 < 20) {
                boss->fwork[22] += 0.1f;
                if (boss->fwork[22] > 1.0f) {
                    boss->fwork[22] = 1.0f;
                }
                boss->fwork[23] += 0.1f;
                if (boss->fwork[23] > 1.0f) {
                    boss->fwork[23] = 1.0f;
                }
            }

            if (boss->timer_050 == 40) {
                boss->swork[18] = 2;
            }

            if (boss->timer_050 == 0) {
                boss->fwork[15] -= 0.1f;
                if (boss->fwork[15] < -1.0f) {
                    boss->timer_050 = 40;
                    boss->state = 10;
                }
            }
            break;

        case 10:
            if (boss->timer_050 == 0) {
                boss->state = 9;
                boss->timer_050 = 70;
                boss->fwork[15] = 8.0f;
                AUDIO_PLAY_SFX(NA_SE_EN_RNG_BEAM_CHARGE, boss->sfxSource, 4);
            } else if ((boss->timer_050 % 2U) == 1) {
                Meteo_80188088(boss);
            }
            break;

        case 20:
            if (boss->timer_052 == 230) {
                Radio_PlayMessage(gMsg_ID_3370, RCID_BOSS_METEO);
            }
            if (boss->timer_052 == 90) {
                Radio_PlayMessage(gMsg_ID_3360, RCID_FOX);
            }

            if (((gGameFrameCount % 8) == 0) && (Rand_ZeroOne() < 0.5f)) {
                boss->timer_05C = 4;
            }

            Matrix_MultVec3fNoTranslate(gCalcMatrix, &D_i2_80195430[RAND_INT(19.9f)], &dest);

            if (((gGameFrameCount % 2) == 0)) {
                func_effect_8007C120(boss->obj.pos.x + dest.x, boss->obj.pos.y + dest.y, boss->obj.pos.z + dest.z,
                                     boss->vel.x, boss->vel.y, boss->vel.z, 0.3f, 20);
            }
            if (((gGameFrameCount % 4) == 0)) {
                func_effect_8007BFFC(boss->obj.pos.x + dest.x, boss->obj.pos.y + dest.y, boss->obj.pos.z + dest.z,
                                     boss->vel.x, boss->vel.y, boss->vel.z, 10.0f, 10);
            }

            boss->vel.y = -5.0f;
            boss->obj.rot.x += 0.2f;
            boss->obj.rot.z -= 0.1f;

            if (boss->timer_050 == 0) {
                func_effect_8007D2C8(boss->obj.pos.x, boss->obj.pos.y, boss->obj.pos.z, 40.0f);
                Object_Kill(&boss->obj, boss->sfxSource);
            }
            if (boss->timer_050 == 20) {
                func_effect_8007A568(boss->obj.pos.x, boss->obj.pos.y, boss->obj.pos.z, 80.0f);
                AUDIO_PLAY_SFX(NA_SE_EN_STAR_EXPLOSION, boss->sfxSource, 4);
                gControllerRumbleTimers[0] = 60;
                for (i = 0; i < ARRAY_COUNT(gActors); i++) {
                    if (gActors[i].obj.id == OBJ_ACTOR_TEAM_BOSS) {
                        Object_Kill(&gActors[i].obj, gActors[i].sfxSource);
                    }
                }
            }

            switch (boss->timer_050) {
                case 20:
                    gShowBossHealth = false;

                case 1:
                case 5:
                case 10:
                case 15:
                    func_effect_8007B344(boss->obj.pos.x, boss->obj.pos.y, boss->obj.pos.z, 71.0f, 5);

                case 0:
                    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
                        func_effect_80079618(RAND_FLOAT_CENTERED(1000.0f) + boss->obj.pos.x,
                                             RAND_FLOAT_CENTERED(1000.0f) + boss->obj.pos.y,
                                             RAND_FLOAT_CENTERED(1000.0f) + boss->obj.pos.z, 3.0f);
                    }
                    break;
            }
    }

    if (boss->obj.rot.z >= 360.0f) {
        boss->obj.rot.z = boss->obj.rot.z - 360.0f;
    }
    if (boss->obj.rot.z < 0.0f) {
        boss->obj.rot.z += 360.0f;
    }

    if (gBossFrameCount == 250) {
        Radio_PlayMessage(gMsg_ID_2225, RCID_SLIPPY);
    }
    if (gBossFrameCount == 406) {
        gShowBossHealth = true;
    }
    if (gBossFrameCount > 406) {
        gBossHealthBar = (boss->swork[2] + boss->swork[3] + boss->swork[4] + boss->swork[5] + boss->swork[7] +
                          boss->swork[8] + boss->swork[6]) /
                         2.6274f; // approx 670 / 255
        if ((gBossFrameCount > 506) && (gBossFrameCount < 1000)) {
            Math_SmoothStepToF(&boss->fwork[17], 3.3f, 1.0f, 0.1f, 0.0f);
            Math_SmoothStepToF(&boss->fwork[18], 3.3f, 1.0f, 0.1f, 0.0f);
            Math_SmoothStepToF(&boss->fwork[19], 3.3f, 1.0f, 0.1f, 0.0f);
            Math_SmoothStepToF(&boss->fwork[20], 3.3f, 1.0f, 0.1f, 0.0f);
        }
    }
}

void Meteo_8018B7C4(s32 arg0) {
    f32 effect = arg0 * 0.83333f; // approx 5 / 6

    if ((gGameFrameCount % 2) != 0) {
        effect *= 1.1f;
    }

    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);

    RCP_SetupDL_64();
    Matrix_Push(&gGfxMatrix);
    Matrix_Scale(gGfxMatrix, 10.0f * effect, 10.0f * effect, 10.0f * effect, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 70);
    gSPDisplayList(gMasterDisp++, D_102ED50);

    Matrix_Pop(&gGfxMatrix);
    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, 20.0f, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, 9.0f * effect, 9.0f * effect, 9.0f * effect, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 60);
    gSPDisplayList(gMasterDisp++, D_102ED50);

    Matrix_Pop(&gGfxMatrix);
    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, 35.0f, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, 7.5f * effect, 7.5f * effect, 7.5f * effect, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 50);
    gSPDisplayList(gMasterDisp++, D_102ED50);

    Matrix_Pop(&gGfxMatrix);
    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, 40.0f, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, 5.0f * effect, 5.0f * effect, 5.0f * effect, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 40);
    gSPDisplayList(gMasterDisp++, D_102ED50);
    Matrix_Pop(&gGfxMatrix);
    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
}

void Meteo_8018BACC(Boss* boss) {
    s32 i;
    f32 var_fs0;
    f32 var_fs1;
    s32 pad;

    gSPDisplayList(gMasterDisp++, D_ME_6001310);
    RCP_SetupDL_64();
    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);

    for (i = 0; i < 6; i++) {
        if ((boss->fwork[i + 3] != 0) && (boss->fwork[11] == 0.0f)) {
            var_fs1 = 2.0f * boss->fwork[3 + i];
            Matrix_Push(&gGfxMatrix);
            switch (i) {
                case 0:
                    Matrix_Translate(gGfxMatrix, 746.0f, 741.0f, 680.0f, MTXF_APPLY);
                    break;

                case 1:
                    Matrix_Translate(gGfxMatrix, -746.0f, 741.0f, 680.0f, MTXF_APPLY);
                    break;

                case 2:
                    Matrix_Translate(gGfxMatrix, -746.0f, -741.0f, 680.0f, MTXF_APPLY);
                    break;

                case 3:
                    Matrix_Translate(gGfxMatrix, 746.0f, -741.0f, 680.0f, MTXF_APPLY);
                    break;

                case 4:
                    Matrix_Translate(gGfxMatrix, 1283.0f, 0.0f, -340.0f, MTXF_APPLY);
                    break;

                case 5:
                    Matrix_Translate(gGfxMatrix, -1283.0f, 0.0f, -340.0f, MTXF_APPLY);
                    break;
            }

            if (i < 4) {
                gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 32, 32, 128);
                Matrix_Scale(gGfxMatrix, var_fs1, var_fs1, var_fs1, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_102ED50);
            } else {
                gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 128);
                Matrix_Scale(gGfxMatrix, var_fs1 * 6.0f, var_fs1 * 6.0f, var_fs1 * 6.0f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_102ED50);
            }
            Matrix_Pop(&gGfxMatrix);
        }
    }

    for (i = 0; i < 7; i++) {
        if (boss->swork[2 + i] != 0) {
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, boss->swork[19], 255);

            if ((boss->swork[9 + i] % 2) != 0) {
                gDPSetPrimColor(gMasterDisp++, 0, 0, 80, 0, 0, 255);
            }

            Matrix_Push(&gGfxMatrix);

            if (i == 4) {
                Matrix_Translate(gGfxMatrix, 0.0f, 0, 300.0f, MTXF_APPLY);
                Matrix_RotateZ(gGfxMatrix, M_PI / 4, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, boss->fwork[21], boss->fwork[21], 1.0f, MTXF_APPLY);
            }

            if (i == 5) {
                Matrix_Translate(gGfxMatrix, 0.0f, 330.0f, -1022.0f, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, boss->fwork[22] * 3.2f, 2.0f * boss->fwork[22], 1.0f, MTXF_APPLY);
            }

            if (i == 6) {
                Matrix_Translate(gGfxMatrix, 0.0f, -330.0f, -1022.0f, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, boss->fwork[23] * 3.2f, 2.0f * boss->fwork[23], 1.0f, MTXF_APPLY);
            }

            if (i < 4) {
                Matrix_RotateZ(gGfxMatrix, M_DTOR * 90.0f * i, MTXF_APPLY);
                Matrix_Translate(gGfxMatrix, 0.0f, 200.0f, 500.0f, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, boss->fwork[17 + i], boss->fwork[17 + i], 1.0f, MTXF_APPLY);
            }

            Matrix_SetGfxMtx(&gMasterDisp);

            if (i < 4) {
                gSPDisplayList(gMasterDisp++, D_ME_6024AD0);
            } else {
                gSPDisplayList(gMasterDisp++, D_ME_60236F0);
            }
            Matrix_Pop(&gGfxMatrix);
        }
    }

    gDPSetPrimColor(gMasterDisp++, 0, 0, 160, 255, 160, 128);
    for (i = 0; i < 4; i++) {
        if (boss->fwork[11] != 0) {
            var_fs1 = boss->fwork[11];
            if (boss->fwork[11] > 15.0f) {
                var_fs1 = 15.0f;
            }

            Matrix_Push(&gGfxMatrix);
            switch (i) {
                case 0:
                    Matrix_Translate(gGfxMatrix, 746.0f, 741.0f, 680.0f, MTXF_APPLY);
                    Matrix_RotateZ(gGfxMatrix, -M_PI / 4, MTXF_APPLY);
                    break;

                case 1:
                    Matrix_Translate(gGfxMatrix, -746.0f, 741.0f, 680.0f, MTXF_APPLY);
                    Matrix_RotateZ(gGfxMatrix, M_PI / 4, MTXF_APPLY);
                    break;

                case 2:
                    Matrix_Translate(gGfxMatrix, -746.0f, -741.0f, 680.0f, MTXF_APPLY);
                    Matrix_RotateZ(gGfxMatrix, 3 * M_PI / 4, MTXF_APPLY);
                    break;

                case 3:
                    Matrix_Translate(gGfxMatrix, 746.0f, -741.0f, 680.0f, MTXF_APPLY);
                    Matrix_RotateZ(gGfxMatrix, -3 * M_PI / 4, MTXF_APPLY);
                    break;
            }

            Matrix_SetGfxMtx(&gMasterDisp);
            Matrix_Push(&gGfxMatrix);

            if ((gGameFrameCount % 2) != 0) {
                Matrix_Scale(gGfxMatrix, var_fs1 * 2.5f, var_fs1 * 2.5f, var_fs1 * 2.5f, MTXF_APPLY);
            } else {
                Matrix_Scale(gGfxMatrix, var_fs1 * 3.0f, var_fs1 * 3.0f, var_fs1 * 3.0f, MTXF_APPLY);
            }

            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_102ED50);
            Matrix_Pop(&gGfxMatrix);
            Matrix_RotateX(gGfxMatrix, -M_PI / 6, MTXF_APPLY);

            if ((gGameFrameCount % 2) != 0) {
                Matrix_RotateY(gGfxMatrix, M_PI, MTXF_APPLY);
            }
            Matrix_Scale(gGfxMatrix, 2.0f, 2.0f * var_fs1, 2.0f, MTXF_APPLY);
            Matrix_Translate(gGfxMatrix, 0.0f, -20.0f, 0.0f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_102F5E0);
            Matrix_Pop(&gGfxMatrix);
        }
    }

    if (boss->fwork[11] > 15.0f) {
        var_fs1 = boss->fwork[11] - 15.0f;
        gDPSetPrimColor(gMasterDisp++, 0, 0, 160, 255, 160, 255);
        Matrix_Push(&gGfxMatrix);
        Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, 1300.0f, MTXF_APPLY);
        if ((gGameFrameCount % 2) != 0) {
            Matrix_Scale(gGfxMatrix, var_fs1 * 0.8f, var_fs1 * 0.8f, var_fs1 * 0.8f, MTXF_APPLY);
        } else {
            Matrix_Scale(gGfxMatrix, var_fs1, var_fs1, var_fs1, MTXF_APPLY);
        }
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, D_102ED50);
        Matrix_Pop(&gGfxMatrix);
    }

    if ((boss->state == 9) || (boss->state == 10)) {
        var_fs1 = boss->fwork[15];
        for (i = 0; i < 10; i++) {
            var_fs1 += 0.3f;
            var_fs0 = var_fs1;
            if (var_fs1 <= 7.0f) {
                if (var_fs1 < 1.0f) {
                    var_fs0 = 1.0f;
                }

                gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, D_i2_80195554[i]);
                Matrix_Push(&gGfxMatrix);

                Matrix_Translate(gGfxMatrix, 700.0f, 0.0f, -(1235.0f - ((var_fs0 - 1.0f) * 89.2f)), MTXF_APPLY);

                if ((gGameFrameCount % 2) != 0) {
                    Matrix_Scale(gGfxMatrix, var_fs0, var_fs0, var_fs0, MTXF_APPLY);
                } else {
                    Matrix_Scale(gGfxMatrix, var_fs0 * 1.1f, var_fs0 * 1.1f, var_fs0 * 1.1f, MTXF_APPLY);
                }

                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_ME_6023810);
                Matrix_Pop(&gGfxMatrix);
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, -700.0f, 0.0f, -(1235.0f - ((var_fs0 - 1.0f) * 89.2f)), MTXF_APPLY);

                if ((gGameFrameCount % 2) != 0) {
                    Matrix_Scale(gGfxMatrix, var_fs0, var_fs0, var_fs0, MTXF_APPLY);
                } else {
                    Matrix_Scale(gGfxMatrix, var_fs0 * 1.1f, var_fs0 * 1.1f, var_fs0 * 1.1f, MTXF_APPLY);
                }

                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_ME_6023810);
                Matrix_Pop(&gGfxMatrix);
            }
        }
    }

    if (boss->swork[0] > 0) {
        Matrix_Push(&gGfxMatrix);
        Matrix_Translate(gGfxMatrix, 0.0f, 650.0f, 600.0f, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        Meteo_8018B7C4(boss->swork[0] - 1);
        Matrix_Pop(&gGfxMatrix);
    }

    if (boss->swork[1] > 0) {
        Matrix_Push(&gGfxMatrix);
        Matrix_Translate(gGfxMatrix, 0.0f, -650.0f, 600.0f, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        Meteo_8018B7C4(boss->swork[1] - 1);
        Matrix_Pop(&gGfxMatrix);
    }

    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
}

void Meteo_8018C77C(Actor* actor, s32 arg1) {
    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_CUTSCENE;

    actor->obj.pos.x = D_i2_80195584[arg1] + gPlayer[0].pos.x;
    actor->obj.pos.y = D_i2_80195594[arg1] + gPlayer[0].pos.y;
    actor->obj.pos.z = D_i2_801955A4[arg1] + gPlayer[0].trueZpos;

    actor->animFrame = D_i2_801955B4[arg1];
    actor->obj.rot.y = 180.0f;
    Object_SetInfo(&actor->info, actor->obj.id);
    actor->info.cullDistance = 200.0f;

    if (actor->animFrame == 0) {
        actor->iwork[11] = 1;
        AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, actor->sfxSource, 4);
        return;
    }

    AUDIO_PLAY_SFX(NA_SE_GREATFOX_ENGINE, actor->sfxSource, 0);
    AUDIO_PLAY_SFX(NA_SE_GREATFOX_BURNER, actor->sfxSource, 0);
}

void Meteo_8018C8F4(Actor* actor1, Actor* actor2) {
    Actor_Initialize(actor1);
    actor1->obj.status = OBJ_INIT;
    actor1->obj.id = OBJ_ACTOR_182;

    actor1->obj.pos.x = RAND_FLOAT_CENTERED_SEEDED(2000.0f) + actor2->obj.pos.x;
    actor1->obj.pos.y = RAND_FLOAT_CENTERED_SEEDED(2000.0f) + actor2->obj.pos.y;
    actor1->obj.pos.z = (RAND_FLOAT_CENTERED_SEEDED(500.0f) + actor2->obj.pos.z) - 9000.0f;

    actor1->obj.rot.y = RAND_FLOAT_SEEDED(360.0f);
    actor1->obj.rot.x = RAND_FLOAT_SEEDED(360.0f);

    actor1->timer_0C2 = 10000;
    actor1->vel.z = 30.0f;
    Object_SetInfo(&actor1->info, actor1->obj.id);
}

void Meteo_8018CA10(Actor* actor1, Actor* actor2, f32 x, f32 y, f32 z) {
    Actor_Initialize(actor1);
    actor1->obj.status = OBJ_INIT;
    actor1->obj.id = OBJ_ACTOR_182;

    actor1->obj.pos.x = actor2->obj.pos.x + x;
    actor1->obj.pos.y = actor2->obj.pos.y + y;
    actor1->obj.pos.z = actor2->obj.pos.x + z;

    actor1->obj.rot.y = RAND_FLOAT_SEEDED(360.0f);
    actor1->obj.rot.x = RAND_FLOAT_SEEDED(360.0f);

    actor1->timer_0C2 = 10000;
    actor1->vel.z = 30.0f;
    Object_SetInfo(&actor1->info, actor1->obj.id);
}

void Meteo_8018CAD8(void) {
    Actor* actor = &gActors[50];

    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.pos.x = 0.0f;
    actor->obj.pos.y = 0.0f;
    actor->obj.pos.z = 9000.0f;
    actor->animFrame = 10;
    actor->obj.id = OBJ_ACTOR_CUTSCENE;
    Object_SetInfo(&actor->info, actor->obj.id);
}

void Meteo_8018CB50(Effect* effect, Actor* actor) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_ACTIVE;
    effect->obj.id = OBJ_EFFECT_346;
    effect->timer_50 = RAND_INT(20.0f) + 20.0f;
    effect->scale2 = RAND_FLOAT(0.5f) + 0.5f;

    effect->obj.pos.x = actor->obj.pos.x;
    effect->obj.pos.y = actor->obj.pos.y;
    effect->obj.pos.z = actor->obj.pos.z;

    effect->vel.x = RAND_FLOAT_CENTERED(30.0f);
    effect->vel.y = RAND_FLOAT_CENTERED(30.0f);
    effect->vel.z = RAND_FLOAT_CENTERED(30.0f);

    effect->obj.rot.z = RAND_FLOAT(360.0f);
    Object_SetInfo(&effect->info, effect->obj.id);
}

void Meteo_8018CCF8(Actor* actor) {
    s32 i;
    s32 j;

    func_effect_8007A6F0(&actor->obj.pos, NA_SE_EN_EXPLOSION_S);

    for (i = 0; i < 25; ++i) {
        for (j = 0; j < ARRAY_COUNT(gEffects); j++) {
            if (gEffects[j].obj.status == OBJ_FREE) {
                Meteo_8018CB50(&gEffects[j], actor);
                break;
            }
        }
    }
}

void Meteo_LevelStart(Player* player) {
    u8 sp8F;
    s32 i;
    Actor* actor0 = &gActors[0];
    Actor* actor1 = &gActors[1];
    Actor* actor2 = &gActors[2];
    Actor* actor3 = &gActors[3];
    f32 x;
    f32 y;
    f32 z;
    f32 sp68;
    f32 sp64;
    Vec3f sp58;
    Vec3f sp4C;

    gFillScreenAlphaStep = 4;

    PRINTF("Demo_Time %d\n");

    switch (player->csState) {
        case 0:
            gCsFrameCount = 0;

            if (gTeamShields[TEAM_ID_FALCO] > 0) {
                Meteo_8018C77C(actor0, 0);
            }
            if (gTeamShields[TEAM_ID_SLIPPY] > 0) {
                Meteo_8018C77C(actor1, 1);
            }
            if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                Meteo_8018C77C(actor2, 2);
            }

            Meteo_8018C77C(actor3, 3);
            Meteo_8018CAD8();

            for (i = 5; i < 15; i++) {
                Meteo_8018C8F4(&gActors[i], actor3);
            }

            D_ctx_80177A48[1] = -13000.0f;
            D_ctx_80177A48[2] = -13000.0f;
            D_ctx_80177A48[4] = -22000.0f;

            player->cam.eye.x = gCsCamEyeX = player->pos.x + 100.0f;
            player->cam.eye.y = gCsCamEyeY = player->pos.y;
            player->cam.eye.z = gCsCamEyeZ = D_ctx_80177A48[1] + player->trueZpos;

            player->cam.at.x = gCsCamAtX = D_ctx_80177A48[2] + player->pos.x;
            player->cam.at.y = gCsCamAtY = player->pos.y;
            player->cam.at.z = gCsCamAtZ = D_ctx_80177A48[4] + player->trueZpos;

            player->csState = 1;

            D_ctx_80177A48[3] = 1.0f;

        case 1:
            actor3->vel.z = 4.0f;
            gCsCamEyeX = player->pos.x + 100.0f;
            gCsCamEyeY = player->pos.y;
            gCsCamEyeZ = D_ctx_80177A48[1] + player->trueZpos;
            gCsCamAtX = D_ctx_80177A48[2] + player->pos.x;
            gCsCamAtY = player->pos.y + 20.0f;
            gCsCamAtZ = D_ctx_80177A48[4] + player->trueZpos;
            Math_SmoothStepToF(&D_ctx_80177A48[1], 8000.0f, 0.05f, 20.0f, 0);
            Math_SmoothStepToF(&D_ctx_80177A48[2], 0.0f, 0.05f, 25.0f, 0);
            Math_SmoothStepToF(&D_ctx_80177A48[4], 0.0f, 0.05f, 200.0f, 0);
            Math_SmoothStepToF(&player->rot.z, 0.0f, 0.05f, 0.3f, 0);

            D_ctx_80177A48[0] = 0.1f;
            if (gCsFrameCount == 680) {
                actor3->state = 10;
            }
            if (gCsFrameCount == 720) {
                actor0->state = 11;
            }
            if (gCsFrameCount == 750) {
                actor2->state = 12;
            }
            if (gCsFrameCount == 780) {
                actor1->state = 13;
            }
            if (gCsFrameCount > 810) {
                player->csState = 2;
                D_ctx_80177A48[0] = 0.0f;
                player->csTimer = 40;
            }
            sp8F = false;
            if (gCsFrameCount == 190) {
                player->csEventTimer = 5;
                player->meTargetIndex = 10;
                sp8F = true;
            }
            if (gCsFrameCount == 230) {
                player->csEventTimer = 3;
                player->meTargetIndex = 6;
                sp8F = true;
            }
            if (gCsFrameCount == 240) {
                player->csEventTimer = 3;
                player->meTargetIndex = 11;
                sp8F = true;
            }
            if (gCsFrameCount == 270) {
                player->csEventTimer = 2;
                player->meTargetIndex = 12;
                sp8F = true;
            }
            if (gCsFrameCount == 600) {
                Meteo_8018CA10(&gActors[16], &gActors[3], 100.0f, 500.0f, 1500.0f);
                Meteo_8018CA10(&gActors[17], &gActors[3], 300.0f, 400.0f, 2000.0f);
            }
            if (gCsFrameCount == 660) {
                for (i = 4; i < 15; i++) {
                    gActors[i].obj.status = OBJ_FREE;
                }

                actor3->obj.pos.x += 1000.0f;
                actor3->obj.pos.z += 4000.0f;

                for (i = 4; i < 9; i++) {
                    Meteo_8018C8F4(&gActors[i], &gActors[3]);
                }

                actor3->obj.pos.x -= 1000.0f;
                actor3->obj.pos.z -= 4000.0f;

                Meteo_8018CA10(&gActors[13], &gActors[3], 1500.0f, 200.0f, 100.0f);
                Meteo_8018CA10(&gActors[14], &gActors[3], 1200.0f, -200.0f, -500.0f);
                Meteo_8018CA10(&gActors[15], &gActors[3], 2000.0f, -100.0f, -1000.0f);

                gActors[50].obj.status = gActors[16].obj.status = gActors[17].obj.status = OBJ_FREE;
            }

            if (gCsFrameCount > 660) {
                player->wings.modelId = 0;
            }

            if (gCsFrameCount == 340) {
                func_effect_8007D2C8(gActors[8].obj.pos.x, gActors[8].obj.pos.y, gActors[8].obj.pos.z, 10.0f);
                gActors[8].obj.status = OBJ_FREE;
                Meteo_8018CCF8(&gActors[8]);
            }

            if (player->csEventTimer != 0) {
                if (sp8F != 0) {
                    sp58 = D_i2_801955C4;
                    D_ctx_80177A48[3] *= -1.0f;
                    x = gActors[player->meTargetIndex].obj.pos.x - (actor3->obj.pos.x + (D_ctx_80177A48[3] * 74.0f));
                    y = gActors[player->meTargetIndex].obj.pos.y - (actor3->obj.pos.y - 232.0f);
                    z = gActors[player->meTargetIndex].obj.pos.z - (actor3->obj.pos.z - 1190.0f);

                    sp64 = Math_RadToDeg(Math_Atan2F(x, z));
                    x = sqrtf(SQ(x) + SQ(z));
                    sp68 = Math_RadToDeg(-Math_Atan2F(y, x));

                    Matrix_RotateY(gCalcMatrix, M_DTOR * sp64, MTXF_NEW);
                    Matrix_RotateX(gCalcMatrix, M_DTOR * sp68, MTXF_APPLY);
                    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp58, &sp4C);

                    Actor_SpawnGreatFoxLaser(100, actor3->obj.pos.x + (D_ctx_80177A48[3] * 74.0f) + (sp4C.x * 0.6f),
                                             actor3->obj.pos.y - 232.0f + (sp4C.y * 0.8f),
                                             actor3->obj.pos.z - 1190.0f + (sp4C.z * 0.8f), sp4C.x, sp4C.y, sp4C.z,
                                             sp68, sp64, 0.0f);
                }
                if (player->csEventTimer == 1) {
                    func_effect_8007D2C8(gActors[player->meTargetIndex].obj.pos.x,
                                         gActors[player->meTargetIndex].obj.pos.y,
                                         gActors[player->meTargetIndex].obj.pos.z, 10.0f);
                    gActors[player->meTargetIndex].obj.status = OBJ_FREE;
                    Meteo_8018CCF8(&gActors[player->meTargetIndex]);
                    Object_Kill(&gPlayerShots[0].obj, gPlayerShots[0].sfxSource);
                }
            }
            break;

        case 2:
            gCsCamEyeX = player->pos.x;
            gCsCamEyeY = (player->pos.y * player->unk_148) + 50.0f;
            gCsCamEyeZ = 400.0f;
            gCsCamAtX = player->pos.x;
            gCsCamAtY = (player->pos.y * player->unk_148) + 20.0f;
            gCsCamAtZ = player->trueZpos;

            Math_SmoothStepToF(D_ctx_80177A48, 1.0f, 1.0f, 0.01f, 0.0f);

            if (player->csTimer == 0) {
                AUDIO_PLAY_BGM(gBgmSeqId);
                gLevelStartStatusScreenTimer = 80;
                player->state_1C8 = PLAYERSTATE_1C8_ACTIVE;
                player->csState = 0;
                player->csTimer = 0;
                player->csEventTimer = 0;
                player->cam.eye.x = player->pos.x;
                player->cam.eye.y = (player->pos.y * player->unk_148) + 50.0f;
                player->cam.eye.z = 400.0f;
                player->cam.at.x = player->pos.x;
                player->cam.at.y = (player->pos.y * player->unk_148) + 20.0f;
                player->cam.at.z = player->trueZpos;

                for (i = 0; i < 4; i++) {
                    Object_Kill(&gActors[i].obj, gActors[i].sfxSource);
                }

                gLoadLevelObjects = 1;
                break;
            }
    }

    switch (gCsFrameCount) {
        case 500:
            if ((gTeamShields[TEAM_ID_SLIPPY] > 0) && (gTeamShields[TEAM_ID_PEPPY] > 0)) {
                Radio_PlayMessage(gMsg_ID_3005, RCID_SLIPPY);
            }
            break;

        case 600:
            if ((gTeamShields[TEAM_ID_SLIPPY] > 0) && (gTeamShields[TEAM_ID_PEPPY] > 0)) {
                Radio_PlayMessage(gMsg_ID_3010, RCID_PEPPY);
            }
            break;

        case 700:
            Radio_PlayMessage(gMsg_ID_3015, RCID_FOX);
            break;
    }

    Math_SmoothStepToF(&player->cam.eye.x, gCsCamEyeX, D_ctx_80177A48[0], 20000.0f, 0.0f);
    Math_SmoothStepToF(&player->cam.eye.y, gCsCamEyeY, D_ctx_80177A48[0], 20000.0f, 0.0f);
    Math_SmoothStepToF(&player->cam.eye.z, gCsCamEyeZ, D_ctx_80177A48[0], 20000.0f, 0.0f);
    Math_SmoothStepToF(&player->cam.at.x, gCsCamAtX, D_ctx_80177A48[0], 20000.0f, 0.0f);
    Math_SmoothStepToF(&player->cam.at.y, gCsCamAtY, D_ctx_80177A48[0], 20000.0f, 0.0f);
    Math_SmoothStepToF(&player->cam.at.z, gCsCamAtZ, D_ctx_80177A48[0], 20000.0f, 0.0f);
}

void Meteo_8018D9EC(Actor* actor) {
    switch (actor->state) {
        case 0:
            actor->fwork[0] = RAND_FLOAT_CENTERED(10.0f);
            actor->state = 1;

        case 1:
            actor->obj.rot.z += actor->fwork[0];
            break;
    }
    Meteo_80187530(actor);
}

void Meteo_8018DA6C(Actor* actor) {
    RCP_SetupDL_60(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
    gSPDisplayList(gMasterDisp++, D_ME_6017AD0);
}

void Meteo_8018DAEC(Actor* actor) {
    RCP_SetupDL_60(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
    gSPDisplayList(gMasterDisp++, D_ME_6016240);
}

void Meteo_8018DB6C(Actor* actor) {
    RCP_SetupDL_60(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
    gSPDisplayList(gMasterDisp++, D_ME_600CD60);
}

void Meteo_8018DBEC(Effect* effect) {
    if (effect->state == 1) {
        Matrix_RotateX(gGfxMatrix, effect->obj.rot.x * M_DTOR, MTXF_APPLY);
        Matrix_Scale(gGfxMatrix, effect->scale2, effect->scale2, effect->scale2, MTXF_APPLY);
        Matrix_RotateZ(gGfxMatrix, M_PI / 2, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, effect->unk_44);
        gSPDisplayList(gMasterDisp++, D_ME_60263F0);
    }
}

void Meteo_8018DCE4(Effect* effect) {
    if (effect->state != 0) {
        Matrix_RotateX(gGfxMatrix, effect->obj.rot.x * M_DTOR, MTXF_APPLY);
        Matrix_Scale(gGfxMatrix, effect->scale2, effect->scale2, effect->scale2 * 3.0f, MTXF_APPLY);

        if ((gGameFrameCount % 2) != 0) {
            Matrix_RotateZ(gGfxMatrix, M_PI, MTXF_APPLY);
        }

        Matrix_RotateX(gGfxMatrix, -M_PI / 2, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 160, 255, 160, effect->unk_44);
        gSPDisplayList(gMasterDisp++, D_102F5E0);
    }
}

void Meteo_8018DE14(Effect* effect) {
    Matrix_RotateX(gGfxMatrix, effect->obj.rot.x * M_DTOR, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, effect->scale2, effect->scale2, effect->scale2, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, effect->unk_44);

    switch (effect->unk_4C) {
        case 0:
            gSPDisplayList(gMasterDisp++, D_ME_6023810);
        case 1:
            break;
    }
}

void Meteo_8018DF08(Actor* actor, s32 idx) {
    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_CUTSCENE;

    actor->obj.pos.x = D_i2_801955D0[idx].x + gPlayer[0].pos.x;
    actor->obj.pos.y = D_i2_801955D0[idx].y + gPlayer[0].pos.y;
    actor->obj.pos.z = D_i2_801955D0[idx].z + gPlayer[0].trueZpos;

    actor->rot_0F4.y = 0.0f;
    actor->rot_0F4.z = D_i2_80195600[idx];

    Object_SetInfo(&actor->info, actor->obj.id);

    if (idx == 3) {
        AUDIO_PLAY_SFX(NA_SE_GREATFOX_ENGINE, actor->sfxSource, 0);
        AUDIO_PLAY_SFX(NA_SE_GREATFOX_BURNER, actor->sfxSource, 0);
        actor->animFrame = 1;
    } else {
        actor->iwork[11] = 1;
        AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, actor->sfxSource, 4);
    }
}

void Meteo_LevelComplete(Player* player) {
    Vec3f src;
    Vec3f dest;
    s32 pad[5];

    gBosses[1].obj.status = OBJ_FREE;

    Math_SmoothStepToF(&player->zRotBarrelRoll, 0.0f, 0.1f, 15.0f, 0.0f);
    Math_SmoothStepToF(&player->zRotBank, 0.0f, 0.1f, 15.0f, 0.0f);
    Math_SmoothStepToF(&player->rot.y, 0.0f, 0.1f, 3.0f, 0.0f);
    Math_SmoothStepToF(&player->rot.z, 0.0f, 0.1f, 3.0f, 0.0f);
    Math_SmoothStepToF(&player->camDist, 0.0f, 0.1f, 3.0f, 0.0f);
    Math_SmoothStepToF(&player->camRoll, 0.0f, 0.1f, 3.0f, 0.0f);
    Math_SmoothStepToAngle(&player->aerobaticPitch, 0.0f, 0.1f, 20.0f, 0.0f);
    Math_SmoothStepToF(&player->boostSpeed, 0.0f, 0.1f, 3.0f, 0.0f);

    switch (player->csState) {
        case 0:
            Audio_StopSfxByBankAndSource(1, player->sfxSource);
            player->csState++;

            D_ctx_80177A48[0] = 0.0f;
            D_ctx_80177A48[1] = 0.0f;
            D_ctx_80177A48[2] = 0.0f;

            player->wings.modelId = 1;

            gCsFrameCount = 0;

        case 1:
            Matrix_RotateY(gCalcMatrix, D_ctx_80177A48[1] * M_DTOR, MTXF_NEW);
            src.x = 0.0f;
            src.y = 0.0f;
            src.z = D_ctx_80177A48[2] + 2000.0f;

            Matrix_MultVec3f(gCalcMatrix, &src, &dest);

            gCsCamEyeX = gBosses[0].obj.pos.x + dest.x;
            gCsCamEyeY = gBosses[0].obj.pos.y + dest.y;

            gCsCamEyeZ = gBosses[0].obj.pos.z + gPathProgress + dest.z;
            gCsCamAtX = gBosses[0].obj.pos.x;
            gCsCamAtY = gBosses[0].obj.pos.y;

            gCsCamAtZ = gBosses[0].obj.pos.z + gPathProgress;

            Math_SmoothStepToF(&D_ctx_80177A48[1], 180.0f, 0.05f, 1.0f, 0.0f);
            Math_SmoothStepToF(&D_ctx_80177A48[2], 1500.0f, 0.1f, 10.0f, 0.0f);
            Math_SmoothStepToF(&D_ctx_80177A48[0], 0.1f, 0.1f, 0.001f, 0.0f);
            Math_SmoothStepToF(&player->baseSpeed, 0.0f, 1.0f, 0.5f, 0.0f);
            Math_SmoothStepToF(&gBosses[0].vel.z, 0.0f, 1.0f, 0.5f, 0.0f);
            Math_SmoothStepToF(&player->rot.x, 0.0f, 0.1f, 3.0f, 0.0f);

            if (gCsFrameCount == 320) {
                gCsFrameCount = 200;
                D_ctx_80177A48[0] = 0.0f;
                D_ctx_80177A48[3] = 0.0f;
                D_ctx_80177A48[4] = 0.0f;
                player->csState++;
                player->csTimer = 100;
            }
            break;

        case 2:
            if (player->csTimer == 0) {
                Math_SmoothStepToF(&D_ctx_80177A48[3], 1.0f, 1.0f, 0.01f, 0.0f);
            }
            if (player->csTimer == 50) {
                AUDIO_PLAY_BGM(NA_BGM_COURSE_CLEAR);
            }

            Math_SmoothStepToF(&D_ctx_80177A48[1], 1080.0f, 0.01f, D_ctx_80177A48[3], 0.0f);

            if (gCsFrameCount < 500) {
                Math_SmoothStepToF(&D_ctx_80177A48[2], -1700.0f, 0.1f, 30.0f, 0.0f);
            } else if (gCsFrameCount < 800) {
                Math_SmoothStepToF(&D_ctx_80177A48[2], -1000.0f, 0.1f, 4.0f, 0.0f);
            } else if (gCsFrameCount < 1150) {
                Math_SmoothStepToF(&D_ctx_80177A48[2], -1250.0f, 0.1f, 4.0f, 0.0f);
            } else {
                Math_SmoothStepToF(&D_ctx_80177A48[2], -1500.0f, 0.1f, 4.0f, 0.0f);
            }

            if (gCsFrameCount < 400) {
                Math_SmoothStepToF(&D_ctx_80177A48[4], 0.0f, 0.03f, 0.2f, 0.0f);
            } else if (gCsFrameCount < 700) {
                Math_SmoothStepToF(&D_ctx_80177A48[4], -40.0f, 0.03f, 0.4f, 0.0f);
            } else if (gCsFrameCount < 1100) {
                Math_SmoothStepToF(&D_ctx_80177A48[4], 40.0f, 0.03f, 0.4f, 0.0f);
            } else {
                Math_SmoothStepToF(&D_ctx_80177A48[4], 7.0f, 0.03f, 0.2f, 0.0f);
            }

            Math_SmoothStepToF(D_ctx_80177A48, 0.1f, 0.1f, 0.002f, 0.0f);

            Matrix_RotateX(gCalcMatrix, D_ctx_80177A48[4] * M_DTOR, MTXF_NEW);
            Matrix_RotateY(gCalcMatrix, D_ctx_80177A48[1] * M_DTOR, MTXF_APPLY);

            src.x = 0.0f;
            src.y = 0.0f;
            src.z = D_ctx_80177A48[2] + 2000.0f;

            Matrix_MultVec3f(gCalcMatrix, &src, &dest);

            gCsCamAtX = player->pos.x;
            gCsCamAtY = player->pos.y;
            gCsCamAtZ = player->trueZpos + gPathProgress + 150.0f;

            if (gCsFrameCount > 1390) {
                player->baseSpeed += 2.0f;
                player->rot.x += 0.1f;
                player->unk_190 = 2.0f;

                if (gCsFrameCount == 1465) {
                    Audio_FadeOutAll(20);
                }

                if (gCsFrameCount > 1465) {
                    gFillScreenAlphaTarget = 255;
                    gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
                    gFillScreenAlphaStep = 8;
                    if (gFillScreenAlpha == 255) {
                        player->state_1C8 = PLAYERSTATE_1C8_NEXT;
                        player->csTimer = 0;
                        gFadeoutType = 4;
                        gLeveLClearStatus[LEVEL_METEO] = Play_CheckMedalStatus(200) + 1;
                    }
                }
            } else {
                gCsCamEyeX = player->pos.x + dest.x;
                gCsCamEyeY = player->pos.y + dest.y;
                gCsCamEyeZ = player->trueZpos + gPathProgress + 150.0f + dest.z;
            }
            break;
    }

    switch (gCsFrameCount) {
        case 350:
            Object_Kill(&gActors[0].obj, gActors[0].sfxSource);
            Object_Kill(&gActors[1].obj, gActors[1].sfxSource);
            Object_Kill(&gActors[2].obj, gActors[2].sfxSource);

            if (gTeamShields[TEAM_ID_FALCO] > 0) {
                Meteo_8018DF08(&gActors[0], 0);
            }
            if (gTeamShields[TEAM_ID_SLIPPY] > 0) {
                Meteo_8018DF08(&gActors[1], 1);
            }
            if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                Meteo_8018DF08(&gActors[2], 2);
            }
            Meteo_8018DF08(&gActors[3], 3);
            break;

        case 370:
            gLevelClearScreenTimer = 100;
            break;

        case 450:
            Radio_PlayMessage(gMsg_ID_20010, RCID_FOX);
            break;

        case 538:
            switch (gTeamShields[TEAM_ID_SLIPPY]) {
                case -1:
                    Radio_PlayMessage(gMsg_ID_20333, RCID_ROB64);
                    break;
                case 0:
                    Radio_PlayMessage(gMsg_ID_20345, RCID_ROB64);
                    break;
                default:
                    func_demo_80048AC0(TEAM_ID_SLIPPY);
                    break;
            }
            break;

        case 685:
            switch (gTeamShields[TEAM_ID_PEPPY]) {
                case -1:
                    Radio_PlayMessage(gMsg_ID_20332, RCID_ROB64);
                    break;
                case 0:
                    Radio_PlayMessage(gMsg_ID_20344, RCID_ROB64);
                    break;
                default:
                    func_demo_80048AC0(TEAM_ID_PEPPY);
                    break;
            }
            break;

        case 831:
            switch (gTeamShields[TEAM_ID_FALCO]) {
                case -1:
                    Radio_PlayMessage(gMsg_ID_20331, RCID_ROB64);
                    break;
                case 0:
                    Radio_PlayMessage(gMsg_ID_20340, RCID_ROB64);
                    break;
                default:
                    func_demo_80048AC0(TEAM_ID_FALCO);
                    break;
            }
            break;

        case 976:
            gShowLevelClearStatusScreen = 1;
            break;

        case 1176:
            gShowLevelClearStatusScreen = 0;
            break;

        case 1300:
            gActors[0].state = 1;
            break;

        case 1330:
            gActors[1].state = 1;
            break;

        case 1360:
            gActors[2].state = 1;
            break;

        case 1390:
            AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, player->sfxSource, 0);
            player->unk_194 = 5.0f;
            player->unk_190 = 5.0f;
            break;

        case 1400:
            gActors[3].state = 1;
            gActors[3].obj.pos.x = player->cam.eye.x - 700.0f;
            gActors[3].obj.pos.y = player->cam.eye.y;
            gActors[3].obj.pos.z = player->cam.eye.z - gPathProgress + 1000.0f;
            break;
    }

    Math_SmoothStepToF(&player->cam.eye.x, gCsCamEyeX, D_ctx_80177A48[0], 50000.0f, 0);
    Math_SmoothStepToF(&player->cam.eye.y, gCsCamEyeY, D_ctx_80177A48[0], 50000.0f, 0);
    Math_SmoothStepToF(&player->cam.eye.z, gCsCamEyeZ, D_ctx_80177A48[0], 50000.0f, 0);
    Math_SmoothStepToF(&player->cam.at.x, gCsCamAtX, D_ctx_80177A48[0], 50000.0f, 0);
    Math_SmoothStepToF(&player->cam.at.y, gCsCamAtY, D_ctx_80177A48[0], 50000.0f, 0);
    Math_SmoothStepToF(&player->cam.at.z, gCsCamAtZ, D_ctx_80177A48[0], 50000.0f, 0);

    Matrix_RotateY(gCalcMatrix, (player->rot.y + 180.0f) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -((player->rot.x + player->aerobaticPitch) * M_DTOR), MTXF_APPLY);

    src.x = 0.0f;
    src.y = 0.0f;
    src.z = player->baseSpeed + player->boostSpeed;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

    player->vel.x = dest.x;
    player->vel.z = dest.z;
    player->vel.y = dest.y;

    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;
    player->pos.z += player->vel.z;

    player->trueZpos = player->pos.z + player->camDist;
    player->bankAngle = player->rot.z + player->zRotBank + player->zRotBarrelRoll;
    player->bobPhase += 10.0f;
    player->yBob = -SIN_DEG(player->bobPhase) * 0.3f;
    player->rockPhase += 8.0f;
    player->rockAngle = SIN_DEG(player->rockPhase);
}

void Meteo_8018ED9C(Actor* actor) {
    Vec3f sp3C;
    Vec3f sp30;

    switch (actor->state) {
        case 0:
            actor->vwork[0].x = gPlayer[0].pos.x + D_i2_80195610[actor->index].x;
            actor->vwork[0].y = gPlayer[0].pos.y + D_i2_80195610[actor->index].y;
            actor->vwork[0].z = gPlayer[0].pos.z + D_i2_80195610[actor->index].z;

            Math_SmoothStepToF(&actor->obj.pos.x, actor->vwork[0].x, 0.02f, 50.0f, 0.0001f);
            Math_SmoothStepToF(&actor->obj.pos.y, actor->vwork[0].y, 0.02f, 50.0f, 0.0001f);
            Math_SmoothStepToF(&actor->obj.pos.z, actor->vwork[0].z, 0.02f, 50.0f, 0.0001f);
            Math_SmoothStepToF(&actor->rot_0F4.z, 0.0f, 0.03f, 0.5f, 0.0001f);
            break;

        case 1:
            actor->state = 2;
            AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, actor->sfxSource, 0);
            actor->timer_0BC = 150;
            actor->fwork[29] = 5.0f;

        case 2:
            actor->iwork[11] = 2;
            actor->fwork[0] += 2.0f;
            actor->rot_0F4.x += 0.1f;
            if (actor->timer_0BC == 0) {
                Object_Kill(&actor->obj, actor->sfxSource);
            }
            break;
    }

    Matrix_RotateY(gCalcMatrix, (actor->rot_0F4.y + 180.0f) * M_DTOR, 0U);
    Matrix_RotateX(gCalcMatrix, -(actor->rot_0F4.x * M_DTOR), 1U);

    sp3C.x = 0.0f;
    sp3C.y = 0.0f;
    sp3C.z = actor->fwork[0];

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp3C, &sp30);

    actor->vel.x = sp30.x;
    actor->vel.y = sp30.y;
    actor->vel.z = sp30.z;

    actor->obj.rot.x = -actor->rot_0F4.x;
    actor->obj.rot.y = actor->rot_0F4.y + 180.0f;
    actor->obj.rot.z = -actor->rot_0F4.z;
}
