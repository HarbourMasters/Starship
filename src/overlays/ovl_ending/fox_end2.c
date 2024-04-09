#include "global.h"
#include "assets/ast_arwing.h"
#include "assets/ast_ending_expert.h"
#include "assets/ast_allies.h"

WingInfo D_ending_80198590;
Vec3f D_ending_801985D0;
Vec3f D_ending_801985E0;
Vec3f D_ending_801985F0;
Vec3f D_ending_80198600[300];

#include "fox_end2_data.c"

void Ending_8018CE20(u32 arg0) {
    u8 alpha;
    s32 i;
    s32 xPos;

    for (i = 0; i < ARRAY_COUNT(D_ending_80192E74); i++) {
        if (D_ending_80192E74[i].unk_00 != NULL) {
            if ((D_ending_80192E74[i].unk_04 <= arg0) &&
                ((D_ending_80192E74[i].unk_04 + D_ending_80192E74[i].unk_08) > arg0)) {
                alpha = 255;

                if ((D_ending_80192E74[i].unk_04 + D_ending_80192E74[i].unk_12) > arg0) {
                    alpha = (arg0 - D_ending_80192E74[i].unk_04) * 255 / D_ending_80192E74[i].unk_12;
                }

                if ((D_ending_80192E74[i].unk_04 + D_ending_80192E74[i].unk_08 - D_ending_80192E74[i].unk_13) < arg0) {
                    alpha = (D_ending_80192E74[i].unk_04 + D_ending_80192E74[i].unk_08 - arg0) * 255 /
                            D_ending_80192E74[i].unk_13;
                }

                if ((D_ending_80192E74[i].unk_11 == 0) || (D_play_800D2F68 == true)) {
                    if (D_ending_80192E74[i].unk_10 == 1) {
                        xPos = (320 - Graphics_GetLargeTextWidth(D_ending_80192E74[i].unk_00)) / 2;
                        RCP_SetupDL(&gMasterDisp, 0x53);
                        gDPSetTextureFilter(gMasterDisp++, G_TF_POINT);
                        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, alpha);
                        Graphics_DisplayLargeText(xPos, D_ending_80192E74[i].unk_0E, 1.0f, 1.0f,
                                                  D_ending_80192E74[i].unk_00);

                    } else if (D_ending_80192E74[i].unk_10 == 2) {
                        RCP_SetupDL(&gMasterDisp, 0x53);
                        gDPSetTextureFilter(gMasterDisp++, G_TF_POINT);
                        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, alpha);
                        TextureRect_8bIA(&gMasterDisp, D_ending_80192E74[i].unk_00, 192, 5, 64.0f, 105.0f, 1.0f, 1.0f);
                        TextureRect_8bIA(&gMasterDisp, D_ending_80192E74[i].unk_00 + 960 * 1, 192, 5, 64.0f, 110.0f,
                                         1.0f, 1.0f);
                        TextureRect_8bIA(&gMasterDisp, D_ending_80192E74[i].unk_00 + 960 * 2, 192, 5, 64.0f, 115.0f,
                                         1.0f, 1.0f);
                        TextureRect_8bIA(&gMasterDisp, D_ending_80192E74[i].unk_00 + 960 * 3, 192, 5, 64.0f, 120.0f,
                                         1.0f, 1.0f);
                        TextureRect_8bIA(&gMasterDisp, D_ending_80192E74[i].unk_00 + 960 * 4, 192, 5, 64.0f, 125.0f,
                                         1.0f, 1.0f);
                        TextureRect_8bIA(&gMasterDisp, D_ending_80192E74[i].unk_00 + 960 * 5, 192, 5, 64.0f, 130.0f,
                                         1.0f, 1.0f);
                    } else {
                        xPos = (320 - Graphics_GetSmallTextWidth(D_ending_80192E74[i].unk_00)) / 2;
                        RCP_SetupDL(&gMasterDisp, 0x53);
                        gDPSetTextureFilter(gMasterDisp++, G_TF_POINT);
                        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 155, 155, alpha);
                        Graphics_DisplaySmallText(xPos, D_ending_80192E74[i].unk_0E, 1.0f, 1.0f,
                                                  D_ending_80192E74[i].unk_00);
                    }
                }
            }
        }
    }
}

void Ending_8018D250(u32 arg0, AssetInfo* asset) {
    gOverlayStage = asset->unk_08;
    D_80137E78 = asset->unk_70;
    D_ctx_80178410 = asset->unk_14;
}

void Ending_8018D28C(s32 arg0, AssetInfo* asset) {
    D_ctx_8017842C += asset->unk_18.x;
    D_ctx_80178430 += asset->unk_18.y;
}

void Ending_8018D2C8(u32 arg0, AssetInfo* asset) {
    u8 alpha = 255;

    if ((asset->unk_0C + asset->fogNear) > arg0) {
        alpha = (arg0 - asset->unk_0C) * 255 / asset->fogNear;
    }

    if ((asset->unk_0C + asset->unk_10 - asset->fogFar) < arg0) {
        alpha = (asset->unk_0C + asset->unk_10 - arg0 - 1) * 255 / asset->fogFar;
    }

    gFillScreenRed = asset->primRed;
    gFillScreenGreen = asset->primGreen;
    gFillScreenBlue = asset->primBlue;

    gFillScreenAlpha = gFillScreenAlphaTarget = alpha;
    gFillScreenAlphaStep = 0;
}

void Ending_8018D398(u32 arg0, AssetInfo* asset) {
    u8 alpha = 255;

    if ((asset->unk_0C + asset->fogNear) > arg0) {
        alpha = (arg0 - asset->unk_0C) * 255 / asset->fogNear;
    }

    if ((asset->unk_0C + asset->unk_10 - asset->fogFar) < arg0) {
        alpha = (asset->unk_0C + asset->unk_10 - arg0) * 255 / asset->fogFar;
    }

    gFillScreenRed = gFillScreenGreen = gFillScreenBlue = gFillScreenAlpha = gFillScreenAlphaTarget =
        gFillScreenAlphaStep = 0;

    Graphics_FillRectangle(&gMasterDisp, 8, 8, SCREEN_WIDTH - 8, SCREEN_HEIGHT - 8, asset->primRed, asset->primGreen,
                           asset->primBlue, alpha);
}

void Ending_8018D4BC(s32 arg0, AssetInfo* asset) {
    Vec3f src;
    Vec3f dest;

    Matrix_RotateY(gCalcMatrix, M_DTOR * D_ending_801985F0.y, 0);
    Matrix_RotateX(gCalcMatrix, M_DTOR * D_ending_801985F0.x, 1);
    Matrix_RotateZ(gCalcMatrix, M_DTOR * D_ending_801985F0.z, 1);

    src.x = asset->unk_18.x;
    src.y = asset->unk_18.y;
    src.z = asset->unk_18.z;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

    Lights_SetOneLight(&gMasterDisp, dest.x, dest.y, dest.z, asset->unk_24.x, asset->unk_24.y, asset->unk_24.z,
                       asset->unk_30.x, asset->unk_30.y, asset->unk_30.z);
}

void Ending_8018D638(u32 arg0, AssetInfo* asset) {
    u8 alpha = 0;
    s32 i;

    if ((asset->unk_0C + asset->fogFar) > arg0) {
        alpha = (asset->unk_0C + asset->fogFar - arg0) * 255 / asset->fogFar;
    }

    gFillScreenRed = asset->primRed;
    gFillScreenGreen = asset->primGreen;
    gFillScreenBlue = asset->primBlue;

    gFillScreenAlpha = gFillScreenAlphaTarget = alpha;
    gFillScreenAlphaStep = 0;

    RCP_SetupDL(&gMasterDisp, 0x53);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    if (gExpertMode != 0) {
        for (i = 0; i < 240; i += 4) {
            if (!D_play_800D2F68) {
                TextureRect_16bRGBA(&gMasterDisp, gEndingNormalReward + 316 * i, 316, 4, 0.0f, i, 1.0f, 1.0f);
            } else {
                TextureRect_16bRGBA(&gMasterDisp, gEndingExpertReward + 316 * i, 316, 4, 0.0f, i, 1.0f, 1.0f);
            }
        }
    } else {
        D_ending_80192E70 = 7200;
    }
}

void Ending_8018D814(u32 arg0, AssetInfo* asset) {
    u8 alpha = 255;

    if ((asset->unk_0C + asset->fogNear) > arg0) {
        alpha = (arg0 - asset->unk_0C) * 255 / asset->fogNear;
    }

    if ((asset->unk_0C + asset->unk_10 - asset->fogFar) < arg0) {
        alpha = (asset->unk_0C + asset->unk_10 - arg0) * 255 / asset->fogFar;
    }

    RCP_SetupDL(&gMasterDisp, asset->unk_08);

    gDPSetPrimColor(gMasterDisp++, 0, 0, asset->primRed, asset->primGreen, asset->primBlue, alpha);

    TextureRect_8bIA(&gMasterDisp, D_5007240, 16, 15, asset->unk_18.x, asset->unk_18.y, 1.0f, 1.0f);
    TextureRect_8bIA(&gMasterDisp, D_5007420, 16, 15, asset->unk_18.x + 16.0f * 1, asset->unk_18.y, 1.0f, 1.0f);
    TextureRect_8bIA(&gMasterDisp, D_5007420, 16, 15, asset->unk_18.x + 16.0f * 2, asset->unk_18.y, 1.0f, 1.0f);
    TextureRect_8bIA(&gMasterDisp, D_5007330, 16, 15, asset->unk_18.x + 16.0f * 3, asset->unk_18.y, 1.0f, 1.0f);
}

void Ending_8018DA0C(u32 arg0, AssetInfo* asset) {
    u8 alpha = 255;

    if ((asset->unk_0C + asset->fogNear) > arg0) {
        alpha = (arg0 - asset->unk_0C) * 255 / asset->fogNear;
    }

    RCP_SetupDL(&gMasterDisp, asset->unk_08);
    gDPSetPrimColor(gMasterDisp++, 0, 0, asset->primRed, asset->primGreen, asset->primBlue, alpha);

    Graphics_DisplaySmallText((s16) asset->unk_18.x, (s16) asset->unk_18.y, asset->unk_30.x, asset->unk_30.y,
                              "TOTAL HITS");
    Graphics_DisplayLargeNumber((s16) (asset->unk_18.x + 5), (s16) (asset->unk_18.y + 13), gTotalHits);

    if ((Ending_8018DCB4() == true) && (alpha == 255)) {
        alpha = (arg0 - (asset->unk_0C + asset->fogNear)) % 10;

        switch (alpha) {
            case 0:
            case 1:
            case 2:
            case 3:
                alpha = 83 * alpha;
                break;
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
                alpha = 42 * (10 - alpha);
                break;
        }
        gDPSetPrimColor(gMasterDisp++, 0, 0, asset->primRed, asset->primGreen, asset->primBlue, alpha);
        Graphics_DisplaySmallText((s16) (asset->unk_18.x + 7), (s16) (asset->unk_18.y + 31), asset->unk_30.x,
                                  asset->unk_30.y, "RANK IN!!");
    }
}

bool Ending_8018DCB4(void) {
    s32 i;
    s32 j;
    s32 k;
    s32 m;
    s32 temp;
    s32 temp2 = 0;
    s32 temp3 = 0;
    s32 temp4[10];
    s32 unk_5E[10][7];
    s32 unk40[10];

    for (i = 0; i < gCurrentPlanet + 1; i++) {
        temp2 += ((D_ctx_80177B50[i] & 0x00FF0000) >> 16) & 1;
        temp2 += ((D_ctx_80177B50[i] & 0x0000FF00) >> 8) & 1;
        temp2 += (D_ctx_80177B50[i] & 0x000000FF) & 1;
    }

    for (i = 0; i < 10; i += 1) {
        temp4[i] = 0;
        unk40[i] = gSaveFile.save.data.unk_40[i];

        for (j = 0; j < 7; j += 1) {
            temp4[i] += gSaveFile.save.data.unk_5E[i][j].unk_0 + (gSaveFile.save.data.unk_5E[i][j].unk_C * 256);
            unk_5E[i][0] += gSaveFile.save.data.unk_5E[i][j].unk_D & 1;
            unk_5E[i][1] += gSaveFile.save.data.unk_5E[i][j].unk_F & 1;
            unk_5E[i][2] += gSaveFile.save.data.unk_5E[i][j].unk_E & 1;
        }
    }

    temp = -1;

    for (i = 0; i < 10; i++) {
        if (temp4[i] <= gTotalHits) {
            if (temp4[i] == gTotalHits) {
                for (j = i; j < 10; j++) {
                    if (temp4[j] != gTotalHits) {
                        temp = j;
                        break;
                    }

                    if (unk40[j] <= gLifeCount[gPlayerNum]) {
                        if (unk40[j] == gLifeCount[gPlayerNum]) {
                            for (k = j; k < 10; k++) {
                                if ((unk40[k] != gLifeCount[gPlayerNum]) || (temp4[k] != gTotalHits)) {
                                    temp = k;
                                    break;
                                }

                                temp3 = 0;

                                for (m = 0; m < 3; m++) {
                                    temp3 += unk_5E[k][m];
                                }

                                if (temp2 > temp3) {
                                    temp = k;
                                    break;
                                }
                            }
                        } else {
                            temp = j;
                        }
                        break;
                    }
                }
            } else {
                temp = i;
            }
            break;
        }
    }

    if (temp == -1) {
        return false;
    } else {
        return true;
    }
}

void Ending_8018E1B8(u32 arg0, AssetInfo* asset) {
    f32 temp;

    if ((asset->unk_18.z + (arg0 - asset->unk_0C) * asset->unk_3C.z) < D_ending_801985D0.z) {
        RCP_SetupDL(&gMasterDisp, 0x43);
    } else {
        RCP_SetupDL(&gMasterDisp, 0x3F);
    }

    gSPFogPosition(gMasterDisp++, asset->fogNear, asset->fogFar);
    gDPSetFogColor(gMasterDisp++, asset->fogRed, asset->fogGreen, asset->fogBlue, 0);
    gDPSetEnvColor(gMasterDisp++, asset->envRed, asset->envGreen, asset->envBlue, asset->envAlpha);
    gDPSetPrimColor(gMasterDisp++, 0, 0, asset->primRed, asset->primGreen, asset->primBlue, asset->primAlpha);

    Matrix_Translate(gGfxMatrix, asset->unk_18.x + (arg0 - asset->unk_0C) * asset->unk_3C.x,
                     asset->unk_18.y + (arg0 - asset->unk_0C) * asset->unk_3C.y,
                     asset->unk_18.z + (arg0 - asset->unk_0C) * asset->unk_3C.z, 1);

    Matrix_Scale(gGfxMatrix, asset->unk_30.x + (arg0 % 3) * 0.01f, asset->unk_30.y + (arg0 % 3) * 0.01f,
                 asset->unk_30.z + (arg0 % 3) * 0.01f, 1);

    temp = __sinf(arg0 * 0.1f + asset->unk_70);

    switch (asset->unk_71) {
        case 1:
            Matrix_RotateY(gGfxMatrix,
                           M_DTOR * (-D_ending_801985F0.y + asset->unk_24.y + temp * asset->unk_54.y +
                                     (arg0 - asset->unk_0C) * asset->unk_48.y),
                           1);
            Matrix_RotateX(gGfxMatrix,
                           M_DTOR * (-D_ending_801985F0.x + asset->unk_24.x + temp * asset->unk_54.x +
                                     (arg0 - asset->unk_0C) * asset->unk_48.x),
                           1);
            Matrix_RotateZ(gGfxMatrix,
                           M_DTOR * (D_ending_801985F0.z + asset->unk_24.z + temp * asset->unk_54.z +
                                     (arg0 - asset->unk_0C) * asset->unk_48.z),
                           1);
            break;

        default:
            Matrix_RotateY(
                gGfxMatrix,
                M_DTOR * (asset->unk_24.y + temp * asset->unk_54.y + (arg0 - asset->unk_0C) * asset->unk_48.y), 1);
            Matrix_RotateX(
                gGfxMatrix,
                M_DTOR * (asset->unk_24.x + temp * asset->unk_54.x + (arg0 - asset->unk_0C) * asset->unk_48.x), 1);
            Matrix_RotateZ(
                gGfxMatrix,
                M_DTOR * (asset->unk_24.z + temp * asset->unk_54.z + (arg0 - asset->unk_0C) * asset->unk_48.z), 1);
            break;
    }

    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_END_7010970);
}

void Ending_8018E7B8(u32 arg0, AssetInfo* asset) {
    f32 temp;

    if ((asset->unk_18.z + (arg0 - asset->unk_0C) * asset->unk_3C.z) < D_ending_801985D0.z) {
        RCP_SetupDL(&gMasterDisp, 0x43);
    } else {
        RCP_SetupDL(&gMasterDisp, 0x3F);
    }

    gSPFogPosition(gMasterDisp++, asset->fogNear, asset->fogFar);
    gDPSetFogColor(gMasterDisp++, asset->fogRed, asset->fogGreen, asset->fogBlue, 0);
    gDPSetEnvColor(gMasterDisp++, asset->envRed, asset->envGreen, asset->envBlue, asset->envAlpha);
    gDPSetPrimColor(gMasterDisp++, 0, 0, asset->primRed, asset->primGreen, asset->primBlue, asset->primAlpha);

    Matrix_Translate(gGfxMatrix, asset->unk_18.x + (arg0 - asset->unk_0C) * asset->unk_3C.x,
                     asset->unk_18.y + (arg0 - asset->unk_0C) * asset->unk_3C.y,
                     asset->unk_18.z + (arg0 - asset->unk_0C) * asset->unk_3C.z, 1);

    temp = __sinf(arg0 * 0.1f + asset->unk_70);

    switch (asset->unk_71) {
        case 1:
            Matrix_RotateY(gGfxMatrix,
                           M_DTOR * (-D_ending_801985F0.y + asset->unk_24.y + temp * asset->unk_54.y +
                                     (arg0 - asset->unk_0C) * asset->unk_48.y),
                           1);
            Matrix_RotateX(gGfxMatrix,
                           M_DTOR * (-D_ending_801985F0.x + asset->unk_24.x + temp * asset->unk_54.x +
                                     (arg0 - asset->unk_0C) * asset->unk_48.x),
                           1);
            Matrix_RotateZ(gGfxMatrix,
                           M_DTOR * (D_ending_801985F0.z + asset->unk_24.z + temp * asset->unk_54.z +
                                     (arg0 - asset->unk_0C) * asset->unk_48.z),
                           1);
            break;

        default:
            Matrix_RotateY(
                gGfxMatrix,
                M_DTOR * (asset->unk_24.y + temp * asset->unk_54.y + (arg0 - asset->unk_0C) * asset->unk_48.y), 1);
            Matrix_RotateX(
                gGfxMatrix,
                M_DTOR * (asset->unk_24.x + temp * asset->unk_54.x + (arg0 - asset->unk_0C) * asset->unk_48.x), 1);
            Matrix_RotateZ(
                gGfxMatrix,
                M_DTOR * (asset->unk_24.z + temp * asset->unk_54.z + (arg0 - asset->unk_0C) * asset->unk_48.z), 1);
            break;
    }

    Matrix_Scale(gGfxMatrix, asset->unk_30.x + (arg0 % 3) * 0.5f, asset->unk_30.y + (arg0 % 3) * 0.5f,
                 asset->unk_30.z + (arg0 % 3) * 0.5f, 1);

    Matrix_SetGfxMtx(&gMasterDisp);

    gSPDisplayList(gMasterDisp++, D_END_7010970);
}

void Ending_8018EDB8(u32 arg0, AssetInfo* asset) {
    f32 temp;

    D_ctx_80178410 = 0;

    RCP_SetupDL(&gMasterDisp, asset->unk_08);

    gSPFogPosition(gMasterDisp++, asset->fogNear, asset->fogFar);
    gDPSetFogColor(gMasterDisp++, asset->fogRed, asset->fogGreen, asset->fogBlue, 0);
    gDPSetPrimColor(gMasterDisp++, 0, 0, asset->primRed, asset->primGreen, asset->primBlue, asset->primAlpha);

    Matrix_Translate(gGfxMatrix, asset->unk_18.x + (arg0 - asset->unk_0C) * asset->unk_3C.x,
                     asset->unk_18.y + (arg0 - asset->unk_0C) * asset->unk_3C.y,
                     asset->unk_18.z + (arg0 - asset->unk_0C) * asset->unk_3C.z, 1);

    Matrix_Scale(gGfxMatrix, asset->unk_30.x, asset->unk_30.y, asset->unk_30.z, 1);

    temp = __sinf(arg0 * 0.1f + asset->unk_70);

    Matrix_RotateY(gGfxMatrix,
                   M_DTOR * (asset->unk_24.y + temp * asset->unk_54.y + (arg0 - asset->unk_0C) * asset->unk_48.y), 1);
    Matrix_RotateX(gGfxMatrix,
                   M_DTOR * (asset->unk_24.x + temp * asset->unk_54.x + (arg0 - asset->unk_0C) * asset->unk_48.x), 1);
    Matrix_RotateZ(gGfxMatrix,
                   M_DTOR * (asset->unk_24.z + temp * asset->unk_54.z + (arg0 - asset->unk_0C) * asset->unk_48.z), 1);

    Matrix_SetGfxMtx(&gMasterDisp);

    gDPLoadTextureBlock(gMasterDisp++, D_END_700EA38, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_WRAP | G_TX_NOMIRROR,
                        G_TX_WRAP | G_TX_NOMIRROR, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
    gDPSetupTile(gMasterDisp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, arg0 * 14, 0, G_TX_NOMIRROR | G_TX_WRAP,
                 G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
    gSPDisplayList(gMasterDisp++, D_END_700E9E0);
}

void Ending_8018F2A8(u32 arg0, AssetInfo* asset) {
    f32 temp;

    RCP_SetupDL(&gMasterDisp, asset->unk_08);

    gSPFogPosition(gMasterDisp++, asset->fogNear, asset->fogFar);
    gDPSetFogColor(gMasterDisp++, asset->fogRed, asset->fogGreen, asset->fogBlue, 0);
    gDPSetPrimColor(gMasterDisp++, 0, 0, asset->primRed, asset->primGreen, asset->primBlue, asset->primAlpha);

    Matrix_Translate(gGfxMatrix, asset->unk_18.x + (arg0 - asset->unk_0C) * asset->unk_3C.x,
                     asset->unk_18.y + (arg0 - asset->unk_0C) * asset->unk_3C.y,
                     asset->unk_18.z + (arg0 - asset->unk_0C) * asset->unk_3C.z, 1);

    Matrix_Scale(gGfxMatrix, asset->unk_30.x, asset->unk_30.y, asset->unk_30.z, 1);

    temp = __sinf(arg0 * 0.1f + asset->unk_70);

    Matrix_RotateY(gGfxMatrix,
                   M_DTOR * (asset->unk_24.y + temp * asset->unk_54.y + (arg0 - asset->unk_0C) * asset->unk_48.y), 1);
    Matrix_RotateX(gGfxMatrix,
                   M_DTOR * (asset->unk_24.x + temp * asset->unk_54.x + (arg0 - asset->unk_0C) * asset->unk_48.x), 1);
    Matrix_RotateZ(gGfxMatrix,
                   M_DTOR * (asset->unk_24.z + temp * asset->unk_54.z + (arg0 - asset->unk_0C) * asset->unk_48.z), 1);

    Matrix_SetGfxMtx(&gMasterDisp);

    gCurrentLevel = LEVEL_UNK_M1;

    func_demo_800515C4();
}

void Ending_8018F64C(u32 arg0, AssetInfo* asset) {
    f32 temp;

    if (D_play_800D3180[8] == 0) {
        return;
    }

    RCP_SetupDL(&gMasterDisp, asset->unk_08);

    gSPFogPosition(gMasterDisp++, asset->fogNear, asset->fogFar);
    gDPSetFogColor(gMasterDisp++, asset->fogRed, asset->fogGreen, asset->fogBlue, 0);
    gDPSetEnvColor(gMasterDisp++, asset->envRed, asset->envGreen, asset->envBlue, asset->envAlpha);
    gDPSetPrimColor(gMasterDisp++, 0, 0, asset->primRed, asset->primGreen, asset->primBlue, asset->primAlpha);

    Matrix_Translate(gGfxMatrix, asset->unk_18.x + (arg0 - asset->unk_0C) * asset->unk_3C.x,
                     asset->unk_18.y + (arg0 - asset->unk_0C) * asset->unk_3C.y,
                     asset->unk_18.z + (arg0 - asset->unk_0C) * asset->unk_3C.z, 1);

    Matrix_Scale(gGfxMatrix, asset->unk_30.x, asset->unk_30.y, asset->unk_30.z, 1);

    temp = __sinf(arg0 * 0.1f + asset->unk_70);

    switch (asset->unk_71) {
        case 1:
            Matrix_RotateY(gGfxMatrix,
                           M_DTOR * (-D_ending_801985F0.y + asset->unk_24.y + temp * asset->unk_54.y +
                                     (arg0 - asset->unk_0C) * asset->unk_48.y),
                           1);
            Matrix_RotateX(gGfxMatrix,
                           M_DTOR * (-D_ending_801985F0.x + asset->unk_24.x + temp * asset->unk_54.x +
                                     (arg0 - asset->unk_0C) * asset->unk_48.x),
                           1);
            Matrix_RotateZ(gGfxMatrix,
                           M_DTOR * (D_ending_801985F0.z + asset->unk_24.z + temp * asset->unk_54.z +
                                     (arg0 - asset->unk_0C) * asset->unk_48.z),
                           1);
            break;

        default:
            Matrix_RotateY(
                gGfxMatrix,
                M_DTOR * (asset->unk_24.y + temp * asset->unk_54.y + (arg0 - asset->unk_0C) * asset->unk_48.y), 1);
            Matrix_RotateX(
                gGfxMatrix,
                M_DTOR * (asset->unk_24.x + temp * asset->unk_54.x + (arg0 - asset->unk_0C) * asset->unk_48.x), 1);
            Matrix_RotateZ(
                gGfxMatrix,
                M_DTOR * (asset->unk_24.z + temp * asset->unk_54.z + (arg0 - asset->unk_0C) * asset->unk_48.z), 1);
            break;
    }

    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_D009A40);

    RCP_SetupDL(&gMasterDisp, 0x43);
    Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -60.0f, 1);

    Matrix_Scale(gGfxMatrix, 0.8f + (arg0 % 3) * 0.01f, 0.3f + (arg0 % 3) * 0.01f, 0.8f + (arg0 % 3) * 0.01f, 1);
    Matrix_SetGfxMtx(&gMasterDisp);

    gSPDisplayList(gMasterDisp++, D_END_7010970);
}

void Ending_8018FC60(u32 arg0, AssetInfo* asset) {
    f32 temp;

    if (D_play_800D3180[16] == 0) {
        return;
    }

    RCP_SetupDL(&gMasterDisp, asset->unk_08);

    gSPFogPosition(gMasterDisp++, asset->fogNear, asset->fogFar);
    gDPSetFogColor(gMasterDisp++, asset->fogRed, asset->fogGreen, asset->fogBlue, 0);
    gDPSetEnvColor(gMasterDisp++, asset->envRed, asset->envGreen, asset->envBlue, asset->envAlpha);
    gDPSetPrimColor(gMasterDisp++, 0, 0, asset->primRed, asset->primGreen, asset->primBlue, asset->primAlpha);

    Matrix_Translate(gGfxMatrix, asset->unk_18.x + (arg0 - asset->unk_0C) * asset->unk_3C.x,
                     asset->unk_18.y + (arg0 - asset->unk_0C) * asset->unk_3C.y,
                     asset->unk_18.z + (arg0 - asset->unk_0C) * asset->unk_3C.z, 1);

    Matrix_Scale(gGfxMatrix, asset->unk_30.x, asset->unk_30.y, asset->unk_30.z, 1);

    temp = __sinf(arg0 * 0.1f + asset->unk_70);

    switch (asset->unk_71) {
        case 1:
            Matrix_RotateY(gGfxMatrix,
                           M_DTOR * (-D_ending_801985F0.y + asset->unk_24.y + temp * asset->unk_54.y +
                                     (arg0 - asset->unk_0C) * asset->unk_48.y),
                           1);
            Matrix_RotateX(gGfxMatrix,
                           M_DTOR * (-D_ending_801985F0.x + asset->unk_24.x + temp * asset->unk_54.x +
                                     (arg0 - asset->unk_0C) * asset->unk_48.x),
                           1);
            Matrix_RotateZ(gGfxMatrix,
                           M_DTOR * (D_ending_801985F0.z + asset->unk_24.z + temp * asset->unk_54.z +
                                     (arg0 - asset->unk_0C) * asset->unk_48.z),
                           1);
            break;

        default:
            Matrix_RotateY(
                gGfxMatrix,
                M_DTOR * (asset->unk_24.y + temp * asset->unk_54.y + (arg0 - asset->unk_0C) * asset->unk_48.y), 1);
            Matrix_RotateX(
                gGfxMatrix,
                M_DTOR * (asset->unk_24.x + temp * asset->unk_54.x + (arg0 - asset->unk_0C) * asset->unk_48.x), 1);
            Matrix_RotateZ(
                gGfxMatrix,
                M_DTOR * (asset->unk_24.z + temp * asset->unk_54.z + (arg0 - asset->unk_0C) * asset->unk_48.z), 1);
            break;
    }

    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_D00B880);

    RCP_SetupDL(&gMasterDisp, 0x43);
    Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -50.0f, 1);

    Matrix_Scale(gGfxMatrix, 0.5f + (arg0 % 3) * 0.01f, 0.3f + (arg0 % 3) * 0.01f, 0.5f + (arg0 % 3) * 0.01f, 1);
    Matrix_SetGfxMtx(&gMasterDisp);

    gSPDisplayList(gMasterDisp++, D_END_7010970);
}

void Ending_80190274(u32 arg0, AssetInfo* asset) {
    f32 temp;

    RCP_SetupDL(&gMasterDisp, asset->unk_08);

    gSPFogPosition(gMasterDisp++, asset->fogNear, asset->fogFar);
    gDPSetFogColor(gMasterDisp++, asset->fogRed, asset->fogGreen, asset->fogBlue, 0);
    gDPSetPrimColor(gMasterDisp++, 0, 0, asset->primRed, asset->primGreen, asset->primBlue, asset->primAlpha);

    Matrix_Translate(gGfxMatrix, D_ending_801985D0.x + asset->unk_18.x + (arg0 - asset->unk_0C) * asset->unk_3C.x,
                     D_ending_801985D0.y + asset->unk_18.y + (arg0 - asset->unk_0C) * asset->unk_3C.y,
                     D_ending_801985D0.z + asset->unk_18.z + (arg0 - asset->unk_0C) * asset->unk_3C.z, 1);

    Matrix_Scale(gGfxMatrix, asset->unk_30.x, asset->unk_30.y, asset->unk_30.z, 1);

    temp = __sinf(arg0 * 0.1f + asset->unk_70);

    Matrix_RotateY(gGfxMatrix,
                   M_DTOR * (asset->unk_24.y + temp * asset->unk_54.y + (arg0 - asset->unk_0C) * asset->unk_48.y), 1);
    Matrix_RotateX(gGfxMatrix,
                   M_DTOR * (asset->unk_24.x + temp * asset->unk_54.x + (arg0 - asset->unk_0C) * asset->unk_48.x), 1);
    Matrix_RotateZ(gGfxMatrix,
                   M_DTOR * (asset->unk_24.z + temp * asset->unk_54.z + (arg0 - asset->unk_0C) * asset->unk_48.z), 1);

    Matrix_SetGfxMtx(&gMasterDisp);

    gSPDisplayList(gMasterDisp++, D_END_7004240);
}

void Ending_80190648(s32 arg0, AssetInfo* asset) {
    RCP_SetupDL(&gMasterDisp, asset->unk_08);

    Matrix_RotateY(gGfxMatrix, M_DTOR * D_ending_801985F0.y, 0);
    Matrix_RotateX(gGfxMatrix, M_DTOR * D_ending_801985F0.x, 1);
    Matrix_RotateZ(gGfxMatrix, M_DTOR * D_ending_801985F0.z, 1);

    Matrix_Translate(gGfxMatrix, asset->unk_18.x, asset->unk_18.y, asset->unk_18.z, 1);
    Matrix_Scale(gGfxMatrix, asset->unk_30.x, asset->unk_30.y, asset->unk_30.z, 1);

    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_END_7002120);
}

void Ending_80190778(u32 arg0, AssetInfo* asset) {
    f32 temp;

    RCP_SetupDL(&gMasterDisp, asset->unk_08);

    gSPFogPosition(gMasterDisp++, asset->fogNear, asset->fogFar);
    gDPSetFogColor(gMasterDisp++, asset->fogRed, asset->fogGreen, asset->fogBlue, 0);
    gDPSetEnvColor(gMasterDisp++, asset->envRed, asset->envGreen, asset->envBlue, asset->envAlpha);
    gDPSetPrimColor(gMasterDisp++, 0, 0, asset->primRed, asset->primGreen, asset->primBlue, asset->primAlpha);

    Matrix_Translate(gGfxMatrix, asset->unk_18.x + (arg0 - asset->unk_0C) * asset->unk_3C.x,
                     asset->unk_18.y - 6.0f + (arg0 - asset->unk_0C) * asset->unk_3C.y,
                     asset->unk_18.z + (arg0 - asset->unk_0C) * asset->unk_3C.z, 1);

    Matrix_Scale(gGfxMatrix, asset->unk_30.x, asset->unk_30.y, asset->unk_30.z, 1);

    temp = __sinf(arg0 * 0.2f + asset->unk_70);

    switch (asset->unk_71) {
        case 1:
            Matrix_RotateY(gGfxMatrix,
                           M_DTOR * (-D_ending_801985F0.y + asset->unk_24.y + temp * asset->unk_54.y +
                                     (arg0 - asset->unk_0C) * asset->unk_48.y),
                           1);
            Matrix_RotateX(gGfxMatrix,
                           M_DTOR * (-D_ending_801985F0.x + asset->unk_24.x + temp * asset->unk_54.x +
                                     (arg0 - asset->unk_0C) * asset->unk_48.x),
                           1);
            Matrix_RotateZ(gGfxMatrix,
                           M_DTOR * (D_ending_801985F0.z + asset->unk_24.z + temp * asset->unk_54.z +
                                     (arg0 - asset->unk_0C) * asset->unk_48.z),
                           1);
            break;

        default:
            Matrix_RotateY(
                gGfxMatrix,
                M_DTOR * (asset->unk_24.y + temp * asset->unk_54.y + (arg0 - asset->unk_0C) * asset->unk_48.y), 1);
            Matrix_RotateX(
                gGfxMatrix,
                M_DTOR * (asset->unk_24.x + temp * asset->unk_54.x + (arg0 - asset->unk_0C) * asset->unk_48.x), 1);
            Matrix_RotateZ(
                gGfxMatrix,
                M_DTOR * (asset->unk_24.z + temp * asset->unk_54.z + (arg0 - asset->unk_0C) * asset->unk_48.z), 1);
            break;
    }

    Matrix_Translate(gGfxMatrix, 0.0f, 480.0f, 0.0f, 1);

    Matrix_SetGfxMtx(&gMasterDisp);

    gSPDisplayList(gMasterDisp++, D_arwing_3005AB0);
}

void Ending_80190CF0(u32 arg0, AssetInfo* asset) {
    u8 alpha = 255;
    f32 temp;

    if (D_play_800D2F68 == true) {
        return;
    }

    if (arg0 == asset->unk_0C) {
        AUDIO_PLAY_SFX(0x1940306EU, gDefaultSfxSource, 4U);
    }

    RCP_SetupDL(&gMasterDisp, asset->unk_08);

    gDPSetFogColor(gMasterDisp++, asset->fogRed, asset->fogGreen, asset->fogBlue, 0);
    gDPSetEnvColor(gMasterDisp++, asset->envRed, asset->envGreen, asset->envBlue, asset->envAlpha);

    if ((asset->unk_0C + asset->fogNear) > arg0) {
        alpha = (arg0 - asset->unk_0C) * 255 / asset->fogNear;
    }

    gDPSetPrimColor(gMasterDisp++, 0, 0, asset->primRed, asset->primGreen, asset->primBlue, alpha);

    Matrix_Translate(gGfxMatrix, asset->unk_18.x + (arg0 - asset->unk_0C) * asset->unk_3C.x,
                     asset->unk_18.y + (arg0 - asset->unk_0C) * asset->unk_3C.y,
                     asset->unk_18.z + (arg0 - asset->unk_0C) * asset->unk_3C.z, 1);

    Matrix_Scale(gGfxMatrix, asset->unk_30.x, asset->unk_30.y, asset->unk_30.z, 1);

    temp = __sinf(arg0 * 0.2f + asset->unk_70);

    switch (asset->unk_71) {
        case 1:
            Matrix_RotateY(gGfxMatrix,
                           M_DTOR * (-D_ending_801985F0.y + asset->unk_24.y + temp * asset->unk_54.y +
                                     (arg0 - asset->unk_0C) * asset->unk_48.y),
                           1);
            Matrix_RotateX(gGfxMatrix,
                           M_DTOR * (-D_ending_801985F0.x + asset->unk_24.x + temp * asset->unk_54.x +
                                     (arg0 - asset->unk_0C) * asset->unk_48.x),
                           1);
            Matrix_RotateZ(gGfxMatrix,
                           M_DTOR * (D_ending_801985F0.z + asset->unk_24.z + temp * asset->unk_54.z +
                                     (arg0 - asset->unk_0C) * asset->unk_48.z),
                           1);
            break;

        default:
            Matrix_RotateY(
                gGfxMatrix,
                M_DTOR * (asset->unk_24.y + temp * asset->unk_54.y + (arg0 - asset->unk_0C) * asset->unk_48.y), 1);
            Matrix_RotateX(
                gGfxMatrix,
                M_DTOR * (asset->unk_24.x + temp * asset->unk_54.x + (arg0 - asset->unk_0C) * asset->unk_48.x), 1);
            Matrix_RotateZ(
                gGfxMatrix,
                M_DTOR * (asset->unk_24.z + temp * asset->unk_54.z + (arg0 - asset->unk_0C) * asset->unk_48.z), 1);
            break;
    }

    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_END_7000000);
}

void Ending_80191234(s32 arg0, s32 arg1) {
    D_game_80161A34 = 8;
    gGameState = GSTATE_MENU;
    gNextGameStateTimer = 2;
    gOptionMenuStatus = OPTION_WAIT;
    gDrawMode = DRAW_NONE;
    gBgColor = 0;
    D_ctx_80178410 = 0;
    gControllerLock = 10;
}

void Ending_80191294(u32 arg0, AssetInfo* asset) {
    f32 temp;

    RCP_SetupDL(&gMasterDisp, asset->unk_08);

    gSPFogPosition(gMasterDisp++, asset->fogNear, asset->fogFar);
    gDPSetFogColor(gMasterDisp++, asset->fogRed, asset->fogGreen, asset->fogBlue, 0);
    gDPSetEnvColor(gMasterDisp++, asset->envRed, asset->envGreen, asset->envBlue, asset->envAlpha);
    gDPSetPrimColor(gMasterDisp++, 0, 0, asset->primRed, asset->primGreen, asset->primBlue, asset->primAlpha);

    Matrix_Translate(gGfxMatrix, asset->unk_18.x + (arg0 - asset->unk_0C) * asset->unk_3C.x,
                     asset->unk_18.y + (arg0 - asset->unk_0C) * asset->unk_3C.y,
                     asset->unk_18.z + (arg0 - asset->unk_0C) * asset->unk_3C.z, 1);

    Matrix_Scale(gGfxMatrix, asset->unk_30.x, asset->unk_30.y, asset->unk_30.z, 1);

    temp = __sinf(arg0 * 0.1f + asset->unk_70);

    Matrix_RotateY(gGfxMatrix,
                   M_DTOR * (asset->unk_24.y + temp * asset->unk_54.y + (arg0 - asset->unk_0C) * asset->unk_48.y), 1);
    Matrix_RotateX(gGfxMatrix,
                   M_DTOR * (asset->unk_24.x + temp * asset->unk_54.x + (arg0 - asset->unk_0C) * asset->unk_48.x), 1);
    Matrix_RotateZ(gGfxMatrix,
                   M_DTOR * (asset->unk_24.z + temp * asset->unk_54.z + (arg0 - asset->unk_0C) * asset->unk_48.z), 1);

    Matrix_SetGfxMtx(&gMasterDisp);

    D_ending_80198590.unk_28 = 0.0f;
    D_ending_80198590.unk_10 = D_ending_80198590.unk_28;
    D_ending_80198590.unk_14 = 0.0f;
    D_ending_80198590.unk_0C = D_ending_80198590.unk_10;
    D_ending_80198590.unk_08 = D_ending_80198590.unk_0C;
    D_ending_80198590.unk_04 = D_ending_80198590.unk_08;
    D_ending_80198590.unk_24 = D_ending_80198590.unk_04;
    D_ending_80198590.unk_20 = D_ending_80198590.unk_24;
    D_ending_80198590.unk_1C = D_ending_80198590.unk_20;
    D_ending_80198590.unk_18 = D_ending_80198590.unk_1C;

    if ((arg0 > 520) && (arg0 < 720)) {
        D_ending_80198590.unk_2C = 1;
    } else {
        D_ending_80198590.unk_2C = 0;
    }

    D_ending_80198590.unk_38 = 0.0f;
    D_ending_80198590.unk_30 = +D_ending_801985F0.x;
    D_ending_80198590.unk_34 = -D_ending_801985F0.y;

    func_display_80053658(&D_ending_80198590);
}

void Ending_80191700(u32 arg0, AssetInfo* asset) {
}

void Ending_80191710(u32 arg0, AssetInfo* asset) {
    f32 temp;

    RCP_SetupDL(&gMasterDisp, asset->unk_08);

    gSPFogPosition(gMasterDisp++, asset->fogNear, asset->fogFar);
    gDPSetFogColor(gMasterDisp++, asset->fogRed, asset->fogGreen, asset->fogBlue, 0);
    gDPSetEnvColor(gMasterDisp++, asset->envRed, asset->envGreen, asset->envBlue, asset->envAlpha);
    gDPSetPrimColor(gMasterDisp++, 0, 0, asset->primRed, asset->primGreen, asset->primBlue, asset->primAlpha);

    Matrix_Translate(gGfxMatrix, asset->unk_18.x + (arg0 - asset->unk_0C) * asset->unk_3C.x,
                     asset->unk_18.y + (arg0 - asset->unk_0C) * asset->unk_3C.y,
                     asset->unk_18.z + (arg0 - asset->unk_0C) * asset->unk_3C.z, 1);

    Matrix_Scale(gGfxMatrix, asset->unk_30.x, asset->unk_30.y, asset->unk_30.z, 1);

    temp = __sinf(arg0 * 0.1f + asset->unk_70);

    switch (asset->unk_71) {
        case 1:
            Matrix_RotateY(gGfxMatrix,
                           M_DTOR * (-D_ending_801985F0.y + asset->unk_24.y + temp * asset->unk_54.y +
                                     (arg0 - asset->unk_0C) * asset->unk_48.y),
                           1);
            Matrix_RotateX(gGfxMatrix,
                           M_DTOR * (-D_ending_801985F0.x + asset->unk_24.x + temp * asset->unk_54.x +
                                     (arg0 - asset->unk_0C) * asset->unk_48.x),
                           1);
            Matrix_RotateZ(gGfxMatrix,
                           M_DTOR * (D_ending_801985F0.z + asset->unk_24.z + temp * asset->unk_54.z +
                                     (arg0 - asset->unk_0C) * asset->unk_48.z),
                           1);
            break;

        default:
            Matrix_RotateY(
                gGfxMatrix,
                M_DTOR * (asset->unk_24.y + temp * asset->unk_54.y + (arg0 - asset->unk_0C) * asset->unk_48.y), 1);
            Matrix_RotateX(
                gGfxMatrix,
                M_DTOR * (asset->unk_24.x + temp * asset->unk_54.x + (arg0 - asset->unk_0C) * asset->unk_48.x), 1);
            Matrix_RotateZ(
                gGfxMatrix,
                M_DTOR * (asset->unk_24.z + temp * asset->unk_54.z + (arg0 - asset->unk_0C) * asset->unk_48.z), 1);
            break;
    }

    Matrix_SetGfxMtx(&gMasterDisp);

    gSPDisplayList(gMasterDisp++, asset->unk_00);
}

void Ending_80191C58(u32 arg0, AssetInfo* asset) {
    ((void (*)(u32, AssetInfo*)) asset->unk_04)(arg0, asset);
}

void Ending_80191C7C(u32 arg0, AssetInfo* asset) {
    f32 temp;

    RCP_SetupDL(&gMasterDisp, asset->unk_08);

    gSPFogPosition(gMasterDisp++, asset->fogNear, asset->fogFar);
    gDPSetFogColor(gMasterDisp++, asset->fogRed, asset->fogGreen, asset->fogBlue, 0);
    gDPSetEnvColor(gMasterDisp++, asset->envRed, asset->envGreen, asset->envBlue, asset->envAlpha);
    gDPSetPrimColor(gMasterDisp++, 0, 0, asset->primRed, asset->primGreen, asset->primBlue, asset->primAlpha);

    Matrix_Translate(gGfxMatrix, asset->unk_18.x + (arg0 - asset->unk_0C) * asset->unk_3C.x,
                     asset->unk_18.y + (arg0 - asset->unk_0C) * asset->unk_3C.y,
                     asset->unk_18.z + (arg0 - asset->unk_0C) * asset->unk_3C.z, 1);

    Matrix_Scale(gGfxMatrix, asset->unk_30.x, asset->unk_30.y, asset->unk_30.z, 1);

    temp = __sinf(arg0 * 0.1f + asset->unk_70);

    Matrix_RotateY(gGfxMatrix,
                   M_DTOR * (asset->unk_24.y + temp * asset->unk_54.y + (arg0 - asset->unk_0C) * asset->unk_48.y), 1);
    Matrix_RotateX(gGfxMatrix,
                   M_DTOR * (asset->unk_24.x + temp * asset->unk_54.x + (arg0 - asset->unk_0C) * asset->unk_48.x), 1);
    Matrix_RotateZ(gGfxMatrix,
                   M_DTOR * (asset->unk_24.z + temp * asset->unk_54.z + (arg0 - asset->unk_0C) * asset->unk_48.z), 1);

    Matrix_SetGfxMtx(&gMasterDisp);

    Animation_GetFrameData(asset->unk_00,
                           (u32) ((arg0 + asset->unk_70) * asset->unk_14) % Animation_GetFrameCount(asset->unk_00),
                           D_ending_80198600);
    Animation_DrawSkeleton(0, asset->unk_04, D_ending_80198600, NULL, NULL, NULL, &gIdentityMatrix);
}

void Ending_80192164(u32 arg0) {
    s32 i;

    for (i = 0; i < 94; i++) {
        if ((D_ending_801934B4[i].unk_0C <= arg0) &&
            ((D_ending_801934B4[i].unk_0C + D_ending_801934B4[i].unk_10) > arg0)) {
            Matrix_Push(&gGfxMatrix);
            if ((D_ending_801934B4[i].unk_00 == NULL) && (D_ending_801934B4[i].unk_04 == NULL)) {
                Ending_80191700(arg0, &D_ending_801934B4[i]);
            } else if ((D_ending_801934B4[i].unk_00 != NULL) && (D_ending_801934B4[i].unk_04 == NULL)) {
                Ending_80191710(arg0, &D_ending_801934B4[i]);
            } else if ((D_ending_801934B4[i].unk_00 == NULL) && (D_ending_801934B4[i].unk_04 != NULL)) {
                Ending_80191C58(arg0, &D_ending_801934B4[i]);
            } else if ((D_ending_801934B4[i].unk_00 != NULL) && (D_ending_801934B4[i].unk_04 != NULL)) {
                Ending_80191C7C(arg0, &D_ending_801934B4[i]);
            }
            Matrix_Pop(&gGfxMatrix);
        }
    }
}

void Ending_80192290(u32 arg0, UnkEnd54* unkEnd54) {
    s32 i;

    for (i = 0; i < (arg0 - unkEnd54->unk_00); i++) {
        D_ending_801985E0.x += unkEnd54->unk_18.x - (unkEnd54->unk_24.x * i);
        D_ending_801985E0.y += unkEnd54->unk_18.y - (unkEnd54->unk_24.y * i);
        D_ending_801985E0.z += unkEnd54->unk_18.z - (unkEnd54->unk_24.z * i);
        D_ending_801985D0.x += unkEnd54->unk_3C.x - (unkEnd54->unk_48.x * i);
        D_ending_801985D0.y += unkEnd54->unk_3C.y - (unkEnd54->unk_48.y * i);
        D_ending_801985D0.z += unkEnd54->unk_3C.z - (unkEnd54->unk_48.z * i);
    }
}

void Ending_8019237C(u32 arg0, UnkEnd54* unkEnd54) {
    s32 i;
    s32 j;

    for (i = 0; i < arg0 - unkEnd54->unk_00; i++) {
        if (i < unkEnd54->unk_04 * 1 / 4) {
            j = i;
        } else if (i < (unkEnd54->unk_04 * 2) / 4) {
            j = (unkEnd54->unk_04 * 2) / 4 - i;
        } else if (i < (unkEnd54->unk_04 * 3) / 4) {
            j = -(i - (unkEnd54->unk_04 * 2) / 4);
        } else if (i < (unkEnd54->unk_04 * 4) / 4) {
            j = -((unkEnd54->unk_04 * 2) / 4 - (i - (unkEnd54->unk_04 * 2) / 4));
        }

        D_ending_801985E0.x += unkEnd54->unk_18.x - (unkEnd54->unk_24.x * j);
        D_ending_801985E0.y += unkEnd54->unk_18.y - (unkEnd54->unk_24.y * j);
        D_ending_801985E0.z += unkEnd54->unk_18.z - (unkEnd54->unk_24.z * j);
        D_ending_801985D0.x += unkEnd54->unk_3C.x - (unkEnd54->unk_48.x * j);
        D_ending_801985D0.y += unkEnd54->unk_3C.y - (unkEnd54->unk_48.y * j);
        D_ending_801985D0.z += unkEnd54->unk_3C.z - (unkEnd54->unk_48.z * j);
    }
}

void Ending_801924EC(u32 arg0) {
    s32 i;
    UnkEnd54* unkEnd54 = D_ending_80195F4C;

    for (i = 0; i < ARRAY_COUNT(D_ending_80195F4C); i++, unkEnd54++) {
        if ((unkEnd54->unk_00 <= arg0) && ((unkEnd54->unk_00 + unkEnd54->unk_04) > arg0)) {
            D_ending_801985E0.x = D_ending_801985E0.y = D_ending_801985E0.z = D_ending_801985D0.x =
                D_ending_801985D0.y = D_ending_801985D0.z = 0.0f;

            switch (unkEnd54->unk_08) {
                case 1:
                    Ending_8019237C(arg0, unkEnd54);
                    break;

                default:
                    Ending_80192290(arg0, unkEnd54);
                    break;
            }

            D_ending_801985E0.x += unkEnd54->unk_0C.x;
            D_ending_801985E0.y += unkEnd54->unk_0C.y;
            D_ending_801985E0.z += unkEnd54->unk_0C.z;
            D_ending_801985D0.x += unkEnd54->unk_30.x;
            D_ending_801985D0.y += unkEnd54->unk_30.y;
            D_ending_801985D0.z += unkEnd54->unk_30.z;

            Matrix_LookAt(gGfxMatrix, D_ending_801985D0.x, D_ending_801985D0.y, D_ending_801985D0.z,
                          D_ending_801985E0.x, D_ending_801985E0.y, D_ending_801985E0.z, 0.0f, 1.0f, 0.0f, 1);

            func_play_800B6F50(D_ending_801985D0.x, D_ending_801985D0.y, D_ending_801985D0.z, D_ending_801985E0.x,
                               D_ending_801985E0.y, D_ending_801985E0.z);

            Matrix_GetYRPAngles(gGfxMatrix, &D_ending_801985F0);
            break;
        }
    }
}

void Ending_801926D4(void) {
    gControllerLock = 10000;

    Matrix_Push(&gGfxMatrix);

    Ending_801924EC(D_ending_80192E70);
    Ending_80192164(D_ending_80192E70);

    Matrix_Pop(&gGfxMatrix);

    D_ending_80192E70++;

    if ((0 <= D_ending_80192E70) && (D_ending_80192E70 < 100)) {
        D_ending_80192E70 = 100;
        if (D_ctx_80177824 == 0) {
            D_ending_80198590 = gPlayer[0].wings;
        } else {
            D_ending_80198590.rightState = D_ending_80198590.leftState = 2;
        }
        AUDIO_PLAY_BGM(SEQ_ID_ENDING);
    }

    if ((2790 <= D_ending_80192E70) && (D_ending_80192E70 < 3000)) {
        D_ending_80192E70 = 3099;
    }

    if ((4891 <= D_ending_80192E70) && (D_ending_80192E70 < 4999)) {
        D_ending_80192E70 = 4999;
    }

    if ((5000 <= D_ending_80192E70) && (D_ending_80192E70 < 5096)) {
        D_ending_80192E70 = 5096;
    }
}
