#ifndef FOX_TITLE_H
#define FOX_TITLE_H

#include "global.h"

typedef enum TitleStates {
    /* 0 */ TITLE_IDLE,
    /* 1 */ TITLE_SETUP,
    /* 2 */ TITLE_UPDATE_ENTRY
} TitleStates;

typedef enum TitleTeam {
    /* 0 */ TEAM_FOX,
    /* 1 */ TEAM_FALCO,
    /* 2 */ TEAM_PEPPY,
    /* 3 */ TEAM_SLIPPY
} TitleTeam;

typedef enum TitleCsStates {
    /* 0 */ TITLE_SCREEN,              // In the Title Screen.
    /* 1 */ TITLE_GREAT_FOX_TRAVELING, // Close up to the Great Fox while it's traveling to corneria.
    /* 2 */ TITLE_CS_TEAM_RUNNING,     // Team is running in Great Fox's the passage way before take-off.
    /* 3 */ TITLE_GREAT_FOX_CLOSE_UP,  // Closing up to the Great Fox before take-off.
    /* 4 */ TITLE_TAKE_OFF,            // Take-off cutscene.
    /* 5 */ TITLE_TAKE_OFF_SPACE,      // Arwings coming out of the Great Fox out to space.
    /* 7 */ TITLE_RANKING = 7          // Show ranking
} TitleCsStates;

typedef enum TitleCardStates {
    /* 0 */ TITLE_CARD_NONE,
    /* 1 */ TITLE_CARD_GREAT_FOX,
    /* 2 */ TITLE_CARD_ARWING
} TitleCardStates;

typedef enum TitleLogoStates {
    /* -1 */ TITLE_LOGO_NONE = -1,
    /*  0 */ TITLE_LOGO_STARFOX_IN,
    /*  1 */ TITLE_LOGO_NINTENDO_64
} TitleLogoStates;

typedef struct AmbientRGB {
    /* 0x00 */ f32 r;
    /* 0x04 */ f32 g;
    /* 0x08 */ f32 b;
} AmbientRGB; // size = 0xC

typedef struct {
    /* 0x00 */ Animation* cutscene;
    /* 0x04 */ Animation* title;
    /* 0x08 */ Limb** skeleton;
} TitleAnimation; // size = 0x0C

typedef struct TitleTeamInfo {
    /* 0x00 */ Vec3f pos;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 shadowScale;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ f32 unk_34;
    /* 0x38 */ f32 unk_38;
    /* 0x3C */ f32 unk_3C;
    /* 0x40 */ f32 unk_40;
    /* 0x44 */ f32 unk_44;
    /* 0x48 */ f32 unk_48;
    /* 0x4C */ f32 unk_4C;
    /* 0x50 */ f32 unk_50;
    /* 0x54 */ bool unk_54;
    /* 0x58 */ s32 frameCount;
    /* 0x5C */ s32 unk_5C;
} TitleTeamInfo; // size = 0x60

typedef struct TitleArwingInfo {
    /* 0x00 */ Vec3f pos;
    /* 0x0C */ f32 scale;
    /* 0x10 */ f32 vel; // Assumption
    /* 0x14 */ char pad14[0x4];
    /* 0x18 */ f32 xRot;
    /* 0x1C */ f32 yRot;
    /* 0x20 */ f32 zRot;
    /* 0x24 */ f32 cockpitGlassXrot;
    /* 0x28 */ f32 laserGunsYpos;
    /* 0x2C */ f32 teamFaceXrot;
    /* 0x30 */ f32 teamFaceYrot;
    /* 0x34 */ s32 drawFace;
    /* 0x38 */ s32 timer;  // Used for closing the cockpit glass and take off
    /* 0x3C */ s32 unk_3C; // Related to engine glow. Investigate
    /* 0x40 */ s32 unk_40; // Related to engine glow. Investigate
    /* 0x44 */ f32 unk_44; // Related to engine glow. Investigate
    /* 0x48 */ bool drawShadow;
    /* 0x4C */ bool draw;
    /* 0x50 */ f32 sfxSource[3];
} TitleArwingInfo; // size = 0x5C

typedef struct {
    /* 0x00 */ Vec3f pos;
    /* 0x0C */ char pad0C[0x4];
    /* 0x10 */ f32 xRot;
    /* 0x14 */ f32 yRot;
    /* 0x18 */ f32 zRot;
    /* 0x1C */ f32 scale;
    /* 0x20 */ char pad20[0x4];
    /* 0x24 */ f32 sfxSource[3];
} TitleGreatFoxInfo; // size = 0x30

typedef struct {
    /* 0x00 */ Vec3f pos;
    /* 0x0C */ bool draw;
    /* 0x10 */ f32 scale;
} TitleCorneria; // size = 0x14

#ifdef __cplusplus
extern "C" {
#endif

extern CameraPoint D_menu_801B6B40[];
extern CameraPoint D_menu_801B6C60[];
extern f32 D_menu_801B7BB0;
extern f32 D_menu_801B7BB4;
extern f32 D_menu_801B7BB8;
extern f32 D_menu_801B7BBC;
extern f32 D_menu_801B7BC0;
extern f32 D_menu_801B7BC4;
extern f32 sTitleTextPrimCol;
extern f32 sTitleTextPrimColTarget;
extern s32 D_menu_801B7BD0;
extern TitleLogoStates sTitleLogoState;
extern s32 D_menu_801B7BD8;
extern f32 sStarfoxLogoAlpha;
extern f32 sInAlpha;
extern s32 D_menu_801B7BE4;
extern f32 D_menu_801B7BE8;
extern s32 D_menu_801B7BEC;
extern TitleCardStates sTitleCardState;
extern f32 D_menu_801B7BF8[10];
extern f32 D_menu_801B7C20[10];
extern f32 D_menu_801B7C48[10];
extern f32 D_menu_801B7C70[10];
extern s32 sMaxExplosions;
extern s32 D_menu_801B7CA0[10];
extern s32 D_menu_801B7CC8[10];
extern s32 D_menu_801B7CF0[10];
extern s32 D_menu_801B7D18[10];
extern f32 D_menu_801B7D40[40];
extern f32 D_menu_801B7DE0[40];
extern f32 D_menu_801B7E80[40];
extern f32 D_menu_801B7F20[40];
extern f32 D_menu_801B7FC0[40];
extern f32 D_menu_801B8060[40];
extern s32 D_menu_801B8100;
extern s32 D_menu_801B8108[40];
extern s32 gRankingTeamAlive[10][3];
extern s32 gTotalHitsRanking[10];
extern u8 sRankNameEntry[10][4];
extern UNK_TYPE D_menu_801B8270[3];
extern bool gGoToTitle;
extern u8 sLevelStartState;
extern s32 sWipeHeight;
extern s32 sTitleRankMaxRecords;
extern f32 D_menu_801B828C;
extern f32 D_menu_801B8290;
extern CameraPoint* D_menu_801B8294;
extern s32 D_menu_801B8298;
extern f32 sTitleCamUpX;
extern f32 sTitleCamUpY;
extern f32 sTitleCamUpZ;
extern s32 sTimer1;
extern s32 sTimer2;
extern s32 D_menu_801B82B0;
extern s32 sTimer3;
extern s32 sTitleMsgFrameCount;
extern s32 D_menu_801B82BC;
extern s32 sSceneState;
extern s32 sCutsceneState;
extern f32 sPassageWayZoffset;
extern f32 D_menu_801B82CC;
extern f32 D_menu_801B82D0;
extern f32 D_menu_801B82D4;
extern f32 D_menu_801B82D8;
extern f32 D_menu_801B82DC;
extern f32 D_menu_801B82E0;
extern f32 D_menu_801B82E4;
extern f32 D_menu_801B82E8;
extern f32 D_menu_801B82EC;
extern f32 D_menu_801B82F0;
extern f32 D_menu_801B82F4;
extern s32 D_menu_801B82F8;
extern s32 D_menu_801B82FC;
extern s32 D_menu_801B8300;
extern f32 D_menu_801B8304;
extern f32 D_menu_801B8308;
extern f32 D_menu_801B830C;
extern s32 D_menu_801B8310;
extern s32 D_menu_801B8314;
extern s32 D_menu_801B8318;
extern s32 D_menu_801B831C;
extern s32 D_menu_801B8320;
extern s32 D_menu_801B8324;
extern f32 sAmbientR;
extern f32 sAmbientG;
extern f32 sAmbientB;
extern s32 D_menu_801B8334;
extern bool D_menu_801B8338;
extern f32 D_menu_801B833C;
extern TitleTeam D_menu_801B8340;
extern bool sDrawTeamName;
extern bool D_menu_801B8348;
extern TitleTeamInfo sTitleTeam[4];
extern f32 D_menu_801B84D0;
extern f32 D_menu_801B84D4;
extern f32 D_menu_801B84D8[3];
extern TitleArwingInfo sTitleArwing[4];
extern TitleGreatFoxInfo sTitleGreatFox;
extern TitleCorneria sTitleCorneria;
extern s32 D_menu_801B869C;
extern bool sDrawTakeOffSpace;
extern s32 D_menu_801B86A4;
extern f32 D_menu_801B86A8;
extern f32 D_menu_801B86AC;
extern f32 D_menu_801B86B0;
extern f32 D_menu_801B86B4;
extern f32 D_menu_801B86B8;
extern f32 D_menu_801B86BC;
extern f32 D_menu_801B86C0;
extern f32 D_menu_801B86C4;
extern f32 D_menu_801B86C8;
extern f32 D_menu_801B86CC;
extern f32 D_menu_801B86D0;
extern f32 D_menu_801B86D4;
extern f32 D_menu_801B86D8;
extern f32 D_menu_801B86DC;
extern Vec3f sCharFrameTable[4][50];
extern bool D_menu_801B9040;
extern f32 sTitleDeckLauncherZpos;
extern f32 D_menu_801B9048;
extern f32 D_menu_801B904C;
extern f32 D_menu_801B9050;
extern f32 sTitleStarfoxLogoXpos;
extern f32 sTitleStarfoxLogoYpos;
extern f32 D_menu_801B905C;
extern f32 D_menu_801B9060;
extern f32 D_menu_801B9064;
extern f32 D_menu_801B9068;
extern f32 D_menu_801B906C;
extern f32 D_menu_801B9070;
extern f32 D_menu_801B9074;
extern f32 D_menu_801B9078;
extern f32 D_menu_801B907C;
extern f32 D_menu_801B9080;
extern f32 D_menu_801B9084;

void Title_Screen_Input(void);
void Title_Cutscene_SetCamera(CameraPoint*, s32, f32);
void Title_Camera_Calc(CameraPoint* pos, CameraPoint* arg1, f32 weight, s32 arg3);
void Title_Arwing_DrawEngineGlow(TitleTeam);
void Title_EngineGlowParticles_Draw(TitleTeam);
void Title_ArwingShadow_Draw(s32);
void Title_Corneria_Draw(f32 zPos);
void Title_GreatFox_Draw(void);
void Title_CorneriaExplosions_Draw(void);
bool Title_Team_OverrideLimbDraw(s32, Gfx**, Vec3f*, Vec3f*, void*);
void Title_TeamRunning_Draw(TitleTeam);
void Title_Passage_Draw(void);
void Title_Sun_Draw(void);
void Title_SunGlare2_Draw(void);
void Title_GreatFoxDeck_Draw(void);
void Title_GreatFoxDeckPlatform_Draw(void);
void Title_GreatFoxDeckLauncher_Draw(TitleTeam teamidx);
void Title_NextState_TitleScreen(void);
void Title_NextState_OptionMenu(void);
void Title_ScreenFade_Update(void);
void Title_SetCamUp3(bool arg0, f32* arg1, f32* arg2, f32* arg3, f32* arg4, f32* arg5, f32* arg6, f32 arg7, f32 arg8,
                    f32 arg9);
void Title_SetCamUp2(f32 arg0, f32 arg1, f32 arg2, f32* arg3, f32* arg4, f32* arg5, f32 arg6, f32* arg7, f32* arg8,
                    f32* arg9, f32 argA, f32 argB, f32 argC);
void Title_GetCamRot(f32* xRot, f32* yRot);
void Title_SetCamUp(f32 xRot, f32 yRot);
void Title_Matrix_Push(void);
void Title_Radio_PlayMessage(u16** msgList, RadioCharacterId character);
s32 Title_GetRankTotalHits(void);
void Title_TitleCard_Draw(void);
void Title_Arwing_Draw(TitleTeam);
void Title_Team_Draw(TitleTeam);
void Title_Logos_Draw(void);
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
void Title_NextState_Check(void);
void Title_SetLightRot(f32, f32, f32, f32*, f32*, f32*);

#ifdef __cplusplus
}
#endif

#endif
