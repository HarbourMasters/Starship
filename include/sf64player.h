#ifndef SF64_PLAYER
#define SF64_PLAYER

#include "sf64math.h"
#include "sf64object.h"

#define PFLAG_228_0 (1 << 0)
#define PFLAG_228_1 (1 << 1)
#define PFLAG_228_2 (1 << 2)
#define PFLAG_228_3 (1 << 3)
#define PFLAG_228_4 (1 << 4)
#define PFLAG_228_5 (1 << 5)
#define PFLAG_228_6 (1 << 6)
#define PFLAG_228_7 (1 << 7)

typedef enum TeamId {
    /* 0 */ TEAM_ID_FOX,
    /* 1 */ TEAM_ID_FALCO,
    /* 2 */ TEAM_ID_SLIPPY,
    /* 3 */ TEAM_ID_PEPPY,
    /* 4 */ TEAM_ID_KATT,
    /* 5 */ TEAM_ID_BILL,
    /* 6 */ TEAM_ID_MAX,
} TeamId;

typedef enum WingState {
    /* 0 */ WINGSTATE_NONE,
    /* 1 */ WINGSTATE_BROKEN,
    /* 2 */ WINGSTATE_INTACT,
} WingState;

typedef enum PlayerForm {
    /* 0 */ FORM_ARWING,
    /* 1 */ FORM_LANDMASTER,
    /* 2 */ FORM_BLUE_MARINE,
    /* 3 */ FORM_ON_FOOT,
    /* 4 */ FORM_UNK_4,
    /*-1 */ FORM_NONE=255,
} PlayerForm;

typedef enum DrawMode {
    /* 0 */ DRAW_NONE,
    /* 1 */ DRAW_TITLE,
    /* 2 */ DRAW_OPTION,
    /* 3 */ DRAW_MAP,
    /* 4 */ DRAW_PLAY,
    /* 5 */ DRAW_UNK_MAP,
    /* 6 */ DRAW_UNK_VS,
    /* 7 */ DRAW_UNK_7,
    /* 8 */ DRAW_ENDING,
} DrawMode;

typedef enum LevelMode {
    /* 0 */ LEVELMODE_ON_RAILS,
    /* 1 */ LEVELMODE_ALL_RANGE,
    /* 2 */ LEVELMODE_UNK_2,
} LevelMode;

typedef enum PlayerState1C8 {
    /*  0 */ PLAYERSTATE_1C8_0,
    /*  1 */ PLAYERSTATE_1C8_1,
    /*  2 */ PLAYERSTATE_1C8_2,
    /*  3 */ PLAYERSTATE_1C8_3,
    /*  4 */ PLAYERSTATE_1C8_4,
    /*  5 */ PLAYERSTATE_1C8_5,
    /*  6 */ PLAYERSTATE_1C8_6,
    /*  7 */ PLAYERSTATE_1C8_7,
    /*  8 */ PLAYERSTATE_1C8_8,
    /*  9 */ PLAYERSTATE_1C8_9,
    /* 10 */ PLAYERSTATE_1C8_10,
    /* 11 */ PLAYERSTATE_1C8_11,
    /* 12 */ PLAYERSTATE_1C8_12,
    /* 13 */ PLAYERSTATE_1C8_13,
} PlayerState1C8;

typedef enum {
    /* 0 */ PLAYERSHOT_0, // single laser?
    /* 1 */ PLAYERSHOT_1, // twin laser?
    /* 2 */ PLAYERSHOT_2,
    /* 3 */ PLAYERSHOT_3, // bomb?
    /* 4 */ PLAYERSHOT_4,
    /* 5 */ PLAYERSHOT_5, // landmaster shot
    /* 6 */ PLAYERSHOT_6, // on-foot shot
    /* 7 */ PLAYERSHOT_7, // unused? related to on-foot shot somehow
    /* 8 */ PLAYERSHOT_8, // charge shot
    /* 9 */ PLAYERSHOT_9,
} PlayerShotId;

typedef enum {
    /* 0 */ LASERS_SINGLE,
    /* 1 */ LASERS_TWIN,
    /* 2 */ LASERS_HYPER,
    /* 3 */ LASERS_UNK_3,
} LaserStrength;

typedef struct {
    /* 0x00 */ Object obj;
    /* 0x1C */ s32 index;
    /* 0x20 */ Vec3f vel;
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ f32 unk_34; 
    /* 0x38 */ f32 sfxSource[3];
    /* 0x44 */ f32 unk_44;
    /* 0x48 */ f32 unk_48;
    /* 0x4C */ f32 unk_4C;
    /* 0x50 */ f32 unk_50;
    /* 0x54 */ f32 unk_54;
    /* 0x58 */ s32 unk_58;
    /* 0x5C */ s32 unk_5C;
    /* 0x60 */ s32 unk_60;
    /* 0x64 */ s32 unk_64;
    /* 0x68 */ s32 playerNum;
    /* 0x6C */ u8 bonus;
} PlayerShot; // size = 0x70

typedef struct {
    /* 0x00 */ u8 rightState;
    /* 0x01 */ u8 leftState;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ u8 unk_2C;
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ f32 unk_34;
    /* 0x38 */ f32 unk_38;
} WingInfo; // size = 0x3C

typedef struct {
    /* 0x00 */ u8 levelType;
    /* 0x01 */ u8 form;
    /* 0x04 */ f32 *srcPos;
    /* 0x08 */ f32 *srcVel;
    /* 0x0C */ u8 boost;
    /* 0x0D */ u8 brake;
    /* 0x10 */ f32 yVel;
    /* 0x14 */ u8 bank;
    /* 0x18 */ f32 zRot;
    /* 0x1C */ u8 roll;
} PlayerSfx; // size = 0x20

typedef struct Player {
    /* 0x000 */ f32 unk_000;
    /* 0x004 */ f32 unk_004;
    /* 0x008 */ f32 unk_008; 
    /* 0x00C */ f32 unk_00C;
    /* 0x010 */ f32 unk_010;
    /* 0x014 */ f32 unk_014;
    /* 0x018 */ f32 unk_018;
    /* 0x01C */ f32 unk_01C;
    /* 0x020 */ char pad20[8];
    /* 0x028 */ f32 unk_028;
    /* 0x02C */ f32 unk_02C;
    /* 0x030 */ f32 unk_030;
    /* 0x034 */ f32 unk_034; 
    /* 0x038 */ char pad38[8];
    /* 0x040 */ Vec3f camEye;
    /* 0x04C */ Vec3f camAt;
    /* 0x058 */ f32 unk_058;
    /* 0x05C */ f32 unk_05C;
    /* 0x05C */ f32 unk_060;
    /* 0x064 */ f32 unk_064;
    /* 0x068 */ f32 unk_068;
    /* 0x06C */ f32 unk_06C;
    /* 0x070 */ f32 unk_070;
    /* 0x074 */ Vec3f pos;
    /* 0x080 */ f32 unk_080;
    /* 0x084 */ f32 unk_084;
    /* 0x088 */ f32 unk_088;
    /* 0x08C */ f32 unk_08C;
    /* 0x090 */ Vec3f unk_090;
    /* 0x09C */ f32 unk_09C;
    /* 0x0A0 */ f32 unk_0A0;
    /* 0x0A4 */ f32 unk_0A4;
    /* 0x0A8 */ f32 unk_0A8;
    /* 0x0AC */ f32 unk_0AC;
    /* 0x0B0 */ f32 unk_0B0;
    /* 0x0B4 */ f32 unk_0B4;
    /* 0x0B8 */ f32 unk_0B8;
    /* 0x0BC */ f32 unk_0BC;
    /* 0x0C0 */ Vec3f vel;
    /* 0x0CC */ f32 unk_0CC;
    /* 0x0D0 */ f32 unk_0D0;
    /* 0x0D4 */ f32 unk_0D4;
    /* 0x0D8 */ Vec3f unk_0D8;
    /* 0x0E4 */ f32 unk_0E4;
    /* 0x0E8 */ f32 unk_0E8;
    /* 0x0EC */ f32 unk_0EC;
    /* 0x0F0 */ f32 unk_0F0;
    /* 0x0F4 */ f32 unk_0F4;
    /* 0x0F8 */ f32 unk_0F8;
    /* 0x0FC */ f32 unk_0FC;
    /* 0x100 */ f32 unk_100;
    /* 0x104 */ f32 unk_104;
    /* 0x108 */ f32 unk_108;
    /* 0x10C */ f32 unk_10C;
    /* 0x110 */ f32 unk_110;
    /* 0x114 */ f32 unk_114;
    /* 0x118 */ f32 unk_118;
    /* 0x11C */ f32 unk_11C;
    /* 0x120 */ f32 unk_120;
    /* 0x124 */ f32 unk_124;
    /* 0x128 */ char pad128[4];
    /* 0x12C */ f32 unk_12C;
    /* 0x130 */ f32 unk_130;
    /* 0x134 */ f32 unk_134;
    /* 0x138 */ f32 unk_138;
    /* 0x13C */ char pad13C[4];
    /* 0x140 */ f32 unk_140;
    /* 0x144 */ f32 unk_144;
    /* 0x148 */ f32 unk_148;
    /* 0x14C */ f32 unk_14C;
    /* 0x150 */ f32 unk_150;
    /* 0x154 */ f32 unk_154;
    /* 0x158 */ f32 unk_158;
    /* 0x15C */ f32 unk_15C;
    /* 0x160 */ char pad160[4];
    /* 0x164 */ f32 unk_164;
    /* 0x168 */ f32 unk_168;
    /* 0x16C */ f32 unk_16C;
    /* 0x170 */ f32 unk_170;
    /* 0x174 */ f32 unk_174;
    /* 0x178 */ f32 unk_178;
    /* 0x17C */ f32 unk_17C;
    /* 0x180 */ f32 unk_180;
    /* 0x184 */ f32 unk_184;
    /* 0x188 */ f32 unk_188;
    /* 0x18C */ f32 unk_18C;
    /* 0x190 */ f32 unk_190;
    /* 0x194 */ f32 unk_194;
    /* 0x198 */ s32 savedCockpitView;
    /* 0x19C */ s32 unk_19C;
    /* 0x1A0 */ s32 unk_1A0;
    /* 0x1A4 */ s32 unk_1A4;
    /* 0x1A8 */ char pad1A8[8];
    /* 0x1B0 */ s32 unk_1B0;
    /* 0x1B4 */ s32 unk_1B4;
    /* 0x1B8 */ char pad1B8[4];
    /* 0x1BC */ s32 unk_1BC;
    /* 0x1C0 */ s32 unk_1C0;
    /* 0x1C4 */ s32 num;
    /* 0x1C8 */ PlayerState1C8 state_1C8;
    /* 0x1CC */ PlayerForm form;
    /* 0x1D0 */ s32 unk_1D0;
    /* 0x1D4 */ s32 unk_1D4;
    /* 0x1D8 */ s32 unk_1D8;
    /* 0x1DC */ s32 unk_1DC;
    /* 0x1E0 */ s32 timer_1E0;
    /* 0x1E4 */ s32 timer_1E4;
    /* 0x1E8 */ s32 timer_1E8;
    /* 0x1EC */ s32 unk_1EC;
    /* 0x1F0 */ s32 unk_1F0;
    /* 0x1F4 */ s32 unk_1F4;
    /* 0x1F8 */ s32 timer_1F8;
    /* 0x1FC */ s32 timer_1FC;
    /* 0x200 */ s32 unk_200;
    /* 0x204 */ s32 unk_204;
    /* 0x208 */ s32 unk_208;
    /* 0x20C */ s32 unk_20C; 
    /* 0x210 */ s32 timer_210;
    /* 0x214 */ s32 timer_214;
    /* 0x218 */ s32 timer_218;
    /* 0x21C */ s32 unk_21C;
    /* 0x220 */ s32 timer_220;
    /* 0x224 */ s32 timer_224;
    /* 0x228 */ s32 flags_228;
    /* 0x22C */ s32 unk_22C;
    /* 0x230 */ s32 unk_230;
    /* 0x234 */ s32 unk_234;
    /* 0x238 */ s32 cockpitView;
    /* 0x23C */ s32 unk_23C;
    /* 0x240 */ s32 unk_240;
    /* 0x244 */ s32 timer_244;
    /* 0x248 */ f32 unk_248;
    /* 0x24C */ f32 unk_24C;
    /* 0x250 */ f32 unk_250;
    /* 0x250 */ char pad254[4];
    /* 0x258 */ f32 unk_258;
    /* 0x25C */ f32 unk_25C;
    /* 0x260 */ char pad260[4];
    /* 0x264 */ s32 shields;
    /* 0x268 */ s32 damage;
    /* 0x26C */ s32 heal;
    /* 0x270 */ s32 unk_270;
    /* 0x274 */ char pad274[4];
    /* 0x278 */ s32 timer_278;
    /* 0x27C */ s32 timer_27C;
    /* 0x280 */ s32 unk_280;
    /* 0x284 */ s32 unk_284;
    /* 0x288 */ s32 unk_288;
    /* 0x28C */ char pad28C[0x28];
    /* 0x2B4 */ bool unk_2B4;
    /* 0x2B8 */ bool unk_2B8;
    /* 0x2BC */ f32 unk_2BC;
    /* 0x2C0 */ f32 unk_2C0;
    /* 0x2C4 */ s32 unk_2C4;
    /* 0x2C8 */ Vec3f hit2;
    /* 0x2D4 */ Vec3f hit1;
    /* 0x2E0 */ Vec3f hit3;
    /* 0x2EC */ Vec3f hit4;
    /* 0x2F8 */ Vec3f jointTable[30];
    /* 0x460 */ f32 sfxSource[3];
    /* 0x46C */ f32 sfxVel[3];
    /* 0x478 */ PlayerSfx sfx;
    /* 0x498 */ s32 timer_498;
    /* 0x49C */ WingInfo wings;
    /* 0x4D8 */ f32 unk_4D8;
    /* 0x4DC */ s32 unk_4DC;
} Player; // size = 0x4E0


#endif
