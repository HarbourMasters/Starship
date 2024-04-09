#include "global.h"

Vec3f D_i5_801B72A0[] = { 500.0f, -700.0f, 200.0f, -500.0f, -700.0f, 200.0f };
Vec3f D_i5_801B72B8[] = { 40.0f,  10.0f, 30.0f, 41.0f,  10.0f, 10.0f, 43.0f,  10.0f, -10.0f, 45.0f,  10.0f, -30.0f,
                          -40.0f, 10.0f, 30.0f, -41.0f, 10.0f, 10.0f, -43.0f, 10.0f, -10.0f, -45.0f, 10.0f, -30.0f };
f32 D_i5_801B7318[] = { 1000.0f, -1000.0f, 0.0f, 0.0f };
f32 D_i5_801B7328[] = { 1000.0f, 1000.0f, 1000.0f, 4000.0f };
f32 D_i5_801B7338[] = { 1000.0f, 1000.0f, 1000.0f, -4000.0f };
f32 D_i5_801B7348[] = { 90.0f, -90.0f, 0.0f };

void Titania_80187530(Actor* actor) {
    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_195;

    actor->obj.pos.x = 0.0f;
    actor->obj.pos.y = 3000.0f;
    actor->obj.pos.z = 0.0f;

    actor->obj.rot.y = 180.0f;
    Object_SetInfo(&actor->info, actor->obj.id);
    AUDIO_PLAY_SFX(0x11030010U, actor->sfxSource, 0U);
    actor->unk_0B6 = 1;
}

void Titania_801875D0(Actor* actor, s32 arg1) {
    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_195;

    actor->obj.pos.x = D_i5_801B72A0[arg1].x;
    actor->obj.pos.y = D_i5_801B72A0[arg1].y + 3000.0f;
    actor->obj.pos.z = D_i5_801B72A0[arg1].z;

    actor->obj.rot.y = 180.0f;
    actor->iwork[11] = 1;
    Object_SetInfo(&actor->info, actor->obj.id);
    AUDIO_PLAY_SFX(0x3100000CU, actor->sfxSource, 4U);
}

void Titania_8018769C(Player* player) {
    f32 sp64;
    Actor* actor = &gActors[3];
    Vec3f sp54;
    Vec3f sp48;

    sp64 = 20000.0f;

    switch (player->unk_1D0) {
        case 0:
            gCsFrameCount = 0;
            D_ctx_80177BAC = 1;
            player->unk_0D4 = 0.0f;

            Titania_80187530(&gActors[3]);

            if (gTeamShields[TEAM_ID_FALCO] > 0) {
                Titania_801875D0(&gActors[10], 0);
            }

            if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                Titania_801875D0(&gActors[11], 1);
            }

            player->pos.x = actor->obj.pos.x;
            player->pos.y = actor->obj.pos.y - 530.0f;
            player->pos.z = actor->obj.pos.z;

            player->camEye.x = gCsCamEyeX = 5000.0f;
            player->camEye.y = gCsCamEyeY = 1000.0f;
            player->camEye.z = gCsCamEyeZ = -5000.0f;

            player->camAt.x = gCsCamAtX = player->pos.x;
            player->camAt.y = gCsCamAtY = player->pos.y;
            player->camAt.z = gCsCamAtZ = player->pos.z;

            player->unk_240 = 1;
            player->unk_1D0 = 1;
            gFogFar = 1006;
            gPlayer[0].unk_19C = 0;
            gBgColor = 0x78C1; // 120, 24, 0

        case 1:
            D_ctx_80177A48[0] = 0.01f;
            sp64 = 20.0f;
            gCsCamEyeX = actor->obj.pos.x - 500.0f;
            gCsCamEyeY = actor->obj.pos.y - 500.0f;
            gCsCamEyeZ = actor->obj.pos.z - 750.0f;

            if (gCsFrameCount == 330) {
                Radio_PlayMessage(gMsg_ID_4113, RCID_FOX);
            }

            if (gCsFrameCount == 430) {
                player->unk_1D0 = 2;
                player->timer_1F8 = 10;
                AUDIO_PLAY_SFX(0x09000002U, player->sfxSource, 0U);
            }
            gCsCamAtX = player->pos.x;
            gCsCamAtY = player->pos.y;
            gCsCamAtZ = player->pos.z;
            break;

        case 2:
            Math_SmoothStepToF(&player->vel.z, -10.0f, 1.0f, 1.0f, 0.0f);
            gCsCamAtX = player->pos.x;
            gCsCamAtY = player->pos.y;
            gCsCamAtZ = player->pos.z;

            if (player->timer_1F8 == 1) {
                player->unk_0D4 = 1.0f;
                D_ctx_80177A48[0] = 0.05f;
            }

            if (player->timer_1F8 == 0) {
                if (player->unk_0D4 > -0.3f) {
                    player->unk_0D4 = player->unk_0D4 - 0.05f;
                }
            }

            if ((gCsFrameCount > 450) && (gCsFrameCount < 490)) {
                Math_SmoothStepToF(&player->unk_170, 2.0f, 1.0f, 0.2f, 0.0f);
                Math_SmoothStepToF(&player->unk_16C, 2.0f, 1.0f, 0.2f, 0.0f);
            } else {
                Math_SmoothStepToF(&player->unk_170, 0.5f, 1.0f, 0.2f, 0.0f);
                Math_SmoothStepToF(&player->unk_16C, 0.5f, 1.0f, 0.2f, 0.0f);
            }

            if (gCsFrameCount == 500) {
                gCsFrameCount = 480;

                player->unk_1D0 = 3;
                player->unk_144 = 200.0f;

                D_ctx_80177D20 = 200.0f;
                D_ctx_80177CC8 = D_ctx_80177D20;

                player->pos.z = -(D_ctx_80177D20) -200.0f;
                player->unk_0D4 = 0.0f;
                player->vel.y = 0.0f;
                player->pos.y = 2000.0f;
                player->vel.z = 0.0f;

                player->camAt.x = gCsCamAtX = player->pos.x;
                player->camAt.y = gCsCamAtY = player->pos.y;
                player->camAt.z = gCsCamAtZ = player->pos.z;

                gPlayer[0].unk_19C = 1;

                gBgColor = 0x2089; // 32, 16, 32

                player->unk_16C = 0.5f;
                player->unk_170 = 0.5f;

                D_ctx_80177A48[2] = -270.0f;
                D_ctx_80177A48[3] = 200.0f;
                D_ctx_80177A48[1] = 0.0f;

                *D_ctx_80177A10 = 0;

                Matrix_RotateY(gCalcMatrix, D_ctx_80177A48[2] * M_DTOR, 0);

                sp54.x = 0.0f;
                sp54.y = 30.0f;
                sp54.z = D_ctx_80177A48[3];

                Matrix_MultVec3f(gCalcMatrix, &sp54, &sp48);

                gCsCamEyeX = sp48.x;

                player->camEye.x = sp48.x;

                gCsCamEyeY = sp48.y;

                player->camEye.y = sp48.y;
                player->camEye.z = gCsCamEyeZ = player->pos.z + player->unk_144 + sp48.z;
            }
            break;

        case 3:
            Math_SmoothStepToF(&D_ctx_80177A48[2], 0.0f, 0.1f, 4.0f, 0.0f);
            Matrix_RotateY(gCalcMatrix, D_ctx_80177A48[2] * M_DTOR, 0);

            sp54.x = 0.0f;
            sp54.y = 30.0f;
            sp54.z = D_ctx_80177A48[3];

            Matrix_MultVec3f(gCalcMatrix, &sp54, &sp48);

            gCsCamEyeX = sp48.x;
            gCsCamEyeY = sp48.y;
            gCsCamEyeZ = player->pos.z + player->unk_144 + sp48.z;
            gCsCamAtX = player->pos.x;

            player->camAt.x = gCsCamAtX;
            player->camAt.y = gCsCamAtY = player->pos.y;
            player->camAt.z = gCsCamAtZ = player->pos.z + player->unk_144;

            Math_SmoothStepToF(&player->pos.y, D_ctx_80177A48[1], 0.1f, 50.0f, 0.0f);

            if (player->pos.y < 200.0f) {
                Math_SmoothStepToF(&player->unk_170, 1.0f, 1.0f, 0.2f, 0.0f);
                Math_SmoothStepToF(&player->unk_16C, 1.0f, 1.0f, 0.2f, 0.0f);
                Math_SmoothStepToF(&D_ctx_80177A48[1], 70.0f, 0.05f, 1.0f, 0.0f);
                Math_SmoothStepToF(&D_ctx_80177A48[3], 400.0f, 1.0f, 5.0f, 0.0f);

                if (D_ctx_80177A10[0] == 0) {
                    D_ctx_80177A10[0]++;
                    AUDIO_PLAY_SFX(0x01008016U, player->sfxSource, 0U);
                }
            }

            if (player->pos.y < 100.0f) {
                func_effect_8007A900(RAND_FLOAT_CENTERED(30.0f) + player->pos.x, 30.0f,
                                     RAND_FLOAT_CENTERED(30.0f) + player->unk_138, RAND_FLOAT(2.0f) + 3.5f, 255, 12, 1);
                Object_Kill(&gActors[3].obj, gActors[3].sfxSource);
            }

            Math_SmoothStepToF(&player->unk_0F0, SIN_DEG(gGameFrameCount * 5.0f) * 10.0f, 0.1f, 100.0f, 0.0f);

            if (gCsFrameCount == 580) {
                gLevelStatusScreenTimer = 50;
                player->state_1C8 = PLAYERSTATE_1C8_3;
                player->unk_1D0 = player->timer_1F8 = player->timer_1FC = player->unk_240 = 0;
                player->unk_0D4 = 3.0f;
                player->unk_014 = 0.0f;
                D_ctx_8017782C = 1;
                func_play_800A594C();
                D_ctx_8017782C = 0;
                if ((gControllerHold[player->num].button & Z_TRIG) && (gControllerHold[player->num].button & R_TRIG)) {
                    Audio_KillSfxBySourceAndId(player->sfxSource, 0x01008016);
                }
            }
            break;
    }

    player->pos.y += player->vel.y;
    player->vel.y -= player->unk_0D4;
    player->pos.z += player->vel.z;
    player->unk_138 = player->pos.z;

    Math_SmoothStepToF(&player->camEye.x, gCsCamEyeX, D_ctx_80177A48[0], sp64, 0.00f);
    Math_SmoothStepToF(&player->camEye.y, gCsCamEyeY, D_ctx_80177A48[0], sp64, 0.00f);
    Math_SmoothStepToF(&player->camEye.z, gCsCamEyeZ, D_ctx_80177A48[0], sp64, 0.00f);
    Math_SmoothStepToF(&player->camAt.x, gCsCamAtX, D_ctx_80177A48[0], sp64, 0.00f);
    Math_SmoothStepToF(&player->camAt.y, gCsCamAtY, D_ctx_80177A48[0], sp64, 0.00f);
    Math_SmoothStepToF(&player->camAt.z, gCsCamAtZ, D_ctx_80177A48[0], sp64, 0.00f);
}

void Titania_80188108(Actor* actor, s32 arg1) {
    Player* player = &gPlayer[0];

    Actor_Initialize(actor);
    actor->obj.pos.x = D_i5_801B7318[arg1] + player->pos.x;
    actor->obj.pos.y = D_i5_801B7328[arg1] + player->pos.y;
    actor->obj.pos.z = D_i5_801B7338[arg1] + player->pos.z;

    actor->fwork[7] = RAND_FLOAT(360.0f);
    actor->fwork[8] = RAND_FLOAT(360.0f);

    actor->vel.x = player->vel.x;
    actor->vel.y = player->vel.y;
    actor->vel.z = player->vel.z;

    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_195;
    actor->obj.rot.y = 180.0f;

    Object_SetInfo(&actor->info, actor->obj.id);

    if (arg1 < 3) {
        actor->iwork[11] = 1;
        actor->unk_0C9 = 1;
        actor->fwork[3] = D_i5_801B7348[arg1];
        actor->state = 30;
        AUDIO_PLAY_SFX(0x3100000CU, actor->sfxSource, 4U);
    } else {
        actor->unk_0B6 = 1;
        actor->state = 20;
        AUDIO_PLAY_SFX(0x11030010U, actor->sfxSource, 0U);
        actor->fwork[9] = 20.0f;
    }
}

void Titania_801882CC(Player* player) {
    f32 x;
    f32 camAtY = 0.0f;
    Vec3f src;
    Vec3f dest;
    s32 i;

    switch (player->unk_1D0) {
        case 0:
            gCsFrameCount = gBossActive = D_ctx_80178488 = 0;

            func_play_800A6148();

            player->unk_1D0 = 1;

            D_ctx_80177A48[0] = 0.0f;
            D_ctx_80177A48[1] = 0.0f;
            D_ctx_80177A48[2] = 0.0f;
            D_ctx_80177A48[3] = 250.0f;

            player->unk_0D4 = 3.0f;

            Titania_80188108(&gActors[0], 0);

            if (gTeamShields[TEAM_ID_FALCO] > 0) {
                Titania_80188108(&gActors[1], 1);
            }
            if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                Titania_80188108(&gActors[2], 2);
            }

            Audio_KillSfxBySourceAndId(player->sfxSource, 0x01004024U);

        case 1:
            Math_SmoothStepToF(D_ctx_80177A48, 0.1f, 1.0f, 0.01f, 0.0f);
            Math_SmoothStepToF(&player->unk_0D0, 4.9f, 0.1f, 1.0f, 0.0f);
            Math_SmoothStepToF(&player->unk_08C, 0.0f, 0.1f, 1.0f, 0.0f);

            if (gCsFrameCount < 1120) {
                Math_SmoothStepToF(&D_ctx_80177A48[1], 0.65f, 0.1f, 0.01f, 0.0f);
            } else {
                Math_SmoothStepToF(&D_ctx_80177A48[1], 0.0f, 0.1f, 0.02f, 0.0f);
            }

            D_ctx_80177A48[2] = D_ctx_80177A48[1] + D_ctx_80177A48[2];

            Matrix_RotateX(gCalcMatrix, -10.0f * M_DTOR, 0);
            Matrix_RotateY(gCalcMatrix, D_ctx_80177A48[2] * M_DTOR, 1);

            src.x = 0.0f;
            src.y = 0.0f;
            src.z = D_ctx_80177A48[3];

            Matrix_MultVec3f(gCalcMatrix, &src, &dest);

            gCsCamEyeX = player->pos.x + dest.x;
            gCsCamEyeY = player->pos.y + dest.y;
            gCsCamEyeZ = player->pos.z + player->unk_144 + dest.z + 50.0f;

            if (gCsCamEyeY < 5.0f) {
                gCsCamEyeY = 5.0f;
            }

            gCsCamAtX = player->pos.x;
            gCsCamAtY = player->pos.y + 30.0f;
            gCsCamAtZ = player->pos.z + player->unk_144;

            func_tank_80045130(player);
            func_tank_80044868(player);
            func_tank_80045678(player);
            func_tank_80045E7C(player);
            func_play_800A8BA4(player);
            func_play_800ADF58(player);

            if (((gGameFrameCount % 4) == 0)) {
                f32 x;
                f32 y;
                f32 z;

                for (i = 0; i < 8; i++) {
                    x = D_i5_801B72B8[i].x;
                    y = D_i5_801B72B8[i].y + RAND_FLOAT_CENTERED(10.0f);
                    z = D_i5_801B72B8[i].z;

                    func_effect_8007A900(player->pos.x + x, player->pos.y + y, player->unk_138 + z,
                                         RAND_FLOAT(0.5f) + 0.5f, 255, 21, 0);
                }
            }
            break;

        case 2:
            Math_SmoothStepToF(D_ctx_80177A48, 0.1f, 1.0f, 0.01f, 0.0f);
            gCsCamEyeX -= 2.5f;
            gCsCamEyeZ -= 1.0f;

            gCsCamAtX = player->pos.x;
            gCsCamAtY = player->pos.y + 30.0f;
            gCsCamAtZ = player->pos.z + player->unk_144;

            if (player->pos.y < 100.0f) {
                camAtY = SIN_DEG(gGameFrameCount * 130.0f) * 3.0f;
            }

            Math_SmoothStepToF(&player->unk_170, 2.0f, 1.0f, 0.2f, 0.0f);
            Math_SmoothStepToF(&player->unk_16C, 2.0f, 1.0f, 0.2f, 0.0f);

            if (gCsFrameCount < 1470) {
                func_effect_8007A900(RAND_FLOAT_CENTERED(30.0f) + (player->pos.x + 30.0f), 30.0f,
                                     RAND_FLOAT_CENTERED(30.0f) + player->unk_138, RAND_FLOAT(2.0f) + 3.5f, 255, 12, 1);
            }

            func_effect_8007A900(RAND_FLOAT_CENTERED(30.0f) + (player->pos.x - 30.0f), 30.0f,
                                 RAND_FLOAT_CENTERED(30.0f) + player->unk_138, RAND_FLOAT(2.0f) + 3.5f, 255, 12, 1);
            Math_SmoothStepToF(&player->unk_0F0, SIN_DEG(gGameFrameCount * 6.0f) * 18.0f, 0.1f, 100.0f, 0.0f);
            Math_SmoothStepToF(&player->unk_080, SIN_DEG(gGameFrameCount * 3.0f) * 5.0f, 0.1f, 100.0f, 0.0f);

            x = SIN_DEG(gGameFrameCount * 4.0f) * -1.5f;

            player->vel.x = x;
            player->vel.y += 0.1f;
            player->vel.z -= 0.17f;

            player->pos.x += x;
            player->pos.y += player->vel.y;
            player->pos.z += player->vel.z;

            player->unk_138 = player->pos.z;
            break;
    }

    switch (gCsFrameCount) {
        case 831:
            D_ctx_80177830 = 1;
            break;

        case 1031:
            D_ctx_80177830 = 0;
            break;

        case 50:
            AUDIO_PLAY_BGM(SEQ_ID_GOOD_END);
            break;

        case 80:
            gLevelClearScreenTimer = 100;
            break;

        case 160:
            Radio_PlayMessage(gMsg_ID_20010, RCID_FOX);
            break;

        case 248:
            Radio_PlayMessage(gMsg_ID_4100, RCID_SLIPPY);
            break;

        case 380:
            switch (gTeamShields[TEAM_ID_FALCO]) {
                case -1:
                    Radio_PlayMessage(gMsg_ID_20331, RCID_ROB64);
                    break;

                case 0:
                    Radio_PlayMessage(gMsg_ID_20343, RCID_ROB64);
                    break;

                default:
                    Radio_PlayMessage(gMsg_ID_4101, RCID_FALCO);
                    break;
            }

            break;

        case 525:
            switch (gTeamShields[TEAM_ID_PEPPY]) {
                case -1:
                    Radio_PlayMessage(gMsg_ID_20332, RCID_ROB64);
                    break;

                case 0:
                    Radio_PlayMessage(gMsg_ID_20344, RCID_ROB64);
                    break;

                default:
                    Radio_PlayMessage(gMsg_ID_4102, RCID_PEPPY);
                    break;
            }
            break;

        case 671:
            Radio_PlayMessage(gMsg_ID_4103, RCID_FOX);
            break;

        case 1200:
            gActors[0].state++;
            break;

        case 1220:
            gActors[1].state++;
            break;

        case 1240:
            gActors[2].state++;
            break;

        case 1280:
            gOverlayStage = 5;
            break;

        case 1300:
            player->unk_1D0++;
            D_ctx_80177A48[0] = 0.0f;
            player->vel.z = 0.0f;
            player->vel.y = 0.0f;
            Titania_80188108(&gActors[3], 3);
            D_game_80161A44 = 30000.0f;
            player->unk_240 = 1;
            func_8001CA24(0);
            AUDIO_PLAY_SFX(0x01008016U, player->sfxSource, 0U);
            break;
    }

    Math_SmoothStepToF(&player->camEye.x, gCsCamEyeX, D_ctx_80177A48[0], 20000.0f, 0.00f);
    Math_SmoothStepToF(&player->camEye.y, gCsCamEyeY, D_ctx_80177A48[0], 20000.0f, 0.00f);
    Math_SmoothStepToF(&player->camEye.z, gCsCamEyeZ, D_ctx_80177A48[0], 20000.0f, 0.00f);
    Math_SmoothStepToF(&player->camAt.x, gCsCamAtX, D_ctx_80177A48[0], 20000.0f, 0.00f);
    Math_SmoothStepToF(&player->camAt.y, gCsCamAtY, D_ctx_80177A48[0], 20000.0f, 0.00f);
    Math_SmoothStepToF(&player->camAt.z, gCsCamAtZ, D_ctx_80177A48[0], 20000.0f, 0.00f);

    player->camAt.y += camAtY;

    if (gCsFrameCount == 1380) {
        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 60);
        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 60);
    }

    if (gCsFrameCount > 1440) {
        gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
        gFillScreenAlphaTarget = 255;

        if (gFillScreenAlpha == 255) {
            player->state_1C8 = PLAYERSTATE_1C8_6;
            D_ctx_8017837C = 4;
            func_play_800A6148();
            Audio_FadeOutAll(10);
            D_play_800D3180[LEVEL_TITANIA] = Play_CheckMedalStatus(150) + 1;
        }
    }
}
