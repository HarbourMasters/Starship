#include "prevent_bss_reordering.h"
#include "global.h"
#include "assets/ast_sector_x.h"

s32 D_i2_80195D80;
f32 D_i2_80195D88[3];
f32 D_i2_80195D98[3];

s32 D_i2_80195640 = 0;
Vec3f D_i2_80195644 = { 73.0f, -102.0f, 80.0f };
Vec3f D_i2_80195650 = { 90.0f, 0.0f, 0.0f };
Vec3f D_i2_8019565C = { 73.0f, -102.0f, -80.0f };
Vec3f D_i2_80195668 = { 90.0f, 0.0f, 0.0f };

bool SectorX_80192AF0(s32, Gfx**, Vec3f*, Vec3f*, void*);
void SectorX_80193208(s32, Vec3f*, void*);

void SectorX_8018F030(void) {
    s32 i;
    Actor* actor = &gActors[0];

    for (i = 0; i < ARRAY_COUNT(gActors); i++, actor++) {
        if (actor->obj.status == OBJ_FREE) {
            Actor_Initialize(actor);
            actor->obj.status = OBJ_INIT;
            actor->obj.id = OBJ_ACTOR_SLIPPY_SX;
            actor->animFrame = 1;
            actor->obj.rot.y = 180.0f;
            actor->obj.pos.x = gPlayer[0].cam.eye.x - 300.0f;
            actor->obj.pos.y = gPlayer[0].cam.eye.y + 200.0f;
            actor->obj.pos.z = gPlayer[0].cam.eye.z - gPathProgress + 300.0f;
            actor->iwork[11] = 1;
            actor->aiType = AI360_SLIPPY;
            Object_SetInfo(&actor->info, actor->obj.id);
            Radio_PlayMessage(gMsg_ID_5475, RCID_SLIPPY);
            break;
        }
    }
}

void SectorX_8018F124(void) {
    Actor* actor = &gActors[50];

    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_SLIPPY_SX;
    actor->animFrame = -1;
    actor->obj.pos.x = gPlayer[0].cam.eye.x + 3000.0f;
    actor->obj.pos.y = gPlayer[0].cam.eye.y - 3000.0f;
    actor->obj.pos.z = gPlayer[0].pos.z + 30000.0f;
    Object_SetInfo(&actor->info, actor->obj.id);
    actor->info.cullDistance = 100000.0f;
}

void SectorX_8018F1DC(Actor* actor) {
    Vec3f src;
    Vec3f dest;

    src.x = 0.0f;
    src.y = 0.0f;
    src.z = 100.0f;
    Matrix_RotateY(gCalcMatrix, (actor->rot_0F4.y + 180.0f) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, actor->rot_0F4.x * M_DTOR, MTXF_APPLY);
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);
    Actor_SpawnPlayerLaser(actor->index, actor->obj.pos.x + (dest.x * 1.5), actor->obj.pos.y + (dest.y * 1.5),
                           actor->obj.pos.z + (dest.z * 1.5), dest.x, dest.y, dest.z, actor->rot_0F4.x,
                           actor->rot_0F4.y + 180.0f, 0.0f);
}

void SectorX_8018F330(Actor* actor) {
    f32 sp34;

    switch (actor->animFrame) {
        case 0:
            actor->obj.rot.x += 7.0f;
            actor->obj.rot.y += 5.0f;
            break;

        case 1:
            actor->rot_0F4.z += 3.0f;
            actor->obj.rot.z = SIN_DEG(actor->rot_0F4.z + 90.0f) * 60.0f;
            sp34 = fabsf(actor->obj.pos.z - gBosses[0].obj.pos.z) * 0.1f;
            Math_SmoothStepToF(&actor->obj.pos.x, gBosses[0].obj.pos.x + SIN_DEG(actor->rot_0F4.z) * sp34, 0.1f, 20.0f,
                               0.0f);
            Math_SmoothStepToF(&actor->obj.pos.y, gBosses[0].obj.pos.y, 0.1f, 20.0f, 0.0f);
            Math_SmoothStepToF(&actor->obj.pos.z, gBosses[0].obj.pos.z, 1.0f, 55.0f, 0);
            if (gBosses[0].state == 20) {
                actor->animFrame = 10;
                break;
            }

            if (((gGameFrameCount % 4) == 0) && (Rand_ZeroOne() < 0.2f)) {
                SectorX_8018F1DC(actor);
            }

            if ((gBosses[0].unk_04C == 75) && (gBosses[0].state == 85)) {
                actor->animFrame = 2;
                actor->vel.x = 10.0f;
                actor->vel.y = -10.0f;
                actor->vel.z = 30.0f;
                Radio_PlayMessage(gMsg_ID_4111, RCID_SLIPPY);
                func_effect_8007A6F0(&actor->obj.pos, NA_SE_EN_EXPLOSION_S);
                gBosses[0].swork[6] = 0;
                gTeamShields[TEAM_ID_SLIPPY] = -2;
                gPlayer[0].state_1C8 = PLAYERSTATE_1C8_STANDBY;
                actor->timer_0BC = 200;
                actor->iwork[14] = 3;
                actor->fwork[0] = 0.0f;
                actor->fwork[1] = 0.0f;
                gProjectFar = 30000.0f;
                SectorX_8018F124();
            }
            break;

        case 2:
            if (actor->timer_0BC == 100) {
                Radio_PlayMessage(gMsg_ID_20294, RCID_FOX);
            }

            actor->obj.rot.x += 5.5f;
            actor->obj.rot.y += 5.0f;

            if (((gGameFrameCount % 8) == 0)) {
                func_effect_8007D10C(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, 1.5f);
            }

            Math_SmoothStepToF(&actor->fwork[0], 0.5f, 1.0f, 0.01f, 0);
            Math_SmoothStepToF(&actor->fwork[1], 0.1f, 1.0f, 0.01f, 0);
            Math_SmoothStepToF(&gPlayer[0].cam.at.x, actor->obj.pos.x, actor->fwork[0], 100.0f, 0.0f);
            Math_SmoothStepToF(&gPlayer[0].cam.at.y, actor->obj.pos.y, actor->fwork[0], 100.0f, 0.0f);
            Math_SmoothStepToF(&gPlayer[0].cam.at.z, actor->obj.pos.z + gPathProgress, actor->fwork[0], 100.0f, 0.0f);
            Math_SmoothStepToF(&gPlayer[0].cam.eye.x, actor->obj.pos.x - 30.0f, actor->fwork[1], 20.0f, 0.0f);
            Math_SmoothStepToF(&gPlayer[0].cam.eye.y, actor->obj.pos.y, actor->fwork[1], 20.0f, 0.0f);
            if (actor->timer_0BC == 0) {
                gPlayer[0].state_1C8 = PLAYERSTATE_1C8_ACTIVE;
                if (gPlayer[0].alternateView) {
                    Camera_UpdateCockpitOnRails(&gPlayer[0], 1);
                }
                gProjectFar = 12800.0f;
                Object_Kill(&gActors[50].obj, gActors[50].sfxSource);
            }
            break;

        case 10:
            Math_SmoothStepToF(&actor->obj.rot.y, 90.0f, 0.1f, 10.0f, 0.0f);
            Math_SmoothStepToF(&actor->obj.rot.z, 90.0f, 1.0f, 10.0f, 0.0f);
            Math_SmoothStepToF(&actor->obj.pos.x, gBosses[0].obj.pos.x + 10000.0f, 0.1f, 40.0f, 0.0f);
            Math_SmoothStepToF(&actor->obj.pos.y, gBosses[0].obj.pos.y + 5000.0f, 0.1f, 10.0f, 0.0f);
            Math_SmoothStepToF(&actor->obj.pos.z, gBosses[0].obj.pos.z, 1.0f, 55.0f, 0.0f);
            break;
    }
}

void SectorX_8018F884(Actor* actor) {
    switch (actor->animFrame) {
        case 0:
            gSPDisplayList(gMasterDisp++, D_SX_6020D20);
            break;

        case 1:
        case 2:
        case 10:
            func_edisplay_8005B388(actor);
            break;

        case -1:
            actor->obj.rot.y = RAD_TO_DEG(-gPlayer[gPlayerNum].camYaw);
            actor->obj.rot.x = RAD_TO_DEG(gPlayer[gPlayerNum].camPitch);
            RCP_SetupDL(&gMasterDisp, SETUPDL_64);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 220, 70, 30, 255);
            Matrix_Scale(gGfxMatrix, 70.0f, 70.0f, 1.0f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_SX_60010C0);

        default:
            break;
    }
}

void SectorX_8018FA04(f32 x, f32 y, f32 z) {
    s32 i;
    Actor* actor;
    f32 yRot;
    f32 xRot;
    f32 pad;
    Vec3f src;
    Vec3f dest;

    for (i = 0; i < ARRAY_COUNT(gActors); i++) {
        actor = &gActors[i];
        if (actor->obj.status == OBJ_FREE) {
            Actor_Initialize(actor);
            actor->obj.status = OBJ_INIT;
            actor->obj.id = OBJ_ACTOR_SLIPPY_SX;
            actor->obj.pos.x = x;
            actor->obj.pos.y = y;
            actor->obj.pos.z = z;
            Object_SetInfo(&actor->info, actor->obj.id);
            actor->info.hitbox = (f32*) LOAD_ASSET(D_SX_60328CC);
            xRot = Math_Atan2F(gPlayer[0].pos.x - x, gPlayer[0].trueZpos - z);
            pad = sqrtf(SQ(gPlayer[0].pos.x - x) + SQ(gPlayer[0].trueZpos - z));
            yRot = -Math_Atan2F(gPlayer[0].pos.y - y, pad);
            Matrix_RotateY(gCalcMatrix, xRot, MTXF_NEW);
            Matrix_RotateX(gCalcMatrix, yRot, MTXF_APPLY);
            src.x = 0.0f;
            src.y = 0.0f;
            src.z = 60.0f;
            Matrix_MultVec3f(gCalcMatrix, &src, &dest);
            actor->vel.x = dest.x;
            actor->vel.y = dest.y;
            actor->vel.z = dest.z - gPathVelZ;
            break;
        }
    }
}

void SectorX_8018FBBC(Vec3f* pos) {
    s32 i;
    Actor* actor;
    f32 xRot;
    f32 yRot;
    Vec3f src;
    Vec3f dest;

    for (i = 0; i < ARRAY_COUNT(gActors); i++) {
        actor = &gActors[i];
        if ((actor->obj.status >= OBJ_ACTIVE) && (fabsf(pos->x - actor->obj.pos.x) < 2500.0f) &&
            (fabsf(pos->z - actor->obj.pos.z) < 2500.0f) && (actor->state != 1000) && (actor->timer_0C2 == 0) &&
            (actor->scale < 0.0f) &&
            Object_CheckHitboxCollision(pos, actor->info.hitbox, &actor->obj, actor->vwork[29].x, actor->vwork[29].y,
                                        actor->vwork[29].z + actor->rot_0F4.z)) {
            Play_PlaySfxFirstPlayer(actor->sfxSource, NA_SE_SLIPPY_HIT);
            actor->state = 1000;
            xRot = Math_Atan2F(actor->obj.pos.x - pos->x, actor->obj.pos.z - pos->z);
            yRot = -Math_Atan2F(actor->obj.pos.y - pos->y,
                                sqrtf(SQ(actor->obj.pos.x - pos->x) + SQ(actor->obj.pos.z - pos->z)));
            Matrix_RotateY(gCalcMatrix, xRot, MTXF_NEW);
            Matrix_RotateX(gCalcMatrix, yRot, MTXF_APPLY);
            src.x = 0.0f;
            src.y = 0.0f;
            src.z = 20.0f;
            Matrix_MultVec3f(gCalcMatrix, &src, &dest);
            actor->vel.x = dest.x;
            actor->vel.z = 10.0f;
            actor->vel.y = dest.y;
            actor->fwork[15] = actor->vel.x * 0.2f;
            actor->fwork[16] = actor->vel.y * -0.2f;
            actor->timer_0C6 = 10;
        }
    }
}

void SectorX_8018FE38(Boss* boss) {
    Vec3f sp2C;
    Vec3f sp20;

    if (boss->state == 0) {
        Animation_GetFrameData(D_SX_60206DC, boss->unk_04C, boss->vwork);
        Math_Vec3fFromAngles(&sp20, boss->obj.rot.x, boss->obj.rot.y, 20.0f);
        boss->vel.x = sp20.x;
        boss->vel.y = sp20.y;
        boss->vel.z = sp20.z;
        boss->state++;
    } else {
        if (boss->obj.id == OBJ_BOSS_304) {
            sp2C.x = boss->fwork[11];
            sp2C.y = boss->fwork[12];
            sp2C.z = boss->fwork[13];
        } else {
            sp2C.x = boss->fwork[8];
            sp2C.y = boss->fwork[9];
            sp2C.z = boss->fwork[10];
        }
        SectorX_8018FBBC(&sp2C);
    }
    if (boss->dmgType == DMG_BEAM) {
        boss->dmgType = DMG_NONE;
        func_effect_8007A6F0(&boss->obj.pos, NA_SE_EN_REFLECT);
    }
}

void SectorX_8018FF20(Boss* boss) {
    SectorX_8018FE38(boss);
}

bool SectorX_8018FF40(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* data) {
    if (((limbIndex >= 12) && (limbIndex < 22)) || ((limbIndex >= 36) && (limbIndex < 40))) {
        return 0;
    }
    *dList = NULL;
    return 0;
}

void SectorX_8018FF84(Boss* boss) {
    Animation_DrawSkeleton(3, D_SX_6020C68, boss->vwork, SectorX_8018FF40, SectorX_80193208, boss, gCalcMatrix);
}

bool SectorX_8018FFDC(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* data) {
    if (((limbIndex >= 2) && (limbIndex < 12)) || ((limbIndex >= 32) && (limbIndex < 36))) {
        return 0;
    }
    *dList = NULL;
    return 0;
}

void SectorX_80190020(Boss* boss) {
    Animation_DrawSkeleton(3, D_SX_6020C68, boss->vwork, SectorX_8018FFDC, SectorX_80193208, boss, gCalcMatrix);
}

void SectorX_80190078(Boss* boss) {
    u8 attack;
    s32 i;
    Vec3f sp80[50];
    Vec3f sp74;
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    s32 frameData;

    gBossFrameCount++;
    gLight2colorStep = 5;
    attack = false;

    if (gBossFrameCount < 150) {
        gLight2RTarget = 20;
        gLight2GTarget = 20;
        gLight2BTarget = 20;
    }

    PRINTF("たかおちゃん よう見ときや！\n");                      // Takao-chan, look at it!
    PRINTF("ボス面累計時間 : <%d>フレーム\n\n", gBossFrameCount); // Boss stage total time: <%d> frames.

    switch (gBossFrameCount) {
        case 175:
            Radio_PlayMessage(gMsg_ID_5473, RCID_FOX);
            break;

        case 300:
            Radio_PlayMessage(gMsg_ID_5492, RCID_BOSS_SECTORX);
            break;

        case 400:
            Radio_PlayMessage(gMsg_ID_2225, RCID_SLIPPY);
            break;

        case 556:
            gShowBossHealth = 1;
            break;

        case 540:
            Radio_PlayMessage(gMsg_ID_5493, RCID_BOSS_SECTORX);
            break;
    }

    if (gBossFrameCount > 556) {
        // approximately 700 / 256
        gBossHealthBar = (boss->swork[3] + boss->health) / 2.73f;
    }

    sp68 = gPlayer[0].pos.x - boss->obj.pos.x;
    sp64 = gPlayer[0].trueZpos - (boss->obj.pos.z + (-237.0f));

    if (boss->swork[7] != 0) {
        sp70 = Math_RadToDeg(Math_Atan2F(sp68, sp64));
        sp6C = Math_RadToDeg(-Math_Atan2F(gPlayer[0].pos.y - (boss->obj.pos.y + 334.0f), sqrtf(SQ(sp68) + SQ(sp64))));
        Math_SmoothStepToAngle(&boss->fwork[4], sp70, 0.1f, 5.0f, 0.00001f);
        Math_SmoothStepToAngle(&boss->fwork[6], sp6C, 0.1f, 5.0f, 0.00001f);
    } else {
        Math_SmoothStepToF(&boss->fwork[4], 182.0f, 0.1f, 2.0f, 0.00001f);
        Math_SmoothStepToAngle(&boss->fwork[6], 0.0f, 0.1f, 1.0f, 0.00001f);
    }

    boss->fwork[5] = SIN_DEG(boss->timer_054 * 50.0f) * boss->timer_054;
    boss->fwork[7] = SIN_DEG(boss->timer_054 * 30.0f) * boss->timer_054 * 0.5f;

    Math_SmoothStepToF(&boss->obj.pos.z, gPlayer[0].pos.z + boss->fwork[1], 0.1f, boss->fwork[42], 0);
    Math_SmoothStepToF(&boss->obj.pos.y, boss->fwork[2], 0.05f, boss->fwork[43], 0);
    Math_SmoothStepToF(&boss->obj.pos.x, boss->fwork[3], 0.05f, boss->fwork[44], 0);
    Math_SmoothStepToAngle(&boss->obj.rot.z, boss->fwork[41], 0.05f, 2.0f, 0);

    if (boss->state != 5) {
        Math_SmoothStepToF(&boss->fwork[29], 0.f, 0.1f, 50.0f, 0);
        Math_SmoothStepToF(&boss->fwork[30], 0.f, 0.1f, 50.0f, 0);
        Math_SmoothStepToF(&boss->fwork[31], 0.f, 0.1f, 50.0f, 0);
        Math_SmoothStepToF(&boss->fwork[32], 0.f, 0.1f, 50.0f, 0);
        Math_SmoothStepToF(&boss->fwork[33], 0.f, 0.1f, 50.0f, 0);
        Math_SmoothStepToF(&boss->fwork[34], 0.f, 0.1f, 50.0f, 0);
        if (boss->state != 4) {
            Math_SmoothStepToF(&boss->fwork[27], 0.0f, 0.1f, 2.0f, 0);
            Math_SmoothStepToF(&boss->fwork[28], 0.0f, 0.1f, 2.0f, 0);
        }
    }

    if (boss->dmgType != DMG_NONE) {
        boss->dmgType = DMG_NONE;
        if (boss->swork[0] == 1) {
            if ((boss->dmgPart == 0) && ((boss->fwork[4] < 45.0f) || (boss->fwork[4] > 315.0f))) {
                AUDIO_PLAY_SFX(NA_SE_EN_DAMAGE_S, boss->sfxSource, 4);
                boss->swork[3] -= boss->damage;
                boss->timer_054 = 20;
                func_effect_8007C120(boss->obj.pos.x, boss->obj.pos.y + 334.0f, -237.0f + boss->obj.pos.z, boss->vel.x,
                                     boss->vel.y, boss->vel.z, 0.2f, 20);

                if (boss->swork[3] <= 0) {
                    func_effect_8007BFFC(boss->obj.pos.x, boss->obj.pos.y + 300.0f, boss->obj.pos.z, 0.0f, 0.0f, 0.0f,
                                         10.0f, 50);

                    func_effect_8007C120(boss->obj.pos.x, boss->obj.pos.y + 334.0f, -237.0f + boss->obj.pos.z,
                                         boss->vel.x, boss->vel.y, boss->vel.z, 0.15f, 70);
                    for (i = 0; i < 10; i++) {
                        Play_SpawnDebris(4, boss->obj.pos.x, boss->obj.pos.y + 334.0f, -237.0f + boss->obj.pos.z);
                    }

                    func_effect_8007A6F0(&boss->obj.pos, NA_SE_EN_EXPLOSION_L);
                    boss->state = 7;
                    boss->timer_050 = 80;
                    boss->swork[0] = 0;
                    boss->timer_05C = 80;
                    boss->swork[1] = 0;
                    boss->fwork[0] = 0.0f;
                    boss->unk_04C = 0;
                    boss->swork[4] = 1;
                    boss->health = 1;
                    boss->swork[7] = 1;
                    Audio_KillSfxBySourceAndId(D_i2_80195D88, NA_SE_EN_SZMIS_ENGINE);
                    Audio_KillSfxBySourceAndId(D_i2_80195D98, NA_SE_EN_SZMIS_ENGINE);
                    boss->info.hitbox = (f32*) LOAD_ASSET(D_SX_603265C);
                    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 1);
                    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 1);
                    boss->timer_052 = 40;
                    gScreenFlashTimer = 5;
                }
            } else {
                func_effect_8007A6F0(&boss->obj.pos, NA_SE_EN_REFLECT);
            }
        } else {
            func_effect_8007A6F0(&boss->obj.pos, NA_SE_EN_REFLECT);
        }

        if (boss->swork[0] == 2) {
            if (boss->dmgPart == 0) {
                boss->health -= boss->damage;

                AUDIO_PLAY_SFX(NA_SE_EN_DAMAGE_S, boss->sfxSource, 4);

                if (boss->health <= 0) {
                    gTeamLowHealthMsgTimer = -1;
                    boss->obj.rot.y = Math_ModF(boss->obj.rot.y, 360.0f);
                    boss->state = 20;
                    boss->timer_050 = 300;
                    boss->fwork[0] = 0.0f;
                    boss->unk_04C = 0;

                    Radio_PlayMessage(gMsg_ID_5499, RCID_BOSS_SECTORX);

                    func_effect_8007BFFC(boss->obj.pos.x, boss->obj.pos.y + 300.0f, boss->obj.pos.z, 0.0f, 0.0f, 0.0f,
                                         10.0f, 50);

                    func_effect_8007C120(boss->obj.pos.x, boss->obj.pos.y + 334.0f, -237.0f + boss->obj.pos.z,
                                         boss->vel.x, boss->vel.y, boss->vel.z, 0.15f, 70);

                    for (i = 0; i < 10; i++) {
                        Play_SpawnDebris(4, boss->obj.pos.x, boss->obj.pos.y + 334.0f, -237.0f + boss->obj.pos.z);
                    }

                    boss->swork[4] = 2;

                    AUDIO_PLAY_SFX(NA_SE_EN_DOWN_IMPACT, boss->sfxSource, 4);

                    gScreenFlashTimer = 8;
                    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 1);
                    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 1);
                    Boss_AwardBonus(boss);
                    boss->info.hitbox = gNoHitbox;
                }

                boss->timer_054 = 20;
                boss->timer_05C = boss->timer_054;
                func_effect_8007C120(boss->obj.pos.x, boss->obj.pos.y, boss->obj.pos.z, boss->vel.x, boss->vel.y,
                                     boss->vel.z, 0.2f, 10);
            } else {
                func_effect_8007A6F0(&boss->obj.pos, NA_SE_EN_REFLECT);
            }
        }
    }

    if (((boss->state != 8) && (boss->state != 20)) && (gPlayer[0].state_1C8 != PLAYERSTATE_1C8_ACTIVE)) {
        boss->state = 8;
        boss->fwork[0] = 0.0f;
        Audio_KillSfxBySourceAndId(D_i2_80195D88, NA_SE_EN_SZMIS_ENGINE);
        Audio_KillSfxBySourceAndId(D_i2_80195D98, NA_SE_EN_SZMIS_ENGINE);
    }

    boss->vel.z = -20.0f;

    switch (boss->state) {
        case 0:
            boss->swork[7] = 1;
            boss->obj.pos.x = gPlayer[0].xPath;
            boss->swork[0] = 0;
            Animation_GetFrameData(D_SX_60206DC, boss->unk_04C, boss->vwork);
            boss->fwork[1] = -2000.0f;
            boss->fwork[14] = 300.0f;
            boss->fwork[17] = -300.0f;
            boss->fwork[16] = 3500.0f;
            boss->fwork[19] = 3000.0f;
            boss->state = 90;
            boss->timer_050 = 450;
            boss->swork[3] = 400;
            boss->health = 300;
            boss->info.hitbox = (f32*) LOAD_ASSET(D_SX_6032550);
            gBossActive = true;
            AUDIO_PLAY_BGM(gBossBgms[gCurrentLevel]);
            boss->swork[6] = 1;
            boss->fwork[44] = 5.0f;
            boss->fwork[43] = 5.0f;
            boss->fwork[42] = 30.0f;
            break;

        case 90:
            if ((boss->timer_050 == 110) || (boss->timer_050 == 66)) {
                AUDIO_PLAY_SFX(NA_SE_EN_COMBINE, boss->sfxSource, 4);
            }

            if (fabsf(Math_SmoothStepToF(&boss->fwork[16], 0.0f, 0.1f, 10.0f, 0)) < 8.0f) {
                Math_SmoothStepToF(&boss->fwork[14], 0.0f, 0.2f, 10.0f, 0);
                if ((boss->timer_050 % 8) == 0) {
                    func_effect_8007C120(boss->obj.pos.x + 312.0f, boss->obj.pos.y, boss->obj.pos.z - 173.0f,
                                         boss->vel.x, boss->vel.y, boss->vel.z, 0.2f, 8);
                }
            }

            if (fabsf(Math_SmoothStepToF(&boss->fwork[19], 0.0f, 0.1f, 10.0f, 0)) < 8.0f) {
                Math_SmoothStepToF(&boss->fwork[17], 0.0f, 0.2f, 10.0f, 0);
                if ((boss->timer_050 % 8) == 0) {
                    func_effect_8007C120(boss->obj.pos.x - 312.0f, boss->obj.pos.y, boss->obj.pos.z - 173.0f,
                                         boss->vel.x, boss->vel.y, boss->vel.z, 0.2f, 8);
                }
            }

            if (boss->timer_050 == 0) {
                boss->state = 100;
                boss->fwork[0] = 0.0f;
                AUDIO_PLAY_SFX(NA_SE_EN_MOTOR_ROLL, boss->sfxSource, 4);
            }
            boss->fwork[43] = boss->fwork[44] = 5.0f;
            boss->fwork[42] = 30.0f;
            break;

        case 100:
            boss->fwork[1] = -2000.0f;

            frameData = Animation_GetFrameData(D_SX_60206DC, boss->unk_04C, sp80);
            Math_SmoothStepToVec3fArray(sp80, boss->vwork, 1, frameData, boss->fwork[0], 100.0f, 0.0f);

            Math_SmoothStepToF(&boss->fwork[0], 1.0f, 1.0f, 0.05f, 0);
            boss->unk_04C++;

            if (boss->unk_04C >= Animation_GetFrameCount(D_SX_60206DC)) {
                boss->unk_04C = 0;
                boss->state = 1;
                boss->fwork[0] = 0.0f;
                AUDIO_PLAY_SFX(NA_SE_EN_UNIT_COMBINE, boss->sfxSource, 4);
            }

            boss->fwork[43] = boss->fwork[44] = 5.0f;
            boss->fwork[42] = 30.0f;
            break;

        case 1: // Taunt
            boss->fwork[1] = -1800.0f;
            boss->fwork[3] = gPlayer[0].pos.x;
            boss->fwork[2] = gPlayer[0].pos.y;
            boss->fwork[42] = 30.0f;
            boss->fwork[44] = 5.0f;
            boss->fwork[43] = 5.0f;

            frameData = Animation_GetFrameData(D_SX_6016E28, boss->unk_04C, sp80);
            Math_SmoothStepToVec3fArray(sp80, boss->vwork, 1, frameData, boss->fwork[0], 100.0f, 0.0f);

            Math_SmoothStepToF(&boss->fwork[0], 1.0f, 1.0f, 0.05f, 0);

            boss->unk_04C++;
            if (boss->unk_04C >= Animation_GetFrameCount(D_SX_6016E28)) {
                boss->unk_04C = 0;
                boss->state = 2;
                boss->fwork[0] = 0.0f;
                boss->swork[1] = 1;
                boss->swork[0] = 1;
                Radio_PlayMessage(gMsg_ID_5494, RCID_BOSS_SECTORX);
            }
            break;

        case 2: // right arm attack
            attack = true;
            boss->fwork[3] = gPlayer[0].pos.x;
            boss->fwork[2] = gPlayer[0].pos.y;

            if (boss->unk_04C > 60) {
                boss->fwork[1] = -1000.0f;
                Math_SmoothStepToF(&boss->fwork[42], 100.0f, 1.0f, 20.0f, 0);
                boss->fwork[43] = boss->fwork[44] = 10.0f;
            } else {
                boss->fwork[1] = -2000.0f;
                Math_SmoothStepToF(&boss->fwork[42], 30.0f, 1.0f, 3.0f, 0);
                boss->fwork[43] = boss->fwork[44] = 10.0f;
            }

            if (boss->unk_04C == 60) {
                AUDIO_PLAY_SFX(NA_SE_EN_THROW, boss->sfxSource, 4);
                boss->fwork[42] = 0.0f;
            }

            frameData = Animation_GetFrameData(D_SX_60123BC, boss->unk_04C, sp80);
            Math_SmoothStepToVec3fArray(sp80, boss->vwork, 1, frameData, boss->fwork[0], 100.0f, 0.0f);

            Math_SmoothStepToF(&boss->fwork[0], 1.0f, 1.0f, 0.05f, 0);

            boss->unk_04C++;
            if (boss->unk_04C >= Animation_GetFrameCount(D_SX_60123BC)) {
                boss->unk_04C = 0;
                boss->state = 3;
                boss->fwork[42] = boss->fwork[43] = boss->fwork[44] = boss->fwork[0] = 0.0f;
                boss->swork[7] = 0;
            }
            break;

        case 3: // left arm attack
            attack = true;
            boss->fwork[3] = gPlayer[0].pos.x;
            boss->fwork[2] = gPlayer[0].pos.y;

            if (boss->unk_04C > 60) {
                boss->fwork[1] = -1000.0f;
                Math_SmoothStepToF(&boss->fwork[42], 100.0f, 1.0f, 20.0f, 0);
                boss->fwork[44] = 10.0f;
                boss->fwork[43] = 10.0f;
            } else {
                boss->fwork[1] = -2500.0f;
                Math_SmoothStepToF(&boss->fwork[42], 30.0f, 1.0f, 3.0f, 0);
                boss->fwork[44] = 10.0f;
                boss->fwork[43] = 10.0f;
            }

            if (boss->unk_04C == 60) {
                AUDIO_PLAY_SFX(NA_SE_EN_THROW, boss->sfxSource, 4);
                boss->fwork[42] = 0.0f;
            }

            frameData = Animation_GetFrameData(D_SX_6013798, boss->unk_04C, sp80);
            Math_SmoothStepToVec3fArray(sp80, boss->vwork, 1, frameData, boss->fwork[0], 100.0f, 0.0f);

            Math_SmoothStepToF(&boss->fwork[0], 1.0f, 1.0f, 0.05f, 0);

            boss->unk_04C++;
            if (boss->unk_04C >= Animation_GetFrameCount(D_SX_6013798)) {
                boss->unk_04C = 0;
                boss->fwork[0] = 0.0f;
                if (boss->swork[3] <= 250) {
                    boss->state = 4;
                    boss->timer_050 = 100;
                    Radio_PlayMessage(gMsg_ID_5495, RCID_BOSS_SECTORX);
                    boss->fwork[44] = 0.0f;
                    boss->fwork[43] = 0.0f;
                    boss->fwork[42] = 0.0f;
                } else {
                    boss->state = 1;
                    boss->swork[1] = 1;
                    boss->swork[7] = 1;
                }
            }
            break;

        case 4: // Arms launch setup
            boss->swork[7] = 0;
            boss->fwork[1] = -3000.0f;
            boss->fwork[3] = gPlayer[0].pos.x;
            boss->fwork[2] = gPlayer[0].pos.y;

            Math_SmoothStepToF(&boss->fwork[44], 10.0f, 1.0f, 1.0f, 0);
            Math_SmoothStepToF(&boss->fwork[43], 10.0f, 1.0f, 1.0f, 0);
            Math_SmoothStepToF(&boss->fwork[42], 50.0f, 1.0f, 3.0f, 0);

            frameData = Animation_GetFrameData(D_SX_6016E28, 0, sp80);
            Math_SmoothStepToVec3fArray(sp80, boss->vwork, 1, frameData, boss->fwork[0], 100.0f, 0.0f);

            Math_SmoothStepToF(&boss->fwork[0], 1.0f, 1.0f, 0.05f, 0);
            Math_SmoothStepToF(&boss->fwork[27], 30.0f, 0.05f, 1.0f, 0);
            Math_SmoothStepToF(&boss->fwork[28], -30.0f, 0.05f, 1.0f, 0);

            if (boss->timer_050 == 0) {
                boss->state = 5;
                boss->timer_050 = 100;
                Radio_PlayMessage(gMsg_ID_5496, RCID_FOX);
            }
            break;

        case 5: // arms lauching attack
            sp74.x = boss->fwork[8] + boss->obj.pos.x;
            sp74.y = boss->fwork[9] + boss->obj.pos.y;
            sp74.z = boss->fwork[10] + boss->obj.pos.z;

            Object_SetSfxSourceToPos(D_i2_80195D88, &sp74);
            AUDIO_PLAY_SFX(NA_SE_EN_SZMIS_ENGINE, D_i2_80195D88, 4);

            sp74.x = boss->fwork[11] + boss->obj.pos.x;
            sp74.y = boss->fwork[12] + boss->obj.pos.y;
            sp74.z = boss->fwork[13] + boss->obj.pos.z;

            Object_SetSfxSourceToPos(D_i2_80195D98, &sp74);
            AUDIO_PLAY_SFX(NA_SE_EN_SZMIS_ENGINE, D_i2_80195D98, 4);

            Math_SmoothStepToF(&boss->fwork[27], 30.0f, 0.05f, 1.0f, 0);
            Math_SmoothStepToF(&boss->fwork[28], -30.0f, 0.05f, 1.0f, 0);

            sp60 = fabsf(boss->obj.pos.x + boss->fwork[8] - gPlayer[0].pos.x) * 0.1f;

            if (sp60 > 5.0f) {
                sp60 = 5.0f;
            }

            if ((boss->obj.pos.x + boss->fwork[8]) < gPlayer[0].pos.x) {
                boss->fwork[29] += sp60;
            }

            if (gPlayer[0].pos.x < (boss->obj.pos.x + boss->fwork[8])) {
                boss->fwork[29] -= sp60;
            }

            sp60 = fabsf((boss->obj.pos.y + boss->fwork[9]) - gPlayer[0].pos.y) * 0.1f;

            if (sp60 > 5.0f) {
                sp60 = 5.0f;
            }

            if ((boss->obj.pos.y + boss->fwork[9]) < gPlayer[0].pos.y) {
                boss->fwork[30] += sp60;
            }

            if (gPlayer[0].pos.y < (boss->obj.pos.y + boss->fwork[9])) {
                boss->fwork[30] -= sp60;
            }

            sp60 = fabsf((boss->obj.pos.x + boss->fwork[11]) - gPlayer[0].pos.x) * 0.1f;

            if (sp60 > 5.0f) {
                sp60 = 5.0f;
            }

            if ((boss->obj.pos.x + boss->fwork[11]) < gPlayer[0].pos.x) {
                boss->fwork[32] += sp60;
            }

            if (gPlayer[0].pos.x < (boss->obj.pos.x + boss->fwork[11])) {
                boss->fwork[32] -= sp60;
            }

            sp60 = fabsf((boss->obj.pos.y + boss->fwork[12]) - gPlayer[0].pos.y) * 0.1f;

            if (sp60 > 5.0f) {
                sp60 = 5.0f;
            }

            if ((boss->obj.pos.y + boss->fwork[12]) < gPlayer[0].pos.y) {
                boss->fwork[33] += sp60;
            }

            if (gPlayer[0].pos.y < (boss->obj.pos.y + boss->fwork[12])) {
                boss->fwork[33] -= sp60;
            }

            Math_SmoothStepToF(&boss->fwork[31], 4000.0f, 1.0f, 80.0f, 0);

            if (boss->timer_050 < 70) {
                Math_SmoothStepToF(&boss->fwork[34], 4000.0f, 1.0f, 80.0f, 0);
            }

            if (boss->timer_050 == 0) {
                boss->state = 6;
                boss->timer_050 = 122;
            }
            break;

        case 6: // Arms come back to robot
            if ((boss->timer_050 == 20) || (boss->timer_050 == 30)) {
                AUDIO_PLAY_SFX(NA_SE_EN_COMBINE, boss->sfxSource, 4);
            }

            if (boss->timer_050 == 0) {
                boss->unk_04C = 0;
                boss->state = 1;
                boss->swork[1] = 1;
                Audio_KillSfxBySourceAndId(D_i2_80195D88, NA_SE_EN_SZMIS_ENGINE);
                Audio_KillSfxBySourceAndId(D_i2_80195D98, NA_SE_EN_SZMIS_ENGINE);
                boss->fwork[0] = 0.0f;
                boss->fwork[44] = 0.0f;
                boss->fwork[43] = 0.0f;
                boss->fwork[42] = 0.0f;
                boss->swork[7] = 1;
            }
            break;

        case 7:
            if (boss->timer_052 == 1) {
                Radio_PlayMessage(gMsg_ID_15252, RCID_SLIPPY);
            }
            boss->fwork[41] = 20.0;
            boss->fwork[2] = -400.0f;
            boss->fwork[42] = 30.0f;

            frameData = Animation_GetFrameData(D_SX_601C690, boss->unk_04C, sp80);
            Math_SmoothStepToVec3fArray(sp80, boss->vwork, 1, frameData, boss->fwork[0], 100.0f, 0.0f);

            Math_SmoothStepToF(&boss->fwork[0], 1.0f, 1.0f, 0.05f, 0);

            boss->unk_04C++;
            if (boss->unk_04C >= Animation_GetFrameCount(D_SX_601C690)) {
                boss->state = 75;
                boss->fwork[0] = 0.0f;
                boss->unk_04C = 0;
                boss->timer_050 = 120;
            }
            break;

        case 75:
            boss->fwork[41] = 20.0f;
            boss->fwork[2] = -400.0f;

            frameData = Animation_GetFrameData(D_SX_600A2D4, 0, sp80);
            Math_SmoothStepToVec3fArray(sp80, boss->vwork, 1, frameData, boss->fwork[0], 2.5f, 0.0f);

            Math_SmoothStepToF(&boss->fwork[0], 0.1f, 1.0f, 0.005f, 0);

            if (boss->timer_050 == 0) {
                boss->state = 8;
                boss->fwork[0] = 0.0f;
                boss->unk_04C = 0;
                boss->health = 300;
                Audio_PlaySequenceDistorted(0, gBossBgms[gCurrentLevel], 1121, 25, -1);
                Radio_PlayMessage(gMsg_ID_19205, RCID_FOX);
                boss->timer_052 = 100;
            }
            break;

        case 8:
            if (boss->timer_052 == 1) {
                Radio_PlayMessage(gMsg_ID_5497, RCID_BOSS_SECTORX);
            }
            boss->fwork[41] = 0.0f;
            boss->fwork[2] = gPlayer[0].pos.y;
            boss->fwork[3] = gPlayer[0].pos.x;
            boss->fwork[44] = 5.0f;
            boss->fwork[1] = -1800.0f;
            boss->fwork[43] = 5.0f;
            boss->fwork[42] = 30.0f;

            frameData = Animation_GetFrameData(D_SX_600F890, boss->unk_04C, sp80);
            Math_SmoothStepToVec3fArray(sp80, boss->vwork, 1, frameData, boss->fwork[0], 100.0f, 0.0f);

            Math_SmoothStepToF(&boss->fwork[0], 1.0f, 1.0f, 0.02f, 0);

            boss->unk_04C++;
            if (boss->unk_04C >= Animation_GetFrameCount(D_SX_600F890)) {
                boss->unk_04C = 0;
                boss->fwork[0] = 0.0f;
                boss->state = 9;
                boss->swork[0] = 2;
                boss->timer_050 = 30;
            }
            break;

        case 85:
            boss->fwork[1] = -3000.0f;
            boss->fwork[2] = gPlayer[0].pos.y;
            boss->fwork[3] = gPlayer[0].pos.x;

            frameData = Animation_GetFrameData(D_SX_60123BC, boss->unk_04C, sp80);
            Math_SmoothStepToVec3fArray(sp80, boss->vwork, 1, frameData, boss->fwork[0], 50.0f, 0.0f);

            Math_SmoothStepToF(&boss->fwork[0], 1.0f, 1.0f, 0.01f, 0);

            if (boss->timer_050 == 0) {
                boss->unk_04C++;
                if (boss->unk_04C >= Animation_GetFrameCount(D_SX_60123BC)) {
                    boss->unk_04C = Animation_GetFrameCount(D_SX_60123BC) - 1;
                    if (gPlayer[0].state_1C8 != PLAYERSTATE_1C8_STANDBY) {
                        boss->unk_04C = 0;
                        boss->state = 10;
                        boss->fwork[0] = 0.0f;
                        boss->fwork[42] = 0.0f;
                    }
                }
                if (boss->unk_04C == 60) {
                    AUDIO_PLAY_SFX(NA_SE_EN_THROW, boss->sfxSource, 4);
                }
            } else if (boss->timer_050 == 1) {
                Radio_PlayMessage(gMsg_ID_20267, RCID_PEPPY);
            }
            break;

        case 9:
            if (boss->timer_050 == 1) {
                Radio_PlayMessage(gMsg_ID_5492, RCID_BOSS_SECTORX);
            }
            boss->fwork[1] = -2000.0f;
            boss->fwork[2] = gPlayer[0].pos.y;
            boss->fwork[3] = gPlayer[0].pos.x;

            frameData = Animation_GetFrameData(D_SX_601AA28, boss->unk_04C, sp80);
            Math_SmoothStepToVec3fArray(sp80, boss->vwork, 1, frameData, boss->fwork[0], 50.0f, 0.0f);

            Math_SmoothStepToF(&boss->fwork[0], 1.0f, 1.0f, 0.01f, 0);
            boss->unk_04C++;

            if (boss->unk_04C >= Animation_GetFrameCount(D_SX_601AA28)) {
                boss->unk_04C = 0;
                boss->state = 10;
                boss->fwork[0] = 0.0f;
                boss->fwork[42] = 0.0f;
                if (boss->swork[10] == 0) {
                    Radio_PlayMessage(gMsg_ID_5474, RCID_FALCO);
                }
                boss->swork[10] = 1;
            }

            if (boss->unk_04C == 70) {
                SectorX_8018FA04(boss->fwork[11] + boss->obj.pos.x, boss->fwork[12] + boss->obj.pos.y,
                                 boss->fwork[13] + boss->obj.pos.z);
                AUDIO_PLAY_SFX(NA_SE_EN_THROW, boss->sfxSource, 4);
            }
            break;

        case 10:
            attack = true;
            boss->fwork[1] = -1000.0f;
            Math_SmoothStepToF(&boss->fwork[42], 50.0f, 1.0f, 3.0f, 0);

            frameData = Animation_GetFrameData(D_SX_60158C4, boss->unk_04C, sp80);
            Math_SmoothStepToVec3fArray(sp80, boss->vwork, 1, frameData, boss->fwork[0], 100.0f, 0.0f);

            Math_SmoothStepToF(&boss->fwork[0], 1.0f, 1.0f, 0.05f, 0);

            boss->unk_04C++;
            if ((boss->unk_04C % 16) == 0) {
                AUDIO_PLAY_SFX(NA_SE_EN_THROW, boss->sfxSource, 4);
            }

            if (boss->unk_04C >= Animation_GetFrameCount(D_SX_60158C4)) {
                boss->unk_04C = 0;
                boss->fwork[0] = 0.0f;

                if ((gBossFrameCount < 2200) || (gTeamShields[TEAM_ID_SLIPPY] <= 0)) {
                    if (boss->health > 150) {
                        boss->state = 8;
                    } else {
                        boss->state = 35;
                        boss->timer_050 = 400;
                        boss->fwork[42] = boss->fwork[43] = boss->fwork[44] = boss->rot_078.y = 0.0f;
                        boss->swork[9] = RAND_INT(1.9f);
                        Radio_PlayMessage(gMsg_ID_5498, RCID_BOSS_SECTORX);
                    }
                } else {
                    boss->state = 85;
                    SectorX_8018F030();
                    boss->timer_050 = 100;
                }
            }
            break;

        case 35:
            if (boss->swork[9] != 0) {
                boss->fwork[2] = 500.0f;
            } else {
                boss->fwork[2] = -500.0f;
            }

            if (boss->timer_050 > 300) {
                boss->fwork[3] = 1000.0f;
                boss->fwork[1] = -2000.0f;
            } else if (boss->timer_050 > 200) {
                boss->fwork[3] = -1000.0f;
                boss->fwork[1] = -2500.0f;
                if ((gGameFrameCount % 16) == 0) {
                    AUDIO_PLAY_SFX(NA_SE_EN_THROW, boss->sfxSource, 4);
                }
            } else if (boss->timer_050 > 100) {
                boss->fwork[3] = 0;
                boss->fwork[1] = -500.0f;
                if (((gGameFrameCount % 16) == 0)) {
                    AUDIO_PLAY_SFX(NA_SE_EN_THROW, boss->sfxSource, 4);
                }
            } else {
                boss->fwork[3] = 0;
                boss->fwork[1] = -2000.0f;
            }

            Math_SmoothStepToF(&boss->fwork[42], 60.0f, 1.0f, 1.0f, 0);
            Math_SmoothStepToF(&boss->fwork[44], 20.0f, 1.0f, 0.5f, 0);
            Math_SmoothStepToF(&boss->fwork[43], 20.0f, 1.0f, 0.5f, 0);

            frameData = Animation_GetFrameData(D_SX_6009FF8, 0, sp80);
            Math_SmoothStepToVec3fArray(sp80, boss->vwork, 1, frameData, boss->fwork[0], 5.0f, 0.0f);

            Math_SmoothStepToF(&boss->fwork[0], 0.1f, 1.0f, 0.001f, 0);
            Math_SmoothStepToF(&boss->rot_078.y, 10.0f, 1.0f, 0.1f, 0);
            Math_SmoothStepToF(&boss->obj.rot.y, 2880.0f, 0.1f, boss->rot_078.y, 0.1f);

            if ((boss->timer_050 == 0) && (boss->obj.rot.y == 2880.0f)) {
                boss->obj.rot.y = 0.0f;
                boss->unk_04C = 0;
                boss->fwork[0] = 0.0f;
                if ((gBossFrameCount < 2200) || (gTeamShields[TEAM_ID_SLIPPY] <= 0)) {
                    boss->state = 9;
                } else {
                    boss->state = 85;
                    SectorX_8018F030();
                    boss->timer_050 = 100;
                }
            }
            break;

        case 20:
            Math_SmoothStepToF(&boss->obj.rot.y, 0.0f, 0.1f, 3.0f, 0.1f);
            boss->swork[0] = 0;
            boss->fwork[1] = -1800.0f;
            boss->fwork[41] = 340.0f;
            boss->fwork[2] = -400.0f;

            frameData = Animation_GetFrameData(D_SX_601C690, boss->unk_04C, sp80);
            Math_SmoothStepToVec3fArray(sp80, boss->vwork, 1, frameData, boss->fwork[0], 100.0f, 0.0f);

            Math_SmoothStepToF(&boss->fwork[0], 1.0f, 1.0f, 0.05f, 0);
            boss->unk_04C++;

            if (boss->unk_04C >= Animation_GetFrameCount(D_SX_601C690)) {
                boss->unk_04C = Animation_GetFrameCount(D_SX_601C690);
            }

            if ((boss->timer_050 & 3) == 0) {
                func_effect_8007D2C8(RAND_FLOAT_CENTERED(500.0f) + boss->obj.pos.x,
                                     RAND_FLOAT_CENTERED(500.0f) + boss->obj.pos.y, boss->obj.pos.z + 100.0f,
                                     RAND_FLOAT(5.0f) + 5.0f);
            }

            if ((((gGameFrameCount % 8) == 0)) && (Rand_ZeroOne() < 0.5f)) {
                boss->timer_05C = 4;
            }

            if ((boss->timer_050 & 3) == 0) {
                func_effect_8007C120(boss->obj.pos.x, boss->obj.pos.y, boss->obj.pos.z, boss->vel.x, boss->vel.y,
                                     boss->vel.z, 0.3f, 10);
            }

            if (boss->timer_050 < 230) {
                Math_SmoothStepToF(&boss->fwork[14], 10000.0f, 1.0f, 60.0f, 0);
                Math_SmoothStepToF(&boss->fwork[17], -10000.0f, 1.0f, 60.0f, 0);
            }

            if (boss->timer_050 == 230) {
                gShowBossHealth = 0;
                func_effect_8007BFFC(boss->obj.pos.x, boss->obj.pos.y, boss->obj.pos.z, 0.0f, 0.0f, 0.0f, 30.0f, 40);
                func_effect_8007A568(boss->obj.pos.x, boss->obj.pos.y, boss->obj.pos.z, 40.0f);
            }

            if (boss->timer_050 == 210) {
                boss->swork[5] = 1;
                boss->timer_05A = 1000;
            }

            if (boss->timer_050 == 120) {
                if ((gPlayer[0].state_1C8 != PLAYERSTATE_1C8_NEXT) && (gPlayer[0].state_1C8 != PLAYERSTATE_1C8_DOWN)) {
                    gPlayer[0].state_1C8 = PLAYERSTATE_1C8_LEVEL_COMPLETE;
                    gPlayer[0].csState = 0;
                    gPlayer[0].unk_234 = 1;
                }
                Object_Kill(&boss->obj, boss->sfxSource);
                gMissionStatus = boss->swork[6];
            }
            break;

        default:
            break;
    }

    D_i2_80195640 = 1;

    Animation_DrawSkeleton(1, D_SX_6020C68, boss->vwork, SectorX_80192AF0, SectorX_80193208, boss, &gIdentityMatrix);

    if (((boss->swork[1] != 0) && (boss->swork[3] > 0)) && ((boss->fwork[4] < 45.0f) || (boss->fwork[4] > 315.0f))) {
        boss->swork[1]++;
        if (boss->swork[1] > 40) {
            if (boss->swork[1] > 50) {
                boss->swork[1] = 0;
            }
            func_effect_8007F11C(OBJ_EFFECT_377, boss->fwork[20] + boss->obj.pos.x, boss->fwork[21] + boss->obj.pos.y,
                                 boss->fwork[22] + boss->obj.pos.z, 100.0f);
            func_effect_8007F11C(OBJ_EFFECT_377, boss->fwork[23] + boss->obj.pos.x, boss->fwork[24] + boss->obj.pos.y,
                                 boss->fwork[25] + boss->obj.pos.z, 100.0f);
        }
    } else {
        boss->swork[1] = 0;
    }

    if (boss->state != 35) {
        boss->info.hitbox = (f32*) LOAD_ASSET(D_SX_6032550);
        boss->info.hitbox[43] = -211.0f + boss->fwork[16];
        boss->info.hitbox[45] = -35.0f + boss->fwork[15];
        boss->info.hitbox[47] = 442.0f + boss->fwork[14];
        boss->info.hitbox[49] = -211.0f + boss->fwork[19];
        boss->info.hitbox[51] = -35.0f + boss->fwork[18];
        boss->info.hitbox[53] = -442.0f + boss->fwork[17];
        boss->info.hitbox[55] = boss->fwork[10];
        boss->info.hitbox[57] = boss->fwork[9];
        boss->info.hitbox[59] = boss->fwork[8];
        boss->info.hitbox[61] = boss->fwork[13];
        boss->info.hitbox[63] = boss->fwork[12];
        boss->info.hitbox[65] = boss->fwork[11];

        if (attack) {
            boss->info.hitbox[56] = 200.0f;
            boss->info.hitbox[58] = 200.0f;
            boss->info.hitbox[60] = 100.0f;
            boss->info.hitbox[62] = 200.0f;
            boss->info.hitbox[64] = 200.0f;
            boss->info.hitbox[66] = 100.0f;
        } else {
            boss->info.hitbox[56] = 200.0f;
            boss->info.hitbox[58] = 100.0f;
            boss->info.hitbox[60] = 70.0f;
            boss->info.hitbox[62] = 200.0f;
            boss->info.hitbox[64] = 100.0f;
            boss->info.hitbox[66] = 70.0f;
        }
    } else {
        boss->info.hitbox = (f32*) LOAD_ASSET(D_SX_6032768);
    }

    if (boss->swork[0] == 1) {
        Math_SmoothStepToF(&boss->fwork[45], 1.0f, 1.0f, 0.05f, 0);
    } else {
        Math_SmoothStepToF(&boss->fwork[45], 0.0f, 1.0f, 0.05f, 0);
    }
}

bool SectorX_80192AF0(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* data) {
    Vec3f sp64 = { 0.0f, 0.0f, 0.0f };
    Vec3f sp58;
    Boss* boss = (Boss*) data;

    if (D_i2_80195640 != 0) {
        *dList = NULL;
    }

    if ((boss->timer_05C % 2) == 0) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_29);
    } else {
        RCP_SetupDL(&gMasterDisp, SETUPDL_27);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 0, 0, 255);
    }

    switch (limbIndex) {
        case 1:
            rot->x += boss->fwork[4] + boss->fwork[5];
            rot->z += boss->fwork[6] + boss->fwork[7];
            if ((boss->timer_054 % 2) != 0) {
                RCP_SetupDL_27();
                gDPSetPrimColor(gMasterDisp++, 0, 0, 64, 64, 255, 255);
            }
            if (boss->swork[4] == 1) {
                *dList = D_SX_6006810;
            } else if (boss->swork[4] == 2) {
                *dList = NULL;
            }

            Matrix_Translate(gCalcMatrix, pos->x, pos->y, pos->z, MTXF_APPLY);
            Matrix_RotateZ(gCalcMatrix, rot->z * M_DTOR, MTXF_APPLY);
            Matrix_RotateY(gCalcMatrix, rot->y * M_DTOR, MTXF_APPLY);
            Matrix_RotateX(gCalcMatrix, rot->x * M_DTOR, MTXF_APPLY);

            if (*dList != NULL) {
                Matrix_Push(&gGfxMatrix);
                Matrix_Push(&gCalcMatrix);
                Matrix_MultVec3f(gCalcMatrix, &sp64, &sp58);
                Display_SetSecondLight(&sp58);
                Matrix_Mult(gGfxMatrix, gCalcMatrix, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, *dList);
                if (boss->swork[4] == 0) {
                    RCP_SetupDL(&gMasterDisp, SETUPDL_41);
                    if (((gGameFrameCount % 2) == 0)) {
                        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
                    } else {
                        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);
                    }
                    Matrix_Push(&gGfxMatrix);
                    Matrix_Translate(gGfxMatrix, D_i2_80195644.x, D_i2_80195644.y, D_i2_80195644.z, (u8) MTXF_APPLY);
                    Matrix_RotateZ(gGfxMatrix, D_i2_80195650.z * M_DTOR, MTXF_APPLY);
                    Matrix_RotateY(gGfxMatrix, D_i2_80195650.y * M_DTOR, MTXF_APPLY);
                    Matrix_RotateX(gGfxMatrix, D_i2_80195650.x * M_DTOR, MTXF_APPLY);
                    Matrix_RotateZ(gGfxMatrix, 2.0f * gGameFrameCount * M_DTOR, MTXF_APPLY);
                    Matrix_Scale(gGfxMatrix, boss->fwork[45], boss->fwork[45], boss->fwork[45], MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_SX_6009C30);
                    Matrix_Pop(&gGfxMatrix);
                    Matrix_Translate(gGfxMatrix, D_i2_8019565C.x, D_i2_8019565C.y, D_i2_8019565C.z, (u8) MTXF_APPLY);
                    Matrix_RotateZ(gGfxMatrix, D_i2_80195668.z * M_DTOR, MTXF_APPLY);
                    Matrix_RotateY(gGfxMatrix, D_i2_80195668.y * M_DTOR, MTXF_APPLY);
                    Matrix_RotateX(gGfxMatrix, D_i2_80195668.x * M_DTOR, MTXF_APPLY);
                    Matrix_RotateZ(gGfxMatrix, 2.0f * -gGameFrameCount * M_DTOR, MTXF_APPLY);
                    Matrix_Scale(gGfxMatrix, boss->fwork[45], boss->fwork[45], boss->fwork[45], MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_SX_6009C30);
                }
                Matrix_Pop(&gGfxMatrix);
                Matrix_Pop(&gCalcMatrix);
            }
            return true;

        case 34:
            rot->x += boss->fwork[27];
            break;

        case 33:
            pos->z -= boss->fwork[31];
            pos->y -= boss->fwork[29];
            pos->x -= boss->fwork[30];
            break;

        case 38:
            rot->x += boss->fwork[28];
            break;

        case 37:
            pos->z += boss->fwork[34];
            pos->y += boss->fwork[32];
            pos->x -= boss->fwork[33];
            break;

        case 35:
            pos->x -= boss->fwork[14];
            pos->y -= boss->fwork[16];
            pos->z -= boss->fwork[15];
            if (boss->state == 20) {
                rot->x += boss->fwork[14] * 0.2f;
                rot->y += boss->fwork[14] * 0.1f;
            }
            break;

        case 39:
            pos->x += boss->fwork[17];
            pos->y -= boss->fwork[19];
            pos->z += boss->fwork[18];
            if (boss->state == 20) {
                rot->x += boss->fwork[17] * 0.1f;
                rot->z += boss->fwork[17] * 0.2f;
            }
            break;
    }

    return false;
}

void SectorX_80193208(s32 limbIndex, Vec3f* rot, void* data) {
    Vec3f sp64 = { 87.0f, -323.0f, 200.0f };
    Vec3f sp58 = { 87.0f, -323.0f, -200.0f };
    Vec3f sp4C = { 87.0f, -323.0f, 200.0f };
    Vec3f sp40 = { 87.0f, -323.0f, -200.0f };
    Vec3f sp34;
    Vec3f sp28;
    Boss* boss = (Boss*) data;

    sp34.x = 0.0f;
    sp34.y = 0.0f;
    sp34.z = 0.0f;

    switch (limbIndex) {
        case 1:
            Matrix_MultVec3f(gCalcMatrix, &sp58, &sp28);
            boss->fwork[20] = sp28.x;
            boss->fwork[21] = sp28.y;
            boss->fwork[22] = sp28.z;
            Matrix_MultVec3f(gCalcMatrix, &sp64, &sp28);
            boss->fwork[23] = sp28.x;
            boss->fwork[24] = sp28.y;
            boss->fwork[25] = sp28.z;
            Matrix_MultVec3f(gCalcMatrix, &sp40, &boss->vwork[45]);
            Matrix_MultVec3f(gCalcMatrix, &sp4C, &boss->vwork[46]);
            break;

        case 6:
            Matrix_MultVec3f(gCalcMatrix, &sp34, &sp28);
            boss->fwork[8] = sp28.x;
            boss->fwork[9] = sp28.y;
            boss->fwork[10] = sp28.z;
            break;

        case 16:
            Matrix_MultVec3f(gCalcMatrix, &sp34, &sp28);
            boss->fwork[11] = sp28.x;
            boss->fwork[12] = sp28.y;
            boss->fwork[13] = sp28.z;
            break;

        case 33:
            Matrix_MultVec3f(gCalcMatrix, &sp34, &sp28);
            boss->fwork[35] = sp28.x;
            boss->fwork[36] = sp28.y;
            boss->fwork[37] = sp28.z;
            break;

        case 37:
            Matrix_MultVec3f(gCalcMatrix, &sp34, &sp28);
            boss->fwork[38] = sp28.x;
            boss->fwork[39] = sp28.y;
            boss->fwork[40] = sp28.z;

        default:
            break;
    }
}

Vec3f D_i2_801956B0[5] = {
    { 0.0f, 2300.0f, -5000.0f },   { -600.0f, 2200.0f, -5000.0f }, { -300.0f, 2270.0f, -5000.0f },
    { 300.0f, 2270.0f, -5000.0f }, { 600.0f, 2200.0f, -5000.0f },
};
Vec3f D_i2_801956EC[3] = {
    { 150.0f, 250.0f, 50.0f },
    { -150.0f, -50.0f, 50.0f },
    { 150.0f, -50.0f, 50.0f },
};
f32 D_i2_80195710[4] = { -1200.0f, 1000.0f, 0.0f, 0.0f };
f32 D_i2_80195720[4] = { -300.0f, 400.0f, -400.0f, 0.0f };
f32 D_i2_80195730[4] = { -800.0f, -800.0f, -1000.0f, -8000.0f };
f32 D_i2_80195740[4] = { -150.0f, 150.0f, 0.0f, 0.0f };
f32 D_i2_80195750[4] = { 20.0f, 0.0f, -70.0f, 0.0f };
f32 D_i2_80195760[4] = { -250.0f, -200.0f, -400.0f, -8000.0f };
f32 D_i2_80195770[3] = { 120.0f, 180.0f, -150.0f };
s16 D_i2_8019577C[3] = { 2, 3, 4 };

void SectorX_80193434(Boss* boss) {
    f32 fwork;

    if (boss->swork[5] == 0) {
        D_i2_80195640 = 0;
        Animation_DrawSkeleton(3, D_SX_6020C68, boss->vwork, SectorX_80192AF0, 0, boss, gCalcMatrix);
        RCP_SetupDL_64();
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 96);

        if (boss->fwork[31] > 10.0f) {
            fwork = boss->fwork[31] * 0.1f;
            if (fwork > 50.0f) {
                fwork = 50.0f;
            }
            if ((gGameFrameCount % 2) != 0) {
                fwork *= 1.2f;
            }
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, boss->fwork[35], boss->fwork[36], boss->fwork[37], MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, fwork, fwork, fwork, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_102ED50);
            Matrix_Pop(&gGfxMatrix);
        }

        if (boss->fwork[34] > 10.0f) {
            fwork = boss->fwork[34] * 0.1f;
            if (fwork > 50.0f) {
                fwork = 50.0f;
            }
            if ((gGameFrameCount % 2) != 0) {
                fwork *= 1.2f;
            }
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, boss->fwork[38], boss->fwork[39], boss->fwork[40], MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, fwork, fwork, fwork, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_102ED50);
            Matrix_Pop(&gGfxMatrix);
        }

        RCP_SetupDL_64();
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 96);

        if (boss->swork[1] != 0) {
            fwork = boss->swork[1] * 0.1f;

            if (fwork > 4.0f) {
                fwork = 4.0f;
            }
            if ((gGameFrameCount % 2) != 0) {
                fwork *= 1.2f;
            }
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, boss->fwork[20], boss->fwork[21], boss->fwork[22], MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, fwork, fwork, fwork, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_SX_600F8A0);
            Matrix_Pop(&gGfxMatrix);
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, boss->fwork[23], boss->fwork[24], boss->fwork[25], MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, fwork, fwork, fwork, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_SX_600F8A0);
            Matrix_Pop(&gGfxMatrix);
        }
    }
}

void SectorX_80193800(Actor* actor, s32 arg1) {
    Actor_Initialize(actor);

    actor->obj.status = OBJ_ACTIVE;
    actor->obj.id = OBJ_ACTOR_CUTSCENE;
    actor->obj.pos.x = D_i2_801956B0[arg1].x;
    actor->obj.pos.y = D_i2_801956B0[arg1].y;
    actor->obj.pos.z = D_i2_801956B0[arg1].z;
    actor->vel.z = 30.0f;
    actor->vel.y = -16.0f;
    actor->animFrame = 20;
    actor->obj.rot.x = 15.0f;

    Object_SetInfo(&actor->info, actor->obj.id);
    AUDIO_PLAY_SFX(NA_SE_EN_ENGINE_01, actor->sfxSource, 4);
}

void SectorX_801938D8(Actor* actor, s32 arg1) {
    Actor_Initialize(actor);
    actor->obj.status = OBJ_ACTIVE;
    actor->obj.id = OBJ_ACTOR_CUTSCENE;
    actor->obj.pos.x = gPlayer[0].cam.eye.x + D_i2_801956EC[arg1].x;
    actor->obj.pos.y = gPlayer[0].cam.eye.y + D_i2_801956EC[arg1].y;
    actor->obj.pos.z = gPlayer[0].cam.eye.z + D_i2_801956EC[arg1].z;
    actor->state = 1;
    actor->iwork[11] = 1;
    actor->vel.z = -30.0f;
    actor->vel.y = 0.0f;
    actor->obj.rot.y = 180.0f;
    actor->obj.rot.x = 10.0f;
    if (arg1 == 2) {
        actor->obj.rot.z = -20.0f;
    }
    Object_SetInfo(&actor->info, actor->obj.id);
    AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, actor->sfxSource, 4);
    AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, actor->sfxSource, 0);
}

void SectorX_LevelStart(Player* player) {
    s32 i;
    Vec3f src;
    Vec3f dest;
    f32 x;
    f32 y;
    f32 z;
    f32 xzDeg;
    f32 xyzDeg;

    switch (player->csState) {
        case 0:
            gCsFrameCount = 0;
            for (i = 0; i < 5; i++) {
                SectorX_80193800(&gActors[5 + i], i);
            }
            player->csState = 1;
            player->cam.eye.x = gCsCamEyeX = 100.0f;
            player->cam.eye.y = gCsCamEyeY = 0.0f;
            player->cam.eye.z = gCsCamEyeZ = -200.0f;
            player->cam.at.x = gCsCamAtX = 0.0f;
            player->cam.at.y = gCsCamAtY = 0.0f;
            player->cam.at.z = gCsCamAtZ = -1000.0f;
            player->camRoll = -5.0f;
            player->baseSpeed = 0.0f;
            gFillScreenAlpha = 255;
            /* fallthrough */
        case 1:
            if (gCsFrameCount < 3) {
                gFillScreenAlpha = 255;
            }
            D_ctx_80177A48[0] = 0.5f;
            gCsCamAtX = gActors[5].obj.pos.x;
            gCsCamAtZ = gActors[5].obj.pos.z;
            player->camRoll -= 0.1f;
            if (gCsFrameCount == 140) {
                x = gActors[5].obj.pos.x;
                y = gActors[5].obj.pos.y - (player->cam.eye.y + 50.0f);
                z = gActors[5].obj.pos.z - (player->cam.eye.z + 20.0f);
                xzDeg = Math_RadToDeg(Math_Atan2F(x, z));
                xyzDeg = Math_RadToDeg(-Math_Atan2F(y, sqrtf(SQ(x) + SQ(z))));
                Matrix_RotateY(gCalcMatrix, M_DTOR * xzDeg, MTXF_NEW);
                Matrix_RotateX(gCalcMatrix, M_DTOR * xyzDeg, MTXF_APPLY);
                src.y = src.x = 0.0f;
                src.z = 100.0f;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);
                Actor_SpawnPlayerLaser(CS_SHOT_ID, 0.0f, player->cam.eye.y + 50.0f, player->cam.eye.z + 20.0f, dest.x,
                                       dest.y, dest.z, xyzDeg, xzDeg, 0.0f);
            }
            if (gCsFrameCount == 143) {
                Object_Kill(&gPlayerShots[0].obj, gPlayerShots[0].sfxSource);
                func_effect_8007BFFC(gActors[5].obj.pos.x, gActors[5].obj.pos.y, gActors[5].obj.pos.z, 0.0f, 0.0f, 0.0f,
                                     3.0f, 40);
                func_effect_8007D2C8(gActors[5].obj.pos.x, gActors[5].obj.pos.y, gActors[5].obj.pos.z, 6.0f);
                func_effect_8007B344(gActors[5].obj.pos.x, gActors[5].obj.pos.y, gActors[5].obj.pos.z, 5.0f, 5);
                Object_Kill(&gActors[5].obj, gActors[5].sfxSource);
                for (i = 0; i < 20; i++) {
                    func_effect_80079618(gActors[5].obj.pos.x, gActors[5].obj.pos.y, gActors[5].obj.pos.z, 0.5f);
                }
                func_effect_8007A6F0(&gActors[5].obj.pos, NA_SE_EN_EXPLOSION_M);
                player->csState++;
                D_ctx_80177A48[0] = 0.1f;
            }
            break;

        case 2:
            if (gCsFrameCount == 170) {
                player->pos.x = 0.0f;
                player->pos.y = player->cam.eye.y + 50.0f;
                player->csState++;
                player->pos.z = player->cam.eye.z + 20.0f;
                player->unk_194 = 10.0f;
                player->unk_190 = 10.0f;
                player->baseSpeed = 30.0f;
                player->rot.z = -80.0f;
                player->rot.x = -20.0f;
                AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, player->sfxSource, 0);
                for (i = 6; i < 10; i++) {
                    Object_Kill(&gActors[i].obj, gActors[i].sfxSource);
                }
                D_ctx_80177A48[0] = 0.0f;
            }
            break;

        case 3:
            if (gCsFrameCount > 200) {
                gCsCamAtX = player->pos.x;
                gCsCamAtY = player->pos.y;
                gCsCamAtZ = player->pos.z;
                Math_SmoothStepToF(D_ctx_80177A48, 0.1f, 1.0f, 0.01f, 0);
            }

            Math_SmoothStepToF(&player->camRoll, 0.0f, 0.5f, 0.07f, 0);
            Math_SmoothStepToF(&player->rot.z, 0.0f, 0.2f, 2.0f, 0);
            Math_SmoothStepToF(&player->rot.x, 20.0f, 0.1f, 1.0f, 0);

            switch (gCsFrameCount) {
                case 195:
                    if (gTeamShields[TEAM_ID_FALCO] > 0) {
                        SectorX_801938D8(&gActors[0], 0);
                    }
                    break;
                case 213:
                    if (gTeamShields[TEAM_ID_SLIPPY] > 0) {
                        SectorX_801938D8(&gActors[1], 1);
                    }
                    break;
                case 229:
                    if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                        SectorX_801938D8(&gActors[2], 2);
                    }
                    break;
            }

            if (gCsFrameCount > 300) {
                player->csState++;
                player->csTimer = 40;
                D_ctx_80177A48[0] = 0.0f;
                gActors[0].obj.pos.z -= player->pos.z;
                gActors[1].obj.pos.z -= player->pos.z;
                gActors[2].obj.pos.z -= player->pos.z;
                player->cam.eye.z -= player->pos.z;
                gCsCamEyeZ -= player->pos.z;
                player->cam.at.z -= player->pos.z;
                gCsCamAtZ -= player->pos.z;
                player->pos.z = 0.0f;
                player->baseSpeed = 0.0f;
            }
            break;

        case 4:
            Math_SmoothStepToF(&player->camRoll, 0.0f, 0.2f, 0.5f, 0);
            Math_SmoothStepToF(&player->pos.y, 350.0f, 0.1f, 15.0f, 0);
            Math_SmoothStepToF(&player->rot.x, 0.0f, 0.1f, 2.0f, 0);
            gCsCamEyeX = player->pos.x;
            gCsCamEyeY = (player->pos.y * player->unk_148) + 50.0f;
            gCsCamEyeZ = 400.0f;
            gCsCamAtX = player->pos.x;
            gCsCamAtY = (player->pos.y * player->unk_148) + 20.0f;
            gCsCamAtZ = player->trueZpos;
            Math_SmoothStepToF(D_ctx_80177A48, 1.0f, 1.0f, 0.01f, 0);

            if (player->csTimer == 0) {
                player->baseSpeed = gArwingSpeed;
                AUDIO_PLAY_BGM(gBgmSeqId);
                gLevelStartStatusScreenTimer = 80;
                player->state_1C8 = PLAYERSTATE_1C8_ACTIVE;
                player->csState = player->csTimer = player->csEventTimer = 0;
                player->cam.eye.y = player->pos.y * player->unk_148 + 50.0f;
                player->cam.eye.z = 400.0f;
                player->cam.at.y = player->pos.y * player->unk_148 + 20.0f;
                player->cam.at.z = player->trueZpos;
                player->cam.at.x = player->cam.eye.x = player->pos.x;
                gLoadLevelObjects = 1;
                for (i = 0; i < 3; i++) {
                    Object_Kill(&gActors[i].obj, gActors[i].sfxSource);
                }
            }
            break;
    }
    Math_SmoothStepToF(&player->cam.eye.x, gCsCamEyeX, D_ctx_80177A48[0], 20000.0f, 0);
    Math_SmoothStepToF(&player->cam.eye.y, gCsCamEyeY, D_ctx_80177A48[0], 20000.0f, 0);
    Math_SmoothStepToF(&player->cam.eye.z, gCsCamEyeZ, D_ctx_80177A48[0], 20000.0f, 0);
    Math_SmoothStepToF(&player->cam.at.x, gCsCamAtX, D_ctx_80177A48[0], 20000.0f, 0);
    Math_SmoothStepToF(&player->cam.at.y, gCsCamAtY, D_ctx_80177A48[0], 20000.0f, 0);
    Math_SmoothStepToF(&player->cam.at.z, gCsCamAtZ, D_ctx_80177A48[0], 20000.0f, 0);
    Matrix_RotateY(gCalcMatrix, (player->rot.y + 180.0f) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -(player->rot.x * M_DTOR), MTXF_APPLY);
    src.x = 0.0f;
    src.y = 0.0f;
    src.z = player->baseSpeed;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);
    player->vel.x = dest.x;
    player->vel.z = dest.z;
    player->vel.y = dest.y;
    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;
    player->pos.z += player->vel.z;
    player->trueZpos = player->pos.z + player->camDist;
}

void SectorX_801944D4(Actor* actor, s32 arg1) {
    Vec3f srcA;
    Vec3f destA;
    Vec3f srcB;
    Vec3f destB;
    Player* player = &gPlayer[0];

    Matrix_RotateY(gCalcMatrix, player->rot.y * M_DTOR, MTXF_NEW);
    srcA.x = D_i2_80195710[arg1];
    srcA.y = D_i2_80195720[arg1];
    srcA.z = D_i2_80195730[arg1];
    srcB.x = D_i2_80195740[arg1];
    srcB.y = D_i2_80195750[arg1];
    srcB.z = D_i2_80195760[arg1];
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &srcA, &destA);
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &srcB, &destB);

    Actor_Initialize(actor);
    actor->obj.pos.x = player->pos.x + destA.x;
    actor->obj.pos.y = player->pos.y + destA.y;
    actor->obj.pos.z = player->trueZpos + destA.z;
    actor->fwork[0] = destB.x;
    actor->fwork[1] = destB.y;
    actor->fwork[2] = destB.z;
    actor->fwork[7] = RAND_FLOAT(360.0f);
    actor->fwork[8] = RAND_FLOAT(360.0f);
    actor->vel.x = player->vel.x;
    actor->vel.y = player->vel.y;
    actor->vel.z = player->vel.z;
    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_CUTSCENE;
    Object_SetInfo(&actor->info, actor->obj.id);
    if (arg1 == 3) {
        actor->animFrame = 1;
        actor->state = 20;
        actor->obj.rot.x = -player->rot.x - 10.0f;
        actor->obj.rot.y = (player->rot.y + 180.0f) - 10.0f;
        actor->fwork[9] = 10.0f;
    } else {
        actor->obj.rot.z = D_i2_80195770[arg1];
        actor->iwork[11] = 1;
        actor->iwork[14] = D_i2_8019577C[arg1];
        AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, actor->sfxSource, 4);
    }
}

void SectorX_LevelComplete(Player* player) {
    Vec3f sp54;
    Vec3f sp48;
    s32 pad[5];

    Math_SmoothStepToF(&player->zRotBarrelRoll, 0.0f, 0.1f, 15.0f, 0.0f);
    Math_SmoothStepToF(&player->zRotBank, 0.0f, 0.1f, 15.0f, 0.0f);
    Math_SmoothStepToF(&player->rot.x, 0.0f, 0.1f, 3.0f, 0.0f);
    Math_SmoothStepToF(&player->rot.y, 0.0f, 0.1f, 3.0f, 0.0f);
    Math_SmoothStepToF(&player->rot.z, 0.0f, 0.1f, 3.0f, 0.0f);
    Math_SmoothStepToF(&player->camDist, 0.0f, 0.1f, 3.0f, 0.0f);
    Math_SmoothStepToF(&player->camRoll, 0.0f, 0.1f, 3.0f, 0.0f);
    Math_SmoothStepToAngle(&player->aerobaticPitch, 0.0f, 0.1f, 20.0f, 0.0f);
    Math_SmoothStepToF(&player->boostSpeed, 0.0f, 0.1f, 3.0f, 0.0f);

    gStarfieldScrollY += 0.2f;
    gStarfieldScrollX -= 0.2f;

    switch (player->csState) {
        case 0:
            Audio_StopSfxByBankAndSource(1, player->sfxSource);
            player->csState++;
            D_ctx_80177A48[1] = 0.05f;
            D_ctx_80177A48[0] = 0.02f;
            D_ctx_80177A48[2] = 0.0f;
            D_ctx_80177A48[3] = D_ctx_80177A48[2];
            gCsFrameCount = 0;
            D_ctx_80177A48[2] = 100.0f;
            D_ctx_80177A48[4] = 100.0f;
            D_ctx_80177A48[5] = 0.0f;
            player->wings.modelId = 1;
            Play_ClearObjectData();

        case 1:
            if (gCsFrameCount > 990) {
                Math_SmoothStepToF(D_ctx_80177A48 + 3, 0.0f, 0.1f, 0.01f, 0.0f);
            } else if (gCsFrameCount > 120) {
                Math_SmoothStepToF(D_ctx_80177A48 + 3, -0.5f, 0.1f, 0.02f, 0.0f);
                Math_SmoothStepToF(D_ctx_80177A48 + 4, 300.0f, 0.1f, 2.0f, 0.0f);
                Math_SmoothStepToF(D_ctx_80177A48 + 5, -50.0f, 0.1f, 1.0f, 0.0f);
            }
            D_ctx_80177A48[2] += D_ctx_80177A48[3];
            Math_SmoothStepToF(&player->baseSpeed, 0.0f, 0.1f, 2.0f, 0.0f);
            Math_SmoothStepToF(D_ctx_80177A48, 0.1f, 1.0f, 0.002f, 0.0f);
            Math_SmoothStepToF(D_ctx_80177A48 + 1, 0.1f, 1.0f, 0.002f, 0.0f);
            Matrix_RotateY(gCalcMatrix, player->rot.y * M_DTOR, MTXF_NEW);
            Matrix_RotateX(gCalcMatrix, player->rot.x * M_DTOR, MTXF_APPLY);
            Matrix_Push(&gCalcMatrix);
            Matrix_RotateY(gCalcMatrix, D_ctx_80177A48[2] * M_DTOR, MTXF_APPLY);
            sp54.x = 0.0f;
            sp54.y = 30.0f;
            sp54.z = D_ctx_80177A48[4];
            Matrix_MultVec3f(gCalcMatrix, &sp54, &sp48);
            Math_SmoothStepToF(&player->cam.eye.x, player->pos.x + sp48.x, D_ctx_80177A48[0], 500.0f, 0.0f);
            Math_SmoothStepToF(&player->cam.eye.y, player->pos.y + sp48.y, D_ctx_80177A48[0], 500.0f, 0.0f);
            Math_SmoothStepToF(&player->cam.eye.z, player->trueZpos + gPathProgress + sp48.z, D_ctx_80177A48[0], 500.0f,
                               0.0f);
            Matrix_Pop(&gCalcMatrix);
            sp54.x = 0.0f;
            sp54.y = 0;
            sp54.z = D_ctx_80177A48[5];
            Matrix_MultVec3f(gCalcMatrix, &sp54, &sp48);
            Math_SmoothStepToF(&player->cam.at.x, player->pos.x + sp48.x, D_ctx_80177A48[1], 500.0f, 0.0f);
            Math_SmoothStepToF(&player->cam.at.y, player->pos.y + sp48.y, D_ctx_80177A48[1], 500.0f, 0.0f);
            Math_SmoothStepToF(&player->cam.at.z, player->trueZpos + gPathProgress + sp48.z, D_ctx_80177A48[1], 500.0f,
                               0.0f);
            break;

        case 2:
            player->baseSpeed += 2.0f;
            if (player->csTimer == 0) {
                Math_SmoothStepToAngle(&player->rot.x, 20.0f, 0.1f, 0.5f, 0.0f);
            }

            if (gCsFrameCount == 1195) {
                Audio_FadeOutAll(10);
            }

            if (gCsFrameCount > 1195) {
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
                gFillScreenAlphaTarget = 255;
                if (gFillScreenAlpha == 255) {
                    player->state_1C8 = PLAYERSTATE_1C8_NEXT;
                    gFadeoutType = 4;
                    player->csTimer = 0;
                    Play_ClearObjectData();
                    gLeveLClearStatus[LEVEL_SECTOR_X] = Play_CheckMedalStatus(150) + 1;
                }
            }
            break;
    }

    switch (gCsFrameCount) {
        case 706:
            gShowLevelClearStatusScreen = 1;
            break;

        case 906:
            gShowLevelClearStatusScreen = 0;
            break;

        case 100:
            if (gTeamShields[TEAM_ID_FALCO] > 0) {
                SectorX_801944D4(&gActors[1], 0);
            }
            if (gTeamShields[TEAM_ID_SLIPPY] > 0) {
                SectorX_801944D4(&gActors[2], 1);
            }
            if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                SectorX_801944D4(&gActors[3], 2);
            }
            break;

        case 30:
            AUDIO_PLAY_BGM(NA_BGM_COURSE_CLEAR);
            break;

        case 60:
            gLevelClearScreenTimer = 100;
            break;

        case 910:
            gSceneSetup = 1;
            break;

        case 920:
            gActors[1].iwork[14] = gActors[2].iwork[14] = gActors[3].iwork[14] = 0;
            SectorX_801944D4(&gActors[0], 3);
            AUDIO_PLAY_SFX(NA_SE_GREATFOX_ENGINE, gActors[0].sfxSource, 0);
            break;

        case 1050:
            gActors[1].state = 10;
            break;

        case 1090:
            gActors[2].state = 10;
            break;

        case 1120:
            gActors[3].state = 10;
            break;

        case 1160:
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 50);
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 50);
            AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, player->sfxSource, 0);
            player->csState = 2;
            player->csTimer = 40;
            player->unk_194 = 5.0f;
            player->unk_190 = 5.0f;
            break;
    }
    if (gTeamShields[TEAM_ID_SLIPPY] != -2) {
        switch (gCsFrameCount) {
            case 140:
                Radio_PlayMessage(gMsg_ID_20010, RCID_FOX);
                break;

            case 228:
                switch (gTeamShields[TEAM_ID_SLIPPY]) {
                    case -1:
                        Radio_PlayMessage(gMsg_ID_20339, RCID_ROB64);
                        break;

                    case 0:
                        Radio_PlayMessage(gMsg_ID_20345, RCID_ROB64);
                        break;

                    default:
                        func_demo_80048AC0(TEAM_ID_SLIPPY);
                        break;
                }
                break;

            case 375:
                switch (gTeamShields[TEAM_ID_PEPPY]) {
                    case -1:
                        Radio_PlayMessage(gMsg_ID_20338, RCID_ROB64);
                        break;

                    case 0:
                        Radio_PlayMessage(gMsg_ID_20344, RCID_ROB64);
                        break;

                    default:
                        func_demo_80048AC0(TEAM_ID_PEPPY);
                        break;
                }
                break;

            case 521:
                func_demo_80048AC0(TEAM_ID_FALCO);
                switch (gTeamShields[TEAM_ID_FALCO]) {
                    case -1:
                        Radio_PlayMessage(gMsg_ID_20337, RCID_ROB64);
                        break;

                    case 0:
                        Radio_PlayMessage(gMsg_ID_20343, RCID_ROB64);
                        break;

                    default:
                        func_demo_80048AC0(TEAM_ID_FALCO);
                        break;
                }
                break;
        }
    } else {
        switch (gCsFrameCount) {
            case 140:
                Radio_PlayMessage(gMsg_ID_5500, RCID_FOX);
                break;

            case 270:
                Radio_PlayMessage(gMsg_ID_5503, RCID_ROB64);
                break;

            case 423:
                switch (gTeamShields[TEAM_ID_PEPPY]) {
                    case -1:
                        Radio_PlayMessage(gMsg_ID_20338, RCID_ROB64);
                        break;

                    case 0:
                        Radio_PlayMessage(gMsg_ID_20344, RCID_ROB64);
                        break;

                    default:
                        Radio_PlayMessage(gMsg_ID_5501, RCID_PEPPY);
                        break;
                }
                break;

            case 569:
                func_demo_80048AC0(TEAM_ID_FALCO);
                switch (gTeamShields[TEAM_ID_FALCO]) {
                    case -1:
                        Radio_PlayMessage(gMsg_ID_20337, RCID_ROB64);
                        break;

                    case 0:
                        Radio_PlayMessage(gMsg_ID_20343, RCID_ROB64);
                        break;

                    default:
                        Radio_PlayMessage(gMsg_ID_5502, RCID_FALCO);
                        break;
                }
                break;
        }
    }
    Matrix_RotateY(gCalcMatrix, (player->rot.y + 180.0f) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -((player->rot.x + player->aerobaticPitch) * M_DTOR), MTXF_APPLY);
    sp54.x = 0.0f;
    sp54.y = 0.0f;
    sp54.z = player->baseSpeed + player->boostSpeed;
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp54, &sp48);
    player->vel.x = sp48.x;
    player->vel.z = sp48.z;
    player->vel.y = sp48.y;
    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;
    player->pos.z += player->vel.z;
    player->trueZpos = player->pos.z + player->camDist;
    player->bankAngle = player->rot.z + player->zRotBank + player->zRotBarrelRoll;
    player->bobPhase += 10.0f;
    player->yBob = -SIN_DEG(player->bobPhase) * 0.3f;
    player->rockPhase += 8.0f;
    player->rockAngle = SIN_DEG(player->rockPhase);
}
