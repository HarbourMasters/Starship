#ifndef I2_H
#define I2_H

#include "stdbool.h"
#include "sf64object.h"
#include "sf64thread.h"
#include "sf64player.h"
#include "sf64mesg.h"

void Meteo_LevelStart(Player*);
void Meteo_LevelComplete(Player*);
void Meteo_8018ED9C(Actor*);
void SectorX_LevelStart(Player*);
void SectorX_LevelComplete(Player*);

void OvlI2_CallFunction(s32, void*);
void Meteo_80187B08(Actor *);
void Meteo_Boss297_Init(Boss *);
void Meteo_8018CCF8(Actor *);

void Meteo_8018756C(Actor*);
void Meteo_80187650(Actor*);
void Meteo_801877C4(Actor*);
void Meteo_8018795C(Actor*);
void Meteo_80188344(Boss*);
void Meteo_801887D0(Boss*);
void Meteo_80188CAC(Effect*);
void Meteo_80188FAC(Effect*);
void Meteo_80189114(Effect*);
void Meteo_8018978C(Boss*);
void Meteo_8018BACC(Boss*);
void Meteo_8018D9EC(Actor*);
void Meteo_8018DA6C(Actor*);
void Meteo_8018DAEC(Actor*);
void Meteo_8018DB6C(Actor*);
void Meteo_8018DBEC(Effect*);
void Meteo_8018DCE4(Effect*);
void Meteo_8018DE14(Effect*);
void SectorX_8018F330(Actor*);
void SectorX_8018F884(Actor*);
void SectorX_8018FE38(Boss*);
void SectorX_8018FF20(Boss*);
void SectorX_8018FF84(Boss*);
void SectorX_80190020(Boss*);
void SectorX_80190078(Boss*);
void SectorX_80193434(Boss*);

#endif
