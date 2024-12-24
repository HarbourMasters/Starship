/*
 * File: fox_title.c
 * System: Title
 * Description: Starfox Title Handler
 */

#include "prevent_bss_reordering.h"
#include "prevent_bss_reordering2.h"
#include "global.h"
#include "fox_title.h"
#include "assets/ast_title.h"
#include "assets/ast_text.h"
#include "port/interpolation/FrameInterpolation.h"

f32 D_menu_801B7BB0;
f32 D_menu_801B7BB4;
f32 D_menu_801B7BB8;
f32 D_menu_801B7BBC;
f32 D_menu_801B7BC0;
f32 D_menu_801B7BC4;
f32 sTitleTextPrimCol;
f32 sTitleTextPrimColTarget;
s32 D_menu_801B7BD0;
TitleLogoStates sTitleLogoState;
s32 D_menu_801B7BD8;
f32 sStarfoxLogoAlpha;
f32 sInAlpha;
s32 D_menu_801B7BE4;
f32 D_menu_801B7BE8;
s32 D_menu_801B7BEC;
TitleCardStates sTitleCardState;
f32 D_menu_801B7BF8[10];
f32 D_menu_801B7C20[10];
f32 D_menu_801B7C48[10];
f32 D_menu_801B7C70[10];
s32 sMaxExplosions;
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
s32 gRankingTeamAlive[10][3];
s32 gTotalHitsRanking[10];
u8 sRankNameEntry[10][4];
UNK_TYPE D_menu_801B8270[3];
bool gGoToTitle;
u8 sLevelStartState;
s32 sWipeHeight;
s32 sTitleRankMaxRecords;
f32 D_menu_801B828C;
f32 D_menu_801B8290;
CameraPoint* D_menu_801B8294;
s32 D_menu_801B8298;
f32 sTitleCamUpX;
f32 sTitleCamUpY;
f32 sTitleCamUpZ;
s32 sTimer1;
s32 sTimer2;
s32 D_menu_801B82B0;
s32 sTimer3;
s32 sTitleMsgFrameCount;
s32 D_menu_801B82BC;
s32 sSceneState;
s32 sCutsceneState;
f32 sPassageWayZoffset;
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
f32 sAmbientR;
f32 sAmbientG;
f32 sAmbientB;
s32 D_menu_801B8334;
bool D_menu_801B8338;
f32 D_menu_801B833C; // Set but never unused
TitleTeam D_menu_801B8340;
bool sDrawTeamName;
bool D_menu_801B8348;
TitleTeamInfo sTitleTeam[4];
f32 D_menu_801B84D0;
f32 D_menu_801B84D4;
f32 D_menu_801B84D8[3];
TitleArwingInfo sTitleArwing[4];
TitleGreatFoxInfo sTitleGreatFox;
TitleCorneria sTitleCorneria;
s32 D_menu_801B869C;
bool sDrawTakeOffSpace;
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
Vec3f sCharFrameTable[4][50];
bool D_menu_801B9040;
f32 sTitleDeckLauncherZpos;
f32 D_menu_801B9048;
f32 D_menu_801B904C;
f32 D_menu_801B9050;
f32 sTitleStarfoxLogoXpos;
f32 sTitleStarfoxLogoYpos;
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
s32 segataSanshiroTimer = 0;

TitleAnimation sTeamAnim[4] = {
    { &aFoxRunningAnim, &aFoxAnim, aFoxSkel },
    { &aFalcoRunningAnim, &aFalcoAnim, aFalcoSkel },
    { &aPeppyRunningAnim, &aPeppyAnim, aPeppySkel },
    { &aSlippyRunningAnim, &aSlippyAnim, aSlippySkel },
};

u16* sGralPepperMsg[5] = {
    gMsg_ID_10, gMsg_ID_20, gMsg_ID_30, gMsg_ID_40, gMsg_ID_50,
};

void Title_Setup(void) {
    gVIsPerFrame = 2;
    gGameFrameCount = 0;
    gTitleState = TITLE_UPDATE_ENTRY;
    gLastGameState = GSTATE_NONE;
    D_game_800D2870 = false;

    gMainController = Title_CheckControllers();

    gFillScreenRed = 0;
    gFillScreenGreen = 0;
    gFillScreenBlue = 0;
    gFillScreenAlpha = 0;

    gFogRed = 0;
    gFogGreen = 0;
    gFogBlue = 0;

    gBgColor = 0;

    sWipeHeight = 0;
    sTimer1 = 0;
    sTimer2 = 0;

    D_menu_801B833C = 0;

    sSceneState = 0;
    sLevelStartState = 0;

    sTitleTextPrimColTarget = 255.0f;
    sTitleTextPrimCol = 255.0f;

    Memory_FreeAll();

    Play_GenerateStarfield();
    gStarfieldX = SCREEN_WIDTH;
    gStarfieldY = SCREEN_HEIGHT;

    Title_GetRankTotalHits();

    if ((gMainController == -1) || gGoToTitle) {
        AUDIO_SET_SPEC(SFXCHAN_0, AUDIOSPEC_23);
        sCutsceneState = TITLE_SCREEN;
        gGoToTitle = false;
    } else {
        AUDIO_SET_SPEC(SFXCHAN_0, AUDIOSPEC_22);
        sCutsceneState = TITLE_GREAT_FOX_TRAVELING;
    }
    gControllerLock = 30;
}

void Title_Main(void) {
    switch (gTitleState) {
        case TITLE_IDLE:
            if (gNextGameStateTimer == 0) {
                gDrawMode = DRAW_NONE;
                gTitleState = TITLE_SETUP;
            }
            break;

        case TITLE_SETUP:
            gDrawMode = DRAW_NONE;
            Title_Setup();
            break;

        case TITLE_UPDATE_ENTRY:
            gDrawMode = DRAW_TITLE;
            Title_UpdateEntry();
            break;
    }
    gGameFrameCount++;
}

void Title_UpdateEntry(void) {

    // LTODO: Verify this is correct
    gMainController = Title_CheckControllers();

    if (sTimer1 > 0) {
        sTimer1--;
    }
    if (sTimer2 > 0) {
        sTimer2--;
    }

    switch (sCutsceneState) {
        case TITLE_RANKING:
            Title_Ranking_Update();
            break;
        case TITLE_SCREEN:
            Title_Screen_Update();
            Title_Screen_Input();
            break;
        case TITLE_GREAT_FOX_TRAVELING:
            Title_CsGreatFoxTraveling_Update();
            break;
        case TITLE_CS_TEAM_RUNNING:
            Title_CsTeamRunning_Update();
            break;
        case TITLE_GREAT_FOX_CLOSE_UP:
            Title_CsGreatFoxCloseUp_Update();
            break;
        case TITLE_TAKE_OFF:
            Title_CsTakeOff_Update();
            break;
        case TITLE_TAKE_OFF_SPACE:
            Title_CsTakeOffSpace_Update();
            break;
    }
    Title_NextState_Check();
}

void Title_Draw(void) {
    switch (sCutsceneState) {
        case TITLE_RANKING:
            Title_Ranking_Draw();
            break;

        case TITLE_SCREEN:
            Title_Matrix_Push();
            Title_Screen_Draw();

            Matrix_Pop(&gGfxMatrix);

            Title_StarfoxLogo_Draw();
            Title_CopyrightSymbol_Draw();
            Title_Copyright_Draw();
            Title_PressStart_Draw();
            Title_Matrix_Push();
            Title_64Logo_Draw();

            Matrix_Pop(&gGfxMatrix);
            break;

        case TITLE_GREAT_FOX_TRAVELING:
            if (D_menu_801B8348) {
                Title_Matrix_Push();
                Title_CsGreatFoxTraveling_Draw();

                Matrix_Pop(&gGfxMatrix);

                Radio_Draw();
                Title_TitleCard_Draw();
            }
            Title_SunGlare_Draw();
            Title_Logos_Draw();
            break;

        case TITLE_CS_TEAM_RUNNING:
            Title_Matrix_Push();
            Title_CsTeamRunning_Draw();

            Matrix_Pop(&gGfxMatrix);

            if (sDrawTeamName) {
                Title_TeamName_Draw();
            }
            break;

        case TITLE_GREAT_FOX_CLOSE_UP:
            Title_Matrix_Push();

            Title_CsGreatFoxCloseUp_Draw();

            Matrix_Pop(&gGfxMatrix);
            break;

        case TITLE_TAKE_OFF:
            Title_Matrix_Push();
            Title_CsTakeOff_Draw();

            Matrix_Pop(&gGfxMatrix);

            Title_TitleCard_Draw();
            break;

        case TITLE_TAKE_OFF_SPACE:
            Title_Matrix_Push();

            Title_CsTakeOffSpace_Draw();

            Matrix_Pop(&gGfxMatrix);
            break;
    }

    if (sWipeHeight != 0) {
        gFillScreenAlpha = 0;
        gFillScreenRed = 0;
        gFillScreenGreen = 0;
        gFillScreenBlue = 0;
        Wipe_Draw(WIPE_VERTICAL, sWipeHeight);
    }
#if 0
    // @decomp Debug:
    RCP_SetupDL(&gMasterDisp, SETUPDL_83);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);
    Graphics_DisplaySmallNumber(80, 220, sSceneState);
#endif
}

s32 Title_CheckControllers(void) {
    s32 ret = -1; // No controller
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gControllerPlugged); i++) {
        if (gControllerPlugged[i] == 1) {
            ret = i;
            break;
        }
    }

    return ret;
}

void Title_Ranking_Update(void) {
    switch (sSceneState) {
        case 0:
            sTitleRankMaxRecords = 0;
            gStarCount = 800;
            D_menu_801B82BC = 450;
            sSceneState++;
            sTimer1 = 20;
            break;

        case 1:
            if (D_menu_801B82BC != 0) {
                Camera_SetStarfieldPos(gCsCamEyeX, gCsCamEyeY, gCsCamEyeZ, gCsCamAtX, gCsCamAtY, gCsCamAtZ);
                gStarfieldScrollX -= 1.0f;
                if (D_menu_801B82BC == 60) {
                    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 60);
                    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 60);
                }
            } else {
                gStarCount = 0;
                gRadioState = 0;
                sSceneState = 0;
                gDrawMode = DRAW_NONE;
                AUDIO_SET_SPEC(SFXCHAN_0, AUDIOSPEC_22);
                sCutsceneState = TITLE_GREAT_FOX_TRAVELING;
            }

            if (sTitleRankMaxRecords == 10) {
                D_menu_801B82BC--;
            }
            break;
    }

    if ((sTimer1 == 0) && ((gGameFrameCount % 8U) == 7) && (sTitleRankMaxRecords < 10)) {
        sTitleRankMaxRecords++;
    }
}

void Title_Ranking_Draw(void) {
    static char sSTARFOX_RANKING[] = "S T A R F O X     R A N K I N G";
    s32 yPos = 20;
    s32 xPos = 36;

    // LTodo: [HD-Texture] Is Broken
    u8* aTextKanjiCOMPLETE_Data = LOAD_ASSET_RAW(aTextKanjiCOMPLETE);

    // Ranking header
    RCP_SetupDL(&gMasterDisp, SETUPDL_83_POINT);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);
    Graphics_DisplaySmallText(xPos, yPos, 1.0f, 1.0f, sSTARFOX_RANKING);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
    Lib_TextureRect_IA8(&gMasterDisp, aSmallText_6, 16, 8, 148.0f, yPos, 1.0f, 1.0f);
    Lib_TextureRect_IA8(&gMasterDisp, aSmallText_4, 16, 8, 164, yPos, 1.0f, 1.0f);

    RCP_SetupDL(&gMasterDisp, SETUPDL_83);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    // This Kanji texture was used to draw a white line.
    Lib_TextureRect_IA8(&gMasterDisp, &aTextKanjiCOMPLETE_Data[288], 16, 2, 36, 32, 15.2f, 1.0f);

    RCP_SetupDL(&gMasterDisp, SETUPDL_83_POINT);

    Title_RankingData_Draw();
}

void Title_RankingData_Draw(void) {
    s32 yPos;
    s32 i;

    RCP_SetupDL(&gMasterDisp, SETUPDL_83_POINT);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);

    Graphics_DisplaySmallText(94, 38, 1.0f, 1.0f, "RANK");
    Graphics_DisplaySmallText(146, 38, 1.0f, 1.0f, "NAME");
    Graphics_DisplaySmallText(192, 38, 1.0f, 1.0f, "HITS");

    for (yPos = 55, i = 0; i < sTitleRankMaxRecords; i++) {
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
        Graphics_DisplaySmallNumber(105 - ((HUD_CountDigits(i + 1) - 1) * 8), yPos, i + 1);

        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);
        Graphics_DisplaySmallText(150, yPos, 1.0f, 1.0f, &sRankNameEntry[i][0]);

        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
        Graphics_DisplaySmallNumber(211 - ((HUD_CountDigits(gTotalHitsRanking[i]) - 1) * 8), yPos,
                                    gTotalHitsRanking[i]);
        yPos += 17;
    }
}

s32 Title_GetRankTotalHits(void) {
    s32 rankTotalHits;
    s32 hitCount;
    s32 rankingRoute;
    s32 i;
    s32 j;

    for (i = 0; i < RANKING_MAX; i++) {
        gTotalHitsRanking[i] = 0;
        for (j = 0; j < 3; j++) {
            gRankingTeamAlive[i][j] = 0;
        }
    }

    for (i = 0; i < RANKING_MAX; i++) {
        sRankNameEntry[i][0] = gSaveFile.save.data.rankNameEntry[i][0] & 0xFF;
        sRankNameEntry[i][1] = gSaveFile.save.data.rankNameEntry[i][1] & 0xFF;
        sRankNameEntry[i][2] = gSaveFile.save.data.rankNameEntry[i][2] & 0xFF;
        sRankNameEntry[i][3] = '\0';

        rankingRoute = gSaveFile.save.data.rankingRoute[i];

        for (j = 0; j < rankingRoute; j++) {
            hitCount = gSaveFile.save.data.stats[i][j].hitCount;
            hitCount |= (gSaveFile.save.data.stats[i][j].hitCountOver256 & 1) << 8;

            gTotalHitsRanking[i] += hitCount;

            gRankingTeamAlive[i][0] += gSaveFile.save.data.stats[i][j].peppyAlive & 1;
            gRankingTeamAlive[i][1] += gSaveFile.save.data.stats[i][j].slippyAlive & 1;
            gRankingTeamAlive[i][2] += gSaveFile.save.data.stats[i][j].falcoAlive & 1;
        }
    }

    rankTotalHits = gTotalHitsRanking[0];

    for (i = 1; i < RANKING_MAX; i++) {
        if (rankTotalHits < gTotalHitsRanking[i]) {
            rankTotalHits = gTotalHitsRanking[i];
        }
    }

    return rankTotalHits;
}

void Title_Screen_Setup(void) {
    bool allExpertMedals = true;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gSaveFile.save.data.planet); i++) {
        if ((i != SAVE_SLOT_VENOM_1) && ((gSaveFile.save.data.planet[i].expertMedal & 1) == 0)) {
            allExpertMedals = false;
            break;
        }
    }

    D_menu_801B82BC = 900;

    gRadioState = 0;

    D_menu_801B869C = 255;

    gStarCount = 800;

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
    sTitleStarfoxLogoXpos = 26.0f;
    sTitleStarfoxLogoYpos = 37.0f;
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

    sTitleCamUpX = 0.0f;
    sTitleCamUpY = 1.0f;
    sTitleCamUpZ = 0.0f;

    D_menu_801B84D4 = 0.5f;

    sTitleArwing[TEAM_FOX].pos.x = -80.0f;
    sTitleArwing[TEAM_FOX].pos.y = 220.0f;
    sTitleArwing[TEAM_FOX].pos.z = -360.0f;
    sTitleArwing[TEAM_FOX].scale = 4.0f;
    sTitleArwing[TEAM_FOX].xRot = 35.0f;
    sTitleArwing[TEAM_FOX].yRot = -90.0f;
    sTitleArwing[TEAM_FOX].zRot = -15.0f;
    sTitleArwing[TEAM_FOX].cockpitGlassXrot = 0.0f;
    sTitleArwing[TEAM_FOX].laserGunsYpos = 0.0f;
    sTitleArwing[TEAM_FOX].teamFaceXrot = 0.0f;
    sTitleArwing[TEAM_FOX].teamFaceYrot = 0.0f;
    sTitleArwing[TEAM_FOX].drawFace = 1;
    sTitleArwing[TEAM_FOX].unk_3C = 0;
    sTitleArwing[TEAM_FOX].unk_40 = 0;
    sTitleArwing[TEAM_FOX].drawShadow = 0;

    if (allExpertMedals) {
        sTitleTeam[TEAM_FOX].pos.x = -299.0f;
        sTitleTeam[TEAM_FOX].pos.y = -32.0f;
        sTitleTeam[TEAM_FOX].pos.z = 90.0f;
        sTitleTeam[TEAM_FOX].unk_48 = -9.660022f;
        sTitleTeam[TEAM_FOX].unk_4C = 60.330208f;
        sTitleTeam[TEAM_FOX].unk_50 = 0.00f;
    } else {
        sTitleTeam[TEAM_FOX].pos.x = 33.00f;
        sTitleTeam[TEAM_FOX].pos.y = 23.00f;
        sTitleTeam[TEAM_FOX].pos.z = 4.00f;
        sTitleTeam[TEAM_FOX].unk_48 = -7.800007f;
        sTitleTeam[TEAM_FOX].unk_4C = 0.589999f;
        sTitleTeam[TEAM_FOX].unk_50 = 0.00f;
    }

    sTitleTeam[TEAM_FOX].unk_30 = 0.0f;
    sTitleTeam[TEAM_FOX].unk_34 = 0.0f;
    sTitleTeam[TEAM_FOX].unk_28 = 0.0f;
    sTitleTeam[TEAM_FOX].unk_2C = 0.0f;
    sTitleTeam[TEAM_FOX].unk_14 = 150.0f;
    sTitleTeam[TEAM_FOX].unk_18 = 0.0f;
    sTitleTeam[TEAM_FOX].unk_1C = 1.0f;
    sTitleTeam[TEAM_FOX].unk_20 = 0.0f;
    sTitleTeam[TEAM_FOX].unk_24 = 0.0f;
    sTitleTeam[TEAM_FOX].unk_54 = false;
    sTitleTeam[TEAM_FOX].unk_38 = 0.0f;
    sTitleTeam[TEAM_FOX].unk_3C = 0.0f;
    sTitleTeam[TEAM_FOX].unk_40 = 0.0f;
    sTitleTeam[TEAM_FOX].unk_44 = 0.0f;
    sTitleTeam[TEAM_FOX].frameCount = 0;
    sTitleTeam[TEAM_FOX].unk_5C = 0;

    if (allExpertMedals) {
        sTitleTeam[TEAM_FALCO].pos.x = -42.0f;
        sTitleTeam[TEAM_FALCO].pos.y = -7.0f;
        sTitleTeam[TEAM_FALCO].pos.z = -12.0f;
        sTitleTeam[TEAM_FALCO].unk_48 = -2.009996f;
        sTitleTeam[TEAM_FALCO].unk_4C = 56.90997f;
        sTitleTeam[TEAM_FALCO].unk_50 = 0.00f;
    } else {
        sTitleTeam[TEAM_FALCO].pos.x = 147.0f;
        sTitleTeam[TEAM_FALCO].pos.y = 18.0f;
        sTitleTeam[TEAM_FALCO].pos.z = -32.0f;
        sTitleTeam[TEAM_FALCO].unk_48 = -6.009995f;
        sTitleTeam[TEAM_FALCO].unk_4C = 22.620012f;
        sTitleTeam[TEAM_FALCO].unk_50 = 0.00f;
    }

    sTitleTeam[TEAM_FALCO].unk_30 = 0.0f;
    sTitleTeam[TEAM_FALCO].unk_34 = 0.0f;
    sTitleTeam[TEAM_FALCO].unk_28 = 0.0f;
    sTitleTeam[TEAM_FALCO].unk_2C = 0.0f;
    sTitleTeam[TEAM_FALCO].unk_14 = 180.0f;
    sTitleTeam[TEAM_FALCO].unk_18 = 0.0f;
    sTitleTeam[TEAM_FALCO].unk_1C = 1.0f;
    sTitleTeam[TEAM_FALCO].unk_20 = 0.0f;
    sTitleTeam[TEAM_FALCO].unk_24 = -4.0f;
    sTitleTeam[TEAM_FALCO].unk_54 = false;
    sTitleTeam[TEAM_FALCO].unk_38 = 0.0f;
    sTitleTeam[TEAM_FALCO].unk_3C = 0.0f;
    sTitleTeam[TEAM_FALCO].unk_40 = 0.0f;
    sTitleTeam[TEAM_FALCO].unk_44 = 0.0f;
    sTitleTeam[TEAM_FALCO].frameCount = 0;
    sTitleTeam[TEAM_FALCO].unk_5C = 0;

    if (allExpertMedals) {
        sTitleTeam[TEAM_PEPPY].pos.x = 90.0f;
        sTitleTeam[TEAM_PEPPY].pos.y = 1.00f;
        sTitleTeam[TEAM_PEPPY].pos.z = -143.0f;
        sTitleTeam[TEAM_PEPPY].unk_48 = -0.500016f;
        sTitleTeam[TEAM_PEPPY].unk_4C = -33.31999f;
        sTitleTeam[TEAM_PEPPY].unk_50 = 0.00f;
    } else {
        sTitleTeam[TEAM_PEPPY].pos.x = -143.0f;
        sTitleTeam[TEAM_PEPPY].pos.y = 22.00f;
        sTitleTeam[TEAM_PEPPY].pos.z = -57.0f;
        sTitleTeam[TEAM_PEPPY].unk_48 = -5.950006f;
        sTitleTeam[TEAM_PEPPY].unk_4C = -7.689997f;
        sTitleTeam[TEAM_PEPPY].unk_50 = 0.00f;
    }

    sTitleTeam[TEAM_PEPPY].unk_30 = 0.0f;
    sTitleTeam[TEAM_PEPPY].unk_34 = 0.0f;
    sTitleTeam[TEAM_PEPPY].unk_28 = 0.0f;
    sTitleTeam[TEAM_PEPPY].unk_2C = 0.0f;
    sTitleTeam[TEAM_PEPPY].unk_14 = 130.0f;
    sTitleTeam[TEAM_PEPPY].unk_18 = 0.0f;
    sTitleTeam[TEAM_PEPPY].unk_1C = 1.0f;
    sTitleTeam[TEAM_PEPPY].unk_20 = 0.0f;
    sTitleTeam[TEAM_PEPPY].unk_24 = 0.0f;
    sTitleTeam[TEAM_PEPPY].unk_54 = false;
    sTitleTeam[TEAM_PEPPY].unk_38 = 0.0f;
    sTitleTeam[TEAM_PEPPY].unk_3C = 0.0f;
    sTitleTeam[TEAM_PEPPY].unk_40 = 0.0f;
    sTitleTeam[TEAM_PEPPY].unk_44 = 0.0f;
    sTitleTeam[TEAM_PEPPY].frameCount = 0;
    sTitleTeam[TEAM_PEPPY].unk_5C = 0;

    if (allExpertMedals) {
        sTitleTeam[TEAM_SLIPPY].pos.x = 58.0f;
        sTitleTeam[TEAM_SLIPPY].pos.y = -5.0f;
        sTitleTeam[TEAM_SLIPPY].pos.z = 22.00f;
        sTitleTeam[TEAM_SLIPPY].unk_48 = -17.899979f;
        sTitleTeam[TEAM_SLIPPY].unk_4C = -8.890011f;
        sTitleTeam[TEAM_SLIPPY].unk_50 = 0.00f;
    } else {
        sTitleTeam[TEAM_SLIPPY].pos.x = -50.0f;
        sTitleTeam[TEAM_SLIPPY].pos.y = 25.0f;
        sTitleTeam[TEAM_SLIPPY].pos.z = 15.0f;
        sTitleTeam[TEAM_SLIPPY].unk_48 = -15.870002f;
        sTitleTeam[TEAM_SLIPPY].unk_4C = -17.549995f;
        sTitleTeam[TEAM_SLIPPY].unk_50 = 0.00f;
    }

    sTitleTeam[TEAM_SLIPPY].unk_30 = 0.0f;
    sTitleTeam[TEAM_SLIPPY].unk_34 = 0.0f;
    sTitleTeam[TEAM_SLIPPY].unk_28 = 0.0f;
    sTitleTeam[TEAM_SLIPPY].unk_2C = 0.0f;
    sTitleTeam[TEAM_SLIPPY].unk_14 = 140.0f;
    sTitleTeam[TEAM_SLIPPY].unk_18 = 0.0f;
    sTitleTeam[TEAM_SLIPPY].unk_1C = 1.0f;
    sTitleTeam[TEAM_SLIPPY].unk_20 = 0.0f;
    sTitleTeam[TEAM_SLIPPY].unk_24 = 0.0f;
    sTitleTeam[TEAM_SLIPPY].unk_54 = false;
    sTitleTeam[TEAM_SLIPPY].unk_38 = 0.0f;
    sTitleTeam[TEAM_SLIPPY].unk_3C = 0.0f;
    sTitleTeam[TEAM_SLIPPY].unk_40 = 0.0f;
    sTitleTeam[TEAM_SLIPPY].unk_44 = 0.0f;
    sTitleTeam[TEAM_SLIPPY].frameCount = 254;
    sTitleTeam[TEAM_SLIPPY].unk_5C = 0;

    for (i = 0; i < ARRAY_COUNT(sTeamAnim); i++) {
        Animation_GetFrameData(sTeamAnim[i].title,
                               sTitleTeam[i].frameCount % Animation_GetFrameCount(sTeamAnim[i].title),
                               sCharFrameTable[i]);
    }

    D_menu_801B86A4 = 0;
    D_menu_801B82B0 = 100;

    AUDIO_PLAY_BGM(NA_BGM_TITLE);
}

void Title_Screen_Update(void) {
    f32 temp_fv1;
    s32 i;
    static f32 D_menu_801ADA64[4] = { 10.0f, 20.0f, 20.0f, 20.0f };
    static f32 D_menu_801ADA74[4] = { 2.0f, 5.0f, 4.0f, 4.0f };

    switch (sSceneState) {
        case 0:
            Title_Screen_Setup();
            D_menu_801B82CC = 0.04f;
            D_menu_801B82D0 = 0.1f;
            D_menu_801B8340 = 0;
            sSceneState++;
            break;

        case 1:
            Math_SmoothStepToF(&D_menu_801B86C8, -10.0f, D_menu_801B82CC, 100.0f, 0.0001f);
            Math_SmoothStepToF(&D_menu_801B86CC, 57.0f, D_menu_801B82CC, 100.0f, 0.0001f);
            Math_SmoothStepToF(&D_menu_801B8304, 13.0f, D_menu_801B82CC, 100.0f, 0.0001f);
            Math_SmoothStepToF(&D_menu_801B8308, 2.0f, D_menu_801B82CC, 100.0f, 0.0001f);
            Math_SmoothStepToF(&D_menu_801B830C, 15.0f, D_menu_801B82CC, 100.0f, 0.0001f);
            D_menu_801B82CC *= 1.04f;

            if (D_menu_801B86CC == 57.0f) {
                sSceneState++;
            }
            break;

        case 2:
            if (D_menu_801B82B0 == 0) {
                sSceneState++;
            }
            break;

        case 3:
            sTimer1 = (s32) (RAND_FLOAT(5.0f) + 1.0f) * 10;
            temp_fv1 = D_menu_801B8340;
            sTitleTeam[D_menu_801B8340].unk_5C = 0;
            sTitleTeam[D_menu_801B8340].unk_18 = 0.0f;

            if (D_menu_801B8340 == 2) {
                sTitleTeam[D_menu_801B8340].frameCount = 0;
            }

            while (temp_fv1 == D_menu_801B8340) {
                D_menu_801B8340 = RAND_INT(4.0f);
            }

            sTitleTeam[D_menu_801B8340].unk_5C = RAND_INT(6.0f) + 5;
            sTitleTeam[D_menu_801B8340].unk_54 = true;

            D_menu_801B82CC = 0.07f;
            sSceneState++;
            break;

        case 4:
            if (sTimer1 == 0) {
                sTitleTeam[D_menu_801B8340].unk_54 = false;
                Math_SmoothStepToF(&sTitleTeam[D_menu_801B8340].unk_18, 0.0f, D_menu_801B82CC, 100.0f, 0.001f);
                D_menu_801B82CC *= 1.07f;

                if (sTitleTeam[D_menu_801B8340].unk_18 == 0.0f) {
                    sSceneState = 3;
                }
            }
            break;
    }

    if (sTitleTeam[D_menu_801B8340].unk_54) {
        if ((sTitleTeam[D_menu_801B8340].unk_18 + sTitleTeam[D_menu_801B8340].unk_1C) < 0.0f) {
            sTitleTeam[D_menu_801B8340].unk_1C = D_menu_801ADA74[D_menu_801B8340];
        }

        if ((sTitleTeam[D_menu_801B8340].unk_18 + sTitleTeam[D_menu_801B8340].unk_1C) >
            D_menu_801ADA64[D_menu_801B8340]) {
            sTitleTeam[D_menu_801B8340].unk_1C = -D_menu_801ADA74[D_menu_801B8340];
        }

        sTitleTeam[D_menu_801B8340].unk_18 += sTitleTeam[D_menu_801B8340].unk_1C;
    }

    if (D_menu_801B82B0 == 0) {
        if ((gGameFrameCount & 0x80) != 0) {
            if (sTitleTeam[TEAM_FALCO].unk_20 + sTitleTeam[TEAM_FALCO].unk_24 < -20.0f) {
                sTitleTeam[TEAM_FALCO].unk_24 = 4.0f;
            }
            if (sTitleTeam[TEAM_FALCO].unk_20 + sTitleTeam[TEAM_FALCO].unk_24 > 0.0f) {
                sTitleTeam[TEAM_FALCO].unk_24 = -4.0f;
            }
            sTitleTeam[TEAM_FALCO].unk_20 += sTitleTeam[TEAM_FALCO].unk_24;
        } else {
            Math_SmoothStepToF(&sTitleTeam[TEAM_FALCO].unk_20, 0.0f, 0.3f, 100.0f, 0.1f);
        }
    }

    if ((D_menu_801B86A4 >= 3) && (D_menu_801B9040 != 0)) {
        Math_SmoothStepToF(&D_menu_801B86C8, -10.0f, D_menu_801B82D0, 100.0f, 0.0001f);
        Math_SmoothStepToF(&D_menu_801B86CC, 57.0f, D_menu_801B82D0, 100.0f, 0.0001f);
        Math_SmoothStepToF(&D_menu_801B905C, 124.0f, D_menu_801B82D0, 100.0f, 0.0001f);
        Math_SmoothStepToF(&D_menu_801B9060, 242.0f, D_menu_801B82D0, 100.0f, 0.0001f);

        for (i = 0; i < ARRAY_COUNT(sTitleTeam); i++) {
            Math_SmoothStepToF(&sTitleTeam[i].unk_28, 0.0f, D_menu_801B82D0, 100.0f, 0.01f);
            Math_SmoothStepToF(&sTitleTeam[i].unk_2C, 0.0f, D_menu_801B82D0, 100.0f, 0.01f);
            Math_SmoothStepToF(&sTitleTeam[i].unk_30, 0.0f, D_menu_801B82D0, 100.0f, 0.01f);
            Math_SmoothStepToF(&sTitleTeam[i].unk_34, 0.0f, D_menu_801B82D0, 100.0f, 0.01f);
            Math_SmoothStepToF(&sTitleTeam[i].unk_38, 0.0f, D_menu_801B82D0, 100.0f, 0.01f);
            Math_SmoothStepToF(&sTitleTeam[i].unk_3C, 0.0f, D_menu_801B82D0, 100.0f, 0.01f);
            Math_SmoothStepToF(&sTitleTeam[i].unk_40, 0.0f, D_menu_801B82D0, 100.0f, 0.01f);
            Math_SmoothStepToF(&sTitleTeam[i].unk_44, 0.0f, D_menu_801B82D0, 100.0f, 0.01f);
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

    sTitleArwing->xRot += 0.6f;

    Title_SetCamUp3(1, &gCsCamEyeX, &gCsCamEyeY, &gCsCamEyeZ, &gCsCamAtX, &gCsCamAtY, &gCsCamAtZ, D_menu_801B86A8,
                    D_menu_801B86AC, D_menu_801B86B0);
    Camera_SetStarfieldPos(gCsCamEyeX, gCsCamEyeY, gCsCamEyeZ, gCsCamAtX, gCsCamAtY, gCsCamAtZ);

    gStarfieldScrollX -= 0.5f;

    if (D_menu_801B82B0 > 0) {
        D_menu_801B82B0--;
    }

    if (D_menu_801B9040 == 1) {
        D_menu_801B82BC = 450;
    }

    if (D_menu_801B82BC != 0) {
        D_menu_801B82BC--;
        return;
    }

    gStarCount = 0;

    sSceneState = 0;

    gDrawMode = DRAW_NONE;

    sCutsceneState = TITLE_RANKING;
}

void Title_Screen_Draw(void) {
    s32 i;
    static TitleTeam D_menu_801ADA84[4] = { TEAM_FOX, TEAM_FALCO, TEAM_SLIPPY, TEAM_PEPPY };

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

    Title_SetLightRot(D_menu_801B86C8, D_menu_801B86CC, 100.0f, &D_menu_801B82E0, &D_menu_801B82E4, &D_menu_801B82E8);

    for (i = 0; i < ARRAY_COUNT(D_menu_801ADA84); i++) {
        Title_Team_Draw(D_menu_801ADA84[i]);
        sTitleTeam[D_menu_801ADA84[i]].frameCount += sTitleTeam[D_menu_801ADA84[i]].unk_5C;
    }

    gLight1R = D_menu_801B8310;
    gLight1G = D_menu_801B8314;
    gLight1B = D_menu_801B8318;

    gAmbientR = D_menu_801B831C;
    gAmbientG = D_menu_801B8320;
    gAmbientB = D_menu_801B8324;

    Title_SetLightRot(D_menu_801B86D0, D_menu_801B86D4, 100.0f, &D_menu_801B82E0, &D_menu_801B82E4, &D_menu_801B82E8);

    Title_Arwing_Draw(0);
}

void Title_CsGreatFox_Setup(void) {
    s32 i;

    gStarCount = 800;
    sMaxExplosions = 10;

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
    sStarfoxLogoAlpha = 0.0f;
    sInAlpha = 0.0f;
    sTitleLogoState = TITLE_LOGO_STARFOX_IN;
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

    sTitleCorneria.pos.y = 0.0f;
    sTitleCorneria.draw = false;
    sTitleCorneria.pos.x = -80.0f;
    sTitleCorneria.pos.z = 500.0f;
    sTitleCorneria.scale = 5.0f;

    D_menu_801B8348 = false;

    sTitleGreatFox.pos.x = 20.0f;
    sTitleGreatFox.pos.y = 0.0f;
    sTitleGreatFox.pos.z = 30.0f;
    sTitleGreatFox.xRot = 0.0f;
    sTitleGreatFox.yRot = 0.0f;
    sTitleGreatFox.zRot = 0.0f;
    sTitleGreatFox.scale = 0.1f;

    D_menu_801B86BC = 0.0f;
    D_menu_801B86C0 = 0.0f;
    D_menu_801B86C4 = 0.0f;
    D_menu_801B86A8 = -10.0f;
    D_menu_801B86AC = 0.0f;

    D_menu_801B86B4 = 1500.0f;
    D_menu_801B86B8 = -100.0f;
    sTitleCamUpX = 0.0f;
    sTitleCamUpY = 1.0f;
    sTitleCamUpZ = 0.0f;

    Title_SetCamUp2(D_menu_801B86BC, D_menu_801B86C0, D_menu_801B86C4, &gCsCamEyeX, &gCsCamEyeY, &gCsCamEyeZ,
                    D_menu_801B86B4, &gCsCamAtX, &gCsCamAtY, &gCsCamAtZ, D_menu_801B86B8, D_menu_801B86A8,
                    D_menu_801B86AC);

    sTitleCardState = TITLE_CARD_NONE;

    AUDIO_PLAY_BGM(NA_BGM_OPENING);
}

void Title_CsGreatFoxTraveling_Update(void) {
    f32 temp;
    f32 temp2;

    switch (sSceneState) {
        case 0:
            Title_CsGreatFox_Setup();
            D_menu_801B8294 = D_menu_801B6B40;
            D_menu_801B7BE8 = 1.0f;
            D_menu_801B82CC = 0.002f;
            sSceneState = 100;
            sTitleMsgFrameCount = 0;

            gRadioState = 0;
            gHideRadio = false;
            gRadioMsgPri = 0;
            break;

        case 100:
            if (gFillScreenAlpha != 0) {
                gFillScreenAlpha -= 5;
            } else {
                sTimer1 = 19;
                sSceneState = 1;
            }
            break;

        case 1:
            if (sTimer1 == 0) {
                temp2 = Math_SmoothStepToF(&sStarfoxLogoAlpha, 255.0f, D_menu_801B82CC, 100.0f, 1.0f);
                D_menu_801B82CC *= 1.08f;
                if (temp2 == 0.0f) {
                    sTimer1 = 50;
                    sTimer2 = 85;
                    D_menu_801B82D0 = 0.01f;
                    D_menu_801B82CC = 0.002f;
                    sSceneState++;
                }
            }
            break;

        case 2:
            if (sTimer1 == 0) {
                Math_SmoothStepToF(&sStarfoxLogoAlpha, 0.0f, D_menu_801B82D0, 100.0f, 0.1f);
                D_menu_801B82D0 *= 1.06f;
                if (sTimer2 == 0) {
                    temp2 = Math_SmoothStepToF(&sInAlpha, 255.0f, D_menu_801B82CC, 100.0f, 1.0f);
                    D_menu_801B82CC *= 1.08f;
                    if (temp2 == 0.0f) {
                        sTimer1 = 30;
                        D_menu_801B82D0 = 0.02f;
                        sSceneState++;
                        D_menu_801B7BD8 = 1;
                        gFillScreenAlpha = 0;
                    }
                }
            }
            break;

        case 3:
            if (sTimer1 == 0) {
                Math_SmoothStepToF(&sInAlpha, 0.0f, D_menu_801B82D0, 100.0f, 0.1f);
                D_menu_801B82D0 *= 1.07f;
                if (D_menu_801B7BB8 < 1200.0f) {
                    D_menu_801B7BB8 += 10.0f;
                    if (D_menu_801B7BB8 > 50.0f) {
                        sTitleLogoState = TITLE_LOGO_NINTENDO_64;
                        sStarfoxLogoAlpha += 1.8f;
                    }
                } else {
                    D_menu_801B7BD8 = 0;
                    sSceneState++;
                }
            }
            break;

        case 4:
            if (sStarfoxLogoAlpha < 255.0f) {
                sStarfoxLogoAlpha += 1.0f;
            } else {
                sStarfoxLogoAlpha = 255.0f;
                sTimer1 = 70;
                sTimer3 = 0;
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

                sSceneState = 10;
            }
            break;

        case 10:
            if (sTimer3 == 45) {
                sTitleCardState = TITLE_CARD_GREAT_FOX;
            }

            if (sTimer3 == 145) {
                sTitleCardState = TITLE_CARD_NONE;
            }

            if (sTitleMsgFrameCount == 638) {
                AUDIO_PLAY_SFX(NA_SE_GREATFOX_ENGINE, sTitleGreatFox.sfxSource, 0);
                AUDIO_PLAY_SFX(NA_SE_GREATFOX_BURNER, sTitleGreatFox.sfxSource, 0);
                Radio_PlayMessage(gMsg_ID_60, RCID_ROB64_TITLE);
            }

            if (sTitleMsgFrameCount == 838) {
                Title_Radio_PlayMessage(sGralPepperMsg, RCID_GEN_PEPPER_TITLE);
            }

            if (sTimer1 == 1) {
                D_menu_801B8348 = true;
            }

            if (sTimer1 != 0) {
                break;
            }

            if (D_menu_801B9078 < 1.39f) {
                D_menu_801B9078 += 0.01f;
                D_menu_801B907C += 0.01f;
                D_menu_801B9070 -= 0.5f;
                D_menu_801B9074 -= 0.5f;
            }

            temp = Math_SmoothStepToF(&sStarfoxLogoAlpha, 0.0f, D_menu_801B82DC, 100.0f, 0.1f);

            D_menu_801B82DC *= 1.06f;

            if (temp == 0.0f) {
                sTitleLogoState = TITLE_LOGO_NONE;
            }

            Title_Cutscene_SetCamera(D_menu_801B8294, 12, D_menu_801B8290);

            Title_GetCamRot(&D_menu_801B86A8, &D_menu_801B86AC);
            Title_SetCamUp(D_menu_801B86A8, D_menu_801B86AC);

            if ((sTitleMsgFrameCount > 960) && (D_menu_801B7BE8 > 0.0f)) {
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

                if (sTimer3 > 550) {
                    D_menu_801B82D8 += 0.0001f;
                } else {
                    D_menu_801B82D8 += 0.000001f;
                }
            }

            if (sTimer3 == 260) {
                sTitleCorneria.draw = true;
            }

            if (sTimer3 == 750) {
                gFillScreenAlpha = 0;
                gFillScreenRed = 0;
                gFillScreenGreen = 0;
                gFillScreenBlue = 0;
                D_menu_801B869C = 1;
            }

            if (gFillScreenAlpha == 255) {
                Audio_KillSfxBySourceAndId(sTitleGreatFox.sfxSource, NA_SE_GREATFOX_ENGINE);
                Audio_KillSfxBySourceAndId(sTitleGreatFox.sfxSource, NA_SE_GREATFOX_BURNER);

                sSceneState = 0;

                gDrawMode = DRAW_NONE;

                sCutsceneState = TITLE_CS_TEAM_RUNNING;
            }
            sTimer3++;
            break;
    }

    Title_ScreenFade_Update();
    Title_SetLightRot(D_menu_801B86C8, D_menu_801B86CC, 100.0f, &D_menu_801B82E0, &D_menu_801B82E4, &D_menu_801B82E8);

    if (D_menu_801B7BE8 != 0) {
        Camera_SetStarfieldPos(gCsCamEyeX, gCsCamEyeY, gCsCamEyeZ, gCsCamAtX, gCsCamAtY, gCsCamAtZ);
    }

    gStarfieldScrollX -= D_menu_801B7BE8;
    sTitleMsgFrameCount++;
}

void Title_CsGreatFoxTraveling_Draw(void) {
    if (sTitleCorneria.draw) {
        Title_Corneria_Draw(-700.0f);
    }
    Title_GreatFox_Draw();
}

void Title_CsTeamRunning_Setup(void) {
    gStarCount = 0;

    D_menu_801B869C = 255;

    gFillScreenAlpha = 255;
    gFillScreenRed = 0;
    gFillScreenGreen = 0;
    gFillScreenBlue = 0;

    sDrawTeamName = false;
    D_menu_801B8334 = 0;
    D_menu_801B8338 = 1;

    sAmbientR = sAmbientG = sAmbientB = 155.0f;
    sAmbientR = 77.0f;
    sAmbientG = 77.0f;
    sAmbientB = 77.0f;

    D_menu_801B86C8 = 0.0f;
    D_menu_801B86CC = -90.0f;
    D_menu_801B82F8 = 76;
    D_menu_801B82FC = 45;
    D_menu_801B8300 = 66;
    D_menu_801B8304 = 11.0f;
    D_menu_801B8308 = 1.0f;
    D_menu_801B830C = 1.0f;
    D_menu_801B84D4 = 0.5f;

    sTitleTeam[TEAM_FOX].pos.x = -20.0f;
    sTitleTeam[TEAM_FOX].pos.y = 0.0f;
    sTitleTeam[TEAM_FOX].pos.z = -600.0f;
    sTitleTeam[TEAM_FOX].unk_0C = 0.0f;
    sTitleTeam[TEAM_FOX].shadowScale = 3.0f;
    sTitleTeam[TEAM_FOX].frameCount = 14;
    sTitleTeam[TEAM_FOX].unk_5C = 5;

    sTitleTeam[TEAM_FALCO].pos.x = -209.0f;
    sTitleTeam[TEAM_FALCO].pos.y = 0.0f;
    sTitleTeam[TEAM_FALCO].pos.z = -820.0f;
    sTitleTeam[TEAM_FALCO].unk_0C = 0.0f;
    sTitleTeam[TEAM_FALCO].shadowScale = 3.0f;
    sTitleTeam[TEAM_FALCO].frameCount = 0;
    sTitleTeam[TEAM_FALCO].unk_5C = 5;

    sTitleTeam[TEAM_PEPPY].pos.x = 62.0f;
    sTitleTeam[TEAM_PEPPY].pos.y = 0.0f;
    sTitleTeam[TEAM_PEPPY].pos.z = -813.0f;
    sTitleTeam[TEAM_PEPPY].unk_0C = 0.0f;
    sTitleTeam[TEAM_PEPPY].shadowScale = 3.0f;
    sTitleTeam[TEAM_PEPPY].frameCount = 29;
    sTitleTeam[TEAM_PEPPY].unk_5C = 6;

    sTitleTeam[TEAM_SLIPPY].pos.x = 183.0f;
    sTitleTeam[TEAM_SLIPPY].pos.y = 0.0f;
    sTitleTeam[TEAM_SLIPPY].pos.z = -990.0f;
    sTitleTeam[TEAM_SLIPPY].unk_0C = 0.0f;
    sTitleTeam[TEAM_SLIPPY].shadowScale = 3.0f;
    sTitleTeam[TEAM_SLIPPY].frameCount = 41;
    sTitleTeam[TEAM_SLIPPY].unk_5C = 7;

    D_menu_801B84D0 = -6000.0f;
    D_menu_801B86BC = 22.0f;
    D_menu_801B86C0 = 116.0f;
    D_menu_801B86C4 = -543.0f;
    D_menu_801B86A8 = 3.0f;
    D_menu_801B86AC = 7.0f;
    D_menu_801B86B4 = 400.0f;
    D_menu_801B86B8 = -100.0f;
    sTitleCamUpX = 0.0f;
    sTitleCamUpY = 1.0f;
    sTitleCamUpZ = 0.0f;

    Title_SetCamUp2(D_menu_801B86BC, D_menu_801B86C0, D_menu_801B86C4, &gCsCamEyeX, &gCsCamEyeY, &gCsCamEyeZ,
                    D_menu_801B86B4, &gCsCamAtX, &gCsCamAtY, &gCsCamAtZ, D_menu_801B86B8, D_menu_801B86A8,
                    D_menu_801B86AC);
}

CameraPoint D_menu_801ADA94[50] = {
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

void Title_CsTeamRunning_Update(void) {
    static s32 D_menu_801ADF44[] = { 63, 170, 268, 368, 368 };

    switch (sSceneState) {
        case 0:
            Title_CsTeamRunning_Setup();
            AUDIO_PLAY_SFX(NA_SE_DEMO_SIREN, gDefaultSfxSource, 4);
            AUDIO_PLAY_SFX(NA_SE_DEMO_RUNNING, D_menu_801B84D8, 0);

            sTimer3 = 0;
            sPassageWayZoffset = 0.0f;
            D_menu_801B7BEC = 0;
            sSceneState++;
            break;

        case 1:
            if (sTimer3 == 20) {
                D_menu_801B869C = 0;
            }

            if (D_menu_801B84D0 != 0.0f) {
                Math_SmoothStepToF(&D_menu_801B84D0, 0.0f, 0.09f, 70.0f, 1.0f);
            }

            if (D_menu_801B84D0 == 0.0f) {
                sTimer3 = 0;
                D_menu_801B8340 = 0;
                D_menu_801B8294 = D_menu_801ADA94;
                D_menu_801B8298 = 0;
                D_menu_801B828C = 0.0f;
                D_menu_801B8290 = 0.06f;
                sSceneState++;
            }
            sTimer3++;
            break;

        case 2:
            Title_GetCamRot(&D_menu_801B86A8, &D_menu_801B86AC);
            Title_SetCamUp(D_menu_801B86A8, D_menu_801B86AC);
            Title_Cutscene_SetCamera(D_menu_801B8294, 34, D_menu_801B8290);

            if (sTimer3 == D_menu_801ADF44[D_menu_801B8340]) {
                sDrawTeamName = true;
                sTimer1 = 40;
                sSceneState = 3;
            }

            if (sTimer3 == 475) {
                D_menu_801B869C = 1;
            }

            if (D_menu_801B7BEC == 795) {
                Audio_KillSfxById(NA_SE_DEMO_SIREN);
                Audio_KillSfxBySourceAndId(D_menu_801B84D8, NA_SE_DEMO_RUNNING);

                sSceneState = 0;

                gDrawMode = DRAW_NONE;

                sCutsceneState = TITLE_GREAT_FOX_CLOSE_UP;
            }
            sTimer3++;
            break;

        case 3:
            if (sTimer1 == 0) {
                sDrawTeamName = false;
                sSceneState = 2;
                D_menu_801B8340++;
            }
            break;
    }

    Title_ScreenFade_Update();
    Title_SetLightRot(D_menu_801B86C8, D_menu_801B86CC, 100.0f, &D_menu_801B82E0, &D_menu_801B82E4, &D_menu_801B82E8);

    D_menu_801B7BEC++;
}

void Title_CsTeamRunning_Draw(void) {
    s32 i;
    static AmbientRGB sAmbientRGB[4] = {
        { 255.0f, 155.0f, 155.0f },
        { 155.0f, 255.0f, 155.0f },
        { 135.0f, 206.0f, 255.0f },
        { 255.0f, 255.0f, 155.0f },
    };

    if ((gGameFrameCount % 8U) == 7) {
        if (D_menu_801B8338 != 0) {
            D_menu_801B8334 = (D_menu_801B8334 + 1) % 4U;
            sAmbientR = sAmbientRGB[D_menu_801B8334].r;
            sAmbientG = sAmbientRGB[D_menu_801B8334].g;
            sAmbientB = sAmbientRGB[D_menu_801B8334].b;
        } else {
            sAmbientR = 155.0f;
            sAmbientG = 155.0f;
            sAmbientB = 155.0f;
        }
        D_menu_801B8338 ^= 1;
    }

    if ((gGameFrameCount % 2) != 0) {
        D_menu_801B86CC += 30.0f;
        if (D_menu_801B86CC > 90.0f) {
            D_menu_801B86CC = -90.0f;
        }
    }

    gAmbientR = sAmbientR;
    gAmbientG = sAmbientG;
    gAmbientB = sAmbientB;

    Title_Passage_Draw();

    gLight1R = D_menu_801B82F8;
    gLight1G = D_menu_801B82FC;
    gLight1B = D_menu_801B8300;
    gAmbientR = D_menu_801B8304;
    gAmbientG = D_menu_801B8308;
    gAmbientB = D_menu_801B830C;

    for (i = 0; i < ARRAY_COUNT(sTitleTeam); i++) {
        Title_TeamRunning_Draw(i);
        sTitleTeam[i].frameCount += sTitleTeam[i].unk_5C;
    }
}

void Title_CsGreatFoxCloseUp_Setup(void) {
    gStarCount = 800;

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

    sTitleCamUpX = 0.0f;
    sTitleCamUpY = 1.0f;
    sTitleCamUpZ = 0.0f;

    sTitleGreatFox.pos.x = 0.0f;
    sTitleGreatFox.pos.y = 0.0f;
    sTitleGreatFox.pos.z = 0.0f;
    sTitleGreatFox.xRot = 0.0f;
    sTitleGreatFox.yRot = 0.0f;
    sTitleGreatFox.zRot = 0.0f;
}

void Title_CsGreatFoxCloseUp_Update(void) {
    switch (sSceneState) {
        case 0:
            Title_CsGreatFoxCloseUp_Setup();
            AUDIO_PLAY_SFX(NA_SE_GREATFOX_ENGINE, sTitleGreatFox.sfxSource, 0);
            AUDIO_PLAY_SFX(NA_SE_GREATFOX_BURNER, sTitleGreatFox.sfxSource, 0);

            D_menu_801B82CC = 0.01f;
            sTimer3 = 0;
            sSceneState++;
            break;

        case 1:
            Math_SmoothStepToF(&D_menu_801B86A8, 30.0f, D_menu_801B82CC, 100.0f, 0.0001f);
            Math_SmoothStepToF(&D_menu_801B86AC, -15.0f, D_menu_801B82CC, 100.0f, 0.0001f);
            Math_SmoothStepToF(&gCsCamAtX, 0.0f, 0.05f, 100.0f, 0.0001f);
            Math_SmoothStepToF(&gCsCamAtY, -40.0f, D_menu_801B82CC, 100.0f, 0.0001f);
            Math_SmoothStepToF(&D_menu_801B86B0, 100.0f, D_menu_801B82CC, 100.0f, 0.0001f);

            D_menu_801B82CC *= 1.04f;
            if (sTimer3 == 50) {
                D_menu_801B869C = 1;
            }

            if (gFillScreenAlpha == 255) {
                Audio_KillSfxBySourceAndId(sTitleGreatFox.sfxSource, NA_SE_GREATFOX_ENGINE);
                Audio_KillSfxBySourceAndId(sTitleGreatFox.sfxSource, NA_SE_GREATFOX_BURNER);

                gDrawMode = DRAW_NONE;

                sSceneState = 0;
                sCutsceneState = TITLE_TAKE_OFF;
            }
            Title_ScreenFade_Update();
            sTimer3++;
            break;
    }

    Title_SetCamUp3(1, &gCsCamEyeX, &gCsCamEyeY, &gCsCamEyeZ, &gCsCamAtX, &gCsCamAtY, &gCsCamAtZ, D_menu_801B86A8,
                    D_menu_801B86AC, D_menu_801B86B0);
    Title_SetLightRot(D_menu_801B86C8, D_menu_801B86CC, 100.0f, &D_menu_801B82E0, &D_menu_801B82E4, &D_menu_801B82E8);
    Camera_SetStarfieldPos(gCsCamEyeX, gCsCamEyeY, gCsCamEyeZ, gCsCamAtX, gCsCamAtY, gCsCamAtZ);

    gStarfieldScrollX += 2.0f;
    gStarfieldScrollY += 2.0f;
}

void Title_CsGreatFoxCloseUp_Draw(void) {
    Title_GreatFox_Draw();
}

void Title_CsTakeOff_Setup(void) {
    f32 var_fv0;
    s32 i;

    sMaxExplosions = 10;

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
    gStarCount = 0;

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

    sTitleCorneria.pos.x = 0.0f;
    sTitleCorneria.pos.y = 0.0f;
    sTitleCorneria.pos.z = 1000.0f;
    sTitleCorneria.scale = 2.0f;
    sTitleCorneria.draw = false;

    D_menu_801B7BE4 = 1;

    var_fv0 = -120.0f;

    for (i = 0; i < ARRAY_COUNT(sTitleArwing); i++, var_fv0 += 75.0f) {
        sTitleArwing[i].pos.x = var_fv0;
        sTitleArwing[i].pos.y = 0.0f;
        sTitleArwing[i].pos.z = 0.0f;
        sTitleArwing[i].scale = 0.5f;
        sTitleArwing[i].xRot = 0.0f;
        sTitleArwing[i].yRot = 0.0f;
        sTitleArwing[i].zRot = 0.0f;
        sTitleArwing[i].cockpitGlassXrot = -60.0f;
        sTitleArwing[i].laserGunsYpos = -10.0f;
        sTitleArwing[i].teamFaceXrot = 0.0f;
        sTitleArwing[i].teamFaceYrot = 0.0f;
        sTitleArwing[i].drawFace = 4 - i;

        sTitleArwing[i].unk_3C = 0;
        sTitleArwing[i].unk_40 = 0;
        sTitleArwing[i].unk_44 = 0.0f;
        sTitleArwing[i].vel = 0.05f;

        sTitleArwing[i].drawShadow = true;
        sTitleArwing[i].draw = true;
    }

    D_menu_801B86BC = 140.0f;
    D_menu_801B86C0 = -20.0f;
    D_menu_801B86C4 = 0.0f;
    D_menu_801B86A8 = 0.0f;
    D_menu_801B86AC = 90.0f;
    D_menu_801B86B4 = 90.0f;
    D_menu_801B86B8 = -50.0f;
    sTitleCamUpX = 0.0f;
    sTitleCamUpY = 1.0f;
    sTitleCamUpZ = 0.0f;

    Title_SetCamUp2(D_menu_801B86BC, D_menu_801B86C0, D_menu_801B86C4, &gCsCamEyeX, &gCsCamEyeY, &gCsCamEyeZ,
                    D_menu_801B86B4, &gCsCamAtX, &gCsCamAtY, &gCsCamAtZ, D_menu_801B86B8, D_menu_801B86A8,
                    D_menu_801B86AC);

    sTitleDeckLauncherZpos = 25.0f;
    D_menu_801B9048 = 84.0f;
    D_menu_801B904C = -20.0f;
    D_menu_801B9050 = -33.0f;
}

void Title_CsTakeOff_Update(void) {
    s32 i;
    f32 temp[4];

    switch (sSceneState) {
        case 0:
            D_menu_801B7BEC = 0;

            segataSanshiroTimer = 0;
            Title_CsTakeOff_Setup();
            Audio_SetEnvSfxReverb(104);

            sTimer1 = 30;

            sTitleArwing[TEAM_SLIPPY].timer = 70;
            sTitleArwing[TEAM_PEPPY].timer = 102;
            sTitleArwing[TEAM_FALCO].timer = 132;
            sTitleArwing[TEAM_FOX].timer = 171;

            D_menu_801B8294 = D_menu_801B6C60;
            D_menu_801B8298 = 0;
            D_menu_801B828C = 0.0f;
            D_menu_801B8290 = 0.024f;
            sSceneState = 10;
            break;

        case 10:
            if (sTimer1 == 0) {
                AUDIO_PLAY_SFX(NA_SE_LIFT_UP, gDefaultSfxSource, 4);
                sTimer3 = 0;
                sSceneState = 1;
            }
            break;

        case 1:
            Title_GetCamRot(&D_menu_801B86A8, &D_menu_801B86AC);
            Title_SetCamUp(D_menu_801B86A8, D_menu_801B86AC);
            Title_Cutscene_SetCamera(D_menu_801B8294, 10, D_menu_801B8290);

            if (D_menu_801B9048 > 0.0f) {
                D_menu_801B9048 -= 0.41f;
                if (D_menu_801B9048 < 0.0f) {
                    D_menu_801B9048 = 0.0f;
                    AUDIO_PLAY_SFX(NA_SE_LIFT_UP_END, gDefaultSfxSource, 4);
                }
            }

            if (sTimer3 == 60) {
                sTitleCardState = 2; // TITLE_CARD_ARWING
            }

            for (i = ARRAY_COUNT(sTitleArwing) - 1; i >= 0; i--) {
                if (sTitleArwing[i].timer > 0) {
                    sTitleArwing[i].timer--;
                }

                if (sTitleArwing[i].timer == 1) {
                    AUDIO_PLAY_SFX(NA_SE_ARWING_HATCH, sTitleArwing[i].sfxSource, 0);
                };

                if (sTitleArwing[i].timer == 0) {
                    Math_SmoothStepToF(&sTitleArwing[i].laserGunsYpos, 0.0f, sTitleArwing[i].vel, 100.0f, 0.01f);
                    temp[i] = Math_SmoothStepToF(&(sTitleArwing[i].cockpitGlassXrot), 0.0f, sTitleArwing[i].vel, 100.0f,
                                                 0.01f);
                    sTitleArwing[i].vel *= 1.04f;
                    if (temp[i] == 0.0f) {
                        Audio_KillSfxBySourceAndId(sTitleArwing[i].sfxSource, NA_SE_ARWING_HATCH);
                    }
                }
            }

            if (sTimer3 == 226) {
                D_menu_801B7BE4 = 0;
                sTitleArwing[TEAM_FOX].draw = false;
            }

            if (sTimer3 == 226) {
                sTitleArwing[TEAM_FALCO].draw = false;

                for (i = 0; i < 4; i++) {
                    sTitleArwing[i].drawShadow = false;
                }
            }

            if (sTimer3 == 226) {
                sTitleArwing[TEAM_FOX].draw = true;
                sTitleArwing[TEAM_FALCO].draw = true;
            }

            if (sTimer3 == 226) {
                sTitleCardState = 0; // TITLE_CARD_NONE

                AUDIO_PLAY_SFX(NA_SE_ENGINE_START, sTitleArwing[TEAM_SLIPPY].sfxSource, 0);

                D_menu_801B86BC = 105.0f;
                D_menu_801B86C0 = 0.0f;
                D_menu_801B86C4 = -12.0f;
                D_menu_801B86A8 = 9.4f;
                D_menu_801B86AC = 110.0f;
                D_menu_801B86B4 = 36.0f;
                D_menu_801B86B8 = -70.0f;

                Title_SetCamUp2(D_menu_801B86BC, D_menu_801B86C0, D_menu_801B86C4, &gCsCamEyeX, &gCsCamEyeY,
                                &gCsCamEyeZ, D_menu_801B86B4, &gCsCamAtX, &gCsCamAtY, &gCsCamAtZ, D_menu_801B86B8,
                                D_menu_801B86A8, D_menu_801B86AC);

                sTimer3 = 0;

                sTitleArwing[TEAM_SLIPPY].unk_44 = 0.0f;

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

                sSceneState++;
            }
            sTimer3++;
            break;

        case 2:
            gStarCount = 800;
            if (sTimer3 == 30) {
                sTitleArwing[TEAM_SLIPPY].unk_40 = 1;
            }

            if (sTimer3 == 40) {
                sTitleArwing[TEAM_SLIPPY].unk_3C = 1;
            }

            if (sTimer3 > 40) {
                sTitleArwing[TEAM_SLIPPY].unk_44 += 0.002f;

                if (sTitleArwing[TEAM_SLIPPY].unk_44 > 0.2f) {
                    sTitleArwing[TEAM_SLIPPY].unk_44 = 0.2f;
                }

                Math_SmoothStepToF(&D_menu_801B82EC, 240.0f, 0.06f, 2.0f, 0.01f);
                Math_SmoothStepToF(&D_menu_801B82F0, 240.0f, 0.06f, 2.0f, 0.01f);
                Math_SmoothStepToF(&D_menu_801B82F4, 255.0f, 0.06f, 2.0f, 0.01f);

                gLight1R = D_menu_801B82EC;
                gLight1G = D_menu_801B82F0;
                gLight1B = D_menu_801B82F4;
            }

            if ((sTimer3 > 60) && (gFillScreenAlpha < 255)) {
                gFillScreenAlpha++;
            }

            if (gFillScreenAlpha == 128) {
                sTimer1 = 7;
                sTitleArwing[TEAM_SLIPPY].unk_3C = 0;
                sTitleArwing[TEAM_SLIPPY].unk_40 = 0;
                gFillScreenAlpha = 255;
                sSceneState++;
            }

            if (sTimer3 == 50 * 4) {
                sTitleArwing[TEAM_FOX].draw = false;
            }

            if (sTimer3 == 60 * 4) {
                sTitleArwing[TEAM_FALCO].draw = false;
            }

            Math_SmoothStepToF(&D_menu_801B86B4, 16.0f, 0.01f, 100.0f, 0.01f);
            Math_SmoothStepToF(&D_menu_801B86AC, 138.0f, 0.01f, 100.0f, 0.01f);

            Title_SetCamUp2(D_menu_801B86BC + 9, D_menu_801B86C0, D_menu_801B86C4, &gCsCamEyeX, &gCsCamEyeY,
                            &gCsCamEyeZ, D_menu_801B86B4, &gCsCamAtX, &gCsCamAtY, &gCsCamAtZ, D_menu_801B86B8,
                            D_menu_801B86A8, D_menu_801B86AC);
            sTimer3++;
            gStarCount = 800;
            break;

        case 3:
            if (sTimer1 == 0) {
                Audio_KillSfxBySourceAndId(sTitleArwing[TEAM_SLIPPY].sfxSource, NA_SE_ENGINE_START);
                AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, sTitleArwing[TEAM_SLIPPY].sfxSource, 0);

                sTimer1 = 4;

                gFillScreenAlpha = 0;

                for (i = 0; i < 4; i++) {
                    sTitleArwing[i].unk_3C = 1;
                    sTitleArwing[i].unk_44 = 0.9f;
                }

                sTimer3 = 0;

                gStarCount = 800;

                sSceneState++;
            }
            break;

        case 4:
            if (sTimer1 == 0) {
                sTitleArwing[TEAM_SLIPPY].unk_44 = 1.2f;

                Math_SmoothStepToF(&sTitleArwing[TEAM_SLIPPY].pos.z, 900.0f, 0.06f, 100.0f, 0.0001f);
                Math_SmoothStepToF(&D_menu_801B86AC, 154.0f, 0.2f, 100.0f, 0.01f);
                Math_SmoothStepToF(&D_menu_801B86A8, -5.0f, 0.2f, 100.0f, 0.01f);
                Math_SmoothStepToF(&D_menu_801B86BC, 100.0f, 0.2f, 100.0f, 0.01f);
                Math_SmoothStepToF(&D_menu_801B86B4, 40.0f, 0.2f, 100.0f, 0.01f);

                Title_SetCamUp2(D_menu_801B86BC, D_menu_801B86C0, D_menu_801B86C4, &gCsCamEyeX, &gCsCamEyeY,
                                &gCsCamEyeZ, D_menu_801B86B4, &gCsCamAtX, &gCsCamAtY, &gCsCamAtZ, D_menu_801B86B8,
                                D_menu_801B86A8, D_menu_801B86AC);

                if (sTimer3 > 8) {
                    Audio_SetEnvSfxReverb(0);
                    sSceneState = 0;
                    sCutsceneState = 5; // TITLE_TAKE_OFF_SPACE
                }
                sTimer3++;
            }
            break;
    }
    Title_SetLightRot(D_menu_801B86C8, D_menu_801B86CC, 100.0f, &D_menu_801B82E0, &D_menu_801B82E4, &D_menu_801B82E8);
    D_menu_801B7BEC++;
}

void Title_CsTakeOff_Draw(void) {
    s32 i;

    if (sTitleCorneria.draw) {
        Title_Corneria_Draw(0.0f);
    }

    Title_GreatFoxDeck_Draw();

    for (i = ARRAY_COUNT(sTitleArwing) - 1; i >= 0; i--) {
        if (sTitleArwing[i].draw) {
            Title_GreatFoxDeckLauncher_Draw(i);
        }
    }

    for (i = 0; i < ARRAY_COUNT(sTitleArwing); i++) {
        if (sTitleArwing[i].draw) {
            Title_Arwing_Draw(i);
        }
    }
}

void Title_CsTakeOffSpace_Setup(void) {
    s32 i;

    gStarCount = 1;
    sMaxExplosions = 10;

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

    sDrawTakeOffSpace = true;
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

    sTitleCorneria.pos.x = 130.0f;
    sTitleCorneria.pos.y = -30.0f;
    sTitleCorneria.pos.z = 2000.0f;
    sTitleCorneria.scale = 8.0f;
    sTitleCorneria.draw = false;

    sTitleGreatFox.pos.x = 0.0f;
    sTitleGreatFox.pos.y = 0.0f;
    sTitleGreatFox.pos.z = 0.0f;
    sTitleGreatFox.xRot = 0.0f;
    sTitleGreatFox.yRot = 0.0f;
    sTitleGreatFox.zRot = 0.0f;
    sTitleGreatFox.scale = 0.1f;

    D_menu_801B86C8 = 0.0f;
    D_menu_801B86CC = 0.0f;

    gLight1R = 101;
    gLight1G = 106;
    gLight1B = 92;
    gAmbientR = 3;
    gAmbientG = 4;
    gAmbientB = 10;

    for (i = 0; i < ARRAY_COUNT(sTitleArwing); i++) {
        sTitleArwing[i].pos.x = 0.0f;
        sTitleArwing[i].pos.y = -40.0f;
        sTitleArwing[i].pos.z = -30.0f;
        sTitleArwing[i].scale = 0.1f;
        sTitleArwing[i].xRot = 0.0f;
        sTitleArwing[i].yRot = 0.0f;
        sTitleArwing[i].zRot = 0.0f;
        sTitleArwing[i].vel = 0.05f;
        sTitleArwing[i].cockpitGlassXrot = 0.0f;
        sTitleArwing[i].laserGunsYpos = 0.0f;
        sTitleArwing[i].teamFaceXrot = 0.0f;
        sTitleArwing[i].teamFaceYrot = 0.0f;
        sTitleArwing[i].drawFace = i + 1;
        sTitleArwing[i].unk_3C = 1;
        sTitleArwing[i].unk_40 = 0;
        sTitleArwing[i].unk_44 = 1.2f;
        sTitleArwing[i].drawShadow = false;
        sTitleArwing[i].draw = false;
    }

    D_menu_801B86BC = -8.0f;
    D_menu_801B86C0 = -37.0f;
    D_menu_801B86C4 = 64.0f;

    D_menu_801B86A8 = 5.899999f;
    D_menu_801B86AC = -112.74477f;
    D_menu_801B86B4 = 235.0f;
    D_menu_801B86B8 = 50.00f;

    sTitleCamUpX = 0.0f;
    sTitleCamUpY = 1.0f;
    sTitleCamUpZ = 0.0f;

    Title_SetCamUp2(D_menu_801B86BC, D_menu_801B86C0, D_menu_801B86C4, &gCsCamEyeX, &gCsCamEyeY, &gCsCamEyeZ,
                    D_menu_801B86B4, &gCsCamAtX, &gCsCamAtY, &gCsCamAtZ, D_menu_801B86B8, D_menu_801B86A8,
                    D_menu_801B86AC);
}

CameraPoint D_menu_801ADF84[50] = {
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

void Title_CsTakeOffSpace_Update(void) {
    s32 i;
    f32 x;
    f32 y;
    f32 z;
    static f32 D_menu_801AE434[4] = { -15.0f, -5.0f, 5.0f, 10.0f };
    static f32 D_menu_801AE444[4] = { -50.0f, -45.0f, -55.0f, -60.0f };
    static f32 D_menu_801AE454[4] = { 265.0f, 260.0f, 255.0f, 230.0f };

    switch (sSceneState) {
        case 0:
            AUDIO_PLAY_SFX(NA_SE_GREATFOX_ENGINE, sTitleGreatFox.sfxSource, 0);
            AUDIO_PLAY_SFX(NA_SE_GREATFOX_BURNER, sTitleGreatFox.sfxSource, 0);

            Title_CsTakeOffSpace_Setup();

            sTimer3 = 0;
            D_menu_801B7BEC = 0;
            sTitleCorneria.draw = true;

            sTitleArwing[TEAM_FOX].timer = 3;
            sTitleArwing[TEAM_FALCO].timer = 23;
            sTitleArwing[TEAM_PEPPY].timer = 43;
            sTitleArwing[TEAM_SLIPPY].timer = 63;

            D_menu_801B8294 = D_menu_801ADF84;
            D_menu_801B8298 = 0;
            D_menu_801B828C = 0.0f;
            D_menu_801B8290 = 0.042f;

            sSceneState++;
            break;

        case 1:
            for (i = 0; i < ARRAY_COUNT(sTitleArwing); i++) {
                if (sTitleArwing[i].timer > 0) {
                    sTitleArwing[i].timer--;
                } else {
                    if (sTitleArwing[i].timer == 0) {
                        AUDIO_PLAY_SFX(NA_SE_PASS, sTitleArwing[i].sfxSource, 0);
                        sTitleArwing[i].timer = -1;
                        sTitleArwing[i].draw = true;
                    }

                    Math_SmoothStepToF(&sTitleArwing[i].pos.y, D_menu_801AE444[i], sTitleArwing[i].vel, 100.0f, 0.001f);
                    Math_SmoothStepToF(&sTitleArwing[i].pos.x, D_menu_801AE434[i], sTitleArwing[i].vel, 100.0f, 0.001f);
                    Math_SmoothStepToF(&sTitleArwing[i].pos.z, D_menu_801AE454[i], sTitleArwing[i].vel, 100.0f, 0.001f);

                    sTitleArwing[i].vel *= 1.05f;

                    if (sTitleArwing[i].pos.z == D_menu_801AE454[i]) {
                        sTitleArwing[i].scale -= 0.002f;
                        if (sTitleArwing[i].scale < 0.0f) {
                            sTitleArwing[i].scale = 0.0f;
                            sTitleArwing[i].draw = false;
                        }
                    }

                    x = D_menu_801AE434[i] - sTitleArwing[i].pos.x;
                    y = D_menu_801AE444[i] - sTitleArwing[i].pos.y;
                    z = D_menu_801AE454[i] + 10.0f - sTitleArwing[i].pos.z;

                    sTitleArwing[i].xRot = RAD_TO_DEG(-Math_Atan2F(y, sqrtf(SQ(x) + SQ(z))));
                    sTitleArwing[i].yRot = RAD_TO_DEG(Math_Atan2F(x, z));
                }
            }

            if (sTimer3 == 125) {
                D_menu_801B869C = 1;
            }

            if (gFillScreenAlpha == 255) {
                Audio_KillSfxBySourceAndId(sTitleGreatFox.sfxSource, NA_SE_GREATFOX_ENGINE);
                Audio_KillSfxBySourceAndId(sTitleGreatFox.sfxSource, NA_SE_GREATFOX_BURNER);
                sSceneState++;
            }
            Title_ScreenFade_Update();
            sTimer3++;
            break;

        case 2:
            gFillScreenAlpha = 0;
            gStarCount = 0;
            sDrawTakeOffSpace = false;
            sTimer1 = 20;
            sSceneState++;
            break;

        case 3:
            if (sTimer1 != 0) {
                break;
            }
            sSceneState = 0;
            gDrawMode = DRAW_NONE;
            sCutsceneState = TITLE_SCREEN;
            AUDIO_SET_SPEC(SFXCHAN_0, AUDIOSPEC_23);
            break;
    }

    Title_GetCamRot(&D_menu_801B86A8, &D_menu_801B86AC);
    Title_SetCamUp(D_menu_801B86A8, D_menu_801B86AC);
    Title_Cutscene_SetCamera(D_menu_801B8294, 9, D_menu_801B8290);
    Title_SetLightRot(D_menu_801B86C8, D_menu_801B86CC, 100.0f, &D_menu_801B82E0, &D_menu_801B82E4, &D_menu_801B82E8);
    Camera_SetStarfieldPos(gCsCamEyeX, gCsCamEyeY, gCsCamEyeZ, gCsCamAtX, gCsCamAtY, gCsCamAtZ);

    D_menu_801B7BEC++;
}

void Title_CsTakeOffSpace_Draw(void) {
    s32 i;

    if (sDrawTakeOffSpace) {
        if (sTitleCorneria.draw) {
            Title_Corneria_Draw(-1000.0f);
        }

        Title_GreatFox_Draw();

        for (i = 0; i < 4; i++) {
            if ((sTitleArwing[i].timer <= 0) && sTitleArwing[i].draw) {
                Title_Arwing_Draw(i);
            }
        }
    }
}

void Title_Cutscene_SetCamera(CameraPoint* arg0, s32 arg1, f32 arg2) {
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

        Title_Camera_Calc(&pos, &arg0[D_menu_801B8298], D_menu_801B828C, var_a3);

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

// Calculation of camera movements using Cubic spline interpolation
void Title_Camera_Calc(CameraPoint* pos, CameraPoint* arg1, f32 weight, s32 arg3) {
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

// Arwings in the take off cutscene
void Title_Arwing_Draw(TitleTeam teamIdx) {
    ArwingInfo arwing;

    Lights_SetOneLight(&gMasterDisp, D_menu_801B82E0, D_menu_801B82E4, D_menu_801B82E8, gLight1R, gLight1G, gLight1B,
                       gAmbientR, gAmbientG, gAmbientB);

    RCP_SetupDL(&gMasterDisp, SETUPDL_23);

    Matrix_Push(&gGfxMatrix);

    Matrix_Translate(gGfxMatrix, sTitleArwing[teamIdx].pos.x, sTitleArwing[teamIdx].pos.y, sTitleArwing[teamIdx].pos.z,
                     MTXF_APPLY);

    Matrix_Scale(gGfxMatrix, sTitleArwing[teamIdx].scale, sTitleArwing[teamIdx].scale, sTitleArwing[teamIdx].scale,
                 MTXF_APPLY);

    Matrix_RotateZ(gGfxMatrix, sTitleArwing[teamIdx].zRot * M_DTOR, MTXF_APPLY);
    Matrix_RotateX(gGfxMatrix, sTitleArwing[teamIdx].xRot * M_DTOR, MTXF_APPLY);
    Matrix_RotateY(gGfxMatrix, sTitleArwing[teamIdx].yRot * M_DTOR, MTXF_APPLY);

    Matrix_SetGfxMtx(&gMasterDisp);

    arwing.rightWingState = arwing.leftWingState = WINGSTATE_INTACT;
    arwing.laserGunsXpos = arwing.wingsXrot = arwing.wingsYrot = arwing.wingsZrot = arwing.upperRightFlapYrot =
        arwing.bottomRightFlapYrot = arwing.upperLeftFlapYrot = arwing.bottomLeftFlapYrot = arwing.unk_28 = 0.0f;

    arwing.laserGunsYpos = sTitleArwing[teamIdx].laserGunsYpos;
    arwing.drawFace = sTitleArwing[teamIdx].drawFace;
    arwing.teamFaceXrot = sTitleArwing[teamIdx].teamFaceXrot;
    arwing.teamFaceYrot = sTitleArwing[teamIdx].teamFaceYrot;
    arwing.cockpitGlassXrot = sTitleArwing[teamIdx].cockpitGlassXrot;

    Display_ArwingWings(&arwing);

    Object_UpdateSfxSource(sTitleArwing[teamIdx].sfxSource);

    if (sTitleArwing[teamIdx].unk_40 != 0) {
        Title_EngineGlowParticles_Draw(teamIdx);
    }

    if (sTitleArwing[teamIdx].unk_3C != 0) {
        Title_Arwing_DrawEngineGlow(teamIdx);
    }

    if (sTitleArwing[teamIdx].drawShadow) {
        Title_ArwingShadow_Draw(teamIdx);
    }

    Matrix_Pop(&gGfxMatrix);
}

// Engine glow of Team Arwing in the take off cutscene
void Title_Arwing_DrawEngineGlow(TitleTeam teamIdx) {
    f32 engineGlowScale;
    f32 sp40;
    f32 sp3C;
    f32 var_fv1;
    f32 var_fa0;
    f32 temp;

    RCP_SetupDL(&gMasterDisp, SETUPDL_67);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    if (sTitleArwing[teamIdx].unk_40 == 1) {
        var_fa0 = -30.0f;
        var_fv1 = 0.02f;
        gDPSetEnvColor(gMasterDisp++, 128, 128, 255, 255);
    } else {
        var_fa0 = -65.0f;
        var_fv1 = 0.2f;
        gDPSetEnvColor(gMasterDisp++, 0, 0, 255, 255);
    }

    engineGlowScale = sTitleArwing[teamIdx].unk_44;

    if ((gGameFrameCount % 2) != 0) {
        engineGlowScale += var_fv1;
    }

    Matrix_Push(&gGfxMatrix);

    // @port: Tag the transform.
    FrameInterpolation_RecordOpenChild("Title_Arwing_DrawEngineGlow", teamIdx);

    Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, var_fa0, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, engineGlowScale, engineGlowScale * 0.7f, engineGlowScale, MTXF_APPLY);

    Matrix_RotateZ(gGfxMatrix, -sTitleArwing[teamIdx].zRot * M_DTOR, MTXF_APPLY);
    Matrix_RotateX(gGfxMatrix, -sTitleArwing[teamIdx].xRot * M_DTOR, MTXF_APPLY);
    Matrix_RotateY(gGfxMatrix, -sTitleArwing[teamIdx].yRot * M_DTOR, MTXF_APPLY);

    sp3C = -Math_Atan2F(gCsCamEyeX - sTitleArwing[teamIdx].pos.x, gCsCamEyeZ - sTitleArwing[teamIdx].pos.z);
    temp = sqrtf(SQ(gCsCamEyeZ - sTitleArwing[teamIdx].pos.z) + SQ(gCsCamEyeX - sTitleArwing[teamIdx].pos.x));
    sp40 = Math_Atan2F(gCsCamEyeY - sTitleArwing[teamIdx].pos.y, temp);

    Matrix_RotateY(gGfxMatrix, -sp3C, MTXF_APPLY);
    Matrix_RotateX(gGfxMatrix, -sp40, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);

    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
    gSPDisplayList(gMasterDisp++, aTitleArwingEngineGlowDL);
    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);

    Matrix_Pop(&gGfxMatrix);

    // @port Pop the transform id.
    FrameInterpolation_RecordCloseChild();
}

void Title_EngineGlowParticles_Draw(TitleTeam teamIdx) {
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

    sp6C = -Math_Atan2F(gCsCamEyeX - sTitleArwing[teamIdx].pos.x, gCsCamEyeZ - sTitleArwing[teamIdx].pos.z);
    temp = sqrtf(SQ(gCsCamEyeZ - sTitleArwing[teamIdx].pos.z) + SQ(gCsCamEyeX - sTitleArwing[teamIdx].pos.x));
    sp70 = Math_Atan2F(gCsCamEyeY - sTitleArwing[teamIdx].pos.y, temp);

    RCP_SetupDL(&gMasterDisp, SETUPDL_49);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 253, 253, 255, 255);
    gDPSetEnvColor(gMasterDisp++, 251, 251, 255, 255);

    for (i = 0; i < D_menu_801B8100; i++) {
        if (D_menu_801B7FC0[i] == 0.0f) {
            continue;
        }

        Matrix_Push(&gGfxMatrix);

        // @port: Tag the transform.
        FrameInterpolation_RecordOpenChild("Title_EngineGlowParticles_Draw", i);

        Matrix_Translate(gGfxMatrix, D_menu_801B7D40[i], D_menu_801B7DE0[i], D_menu_801B7E80[i], MTXF_APPLY);
        Matrix_Scale(gGfxMatrix, D_menu_801B7FC0[i], D_menu_801B7FC0[i], D_menu_801B7FC0[i], MTXF_APPLY);

        Matrix_RotateZ(gGfxMatrix, -sTitleArwing[teamIdx].zRot * M_DTOR, MTXF_APPLY);
        Matrix_RotateX(gGfxMatrix, -sTitleArwing[teamIdx].xRot * M_DTOR, MTXF_APPLY);
        Matrix_RotateY(gGfxMatrix, -sTitleArwing[teamIdx].yRot * M_DTOR, MTXF_APPLY);

        Matrix_RotateY(gGfxMatrix, -sp6C, MTXF_APPLY);
        Matrix_RotateX(gGfxMatrix, -sp70, MTXF_APPLY);

        Matrix_SetGfxMtx(&gMasterDisp);

        gSPDisplayList(gMasterDisp++, aTitleArwingEngineGlowDL);

        Matrix_Pop(&gGfxMatrix);

        // @port Pop the transform id.
        FrameInterpolation_RecordCloseChild();
    }
}

void Title_ArwingShadow_Draw(s32 teamIdx) {
    Matrix_Push(&gGfxMatrix);

    // @port: Tag the transform.
    FrameInterpolation_RecordOpenChild("Title_ArwingShadow_Draw", teamIdx);

    Matrix_Translate(gGfxMatrix, 0.0f,
                     (D_menu_801B9050 - sTitleArwing[teamIdx].pos.y * 2.05f) + (D_menu_801B9048 - 84.0f) * 1.99f, 0.0f,
                     MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 1.0f, MTXF_APPLY);
    Matrix_RotateY(gGfxMatrix, M_PI, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);

    RCP_SetupDL_64();

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 240);
    gSPDisplayList(gMasterDisp++, aTitleArwingShadowDL);

    Matrix_Pop(&gGfxMatrix);

    // @port Pop the transform id.
    FrameInterpolation_RecordCloseChild();
}

void Title_Corneria_Draw(f32 zPos) {
    f32 xRot;
    f32 yRot;

    Title_GetCamRot(&xRot, &yRot);
    RCP_SetupDL(&gMasterDisp, SETUPDL_53);

    if (zPos != 0.0f) {
        sTitleCorneria.pos.z = gCsCamEyeZ - zPos;
    }

    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, sTitleCorneria.pos.x, sTitleCorneria.pos.y, sTitleCorneria.pos.z, MTXF_APPLY);
    Matrix_RotateY(gGfxMatrix, M_DTOR * yRot, MTXF_APPLY);
    Matrix_RotateX(gGfxMatrix, M_DTOR * xRot, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, sTitleCorneria.scale, sTitleCorneria.scale, sTitleCorneria.scale, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);

    gSPDisplayList(gMasterDisp++, aPlanetCorneriaDL);

    Title_CorneriaExplosions_Draw();

    Matrix_Pop(&gGfxMatrix);
}

void Title_GreatFox_Draw(void) {
    Lights_SetOneLight(&gMasterDisp, D_menu_801B82E0, D_menu_801B82E4, D_menu_801B82E8, gLight1R, gLight1G, gLight1B,
                       gAmbientR, gAmbientG, gAmbientB);

    Matrix_Push(&gGfxMatrix);

    Matrix_Translate(gGfxMatrix, sTitleGreatFox.pos.x, sTitleGreatFox.pos.y, sTitleGreatFox.pos.z, MTXF_APPLY);

    Matrix_RotateZ(gGfxMatrix, M_DTOR * sTitleGreatFox.zRot, MTXF_APPLY);
    Matrix_RotateX(gGfxMatrix, M_DTOR * sTitleGreatFox.xRot, MTXF_APPLY);
    Matrix_RotateY(gGfxMatrix, M_DTOR * sTitleGreatFox.yRot, MTXF_APPLY);

    Matrix_Scale(gGfxMatrix, sTitleGreatFox.scale, sTitleGreatFox.scale, sTitleGreatFox.scale, MTXF_APPLY);

    Matrix_SetGfxMtx(&gMasterDisp);
    RCP_SetupDL(&gMasterDisp, SETUPDL_23);

    gGreatFoxIntact = true; // Unused here

    Cutscene_DrawGreatFox();

    Object_UpdateSfxSource(sTitleGreatFox.sfxSource);

    Matrix_Pop(&gGfxMatrix);
}

void Title_CorneriaExplosions_Draw(void) {
    f32 scale;
    s32 i;

    for (i = 0; i < sMaxExplosions; i++) {
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

    RCP_SetupDL(&gMasterDisp, SETUPDL_49);

    for (i = 0; i < sMaxExplosions; i++) {
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 200, 200, D_menu_801B7CC8[i]);
        gDPSetEnvColor(gMasterDisp++, 255, 0, 0, D_menu_801B7CF0[i]);

        scale = D_menu_801B7C48[i] / sTitleCorneria.scale;

        Matrix_Push(&gGfxMatrix);

        // @port Skip interpolation
        FrameInterpolation_ShouldInterpolateFrame(false);

        Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, 5.0f, MTXF_APPLY);
        Matrix_RotateZ(gGfxMatrix, D_menu_801B7C20[i] * M_DTOR, MTXF_APPLY);
        Matrix_Translate(gGfxMatrix, 0.0f, D_menu_801B7BF8[i], 0.0f, MTXF_APPLY);
        Matrix_Scale(gGfxMatrix, scale, scale, scale, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);

        gSPDisplayList(gMasterDisp++, aTitleArwingEngineGlowDL);

        Matrix_Pop(&gGfxMatrix);

        // @port renable interpolation
        FrameInterpolation_ShouldInterpolateFrame(true);
    }
}

void Title_TeamRunning_Draw(TitleTeam teamIdx) {
    Vec3f frameTable[50];
    s32 frame;
    f32 temp_fv1;

    Lights_SetOneLight(&gMasterDisp, D_menu_801B82E0, D_menu_801B82E4, D_menu_801B82E8, gLight1R, gLight1G, gLight1B,
                       gAmbientR, gAmbientG, gAmbientB);

    frame = sTitleTeam[teamIdx].frameCount % Animation_GetFrameCount(sTeamAnim[teamIdx].cutscene);

    RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, 255, 995, 1000);

    Matrix_Push(&gGfxMatrix);

    Matrix_Translate(gGfxMatrix, sTitleTeam[teamIdx].pos.x, sTitleTeam[teamIdx].pos.y,
                     sTitleTeam[teamIdx].pos.z + D_menu_801B84D0, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, D_menu_801B84D4, D_menu_801B84D4, D_menu_801B84D4, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);

    if (teamIdx == TEAM_PEPPY) {
        gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
    }

    Animation_GetFrameData(sTeamAnim[teamIdx].cutscene, frame, frameTable);
    Animation_DrawSkeleton(0, sTeamAnim[teamIdx].skeleton, frameTable, NULL, NULL, NULL, &gIdentityMatrix);

    if (teamIdx == TEAM_PEPPY) {
        gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
    }

    if (teamIdx == TEAM_FOX) {
        Object_UpdateSfxSource(D_menu_801B84D8);
    }

    Matrix_Pop(&gGfxMatrix);

    Matrix_Push(&gGfxMatrix);

    // @port: Tag the transform.
    FrameInterpolation_RecordOpenChild("Title_TeamRunning_Draw", teamIdx);

    Matrix_Translate(gGfxMatrix, sTitleTeam[teamIdx].pos.x - 5.0f, 5.0f,
                     sTitleTeam[teamIdx].pos.z + 10.0f + D_menu_801B84D0, MTXF_APPLY);

    Matrix_Scale(gGfxMatrix, sTitleTeam[teamIdx].shadowScale, sTitleTeam[teamIdx].shadowScale,
                 sTitleTeam[teamIdx].shadowScale, MTXF_APPLY);

    Matrix_SetGfxMtx(&gMasterDisp);

    RCP_SetupDL_64();

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 128);
    gSPDisplayList(gMasterDisp++, aTeamShadowDL);

    Matrix_Pop(&gGfxMatrix);

    // @port Pop the transform id.
    FrameInterpolation_RecordCloseChild();

    temp_fv1 = SIN_DEG(frame * 12.0f) * 15.0f;

    if (temp_fv1 >= 0) {
        sTitleTeam[teamIdx].unk_0C = temp_fv1;
    } else if (temp_fv1 > -2.0f) {
        sTitleTeam[teamIdx].unk_0C = -temp_fv1;
    } else {
        sTitleTeam[teamIdx].unk_0C = 0.0f;
    }
    sTitleTeam[teamIdx].shadowScale = 3.0f - (sTitleTeam[teamIdx].unk_0C / 100.0f);
}

void Title_Team_Draw(TitleTeam teamIdx) {
    Vec3f frameTable[50];
    s32 frame;

    frame = sTitleTeam[teamIdx].frameCount % Animation_GetFrameCount(sTeamAnim[teamIdx].title);

    RCP_SetupDL(&gMasterDisp, SETUPDL_23);

    Lights_SetOneLight(&gMasterDisp, D_menu_801B82E0, D_menu_801B82E4, D_menu_801B82E8, gLight1R, gLight1G, gLight1B,
                       gAmbientR, gAmbientG, gAmbientB);

    Matrix_Push(&gGfxMatrix);

    // @port: Tag the transform.
    FrameInterpolation_RecordOpenChild("Title_Team_Draw", teamIdx);

    Matrix_RotateX(gGfxMatrix, sTitleTeam[teamIdx].unk_48 * M_DTOR, MTXF_APPLY);
    Matrix_RotateY(gGfxMatrix, sTitleTeam[teamIdx].unk_4C * M_DTOR, MTXF_APPLY);
    Matrix_RotateZ(gGfxMatrix, sTitleTeam[teamIdx].unk_50 * M_DTOR, MTXF_APPLY);

    Matrix_Translate(gGfxMatrix, sTitleTeam[teamIdx].pos.x, sTitleTeam[teamIdx].pos.y, sTitleTeam[teamIdx].pos.z,
                     MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, D_menu_801B84D4, D_menu_801B84D4, D_menu_801B84D4, MTXF_APPLY);

    Matrix_SetGfxMtx(&gMasterDisp);

    Math_SmoothStepToVec3fArray(frameTable, sCharFrameTable[teamIdx], 1,
                                Animation_GetFrameData(sTeamAnim[teamIdx].title, frame, frameTable), 0.2f, 100.0f,
                                0.0001f);
    Animation_DrawSkeleton(1, sTeamAnim[teamIdx].skeleton, sCharFrameTable[teamIdx], Title_Team_OverrideLimbDraw, NULL,
                           &teamIdx, &gIdentityMatrix);

    Matrix_Pop(&gGfxMatrix);

    // @port Pop the transform id.
    FrameInterpolation_RecordCloseChild();
}

bool Title_Team_OverrideLimbDraw(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    f32 x;
    f32 y;
    f32 z;
    TitleTeam teamIdx = *(TitleTeam*) thisx;

    if ((D_menu_801B86A4 < 2) && D_menu_801B9040) {
        x = D_menu_801B905C - sTitleTeam[teamIdx].pos.x;
        y = D_menu_801B9060 - (sTitleTeam[teamIdx].pos.y + sTitleTeam[teamIdx].unk_14);
        z = D_menu_801B9064 - sTitleTeam[teamIdx].pos.z;

        sTitleTeam[teamIdx].unk_28 = Math_Atan2F(x, sqrtf(SQ(y) + SQ(z))) * M_RTOD;
        sTitleTeam[teamIdx].unk_2C = Math_Atan2F(y, z) * M_RTOD;

        sTitleTeam[teamIdx].unk_38 = sTitleTeam[teamIdx].unk_28;
        sTitleTeam[teamIdx].unk_3C = sTitleTeam[teamIdx].unk_2C;

        if (sTitleTeam[teamIdx].unk_28 < -45.0f) {
            sTitleTeam[teamIdx].unk_28 = -45.0f;
        } else if (sTitleTeam[teamIdx].unk_28 > 45.0f) {
            sTitleTeam[teamIdx].unk_28 = 45.0f;
        }

        if (sTitleTeam[teamIdx].unk_2C < -40.0f) {
            sTitleTeam[teamIdx].unk_2C = -40.0f;
        } else if (sTitleTeam[teamIdx].unk_2C > 55.0f) {
            sTitleTeam[teamIdx].unk_2C = 55.0f;
        }

        if (sTitleTeam[teamIdx].unk_38 < -20.0f) {
            sTitleTeam[teamIdx].unk_38 = sTitleTeam[teamIdx].unk_38 - (-20.0f);
            if (sTitleTeam[teamIdx].unk_38 < -20.0f) {
                sTitleTeam[teamIdx].unk_38 = -20.0f;
            }
        } else if (sTitleTeam[teamIdx].unk_38 > 20.0f) {
            sTitleTeam[teamIdx].unk_38 = sTitleTeam[teamIdx].unk_38 - 20.0f;
            if (sTitleTeam[teamIdx].unk_38 > 20.0f) {
                sTitleTeam[teamIdx].unk_38 = 20.0f;
            }
        } else {
            sTitleTeam[teamIdx].unk_38 = 0.0f;
        }

        if (sTitleTeam[teamIdx].unk_3C < -35.0f) {
            sTitleTeam[teamIdx].unk_3C = sTitleTeam[teamIdx].unk_3C - (-35.0f);
            if (sTitleTeam[teamIdx].unk_3C < -10.0f) {
                sTitleTeam[teamIdx].unk_3C = -10.0f;
            }
        } else if (sTitleTeam[teamIdx].unk_3C > 40.0f) {
            sTitleTeam[teamIdx].unk_3C = sTitleTeam[teamIdx].unk_3C - 40.0f;
            if (sTitleTeam[teamIdx].unk_3C > 10.0f) {
                sTitleTeam[teamIdx].unk_3C = 10.0f;
            }
        } else {
            sTitleTeam[teamIdx].unk_3C = 0.0f;
        }

        Math_SmoothStepToF(&sTitleTeam[teamIdx].unk_30, sTitleTeam[teamIdx].unk_28, 0.01f, 100.0f, 0.0001f);
        Math_SmoothStepToF(&sTitleTeam[teamIdx].unk_34, sTitleTeam[teamIdx].unk_2C, 0.01f, 100.0f, 0.0001f);
        Math_SmoothStepToF(&sTitleTeam[teamIdx].unk_40, sTitleTeam[teamIdx].unk_38, 0.005f, 100.0f, 0.0001f);
        Math_SmoothStepToF(&sTitleTeam[teamIdx].unk_44, sTitleTeam[teamIdx].unk_3C, 0.005f, 100.0f, 0.0001f);
    }

    switch (teamIdx) {
        case TEAM_FOX:
            if (limbIndex == 1) {
                rot->z += sTitleTeam[teamIdx].unk_18;
            }
            if (limbIndex == 19) {
                rot->x += sTitleTeam[teamIdx].unk_30;
                rot->y += sTitleTeam[teamIdx].unk_34;
            }
            if (limbIndex == 20) {
                rot->x += sTitleTeam[teamIdx].unk_40;
                rot->y += sTitleTeam[teamIdx].unk_44;
            }
            break;

        case TEAM_FALCO:
            if (limbIndex == 1) {
                rot->z += sTitleTeam[teamIdx].unk_18;
            }
            if (limbIndex == 11) {
                rot->z += sTitleTeam[teamIdx].unk_20;
            }
            if (limbIndex == 19) {
                rot->x += sTitleTeam[teamIdx].unk_30;
                rot->y += sTitleTeam[teamIdx].unk_34;
            }
            if (limbIndex == 20) {
                rot->x += sTitleTeam[teamIdx].unk_40;
                rot->y += sTitleTeam[teamIdx].unk_44;
            }
            if (limbIndex == 21) {
                rot->x += -5.0f;
            }
            break;

        case TEAM_PEPPY:
            if (limbIndex == 1) {
                rot->z += sTitleTeam[teamIdx].unk_18;
            }
            if (limbIndex == 19) {
                rot->x += sTitleTeam[teamIdx].unk_30;
                rot->y += sTitleTeam[teamIdx].unk_34;
            }
            if (limbIndex == 20) {
                rot->x += sTitleTeam[teamIdx].unk_40;
                rot->y += sTitleTeam[teamIdx].unk_44;
            }
            if (limbIndex == 21) {
                rot->x += 10.0f;
            }
            break;

        case TEAM_SLIPPY:
            if (limbIndex == 1) {
                rot->z += sTitleTeam[teamIdx].unk_18;
            }
            if (limbIndex == 17) {
                rot->x += sTitleTeam[teamIdx].unk_30;
                rot->y += sTitleTeam[teamIdx].unk_34;
            }
            if (limbIndex == 18) {
                rot->x += sTitleTeam[teamIdx].unk_40;
                rot->y += sTitleTeam[teamIdx].unk_44;
            }
            if (limbIndex == 19) {
                rot->x += 4.0f;
            }
            break;
    }

    return false;
}

f32 prevPassageWayOffset = 0.0f;

void Title_Passage_Draw(void) {
    f32 sZoffsetScale;

    Lights_SetOneLight(&gMasterDisp, 0, 0, 0, 0, 0, 0, gAmbientR, gAmbientG, gAmbientB);

    if (gCsCamAtZ < gCsCamEyeZ) {
        sZoffsetScale = 1.0f;
    } else {
        sZoffsetScale = 3.0f;
    }

    sPassageWayZoffset += 70.0f;
    sPassageWayZoffset = Math_ModF(sPassageWayZoffset, 4101.6f);

    s8 skipInterpolation = (fabsf(sPassageWayZoffset - prevPassageWayOffset) > 4101.6f / 2.0f);

    RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, 255, 995, 1000);

    Matrix_Push(&gGfxMatrix);

    if (skipInterpolation) {
        // @port Skip interpolation
        FrameInterpolation_ShouldInterpolateFrame(false);

    } else {
        // @port: Tag the transform.
        FrameInterpolation_RecordOpenChild("Title_Passage_Draw", 0);
    }

    Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, (3079.2002f * sZoffsetScale) - sPassageWayZoffset, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, 0.6f, 0.6f, 0.6f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);

    gSPDisplayList(gMasterDisp++, aTitleCsPassageWayDL);

    Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -6836.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);

    gSPDisplayList(gMasterDisp++, aTitleCsPassageWayDL);

    Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -6836.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);

    gSPDisplayList(gMasterDisp++, aTitleCsPassageWayDL);

    Matrix_Pop(&gGfxMatrix);

    if (skipInterpolation) {
        // @port Skip interpolation
        FrameInterpolation_ShouldInterpolateFrame(true);
    } else {
        // @port Pop the transform id.
        FrameInterpolation_RecordCloseChild();
    }

    prevPassageWayOffset = sPassageWayZoffset;
}

void Title_StarfoxLogo_Draw(void) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_83_POINT);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    // LTodo: Validate this
    Lib_TextureRect_RGBA16(&gMasterDisp, aTitleStarfoxLogoTex, 236, 60, sTitleStarfoxLogoXpos, sTitleStarfoxLogoYpos,
                           1.0f, 1.0f);
}

void Title_64Logo_Draw(void) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_53);
    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, D_menu_801B905C, D_menu_801B9060, D_menu_801B9064, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, D_menu_801B9068, D_menu_801B906C, 1.0f, MTXF_APPLY);
    Matrix_RotateX(gGfxMatrix, M_DTOR * 90, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, a64LogoDL);
    Matrix_Pop(&gGfxMatrix);
}

void Title_CopyrightSymbol_Draw(void) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_83_POINT);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
    Lib_TextureRect_IA8(&gMasterDisp, aTitleCopyrightTex, 16, 16, 234.0f, 20.0f, 1.0f, 1.0f);
}

void Title_PressStart_Draw(void) {
    f32 yPos;
    s32 i;
    static f32 sNoControllerBgXpos = 68.0f;
    static f32 sNoControllerBgYpos = 170.0f;
    static f32 sNoControllerBgXscale = 5.55f;
    static f32 sNoControllerBgYscale = 0.9f;
    static f32 D_menu_801AE474 = 70.0f;
    static f32 D_menu_801AE478 = 172.0f;

    if (gControllerLock == 0) {
        yPos = 188.0f;

        if ((s32) Math_SmoothStepToF(&sTitleTextPrimCol, sTitleTextPrimColTarget, 0.5f, 100.0f, 1.0f) == 0.0f) {
            if (sTitleTextPrimCol == 32.0f) {
                sTitleTextPrimColTarget = 255.0f;
            } else {
                sTitleTextPrimColTarget = 32.0f;
            }
        }

        if (gMainController < 0) {
            // No Controller background
            RCP_SetupDL(&gMasterDisp, SETUPDL_85_POINT);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 60, 60, 255, 200);

            Lib_TextureRect_CI8(&gMasterDisp, aNoControllerBgTex, aNoControllerBgTLUT, 32, 32, sNoControllerBgXpos,
                                sNoControllerBgYpos, sNoControllerBgXscale, sNoControllerBgYscale);

            // No Controller
            RCP_SetupDL(&gMasterDisp, SETUPDL_83_POINT);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, (s32) sTitleTextPrimCol, (s32) sTitleTextPrimCol, 255);

            Lib_TextureRect_IA8(&gMasterDisp, aTitleNoControllerTex, 176, 24, D_menu_801AE474, D_menu_801AE478, 1.0f,
                                1.0f);
        } else {
            // Press Start
            RCP_SetupDL(&gMasterDisp, SETUPDL_83_POINT);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, (s32) sTitleTextPrimCol, (s32) sTitleTextPrimCol, 255);

            Lib_TextureRect_IA8(&gMasterDisp, aTitlePressStartTex, 120, 13, 101.0f, yPos, 1.0f, 1.0f);
        }
    }
}

void Title_Copyright_Draw(void) {
    s32 i;

    RCP_SetupDL(&gMasterDisp, SETUPDL_83_POINT);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    Lib_TextureRect_IA8(&gMasterDisp, a1997NintendoTex, 120, 12, 102.0f, 209.0f, 1.0f, 1.0f);
}

void Title_TeamName_Draw(void) {
    s32 i;
    Gfx* temp_v1;
    f32 temp_fs2;
    s32 var_s0;
    s32 var_s0_2;
    f32 temp;
    static f32 D_menu_801AE47C[] = { 90.0f, 100.0f, 75.0f, 75.0f };

    temp_fs2 = D_menu_801AE47C[D_menu_801B8340];
    temp = 210.0f;

    RCP_SetupDL(&gMasterDisp, SETUPDL_83_POINT);

    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

    switch (D_menu_801B8340) {
        case 0:
            Lib_TextureRect_IA8(&gMasterDisp, gTitleSlippyCard, 144, 13, temp_fs2, temp, 1.0f, 1.0f);
            break;

        case 1:
            Lib_TextureRect_IA8(&gMasterDisp, gTitlePeppyCard, 120, 13, temp_fs2, temp, 1.0f, 1.0f);
            break;

        case 2:
            Lib_TextureRect_IA8(&gMasterDisp, gTitleFalcoCard, 176, 13, temp_fs2, temp, 1.0f, 1.0f);
            break;

        case 3:
            Lib_TextureRect_IA8(&gMasterDisp, gTitleFoxCard, 176, 13, temp_fs2, temp, 1.0f, 1.0f);
            break;
    }
}

Gfx* D_menu_801AE48C[12] = {
    D_TITLE_6036290, D_TITLE_6036290, D_TITLE_6036290, D_TITLE_6036290, D_TITLE_6036B30, D_TITLE_6036290,
    D_TITLE_6036290, D_TITLE_6036290, D_TITLE_6036290, D_TITLE_6036290, D_TITLE_6036B30, D_TITLE_6036290,
};

f32 D_menu_801AE4BC[12] = {
    0.0f, 0.0f, 0.0f, 0.0f, 10.0f, 13.0f, 20.0f, 35.0f, 40.0f, 50.0f, 50.0f, 70.0f,
};

f32 D_menu_801AE4EC[] = {
    20.0f, 22.0f, 24.0f, 28.0f, 30.0f, 14.0f, 16.0f, 18.0f, 27.0f, 28.0f, 70.0f, 40.0f,
};

u8 D_menu_801AE51C[] = {
    0xC0, 0x80, 0x60, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
};

s32 D_menu_801AE528[] = {
    80, 64, 48, 32, 12, 32, 44, 32, 42, 36, 12, 38,
};

void Title_SunGlare_Draw(void) {
    if (D_menu_801B7BD8 != 0) {
        if ((D_menu_801B7BB8 > -870.0f) && (D_menu_801B7BB8 < 900.0f) && (gFillScreenAlpha > 0)) {
            if ((D_menu_801B7BB8 < 0.0f) && (D_menu_801B7BD0 < 255)) {
                D_menu_801B7BD0 += 2;
            }
            if ((D_menu_801B7BB8 > 0.0f) && (D_menu_801B7BD0 > 0)) {
                D_menu_801B7BD0 -= 2;
            }

            RCP_SetupDL(&gMasterDisp, SETUPDL_83_POINT);

            gDPSetAlphaDither(gMasterDisp++, G_AD_NOISE);
            gDPSetColorDither(gMasterDisp++, G_CD_NOISE);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, D_menu_801B7BD0);

            Lib_TextureRect_RGBA16(&gMasterDisp, aTitleSunGlareTex, 32, 32, D_menu_801B9080, D_menu_801B9084,
                                   D_menu_801B7BB0, D_menu_801B7BB4);
            D_menu_801B9080 += 1.66f;
        }

        Title_Matrix_Push();
        Title_Sun_Draw();
        Title_SunGlare2_Draw();

        Matrix_Pop(&gGfxMatrix);
    }
}

void Title_Sun_Draw(void) {
    s32 i;

    if (gFillScreenAlpha > 0) {
        gFillScreenAlpha -= 4;
    }

    gSunViewX = D_menu_801B7BB8;
    gSunViewY = D_menu_801B7BBC;

    if (gSunViewX < 950.0f) {
        if (gSunViewX > -900.0f) {
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
        RCP_SetupDL(&gMasterDisp, SETUPDL_62);

        gDPSetAlphaDither(gMasterDisp++, G_AD_NOISE);
        gDPSetColorDither(gMasterDisp++, G_CD_NOISE);

        Matrix_Push(&gGfxMatrix);
        Matrix_Translate(gGfxMatrix, gSunViewX, gSunViewY, -200.0f, MTXF_APPLY);

        for (i = 0; i < 4; i++) {
            Matrix_Push(&gGfxMatrix);
            Matrix_Scale(gGfxMatrix, D_menu_801AE4EC[i] * 0.5f, D_menu_801AE4EC[i] * 0.5f, D_menu_801AE4EC[i] * 0.5f,
                         MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);

            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, D_menu_801AE51C[i], D_menu_801AE528[i]);
            gSPDisplayList(gMasterDisp++, D_menu_801AE48C[i]);

            Matrix_Pop(&gGfxMatrix);
        }
        Matrix_Pop(&gGfxMatrix);
    }
}

void Title_SunGlare2_Draw(void) {
    static s32 D_menu_801AE558 = 12;
    f32 temp_fs3;
    f32 temp_fs4;
    f32 var_fs1;
    f32 temp;
    s32 i;

    RCP_SetupDL(&gMasterDisp, SETUPDL_62);

    gDPSetAlphaDither(gMasterDisp++, G_AD_NOISE);
    gDPSetColorDither(gMasterDisp++, G_CD_NOISE);

    if (gFillScreenAlpha > 0) {
        temp_fs3 = gSunViewX * -0.03f;
        temp_fs4 = gSunViewY * 0.03f;

        var_fs1 = 1.0f;
        if (gFillScreenAlpha < 10) {
            var_fs1 = gFillScreenAlpha / 10.0f;
        }

        var_fs1 *= 0.5f;

        Matrix_Push(&gGfxMatrix);
        Matrix_Translate(gGfxMatrix, gSunViewX, gSunViewY, -200.0f, MTXF_APPLY);

        for (i = 4; i < 12; i++) {
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, D_menu_801AE4BC[i] * temp_fs3, -D_menu_801AE4BC[i] * temp_fs4, 0.0f,
                             MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, D_menu_801AE4EC[i] * 0.5f, D_menu_801AE4EC[i] * 0.5f, D_menu_801AE4EC[i] * 0.5f,
                         MTXF_APPLY);

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

// Draws the Starfox and N64 logos
void Title_Logos_Draw(void) {
    s32 i;

    switch (sTitleLogoState) {
        case TITLE_LOGO_STARFOX_IN:
            RCP_SetupDL(&gMasterDisp, SETUPDL_85_POINT);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, (s32) sStarfoxLogoAlpha);
            Lib_TextureRect_CI4(&gMasterDisp, aIntroStarfoxLogoTex, aIntroStarfoxLogoTLUT, 256, 13, 90.0f, 110.0f, 1.0f,
                                1.0f);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, (s32) sInAlpha);
            Lib_TextureRect_CI4(&gMasterDisp, aIntroInTex, aIntroInTLUT, 32, 13, 150.0f, 110.0f, 1.0f, 1.0f);
            break;

        case TITLE_LOGO_NINTENDO_64:
            RCP_SetupDL(&gMasterDisp, SETUPDL_83_POINT);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, (s32) sStarfoxLogoAlpha);
            Lib_TextureRect_RGBA16(&gMasterDisp, aTitleN64LogoTex, 128, 88, D_menu_801B9070, D_menu_801B9074,
                                   D_menu_801B9078, D_menu_801B907C);

        case TITLE_LOGO_NONE:
            break;
    }
}

void Title_GreatFoxDeck_Draw(void) {
    segataSanshiroTimer++;

    // Set up lights and display list
    Lights_SetOneLight(&gMasterDisp, D_menu_801B82E0, D_menu_801B82E4, D_menu_801B82E8, 0, 0, 0, gAmbientR, gAmbientG,
                       gAmbientB);
    RCP_SetupDL(&gMasterDisp, SETUPDL_23);

    Matrix_Push(&gGfxMatrix);

    // @port: Tag the transform.
    FrameInterpolation_RecordOpenChild("TAG_GREATFOXDECK", 0);

    Matrix_Translate(gGfxMatrix, 0.0f, D_menu_801B9048, D_menu_801B904C, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, 0.4f, 0.4f, 0.4f, MTXF_APPLY);

    Matrix_SetGfxMtx(&gMasterDisp);

    // Draw the original display list
    gSPDisplayList(gMasterDisp++, aTitleGreatFoxDeckDL);

    // Apply scaling for mirroring
    Matrix_Push(&gGfxMatrix);                                // Push current matrix state
    Matrix_Scale(gGfxMatrix, -1.0f, 1.0f, 1.0f, MTXF_APPLY); // Mirror the display list horizontally
    Matrix_Translate(gGfxMatrix, -800.0f, 0.0f, 0.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);

    // Invert the culling mode for the mirrored geometry
    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK); // Clear normal backface culling
    gSPSetGeometryMode(gMasterDisp++, G_CULL_FRONT);  // Enable front-face culling (inverted culling)

    if (segataSanshiroTimer > 50) {
        // Draw the mirrored display list
        gSPDisplayList(gMasterDisp++, aTitleGreatFoxDeckDL);
    }
    // Restore culling mode
    gSPClearGeometryMode(gMasterDisp++, G_CULL_FRONT); // Clear front-face culling (inverted)
    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);    // Re-enable normal backface culling

    Matrix_Pop(&gGfxMatrix); // Restore original matrix state

    Title_GreatFoxDeckPlatform_Draw();

    Matrix_Pop(&gGfxMatrix); // Restore original transformation

    // @port Pop the transform id.
    FrameInterpolation_RecordCloseChild();
}

void Title_GreatFoxDeckPlatform_Draw(void) {
    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
    Matrix_Translate(gGfxMatrix, 400.0f, -250.0f, 0.0f, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 1.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, aTitleGreatFoxDeckPlatformDL);
    Matrix_Translate(gGfxMatrix, 400.0f - 400.0f, -250.0f + 250.0f, 500.0f, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 1.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, aTitleGreatFoxDeckPlatformDL);
    Matrix_Translate(gGfxMatrix, 400.0f - 400.0f, -250.0f + 250.0f, -1000.0f, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 1.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, aTitleGreatFoxDeckPlatformDL);
    Matrix_Translate(gGfxMatrix, 400.0f - 400.0f, -250.0f + 250.0f, -500.0f, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 1.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, aTitleGreatFoxDeckPlatformDL);

    // reuse same DLs to complete the other side of the platform

    Matrix_Translate(gGfxMatrix, -100.0f, -110.0f, 0.0f, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, 1.0f, -1.0f, 1.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, aTitleGreatFoxDeckPlatformDL);

    Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, 500.0f, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 1.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, aTitleGreatFoxDeckPlatformDL);

    Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, 500.0f, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 1.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, aTitleGreatFoxDeckPlatformDL);

    Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, 500.0f, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 1.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, aTitleGreatFoxDeckPlatformDL);
}

void Title_GreatFoxDeckLauncher_Draw(TitleTeam teamidx) {
    Lights_SetOneLight(&gMasterDisp, D_menu_801B82E0, D_menu_801B82E4, D_menu_801B82E8, gLight1R, gLight1G, gLight1B,
                       gAmbientR, gAmbientG, gAmbientB);
    RCP_SetupDL(&gMasterDisp, SETUPDL_23);

    Matrix_Push(&gGfxMatrix);

    // @port: Tag the transform.
    FrameInterpolation_RecordOpenChild("Title_GreatFoxDeckLauncher_Draw", teamidx);

    Matrix_Translate(gGfxMatrix, sTitleArwing[teamidx].pos.x, -12.8f, sTitleDeckLauncherZpos, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, 0.8f, 0.8f, 0.8f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);

    gSPDisplayList(gMasterDisp++, aTitleGreatFoxDeckLauncherDL);

    Matrix_Pop(&gGfxMatrix);

    // @port Pop the transform id.
    FrameInterpolation_RecordCloseChild();
}

void Title_TitleCard_Draw(void) {
    s32 i;
    static f32 aTitleGreatFoxCardXpos = 89.0f;
    static f32 aTitleGreatFoxCardYpos = 17.0f;
    static f32 sTitleArwingCardXpos = 101.0f;
    static f32 sTitleArwingCardYpos = 197.0f;

    switch (sTitleCardState) {
        case TITLE_CARD_NONE:
            break;

        case TITLE_CARD_GREAT_FOX:
            RCP_SetupDL(&gMasterDisp, SETUPDL_83_POINT);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
            Lib_TextureRect_IA8(&gMasterDisp, aTitleGreatFoxCardTex, 144, 28, aTitleGreatFoxCardXpos,
                                aTitleGreatFoxCardYpos, 1.0f, 1.0f);
            break;

        case TITLE_CARD_ARWING:
            RCP_SetupDL(&gMasterDisp, SETUPDL_83_POINT);
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);

            Lib_TextureRect_IA8(&gMasterDisp, aTitleArwingCardTex, 112, 26, sTitleArwingCardXpos, sTitleArwingCardYpos,
                                1.0f, 1.0f);
    }
}

// Redirect to either Title Screen or Option menu
void Title_NextState_Check(void) {
    if (sCutsceneState == TITLE_SCREEN) {
        Title_NextState_OptionMenu();
    } else {
        Title_NextState_TitleScreen();
    }
}

void Title_NextState_TitleScreen(void) {
    switch (sLevelStartState) {
        case 0: // Wait for input
            if (gControllerPress[gMainController].button &
                (START_BUTTON | A_BUTTON | B_BUTTON | D_CBUTTONS | L_CBUTTONS | U_CBUTTONS | R_CBUTTONS)) {
                AUDIO_PLAY_SFX(NA_SE_DECIDE, gDefaultSfxSource, 4);
                sWipeHeight = 0;
                sLevelStartState = 1;
                gControllerLock = 30;
            }
            break;

        case 1: // Go to the title screen
            if (sWipeHeight < 120) {
                sWipeHeight += 18;
            } else {
                AUDIO_SET_SPEC(SFXCHAN_0, AUDIOSPEC_23);
                gStarCount = 0;
                gRadioState = 0;
                sSceneState = 0;
                gDrawMode = DRAW_NONE;
                sCutsceneState = TITLE_SCREEN;
                gControllerLock = 30;
                sWipeHeight = 0;
                sLevelStartState = 0;
            }
            break;
    }
}

void Title_NextState_OptionMenu(void) {
    if (gControllerLock == 0) {
        switch (sLevelStartState) {
            case 0: // Wait for input
                if (((gControllerPress[gMainController].button & START_BUTTON) ||
                     (gControllerPress[gMainController].button & A_BUTTON)) &&
                    !sLevelStartState) {
                    AUDIO_PLAY_SFX(NA_SE_DECIDE, gDefaultSfxSource, 4);
                    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 30);
                    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 30);
                    sWipeHeight = 0;
                    sLevelStartState = 1;
                }
                break;

            case 1: // Go to the Option Menu
                if (sWipeHeight < 120) {
                    sWipeHeight += 18;
                } else {
                    if (CVarGetInteger("gDebugEnding", 0) == 1) {
                        gGameState = GSTATE_ENDING;
                        gGreatFoxIntact = 1;
                        gLeveLClearStatus[LEVEL_ZONESS] = 1;
                        gLeveLClearStatus[LEVEL_KATINA] = 1;
                    } else {
                        gGameState = GSTATE_MENU;
                    }
                    gNextGameStateTimer = 2;
                    gOptionMenuStatus = OPTION_WAIT;
                    gDrawMode = DRAW_NONE;
                    gStarCount = 0;
                    sLevelStartState = 0;
                    sWipeHeight = 0;
                    gControllerLock = 3;
                }
                break;
        }
    }
}

void Title_Screen_Input(void) {
    f32 stickX;
    f32 stickY;

    if ((D_menu_801B82B0 == 0) && !D_menu_801B9040 &&
        ((gControllerPress[gMainController].stick_x != 0) || (gControllerPress[gMainController].stick_y != 0))) {
        D_menu_801B9040 = true;
        D_menu_801B86A4 = false;
    }

    stickX = gControllerPress[gMainController].stick_x;
    stickY = gControllerPress[gMainController].stick_y;

    if (D_menu_801B9040) {
        if (((D_menu_801B905C + (stickX * 0.2f)) > -500.0f) && ((D_menu_801B905C + (stickX * 0.2f)) < 500.0f)) {
            D_menu_801B905C += stickX * 0.2f;
        }
        if (((D_menu_801B9060 + (stickY * 0.2f)) > -500.0f) && ((D_menu_801B9060 + (stickY * 0.2f)) < 500.0f)) {
            D_menu_801B9060 += stickY * 0.2f;
        }
    }

    if (D_menu_801B9040 && (gControllerPress[gMainController].stick_x == 0) &&
        (gControllerPress[gMainController].stick_y == 0)) {
        D_menu_801B86A4++;
    } else {
        D_menu_801B86A4 = 0;
    }
}

void Title_ScreenFade_Update(void) {
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

void Title_SetCamUp3(bool arg0, f32* arg1, f32* arg2, f32* arg3, f32* arg4, f32* arg5, f32* arg6, f32 arg7, f32 arg8,
                     f32 arg9) {
    Vec3f sp54;
    Vec3f sp48;
    f32* sp44;
    f32* sp40;
    f32* sp3C;
    f32* var_t0;
    f32* var_v0;
    f32* var_v1;

    if (arg0) {
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

    Matrix_Translate(gCalcMatrix, *var_v0, *var_v1, *var_t0, MTXF_NEW);
    Matrix_RotateY(gCalcMatrix, M_DTOR * arg8, MTXF_APPLY);
    Matrix_RotateX(gCalcMatrix, M_DTOR * arg7, MTXF_APPLY);
    Matrix_MultVec3f(gCalcMatrix, &sp48, &sp54);

    *sp44 = sp54.x;
    *sp40 = sp54.y;
    *sp3C = sp54.z;

    sp48.x = 0.0f;
    sp48.y = 1.0f;
    sp48.z = 0.0f;

    Matrix_RotateY(gCalcMatrix, M_DTOR * arg8, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, M_DTOR * arg7, MTXF_APPLY);
    Matrix_MultVec3f(gCalcMatrix, &sp48, &sp54);

    sTitleCamUpX = sp54.x;
    sTitleCamUpY = sp54.y;
    sTitleCamUpZ = sp54.z;
}

void Title_SetCamUp2(f32 arg0, f32 arg1, f32 arg2, f32* arg3, f32* arg4, f32* arg5, f32 arg6, f32* arg7, f32* arg8,
                     f32* arg9, f32 argA, f32 argB, f32 argC) {
    Vec3f dest;
    Vec3f src;

    src.x = 0.0f;
    src.y = 0.0f;
    src.z = argA;

    Matrix_Translate(gCalcMatrix, arg0, arg1, arg2, MTXF_NEW);

    Matrix_RotateY(gCalcMatrix, M_DTOR * argC, MTXF_APPLY);
    Matrix_RotateX(gCalcMatrix, M_DTOR * argB, MTXF_APPLY);

    Matrix_MultVec3f(gCalcMatrix, &src, &dest);

    *arg7 = dest.x;
    *arg8 = dest.y;
    *arg9 = dest.z;

    src.x = 0.0f;
    src.y = 0.0f;
    src.z = arg6;

    Matrix_Translate(gCalcMatrix, arg0, arg1, arg2, MTXF_NEW);
    Matrix_RotateY(gCalcMatrix, M_DTOR * argC, MTXF_APPLY);
    Matrix_RotateX(gCalcMatrix, M_DTOR * argB, MTXF_APPLY);
    Matrix_MultVec3f(gCalcMatrix, &src, &dest);

    *arg3 = dest.x;
    *arg4 = dest.y;
    *arg5 = dest.z;

    src.x = 0.0f;
    src.y = 1.0f;
    src.z = 0.0f;

    Matrix_RotateY(gCalcMatrix, M_DTOR * argC, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, M_DTOR * argB, MTXF_APPLY);
    Matrix_MultVec3f(gCalcMatrix, &src, &dest);

    sTitleCamUpX = dest.x;
    sTitleCamUpY = dest.y;
    sTitleCamUpZ = dest.z;
}

void Title_SetLightRot(f32 xRot, f32 yRot, f32 zSrc, f32* dirX, f32* dirY, f32* dirZ) {
    f32 xRotTarget;
    f32 yRotTarget;
    Vec3f dest;
    Vec3f src;

    src.x = 0.0f;
    src.y = 0.0f;
    src.z = zSrc;

    Title_GetCamRot(&xRotTarget, &yRotTarget);

    Matrix_RotateX(gCalcMatrix, M_DTOR * -xRotTarget, MTXF_NEW);
    Matrix_RotateY(gCalcMatrix, M_DTOR * -yRotTarget, MTXF_APPLY);
    Matrix_RotateY(gCalcMatrix, M_DTOR * yRot, MTXF_APPLY);
    Matrix_RotateX(gCalcMatrix, M_DTOR * xRot, MTXF_APPLY);

    Matrix_MultVec3f(gCalcMatrix, &src, &dest);

    *dirX = dest.x;
    *dirY = dest.y;
    *dirZ = dest.z;
}

void Title_GetCamRot(f32* xRot, f32* yRot) {
    f32 x = gCsCamEyeX - gCsCamAtX;
    f32 y = gCsCamEyeY - gCsCamAtY;
    f32 z = gCsCamEyeZ - gCsCamAtZ;

    *xRot = -Math_Atan2F(y, sqrtf(SQ(x) + SQ(z))) * M_RTOD;
    *yRot = +Math_Atan2F(x, z) * M_RTOD;
}

void Title_SetCamUp(f32 xRot, f32 yRot) {
    Vec3f dest;
    Vec3f src;

    src.x = 0.0f;
    src.y = 1.0f;
    src.z = 0.0f;

    Matrix_RotateY(gCalcMatrix, M_DTOR * yRot, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, M_DTOR * xRot, MTXF_APPLY);

    Matrix_MultVec3f(gCalcMatrix, &src, &dest);

    sTitleCamUpX = dest.x;
    sTitleCamUpY = dest.y;
    sTitleCamUpZ = dest.z;
}

void Title_Matrix_Push(void) {
    Matrix_Push(&gGfxMatrix);
    Matrix_LookAt(gGfxMatrix, gCsCamEyeX, gCsCamEyeY, gCsCamEyeZ, gCsCamAtX, gCsCamAtY, gCsCamAtZ, sTitleCamUpX,
                  sTitleCamUpY, sTitleCamUpZ, MTXF_APPLY);
    Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, 0.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
}

void Title_Radio_PlayMessage(u16** msgList, RadioCharacterId character) {
    gRadioMsgList = msgList;
    gRadioMsgListIndex = 0;
    gRadioMsg = SEGMENTED_TO_VIRTUAL(msgList[gRadioMsgListIndex]);
    gRadioMsgId = 10 * (gRadioMsgListIndex + 1);
    gRadioMsgRadioId = character;
    gRadioState = 100;

    switch (gGameState) {
        case GSTATE_TITLE:
            gRadioPrintPosY = 176;
            gRadioPrintPosX = OTRGetRectDimensionFromLeftEdge(85);
            gRadioTextBoxPosX = OTRGetRectDimensionFromLeftEdge(80.0f);
            gRadioTextBoxPosY = 174.0f;
            gRadioTextBoxScaleX = 4.63f;
            gRadioPortraitPosX = OTRGetRectDimensionFromLeftEdge(32.0f);
            gRadioPortraitPosY = 174.0f;
            break;

        case GSTATE_PLAY:
            gRadioPrintPosY = 179;
            gRadioPrintPosX = OTRGetRectDimensionFromLeftEdge(79);
            gRadioTextBoxPosX = OTRGetRectDimensionFromLeftEdge(74.0f);
            gRadioTextBoxPosY = 178.0f;
            gRadioTextBoxScaleX = 4.53f;
            gRadioPortraitPosX = OTRGetRectDimensionFromLeftEdge(26.0f);
            gRadioPortraitPosY = 178.0f;
    }

    Audio_PlayVoice(Message_IdFromPtr(gRadioMsg));
}
