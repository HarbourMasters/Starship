#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "sys.h"
#include "sf64object.h"
#include "sf64player.h"
#include "sf64mesg.h"

// fox_360
void AllRange_FortunaIntro(Player*);
void AllRange_GetStarWolfHits(Actor*);
void AllRange_DrawCountdown(void);
void Boss309_Update(Boss*);
void Boss309_Draw(Boss*);
void Boss310_Update(Boss*);
void Boss310_Draw(Boss*);
void Actor271_Update(Actor*);
void Actor271_Draw(Actor*);
void Actor272_Update(Actor*);
void Actor272_Draw(Actor*);
bool AllRange_PlayMessage(u16*, RadioCharacterId);
void AllRange_GreatFoxRepair(Player*);
void AllRange_ClearRadio(void);
void ActorAllRange_SetShadowData(Actor* this);
void ActorAllRange_SpawnTeam(void);
void ActorAllRange_PlayMessage(u16* msg, RadioCharacterId character);
void ActorAllRange_UpdateStarWolfEvents(Actor*);
void ActorAllRange_UpdateEvemyEvents(Actor*);
void ActorAllRange_ApplyDamage(Actor*);
bool func_360_80031900(Actor*);
void ActorAllRange_Update(Actor* this);
void ActorAllRange_Draw(Actor* this);

//fox_beam
void PlayerShot_CollisionCheck(PlayerShot* shot);
void PlayerShot_Impact(PlayerShot* shot);
void PlayerShot_SpawnEffect351(f32 xPos, f32 yPos, f32 zPos);
void PlayerShot_Initialize(PlayerShot*);
void PlayerShot_SpawnEffect344(f32, f32, f32, f32, f32, f32, f32, f32, f32, s32, s32);
void PlayerShot_UpdateAll(void);
void PlayerShot_DrawAll(void);

// fox_bg
void Background_DrawStarfield(void);
void Background_DrawPartialStarfield(s32, s32);
void Background_DrawBackdrop(void);
void Background_DrawSun(void);
void Background_DrawLensFlare(void);
void Background_dummy_80040CDC(void);
void Background_DrawGround(void);

// fox_boss
void Boss_AwardBonus(Boss* boss);
void Boss299_Init(Boss* boss);
void Boss299_Update(Boss* boss);
void Boss299_Draw(Boss* boss);
void Boss300_Init(Boss* boss);
void Boss300_Update(Boss* boss);
void Boss300_Draw(Boss* boss);
void Boss_SpawnDebris(f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, s32, s32);
void Boss_CompleteLevel(Player* player, f32 xPos, f32 yPos, f32 zPos);

// fox_tank
void Player_UpdateTankCamOnRails(Player* player);
void func_tank_800444BC(Player* player);
void func_tank_80044868(Player*);
void func_tank_80045130(Player*);
void func_tank_80045678(Player*);
void func_tank_80045E7C(Player*);
void Tank_UpdateOnRails(Player* player);
void func_tank_80046358(Player*);

// fox_demo
void Cutscene_KillPlayer(Player*);
void func_demo_80048AC0(TeamId teamId);
void Cutscene_EnterWarpZone(Player*);
void Cutscene_LevelStart(Player*);
void func_demo_8004AA84(void);
void Cutscene_AllRangeMode(Player*);
void Cutscene_LevelComplete(Player*);
void Cutscene_UTurn(Player*);
void Cutscene_KillPlayer(Player* player);
void Cutscene_PlayerDown(Player*);
void ActorCutscene_Update(Actor*);
void ActorCutscene_Draw(Actor*);
void Cutscene_DrawGreatFox(void);

// fox_display
void func_display_80053658(WingInfo*);
void Play_DrawEngineGlow(s32);
void func_display_80057814(Player*);
void Play_Draw(void);

// fox_edata
void func_edata_800594F0(Scenery*);
void func_edata_800595D0(Scenery*);
void Object_ApplyWaterDistortion(void);
void func_edata_800596B0(Actor*);

// fox_edisplay
void Graphics_SetScaleMtx(f32);
void Sprite168_Draw(Sprite*);
void Actor201_Draw(Actor*);
void Actor202_Draw(Actor*);
void MeteoTunnel_Draw(Scenery*);
void Scenery_DrawTitaniaBones(Scenery*);
void Scenery42_Draw(Scenery*);
void Actor196_Draw(Actor*);
void Sprite167_Draw(Sprite*);
void FogShadow_Draw(Sprite*);
void func_edisplay_80059F68(Scenery*);
void func_edisplay_80059FDC(Scenery*);
void ActorDebris_Draw(Actor*);
void Actor_DrawEngineAndContrails(Actor*);
void Actor_DrawEngineGlow(Actor*, s32);
void func_edisplay_8005B388(Actor*);
void func_edisplay_8005B6A4(Actor*);
void func_edisplay_8005B71C(Actor*);
void func_edisplay_8005B7CC(Actor*);
void func_edisplay_8005B848(Actor*);
void func_edisplay_8005B9A4(Actor*);
void func_edisplay_8005BA30(Actor*);
void ItemCheckpoint_Draw(Item*);
void ItemSilverRing_Draw(Item*);
void ItemSilverStar_Draw(Item*);
void ItemGoldRing_Draw(Item*);
void ItemBomb_Draw(Item*);
void ItemLasers_Draw(Item*);
void ItemMeteoWarp_Draw(Item*);
void Object_ClampSfxSource(f32*);
void Object_SetSfxSourceToPos(f32*, Vec3f*);
void Object_UpdateSfxSource(f32*);
void Object_SetSfxSourceToView(f32*, Vec3f*);
void Display_SetSecondLight(Vec3f*);
bool func_edisplay_8005F9DC(Vec3f*);

// fox_enmy
void Object_Draw(s32 );
void Effect_Draw(u8 );
void TexturedLine_Draw(void);
void TexturedLine_DrawPath(s32);
void Object_PlayerSfx(f32* , u32 , s32 );
void Object_Kill(Object*, f32*);
bool func_enmy_80060FE4(Vec3f*, f32);
void Object_SetInfo(ObjectInfo* info, u32 objId);
void Scenery_Initialize(Scenery*);
void Sprite_Initialize(Sprite*);
void Actor_Initialize(Actor*);
void Boss_Initialize(Boss*);
void Item_Initialize(Item*);
void Effect_Initialize(Effect*);
void func_enmy_80061B68(void);
void func_enmy_80061CD0(void);
void func_enmy_80061E48(Actor* , f32 , f32 , f32 );
void ActorEvent_Load(Actor* , ObjectInit* , s32 );
void Object_Load(ObjectInit* , f32 , f32 , f32 , f32 );
void func_enmy_80062568(void);
void func_enmy_80062B60(f32 xPos, f32 zPos, s32 state, f32 scale);
void func_enmy_80062C38(f32, f32);
bool Object_CheckHitboxCollision(Vec3f* pos, f32* hitboxData, Object* obj, f32 xRot, f32 yRot, f32 zRot);
bool Object_CheckSingleHitbox(Vec3f*, f32*, Vec3f*);
bool Object_CheckPolyCollision(Vec3f* , Vec3f* , ObjectId , Object* );
s32 Object_CheckCollision(s32 , Vec3f* , Vec3f* , s32 );
void Scenery_UpdateTitaniaBones(Scenery*);
void func_enmy_800654E4(Object*);
void func_enmy_800656D4(Actor*);
void func_enmy_800660F0(Actor*);
void Actor_Despawn(Actor*);
void func_enmy_8006654C(Actor*);
void func_enmy_8006684C(Actor*);
void func_enmy_800669A0(Actor*);
void func_enmy_80066A80(Actor*);
void func_enmy_80066C00(Scenery*);
void func_enmy_80066D5C(Scenery*);
void Sprite167_Update(Sprite*);
void func_enmy_80066EA8(Scenery*);
void Item_CheckBounds(Item*);
void Item_SpinPickup(Item*);
void Actor_SpawnDebris70(f32, f32, f32, f32, f32, f32, f32, f32);
void ActorSupplies_Update(Actor*);
void ActorSupplies_Draw(Actor*);
void func_enmy_80067A40(void);
void Item1up_Update(Item*);
void ItemPickup_Update(Item*);
void ItemLasers_Update(Item*);
void ItemSupplyRing_Update(Item*);
void ItemSilverStar_Update(Item*);
void ItemGoldRing_Update(Item*);
void ItemWingRepair_Update(Item*);
void ItemMeteoWarp_Update(Item*);
void ItemCheckpoint_Update(Item*);
void ItemRingCheck_Update(Item*);
void ItemPathChange_Update(Item*);
void Sprite_UpdateDoodad(Sprite*);
void Object_Dying(s32, ObjectId);
void Effect_Move(Effect*);
void Actor_Move(Actor*);
void Boss_Move(Boss*);
void Scenery_Move(Scenery*);
void Sprite_Move(Sprite*);
void Item_Move(Item*);
void Actor_Update(Actor*);
void Boss_Update(Boss*);
void Scenery_Update(Scenery*);
void Sprite_Update(Sprite*);
void Item_Update(Item*);
void Effect_Update(Effect*);
void TexturedLine_Update(TexturedLine*);
void TexturedLine_UpdateAll(void);
void Object_Update(void);

//fox_enmy2
void Actor237_Update(Actor*);
void Actor237_Draw(Actor*);
void Scenery54_Update(Scenery*);
void Actor201_Update(Actor*);
void Actor202_Update(Actor*);
void Actor194_Update(Actor*);
void Actor194_Dying(Actor*);
void Actor194_Draw(Actor*);
void Scenery42_Update(Scenery*);
void Actor196_Update(Actor*);
void ActorDebris_Update(Actor*);
void MeteoTunnel_Update(Scenery*);
void Actor_SetupPlayerShot(PlayerShotId, PlayerShot*, s32, f32, f32, f32, f32, f32, f32, f32, f32, f32);
void Actor_SpawnPlayerLaser(s32, f32, f32, f32, f32, f32, f32, f32, f32, f32);
void Actor_SpawnGreatFoxLaser(s32 actorId, f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 xRot, f32 yRot,
                   f32 zRot);
void ActorEvent_SpawnEffect347(f32 xPos, f32 yPos, f32 zPos, f32 scale1);
void ActorEvent_8006F254(Actor*);
void ActorEvent_Update(Actor*);
s32 Scenery111_Draw(Scenery*);
void ActorEvent_Draw(Actor*);
void func_enmy2_800763A4(Actor*);
void ActorEvent_Dying(Actor*);
void Actor234_Update(Actor*);
void Actor234_Draw(Actor*);

// fox_effect
s32 func_effect_80081B24(f32 xPos, f32 yPos, f32 zPos, f32 scale2);
s32 BonusText_Display(f32 xPos, f32 yPos, f32 zPos, s32 hits);
void BonusText_Update(void);
void BonusText_DrawAll(void);
Effect* func_effect_8007783C(ObjectId objId);
void func_effect_8007797C(f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 scale2);
void func_effect_80077A00(Effect* );
void func_effect_80077A7C(Effect* );
void func_effect_80077B78(Effect* );
void func_effect_80077B84(Effect* );
void func_effect_80078038(Effect* );
void func_effect_800780F8(Effect* );
void func_effect_800783C0(Effect* );
void func_effect_80078438(Effect* );
void func_effect_800784B4(Effect* );
void func_effect_80078550(Effect* );
void func_effect_80078604(Effect* );
void func_effect_8007868C(Effect* );
void func_effect_8007879C(Effect* );
void func_effect_800788B0(Effect* );
void func_effect_80078A64(Effect* );
void func_effect_80078AEC(Effect* );
void func_effect_80078B8C(Effect*);
void func_effect_80078BE0(Effect* );
void func_effect_80078C84(Effect* );
void func_effect_80078CE8(Effect* );
void func_effect_80078E50(f32 xPos, f32 yPos, f32 zPos, f32 scale2);
void func_effect_80078EBC(Effect* );
void func_effect_80078F78(Effect* );
void func_effect_800794CC(f32 xPos, f32 yPos, f32 zPos, f32 scale2);
void func_effect_8007953C(f32 xPos, f32 yPos, f32 zPos, f32 scale2);
void func_effect_800795AC(f32 xPos, f32 yPos, f32 zPos, f32 scale2);
void func_effect_80079618(f32 xPos, f32 yPos, f32 zPos, f32 scale2);
void func_effect_8007968C(Effect*);
void func_effect_800798F0(Effect* );
void func_effect_8007A28C(Effect* );
void func_effect_8007A3C0(Effect* );
void func_effect_8007A568(f32 xPos, f32 yPos, f32 zPos, f32 scale1);
void func_effect_8007A5F8(Effect* , Vec3f* pos, u32 sfxId);
void func_effect_8007A6F0(Vec3f* pos, s32 sfxId);
void func_effect_8007A748(Effect*);
bool func_effect_8007A774(Player*, Effect*, f32);
void func_effect_8007A900(f32 xPos, f32 yPos, f32 zPos, f32 scale1, u8, u8, u16);
void func_effect_8007A994(Effect*);
void func_effect_8007AA60(Effect*);
void func_effect_8007AB50(Effect*);
void func_effect_8007ACE0(f32 xPos, f32 yPos, f32 zPos, f32 scale2, f32 scale1, f32 yRot);
void func_effect_8007ADF4(f32 xPos, f32 yPos, f32 zPos, f32 scale2, f32 scale1);
void func_effect_8007AFD0(f32 xPos, f32 zPos, f32 xVel, f32 zVel, f32 scale1);
void func_effect_8007B040(Effect*);
void func_effect_8007B0F4(Effect*);
void func_effect_8007B228(f32 xPos, f32 yPos, f32 zPos, f32 scale1);
void func_effect_8007B344(f32 xPos, f32 yPos, f32 zPos, f32 scale1, s32 );
void func_effect_8007B3B8(Effect*);
void func_effect_8007B550(f32 xPos, f32 yPos, f32 zPos, f32 scale1, s32 );
void func_effect_8007B5C0(Effect*);
void func_effect_8007B62C(Effect*);
void func_effect_8007B670(Effect*);
void func_effect_8007B67C(Effect*);
void func_effect_8007B758(Effect*);
void func_effect_8007B8F8(f32 xPos, f32 yPos, f32 zPos, f32 scale2);
void func_effect_8007B960(Effect*);
void func_effect_8007BC7C(f32 xPos, f32 yPos, f32 zPos, f32 scale2);
void func_effect_8007BCE8(Effect*);
void func_effect_8007B9DC(Effect*);
void func_effect_8007BDE0(Effect*);
void func_effect_8007BE54(Effect*);
void func_effect_8007BEE8(Effect*);
void func_effect_8007BFFC(f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 scale2, s32 timer50);
void func_effect_8007C120(f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 scale2, s32 timer50);
void func_effect_8007C250(Effect*);
void func_effect_8007C484(f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 scale2, s32 arg7);
void func_effect_8007C50C(Effect*);
void func_effect_8007C688(f32 xPos, f32 yPos, f32 zPos, f32 scale2, s32 timer50);
void func_effect_8007C8C4(Effect*);
void func_effect_8007C85C(f32 xPos, f32 yPos, f32 zPos, f32 scale2);
void func_effect_8007C9E0(Effect*);
void func_effect_8007CAF0(Effect*);
void func_effect_8007CF30(f32 xPos, f32 yPos, f32 zPos, f32 scale2);
void func_effect_8007D074(f32 xPos, f32 yPos, f32 zPos, f32 scale2);
void func_effect_8007D0E0(f32 xPos, f32 yPos, f32 zPos, f32 scale2);
void func_effect_8007D10C(f32 xPos, f32 yPos, f32 zPos, f32 scale2);
void func_effect_8007D1E0(f32 xPos, f32 yPos, f32 zPos, f32 scale2);
void func_effect_8007D24C(f32 xPos, f32 yPos, f32 zPos, f32 scale2);
void func_effect_8007D2C8(f32 xPos, f32 yPos, f32 zPos, f32 scale2);
void func_effect_8007D2F4(Effect*);
void func_effect_8007D55C(Effect*);
void func_effect_8007D748(Effect*);
void func_effect_8007D8A8(Effect*);
void func_effect_8007D9DC(f32 xPos, f32 yPos, f32 zPos, f32 scale2, f32 scale1, s32 timer50);
void func_effect_8007DA58(Effect*);
void func_effect_8007DAE4(Effect*);
void func_effect_8007DB70(Effect*);
void func_effect_8007DED4(Effect*);
void func_effect_8007E014(Effect*);
void func_effect_8007E258(Effect*);
void func_effect_8007E298(Effect*);
void func_effect_8007E330(Effect*);
void func_effect_8007E3E4(Effect*);
void func_effect_8007E45C(Effect*);
void func_effect_8007E5CC(Effect*);
void func_effect_8007E648(Effect*);
void func_effect_8007E93C(Effect* effect, u32 objId, f32 xPos, f32 yPos, f32 zPos, f32 speed);
void func_effect_8007EE68(ObjectId objId, Vec3f* pos, Vec3f* rot, Vec3f* arg3, Vec3f* arg4, f32 scale2);
void func_effect_8007F04C(ObjectId objId, f32 xPos, f32 yPos, f32 zPos, f32 xRot, f32 yRot, f32 zRot, f32 unkX, f32 unkY, f32 unkZ, f32 xVel, f32 yVel, f32 zVel, f32 scale2);
void func_effect_8007F11C(ObjectId objId, f32 xPos, f32 yPos, f32 zPos, f32 speed);
void func_effect_8007F20C(ObjectId objId, f32 xPos, f32 yPos, f32 zPos, f32 speed);
void func_effect_8007F438(Effect*);
void func_effect_8007F6B0(Effect*);
void func_effect_8007F958(Effect*);
void func_effect_8007FBE0(Effect*);
void func_effect_8007FE88(Effect*);
bool func_effect_8007FD84(Effect*);
void func_effect_800802B8(Effect*);
void func_effect_800802D8(Effect*);
void func_effect_800802F8(Effect*);
void func_effect_80080360(Effect*);
void func_effect_8008040C(Effect*);
void func_effect_8008092C(Effect*);
void func_effect_80080ACC(Effect*);
void func_effect_80080D04(Effect*);
void func_effect_800815DC(void);
void func_effect_80081A8C(f32 xPos, f32 yPos, f32 zPos, f32 scale2, s32 arg4);
void func_effect_80081BEC(f32 xPos, f32 yPos, f32 zPos, f32 scale2, s32 arg4);
void func_effect_80081C5C(Effect*);
void func_effect_80082F78(Effect*);
void func_effect_8008377C(f32, f32, f32, f32, f32);
void func_effect_800837EC(Effect*);
void func_effect_80083B8C(Effect*);
void func_effect_80083C70(Effect* effect, f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 arg7, s32 arg8);
void func_effect_80083D2C(f32 xPos, f32 yPos, f32 zPos, f32 srcZ);
void func_effect_80083FA8(Effect*);
void func_effect_80084194(Effect*);

// fox_fade
void Wipe_Draw(WipeMode mode, s32 frame);

// fox_hud
void func_hud_80084B94(s32);
void func_hud_800857DC(f32, f32, f32, f32);
void func_hud_80085890(f32, f32, f32, f32);
void func_hud_80086110(f32, f32, s32);
void func_hud_80086664(f32, f32);
void func_hud_800869A0(f32, f32, s32, f32, s32, s32);
void func_hud_80087530(f32, f32, s32);
void func_hud_800884E4(void);
void func_hud_80088564(void);
void HUD_DrawStatusScreens(void);
s32 func_hud_8008AC54(s32);
void func_hud_8008AD94(void);
void func_hud_8008B5B0(f32 x, f32 y);
s32 func_hud_8008B774(void);
void func_hud_8008BD00(u8*, s32, s32, u8);
void func_hud_8008C104(u16*, u16*);
void HUD_DisplaySmallNumber(f32, f32, f32, s32);
void func_hud_8008C5C8(f32, f32, f32, s32);
void func_hud_8008C6F4(s32, s32);
s32 func_hud_8008BCBC(s32);
void HUD_DrawEdgeArrows(void);
s32 HUD_dummy_8008CB8C(void);
void func_hud_8008D0DC(f32, f32, f32, f32, f32);
void HUD_DrawBossHealth(void);
void HUD_DrawCountdown(s32* , f32);
void func_hud_8008E9EC(f32, f32);
void func_hud_8008EA14(f32, f32);
void HUD_Draw(void);
void HUD_BossFO_Draw(Boss*);
void func_hud_8008FFF0(Boss*, s32);
s32 func_hud_80090200(Boss* boss);
bool func_hud_8009092C(Actor*);
void HUD_BossFO_Update(Boss*);
bool func_hud_800915FC(Actor*);
bool func_hud_800924E0(Actor*);

void ActorTeamBoss_Init(Actor*);
void ActorTeamBoss_Update(Actor* this);
void func_hud_80093164(Actor*);
void HUD_AquasStart(Player*);
void func_hud_800953A0(Actor*, s32);
void func_hud_8009546C(Actor*, s32);
void func_hud_80095538(Actor*, s32);
void HUD_AquasComplete(Player*);
void func_hud_80094954(Effect*);
void func_hud_80094BBC(Effect*);
void func_hud_80094D20(f32, f32);
void func_hud_80096A74(Player* player);

// fox_col1
void func_col1_80098860(PlaneF* plane, Vec3f* point, Vec3f* normal);
s32 func_col1_800988B4(Vec3f* vec, PlaneF* plane);
bool func_col1_800998FC(Vec3f* objPos, Vec3f* colliderPos, Vec3f* objVel, s32 colId, Vec3f* hitPosOut,
                        f32* hitAnglesOut);

// fox_col2
bool func_col2_800A3690(Vec3f* objPos, Vec3f* colliderPos, s32 colId, Vec3f* hitDataOut);

// fox_pause
void func_pause_800A3CA0(void);

// fox_play
bool Play_CheckMedalStatus(u16);
void Play_dummy_MuteSfx(void);
s32 Play_GetMaxShields(void);
void Play_PlaySfxFirstPlayer(f32*, u32);
void Player_SetupArwingShot(Player* player, PlayerShot* shot, f32 arg2, f32 arg3, PlayerShotId shotId, f32 speed);
void Play_Setup(void);
void Play_InitEnvironment(void);
void Play_GenerateStarfield(void);
void Play_SetupStarfield(void);
void Player_PlaySfx(f32* , u32 , s32 );
void Play_PlaySfxNoPlayer(f32* , u32 );
void Play_ClearObjectData(void);
void Play_SpawnDebris(s32 , f32 , f32 , f32 );
void Player_ApplyDamage(Player* player, s32 direction, s32 damage);
bool Play_CheckDynaFloorCollision(f32* , s32* , f32 xPos, f32 yPos, f32 zPos);
bool Play_CheckSingleHitbox(Hitbox* hitbox, f32 , f32 , f32 , f32 , f32 , f32 );
void Player_CollisionCheck(Player* player);
void Player_FloorCheck(Player* player);
void Player_SetupOnFootShot(Player*, PlayerShot*, PlayerShotId );
void Player_Setup(Player*);
void Player_Update360(Player*);
void Play_InitLevel(void);
void Player_InitVersus(void);
void Player_CheckBounds360(Player*);
void Player_UpdateArwingRoll(Player*);
void Player_ArwingBoost(Player*);
void Camera_UpdateArwingOnRails(Player*);
void Camera_UpdateCockpitOnRails(Player*, s32);
void Camera_FollowPlayer(Player*, s32 , bool );
void Camera_UpdateArwing360(Player*, s32);
void Camera_UpdateTank360(Player*, s32 );
void Camera_UpdateOnFoot360(Player*, s32 );
void Camera_SetStarfieldPos(f32, f32, f32, f32, f32, f32);
void Camera_Update360(Player*, s32);
void Camera_SetupLights(Player*);
void Play_SpawnVsItem(ObjectId , Item*);
void Play_Main(void);
void Play_SpawnHitmark(f32 xPos, f32 yPos, f32 zPos);
void Player_Shoot(Player* player);
void Player_UpdatePath(Player* player);
void Player_LowHealthAlarm(Player* player);
void Play_dummy_800B41E0(Player* player);
void Player_Down(Player* player);
void Player_DamageEffects(Player* player);
void Player_CheckItemCollect(Player* player);
void Player_UpdateHitbox(Player* player);
s32 Player_CheckHitboxCollision(Player* player, f32* hitboxData, s32* index, f32 xPos, f32 yPos, f32 zPos, f32 xRot, f32 yRot,
                  f32 zRot, f32 arg9, f32 argA, f32 argB);
bool Play_CheckPolyCollision(ObjectId objId, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, Vec3f* arg7, Vec3f* arg8);
void Scenery360_Initialize(Scenery360*);

// fox_versus
s32 Versus_Main(void);
void Versus_Draw(void);
void Versus_StartMatch(void);
void func_versus_800C2190(void);
void func_versus_800C26C8(void);

void OvlMenu_CallFunction(u32, void*);
void Map_Main(void);

void Ending_Main(void);
void Ending_Draw(void);

// sf_i5_5
bool Ground_801B49D0(Actor* actor);

// libultra
void gSPSegmentLoadRes(void* value, int segNum, uintptr_t target);
void gSPDisplayList(Gfx* pkt, Gfx* dl);
void gSPDisplayListOffset(Gfx* pkt, Gfx* dl, int offset);
void gSPVertex(Gfx* pkt, uintptr_t v, int n, int v0);
void gSPInvalidateTexCache(Gfx* pkt, uintptr_t texAddr);

#endif
