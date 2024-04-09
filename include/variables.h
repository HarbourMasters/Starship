#ifndef VARIABLES_H
#define VARIABLES_H

#include "sys.h"
#include "structs.h"
#include "sf64level.h"
#include "sf64object.h"
#include "sf64player.h"

// fox_360
extern s32 D_360_800C9B4C;

// fox_bg
extern u16 D_bg_800C9C3C[16];

// fox_boss
extern s32 D_boss_800C9E90[];

// fox_tank
extern Vec3f D_tank_800C9F2C;

// fox_display
extern s32 D_display_800CA220;
extern f32 D_display_800CA230;
extern Actor* D_display_800CA234;
extern s32 D_display_Timer_800CA238;

// fox_edata
extern f32 gActor241Hitbox[];
extern f32 gDefaultCubeHitbox100[];
extern f32 gDefaultCubeHitbox150[];
extern f32 gDefaultCubeHitbox200[];
extern f32 gDefaultCubeHitbox300[];
extern f32 gDefaultCubeHitbox400[];
extern f32 gItemRingCheckHitbox[];
extern f32 gHitboxNone[];
extern f32 gItemCheckpointHitbox[];
extern f32 gItemSupplyRingHitbox[];
extern f32 gMeteoWarpHitbox[];
extern f32 D_edata_800CBF8C[];
extern f32 gItemLasersHitbox[];
extern f32 gItemBombHitbox[];
extern f32 gActor190_191Hitbox[];
extern f32 gActor194HItbox[];
extern f32 gTeamHitbox[];
extern f32 gActorAllRangeHItbox[];
extern f32 gWarpZoneEvent94Hitbox[];
extern f32 gWarpZoneEvent96Hitbox[];
extern f32 gWarpZoneEvent92Hitbox[];
extern f32 gWarpZoneEvent93Hitbox[];
extern ObjectInfo D_edata_800CC124[];
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
extern u32 D_enmy_800CFF54[9];

// fox_enmy2
extern s32 D_enmy2_800CFF80[4];
extern s32 gCallVoiceParam;

// fox_hud
extern s16 D_hud_800D1970;

// fox_A4290
extern CollisionHeader D_800D2B38[];
extern CollisionHeader2 D_800D2CA0[];

// fox_play
extern u8 D_play_800D2F68;
extern u8 D_play_800D3180[30];

// fox_radio
extern s32 gCurrentMsgPri;

// fox_360
extern s32 gAllRangeSupplyTimer;
extern s32 sStarWolfKillTimer;
extern s16 gStarWolfMsgTimer;
extern s32 gAllRangeWingRepairTimer;
extern s32 gAllRangeWingRepairSent;
extern f32 gSzMissileR;
extern f32 gSzMissileG;
extern f32 gSzMissileB;
extern u8 gKaKilledAlly;
extern u8 gKaAllyKillCount;
extern s32 gAllRangeCheckpoint;
extern s32 gAllRangeEventTimer;
extern s32 gAllRangeCountdown[3];
extern s32 gShowAllRangeCountdown;
extern s32 gAllRangeFrameCount;
extern f32 gAllRangeCountdownScale;

// fox_bg
extern f32 D_bg_800C9C30;
extern u16 D_bg_800C9C34;
extern f32 D_bg_8015F960;
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
extern Vec3f D_display_80161578[];
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
extern s32 D_hud_80161710;
extern s32 gTotalHits; // 0x80161714 gTotalGameScore
extern f32 D_hud_80161720[3];
extern s32 gDisplayedHitCount;
extern s32 D_hud_80161730;
extern s32 gShowBossHealth; // 0x80161734

// fox_play
extern u8 gSavedZoSearchlightStatus;
extern f32 D_play_80161A54;
extern s32 D_play_80161A58;
extern s32 D_play_80161A5C;
extern u16 gScreenFlashTimer;
extern u16 gDropHitCountItem;

//fox_radio
extern u16** D_radio_80178720;
extern s32 D_radio_80178724;
extern s32 D_radio_80178728;
extern s32 D_radio_8017872C;
extern f32 D_radio_80178730;
extern f32 D_radio_80178734;
extern f32 D_radio_80178738;
extern f32 D_radio_8017873C;
extern f32 D_radio_80178740;

// fox_versus
extern s32 D_versus_80178750;
extern s32 D_versus_80178754;
extern s32 D_versus_80178758;
extern s32 sUnlockLandmaster; // sUnlockLandmaster
extern s32 sUnlockOnFoot; // sUnlockOnFoot
extern s32 D_versus_80178768[];

// gfx_data
extern u16 D_Tex_800DACB8[][32];
extern u16 D_Tex_800D99F8[];
extern u16 gTextCharPalettes[];
extern Gfx gRcpInitDL[];
extern Gfx D_Gfx_800DAC20[];
extern Gfx D_Gfx_800D9688[];
extern u8 D_Tex_800DB4B8[];
extern Gfx D_Gfx_800D94D0[];

extern OSTime osClockRate;

#define osViClock 0x02E6D354;

#endif // VARIABLES_H
