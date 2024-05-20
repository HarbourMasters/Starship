#ifndef FOX_OPTION_H
#define FOX_OPTION_H

#include "global.h"

//! TODO: RENAME. Member names inferred by Option_DrawCardLabel.
typedef struct {
    /* 0x00 */ s32 unk_00; // type
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ void* unk_08; // texture
    /* 0x0C */ u16* unk_0C; // palette
    /* 0x10 */ s32 unk_10; // width
    /* 0x14 */ s32 unk_14; // height
    /* 0x18 */ f32 unk_18; // xPos
    /* 0x1C */ f32 unk_1C; // yPos
    /* 0x20 */ f32 unk_20; // xScale
    /* 0x24 */ f32 unk_24; // yScale
    /* 0x28 */ s32 unk_28; // red
    /* 0x2C */ s32 unk_2C; // green
    /* 0x30 */ s32 unk_30; // blue
    /* 0x34 */ s32 unk_34; // alpha
} OptionTexture; // size = 0x38

//! TODO: RENAME. Member names inferred by Option_DrawMenuCard
typedef struct {
    /* 0x00 */ f32 unk_00; // x
    /* 0x04 */ f32 unk_04; // y
    /* 0x08 */ f32 unk_08; // z
    /* 0x0C */ f32 unk_0C; // xScale
    /* 0x10 */ f32 unk_10; // yScale
} MenuContext_38; // size = 0x14

//! TODO: RENAME. Member names inferred by Option_DrawMenuArwing
typedef struct {
    /* 0x0 */ f32 unk_0; // x
    /* 0x4 */ f32 unk_4; // y
    /* 0x8 */ f32 unk_8; // range
} ArwingPosition; // size = 0xC

typedef struct {
    /* 0x00 */ OptionTexture unk_00;
    /* 0x38 */ MenuContext_38 unk_38;
    /* 0x4C */ ArwingPosition unk_4C;
    /* 0x58 */ s32 unk_58;
    /* 0x5C */ s32 unk_5C;
} OptionEntry; // size = 0x60

typedef struct {
    /* 0x0 */ PlanetId unk_0;
    /* 0x4 */ PlanetId unk_4;
    /* 0x8 */ s32 unk_8;
} UnkStruct_D_menu_801AED4C; // size = 0xC

typedef struct {
    s32 unk_0;
    s32 unk_4;
} UnkStruct_D_menu_801B9250;

typedef enum OptionId {
    OPTION_MAIN_MENU = 1000,
    OPTION_VERSUS_STAGE = 2000,
    OPTION_MAP = 0,
    OPTION_TRAINING = 1,
    OPTION_VERSUS = 2,
    OPTION_RANKING = 3,
    OPTION_SOUND = 4,
    OPTION_DATA = 5,
    OPTION_EXPERT_SOUND = 6,
    OPTION_POINT_MATCH = 10,
    OPTION_BR_MATCH = 20,
    OPTION_TT_MATCH = 30,
    OPTION_NAME = 200,
    OPTION_SCORE = 300,
    OPTION_INVOICE = 400,
    OPTION_MAX,
} OptionId;

#define OPTION_COUNT ARRAY_COUNT(sOptionCardList)

extern u8* D_menu_801B68B0[];
extern u8* D_menu_801B68D4[];

extern s32 D_menu_801B8220[]; // total hits ranking? see Option_80197DE4
extern s32 D_menu_801B827C; // engine
extern s32 D_menu_801B8280;
extern s32 D_menu_801B8284;
extern s32 D_menu_801B8288;

// Planet textures
extern u8 D_menu_801B9410[96 * 96];
extern u8 D_menu_801BB810[96 * 96];
extern u8 D_menu_801BDC10[96 * 96];
extern u8 D_menu_801C0010[96 * 96];
extern u8 D_menu_801C2410[96 * 96];
extern u8 D_menu_801C4810[96 * 96];
extern u8 D_menu_801C6C10[96 * 96];
extern u8 D_menu_801C9010[96 * 96];
extern u8 D_menu_801CB410[96 * 96];

void Title_UpdateEntry(void);
 s32 Title_80187ABC(void);
void Title_80187B00(void);
void Title_80187E28(void);
void Title_801888E8(void);
void Title_8018994C(void);
void Title_8018A644(void);
void Title_8018ACEC(void);
void Title_8018B5C4(void);
void Title_8018C644(void);
void Title_80187CA8(void);
s32 Title_80188010(void);
void Title_80189208(void);
void Title_8018A2F8(void);
void Title_8018A990(void);
void Title_8018B038(void);
void Title_8018C114(void);
void Title_8018CB90(void);
void Title_8018F680(void);
void Title_8018F77C(void);
void Title_8018F85C(void);
void Title_8018F8E4(void);
void Title_8018FC14(void);
void Title_8018FD08(void);
void Title_8018FF74(void);

void Option_UpdateEntry(void);
void Option_MapUpdate(void);
void Option_MainMenuUpdate(void);
void Option_TrainingUpdate(void);
void Option_MainMenuDraw(void);
void Option_VersusUpdate(void);
void Option_VersusDraw(void);
void Option_SoundInit(void);
void Option_SoundUpdate(void);
void Option_80194AEC(void);
void Option_80194BD0(void);
void Option_SoundDraw(void);
void Option_801952B4(void);
void Option_ExpertSoundInit(void);
void Option_ExpertSoundUpdate(void);
void Option_ExpertSoundDraw(void);
void Option_DataInit(void);
void Option_DataUpdate(void);
void Option_8019669C(void);
void Option_DataDraw(void);
void Option_RankingInit(void);
void Option_RankingUpdate(void);
void Option_RankingDraw(void);
void Option_80196FC4(void);
void Option_80197074(void);
void Option_8019715C(void);
void Option_RankingMenuDraw(void);
void Option_8019752C(void);
void Option_80197914(void);
void Option_80197A3C(s32, s32, s32);
void Option_80197D30(s32, s32, s32);
void Option_80197DE4(s32, s32, s32);
void Option_80197F74(s32, s32, s32);
void Option_80198164(s32, f32, f32);
void Option_801982B0(s32, s32, f32, f32, s32);
void Option_801984D0(s32, s32, f32, f32);
void Option_80198608(s32, s32, f32, f32);
void Option_8019882C(s32, s32, f32, f32);
void Option_8019896C(s32, f32, s32);
void Option_80199198(f32 arg0, f32 arg1, f32 arg2);
s32 Option_80199284(PlanetId start, PlanetId end);
void Option_VersusMenuInit(void);
void Option_VersusMenuUpdate(void);
void Option_8019949C(void);
void Option_VersusMenuDraw(void);
void Option_80199820(s32);
void Option_80199EA8(void);
void Option_VersusStageInit(void);
void Option_8019A080(void);
void Option_VersusStageUpdate(void);
void Option_8019A124(void);
void Option_8019A1A8(void);
void Option_8019A214(void);
void Option_8019A298(void);
void Option_8019A2E0(void);
void Option_8019A4DC(void);
void Option_8019A6DC(void);
void Option_8019A954(void);
void Option_VersusStageDraw(void);
void Option_8019AB30(void);
void Option_8019AD84(void);
void Option_8019AFFC(void);
void Option_8019B1F8(void);
void Option_8019B3DC(void);
void Option_8019B5AC(void);
void Option_8019B6D8(f32 xPos, f32 yPos, f32 offset, s32 r, s32 g, s32 b);
void Option_8019B7D4(void);
void Option_8019B8A0(s32 arg0);
void Option_8019B8C8(void);
void Option_DrawMenuLabel(void);
void Option_DrawMenuCard(MenuContext_38 arg0);
void Option_DrawMenuArwing(ArwingPosition arg0);
void Option_8019BC44(f32, f32, f32, f32, f32, f32);
void Option_8019BDF0(void);
void Option_8019BE7C(f32, f32, f32, f32 *, f32 *, f32 *);
void Option_8019BF34(void);
void Option_8019C04C(void);
void Option_DrawCardLabel(OptionTexture arg0);
bool Option_8019C418(s32* arg0, s32 arg1, bool arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, UnkStruct_D_menu_801B9250* arg8);
s32 Option_8019C5A0(s32*);
bool Option_8019C66C(f32* arg0, f32 arg1, f32 arg2, UnkStruct_D_menu_801B9250* arg3);
void Option_8019C824(f32* );
s32 Option_8019C8C4(void);
void Option_8019CAE0(void);
void Option_8019CBC0(void);
void Option_8019CD54(void);
void Option_8019D118(void);
void Option_8019D624(void);
void Option_8019DB20(s32, f32, f32, f32, f32, f32, f32, f32);
s32 Option_8019DCE8(s32 arg0);
void Option_8019DD44(void);
void Option_8019DE74(void);
void Option_8019DF64(void);
void Option_InvoiceUpdate(void);
void Option_InvoiceDraw(void);

void Map_Main(void);
void Map_801A07E8(u8*, u8*, f32*);
void Map_801AD7EC(s32, s32, s32);
void Map_801A9FD4(s32);

#endif
