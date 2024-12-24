// #include "prevent_bss_reordering.h"
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

bool SectorX_SxSpyborg_OverrideLimbDraw(s32, Gfx**, Vec3f*, Vec3f*, void*);
void SectorX_SxSpyborg_PostLimbDraw(s32, Vec3f*, void*);

void SectorX_8018F030(void) {
    s32 i;
    SxSlippy* slippy = &gActors[0];

    for (i = 0; i < ARRAY_COUNT(gActors); i++, slippy++) {
        if (slippy->obj.status == OBJ_FREE) {
            Actor_Initialize(slippy);
            slippy->obj.status = OBJ_INIT;
            slippy->obj.id = OBJ_ACTOR_SX_SLIPPY;
            slippy->animFrame = 1;
            slippy->obj.rot.y = 180.0f;
            slippy->obj.pos.x = gPlayer[0].cam.eye.x - 300.0f;
            slippy->obj.pos.y = gPlayer[0].cam.eye.y + 200.0f;
            slippy->obj.pos.z = gPlayer[0].cam.eye.z - gPathProgress + 300.0f;
            slippy->iwork[11] = 1;
            slippy->aiType = AI360_SLIPPY;
            Object_SetInfo(&slippy->info, slippy->obj.id);
            Radio_PlayMessage(gMsg_ID_5475, RCID_SLIPPY);
            break;
        }
    }
}

void SectorX_SxSlippy_Setup(void) {
    SxSlippy* slippy = &gActors[50];

    Actor_Initialize(slippy);
    slippy->obj.status = OBJ_INIT;
    slippy->obj.id = OBJ_ACTOR_SX_SLIPPY;
    slippy->animFrame = -1;

    slippy->obj.pos.x = gPlayer[0].cam.eye.x + 3000.0f;
    slippy->obj.pos.y = gPlayer[0].cam.eye.y - 3000.0f;
    slippy->obj.pos.z = gPlayer[0].pos.z + 30000.0f;

    Object_SetInfo(&slippy->info, slippy->obj.id);
    slippy->info.cullDistance = 100000.0f;
}

void SectorX_SxSlippy_ShootBoss(SxSlippy* this) {
    Vec3f src;
    Vec3f dest;

    src.x = 0.0f;
    src.y = 0.0f;
    src.z = 100.0f;

    Matrix_RotateY(gCalcMatrix, (this->rot_0F4.y + 180.0f) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, this->rot_0F4.x * M_DTOR, MTXF_APPLY);

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

    Actor_SpawnPlayerLaser(this->index, this->obj.pos.x + (dest.x * 1.5), this->obj.pos.y + (dest.y * 1.5),
                           this->obj.pos.z + (dest.z * 1.5), dest.x, dest.y, dest.z, this->rot_0F4.x,
                           this->rot_0F4.y + 180.0f, 0.0f);
}

void SectorX_SxSlippy_Update(SxSlippy* this) {
    f32 sp34;

    switch (this->animFrame) {
        case 0:
            this->obj.rot.x += 7.0f;
            this->obj.rot.y += 5.0f;
            break;

        case 1:
            this->rot_0F4.z += 3.0f;
            this->obj.rot.z = SIN_DEG(this->rot_0F4.z + 90.0f) * 60.0f;
            sp34 = fabsf(this->obj.pos.z - gBosses[0].obj.pos.z) * 0.1f;
            Math_SmoothStepToF(&this->obj.pos.x, gBosses[0].obj.pos.x + SIN_DEG(this->rot_0F4.z) * sp34, 0.1f, 20.0f,
                               0.0f);
            Math_SmoothStepToF(&this->obj.pos.y, gBosses[0].obj.pos.y, 0.1f, 20.0f, 0.0f);
            Math_SmoothStepToF(&this->obj.pos.z, gBosses[0].obj.pos.z, 1.0f, 55.0f, 0);

            if (gBosses[0].state == 20) {
                this->animFrame = 10;
                break;
            }

            if (((gGameFrameCount % 4) == 0) && (Rand_ZeroOne() < 0.2f)) {
                SectorX_SxSlippy_ShootBoss(this);
            }

            if ((gBosses[0].animFrame == 75) && (gBosses[0].state == 85)) {
                this->animFrame = 2;

                this->vel.x = 10.0f;
                this->vel.y = -10.0f;
                this->vel.z = 30.0f;

                Radio_PlayMessage(gMsg_ID_4111, RCID_SLIPPY);
                Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_EXPLOSION_S);

                gBosses[0].swork[6] = 0;
                gTeamShields[TEAM_ID_SLIPPY] = -2;
                gPlayer[0].state = PLAYERSTATE_STANDBY;

                this->timer_0BC = 200;
                this->iwork[TEAM_FACE] = FACE_SLIPPY;
                this->fwork[0] = 0.0f;
                this->fwork[1] = 0.0f;

                gProjectFar = 30000.0f;

                SectorX_SxSlippy_Setup();
            }
            break;

        case 2:
            if (this->timer_0BC == 100) {
                Radio_PlayMessage(gMsg_ID_20294, RCID_FOX);
            }

            this->obj.rot.x += 5.5f;
            this->obj.rot.y += 5.0f;

            if ((gGameFrameCount % 8) == 0) {
                func_effect_8007D10C(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 1.5f);
            }

            Math_SmoothStepToF(&this->fwork[0], 0.5f, 1.0f, 0.01f, 0);
            Math_SmoothStepToF(&this->fwork[1], 0.1f, 1.0f, 0.01f, 0);

            Math_SmoothStepToF(&gPlayer[0].cam.at.x, this->obj.pos.x, this->fwork[0], 100.0f, 0.0f);
            Math_SmoothStepToF(&gPlayer[0].cam.at.y, this->obj.pos.y, this->fwork[0], 100.0f, 0.0f);
            Math_SmoothStepToF(&gPlayer[0].cam.at.z, this->obj.pos.z + gPathProgress, this->fwork[0], 100.0f, 0.0f);
            Math_SmoothStepToF(&gPlayer[0].cam.eye.x, this->obj.pos.x - 30.0f, this->fwork[1], 20.0f, 0.0f);
            Math_SmoothStepToF(&gPlayer[0].cam.eye.y, this->obj.pos.y, this->fwork[1], 20.0f, 0.0f);

            if (this->timer_0BC == 0) {
                gPlayer[0].state = PLAYERSTATE_ACTIVE;
                if (gPlayer[0].alternateView) {
                    Camera_UpdateCockpitOnRails(&gPlayer[0], 1);
                }
                gProjectFar = 12800.0f;
                Object_Kill(&gActors[50].obj, gActors[50].sfxSource);
            }
            break;

        case 10:
            Math_SmoothStepToF(&this->obj.rot.y, 90.0f, 0.1f, 10.0f, 0.0f);
            Math_SmoothStepToF(&this->obj.rot.z, 90.0f, 1.0f, 10.0f, 0.0f);
            Math_SmoothStepToF(&this->obj.pos.x, gBosses[0].obj.pos.x + 10000.0f, 0.1f, 40.0f, 0.0f);
            Math_SmoothStepToF(&this->obj.pos.y, gBosses[0].obj.pos.y + 5000.0f, 0.1f, 10.0f, 0.0f);
            Math_SmoothStepToF(&this->obj.pos.z, gBosses[0].obj.pos.z, 1.0f, 55.0f, 0.0f);
            break;
    }
}

void SectorX_SxSlippy_Draw(SxSlippy* this) {
    switch (this->animFrame) {
        case 0:
            gSPDisplayList(gMasterDisp++, aSxBaseWallTile1DL);
            break;

        case 1:
        case 2:
        case 10:
            ActorTeamArwing_Draw(this);
            break;

        case -1:
            this->obj.rot.y = RAD_TO_DEG(-gPlayer[gPlayerNum].camYaw);
            this->obj.rot.x = RAD_TO_DEG(gPlayer[gPlayerNum].camPitch);
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
    Actor* slippy;
    f32 yRot;
    f32 xRot;
    f32 pad;
    Vec3f src;
    Vec3f dest;

    for (i = 0; i < ARRAY_COUNT(gActors); i++) {
        slippy = &gActors[i];
        if (slippy->obj.status == OBJ_FREE) {
            Actor_Initialize(slippy);
            slippy->obj.status = OBJ_INIT;
            slippy->obj.id = OBJ_ACTOR_SX_SLIPPY;
            slippy->obj.pos.x = x;
            slippy->obj.pos.y = y;
            slippy->obj.pos.z = z;
            Object_SetInfo(&slippy->info, slippy->obj.id);
            slippy->info.hitbox = (f32*)SEGMENTED_TO_VIRTUAL(aSxBaseWallTile1Hitbox);
            xRot = Math_Atan2F(gPlayer[0].pos.x - x, gPlayer[0].trueZpos - z);
            pad = sqrtf(SQ(gPlayer[0].pos.x - x) + SQ(gPlayer[0].trueZpos - z));
            yRot = -Math_Atan2F(gPlayer[0].pos.y - y, pad);
            Matrix_RotateY(gCalcMatrix, xRot, MTXF_NEW);
            Matrix_RotateX(gCalcMatrix, yRot, MTXF_APPLY);
            src.x = 0.0f;
            src.y = 0.0f;
            src.z = 60.0f;
            Matrix_MultVec3f(gCalcMatrix, &src, &dest);
            slippy->vel.x = dest.x;
            slippy->vel.y = dest.y;
            slippy->vel.z = dest.z - gPathVelZ;
            break;
        }
    }
}

void SectorX_8018FBBC(Vec3f* pos) {
    s32 i;
    Actor* slippy;
    f32 xRot;
    f32 yRot;
    Vec3f src;
    Vec3f dest;

    for (i = 0; i < ARRAY_COUNT(gActors); i++) {
        slippy = &gActors[i];
        if ((slippy->obj.status >= OBJ_ACTIVE) && (fabsf(pos->x - slippy->obj.pos.x) < 2500.0f) &&
            (fabsf(pos->z - slippy->obj.pos.z) < 2500.0f) && (slippy->state != 1000) && (slippy->timer_0C2 == 0) &&
            (slippy->scale < 0.0f) &&
            Object_CheckHitboxCollision(pos, slippy->info.hitbox, &slippy->obj, slippy->vwork[29].x,
                                        slippy->vwork[29].y, slippy->vwork[29].z + slippy->rot_0F4.z)) {
            Play_PlaySfxFirstPlayer(slippy->sfxSource, NA_SE_SLIPPY_HIT);
            slippy->state = 1000;
            xRot = Math_Atan2F(slippy->obj.pos.x - pos->x, slippy->obj.pos.z - pos->z);
            yRot = -Math_Atan2F(slippy->obj.pos.y - pos->y,
                                sqrtf(SQ(slippy->obj.pos.x - pos->x) + SQ(slippy->obj.pos.z - pos->z)));
            Matrix_RotateY(gCalcMatrix, xRot, MTXF_NEW);
            Matrix_RotateX(gCalcMatrix, yRot, MTXF_APPLY);
            src.x = 0.0f;
            src.y = 0.0f;
            src.z = 20.0f;
            Matrix_MultVec3f(gCalcMatrix, &src, &dest);
            slippy->vel.x = dest.x;
            slippy->vel.z = 10.0f;
            slippy->vel.y = dest.y;
            slippy->fwork[15] = slippy->vel.x * 0.2f;
            slippy->fwork[16] = slippy->vel.y * -0.2f;
            slippy->timer_0C6 = 10;
        }
    }
}

void SectorX_SxSpyborgLeftArm_Update(SxSpyborgLeftArm* this) {
    Vec3f sp2C;
    Vec3f sp20;

    if (this->state == 0) {
        Animation_GetFrameData(&D_SX_60206DC, this->animFrame, this->vwork);
        Math_Vec3fFromAngles(&sp20, this->obj.rot.x, this->obj.rot.y, 20.0f);
        this->vel.x = sp20.x;
        this->vel.y = sp20.y;
        this->vel.z = sp20.z;
        this->state++;
    } else {
        if (this->obj.id == OBJ_BOSS_SX_SPYBORG_LEFT_ARM) {
            sp2C.x = this->fwork[11];
            sp2C.y = this->fwork[12];
            sp2C.z = this->fwork[13];
        } else {
            sp2C.x = this->fwork[8];
            sp2C.y = this->fwork[9];
            sp2C.z = this->fwork[10];
        }
        SectorX_8018FBBC(&sp2C);
    }

    if (this->dmgType == DMG_BEAM) {
        this->dmgType = DMG_NONE;
        Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_REFLECT);
    }
}

void SectorX_SxSpyborgRightArm_Update(SxSpyborgRightArm* this) {
    SectorX_SxSpyborgLeftArm_Update(this);
}

bool SectorX_8018FF40(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* data) {
    if (((limbIndex >= 12) && (limbIndex < 22)) || ((limbIndex >= 36) && (limbIndex < 40))) {
        return 0;
    }
    *dList = NULL;
    return 0;
}

void SectorX_SxSpyborgLeftArm_Draw(SxSpyborgLeftArm* this) {
    Animation_DrawSkeleton(3, aSxSpyborgSkel, this->vwork, SectorX_8018FF40, SectorX_SxSpyborg_PostLimbDraw, this,
                           gCalcMatrix);
}

bool SectorX_8018FFDC(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* data) {
    if (((limbIndex >= 2) && (limbIndex < 12)) || ((limbIndex >= 32) && (limbIndex < 36))) {
        return 0;
    }
    *dList = NULL;
    return 0;
}

void SectorX_SxSpyborgRightArm_Draw(SxSpyborgRightArm* this) {
    Animation_DrawSkeleton(3, aSxSpyborgSkel, this->vwork, SectorX_8018FFDC, SectorX_SxSpyborg_PostLimbDraw, this,
                           gCalcMatrix);
}

void SectorX_SxSpyborg_Update(SxSpyborg* this) {
    u8 attack;
    s32 i;
    Vec3f frameTable[50];
    Vec3f sfxPos;
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
            gShowBossHealth = true;
            break;

        case 540:
            Radio_PlayMessage(gMsg_ID_5493, RCID_BOSS_SECTORX);
            break;
    }

    if (gBossFrameCount > 556) {
        // approximately 700 / 256
        gBossHealthBar = (this->swork[3] + this->health) / 2.73f;
    }

    sp68 = gPlayer[0].pos.x - this->obj.pos.x;
    sp64 = gPlayer[0].trueZpos - (this->obj.pos.z + (-237.0f));

    if (this->swork[7] != 0) {
        sp70 = Math_RadToDeg(Math_Atan2F(sp68, sp64));
        sp6C = Math_RadToDeg(-Math_Atan2F(gPlayer[0].pos.y - (this->obj.pos.y + 334.0f), sqrtf(SQ(sp68) + SQ(sp64))));
        Math_SmoothStepToAngle(&this->fwork[4], sp70, 0.1f, 5.0f, 0.00001f);
        Math_SmoothStepToAngle(&this->fwork[6], sp6C, 0.1f, 5.0f, 0.00001f);
    } else {
        Math_SmoothStepToF(&this->fwork[4], 182.0f, 0.1f, 2.0f, 0.00001f);
        Math_SmoothStepToAngle(&this->fwork[6], 0.0f, 0.1f, 1.0f, 0.00001f);
    }

    this->fwork[5] = SIN_DEG(this->timer_054 * 50.0f) * this->timer_054;
    this->fwork[7] = SIN_DEG(this->timer_054 * 30.0f) * this->timer_054 * 0.5f;

    Math_SmoothStepToF(&this->obj.pos.z, gPlayer[0].pos.z + this->fwork[1], 0.1f, this->fwork[42], 0);
    Math_SmoothStepToF(&this->obj.pos.y, this->fwork[2], 0.05f, this->fwork[43], 0);
    Math_SmoothStepToF(&this->obj.pos.x, this->fwork[3], 0.05f, this->fwork[44], 0);
    Math_SmoothStepToAngle(&this->obj.rot.z, this->fwork[41], 0.05f, 2.0f, 0);

    if (this->state != 5) {
        Math_SmoothStepToF(&this->fwork[29], 0.f, 0.1f, 50.0f, 0);
        Math_SmoothStepToF(&this->fwork[30], 0.f, 0.1f, 50.0f, 0);
        Math_SmoothStepToF(&this->fwork[31], 0.f, 0.1f, 50.0f, 0);
        Math_SmoothStepToF(&this->fwork[32], 0.f, 0.1f, 50.0f, 0);
        Math_SmoothStepToF(&this->fwork[33], 0.f, 0.1f, 50.0f, 0);
        Math_SmoothStepToF(&this->fwork[34], 0.f, 0.1f, 50.0f, 0);
        if (this->state != 4) {
            Math_SmoothStepToF(&this->fwork[27], 0.0f, 0.1f, 2.0f, 0);
            Math_SmoothStepToF(&this->fwork[28], 0.0f, 0.1f, 2.0f, 0);
        }
    }

    if (this->dmgType != DMG_NONE) {
        this->dmgType = DMG_NONE;
        if (this->swork[0] == 1) {
            if ((this->dmgPart == 0) && ((this->fwork[4] < 45.0f) || (this->fwork[4] > 315.0f))) {
                AUDIO_PLAY_SFX(NA_SE_EN_DAMAGE_S, this->sfxSource, 4);
                this->swork[3] -= this->damage;
                this->timer_054 = 20;
                Effect_Effect390_Spawn(this->obj.pos.x, this->obj.pos.y + 334.0f, -237.0f + this->obj.pos.z,
                                       this->vel.x, this->vel.y, this->vel.z, 0.2f, 20);

                if (this->swork[3] <= 0) {
                    Effect386_Spawn1(this->obj.pos.x, this->obj.pos.y + 300.0f, this->obj.pos.z, 0.0f, 0.0f, 0.0f,
                                     10.0f, 50);

                    Effect_Effect390_Spawn(this->obj.pos.x, this->obj.pos.y + 334.0f, -237.0f + this->obj.pos.z,
                                           this->vel.x, this->vel.y, this->vel.z, 0.15f, 70);
                    for (i = 0; i < 10; i++) {
                        Play_SpawnDebris(4, this->obj.pos.x, this->obj.pos.y + 334.0f, -237.0f + this->obj.pos.z);
                    }

                    Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_EXPLOSION_L);
                    this->state = 7;
                    this->timer_050 = 80;
                    this->swork[0] = 0;
                    this->timer_05C = 80;
                    this->swork[1] = 0;
                    this->fwork[0] = 0.0f;
                    this->animFrame = 0;
                    this->swork[4] = 1;
                    this->health = 1;
                    this->swork[7] = 1;
                    Audio_KillSfxBySourceAndId(D_i2_80195D88, NA_SE_EN_SZMIS_ENGINE);
                    Audio_KillSfxBySourceAndId(D_i2_80195D98, NA_SE_EN_SZMIS_ENGINE);
                    this->info.hitbox = SEGMENTED_TO_VIRTUAL(D_SX_603265C);
                    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 1);
                    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 1);
                    this->timer_052 = 40;
                    gScreenFlashTimer = 5;
                }
            } else {
                Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_REFLECT);
            }
        } else {
            Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_REFLECT);
        }

        if (this->swork[0] == 2) {
            if (this->dmgPart == 0) {
                this->health -= this->damage;

                AUDIO_PLAY_SFX(NA_SE_EN_DAMAGE_S, this->sfxSource, 4);

                if (this->health <= 0) {
                    gTeamLowHealthMsgTimer = -1;
                    this->obj.rot.y = Math_ModF(this->obj.rot.y, 360.0f);
                    this->state = 20;
                    this->timer_050 = 300;
                    this->fwork[0] = 0.0f;
                    this->animFrame = 0;

                    Radio_PlayMessage(gMsg_ID_5499, RCID_BOSS_SECTORX);

                    Effect386_Spawn1(this->obj.pos.x, this->obj.pos.y + 300.0f, this->obj.pos.z, 0.0f, 0.0f, 0.0f,
                                     10.0f, 50);

                    Effect_Effect390_Spawn(this->obj.pos.x, this->obj.pos.y + 334.0f, -237.0f + this->obj.pos.z,
                                           this->vel.x, this->vel.y, this->vel.z, 0.15f, 70);

                    for (i = 0; i < 10; i++) {
                        Play_SpawnDebris(4, this->obj.pos.x, this->obj.pos.y + 334.0f, -237.0f + this->obj.pos.z);
                    }

                    this->swork[4] = 2;

                    AUDIO_PLAY_SFX(NA_SE_EN_DOWN_IMPACT, this->sfxSource, 4);

                    gScreenFlashTimer = 8;
                    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 1);
                    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 1);
                    Boss_AwardBonus(this);
                    this->info.hitbox = gNoHitbox;
                }

                this->timer_054 = 20;
                this->timer_05C = this->timer_054;
                Effect_Effect390_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, this->vel.x, this->vel.y,
                                       this->vel.z, 0.2f, 10);
            } else {
                Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_REFLECT);
            }
        }
    }

    if (((this->state != 8) && (this->state != 20)) && (gPlayer[0].state != PLAYERSTATE_ACTIVE)) {
        this->state = 8;
        this->fwork[0] = 0.0f;
        Audio_KillSfxBySourceAndId(D_i2_80195D88, NA_SE_EN_SZMIS_ENGINE);
        Audio_KillSfxBySourceAndId(D_i2_80195D98, NA_SE_EN_SZMIS_ENGINE);
    }

    this->vel.z = -20.0f;

    switch (this->state) {
        case 0:
            this->swork[7] = 1;
            this->obj.pos.x = gPlayer[0].xPath;
            this->swork[0] = 0;
            Animation_GetFrameData(&D_SX_60206DC, this->animFrame, this->vwork);
            this->fwork[1] = -2000.0f;
            this->fwork[14] = 300.0f;
            this->fwork[17] = -300.0f;
            this->fwork[16] = 3500.0f;
            this->fwork[19] = 3000.0f;
            this->state = 90;
            this->timer_050 = 450;
            this->swork[3] = 400;
            this->health = 300;
            this->info.hitbox = SEGMENTED_TO_VIRTUAL(aSxSpyborgHitbox);
            gBossActive = true;
            AUDIO_PLAY_BGM(gBossBgms[gCurrentLevel]);
            this->swork[6] = 1;
            this->fwork[44] = 5.0f;
            this->fwork[43] = 5.0f;
            this->fwork[42] = 30.0f;
            break;

        case 90:
            if ((this->timer_050 == 110) || (this->timer_050 == 66)) {
                AUDIO_PLAY_SFX(NA_SE_EN_COMBINE, this->sfxSource, 4);
            }

            if (fabsf(Math_SmoothStepToF(&this->fwork[16], 0.0f, 0.1f, 10.0f, 0)) < 8.0f) {
                Math_SmoothStepToF(&this->fwork[14], 0.0f, 0.2f, 10.0f, 0);
                if ((this->timer_050 % 8) == 0) {
                    Effect_Effect390_Spawn(this->obj.pos.x + 312.0f, this->obj.pos.y, this->obj.pos.z - 173.0f,
                                           this->vel.x, this->vel.y, this->vel.z, 0.2f, 8);
                }
            }

            if (fabsf(Math_SmoothStepToF(&this->fwork[19], 0.0f, 0.1f, 10.0f, 0)) < 8.0f) {
                Math_SmoothStepToF(&this->fwork[17], 0.0f, 0.2f, 10.0f, 0);
                if ((this->timer_050 % 8) == 0) {
                    Effect_Effect390_Spawn(this->obj.pos.x - 312.0f, this->obj.pos.y, this->obj.pos.z - 173.0f,
                                           this->vel.x, this->vel.y, this->vel.z, 0.2f, 8);
                }
            }

            if (this->timer_050 == 0) {
                this->state = 100;
                this->fwork[0] = 0.0f;
                AUDIO_PLAY_SFX(NA_SE_EN_MOTOR_ROLL, this->sfxSource, 4);
            }
            this->fwork[43] = this->fwork[44] = 5.0f;
            this->fwork[42] = 30.0f;
            break;

        case 100:
            this->fwork[1] = -2000.0f;

            frameData = Animation_GetFrameData(&D_SX_60206DC, this->animFrame, frameTable);
            Math_SmoothStepToVec3fArray(frameTable, this->vwork, 1, frameData, this->fwork[0], 100.0f, 0.0f);

            Math_SmoothStepToF(&this->fwork[0], 1.0f, 1.0f, 0.05f, 0);
            this->animFrame++;

            if (this->animFrame >= Animation_GetFrameCount(&D_SX_60206DC)) {
                this->animFrame = 0;
                this->state = 1;
                this->fwork[0] = 0.0f;
                AUDIO_PLAY_SFX(NA_SE_EN_UNIT_COMBINE, this->sfxSource, 4);
            }

            this->fwork[43] = this->fwork[44] = 5.0f;
            this->fwork[42] = 30.0f;
            break;

        case 1: // Taunt
            this->fwork[1] = -1800.0f;
            this->fwork[3] = gPlayer[0].pos.x;
            this->fwork[2] = gPlayer[0].pos.y;
            this->fwork[42] = 30.0f;
            this->fwork[44] = 5.0f;
            this->fwork[43] = 5.0f;

            frameData = Animation_GetFrameData(&D_SX_6016E28, this->animFrame, frameTable);
            Math_SmoothStepToVec3fArray(frameTable, this->vwork, 1, frameData, this->fwork[0], 100.0f, 0.0f);

            Math_SmoothStepToF(&this->fwork[0], 1.0f, 1.0f, 0.05f, 0);

            this->animFrame++;
            if (this->animFrame >= Animation_GetFrameCount(&D_SX_6016E28)) {
                this->animFrame = 0;
                this->state = 2;
                this->fwork[0] = 0.0f;
                this->swork[1] = 1;
                this->swork[0] = 1;
                Radio_PlayMessage(gMsg_ID_5494, RCID_BOSS_SECTORX);
            }
            break;

        case 2: // right arm attack
            attack = true;
            this->fwork[3] = gPlayer[0].pos.x;
            this->fwork[2] = gPlayer[0].pos.y;

            if (this->animFrame > 60) {
                this->fwork[1] = -1000.0f;
                Math_SmoothStepToF(&this->fwork[42], 100.0f, 1.0f, 20.0f, 0);
                this->fwork[43] = this->fwork[44] = 10.0f;
            } else {
                this->fwork[1] = -2000.0f;
                Math_SmoothStepToF(&this->fwork[42], 30.0f, 1.0f, 3.0f, 0);
                this->fwork[43] = this->fwork[44] = 10.0f;
            }

            if (this->animFrame == 60) {
                AUDIO_PLAY_SFX(NA_SE_EN_THROW, this->sfxSource, 4);
                this->fwork[42] = 0.0f;
            }

            frameData = Animation_GetFrameData(&D_SX_60123BC, this->animFrame, frameTable);
            Math_SmoothStepToVec3fArray(frameTable, this->vwork, 1, frameData, this->fwork[0], 100.0f, 0.0f);

            Math_SmoothStepToF(&this->fwork[0], 1.0f, 1.0f, 0.05f, 0);

            this->animFrame++;
            if (this->animFrame >= Animation_GetFrameCount(&D_SX_60123BC)) {
                this->animFrame = 0;
                this->state = 3;
                this->fwork[42] = this->fwork[43] = this->fwork[44] = this->fwork[0] = 0.0f;
                this->swork[7] = 0;
            }
            break;

        case 3: // left arm attack
            attack = true;
            this->fwork[3] = gPlayer[0].pos.x;
            this->fwork[2] = gPlayer[0].pos.y;

            if (this->animFrame > 60) {
                this->fwork[1] = -1000.0f;
                Math_SmoothStepToF(&this->fwork[42], 100.0f, 1.0f, 20.0f, 0);
                this->fwork[44] = 10.0f;
                this->fwork[43] = 10.0f;
            } else {
                this->fwork[1] = -2500.0f;
                Math_SmoothStepToF(&this->fwork[42], 30.0f, 1.0f, 3.0f, 0);
                this->fwork[44] = 10.0f;
                this->fwork[43] = 10.0f;
            }

            if (this->animFrame == 60) {
                AUDIO_PLAY_SFX(NA_SE_EN_THROW, this->sfxSource, 4);
                this->fwork[42] = 0.0f;
            }

            frameData = Animation_GetFrameData(&D_SX_6013798, this->animFrame, frameTable);
            Math_SmoothStepToVec3fArray(frameTable, this->vwork, 1, frameData, this->fwork[0], 100.0f, 0.0f);

            Math_SmoothStepToF(&this->fwork[0], 1.0f, 1.0f, 0.05f, 0);

            this->animFrame++;
            if (this->animFrame >= Animation_GetFrameCount(&D_SX_6013798)) {
                this->animFrame = 0;
                this->fwork[0] = 0.0f;
                if (this->swork[3] <= 250) {
                    this->state = 4;
                    this->timer_050 = 100;
                    Radio_PlayMessage(gMsg_ID_5495, RCID_BOSS_SECTORX);
                    this->fwork[44] = 0.0f;
                    this->fwork[43] = 0.0f;
                    this->fwork[42] = 0.0f;
                } else {
                    this->state = 1;
                    this->swork[1] = 1;
                    this->swork[7] = 1;
                }
            }
            break;

        case 4: // Arms launch setup
            this->swork[7] = 0;
            this->fwork[1] = -3000.0f;
            this->fwork[3] = gPlayer[0].pos.x;
            this->fwork[2] = gPlayer[0].pos.y;

            Math_SmoothStepToF(&this->fwork[44], 10.0f, 1.0f, 1.0f, 0);
            Math_SmoothStepToF(&this->fwork[43], 10.0f, 1.0f, 1.0f, 0);
            Math_SmoothStepToF(&this->fwork[42], 50.0f, 1.0f, 3.0f, 0);

            frameData = Animation_GetFrameData(&D_SX_6016E28, 0, frameTable);
            Math_SmoothStepToVec3fArray(frameTable, this->vwork, 1, frameData, this->fwork[0], 100.0f, 0.0f);

            Math_SmoothStepToF(&this->fwork[0], 1.0f, 1.0f, 0.05f, 0);
            Math_SmoothStepToF(&this->fwork[27], 30.0f, 0.05f, 1.0f, 0);
            Math_SmoothStepToF(&this->fwork[28], -30.0f, 0.05f, 1.0f, 0);

            if (this->timer_050 == 0) {
                this->state = 5;
                this->timer_050 = 100;
                Radio_PlayMessage(gMsg_ID_5496, RCID_FOX);
            }
            break;

        case 5: // arms lauching attack
            sfxPos.x = this->fwork[8] + this->obj.pos.x;
            sfxPos.y = this->fwork[9] + this->obj.pos.y;
            sfxPos.z = this->fwork[10] + this->obj.pos.z;

            Object_SetSfxSourceToPos(D_i2_80195D88, &sfxPos);
            AUDIO_PLAY_SFX(NA_SE_EN_SZMIS_ENGINE, D_i2_80195D88, 4);

            sfxPos.x = this->fwork[11] + this->obj.pos.x;
            sfxPos.y = this->fwork[12] + this->obj.pos.y;
            sfxPos.z = this->fwork[13] + this->obj.pos.z;

            Object_SetSfxSourceToPos(D_i2_80195D98, &sfxPos);
            AUDIO_PLAY_SFX(NA_SE_EN_SZMIS_ENGINE, D_i2_80195D98, 4);

            Math_SmoothStepToF(&this->fwork[27], 30.0f, 0.05f, 1.0f, 0);
            Math_SmoothStepToF(&this->fwork[28], -30.0f, 0.05f, 1.0f, 0);

            sp60 = fabsf(this->obj.pos.x + this->fwork[8] - gPlayer[0].pos.x) * 0.1f;

            if (sp60 > 5.0f) {
                sp60 = 5.0f;
            }

            if ((this->obj.pos.x + this->fwork[8]) < gPlayer[0].pos.x) {
                this->fwork[29] += sp60;
            }

            if (gPlayer[0].pos.x < (this->obj.pos.x + this->fwork[8])) {
                this->fwork[29] -= sp60;
            }

            sp60 = fabsf((this->obj.pos.y + this->fwork[9]) - gPlayer[0].pos.y) * 0.1f;

            if (sp60 > 5.0f) {
                sp60 = 5.0f;
            }

            if ((this->obj.pos.y + this->fwork[9]) < gPlayer[0].pos.y) {
                this->fwork[30] += sp60;
            }

            if (gPlayer[0].pos.y < (this->obj.pos.y + this->fwork[9])) {
                this->fwork[30] -= sp60;
            }

            sp60 = fabsf((this->obj.pos.x + this->fwork[11]) - gPlayer[0].pos.x) * 0.1f;

            if (sp60 > 5.0f) {
                sp60 = 5.0f;
            }

            if ((this->obj.pos.x + this->fwork[11]) < gPlayer[0].pos.x) {
                this->fwork[32] += sp60;
            }

            if (gPlayer[0].pos.x < (this->obj.pos.x + this->fwork[11])) {
                this->fwork[32] -= sp60;
            }

            sp60 = fabsf((this->obj.pos.y + this->fwork[12]) - gPlayer[0].pos.y) * 0.1f;

            if (sp60 > 5.0f) {
                sp60 = 5.0f;
            }

            if ((this->obj.pos.y + this->fwork[12]) < gPlayer[0].pos.y) {
                this->fwork[33] += sp60;
            }

            if (gPlayer[0].pos.y < (this->obj.pos.y + this->fwork[12])) {
                this->fwork[33] -= sp60;
            }

            Math_SmoothStepToF(&this->fwork[31], 4000.0f, 1.0f, 80.0f, 0);

            if (this->timer_050 < 70) {
                Math_SmoothStepToF(&this->fwork[34], 4000.0f, 1.0f, 80.0f, 0);
            }

            if (this->timer_050 == 0) {
                this->state = 6;
                this->timer_050 = 122;
            }
            break;

        case 6: // Arms come back to robot
            if ((this->timer_050 == 20) || (this->timer_050 == 30)) {
                AUDIO_PLAY_SFX(NA_SE_EN_COMBINE, this->sfxSource, 4);
            }

            if (this->timer_050 == 0) {
                this->animFrame = 0;
                this->state = 1;
                this->swork[1] = 1;
                Audio_KillSfxBySourceAndId(D_i2_80195D88, NA_SE_EN_SZMIS_ENGINE);
                Audio_KillSfxBySourceAndId(D_i2_80195D98, NA_SE_EN_SZMIS_ENGINE);
                this->fwork[0] = 0.0f;
                this->fwork[44] = 0.0f;
                this->fwork[43] = 0.0f;
                this->fwork[42] = 0.0f;
                this->swork[7] = 1;
            }
            break;

        case 7:
            if (this->timer_052 == 1) {
                Radio_PlayMessage(gMsg_ID_15252, RCID_SLIPPY);
            }
            this->fwork[41] = 20.0;
            this->fwork[2] = -400.0f;
            this->fwork[42] = 30.0f;

            frameData = Animation_GetFrameData(&D_SX_601C690, this->animFrame, frameTable);
            Math_SmoothStepToVec3fArray(frameTable, this->vwork, 1, frameData, this->fwork[0], 100.0f, 0.0f);

            Math_SmoothStepToF(&this->fwork[0], 1.0f, 1.0f, 0.05f, 0);

            this->animFrame++;
            if (this->animFrame >= Animation_GetFrameCount(&D_SX_601C690)) {
                this->state = 75;
                this->fwork[0] = 0.0f;
                this->animFrame = 0;
                this->timer_050 = 120;
            }
            break;

        case 75:
            this->fwork[41] = 20.0f;
            this->fwork[2] = -400.0f;

            frameData = Animation_GetFrameData(&D_SX_600A2D4, 0, frameTable);
            Math_SmoothStepToVec3fArray(frameTable, this->vwork, 1, frameData, this->fwork[0], 2.5f, 0.0f);

            Math_SmoothStepToF(&this->fwork[0], 0.1f, 1.0f, 0.005f, 0);

            if (this->timer_050 == 0) {
                this->state = 8;
                this->fwork[0] = 0.0f;
                this->animFrame = 0;
                this->health = 300;
                Audio_PlaySequenceDistorted(0, gBossBgms[gCurrentLevel], 1121, 25, -1);
                Radio_PlayMessage(gMsg_ID_19205, RCID_FOX);
                this->timer_052 = 100;
            }
            break;

        case 8:
            if (this->timer_052 == 1) {
                Radio_PlayMessage(gMsg_ID_5497, RCID_BOSS_SECTORX);
            }
            this->fwork[41] = 0.0f;
            this->fwork[2] = gPlayer[0].pos.y;
            this->fwork[3] = gPlayer[0].pos.x;
            this->fwork[44] = 5.0f;
            this->fwork[1] = -1800.0f;
            this->fwork[43] = 5.0f;
            this->fwork[42] = 30.0f;

            frameData = Animation_GetFrameData(&D_SX_600F890, this->animFrame, frameTable);
            Math_SmoothStepToVec3fArray(frameTable, this->vwork, 1, frameData, this->fwork[0], 100.0f, 0.0f);

            Math_SmoothStepToF(&this->fwork[0], 1.0f, 1.0f, 0.02f, 0);

            this->animFrame++;
            if (this->animFrame >= Animation_GetFrameCount(&D_SX_600F890)) {
                this->animFrame = 0;
                this->fwork[0] = 0.0f;
                this->state = 9;
                this->swork[0] = 2;
                this->timer_050 = 30;
            }
            break;

        case 85:
            this->fwork[1] = -3000.0f;
            this->fwork[2] = gPlayer[0].pos.y;
            this->fwork[3] = gPlayer[0].pos.x;

            frameData = Animation_GetFrameData(&D_SX_60123BC, this->animFrame, frameTable);
            Math_SmoothStepToVec3fArray(frameTable, this->vwork, 1, frameData, this->fwork[0], 50.0f, 0.0f);

            Math_SmoothStepToF(&this->fwork[0], 1.0f, 1.0f, 0.01f, 0);

            if (this->timer_050 == 0) {
                this->animFrame++;
                if (this->animFrame >= Animation_GetFrameCount(&D_SX_60123BC)) {
                    this->animFrame = Animation_GetFrameCount(&D_SX_60123BC) - 1;
                    if (gPlayer[0].state != PLAYERSTATE_STANDBY) {
                        this->animFrame = 0;
                        this->state = 10;
                        this->fwork[0] = 0.0f;
                        this->fwork[42] = 0.0f;
                    }
                }
                if (this->animFrame == 60) {
                    AUDIO_PLAY_SFX(NA_SE_EN_THROW, this->sfxSource, 4);
                }
            } else if (this->timer_050 == 1) {
                Radio_PlayMessage(gMsg_ID_20267, RCID_PEPPY);
            }
            break;

        case 9:
            if (this->timer_050 == 1) {
                Radio_PlayMessage(gMsg_ID_5492, RCID_BOSS_SECTORX);
            }
            this->fwork[1] = -2000.0f;
            this->fwork[2] = gPlayer[0].pos.y;
            this->fwork[3] = gPlayer[0].pos.x;

            frameData = Animation_GetFrameData(&D_SX_601AA28, this->animFrame, frameTable);
            Math_SmoothStepToVec3fArray(frameTable, this->vwork, 1, frameData, this->fwork[0], 50.0f, 0.0f);

            Math_SmoothStepToF(&this->fwork[0], 1.0f, 1.0f, 0.01f, 0);
            this->animFrame++;

            if (this->animFrame >= Animation_GetFrameCount(&D_SX_601AA28)) {
                this->animFrame = 0;
                this->state = 10;
                this->fwork[0] = 0.0f;
                this->fwork[42] = 0.0f;
                if (this->swork[10] == 0) {
                    Radio_PlayMessage(gMsg_ID_5474, RCID_FALCO);
                }
                this->swork[10] = 1;
            }

            if (this->animFrame == 70) {
                SectorX_8018FA04(this->fwork[11] + this->obj.pos.x, this->fwork[12] + this->obj.pos.y,
                                 this->fwork[13] + this->obj.pos.z);
                AUDIO_PLAY_SFX(NA_SE_EN_THROW, this->sfxSource, 4);
            }
            break;

        case 10:
            attack = true;
            this->fwork[1] = -1000.0f;
            Math_SmoothStepToF(&this->fwork[42], 50.0f, 1.0f, 3.0f, 0);

            frameData = Animation_GetFrameData(&D_SX_60158C4, this->animFrame, frameTable);
            Math_SmoothStepToVec3fArray(frameTable, this->vwork, 1, frameData, this->fwork[0], 100.0f, 0.0f);

            Math_SmoothStepToF(&this->fwork[0], 1.0f, 1.0f, 0.05f, 0);

            this->animFrame++;
            if ((this->animFrame % 16) == 0) {
                AUDIO_PLAY_SFX(NA_SE_EN_THROW, this->sfxSource, 4);
            }

            if (this->animFrame >= Animation_GetFrameCount(&D_SX_60158C4)) {
                this->animFrame = 0;
                this->fwork[0] = 0.0f;

                if ((gBossFrameCount < 2200) || (gTeamShields[TEAM_ID_SLIPPY] <= 0)) {
                    if (this->health > 150) {
                        this->state = 8;
                    } else {
                        this->state = 35;
                        this->timer_050 = 400;
                        this->fwork[42] = this->fwork[43] = this->fwork[44] = this->rot_078.y = 0.0f;
                        this->swork[9] = RAND_INT(1.9f);
                        Radio_PlayMessage(gMsg_ID_5498, RCID_BOSS_SECTORX);
                    }
                } else {
                    this->state = 85;
                    SectorX_8018F030();
                    this->timer_050 = 100;
                }
            }
            break;

        case 35:
            if (this->swork[9] != 0) {
                this->fwork[2] = 500.0f;
            } else {
                this->fwork[2] = -500.0f;
            }

            if (this->timer_050 > 300) {
                this->fwork[3] = 1000.0f;
                this->fwork[1] = -2000.0f;
            } else if (this->timer_050 > 200) {
                this->fwork[3] = -1000.0f;
                this->fwork[1] = -2500.0f;
                if ((gGameFrameCount % 16) == 0) {
                    AUDIO_PLAY_SFX(NA_SE_EN_THROW, this->sfxSource, 4);
                }
            } else if (this->timer_050 > 100) {
                this->fwork[3] = 0;
                this->fwork[1] = -500.0f;
                if (((gGameFrameCount % 16) == 0)) {
                    AUDIO_PLAY_SFX(NA_SE_EN_THROW, this->sfxSource, 4);
                }
            } else {
                this->fwork[3] = 0;
                this->fwork[1] = -2000.0f;
            }

            Math_SmoothStepToF(&this->fwork[42], 60.0f, 1.0f, 1.0f, 0);
            Math_SmoothStepToF(&this->fwork[44], 20.0f, 1.0f, 0.5f, 0);
            Math_SmoothStepToF(&this->fwork[43], 20.0f, 1.0f, 0.5f, 0);

            frameData = Animation_GetFrameData(&D_SX_6009FF8, 0, frameTable);
            Math_SmoothStepToVec3fArray(frameTable, this->vwork, 1, frameData, this->fwork[0], 5.0f, 0.0f);

            Math_SmoothStepToF(&this->fwork[0], 0.1f, 1.0f, 0.001f, 0);
            Math_SmoothStepToF(&this->rot_078.y, 10.0f, 1.0f, 0.1f, 0);
            Math_SmoothStepToF(&this->obj.rot.y, 2880.0f, 0.1f, this->rot_078.y, 0.1f);

            if ((this->timer_050 == 0) && (this->obj.rot.y == 2880.0f)) {
                this->obj.rot.y = 0.0f;
                this->animFrame = 0;
                this->fwork[0] = 0.0f;
                if ((gBossFrameCount < 2200) || (gTeamShields[TEAM_ID_SLIPPY] <= 0)) {
                    this->state = 9;
                } else {
                    this->state = 85;
                    SectorX_8018F030();
                    this->timer_050 = 100;
                }
            }
            break;

        case 20:
            Math_SmoothStepToF(&this->obj.rot.y, 0.0f, 0.1f, 3.0f, 0.1f);
            this->swork[0] = 0;
            this->fwork[1] = -1800.0f;
            this->fwork[41] = 340.0f;
            this->fwork[2] = -400.0f;

            frameData = Animation_GetFrameData(&D_SX_601C690, this->animFrame, frameTable);
            Math_SmoothStepToVec3fArray(frameTable, this->vwork, 1, frameData, this->fwork[0], 100.0f, 0.0f);

            Math_SmoothStepToF(&this->fwork[0], 1.0f, 1.0f, 0.05f, 0);
            this->animFrame++;

            if (this->animFrame >= Animation_GetFrameCount(&D_SX_601C690)) {
                this->animFrame = Animation_GetFrameCount(&D_SX_601C690);
            }

            if ((this->timer_050 & 3) == 0) {
                func_effect_8007D2C8(RAND_FLOAT_CENTERED(500.0f) + this->obj.pos.x,
                                     RAND_FLOAT_CENTERED(500.0f) + this->obj.pos.y, this->obj.pos.z + 100.0f,
                                     RAND_FLOAT(5.0f) + 5.0f);
            }

            if (((gGameFrameCount % 8) == 0) && (Rand_ZeroOne() < 0.5f)) {
                this->timer_05C = 4;
            }

            if ((this->timer_050 & 3) == 0) {
                Effect_Effect390_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, this->vel.x, this->vel.y,
                                       this->vel.z, 0.3f, 10);
            }

            if (this->timer_050 < 230) {
                Math_SmoothStepToF(&this->fwork[14], 10000.0f, 1.0f, 60.0f, 0);
                Math_SmoothStepToF(&this->fwork[17], -10000.0f, 1.0f, 60.0f, 0);
            }

            if (this->timer_050 == 230) {
                gShowBossHealth = false;
                Effect386_Spawn1(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 0.0f, 0.0f, 0.0f, 30.0f, 40);
                Effect_Effect383_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 40.0f);
            }

            if (this->timer_050 == 210) {
                this->swork[5] = 1;
                this->timer_05A = 1000;
            }

            if (this->timer_050 == 120) {
                if ((gPlayer[0].state != PLAYERSTATE_NEXT) && (gPlayer[0].state != PLAYERSTATE_DOWN)) {
                    gPlayer[0].state = PLAYERSTATE_LEVEL_COMPLETE;
                    gPlayer[0].csState = 0;
                    gPlayer[0].draw = true;
                }
                Object_Kill(&this->obj, this->sfxSource);
                gMissionStatus = this->swork[6];
            }
            break;

        default:
            break;
    }

    D_i2_80195640 = 1;

    Animation_DrawSkeleton(1, aSxSpyborgSkel, this->vwork, SectorX_SxSpyborg_OverrideLimbDraw,
                           SectorX_SxSpyborg_PostLimbDraw, this, &gIdentityMatrix);

    if (((this->swork[1] != 0) && (this->swork[3] > 0)) && ((this->fwork[4] < 45.0f) || (this->fwork[4] > 315.0f))) {
        this->swork[1]++;
        if (this->swork[1] > 40) {
            if (this->swork[1] > 50) {
                this->swork[1] = 0;
            }
            Effect_EnemyLaser(OBJ_EFFECT_377, this->fwork[20] + this->obj.pos.x, this->fwork[21] + this->obj.pos.y,
                              this->fwork[22] + this->obj.pos.z, 100.0f);
            Effect_EnemyLaser(OBJ_EFFECT_377, this->fwork[23] + this->obj.pos.x, this->fwork[24] + this->obj.pos.y,
                              this->fwork[25] + this->obj.pos.z, 100.0f);
        }
    } else {
        this->swork[1] = 0;
    }

    if (this->state != 35) {
        this->info.hitbox = SEGMENTED_TO_VIRTUAL(aSxSpyborgHitbox);
        this->info.hitbox[43] = -211.0f + this->fwork[16];
        this->info.hitbox[45] = -35.0f + this->fwork[15];
        this->info.hitbox[47] = 442.0f + this->fwork[14];
        this->info.hitbox[49] = -211.0f + this->fwork[19];
        this->info.hitbox[51] = -35.0f + this->fwork[18];
        this->info.hitbox[53] = -442.0f + this->fwork[17];
        this->info.hitbox[55] = this->fwork[10];
        this->info.hitbox[57] = this->fwork[9];
        this->info.hitbox[59] = this->fwork[8];
        this->info.hitbox[61] = this->fwork[13];
        this->info.hitbox[63] = this->fwork[12];
        this->info.hitbox[65] = this->fwork[11];

        if (attack) {
            this->info.hitbox[56] = 200.0f;
            this->info.hitbox[58] = 200.0f;
            this->info.hitbox[60] = 100.0f;
            this->info.hitbox[62] = 200.0f;
            this->info.hitbox[64] = 200.0f;
            this->info.hitbox[66] = 100.0f;
        } else {
            this->info.hitbox[56] = 200.0f;
            this->info.hitbox[58] = 100.0f;
            this->info.hitbox[60] = 70.0f;
            this->info.hitbox[62] = 200.0f;
            this->info.hitbox[64] = 100.0f;
            this->info.hitbox[66] = 70.0f;
        }
    } else {
        this->info.hitbox = SEGMENTED_TO_VIRTUAL(D_SX_6032768);
    }

    if (this->swork[0] == 1) {
        Math_SmoothStepToF(&this->fwork[45], 1.0f, 1.0f, 0.05f, 0);
    } else {
        Math_SmoothStepToF(&this->fwork[45], 0.0f, 1.0f, 0.05f, 0);
    }
}

bool SectorX_SxSpyborg_OverrideLimbDraw(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    Vec3f src = { 0.0f, 0.0f, 0.0f };
    Vec3f dest;
    SxSpyborg* boss = (SxSpyborg*) thisx;

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
                Matrix_MultVec3f(gCalcMatrix, &src, &dest);
                Display_SetSecondLight(&dest);
                Matrix_Mult(gGfxMatrix, gCalcMatrix, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, *dList);

                if (boss->swork[4] == 0) {
                    RCP_SetupDL(&gMasterDisp, SETUPDL_41);

                    if ((gGameFrameCount % 2) == 0) {
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

void SectorX_SxSpyborg_PostLimbDraw(s32 limbIndex, Vec3f* rot, void* thisx) {
    Vec3f sp64 = { 87.0f, -323.0f, 200.0f };
    Vec3f sp58 = { 87.0f, -323.0f, -200.0f };
    Vec3f sp4C = { 87.0f, -323.0f, 200.0f };
    Vec3f sp40 = { 87.0f, -323.0f, -200.0f };
    Vec3f src;
    Vec3f dest;
    SxSpyborg* boss = (SxSpyborg*) thisx;

    src.x = 0.0f;
    src.y = 0.0f;
    src.z = 0.0f;

    switch (limbIndex) {
        case 1:
            Matrix_MultVec3f(gCalcMatrix, &sp58, &dest);
            boss->fwork[20] = dest.x;
            boss->fwork[21] = dest.y;
            boss->fwork[22] = dest.z;
            Matrix_MultVec3f(gCalcMatrix, &sp64, &dest);
            boss->fwork[23] = dest.x;
            boss->fwork[24] = dest.y;
            boss->fwork[25] = dest.z;
            Matrix_MultVec3f(gCalcMatrix, &sp40, &boss->vwork[45]);
            Matrix_MultVec3f(gCalcMatrix, &sp4C, &boss->vwork[46]);
            break;

        case 6:
            Matrix_MultVec3f(gCalcMatrix, &src, &dest);
            boss->fwork[8] = dest.x;
            boss->fwork[9] = dest.y;
            boss->fwork[10] = dest.z;
            break;

        case 16:
            Matrix_MultVec3f(gCalcMatrix, &src, &dest);
            boss->fwork[11] = dest.x;
            boss->fwork[12] = dest.y;
            boss->fwork[13] = dest.z;
            break;

        case 33:
            Matrix_MultVec3f(gCalcMatrix, &src, &dest);
            boss->fwork[35] = dest.x;
            boss->fwork[36] = dest.y;
            boss->fwork[37] = dest.z;
            break;

        case 37:
            Matrix_MultVec3f(gCalcMatrix, &src, &dest);
            boss->fwork[38] = dest.x;
            boss->fwork[39] = dest.y;
            boss->fwork[40] = dest.z;

        default:
            break;
    }
}

Vec3f sSxCsCommanderPos[5] = { { 0.0f, 2300.0f, -5000.0f },
                               { -600.0f, 2200.0f, -5000.0f },
                               { -300.0f, 2270.0f, -5000.0f },
                               { 300.0f, 2270.0f, -5000.0f },
                               { 600.0f, 2200.0f, -5000.0f } };

Vec3f sLevelStartTeamSetupPos[3] = {
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
s16 sSxTeamFaces[3] = { FACE_FALCO, FACE_SLIPPY, FACE_PEPPY };

void SectorX_SxSpyborg_Draw(SxSpyborg* this) {
    f32 fwork;

    if (this->swork[5] == 0) {
        D_i2_80195640 = 0;
        Animation_DrawSkeleton(3, aSxSpyborgSkel, this->vwork, SectorX_SxSpyborg_OverrideLimbDraw, 0, this,
                               gCalcMatrix);
        RCP_SetupDL_64();
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 96);

        if (this->fwork[31] > 10.0f) {
            fwork = this->fwork[31] * 0.1f;
            if (fwork > 50.0f) {
                fwork = 50.0f;
            }
            if ((gGameFrameCount % 2) != 0) {
                fwork *= 1.2f;
            }
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, this->fwork[35], this->fwork[36], this->fwork[37], MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, fwork, fwork, fwork, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, aBlueSphereDL);
            Matrix_Pop(&gGfxMatrix);
        }

        if (this->fwork[34] > 10.0f) {
            fwork = this->fwork[34] * 0.1f;
            if (fwork > 50.0f) {
                fwork = 50.0f;
            }
            if ((gGameFrameCount % 2) != 0) {
                fwork *= 1.2f;
            }
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, this->fwork[38], this->fwork[39], this->fwork[40], MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, fwork, fwork, fwork, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, aBlueSphereDL);
            Matrix_Pop(&gGfxMatrix);
        }

        RCP_SetupDL_64();
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 96);

        if (this->swork[1] != 0) {
            fwork = this->swork[1] * 0.1f;

            if (fwork > 4.0f) {
                fwork = 4.0f;
            }
            if ((gGameFrameCount % 2) != 0) {
                fwork *= 1.2f;
            }
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, this->fwork[20], this->fwork[21], this->fwork[22], MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, fwork, fwork, fwork, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_SX_600F8A0);
            Matrix_Pop(&gGfxMatrix);

            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, this->fwork[23], this->fwork[24], this->fwork[25], MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, fwork, fwork, fwork, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_SX_600F8A0);
            Matrix_Pop(&gGfxMatrix);
        }
    }
}

void SectorX_CsCommander_Setup(ActorCutscene* this, s32 index) {
    Actor_Initialize(this);
    this->obj.status = OBJ_ACTIVE;
    this->obj.id = OBJ_ACTOR_CUTSCENE;

    this->obj.pos.x = sSxCsCommanderPos[index].x;
    this->obj.pos.y = sSxCsCommanderPos[index].y;
    this->obj.pos.z = sSxCsCommanderPos[index].z;

    this->vel.z = 30.0f;
    this->vel.y = -16.0f;
    this->animFrame = ACTOR_CS_COMMANDER;
    this->obj.rot.x = 15.0f;

    Object_SetInfo(&this->info, this->obj.id);
    AUDIO_PLAY_SFX(NA_SE_EN_ENGINE_01, this->sfxSource, 4);
}

void SectorX_LevelStart_SetupTeam(ActorCutscene* this, s32 teamIdx) {
    Actor_Initialize(this);
    this->obj.status = OBJ_ACTIVE;
    this->obj.id = OBJ_ACTOR_CUTSCENE;

    this->obj.pos.x = gPlayer[0].cam.eye.x + sLevelStartTeamSetupPos[teamIdx].x;
    this->obj.pos.y = gPlayer[0].cam.eye.y + sLevelStartTeamSetupPos[teamIdx].y;
    this->obj.pos.z = gPlayer[0].cam.eye.z + sLevelStartTeamSetupPos[teamIdx].z;

    this->state = 1;
    this->iwork[11] = 1;
    this->vel.z = -30.0f;
    this->vel.y = 0.0f;
    this->obj.rot.y = 180.0f;
    this->obj.rot.x = 10.0f;

    if (teamIdx == 2) {
        this->obj.rot.z = -20.0f;
    }

    Object_SetInfo(&this->info, this->obj.id);
    AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, this->sfxSource, 4);
    AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, this->sfxSource, 0);
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
                SectorX_CsCommander_Setup(&gActors[5 + i], i);
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
                Effect386_Spawn1(gActors[5].obj.pos.x, gActors[5].obj.pos.y, gActors[5].obj.pos.z, 0.0f, 0.0f, 0.0f,
                                 3.0f, 40);
                func_effect_8007D2C8(gActors[5].obj.pos.x, gActors[5].obj.pos.y, gActors[5].obj.pos.z, 6.0f);
                Effect_Effect384_Spawn(gActors[5].obj.pos.x, gActors[5].obj.pos.y, gActors[5].obj.pos.z, 5.0f, 5);
                Object_Kill(&gActors[5].obj, gActors[5].sfxSource);
                for (i = 0; i < 20; i++) {
                    func_effect_80079618(gActors[5].obj.pos.x, gActors[5].obj.pos.y, gActors[5].obj.pos.z, 0.5f);
                }
                Effect_SpawnTimedSfxAtPos(&gActors[5].obj.pos, NA_SE_EN_EXPLOSION_M);
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
                        SectorX_LevelStart_SetupTeam(&gActors[0], 0);
                    }
                    break;
                case 213:
                    if (gTeamShields[TEAM_ID_SLIPPY] > 0) {
                        SectorX_LevelStart_SetupTeam(&gActors[1], 1);
                    }
                    break;
                case 229:
                    if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                        SectorX_LevelStart_SetupTeam(&gActors[2], 2);
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
                player->state = PLAYERSTATE_ACTIVE;
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

void SectorX_LevelComplete_SetupTeam(ActorCutscene* this, s32 teamIdx) {
    Vec3f srcA;
    Vec3f destA;
    Vec3f srcB;
    Vec3f destB;
    Player* player = &gPlayer[0];

    Matrix_RotateY(gCalcMatrix, player->rot.y * M_DTOR, MTXF_NEW);

    srcA.x = D_i2_80195710[teamIdx];
    srcA.y = D_i2_80195720[teamIdx];
    srcA.z = D_i2_80195730[teamIdx];
    srcB.x = D_i2_80195740[teamIdx];
    srcB.y = D_i2_80195750[teamIdx];
    srcB.z = D_i2_80195760[teamIdx];

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &srcA, &destA);
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &srcB, &destB);

    Actor_Initialize(this);
    this->obj.pos.x = player->pos.x + destA.x;
    this->obj.pos.y = player->pos.y + destA.y;
    this->obj.pos.z = player->trueZpos + destA.z;
    this->fwork[0] = destB.x;
    this->fwork[1] = destB.y;
    this->fwork[2] = destB.z;
    this->fwork[7] = RAND_FLOAT(360.0f);
    this->fwork[8] = RAND_FLOAT(360.0f);
    this->vel.x = player->vel.x;
    this->vel.y = player->vel.y;
    this->vel.z = player->vel.z;
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_ACTOR_CUTSCENE;

    Object_SetInfo(&this->info, this->obj.id);

    if (teamIdx == 3) {
        this->animFrame = ACTOR_CS_GREAT_FOX;
        this->state = 20;
        this->obj.rot.x = -player->rot.x - 10.0f;
        this->obj.rot.y = (player->rot.y + 180.0f) - 10.0f;
        this->fwork[9] = 10.0f;
    } else {
        this->obj.rot.z = D_i2_80195770[teamIdx];
        this->iwork[11] = 1;
        this->iwork[TEAM_FACE] = sSxTeamFaces[teamIdx];
        AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, this->sfxSource, 4);
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
            player->arwing.drawFace = true;
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
                    player->state = PLAYERSTATE_NEXT;
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
            gShowLevelClearStatusScreen = true;
            break;

        case 906:
            gShowLevelClearStatusScreen = false;
            break;

        case 100:
            if (gTeamShields[TEAM_ID_FALCO] > 0) {
                SectorX_LevelComplete_SetupTeam(&gActors[1], 0);
            }
            if (gTeamShields[TEAM_ID_SLIPPY] > 0) {
                SectorX_LevelComplete_SetupTeam(&gActors[2], 1);
            }
            if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                SectorX_LevelComplete_SetupTeam(&gActors[3], 2);
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
            gActors[1].iwork[TEAM_FACE] = gActors[2].iwork[TEAM_FACE] = gActors[3].iwork[TEAM_FACE] = FACE_NONE;
            SectorX_LevelComplete_SetupTeam(&gActors[0], 3);
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
