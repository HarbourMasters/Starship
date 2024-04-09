#include "global.h"
#include "assets/ast_venom_2.h"

void Venom2_80196210(Boss* boss) {
    Math_SmoothStepToF(&boss->fwork[0], boss->fwork[1], 0.5f, 5.0f, 0.0f);
}

bool Venom2_8019624C(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* data) {
    Boss* boss = (Boss*) data;

    if ((limbIndex == 1) || (limbIndex == 2)) {
        pos->x -= boss->fwork[0];
    }

    return false;
}

void Venom2_80196288(Boss* boss) {
    Animation_GetFrameData(&D_VE2_6014904, 0, boss->vwork);
    Animation_DrawSkeleton(3, D_VE2_60149D0, boss->vwork, Venom2_8019624C, NULL, boss, gCalcMatrix);
}

void Venom2_801962F4(Actor* actor) {
    func_360_8002F69C(actor);
}

static Vec3f D_i6_801A68B0[6] = {
    { 0.0f, 4030.0f, 18000.0f }, { -500.0f, 3820.0f, 17200.0f }, { 550.0f, 3750.0f, 17000.0f },
    { 1000.0f, 300.0f, 0.0f },   { -1000.0f, 300.0f, 0.0f },     { 0.0f, 500.0f, 0.0f },
};

static f32 D_i6_801A68F8[3] = { 300.0f, 70.0f, 280.0f };

void Venom2_80196314(Actor* actor) {
    Actor* otherActor;
    Actor* actor4 = &gActors[4];
    Player* player = &gPlayer[0];
    s32 i;

    switch (actor->state) {
        case 0:
            gAllRangeEventTimer = 0;
            gStarWolfMsgTimer = 0;

            for (i = 0; i < 6; i++) {
                gSavedStarWolfTeamAlive[i] = 1;
                gStarWolfTeamAlive[i] = 1;
            }

            if (player->state_1C8 == PLAYERSTATE_1C8_3) {
                actor->state = 2;
                player->pos.x = 0.0f;
                player->pos.z = 8000.0f;
                player->pos.y = 670.0f;
                D_360_800C9B4C = 120;
                gStarWolfMsgTimer = 1000;
            } else {
                D_360_800C9B4C = 320;
                gStarWolfMsgTimer = 1200;
                actor->state = 1;
                player->pos.x = 0.0f;
                player->pos.z = 16000.0f;
                player->pos.y = 4350.0f;
                player->unk_0E4 = -20.0f;
                player->unk_114 = 0.0f;
                actor->timer_0BC = 210;
                for (otherActor = &gActors[1], i = 1; i < 4; i++, otherActor++) {
                    otherActor->obj.pos.x = D_i6_801A68B0[i - 1].x;
                    otherActor->obj.pos.y = D_i6_801A68B0[i - 1].y + 750.f;
                    otherActor->obj.pos.z = D_i6_801A68B0[i - 1].z;
                    otherActor->obj.rot.z = D_i6_801A68F8[i - 1];
                    otherActor->unk_0F4.x = 340.0f;
                }

                gFillScreenAlpha = gFillScreenAlphaTarget = 255;
            }
            func_play_800B63BC(player, 1);
            /* fallthrough */
        case 1:

            for (otherActor = &gActors[1], i = 1; i < 4; i++, otherActor++) {
                otherActor->state = 0;
                otherActor->timer_0BC = 3;
                if (actor->timer_0BC == 0) {
                    otherActor->state = 2;
                    actor->state = 2;
                    player->state_1C8 = PLAYERSTATE_1C8_3;
                    player->unk_014 = 0.0001f;
                    gLevelStatusScreenTimer = 80;
                }
            }
            if (gAllRangeEventTimer == 80) {
                Radio_PlayMessage(gMsg_ID_19010, RCID_FOX);
            }
            break;
        case 2:
            Venom2_801962F4(actor);
            if (((D_360_800C9B4C + 100) < gAllRangeEventTimer) && (gActors[4].obj.status == OBJ_FREE) &&
                (gActors[5].obj.status == OBJ_FREE) && (gActors[6].obj.status == OBJ_FREE) &&
                (gActors[7].obj.status == OBJ_FREE) && (actor->timer_0BE == 0)) {
                actor->timer_0BE = 80;
            }
            if ((actor->timer_0BE == 1) && (player->state_1C8 != PLAYERSTATE_1C8_7)) {

                for (i = 1; i < ARRAY_COUNT(gTeamShields); i++) {
                    gPrevPlanetTeamShields[i] = gSavedTeamShields[i];
                    gPrevPlanetSavedTeamShields[i] = gSavedTeamShields[i];
                    gSavedTeamShields[i] = gTeamShields[i];
                }

                player->state_1C8 = PLAYERSTATE_1C8_7;
                player->unk_1D0 = 0;
                D_play_800D3180[gCurrentLevel] = 2;
                D_ctx_80177C94 = gGoldRingCount[0];
                D_ctx_80177C9C = player->shields + 1;
                D_play_80161A5C = D_ctx_80177CA4 = gHitCount;
                D_ctx_80177CAC = player->wings.rightState;
                D_ctx_80177CB4 = player->wings.leftState;
                D_ctx_80177CBC = gRightWingHealth[0];
                D_ctx_80177CC4 = gLeftWingHealth[0];
            }
            break;
        case 3:
            gPauseEnabled = 0;
            if (gStarWolfMsgTimer < 600) {
                player->camEye.x += actor4->vel.x * 0.23f;
                player->camEye.y += actor4->vel.y * 0.23f;
                player->camEye.z += actor4->vel.z * 0.23f;
            }
            Math_SmoothStepToF(&player->camAt.x, actor4->obj.pos.x, 1.0f, 20000.0f, 0.0f);
            Math_SmoothStepToF(&player->camAt.y, actor4->obj.pos.y, 1.0f, 20000.0f, 0.0f);
            Math_SmoothStepToF(&player->camAt.z, actor4->obj.pos.z, 1.0f, 20000.0f, 0.0f);
            Math_SmoothStepToF(&player->unk_034, 0, 0.1f, 0.2f, 0.0f);
            if ((gControllerPress->button & START_BUTTON) || (gAllRangeEventTimer == (D_360_800C9B4C + 300))) {
                actor->state = 2;
                player->state_1C8 = PLAYERSTATE_1C8_3;
                func_play_800B7184(player, 1);
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

void Venom2_80196968(void) {
    Actor* actor;
    Boss* boss;
    Object_58* obj58;
    s32 i;

    gLevelObjects = LOAD_ASSET(gLevelObjectInits[gCurrentLevel]);

    for (obj58 = gObjects58, i = 0; i < 1000; i++) {
        if (gLevelObjects[i].id < 0) {
            break;
        }

        if (gLevelObjects[i].id <= OBJ_80_160) {
            Object_58_Initialize(obj58);
            obj58->obj.status = OBJ_ACTIVE;
            obj58->obj.id = gLevelObjects[i].id;
            obj58->sfxSource[0] = obj58->obj.pos.x = gLevelObjects[i].xPos;
            obj58->sfxSource[1] = obj58->obj.pos.y = gLevelObjects[i].yPos;
            obj58->sfxSource[2] = obj58->obj.pos.z = -gLevelObjects[i].zPos1;
            obj58->unk_54 = obj58->obj.rot.y = gLevelObjects[i].rot.y;

            Object_SetInfo(&obj58->info, obj58->obj.id);

            obj58++;
        }
    }

    for (actor = &gActors[30], i = 0; i < 1000; i++) {
        if (gLevelObjects[i].id < 0) {
            break;
        }

        if ((gLevelObjects[i].id >= OBJ_ACTOR_176) && (gLevelObjects[i].id <= OBJ_ACTOR_SUPPLIES)) {
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
    boss->obj.id = OBJ_BOSS_312;
    Object_SetInfo(&boss->info, boss->obj.id);
}

void Venom2_80196BF8(Player* player) {
    Vec3f vec;
    Vec3f vel;
    f32 temp_fv0;

    if (gCsFrameCount > 50) {
        gFillScreenAlphaStep = 3;
        gFillScreenAlphaTarget = 0;
    }
    Matrix_RotateY(gCalcMatrix, (player->unk_114 + player->unk_0E8 + 180.0f) * M_DTOR, 0);
    Matrix_RotateX(gCalcMatrix, -((player->unk_120 + player->unk_0E4 + player->unk_4D8) * M_DTOR), 1);
    vec.x = 0.0f;
    vec.y = 0.0f;
    vec.z = player->unk_0D0 + player->unk_110;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &vec, &vel);
    player->vel.x = vel.x;
    player->vel.z = vel.z;
    player->vel.y = vel.y;
    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;
    player->pos.z += player->vel.z;

    player->unk_0F8 = player->unk_0EC + player->unk_12C + player->unk_130;
    player->unk_138 = player->pos.z;
    player->camEye.x = 50.0f;
    player->camEye.y = 1800.0f;
    player->camEye.z = 9000.0f;
    player->camAt.x = player->pos.x;
    player->camAt.y = player->pos.y;
    player->camAt.z = player->pos.z;
}

void Venom2_80196D88(Player* player) {
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

    Math_SmoothStepToF(&player->unk_110, 0.0f, 0.1f, 1.5f, 0.0f);
    Math_SmoothStepToF(&player->unk_0E8, 0.0f, 0.1f, 1.5f, 0.0f);
    Math_SmoothStepToF(&player->unk_0E4, 0.0f, 0.1f, 1.5f, 0.0f);

    var_fa0 = -player->unk_120;
    temp_fv1 = player->unk_0EC;

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

    Math_SmoothStepToF(&player->wings.unk_04, -var_fa0 + sp74, 0.1f, 100.0f, 0.0f);
    Math_SmoothStepToF(&player->wings.unk_08, -var_fa0 - sp74, 0.1f, 100.0f, 0.0f);
    Math_SmoothStepToF(&player->wings.unk_0C, -var_fa0 + sp70, 0.1f, 100.0f, 0.0f);
    Math_SmoothStepToF(&player->wings.unk_10, -var_fa0 - sp70, 0.1f, 100.0f, 0.0f);
    sp94 = player->pos.x - gBosses[0].obj.pos.x;
    sp90 = player->pos.y - (gBosses[0].obj.pos.y + 700.0f);
    sp8C = player->pos.z - gBosses[0].obj.pos.z;

    switch (player->unk_1D0) {
        case 0:
            player->unk_1D0++;
            player->wings.unk_04 = player->wings.unk_0C = player->wings.unk_08 = player->wings.unk_10 = 0.0f;
            player->wings.unk_2C = 1;
            D_ctx_80177A48[0] = 0.0f;
            D_ctx_80177A48[1] = 0.1f;
            D_ctx_80177A48[3] = 0.0f;
            D_ctx_80177A48[4] = 0.0f;
            player->timer_1F8 = 0;
            if ((fabsf(sp94) < 4000.0f) && (fabsf(sp8C) < 4000.0f)) {
                player->timer_1F8 = 250;
                sp64.x = 0.0f;
                sp64.y = 0.0f;
                sp64.z = 5000.0f;
                Matrix_RotateY(gCalcMatrix, player->unk_114, 0);
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp64, &sp58);
                D_ctx_80177A48[5] = sp58.x;
                D_ctx_80177A48[6] = sp58.z;
            }
            if (gLevelStage == 2) {
                player->timer_1FC = 240;
            } else {
                player->timer_1FC = 180;
            }
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 60);
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 60);
            /* fallthrough */
        case 1:
            if (gLevelStage == 2) {
                gFillScreenAlphaStep = 2;
                gFillScreenAlphaTarget = 0;
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
            }
            Math_SmoothStepToF(&D_ctx_80177A48[1], 0.8f, 1.0f, 0.05f, 0.0f);
            Math_SmoothStepToF(&player->unk_12C, 0.0f, 0.1f, 15.0f, 0.0f);
            if (player->timer_1F8 == 1) {
                D_ctx_80177A48[4] = 0.0f;
            }
            if (player->timer_1F8 != 0) {
                sp94 = player->pos.x - (gBosses[0].obj.pos.x + D_ctx_80177A48[5]);
                sp90 = player->pos.y - (gBosses[0].obj.pos.y + 700.0f);
                sp8C = player->pos.z - (gBosses[0].obj.pos.z + D_ctx_80177A48[6]);
            }
            sp84 = Math_RadToDeg(Math_Atan2F(sp94, sp8C));
            sp8C = sqrtf(SQ(sp94) + SQ(sp8C));
            pad88 = Math_RadToDeg(-Math_Atan2F(sp90, sp8C));
            Math_SmoothStepToAngle(&player->unk_120, pad88, 0.1f, D_ctx_80177A48[4], 0.0f);
            pad80 = Math_SmoothStepToAngle(&player->unk_114, sp84, 0.1f, D_ctx_80177A48[4], 0.0f) * 20.0f;
            Math_SmoothStepToF(&player->unk_0EC, pad80, 0.1f, 3.0f, 0.0f);
            Math_SmoothStepToF(&D_ctx_80177A48[4], 3.0f, 1.0f, 0.1f, 0.0f);
            Matrix_RotateX(gCalcMatrix, -(D_PI / 9), 0);
            Matrix_RotateY(gCalcMatrix, (D_ctx_80177A48[3] + player->unk_114) * M_DTOR, 1);
            D_ctx_80177A48[3] += 1.0f;
            sp64.x = 0.0f;
            sp64.y = 0.0f;
            sp64.z = 400.0f;
            Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp64, &sp58);
            gCsCamEyeX = player->pos.x + sp58.x;
            gCsCamEyeY = player->pos.y + sp58.y;
            gCsCamEyeZ = player->pos.z + sp58.z;
            Math_SmoothStepToF(D_ctx_80177A48, 0.5f, 1.0f, 0.01f, 0.0f);
            Math_SmoothStepToF(&player->unk_034, 0.0f, 0.1f, 3.0f, 0.0f);
            if ((player->timer_1F8 == 0) && (fabsf(sp94) < 50.0f) && (fabsf(sp8C) < 50.0f)) {
                player->unk_1D0++;
                D_ctx_80177A48[2] = 0.75f;
                D_ctx_80177A48[3] = 0.0f;
                D_ctx_80177A48[4] = 0.0f;

                if (player->unk_120 >= 180.0f) {
                    player->unk_120 -= 360.0f;
                }
                AUDIO_PLAY_SFX(0x09000002, player->sfxSource, 0);
                player->unk_194 = 5.0f;
                player->unk_190 = 5.0f;
                gCsFrameCount = 0;
                Audio_SetBgmParam(0);
            }
            break;
        case 2:
            player->unk_190 = 2.0f;
            Math_SmoothStepToF(&player->unk_120, 270.0f, 0.1f, D_ctx_80177A48[2], 0.0f);
            Math_SmoothStepToF(&D_ctx_80177A48[2], 4.0f, 1.0f, 0.05f, 0.0f);
            if (player->unk_120 > 80.0f) {
                Math_SmoothStepToF(&player->unk_12C, 10000.0f, 0.1f, 8.0f, 0.0f);
            }
            if (player->unk_120 > 250.0f) {
                Math_SmoothStepToF(&player->pos.x, 0.0f, 0.3f, D_ctx_80177A48[3], 0.0f);
                Math_SmoothStepToF(&player->pos.z, 0.0f, 0.3f, D_ctx_80177A48[3], 0.0f);
                Math_SmoothStepToF(&D_ctx_80177A48[3], 30.0f, 1.0f, 1.0f, 0.0f);
            }
            if (player->unk_120 > 200.0f) {
                Math_SmoothStepToF(&D_ctx_80177A48[4], 20.0f, 1.0f, 1.0f, 0.0f);
                Math_SmoothStepToF(&gCsCamEyeX, player->pos.x, 0.1f, D_ctx_80177A48[4], 0.0f);
                Math_SmoothStepToF(&gCsCamEyeY, player->pos.y + 200.0f, 0.1f, D_ctx_80177A48[4], 0.0f);
                Math_SmoothStepToF(&gCsCamEyeZ, player->pos.z, 0.1f, D_ctx_80177A48[4], 0.0f);
            } else {
                Math_SmoothStepToF(&gCsCamEyeY, player->pos.y, 0.1f, 2.0f, 0.0f);
            }

            if (gCsFrameCount == 105) {
                AUDIO_PLAY_SFX(0x09000002, player->sfxSource, 0);
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
                    if (D_play_800D3180[gCurrentLevel] != 0) {
                        gNextLevelStage = 1;
                    }
                    func_8001CA24(0);
                    Audio_KillSfxBySource(player->sfxSource);

                    for (i = 0; i < 200; i++) {
                        gObjects58[i].obj.status = OBJ_FREE;
                    }
                }
            }
            if (gCsFrameCount > 110) {
                gBosses[0].fwork[1] = 150.0f;
            }
            break;
    }
    if (player->timer_1FC == 150) {
        Radio_PlayMessage(gMsg_ID_8215, RCID_FOX);
        AUDIO_PLAY_BGM(SEQ_ID_TO_ANDROSS | SEQ_FLAG);
    }
    if (player->timer_1FC == 1) {
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
    gCsCamAtZ = player->unk_138;
    Matrix_RotateY(gCalcMatrix, (player->unk_114 + player->unk_0E8 + 180.0f) * M_DTOR, 0);
    Matrix_RotateX(gCalcMatrix, -((player->unk_120 + player->unk_0E4 + player->unk_4D8) * M_DTOR), 1);
    sp64.x = 0.0f;
    sp64.y = 0.0f;
    sp64.z = player->unk_0D0 + player->unk_110;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp64, &sp58);
    player->vel.x = sp58.x;
    player->vel.z = sp58.z;
    player->vel.y = sp58.y;
    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;
    player->pos.z += player->vel.z;
    player->unk_138 = player->pos.z;
    player->unk_0F8 = player->unk_0EC + player->unk_12C + player->unk_130;
    Math_SmoothStepToF(&player->unk_130, 0.0f, 0.1f, 15.0f, 0.0f);
    Math_SmoothStepToAngle(&player->unk_4D8, 0.0f, 0.1f, 5.0f, 0.0f);
    Math_SmoothStepToF(&player->camEye.x, gCsCamEyeX, D_ctx_80177A48[0], 100.0f, 0);
    Math_SmoothStepToF(&player->camEye.y, gCsCamEyeY, D_ctx_80177A48[0], 100.0f, 0);
    Math_SmoothStepToF(&player->camEye.z, gCsCamEyeZ, D_ctx_80177A48[0], 100.0f, 0);
    Math_SmoothStepToF(&player->camAt.x, gCsCamAtX, D_ctx_80177A48[1], 100.0f, 0);
    Math_SmoothStepToF(&player->camAt.y, gCsCamAtY, D_ctx_80177A48[1], 100.0f, 0);
    Math_SmoothStepToF(&player->camAt.z, gCsCamAtZ, D_ctx_80177A48[1], 100.0f, 0);
    player->unk_088 += 10.0f;
    player->unk_080 = -SIN_DEG(player->unk_088) * 0.3f;
    player->unk_0F4 += 8.0f;
    player->unk_0F0 = SIN_DEG(player->unk_0F4);
}
