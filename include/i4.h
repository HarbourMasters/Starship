#ifndef I4_H
#define I4_H

#include "stdbool.h"
#include "structs.h"
#include "sf64object.h"
#include "sf64thread.h"
#include "sf64player.h"
#include "sf64mesg.h"

extern s32 D_BO_801A03DC;
extern Matrix D_BO_8019EE80;

void Bolse_LevelStart(Player*);
void Bolse_LevelComplete(Player*);
void Katina_LevelStart(Player*);
void Katina_LevelComplete(Player*);
void Katina_SFTeamFlyTowardsCamera(Actor*);
void SectorZ_LevelStart(Player*);
void SectorZ_LevelComplete(Player*);
void SectorZ_8019DD20(Actor*);

void OvlI4_CallFunction(u32, void*);
void Fortuna_UpdateEvents(Actor*);
void Fortuna_8018BA2C(void);
void Bolse_UpdateEventHandler(Actor*);
void Bolse_80191ED8(void);
void Bolse_DrawDynamicGround(void);
void Katina_BossSetup(Boss *);
void Katina_UpdateEvents(Actor*);
void Katina_Init(void);
void SectorZ_80199900(Actor *, s32);
void SectorZ_Missile_Update(Actor*);
void SectorZ_UpdateEvents(Actor*);
void SectorZ_8019EA68(void);

void Fortuna_80188AD0(Actor*);
void Fortuna_80188FE4(Actor*);
void Bolse_80191054(Effect*);
void Bolse_80191180(Effect*);
void Bolse_801912FC(Boss*);
void Bolse_80191AFC(Boss*);
void Katina_LaserEnergyParticlesUpdate(Effect*);
void Katina_LaserEnergyParticlesDraw(Effect*);
void Katina_BaseUpdate(Boss*);
void Katina_Base_Draw(Boss*);
void Katina_BossUpdate(Boss*);
void Katina_BossDraw(Boss*);
void SectorZ_8019E234(Actor*);
void SectorZ_8019E3A8(Actor*);
void SectorZ_Boss_Update(Boss*);
void SectorZ_Boss_Draw(Boss*);

#endif
