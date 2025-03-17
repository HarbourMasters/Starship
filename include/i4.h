#ifndef I4_H
#define I4_H

#include "libc/stdbool.h"
#include "sf64object.h"
#include "sf64thread.h"
#include "sf64player.h"
#include "sf64mesg.h"

#ifdef __cplusplus
extern "C" {
#endif

extern s32 D_BO_801A03DC;
extern Matrix D_BO_8019EE80;

void Bolse_LevelStart(Player*);
void Bolse_LevelComplete(Player*);
void Katina_LevelStart(Player*);
void Katina_LevelComplete(Player*);
void Katina_SFTeamFlyTowardsCamera(Actor*);
void SectorZ_LevelStart(Player*);
void SectorZ_LevelComplete(Player*);
void SectorZ_LevelCompleteCsUpdate(Actor*);

void OvlI4_CallFunction(u32, void*);
void Fortuna_UpdateEvents(Actor*);
void Fortuna_LoadLevelObjects(void);
void Bolse_UpdateEventHandler(Actor*);
void Bolse_LoadLevelObjects(void);
void Bolse_DrawDynamicGround(void);
void Katina_KaSaucerer_Init(Boss *);
void Katina_UpdateEvents(Actor*);
void Katina_Init(void);
void SectorZ_MissileExplode(ActorAllRange* thisx, bool shotDown);
void SectorZ_Missile_Update(Actor*);
void SectorZ_UpdateEvents(Actor*);
void SectorZ_LoadLevelObjects(void);

void Fortuna_FoRadar_Update(Actor*);
void Fortuna_FoRadar_Draw(Actor*);
void Bolse_Effect397_Update(Effect*);
void Bolse_Effect397_Draw(Effect*);
void Bolse_BoBaseCore_Update(Boss*);
void Bolse_BoBaseCore_Draw(Boss*);
void Katina_LaserEnergyParticlesUpdate(Effect*);
void Katina_LaserEnergyParticlesDraw(Effect*);
void Katina_KaFrontlineBase_Update(Boss*);
void Katina_KaFrontlineBase_Draw(Boss*);
void Katina_KaSaucerer_Update(Boss*);
void Katina_KaSaucerer_Draw(Boss*);
void SectorZ_SpaceJunkUpdate(Actor*);
void SectorZ_SpaceJunkDraw(Actor*);
void SectorZ_SzGreatFox_Update(Boss*);
void SectorZ_SzGreatFox_Draw(Boss*);

#ifdef __cplusplus
}
#endif

#endif
