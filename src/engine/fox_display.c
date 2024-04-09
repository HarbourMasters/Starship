#include "global.h"
#include "assets/ast_arwing.h"
#include "assets/ast_allies.h"
#include "assets/ast_landmaster.h"
#include "assets/ast_versus.h"
#include "assets/ast_sector_z.h"

Vec3f D_display_801613B0[4];
Vec3f D_display_801613E0[4];
s16 gReflectY;
Matrix D_display_80161418[4];
Vec3f D_display_80161518[4];
Vec3f D_display_80161548[4];
Vec3f D_display_80161578[4];
f32 D_display_801615A8[4];
f32 D_display_801615B8[4];

s32 D_display_800CA220 = 0;
u8 D_display_800CA224[] = { 0, 0, 0, 0 }; //
s32 D_display_800CA228 = 0;               //
s32 D_display_800CA22C = 0;               //
f32 D_display_800CA230 = 0.0f;
Actor* D_display_800CA234 = NULL;
s32 D_display_Timer_800CA238 = 0;
f32 D_display_800CA23C[3] = { 0.5f, 0.25f, 0.25f }; //
f32 D_display_800CA248[3] = { 2.0f, 1.0f, 0.5f };   //

void func_display_80051B30(void) {
    s32 sp7C;
    f32 sp78;
    f32 sp74;
    Vec3f sp68;
    Vec3f sp5C;

    if ((gPlayState == PLAY_PAUSE) || (D_display_800CA234 == NULL)) {
        return;
    }
    if ((D_display_800CA234->obj.status != OBJ_ACTIVE) || (gPlayer[0].state_1C8 != PLAYERSTATE_1C8_3)) {
        D_display_800CA234 = NULL;
        D_display_Timer_800CA238 = 0;
        return;
    }
    if (D_display_Timer_800CA238 != 0) {
        D_display_Timer_800CA238--;
        if (D_display_Timer_800CA238 == 0) {
            D_display_800CA234 = NULL;
            return;
        }
    }
    if (!(D_display_Timer_800CA238 & 4)) {
        Matrix_RotateY(gCalcMatrix, gPlayer[0].unk_058, 0);
        Matrix_RotateX(gCalcMatrix, gPlayer[0].unk_05C, 1);
        sp68.x = D_display_800CA234->obj.pos.x - gPlayer[0].camEye.x;
        sp68.y = D_display_800CA234->obj.pos.y - gPlayer[0].camEye.y;
        sp68.z = D_display_800CA234->obj.pos.z + D_ctx_80177D20 - gPlayer[0].camEye.z;
        Matrix_MultVec3f(gCalcMatrix, &sp68, &sp5C);
        sp7C = 0;
        if ((sp5C.z < 0.0f) && (sp5C.z > -12000.0f) && (fabsf(sp5C.x) < fabsf(sp5C.z * 0.4f))) {
            sp7C = 1;
        }
        RCP_SetupDL(&gMasterDisp, 0xC);
        switch (D_display_800CA234->aiType) {
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
        switch (sp7C) {
            case 0:
                if (D_display_800CA234->sfxSource[0] > 0.0f) {
                    sp78 = 20.0f;
                    sp74 = M_PI / 2;
                } else {
                    sp78 = -20.0f;
                    sp74 = -M_PI / 2;
                }
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, sp78, 0.0f, -50.0f, 1);
                Matrix_RotateZ(gGfxMatrix, sp74, 1);
                Matrix_Scale(gGfxMatrix, 0.03f, 0.03f, 0.03f, 1);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_1023700);
                Matrix_Pop(&gGfxMatrix);
                break;
            case 1:
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, 20.0f, 0.0f, -50.0f, 1);
                Matrix_RotateZ(gGfxMatrix, -M_PI / 2, 1);
                Matrix_Scale(gGfxMatrix, 0.03f, 0.03f, 0.03f, 1);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_1023700);
                Matrix_Pop(&gGfxMatrix);
                sp78 = -20.0f;
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, -20.0f, 0.0f, -50.0f, 1);
                Matrix_RotateZ(gGfxMatrix, M_PI / 2, 1);
                Matrix_Scale(gGfxMatrix, 0.03f, 0.03f, 0.03f, 1);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_1023700);
                Matrix_Pop(&gGfxMatrix);
                break;
        }
        switch (sp7C) {
            case 0:
                RCP_SetupDL(&gMasterDisp, 0x4C);
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 0, 255);
                if (sp78 < 0.0f) {
                    Graphics_DisplaySmallText(43 - 19, 106, 1.0f, 1.0f, "HELP!!");
                } else {
                    Graphics_DisplaySmallText(SCREEN_WIDTH - 43 - 19, 106, 1.0f, 1.0f, "HELP!!");
                }
                break;
            case 1:
                RCP_SetupDL(&gMasterDisp, 0x4C);
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 0, 255);
                Graphics_DisplaySmallText(43 - 19, 106, 1.0f, 1.0f, "HELP!!");
                Graphics_DisplaySmallText(SCREEN_WIDTH - 43 - 19, 106, 1.0f, 1.0f, "HELP!!");
                break;
        }
    }
}

bool func_display_800520FC(s32 limbIndex, Gfx** gfxPtr, Vec3f* pos, Vec3f* rot, void* data) {
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

void func_display_800523A8(s32 limbIndex, Vec3f* rot, void* data) {
    Vec3f sp1C;
    Player* player = (Player*) data;

    if (limbIndex == 11) {
        sp1C.x = 3.0f;
        sp1C.y = 1.0f;
        sp1C.z = -28.0f;
        Matrix_MultVec3f(gGfxMatrix, &sp1C, &D_display_801613B0[player->num]);
    }
}

void func_display_80052420(s32 limbIndex, Vec3f* rot, void* data) {
    Vec3f sp1C;
    Player* player = (Player*) data;

    if (limbIndex == 16) {
        sp1C.x = 13.0f;
        sp1C.y = 2.0f;
        sp1C.z = 28.0f;
        Matrix_MultVec3f(gGfxMatrix, &sp1C, &D_display_801613B0[player->num]);
    }
}

void func_display_80052498(s32 limbIndex, Vec3f* rot, void* data) {
    Vec3f sp1C;
    Player* player = (Player*) data;

    if (limbIndex == 11) {
        sp1C.x = 0.0f;
        sp1C.y = 2.0f;
        sp1C.z = 29.0f;
        Matrix_MultVec3f(gGfxMatrix, &sp1C, &D_display_801613B0[player->num]);
    }
}

void func_display_8005250C(s32 limbIndex, Vec3f* rot, void* data) {
    Vec3f sp1C;
    Player* player = (Player*) data;

    if (limbIndex == 11) {
        sp1C.x = 19.0f;
        sp1C.y = 1.0f;
        sp1C.z = 32.0f;
        Matrix_MultVec3f(gGfxMatrix, &sp1C, &D_display_801613B0[player->num]);
    }
}

void func_display_80052584(Player* player) {
    Matrix_Push(&gGfxMatrix);
    Matrix_Copy(gGfxMatrix, &gIdentityMatrix);
    if ((player->state_1C8 == PLAYERSTATE_1C8_3) && (player->timer_1F8 != 0)) {
        Matrix_Translate(gGfxMatrix, D_display_801613B0[player->num].x, D_display_801613B0[player->num].y,
                         D_display_801613B0[player->num].z, 1);
        Matrix_Scale(gGfxMatrix, D_display_800CA23C[player->timer_1F8 - 1], D_display_800CA23C[player->timer_1F8 - 1],
                     D_display_800CA23C[player->timer_1F8 - 1], 1);
        Matrix_SetGfxMtx(&gMasterDisp);
        RCP_SetupDL_40();
        gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
        gSPDisplayList(gMasterDisp++, D_versus_302D240);
    }
    Matrix_Pop(&gGfxMatrix);
}

void func_display_800526B8(Player* player) {
    Matrix_Push(&gGfxMatrix);
    Matrix_Scale(gCalcMatrix, 0.5f, 0.5f, 0.5f, 1);
    Matrix_Translate(gCalcMatrix, 0.0f, 35.0f, 0.0f, 1);
    switch (player->num) {
        case 0:
            Animation_DrawSkeleton(5, D_versus_301D258, player->jointTable, func_display_800520FC,
                                   func_display_800523A8, player, gCalcMatrix);
            break;
        case 1:
            Animation_DrawSkeleton(5, D_versus_301DB94, player->jointTable, func_display_800520FC,
                                   func_display_80052420, player, gCalcMatrix);
            break;
        case 2:
            Animation_DrawSkeleton(5, D_versus_301E3E8, player->jointTable, func_display_800520FC,
                                   func_display_80052498, player, gCalcMatrix);
            break;
        case 3:
            Animation_DrawSkeleton(5, D_versus_301C614, player->jointTable, func_display_800520FC,
                                   func_display_8005250C, player, gCalcMatrix);
            break;
    }
    Matrix_Pop(&gGfxMatrix);
    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
}

void func_display_80052884(Player* player) {
    f32 sp64;
    Vec3f sp58;
    Vec3f sp4C = { 0.0f, 0.0f, 90.0f };
    Vec3f sp40 = { 0.0f, 40.0f, -70.0f };

    Matrix_Push(&gGfxMatrix);
    if (!gVersusMode) {
        gSPDisplayList(gMasterDisp++, D_landmaster_3000090);
    } else {
        gSPDisplayList(gMasterDisp++, D_versus_300FB80);
    }
    Matrix_MultVec3f(gGfxMatrix, &sp40, &D_display_80161518[player->num]);
    Matrix_Translate(gGfxMatrix, 0.0f, 51.0f, -10.0f, 1);
    Matrix_RotateY(gGfxMatrix, -player->unk_180 * M_DTOR, 1);
    Matrix_RotateX(gGfxMatrix, player->unk_17C * M_DTOR, 1);
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
        gSPDisplayList(gMasterDisp++, D_landmaster_3004680);
    } else {
        gSPDisplayList(gMasterDisp++, D_versus_301F140);
    }
    Matrix_MultVec3f(gGfxMatrix, &sp4C, &D_display_80161548[player->num]);
    Matrix_Pop(&gGfxMatrix);
}

Gfx* D_display_800CA26C[] = { D_arwing_3000090, D_arwing_3016CC0, D_arwing_3005AB0, D_arwing_3003CE0 };
Gfx* D_display_800CA27C[] = { D_arwing_3001C90, D_arwing_3016CC0, D_arwing_3005AB0, D_arwing_3003CE0 };
f32 D_display_800CA28C = 2.0f;
f32 D_display_800CA290 = 13.0f;
f32 D_display_800CA294 = -10.0f;
f32 D_display_800CA298[] = { 0.0f, 0.0f, 0.0f, 0.0f };
f32 D_display_800CA2A8 = 0.0f;

void func_display_80052B80(Player* player) {
    Matrix_Push(&gGfxMatrix);
    if ((player->state_1C8 == PLAYERSTATE_1C8_3) && (player->unk_1A0 != 0)) {
        Matrix_Translate(gGfxMatrix, D_display_80161548[player->num].x, D_display_80161548[player->num].y,
                         D_display_80161548[player->num].z, 1);
        Matrix_Scale(gGfxMatrix, D_display_800CA248[player->unk_1A0 - 1], D_display_800CA248[player->unk_1A0 - 1],
                     D_display_800CA248[player->unk_1A0 - 1], 1);
        Matrix_SetGfxMtx(&gMasterDisp);
        if (gVersusMode) {
            RCP_SetupDL_40();
            gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
            gSPDisplayList(gMasterDisp++, D_versus_301FD20);
        } else {
            Matrix_Scale(gGfxMatrix, 0.5f, 0.5f, 0.5f, 1);
            Matrix_SetGfxMtx(&gMasterDisp);
            RCP_SetupDL(&gMasterDisp, 0x43);
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
            gDPSetEnvColor(gMasterDisp++, 0, 255, 0, 255);
            gSPDisplayList(gMasterDisp++, D_1024AC0);
        }
    }
    Matrix_Pop(&gGfxMatrix);
}

void func_display_80052D48(Player* player) {
    f32 sp2C;

    Matrix_Push(&gGfxMatrix);
    Matrix_Copy(gGfxMatrix, &D_display_80161418[player->num]);
    if (gVersusMode) {
        RCP_SetupDL_64();
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 150);
    } else {
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 192);
        gDPSetEnvColor(gMasterDisp++, 255, 0, 0, 192);
        RCP_SetupDL(&gMasterDisp, 0x43);
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
        Matrix_Translate(gGfxMatrix, 20.0f, 30.0f, -10.0f, 1);
        if (!gVersusMode) {
            Matrix_RotateY(gGfxMatrix, -gPlayer[gPlayerNum].unk_058, 1);
        }
        Matrix_Scale(gGfxMatrix, sp2C, sp2C, sp2C, 1);
        Matrix_Translate(gGfxMatrix, 0.0f, -30.0f, 0.0f, 1);
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
        Matrix_Translate(gGfxMatrix, -20.0f, 30.0f, -10.0f, 1);
        if (!gVersusMode) {
            Matrix_RotateY(gGfxMatrix, -gPlayer[gPlayerNum].unk_058, 1);
        }
        Matrix_Scale(gGfxMatrix, sp2C, sp2C, sp2C, 1);
        Matrix_Translate(gGfxMatrix, 0.0f, -30.0f, 0.0f, 1);
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

void func_display_8005314C(void) {
    if (gReflectY != 0) {
        gSPSetGeometryMode(gMasterDisp++, G_CULL_FRONT);
        gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
    }
}

bool func_display_800531A4(s32 limbIndex, Gfx** gfxPtr, Vec3f* pos, Vec3f* rot, void* wingData) {
    WingInfo* wings = (WingInfo*) wingData;

    if ((D_display_800CA22C != 0) && (gPlayer[0].unk_200 == 0)) {
        RCP_SetupDL(&gMasterDisp, 0x1D);
        func_display_8005314C();
    }
    switch (limbIndex) {
        case 13:
            if (wings->rightState == WINGSTATE_NONE) {
                *gfxPtr = NULL;
            }
            if (wings->rightState == WINGSTATE_BROKEN) {
                *gfxPtr = D_arwing_3015120;
            }
            if ((D_display_800CA22C != 0) && ((D_ctx_80177D40[0] % 2) != 0)) {
                RCP_SetupDL(&gMasterDisp, 0x22);
                func_display_8005314C();
                if (D_ctx_80177D40[0] > 1000) {
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 32, 32, 255, 255);
                } else {
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
                }
            }
            break;
        case 1:
        case 2:
            if (wings->rightState != 2) {
                *gfxPtr = NULL;
            }
            if ((D_display_800CA22C != 0) && ((D_ctx_80177D40[0] % 2) != 0)) {
                RCP_SetupDL(&gMasterDisp, 0x22);
                func_display_8005314C();
                if (D_ctx_80177D40[0] > 1000) {
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 32, 32, 255, 255);
                } else {
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
                }
            }
            break;
        case 12:
            if (wings->rightState == WINGSTATE_NONE) { // should be leftState?
                *gfxPtr = NULL;
            }
            if (wings->leftState == WINGSTATE_BROKEN) {
                *gfxPtr = D_arwing_3014BF0;
            }
            if ((D_display_800CA22C != 0) && ((D_ctx_80177D58[0] % 2) != 0)) {
                RCP_SetupDL(&gMasterDisp, 0x22);
                func_display_8005314C();
                if (D_ctx_80177D58[0] > 1000) {
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 32, 32, 255, 255);
                } else {
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
                }
            }
            break;
        case 5:
        case 6:
            if (wings->leftState != 2) {
                *gfxPtr = NULL;
            }
            if ((D_display_800CA22C != 0) && ((D_ctx_80177D58[0] % 2) != 0)) {
                RCP_SetupDL(&gMasterDisp, 0x22);
                func_display_8005314C();
                if (D_ctx_80177D58[0] > 1000) {
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 32, 32, 255, 255);
                } else {
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
                }
            }
            break;
    }
    switch (limbIndex) {
        case 1:
            rot->y -= wings->unk_04;
            break;
        case 2:
            rot->y -= wings->unk_08;
            break;
        case 5:
            rot->y -= wings->unk_10;
            break;
        case 6:
            rot->y -= wings->unk_0C;
            break;
        case 12:
            rot->z += wings->unk_20;
            break;
        case 13:
            rot->z += wings->unk_20;
            break;
        case 4:
            pos->z -= wings->unk_14;
            pos->x += wings->unk_18;
            break;
        case 8:
            pos->z += wings->unk_14;
            pos->x += wings->unk_18;
            break;
    }
    return false;
}

void func_display_80053658(WingInfo* wings) {
    Vec3f sp68[30];
    s32 sp64;

    Matrix_Push(&gGfxMatrix);
    wings->unk_18 = 0.0f;
    if (wings->unk_14 < -7.0f) {
        wings->unk_18 = (-wings->unk_14 - 7.0f) * 2.5f;
    }
    if (gGameState == GSTATE_PLAY) {
        Animation_DrawSkeleton(1, D_arwing_3016610, gPlayer[0].jointTable, func_display_800531A4, NULL, wings,
                               &gIdentityMatrix);
    } else {
        if (gGameState == GSTATE_MENU) {
            Animation_GetFrameData(&D_arwing_3015AF4, 0, sp68);
        } else {
            Animation_GetFrameData(&D_arwing_3015C28, 0, sp68);
        }
        Animation_DrawSkeleton(1, D_arwing_3016610, sp68, func_display_800531A4, NULL, wings, &gIdentityMatrix);
    }
    D_display_800CA22C = 0;
    sp64 = wings->unk_2C;
    if (D_display_800CA220 != 0) {
        sp64 = 1;
    }
    if (sp64 != 0) {
        Matrix_Push(&gGfxMatrix);
        Matrix_Translate(gGfxMatrix, 0.0f, 6.4f, -16.5f, 1);
        Matrix_RotateY(gGfxMatrix, wings->unk_34 * M_DTOR, 1);
        Matrix_RotateX(gGfxMatrix, wings->unk_30 * M_DTOR, 1);
        Matrix_Scale(gGfxMatrix, 1.0f / 70.925f, 1.0f / 70.925f, 1.0f / 70.925f, 1);
        if (gGameState == GSTATE_ENDING) {
            Matrix_Scale(gGfxMatrix, 0.95f, 0.95f, 0.95f, 1);
        }
        Matrix_SetGfxMtx(&gMasterDisp);
        if (gExpertMode) {
            gSPDisplayList(gMasterDisp++, D_display_800CA27C[sp64 - 1]);
        } else {
            gSPDisplayList(gMasterDisp++, D_display_800CA26C[sp64 - 1]);
        }
        Matrix_Pop(&gGfxMatrix);
    }
    Matrix_Translate(gGfxMatrix, 0.0f, 17.2f, -25.8f, 1);
    Matrix_RotateX(gGfxMatrix, wings->unk_38 * M_DTOR, 1);
    Matrix_SetGfxMtx(&gMasterDisp);
    RCP_SetupDL_64_2();
    if ((gGameState == GSTATE_PLAY) && (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_2) &&
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
}

void func_display_80053B00(f32 arg0, f32 arg1, UNK_TYPE arg2, UNK_TYPE arg3) {
}

void func_display_80053B18(void) {
    Matrix_Push(&gGfxMatrix);
    Matrix_Copy(gGfxMatrix, &D_display_80161418[0]);
    Matrix_Translate(gGfxMatrix, 0.0f, D_display_800CA290, D_display_800CA294, 1);
    Matrix_Scale(gGfxMatrix, D_display_800CA28C, D_display_800CA28C, D_display_800CA28C, 1);
    Matrix_SetGfxMtx(&gMasterDisp);
    RCP_SetupDL_64_2();
    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 120);
    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
    gSPDisplayList(gMasterDisp++, D_arwing_30194E0);
    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
    Matrix_Pop(&gGfxMatrix);
}

void func_display_80053C38(Player* player, s32 arg1) {
    Vec3f sp4C;
    f32 sp48;

    if ((gPlayerNum == player->num) && (arg1 == 0)) {
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
    if ((player->cockpitView != 0) && (gLevelMode == LEVELMODE_ON_RAILS) &&
        (fabsf(player->unk_138 + D_ctx_80177D20 - player->camEye.z) < 10.0f)) {
        if (arg1 == 0) {
            D_display_800CA228 = 1;
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, 0.0f, -8.0f, 5.0f, 1);
            Matrix_RotateY(gGfxMatrix, M_PI, 1);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_arwing_30131F0);
            Matrix_Pop(&gGfxMatrix);
        }
    } else {
        if (gVersusMode) {
            if ((player->wings.rightState == WINGSTATE_INTACT) && (player->wings.leftState == WINGSTATE_INTACT)) {
                gSPDisplayList(gMasterDisp++, D_versus_300EE80);
            } else if ((player->wings.rightState <= WINGSTATE_BROKEN) &&
                       (player->wings.leftState == WINGSTATE_INTACT)) {
                gSPDisplayList(gMasterDisp++, D_versus_3010A90);
            } else if ((player->wings.rightState == WINGSTATE_INTACT) &&
                       (player->wings.leftState <= WINGSTATE_BROKEN)) {
                gSPDisplayList(gMasterDisp++, D_versus_3011470);
            } else {
                gSPDisplayList(gMasterDisp++, D_versus_300D550);
            }
        } else {
            if ((gLevelType == LEVELTYPE_SPACE) || (gCurrentLevel == LEVEL_BOLSE)) {
                player->wings.unk_28 = player->wings.unk_04 = player->wings.unk_08 = player->wings.unk_0C =
                    player->wings.unk_10 = 0.0f;
            }
            D_display_800CA22C = 1;
            gReflectY = arg1;
            func_display_80053658(&player->wings);
        }
    }
}

void func_display_80053F7C(Player* player) {
    Vec3f* pad;
    s32 i;

    if ((gPlayerNum == player->num) && ((player->form == FORM_ARWING) || (player->form == FORM_LANDMASTER)) &&
        (player->unk_234 != 0) &&
        (((gGameState == GSTATE_PLAY) && (player->state_1C8 == PLAYERSTATE_1C8_3)) || (gGameState == GSTATE_MENU))) {
        for (i = 0; i < 2; i++) {
            pad = &D_display_801613E0[i];
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, pad->x, pad->y, pad->z, 1);
            if (gChargeTimers[player->num] >= 20) {
                RCP_SetupDL(&gMasterDisp, 0x3F);
                if (i == 1) {
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
                    gDPSetEnvColor(gMasterDisp++, 255, 0, 0, 255);
                    Math_SmoothStepToF(&D_display_800CA298[player->num], 2.0f, 1.0f, 0.4f, 0.0f);
                } else {
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 0, 255);
                    gDPSetEnvColor(gMasterDisp++, 255, 255, 0, 255);
                }
            } else {
                RCP_SetupDL_36();
            }
            if (i == 1) {
                Matrix_Scale(gGfxMatrix, D_display_800CA298[player->num], D_display_800CA298[player->num], 1.0f, 1);
                Math_SmoothStepToF(&D_display_800CA298[player->num], 1.0f, 1.0f, 0.2f, 0.0f);
            }
            Matrix_Scale(gGfxMatrix, 4.0f, 4.0f, 4.0f, 1);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_1024F60);
            Matrix_Pop(&gGfxMatrix);
        }
    }
}

void func_display_80054280(Player* player, s32 arg1) {
    switch (player->form) {
        case FORM_ARWING:
            func_display_80053C38(player, arg1);
            return;
        case FORM_LANDMASTER:
            func_display_80052884(player);
            return;
        case FORM_BLUE_MARINE:
            Aquas_801ACBB4(player);
            return;
        case FORM_ON_FOOT:
            func_display_800526B8(player);
            return;
    }
}

void func_display_80054300(Player* player) {
    Math_SmoothStepToF(&D_display_800CA2A8, player->unk_23C, 1.0f, 10.0f, 0.0f);
    RCP_SetupDL(&gMasterDisp, 0x42);
    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 0, 0, 0, (s32) D_display_800CA2A8);
    if (player->unk_068 > 30.0f) {
        gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
    }
    if ((gGroundType == GROUNDTYPE_WATER) && (player->unk_068 < 10.0f)) {
        player->unk_23C = 90;
    } else {
        player->unk_23C = 180;
    }
    switch (player->form) {
        case FORM_ARWING:
        fake_label:
            Matrix_Scale(gGfxMatrix, 2.5049999f, 1.5f, 2.5049999f, 1);
            Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, 30.0f, 1);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_1032780);
            break;
        case FORM_LANDMASTER:
            Matrix_Push(&gGfxMatrix);
            Matrix_Scale(gGfxMatrix, 1.17f, 1.17f, 1.17f, 1);
            Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, 20.0f, 1);
            Matrix_SetGfxMtx(&gMasterDisp);
            if (gCurrentLevel == LEVEL_MACBETH) {
                RCP_SetupDL(&gMasterDisp, 0x41);
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
            Matrix_Scale(gGfxMatrix, 0.5f, 0.5f, 0.5f, 1);
            Matrix_RotateX(gGfxMatrix, M_PI / 2, 1);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
            gSPDisplayList(gMasterDisp++, D_102A8A0);
            gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
            Matrix_Pop(&gGfxMatrix);
            break;
    }
}

void func_display_8005465C(s32 levelType) {
    RCP_SetupDL(&gMasterDisp, 0x43);
    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);

    switch (levelType) {
        case LEVELTYPE_PLANET:
            gDPSetEnvColor(gMasterDisp++, 255, 0, 0, 255);
            break;
        case LEVELTYPE_SPACE:
            gDPSetEnvColor(gMasterDisp++, 0, 0, 255, 255);
            break;
        case LEVELTYPE_UNK2:
            gDPSetEnvColor(gMasterDisp++, 0, 255, 0, 255);
            break;
        case LEVELTYPE_UNK3:
            gDPSetEnvColor(gMasterDisp++, 255, 64, 0, 255);
            break;
    }
    gSPDisplayList(gMasterDisp++, D_1024AC0);
}

void func_display_8005478C(Player* player) {
    RCP_SetupDL_64();
    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 100);
    Matrix_Push(&gGfxMatrix);
    Matrix_RotateZ(gGfxMatrix, player->unk_0F8 * M_DTOR, 1);
    if (player->form == FORM_LANDMASTER) {
        if (player->unk_194 <= 0.0f) {
            Matrix_Pop(&gGfxMatrix);
            return;
        }
        Matrix_Scale(gGfxMatrix, player->unk_194, player->unk_194, 1.0f, 1);
    } else {
        Matrix_Scale(gGfxMatrix, player->unk_194, player->unk_194, 1.0f, 1);
    }
    if ((gGameFrameCount % 2) != 0) {
        Matrix_Scale(gGfxMatrix, 0.9f, 0.63f, 1.0f, 1);
    } else {
        Matrix_Scale(gGfxMatrix, 0.80999994f, 0.567f, 1.0f, 1);
    }
    Matrix_SetGfxMtx(&gMasterDisp);
    func_display_8005465C(gLevelType);
    Matrix_Pop(&gGfxMatrix);
}

void func_display_80054914(Player* player) {
    f32 sp4C;
    Vec3f sp40;
    Vec3f sp34;

    if (player->unk_280 != 0) {
        Matrix_RotateY(gCalcMatrix, (player->unk_114 + player->unk_0E8 + player->unk_134 + 180.0f) * M_DTOR, 0);
        Matrix_RotateX(gCalcMatrix, -((player->unk_120 + player->unk_0E4 + player->unk_134 + player->unk_4D8) * M_DTOR),
                       1);
        Matrix_RotateZ(gCalcMatrix, -((player->unk_0F8 + player->unk_0F0 + player->unk_134) * M_DTOR), 1);
        Matrix_Translate(gCalcMatrix, player->unk_084, player->unk_080, 0.0f, 1);
        sp40.x = 0.0f;
        sp40.y = 0.0f;
        sp40.z = -30.0f;
        Matrix_MultVec3f(gCalcMatrix, &sp40, &sp34);
        sp4C = 1.0f;
        if (player->unk_1F0 < 0) {
            sp4C = -1.0f;
        }
        Matrix_Push(&gGfxMatrix);
        Matrix_Translate(gGfxMatrix, player->pos.x + sp34.x, player->pos.y + sp34.y,
                         player->unk_138 + player->unk_144 + sp34.z, 1);
        Matrix_RotateY(gGfxMatrix, -gPlayer[gPlayerNum].unk_058, 1);
        Matrix_RotateX(gGfxMatrix, gPlayer[gPlayerNum].unk_05C, 1);
        Matrix_RotateZ(gGfxMatrix, gGameFrameCount * 20.0f * sp4C * M_DTOR, 1);
        if (player->form == FORM_ARWING) {
            Matrix_Scale(gGfxMatrix, 2.0f, 2.0f, 2.0f, 1);
        } else {
            Matrix_Scale(gGfxMatrix, 1.2f, 1.2f, 1.2f, 1);
        }
        if (player->unk_1F0 < 0) {
            Matrix_RotateX(gGfxMatrix, M_PI, 1);
        }
        Matrix_SetGfxMtx(&gMasterDisp);
        RCP_SetupDL(&gMasterDisp, 0x43);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, player->unk_280);
        gDPSetEnvColor(gMasterDisp++, 0, 0, 160, player->unk_280);
        gSPDisplayList(gMasterDisp++, D_101DC10);
        Matrix_Pop(&gGfxMatrix);
    }
}

void func_display_80054CA4(Player* player) {
    if (D_ctx_80177AB8[player->num] > 1.0f) {
        Matrix_Push(&gGfxMatrix);
        Matrix_Copy(gGfxMatrix, &D_display_80161418[player->num]);
        Matrix_Translate(gGfxMatrix, 0.0f, -5.0f, 10.0f, 1);
        Matrix_Scale(gGfxMatrix, 2.5f, 1.6f, 2.5f, 1);
        Matrix_SetGfxMtx(&gMasterDisp);
        RCP_SetupDL(&gMasterDisp, 0x44);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 0, 255, 255, (s32) D_ctx_80177AB8[player->num]);
        gDPSetEnvColor(gMasterDisp++, 255, 0, 255, (s32) D_ctx_80177AB8[player->num]);
        gSPDisplayList(gMasterDisp++, D_101CD70);
        Matrix_Pop(&gGfxMatrix);
        Texture_Scroll(D_101D070, 32, 32, 3);
        Texture_Scroll(D_101D070, 32, 32, 3);
    }
}

void func_display_80054E80(Player* player) {
    Vec3f spC4 = { 0.0f, -5.0f, 60.0f };
    Vec3f spB8 = { 0.0f, -14.0f, 60.0f };
    Vec3f spAC = { 30.0f, -10.0f, 30.0f };
    Vec3f spA0 = { -30.0f, -10.0f, 30.0f };
    Vec3f sp94;
    Vec3f sp88;
    u8 var_v1;
    f32 sp80;

    if (gChargeTimers[player->num] > 10) {
        RCP_SetupDL(&gMasterDisp, 0x43);
        Matrix_Copy(gCalcMatrix, &D_display_80161418[player->num]);
        if ((player->cockpitView != 0) && (gLevelMode == LEVELMODE_ON_RAILS)) {
            Matrix_MultVec3f(gCalcMatrix, &spB8, &sp94);
        } else {
            Matrix_MultVec3f(gCalcMatrix, &spC4, &sp94);
        }
        Matrix_Push(&gGfxMatrix);
        sp80 = gChargeTimers[player->num] / 20.0f;
        Matrix_Translate(gGfxMatrix, sp94.x, sp94.y, sp94.z, 0);
        Matrix_Scale(gGfxMatrix, sp80, sp80, 1.0f, 1);
        Matrix_Push(&gGfxMatrix);
        if ((player->cockpitView != 0) && (gLevelMode == LEVELMODE_ON_RAILS)) {
            Matrix_Scale(gGfxMatrix, 3.0f, 3.0f, 3.0f, 1);
        } else {
            Matrix_Scale(gGfxMatrix, 10.0f, 10.0f, 10.0f, 1);
        }
        RCP_SetupDL(&gMasterDisp, 0x31);
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
        Matrix_RotateZ(gGfxMatrix, gGameFrameCount * 53.0f * M_DTOR, 1);
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, D_101C2E0);
        Matrix_RotateZ(gGfxMatrix, gGameFrameCount * -53.0f * 2.0f * M_DTOR, 1);
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, D_101C2E0);
        Matrix_Pop(&gGfxMatrix);
        if ((player->cockpitView != 0) && (gLevelMode == LEVELMODE_ON_RAILS)) {
            Matrix_Scale(gGfxMatrix, 0.3f, 0.3f, 0.3f, 1);
        }
        Matrix_Scale(gGfxMatrix, 0.5f, 0.5f, 1.0f, 1);
        if (((gGameFrameCount % 2) == 0)) {
            Matrix_Scale(gGfxMatrix, 1.7f, 1.7f, 1.0f, 1);
        } else {
            Matrix_Scale(gGfxMatrix, 1.3f, 1.3f, 1.0f, 1);
        }
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, D_1024AC0);
        Matrix_Pop(&gGfxMatrix);
    }
    if (D_ctx_80177AA0[player->num] > 0.1f) {
        Matrix_Push(&gGfxMatrix);
        RCP_SetupDL(&gMasterDisp, 0x43);
        Matrix_Copy(gCalcMatrix, &D_display_80161418[player->num]);
        var_v1 = gLaserStrength[player->num];
        if (player->wings.unk_14 > -8.0f) {
            var_v1 = LASERS_SINGLE;
        }
        switch (var_v1) {
            case LASERS_SINGLE:
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 192, 255, 192, 128);
                gDPSetEnvColor(gMasterDisp++, 64, 255, 64, 128);
                if ((player->cockpitView != 0) && (gLevelMode == LEVELMODE_ON_RAILS)) {
                    Matrix_MultVec3f(gCalcMatrix, &spB8, &sp94);
                } else {
                    Matrix_MultVec3f(gCalcMatrix, &spC4, &sp94);
                }
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, sp94.x, sp94.y, sp94.z, 0);
                Matrix_Scale(gGfxMatrix, D_ctx_80177AA0[player->num], D_ctx_80177AA0[player->num], 1.0f, 1);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_1024AC0);
                Matrix_Pop(&gGfxMatrix);
                break;
            case LASERS_TWIN:
            case LASERS_HYPER:
                if (var_v1 == LASERS_TWIN) {
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 192, 255, 192, 128);
                    gDPSetEnvColor(gMasterDisp++, 64, 255, 64, 128);
                } else {
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 128, 255, 255, 160);
                    gDPSetEnvColor(gMasterDisp++, 128, 128, 255, 160);
                }
                Matrix_MultVec3f(gCalcMatrix, &spAC, &sp94);
                Matrix_MultVec3f(gCalcMatrix, &spA0, &sp88);
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, sp94.x, sp94.y, sp94.z, 0);
                Matrix_Scale(gGfxMatrix, D_ctx_80177AA0[player->num], D_ctx_80177AA0[player->num], 1.0f, 1);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_1024AC0);
                Matrix_Pop(&gGfxMatrix);
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, sp88.x, sp88.y, sp88.z, 0);
                Matrix_Scale(gGfxMatrix, D_ctx_80177AA0[player->num], D_ctx_80177AA0[player->num], 1.0f, 1);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_1024AC0);
                Matrix_Pop(&gGfxMatrix);
                break;
        }
        Matrix_Pop(&gGfxMatrix);
    }
}

void func_display_80055788(Player* player) {
    f32 sp54;

    if (gChargeTimers[player->num] > 10) {
        RCP_SetupDL(&gMasterDisp, 0x43);
        Matrix_Push(&gGfxMatrix);
        sp54 = gChargeTimers[player->num] / 20.0f;
        Matrix_Translate(gGfxMatrix, D_display_80161548[player->num].x, D_display_80161548[player->num].y,
                         D_display_80161548[player->num].z, 0);
        Matrix_Scale(gGfxMatrix, sp54, sp54, 1.0f, 1);
        Matrix_Push(&gGfxMatrix);
        Matrix_Scale(gGfxMatrix, 10.0f, 10.0f, 10.0f, 1);
        RCP_SetupDL(&gMasterDisp, 0x31);
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
        Matrix_RotateZ(gGfxMatrix, gGameFrameCount * 53.0f * M_DTOR, 1);
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, D_101C2E0);
        Matrix_RotateZ(gGfxMatrix, gGameFrameCount * -53.0f * 2.0f * M_DTOR, 1);
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, D_101C2E0);
        Matrix_Pop(&gGfxMatrix);
        Matrix_Scale(gGfxMatrix, 0.5f, 0.5f, 1.0f, 1);
        if (((gGameFrameCount % 2) == 0)) {
            Matrix_Scale(gGfxMatrix, 1.7f, 1.7f, 1.0f, 1);
        } else {
            Matrix_Scale(gGfxMatrix, 1.3f, 1.3f, 1.0f, 1);
        }
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, D_1024AC0);
        Matrix_Pop(&gGfxMatrix);
    }
}

void func_display_80055B58(Player* player) {
    Vec3f sp4C;
    Vec3f sp40;
    f32 var_fv0;
    s32 pad[3];

    if ((player->unk_234 != 0) && (player->state_1C8 != PLAYERSTATE_1C8_4)) {
        switch (player->form) {
            case FORM_ARWING:
                Matrix_RotateY(gCalcMatrix, (player->unk_114 + player->unk_0E8 + player->unk_134 + 180.0f) * M_DTOR, 0);
                Matrix_RotateX(gCalcMatrix,
                               -((player->unk_120 + player->unk_0E4 + player->unk_134 + player->unk_4D8) * M_DTOR), 1);
                Matrix_RotateZ(gCalcMatrix, -((player->unk_0F8 + player->unk_0F0 + player->unk_134) * M_DTOR), 1);
                Matrix_Translate(gCalcMatrix, player->unk_084, player->unk_080, 0.0f, 1);
                var_fv0 = player->unk_194 * 30.0f;
                if (var_fv0 > 30.0f) {
                    var_fv0 = 30.0f;
                }

                sp4C.x = 0;
                sp4C.y = 0;
                sp4C.z = -40.0f - var_fv0;

                Matrix_MultVec3f(gCalcMatrix, &sp4C, &sp40);
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, player->pos.x + sp40.x, player->pos.y + sp40.y,
                                 player->unk_138 + player->unk_144 + sp40.z, 1);
                Matrix_RotateY(gGfxMatrix, -gPlayer[gPlayerNum].unk_058, 1);
                Matrix_RotateX(gGfxMatrix, gPlayer[gPlayerNum].unk_05C, 1);
                Matrix_SetGfxMtx(&gMasterDisp);
                func_display_8005478C(player);
                Matrix_Pop(&gGfxMatrix);
                func_display_80054914(player);
                func_display_80054CA4(player);
                func_display_80054E80(player);
                break;
            case FORM_LANDMASTER:
                func_display_80052D48(player);
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, D_display_80161518[player->num].x, D_display_80161518[player->num].y,
                                 D_display_80161518[player->num].z, 0);
                Matrix_SetGfxMtx(&gMasterDisp);
                func_display_8005478C(player);
                Matrix_Pop(&gGfxMatrix);
                func_display_80055788(player);
                break;
            case FORM_BLUE_MARINE:
                func_display_80054914(player);
                break;
        }
    }
}

void func_display_80055E98(Player* player) {
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 var_fs0;

    sp5C = 70.0f;
    sp58 = -18.0f;
    if (player->unk_204 == 2) {
        sp5C = 108.0f;
        sp58 = -22.0f;
    }
    if (player->unk_25C != 0.0f) {
        sp54 = 0.0f;
        if ((gGameFrameCount % 2) != 0) {
            sp54 = 180.0f;
        }
        var_fs0 = player->unk_0E8;
        if (var_fs0 > 90.0f) {
            var_fs0 -= 180.0f;
        }
        var_fs0 = var_fs0 * 0.25f;
        sp50 = player->unk_0E4 * 0.25f;
        if (player->state_1C8 == PLAYERSTATE_1C8_7) {
            var_fs0 = 0.0f;
            sp50 = 0.0f;
        }
        RCP_SetupDL_64();
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 100);
        if (player->wings.leftState == WINGSTATE_INTACT) {
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, sp5C, sp58, -100.0f, 1);
            Matrix_RotateX(gGfxMatrix, M_DTOR * sp50, 1);
            Matrix_RotateY(gGfxMatrix, -(M_DTOR * var_fs0), 1);
            Matrix_Scale(gGfxMatrix, player->unk_25C, 1.0f, 50.0f, 1);
            Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -17.5f, 1);
            Matrix_RotateX(gGfxMatrix, M_PI / 2, 1);
            Matrix_RotateY(gGfxMatrix, M_DTOR * sp54, 1);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_102A8A0);
            Matrix_Pop(&gGfxMatrix);
        }
        if (player->wings.rightState == WINGSTATE_INTACT) {
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, -sp5C, sp58, -100.0f, 1);
            Matrix_RotateX(gGfxMatrix, M_DTOR * sp50, 1);
            Matrix_RotateY(gGfxMatrix, -(M_DTOR * var_fs0), 1);
            Matrix_Scale(gGfxMatrix, player->unk_25C, 1.0f, 50.0f, 1);
            Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -17.5f, 1);
            Matrix_RotateX(gGfxMatrix, M_PI / 2, 1);
            Matrix_RotateY(gGfxMatrix, M_DTOR * sp54, 1);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_102A8A0);
            Matrix_Pop(&gGfxMatrix);
        }
    }
}

void func_display_80056230(Player* player) {
    if ((player->unk_234 != 0) && (player->form == FORM_ARWING) && (gCurrentLevel != LEVEL_VENOM_ANDROSS) &&
        (gCurrentLevel != LEVEL_TRAINING) && (gLevelType == LEVELTYPE_PLANET)) {
        Matrix_Push(&gGfxMatrix);
        Matrix_Translate(gGfxMatrix, player->pos.x, player->pos.y, player->unk_138 + player->unk_144, 1);
        Matrix_RotateY(gGfxMatrix, (player->unk_114 + player->unk_0E8 + 180.0f) * M_DTOR, 1);
        Matrix_RotateX(gGfxMatrix, -((player->unk_120 + player->unk_0E4 + player->unk_4D8) * M_DTOR), 1);
        Matrix_RotateZ(gGfxMatrix, -((player->unk_0F8 + player->unk_0F0 + player->unk_134) * M_DTOR), 1);
        Matrix_Translate(gGfxMatrix, player->unk_084, player->unk_080, 0.0f, 1);
        Matrix_SetGfxMtx(&gMasterDisp);
        func_display_80055E98(player);
        Matrix_Pop(&gGfxMatrix);
    }
}

bool func_display_800563B4(s32 index, s32 arg1) {
    Vec3f sp2C = { 0.0f, 0.0f, 0.0f };
    Vec3f sp20;

    Matrix_MultVec3f(gGfxMatrix, &sp2C, &sp20);
    if ((sp20.z < 200.0f) && (sp20.z > -12000.0f)) {
        if (fabsf(sp20.x) < (fabsf(sp20.z * 0.5f) + 500.0f)) {
            if (fabsf(sp20.y) < (fabsf(sp20.z * 0.5f) + 500.0f)) {
                if (arg1 == 0) {
                    D_display_800CA224[index] = 1;
                }
                return true;
            }
        }
    }
    if (arg1 == 0) {
        D_display_800CA224[index] = 0;
    }
    return false;
}

s32 D_display_800CA2E8[16] = { 60, 40, 20, 20, 20, 20, 20, 20, 0, 0, 0, 0, 0, 0, 0, 0 };

void func_display_800564C0(Player* player, s32 arg1) {
    s32 i;
    Vec3f sp50 = { 0.0f, 0.0f, 0.0f };

    if (player->unk_234 != 0) {
        Matrix_Push(&gGfxMatrix);
        if (player->form == FORM_LANDMASTER) {
            if (player->unk_1D4 != 0) {
                Matrix_Translate(gGfxMatrix, 0.0f, gCameraShakeY, 0.0f, 1);
            }
            Matrix_Translate(gGfxMatrix, player->pos.x, player->pos.y + player->unk_18C + 30.0f,
                             player->unk_138 + player->unk_144, 1);
            if (gVersusMode) {
                for (i = 0; i < gCamCount; i++) {
                    if (D_ctx_80177B00[player->num][i] != 0) {
                        Matrix_MultVec3f(gGfxMatrix, &sp50, &D_display_80161578[i]);
                        if ((i == gPlayerNum) &&
                            ((D_display_80161578[i].z > 300.0f) || (D_display_80161578[i].z < -8000.0f) ||
                             (fabsf(D_display_80161578[i].x) > (fabsf(D_display_80161578[i].z * 0.5f) + 100.0f)) ||
                             (fabsf(D_display_80161578[i].y)) > (fabsf(D_display_80161578[i].z * 0.5f) + 100.0f))) {

                            D_ctx_80177B00[player->num][i] = 0;
                        }
                    }
                }
            }
            if (!func_display_800563B4(player->num, arg1)) {
                Matrix_Pop(&gGfxMatrix);
                return;
            }
            Matrix_RotateX(gGfxMatrix, (player->unk_0E4 + player->unk_134) * M_DTOR, 1);
            Matrix_RotateZ(gGfxMatrix, (player->unk_0EC + player->unk_0F0 + player->unk_134) * M_DTOR, 1);
            Matrix_RotateY(gGfxMatrix, (player->unk_114 + player->unk_0E8 + 180.0f) * M_DTOR, 1);
            if (gVersusMode) {
                Matrix_RotateX(gGfxMatrix, player->unk_000 * M_DTOR, 1);
            }
            Matrix_RotateZ(gGfxMatrix, (-player->unk_12C - player->unk_130) * M_DTOR, 1);
            Matrix_Translate(gGfxMatrix, player->unk_084, player->unk_080 - 30.0f, 0.0f, 1);
            Matrix_SetGfxMtx(&gMasterDisp);
        } else if (player->form == FORM_ON_FOOT) {
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, player->pos.x, player->pos.y, player->unk_138 + player->unk_144, 1);
            if (!func_display_800563B4(player->num, arg1)) {
                Matrix_Pop(&gGfxMatrix);
                Matrix_Pop(&gGfxMatrix);
                return;
            }
            Matrix_Pop(&gGfxMatrix);
            Matrix_Translate(gCalcMatrix, player->pos.x, player->pos.y + gCameraShakeY,
                             player->unk_138 + player->unk_144, 0);
            Matrix_RotateY(gCalcMatrix, (player->unk_114 + player->unk_0E8 + player->unk_134 + 180.0f) * M_DTOR, 1);
            Matrix_RotateX(gCalcMatrix, -((player->unk_120 + player->unk_0E4 + player->unk_134) * M_DTOR), 1);
            Matrix_RotateZ(gCalcMatrix, -((player->unk_0F8 + player->unk_0F0 + player->unk_134) * M_DTOR), 1);
            Matrix_Translate(gCalcMatrix, player->unk_084, player->unk_080, 0.0f, 1);
        } else {
            Matrix_Translate(gGfxMatrix, player->pos.x, player->pos.y, player->unk_138 + player->unk_144, 1);
            if (gVersusMode) {
                for (i = 0; i < gCamCount; i++) {
                    if (D_ctx_80177B00[player->num][i] != 0) {
                        Matrix_MultVec3f(gGfxMatrix, &sp50, &D_display_80161578[i]);
                        if ((i == gPlayerNum) &&
                            ((D_display_80161578[i].z > 300.0f) || (D_display_80161578[i].z < -8000.0f) ||
                             (fabsf(D_display_80161578[i].x) > (fabsf(D_display_80161578[i].z * 0.5f) + 100.0f)) ||
                             (fabsf(D_display_80161578[i].y) > (fabsf(D_display_80161578[i].z * 0.5f) + 100.0f)))) {

                            D_ctx_80177B00[player->num][i] = 0;
                        }
                    }
                }
            }
            if (!func_display_800563B4(player->num, arg1)) {
                Matrix_Pop(&gGfxMatrix);
                return;
            }
            Matrix_RotateY(gGfxMatrix, (player->unk_114 + player->unk_0E8 + player->unk_134 + 180.0f) * M_DTOR, 1);
            Matrix_RotateX(gGfxMatrix,
                           -((player->unk_120 + player->unk_0E4 + player->unk_4D8 + player->unk_134) * M_DTOR), 1);
            Matrix_RotateZ(gGfxMatrix, -((player->unk_0F8 + player->unk_0F0 + player->unk_134) * M_DTOR), 1);
            Matrix_Translate(gGfxMatrix, player->unk_084, player->unk_080, 0.0f, 1);
            Matrix_SetGfxMtx(&gMasterDisp);
        }
        switch (player->unk_200) {
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
        if (arg1 != 0) {
            func_edisplay_800596C0();
        } else {
            Matrix_Copy(&D_display_80161418[player->num], gGfxMatrix);
        }
        func_display_80054280(player, arg1);
        Matrix_Pop(&gGfxMatrix);
    }
}

f32 D_display_800CA334[] = {
    0.02f, 0.06f, 0.08f, 0.05f, 0.04f, 0.03f, 0.06f, 0.04f,
};
Gfx* D_display_800CA354[] = {
    D_1024570, D_1024570, D_10246D0, D_1024410, D_1024410, D_1024410,
    D_1024410, D_1024410, D_D000000, D_D00B5C0, D_D00B720,
};
f32 D_display_800CA380 = 0.0f;
f32 D_display_800CA384 = 0.0f;
f32 D_display_800CA388 = -300.0f;
f32 D_display_800CA38C[] = {
    0.0f,
    -300.0f,
    -150.0f,
    -50.0f,
};

void func_display_80056E2C(Player* player) {
    f32 sp34;
    f32 sp30;
    f32 sp2C;

    if ((player->unk_234 != 0) && (player->unk_240 == 0)) {
        sp34 = D_display_800CA334[gGameFrameCount % 8U];
        sp30 = D_display_800CA334[(gGameFrameCount + 4) % 8U];
        if (player->unk_1D4 != 0) {
            sp34 = sp30 = 0.0f;
        }
        Matrix_Push(&gGfxMatrix);
        if (gLevelMode == LEVELMODE_ALL_RANGE) {
            if (player->form == FORM_ON_FOOT) {
                Matrix_Translate(gGfxMatrix, player->unk_064, player->unk_068 + 2.0f, player->unk_06C, 1);
            } else {
                Matrix_Translate(gGfxMatrix, player->unk_064, player->unk_068 + 2.0f, player->unk_06C, 1);
            }
        } else {
            Matrix_Translate(gGfxMatrix, player->unk_064, player->unk_068 + 2.0f, player->unk_06C + player->unk_144, 1);
        }
        Matrix_RotateY(gGfxMatrix, player->unk_070, 1);
        Matrix_RotateX(gGfxMatrix, player->unk_248, 1);
        Matrix_RotateZ(gGfxMatrix, player->unk_24C, 1);
        Matrix_Scale(gGfxMatrix, 0.8f + sp34, 0.0f, 0.8f + sp30, 1);
        if ((player->form == FORM_ARWING) || (player->form == FORM_BLUE_MARINE) || (player->form == FORM_ON_FOOT)) {
            sp2C = player->unk_0F8 + player->unk_0F0 + player->unk_134;
            if (((sp2C > 70.0f) && (sp2C < 110.0f)) || ((sp2C < -70.0f) && (sp2C > -110.0f))) {
                sp2C = 70.0f;
            }
            Matrix_RotateY(gGfxMatrix, -player->unk_070, 1);
            Matrix_RotateY(gGfxMatrix, (player->unk_114 + player->unk_0E8 + player->unk_134) * M_DTOR, 1);
            Matrix_RotateX(gGfxMatrix,
                           -((player->unk_120 + player->unk_0E4 + player->unk_4D8 + player->unk_134) * M_DTOR), 1);
            Matrix_RotateZ(gGfxMatrix, M_DTOR * sp2C, 1);
        } else {
            Matrix_RotateY(gGfxMatrix, player->unk_114 * M_DTOR, 1);
            Matrix_RotateX(gGfxMatrix, (player->unk_0E4 + player->unk_4D8 + player->unk_134) * M_DTOR, 1);
            Matrix_RotateZ(gGfxMatrix, (player->unk_0EC + player->unk_0F0 + player->unk_134) * M_DTOR, 1);
            Matrix_RotateY(gGfxMatrix, player->unk_0E8 * M_DTOR, 1);
            Matrix_RotateZ(gGfxMatrix, (-player->unk_12C - player->unk_130) * M_DTOR, 1);
        }
        func_display_80054300(player);
        Matrix_Pop(&gGfxMatrix);
    }
}

void func_display_80057248(void) {
    s32 i;
    f32 var_fs0;

    if (!(gGameFrameCount & 4)) {
        RCP_SetupDL_40();
        for (i = 0; i < ARRAY_COUNT(gTeamArrowsViewPos); i++) {
            if (gTeamArrowsViewPos[i].z < 0.0f) {
                var_fs0 = (VEC3F_MAG(&gTeamArrowsViewPos[i])) * 0.0015f;
                if (var_fs0 > 100.0f) {
                    var_fs0 = 100.0f;
                } else if (var_fs0 < 1.0f) {
                    var_fs0 = 1.0f;
                }
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, gTeamArrowsViewPos[i].x, gTeamArrowsViewPos[i].y, gTeamArrowsViewPos[i].z,
                                 1);
                Matrix_Scale(gGfxMatrix, var_fs0 * 0.25f, var_fs0 * 0.25f, 1.0f, 1);
                if ((i == 0) && (gCurrentLevel == LEVEL_SECTOR_Z)) {
                    Matrix_Scale(gGfxMatrix, 2.0f, 2.0f, 1.0f, 1);
                }
                Matrix_Translate(gGfxMatrix, 0.0f, 150.0f, 0.0f, 1);
                Matrix_SetGfxMtx(&gMasterDisp);
                gDPSetTextureFilter(gMasterDisp++, G_TF_POINT);
                if ((i == 0) && (gCurrentLevel == LEVEL_SECTOR_Z)) {
                    gSPDisplayList(gMasterDisp++, D_SZ_6004330);
                } else {
                    gSPDisplayList(gMasterDisp++, D_display_800CA354[i]);
                }
                Matrix_Pop(&gGfxMatrix);
            }
            gTeamArrowsViewPos[i].x = gTeamArrowsViewPos[i].y = 0;
            gTeamArrowsViewPos[i].z = 100.0f;
        }
        gDPSetTextureFilter(gMasterDisp++, G_TF_BILERP);
    }
}

void func_display_80057504(void) {
    s32 i;
    s32 j;
    f32 var_fs0;

    for (i = 0; i < gCamCount; i++) {
        if (D_display_80161578[i].z < 0.0f) {
            var_fs0 = (VEC3F_MAG(&D_display_80161578[i]));
            if (var_fs0 < 20000.0f) {
                var_fs0 *= 0.0015f;
                if (var_fs0 > 100.0f) {
                    var_fs0 = 100.0f;
                }
                if (var_fs0 < 1.2f) {
                    var_fs0 = 1.2f;
                }
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, D_display_80161578[i].x, D_display_80161578[i].y, D_display_80161578[i].z,
                                 1);
                if ((gPlayState != PLAY_PAUSE) && (i == gPlayerNum)) {
                    Math_SmoothStepToF(&D_display_801615A8[i], 0.0f, 0.5f, 20.0f, 0);
                    Math_SmoothStepToF(&D_display_801615B8[i], 1.0, 0.5f, 0.2f, 0);
                }
                var_fs0 *= D_display_801615B8[i];
                Matrix_Scale(gGfxMatrix, var_fs0 * 1.5f, var_fs0 * 1.5f, 1.0f, 1);
                Matrix_RotateZ(gGfxMatrix, D_display_801615A8[i] * M_DTOR, 1);
                Matrix_SetGfxMtx(&gMasterDisp);
                RCP_SetupDL(&gMasterDisp, 0x43);
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
                gDPSetEnvColor(gMasterDisp++, 255, 0, 0, 255);
                gSPDisplayList(gMasterDisp++, D_1024F60);
                Matrix_Pop(&gGfxMatrix);
            }
        }
    }
    for (j = 0; j < gCamCount; j++) {

        D_display_80161578[j].x = D_display_80161578[j].y = 0.f;
        D_display_80161578[j].z = 100.0f;
    }
}

void func_display_80057814(Player* player) {
    Vec3f sp2C;
    Vec3f sp20;

    sp20.x = player->pos.x;
    sp20.y = player->pos.y;
    sp20.z = player->unk_138;
    sp2C.x = player->sfxSource[0];
    sp2C.y = player->sfxSource[1];
    sp2C.z = player->sfxSource[2];
    func_edisplay_8005F0E8(player->sfxSource, &sp20);
    player->sfxVel[0] = player->sfxSource[0] - sp2C.x;
    player->sfxVel[1] = player->sfxSource[1] - sp2C.y;
    player->sfxVel[2] = player->sfxSource[2] - sp2C.z;
    player->sfx.srcVel = player->sfxVel;
    player->sfx.srcPos = player->sfxSource;
    player->sfx.yVel = player->vel.y;
    player->sfx.zRot = player->unk_0F8;
}

void func_display_800578C4(Player* player) {
    Vec3f sp4C = { 0.0f, 0.0f, -300.0f };
    Vec3f sp40;
    f32 sp3C;
    f32 sp38;

    switch (D_display_800CA220) {
        case 0:
            Math_SmoothStepToAngle(&player->wings.unk_30, 0.0f, 0.2f, 3.0f, 0.0f);
            Math_SmoothStepToAngle(&player->wings.unk_34, 0.0f, 0.2f, 3.0f, 0.0f);
            gPlayerCamEye.x = player->camEye.x;
            gPlayerCamEye.y = player->camEye.y;
            gPlayerCamEye.z = player->camEye.z;
            gPlayerCamAt.x = player->camAt.x;
            gPlayerCamAt.y = player->camAt.y;
            gPlayerCamAt.z = player->camAt.z;
            break;
        case 1:
        case 2:
        case 3:
            sp38 = Math_RadToDeg(player->unk_05C) + player->unk_0E4;
            if (sp38 > 360.0f) {
                sp38 -= 360.0f;
            }
            if (sp38 < 0.0f) {
                sp38 += 360.0f;
            }
            sp3C = (Math_RadToDeg(player->unk_058) + 180.0f) - player->unk_0E8;
            if (sp3C > 360.0f) {
                sp3C -= 360.0f;
            }
            if (sp3C < 0.0f) {
                sp3C += 360.0f;
            }
            sp3C = 360.0f - sp3C;
            Math_SmoothStepToAngle(&player->wings.unk_30, sp38, 0.2f, 6.0f, 0.0f);
            Math_SmoothStepToAngle(&player->wings.unk_34, sp3C, 0.2f, 6.0f, 0.0f);
            Math_SmoothStepToF(&D_display_800CA380, gControllerPress->stick_y * 0.75f, 0.1f, 2.0f, 0.0f);
            Math_SmoothStepToF(&D_display_800CA384, gControllerPress->stick_x * 3.0f, 0.1f, 5.0f, 0.0f);
            Math_SmoothStepToF(&D_display_800CA388, D_display_800CA38C[D_display_800CA220], 0.1f, 10.0f, 0.0f);
            sp4C.z = D_display_800CA388;
            Matrix_RotateX(gCalcMatrix, (player->unk_0E8 + D_display_800CA380) * M_DTOR, 0);
            Matrix_RotateY(gCalcMatrix, (player->unk_0E4 + D_display_800CA384) * M_DTOR, 1);
            Matrix_MultVec3f(gCalcMatrix, &sp4C, &sp40);
            gPlayerCamEye.x = player->pos.x + sp40.x;
            gPlayerCamEye.y = player->pos.y + sp40.y + 20.0f;
            gPlayerCamEye.z = player->unk_138 + sp40.z;
            gPlayerCamAt.x = (SIN_DEG(gGameFrameCount * 3.0f) * 3.0f) + player->pos.x;
            gPlayerCamAt.y = (COS_DEG(gGameFrameCount * 4.0f) * 3.0f) + player->pos.y;
            gPlayerCamAt.z = (SIN_DEG(gGameFrameCount * 3.5f) * 3.0f) + player->unk_138;
            break;
    }
}

void Play_Draw(void) {
    s32 i;
    Vec3f tempVec;
    Vec3f playerCamUp;
    Vec3f opponentPos;
    s32 pad;
    Player* opponent;
    Player* player = &gPlayer[gPlayerNum];

    D_display_800CA228 = 0;

    if (gHitCount > 511) {
        gHitCount = 511;
    }
    Matrix_Push(&gGfxMatrix);
    if ((gCurrentLevel == LEVEL_AQUAS) && (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_3)) {
        Math_SmoothStepToF(&D_display_800CA230, 0.01f, 0.2f, 0.002f, 0.0f);
    } else {
        Math_SmoothStepToF(&D_display_800CA230, 0.0f, 0.2f, 0.002f, 0.0f);
    }
    Matrix_RotateZ(gGfxMatrix, gGameFrameCount * 10.0f * M_DTOR, 1);
    Matrix_Scale(gGfxMatrix, 1.0f + D_display_800CA230, 1.0f - D_display_800CA230, 1.0f, 1);
    Matrix_RotateZ(gGfxMatrix, -(f32) gGameFrameCount * 10.0f * M_DTOR, 1);
    Matrix_Scale(gGfxMatrix, 1.0f + D_display_800CA230, 1.0f - D_display_800CA230, 1.0f, 1);
    Matrix_Push(&gGfxMatrix);
    func_play_800B73E0(player);
    Lights_SetOneLight(&gMasterDisp, gLight1x, gLight1y, gLight1z, gLight1R, gLight1G, gLight1B, gAmbientR, gAmbientG,
                       gAmbientB);
    if (gLevelMode == LEVELMODE_ON_RAILS) {
        Matrix_RotateY(gCalcMatrix, player->unk_114 * M_DTOR, 0);
        Matrix_RotateX(gCalcMatrix, player->unk_120 * M_DTOR, 1);

        tempVec.x = player->camEye.x - player->pos.x;
        tempVec.y = player->camEye.y - player->pos.y;
        tempVec.z = player->camEye.z - (player->unk_138 + player->unk_144);
        Matrix_MultVec3f(gCalcMatrix, &tempVec, &gPlayerCamEye);
        gPlayerCamEye.x += player->pos.x;
        gPlayerCamEye.y += player->pos.y;
        gPlayerCamEye.z += player->unk_138 + player->unk_144;

        tempVec.x = player->camAt.x - player->pos.x;
        tempVec.y = player->camAt.y - player->pos.y;
        tempVec.z = player->camAt.z - (player->unk_138 + player->unk_144);
        Matrix_MultVec3f(gCalcMatrix, &tempVec, &gPlayerCamAt);
        gPlayerCamAt.x += player->pos.x;
        gPlayerCamAt.y += player->pos.y;
        gPlayerCamAt.z += player->unk_138 + player->unk_144;

        if ((player->cockpitView != 0) && (player->unk_110 > 5.0f)) {
            gPlayerCamAt.x += SIN_DEG(gGameFrameCount * 150.0f) * player->unk_110 * 0.2f;
        }
    } else if (player->state_1C8 == PLAYERSTATE_1C8_7) {
        func_display_800578C4(player);
    } else {
        gPlayerCamEye.x = player->camEye.x;
        gPlayerCamEye.y = player->camEye.y;
        gPlayerCamEye.z = player->camEye.z;
        gPlayerCamAt.x = player->camAt.x;
        gPlayerCamAt.y = player->camAt.y;
        gPlayerCamAt.z = player->camAt.z;
    }
    player->unk_058 = -Math_Atan2F(gPlayerCamEye.x - gPlayerCamAt.x, gPlayerCamEye.z - gPlayerCamAt.z);
    player->unk_05C = -Math_Atan2F(gPlayerCamEye.y - gPlayerCamAt.y,
                                   sqrtf(SQ(gPlayerCamEye.z - gPlayerCamAt.z) + SQ(gPlayerCamEye.x - gPlayerCamAt.x)));
    Matrix_RotateY(gCalcMatrix, -player->unk_058, 0);
    Matrix_RotateX(gCalcMatrix, player->unk_05C, 1);
    Matrix_RotateZ(gCalcMatrix, -player->unk_034 * M_DTOR, 1);
    tempVec.x = 0.0f;
    tempVec.y = 100.0f;
    tempVec.z = 0.0f;
    Matrix_MultVec3f(gCalcMatrix, &tempVec, &playerCamUp);
    if (D_ctx_80178410 != 0) {
        D_ctx_80178428 = DEG_TO_RAD(gPlayer[0].unk_034);
        func_play_800B6F50(gPlayerCamEye.x, gPlayerCamEye.y, gPlayerCamEye.z, gPlayerCamAt.x, gPlayerCamAt.y,
                           gPlayerCamAt.z);
        func_bg_8003DAF0();
    }
    func_bg_8003E1E8();
    func_bg_80040450();
    Matrix_Push(&gGfxMatrix);
    Matrix_LookAt(gGfxMatrix, gPlayerCamEye.x, gPlayerCamEye.y, gPlayerCamEye.z, gPlayerCamAt.x, gPlayerCamAt.y,
                  gPlayerCamAt.z, playerCamUp.x, playerCamUp.y, playerCamUp.z, 1);
    if ((gLevelType == LEVELTYPE_PLANET) || (gCurrentLevel == LEVEL_BOLSE)) {
        if ((gCurrentLevel == LEVEL_TITANIA) &&
            ((gPlayer[0].state_1C8 != PLAYERSTATE_1C8_2) || (gPlayer[0].unk_19C != 0))) {
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, 0.0f, gCameraShakeY, 0.0f, 1);
            Matrix_SetGfxMtx(&gMasterDisp);
            Ground_801B58AC(&gMasterDisp, D_ctx_80177CC8);
            D_ctx_80177CC8 = 0.0f;
            Matrix_Pop(&gGfxMatrix);
        } else if (gGroundType != GROUNDTYPE_WATER) {
            D_bg_8015F964 = 0;
            func_bg_80040CE4();
        }
    }
    Lights_SetOneLight(&gMasterDisp, gLight2x, gLight2y, gLight2z, gLight2R, gLight2G, gLight2B, gAmbientR, gAmbientG,
                       gAmbientB);
    for (i = 0, opponent = gPlayer; i < gCamCount; i++, opponent++) {
        opponentPos.x = opponent->pos.x;
        opponentPos.y = opponent->pos.y;
        opponentPos.z = opponent->unk_138;
        func_edisplay_8005F670(&opponentPos);
        func_display_800564C0(opponent, 0);
        func_display_80057814(opponent);
    }
    if ((gGroundType == GROUNDTYPE_WATER) && (gPlayer[0].state_1C8 != PLAYERSTATE_1C8_2)) {
        Lights_SetOneLight(&gMasterDisp, gLight2x, -1 * gLight2y, gLight2z, gLight2R, gLight2G, gLight2B, gAmbientR,
                           gAmbientG, gAmbientB);
        Matrix_Push(&gGfxMatrix);
        Matrix_Scale(gGfxMatrix, 1.0f, -1.0f, 1.0f, 1);
        for (i = 0, opponent = gPlayer; i < gCamCount; i++, opponent++) {
            opponentPos.x = opponent->pos.x;
            opponentPos.y = opponent->pos.y;
            opponentPos.z = opponent->unk_138;
            func_display_800564C0(opponent, 1);
        }
        Matrix_Pop(&gGfxMatrix);
    }
    Lights_SetOneLight(&gMasterDisp, gLight1x, gLight1y, gLight1z, gLight1R, gLight1G, gLight1B, gAmbientR, gAmbientG,
                       gAmbientB);
    Object_Draw(1);
    TexturedLine_Draw();
    gReflectY = 1;
    PlayerShot_Draw();
    if ((gGroundType == GROUNDTYPE_WATER) && (gPlayer[0].state_1C8 != PLAYERSTATE_1C8_2)) {
        Matrix_Push(&gGfxMatrix);
        Matrix_Scale(gGfxMatrix, 1.0f, -1.0f, 1.0f, 1);
        gReflectY = -1;
        PlayerShot_Draw();
        Matrix_Pop(&gGfxMatrix);
    }
    gReflectY = -1;
    if ((gGroundType == GROUNDTYPE_WATER) && (gPlayer[0].state_1C8 != PLAYERSTATE_1C8_2)) {
        Matrix_Push(&gGfxMatrix);
        Matrix_Scale(gGfxMatrix, 1.0f, -1.0f, 1.0f, 1);
        for (i = 0, opponent = gPlayer; i < gCamCount; i++, opponent++) {
            if (D_display_800CA224[i] != 0) {
                func_display_80055B58(opponent);
                func_display_80056230(opponent);
            }
            Matrix_Pop(&gGfxMatrix);
        }
    }
    if (gCurrentLevel == LEVEL_AQUAS) {
        Effect_Draw(0);
    }
    if ((gGroundType == GROUNDTYPE_WATER) || (D_ctx_80177AC8 != 0)) {
        D_bg_8015F964 = 1;
        Effect_Draw(1);
        func_bg_80040CE4();
    }
    if ((gCurrentLevel != LEVEL_AQUAS) &&
        (((gCurrentLevel != LEVEL_CORNERIA) && (gCurrentLevel != LEVEL_VENOM_ANDROSS)) ||
         ((gPlayer[0].state_1C8 != PLAYERSTATE_1C8_7) && (gPlayer[0].state_1C8 != PLAYERSTATE_1C8_2)))) {
        Effect_Draw(0);
    }
    gReflectY = 1;
    for (i = 0, opponent = gPlayer; i < gCamCount; i++, opponent++) {
        if (D_display_800CA224[i] != 0) {
            func_display_80056E2C(opponent);
            func_display_80055B58(opponent);
            func_display_80056230(opponent);
        }
    }
    if ((gCurrentLevel == LEVEL_AQUAS) && (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_3)) {
        Aquas_801AA20C();
    }
    if (((gCurrentLevel == LEVEL_CORNERIA) || (gCurrentLevel == LEVEL_VENOM_ANDROSS)) &&
        ((gPlayer[0].state_1C8 == PLAYERSTATE_1C8_7) || (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_2))) {
        Effect_Draw(0);
    }
    BonusText_DrawAll();
    Matrix_Pop(&gGfxMatrix);
    func_display_80057248();
    func_display_80057504();
    if (D_display_800CA228 != 0) {
        func_display_80053B18();
    }
    for (i = 0, opponent = gPlayer; i < gCamCount; i++, opponent++) {
        if (D_display_800CA224[i] != 0) {
            if (gShowCrosshairs[i]) {
                func_display_80053F7C(opponent);
            }
            if (opponent->form == FORM_LANDMASTER) {
                func_display_80052B80(opponent);
            } else if (opponent->form == FORM_ON_FOOT) {
                func_display_80052584(opponent);
            }
        }
    }
    if ((gLevelMode == LEVELMODE_UNK_2) && (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_3)) {
        Turret_801A6164(gPlayer);
    }
    func_bg_80040954();
    if ((gCamCount != 1) && ((player->state_1C8 == PLAYERSTATE_1C8_3) || (player->state_1C8 == PLAYERSTATE_1C8_5))) {
        func_hud_8008FA84();
        func_hud_8008CA44();
    }
    Matrix_Pop(&gGfxMatrix);
    func_display_80051B30();
    D_display_800CA224[gPlayerNum] = 0;
    Matrix_Pop(&gGfxMatrix);
}
