/*
 * File: fox_me.c
 * System: Meteo
 * Description: Level: Meteo
 */

#include "global.h"
#include "assets/ast_meteo.h"
#include "fox_record.h"

// MeCrusher destroy cutscene timings recorded from a real N64
u8 gMeCrusherCutsceneRecord[] = {
    0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x02
};

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

f32 sMeLevelStartTeamSetupXpos[] = { 180.0f, -180.0f, 0.0f, -1500.0f };

f32 sMeLevelStartTeamSetupYpos[] = { 50.0f, 100.0f, -50.0f, 0.0f };

f32 sMeLevelStartTeamSetupZpos[] = { 240.0f, 480.0f, 720.0f, -5000.0f };

s32 sMeLevelStartTeamSetupModel[] = { ACTOR_CS_TEAM_ARWING, ACTOR_CS_TEAM_ARWING, ACTOR_CS_TEAM_ARWING,
                                      ACTOR_CS_GREAT_FOX };

Vec3f D_i2_801955C4 = { 0.0f, 0.0f, 100.0f };

Vec3f sMeLevelCompleteTeamSetupPos[] = { 2000.0f, 2000.0f,  2000.0f, -2000.0f, 2000.0f,  2000.0f,
                                         0.0f,    -3000.0f, 3000.0f, 5000.0f,  -3000.0f, -3000.0f };

f32 sMeLevelCompleteTeamSetupModel[] = { 75.0f, -80.0f, 85.0f, 0.0f };

Vec3f D_i2_80195610[] = {
    { 200.0f, -10.0f, 200.0f },
    { -200.0f, 20.0f, 200.0f },
    { 0.0f, 50.0f, 400.0f },
    { -2000.0f, -1000.0f, 0.0f },
};

void Meteo_ReflectDamage(Actor* this) {
    if (this->dmgType == DMG_BEAM) {
        this->dmgType = DMG_NONE;
        Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_ROCK_REFLECT);
    }
}

PosRot sMeteorGroup1[10] = {
    {
        // Meteor Number: 10000005
        // Pos:
        { -751.610779, 895.229431, -14118.559570 },
        // Rot:
        { 246.692810, 252.189011, 0.0f },
    },
    {
        // Meteor Number: 10000006
        // Pos:
        { -1496.616821, -237.345093, -13889.714844 },
        // Rot:
        { 240.222717, 204.470245, 0.0f },
    },
    {
        // Meteor Number: 10000007
        // Pos:
        { -2340.733887, 671.444031, -13942.265625 },
        // Rot:
        { 224.260315, 213.531525, 0.0f },
    },
    {
        // Meteor Number: 10000008
        // Pos:
        { -872.569824, 515.999390, -13978.042969 },
        // Rot:
        { 353.063599, 196.916153, 0.0f },
    },
    {
        // Meteor Number: 10000009
        // Pos:
        { -1244.159180, -568.048401, -13831.064453 },
        // Rot:
        { 197.289780, 116.560478, 0.0f },
    },
    {
        // Meteor Number: 1000000a
        // Pos:
        { -1766.432739, 71.170959, -13912.819336 },
        // Rot:
        { 276.255524, 353.187103, 0.0f },
    },
    {
        // Meteor Number: 1000000b
        // Pos:
        { -1174.724609, -202.646606, -14182.970703 },
        // Rot:
        { 92.375626, 72.047653, 0.0f },
    },
    {
        // Meteor Number: 1000000c
        // Pos:
        { -2022.511963, -378.516357, -14139.068359 },
        // Rot:
        { 224.973175, 315.608368, 0.0f },
    },
    {
        // Meteor Number: 1000000d
        // Pos:
        { -1707.861450, 1120.328125, -13761.345703 },
        // Rot:
        { 298.162506, 235.397705, 0.0f },
    },
    {
        // Meteor Number: 1000000e
        // Pos:
        { -1883.771973, -502.502319, -14215.611328 },
        // Rot:
        { 178.305359, 92.261642, 0.0f },
    },
};

PosRot sMeteorGroup2[5] = {
    {
        // Meteor Number: 20000004
        // Pos:
        { 182.362061, 170.138458, -7205.532715 },
        // Rot:
        { 231.369064, 257.044342, 0.0f },
    },
    {
        // Meteor Number: 20000005
        // Pos:
        { 335.380554, -309.073853, -7308.596680 },
        // Rot:
        { 324.552704, 51.662823, 0.0f },
    },
    {
        // Meteor Number: 20000006
        // Pos:
        { -1299.856689, 1078.993408, -7368.679688 },
        // Rot:
        { 130.723480, 213.801590, 0.0f },
    },
    {
        // Meteor Number: 20000007
        // Pos:
        { 196.442139, 312.897308, -7504.875000 },
        // Rot:
        { 68.665321, 15.956697, 0.0f },
    },
    {
        // Meteor Number: 20000008
        // Pos:
        { -1016.868591, 662.603943, -7195.014648 },
        // Rot:
        { 152.309296, 240.838593, 0.0f },
    },
};

void Meteo_MeMeteor1_Update(MeMeteor1* this) {
    Vec3f vec;

    if (this->dmgType != DMG_NONE) {
        this->dmgType = DMG_NONE;
        this->health -= this->damage;
        if (this->health <= 0) {
            this->obj.status = OBJ_DYING;
        }
    }

    this->obj.rot.y += 2.0f;
    this->obj.rot.x += 1.3f;

    vec.x = this->vel.x;
    vec.y = this->vel.y;
    vec.z = this->vel.z;

    if ((Object_CheckCollision(this->index, &this->obj.pos, &vec, 0) != 0) ||
        (this->obj.pos.y < (gGroundHeight + 20.0f))) {
        this->obj.status = OBJ_DYING;
    }
    Meteo_ReflectDamage(this);
}

void Meteo_MeMeteor2_Update(MeMeteor2* this) {
    Vec3f vec;

    this->obj.rot.y += 1.7f;
    this->obj.rot.x += 3.3f;
    this->work_046 -= 15;

    if (this->work_046 < 0) {
        this->work_046 = 0;
    }

    this->work_048 += 8;
    if (this->work_048 > 995) {
        this->work_048 = 995;
    }

    if ((this->timer_0BC % 4U) == 1) {
        func_effect_8007D0E0(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 6.0f);
    }

    if (this->dmgType != DMG_NONE) {
        Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_EXPLOSION_S);
        func_effect_8007D2C8(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 10.0f);
        Object_Kill(&this->obj, this->sfxSource);
    }

    if (this->timer_0C2 == 0) {
        vec.x = this->vel.x;
        vec.y = this->vel.y;
        vec.z = this->vel.z;
        if ((Object_CheckCollision(this->index, &this->obj.pos, &vec, 0) != 0) ||
            (this->obj.pos.y < (gGroundHeight + 20.0f))) {
            func_effect_8007D2C8(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 10.0f);
            this->obj.status = OBJ_DYING;
        }
    }
    Meteo_ReflectDamage(this);
}

void Meteo_MeLaserCannon2_Update(MeLaserCannon2* this) {
    Vec3f dest;
    Vec3f src;

    this->obj.rot.z += 1.0f;

    Matrix_RotateZ(gCalcMatrix, this->obj.rot.z * M_DTOR, MTXF_NEW);

    src.x = 0.0f;
    src.y = -1100.0f;
    src.z = 0.0f;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

    this->obj.pos.x = this->fwork[0] + dest.x;
    this->obj.pos.y = this->fwork[1] + dest.y;

    if (this->dmgType != DMG_NONE) {
        Actor_Despawn(this);
        Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_EXPLOSION_S);
        Object_Kill(&this->obj, this->sfxSource);
        func_effect_8007D0E0(this->obj.pos.x, this->obj.pos.y + 30.0f, this->obj.pos.z, 5.0f);
        Effect386_Spawn1(this->obj.pos.x, this->obj.pos.y + 30.0f, this->obj.pos.z, 0.0f, 0.0f, 0.0f, 3.0f, 10);
    }

    if (this->timer_0BC == 0) {
        this->timer_0BC = 40;
        if (this->obj.pos.z < (gPlayer[0].trueZpos - 1000.0f)) {
            Effect_EnemyLaser(OBJ_EFFECT_ENEMY_LASER_1, this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 120.0f);
        }
    }
}

void Meteo_MeLaserCannon1_Update(MeLaserCannon1* this) {
    Vec3f vec;
    s32 pad[2];

    this->obj.rot.y += 7.0f;
    this->obj.rot.x += 3.3f;

    if (this->dmgType != DMG_NONE) {
        Actor_Despawn(this);
        Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_EXPLOSION_S);
        Object_Kill(&this->obj, this->sfxSource);
        func_effect_8007D0E0(this->obj.pos.x - this->vel.x, this->obj.pos.y, this->obj.pos.z - this->vel.z, 8.0f);
        Effect386_Spawn1(this->obj.pos.x - this->vel.x, this->obj.pos.y + 30.0f, this->obj.pos.z - this->vel.z, 0.0f,
                         0.0f, 0.0f, 4.0f, 10);
    }

    if ((gGameFrameCount % 8) == 0) {
        Math_Vec3fFromAngles(&vec, this->obj.rot.x, this->obj.rot.y, 100.0f);
        func_effect_8007F04C(OBJ_EFFECT_ENEMY_LASER_1, this->obj.pos.x + (vec.x * 3.0f),
                             this->obj.pos.y + (vec.y * 3.0f), this->obj.pos.z + (vec.z * 3.0f), this->obj.rot.x,
                             this->obj.rot.y, this->obj.rot.z, 0.0f, 0.0f, 0.0f, vec.x, vec.y, vec.z, 1.0f);
    }
}

void Meteo_80187B08(MeLaserCannon1* this) {
    this->obj.rot.y += 7.0f;
    this->obj.rot.x += 3.3f;

    this->work_046 -= 11;

    if (this->work_046 < 0) {
        this->work_046 = 0;
    }

    this->work_048 += 4;
    if (this->work_048 > 995) {
        this->work_048 = 995;
    }

    if ((this->timer_0BC % 4) == 0) {
        func_effect_8007D0E0(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 6.0f);
    }

    if ((this->dmgType != DMG_NONE) || (this->timer_0BC == 0)) {
        Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_EXPLOSION_S);
        Object_Kill(&this->obj, this->sfxSource);
        func_effect_8007D0E0(this->obj.pos.x - this->vel.x, this->obj.pos.y, this->obj.pos.z - this->vel.z, 8.0f);
        Effect386_Spawn1(this->obj.pos.x - this->vel.x, this->obj.pos.y + 30.0f, this->obj.pos.z - this->vel.z, 0.0f,
                         0.0f, 0.0f, 4.0f, 10);
    }
}

void Meteo_80187C68(Actor* this, f32 x, f32 y, f32 z, f32 arg4, f32 xRot, f32 yRot, s32 timerBC, s32 eventType,
                    s32 objId) {
    Actor_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = objId;

    this->obj.pos.x = x;
    this->obj.pos.y = y;
    this->obj.pos.z = z;

    this->obj.rot.x = xRot;
    this->obj.rot.y = yRot;

    this->timer_0BC = timerBC;
    this->timer_0BE = 20;
    this->eventType = eventType;
    this->fwork[5] = arg4;
    Object_SetInfo(&this->info, this->obj.id);
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

void Meteo_80187D98(Effect369* this, f32 x, f32 y, f32 z, f32 arg4, bool rotate) {
    Effect_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_EFFECT_369;

    this->obj.pos.x = x;
    this->obj.pos.y = y;
    this->obj.pos.z = z;

    this->unk_60.z = arg4;
    this->unk_48 = rotate;
    this->obj.rot.x = 45.0f;

    if (rotate) {
        this->obj.rot.x = -45.0f;
    }

    Object_SetInfo(&this->info, this->obj.id);
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

void Meteo_80187FF8(Effect371* this, f32 x, f32 y, f32 z) {
    Effect_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_EFFECT_371;

    this->obj.pos.x = x;
    this->obj.pos.y = y;
    this->obj.pos.z = z;

    this->unk_44 = 128;
    this->vel.z = 50.0f;
    this->scale2 = 1.0f;
    Object_SetInfo(&this->info, this->obj.id);
}

void Meteo_80188088(MeCrusher* this) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Meteo_80187FF8(&gEffects[i], this->obj.pos.x + 700.0f, this->obj.pos.y, this->obj.pos.z + 1235.0f);
            AUDIO_PLAY_SFX(NA_SE_EN_RNG_BEAM_SHOT, gEffects[i].sfxSource, 4);
            break;
        }
    }

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Meteo_80187FF8(&gEffects[i], this->obj.pos.x - 700.0f, this->obj.pos.y, this->obj.pos.z + 1235.0f);
            break;
        }
    }
}

void Meteo_Effect370_Setup1(Effect370* this, f32 x, f32 y, f32 z, f32 zRot, s32 arg5) {
    Effect_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_EFFECT_370;

    this->obj.pos.x = x;
    this->obj.pos.y = y;
    this->obj.pos.z = z;

    this->obj.rot.z = zRot;

    this->state = arg5;
    Object_SetInfo(&this->info, this->obj.id);
}

void Meteo_Effect370_Spawn1(f32 x, f32 y, f32 z, f32 zRot) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Meteo_Effect370_Setup1(&gEffects[i], x, y, z, zRot, 0);
            break;
        }
    }
}

void Meteo_Effect370_Spawn2(f32 x, f32 y, f32 z, f32 zRot) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Meteo_Effect370_Setup1(&gEffects[i], x, y, z, zRot, -1);
            AUDIO_PLAY_SFX(NA_SE_EN_GRN_BEAM_SHOT, gEffects[i].sfxSource, 4);
            break;
        }
    }
}

void Meteo_MeCrusherShield_Update(MeCrusherShield* this) {
    Vec3f src;
    Vec3f dest;
    f32 temp;

    if (this->state < 5) {
        this->obj.pos.x = gBosses[0].obj.pos.x;
        this->obj.pos.y = gBosses[0].obj.pos.y;
        this->obj.pos.z = gBosses[0].obj.pos.z;
        this->obj.rot.x = gBosses[0].obj.rot.x;
        this->obj.rot.y = gBosses[0].obj.rot.y;
        this->obj.rot.z = gBosses[0].obj.rot.z + this->rot_078.z + 45.0f + 180.0f;
    }

    switch (this->state) {
        case 0:
            this->timer_050 = 150;
            this->rot_078.z += 2.5f;
            break;

        case 1:
            temp = fabsf(90.0f - this->rot_078.z) * 0.1f;
            if (temp > 2.5f) {
                temp = 2.5f;
            }

            this->rot_078.z += temp;

            if (this->timer_050 == 0) {
                this->state = 2;
                this->dmgType = DMG_NONE;
            }
            break;

        case 2:
            if (this->dmgType == DMG_BEAM) {
                this->dmgType = DMG_NONE;
                this->timer_054 = 5;
                this->swork[0] += 32;

                Audio_SetTransposeAndPlaySfx(this->sfxSource, NA_SE_EN_GRN_BEAM_CHARGE, this->work_04A);

                this->work_04A++;
                if (this->work_04A > 7) {
                    this->work_04A = 7;
                }

                if (this->swork[0] >= 255) {
                    this->work_04A = 0;

                    Audio_KillSfxBySource(this->sfxSource);

                    if (this->swork[1] == 0) {
                        this->swork[1]++;
                        Radio_PlayMessage(gMsg_ID_3315, RCID_PEPPY);
                    }

                    this->swork[0] = 0;

                    Matrix_RotateZ(gCalcMatrix, (this->obj.rot.z - 45.0f) * M_DTOR, MTXF_NEW);

                    src.x = 0.0f;
                    src.y = 156.0f;
                    src.z = 930.0f;

                    Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

                    Meteo_Effect370_Spawn2(this->obj.pos.x + dest.x, this->obj.pos.y + dest.y, this->obj.pos.z + dest.z,
                                           this->obj.rot.z - 45.0f);
                    Meteo_Effect370_Spawn1(this->obj.pos.x - dest.x, this->obj.pos.y - dest.y, this->obj.pos.z + dest.z,
                                           this->obj.rot.z - 45.0f);
                    Meteo_Effect370_Spawn1(this->obj.pos.x + dest.y, this->obj.pos.y - dest.x, this->obj.pos.z + dest.z,
                                           (this->obj.rot.z - 45.0f) + 90.0f);
                }
            }
            break;

        case 3:
            this->timer_050 = 30;
            this->state = 4;
            this->timer_05C = 15;
            this->swork[0] = 0;
            break;

        case 4:
            if (this->timer_050 == 0) {
                func_effect_8007D2C8(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + 500.0f, 30.0f);
                Effect386_Spawn1(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + 500.0f, 0.0f, 0.0f, 0.0f, 20.0f,
                                 30);
                this->state = 5;

                this->info.cullDistance = 1000.0f;

                Audio_KillSfxBySourceAndId(this->sfxSource, NA_SE_EN_GRN_BEAM_CHARGE);
                AUDIO_PLAY_SFX(NA_SE_EN_MEBOSS_SHIELD, this->sfxSource, 4);
            }
            break;

        case 5:
            this->obj.rot.z -= 3.0f;
            if (this->vel.z < 5.0f) {
                this->vel.z = this->vel.z + 1.0f;
            }
            break;
    }

    if (this->rot_078.z >= 360.0f) {
        this->rot_078.z -= 360.0f;
    }
    if (this->rot_078.z < 0.0f) {
        this->rot_078.z += 360.0f;
    }
}

void Meteo_MeCrusherShield_Draw(MeCrusherShield* this) {
    s32 i;

    if ((this->timer_054 % 2) != 0) {
        RCP_SetupDL_27();
        gDPSetPrimColor(gMasterDisp++, 0, 0, 0, 255, 0, 255);
    }

    Matrix_RotateZ(gGfxMatrix, (M_PI / 4), MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_ME_60240B0);
    RCP_SetupDL_64();

    for (i = 1; i < 4; i++) {
        if (this->swork[0] != 0) {
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, this->swork[0]);
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

void Meteo_MeCrusher_Init(MeCrusher* this) {
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

    i = this->work_044 = 1;

    Boss_Initialize(&gBosses[i]);

    gBosses[i].obj.status = OBJ_INIT;
    gBosses[i].obj.id = OBJ_BOSS_ME_CRUSHER_SHIELD;
    gBosses[i].obj.pos.x = this->obj.pos.x;
    gBosses[i].obj.pos.y = this->obj.pos.y;
    gBosses[i].obj.pos.z = this->obj.pos.z;

    Object_SetInfo(&gBosses[i].info, gBosses[i].obj.id);
    Radio_PlayMessage(gMsg_ID_3300, RCID_BOSS_METEO);
    AUDIO_PLAY_SFX(NA_SE_EN_BURNER_L, this->sfxSource, 4);
}

void Meteo_Effect369_Setup(Effect369* this, f32 x, f32 y, f32 z, f32 xRot, f32 yRot, f32 arg6, f32 arg7) {
    Effect_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_EFFECT_369;

    this->obj.pos.x = x;
    this->obj.pos.y = y;
    this->obj.pos.z = z;

    this->obj.rot.x = xRot;
    this->obj.rot.y = yRot;
    this->unk_60.z = arg6;

    this->timer_50 = 20;
    this->scale2 = arg7;
    this->state = 1;
    this->unk_44 = 128;
    Object_SetInfo(&this->info, this->obj.id);
}

void Meteo_Effect369_Spawn(f32 x, f32 y, f32 z, f32 xRot, f32 yRot, f32 arg5, f32 arg6) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Meteo_Effect369_Setup(&gEffects[i], x, y, z, xRot, yRot, arg5, arg6);
            return;
        }
    }
}

void Meteo_Effect369_Update(Effect369* this) {
    Vec3f src;
    Vec3f dest;

    if (this->state == 0) {
        switch (this->unk_48) {
            case 0:
                this->obj.rot.x -= 15.0f;
                if (this->obj.rot.x <= -45.0f) {
                    this->unk_48 = 1;
                }
                break;

            case 1:
                this->obj.rot.x += 15.0f;
                if (this->obj.rot.x >= 45.0f) {
                    this->unk_48 = 0;
                }
                break;
        }

        this->unk_44 = 255;
        this->scale2 = 1.0f;
        this->unk_60.z += 20.0f;

        Matrix_RotateZ(gCalcMatrix, this->unk_60.z * M_DTOR, MTXF_NEW);
        Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);

        src.x = 0.0f;
        src.y = 0.0f;
        src.z = 80.0f;

        Matrix_MultVec3f(gCalcMatrix, &src, &dest);

        this->vel.x = dest.x;
        this->vel.y = dest.y;
        this->vel.z = dest.z;

        Meteo_Effect369_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, this->obj.rot.x, this->obj.rot.y,
                              this->unk_60.z, 1.0f);
    } else if (this->timer_50 == 0) {
        Object_Kill(&this->obj, this->sfxSource);
    }

    func_effect_8007A774(gPlayer, this, 90.0f);
}

void Meteo_Effect370_Setup2(Effect370* this, f32 x, f32 y, f32 z, f32 xRot, f32 yRot, f32 zRot, f32 scale) {
    Effect_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_EFFECT_370;

    this->obj.pos.x = x;
    this->obj.pos.y = y;
    this->obj.pos.z = z;

    this->obj.rot.x = xRot;
    this->obj.rot.y = yRot;
    this->obj.rot.z = zRot;

    this->scale2 = scale;
    this->state = 1;
    this->unk_44 = 128;
    Object_SetInfo(&this->info, this->obj.id);
}

void Meteo_Effect370_Spawn3(f32 x, f32 y, f32 z, f32 xRot, f32 yRot, f32 arg5, f32 scale) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Meteo_Effect370_Setup2(&gEffects[i], x, y, z, xRot, yRot, arg5, scale);
            return;
        }
    }
}

void Meteo_Effect370_Update(Effect370* this) {
    Vec3f src;
    Vec3f dest;

    if (this->state != 1) {
        this->obj.rot.x = 10.0f;
        this->obj.rot.z += 20.0f;

        Matrix_RotateZ(gCalcMatrix, this->obj.rot.z * M_DTOR, MTXF_NEW);
        Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);

        src.x = 0.0f;
        src.y = 0.0f;
        src.z = 80.0f;

        Matrix_MultVec3f(gCalcMatrix, &src, &dest);

        this->vel.x = dest.x;
        this->vel.y = dest.y;
        this->vel.z = dest.z;

        if ((gGameFrameCount % 2) == 0) {
            Meteo_Effect370_Spawn3(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, this->obj.rot.x, this->obj.rot.y,
                                   this->obj.rot.z, 5.0f);
        }
    } else {
        this->unk_44 -= 8;
        if (this->unk_44 < 0) {
            Object_Kill(&this->obj, this->sfxSource);
        }
    }
    func_effect_8007A774(gPlayer, this, 60.0f);
}

void Meteo_Effect371_Update(Effect371* this) {
    if (gPlayer[0].state == PLAYERSTATE_LEVEL_COMPLETE) {
        Object_Kill(&this->obj, this->sfxSource);
    }

    this->scale2 += 0.5f;
    if (this->scale2 > 10.0f) {
        this->scale2 = 10.0f;
    }

    this->obj.rot.z += 35.0f;
    if (this->obj.pos.x < gPlayer[0].pos.x) {
        this->obj.pos.x += 1.5f;
        if (this->vel.x < 40.0f) {
            this->vel.x += 2.0f;
        }
    }

    if (gPlayer[0].pos.x < this->obj.pos.x) {
        this->obj.pos.x -= 1.5f;
        if (this->vel.x > -40.0f) {
            this->vel.x -= 2.0f;
        }
    }

    if (this->obj.pos.y < gPlayer[0].pos.y) {
        this->obj.pos.y += 1.5f;
        if (this->vel.y < 40.0f) {
            this->vel.y += 2.0f;
        }
    }

    if (gPlayer[0].pos.y < this->obj.pos.y) {
        this->obj.pos.y -= 1.5f;
        if (this->vel.y > -40.0f) {
            this->vel.y -= 2.0f;
        }
    }

    func_effect_8007A774(gPlayer, this, 100.0f);
}

void Meteo_801892F0(MeCrusher* this, s32 dmgPart) {
    Vec3f dest;
    Vec3f src;

    Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_EXPLOSION_M);

    if (dmgPart == 7) {
        func_effect_8007D2C8(this->obj.pos.x, this->obj.pos.y + 330.0f, this->obj.pos.z + 1020.0f, 15.0f);
        Effect386_Spawn1(this->obj.pos.x, this->obj.pos.y + 330.0f, this->obj.pos.z + 1020.0f, 0.0f, 0.0f, 0.0f, 7.0f,
                         20);
    }

    if (dmgPart == 5) {
        func_effect_8007D2C8(this->obj.pos.x, this->obj.pos.y - 330.0f, this->obj.pos.z + 1020.0f, 15.0f);
        Effect386_Spawn1(this->obj.pos.x, this->obj.pos.y - 330.0f, this->obj.pos.z + 1020.0f, 0.0f, 0.0f, 0.0f, 7.0f,
                         20);
    }

    if (dmgPart == 4) {
        func_effect_8007D2C8(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + 300.0f, 20.0f);
        Effect386_Spawn1(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + 300.0f, 0.0f, 0.0f, 0.0f, 10.0f, 25);
    }

    if (dmgPart < 4) {
        Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
        Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);
        Matrix_RotateZ(gCalcMatrix, this->obj.rot.z * M_DTOR, MTXF_APPLY);
        Matrix_RotateZ(gCalcMatrix, M_DTOR * 90.0f * dmgPart, MTXF_APPLY);

        src.x = 0.0f;
        src.y = 200.0f;
        src.z = 500.0f;

        Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

        func_effect_8007D2C8(this->obj.pos.x + dest.x, this->obj.pos.y + dest.y, this->obj.pos.z + dest.z, 10.0f);
        Effect386_Spawn1(this->obj.pos.x + dest.x, this->obj.pos.y + dest.y, this->obj.pos.z + dest.z, 0.0f, 0.0f, 0.0f,
                         5.0f, 15);
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

void Meteo_MeCrusher_Update(MeCrusher* this) {
    f32 sp7C;
    f32 rand;
    s32 i;
    s32 var_v0;

    Vec3f src;
    Vec3f dest;

    gBossFrameCount++;

    Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);
    Matrix_RotateZ(gCalcMatrix, this->obj.rot.z * M_DTOR, MTXF_APPLY);

    if ((gGameFrameCount & 0x10) != 0) {
        this->swork[19] += 32;
        if (this->swork[19] > 128) {
            this->swork[19] = 128;
        }
    } else {
        this->swork[19] -= 32;
        if (this->swork[19] < 0) {
            this->swork[19] = 0;
        }
    }

    if ((gGameFrameCount & 0x38) == 0) {
        this->fwork[3] = D_i2_80195534[gGameFrameCount % 8U];
        this->fwork[4] = D_i2_80195534[gGameFrameCount % 8U];
        this->fwork[5] = D_i2_80195534[gGameFrameCount % 8U];
        this->fwork[6] = D_i2_80195534[gGameFrameCount % 8U];
    }

    if (((gGameFrameCount + 20) & 0x38) == 0) {
        this->fwork[7] = D_i2_80195534[(gGameFrameCount + 20) % 8U];
        this->fwork[8] = D_i2_80195534[(gGameFrameCount + 20) % 8U];
    }

    if (this->swork[9] != 0) {
        this->swork[9]--;
    }

    if (this->swork[10] != 0) {
        this->swork[10]--;
    }

    if (this->swork[11] != 0) {
        this->swork[11]--;
    }

    if (this->swork[12] != 0) {
        this->swork[12]--;
    }

    if (this->swork[13] != 0) {
        this->swork[13]--;
    }

    if (this->swork[14] != 0) {
        this->swork[14]--;
    }

    if (this->swork[15] != 0) {
        this->swork[15]--;
    }

    if (this->swork[0] > 5) {
        this->swork[0]--;
        if (this->swork[0] == 5) {
            Audio_KillSfxBySourceAndId(this->sfxSource, NA_SE_EN_BURNER_L);
        }
    }

    if (this->swork[1] > 5) {
        this->swork[1] = this->swork[1] - 1;
        if (this->swork[1] == 5) {
            Audio_KillSfxBySourceAndId(this->sfxSource, NA_SE_EN_BURNER_L);
        }
    }

    if (this->dmgType != DMG_NONE) {
        this->dmgType = DMG_NONE;
        if ((this->dmgPart != 7) && (this->dmgPart >= 5) && (this->dmgPart != 5)) {
            AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
        }

        if ((this->state >= 2) && (this->state < 20)) {
            if ((this->dmgPart < 5) && (this[0].fwork[17 + this->dmgPart] > 0.5f)) {
                if (this[0].swork[this->dmgPart + 2] != 0) {
                    AUDIO_PLAY_SFX(NA_SE_OB_DAMAGE_M, this->sfxSource, 4);

                    this[0].swork[9 + this->dmgPart] = 20;
                    this[0].swork[2 + this->dmgPart] -= this->damage;

                    if (this[0].swork[2 + this->dmgPart] <= 0) {
                        this[0].swork[2 + this->dmgPart] = 0;
                        Meteo_801892F0(this, this->dmgPart);
                        this->swork[20]++;
                        if (this->swork[20] == 2) {
                            Radio_PlayMessage(gMsg_ID_17160, RCID_PEPPY);
                        }
                        if (this->swork[20] == 3) {
                            Radio_PlayMessage(gMsg_ID_3371, RCID_BOSS_METEO);
                        }
                        if (this->swork[20] == 4) {
                            Radio_PlayMessage(gMsg_ID_3320, RCID_BOSS_METEO);
                        }
                    }
                } else {
                    AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
                }
            }

            if (this->state >= 9) {
                if (this->dmgPart == 5) {
                    if ((this->swork[7] != 0) && (this->fwork[22] > 0.8f)) {
                        AUDIO_PLAY_SFX(NA_SE_EN_KNOCK_DOWN, this->sfxSource, 4);
                        this->swork[14] = 20;
                        this->swork[7] -= this->damage;
                        if (this->swork[7] <= 0) {
                            this->swork[7] = 0;
                            Meteo_801892F0(this, this->dmgPart);
                        }
                    } else {
                        AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
                    }
                }

                if (this->dmgPart == 7) {
                    if ((this->swork[8] != 0) && (this->fwork[23] > 0.8f)) {
                        AUDIO_PLAY_SFX(NA_SE_EN_KNOCK_DOWN, this->sfxSource, 4);
                        this->swork[15] = 20;
                        this->swork[8] -= this->damage;
                        if (this->swork[8] <= 0) {
                            this->swork[8] = 0;
                            Meteo_801892F0(this, this->dmgPart);
                        }
                    } else {
                        AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
                    }
                }

                if (this->swork[7] <= 0) {
                    if (this->swork[8] <= 0) {
                        Boss_AwardBonus(this);

                        this->state = 20;
                        this->timer_050 = 300;
                        this->timer_052 = 260;
                        this->vel.x = 0.0f;
                        this->vel.y = 0.0f;

                        if ((gPlayer[0].state == PLAYERSTATE_ACTIVE) || (gPlayer[0].state == PLAYERSTATE_U_TURN)) {
                            gPlayer[0].state = PLAYERSTATE_LEVEL_COMPLETE;
                            gPlayer[0].csState = 0;
                            gCsFrameCount = 0;
                        }

                        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 50);
                        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 50);
                        AUDIO_PLAY_SFX(NA_SE_EN_DOWN_IMPACT, this->sfxSource, 4);
                        gScreenFlashTimer = 8;
                    }
                }
            }
        }
    }

    sp7C = this->obj.pos.z + gPathProgress;

    if (this->state >= 3) {
        if (this->state < 20) {
            Math_SmoothStepToF(&this->vel.z, -gArwingSpeed, 0.1f, 2.0f, 0.0f);
            if ((this->fwork[9] + 200.0f) < sp7C) {
                Math_SmoothStepToF(&this->vel.z, -60.0f, 0.1f, 4.0f, 0.0f);
            }
            if (sp7C < (this->fwork[9] - 300.0f)) {
                Math_SmoothStepToF(&this->vel.z, 20.0f, 0.1f, 4.0f, 0.0f);
            }
        }
    }

    if ((this->state >= 3) && (this->state < 20)) {
        switch (this->swork[16]) {
            case 0:
                if (this->vel.y > 0.0f) {
                    this->vel.y -= 0.2f;
                }
                if (this->vel.y < 0.0f) {
                    this->vel.y += 0.2f;
                }

                if (this->timer_054 == 0) {
                    this->timer_054 = 20;
                    this->fwork[13] = 7.0f;
                    if (this->obj.pos.y > 0.0f) {
                        this->fwork[13] = -7.0f;
                    }
                    this->timer_054 = RAND_INT(30.0f) + 40.0f;
                    this->swork[16] = 1;
                }
                break;

            case 1:
                if (this->fwork[13] < this->vel.y) {
                    this->vel.y = this->vel.y - 0.2f;
                }

                if (this->vel.y < this->fwork[13]) {
                    this->vel.y += 0.2f;
                }

                if (this->timer_054 == 0) {
                    this->swork[16] = 0;
                    this->timer_054 = RAND_INT(30.0f) + 40.0f;
                }
                break;
        }

        switch (this->swork[17]) {
            case 0:
                if (this->vel.x > 0.0f) {
                    this->vel.x = this->vel.x - 0.2f;
                }

                if (this->vel.x < 0.0f) {
                    this->vel.x += 0.2f;
                }

                if (this->timer_056 == 0) {
                    this->timer_056 = 20;
                    this->fwork[14] = 7.0f;
                    if (this->obj.pos.x > 0.0f) {
                        this->fwork[14] = -7.0f;
                    }
                    this->timer_056 = RAND_INT(40.0f) + 50.0f;
                    this->swork[17] = 1;
                }
                break;

            case 1:
                if (this->fwork[14] < this->vel.x) {
                    this->vel.x = this->vel.x - 0.2f;
                }
                if (this->vel.x < this->fwork[14]) {
                    this->vel.x += 0.2f;
                }
                if (this->timer_056 == 0) {
                    this->swork[17] = 0;
                    this->timer_056 = RAND_INT(40.0f) + 50.0f;
                }
                break;
        }
    }

    if (this->swork[18] != 0) {
        s32 objId;

        if (ActorMissileSeek_ModeCheck(0) >= 4) {
            objId = OBJ_ACTOR_MISSILE_SEEK_PLAYER;
        } else {
            objId = OBJ_ACTOR_MISSILE_SEEK_TEAM;
        }

        AUDIO_PLAY_SFX(NA_SE_EN_BARREL_SHOT, this->sfxSource, 4);

        src.x = 0.0f;
        src.y = 330.0f;
        src.z = -1022.0f;

        Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

        if (this->swork[18] == 1) {
            Meteo_80187D08(this->obj.pos.x + dest.x, this->obj.pos.y + dest.y, this->obj.pos.z + dest.z, 50.0f, 270.0f,
                           0.0f, 30, 0, objId);
        } else {
            Meteo_80187D08(this->obj.pos.x + dest.x, this->obj.pos.y + dest.y, this->obj.pos.z + dest.z, 50.0f, 0.0f,
                           0.0f, 0, 0, objId);
        }

        src.y = -330.0f;

        Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

        if (this->swork[18] == 1) {
            Meteo_80187D08(this->obj.pos.x + dest.x, this->obj.pos.y + dest.y, this->obj.pos.z + dest.z, 50.0f, 90.0f,
                           0.0f, 30, 0, objId);
        } else {
            Meteo_80187D08(this->obj.pos.x + dest.x, this->obj.pos.y + dest.y, this->obj.pos.z + dest.z, 50.0f, 0.0f,
                           0.0f, 0, 0, objId);
        }
        this->swork[18] = 0;
    }

    if ((sp7C < 200.0f) && (sp7C > -1500.0f)) {
        gLight2xRotTarget = 0.0f;
        gLight2yRotTarget = 150.0f;
        gLight2zRotTarget = 0.0f;
    }

    switch (this->state) {
        case 0:
            this->swork[0] = 10;
            this->swork[1] = 10;

            this->obj.pos.y += ((0.0f - this->obj.pos.y) * this->fwork[1]);
            this->vel.z = this->fwork[0] - gPathVelZ;

            if (sp7C < this->fwork[9]) {
                this->state = 1;
                this->fwork[1] = 0.0f;
            }

            if (sp7C < -1000.0f) {
                if (this->fwork[1] < 0.005f) {
                    this->fwork[1] = this->fwork[1] + 0.0001f;
                }
            }
            break;

        case 1:
            this->obj.pos.y += ((0.0f - this->obj.pos.y) * this->fwork[1]);
            this->vel.z = this->fwork[0] - gPathVelZ;

            if (this->fwork[0] < 0.0f) {
                this->fwork[0] += 0.5f;
                if (this->fwork[0] >= 0.0f) {
                    this->state = 2;
                    this->timer_050 = 50;
                    gBosses[this->work_044].state = 1;
                }
            }

            if (this->fwork[1] < 0.005f) {
                this->fwork[1] = this->fwork[1] + 0.0001f;
            }
            break;

        case 2:
            this->obj.pos.y += ((0.0f - this->obj.pos.y) * this->fwork[1]);
            this->vel.z = this->fwork[0] - gPathVelZ;

            if (this->fwork[1] < 0.05f) {
                this->fwork[1] = this->fwork[1] + 0.0004f;
            }

            if (this->timer_050 == 0) {
                this->state = 3;
                this->timer_050 = 50;
                this->timer_058 = 100;
                Radio_PlayMessage(gMsg_ID_3310, RCID_BOSS_METEO);
            }
            break;

        case 3:
            if (this->timer_052 == 0) {
                rand = Rand_ZeroOne();
                this->fwork[9] = -3000.0f;
                if (rand < 0.3f) {
                    this->fwork[9] = -2000.0f;
                }
                if (rand > 0.7f) {
                    this->fwork[9] = -4000.0f;
                }
                this->timer_052 = 80;
            } else if (this->vel.z < -50.0f) {
                if (this->swork[0] == 5) {
                    AUDIO_PLAY_SFX(NA_SE_EN_BURNER_L, this->sfxSource, 4);
                }

                if (this->swork[0] < 10) {
                    this->swork[0] += 2;
                    if (this->swork[0] > 10) {
                        this->swork[0] = 10;
                    }
                }

                if (this->swork[1] < 10) {
                    this->swork[1] += 2;
                    if (this->swork[1] > 10) {
                        this->swork[1] = 10;
                    }
                }
            }

            if (gBosses[this->work_044].state < 3) {
                var_v0 = 0;
                if (this->swork[2] == 0) {
                    var_v0 = 1;
                    this->obj.rot.z += 0.1f;
                }
                if (this->swork[3] == 0) {
                    var_v0++;
                    this->obj.rot.z += 0.1f;
                }
                if (this->swork[4] == 0) {
                    var_v0++;
                    this->obj.rot.z += 0.1f;
                }
                if (this->swork[5] == 0) {
                    var_v0++;
                    this->obj.rot.z += 0.1f;
                }
                if (var_v0 == 4) {
                    gBosses[this->work_044].state = 3;
                    this->state = 4;
                    this->timer_050 = 250;
                    this->timer_05A = 30;
                    this->fwork[10] = 0;
                }

                if ((this->timer_050 == 0) && (gBosses[this->work_044].state == 2)) {
                    this->fwork[2] = 90.0f;
                    this->timer_050 = D_i2_80195520[var_v0] + 45;
                    AUDIO_PLAY_SFX(NA_SE_EN_SHIELD_ROLL, this->sfxSource, 4);
                }

                if (this->fwork[2] > 0.0f) {
                    this->fwork[2] -= 2.0f;
                    gBosses[this->work_044].rot_078.z -= 2.0f;
                }
            }

            if (this->timer_058 == 0) {
                this->timer_058 = RAND_INT(80.0f) + 180.0f;
                this->swork[18] = 1;
            }
            break;

        case 4:
            this->fwork[9] = -3000.0f;
            if (this->fwork[10] < 0.02f) {
                this->fwork[10] += 0.0002f;
            }
            this->obj.rot.z += ((0.0f - this->obj.rot.z) * this->fwork[10]);
            if (this->timer_050 == 100) {
                Radio_PlayMessage(gMsg_ID_3321, RCID_BOSS_METEO);
            }
            if (this->timer_050 == 0) {
                this->state = 5;
                this->timer_050 = 70;
            }
            break;

        case 5:
            this->obj.rot.z += ((0.0f - this->obj.rot.z) * 0.02f);

            if (this->timer_050 == 1) {
                AUDIO_PLAY_SFX(NA_SE_EN_S_BEAM_CHARGE, this->sfxSource, 4);
            }

            if (this->timer_050 == 0) {
                gLight1xRotTarget = 0.0f;
                gLight1yRotTarget = 5.0f;
                gLight1zRotTarget = 0.0f;
                gLight2xRotTarget = 0.0f;
                gLight2yRotTarget = 100.0f;
                gLight2zRotTarget = 0.0f;
                gLight1rotStep = 5.0f;
                gLight2rotStep = 5.0f;

                if (this->fwork[11] < 70.0f) {
                    this->fwork[11] += 1.0f;
                    if (this->fwork[11] > 20.0f) {
                        this->fwork[11] += 1.0f;
                    }
                } else {
                    this->state = 6;
                    this->timer_050 = 75;
                }

                if (this->fwork[11] > 30.0f) {
                    Meteo_80189624();
                }
            }
            break;

        case 6:
            this->obj.rot.z = this->obj.rot.z + ((0.0f - this->obj.rot.z) * 0.02f);
            Math_SmoothStepToF(&this->fwork[0x15], 4.0f, 1.0f, 0.1f, 0.0f);

            if (gPlayer[0].state != PLAYERSTATE_NEXT) {
                gFillScreenRed = gFillScreenAlpha = gFillScreenGreen = gFillScreenBlue = 0;

                if ((this->timer_050 == 10) || (this->timer_050 == 30) || (this->timer_050 == 50) ||
                    (this->timer_050 == 70)) {
                    gFillScreenAlpha = 150;
                    gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
                    Meteo_80187E38(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + 1300.0f,
                                   this->fwork[12] + this->obj.rot.z);
                    this->fwork[12] = RAND_FLOAT(360.0f);
                }
                if ((this->timer_050 == 13) || (this->timer_050 == 33) || (this->timer_050 == 53) ||
                    (this->timer_050 == 73)) {
                    gFillScreenAlpha = 150;
                    gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
                }
                if (this->timer_050 == 0) {
                    this->state = 7;
                    AUDIO_PLAY_SFX(NA_SE_EN_S_BEAM_END, this->sfxSource, 4);
                }
                Meteo_80189624();
            }
            break;

        case 7:
            if (this->fwork[11] > 26.0f) {
                Meteo_80189624();
            }

            if (this->fwork[11] > 0.0f) {
                this->fwork[11] -= 2.0f;
                if (this->fwork[11] <= 0.0f) {
                    this->fwork[11] = 0.0f;
                    Audio_KillSfxBySource(this->sfxSource);
                    if (this->swork[6] == 0) {
                        this->state = 8;

                        this->timer_050 = 190;
                        this->timer_052 = 230;

                        this->fwork[10] = 0.0f;
                        this->fwork[22] = 0.0f;
                        this->fwork[23] = 0.0f;
                        gCsFrameCount = 0;
                        Radio_PlayMessage(gMsg_ID_3322, RCID_BOSS_METEO);
                        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 1);
                        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 1);
                    } else {
                        this->state = 5;
                        this->timer_050 = 70;
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

            if (this->timer_050 == 0) {
                if (this->fwork[10] < 0.02f) {
                    this->fwork[10] = this->fwork[10] + 0.0002f;
                }

                this->obj.rot.x += (-180.0f - this->obj.rot.x) * this->fwork[10];

                if (this->timer_052 != 0) {
                    if (this->swork[0] == 5) {
                        AUDIO_PLAY_SFX(NA_SE_EN_BURNER_L, this->sfxSource, 4);
                    }
                    if (this->swork[0] < 10) {
                        this->swork[0] += 2;
                        if (this->swork[0] > 10) {
                            this->swork[0] = 10;
                        }
                    }
                }

                if (this->obj.rot.x < -178.0f) {
                    this->state = 9;
                    this->timer_050 = 0;
                    this->fwork[15] = 8.0f;
                    AUDIO_PLAY_SFX(NA_SE_EN_RNG_BEAM_CHARGE, this->sfxSource, 4);
                }
            }
            break;

        case 9:
            this->obj.rot.x += (-180.0f - this->obj.rot.x) * this->fwork[10];
            if ((this->timer_050 > 50) && (this->timer_050 <= 64)) {
                this->fwork[22] -= 0.1f;
                if (this->fwork[22] < 0.0f) {
                    this->fwork[22] = 0.0f;
                }
                this->fwork[23] -= 0.1f;
                if (this->fwork[23] < 0.0f) {
                    this->fwork[23] = 0.0f;
                }
            }

            if (this->timer_050 < 20) {
                this->fwork[22] += 0.1f;
                if (this->fwork[22] > 1.0f) {
                    this->fwork[22] = 1.0f;
                }
                this->fwork[23] += 0.1f;
                if (this->fwork[23] > 1.0f) {
                    this->fwork[23] = 1.0f;
                }
            }

            if (this->timer_050 == 40) {
                this->swork[18] = 2;
            }

            if (this->timer_050 == 0) {
                this->fwork[15] -= 0.1f;
                if (this->fwork[15] < -1.0f) {
                    this->timer_050 = 40;
                    this->state = 10;
                }
            }
            break;

        case 10:
            if (this->timer_050 == 0) {
                this->state = 9;
                this->timer_050 = 70;
                this->fwork[15] = 8.0f;
                AUDIO_PLAY_SFX(NA_SE_EN_RNG_BEAM_CHARGE, this->sfxSource, 4);
            } else if ((this->timer_050 % 2U) == 1) {
                Meteo_80188088(this);
            }
            break;

        case 20:
            if (this->timer_052 == 230) {
                Radio_PlayMessage(gMsg_ID_3370, RCID_BOSS_METEO);
            }
            if (this->timer_052 == 90) {
                Radio_PlayMessage(gMsg_ID_3360, RCID_FOX);
            }

            if (((gGameFrameCount % 8) == 0) && (Rand_ZeroOne() < 0.5f)) {
                this->timer_05C = 4;
            }

            Matrix_MultVec3fNoTranslate(gCalcMatrix, &D_i2_80195430[RAND_INT(19.9f)], &dest);

            if (((gGameFrameCount % 2) == 0)) {
                Effect_Effect390_Spawn(this->obj.pos.x + dest.x, this->obj.pos.y + dest.y, this->obj.pos.z + dest.z,
                                       this->vel.x, this->vel.y, this->vel.z, 0.3f, 20);
            }
            if (((gGameFrameCount % 4) == 0)) {
                Effect386_Spawn1(this->obj.pos.x + dest.x, this->obj.pos.y + dest.y, this->obj.pos.z + dest.z,
                                 this->vel.x, this->vel.y, this->vel.z, 10.0f, 10);
            }

            this->vel.y = -5.0f;
            this->obj.rot.x += 0.2f;
            this->obj.rot.z -= 0.1f;

            if (this->timer_050 == 0) {
                func_effect_8007D2C8(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 40.0f);
                Object_Kill(&this->obj, this->sfxSource);
            }
            if (this->timer_050 == 20) {
                Effect_Effect383_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 80.0f);
                AUDIO_PLAY_SFX(NA_SE_EN_STAR_EXPLOSION, this->sfxSource, 4);
                gControllerRumbleTimers[0] = 60;
                for (i = 0; i < ARRAY_COUNT(gActors); i++) {
                    if (gActors[i].obj.id == OBJ_ACTOR_TEAM_BOSS) {
                        Object_Kill(&gActors[i].obj, gActors[i].sfxSource);
                    }
                }
            }

            switch (this->timer_050) {
                case 20:
                    gShowBossHealth = false;

                case 1:
                case 5:
                case 10:
                case 15:
                    Effect_Effect384_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 71.0f, 5);

                case 0:
                    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
                        func_effect_80079618(RAND_FLOAT_CENTERED(1000.0f) + this->obj.pos.x,
                                             RAND_FLOAT_CENTERED(1000.0f) + this->obj.pos.y,
                                             RAND_FLOAT_CENTERED(1000.0f) + this->obj.pos.z, 3.0f);
                    }
                    break;
            }
    }

    if (this->obj.rot.z >= 360.0f) {
        this->obj.rot.z = this->obj.rot.z - 360.0f;
    }
    if (this->obj.rot.z < 0.0f) {
        this->obj.rot.z += 360.0f;
    }

    if (gBossFrameCount == 250) {
        Radio_PlayMessage(gMsg_ID_2225, RCID_SLIPPY);
    }
    if (gBossFrameCount == 406) {
        gShowBossHealth = true;
    }
    if (gBossFrameCount > 406) {
        gBossHealthBar = (this->swork[2] + this->swork[3] + this->swork[4] + this->swork[5] + this->swork[7] +
                          this->swork[8] + this->swork[6]) /
                         2.6274f; // approx 670 / 255
        if ((gBossFrameCount > 506) && (gBossFrameCount < 1000)) {
            Math_SmoothStepToF(&this->fwork[17], 3.3f, 1.0f, 0.1f, 0.0f);
            Math_SmoothStepToF(&this->fwork[18], 3.3f, 1.0f, 0.1f, 0.0f);
            Math_SmoothStepToF(&this->fwork[19], 3.3f, 1.0f, 0.1f, 0.0f);
            Math_SmoothStepToF(&this->fwork[20], 3.3f, 1.0f, 0.1f, 0.0f);
        }
    }
}

void Meteo_MeCrusherEngineGlow_Draw(s32 scale) {
    f32 xScale = scale * 0.83333f; // approx 5 / 6

    if ((gGameFrameCount % 2) != 0) {
        xScale *= 1.1f;
    }

    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);

    RCP_SetupDL_64();
    Matrix_Push(&gGfxMatrix);
    Matrix_Scale(gGfxMatrix, 10.0f * xScale, 10.0f * xScale, 10.0f * xScale, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 70);
    gSPDisplayList(gMasterDisp++, aBlueSphereDL);

    Matrix_Pop(&gGfxMatrix);
    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, 20.0f, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, 9.0f * xScale, 9.0f * xScale, 9.0f * xScale, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 60);
    gSPDisplayList(gMasterDisp++, aBlueSphereDL);

    Matrix_Pop(&gGfxMatrix);
    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, 35.0f, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, 7.5f * xScale, 7.5f * xScale, 7.5f * xScale, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 50);
    gSPDisplayList(gMasterDisp++, aBlueSphereDL);

    Matrix_Pop(&gGfxMatrix);
    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, 40.0f, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, 5.0f * xScale, 5.0f * xScale, 5.0f * xScale, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 40);
    gSPDisplayList(gMasterDisp++, aBlueSphereDL);
    Matrix_Pop(&gGfxMatrix);
    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
}

void Meteo_MeCrusher_Draw(MeCrusher* this) {
    s32 i;
    f32 var_fs0;
    f32 var_fs1;
    s32 pad;

    gSPDisplayList(gMasterDisp++, aMeCrusherDL);

    RCP_SetupDL_64();
    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);

    for (i = 0; i < 6; i++) {
        FrameInterpolation_RecordOpenChild("MeCrusher_1", i);
        if ((this->fwork[i + 3] != 0) && (this->fwork[11] == 0.0f)) {
            var_fs1 = 2.0f * this->fwork[3 + i];
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
                gSPDisplayList(gMasterDisp++, aBlueSphereDL);
            } else {
                gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 128);
                Matrix_Scale(gGfxMatrix, var_fs1 * 6.0f, var_fs1 * 6.0f, var_fs1 * 6.0f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, aBlueSphereDL);
            }
            Matrix_Pop(&gGfxMatrix);
        }
        FrameInterpolation_RecordCloseChild();
    }

    for (i = 0; i < 7; i++) {
        FrameInterpolation_RecordOpenChild("MeCrusher_2", i);
        if (this->swork[2 + i] != 0) {
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, this->swork[19], 255);

            if ((this->swork[9 + i] % 2) != 0) {
                gDPSetPrimColor(gMasterDisp++, 0, 0, 80, 0, 0, 255);
            }

            Matrix_Push(&gGfxMatrix);

            if (i == 4) {
                Matrix_Translate(gGfxMatrix, 0.0f, 0, 300.0f, MTXF_APPLY);
                Matrix_RotateZ(gGfxMatrix, M_PI / 4, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, this->fwork[21], this->fwork[21], 1.0f, MTXF_APPLY);
            }

            if (i == 5) {
                Matrix_Translate(gGfxMatrix, 0.0f, 330.0f, -1022.0f, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, this->fwork[22] * 3.2f, 2.0f * this->fwork[22], 1.0f, MTXF_APPLY);
            }

            if (i == 6) {
                Matrix_Translate(gGfxMatrix, 0.0f, -330.0f, -1022.0f, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, this->fwork[23] * 3.2f, 2.0f * this->fwork[23], 1.0f, MTXF_APPLY);
            }

            if (i < 4) {
                Matrix_RotateZ(gGfxMatrix, M_DTOR * 90.0f * i, MTXF_APPLY);
                Matrix_Translate(gGfxMatrix, 0.0f, 200.0f, 500.0f, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, this->fwork[17 + i], this->fwork[17 + i], 1.0f, MTXF_APPLY);
            }

            Matrix_SetGfxMtx(&gMasterDisp);

            if (i < 4) {
                gSPDisplayList(gMasterDisp++, D_ME_6024AD0);
            } else {
                gSPDisplayList(gMasterDisp++, D_ME_60236F0);
            }
            Matrix_Pop(&gGfxMatrix);
        }
        FrameInterpolation_RecordCloseChild();
    }

    gDPSetPrimColor(gMasterDisp++, 0, 0, 160, 255, 160, 128);

    for (i = 0; i < 4; i++) {
        FrameInterpolation_RecordOpenChild("MeCrusher_3", i);
        if (this->fwork[11] != 0) {
            var_fs1 = this->fwork[11];
            if (this->fwork[11] > 15.0f) {
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
            gSPDisplayList(gMasterDisp++, aBlueSphereDL);
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
        FrameInterpolation_RecordCloseChild();
    }

    if (this->fwork[11] > 15.0f) {
        FrameInterpolation_RecordOpenChild("MeCrusher_3", 100);
        var_fs1 = this->fwork[11] - 15.0f;
        gDPSetPrimColor(gMasterDisp++, 0, 0, 160, 255, 160, 255);
        Matrix_Push(&gGfxMatrix);
        Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, 1300.0f, MTXF_APPLY);
        if ((gGameFrameCount % 2) != 0) {
            Matrix_Scale(gGfxMatrix, var_fs1 * 0.8f, var_fs1 * 0.8f, var_fs1 * 0.8f, MTXF_APPLY);
        } else {
            Matrix_Scale(gGfxMatrix, var_fs1, var_fs1, var_fs1, MTXF_APPLY);
        }
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, aBlueSphereDL);
        Matrix_Pop(&gGfxMatrix);
        FrameInterpolation_RecordCloseChild();
    }

    if ((this->state == 9) || (this->state == 10)) {
        var_fs1 = this->fwork[15];
        for (i = 0; i < 10; i++) {
            FrameInterpolation_RecordOpenChild("MeCrusher_4", i);
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
            FrameInterpolation_RecordCloseChild();
        }
    }

    if (this->swork[0] > 0) {
        Matrix_Push(&gGfxMatrix);
        Matrix_Translate(gGfxMatrix, 0.0f, 650.0f, 600.0f, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        Meteo_MeCrusherEngineGlow_Draw(this->swork[0] - 1);
        Matrix_Pop(&gGfxMatrix);
    }

    if (this->swork[1] > 0) {
        Matrix_Push(&gGfxMatrix);
        Matrix_Translate(gGfxMatrix, 0.0f, -650.0f, 600.0f, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        Meteo_MeCrusherEngineGlow_Draw(this->swork[1] - 1);
        Matrix_Pop(&gGfxMatrix);
    }

    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
}

void Meteo_LevelStart_SetupTeam(ActorCutscene* this, s32 teamIdx) {
    Actor_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_ACTOR_CUTSCENE;

    this->obj.pos.x = sMeLevelStartTeamSetupXpos[teamIdx] + gPlayer[0].pos.x;
    this->obj.pos.y = sMeLevelStartTeamSetupYpos[teamIdx] + gPlayer[0].pos.y;
    this->obj.pos.z = sMeLevelStartTeamSetupZpos[teamIdx] + gPlayer[0].trueZpos;

    this->animFrame = sMeLevelStartTeamSetupModel[teamIdx];
    this->obj.rot.y = 180.0f;
    Object_SetInfo(&this->info, this->obj.id);
    this->info.cullDistance = 200.0f;

    if (this->animFrame == ACTOR_CS_TEAM_ARWING) {
        this->iwork[11] = 1;
        AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, this->sfxSource, 4);

        if (CVarGetInteger("gTeamFaces", 1) == 1) {
            // @port: Setup team faces
            this->iwork[14] = teamIdx + 2;
        }
        return;
    }

    AUDIO_PLAY_SFX(NA_SE_GREATFOX_ENGINE, this->sfxSource, 0);
    AUDIO_PLAY_SFX(NA_SE_GREATFOX_BURNER, this->sfxSource, 0);
}

void Meteo_8018C8F4(MeMeteor2* this, ActorCutscene* actorCs) {
    Actor_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_ACTOR_ME_METEOR_2;

    this->obj.pos.x = RAND_FLOAT_CENTERED_SEEDED(2000.0f) + actorCs->obj.pos.x;
    this->obj.pos.y = RAND_FLOAT_CENTERED_SEEDED(2000.0f) + actorCs->obj.pos.y;
    this->obj.pos.z = RAND_FLOAT_CENTERED_SEEDED(500.0f) + actorCs->obj.pos.z - 9000.0f;

    this->obj.rot.y = RAND_FLOAT_SEEDED(360.0f);
    this->obj.rot.x = RAND_FLOAT_SEEDED(360.0f);

    this->timer_0C2 = 10000;
    this->vel.z = 30.0f;
    Object_SetInfo(&this->info, this->obj.id);
}

void Meteo_8018CA10(MeMeteor2* this, ActorCutscene* actorCs, f32 x, f32 y, f32 z) {
    Actor_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_ACTOR_ME_METEOR_2;

    this->obj.pos.x = actorCs->obj.pos.x + x;
    this->obj.pos.y = actorCs->obj.pos.y + y;
    this->obj.pos.z = actorCs->obj.pos.x + z;

    this->obj.rot.y = RAND_FLOAT_SEEDED(360.0f);
    this->obj.rot.x = RAND_FLOAT_SEEDED(360.0f);

    this->timer_0C2 = 10000;
    this->vel.z = 30.0f;
    Object_SetInfo(&this->info, this->obj.id);
}

void Meteo_8018CAD8(void) {
    ActorCutscene* actorCs = &gActors[50];

    Actor_Initialize(actorCs);
    actorCs->obj.status = OBJ_INIT;
    actorCs->obj.id = OBJ_ACTOR_CUTSCENE;

    actorCs->obj.pos.x = 0.0f;
    actorCs->obj.pos.y = 0.0f;
    actorCs->obj.pos.z = 9000.0f;

    actorCs->animFrame = ACTOR_CS_ME_CORNERIA_BG;
    Object_SetInfo(&actorCs->info, actorCs->obj.id);
}

void Meteo_Effect346_Setup(Effect346* this, Actor* actor) {
    Effect_Initialize(this);
    this->obj.status = OBJ_ACTIVE;
    this->obj.id = OBJ_EFFECT_346;

    this->timer_50 = RAND_INT(20.0f) + 20.0f;
    this->scale2 = RAND_FLOAT(0.5f) + 0.5f;

    this->obj.pos.x = actor->obj.pos.x;
    this->obj.pos.y = actor->obj.pos.y;
    this->obj.pos.z = actor->obj.pos.z;

    this->vel.x = RAND_FLOAT_CENTERED(30.0f);
    this->vel.y = RAND_FLOAT_CENTERED(30.0f);
    this->vel.z = RAND_FLOAT_CENTERED(30.0f);

    this->obj.rot.z = RAND_FLOAT(360.0f);
    Object_SetInfo(&this->info, this->obj.id);
}

void Meteo_Effect346_Spawn(ActorEvent* this) {
    s32 i;
    s32 j;

    Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_EXPLOSION_S);

    for (i = 0; i < 25; i++) {
        for (j = 0; j < ARRAY_COUNT(gEffects); j++) {
            if (gEffects[j].obj.status == OBJ_FREE) {
                Meteo_Effect346_Setup(&gEffects[j], this);
                break;
            }
        }
    }
}

void Meteo_SpawnMeteorsGroup1(MeMeteor2* this, ActorCutscene* actorCs, s32 index) {
    Actor_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_ACTOR_ME_METEOR_2;

    this->obj.pos.x = sMeteorGroup1[index - 5].pos.x;
    this->obj.pos.y = sMeteorGroup1[index - 5].pos.y;
    this->obj.pos.z = sMeteorGroup1[index - 5].pos.z;

    this->obj.rot.y = sMeteorGroup1[index - 5].rot.y;
    this->obj.rot.x = sMeteorGroup1[index - 5].rot.x;

#if 0
    printf("{ // Meteor Number: %x \n", index);
    printf(" // Pos: \n");
    printf("    { %f, ", this->obj.pos.x);
    printf(" %f, ", this->obj.pos.y);
    printf(" %f }, \n", this->obj.pos.z);
    printf(" // Rot: \n");
    printf("    {");
    printf(" %f, ", this->obj.rot.x);
    printf(" %f, ", this->obj.rot.y);
    printf(" 0.0f ");
    printf("},\n");
    printf("}, \n");
#endif

    this->timer_0C2 = 10000;
    this->vel.z = 30.0f;
    Object_SetInfo(&this->info, this->obj.id);
}

void Meteo_SpawnMeteorsGroup2(MeMeteor2* this, ActorCutscene* actorCs, s32 index) {
    Actor_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_ACTOR_ME_METEOR_2;

    this->obj.pos.x = sMeteorGroup2[index - 4].pos.x;
    this->obj.pos.y = sMeteorGroup2[index - 4].pos.y;
    this->obj.pos.z = sMeteorGroup2[index - 4].pos.z;

    this->obj.rot.y = sMeteorGroup2[index - 4].rot.y;
    this->obj.rot.x = sMeteorGroup2[index - 4].rot.x;

#if 0
    printf("{ // Meteor Number: %x \n", index);
    printf(" // Pos: \n");
    printf("    { %f, ", this->obj.pos.x);
    printf(" %f, ", this->obj.pos.y);
    printf(" %f }, \n", this->obj.pos.z);
    printf(" // Rot: \n");
    printf("    {");
    printf(" %f, ", this->obj.rot.x);
    printf(" %f, ", this->obj.rot.y);
    printf(" 0.0f ");
    printf("},\n");
    printf("}, \n");
#endif

    this->timer_0C2 = 10000;
    this->vel.z = 30.0f;
    Object_SetInfo(&this->info, this->obj.id);
}

void Meteo_LevelStart(Player* player) {
    u8 sp8F;
    s32 i;
    Actor* falco = &gActors[0];
    Actor* slippy = &gActors[1];
    Actor* peppy = &gActors[2];
    Actor* greatFox = &gActors[3];
    f32 x;
    f32 y;
    f32 z;
    f32 sp68;
    f32 sp64;
    Vec3f sp58;
    Vec3f sp4C;

    gFillScreenAlphaStep = 4;

    PRINTF("Demo_Time %d\n", gCsFrameCount);

    switch (player->csState) {
        case 0:
            gCsFrameCount = 0;

            if (gTeamShields[TEAM_ID_FALCO] > 0) {
                Meteo_LevelStart_SetupTeam(falco, 0);
            }
            if (gTeamShields[TEAM_ID_SLIPPY] > 0) {
                Meteo_LevelStart_SetupTeam(slippy, 1);
            }
            if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                Meteo_LevelStart_SetupTeam(peppy, 2);
            }

            Meteo_LevelStart_SetupTeam(greatFox, 3);
            Meteo_8018CAD8();

            for (i = 5; i < 15; i++) {
                Meteo_SpawnMeteorsGroup1(&gActors[i], greatFox, i);
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
            greatFox->vel.z = 4.0f;
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
                greatFox->state = 10;
            }
            if (gCsFrameCount == 720) {
                falco->state = 11;
            }
            if (gCsFrameCount == 750) {
                peppy->state = 12;
            }
            if (gCsFrameCount == 780) {
                slippy->state = 13;
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
                Meteo_8018CA10(&gActors[16], greatFox, 100.0f, 500.0f, 1500.0f);
                Meteo_8018CA10(&gActors[17], greatFox, 300.0f, 400.0f, 2000.0f);
            }
            if (gCsFrameCount == 660) {
                for (i = 4; i < 15; i++) {
                    gActors[i].obj.status = OBJ_FREE;
                }

                greatFox->obj.pos.x += 1000.0f;
                greatFox->obj.pos.z += 4000.0f;

                for (i = 4; i < 9; i++) {
                    Meteo_SpawnMeteorsGroup2(&gActors[i], greatFox, i);
                }

                greatFox->obj.pos.x -= 1000.0f;
                greatFox->obj.pos.z -= 4000.0f;

                Meteo_8018CA10(&gActors[13], greatFox, 1500.0f, 200.0f, 100.0f);
                Meteo_8018CA10(&gActors[14], greatFox, 1200.0f, -200.0f, -500.0f);
                Meteo_8018CA10(&gActors[15], greatFox, 2000.0f, -100.0f, -1000.0f);

                gActors[50].obj.status = gActors[16].obj.status = gActors[17].obj.status = OBJ_FREE;
            }

            if (gCsFrameCount > 660) {
                player->arwing.drawFace = false;
            }

            if (gCsFrameCount == 340) {
                func_effect_8007D2C8(gActors[8].obj.pos.x, gActors[8].obj.pos.y, gActors[8].obj.pos.z, 10.0f);
                gActors[8].obj.status = OBJ_FREE;
                Meteo_Effect346_Spawn(&gActors[8]);
            }

            if (player->csEventTimer != 0) {
                if (sp8F != 0) {
                    sp58 = D_i2_801955C4;
                    D_ctx_80177A48[3] *= -1.0f;
                    x = gActors[player->meTargetIndex].obj.pos.x - (greatFox->obj.pos.x + (D_ctx_80177A48[3] * 74.0f));
                    y = gActors[player->meTargetIndex].obj.pos.y - (greatFox->obj.pos.y - 232.0f);
                    z = gActors[player->meTargetIndex].obj.pos.z - (greatFox->obj.pos.z - 1190.0f);

                    sp64 = Math_RadToDeg(Math_Atan2F(x, z));
                    x = sqrtf(SQ(x) + SQ(z));
                    sp68 = Math_RadToDeg(-Math_Atan2F(y, x));

                    Matrix_RotateY(gCalcMatrix, M_DTOR * sp64, MTXF_NEW);
                    Matrix_RotateX(gCalcMatrix, M_DTOR * sp68, MTXF_APPLY);
                    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp58, &sp4C);

                    Actor_SpawnGreatFoxLaser(100, greatFox->obj.pos.x + (D_ctx_80177A48[3] * 74.0f) + (sp4C.x * 0.6f),
                                             greatFox->obj.pos.y - 232.0f + (sp4C.y * 0.8f),
                                             greatFox->obj.pos.z - 1190.0f + (sp4C.z * 0.8f), sp4C.x, sp4C.y, sp4C.z,
                                             sp68, sp64, 0.0f);
                }
                if (player->csEventTimer == 1) {
                    func_effect_8007D2C8(gActors[player->meTargetIndex].obj.pos.x,
                                         gActors[player->meTargetIndex].obj.pos.y,
                                         gActors[player->meTargetIndex].obj.pos.z, 10.0f);
                    gActors[player->meTargetIndex].obj.status = OBJ_FREE;
                    Meteo_Effect346_Spawn(&gActors[player->meTargetIndex]);
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
                player->state = PLAYERSTATE_ACTIVE;
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

void Meteo_MeteorShower_Update(Actor* this) {
    switch (this->state) {
        case 0:
            this->fwork[0] = RAND_FLOAT_CENTERED(10.0f);
            this->state = 1;

        case 1:
            this->obj.rot.z += this->fwork[0];
            break;
    }
    Meteo_ReflectDamage(this);
}

void Meteo_MeMeteorShower1_Draw(MeMeteorShower1* this) {
    RCP_SetupDL_60(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
    gSPDisplayList(gMasterDisp++, aMeMeteorShower1DL);
}

void Meteo_MeMeteorShower2_Draw(MeMeteorShower2* this) {
    RCP_SetupDL_60(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
    gSPDisplayList(gMasterDisp++, aMeMeteorShower2DL);
}

void Meteo_MeMeteorShower3_Draw(MeMeteorShower3* this) {
    RCP_SetupDL_60(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
    gSPDisplayList(gMasterDisp++, aMeMeteorShower3DL);
}

void Meteo_Effect370_Draw(Effect370* this) {
    if (this->state == 1) {
        Matrix_RotateX(gGfxMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);
        Matrix_Scale(gGfxMatrix, this->scale2, this->scale2, this->scale2, MTXF_APPLY);
        Matrix_RotateZ(gGfxMatrix, M_PI / 2, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, this->unk_44);
        gSPDisplayList(gMasterDisp++, D_ME_60263F0);
    }
}

void Meteo_Effect369_Draw(Effect369* this) {
    if (this->state != 0) {
        Matrix_RotateX(gGfxMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);
        Matrix_Scale(gGfxMatrix, this->scale2, this->scale2, this->scale2 * 3.0f, MTXF_APPLY);

        if ((gGameFrameCount % 2) != 0) {
            Matrix_RotateZ(gGfxMatrix, M_PI, MTXF_APPLY);
        }

        Matrix_RotateX(gGfxMatrix, -M_PI / 2, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 160, 255, 160, this->unk_44);
        gSPDisplayList(gMasterDisp++, D_102F5E0);
    }
}

void Meteo_Effect371_Draw(Effect371* this) {
    Matrix_RotateX(gGfxMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, this->scale2, this->scale2, this->scale2, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, this->unk_44);

    switch (this->unk_4C) {
        case 0:
            gSPDisplayList(gMasterDisp++, D_ME_6023810);
        case 1:
            break;
    }
}

void Meteo_LevelComplete_SetupTeam(ActorCutscene* this, s32 teamIdx) {
    Actor_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_ACTOR_CUTSCENE;

    this->obj.pos.x = sMeLevelCompleteTeamSetupPos[teamIdx].x + gPlayer[0].pos.x;
    this->obj.pos.y = sMeLevelCompleteTeamSetupPos[teamIdx].y + gPlayer[0].pos.y;
    this->obj.pos.z = sMeLevelCompleteTeamSetupPos[teamIdx].z + gPlayer[0].trueZpos;

    this->rot_0F4.y = 0.0f;
    this->rot_0F4.z = sMeLevelCompleteTeamSetupModel[teamIdx];

    Object_SetInfo(&this->info, this->obj.id);

    if (teamIdx == 3) {
        AUDIO_PLAY_SFX(NA_SE_GREATFOX_ENGINE, this->sfxSource, 0);
        AUDIO_PLAY_SFX(NA_SE_GREATFOX_BURNER, this->sfxSource, 0);
        this->animFrame = ACTOR_CS_GREAT_FOX;
    } else {
        this->iwork[11] = 1;
        AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, this->sfxSource, 4);

        if (CVarGetInteger("gTeamFaces", 1) == 1) {
            // @port: Setup team faces
            this->iwork[14] = teamIdx + 2;
        }
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

    UpdateVisPerFrameFromRecording(gMeCrusherCutsceneRecord, ARRAY_COUNT(gMeCrusherCutsceneRecord));

    switch (player->csState) {
        case 0:
            Audio_StopSfxByBankAndSource(1, player->sfxSource);
            player->csState++;

            D_ctx_80177A48[0] = 0.0f;
            D_ctx_80177A48[1] = 0.0f;
            D_ctx_80177A48[2] = 0.0f;

            player->arwing.drawFace = true;

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
                        player->state = PLAYERSTATE_NEXT;
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
                Meteo_LevelComplete_SetupTeam(&gActors[0], 0);
            }
            if (gTeamShields[TEAM_ID_SLIPPY] > 0) {
                Meteo_LevelComplete_SetupTeam(&gActors[1], 1);
            }
            if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                Meteo_LevelComplete_SetupTeam(&gActors[2], 2);
            }
            Meteo_LevelComplete_SetupTeam(&gActors[3], 3);
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
            gShowLevelClearStatusScreen = true;
            break;

        case 1176:
            gShowLevelClearStatusScreen = false;
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

void Meteo_8018ED9C(ActorCutscene* this) {
    Vec3f src;
    Vec3f dest;

    switch (this->state) {
        case 0:
            this->vwork[0].x = gPlayer[0].pos.x + D_i2_80195610[this->index].x;
            this->vwork[0].y = gPlayer[0].pos.y + D_i2_80195610[this->index].y;
            this->vwork[0].z = gPlayer[0].pos.z + D_i2_80195610[this->index].z;

            Math_SmoothStepToF(&this->obj.pos.x, this->vwork[0].x, 0.02f, 50.0f, 0.0001f);
            Math_SmoothStepToF(&this->obj.pos.y, this->vwork[0].y, 0.02f, 50.0f, 0.0001f);
            Math_SmoothStepToF(&this->obj.pos.z, this->vwork[0].z, 0.02f, 50.0f, 0.0001f);
            Math_SmoothStepToF(&this->rot_0F4.z, 0.0f, 0.03f, 0.5f, 0.0001f);
            break;

        case 1:
            this->state = 2;
            AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, this->sfxSource, 0);
            this->timer_0BC = 150;
            this->fwork[29] = 5.0f;

        case 2:
            this->iwork[11] = 2;
            this->fwork[0] += 2.0f;
            this->rot_0F4.x += 0.1f;
            if (this->timer_0BC == 0) {
                Object_Kill(&this->obj, this->sfxSource);
            }
            break;
    }

    Matrix_RotateY(gCalcMatrix, (this->rot_0F4.y + 180.0f) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -(this->rot_0F4.x * M_DTOR), MTXF_APPLY);

    src.x = 0.0f;
    src.y = 0.0f;
    src.z = this->fwork[0];

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

    this->vel.x = dest.x;
    this->vel.y = dest.y;
    this->vel.z = dest.z;

    this->obj.rot.x = -this->rot_0F4.x;
    this->obj.rot.y = +this->rot_0F4.y + 180.0f;
    this->obj.rot.z = -this->rot_0F4.z;
}
