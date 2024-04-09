#ifndef CONTEXT_H
#define CONTEXT_H

#include "sys.h"
#include "sf64level.h"
#include "sf64object.h"
#include "sf64player.h"

extern s32 gOverlaySetup;
extern s32 gOverlayStage;
extern s32 D_ctx_80177824; // some sort of flag
extern s32 D_ctx_8017782C; // some sort of flag. all range related?
extern GameState gGameState;
extern s32 gNextGameStateTimer; // next game state timer?
extern s32 D_ctx_80177844; // timer for vs item spawn
extern OptionState gOptionMenuStatus;
extern s32 gPlayState; // pause-related state
extern s32 D_ctx_80177868; // some sort of state. pause-related?
extern LevelMode gLevelMode;
extern DrawMode gDrawMode;
extern s32 gPlayerNum;
extern s32 gCamCount;
extern s32 gTeamShields[6];
extern s32 gSavedTeamShields[6];
extern UNK_TYPE gPrevPlanetSavedTeamShields[6];
extern s32 gTeamDamage[6];
extern u8 gNextPlanetPath; // next planet path
extern f32 gGroundLevel;
extern f32 D_ctx_80177950;
extern f32 D_ctx_80177968;
extern f32 D_ctx_80177970;
extern f32 gCsCamEyeX;
extern f32 gCsCamEyeY;
extern f32 gCsCamEyeZ;
extern f32 gCsCamAtX;
extern f32 gCsCamAtY;
extern f32 gCsCamAtZ;
extern Vec3f gPlayerCamEye;
extern Vec3f gPlayerCamAt;
extern bool gExpertMode;
extern s32 D_ctx_80177A10[10];
extern f32 D_ctx_80177A48[10];
extern s32 gCsFrameCount;
extern u8 D_ctx_80177A98;
extern u8 D_ctx_80177AB0;
extern u8 D_ctx_80177AC8;
extern s32 D_ctx_80177AE0;
extern s32 gMainController;
extern s32 D_ctx_80177B40;
extern PlanetId gCurrentPlanet; // D_ctx_80177B48 // Arrow pointer?
extern s32 D_ctx_80177B50[7];
extern s32 D_ctx_80177B70[7];
extern PlanetId D_ctx_80177B90[7];
extern s32 D_ctx_80177BB0[7];
extern s32 D_ctx_80177BD8[22]; // overruns D_ctx_80177C30?
extern s32 gPrevPlanetTeamShields[6];
extern s32 D_ctx_80177C58[6];
extern u8  gSoundMode;
extern s32 gVolumeSettings[3];
extern u16 gBgmSeqId;
extern u8  gLevelType;
extern s32 D_ctx_80177CA0;
extern UNK_TYPE F_80177CA8;
extern f32 D_ctx_80177CB0;
extern UNK_TYPE F_80177CB8;
extern f32 D_ctx_80177CC0;
extern f32 D_ctx_80177CC8;
extern f32 D_ctx_80177CE8;
extern f32 D_ctx_80177D08;
extern f32 D_ctx_80177D20;
extern f32 D_ctx_80177D38;
extern f32 D_ctx_80177D50;
extern f32 D_ctx_80177D68;
extern UNK_TYPE F_80177D80;
extern UNK_TYPE F_80177DE8;
extern s32 gGameFrameCount;
extern s32 D_ctx_80177DC8;
extern s32 D_ctx_80177E70;
extern s32 D_ctx_80177E78;
extern s32 gRingPassCount;
extern Vec3f D_ctx_80177E88;
extern Vec3f D_ctx_80177F10;
extern UNK_TYPE F_80178020;
extern s32 D_ctx_8017812C;
extern LevelId gCurrentLevel;
extern s32 gLevelStage;
extern s32 gBossActive;
extern s32 D_ctx_8017828C;
extern s32 D_ctx_80178294;
extern s32 gRadioState;
extern s32 D_ctx_801782A4;
extern s32 D_Timer_801782AC;
extern s32 D_Timer_801782B4;
extern s32 D_ctx_801782C0;
extern s32 D_ctx_801782C8;
extern s32 D_ctx_801782D0;
extern s32 D_ctx_801782D8;
extern UNK_TYPE F_801782E0;
extern s32 D_ctx_801782E8;
extern UNK_TYPE F_801782F0;
extern s32 D_ctx_801782F8;
extern s32 D_ctx_80178300;
extern u16* D_ctx_80178308;
extern ObjectInit* gLevelObjects;
extern s32 gFogRed;
extern s32 gFogGreen;
extern s32 gFogBlue;
extern s32 gFogAlpha;
extern s32 gFillScreenAlpha; // alpha something
extern s32 gFillScreenRed; // red something
extern s32 gFillScreenGreen; // green something
extern s32 gFillScreenBlue; // blue something
extern s32 gFillScreenAlphaTarget; // alpha target
extern s32 gFillScreenAlphaStep; // alpha step
extern s32 D_ctx_80178360; // 2 lights second color
extern s32 D_ctx_80178364;
extern s32 D_ctx_80178368;
extern f32 D_ctx_8017836C; // 2 lights second color brightness
extern f32 D_ctx_80178370; // Vec3f?
extern f32 D_ctx_80178374;
extern f32 D_ctx_80178378;
extern s32 D_ctx_8017837C;
extern u32 gPlayerFillScreenAlphas[4]; // player alphas
extern s32 gPlayerFillScreenReds[4]; // player reds
extern s32 gPlayerFillScreenGreens[4]; // player greens
extern s32 gPlayerFillScreenBlues[4]; // player blues
extern s32 D_ctx_801783C0[4];
extern f32 D_ctx_801783D0; // something x translate
extern f32 D_ctx_801783D4; // something y translate
extern s32 gFogNear; //near
extern s32 gFogFar; //far
extern UNK_TYPE F_801783E0[12];
extern s32 D_ctx_80178410;
extern f32 D_ctx_80178414;
extern f32 D_ctx_80178418;
extern UNK_TYPE F_8017841C;
extern f32 D_ctx_80178420;
extern f32 D_ctx_80178424;
extern f32 D_ctx_80178428;
extern f32 D_ctx_8017842C;
extern f32 D_ctx_80178430;
extern UNK_TYPE F_80178434;
extern UNK_TYPE F_80178438;
extern UNK_TYPE F_8017843C;
extern f32 D_ctx_80178440;
extern f32 D_ctx_80178444;
extern f32 D_ctx_80178448;
extern f32 D_ctx_80178450[3];
extern f32 D_ctx_80178460[3];
extern f32 D_ctx_80178470[3];
extern f32 gCameraShakeY;
extern s32 gCameraShake;
extern s32 D_ctx_80178484;
extern bool D_ctx_80178488;
extern UNK_TYPE F_8017848C;
extern UNK_TYPE F_80178490;
extern s32 D_ctx_80178494;
extern f32 D_ctx_80178498;
extern f32 D_ctx_8017849C;
extern f32 D_ctx_801784A0;
extern s32 D_ctx_801784A4;
extern UNK_TYPE F_801784A8;
extern s32 D_ctx_801784AC;
extern UNK_TYPE F_801784B0;
extern UNK_TYPE F_801784B4;
extern f32 D_ctx_801784B8; // effective Vec3f
extern f32 D_ctx_801784BC;
extern f32 D_ctx_801784C0;
extern f32 D_ctx_801784C4; // effective Vec3f
extern f32 D_ctx_801784C8;
extern f32 D_ctx_801784CC;
extern f32 D_ctx_801784D0; // effective Vec3f
extern f32 D_ctx_801784D4;
extern f32 D_ctx_801784D8;
extern s32 gLight1x; // Vec3i light direction
extern s32 gLight1y;
extern s32 gLight1z;
extern f32 D_ctx_801784E8;
extern f32 D_ctx_801784EC; // effective Vec3f?
extern f32 D_ctx_801784F0;
extern f32 D_ctx_801784F4;
extern f32 D_ctx_801784F8; // effective Vec3f
extern f32 D_ctx_801784FC;
extern f32 D_ctx_80178500;
extern s32 gLight2x; // Vec3i light direction alternate
extern s32 gLight2y;
extern s32 gLight2z;
extern f32 D_ctx_80178510;
extern UNK_TYPE F_801784514;
extern UNK_TYPE F_801784518;
extern UNK_TYPE F_80178451C;
extern f32 D_ctx_80178520; // effective Vec3f
extern f32 D_ctx_80178524;
extern f32 D_ctx_80178528;
extern UNK_TYPE F_80178452C;
extern UNK_TYPE F_801784530;
extern UNK_TYPE F_801784534;
extern f32 D_ctx_80178538;
extern f32 D_ctx_8017853C;
extern s32 D_ctx_80178540;
extern s32 D_ctx_80178544;
extern s32 gLight1R; // Color32 light color 1
extern s32 gLight1G;
extern s32 gLight1B;
extern s32 gAmbientR; // Color32 ambient color
extern s32 gAmbientG;
extern s32 gAmbientB;
extern UNK_TYPE F_801784560;
extern s32 gLight2R; // Color32 light color 2
extern s32 gLight2G;
extern s32 gLight2B;
extern s32 D_ctx_80178570; // Color32 light color 2 modifier?
extern s32 D_ctx_80178574;
extern s32 D_ctx_80178578;
extern s32 D_ctx_80161A70; // Color32?
extern s32 D_ctx_80161A74;
extern s32 D_ctx_80161A78;
extern s32 D_ctx_80161A7C;
extern s32 D_ctx_80161A80;
extern s32 D_ctx_80161A84;
extern s32 gGroundType;
extern s32 gSavedGroundType;
extern u8 gGoldRingCount[4];
extern u8 D_ctx_80161A94[4];
extern s32 gHitCount;
extern s32 gSavedHitCount;
extern s16 gLifeCount[4];
extern LaserStrength gLaserStrength[4];
extern s32 D_ctx_80161AB8;
extern UNK_TYPE F_80161AC0[16];
extern Object_80 gObjects80[50];
extern Sprite gSprites[40];
extern Actor gActors[60];
extern Boss gBosses[4];
extern Effect gEffects[100];
extern Item gItems[20];
extern PlayerShot gPlayerShots[16];
extern TexturedLine gTexturedLines[100];
extern RadarMark gRadarMarks[65];
extern BonusText gBonusText[10];
extern s32 D_ctx_80176550[2];
extern f32 D_ctx_80176558[2][100];
extern f32 D_ctx_80176878[2][100];
extern f32 D_ctx_80176B98[2][100];
extern f32 D_ctx_80176EB8[2][100];
extern f32 D_ctx_801771D8[2][100];
extern f32 D_ctx_80177500[2][100];
extern u16 gEnemyShotSpeed; // enemy shot speed?
extern u8 D_ctx_80177830; // show level complete status overlay
extern s32 gLevelStatusScreenTimer; // level clear related
extern s32 gLevelClearScreenTimer; // timer for mission accomplished scrren
extern s32 gBossHealthBar;
extern s32 D_ctx_80177850; // bonus text related. set to 15 but never read
extern s32 D_ctx_80177858[4];
extern s32 D_ctx_80177870[4];
extern s32 gHandicap[4];
extern VsStage gVersusStage;
extern s32 D_ctx_801778A4;
extern s32 D_ctx_801778AC;
extern s32 D_ctx_801778C8;
extern bool gVersusMode;
extern u16 gBoostButton[4];
extern u16 gBrakeButton[4];
extern u16 gShootButton[4];
extern u16 gBombButton[4];
extern f32 D_ctx_80177958[4];
extern s32 D_ctx_8017796C;
extern OSContPad* gInputHold;
extern OSContPad* gInputPress;
extern u8* D_ctx_80177984;
extern s32 D_ctx_80177990[4];
extern f32 D_ctx_801779A8[4];
extern u8 gPauseEnabled;
extern s32 gChargeTimers[4];
extern f32 D_ctx_801779E4;
extern f32 D_ctx_801779F4;
extern s32 D_Timer_80177A00[4];
extern s32 D_Timer_80177A38[4];
extern s32 D_Timer_80177A70[4];
extern s32 D_Timer_80177A88[4];
extern f32 D_ctx_80177AA0[4];
extern f32 D_ctx_80177AB8[4];
extern s32 D_ctx_80177AD0[4];
extern s32 D_ctx_80177AE8[4];
extern s32 D_ctx_80177B00[4][4];
extern u8 D_Timer_80177B44;
extern u8 D_ctx_80177B4C;
extern u8 D_ctx_80177B6C;
extern u8  gGreatFoxIntact;
extern u8 D_ctx_80177BAC;
extern u16 D_Timer_80177BD0[4];
extern u16 D_ctx_80177C30[4];
extern s32 D_ctx_80177C50;
extern s32 D_ctx_80177C70;
extern s32 D_ctx_80177C78;
extern s32 D_ctx_80177C8C;
extern s32 D_ctx_80177C94;
extern s32 D_ctx_80177C9C;
extern s32 D_ctx_80177CA4;
extern s32 D_ctx_80177CAC;
extern s32 D_ctx_80177CB4;
extern s32 D_ctx_80177CBC;
extern s32 D_ctx_80177CC4;
extern s32 gStarWolfTeamAlive[6];
extern s32 gSavedStarWolfTeamAlive[6];
extern s32 gRightWingHealth[4];
extern s32 gLeftWingHealth[4];
extern s32 D_ctx_80177D40[4];
extern s32 D_ctx_80177D58[4];
extern s32 D_ctx_80177D70[4];
extern s32 D_ctx_80177D88[4];
extern s32 gBombCount[4];
extern s32 D_ctx_80177DB8[4];
extern s32 D_ctx_80177DD0[4][10];
extern s32 D_ctx_80177E74;
extern s32 D_ctx_80177E7C;
extern s32 gChangeTo360;
extern Vec3f gTeamArrowsViewPos[10];
extern f32 D_ctx_80177F20[65];
extern f32 D_ctx_80178028[65];
extern f32 D_ctx_80178130[65];
extern u8 D_ctx_80178238[65];
extern Player* gPlayer;
extern f32* D_ctx_80178288;
extern f32* D_ctx_80178290;
extern u32* D_ctx_80178298;
extern UNK_TYPE F_801782A0;
extern Object_58* gObjects58;
extern UNK_TYPE F_801782B0;
extern s32 D_ctx_801782B8;
extern s32 D_ctx_801782BC;
extern PosRot* D_ctx_801782C4;
extern f32* D_ctx_801782CC;
extern f32* D_ctx_801782D4;
extern f32* D_ctx_801782DC;
extern f32* D_ctx_801782E4;
extern f32* D_ctx_801782EC;
extern UNK_TYPE F_801782F4;
extern s32 D_ctx_801782FC;
extern UNK_TYPE F_80178304;
extern UNK_TYPE F_8017830C;
extern UNK_TYPE F_80178314;
extern UNK_TYPE F_80178318;
extern UNK_TYPE F_8017831C;
extern UNK_TYPE F_80178324;
extern UNK_TYPE F_8017832C;
extern UNK_TYPE F_80178334;
extern UNK_TYPE F_8017833C;
extern UNK_TYPE F_80178344;
extern UNK_TYPE F_8017834C;


#endif
