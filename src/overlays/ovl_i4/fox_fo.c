/*
 * File: fox_fo.c
 * System: Fortuna
 * Description: Level: Fortuna
 */

#include "global.h"
#include "assets/ast_fortuna.h"

void Fortuna_801875F0(Actor* actor) {
    s32 i;
    s32 counter;
    Actor* actorPtr = &gActors[10];
    f32 D_i4_8019EDE0[] = { 180.0f, 60.0f, 300.0f };

    for (counter = 0, i = 0; i < 10; i++, actorPtr++) {
        if (actorPtr->obj.status != OBJ_FREE) {
            counter++;
        }
    }

    if ((counter < 10) && (actor->timer_0C0 == 0)) {
        if (gAllRangeEventTimer < (D_360_800C9B4C - 500)) {
            actor->timer_0C0 = 40;

            actor->unk_04E++;
            if (actor->unk_04E >= 3) {
                actor->unk_04E = 0;
            }

            for (i = 0, actorPtr = &gActors[10]; i < 10; i++, actorPtr++) {
                if (actorPtr->obj.status == OBJ_FREE) {
                    Actor_Initialize(actorPtr);
                    actorPtr->obj.status = OBJ_ACTIVE;
                    actorPtr->obj.id = OBJ_ACTOR_ALLRANGE;
                    actorPtr->obj.pos.x = gBosses[0].obj.pos.x;
                    actorPtr->obj.pos.y = gBosses[0].obj.pos.y + 20.0f;
                    actorPtr->obj.pos.z = gBosses[0].obj.pos.z;
                    actorPtr->state = 1;
                    actorPtr->timer_0BC = 100;
                    actorPtr->aiType = i + AI360_10;
                    actorPtr->aiIndex = -1;

                    if ((i == 3) && (Rand_ZeroOne() < 0.3f)) {
                        actorPtr->aiIndex = AI360_SLIPPY;
                    }
                    if ((i == 4) && (Rand_ZeroOne() < 0.3f)) {
                        actorPtr->aiIndex = AI360_PEPPY;
                    }
                    if ((i == 5) && (Rand_ZeroOne() < 0.3f)) {
                        actorPtr->aiIndex = AI360_FALCO;
                    }

                    actorPtr->unk_0F4.x = 3.0f;
                    actorPtr->unk_0F4.y = D_i4_8019EDE0[actor->unk_04E];
                    actorPtr->health = 24;
                    actorPtr->unk_0C9 = actorPtr->iwork[11] = 1;
                    actorPtr->itemDrop = DROP_SILVER_RING_50p;
                    Object_SetInfo(&actorPtr->info, actorPtr->obj.id);
                    AUDIO_PLAY_SFX(0x31000011U, actorPtr->sfxSource, 4);
                    break;
                }
            }
        }
    }
    func_360_8002F69C(actor);
}

f32 D_8019EDEC[] = { 0.0f, 700.0f, 12000.0f };

void Fortuna_80187884(Actor* actor, f32 xPos, f32 yPos, f32 zPos, f32 arg4) {
    s32 health = actor->health;
    PRINTF("Enm->work[0]=%d\n");
    PRINTF("tim %d\n");

    Actor_Initialize(actor);
    actor->health = health;
    actor->obj.status = OBJ_ACTIVE;
    actor->obj.pos.x = xPos;
    actor->obj.pos.y = yPos;
    actor->obj.pos.z = zPos;
    actor->obj.id = OBJ_ACTOR_ALLRANGE;
    actor->aiType = AI360_WOLF;
    actor->unk_0C9 = 1;
    actor->state = 0;
    actor->timer_0BC = 10000;
    actor->unk_0F4.y = arg4;
    actor->iwork[11] = 1;
    actor->unk_0F4.x = 0.0f;
    Object_SetInfo(&actor->info, actor->obj.id);
    AUDIO_PLAY_SFX(0x31004005U, actor->sfxSource, 4U);
}

Vec3f D_i4_8019EDF8[] = { { -300.0f, 1000.0f, 13000.0f }, { 300.0f, 700.0f, 14000.0f }, { 1000.0f, 300.0f, 0.0f } };
Vec3f D_i4_8019EE1C[] = { { -1000.0f, 300.0f, 0 }, { 0.0f, 500.0f, 0 } };

void Fortuna_80187960(Actor* actor) {
    s32 i;
    Player* player = &gPlayer[0];
    Actor* actorPtr;
    Actor* actor0 = &gActors[0];
    Actor* actor1 = &gActors[1];
    Actor* actor2 = &gActors[2];
    Actor* actor3 = &gActors[3];
    Actor* actor4 = &gActors[4];
    Actor* actor19 = &gActors[19];
    s32 pad[2];

    if ((player->state_1C8 == PLAYERSTATE_1C8_4) || (player->state_1C8 == PLAYERSTATE_1C8_6)) {
        gAllRangeEventTimer = 20000;
        return;
    }

    if (gAllRangeEventTimer == 50) {
        Radio_PlayMessage(gMsg_ID_9000, RCID_FOX);
    }

    if ((gAllRangeEventTimer + 400) == (0, D_360_800C9B4C)) {
        Radio_PlayMessage(gMsg_ID_9010, RCID_SLIPPY);
    }

    if ((gAllRangeEventTimer + 240) == (0, D_360_800C9B4C)) {
        Radio_PlayMessage(gMsg_ID_9375, RCID_ROB64);
        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 1);
        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 1);
    }

    if ((gAllRangeEventTimer + 100) == (0, D_360_800C9B4C)) {
        Radio_PlayMessage(gMsg_ID_9380, RCID_FOX);
    }

    if (gAllRangeEventTimer == 7160) {
        Radio_PlayMessage(gMsg_ID_9385, RCID_FOX);
    }

    if (gAllRangeEventTimer == 7000) {
        AUDIO_PLAY_SFX(0x11030016U, gBosses[0].sfxSource, 4U);
        func_360_8002EE34();
        Radio_PlayMessage(gMsg_ID_9390, RCID_ROB64);
        gAllRangeCountdownScale = 1.0f;
        gShowAllRangeCountdown = 1;
        gAllRangeCountdown[0] = 1;
        gAllRangeCountdown[1] = 4;
        gAllRangeCountdown[2] = 99;
    }

    if (gAllRangeEventTimer == 8036) {
        Radio_PlayMessage(gMsg_ID_9395, RCID_ROB64);
    }

    if (gAllRangeEventTimer == 8540) {
        Radio_PlayMessage(gMsg_ID_9400, RCID_ROB64);
        Audio_PlaySequence(SEQ_PLAYER_BGM, SEQ_ID_FORTUNA | SEQ_FLAG, 0, 0);
        gActors[1].aiIndex = gActors[2].aiIndex = gActors[3].aiIndex = gActors[4].aiIndex = gActors[5].aiIndex =
            gActors[6].aiIndex = gActors[7].aiIndex = -1;
    }

    if ((D_360_800C9B4C < gAllRangeEventTimer) && (gAllRangeEventTimer < 9970) && (gStarWolfTeamAlive[0] == 0) &&
        (gStarWolfTeamAlive[1] == 0) && (gStarWolfTeamAlive[2] == 0) && (gStarWolfTeamAlive[3] == 0)) {
        gAllRangeEventTimer = 9970;
    }

    if (gAllRangeEventTimer == 9056) {
        if ((gStarWolfTeamAlive[0] != 0) || (gStarWolfTeamAlive[1] != 0) || (gStarWolfTeamAlive[2] != 0) ||
            ((gStarWolfTeamAlive[3] != 0))) {
            Radio_PlayMessage(gMsg_ID_9405, RCID_ROB64);
        } else {
            gAllRangeEventTimer = 9995;
        }
    }

    if (gAllRangeEventTimer == 9206) {
        gShowAllRangeCountdown = 0;
        actor->state = 5;
        gPlayer[0].state_1C8 = PLAYERSTATE_1C8_0;
        actor->iwork[0] = 0;
        actor->fwork[0] = 0.0f;
        func_360_8002EE34();
        for (i = 4; i < 8; i++) {
            Object_Kill(&gActors[i].obj, gActors[i].sfxSource);
        }
    }

    if ((gAllRangeEventTimer == 10000) && ((gStarWolfTeamAlive[0] != 0) || (gStarWolfTeamAlive[1] != 0) ||
                                           (gStarWolfTeamAlive[2] != 0) || (gStarWolfTeamAlive[3] != 0))) {
        Radio_PlayMessage(gMsg_ID_9420, RCID_FOX);
    }

    if (gAllRangeEventTimer == 10100) {
        gShowAllRangeCountdown = 0;
        actor->iwork[0] = 0;
        actor->state = 6;
        gPlayer[0].state_1C8 = PLAYERSTATE_1C8_7;
        gPlayer[0].unk_1D0 = 0;
        gPlayer[0].unk_000 = 0.0f;

        func_360_8002EE34();

        for (i = 4; i < 8; i++) {
            Object_Kill(&gActors[i].obj, gActors[i].sfxSource);
        }

        if ((gStarWolfTeamAlive[0] == 0) && (gStarWolfTeamAlive[1] == 0) && (gStarWolfTeamAlive[2] == 0) &&
            (gStarWolfTeamAlive[3] == 0)) {
            Radio_PlayMessage(gMsg_ID_9411, RCID_FOX);
            gNextPlanetPath = 1;
            gPlayer[0].timer_1F8 = 50;
            player->unk_190 = 5.0f;
            player->unk_194 = 5.0f;
            AUDIO_PLAY_SFX(0x09000002U, player->sfxSource, 0U);
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 30);
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 30);
        } else {
            gNextPlanetPath = 0;
            gPlayer[0].timer_1F8 = 30;
        }
    }

    switch (actor->state) {
        case 0:
            D_360_800C9B4C = 2880;
            for (i = 0; i < 6; i++) {
                gSavedStarWolfTeamAlive[i] = 1;
                gStarWolfTeamAlive[i] = 1;
            }
            gAllRangeEventTimer = 0;
            gStarWolfMsgTimer = 0;
            if (player->state_1C8 == PLAYERSTATE_1C8_3) {
                actor->state = 2;
                player->pos.x = 0.0f;
                player->pos.z = 8000.0f;
                player->pos.y = 670.0f;
                gAllRangeEventTimer = 200;
                if (gAllRangeCheckpoint != 0) {
                    gAllRangeEventTimer = D_360_800C9B4C - 1;
                    gHitCount = gSavedHitCount;
                }
            } else {
                actor->state = 1;
                player->pos.x = 0.0f;
                player->pos.z = 15000.0f;
                player->pos.y = 670.0f;
                player->unk_114 = 0.0f;

                for (actorPtr = &gActors[1], i = 0; i < 3; i++, actorPtr++) {
                    actorPtr->obj.pos.x = D_i4_8019EDF8[i - 1].x;
                    actorPtr->obj.pos.y = D_i4_8019EDF8[i - 1].y;
                    actorPtr->obj.pos.z = D_i4_8019EDF8[i - 1].z;
                }
            }
            func_play_800B63BC(player, 1);
            break;

        case 1:
            for (actorPtr = actor0 + 1, i = 0; i < 3; i++, actorPtr++) {
                actorPtr->fwork[4] = D_i4_8019EE1C[i - 1].x;
                actorPtr->fwork[5] = D_i4_8019EE1C[i - 1].y;
                actorPtr->fwork[6] = D_i4_8019EE1C[i - 1].z;
                actorPtr->state = 3;
                actorPtr->timer_0BC = 3;
                if (gCsFrameCount == 264) {
                    actorPtr->state = 2;
                    actor->state = 2;
                    player->state_1C8 = PLAYERSTATE_1C8_3;
                    player->unk_014 = 0.0001f;
                    AUDIO_PLAY_BGM(gBgmSeqId);
                    gLevelStatusScreenTimer = 80;
                }
            };
            break;

        case 2:
            Fortuna_801875F0(actor);
            break;

        case 3:
            player->camEye.x += actor4->vel.x * 0.23f;
            player->camEye.y += actor4->vel.y * 0.23f;
            player->camEye.z += actor4->vel.z * 0.23f;
            Math_SmoothStepToF(&player->camAt.x, actor4->obj.pos.x, 1.0f, 20000.0f, 0.0f);
            Math_SmoothStepToF(&player->camAt.y, actor4->obj.pos.y, 1.0f, 20000.0f, 0.0f);
            Math_SmoothStepToF(&player->camAt.z, actor4->obj.pos.z, 1.0f, 20000.0f, 0.0f);
            Math_SmoothStepToF(&player->unk_034, 0.0f, 1.0f, 1000.0f, 0.0f);
            if (gAllRangeEventTimer == (D_360_800C9B4C + 2)) {
                gStarWolfMsgTimer = 883;
                gAllRangeCheckpoint = 1;

                gSavedHitCount = gHitCount;

                for (i = TEAM_ID_FALCO; i <= TEAM_ID_PEPPY; i++) {
                    gSavedTeamShields[i] = gTeamShields[i];
                };
            }

            if ((gControllerPress->button & START_BUTTON) || (gAllRangeEventTimer == (D_360_800C9B4C + 440))) {
                actor->state = 2;
                player->state_1C8 = PLAYERSTATE_1C8_3;
                func_play_800B7184(player, 1);
                player->unk_014 = 0.0f;
                D_hud_80161708 = 0;
            }
            gPauseEnabled = 0;
            break;

        case 5:
            gAllRangeEventTimer = 9207;
            actor->iwork[0] += 1;
            actor->fwork[0] += 10.0f;
            player->camEye.x = 300.0f;
            player->camEye.y = 300.0f;
            player->camEye.z = -1000.0f;
            player->camAt.x = actor->fwork[0] + 300.0f;
            player->camAt.y = actor->fwork[0] + 500.0f;
            player->camAt.z = -15000.0f;
            player->unk_034 = 0.0f;

            if ((actor->iwork[0] == 50) && (gStarWolfTeamAlive[0] != 0)) {
                if (gRadioState == 0) {
                    Radio_PlayMessage(gMsg_ID_9431, RCID_WOLF);
                }
                Fortuna_80187884(&gActors[4], player->camEye.x - 200.0f, player->camEye.y, player->camEye.z, 160.0f);
            }

            if ((actor->iwork[0] == 70) && (gStarWolfTeamAlive[1] != 0)) {
                if (gRadioState == 0) {
                    Radio_PlayMessage(gMsg_ID_9432, RCID_LEON);
                }
                Fortuna_80187884(&gActors[5], player->camEye.x, player->camEye.y + 50.0f, player->camEye.z, 160.0f);
            }

            if ((actor->iwork[0] == 90) && (gStarWolfTeamAlive[2] != 0)) {
                if (gRadioState == 0) {
                    Radio_PlayMessage(gMsg_ID_9433, RCID_PIGMA);
                }
                Fortuna_80187884(gActors + 6, player->camEye.x - 200.0f, player->camEye.y + 200.0f, player->camEye.z,
                                 160.0f);
            }

            if ((actor->iwork[0] == 110) && (gStarWolfTeamAlive[3] != 0)) {
                if (gRadioState == 0) {
                    Radio_PlayMessage(gMsg_ID_9434, RCID_ANDREW);
                }
                Fortuna_80187884(gActors + 7, player->camEye.x - 300.0f, player->camEye.y, player->camEye.z, 160.0f);
            }

            if (actor->iwork[0] == 250) {
                actor->state = 2;
                player->state_1C8 = PLAYERSTATE_1C8_3;

                func_play_800B7184(player, 1);

                player->unk_014 = 0.0f;
                D_hud_80161708 = 0;

                for (i = 4; i < 8; i++) {
                    Object_Kill(&gActors[i].obj, gActors[i].sfxSource);
                }

                gShowAllRangeCountdown = 1;
                gAllRangeEventTimer = 9970;
            }
            break;

        case 6:
            actor->iwork[0] += 1;
            if (gNextPlanetPath == 0) {
                actor1->aiIndex = AI360_FOX;
                actor1->state = 2;
                actor2->aiIndex = AI360_FOX;
                actor2->state = 2;
                actor3->aiIndex = AI360_FOX;
                actor3->state = 2;
                if (actor->iwork[0] == 130) {
                    Vec3f sp50 = { 0.0f, 0.0f, -10000 };

                    Actor_Initialize(actor19);
                    Matrix_Translate(gCalcMatrix, player->pos.x, player->pos.y, player->unk_138, 0);
                    Matrix_RotateY(gCalcMatrix, (player->unk_0E8 + player->unk_114) * M_DTOR, 1);
                    Matrix_RotateX(gCalcMatrix, player->unk_0E4 * M_DTOR, 1);
                    Matrix_MultVec3f(gCalcMatrix, &sp50, &actor19->obj.pos);

                    actor19->obj.status = OBJ_ACTIVE;
                    actor19->obj.id = OBJ_ACTOR_ALLRANGE;
                    actor19->state = 4;
                    actor19->unk_0F4.y = player->unk_0E8 + player->unk_114 + 180.0f;
                    actor19->unk_0F4.x = 15.0f;
                    actor19->aiType = AI360_GREAT_FOX;
                    actor19->fwork[1] = 90.0f;
                    actor19->fwork[0] = 90.0f;
                    Object_SetInfo(&actor19->info, actor19->obj.id);
                }
            }
            gOverlayStage = 1;
            D_game_80161A44 = 30000.0f;
            break;

        default:
            break;
    }

    if (gStarWolfMsgTimer != 0) {
        gStarWolfMsgTimer--;
        switch (gStarWolfMsgTimer) {
            case 860:
                if (gStarWolfTeamAlive[0] != 0) {
                    Radio_PlayMessage(gMsg_ID_9250, RCID_WOLF);
                }
                break;

            case 760:
                if (gStarWolfTeamAlive[1] != 0) {
                    Radio_PlayMessage(gMsg_ID_9260, RCID_LEON);
                }
                break;

            case 660:
                if (gStarWolfTeamAlive[2] != 0) {
                    if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                        Radio_PlayMessage(gMsg_ID_9275, RCID_PIGMA);
                    } else {
                        Radio_PlayMessage(gMsg_ID_9270, RCID_PIGMA);
                    }
                }
                break;

            case 540:
                if (gStarWolfTeamAlive[3] != 0) {
                    Radio_PlayMessage(gMsg_ID_9280, RCID_ANDREW);
                }
                break;

            case 380:
                Radio_PlayMessage(gMsg_ID_9285, RCID_FOX);
                break;

            case 240:
                Radio_PlayMessage(gMsg_ID_9385, RCID_FOX);
                break;
        }
    }
}

void Fortuna_801888C0(Actor* actor, Vec3f* pos, Vec3f* rot, f32 xVel, f32 yVel, f32 zVel, s32 state) {
    Actor_Initialize(actor);
    actor->obj.status = OBJ_ACTIVE;
    actor->obj.id = OBJ_ACTOR_189;
    actor->state = state;

    actor->obj.pos = *pos;
    actor->obj.rot = *rot;

    actor->vel.x = xVel;
    actor->vel.y = yVel;
    actor->vel.z = zVel;

    actor->scale = 2.5f;
    actor->timer_0BC = RAND_INT(15.0f) + 25.0f;
    actor->gravity = 0.5f;
    Object_SetInfo(&actor->info, actor->obj.id);
}

void Fortuna_80188A48(Vec3f* pos, Vec3f* rot, f32 xVel, f32 yVel, f32 zVel, s32 state) {
    s32 i;

    for (i = ARRAY_COUNT(gActors) - 1; i >= 30; i--) {
        if (gActors[i].obj.status == 0) {
            Fortuna_801888C0(&gActors[i], pos, rot, xVel, yVel, zVel, state);
            break;
        }
    }
}

void Fortuna_80188AD0(Actor* actor) {
    actor->fwork[0] += 2.0f;
    if (actor->state == 2) {
        actor->state = 3;
        Fortuna_80188A48(actor->vwork, &actor->vwork[6], RAND_FLOAT_CENTERED(50.0f), RAND_FLOAT(10.0f) + 10.0f,
                         RAND_FLOAT_CENTERED(50.0f), 36);
        Fortuna_80188A48(&actor->vwork[1], &actor->vwork[7], RAND_FLOAT_CENTERED(50.0f), RAND_FLOAT(10.0f) + 10.0f,
                         RAND_FLOAT_CENTERED(50.0f), 36);
        Fortuna_80188A48(&actor->vwork[2], &actor->vwork[8], RAND_FLOAT_CENTERED(50.0f), RAND_FLOAT(10.0f) + 10.0f,
                         RAND_FLOAT_CENTERED(50.0f), 35);
        Fortuna_80188A48(&actor->vwork[3], &actor->vwork[9], RAND_FLOAT_CENTERED(50.0f), RAND_FLOAT(10.0f) + 10.0f,
                         RAND_FLOAT_CENTERED(50.0f), 35);
        func_effect_8007BFFC(actor->obj.pos.x, actor->obj.pos.y + 180.0f, actor->obj.pos.z, 0.0f, 0.0f, 0.0f, 5.0f, 10);
        actor->itemDrop = DROP_SILVER_RING;
        actor->obj.pos.y += 230.0f;
        Actor_Despawn(actor);
        actor->obj.pos.y -= 230.0f;
    }

    if ((actor->unk_0D0 != 0) && (actor->state == 0)) {
        actor->unk_0D0 = 0;
        actor->state = 1;
        actor->info.hitbox = LOAD_ASSET(D_FO_600FF64);
        actor->info.unk_1C = 0.0f;
        actor->timer_0CA[0] = 0;
        actor->info.bonus = 0;
        AUDIO_PLAY_SFX(0x2903B009U, actor->sfxSource, 4U);
    }
}

void Fortuna_80188DA0(s32 limbIndex, Vec3f* rot, void* ptr) {
    Vec3f vec = { 0.0f, 0.0f, 0.0f };
    Actor* actor = (Actor*) ptr;

    if (actor->state == 1) {
        switch (limbIndex) {
            case 1:
                Matrix_MultVec3f(gCalcMatrix, &vec, actor->vwork);
                Matrix_GetYRPAngles(gCalcMatrix, &actor->vwork[6]);
                break;

            case 2:
                Matrix_MultVec3f(gCalcMatrix, &vec, &actor->vwork[1]);
                Matrix_GetYRPAngles(gCalcMatrix, &actor->vwork[7]);
                break;

            case 3:
                Matrix_MultVec3f(gCalcMatrix, &vec, &actor->vwork[2]);
                Matrix_GetYRPAngles(gCalcMatrix, &actor->vwork[8]);
                break;

            case 4:
                Matrix_MultVec3f(gCalcMatrix, &vec, &actor->vwork[3]);
                Matrix_GetYRPAngles(gCalcMatrix, &actor->vwork[9]);
                break;

            case 7:
                Matrix_MultVec3f(gCalcMatrix, &vec, &actor->vwork[4]);
                Matrix_GetYRPAngles(gCalcMatrix, &actor->vwork[10]);
                break;

            case 8:
                Matrix_MultVec3f(gCalcMatrix, &vec, &actor->vwork[5]);
                Matrix_GetYRPAngles(gCalcMatrix, &actor->vwork[11]);
                break;
        }
    }
}

bool Fortuna_80188F08(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* ptr) {
    Actor* actor = (Actor*) ptr;

    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);

    if ((actor->state != 0) && (limbIndex != 8)) {
        *dList = NULL;
    }

    switch (limbIndex) {
        case 1:
        case 2:
            gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
            break;

        case 5:
            rot->x += actor->fwork[0];
            break;

        case 6:
            rot->x += actor->fwork[0];
            break;

        case 7:
            rot->x += actor->fwork[0] * 0.7f;
            break;
    }

    return false;
}

void Fortuna_80188FE4(Actor* actor) {
    Vec3f vec[20];

    Animation_GetFrameData(&D_FO_6007854, 0, vec);
    Animation_DrawSkeleton(3, D_FO_6007980, vec, Fortuna_80188F08, Fortuna_80188DA0, actor, gCalcMatrix);

    if (actor->state == 1) {
        actor->state = 2;
    }
}

void Fortuna_8018906C(void) {
    Actor* actor = &gActors[50];

    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_195;
    actor->obj.pos.x = 0.0f;
    actor->obj.pos.y = 0.0f;
    actor->obj.pos.z = -9000.0f;
    actor->unk_0B6 = 11;
    actor->scale = 0.0f;
    Object_SetInfo(&actor->info, actor->obj.id);
}

f32 D_i4_8019EE4C[] = { -200.0f, 200.0f, -50.0f, -2000.0f };
f32 D_i4_8019EE5C[] = { 0.0f, 30.0f, -90.0f, 0.0f };
f32 D_i4_8019EE6C[] = { -100.0f, -200.0f, -300.0f, 0.0f };
s32 D_i4_8019EE7C = 0; // padding for dword aligned matrix?
Matrix D_BO_8019EE80 = { {
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f, 0.0f },
} };

void Fortuna_801890EC(Actor* actor, s32 arg1) {
    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_195;
    actor->obj.pos.x = D_i4_8019EE4C[arg1] + gPlayer[0].pos.x;
    actor->obj.pos.y = D_i4_8019EE5C[arg1] + gPlayer[0].pos.y;
    actor->obj.pos.z = D_i4_8019EE6C[arg1] + gPlayer[0].unk_138;
    actor->vel.z = gPlayer[0].unk_0D0;

    Object_SetInfo(&actor->info, actor->obj.id);

    if (arg1 < 3) {
        actor->iwork[11] = 1;
        AUDIO_PLAY_SFX(0x3100000CU, actor->sfxSource, 4U);
    } else {
        actor->obj.pos.z = -9500.0f;
        actor->unk_0B6 = 1;
        actor->vel.z = 22.0f;

        AUDIO_PLAY_SFX(0x11030010U, actor->sfxSource, 0U);
        AUDIO_PLAY_SFX(0x31024059U, actor->sfxSource, 0U);
    }
}

void Fortuna_8018927C(Player* player) {
    s32 i;
    Vec3f src;
    Vec3f dest;
    Actor* actor0 = &gActors[0];
    Actor* actor1 = &gActors[1];
    Actor* actor2 = &gActors[2];
    Actor* actor3 = &gActors[3];
    s32 pad[3];

    if ((player->unk_1D0 < 10) && (player->unk_1D0 >= 0)) {
        Math_SmoothStepToF(&player->unk_130, 0.0f, 0.1f, 15.0f, 0.0f);
        Math_SmoothStepToF(&player->unk_12C, 0.0f, 0.1f, 15.0f, 0.0f);
        Math_SmoothStepToF(&player->unk_034, 0.0f, 0.1f, 3.0f, 0.0f);
        Math_SmoothStepToAngle(&player->unk_4D8, 0.0f, 0.1f, 20.0f, 0.0f);
        if (gNextPlanetPath == 0) {
            if (player->pos.y < 700.0f) {
                Math_SmoothStepToF(&player->pos.y, 700.0f, 0.1f, 10.0f, 0.0f);
            }
        } else if (player->pos.y < 500.0f) {
            Math_SmoothStepToF(&player->pos.y, 500.0f, 0.1f, 5.0f, 0.0f);
        }
        func_play_800B7184(player, 0);
        player->camEye.x += player->vel.x * 0.1f;
        player->camEye.y += player->vel.y * 0.1f;
        player->camEye.z += player->vel.z * 0.1f;
    }

    player->wings.unk_04 = 0.0f;
    player->wings.unk_0C = 0.0f;
    player->wings.unk_08 = 0.0f;
    player->wings.unk_10 = 0.0f;

    Math_SmoothStepToF(&player->unk_110, 0.0f, 0.1f, 1.5f, 0.0f);

    switch (player->unk_1D0) {
        case -1:
            player->wings.unk_2C = 1;
            player->unk_0E8 = 0.0f;
            player->unk_0D0 = 30.0f;
            player->unk_114 = 180.0f;
            player->unk_0E4 = -7.0f;
            Math_SmoothStepToF(&player->unk_0EC, 0.0f, 0.05f, 1.0f, 0.0f);
            player->unk_12C = 0.0f;
            player->unk_130 = 0.0f;
            player->unk_4D8 = 0.0f;
            player->camEye.x = -200.0f;
            player->camEye.y = 100.0f;
            player->camEye.z = -1500.0f;
            player->camAt.x = player->pos.x;
            player->camAt.y = player->pos.y;
            player->camAt.z = player->unk_138;

            if (player->timer_1F8 < 80) {
                gFillScreenAlphaTarget = 255;
                gFillScreenAlphaStep = 10;
                gFillScreenGreen = gFillScreenRed = gFillScreenBlue = 0;
                if (player->timer_1F8 == 0) {
                    player->timer_1F8 = 0;
                    player->unk_1D0 = 1;
                }
            }
            break;

        case 0:
            if (gNextPlanetPath == 0) {
                Math_SmoothStepToF(&player->unk_0E8, 40.0f, 0.1f, 2.5f, 0.0f);
                Math_SmoothStepToF(&player->unk_0EC, 60.0f, 0.2f, 5.0f, 0.0f);
                Math_SmoothStepToF(&player->unk_0E4, 0.0f, 0.1f, 2.5f, 0.0f);
            } else {
                player->unk_190 = 2.0f;
                player->camEye.y += 3.0f;
                Math_SmoothStepToF(&player->unk_0EC,
                                   Math_SmoothStepToF(&player->unk_114,
                                                      Math_RadToDeg(Math_Atan2F(player->pos.x, player->unk_138)), 0.1f,
                                                      4.0f, 0.0f) *
                                       20.0f,
                                   0.2f, 5.0f, 0.0f);
                Math_SmoothStepToF(&player->unk_0E4, 0.0f, 0.1f, 2.5f, 0.0f);
            }

            if (player->timer_1F8 == 0) {
                if (gNextPlanetPath != 0) {
                    player->timer_1F8 = 150;
                    player->unk_1D0 = -1;
                    player->pos.x = 0.0f;
                    player->unk_110 = 0.0f;
                    player->unk_0D0 = 0.0f;
                    player->pos.y = 350.0f;
                    player->pos.z = -2800.0f;
                } else {
                    player->timer_1F8 = 280;
                    player->unk_1D0 = 1;
                }
                player->unk_194 = 5.0f;
                player->unk_190 = 5.0f;
                AUDIO_PLAY_SFX(0x09000002U, player->sfxSource, 0U);
            }
            break;

        case 1:
            player->unk_190 = 2.0f;
            Math_SmoothStepToF(&player->unk_0E4, 15.0f, 0.1f, 0.4f, 0.0f);
            Math_SmoothStepToF(&player->unk_0EC, -40.0f, 0.2f, 5.0f, 0.0f);
            Math_SmoothStepToF(&player->unk_0E8, -120.0f, 0.1f, 2.0f, 0.0f);
            player->unk_0D0 += 1.0f;
            if (player->unk_0D0 >= 70.0f) {
                player->unk_0D0 = 70.0f;
                player->unk_25C += 0.04f;
                if (player->unk_25C > 0.6f) {
                    player->unk_25C = 0.6f;
                }
            }
            if (player->timer_1F8 == 0) {
                player->unk_1D0 = 2;
                player->timer_1F8 = 1000;
                for (i = 0; i < ARRAY_COUNT(gActors); i++) {
                    Object_Kill(&gActors[i].obj, gActors[i].sfxSource);
                }
                //! FAKE:
                if (((&dest) && (&dest)) && (&dest)) {}

                func_8001CA24(0);
                Audio_KillSfxBySource(player->sfxSource);
                player->unk_234 = 0;
                gFillScreenAlpha = 255;
                gFillScreenAlphaTarget = 255;
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
                gFillScreenAlphaStep = 0;
            }
            break;

        case 2:
            if (!(gNextPlanetPath) && (player->timer_1F8) > 830) {
                gFillScreenAlphaTarget = 0;
                gFillScreenAlphaStep = 8;
            }
            if (player->timer_1F8 == 810) {
                Audio_KillSfxBySource(gBosses[0].sfxSource);
            }
            if (player->timer_1F8 == 830) {
                gFillScreenAlphaTarget = 255;
                gFillScreenAlphaStep = 2;
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
            }

            gBosses[0].swork[0] = 1;

            if ((func_hud_80090200(&gBosses[0]) == 2) || (gNextPlanetPath != 0)) {
                func_play_800A6148();
                if (gNextPlanetPath == 0) {
                    player->unk_1D0 = 10;
                } else {
                    player->unk_1D0 = 20;
                }

                for (i = 0; i < 200; i++) {
                    gObjects58[i].obj.status = OBJ_FREE;
                }

                func_play_800A5EBC();
                gLevelType = 1;
                D_ctx_801784AC = gBgColor = gFogRed = gFogGreen = gFogBlue = 0;
                gLight1R = gLight2R = D_ctx_80161A70 = 86;
                gLight1G = gLight2G = D_ctx_80161A74 = 58;
                gLight1B = gLight2B = D_ctx_80161A78 = 25;
                gAmbientR = 11;
                gAmbientG = 8;
                gAmbientB = 24;
                D_ctx_801784D0 = D_ctx_801784C4 = D_ctx_801784C4 = D_ctx_801784F8 = D_ctx_801784C4 = -59.0f;
                D_ctx_801784D4 = D_ctx_801784C8 = D_ctx_801784C8 = D_ctx_801784FC = D_ctx_801784C8 = 58.0f;
                D_ctx_801784D8 = D_ctx_801784CC = D_ctx_801784CC = D_ctx_80178500 = D_ctx_801784CC = 13.0f;

                if (gNextPlanetPath == 0) {
                    player->pos.x = 0.0f;
                    player->pos.y = 0.0f;
                    player->unk_0E4 = 0.0f;
                    player->unk_0EC = 0.0f;
                    player->unk_0D0 = 0.0f;
                    player->unk_114 = 0.0f;
                    player->unk_0E8 = 180.0f;
                    Fortuna_8018906C();
                } else {
                    player->pos.x = 0.0f;
                    player->unk_0E4 = 0.0f;
                    player->unk_0EC = 0.0f;
                    player->unk_114 = 0.0f;
                    player->unk_0D0 = 0.0f;
                    player->camAt.y = 16.0f;
                    player->pos.y = -100.0f;
                    player->unk_0E8 = 180.0f;
                }
                player->pos.z = -10000.0f;
                gCsFrameCount = 0;
                player->wings.unk_2C = 1;
                player->unk_204 = 1;
                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 100);
                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 100);
                func_8001C8B8(0);
                if (gNextPlanetPath == 0) {
                    Fortuna_801890EC(actor0, 3);
                }
            }
            break;

        case 10:
            player->unk_234 = 1;
            gFillScreenAlphaTarget = 0;
            gFillScreenAlphaStep = 4;
            player->camEye.x = 400.0f;
            player->camEye.y = 0;
            player->camEye.z = 0.0f;
            player->camAt.x = actor0->obj.pos.x;
            player->camAt.y = actor0->obj.pos.y;
            player->camAt.z = actor0->obj.pos.z;

            if (gCsFrameCount == 100) {
                player->unk_0D0 = 30.0f;
                if (gTeamShields[TEAM_ID_FALCO] > 0) {
                    Fortuna_801890EC(actor3, 0);
                }
                if (gTeamShields[TEAM_ID_SLIPPY] > 0) {
                    Fortuna_801890EC(actor1, 1);
                }
                if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                    Fortuna_801890EC(actor2, 2);
                }
            }

            if (gCsFrameCount == 496) {
                player->unk_1D0 = 11;
                D_ctx_80177A48[0] = 0.01f;
                D_ctx_80177A48[1] = 0.0f;
                D_ctx_80177A48[2] = -400.0f;
                D_ctx_80177A48[3] = 0.0f;
                actor3->iwork[14] = 2;
                actor1->iwork[14] = 3;
                actor2->iwork[14] = 4;
            }

            if (gCsFrameCount == 200) {
                if (gNextPlanetPath == 0) {
                    AUDIO_PLAY_BGM(SEQ_ID_BAD_END);
                } else {
                    AUDIO_PLAY_BGM(SEQ_ID_GOOD_END);
                }
            }

            if (gCsFrameCount == 420) {
                gLevelClearScreenTimer = 100;
            }
            break;

        case 11:
            D_ctx_80177A48[1] += D_ctx_80177A48[3];
            Matrix_RotateX(gCalcMatrix, -0.17453292f, 0);
            Matrix_RotateY(gCalcMatrix, D_ctx_80177A48[1] * M_DTOR, 1);
            src.x = 0;
            src.y = 0.0f;
            src.z = D_ctx_80177A48[2];
            Matrix_MultVec3f(gCalcMatrix, &src, player->jointTable);
            gCsCamEyeX = player->jointTable[0].x + player->pos.x;
            gCsCamEyeY = player->jointTable[0].y + player->pos.y;
            gCsCamEyeZ = player->jointTable[0].z + (player->pos.z - 250.0f);
            gCsCamAtX = player->pos.x;
            gCsCamAtY = player->pos.y;
            gCsCamAtZ = player->pos.z - 250.0f;

            Math_SmoothStepToF(D_ctx_80177A48, 0.05f, 1.0f, 0.001f, 0);

            Math_SmoothStepToF(&player->camEye.x, gCsCamEyeX, D_ctx_80177A48[0], 20000.0f, 0);
            Math_SmoothStepToF(&player->camEye.y, gCsCamEyeY, D_ctx_80177A48[0], 20000.0f, 0);
            Math_SmoothStepToF(&player->camEye.z, gCsCamEyeZ, D_ctx_80177A48[0], 20000.0f, 0);

            Math_SmoothStepToF(&player->camAt.x, gCsCamAtX, D_ctx_80177A48[0], 20000.0f, 0);
            Math_SmoothStepToF(&player->camAt.y, gCsCamAtY, D_ctx_80177A48[0], 20000.0f, 0);
            Math_SmoothStepToF(&player->camAt.z, gCsCamAtZ, D_ctx_80177A48[0], 20000.0f, 0);

            Math_SmoothStepToF(&player->unk_0D0, 0.0f, 0.05f, 2.0f, 0);

            Math_SmoothStepToF(&actor3->vel.z, 0.0f, 0.05f, 2.0f, 0);
            Math_SmoothStepToF(&actor1->vel.z, 0.0f, 0.05f, 2.0f, 0);
            Math_SmoothStepToF(&actor2->vel.z, 0.0f, 0.05f, 2.0f, 0);
            Math_SmoothStepToF(&actor0->vel.z, 0.0f, 0.05f, 2.0f, 0);

            if (gCsFrameCount == 500) {
                Radio_PlayMessage(gMsg_ID_20010, RCID_FOX);
            }

            if (gNextPlanetPath == 0) {
                switch (gCsFrameCount) {
                    case 588:
                        switch (gTeamShields[TEAM_ID_SLIPPY]) {
                            case -1:
                                Radio_PlayMessage(gMsg_ID_20339, RCID_ROB64);
                                break;
                            case 0:
                                Radio_PlayMessage(gMsg_ID_20345, RCID_ROB64);
                                break;
                            default:
                                Radio_PlayMessage(gMsg_ID_9425, RCID_SLIPPY);
                                break;
                        }
                        break;

                    case 735:
                        switch (gTeamShields[TEAM_ID_PEPPY]) {
                            case -1:
                                Radio_PlayMessage(gMsg_ID_20338, RCID_ROB64);
                                break;
                            case 0:
                                Radio_PlayMessage(gMsg_ID_20344, RCID_ROB64);
                                break;
                            default:
                                Radio_PlayMessage(gMsg_ID_9426, RCID_PEPPY);
                                break;
                        }
                        break;

                    case 881:
                        switch (gTeamShields[TEAM_ID_FALCO]) {
                            case -1:
                                Radio_PlayMessage(gMsg_ID_20337, RCID_ROB64);
                                break;
                            case 0:
                                Radio_PlayMessage(gMsg_ID_20340, RCID_ROB64);
                                break;
                            default:
                                Radio_PlayMessage(gMsg_ID_9427, RCID_FALCO);
                                break;
                        }
                        break;
                }
            } else {
                switch (gCsFrameCount) {
                    case 588:
                        switch (gTeamShields[TEAM_ID_SLIPPY]) {
                            case -1:
                                Radio_PlayMessage(gMsg_ID_20339, RCID_ROB64);
                                break;
                            case 0:
                                Radio_PlayMessage(gMsg_ID_20345, RCID_ROB64);
                                break;
                            default:
                                Radio_PlayMessage(gMsg_ID_9428, RCID_SLIPPY);
                                break;
                        }
                        break;

                    case 735:
                        switch (gTeamShields[TEAM_ID_PEPPY]) {
                            case -1:
                                Radio_PlayMessage(gMsg_ID_20338, RCID_ROB64);
                                break;
                            case 0:
                                Radio_PlayMessage(gMsg_ID_20344, RCID_ROB64);
                                break;
                            default:
                                Radio_PlayMessage(gMsg_ID_9429, RCID_PEPPY);
                                break;
                        }
                        break;

                    case 881:
                        switch (gTeamShields[TEAM_ID_FALCO]) {
                            case -1:
                                Radio_PlayMessage(gMsg_ID_20337, RCID_ROB64);
                                break;
                            case 0:
                                Radio_PlayMessage(gMsg_ID_20340, RCID_ROB64);
                                break;
                            default:
                                Radio_PlayMessage(gMsg_ID_9430, RCID_FALCO);
                                break;
                        }
                        break;
                }
            }

            if (gCsFrameCount < 1136) {
                Math_SmoothStepToF(&D_ctx_80177A48[3], 0.55f, 1.0f, 0.02f, 0);
            } else {
                D_ctx_80178430 += 0.3f;
                D_ctx_8017842C += 0.3f;
                Math_SmoothStepToF(&D_ctx_80177A48[3], 0.0f, 1.0f, 0.02f, 0);
                if (gCsFrameCount == 1216) {
                    player->unk_1D0 = 12;
                    player->timer_1F8 = 1000;
                    D_ctx_80177A48[4] = 1.0f;
                    actor2->vel.y = 0.1f;
                    actor1->vel.y = 0.1f;
                    AUDIO_PLAY_SFX(0x09000002U, player->sfxSource, 0U);
                    player->unk_194 = 5.0f;
                    player->unk_190 = 5.0f;
                    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 50);
                    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 50);
                }
            }
            break;

        case 12:
            D_ctx_80178430 += 0.3f;
            D_ctx_8017842C += 0.3f;
            player->unk_0D0 += 1.0f;
            player->unk_0D0 *= 1.15f;
            player->pos.y += D_ctx_80177A48[4];
            D_ctx_80177A48[4] *= 1.19f;
            player->unk_190 = 2.0f;

            if (gTeamShields[TEAM_ID_FALCO] > 0) {
                if (player->timer_1F8 == 980) {
                    AUDIO_PLAY_SFX(0x09000002U, actor3->sfxSource, 0U);
                    actor3->vel.y = 1.0f;
                    actor3->fwork[29] = 5.0f;
                }
                if (player->timer_1F8 < 980) {
                    actor3->vel.z += 1.0f;
                    actor3->vel.z *= 1.15f;
                    actor3->vel.y *= 1.19f;
                    actor3->iwork[11] = 2;
                }
            }

            if ((gTeamShields[TEAM_ID_PEPPY] > 0) && (player->timer_1F8 == 960)) {
                AUDIO_PLAY_SFX(0x09000002U, actor2->sfxSource, 0U);
                actor2->vel.y = 1.0f;
                actor2->fwork[29] = 5.0f;
            }

            if (player->timer_1F8 < 960) {
                actor2->vel.z += 1.0f;
                actor2->vel.z *= 1.15f;
                actor2->vel.y *= 1.19f;
                actor2->iwork[11] = 2;
            }

            if (gTeamShields[TEAM_ID_SLIPPY] > 0) {
                if (player->timer_1F8 == 940) {
                    AUDIO_PLAY_SFX(0x09000002U, actor1->sfxSource, 0U);
                    actor1->vel.y = 1.0f;
                    actor1->fwork[29] = 5.0f;
                }

                if (player->timer_1F8 < 940) {
                    actor1->vel.z += 1.0f;
                    actor1->vel.z *= 1.15f;
                    actor1->vel.y *= 1.19f;
                    actor1->iwork[11] = 2;
                }
            }

            if (player->timer_1F8 == 910) {
                actor0->vel.y = 1.0f;
                actor0->obj.rot.x = -2.0f;
            }

            if (player->timer_1F8 < 910) {
                actor0->vel.z += 1.0f;
                actor0->vel.z *= 1.02f;
                actor0->vel.y *= 1.06f;
                actor0->obj.rot.x *= 1.03f;
            }

            if (gCsFrameCount == 1382) {
                player->state_1C8 = PLAYERSTATE_1C8_6;
                player->timer_1F8 = 0;
                D_ctx_8017837C = 4;
                Audio_FadeOutAll(10);
                for (i = 0; i < 6; i++) {
                    gSavedStarWolfTeamAlive[i] = gStarWolfTeamAlive[i];
                }
                D_play_800D3180[LEVEL_FORTUNA] = Play_CheckMedalStatus(50) + 1;
            }
            break;

        case 20:
            if (gTeamShields[TEAM_ID_FALCO] > 0) {
                Fortuna_801890EC(actor3, 0);
                actor3->obj.pos.x = (player->pos.x - 100.0f) - 400.0f;
                actor3->obj.pos.y = player->pos.y + 400.0f;
                actor3->obj.pos.z = player->unk_138 - 150.0f;
                actor3->obj.rot.z = 90.0f;
            }
            if (gTeamShields[TEAM_ID_SLIPPY] > 0) {
                Fortuna_801890EC(actor1, 1);
                actor1->obj.pos.x = player->pos.x + 100.0f + 400.0f;
                actor1->obj.pos.y = player->pos.y + 400.0f;
                actor1->obj.pos.z = player->unk_138 - 150.0f;
                actor1->obj.rot.z = -90.0f;
            }
            if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                Fortuna_801890EC(actor2, 2);
                actor2->obj.pos.x = player->pos.x;
                actor2->obj.pos.y = player->pos.y + 100.0f + 400.0f;
                actor2->obj.pos.z = player->unk_138 - 250.0f;
            }
            Fortuna_801890EC(actor0, 3);

            actor0->obj.pos.z = player->pos.z + 400.0f;
            actor0->vel.z = 0.0f;
            actor0->info.bonus = 1;
            gCsFrameCount = 0;
            player->unk_1D0 = 21;
            player->unk_234 = 1;

            for (i = 0; i < 9; i++) {
                D_ctx_80177A48[i] = 0.0f;
            }

            D_ctx_80177A48[5] = 94.0f;
            gCsCamAtX = 0.0f;
            gCsCamAtY = 30.0f;
            gCsCamAtZ = 0.0f;

        case 21:
            if (gCsFrameCount < 30) {
                break;
            }

            if (gFillScreenAlpha != 0) {
                gFillScreenAlphaTarget = 0;
                gFillScreenAlphaStep = 1;
            }

            if (gCsFrameCount == 140) {
                player->unk_0D0 = 30.0f;
                actor3->vel.z = 30.0f;
                actor1->vel.z = 30.0f;
                actor2->vel.z = 30.0f;
                actor0->vel.z = 30.0f;
            }
            if (gCsFrameCount > 140) {
                Math_SmoothStepToF(&actor3->obj.rot.z, 0.0f, 0.03f, 1.2f, 0.0001f);
                Math_SmoothStepToF(&actor3->obj.pos.x, -100.0f, 0.03f, 1000.0f, 0.0001f);
                Math_SmoothStepToF(&actor3->obj.pos.y, 40.0f, 0.03f, 1000.0f, 0.0001f);
            }
            if (gCsFrameCount > 180) {
                Math_SmoothStepToF(&actor1->obj.rot.z, 0.0f, 0.03f, 1.2f, 0.0001f);
                Math_SmoothStepToF(&actor1->obj.pos.x, 100.0f, 0.03f, 1000.0f, 0.0001f);
                Math_SmoothStepToF(&actor1->obj.pos.y, 40.0f, 0.03f, 1000.0f, 0.0001f);
            }
            if (gCsFrameCount > 220) {
                Math_SmoothStepToF(&actor2->obj.pos.y, 90.0f, 0.03f, 1000.0f, 0.0001f);
            }
            if (gCsFrameCount > 340) {
                Math_SmoothStepToF(&player->pos.y, -10.0f, 0.03f, 1000.0f, 0.0001f);
            }
            if (gCsFrameCount > 530) {
                Radio_PlayMessage(gMsg_ID_20010, RCID_FOX);
                player->pos.y = -10.0f;
                actor3->obj.rot.z = 0.0f;
                actor3->obj.pos.x = -100.0f;
                actor3->obj.pos.y = 40.0f;
                actor1->obj.rot.z = 0.0f;
                actor1->obj.pos.x = 100.0f;
                actor1->obj.pos.y = 40.0f;
                actor2->obj.pos.y = 90.0f;
                player->unk_1D0 = 22;
            }

            switch (gCsFrameCount) {
                case 140:
                    AUDIO_PLAY_BGM(SEQ_ID_GOOD_END);
                    break;
                case 450:
                    gLevelClearScreenTimer = 100;
                    break;
            }
            src.x = 0.0f;
            src.y = D_ctx_80177A48[7];
            src.z = D_ctx_80177A48[5];
            Matrix_Translate(gCalcMatrix, player->pos.x, 0.0f, player->pos.z + D_ctx_80177D20, 0);
            Matrix_RotateY(gCalcMatrix, -(D_ctx_80177A48[4] * M_DTOR), 1);
            Matrix_MultVec3f(gCalcMatrix, &src, &dest);
            player->camEye.x = gCsCamEyeX = dest.x;
            player->camEye.y = gCsCamEyeY = dest.y;
            player->camEye.z = gCsCamEyeZ = dest.z;
            Math_SmoothStepToF(&gCsCamAtY, 0.0f, 0.005f, 1000.0f, 0.0001f);
            player->camAt.x = player->pos.x;
            player->camAt.y = gCsCamAtY;
            player->camAt.z = player->pos.z + D_ctx_80177D20;
            break;

        case 22:
            if ((gCsFrameCount >= 1110) && (gCsFrameCount < 1240)) {
                Math_SmoothStepToF(&player->unk_0D0, 0.0f, 0.02f, 1000.0f, 0.001f);
                Math_SmoothStepToF(&actor3->vel.z, 0.0f, 0.02f, 1000.0f, 0.001f);
                Math_SmoothStepToF(&actor1->vel.z, 0.0f, 0.02f, 1000.0f, 0.001f);
                Math_SmoothStepToF(&actor2->vel.z, 0.0f, 0.02f, 1000.0f, 0.001f);
                Math_SmoothStepToF(&actor0->vel.z, 0.0f, 0.02f, 1000.0f, 0.001f);
            }
            if (gCsFrameCount == 1239) {
                player->unk_0D0 = 0.0f;
                actor3->vel.z = 0.0f;
                actor1->vel.z = 0.0f;
                actor2->vel.z = 0.0f;
                actor0->vel.z = 0.0f;
            }

            switch (gCsFrameCount) {
                case 618:
                    switch (gTeamShields[TEAM_ID_SLIPPY]) {
                        case -1:
                            Radio_PlayMessage(gMsg_ID_20339, RCID_ROB64);
                            break;
                        case 0:
                            Radio_PlayMessage(gMsg_ID_20345, RCID_ROB64);
                            break;
                        default:
                            Radio_PlayMessage(gMsg_ID_9428, RCID_SLIPPY);
                            break;
                    }
                    break;

                case 765:
                    switch (gTeamShields[TEAM_ID_PEPPY]) {
                        case -1:
                            Radio_PlayMessage(gMsg_ID_20338, RCID_ROB64);
                            break;
                        case 0:
                            Radio_PlayMessage(gMsg_ID_20344, RCID_ROB64);
                            break;
                        default:
                            Radio_PlayMessage(gMsg_ID_9429, RCID_PEPPY);
                            break;
                    }
                    break;

                case 911:
                    switch (gTeamShields[TEAM_ID_FALCO]) {
                        case -1:
                            Radio_PlayMessage(gMsg_ID_20337, RCID_ROB64);
                            break;
                        case 0:
                            Radio_PlayMessage(gMsg_ID_20340, RCID_ROB64);
                            break;
                        default:
                            Radio_PlayMessage(gMsg_ID_9430, RCID_FALCO);
                            break;
                    }
                    break;

                case 1080:
                    D_ctx_80177830 = 1;
                    break;

                case 1240:
                    if (gTeamShields[TEAM_ID_FALCO] > 0) {
                        AUDIO_PLAY_SFX(0x09000002U, actor3->sfxSource, 0U);
                        actor3->fwork[29] = 5.0f;
                        actor3->iwork[11] = 2;
                    }
                    break;

                case 1260:
                    if (gTeamShields[TEAM_ID_SLIPPY] > 0) {
                        AUDIO_PLAY_SFX(0x09000002U, actor1->sfxSource, 0U);
                        actor1->fwork[29] = 5.0f;
                        actor1->iwork[11] = 2;
                    }
                    break;

                case 1280:
                    if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                        AUDIO_PLAY_SFX(0x09000002U, actor2->sfxSource, 0U);
                        actor2->fwork[29] = 5.0f;
                        actor2->iwork[11] = 2;
                    }
                    D_ctx_80177830 = 0;
                    break;

                case 1300:
                    AUDIO_PLAY_SFX(0x09000002U, player->sfxSource, 0U);
                    player->unk_190 = 2.0f;
                    player->unk_194 = 5.0f;
                    break;

                case 1350:
                    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 50);
                    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 50);
                    break;
            }

            if ((gCsFrameCount >= 1400)) {
                gFillScreenAlphaTarget = 255;
                gFillScreenAlphaStep = 16;
                if (gFillScreenAlpha == 255) {
                    player->state_1C8 = PLAYERSTATE_1C8_6;
                    player->timer_1F8 = 0;
                    D_ctx_8017837C = 4;
                    Audio_FadeOutAll(10);

                    // clang-format off
                    for (i = 0; i < 6; i++) { \
                        gSavedStarWolfTeamAlive[i] = gStarWolfTeamAlive[i];
                    }
                    // clang-format on

                    D_play_800D3180[LEVEL_FORTUNA] = Play_CheckMedalStatus(50) + 1;
                    func_play_800A6148();
                    break;
                }
            }

            if (gCsFrameCount > 1060) {
                Math_SmoothStepToF(D_ctx_80177A48, 300.0f, 0.02f, 1000.0f, 0.001f);
                Math_SmoothStepToF(&D_ctx_80177A48[1], -100.0f, 0.02f, 1000.0f, 0.001f);
            } else if (gCsFrameCount > 770) {
                Math_SmoothStepToF(D_ctx_80177A48, 600.0f, 0.02f, 1000.0f, 0.001f);
            } else {
                Math_SmoothStepToF(D_ctx_80177A48, 400.0f, 0.03f, 1000.0f, 0.001f);
            }

            Math_SmoothStepToF(&D_ctx_80177A48[5], D_ctx_80177A48[0], 0.01f, 1000.0f, 0.001f);
            Math_SmoothStepToF(&D_ctx_80177A48[7], D_ctx_80177A48[1], 0.01f, 1000.0f, 0.001f);

            if (gCsFrameCount > 1060) {
                Math_SmoothStepToF(&D_ctx_80177A48[2], -70.0f, 0.05f, 1000.0f, 0.001f);
            } else if (gCsFrameCount < 770) {
                Math_SmoothStepToF(&D_ctx_80177A48[2], 100.0f, 0.05f, 1000.0f, 0.001f);
            }

            Math_SmoothStepToF(&D_ctx_80177A48[6], D_ctx_80177A48[2], 0.01f, 1000.0f, 0.001f);

            if (gCsFrameCount < 1180) {
                Math_SmoothStepToF(&D_ctx_80177A48[8], 0.41f, 0.01f, 10.0f, 0.001f);
            } else {
                Math_SmoothStepToF(&D_ctx_80177A48[8], 0.0f, 0.001f, 1.0f, 0.0001f);
            }

            D_ctx_80177A48[4] += D_ctx_80177A48[8];

            if (D_ctx_80177A48[4] >= 360.0f) {
                D_ctx_80177A48[4] = D_ctx_80177A48[4] - 360.0f;
            }

            if (D_ctx_80177A48[4] < 0.0f) {
                D_ctx_80177A48[4] = D_ctx_80177A48[4] + 360.0f;
            }

            if (gCsFrameCount < 1300) {
                src.x = 0.0f;
                src.y = D_ctx_80177A48[7];
                src.z = D_ctx_80177A48[5];
                Matrix_Translate(gCalcMatrix, player->pos.x, 0.0f, player->pos.z + D_ctx_80177D20, 0);
                Matrix_RotateY(gCalcMatrix, -(D_ctx_80177A48[4] * M_DTOR), 1);
                Matrix_MultVec3f(gCalcMatrix, &src, &dest);
                player->camEye.x = gCsCamEyeX = dest.x;
                player->camEye.y = gCsCamEyeY = dest.y;
                player->camEye.z = gCsCamEyeZ = dest.z;
            }

            if (gCsFrameCount >= 1240) {
                Math_SmoothStepToF(&actor3->vel.z, 50.0f, 0.1f, 1000.0f, 0.001f);
            }
            if (gCsFrameCount >= 1260) {
                Math_SmoothStepToF(&actor1->vel.z, 50.0f, 0.1f, 1000.0f, 0.001f);
            }
            if (gCsFrameCount >= 1280) {
                Math_SmoothStepToF(&actor2->vel.z, 50.0f, 0.1f, 1000.0f, 0.001f);
            }
            if (gCsFrameCount >= 1300) {
                Math_SmoothStepToF(&player->unk_0D0, 50.0f, 0.1f, 1000.0f, 0.001f);
                Math_SmoothStepToF(&actor0->vel.z, 40.0f, 0.1f, 1000.0f, 0.001f);
            }
            Math_SmoothStepToF(&gCsCamAtY, player->pos.y, 0.005f, 1000.0f, 0.0001f);

            player->camAt.x = gCsCamAtX = player->pos.x;
            player->camAt.y = gCsCamAtY;
            player->camAt.z = gCsCamAtZ = player->pos.z - D_ctx_80177A48[6] + D_ctx_80177D20;
            break;
    }

    if (player->unk_1D0 < 20) {
        switch (gCsFrameCount) {
            case 1020:
                D_ctx_80177830 = 1;
                break;
            case 1220:
                D_ctx_80177830 = 0;
                break;
        }
    }

    Matrix_RotateY(gCalcMatrix, (player->unk_114 + player->unk_0E8 + 180.0f) * M_DTOR, 0);
    Matrix_RotateX(gCalcMatrix, -((player->unk_120 + player->unk_0E4 + player->unk_4D8) * M_DTOR), 1);

    src.x = 0.0f;
    src.y = 0.0f;
    src.z = player->unk_0D0 + player->unk_110;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

    player->vel.x = dest.x;
    player->vel.z = dest.z;
    player->vel.y = dest.y;
    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;
    player->pos.z += player->vel.z;
    player->unk_138 = player->pos.z;
    player->unk_0F8 = player->unk_0EC + player->unk_12C + player->unk_130;
}

void Fortuna_8018BA2C(void) {
    s32 i;
    Actor* actor;
    Sprite* sprite;
    Object_58* obj58;
    Boss* boss = &gBosses[0];

    gLevelObjects = LOAD_ASSET(gLevelObjectInits[gCurrentLevel]);

    for (obj58 = &gObjects58[0], i = 0; i < 1000; i++) {
        if (gLevelObjects[i].id < 0) {
            break;
        }
        if (gLevelObjects[i].id < 161) {
            Object_58_Initialize(obj58);
            obj58->obj.status = OBJ_ACTIVE;
            obj58->obj.id = gLevelObjects[i].id;
            obj58->obj.pos.x = gLevelObjects[i].xPos;
            obj58->obj.pos.z = gLevelObjects[i].zPos1;
            obj58->obj.pos.y = gLevelObjects[i].yPos;
            obj58->obj.rot.y = gLevelObjects[i].rot.y;
            Object_SetInfo(&obj58->info, obj58->obj.id);
            obj58++;
        }
    }

    for (actor = &gActors[20], i = 0; i < 1000; i++) {
        if (gLevelObjects[i].id < 0) {
            break;
        }
        if ((gLevelObjects[i].id >= OBJ_ACTOR_176) && (gLevelObjects[i].id < OBJ_BOSS_292)) {
            Actor_Initialize(actor);
            actor->obj.status = OBJ_INIT;
            actor->obj.id = gLevelObjects[i].id;
            actor->obj.pos.x = gLevelObjects[i].xPos;
            actor->obj.pos.z = gLevelObjects[i].zPos1;
            actor->obj.pos.y = gLevelObjects[i].yPos;
            Object_SetInfo(&actor->info, actor->obj.id);
            actor++;
        }
    }

    for (sprite = &gSprites[0], i = 0; i < 1000; i++) {
        if (gLevelObjects[i].id < 0) {
            break;
        }
        if (gLevelObjects[i].id == 163) {
            Sprite_Initialize(sprite);
            sprite->obj.status = OBJ_INIT;
            sprite->obj.id = gLevelObjects[i].id;
            sprite->obj.pos.x = gLevelObjects[i].xPos;
            sprite->obj.pos.z = gLevelObjects[i].zPos1;
            sprite->obj.pos.y = gLevelObjects[i].yPos;
            Object_SetInfo(&sprite->info, sprite->obj.id);
            sprite++;
        }
    }
    Boss_Initialize(boss);
    boss->obj.status = OBJ_INIT;
    boss->obj.pos.x = 0.0f;
    boss->obj.pos.y = 0.0f;
    boss->obj.pos.z = 0.0f;
    boss->obj.id = OBJ_BOSS_308;
    Object_SetInfo(&boss->info, boss->obj.id);
}
