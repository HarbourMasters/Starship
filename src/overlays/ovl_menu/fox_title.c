/*
 * File: fox_title.c
 * System: Title
 * Description: Starfox Title Handler
 */
// #include "prevent_bss_reordering.h"
#include "global.h"
#include "fox_title.h"
#include "assets/ast_title.h"
#include "assets/ast_font.h"

f32 D_menu_801B7BB0;
f32 D_menu_801B7BB4;
f32 D_menu_801B7BB8;
f32 D_menu_801B7BBC;
f32 D_menu_801B7BC0;
f32 D_menu_801B7BC4;
f32 D_menu_801B7BC8;
f32 D_menu_801B7BCC;
s32 D_menu_801B7BD0;
s32 D_menu_801B7BD4;
s32 D_menu_801B7BD8;
f32 D_menu_801B7BDC;
f32 D_menu_801B7BE0;
s32 D_menu_801B7BE4;
f32 D_menu_801B7BE8;
s32 D_menu_801B7BEC;
s32 D_menu_801B7BF0;
f32 D_menu_801B7BF8[10];
f32 D_menu_801B7C20[10];
f32 D_menu_801B7C48[10];
f32 D_menu_801B7C70[10];
s32 D_menu_801B7C98;
s32 D_menu_801B7CA0[10];
s32 D_menu_801B7CC8[10];
s32 D_menu_801B7CF0[10];
s32 D_menu_801B7D18[10];
f32 D_menu_801B7D40[40];
f32 D_menu_801B7DE0[40];
f32 D_menu_801B7E80[40];
f32 D_menu_801B7F20[40];
f32 D_menu_801B7FC0[40];
f32 D_menu_801B8060[40];
s32 D_menu_801B8100;
s32 D_menu_801B8108[40];
s32 D_menu_801B81A8[10][3];
s32 D_menu_801B8220[10];
u8 D_menu_801B8248[10][4];
UNK_TYPE D_menu_801B8270[3];
s32 D_menu_801B827C;
s32 D_menu_801B8280;
s32 D_menu_801B8284;
s32 D_menu_801B8288;
f32 D_menu_801B828C;
f32 D_menu_801B8290;
CameraPoint* D_menu_801B8294;
s32 D_menu_801B8298;
f32 D_menu_801B829C;
f32 D_menu_801B82A0;
f32 D_menu_801B82A4;
s32 D_menu_801B82A8;
s32 D_menu_801B82AC;
s32 D_menu_801B82B0;
s32 D_menu_801B82B4;
s32 D_menu_801B82B8;
s32 D_menu_801B82BC;
s32 D_menu_801B82C0;
s32 D_menu_801B82C4;
f32 D_menu_801B82C8;
f32 D_menu_801B82CC;
f32 D_menu_801B82D0;
f32 D_menu_801B82D4;
f32 D_menu_801B82D8;
f32 D_menu_801B82DC;
f32 D_menu_801B82E0;
f32 D_menu_801B82E4;
f32 D_menu_801B82E8;
f32 D_menu_801B82EC;
f32 D_menu_801B82F0;
f32 D_menu_801B82F4;
s32 D_menu_801B82F8;
s32 D_menu_801B82FC;
s32 D_menu_801B8300;
f32 D_menu_801B8304;
f32 D_menu_801B8308;
f32 D_menu_801B830C;
s32 D_menu_801B8310;
s32 D_menu_801B8314;
s32 D_menu_801B8318;
s32 D_menu_801B831C;
s32 D_menu_801B8320;
s32 D_menu_801B8324;
f32 D_menu_801B8328;
f32 D_menu_801B832C;
f32 D_menu_801B8330;
s32 D_menu_801B8334;
bool D_menu_801B8338;
f32 D_menu_801B833C;
s32 D_menu_801B8340;
s32 D_menu_801B8344;
s32 D_menu_801B8348;
UnkStruct_D_801B8350 D_menu_801B8350[4];
f32 D_menu_801B84D0;
f32 D_menu_801B84D4;
f32 D_menu_801B84D8[3];
UnkStruct_D_menu_801B84E8 D_menu_801B84E8[4];
UnkStruct_D_menu_801B8658 D_menu_801B8658;
UnkStruct_D_menu_801B8688 D_menu_801B8688;
s32 D_menu_801B869C;
s32 D_menu_801B86A0;
s32 D_menu_801B86A4;
f32 D_menu_801B86A8;
f32 D_menu_801B86AC;
f32 D_menu_801B86B0;
f32 D_menu_801B86B4;
f32 D_menu_801B86B8;
f32 D_menu_801B86BC;
f32 D_menu_801B86C0;
f32 D_menu_801B86C4;
f32 D_menu_801B86C8;
f32 D_menu_801B86CC;
f32 D_menu_801B86D0;
f32 D_menu_801B86D4;
f32 D_menu_801B86D8;
f32 D_menu_801B86DC;
Vec3f D_menu_801B86E0[4][50];
s32 D_menu_801B9040;
f32 D_menu_801B9044;
f32 D_menu_801B9048;
f32 D_menu_801B904C;
f32 D_menu_801B9050;
f32 D_menu_801B9054;
f32 D_menu_801B9058;
f32 D_menu_801B905C;
f32 D_menu_801B9060;
f32 D_menu_801B9064;
f32 D_menu_801B9068;
f32 D_menu_801B906C;
f32 D_menu_801B9070;
f32 D_menu_801B9074;
f32 D_menu_801B9078;
f32 D_menu_801B907C;
f32 D_menu_801B9080;
f32 D_menu_801B9084;

typedef struct {
    /* 0x00 */ Animation* unk_0;
    /* 0x04 */ Animation* unk_4;
    /* 0x08 */ Limb** skeleton;
} TitleAnimation; // size = 0x0C

//! TODO: Symbols for segmented addresses
TitleAnimation D_menu_801ADA00[4] = {
    { &D_TITLE_602F8E0, &D_TITLE_6035024, D_TITLE_602FBAC },
    { &D_TITLE_60305C0, &D_TITLE_60338DC, D_TITLE_603088C },
    { &D_TITLE_6031DB8, &D_TITLE_603531C, D_TITLE_6032084 },
    { &D_TITLE_6031120, &D_TITLE_6036278, D_TITLE_60313AC },
};

u16* D_menu_801ADA30[5] = {
    gMsg_ID_10, gMsg_ID_20, gMsg_ID_30, gMsg_ID_40, gMsg_ID_50,
};

void Title_801875E0(void) {
    D_80137E78 = 2;

    gGameFrameCount = 0;

    D_ctx_80177AE0 = 2;

    D_game_80161A34 = 0;
    D_game_800D2870 = 0;

    gMainController = Title_80187ABC();

    gFillScreenRed = 0;
    gFillScreenGreen = 0;
    gFillScreenBlue = 0;
    gFillScreenAlpha = 0;

    gFogRed = 0;
    gFogGreen = 0;
    gFogBlue = 0;

    gBgColor = 0;

    D_menu_801B8284 = 0;
    D_menu_801B82A8 = 0;
    D_menu_801B82AC = 0;

    D_menu_801B833C = 0.0f;

    D_menu_801B82C0 = 0;
    D_menu_801B8280 = 0;

    D_menu_801B7BCC = 255.0f;
    D_menu_801B7BC8 = 255.0f;

    Memory_FreeAll();

    func_play_800A5D6C();
    D_ctx_80178420 = 320.0f;
    D_ctx_80178424 = 240.0f;

    Title_80188010();

    if ((gMainController == -1) || (D_menu_801B827C != 0)) {
        Audio_SetAudioSpec(0, 0x17);
        D_menu_801B82C4 = 0;
        D_menu_801B827C = 0;
    } else {
        Audio_SetAudioSpec(0, 0x16);
        D_menu_801B82C4 = 1;
    }
    gControllerLock = 30;
}

void Title_80187754(void) {
    switch (D_ctx_80177AE0) {
        case 0:
            if (gNextGameStateTimer == 0) {
                gDrawMode = DRAW_NONE;
                D_ctx_80177AE0 = 1;
            }
            break;

        case 1:
            gDrawMode = DRAW_NONE;
            Title_801875E0();
            break;

        case 2:
            gDrawMode = DRAW_TITLE;
            Title_801877F0();
            break;
    }
    gGameFrameCount++;
}

void Title_801877F0(void) {
    if (D_menu_801B82A8 > 0) {
        D_menu_801B82A8 -= 1;
    }

    if (D_menu_801B82AC > 0) {
        D_menu_801B82AC -= 1;
    }

    switch (D_menu_801B82C4) {
        case 7:
            Title_80187B00();
            break;
        case 0:
            Title_801888E8();
            Title_8019111C();
            break;
        case 1:
            Title_8018994C();
            break;
        case 2:
            Title_8018A644();
            break;
        case 3:
            Title_8018ACEC();
            break;
        case 4:
            Title_8018B5C4();
            break;
        case 5:
            Title_8018C644();
            break;
    }
    Title_80190E64();
}

void Title_801878D8(void) {
    switch (D_menu_801B82C4) {
        case 7:
            Title_80187CA8();
            break;

        case 0:
            Title_801918FC();
            Title_80189208();
            Matrix_Pop(&gGfxMatrix);
            Title_8018F680();
            Title_8018F85C();
            Title_8018FC14();
            Title_8018F8E4();
            Title_801918FC();
            Title_8018F77C();
            Matrix_Pop(&gGfxMatrix);
            break;

        case 1:
            if (D_menu_801B8348 != 0) {
                Title_801918FC();
                Title_8018A2F8();
                Matrix_Pop(&gGfxMatrix);
                func_radio_800BB5D0();
                Title_80190C9C();
            }
            Title_8018FF74();
            Title_801906A0();
            break;

        case 2:
            Title_801918FC();
            Title_8018A990();
            Matrix_Pop(&gGfxMatrix);
            if (D_menu_801B8344 != 0) {
                Title_8018FD08();
            }
            break;

        case 3:
            Title_801918FC();
            Title_8018B038();
            Matrix_Pop(&gGfxMatrix);
            break;

        case 4:
            Title_801918FC();
            Title_8018C114();
            Matrix_Pop(&gGfxMatrix);
            Title_80190C9C();
            break;

        case 5:
            Title_801918FC();
            Title_8018CB90();
            Matrix_Pop(&gGfxMatrix);
            break;
    }

    if (D_menu_801B8284 != 0) {
        gFillScreenAlpha = 0;
        gFillScreenRed = 0;
        gFillScreenGreen = 0;
        gFillScreenBlue = 0;
        func_fade_80084688(2, D_menu_801B8284);
    }
}

s32 Title_80187ABC(void) {
    s32 ret = -1;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (gControllerPlugged[i] == 1) {
            ret = i;
            break;
        }
    }

    return ret;
}

void Title_80187B00(void) {
    switch (D_menu_801B82C0) {
        case 0:
            D_menu_801B8288 = 0;
            D_ctx_80178410 = 800;
            D_menu_801B82BC = 450;
            D_menu_801B82C0++;
            D_menu_801B82A8 = 20;
            break;

        case 1:
            if (D_menu_801B82BC != 0) {
                func_play_800B6F50(gCsCamEyeX, gCsCamEyeY, gCsCamEyeZ, gCsCamAtX, gCsCamAtY, gCsCamAtZ);
                D_ctx_8017842C -= 1.0f;
                if (D_menu_801B82BC == 60) {
                    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 60);
                    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 60);
                }
            } else {
                D_ctx_80178410 = 0;
                gRadioState = 0;
                D_menu_801B82C0 = 0;
                gDrawMode = DRAW_NONE;
                Audio_SetAudioSpec(0, 0x16);
                D_menu_801B82C4 = 1;
            }

            if (D_menu_801B8288 == 10) {
                D_menu_801B82BC--;
            }
            break;
    }

    if ((D_menu_801B82A8 == 0) && ((gGameFrameCount % 8U) == 7) && (D_menu_801B8288 < 10)) {
        D_menu_801B8288++;
    }
}

void Title_80187CA8(void) {
    static char D_menu_801ADA44[] = "S T A R F O X     R A N K I N G";

    // LTodo: [HD-Texture] Is Broken
    uint8_t* D_5007690_Data = LOAD_ASSET_RAW(D_5007690);
    s32 temp = 20;
    s32 temp2 = 36;

    RCP_SetupDL(&gMasterDisp, 0x53);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);

    Graphics_DisplaySmallText(temp2, temp, 1.0f, 1.0f, D_menu_801ADA44);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    TextureRect_8bIA(&gMasterDisp, D_5000300, 16, 8, 148.0f, temp, 1.0f, 1.0f);
    TextureRect_8bIA(&gMasterDisp, D_5000200, 16, 8, 164, temp, 1.0f, 1.0f);

    RCP_SetupDL(&gMasterDisp, 0x53);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    TextureRect_8bIA(&gMasterDisp, &D_5007690_Data[48 * 6], 16, 2, 36, 32, 15.2f, 1.0f);
    Title_80187E28();
}

void Title_80187E28(void) {
    s32 temp;
    s32 i;

    RCP_SetupDL(&gMasterDisp, 0x53);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);

    Graphics_DisplaySmallText(94, 38, 1.0f, 1.0f, "RANK");
    Graphics_DisplaySmallText(146, 38, 1.0f, 1.0f, "NAME");
    Graphics_DisplaySmallText(192, 38, 1.0f, 1.0f, "HITS");
    temp = 55;

    for (i = 0; i < D_menu_801B8288; i++) {
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

        Graphics_DisplaySmallNumber(105 - ((func_hud_8008BCBC(i + 1) - 1) * 8), temp, i + 1);

        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);

        Graphics_DisplaySmallText(150, temp, 1.0f, 1.0f, &D_menu_801B8248[i][0]);

        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

        Graphics_DisplaySmallNumber(211 - ((func_hud_8008BCBC(D_menu_801B8220[i]) - 1) * 8), temp, D_menu_801B8220[i]);
        temp += 17;
    }
}

s32 Title_80188010(void) {
    s32 temp1;
    s32 temp2;
    s32 temp3;
    s32 i;
    s32 j;

    for (i = 0; i < 10; i++) {
        D_menu_801B8220[i] = 0;
        for (j = 0; j < 3; j++) {
            D_menu_801B81A8[i][j] = 0;
        }
    }

    for (i = 0; i < 10; i++) {
        D_menu_801B8248[i][0] = gSaveFile.save.data.unk_18[i][0] & 0xFF;
        D_menu_801B8248[i][1] = gSaveFile.save.data.unk_18[i][1] & 0xFF;
        D_menu_801B8248[i][2] = gSaveFile.save.data.unk_18[i][2] & 0xFF;
        D_menu_801B8248[i][3] = '\0';

        temp3 = gSaveFile.save.data.unk_36[i];

        for (j = 0; j < temp3; j++) {
            temp2 = gSaveFile.save.data.unk_5E[i][j].unk_0;
            temp2 |= (gSaveFile.save.data.unk_5E[i][j].unk_C & 1) * 256;

            D_menu_801B8220[i] += temp2;

            D_menu_801B81A8[i][0] += gSaveFile.save.data.unk_5E[i][j].unk_D & 1;
            D_menu_801B81A8[i][1] += gSaveFile.save.data.unk_5E[i][j].unk_F & 1;
            D_menu_801B81A8[i][2] += gSaveFile.save.data.unk_5E[i][j].unk_E & 1;
        }
    }

    temp1 = D_menu_801B8220[0];

    for (i = 1; i < 10; i++) {
        if (temp1 < D_menu_801B8220[i]) {
            temp1 = D_menu_801B8220[i];
        }
    }

    return temp1;
}

void Title_801881FC(void) {
    bool var_a1 = true;
    s32 i;

    for (i = 0; i < 16; i++) {
        if ((i != 14) && (!(gSaveFile.save.data.planet[i].expertMedal & 1))) {
            var_a1 = false;
            break;
        }
    }

    D_menu_801B82BC = 900;

    gRadioState = 0;

    D_menu_801B869C = 255;

    D_ctx_80178410 = 800;

    D_menu_801B9040 = 0;
    D_menu_801B86C8 = 0.0f;
    D_menu_801B86CC = -180.0f;
    D_menu_801B82F8 = 124;
    D_menu_801B82FC = 108;
    D_menu_801B8300 = 75;
    D_menu_801B8304 = 0.0f;
    D_menu_801B8308 = 0.0f;
    D_menu_801B830C = 0.0f;
    D_menu_801B86D0 = -70.0f;
    D_menu_801B86D4 = 22.0f;
    D_menu_801B8310 = 30;
    D_menu_801B8314 = 29;
    D_menu_801B8318 = 40;
    D_menu_801B831C = 6;
    D_menu_801B8320 = 1;
    D_menu_801B8324 = 11;
    D_menu_801B9054 = 26.0f;
    D_menu_801B9058 = 37.0f;
    D_menu_801B9068 = 1.5f;
    D_menu_801B906C = 3.0f;
    D_menu_801B905C = 124.0f;
    D_menu_801B9060 = 242.0f;
    D_menu_801B9064 = 100.0f;

    gFillScreenAlpha = 0;
    gFillScreenRed = 0;
    gFillScreenGreen = 0;
    gFillScreenBlue = 0;

    D_menu_801B86A8 = 0.0f;
    D_menu_801B86AC = 0.0f;
    D_menu_801B86B0 = 430.0f;

    gCsCamAtX = 0.0f;
    gCsCamAtY = 180.0f;
    gCsCamAtZ = 0.0f;

    D_menu_801B829C = 0.0f;
    D_menu_801B82A0 = 1.0f;
    D_menu_801B82A4 = 0.0f;

    D_menu_801B84D4 = 0.5f;

    D_menu_801B84E8[0].unk_00.x = -80.0f;
    D_menu_801B84E8[0].unk_00.y = 220.0f;
    D_menu_801B84E8[0].unk_00.z = -360.0f;
    D_menu_801B84E8[0].unk_0C = 4.0f;
    D_menu_801B84E8[0].unk_18 = 35.0f;
    D_menu_801B84E8[0].unk_1C = -90.0f;
    D_menu_801B84E8[0].unk_20 = -15.0f;
    D_menu_801B84E8[0].unk_24 = 0.0f;
    D_menu_801B84E8[0].unk_28 = 0.0f;
    D_menu_801B84E8[0].unk_2C = 0.0f;
    D_menu_801B84E8[0].unk_30 = 0.0f;
    D_menu_801B84E8[0].unk_34 = 1;
    D_menu_801B84E8[0].unk_3C = 0;
    D_menu_801B84E8[0].unk_40 = 0;
    D_menu_801B84E8[0].unk_48 = 0;

    if (var_a1) {
        D_menu_801B8350[0].unk_00.x = -299.0f;
        D_menu_801B8350[0].unk_00.y = -32.0f;
        D_menu_801B8350[0].unk_00.z = 90.0f;
        D_menu_801B8350[0].unk_48 = -9.660022f;
        D_menu_801B8350[0].unk_4C = 60.330208f;
        D_menu_801B8350[0].unk_50 = 0.00f;
    } else {
        D_menu_801B8350[0].unk_00.x = 33.00f;
        D_menu_801B8350[0].unk_00.y = 23.00f;
        D_menu_801B8350[0].unk_00.z = 4.00f;
        D_menu_801B8350[0].unk_48 = -7.800007f;
        D_menu_801B8350[0].unk_4C = 0.589999f;
        D_menu_801B8350[0].unk_50 = 0.00f;
    }
    D_menu_801B8350[0].unk_30 = 0.0f;
    D_menu_801B8350[0].unk_34 = 0.0f;
    D_menu_801B8350[0].unk_28 = 0.0f;
    D_menu_801B8350[0].unk_2C = 0.0f;
    D_menu_801B8350[0].unk_14 = 150.0f;
    D_menu_801B8350[0].unk_18 = 0.0f;
    D_menu_801B8350[0].unk_1C = 1.0f;
    D_menu_801B8350[0].unk_20 = 0.0f;
    D_menu_801B8350[0].unk_24 = 0.0f;
    D_menu_801B8350[0].unk_54 = 0;
    D_menu_801B8350[0].unk_38 = 0.0f;
    D_menu_801B8350[0].unk_3C = 0.0f;
    D_menu_801B8350[0].unk_40 = 0.0f;
    D_menu_801B8350[0].unk_44 = 0.0f;
    D_menu_801B8350[0].unk_58 = 0;
    D_menu_801B8350[0].unk_5C = 0;

    if (var_a1) {
        D_menu_801B8350[1].unk_00.x = -42.0f;
        D_menu_801B8350[1].unk_00.y = -7.0f;
        D_menu_801B8350[1].unk_00.z = -12.0f;
        D_menu_801B8350[1].unk_48 = -2.009996f;
        D_menu_801B8350[1].unk_4C = 56.90997f;
        D_menu_801B8350[1].unk_50 = 0.00f;
    } else {
        D_menu_801B8350[1].unk_00.x = 147.0f;
        D_menu_801B8350[1].unk_00.y = 18.0f;
        D_menu_801B8350[1].unk_00.z = -32.0f;
        D_menu_801B8350[1].unk_48 = -6.009995f;
        D_menu_801B8350[1].unk_4C = 22.620012f;
        D_menu_801B8350[1].unk_50 = 0.00f;
    }
    D_menu_801B8350[1].unk_30 = 0.0f;
    D_menu_801B8350[1].unk_34 = 0.0f;
    D_menu_801B8350[1].unk_28 = 0.0f;
    D_menu_801B8350[1].unk_2C = 0.0f;
    D_menu_801B8350[1].unk_14 = 180.0f;
    D_menu_801B8350[1].unk_18 = 0.0f;
    D_menu_801B8350[1].unk_1C = 1.0f;
    D_menu_801B8350[1].unk_20 = 0.0f;
    D_menu_801B8350[1].unk_24 = -4.0f;
    D_menu_801B8350[1].unk_54 = 0;
    D_menu_801B8350[1].unk_38 = 0.0f;
    D_menu_801B8350[1].unk_3C = 0.0f;
    D_menu_801B8350[1].unk_40 = 0.0f;
    D_menu_801B8350[1].unk_44 = 0.0f;
    D_menu_801B8350[1].unk_58 = 0;
    D_menu_801B8350[1].unk_5C = 0;

    if (var_a1) {
        D_menu_801B8350[2].unk_00.x = 90.0f;
        D_menu_801B8350[2].unk_00.y = 1.00f;
        D_menu_801B8350[2].unk_00.z = -143.0f;
        D_menu_801B8350[2].unk_48 = -0.500016f;
        D_menu_801B8350[2].unk_4C = -33.31999f;
        D_menu_801B8350[2].unk_50 = 0.00f;
    } else {
        D_menu_801B8350[2].unk_00.x = -143.0f;
        D_menu_801B8350[2].unk_00.y = 22.00f;
        D_menu_801B8350[2].unk_00.z = -57.0f;
        D_menu_801B8350[2].unk_48 = -5.950006f;
        D_menu_801B8350[2].unk_4C = -7.689997f;
        D_menu_801B8350[2].unk_50 = 0.00f;
    }
    D_menu_801B8350[2].unk_30 = 0.0f;
    D_menu_801B8350[2].unk_34 = 0.0f;
    D_menu_801B8350[2].unk_28 = 0.0f;
    D_menu_801B8350[2].unk_2C = 0.0f;
    D_menu_801B8350[2].unk_14 = 130.0f;
    D_menu_801B8350[2].unk_18 = 0.0f;
    D_menu_801B8350[2].unk_1C = 1.0f;
    D_menu_801B8350[2].unk_20 = 0.0f;
    D_menu_801B8350[2].unk_24 = 0.0f;
    D_menu_801B8350[2].unk_54 = 0;
    D_menu_801B8350[2].unk_38 = 0.0f;
    D_menu_801B8350[2].unk_3C = 0.0f;
    D_menu_801B8350[2].unk_40 = 0.0f;
    D_menu_801B8350[2].unk_44 = 0.0f;
    D_menu_801B8350[2].unk_58 = 0;
    D_menu_801B8350[2].unk_5C = 0;

    if (var_a1) {
        D_menu_801B8350[3].unk_00.x = 58.0f;
        D_menu_801B8350[3].unk_00.y = -5.0f;
        D_menu_801B8350[3].unk_00.z = 22.00f;
        D_menu_801B8350[3].unk_48 = -17.899979f;
        D_menu_801B8350[3].unk_4C = -8.890011f;
        D_menu_801B8350[3].unk_50 = 0.00f;
    } else {
        D_menu_801B8350[3].unk_00.x = -50.0f;
        D_menu_801B8350[3].unk_00.y = 25.0f;
        D_menu_801B8350[3].unk_00.z = 15.0f;
        D_menu_801B8350[3].unk_48 = -15.870002f;
        D_menu_801B8350[3].unk_4C = -17.549995f;
        D_menu_801B8350[3].unk_50 = 0.00f;
    }
    D_menu_801B8350[3].unk_30 = 0.0f;
    D_menu_801B8350[3].unk_34 = 0.0f;
    D_menu_801B8350[3].unk_28 = 0.0f;
    D_menu_801B8350[3].unk_2C = 0.0f;
    D_menu_801B8350[3].unk_14 = 140.0f;
    D_menu_801B8350[3].unk_18 = 0.0f;
    D_menu_801B8350[3].unk_1C = 1.0f;
    D_menu_801B8350[3].unk_20 = 0.0f;
    D_menu_801B8350[3].unk_24 = 0.0f;
    D_menu_801B8350[3].unk_54 = 0;
    D_menu_801B8350[3].unk_38 = 0.0f;
    D_menu_801B8350[3].unk_3C = 0.0f;
    D_menu_801B8350[3].unk_40 = 0.0f;
    D_menu_801B8350[3].unk_44 = 0.0f;
    D_menu_801B8350[3].unk_58 = 254;
    D_menu_801B8350[3].unk_5C = 0;

    for (i = 0; i < 4; i++) {
        Animation_GetFrameData(D_menu_801ADA00[i].unk_4,
                               D_menu_801B8350[i].unk_58 % Animation_GetFrameCount(D_menu_801ADA00[i].unk_4),
                               D_menu_801B86E0[i]);
    }

    D_menu_801B86A4 = 0;
    D_menu_801B82B0 = 100;

    AUDIO_PLAY_BGM(SEQ_ID_TITLE);
}

void Title_801888E8(void) {
    f32 temp_fv1;
    s32 i;
    static f32 D_menu_801ADA64[4] = { 10.0f, 20.0f, 20.0f, 20.0f };
    static f32 D_menu_801ADA74[4] = { 2.0f, 5.0f, 4.0f, 4.0f };

    switch (D_menu_801B82C0) {
        case 0:
            Title_801881FC();
            D_menu_801B82CC = 0.04f;
            D_menu_801B82D0 = 0.1f;
            D_menu_801B8340 = 0;
            D_menu_801B82C0++;
            break;

        case 1:
            Math_SmoothStepToF(&D_menu_801B86C8, -10.0f, D_menu_801B82CC, 100.0f, 0.0001f);
            Math_SmoothStepToF(&D_menu_801B86CC, 57.0f, D_menu_801B82CC, 100.0f, 0.0001f);
            Math_SmoothStepToF(&D_menu_801B8304, 13.0f, D_menu_801B82CC, 100.0f, 0.0001f);
            Math_SmoothStepToF(&D_menu_801B8308, 2.0f, D_menu_801B82CC, 100.0f, 0.0001f);
            Math_SmoothStepToF(&D_menu_801B830C, 15.0f, D_menu_801B82CC, 100.0f, 0.0001f);
            D_menu_801B82CC *= 1.04f;

            if (D_menu_801B86CC == 57.0f) {
                D_menu_801B82C0++;
            }
            break;

        case 2:
            if (D_menu_801B82B0 == 0) {
                D_menu_801B82C0++;
            }
            break;

        case 3:
            D_menu_801B82A8 = (s32) (RAND_FLOAT(5.0f) + 1.0f) * 10;
            temp_fv1 = D_menu_801B8340;
            D_menu_801B8350[D_menu_801B8340].unk_5C = 0;
            D_menu_801B8350[D_menu_801B8340].unk_18 = 0.0f;

            if (D_menu_801B8340 == 2) {
                D_menu_801B8350[D_menu_801B8340].unk_58 = 0;
            }

            while (temp_fv1 == D_menu_801B8340) {
                D_menu_801B8340 = RAND_INT(4.0f);
            }

            D_menu_801B8350[D_menu_801B8340].unk_5C = RAND_INT(6.0f) + 5;
            D_menu_801B8350[D_menu_801B8340].unk_54 = 1;

            D_menu_801B82CC = 0.07f;
            D_menu_801B82C0++;
            break;

        case 4:
            if (D_menu_801B82A8 == 0) {
                D_menu_801B8350[D_menu_801B8340].unk_54 = 0;
                Math_SmoothStepToF(&D_menu_801B8350[D_menu_801B8340].unk_18, 0.0f, D_menu_801B82CC, 100.0f, 0.001f);
                D_menu_801B82CC *= 1.07f;

                if (D_menu_801B8350[D_menu_801B8340].unk_18 == 0.0f) {
                    D_menu_801B82C0 = 3;
                }
            }
            break;
    }

    if (D_menu_801B8350[D_menu_801B8340].unk_54 != 0) {
        if ((D_menu_801B8350[D_menu_801B8340].unk_18 + D_menu_801B8350[D_menu_801B8340].unk_1C) < 0.0f) {
            D_menu_801B8350[D_menu_801B8340].unk_1C = D_menu_801ADA74[D_menu_801B8340];
        }

        if ((D_menu_801B8350[D_menu_801B8340].unk_18 + D_menu_801B8350[D_menu_801B8340].unk_1C) >
            D_menu_801ADA64[D_menu_801B8340]) {
            D_menu_801B8350[D_menu_801B8340].unk_1C = -D_menu_801ADA74[D_menu_801B8340];
        }

        D_menu_801B8350[D_menu_801B8340].unk_18 += D_menu_801B8350[D_menu_801B8340].unk_1C;
    }

    if (D_menu_801B82B0 == 0) {
        if (gGameFrameCount & 0x80) {
            if (D_menu_801B8350[1].unk_20 + D_menu_801B8350[1].unk_24 < -20.0f) {
                D_menu_801B8350[1].unk_24 = 4.0f;
            }
            if (D_menu_801B8350[1].unk_20 + D_menu_801B8350[1].unk_24 > 0.0f) {
                D_menu_801B8350[1].unk_24 = -4.0f;
            }
            D_menu_801B8350[1].unk_20 += D_menu_801B8350[1].unk_24;
        } else {
            Math_SmoothStepToF(&D_menu_801B8350[1].unk_20, 0.0f, 0.3f, 100.0f, 0.1f);
        }
    }

    if ((D_menu_801B86A4 >= 3) && (D_menu_801B9040 != 0)) {
        Math_SmoothStepToF(&D_menu_801B86C8, -10.0f, D_menu_801B82D0, 100.0f, 0.0001f);
        Math_SmoothStepToF(&D_menu_801B86CC, 57.0f, D_menu_801B82D0, 100.0f, 0.0001f);
        Math_SmoothStepToF(&D_menu_801B905C, 124.0f, D_menu_801B82D0, 100.0f, 0.0001f);
        Math_SmoothStepToF(&D_menu_801B9060, 242.0f, D_menu_801B82D0, 100.0f, 0.0001f);

        for (i = 0; i < 4; i++) {
            Math_SmoothStepToF(&D_menu_801B8350[i].unk_28, 0.0f, D_menu_801B82D0, 100.0f, 0.01f);
            Math_SmoothStepToF(&D_menu_801B8350[i].unk_2C, 0.0f, D_menu_801B82D0, 100.0f, 0.01f);
            Math_SmoothStepToF(&D_menu_801B8350[i].unk_30, 0.0f, D_menu_801B82D0, 100.0f, 0.01f);
            Math_SmoothStepToF(&D_menu_801B8350[i].unk_34, 0.0f, D_menu_801B82D0, 100.0f, 0.01f);
            Math_SmoothStepToF(&D_menu_801B8350[i].unk_38, 0.0f, D_menu_801B82D0, 100.0f, 0.01f);
            Math_SmoothStepToF(&D_menu_801B8350[i].unk_3C, 0.0f, D_menu_801B82D0, 100.0f, 0.01f);
            Math_SmoothStepToF(&D_menu_801B8350[i].unk_40, 0.0f, D_menu_801B82D0, 100.0f, 0.01f);
            Math_SmoothStepToF(&D_menu_801B8350[i].unk_44, 0.0f, D_menu_801B82D0, 100.0f, 0.01f);
        }

        D_menu_801B82D0 *= 1.1f;

        if ((D_menu_801B905C == 124.0f) && (D_menu_801B9060 == 242.0f)) {
            D_menu_801B9040 = 0;
            D_menu_801B82D0 = 0.08f;
            D_menu_801B86A4 = 0;
        }

        if ((gControllerPress[gMainController].stick_x != 0) || (gControllerPress[gMainController].stick_y != 0)) {
            D_menu_801B82D0 = 0.08f;
        }
    }

    D_menu_801B84E8->unk_18 += 0.6f;

    Title_80191320(1, &gCsCamEyeX, &gCsCamEyeY, &gCsCamEyeZ, &gCsCamAtX, &gCsCamAtY, &gCsCamAtZ, D_menu_801B86A8,
                   D_menu_801B86AC, D_menu_801B86B0);
    func_play_800B6F50(gCsCamEyeX, gCsCamEyeY, gCsCamEyeZ, gCsCamAtX, gCsCamAtY, gCsCamAtZ);

    D_ctx_8017842C -= 0.5f;

    if (D_menu_801B82B0 > 0) {
        D_menu_801B82B0 -= 1;
    }

    if (D_menu_801B9040 == 1) {
        D_menu_801B82BC = 450;
    }

    if (D_menu_801B82BC != 0) {
        D_menu_801B82BC -= 1;
        return;
    }

    D_ctx_80178410 = 0;

    D_menu_801B82C0 = 0;

    gDrawMode = DRAW_NONE;

    D_menu_801B82C4 = 7;
}

void Title_80189208(void) {
    s32 i;
    static s32 D_menu_801ADA84[4] = { 0, 1, 3, 2 };

    gLight1R = D_menu_801B82F8;
    gLight1G = D_menu_801B82FC;
    gLight1B = D_menu_801B8300;
    gAmbientR = D_menu_801B8304;
    gAmbientG = D_menu_801B8308;
    gAmbientB = D_menu_801B830C;

    if ((D_menu_801B86A4 < 2) && (D_menu_801B9040 != 0)) {
        D_menu_801B86D8 = RAD_TO_DEG(Math_Atan2F(-D_menu_801B9060, sqrtf(SQ(-D_menu_801B905C) + SQ(-D_menu_801B9064))));
        D_menu_801B86DC = RAD_TO_DEG(Math_Atan2F(D_menu_801B905C, D_menu_801B9064));

        Math_SmoothStepToF(&D_menu_801B86C8, D_menu_801B86D8, 0.1f, 100.0f, 0.0001f);
        Math_SmoothStepToF(&D_menu_801B86CC, D_menu_801B86DC, 0.1f, 100.0f, 0.0001f);
    }

    Title_80191674(D_menu_801B86C8, D_menu_801B86CC, 100.0f, &D_menu_801B82E0, &D_menu_801B82E4, &D_menu_801B82E8);

    for (i = 0; i < 4; i++) {
        Title_8018EA78(D_menu_801ADA84[i]);
        D_menu_801B8350[D_menu_801ADA84[i]].unk_58 += D_menu_801B8350[D_menu_801ADA84[i]].unk_5C;
    }

    gLight1R = D_menu_801B8310;
    gLight1G = D_menu_801B8314;
    gLight1B = D_menu_801B8318;

    gAmbientR = D_menu_801B831C;
    gAmbientG = D_menu_801B8320;
    gAmbientB = D_menu_801B8324;

    Title_80191674(D_menu_801B86D0, D_menu_801B86D4, 100.0f, &D_menu_801B82E0, &D_menu_801B82E4, &D_menu_801B82E8);

    Title_8018D2B8(0);
}

void Title_801894E8(void) {
    s32 i;

    D_ctx_80178410 = 800;
    D_menu_801B7C98 = 10;

    for (i = 0; i < 10; i++) {
        D_menu_801B7BF8[i] = 10.0f + RAND_FLOAT(10.0f);
        D_menu_801B7C20[i] = -10.0f + RAND_FLOAT(-60.0f);
        D_menu_801B7C48[i] = 0.0f;
        D_menu_801B7C70[i] = 0.1f + RAND_FLOAT(0.3f);
        D_menu_801B7D18[i] = 5 + RAND_INT(5.0f);
        D_menu_801B7CC8[i] = 255;
        D_menu_801B7CF0[i] = 128;
        D_menu_801B7CA0[i] = 0;
    }

    D_menu_801B869C = 255;
    gFillScreenAlpha = 255;
    gFillScreenRed = 0;
    gFillScreenGreen = 0;
    gFillScreenBlue = 0;

    D_menu_801B9070 = 110.0f;
    D_menu_801B9074 = 70.0f;
    D_menu_801B9078 = 1.0f;
    D_menu_801B907C = 1.0f;
    D_menu_801B7BDC = 0.0f;
    D_menu_801B7BE0 = 0.0f;
    D_menu_801B7BD4 = 0;
    D_menu_801B7BD8 = 0;
    D_menu_801B9080 = 0.0f;
    D_menu_801B9084 = 60.0f;
    D_menu_801B7BB0 = 1.0f;
    D_menu_801B7BB4 = 1.0f;
    D_menu_801B7BD0 = 0;
    D_menu_801B7BB8 = -900.0f;
    D_menu_801B7BBC = 205.0f;
    D_menu_801B7BC0 = 10.0f;
    D_menu_801B7BC4 = 10.0f;
    D_menu_801B86C8 = 0.0f;
    D_menu_801B86CC = 162.0f;

    gLight1R = 101;
    gLight1G = 106;
    gLight1B = 92;
    gAmbientR = 3;
    gAmbientG = 4;
    gAmbientB = 10;

    D_menu_801B8688.pos.y = 0.0f;
    D_menu_801B8688.unk_0C = 0;
    D_menu_801B8688.pos.x = -80.0f;
    D_menu_801B8688.pos.z = 500.0f;
    D_menu_801B8688.scale = 5.0f;

    D_menu_801B8348 = 0;

    D_menu_801B8658.pos.x = 20.0f;
    D_menu_801B8658.pos.y = 0.0f;
    D_menu_801B8658.pos.z = 30.0f;
    D_menu_801B8658.angleX = 0.0f;
    D_menu_801B8658.angleY = 0.0f;
    D_menu_801B8658.angleZ = 0.0f;
    D_menu_801B8658.scale = 0.1f;

    D_menu_801B86BC = 0.0f;
    D_menu_801B86C0 = 0.0f;
    D_menu_801B86C4 = 0.0f;
    D_menu_801B86A8 = -10.0f;
    D_menu_801B86AC = 0.0f;

    D_menu_801B86B4 = 1500.0f;
    D_menu_801B86B8 = -100.0f;
    D_menu_801B829C = 0.0f;
    D_menu_801B82A0 = 1.0f;
    D_menu_801B82A4 = 0.0f;

    Title_801914AC(D_menu_801B86BC, D_menu_801B86C0, D_menu_801B86C4, &gCsCamEyeX, &gCsCamEyeY, &gCsCamEyeZ,
                   D_menu_801B86B4, &gCsCamAtX, &gCsCamAtY, &gCsCamAtZ, D_menu_801B86B8, D_menu_801B86A8,
                   D_menu_801B86AC);

    D_menu_801B7BF0 = 0;

    AUDIO_PLAY_BGM(SEQ_ID_OPENING);
}

void Title_8018994C(void) {
    f32 temp;
    f32 temp2;

    switch (D_menu_801B82C0) {
        case 0:
            Title_801894E8();
            D_menu_801B8294 = D_menu_801B6B40;
            D_menu_801B7BE8 = 1.0f;
            D_menu_801B82CC = 0.002f;
            D_menu_801B82C0 = 100;
            D_menu_801B82B8 = 0;

            gRadioState = 0;
            D_ctx_80178300 = 0;
            gCurrentMsgPri = 0;
            break;

        case 100:
            if (gFillScreenAlpha != 0) {
                gFillScreenAlpha -= 5;
            } else {
                D_menu_801B82A8 = 19;
                D_menu_801B82C0 = 1;
            }
            break;

        case 1:
            if (D_menu_801B82A8 == 0) {
                temp2 = Math_SmoothStepToF(&D_menu_801B7BDC, 255.0f, D_menu_801B82CC, 100.0f, 1.0f);
                D_menu_801B82CC *= 1.08f;
                if (temp2 == 0.0f) {
                    D_menu_801B82A8 = 50;
                    D_menu_801B82AC = 85;
                    D_menu_801B82D0 = 0.01f;
                    D_menu_801B82CC = 0.002f;
                    D_menu_801B82C0++;
                }
            }
            break;

        case 2:
            if (D_menu_801B82A8 == 0) {
                Math_SmoothStepToF(&D_menu_801B7BDC, 0.0f, D_menu_801B82D0, 100.0f, 0.1f);
                D_menu_801B82D0 *= 1.06f;
                if (D_menu_801B82AC == 0) {
                    temp2 = Math_SmoothStepToF(&D_menu_801B7BE0, 255.0f, D_menu_801B82CC, 100.0f, 1.0f);
                    D_menu_801B82CC *= 1.08f;
                    if (temp2 == 0.0f) {
                        D_menu_801B82A8 = 30;
                        D_menu_801B82D0 = 0.02f;
                        D_menu_801B82C0++;
                        D_menu_801B7BD8 = 1;
                        gFillScreenAlpha = 0;
                    }
                }
            }
            break;

        case 3:
            if (D_menu_801B82A8 == 0) {
                Math_SmoothStepToF(&D_menu_801B7BE0, 0.0f, D_menu_801B82D0, 100.0f, 0.1f);
                D_menu_801B82D0 *= 1.07f;
                if (D_menu_801B7BB8 < 1200.0f) {
                    D_menu_801B7BB8 += 10.0f;
                    if (D_menu_801B7BB8 > 50.0f) {
                        D_menu_801B7BD4 = 1;
                        D_menu_801B7BDC += 1.8f;
                    }
                } else {
                    D_menu_801B7BD8 = 0;
                    D_menu_801B82C0++;
                }
            }
            break;

        case 4:
            if (D_menu_801B7BDC < 255.0f) {
                D_menu_801B7BDC += 1.0f;
            } else {
                D_menu_801B7BDC = 255.0f;
                D_menu_801B82A8 = 70;
                D_menu_801B82B4 = 0;
                D_menu_801B82D4 = 0.02f;
                D_menu_801B82D8 = 0.00005f;
                D_menu_801B82DC = 0.02f;
                D_menu_801B8298 = 0;
                D_menu_801B828C = 0.0f;
                D_menu_801B8290 = 0.011f;

                gCsCamEyeX = D_menu_801B6B40[0].eye.x;
                gCsCamEyeY = D_menu_801B6B40[0].eye.y;
                gCsCamEyeZ = D_menu_801B6B40[0].eye.z;
                gCsCamAtX = D_menu_801B6B40[0].at.x;
                gCsCamAtY = D_menu_801B6B40[0].at.y;
                gCsCamAtZ = D_menu_801B6B40[0].at.z;

                D_menu_801B82C0 = 10;
            }
            break;

        case 10:
            if (D_menu_801B82B4 == 45) {
                D_menu_801B7BF0 = 1;
            }

            if (D_menu_801B82B4 == 145) {
                D_menu_801B7BF0 = 0;
            }

            if (D_menu_801B82B8 == 638) {
                AUDIO_PLAY_SFX(0x11030010, D_menu_801B8658.unk_24, 0);
                AUDIO_PLAY_SFX(0x31024059, D_menu_801B8658.unk_24, 0);
                Radio_PlayMessage(gMsg_ID_60, RCID_ROB64_TITLE);
            }

            if (D_menu_801B82B8 == 838) {
                Title_801919C4(D_menu_801ADA30, RCID_GEN_PEPPER_TITLE);
            }

            if (D_menu_801B82A8 == 1) {
                D_menu_801B8348 = 1;
            }

            if (D_menu_801B82A8 != 0) {
                break;
            }

            if (D_menu_801B9078 < 1.39f) {
                D_menu_801B9078 += 0.01f;
                D_menu_801B907C += 0.01f;
                D_menu_801B9070 -= 0.5f;
                D_menu_801B9074 -= 0.5f;
            }

            temp = Math_SmoothStepToF(&D_menu_801B7BDC, 0.0f, D_menu_801B82DC, 100.0f, 0.1f);

            D_menu_801B82DC *= 1.06f;

            if (temp == 0.0f) {
                D_menu_801B7BD4 = -1;
            }

            Title_8018CC30(D_menu_801B8294, 12, D_menu_801B8290);

            Title_80191798(&D_menu_801B86A8, &D_menu_801B86AC);
            Title_80191844(D_menu_801B86A8, D_menu_801B86AC);

            if ((D_menu_801B82B8 > 960) && (D_menu_801B7BE8 > 0.0f)) {
                D_menu_801B7BE8 -= 0.0022f;
                if (D_menu_801B7BE8 < 0.0f) {
                    D_menu_801B7BE8 = 0.0f;
                }
            }

            if (D_menu_801B86AC > -100.0f) {
                Math_SmoothStepToF(&D_menu_801B86C8, 15.0f, D_menu_801B82D4, 100.0f, 0.0001f);
                Math_SmoothStepToF(&D_menu_801B86CC, -35.0f, D_menu_801B82D4, 100.0f, 0.0001f);
                D_menu_801B82D4 -= 0.000005f;
            } else {
                Math_SmoothStepToF(&D_menu_801B86C8, -20.0f, D_menu_801B82D8, 100.0f, 0.0001f);
                Math_SmoothStepToF(&D_menu_801B86CC, -25.0f, D_menu_801B82D8, 100.0f, 0.0001f);

                if (D_menu_801B82B4 > 550) {
                    D_menu_801B82D8 += 0.0001f;
                } else {
                    D_menu_801B82D8 += 0.000001f;
                }
            }

            if (D_menu_801B82B4 == 260) {
                D_menu_801B8688.unk_0C = 1;
            }

            if (D_menu_801B82B4 == 750) {
                gFillScreenAlpha = 0;
                gFillScreenRed = 0;
                gFillScreenGreen = 0;
                gFillScreenBlue = 0;
                D_menu_801B869C = 1;
            }

            if (gFillScreenAlpha == 255) {
                Audio_KillSfxBySourceAndId(D_menu_801B8658.unk_24, 0x11030010);
                Audio_KillSfxBySourceAndId(D_menu_801B8658.unk_24, 0x31024059);

                D_menu_801B82C0 = 0;

                gDrawMode = DRAW_NONE;

                D_menu_801B82C4 = 2;
            }
            D_menu_801B82B4++;
            break;
    }

    Title_801912A0();
    Title_80191674(D_menu_801B86C8, D_menu_801B86CC, 100.0f, &D_menu_801B82E0, &D_menu_801B82E4, &D_menu_801B82E8);

    if (D_menu_801B7BE8 != 0) {
        func_play_800B6F50(gCsCamEyeX, gCsCamEyeY, gCsCamEyeZ, gCsCamAtX, gCsCamAtY, gCsCamAtZ);
    }

    D_ctx_8017842C -= D_menu_801B7BE8;
    D_menu_801B82B8++;
}

void Title_8018A2F8(void) {
    if (D_menu_801B8688.unk_0C != 0) {
        Title_8018DF0C(-700.0f);
    }
    Title_8018E058();
}

void Title_8018A338(void) {
    D_ctx_80178410 = 0;

    D_menu_801B869C = 255;

    gFillScreenAlpha = 255;
    gFillScreenRed = 0;
    gFillScreenGreen = 0;
    gFillScreenBlue = 0;

    D_menu_801B8344 = 0;
    D_menu_801B8334 = 0;
    D_menu_801B8338 = 1;

    D_menu_801B8328 = D_menu_801B832C = D_menu_801B8330 = 155.0f;

    D_menu_801B8328 = 77.0f;
    D_menu_801B832C = 77.0f;
    D_menu_801B8330 = 77.0f;

    D_menu_801B86C8 = 0.0f;
    D_menu_801B86CC = -90.0f;
    D_menu_801B82F8 = 76;
    D_menu_801B82FC = 45;
    D_menu_801B8300 = 66;
    D_menu_801B8304 = 11.0f;
    D_menu_801B8308 = 1.0f;
    D_menu_801B830C = 1.0f;
    D_menu_801B84D4 = 0.5f;

    D_menu_801B8350[0].unk_00.x = -20.0f;
    D_menu_801B8350[0].unk_00.y = 0.0f;
    D_menu_801B8350[0].unk_00.z = -600.0f;
    D_menu_801B8350[0].unk_0C = 0.0f;
    D_menu_801B8350[0].unk_10 = 3.0f;
    D_menu_801B8350[0].unk_58 = 14;
    D_menu_801B8350[0].unk_5C = 5;

    D_menu_801B8350[1].unk_00.x = -209.0f;
    D_menu_801B8350[1].unk_00.y = 0.0f;
    D_menu_801B8350[1].unk_00.z = -820.0f;
    D_menu_801B8350[1].unk_0C = 0.0f;
    D_menu_801B8350[1].unk_10 = 3.0f;
    D_menu_801B8350[1].unk_58 = 0;
    D_menu_801B8350[1].unk_5C = 5;

    D_menu_801B8350[2].unk_00.x = 62.0f;
    D_menu_801B8350[2].unk_00.y = 0.0f;
    D_menu_801B8350[2].unk_00.z = -813.0f;
    D_menu_801B8350[2].unk_0C = 0.0f;
    D_menu_801B8350[2].unk_10 = 3.0f;
    D_menu_801B8350[2].unk_58 = 29;
    D_menu_801B8350[2].unk_5C = 6;

    D_menu_801B8350[3].unk_00.x = 183.0f;
    D_menu_801B8350[3].unk_00.y = 0.0f;
    D_menu_801B8350[3].unk_00.z = -990.0f;
    D_menu_801B8350[3].unk_0C = 0.0f;
    D_menu_801B8350[3].unk_10 = 3.0f;
    D_menu_801B8350[3].unk_58 = 41;
    D_menu_801B8350[3].unk_5C = 7;

    D_menu_801B84D0 = -6000.0f;
    D_menu_801B86BC = 22.0f;
    D_menu_801B86C0 = 116.0f;
    D_menu_801B86C4 = -543.0f;
    D_menu_801B86A8 = 3.0f;
    D_menu_801B86AC = 7.0f;
    D_menu_801B86B4 = 400.0f;
    D_menu_801B86B8 = -100.0f;
    D_menu_801B829C = 0.0f;
    D_menu_801B82A0 = 1.0f;
    D_menu_801B82A4 = 0.0f;

    Title_801914AC(D_menu_801B86BC, D_menu_801B86C0, D_menu_801B86C4, &gCsCamEyeX, &gCsCamEyeY, &gCsCamEyeZ,
                   D_menu_801B86B4, &gCsCamAtX, &gCsCamAtY, &gCsCamAtZ, D_menu_801B86B8, D_menu_801B86A8,
                   D_menu_801B86AC);
}

static CameraPoint D_menu_801ADA94[50] = {
    { 70.68093f, 95.06561f, -146.52567f, 9.829767f, 121.2336f, -642.1186f },
    { 205.506f, 142.9332f, -268.0091f, 168.6235f, 176.76671f, -765.49774f },
    { 247.74275f, 218.72449f, -519.0222f, 186.81432f, 211.56888f, -1015.24445f },
    { 154.73712f, 157.72694f, -740.8712f, 222.56572f, 143.06827f, -1236.0322f },
    { 135.52502f, 142.27957f, -793.6749f, 316.11874f, 98.18011f, -1257.8313f },
    { 138.90092f, 142.27957f, -860.379f, 315.27478f, 98.18011f, -1326.1553f },
    { 136.89713f, 214.43028f, -731.92285f, 283.27573f, 80.142426f, -1190.7693f },
    { 120.86948f, 242.49208f, -629.05237f, 262.28262f, 73.12698f, -1077.7369f },
    { 50.869476f, 242.49208f, -553.05237f, 192.28262f, 73.12698f, -1001.7369f },
    { -16.4814f, 233.25653f, -604.46075f, 187.87035f, 75.43587f, -1032.6348f },
    { -13.395493f, 191.66321f, -629.1167f, 204.59888f, 85.8342f, -1066.4708f },
    { -41.594223f, 184.11728f, -669.04443f, 256.64856f, 100.22068f, -1061.4889f },
    { -87.65735f, 182.94937f, -639.51697f, 274.41434f, 89.26266f, -971.3707f },
    { -215.5498f, 103.66844f, -641.08514f, 160.13745f, 109.082886f, -970.9787f },
    { -185.00772f, 8.353668f, -560.10535f, 28.75193f, 144.16159f, -991.2237f },
    { -91.497696f, 107.96538f, -610.0586f, -332.12558f, 199.25865f, -1038.7354f },
    { -84.526764f, 188.95499f, -642.84845f, -400.11832f, 179.01125f, -1030.5378f },
    { -103.5627f, 179.47885f, -668.8744f, -420.3593f, 197.6303f, -1055.2814f },
    { -109.0918f, 185.47885f, -678.64606f, -440.22705f, 203.6303f, -1052.8385f },
    { -78.15802f, 293.8913f, -640.17566f, -433.1684f, 30.021736f, -1045.5648f },
    { 87.70392f, 358.64935f, -198.21808f, -424.1852f, 182.75551f, -1062.7589f },
    { 68.50934f, 201.02536f, -339.22345f, -376.33456f, 178.32996f, -1063.1702f },
    { 64.247314f, 160.06393f, -446.7345f, -383.97687f, 209.50546f, -1058.4948f },
    { 57.03543f, 138.23148f, -443.5014f, -281.83368f, 268.09802f, -1018.5687f },
    { 0.701339f, 230.27605f, -198.30273f, -0.12092f, 252.22827f, -877.9478f },
    { -313.9902f, 273.13742f, -157.31583f, -0.190525f, 139.842f, -687.0914f },
    { -436.74377f, 352.97644f, -269.34598f, 53.6931f, 105.91397f, -809.0976f },
    { -501.5115f, 422.98685f, -410.4659f, 61.23355f, 96.697556f, -858.7441f },
    { -597.8429f, 475.272f, -752.4272f, 76.44749f, 88.40118f, -816.1725f },
    { -536.05865f, 387.8474f, -1155.2682f, 68.51621f, 100.70934f, -774.557f },
    { -406.2596f, 192.84035f, -1361.467f, 49.143227f, 129.81488f, -743.781f },
    { -387.7423f, 192.84035f, -1374.6389f, 46.379448f, 129.81488f, -741.81506f },
    { -368.49048f, 192.84035f, -1387.3623f, 43.506042f, 129.81488f, -739.9161f },
    { -357.60858f, 192.84035f, -1394.141f, 41.881878f, 129.81488f, -738.9043f },
};

void Title_8018A644(void) {
    static s32 D_menu_801ADF44[] = { 63, 170, 268, 368 };

    switch (D_menu_801B82C0) {
        case 0:
            Title_8018A338();
            AUDIO_PLAY_SFX(0x49000014, gDefaultSfxSource, 4);
            AUDIO_PLAY_SFX(0x0140001C, D_menu_801B84D8, 0);

            D_menu_801B82B4 = 0;
            D_menu_801B82C8 = 0.0f;
            D_menu_801B7BEC = 0;
            D_menu_801B82C0++;
            break;

        case 1:
            if (D_menu_801B82B4 == 20) {
                D_menu_801B869C = 0;
            }

            if (D_menu_801B84D0 != 0.0f) {
                Math_SmoothStepToF(&D_menu_801B84D0, 0.0f, 0.09f, 70.0f, 1.0f);
            }

            if (D_menu_801B84D0 == 0.0f) {
                D_menu_801B82B4 = 0;
                D_menu_801B8340 = 0;
                D_menu_801B8294 = D_menu_801ADA94;
                D_menu_801B8298 = 0;
                D_menu_801B828C = 0.0f;
                D_menu_801B8290 = 0.06f;
                D_menu_801B82C0++;
            }
            D_menu_801B82B4++;
            break;

        case 2:
            Title_80191798(&D_menu_801B86A8, &D_menu_801B86AC);
            Title_80191844(D_menu_801B86A8, D_menu_801B86AC);
            Title_8018CC30(D_menu_801B8294, 34, D_menu_801B8290);

            if (D_menu_801B82B4 == D_menu_801ADF44[D_menu_801B8340]) {
                D_menu_801B8344 = 1;
                D_menu_801B82A8 = 40;
                D_menu_801B82C0 = 3;
            }

            if (D_menu_801B82B4 == 475) {
                D_menu_801B869C = 1;
            }

            if (D_menu_801B7BEC == 795) {
                Audio_KillSfxById(0x49000014);
                Audio_KillSfxBySourceAndId(D_menu_801B84D8, 0x0140001C);

                D_menu_801B82C0 = 0;

                gDrawMode = DRAW_NONE;

                D_menu_801B82C4 = 3;
            }
            D_menu_801B82B4++;
            break;

        case 3:
            if (D_menu_801B82A8 == 0) {
                D_menu_801B8344 = 0;
                D_menu_801B82C0 = 2;
                D_menu_801B8340++;
            }
            break;
    }

    Title_801912A0();
    Title_80191674(D_menu_801B86C8, D_menu_801B86CC, 100.0f, &D_menu_801B82E0, &D_menu_801B82E4, &D_menu_801B82E8);

    D_menu_801B7BEC++;
}

void Title_8018A990(void) {
    s32 i;
    static UnkStruct_D_menu_801ADF54 D_menu_801ADF54[4] = {
        { 255.0f, 155.0f, 155.0f },
        { 155.0f, 255.0f, 155.0f },
        { 135.0f, 206.0f, 255.0f },
        { 255.0f, 255.0f, 155.0f },
    };

    if ((gGameFrameCount % 8U) == 7) {
        if (D_menu_801B8338 != 0) {
            D_menu_801B8334 = (D_menu_801B8334 + 1) % 4U;
            D_menu_801B8328 = D_menu_801ADF54[D_menu_801B8334].unk_0;
            D_menu_801B832C = D_menu_801ADF54[D_menu_801B8334].unk_4;
            D_menu_801B8330 = D_menu_801ADF54[D_menu_801B8334].unk_8;
        } else {
            D_menu_801B8328 = 155.0f;
            D_menu_801B832C = 155.0f;
            D_menu_801B8330 = 155.0f;
        }
        D_menu_801B8338 ^= 1;
    }

    if ((gGameFrameCount % 2) != 0) {
        D_menu_801B86CC += 30.0f;
        if (D_menu_801B86CC > 90.0f) {
            D_menu_801B86CC = -90.0f;
        }
    }

    gAmbientR = D_menu_801B8328;
    gAmbientG = D_menu_801B832C;
    gAmbientB = D_menu_801B8330;

    Title_8018F438();

    gLight1R = D_menu_801B82F8;
    gLight1G = D_menu_801B82FC;
    gLight1B = D_menu_801B8300;
    gAmbientR = D_menu_801B8304;
    gAmbientG = D_menu_801B8308;
    gAmbientB = D_menu_801B830C;

    for (i = 0; i < 4; i++) {
        Title_8018E67C(i);
        D_menu_801B8350[i].unk_58 += D_menu_801B8350[i].unk_5C;
    }
}

void Title_8018ABC0(void) {
    D_ctx_80178410 = 800;

    D_menu_801B869C = 255;

    gFillScreenAlpha = 0;
    gFillScreenRed = 0;
    gFillScreenGreen = 0;
    gFillScreenBlue = 0;
    gLight1R = 101;
    gLight1G = 106;
    gLight1B = 92;
    gAmbientR = 3;
    gAmbientG = 4;
    gAmbientB = 10;

    D_menu_801B86A8 = 10.0f;
    D_menu_801B86AC = -30.0f;
    D_menu_801B86B0 = 450.0f;
    D_menu_801B86C8 = 0.0f;
    D_menu_801B86CC = 0.0f;

    gCsCamAtX = -10.0f;
    gCsCamAtY = 0.0f;
    gCsCamAtZ = 0.0f;

    D_menu_801B829C = 0.0f;
    D_menu_801B82A0 = 1.0f;
    D_menu_801B82A4 = 0.0f;

    D_menu_801B8658.pos.x = 0.0f;
    D_menu_801B8658.pos.y = 0.0f;
    D_menu_801B8658.pos.z = 0.0f;
    D_menu_801B8658.angleX = 0.0f;
    D_menu_801B8658.angleY = 0.0f;
    D_menu_801B8658.angleZ = 0.0f;
}

void Title_8018ACEC(void) {
    switch (D_menu_801B82C0) {
        case 0:
            Title_8018ABC0();
            AUDIO_PLAY_SFX(0x11030010, D_menu_801B8658.unk_24, 0);
            AUDIO_PLAY_SFX(0x31024059, D_menu_801B8658.unk_24, 0);

            D_menu_801B82CC = 0.01f;
            D_menu_801B82B4 = 0;
            D_menu_801B82C0++;
            break;

        case 1:
            Math_SmoothStepToF(&D_menu_801B86A8, 30.0f, D_menu_801B82CC, 100.0f, 0.0001f);
            Math_SmoothStepToF(&D_menu_801B86AC, -15.0f, D_menu_801B82CC, 100.0f, 0.0001f);
            Math_SmoothStepToF(&gCsCamAtX, 0.0f, 0.05f, 100.0f, 0.0001f);
            Math_SmoothStepToF(&gCsCamAtY, -40.0f, D_menu_801B82CC, 100.0f, 0.0001f);
            Math_SmoothStepToF(&D_menu_801B86B0, 100.0f, D_menu_801B82CC, 100.0f, 0.0001f);

            D_menu_801B82CC *= 1.04f;
            if (D_menu_801B82B4 == 50) {
                D_menu_801B869C = 1;
            }

            if (gFillScreenAlpha == 255) {
                Audio_KillSfxBySourceAndId(D_menu_801B8658.unk_24, 0x11030010);
                Audio_KillSfxBySourceAndId(D_menu_801B8658.unk_24, 0x31024059);

                gDrawMode = DRAW_NONE;

                D_menu_801B82C0 = 0;
                D_menu_801B82C4 = 4;
            }
            Title_801912A0();
            D_menu_801B82B4++;
            break;
    }

    Title_80191320(1, &gCsCamEyeX, &gCsCamEyeY, &gCsCamEyeZ, &gCsCamAtX, &gCsCamAtY, &gCsCamAtZ, D_menu_801B86A8,
                   D_menu_801B86AC, D_menu_801B86B0);
    Title_80191674(D_menu_801B86C8, D_menu_801B86CC, 100.0f, &D_menu_801B82E0, &D_menu_801B82E4, &D_menu_801B82E8);
    func_play_800B6F50(gCsCamEyeX, gCsCamEyeY, gCsCamEyeZ, gCsCamAtX, gCsCamAtY, gCsCamAtZ);

    D_ctx_8017842C += 2.0f;
    D_ctx_80178430 += 2.0f;
}

void Title_8018B038(void) {
    Title_8018E058();
}

void Title_8018B058(void) {
    f32 var_fv0;
    s32 i;

    D_menu_801B7C98 = 10;

    for (i = 0; i < 10; i++) {
        D_menu_801B7BF8[i] = 10.0f + RAND_FLOAT(10.0f);
        D_menu_801B7C20[i] = -10.0f + RAND_FLOAT(-60.0f);
        D_menu_801B7C48[i] = 0.0f;
        D_menu_801B7C70[i] = 0.1f + RAND_FLOAT(0.3f);
        D_menu_801B7D18[i] = 5 + RAND_INT(5.0f);
        D_menu_801B7CC8[i] = 255;
        D_menu_801B7CF0[i] = 128;
        D_menu_801B7CA0[i] = 0;
    }

    D_menu_801B8100 = 20;

    for (i = 0; i < D_menu_801B8100; i++) {
        D_menu_801B7D40[i] = -RAND_FLOAT(22.0f) + 13.0f;
        D_menu_801B7DE0[i] = 5.0f - RAND_FLOAT(10.0f);
        D_menu_801B7E80[i] = -25.0f - RAND_FLOAT(15.0f);
        D_menu_801B7FC0[i] = 0.0f;
        D_menu_801B8060[i] = RAND_FLOAT(0.04f);
        D_menu_801B7F20[i] = 0.02f + RAND_FLOAT(0.08f);
        D_menu_801B8108[i] = 0;
    }

    D_menu_801B869C = 255;

    gFillScreenAlpha = 0;
    gFillScreenRed = 255;
    gFillScreenGreen = 255;
    gFillScreenBlue = 255;
    D_ctx_80178410 = 0;

    D_menu_801B8334 = 0;
    D_menu_801B8338 = 1;
    D_menu_801B86C8 = -360.0f;
    D_menu_801B86CC = 131.0f;

    gLight1R = 90;
    gLight1G = 75;
    gLight1B = 90;
    gAmbientR = 45;
    gAmbientG = 34;
    gAmbientB = 56;

    D_menu_801B8688.pos.x = 0.0f;
    D_menu_801B8688.pos.y = 0.0f;
    D_menu_801B8688.pos.z = 1000.0f;
    D_menu_801B8688.scale = 2.0f;
    D_menu_801B8688.unk_0C = 0;

    D_menu_801B7BE4 = 1;

    var_fv0 = -120.0f;

    for (i = 0; i < 4; i++, var_fv0 += 75.0f) {
        D_menu_801B84E8[i].unk_00.x = var_fv0;
        D_menu_801B84E8[i].unk_00.y = 0.0f;
        D_menu_801B84E8[i].unk_00.z = 0.0f;
        D_menu_801B84E8[i].unk_0C = 0.5f;
        D_menu_801B84E8[i].unk_18 = 0.0f;
        D_menu_801B84E8[i].unk_1C = 0.0f;
        D_menu_801B84E8[i].unk_20 = 0.0f;
        D_menu_801B84E8[i].unk_24 = -60.0f;
        D_menu_801B84E8[i].unk_28 = -10.0f;
        D_menu_801B84E8[i].unk_2C = 0.0f;
        D_menu_801B84E8[i].unk_30 = 0.0f;
        D_menu_801B84E8[i].unk_34 = 4 - i;

        D_menu_801B84E8[i].unk_3C = 0;
        D_menu_801B84E8[i].unk_40 = 0;
        D_menu_801B84E8[i].unk_44 = 0.0f;
        D_menu_801B84E8[i].unk_10 = 0.05f;

        D_menu_801B84E8[i].unk_48 = 1;
        D_menu_801B84E8[i].unk_4C = 1;
    }

    D_menu_801B86BC = 140.0f;
    D_menu_801B86C0 = -20.0f;
    D_menu_801B86C4 = 0.0f;
    D_menu_801B86A8 = 0.0f;
    D_menu_801B86AC = 90.0f;
    D_menu_801B86B4 = 90.0f;
    D_menu_801B86B8 = -50.0f;
    D_menu_801B829C = 0.0f;
    D_menu_801B82A0 = 1.0f;
    D_menu_801B82A4 = 0.0f;

    Title_801914AC(D_menu_801B86BC, D_menu_801B86C0, D_menu_801B86C4, &gCsCamEyeX, &gCsCamEyeY, &gCsCamEyeZ,
                   D_menu_801B86B4, &gCsCamAtX, &gCsCamAtY, &gCsCamAtZ, D_menu_801B86B8, D_menu_801B86A8,
                   D_menu_801B86AC);

    D_menu_801B9044 = 25.0f;
    D_menu_801B9048 = 84.0f;
    D_menu_801B904C = -20.0f;
    D_menu_801B9050 = -33.0f;
}

void Title_8018B5C4(void) {
    s32 i;
    f32 temp[4];

    switch (D_menu_801B82C0) {
        case 0:
            D_menu_801B7BEC = 0;

            Title_8018B058();
            Audio_SetBaseSfxReverb(0x68);

            D_menu_801B82A8 = 30;

            D_menu_801B84E8[3].unk_38 = 70;
            D_menu_801B84E8[2].unk_38 = 102;
            D_menu_801B84E8[1].unk_38 = 132;
            D_menu_801B84E8[0].unk_38 = 171;

            D_menu_801B8294 = D_menu_801B6C60;
            D_menu_801B8298 = 0;
            D_menu_801B828C = 0.0f;
            D_menu_801B8290 = 0.024f;
            D_menu_801B82C0 = 10;
            break;

        case 10:
            if (D_menu_801B82A8 == 0) {
                AUDIO_PLAY_SFX(0x0100001D, gDefaultSfxSource, 4);
                D_menu_801B82B4 = 0;
                D_menu_801B82C0 = 1;
            }
            break;

        case 1:
            Title_80191798(&D_menu_801B86A8, &D_menu_801B86AC);
            Title_80191844(D_menu_801B86A8, D_menu_801B86AC);
            Title_8018CC30(D_menu_801B8294, 10, D_menu_801B8290);

            if (D_menu_801B9048 > 0.0f) {
                D_menu_801B9048 -= 0.41f;
                if (D_menu_801B9048 < 0.0f) {
                    D_menu_801B9048 = 0.0f;
                    AUDIO_PLAY_SFX(0x09002013, gDefaultSfxSource, 4);
                }
            }

            if (D_menu_801B82B4 == 60) {
                D_menu_801B7BF0 = 2;
            }

            for (i = 3; i >= 0; i--) {
                if (D_menu_801B84E8[i].unk_38 > 0) {
                    D_menu_801B84E8[i].unk_38--;
                }

                if (D_menu_801B84E8[i].unk_38 == 1) {
                    AUDIO_PLAY_SFX(0x1950107A, D_menu_801B84E8[i].unk_50, 0);
                };

                if (D_menu_801B84E8[i].unk_38 == 0) {
                    Math_SmoothStepToF(&D_menu_801B84E8[i].unk_28, 0.0f, D_menu_801B84E8[i].unk_10, 100.0f, 0.01f);
                    temp[i] = Math_SmoothStepToF(&(D_menu_801B84E8[i].unk_24), 0.0f, D_menu_801B84E8[i].unk_10, 100.0f,
                                                 0.01f);
                    D_menu_801B84E8[i].unk_10 *= 1.04f;
                    if (temp[i] == 0.0f) {
                        Audio_KillSfxBySourceAndId(D_menu_801B84E8[i].unk_50, 0x1950107A);
                    }
                }
            }

            if (D_menu_801B82B4 == 70) {
                D_menu_801B7BE4 = 0;
                D_menu_801B84E8[0].unk_4C = 0;
            }

            if (D_menu_801B82B4 == 80) {
                D_menu_801B84E8[1].unk_4C = 0;

                for (i = 0; i < 4; i++) {
                    D_menu_801B84E8[i].unk_48 = 0;
                }
            }

            if (D_menu_801B82B4 == 115) {
                D_menu_801B84E8[0].unk_4C = 1;
                D_menu_801B84E8[1].unk_4C = 1;
            }

            if (D_menu_801B82B4 == 226) {
                D_menu_801B7BF0 = 0;

                AUDIO_PLAY_SFX(0x0100001E, D_menu_801B84E8[3].unk_50, 0);

                D_menu_801B86BC = 105.0f;
                D_menu_801B86C0 = 0.0f;
                D_menu_801B86C4 = -12.0f;
                D_menu_801B86A8 = 9.4f;
                D_menu_801B86AC = 110.0f;
                D_menu_801B86B4 = 36.0f;
                D_menu_801B86B8 = -70.0f;

                Title_801914AC(D_menu_801B86BC, D_menu_801B86C0, D_menu_801B86C4, &gCsCamEyeX, &gCsCamEyeY, &gCsCamEyeZ,
                               D_menu_801B86B4, &gCsCamAtX, &gCsCamAtY, &gCsCamAtZ, D_menu_801B86B8, D_menu_801B86A8,
                               D_menu_801B86AC);

                D_menu_801B82B4 = 0;

                D_menu_801B84E8[3].unk_44 = 0.0f;

                D_menu_801B86C8 = 60.0f;
                D_menu_801B86CC = 0.0f;
                D_menu_801B82EC = 60.0f;
                D_menu_801B82F0 = 45.0f;
                D_menu_801B82F4 = 60.0f;

                gLight1R = D_menu_801B82EC;
                gLight1G = D_menu_801B82F0;
                gLight1B = D_menu_801B82F4;

                gAmbientR = 35;
                gAmbientG = 24;
                gAmbientB = 46;

                D_menu_801B82C0++;
            }
            D_menu_801B82B4++;
            break;

        case 2:
            if (D_menu_801B82B4 == 30) {
                D_menu_801B84E8[3].unk_40 = 1;
            }

            if (D_menu_801B82B4 == 40) {
                D_menu_801B84E8[3].unk_3C = 1;
            }

            if (D_menu_801B82B4 > 40) {
                D_menu_801B84E8[3].unk_44 += 0.002f;

                if (D_menu_801B84E8[3].unk_44 > 0.2f) {
                    D_menu_801B84E8[3].unk_44 = 0.2f;
                }

                Math_SmoothStepToF(&D_menu_801B82EC, 240.0f, 0.06f, 2.0f, 0.01f);
                Math_SmoothStepToF(&D_menu_801B82F0, 240.0f, 0.06f, 2.0f, 0.01f);
                Math_SmoothStepToF(&D_menu_801B82F4, 255.0f, 0.06f, 2.0f, 0.01f);

                gLight1R = D_menu_801B82EC;
                gLight1G = D_menu_801B82F0;
                gLight1B = D_menu_801B82F4;
            }

            if ((D_menu_801B82B4 > 60) && (gFillScreenAlpha < 255)) {
                gFillScreenAlpha++;
            }

            if (gFillScreenAlpha == 128) {
                D_menu_801B82A8 = 7;
                D_menu_801B84E8[3].unk_3C = 0;
                D_menu_801B84E8[3].unk_40 = 0;
                gFillScreenAlpha = 255;
                D_menu_801B82C0++;
            }

            if (D_menu_801B82B4 == 50) {
                D_menu_801B84E8[0].unk_4C = 0;
            }

            if (D_menu_801B82B4 == 60) {
                D_menu_801B84E8[1].unk_4C = 0;
            }

            Math_SmoothStepToF(&D_menu_801B86B4, 16.0f, 0.01f, 100.0f, 0.01f);
            Math_SmoothStepToF(&D_menu_801B86AC, 138.0f, 0.01f, 100.0f, 0.01f);

            Title_801914AC(D_menu_801B86BC, D_menu_801B86C0, D_menu_801B86C4, &gCsCamEyeX, &gCsCamEyeY, &gCsCamEyeZ,
                           D_menu_801B86B4, &gCsCamAtX, &gCsCamAtY, &gCsCamAtZ, D_menu_801B86B8, D_menu_801B86A8,
                           D_menu_801B86AC);
            D_menu_801B82B4++;
            break;

        case 3:
            if (D_menu_801B82A8 == 0) {
                Audio_KillSfxBySourceAndId(D_menu_801B84E8[3].unk_50, 0x0100001E);
                AUDIO_PLAY_SFX(0x09000002, D_menu_801B84E8[3].unk_50, 0);

                D_menu_801B82A8 = 4;

                gFillScreenAlpha = 0;

                for (i = 0; i < 4; i++) {
                    D_menu_801B84E8[i].unk_3C = 1;
                    D_menu_801B84E8[i].unk_44 = 0.9f;
                }

                D_menu_801B82B4 = 0;

                D_ctx_80178410 = 800;

                D_menu_801B82C0++;
            }
            break;

        case 4:
            if (D_menu_801B82A8 == 0) {
                D_menu_801B84E8[3].unk_44 = 1.2f;

                Math_SmoothStepToF(&D_menu_801B84E8[3].unk_00.z, 900.0f, 0.06f, 100.0f, 0.0001f);
                Math_SmoothStepToF(&D_menu_801B86AC, 154.0f, 0.2f, 100.0f, 0.01f);
                Math_SmoothStepToF(&D_menu_801B86A8, -5.0f, 0.2f, 100.0f, 0.01f);
                Math_SmoothStepToF(&D_menu_801B86BC, 100.0f, 0.2f, 100.0f, 0.01f);
                Math_SmoothStepToF(&D_menu_801B86B4, 40.0f, 0.2f, 100.0f, 0.01f);

                Title_801914AC(D_menu_801B86BC, D_menu_801B86C0, D_menu_801B86C4, &gCsCamEyeX, &gCsCamEyeY, &gCsCamEyeZ,
                               D_menu_801B86B4, &gCsCamAtX, &gCsCamAtY, &gCsCamAtZ, D_menu_801B86B8, D_menu_801B86A8,
                               D_menu_801B86AC);

                if (D_menu_801B82B4 > 8) {
                    Audio_SetBaseSfxReverb(0);
                    D_menu_801B82C0 = 0;
                    D_menu_801B82C4 = 5;
                }
                D_menu_801B82B4++;
            }
            break;
    }
    Title_80191674(D_menu_801B86C8, D_menu_801B86CC, 100.0f, &D_menu_801B82E0, &D_menu_801B82E4, &D_menu_801B82E8);
    D_menu_801B7BEC++;
}

void Title_8018C114(void) {
    s32 i;

    if (D_menu_801B8688.unk_0C != 0) {
        Title_8018DF0C(0.0f);
    }

    Title_80190950();

    for (i = 3; i >= 0; i--) {
        if (D_menu_801B84E8[i].unk_4C) {
            Title_80190B30(i);
        }
    }

    for (i = 0; i < 4; i++) {
        if (D_menu_801B84E8[i].unk_4C) {
            Title_8018D2B8(i);
        }
    }
}

void Title_8018C1C0(void) {
    s32 i;

    D_ctx_80178410 = 1;
    D_menu_801B7C98 = 10;

    for (i = 0; i < 10; i++) {
        D_menu_801B7BF8[i] = RAND_FLOAT(10.0f) + 10.0f;
        D_menu_801B7C20[i] = -10.0f + RAND_FLOAT(-60.0f);
        D_menu_801B7C48[i] = 0.0f;
        D_menu_801B7C70[i] = RAND_FLOAT(0.3f) + 0.1f;
        D_menu_801B7D18[i] = 5 + RAND_INT(5.0f);
        D_menu_801B7CC8[i] = 255;
        D_menu_801B7CF0[i] = 128;
        D_menu_801B7CA0[i] = 0;
    }

    D_menu_801B86A0 = 1;
    D_menu_801B86BC = 0.0f;
    D_menu_801B86C0 = -38.0f;
    D_menu_801B86C4 = 35.0f;

    D_menu_801B86A8 = -35.0f;
    D_menu_801B86AC = -50.0f;
    D_menu_801B86B4 = 105.0f;
    D_menu_801B86B8 = 50.0f;

    D_menu_801B869C = 255;

    gFillScreenAlpha = 0;
    gFillScreenRed = 0;
    gFillScreenGreen = 0;
    gFillScreenBlue = 0;

    D_menu_801B8688.pos.x = 130.0f;
    D_menu_801B8688.pos.y = -30.0f;
    D_menu_801B8688.pos.z = 2000.0f;
    D_menu_801B8688.scale = 8.0f;
    D_menu_801B8688.unk_0C = 0;

    D_menu_801B8658.pos.x = 0.0f;
    D_menu_801B8658.pos.y = 0.0f;
    D_menu_801B8658.pos.z = 0.0f;
    D_menu_801B8658.angleX = 0.0f;
    D_menu_801B8658.angleY = 0.0f;
    D_menu_801B8658.angleZ = 0.0f;
    D_menu_801B8658.scale = 0.1f;

    D_menu_801B86C8 = 0.0f;
    D_menu_801B86CC = 0.0f;

    gLight1R = 101;
    gLight1G = 106;
    gLight1B = 92;
    gAmbientR = 3;
    gAmbientG = 4;
    gAmbientB = 10;

    for (i = 0; i < 4; i++) {
        D_menu_801B84E8[i].unk_00.x = 0.0f;
        D_menu_801B84E8[i].unk_00.y = -40.0f;
        D_menu_801B84E8[i].unk_00.z = -30.0f;
        D_menu_801B84E8[i].unk_0C = 0.1f;
        D_menu_801B84E8[i].unk_18 = 0.0f;
        D_menu_801B84E8[i].unk_1C = 0.0f;
        D_menu_801B84E8[i].unk_20 = 0.0f;
        D_menu_801B84E8[i].unk_10 = 0.05f;
        D_menu_801B84E8[i].unk_24 = 0.0f;
        D_menu_801B84E8[i].unk_28 = 0.0f;
        D_menu_801B84E8[i].unk_2C = 0.0f;
        D_menu_801B84E8[i].unk_30 = 0.0f;
        D_menu_801B84E8[i].unk_34 = i + 1;
        D_menu_801B84E8[i].unk_3C = 1;
        D_menu_801B84E8[i].unk_40 = 0;
        D_menu_801B84E8[i].unk_44 = 1.2f;
        D_menu_801B84E8[i].unk_48 = 0;
        D_menu_801B84E8[i].unk_4C = 0;
    }

    D_menu_801B86BC = -8.0f;
    D_menu_801B86C0 = -37.0f;
    D_menu_801B86C4 = 64.0f;

    D_menu_801B86A8 = 5.899999f;
    D_menu_801B86AC = -112.74477f;
    D_menu_801B86B4 = 235.0f;
    D_menu_801B86B8 = 50.00f;

    D_menu_801B829C = 0.0f;
    D_menu_801B82A0 = 1.0f;
    D_menu_801B82A4 = 0.0f;

    Title_801914AC(D_menu_801B86BC, D_menu_801B86C0, D_menu_801B86C4, &gCsCamEyeX, &gCsCamEyeY, &gCsCamEyeZ,
                   D_menu_801B86B4, &gCsCamAtX, &gCsCamAtY, &gCsCamAtZ, D_menu_801B86B8, D_menu_801B86A8,
                   D_menu_801B86AC);
}

static CameraPoint D_menu_801ADF84[50] = {
    { -223.5775f, -61.156242f, -26.375984f, -53.867554f, -42.139626f, 44.77107f },
    { -160.05501f, -67.74775f, 85.750084f, -61.486446f, -44.164986f, 29.322315f },
    { -22.228004f, -79.54139f, 121.01903f, -15.555059f, -64.843475f, 85.51631f },
    { 94.76258f, -100.20792f, 96.57968f, 56.850273f, -76.324486f, 62.990417f },
    { 187.5704f, -114.560425f, 12.510195f, 111.428185f, -84.394104f, 8.465982f },
    { 244.8392f, -135.20625f, -212.59172f, 124.296425f, -87.25594f, -43.656223f },
    { 279.38947f, -216.01698f, -401.49118f, 122.86145f, -89.64914f, -105.359215f },
    { 440.83572f, -305.19196f, -598.5676f, 89.57457f, -23.879997f, -4.847023f },
    { 481.63818f, -313.2934f, -628.9213f, 96.2103f, -5.343582f, -4.23885f },
};

void Title_8018C644(void) {
    s32 i;
    f32 x;
    f32 y;
    f32 z;
    static f32 D_menu_801AE434[4] = { -15.0f, -5.0f, 5.0f, 10.0f };
    static f32 D_menu_801AE444[4] = { -50.0f, -45.0f, -55.0f, -60.0f };
    static f32 D_menu_801AE454[4] = { 265.0f, 260.0f, 255.0f, 230.0f };

    switch (D_menu_801B82C0) {
        case 0:
            AUDIO_PLAY_SFX(0x11030010, D_menu_801B8658.unk_24, 0);
            AUDIO_PLAY_SFX(0x31024059, D_menu_801B8658.unk_24, 0);

            Title_8018C1C0();

            D_menu_801B82B4 = 0;
            D_menu_801B7BEC = 0;
            D_menu_801B8688.unk_0C = 1;

            D_menu_801B84E8[0].unk_38 = 3;
            D_menu_801B84E8[1].unk_38 = 23;
            D_menu_801B84E8[2].unk_38 = 43;
            D_menu_801B84E8[3].unk_38 = 63;

            D_menu_801B8294 = D_menu_801ADF84;
            D_menu_801B8298 = 0;
            D_menu_801B828C = 0.0f;
            D_menu_801B8290 = 0.042f;

            D_menu_801B82C0++;
            break;

        case 1:
            for (i = 0; i < 4; i++) {
                if (D_menu_801B84E8[i].unk_38 > 0) {
                    D_menu_801B84E8[i].unk_38--;
                } else {
                    if (D_menu_801B84E8[i].unk_38 == 0) {
                        AUDIO_PLAY_SFX(0x19000001, D_menu_801B84E8[i].unk_50, 0);
                        D_menu_801B84E8[i].unk_38 = -1;
                        D_menu_801B84E8[i].unk_4C = 1;
                    }

                    Math_SmoothStepToF(&D_menu_801B84E8[i].unk_00.y, D_menu_801AE444[i], D_menu_801B84E8[i].unk_10,
                                       100.0f, 0.001f);
                    Math_SmoothStepToF(&D_menu_801B84E8[i].unk_00.x, D_menu_801AE434[i], D_menu_801B84E8[i].unk_10,
                                       100.0f, 0.001f);
                    Math_SmoothStepToF(&D_menu_801B84E8[i].unk_00.z, D_menu_801AE454[i], D_menu_801B84E8[i].unk_10,
                                       100.0f, 0.001f);

                    D_menu_801B84E8[i].unk_10 *= 1.05f;

                    if (D_menu_801B84E8[i].unk_00.z == D_menu_801AE454[i]) {
                        D_menu_801B84E8[i].unk_0C -= 0.002f;
                        if (D_menu_801B84E8[i].unk_0C < 0.0f) {
                            D_menu_801B84E8[i].unk_0C = 0.0f;
                            D_menu_801B84E8[i].unk_4C = 0;
                        }
                    }

                    x = D_menu_801AE434[i] - D_menu_801B84E8[i].unk_00.x;
                    y = D_menu_801AE444[i] - D_menu_801B84E8[i].unk_00.y;
                    z = D_menu_801AE454[i] + 10.0f - D_menu_801B84E8[i].unk_00.z;

                    D_menu_801B84E8[i].unk_18 = RAD_TO_DEG(-Math_Atan2F(y, sqrtf(SQ(x) + SQ(z))));
                    D_menu_801B84E8[i].unk_1C = RAD_TO_DEG(Math_Atan2F(x, z));
                }
            }

            if (D_menu_801B82B4 == 125) {
                D_menu_801B869C = 1;
            }

            if (gFillScreenAlpha == 255) {
                Audio_KillSfxBySourceAndId(D_menu_801B8658.unk_24, 0x11030010);
                Audio_KillSfxBySourceAndId(D_menu_801B8658.unk_24, 0x31024059);
                D_menu_801B82C0++;
            }
            Title_801912A0();
            D_menu_801B82B4++;
            break;

        case 2:
            gFillScreenAlpha = 0;
            D_ctx_80178410 = 0;
            D_menu_801B86A0 = 0;
            D_menu_801B82A8 = 20;
            D_menu_801B82C0++;
            break;

        case 3:
            if (D_menu_801B82A8 != 0) {
                break;
            }
            D_menu_801B82C0 = 0;
            gDrawMode = DRAW_NONE;
            D_menu_801B82C4 = 0;
            Audio_SetAudioSpec(0, 23);
            break;
    }

    Title_80191798(&D_menu_801B86A8, &D_menu_801B86AC);
    Title_80191844(D_menu_801B86A8, D_menu_801B86AC);
    Title_8018CC30(D_menu_801B8294, 9, D_menu_801B8290);
    Title_80191674(D_menu_801B86C8, D_menu_801B86CC, 100.0f, &D_menu_801B82E0, &D_menu_801B82E4, &D_menu_801B82E8);
    func_play_800B6F50(gCsCamEyeX, gCsCamEyeY, gCsCamEyeZ, gCsCamAtX, gCsCamAtY, gCsCamAtZ);

    D_menu_801B7BEC++;
}

void Title_8018CB90(void) {
    s32 i;

    if (D_menu_801B86A0 != 0) {
        if (D_menu_801B8688.unk_0C != 0) {
            Title_8018DF0C(-1000.0f);
        }

        Title_8018E058();

        for (i = 0; i < 4; i++) {
            if ((D_menu_801B84E8[i].unk_38 <= 0) && (D_menu_801B84E8[i].unk_4C != 0)) {
                Title_8018D2B8(i);
            }
        }
    }
}

void Title_8018CC30(CameraPoint* arg0, s32 arg1, f32 arg2) {
    s32 var_a3;
    CameraPoint pos;

    if (D_menu_801B8298 != -1) {
        if (D_menu_801B8298 == 0) {
            var_a3 = 0;
        } else if (D_menu_801B8298 == 1) {
            var_a3 = 1;
            if (arg1 == 5) {
                var_a3 = 4;
            }
        } else if (arg1 == (D_menu_801B8298 + 5)) {
            var_a3 = 3;
        } else if (arg1 == (D_menu_801B8298 + 4)) {
            { var_a3 = 4; }
        } else {
            var_a3 = 2;
        }

        Title_8018CD9C(&pos, &arg0[D_menu_801B8298], D_menu_801B828C, var_a3);
        gCsCamEyeX = pos.eye.x;
        gCsCamEyeY = pos.eye.y;
        gCsCamEyeZ = pos.eye.z;
        gCsCamAtX = pos.at.x;
        gCsCamAtY = pos.at.y;
        gCsCamAtZ = pos.at.z;

        D_menu_801B828C += arg2;

        if (D_menu_801B828C > 1.0f) {
            D_menu_801B8298++;
            D_menu_801B828C = 0.0f;
            if ((arg1 - 4) < D_menu_801B8298) {
                D_menu_801B8298 = -1;
            }
        }
    }
}

void Title_8018CD9C(CameraPoint* pos, CameraPoint* arg1, f32 weight, s32 arg3) {
    f32 temp1;
    f32 temp2;
    f32 temp3;
    f32 temp4;

    switch (arg3) {
        case 0:
            temp1 = CUBE(1.0f - weight);
            temp2 = 21.0f * CUBE(weight) / 12.0f - 9.0f * SQ(weight) / 2.0f + 3.0f * weight;
            temp3 = -11.0f * CUBE(weight) / 12.0f + 3.0f * SQ(weight) / 2.0f;
            temp4 = CUBE(weight) / 6.0f;
            break;

        case 1:
            temp1 = CUBE(1.0f - weight) / 4.0f;
            temp2 = 7.0f * CUBE(weight) / 12.0f - 5.0f * SQ(weight) / 4.0f + weight / 4.0f + 7.0f / 12.0f;
            temp3 = -CUBE(weight) / 2.0f + SQ(weight) / 2.0f + weight / 2.0f + 1.0f / 6.0f;
            temp4 = CUBE(weight) / 6.0f;
            break;

        case 2:
            temp1 = CUBE(1.0f - weight) / 6.0f;
            temp2 = (0.5f * weight - 1.0f) * SQ(weight) + 2.0f / 3.0f;
            temp3 = ((-weight + 1.0f) * weight + 1.0f) * 0.5f * weight + 1.0f / 6.0f;
            temp4 = CUBE(weight) / 6.0f;
            break;

        case 3:
            temp1 = CUBE(1.0f - weight) / 6.0f;
            temp2 = -CUBE(1.0f - weight) / 2.0f + SQ(1.0f - weight) / 2.0f + (1.0f - weight) / 2.0f + 1.0f / 6.0f;
            temp3 = 7.0f * CUBE(1.0f - weight) / 12.0f - 5.0f * SQ(1.0f - weight) / 4.0f + (1.0f - weight) / 4.0f +
                    7.0f / 12.0f;
            temp4 = CUBE(weight) / 4.0f;
            break;

        case 4:
            temp1 = CUBE(1.0f - weight) / 6.0f;
            temp2 = -11.0f * CUBE(1.0f - weight) / 12.0f + 3.0f * SQ(1.0f - weight) / 2.0f;
            temp3 = 21.0f * CUBE(1.0f - weight) / 12.0f - 9.0f * SQ(1.0f - weight) / 2.0f + 3.0f * (1.0f - weight);
            temp4 = CUBE(weight);
            break;
    }

    pos->eye.x = (temp1 * (arg1 + 0)->eye.x) + (temp2 * (arg1 + 1)->eye.x) + (temp3 * (arg1 + 2)->eye.x) +
                 (temp4 * (arg1 + 3)->eye.x);
    pos->eye.y = (temp1 * (arg1 + 0)->eye.y) + (temp2 * (arg1 + 1)->eye.y) + (temp3 * (arg1 + 2)->eye.y) +
                 (temp4 * (arg1 + 3)->eye.y);
    pos->eye.z = (temp1 * (arg1 + 0)->eye.z) + (temp2 * (arg1 + 1)->eye.z) + (temp3 * (arg1 + 2)->eye.z) +
                 (temp4 * (arg1 + 3)->eye.z);

    pos->at.x = (temp1 * (arg1 + 0)->at.x) + (temp2 * (arg1 + 1)->at.x) + (temp3 * (arg1 + 2)->at.x) +
                (temp4 * (arg1 + 3)->at.x);
    pos->at.y = (temp1 * (arg1 + 0)->at.y) + (temp2 * (arg1 + 1)->at.y) + (temp3 * (arg1 + 2)->at.y) +
                (temp4 * (arg1 + 3)->at.y);
    pos->at.z = (temp1 * (arg1 + 0)->at.z) + (temp2 * (arg1 + 1)->at.z) + (temp3 * (arg1 + 2)->at.z) +
                (temp4 * (arg1 + 3)->at.z);
}

void Title_8018D2B8(s32 arg0) {
    WingInfo wings;

    Lights_SetOneLight(&gMasterDisp, D_menu_801B82E0, D_menu_801B82E4, D_menu_801B82E8, gLight1R, gLight1G, gLight1B,
                       gAmbientR, gAmbientG, gAmbientB);

    RCP_SetupDL(&gMasterDisp, 0x17);

    Matrix_Push(&gGfxMatrix);

    Matrix_Translate(gGfxMatrix, D_menu_801B84E8[arg0].unk_00.x, D_menu_801B84E8[arg0].unk_00.y,
                     D_menu_801B84E8[arg0].unk_00.z, 1);

    Matrix_Scale(gGfxMatrix, D_menu_801B84E8[arg0].unk_0C, D_menu_801B84E8[arg0].unk_0C, D_menu_801B84E8[arg0].unk_0C,
                 1);

    Matrix_RotateZ(gGfxMatrix, D_menu_801B84E8[arg0].unk_20 * M_DTOR, 1);
    Matrix_RotateX(gGfxMatrix, D_menu_801B84E8[arg0].unk_18 * M_DTOR, 1);
    Matrix_RotateY(gGfxMatrix, D_menu_801B84E8[arg0].unk_1C * M_DTOR, 1);

    Matrix_SetGfxMtx(&gMasterDisp);

    wings.rightState = wings.leftState = WINGSTATE_INTACT;
    wings.unk_18 = wings.unk_1C = wings.unk_20 = wings.unk_24 = wings.unk_04 = wings.unk_08 = wings.unk_0C =
        wings.unk_10 = wings.unk_28 = 0.0f;

    wings.unk_14 = D_menu_801B84E8[arg0].unk_28;
    wings.unk_2C = D_menu_801B84E8[arg0].unk_34;
    wings.unk_30 = D_menu_801B84E8[arg0].unk_2C;
    wings.unk_34 = D_menu_801B84E8[arg0].unk_30;
    wings.unk_38 = D_menu_801B84E8[arg0].unk_24;

    func_display_80053658(&wings);

    func_edisplay_8005F1EC(D_menu_801B84E8[arg0].unk_50);

    if (D_menu_801B84E8[arg0].unk_40 != 0) {
        Title_8018D80C(arg0);
    }

    if (D_menu_801B84E8[arg0].unk_3C != 0) {
        Title_8018D510(arg0);
    }

    if (D_menu_801B84E8[arg0].unk_48 != 0) {
        Title_8018DDB8(arg0);
    }

    Matrix_Pop(&gGfxMatrix);
}

void Title_8018D510(s32 arg0) {
    f32 var_fv0;
    f32 sp40;
    f32 sp3C;
    f32 var_fv1;
    f32 var_fa0;
    f32 temp;

    RCP_SetupDL(&gMasterDisp, 0x43);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    if (D_menu_801B84E8[arg0].unk_40 == 1) {
        var_fa0 = -30.0f;
        var_fv1 = 0.02f;
        gDPSetEnvColor(gMasterDisp++, 128, 128, 255, 255);
    } else {
        var_fa0 = -65.0f;
        var_fv1 = 0.2f;
        gDPSetEnvColor(gMasterDisp++, 0, 0, 255, 255);
    }

    var_fv0 = D_menu_801B84E8[arg0].unk_44;

    if ((gGameFrameCount % 2) != 0) {
        var_fv0 += var_fv1;
    }

    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, var_fa0, 1);
    Matrix_Scale(gGfxMatrix, var_fv0, var_fv0 * 0.7f, var_fv0, 1);

    Matrix_RotateZ(gGfxMatrix, -D_menu_801B84E8[arg0].unk_20 * M_DTOR, 1);
    Matrix_RotateX(gGfxMatrix, -D_menu_801B84E8[arg0].unk_18 * M_DTOR, 1);
    Matrix_RotateY(gGfxMatrix, -D_menu_801B84E8[arg0].unk_1C * M_DTOR, 1);

    sp3C = -Math_Atan2F(gCsCamEyeX - D_menu_801B84E8[arg0].unk_00.x, gCsCamEyeZ - D_menu_801B84E8[arg0].unk_00.z);
    temp = sqrtf(SQ(gCsCamEyeZ - D_menu_801B84E8[arg0].unk_00.z) + SQ(gCsCamEyeX - D_menu_801B84E8[arg0].unk_00.x));
    sp40 = Math_Atan2F(gCsCamEyeY - D_menu_801B84E8[arg0].unk_00.y, temp);

    Matrix_RotateY(gGfxMatrix, -sp3C, 1);
    Matrix_RotateX(gGfxMatrix, -sp40, 1);
    Matrix_SetGfxMtx(&gMasterDisp);

    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
    gSPDisplayList(gMasterDisp++, D_TITLE_60320E0);
    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);

    Matrix_Pop(&gGfxMatrix);
}

void Title_8018D80C(s32 arg0) {
    s32 i;
    f32 sp70;
    f32 sp6C;
    f32 temp;

    for (i = 0; i < D_menu_801B8100; i++) {
        switch (D_menu_801B8108[i]) {
            case 0:
                Math_SmoothStepToF(&D_menu_801B7FC0[i], D_menu_801B8060[i], 0.05f, 100.0f, 0.01f);

                if (D_menu_801B7FC0[i] >= D_menu_801B8060[i]) {
                    D_menu_801B7FC0[i] = D_menu_801B8060[i];
                    D_menu_801B8108[i] = 1;
                }
                break;

            case 1:
                Math_SmoothStepToF(&D_menu_801B7D40[i], 0.0f, D_menu_801B7F20[i], 100.0f, 0.01f);
                Math_SmoothStepToF(&D_menu_801B7DE0[i], 0.0f, D_menu_801B7F20[i], 100.0f, 0.01f);
                Math_SmoothStepToF(&D_menu_801B7E80[i], -25.0f, D_menu_801B7F20[i], 100.0f, 0.01f);

                D_menu_801B7FC0[i] -= 0.002f;
                if (D_menu_801B7FC0[i] < 0.0f) {
                    D_menu_801B7FC0[i] = 0.0f;
                    D_menu_801B8108[i] = 255;
                }
                break;

            case 255:
                D_menu_801B7D40[i] = 10.0f - RAND_FLOAT(20.0f);
                D_menu_801B7DE0[i] = 3.0f - RAND_FLOAT(7.0f);
                D_menu_801B7E80[i] = -30.0f - RAND_FLOAT(15.0f);
                D_menu_801B7FC0[i] = 0.0f;
                D_menu_801B8060[i] = RAND_FLOAT(0.02f);
                D_menu_801B7F20[i] = 0.02f + RAND_FLOAT(0.08f);
                D_menu_801B8108[i] = 0;
                break;
        }
    }

    sp6C = -Math_Atan2F(gCsCamEyeX - D_menu_801B84E8[arg0].unk_00.x, gCsCamEyeZ - D_menu_801B84E8[arg0].unk_00.z);
    temp = sqrtf(SQ(gCsCamEyeZ - D_menu_801B84E8[arg0].unk_00.z) + SQ(gCsCamEyeX - D_menu_801B84E8[arg0].unk_00.x));
    sp70 = Math_Atan2F(gCsCamEyeY - D_menu_801B84E8[arg0].unk_00.y, temp);

    RCP_SetupDL(&gMasterDisp, 0x31);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 253, 253, 255, 255);
    gDPSetEnvColor(gMasterDisp++, 251, 251, 255, 255);

    for (i = 0; i < D_menu_801B8100; i++) {
        if (D_menu_801B7FC0[i] == 0.0f) {
            continue;
        }

        Matrix_Push(&gGfxMatrix);

        Matrix_Translate(gGfxMatrix, D_menu_801B7D40[i], D_menu_801B7DE0[i], D_menu_801B7E80[i], 1);
        Matrix_Scale(gGfxMatrix, D_menu_801B7FC0[i], D_menu_801B7FC0[i], D_menu_801B7FC0[i], 1);

        Matrix_RotateZ(gGfxMatrix, -D_menu_801B84E8[arg0].unk_20 * M_DTOR, 1);
        Matrix_RotateX(gGfxMatrix, -D_menu_801B84E8[arg0].unk_18 * M_DTOR, 1);
        Matrix_RotateY(gGfxMatrix, -D_menu_801B84E8[arg0].unk_1C * M_DTOR, 1);

        Matrix_RotateY(gGfxMatrix, -sp6C, 1);
        Matrix_RotateX(gGfxMatrix, -sp70, 1);

        Matrix_SetGfxMtx(&gMasterDisp);

        gSPDisplayList(gMasterDisp++, D_TITLE_60320E0);

        Matrix_Pop(&gGfxMatrix);
    }
}

void Title_8018DDB8(s32 arg0) {
    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, 0.0f,
                     (D_menu_801B9050 - D_menu_801B84E8[arg0].unk_00.y * 2.05f) + (D_menu_801B9048 - 84.0f) * 1.99f,
                     0.0f, 1);
    Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 1.0f, 1);
    Matrix_RotateY(gGfxMatrix, M_PI, 1);
    Matrix_SetGfxMtx(&gMasterDisp);

    RCP_SetupDL_64();

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 240);
    gSPDisplayList(gMasterDisp++, D_TITLE_6032580);

    Matrix_Pop(&gGfxMatrix);
}

void Title_8018DF0C(f32 arg0) {
    f32 sp34;
    f32 sp30;

    Title_80191798(&sp34, &sp30);
    RCP_SetupDL(&gMasterDisp, 0x35);

    if (arg0 != 0.0f) {
        D_menu_801B8688.pos.z = gCsCamEyeZ - arg0;
    }

    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, D_menu_801B8688.pos.x, D_menu_801B8688.pos.y, D_menu_801B8688.pos.z, 1);
    Matrix_RotateY(gGfxMatrix, M_DTOR * sp30, 1);
    Matrix_RotateX(gGfxMatrix, M_DTOR * sp34, 1);
    Matrix_Scale(gGfxMatrix, D_menu_801B8688.scale, D_menu_801B8688.scale, D_menu_801B8688.scale, 1);
    Matrix_SetGfxMtx(&gMasterDisp);

    gSPDisplayList(gMasterDisp++, D_TITLE_6037CF0);
    Title_8018E200();
    Matrix_Pop(&gGfxMatrix);
}

void Title_8018E058(void) {
    Lights_SetOneLight(&gMasterDisp, D_menu_801B82E0, D_menu_801B82E4, D_menu_801B82E8, gLight1R, gLight1G, gLight1B,
                       gAmbientR, gAmbientG, gAmbientB);

    Matrix_Push(&gGfxMatrix);

    Matrix_Translate(gGfxMatrix, D_menu_801B8658.pos.x, D_menu_801B8658.pos.y, D_menu_801B8658.pos.z, 1);

    Matrix_RotateZ(gGfxMatrix, M_DTOR * D_menu_801B8658.angleZ, 1);
    Matrix_RotateX(gGfxMatrix, M_DTOR * D_menu_801B8658.angleX, 1);
    Matrix_RotateY(gGfxMatrix, M_DTOR * D_menu_801B8658.angleY, 1);

    Matrix_Scale(gGfxMatrix, D_menu_801B8658.scale, D_menu_801B8658.scale, D_menu_801B8658.scale, 1);

    Matrix_SetGfxMtx(&gMasterDisp);
    RCP_SetupDL(&gMasterDisp, 0x17);

    gGreatFoxIntact = true;

    func_demo_800515C4();
    func_edisplay_8005F1EC(D_menu_801B8658.unk_24);

    Matrix_Pop(&gGfxMatrix);
}

void Title_8018E200(void) {
    f32 scale;
    s32 i;

    for (i = 0; i < D_menu_801B7C98; i++) {
        switch (D_menu_801B7CA0[i]) {
            case 0:
                D_menu_801B7C48[i] += 0.15f;
                if (D_menu_801B7C48[i] >= D_menu_801B7C70[i]) {
                    D_menu_801B7C48[i] = D_menu_801B7C70[i];
                    D_menu_801B7CA0[i] = 10;
                }
                break;

            case 10:
                D_menu_801B7D18[i]--;
                if (D_menu_801B7D18[i] <= 0) {
                    D_menu_801B7CA0[i] = 1;
                }
                break;

            case 1:
                D_menu_801B7CC8[i] -= 16;
                if (D_menu_801B7CC8[i] < 0) {
                    D_menu_801B7CC8[i] = 0;
                }
                D_menu_801B7CF0[i] -= 16;
                if (D_menu_801B7CF0[i] < 0) {
                    D_menu_801B7CF0[i] = 0;
                }
                if (D_menu_801B7CC8[i] == 0 && D_menu_801B7CF0[i] == 0) {
                    D_menu_801B7CA0[i] = 255;
                }
                break;

            case 255:
                D_menu_801B7BF8[i] = 10.0f + RAND_FLOAT(10.0f);
                D_menu_801B7C20[i] = -10.0f + RAND_FLOAT(-60.0f);
                D_menu_801B7C48[i] = 0.0f;
                D_menu_801B7C70[i] = 0.1f + RAND_FLOAT(0.3f);
                D_menu_801B7D18[i] = 5 + RAND_INT(5.0f);
                D_menu_801B7CC8[i] = 255;
                D_menu_801B7CF0[i] = 128;
                D_menu_801B7CA0[i] = 0;
                break;
        }
    }

    RCP_SetupDL(&gMasterDisp, 0x31);

    for (i = 0; i < D_menu_801B7C98; i++) {
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 200, 200, D_menu_801B7CC8[i]);
        gDPSetEnvColor(gMasterDisp++, 255, 0, 0, D_menu_801B7CF0[i]);

        scale = D_menu_801B7C48[i] / D_menu_801B8688.scale;

        Matrix_Push(&gGfxMatrix);

        Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, 5.0f, 1);
        Matrix_RotateZ(gGfxMatrix, D_menu_801B7C20[i] * M_DTOR, 1);
        Matrix_Translate(gGfxMatrix, 0.0f, D_menu_801B7BF8[i], 0.0f, 1);
        Matrix_Scale(gGfxMatrix, scale, scale, scale, 1);

        Matrix_SetGfxMtx(&gMasterDisp);

        gSPDisplayList(gMasterDisp++, D_TITLE_60320E0);

        Matrix_Pop(&gGfxMatrix);
    }
}

void Title_8018E67C(s32 arg0) {
    Vec3f sp60[50];
    s32 sp5C;
    f32 temp_fv1;

    Lights_SetOneLight(&gMasterDisp, D_menu_801B82E0, D_menu_801B82E4, D_menu_801B82E8, gLight1R, gLight1G, gLight1B,
                       gAmbientR, gAmbientG, gAmbientB);

    sp5C = D_menu_801B8350[arg0].unk_58 % Animation_GetFrameCount(D_menu_801ADA00[arg0].unk_0);

    RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, 255, 995, 1000);

    Matrix_Push(&gGfxMatrix);

    Matrix_Translate(gGfxMatrix, D_menu_801B8350[arg0].unk_00.x, D_menu_801B8350[arg0].unk_00.y,
                     D_menu_801B8350[arg0].unk_00.z + D_menu_801B84D0, 1);
    Matrix_Scale(gGfxMatrix, D_menu_801B84D4, D_menu_801B84D4, D_menu_801B84D4, 1);
    Matrix_SetGfxMtx(&gMasterDisp);

    if (arg0 == 2) {
        gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
    }

    Animation_GetFrameData(D_menu_801ADA00[arg0].unk_0, sp5C, sp60);
    Animation_DrawSkeleton(0, D_menu_801ADA00[arg0].skeleton, sp60, NULL, NULL, NULL, &gIdentityMatrix);

    if (arg0 == 2) {
        gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
    }

    if (arg0 == 0) {
        func_edisplay_8005F1EC(D_menu_801B84D8);
    }

    Matrix_Pop(&gGfxMatrix);
    Matrix_Push(&gGfxMatrix);

    Matrix_Translate(gGfxMatrix, D_menu_801B8350[arg0].unk_00.x - 5.0f, 5.0f,
                     D_menu_801B8350[arg0].unk_00.z + 10.0f + D_menu_801B84D0, 1);

    Matrix_Scale(gGfxMatrix, D_menu_801B8350[arg0].unk_10, D_menu_801B8350[arg0].unk_10, D_menu_801B8350[arg0].unk_10,
                 1);

    Matrix_SetGfxMtx(&gMasterDisp);

    RCP_SetupDL_64();

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 128);
    gSPDisplayList(gMasterDisp++, D_TITLE_6041070);

    Matrix_Pop(&gGfxMatrix);

    temp_fv1 = SIN_DEG(sp5C * 12.0f) * 15.0f;

    if (temp_fv1 >= 0) {
        D_menu_801B8350[arg0].unk_0C = temp_fv1;
    } else if (temp_fv1 > -2.0f) {
        D_menu_801B8350[arg0].unk_0C = -temp_fv1;
    } else {
        D_menu_801B8350[arg0].unk_0C = 0.0f;
    }
    D_menu_801B8350[arg0].unk_10 = 3.0f - (D_menu_801B8350[arg0].unk_0C / 100.0f);
}

void Title_8018EA78(s32 arg0) {
    Vec3f sp48[50];
    s32 sp44;

    sp44 = D_menu_801B8350[arg0].unk_58 % Animation_GetFrameCount(D_menu_801ADA00[arg0].unk_4);

    RCP_SetupDL(&gMasterDisp, 0x17);

    Lights_SetOneLight(&gMasterDisp, D_menu_801B82E0, D_menu_801B82E4, D_menu_801B82E8, gLight1R, gLight1G, gLight1B,
                       gAmbientR, gAmbientG, gAmbientB);

    Matrix_Push(&gGfxMatrix);

    Matrix_RotateX(gGfxMatrix, D_menu_801B8350[arg0].unk_48 * M_DTOR, 1);
    Matrix_RotateY(gGfxMatrix, D_menu_801B8350[arg0].unk_4C * M_DTOR, 1);
    Matrix_RotateZ(gGfxMatrix, D_menu_801B8350[arg0].unk_50 * M_DTOR, 1);

    Matrix_Translate(gGfxMatrix, D_menu_801B8350[arg0].unk_00.x, D_menu_801B8350[arg0].unk_00.y,
                     D_menu_801B8350[arg0].unk_00.z, 1);
    Matrix_Scale(gGfxMatrix, D_menu_801B84D4, D_menu_801B84D4, D_menu_801B84D4, 1);

    Matrix_SetGfxMtx(&gMasterDisp);

    Math_SmoothStepToVec3fArray(sp48, D_menu_801B86E0[arg0], 1,
                                Animation_GetFrameData(D_menu_801ADA00[arg0].unk_4, sp44, sp48), 0.2f, 100.0f, 0.0001f);
    Animation_DrawSkeleton(1, D_menu_801ADA00[arg0].skeleton, D_menu_801B86E0[arg0], Title_8018EDC8, NULL, &arg0,
                           &gIdentityMatrix);

    Matrix_Pop(&gGfxMatrix);
}

bool Title_8018EDC8(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* data) {
    f32 x;
    f32 y;
    f32 z;
    s32 i = *(s32*) data;

    if ((D_menu_801B86A4 < 2) && D_menu_801B9040) {
        x = D_menu_801B905C - D_menu_801B8350[i].unk_00.x;
        y = D_menu_801B9060 - (D_menu_801B8350[i].unk_00.y + D_menu_801B8350[i].unk_14);
        z = D_menu_801B9064 - D_menu_801B8350[i].unk_00.z;

        D_menu_801B8350[i].unk_28 = Math_Atan2F(x, sqrtf(SQ(y) + SQ(z))) * M_RTOD;
        D_menu_801B8350[i].unk_2C = Math_Atan2F(y, z) * M_RTOD;

        D_menu_801B8350[i].unk_38 = D_menu_801B8350[i].unk_28;
        D_menu_801B8350[i].unk_3C = D_menu_801B8350[i].unk_2C;

        if (D_menu_801B8350[i].unk_28 < -45.0f) {
            D_menu_801B8350[i].unk_28 = -45.0f;
        } else if (D_menu_801B8350[i].unk_28 > 45.0f) {
            D_menu_801B8350[i].unk_28 = 45.0f;
        }

        if (D_menu_801B8350[i].unk_2C < -40.0f) {
            D_menu_801B8350[i].unk_2C = -40.0f;
        } else if (D_menu_801B8350[i].unk_2C > 55.0f) {
            D_menu_801B8350[i].unk_2C = 55.0f;
        }

        if (D_menu_801B8350[i].unk_38 < -20.0f) {
            D_menu_801B8350[i].unk_38 = D_menu_801B8350[i].unk_38 - (-20.0f);
            if (D_menu_801B8350[i].unk_38 < -20.0f) {
                D_menu_801B8350[i].unk_38 = -20.0f;
            }
        } else if (D_menu_801B8350[i].unk_38 > 20.0f) {
            D_menu_801B8350[i].unk_38 = D_menu_801B8350[i].unk_38 - 20.0f;
            if (D_menu_801B8350[i].unk_38 > 20.0f) {
                D_menu_801B8350[i].unk_38 = 20.0f;
            }
        } else {
            D_menu_801B8350[i].unk_38 = 0.0f;
        }

        if (D_menu_801B8350[i].unk_3C < -35.0f) {
            D_menu_801B8350[i].unk_3C = D_menu_801B8350[i].unk_3C - (-35.0f);
            if (D_menu_801B8350[i].unk_3C < -10.0f) {
                D_menu_801B8350[i].unk_3C = -10.0f;
            }
        } else if (D_menu_801B8350[i].unk_3C > 40.0f) {
            D_menu_801B8350[i].unk_3C = D_menu_801B8350[i].unk_3C - 40.0f;
            if (D_menu_801B8350[i].unk_3C > 10.0f) {
                D_menu_801B8350[i].unk_3C = 10.0f;
            }
        } else {
            D_menu_801B8350[i].unk_3C = 0.0f;
        }

        Math_SmoothStepToF(&D_menu_801B8350[i].unk_30, D_menu_801B8350[i].unk_28, 0.01f, 100.0f, 0.0001f);
        Math_SmoothStepToF(&D_menu_801B8350[i].unk_34, D_menu_801B8350[i].unk_2C, 0.01f, 100.0f, 0.0001f);
        Math_SmoothStepToF(&D_menu_801B8350[i].unk_40, D_menu_801B8350[i].unk_38, 0.005f, 100.0f, 0.0001f);
        Math_SmoothStepToF(&D_menu_801B8350[i].unk_44, D_menu_801B8350[i].unk_3C, 0.005f, 100.0f, 0.0001f);
    }

    switch (i) {
        case 0:
            if (limbIndex == 1) {
                rot->z += D_menu_801B8350[i].unk_18;
            }
            if (limbIndex == 19) {
                rot->x += D_menu_801B8350[i].unk_30;
                rot->y += D_menu_801B8350[i].unk_34;
            }
            if (limbIndex == 20) {
                rot->x += D_menu_801B8350[i].unk_40;
                rot->y += D_menu_801B8350[i].unk_44;
            }
            break;

        case 1:
            if (limbIndex == 1) {
                rot->z += D_menu_801B8350[i].unk_18;
            }
            if (limbIndex == 11) {
                rot->z += D_menu_801B8350[i].unk_20;
            }
            if (limbIndex == 19) {
                rot->x += D_menu_801B8350[i].unk_30;
                rot->y += D_menu_801B8350[i].unk_34;
            }
            if (limbIndex == 20) {
                rot->x += D_menu_801B8350[i].unk_40;
                rot->y += D_menu_801B8350[i].unk_44;
            }
            if (limbIndex == 21) {
                rot->x += -5.0f;
            }
            break;

        case 2:
            if (limbIndex == 1) {
                rot->z += D_menu_801B8350[i].unk_18;
            }
            if (limbIndex == 19) {
                rot->x += D_menu_801B8350[i].unk_30;
                rot->y += D_menu_801B8350[i].unk_34;
            }
            if (limbIndex == 20) {
                rot->x += D_menu_801B8350[i].unk_40;
                rot->y += D_menu_801B8350[i].unk_44;
            }
            if (limbIndex == 21) {
                rot->x += 10.0f;
            }
            break;

        case 3:
            if (limbIndex == 1) {
                rot->z += D_menu_801B8350[i].unk_18;
            }
            if (limbIndex == 17) {
                rot->x += D_menu_801B8350[i].unk_30;
                rot->y += D_menu_801B8350[i].unk_34;
            }
            if (limbIndex == 18) {
                rot->x += D_menu_801B8350[i].unk_40;
                rot->y += D_menu_801B8350[i].unk_44;
            }
            if (limbIndex == 19) {
                rot->x += 4.0f;
            }
            break;
    }

    return false;
}

void Title_8018F438(void) {
    f32 sp54;

    Lights_SetOneLight(&gMasterDisp, 0, 0, 0, 0, 0, 0, gAmbientR, gAmbientG, gAmbientB);

    if (gCsCamAtZ < gCsCamEyeZ) {
        sp54 = 1.0f;
    } else {
        sp54 = 3.0f;
    }

    D_menu_801B82C8 += 70.0f;
    D_menu_801B82C8 = Math_ModF(D_menu_801B82C8, 4101.6f);

    RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, 255, 995, 1000);

    Matrix_Push(&gGfxMatrix);

    Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, (3079.2002f * sp54) - D_menu_801B82C8, 1);
    Matrix_Scale(gGfxMatrix, 0.6f, 0.6f, 0.6f, 1);
    Matrix_SetGfxMtx(&gMasterDisp);

    gSPDisplayList(gMasterDisp++, D_TITLE_602E380);

    Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -6836.0f, 1);
    Matrix_SetGfxMtx(&gMasterDisp);

    gSPDisplayList(gMasterDisp++, D_TITLE_602E380);

    Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -6836.0f, 1);
    Matrix_SetGfxMtx(&gMasterDisp);

    gSPDisplayList(gMasterDisp++, D_TITLE_602E380);

    Matrix_Pop(&gGfxMatrix);
}

void Title_8018F680(void) {
    RCP_SetupDL(&gMasterDisp, 0x53);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    // LTodo: Validate this
    TextureRect_16bRGBA(&gMasterDisp, gTitleStarfoxLogo, 236, 60, D_menu_801B9054, D_menu_801B9058, 1.0f, 1.0f);
}

void Title_8018F77C(void) {
    RCP_SetupDL(&gMasterDisp, 0x35);
    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, D_menu_801B905C, D_menu_801B9060, D_menu_801B9064, 1);
    Matrix_Scale(gGfxMatrix, D_menu_801B9068, D_menu_801B906C, 1.0f, 1);
    Matrix_RotateX(gGfxMatrix, M_DTOR * 90, 1);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_TITLE_60148D0);
    Matrix_Pop(&gGfxMatrix);
}

void Title_8018F85C(void) {
    RCP_SetupDL(&gMasterDisp, 0x53);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
    TextureRect_8bIA(&gMasterDisp, gTitleCopyrightSymbol, 16, 16, 234.0f, 20.0f, 1.0f, 1.0f);
}

void Title_8018F8E4(void) {
    f32 temp2;
    s32 i;
    static f32 D_menu_801AE464 = 68.0f;
    static f32 D_menu_801AE468 = 170.0f;
    static f32 D_menu_801AE46C = 5.55f;
    static f32 D_menu_801AE470 = 0.9f;
    static f32 D_menu_801AE474 = 70.0f;
    static f32 D_menu_801AE478 = 172.0f;

    if (gControllerLock == 0) {
        temp2 = 188.0f;

        if ((s32) Math_SmoothStepToF(&D_menu_801B7BC8, D_menu_801B7BCC, 0.5f, 100.0f, 1.0f) == 0.0f) {
            if (D_menu_801B7BC8 == 32.0f) {
                D_menu_801B7BCC = 255.0f;
            } else {
                D_menu_801B7BCC = 32.0f;
            }
        }

        if (gMainController < 0) {
            RCP_SetupDL(&gMasterDisp, 0x55);

            gDPSetPrimColor(gMasterDisp++, 0, 0, 60, 60, 255, 200);

            TextureRect_8bCI(&gMasterDisp, D_TITLE_601D750, D_TITLE_601DB50, 32, 32, D_menu_801AE464, D_menu_801AE468,
                             D_menu_801AE46C, D_menu_801AE470);
            RCP_SetupDL(&gMasterDisp, 0x53);

            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, (s32) D_menu_801B7BC8, (s32) D_menu_801B7BC8, 255);

            TextureRect_8bIA(&gMasterDisp, gTitleNoController, 176, 24, D_menu_801AE474, D_menu_801AE478, 1.0f, 1.0f);
        } else {
            RCP_SetupDL(&gMasterDisp, 0x53);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, (s32) D_menu_801B7BC8, (s32) D_menu_801B7BC8, 255);

            TextureRect_8bIA(&gMasterDisp, gTitlePressStart, 120, 13, 101.0f, temp2, 1.0f, 1.0f);
        }
    }
}

void Title_8018FC14(void) {
    s32 i;

    RCP_SetupDL(&gMasterDisp, 0x53);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    TextureRect_8bIA(&gMasterDisp, gTitleNintendoCopyright, 120, 12, 102.0f, 209.0f, 1.0f, 1.0f);
}

void Title_8018FD08(void) {
    s32 i;
    Gfx* temp_v1;
    f32 temp_fs2;
    s32 var_s0;
    s32 var_s0_2;
    f32 temp;
    static f32 D_menu_801AE47C[] = { 90.0f, 100.0f, 75.0f, 75.0f };

    temp_fs2 = D_menu_801AE47C[D_menu_801B8340];
    temp = 210.0f;

    RCP_SetupDL(&gMasterDisp, 0x53);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    switch (D_menu_801B8340) {
        case 0:
            TextureRect_8bIA(&gMasterDisp, gTitleSlippyCard, 144, 13, temp_fs2, temp, 1.0f, 1.0f);
            break;

        case 1:
            TextureRect_8bIA(&gMasterDisp, gTitlePeppyCard, 120, 13, temp_fs2, temp, 1.0f, 1.0f);
            break;

        case 2:
            TextureRect_8bIA(&gMasterDisp, gTitleFalcoCard, 176, 13, temp_fs2, temp, 1.0f, 1.0f);
            break;

        case 3:
            TextureRect_8bIA(&gMasterDisp, gTitleFoxCard, 176, 13, temp_fs2, temp, 1.0f, 1.0f);
            break;
    }
}

static Gfx* D_menu_801AE48C[12] = {
    D_TITLE_6036290, D_TITLE_6036290, D_TITLE_6036290, D_TITLE_6036290, D_TITLE_6036B30, D_TITLE_6036290,
    D_TITLE_6036290, D_TITLE_6036290, D_TITLE_6036290, D_TITLE_6036290, D_TITLE_6036B30, D_TITLE_6036290,
};

static f32 D_menu_801AE4BC[12] = {
    0.0f, 0.0f, 0.0f, 0.0f, 10.0f, 13.0f, 20.0f, 35.0f, 40.0f, 50.0f, 50.0f, 70.0f,
};

static f32 D_menu_801AE4EC[] = {
    20.0f, 22.0f, 24.0f, 28.0f, 30.0f, 14.0f, 16.0f, 18.0f, 27.0f, 28.0f, 70.0f, 40.0f,
};

static u8 D_menu_801AE51C[] = {
    0xC0, 0x80, 0x60, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
};

static s32 D_menu_801AE528[] = {
    80, 64, 48, 32, 12, 32, 44, 32, 42, 36, 12, 38,
};

void Title_8018FF74(void) {
    if (D_menu_801B7BD8 != 0) {
        if ((D_menu_801B7BB8 > -870.0f) && (D_menu_801B7BB8 < 900.0f) && (gFillScreenAlpha > 0)) {
            if ((D_menu_801B7BB8 < 0.0f) && (D_menu_801B7BD0 < 255)) {
                D_menu_801B7BD0 += 2;
            }
            if ((D_menu_801B7BB8 > 0.0f) && (D_menu_801B7BD0 > 0)) {
                D_menu_801B7BD0 -= 2;
            }

            RCP_SetupDL(&gMasterDisp, 0x53);

            gDPSetAlphaDither(gMasterDisp++, G_AD_NOISE);
            gDPSetColorDither(gMasterDisp++, G_CD_NOISE);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, D_menu_801B7BD0);

            TextureRect_16bRGBA(&gMasterDisp, gTitleSunBeam, 32, 32, D_menu_801B9080, D_menu_801B9084, D_menu_801B7BB0,
                                D_menu_801B7BB4);
            D_menu_801B9080 += 1.66f;
        }

        Title_801918FC();
        Title_80190144();
        Title_801903B8();

        Matrix_Pop(&gGfxMatrix);
    }
}

void Title_80190144(void) {
    s32 i;

    if (gFillScreenAlpha > 0) {
        gFillScreenAlpha -= 4;
    }

    D_ctx_801783D0 = D_menu_801B7BB8;
    D_ctx_801783D4 = D_menu_801B7BBC;

    if (D_ctx_801783D0 < 950.0f) {
        if (D_ctx_801783D0 > -900.0f) {
            gFillScreenAlpha += 8;
            if (gFillScreenAlpha > 60) {
                gFillScreenAlpha = 60;
            }
            gFillScreenRed = 208;
            gFillScreenGreen = 208;
            gFillScreenBlue = 208;
        }
    }

    if (gFillScreenAlpha > 0) {
        RCP_SetupDL(&gMasterDisp, 0x3E);

        gDPSetAlphaDither(gMasterDisp++, G_AD_NOISE);
        gDPSetColorDither(gMasterDisp++, G_CD_NOISE);

        Matrix_Push(&gGfxMatrix);
        Matrix_Translate(gGfxMatrix, D_ctx_801783D0, D_ctx_801783D4, -200.0f, 1);

        for (i = 0; i < 4; i++) {
            Matrix_Push(&gGfxMatrix);
            Matrix_Scale(gGfxMatrix, D_menu_801AE4EC[i] * 0.5f, D_menu_801AE4EC[i] * 0.5f, D_menu_801AE4EC[i] * 0.5f,
                         1);
            Matrix_SetGfxMtx(&gMasterDisp);

            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, D_menu_801AE51C[i], D_menu_801AE528[i]);
            gSPDisplayList(gMasterDisp++, D_menu_801AE48C[i]);

            Matrix_Pop(&gGfxMatrix);
        }
        Matrix_Pop(&gGfxMatrix);
    }
}

void Title_801903B8(void) {
    static s32 D_menu_801AE558 = 12;
    f32 temp_fs3;
    f32 temp_fs4;
    f32 var_fs1;
    f32 temp;
    s32 i;

    RCP_SetupDL(&gMasterDisp, 0x3E);

    gDPSetAlphaDither(gMasterDisp++, G_AD_NOISE);
    gDPSetColorDither(gMasterDisp++, G_CD_NOISE);

    if (gFillScreenAlpha > 0) {
        temp_fs3 = D_ctx_801783D0 * -0.03f;
        temp_fs4 = D_ctx_801783D4 * 0.03f;

        var_fs1 = 1.0f;
        if (gFillScreenAlpha < 10) {
            var_fs1 = gFillScreenAlpha / 10.0f;
        }

        var_fs1 *= 0.5f;

        Matrix_Push(&gGfxMatrix);
        Matrix_Translate(gGfxMatrix, D_ctx_801783D0, D_ctx_801783D4, -200.0f, 1);

        for (i = 4; i < 12; i++) {
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, D_menu_801AE4BC[i] * temp_fs3, -D_menu_801AE4BC[i] * temp_fs4, 0.0f, 1);
            Matrix_Scale(gGfxMatrix, D_menu_801AE4EC[i] * 0.5f, D_menu_801AE4EC[i] * 0.5f, D_menu_801AE4EC[i] * 0.5f,
                         1);

            Matrix_SetGfxMtx(&gMasterDisp);

            temp = D_menu_801AE528[i] * var_fs1;

            if (i != 10) {
                gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, D_menu_801AE51C[i], (s32) temp);
            } else {
                gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, D_menu_801AE51C[i], D_menu_801AE558);
            }
            gSPDisplayList(gMasterDisp++, D_menu_801AE48C[i]);
            Matrix_Pop(&gGfxMatrix);
        }
        Matrix_Pop(&gGfxMatrix);
    }
}

void Title_801906A0(void) {
    s32 i;

    switch (D_menu_801B7BD4) {
        case 0:
            RCP_SetupDL(&gMasterDisp, 0x55);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, (s32) D_menu_801B7BDC);
            TextureRect_4bCI(&gMasterDisp, gTextIntroStarfox, gTextIntroStarfoxPalette, 256, 13, 90.0f, 110.0f, 1.0f,
                             1.0f);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, (s32) D_menu_801B7BE0);
            TextureRect_4bCI(&gMasterDisp, gTextIntroIn, gTextIntroInPalette, 32, 13, 150.0f, 110.0f, 1.0f, 1.0f);
            break;

        case 1:
            RCP_SetupDL(&gMasterDisp, 0x53);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, (s32) D_menu_801B7BDC);
            TextureRect_16bRGBA(&gMasterDisp, gTitleNintendo64Logo, 128, 88, D_menu_801B9070, D_menu_801B9074,
                                D_menu_801B9078, D_menu_801B907C);

        case -1:
            break;
    }
}

void Title_80190950(void) {
    Lights_SetOneLight(&gMasterDisp, D_menu_801B82E0, D_menu_801B82E4, D_menu_801B82E8, 0, 0, 0, gAmbientR, gAmbientG,
                       gAmbientB);
    RCP_SetupDL(&gMasterDisp, 0x17);

    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, 0.0f, D_menu_801B9048, D_menu_801B904C, 1);
    Matrix_Scale(gGfxMatrix, 0.4f, 0.4f, 0.4f, 1);
    Matrix_SetGfxMtx(&gMasterDisp);

    gSPDisplayList(gMasterDisp++, D_TITLE_6018D40);

    if (D_menu_801B7BE4 != 0) {
        Title_80190A98();
    }

    Matrix_Pop(&gGfxMatrix);
}

void Title_80190A98(void) {
    Matrix_Translate(gGfxMatrix, 401.0f, -249.0f, -22.0f, 1);
    Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 1.0f, 1);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_TITLE_602A720);
}

void Title_80190B30(s32 arg0) {
    Lights_SetOneLight(&gMasterDisp, D_menu_801B82E0, D_menu_801B82E4, D_menu_801B82E8, gLight1R, gLight1G, gLight1B,
                       gAmbientR, gAmbientG, gAmbientB);
    RCP_SetupDL(&gMasterDisp, 0x17);

    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, D_menu_801B84E8[arg0].unk_00.x, -12.8f, D_menu_801B9044, 1);
    Matrix_Scale(gGfxMatrix, 0.8f, 0.8f, 0.8f, 1);
    Matrix_SetGfxMtx(&gMasterDisp);

    gSPDisplayList(gMasterDisp++, D_TITLE_601C7C0);

    Matrix_Pop(&gGfxMatrix);
}

void Title_80190C9C(void) {
    s32 i;
    static f32 D_menu_801AE55C = 89.0f;
    static f32 D_menu_801AE560 = 17.0f;
    static f32 D_menu_801AE564 = 101.0f;
    static f32 D_menu_801AE568 = 197.0f;

    switch (D_menu_801B7BF0) {
        case 0:
            break;

        case 1:
            RCP_SetupDL(&gMasterDisp, 0x53);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
            TextureRect_8bIA(&gMasterDisp, gTitleGreatFoxCard, 144, 28, D_menu_801AE55C, D_menu_801AE560, 1.0f, 1.0f);
            break;

        case 2:
            RCP_SetupDL(&gMasterDisp, 0x53);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

            TextureRect_8bIA(&gMasterDisp, gTitleArwingCard, 112, 26, D_menu_801AE564, D_menu_801AE568, 1.0f, 1.0f);
    }
}

void Title_80190E64(void) {
    if (D_menu_801B82C4 == 0) {
        Title_80190FD0();
    } else {
        Title_80190EA4();
    }
}

void Title_80190EA4(void) {
    switch (D_menu_801B8280) {
        case 0:
            if (gControllerPress[gMainController].button &
                (START_BUTTON | A_BUTTON | B_BUTTON | D_CBUTTONS | L_CBUTTONS | U_CBUTTONS |
                 R_CBUTTONS)) { // START, A, B, C-left, C-Down, C-Up, C-Right
                AUDIO_PLAY_SFX(0x49000003, gDefaultSfxSource, 4);
                D_menu_801B8284 = 0;
                D_menu_801B8280 = 1;
                gControllerLock = 30;
            }
            break;

        case 1:
            if (D_menu_801B8284 < 120) {
                D_menu_801B8284 += 18;
            } else {
                Audio_SetAudioSpec(0, 0x17);
                D_ctx_80178410 = 0;
                gRadioState = 0;
                D_menu_801B82C0 = 0;
                gDrawMode = DRAW_NONE;
                D_menu_801B82C4 = 0;
                gControllerLock = 30;
                D_menu_801B8284 = 0;
                D_menu_801B8280 = 0;
            }
            break;
    }
}

void Title_80190FD0(void) {
    if (gControllerLock == 0) {
        switch (D_menu_801B8280) {
            case 0:
                if (((gControllerPress[gMainController].button & START_BUTTON) ||
                     (gControllerPress[gMainController].button & A_BUTTON)) &&
                    (D_menu_801B8280 == 0)) {
                    AUDIO_PLAY_SFX(0x49000003, gDefaultSfxSource, 4);
                    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 30);
                    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 30);
                    D_menu_801B8284 = 0;
                    D_menu_801B8280 = 1;
                }
                break;

            case 1:
                if (D_menu_801B8284 < 120) {
                    D_menu_801B8284 += 18;
                } else {
                    gGameState = GSTATE_MENU;
                    gNextGameStateTimer = 2;
                    gOptionMenuStatus = OPTION_WAIT;
                    gDrawMode = DRAW_NONE;
                    D_ctx_80178410 = 0;
                    D_menu_801B8280 = 0;
                    D_menu_801B8284 = 0;
                    gControllerLock = 3;
                }
                break;
        }
    }
}

void Title_8019111C(void) {
    f32 x;
    f32 y;

    if ((D_menu_801B82B0 == 0) && (D_menu_801B9040 == 0) &&
        ((gControllerPress[gMainController].stick_x != 0) || (gControllerPress[gMainController].stick_y != 0))) {
        D_menu_801B9040 = 1;
        D_menu_801B86A4 = 0;
    }

    x = gControllerPress[gMainController].stick_x;
    y = gControllerPress[gMainController].stick_y;

    if (D_menu_801B9040 != 0) {
        if (((x * 0.2f) + D_menu_801B905C > -500.0f) && ((x * 0.2f) + D_menu_801B905C < 500.0f)) {
            D_menu_801B905C += x * 0.2f;
        }
        if (((y * 0.2f) + D_menu_801B9060 > -500.0f) && ((y * 0.2f) + D_menu_801B9060 < 500.0f)) {
            D_menu_801B9060 += y * 0.2f;
        }
    }

    if ((D_menu_801B9040 != 0) && (gControllerPress[gMainController].stick_x == 0) &&
        (gControllerPress[gMainController].stick_y == 0)) {
        D_menu_801B86A4++;
    } else {
        D_menu_801B86A4 = 0;
    }
}

void Title_801912A0(void) {
    switch (D_menu_801B869C) {
        case 0:
            gFillScreenAlpha -= 4;
            if (gFillScreenAlpha < 0) {
                gFillScreenAlpha = 0;
                D_menu_801B869C = 255;
            }
            break;

        case 1:
            gFillScreenAlpha += 15;
            if (gFillScreenAlpha > 255) {
                gFillScreenAlpha = 255;
                D_menu_801B869C = 255;
            }
            break;
    }
}

void Title_80191320(s32 arg0, f32* arg1, f32* arg2, f32* arg3, f32* arg4, f32* arg5, f32* arg6, f32 arg7, f32 arg8,
                    f32 arg9) {
    Vec3f sp54;
    Vec3f sp48;
    f32* sp44;
    f32* sp40;
    f32* sp3C;
    f32* var_t0;
    f32* var_v0;
    f32* var_v1;

    if (arg0 != 0) {
        var_v0 = arg4;
        var_v1 = arg5;
        var_t0 = arg6;
        sp44 = arg1;
        sp40 = arg2;
        sp3C = arg3;
    } else {
        var_v0 = arg1;
        var_v1 = arg2;
        var_t0 = arg3;
        arg9 = -arg9;
        sp44 = arg4;
        sp40 = arg5;
        sp3C = arg6;
    }

    sp48.x = 0.0f;
    sp48.y = 0.0f;
    sp48.z = arg9;

    Matrix_Translate(gCalcMatrix, *var_v0, *var_v1, *var_t0, 0);
    Matrix_RotateY(gCalcMatrix, M_DTOR * arg8, 1);
    Matrix_RotateX(gCalcMatrix, M_DTOR * arg7, 1);
    Matrix_MultVec3f(gCalcMatrix, &sp48, &sp54);

    *sp44 = sp54.x;
    *sp40 = sp54.y;
    *sp3C = sp54.z;

    sp48.x = 0.0f;
    sp48.y = 1.0f;
    sp48.z = 0.0f;

    Matrix_RotateY(gCalcMatrix, M_DTOR * arg8, 0);
    Matrix_RotateX(gCalcMatrix, M_DTOR * arg7, 1);
    Matrix_MultVec3f(gCalcMatrix, &sp48, &sp54);

    D_menu_801B829C = sp54.x;
    D_menu_801B82A0 = sp54.y;
    D_menu_801B82A4 = sp54.z;
}

void Title_801914AC(f32 arg0, f32 arg1, f32 arg2, f32* arg3, f32* arg4, f32* arg5, f32 arg6, f32* arg7, f32* arg8,
                    f32* arg9, f32 argA, f32 argB, f32 argC) {
    Vec3f sp44;
    Vec3f sp38;

    sp38.x = 0.0f;
    sp38.y = 0.0f;
    sp38.z = argA;

    Matrix_Translate(gCalcMatrix, arg0, arg1, arg2, 0);

    Matrix_RotateY(gCalcMatrix, M_DTOR * argC, 1);
    Matrix_RotateX(gCalcMatrix, M_DTOR * argB, 1);

    Matrix_MultVec3f(gCalcMatrix, &sp38, &sp44);

    *arg7 = sp44.x;
    *arg8 = sp44.y;
    *arg9 = sp44.z;

    sp38.x = 0.0f;
    sp38.y = 0.0f;
    sp38.z = arg6;

    Matrix_Translate(gCalcMatrix, arg0, arg1, arg2, 0);
    Matrix_RotateY(gCalcMatrix, M_DTOR * argC, 1);
    Matrix_RotateX(gCalcMatrix, M_DTOR * argB, 1);
    Matrix_MultVec3f(gCalcMatrix, &sp38, &sp44);

    *arg3 = sp44.x;
    *arg4 = sp44.y;
    *arg5 = sp44.z;

    sp38.x = 0.0f;
    sp38.y = 1.0f;
    sp38.z = 0.0f;

    Matrix_RotateY(gCalcMatrix, M_DTOR * argC, 0);
    Matrix_RotateX(gCalcMatrix, M_DTOR * argB, 1);
    Matrix_MultVec3f(gCalcMatrix, &sp38, &sp44);

    D_menu_801B829C = sp44.x;
    D_menu_801B82A0 = sp44.y;
    D_menu_801B82A4 = sp44.z;
}

void Title_80191674(f32 arg0, f32 arg1, f32 arg2, f32* arg3, f32* arg4, f32* arg5) {
    f32 sp34;
    f32 sp30;
    Vec3f sp24;
    Vec3f sp18;

    sp18.x = 0.0f;
    sp18.y = 0.0f;
    sp18.z = arg2;

    Title_80191798(&sp34, &sp30);

    Matrix_RotateX(gCalcMatrix, M_DTOR * -sp34, 0);
    Matrix_RotateY(gCalcMatrix, M_DTOR * -sp30, 1);
    Matrix_RotateY(gCalcMatrix, M_DTOR * arg1, 1);
    Matrix_RotateX(gCalcMatrix, M_DTOR * arg0, 1);

    Matrix_MultVec3f(gCalcMatrix, &sp18, &sp24);

    *arg3 = sp24.x;
    *arg4 = sp24.y;
    *arg5 = sp24.z;
}

void Title_80191798(f32* arg0, f32* arg1) {
    f32 temp_fv1 = gCsCamEyeX - gCsCamAtX;
    f32 temp_fv2 = gCsCamEyeY - gCsCamAtY;
    f32 temp_ft4 = gCsCamEyeZ - gCsCamAtZ;

    *arg0 = -Math_Atan2F(temp_fv2, sqrtf(SQ(temp_fv1) + SQ(temp_ft4))) * M_RTOD;
    *arg1 = Math_Atan2F(temp_fv1, temp_ft4) * M_RTOD;
}

void Title_80191844(f32 arg0, f32 arg1) {
    Vec3f sp24;
    Vec3f sp18;

    sp18.x = 0.0f;
    sp18.y = 1.0f;
    sp18.z = 0.0f;

    Matrix_RotateY(gCalcMatrix, M_DTOR * arg1, 0);
    Matrix_RotateX(gCalcMatrix, M_DTOR * arg0, 1);

    Matrix_MultVec3f(gCalcMatrix, &sp18, &sp24);

    D_menu_801B829C = sp24.x;
    D_menu_801B82A0 = sp24.y;
    D_menu_801B82A4 = sp24.z;
}

void Title_801918FC(void) {
    Matrix_Push(&gGfxMatrix);
    Matrix_LookAt(gGfxMatrix, gCsCamEyeX, gCsCamEyeY, gCsCamEyeZ, gCsCamAtX, gCsCamAtY, gCsCamAtZ, D_menu_801B829C,
                  D_menu_801B82A0, D_menu_801B82A4, 1);
    Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, 0.0f, 1);
    Matrix_SetGfxMtx(&gMasterDisp);
}

void Title_801919C4(u16** arg0, s32 arg1) {
    D_radio_80178720 = arg0;
    D_radio_80178724 = 0;
    D_ctx_80178308 = arg0[D_radio_80178724];
    D_ctx_80177D68 = arg1;
    gRadioState = 100;

    switch (gGameState) {
        case GSTATE_TITLE:
            D_radio_8017872C = 176;
            D_radio_80178728 = 85;
            D_radio_80178730 = 80.0f;
            D_radio_80178734 = 174.0f;
            D_radio_80178738 = 4.63f;
            D_radio_8017873C = 32.0f;
            D_radio_80178740 = 174.0f;
            break;

        case GSTATE_PLAY:
            D_radio_8017872C = 179;
            D_radio_80178728 = 79;
            D_radio_80178730 = 74.0f;
            D_radio_80178734 = 178.0f;
            D_radio_80178738 = 4.53f;
            D_radio_8017873C = 26.0f;
            D_radio_80178740 = 178.0f;
    }

    Audio_PlayVoice(Message_IdFromPtr(D_ctx_80178308));
}
