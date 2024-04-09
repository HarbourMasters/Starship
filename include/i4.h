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

void Bolse_8018EF6C(Player*);
void Bolse_8018F94C(Player*);
void Katina_80192E20(Player*);
void Katina_80197290(Player*);
void Katina_80197F10(Actor*);
void SectorZ_8019BA64(Player*);
void SectorZ_8019C85C(Player*);
void SectorZ_8019DD20(Actor*);

void OvlI4_CallFunction(u32, void*);
void Fortuna_80187960(Actor*);
void Fortuna_8018BA2C(void);
void Bolse_8018C158(Actor*);
void Bolse_80191ED8(void);
void Bolse_80192264(void);
void Katina_Boss316_Init(Boss *);
void Katina_80198594(Actor*);
void Katina_80198930(void);
void SectorZ_80199900(Actor *, s32);
void SectorZ_Missile_Update(Actor*);
void SectorZ_8019AB8C(Actor*);
void SectorZ_8019EA68(void);

void Fortuna_80188AD0(Actor*);
void Fortuna_80188FE4(Actor*);
void Bolse_80191054(Effect*);
void Bolse_80191180(Effect*);
void Bolse_801912FC(Boss*);
void Bolse_80191AFC(Boss*);
void Katina_80192984(Effect*);
void Katina_80192A68(Effect*);
void Katina_80193718(Boss*);
void Katina_80193B1C(Boss*);
void Katina_801946C4(Boss*);
void Katina_801968F4(Boss*);
void SectorZ_8019E234(Actor*);
void SectorZ_8019E3A8(Actor*);
void SectorZ_8019E454(Boss*);
void SectorZ_8019E98C(Boss*);

#endif
