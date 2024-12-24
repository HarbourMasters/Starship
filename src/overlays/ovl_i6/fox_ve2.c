/*
 * File: fox_ve2.c
 * System: Venom2
 * Description: Level: Venom 2
 */

#include "global.h"
#include "assets/ast_venom_2.h"

void Venom2_Ve2Base_Update(Ve2Base* this) {
    Math_SmoothStepToF(&this->fwork[0], this->fwork[1], 0.5f, 5.0f, 0.0f);
}

bool Venom2_Ve2Base_OverrideLimbDraw(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    Ve2Base* this = (Ve2Base*) thisx;

    if ((limbIndex == 1) || (limbIndex == 2)) {
        pos->x -= this->fwork[0];
    }

    return false;
}

void Venom2_Ve2Base_Draw(Ve2Base* this) {
    Animation_GetFrameData(&aVe2BaseAnim, 0, this->vwork);
    Animation_DrawSkeleton(3, aVe2BaseSkel, this->vwork, Venom2_Ve2Base_OverrideLimbDraw, NULL, this, gCalcMatrix);
}

void Venom2_UpdateStarWolfEvents(ActorAllRange* this) {
    ActorAllRange_UpdateStarWolfEvents(this);
}

Vec3f sTeamInitPos[6] = {
    { 0.0f, 4030.0f, 18000.0f }, { -500.0f, 3820.0f, 17200.0f }, { 550.0f, 3750.0f, 17000.0f },
    { 1000.0f, 300.0f, 0.0f },   { -1000.0f, 300.0f, 0.0f },     { 0.0f, 500.0f, 0.0f },
};

f32 sTeamInitRot[3] = { 300.0f, 70.0f, 280.0f };

void Venom2_UpdateEvents(ActorAllRange* this) {
    ActorAllRange* team;
    ActorAllRange* wolf = &gActors[4];
    Player* player = &gPlayer[0];
    s32 i;

    switch (this->state) {
        case 0:
            gAllRangeEventTimer = 0;
            gStarWolfMsgTimer = 0;

            for (i = 0; i < 6; i++) {
                gSavedStarWolfTeamAlive[i] = 1;
                gStarWolfTeamAlive[i] = 1;
            }

            if (player->state == PLAYERSTATE_ACTIVE) {
                this->state = 2;
                player->pos.x = 0.0f;
                player->pos.z = 8000.0f;
                player->pos.y = 670.0f;
                gAllRangeSpawnEvent = 120;
                gStarWolfMsgTimer = 1000;
            } else {
                gAllRangeSpawnEvent = 320;
                gStarWolfMsgTimer = 1200;

                this->state = 1;

                player->pos.x = 0.0f;
                player->pos.z = 16000.0f;
                player->pos.y = 4350.0f;
                player->rot.x = -20.0f;
                player->yRot_114 = 0.0f;

                this->timer_0BC = 210;

                for (team = &gActors[AI360_FALCO], i = AI360_FALCO; i <= AI360_PEPPY; i++, team++) {
                    team->obj.pos.x = sTeamInitPos[i - 1].x;
                    team->obj.pos.y = sTeamInitPos[i - 1].y + 750.f;
                    team->obj.pos.z = sTeamInitPos[i - 1].z;
                    team->obj.rot.z = sTeamInitRot[i - 1];
                    team->rot_0F4.x = 340.0f;
                }

                gFillScreenAlpha = gFillScreenAlphaTarget = 255;
            }
            Camera_UpdateArwing360(player, true);
            /* fallthrough */
        case 1:
            for (team = &gActors[1], i = 1; i < 4; i++, team++) {
                team->state = 0;
                team->timer_0BC = 3;
                if (this->timer_0BC == 0) {
                    team->state = 2;
                    this->state = 2;
                    player->state = PLAYERSTATE_ACTIVE;
                    player->unk_014 = 0.0001f;
                    gLevelStartStatusScreenTimer = 80;
                }
            }
            if (gAllRangeEventTimer == 80) {
                Radio_PlayMessage(gMsg_ID_19010, RCID_FOX);
            }
            break;

        case 2:
            Venom2_UpdateStarWolfEvents(this);
            if (((gAllRangeSpawnEvent + 100) < gAllRangeEventTimer) && (gActors[4].obj.status == OBJ_FREE) &&
                (gActors[5].obj.status == OBJ_FREE) && (gActors[6].obj.status == OBJ_FREE) &&
                (gActors[7].obj.status == OBJ_FREE) && (this->timer_0BE == 0)) {
                this->timer_0BE = 80;
            }

            if ((this->timer_0BE == 1) && (player->state != PLAYERSTATE_LEVEL_COMPLETE)) {
                for (i = 1; i < ARRAY_COUNT(gTeamShields); i++) {
                    gPrevPlanetTeamShields[i] = gSavedTeamShields[i];
                    gPrevPlanetSavedTeamShields[i] = gSavedTeamShields[i];
                    gSavedTeamShields[i] = gTeamShields[i];
                }

                player->state = PLAYERSTATE_LEVEL_COMPLETE;
                player->csState = 0;
                gLeveLClearStatus[gCurrentLevel] = 2;
                D_ctx_80177C94 = gGoldRingCount[0];
                D_ctx_80177C9C = player->shields + 1;
                D_play_80161A5C = D_ctx_80177CA4 = gHitCount;
                D_ctx_80177CAC = player->arwing.rightWingState;
                D_ctx_80177CB4 = player->arwing.leftWingState;
                D_ctx_80177CBC = gRightWingHealth[0];
                D_ctx_80177CC4 = gLeftWingHealth[0];
            }
            break;

        case 3:
            gPauseEnabled = false;
            if (gStarWolfMsgTimer < 600) {
                player->cam.eye.x += wolf->vel.x * 0.23f;
                player->cam.eye.y += wolf->vel.y * 0.23f;
                player->cam.eye.z += wolf->vel.z * 0.23f;
            }
            Math_SmoothStepToF(&player->cam.at.x, wolf->obj.pos.x, 1.0f, 20000.0f, 0.0f);
            Math_SmoothStepToF(&player->cam.at.y, wolf->obj.pos.y, 1.0f, 20000.0f, 0.0f);
            Math_SmoothStepToF(&player->cam.at.z, wolf->obj.pos.z, 1.0f, 20000.0f, 0.0f);
            Math_SmoothStepToF(&player->camRoll, 0, 0.1f, 0.2f, 0.0f);

            if ((gControllerPress->button & START_BUTTON) || (gAllRangeEventTimer == (gAllRangeSpawnEvent + 300))) {
                this->state = 2;
                player->state = PLAYERSTATE_ACTIVE;
                Camera_Update360(player, true);
                player->unk_014 = 0.0f;
                D_hud_80161708 = 0;
            }
            break;
    }

    if (gStarWolfMsgTimer != 0) {
        gStarWolfMsgTimer--;

        switch (gStarWolfMsgTimer) {
            case 860:
                Radio_PlayMessage(gMsg_ID_19200, RCID_WOLF);
                break;
            case 760:
                Radio_PlayMessage(gMsg_ID_19210, RCID_LEON);
                break;
            case 620:
                Radio_PlayMessage(gMsg_ID_19220, RCID_PIGMA);
                break;
            case 480:
                Radio_PlayMessage(gMsg_ID_19230, RCID_ANDREW);
                break;
            case 350:
                Radio_PlayMessage(gMsg_ID_19240, RCID_FOX);
                break;
            case 220:
                Radio_PlayMessage(gMsg_ID_19250, RCID_FALCO);
                break;
        }
    }
}

void Venom2_LoadLevelObjects(void) {
    Actor* actor;
    Boss* boss;
    Scenery360* scenery360;
    s32 i;

    gLevelObjects = SEGMENTED_TO_VIRTUAL(gLevelObjectInits[gCurrentLevel]);

    for (scenery360 = gScenery360, i = 0; i < 1000; i++) {
        if (gLevelObjects[i].id <= OBJ_INVALID) {
            break;
        }

        if (gLevelObjects[i].id < OBJ_SCENERY_MAX) {
            Scenery360_Initialize(scenery360);
            scenery360->obj.status = OBJ_ACTIVE;
            scenery360->obj.id = gLevelObjects[i].id;
            scenery360->sfxSource[0] = scenery360->obj.pos.x = gLevelObjects[i].xPos;
            scenery360->sfxSource[1] = scenery360->obj.pos.y = gLevelObjects[i].yPos;
            scenery360->sfxSource[2] = scenery360->obj.pos.z = -gLevelObjects[i].zPos1;
            scenery360->unk_54 = scenery360->obj.rot.y = gLevelObjects[i].rot.y;

            Object_SetInfo(&scenery360->info, scenery360->obj.id);

            scenery360++;
        }
    }

    for (actor = &gActors[30], i = 0; i < 1000; i++) {
        if (gLevelObjects[i].id <= OBJ_INVALID) {
            break;
        }

        if ((gLevelObjects[i].id >= OBJ_ACTOR_START) && (gLevelObjects[i].id < OBJ_ACTOR_MAX)) {
            Actor_Initialize(actor);
            actor->obj.status = OBJ_INIT;
            actor->obj.id = gLevelObjects[i].id;
            actor->fwork[10] = actor->obj.pos.x = gLevelObjects[i].xPos;
            actor->fwork[11] = actor->obj.pos.y = gLevelObjects[i].yPos;
            actor->fwork[12] = actor->obj.pos.z = -gLevelObjects[i].zPos1;
            actor->fwork[13] = actor->obj.rot.y = gLevelObjects[i].rot.y;
            Object_SetInfo(&actor->info, actor->obj.id);
            actor++;
        }
    }
    boss = &gBosses[0];
    Boss_Initialize(boss);
    boss->obj.status = OBJ_INIT;
    boss->obj.id = OBJ_BOSS_VE2_BASE;
    Object_SetInfo(&boss->info, boss->obj.id);
}

void Venom2_LevelStart(Player* player) {
    Vec3f vec;
    Vec3f vel;
    f32 temp_fv0;

    if (gCsFrameCount > 50) {
        gFillScreenAlphaStep = 3;
        gFillScreenAlphaTarget = 0;
    }
    Matrix_RotateY(gCalcMatrix, (player->yRot_114 + player->rot.y + 180.0f) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -((player->xRot_120 + player->rot.x + player->aerobaticPitch) * M_DTOR), MTXF_APPLY);
    vec.x = 0.0f;
    vec.y = 0.0f;
    vec.z = player->baseSpeed + player->boostSpeed;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &vec, &vel);
    player->vel.x = vel.x;
    player->vel.z = vel.z;
    player->vel.y = vel.y;
    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;
    player->pos.z += player->vel.z;

    player->bankAngle = player->rot.z + player->zRotBank + player->zRotBarrelRoll;
    player->trueZpos = player->pos.z;
    player->cam.eye.x = 50.0f;
    player->cam.eye.y = 1800.0f;
    player->cam.eye.z = 9000.0f;
    player->cam.at.x = player->pos.x;
    player->cam.at.y = player->pos.y;
    player->cam.at.z = player->pos.z;
}

void Venom2_LevelComplete(Player* player) {
    s32 i;
    s32 pad;
    f32 sp94;
    f32 sp90;
    f32 sp8C;
    f32 pad88;
    f32 sp84;
    f32 pad80;
    f32 var_fa0;
    f32 temp_fv1;
    f32 sp74;
    f32 sp70;
    Vec3f sp64;
    Vec3f sp58;
    s32 pad2;

    Math_SmoothStepToF(&player->boostSpeed, 0.0f, 0.1f, 1.5f, 0.0f);
    Math_SmoothStepToF(&player->rot.y, 0.0f, 0.1f, 1.5f, 0.0f);
    Math_SmoothStepToF(&player->rot.x, 0.0f, 0.1f, 1.5f, 0.0f);

    var_fa0 = -player->xRot_120;
    temp_fv1 = player->rot.z;

    if (var_fa0 < -90.0f) {
        var_fa0 = 0.0f;
    }

    sp74 = sp70 = 0.0f;

    if (temp_fv1 < -5.0f) {
        sp74 = -temp_fv1;
    }

    if (temp_fv1 > 5.0f) {
        sp70 = temp_fv1;
    }

    Math_SmoothStepToF(&player->arwing.upperRightFlapYrot, -var_fa0 + sp74, 0.1f, 100.0f, 0.0f);
    Math_SmoothStepToF(&player->arwing.bottomRightFlapYrot, -var_fa0 - sp74, 0.1f, 100.0f, 0.0f);
    Math_SmoothStepToF(&player->arwing.upperLeftFlapYrot, -var_fa0 + sp70, 0.1f, 100.0f, 0.0f);
    Math_SmoothStepToF(&player->arwing.bottomLeftFlapYrot, -var_fa0 - sp70, 0.1f, 100.0f, 0.0f);
    sp94 = player->pos.x - gBosses[0].obj.pos.x;
    sp90 = player->pos.y - (gBosses[0].obj.pos.y + 700.0f);
    sp8C = player->pos.z - gBosses[0].obj.pos.z;

    switch (player->csState) {
        case 0:
            player->csState++;
            player->arwing.upperRightFlapYrot = player->arwing.upperLeftFlapYrot = player->arwing.bottomRightFlapYrot =
                player->arwing.bottomLeftFlapYrot = 0.0f;
            player->arwing.drawFace = true;

            D_ctx_80177A48[0] = 0.0f;
            D_ctx_80177A48[1] = 0.1f;
            D_ctx_80177A48[3] = 0.0f;
            D_ctx_80177A48[4] = 0.0f;

            player->csTimer = 0;

            if ((fabsf(sp94) < 4000.0f) && (fabsf(sp8C) < 4000.0f)) {
                player->csTimer = 250;
                sp64.x = 0.0f;
                sp64.y = 0.0f;
                sp64.z = 5000.0f;
                Matrix_RotateY(gCalcMatrix, player->yRot_114, MTXF_NEW);
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp64, &sp58);
                D_ctx_80177A48[5] = sp58.x;
                D_ctx_80177A48[6] = sp58.z;
            }
            if (gLevelPhase == 2) {
                player->csEventTimer = 240;
            } else {
                player->csEventTimer = 180;
            }
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 60);
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 60);
            /* fallthrough */
        case 1:
            if (gLevelPhase == 2) {
                gFillScreenAlphaStep = 2;
                gFillScreenAlphaTarget = 0;
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
            }

            Math_SmoothStepToF(&D_ctx_80177A48[1], 0.8f, 1.0f, 0.05f, 0.0f);
            Math_SmoothStepToF(&player->zRotBank, 0.0f, 0.1f, 15.0f, 0.0f);
            if (player->csTimer == 1) {
                D_ctx_80177A48[4] = 0.0f;
            }
            if (player->csTimer != 0) {
                sp94 = player->pos.x - (gBosses[0].obj.pos.x + D_ctx_80177A48[5]);
                sp90 = player->pos.y - (gBosses[0].obj.pos.y + 700.0f);
                sp8C = player->pos.z - (gBosses[0].obj.pos.z + D_ctx_80177A48[6]);
            }

            sp84 = Math_RadToDeg(Math_Atan2F(sp94, sp8C));
            sp8C = sqrtf(SQ(sp94) + SQ(sp8C));
            pad88 = Math_RadToDeg(-Math_Atan2F(sp90, sp8C));
            Math_SmoothStepToAngle(&player->xRot_120, pad88, 0.1f, D_ctx_80177A48[4], 0.0f);
            pad80 = Math_SmoothStepToAngle(&player->yRot_114, sp84, 0.1f, D_ctx_80177A48[4], 0.0f) * 20.0f;
            Math_SmoothStepToF(&player->rot.z, pad80, 0.1f, 3.0f, 0.0f);
            Math_SmoothStepToF(&D_ctx_80177A48[4], 3.0f, 1.0f, 0.1f, 0.0f);
            Matrix_RotateX(gCalcMatrix, -(D_PI / 9), MTXF_NEW);
            Matrix_RotateY(gCalcMatrix, (D_ctx_80177A48[3] + player->yRot_114) * M_DTOR, MTXF_APPLY);
            D_ctx_80177A48[3] += 1.0f;

            sp64.x = 0.0f;
            sp64.y = 0.0f;
            sp64.z = 400.0f;

            Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp64, &sp58);

            gCsCamEyeX = player->pos.x + sp58.x;
            gCsCamEyeY = player->pos.y + sp58.y;
            gCsCamEyeZ = player->pos.z + sp58.z;

            Math_SmoothStepToF(D_ctx_80177A48, 0.5f, 1.0f, 0.01f, 0.0f);
            Math_SmoothStepToF(&player->camRoll, 0.0f, 0.1f, 3.0f, 0.0f);
            if ((player->csTimer == 0) && (fabsf(sp94) < 50.0f) && (fabsf(sp8C) < 50.0f)) {
                player->csState++;
                D_ctx_80177A48[2] = 0.75f;
                D_ctx_80177A48[3] = 0.0f;
                D_ctx_80177A48[4] = 0.0f;

                if (player->xRot_120 >= 180.0f) {
                    player->xRot_120 -= 360.0f;
                }
                AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, player->sfxSource, 0);
                player->unk_194 = 5.0f;
                player->unk_190 = 5.0f;
                gCsFrameCount = 0;
                Audio_SetBgmParam(0);
            }
            break;

        case 2:
            player->unk_190 = 2.0f;

            Math_SmoothStepToF(&player->xRot_120, 270.0f, 0.1f, D_ctx_80177A48[2], 0.0f);
            Math_SmoothStepToF(&D_ctx_80177A48[2], 4.0f, 1.0f, 0.05f, 0.0f);

            if (player->xRot_120 > 80.0f) {
                Math_SmoothStepToF(&player->zRotBank, 10000.0f, 0.1f, 8.0f, 0.0f);
            }
            if (player->xRot_120 > 250.0f) {
                Math_SmoothStepToF(&player->pos.x, 0.0f, 0.3f, D_ctx_80177A48[3], 0.0f);
                Math_SmoothStepToF(&player->pos.z, 0.0f, 0.3f, D_ctx_80177A48[3], 0.0f);
                Math_SmoothStepToF(&D_ctx_80177A48[3], 30.0f, 1.0f, 1.0f, 0.0f);
            }
            if (player->xRot_120 > 200.0f) {
                Math_SmoothStepToF(&D_ctx_80177A48[4], 20.0f, 1.0f, 1.0f, 0.0f);
                Math_SmoothStepToF(&gCsCamEyeX, player->pos.x, 0.1f, D_ctx_80177A48[4], 0.0f);
                Math_SmoothStepToF(&gCsCamEyeY, player->pos.y + 200.0f, 0.1f, D_ctx_80177A48[4], 0.0f);
                Math_SmoothStepToF(&gCsCamEyeZ, player->pos.z, 0.1f, D_ctx_80177A48[4], 0.0f);
            } else {
                Math_SmoothStepToF(&gCsCamEyeY, player->pos.y, 0.1f, 2.0f, 0.0f);
            }

            if (gCsFrameCount == 105) {
                AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, player->sfxSource, 0);
                player->unk_194 = 5.0f;
                player->unk_190 = 5.0f;
            }
            if (gCsFrameCount > 110) {
                gFillScreenAlphaTarget = 255;
                gFillScreenAlphaStep = 8;
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
                if (gFillScreenAlpha == 255) {

                    for (i = 1; i < ARRAY_COUNT(gTeamShields); i++) {
                        gPrevPlanetTeamShields[i] = gSavedTeamShields[i];
                        gPrevPlanetSavedTeamShields[i] = gSavedTeamShields[i];
                        gSavedTeamShields[i] = gTeamShields[i];
                    }

                    gNextGameState = GSTATE_PLAY;
                    gNextLevel = LEVEL_VENOM_ANDROSS;
                    if (gLeveLClearStatus[gCurrentLevel] != 0) {
                        gNextLevelPhase = 1;
                    }
                    Audio_StopPlayerNoise(0);
                    Audio_KillSfxBySource(player->sfxSource);

                    for (i = 0; i < 200; i++) {
                        gScenery360[i].obj.status = OBJ_FREE;
                    }
                }
            }
            if (gCsFrameCount > 110) {
                gBosses[0].fwork[1] = 150.0f;
            }
            break;
    }
    if (player->csEventTimer == 150) {
        Radio_PlayMessage(gMsg_ID_8215, RCID_FOX);
        AUDIO_PLAY_BGM(NA_BGM_DASH_INTO_BASE);
    }
    if (player->csEventTimer == 1) {
        if ((gTeamShields[TEAM_ID_SLIPPY] > 0) || (gTeamShields[TEAM_ID_FALCO] > 0) ||
            (gTeamShields[TEAM_ID_PEPPY] > 0)) {
            Radio_PlayMessage(gMsg_ID_8230, RCID_FALCO);
            Radio_PlayMessage(gMsg_ID_8220, RCID_PEPPY);
            Radio_PlayMessage(gMsg_ID_8240, RCID_SLIPPY);
        } else {
            Radio_PlayMessage(gMsg_ID_8205, RCID_FOX);
        }
    }
    gCsCamAtX = player->pos.x;
    gCsCamAtY = player->pos.y;
    gCsCamAtZ = player->trueZpos;

    Matrix_RotateY(gCalcMatrix, (player->yRot_114 + player->rot.y + 180.0f) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -((player->xRot_120 + player->rot.x + player->aerobaticPitch) * M_DTOR), MTXF_APPLY);

    sp64.x = 0.0f;
    sp64.y = 0.0f;

    sp64.z = player->baseSpeed + player->boostSpeed;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp64, &sp58);

    player->vel.x = sp58.x;
    player->vel.z = sp58.z;
    player->vel.y = sp58.y;
    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;
    player->pos.z += player->vel.z;
    player->trueZpos = player->pos.z;
    player->bankAngle = player->rot.z + player->zRotBank + player->zRotBarrelRoll;

    Math_SmoothStepToF(&player->zRotBarrelRoll, 0.0f, 0.1f, 15.0f, 0.0f);
    Math_SmoothStepToAngle(&player->aerobaticPitch, 0.0f, 0.1f, 5.0f, 0.0f);

    Math_SmoothStepToF(&player->cam.eye.x, gCsCamEyeX, D_ctx_80177A48[0], 100.0f, 0);
    Math_SmoothStepToF(&player->cam.eye.y, gCsCamEyeY, D_ctx_80177A48[0], 100.0f, 0);
    Math_SmoothStepToF(&player->cam.eye.z, gCsCamEyeZ, D_ctx_80177A48[0], 100.0f, 0);

    Math_SmoothStepToF(&player->cam.at.x, gCsCamAtX, D_ctx_80177A48[1], 100.0f, 0);
    Math_SmoothStepToF(&player->cam.at.y, gCsCamAtY, D_ctx_80177A48[1], 100.0f, 0);
    Math_SmoothStepToF(&player->cam.at.z, gCsCamAtZ, D_ctx_80177A48[1], 100.0f, 0);

    player->bobPhase += 10.0f;
    player->yBob = -SIN_DEG(player->bobPhase) * 0.3f;
    player->rockPhase += 8.0f;
    player->rockAngle = SIN_DEG(player->rockPhase);
}
