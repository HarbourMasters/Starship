#ifndef I3_H
#define I3_H

#include "stdbool.h"
#include "structs.h"
#include "sf64object.h"
#include "sf64thread.h"
#include "sf64player.h"
#include "sf64mesg.h"

extern f32 D_AQ_801C4188;

void Aquas_801BE034(Actor*);

void Area6_8018DA58(Actor*);
void Zoness_8019E5F0(Actor*);
void Solar_801A8BE8(Actor*);
void Aquas_801AB9B0(Player*);
void Aquas_801BE0F0(Actor*);

void OvlI3_CallFunction(s32, void*);
void Area6_BossA6_Init(Boss *);
void Area6_Boss_Update(Boss*);
void Area6_Boss_Draw(Boss*);
void Area6_LevelStart(Player *player);
void Area6_LevelComplete(Player*);

void Zoness_SpawnDebris(Vec3f*, Vec3f*, f32, f32, f32, s32, f32, s32, s32);
void Zoness_80190430(Actor* actor);
void Zoness_801904CC(Actor* actor);
void Zoness_80190A00(Actor* actor);
void Zoness_80190F08(Actor* actor);
void Zoness_80191010(Actor* actor);
void Zoness_801914C4(Actor* actor);
void Zoness_801915A4(Actor* actor);
void Zoness_80191680(Actor* actor);
void Zoness_80191B4C(Actor* actor);
void Zoness_80191BB8(Actor* actor);
void Zoness_80191BC4(Actor* actor);
void Zoness_80191DB0(Actor* actor);
void Zoness_80191DB0(Actor* actor);
void Zoness_80191FFC(Actor* actor);
void Zoness_80192094(Actor* actor);
void Zoness_80192834(Actor* actor);
void Zoness_80192C18(Actor* actor);
void Zoness_80192E64(Actor* actor);
void Zoness_80193240(Actor* actor);
void Zoness_BossZo_Init(Boss* this);
void Zoness_Boss_Draw(Boss* bossZO);
void Zoness_Boss_Update(Boss* bossZO);
void Zoness_8019969C(Actor* actor);
void Zoness_8019983C(Actor* actor);
void Zoness_80199A28(Actor* actor);
void Zoness_80199E24(Actor* actor);
void Zoness_80199F10(Actor* actor);
void Zoness_8019A1FC(Actor* actor);
void Zoness_8019A5D4(Actor* actor);
void Zoness_8019ACCC(Actor* actor);
void Zoness_8019B1F0(Actor* actor);
void Zoness_8019B548(Actor* actor);
void Zoness_8019B7DC(Actor* actor);
void Zoness_8019B810(Actor* actor);
void Zoness_8019B854(Actor* actor);
void Zoness_8019BDE0(Actor* actor);
void Zoness_8019BE48(Actor* actor);
void Zoness_8019C1CC(Actor* actor);
void Zoness_8019C200(Actor* actor);
void Zoness_8019C454(Actor* actor);
void Zoness_8019C83C(Actor* actor);
void Zoness_8019CBEC(Actor* actor);
void Zoness_8019CE58(Actor* actor);
void Zoness_Actor247_Init(Actor* this);
void Zoness_8019D15C(Actor* actor);
void Zoness_8019D3C4(Actor* actor);
void Zoness_LevelStart(Player* player);
void Zoness_LevelComplete(Player* player);

void Solar_8019E8B8(f32, f32, f32, f32);
void Solar_8019E9F4(f32, f32, f32, f32, f32, f32, f32, s32);
void Solar_8019EA7C(Actor*);
void Solar_8019F20C(Actor*);
void Solar_8019F7AC(Actor*);
void Solar_801A003C(Actor*);
void Solar_801A0120(Effect*);
void Solar_801A0AF0(Effect*);
void Solar_LevelStart(Player* player);
void Solar_Boss_Update(Boss*);
void Solar_Boss_Draw(Boss*);
void Solar_801A8BE8(Actor*);
void Solar_LevelComplete(Player* player);

void Aquas_801A9824(void);
void Aquas_801AA20C(void);
void Aquas_UpdateCamera(Player*);
void Aquas_BlueMarineMove(Player*);
void Aquas_801ABA40(PlayerShot*);
void Aquas_BlueMarineShoot(Player*);
void Aquas_801AC8A8(f32, f32, f32, f32, s32);
void Aquas_801AC918(Effect*);
void Aquas_801ACBB4(Player*);
void Aquas_BlueMarineBoost(Player*);
void Aquas_BlueMarineBrake(Player*);
void Aquas_801AD688(Actor *);
void Aquas_801AD6C0(Actor*);
void Aquas_801AE168(Actor*);
void Aquas_801AE3AC(Actor *);
void Aquas_801AE3D8(Actor*);
void Aquas_801AEB44(Actor*);
void Aquas_801AF9FC(Actor *);
void Aquas_801AFA5C(Actor*);
void Aquas_801B099C(Actor*);
void Aquas_801B0B60(Actor*);
void Aquas_801B0EC0(Actor*);
void Aquas_BossAq_Init(Boss*);
void Aquas_Boss_Update(Boss*);
void Aquas_Boss_Draw(Boss*);
void Aquas_801B504C(Actor*);
void Aquas_801B50E8(Actor*);
void Aquas_801B619C(Actor*);
void Aquas_801B6344(Actor *);
void Aquas_801B638C(Actor*);
void Aquas_801B6E54(Actor *);
void Aquas_801B6FF8(Actor*);
void Aquas_801B7A24(Actor*);
void Aquas_801B7AF0(Actor *);
void Aquas_801B7C78(Actor*);
void Aquas_801B90DC(Actor*);
void Aquas_801B91A4(Actor*);
void Aquas_801BA108(Actor*);
void Aquas_801BA26C(Actor*);
void Aquas_801BA4E4(Actor*);
void Aquas_801BA57C(Actor *);
void Aquas_801BA6A4(Actor*);
void Aquas_801BAD7C(Actor*);
void Aquas_801BADF8(Actor*);
void Aquas_801BB204(Actor*);
void Aquas_801BB26C(Actor *);
void Aquas_801BB79C(Actor*);
void Aquas_801BC930(Actor*);
void Aquas_801BC9A0(Actor*);
void Aquas_801BD264(Actor*);
void Aquas_801BD54C(Actor*);
void Aquas_801BDE6C(Actor*);
void Aquas_801BDF14(void);
void Aquas_801BE1FC(Scenery*);
void Aquas_801BE3F8(Actor*);
void Aquas_801BEB1C(Actor*);
void Aquas_Boss301_Update(Boss*);
void Aquas_Boss301_Draw(Boss*);
void Aquas_801BEC68(Actor*);
void Aquas_801BEC74(Actor*);
void Aquas_Update360(Player*);

#endif
