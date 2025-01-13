#include "prevent_bss_reordering.h"
#include "global.h"
#include "fox_option.h"
#include "assets/ast_vs_menu.h"
#include "assets/ast_text.h"
#include "assets/ast_versus.h"

#define VS_TIE 99

bool gVsMatchOver;
s32 gVsMatchState;
s32 D_versus_80178758;
s32 sUnlockLandmaster;
s32 sUnlockOnFoot;
s32 gVsCountdown[3];
s32 PAD_80178774;
s32 sVsDrawMode;
s32 sPlayerFormOption[4];
s32 sStartCountdown;
s32 sStartTimer;
s32 D_80178798;
s32 D_8017879C;
s32 D_801787A0;
s32 sVsMatchMenuOption;
s32 sVsWinner;
f32 D_801787AC;
f32 D_801787B0;
s32 sVsPlayerCount;
s32 D_801787B8;
s32 D_801787BC;
f32 D_801787C0;
f32 D_801787C4;
f32 D_801787C8;
f32 D_801787CC;
f32 D_801787D0;
f32 D_801787D8[4];
f32 D_801787E8[4];
s32 sPlayerRespawnTimer[4];
u16 sVsDisplayedScores[4];
s32 D_80178810[4];
s32 sPlayerDownFrames[4];
s32 D_80178830;
s32 D_80178838[5];
s32 D_80178850[4];
OSTime sDrawTime;
OSTime sPrevDrawTime;

s32 D_800D4A90 = 0;
s32 D_800D4A94 = 0;
s32 D_800D4A98 = 0;
bool sStartVsHurryBgm = false;
bool sVsHurryBgmPlaying = false;

void Versus_Exit(void) {
    s32 i;

    Memory_FreeAll();
    Play_ClearObjectData();

    for (i = 0; i < gCamCount; i++) {
        Audio_KillSfxBySource(gPlayer[i].sfxSource);
        Audio_StopPlayerNoise(i);
    }

    gGameState = GSTATE_INIT;
    gNextGameStateTimer = 2;
    gCamCount = 1;
    gPlayState = PLAY_STANDBY;
    gDrawMode = DRAW_NONE;
    gTitleState = 0;
    gOptionMenuStatus = OPTION_WAIT;
    gMapState = 0;
    gBgColor = 0;
    gPlayerGlareAlphas[0] = 0;
    gPlayerGlareAlphas[1] = 0;
    gPlayerGlareAlphas[2] = 0;
    gPlayerGlareAlphas[3] = 0;
    gSceneSetup = 0;
    gRadioState = 0;
    gVersusMode = 0;
    gFillScreenAlphaTarget = 0;
    gFillScreenAlpha = 255;
    gClearPlayerInfo = true;
}

void func_versus_800BC88C(f32 xPos, f32 yPos, f32 scale) {
    Lib_TextureRect_IA8(&gMasterDisp, D_VS_MENU_7003830, 64, 17, xPos, yPos, scale, scale);
}

void func_versus_800BC8D8(f32 xPos, f32 yPos, f32 scale) {
    Lib_TextureRect_CI8(&gMasterDisp, D_versus_300A470, D_versus_300B218, 152, 23, xPos, yPos, scale, scale);
}

void func_versus_800BC9DC(f32 xPos, f32 yPos, f32 scale, s32 yScale) {
    u16* D_800D4AA4[] = { D_versus_3008DE0, D_versus_30098C0, D_versus_300A390 };
    u8* D_800D4ABC[] = { D_versus_30087A0, D_versus_3008EC0, D_versus_3009990 };
    s32 D_800D4AB0[] = { 40, 64, 64 };

    Lib_TextureRect_CI8(&gMasterDisp, D_800D4ABC[yScale], D_800D4AA4[yScale], D_800D4AB0[yScale], 40, xPos, yPos, scale,
                     scale);
}

void func_versus_800BCB44(f32 xPos, f32 yPos, f32 scale) {
    Lib_TextureRect_CI8(&gMasterDisp, D_versus_3006C60, D_versus_3007500, 96, 23, xPos, yPos, scale, scale);
}

void func_versus_800BCC48(f32 xPos, f32 yPos, f32 xScale, f32 yScale, s32 arg4) {
    u16* D_800D4AC8[] = { D_versus_3006A68, D_versus_3008598, D_versus_300C458, D_versus_3005E38 };
    u8* D_800D4AD8[] = { D_versus_3006040, D_versus_30076C0, D_versus_300B3F0, D_versus_3004F60 };
    s32 D_800D4AE8[] = { 104, 152, 168, 152 };

    Lib_TextureRect_CI8(&gMasterDisp, D_800D4AD8[arg4], D_800D4AC8[arg4], D_800D4AE8[arg4], 25, xPos, yPos, xScale,
                     yScale);
}

void func_versus_800BCE24(f32 xPos, f32 yPos, f32 xScale, f32 yScale) {
    Lib_TextureRect_CI8(&gMasterDisp, D_versus_3001420, D_versus_3003E20, 256, 42, xPos, yPos, xScale, yScale);
}

void func_versus_800BCEF8(f32 xPos, f32 yPos, f32 scale) {
    s32 i;

    Lib_TextureRect_CI8(&gMasterDisp, D_versus_3004010, D_versus_3004D58, 136, 25, xPos, yPos, scale, scale);
}

void func_versus_800BCFFC(f32 xPos, f32 yPos, f32 xScale, f32 yScale) {
    Lib_TextureRect_CI8(&gMasterDisp, aMsgWindowBgTex, aMsgWindowBgTLUT, 24, 17, xPos, yPos, xScale, yScale);
}

void func_versus_800BD05C(f32 xPos, f32 yPos, f32 scale) {
    Lib_TextureRect_CI4(&gMasterDisp, D_versus_30003A0, D_versus_30004E0, 64, 10, xPos, yPos, scale, scale);
}

void func_versus_800BD0B4(f32 xPos, f32 yPos, f32 scale) {
    Lib_TextureRect_CI4(&gMasterDisp, D_versus_3000510, D_versus_30006A0, 80, 10, xPos, yPos, scale, scale);
}

void func_versus_800BD10C(f32 xPos, f32 yPos, f32 scale) {
    Lib_TextureRect_CI4(&gMasterDisp, D_versus_30006D0, D_versus_3000810, 64, 10, xPos, yPos, scale, scale);
}

void func_versus_800BD164(f32 xPos, f32 yPos) {
    Lib_TextureRect_IA8(&gMasterDisp, D_VS_MENU_7003C70, 16, 16, xPos, yPos, 1.0f, 1.0f);
}

void func_versus_800BD1B0(f32 xPos, f32 yPos) {
    Lib_TextureRect_IA8(&gMasterDisp, D_VS_MENU_7003F10, 16, 16, xPos, yPos, 1.0f, 1.0f);
}

void func_versus_800BD1FC(f32 xPos, f32 yPos) {
    Lib_TextureRect_IA8(&gMasterDisp, D_VS_MENU_7003E10, 16, 16, xPos, yPos, 1.0f, 1.0f);
}

void func_versus_800BD248(f32 xPos, f32 yPos) {
    Lib_TextureRect_CI8(&gMasterDisp, D_VS_MENU_7004050, D_VS_MENU_7004150, 16, 16, xPos, yPos, 1.0f, 1.0f);
}

void func_versus_800BD2A0(f32 xPos, f32 yPos) {
    Lib_TextureRect_CI8(&gMasterDisp, D_VS_MENU_70041F0, D_VS_MENU_70042F0, 16, 16, xPos, yPos, 1.0f, 1.0f);
}

void func_versus_800BD2F8(f32 xPos, f32 yPos) {
    Lib_TextureRect_CI8(&gMasterDisp, D_VS_MENU_7004360, D_VS_MENU_7004460, 16, 16, xPos, yPos, 1.0f, 1.0f);
}

void func_versus_800BD350(f32 xPos, f32 yPos) {
    Lib_TextureRect_CI8(&gMasterDisp, D_VS_MENU_70044D0, D_VS_MENU_7004990, 64, 19, xPos, yPos, 1.0f, 1.0f);
}

void func_versus_800BD3A8(f32 xPos, f32 yPos) {
    Lib_TextureRect_CI4(&gMasterDisp, aVsHandicapFrameTex, aVsHandicapFrameTLUT, 80, 71, xPos, yPos, 1.0f,
                     1.0f);
}

void func_versus_800BD4D4(f32 xPos, f32 yPos, s32 arg2) {
    u8* D_800D4AF8[] = { aSmallText_0, aSmallText_1, aSmallText_2, aSmallText_3, aSmallText_4,
                         aSmallText_5, aSmallText_6, aSmallText_7, aSmallText_8, aSmallText_9 };
    bool var_s2 = false;
    s32 i = 1000;
    s32 j;

    arg2 %= i;

    for (i /= 10; i != 1; i /= 10) {
        j = arg2 / i;
        if (j || (var_s2 == true)) {
            Lib_TextureRect_IA8(&gMasterDisp, D_800D4AF8[j / i], 16, 8, xPos, yPos, 1.0f, 1.0f);
            xPos += 9.0f;
            arg2 %= i;
            var_s2 = true;
        }
    }
    Lib_TextureRect_IA8(&gMasterDisp, D_800D4AF8[arg2 / i], 16, 8, xPos, yPos, 1.0f, 1.0f);
}

void func_versus_800BD720(f32 xPos, f32 yPos) {
    Lib_TextureRect_IA8(&gMasterDisp, aVsStarTex, 8, 8, xPos, yPos, 1.0f, 1.0f);
}

void func_versus_800BD76C(f32 xPos, f32 yPos) {
    Lib_TextureRect_CI4(&gMasterDisp, D_versus_30001E0, D_versus_3000380, 64, 13, xPos, yPos, 1.0f, 1.0f);
}

void func_versus_800BD7C4(f32 xPos, f32 yPos, s32 arg2) {
    u8* D_800D4B20[] = { aSmallText_0, aSmallText_1, aSmallText_2, aSmallText_3, aSmallText_4,
                         aSmallText_5, aSmallText_6, aSmallText_7, aSmallText_8, aSmallText_9 };
    s32 i;

    for (i = 10; i != 1; i /= 10) {
        if ((xPos > 0) && (yPos > 0)) {
            Lib_TextureRect_IA8(&gMasterDisp, D_800D4B20[arg2 / i], 16, 8, xPos, yPos, 1.0f, 1.0f);
        }
        xPos += 9.0f;
        arg2 %= i;
    }

    if ((xPos > 0) && (yPos > 0)) {
        Lib_TextureRect_IA8(&gMasterDisp, D_800D4B20[arg2 / i], 16, 8, xPos, yPos, 1.0f, 1.0f);
    }
}

void func_versus_800BD9FC(f32 xPos, f32 yPos) {
    Lib_TextureRect_CI4(&gMasterDisp, D_1011E80, D_1011EC0, 16, 8, xPos, yPos, 1.0f, 1.0f);
}

void func_versus_800BDA54(f32 xPos, f32 yPos) {
    Lib_TextureRect_IA8(&gMasterDisp, aSmallText_L, 8, 8, xPos, yPos, 1.0f, 1.0f);
}

void func_versus_800BDAA0(f32 xPos, f32 yPos, s32 arg2, s32 arg3, s32 arg4) {
    u8* D_800D4B48[] = { aLargeText_0, aLargeText_1, aLargeText_2, aLargeText_3, aLargeText_4,
                         aLargeText_5, aLargeText_6, aLargeText_7, aLargeText_8, aLargeText_9 };
    s32 i = 1000;
    s32 temp1;
    s32 temp2;
    s32 temp3 = arg2;
    s32 y3 = arg3;

    arg2 %= i;
    arg3 %= i;

    for (i /= 10; i >= 1; i /= 10) {
        temp1 = arg2 / i;
        temp2 = arg3 / i;
        if (temp1 == temp2) {
            Lib_TextureRect_IA8(&gMasterDisp, D_800D4B48[temp1], 16, 15, xPos, yPos, 0.7f, 0.7f);
        } else {
            if (temp3 < y3) {
                Lib_TextureRect_IA8(&gMasterDisp, D_800D4B48[temp2], 16, arg4, xPos, yPos, 0.7f, 0.7f);
            }
        }
        xPos += 13.0f * 0.7f;
        arg2 %= i;
        arg3 %= i;
    }
}

void Versus_dummy_800BDE3C(void) {
}

void func_versus_800BDE44(void) {
    s32 i;
    f32 D_800D4B70[] = { 82.0f, 242.0f, 82.0f, 242.0f };
    f32 D_800D4B80[] = { 82.0f, 82.0f, 202.0f, 202.0f };

    RCP_SetupDL(&gMasterDisp, SETUPDL_76);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);

    for (i = 0; i < 4; i++) {
        if ((gPlayer[i].state == PLAYERSTATE_ACTIVE) || (gPlayer[i].state == PLAYERSTATE_U_TURN)) {
            if ((gPlayerScores[i] != sVsDisplayedScores[i]) || (D_80178810[i] != 0)) {
                D_80178810[i] += 4;
                if (D_80178810[i] > 15) {
                    if (gPlayerScores[i] > sVsDisplayedScores[i]) {
                        sVsDisplayedScores[i] += 1; // can't be ++
                    } else {
                        sVsDisplayedScores[i] -= 1; // can't be --
                    }

                    if (gPlayerScores[i] != sVsDisplayedScores[i]) {
                        D_80178810[i] -= 15;
                    } else {
                        D_80178810[i] = 0;
                    }
                    AUDIO_PLAY_SFX(NA_SE_COUNT_UP, gDefaultSfxSource, 4);
                }
            }

            if (gPlayerScores[i] >= sVsDisplayedScores[i]) {
                func_versus_800BDAA0(D_800D4B70[i], D_800D4B80[i], sVsDisplayedScores[i] + 1, sVsDisplayedScores[i],
                                     D_80178810[i]);
            } else {
                func_versus_800BDAA0(D_800D4B70[i], D_800D4B80[i], sVsDisplayedScores[i] - 1, sVsDisplayedScores[i],
                                     D_80178810[i]);
            }
        }
    }
}

s32 Versus_UpdateTimer(void) {
    s32 temp = (s32) CYCLES_TO_USEC((sDrawTime - sPrevDrawTime)) / 10000;

    gVsCountdown[2] -= temp;
    if (gVsCountdown[2] < 0) {
        gVsCountdown[2] *= -1;
        temp = (gVsCountdown[2] / 100) + 1;
        gVsCountdown[2] %= 100;
        gVsCountdown[2] = (100 - gVsCountdown[2]) % 100;
        gVsCountdown[1] -= temp;

        if (gVsCountdown[1] >= 0) {
            if ((gVsCountdown[0] == 0) && (gVsCountdown[1] < 15) && (gVsCountdown[1] >= 0)) {
                AUDIO_PLAY_SFX(NA_SE_COUNTDOWN, gDefaultSfxSource, 4);
            }
        } else {
            // clang-format off
            if (gVsCountdown[0] == 0) {\
                AUDIO_PLAY_SFX(NA_SE_TIME_OVER, gDefaultSfxSource, 4);\
            }
            // clang-format on
            gVsCountdown[1] *= -1;
            temp = (gVsCountdown[1] / 60) + 1;
            gVsCountdown[1] %= 60;
            gVsCountdown[1] = (60 - gVsCountdown[1]) % 60;
            gVsCountdown[0] -= temp;
            if (gVsCountdown[0] < 0) {
                gVsCountdown[0] = 0;
                gVsCountdown[1] = 0;
                gVsCountdown[2] = 0;
            }
        }
    }

    return 0;
}

s32 Versus_DrawCountdown(f32 xPos, f32 yPos, s32* countdown) {
    s32 i;
    f32 xTemp;
    f32 x;
    f32 y;
    s32 temp;

    RCP_SetupDL(&gMasterDisp, SETUPDL_78);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 0, 0, 0, 255);
    Lib_TextureRect_CI8(&gMasterDisp, aMsgWindowBgTex, aMsgWindowBgTLUT, 24, 17, 120.0f, 115.0f, 3.33f, 0.53f);

    xTemp = 0.0f;

    x = xPos;
    y = yPos;

    for (i = 0; i < 5; i++) {
        if ((i == 0) || (i == 2)) {
            temp = countdown[i / 2] % 60;
        }

        if (i == 4) {
            temp = countdown[i / 2] % 100;
        }

        if ((i % 2) == 1) {
            RCP_SetupDL(&gMasterDisp, SETUPDL_78);
            func_versus_800BD9FC(x + xTemp, y);
        } else {
            RCP_SetupDL(&gMasterDisp, SETUPDL_76);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);
            func_versus_800BD7C4(x + xTemp, y, temp);
            xTemp += 9.0f;
        }

        xTemp += 9.0f;
    }

    return 0;
}

s32 Versus_SelectStartingForm(void) {
    s32 i;
    s32 ret = 0;

    if ((!sUnlockLandmaster && !sUnlockOnFoot) || (gVersusStage == VS_STAGE_SECTOR_Z)) {
        for (i = 0; i < 4; i++) {
            if (gPlayerInactive[i]) {
                continue;
            }
            sPlayerFormOption[i] = 1;
            gPlayerForms[i] = FORM_ARWING;
            ret++;
        }
        return ret;
    }

    for (i = 0; i < 4; i++) {
        if (gPlayerInactive[i]) {
            continue;
        }

        if ((sPlayerFormOption[i] == 0) && (sPlayerRespawnTimer[i] == 0)) {
            if (sUnlockLandmaster && sUnlockOnFoot) {
                sPlayerFormOption[i] = RAND_INT(3.0f) + 1;
            }
            if (sUnlockLandmaster && !sUnlockOnFoot) {
                sPlayerFormOption[i] = RAND_INT(2.0f) + 1;
            }
        }

        if (sPlayerRespawnTimer[i] != 0) {
            sPlayerRespawnTimer[i]--;
        }

        if (sUnlockLandmaster && (sPlayerFormOption[i] == 0) && (gControllerPress[i].button & B_BUTTON)) {
            AUDIO_PLAY_SFX(NA_SE_DECIDE, gDefaultSfxSource, 4);
            sPlayerFormOption[i] = 2;
        }

        if (sUnlockOnFoot && (sPlayerFormOption[i] == 0) &&
            ((gControllerPress[i].button & L_CBUTTONS) || (gControllerPress[i].button & D_CBUTTONS) ||
             (gControllerPress[i].button & U_CBUTTONS) || (gControllerPress[i].button & R_CBUTTONS))) {
            AUDIO_PLAY_SFX(NA_SE_DECIDE, gDefaultSfxSource, 4);
            sPlayerFormOption[i] = 3;
        }

        if ((sPlayerFormOption[i] == 0) && (gControllerPress[i].button & A_BUTTON)) {
            AUDIO_PLAY_SFX(NA_SE_DECIDE, gDefaultSfxSource, 4);
            sPlayerFormOption[i] = 1;
        }

        if (sPlayerFormOption[i] != 0) {
            switch (sPlayerFormOption[i]) {
                case 1:
                    gPlayerForms[i] = FORM_ARWING;
                    break;
                case 2:
                    gPlayerForms[i] = FORM_LANDMASTER;
                    break;
                case 3:
                    gPlayerForms[i] = FORM_ON_FOOT;
                    break;
                default:
                    gPlayerForms[i] = FORM_ARWING;
                    break;
            }
            ret++;
        }
    }

    return ret;
}

void func_versus_800BE924(s32 index) {
    f32 D_800D4B90[] = { 40.0f, 200.0f, 40.0f, 200.0f };
    f32 D_800D4BA0[] = { 20.0f, 20.0f, 140.0f, 140.0f };

    RCP_SetupDL(&gMasterDisp, SETUPDL_78);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
    func_versus_800BD3A8(D_800D4B90[index] + 0.0f, D_800D4BA0[index] + 10.0f);
    func_versus_800BD350(D_800D4B90[index] + 5.0f, D_800D4BA0[index] + 0.0f);

    if (sUnlockLandmaster && sUnlockOnFoot) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_78);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
        func_versus_800BD248(D_800D4B90[index] + 15.0f, D_800D4BA0[index] + 22.0f);
        func_versus_800BD2A0(D_800D4B90[index] + 15.0f, D_800D4BA0[index] + 40.0f);
        func_versus_800BD2F8(D_800D4B90[index] + 15.0f, D_800D4BA0[index] + 58.0f);

        RCP_SetupDL(&gMasterDisp, SETUPDL_76);
        func_versus_800BD164(D_800D4B90[index] + 43.0f, D_800D4BA0[index] + 22.0f);
        func_versus_800BD1B0(D_800D4B90[index] + 43.0f, D_800D4BA0[index] + 40.0f);
        func_versus_800BD1FC(D_800D4B90[index] + 43.0f, D_800D4BA0[index] + 58.0f);
    }

    if (sUnlockLandmaster && !sUnlockOnFoot) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_78);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
        func_versus_800BD248(D_800D4B90[index] + 15.0f, D_800D4BA0[index] + 29.0f);
        func_versus_800BD2A0(D_800D4B90[index] + 15.0f, D_800D4BA0[index] + 51.0f);

        RCP_SetupDL(&gMasterDisp, SETUPDL_76);
        func_versus_800BD164(D_800D4B90[index] + 43.0f, D_800D4BA0[index] + 29.0f);
        func_versus_800BD1B0(D_800D4B90[index] + 43.0f, D_800D4BA0[index] + 51.0f);
    }

    RCP_SetupDL(&gMasterDisp, SETUPDL_76);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);
    func_versus_800BD4D4(D_800D4B90[index] + 32.0f, D_800D4BA0[index] + 84.0f, (sPlayerRespawnTimer[index] / 30) + 1);
}

void func_versus_800BECA8(s32 index) {
    f32 D_800D4BB0[] = { 40.0f, 200.0f, 40.0f, 200.0f };
    f32 D_800D4BC0[] = { 40.0f, 40.0f, 160.0f, 160.0f };

    RCP_SetupDL(&gMasterDisp, SETUPDL_76);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 30, 0, 255);
    func_versus_800BC88C(D_800D4BB0[index], D_800D4BC0[index], 1.0f);
}

void func_versus_800BED78(void) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_78);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
    func_versus_800BC8D8(84.0f, 108.0f, 1.0f);
}

s32 func_versus_800BEDDC(void) {
    s32 i;
    s32 var_s4 = 0;

    if (!sUnlockLandmaster && !sUnlockOnFoot || (gVersusStage == VS_STAGE_SECTOR_Z)) {
        func_versus_800BED78();
        return 0;
    }

    for (i = 0; i < 4; i++) {
        if (gPlayerInactive[i]) {
            continue;
        }

        if (sPlayerFormOption[i] == 0) {
            func_versus_800BE924(i);
        } else {
            func_versus_800BECA8(i);
        }

        if (sPlayerFormOption[i] != 0) {
            var_s4++;
            if (var_s4 == sVsPlayerCount) {
                func_versus_800BED78();
            }
        }
    }

    return 0;
}

s32 Versus_UpdateStartCountdown(void) {
    s32 ret;

    ret = 0;
    if (sStartCountdown == 0) {
        return 2;
    }

    sStartTimer--;

    if (sStartTimer == 0) {
        sStartCountdown--;
        if (sStartCountdown != 0) {
            AUDIO_PLAY_SFX(NA_SE_READY, gDefaultSfxSource, 4);
            ret = 0;
        } else {
            AUDIO_PLAY_SFX(NA_SE_GO, gDefaultSfxSource, 4);
            ret = 1;
        }
        sStartTimer = 30;
    }

    return ret;
}

s32 func_versus_800BEFE4(void) {
    f32 D_800D4BD0[] = { 46.0f, 206.0f, 46.0f, 206.0f };
    f32 D_800D4BE0[] = { 40.0f, 40.0f, 160.0f, 160.0f };
    f32 D_800D4BF0[] = { 12.0f, 0.0f, 0.0f };
    s32 i;

    RCP_SetupDL(&gMasterDisp, SETUPDL_78);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    for (i = 0; i < 4; i++) {
        if (gPlayerInactive[i]) {
            continue;
        }

        if (sStartCountdown != 0) {
            func_versus_800BC9DC(D_800D4BD0[i] + D_800D4BF0[sStartCountdown - 1], D_800D4BE0[i], 1.0f,
                                 sStartCountdown - 1);
        } else {
            func_versus_800BCB44(D_800D4BD0[i] - 16.0f, D_800D4BE0[i], 1.0f);
        }
    }
    return 0;
}

s32 Versus_UpdatePlayerStatus(void) {
    s32 i;
    f32 ret;

    for (i = 0, ret = 0; i < 4; i++) {
        D_80178850[i] = true;

        if (gPlayer[i].state != PLAYERSTATE_VS_STANDBY) {
            D_80178850[i] = false;
            sPlayerRespawnTimer[i] = 150;
            continue;
        }

        if (gPlayerInactive[i] || (gVsMatchType == VS_MATCH_BATTLE) ||
            ((sVsPlayerCount == 1) && (gVsMatchType != VS_MATCH_TIME)) ||
            ((gVsMatchType == VS_MATCH_TIME) && VS_TIME_UP(gVsCountdown))) {
            ret = Math_SmoothStepToF(&D_801787D8[i], D_801787E8[i], 0.3f, 100.0f, 1.0f);
            if (ret == 0.0f) {
                if (D_801787E8[i] == 32.0f) {
                    D_801787E8[i] = 255.0f;
                } else {
                    D_801787E8[i] = 32.0f;
                }
            }
            gPlayer[i].csState = 0;
        } else {
            sPlayerFormOption[i] = 0;
            gPlayer[i].csState = 0;
            if ((sPlayerFormOption[i] == 0) && (sPlayerRespawnTimer[i] == 0)) {
                if (sUnlockLandmaster && sUnlockOnFoot) {
                    sPlayerFormOption[i] = RAND_INT(3.0f) + 1;
                }
                if (sUnlockLandmaster && !sUnlockOnFoot) {
                    sPlayerFormOption[i] = RAND_INT(2.0f) + 1;
                }
            }

            if (sPlayerRespawnTimer[i] != 0) {
                sPlayerRespawnTimer[i]--;
            }

            if (sUnlockLandmaster && (sPlayerFormOption[i] == 0) && (gControllerPress[i].button & B_BUTTON)) {
                sPlayerFormOption[i] = 2;
            }

            if (sUnlockOnFoot && (sPlayerFormOption[i] == 0) &&
                ((gControllerPress[i].button & L_CBUTTONS) || (gControllerPress[i].button & D_CBUTTONS) ||
                 (gControllerPress[i].button & U_CBUTTONS) || (gControllerPress[i].button & R_CBUTTONS))) {
                sPlayerFormOption[i] = 3;
            }

            if ((sPlayerFormOption[i] == 0) && (gControllerPress[i].button & A_BUTTON)) {
                sPlayerFormOption[i] = 1;
            }

            if ((!sUnlockLandmaster && !sUnlockOnFoot) || (gVersusStage == VS_STAGE_SECTOR_Z)) {
                D_80178850[i] = false;
                sPlayerFormOption[i] = 1;
            }

            if (sPlayerFormOption[i] != 0) {
                switch (sPlayerFormOption[i]) {
                    case 1:
                        gPlayerForms[i] = FORM_ARWING;
                        break;

                    case 2:
                        gPlayerForms[i] = FORM_LANDMASTER;
                        break;

                    case 3:
                        gPlayerForms[i] = FORM_ON_FOOT;
                        break;

                    default:
                        gPlayerForms[i] = FORM_ARWING;
                        break;
                }

                sPlayerDownFrames[i]++;

                if (gVsMatchType == VS_MATCH_TIME) {
                    gPlayerScores[i] = D_80178838[i] = sVsDisplayedScores[i] = D_80178810[i] = 0;
                }
                gPlayer[i].csState = 1;
            }
        }
    }

    return 0;
}

s32 func_versus_800BF59C(void) {
    s32 i;
    f32 D_800D4BFC[] = { 83.0f, 226.0f, 83.0f, 226.0f };
    f32 D_800D4C0C[] = { 102.0f, 102.0f, 209.0f, 209.0f };
    s32 colorGB;

    for (i = 0; i < 4; i++) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_78);

        if (D_80178850[i] == 0) {
            continue;
        }

        if (gPlayerInactive[i] || (gVsMatchType == VS_MATCH_BATTLE)) {
            colorGB = D_801787D8[i];
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, colorGB, colorGB, 255);
            func_versus_800BD76C(D_800D4BFC[i], D_800D4C0C[i]);
        } else {
            if (sUnlockLandmaster || sUnlockOnFoot) {
                func_versus_800BE924(i);
            }
        }
    }
    return 0;
}

void func_versus_800BF750(void) {
    s32 i;
    s32 j;
    f32 D_800D4C1C[] = { 112.0f, 272.0f, 112.0f, 272.0f };
    f32 D_800D4C2C[] = { 75.0f, 75.0f, 195.0f, 195.0f };
    s32 D_800D4C3C[] = { 177, 255, 0, 30 };
    s32 D_800D4C4C[] = { 242, 30, 179, 30 };
    s32 D_800D4C5C[] = { 12, 0, 67, 255 };
    s32 temp;

    RCP_SetupDL(&gMasterDisp, SETUPDL_76);

    for (i = 0; i < 4; i++) {
        if (gPlayer[i].state != PLAYERSTATE_ACTIVE) {
            continue;
        }
        for (j = 0, temp = 0; j < 4; j++) {
            if ((gVsLockOnTimers[i][j] != 0) && (gGameFrameCount & 4)) {
                gDPSetPrimColor(gMasterDisp++, 0, 0, D_800D4C3C[j], D_800D4C4C[j], D_800D4C5C[j], 255);
                func_versus_800BDA54(D_800D4C1C[i] + temp * 9.0f, D_800D4C2C[i]);
                temp++;
            }
        }
    }
}

bool Versus_CheckForWinner(void) {
    s32 i;
    s32 j;
    s32 tieScore;
    s32 numDown;
    bool beaten[4];

    switch (gVsMatchType) {
        case VS_MATCH_POINTS:
            for (i = 0, numDown = 0; i < 4; i++) {
                if (gPlayer[i].state != PLAYERSTATE_VS_STANDBY) {
                    sVsWinner = i;
                }
                if (gPlayer[i].state == PLAYERSTATE_VS_STANDBY) {
                    numDown++;
                }
            }

            if ((sVsPlayerCount == 1) && (numDown == 4)) {
                gVsMatchWon = true;
                sVsWinner = VS_TIE;
            } else {
                for (i = 0; i < 4; i++) {
                    if (gVsPoints[i] == gVsPointsToWin) {
                        break;
                    } else if (gVsPoints[i] == (gVsPointsToWin - 1)) {
                        sStartVsHurryBgm = true;
                    }
                }

                if (i >= 4) {
                    return false;
                }

                if (gPlayer[i].timer_278 != 0) {
                    return false;
                }

                for (j = 0; j < 4; j++) {
                    if (j == i) {
                        continue;
                    }
                    if (gPlayer[j].attacker >= 0) {
                        gPlayer[j].attacker = i + 1;
                    }
                    gPlayer[j].state = PLAYERSTATE_VS_STANDBY;
                }
                gVsMatchWon = true;
                sVsWinner = i;
            }
            break;

        case VS_MATCH_BATTLE:
            for (i = 0, numDown = 0; i < 4; i++) {
                if (gPlayer[i].state != PLAYERSTATE_VS_STANDBY) {
                    sVsWinner = i;
                }
                if (gPlayer[i].state == PLAYERSTATE_VS_STANDBY) {
                    numDown++;
                }
            }
            if ((sVsPlayerCount == 1) && (numDown == 4)) {
                gVsMatchWon = true;
                sVsWinner = VS_TIE;
            } else {
                if (numDown >= 2) {
                    sStartVsHurryBgm = true;
                }

                if ((numDown < 3) || (sVsPlayerCount == 1)) {
                    return false;
                }

                if (numDown >= 4) {
                    sVsWinner = VS_TIE;
                }

                for (j = 0; j < 4; j++) {
                    if (j == sVsWinner) {
                        continue;
                    }
                    if (gPlayer[j].attacker >= 0) {
                        gPlayer[j].attacker = i + 1;
                    }
                    gPlayer[j].state = PLAYERSTATE_VS_STANDBY;
                }
                gVsMatchWon = true;
            }
            break;

        case VS_MATCH_TIME:
            if (!VS_TIME_UP(gVsCountdown)) {
                return false;
            }

            if (gVsMatchType == VS_MATCH_TIME) {
                for (i = 0; i < 4; i++) {
                    if ((gPlayer[i].state == PLAYERSTATE_DOWN) || (gPlayer[i].state == PLAYERSTATE_VS_STANDBY)) {
                        gPlayerScores[i] = D_80178838[i] = sVsDisplayedScores[i] = D_80178810[i] = 0;
                        sPlayerDownFrames[i]++;
                    }
                }
            }

            for (i = 0; i < 4; i++) {
                beaten[i] = false;
            }

            for (i = 0; i < 4; i++) {
                if (!gControllerPlugged[i]) {
                    continue;
                }
                for (j = 0, tieScore = 0; j < 4; j++) {
                    if (!gControllerPlugged[j] || beaten[j] || (i == j)) {
                        continue;
                    }
                    if (gPlayerScores[i] < gPlayerScores[j]) {
                        beaten[i] = true;
                        break;
                    } else if (gPlayerScores[i] == gPlayerScores[j]) {
                        tieScore = true;
                    }
                }

                if ((j == 4) && !tieScore) {
                    sVsWinner = i;
                }
            }

            if (sVsWinner == VS_TIE) {
                for (i = 0; i < 4; i++) {
                    if (!gControllerPlugged[i] || beaten[i]) {
                        continue;
                    }
                    if (0) {}

                    for (j = 0, tieScore = 0; j < 4; j++) {
                        if (!gControllerPlugged[j] || beaten[j] || (i == j)) {
                            continue;
                        }
                        if (sPlayerDownFrames[i] > sPlayerDownFrames[j]) {
                            beaten[i] = true;
                            break;
                        } else if (sPlayerDownFrames[i] == sPlayerDownFrames[j]) {
                            tieScore = true;
                        }
                    }
                    if ((j == 4) && !tieScore) {
                        sVsWinner = i;
                    }
                }

                if (sVsWinner == VS_TIE) {
                    for (i = 0; i < 4; i++) {
                        if (!gControllerPlugged[i] || beaten[i]) {
                            continue;
                        }
                        for (j = 0, tieScore = 0; j < 4; j++) {
                            if (!gControllerPlugged[j] || beaten[j] || (i == j)) {
                                continue;
                            }
                            if (gPlayer[i].shields < gPlayer[j].shields) {
                                beaten[i] = true;
                                break;
                            } else if (gPlayer[i].shields == gPlayer[j].shields) {
                                tieScore = true;
                            }
                        }
                        if ((j == 4) && !tieScore) {
                            sVsWinner = i;
                        }
                    }
                }
            }

            for (j = 0; j < 4; j++) {
                if (j == sVsWinner) {
                    continue;
                }

                if (gPlayer[j].attacker >= 0) {
                    gPlayer[j].attacker = i + 1;
                }

                gPlayer[j].state = PLAYERSTATE_VS_STANDBY;
            }
            gVsMatchWon = true;
            break;

        default:
            break;
    }

    return true;
}

void func_versus_800C024C(void) {
    D_801787BC = 1;
    D_80178798 = 0;
    D_801787C4 = 0.0f;
    D_801787C8 = 1.0f;
    D_801787C0 = 400.0f;
}

bool func_versus_800C0294(s32 index) {
    f32 D_800D4C6C[] = { 108.0f, 84.0f, 79.0f, 84.0f, 36.0f };
    s32 ret = false;
    s32 temp;

    if (index == VS_TIE) {
        index = 4;
    }

    switch (D_801787BC) {
        case 0:
            break;

        case 1:
            if ((D_801787C0 -= (D_801787C4 += 10.0f)) <= (D_800D4C6C[index] * 0.8f)) {
                D_801787BC = 2;
                D_801787C0 = D_800D4C6C[index] * 0.8f;
            }
            break;

        case 2:
            if (Math_SmoothStepToF(&D_801787C8, 0.3f, 0.4f, 100.0f, 0.01f) == 0.0f) {
                D_801787BC = 3;
                D_801787C4 = 0.0f;
            }
            break;

        case 3:
            temp = Math_SmoothStepToF(&D_801787C8, 1.0f, 0.6f, 100.0f, 0.1f);
            if (D_801787C0 < D_800D4C6C[index]) {
                D_801787C0 += (D_801787C4 += 3.0f);
            } else {
                D_801787C0 = D_800D4C6C[index];
            }

            if ((D_801787C0 == D_800D4C6C[index]) && (temp == 0.0f)) {
                D_801787BC = 4;
            }
            break;

        default:
            ret = true;
            break;
    }

    return ret;
}

s32 func_versus_800C04DC(f32 xPos, f32 scale, s32 arg2) {
    f32 x;
    f32 y;

    if ((gVsMatchType == VS_MATCH_TIME) && ((D_800D4A98 & 0x20) != 0) && (sVsWinner != VS_TIE)) {
        x = 118.0f;
        y = 110.0f;

        RCP_SetupDL(&gMasterDisp, SETUPDL_78);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 0, 0, 0, 200);
        func_versus_800BCFFC(98.0f, 100.0f, 5.2f, 2.98f);

        RCP_SetupDL(&gMasterDisp, SETUPDL_83);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);

        Graphics_DisplaySmallText(x, y, 1.0f, 1.0f, "TOTAL");
        Graphics_DisplaySmallText(x + 45.0f, y, 1.0f, 1.0f, "SCORE");

        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
        HUD_Number_Draw(x + 18.0f, y + 16.0f, D_800D4A94, 1.0f, 0, 9999);
    } else {
        if (arg2 < 4) {
            RCP_SetupDL(&gMasterDisp, SETUPDL_78);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
            func_versus_800BCC48(xPos, 100.0f, scale, 1.0f, arg2);
        } else {
            RCP_SetupDL(&gMasterDisp, SETUPDL_78);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
            func_versus_800BCE24(xPos, 104.0f, scale, 1.0f);
        }
    }

    return 0;
}

s32 func_versus_800C075C(void) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_78);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
    func_versus_800BCEF8(94.0f, 126.0f, 1.0f);
    return 0;
}

s32 Versus_GetMenuInput(void) {
    s32 i;
    s32 stick_y = 0;
    s32 ret = 0;

    for (i = 0; i < 4; i++) {
        if (gControllerPlugged[i] == true) {
            stick_y = gControllerPress[i].stick_y;
            if (stick_y != 0) {
                break;
            }
        }
    }

    if (stick_y != 0) {
        if (stick_y > 0) {
            stick_y = -1;
        } else {
            stick_y = 1;
        }

        if (D_8017879C == 0) {
            ret = stick_y;
        }
        D_801787A0++;
        D_8017879C = stick_y;
    } else {
        D_8017879C = 0;
        D_801787A0 = 0;
    }

    // clang-format off
    if (ret != 0) { AUDIO_PLAY_SFX(NA_SE_CURSOR, gDefaultSfxSource, 4); }
    // clang-format on

    return ret;
}

bool func_versus_800C08D0(void) {
    f32 temp = 0.0f;

    temp += Math_SmoothStepToF(&D_801787CC, 1.55f, 0.6f, 10.0f, 0.04f);
    temp += Math_SmoothStepToF(&D_801787D0, 0.82f, 0.6f, 10.0f, 0.04f);

    if (temp != 0.0f) {
        return false;
    } else {
        return true;
    }
}

void func_versus_800C0970(f32 yScale1, f32 yScale2) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_78);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 0, 0, 0, 255);
    func_versus_800BCFFC(98.0f, 72.0f, 5.19f, yScale1);
    func_versus_800BCFFC(98.0f, 152.0f, 5.19f, yScale2);
}

s32 Versus_UpdateMenuOptions(void) {
    s32 input = Versus_GetMenuInput();

    if (input != 0) {
        D_801787AC = 255.0f;
        D_801787B0 = 255.0f;
        sVsMatchMenuOption += input;

        if (sVsMatchMenuOption >= 3) {
            sVsMatchMenuOption = 0;
            sVsMatchMenuOption = 0;
        }

        if (sVsMatchMenuOption < 0) {
            sVsMatchMenuOption = 2;
        }
    }

    if (Math_SmoothStepToF(&D_801787AC, D_801787B0, 0.5f, 100.0f, 1.0f) == 0.0f) {
        if (D_801787B0 == 32.0f) {
            D_801787B0 = 255.0f;
        } else {
            D_801787B0 = 32.0f;
        }
    }

    return sVsMatchMenuOption;
}

s32 func_versus_800C0B0C(void) {
    s32 i;
    s32 colorGB[3];

    RCP_SetupDL(&gMasterDisp, SETUPDL_78);

    for (i = 0; i < 3; i++) {
        if (i == sVsMatchMenuOption) {
            colorGB[i] = D_801787AC;
        } else {
            colorGB[i] = 255;
        }
    }

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, colorGB[0], colorGB[0], 255);
    func_versus_800BD05C(140.0f, 74.0f, 1.0f);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, colorGB[1], colorGB[1], 255);
    func_versus_800BD0B4(124.0f, 86.0f, 1.0f);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, colorGB[2], colorGB[2], 255);
    func_versus_800BD10C(144.0f, 154.0f, 1.0f);

    return 0;
}

bool Versus_UpdateMenu(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if ((gControllerPlugged[i] == true) && (gControllerPress[i].button & A_BUTTON)) {
            D_801787AC = 32.0f;
            return true;
        }
    }

    Versus_UpdateMenuOptions();

    return false;
}

bool func_versus_800C0D10(void) {
    s32 i;
    s32 cont;
    bool ret = false;

    switch (D_800D4A90) {
        case 0:
            // clang-format off
	        for (i = 0; i < 5; i++) { D_80178838[i] = 0; }
            // clang-format on
            D_800D4A90 = 1;
            D_800D4A94 = 0;
            break;

        case 1:
            cont = 0;

            for (i = 0; i < 4; i++) {
                if (gPlayerScores[i] == D_80178838[i]) {
                    cont++;
                    continue;
                }
                D_80178838[i]++;
                D_800D4A94++;
            }

            if (cont == 4) {
                D_800D4A90 = 2;
            } else {
                AUDIO_PLAY_SFX(NA_SE_COUNT_UP, gDefaultSfxSource, 4);
            }
            break;

        case 2:
            if (D_80178838[4] != D_800D4A94) {
                D_80178838[4]++;
            } else {
                ret = true;
            }
            break;

        default:
            break;
    }

    return ret;
}

s32 func_versus_800C0E78(void) {
    s32 i;
    u8* D_800D4C80[] = {
        "FOX",
        "PEPPY",
        "SLIPPY",
        "FALCO",
    };
    f32 D_800D4C90[5] = {
        32.0f, 168.0f, 32.0f, 168.0f, 0.0f,
    };
    f32 D_800D4CA4[5] = {
        20.0f, 20.0f, 200.0f, 200.0f, 0.0f,
    };

    for (i = 0; i < 4; i++) {
        if (gControllerPlugged[i] == true) {
            RCP_SetupDL(&gMasterDisp, SETUPDL_83);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);
            Graphics_DisplaySmallText(D_800D4C90[i], D_800D4CA4[i], 1.0f, 1.0f, D_800D4C80[i]);

            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
            HUD_Number_Draw(D_800D4C90[i], D_800D4CA4[i] + 9.0f, D_80178838[i], 1.0f, 0, 999);
        }
    }

    return 0;
}

bool func_versus_800C107C(s32 playerNum) {
    D_80178798++;
    if (D_80178798 == 10) {
        AUDIO_PLAY_SFX(NA_SE_COUNT_UP, gDefaultSfxSource, 4);
        D_801787B8++;
        D_80178798 = 0;
    }

    if (D_801787B8 < gVsPoints[playerNum]) {
        return false;
    } else {
        return true;
    }
}

s32 func_versus_800C1138(s32 max, s32 arg1) {
    f32 D_800D4CB8[] = { 24.0f, 248.0f, 24.0f, 248.0f };
    f32 D_800D4CC8[] = { 104.0f, 104.0f, 216.0f, 216.0f };
    s32 D_800D4CD8[] = { 177, 255, 0, 30 };
    s32 D_800D4CE8[] = { 242, 30, 179, 30 };
    s32 D_800D4CF8[] = { 12, 0, 67, 255 };
    s32 i;
    s32 j;

    for (i = 0; i < max; i++) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_77);
        j = gVsKills[arg1][i];
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
        gDPSetEnvColor(gMasterDisp++, D_800D4CD8[j], D_800D4CE8[j], D_800D4CF8[j], 0);
        func_versus_800BD720(D_800D4CB8[arg1] + (i * 9.0f), D_800D4CC8[arg1]);
    }

    return 0;
}

void Versus_InitMatch(void) {
    s32 i;

    for (i = 0, sVsPlayerCount = 0; i < 4; i++) {
        if (!gPlayerInactive[i]) {
            sVsPlayerCount++;
        }
        sPlayerFormOption[i] = 0;
        D_801787D8[i] = 0.0f;
        D_801787E8[i] = 0.0f;
    }

    D_801787CC = 0.0f;
    D_801787D0 = 0.0f;
    D_801787AC = 255.0f;
    D_801787B0 = 0.0f;
    gNextVsViewScale = 0.5f;
    sVsDrawMode = 0;
    sStartCountdown = 4;
    sStartTimer = 1;
    D_8017879C = 0;
    D_801787A0 = 0;
    sVsMatchMenuOption = 0;
    sVsWinner = VS_TIE;
    D_801787B8 = 0;
    gVsMatchOver = false;
    gBgColor = 0;
    D_80178830 = 0;
    D_800D4A90 = 0;
    D_800D4A98 = 0;
    sStartVsHurryBgm = sVsHurryBgmPlaying = false;
    gFillScreenAlpha = 255;
    gFillScreenAlphaStep = 0;
    gFillScreenAlphaTarget = 0;

    for (i = 0; i < 4; i++) {
        gPlayerScores[i] = 0;
        sVsDisplayedScores[i] = 0;
        D_80178810[i] = 0;
        sPlayerDownFrames[i] = 0;
    }

    // clang-format off
    for (i = 0; i < 4; i++) { sPlayerRespawnTimer[i] = 150; }
    // clang-format on

    if (gSaveFile.save.data.planet[SAVE_SLOT_VENOM_2].normalClear == 1) {
        sUnlockLandmaster = true;
    } else {
        sUnlockLandmaster = false;
    }

    if (gSaveFile.save.data.planet[SAVE_SLOT_VENOM_2].expertClear == 1) {
        sUnlockOnFoot = true;
    } else {
        sUnlockOnFoot = false;
    }

    if (gVsMatchType == VS_MATCH_TIME) {
        gVsPointsToWin = 10000;
    }
    if (!sUnlockLandmaster) {
        sUnlockOnFoot = false;
    }

    gVsCountdown[0] = gVsTimeTrialLimit + 1;
    gVsCountdown[1] = 0;
    gVsCountdown[2] = 0;
}

bool Versus_InitViewports(void) {
    bool ret = false;

    if (gNextVsViewScale >= 1.5f) {
        gNextVsViewScale = 1.5f;
        switch (gVersusStage) {
            case VS_STAGE_CORNERIA:
                gBgColor = 0x8FBD; // 136, 240, 240
                break;

            case VS_STAGE_KATINA:
                gBgColor = 0xADA7; // 168, 176, 152
                break;

            case VS_STAGE_SECTOR_Z:
                gBgColor = 0x0001; // 0, 0, 0
                break;

            default:
                gBgColor = 0x8FBD; // 136, 240, 240
                break;
        }
        ret = true;
    } else {
        gNextVsViewScale += 0.05f;
        gBgColor = 0;
    }

    return ret;
}

/* return type needs to be s32 for Versus_Update to match */
s32 Versus_ClearFrameCounter(void) {
    D_80178798 = 0;
}

bool Versus_WaitFrames(s32 frame) {
    if (frame != D_80178798) {
        D_80178798++;
    } else {
        return true;
    }
    return false;
}

void Versus_PlayAgain(void) {
    Player_InitVersus();
    gVsMatchState = VS_STATE_0;
    sVsDrawMode = 0;
}

void Versus_ReturnToMenu(void) {
    Versus_Exit();
    gGameState = GSTATE_MENU;
    gNextGameStateTimer = 2;
    gOptionMenuStatus = OPTION_WAIT;
    D_game_800D2870 = true;
    gBgColor = 0;
}

void Versus_dummy_800C1758(void) {
}

void Versus_dummy_800C175C(void) {
}

void Versus_dummy_800C1764(void) {
}

bool Versus_Update(void) {
    s32 ret = 0;

    switch (gVsMatchState) {
        case VS_STATE_0:
            Versus_InitMatch();
            gVsMatchState = VS_STATE_1;
            Versus_ClearFrameCounter();
            break;

        case VS_STATE_1:
            if (!Versus_InitViewports()) {
                break;
            }
            if (Versus_WaitFrames(30)) {
                AUDIO_PLAY_BGM(gBgmSeqId);
                gVsMatchState = VS_STATE_2;
                Versus_ClearFrameCounter();
            }
            break;

        case VS_STATE_2:
            sVsDrawMode = 1;
            if (sVsPlayerCount != Versus_SelectStartingForm()) {
                break;
            }
            if (Versus_WaitFrames(30)) {
                Player_InitVersus();
                gVsMatchState = VS_STATE_3;
                Versus_ClearFrameCounter();
            }
            break;

        case VS_STATE_3:
            sVsDrawMode = 2;
            ret = Versus_UpdateStartCountdown();

            if (ret == 0) {
                break;
            }
            if (ret == 1) {
                gVsMatchStart = true;
            }
            if (Versus_WaitFrames(30)) {
                gVsMatchState = VS_STATE_4;
            }
            break;

        case VS_STATE_4:
            if ((sStartVsHurryBgm == true) && !sVsHurryBgmPlaying) {
                AUDIO_PLAY_BGM(NA_BGM_BATTLE_LAST);
                sVsHurryBgmPlaying = true;
            }

            if (gVsMatchType == VS_MATCH_TIME) {
                sVsDrawMode = 10;
                Versus_UpdateTimer();
                Versus_dummy_800BDE3C();
            } else {
                sVsDrawMode = 8;
            }

            if (Versus_CheckForWinner()) {
                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 1);
                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 1);
                if (gVsMatchType == VS_MATCH_TIME) {
                    sVsDrawMode = 11;
                } else {
                    sVsDrawMode = 0;
                }
                gVsMatchState = VS_STATE_5;
                Versus_ClearFrameCounter();
            } else {
                Versus_UpdatePlayerStatus();
            }
            break;

        case VS_STATE_5:
            if (Versus_WaitFrames(60)) {
                switch (sVsWinner) {
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                        AUDIO_PLAY_BGM(NA_BGM_COURSE_CLEAR);
                        break;

                    case VS_TIE:
                        AUDIO_PLAY_BGM(NA_BGM_COURSE_FAILURE);
                        break;

                    default:
                        break;
                }

                gVsMatchOver = true;
                gVsMatchState = VS_STATE_6;
                func_versus_800C024C();
            }
            break;

        case VS_STATE_6:
            sVsDrawMode = 3;
            if (!func_versus_800C0294(sVsWinner)) {
                break;
            }
            if (Versus_WaitFrames(30)) {
                Versus_ClearFrameCounter();
                gVsMatchState = VS_STATE_7;
            }
            break;

        case VS_STATE_7:
            sVsDrawMode = 4;
            if (Versus_WaitFrames(15)) {
                Versus_ClearFrameCounter();
                if (((gVsMatchType == VS_MATCH_POINTS) && (sVsPlayerCount > 1)) || (gVsMatchType == VS_MATCH_TIME)) {
                    gVsMatchState = VS_STATE_8;
                } else {
                    gVsMatchState = VS_STATE_9;
                }
            }
            break;

        case VS_STATE_8:
            sVsDrawMode = 5;
            switch (gVsMatchType) {
                case VS_MATCH_POINTS:
                    if (func_versus_800C107C(sVsWinner)) {
                        gVsMatchState = VS_STATE_9;
                    }
                    break;

                case VS_MATCH_TIME:
                    if (func_versus_800C0D10()) {
                        gVsMatchState = VS_STATE_9;
                    }
                    break;

                default:
                    break;
            }

            break;

        case VS_STATE_9:
            sVsDrawMode = 6;
            if (func_versus_800C08D0()) {
                Versus_ClearFrameCounter();
                D_801787AC = 0.0f;
                D_80178830 = 0;
                gVsMatchState = VS_STATE_10;
            }
            break;

        case VS_STATE_10:
            sVsDrawMode = 7;
            if (Versus_WaitFrames(60) && Versus_UpdateMenu()) {
                switch (sVsMatchMenuOption) {
                    case 0:
                        gVsMatchState = VS_STATE_11;
                        break;

                    case 1:
                        gVsMatchState = VS_STATE_12;
                        break;

                    case 2:
                        gVsMatchState = VS_STATE_13;
                        break;

                    default:
                        gVsMatchState = VS_STATE_14;
                        break;
                }

                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 50);
                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 50);
            }
            break;

        case VS_STATE_11:
            D_80178830 += 16;
            if (D_80178830 > 480) {
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
                gFillScreenAlpha = gFillScreenAlphaTarget = 255;
                gBgColor = 0;
                Versus_PlayAgain();
            }
            break;

        case VS_STATE_12:
            D_80178830 += 16;
            if (D_80178830 > 160) {
                if (D_80178830 > 176) {
                    gCamCount = 1;
                }
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
                gBgColor = 0;
                if (D_80178830 > 224) {
                    Versus_ReturnToMenu();
                }
            }
            break;

        case VS_STATE_13:
            D_80178830 += 16;
            if (D_80178830 > 160) {
                if (D_80178830 > 176) {
                    gCamCount = 1;
                }

                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
                gBgColor = 0;

                if (D_80178830 > 224) {
                    Versus_Exit();
                    gGoToTitle = true;
                }
            }
            break;

        case VS_STATE_14:
            break;

        case VS_STATE_20:
            sVsDrawMode = 9;
            if (gInputPress->button & B_BUTTON) {
                gVsMatchState = VS_STATE_13;
            } else {
                Versus_dummy_800C175C();
            }
            break;
    }

    if ((gVsMatchState == VS_STATE_8) || (gVsMatchState == VS_STATE_9) || (gVsMatchState == VS_STATE_10)) {
        D_800D4A98++;
    }

    if (gVsMatchState >= VS_STATE_5) {
        gPauseEnabled = false;
    }

    return false;
}

s32 Versus_Main(void) {
    if (gPlayState != PLAY_PAUSE) {
        Versus_Update();
    }
    return 0;
}

void Versus_Draw(void) {
    s32 var_a1;

    sPrevDrawTime = sDrawTime;
    sDrawTime = osGetTime();

    switch (sVsDrawMode) {
        case 1:
            func_versus_800BEDDC();
            break;

        case 2:
            func_versus_800BEFE4();
            break;

        case 7:
        case 6:
            func_versus_800C0970(D_801787CC, D_801787D0);
            /* fallthrough*/
        case 5:
            switch (gVsMatchType) {
                case VS_MATCH_POINTS:
                    func_versus_800C1138(D_801787B8, sVsWinner);
                    break;

                case VS_MATCH_TIME:
                    func_versus_800C0E78();
                    break;
            }
            /* fallthrough*/
        case 4:
            if (((gVsMatchType != VS_MATCH_TIME) || ((D_800D4A98 & 0x20) == 0)) && (sVsWinner < 4)) {
                func_versus_800C075C();
            }
            /* fallthrough*/
        case 3:
            func_versus_800C04DC(D_801787C0, D_801787C8, sVsWinner);
            if (sVsDrawMode == 7) {
                func_versus_800C0B0C();
            }
            break;

        case 10:
            func_versus_800BDE44();
            /* fallthrough*/
        case 8:
            func_versus_800BF750();
            func_versus_800BF59C();
            /* fallthrough*/
        case 11:
            if (gVsMatchType == VS_MATCH_TIME) {
                Versus_DrawCountdown(124.0f, 116.0f, gVsCountdown);
            }
            break;

        case 9:
            Versus_dummy_800C1764();
            break;
    }

    var_a1 = D_80178830;
    if (var_a1 >= 121) {
        var_a1 = 121;
    }
    Wipe_Draw(WIPE_VERTICAL, var_a1);
}

void Versus_StartMatch(void) {
    switch (gOptionMenuStatus) {
        case 0:
            if (gNextGameStateTimer == 0) {
                gOptionMenuStatus = OPTION_SETUP;
                gStarCount = 0;
            }
            break;

        case 1:
            gOptionMenuStatus = OPTION_UPDATE;
            break;

        case 2:
            gDrawMode = DRAW_NONE;
            Play_Setup();

            if (gVersusStage == VS_STAGE_SECTOR_Z) {
                gSceneSetup = 1;
            }

            gCurrentLevel = LEVEL_VERSUS;
            gGameState = GSTATE_PLAY;
            gNextGameStateTimer = 2;
            gPlayState = PLAY_STANDBY;
            D_versus_80178758 = 0;
            break;
    }
    gGameFrameCount++;
}

void func_versus_800C2190(void) {
}

bool func_versus_800C2198(Actor* actor, f32 arg1, f32 arg2) {
    if ((fabsf(gBosses[0].obj.pos.x - (actor->obj.pos.x + (arg1 * 650.0f))) < 1500.0f) &&
        (fabsf(gBosses[0].obj.pos.z - (actor->obj.pos.z + (arg2 * 650.0f))) < 1500.0f) &&
        (fabsf(gBosses[0].obj.pos.y - actor->obj.pos.y) < 700.0f)) {
        return true;
    } else {
        return false;
    }
}

void func_versus_800C2244(Actor* actor) {
    bool boolTemp2;
    bool boolTemp;
    s32 pad2[6];
    f32 x;
    f32 y;
    f32 z;
    f32 x3;
    s32 pad4;
    f32 y3;
    s32 pad3[3];
    f32 sinX;
    f32 sinY;
    f32 cosX;
    f32 cosY;
    Vec3f vec;
    s32 pad;

    boolTemp = false;

    switch (actor->state) {
        case 0:
            boolTemp = true;

            if (actor->timer_0BC == 0) {
                y = RAND_FLOAT(1000.0f);
                x = RAND_FLOAT_CENTERED(10000.0f);
                z = RAND_FLOAT_CENTERED(10000.0f);

                if ((fabsf(actor->obj.pos.x - x) > 2000.0f) || (fabsf(actor->obj.pos.z - z) > 2000.0f)) {
                    actor->fwork[4] = x;
                    actor->fwork[5] = y;
                    actor->fwork[6] = z;
                    actor->timer_0BC = RAND_INT(20.0f) + 10;
                }
            }
            break;
    }

    sinX = SIN_DEG(actor->obj.rot.x);
    cosX = COS_DEG(actor->obj.rot.x);
    sinY = SIN_DEG(actor->obj.rot.y);
    cosY = COS_DEG(actor->obj.rot.y);

    if (boolTemp) {
        x = actor->fwork[4] - actor->obj.pos.x;
        y = actor->fwork[5] - actor->obj.pos.y;
        z = actor->fwork[6] - actor->obj.pos.z;

        if (((gGameFrameCount + actor->index) % 8) == 0) {
            actor->fwork[19] = Math_RadToDeg((Math_Atan2F(x, z)));
            z = sqrtf(SQ(x) + SQ(z));
            actor->fwork[20] = Math_RadToDeg((Math_Atan2F(y, z)));
        }

        x3 = actor->fwork[20];

        boolTemp2 = func_versus_800C2198(actor, sinY, cosY);

        if (boolTemp2) {
            x3 += 40.0f * boolTemp2;

            if (x3 >= 360.0f) {
                x3 -= 360.0f;
            }
            if (x3 < 0.0f) {
                x3 += 360.0f;
            }

        } else if (actor->obj.pos.y < gGroundHeight + 50.0f) {
            if (x3 > 180.0f) {
                x3 = 0.0f;
                actor->rot_0F4.x = 0.0f;
            }
        }

        Math_SmoothStepToAngle(&actor->rot_0F4.x, x3, 0.5f, 1.0f, 0.0001f);
        y3 = Math_SmoothStepToAngle(&actor->rot_0F4.y, actor->fwork[19], 0.5f, 1.0f, 0.0001f) * 30.0f;

        if (y3 < 0.0f) {
            y3 *= -1.0f;
        } else {
            y3 = 360.0f - y3;
        }

        Math_SmoothStepToAngle(&actor->obj.rot.z, y3, 0.1f, 3.0f, 0.01f);
    }

    actor->obj.rot.x = -actor->rot_0F4.x;
    actor->obj.rot.y = actor->rot_0F4.y;

    vec.z = +cosX * 38.0f;
    vec.y = -sinX * 38.0f;

    vec.x = sinY * vec.z;
    vec.z = cosY * vec.z;

    actor->vel.x = vec.x + actor->fwork[13];
    actor->vel.y = vec.y + actor->fwork[14];
    actor->vel.z = vec.z + actor->fwork[12];

    actor->fwork[13] -= actor->fwork[13] * 0.1f;
    actor->fwork[14] -= actor->fwork[14] * 0.1f;
    actor->fwork[12] -= actor->fwork[12] * 0.1f;

    if ((actor->obj.pos.y < gGroundHeight + 40.0f) && (actor->vel.y < 0.0f)) {
        actor->obj.pos.y = gGroundHeight + 40.0f;
        actor->vel.y = 0.0f;
    }

    ActorAllRange_ApplyDamage(actor);

    if (actor->iwork[8]) {
        actor->iwork[8]--;
    }
}

void func_versus_800C26C8(void) {
    s32 i;
    Vec3f src;
    Vec3f dest;
    Actor* actor;

    if ((gVsMatchType == VS_MATCH_TIME) && gVsMatchStart) {

        if (D_versus_80178758 != 0) {
            D_versus_80178758--;
        }

        if (D_versus_80178758 == 0) {
            D_versus_80178758 = 2;

            src.x = 0.0f;
            src.y = 500.0f;
            src.z = -10000.0f;

            for (i = 0, actor = &gActors[10]; i < 5; i++, actor++) {
                if (actor->obj.status == OBJ_FREE) {
                    Actor_Initialize(actor);
                    actor->obj.status = OBJ_ACTIVE;
                    actor->obj.id = 197;
                    Matrix_RotateY(gCalcMatrix, M_DTOR * RAND_FLOAT(360.0f), MTXF_NEW);
                    Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);
                    actor->obj.pos.x = dest.x;
                    actor->obj.pos.y = dest.y;
                    actor->obj.pos.z = dest.z;
                    actor->aiType = i + AI360_ENEMY;
                    actor->health = 24;
                    actor->timer_0C2 = 30;

                    Object_SetInfo(&actor->info, actor->obj.id);
                    actor->info.action = (ObjectFunc) func_versus_800C2244;
                    break;
                }
            }
        }
    }
}
