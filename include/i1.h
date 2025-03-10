#ifndef I1_H
#define I1_H

#include "libc/stdbool.h"
#include "sf64object.h"
#include "sf64thread.h"
#include "sf64player.h"
#include "sf64mesg.h"

#ifdef __cplusplus
extern "C" {
#endif

extern Gfx* D_VE1_8019A008[];
extern f32 aVe1GolemechHitbox[];

extern void Corneria_LevelStart(Player*);
extern void Corneria_LevelComplete1(Player*);
extern void Venom1_LevelStart(Player*);

void Corneria_CoSmoke_Update(Sprite*);
void Corneria_CoGranga_Update(CoGranga*);
void Corneria_CoGranga_Draw(CoGranga*);
void Corneria_CoGaruda1_Update(CoGaruda1*);
void Corneria_CoGaruda2_Update(CoGaruda2*);
void Corneria_CoGaruda3_Update(CoGaruda3*);
void Corneria_CoGarudaDestroy_Update(CoGarudaDestroy*);
void Corneria_CoGaruda1_Draw(CoGaruda1*);
void Corneria_CoGaruda2_Draw(CoGaruda2*);
void Corneria_CoGaruda3_Draw(CoGaruda3*);
void Corneria_CoGarudaDestroy_Draw(CoGarudaDestroy*);
void Corneria_CoCarrier_Update(CoCarrier*);
void Corneria_CarrierLeft_Update(CoCarrierLeft*);
void Corneria_CarrierUpper_Update(CoCarrierUpper*);
void Corneria_CarrierBottom_Update(CoCarrierBottom*);
void Corneria_CoCarrier_Draw(CoCarrier*);
void Corneria_CoCarrierLeft_Draw(CoCarrierLeft*);
void Corneria_CoCarrierUpper_Draw(CoCarrierUpper*);
void Corneria_CoCarrierBottom_Draw(CoCarrierBottom*);
void Corneria_CoDoors_Update(Scenery*);
void Corneria_CoDoors_Draw(Scenery*);
void Venom1_BossTrigger1_Update(Sprite*);
void Venom1_BossTrigger2_Update(Sprite*);
void Venom1_BossTrigger3_Update(Sprite*);
void Venom1_BossTrigger4_Update(Sprite*);
void Venom1_Ve1Pillar1_Update(Actor*);
void Venom1_Pillar2_3_Update(Actor*);
void Venom1_Ve1Pillar2_Draw(Actor*);
void Venom1_Ve1Pillar4_Update(Actor*);
void Venom1_Ve1MonkeyStatue_Update(Actor*);
void Venom1_Ve1MonkeyStatue_Draw(Actor*);
void Venom1_Ve1Generator_Update(Scenery*);
void Venom1_Ve1Golemech_Update(Boss*);
void Venom1_Ve1Golemech_Draw(Boss*);
void Training_ItemRing_Update(Item*);

void OvlI1_CallFunction(s32, void*);
void Corneria_CoBuildingOnFire_Update(Scenery*);
void Corneria_CoBuildingOnFire_Draw(Scenery*);
void Corneria_Granga_Init(Boss *);
void Corneria_CoIBeam_Init(Actor *);
void Corneria_CoCarrier_Init(CoCarrier *);
void Corneria_CoCarrierLeft_Draw(Boss*);
void Venom1_Ve1TempleEntrance_Update(Scenery* );
void Venom1_Ve1Pillar1_Init(Actor *);
void Venom1_Ve1Pillar2_3_Init(Actor *);
void Venom1_Ve1Pillar4_Init(Actor *);
void Venom1_Ve1MonkeyStatue_Init(Actor *);
void Venom1_Ve1Golemech_Init(Boss *);
void Venom1_Ve1Golemech_SetShadow(Boss *);
void Venom1_Ve1Golemech_Dying(Boss *);
void Training_RingPassCount_Draw(void);
void Training_Setup360(void);
void Training_SpawnEnemies(void);
void Venom1_8019864C(PlayerShot*);

#ifdef __cplusplus
}
#endif

#endif
