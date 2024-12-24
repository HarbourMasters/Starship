#ifndef VARIABLES_H
#define VARIABLES_H

#include "sys.h"
#include "sf64level.h"
#include "sf64object.h"
#include "sf64player.h"

// fox_360
extern s32 gAllRangeSpawnEvent;

// fox_bg
extern u16 gStarColors[16];

// fox_boss
extern s32 gBossBgms[];

// fox_tank
extern Vec3f D_tank_800C9F2C;

// fox_display
extern s32 D_display_800CA220;
extern f32 gCamDistortion;
extern Actor* gTeamHelpActor;
extern s32 gTeamHelpTimer;

// fox_edata
extern f32 gZoEnergyBallHitbox[];
extern f32 gCubeHitbox100[];
extern f32 gCubeHitbox150[];
extern f32 gCubeHitbox200[];
extern f32 gCubeHitbox300[];
extern f32 gCubeHitbox400[];
extern f32 gItemRingCheckHitbox[];
extern f32 gNoHitbox[];
extern f32 gItemCheckpointHitbox[];
extern f32 gItemSupplyRingHitbox[];
extern f32 gMeteoWarpHitbox[];
extern f32 gItemPathChangeHitbox[];
extern f32 gItemLasersHitbox[];
extern f32 gItemBombHitbox[];
extern f32 gActorMissileSeekHitbox[];
extern f32 gMeMoraHitbox[];
extern f32 gTeamHitbox[];
extern f32 gActorAllRangeHItbox[];
extern f32 aWzMeteor1Hitbox[];
extern f32 aWzGateHitbox[];
extern f32 aWzPillar1Hitbox[];
extern f32 aWzPillar2Hitbox[];
extern ObjectInfo gObjectInfo[];
extern f32* D_edata_800CF964[];

// fox_edisplay
extern f32 D_edisplay_800CF9B0[];
extern Gfx* D_edisplay_800CFA54[];
extern Gfx* D_edisplay_800CFAC4[];
extern Gfx* D_edisplay_800CFADC[];
extern Gfx* D_edisplay_800CFB08[];
extern Gfx* D_edisplay_800CFB14[];
extern Gfx* D_edisplay_800CFB28[];
extern Gfx* D_edisplay_800CFB40[];
extern Gfx* D_edisplay_800CFB64[];
extern Gfx* D_edisplay_800CFB88[];
extern Gfx* D_edisplay_800CFBA8[];
extern Gfx* D_edisplay_800CFBE4[];
extern Gfx* D_edisplay_800CFC0C[];
extern Gfx* D_edisplay_800CFC40[];
extern Gfx* D_edisplay_800CFC50[];
extern Gfx* D_edisplay_800CFC64[];
extern Gfx* D_edisplay_800CFC7C[];
extern f32 D_edisplay_800CFCA0[];
extern f32 D_edisplay_800CFCCC[];
extern Gfx D_edisplay_800CFD80[];

// fox_enmy
extern ObjectInit* gLevelObjectInits[];
extern u32 gWarpRingSfx[9];

// fox_enmy2
extern s32 gTeamEventActorIndex[4];
extern s32 gCallVoiceParam;

// fox_hud
extern s16 D_hud_800D1970;

// fox_col2
extern CollisionHeader D_800D2B38[];
extern CollisionHeader2 D_800D2CA0[];

// fox_play
extern u8 gVenomHardClear;
extern u8 gLeveLClearStatus[30];

// fox_radio
extern s32 gRadioMsgPri;

// fox_360
extern s32 gAllRangeSupplyTimer;
extern s32 sStarWolfKillTimer;
extern s16 gStarWolfMsgTimer;
extern s32 gAllRangeWingRepairTimer;
extern s32 gAllRangeSuppliesSent;
extern f32 gSzMissileR;
extern f32 gSzMissileG;
extern f32 gSzMissileB;
extern u8 gKaKilledAlly;
extern u8 gKaAllyKillCount;
extern s32 gAllRangeCheckpoint;
extern s32 gAllRangeEventTimer;
extern s32 gAllRangeCountdown[3];
extern bool gShowAllRangeCountdown;
extern s32 gAllRangeFrameCount;
extern f32 gAllRangeCountdownScale;

// fox_bg
extern f32 gAndrossUnkAlpha;
extern u16 gBolseDynamicGround;
extern f32 gWarpZoneBgAlpha;
extern u8 D_bg_8015F964;
extern f32 D_bg_8015F968;
extern f32 D_bg_8015F96C;
extern f32 D_bg_8015F970;
extern s32 D_bg_8015F974;
extern s32 D_bg_8015F978;
extern s32 D_bg_8015F97C;
extern s32 D_bg_8015F980;
extern f32 D_bg_8015F984;

// fox_boss
extern s32 gBossFrameCount;

// fox_display
extern Vec3f D_display_801613B0[]; // static, here for reordering
extern Vec3f D_display_801613E0[]; // static, here for reordering
extern s16 gReflectY;
extern Matrix D_display_80161418[]; // static, here for reordering
extern Vec3f D_display_80161518[]; // static, here for reordering
extern Vec3f D_display_80161548[]; // static, here for reordering
extern Vec3f gLockOnTargetViewPos[];
extern f32 D_display_801615A8[];
extern f32 D_display_801615B8[];

// fox_edisplay
extern Vec3f D_edisplay_801615D0;

// fox_enmy
extern s32 D_enmy_Timer_80161670[4];
extern s32 gLastPathChange;
extern u8 gMissedZoSearchlight;

// fox_enmy2
extern s32 gCallTimer;

// fox_hud
extern s32 D_hud_80161704;
extern s32 D_hud_80161708;
extern s32 D_hud_8016170C;
extern s32 gRadarMissileAlarmTimer;
extern s32 gTotalHits; // 0x80161714 gTotalGameScore
extern f32 D_hud_80161720[3];
extern s32 gDisplayedHitCount;
extern s32 D_hud_80161730;
extern s32 gShowBossHealth; // 0x80161734

// fox_std_lib
extern char D_801619A0[];

// fox_play
extern u8 gSavedZoSearchlightStatus;
extern f32 gArwingSpeed;
extern s32 D_play_80161A58;
extern s32 D_play_80161A5C;
extern u16 gScreenFlashTimer;
extern u16 gDropHitCountItem;

//fox_radio
extern u16** gRadioMsgList;
extern s32 gRadioMsgListIndex;
extern s32 gRadioPrintPosX;
extern s32 gRadioPrintPosY;
extern f32 gRadioTextBoxPosX;
extern f32 gRadioTextBoxPosY;
extern f32 gRadioTextBoxScaleX;
extern f32 gRadioPortraitPosX;
extern f32 gRadioPortraitPosY;

// fox_versus
extern bool gVsMatchOver;
extern s32 gVsMatchState;
extern s32 D_versus_80178758;
extern s32 sUnlockLandmaster; // sUnlockLandmaster
extern s32 sUnlockOnFoot; // sUnlockOnFoot
extern s32 gVsCountdown[];

// gfx_data
extern u16 D_Tex_800DACB8[];
extern u16 D_Tex_800D99F8[];
extern u16 gTextCharPalettes[];
extern Gfx gRcpInitDL[];
extern Gfx aCoHighwayShadowDL[];
extern Gfx D_Gfx_800D9688[];
extern u8 D_Tex_800DB4B8[];
extern Gfx D_Gfx_800D94D0[];

extern OSTime osClockRate;

#define osViClock 0x02E6D354;

#endif // VARIABLES_H
