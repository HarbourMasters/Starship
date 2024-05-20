/*
 * File: fox_sx.c
 * System: Sector Z
 * Description: Level: Sector Z
 */

#include "global.h"
#include "assets/ast_sector_z.h"

s32 D_i4_801A0560;
s32 D_i4_801A0564;

Vec3f D_i4_8019F4C0[] = {
    { 0.0f, 0.0f, 35000.0f },
    { -2000.0f, 0.0f, 35000.0f },
    { 2000.0f, 0.0f, 35000.0f },
};
Vec3f D_i4_8019F4E4[] = {
    { -700.0f, -200.0f, 200.0f },
    { 500.0f, 200.0f, -300.0f },
    { 300.0f, -300.0f, -200.0f },
    { 200.0f, 400.0f, 500.0f },
};

void SectorZ_80199900(Actor* actor, s32 arg1) {
    s32 i;

    PRINTF("MISS_MOVE_TIME %d\n");
    PRINTF("Enm->time0 %d\n");
    PRINTF("time0 %d\n");
    PRINTF("Demo_Time=%d\n");

    gScreenFlashTimer = 8;

    Object_Kill(&actor->obj, actor->sfxSource);
    func_effect_8007A6F0(&actor->obj.pos, NA_SE_EN_MS_EXPLOSION_S);

    for (i = 0; i < 20; i++) {
        func_effect_800794CC(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, 1.0f);
        func_effect_80079618(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, 1.0f);
    }

    func_effect_8007BFFC(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, 0.0f, 0.0f, 0.0f, 20.0f, 30);
    func_effect_8007B344(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, 20.0f, 5);

    if (arg1 != 0) {
        D_i4_801A0560++;
        if ((D_i4_801A0560 >= 6) &&
            ((gPlayer[0].state_1C8 == PLAYERSTATE_1C8_ACTIVE) || (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_U_TURN))) {
            gCsFrameCount = 0;
            gPlayer[0].state_1C8 = PLAYERSTATE_1C8_LEVEL_COMPLETE;
            gPlayer[0].csState = 1000;
            gActors[0].state = 6;
            gPlayer[0].csTimer = 30;
            AUDIO_PLAY_SFX(NA_SE_GREATFOX_ENGINE, gActors[0].sfxSource, 0);
            AUDIO_PLAY_SFX(NA_SE_GREATFOX_BURNER, gActors[0].sfxSource, 0);
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 1);
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 1);
        }

        if ((D_i4_801A0560 == 3) && (gLeveLClearStatus[LEVEL_ZONESS] != 0)) {
            gAllRangeSpawnEvent = gAllRangeEventTimer + 110;
        }
    }
}

void SectorZ_80199B18(Effect* effect, f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 scale) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = OBJ_EFFECT_FIRE_SMOKE;

    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;

    effect->vel.x = xVel;
    effect->vel.y = yVel;
    effect->vel.z = zVel;

    effect->scale2 = scale;
    effect->scale1 = 0.5f;

    effect->unk_4C = 2;
    effect->obj.rot.z = RAND_FLOAT(360.0f);

    Object_SetInfo(&effect->info, effect->obj.id);

    effect->unk_44 = 255;
    effect->unk_46 = 2;
}

void SectorZ_80199BDC(f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 scale) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == 0) {
            SectorZ_80199B18(&gEffects[i], xPos, yPos, zPos, xVel, yVel, zVel, scale);
            break;
        }
    }
}
typedef enum {
    MISSILE_TARGET_X = 4,
    MISSILE_TARGET_Y = 5,
    MISSILE_TARGET_Z = 6,
} MissileWork;

// https://decomp.me/scratch/7td7r
#ifdef NON_MATCHING
void SectorZ_Missile_Update(Actor* this) {
    f32 xDist;
    f32 yDist;
    f32 zDist;
    f32 x;
    f32 y;
    s32 pad;

    switch (++this->iwork[9]) {
        case 600:
            Radio_PlayMessage(gMsg_ID_16080, RCID_ROB64);
            break;

        case 1000:
            Radio_PlayMessage(gMsg_ID_16085, RCID_ROB64);
            break;

        case 1200:
            Radio_PlayMessage(gMsg_ID_16090, RCID_ROB64);
            break;
    }

    /* Distance between the Great Fox and the missile */
    xDist = gBosses[0].obj.pos.x - this->obj.pos.x;
    zDist = gBosses[0].obj.pos.z - this->obj.pos.z;

    SIN_DEG(gGameFrameCount); // WTF

    if (xDist) {}
    if (zDist) {}

    if (this->aiType < AI360_GREAT_FOX) {
        xDist = SIN_DEG((this->index * 45) + gGameFrameCount) * 5000.0f;
        zDist = COS_DEG((this->index * 45) + (gGameFrameCount * 2)) * 5000.0f;
    } else {
        zDist = 0.0f;
        xDist = 0.0f;
    }

    this->fwork[MISSILE_TARGET_X] = (gBosses[0].obj.pos.x + xDist) + 400.0f;
    this->fwork[MISSILE_TARGET_Y] = (gBosses[0].obj.pos.y + zDist) + 100.0f;
    this->fwork[MISSILE_TARGET_Z] = gBosses[0].obj.pos.z;
    this->fwork[3] = 1.4f;

    if (((fabsf(this->fwork[MISSILE_TARGET_X] - this->obj.pos.x) < 800.0f) &&
         (fabsf(this->fwork[MISSILE_TARGET_Y] - this->obj.pos.y) < 800.0f)) &&
        (fabsf(this->fwork[MISSILE_TARGET_Z] - this->obj.pos.z) < 800.0f)) {
        SectorZ_80199900(this, 0);
        gCameraShake = 25;
        gBosses[0].dmgType = DMG_UNK_100;
        if ((gPlayer[0].state_1C8 == PLAYERSTATE_1C8_ACTIVE) || (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_U_TURN)) {
            gPlayer[0].state_1C8 = PLAYERSTATE_1C8_LEVEL_COMPLETE;
            gPlayer[0].csState = 0;
            gActors[0].state = -31072;
            return;
        }
    }

    if (((fabsf(this->fwork[MISSILE_TARGET_Z] - this->obj.pos.z) < 2000.0f) &&
         (((gPlayer[0].cam.eye.z < 0.0f) || (D_edisplay_801615D0.y < 0.0f)) ||
          (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_GFOX_REPAIR))) &&
        (((gPlayer[0].state_1C8 == PLAYERSTATE_1C8_ACTIVE) || (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_GFOX_REPAIR)) ||
         (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_U_TURN))) {
        gPlayer[0].state_1C8 = PLAYERSTATE_1C8_LEVEL_COMPLETE;
        gPlayer[0].csState = 100;
        gActors[0].state = -31072;
    }
}
#else
#pragma GLOBAL_ASM("asm/us/rev1/nonmatchings/overlays/ovl_i4/fox_sz/SectorZ_Missile_Update.s")
#endif

void SectorZ_80199FCC(Actor* actor, s32 arg1) {
    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_ALLRANGE;
    actor->aiType = AI360_MISSILE;

    actor->obj.pos.x = D_i4_8019F4C0[arg1].x;
    actor->obj.pos.y = D_i4_8019F4C0[arg1].y;
    actor->obj.pos.z = D_i4_8019F4C0[arg1].z;

    actor->state = 5;
    actor->rot_0F4.y = 180.0f;

    Object_SetInfo(&actor->info, actor->obj.id);

    actor->health = 250;
    actor->info.drawType = 2;
    actor->info.hitbox = LOAD_ASSET(D_SZ_6009230);
    actor->fwork[1] = 25.0f;
    actor->fwork[29] = 2.0f;

    AUDIO_PLAY_SFX(NA_SE_EN_PUNCH_ENGINE, actor->sfxSource, 4);
}

void SectorZ_8019A0F8(Actor* actor, s32 arg1) {
    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_ALLRANGE;
    actor->aiType = arg1 + AI360_10 + 3;

    actor->obj.pos.x = gActors[10].obj.pos.x + D_i4_8019F4E4[arg1].x;
    actor->obj.pos.y = gActors[10].obj.pos.y + D_i4_8019F4E4[arg1].y;
    actor->obj.pos.z = gActors[10].obj.pos.z + D_i4_8019F4E4[arg1].z;

    actor->state = 5;
    actor->rot_0F4.y = 180.0f;

    Object_SetInfo(&actor->info, actor->obj.id);

    actor->fwork[1] = gActors[10].fwork[1];
    actor->iwork[11] = 1;
}

void SectorZ_8019A1D0(void) {
    Actor* actor = &gActors[8];

    Actor_Initialize(actor);
    actor->obj.status = OBJ_ACTIVE;
    actor->obj.id = OBJ_ACTOR_ALLRANGE;

    actor->obj.pos.x = 0.0f;
    actor->obj.pos.y = 4500.0f;
    actor->obj.pos.z = 30000.0f;

    actor->aiType = AI360_KATT;
    actor->aiIndex = AI360_10 + 2;
    actor->health = 10000;
    actor->rot_0F4.y = 180.0f;
    actor->state = 0;
    actor->timer_0BC = 250;
    actor->rot_0F4.x = -20.0f;
    actor->iwork[11] = 1;
    actor->obj.rot.z = 90.0f;

    Object_SetInfo(&actor->info, actor->obj.id);

    actor->info.targetOffset = 0.0f;

    AUDIO_PLAY_SFX(NA_SE_EN_ENGINE_01, actor->sfxSource, 4);
}

void SectorZ_8019A2F4(Actor* actor) {
    if (gAllRangeEventTimer == gAllRangeSpawnEvent) {
        SectorZ_8019A1D0();
        gCsFrameCount = 0;
        actor->timer_0BC = 400;
        actor->state = 3;
        gPlayer[0].state_1C8 = PLAYERSTATE_1C8_STANDBY;

        Audio_PlayFanfare(NA_BGM_KATT, 20, 10, 10);
        AllRange_ClearRadio();

        gPlayer[0].cam.eye.x = 250.0f;
        gPlayer[0].cam.eye.y = 2500.0f;
        gPlayer[0].cam.eye.z = 25000.0f;

        gPlayer[0].cam.at.x = gActors[8].obj.pos.x;
        gPlayer[0].cam.at.y = gActors[8].obj.pos.y;
        gPlayer[0].cam.at.z = gActors[8].obj.pos.z;
        D_i4_801A0564 = 1;
    }
}

void SectorZ_8019A3E8(Actor* actor) {
    s32 i;
    Vec3f sp40;
    Vec3f sp34;
    Actor* actorPtr;

    if (gAllRangeEventTimer >= 0) {
        if (gTeamShields[AI360_FALCO] > 0) {
            if (gActors[AI360_FALCO].iwork[2] == AI360_FOX) {
                if (gActors[AI360_10].obj.status == 2) {
                    if (gActors[1].aiIndex != AI360_10) {
                        Radio_PlayMessage(gMsg_ID_16040, RCID_FALCO);
                    }
                    gActors[AI360_FALCO].aiIndex = AI360_10;
                } else {
                    gActors[AI360_FALCO].aiIndex = AI360_10 + 3;
                }
            } else {
                gActors[AI360_FALCO].aiIndex = -1;
            }
        }

        if (gTeamShields[AI360_PEPPY] > 0) {
            if (gActors[AI360_PEPPY].iwork[2] == AI360_FOX) {
                if (gActors[AI360_10 + 2].obj.status == 2) {
                    if (gActors[AI360_PEPPY].aiIndex != AI360_10 + 2) {
                        Radio_PlayMessage(gMsg_ID_16046, RCID_PEPPY);
                    }
                    gActors[AI360_PEPPY].aiIndex = AI360_10 + 2;
                } else {
                    gActors[AI360_PEPPY].aiIndex = AI360_10 + 5;
                }
            } else {
                gActors[AI360_PEPPY].aiIndex = -1;
            }
        }

        if (D_i4_801A0564 != 0) {
            if (gActors[11].obj.status == 2) {
                if (gActors[8].aiIndex != AI360_10 + 1) {
                    Radio_PlayMessage(gMsg_ID_16135, RCID_KATT);
                }
                gActors[AI360_KATT].aiIndex = AI360_10 + 1;
            } else {
                gActors[AI360_KATT].aiIndex = -1;
            }
        } else if (gTeamShields[AI360_SLIPPY] > 0) {
            if (gActors[AI360_SLIPPY].iwork[2] == AI360_FOX) {
                if (gActors[11].obj.status == 2) {
                    if (gActors[AI360_SLIPPY].aiIndex != AI360_10 + 1) {
                        Radio_PlayMessage(gMsg_ID_16047, RCID_SLIPPY);
                    }
                    gActors[AI360_SLIPPY].aiIndex = AI360_10 + 1;
                } else {
                    gActors[AI360_SLIPPY].aiIndex = AI360_10 + 4;
                }
            } else {
                gActors[AI360_SLIPPY].aiIndex = -1;
            }
        }
    }

    if (gAllRangeEventTimer == 100) {
        Radio_PlayMessage(gMsg_ID_16030, RCID_FALCO);
    }

    if (((actor->timer_0C0 == 0) && (gPlayer[0].state_1C8 != PLAYERSTATE_1C8_STANDBY)) &&
        ((gAllRangeEventTimer < 200) || ((gAllRangeEventTimer > 4000) && (gAllRangeEventTimer < 4200)))) {
        actor->timer_0C0 = 5;
        actorPtr = &gActors[13];
        sp40.x = 0.0f;
        sp40.y = 0.0f;
        sp40.z = -17000.0f;

        for (i = 0; i < 20; i++, actorPtr++) {
            if (actorPtr->obj.status == 0) {
                Actor_Initialize(actorPtr);
                actorPtr->obj.status = OBJ_ACTIVE;
                actorPtr->obj.id = OBJ_ACTOR_ALLRANGE;
                Matrix_RotateY(gCalcMatrix, (actor->counter_04E * 18.0f) * M_DTOR, MTXF_NEW);
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp40, &sp34);

                actorPtr->obj.pos.x = sp34.x;
                actorPtr->obj.pos.y = RAND_FLOAT(1000.0f) + 300.0f;
                actorPtr->obj.pos.z = sp34.z;

                actorPtr->rot_0F4.y = actor->counter_04E * 18.0f;
                actorPtr->state = 3;
                actorPtr->aiType = i + AI360_10 + 3;
                actorPtr->aiIndex = -1;

                if (gAllRangeEventTimer >= 0) {
                    if (((i + 13) == 23) || ((i + 13) == 24)) {
                        actorPtr->aiIndex = AI360_SLIPPY;
                        actorPtr->state = 2;
                    }
                    if ((i + 13) == 25) {
                        actorPtr->aiIndex = AI360_FOX;
                        actorPtr->state = 2;
                    }
                    if (((i + 13) == 26) || ((i + 13) == 27)) {
                        actorPtr->aiIndex = AI360_PEPPY;
                        actorPtr->state = 2;
                    }
                    if ((i + 13) == 28) {
                        actorPtr->aiIndex = AI360_FALCO;
                        actorPtr->state = 2;
                    }
                }
                actorPtr->health = 24;
                actorPtr->iwork[11] = 1;
                actorPtr->itemDrop = DROP_SILVER_RING_50p;
                actorPtr->timer_0C2 = 30;
                Object_SetInfo(&actorPtr->info, actorPtr->obj.id);
                AUDIO_PLAY_SFX(NA_SE_EN_ENGINE_01, actorPtr->sfxSource, 4);
                actor->counter_04E++;
                break;
            }
        }
    }

    switch (gAllRangeEventTimer) {
        case 5850:
            Radio_PlayMessage(gMsg_ID_16110, RCID_ROB64);
            break;

        case 6000:
            SectorZ_80199FCC(&gActors[12], 2);
            SectorZ_80199FCC(&gActors[11], 1);
            SectorZ_80199FCC(&gActors[10], 0);
            D_hud_80161710 = 580;
            break;

        case 3850:
            Radio_PlayMessage(gMsg_ID_16100, RCID_ROB64);
            break;

        case 4000:
            SectorZ_80199FCC(&gActors[11], 1);
            SectorZ_80199FCC(&gActors[10], 0);
            D_hud_80161710 = 580;
            break;

        case 2000:
            D_hud_80161710 = 490;
            SectorZ_80199FCC(&gActors[10], 0);

            gActors[10].fwork[1] = 10.0f;
            gActors[10].obj.pos.z = 25000.0f;

            SectorZ_8019A0F8(&gActors[13], 0);
            SectorZ_8019A0F8(&gActors[14], 1);
            SectorZ_8019A0F8(&gActors[15], 2);
            SectorZ_8019A0F8(&gActors[16], 3);

            gPlayer[0].state_1C8 = PLAYERSTATE_1C8_STANDBY;
            actor->state = 10;
            actor->fwork[10] = 0.0f;
            gPlayer[0].camRoll = 15.0f;

            gPlayer[0].cam.eye.x = gActors[10].obj.pos.x - 25000.0f;
            gPlayer[0].cam.eye.y = gActors[10].obj.pos.y;
            gPlayer[0].cam.eye.z = gActors[10].obj.pos.z;

            gPlayer[0].cam.at.x = gActors[10].obj.pos.x;
            gPlayer[0].cam.at.y = gActors[10].obj.pos.y;
            gPlayer[0].cam.at.z = gActors[10].obj.pos.z;

            actor->timer_0BC = 10000;
            gFillScreenAlpha = gFillScreenAlphaTarget = 255;
            gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
            AUDIO_PLAY_BGM(NA_BGM_BOSS_SZ);
            break;
    }

    ActorAllRange_UpdateEvemyEvents(actor);
    SectorZ_8019A2F4(actor);
}

bool SectorZ_8019AA9C(Player* player) {
    if (player->state_1C8 == PLAYERSTATE_1C8_ACTIVE) {
        if ((player->yRot_114 > 30.0f) && (player->yRot_114 < 150.0f) && (fabsf(player->pos.x - 1270.0f) < 450.0f) &&
            (fabsf(player->pos.y - 265.0f) < 100.0f) && (fabsf(player->trueZpos) < 172.0f)) {
            player->state_1C8 = PLAYERSTATE_1C8_GFOX_REPAIR;
            player->csState = 0;
            gActors[0].state = 20;
            gAllRangeEventTimer--;
            return true;
        }
    }
    return false;
}

void SectorZ_UpdateEvents(Actor* actor) {
    s32 i;
    Player* player;
    Actor* actor8;
    s32 pad;
    f32 D_i4_8019F514[5] = { -200.0f, -100.0f, -0.0f, 100.0f, 200.0f };

    player = &gPlayer[0];

    switch ((s32) actor->state) {
        case 0:
            D_i4_801A0564 = D_i4_801A0560 = 0;
            gSzMissileR = 63.0f;
            gSzMissileG = 255.0f;
            gSzMissileB = 158.0f;
            gProjectFar = 30000.0f;
            gAllRangeEventTimer = 0;
            actor->state = 2;
            if (gAllRangeCheckpoint != 0) {
                gHitCount = gSavedHitCount;
            }
            gAllRangeSpawnEvent = 1000000;

        case 2:
            if (SectorZ_8019AA9C(player) == 0) {
                SectorZ_8019A3E8(actor);
                switch (actor->timer_0BE) {
                    case 548:
                        Radio_PlayMessage(gMsg_ID_16050, RCID_ROB64);
                        break;

                    case 385:
                        Radio_PlayMessage(gMsg_ID_16055, RCID_ROB64);
                        break;

                    case 235:
                        Radio_PlayMessage(gMsg_ID_16060, RCID_FOX);
                        break;

                    case 130:
                        break;
                }
            }
            break;

        case 20:
            gAllRangeEventTimer--;
            break;

        case 3:
            actor8 = &gActors[8];
            gCsFrameCount++;
            if (gCsFrameCount == 3) {
                func_effect_80078E50(actor8->obj.pos.x, actor8->obj.pos.y, actor8->obj.pos.z, 30.0f);
            }
            player->cam.eye.x += actor8->vel.x * 0.23f;
            player->cam.eye.y += actor8->vel.y * 0.23f;
            player->cam.eye.z += actor8->vel.z * 0.23f;

            Math_SmoothStepToF(&player->cam.at.x, actor8->obj.pos.x, 1.0f, 20000.0f, 0);
            Math_SmoothStepToF(&player->cam.at.y, actor8->obj.pos.y, 1.0f, 20000.0f, 0);
            Math_SmoothStepToF(&player->cam.at.z, actor8->obj.pos.z, 1.0f, 20000.0f, 0);
            Math_SmoothStepToF(&player->camRoll, 0, 1.0f, 1000.0f, 0);

            switch (actor->timer_0BC) {
                case 370:
                    Radio_PlayMessage(gMsg_ID_16120, RCID_KATT);
                    break;

                case 261:
                    Radio_PlayMessage(gMsg_ID_16125, RCID_FALCO);
                    break;

                case 140:
                    gRadioState = 0;
                    Radio_PlayMessage(gMsg_ID_16130, RCID_KATT);
                    break;

                case 260:
                    actor8->fwork[7] = 360.0f;
                    actor8->fwork[8] = 0.0f;
                    break;

                case 230:
                    actor8->fwork[7] = 0.0f;
                    actor8->fwork[8] = 359.999f;
                    break;
            }

            if (actor->timer_0BC == 70) {
                actor->state = 2;
                player->state_1C8 = PLAYERSTATE_1C8_ACTIVE;
                Camera_Update360(player, 1);
                player->unk_014 = 0.0f;
            }
            break;

        case 6:
            gActors[1].aiIndex = AI360_FOX;
            gActors[1].state = 2;
            gActors[2].aiIndex = AI360_FOX;
            gActors[2].state = 2;
            gActors[3].aiIndex = AI360_FOX;
            gActors[3].state = 2;

            for (i = 10; i < ARRAY_COUNT(gActors); i++) {
                gActors[i].aiIndex = -1;
                gActors[i].state = 3;
            }
            break;

        case 10:
            gFillScreenAlpha = gFillScreenAlphaTarget = 0;
            switch (actor->timer_0BC) {
                case 9800:
                    AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, gActors[10].sfxSource, 0);
                    gActors[10].fwork[29] = 12.0f;
                    break;

                case 9780:
                    gActors[13].aiIndex = -1;
                    gActors[13].state = 3;
                    break;

                case 9740:
                    gActors[14].aiIndex = -1;
                    gActors[14].state = 3;
                    break;

                case 9730:
                    gActors[15].aiIndex = -1;
                    gActors[15].state = 3;
                    break;

                case 9710:
                    gActors[16].aiIndex = -1;
                    gActors[16].state = 3;
                    break;
            }

            Math_SmoothStepToF(&player->cam.at.x, gActors[10].obj.pos.x, 0.2, 500.0f, 0.0f);
            Math_SmoothStepToF(&player->cam.at.y, gActors[10].obj.pos.y, 0.2, 500.0f, 0.0f);
            Math_SmoothStepToF(&player->cam.at.z, gActors[10].obj.pos.z, 0.2, 500.0f, 0.0f);

            if (actor->timer_0BC < 9800) {
                Math_SmoothStepToF(&gActors[10].fwork[1], 80.0f, 0.1, 10.0f, 0);
                Math_SmoothStepToF(&gActors[10].fwork[29], 3.0f, 0.1, 1.0f, 0);
            } else {
                Math_SmoothStepToF(&actor->fwork[10], 700.0f, 1, 5.0f, 0.0f);
                Math_SmoothStepToF(&player->cam.eye.x, gActors[10].obj.pos.x - 300.0f, 0.07f, actor->fwork[10], 0);
                Math_SmoothStepToF(&player->cam.eye.y, gActors[10].obj.pos.y, 0.07f, actor->fwork[10], 0);
                Math_SmoothStepToF(&player->cam.eye.z, gActors[10].obj.pos.z + 500.0f, 0.05f, 50.0f, 0);
                Math_SmoothStepToF(&gActors[10].fwork[29], 2.0f, 0.1f, 1.0f, 0);
            }

            if (actor->timer_0BC < 9680) {
                actor->state = 2;
                player->state_1C8 = PLAYERSTATE_1C8_ACTIVE;
                Camera_Update360(player, 1);
                player->unk_014 = 0.0f;
                gActors[10].fwork[1] = 25.0f;
                gActors[10].fwork[29] = 5.0f;
                gActors[10].obj.pos.z = 35000.0f;
                gActors[10].iwork[9] = 0;
                gPlayer[0].camRoll = 0.0f;
                actor->timer_0BE = 550;
            }
            break;

        case 100000:
            break;
    }

    if ((gGameFrameCount & 0x18) == 0) {
        Math_SmoothStepToF(&gSzMissileR, 63.0f, 1.0f, 9.450001f, 0);
        Math_SmoothStepToF(&gSzMissileG, 255.0f, 1.0f, 35.25f, 0);
        Math_SmoothStepToF(&gSzMissileB, 158.0f, 1.0f, 21.6f, 0);
    } else {
        Math_SmoothStepToF(&gSzMissileR, 0.0f, 1.0f, 3.15f, 0);
        Math_SmoothStepToF(&gSzMissileG, 20.0f, 1.0f, 11.75f, 0);
        Math_SmoothStepToF(&gSzMissileB, 14.0f, 1.0f, 7.2000003f, 0);
    }
}

Vec3f D_i4_8019F528[] = {
    { 1000.0f, 1000.0f, 1000.0f },  { 0.0f, -700.0f, 1500.0f },       { 2000.0f, -500.0f, 2500.0f },
    { -500.0f, 500.0f, -3000.0f },  { -2000.0f, -1000.0f, -1000.0f }, { -1000.0f, 1700.0f, -1500.0f },
    { 2000.0f, 2500.0f, -2500.0f },
};

void SectorZ_8019B48C(void) {
    Actor* actor = &gActors[1];
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_i4_8019F528); i++, actor++) {
        Actor_Initialize(actor);
        actor->obj.status = OBJ_INIT;
        actor->obj.id = OBJ_ACTOR_CUTSCENE;
        actor->animFrame = 25;
        actor->obj.pos.x = D_i4_8019F528[i].x;
        actor->obj.pos.y = D_i4_8019F528[i].y;
        actor->obj.pos.z = D_i4_8019F528[i].z;
        actor->obj.rot.y = RAND_FLOAT(360.0f);
        actor->vel.x = 5.0f;
        Object_SetInfo(&actor->info, actor->obj.id);
    }
}

void SectorZ_8019B568(void) {
    Actor* actor = &gActors[0];

    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_CUTSCENE;

    actor->obj.pos.x = 5000.0f;
    actor->obj.pos.y = 0.0f;
    actor->obj.pos.z = 0.0f;

    actor->obj.rot.y = 270.0f;
    actor->animFrame = 1;
    actor->vel.x = -20.0f;
    Object_SetInfo(&actor->info, actor->obj.id);
    AUDIO_PLAY_SFX(NA_SE_GREATFOX_ENGINE, actor->sfxSource, 0);
}
Vec3f D_i4_8019F57C[] = {
    { 150.0f, 150.0f, 50.0f }, { -150.0f, -150.0f, 50.0f }, { -150.0f, 150.0f, 50.0f }, { 150.0f, -150.0f, 50.0f }
};

f32 D_i4_8019F5AC[] = { -30.0f, 20.0f, 30.0f, -40.0f };

void SectorZ_8019B630(Actor* actor, s32 index) {
    Actor_Initialize(actor);
    actor->obj.status = OBJ_ACTIVE;
    actor->obj.id = OBJ_ACTOR_CUTSCENE;

    actor->obj.pos.x = gPlayer[0].cam.eye.x + D_i4_8019F57C[index].x;
    actor->obj.pos.y = gPlayer[0].cam.eye.y + D_i4_8019F57C[index].y;
    actor->obj.pos.z = gPlayer[0].cam.eye.z + D_i4_8019F57C[index].z;

    actor->vel.z = -30.0f;
    actor->vel.y = -10.0f;

    actor->obj.rot.y = 180.0f;
    actor->obj.rot.x = 10.0f;
    actor->obj.rot.z = D_i4_8019F5AC[index];

    actor->animFrame = 26;
    actor->iwork[11] = 1;
    Object_SetInfo(&actor->info, actor->obj.id);
    AUDIO_PLAY_SFX(NA_SE_EN_ENGINE_01, actor->sfxSource, 4);
}

Vec3f D_i4_8019F5BC[] = {
    { 200.0f, 0.0f, 0.0f }, { 200.0f, 0.0f, 0.0f }, { 200.0f, 0.0f, 0.0f }, { 200.0f, 0.0f, 0.0f }
};

void SectorZ_8019B75C(Actor* actor, s32 arg1) {
    Actor* newActor = &gActors[0];

    Actor_Initialize(actor);
    actor->obj.status = OBJ_ACTIVE;
    actor->obj.id = OBJ_ACTOR_CUTSCENE;

    actor->obj.pos.x = D_i4_8019F5BC[arg1].x + newActor->obj.pos.x;
    actor->obj.pos.y = newActor->obj.pos.y - 500.0f;
    actor->obj.pos.z = D_i4_8019F5BC[arg1].z + newActor->obj.pos.z;

    actor->vel.x = -gArwingSpeed;
    actor->obj.rot.y = 270.0f;

    Object_SetInfo(&actor->info, actor->obj.id);

    AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, actor->sfxSource, 4);
    AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, actor->sfxSource, 0);
    actor->fwork[29] = 5.0f;
}

Vec3f D_i4_8019F5EC[] = {
    { 0.0f, 20000.0f, 0.0f }, { -1000.0f, 100.0f, 500.0f }, { -1300.0f, -50.0f, 0.0f }, { -1600.0f, 50.0f, -500.0f }
};

void SectorZ_8019B888(void) {
    s32 i;
    Actor* actor;

    for (i = 0, actor = &gActors[0]; i <= TEAM_ID_PEPPY; i++, actor++) {
        if ((i <= 0) || (gTeamShields[i] > 0)) {
            Actor_Initialize(actor);
            actor->obj.status = OBJ_ACTIVE;
            actor->obj.id = OBJ_ACTOR_ALLRANGE;
            Object_SetInfo(&actor->info, actor->obj.id);
            if (i == 0) {
                actor->aiType = AI360_EVENT_HANDLER;
            } else {
                actor->obj.pos.x = gPlayer[0].pos.x + D_i4_8019F5EC[i].x;
                actor->obj.pos.y = gPlayer[0].pos.y + D_i4_8019F5EC[i].y;
                actor->obj.pos.z = gPlayer[0].pos.z + D_i4_8019F5EC[i].z;
                actor->aiType = i;
                actor->state = 2;
                actor->rot_0F4.y = 270.0f;
                actor->health = 255;
                actor->iwork[11] = 1;
                AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, actor->sfxSource, 4);
                actor->info.hitbox = LOAD_ASSET(gTeamHitbox);
                actor->info.unk_16 = 0;
                actor->info.targetOffset = 0.0f;
            }
        }
    }
}

void SectorZ_LevelStart(Player* player) {
    s32 i;
    s32 j;
    Vec3f sp74;
    Vec3f sp68;
    Actor* actor = gActors;

    gAllRangeEventTimer = 0;

    switch (player->csState) {
        case 0:
            gCsFrameCount = 0;

            player->csState++;

            SectorZ_8019B568();
            SectorZ_8019B48C();

            gCsCamEyeX = 0.0f;
            gCsCamEyeY = 0.0f;
            gCsCamEyeZ = 6000.0f;
            gCsCamAtX = 2500.0f;
            gCsCamAtY = 0.0f;
            gCsCamAtZ = 0.0f;
            D_ctx_80177A48[0] = 1.0f;

            player->unk_234 = 0;
            player->baseSpeed = 0.0f;
            player->camRoll = -20.0f;

            gProjectFar = 30000.0f;

        case 1:
            if (gCsFrameCount < 7) {
                gFillScreenAlpha = 255;
            }

            gCsCamAtX -= 10.0f;
            gCsCamEyeZ -= 7.0f;

            if (gCsFrameCount == 320) {
                actor = &actor[0];
                player->csState = 2;
                actor->vel.x = -10.0f;
                actor->obj.pos.x = 1000.0f;
                gCsCamEyeX = 0.0f;
                gCsCamEyeY = 0.0f;
                gCsCamEyeZ = 17000.0f;
                gCsCamAtX = 0.0f;
                gCsCamAtY = 0.0f;
                gCsCamAtZ = 0.0f;
                gFillScreenAlpha = 255;
            }
            break;

        case 2:
            gFillScreenAlpha = 0;
            player->camRoll += 0.05f;

            for (i = 30; i < 34; i++) {
                Math_SmoothStepToF(&gActors[i].vel.x, -5.0f, 0.1f, 0.1, 0.0f);
                Math_SmoothStepToF(&gActors[i].vel.y, 5.0f, 0.1f, 0.1, 0.0f);
                Math_SmoothStepToF(&gActors[i].obj.rot.x, -10.0f, 0.1f, 0.2f, 0.0f);
                Math_SmoothStepToF(&gActors[i].obj.rot.z, 0.0f, 0.1f, 0.3f, 0.0f);
            }

            if (gCsFrameCount == 500) {
                gCsFrameCount = 520;

                player->csState++;

                actor->vel.x = 0.0f;

                actor->obj.pos.z = 0.0f;
                actor->obj.pos.y = 0.0f;
                actor->obj.pos.x = 0.0f;

                player->camRoll = 0.0f;

                player->cam.eye.x = gCsCamEyeX = actor->obj.pos.x - 2800.0f;
                player->cam.eye.y = gCsCamEyeY = actor->obj.pos.y + 1400.0f;
                player->cam.eye.z = gCsCamEyeZ = actor->obj.pos.z + 700.0f;

                player->cam.at.x = gCsCamAtX = actor->obj.pos.x - 1000.0f;
                player->cam.at.y = gCsCamAtY = actor->obj.pos.y;
                player->cam.at.z = gCsCamAtZ = actor->obj.pos.z;

                D_ctx_80177A48[0] = 0.0f;
                gFillScreenAlpha = 255;

                for (i = 0; i < 4; i++) {
                    Object_Kill(&gActors[i + 30].obj, gActors[i + 30].sfxSource);
                }

                player->pos.x = actor->obj.pos.x + 200.0f;
                player->pos.y = actor->obj.pos.y - 480.0f;
                player->pos.z = actor->obj.pos.z;

                AUDIO_PLAY_BGM(NA_BGM_SZ_START_DEMO);
            }
            break;

        case 3:
            gFillScreenAlpha = 0;
            gCsCamEyeX = -1250.0f;
            gCsCamEyeY = -395.0f;

            gCsCamAtX = player->pos.x;
            gCsCamAtY = player->pos.y;
            gCsCamAtZ = player->pos.z;

            Math_SmoothStepToF(D_ctx_80177A48, 0.05f, 1.0f, 0.0005f, 0.0f);

            gActors[30].obj.rot.x -= 0.65f;
            gActors[31].obj.rot.x -= 0.65f;
            gActors[32].obj.rot.x -= 0.65f;
            gActors[30].iwork[11] = 2;
            gActors[31].iwork[11] = 2;
            gActors[32].iwork[11] = 2;
            gActors[30].obj.rot.y += 0.5f;
            gActors[31].obj.rot.y -= 0.4f;
            gActors[32].obj.rot.y += 0.6f;
            gActors[30].vel.z += 0.325f;
            gActors[31].vel.z -= 0.26f;
            gActors[32].vel.z += 0.39000002f;
            gActors[30].obj.rot.z += 0.2f;
            gActors[31].obj.rot.z -= 0.3f;
            gActors[32].obj.rot.z -= 0.3f;
            gActors[30].vel.y += 0.4f;
            gActors[31].vel.y += 0.27f;
            gActors[32].vel.y += 0.4f;

            if (gCsFrameCount > 760) {
                player->rot.x += 0.25f;
            }

            if (gCsFrameCount > 765) {
                gCsCamEyeZ += 3.0f;
                Math_SmoothStepToF(D_ctx_80177A48, 0.9f, 1.0f, 0.07f, 0.0f);
            } else {
                gCsCamEyeZ = 0.0f;
            }

            if (gCsFrameCount == 800) {
                for (i = 0; i < ARRAY_COUNT(gActors); i++) {
                    Object_Kill(&gActors[i].obj, gActors[i].sfxSource);
                }
                SectorZ_8019EA68();
                SectorZ_8019B888();
            }

            if (gCsFrameCount == 820) {
                Audio_KillSfxById(NA_SE_DEMO_SIREN);
                player->state_1C8 = PLAYERSTATE_1C8_ACTIVE;
                player->unk_01C = player->unk_018 = player->unk_014 = 0.f;
                AUDIO_PLAY_BGM(gBgmSeqId);
                gLevelStartStatusScreenTimer = 50;
            }
            break;
    }

    switch (gCsFrameCount) {
        case 20:
            AUDIO_PLAY_SFX(NA_SE_DEMO_SIREN, gDefaultSfxSource, 4);
            break;

        case 330:
            Radio_PlayMessage(gMsg_ID_16010, RCID_ROB64);
            break;

        case 80:
            break;

        case 370:
            SectorZ_8019B630(&gActors[30], 0);
            break;

        case 390:
            SectorZ_8019B630(&gActors[31], 1);
            break;

        case 405:
            SectorZ_8019B630(&gActors[32], 2);
            break;

        case 425:
            SectorZ_8019B630(&gActors[33], 3);
            break;

        case 560:
            Radio_PlayMessage(gMsg_ID_16020, RCID_FOX);
            break;

        case 700:
            if (gTeamShields[TEAM_ID_SLIPPY] > 0) {
                SectorZ_8019B75C(&gActors[30], 0);
            }
            break;

        case 720:
            if (gTeamShields[TEAM_ID_FALCO] > 0) {
                SectorZ_8019B75C(&gActors[31], 1);
            }
            break;

        case 740:
            if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                SectorZ_8019B75C(&gActors[32], 2);
            }
            break;

        case 760:
            player->unk_194 = 5.0f;
            player->unk_190 = 5.0f;
            player->yRot_114 = 90.0f;
            player->baseSpeed = gArwingSpeed;
            player->unk_234 = 1;
            AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, player->sfxSource, 0);
            break;
    }

    Matrix_RotateY(gCalcMatrix, (player->rot.y + player->yRot_114 + 180.0f) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -(player->rot.x * M_DTOR), MTXF_APPLY);

    sp74.x = 0.0f;
    sp74.y = 0.0f;
    sp74.z = player->baseSpeed;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp74, &sp68);

    player->vel.x = sp68.x;
    player->vel.z = sp68.z;
    player->vel.y = sp68.y;

    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;
    player->pos.z += player->vel.z;

    player->trueZpos = player->pos.z;
    player->bankAngle = player->rot.z + player->zRotBank + player->zRotBarrelRoll;

    Math_SmoothStepToF(&player->cam.eye.x, gCsCamEyeX, D_ctx_80177A48[0], 50000.0f, 0);
    Math_SmoothStepToF(&player->cam.eye.y, gCsCamEyeY, D_ctx_80177A48[0], 50000.0f, 0);
    Math_SmoothStepToF(&player->cam.eye.z, gCsCamEyeZ, D_ctx_80177A48[0], 50000.0f, 0);
    Math_SmoothStepToF(&player->cam.at.x, gCsCamAtX, D_ctx_80177A48[0], 50000.0f, 0);
    Math_SmoothStepToF(&player->cam.at.y, gCsCamAtY, D_ctx_80177A48[0], 50000.0f, 0);
    Math_SmoothStepToF(&player->cam.at.z, gCsCamAtZ, D_ctx_80177A48[0], 50000.0f, 0);
}

f32 D_i4_8019F61C[] = { -300.0f, 350.0f, -50.0f, 800.0f };

f32 D_i4_8019F62C[] = { 0.0f, -30.0f, -90.0f, -550.0f };

f32 D_i4_8019F63C[] = { -200.0f, -250.0f, -500.0f, 5000.0f };

void SectorZ_8019C574(Actor* actor, s32 index) {
    f32 var_fv0 = 1.0f;

    if (!gGreatFoxIntact) {
        var_fv0 = -1.0f;
    }

    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_CUTSCENE;

    actor->obj.pos.x = D_i4_8019F61C[index] * var_fv0;
    actor->obj.pos.y = D_i4_8019F62C[index];
    actor->obj.pos.z = D_i4_8019F63C[index];

    actor->fwork[0] = gPlayer[0].baseSpeed;
    actor->rot_0F4.y = gPlayer[0].rot.y;

    Object_SetInfo(&actor->info, actor->obj.id);

    if (index < 3) {
        actor->iwork[11] = 1;
        AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, actor->sfxSource, 4);
    } else {
        actor->animFrame = 1;
        actor->fwork[0] = 20.0f;

        AUDIO_PLAY_SFX(NA_SE_GREATFOX_ENGINE, actor->sfxSource, 0);
        AUDIO_PLAY_SFX(NA_SE_GREATFOX_BURNER, actor->sfxSource, 0);
    }
}

void SectorZ_8019C70C(void) {
    Actor* actor = &gActors[8];

    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_CUTSCENE;

    actor->obj.pos.x = gBosses[0].obj.pos.x + 700.0f;
    actor->obj.pos.y = gBosses[0].obj.pos.y - 1000.0f;
    actor->obj.pos.z = gBosses[0].obj.pos.z - 1000.0f;

    actor->rot_0F4.y = 180.0f;
    actor->rot_0F4.x = 20.0f;

    actor->obj.rot.x = -20.0f;
    actor->obj.rot.y = 180.0f;
    actor->obj.rot.y = 2.0f * actor->obj.rot.y;
    actor->obj.rot.z = -actor->rot_0F4.z;

    actor->fwork[0] = 30.0f;
    actor->animFrame = 24;
    actor->iwork[11] = 1;
    actor->state = 10;
    actor->timer_0BC = 130;

    Object_SetInfo(&actor->info, actor->obj.id);
    AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, actor->sfxSource, 4);
}

void SectorZ_LevelComplete(Player* player) {
    s32 i;
    Vec3f src;
    Vec3f dest;
    Actor* actor0 = &gActors[0];
    Actor* actor1 = &gActors[1];
    Actor* actor2 = &gActors[2];
    Actor* actor3 = &gActors[3];
    Boss* boss0 = &gBosses[0];
    f32 var_fv1 = 1.0f;

    if (!gGreatFoxIntact) {
        var_fv1 = -1.0f;
    }

    Math_SmoothStepToF(&player->boostSpeed, 0.0f, 0.1f, 1.5f, 0.0f);

    switch (player->csState) {
        case 1000:
            Math_SmoothStepToF(&player->rot.y, -40.0f, 0.1f, 2.5f, 0);
            Math_SmoothStepToF(&player->rot.z, -60.0f, 0.2f, 5.0f, 0);
            Math_SmoothStepToF(&player->rot.x, 0, 0.1f, 2.5f, 0);
            if (player->csTimer == 0) {
                player->csState = 1001;
                player->csTimer = 100;
                AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, player->sfxSource, 0);
                player->unk_194 = 5.0f;
                player->unk_190 = 5.0f;
                gProjectFar = 30000.0f;
            }
            break;

        case 1001:
            player->unk_190 = 2.0f;

            Math_SmoothStepToF(&player->rot.x, 15.0f, 0.1f, 0.4f, 0);
            Math_SmoothStepToF(&player->rot.z, 40.0f, 0.2f, 5.0f, 0);
            Math_SmoothStepToF(&player->rot.y, 120.0f, 0.1f, 2.0f, 0);

            player->baseSpeed += 1.0f;
            if (player->baseSpeed >= 70.0f) {
                player->baseSpeed = 70.0f;
            }

            if (player->csTimer == 0) {
                gPlayer[0].csState = 0;
            }
            break;

        case 100:
            gCsCamEyeX = boss0->obj.pos.x;
            gCsCamEyeY = boss0->obj.pos.y;
            gCsCamEyeZ = boss0->obj.pos.z + 4000.0f;

            gCsCamAtX = boss0->obj.pos.x;
            gCsCamAtY = boss0->obj.pos.y;
            gCsCamAtZ = boss0->obj.pos.z;

            D_ctx_80177A48[0] = 1.0f;
            gProjectFar = 30000.0f;

            player->unk_234 = 0;
            player->baseSpeed = 0.0f;
            player->camRoll = 0.0f;

            if (boss0->state != 0) {
                player->csState = 0;
            }
            break;

        case 0:
            gCsFrameCount = 0;

            player->unk_234 = 0;

            gCsCamEyeX = boss0->obj.pos.x;
            gCsCamEyeY = boss0->obj.pos.y;
            gCsCamEyeZ = boss0->obj.pos.z + 4000.0f;

            D_ctx_80177A48[0] = 1.0f;

            player->csState = 1;

            gProjectFar = 30000.0f;

            player->csTimer = 550;
            player->baseSpeed = 0.0f;
            player->camRoll = 0.0f;

            gFillScreenAlphaTarget = 255;
            gFillScreenAlpha = gFillScreenAlphaTarget;

            for (i = 0; i < ARRAY_COUNT(gActors); i++) {
                Object_Kill(&gActors[i].obj, gActors[i].sfxSource);
            }
            AUDIO_PLAY_SFX(NA_SE_GREATFOX_BURNER, boss0->sfxSource, 0);
            break;

        case 1:
            gFillScreenAlphaTarget = 0;
            gFillScreenAlpha = 0;

            Math_SmoothStepToAngle(&boss0->rot_078.x, 20.0f, 0.03f, boss0->fwork[1], 0.0f);
            Math_SmoothStepToAngle(&boss0->rot_078.y, 180.0f, 0.03f, boss0->fwork[2], 0.0f);
            Math_SmoothStepToAngle(&boss0->rot_078.z, 30.0f, 0.03f, boss0->fwork[3], 0.0f);
            Math_SmoothStepToF(&boss0->fwork[0], 20.0f, 0.05f, 0.3f, 0.0f);
            Math_SmoothStepToF(&boss0->fwork[1], 0.07f, 1.0f, 0.07f, 0.0f);
            Math_SmoothStepToF(&boss0->fwork[2], 0.5f, 1.0f, 0.05f, 0.0f);
            Math_SmoothStepToF(&boss0->fwork[3], 0.7f, 1.0f, 0.7f, 0.0f);

            if ((gCsFrameCount == 100) && gGreatFoxIntact) {
                AUDIO_PLAY_BGM(NA_BGM_COURSE_CLEAR);
            }

            if ((gCsFrameCount == 210) && gGreatFoxIntact) {
                gLevelClearScreenTimer = 100;
                gMissionStatus = MISSION_ACCOMPLISHED;
            }

            if ((gCsFrameCount == 230) && (D_i4_801A0564 != 0)) {
                SectorZ_8019C70C();
            }

            gCsCamAtX = boss0->obj.pos.x;
            gCsCamAtY = boss0->obj.pos.y + (2.0f * gCameraShakeY);
            gCsCamAtZ = boss0->obj.pos.z;

            if (player->csTimer == 0) {
                player->csState = 2;
            }
            break;

        case 2:
            gFillScreenAlphaTarget = 0;
            gFillScreenAlpha = 0;

            if (player->csTimer == 0) {
                if (!gGreatFoxIntact) {
                    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 50);
                    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 50);
                }

                gCsFrameCount = 1280;

                player->csState = 10;
                player->csTimer = 1000;

                Audio_StopPlayerNoise(0);
                Audio_KillSfxBySource(player->sfxSource);
                Play_ClearObjectData();

                player->pos.x = 0.0f;
                player->pos.y = 0.0f;
                player->pos.z = 0.0f;

                player->rot.x = 0.0f;
                player->unk_234 = 1;
                player->rot.y = 180.0f;
                player->rot.z = 0.0f;
                player->yRot_114 = 0.0f;
                player->aerobaticPitch = 0.0f;
                player->baseSpeed = 40.0f;

                gCsCamEyeX = 0.0f - (200.0f * var_fv1);
                gCsCamEyeY = player->pos.y;
                gCsCamEyeZ = player->pos.z + 12000.0f;
                gCsCamAtX = player->pos.x;
                gCsCamAtY = player->pos.y;
                gCsCamAtZ = player->pos.z;

                if (gTeamShields[TEAM_ID_FALCO] > 0) {
                    SectorZ_8019C574(actor1, 0);
                }
                if (gTeamShields[TEAM_ID_SLIPPY] > 0) {
                    SectorZ_8019C574(actor3, 1);
                }
                if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                    SectorZ_8019C574(actor2, 2);
                }
                SectorZ_8019C574(actor0, 3);
                gFillScreenAlpha = gFillScreenAlphaTarget = 255;
            }
            break;

        case 10:
            gFillScreenAlpha = gFillScreenAlphaTarget = 0;
            gCsCamAtX = player->pos.x;
            gCsCamAtY = player->pos.y;
            gCsCamAtZ = player->pos.z;

            if (gCsFrameCount == 1620) {
                player->csState++;
                D_ctx_80177A48[0] = 0.0f;
                D_ctx_80177A48[1] = 0.0f;
                D_ctx_80177A48[2] = 0.0f;
                D_ctx_80177A48[3] = 300.0f;

                for (i = 0; i < 200; i++) {
                    gScenery360[i].obj.status = OBJ_FREE;
                }
            }
            break;

        case 11:
            Matrix_RotateY(gCalcMatrix, D_ctx_80177A48[1] * M_DTOR, MTXF_NEW);
            D_ctx_80177A48[1] += D_ctx_80177A48[2] * var_fv1;

            src.x = -800.0f * var_fv1;
            src.y = D_ctx_80177A48[3];
            src.z = 0.0f;

            Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

            Math_SmoothStepToF(&player->baseSpeed, 0, 0.05f, 1.0f, 0);
            Math_SmoothStepToF(&actor1->fwork[0], 0, 0.05f, 1.0f, 0);
            Math_SmoothStepToF(&actor3->fwork[0], 0, 0.05f, 1.0f, 0);
            Math_SmoothStepToF(&actor2->fwork[0], 0.0f, 0.05f, 1.0f, 0);
            Math_SmoothStepToF(&actor0->fwork[0], 0.0f, 0.05f, 1.0f, 0);
            Math_SmoothStepToF(D_ctx_80177A48, 0.02f, 1.0f, 0.001f, 0);

            if (gCsFrameCount > 2000) {
                Math_SmoothStepToF(&D_ctx_80177A48[3], 50.0f, 0.05f, 1.5f, 0);
            }

            if (gCsFrameCount < 2330) {
                Math_SmoothStepToF(&D_ctx_80177A48[2], 0.5f, 1.0f, 0.008f, 0);
            } else {
                Math_SmoothStepToF(&D_ctx_80177A48[2], 0.0f, 1.0f, 0.002f, 0);
            }

            if (gCsFrameCount > 2510) {
                player->baseSpeed += 2.0f;
                player->rot.x += 0.1f;
                player->unk_190 = 2.0f;
            }

            if (gCsFrameCount > 2550) {
                Math_SmoothStepToF(&D_ctx_80177A48[0], 0.1f, 1.0f, 0.005f, 0);
            } else {
                gCsCamEyeX = actor0->obj.pos.x - (800.0f * var_fv1) + dest.x;
                gCsCamEyeY = actor0->obj.pos.y + 550.0f + dest.y;
                gCsCamEyeZ = actor0->obj.pos.z + 2430.0f + dest.z;
            }

            gCsCamAtX = actor0->obj.pos.x - (800.0f * var_fv1);
            gCsCamAtY = actor0->obj.pos.y + 550.0f;
            gCsCamAtZ = actor0->obj.pos.z + 2430.0f - 250.0f;

            if (gCsFrameCount == 2660) {
                Audio_FadeOutAll(50);
            }

            if (gCsFrameCount > 2710) {
                gFillScreenAlphaTarget = 255;
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
                gFillScreenAlphaStep = 8;
                if (gFillScreenAlpha == 255) {
                    player->state_1C8 = PLAYERSTATE_1C8_NEXT;
                    player->csTimer = 0;
                    gFadeoutType = 4;
                    gLeveLClearStatus[LEVEL_SECTOR_Z] = Play_CheckMedalStatus(100) + 1;
                }
            }
            break;
    }

    if (gGreatFoxIntact) {
        switch (gCsFrameCount) {
            case 1729:
                Radio_PlayMessage(gMsg_ID_16250, RCID_ROB64);
                break;

            case 1847:
                switch (gTeamShields[TEAM_ID_FALCO]) {
                    case -1:
                        Radio_PlayMessage(gMsg_ID_20337, RCID_ROB64);
                        break;

                    case 0:
                        Radio_PlayMessage(gMsg_ID_20343, RCID_ROB64);
                        break;

                    default:
                        Radio_PlayMessage(gMsg_ID_16260, RCID_FALCO);
                        break;
                }
                break;

            case 1984:
                switch (gTeamShields[TEAM_ID_PEPPY]) {
                    case -1:
                        Radio_PlayMessage(gMsg_ID_20338, RCID_ROB64);
                        break;

                    case 0:
                        Radio_PlayMessage(gMsg_ID_20344, RCID_ROB64);
                        break;

                    default:
                        Radio_PlayMessage(gMsg_ID_16270, RCID_PEPPY);
                        break;
                }
                break;

            case 2130:
                switch (gTeamShields[TEAM_ID_SLIPPY]) {
                    case -1:
                        Radio_PlayMessage(gMsg_ID_20339, RCID_ROB64);
                        break;

                    case 0:
                        Radio_PlayMessage(gMsg_ID_20345, RCID_ROB64);
                        break;

                    default:
                        Radio_PlayMessage(gMsg_ID_16280, RCID_SLIPPY);
                        break;
                }

                break;
        }

    } else {
        switch (gCsFrameCount) {
            case 1729:
                Radio_PlayMessage(gMsg_ID_16210, RCID_ROB64);
                break;

            case 1847:
                switch (gTeamShields[TEAM_ID_FALCO]) {
                    case -1:
                        Radio_PlayMessage(gMsg_ID_20337, RCID_ROB64);
                        break;

                    case 0:
                        Radio_PlayMessage(gMsg_ID_20343, RCID_ROB64);
                        break;

                    default:
                        Radio_PlayMessage(gMsg_ID_16220, RCID_FALCO);
                        break;
                }
                break;

            case 1984:
                switch (gTeamShields[TEAM_ID_PEPPY]) {
                    case -1:
                        Radio_PlayMessage(gMsg_ID_20338, RCID_ROB64);
                        break;

                    case 0:
                        Radio_PlayMessage(gMsg_ID_20344, RCID_ROB64);
                        break;

                    default:
                        Radio_PlayMessage(gMsg_ID_16230, RCID_PEPPY);
                        break;
                }
                break;

            case 2130:
                switch (gTeamShields[TEAM_ID_SLIPPY]) {
                    case -1:
                        Radio_PlayMessage(gMsg_ID_20339, RCID_ROB64);
                        break;

                    case 0:
                        Radio_PlayMessage(gMsg_ID_20345, RCID_ROB64);
                        break;

                    default:
                        Radio_PlayMessage(gMsg_ID_16240, RCID_SLIPPY);
                        break;
                }
                break;
        }
    }
    switch (gCsFrameCount) {
        case 1640:
            Radio_PlayMessage(gMsg_ID_16200, RCID_FOX);
            break;

        case 2277:
            gShowLevelClearStatusScreen = 1;
            break;

        case 2477:
            gShowLevelClearStatusScreen = 0;
            break;

        case 1370:
            if (gGreatFoxIntact) {
                gMissionStatus = MISSION_ACCOMPLISHED;
            } else {
                AUDIO_PLAY_BGM(NA_BGM_COURSE_FAILURE);
                gMissionStatus = MISSION_COMPLETE;
            }
            break;

        case 1560:
            if (!gGreatFoxIntact) {
                gLevelClearScreenTimer = 100;
            }
            break;

        case 1700:
            player->unk_204 = gLevelType;
            break;

        case 2450:
            actor2->state = 1;
            break;

        case 2470:
            actor3->state = 1;
            break;

        case 2490:
            gActors[1].state = 1;
            break;

        case 2510:
            AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, player->sfxSource, 0);
            player->unk_190 = player->unk_194 = 5.0f;
            break;

        case 2550:
            gActors[0].state = 1;
            break;
    }

    Matrix_RotateY(gCalcMatrix, ((player->yRot_114 + player->rot.y) + 180.0f) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -(((player->xRot_120 + player->rot.x) + player->aerobaticPitch) * M_DTOR), MTXF_APPLY);

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

    player->trueZpos = player->pos.z;
    player->bankAngle = player->rot.z + player->zRotBank + player->zRotBarrelRoll;

    Math_SmoothStepToF(&player->zRotBarrelRoll, 0.0f, 0.1f, 15.0f, 0.0f);
    Math_SmoothStepToF(&player->zRotBank, 0.0f, 0.1f, 15.0f, 0.0f);
    Math_SmoothStepToF(&player->camRoll, 0.0f, 0.1f, 3.0f, 0.0f);
    Math_SmoothStepToAngle(&player->aerobaticPitch, 0.0f, 0.1f, 20.0f, 0.0f);

    if (player->csState >= 1000) {
        if (player->pos.y < 700.0f) {
            Math_SmoothStepToF(&player->pos.y, 700.0f, 0.1f, 10.0f, 0.0f);
        }
        Camera_Update360(player, 0);
        player->cam.eye.x += player->vel.x * 0.1f;
        player->cam.eye.y += player->vel.y * 0.1f;
        player->cam.eye.z += player->vel.z * 0.1f;
    } else {
        Math_SmoothStepToF(&player->cam.eye.x, gCsCamEyeX, D_ctx_80177A48[0], 50000.0f, 0.0f);
        Math_SmoothStepToF(&player->cam.eye.y, gCsCamEyeY, D_ctx_80177A48[0], 50000.0f, 0.0f);
        Math_SmoothStepToF(&player->cam.eye.z, gCsCamEyeZ, D_ctx_80177A48[0], 50000.0f, 0.0f);
        Math_SmoothStepToF(&player->cam.at.x, gCsCamAtX, D_ctx_80177A48[0], 50000.0f, 0.0f);
        Math_SmoothStepToF(&player->cam.at.y, gCsCamAtY, D_ctx_80177A48[0], 50000.0f, 0.0f);
        Math_SmoothStepToF(&player->cam.at.z, gCsCamAtZ, D_ctx_80177A48[0], 50000.0f, 0.0f);
    }

    player->bobPhase += 10.0f;
    player->yBob = -SIN_DEG(player->bobPhase) * 0.3f;
    player->rockPhase += 8.0f;
    player->rockAngle = SIN_DEG(player->rockPhase);
}

void SectorZ_8019DD20(Actor* actor) {
    Vec3f src;
    Vec3f dest;

    switch (actor->state) {
        case 1:
            actor->state = 2;
            AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, actor->sfxSource, 0);
            actor->fwork[29] = 5.0f;

        case 2:
            actor->iwork[11] = 2;
            actor->fwork[0] += 2.0f;
            actor->rot_0F4.x += actor->fwork[1];
            Math_SmoothStepToF(&actor->fwork[1], 0.1f, 1.0f, 0.01f, 0.0f);
            break;

        case 10:
            if (actor->timer_0BC == 0) {
                actor->state = 11;
            }
            break;

        case 11:
            Math_SmoothStepToF(&actor->rot_0F4.x, 215.0f, 0.1f, 7.0f, 0.0f);
            Math_SmoothStepToF(&actor->fwork[0], 10.0f, 0.1f, 1.5f, 0.0f);
            Math_SmoothStepToAngle(&actor->rot_0F4.y, 140.0f, 0.1f, 1.0f, 0.0f);
            if (actor->rot_0F4.x > 180.0f) {
                actor->state = 12;
            }
            break;

        case 12:
            Math_SmoothStepToAngle(&actor->rot_0F4.x, 218.0f, 0.1f, 7.0f, 0.0f);
            Math_SmoothStepToAngle(&actor->rot_0F4.y, 147.0f, 0.1f, 1.0f, 0.0f);
            Math_SmoothStepToF(&actor->rot_0F4.z, 170.0f, 0.03f, 3.0f, 0.0f);
            Math_SmoothStepToF(&actor->fwork[0], 20.0f, 0.1f, 1.0f, 0.0f);
            break;
    }

    if (actor->animFrame == 24) {
        switch (gCsFrameCount) {
            case 290:
                if (gTeamShields[TEAM_ID_FALCO] > 0) {
                    Radio_PlayMessage(gMsg_ID_16150, RCID_KATT);
                }
                break;

            case 430:
                AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, actor->sfxSource, 0);
                actor->fwork[29] = 8.0f;
                break;

            case 400:
                if (gGreatFoxIntact) {
                    Radio_PlayMessage(gMsg_ID_16160, RCID_KATT);
                } else {
                    Radio_PlayMessage(gMsg_ID_16165, RCID_KATT);
                }
                break;
        }

        if (gCsFrameCount > 430) {
            actor->fwork[29] = 3.0f;
            Math_SmoothStepToF(&actor->rot_0F4.z, 500.0f, 0.1f, 20.0f, 0.0f);
            Math_SmoothStepToF(&actor->fwork[0], 40.0f, 0.1f, 3.0f, 0.0f);

            if ((gCsFrameCount < 460) && ((gCsFrameCount & 3) == 0)) {
                Matrix_RotateY(gCalcMatrix, actor->obj.rot.y * M_DTOR, MTXF_NEW);
                Matrix_RotateX(gCalcMatrix, actor->obj.rot.x * M_DTOR, MTXF_APPLY);
                Matrix_RotateZ(gCalcMatrix, actor->obj.rot.z * M_DTOR, MTXF_APPLY);
                src.x = 0.0f;
                src.y = 70.0f;
                src.z = -70.0f;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);
                func_effect_80078E50(actor->obj.pos.x + dest.x, actor->obj.pos.y + dest.y, actor->obj.pos.z + dest.z,
                                     3.1f);
            }
        }
    }

    Matrix_RotateY(gCalcMatrix, (actor->rot_0F4.y + 180.0f) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -(actor->rot_0F4.x * M_DTOR), MTXF_APPLY);

    src.x = 0.0f;
    src.y = 0.0f;
    src.z = actor->fwork[0];

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

    actor->vel.x = dest.x;
    actor->vel.y = dest.y;
    actor->vel.z = dest.z;

    actor->obj.rot.x = -actor->rot_0F4.x;
    actor->obj.rot.y = actor->rot_0F4.y + 180.0f;
    actor->obj.rot.z = -actor->rot_0F4.z;
}

void SectorZ_8019E234(Actor* actor) {
    s32 i;

    actor->obj.rot.x += actor->rot_0F4.x;
    actor->obj.rot.y += actor->rot_0F4.y;

    if (actor->dmgType != DMG_NONE) {
        actor->timer_0C6 = 20;
        actor->dmgType = DMG_NONE;
        actor->health -= actor->damage;
        AUDIO_PLAY_SFX(NA_SE_EN_DAMAGE_S, actor->sfxSource, 4);
        if (actor->health <= 0) {
            func_effect_8007BFFC(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, 0.0f, 0.0f, 0.0f, 5.0f, 10);
            Actor_Despawn(actor);
            BonusText_Display(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, 2);
            gHitCount += 3;
            D_ctx_80177850 = 15;
            for (i = 0; i < 6; i++) {
                func_effect_800794CC(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, 1.0f);
            }
            Object_Kill(&actor->obj, actor->sfxSource);
            func_effect_8007A6F0(&actor->obj.pos, NA_SE_OB_EXPLOSION_S);
        }
    }
}

void SectorZ_8019E3A8(Actor* actor) {
    gSPDisplayList(gMasterDisp++, D_SZ_6001A10);
    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
    RCP_SetupDL(&gMasterDisp, SETUPDL_57);
    gSPDisplayList(gMasterDisp++, D_SZ_60045E0);
    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
}

Vec3f D_i4_8019F64C[] = { { 612.0f, 409.0f, 386.0f }, { 1027.0f, 141.0f, 383.0f }, { 375.0f, 292.0f, 380.0f },
                          { -4.0f, 80.0f, 380.0f },   { 314.0f, 80.0f, 385.0f },   { 565.0f, 300.0f, 385.0f },
                          { 600.0f, 385.0f, 380.0f }, { 776.0f, 245.0f, 384.0f },  { 376.0f, 123.0f, 384.0f },
                          { 428.0f, 174.0f, 383.0f }, { 722.0f, 306.0f, 383.0f },  { 530.0f, 380.0f, 385.0f } };

void SectorZ_Boss_Update(Boss* boss) {
    s32 i;
    s32 j;
    f32 x;
    f32 y;
    f32 z;
    Vec3f src;
    Vec3f dest;

    if (boss->dmgType == DMG_UNK_100) {
        boss->dmgType = DMG_NONE;
        boss->timer_050 = 10;
        boss->timer_052 = 60;
        boss->state = 1;
        AUDIO_PLAY_SFX(NA_SE_OB_BROKEN_SPARK_L, boss->sfxSource, 0);
    }

    if (boss->timer_050 == 1) {
        gGreatFoxIntact = false;
    }

    if (boss->timer_050 == 5) {
        x = boss->obj.pos.x + 400.0f;
        y = boss->obj.pos.y + 200.0f;
        z = boss->obj.pos.z + 1000.0f;

        for (i = 0; i < 25; i++) {
            func_effect_800794CC(x + RAND_FLOAT_CENTERED(300.0f), y + RAND_FLOAT_CENTERED(100.0f), z, 2.0f);
            func_effect_80079618(x + RAND_FLOAT_CENTERED(300.0f), y + RAND_FLOAT_CENTERED(100.0f), z, 2.0f);
        }
        func_effect_8007BFFC(x, y, z, 0.0f, 0.0f, 0.0f, 20.0f, 30);
    }

    if (boss->timer_052 != 0) {
        for (j = 0; j < 1; j++) {
            i = RAND_INT(11.99f);
            SectorZ_80199BDC(D_i4_8019F64C[i].x + boss->obj.pos.x, D_i4_8019F64C[i].y + boss->obj.pos.y,
                             D_i4_8019F64C[i].z + boss->obj.pos.z, RAND_FLOAT_CENTERED(5.0f), RAND_FLOAT_CENTERED(5.0f),
                             10.0f, RAND_FLOAT(2.0f) + 4.0f);
        }
    }

    Matrix_RotateY(gCalcMatrix, (boss->rot_078.y + 180.0f) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -(boss->rot_078.x * M_DTOR), MTXF_APPLY);

    src.x = 0.0f;
    src.y = 0.0f;
    src.z = boss->fwork[0];

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

    boss->vel.x = dest.x;
    boss->vel.y = dest.y;
    boss->vel.z = dest.z;

    boss->obj.rot.x = -boss->rot_078.x;
    boss->obj.rot.y = boss->rot_078.y + 180.0f;
    boss->obj.rot.z = -boss->rot_078.z;

    if (!gGreatFoxIntact) {
        Matrix_RotateY(gCalcMatrix, (boss->obj.rot.y - 270.0f) * M_DTOR, MTXF_NEW);
        Matrix_RotateX(gCalcMatrix, boss->obj.rot.x * M_DTOR, MTXF_APPLY);
        Matrix_RotateZ(gCalcMatrix, boss->obj.rot.z * M_DTOR, MTXF_APPLY);
        Matrix_MultVec3fNoTranslate(gCalcMatrix, &D_i4_8019F64C[RAND_INT(11.99f)], &dest);
        func_effect_8007C484(boss->obj.pos.x + dest.x, boss->obj.pos.y + dest.y, boss->obj.pos.z + dest.z, boss->vel.x,
                             boss->vel.y, boss->vel.z, RAND_FLOAT(0.1f) + 0.15f, 0);
        if (((gGameFrameCount % 7) == 0) && (Rand_ZeroOne() < 0.5f)) {
            SectorZ_80199BDC(boss->obj.pos.x + dest.x, boss->obj.pos.y + dest.y, boss->obj.pos.z + dest.z, boss->vel.x,
                             boss->vel.y, boss->vel.z + 5.0f, RAND_FLOAT(2.0f) + 4.0f);
        }
    }
}

void SectorZ_Boss_Draw(Boss* boss) {
    gSPFogPosition(gMasterDisp++, gFogNear, 1005);
    Cutscene_DrawGreatFox();
}

void SectorZ_8019EA68(void) {
    s32 i;
    s32 j;
    Actor* actor;
    Scenery360* scenery360;
    Boss* boss = &gBosses[0];

    gLevelObjects = LOAD_ASSET(gLevelObjectInits[gCurrentLevel]);

    Rand_SetSeed(1, 29000, 9876);

    for (scenery360 = gScenery360, i = 0; i < 1000; i++) {
        if (gLevelObjects[i].id <= OBJ_INVALID) {
            break;
        }

        if (gLevelObjects[i].id < OBJ_SCENERY_MAX) {
            Scenery360_Initialize(scenery360);
            scenery360->obj.status = OBJ_ACTIVE;
            scenery360->obj.id = gLevelObjects[i].id;
            scenery360->obj.pos.x = gLevelObjects[i].xPos;
            scenery360->obj.pos.y = gLevelObjects[i].yPos;
            scenery360->obj.pos.z = -gLevelObjects[i].zPos1;
            scenery360->obj.rot.y = gLevelObjects[i].rot.y;
            Object_SetInfo(&scenery360->info, scenery360->obj.id);
            scenery360++;
        }
    }

    for (j = 50, actor = &gActors[j], i = 0; i < 1000; i++) {
        if (gLevelObjects[i].id <= OBJ_INVALID) {
            break;
        }

        if ((gLevelObjects[i].id >= OBJ_ACTOR_START) && (gLevelObjects[i].id < OBJ_ACTOR_MAX)) {
            Actor_Initialize(actor);
            actor->obj.status = OBJ_INIT;
            actor->obj.id = gLevelObjects[i].id;
            actor->obj.pos.x = gLevelObjects[i].xPos;
            actor->obj.pos.y = gLevelObjects[i].yPos;
            actor->obj.pos.z = -gLevelObjects[i].zPos1;
            actor->health = 24;
            actor->rot_0F4.x = RAND_FLOAT_CENTERED(4.0f);
            actor->rot_0F4.y = RAND_FLOAT_CENTERED(4.0f);
            Object_SetInfo(&actor->info, actor->obj.id);
            actor->itemDrop = DROP_SILVER_RING;

            if (j++ >= ARRAY_COUNT(gActors)) {
                break;
            }
            actor++;
        }
    }

    Boss_Initialize(boss);
    boss->obj.status = OBJ_INIT;

    boss->obj.pos.x = 0.0f;
    boss->obj.pos.y = 0.0f;
    boss->obj.pos.z = 0.0f;

    boss->rot_078.y = 90.0f;

    boss->obj.rot.x = -boss->rot_078.x;
    boss->obj.rot.y = boss->rot_078.y + 180.0f;
    boss->obj.rot.z = -boss->rot_078.z;

    boss->obj.id = OBJ_BOSS_SZ;
    Object_SetInfo(&boss->info, boss->obj.id);
    AUDIO_PLAY_SFX(NA_SE_GREATFOX_ENGINE, boss->sfxSource, 0);
}
