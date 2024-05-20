/*
 * File: fox_demo.c
 * System: Game Engine
 * Description: Starfox Cutscene Handler
 */

#include "global.h"
#include "assets/ast_aquas.h"
#include "assets/ast_great_fox.h"
#include "assets/ast_enmy_space.h"
#include "assets/ast_enmy_planet.h"
#include "assets/ast_ending.h"
#include "assets/ast_meteo.h"
#include "assets/ast_bolse.h"
#include "assets/ast_sector_x.h"
#include "assets/ast_sector_y.h"
#include "assets/ast_sector_z.h"
#include "assets/ast_title.h"
#include "assets/ast_katina.h"
#include "assets/ast_allies.h"

void func_demo_80048AC0(TeamId teamId) {
    s32 teamShield;

    if (teamId == TEAM_ID_FALCO) {
        if (gTeamShields[TEAM_ID_FALCO] < 64) {
            Radio_PlayMessage(gMsg_ID_20303, RCID_FALCO);
            return;
        }
        if ((s32) (Play_GetMaxShields() * 0.8f) < gPlayer[0].shields) {
            Radio_PlayMessage(gMsg_ID_20017, RCID_FALCO);
            return;
        }
        if ((s32) (Play_GetMaxShields() * 0.3f) < gPlayer[0].shields) {
            Radio_PlayMessage(gMsg_ID_20019, RCID_FALCO);
            return;
        }
        Radio_PlayMessage(gMsg_ID_20018, RCID_FALCO);
        return;
    }

    teamShield = gTeamShields[teamId];

    if (teamShield > 160) {
        switch (teamId) {
            case TEAM_ID_SLIPPY:
                Radio_PlayMessage(gMsg_ID_20011, RCID_SLIPPY);
                break;
            case TEAM_ID_PEPPY:
                Radio_PlayMessage(gMsg_ID_20012, RCID_PEPPY);
                break;
        }
    } else if (teamShield > 64) {
        switch (teamId) {
            case TEAM_ID_SLIPPY:
                Radio_PlayMessage(gMsg_ID_20013, RCID_SLIPPY);
                break;
            case TEAM_ID_PEPPY:
                Radio_PlayMessage(gMsg_ID_20014, RCID_PEPPY);
                break;
        }
    } else {
        switch (teamId) {
            case TEAM_ID_SLIPPY:
                Radio_PlayMessage(gMsg_ID_20015, RCID_SLIPPY);
                break;
            case TEAM_ID_PEPPY:
                Radio_PlayMessage(gMsg_ID_20016, RCID_PEPPY);
                break;
        }
    }
}

static Vec3f D_demo_800C9F60[] = {
    { 2000.0f, 2000.0f, 2000.0f },
    { -2000.0f, 2000.0f, 2000.0f },
    { 0.0f, -3000.0f, 3000.0f },
    { 5000.0f, -3000.0f, -3000.0f },
};
static f32 D_demo_800C9F90[] = { 75.0f, -80.0f, 85.0f, 0.0f };

void func_demo_80048CC4(Actor* actor, s32 arg1) {
    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_CUTSCENE;
    actor->obj.pos.x = D_demo_800C9F60[arg1].x + gPlayer[0].pos.x;
    actor->obj.pos.y = D_demo_800C9F60[arg1].y + gPlayer[0].pos.y;
    actor->obj.pos.z = D_demo_800C9F60[arg1].z + gPlayer[0].trueZpos;
    actor->rot_0F4.y = 0.0f;
    actor->rot_0F4.z = D_demo_800C9F90[arg1];
    Object_SetInfo(&actor->info, actor->obj.id);

    if (arg1 == 3) {
        AUDIO_PLAY_SFX(NA_SE_GREATFOX_ENGINE, actor->sfxSource, 0);
        AUDIO_PLAY_SFX(NA_SE_GREATFOX_BURNER, actor->sfxSource, 0);
        actor->animFrame = 1;
    } else {
        actor->iwork[11] = 1;
        AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, actor->sfxSource, 4);
    }
}

void Cutscene_WarpZoneComplete(Player* player) {
    Vec3f sp5C;
    Vec3f sp50;
    s32 pad[2];
    f32 temp_ft3;
    f32 temp_ret;
    s32 temp_v1;

    gBosses[1].obj.status = OBJ_FREE;
    Math_SmoothStepToF(&player->zRotBarrelRoll, 0.0f, 0.1f, 15.0f, 0.0f);
    Math_SmoothStepToF(&player->zRotBank, 0.0f, 0.1f, 15.0f, 0.0f);
    Math_SmoothStepToF(&player->rot.x, 0.0f, 0.1f, 3.0f, 0.0f);
    Math_SmoothStepToF(&player->rot.y, 0.0f, 0.1f, 3.0f, 0.0f);
    Math_SmoothStepToF(&player->rot.z, 0.0f, 0.1f, 3.0f, 0.0f);
    Math_SmoothStepToF(&player->camDist, 0.0f, 0.1f, 3.0f, 0.0f);
    Math_SmoothStepToF(&player->camRoll, 0.0f, 0.1f, 3.0f, 0.0f);
    Math_SmoothStepToAngle(&player->aerobaticPitch, 0.0f, 0.1f, 20.0f, 0.0f);
    Math_SmoothStepToF(&player->boostSpeed, 0.0f, 0.1f, 3.0f, 0.0f);

    switch (player->csState) {
        case 0:
            player->somersault = false;
            Audio_StopSfxByBankAndSource(1, player->sfxSource);
            player->csState++;
            D_ctx_80177A48[0] = 0.0f;
            D_ctx_80177A48[1] = 0.0f;
            D_ctx_80177A48[2] = 0.0f;
            player->wings.modelId = 1;
            gCsFrameCount = 0;
            /* fallthrough */
        case 1:
            D_ctx_80177A48[1] -= D_ctx_80177A48[2];
            Math_SmoothStepToF(&D_ctx_80177A48[2], 1.2f, 0.1f, 0.01f, 0.0f);
            Math_SmoothStepToF(&D_ctx_80177A48[0], 0.1f, 0.1f, 0.002f, 0.0f);
            Math_SmoothStepToF(&player->baseSpeed, 0.0f, 1.0f, 0.5f, 0.0f);
            Matrix_RotateX(gCalcMatrix, -5.0f * M_DTOR, MTXF_NEW);
            Matrix_RotateY(gCalcMatrix, D_ctx_80177A48[1] * M_DTOR, MTXF_APPLY);
            sp5C.x = 0.0f;
            sp5C.y = 0.0f;
            sp5C.z = 300.0f;
            Matrix_MultVec3f(gCalcMatrix, &sp5C, &sp50);
            gCsCamAtX = player->pos.x;
            gCsCamAtY = player->pos.y;
            gCsCamAtZ = player->trueZpos + gPathProgress;

            switch (gCsFrameCount) {
                case 101:
                    if (gTeamShields[TEAM_ID_FALCO] > 0) {
                        func_demo_80048CC4(&gActors[0], 0);
                    }
                    if (gTeamShields[TEAM_ID_SLIPPY] > 0) {
                        func_demo_80048CC4(&gActors[1], 1);
                    }
                    if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                        func_demo_80048CC4(&gActors[2], 2);
                    }
                    break;

                case 100:
                    gLevelClearScreenTimer = 100;
                    break;

                case 200:
                    gShowLevelClearStatusScreen = 1;
                    break;

                case 400:
                    gShowLevelClearStatusScreen = 0;
                    break;

                case 420:
                    gActors[0].state = 1;
                    break;

                case 430:
                    gActors[1].state = 1;
                    break;

                case 440:
                    gActors[2].state = 1;
                    break;

                case 450:
                    AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, player->sfxSource, 0);
                    player->unk_194 = 5.0f;
                    player->unk_190 = 5.0f;

                default:
                    break;
            }
            if (gCsFrameCount > 450) {
                Math_SmoothStepToF(&D_ctx_80177A48[0], 1.0f, 0.1f, 0.004f, 0.0f);
                player->baseSpeed += 2.0f;
                player->rot.x += 0.1f;
                player->unk_190 = 2.0f;

                if (gCsFrameCount == 530) {
                    Audio_FadeOutAll(50);
                }

                if (gCsFrameCount > 540) {
                    gFillScreenAlphaTarget = 255;
                    gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
                    gFillScreenAlphaStep = 8;
                    if (gFillScreenAlpha == 255) {
                        player->state_1C8 = PLAYERSTATE_1C8_NEXT;
                        player->csTimer = 0;
                        gFadeoutType = 4;
                        if (gCurrentLevel == LEVEL_METEO) {
                            gLeveLClearStatus[LEVEL_METEO] = Play_CheckMedalStatus(200) + 1;
                        } else {
                            gLeveLClearStatus[LEVEL_SECTOR_X] = Play_CheckMedalStatus(150) + 1;
                        }
                        gMissionStatus = MISSION_WARP;
                    }
                }
            } else {
                gCsCamEyeX = player->pos.x + sp50.x;
                gCsCamEyeY = player->pos.y + sp50.y;
                gCsCamEyeZ = player->trueZpos + gPathProgress + sp50.z;
            }

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

    sp5C.x = 0.0f;
    sp5C.y = 0.0f;
    sp5C.z = player->baseSpeed + player->boostSpeed;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp5C, &sp50);
    player->vel.x = sp50.x;
    player->vel.z = sp50.z;
    player->vel.y = sp50.y;

    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;
    player->pos.z += player->vel.z;

    player->trueZpos = player->pos.z + player->camDist;
    player->bankAngle = player->rot.z + player->zRotBank + player->zRotBarrelRoll;
    player->bobPhase += 10.0f;
    player->yBob = (-SIN_DEG(player->bobPhase)) * 0.3f;
    player->rockPhase += 8.0f;
    player->rockAngle = SIN_DEG(player->rockPhase);
}

static Vec3f D_demo_800C9FA0[] = {
    { 200.0f, -10.0f, 200.0f },
    { -200.0f, 20.0f, 200.0f },
    { 0.0f, 50.0f, 400.0f },
    { -2000.0f, -1000.0f, 0.0f },
};

void func_demo_80049630(ActorCutscene* this) {
    Vec3f sp3C;
    Vec3f sp30;

    switch (this->state) {
        case 0:
            this->vwork[0].x = gPlayer[0].pos.x + D_demo_800C9FA0[this->index].x;
            this->vwork[0].y = gPlayer[0].pos.y + D_demo_800C9FA0[this->index].y;
            this->vwork[0].z = gPlayer[0].pos.z + D_demo_800C9FA0[this->index].z;
            Math_SmoothStepToF(&this->obj.pos.x, this->vwork[0].x, 0.05f, 50.0f, 0.0001f);
            Math_SmoothStepToF(&this->obj.pos.y, this->vwork[0].y, 0.05f, 50.0f, 0.0001f);
            Math_SmoothStepToF(&this->obj.pos.z, this->vwork[0].z, 0.05f, 50.0f, 0.0001f);
            Math_SmoothStepToF(&this->rot_0F4.x, gPlayer[0].rot.x, 0.1f, 2.0f, 0.0001f);
            Math_SmoothStepToF(&this->rot_0F4.y, gPlayer[0].rot.y, 0.1f, 2.0f, 0.0001f);
            Math_SmoothStepToF(&this->rot_0F4.z, 0.0f, 0.05f, 0.2f, 0.0001f);
            break;

        case 1:
            this->state = 2;
            AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, this->sfxSource, 0);
            this->timer_0BC = 150;
            this->fwork[29] = 5.0f;

        case 2:
            this->iwork[11] = 2;
            this->fwork[0] += 2.0f;
            if (this->timer_0BC == 0) {
                Object_Kill(&this->obj, this->sfxSource);
            }
            break;
    }
    Matrix_RotateY(gCalcMatrix, (this->rot_0F4.y + 180.0f) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -(this->rot_0F4.x * M_DTOR), MTXF_APPLY);

    sp3C.x = 0.0f;
    sp3C.y = 0.0f;
    sp3C.z = this->fwork[0];

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp3C, &sp30);

    this->vel.x = sp30.x;
    this->vel.y = sp30.y;
    this->vel.z = sp30.z;

    this->obj.rot.x = -this->rot_0F4.x;
    this->obj.rot.y = this->rot_0F4.y + 180.0f;
    this->obj.rot.z = -this->rot_0F4.z;
}

void func_demo_8004990C(Player* player) {
    if (gGroundType == 0) {
        gPathTexScroll += 60.0f;
    }
    player->trueZpos = player->pos.z + player->camDist;
    player->bankAngle = player->rot.z + player->zRotBank + player->zRotBarrelRoll;
}

static f32 D_demo_800C9FD0[] = { -1200.0f, 1200.0f, 0.0f, 0.0f };
static f32 D_demo_800C9FE0[] = { 0.0f, 0.0f, 600.0f, 2000.0f };
static f32 D_demo_800C9FF0[] = { -100.0f, 0.0f, 100.0f, 500.0f };
static f32 D_demo_800CA000[] = { -150.0f, 150.0f, 0.0f, 0.0f };
static f32 D_demo_800CA010[] = { 0.0f, 0.0f, 80.0f, 1000.0f };
static f32 D_demo_800CA020[] = { 45.0f, -45.0f, 10.0f, 0.0f };
static s32 D_demo_800CA030[] = { 0, 0, 0, 1 };
static s32 D_demo_800CA040[] = { 0, 0, 0, 0 };

void func_demo_80049968(Actor* actor, s32 arg1) {
    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_CUTSCENE;
    actor->obj.pos.x = D_demo_800C9FD0[arg1];
    actor->obj.pos.y = D_demo_800C9FE0[arg1];
    actor->obj.pos.z = D_demo_800C9FF0[arg1] + gPlayer[0].trueZpos;
    actor->fwork[0] = D_demo_800CA000[arg1];
    actor->fwork[1] = D_demo_800CA010[arg1];
    actor->animFrame = D_demo_800CA030[arg1];
    actor->state = D_demo_800CA040[arg1];
    actor->obj.rot.z = D_demo_800CA020[arg1];
    actor->obj.rot.y = 180.0f;
    actor->vel.z = gPlayer[0].vel.z;
    Object_SetInfo(&actor->info, actor->obj.id);
    actor->iwork[11] = 1;
    AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, actor->sfxSource, 4);
}

void func_demo_80049A9C(Effect* effect, f32 x, f32 y, f32 z) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.id = OBJ_EFFECT_346;
    effect->timer_50 = 100;
    effect->scale2 = 0.2f;
    effect->obj.pos.x = x;
    effect->obj.pos.y = y;
    effect->obj.pos.z = z;
    effect->vel.z = 40.0f;
    effect->obj.rot.z = RAND_FLOAT(360.0f);
    Object_SetInfo(&effect->info, effect->obj.id);
}

void func_demo_80049B44(void) {
    s32 i;
    f32 x;
    f32 y;
    f32 z;

    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            x = RAND_FLOAT_CENTERED(400.0f);
            y = RAND_FLOAT_CENTERED(400.0f);
            z = -gPathProgress - 500.0f - RAND_FLOAT(500.0f);
            func_demo_80049A9C(&gEffects[i], x, y, z);
            break;
        }
    }
}

void Cutscene_EnterWarpZone(Player* player) {
    s32 var_v0;
    s32 pad[4];

    player->pos.x += player->vel.x;
    player->flags_228 = 0;
    player->alternateView = false;
    player->pos.y += player->vel.y;
    player->pos.z += player->vel.z;

    func_demo_8004990C(player);

    player->zPathVel = -player->vel.z;
    player->zPath += -player->vel.z;
    gPathProgress = player->zPath;

    Math_SmoothStepToF(&player->zRotBarrelRoll, 0.0f, 0.1f, 15.0f, 0.0f);
    Math_SmoothStepToF(&player->zRotBank, 0.0f, 0.1f, 15.0f, 0.0f);
    Math_SmoothStepToF(&player->rot.z, 0.0f, 0.1f, 5.0f, 0.0f);
    Math_SmoothStepToF(&player->rot.x, 0.0f, 0.1f, 5.0f, 0.0f);
    Math_SmoothStepToF(&player->rot.y, 0.0f, 0.1f, 5.0f, 0.0f);
    Math_SmoothStepToF(&player->pos.x, 0.0f, 0.1f, 50.0f, 0.0f);
    Math_SmoothStepToF(&player->pos.y, 0.0f, 0.1f, 50.0f, 0.0f);
    Math_SmoothStepToF(&player->cam.eye.x, 0.0f, 0.1f, 50.0f, 0.0f);
    Math_SmoothStepToF(&player->cam.eye.y, 0.0f, 0.1f, 50.0f, 0.0f);
    Math_SmoothStepToF(&player->cam.at.x, 0.0f, 0.1f, 50.0f, 0.0f);
    Math_SmoothStepToF(&player->cam.at.y, 0.0f, 0.1f, 50.0f, 0.0f);
    Math_SmoothStepToAngle(&player->aerobaticPitch, 0.0f, 0.1f, 20.0f, 0.0f);

    switch (player->csState) {
        case 0:
            player->somersault = false;
            gStarWarpDistortion = 100.0f;
            player->csState = 1;
            gStarCount = 1;
            gLoadLevelObjects = 0;
            player->vel.x = 0.0f;
            player->vel.y = 0.0f;
            player->vel.z = -500.0f;
            player->warpCamSpeed = -500.0f;

            if (gTeamShields[TEAM_ID_FALCO] > 0) {
                func_demo_80049968(&gActors[0], 0);
            }
            if (gTeamShields[TEAM_ID_SLIPPY] > 0) {
                func_demo_80049968(&gActors[1], 1);
            }
            if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                func_demo_80049968(&gActors[2], 2);
            }

            func_demo_80049968(&gActors[3], 3);
            player->csTimer = 50;
            break;

        case 1:
            Math_SmoothStepToF(&D_ctx_801779A8[player->num], 100.0f, 1.0f, 4.0f, 0.0f);
            Math_SmoothStepToF(&player->camRoll, 0.0f, 0.1f, 3.0f, 0.0f);
            gStarWarpDistortion *= 1.05f;
            if (player->csTimer == 0) {
                player->csState = 2;
                player->csTimer = 150;
            }
            player->unk_190 = 2.0f;
            player->camDist -= 2.0f;
            gBlurAlpha = 128;
            break;

        case 2:
            Math_SmoothStepToF(&D_ctx_801779A8[player->num], 100.0f, 1.0f, 3.0f, 0.0f);
            if (gStarWarpDistortion < 20000.0f) {
                gStarWarpDistortion *= 1.01f;
            }

            if (player->csTimer <= 100) {
                if (player->csTimer == 100) {
                    Play_PlaySfxFirstPlayer(player->sfxSource, NA_SE_ARWING_WARP_DASH);
                    player->unk_194 = 5.0f;
                    player->unk_190 = 5.0f;
                }

                player->camDist += player->warpCamSpeed;
                player->warpCamSpeed -= 100.0f;

                if (player->camDist < -15000.0f) {
                    player->camDist = 0.0f;
                    player->warpCamSpeed = 0.0f;
                    player->unk_234 = 0;
                }
            }
            var_v0 = 1;
            player->unk_190 = 2.0f;

            if ((player->csTimer == 95) && (gTeamShields[TEAM_ID_FALCO] > 0)) {
                gActors[0].state = var_v0;
                AUDIO_PLAY_SFX(NA_SE_ARWING_WARP_DASH, gActors[0].sfxSource, 0);
            }

            if ((player->csTimer == 90) && (gTeamShields[TEAM_ID_PEPPY] > 0)) {
                gActors[2].state = var_v0;
                AUDIO_PLAY_SFX(NA_SE_ARWING_WARP_DASH, gActors[2].sfxSource, 0);
            }

            if ((player->csTimer == 85) && (gTeamShields[TEAM_ID_SLIPPY] > 0)) {
                gActors[1].state = var_v0;
                AUDIO_PLAY_SFX(NA_SE_ARWING_WARP_DASH, gActors[1].sfxSource, 0);
            }

            if (player->csTimer == 60) {
                gActors[3].state = var_v0;
                AUDIO_PLAY_SFX(NA_SE_ARWING_WARP_DASH, gActors[3].sfxSource, 0);
                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 50);
                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 50);
            }

            if (player->csTimer == 50) {
                player->csState = 4;
                player->csTimer = 0;
            }
            break;

        case 4:
            Math_SmoothStepToF(&D_ctx_801779A8[player->num], 100.0f, 1.0f, 3.0f, 0.0f);
            player->camRoll -= 0.5f;
            if (player->csTimer == 0) {
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
                gFillScreenAlphaTarget = 255;
                gFillScreenAlphaStep = 8;
                if (gFillScreenAlpha == 255) {
                    Play_ClearObjectData();
                    player->csState = 5;
                    player->csTimer = 10;
                    player->camDist = -10000.0f;
                    player->xPath = player->xPathTarget = player->yPath = player->yPathTarget = player->pos.x =
                        player->pos.y = player->pos.z = player->zRotBarrelRoll = player->camRoll = player->trueZpos =
                            player->vel.z = player->zPath = gPathProgress = player->zPath = gSavedPathProgress =
                                gPathProgress = 0.0f;

                    player->meteoWarpTimer = gSavedHitCount = gObjectLoadIndex = gSavedObjectLoadIndex = 0;

                    player->unk_234 = 1;
                    gLevelPhase = 1;
                    gCamDistortion = 0.15f;
                    AUDIO_PLAY_SFX(NA_SE_WARP_OUT, gDefaultSfxSource, 0);
                    Play_InitLevel();
                }
            }
            break;

        case 5:
            Math_SmoothStepToF(&D_ctx_801779A8[player->num], 100.0f, 1.0f, 3.0f, 0.0f);
            if (player->csTimer == 0) {
                gFillScreenAlphaTarget = 0;
                gFillScreenAlphaStep = 8;
                if (gFillScreenAlpha == 0) {
                    player->csState = 6;
                    player->csTimer = 50;
                }
            }
            break;

        case 6:
            Math_SmoothStepToF(&gStarWarpDistortion, 0.0f, 0.2f, 1000.0f, 0.1f);
            Math_SmoothStepToF(&player->camDist, 0.0f, 0.2f, 500.0f, 0.1f);
            if (player->csTimer < 30) {
                for (var_v0 = 0; var_v0 < 3; var_v0++) {
                    func_demo_80049B44();
                }
            }

            if (player->csTimer == 30) {
                gStarCount = 300;
                AUDIO_PLAY_BGM(NA_BGM_STAGE_WZ);
            }

            if (player->csTimer == 0) {
                gWarpZoneBgAlpha = 0.0f;
                gStarWarpDistortion = 0.0f;
                player->state_1C8 = PLAYERSTATE_1C8_ACTIVE;
                player->unk_014 = 0.0f;
                player->unk_018 = 0.0f;
                gDrawSmallRocks = 0;
                gLoadLevelObjects = 1;
            }
            Math_SmoothStepToF(&player->cam.eye.y, (player->pos.y * player->unk_148) + 50.0f, 0.2f, 15.0f, 0.01f);
            Math_SmoothStepToF(&player->cam.at.y, (player->pos.y * player->unk_14C) + 20.0f, 0.2f, 15.0f, 0.01f);
            break;

        default:
            return;
    }
}

void Cutscene_LevelStart(Player* player) {
    gCsFrameCount++;
    if (gLevelMode == LEVELMODE_ON_RAILS) {
        switch (gCurrentLevel) {
            case LEVEL_CORNERIA:
                Corneria_LevelStart(player);
                Player_FloorCheck(player);
                break;

            case LEVEL_METEO:
                Meteo_LevelStart(player);
                break;

            case LEVEL_SECTOR_X:
                SectorX_LevelStart(player);
                break;

            case LEVEL_TITANIA:
                Titania_LevelStart(player);
                Player_FloorCheck(player);
                break;

            case LEVEL_ZONESS:
                Zoness_LevelStart(player);
                break;

            case LEVEL_MACBETH:
                Macbeth_LevelStart(player);
                break;

            case LEVEL_SECTOR_Y:
                SectorY_801A0AC0(player);
                break;

            case LEVEL_SOLAR:
                Solar_LevelStart(player);
                break;

            case LEVEL_VENOM_1:
                Venom1_LevelStart(player);
                Player_FloorCheck(player);
                break;

            case LEVEL_AQUAS:
                HUD_AquasStart(player);
                break;

            case LEVEL_AREA_6:
                Area6_LevelStart(player);
                break;
        }
        func_demo_8004990C(player);
    } else {
        switch (gCurrentLevel) {
            case LEVEL_FORTUNA:
                AllRange_FortunaIntro(player);
                Player_FloorCheck(player);
                break;

            case LEVEL_VENOM_2:
                Venom2_LevelStart(player);
                Player_FloorCheck(player);
                break;

            case LEVEL_BOLSE:
                Bolse_LevelStart(player);
                Player_FloorCheck(player);
                break;

            case LEVEL_KATINA:
                Katina_LevelStart(player);
                Player_FloorCheck(player);
                break;

            case LEVEL_SECTOR_Z:
                SectorZ_LevelStart(player);

            default:
                break;
        }
    }
}

static f32 D_demo_800CA050[] = { 210.0f, -210.0f, 0.0f };
static f32 D_demo_800CA05C[] = { -60.0f, -60.0f, -120.0f };
static f32 D_demo_800CA068[] = { -150.0f, -150.0f, -300.0f };
static f32 D_demo_800CA074[] = { 360.0f, -360.0f, 0.0f };

void func_demo_8004A700(Actor* actor, s32 arg1) {
    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_CUTSCENE;
    actor->obj.pos.x = gPlayer[0].pos.x;
    actor->obj.pos.y = gPlayer[0].pos.y - 1000.0f;
    actor->obj.pos.z = gPlayer[0].pos.z;
    actor->fwork[0] = D_demo_800CA050[arg1];
    actor->fwork[1] = D_demo_800CA05C[arg1];
    actor->fwork[2] = D_demo_800CA068[arg1];
    actor->fwork[3] = 4.0f;
    actor->fwork[7] = RAND_FLOAT(100.0f);
    actor->fwork[8] = RAND_FLOAT(100.0f);
    actor->obj.rot.z = D_demo_800CA074[arg1];
    actor->iwork[11] = 1;
    Object_SetInfo(&actor->info, actor->obj.id);
    AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, actor->sfxSource, 4);
}

void func_demo_8004A840(s32 actor) {
    func_demo_8004A700(&gActors[actor], actor);
}

void func_demo_8004A888(Effect* effect) {
    Vec3f sp2C;
    Vec3f sp20;

    Matrix_RotateY(gCalcMatrix, (gPlayer[0].rot.y + 180.0f) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -(gPlayer[0].rot.x * M_DTOR), MTXF_APPLY);
    Effect_Initialize(effect);

    effect->obj.status = OBJ_INIT;
    sp2C.x = RAND_FLOAT_CENTERED(1500.0f);
    sp2C.y = RAND_FLOAT_CENTERED(800.0f);
    sp2C.z = 3000.0f;

    Matrix_MultVec3f(gCalcMatrix, &sp2C, &sp20);

    effect->obj.pos.x = gPlayer[0].pos.x + sp20.x;
    effect->obj.pos.y = gPlayer[0].pos.y + sp20.y;
    effect->obj.pos.z = gPlayer[0].pos.z + sp20.z;
    sp2C.x = 0.0f;
    sp2C.y = 0.0f;
    sp2C.z = -80.0f;

    Matrix_MultVec3f(gCalcMatrix, &sp2C, &sp20);

    effect->vel.x = sp20.x;
    effect->vel.y = sp20.y;
    effect->vel.z = sp20.z;
    effect->obj.id = OBJ_EFFECT_352;
    effect->timer_50 = 40;
    effect->unk_46 = 144;
    effect->scale2 = RAND_FLOAT(30.0f) + 10.0f;

    if (Rand_ZeroOne() < 0.5f) {
        effect->obj.rot.z = 180.0f;
    }
    Object_SetInfo(&effect->info, effect->obj.id);
}

void func_demo_8004AA84(void) {
    s32 i;

    if (((gGameFrameCount % 8) == 0) && (gLevelType == LEVELTYPE_PLANET)) {
        for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
            if (gEffects[i].obj.status == OBJ_FREE) {
                func_demo_8004A888(&gEffects[i]);
                break;
            }
        }
    }
}

static f32 D_demo_800CA080[] = { -400.0f, 0.0f, 400.0f };
static f32 D_demo_800CA08C[] = { 0.0f, 200.0f, 0.0f };

void Cutscene_AllRangeMode(Player* player) {
    s32 pad;
    Vec3f sp70;
    Vec3f sp64;
    Actor* actor;
    f32 var_s1;
    f32 var_s2;
    f32 var_s3;
    s32 i;
    s32 pad1;
    s32 pad2;

    gCsFrameCount++;
    Math_SmoothStepToAngle(&player->aerobaticPitch, 0.0f, 0.1f, 20.0f, 0.0f);
    if (gCsFrameCount == 37) {
        gChangeTo360 = true;
        if (gCurrentLevel == LEVEL_VENOM_ANDROSS) {
            Radio_PlayMessage(gMsg_ID_19466, RCID_FOX);
            AUDIO_PLAY_BGM(NA_BGM_ANDROSS_BRAIN);
        } else if (gCurrentLevel != LEVEL_TRAINING) {
            Radio_PlayMessage(gMsg_ID_20180, RCID_FOX);
            if (gCurrentLevel == LEVEL_SECTOR_Y) {
                Audio_PlaySequence(SEQ_PLAYER_BGM, gBossBgms[gCurrentLevel], 0, 2);
            } else {
                AUDIO_PLAY_BGM(gBossBgms[gCurrentLevel]);
            }
        }
    }
    player->wings.unk_10 = 0.0f;
    player->wings.unk_08 = 0.0f;
    player->wings.unk_0C = 0.0f;
    player->wings.unk_04 = 0.0f;

    Math_SmoothStepToF(&player->rot.x, 0.0f, 0.1f, 5.0f, 0.0f);
    Math_SmoothStepToF(&player->rot.y, 0.0f, 0.1f, 5.0f, 0.0f);
    Math_SmoothStepToF(&player->rot.z, 0.0f, 0.1f, 1.0f, 0.0f);
    Math_SmoothStepToF(&player->zRotBank, 0.0f, 0.1f, 5.0f, 0.0f);
    Math_SmoothStepToF(&player->camRoll, 0.0f, 0.1f, 3.0f, 0.0f);
    Math_SmoothStepToF(&player->boostSpeed, 0.0f, 0.1f, 3.0f, 0.0f);
    Math_SmoothStepToF(&player->camDist, 0.0f, 0.1f, 3.0f, 0.0f);

    switch (player->csState) {
        case 0:
            Audio_PlayVoice(0);
            D_ctx_80177A48[0] = 0.005f;
            D_ctx_80177A48[1] = 0.0f;
            D_ctx_80177A48[2] = 60.0f;
            D_ctx_80177A48[3] = 0.0f;
            player->wings.modelId = 1;
            player->csState++;
            gCsFrameCount = 0;
            /* fallthrough */
        case 1:
            if (player->pos.y < 350.0f) {
                Math_SmoothStepToF(&player->pos.y, 350.0f, 0.1f, D_ctx_80177A48[3], 0.0f);
            }

            Math_SmoothStepToF(&D_ctx_80177A48[3], 10.0f, 1.0f, 1.0f, 0.0f);
            Math_SmoothStepToF(&D_ctx_80177A48[1], 360.0f, 0.05f, 1.5f, 0.0f);
            Math_SmoothStepToF(&D_ctx_80177A48[2], -70.0f, 0.1f, 0.7f, 0.0f);

            if (D_ctx_80177A48[1] > 220.0f) {
                player->unk_204 = 2;
            }

            if ((gCsFrameCount > 135) && (gCsFrameCount < 180)) {
                Math_SmoothStepToF(&D_ctx_801779A8[player->num], 30.0f, 1.0f, 10.0f, 0.0f);
            }

            if (gCsFrameCount == 138) {
                AUDIO_PLAY_SFX(NA_SE_WING_OPEN, player->sfxSource, 0);
            }

            if (gCsFrameCount == 190) {
                AUDIO_PLAY_SFX(NA_SE_WING_OPEN_END, player->sfxSource, 0);
            }

            if (D_ctx_80177A48[1] > 350.0f) {
                player->state_1C8 = PLAYERSTATE_1C8_ACTIVE;
                player->unk_014 = 0.0f;
                player->unk_018 = 0.1f;
                player->unk_194 = 10.0f;
                player->unk_190 = 10.0f;

                AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, player->sfxSource, 0);

                D_ctx_801779A8[player->num] = 70.0f;

                if ((gCurrentLevel != LEVEL_VENOM_ANDROSS) && (gCurrentLevel != LEVEL_TRAINING)) {
                    D_hud_800D1970 = 0;
                    for (i = 0, actor = &gActors[2]; i < 3; i++, actor++) {
                        Actor_Initialize(actor);
                        actor->obj.status = OBJ_INIT;
                        actor->obj.id = OBJ_ACTOR_TEAM_BOSS;
                        actor->obj.pos.x = D_demo_800CA080[i] + player->pos.x;
                        actor->obj.pos.y = D_demo_800CA08C[i] + player->pos.y;
                        actor->obj.pos.z = player->trueZpos - 1000.0f;
                        actor->rot_0F4.y = 180.0f;
                        Object_SetInfo(&actor->info, actor->obj.id);
                    }
                }
            }

            Matrix_RotateY(gCalcMatrix, D_ctx_80177A48[1] * M_DTOR, MTXF_NEW);
            Matrix_RotateX(gCalcMatrix, D_ctx_80177A48[2] * M_DTOR, MTXF_APPLY);

            sp70.x = 0.0f;
            sp70.y = 0.0f;
            sp70.z = 200.0f;

            Matrix_MultVec3f(gCalcMatrix, &sp70, &sp64);

            if ((gCurrentLevel == LEVEL_CORNERIA) || (gCurrentLevel == LEVEL_VENOM_ANDROSS)) {
                sp64.x *= -1.0f;
            }
            Math_SmoothStepToF(&D_ctx_80177A48[0], 0.1f, 1.0f, 0.005f, 0.0f);
            Math_SmoothStepToF(&player->cam.eye.x, player->pos.x + sp64.x, D_ctx_80177A48[0], 500.0f, 0.0f);
            Math_SmoothStepToF(&player->cam.eye.y, player->pos.y + sp64.y, D_ctx_80177A48[0], 500.0f, 0.0f);
            Math_SmoothStepToF(&player->cam.eye.z, player->trueZpos + gPathProgress + sp64.z, D_ctx_80177A48[0], 500.0f,
                               0.0f);
            Math_SmoothStepToF(&player->cam.at.x, player->pos.x, D_ctx_80177A48[0], 500.0f, 0.0f);
            Math_SmoothStepToF(&player->cam.at.y, player->pos.y, D_ctx_80177A48[0], 500.0f, 0.0f);
            Math_SmoothStepToF(&player->cam.at.z, player->trueZpos + gPathProgress, D_ctx_80177A48[0], 500.0f, 0.0f);
            break;
    }
    Matrix_RotateY(gCalcMatrix, (player->rot.y + 180.0f) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -(player->rot.x * M_DTOR), MTXF_APPLY);

    sp70.x = 0.0f;
    sp70.y = 0.0f;
    sp70.z = player->baseSpeed + player->boostSpeed;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp70, &sp64);

    player->vel.x = sp64.x;
    player->vel.z = sp64.z;
    player->vel.y = sp64.y;
    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;
    player->pos.z += player->vel.z;
    player->trueZpos = player->pos.z + player->camDist;
    player->cam.at.z += player->vel.z;
    player->cam.eye.z += player->vel.z;

    player->bankAngle = player->rot.z + player->zRotBank + player->zRotBarrelRoll;
    player->bobPhase += 10.0f;
    player->yBob = -SIN_DEG(player->bobPhase) * 0.3f;
    player->rockPhase += 8.0f;
    player->rockAngle = SIN_DEG(player->rockPhase);

    Player_FloorCheck(player);
}

void Cutscene_CoComplete2(Player* player) {
    s32 pad[5];
    Vec3f sp78;
    Vec3f sp6C;
    Vec3f sp60;
    Vec3f sp54;
    s32 pad2[2];
    f32 var_fa1;

    player->flags_228 = 0;

    Math_SmoothStepToF(&player->camRoll, 0.0f, 0.1f, 5.0f, 0.01f);

    switch (player->csState) {
        case 10:
            D_ctx_80177A48[2] = 0.0f;
            player->csState++;
            player->wings.unk_04 = 0.0f;
            player->wings.unk_0C = 0.0f;
            player->wings.unk_08 = 0.0f;
            player->wings.unk_10 = 0.0f;
            player->zRotBarrelRoll = 0.0f;
            player->zRotBank = 0.0f;
            player->boostSpeed = 0.0f;
            player->wings.modelId = 1;
            player->baseSpeed = 40.0f;
            /* fallthrough */

        case 11:
            D_ctx_80177A48[0] = 0.0f;
            Math_SmoothStepToAngle(&player->aerobaticPitch, 0.0f, 1.0f, 5.0f, 0.0f);
            player->cam.at.x += (gBossDeathCamAtX - player->cam.at.x) * 0.01f;
            player->cam.at.y += (gBossDeathCamAtY - player->cam.at.y) * 0.01f;
            player->cam.at.z += (gBossDeathCamAtZ - player->cam.at.z) * 0.01f;
            player->cam.eye.x += (player->cam.at.x + (500.0f * player->unk_004) - player->cam.eye.x) * 0.01f;
            player->cam.eye.y += (player->cam.at.y + 500.0f - player->cam.eye.y) * 0.01f;
            player->cam.eye.z += (gBossDeathCamAtZ + (2000.0f * D_ctx_80177950) - player->cam.eye.z) * 0.01f;

            if (player->csEventTimer > 25) {
                D_ctx_80177A48[2] += 1.5f * player->unk_004;
                Math_SmoothStepToF(&player->rot.z, player->unk_004 * -450.0f * D_ctx_80177950, 0.2f, 20.0f, 0.1f);
            } else {
                D_ctx_80177A48[2] += 0.25f * player->unk_004;
                if (player->rot.z < (-360.0f)) {
                    player->rot.z += 360.0f;
                }
                if (player->rot.z > 360.0f) {
                    player->rot.z -= 360.0f;
                }
                Math_SmoothStepToF(&player->rot.z, player->unk_004 * 20.0f * D_ctx_80177950, 0.1f, 3.0f, 0.1f);
            }

            if (D_ctx_80177950 > 0.0f) {
                Math_SmoothStepToF(&player->rot.y, 0.0f, 0.1f, 3.0f, 0.1f);
            } else {
                Math_SmoothStepToF(&player->rot.y, 180.0f, 0.1f, 3.0f, 0.1f);
                Math_SmoothStepToF(&player->pos.x, player->cam.eye.x, 1.0f, 30.0f, 0.0f);
                D_ctx_80177A48[2] = 0.0f;
            }

            player->pos.x += D_ctx_80177A48[2];
            Math_SmoothStepToF(&player->rot.x, 0.0f, 0.1f, 3.0f, 0.1f);
            Math_SmoothStepToF(&player->pos.y, player->cam.eye.y + 5.0f, 0.1f, 1.0f, 0.0f);

            if (player->csTimer == 0) {
                player->csState = 0;
                player->csTimer = 120;
                player->csEventTimer = 20;
                D_ctx_80177A48[0] = 0.001f;
                gCsCamEyeX = player->cam.eye.x;
                gCsCamEyeY = player->cam.eye.y;
                gCsCamEyeZ = player->cam.eye.z;
                gCsCamAtX = player->cam.at.x;
                gCsCamAtY = player->cam.at.y;
                gCsCamAtZ = player->cam.at.z;
            }
            break;

        case 0:
            if (player->csTimer > 60) {
                Math_SmoothStepToF(&player->rot.z, player->unk_004 * 60.0f * D_ctx_80177950, 0.1f, 4.0f, 0.1f);
            }
            if (player->csTimer < 80) {
                gCsCamAtX = player->pos.x;
                gCsCamAtY = player->pos.y;
                gCsCamAtZ = player->trueZpos + gPathProgress + 30.0f;
                Math_SmoothStepToF(&D_ctx_80177A48[0], 0.05f, 0.1f, 0.0005f, 0.0f);
            }

            Math_SmoothStepToF(&player->pos.x, player->cam.eye.x, 0.1f, 10.0f, 0.0f);
            gCsCamEyeY += ((player->cam.at.y + 500.0f) - player->cam.eye.y) * 0.01f;
            player->cam.eye.y = gCsCamEyeY;
            var_fa1 = player->unk_004 * 190.0f;

            if ((D_ctx_80177950 > 0.0f) && (player->unk_004 > 0.0f)) {
                var_fa1 = 181.0f;
            }
            if ((D_ctx_80177950 > 0.0f) && (player->unk_004 < 0.0f)) {
                var_fa1 = -181.0f;
            }
            if ((D_ctx_80177950 < 0.0f) && (player->unk_004 > 0.0f)) {
                var_fa1 = 0.0f;
            }
            if ((D_ctx_80177950 < 0.0f) && (player->unk_004 < 0.0f)) {
                var_fa1 = 360.0f;
            }
            if (player->csEventTimer == 0) {
                Math_SmoothStepToF(&player->rot.y, var_fa1, 0.1f, 4.0f, 0.0f);
            }

            player->vel.y = 0.0f;
            Math_SmoothStepToF(&player->pos.y, player->cam.eye.y + 5.0f, 0.1f, 4.0f, 0.0f);

            if (player->csTimer < 40) {
                Math_SmoothStepToF(&player->rot.z, player->unk_004 * 180.0f, 0.1f, 1.5f, 0.0f);
            }
            if (player->csTimer == 0) {
                player->csState = 1;
                player->csTimer = 150;
                player->wings.unk_10 = 0.0f;
                player->wings.unk_08 = 0.0f;
                player->wings.unk_0C = 0.0f;
                player->wings.unk_04 = 0.0f;
            }
            break;

        case 1:
            Math_SmoothStepToF(&D_ctx_80177A48[0], 1.0f, 0.1f, 0.05f, 0.0f);
            player->contrailScale += 0.04f;
            if (player->contrailScale > 0.6f) {
                player->contrailScale = 0.6f;
            }

            player->unk_000 += 0.005f;
            if (player->unk_000 > 0.3f) {
                player->unk_000 = 0.3f;
            }
            Math_SmoothStepToF(&gCsCamAtX, player->pos.x, D_ctx_80177A48[0], 50000.0f, 0.0f);
            Math_SmoothStepToF(&gCsCamAtY, player->pos.y, D_ctx_80177A48[0], 50000.0f, 0.0f);
            Math_SmoothStepToF(&gCsCamAtZ, player->trueZpos + gPathProgress + 30.0f, D_ctx_80177A48[0], 50000.0f, 0.0f);
            Math_SmoothStepToF(&player->pos.y, player->cam.eye.y + 5.0f, 0.1f, 4.0f, 0.0f);
            Math_SmoothStepToF(&player->rot.x, 20.0f, 0.1f, 0.2f, 0.01f);
            Math_SmoothStepToF(&player->pos.x, player->cam.eye.x, 0.1f, 2.0f, 0.0f);

            if (player->csTimer <= 110) {
                Math_SmoothStepToF(&player->rot.z, player->unk_004 * 360.0f, 0.1f, 2.5f, 0.0f);
            } else {
                Math_SmoothStepToF(&player->rot.z, player->unk_004 * 180.0f, 0.1f, 2.5f, 0.0f);
            }

            if ((180.0f - fabsf(player->rot.z)) <= 3.0f) {
                gGroundSurface = SURFACE_ROCK;
            }

            if (player->csTimer == 0) {
                player->csTimer = 200;
                player->csEventTimer = 500;
                player->csState = 2;
                player->unk_000 = player->unk_004 = player->unk_008 = gCOComplete2CamRotY = 0.0f;
                player->baseSpeed = 0.0f;
                D_ctx_80177A48[6] = 0.0f;
            }
            break;

        case 2:
            player->pos.y += 5.0f;
            Matrix_RotateY(gCalcMatrix, (player->rot.y + 180.0f + gCOComplete2CamRotY) * M_DTOR, MTXF_NEW);
            Matrix_RotateX(gCalcMatrix, -(player->rot.x * M_DTOR), MTXF_APPLY);
            Matrix_RotateZ(gCalcMatrix, -((player->bankAngle + player->rockAngle) * M_DTOR), MTXF_APPLY);

            sp78.x = 0;
            sp78.y = 70.0f;
            sp78.z = -800.0f;

            Matrix_MultVec3f(gCalcMatrix, &sp78, &sp6C);
            Math_SmoothStepToF(&gCsCamAtX, player->pos.x, D_ctx_80177A48[0], 50000.0f, 0.0f);
            Math_SmoothStepToF(&gCsCamAtY, player->pos.y - D_ctx_80177A48[6], D_ctx_80177A48[0], 50000.0f, 0.0f);
            Math_SmoothStepToF(&gCsCamAtZ, player->trueZpos + gPathProgress - D_ctx_80177A48[6], D_ctx_80177A48[0],
                               50000.0f, 0.0f);
            Math_SmoothStepToF(&D_ctx_80177A48[6], 130.0f, 0.1f, 0.25f, 0.0f);
            player->unk_000 += 0.002f;

            if (player->unk_000 > 0.3f) {
                player->unk_000 = 0.3f;
            }

            gCsCamEyeX += (player->pos.x + sp6C.x - gCsCamEyeX) * player->unk_000;
            gCsCamEyeY += (player->pos.y + sp6C.y - gCsCamEyeY) * player->unk_000;
            gCsCamEyeZ += (player->trueZpos + gPathProgress + sp6C.z - gCsCamEyeZ) * player->unk_000;
            gStarfieldScrollY += 0.2f;
            gStarfieldScrollX += 0.2f;
            gCOComplete2CamRotY += player->unk_008;
            Math_SmoothStepToAngle(&player->rot.z, 0.0f, 0.1f, 2.0f, 0.0f);

            if (player->csTimer == 0) {
                player->unk_008 += 0.01f;
                if (player->unk_008 > 0.63f) {
                    player->unk_008 = 0.63f;
                }
            } else {
                player->unk_008 -= 0.0005f;
                if (player->unk_008 < 0.0f) {
                    player->unk_008 = 0.0f;
                }
            }

            player->vel.y = 5.0f;

            if ((player->csTimer == 50) && (gTeamShields[TEAM_ID_FALCO] > 0)) {
                func_demo_8004A840(0);
            }

            if ((player->csTimer == 70) && (gTeamShields[TEAM_ID_SLIPPY] > 0)) {
                func_demo_8004A840(1);
            }

            if (player->csTimer == 90) {
                Play_ClearObjectData();
                if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                    func_demo_8004A840(2);
                }
                gGroundSurface = SURFACE_GRASS;
            }

            Matrix_RotateY(gCalcMatrix, (player->rot.y + 180.0f) * M_DTOR, MTXF_NEW);
            Matrix_RotateX(gCalcMatrix, -(player->rot.x * M_DTOR), MTXF_APPLY);
            Matrix_RotateZ(gCalcMatrix, -((player->bankAngle + player->rockAngle) * M_DTOR), MTXF_APPLY);

            if ((gCOComplete2CamRotY > 70.0f) && (gCOComplete2CamRotY < 280.0f)) {
                func_demo_8004AA84();
            }
            sp78.x = gActors[0].fwork[0] * gActors[0].fwork[3];
            sp78.y = gActors[0].fwork[1] * gActors[0].fwork[3];
            sp78.z = gActors[0].fwork[2] * gActors[0].fwork[3];

            Matrix_MultVec3f(gCalcMatrix, &sp78, &sp6C);

            gCsTeamTargetsX[0] = player->pos.x + sp6C.x;
            gCsTeamTargetsY[0] = player->pos.y + sp6C.y;
            gCsTeamTargetsZ[0] = player->trueZpos + sp6C.z;

            sp78.x = gActors[1].fwork[0] * gActors[1].fwork[3];
            sp78.y = gActors[1].fwork[1] * gActors[1].fwork[3];
            sp78.z = gActors[1].fwork[2] * gActors[1].fwork[3];

            Matrix_MultVec3f(gCalcMatrix, &sp78, &sp6C);

            gCsTeamTargetsX[1] = player->pos.x + sp6C.x;
            gCsTeamTargetsY[1] = player->pos.y + sp6C.y;
            gCsTeamTargetsZ[1] = player->trueZpos + sp6C.z;

            sp78.x = gActors[2].fwork[0] * gActors[2].fwork[3];
            sp78.y = gActors[2].fwork[1] * gActors[2].fwork[3];
            sp78.z = gActors[2].fwork[2] * gActors[2].fwork[3];

            Matrix_MultVec3f(gCalcMatrix, &sp78, &sp6C);

            gCsTeamTargetsX[2] = player->pos.x + sp6C.x;
            gCsTeamTargetsY[2] = player->pos.y + sp6C.y;
            gCsTeamTargetsZ[2] = player->trueZpos + sp6C.z;

            switch (gCsFrameCount) {
                case 330:
                    gLevelClearScreenTimer = 100;
                    break;

                case 410:
                    Radio_PlayMessage(gMsg_ID_2335, RCID_FOX);
                    break;

                case 550:
                    if ((gTeamShields[TEAM_ID_SLIPPY] == (-1)) || (gTeamShields[TEAM_ID_SLIPPY] == 0)) {
                        Radio_PlayMessage(gMsg_ID_20333, RCID_ROB64);
                    } else {
                        Radio_PlayMessage(gMsg_ID_2300, RCID_SLIPPY);
                    }
                    break;

                case 682:
                    if ((gTeamShields[TEAM_ID_PEPPY] == -1) || (gTeamShields[TEAM_ID_PEPPY] == 0)) {
                        Radio_PlayMessage(gMsg_ID_20332, RCID_ROB64);
                    } else {
                        Radio_PlayMessage(gMsg_ID_2310, RCID_PEPPY);
                    }
                    break;

                case 816:
                    if ((gTeamShields[TEAM_ID_FALCO] == -1) || (gTeamShields[TEAM_ID_FALCO] == 0)) {
                        Radio_PlayMessage(gMsg_ID_20331, RCID_ROB64);
                    } else {
                        Radio_PlayMessage(gMsg_ID_2320, RCID_FALCO);
                    }
                    break;
            }
            break;

        case 3:
            gStarfieldScrollY += 0.2f;
            gStarfieldScrollX += 0.2f;
            if (player->csTimer == 0) {
                player->csState = 4;
                player->csTimer = 30;
                player->unk_000 = 0.0f;
                player->unk_194 = 5.0f;
                player->unk_190 = 5.0f;
            }
            break;

        case 4:
            gStarfieldScrollY += 0.2f;
            gStarfieldScrollX += 0.2f;
            player->unk_190 = 2.0f;
            player->contrailScale += 0.1f;
            if (player->contrailScale > 0.6f) {
                player->contrailScale = 0.6f;
            }
            player->unk_000 += 1.0f;
            player->baseSpeed = SQ(player->unk_000);
            if (player->csTimer == 0) {
                D_ctx_80177A48[7] = player->vel.x;
                D_ctx_80177A48[8] = player->vel.y;
                D_ctx_80177A48[9] = player->vel.z;
                player->csState = 5;
                player->baseSpeed = 0.0f;
                player->csTimer = 10;
                func_effect_80078E50(player->pos.x, player->pos.y, player->trueZpos, 30.0f);
            }
            gCsCamAtX = player->pos.x;
            gCsCamAtY = player->pos.y - D_ctx_80177A48[6];
            gCsCamAtZ = player->trueZpos + gPathProgress - D_ctx_80177A48[6];
            break;

        case 5:
            gCsCamAtX += D_ctx_80177A48[7];
            gCsCamAtY += D_ctx_80177A48[8];
            gCsCamAtZ += D_ctx_80177A48[9];
            player->unk_234 = 0;
            if (player->csTimer == 0) {
                player->state_1C8 = PLAYERSTATE_1C8_NEXT;
                player->csTimer = 0;
                gFadeoutType = 4;
                Audio_FadeOutAll(10);
                gLeveLClearStatus[gCurrentLevel] = Play_CheckMedalStatus(150) + 1;
            }
            break;
    }

    switch (gCsFrameCount) {
        case 961:
            gShowLevelClearStatusScreen = 1;
            break;

        case 1161:
            gShowLevelClearStatusScreen = 0;
            break;

        case 1255:
            player->csState = 3;
            player->csTimer = 10;
            Play_PlaySfxFirstPlayer(player->sfxSource, NA_SE_ARWING_BOOST);
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 50);
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 50);
            break;
    }

    Matrix_RotateY(gCalcMatrix, (player->yRot_114 + player->rot.y + 180.0f) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -((player->xRot_120 + player->rot.x) * M_DTOR), MTXF_APPLY);

    sp60.x = 0.0f;
    sp60.y = 0.0f;
    sp60.z = player->baseSpeed;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp60, &sp54);

    player->vel.x = sp54.x;
    player->vel.z = sp54.z;
    player->vel.y = sp54.y;

    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;
    player->pos.z += player->vel.z;

    player->bankAngle = player->rot.z;
    player->trueZpos = player->pos.z;

    Math_SmoothStepToF(&player->cam.eye.x, gCsCamEyeX, D_ctx_80177A48[0], 50000.0f, 0);
    Math_SmoothStepToF(&player->cam.eye.y, gCsCamEyeY, D_ctx_80177A48[0], 50000.0f, 0);
    Math_SmoothStepToF(&player->cam.eye.z, gCsCamEyeZ, D_ctx_80177A48[0], 50000.0f, 0);
    Math_SmoothStepToF(&player->cam.at.x, gCsCamAtX, D_ctx_80177A48[0], 50000.0f, 0.f);
    Math_SmoothStepToF(&player->cam.at.y, gCsCamAtY, D_ctx_80177A48[0], 50000.0f, 0.f);
    Math_SmoothStepToF(&player->cam.at.z, gCsCamAtZ, D_ctx_80177A48[0], 50000.0f, 0.f);

    player->bobPhase += 10.0f;
    player->yBob = (-SIN_DEG(player->bobPhase)) * 0.3f;
    player->rockPhase += 8.0f;
    player->rockAngle = SIN_DEG(player->rockPhase);
}

void Cutscene_FortunaComplete(Player* player) {
    OvlI4_CallFunction(OVLCALL_FO_CS_COMPLETE, player);
}

void Cutscene_LevelComplete(Player* player) {
    s32 sp24;
    s32 sp20;
    s32 btn;

    gCsFrameCount++;

    switch (player->form) {
        case FORM_ARWING:
            if ((gCurrentLevel == LEVEL_VENOM_ANDROSS) || ((gCurrentLevel == LEVEL_VENOM_2) && (gLevelPhase == 1))) {
                Andross_80193C4C(player);
            } else if (gCurrentLevel == LEVEL_SECTOR_X) {
                if (gLevelPhase == 0) {
                    SectorX_LevelComplete(player);
                } else {
                    Cutscene_WarpZoneComplete(player);
                }
            } else if (gCurrentLevel == LEVEL_AREA_6) {
                Area6_LevelComplete(player);
            } else if (gCurrentLevel == LEVEL_FORTUNA) {
                Cutscene_FortunaComplete(player);
                Player_FloorCheck(player);
            } else if (gCurrentLevel == LEVEL_BOLSE) {
                Bolse_LevelComplete(player);
                Player_FloorCheck(player);
            } else if (gCurrentLevel == LEVEL_SECTOR_Z) {
                SectorZ_LevelComplete(player);
            } else if (gCurrentLevel == LEVEL_KATINA) {
                Katina_LevelComplete(player);
                Player_FloorCheck(player);
            } else if (gCurrentLevel == LEVEL_SECTOR_Y) {
                SectorY_LevelComplete(player);
                Player_FloorCheck(player);
            } else if (gCurrentLevel == LEVEL_SOLAR) {
                Solar_LevelComplete(player);
                Player_FloorCheck(player);
            } else if (gCurrentLevel == LEVEL_ZONESS) {
                Zoness_LevelComplete(player);
                Player_FloorCheck(player);
            } else if (gCurrentLevel == LEVEL_VENOM_2) {
                Venom2_LevelComplete(player);
                Player_FloorCheck(player);
            } else if (gCurrentLevel == LEVEL_METEO) {
                if (gLevelPhase == 0) {
                    Meteo_LevelComplete(player);
                } else {
                    Cutscene_WarpZoneComplete(player);
                }
            } else if ((gCurrentLevel == LEVEL_CORNERIA) && (gLevelMode == LEVELMODE_ALL_RANGE)) {
                Corneria_LevelComplete1(player);
                Player_FloorCheck(player);
            } else {
                if (gCsFrameCount == 170) {
                    AUDIO_PLAY_BGM(NA_BGM_COURSE_CLEAR);
                }
                Cutscene_CoComplete2(player);
                Player_FloorCheck(player);
            }
            Player_UpdateArwingRoll(player);
            break;

        case FORM_LANDMASTER:
            sp20 = gInputPress->button;
            sp24 = gInputHold->button;
            gInputPress->button = 0;
            btn = gInputPress->button;
            gInputHold->button = gInputPress->button;
            gInputPress->stick_y = btn;
            gInputPress->stick_x = btn;

            if (gCurrentLevel == LEVEL_TITANIA) {
                Titania_LevelComplete(player);
            } else if (gMissionStatus != MISSION_COMPLETE) {
                Macbeth_LevelComplete2(player);
            } else {
                Macbeth_LevelComplete1(player);
            }

            func_tank_80046358(player);
            gInputPress->button = sp20;
            gInputHold->button = sp24;
            break;

        case FORM_BLUE_MARINE:
            if (gCurrentLevel == LEVEL_AQUAS) {
                HUD_AquasComplete(player);
            }
            break;
    }
}

void Cutscene_UTurn(Player* player) {
    Vec3f sp58;
    PosRot sp50;

    Math_SmoothStepToF(&player->zRotBarrelRoll, 0.0f, 0.1f, 15.0f, 0.0f);
    Math_SmoothStepToF(&player->rot.z, 0.0f, 0.1f, 5.0f, 0.0f);
    Math_SmoothStepToF(&player->rot.y, 0.0f, 0.1f, 5.0f, 0.0f);
    Math_SmoothStepToF(&player->rot.x, 0.0f, 0.1f, 5.0f, 0.0f);
    Math_SmoothStepToF(&player->cam.eye.y, player->pos.y - 20.0f, 0.2f, 100.0f, 0.0f);

    sp50.rot.z = player->baseSpeed;
    sp58.x = Math_RadToDeg(Math_Atan2F(player->pos.x, player->trueZpos));

    player->boostCooldown = 1;
    player->boostMeter += 1.0f;

    if (player->boostMeter > 90.0f) {
        player->boostMeter = 90.0f;
    }

    switch (player->csState) {
        case 0:
            if (player->unk_19C != 0) {
                player->csTimer = 10;
            } else {
                player->csTimer = 30;
            }
            player->csState = 1;
            if (player->aerobaticPitch > 180.0f) {
                player->aerobaticPitch -= 360.0f;
            }
            /* fallthrough */

        case 1:
            if (player->csTimer == 0) {
                player->csState = 2;
                if (player->unk_19C != 0) {
                    player->csTimer = 60;
                } else {
                    player->csTimer = 80;
                }
            }
            player->cam.eye.x += player->vel.x * 0.2f;
            player->cam.eye.z += player->vel.z * 0.2f;
            Math_SmoothStepToF(&player->zRotBank, 0.0f, 0.1f, 15.0f, 0.0f);
            break;

        case 2:
            if (player->aerobaticPitch > 140.0f) {
                sp58.y = 0.0f;
            } else {
                sp58.y = 60.0f;
            }

            Math_SmoothStepToF(&player->wings.unk_04, sp58.y, 0.3f, 100.0f, 0.0f);
            Math_SmoothStepToF(&player->wings.unk_08, sp58.y, 0.3f, 100.0f, 0.0f);
            Math_SmoothStepToF(&player->wings.unk_0C, sp58.y, 0.3f, 100.0f, 0.0f);
            Math_SmoothStepToF(&player->wings.unk_10, sp58.y, 0.3f, 100.0f, 0.0f);
            Math_SmoothStepToF(&player->zRotBank, 0.0f, 0.1f, 15.0f, 0.0f);
            Math_SmoothStepToF(&player->aerobaticPitch, 190.0f, 0.1f, 6.0f, 0.001f);

            if (player->aerobaticPitch > 180.0f) {
                player->yRot_114 += 180.0f;
                if (player->yRot_114 >= 360.0f) {
                    player->yRot_114 -= 360.0f;
                }
                player->aerobaticPitch = 360.0f - (player->aerobaticPitch - 180.0f);
                if ((sp58.x - player->yRot_114) < 180.0f) {
                    player->zRotBank = 180.0f;
                } else {
                    player->zRotBank = -180.0f;
                }
                player->csState = 3;
                Player_PlaySfx(player->sfxSource, NA_SE_ARWING_BOOST, player->num);
                player->unk_194 = 7.0f;
                player->unk_190 = 7.0f;
            }
            player->unk_004 -= 0.2f;
            break;

        case 3:
            Math_SmoothStepToF(&player->zRotBank, 0.0f, 0.05f, 5.0f, 0.0f);

            sp58.y = player->zRotBank * 0.3f;

            Math_SmoothStepToF(&player->wings.unk_04, sp58.y, 0.3f, 100.0f, 0.0f);
            Math_SmoothStepToF(&player->wings.unk_08, sp58.y, 0.3f, 100.0f, 0.0f);

            sp58.z = -sp58.y;

            Math_SmoothStepToF(&player->wings.unk_0C, sp58.z, 0.3f, 100.0f, 0.0f);
            Math_SmoothStepToF(&player->wings.unk_10, sp58.z, 0.3f, 100.0f, 0.0f);

            player->unk_190 = 2.0f;
            player->cam.eye.x += player->vel.x * 0.1f;
            player->cam.eye.z += player->vel.z * 0.1f;

            if (player->unk_19C != 0) {
                player->cam.eye.x += player->vel.z * 0.2f;
                player->cam.eye.z += player->vel.x * 0.2f;
            }

            if (player->unk_19C == 0) {
                Math_SmoothStepToAngle(&player->yRot_114, sp58.x, 0.1f, 2.0f, 0.0f);
            }

            if (player->pos.y < player->pathHeight) {
                if (player->unk_004 < 0.0f) {
                    player->unk_004 += 0.2f;
                }
            } else {
                player->unk_004 -= 0.2f;
            }

            if (player->csTimer == 0) {
                player->state_1C8 = PLAYERSTATE_1C8_ACTIVE;
                player->unk_014 = 0.0f;
                player->unk_018 = 0.0f;
            }
            break;
    }
    player->pos.y += player->unk_004;
    player->cam.at.y += player->unk_004;
    player->bankAngle = player->rot.z + player->zRotBank + player->zRotBarrelRoll;

    Matrix_RotateY(gCalcMatrix, (player->yRot_114 + player->rot.y + 180.0f) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -((player->xRot_120 + player->rot.x + player->aerobaticPitch) * M_DTOR), MTXF_APPLY);

    sp50.rot.x = 0.0f;
    sp50.rot.y = 0.0f;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp50.rot, &sp50.pos);

    player->vel.x = sp50.pos.x;
    player->vel.z = sp50.pos.z;
    player->vel.y = sp50.pos.y;
    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;

    if (player->pos.y < player->pathFloor) {
        player->pos.y = player->pathFloor;
        player->vel.y = 0.0f;
    }
    player->pos.z += player->vel.z;
    player->trueZpos = player->pos.z;

    Player_ArwingBoost(player);
    Player_UpdateArwingRoll(player);
    Player_Shoot(player);
    Player_FloorCheck(player);
    Player_DamageEffects(player);
}

void func_demo_8004D3C8(s32 arg0) {
}

void Cutscene_DropVsItem(Player* player, ObjectId itemId, Item* item) {
    Item_Initialize(item);
    item->obj.status = OBJ_INIT;
    item->obj.pos.x = player->pos.x;
    item->obj.pos.y = player->pos.y;
    item->obj.pos.z = player->trueZpos;
    item->obj.id = itemId;
    Object_SetInfo(&item->info, item->obj.id);
}

void Cutscene_KillPlayer(Player* player) {
    s32 teamId;

    Audio_StopPlayerNoise(player->num);
    Audio_KillSfxBySourceAndId(player->sfxSource, NA_SE_ARWING_DOWN);
    Player_PlaySfx(player->sfxSource, NA_SE_ARWING_EXPLOSION, player->num);
    player->state_1C8 = PLAYERSTATE_1C8_NEXT;
    player->csTimer = 70;
    player->timer_224 = 20;
    gFadeoutType = 7;

    if (player->grounded) {
        player->unk_284 = 0;
    }

    if (!gVersusMode) {
        if (gCurrentLevel == LEVEL_VENOM_ANDROSS) {
            Radio_PlayMessage(gMsg_ID_20318, RCID_FOX);
        } else {
            if ((gCurrentLevel != LEVEL_TRAINING) &&
                ((gTeamShields[TEAM_ID_FALCO] > 0) || (gTeamShields[TEAM_ID_SLIPPY] > 0) ||
                 (gTeamShields[TEAM_ID_PEPPY] > 0))) {
                do {
                    teamId = RAND_INT(2.9f) + 1;
                } while (gTeamShields[teamId] <= 0);

                switch (teamId) {
                    case 1:
                        Radio_PlayMessage(gMsg_ID_20090, RCID_FALCO);
                        break;

                    case 2:
                        Radio_PlayMessage(gMsg_ID_20092, RCID_SLIPPY);
                        break;

                    case 3:
                        Radio_PlayMessage(gMsg_ID_20091, RCID_PEPPY);
                        break;
                }
            }
        }

        if (gCurrentLevel != LEVEL_TRAINING) {
            gLifeCount[gPlayerNum]--;
        }
    } else {
        if (player->attacker > 0) {
            gVsKills[player->attacker - 1][gVsPoints[player->attacker - 1]] = player->num;
            gVsPoints[player->attacker - 1]++;
            if (gVsPointsToWin == gVsPoints[player->attacker - 1]) {
                player->attacker = -1;
                if (player->unk_284 == 0) {
                    func_effect_8007C688(player->pos.x, player->pos.y, player->trueZpos, 3.0f, 1000);
                }
            }
        }
        if (gBombCount[gPlayerNum] != 0) {
            gBombCount[gPlayerNum] = 0;
            Cutscene_DropVsItem(player, OBJ_ITEM_BOMB, &gItems[1]);
        }
        if (gLaserStrength[gPlayerNum] != 0) {
            gLaserStrength[gPlayerNum] = 0;
            Cutscene_DropVsItem(player, OBJ_ITEM_LASERS, &gItems[0]);
        }
    }
}

void func_demo_8004D738(Player* player) {
    player->pos.y += 30.0f;
    func_effect_8007D0E0(player->pos.x, player->pos.y, player->trueZpos, 6.0f);
    if (gCamCount == 1) {
        func_effect_8007BFFC(player->pos.x, player->pos.y, player->trueZpos, 0.0f, 0.0f, 0.0f, 3.0f, 80);
        func_effect_8007C688(player->pos.x, player->pos.y, player->trueZpos, 3.0f, 800);
    } else {
        func_effect_8007BFFC(player->pos.x, player->pos.y, player->trueZpos, 0.0f, 0.0f, 0.0f, 3.0f, 10);
    }
    Cutscene_KillPlayer(player);
}

void func_demo_8004D828(Player* player) {
    s32 i;
    Vec3f src;
    Vec3f dest;

    Math_SmoothStepToF(&player->rot.x, 0.0f, 0.1f, 1.0f, 0.01f);
    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;

    if (!((gCurrentLevel == LEVEL_VENOM_1) && gBossActive) &&
        ((gLevelType == LEVELTYPE_PLANET) || (gCurrentLevel == LEVEL_BOLSE))) {
        player->vel.y -= 0.5f;
        player->rot.x -= 2.0f;
    }

    player->pos.z += player->vel.z;
    player->trueZpos = player->pos.z;
    player->bankAngle = player->rot.z + player->zRotBank + player->zRotBarrelRoll;
    player->zRotBank += 15.0f;

    if (player->csState != 0) {
        player->rot.y += 11.0f;
        player->rot.x += 17.0f;
    }

    if (gCamCount == 1) {
        if (((gGameFrameCount % 2) == 0)) {
            func_effect_8007D24C(RAND_FLOAT_CENTERED(20.0) + player->pos.x, RAND_FLOAT_CENTERED(20.0) + player->pos.y,
                                 player->trueZpos, 2.2f);
        }
    } else if (((gGameFrameCount % 4) == 0)) {
        func_effect_8007D10C(RAND_FLOAT_CENTERED(10.0f) + player->pos.x, RAND_FLOAT_CENTERED(10.0f) + player->pos.y,
                             RAND_FLOAT_CENTERED(10.0f) + player->trueZpos, 2.2f);
    }

    if ((player->pos.y < player->pathFloor) && (player->csState == 0)) {
        player->pos.y = player->pathFloor;
        player->unk_284 = 0;
        player->radioDamageTimer = 0;
        player->vel.y = 10.0f;
        player->csState = 1;

        Play_PlaySfxNoPlayer(player->sfxSource, NA_SE_EXPLOSION_S);

        if ((gCurrentLevel == LEVEL_CORNERIA) || (gCurrentLevel == LEVEL_FORTUNA)) {
            func_enmy_80062C38(player->pos.x, player->pos.z);
        } else {
            func_effect_8007D0E0(player->pos.x, player->pos.y, player->trueZpos, 3.0f);
        }

        if (player->wings.rightState == WINGSTATE_INTACT) {
            Play_SpawnDebris(1, player->hit1.x, player->hit1.y, player->hit1.z);
            player->wings.rightState = WINGSTATE_BROKEN;
            func_effect_8007D0E0(player->hit1.x, player->hit1.y, player->hit1.z, 2.0f);
        }
        if (player->wings.leftState == WINGSTATE_INTACT) {
            Play_SpawnDebris(0, player->hit2.x, player->hit2.y, player->hit2.z);
            player->wings.leftState = WINGSTATE_BROKEN;
            func_effect_8007D0E0(player->hit2.x, player->hit2.y, player->hit2.z, 2.0f);
        }
    } else if (((player->radioDamageTimer > 0) || (player->pos.y < player->pathFloor) ||
                (player->pos.y < gWaterLevel) || (player->csEventTimer == 0)) &&
               (player->csTimer == 0)) {
        if (gCamCount != 4) {
            if (player->unk_284 == 0) {
                func_effect_8007C688(player->pos.x, player->pos.y, player->trueZpos - (2.0f * player->vel.z), 3.0f, 80);
            }
            if (player->pos.y < player->pathFloor) {
                func_enmy_80062C38(player->pos.x, player->pos.z);
            }
        }
        if (gLevelType == LEVELTYPE_PLANET) {
            for (i = 0; i < 4; i++) {
                Play_SpawnDebris(2, player->pos.x, player->pos.y, player->trueZpos);
            }

            for (i = 0; i < 2; i++) {
                Play_SpawnDebris(3, player->pos.x, player->pos.y, player->trueZpos);
            }
        }
        func_effect_8007D0E0(player->pos.x, player->pos.y, player->trueZpos, 5.0f);
        func_effect_8007BFFC(player->pos.x, player->pos.y, player->trueZpos, player->vel.x, 0.0f, player->vel.z, 5.0f,
                             20);
        Cutscene_KillPlayer(player);
    }
    Math_SmoothStepToF(&player->camRoll, 0.0f, 0.05f, 5.0f, 0.00001f);
    Matrix_RotateY(gCalcMatrix, (player->yRot_114 + (player->damageShake * 0.2f)) * M_DTOR, MTXF_NEW);
    Math_SmoothStepToF(&player->unk_000, 700.0f, 0.05f, 10.0f, 0.00001f);

    src.x = player->unk_004 * (player->unk_000 * 0.7f);
    src.y = player->unk_000 * 0.5f;
    src.z = player->unk_000 + (400.0f - player->camDist);

    Matrix_MultVec3f(gCalcMatrix, &src, &dest);

    player->cam.eye.x = player->pos.x + dest.x;
    player->cam.eye.z = player->pos.z + dest.z;

    player->cam.at.x = player->pos.x;
    player->cam.at.z = player->pos.z;

    if ((gLevelType == LEVELTYPE_PLANET) || (gCurrentLevel == LEVEL_BOLSE)) {
        player->cam.eye.y = (player->pos.y * player->unk_148) + dest.y;
        player->cam.eye.y -= player->unk_02C - 50.0f;
        player->cam.at.y = (player->pos.y * player->unk_14C) + 20.0f + (player->xRock * 5.0f);
    } else {
        player->cam.eye.y = player->pos.y + dest.y;
        player->cam.at.y = player->pos.y;
    }

    if (gVersusMode != 0) {
        Player_CheckBounds360(player);
    }
}

void func_demo_8004DEF8(Player* player) {
    s32 i;

    if (player->rot.x < 0.0f) {
        player->rot.x += 1.0f;
    }
    if (player->rot.x > 0.0f) {
        player->rot.x -= 1.0f;
    }

    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;

    if (!((gCurrentLevel == LEVEL_VENOM_ANDROSS) && gBossActive) && (gLevelType == LEVELTYPE_PLANET)) {
        player->vel.y = player->vel.y - 0.5f;
    }

    player->pos.z += player->vel.z;
    player->trueZpos = player->pos.z + player->camDist;
    player->bankAngle = player->rot.z + player->zRotBank + player->zRotBarrelRoll;
    player->zRotBank = player->zRotBank + 15.0f;

    if (player->csState != 0) {
        player->rot.y += 14.0f;
        player->rot.x += 26.0f;
    }

    if (((gGameFrameCount % 2) == 0)) {
        func_effect_8007D24C(RAND_FLOAT_CENTERED(20.0) + player->pos.x, RAND_FLOAT_CENTERED(20.0) + player->pos.y,
                             player->trueZpos, 2.2f);
    }

    if ((player->pos.y < player->pathFloor) && (player->csState == 0)) {
        player->pos.y = player->pathFloor;
        player->radioDamageTimer = 0;
        player->vel.y = 10.0f;
        player->csState = 1;
        Play_PlaySfxNoPlayer(player->sfxSource, NA_SE_EXPLOSION_S);
        if (gCurrentLevel == LEVEL_CORNERIA) {
            func_enmy_80062C38(player->pos.x, player->pos.z);
        }

        if (player->wings.rightState == WINGSTATE_INTACT) {
            Play_SpawnDebris(1, player->hit1.x, player->hit1.y, player->hit1.z);
            player->wings.rightState = WINGSTATE_NONE;
            func_effect_8007D0E0(player->hit1.x, player->hit1.y, player->hit1.z, 2.0f);
        }

        if (player->wings.leftState == WINGSTATE_INTACT) {
            Play_SpawnDebris(0, player->hit2.x, player->hit2.y, player->hit2.z);
            player->wings.leftState = WINGSTATE_NONE;
            func_effect_8007D0E0(player->hit2.x, player->hit2.y, player->hit2.z, 2.0f);
        }
    } else if (((player->radioDamageTimer > 0) || (player->pos.y < player->pathFloor) || (player->csEventTimer == 0)) &&
               (player->csTimer == 0)) {
        if (player->pos.y < player->pathFloor) {
            func_effect_8007C688(player->pos.x, gGroundHeight + 20.0f, player->trueZpos - (2.0f * player->vel.z), 3.0f,
                                 800);
            func_enmy_80062C38(player->pos.x, player->pos.z);
        }
        func_effect_8007D0E0(player->pos.x, player->pos.y - (2.0f * player->vel.y),
                             player->trueZpos - (2.0f * player->vel.z), 6.0f);
        func_effect_8007BFFC(player->pos.x, player->pos.y - player->vel.y, player->trueZpos - (2.0f * player->vel.z),
                             0.0f, 0.0f, 0.0f, 3.0f, 20);
        if (gLevelType == LEVELTYPE_PLANET) {
            for (i = 0; i < 2; i++) {
                Play_SpawnDebris(2, player->pos.x, player->pos.y, player->trueZpos);
            }

            for (i = 0; i < 4; i++) {
                Play_SpawnDebris(4, player->pos.x, player->pos.y, player->trueZpos);
            }
        }
        Cutscene_KillPlayer(player);
    }

    player->camRoll -= 3.0f;

    if (player->csState != 0) {
        player->camRoll += 10.0f;
    }

    if ((gGroundSurface == SURFACE_WATER) && (player->pos.y <= player->pathFloor)) {
        func_effect_8007D9DC(player->pos.x, gGroundHeight + 2.0f, player->trueZpos, 3.0f, 20.0f, 0);
        func_effect_8007ADF4(player->pos.x, gGroundHeight, player->trueZpos, 0.1f, 2.0f);
    }
}

void Cutscene_PlayerDown(Player* player) {
    player->flags_228 = 0;
    player->barrelRollAlpha = 0;

    if ((gGameFrameCount % 2) != 0) {
        gControllerRumbleFlags[gPlayerNum] = 1;
    }

    switch (player->form) {
        case FORM_ARWING:
            if (gLevelMode == LEVELMODE_ALL_RANGE) {
                func_demo_8004D828(player);
            } else {
                func_demo_8004DEF8(player);
                Player_UpdatePath(player);
            }
            Player_CollisionCheck(player);
            Player_FloorCheck(player);
            break;

        case FORM_LANDMASTER:
            func_demo_8004D738(player);
            break;

        case FORM_BLUE_MARINE:
            Aquas_801AB9B0(player);
            break;

        case FORM_ON_FOOT:
            func_demo_8004D738(player);
            break;
    }
}

static f32 D_demo_800CA098[] = { 1.0f, -0.9f, 0.7f };
static f32 D_demo_800CA0A4[] = { 150.0f, 100.0f, 200.0f };
static f32 D_demo_800CA0B0[] = { 200.0f, 300.0f, 500.0f };

void func_demo_8004E4D4(ActorCutscene* this) {
    Vec3f sp54;
    Vec3f sp48;
    Vec3f sp3C;
    Player* sp38 = gPlayer;
    f32 sp34;

    this->fwork[7] += 3.0f;
    this->rot_0F4.z = SIN_DEG(this->fwork[7]) * 1.5f;
    this->fwork[8] += 2.0f;
    sp34 = SIN_DEG(this->fwork[8]) * 10.0f;

    switch (this->state) {
        case 0:
            Math_SmoothStepToF(&this->obj.rot.z, 0.0f, 0.05f, 1.0f, 0.0f);
            Math_SmoothStepToF(&this->obj.pos.x, this->fwork[0] + sp38->pos.x, 0.03f, 10.0f, 0.0f);
            Math_SmoothStepToF(&this->obj.pos.y, this->fwork[1] + sp38->pos.y + sp34, 0.03f, 10.0f, 0.0f);
            Math_SmoothStepToF(&this->obj.pos.z, this->fwork[2] + sp38->trueZpos, 0.03f, 10.0f, 0.0f);
            this->obj.rot.x = -sp38->rot.x;
            this->obj.rot.y = sp38->rot.y + 180.0f;
            break;

        case 1:
            this->state = 2;
            this->timer_0BC = 50;
            this->fwork[9] = 2.0f;
            AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, this->sfxSource, 0);
            this->fwork[29] = 5.0f;
            /* fallthrough */

        case 2:
            if (gLevelType == LEVELTYPE_PLANET) {
                this->fwork[21] += 0.4f;
                if (this->fwork[21] > 0.6f) {
                    this->fwork[21] = 0.6f;
                }
            }
            this->iwork[11] = 2;
            this->fwork[9] *= 1.2f;
            if (this->timer_0BC == 0) {
                Object_Kill(&this->obj, this->sfxSource);
            }
            break;

        case 10:
            this->state = 11;
            this->timer_0BC = 150;
            this->timer_0BE = 40;
            AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, this->sfxSource, 0);
            this->fwork[29] = 5.0f;
            /* fallthrough */
        case 11:
            this->iwork[11] = 2;
            this->fwork[9] += 2.0f;
            if (this->fwork[9] > 50.0f) {
                this->fwork[9] = 50.0f;
            }
            if (this->timer_0BE == 0) {
                switch (this->index) {
                    case 1:
                        this->obj.rot.y += 0.3f;
                        Math_SmoothStepToF(&this->obj.rot.z, -70.0f, 0.05f, 4.0f, 0.0f);
                        break;

                    case 2:
                        this->obj.rot.y -= 0.3f;
                        Math_SmoothStepToF(&this->obj.rot.z, 70.0f, 0.05f, 4.0f, 0.0f);
                        break;

                    case 3:
                        this->obj.rot.x -= 0.4f;
                        Math_SmoothStepToF(&this->obj.rot.z, 1000.0f, 0.05f, 6.0f, 0.0f);
                        break;
                }
            }

            if (this->timer_0BC == 0) {
                Object_Kill(&this->obj, this->sfxSource);
            }
            break;

        case 30:
            this->fwork[3] += D_demo_800CA098[this->index];

            Matrix_RotateY(gCalcMatrix, this->fwork[3] * M_DTOR, MTXF_NEW);

            sp54.x = 0.0f;
            sp54.y = D_demo_800CA0A4[this->index];
            sp54.z = D_demo_800CA0B0[this->index];

            Matrix_MultVec3f(gCalcMatrix, &sp54, &sp3C);

            this->fwork[0] = sp3C.x;
            this->fwork[1] = sp3C.y;
            this->fwork[2] = sp3C.z - 100.0f;

            Math_SmoothStepToF(&this->obj.rot.z, SIN_DEG(this->fwork[3]) * -30.0f, 0.1f, 2.0f, 0.0f);
            Math_SmoothStepToF(&this->obj.pos.x, this->fwork[0] + sp38->pos.x, 0.03f, 10.0f, 0.0f);
            Math_SmoothStepToF(&this->obj.pos.y, this->fwork[1] + sp38->pos.y + sp34, 0.03f, 10.0f, 0.0f);
            Math_SmoothStepToF(&this->obj.pos.z, this->fwork[2] + sp38->trueZpos, 0.03f, 10.0f, 0.0f);
            break;

        case 31:
            AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, this->sfxSource, 0);
            this->state++;
            this->fwork[29] = 5.0f;
            /* fallthrough */

        case 32:
            this->iwork[11] = 2;
            Math_SmoothStepToF(&this->obj.rot.x, -20.0f, 0.1f, 0.5f, 0.0f);
            Math_SmoothStepToF(&this->fwork[9], 25.0f, 0.1f, 2.0f, 0.0f);
            Math_SmoothStepToF(&this->obj.rot.z, 0.0f, 0.1f, 0.5f, 0.0f);
            break;
    }
    Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);

    sp54.x = 0.0f;
    sp54.y = 0.0f;
    sp54.z = this->fwork[9];

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp54, &sp48);

    this->vel.x = sp48.x;
    this->vel.y = sp48.y;
    this->vel.z = sp48.z;
}

void func_demo_8004EBD0(ActorCutscene* this) {
    Vec3f src;
    Vec3f dest;

    if (this->state < 4) {
        this->fwork[9] = 0.4f;

        this->obj.pos.x += (gCsTeamTargetsX[this->index] - this->obj.pos.x) * 0.4f;
        this->obj.pos.y += (gCsTeamTargetsY[this->index] - this->obj.pos.y) * 0.4f;
        this->obj.pos.z += (gCsTeamTargetsZ[this->index] - this->obj.pos.z) * 0.4f;

        this->obj.rot.z *= 0.98f;
        this->obj.rot.x = -gPlayer[0].rot.x;
        this->obj.rot.y = gPlayer[0].rot.y + 180.0f;

        if (1) {}

        this->fwork[7] += 1.0f;
        if (((s32) this->fwork[7] & 0x40) != 0) {
            this->fwork[0] += 0.1f;
        } else {
            this->fwork[0] -= 0.1f;
        }

        this->fwork[8] += 1.2f;
        if (((s32) this->fwork[8] & 0x40) != 0) {
            this->fwork[1] += 0.1f;
        } else {
            this->fwork[1] -= 0.1f;
        }
    }

    switch (this->state) {
        case 0:
            this->fwork[3] *= 0.992f;
            if (this->fwork[3] < 1.2f) {
                this->state++;
            }
            break;

        case 1:
            this->fwork[3] *= 0.997f;
            if (this->fwork[3] < 1.0f) {
                this->fwork[3] = 1.0f;
                this->state++;
            }
            this->timer_0BC = 560;
            break;

        case 2:
            if (this->timer_0BC == 110) {
                gPlayer[0].csTimer = 10000;
            }
            if (this->timer_0BC == 260) {
                gPlayer[0].csEventTimer = 10000;
            }
            if (this->timer_0BC == 0) {
                this->state++;
                this->timer_0BC = 10;
                Play_PlaySfxFirstPlayer(this->sfxSource, NA_SE_ARWING_BOOST);
                this->fwork[29] = 5.0f;
            }
            break;

        case 3:
            this->iwork[11] = 2;
            if (this->timer_0BC == 0) {
                this->state++;
                this->timer_0BC = 30;
            }
            break;

        case 4:
            this->fwork[21] += 0.4f;
            if (this->fwork[21] > 0.6f) {
                this->fwork[21] = 0.6f;
            }
            this->fwork[6] += 1.0f;

            Matrix_RotateY(gCalcMatrix, (gPlayer[0].rot.y + 180.0f) * M_DTOR, MTXF_NEW);
            Matrix_RotateX(gCalcMatrix, -(gPlayer[0].rot.x * M_DTOR), MTXF_APPLY);
            Matrix_RotateZ(gCalcMatrix, -((gPlayer[0].bankAngle + gPlayer[0].rockAngle) * M_DTOR), MTXF_APPLY);
            src.x = 0.0f;
            src.y = 0.0f;
            src.z = this->fwork[6] * this->fwork[6];

            Matrix_MultVec3f(gCalcMatrix, &src, &dest);

            this->vel.x = dest.x;
            this->vel.y = dest.y;
            this->vel.z = dest.z;

            if (this->timer_0BC == 0) {
                func_effect_80078E50(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 30.0f);
                Object_Kill(&this->obj, this->sfxSource);
            }
            break;
    }
    this->obj.pos.y += 5.0f;
    this->fwork[21] -= 0.02f;
    if (this->fwork[21] < 0.0f) {
        this->fwork[21] = 0.0f;
    }
}

void func_demo_8004F05C(Actor* actor) {
    if (((gLevelType == LEVELTYPE_PLANET) && (actor->animFrame == 0)) || (gCurrentLevel == LEVEL_BOLSE)) {
        actor->fwork[0] += 3.0f;
        actor->fwork[1] = SIN_DEG(actor->fwork[0]) * 1.5f;
    }

    switch (gCurrentLevel) {
        case LEVEL_BOLSE:
            switch (actor->animFrame) {
                case 0:
                    if (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_LEVEL_INTRO) {
                        actor->rot_0F4.z += actor->rot_0F4.y;
                        actor->vel.x = SIN_DEG(actor->rot_0F4.z) * 10.0f;
                        actor->obj.rot.z = SIN_DEG(actor->rot_0F4.z) * 40.0f;
                        break;
                    }

                    Math_SmoothStepToF(&actor->obj.rot.z, actor->fwork[1], 0.05f, 0.3f, 0.0f);

                    switch (actor->state) {
                        case 0:
                            break;

                        case 1:
                            actor->state = 2;
                            actor->timer_0BC = 100;
                            AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, actor->sfxSource, 0);
                            actor->fwork[29] = 5.0f;

                        case 2:
                            actor->iwork[11] = 2;
                            actor->vel.z -= 5.0f;
                            if (actor->timer_0BC == 0) {
                                Object_Kill(&actor->obj, actor->sfxSource);
                            }
                            break;
                    }
                    break;

                case 31:
                    if (actor->timer_0BC == 0) {
                        Object_Kill(&actor->obj, actor->sfxSource);
                    }
                    break;

                case 32:
                    actor->obj.rot.z += actor->rot_0F4.z;
                    if (actor->timer_0BC == 0) {
                        Object_Kill(&actor->obj, actor->sfxSource);
                    }
                    break;

                case 30:
                    break;
            }
            break;

        case LEVEL_AREA_6:
            Area6_8018DA58(actor);
            break;

        case LEVEL_SECTOR_Y:
            switch (actor->animFrame) {
                case 0:
                    SectorY_8019FF00(actor);
                    break;

                case 42:
                    if (actor->timer_0BC == 0) {
                        if (actor->obj.pos.x >= -3500.0f) {
                            if (actor->obj.pos.z <= 3000.0f) {
                                if ((fabsf(actor->obj.pos.y) <= 400.0f) && (gCsFrameCount <= 300)) {
                                    func_effect_8007D2C8(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, 8.0f);
                                }
                            }
                        }
                        Object_Kill(&actor->obj, actor->sfxSource);
                    }
                    break;

                case 43:
                    if (actor->timer_0BC == 0) {
                        Object_Kill(&actor->obj, actor->sfxSource);
                    }
                    break;
            }
            break;

        case LEVEL_SECTOR_X:
            if ((actor->state != 0) && (actor->state == 1)) {
                actor->vel.y += 0.1f;
                Math_SmoothStepToF(&actor->obj.rot.x, -20.0f, 0.1f, 0.5f, 0.0f);
            }
            break;

        case LEVEL_SECTOR_Z:
        case LEVEL_KATINA:
            break;

        default:
            switch (actor->state) {
                case 100:
                    Math_SmoothStepToF(&actor->obj.pos.x, actor->vwork[0x14].x, 0.03f, 3.0f, 0.0f);
                    Math_SmoothStepToF(&actor->obj.pos.y, actor->vwork[0x14].y, 0.03f, 2.0f, 0.0f);
                    Math_SmoothStepToF(&actor->obj.pos.z, actor->vwork[0x14].z, 0.03f, 2.0f, 0.0f);
                    Math_SmoothStepToF(&actor->obj.rot.z, 0.0f, 0.02f, 0.3f, 0);
                    break;

                case 0:
                    actor->obj.rot.z = actor->rot_0F4.z;
                    if (actor->animFrame == 10) {
                        actor->obj.pos.z = gPlayer[0].cam.eye.z + 12000.0f;
                    }
                    break;

                case 1:
                    actor->vel.y += 0.8f;
                    actor->vel.x += 0.8f;
                    Math_SmoothStepToF(&actor->obj.rot.z, 420.0f, 0.1f, 15.0f, 0.001f);
                    break;

                case 2:
                    actor->vel.y += 0.8f;
                    actor->vel.x -= 0.8f;
                    Math_SmoothStepToF(&actor->obj.rot.z, -420.0f, 0.1f, 15.0f, 0.001f);
                    break;

                case 3:
                    actor->vel.y += 1.2f;
                    actor->vel.z += 0.1f;
                    Math_SmoothStepToF(&actor->obj.rot.x, -45.0f, 0.1f, 15.0f, 0.001f);
                    break;

                case 10:
                    actor->vel.x -= 1.0f;
                    Math_SmoothStepToF(&actor->obj.rot.z, -45.0f, 0.05f, 0.5f, 0.0f);
                    break;

                case 11:
                    actor->vel.x -= 2.0f;
                    Math_SmoothStepToF(&actor->obj.rot.z, -70.0f, 0.1f, 6.0f, 0.0f);
                    Math_SmoothStepToF(&actor->obj.rot.y, 225.0f, 0.05f, 2.0f, 0.0f);
                    break;

                case 12:
                    actor->vel.x += 2.0f;
                    actor->vel.y += 1.0f;
                    Math_SmoothStepToF(&actor->obj.rot.z, 80.0f, 0.1f, 6.0f, 0.0f);
                    Math_SmoothStepToF(&actor->obj.rot.x, -15.0f, 0.05f, 4.0f, 0.0f);
                    Math_SmoothStepToF(&actor->obj.rot.y, 135.0f, 0.05f, 2.0f, 0.0f);
                    break;

                case 13:
                    actor->vel.y += 2.0f;
                    Math_SmoothStepToF(&actor->obj.rot.z, -400.0f, 0.2f, 14.0f, 0.0f);
                    Math_SmoothStepToF(&actor->obj.rot.x, -45.0f, 0.05f, 4.0f, 0.0f);
                    break;
            }
            break;
    }
}

void func_demo_8004F798(Actor* actor) {
    actor->iwork[11] = 2;

    switch (actor->state) {
        case 0:
            Math_SmoothStepToF(&actor->obj.pos.x, actor->fwork[0], 0.05f, 50.0f, 0.0f);
            Math_SmoothStepToF(&actor->obj.pos.y, actor->fwork[1], 0.05f, 50.0f, 0.0f);
            Math_SmoothStepToF(&actor->obj.rot.z, 0.0f, 0.05f, 1.0f, 0.0f);
            actor->obj.pos.z -= 2.0f;
            break;

        case 1:
            actor->fwork[29] = 10.0f;
            actor->vel.z -= 100.0f;
            if ((actor->obj.pos.z + gPathProgress) < -15000.0f) {
                Object_Kill(&actor->obj, actor->sfxSource);
            }
            break;
    }
}

void ActorCutscene_Update(ActorCutscene* this) {

    if (gCurrentLevel == LEVEL_AQUAS) {
        func_hud_80093164(this);
        return;
    }

    switch (gPlayer[0].state_1C8) {
        case PLAYERSTATE_1C8_LEVEL_COMPLETE:
            switch (gCurrentLevel) {
                case LEVEL_SECTOR_Y:
                    if (gPlayer[0].csState >= 3) {
                        SectorY_8019FF00(this);
                    }
                    break;

                case LEVEL_SOLAR:
                    if (gPlayer[0].csState >= 3) {
                        Solar_801A8BE8(this);
                    }
                    break;

                case LEVEL_ZONESS:
                    if (gPlayer[0].csState >= 3) {
                        Zoness_8019E5F0(this);
                    }
                    break;

                case LEVEL_VENOM_ANDROSS:
                case LEVEL_VENOM_2:
                    Andross_80195E44(this);
                    break;

                case LEVEL_KATINA:
                    Katina_SFTeamFlyTowardsCamera(this);
                    break;

                case LEVEL_SECTOR_Z:
                    SectorZ_8019DD20(this);
                    break;

                case LEVEL_AREA_6:
                    Area6_8018DA58(this);
                    break;

                case LEVEL_METEO:
                    if (gLevelPhase == 0) {
                        Meteo_8018ED9C(this);
                    } else {
                        func_demo_80049630(this);
                    }
                    break;

                case LEVEL_FORTUNA:
                    if (this->animFrame == 11) {
                        switch (this->state) {
                            case 0:
                                if (gCsFrameCount == 100) {
                                    this->state = 1;
                                    this->timer_0BC = 50;
                                    this->iwork[0] = 255;
                                    AUDIO_PLAY_SFX(NA_SE_EN_BOSS_EXPLOSION, this->sfxSource, 0);
                                }
                                break;

                            case 1:
                                Math_SmoothStepToF(&this->scale, 0.5f, 0.03f, 0.01f, 0.0f);
                                gFillScreenRed = gFillScreenAlpha = gFillScreenGreen = gFillScreenBlue = 0;

                                if ((this->timer_0BC == 43) || (this->timer_0BC == 46) || (this->timer_0BC == 49)) {
                                    gFillScreenAlpha = 192;
                                    gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
                                }

                                this->iwork[0] -= 2;
                                if (this->iwork[0] < 0) {
                                    this->iwork[0] = 0;
                                    this->scale = 0.0f;
                                }

                                gLight3Brightness = this->iwork[0] / 255.0f;
                                gLight3x = gActors[0].obj.pos.x + 10.0f;
                                gLight3y = gActors[0].obj.pos.y - 40.0f;
                                gLight3z = gActors[0].obj.pos.z - 70.0f;
                                gLight3R = 255;
                                gLight3G = 255;
                                gLight3B = 80;
                                break;
                        }
                    }
                    break;

                case LEVEL_CORNERIA:
                    if (gLevelMode == LEVELMODE_ALL_RANGE) {
                        func_demo_8004E4D4(this);
                    } else {
                        func_demo_8004EBD0(this);
                    }
                    break;

                case LEVEL_SECTOR_X:
                    if (gLevelPhase != 0) {
                        func_demo_80049630(this);
                    } else {
                        func_demo_8004E4D4(this);
                    }
                    break;

                case LEVEL_TITANIA:
                    func_demo_8004E4D4(this);
                    break;

                case LEVEL_MACBETH:
                    Macbeth_801B28BC(this);
                    break;

                case LEVEL_BOLSE:
                    func_demo_8004F05C(this);
                    break;

                default:
                    func_demo_8004EBD0(this);
                    break;
            }
            break;

        case PLAYERSTATE_1C8_LEVEL_INTRO:
            func_demo_8004F05C(this);
            break;

        case PLAYERSTATE_1C8_ENTER_WARP_ZONE:
            func_demo_8004F798(this);
            break;

        case PLAYERSTATE_1C8_STANDBY:
            if (gCurrentLevel == LEVEL_SECTOR_Y) {
                SectorY_8019FF00(this);
            }
            break;
    }
}

static Vec3f D_demo_800CA0BC[] = {
    { -1373.0, 484.0, -374.0 },
    { 1373.0, 484.0, -374.0 },
    { -1373.0, -704.0, -374.0 },
    { 1373.0, -704.0, -374.0 },
};
static Vec3f D_demo_800CA0EC[] = {
    { 0.0, 40.0, -2278.0 },
    { 295.0, -92.0, -1301.0 },
    { -295.0, -92.0, -1301.0 },
};
static Vec3f D_demo_800CA110[8] = {
    { 170.0f, -35.0f, -380.0f },   { -170.0f, -40.0f, -380.0f }, { 170.0f, -130.0f, -380.0f },
    { -170.0f, -140.0f, -380.0f }, { 140.0f, 40.0f, -250.0f },   { -150.0f, 40.0f, -250.0f },
    { 140.0f, 0.0f, -250.0f },     { -150.0f, 0.0f, -250.0f },
};
static f32 D_demo_800CA170[] = {
    0.15f, 0.45f, 0.75f, 1.3f, 0.75f, 0.45f, 0.15f, 0.0f,
};
static f32 D_demo_800CA190[] = { 5.0f, 5.2f };
static f32 D_demo_800CA198[] = {
    0.5f, 1.5f, 2.5f, 1.5f, 0.5f, 0.2f, 0.2f,
};
static f32 D_demo_800CA1B4[] = {
    -30.0f, -60.0f, -90.0f, -120.0f, -150.0f, -180.0f, -200.0, -210.0,
};
static f32 D_demo_800CA1D4[] = {
    1.5f, 0.87f, 0.83f, 0.75f, 0.7f, 0.6f, 0.4f, 0.1f,
};
static Animation* D_demo_800CA1F4[] = {
    &D_SY_60265B4, &D_SY_602B8DC, &D_SY_60034C4, &D_SY_602A2CC, &D_SY_602CEB4, &D_SY_602B778, &D_SY_601F3B8,
};

void func_demo_8004FCB8(Actor* actor, s32 arg1) {
    f32 angle;
    f32 scale;
    s32 i;

    if (actor->timer_0BC == 0) {
        actor->timer_0BC = 32;
        actor->fwork[5] = 0.3f;
    }

    if (actor->fwork[5] > 0.0f) {
        scale = actor->fwork[5];
        actor->fwork[5] -= 0.05f;
        RCP_SetupDL_49();
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
        gDPSetEnvColor(gMasterDisp++, 16, 16, 240, 255);
        angle = Math_Atan2F(gPlayer[0].cam.eye.x - gPlayer[0].cam.at.x, gPlayer[0].cam.eye.z - gPlayer[0].cam.at.z);

        for (i = arg1; i < (arg1 + 4); i++) {
            Matrix_Pop(&gGfxMatrix);
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, D_demo_800CA110[i].x + actor->obj.pos.x,
                             D_demo_800CA110[i].y + actor->obj.pos.y, D_demo_800CA110[i].z + actor->obj.pos.z,
                             MTXF_APPLY);
            Matrix_RotateY(gGfxMatrix, angle, MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, scale, scale, scale, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_1024AC0);
        }
    }
}

void ActorCutscene_Draw(Actor* actor) {
    static f32 D_800CA210 = 0.0f;
    static f32 D_800CA214 = 0.0f;
    static f32 D_800CA218 = 0.0f;
    f32 sp2DC;
    f32 sp2D8;
    f32 sp2D4;
    s32 sp2D0;
    s32 pad2C4[3];
    Vec3f sp2B8;
    Vec3f sp2AC;
    Vec3f sp144[30];
    s32 pad[3];
    s32 animFrameData;
    f32 camX;
    f32 camY;
    f32 camZ;
    f32 y;
    f32 x;

    switch (actor->animFrame) {
        case 1000:
            RCP_SetupDL(&gMasterDisp, SETUPDL_45);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, actor->unk_046);
            gSPDisplayList(gMasterDisp++, D_ENMY_PLANET_40018A0);

            if (actor->unk_046 > 50) {
                Actor_DrawEngineAndContrails(actor);
            }
            break;

        case 0:
            func_edisplay_8005B388(actor);
            break;

        case 1:
            if (gCurrentLevel == LEVEL_SECTOR_Z) {
                gSPFogPosition(gMasterDisp++, gFogNear, 1005);
            }
            actor->info.bonus = 1;
            Cutscene_DrawGreatFox();
            break;

        case 10:
            RCP_SetupDL_40();
            Matrix_Scale(gGfxMatrix, 60.0f, 60.0f, 1.0f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_ME_6020810);
            break;

        case 11:
            RCP_SetupDL_64_2();
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
            Matrix_Scale(gGfxMatrix, 60.0f, 60.0f, 1.0f, MTXF_APPLY);
            Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, 10.0f, MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, actor->scale, actor->scale, 1.0f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);

            RCP_SetupDL_49();
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, actor->iwork[0]);
            gDPSetEnvColor(gMasterDisp++, 255, 255, 00, actor->iwork[0]);
            gSPDisplayList(gMasterDisp++, D_1024AC0);
            break;

        case 20:
            gSPDisplayList(gMasterDisp++, D_ENMY_SPACE_400AAE0);
            break;

        case 24:
            gSPDisplayList(gMasterDisp++, D_D009A40);
            Actor_DrawEngineAndContrails(actor);
            break;

        case 25:
            if ((actor->index % 2) != 0) {
                gSPDisplayList(gMasterDisp++, D_SZ_6001DA0);
            } else {
                gSPDisplayList(gMasterDisp++, D_SZ_6001360);
            }
            break;

        case 26:
            gSPDisplayList(gMasterDisp++, D_SZ_6004FE0);
            Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -60.0f, MTXF_APPLY);
            Actor_DrawEngineGlow(actor, 2);
            break;

        case 28:
            gSPDisplayList(gMasterDisp++, D_ENMY_SPACE_400AAE0);
            Matrix_Translate(gGfxMatrix, 0.f, 0.f, -60.0f, MTXF_APPLY);
            Actor_DrawEngineGlow(actor, 2);
            break;

        case 30:
            Display_SetSecondLight(&actor->obj.pos);

            if (actor->unk_046 != 0) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_55);
                gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                Rand_SetSeed(1, 29000, 9876);

                for (sp2D0 = 0; sp2D0 < 30; sp2D0++) {
                    Matrix_Push(&gGfxMatrix);
                    Matrix_Translate(gGfxMatrix, RAND_FLOAT_CENTERED_SEEDED(3000.0f) * actor->fwork[20],
                                     RAND_FLOAT_CENTERED_SEEDED(3000.0f) * actor->fwork[20],
                                     RAND_FLOAT_CENTERED_SEEDED(3000.0f) * actor->fwork[20], MTXF_APPLY);
                    Matrix_RotateY(gGfxMatrix, 2.0f * RAND_FLOAT_SEEDED(M_PI), MTXF_APPLY);
                    Matrix_RotateZ(gGfxMatrix, (2.0f * gGameFrameCount) * M_DTOR, MTXF_APPLY);
                    Matrix_RotateX(gGfxMatrix, 2.0f * RAND_FLOAT_SEEDED(M_PI), MTXF_APPLY);

                    switch ((s32) (sp2D0 % 4U)) {
                        case 0:
                            Matrix_Scale(gGfxMatrix, 1.0f, 0.3f, 1.0f, MTXF_APPLY);
                            break;

                        case 1:
                            Matrix_Scale(gGfxMatrix, 0.3f, 1.0f, 1.0f, MTXF_APPLY);
                            break;

                        case 2:
                            Matrix_Scale(gGfxMatrix, 1.0f, 0.5f, 1.0f, MTXF_APPLY);
                            break;

                        case 3:
                            Matrix_Scale(gGfxMatrix, 0.5f, 1.0f, 1.0f, MTXF_APPLY);
                            break;
                    }

                    Matrix_Scale(gGfxMatrix, RAND_FLOAT_SEEDED(8.0f) + 8.0f, RAND_FLOAT_SEEDED(8.0f) + 8.0f, 10.0f,
                                 MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_1021E20);
                    Matrix_Pop(&gGfxMatrix);
                }

                break;
            }

            if (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_LEVEL_INTRO) {
                Matrix_Push(&gGfxMatrix);
                Matrix_RotateX(gGfxMatrix, 20.0f * M_DTOR, MTXF_APPLY);
                Matrix_RotateY(gGfxMatrix, (gGameFrameCount * 0.5f) * M_DTOR, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, 2.0f, 2.0f, 2.0f, MTXF_APPLY);
            } else {
                Matrix_RotateX(gGfxMatrix, -10.0f * M_DTOR, MTXF_APPLY);
                Matrix_RotateY(gGfxMatrix, (gGameFrameCount * 0.3f) * M_DTOR, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, 4.0f, 4.0f, 4.0f, MTXF_APPLY);
                Matrix_Push(&gGfxMatrix);
            }

            Matrix_Translate(gGfxMatrix, 0.f, -590.0f, 0.f, MTXF_APPLY);

            Matrix_SetGfxMtx(&gMasterDisp);

            gSPDisplayList(gMasterDisp++, D_BO_600BAA0);

            Matrix_Push(&gGfxMatrix);

            RCP_SetupDL(&gMasterDisp, SETUPDL_64);

            switch ((gGameFrameCount >> 3) % 4U) {
                case 0:
                    sp2DC = 255.0f;
                    sp2D8 = 0.0f;
                    sp2D4 = 0.0f;
                    break;

                case 1:
                    sp2DC = 0.0f;
                    sp2D8 = 255.0f;
                    sp2D4 = 0.0f;
                    break;

                case 2:
                    sp2DC = 0.0f;
                    sp2D8 = 0.0f;
                    sp2D4 = 255.0f;
                    break;

                case 3:
                    sp2DC = 255.0f;
                    sp2D8 = 255.0f;
                    sp2D4 = 0.0f;
                    break;
            }

            Math_SmoothStepToF(&D_800CA210, sp2DC, 1.0f, 20.0f, 0);
            Math_SmoothStepToF(&D_800CA214, sp2D8, 1.0f, 20.0f, 0);
            Math_SmoothStepToF(&D_800CA218, sp2D4, 1.0f, 20.0f, 0);

            gDPSetPrimColor(gMasterDisp++, 0, 0, (s32) D_800CA210, (s32) D_800CA214, (s32) D_800CA218, 128);

            if (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_LEVEL_INTRO) {
                Matrix_Scale(gGfxMatrix, 1.02f, 1.02f, 1.02f, MTXF_APPLY);
            } else {
                Matrix_Scale(gGfxMatrix, 0.97f, 0.97f, 0.97f, MTXF_APPLY);
            }

            Matrix_SetGfxMtx(&gMasterDisp);

            gDPSetTextureFilter(gMasterDisp++, G_TF_POINT);
            gSPDisplayList(gMasterDisp++, D_BO_6000D80);
            gDPSetTextureFilter(gMasterDisp++, G_TF_BILERP);

            Matrix_Pop(&gGfxMatrix);
            Matrix_Pop(&gGfxMatrix);

            if (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_LEVEL_COMPLETE) {
                Matrix_Scale(gGfxMatrix, 0.075f, 0.075f, 0.075f, MTXF_APPLY);
                break;
            }
            break;

        case 31:
            RCP_SetupDL_21();
            Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 2.0f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_101ABD0);
            break;

        case 32:
            gSPDisplayList(gMasterDisp++, D_BO_6008770);
            break;

        case 33:
            if ((actor->index == 3) && (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_LEVEL_COMPLETE)) {
                gSPDisplayList(gMasterDisp++, D_D00B880);
            } else {
                gSPDisplayList(gMasterDisp++, aKaCornerianFighterDL);
            }
            Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -60.0f, MTXF_APPLY);
            Actor_DrawEngineGlow(actor, 0);
            break;

        case 34:
            gSPDisplayList(gMasterDisp++, aKaEnemy1DL);
            break;

        case 35:
            Matrix_Scale(gGfxMatrix, 0.125f, 0.125f, 0.125f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            /* fallthrough */
        case 39:
            gSPDisplayList(gMasterDisp++, D_SY_60097E0);
            func_demo_8004FCB8(actor, 4);
            break;

        case 36:
            Matrix_Scale(gGfxMatrix, actor->scale, actor->scale, actor->scale, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_SY_601D730);
            func_demo_8004FCB8(actor, 0);
            break;

        case 37:
            RCP_SetupDL_49();
            gDPSetPrimColor(gMasterDisp++, 0, 0, actor->iwork[0], actor->iwork[1], actor->iwork[2], actor->iwork[3]);
            gDPSetEnvColor(gMasterDisp++, actor->iwork[4], actor->iwork[5], actor->iwork[6], actor->iwork[7]);
            Matrix_Scale(gGfxMatrix, actor->scale, actor->fwork[4], 1.0f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_1024AC0);
            break;

        case 38:
            animFrameData = Animation_GetFrameData(D_demo_800CA1F4[actor->iwork[4]], actor->iwork[5], sp144);
            Math_SmoothStepToVec3fArray(sp144, actor->vwork, 1, animFrameData, actor->fwork[2], 100.0f, .0f);
            RCP_SetupDL_30(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 150, 255, 150, 255);
            Animation_DrawSkeleton(1, D_SY_602D140, actor->vwork, 0, 0, actor, &gIdentityMatrix);

            if (actor->fwork[0] != 0.0f) {
                RCP_SetupDL_49();
                gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
                gDPSetEnvColor(gMasterDisp++, 255, 32, 32, 255);
                Matrix_Translate(gGfxMatrix, 10.0f, -5.0f, -40.0f, MTXF_APPLY);
                Matrix_RotateY(gGfxMatrix, (-actor->obj.rot.y) * M_DTOR, MTXF_APPLY);
                Graphics_SetScaleMtx(1.0f);
                Matrix_Scale(gGfxMatrix, actor->fwork[0], actor->fwork[0], actor->fwork[0], MTXF_APPLY);

                camX = gPlayer[0].cam.eye.x - actor->obj.pos.x;
                camY = gPlayer[0].cam.eye.y - actor->obj.pos.y;
                camZ = gPlayer[0].cam.eye.z - (actor->obj.pos.z + gPathProgress);

                y = -Math_Atan2F(camX, camZ);
                x = Math_Atan2F(camY, sqrtf(SQ(camZ) + SQ(camX)));

                Matrix_RotateY(gGfxMatrix, -y, MTXF_APPLY);
                Matrix_RotateX(gGfxMatrix, -x, MTXF_APPLY);

                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_1024AC0);
                Math_SmoothStepToF(&actor->fwork[0], 0.0f, 0.1f, 0.2f, 0.05f);
            }

            if (actor->fwork[6] != 0.0f) {
                RCP_SetupDL_49();
                gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
                gDPSetEnvColor(gMasterDisp++, 255, 48, 0, 255);
                Matrix_Pop(&gGfxMatrix);
                Matrix_Push(&gGfxMatrix);
                Matrix_RotateY(gCalcMatrix, (actor->obj.rot.y - 90.0f) * M_DTOR, MTXF_NEW);

                sp2B8.x = 210.0f;
                sp2B8.y = 0.0f;
                sp2B8.z = 40.0f;

                Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp2B8, &sp2AC);
                Matrix_Translate(gGfxMatrix, actor->obj.pos.x + sp2AC.x, actor->obj.pos.y + sp2AC.y,
                                 actor->obj.pos.z + sp2AC.z, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, actor->fwork[6], actor->fwork[6], actor->fwork[6], MTXF_APPLY);

                camX = gPlayer[0].cam.eye.x - actor->obj.pos.x;
                camY = gPlayer[0].cam.eye.y - actor->obj.pos.y;
                camZ = gPlayer[0].cam.eye.z - (actor->obj.pos.z + gPathProgress);

                y = -Math_Atan2F(camX, camZ);
                x = Math_Atan2F(camY, sqrtf(SQ(camZ) + SQ(camX)));

                Matrix_RotateY(gGfxMatrix, -y, MTXF_APPLY);
                Matrix_RotateX(gGfxMatrix, -x, MTXF_APPLY);

                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_1024AC0);
                Math_SmoothStepToF(&actor->fwork[6], 0.00f, 0.1f, 0.6f, 0);
            }
            break;

        case 40:
            gSPDisplayList(gMasterDisp++, D_SY_60132A0);
            break;

        case 41:
            Aquas_801BE0F0(actor);
            break;

        case 42:
            gSPDisplayList(gMasterDisp++, D_SY_6014A40);
            break;

        case 43:
            RCP_SetupDL_49();

            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, actor->iwork[0]);
            gDPSetEnvColor(gMasterDisp++, 255, 192, 128, 255);

            Matrix_RotateY(
                gGfxMatrix,
                Math_Atan2F(gPlayer[0].cam.eye.x - gPlayer[0].cam.at.x, gPlayer[0].cam.eye.z - gPlayer[0].cam.at.z),
                MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, actor->fwork[0], actor->fwork[0], actor->fwork[0], MTXF_APPLY);

            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_1024AC0);

            if (actor->iwork[0] != 0) {
                actor->iwork[0] -= 7;
            }
            actor->fwork[0] += 0.2f;
            break;

        case 44:
            Animation_GetFrameData(&D_AQ_6020A40, actor->iwork[0], actor->vwork);
            gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
            Animation_DrawSkeleton(1, D_AQ_6020C6C, actor->vwork, 0, 0, &actor->index, &gIdentityMatrix);
            gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
            break;

        case 45:
            Matrix_Scale(gGfxMatrix, 0.5f, 0.5f, 0.5f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_AQ_600EEF0);
            break;

        case 46:
            gSPDisplayList(gMasterDisp++, D_AQ_601DE60);
            break;

        case 47:
            gSPDisplayList(gMasterDisp++, D_AQ_602B4C0);
            break;
    }
}

void Cutscene_DrawGreatFox(void) {
    Vec3f* var_s6_2;
    s32 i;
    s32 j;
    f32 sp9C[4];
    Gfx* var_fp;

    (void) "Demo_Time=%d\n";
    (void) "Demo_Time=%d\n";
    (void) "d Enm->wrk0 %d\n";

    if (gGameState == GSTATE_TITLE) {
        var_fp = D_TITLE_60320E0;
    } else if (gGameState == GSTATE_ENDING) {
        var_fp = D_END_7010970;
    } else {
        var_fp = D_1024AC0;
    }

    if (gCurrentLevel == LEVEL_TITANIA) {
        RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, 1005);
    }

    if (gGreatFoxIntact) {
        gSPDisplayList(gMasterDisp++, D_GREAT_FOX_E000000);
    } else {
        gSPDisplayList(gMasterDisp++, D_GREAT_FOX_E003AB0);
    }

    if ((gCurrentLevel != LEVEL_AQUAS) &&
        ((gCurrentLevel != LEVEL_SECTOR_Z) || (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_LEVEL_COMPLETE))) {
        RCP_SetupDL_49();
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
        for (i = 0, var_s6_2 = D_demo_800CA0BC; i < ARRAY_COUNT(sp9C); i++, var_s6_2++) {
            if ((i != 1) || gGreatFoxIntact) {
                sp9C[i] = 0.0f;
                if (i < 2) {
                    if ((gGameFrameCount & ((64 - 1) & ~(8 - 1))) == 0) {
                        sp9C[i] = D_demo_800CA170[gGameFrameCount % 8U];
                    }
                    gDPSetEnvColor(gMasterDisp++, 255, 32, 32, 128);
                } else {
                    if (((gGameFrameCount + 32) & 0x38) == 0) {
                        sp9C[i] = D_demo_800CA170[gGameFrameCount % 8U];
                    }
                    gDPSetEnvColor(gMasterDisp++, 32, 32, 255, 128);
                }
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, var_s6_2->x, var_s6_2->y, var_s6_2->z, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, sp9C[i], sp9C[i], 1.0f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, var_fp);
                Matrix_Pop(&gGfxMatrix);
            }
        }

        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 48);
        gDPSetEnvColor(gMasterDisp++, 255, 255, 0, 48);
        for (i = 0, var_s6_2 = D_demo_800CA0EC; i < 3; i++, var_s6_2++) {
            sp9C[i] = D_demo_800CA190[gGameFrameCount % 2U];
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, var_s6_2->x, var_s6_2->y, var_s6_2->z, MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, sp9C[i], sp9C[i], 1.0f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, var_fp);

            for (j = 0; j < 4; j++) {
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, D_demo_800CA1B4[2 * j], MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, D_demo_800CA1D4[2 * j], D_demo_800CA1D4[2 * j], 1.0f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, var_fp);
                Matrix_Pop(&gGfxMatrix);
            }
            Matrix_Pop(&gGfxMatrix);
        }

        if ((gCurrentLevel == LEVEL_METEO) && (gPlayer[0].csEventTimer != 0)) {
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 128);
            gDPSetEnvColor(gMasterDisp++, 255, 255, 32, 128);
            Matrix_Translate(gGfxMatrix, D_ctx_80177A48[3] * (-74.0f), -232.0f, 1190.0f, MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, D_demo_800CA198[gPlayer[0].csEventTimer], D_demo_800CA198[gPlayer[0].csEventTimer],
                         1.0f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, var_fp);
        }
    }
}
