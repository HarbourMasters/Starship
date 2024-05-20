/*
 * File: fox_tr360.c
 * System: Training
 * Description: Level: Training - All Range mode
 */

#include "global.h"
#include "assets/ast_training.h"

void Training_Setup360(void) {
    Scenery360* scenery360;
    s32 i;

    gLevelObjects = LOAD_ASSET(D_TR_6008EF8);
    Rand_SetSeed(1, 29000, 9876);

    scenery360 = gScenery360;

    for (i = 0; i < 1000; i++) {
        if (gLevelObjects[i].id <= OBJ_INVALID) {
            break;
        }
        if (gLevelObjects[i].id < OBJ_SCENERY_MAX) {
            Scenery360_Initialize(scenery360);
            scenery360->obj.status = OBJ_ACTIVE;
            scenery360->obj.id = gLevelObjects[i].id;
            scenery360->obj.pos.x = gLevelObjects[i].xPos;
            scenery360->obj.pos.z = -gLevelObjects[i].zPos1;
            scenery360->obj.pos.y = gLevelObjects[i].yPos - RAND_FLOAT_SEEDED(300.0f);
            scenery360->obj.rot.y = gLevelObjects[i].rot.y;
            Object_SetInfo(&scenery360->info, scenery360->obj.id);
            scenery360++;
        }
    }
}

bool Training_80198DCC(Actor* actor, f32 x, f32 z) {
    Scenery360* scenery360;
    s32 i;

    for (i = 0, scenery360 = gScenery360; i < 200;) {
        if ((scenery360->obj.status == OBJ_ACTIVE) &&
            (fabsf(scenery360->obj.pos.x - (actor->obj.pos.x + ((x * 650.0f) + 350.0f))) < 1200.0f) &&
            (fabsf(scenery360->obj.pos.z - (actor->obj.pos.z + ((z * 650.0f) + 350.0f))) < 1200.0f) &&
            (actor->obj.pos.y < 650.0f)) {
            return true;
        }
        scenery360++;
        if ((scenery360->obj.status == OBJ_ACTIVE) &&
            (fabsf(scenery360->obj.pos.x - (actor->obj.pos.x + ((x * 650.0f) + 350.0f))) < 1200.0f) &&
            (fabsf(scenery360->obj.pos.z - (actor->obj.pos.z + ((z * 650.0f) + 350.0f))) < 1200.0f) &&
            (actor->obj.pos.y < 650.0f)) {
            return true;
        }
        scenery360++;
        if ((scenery360->obj.status == OBJ_ACTIVE) &&
            (fabsf(scenery360->obj.pos.x - (actor->obj.pos.x + ((x * 650.0f) + 350.0f))) < 1200.0f) &&
            (fabsf(scenery360->obj.pos.z - (actor->obj.pos.z + ((z * 650.0f) + 350.0f))) < 1200.0f) &&
            (actor->obj.pos.y < 650.0f)) {
            return true;
        }
        scenery360++;
        if ((scenery360->obj.status == OBJ_ACTIVE) &&
            (fabsf(scenery360->obj.pos.x - (actor->obj.pos.x + ((x * 650.0f) + 350.0f))) < 1200.0f) &&
            (fabsf(scenery360->obj.pos.z - (actor->obj.pos.z + ((z * 650.0f) + 350.0f))) < 1200.0f) &&
            (actor->obj.pos.y < 650.0f)) {
            return true;
        }
        scenery360++;
        i += 4;
    }

    return false;
}

void Training_80199024(Actor* actor) {
    s32 pad[8];
    Vec3f sp54;
    f32 var_fv0;
    RadarMark* radarMark;
    f32 temp_fv0;
    f32 temp_fv1;
    f32 var_fv0_2;
    s32 temp_v0;
    f32 sinRotX;
    f32 sinRotY;
    f32 cosRotX;
    f32 cosRotY;

    if (actor->timer_0BC == 0) {
        sp54.y = RAND_FLOAT(1000.0f);
        sp54.z = RAND_FLOAT_CENTERED(10000.0f);
        sp54.x = RAND_FLOAT_CENTERED(10000.0f);
        actor->fwork[4] = sp54.z;
        actor->fwork[5] = sp54.y;
        actor->fwork[6] = sp54.x;
        actor->timer_0BC = RAND_INT(20.0f) + 10;
    }

    sinRotX = SIN_DEG(actor->obj.rot.x);
    cosRotX = COS_DEG(actor->obj.rot.x);
    sinRotY = SIN_DEG(actor->obj.rot.y);
    cosRotY = COS_DEG(actor->obj.rot.y);

    sp54.z = actor->fwork[4] - actor->obj.pos.x;
    sp54.y = actor->fwork[5] - actor->obj.pos.y;
    sp54.x = actor->fwork[6] - actor->obj.pos.z;

    if (((actor->index + gGameFrameCount) % 8) == 0) {
        actor->fwork[19] = Math_RadToDeg(Math_Atan2F(sp54.z, sp54.x));
        actor->fwork[20] = Math_RadToDeg(Math_Atan2F(sp54.y, sqrtf(SQ(sp54.z) + SQ(sp54.x))));
    }

    var_fv0 = actor->fwork[20];

    temp_v0 = Training_80198DCC(actor, sinRotY, cosRotY);
    if (temp_v0 != 0) {
        var_fv0 += 40.0f * (f32) temp_v0;
        if (var_fv0 >= 360.0f) {
            var_fv0 -= 360.0f;
        }
        if (var_fv0 < 0.0f) {
            var_fv0 += 360.0f;
        }
    } else if ((actor->obj.pos.y < (gGroundHeight + 50.0f)) && (var_fv0 > 180.0f)) {
        var_fv0 = 0.0f;
        actor->rot_0F4.x = 0.0f;
    }

    Math_SmoothStepToAngle(&actor->rot_0F4.x, var_fv0, 0.5f, 1.0f, 0.0001f);
    temp_fv1 = Math_SmoothStepToAngle(&actor->rot_0F4.y, actor->fwork[19], 0.5f, 1.0f, 0.0001f) * 30.0f;

    if (temp_fv1 < 0.0f) {
        var_fv0_2 = temp_fv1 * -1.0f;
    } else {
        var_fv0_2 = 360.0f - temp_fv1;
    }

    Math_SmoothStepToAngle(&actor->obj.rot.z, var_fv0_2, 0.1f, 3.0f, 0.01f);

    actor->obj.rot.x = -actor->rot_0F4.x;
    actor->obj.rot.y = actor->rot_0F4.y;

    actor->vel.x = actor->fwork[13] + (sinRotY * (cosRotX * 35.0f));
    actor->vel.y = actor->fwork[14] + (-sinRotX * 35.0f);
    actor->vel.z = actor->fwork[12] + (cosRotY * (cosRotX * 35.0f));

    actor->fwork[13] -= (actor->fwork[13] * 0.1f);
    actor->fwork[14] -= (actor->fwork[14] * 0.1f);
    actor->fwork[12] -= (actor->fwork[12] * 0.1f);

    if ((actor->obj.pos.y < gGroundHeight + 40.0f) && (actor->vel.y < 0.0f)) {
        actor->obj.pos.y = gGroundHeight + 40.0f;
        actor->vel.y = 0.0f;
    }

    ActorAllRange_ApplyDamage(actor);

    radarMark = &gRadarMarks[actor->index];
    radarMark->status = 1;
    radarMark->type = actor->aiType;
    radarMark->pos.x = actor->obj.pos.x;
    radarMark->pos.y = actor->obj.pos.y;
    radarMark->pos.z = actor->obj.pos.z;
    radarMark->yRot = actor->rot_0F4.y + 180.0f;

    if (actor->iwork[8] != 0) {
        actor->iwork[8]--;
    }
}

typedef struct {
    u16* msg;
    u16 unk;
} UnkMsg_D_i1_8019AE50;

UnkMsg_D_i1_8019AE50 D_i1_8019AE50[] = {
    { gMsg_ID_23028, 224 }, { gMsg_ID_23029, 160 }, { gMsg_ID_23030, 224 }, { gMsg_ID_23031, 256 },
    { gMsg_ID_23016, 160 }, { gMsg_ID_23024, 160 }, { gMsg_ID_23019, 256 }, { gMsg_ID_23015, 160 },
    { gMsg_ID_23017, 160 }, { gMsg_ID_23025, 160 }, { gMsg_ID_23002, 160 }, { gMsg_ID_23004, 160 },
    { gMsg_ID_23005, 160 }, { gMsg_ID_23023, 160 }, { gMsg_ID_23006, 160 }, { gMsg_ID_23007, 256 },
    { gMsg_ID_20330, 0 },   { gMsg_ID_23026, 256 }, { gMsg_ID_23032, 256 }, { NULL, -1 },
};

void Training_8019949C(void) {
    s32 i;
    Actor* actor;
    Vec3f sp44;
    Vec3f sp38;
    s32 var_v1 = 1;

    if (gHitCount >= 100) {
        var_v1 = 0;
    }

    if (((gGameFrameCount % 4) == 0) && (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_ACTIVE)) {
        sp44.x = 0.0f;
        sp44.y = 0.0f;
        sp44.z = -15000.0f;

        for (i = var_v1, actor = &gActors[i + 10]; i < 16; i++, actor++) {
            if (actor->obj.status == OBJ_FREE) {
                Actor_Initialize(actor);

                actor->obj.status = OBJ_ACTIVE;
                actor->obj.id = OBJ_ACTOR_ALLRANGE;

                Matrix_RotateY(gCalcMatrix, gGameFrameCount * 6.0f * M_DTOR, MTXF_NEW);

                Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp44, &sp38);

                actor->obj.pos.x = sp38.x;
                actor->obj.pos.y = 2000.0f;
                actor->obj.pos.z = sp38.z;

                actor->rot_0F4.y = gGameFrameCount * 6.0f;
                actor->aiType = i + AI360_10;
                actor->health = 24;
                actor->drawShadow = actor->iwork[11] = 1;
                actor->timer_0C2 = 30;

                Object_SetInfo(&actor->info, actor->obj.id);

                AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, actor->sfxSource, 4);

                if ((i + 10) == 10) {
                    actor->aiIndex = AI360_FOX;
                    actor->health = 50;
                } else {
                    actor->aiIndex = -1;
                    actor->info.action = (ObjectFunc) Training_80199024;
                }
                break;
            }
        }
    }

    if (gTraining360MsgTimer != 0) {
        gTraining360MsgTimer--;
    }

    if (gTraining360MsgTimer == 0) {
        if (D_i1_8019AE50[gTraining360MsgIndex].msg == 0) {
            gTraining360MsgIndex = 1;
        }
        if (D_i1_8019AE50[gTraining360MsgIndex].unk != 0) {
            Radio_PlayMessage(D_i1_8019AE50[gTraining360MsgIndex].msg, RCID_TR);
            gTraining360MsgTimer = D_i1_8019AE50[gTraining360MsgIndex].unk;
        } else {
            gCallTimer = 80;
            gTraining360MsgTimer = 320;
        }
        gTraining360MsgIndex++;
    }

    if ((gCallTimer != 0) && (gControllerPress[gMainController].button & R_CBUTTONS)) {
        Audio_SetUnkVoiceParam(0);
        gCallVoiceParam = 0;
        gCallTimer = 0;
        Radio_PlayMessage(gMsg_ID_20329, RCID_ROB64);
    }
}
