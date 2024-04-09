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

static Vec3f D_demo_800C9F60[] = {
    { 2000.0f, 2000.0f, 2000.0f },
    { -2000.0f, 2000.0f, 2000.0f },
    { 0.0f, -3000.0f, 3000.0f },
    { 5000.0f, -3000.0f, -3000.0f },
};

static f32 D_demo_800C9F90[] = { 75.0f, -80.0f, 85.0f, 0.0f };

static Vec3f D_demo_800C9FA0[] = {
    { 200.0f, -10.0f, 200.0f },
    { -200.0f, 20.0f, 200.0f },
    { 0.0f, 50.0f, 400.0f },
    { -2000.0f, -1000.0f, 0.0f },
};

static f32 D_demo_800C9FD0[] = { -1200.0f, 1200.0f, 0.0f, 0.0f };

static f32 D_demo_800C9FE0[] = { 0.0f, 0.0f, 600.0f, 2000.0f };

static f32 D_demo_800C9FF0[] = { -100.0f, 0.0f, 100.0f, 500.0f };

static f32 D_demo_800CA000[] = { -150.0f, 150.0f, 0.0f, 0.0f };

static f32 D_demo_800CA010[] = { 0.0f, 0.0f, 80.0f, 1000.0f };

static f32 D_demo_800CA020[] = { 45.0f, -45.0f, 10.0f, 0.0f };

static s32 D_demo_800CA030[] = { 0, 0, 0, 1 };

static s32 D_demo_800CA040[] = { 0, 0, 0, 0 };

static f32 D_demo_800CA050[] = { 210.0f, -210.0f, 0.0f };

static f32 D_demo_800CA05C[] = { -60.0f, -60.0f, -120.0f };

static f32 D_demo_800CA068[] = { -150.0f, -150.0f, -300.0f };

static f32 D_demo_800CA074[] = { 360.0f, -360.0f, 0.0f };

static f32 D_demo_800CA080[] = { -400.0f, 0.0f, 400.0f };

static f32 D_demo_800CA08C[] = { 0.0f, 200.0f, 0.0f };

static f32 D_demo_800CA098[] = { 1.0f, -0.9f, 0.7f };

static f32 D_demo_800CA0A4[] = { 150.0f, 100.0f, 200.0f };

static f32 D_demo_800CA0B0[] = { 200.0f, 300.0f, 500.0f };

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

void func_demo_80048AC0(s32 teamId) {
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

void func_demo_80048CC4(Actor* actor, s32 arg1) {
    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_195;
    actor->obj.pos.x = D_demo_800C9F60[arg1].x + gPlayer[0].pos.x;
    actor->obj.pos.y = D_demo_800C9F60[arg1].y + gPlayer[0].pos.y;
    actor->obj.pos.z = D_demo_800C9F60[arg1].z + gPlayer[0].unk_138;
    actor->unk_0F4.y = 0.0f;
    actor->unk_0F4.z = D_demo_800C9F90[arg1];
    Object_SetInfo(&actor->info, actor->obj.id);

    if (arg1 == 3) {
        AUDIO_PLAY_SFX(0x11030010U, actor->sfxSource, 0);
        AUDIO_PLAY_SFX(0x31024059U, actor->sfxSource, 0);
        actor->unk_0B6 = 1;
    } else {
        actor->iwork[11] = 1;
        AUDIO_PLAY_SFX(0x3100000CU, actor->sfxSource, 4);
    }
}

void func_demo_80048E40(Player* player) {
    Vec3f sp5C;
    Vec3f sp50;
    s32 pad[2];
    f32 temp_ft3;
    f32 temp_ret;
    s32 temp_v1;

    gBosses[1].obj.status = OBJ_FREE;
    Math_SmoothStepToF(&player->unk_130, 0.0f, 0.1f, 15.0f, 0.0f);
    Math_SmoothStepToF(&player->unk_12C, 0.0f, 0.1f, 15.0f, 0.0f);
    Math_SmoothStepToF(&player->unk_0E4, 0.0f, 0.1f, 3.0f, 0.0f);
    Math_SmoothStepToF(&player->unk_0E8, 0.0f, 0.1f, 3.0f, 0.0f);
    Math_SmoothStepToF(&player->unk_0EC, 0.0f, 0.1f, 3.0f, 0.0f);
    Math_SmoothStepToF(&player->unk_08C, 0.0f, 0.1f, 3.0f, 0.0f);
    Math_SmoothStepToF(&player->unk_034, 0.0f, 0.1f, 3.0f, 0.0f);
    Math_SmoothStepToAngle(&player->unk_4D8, 0.0f, 0.1f, 20.0f, 0.0f);
    Math_SmoothStepToF(&player->unk_110, 0.0f, 0.1f, 3.0f, 0.0f);

    switch (player->unk_1D0) {
        case 0:
            player->unk_4DC = 0;
            Audio_StopSfxByBankAndSource(1, player->sfxSource);
            player->unk_1D0++;
            D_ctx_80177A48[0] = 0.0f;
            D_ctx_80177A48[1] = 0.0f;
            D_ctx_80177A48[2] = 0.0f;
            player->wings.unk_2C = 1;
            gCsFrameCount = 0;
            /* fallthrough */
        case 1:
            D_ctx_80177A48[1] -= D_ctx_80177A48[2];
            Math_SmoothStepToF(&D_ctx_80177A48[2], 1.2f, 0.1f, 0.01f, 0.0f);
            Math_SmoothStepToF(&D_ctx_80177A48[0], 0.1f, 0.1f, 0.002f, 0.0f);
            Math_SmoothStepToF(&player->unk_0D0, 0.0f, 1.0f, 0.5f, 0.0f);
            Matrix_RotateX(gCalcMatrix, -5.0f * M_DTOR, 0);
            Matrix_RotateY(gCalcMatrix, D_ctx_80177A48[1] * M_DTOR, 1);
            sp5C.x = 0.0f;
            sp5C.y = 0.0f;
            sp5C.z = 300.0f;
            Matrix_MultVec3f(gCalcMatrix, &sp5C, &sp50);
            gCsCamAtX = player->pos.x;
            gCsCamAtY = player->pos.y;
            gCsCamAtZ = player->unk_138 + D_ctx_80177D20;

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
                    D_ctx_80177830 = 1;
                    break;

                case 400:
                    D_ctx_80177830 = 0;
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
                    AUDIO_PLAY_SFX(0x09000002U, player->sfxSource, 0);
                    player->unk_194 = 5.0f;
                    player->unk_190 = 5.0f;

                default:
                    break;
            }
            if (gCsFrameCount > 450) {
                Math_SmoothStepToF(&D_ctx_80177A48[0], 1.0f, 0.1f, 0.004f, 0.0f);
                player->unk_0D0 += 2.0f;
                player->unk_0E4 += 0.1f;
                player->unk_190 = 2.0f;

                if (gCsFrameCount == 530) {
                    Audio_FadeOutAll(50);
                }

                if (gCsFrameCount > 540) {
                    gFillScreenAlphaTarget = 255;
                    gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
                    gFillScreenAlphaStep = 8;
                    if (gFillScreenAlpha == 255) {
                        player->state_1C8 = PLAYERSTATE_1C8_6;
                        player->timer_1F8 = 0;
                        D_ctx_8017837C = 4;
                        if (gCurrentLevel == LEVEL_METEO) {
                            D_play_800D3180[LEVEL_METEO] = Play_CheckMedalStatus(200) + 1;
                        } else {
                            D_play_800D3180[LEVEL_SECTOR_X] = Play_CheckMedalStatus(150) + 1;
                        }
                        gNextPlanetPath = 2;
                    }
                }
            } else {
                gCsCamEyeX = player->pos.x + sp50.x;
                gCsCamEyeY = player->pos.y + sp50.y;
                gCsCamEyeZ = player->unk_138 + D_ctx_80177D20 + sp50.z;
            }

            break;
    }

    Math_SmoothStepToF(&player->camEye.x, gCsCamEyeX, D_ctx_80177A48[0], 50000.0f, 0);
    Math_SmoothStepToF(&player->camEye.y, gCsCamEyeY, D_ctx_80177A48[0], 50000.0f, 0);
    Math_SmoothStepToF(&player->camEye.z, gCsCamEyeZ, D_ctx_80177A48[0], 50000.0f, 0);
    Math_SmoothStepToF(&player->camAt.x, gCsCamAtX, D_ctx_80177A48[0], 50000.0f, 0);
    Math_SmoothStepToF(&player->camAt.y, gCsCamAtY, D_ctx_80177A48[0], 50000.0f, 0);
    Math_SmoothStepToF(&player->camAt.z, gCsCamAtZ, D_ctx_80177A48[0], 50000.0f, 0);
    Matrix_RotateY(gCalcMatrix, (player->unk_0E8 + 180.0f) * M_DTOR, 0);
    Matrix_RotateX(gCalcMatrix, -((player->unk_0E4 + player->unk_4D8) * M_DTOR), 1);

    sp5C.x = 0.0f;
    sp5C.y = 0.0f;
    sp5C.z = player->unk_0D0 + player->unk_110;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp5C, &sp50);
    player->vel.x = sp50.x;
    player->vel.z = sp50.z;
    player->vel.y = sp50.y;

    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;
    player->pos.z += player->vel.z;

    player->unk_138 = player->pos.z + player->unk_08C;
    player->unk_0F8 = player->unk_0EC + player->unk_12C + player->unk_130;
    player->unk_088 += 10.0f;
    player->unk_080 = (-SIN_DEG(player->unk_088)) * 0.3f;
    player->unk_0F4 += 8.0f;
    player->unk_0F0 = SIN_DEG(player->unk_0F4);
}

void func_demo_80049630(Actor* actor) {
    Vec3f sp3C;
    Vec3f sp30;

    switch (actor->state) {
        case 0:
            actor->vwork[0].x = gPlayer[0].pos.x + D_demo_800C9FA0[actor->index].x;
            actor->vwork[0].y = gPlayer[0].pos.y + D_demo_800C9FA0[actor->index].y;
            actor->vwork[0].z = gPlayer[0].pos.z + D_demo_800C9FA0[actor->index].z;
            Math_SmoothStepToF(&actor->obj.pos.x, actor->vwork[0].x, 0.05f, 50.0f, 0.0001f);
            Math_SmoothStepToF(&actor->obj.pos.y, actor->vwork[0].y, 0.05f, 50.0f, 0.0001f);
            Math_SmoothStepToF(&actor->obj.pos.z, actor->vwork[0].z, 0.05f, 50.0f, 0.0001f);
            Math_SmoothStepToF(&actor->unk_0F4.x, gPlayer[0].unk_0E4, 0.1f, 2.0f, 0.0001f);
            Math_SmoothStepToF(&actor->unk_0F4.y, gPlayer[0].unk_0E8, 0.1f, 2.0f, 0.0001f);
            Math_SmoothStepToF(&actor->unk_0F4.z, 0.0f, 0.05f, 0.2f, 0.0001f);
            break;

        case 1:
            actor->state = 2;
            AUDIO_PLAY_SFX(0x09000002U, actor->sfxSource, 0);
            actor->timer_0BC = 150;
            actor->fwork[29] = 5.0f;

        case 2:
            actor->iwork[11] = 2;
            actor->fwork[0] += 2.0f;
            if (actor->timer_0BC == 0) {
                Object_Kill(&actor->obj, actor->sfxSource);
            }
            break;
    }
    Matrix_RotateY(gCalcMatrix, (actor->unk_0F4.y + 180.0f) * M_DTOR, 0);
    Matrix_RotateX(gCalcMatrix, -(actor->unk_0F4.x * M_DTOR), 1);

    sp3C.x = 0.0f;
    sp3C.y = 0.0f;
    sp3C.z = actor->fwork[0];

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp3C, &sp30);

    actor->vel.x = sp30.x;
    actor->vel.y = sp30.y;
    actor->vel.z = sp30.z;

    actor->obj.rot.x = -actor->unk_0F4.x;
    actor->obj.rot.y = actor->unk_0F4.y + 180.0f;
    actor->obj.rot.z = -actor->unk_0F4.z;
}

void func_demo_8004990C(Player* player) {
    if (D_ctx_801784AC == 0) {
        D_ctx_80177CE8 += 60.0f;
    }
    player->unk_138 = player->pos.z + player->unk_08C;
    player->unk_0F8 = player->unk_0EC + player->unk_12C + player->unk_130;
}

void func_demo_80049968(Actor* actor, s32 arg1) {
    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_195;
    actor->obj.pos.x = D_demo_800C9FD0[arg1];
    actor->obj.pos.y = D_demo_800C9FE0[arg1];
    actor->obj.pos.z = D_demo_800C9FF0[arg1] + ((void) 0, gPlayer)[0].unk_138;
    actor->fwork[0] = D_demo_800CA000[arg1];
    actor->fwork[1] = D_demo_800CA010[arg1];
    actor->unk_0B6 = D_demo_800CA030[arg1];
    actor->state = D_demo_800CA040[arg1];
    actor->obj.rot.z = D_demo_800CA020[arg1];
    actor->obj.rot.y = 180.0f;
    actor->vel.z = gPlayer[0].vel.z;
    Object_SetInfo(&actor->info, actor->obj.id);
    actor->iwork[11] = 1;
    AUDIO_PLAY_SFX(0x3100000CU, actor->sfxSource, 4U);
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
            z = -D_ctx_80177D20 - 500.0f - RAND_FLOAT(500.0f);
            func_demo_80049A9C(&gEffects[i], x, y, z);
            break;
        }
    }
}

void func_demo_80049C0C(Player* player) {
    s32 var_v0;
    s32 pad[4];

    player->pos.x += player->vel.x;
    player->flags_228 = 0;
    player->cockpitView = 0;
    player->pos.y += player->vel.y;
    player->pos.z += player->vel.z;

    func_demo_8004990C(player);

    player->unk_140 = -player->vel.z;
    player->unk_144 += -player->vel.z;
    D_ctx_80177D20 = player->unk_144;

    Math_SmoothStepToF(&player->unk_130, 0.0f, 0.1f, 15.0f, 0.0f);
    Math_SmoothStepToF(&player->unk_12C, 0.0f, 0.1f, 15.0f, 0.0f);
    Math_SmoothStepToF(&player->unk_0EC, 0.0f, 0.1f, 5.0f, 0.0f);
    Math_SmoothStepToF(&player->unk_0E4, 0.0f, 0.1f, 5.0f, 0.0f);
    Math_SmoothStepToF(&player->unk_0E8, 0.0f, 0.1f, 5.0f, 0.0f);
    Math_SmoothStepToF(&player->pos.x, 0.0f, 0.1f, 50.0f, 0.0f);
    Math_SmoothStepToF(&player->pos.y, 0.0f, 0.1f, 50.0f, 0.0f);
    Math_SmoothStepToF(&player->camEye.x, 0.0f, 0.1f, 50.0f, 0.0f);
    Math_SmoothStepToF(&player->camEye.y, 0.0f, 0.1f, 50.0f, 0.0f);
    Math_SmoothStepToF(&player->camAt.x, 0.0f, 0.1f, 50.0f, 0.0f);
    Math_SmoothStepToF(&player->camAt.y, 0.0f, 0.1f, 50.0f, 0.0f);
    Math_SmoothStepToAngle(&player->unk_4D8, 0.0f, 0.1f, 20.0f, 0.0f);

    switch (player->unk_1D0) {
        case 0:
            player->unk_4DC = 0;
            D_ctx_80178414 = 100.0f;
            player->unk_1D0 = 1;
            D_ctx_80178410 = 1;
            D_ctx_80178488 = 0;
            player->vel.x = 0.0f;
            player->vel.y = 0.0f;
            player->vel.z = -500.0f;
            player->unk_0CC = -500.0f;

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
            player->timer_1F8 = 50;
            break;

        case 1:
            Math_SmoothStepToF(&D_ctx_801779A8[player->num], 100.0f, 1.0f, 4.0f, 0.0f);
            Math_SmoothStepToF(&player->unk_034, 0.0f, 0.1f, 3.0f, 0.0f);
            D_ctx_80178414 *= 1.05f;
            if (player->timer_1F8 == 0) {
                player->unk_1D0 = 2;
                player->timer_1F8 = 150;
            }
            player->unk_190 = 2.0f;
            player->unk_08C -= 2.0f;
            gBlurAlpha = 128;
            break;

        case 2:
            Math_SmoothStepToF(&D_ctx_801779A8[player->num], 100.0f, 1.0f, 3.0f, 0.0f);
            if (D_ctx_80178414 < 20000.0f) {
                D_ctx_80178414 *= 1.01f;
            }

            if (player->timer_1F8 <= 100) {
                if (player->timer_1F8 == 100) {
                    func_play_800A6028(player->sfxSource, 0x0940802AU);
                    player->unk_194 = 5.0f;
                    player->unk_190 = 5.0f;
                }

                player->unk_08C += player->unk_0CC;
                player->unk_0CC = player->unk_0CC - 100.0f;

                if (player->unk_08C < -15000.0f) {
                    player->unk_08C = 0.0f;
                    player->unk_0CC = 0.0f;
                    player->unk_234 = 0;
                }
            }
            var_v0 = 1;
            player->unk_190 = 2.0f;

            if ((player->timer_1F8 == 95) && (gTeamShields[TEAM_ID_FALCO] > 0)) {
                gActors[0].state = var_v0;
                AUDIO_PLAY_SFX(0x0940802AU, gActors[0].sfxSource, 0);
            }

            if ((player->timer_1F8 == 90) && (gTeamShields[TEAM_ID_PEPPY] > 0)) {
                gActors[2].state = var_v0;
                AUDIO_PLAY_SFX(0x0940802AU, gActors[2].sfxSource, 0);
            }

            if ((player->timer_1F8 == 85) && (gTeamShields[TEAM_ID_SLIPPY] > 0)) {
                gActors[1].state = var_v0;
                AUDIO_PLAY_SFX(0x0940802AU, gActors[1].sfxSource, 0);
            }

            if (player->timer_1F8 == 60) {
                gActors[3].state = var_v0;
                AUDIO_PLAY_SFX(0x0940802AU, gActors[3].sfxSource, 0);
                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 50);
                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 50);
            }

            if (player->timer_1F8 == 50) {
                player->unk_1D0 = 4;
                player->timer_1F8 = 0;
            }
            break;

        case 4:
            Math_SmoothStepToF(&D_ctx_801779A8[player->num], 100.0f, 1.0f, 3.0f, 0.0f);
            player->unk_034 -= 0.5f;
            if (player->timer_1F8 == 0) {
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
                gFillScreenAlphaTarget = 255;
                gFillScreenAlphaStep = 8;
                if (gFillScreenAlpha == 255) {
                    func_play_800A6148();
                    player->unk_1D0 = 5;
                    player->timer_1F8 = 10;
                    player->unk_08C = -10000.0f;
                    player->unk_0AC = player->unk_0B8 = player->unk_0B0 = player->unk_0BC = player->pos.x =
                        player->pos.y = player->pos.z = player->unk_130 = player->unk_034 = player->unk_138 =
                            player->vel.z = player->unk_144 = D_ctx_80177D20 = player->unk_144 = D_ctx_80177CB0 =
                                D_ctx_80177D20 = 0.0f;

                    player->timer_27C = gSavedHitCount = D_ctx_80177DC8 = D_ctx_80177CA0 = 0;

                    player->unk_234 = 1;
                    gLevelStage = 1;
                    D_display_800CA230 = 0.15f;
                    AUDIO_PLAY_SFX(0x11407079U, gDefaultSfxSource, 0);
                    func_play_800AB334();
                }
            }
            break;

        case 5:
            Math_SmoothStepToF(&D_ctx_801779A8[player->num], 100.0f, 1.0f, 3.0f, 0.0f);
            if (player->timer_1F8 == 0) {
                gFillScreenAlphaTarget = 0;
                gFillScreenAlphaStep = 8;
                if (gFillScreenAlpha == 0) {
                    player->unk_1D0 = 6;
                    player->timer_1F8 = 50;
                }
            }
            break;

        case 6:
            Math_SmoothStepToF(&D_ctx_80178414, 0.0f, 0.2f, 1000.0f, 0.1f);
            Math_SmoothStepToF(&player->unk_08C, 0.0f, 0.2f, 500.0f, 0.1f);
            if (player->timer_1F8 < 30) {
                for (var_v0 = 0; var_v0 < 3; var_v0++) {
                    func_demo_80049B44();
                }
            }

            if (player->timer_1F8 == 30) {
                D_ctx_80178410 = 300;
                AUDIO_PLAY_BGM(SEQ_ID_WARP_ZONE | SEQ_FLAG);
            }

            if (player->timer_1F8 == 0) {
                D_bg_8015F960 = 0.0f;
                D_ctx_80178414 = 0.0f;
                player->state_1C8 = PLAYERSTATE_1C8_3;
                player->unk_014 = 0.0f;
                player->unk_018 = 0.0f;
                D_ctx_801782B8 = 0;
                D_ctx_80178488 = 1;
            }
            Math_SmoothStepToF(&player->camEye.y, (player->pos.y * player->unk_148) + 50.0f, 0.2f, 15.0f, 0.01f);
            Math_SmoothStepToF(&player->camAt.y, (player->pos.y * player->unk_14C) + 20.0f, 0.2f, 15.0f, 0.01f);
            break;

        default:
            return;
    }
}

void func_demo_8004A52C(Player* player) {
    gCsFrameCount += 1;
    if (gLevelMode == LEVELMODE_ON_RAILS) {
        switch (gCurrentLevel) {
            case LEVEL_CORNERIA:
                Corneria_8018F880(player);
                func_play_800AA800(player);
                break;

            case LEVEL_METEO:
                Meteo_8018CD8C(player);
                break;

            case LEVEL_SECTOR_X:
                SectorX_80193A30(player);
                break;

            case LEVEL_TITANIA:
                Titania_8018769C(player);
                func_play_800AA800(player);
                break;

            case LEVEL_ZONESS:
                Zoness_8019D428(player);
                break;

            case LEVEL_MACBETH:
                Macbeth_801AC754(player);
                break;

            case LEVEL_SECTOR_Y:
                SectorY_801A0AC0(player);
                break;

            case LEVEL_SOLAR:
                Solar_801A10F4(player);
                break;

            case LEVEL_VENOM_1:
                Venom1_801988B8(player);
                func_play_800AA800(player);
                break;

            case LEVEL_AQUAS:
                func_hud_800935E8(player);
                break;

            case LEVEL_AREA_6:
                Area6_8018DF74(player);
                break;
        }
        func_demo_8004990C(player);
        return;
    }
    switch (gCurrentLevel) {
        case LEVEL_FORTUNA:
            func_360_8002ED60(player);
            func_play_800AA800(player);
            break;

        case LEVEL_VENOM_2:
            Venom2_80196BF8(player);
            func_play_800AA800(player);
            break;

        case LEVEL_BOLSE:
            Bolse_8018EF6C(player);
            func_play_800AA800(player);
            break;

        case LEVEL_KATINA:
            Katina_80192E20(player);
            func_play_800AA800(player);
            break;

        case LEVEL_SECTOR_Z:
            SectorZ_8019BA64(player);

        default:
            break;
    }
}

void func_demo_8004A700(Actor* actor, s32 arg1) {
    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_195;
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
    AUDIO_PLAY_SFX(0x3100000CU, actor->sfxSource, 4U);
}

void func_demo_8004A840(s32 actor) {
    func_demo_8004A700(&gActors[actor], actor);
}

void func_demo_8004A888(Effect* effect) {
    Vec3f sp2C;
    Vec3f sp20;

    Matrix_RotateY(gCalcMatrix, (gPlayer[0].unk_0E8 + 180.0f) * M_DTOR, 0);
    Matrix_RotateX(gCalcMatrix, -(gPlayer[0].unk_0E4 * M_DTOR), 1);
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

void func_demo_8004AAF4(Player* player) {
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

    gCsFrameCount += 1;
    Math_SmoothStepToAngle(&player->unk_4D8, 0.0f, 0.1f, 20.0f, 0.0f);
    if (gCsFrameCount == 37) {
        gChangeTo360 = true;
        if (gCurrentLevel == LEVEL_VENOM_ANDROSS) {
            Radio_PlayMessage(gMsg_ID_19466, RCID_FOX);
            AUDIO_PLAY_BGM(SEQ_ID_AND_BRAIN | SEQ_FLAG);
        } else if (gCurrentLevel != LEVEL_TRAINING) {
            Radio_PlayMessage(gMsg_ID_20180, RCID_FOX);
            if (gCurrentLevel == LEVEL_SECTOR_Y) {
                Audio_PlaySequence(SEQ_PLAYER_BGM, D_boss_800C9E90[gCurrentLevel], 0, 2);
            } else {
                AUDIO_PLAY_BGM(D_boss_800C9E90[gCurrentLevel]);
            }
        }
    }
    player->wings.unk_10 = 0.0f;
    player->wings.unk_08 = 0.0f;
    player->wings.unk_0C = 0.0f;
    player->wings.unk_04 = 0.0f;

    Math_SmoothStepToF(&player->unk_0E4, 0.0f, 0.1f, 5.0f, 0.0f);
    Math_SmoothStepToF(&player->unk_0E8, 0.0f, 0.1f, 5.0f, 0.0f);
    Math_SmoothStepToF(&player->unk_0EC, 0.0f, 0.1f, 1.0f, 0.0f);
    Math_SmoothStepToF(&player->unk_12C, 0.0f, 0.1f, 5.0f, 0.0f);
    Math_SmoothStepToF(&player->unk_034, 0.0f, 0.1f, 3.0f, 0.0f);
    Math_SmoothStepToF(&player->unk_110, 0.0f, 0.1f, 3.0f, 0.0f);
    Math_SmoothStepToF(&player->unk_08C, 0.0f, 0.1f, 3.0f, 0.0f);

    switch (player->unk_1D0) {
        case 0:
            Audio_PlayVoice(0);
            D_ctx_80177A48[0] = 0.005f;
            D_ctx_80177A48[1] = 0.0f;
            D_ctx_80177A48[2] = 60.0f;
            D_ctx_80177A48[3] = 0.0f;
            player->wings.unk_2C = 1;
            player->unk_1D0++;
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
                AUDIO_PLAY_SFX(0x09000007U, player->sfxSource, 0);
            }

            if (gCsFrameCount == 190) {
                AUDIO_PLAY_SFX(0x09000013U, player->sfxSource, 0);
            }

            if (D_ctx_80177A48[1] > 350.0f) {
                player->state_1C8 = PLAYERSTATE_1C8_3;
                player->unk_014 = 0.0f;
                player->unk_018 = 0.1f;
                player->unk_194 = 10.0f;
                player->unk_190 = 10.0f;

                AUDIO_PLAY_SFX(0x09000002U, player->sfxSource, 0);

                D_ctx_801779A8[player->num] = 70.0f;

                if ((gCurrentLevel != LEVEL_VENOM_ANDROSS) && (gCurrentLevel != LEVEL_TRAINING)) {
                    D_hud_800D1970 = 0;
                    for (i = 0, actor = &gActors[2]; i < 3; i++, actor++) {
                        Actor_Initialize(actor);
                        actor->obj.status = OBJ_INIT;
                        actor->obj.id = OBJ_ACTOR_TEAM_BOSS;
                        actor->obj.pos.x = D_demo_800CA080[i] + player->pos.x;
                        actor->obj.pos.y = D_demo_800CA08C[i] + player->pos.y;
                        actor->obj.pos.z = player->unk_138 - 1000.0f;
                        actor->unk_0F4.y = 180.0f;
                        Object_SetInfo(&actor->info, actor->obj.id);
                    }
                }
            }

            Matrix_RotateY(gCalcMatrix, D_ctx_80177A48[1] * M_DTOR, 0);
            Matrix_RotateX(gCalcMatrix, D_ctx_80177A48[2] * M_DTOR, 1);

            sp70.x = 0.0f;
            sp70.y = 0.0f;
            sp70.z = 200.0f;

            Matrix_MultVec3f(gCalcMatrix, &sp70, &sp64);

            if ((gCurrentLevel == LEVEL_CORNERIA) || (gCurrentLevel == LEVEL_VENOM_ANDROSS)) {
                sp64.x *= -1.0f;
            }
            Math_SmoothStepToF(&D_ctx_80177A48[0], 0.1f, 1.0f, 0.005f, 0.0f);
            Math_SmoothStepToF(&player->camEye.x, player->pos.x + sp64.x, D_ctx_80177A48[0], 500.0f, 0.0f);
            Math_SmoothStepToF(&player->camEye.y, player->pos.y + sp64.y, D_ctx_80177A48[0], 500.0f, 0.0f);
            Math_SmoothStepToF(&player->camEye.z, player->unk_138 + D_ctx_80177D20 + sp64.z, D_ctx_80177A48[0], 500.0f,
                               0.0f);
            Math_SmoothStepToF(&player->camAt.x, player->pos.x, D_ctx_80177A48[0], 500.0f, 0.0f);
            Math_SmoothStepToF(&player->camAt.y, player->pos.y, D_ctx_80177A48[0], 500.0f, 0.0f);
            Math_SmoothStepToF(&player->camAt.z, player->unk_138 + D_ctx_80177D20, D_ctx_80177A48[0], 500.0f, 0.0f);
            break;
    }
    Matrix_RotateY(gCalcMatrix, (player->unk_0E8 + 180.0f) * M_DTOR, 0);
    Matrix_RotateX(gCalcMatrix, -(player->unk_0E4 * M_DTOR), 1);

    sp70.x = 0.0f;
    sp70.y = 0.0f;
    sp70.z = player->unk_0D0 + player->unk_110;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp70, &sp64);

    player->vel.x = sp64.x;
    player->vel.z = sp64.z;
    player->vel.y = sp64.y;
    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;
    player->pos.z += player->vel.z;
    player->unk_138 = player->pos.z + player->unk_08C;
    player->camAt.z += player->vel.z;
    player->camEye.z += player->vel.z;

    player->unk_0F8 = player->unk_0EC + player->unk_12C + player->unk_130;
    player->unk_088 += 10.0f;
    player->unk_080 = -SIN_DEG(player->unk_088) * 0.3f;
    player->unk_0F4 += 8.0f;
    player->unk_0F0 = SIN_DEG(player->unk_0F4);

    func_play_800AA800(player);
}

void func_demo_8004B368(Player* player) {
    s32 pad[5];
    Vec3f sp78;
    Vec3f sp6C;
    Vec3f sp60;
    Vec3f sp54;
    s32 pad2[2];
    f32 var_fa1;

    player->flags_228 = 0;

    Math_SmoothStepToF(&player->unk_034, 0.0f, 0.1f, 5.0f, 0.01f);

    switch (player->unk_1D0) {
        case 10:
            D_ctx_80177A48[2] = 0.0f;
            player->unk_1D0++;
            player->wings.unk_04 = 0.0f;
            player->wings.unk_0C = 0.0f;
            player->wings.unk_08 = 0.0f;
            player->wings.unk_10 = 0.0f;
            player->unk_130 = 0.0f;
            player->unk_12C = 0.0f;
            player->unk_110 = 0.0f;
            player->wings.unk_2C = 1;
            player->unk_0D0 = 40.0f;
            /* fallthrough */

        case 11:
            D_ctx_80177A48[0] = 0.0f;
            Math_SmoothStepToAngle(&player->unk_4D8, 0.0f, 1.0f, 5.0f, 0.0f);
            player->camAt.x += (D_ctx_80178440 - player->camAt.x) * 0.01f;
            player->camAt.y += (D_ctx_80178444 - player->camAt.y) * 0.01f;
            player->camAt.z += (D_ctx_80178448 - player->camAt.z) * 0.01f;
            player->camEye.x += ((player->camAt.x + (500.0f * player->unk_004)) - player->camEye.x) * 0.01f;
            player->camEye.y += ((player->camAt.y + 500.0f) - player->camEye.y) * 0.01f;
            player->camEye.z += ((D_ctx_80178448 + (2000.0f * D_ctx_80177950)) - player->camEye.z) * 0.01f;

            if (player->timer_1FC > 25) {
                D_ctx_80177A48[2] += 1.5f * player->unk_004;
                Math_SmoothStepToF(&player->unk_0EC, (player->unk_004 * (-450.0f)) * D_ctx_80177950, 0.2f, 20.0f, 0.1f);
            } else {
                D_ctx_80177A48[2] += 0.25f * player->unk_004;
                if (player->unk_0EC < (-360.0f)) {
                    player->unk_0EC += 360.0f;
                }
                if (player->unk_0EC > 360.0f) {
                    player->unk_0EC -= 360.0f;
                }
                Math_SmoothStepToF(&player->unk_0EC, (player->unk_004 * 20.0f) * D_ctx_80177950, 0.1f, 3.0f, 0.1f);
            }

            if (D_ctx_80177950 > 0.0f) {
                Math_SmoothStepToF(&player->unk_0E8, 0.0f, 0.1f, 3.0f, 0.1f);
            } else {
                Math_SmoothStepToF(&player->unk_0E8, 180.0f, 0.1f, 3.0f, 0.1f);
                Math_SmoothStepToF(&player->pos.x, player->camEye.x, 1.0f, 30.0f, 0.0f);
                D_ctx_80177A48[2] = 0.0f;
            }

            player->pos.x += D_ctx_80177A48[2];
            Math_SmoothStepToF(&player->unk_0E4, 0.0f, 0.1f, 3.0f, 0.1f);
            Math_SmoothStepToF(&player->pos.y, player->camEye.y + 5.0f, 0.1f, 1.0f, 0.0f);

            if (player->timer_1F8 == 0) {
                player->unk_1D0 = 0;
                player->timer_1F8 = 120;
                player->timer_1FC = 20;
                D_ctx_80177A48[0] = 0.001f;
                gCsCamEyeX = player->camEye.x;
                gCsCamEyeY = player->camEye.y;
                gCsCamEyeZ = player->camEye.z;
                gCsCamAtX = player->camAt.x;
                gCsCamAtY = player->camAt.y;
                gCsCamAtZ = player->camAt.z;
            }
            break;

        case 0:
            if (player->timer_1F8 > 60) {
                Math_SmoothStepToF(&player->unk_0EC, (player->unk_004 * 60.0f) * D_ctx_80177950, 0.1f, 4.0f, 0.1f);
            }
            if (player->timer_1F8 < 80) {
                gCsCamAtX = player->pos.x;
                gCsCamAtY = player->pos.y;
                gCsCamAtZ = player->unk_138 + D_ctx_80177D20 + 30.0f;
                Math_SmoothStepToF(&D_ctx_80177A48[0], 0.05f, 0.1f, 0.0005f, 0.0f);
            }

            Math_SmoothStepToF(&player->pos.x, player->camEye.x, 0.1f, 10.0f, 0.0f);
            gCsCamEyeY += ((player->camAt.y + 500.0f) - player->camEye.y) * 0.01f;
            player->camEye.y = gCsCamEyeY;
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
            if (player->timer_1FC == 0) {
                Math_SmoothStepToF(&player->unk_0E8, var_fa1, 0.1f, 4.0f, 0.0f);
            }

            player->vel.y = 0.0f;
            Math_SmoothStepToF(&player->pos.y, player->camEye.y + 5.0f, 0.1f, 4.0f, 0.0f);

            if (player->timer_1F8 < 40) {
                Math_SmoothStepToF(&player->unk_0EC, player->unk_004 * 180.0f, 0.1f, 1.5f, 0.0f);
            }
            if (player->timer_1F8 == 0) {
                player->unk_1D0 = 1;
                player->timer_1F8 = 150;
                player->wings.unk_10 = 0.0f;
                player->wings.unk_08 = 0.0f;
                player->wings.unk_0C = 0.0f;
                player->wings.unk_04 = 0.0f;
            }
            break;

        case 1:
            Math_SmoothStepToF(&D_ctx_80177A48[0], 1.0f, 0.1f, 0.05f, 0.0f);
            player->unk_25C += 0.04f;
            if (player->unk_25C > 0.6f) {
                player->unk_25C = 0.6f;
            }

            player->unk_000 += 0.005f;
            if (player->unk_000 > 0.3f) {
                player->unk_000 = 0.3f;
            }
            Math_SmoothStepToF(&gCsCamAtX, player->pos.x, D_ctx_80177A48[0], 50000.0f, 0.0f);
            Math_SmoothStepToF(&gCsCamAtY, player->pos.y, D_ctx_80177A48[0], 50000.0f, 0.0f);
            Math_SmoothStepToF(&gCsCamAtZ, player->unk_138 + D_ctx_80177D20 + 30.0f, D_ctx_80177A48[0], 50000.0f, 0.0f);
            Math_SmoothStepToF(&player->pos.y, player->camEye.y + 5.0f, 0.1f, 4.0f, 0.0f);
            Math_SmoothStepToF(&player->unk_0E4, 20.0f, 0.1f, 0.2f, 0.01f);
            Math_SmoothStepToF(&player->pos.x, player->camEye.x, 0.1f, 2.0f, 0.0f);

            if (player->timer_1F8 <= 110) {
                Math_SmoothStepToF(&player->unk_0EC, player->unk_004 * 360.0f, 0.1f, 2.5f, 0.0f);
            } else {
                Math_SmoothStepToF(&player->unk_0EC, player->unk_004 * 180.0f, 0.1f, 2.5f, 0.0f);
            }

            if ((180.0f - fabsf(player->unk_0EC)) <= 3.0f) {
                gGroundType = GROUNDTYPE_ROCK;
            }

            if (player->timer_1F8 == 0) {
                player->timer_1F8 = 200;
                player->timer_1FC = 500;
                player->unk_1D0 = 2;
                player->unk_000 = (player->unk_004 = (player->unk_008 = (D_ctx_80178418 = 0.0f)));
                player->unk_0D0 = 0.0f;
                D_ctx_80177A48[6] = 0.0f;
            }
            break;

        case 2:
            player->pos.y += 5.0f;
            Matrix_RotateY(gCalcMatrix, ((player->unk_0E8 + 180.0f) + D_ctx_80178418) * M_DTOR, 0);
            Matrix_RotateX(gCalcMatrix, -(player->unk_0E4 * M_DTOR), 1);
            Matrix_RotateZ(gCalcMatrix, -((player->unk_0F8 + player->unk_0F0) * M_DTOR), 1);

            sp78.x = 0;
            sp78.y = 70.0f;
            sp78.z = -800.0f;

            Matrix_MultVec3f(gCalcMatrix, &sp78, &sp6C);
            Math_SmoothStepToF(&gCsCamAtX, player->pos.x, D_ctx_80177A48[0], 50000.0f, 0.0f);
            Math_SmoothStepToF(&gCsCamAtY, player->pos.y - D_ctx_80177A48[6], D_ctx_80177A48[0], 50000.0f, 0.0f);
            Math_SmoothStepToF(&gCsCamAtZ, player->unk_138 + D_ctx_80177D20 - D_ctx_80177A48[6], D_ctx_80177A48[0],
                               50000.0f, 0.0f);
            Math_SmoothStepToF(&D_ctx_80177A48[6], 130.0f, 0.1f, 0.25f, 0.0f);
            player->unk_000 += 0.002f;

            if (player->unk_000 > 0.3f) {
                player->unk_000 = 0.3f;
            }

            gCsCamEyeX += ((player->pos.x + sp6C.x) - gCsCamEyeX) * player->unk_000;
            gCsCamEyeY += ((player->pos.y + sp6C.y) - gCsCamEyeY) * player->unk_000;
            gCsCamEyeZ += ((player->unk_138 + D_ctx_80177D20 + sp6C.z) - gCsCamEyeZ) * player->unk_000;
            D_ctx_80178430 += 0.2f;
            D_ctx_8017842C += 0.2f;
            D_ctx_80178418 += player->unk_008;
            Math_SmoothStepToAngle(&player->unk_0EC, 0.0f, 0.1f, 2.0f, 0.0f);

            if (player->timer_1F8 == 0) {
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

            if ((player->timer_1F8 == 50) && (gTeamShields[TEAM_ID_FALCO] > 0)) {
                func_demo_8004A840(0);
            }

            if ((player->timer_1F8 == 70) && (gTeamShields[TEAM_ID_SLIPPY] > 0)) {
                func_demo_8004A840(1);
            }

            if (player->timer_1F8 == 90) {
                func_play_800A6148();
                if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                    func_demo_8004A840(2);
                }
                gGroundType = GROUNDTYPE_GRASS;
            }

            Matrix_RotateY(gCalcMatrix, (player->unk_0E8 + 180.0f) * M_DTOR, 0);
            Matrix_RotateX(gCalcMatrix, -(player->unk_0E4 * M_DTOR), 1);
            Matrix_RotateZ(gCalcMatrix, -((player->unk_0F8 + player->unk_0F0) * M_DTOR), 1);

            if ((D_ctx_80178418 > 70.0f) && (D_ctx_80178418 < 280.0f)) {
                func_demo_8004AA84();
            }
            sp78.x = gActors[0].fwork[0] * gActors[0].fwork[3];
            sp78.y = gActors[0].fwork[1] * gActors[0].fwork[3];
            sp78.z = gActors[0].fwork[2] * gActors[0].fwork[3];

            Matrix_MultVec3f(gCalcMatrix, &sp78, &sp6C);

            D_ctx_80178450[0] = player->pos.x + sp6C.x;
            D_ctx_80178460[0] = player->pos.y + sp6C.y;
            D_ctx_80178470[0] = player->unk_138 + sp6C.z;

            sp78.x = gActors[1].fwork[0] * gActors[1].fwork[3];
            sp78.y = gActors[1].fwork[1] * gActors[1].fwork[3];
            sp78.z = gActors[1].fwork[2] * gActors[1].fwork[3];

            Matrix_MultVec3f(gCalcMatrix, &sp78, &sp6C);

            D_ctx_80178450[1] = player->pos.x + sp6C.x;
            D_ctx_80178460[1] = player->pos.y + sp6C.y;
            D_ctx_80178470[1] = player->unk_138 + sp6C.z;

            sp78.x = gActors[2].fwork[0] * gActors[2].fwork[3];
            sp78.y = gActors[2].fwork[1] * gActors[2].fwork[3];
            sp78.z = gActors[2].fwork[2] * gActors[2].fwork[3];

            Matrix_MultVec3f(gCalcMatrix, &sp78, &sp6C);

            D_ctx_80178450[2] = player->pos.x + sp6C.x;
            D_ctx_80178460[2] = player->pos.y + sp6C.y;
            D_ctx_80178470[2] = player->unk_138 + sp6C.z;

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
            D_ctx_80178430 += 0.2f;
            D_ctx_8017842C += 0.2f;
            if (player->timer_1F8 == 0) {
                player->unk_1D0 = 4;
                player->timer_1F8 = 30;
                player->unk_000 = 0.0f;
                player->unk_194 = 5.0f;
                player->unk_190 = 5.0f;
            }
            break;

        case 4:
            D_ctx_80178430 += 0.2f;
            D_ctx_8017842C += 0.2f;
            player->unk_190 = 2.0f;
            player->unk_25C += 0.1f;
            if (player->unk_25C > 0.6f) {
                player->unk_25C = 0.6f;
            }
            player->unk_000 += 1.0f;
            player->unk_0D0 = player->unk_000 * player->unk_000;
            if (player->timer_1F8 == 0) {
                D_ctx_80177A48[7] = player->vel.x;
                D_ctx_80177A48[8] = player->vel.y;
                D_ctx_80177A48[9] = player->vel.z;
                player->unk_1D0 = 5;
                player->unk_0D0 = 0.0f;
                player->timer_1F8 = 10;
                func_effect_80078E50(player->pos.x, player->pos.y, player->unk_138, 30.0f);
            }
            gCsCamAtX = player->pos.x;
            gCsCamAtY = player->pos.y - D_ctx_80177A48[6];
            gCsCamAtZ = player->unk_138 + D_ctx_80177D20 - D_ctx_80177A48[6];
            break;

        case 5:
            gCsCamAtX += D_ctx_80177A48[7];
            gCsCamAtY += D_ctx_80177A48[8];
            gCsCamAtZ += D_ctx_80177A48[9];
            player->unk_234 = 0;
            if (player->timer_1F8 == 0) {
                player->state_1C8 = PLAYERSTATE_1C8_6;
                player->timer_1F8 = 0;
                D_ctx_8017837C = 4;
                Audio_FadeOutAll(10);
                D_play_800D3180[gCurrentLevel] = Play_CheckMedalStatus(150) + 1;
            }
            break;
    }

    switch (gCsFrameCount) {
        case 961:
            D_ctx_80177830 = 1;
            break;

        case 1161:
            D_ctx_80177830 = 0;
            break;

        case 1255:
            player->unk_1D0 = 3;
            player->timer_1F8 = 10;
            func_play_800A6028(player->sfxSource, 0x09000002U);
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 50);
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 50);
            break;
    }

    Matrix_RotateY(gCalcMatrix, ((player->unk_114 + player->unk_0E8) + 180.0f) * M_DTOR, 0);
    Matrix_RotateX(gCalcMatrix, -((player->unk_120 + player->unk_0E4) * M_DTOR), 1);

    sp60.x = 0.0f;
    sp60.y = 0.0f;
    sp60.z = player->unk_0D0;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp60, &sp54);

    player->vel.x = sp54.x;
    player->vel.z = sp54.z;
    player->vel.y = sp54.y;

    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;
    player->pos.z += player->vel.z;

    player->unk_0F8 = player->unk_0EC;
    player->unk_138 = player->pos.z;

    Math_SmoothStepToF(&player->camEye.x, gCsCamEyeX, D_ctx_80177A48[0], 50000.0f, 0);
    Math_SmoothStepToF(&player->camEye.y, gCsCamEyeY, D_ctx_80177A48[0], 50000.0f, 0);
    Math_SmoothStepToF(&player->camEye.z, gCsCamEyeZ, D_ctx_80177A48[0], 50000.0f, 0);
    Math_SmoothStepToF(&player->camAt.x, gCsCamAtX, D_ctx_80177A48[0], 50000.0f, 0.f);
    Math_SmoothStepToF(&player->camAt.y, gCsCamAtY, D_ctx_80177A48[0], 50000.0f, 0.f);
    Math_SmoothStepToF(&player->camAt.z, gCsCamAtZ, D_ctx_80177A48[0], 50000.0f, 0.f);

    player->unk_088 += 10.0f;
    player->unk_080 = (-SIN_DEG(player->unk_088)) * 0.3f;
    player->unk_0F4 += 8.0f;
    player->unk_0F0 = SIN_DEG(player->unk_0F4);
}

void func_demo_8004C90C(Player* player) {
    OvlI4_CallFunction(90, player);
}

void func_demo_8004C930(Player* player) {
    s32 sp24;
    s32 sp20;
    s32 btn;

    gCsFrameCount += 1;

    switch (player->form) {
        case FORM_ARWING:
            if ((gCurrentLevel == LEVEL_VENOM_ANDROSS) || ((gCurrentLevel == LEVEL_VENOM_2) && (gLevelStage == 1))) {
                Andross_80193C4C(player);
            } else if (gCurrentLevel == LEVEL_SECTOR_X) {
                if (gLevelStage == 0) {
                    SectorX_80194728(player);
                } else {
                    func_demo_80048E40(player);
                }
            } else if (gCurrentLevel == LEVEL_AREA_6) {
                Area6_8018ED78(player);
            } else if (gCurrentLevel == LEVEL_FORTUNA) {
                func_demo_8004C90C(player);
                func_play_800AA800(player);
            } else if (gCurrentLevel == LEVEL_BOLSE) {
                Bolse_8018F94C(player);
                func_play_800AA800(player);
            } else if (gCurrentLevel == LEVEL_SECTOR_Z) {
                SectorZ_8019C85C(player);
            } else if (gCurrentLevel == LEVEL_KATINA) {
                Katina_80197290(player);
                func_play_800AA800(player);
            } else if (gCurrentLevel == LEVEL_SECTOR_Y) {
                SectorY_8019EE60(player);
                func_play_800AA800(player);
            } else if (gCurrentLevel == LEVEL_SOLAR) {
                Solar_801A7930(player);
                func_play_800AA800(player);
            } else if (gCurrentLevel == LEVEL_ZONESS) {
                Zoness_8019D76C(player);
                func_play_800AA800(player);
            } else if (gCurrentLevel == LEVEL_VENOM_2) {
                Venom2_80196D88(player);
                func_play_800AA800(player);
            } else if (gCurrentLevel == LEVEL_METEO) {
                if (gLevelStage == 0) {
                    Meteo_8018E084(player);
                } else {
                    func_demo_80048E40(player);
                }
            } else if ((gCurrentLevel == LEVEL_CORNERIA) && (gLevelMode == LEVELMODE_ALL_RANGE)) {
                Corneria_80191160(player);
                func_play_800AA800(player);
            } else {
                if (gCsFrameCount == 170) {
                    AUDIO_PLAY_BGM(SEQ_ID_GOOD_END);
                }
                func_demo_8004B368(player);
                func_play_800AA800(player);
            }
            func_play_800B2130(player);
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
                Titania_801882CC(player);
            } else if (gNextPlanetPath != 0) {
                Macbeth_801AF8F4(player);
            } else {
                Macbeth_801B3D04(player);
            }

            func_tank_80046358(player);
            gInputPress->button = sp20;
            gInputHold->button = sp24;
            break;

        case FORM_BLUE_MARINE:
            if (gCurrentLevel == LEVEL_AQUAS) {
                func_hud_80095604(player);
            }
            break;
    }
}

void func_demo_8004CCC0(Player* player) {
    Vec3f sp58;
    PosRot sp50;

    Math_SmoothStepToF(&player->unk_130, 0.0f, 0.1f, 15.0f, 0.0f);
    Math_SmoothStepToF(&player->unk_0EC, 0.0f, 0.1f, 5.0f, 0.0f);
    Math_SmoothStepToF(&player->unk_0E8, 0.0f, 0.1f, 5.0f, 0.0f);
    Math_SmoothStepToF(&player->unk_0E4, 0.0f, 0.1f, 5.0f, 0.0f);
    Math_SmoothStepToF(&player->camEye.y, player->pos.y - 20.0f, 0.2f, 100.0f, 0.0f);

    sp50.rot.z = player->unk_0D0;
    sp58.x = Math_RadToDeg(Math_Atan2F(player->pos.x, player->unk_138));

    player->unk_2B4 = 1;
    player->unk_2BC += 1.0f;

    if (player->unk_2BC > 90.0f) {
        player->unk_2BC = 90.0f;
    }

    switch (player->unk_1D0) {
        case 0:
            if (player->unk_19C != 0) {
                player->timer_1F8 = 10;
            } else {
                player->timer_1F8 = 30;
            }
            player->unk_1D0 = 1;
            if (player->unk_4D8 > 180.0f) {
                player->unk_4D8 -= 360.0f;
            }
            /* fallthrough */

        case 1:
            if (player->timer_1F8 == 0) {
                player->unk_1D0 = 2;
                if (player->unk_19C != 0) {
                    player->timer_1F8 = 60;
                } else {
                    player->timer_1F8 = 80;
                }
            }
            player->camEye.x += player->vel.x * 0.2f;
            player->camEye.z += player->vel.z * 0.2f;
            Math_SmoothStepToF(&player->unk_12C, 0.0f, 0.1f, 15.0f, 0.0f);
            break;

        case 2:
            if (player->unk_4D8 > 140.0f) {
                sp58.y = 0.0f;
            } else {
                sp58.y = 60.0f;
            }

            Math_SmoothStepToF(&player->wings.unk_04, sp58.y, 0.3f, 100.0f, 0.0f);
            Math_SmoothStepToF(&player->wings.unk_08, sp58.y, 0.3f, 100.0f, 0.0f);
            Math_SmoothStepToF(&player->wings.unk_0C, sp58.y, 0.3f, 100.0f, 0.0f);
            Math_SmoothStepToF(&player->wings.unk_10, sp58.y, 0.3f, 100.0f, 0.0f);
            Math_SmoothStepToF(&player->unk_12C, 0.0f, 0.1f, 15.0f, 0.0f);
            Math_SmoothStepToF(&player->unk_4D8, 190.0f, 0.1f, 6.0f, 0.001f);

            if (player->unk_4D8 > 180.0f) {
                player->unk_114 += 180.0f;
                if (player->unk_114 >= 360.0f) {
                    player->unk_114 -= 360.0f;
                }
                player->unk_4D8 = 360.0f - (player->unk_4D8 - 180.0f);
                if ((sp58.x - player->unk_114) < 180.0f) {
                    player->unk_12C = 180.0f;
                } else {
                    player->unk_12C = -180.0f;
                }
                player->unk_1D0 = 3;
                func_play_800A5FA0(player->sfxSource, 0x09000002U, player->num);
                player->unk_194 = 7.0f;
                player->unk_190 = 7.0f;
            }
            player->unk_004 -= 0.2f;
            break;

        case 3:
            Math_SmoothStepToF(&player->unk_12C, 0.0f, 0.05f, 5.0f, 0.0f);

            sp58.y = player->unk_12C * 0.3f;

            Math_SmoothStepToF(&player->wings.unk_04, sp58.y, 0.3f, 100.0f, 0.0f);
            Math_SmoothStepToF(&player->wings.unk_08, sp58.y, 0.3f, 100.0f, 0.0f);

            sp58.z = -sp58.y;

            Math_SmoothStepToF(&player->wings.unk_0C, sp58.z, 0.3f, 100.0f, 0.0f);
            Math_SmoothStepToF(&player->wings.unk_10, sp58.z, 0.3f, 100.0f, 0.0f);

            player->unk_190 = 2.0f;
            player->camEye.x += player->vel.x * 0.1f;
            player->camEye.z += player->vel.z * 0.1f;

            if (player->unk_19C != 0) {
                player->camEye.x += player->vel.z * 0.2f;
                player->camEye.z += player->vel.x * 0.2f;
            }

            if (player->unk_19C == 0) {
                Math_SmoothStepToAngle(&player->unk_114, sp58.x, 0.1f, 2.0f, 0.0f);
            }

            if (player->pos.y < player->unk_0A0) {
                if (player->unk_004 < 0.0f) {
                    player->unk_004 += 0.2f;
                }
            } else {
                player->unk_004 -= 0.2f;
            }

            if (player->timer_1F8 == 0) {
                player->state_1C8 = PLAYERSTATE_1C8_3;
                player->unk_014 = 0.0f;
                player->unk_018 = 0.0f;
            }
            break;
    }
    player->pos.y += player->unk_004;
    player->camAt.y += player->unk_004;
    player->unk_0F8 = player->unk_0EC + player->unk_12C + player->unk_130;

    Matrix_RotateY(gCalcMatrix, (player->unk_114 + player->unk_0E8 + 180.0f) * M_DTOR, 0);
    Matrix_RotateX(gCalcMatrix, -((player->unk_120 + player->unk_0E4 + player->unk_4D8) * M_DTOR), 1);

    sp50.rot.x = 0.0f;
    sp50.rot.y = 0.0f;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp50.rot, &sp50.pos);

    player->vel.x = sp50.pos.x;
    player->vel.z = sp50.pos.z;
    player->vel.y = sp50.pos.y;
    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;

    if (player->pos.y < player->unk_0A4) {
        player->pos.y = player->unk_0A4;
        player->vel.y = 0.0f;
    }
    player->pos.z += player->vel.z;
    player->unk_138 = player->pos.z;

    func_play_800B2574(player);
    func_play_800B2130(player);
    func_play_800AD7F0(player);
    func_play_800AA800(player);
    func_play_800A46A0(player);
}

void func_demo_8004D3C8(s32 arg0) {
}

void func_demo_8004D3D4(Player* player, ObjectId itemId, Item* item) {
    Item_Initialize(item);
    item->obj.status = OBJ_INIT;
    item->obj.pos.x = player->pos.x;
    item->obj.pos.y = player->pos.y;
    item->obj.pos.z = player->unk_138;
    item->obj.id = itemId;
    Object_SetInfo(&item->info, item->obj.id);
}

void func_demo_8004D440(Player* player) {
    s32 teamId;

    func_8001CA24(player->num);
    Audio_KillSfxBySourceAndId(player->sfxSource, 0x0900C010U);
    func_play_800A5FA0(player->sfxSource, 0x0903F004U, player->num);
    player->state_1C8 = PLAYERSTATE_1C8_6;
    player->timer_1F8 = 70;
    player->timer_224 = 20;
    D_ctx_8017837C = 7;

    if (player->unk_1D4 != 0) {
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
            gLifeCount[gPlayerNum] -= 1;
        }
    } else {
        if (player->unk_288 > 0) {
            D_ctx_80177DD0[player->unk_288 - 1][D_ctx_80177DB8[player->unk_288 - 1]] = player->num;
            D_ctx_80177DB8[player->unk_288 - 1] += 1;
            if (D_ctx_801778A4 == D_ctx_80177DB8[player->unk_288 - 1]) {
                player->unk_288 = -1;
                if (player->unk_284 == 0) {
                    func_effect_8007C688(player->pos.x, player->pos.y, player->unk_138, 3.0f, 1000);
                }
            }
        }
        if (gBombCount[gPlayerNum] != 0) {
            gBombCount[gPlayerNum] = 0;
            func_demo_8004D3D4(player, OBJ_ITEM_BOMB, &gItems[1]);
        }
        if (gLaserStrength[gPlayerNum] != 0) {
            gLaserStrength[gPlayerNum] = 0;
            func_demo_8004D3D4(player, OBJ_ITEM_LASERS, &gItems[0]);
        }
    }
}

void func_demo_8004D738(Player* player) {
    player->pos.y += 30.0f;
    func_effect_8007D0E0(player->pos.x, player->pos.y, player->unk_138, 6.0f);
    if (gCamCount == 1) {
        func_effect_8007BFFC(player->pos.x, player->pos.y, player->unk_138, 0.0f, 0.0f, 0.0f, 3.0f, 80);
        func_effect_8007C688(player->pos.x, player->pos.y, player->unk_138, 3.0f, 800);
    } else {
        func_effect_8007BFFC(player->pos.x, player->pos.y, player->unk_138, 0.0f, 0.0f, 0.0f, 3.0f, 10);
    }
    func_demo_8004D440(player);
}

void func_demo_8004D828(Player* player) {
    s32 i;
    Vec3f src;
    Vec3f dest;

    Math_SmoothStepToF(&player->unk_0E4, 0.0f, 0.1f, 1.0f, 0.01f);
    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;

    if ((gCurrentLevel != LEVEL_VENOM_1 || gBossActive == 0) &&
        (gLevelType == LEVELTYPE_PLANET || gCurrentLevel == LEVEL_BOLSE)) {
        player->vel.y -= 0.5f;
        player->unk_0E4 -= 2.0f;
    }

    player->pos.z += player->vel.z;
    player->unk_138 = player->pos.z;
    player->unk_0F8 = player->unk_0EC + player->unk_12C + player->unk_130;
    player->unk_12C += 15.0f;

    if (player->unk_1D0 != 0) {
        player->unk_0E8 += 11.0f;
        player->unk_0E4 += 17.0f;
    }

    if (gCamCount == 1) {
        if (((gGameFrameCount % 2) == 0)) {
            func_effect_8007D24C(RAND_FLOAT_CENTERED(20.0) + player->pos.x, RAND_FLOAT_CENTERED(20.0) + player->pos.y,
                                 player->unk_138, 2.2f);
        }
    } else if (((gGameFrameCount % 4) == 0)) {
        func_effect_8007D10C(RAND_FLOAT_CENTERED(10.0f) + player->pos.x, RAND_FLOAT_CENTERED(10.0f) + player->pos.y,
                             RAND_FLOAT_CENTERED(10.0f) + player->unk_138, 2.2f);
    }

    if ((player->pos.y < player->unk_0A4) && (player->unk_1D0 == 0)) {
        player->pos.y = player->unk_0A4;
        player->unk_284 = 0;
        player->timer_220 = 0;
        player->vel.y = 10.0f;
        player->unk_1D0 = 1;

        func_play_800A6070(player->sfxSource, 0x29000000U);

        if ((gCurrentLevel == LEVEL_CORNERIA) || (gCurrentLevel == LEVEL_FORTUNA)) {
            func_enmy_80062C38(player->pos.x, player->pos.z);
        } else {
            func_effect_8007D0E0(player->pos.x, player->pos.y, player->unk_138, 3.0f);
        }

        if (player->wings.rightState == 2) {
            func_play_800A69F8(1, player->hit1.x, player->hit1.y, player->hit1.z);
            player->wings.rightState = 1;
            func_effect_8007D0E0(player->hit1.x, player->hit1.y, player->hit1.z, 2.0f);
        }
        if (player->wings.leftState == 2) {
            func_play_800A69F8(0, player->hit2.x, player->hit2.y, player->hit2.z);
            player->wings.leftState = 1;
            func_effect_8007D0E0(player->hit2.x, player->hit2.y, player->hit2.z, 2.0f);
        }
    } else if (((player->timer_220 > 0) || (player->pos.y < player->unk_0A4) || (player->pos.y < D_ctx_80177CC0) ||
                (player->timer_1FC == 0)) &&
               (player->timer_1F8 == 0)) {
        if (gCamCount != 4) {
            if (player->unk_284 == 0) {
                func_effect_8007C688(player->pos.x, player->pos.y, player->unk_138 - (2.0f * player->vel.z), 3.0f, 80);
            }
            if (player->pos.y < player->unk_0A4) {
                func_enmy_80062C38(player->pos.x, player->pos.z);
            }
        }
        if (gLevelType == LEVELTYPE_PLANET) {
            for (i = 0; i < 4; i++) {
                func_play_800A69F8(2, player->pos.x, player->pos.y, player->unk_138);
            }

            for (i = 0; i < 2; i++) {
                func_play_800A69F8(3, player->pos.x, player->pos.y, player->unk_138);
            }
        }
        func_effect_8007D0E0(player->pos.x, player->pos.y, player->unk_138, 5.0f);
        func_effect_8007BFFC(player->pos.x, player->pos.y, player->unk_138, player->vel.x, 0.0f, player->vel.z, 5.0f,
                             20);
        func_demo_8004D440(player);
    }
    Math_SmoothStepToF(&player->unk_034, 0.0f, 0.05f, 5.0f, 0.00001f);
    Matrix_RotateY(gCalcMatrix, (player->unk_114 + (player->unk_134 * 0.2f)) * M_DTOR, 0);
    Math_SmoothStepToF(&player->unk_000, 700.0f, 0.05f, 10.0f, 0.00001f);

    src.x = player->unk_004 * (player->unk_000 * 0.7f);
    src.y = player->unk_000 * 0.5f;
    src.z = player->unk_000 + (400.0f - player->unk_08C);

    Matrix_MultVec3f(gCalcMatrix, &src, &dest);

    player->camEye.x = player->pos.x + dest.x;
    player->camEye.z = player->pos.z + dest.z;

    player->camAt.x = player->pos.x;
    player->camAt.z = player->pos.z;

    if ((gLevelType == LEVELTYPE_PLANET) || (gCurrentLevel == LEVEL_BOLSE)) {
        player->camEye.y = (player->pos.y * player->unk_148) + dest.y;
        player->camEye.y -= player->unk_02C - 50.0f;
        player->camAt.y = ((player->pos.y * player->unk_14C) + 20.0f) + (player->unk_060 * 5.0f);
    } else {
        player->camEye.y = player->pos.y + dest.y;
        player->camAt.y = player->pos.y;
    }

    if (gVersusMode != 0) {
        func_play_800AE278(player);
    }
}

void func_demo_8004DEF8(Player* player) {
    s32 i;

    if (player->unk_0E4 < 0.0f) {
        player->unk_0E4 += 1.0f;
    }
    if (player->unk_0E4 > 0.0f) {
        player->unk_0E4 -= 1.0f;
    }

    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;

    if (((gCurrentLevel != LEVEL_VENOM_ANDROSS) || (gBossActive == 0)) && (gLevelType == LEVELTYPE_PLANET)) {
        player->vel.y = player->vel.y - 0.5f;
    }

    player->pos.z += player->vel.z;
    player->unk_138 = player->pos.z + player->unk_08C;
    player->unk_0F8 = player->unk_0EC + player->unk_12C + player->unk_130;
    player->unk_12C = player->unk_12C + 15.0f;

    if (player->unk_1D0 != 0) {
        player->unk_0E8 += 14.0f;
        player->unk_0E4 += 26.0f;
    }

    if (((gGameFrameCount % 2) == 0)) {
        func_effect_8007D24C(RAND_FLOAT_CENTERED(20.0) + player->pos.x, RAND_FLOAT_CENTERED(20.0) + player->pos.y,
                             player->unk_138, 2.2f);
    }

    if ((player->pos.y < player->unk_0A4) && (player->unk_1D0 == 0)) {
        player->pos.y = player->unk_0A4;
        player->timer_220 = 0;
        player->vel.y = 10.0f;
        player->unk_1D0 = 1;
        func_play_800A6070(player->sfxSource, 0x29000000U);
        if (gCurrentLevel == LEVEL_CORNERIA) {
            func_enmy_80062C38(player->pos.x, player->pos.z);
        }

        if (player->wings.rightState == 2) {
            func_play_800A69F8(1, player->hit1.x, player->hit1.y, player->hit1.z);
            player->wings.rightState = 0;
            func_effect_8007D0E0(player->hit1.x, player->hit1.y, player->hit1.z, 2.0f);
        }

        if (player->wings.leftState == 2) {
            func_play_800A69F8(0, player->hit2.x, player->hit2.y, player->hit2.z);
            player->wings.leftState = 0;
            func_effect_8007D0E0(player->hit2.x, player->hit2.y, player->hit2.z, 2.0f);
        }
    } else if ((((player->timer_220 > 0) || (player->pos.y < player->unk_0A4)) || (player->timer_1FC == 0)) &&
               (player->timer_1F8 == 0)) {
        if (player->pos.y < player->unk_0A4) {
            func_effect_8007C688(player->pos.x, gGroundLevel + 20.0f, player->unk_138 - (2.0f * player->vel.z), 3.0f,
                                 800);
            func_enmy_80062C38(player->pos.x, player->pos.z);
        }
        func_effect_8007D0E0(player->pos.x, player->pos.y - (2.0f * player->vel.y),
                             player->unk_138 - (2.0f * player->vel.z), 6.0f);
        func_effect_8007BFFC(player->pos.x, player->pos.y - player->vel.y, player->unk_138 - (2.0f * player->vel.z),
                             0.0f, 0.0f, 0.0f, 3.0f, 20);
        if (gLevelType == LEVELTYPE_PLANET) {
            for (i = 0; i < 2; i++) {
                func_play_800A69F8(2, player->pos.x, player->pos.y, player->unk_138);
            }

            for (i = 0; i < 4; i++) {
                func_play_800A69F8(4, player->pos.x, player->pos.y, player->unk_138);
            }
        }
        func_demo_8004D440(player);
    }

    player->unk_034 -= 3.0f;

    if (player->unk_1D0 != 0) {
        player->unk_034 += 10.0f;
    }

    if ((gGroundType == GROUNDTYPE_WATER) && (player->pos.y <= player->unk_0A4)) {
        func_effect_8007D9DC(player->pos.x, gGroundLevel + 2.0f, player->unk_138, 3.0f, 20.0f, 0);
        func_effect_8007ADF4(player->pos.x, gGroundLevel, player->unk_138, 0.1f, 2.0f);
    }
}

void func_demo_8004E3D8(Player* player) {
    player->flags_228 = 0;
    player->unk_280 = 0;

    if ((gGameFrameCount % 2) != 0) {
        D_80137E84[gPlayerNum] = 1;
    }

    switch (player->form) {
        case FORM_ARWING:
            if (gLevelMode == LEVELMODE_ALL_RANGE) {
                func_demo_8004D828(player);
            } else {
                func_demo_8004DEF8(player);
                func_play_800ADF58(player);
            }
            func_play_800A8BA4(player);
            func_play_800AA800(player);
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

void func_demo_8004E4D4(Actor* actor) {
    Vec3f sp54;
    Vec3f sp48;
    Vec3f sp3C;
    Player* sp38 = gPlayer;
    f32 sp34;

    actor->fwork[7] += 3.0f;
    actor->unk_0F4.z = SIN_DEG(actor->fwork[7]) * 1.5f;
    actor->fwork[8] += 2.0f;
    sp34 = SIN_DEG(actor->fwork[8]) * 10.0f;

    switch (actor->state) {
        case 0:
            Math_SmoothStepToF(&actor->obj.rot.z, 0.0f, 0.05f, 1.0f, 0.0f);
            Math_SmoothStepToF(&actor->obj.pos.x, actor->fwork[0] + sp38->pos.x, 0.03f, 10.0f, 0.0f);
            Math_SmoothStepToF(&actor->obj.pos.y, actor->fwork[1] + sp38->pos.y + sp34, 0.03f, 10.0f, 0.0f);
            Math_SmoothStepToF(&actor->obj.pos.z, actor->fwork[2] + sp38->unk_138, 0.03f, 10.0f, 0.0f);
            actor->obj.rot.x = -sp38->unk_0E4;
            actor->obj.rot.y = sp38->unk_0E8 + 180.0f;
            break;

        case 1:
            actor->state = 2;
            actor->timer_0BC = 50;
            actor->fwork[9] = 2.0f;
            AUDIO_PLAY_SFX(0x09000002U, actor->sfxSource, 0);
            actor->fwork[29] = 5.0f;
            /* fallthrough */

        case 2:
            if (gLevelType == LEVELTYPE_PLANET) {
                actor->fwork[21] += 0.4f;
                if (actor->fwork[21] > 0.6f) {
                    actor->fwork[21] = 0.6f;
                }
            }
            actor->iwork[11] = 2;
            actor->fwork[9] *= 1.2f;
            if (actor->timer_0BC == 0) {
                Object_Kill(&actor->obj, actor->sfxSource);
            }
            break;

        case 10:
            actor->state = 11;
            actor->timer_0BC = 150;
            actor->timer_0BE = 40;
            AUDIO_PLAY_SFX(0x09000002U, actor->sfxSource, 0);
            actor->fwork[29] = 5.0f;
            /* fallthrough */
        case 11:
            actor->iwork[11] = 2;
            actor->fwork[9] += 2.0f;
            if (actor->fwork[9] > 50.0f) {
                actor->fwork[9] = 50.0f;
            }
            if (actor->timer_0BE == 0) {
                switch (actor->index) {
                    case 1:
                        actor->obj.rot.y += 0.3f;
                        Math_SmoothStepToF(&actor->obj.rot.z, -70.0f, 0.05f, 4.0f, 0.0f);
                        break;

                    case 2:
                        actor->obj.rot.y -= 0.3f;
                        Math_SmoothStepToF(&actor->obj.rot.z, 70.0f, 0.05f, 4.0f, 0.0f);
                        break;

                    case 3:
                        actor->obj.rot.x -= 0.4f;
                        Math_SmoothStepToF(&actor->obj.rot.z, 1000.0f, 0.05f, 6.0f, 0.0f);
                        break;
                }
            }

            if (actor->timer_0BC == 0) {
                Object_Kill(&actor->obj, actor->sfxSource);
            }
            break;

        case 30:
            actor->fwork[3] += D_demo_800CA098[actor->index];

            Matrix_RotateY(gCalcMatrix, actor->fwork[3] * M_DTOR, 0);

            sp54.x = 0.0f;
            sp54.y = D_demo_800CA0A4[actor->index];
            sp54.z = D_demo_800CA0B0[actor->index];

            Matrix_MultVec3f(gCalcMatrix, &sp54, &sp3C);

            actor->fwork[0] = sp3C.x;
            actor->fwork[1] = sp3C.y;
            actor->fwork[2] = sp3C.z - 100.0f;

            Math_SmoothStepToF(&actor->obj.rot.z, SIN_DEG(actor->fwork[3]) * -30.0f, 0.1f, 2.0f, 0.0f);
            Math_SmoothStepToF(&actor->obj.pos.x, actor->fwork[0] + sp38->pos.x, 0.03f, 10.0f, 0.0f);
            Math_SmoothStepToF(&actor->obj.pos.y, actor->fwork[1] + sp38->pos.y + sp34, 0.03f, 10.0f, 0.0f);
            Math_SmoothStepToF(&actor->obj.pos.z, actor->fwork[2] + sp38->unk_138, 0.03f, 10.0f, 0.0f);
            break;

        case 31:
            AUDIO_PLAY_SFX(0x09000002U, actor->sfxSource, 0);
            actor->state += 1;
            actor->fwork[29] = 5.0f;
            /* fallthrough */

        case 32:
            actor->iwork[11] = 2;
            Math_SmoothStepToF(&actor->obj.rot.x, -20.0f, 0.1f, 0.5f, 0.0f);
            Math_SmoothStepToF(&actor->fwork[9], 25.0f, 0.1f, 2.0f, 0.0f);
            Math_SmoothStepToF(&actor->obj.rot.z, 0.0f, 0.1f, 0.5f, 0.0f);
            break;
    }
    Matrix_RotateY(gCalcMatrix, actor->obj.rot.y * M_DTOR, 0);
    Matrix_RotateX(gCalcMatrix, actor->obj.rot.x * M_DTOR, 1);

    sp54.x = 0.0f;
    sp54.y = 0.0f;
    sp54.z = actor->fwork[9];

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp54, &sp48);

    actor->vel.x = sp48.x;
    actor->vel.y = sp48.y;
    actor->vel.z = sp48.z;
}

void func_demo_8004EBD0(Actor* actor) {
    Vec3f src;
    Vec3f dest;

    if (actor->state < 4) {
        actor->fwork[9] = 0.4f;

        actor->obj.pos.x += (D_ctx_80178450[actor->index] - actor->obj.pos.x) * 0.4f;
        actor->obj.pos.y += (D_ctx_80178460[actor->index] - actor->obj.pos.y) * 0.4f;
        actor->obj.pos.z += (D_ctx_80178470[actor->index] - actor->obj.pos.z) * 0.4f;

        actor->obj.rot.z *= 0.98f;
        actor->obj.rot.x = -gPlayer[0].unk_0E4;
        actor->obj.rot.y = gPlayer[0].unk_0E8 + 180.0f;

        if (1) {}

        actor->fwork[7] += 1.0f;
        if ((s32) actor->fwork[7] & 0x40) {
            actor->fwork[0] += 0.1f;
        } else {
            actor->fwork[0] -= 0.1f;
        }

        actor->fwork[8] += 1.2f;
        if ((s32) actor->fwork[8] & 0x40) {
            actor->fwork[1] += 0.1f;
        } else {
            actor->fwork[1] -= 0.1f;
        }
    }

    switch (actor->state) {
        case 0:
            actor->fwork[3] *= 0.992f;
            if (actor->fwork[3] < 1.2f) {
                actor->state += 1;
            }
            break;

        case 1:
            actor->fwork[3] *= 0.997f;
            if (actor->fwork[3] < 1.0f) {
                actor->fwork[3] = 1.0f;
                actor->state += 1;
            }
            actor->timer_0BC = 560;
            break;

        case 2:
            if (actor->timer_0BC == 110) {
                gPlayer[0].timer_1F8 = 10000;
            }
            if (actor->timer_0BC == 260) {
                gPlayer[0].timer_1FC = 10000;
            }
            if (actor->timer_0BC == 0) {
                actor->state++;
                actor->timer_0BC = 10;
                func_play_800A6028(actor->sfxSource, 0x09000002);
                actor->fwork[29] = 5.0f;
            }
            break;

        case 3:
            actor->iwork[11] = 2;
            if (actor->timer_0BC == 0) {
                actor->state++;
                actor->timer_0BC = 30;
            }
            break;

        case 4:
            actor->fwork[21] += 0.4f;
            if (actor->fwork[21] > 0.6f) {
                actor->fwork[21] = 0.6f;
            }
            actor->fwork[6] += 1.0f;

            Matrix_RotateY(gCalcMatrix, (gPlayer[0].unk_0E8 + 180.0f) * M_DTOR, 0);
            Matrix_RotateX(gCalcMatrix, -(gPlayer[0].unk_0E4 * M_DTOR), 1);
            Matrix_RotateZ(gCalcMatrix, -((gPlayer[0].unk_0F8 + gPlayer[0].unk_0F0) * M_DTOR), 1);
            src.x = 0.0f;
            src.y = 0.0f;
            src.z = actor->fwork[6] * actor->fwork[6];

            Matrix_MultVec3f(gCalcMatrix, &src, &dest);

            actor->vel.x = dest.x;
            actor->vel.y = dest.y;
            actor->vel.z = dest.z;

            if (actor->timer_0BC == 0) {
                func_effect_80078E50(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, 30.0f);
                Object_Kill(&actor->obj, actor->sfxSource);
            }
            break;
    }
    actor->obj.pos.y += 5.0f;
    actor->fwork[21] -= 0.02f;
    if (actor->fwork[21] < 0.0f) {
        actor->fwork[21] = 0.0f;
    }
}

void func_demo_8004F05C(Actor* actor) {
    if (((gLevelType == LEVELTYPE_PLANET) && (actor->unk_0B6 == 0)) || (gCurrentLevel == LEVEL_BOLSE)) {
        actor->fwork[0] += 3.0f;
        actor->fwork[1] = SIN_DEG(actor->fwork[0]) * 1.5f;
    }

    switch (gCurrentLevel) {
        case LEVEL_BOLSE:
            switch (actor->unk_0B6) {
                case 0:
                    if (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_2) {
                        actor->unk_0F4.z += actor->unk_0F4.y;
                        actor->vel.x = SIN_DEG(actor->unk_0F4.z) * 10.0f;
                        actor->obj.rot.z = SIN_DEG(actor->unk_0F4.z) * 40.0f;
                        break;
                    }

                    Math_SmoothStepToF(&actor->obj.rot.z, actor->fwork[1], 0.05f, 0.3f, 0.0f);

                    switch (actor->state) {
                        case 0:
                            break;

                        case 1:
                            actor->state = 2;
                            actor->timer_0BC = 100;
                            AUDIO_PLAY_SFX(0x09000002U, actor->sfxSource, 0U);
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
                    actor->obj.rot.z += actor->unk_0F4.z;
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
            switch (actor->unk_0B6) {
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
                    actor->obj.rot.z = actor->unk_0F4.z;
                    if (actor->unk_0B6 == 10) {
                        actor->obj.pos.z = gPlayer[0].camEye.z + 12000.0f;
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
            if ((actor->obj.pos.z + D_ctx_80177D20) < -15000.0f) {
                Object_Kill(&actor->obj, actor->sfxSource);
            }
            break;
    }
}

void func_demo_8004F8AC(Actor* actor) {

    if (gCurrentLevel == LEVEL_AQUAS) {
        func_hud_80093164(actor);
        return;
    }

    switch (gPlayer[0].state_1C8) {
        case PLAYERSTATE_1C8_7:
            switch (gCurrentLevel) {
                case LEVEL_SECTOR_Y:
                    if (gPlayer[0].unk_1D0 >= 3) {
                        SectorY_8019FF00(actor);
                    }
                    break;

                case LEVEL_SOLAR:
                    if (gPlayer[0].unk_1D0 >= 3) {
                        Solar_801A8BE8(actor);
                    }
                    break;

                case LEVEL_ZONESS:
                    if (gPlayer[0].unk_1D0 >= 3) {
                        Zoness_8019E5F0(actor);
                    }
                    break;

                case LEVEL_VENOM_ANDROSS:
                case LEVEL_VENOM_2:
                    Andross_80195E44(actor);
                    break;

                case LEVEL_KATINA:
                    Katina_80197F10(actor);
                    break;

                case LEVEL_SECTOR_Z:
                    SectorZ_8019DD20(actor);
                    break;

                case LEVEL_AREA_6:
                    Area6_8018DA58(actor);
                    break;

                case LEVEL_METEO:
                    if (gLevelStage == 0) {
                        Meteo_8018ED9C(actor);
                        break;
                    }

                    func_demo_80049630(actor);
                    break;

                case LEVEL_FORTUNA:
                    if (actor->unk_0B6 == 11) {
                        switch (actor->state) {
                            case 0:
                                if (gCsFrameCount == 100) {
                                    actor->state = 1;
                                    actor->timer_0BC = 50;
                                    actor->iwork[0] = 255;
                                    AUDIO_PLAY_SFX(0x2902F026U, actor->sfxSource, 0);
                                }
                                break;

                            case 1:
                                Math_SmoothStepToF(&actor->scale, 0.5f, 0.03f, 0.01f, 0.0f);
                                gFillScreenRed = gFillScreenAlpha = gFillScreenGreen = gFillScreenBlue = 0;

                                if ((actor->timer_0BC == 43) || (actor->timer_0BC == 46) || (actor->timer_0BC == 49)) {
                                    gFillScreenAlpha = 192;
                                    gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
                                }

                                actor->iwork[0] -= 2;
                                if (actor->iwork[0] < 0) {
                                    actor->iwork[0] = 0;
                                    actor->scale = 0.0f;
                                }

                                D_ctx_8017836C = actor->iwork[0] / 255.0f;
                                D_ctx_80178370 = gActors[0].obj.pos.x + 10.0f;
                                D_ctx_80178374 = gActors[0].obj.pos.y - 40.0f;
                                D_ctx_80178378 = gActors[0].obj.pos.z - 70.0f;
                                D_ctx_80178360 = 255;
                                D_ctx_80178364 = 255;
                                D_ctx_80178368 = 80;
                                break;
                        }
                    }
                    break;

                case LEVEL_CORNERIA:
                    if (gLevelMode == LEVELMODE_ALL_RANGE) {
                        func_demo_8004E4D4(actor);
                        break;
                    }

                    func_demo_8004EBD0(actor);
                    break;

                case LEVEL_SECTOR_X:
                    if (gLevelStage != 0) {
                        func_demo_80049630(actor);
                        break;
                    }

                    func_demo_8004E4D4(actor);
                    break;

                case LEVEL_TITANIA:
                    func_demo_8004E4D4(actor);
                    break;

                case LEVEL_MACBETH:
                    Macbeth_801B28BC(actor);
                    break;

                case LEVEL_BOLSE:
                    func_demo_8004F05C(actor);
                    break;

                default:
                    func_demo_8004EBD0(actor);
                    break;
            }
            break;

        case PLAYERSTATE_1C8_2:
            func_demo_8004F05C(actor);
            break;

        case PLAYERSTATE_1C8_8:
            func_demo_8004F798(actor);
            break;

        case PLAYERSTATE_1C8_0:
            if (gCurrentLevel == LEVEL_SECTOR_Y) {
                SectorY_8019FF00(actor);
            }
            break;
    }
}

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
        angle = Math_Atan2F(gPlayer[0].camEye.x - gPlayer[0].camAt.x, gPlayer[0].camEye.z - gPlayer[0].camAt.z);

        for (i = arg1; i < (arg1 + 4); i++) {
            Matrix_Pop(&gGfxMatrix);
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, D_demo_800CA110[i].x + actor->obj.pos.x,
                             D_demo_800CA110[i].y + actor->obj.pos.y, D_demo_800CA110[i].z + actor->obj.pos.z, 1);
            Matrix_RotateY(gGfxMatrix, angle, 1);
            Matrix_Scale(gGfxMatrix, scale, scale, scale, 1);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_1024AC0);
        }
    }
}

void func_demo_8004FEC0(Actor* actor) {
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

    switch (actor->unk_0B6) {
        case 1000:
            RCP_SetupDL(&gMasterDisp, 0x2D);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, actor->unk_046);
            gSPDisplayList(gMasterDisp++, D_ENMY_PLANET_40018A0);

            if (actor->unk_046 > 50) {
                func_edisplay_8005ADAC(actor);
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
            func_demo_800515C4();
            break;

        case 10:
            RCP_SetupDL_40();
            Matrix_Scale(gGfxMatrix, 60.0f, 60.0f, 1.0f, 1);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_ME_6020810);
            break;

        case 11:
            RCP_SetupDL_64_2();
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
            Matrix_Scale(gGfxMatrix, 60.0f, 60.0f, 1.0f, 1);
            Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, 10.0f, 1);
            Matrix_Scale(gGfxMatrix, actor->scale, actor->scale, 1.0f, 1);
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
            func_edisplay_8005ADAC(actor);
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
            Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -60.0f, 1);
            func_edisplay_8005B1E8(actor, 2);
            break;

        case 28:
            gSPDisplayList(gMasterDisp++, D_ENMY_SPACE_400AAE0);
            Matrix_Translate(gGfxMatrix, 0.f, 0.f, -60.0f, 1);
            func_edisplay_8005B1E8(actor, 2);
            break;

        case 30:
            func_edisplay_8005F670(&actor->obj.pos);

            if (actor->unk_046 != 0) {
                RCP_SetupDL(&gMasterDisp, 0x37);
                gSPClearGeometryMode(gMasterDisp++, 0x00002000);
                Rand_SetSeed(1, 29000, 9876);

                for (sp2D0 = 0; sp2D0 < 30; sp2D0++) {
                    Matrix_Push(&gGfxMatrix);
                    Matrix_Translate(gGfxMatrix, RAND_FLOAT_CENTERED_SEEDED(3000.0f) * actor->fwork[20],
                                     RAND_FLOAT_CENTERED_SEEDED(3000.0f) * actor->fwork[20],
                                     RAND_FLOAT_CENTERED_SEEDED(3000.0f) * actor->fwork[20], 1);
                    Matrix_RotateY(gGfxMatrix, 2.0f * RAND_FLOAT_SEEDED(M_PI), 1);
                    Matrix_RotateZ(gGfxMatrix, (2.0f * gGameFrameCount) * M_DTOR, 1);
                    Matrix_RotateX(gGfxMatrix, 2.0f * RAND_FLOAT_SEEDED(M_PI), 1);

                    switch ((s32) (sp2D0 % 4U)) {
                        case 0:
                            Matrix_Scale(gGfxMatrix, 1.0f, 0.3f, 1.0f, 1);
                            break;

                        case 1:
                            Matrix_Scale(gGfxMatrix, 0.3f, 1.0f, 1.0f, 1);
                            break;

                        case 2:
                            Matrix_Scale(gGfxMatrix, 1.0f, 0.5f, 1.0f, 1);
                            break;

                        case 3:
                            Matrix_Scale(gGfxMatrix, 0.5f, 1.0f, 1.0f, 1);
                            break;
                    }

                    Matrix_Scale(gGfxMatrix, RAND_FLOAT_SEEDED(8.0f) + 8.0f, RAND_FLOAT_SEEDED(8.0f) + 8.0f, 10.0f, 1);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_1021E20);
                    Matrix_Pop(&gGfxMatrix);
                }

                break;
            }

            if (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_2) {
                Matrix_Push(&gGfxMatrix);
                Matrix_RotateX(gGfxMatrix, 20.0f * M_DTOR, 1);
                Matrix_RotateY(gGfxMatrix, (gGameFrameCount * 0.5f) * M_DTOR, 1);
                Matrix_Scale(gGfxMatrix, 2.0f, 2.0f, 2.0f, 1);
            } else {
                Matrix_RotateX(gGfxMatrix, -10.0f * M_DTOR, 1);
                Matrix_RotateY(gGfxMatrix, (gGameFrameCount * 0.3f) * M_DTOR, 1);
                Matrix_Scale(gGfxMatrix, 4.0f, 4.0f, 4.0f, 1);
                Matrix_Push(&gGfxMatrix);
            }

            Matrix_Translate(gGfxMatrix, 0.f, -590.0f, 0.f, 1);

            Matrix_SetGfxMtx(&gMasterDisp);

            gSPDisplayList(gMasterDisp++, D_BO_600BAA0);

            Matrix_Push(&gGfxMatrix);

            RCP_SetupDL(&gMasterDisp, 0x40);

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

            if (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_2) {
                Matrix_Scale(gGfxMatrix, 1.02f, 1.02f, 1.02f, 1);
            } else {
                Matrix_Scale(gGfxMatrix, 0.97f, 0.97f, 0.97f, 1);
            }

            Matrix_SetGfxMtx(&gMasterDisp);

            gDPSetTextureFilter(gMasterDisp++, 0 << 12);
            gSPDisplayList(gMasterDisp++, D_BO_6000D80);
            gDPSetTextureFilter(gMasterDisp++, 2 << 12);

            Matrix_Pop(&gGfxMatrix);
            Matrix_Pop(&gGfxMatrix);

            if (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_7) {
                Matrix_Scale(gGfxMatrix, 0.075f, 0.075f, 0.075f, 1);
                break;
            }
            break;

        case 31:
            RCP_SetupDL_21();
            Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 2.0f, 1);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_101ABD0);
            break;

        case 32:
            gSPDisplayList(gMasterDisp++, D_BO_6008770);
            break;

        case 33:
            if ((actor->index == 3) && (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_7)) {
                gSPDisplayList(gMasterDisp++, D_D00B880);
            } else {
                gSPDisplayList(gMasterDisp++, D_KA_600E050);
            }
            Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -60.0f, 1);
            func_edisplay_8005B1E8(actor, 0);
            break;

        case 34:
            gSPDisplayList(gMasterDisp++, D_KA_6001530);
            break;

        case 35:
            Matrix_Scale(gGfxMatrix, 0.125f, 0.125f, 0.125f, 1);
            Matrix_SetGfxMtx(&gMasterDisp);
            /* fallthrough */
        case 39:
            gSPDisplayList(gMasterDisp++, D_SY_60097E0);
            func_demo_8004FCB8(actor, 4);
            break;

        case 36:
            Matrix_Scale(gGfxMatrix, actor->scale, actor->scale, actor->scale, 1);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_SY_601D730);
            func_demo_8004FCB8(actor, 0);
            break;

        case 37:
            RCP_SetupDL_49();
            gDPSetPrimColor(gMasterDisp++, 0, 0, actor->iwork[0], actor->iwork[1], actor->iwork[2], actor->iwork[3]);
            gDPSetEnvColor(gMasterDisp++, actor->iwork[4], actor->iwork[5], actor->iwork[6], actor->iwork[7]);
            Matrix_Scale(gGfxMatrix, actor->scale, actor->fwork[4], 1.0f, 1);
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
                Matrix_Translate(gGfxMatrix, 10.0f, -5.0f, -40.0f, 1);
                Matrix_RotateY(gGfxMatrix, (-actor->obj.rot.y) * M_DTOR, 1);
                Graphics_SetScaleMtx(1.0f);
                Matrix_Scale(gGfxMatrix, actor->fwork[0], actor->fwork[0], actor->fwork[0], 1);

                camX = gPlayer[0].camEye.x - actor->obj.pos.x;
                camY = gPlayer[0].camEye.y - actor->obj.pos.y;
                camZ = gPlayer[0].camEye.z - (actor->obj.pos.z + D_ctx_80177D20);

                y = -Math_Atan2F(camX, camZ);
                x = Math_Atan2F(camY, sqrtf(SQ(camZ) + SQ(camX)));

                Matrix_RotateY(gGfxMatrix, -y, 1);
                Matrix_RotateX(gGfxMatrix, -x, 1);

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
                Matrix_RotateY(gCalcMatrix, (actor->obj.rot.y - 90.0f) * M_DTOR, 0);

                sp2B8.x = 210.0f;
                sp2B8.y = 0.0f;
                sp2B8.z = 40.0f;

                Matrix_MultVec3fNoTranslate(gCalcMatrix, (Vec3f*) (&sp2B8), &sp2AC);
                Matrix_Translate(gGfxMatrix, actor->obj.pos.x + sp2AC.x, actor->obj.pos.y + sp2AC.y,
                                 actor->obj.pos.z + sp2AC.z, 1);
                Matrix_Scale(gGfxMatrix, actor->fwork[6], actor->fwork[6], actor->fwork[6], 1);

                camX = gPlayer[0].camEye.x - actor->obj.pos.x;
                camY = gPlayer[0].camEye.y - actor->obj.pos.y;
                camZ = gPlayer[0].camEye.z - (actor->obj.pos.z + D_ctx_80177D20);

                y = -Math_Atan2F(camX, camZ);
                x = Math_Atan2F(camY, sqrtf(SQ(camZ) + SQ(camX)));

                Matrix_RotateY(gGfxMatrix, -y, 1);
                Matrix_RotateX(gGfxMatrix, -x, 1);

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
                Math_Atan2F(gPlayer[0].camEye.x - gPlayer[0].camAt.x, gPlayer[0].camEye.z - gPlayer[0].camAt.z), 1);
            Matrix_Scale(gGfxMatrix, actor->fwork[0], actor->fwork[0], actor->fwork[0], 1);

            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_1024AC0);

            if (actor->iwork[0] != 0) {
                actor->iwork[0] -= 7;
            }
            actor->fwork[0] += 0.2f;
            break;

        case 44:
            Animation_GetFrameData(&D_AQ_6020A40, actor->iwork[0], actor->vwork);
            gSPClearGeometryMode(gMasterDisp++, 0x00002000);
            Animation_DrawSkeleton(1, D_AQ_6020C6C, actor->vwork, 0, 0, &actor->index, &gIdentityMatrix);
            gSPSetGeometryMode(gMasterDisp++, 0x00002000);
            break;

        case 45:
            Matrix_Scale(gGfxMatrix, 0.5f, 0.5f, 0.5f, 1);
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

void func_demo_800515C4(void) {
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
        ((gCurrentLevel != LEVEL_SECTOR_Z) || (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_7))) {
        RCP_SetupDL_49();
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
        for (i = 0, var_s6_2 = D_demo_800CA0BC; i < 4; i++, var_s6_2++) {
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
                Matrix_Translate(gGfxMatrix, var_s6_2->x, var_s6_2->y, var_s6_2->z, 1);
                Matrix_Scale(gGfxMatrix, sp9C[i], sp9C[i], 1.0f, 1);
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
            Matrix_Translate(gGfxMatrix, var_s6_2->x, var_s6_2->y, var_s6_2->z, 1);
            Matrix_Scale(gGfxMatrix, sp9C[i], sp9C[i], 1.0f, 1);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, var_fp);

            for (j = 0; j < 4; j++) {
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, D_demo_800CA1B4[2 * j], 1);
                Matrix_Scale(gGfxMatrix, D_demo_800CA1D4[2 * j], D_demo_800CA1D4[2 * j], 1.0f, 1);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, var_fp);
                Matrix_Pop(&gGfxMatrix);
            }
            Matrix_Pop(&gGfxMatrix);
        }

        if ((gCurrentLevel == LEVEL_METEO) && (gPlayer[0].timer_1FC != 0)) {
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 128);
            gDPSetEnvColor(gMasterDisp++, 255, 255, 32, 128);
            Matrix_Translate(gGfxMatrix, D_ctx_80177A48[3] * (-74.0f), -232.0f, 1190.0f, 1);
            Matrix_Scale(gGfxMatrix, D_demo_800CA198[gPlayer[0].timer_1FC], D_demo_800CA198[gPlayer[0].timer_1FC], 1.0f,
                         1);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, var_fp);
        }
    }
}
