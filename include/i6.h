#ifndef I6_H
#define I6_H

#include "libc/stdbool.h"
#include "sf64object.h"
#include "sf64thread.h"
#include "sf64player.h"
#include "sf64mesg.h"

#ifdef __cplusplus
extern "C" {
#endif

extern f32 D_Andross_801A7F58;
extern f32 D_Andross_801A7F60;
extern f32 D_Andross_801A7F68;
extern f32 D_Andross_801A7F70;
extern f32 D_Andross_801A7F78;

void Andross_80187530(Actor*);
void Andross_80193C4C(Player*);
void Andross_80195E44(Actor*);
void Venom2_LevelStart(Player*);
void Venom2_LevelComplete(Player*);
void SectorY_LevelComplete(Player*);
void SectorY_8019FF00(Actor*);
void SectorY_801A0AC0(Player*);

void Andross_Gate_Draw(Actor*);
void OvlI6_CallFunction(u32 mode, void* ptr);
void Andross_801878A8(void);
void Andross_801888F4(Actor *);
void Andross_80189214(void);
void Andross_8018BDD8(void);
void Andross_8018C390(Player*);
void Andross_AndAndross_Init(Boss *);
void Andross_801961AC(void);
void Venom2_UpdateEvents(Actor*);
void Venom2_LoadLevelObjects(void);
void SectorY_SyShogun_Init(Boss *);
void SectorY_SyRobot_Update(Actor*);
void SectorY_SyRobot_Draw(Actor*);
void Turret_Update(Player*);
void Turret_UpdateCamera(Player*);
void Turret_Draw(Player *);

void Andross_ActorTeamArwing_Update(Actor*);
void Andross_ActorTeamArwing_Draw(Actor*);
void Andross_AndBrainWaste_Update(Actor*);
void Andross_AndBrainWaste_Draw(Actor*);
void Andross_AndBossTimer_Update(Actor*);
void Andross_AndRadio_Update(Actor*);
void Andross_AndJamesTrigger_Update(Actor*);
void Andross_AndExplosion_Update(Actor*);
void Andross_AndBrain_Update(Boss*);
void Andross_AndBrain_Draw(Boss*);
void Andross_Effect396_Update(Effect*);
void Andross_Effect396_Draw(Effect*);
void Andross_AndAndross_Update(Boss*);
void Andross_AndAndross_Draw(Boss*);
void Andross_AndLaserEmitter_Update(Actor*);
void Andross_AndLaserEmitter_Draw(Actor*);
void Andross_AndDoor_Update(Scenery*);
void Andross_AndDoor_Draw(Scenery*);
void Andross_AndPassage_Update(Scenery*);
void Andross_AndPassage_Draw(Scenery*);
void Venom2_Ve2Base_Update(Boss*);
void Venom2_Ve2Base_Draw(Boss*);
void SectorY_Effect354_Draw(Effect*);
void SectorY_Scenery156_Draw(Scenery*);
void SectorY_SyShogun_Update(Boss*);
void SectorY_SyShogun_Draw(Boss*);
void SectorY_SyShip3Destroyed_Update(Scenery*);
void SectorY_SyShip4Destroyed_Update(Scenery*);

#ifdef __cplusplus
}
#endif

#endif
