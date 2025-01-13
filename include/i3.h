#ifndef I3_H
#define I3_H

#include "libc/stdbool.h"
#include "sf64object.h"
#include "sf64thread.h"
#include "sf64player.h"
#include "sf64mesg.h"

extern f32 D_AQ_801C4188;

void Aquas_CsAqFishGroup_Update(Actor*);

void Area6_8018DA58(Actor*);
void Zoness_8019E5F0(Actor*);
void Aquas_BlueMarineDown(Player*);
void Aquas_801BE0F0(Actor*);

void OvlI3_CallFunction(s32, void*);
void Area6_A6Gorgon_Init(Boss *);
void Area6_A6Gorgon_Update(Boss*);
void Area6_A6Gorgon_Draw(Boss*);
void Area6_LevelStart(Player *player);
void Area6_LevelComplete(Player*);

void Zoness_ActorDebris_Spawn(Vec3f*, Vec3f*, f32, f32, f32, s32, f32, s32, s32);
void Zoness_ZoBird_Draw(ZoBird* this);
void Zoness_ZoBird_Update(ZoBird* this);
void Zoness_ZoDodora_Update(Actor* this);
void Zoness_ZoDodora_Draw(Actor* this);
void Zoness_ZoFish_Update(Actor* this);
void Zoness_ZoFish_Draw(Actor* this);
void Zoness_ZoEnergyBall_Init(Actor* this);
void Zoness_ZGull_Update(Actor* this);
void Zoness_ZGull_Draw(Actor* this);
void Zoness_ZoEnergyBall_Init2(Actor* actor);
void Zoness_ZoEnergyBall_Update(Actor* this);
void Zoness_ZoEnergyBall_Draw(Actor* this);
void Zoness_ZoTroika_Draw(Actor* this);
void Zoness_ZoTroika_Update(Actor* this);
void Zoness_ZoShrimp_Update(Actor* this);
void Zoness_ZoShrimp_Draw(Actor* this);
void Zoness_ZoObnema_Update(Actor* this);
void Zoness_ZoObnema_Draw(Actor* actor);
void Zoness_ZoSarumarine_Init(Boss* this);
void Zoness_ZoSarumarine_Draw(Boss* this);
void Zoness_ZoSarumarine_Update(Boss* this);
void Zoness_ZoBall_Update(ZoBall* this);
void Zoness_ZoBall_Draw(Actor* actor);
void Zoness_ZoMine_Update(Actor* this);
void Zoness_ZoMine_Draw(ZoMine* actor);
void Zoness_ZoCraneMagnet_Update(Actor* this);
void Zoness_ZoCraneMagnet_Draw(Actor* this);
void Zoness_ZoSpikeBall_Update(Actor* this);
void Zoness_ZoSpikeBall_Draw(Actor* this);
void Zoness_ZoTanker_Init(Actor* actor);
void Zoness_ZoTanker_Update(Actor* this);
void Zoness_ZoTanker_Draw(Actor* actor);
void Zoness_ZoContainer_Init(Actor* this);
void Zoness_ZoContainer_Update(Actor* this);
void Zoness_ZoContainer_Draw(Actor* this);
void Zoness_ZoRadarBuoy_Update(Actor* this);
void Zoness_ZoRadarBuoy_Draw(Actor* actor);
void Zoness_ZoSupplyCrane_Init(Actor* this);
void Zoness_ZoSupplyCrane_Update(Actor* this);
void Zoness_ZoSupplyCrane_Draw(Actor* this);
void Zoness_ZoSearchLight_Update(Actor* this);
void Zoness_ZoSearchLight_Draw(Actor* this);
void Zoness_ZoBarrier_Init(Actor* this);
void Zoness_ZoBarrier_Update(Actor* this);
void Zoness_ZoBarrier_Draw(Actor* this);
void Zoness_LevelStart(Player* player);
void Zoness_LevelComplete(Player* player);

void Solar_8019E8B8(f32, f32, f32, f32);
void Solar_8019E9F4(f32, f32, f32, f32, f32, f32, f32, s32);
void Solar_SoWave_Update(SoWave*);
void Solar_SoRock_Update(Actor*);
void Solar_SoRock_Draw(Actor*);
void Solar_SoProminence_Update(SoProminence*);
void Solar_Effect392_Update(Effect392*);
void Solar_Effect392_Draw(Effect392*);
void Solar_LevelStart(Player* player);
void Solar_SoVulkain_Update(SoVulkain*);
void Solar_SoVulkain_Draw(SoVulkain*);
void Solar_801A8BE8(ActorCutscene*);
void Solar_LevelComplete(Player* player);

void Aquas_InitLevel(void);
void Aquas_801AA20C(void);
void Aquas_UpdateCamera(Player*);
void Aquas_BlueMarineMove(Player*);
void Aquas_801ABA40(PlayerShot*);
void Aquas_BlueMarineShoot(Player*);
void Aquas_Effect366_Spawn(f32, f32, f32, f32, s32);
void Aquas_Effect366_Update(Effect*);
void Aquas_BlueMarine_Draw(Player*);
void Aquas_BlueMarineBoost(Player*);
void Aquas_BlueMarineBrake(Player*);
void Aquas_Actor255_Init(Actor *);
void Aquas_Actor255_Update(Actor*);
void Aquas_Actor255_Draw(Actor*);
void Aquas_Actor256_Init(Actor *);
void Aquas_Actor256_Update(Actor*);
void Aquas_Actor256_Draw(Actor*);
void Aquas_Actor257_Init(Actor *);
void Aquas_Actor257_Update(Actor*);
void Aquas_Actor257_Draw(Actor*);
void Aquas_AqPearl_Update(Actor*);
void Aquas_AqPearl_Draw(Actor*);
void Aquas_AqBacoon_Init(Boss*);
void Aquas_AqBacoon_Update(Boss*);
void Aquas_AqBacoon_Draw(Boss*);
void Aquas_AqSculpin_Draw(Actor*);
void Aquas_AqSculpin_Update(Actor*);
void Aquas_AqAnglerFish_Draw(Actor*);
void Aquas_AqAnglerFish_Init(Actor *);
void Aquas_AqAnglerFish_Update(Actor*);
void Aquas_AqSpindlyFish_Init(Actor *);
void Aquas_AqSpindlyFish_Update(Actor*);
void Aquas_AqSpindlyFish_Draw(Actor*);
void Aquas_AqGaroa_Init(Actor *);
void Aquas_AqGaroa_Update(Actor*);
void Aquas_AqGaroa_Draw(Actor*);
void Aquas_AqSquid_Update(Actor*);
void Aquas_AqSquid_Draw(Actor*);
void Aquas_AqSeaweed_Update(Actor*);
void Aquas_AqSeaweed_Draw(Actor*);
void Aquas_AqBoulder_Init(Actor *);
void Aquas_AqBoulder_Update(Actor*);
void Aquas_AqBoulder_Draw(Actor*);
void Aquas_AqCoral_Update(Actor*);
void Aquas_AqCoral_Draw(Actor*);
void Aquas_AqJellyfish_Init(Actor *);
void Aquas_AqJellyfish_Update(Actor*);
void Aquas_AqJellyfish_Draw(Actor*);
void Aquas_AqStoneColumn_Update(Actor*);
void Aquas_AqStoneColumn_Draw(Actor*);
void Aquas_AqFishGroup_Update(Actor*);
void Aquas_AqFishGroup_Draw(Actor*);
void Aquas_801BDF14(void);
void Aquas_AqBump2_Draw(Scenery*);
void Aquas_AqOyster_Update(Actor*);
void Aquas_AqOyster_Draw(Actor*);
void Aquas_Boss301_Update(Boss*);
void Aquas_Boss301_Draw(Boss*);
void Aquas_Actor188_Update(Actor*);
void Aquas_Actor188_Draw(Actor*);
void Aquas_Update360(Player*);

#endif
