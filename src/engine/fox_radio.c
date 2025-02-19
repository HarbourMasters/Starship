/*
 * File: fox_title.c
 * System: Radio
 * Description: Starfox Radio Handler
 */

#include "prevent_bss_reordering.h"
#include "global.h"
#include "assets/ast_allies.h"
#include "assets/ast_corneria.h"
#include "assets/ast_meteo.h"
#include "assets/ast_training.h"
#include "assets/ast_sector_x.h"
#include "assets/ast_sector_y.h"
#include "assets/ast_macbeth.h"
#include "assets/ast_star_wolf.h"
#include "assets/ast_great_fox.h"
#include "assets/ast_area_6.h"
#include "assets/ast_title.h"
#include "assets/ast_zoness.h"
#include "port/hooks/Events.h"
#include "port/mods/PortEnhancements.h"

u16** gRadioMsgList;
s32 gRadioMsgListIndex;
s32 gRadioPrintPosX;
s32 gRadioPrintPosY;
f32 gRadioTextBoxPosX;
f32 gRadioTextBoxPosY;
f32 gRadioTextBoxScaleX;
f32 gRadioPortraitPosX;
f32 gRadioPortraitPosY;

s32 gRadioMsgPri = 0;

void func_radio_800BA760(void) {
    RCP_SetupDL_36();
    if (gRadioTextBoxScaleY == 1.3f) {
        gMsgCharIsPrinting = Message_IsPrintingChar(gRadioMsg, gRadioMsgCharIndex);
    }
}

s32 func_radio_800BA7BC(u16* msg, s32 priority) {
    if (priority == gRadioMsgPri) {
        return 0;
    }

    if (priority < gRadioMsgPri) {
        return 1;
    }

    if (gRadioMsgPri < priority) {
        gRadioMsgPri = priority;
        return 2;
    }
}

void Radio_PlayMessage(u16* msg, RadioCharacterId character) {
    TeamId teamId;
    s32 pad;
    s32 priority;
    msg = SEGMENTED_TO_VIRTUAL(msg);

    switch (msg[0]) {
        default:
        case MSGCHAR_PRI0:
            priority = 0;
            break;
        case MSGCHAR_PRI1:
            priority = 1;
            break;
        case MSGCHAR_PRI2:
            priority = 2;
            break;
        case MSGCHAR_PRI3:
            priority = 3;
            break;
    }

    if (gGameState == GSTATE_PLAY) {
        if ((character == RCID_FALCO) || (character == RCID_SLIPPY) || (character == RCID_PEPPY)) {
            if (character == RCID_FALCO) {
                teamId = TEAM_ID_FALCO;
            }
            if (character == RCID_SLIPPY) {
                teamId = TEAM_ID_SLIPPY;
            }
            if (character == RCID_PEPPY) {
                teamId = TEAM_ID_PEPPY;
            }
            if ((gTeamShields[teamId] <= 0) && (gTeamShields[teamId] != -2)) {
                return;
            }
        }
    }

    if ((gRadioState != 0) && (func_radio_800BA7BC(msg, priority) == 1)) {
        return;
    }

    gRadioMsgPri = priority;
    gRadioMsgRadioId = character;

    if (gExpertMode && ((character == RCID_FOX) || (character == RCID_FOX_RED))) {
        gRadioMsgRadioId = RCID_FOX_EXPERT;
    }

    if (gCurrentLevel == LEVEL_VENOM_2) {
        switch (character) {
            case RCID_WOLF:
                gRadioMsgRadioId = RCID_WOLF_2;
                break;
            case RCID_PIGMA:
                gRadioMsgRadioId = RCID_PIGMA_2;
                break;
            case RCID_LEON:
                gRadioMsgRadioId = RCID_LEON_2;
                break;
            case RCID_ANDREW:
                gRadioMsgRadioId = RCID_ANDREW_2;
                break;
        }
    }

    gRadioMsg = msg;
    gRadioState = 100;

    gRadioMsgId = Message_IdFromPtr(msg);
    Audio_PlayVoice(gRadioMsgId);
}

void Radio_CalculatePositions(){
        switch (gGameState) {
        case GSTATE_TITLE:
            gRadioPrintPosY = 176;
            gRadioPrintPosX = OTRGetRectDimensionFromLeftEdgeOverride(85.0f);
            gRadioTextBoxPosX = OTRGetRectDimensionFromLeftEdgeOverride(80.0f);
            gRadioTextBoxPosY = 174.0f;
            gRadioTextBoxScaleX = 4.63f;
            gRadioPortraitPosX = OTRGetRectDimensionFromLeftEdgeOverride(32.0f);
            gRadioPortraitPosY = 174.0f;
            break;

        case GSTATE_ENDING:
            gRadioPrintPosY = 176;
            gRadioPrintPosX = 85.0f;
            gRadioTextBoxPosX = 80.0f;
            gRadioTextBoxPosY = 174.0f;
            gRadioTextBoxScaleX = 4.63f;
            gRadioPortraitPosX = 32.0f;
            gRadioPortraitPosY = 174.0f;
            break;

        case GSTATE_PLAY:
            gRadioPrintPosY = 180;
            gRadioPrintPosX = OTRGetRectDimensionFromLeftEdgeOverride(79.0f);
            gRadioTextBoxPosX = OTRGetRectDimensionFromLeftEdgeOverride(74.0f);
            gRadioTextBoxPosY = 178.0f;
            gRadioTextBoxScaleX = 4.53f;
            gRadioPortraitPosX = OTRGetRectDimensionFromLeftEdgeOverride(26.0f);
            gRadioPortraitPosY = 178.0f;
            break;
    }
}

s32 sRadioUseRedBox;

void func_radio_800BAAE8(void) {
    static f32 D_800D4A74 = -1.0f;
    u16* radioPortraitTex = NULL;
    s32 mirror;
    s32 i;
    f32 sp38;
    f32 temp_fa0;

    sRadioUseRedBox = false;

    mirror = false;
    CALL_EVENT(PreSetupRadioMsgEvent, &sRadioUseRedBox);
    switch (gCurrentRadioPortrait) {
        case RCID_FOX_RED:
            sRadioUseRedBox = true;
            /* fallthrough */
        case RCID_FOX:
            radioPortraitTex = aFoxPortraitTex;
            break;
        case RCID_FOX_RED + 1:
            sRadioUseRedBox = true;
            /* fallthrough */
        case RCID_FOX + 1:
            radioPortraitTex = D_1006000;
            break;
        case RCID_FOX_EXPERT:
            radioPortraitTex = D_1006F20;
            break;
        case RCID_FOX_EXPERT + 1:
            radioPortraitTex = D_1007E40;
            break;
        case RCID_FALCO_RED:
            sRadioUseRedBox = true;
            /* fallthrough */
        case RCID_FALCO:
            radioPortraitTex = aFalcoPortraitTex;
            break;
        case RCID_FALCO_RED + 1:
            sRadioUseRedBox = true;
            /* fallthrough */
        case RCID_FALCO + 1:
            radioPortraitTex = D_10041C0;
            break;
        case RCID_SLIPPY_RED:
            sRadioUseRedBox = true;
            /* fallthrough */
        case RCID_SLIPPY:
            radioPortraitTex = aSlippyPortraitTex;
            break;
        case RCID_SLIPPY_RED + 1:
            sRadioUseRedBox = true;
            /* fallthrough */
        case RCID_SLIPPY + 1:
            radioPortraitTex = D_100E820;
            break;
        case RCID_PEPPY_RED:
            sRadioUseRedBox = true;
            /* fallthrough */
        case RCID_PEPPY:
            radioPortraitTex = aPeppyPortraitTex;
            break;
        case RCID_PEPPY_RED + 1:
            sRadioUseRedBox = true;
            /* fallthrough */
        case RCID_PEPPY + 1:
            radioPortraitTex = D_100C9E0;
            break;
        case RCID_WOLF:
            radioPortraitTex = D_STAR_WOLF_F00B580;
            break;
        case RCID_WOLF + 1:
            radioPortraitTex = D_STAR_WOLF_F00C4A0;
            break;
        case RCID_PIGMA:
            radioPortraitTex = D_STAR_WOLF_F003C80;
            break;
        case RCID_PIGMA + 1:
            radioPortraitTex = D_STAR_WOLF_F004BA0;
            break;
        case RCID_LEON:
            radioPortraitTex = D_STAR_WOLF_F007900;
            break;
        case RCID_LEON + 1:
            radioPortraitTex = D_STAR_WOLF_F008820;
            break;
        case RCID_ANDREW:
            radioPortraitTex = D_STAR_WOLF_F000000;
            break;
        case RCID_ANDREW + 1:
            radioPortraitTex = D_STAR_WOLF_F000F20;
            break;
        case RCID_WOLF_2:
            radioPortraitTex = D_STAR_WOLF_F00D3C0;
            break;
        case RCID_WOLF_2 + 1:
            radioPortraitTex = D_STAR_WOLF_F00E2E0;
            break;
        case RCID_PIGMA_2:
            radioPortraitTex = D_STAR_WOLF_F005AC0;
            break;
        case RCID_PIGMA_2 + 1:
            radioPortraitTex = D_STAR_WOLF_F0069E0;
            break;
        case RCID_LEON_2:
            radioPortraitTex = D_STAR_WOLF_F009740;
            break;
        case RCID_LEON_2 + 1:
            radioPortraitTex = D_STAR_WOLF_F00A660;
            break;
        case RCID_ANDREW_2:
            radioPortraitTex = D_STAR_WOLF_F001E40;
            break;
        case RCID_ANDREW_2 + 1:
            radioPortraitTex = D_STAR_WOLF_F002D60;
            break;
        case RCID_BOSS_CORNERIA:
            radioPortraitTex = D_CO_6026420;
            break;
        case RCID_BOSS_CORNERIA + 1:
            radioPortraitTex = D_CO_6027340;
            break;
        case RCID_BOSS_CORNERIA2:
            radioPortraitTex = D_CO_60245E0;
            break;
        case RCID_BOSS_CORNERIA2 + 1:
            radioPortraitTex = D_CO_6025500;
            break;
        case RCID_BOSS_METEO:
            radioPortraitTex = D_ME_601C8E0;
            break;
        case RCID_BOSS_METEO + 1:
            radioPortraitTex = D_ME_601D800;
            break;
        case RCID_BOSS_AREA6:
            radioPortraitTex = D_A6_60047E0;
            break;
        case RCID_BOSS_AREA6 + 1:
            radioPortraitTex = D_A6_6005700;
            break;
        case RCID_CAIMAN_AREA6:
            radioPortraitTex = D_A6_60029A0;
            break;
        case RCID_CAIMAN_AREA6 + 1:
            radioPortraitTex = D_A6_60038C0;
            break;
        case RCID_BOSS_ZONESS:
            radioPortraitTex = D_ZO_6014510;
            break;
        case RCID_BOSS_ZONESS + 1:
            radioPortraitTex = D_ZO_6015430;
            break;
        case RCID_BOSS_SECTORX:
            radioPortraitTex = D_SX_6020FB0;
            break;
        case RCID_BOSS_SECTORX + 1:
            radioPortraitTex = D_SX_6021ED0;
            break;
        case RCID_BOSS_SECTORY:
            radioPortraitTex = D_SY_6018F30;
            break;
        case RCID_BOSS_SECTORY + 1:
            radioPortraitTex = D_SY_6019E50;
            break;
        case RCID_BOSS_MACBETH:
            radioPortraitTex = D_MA_6010C20;
            break;
        case RCID_BOSS_MACBETH + 1:
            radioPortraitTex = D_MA_6011B40;
            break;
        case RCID_ROB64_RED:
            sRadioUseRedBox = true;
            /* fallthrough */
        case RCID_ROB64:
        case RCID_ROB64_2:
            radioPortraitTex = D_1009C80;
            break;
        case RCID_ROB64_RED + 1:
            sRadioUseRedBox = true;
            /* fallthrough */
        case RCID_ROB64 + 1:
        case RCID_ROB64_2 + 1:
            radioPortraitTex = D_100ABA0;
            break;
        case RCID_KATT:
            radioPortraitTex = D_D003DF0;
            break;
        case RCID_KATT + 1:
            radioPortraitTex = D_D004D10;
            break;
        case RCID_ANDROSS_RED:
        case RCID_ANDROSS:
            radioPortraitTex = D_D000170;
            if ((gGameState == GSTATE_PLAY) && (gCurrentLevel == LEVEL_AREA_6)) {
                radioPortraitTex = D_A6_6000B60;
            }
            sRadioUseRedBox = true;
            break;
        case RCID_ANDROSS_RED + 1:
        case RCID_ANDROSS + 1:
            radioPortraitTex = D_D001090;
            if ((gGameState == GSTATE_PLAY) && (gCurrentLevel == LEVEL_AREA_6)) {
                radioPortraitTex = D_A6_6001A80;
            }
            sRadioUseRedBox = true;
            break;
        case RCID_JAMES:
            radioPortraitTex = D_D005C30;
            break;
        case RCID_JAMES + 1:
            radioPortraitTex = D_D006B50;
            break;
        case RCID_BILL:
            radioPortraitTex = D_D001FB0;
            break;
        case RCID_BILL + 1:
            radioPortraitTex = D_D002ED0;
            break;
        case RCID_GEN_PEPPER:
            radioPortraitTex = D_D007A70;
            break;
        case RCID_GEN_PEPPER + 1:
            radioPortraitTex = D_D008990;
            break;
        case RCID_ROB64_TITLE:
            radioPortraitTex = D_GREAT_FOX_E00E100;
            break;
        case RCID_ROB64_TITLE + 1:
            radioPortraitTex = D_GREAT_FOX_E00F020;
            break;
        case RCID_GEN_PEPPER_TITLE:
            radioPortraitTex = D_GREAT_FOX_E00FF40;
            break;
        case RCID_GEN_PEPPER_TITLE + 1:
            radioPortraitTex = D_GREAT_FOX_E010E60;
            break;
        case RCID_TR:
            radioPortraitTex = D_TR_6000900;
            break;
        case RCID_TR + 1:
            radioPortraitTex = D_TR_6001820;
            break;
        case RCID_STATIC + 1:
            mirror = true;
            /* fallthrough */
        case RCID_STATIC:
            switch (gGameState) {
                default:
                    radioPortraitTex = NULL;
                    break;
                case GSTATE_PLAY:
                    radioPortraitTex = D_1008D60;
                    break;
                case GSTATE_TITLE:
                case GSTATE_ENDING:
                    radioPortraitTex = gTitleRadioStatic;
                    break;
            }
            if (((s32) gRadioMsgRadioId == RCID_ANDROSS) || ((s32) gRadioMsgRadioId == RCID_ANDROSS_RED)) {
                sRadioUseRedBox = true;
            }
            break;
    }
    if ((radioPortraitTex != NULL) && (gRadioPortraitScaleY != 0.0f)) {
        temp_fa0 = (2.0f * gRadioPortraitScaleY) + gRadioPortraitPosY;
        if ((gRadioPortraitPosY + 20.0f) <= temp_fa0) {
            D_800D4A74 = 1.0f;
        }
        if (temp_fa0 <= gRadioPortraitPosY) {
            D_800D4A74 = -1.0f;
        }
        sp38 = gRadioPortraitScaleY * 20.0f * D_800D4A74;
        gSPDisplayList(gMasterDisp++, gRcpSetupDLs[SETUPDL_76_OPTIONAL]);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);

        if (mirror) {
            Lib_TextureRect_RGBA16_MirX(&gMasterDisp, radioPortraitTex, 44, 44, gRadioPortraitPosX,
                                        gRadioPortraitPosY + 20.0f + sp38 + gRadioPortraitScaleY, 1.0f,
                                        gRadioPortraitScaleY);
        } else {
            Lib_TextureRect_RGBA16(&gMasterDisp, radioPortraitTex, 44, 44, gRadioPortraitPosX,
                                   gRadioPortraitPosY + 20.0f + sp38 + gRadioPortraitScaleY, 1.0f,
                                   gRadioPortraitScaleY);
        }
    }
}

void func_radio_800BB388(void) {
    static f32 D_800D4A78 = -1.0f;
    f32 temp_fa0;
    u8* texture;
    u16* palette;
    f32 sp30;
    
    Radio_CalculatePositions();

    if ((gGameState != GSTATE_MAP) && (gRadioTextBoxScaleY != 0.0f)) {
        temp_fa0 = (gRadioTextBoxScaleY / 0.26f) * 3.0f;
        if ((gRadioTextBoxPosY + 16.0f) <= (temp_fa0 + gRadioTextBoxPosY)) {
            D_800D4A78 = 1.0f;
        }
        if (temp_fa0 + gRadioTextBoxPosY <= gRadioTextBoxPosY) {
            D_800D4A78 = -1.0f;
        }

        sp30 = temp_fa0 * D_800D4A78;

        RCP_SetupDL(&gMasterDisp, SETUPDL_85_OPTIONAL);

        switch (gGameState) {
            case GSTATE_TITLE:
            case GSTATE_ENDING:
                texture = aNoControllerBgTex;
                palette = aNoControllerBgTLUT;
                break;

            case GSTATE_PLAY:
                texture = aMsgWindowBgTex;
                palette = aMsgWindowBgTLUT;
                break;
        }

        if (sRadioUseRedBox == true) {
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 25, 25, 170);
        } else {
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 60, 60, 255, 170);
        }

        Lib_TextureRect_CI8(&gMasterDisp, texture, palette, 32, 32, gRadioTextBoxPosX, gRadioTextBoxPosY + 16.0f + sp30,
                            gRadioTextBoxScaleX, gRadioTextBoxScaleY);
    }

    if (gRadioTextBoxScaleY == 1.3f) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_85_OPTIONAL);
        gMsgCharIsPrinting =
            Message_DisplayText(&gMasterDisp, gRadioMsg, gRadioPrintPosX, gRadioPrintPosY, gRadioMsgCharIndex);
    }
}

s32 D_radio_80178748; // set to 1, never used
s32 sRadioCheckMouthFlag;

void Radio_Draw(void) {
    s32 idx;
    RadioCharacterId radioCharId;
    u32 ret;
    s32 fakeTemp;

    if ((gPlayState == PLAY_PAUSE) && (gGameState != GSTATE_ENDING)) {
        return;
    }

    if (gRadioStateTimer > 0) {
        gRadioStateTimer--;
    }

    if (gRadioMouthTimer > 0) {
        gRadioMouthTimer--;
    }

    switch (gRadioState) {
        case 100:
            D_radio_80178748 = 1;
            gCurrentRadioPortrait = RCID_1000;
            gRadioState = 1;
            gRadioMsgCharIndex = 0;
            gRadioPortraitScaleY = 0.0f;
            gRadioTextBoxScaleY = 0.0f;
            sRadioCheckMouthFlag = 0;
            if (gCamCount != 1) {
                gRadioState = 0;
            }
            break;

        case 1:
            gRadioPortraitScaleY += 0.25f;
            if (gRadioPortraitScaleY == 1.0f) {
                gRadioState++;
                gRadioStateTimer = 10;
            }
            gCurrentRadioPortrait = RCID_STATIC;
            if ((gGameFrameCount % 2) != 0) {
                gCurrentRadioPortrait = RCID_STATIC + 1;
            }
            break;

        case 2:
            if (gRadioStateTimer == 0) {
                gRadioState++;
                gRadioStateTimer = 10;
            }
            gCurrentRadioPortrait = RCID_STATIC;
            if ((gGameFrameCount % 2) != 0) {
                gCurrentRadioPortrait = RCID_STATIC + 1;
            }
            break;

        case 3:
            if (gRadioStateTimer == 0) {
                gRadioState++;
                ret = Message_GetWidth(gRadioMsg);
                if (gVIsPerFrame == 3) {
                    gRadioStateTimer = ret + 16;
                } else {
                    gRadioStateTimer = (2 * ret) + 16;
                }
                if ((gGameState == GSTATE_TITLE) || (gGameState == GSTATE_ENDING)) {
                    gRadioStateTimer = ret * 2;
                }
            }
            gCurrentRadioPortrait = (s32) gRadioMsgRadioId;
            gRadioTextBoxScaleY += 0.26f;
            if (gRadioTextBoxScaleY > 1.3f) {
                gRadioTextBoxScaleY = 1.3f;
            }
            break;

        case 31:
            gRadioState++;
            gRadioStateTimer = 80 - gRadioStateTimer;
            break;

        case 32:
            if (Audio_GetCurrentVoice() == 0) {
                gRadioMsgListIndex++;
                gRadioMsg = SEGMENTED_TO_VIRTUAL(gRadioMsgList[gRadioMsgListIndex]);
                Audio_PlayVoice(Message_IdFromPtr(gRadioMsg));
                gRadioMsgCharIndex = 0;
                sRadioCheckMouthFlag = 0;
                gRadioStateTimer = 80;
                gRadioStateTimer = Message_GetWidth(gRadioMsg) * 2;
                gRadioState = 4;
            }
            break;

        case 4:
            if ((Audio_GetCurrentVoice() == 0) && (gRadioStateTimer == 0)) {
                gRadioStateTimer = 10;
                gCurrentRadioPortrait = (s32) gRadioMsgRadioId;
                gRadioState = 6;
            }
            gCurrentRadioPortrait = (s32) gRadioMsgRadioId;
            if (gRadioMouthTimer > 0) {
                gCurrentRadioPortrait = (s32) gRadioMsgRadioId + 1;
            }

            if (!gVIsPerFrame) {}

            if (1) {
                fakeTemp = 0;
            }

            if (!(fakeTemp)) {
                ret = Audio_GetCurrentVoiceStatus();

                if (gRadioMsgCharIndex < 60 && gRadioMsg[gRadioMsgCharIndex + 1] != MSGCHAR_END) {
                    if (gRadioMsg[gRadioMsgCharIndex + 1] == MSGCHAR_NXT) {
                        if (ret == 0) {
                            gRadioState = 31;
                        }
                    } else {
                        gRadioMsgCharIndex++;
                    }
                } else if (gRadioMsgCharIndex < 60) {
                    gRadioMsgCharIndex = 60;
                }

                if (sRadioCheckMouthFlag) {
                    if ((gRadioMsgId >= 23000) && (gRadioMsgId < 23033)) {
                        if (gMsgCharIsPrinting) {
                            gRadioMouthTimer = 2;
                            AUDIO_PLAY_SFX(NA_SE_MESSAGE_MOVE, gDefaultSfxSource, 4);
                        }
                    } else if (ret == 1) {
                        gRadioMouthTimer = 2;
                    } else {
                        gRadioMouthTimer = 0;
                    }
                }
            }
            sRadioCheckMouthFlag ^= 1;
            break;

        case 5:
            if (gRadioStateTimer == 0) {
                gRadioState++;
                gRadioStateTimer = 10;
            }
            gCurrentRadioPortrait = (s32) gRadioMsgRadioId;
            break;

        case 6:
            if (gRadioStateTimer == 0) {
                if (gGameState == GSTATE_ENDING) {
                    Audio_ClearVoice();
                } else {
                    Audio_PlayVoice(0);
                }
                gRadioState++;
            }
            gCurrentRadioPortrait = RCID_STATIC;
            if ((gGameFrameCount % 2) != 0) {
                gCurrentRadioPortrait = RCID_STATIC + 1;
            }
            gRadioTextBoxScaleY -= 0.26f;
            if (gRadioTextBoxScaleY < 0.0f) {
                gRadioTextBoxScaleY = 0.0f;
            }
            break;

        case 7:
            gRadioPortraitScaleY -= 0.25f;
            if (gRadioPortraitScaleY == 0) {
                gHideRadio = false;
                gRadioMsgPri = 0;
                gRadioState = 0;
            }
            gCurrentRadioPortrait = RCID_STATIC;
            if ((gGameFrameCount % 2) != 0) {
                gCurrentRadioPortrait = RCID_STATIC + 1;
            }
            break;

        case 8:
            gCurrentRadioPortrait = (s32) gRadioMsgRadioId;
            gRadioTextBoxScaleY = 1.3f;
            gRadioPortraitScaleY = 1.0f;
            break;

        case 0:
            break;
    }

    if (((gRadioState > 0) && (gRadioState != 100)) && !gHideRadio) {
        func_radio_800BAAE8();
        func_radio_800BB388();

        radioCharId = (s32) gRadioMsgRadioId;

        if (((radioCharId == RCID_FALCO) || (radioCharId == RCID_SLIPPY)) || (radioCharId == RCID_PEPPY)) {
            if (radioCharId == RCID_FALCO) {
                idx = TEAM_ID_FALCO;
            }
            if (radioCharId == RCID_SLIPPY) {
                idx = TEAM_ID_SLIPPY;
            }
            if (radioCharId == RCID_PEPPY) {
                idx = TEAM_ID_PEPPY;
            }
            if ((gTeamShields[idx] <= 0) && (gGameFrameCount & 4) && (gTeamShields[idx] != -2) &&
                (gCurrentRadioPortrait != RCID_STATIC) && (gCurrentRadioPortrait != RCID_STATIC + 1) &&
                (gCurrentRadioPortrait != RCID_1000)) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_76_OPTIONAL);
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 0, 255);
                Graphics_DisplaySmallText(OTRGetRectDimensionFromLeftEdgeOverride(31.0f), 167, 1.0f, 1.0f, "DOWN");
                HUD_TeamDownWrench_Draw(1);
            }
            if (((gCurrentRadioPortrait != RCID_STATIC) && (gCurrentRadioPortrait != RCID_STATIC + 1)) &&
                (gCurrentRadioPortrait != RCID_1000)) {
                HUD_TeamShields_Draw(OTRGetRectDimensionFromLeftEdgeOverride(22.0f), 165.0f, gTeamShields[idx]);
            }
        }

        radioCharId = (s32) gRadioMsgRadioId;

        if ((radioCharId == RCID_WOLF) || (radioCharId == RCID_PIGMA) || (radioCharId == RCID_LEON) ||
            (radioCharId == RCID_ANDREW) || (radioCharId == RCID_WOLF_2) || (radioCharId == RCID_PIGMA_2) ||
            (radioCharId == RCID_LEON_2) || (radioCharId == RCID_ANDREW_2)) {
            switch (radioCharId) {
                case RCID_WOLF:

                case RCID_WOLF_2:
                    idx = 4;
                    break;

                case RCID_LEON:

                case RCID_LEON_2:
                    idx = 5;
                    break;

                case RCID_PIGMA:

                case RCID_PIGMA_2:
                    idx = 6;
                    break;

                case RCID_ANDREW:

                case RCID_ANDREW_2:
                    idx = 7;
                    break;

                default:
                    idx = 0;
                    break;
            }

            if ((gActors[idx].obj.status != OBJ_ACTIVE) && (gGameFrameCount & 4) &&
                (gPlayer[0].state == PLAYERSTATE_ACTIVE) && (gCurrentRadioPortrait != RCID_STATIC) &&
                (gCurrentRadioPortrait != RCID_STATIC + 1) && (gCurrentRadioPortrait != RCID_1000)) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_76_OPTIONAL);
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 0, 255);
                Graphics_DisplaySmallText(OTRGetRectDimensionFromLeftEdgeOverride(31.0f), 167, 1.0f, 1.0f, "DOWN");
            }
            if (((gCurrentRadioPortrait != RCID_STATIC) && (gCurrentRadioPortrait != RCID_STATIC + 1)) &&
                (gCurrentRadioPortrait != RCID_1000)) {
                HUD_TeamShields_Draw(OTRGetRectDimensionFromLeftEdgeOverride(22.0f), 165.0f, gActors[idx].health * 2.55f);
            }
        }
        if (((gCurrentRadioPortrait != RCID_STATIC) && (gCurrentRadioPortrait != RCID_STATIC + 1)) &&
            (gCurrentRadioPortrait != RCID_1000)) {
            HUD_RadioCharacterName_Draw();
        }
    }

    if (gHideRadio == true) {
        func_radio_800BA760();
    }
}

// Unused in VERSION_US and absent in VERSION_EU, probably a leftover from VERSION_JP ?
void func_radio_800BC040(void) {
    if (gPlayState != PLAY_PAUSE) {
        if (gRadioStateTimer > 0) {
            gRadioStateTimer--;
        }
        if (gRadioMouthTimer > 0) {
            gRadioMouthTimer--;
        }

        switch (gRadioState) {
            case 100:
                gCurrentRadioPortrait = RCID_1000;
                gRadioState = 1;
                gRadioPortraitScaleY = 0.0f;
                gRadioTextBoxScaleY = 0.0f;
                gRadioMsgCharIndex = Message_GetWidth(gRadioMsg);
                if (gCamCount != 1) {
                    gRadioState = 0;
                }
                break;

            case 1:
                gRadioPortraitScaleY += 0.02f;
                if (gRadioPortraitScaleY == 0.04f) {
                    gRadioState++;
                    gRadioStateTimer = 5;
                }
                break;

            case 2:
                if (gRadioStateTimer == 0) {
                    gRadioState++;
                    gRadioStateTimer = 5;
                }

                gCurrentRadioPortrait = RCID_STATIC;

                if ((gGameFrameCount % 2) != 0) {
                    gCurrentRadioPortrait = RCID_STATIC + 1;
                }
                break;

            case 3:
                if (gRadioStateTimer == 0) {
                    gRadioState++;
                    gRadioStateTimer = 5;

                    if (gGameState == GSTATE_TITLE) {
                        gRadioStateTimer = 30;
                    }
                }

                gCurrentRadioPortrait = (s32) gRadioMsgRadioId;
                gRadioTextBoxScaleY += 0.015f;

                if (gRadioTextBoxScaleY > 0.07f) {
                    gRadioTextBoxScaleY = 0.07f;
                }
                break;

            case 4:
                if (gRadioStateTimer == 0) {
                    gRadioState++;
                    gRadioStateTimer = 10;
                }
                break;

            case 5:
                if (gRadioStateTimer == 0) {
                    gRadioState++;
                    gRadioStateTimer = 5;
                }
                gCurrentRadioPortrait = (s32) gRadioMsgRadioId;
                break;

            case 6:
                if (gRadioStateTimer == 0) {
                    Audio_PlayVoice(0);
                    gRadioState++;
                }

                gCurrentRadioPortrait = RCID_STATIC;

                if ((gGameFrameCount % 2) != 0) {
                    gCurrentRadioPortrait = RCID_STATIC + 1;
                }

                gRadioTextBoxScaleY -= 0.015f;

                if (gRadioTextBoxScaleY < 0.0f) {
                    gRadioTextBoxScaleY = 0.0f;
                }
                break;

            case 7:
                gRadioPortraitScaleY -= 0.02f;
                if (gRadioPortraitScaleY == 0) {
                    gRadioState = 0;
                    gRadioStateTimer = 5;
                }
                gCurrentRadioPortrait = RCID_STATIC;
                if ((gGameFrameCount % 2) != 0) {
                    gCurrentRadioPortrait = RCID_STATIC + 1;
                }
                break;

            case 0:
                break;
        }

        if ((gRadioState > 0) && (gRadioState != 100)) {
            func_radio_800BAAE8();
            func_radio_800BB388();
            if (((s32) gRadioMsgRadioId == RCID_FALCO) || ((s32) gRadioMsgRadioId == RCID_SLIPPY) ||
                ((s32) gRadioMsgRadioId == RCID_PEPPY)) {
                Matrix_Push(&gGfxMatrix);
                RCP_SetupDL_36();
                Matrix_Translate(gGfxMatrix, -150.0f, -115.0f, -443.0f, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, 0.068f, 0.068f, 1.0f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gPlayerNum = 0;
                Matrix_Pop(&gGfxMatrix);
            }
        }
    }
}
