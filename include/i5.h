#ifndef I5_H
#define I5_H

#include "libc/stdbool.h"
#include "sf64object.h"
#include "sf64thread.h"
#include "sf64player.h"
#include "sf64mesg.h"


extern Gfx* D_TI_801B7584[];
extern Gfx* D_TI_801B7608[];
extern Gfx* D_TI_801B769C[];
extern f32 aTiGorasHitbox[];
extern u8 D_MA_801BA1E8;
extern f32 D_MA_801BE250[40];
extern s16 D_MA_801BE2F0[9];

void Titania_LevelStart(Player*);
void Titania_LevelComplete(Player*);
void Macbeth_LevelStart(Player*);
void Macbeth_LevelComplete2(Player*);
void Macbeth_801B28BC(Actor*);
void Macbeth_LevelComplete1(Player*);

void OvlI5_CallFunction(u32 mode, void* ptr);
void Titania_LevelStart(Player *);
void Titania_80188F30(void);
void Titania_TiFekuda_Init(Actor *);
void Titania_TiRasco_Init(Actor *);
void Titania_TiRasco_Dying(Actor *);
void Titania_TiBomb_Init(Actor *);
void Titania_TiDesertCrawler_Init(Actor *);
void Titania_8018E3B0(Actor *);
void Titania_TiDelphor_Init(Actor *);
void Titania_TiDelphorHead_Init(Actor *);
void Titania_TiCactus_Init(Sprite *);
void Titania_TiPillar_Init(Scenery *);
void Titania_TiGoras_Init(Boss *);
void Titania_TiGoras_Dying(Boss *);
void Macbeth_InitLevel(void);
void Macbeth_Train_Init(Actor *);
void Macbeth_MaMaRailroadSwitch_Init(Actor *);
void Macbeth_MaBoulder_Init(Actor *);
void Macbeth_MaRailwaySignal_Init(Actor *);
void Macbeth_LockBars_Init(Actor *);
void Macbeth_MaBarrier_Init(Actor *);
void Macbeth_MaProximityLight_Init(Scenery *);
void Macbeth_Actor207_Init(Actor *);
void Macbeth_801ACFBC(void);
void Macbeth_801AD080(void);
void Ground_801B5110(f32, f32, f32);
void Ground_801B58AC(Gfx **, f32);
bool Ground_801B6AEC(f32, f32, f32);
s32 Ground_801B6E20(f32, f32, f32 *, f32 *, f32 *);
void Macbeth_801AD144(PlayerShot*);
void Titania_Effect368_Spawn(f32, f32, f32, f32, f32);
bool Macbeth_801A3C20(f32);
bool Macbeth_801A3300(Player*, f32, f32);
bool Macbeth_801A3790(Player*, f32, f32);

void Titania_Effect368_Update(Effect*);
void Titania_Effect368_Draw(Effect*);
void Titania_TiTerrain_Update(Actor*);
void Titania_TiDesertRover_Update(Actor*);
void Titania_TiDesertRover_Draw(Actor*);
void Titania_TiFekuda_Update(Actor*);
void Titania_TiFekuda_Draw(Actor*);
void Titania_TiBoulder_Update(Actor*);
void Titania_TiBoulder_Draw(Actor*);
void Titania_TiLandmine_Update(Actor*);
void Titania_TiRasco_Update(Actor*);
void Titania_TiRasco_Draw(Actor*);
void Titania_TiBomb_Update(Actor*);
void Titania_TiBomb_Draw(Actor*);
void Titania_TiDesertCrawler_Update(Actor*);
void Titania_TiDesertCrawler_Draw(Actor*);
void Titania_TiDelphor_Update(Actor*);
void Titania_TiDelphor_Draw(Actor*);
void Titania_TiDelphorHead_Update(Actor*);
void Titania_TiDelphorHead_Draw(Actor*);
void Titania_Cactus_Update(Sprite*);
void Titania_TiPillar_Update(Scenery*);
void Titania_TiPillar_Draw(Scenery*);
void Titania_TiGoras_Update(Boss*);
void Titania_TiGoras_Draw(Boss*);
void Macbeth_MaLocomotive_Update(Actor*);
void Macbeth_MaTrainCar4_Update(Actor*);
void Macbeth_MaTrainCar3_Update(Actor*);
void Macbeth_MaTrainCar5_Update(Actor*);
void Macbeth_MaTrainCar2_Update(Actor*);
void Macbeth_MaTrainCar7_Update(Actor*);
void Macbeth_MaTrainCar6_Update(Actor*);
void Macbeth_MaSwitchTrack_Update(Scenery*);
void Macbeth_Train_Draw(Actor*);
void Macbeth_TrainTrack_Draw(Scenery*);
void Macbeth_MaTower_Draw(Scenery*);
void Macbeth_IndicatorSign_Draw(Scenery*);
void Macbeth_MaTrainStopBlock_Update(Scenery*);
void Macbeth_MaTrainStopBlock_Draw(Scenery*);
void Macbeth_MaRailroadSwitch_Update(Actor*);
void Macbeth_MaRailroadSwitch_Draw(Actor*);
void Macbeth_MaBoulder_Update(Actor*);
void Macbeth_MaBoulder_Draw(Actor*);
void Macbeth_MaRailwaySignal_Update(Actor*);
void Macbeth_MaRailwaySignal_Draw(Actor*);
void Macbeth_Effect378_Update(Effect*);
void Macbeth_Effect378_Draw(Effect*);
void Macbeth_Effect380_Update(Effect*);
void Macbeth_Effect380_Draw(Effect*);
void Macbeth_MaHorizontalLockBar_Update(Actor*);
void Macbeth_MaHorizontalLockBar_Draw(Actor*);
void Macbeth_MaVerticalLockBar_Update(Actor*);
void Macbeth_MaVerticalLockBar_Draw(Actor*);
void Macbeth_MaBarrier_Update(Actor*);
void Macbeth_MaBarrier_Draw(Actor*);
void Macbeth_MaProximityLight_Draw(Scenery*);
void Macbeth_MaFallingBoulder_Update(Actor*);
void Macbeth_MaFallingBoulder_Draw(Actor*);
void Macbeth_Actor207_Update(Actor*);
void Macbeth_Actor207_Draw(Actor*);
void Macbeth_MaTrainCar1_Update(Actor*);
void Macbeth_MaBombDrop_Update(Actor*);
void Macbeth_MaBombDrop_Draw(Actor*);
void Macbeth_MaSpear_Update(Actor*);
void Macbeth_MaSpear_Draw(Actor*);
void Macbeth_Effect379_Update(Effect*);
void Macbeth_Effect379_Draw(Effect*);
void Macbeth_MaShockBox_Update(Actor*);
void Macbeth_MaShockBox_Draw(Actor*);
s32 Macbeth_801A55D4(s32 , Vec3f* , Vec3f* , s32 );

#endif
