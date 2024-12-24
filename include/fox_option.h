#ifndef FOX_OPTION_H
#define FOX_OPTION_H

#include "global.h"

typedef struct {
    /* 0x00 */ s32 type;
    /* 0x04 */ s32 unk_04; // Always set to 0 and never used
    /* 0x08 */ void* texture;
    /* 0x0C */ u16* palette;
    /* 0x10 */ s32 width;
    /* 0x14 */ s32 height;
    /* 0x18 */ f32 xPos;
    /* 0x1C */ f32 yPos;
    /* 0x20 */ f32 xScale;
    /* 0x24 */ f32 yScale;
    /* 0x28 */ s32 red;
    /* 0x2C */ s32 green;
    /* 0x30 */ s32 blue;
    /* 0x34 */ s32 alpha;
} OptionCardTexture; // size = 0x38

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 xScale;
    /* 0x10 */ f32 yScale;
} OptionCardFrame; // size = 0x14

typedef struct {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 range;
} ArwingCursorPos; // size = 0xC

typedef struct {
    /* 0x00 */ OptionCardTexture tex;
    /* 0x38 */ OptionCardFrame frame;
    /* 0x4C */ ArwingCursorPos pos;
    /* 0x58 */ bool drawTex;
    /* 0x5C */ bool drawFrame;
} OptionEntry; // size = 0x60

typedef struct {
    /* 0x0 */ PlanetId start;
    /* 0x4 */ PlanetId end;
    /* 0x8 */ s32 color;
} RouteColoredLine; // size = 0xC

typedef struct {
    s32 unk_0;
    s32 unk_4;
} StickInput;

typedef enum OptionId {
    /* 1000 */ OPTION_MAIN_MENU = 1000,
    /* 2000 */ OPTION_VERSUS_STAGE = 2000,
    /*    0 */ OPTION_MAP = 0,
    /*    1 */ OPTION_TRAINING,
    /*    2 */ OPTION_VERSUS,
    /*    3 */ OPTION_RANKING,
    /*    4 */ OPTION_SOUND,
#ifdef VERSION_EU
    /*    5 */ OPTION_LANGUAGE,
    /*    6 */ OPTION_DATA,
    /*    7 */ OPTION_EXPERT_SOUND,
#else
    /*    5 */ OPTION_DATA,
    /*    6 */ OPTION_EXPERT_SOUND,
#endif
    /*   10 */ OPTION_POINT_MATCH = 10, // Point Match
    /*   20 */ OPTION_BR_MATCH = 20,    // Battle Royal Match
    /*   30 */ OPTION_TT_MATCH = 30,    // Time Trial Match
    /*  200 */ OPTION_NAME_ENTRY = 200,
    /*  300 */ OPTION_SCORE = 300,
    /*  400 */ OPTION_INVOICE = 400,
    /*  401 */ OPTION_MAX
} OptionId;

extern u8* gBSSMapPlanetTextures[9];
extern u8* gAssetMapPlanetTextures[9];

extern s32 gTotalHitsRanking[];
extern bool gGoToTitle;   // engine
extern u8 sLevelStartState;
extern s32 sWipeHeight;
extern s32 sTitleRankMaxRecords;

// Planet textures
extern u8 gMapVenomCloudTex[96 * 96];
extern u8 gMapCorneriaTex[96 * 96];
extern u8 gMapFortunaTex[96 * 96];
extern u8 gMapAquasTex[96 * 96];
extern u8 gMapVenomTex[96 * 96];
extern u8 gMapTitaniaTex[96 * 96];
extern u8 gMapKatinaTex[96 * 96];
extern u8 gMapMacbethTex[96 * 96];
extern u8 gMapZonessTex[96 * 96];

void Title_UpdateEntry(void);
s32 Title_CheckControllers(void);
void Title_Ranking_Update(void);
void Title_RankingData_Draw(void);
void Title_Screen_Update(void);
void Title_CsGreatFoxTraveling_Update(void);
void Title_CsTeamRunning_Update(void);
void Title_CsGreatFoxCloseUp_Update(void);
void Title_CsTakeOff_Update(void);
void Title_CsTakeOffSpace_Update(void);
void Title_Ranking_Draw(void);
s32 Title_GetRankTotalHits(void);
void Title_Screen_Draw(void);
void Title_CsGreatFoxTraveling_Draw(void);
void Title_CsTeamRunning_Draw(void);
void Title_CsGreatFoxCloseUp_Draw(void);
void Title_CsTakeOff_Draw(void);
void Title_CsTakeOffSpace_Draw(void);
void Title_StarfoxLogo_Draw(void);
void Title_64Logo_Draw(void);
void Title_CopyrightSymbol_Draw(void);
void Title_PressStart_Draw(void);
void Title_Copyright_Draw(void);
void Title_TeamName_Draw(void);
void Title_SunGlare_Draw(void);

void Option_Entry_Update(void);
void Option_Map_Update(void);
void Option_MainMenu_Update(void);
void Option_Training_Update(void);
void Option_MainMenu_Draw(void);
void Option_Versus_Update(void);
void Option_Versus_Draw(void);
void Option_Sound_Setup(void);
void Option_Sound_Update(void);
void Option_Sound_SetSoundMode(void);
void Option_Sound_SetVolumeLevels(void);
void Option_Sound_Draw(void);
void Option_Sound_Speaker_Draw(void);
void Option_ExpertSound_Setup(void);
void Option_ExpertSound_Update(void);
void Option_ExpertSound_Draw(void);
void Option_Data_Setup(void);
void Option_Data_Update(void);
void Option_Data_Select(void);
void Option_Data_Draw(void);
void Option_Ranking_Setup(void);
void Option_Ranking_Update(void);
void Option_Ranking_Draw(void);
void Option_Ranking_Select(void);
void Option_Ranking_Cursor(void);
void Option_Ranking2_Cursor(void);
void Option_RankingMenu_Draw(void);
void Option_RankingMenu2_Draw(void);
void Option_80197914(void);
void Option_OrdinalNumbers_Draw(s32, s32, s32);
void Option_RankingName_Draw(s32, s32, s32);
void Option_RankingTotalHits_Draw(s32, s32, s32);
void Option_RankingTeamAlive_Draw(s32, s32, s32);
void Option_RankingRoute_Draw(s32, f32, f32);
void Option_RankingRouteFrame_Draw(s32, s32, f32, f32, s32);
void Option_RankingHitCount_Draw(s32, s32, f32, f32);
void Option_RankingTeamPresence_Draw(s32, s32, f32, f32);
void Option_RankingPlanetName_Draw(s32, s32, f32, f32);
void Option_RankingPlanetRoute_Draw(s32, f32, s32);
void Option_RankingRouteMedal_Draw(f32 xPos, f32 yPos, f32 zPos);
s32 Option_GetRouteLineColor(PlanetId start, PlanetId end);
void Option_VersusMenu_Setup(void);
void Option_VersusMenu_Update(void);
void Option_VersusMenu_Cursor(void);
void Option_VersusMenu_Draw(void);
void Option_VS_HandicapSet_Draw(s32);
void Option_VS_N64Console_Draw(void);
void Option_VersusStage_Setup(void);
void Option_8019A080(void);
void Option_VersusStage_Update(void);
void Option_Vs_PointMatch_Update(void);
void Option_Vs_BattleRoyal_Update(void);
void Option_Vs_TimeTrial_Update(void);
void Option_Vs_StartMatch(void);
void Option_Vs_Point_Selection(void);
void Option_VsTimeSelection(void);
void Option_VsStageSelection(void);
void Option_VsConfirmSelection(void);
void Option_VersusStage_Draw(void);
void Option_VsPointMatch_Draw(void);
void Option_VsTimeTrial_Draw(void);
void Option_VsStageSelect_Draw(void);
void Option_VsTimeTrialStageSelect_Draw(void);
void Option_VsStageSelect2_Draw(void);
void Option_VsOKConfirm_Draw(void);
void Option_VsSelectionArrows_Draw(f32 xPos, f32 yPos, f32 offset, s32 r, s32 g, s32 b);
void Option_AcceptCancel_Draw(void);
void Option_VsBackToSubMenu(OptionId menuEntryState);
void Option_VsMenuCard_Draw(void);
void Option_DrawMenuLabel(void);
void Option_DrawMenuCard(OptionCardFrame arg0);
void Option_DrawMenuArwing(ArwingCursorPos arwing);
void Option_DrawArwing(f32, f32, f32, f32, f32, f32, s32);
void Option_Menu_Push(void);
void Option_SetMenuLightPos(f32, f32, f32, f32*, f32*, f32*);
void Option_CardLightning_Update(void);
void Option_CardLightning_Draw(void);
void Option_DrawCardLabel(OptionCardTexture tex);
bool Option_Input_MoveCursor_Y(s32* arg0, s32 arg1, bool arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6,
                               s32 controllerNum, StickInput* stickY);
s32 Option_Input_DataSelect_X(s32*);
bool Option_Input_Sound_X(f32* arg0, f32 arg1, f32 arg2, StickInput* arg3);
void Option_Color_FlashRed(f32*);
s32 Option_RankInPos_Check(void);
void Option_NameEntry_Update(void);
void Option_NameEntry_Setup(void);
void Option_NameEntry_Select(void);
void Option_NameEntry_Draw(void);
void Option_Ranking_SaveData(void);
void Option_3DFont_Draw(s32, f32, f32, f32, f32, f32, f32, f32);
s32 Option_GetCharIndex(s32 character);
void Option_Score_Update(void);
void Option_Score_Update2(void);
void Option_Score_Draw(void);
void Option_Invoice_Update(void);
void Option_InvoiceDraw(void);

void Map_Main(void);
void Map_Texture_Sphere(u8*, u8*, f32*);
void Map_RemainingLives_Draw(s32, s32, s32);
void Map_801A9FD4(bool);

#endif
