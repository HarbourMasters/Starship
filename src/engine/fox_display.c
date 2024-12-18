#include "global.h"
#include "mods/hit64.c"
#include "assets/ast_arwing.h"
#include "assets/ast_allies.h"
#include "assets/ast_landmaster.h"
#include "assets/ast_versus.h"
#include "assets/ast_sector_z.h"
#include "port/interpolation/FrameInterpolation.h"

// f32 path1 = 0.0f;
// f32 path2 = 0.0f;

Vec3f D_display_801613B0[4];
Vec3f D_display_801613E0[4];
s16 gReflectY;
Matrix D_display_80161418[4];
Vec3f D_display_80161518[4];
Vec3f D_display_80161548[4];
Vec3f gLockOnTargetViewPos[4];
f32 D_display_801615A8[4];
f32 D_display_801615B8[4];

s32 D_display_800CA220 = 0;
u8 sPlayersVisible[] = { false, false, false, false };
bool sDrawCockpit = false;
s32 D_display_800CA22C = false;
f32 gCamDistortion = 0.0f;
Actor* gTeamHelpActor = NULL;
s32 gTeamHelpTimer = 0;
f32 D_display_800CA23C[3] = { 0.5f, 0.25f, 0.25f };
f32 D_display_800CA248[3] = { 2.0f, 1.0f, 0.5f };

#if DEBUG_BOSS_KILLER == 1
void KillBoss(void);
#endif

void Display_DrawHelpAlert(void) {
    bool centered; // Enemy pos is centered, so both help arrows should be displayed
    f32 sp78;
    f32 sp74;
    Vec3f sp68;
    Vec3f sp5C;

    if ((gPlayState == PLAY_PAUSE) || (gTeamHelpActor == NULL)) {
        return;
    }

    if ((gTeamHelpActor->obj.status != OBJ_ACTIVE) || (gPlayer[0].state_1C8 != PLAYERSTATE_1C8_ACTIVE)) {
        gTeamHelpActor = NULL;
        gTeamHelpTimer = 0;
        return;
    }

    if (gTeamHelpTimer != 0) {
        gTeamHelpTimer--;
        if (gTeamHelpTimer == 0) {
            gTeamHelpActor = NULL;
            return;
        }
    }

    if ((gTeamHelpTimer & 4) == 0) {
        Matrix_RotateY(gCalcMatrix, gPlayer[0].camYaw, MTXF_NEW);
        Matrix_RotateX(gCalcMatrix, gPlayer[0].camPitch, MTXF_APPLY);

        sp68.x = gTeamHelpActor->obj.pos.x - gPlayer[0].cam.eye.x;
        sp68.y = gTeamHelpActor->obj.pos.y - gPlayer[0].cam.eye.y;
        sp68.z = gTeamHelpActor->obj.pos.z + gPathProgress - gPlayer[0].cam.eye.z;

        Matrix_MultVec3f(gCalcMatrix, &sp68, &sp5C);

        centered = false;
        if ((sp5C.z < 0.0f) && (sp5C.z > -12000.0f) && (fabsf(sp5C.x) < fabsf(sp5C.z * 0.4f))) {
            centered = true;
        }

        RCP_SetupDL(&gMasterDisp, SETUPDL_12);

        switch (gTeamHelpActor->aiType) {
            case AI360_PEPPY:
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 30, 0, 255);
                break;
            case AI360_SLIPPY:
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 00, 179, 67, 255);
                break;
            case AI360_FALCO:
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 30, 30, 255, 255);
                break;
        }

        switch (centered) {
            case false:
                if (gTeamHelpActor->sfxSource[0] > 0.0f) {
                    sp78 = 20.0f * OTRGetAspectRatio()-8;
                    sp74 = M_PI / 2;
                } else {
                    sp78 = -20.0f * OTRGetAspectRatio()+8;
                    sp74 = -M_PI / 2;
                }
                Matrix_Push(&gGfxMatrix);

                // @port: Tag the transform.
                FrameInterpolation_RecordOpenChild("Display_DrawHelpAlert", centered);

                Matrix_Translate(gGfxMatrix, sp78, 0.0f, -50.0f, MTXF_APPLY);
                Matrix_RotateZ(gGfxMatrix, sp74, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, 0.03f, 0.03f, 0.03f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_1023700);
                Matrix_Pop(&gGfxMatrix);

                // @port Pop the transform id.
                FrameInterpolation_RecordCloseChild();
                break;

            case true:
                // right arrow (both at the same time)
                Matrix_Push(&gGfxMatrix);

                // @port: Tag the transform.
                FrameInterpolation_RecordOpenChild("Display_DrawHelpAlert", centered);
                Matrix_Translate(gGfxMatrix, 20.0f * OTRGetAspectRatio() - 8, 0.0f, -50.0f, MTXF_APPLY);
                Matrix_RotateZ(gGfxMatrix, -M_PI / 2, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, 0.03f, 0.03f, 0.03f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_1023700);
                Matrix_Pop(&gGfxMatrix);
                sp78 = -20.0f;

                // left arrow (both in simultaneous)
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, -20.0f * OTRGetAspectRatio() + 8, 0.0f, -50.0f, MTXF_APPLY);
                Matrix_RotateZ(gGfxMatrix, M_PI / 2, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, 0.03f, 0.03f, 0.03f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_1023700);
                Matrix_Pop(&gGfxMatrix);

                // @port Pop the transform id.
                FrameInterpolation_RecordCloseChild();
                break;
        }
        
        switch (centered) {
            case false:
                RCP_SetupDL(&gMasterDisp, SETUPDL_76_POINT);
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 0, 255);
                if (sp78 < 0.0f) {
                    Graphics_DisplaySmallText(OTRGetRectDimensionFromLeftEdge(38.0f), 106, 1.0f, 1.0f, "HELP!!");
                } else {
                    Graphics_DisplaySmallText(OTRGetRectDimensionFromRightEdge(248), 106, 1.0f, 1.0f, "HELP!!");
                }
                break;

            case true:
                RCP_SetupDL(&gMasterDisp, SETUPDL_76_POINT);
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 0, 255);
                Graphics_DisplaySmallText(OTRGetRectDimensionFromLeftEdge(38.0f) , 106, 1.0f, 1.0f, "HELP!!");
                Graphics_DisplaySmallText(OTRGetRectDimensionFromRightEdge(248), 106, 1.0f, 1.0f, "HELP!!");
                break;
        }
    }
}

bool Display_OnFootCharacter_OverrideLimbDraw(s32 limbIndex, Gfx** gfxPtr, Vec3f* pos, Vec3f* rot, void* data) {
    Player* player = (Player*) data;

    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);

    if (player->num == 1) {
        if (limbIndex == 16) {
            rot->y += player->unk_154;
            rot->y -= player->unk_180;
        }
        if (limbIndex == 22) {
            rot->y += -player->unk_158 * 0.8f;
            rot->x -= player->unk_15C;
        }
        if (limbIndex == 1) {
            gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
            rot->y += player->unk_164;
        }
        if (limbIndex == 2) {
            gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
            rot->y += player->unk_164;
        }
        if (limbIndex == 3) {
            gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
            rot->y += player->unk_168;
        }
        if (limbIndex == 4) {
            gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
            rot->y += player->unk_168;
        }
    } else {
        if (limbIndex == 11) {
            if (player->num == 0) {
                rot->y += -player->unk_154 * 0.8f;
            }
            if (player->num == 2) {
                rot->y += player->unk_154;
                rot->y -= player->unk_180;
            }
            if (player->num == 3) {
                rot->y += player->unk_154 * 0.8f;
            }
        }
        if (limbIndex == 16) {
            rot->y += -player->unk_158 * 0.8f;
            rot->x -= player->unk_15C;
        }
        if ((limbIndex == 17) && (player->num != 2)) {
            rot->y += player->unk_180;
            rot->x -= player->unk_180;
            rot->y += -player->unk_158 * 0.2f;
            rot->x += -player->unk_15C * 0.2f;
        }
    }
    return false;
}

void Display_OnFootFox_PostLimbDraw(s32 limbIndex, Vec3f* rot, void* data) {
    Vec3f sp1C;
    Player* player = (Player*) data;

    if (limbIndex == 11) {
        sp1C.x = 3.0f;
        sp1C.y = 1.0f;
        sp1C.z = -28.0f;
        Matrix_MultVec3f(gGfxMatrix, &sp1C, &D_display_801613B0[player->num]);
    }
}

void Display_OnFootPeppy_PostLimbDraw(s32 limbIndex, Vec3f* rot, void* data) {
    Vec3f sp1C;
    Player* player = (Player*) data;

    if (limbIndex == 16) {
        sp1C.x = 13.0f;
        sp1C.y = 2.0f;
        sp1C.z = 28.0f;
        Matrix_MultVec3f(gGfxMatrix, &sp1C, &D_display_801613B0[player->num]);
    }
}

void Display_OnFootSlippy_PostLimbDraw(s32 limbIndex, Vec3f* rot, void* data) {
    Vec3f sp1C;
    Player* player = (Player*) data;

    if (limbIndex == 11) {
        sp1C.x = 0.0f;
        sp1C.y = 2.0f;
        sp1C.z = 29.0f;
        Matrix_MultVec3f(gGfxMatrix, &sp1C, &D_display_801613B0[player->num]);
    }
}

void Display_OnFootFalco_PostLimbDraw(s32 limbIndex, Vec3f* rot, void* data) {
    Vec3f sp1C;
    Player* player = (Player*) data;

    if (limbIndex == 11) {
        sp1C.x = 19.0f;
        sp1C.y = 1.0f;
        sp1C.z = 32.0f;
        Matrix_MultVec3f(gGfxMatrix, &sp1C, &D_display_801613B0[player->num]);
    }
}

void Display_OnFootMuzzleFlash(Player* player) {
    Matrix_Push(&gGfxMatrix);

    // @port: Tag the transform.
    FrameInterpolation_RecordOpenChild("Display_OnFootMuzzleFlash", player->num);

    Matrix_Copy(gGfxMatrix, &gIdentityMatrix);
    if ((player->state_1C8 == PLAYERSTATE_1C8_ACTIVE) && (player->csTimer != 0)) {
        Matrix_Translate(gGfxMatrix, D_display_801613B0[player->num].x, D_display_801613B0[player->num].y,
                         D_display_801613B0[player->num].z, MTXF_APPLY);
        Matrix_Scale(gGfxMatrix, D_display_800CA23C[player->csTimer - 1], D_display_800CA23C[player->csTimer - 1],
                     D_display_800CA23C[player->csTimer - 1], MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        RCP_SetupDL_40();
        gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
        gSPDisplayList(gMasterDisp++, D_versus_302D240);
    }
    Matrix_Pop(&gGfxMatrix);

    // @port Pop the transform id.
    FrameInterpolation_RecordCloseChild();
}

void Display_OnFootCharacter(Player* player) {
    Matrix_Push(&gGfxMatrix);
    Matrix_Scale(gCalcMatrix, 0.5f, 0.5f, 0.5f, MTXF_APPLY);
    Matrix_Translate(gCalcMatrix, 0.0f, 35.0f, 0.0f, MTXF_APPLY);
    switch (player->num) {
        case 0:
            Animation_DrawSkeleton(5, aVsOnFootFoxSkel, player->jointTable, Display_OnFootCharacter_OverrideLimbDraw,
                                   Display_OnFootFox_PostLimbDraw, player, gCalcMatrix);
            break;
        case 1:
            Animation_DrawSkeleton(5, aVsOnFootPeppySkel, player->jointTable, Display_OnFootCharacter_OverrideLimbDraw,
                                   Display_OnFootPeppy_PostLimbDraw, player, gCalcMatrix);
            break;
        case 2:
            Animation_DrawSkeleton(5, aVsOnFootSlippySkel, player->jointTable, Display_OnFootCharacter_OverrideLimbDraw,
                                   Display_OnFootSlippy_PostLimbDraw, player, gCalcMatrix);
            break;
        case 3:
            Animation_DrawSkeleton(5, aVsOnFootFalcoSkel, player->jointTable, Display_OnFootCharacter_OverrideLimbDraw,
                                   Display_OnFootFalco_PostLimbDraw, player, gCalcMatrix);
            break;
    }
    Matrix_Pop(&gGfxMatrix);
    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
}

void Display_Landmaster(Player* player) {
    f32 sp64;
    Vec3f sp58;
    Vec3f sp4C = { 0.0f, 0.0f, 90.0f };
    Vec3f sp40 = { 0.0f, 40.0f, -70.0f };

    Matrix_Push(&gGfxMatrix);

    if (!gVersusMode) {
        gSPDisplayList(gMasterDisp++, aLandmasterModelDL);
    } else {
        gSPDisplayList(gMasterDisp++, aVsLandmasterModelDL);
    }

    Matrix_MultVec3f(gGfxMatrix, &sp40, &D_display_80161518[player->num]);
    Matrix_Translate(gGfxMatrix, 0.0f, 51.0f, -10.0f, MTXF_APPLY);
    Matrix_RotateY(gGfxMatrix, -player->unk_180 * M_DTOR, MTXF_APPLY);
    Matrix_RotateX(gGfxMatrix, player->unk_17C * M_DTOR, MTXF_APPLY);
    if (gPlayerNum == player->num) {
        sp64 = 0.0f;
        if (gChargeTimers[player->num] >= 20) {
            sp64 = (s32) (gGameFrameCount % 8U) * 80.0f;
        }
        sp58.x = 0.0f;
        sp58.y = 0.0f;
        sp58.z = 1200.0f;
        Matrix_MultVec3f(gGfxMatrix, &sp58, &D_display_801613E0[0]);
        sp58.z = 2400.0f + sp64;
        Matrix_MultVec3f(gGfxMatrix, &sp58, &D_display_801613E0[1]);
    }

    Matrix_SetGfxMtx(&gMasterDisp);

    if (!gVersusMode) {
        if (player->unk_1A0 != 0) {
            RCP_SetupDL_64();
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 64, 255, 64, 255);
        }
        gSPDisplayList(gMasterDisp++, aLandmasterCanonDL);
    } else {
        gSPDisplayList(gMasterDisp++, aVsLandmasterCanonDL);
    }

    Matrix_MultVec3f(gGfxMatrix, &sp4C, &D_display_80161548[player->num]);
    Matrix_Pop(&gGfxMatrix);
}

Gfx* sFaceDL[] = { aAwFoxHeadDL, aAwFalcoHeadDL, aAwSlippyHeadDL, aAwPeppyHeadDL };
Gfx* sExpertFaceDL[] = { aAwJamesHeadDL, aAwFalcoHeadDL, aAwSlippyHeadDL, aAwPeppyHeadDL };
f32 D_display_800CA28C = 2.0f;
f32 D_display_800CA290 = 13.0f;
f32 D_display_800CA294 = -10.0f;
f32 sReticleScales[] = { 0.0f, 0.0f, 0.0f, 0.0f };
f32 sPlayerShadowing = 0.0f;

void Display_LandmasterMuzzleFlash(Player* player) {
    Matrix_Push(&gGfxMatrix);

    // @port: Tag the transform.
    FrameInterpolation_RecordOpenChild("Display_LandmasterMuzzleFlash", player->num);

    if ((player->state_1C8 == PLAYERSTATE_1C8_ACTIVE) && (player->unk_1A0 != 0)) {
        Matrix_Translate(gGfxMatrix, D_display_80161548[player->num].x, D_display_80161548[player->num].y,
                         D_display_80161548[player->num].z, MTXF_APPLY);
        Matrix_Scale(gGfxMatrix, D_display_800CA248[player->unk_1A0 - 1], D_display_800CA248[player->unk_1A0 - 1],
                     D_display_800CA248[player->unk_1A0 - 1], MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);

        if (gVersusMode) {
            RCP_SetupDL_40();
            gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
            gSPDisplayList(gMasterDisp++, D_versus_301FD20);
        } else {
            Matrix_Scale(gGfxMatrix, 0.5f, 0.5f, 0.5f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            RCP_SetupDL(&gMasterDisp, SETUPDL_67);
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
            gDPSetEnvColor(gMasterDisp++, 0, 255, 0, 255);
            gSPDisplayList(gMasterDisp++, aOrbDL);
        }
    }
    Matrix_Pop(&gGfxMatrix);

    // @port Pop the transform id.
    FrameInterpolation_RecordCloseChild();
}

void Display_LandmasterThrusters(Player* player) {
    f32 sp2C;

    Matrix_Push(&gGfxMatrix);
    Matrix_Copy(gGfxMatrix, &D_display_80161418[player->num]);

    if (gVersusMode) {
        RCP_SetupDL_64();
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 150);
    } else {
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 192);
        gDPSetEnvColor(gMasterDisp++, 255, 0, 0, 192);
        RCP_SetupDL(&gMasterDisp, SETUPDL_67);
    }

    sp2C = player->unk_16C;
    if (sp2C > 0.2f) {
        if (!gVersusMode) {
            sp2C *= 1.1f;
        }

        if ((gGameFrameCount % 2) != 0) {
            sp2C *= 1.1f;
        }

        Matrix_Push(&gGfxMatrix);
        Matrix_Translate(gGfxMatrix, 20.0f, 30.0f, -10.0f, MTXF_APPLY);

        if (!gVersusMode) {
            Matrix_RotateY(gGfxMatrix, -gPlayer[gPlayerNum].camYaw, MTXF_APPLY);
        }

        Matrix_Scale(gGfxMatrix, sp2C, sp2C, sp2C, MTXF_APPLY);
        Matrix_Translate(gGfxMatrix, 0.0f, -30.0f, 0.0f, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);

        if (!gVersusMode) {
            gSPDisplayList(gMasterDisp++, D_landmaster_30066B0);
        } else {
            gSPDisplayList(gMasterDisp++, D_versus_301B6E0);
        }
        Matrix_Pop(&gGfxMatrix);
    }

    sp2C = player->unk_170;
    if (sp2C > 0.2f) {
        if (!gVersusMode) {
            sp2C *= 1.1f;
        }

        if ((gGameFrameCount % 2) != 0) {
            sp2C *= 1.1f;
        }

        Matrix_Push(&gGfxMatrix);
        Matrix_Translate(gGfxMatrix, -20.0f, 30.0f, -10.0f, MTXF_APPLY);

        if (!gVersusMode) {
            Matrix_RotateY(gGfxMatrix, -gPlayer[gPlayerNum].camYaw, MTXF_APPLY);
        }

        Matrix_Scale(gGfxMatrix, sp2C, sp2C, sp2C, MTXF_APPLY);
        Matrix_Translate(gGfxMatrix, 0.0f, -30.0f, 0.0f, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);

        if (!gVersusMode) {
            gSPDisplayList(gMasterDisp++, D_landmaster_30066B0);
        } else {
            gSPDisplayList(gMasterDisp++, D_versus_301B6E0);
        }
        Matrix_Pop(&gGfxMatrix);
    }
    Matrix_Pop(&gGfxMatrix);
}

void Display_SetCullingMode(void) {
    if (gReflectY != 0) {
        gSPSetGeometryMode(gMasterDisp++, G_CULL_FRONT);
        gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
    }
}

bool Display_ArwingWingsOverrideLimbDraw(s32 limbIndex, Gfx** gfxPtr, Vec3f* pos, Vec3f* rot, void* wingData) {
    ArwingInfo* arwing = (ArwingInfo*) wingData;

    if (D_display_800CA22C && (gPlayer[0].dmgEffect == 0)) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_29);
        Display_SetCullingMode();
    }

    switch (limbIndex) {
        case 13:
            if (arwing->rightWingState == WINGSTATE_NONE) {
                *gfxPtr = NULL;
            }
            if (arwing->rightWingState == WINGSTATE_BROKEN) {
                *gfxPtr = aAwLeftWingBrokenDL;
            }
            if (D_display_800CA22C && ((gRightWingFlashTimer[0] % 2) != 0)) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_34);
                Display_SetCullingMode();
                if (gRightWingFlashTimer[0] > 1000) {
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 32, 32, 255, 255);
                } else {
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
                }
            }
            break;

        case 1:
        case 2:
            if (arwing->rightWingState != 2) {
                *gfxPtr = NULL;
            }
            if (D_display_800CA22C && ((gRightWingFlashTimer[0] % 2) != 0)) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_34);
                Display_SetCullingMode();
                if (gRightWingFlashTimer[0] > 1000) {
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 32, 32, 255, 255);
                } else {
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
                }
            }
            break;

        case 12:
            if (arwing->rightWingState == WINGSTATE_NONE) { // should be leftWingState?
                *gfxPtr = NULL;
            }
            if (arwing->leftWingState == WINGSTATE_BROKEN) {
                *gfxPtr = aAwRightWingBrokenDL;
            }
            if (D_display_800CA22C && ((gLeftWingFlashTimer[0] % 2) != 0)) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_34);
                Display_SetCullingMode();
                if (gLeftWingFlashTimer[0] > 1000) {
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 32, 32, 255, 255);
                } else {
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
                }
            }
            break;

        case 5:
        case 6:
            if (arwing->leftWingState != 2) {
                *gfxPtr = NULL;
            }
            if (D_display_800CA22C && ((gLeftWingFlashTimer[0] % 2) != 0)) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_34);
                Display_SetCullingMode();
                if (gLeftWingFlashTimer[0] > 1000) {
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 32, 32, 255, 255);
                } else {
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
                }
            }
            break;
    }

    switch (limbIndex) {
        case 1:
            rot->y -= arwing->upperRightFlapYrot;
            break;
        case 2:
            rot->y -= arwing->bottomRightFlapYrot;
            break;
        case 5:
            rot->y -= arwing->bottomLeftFlapYrot;
            break;
        case 6:
            rot->y -= arwing->upperLeftFlapYrot;
            break;
        case 12:
            rot->z += arwing->wingsYrot;
            break;
        case 13:
            rot->z += arwing->wingsYrot;
            break;
        case 4:
            pos->z -= arwing->laserGunsYpos;
            pos->x += arwing->laserGunsXpos;
            break;
        case 8:
            pos->z += arwing->laserGunsYpos;
            pos->x += arwing->laserGunsXpos;
            break;
    }
    return false;
}

void Display_ArwingWings(ArwingInfo* arwing) {
    Vec3f frameTable[30];
    s32 drawFace;

    Matrix_Push(&gGfxMatrix);

    arwing->laserGunsXpos = 0.0f;
    if (arwing->laserGunsYpos < -7.0f) {
        arwing->laserGunsXpos = (-arwing->laserGunsYpos - 7.0f) * 2.5f;
    }

    if (gGameState == GSTATE_PLAY) {
        Animation_DrawSkeleton(1, D_arwing_3016610, gPlayer[0].jointTable, Display_ArwingWingsOverrideLimbDraw, NULL,
                               arwing, &gIdentityMatrix);
    } else {
        if (gGameState == GSTATE_MENU) {
            Animation_GetFrameData(&D_arwing_3015AF4, 0, frameTable);
        } else {
            Animation_GetFrameData(&D_arwing_3015C28, 0, frameTable);
        }
        Animation_DrawSkeleton(1, D_arwing_3016610, frameTable, Display_ArwingWingsOverrideLimbDraw, NULL, arwing,
                               &gIdentityMatrix);
    }

    D_display_800CA22C = false;

    drawFace = arwing->drawFace;
    if (D_display_800CA220 != 0) {
        drawFace = true;
    }

    // @port: Tag the transform.
    FrameInterpolation_RecordOpenChild(arwing, 0);

    if (drawFace != 0) {
        Matrix_Push(&gGfxMatrix);

        // @port: Tag the transform.
        FrameInterpolation_RecordOpenChild("ArwingCharFace", arwing->drawFace);

        Matrix_Translate(gGfxMatrix, 0.0f, 6.4f, -16.5f, MTXF_APPLY);
        Matrix_RotateY(gGfxMatrix, arwing->teamFaceYrot * M_DTOR, MTXF_APPLY);
        Matrix_RotateX(gGfxMatrix, arwing->teamFaceXrot * M_DTOR, MTXF_APPLY);
        Matrix_Scale(gGfxMatrix, 1.0f / 70.925f, 1.0f / 70.925f, 1.0f / 70.925f, MTXF_APPLY);

        if (gGameState == GSTATE_ENDING) {
            Matrix_Scale(gGfxMatrix, 0.95f, 0.95f, 0.95f, MTXF_APPLY);
        }

        Matrix_SetGfxMtx(&gMasterDisp);

        if (gExpertMode) {
            gSPDisplayList(gMasterDisp++, sExpertFaceDL[drawFace - 1]);
        } else {
            gSPDisplayList(gMasterDisp++, sFaceDL[drawFace - 1]);
        }
        Matrix_Pop(&gGfxMatrix);

        // @port Pop the transform id.
        FrameInterpolation_RecordCloseChild();
    }

    Matrix_Translate(gGfxMatrix, 0.0f, 17.2f, -25.8f, MTXF_APPLY);
    Matrix_RotateX(gGfxMatrix, arwing->cockpitGlassXrot * M_DTOR, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    RCP_SetupDL_64_2();

    if ((gGameState == GSTATE_PLAY) && (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_LEVEL_INTRO) &&
        (gCurrentLevel == LEVEL_CORNERIA)) {
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 120);
        gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
        gSPDisplayList(gMasterDisp++, D_arwing_30194E0);
        RCP_SetupDL_46();
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 100);
        gSPDisplayList(gMasterDisp++, D_arwing_30183D0);
    } else {
        RCP_SetupDL_46();
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 140);
        gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
        gSPDisplayList(gMasterDisp++, D_arwing_30194E0);
    }

    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
    Matrix_Pop(&gGfxMatrix);

    // @port Pop the transform id.
    FrameInterpolation_RecordCloseChild();
}

void Display_Unused(f32 arg0, f32 arg1, UNK_TYPE arg2, UNK_TYPE arg3) {
    /* Unimplemented. */
}

void Display_CockpitGlass(void) {
    Matrix_Push(&gGfxMatrix);

    // @port: Tag the transform.
    FrameInterpolation_RecordOpenChild("Display_CockpitGlass", 0);

    Matrix_Copy(gGfxMatrix, &D_display_80161418[0]);
    Matrix_Translate(gGfxMatrix, 0.0f, D_display_800CA290, D_display_800CA294, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, D_display_800CA28C, D_display_800CA28C, D_display_800CA28C, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    RCP_SetupDL_64_2();
    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 120);
    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
    gSPDisplayList(gMasterDisp++, D_arwing_30194E0);
    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
    Matrix_Pop(&gGfxMatrix);

    // @port Pop the transform id.
    FrameInterpolation_RecordCloseChild();
}

void Display_Arwing(Player* player, s32 reflectY) {
    Vec3f sp4C;
    f32 sp48;

    if ((gPlayerNum == player->num) && (reflectY == 0)) {
        sp48 = 0.0f;
        if (gChargeTimers[player->num] >= 20) {
            sp48 = (s32) (gGameFrameCount % 8U) * 80.0f;
        }
        sp4C.x = 0.0f;
        sp4C.y = 0.0f;
        sp4C.z = 1200.0f;
        Matrix_MultVec3f(gGfxMatrix, &sp4C, &D_display_801613E0[0]);
        sp4C.z = 2400.0f + sp48;
        Matrix_MultVec3f(gGfxMatrix, &sp4C, &D_display_801613E0[1]);
    }

    if (player->alternateView && (gLevelMode == LEVELMODE_ON_RAILS) &&
        (fabsf(player->trueZpos + gPathProgress - player->cam.eye.z) < 10.0f)) {
        if (reflectY == 0) {
            sDrawCockpit = true;
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, 0.0f, -8.0f, 5.0f, MTXF_APPLY);
            Matrix_RotateY(gGfxMatrix, M_PI, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, aAwCockpitViewDL);
            Matrix_Pop(&gGfxMatrix);
        }
    } else {
        if (gVersusMode) {
            if ((player->arwing.rightWingState == WINGSTATE_INTACT) &&
                (player->arwing.leftWingState == WINGSTATE_INTACT)) {
                gSPDisplayList(gMasterDisp++, D_versus_300EE80);
            } else if ((player->arwing.rightWingState <= WINGSTATE_BROKEN) &&
                       (player->arwing.leftWingState == WINGSTATE_INTACT)) {
                gSPDisplayList(gMasterDisp++, D_versus_3010A90);
            } else if ((player->arwing.rightWingState == WINGSTATE_INTACT) &&
                       (player->arwing.leftWingState <= WINGSTATE_BROKEN)) {
                gSPDisplayList(gMasterDisp++, D_versus_3011470);
            } else {
                gSPDisplayList(gMasterDisp++, D_versus_300D550);
            }
        } else {
            if ((gLevelType == LEVELTYPE_SPACE) || (gCurrentLevel == LEVEL_BOLSE)) {
                player->arwing.unk_28 = player->arwing.upperRightFlapYrot = player->arwing.bottomRightFlapYrot =
                    player->arwing.upperLeftFlapYrot = player->arwing.bottomLeftFlapYrot = 0.0f;
            }
            D_display_800CA22C = true;
            gReflectY = reflectY;
            Display_ArwingWings(&player->arwing);
        }
    }
}

void Display_Reticle(Player* player) {
    Vec3f* translate;
    s32 i;

    if ((gPlayerNum == player->num) && ((player->form == FORM_ARWING) || (player->form == FORM_LANDMASTER)) &&
        player->draw &&
        (((gGameState == GSTATE_PLAY) && (player->state_1C8 == PLAYERSTATE_1C8_ACTIVE)) ||
         (gGameState == GSTATE_MENU))) {
        for (i = 0; i < 2; i++) {
            FrameInterpolation_RecordOpenChild("Reticle", (player->num << 16) + i);
            FrameInterpolation_RecordMarker(__FILE__, __LINE__);
            translate = &D_display_801613E0[i];
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, translate->x, translate->y, translate->z, MTXF_APPLY);
            if (gChargeTimers[player->num] >= 20) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_63_POINT);
                if (i == 1) {
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
                    gDPSetEnvColor(gMasterDisp++, 255, 0, 0, 255);
                    Math_SmoothStepToF(&sReticleScales[player->num], 2.0f, 1.0f, 0.4f, 0.0f);
                } else {
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 0, 255);
                    gDPSetEnvColor(gMasterDisp++, 255, 255, 0, 255);
                }
            } else {
                gSPDisplayList(gMasterDisp++, gRcpSetupDLs[SETUPDL_36_POINT]);
            }

            if (i == 1) {
                Matrix_Scale(gGfxMatrix, sReticleScales[player->num], sReticleScales[player->num], 1.0f, MTXF_APPLY);
                Math_SmoothStepToF(&sReticleScales[player->num], 1.0f, 1.0f, 0.2f, 0.0f);
            }
            Matrix_Scale(gGfxMatrix, 4.0f, 4.0f, 4.0f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_1024F60);
            Matrix_Pop(&gGfxMatrix);
            FrameInterpolation_RecordCloseChild();
        }
    }
}

void Display_DrawPlayer(Player* player, s32 reflectY) {
    switch (player->form) {
        case FORM_ARWING:
            Display_Arwing(player, reflectY);
            break;
        case FORM_LANDMASTER:
            Display_Landmaster(player);
            break;
        case FORM_BLUE_MARINE:
            Aquas_BlueMarine_Draw(player);
            break;
        case FORM_ON_FOOT:
            Display_OnFootCharacter(player);
            break;
    }
}

void Display_PlayerShadow_Draw(Player* player) {
    Math_SmoothStepToF(&sPlayerShadowing, player->shadowing, 1.0f, 10.0f, 0.0f);
    RCP_SetupDL(&gMasterDisp, SETUPDL_66);
    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 0, 0, 0, (s32) sPlayerShadowing);

    if (player->groundPos.y > 30.0f) {
        gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
    }

    if ((gGroundSurface == SURFACE_WATER) && (player->groundPos.y < 10.0f)) {
        player->shadowing = 90;
    } else {
        player->shadowing = 180;
    }

    switch (player->form) {
        case FORM_ARWING:
        fake_label:
            Matrix_Scale(gGfxMatrix, 1.5f * 1.67f, 1.5f, 1.5f * 1.67f, MTXF_APPLY);
            Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, 30.0f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, aArwingShadowDL);
            break;

        case FORM_LANDMASTER:
            Matrix_Push(&gGfxMatrix);
            Matrix_Scale(gGfxMatrix, 1.17f, 1.17f, 1.17f, MTXF_APPLY);
            Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, 20.0f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            if (gCurrentLevel == LEVEL_MACBETH) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_65);
            }
            if (!gVersusMode) {
                gSPDisplayList(gMasterDisp++, D_landmaster_3008100);
            } else {
                gSPDisplayList(gMasterDisp++, D_versus_301E570);
            }
            Matrix_Pop(&gGfxMatrix);
            break;

        case FORM_BLUE_MARINE:
            break;

        case FORM_ON_FOOT:
            Matrix_Push(&gGfxMatrix);
            Matrix_Scale(gGfxMatrix, 0.5f, 0.5f, 0.5f, MTXF_APPLY);
            Matrix_RotateX(gGfxMatrix, M_PI / 2, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
            gSPDisplayList(gMasterDisp++, aRadarMarkKaSaucererDL);
            gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
            Matrix_Pop(&gGfxMatrix);
            break;
    }
}

void Display_DrawEngineGlow(EngineGlowColor color) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_67);
    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);

    switch (color) {
        case EG_RED:
            gDPSetEnvColor(gMasterDisp++, 255, 0, 0, 255);
            break;
        case EG_BLUE:
            gDPSetEnvColor(gMasterDisp++, 0, 0, 255, 255);
            break;
        case EG_GREEN:
            gDPSetEnvColor(gMasterDisp++, 0, 255, 0, 255);
            break;
        case EG_ORANGE:
            gDPSetEnvColor(gMasterDisp++, 255, 64, 0, 255);
            break;
    }
    gSPDisplayList(gMasterDisp++, aOrbDL);
}

void Display_LandmasterEngineGlow_Draw(Player* player) {
    RCP_SetupDL_64();
    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 100);
    Matrix_Push(&gGfxMatrix);
    Matrix_RotateZ(gGfxMatrix, player->bankAngle * M_DTOR, MTXF_APPLY);
    if (player->form == FORM_LANDMASTER) {
        if (player->unk_194 <= 0.0f) {
            Matrix_Pop(&gGfxMatrix);
            return;
        }
        Matrix_Scale(gGfxMatrix, player->unk_194, player->unk_194, 1.0f, MTXF_APPLY);
    } else {
        Matrix_Scale(gGfxMatrix, player->unk_194, player->unk_194, 1.0f, MTXF_APPLY);
    }

    if ((gGameFrameCount % 2) != 0) {
        Matrix_Scale(gGfxMatrix, 0.9f, 0.63f, 1.0f, MTXF_APPLY);
    } else {
        Matrix_Scale(gGfxMatrix, 0.9f * 0.9f, 0.9f * 0.63f, 1.0f, MTXF_APPLY);
    }
    Matrix_SetGfxMtx(&gMasterDisp);
    Display_DrawEngineGlow(gLevelType);
    Matrix_Pop(&gGfxMatrix);
}

void Display_BarrelRollShield(Player* player) {
    f32 zRotDirection;
    Vec3f src;
    Vec3f dest;

    if (player->barrelRollAlpha != 0) {
        Matrix_RotateY(gCalcMatrix, (player->yRot_114 + player->rot.y + player->damageShake + 180.0f) * M_DTOR,
                       MTXF_NEW);
        Matrix_RotateX(gCalcMatrix,
                       -((player->xRot_120 + player->rot.x + player->damageShake + player->aerobaticPitch) * M_DTOR),
                       MTXF_APPLY);
        Matrix_RotateZ(gCalcMatrix, -((player->bankAngle + player->rockAngle + player->damageShake) * M_DTOR),
                       MTXF_APPLY);

        Matrix_Translate(gCalcMatrix, player->xShake, player->yBob, 0.0f, MTXF_APPLY);

        src.x = 0.0f;
        src.y = 0.0f;
        src.z = -30.0f;

        Matrix_MultVec3f(gCalcMatrix, &src, &dest);

        zRotDirection = 1.0f;
        if (player->baseRollRate < 0) {
            zRotDirection = -1.0f;
        }

        Matrix_Push(&gGfxMatrix);

        // @port: Tag the transform.
        FrameInterpolation_RecordOpenChild("BarrelRollShield", 0);

        Matrix_Translate(gGfxMatrix, player->pos.x + dest.x, player->pos.y + dest.y,
                         player->trueZpos + player->zPath + dest.z, MTXF_APPLY);
        Matrix_RotateY(gGfxMatrix, -gPlayer[gPlayerNum].camYaw, MTXF_APPLY);
        Matrix_RotateX(gGfxMatrix, gPlayer[gPlayerNum].camPitch, MTXF_APPLY);
        Matrix_RotateZ(gGfxMatrix, gGameFrameCount * 20.0f * zRotDirection * M_DTOR, MTXF_APPLY);

        if (player->form == FORM_ARWING) {
            Matrix_Scale(gGfxMatrix, 2.0f, 2.0f, 2.0f, MTXF_APPLY);
        } else {
            Matrix_Scale(gGfxMatrix, 1.2f, 1.2f, 1.2f, MTXF_APPLY);
        }
        if (player->baseRollRate < 0) {
            Matrix_RotateX(gGfxMatrix, M_PI, MTXF_APPLY);
        }

        Matrix_SetGfxMtx(&gMasterDisp);
        RCP_SetupDL(&gMasterDisp, SETUPDL_67);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, player->barrelRollAlpha);
        gDPSetEnvColor(gMasterDisp++, 0, 0, 160, player->barrelRollAlpha);
        gSPDisplayList(gMasterDisp++, aBarrelRollTex);

        Matrix_Pop(&gGfxMatrix);

        // @port Pop the transform id.
        FrameInterpolation_RecordCloseChild();
    }
}

void Display_UnusedShield(Player* player) {
    if (gShieldAlpha[player->num] > 1.0f) {
        Matrix_Push(&gGfxMatrix);

        // @port: Tag the transform.
        FrameInterpolation_RecordOpenChild("Display_UnusedShield", 0);

        Matrix_Copy(gGfxMatrix, &D_display_80161418[player->num]);
        Matrix_Translate(gGfxMatrix, 0.0f, -5.0f, 10.0f, MTXF_APPLY);
        Matrix_Scale(gGfxMatrix, 2.5f, 1.6f, 2.5f, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        RCP_SetupDL(&gMasterDisp, SETUPDL_68);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 0, 255, 255, (s32) gShieldAlpha[player->num]);
        gDPSetEnvColor(gMasterDisp++, 255, 0, 255, (s32) gShieldAlpha[player->num]);
        gSPDisplayList(gMasterDisp++, aUnusedShieldDL);
        Matrix_Pop(&gGfxMatrix);

        // @port Pop the transform id.
        FrameInterpolation_RecordCloseChild();
        Lib_Texture_Scroll(aUnusedShieldTex, 32, 32, 3);
        Lib_Texture_Scroll(aUnusedShieldTex, 32, 32, 3);
    }
}

void Display_ArwingLaserCharge(Player* player) {
    Vec3f spC4 = { 0.0f, -5.0f, 60.0f };
    Vec3f spB8 = { 0.0f, -14.0f, 60.0f };
    Vec3f spAC = { 30.0f, -10.0f, 30.0f };
    Vec3f spA0 = { -30.0f, -10.0f, 30.0f };
    Vec3f sp94;
    Vec3f sp88;
    u8 laserStrength;
    f32 sp80;

    if (gChargeTimers[player->num] > 10) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_67);
        Matrix_Copy(gCalcMatrix, &D_display_80161418[player->num]);
        if (player->alternateView && (gLevelMode == LEVELMODE_ON_RAILS)) {
            Matrix_MultVec3f(gCalcMatrix, &spB8, &sp94);
        } else {
            Matrix_MultVec3f(gCalcMatrix, &spC4, &sp94);
        }

        Matrix_Push(&gGfxMatrix);

        sp80 = gChargeTimers[player->num] / 20.0f;

        Matrix_Translate(gGfxMatrix, sp94.x, sp94.y, sp94.z, MTXF_NEW);
        Matrix_Scale(gGfxMatrix, sp80, sp80, 1.0f, MTXF_APPLY);
        Matrix_Push(&gGfxMatrix);

        if (player->alternateView && (gLevelMode == LEVELMODE_ON_RAILS)) {
            Matrix_Scale(gGfxMatrix, 3.0f, 3.0f, 3.0f, MTXF_APPLY);
        } else {
            Matrix_Scale(gGfxMatrix, 10.0f, 10.0f, 10.0f, MTXF_APPLY);
        }
        RCP_SetupDL(&gMasterDisp, SETUPDL_49);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 128);

        if (gVersusMode) {
            switch (player->num) {
                case 0:
                    gDPSetEnvColor(gMasterDisp++, 255, 255, 32, 128);
                    break;
                case 1:
                    gDPSetEnvColor(gMasterDisp++, 255, 32, 32, 128);
                    break;
                case 2:
                    gDPSetEnvColor(gMasterDisp++, 32, 255, 32, 128);
                    break;
                case 3:
                    gDPSetEnvColor(gMasterDisp++, 32, 32, 255, 128);
                    break;
            }
        } else {
            gDPSetEnvColor(gMasterDisp++, 0, 255, 0, 128);
        }

        Matrix_RotateZ(gGfxMatrix, gGameFrameCount * 53.0f * M_DTOR, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, aStarDL);
        Matrix_RotateZ(gGfxMatrix, gGameFrameCount * -53.0f * 2.0f * M_DTOR, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, aStarDL);
        Matrix_Pop(&gGfxMatrix);

        if (player->alternateView && (gLevelMode == LEVELMODE_ON_RAILS)) {
            Matrix_Scale(gGfxMatrix, 0.3f, 0.3f, 0.3f, MTXF_APPLY);
        }

        Matrix_Scale(gGfxMatrix, 0.5f, 0.5f, 1.0f, MTXF_APPLY);

        if ((gGameFrameCount % 2) == 0) {
            Matrix_Scale(gGfxMatrix, 1.7f, 1.7f, 1.0f, MTXF_APPLY);
        } else {
            Matrix_Scale(gGfxMatrix, 1.3f, 1.3f, 1.0f, MTXF_APPLY);
        }
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, aOrbDL);
        Matrix_Pop(&gGfxMatrix);
    }
    if (gMuzzleFlashScale[player->num] > 0.1f) {
        Matrix_Push(&gGfxMatrix);
        RCP_SetupDL(&gMasterDisp, SETUPDL_67);
        Matrix_Copy(gCalcMatrix, &D_display_80161418[player->num]);

        laserStrength = gLaserStrength[player->num];
        if (player->arwing.laserGunsYpos > -8.0f) {
            laserStrength = LASERS_SINGLE;
        }

        switch (laserStrength) {
            case LASERS_SINGLE:
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 192, 255, 192, 128);
                gDPSetEnvColor(gMasterDisp++, 64, 255, 64, 128);
                if (player->alternateView && (gLevelMode == LEVELMODE_ON_RAILS)) {
                    Matrix_MultVec3f(gCalcMatrix, &spB8, &sp94);
                } else {
                    Matrix_MultVec3f(gCalcMatrix, &spC4, &sp94);
                }

                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, sp94.x, sp94.y, sp94.z, MTXF_NEW);
                Matrix_Scale(gGfxMatrix, gMuzzleFlashScale[player->num], gMuzzleFlashScale[player->num], 1.0f,
                             MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, aOrbDL);

                Matrix_Pop(&gGfxMatrix);
                break;

            case LASERS_TWIN:
            case LASERS_HYPER:
                if (laserStrength == LASERS_TWIN) {
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 192, 255, 192, 128);
                    gDPSetEnvColor(gMasterDisp++, 64, 255, 64, 128);
                } else {
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 128, 255, 255, 160);
                    gDPSetEnvColor(gMasterDisp++, 128, 128, 255, 160);
                }
                Matrix_MultVec3f(gCalcMatrix, &spAC, &sp94);
                Matrix_MultVec3f(gCalcMatrix, &spA0, &sp88);
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, sp94.x, sp94.y, sp94.z, MTXF_NEW);
                Matrix_Scale(gGfxMatrix, gMuzzleFlashScale[player->num], gMuzzleFlashScale[player->num], 1.0f,
                             MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, aOrbDL);
                Matrix_Pop(&gGfxMatrix);

                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, sp88.x, sp88.y, sp88.z, MTXF_NEW);
                Matrix_Scale(gGfxMatrix, gMuzzleFlashScale[player->num], gMuzzleFlashScale[player->num], 1.0f,
                             MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, aOrbDL);

                Matrix_Pop(&gGfxMatrix);
                break;
        }
        Matrix_Pop(&gGfxMatrix);
    }
}

void Display_LandmasterLaserCharge(Player* player) {
    f32 sp54;

    if (gChargeTimers[player->num] > 10) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_67);
        Matrix_Push(&gGfxMatrix);

        sp54 = gChargeTimers[player->num] / 20.0f;

        Matrix_Translate(gGfxMatrix, D_display_80161548[player->num].x, D_display_80161548[player->num].y,
                         D_display_80161548[player->num].z, MTXF_NEW);

        Matrix_Scale(gGfxMatrix, sp54, sp54, 1.0f, MTXF_APPLY);

        Matrix_Push(&gGfxMatrix);

        Matrix_Scale(gGfxMatrix, 10.0f, 10.0f, 10.0f, MTXF_APPLY);

        RCP_SetupDL(&gMasterDisp, SETUPDL_49);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 128);

        if (gVersusMode) {
            switch (player->num) {
                case 0:
                    gDPSetEnvColor(gMasterDisp++, 255, 255, 32, 128);
                    break;
                case 1:
                    gDPSetEnvColor(gMasterDisp++, 255, 32, 32, 128);
                    break;
                case 2:
                    gDPSetEnvColor(gMasterDisp++, 32, 255, 32, 128);
                    break;
                case 3:
                    gDPSetEnvColor(gMasterDisp++, 32, 32, 255, 128);
                    break;
            }
        } else {
            gDPSetEnvColor(gMasterDisp++, 0, 255, 0, 128);
        }

        Matrix_RotateZ(gGfxMatrix, gGameFrameCount * 53.0f * M_DTOR, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, aStarDL);

        Matrix_RotateZ(gGfxMatrix, gGameFrameCount * -53.0f * 2.0f * M_DTOR, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, aStarDL);

        Matrix_Pop(&gGfxMatrix);
        Matrix_Scale(gGfxMatrix, 0.5f, 0.5f, 1.0f, MTXF_APPLY);

        if ((gGameFrameCount % 2) == 0) {
            Matrix_Scale(gGfxMatrix, 1.7f, 1.7f, 1.0f, MTXF_APPLY);
        } else {
            Matrix_Scale(gGfxMatrix, 1.3f, 1.3f, 1.0f, MTXF_APPLY);
        }
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, aOrbDL);
        Matrix_Pop(&gGfxMatrix);
    }
}

void Display_PlayerFeatures(Player* player) {
    Vec3f src;
    Vec3f dest;
    f32 var_fv0;
    s32 pad[3];

    if (player->draw && (player->state_1C8 != PLAYERSTATE_1C8_DOWN)) {
        switch (player->form) {
            case FORM_ARWING:
                Matrix_RotateY(gCalcMatrix, (player->yRot_114 + player->rot.y + player->damageShake + 180.0f) * M_DTOR,
                               MTXF_NEW);
                Matrix_RotateX(
                    gCalcMatrix,
                    -((player->xRot_120 + player->rot.x + player->damageShake + player->aerobaticPitch) * M_DTOR),
                    MTXF_APPLY);
                Matrix_RotateZ(gCalcMatrix, -((player->bankAngle + player->rockAngle + player->damageShake) * M_DTOR),
                               MTXF_APPLY);
                Matrix_Translate(gCalcMatrix, player->xShake, player->yBob, 0.0f, MTXF_APPLY);
                var_fv0 = player->unk_194 * 30.0f;
                if (var_fv0 > 30.0f) {
                    var_fv0 = 30.0f;
                }

                src.x = 0;
                src.y = 0;
                src.z = -40.0f - var_fv0;

                Matrix_MultVec3f(gCalcMatrix, &src, &dest);
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, player->pos.x + dest.x, player->pos.y + dest.y,
                                 player->trueZpos + player->zPath + dest.z, MTXF_APPLY);
                Matrix_RotateY(gGfxMatrix, -gPlayer[gPlayerNum].camYaw, MTXF_APPLY);
                Matrix_RotateX(gGfxMatrix, gPlayer[gPlayerNum].camPitch, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                Display_LandmasterEngineGlow_Draw(player);
                Matrix_Pop(&gGfxMatrix);
                Display_BarrelRollShield(player);
                Display_UnusedShield(player);
                Display_ArwingLaserCharge(player);
                break;

            case FORM_LANDMASTER:
                Display_LandmasterThrusters(player);
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, D_display_80161518[player->num].x, D_display_80161518[player->num].y,
                                 D_display_80161518[player->num].z, MTXF_NEW);
                Matrix_SetGfxMtx(&gMasterDisp);
                Display_LandmasterEngineGlow_Draw(player);
                Matrix_Pop(&gGfxMatrix);
                Display_LandmasterLaserCharge(player);
                break;

            case FORM_BLUE_MARINE:
                Display_BarrelRollShield(player);
                break;
        }
    }
}

void Display_ArwingWingTrail_Draw(Player* player) {
    f32 sp5C = 70.0f;
    f32 sp58 = -18.0f;
    f32 sp54;
    f32 sp50;
    f32 yRot;

    if (player->wingPosition == 2) {
        sp5C = 108.0f;
        sp58 = -22.0f;
    }
    if (player->contrailScale != 0.0f) {
        sp54 = 0.0f;
        if ((gGameFrameCount % 2) != 0) {
            sp54 = 180.0f;
        }

        yRot = player->rot.y;
        if (yRot > 90.0f) {
            yRot -= 180.0f;
        }

        yRot *= 0.25f;
        sp50 = player->rot.x * 0.25f;

        if (player->state_1C8 == PLAYERSTATE_1C8_LEVEL_COMPLETE) {
            yRot = 0.0f;
            sp50 = 0.0f;
        }

        RCP_SetupDL_64();
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 100);

        // @port: Tag the transform.
        FrameInterpolation_RecordOpenChild("WingTrail", 0);

        if (player->arwing.leftWingState == WINGSTATE_INTACT) {
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, sp5C, sp58, -100.0f, MTXF_APPLY);
            Matrix_RotateX(gGfxMatrix, M_DTOR * sp50, MTXF_APPLY);
            Matrix_RotateY(gGfxMatrix, -(M_DTOR * yRot), MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, player->contrailScale, 1.0f, 50.0f, MTXF_APPLY);
            Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -17.5f, MTXF_APPLY);
            Matrix_RotateX(gGfxMatrix, M_PI / 2, MTXF_APPLY);
            Matrix_RotateY(gGfxMatrix, M_DTOR * sp54, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, aRadarMarkKaSaucererDL);
            Matrix_Pop(&gGfxMatrix);
        }

        // @port Pop the transform id.
        FrameInterpolation_RecordCloseChild();

        // @port: Tag the transform.
        FrameInterpolation_RecordOpenChild("WingTrail", 1);

        if (player->arwing.rightWingState == WINGSTATE_INTACT) {
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, -sp5C, sp58, -100.0f, MTXF_APPLY);
            Matrix_RotateX(gGfxMatrix, M_DTOR * sp50, MTXF_APPLY);
            Matrix_RotateY(gGfxMatrix, -(M_DTOR * yRot), MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, player->contrailScale, 1.0f, 50.0f, MTXF_APPLY);
            Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -17.5f, MTXF_APPLY);
            Matrix_RotateX(gGfxMatrix, M_PI / 2, MTXF_APPLY);
            Matrix_RotateY(gGfxMatrix, M_DTOR * sp54, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, aRadarMarkKaSaucererDL);
            Matrix_Pop(&gGfxMatrix);
        }

        // @port Pop the transform id.
        FrameInterpolation_RecordCloseChild();
    }
}

void Display_ArwingWingTrail_Update(Player* player) {
    if (player->draw && (player->form == FORM_ARWING) && (gCurrentLevel != LEVEL_VENOM_ANDROSS) &&
        (gCurrentLevel != LEVEL_TRAINING) && (gLevelType == LEVELTYPE_PLANET)) {
        Matrix_Push(&gGfxMatrix);
        Matrix_Translate(gGfxMatrix, player->pos.x, player->pos.y, player->trueZpos + player->zPath, MTXF_APPLY);
        Matrix_RotateY(gGfxMatrix, (player->yRot_114 + player->rot.y + 180.0f) * M_DTOR, MTXF_APPLY);
        Matrix_RotateX(gGfxMatrix, -((player->xRot_120 + player->rot.x + player->aerobaticPitch) * M_DTOR), MTXF_APPLY);
        Matrix_RotateZ(gGfxMatrix, -((player->bankAngle + player->rockAngle + player->damageShake) * M_DTOR),
                       MTXF_APPLY);
        Matrix_Translate(gGfxMatrix, player->xShake, player->yBob, 0.0f, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        Display_ArwingWingTrail_Draw(player);
        Matrix_Pop(&gGfxMatrix);
    }
}

bool Display_CheckPlayerVisible(s32 index, s32 reflectY) {
    Vec3f src = { 0.0f, 0.0f, 0.0f };
    Vec3f dest;

    Matrix_MultVec3f(gGfxMatrix, &src, &dest);

    if ((dest.z < 200.0f) && (dest.z > -12000.0f)) {
        if (fabsf(dest.x) < (fabsf(dest.z * /*0.5f*/ 1.5f) + 500.0f)) {
            if (fabsf(dest.y) < (fabsf(dest.z * 0.5f) + 500.0f)) {
                if (reflectY == 0) {
                    sPlayersVisible[index] = true;
                }
                return true;
            }
        }
    }

    if (reflectY == 0) {
        sPlayersVisible[index] = false;
    }
    return false;
}

// unused
s32 D_display_800CA2E8[16] = { 60, 40, 20, 20, 20, 20, 20, 20, 0, 0, 0, 0, 0, 0, 0, 0 };

void Display_Player_Update(Player* player, s32 reflectY) {
    s32 i;
    Vec3f sp50 = { 0.0f, 0.0f, 0.0f };

    if (player->draw) {
        Matrix_Push(&gGfxMatrix);
        if (player->form == FORM_LANDMASTER) {
            if (player->grounded) {
                Matrix_Translate(gGfxMatrix, 0.0f, gCameraShakeY, 0.0f, MTXF_APPLY);
            }
            Matrix_Translate(gGfxMatrix, player->pos.x, player->pos.y + player->unk_18C + 30.0f,
                             player->trueZpos + player->zPath, MTXF_APPLY);
            if (gVersusMode) {
                for (i = 0; i < gCamCount; i++) {
                    if (gVsLockOnTimers[player->num][i] != 0) {
                        Matrix_MultVec3f(gGfxMatrix, &sp50, &gLockOnTargetViewPos[i]);
                        if ((i == gPlayerNum) &&
                            ((gLockOnTargetViewPos[i].z > 300.0f) || (gLockOnTargetViewPos[i].z < -8000.0f) ||
                             (fabsf(gLockOnTargetViewPos[i].x) > (fabsf(gLockOnTargetViewPos[i].z * 0.5f) + 100.0f)) ||
                             (fabsf(gLockOnTargetViewPos[i].y)) > (fabsf(gLockOnTargetViewPos[i].z * 0.5f) + 100.0f))) {

                            gVsLockOnTimers[player->num][i] = 0;
                        }
                    }
                }
            }

            if (!Display_CheckPlayerVisible(player->num, reflectY)) {
                Matrix_Pop(&gGfxMatrix);
                return;
            }

            Matrix_RotateX(gGfxMatrix, (player->rot.x + player->damageShake) * M_DTOR, MTXF_APPLY);
            Matrix_RotateZ(gGfxMatrix, (player->rot.z + player->rockAngle + player->damageShake) * M_DTOR, MTXF_APPLY);
            Matrix_RotateY(gGfxMatrix, (player->yRot_114 + player->rot.y + 180.0f) * M_DTOR, MTXF_APPLY);

            if (gVersusMode) {
                Matrix_RotateX(gGfxMatrix, player->unk_000 * M_DTOR, MTXF_APPLY);
            }

            Matrix_RotateZ(gGfxMatrix, (-player->zRotBank - player->zRotBarrelRoll) * M_DTOR, MTXF_APPLY);
            Matrix_Translate(gGfxMatrix, player->xShake, player->yBob - 30.0f, 0.0f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
        } else if (player->form == FORM_ON_FOOT) {
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, player->pos.x, player->pos.y, player->trueZpos + player->zPath, MTXF_APPLY);

            if (!Display_CheckPlayerVisible(player->num, reflectY)) {
                Matrix_Pop(&gGfxMatrix);
                Matrix_Pop(&gGfxMatrix);
                return;
            }

            Matrix_Pop(&gGfxMatrix);
            Matrix_Translate(gCalcMatrix, player->pos.x, player->pos.y + gCameraShakeY,
                             player->trueZpos + player->zPath, MTXF_NEW);
            Matrix_RotateY(gCalcMatrix, (player->yRot_114 + player->rot.y + player->damageShake + 180.0f) * M_DTOR,
                           MTXF_APPLY);
            Matrix_RotateX(gCalcMatrix, -((player->xRot_120 + player->rot.x + player->damageShake) * M_DTOR),
                           MTXF_APPLY);
            Matrix_RotateZ(gCalcMatrix, -((player->bankAngle + player->rockAngle + player->damageShake) * M_DTOR),
                           MTXF_APPLY);
            Matrix_Translate(gCalcMatrix, player->xShake, player->yBob, 0.0f, MTXF_APPLY);
        } else {
            Matrix_Translate(gGfxMatrix, player->pos.x, player->pos.y, player->trueZpos + player->zPath, MTXF_APPLY);
            if (gVersusMode) {
                for (i = 0; i < gCamCount; i++) {
                    if (gVsLockOnTimers[player->num][i] != 0) {
                        Matrix_MultVec3f(gGfxMatrix, &sp50, &gLockOnTargetViewPos[i]);
                        if ((i == gPlayerNum) &&
                            ((gLockOnTargetViewPos[i].z > 300.0f) || (gLockOnTargetViewPos[i].z < -8000.0f) ||
                             (fabsf(gLockOnTargetViewPos[i].x) > (fabsf(gLockOnTargetViewPos[i].z * 0.5f) + 100.0f)) ||
                             (fabsf(gLockOnTargetViewPos[i].y) > (fabsf(gLockOnTargetViewPos[i].z * 0.5f) + 100.0f)))) {

                            gVsLockOnTimers[player->num][i] = 0;
                        }
                    }
                }
            }

            if (!Display_CheckPlayerVisible(player->num, reflectY)) {
                Matrix_Pop(&gGfxMatrix);
                return;
            }
            Matrix_RotateY(gGfxMatrix, (player->yRot_114 + player->rot.y + player->damageShake + 180.0f) * M_DTOR,
                           MTXF_APPLY);
            Matrix_RotateX(
                gGfxMatrix,
                -((player->xRot_120 + player->rot.x + player->aerobaticPitch + player->damageShake) * M_DTOR),
                MTXF_APPLY);
            Matrix_RotateZ(gGfxMatrix, -((player->bankAngle + player->rockAngle + player->damageShake) * M_DTOR),
                           MTXF_APPLY);
            Matrix_Translate(gGfxMatrix, player->xShake, player->yBob, 0.0f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
        }

        switch (player->dmgEffect) {
            case 0:
                if (!gVersusMode) {
                    if ((gCurrentLevel == LEVEL_FORTUNA) || (gCurrentLevel == LEVEL_TITANIA)) {
                        RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, 1005);
                    } else {
                        RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
                    }
                } else if (gVersusStage == VS_STAGE_SECTOR_Z) {
                    RCP_SetupDL_29(128, 128, 255, 255, gFogNear, gFogFar);
                } else {
                    RCP_SetupDL_29(0, 0, 0, 255, gFogNear, gFogFar);
                }
                break;

            case 1:
                RCP_SetupDL_27();
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
                break;

            case 2:
                RCP_SetupDL_32();
                break;
        }

        if (reflectY != 0) {
            Object_ApplyWaterDistortion();
        } else {
            Matrix_Copy(&D_display_80161418[player->num], gGfxMatrix);
        }
        Display_DrawPlayer(player, reflectY);
        Matrix_Pop(&gGfxMatrix);
    }
}

f32 D_display_800CA334[] = {
    0.02f, 0.06f, 0.08f, 0.05f, 0.04f, 0.03f, 0.06f, 0.04f,
};
Gfx* sTeammateMarkDLs[] = {
    aFalcoMarkDL, aFalcoMarkDL, aSlippyMarkDL, aPeppyMarkDL, aPeppyMarkDL, aPeppyMarkDL,
    aPeppyMarkDL, aPeppyMarkDL, aKattMarkDL,   aBillMarkDL,  aJamesMarkDL,
};
f32 D_display_800CA380 = 0.0f;
f32 D_display_800CA384 = 0.0f;
f32 D_display_800CA388 = -300.0f;
f32 D_display_800CA38C[] = { 0.0f, -300.0f, -150.0f, -50.0f };

void Display_PlayerShadow_Update(Player* player) {
    f32 xScale;
    f32 zScale;
    f32 angle;

    if (player->draw && !player->hideShadow) {
        xScale = D_display_800CA334[gGameFrameCount % 8U];
        zScale = D_display_800CA334[(gGameFrameCount + 4) % 8U];

        if (player->grounded) {
            xScale = zScale = 0.0f;
        }

        Matrix_Push(&gGfxMatrix);

        if (gLevelMode == LEVELMODE_ALL_RANGE) {
            if (player->form == FORM_ON_FOOT) {
                Matrix_Translate(gGfxMatrix, player->groundPos.x, player->groundPos.y + 2.0f, player->groundPos.z,
                                 MTXF_APPLY);
            } else {
                Matrix_Translate(gGfxMatrix, player->groundPos.x, player->groundPos.y + 2.0f, player->groundPos.z,
                                 MTXF_APPLY);
            }
        } else {
            Matrix_Translate(gGfxMatrix, player->groundPos.x, player->groundPos.y + 2.0f,
                             player->groundPos.z + player->zPath, MTXF_APPLY);
        }

        Matrix_RotateY(gGfxMatrix, player->groundRotY, MTXF_APPLY);
        Matrix_RotateX(gGfxMatrix, player->shadowRotX, MTXF_APPLY);
        Matrix_RotateZ(gGfxMatrix, player->shadowRotZ, MTXF_APPLY);

        Matrix_Scale(gGfxMatrix, 0.8f + xScale, 0.0f, 0.8f + zScale, MTXF_APPLY);

        if ((player->form == FORM_ARWING) || (player->form == FORM_BLUE_MARINE) || (player->form == FORM_ON_FOOT)) {
            angle = player->bankAngle + player->rockAngle + player->damageShake;
            if (((angle > 70.0f) && (angle < 110.0f)) || ((angle < -70.0f) && (angle > -110.0f))) {
                angle = 70.0f;
            }
            Matrix_RotateY(gGfxMatrix, -player->groundRotY, MTXF_APPLY);
            Matrix_RotateY(gGfxMatrix, (player->yRot_114 + player->rot.y + player->damageShake) * M_DTOR, MTXF_APPLY);
            Matrix_RotateX(
                gGfxMatrix,
                -((player->xRot_120 + player->rot.x + player->aerobaticPitch + player->damageShake) * M_DTOR),
                MTXF_APPLY);
            Matrix_RotateZ(gGfxMatrix, M_DTOR * angle, MTXF_APPLY);
        } else {
            Matrix_RotateY(gGfxMatrix, player->yRot_114 * M_DTOR, MTXF_APPLY);
            Matrix_RotateX(gGfxMatrix, (player->rot.x + player->aerobaticPitch + player->damageShake) * M_DTOR,
                           MTXF_APPLY);
            Matrix_RotateZ(gGfxMatrix, (player->rot.z + player->rockAngle + player->damageShake) * M_DTOR, MTXF_APPLY);
            Matrix_RotateY(gGfxMatrix, player->rot.y * M_DTOR, MTXF_APPLY);
            Matrix_RotateZ(gGfxMatrix, (-player->zRotBank - player->zRotBarrelRoll) * M_DTOR, MTXF_APPLY);
        }
        Display_PlayerShadow_Draw(player);
        Matrix_Pop(&gGfxMatrix);
    }
}

void Display_ActorMarks(void) {
    s32 i;
    f32 var_fs0;

    if ((gGameFrameCount & 4) == 0) {
        RCP_SetupDL_40();

        for (i = 0; i < ARRAY_COUNT(gTeamArrowsViewPos); i++) {
            if (gTeamArrowsViewPos[i].z < 0.0f) {
                FrameInterpolation_RecordOpenChild(&gTeamArrowsViewPos[i], i);
                FrameInterpolation_RecordMarker(__FILE__, __LINE__);
                var_fs0 = (VEC3F_MAG(&gTeamArrowsViewPos[i])) * 0.0015f;
                if (var_fs0 > 100.0f) {
                    var_fs0 = 100.0f;
                } else if (var_fs0 < 1.0f) {
                    var_fs0 = 1.0f;
                }

                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, gTeamArrowsViewPos[i].x, gTeamArrowsViewPos[i].y, gTeamArrowsViewPos[i].z,
                                 MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, var_fs0 * 0.25f, var_fs0 * 0.25f, 1.0f, MTXF_APPLY);

                if ((i == 0) && (gCurrentLevel == LEVEL_SECTOR_Z)) {
                    Matrix_Scale(gGfxMatrix, 2.0f, 2.0f, 1.0f, MTXF_APPLY);
                }

                Matrix_Translate(gGfxMatrix, 0.0f, 150.0f, 0.0f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gDPSetTextureFilter(gMasterDisp++, G_TF_POINT);

                if ((i == 0) && (gCurrentLevel == LEVEL_SECTOR_Z)) {
                    gSPDisplayList(gMasterDisp++, aSzMissileMark);
                } else {
                    gSPDisplayList(gMasterDisp++, sTeammateMarkDLs[i]);
                }
                Matrix_Pop(&gGfxMatrix);
                FrameInterpolation_RecordCloseChild();
            }
            gTeamArrowsViewPos[i].x = gTeamArrowsViewPos[i].y = 0;
            gTeamArrowsViewPos[i].z = 100.0f;
        }
        gDPSetTextureFilter(gMasterDisp++, G_TF_BILERP);
    }
}

void Display_LockOnIndicator(void) {
    s32 i;
    s32 j;
    f32 var_fs0;

    for (i = 0; i < gCamCount; i++) {
        if (gLockOnTargetViewPos[i].z < 0.0f) {
            var_fs0 = VEC3F_MAG(&gLockOnTargetViewPos[i]);
            if (var_fs0 < 20000.0f) {
                FrameInterpolation_RecordOpenChild("LcckOnIndicator", 0);
                FrameInterpolation_RecordMarker(__FILE__, __LINE__);
                var_fs0 *= 0.0015f;
                if (var_fs0 > 100.0f) {
                    var_fs0 = 100.0f;
                }
                if (var_fs0 < 1.2f) {
                    var_fs0 = 1.2f;
                }

                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, gLockOnTargetViewPos[i].x, gLockOnTargetViewPos[i].y,
                                 gLockOnTargetViewPos[i].z, MTXF_APPLY);
                if ((gPlayState != PLAY_PAUSE) && (i == gPlayerNum)) {
                    Math_SmoothStepToF(&D_display_801615A8[i], 0.0f, 0.5f, 20.0f, 0);
                    Math_SmoothStepToF(&D_display_801615B8[i], 1.0, 0.5f, 0.2f, 0);
                }
                var_fs0 *= D_display_801615B8[i];
                Matrix_Scale(gGfxMatrix, var_fs0 * 1.5f, var_fs0 * 1.5f, 1.0f, MTXF_APPLY);
                Matrix_RotateZ(gGfxMatrix, D_display_801615A8[i] * M_DTOR, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                RCP_SetupDL(&gMasterDisp, SETUPDL_67);
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
                gDPSetEnvColor(gMasterDisp++, 255, 0, 0, 255);
                gSPDisplayList(gMasterDisp++, D_1024F60);
                Matrix_Pop(&gGfxMatrix);
                FrameInterpolation_RecordCloseChild();
            }
        }
    }
    for (j = 0; j < gCamCount; j++) {
        gLockOnTargetViewPos[j].x = gLockOnTargetViewPos[j].y = 0.f;
        gLockOnTargetViewPos[j].z = 100.0f;
    }
}

void Display_SetupPlayerSfxPos(Player* player) {
    Vec3f sp2C;
    Vec3f sp20;

    sp20.x = player->pos.x;
    sp20.y = player->pos.y;
    sp20.z = player->trueZpos;
    sp2C.x = player->sfxSource[0];
    sp2C.y = player->sfxSource[1];
    sp2C.z = player->sfxSource[2];
    Object_SetSfxSourceToPos(player->sfxSource, &sp20);
    player->sfxVel[0] = player->sfxSource[0] - sp2C.x;
    player->sfxVel[1] = player->sfxSource[1] - sp2C.y;
    player->sfxVel[2] = player->sfxSource[2] - sp2C.z;
    player->sfx.srcVel = player->sfxVel;
    player->sfx.srcPos = player->sfxSource;
    player->sfx.yVel = player->vel.y;
    player->sfx.zRot = player->bankAngle;
}

void Display_CsLevelCompleteHandleCamera(Player* player) {
    Vec3f sp4C = { 0.0f, 0.0f, -300.0f };
    Vec3f sp40;
    f32 sp3C;
    f32 sp38;

    switch (D_display_800CA220) {
        case 0:
            Math_SmoothStepToAngle(&player->arwing.teamFaceXrot, 0.0f, 0.2f, 3.0f, 0.0f);
            Math_SmoothStepToAngle(&player->arwing.teamFaceYrot, 0.0f, 0.2f, 3.0f, 0.0f);
            gPlayCamEye.x = player->cam.eye.x;
            gPlayCamEye.y = player->cam.eye.y;
            gPlayCamEye.z = player->cam.eye.z;
            gPlayCamAt.x = player->cam.at.x;
            gPlayCamAt.y = player->cam.at.y;
            gPlayCamAt.z = player->cam.at.z;
            break;

        // Seems unused. Some sort of debugging code leftover?
        case 1:
        case 2:
        case 3:
            sp38 = Math_RadToDeg(player->camPitch) + player->rot.x;
            if (sp38 > 360.0f) {
                sp38 -= 360.0f;
            }
            if (sp38 < 0.0f) {
                sp38 += 360.0f;
            }
            sp3C = (Math_RadToDeg(player->camYaw) + 180.0f) - player->rot.y;
            if (sp3C > 360.0f) {
                sp3C -= 360.0f;
            }
            if (sp3C < 0.0f) {
                sp3C += 360.0f;
            }
            sp3C = 360.0f - sp3C;

            Math_SmoothStepToAngle(&player->arwing.teamFaceXrot, sp38, 0.2f, 6.0f, 0.0f);
            Math_SmoothStepToAngle(&player->arwing.teamFaceYrot, sp3C, 0.2f, 6.0f, 0.0f);

            Math_SmoothStepToF(&D_display_800CA380, gControllerPress[0].stick_y * 0.75f, 0.1f, 2.0f, 0.0f);
            Math_SmoothStepToF(&D_display_800CA384, gControllerPress[0].stick_x * 3.0f, 0.1f, 5.0f, 0.0f);
            Math_SmoothStepToF(&D_display_800CA388, D_display_800CA38C[D_display_800CA220], 0.1f, 10.0f, 0.0f);

            sp4C.z = D_display_800CA388;
            Matrix_RotateX(gCalcMatrix, (player->rot.y + D_display_800CA380) * M_DTOR, MTXF_NEW);
            Matrix_RotateY(gCalcMatrix, (player->rot.x + D_display_800CA384) * M_DTOR, MTXF_APPLY);
            Matrix_MultVec3f(gCalcMatrix, &sp4C, &sp40);
            gPlayCamEye.x = player->pos.x + sp40.x;
            gPlayCamEye.y = player->pos.y + sp40.y + 20.0f;
            gPlayCamEye.z = player->trueZpos + sp40.z;
            gPlayCamAt.x = (SIN_DEG(gGameFrameCount * 3.0f) * 3.0f) + player->pos.x;
            gPlayCamAt.y = (COS_DEG(gGameFrameCount * 4.0f) * 3.0f) + player->pos.y;
            gPlayCamAt.z = (SIN_DEG(gGameFrameCount * 3.5f) * 3.0f) + player->trueZpos;
            break;
    }
}
#if 1
f32 gTestVarF = 0.0f;
#endif
void Display_Update(void) {
    s32 i;
    Vec3f tempVec;
    Vec3f playerCamUp;
    Vec3f playerPos;
    s32 pad;
    Player* player;
    Player* camPlayer = &gPlayer[gPlayerNum];

    sDrawCockpit = false;

    // @port: Display player's face at all times.
    gPlayer[0].arwing.drawFace = true;

    // @port remove 511 hit count cap, hated by generations
#if 0
    // 511 hit count cap
    if (gHitCount > 511) {
        gHitCount = 511;
    }
#endif

    Matrix_Push(&gGfxMatrix);
    if ((gCurrentLevel == LEVEL_AQUAS) && (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_ACTIVE)) {
        Math_SmoothStepToF(&gCamDistortion, 0.01f, 0.2f, 0.002f, 0.0f);
    } else {
        Math_SmoothStepToF(&gCamDistortion, 0.0f, 0.2f, 0.002f, 0.0f);
    }
    Matrix_RotateZ(gGfxMatrix, gGameFrameCount * 10.0f * M_DTOR, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, 1.0f + gCamDistortion, 1.0f - gCamDistortion, 1.0f, MTXF_APPLY);
    Matrix_RotateZ(gGfxMatrix, -(f32) gGameFrameCount * 10.0f * M_DTOR, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, 1.0f + gCamDistortion, 1.0f - gCamDistortion, 1.0f, MTXF_APPLY);
    Matrix_Push(&gGfxMatrix);
    Camera_SetupLights(camPlayer);
    Lights_SetOneLight(&gMasterDisp, gLight1x, gLight1y, gLight1z, gLight1R, gLight1G, gLight1B, gAmbientR, gAmbientG,
                       gAmbientB);

    if (gLevelMode == LEVELMODE_ON_RAILS) {
        Matrix_RotateY(gCalcMatrix, camPlayer->yRot_114 * M_DTOR, MTXF_NEW);
        Matrix_RotateX(gCalcMatrix, camPlayer->xRot_120 * M_DTOR, MTXF_APPLY);

        tempVec.x = camPlayer->cam.eye.x - camPlayer->pos.x;
        tempVec.y = camPlayer->cam.eye.y - camPlayer->pos.y;
        tempVec.z = camPlayer->cam.eye.z - (camPlayer->trueZpos + camPlayer->zPath);

        Matrix_MultVec3f(gCalcMatrix, &tempVec, &gPlayCamEye);

        gPlayCamEye.x += camPlayer->pos.x;
        gPlayCamEye.y += camPlayer->pos.y;
        gPlayCamEye.z += camPlayer->trueZpos + camPlayer->zPath;

        tempVec.x = camPlayer->cam.at.x - camPlayer->pos.x;
        tempVec.y = camPlayer->cam.at.y - camPlayer->pos.y;
        tempVec.z = camPlayer->cam.at.z - (camPlayer->trueZpos + camPlayer->zPath);

        Matrix_MultVec3f(gCalcMatrix, &tempVec, &gPlayCamAt);

        gPlayCamAt.x += camPlayer->pos.x;
        gPlayCamAt.y += camPlayer->pos.y;
        gPlayCamAt.z += camPlayer->trueZpos + camPlayer->zPath;

        if (camPlayer->alternateView && (camPlayer->boostSpeed > 5.0f)) {
            gPlayCamAt.x += SIN_DEG(gGameFrameCount * 150.0f) * camPlayer->boostSpeed * 0.2f;
        }
    } else if (camPlayer->state_1C8 == PLAYERSTATE_1C8_LEVEL_COMPLETE) {
        Display_CsLevelCompleteHandleCamera(camPlayer);
    } else {
        gPlayCamEye.x = camPlayer->cam.eye.x;
        gPlayCamEye.y = camPlayer->cam.eye.y;
        gPlayCamEye.z = camPlayer->cam.eye.z;
        gPlayCamAt.x = camPlayer->cam.at.x;
        gPlayCamAt.y = camPlayer->cam.at.y;
        gPlayCamAt.z = camPlayer->cam.at.z;
    }
    camPlayer->camYaw = -Math_Atan2F(gPlayCamEye.x - gPlayCamAt.x, gPlayCamEye.z - gPlayCamAt.z);
    camPlayer->camPitch = -Math_Atan2F(gPlayCamEye.y - gPlayCamAt.y,
                                       sqrtf(SQ(gPlayCamEye.z - gPlayCamAt.z) + SQ(gPlayCamEye.x - gPlayCamAt.x)));
    Matrix_RotateY(gCalcMatrix, -camPlayer->camYaw, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, camPlayer->camPitch, MTXF_APPLY);
    Matrix_RotateZ(gCalcMatrix, -camPlayer->camRoll * M_DTOR, MTXF_APPLY);
    tempVec.x = 0.0f;
    tempVec.y = 100.0f;
    tempVec.z = 0.0f;
    Matrix_MultVec3f(gCalcMatrix, &tempVec, &playerCamUp);
    if (gStarCount != 0) {
        gStarfieldRoll = DEG_TO_RAD(gPlayer[0].camRoll);
        Camera_SetStarfieldPos(gPlayCamEye.x, gPlayCamEye.y, gPlayCamEye.z, gPlayCamAt.x, gPlayCamAt.y, gPlayCamAt.z);
        Background_DrawStarfield();
    }

    Background_DrawBackdrop();
    FrameInterpolation_RecordOpenChild("Sun", 0);
    FrameInterpolation_RecordMarker(__FILE__, __LINE__);
    Background_DrawSun();
    FrameInterpolation_RecordCloseChild();
    Matrix_Push(&gGfxMatrix);
    Matrix_LookAt(gGfxMatrix, gPlayCamEye.x, gPlayCamEye.y, gPlayCamEye.z, gPlayCamAt.x, gPlayCamAt.y, gPlayCamAt.z,
                  playerCamUp.x, playerCamUp.y, playerCamUp.z, MTXF_APPLY);

    if ((gLevelType == LEVELTYPE_PLANET) || (gCurrentLevel == LEVEL_BOLSE)) {
        if ((gCurrentLevel == LEVEL_TITANIA) &&
            ((gPlayer[0].state_1C8 != PLAYERSTATE_1C8_LEVEL_INTRO) || (gPlayer[0].unk_19C != 0))) {
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, 0.0f, gCameraShakeY, 0.0f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            Ground_801B58AC(&gMasterDisp, gPathGroundScroll);
            gPathGroundScroll = 0.0f;
            Matrix_Pop(&gGfxMatrix);
        } else if (gGroundSurface != SURFACE_WATER) {
            D_bg_8015F964 = false;
            FrameInterpolation_RecordOpenChild("Ground", 0);
            FrameInterpolation_RecordMarker(__FILE__, __LINE__);
            Background_DrawGround();
            FrameInterpolation_RecordCloseChild();
        }
    }

    Lights_SetOneLight(&gMasterDisp, gLight2x, gLight2y, gLight2z, gLight2R, gLight2G, gLight2B, gAmbientR, gAmbientG,
                       gAmbientB);

    for (i = 0, player = &gPlayer[0]; i < gCamCount; i++, player++) {
        playerPos.x = player->pos.x;
        playerPos.y = player->pos.y;
        playerPos.z = player->trueZpos;
        Display_SetSecondLight(&playerPos);
        FrameInterpolation_RecordOpenChild(player, i);
        Display_Player_Update(player, 0);
        FrameInterpolation_RecordCloseChild();
        Display_SetupPlayerSfxPos(player);
    }

    if ((gGroundSurface == SURFACE_WATER) && (gPlayer[0].state_1C8 != PLAYERSTATE_1C8_LEVEL_INTRO)) {
        Lights_SetOneLight(&gMasterDisp, gLight2x, -1 * gLight2y, gLight2z, gLight2R, gLight2G, gLight2B, gAmbientR,
                           gAmbientG, gAmbientB);
        Matrix_Push(&gGfxMatrix);
        Matrix_Scale(gGfxMatrix, 1.0f, -1.0f, 1.0f, MTXF_APPLY);
        for (i = 0, player = &gPlayer[0]; i < gCamCount; i++, player++) {
            playerPos.x = player->pos.x;
            playerPos.y = player->pos.y;
            playerPos.z = player->trueZpos;
            FrameInterpolation_RecordOpenChild(player, i);
            Display_Player_Update(player, 1);
            FrameInterpolation_RecordCloseChild();
        }
        Matrix_Pop(&gGfxMatrix);
    }

    Lights_SetOneLight(&gMasterDisp, gLight1x, gLight1y, gLight1z, gLight1R, gLight1G, gLight1B, gAmbientR, gAmbientG,
                       gAmbientB);
    Object_Draw(1);
    TexturedLine_Draw();
    gReflectY = 1;
    PlayerShot_DrawAll();
    if ((gGroundSurface == SURFACE_WATER) && (gPlayer[0].state_1C8 != PLAYERSTATE_1C8_LEVEL_INTRO)) {
        Matrix_Push(&gGfxMatrix);
        Matrix_Scale(gGfxMatrix, 1.0f, -1.0f, 1.0f, MTXF_APPLY);
        gReflectY = -1;
        PlayerShot_DrawAll();
        Matrix_Pop(&gGfxMatrix);
    }

    gReflectY = -1;

    if ((gGroundSurface == SURFACE_WATER) && (gPlayer[0].state_1C8 != PLAYERSTATE_1C8_LEVEL_INTRO)) {
        Matrix_Push(&gGfxMatrix);
        Matrix_Scale(gGfxMatrix, 1.0f, -1.0f, 1.0f, MTXF_APPLY);
        for (i = 0, player = &gPlayer[0]; i < gCamCount; i++, player++) {
            if (sPlayersVisible[i]) {
                Display_PlayerFeatures(player);
                Display_ArwingWingTrail_Update(player);
            }
            Matrix_Pop(&gGfxMatrix);
        }
    }

    if (gCurrentLevel == LEVEL_AQUAS) {
        Effect_Draw(0);
    }
    if ((gGroundSurface == SURFACE_WATER) || (gAqDrawMode != 0)) {
        D_bg_8015F964 = true;
        Effect_Draw(1);
        FrameInterpolation_RecordOpenChild("Ground", 0);
        FrameInterpolation_RecordMarker(__FILE__, __LINE__);
        Background_DrawGround();
        FrameInterpolation_RecordCloseChild();
    }

    if ((gCurrentLevel != LEVEL_AQUAS) &&
        (((gCurrentLevel != LEVEL_CORNERIA) && (gCurrentLevel != LEVEL_VENOM_ANDROSS)) ||
         ((gPlayer[0].state_1C8 != PLAYERSTATE_1C8_LEVEL_COMPLETE) &&
          (gPlayer[0].state_1C8 != PLAYERSTATE_1C8_LEVEL_INTRO)))) {
        Effect_Draw(0);
    }

    gReflectY = 1;

    for (i = 0, player = &gPlayer[0]; i < gCamCount; i++, player++) {
        if (sPlayersVisible[i]) {
            FrameInterpolation_RecordOpenChild(player, i);
            FrameInterpolation_RecordMarker(__FILE__, __LINE__);
            Display_PlayerShadow_Update(player);
            Display_PlayerFeatures(player);
            Display_ArwingWingTrail_Update(player);
            FrameInterpolation_RecordCloseChild();
        }
    }

    if ((gCurrentLevel == LEVEL_AQUAS) && (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_ACTIVE)) {
        Aquas_801AA20C();
    }

    if (((gCurrentLevel == LEVEL_CORNERIA) || (gCurrentLevel == LEVEL_VENOM_ANDROSS)) &&
        ((gPlayer[0].state_1C8 == PLAYERSTATE_1C8_LEVEL_COMPLETE) ||
         (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_LEVEL_INTRO))) {
        Effect_Draw(0);
    }

    BonusText_DrawAll();
    Matrix_Pop(&gGfxMatrix);
    Display_ActorMarks();
    Display_LockOnIndicator();

    if (sDrawCockpit) {
        Display_CockpitGlass();
    }

    for (i = 0, player = &gPlayer[0]; i < gCamCount; i++, player++) {
        if (sPlayersVisible[i]) {
            if (gShowReticles[i]) {
                Display_Reticle(player);
            }
            if (player->form == FORM_LANDMASTER) {
                Display_LandmasterMuzzleFlash(player);
            } else if (player->form == FORM_ON_FOOT) {
                Display_OnFootMuzzleFlash(player);
            }
        }
    }

    if ((gLevelMode == LEVELMODE_TURRET) && (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_ACTIVE)) {
        Turret_Draw(gPlayer);
    }

    Background_DrawLensFlare();

    if ((gCamCount != 1) &&
        ((camPlayer->state_1C8 == PLAYERSTATE_1C8_ACTIVE) || (camPlayer->state_1C8 == PLAYERSTATE_1C8_U_TURN))) {
        HUD_Draw();
        HUD_EdgeArrows_Update();
    }
    Matrix_Pop(&gGfxMatrix);
    Display_DrawHelpAlert();
    sPlayersVisible[gPlayerNum] = false;
    Matrix_Pop(&gGfxMatrix);

#if DEBUG_BOSS_KILLER == 1
    KillBoss();
#endif

    if (CVarGetInteger("gDebugSpeedControl", 0) == 1) {
        Player* player = gPlayer;
        static s32 prevSpeed;
        static bool debugFreeze = false;

        if (gControllerPress[0].button & L_JPAD) {
            player->baseSpeed -= 50;
        } else if (gControllerPress[0].button & R_JPAD) {
            player->baseSpeed += 50;
        }

        if ((!debugFreeze) && (gControllerPress[0].button & D_JPAD)) {
            prevSpeed = player->baseSpeed;
            player->baseSpeed = 0;
            debugFreeze = true;
        } else if ((debugFreeze) && (gControllerPress[0].button & D_JPAD)) {
            player->baseSpeed = prevSpeed;
            debugFreeze = false;
        }
    }

    if (CVarGetInteger("gDebugJumpToMap", 0) == 1) {
        Player* pl = &gPlayer[0];

        if ((gGameState != GSTATE_PLAY) || (gPlayState <= PLAY_INIT)) {
            return;
        }

        if ((gControllerHold[0].button & Z_TRIG) && (gControllerHold[0].button & R_TRIG) &&
            (gControllerPress[0].button & U_CBUTTONS)) {
            gFillScreenAlphaTarget = 255;
            gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
            gFillScreenAlphaStep = 8;
            gShowLevelClearStatusScreen = false;
            pl->state_1C8 = PLAYERSTATE_1C8_NEXT;
            pl->csTimer = 0;
            gFadeoutType = 4;
        }
    }

    if (CVarGetInteger("gDebugWarpZone", 0) == 1) {
        if ((gGameState != GSTATE_PLAY) || (gPlayState <= PLAY_INIT)) {
            return;
        }
        if (gControllerPress[0].button & L_TRIG) {
            if ((gCurrentLevel != LEVEL_SECTOR_X) && (gCurrentLevel != LEVEL_METEO)) {
                return;
            }
            if (gCurrentLevel == LEVEL_SECTOR_X) {
                gRingPassCount++;
                gPlayer[0].state_1C8 = PLAYERSTATE_1C8_ENTER_WARP_ZONE;
                gPlayer[0].csState = 0;
                gSceneSetup = 1;
                AUDIO_PLAY_SFX(NA_SE_WARP_HOLE, gDefaultSfxSource, 0);
                gMissionStatus = MISSION_WARP;
                gLeveLClearStatus[gCurrentLevel] = 1;
            } else {
                gPlayer[0].state_1C8 = PLAYERSTATE_1C8_ENTER_WARP_ZONE;
                gPlayer[0].csState = 0;
                AUDIO_PLAY_SFX(NA_SE_WARP_HOLE, gDefaultSfxSource, 0);
                gMissionStatus = MISSION_WARP;
                gLeveLClearStatus[gCurrentLevel] = 1;
            }
        }
    }

    if (CVarGetInteger("gDebugNoCollision", 0) == 1) {
        if ((gGameState != GSTATE_PLAY) || (gPlayState <= PLAY_INIT)) {
            return;
        }
        gPlayer->mercyTimer = 1000;
    }

    if (CVarGetInteger("gDebugLevelComplete", 0) == 1) {
        Player* pl = &gPlayer[0];
        if ((gGameState != GSTATE_PLAY) || (gPlayState <= PLAY_INIT)) {
            return;
        }

        if (gControllerPress[0].button & L_TRIG) {
            pl->state_1C8 = PLAYERSTATE_1C8_LEVEL_COMPLETE;
            gMissionStatus = MISSION_ACCOMPLISHED;
        }
    }

    if (CVarGetInteger("gDebugJumpToAllRange", 0) == 1) {
        Player* pl2 = &gPlayer[0];

        if ((gLevelMode != LEVELMODE_ALL_RANGE) && (gControllerPress[0].button & L_TRIG)) {
            pl2->state_1C8 = PLAYERSTATE_1C8_START_360;
        }
    }

    // Cheats start here

    if (CVarGetInteger("gInfiniteLives", 0) == 1) {
        if ((gGameState != GSTATE_PLAY) || (gPlayState <= PLAY_INIT)) {
            return;
        }
        gLifeCount[0] = 9;
    }

    if (CVarGetInteger("gInfiniteBombs", 0) == 1) {
        if ((gGameState != GSTATE_PLAY) || (gPlayState <= PLAY_INIT)) {
            return;
        }
        gBombCount[0] = 9;
    }

    if (CVarGetInteger("gHyperLaser", 0) == 1) {
        if ((gGameState != GSTATE_PLAY) || (gPlayState <= PLAY_INIT)) {
            return;
        }
        gLaserStrength[0] = 2;
    }

    if (CVarGetInteger("gScoreEditor", 0) == 1) {
        if ((gGameState != GSTATE_PLAY) || (gPlayState <= PLAY_INIT)) {
            return;
        }
        gHitCount = CVarGetInteger("gScoreEditValue", 1);

    }
    Hit64_Main();
    // ground testing
#if 0
    RCP_SetupDL(&gMasterDisp, SETUPDL_83);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);
    Graphics_DisplaySmallText(10, 210, 1.0f, 1.0f, "STICK_X:");
    Graphics_DisplaySmallNumber(60, 210, (int) ABS(gInputPress->stick_x));
    Graphics_DisplaySmallText(10, 220, 1.0f, 1.0f, "STICK_Y:");
    Graphics_DisplaySmallNumber(60, 220, (int) ABS(gInputPress->stick_y));
    if (gInputPress->stick_x < 0) Graphics_DisplaySmallText(110, 210, 1.0f, 1.0f, "NEG:");
    if (gInputPress->stick_y < 0) Graphics_DisplaySmallText(110, 220, 1.0f, 1.0f, "NEG:");
#endif
}
