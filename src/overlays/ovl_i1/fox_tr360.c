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
    gLevelObjects = SEGMENTED_TO_VIRTUAL(D_TR_6008EF8);

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

bool Training_EnemyObstacleCheck(ActorAllRange* this, f32 sinRotY, f32 cosRotY) {
    Scenery360* scenery360;
    s32 i;

    for (i = 0, scenery360 = gScenery360; i < 200;) {
        if ((scenery360->obj.status == OBJ_ACTIVE) &&
            (fabsf(scenery360->obj.pos.x - (this->obj.pos.x + ((sinRotY * 650.0f) + 350.0f))) < 1200.0f) &&
            (fabsf(scenery360->obj.pos.z - (this->obj.pos.z + ((cosRotY * 650.0f) + 350.0f))) < 1200.0f) &&
            (this->obj.pos.y < 650.0f)) {
            return true;
        }
        scenery360++;
        if ((scenery360->obj.status == OBJ_ACTIVE) &&
            (fabsf(scenery360->obj.pos.x - (this->obj.pos.x + ((sinRotY * 650.0f) + 350.0f))) < 1200.0f) &&
            (fabsf(scenery360->obj.pos.z - (this->obj.pos.z + ((cosRotY * 650.0f) + 350.0f))) < 1200.0f) &&
            (this->obj.pos.y < 650.0f)) {
            return true;
        }
        scenery360++;
        if ((scenery360->obj.status == OBJ_ACTIVE) &&
            (fabsf(scenery360->obj.pos.x - (this->obj.pos.x + ((sinRotY * 650.0f) + 350.0f))) < 1200.0f) &&
            (fabsf(scenery360->obj.pos.z - (this->obj.pos.z + ((cosRotY * 650.0f) + 350.0f))) < 1200.0f) &&
            (this->obj.pos.y < 650.0f)) {
            return true;
        }
        scenery360++;
        if ((scenery360->obj.status == OBJ_ACTIVE) &&
            (fabsf(scenery360->obj.pos.x - (this->obj.pos.x + ((sinRotY * 650.0f) + 350.0f))) < 1200.0f) &&
            (fabsf(scenery360->obj.pos.z - (this->obj.pos.z + ((cosRotY * 650.0f) + 350.0f))) < 1200.0f) &&
            (this->obj.pos.y < 650.0f)) {
            return true;
        }
        scenery360++;
        i += 4;
    }
    return false;
}

void Training_Enemy_Update(ActorAllRange* this) {
    s32 pad[8];
    f32 xPos;
    f32 yPos;
    f32 zPos;
    f32 targetAngle2;
    RadarMark* radarMark;
    f32 pad2;
    f32 angle;
    f32 targetAngle;
    bool enemyNearObstacle;
    f32 sinRotX;
    f32 sinRotY;
    f32 cosRotX;
    f32 cosRotY;

    if (this->timer_0BC == 0) {
        yPos = RAND_FLOAT(1000.0f);
        xPos = RAND_FLOAT_CENTERED(10000.0f);
        zPos = RAND_FLOAT_CENTERED(10000.0f);
        this->fwork[4] = xPos;
        this->fwork[5] = yPos;
        this->fwork[6] = zPos;
        this->timer_0BC = RAND_INT(20.0f) + 10;
    }

    sinRotX = SIN_DEG(this->obj.rot.x);
    cosRotX = COS_DEG(this->obj.rot.x);
    sinRotY = SIN_DEG(this->obj.rot.y);
    cosRotY = COS_DEG(this->obj.rot.y);

    xPos = this->fwork[4] - this->obj.pos.x;
    yPos = this->fwork[5] - this->obj.pos.y;
    zPos = this->fwork[6] - this->obj.pos.z;

    if (((this->index + gGameFrameCount) % 8) == 0) {
        this->fwork[19] = Math_RadToDeg(Math_Atan2F(xPos, zPos));
        this->fwork[20] = Math_RadToDeg(Math_Atan2F(yPos, sqrtf(SQ(xPos) + SQ(zPos))));
    }

    targetAngle2 = this->fwork[20];

    enemyNearObstacle = Training_EnemyObstacleCheck(this, sinRotY, cosRotY);
    if (enemyNearObstacle) {
        targetAngle2 += 40.0f * (f32) enemyNearObstacle;
        if (targetAngle2 >= 360.0f) {
            targetAngle2 -= 360.0f;
        }
        if (targetAngle2 < 0.0f) {
            targetAngle2 += 360.0f;
        }
    } else if ((this->obj.pos.y < (gGroundHeight + 50.0f)) && (targetAngle2 > 180.0f)) {
        targetAngle2 = 0.0f;
        this->rot_0F4.x = 0.0f;
    }

    Math_SmoothStepToAngle(&this->rot_0F4.x, targetAngle2, 0.5f, 1.0f, 0.0001f);
    angle = Math_SmoothStepToAngle(&this->rot_0F4.y, this->fwork[19], 0.5f, 1.0f, 0.0001f) * 30.0f;

    if (angle < 0.0f) {
        targetAngle = angle * -1.0f;
    } else {
        targetAngle = 360.0f - angle;
    }

    Math_SmoothStepToAngle(&this->obj.rot.z, targetAngle, 0.1f, 3.0f, 0.01f);

    this->obj.rot.x = -this->rot_0F4.x;
    this->obj.rot.y = this->rot_0F4.y;

    this->vel.x = this->fwork[13] + (sinRotY * (cosRotX * 35.0f));
    this->vel.y = this->fwork[14] + (-sinRotX * 35.0f);
    this->vel.z = this->fwork[12] + (cosRotY * (cosRotX * 35.0f));

    this->fwork[13] -= (this->fwork[13] * 0.1f);
    this->fwork[14] -= (this->fwork[14] * 0.1f);
    this->fwork[12] -= (this->fwork[12] * 0.1f);

    if ((this->obj.pos.y < gGroundHeight + 40.0f) && (this->vel.y < 0.0f)) {
        this->obj.pos.y = gGroundHeight + 40.0f;
        this->vel.y = 0.0f;
    }

    ActorAllRange_ApplyDamage(this);

    radarMark = &gRadarMarks[this->index];
    radarMark->enabled = true;
    radarMark->type = this->aiType;
    radarMark->pos.x = this->obj.pos.x;
    radarMark->pos.y = this->obj.pos.y;
    radarMark->pos.z = this->obj.pos.z;
    radarMark->yRot = this->rot_0F4.y + 180.0f;

    if (this->iwork[8] != 0) {
        this->iwork[8]--;
    }
}

typedef struct TrainingMessage {
    /* 0x00 */ u16* msg;
    /* 0x04 */ u16 msgTimer;
} TrainingMessage;

TrainingMessage sTrainingMessages[] = {
    { gMsg_ID_23028, 224 }, { gMsg_ID_23029, 160 }, { gMsg_ID_23030, 224 }, { gMsg_ID_23031, 256 },
    { gMsg_ID_23016, 160 }, { gMsg_ID_23024, 160 }, { gMsg_ID_23019, 256 }, { gMsg_ID_23015, 160 },
    { gMsg_ID_23017, 160 }, { gMsg_ID_23025, 160 }, { gMsg_ID_23002, 160 }, { gMsg_ID_23004, 160 },
    { gMsg_ID_23005, 160 }, { gMsg_ID_23023, 160 }, { gMsg_ID_23006, 160 }, { gMsg_ID_23007, 256 },
    { gMsg_ID_20330, 0 },   { gMsg_ID_23026, 256 }, { gMsg_ID_23032, 256 }, { NULL, -1 },
};

void Training_SpawnEnemies(void) {
    s32 i;
    ActorAllRange* enemy;
    Vec3f src;
    Vec3f dest;
    s32 aiTypeIndex;

    aiTypeIndex = 1;
    if (gHitCount >= 100) {
        aiTypeIndex = 0;
    }

    if (((gGameFrameCount % 4) == 0) && (gPlayer[0].state == PLAYERSTATE_ACTIVE)) {
        src.x = 0.0f;
        src.y = 0.0f;
        src.z = -15000.0f;

        for (i = aiTypeIndex, enemy = &gActors[i + 10]; i < 16; i++, enemy++) {
            if (enemy->obj.status == OBJ_FREE) {
                Actor_Initialize(enemy);

                enemy->obj.status = OBJ_ACTIVE;
                enemy->obj.id = OBJ_ACTOR_ALLRANGE;

                Matrix_RotateY(gCalcMatrix, (gGameFrameCount * 6.0f) * M_DTOR, MTXF_NEW);
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

                enemy->obj.pos.x = dest.x;
                enemy->obj.pos.y = 2000.0f;
                enemy->obj.pos.z = dest.z;

                enemy->rot_0F4.y = gGameFrameCount * 6.0f;
                enemy->aiType = i + AI360_ENEMY;
                enemy->health = 24;
                enemy->drawShadow = enemy->iwork[11] = 1;
                enemy->timer_0C2 = 30;

                Object_SetInfo(&enemy->info, enemy->obj.id);

                AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, enemy->sfxSource, 4);

                if ((i + 10) == 10) {
                    enemy->aiIndex = AI360_FOX;
                    enemy->health = 50;
                } else {
                    enemy->aiIndex = -1;
                    enemy->info.action = (ObjectFunc) Training_Enemy_Update;
                }
                break;
            }
        }
    }

    if (gTraining360MsgTimer != 0) {
        gTraining360MsgTimer--;
    }

    if (gTraining360MsgTimer == 0) {
        if (sTrainingMessages[gTraining360MsgIndex].msg == NULL) {
            gTraining360MsgIndex = 1;
        }
        if (sTrainingMessages[gTraining360MsgIndex].msgTimer != 0) {
            Radio_PlayMessage(sTrainingMessages[gTraining360MsgIndex].msg, RCID_TR);
            gTraining360MsgTimer = sTrainingMessages[gTraining360MsgIndex].msgTimer;
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
