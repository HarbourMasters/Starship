#ifndef I5_H
#define I5_H

#include "stdbool.h"
#include "sf64object.h"
#include "sf64thread.h"
#include "sf64player.h"
#include "sf64mesg.h"


extern Gfx* D_TI_801B7584[];
extern Gfx* D_TI_801B7608[];
extern Gfx* D_TI_801B769C[];
extern f32 D_TI_801B83A8[];
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
void Titania_80189B80(Actor *);
void Titania_8018ADC4(Actor *);
void Titania_8018B720(Actor *);
void Titania_Actor231_Init(Actor *);
void Titania_8018BFB0(Actor *);
void Titania_8018E3B0(Actor *);
void Titania_8018E3CC(Actor *);
void Titania_8018E5E8(Actor *);
void Titania_8018EFF0(Sprite *);
void Titania_8018F0D8(Scenery *);
void Titania_Boss306_Init(Boss *);
void Titania_801990DC(Boss *);
void Macbeth_80199920(void);
void Macbeth_80199F8C(Actor *);
void Macbeth_801A3E70(Actor *);
void Macbeth_801A4660(Actor *);
void Macbeth_801A4AF8(Actor *);
void Macbeth_801A5E2C(Actor *);
void Macbeth_801A6134(Actor *);
void Macbeth_801A65E0(Scenery *);
void Macbeth_801A7D98(Actor *);
void Macbeth_801ACFBC(void);
void Macbeth_801AD080(void);
void Ground_801B5110(f32, f32, f32);
void Ground_801B58AC(Gfx **, f32);
bool Ground_801B6AEC(f32, f32, f32);
s32 Ground_801B6E20(f32, f32, f32 *, f32 *, f32 *);
void Macbeth_801AD144(PlayerShot*);
void Titania_80189120(f32, f32, f32, f32, f32);
bool Macbeth_801A3C20(f32);
bool Macbeth_801A3300(Player*, f32, f32);
bool Macbeth_801A3790(Player*, f32, f32);

void Titania_80188F60(Effect*);
void Titania_80188FA8(Effect*);
void Titania_80189194(Actor*);
void Titania_801895B8(Actor*);
void Titania_80189AFC(Actor*);
void Titania_80189CC8(Actor*);
void Titania_8018A1C0(Actor*);
void Titania_8018A544(Actor*);
void Titania_8018AABC(Actor*);
void Titania_8018AB44(Actor*);
void Titania_8018B268(Actor*);
void Titania_8018B6AC(Actor*);
void Titania_8018B9D0(Actor*);
void Titania_8018BE84(Actor*);
void Titania_8018C8A8(Actor*);
void Titania_8018E2D8(Actor*);
void Titania_8018E54C(Actor*);
void Titania_8018E5B4(Actor*);
void Titania_8018E5F8(Actor*);
void Titania_8018EF14(Actor*);
void Titania_Cactus_Update(Sprite*);
void Titania_8018F4D8(Scenery*);
void Titania_8018F8B8(Scenery*);
void Titania_Boss_Update(Boss*);
void Titania_Boss_Draw(Boss*);
void Macbeth_8019C778(Actor*);
void Macbeth_8019CE88(Actor*);
void Macbeth_8019D700(Actor*);
void Macbeth_8019E410(Actor*);
void Macbeth_8019EA60(Actor*);
void Macbeth_8019EE68(Actor*);
void Macbeth_8019FF9C(Actor*);
void Macbeth_801A0BD8(Scenery*);
void Macbeth_801A12C4(Actor*);
void Macbeth_801A23AC(Scenery*);
void Macbeth_801A2A78(Scenery*);
void Macbeth_801A2B24(Scenery*);
void Macbeth_801A2DD8(Scenery*);
void Macbeth_801A3240(Scenery*);
void Macbeth_801A3E98(Actor*);
void Macbeth_801A43BC(Actor*);
void Macbeth_801A46A0(Actor*);
void Macbeth_801A4A64(Actor*);
void Macbeth_801A4B24(Actor*);
void Macbeth_801A54E8(Actor*);
void Macbeth_801A57D0(Effect*);
void Macbeth_801A5AF0(Effect*);
void Macbeth_801A5B4C(Effect*);
void Macbeth_801A5D68(Effect*);
void Macbeth_801A5E54(Actor*);
void Macbeth_801A5F90(Actor*);
void Macbeth_801A5FD0(Actor*);
void Macbeth_801A6100(Actor*);
void Macbeth_801A6144(Actor*);
void Macbeth_801A6540(Actor*);
void Macbeth_801A6608(Scenery*);
void Macbeth_801A67C8(Actor*);
void Macbeth_801A68EC(Actor*);
void Macbeth_801A7E7C(Actor*);
void Macbeth_801AC294(Actor*);
void Macbeth_801AC438(Actor*);
void Macbeth_801AD6F0(Actor*);
void Macbeth_801ADAC8(Actor*);
void Macbeth_801ADD68(Actor*);
void Macbeth_801AE2C0(Actor*);
void Macbeth_801AE87C(Effect*);
void Macbeth_801AEAA0(Effect*);
void Macbeth_801AEC04(Actor*);
void Macbeth_801AEEFC(Actor*);
s32 Macbeth_801A55D4(s32 , Vec3f* , Vec3f* , s32 );

#endif
