#include "prevent_bss_reordering.h"
#include "global.h"
#include "sf64dma.h"
#include "assets/ast_logo.h"
#include "mods.h"
#include "port/interpolation/FrameInterpolation.h"
#include "port/hooks/list/EngineEvent.h"
#include "port/mods/PortEnhancements.h"

f32 gNextVsViewScale;
f32 gVsViewScale;
s32 gPlayerInactive[4];
s32 gVsMenuSelection;
u8 gShowHud;
u16 gNextLevelPhase;
u16 gNextLevel;
u16 gNextGameState;
u16 gLastGameState;
u16 gBgColor;
u8 gBlurAlpha;
u8 gGameStandby;
f32 gFovY;
f32 gProjectNear;
f32 gProjectFar;

bool gShowReticles[4] = { true, true, true, true };
bool D_game_800D2870 = false;
s32 sVsCameraULx[] = { 0, SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2 };
s32 sVsCameraLRx[] = { SCREEN_WIDTH / 2 - 1, SCREEN_WIDTH - 1, SCREEN_WIDTH / 2 - 1, SCREEN_WIDTH - 1 };
s32 sVsCameraULy[] = { 0, 0, SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 2 };
s32 sVsCameraLRy[] = { SCREEN_HEIGHT / 2 - 1, SCREEN_HEIGHT / 2 - 1, SCREEN_HEIGHT - 1, SCREEN_HEIGHT - 1 };
s32 sLevelSceneIds[] = {
    /* LEVEL_CORNERIA */ SCENE_CORNERIA,
    /* LEVEL_METEO */ SCENE_METEO,
    /* LEVEL_SECTOR_X */ SCENE_SECTOR_X,
    /* LEVEL_AREA_6 */ SCENE_AREA_6,
    /* LEVEL_UNK_4 */ SCENE_UNK_4,
    /* LEVEL_SECTOR_Y */ SCENE_SECTOR_Y,
    /* LEVEL_VENOM_1 */ SCENE_VENOM_1,
    /* LEVEL_SOLAR */ SCENE_SOLAR,
    /* LEVEL_ZONESS */ SCENE_ZONESS,
    /* LEVEL_VENOM_ANDROSS */ SCENE_VENOM_ANDROSS,
    /* LEVEL_TRAINING */ SCENE_TRAINING,
    /* LEVEL_MACBETH */ SCENE_MACBETH,
    /* LEVEL_TITANIA */ SCENE_TITANIA,
    /* LEVEL_AQUAS */ SCENE_AQUAS,
    /* LEVEL_FORTUNA */ SCENE_FORTUNA,
    /* LEVEL_UNK_15 */ SCENE_TITLE,
    /* LEVEL_KATINA */ SCENE_KATINA,
    /* LEVEL_BOLSE */ SCENE_BOLSE,
    /* LEVEL_SECTOR_Z */ SCENE_SECTOR_Z,
    /* LEVEL_VENOM_2 */ SCENE_VENOM_2,
    /* LEVEL_VERSUS */ SCENE_VERSUS,
};

void Game_Initialize(void) {
    Memory_FreeAll();
    Rand_Init();
    Rand_SetSeed(1, 29000, 9876);
    gGameState = GSTATE_BOOT;
#ifdef MODS_BOOT_STATE
    gNextGameState = GSTATE_INIT;
    if (Save_Read() != 0) {
#ifdef AVOID_UB
        gSaveFile.save = gDefaultSave;
        gSaveFile.backup = gDefaultSave;
#else
        gSaveFile = *((SaveFile*) &gDefaultSave);
#endif
        Save_Write();
    }
#endif
    gNextGameStateTimer = 0;
    gBgColor = 0;
    gBlurAlpha = 255;
    gFovY = 45.0f;
    gProjectNear = 10.0f;
    gProjectFar = 12800.0f;
    gNextVsViewScale = gVsViewScale = 0.0f;
    gSceneId = SCENE_LOGO;
    gSceneSetup = 0;
    Load_InitDmaAndMsg();
    gGameStandby = true;
}

void Game_SetGameState(void) {
    gVsViewScale = gNextVsViewScale;

    if (gNextGameState == GSTATE_NONE) {
        return;
    }

    switch (gNextGameState) {
        case GSTATE_PLAY:
            gCurrentLevel = gNextLevel;
            Play_Setup();
            gPlayState = PLAY_STANDBY;
            gLevelPhase = gNextLevelPhase;
            gNextLevelPhase = 0;
            if ((gLevelPhase != 0) && (gCurrentLevel != LEVEL_VENOM_ANDROSS)) {
                D_ctx_8017782C = false;
            }
            break;
        case GSTATE_MAP:
            gMapState = 0;
            break;
        case GSTATE_GAME_OVER:
            D_ctx_80177868 = 0;
            break;
    }
    Memory_FreeAll();
    Play_ClearObjectData();
    gGameState = gNextGameState;
    gNextGameStateTimer = 3;
    gAllRangeCheckpoint = 0;
    gNextGameState = GSTATE_NONE;
    gSceneSetup = 0;
    gFillScreenColor = gBgColor = 0;
    gPathProgress = 0.0f;
    if ((gCurrentLevel == LEVEL_VENOM_2) && (gLevelPhase == 2)) {
        gFillScreenColor = gBgColor = 0xFFFF; // 248, 248, 248
        gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
    } else {
        gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
        Audio_FadeOutAll(1);
    }
    gFillScreenAlpha = 255;
    gPlayerGlareAlphas[0] = 0;
    gRadioState = 0;
    gStarfieldRoll = 0.0f;
    gBlurAlpha = 255;
    gDrawMode = DRAW_NONE;
    Audio_ClearVoice();
    Audio_SetEnvSfxReverb(0);
}

bool Game_ChangeScene(void) {
    static u8 sHoldTimer = 0;
    static u8 sSceneSelect = SCENE_LOGO;
    static u8 sCurrentSceneId = SCENE_LOGO;
    static u8 sCurrentSetup = SCENE_LOGO;

    if (gSceneId != sCurrentSceneId) {
        sHoldTimer = 2;
        sCurrentSceneId = gSceneId;
    }
    if (sHoldTimer == 0) {
        sSceneSelect = sCurrentSceneId;
        sCurrentSetup = gSceneSetup;
    }
    Load_SceneSetup(sSceneSelect, sCurrentSetup);

    if (sHoldTimer) {
        sHoldTimer--;
        return true;
    }
    return false;
}

#define LEFT_MARGIN OTRGetRectDimensionFromLeftEdge(SCREEN_MARGIN)
#define RIGHT_MARGIN OTRGetRectDimensionFromRightEdge(SCREEN_WIDTH - SCREEN_MARGIN)

void Game_InitMasterDL(Gfx** dList) {
    gSPDisplayList((*dList)++, gRcpInitDL);
    gDPSetScissor((*dList)++, G_SC_NON_INTERLACE, SCREEN_MARGIN, SCREEN_MARGIN, SCREEN_WIDTH - SCREEN_MARGIN,
                  SCREEN_HEIGHT - SCREEN_MARGIN);
    gDPSetDepthImage((*dList)++, &gZBuffer);
    gDPSetColorImage((*dList)++, G_IM_FMT_RGBA, G_IM_SIZ_16b, RIGHT_MARGIN, &gZBuffer);
    gDPSetFillColor((*dList)++, FILL_COLOR(GPACK_ZDZ(G_MAXFBZ, 0)));
    gDPFillWideRectangle((*dList)++, LEFT_MARGIN, SCREEN_MARGIN, RIGHT_MARGIN, SCREEN_HEIGHT - SCREEN_MARGIN);
    gDPSetColorImage((*dList)++, G_IM_FMT_RGBA, G_IM_SIZ_16b, RIGHT_MARGIN, gFrameBuffer);

    if (gBlurAlpha < 255) {
        gDPPipeSync((*dList)++);
        gDPSetCycleType((*dList)++, G_CYC_1CYCLE);
        gDPSetCombineMode((*dList)++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
        gDPSetRenderMode((*dList)++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetPrimColor((*dList)++, 0x00, 0x00, RGBA16_RED(gBgColor) * 8, RGBA16_GRN(gBgColor) * 8,
                        RGBA16_BLU(gBgColor) * 8, gBlurAlpha);
    } else {
        gDPSetFillColor((*dList)++, FILL_COLOR(gBgColor | 1));
    }
    gDPFillWideRectangle((*dList)++, LEFT_MARGIN, SCREEN_MARGIN, RIGHT_MARGIN, SCREEN_HEIGHT - SCREEN_MARGIN);
    gDPPipeSync((*dList)++);
    gDPSetColorDither((*dList)++, G_CD_MAGICSQ);
}

void Game_InitStandbyDL(Gfx** dList) {
    gSPDisplayList((*dList)++, gRcpInitDL);
    gDPSetScissor((*dList)++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT * 3);
    gDPSetFillColor((*dList)++, FILL_COLOR(0x0001));
    gDPSetColorImage((*dList)++, G_IM_FMT_RGBA, G_IM_SIZ_16b, RIGHT_MARGIN, gFrameBuffers[0].data);
    gDPFillWideRectangle((*dList)++, OTRGetDimensionFromLeftEdge(0), 0, OTRGetRectDimensionFromRightEdge(0),
                         SCREEN_HEIGHT * 3 - 1);
    gDPPipeSync((*dList)++);
    gDPSetColorDither((*dList)++, G_CD_MAGICSQ);
}

void Game_InitFullViewport(void) {
    gViewport->vp.vscale[0] = gViewport->vp.vtrans[0] = SCREEN_WIDTH * 2;
    gViewport->vp.vscale[1] = gViewport->vp.vtrans[1] = SCREEN_HEIGHT * 2;
    gViewport->vp.vscale[2] = gViewport->vp.vtrans[2] = G_MAXZ / 2;
    gViewport->vp.vscale[3] = gViewport->vp.vtrans[3] = 0;
}

void Game_InitViewport(Gfx** dList, u8 camCount, u8 camIndex) {
    switch (camCount) {
        case 4:
            switch (camIndex) {
                case 0:
                    gViewport->vp.vscale[0] = SCREEN_WIDTH * (gVsViewScale - 1.0f) * 2;
                    gViewport->vp.vscale[1] = SCREEN_HEIGHT * (gVsViewScale - 1.0f) * 2;
                    gViewport->vp.vscale[2] = G_MAXZ / 2;
                    gViewport->vp.vscale[3] = 0;
                    gViewport->vp.vtrans[0] = SCREEN_WIDTH * (2.0f - gVsViewScale) * 2;
                    gViewport->vp.vtrans[1] = SCREEN_HEIGHT * (2.0f - gVsViewScale) * 2;
                    gViewport->vp.vtrans[2] = G_MAXZ / 2;
                    gViewport->vp.vtrans[3] = 0;
                    gDPSetScissor((*dList)++, G_SC_NON_INTERLACE, SCREEN_MARGIN, SCREEN_MARGIN, SCREEN_WIDTH / 2,
                                  SCREEN_HEIGHT / 2);
                    break;
                case 1:
                    gViewport->vp.vscale[0] = SCREEN_WIDTH * (gVsViewScale - 1.0f) * 2;
                    gViewport->vp.vscale[1] = SCREEN_HEIGHT * (gVsViewScale - 1.0f) * 2;
                    gViewport->vp.vscale[2] = G_MAXZ / 2;
                    gViewport->vp.vscale[3] = 0;
                    gViewport->vp.vtrans[0] = SCREEN_WIDTH * gVsViewScale * 2;
                    gViewport->vp.vtrans[1] = SCREEN_HEIGHT * (2.0f - gVsViewScale) * 2;
                    gViewport->vp.vtrans[2] = G_MAXZ / 2;
                    gViewport->vp.vtrans[3] = 0;
                    gDPSetScissor((*dList)++, G_SC_NON_INTERLACE, SCREEN_WIDTH / 2, SCREEN_MARGIN,
                                  SCREEN_WIDTH - SCREEN_MARGIN, SCREEN_HEIGHT / 2);
                    break;
                case 2:
                    gViewport->vp.vscale[0] = SCREEN_WIDTH * (gVsViewScale - 1.0f) * 2;
                    gViewport->vp.vscale[1] = SCREEN_HEIGHT * (gVsViewScale - 1.0f) * 2;
                    gViewport->vp.vscale[2] = G_MAXZ / 2;
                    gViewport->vp.vscale[3] = 0;
                    gViewport->vp.vtrans[0] = SCREEN_WIDTH * (2.0f - gVsViewScale) * 2;
                    gViewport->vp.vtrans[1] = SCREEN_HEIGHT * gVsViewScale * 2;
                    gViewport->vp.vtrans[2] = G_MAXZ / 2;
                    gViewport->vp.vtrans[3] = 0;
                    gDPSetScissor((*dList)++, G_SC_NON_INTERLACE, SCREEN_MARGIN, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2,
                                  SCREEN_HEIGHT - SCREEN_MARGIN);
                    break;
                case 3:
                    gViewport->vp.vscale[0] = SCREEN_WIDTH * (gVsViewScale - 1.0f) * 2;
                    gViewport->vp.vscale[1] = SCREEN_HEIGHT * (gVsViewScale - 1.0f) * 2;
                    gViewport->vp.vscale[2] = G_MAXZ / 2;
                    gViewport->vp.vscale[3] = 0;
                    gViewport->vp.vtrans[0] = SCREEN_WIDTH * gVsViewScale * 2;
                    gViewport->vp.vtrans[1] = SCREEN_HEIGHT * gVsViewScale * 2;
                    gViewport->vp.vtrans[2] = G_MAXZ / 2;
                    gViewport->vp.vtrans[3] = 0;
                    gDPSetScissor((*dList)++, G_SC_NON_INTERLACE, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
                                  SCREEN_WIDTH - SCREEN_MARGIN, SCREEN_HEIGHT - SCREEN_MARGIN);
                    break;
                default:
                    Game_InitFullViewport();
                    break;
            }
            break;
        case 1:
        default:
            Game_InitFullViewport();
            break;
    }
    gSPViewport((*dList)++, gViewport++);
}

void Game_Draw(s32 playerNum) {
    FrameInterpolation_StartRecord();
    switch (gDrawMode) {
        case DRAW_NONE:
            break;
        case DRAW_TITLE:
            Background_DrawStarfield();
            OvlMenu_CallFunction(OVLCALL_TITLE_DRAW, NULL);
            break;
        case DRAW_OPTION:
            Background_DrawStarfield();
            OvlMenu_CallFunction(OVLCALL_OPTION_DRAW, NULL);
            break;
        case DRAW_MAP:
            Background_DrawStarfield();
            OvlMenu_CallFunction(OVLCALL_MAP_DRAW, NULL);
            break;
        case DRAW_PLAY:
            gPlayerNum = playerNum;
            Display_Update();
            break;
        case DRAW_UNK_MAP: // likely game over
            Background_DrawStarfield();
            OvlMenu_CallFunction(OVLCALL_UNKMAP_DRAW, NULL);
            break;
        case DRAW_UNK_VS:
            func_versus_800C2190();
            break;
        case DRAW_UNK_7:
            gPlayerNum = playerNum;
            func_pause_800A3CA0();
            break;
        case DRAW_ENDING:
            Background_DrawStarfield();
            gPlayerNum = playerNum;
            Ending_Draw();
            break;
    }
    FrameInterpolation_StopRecord();
}

void Game_SetScene(void) {
    switch (gGameState) {
        case GSTATE_INIT:
            gSceneId = SCENE_TITLE;
            gSceneSetup = 0;
            break;
        case GSTATE_TITLE:
            gSceneId = SCENE_TITLE;
            gSceneSetup = 0;
            break;
        case GSTATE_MENU:
            gSceneId = SCENE_MENU;
            gSceneSetup = 0;
            break;
        case GSTATE_MAP:
            gSceneId = SCENE_MAP;
            gSceneSetup = 0;
            return;
        case GSTATE_VS_INIT:
            gSceneId = SCENE_VERSUS;
            break;
        case GSTATE_PLAY:
            gSceneId = sLevelSceneIds[gCurrentLevel];
            break;
        case GSTATE_GAME_OVER:
            gSceneId = SCENE_GAME_OVER;
            gSceneSetup = 0;
            break;
        case GSTATE_ENDING:
            gSceneId = SCENE_CREDITS;
            break;
    }
}

void Game_Update(void) {
    s32 i;
    u8 partialFill;
    u8 soundMode;

    // @port: @event: Call GamePreUpdateEvent
    CALL_EVENT(GamePreUpdateEvent);

    Game_SetGameState();
    if (gGameStandby) {
        Game_InitStandbyDL(&gUnkDisp1);
        gGameStandby = false;
        return;
    }

    Game_InitMasterDL(&gUnkDisp1);
    Game_SetScene();

    if (Game_ChangeScene() != true) {
        Lib_InitPerspective(&gUnkDisp1);
        Game_InitViewport(&gUnkDisp1, gCamCount, 0);

        if (gNextGameStateTimer != 0) {
            gNextGameStateTimer--;
        }

        switch (gGameState) {
            case GSTATE_BOOT:
                gNextGameStateTimer = 2;
                gGameState++;
                break;

            case GSTATE_BOOT_WAIT:
                if (gNextGameStateTimer == 0) {
                    gGameState++;
                }
                break;

            case GSTATE_SHOW_LOGO:
                RCP_SetupDL(&gMasterDisp, SETUPDL_76_OPTIONAL);
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
                Lib_TextureRect_IA8(&gMasterDisp, gNintendoLogo, 128, 74, 100.0f, 86.0f, 1.0f, 1.0f);
                gGameState++;
                break;

            case GSTATE_CHECK_SAVE:
                if (Save_Read() != 0) {
#ifdef AVOID_UB
                    gSaveFile.save = gDefaultSave;
                    gSaveFile.backup = gDefaultSave;
#else
                    gSaveFile = *((SaveFile*) &gDefaultSave);
#endif
                    Save_Write();
                }
                gGameState++;
                Timer_CreateTask(MSEC_TO_CYCLES(1000), Timer_Increment, (s32*) &gGameState, 1);
                /* fallthrough */
            case GSTATE_LOGO_WAIT:
                RCP_SetupDL(&gMasterDisp, SETUPDL_76_OPTIONAL);
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
                Lib_TextureRect_IA8(&gMasterDisp, gNintendoLogo, 128, 74, 100.0f, 86.0f, 1.0f, 1.0f);
                break;

            case GSTATE_START:
                gGameState = GSTATE_INIT;
                gSceneId = SCENE_TITLE;
                gSceneSetup = 0;
                break;

            case GSTATE_INIT:
                gGameState = GSTATE_TITLE;
                gTitleState = 1;
                gClearPlayerInfo = true;
                Memory_FreeAll();
                Play_ClearObjectData();
                gCamCount = 1;
                gLifeCount[0] = 2;
                gPathProgress = 0.0f;
                D_hud_8016170C = gCsFrameCount = gShowLevelClearStatusScreen = gLevelStartStatusScreenTimer =
                    gLevelClearScreenTimer = gVsMatchState = gVersusMode = gTitleState = gStarCount = gMapState =
                        gPlayState = gOptionMenuStatus = gDrawMode = gShowBossHealth = gShowHud = gBgColor =
                            gFillScreenAlpha = 0;
                gNextGameState = D_ctx_80177C94 = D_ctx_80177CAC = D_ctx_80177CB4 = D_ctx_80177CBC = D_ctx_80177CC4 =
                    D_ctx_80177C9C = D_ctx_80177CA4 = D_play_80161A5C = gLastGameState = GSTATE_NONE;
#ifdef MODS_BOOT_STATE
                gNextGameState = MODS_BOOT_STATE;
#endif
                CVarSetFloat("gMainMusicVolume", gSaveFile.save.data.musicVolume / 100.0f);
                CVarSetFloat("gVoiceVolume", gSaveFile.save.data.voiceVolume / 100.0f);
                CVarSetFloat("gSFXMusicVolume", gSaveFile.save.data.sfxVolume / 100.0f);
                for (i = 0; i < 4; i++) {
                    gBoostButton[i] = L_CBUTTONS;
                    gBrakeButton[i] = D_CBUTTONS;
                    gShootButton[i] = A_BUTTON;
                    gBombButton[i] = B_BUTTON;

                    D_ctx_80177958[i] = 1.0f;

                    D_ctx_80177858[i] = 3;
                    gPlayerForms[i] = FORM_ARWING;
                    gShowReticles[i] = true;
                    gPlayerGlareAlphas[i] = 0;
                }

                gVersusStage = 0;
                gVsPointsToWin = 3;
                gBlurAlpha = 255;
                for (i = 0; i < ARRAY_COUNT(gLeveLClearStatus); i++) {
                    gLeveLClearStatus[i] = 0;
                }

                gExpertMode = false;
                gOptionSoundMode = gSaveFile.save.data.soundMode;
                switch (gOptionSoundMode) {
                    case OPTIONSOUND_STEREO:
                        soundMode = SOUNDMODE_STEREO;
                        break;
                    case OPTIONSOUND_MONO:
                        soundMode = SOUNDMODE_MONO;
                        break;
                    case OPTIONSOUND_HEADSET:
                        soundMode = SOUNDMODE_HEADSET;
                        break;
                    default:
                        gOptionSoundMode = OPTIONSOUND_STEREO;
                        soundMode = SOUNDMODE_STEREO;
                        break;
                }
                SEQCMD_SET_SOUND_MODE(soundMode);
                gVolumeSettings[AUDIO_TYPE_MUSIC] = gSaveFile.save.data.musicVolume;
                gVolumeSettings[AUDIO_TYPE_VOICE] = gSaveFile.save.data.voiceVolume;
                gVolumeSettings[AUDIO_TYPE_SFX] = gSaveFile.save.data.sfxVolume;
                if (gVolumeSettings[AUDIO_TYPE_MUSIC] > 99) {
                    gVolumeSettings[AUDIO_TYPE_MUSIC] = 99;
                }
                if (gVolumeSettings[AUDIO_TYPE_VOICE] > 99) {
                    gVolumeSettings[AUDIO_TYPE_VOICE] = 99;
                }
                if (gVolumeSettings[AUDIO_TYPE_SFX] > 99) {
                    gVolumeSettings[AUDIO_TYPE_SFX] = 99;
                }
                Audio_SetVolume(AUDIO_TYPE_MUSIC, gVolumeSettings[AUDIO_TYPE_MUSIC]);
                Audio_SetVolume(AUDIO_TYPE_VOICE, gVolumeSettings[AUDIO_TYPE_VOICE]);
                Audio_SetVolume(AUDIO_TYPE_SFX, gVolumeSettings[AUDIO_TYPE_SFX]);
                break;

            case GSTATE_TITLE:
                OvlMenu_CallFunction(OVLCALL_TITLE_UPDATE, NULL);
                break;
            case GSTATE_MENU:
                OvlMenu_CallFunction(OVLCALL_OPTION_UPDATE, NULL);
                break;
            case GSTATE_MAP:
                Map_Main();
                break;
            case GSTATE_VS_INIT:
                Versus_StartMatch();
                break;
            case GSTATE_PLAY:
                Play_Main();
                break;
            case GSTATE_GAME_OVER:
                OvlMenu_CallFunction(OVLCALL_GAME_OVER_UPDATE, NULL);
                break;
            case GSTATE_ENDING:
                gDrawMode = DRAW_ENDING;
                Ending_Main();
                break;
            default:
                break;
        }

        Game_Draw(0);

        if (gCamCount == 2) {
            Game_InitViewport(&gMasterDisp, gCamCount, 1);
            Game_Draw(1);
            gDPPipeSync(gMasterDisp++);
            gDPSetScissor(gMasterDisp++, G_SC_NON_INTERLACE, SCREEN_MARGIN, SCREEN_MARGIN, SCREEN_WIDTH - SCREEN_MARGIN,
                          SCREEN_HEIGHT - SCREEN_MARGIN);
        } else if ((gCamCount == 4) && (gDrawMode != DRAW_NONE)) {
            Game_InitViewport(&gMasterDisp, gCamCount, 3);
            Game_Draw(3);
            Game_InitViewport(&gMasterDisp, gCamCount, 2);
            Game_Draw(2);
            Game_InitViewport(&gMasterDisp, gCamCount, 1);
            Game_Draw(1);
            gDPPipeSync(gMasterDisp++);
            gDPSetScissor(gMasterDisp++, G_SC_NON_INTERLACE, SCREEN_MARGIN, SCREEN_MARGIN, SCREEN_WIDTH - SCREEN_MARGIN,
                          SCREEN_HEIGHT - SCREEN_MARGIN);
            gDPSetColorDither(gMasterDisp++, G_CD_NOISE);
            gDPSetAlphaDither(gMasterDisp++, G_AD_NOISE);
            gDPSetCycleType(gMasterDisp++, G_CYC_1CYCLE);
            gDPSetCombineMode(gMasterDisp++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
            gDPSetRenderMode(gMasterDisp++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 0, 0, 0, 0);
            gDPFillRectangle(gMasterDisp++, SCREEN_WIDTH / 2 - 2 - 1, SCREEN_MARGIN, SCREEN_WIDTH / 2 + 2,
                             SCREEN_HEIGHT - SCREEN_MARGIN);
            gDPFillRectangle(gMasterDisp++, SCREEN_MARGIN, SCREEN_HEIGHT / 2 - 2 - 1, SCREEN_WIDTH - SCREEN_MARGIN,
                             SCREEN_HEIGHT / 2 + 2);

            if (gLevelType == LEVELTYPE_PLANET) {
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 0, 0, 0, 255);
            } else {
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 100, 100, 255, 255);
            }
            gDPFillRectangle(gMasterDisp++, SCREEN_WIDTH / 2 - 1 - 1, SCREEN_MARGIN, SCREEN_WIDTH / 2 + 1,
                             SCREEN_HEIGHT - SCREEN_MARGIN);
            gDPFillRectangle(gMasterDisp++, SCREEN_MARGIN, SCREEN_HEIGHT / 2 - 1 - 1, SCREEN_WIDTH - SCREEN_MARGIN,
                             SCREEN_HEIGHT / 2 + 1);

            HUD_8008CB8C();
        }

        partialFill = false;

        if (gCamCount == 1) {
            Graphics_FillRectangle(&gMasterDisp, OTRGetRectDimensionFromLeftEdge(0), 0,
                                   OTRGetRectDimensionFromRightEdge(SCREEN_WIDTH - 1), SCREEN_HEIGHT - 1,
                                   gPlayerGlareReds[0], gPlayerGlareGreens[0], gPlayerGlareBlues[0],
                                   gPlayerGlareAlphas[0]);
            if ((gDrawMode == DRAW_PLAY) || (gDrawMode == DRAW_ENDING)) {
                Radio_Draw();
                if (gShowHud) {
                    HUD_Draw();
                    CALL_CANCELLABLE_EVENT(DrawEdgeArrowsHUDEvent){
                        HUD_EdgeArrows_Update();
                    }
                }
                CALL_CANCELLABLE_EVENT(DrawBossHealthHUDEvent){
                    HUD_DrawBossHealth();
                }
            }
        } else {
            for (i = 0; i < gCamCount; i++) {
                if (gPlayer[i].dmgEffectTimer != 0) {

                    Graphics_FillRectangle(&gMasterDisp, sVsCameraULx[i], sVsCameraULy[i], sVsCameraLRx[i],
                                           sVsCameraLRy[i], gFillScreenRed, gFillScreenGreen, gFillScreenBlue,
                                           gFillScreenAlpha);
                    partialFill = true;
                } else {
                    Graphics_FillRectangle(&gMasterDisp, sVsCameraULx[i], sVsCameraULy[i], sVsCameraLRx[i],
                                           sVsCameraLRy[i], gPlayerGlareReds[i], gPlayerGlareGreens[i],
                                           gPlayerGlareBlues[i], gPlayerGlareAlphas[i]);
                }
            }
        }

        Background_dummy_80040CDC();
        HUD_DrawStatusScreens();
        AllRange_DrawCountdown();

        if ((gGameState == GSTATE_PLAY) && gVersusMode) {
            Versus_Draw();
        }

        Wipe_Draw(WIPE_CIRCULAR, gCircleWipeFrame);

        if (!partialFill) {
            Graphics_FillRectangle(&gMasterDisp, OTRGetRectDimensionFromLeftEdge(0), 0,
                                   OTRGetRectDimensionFromRightEdge(SCREEN_WIDTH), SCREEN_HEIGHT,
                                   gFillScreenRed, gFillScreenGreen, gFillScreenBlue, gFillScreenAlpha);
        }
        Audio_dummy_80016A50();

        // @port: @event: Call GamePostUpdateEvent
        CALL_EVENT(GamePostUpdateEvent);
    }
}

#if MODS_FPS_COUNTER == 1
#include "../mods/fpscounter.c"
#endif
#if MODS_RAM_MOD == 1
#include "../mods/object_ram.c"
#endif
#if MODS_SPAWNER == 1
#include "../mods/spawner.c"
#endif

Actor* Game_SpawnActor(ObjectId objId) {
    Actor* actor = &gActors[0];
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gActors); i++, actor++) {
        if (actor->obj.status == OBJ_FREE) {
            Actor_Initialize(actor);
            actor->obj.status = OBJ_INIT;
            actor->obj.id = objId;
            Object_SetInfo(&actor->info, actor->obj.id);
            break;
        }
    }
    if (i == ARRAY_COUNT(gActors)) {
        actor = NULL;
    }
    return actor;
}
