#include "prevent_context_reordering.h"
#include "sys.h"
#include "sf64level.h"
#include "sf64object.h"
#include "sf64player.h"

s32 gSceneId;
s32 gSceneSetup;
s32 D_ctx_80177824; // some sort of flag
s32 D_ctx_8017782C; // some sort of flag. all range related?
GameState gGameState;
s32 gNextGameStateTimer;
s32 gVsItemSpawnTimer;
OptionState gOptionMenuStatus;
s32 gPlayState;
s32 D_ctx_80177868; // some sort of state. pause-related? Also used by game over
LevelMode gLevelMode;
DrawMode gDrawMode;
s32 gPlayerNum;
s32 gCamCount;
s32 gTeamShields[6];
s32 gSavedTeamShields[6];
s32 gPrevPlanetSavedTeamShields[6];
s32 gTeamDamage[6];
u8 gMissionStatus;
f32 gGroundHeight;
f32 D_ctx_80177950; // Related to camera z-rotations? Only set to -1 in corneria intro, where it does nothing?
f32 gPlayerTurnRate;
f32 gPlayerTurnStickMod;
f32 gCsCamEyeX;
f32 gCsCamEyeY;
f32 gCsCamEyeZ;
f32 gCsCamAtX;
f32 gCsCamAtY;
f32 gCsCamAtZ;
Vec3f gPlayCamEye;
Vec3f gPlayCamAt;
bool gExpertMode;
s32 D_ctx_80177A10[10]; // work buffer
f32 D_ctx_80177A48[10]; // work buffer
s32 gCsFrameCount;
u8 gDrawGround; // some sort of flag. Used in background
u8 gDrawBackdrop;
u8 gAqDrawMode;
s32 gTitleState;
s32 gMainController;
s32 gMapState;
s32 gMissionNumber;
s32 gMissionTeamStatus[7];
s32 gMissionHitCount[7];
PlanetId gMissionPlanet[7];
s32 gMissionMedal[7];
#ifdef AVOID_UB
s32 gPlanetPathStatus[24];
#else
s32 gPlanetPathStatus[22]; // overruns gPrevPlanetTeamShields?
#endif
s32 gPrevPlanetTeamShields[6];
s32 D_ctx_80177C58[6]; // another saved team shields. maybe this is prev planet?
u8 gOptionSoundMode;
s32 gVolumeSettings[3];
u16 gBgmSeqId;
u8 gLevelType;
s32 gSavedObjectLoadIndex;
UNK_TYPE F_80177CA8;
f32 gSavedPathProgress;
UNK_TYPE F_80177CB8;
f32 gWaterLevel;
f32 gPathGroundScroll;
f32 gPathTexScroll;
f32 gPathVelZ;
f32 gPathProgress;
f32 gRadioPortraitScaleY;
f32 gRadioTextBoxScaleY;
f32 gRadioMsgRadioId;
UNK_TYPE F_80177D80;
UNK_TYPE F_80177DE8;
s32 gGameFrameCount;
s32 gObjectLoadIndex;
s32 gPrevEventActorIndex;
s32 gFormationLeaderIndex;
s32 gRingPassCount;
Vec3f gFormationInitRot;
Vec3f gFormationInitPos;
UNK_TYPE F_80178020;
s32 gGroundClipMode;
LevelId gCurrentLevel;
s32 gLevelPhase;
s32 gBossActive;
bool gKillEventActors;
s32 gUseDynaFloor;
s32 gRadioState;
s32 gCurrentRadioPortrait;
s32 gRadioStateTimer;
s32 gRadioMouthTimer;
u8 gLeveLClearStatus[30] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
s32 D_ctx_801782C0; // set to 0, never used
s32 D_ctx_801782C8; // set to 0, never used
s32 D_ctx_801782D0; // set to 0, never used
s32 gRadioMsgCharIndex;
UNK_TYPE F_801782E0;
s32 gRadioMsgId;
UNK_TYPE F_801782F0;
bool gMsgCharIsPrinting;
bool gHideRadio;
u16* gRadioMsg;
ObjectInit* gLevelObjects;
UNK_TYPE F_80178318;
s32 gFogRed;
s32 gFogGreen;
s32 gFogBlue;
s32 gFogAlpha;
s32 gFillScreenAlpha;
s32 gFillScreenRed;
s32 gFillScreenGreen;
s32 gFillScreenBlue;
s32 gFillScreenAlphaTarget;
s32 gFillScreenAlphaStep;
s32 gLight3R; // 2 lights second color
s32 gLight3G;
s32 gLight3B;
f32 gLight3Brightness; // 2 lights second color brightness
f32 gLight3x;          // Vec3f?
f32 gLight3y;
f32 gLight3z;
s32 gFadeoutType;
u32 gPlayerGlareAlphas[4];
s32 gPlayerGlareReds[4];
s32 gPlayerGlareGreens[4];
s32 gPlayerGlareBlues[4];
UNK_TYPE D_ctx_801783C0[4]; // unused. player alpha targets?
f32 gSunViewX;              // something x translate
f32 gSunViewY;              // something y translate
s32 gFogNear;               // near
s32 gFogFar;                // far
UNK_TYPE F_801783E0;
UNK_TYPE F_801783E4;
UNK_TYPE F_801783E8;
UNK_TYPE F_801783EC;
UNK_TYPE F_801783F0;
UNK_TYPE F_801783F4;
UNK_TYPE F_801783F8;
UNK_TYPE F_801783FC;
UNK_TYPE F_80178400;
UNK_TYPE F_80178404;
UNK_TYPE F_80178408;
UNK_TYPE F_8017840C;
UNK_TYPE P_800D31A0 = 0;
s32 gStarCount;
f32 gStarWarpDistortion;
f32 gCOComplete2CamRotY;
UNK_TYPE F_8017841C;
f32 gStarfieldX;
f32 gStarfieldY;
f32 gStarfieldRoll;
f32 gStarfieldScrollX; // starfield yaw?
f32 gStarfieldScrollY; // starfield roll?
UNK_TYPE F_80178434;
UNK_TYPE F_80178438;
UNK_TYPE F_8017843C;
f32 gBossDeathCamAtX; //
f32 gBossDeathCamAtY;
f32 gBossDeathCamAtZ;
f32 gCsTeamTargetsX[3]; // x positions of certain actors (teammates?)
f32 gCsTeamTargetsY[3]; // y positions of certain actors (teammates?)
f32 gCsTeamTargetsZ[3]; // z positions of certain actors (teammates?)
f32 gCameraShakeY;
s32 gCameraShake;
s32 D_ctx_80178484; // set to 100000 when pausing but not used
bool gLoadLevelObjects;
UNK_TYPE F_8017848C;
UNK_TYPE F_80178490;
#ifdef AVOID_UB
s32 D_ctx_80178494 = 0;
#else
s32 D_ctx_80178494;        // Torpedoes have this set to their unk_5C. Were they shot2s at some point?
#endif
f32 gShotHitPosZ;
f32 gShotHitPosX;
f32 gShotHitPosY;
s32 gZOSnakeWaypointCount;
UNK_TYPE F_801784A8;
GroundType gGroundType;
UNK_TYPE F_801784B0;
UNK_TYPE F_801784B4;

// light source 1. Used for most things
f32 gLight1xRot; // effective Vec3f
f32 gLight1yRot;
f32 gLight1zRot;
f32 gLight1xRotTarget; // effective Vec3f
f32 gLight1yRotTarget;
f32 gLight1zRotTarget;
f32 gEnvLightxRot; // effective Vec3f
f32 gEnvLightyRot;
f32 gEnvLightzRot;
s32 gLight1x; // Vec3i?
s32 gLight1y;
s32 gLight1z;
f32 gLight1rotStep;

// light source 2. used for Players
f32 gLight2xRot; // effective Vec3f
f32 gLight2yRot;
f32 gLight2zRot;
f32 gLight2xRotTarget; // effective Vec3f
f32 gLight2yRotTarget;
f32 gLight2zRotTarget;
s32 gLight2x; // Vec3i?
s32 gLight2y;
s32 gLight2z;
f32 gLight2rotStep;

// this section looks like a third light source. May have been for scenery shadows
UNK_TYPE F_801784514;
UNK_TYPE F_801784518;
UNK_TYPE F_80178451C;
f32 D_ctx_80178520; // effective Vec3f, set to env light rotation but unused
f32 D_ctx_80178524;
f32 D_ctx_80178528;
UNK_TYPE F_80178452C;
UNK_TYPE F_801784530;
UNK_TYPE F_801784534;
f32 D_ctx_80178538;

f32 D_ctx_8017853C;   // hitbox size modifier for player collisions. always 0.0f. seems out of place
s32 gLight2colorStep; // light 2 color step
s32 D_ctx_80178544;   // light 3 color step?

s32 gLight1R; // Color32 light color 1
s32 gLight1G;
s32 gLight1B;
s32 gAmbientR; // Color32 ambient color
s32 gAmbientG;
s32 gAmbientB;

UNK_TYPE F_80178560;

s32 gLight2R; // Color32 light color 2
s32 gLight2G;
s32 gLight2B;
s32 gLight2RTarget; // Color32 light color 2 modifier?
s32 gLight2GTarget;
s32 gLight2BTarget;

s32 D_ctx_80161A70; // unused Color32, perhaps for third light? start of bss
s32 D_ctx_80161A74;
s32 D_ctx_80161A78;
s32 D_ctx_80161A7C; // unused Color32, perhaps targets for third light?
s32 D_ctx_80161A80;
s32 D_ctx_80161A84;

GroundSurface gGroundSurface;
GroundSurface gSavedGroundSurface;
u8 gGoldRingCount[4];
u8 gSavedGoldRingCount[4];
s32 gHitCount;
s32 gSavedHitCount;
s16 gLifeCount[4];
LaserStrength gLaserStrength[4];
s32 gCullObjects;
UNK_TYPE F_80161AC0[4];
UNK_TYPE F_80161AD0[4];
UNK_TYPE F_80161AE0[4];
UNK_TYPE F_80161AF0[4];
UNK_TYPE P_800D31A4 = 0;
Scenery gScenery[50];
Sprite gSprites[40];
Actor gActors[60];
Boss gBosses[4];
Effect gEffects[100];
Item gItems[20];
PlayerShot gPlayerShots[16];
TexturedLine gTexturedLines[100];
RadarMark gRadarMarks[65];
BonusText gBonusText[10];
s32 gActor194Status[2];
f32 gActor194xPos[2][100];
f32 gActor194yPos[2][100];
f32 gActor194zPos[2][100];
f32 gActor194xRot[2][100];
f32 gActor194yRot[2][100];
f32 gActor194zRot[2][100];
UNK_TYPE P_800D31A8 = 0;
u16 gEnemyShotSpeed; // enemy shot speed?
u8 gShowLevelClearStatusScreen;
s32 gLevelStartStatusScreenTimer;
s32 gLevelClearScreenTimer; // timer for mission accomplished scrren
s32 gBossHealthBar;
s32 D_ctx_80177850;    // bonus text related. set to 15 but never read
s32 D_ctx_80177858[4]; // set to 3 but never used. related to VS mode customization?
PlayerForm gPlayerForms[4];
s32 gHandicap[4];
VsStage gVersusStage;
s32 gVsPointsToWin;
s32 gVsMatchType;
s32 gVsTimeTrialLimit;
bool gVersusMode;
u16 gBoostButton[4];
u16 gBrakeButton[4];
u16 gShootButton[4];
u16 gBombButton[4];
f32 D_ctx_80177958[4]; // set to 1.0f but never used
s32 gTeamLowHealthMsgTimer;
OSContPad* gInputHold;
OSContPad* gInputPress;
u8* gControllerRumble;
s32 D_ctx_80177990[4]; // these two are also rumble related
f32 D_ctx_801779A8[4];
u8 gPauseEnabled;
s32 gChargeTimers[4];
f32 gPathVelX;
f32 gPathVelY;
s32 gUturnDownTimers[4];
s32 gUturnBrakeTimers[4];
s32 gLoopDownTimers[4];
s32 gLoopBoostTimers[4];
f32 gMuzzleFlashScale[4];
f32 gShieldAlpha[4];
s32 gHasShield[4];
s32 gShieldTimer[4];
s32 gVsLockOnTimers[4][4];
u8 gStartAndrossFightTimer;
u8 gSoShieldsEmpty;
u8 gCoUturnCount;
u8 gGreatFoxIntact;
u8 gTiStartLandmaster;
u16 gControllerRumbleTimers[4];
u16 gPlayerScores[4];
s32 gCircleWipeFrame;
s32 D_ctx_80177C70; // sets camera field of view Y. initialized to 0 and never changed
s32 gTraining360MsgTimer;
s32 gTraining360MsgIndex;
s32 D_ctx_80177C94; // these save player parameters across the Venom -> Andross transition
s32 D_ctx_80177C9C;
s32 D_ctx_80177CA4;
s32 D_ctx_80177CAC;
s32 D_ctx_80177CB4;
s32 D_ctx_80177CBC;
s32 D_ctx_80177CC4;
s32 gStarWolfTeamAlive[6];
s32 gSavedStarWolfTeamAlive[6];
s32 gRightWingHealth[4];
s32 gLeftWingHealth[4];
s32 gRightWingFlashTimer[4];
s32 gLeftWingFlashTimer[4];
s32 gRightWingDebrisTimer[4];
s32 gLeftWingDebrisTimer[4];
s32 gBombCount[4];
s32 gVsPoints[4];
s32 gVsKills[4][10];
s32 gVsMatchOver;
s32 gVsMatchStart;
bool gChangeTo360;
Vec3f gTeamArrowsViewPos[10];
f32 D_ctx_80177F20[65]; // Seem to be an early implementation of RadarMark
f32 D_ctx_80178028[65];
f32 D_ctx_80178130[65];
u8 D_ctx_80178238[65];
Player* gPlayer;
f32* gStarOffsetsX;
f32* gStarOffsetsY;
u32* gStarFillColors;
UNK_TYPE F_801782A0;
Scenery360* gScenery360;
UNK_TYPE F_801782B0;
s32 gDrawSmallRocks;
s32 D_ctx_801782BC; // set to 0, never used
PosRot* gZOSnakePosRots;
f32* D_ctx_801782CC; // arrays used for dynamic floor
f32* D_ctx_801782D4;
f32* D_ctx_801782DC;
f32* D_ctx_801782E4;
f32* D_ctx_801782EC;
UNK_TYPE F_801782F4;
s32 gDynaFloorTimer; // timer related to dynamic floor
UNK_TYPE F_80178304;
UNK_TYPE F_8017830C;
UNK_TYPE F_80178314;
UNK_TYPE F_8017831C;
UNK_TYPE F_80178324;
UNK_TYPE F_8017832C;
UNK_TYPE F_80178334;
UNK_TYPE F_8017833C;
UNK_TYPE F_80178344;
UNK_TYPE F_8017834C;
