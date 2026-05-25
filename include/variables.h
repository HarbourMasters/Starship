#ifndef VARIABLES_H
#define VARIABLES_H

#include "sys.h"
#include "sf64level.h"
#include "sf64object.h"
#include "sf64player.h"

// fox_360
extern_s s32 gAllRangeSpawnEvent;

// fox_bg
extern_s u16 gStarColors[16];

// fox_boss
extern_s s32 gBossBgms[];

// fox_tank
extern_s Vec3f D_tank_800C9F2C;

// fox_display
extern_s s32 D_display_800CA220;
extern_s f32 gCamDistortion;
extern_s Actor* gTeamHelpActor;
extern_s s32 gTeamHelpTimer;

// fox_edata
extern_s f32 gZoEnergyBallHitbox[];
extern_s f32 gCubeHitbox100[];
extern_s f32 gCubeHitbox150[];
extern_s f32 gCubeHitbox200[];
extern_s f32 gCubeHitbox300[];
extern_s f32 gCubeHitbox400[];
extern_s f32 gItemRingCheckHitbox[];
extern_s f32 gNoHitbox[];
extern_s f32 gItemCheckpointHitbox[];
extern_s f32 gItemSupplyRingHitbox[];
extern_s f32 gMeteoWarpHitbox[];
extern_s f32 gItemPathChangeHitbox[];
extern_s f32 gItemLasersHitbox[];
extern_s f32 gItemBombHitbox[];
extern_s f32 gActorMissileSeekHitbox[];
extern_s f32 gMeMoraHitbox[];
extern_s f32 gTeamHitbox[];
extern_s f32 gActorAllRangeHItbox[];
extern_s f32 aWzMeteor1Hitbox[];
extern_s f32 aWzGateHitbox[];
extern_s f32 aWzPillar1Hitbox[];
extern_s f32 aWzPillar2Hitbox[];
extern_s ObjectInfo gObjectInfo[];
extern_s f32* D_edata_800CF964[];

// fox_edisplay
extern_s f32 D_edisplay_800CF9B0[];
extern_s Gfx* D_edisplay_800CFA54[];
extern_s Gfx* D_edisplay_800CFAC4[];
extern_s Gfx* D_edisplay_800CFADC[];
extern_s Gfx* D_edisplay_800CFB08[];
extern_s Gfx* D_edisplay_800CFB14[];
extern_s Gfx* D_edisplay_800CFB28[];
extern_s Gfx* D_edisplay_800CFB40[];
extern_s Gfx* D_edisplay_800CFB64[];
extern_s Gfx* D_edisplay_800CFB88[];
extern_s Gfx* D_edisplay_800CFBA8[];
extern_s Gfx* D_edisplay_800CFBE4[];
extern_s Gfx* D_edisplay_800CFC0C[];
extern_s Gfx* D_edisplay_800CFC40[];
extern_s Gfx* D_edisplay_800CFC50[];
extern_s Gfx* D_edisplay_800CFC64[];
extern_s Gfx* D_edisplay_800CFC7C[];
extern_s f32 D_edisplay_800CFCA0[];
extern_s f32 D_edisplay_800CFCCC[];
extern_s Gfx D_edisplay_800CFD80[];

// fox_enmy
extern_s ObjectInit* gLevelObjectInits[];
extern_s u32 gWarpRingSfx[9];

// fox_enmy2
extern_s s32 gTeamEventActorIndex[4];
extern_s s32 gCallVoiceParam;

// fox_hud
extern_s s16 D_hud_800D1970;

// fox_col2
extern_s CollisionHeader D_800D2B38[];
extern_s CollisionHeader2 D_800D2CA0[];

// fox_play
extern_s u8 gVenomHardClear;
extern_s u8 gLeveLClearStatus[30];

// fox_radio
extern_s s32 gRadioMsgPri;

// fox_360
extern_s s32 gAllRangeSupplyTimer;
extern_s s32 sStarWolfKillTimer;
extern_s s16 gStarWolfMsgTimer;
extern_s s32 gAllRangeWingRepairTimer;
extern_s s32 gAllRangeSuppliesSent;
extern_s f32 gSzMissileR;
extern_s f32 gSzMissileG;
extern_s f32 gSzMissileB;
extern_s u8 gKaKilledAlly;
extern_s u8 gKaAllyKillCount;
extern_s s32 gAllRangeCheckpoint;
extern_s s32 gAllRangeEventTimer;
extern_s s32 gAllRangeCountdown[3];
extern_s bool gShowAllRangeCountdown;
extern_s s32 gAllRangeFrameCount;
extern_s f32 gAllRangeCountdownScale;

// fox_bg
extern_s f32 gAndrossUnkAlpha;
extern_s u16 gBolseDynamicGround;
extern_s f32 gWarpZoneBgAlpha;
extern_s u8 D_bg_8015F964;
extern_s f32 D_bg_8015F968;
extern_s f32 D_bg_8015F96C;
extern_s f32 D_bg_8015F970;
extern_s s32 D_bg_8015F974;
extern_s s32 D_bg_8015F978;
extern_s s32 D_bg_8015F97C;
extern_s s32 D_bg_8015F980;
extern_s f32 D_bg_8015F984;

// fox_boss
extern_s s32 gBossFrameCount;

// fox_display
extern_s Vec3f D_display_801613B0[]; // static, here for reordering
extern_s Vec3f D_display_801613E0[]; // static, here for reordering
extern_s s16 gReflectY;
extern_s Matrix D_display_80161418[]; // static, here for reordering
extern_s Vec3f D_display_80161518[]; // static, here for reordering
extern_s Vec3f D_display_80161548[]; // static, here for reordering
extern_s Vec3f gLockOnTargetViewPos[];
extern_s f32 D_display_801615A8[];
extern_s f32 D_display_801615B8[];

// fox_edisplay
extern_s Vec3f D_edisplay_801615D0;

// fox_enmy
extern_s s32 D_enmy_Timer_80161670[4];
extern_s s32 gLastPathChange;
extern_s u8 gMissedZoSearchlight;

// fox_enmy2
extern_s s32 gCallTimer;

// fox_hud
extern_s s32 D_hud_80161704;
extern_s s32 D_hud_80161708;
extern_s s32 D_hud_8016170C;
extern_s s32 gRadarMissileAlarmTimer;
extern_s s32 gTotalHits; // 0x80161714 gTotalGameScore
extern_s f32 D_hud_80161720[3];
extern_s s32 gDisplayedHitCount;
extern_s s32 D_hud_80161730;
extern_s s32 gShowBossHealth; // 0x80161734

// fox_std_lib
extern_s char D_801619A0[];

// fox_play
extern_s u8 gSavedZoSearchlightStatus;
extern_s f32 gArwingSpeed;
extern_s s32 D_play_80161A58;
extern_s s32 D_play_80161A5C;
extern_s u16 gScreenFlashTimer;
extern_s u16 gDropHitCountItem;

//fox_radio
extern_s u16** gRadioMsgList;
extern_s s32 gRadioMsgListIndex;
extern_s s32 gRadioPrintPosX;
extern_s s32 gRadioPrintPosY;
extern_s f32 gRadioTextBoxPosX;
extern_s f32 gRadioTextBoxPosY;
extern_s f32 gRadioTextBoxScaleX;
extern_s f32 gRadioPortraitPosX;
extern_s f32 gRadioPortraitPosY;

// fox_versus
extern_s bool gVsMatchOver;
extern_s s32 gVsMatchState;
extern_s s32 D_versus_80178758;
extern_s s32 sUnlockLandmaster; // sUnlockLandmaster
extern_s s32 sUnlockOnFoot; // sUnlockOnFoot
extern_s s32 gVsCountdown[];

// gfx_data
extern_s u16 D_Tex_800DACB8[];
extern_s u16 D_Tex_800D99F8[];
extern_s u16 gTextCharPalettes[];
extern_s Gfx gRcpInitDL[];
extern_s Gfx aCoHighwayShadowDL[];
extern_s Gfx D_Gfx_800D9688[];
extern_s u8 D_Tex_800DB4B8[];
extern_s Gfx D_Gfx_800D94D0[];

extern_s OSTime osClockRate;

#define osViClock 0x02E6D354;

#endif // VARIABLES_H
