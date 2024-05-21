#ifndef I1_H
#define I1_H

#include "stdbool.h"
#include "sf64object.h"
#include "sf64thread.h"
#include "sf64player.h"
#include "sf64mesg.h"

extern Gfx* D_VE1_8019A008[];
extern f32 D_VE1_8019A9B8[];

extern void Corneria_LevelStart(Player*);
extern void Corneria_LevelComplete1(Player*);
extern void Venom1_LevelStart(Player*);

void Corneria_801875A4(Sprite*);
void Corneria_80189058(Boss*);
void Corneria_8018AA74(Boss*);
void Corneria_8018AED0(Actor*);
void Corneria_8018B15C(Actor*);
void Corneria_8018B418(Actor*);
void Corneria_8018B58C(Actor*);
void Corneria_8018BAAC(Actor*);
void Corneria_8018BBA4(Actor*);
void Corneria_8018BBF8(Actor*);
void Corneria_8018BD7C(Actor*);
void Corneria_8018C19C(Boss*);
void Corneria_8018DDAC(Boss*);
void Corneria_8018E290(Boss*);
void Corneria_8018E76C(Boss*);
void Corneria_8018ECAC(Boss*);
void Corneria_8018ED78(Boss*);
void Corneria_8018EE84(Boss*);
void Corneria_8018EF90(Boss*);
void Corneria_8018F044(Scenery*);
void Corneria_8018F31C(Scenery*);
void Venom1_BossTrigger1_Update(Sprite*);
void Venom1_BossTrigger2_Update(Sprite*);
void Venom1_BossTrigger3_Update(Sprite*);
void Venom1_BossTrigger4_Update(Sprite*);
void Venom1_80192518(Actor*);
void Venom1_80192CD4(Actor*);
void Venom1_80192E2C(Actor*);
void Venom1_80192EB0(Actor*);
void Venom1_801933DC(Actor*);
void Venom1_801934D0(Actor*);
void Venom1_80193540(Scenery*);
void Venom1_Boss_Update(Boss*);
void Venom1_Boss_Draw(Boss*);
void Training_ItemRing_Update(Item*);

void OvlI1_CallFunction(s32, void*);
void Corneria_80187530(Scenery*);
void Corneria_8018753C(Scenery*);
void Corneria_Boss292_Init(Boss *);
void Corneria_8018B0B4(Actor *);
void Corneria_Boss293_Init(Boss *);
void Corneria_8018ED78(Boss*);
void Venom1_801924A8(Scenery* );
void Venom1_8019250C(Actor *);
void Venom1_80192CB0(Actor *);
void Venom1_80192EA4(Actor *);
void Venom1_801933B4(Actor *);
void Venom1_Boss319_Init(Boss *);
void Venom1_80198310(Boss *);
void Venom1_80198594(Boss *);
void Training_801988E0(void);
void Training_Setup360(void);
void Training_8019949C(void);
void Venom1_8019864C(PlayerShot*);

#endif
