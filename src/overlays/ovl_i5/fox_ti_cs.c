#include "global.h"

Vec3f D_i5_801B72A0[] = { 500.0f, -700.0f, 200.0f, -500.0f, -700.0f, 200.0f };
Vec3f D_i5_801B72B8[] = { 40.0f,  10.0f, 30.0f, 41.0f,  10.0f, 10.0f, 43.0f,  10.0f, -10.0f, 45.0f,  10.0f, -30.0f,
                          -40.0f, 10.0f, 30.0f, -41.0f, 10.0f, 10.0f, -43.0f, 10.0f, -10.0f, -45.0f, 10.0f, -30.0f };
f32 D_i5_801B7318[] = { 1000.0f, -1000.0f, 0.0f, 0.0f };
f32 D_i5_801B7328[] = { 1000.0f, 1000.0f, 1000.0f, 4000.0f };
f32 D_i5_801B7338[] = { 1000.0f, 1000.0f, 1000.0f, -4000.0f };
f32 D_i5_801B7348[] = { 90.0f, -90.0f, 0.0f };

void Titania_80187530(ActorCutscene* this) {
    Actor_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_ACTOR_CUTSCENE;

    this->obj.pos.x = 0.0f;
    this->obj.pos.y = 3000.0f;
    this->obj.pos.z = 0.0f;

    this->obj.rot.y = 180.0f;
    Object_SetInfo(&this->info, this->obj.id);
    AUDIO_PLAY_SFX(NA_SE_GREATFOX_ENGINE, this->sfxSource, 0);
    this->animFrame = ACTOR_CS_GREAT_FOX;
}

void Titania_801875D0(ActorCutscene* this, s32 arg1) {
    Actor_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_ACTOR_CUTSCENE;

    this->obj.pos.x = D_i5_801B72A0[arg1].x;
    this->obj.pos.y = D_i5_801B72A0[arg1].y + 3000.0f;
    this->obj.pos.z = D_i5_801B72A0[arg1].z;

    this->obj.rot.y = 180.0f;
    this->iwork[11] = 1;
    Object_SetInfo(&this->info, this->obj.id);
    AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, this->sfxSource, 4);
}

void Titania_LevelStart(Player* player) {
    f32 sp64;
    Actor* actor = &gActors[3];
    Vec3f sp54;
    Vec3f sp48;

    sp64 = 20000.0f;

    switch (player->csState) {
        case 0:
            gCsFrameCount = 0;
            gTiStartLandmaster = 1;
            player->gravity = 0.0f;

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

            player->cam.eye.x = gCsCamEyeX = 5000.0f;
            player->cam.eye.y = gCsCamEyeY = 1000.0f;
            player->cam.eye.z = gCsCamEyeZ = -5000.0f;

            player->cam.at.x = gCsCamAtX = player->pos.x;
            player->cam.at.y = gCsCamAtY = player->pos.y;
            player->cam.at.z = gCsCamAtZ = player->pos.z;

            player->hideShadow = true;
            player->csState = 1;
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
                player->csState = 2;
                player->csTimer = 10;
                AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, player->sfxSource, 0);
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

            if (player->csTimer == 1) {
                player->gravity = 1.0f;
                D_ctx_80177A48[0] = 0.05f;
            }

            if (player->csTimer == 0) {
                if (player->gravity > -0.3f) {
                    player->gravity = player->gravity - 0.05f;
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

                player->csState = 3;
                player->zPath = 200.0f;

                gPathProgress = 200.0f;
                gPathGroundScroll = gPathProgress;

                player->pos.z = -(gPathProgress) -200.0f;
                player->gravity = 0.0f;
                player->vel.y = 0.0f;
                player->pos.y = 2000.0f;
                player->vel.z = 0.0f;

                player->cam.at.x = gCsCamAtX = player->pos.x;
                player->cam.at.y = gCsCamAtY = player->pos.y;
                player->cam.at.z = gCsCamAtZ = player->pos.z;

                gPlayer[0].unk_19C = 1;

                gBgColor = 0x2089; // 32, 16, 32

                player->unk_16C = 0.5f;
                player->unk_170 = 0.5f;

                D_ctx_80177A48[2] = -270.0f;
                D_ctx_80177A48[3] = 200.0f;
                D_ctx_80177A48[1] = 0.0f;

                D_ctx_80177A10[0] = 0;

                Matrix_RotateY(gCalcMatrix, D_ctx_80177A48[2] * M_DTOR, MTXF_NEW);

                sp54.x = 0.0f;
                sp54.y = 30.0f;
                sp54.z = D_ctx_80177A48[3];

                Matrix_MultVec3f(gCalcMatrix, &sp54, &sp48);

                gCsCamEyeX = sp48.x;

                player->cam.eye.x = sp48.x;

                gCsCamEyeY = sp48.y;

                player->cam.eye.y = sp48.y;
                player->cam.eye.z = gCsCamEyeZ = player->pos.z + player->zPath + sp48.z;
            }
            break;

        case 3:
            Math_SmoothStepToF(&D_ctx_80177A48[2], 0.0f, 0.1f, 4.0f, 0.0f);
            Matrix_RotateY(gCalcMatrix, D_ctx_80177A48[2] * M_DTOR, MTXF_NEW);

            sp54.x = 0.0f;
            sp54.y = 30.0f;
            sp54.z = D_ctx_80177A48[3];

            Matrix_MultVec3f(gCalcMatrix, &sp54, &sp48);

            gCsCamEyeX = sp48.x;
            gCsCamEyeY = sp48.y;
            gCsCamEyeZ = player->pos.z + player->zPath + sp48.z;
            gCsCamAtX = player->pos.x;

            player->cam.at.x = gCsCamAtX;
            player->cam.at.y = gCsCamAtY = player->pos.y;
            player->cam.at.z = gCsCamAtZ = player->pos.z + player->zPath;

            Math_SmoothStepToF(&player->pos.y, D_ctx_80177A48[1], 0.1f, 50.0f, 0.0f);

            if (player->pos.y < 200.0f) {
                Math_SmoothStepToF(&player->unk_170, 1.0f, 1.0f, 0.2f, 0.0f);
                Math_SmoothStepToF(&player->unk_16C, 1.0f, 1.0f, 0.2f, 0.0f);
                Math_SmoothStepToF(&D_ctx_80177A48[1], 70.0f, 0.05f, 1.0f, 0.0f);
                Math_SmoothStepToF(&D_ctx_80177A48[3], 400.0f, 1.0f, 5.0f, 0.0f);

                if (D_ctx_80177A10[0] == 0) {
                    D_ctx_80177A10[0]++;
                    AUDIO_PLAY_SFX(NA_SE_TANK_GO_UP, player->sfxSource, 0);
                }
            }

            if (player->pos.y < 100.0f) {
                Effect_Effect359_Spawn(RAND_FLOAT_CENTERED(30.0f) + player->pos.x, 30.0f,
                                       RAND_FLOAT_CENTERED(30.0f) + player->trueZpos, RAND_FLOAT(2.0f) + 3.5f, 255, 12,
                                       1);
                Object_Kill(&gActors[3].obj, gActors[3].sfxSource);
            }

            Math_SmoothStepToF(&player->rockAngle, SIN_DEG(gGameFrameCount * 5.0f) * 10.0f, 0.1f, 100.0f, 0.0f);

            if (gCsFrameCount == 580) {
                gLevelStartStatusScreenTimer = 50;
                player->state = PLAYERSTATE_ACTIVE;
                player->csState = player->csTimer = player->csEventTimer = player->hideShadow = 0;
                player->gravity = 3.0f;
                player->unk_014 = 0.0f;
                D_ctx_8017782C = true;
                Play_InitEnvironment();
                D_ctx_8017782C = false;
                if ((gControllerHold[player->num].button & Z_TRIG) && (gControllerHold[player->num].button & R_TRIG)) {
                    Audio_KillSfxBySourceAndId(player->sfxSource, NA_SE_TANK_GO_UP);
                }
            }
            break;
    }

    player->pos.y += player->vel.y;
    player->vel.y -= player->gravity;
    player->pos.z += player->vel.z;
    player->trueZpos = player->pos.z;

    Math_SmoothStepToF(&player->cam.eye.x, gCsCamEyeX, D_ctx_80177A48[0], sp64, 0.00f);
    Math_SmoothStepToF(&player->cam.eye.y, gCsCamEyeY, D_ctx_80177A48[0], sp64, 0.00f);
    Math_SmoothStepToF(&player->cam.eye.z, gCsCamEyeZ, D_ctx_80177A48[0], sp64, 0.00f);
    Math_SmoothStepToF(&player->cam.at.x, gCsCamAtX, D_ctx_80177A48[0], sp64, 0.00f);
    Math_SmoothStepToF(&player->cam.at.y, gCsCamAtY, D_ctx_80177A48[0], sp64, 0.00f);
    Math_SmoothStepToF(&player->cam.at.z, gCsCamAtZ, D_ctx_80177A48[0], sp64, 0.00f);
}

void Titania_80188108(Actor* this, s32 index) {
    Player* player = &gPlayer[0];

    Actor_Initialize(this);
    this->obj.pos.x = D_i5_801B7318[index] + player->pos.x;
    this->obj.pos.y = D_i5_801B7328[index] + player->pos.y;
    this->obj.pos.z = D_i5_801B7338[index] + player->pos.z;

    this->fwork[7] = RAND_FLOAT(360.0f);
    this->fwork[8] = RAND_FLOAT(360.0f);

    this->vel.x = player->vel.x;
    this->vel.y = player->vel.y;
    this->vel.z = player->vel.z;

    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_ACTOR_CUTSCENE;
    this->obj.rot.y = 180.0f;

    Object_SetInfo(&this->info, this->obj.id);

    if (index < 3) {
        this->iwork[11] = 1;
        this->drawShadow = true;
        this->fwork[3] = D_i5_801B7348[index];
        this->state = 30;
        AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, this->sfxSource, 4);
    } else {
        this->animFrame = ACTOR_CS_GREAT_FOX;
        this->state = 20;
        AUDIO_PLAY_SFX(NA_SE_GREATFOX_ENGINE, this->sfxSource, 0);
        this->fwork[9] = 20.0f;
    }
}

void Titania_LevelComplete(Player* player) {
    f32 x;
    f32 camAtY = 0.0f;
    Vec3f src;
    Vec3f dest;
    s32 i;

    switch (player->csState) {
        case 0:
            gCsFrameCount = gBossActive = gLoadLevelObjects = 0;

            Play_ClearObjectData();

            player->csState = 1;

            D_ctx_80177A48[0] = 0.0f;
            D_ctx_80177A48[1] = 0.0f;
            D_ctx_80177A48[2] = 0.0f;
            D_ctx_80177A48[3] = 250.0f;

            player->gravity = 3.0f;

            Titania_80188108(&gActors[0], 0);

            if (gTeamShields[TEAM_ID_FALCO] > 0) {
                Titania_80188108(&gActors[1], 1);
            }
            if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                Titania_80188108(&gActors[2], 2);
            }

            Audio_KillSfxBySourceAndId(player->sfxSource, NA_SE_TANK_BURNER_HALF);

        case 1:
            Math_SmoothStepToF(D_ctx_80177A48, 0.1f, 1.0f, 0.01f, 0.0f);
            Math_SmoothStepToF(&player->baseSpeed, 4.9f, 0.1f, 1.0f, 0.0f);
            Math_SmoothStepToF(&player->camDist, 0.0f, 0.1f, 1.0f, 0.0f);

            if (gCsFrameCount < 1120) {
                Math_SmoothStepToF(&D_ctx_80177A48[1], 0.65f, 0.1f, 0.01f, 0.0f);
            } else {
                Math_SmoothStepToF(&D_ctx_80177A48[1], 0.0f, 0.1f, 0.02f, 0.0f);
            }

            D_ctx_80177A48[2] = D_ctx_80177A48[1] + D_ctx_80177A48[2];

            Matrix_RotateX(gCalcMatrix, -10.0f * M_DTOR, MTXF_NEW);
            Matrix_RotateY(gCalcMatrix, D_ctx_80177A48[2] * M_DTOR, MTXF_APPLY);

            src.x = 0.0f;
            src.y = 0.0f;
            src.z = D_ctx_80177A48[3];

            Matrix_MultVec3f(gCalcMatrix, &src, &dest);

            gCsCamEyeX = player->pos.x + dest.x;
            gCsCamEyeY = player->pos.y + dest.y;
            gCsCamEyeZ = player->pos.z + player->zPath + dest.z + 50.0f;

            if (gCsCamEyeY < 5.0f) {
                gCsCamEyeY = 5.0f;
            }

            gCsCamAtX = player->pos.x;
            gCsCamAtY = player->pos.y + 30.0f;
            gCsCamAtZ = player->pos.z + player->zPath;

            func_tank_80045130(player);
            func_tank_80044868(player);
            func_tank_80045678(player);
            func_tank_80045E7C(player);
            Player_CollisionCheck(player);
            Player_UpdatePath(player);

            if ((gGameFrameCount % 4) == 0) {
                f32 x;
                f32 y;
                f32 z;

                for (i = 0; i < 8; i++) {
                    x = D_i5_801B72B8[i].x;
                    y = D_i5_801B72B8[i].y + RAND_FLOAT_CENTERED(10.0f);
                    z = D_i5_801B72B8[i].z;

                    Effect_Effect359_Spawn(player->pos.x + x, player->pos.y + y, player->trueZpos + z,
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
            gCsCamAtZ = player->pos.z + player->zPath;

            if (player->pos.y < 100.0f) {
                camAtY = SIN_DEG(gGameFrameCount * 130.0f) * 3.0f;
            }

            Math_SmoothStepToF(&player->unk_170, 2.0f, 1.0f, 0.2f, 0.0f);
            Math_SmoothStepToF(&player->unk_16C, 2.0f, 1.0f, 0.2f, 0.0f);

            if (gCsFrameCount < 1470) {
                Effect_Effect359_Spawn(RAND_FLOAT_CENTERED(30.0f) + (player->pos.x + 30.0f), 30.0f,
                                       RAND_FLOAT_CENTERED(30.0f) + player->trueZpos, RAND_FLOAT(2.0f) + 3.5f, 255, 12,
                                       1);
            }

            Effect_Effect359_Spawn(RAND_FLOAT_CENTERED(30.0f) + (player->pos.x - 30.0f), 30.0f,
                                   RAND_FLOAT_CENTERED(30.0f) + player->trueZpos, RAND_FLOAT(2.0f) + 3.5f, 255, 12, 1);
            Math_SmoothStepToF(&player->rockAngle, SIN_DEG(gGameFrameCount * 6.0f) * 18.0f, 0.1f, 100.0f, 0.0f);
            Math_SmoothStepToF(&player->yBob, SIN_DEG(gGameFrameCount * 3.0f) * 5.0f, 0.1f, 100.0f, 0.0f);

            x = SIN_DEG(gGameFrameCount * 4.0f) * -1.5f;

            player->vel.x = x;
            player->vel.y += 0.1f;
            player->vel.z -= 0.17f;

            player->pos.x += x;
            player->pos.y += player->vel.y;
            player->pos.z += player->vel.z;

            player->trueZpos = player->pos.z;
            break;
    }

    switch (gCsFrameCount) {
        case 831:
            gShowLevelClearStatusScreen = true;
            break;

        case 1031:
            gShowLevelClearStatusScreen = false;
            break;

        case 50:
            AUDIO_PLAY_BGM(NA_BGM_COURSE_CLEAR);
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
            gSceneSetup = 5;
            break;

        case 1300:
            player->csState++;
            D_ctx_80177A48[0] = 0.0f;
            player->vel.z = 0.0f;
            player->vel.y = 0.0f;
            Titania_80188108(&gActors[3], 3);
            gProjectFar = 30000.0f;
            player->hideShadow = true;
            Audio_StopPlayerNoise(0);
            AUDIO_PLAY_SFX(NA_SE_TANK_GO_UP, player->sfxSource, 0);
            break;
    }

    Math_SmoothStepToF(&player->cam.eye.x, gCsCamEyeX, D_ctx_80177A48[0], 20000.0f, 0.00f);
    Math_SmoothStepToF(&player->cam.eye.y, gCsCamEyeY, D_ctx_80177A48[0], 20000.0f, 0.00f);
    Math_SmoothStepToF(&player->cam.eye.z, gCsCamEyeZ, D_ctx_80177A48[0], 20000.0f, 0.00f);
    Math_SmoothStepToF(&player->cam.at.x, gCsCamAtX, D_ctx_80177A48[0], 20000.0f, 0.00f);
    Math_SmoothStepToF(&player->cam.at.y, gCsCamAtY, D_ctx_80177A48[0], 20000.0f, 0.00f);
    Math_SmoothStepToF(&player->cam.at.z, gCsCamAtZ, D_ctx_80177A48[0], 20000.0f, 0.00f);

    player->cam.at.y += camAtY;

    if (gCsFrameCount == 1380) {
        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 60);
        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 60);
    }

    if (gCsFrameCount > 1440) {
        gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
        gFillScreenAlphaTarget = 255;

        if (gFillScreenAlpha == 255) {
            player->state = PLAYERSTATE_NEXT;
            gFadeoutType = 4;
            Play_ClearObjectData();
            Audio_FadeOutAll(10);
            gLeveLClearStatus[LEVEL_TITANIA] = Play_CheckMedalStatus(150) + 1;
        }
    }
}
