#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "sys.h"
#include "sf64object.h"
#include "sf64player.h"
#include "sf64mesg.h"
#include "fox_hud.h"

// fox_360
void AllRange_FortunaIntro(Player*);
void AllRange_GetStarWolfHits(Actor*);
void AllRange_DrawCountdown(void);
void BoBase_Update(Boss*);
void BoBase_Draw(Boss*);
void BoBaseShield_Update(Boss*);
void BoBaseShield_Draw(Boss*);
void BoShieldReactor_Update(Actor*);
void BoShieldReactor_Draw(Actor*);
void BoLaserCannon_Update(Actor*);
void BoLaserCannon_Draw(Actor*);
bool AllRange_PlayMessage(u16*, RadioCharacterId);
void AllRange_GreatFoxRepair(Player*);
void AllRange_ClearRadio(void);
void ActorAllRange_SetShadowData(Actor* this);
void ActorAllRange_SpawnTeam(void);
void ActorAllRange_PlayMessage(u16* msg, RadioCharacterId character);
void ActorAllRange_UpdateStarWolfEvents(Actor*);
void ActorAllRange_UpdateEnemyEvents(Actor*);
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
void Boss_AwardBonus(Boss* this);
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
void Display_ArwingWings(ArwingInfo*);
void Display_DrawEngineGlow(EngineGlowColor);
void Display_SetupPlayerSfxPos(Player*);
void Display_Update(void);

// fox_edata
void Ve1Wall1_Draw(Scenery*);
void Ve1Wall2_Draw(Scenery*);
void Object_ApplyWaterDistortion(void);
void AndJamesTrigger_Draw(Actor*);

// fox_edisplay
void Graphics_SetScaleMtx(f32);
void Sprite168_Draw(Sprite*);
void MeteoBall_Draw(Actor*);
void MeHopBot_Draw(Actor*);
void MeteoTunnel_Draw(Scenery*);
void Scenery_DrawTitaniaBones(Scenery*);
void CoIBeam_Draw(Scenery*);
void CoMoleMissile_Draw(CoMoleMissile*);
void Sprite167_Draw(Sprite*);
void FogShadow_Draw(Sprite*);
void CoBuilding9_Draw(Scenery*);
void CoBuilding10_Draw(Scenery*);
void ActorDebris_Draw(Actor*);
void Actor_DrawEngineAndContrails(Actor*);
void Actor_DrawEngineGlow(Actor*, EngineGlowColor);
void ActorTeamArwing_Draw(Actor*);
void MeMolarRock_Draw(Actor*);
void MeMeteor2_Draw(MeMeteor2*);
void MeLaserCannon1_Draw(MeLaserCannon1*);
void ActorMissileSeek_Draw(Actor*);
void CoSkibot_Draw(CoSkibot*);
void CoRadar_Draw(CoRadar*);
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
s32 Object_CheckCollision(s32 index, Vec3f* pos, Vec3f* vel, s32 mode);
void Scenery_UpdateTitaniaBones(Scenery*);
void func_enmy_800654E4(Object*);
void ActorMissileSeek_Update(Actor*);
void func_enmy_800660F0(Actor*);
void Actor_Despawn(Actor*);
void CoSkibot_Update(CoSkibot*);
void func_enmy_8006684C(Actor*);
void CoRadar_Update(CoRadar*);
void MeMolarRock_Update(Actor*);
void func_enmy_80066C00(Scenery*);
void CoBuilding9_Update(Scenery*);
void Sprite167_Update(Sprite*);
void SceneryRotateTowardsCamera(Scenery*);
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
float FloatMod(float a, float b);

//fox_enmy2
void Actor237_Update(Actor*);
void Actor237_Draw(Actor*);
void CoWaterfall_Update(Scenery*);
void MeteoBall_Update(Actor*);
void MeHopBot_Update(Actor*);
void MeMora_Update(Actor*);
void MeMora_Dying(Actor*);
void MeMora_Draw(Actor*);
void CoIBeam_Update(Scenery*);
void CoMoleMissile_Update(CoMoleMissile*);
void ActorDebris_Update(Actor*);
void MeteoTunnel_Update(Scenery*);
void Actor_SetupPlayerShot(PlayerShotId, PlayerShot*, s32, f32, f32, f32, f32, f32, f32, f32, f32, f32);
void Actor_SpawnPlayerLaser(s32 actorId, f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 xRot, f32 yRot,
                            f32 zRot);
void Actor_SpawnGreatFoxLaser(s32 actorId, f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 xRot, f32 yRot,
                   f32 zRot);
void ActorEvent_SpawnEffect347(f32 xPos, f32 yPos, f32 zPos, f32 scale1);
void ActorEvent_8006F254(Actor*);
void ActorEvent_Update(Actor*);
s32 SyShipDebris_Draw(Scenery*);
void ActorEvent_Draw(Actor*);
void func_enmy2_800763A4(Actor*);
void ActorEvent_Dying(Actor*);
void TiGreatFox_Update(Actor*);
void TiGreatFox_Draw(Actor*);

// fox_effect
s32 func_effect_80081B24(f32 xPos, f32 yPos, f32 zPos, f32 scale2);
s32 BonusText_Display(f32 xPos, f32 yPos, f32 zPos, s32 hits);
void BonusText_Update(void);
void BonusText_DrawAll(void);
Effect* Effect_Load(ObjectId objId);
void Effect_FireSmoke_Spawn2(f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 scale2);
void Effect_Effect372_Draw(Effect* );
void Effect_Effect382_Draw(Effect* );
void Effect_Effect388_Draw(Effect* );
void Effect_Effect384_Draw(Effect* );
void Effect_Effect385_Draw(Effect* );
void Effect_Effect389_Draw(Effect* );
void Effect_Effect347_Draw(Effect* );
void Effect_Effect351_Draw(Effect* );
void Effect_Clouds_Draw(Effect* );
void Effect_Effect366_Draw(Effect* );
void Effect_Effect367_Draw(Effect* );
void Effect_Effect344_Draw(Effect* );
void Effect_Effect345_Draw(Effect* );
void Effect_Effect346_Draw(Effect* );
void Effect_Effect348_Draw(Effect* );
void Effect_Effect355_Draw(Effect* );
void Effect_Effect353_Draw(Effect*);
void Effect_Effect377_Draw(Effect* );
void Effect_Effect356_Draw(Effect* );
void Effect_Effect376_Draw(Effect* );
void Effect_Effect393_Spawn(f32 xPos, f32 yPos, f32 zPos, f32 scale2);
void Effect_Effect393_Update(Effect* );
void Effect_Effect393_Draw(Effect* );
void Effect_Effect357_Spawn50(f32 xPos, f32 yPos, f32 zPos, f32 scale2);
void Effect_Effect357_Spawn80(f32 xPos, f32 yPos, f32 zPos, f32 scale2);
void Effect_Effect357_Spawn95(f32 xPos, f32 yPos, f32 zPos, f32 scale2);
void func_effect_80079618(f32 xPos, f32 yPos, f32 zPos, f32 scale2);
void Effect_Effect357_Update(Effect*);
void Effect_Effect357_Draw(Effect* );
void Effect_Effect383_Update(Effect* );
void Effect_Effect383_Draw(Effect* );
void Effect_Effect383_Spawn(f32 xPos, f32 yPos, f32 zPos, f32 scale1);
void Effect_SetupTimedSfxAtPos(Effect* , Vec3f* pos, u32 sfxId);
void Effect_SpawnTimedSfxAtPos(Vec3f* pos, s32 sfxId);
void Effect_TimedSfx_Update(Effect*);
bool func_effect_8007A774(Player*, Effect*, f32);
void Effect_Effect359_Spawn(f32 xPos, f32 yPos, f32 zPos, f32 scale1, u8, u8, u16);
void Effect_Effect359_Update(Effect359*);
void Effect_Effect359_Draw(Effect*);
void Effect_Effect372_Update(Effect*);
void Effect_Effect372_Spawn1(f32 xPos, f32 yPos, f32 zPos, f32 scale2, f32 scale1, f32 yRot);
void Effect_Effect372_Spawn2(f32 xPos, f32 yPos, f32 zPos, f32 scale2, f32 scale1);
void Effect_Effect382_Spawn(f32 xPos, f32 zPos, f32 xVel, f32 zVel, f32 scale1);
void Effect_Effect382_Update(Effect*);
void Effect_Effect381_Update(Effect*);
void Effect_Effect381_Spawn(f32 xPos, f32 yPos, f32 zPos, f32 scale1);
void Effect_Effect384_Spawn(f32 xPos, f32 yPos, f32 zPos, f32 scale1, s32 );
void Effect_Effect384_Update(Effect*);
void Effect_Effect385_Spawn(f32 xPos, f32 yPos, f32 zPos, f32 scale1, s32 );
void Effect_Effect385_Update(Effect*);
void Effect_Clouds_Update(Effect*);
void Effect_Effect388_Update(Effect*);
void Effect_Effect389_Update(Effect*);
void Effect_Effect347_Update(Effect*);
void Effect_Effect364_Spawn(f32 xPos, f32 yPos, f32 zPos, f32 scale2);
void Effect_Effect364_Update(Effect*);
void Effect_Effect362_Spawn(f32 xPos, f32 yPos, f32 zPos, f32 scale2);
void Effect_Effect362_Update(Effect*);
void Effect_Effect364_Draw(Effect*);
void Effect_Effect361_Update(Effect*);
void Effect_Effect360_Update(Effect*);
void Effect_Effect360_361_362_Draw(Effect*);
void Effect386_Spawn1(f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 scale2, s32 timer50);
void Effect_Effect390_Spawn(f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 scale2, s32 timer50);
void Effect_Effect386_Update(Effect*);
void Effect_Effect389_Spawn(f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 scale2, s32 arg7);
void Effect_Effect390_Update(Effect*);
void Effect_Effect387_Spawn(f32 xPos, f32 yPos, f32 zPos, f32 scale2, s32 timer50);
void Effect_Effect387_Update(Effect*);
void Effect_Effect343_Spawn(f32 xPos, f32 yPos, f32 zPos, f32 scale2);
void Effect_Effect343_Update(Effect*);
void Effect_Effect343_Draw(Effect*);
void Effect_FireSmoke_Spawn(f32 xPos, f32 yPos, f32 zPos, f32 scale2);
void func_effect_8007D074(f32 xPos, f32 yPos, f32 zPos, f32 scale2);
void func_effect_8007D0E0(f32 xPos, f32 yPos, f32 zPos, f32 scale2);
void func_effect_8007D10C(f32 xPos, f32 yPos, f32 zPos, f32 scale2);
void Effect_Effect341_Spawn(f32 xPos, f32 yPos, f32 zPos, f32 scale2);
void func_effect_8007D24C(f32 xPos, f32 yPos, f32 zPos, f32 scale2);
void func_effect_8007D2C8(f32 xPos, f32 yPos, f32 zPos, f32 scale2);
void Effect_Effect339_Update(Effect*);
void Effect_FireSmoke_Draw(Effect*);
void Effect_Effect340_Update(Effect*);
void Effect_Effect341_Update(Effect*);
void Effect_Effect367_Spawn(f32 xPos, f32 yPos, f32 zPos, f32 scale2, f32 scale1, s32 timer50);
void Effect_Effect375_Update(Effect*);
void Effect_Effect375_Draw(Effect*);
void Effect_Effect374_Update(Effect*);
void Effect_Effect374_Draw(Effect*);
void Effect_Effect344_Update(Effect*);
void Effect_Effect345_Update(Effect*);
void Effect_Effect342_Update(Effect*);
void Effect_Effect342_Draw(Effect*);
void Effect_Effect351_Update(Effect*);
void Effect_Effect365_Update(Effect*);
void Effect_Effect365_Draw(Effect*);
void Effect_Effect367_Update(Effect*);
void func_effect_8007E93C(Effect* this, u32 objId, f32 xPos, f32 yPos, f32 zPos, f32 speed);
void func_effect_8007EE68(ObjectId objId, Vec3f* pos, Vec3f* rot, Vec3f* arg3, Vec3f* arg4, f32 scale2);
void func_effect_8007F04C(ObjectId objId, f32 xPos, f32 yPos, f32 zPos, f32 xRot, f32 yRot, f32 zRot, f32 unkX, f32 unkY, f32 unkZ, f32 xVel, f32 yVel, f32 zVel, f32 scale2);
void Effect_EnemyLaser(ObjectId objId, f32 xPos, f32 yPos, f32 zPos, f32 speed);
void func_effect_8007F20C(ObjectId objId, f32 xPos, f32 yPos, f32 zPos, f32 speed);
void Effect_Effect346_Update(Effect*);
void Effect_Effect348_Update(Effect*);
void Effect_Effect349_Update(Effect*);
void Effect_Effect350_Update(Effect*);
void Effect_Effect353_354_Update(Effect*);
bool func_effect_8007FD84(Effect*);
void Effect_Effect355_Update(Effect*);
void Effect_Effect377_Update(Effect*);
void Effect_Effect356_Update(Effect*);
void Effect_Effect376_Update(Effect*);
void Effect_Effect398_Update(Effect*);
void Effect_Effect398_Draw(Effect*);
void Effect_Effect394_Update(Effect*);
void Effect_Effect394_Draw(Effect*);
void func_effect_800815DC(void);
void func_effect_80081A8C(f32 xPos, f32 yPos, f32 zPos, f32 scale2, s32 arg4);
void func_effect_80081BEC(f32 xPos, f32 yPos, f32 zPos, f32 scale2, s32 arg4);
void Effect_Effect395_Update(Effect*);
void Effect_Effect395_Draw(Effect*);
void Effect_Effect391_Spawn(f32, f32, f32, f32, f32);
void Effect_Effect391_Update(Effect*);
void Effect_Effect391_Draw(Effect*);
void Effect_Effect399_Setup(Effect* this, f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 arg7, s32 arg8);
void func_effect_80083D2C(f32 xPos, f32 yPos, f32 zPos, f32 srcZ);
void Effect_Effect399_Update(Effect*);
void Effect_Effect399_Draw(Effect*);

// fox_fade
void Wipe_Draw(WipeMode mode, s32 frame);

// fox_hud
void HUD_TeamDownWrench_Draw(s32);
void HUD_BoostGaugeOverheat_Draw(f32, f32, f32, f32);
void HUD_BoostGaugeCool_Draw(f32, f32, f32, f32);
void HUD_TeamShields_Draw(f32, f32, s32);
void HUD_TitleCard_Draw(f32, f32);
void HUD_Number_Draw(f32, f32, s32, f32, bool, s32);
void HUD_LivesCount2_Draw(f32, f32, s32);
void HUD_SetMissionTeamStatus(void);
void HUD_Bolse_Area6_SaveData(void);
void HUD_DrawStatusScreens(void);
s32 ActorMissileSeek_ModeCheck(ActorMissileSeekMode mode);
void HUD_RadioCharacterName_Draw(void);
void HUD_PlayerShieldGauge_Draw(f32 x, f32 y);
s32 HUD_RadioDamage_Type(void);
void HUD_Texture_Scroll(u8*, s32, s32, u8);
void HUD_Texture_Wave(u16*, u16*);
void HUD_DisplaySmallNumber(f32, f32, f32, s32);
void HUD_VsModePortraitTex_Draw(f32, f32, f32, s32);
void HUD_EdgeArrows_Draw(s32, bool);
s32 HUD_CountDigits(s32);
void HUD_EdgeArrows_Update(void);
s32 HUD_8008CB8C(void);
void HUD_VS_ShieldGaugeTex_Draw(f32, f32, f32, f32, f32);
void HUD_DrawBossHealth(void);
void HUD_DrawCountdown(s32* , f32);
void HUD_Shield_GoldRings_Score(f32, f32);
void HUD_BombCounter_Draw(f32, f32);
void HUD_Draw(void);
void FoBase_Draw(Boss*);
void FoBase_BurnEffects(Boss*, s32);
s32 FoBase_ExplodeCs(Boss* this);
bool ActorTeamBoss_SetTarget(Actor*);
void FoBase_Update(Boss*);
bool ActorTeamBoss_ObstacleCheck(Actor*);
bool ActorTeamBoss_SomerSault(Actor*);

void ActorTeamBoss_Init(Actor*);
void ActorTeamBoss_Update(Actor* this);
void Aquas_CsIntroActors_Update(Actor*);
void Aquas_CsLevelStart(Player*);
void Aquas_AqBump2_Setup(Actor*, s32);
void Aquas_AqCoralReef2_Setup(Actor*, s32);
void Aquas_AqRock_Setup(Actor*, s32);
void Aquas_CsLevelComplete(Player*);
void Aquas_Effect363_Update(Effect*);
void Aquas_Effect363_Draw(Effect*);
void HUD_Score_Draw(f32, f32);
void Venom1_LevelStart2(Player* player);

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
bool Play_CheckDynaFloorCollision(f32* floorHeight, s32* triangleIndex, f32 xPos, f32 yPos, f32 zPos);
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
void Camera_FollowPlayer(Player*, s32 , bool);
void Camera_UpdateArwing360(Player*, bool);
void Camera_UpdateTank360(Player*, s32 );
void Camera_UpdateOnFoot360(Player*, s32 );
void Camera_SetStarfieldPos(f32, f32, f32, f32, f32, f32);
void Camera_Update360(Player*, bool);
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
