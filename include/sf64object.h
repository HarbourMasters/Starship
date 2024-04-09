#ifndef SF64_OBJECT
#define SF64_OBJECT

#include <libultraship.h>
#include "sf64math.h"

#define HITBOX_TYPE_2 200000.0f
#define HITBOX_TYPE_3 300000.0f
#define HITBOX_TYPE_4 400000.0f

typedef struct {
    /* 0x0 */ f32 offset;
    /* 0x4 */ f32 size;
} HitboxDim; // size = 0x8

typedef struct {
    /* 0x00 */ HitboxDim z;
    /* 0x08 */ HitboxDim y;
    /* 0x10 */ HitboxDim x;
} Hitbox; // size = 0x18

typedef struct {
   /* 0x00 */ Triangle tri;
   /* 0x08 */ PlaneI plane;
} CollisionPoly; // size = 0x14

typedef struct {
    /* 0x00 */ Vec3f min;
    /* 0x0C */ Vec3f max;
    /* 0x18 */ s32 polyCount;
    /* 0x1C */ CollisionPoly* polys;
    /* 0x20 */ Vec3s* mesh;
} CollisionHeader; // size = 0x24

typedef struct {
   /* 0x00 */ Vec3f min;
   /* 0x0C */ Vec3f max;
   /* 0x18 */ s32 polyCount;
   /* 0x1C */ Triangle* polys;
   /* 0x20 */ Vec3f* mesh;
} CollisionHeader2; // size = 0x24

typedef enum {
    /*  0 */ COL1_0, // OBJ_ACTOR_180
    /*  1 */ COL1_1, // OBJ_80_39
    /*  2 */ COL1_2,
    /*  3 */ COL1_3, // ACTOR_EVENT_ID
    /*  4 */ COL1_4, // OBJ_BOSS_308
    /*  5 */ COL1_5, // OBJ_80_149
    /*  6 */ COL1_6, // OBJ_80_150
    /*  7 */ COL1_7, // OBJ_BOSS_309
    /*  8 */ COL1_8, // OBJ_BOSS_313
    /*  9 */ COL1_9, // OBJ_BOSS_312
} CollisonId_1;

typedef enum {
    /*  0 */  COL2_0, // default
    /*  1 */  COL2_1, // OBJ_80_4, OBJ_80_5
    /*  2 */  COL2_2, // OBJ_80_2
    /*  3 */  COL2_3, // OBJ_80_3, OBJ_80_69
    /*  4 */  COL2_4, // OBJ_80_140
    /*  5 */  COL2_5, // PLAYERSHOT_7 ?
    /*  6 */  COL2_6, // OBJ_80_141
    /*  7 */  COL2_7, // OBJ_80_47
    /*  8 */  COL2_8, // OBJ_80_70
    /*  9 */  COL2_9, // OBJ_80_72
    /* 10 */ COL2_10, // OBJ_80_71
    /* 11 */ COL2_11, // OBJ_80_73
    /* 12 */ COL2_12, // OBJ_80_67
    /* 13 */ COL2_13, // OBJ_80_74
    /* 14 */ COL2_14, // OBJ_80_117
    /* 15 */ COL2_15, // OBJ_80_124
    /* 16 */ COL2_16, // OBJ_80_126
    /* 17 */ COL2_17, // OBJ_80_143
    /* 18 */ COL2_18, // OBJ_80_120
} CollisionId_2;

typedef struct {
    /* 0x00 */ f32 zPos1;
    /* 0x04 */ s16 zPos2;
    /* 0x06 */ s16 xPos;
    /* 0x08 */ s16 yPos;
    /* 0x0A */ Vec3s rot;
    /* 0x10 */ s16 id;
} ObjectInit; // size = 0x14

typedef struct {
    /* 0x00 */ Gfx* dList;
    /* 0x04 */ f32* hitbox;
    /* 0x08 */ f32 scale;
    /* 0x0C */ f32 info_unk_10;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ u8 info_unk_16;
    /* 0x15 */ u8 info_unk_14;
    /* 0x16 */ u8 sfx;
    /* 0x17 */ u8 info_unk_19;
    /* 0x18 */ f32 info_unk_1C;
    /* 0x1C */ u8 bonus;
} UnkStruct_D003C; // size = 0x20

typedef enum ObjectStatus {
    /* 0 */ OBJ_FREE,
    /* 1 */ OBJ_INIT,
    /* 2 */ OBJ_ACTIVE,
    /* 3 */ OBJ_DYING,
} ObjectStatus;

typedef struct {
    /* 0x00 */ u8 status;
    /* 0x02 */ u16 id;
    /* 0x04 */ Vec3f pos;
    /* 0x10 */ Vec3f rot;
} Object; // size = 0x1C

typedef void (*ObjectFunc)(Object*);

typedef struct {
    /* 0x00 */ union {
        ObjectFunc draw;
        Gfx* dList;
    };
    /* 0x00 */ u8 drawType;
    /* 0x08 */ ObjectFunc action; // argument must have object type.
    /* 0x0C */ f32* hitbox;
    /* 0x10 */ f32 unk_10; // z coordinate of something
    /* 0x14 */ s16 unk_14; // can be -1, 0, 1
    /* 0x16 */ s16 unk_16; // can be 0, 1, 2
    /* 0x18 */ u8 damage;
    /* 0x19 */ u8 unk_19; // can be 0, 1, 2
    /* 0x1C */ f32 unk_1C; // y offset of something
    /* 0x20 */ u8 bonus;
} ObjectInfo; // size = 0x24

typedef struct {
    /* 0x00 */ Object obj;
    /* 0x1C */ ObjectInfo info;
    /* 0x40 */ u8 unk_40;
    /* 0x41 */ char unk_41[7];
    /* 0x48 */ f32 sfxSource[3];
    /* 0x54 */ f32 unk_54;
} Object_58; // size = 0x58

typedef struct {
    /* 0x00 */ Object obj;
    /* 0x1C */ ObjectInfo info;
    /* 0x40 */ s32 index;
    /* 0x44 */ s32 unk_44;
    /* 0x48 */ s32 state;
    /* 0x4C */ s32 timer_4C;
    /* 0x50 */ s8 dmgType;
    /* 0x54 */ s32 dmgPart;
    /* 0x58 */ f32 unk_58;
    /* 0x5C */ f32 unk_5C;
    /* 0x60 */ f32 unk_60;
    /* 0x64 */ Vec3f vel;
    /* 0x70 */ f32 sfxSource[3];
    /* 0x7C */ char pad7C[4];
} Object_80; // size = 0x80

typedef struct {
    /* 0x00 */ Object obj;
    /* 0x1C */ ObjectInfo info;
    /* 0x40 */ s32 index;
    /* 0x44 */ char pad44[1];
    /* 0x45 */ u8 unk_45;
    /* 0x46 */ s8 unk_46;
    /* 0x48 */ s32 unk_48;
} Sprite; // size = 0x4C

typedef struct {
    /* 0x00 */ Object obj;
    /* 0x1C */ ObjectInfo info;
    /* 0x40 */ s32 index;
    /* 0x44 */ s16 unk_44;
    /* 0x46 */ u8 state;
    /* 0x48 */ u16 timer_48;
    /* 0x4A */ u16 timer_4A;
    /* 0x4C */ s8 collected;
    /* 0x4E */ s16 playerNum;
    /* 0x50 */ f32 unk_50;
    /* 0x54 */ f32 unk_54;
    /* 0x58 */ f32 unk_58;
    /* 0x5C */ f32 sfxSource[3];
    /* 0x68 */ f32 scale;
} Item; // size 0x6C

typedef struct {
    /* 0x00 */ Object obj;
    /* 0x1C */ ObjectInfo info;
    /* 0x40 */ s32 index;
    /* 0x44 */ s16 unk_44;
    /* 0x46 */ s16 unk_46;
    /* 0x48 */ s16 unk_48;
    /* 0x4A */ s16 unk_4A;
    /* 0x4C */ u8 unk_4C;
    /* 0x4E */ s16 state;
    /* 0x50 */ u16 timer_50;
    /* 0x52 */ char pad52[0x2];
    /* 0x54 */ Vec3f vel;
    /* 0x60 */ Vec3f unk_60;
    /* 0x6C */ f32 scale1;
    /* 0x70 */ f32 scale2;
    /* 0x74 */ Gfx* unk_74;
    /* 0x78 */ s16 unk_78;
    /* 0x7A */ s16 unk_7A;
    /* 0x7C */ char pad7C[4];
    /* 0x80 */ f32 sfxSource[3];
} Effect; // size 0x8C

typedef struct {
    /* 0x000 */ Object obj;
    /* 0x01C */ ObjectInfo info;
    /* 0x040 */ s32 index;
    /* 0x044 */ s16 unk_044;
    /* 0x046 */ s16 unk_046;
    /* 0x048 */ s16 unk_048;
    /* 0x04A */ s16 unk_04A;
    /* 0x04C */ s16 unk_04C;
    /* 0x04E */ s16 state;
    /* 0x050 */ s16 timer_050;
    /* 0x052 */ s16 timer_052;
    /* 0x054 */ s16 timer_054;
    /* 0x056 */ s16 timer_056;
    /* 0x058 */ s16 timer_058;
    /* 0x05A */ s16 timer_05A;
    /* 0x05C */ s16 timer_05C;
    /* 0x05E */ u8 unk_05E;
    /* 0x060 */ s16 health;
    /* 0x062 */ s8 dmgType;
    /* 0x064 */ s16 damage;
    /* 0x066 */ s16 dmgPart;
    /* 0x068 */ f32 unk_068;
    /* 0x06C */ Vec3f vel;
    /* 0x078 */ Vec3f unk_078;
    /* 0x084 */ f32 gravity;
    /* 0x088 */ s16 swork[40];
    /* 0x0D8 */ f32 fwork[50];
    /* 0x1A0 */ Vec3f vwork[50];
    /* 0x3F8 */ f32 unk_3F8;
    /* 0x3FC */ f32 sfxSource[3];
} Boss; // size = 0x408

#define DMG_BEAM 1
#define DMG_NONE 0
#define DMG_BOMB -1
#define DMG_UNK_100 100

typedef struct {
    /* 0x000 */ Object obj;
    /* 0x01C */ ObjectInfo info;
    /* 0x040 */ s32 index;
    /* 0x044 */ u8 itemDrop;
    /* 0x046 */ s16 unk_046;
    /* 0x048 */ s16 unk_048;
    /* 0x04A */ s16 unk_04A;
    /* 0x04C */ s16 timer_04C;
    /* 0x04E */ s16 unk_04E;
    /* 0x050 */ uintptr_t iwork[25];
    /* 0x0B4 */ s16 unk_0B4;
    /* 0x0B6 */ s16 unk_0B6;
    /* 0x0B8 */ s16 state;
    /* 0x0BA */ char pad0BA[0x2];
    /* 0x0BC */ u16 timer_0BC;
    /* 0x0BE */ u16 timer_0BE;
    /* 0x0C0 */ u16 timer_0C0;
    /* 0x0C2 */ u16 timer_0C2;
    /* 0x0C4 */ u16 timer_0C4;
    /* 0x0C6 */ u16 timer_0C6;
    /* 0x0C8 */ u8 unk_0C8;
    /* 0x0C9 */ u8 unk_0C9;
    /* 0x0CA */ u8 timer_0CA[4];
    /* 0x0CE */ s16 health;
    /* 0x0D0 */ s8 unk_0D0;
    /* 0x0D2 */ s16 unk_0D2;
    /* 0x0D4 */ s16 unk_0D4;
    /* 0x0D6 */ u16 damage;
    /* 0x0D8 */ Vec3f unk_0D8;
    /* 0x0E4 */ s16 aiType;
    /* 0x0E6 */ s16 aiIndex;
    /* 0x0E8 */ Vec3f vel;
    /* 0x0F4 */ Vec3f unk_0F4;
    /* 0x100 */ f32 sfxSource[3];
    /* 0x10C */ f32 gravity;
    /* 0x110 */ f32 scale;
    /* 0x114 */ f32 fwork[30];
    /* 0x18C */ Vec3f vwork[30];
} Actor; // size = 0x2F4

typedef enum ObjectId {
  /*  -1 */  OBJ_INVALID=-1,
  /*   0 */  OBJ_80_0,
  /*   1 */  OBJ_80_1,
  /*   2 */  OBJ_80_2,
  /*   3 */  OBJ_80_3,
  /*   4 */  OBJ_80_4,
  /*   5 */  OBJ_80_5,
  /*   6 */  OBJ_80_6,
  /*   7 */  OBJ_80_7,
  /*   8 */  OBJ_80_8,
  /*   9 */  OBJ_80_9,
  /*  10 */  OBJ_80_10,
  /*  11 */  OBJ_80_11,
  /*  12 */  OBJ_80_12,
  /*  13 */  OBJ_80_13,
  /*  14 */  OBJ_80_14,
  /*  15 */  OBJ_80_15,
  /*  16 */  OBJ_80_16,
  /*  17 */  OBJ_80_17,
  /*  18 */  OBJ_80_18,
  /*  19 */  OBJ_80_19,
  /*  20 */  OBJ_80_20,
  /*  21 */  OBJ_80_21,
  /*  22 */  OBJ_80_22,
  /*  23 */  OBJ_80_23,
  /*  24 */  OBJ_80_24,
  /*  25 */  OBJ_80_25,
  /*  26 */  OBJ_80_26,
  /*  27 */  OBJ_80_27,
  /*  28 */  OBJ_80_28,
  /*  29 */  OBJ_80_29,
  /*  30 */  OBJ_80_30,
  /*  31 */  OBJ_80_31,
  /*  32 */  OBJ_80_32,
  /*  33 */  OBJ_80_33,
  /*  34 */  OBJ_80_34,
  /*  35 */  OBJ_80_35,
  /*  36 */  OBJ_80_36,
  /*  37 */  OBJ_80_37,
  /*  38 */  OBJ_80_38,
  /*  39 */  OBJ_80_39,
  /*  40 */  OBJ_80_40,
  /*  41 */  OBJ_80_41,
  /*  42 */  OBJ_80_42,
  /*  43 */  OBJ_80_43,
  /*  44 */  OBJ_80_44,
  /*  45 */  OBJ_80_45,
  /*  46 */  OBJ_80_46,
  /*  47 */  OBJ_80_47,
  /*  48 */  OBJ_80_48,
  /*  49 */  OBJ_80_49,
  /*  50 */  OBJ_80_50,
  /*  51 */  OBJ_80_51,
  /*  52 */  OBJ_80_52,
  /*  53 */  OBJ_80_53,
  /*  54 */  OBJ_80_54,
  /*  55 */  OBJ_80_55,
  /*  56 */  OBJ_80_56,
  /*  57 */  OBJ_80_57,
  /*  58 */  OBJ_80_58,
  /*  59 */  OBJ_80_59,
  /*  60 */  OBJ_80_60,
  /*  61 */  OBJ_80_61,
  /*  62 */  OBJ_80_62,
  /*  63 */  OBJ_80_63,
  /*  64 */  OBJ_80_64,
  /*  65 */  OBJ_80_65,
  /*  66 */  OBJ_80_66,
  /*  67 */  OBJ_80_67,
  /*  68 */  OBJ_80_68,
  /*  69 */  OBJ_80_69,
  /*  70 */  OBJ_80_70,
  /*  71 */  OBJ_80_71,
  /*  72 */  OBJ_80_72,
  /*  73 */  OBJ_80_73,
  /*  74 */  OBJ_80_74,
  /*  75 */  OBJ_80_75,
  /*  76 */  OBJ_80_76,
  /*  77 */  OBJ_80_77,
  /*  78 */  OBJ_80_78,
  /*  79 */  OBJ_80_79,
  /*  80 */  OBJ_80_80,
  /*  81 */  OBJ_80_81,
  /*  82 */  OBJ_80_82,
  /*  83 */  OBJ_80_83,
  /*  84 */  OBJ_80_84,
  /*  85 */  OBJ_80_85,
  /*  86 */  OBJ_80_86,
  /*  87 */  OBJ_80_87,
  /*  88 */  OBJ_80_88,
  /*  89 */  OBJ_80_89,
  /*  90 */  OBJ_80_90,
  /*  91 */  OBJ_80_91,
  /*  92 */  OBJ_80_92,
  /*  93 */  OBJ_80_93,
  /*  94 */  OBJ_80_94,
  /*  95 */  OBJ_80_95,
  /*  96 */  OBJ_80_96,
  /*  97 */  OBJ_80_97,
  /*  98 */  OBJ_80_98,
  /*  99 */  OBJ_80_99,
  /* 100 */  OBJ_80_100,
  /* 101 */  OBJ_80_101,
  /* 102 */  OBJ_80_102,
  /* 103 */  OBJ_80_103,
  /* 104 */  OBJ_80_104,
  /* 105 */  OBJ_80_105,
  /* 106 */  OBJ_80_106,
  /* 107 */  OBJ_80_107,
  /* 108 */  OBJ_80_108,
  /* 109 */  OBJ_80_109,
  /* 110 */  OBJ_80_110,
  /* 111 */  OBJ_80_111,
  /* 112 */  OBJ_80_112,
  /* 113 */  OBJ_80_113,
  /* 114 */  OBJ_80_114,
  /* 115 */  OBJ_80_115,
  /* 116 */  OBJ_80_116,
  /* 117 */  OBJ_80_117,
  /* 118 */  OBJ_80_118,
  /* 119 */  OBJ_80_119,
  /* 120 */  OBJ_80_120,
  /* 121 */  OBJ_80_121,
  /* 122 */  OBJ_80_122,
  /* 123 */  OBJ_80_123,
  /* 124 */  OBJ_80_124,
  /* 125 */  OBJ_80_125,
  /* 126 */  OBJ_80_126,
  /* 127 */  OBJ_80_127,
  /* 128 */  OBJ_80_128,
  /* 129 */  OBJ_80_129,
  /* 130 */  OBJ_80_130,
  /* 131 */  OBJ_80_131,
  /* 132 */  OBJ_80_132,
  /* 133 */  OBJ_80_133,
  /* 134 */  OBJ_80_134,
  /* 135 */  OBJ_80_135,
  /* 136 */  OBJ_80_136,
  /* 137 */  OBJ_80_137,
  /* 138 */  OBJ_80_138,
  /* 139 */  OBJ_80_139,
  /* 140 */  OBJ_80_140,
  /* 141 */  OBJ_80_141,
  /* 142 */  OBJ_80_142,
  /* 143 */  OBJ_80_143,
  /* 144 */  OBJ_80_144,
  /* 145 */  OBJ_80_145,
  /* 146 */  OBJ_80_146,
  /* 147 */  OBJ_80_147,
  /* 148 */  OBJ_80_148,
  /* 149 */  OBJ_80_149,
  /* 150 */  OBJ_80_150,
  /* 151 */  OBJ_80_151,
  /* 152 */  OBJ_80_152,
  /* 153 */  OBJ_80_153,
  /* 154 */  OBJ_80_154,
  /* 155 */  OBJ_80_155,
  /* 156 */  OBJ_80_156,
  /* 157 */  OBJ_80_157,
  /* 158 */  OBJ_80_158,
  /* 159 */  OBJ_80_159,
  /* 160 */  OBJ_80_160,
  /* 161 */  OBJ_SPRITE_CO_POLE,
  /* 162 */  OBJ_SPRITE_CO_TREE,
  /* 163 */  OBJ_SPRITE_FO_POLE,
  /* 164 */  OBJ_SPRITE_FOG_SHADOW,
  /* 165 */  OBJ_SPRITE_CO_RUIN1,
  /* 166 */  OBJ_SPRITE_CO_RUIN2,
  /* 167 */  OBJ_SPRITE_167,
  /* 168 */  OBJ_SPRITE_168,
  /* 169 */  OBJ_SPRITE_TI_CACTUS,
  /* 170 */  OBJ_SPRITE_CO_SMOKE,
  /* 171 */  OBJ_SPRITE_VE1_BOSS_TRIGGER1,
  /* 172 */  OBJ_SPRITE_VE1_BOSS_TRIGGER2,
  /* 173 */  OBJ_SPRITE_VE1_BOSS_TRIGGER3,
  /* 174 */  OBJ_SPRITE_VE1_BOSS_TRIGGER4,
  /* 175 */  OBJ_SPRITE_GFOX_TARGET,
  /* 176 */  OBJ_ACTOR_176,
  /* 177 */  OBJ_ACTOR_177,
  /* 178 */  OBJ_ACTOR_178,
  /* 179 */  OBJ_ACTOR_179,
  /* 180 */  OBJ_ACTOR_180,
  /* 181 */  OBJ_ACTOR_181,
  /* 182 */  OBJ_ACTOR_182,
  /* 183 */  OBJ_ACTOR_183,
  /* 184 */  OBJ_ACTOR_184,
  /* 185 */  OBJ_ACTOR_185,
  /* 186 */  OBJ_ACTOR_186,
  /* 187 */  OBJ_ACTOR_187,
  /* 188 */  OBJ_ACTOR_188,
  /* 189 */  OBJ_ACTOR_189,
  /* 190 */  OBJ_ACTOR_190,
  /* 191 */  OBJ_ACTOR_191,
  /* 192 */  OBJ_ACTOR_192,
  /* 193 */  OBJ_ACTOR_193,
  /* 194 */  OBJ_ACTOR_194,
  /* 195 */  OBJ_ACTOR_195,
  /* 196 */  OBJ_ACTOR_196,
  /* 197 */  OBJ_ACTOR_ALLRANGE,
  /* 198 */  OBJ_ACTOR_TEAM_BOSS,
  /* 199 */  OBJ_ACTOR_199,
  /* 200 */  OBJ_ACTOR_EVENT,
  /* 201 */  OBJ_ACTOR_201,
  /* 202 */  OBJ_ACTOR_202,
  /* 203 */  OBJ_ACTOR_SLIPPY_SX,
  /* 204 */  OBJ_ACTOR_204,
  /* 205 */  OBJ_ACTOR_205,
  /* 206 */  OBJ_ACTOR_206,
  /* 207 */  OBJ_ACTOR_207,
  /* 208 */  OBJ_ACTOR_208,
  /* 209 */  OBJ_ACTOR_209,
  /* 210 */  OBJ_ACTOR_210,
  /* 211 */  OBJ_ACTOR_211,
  /* 212 */  OBJ_ACTOR_212,
  /* 213 */  OBJ_ACTOR_213,
  /* 214 */  OBJ_ACTOR_214,
  /* 215 */  OBJ_ACTOR_215,
  /* 216 */  OBJ_ACTOR_216,
  /* 217 */  OBJ_ACTOR_217,
  /* 218 */  OBJ_ACTOR_218,
  /* 219 */  OBJ_ACTOR_219,
  /* 220 */  OBJ_ACTOR_220,
  /* 221 */  OBJ_ACTOR_221,
  /* 222 */  OBJ_ACTOR_222,
  /* 223 */  OBJ_ACTOR_223,
  /* 224 */  OBJ_ACTOR_224,
  /* 225 */  OBJ_ACTOR_225,
  /* 226 */  OBJ_ACTOR_226,
  /* 227 */  OBJ_ACTOR_227,
  /* 228 */  OBJ_ACTOR_228,
  /* 229 */  OBJ_ACTOR_229,
  /* 230 */  OBJ_ACTOR_230,
  /* 231 */  OBJ_ACTOR_231,
  /* 232 */  OBJ_ACTOR_232,
  /* 233 */  OBJ_ACTOR_233,
  /* 234 */  OBJ_ACTOR_234,
  /* 235 */  OBJ_ACTOR_235,
  /* 236 */  OBJ_ACTOR_236,
  /* 237 */  OBJ_ACTOR_237,
  /* 238 */  OBJ_ACTOR_238,
  /* 239 */  OBJ_ACTOR_239,
  /* 240 */  OBJ_ACTOR_240,
  /* 241 */  OBJ_ACTOR_241,
  /* 242 */  OBJ_ACTOR_242,
  /* 243 */  OBJ_ACTOR_243,
  /* 244 */  OBJ_ACTOR_244,
  /* 245 */  OBJ_ACTOR_245,
  /* 246 */  OBJ_ACTOR_246,
  /* 247 */  OBJ_ACTOR_247,
  /* 248 */  OBJ_ACTOR_248,
  /* 249 */  OBJ_ACTOR_249,
  /* 250 */  OBJ_ACTOR_250,
  /* 251 */  OBJ_ACTOR_251,
  /* 252 */  OBJ_ACTOR_252,
  /* 253 */  OBJ_ACTOR_253,
  /* 254 */  OBJ_ACTOR_254,
  /* 255 */  OBJ_ACTOR_255,
  /* 256 */  OBJ_ACTOR_256,
  /* 257 */  OBJ_ACTOR_257,
  /* 258 */  OBJ_ACTOR_258,
  /* 259 */  OBJ_ACTOR_259,
  /* 260 */  OBJ_ACTOR_260,
  /* 261 */  OBJ_ACTOR_261,
  /* 262 */  OBJ_ACTOR_262,
  /* 263 */  OBJ_ACTOR_263,
  /* 264 */  OBJ_ACTOR_264,
  /* 265 */  OBJ_ACTOR_265,
  /* 266 */  OBJ_ACTOR_266,
  /* 267 */  OBJ_ACTOR_267,
  /* 268 */  OBJ_ACTOR_268,
  /* 269 */  OBJ_ACTOR_269,
  /* 270 */  OBJ_ACTOR_270,
  /* 271 */  OBJ_ACTOR_271,
  /* 272 */  OBJ_ACTOR_272,
  /* 273 */  OBJ_ACTOR_273,
  /* 274 */  OBJ_ACTOR_274,
  /* 275 */  OBJ_ACTOR_275,
  /* 276 */  OBJ_ACTOR_276,
  /* 277 */  OBJ_ACTOR_277,
  /* 278 */  OBJ_ACTOR_278,
  /* 279 */  OBJ_ACTOR_279,
  /* 280 */  OBJ_ACTOR_280,
  /* 281 */  OBJ_ACTOR_281,
  /* 282 */  OBJ_ACTOR_282,
  /* 283 */  OBJ_ACTOR_283,
  /* 284 */  OBJ_ACTOR_284,
  /* 285 */  OBJ_ACTOR_285,
  /* 286 */  OBJ_ACTOR_286,
  /* 287 */  OBJ_ACTOR_287,
  /* 288 */  OBJ_ACTOR_288,
  /* 289 */  OBJ_ACTOR_289,
  /* 290 */  OBJ_ACTOR_290,
  /* 291 */  OBJ_ACTOR_SUPPLIES,
  /* 292 */  OBJ_BOSS_292,
  /* 293 */  OBJ_BOSS_293,
  /* 294 */  OBJ_BOSS_294,
  /* 295 */  OBJ_BOSS_295,
  /* 296 */  OBJ_BOSS_296,
  /* 297 */  OBJ_BOSS_297,
  /* 298 */  OBJ_BOSS_298,
  /* 299 */  OBJ_BOSS_299,
  /* 300 */  OBJ_BOSS_300,
  /* 301 */  OBJ_BOSS_301,
  /* 302 */  OBJ_BOSS_A6,
  /* 303 */  OBJ_BOSS_303,
  /* 304 */  OBJ_BOSS_304,
  /* 305 */  OBJ_BOSS_305,
  /* 306 */  OBJ_BOSS_306,
  /* 307 */  OBJ_BOSS_ZO,
  /* 308 */  OBJ_BOSS_308,
  /* 309 */  OBJ_BOSS_309,
  /* 310 */  OBJ_BOSS_310,
  /* 311 */  OBJ_BOSS_311,
  /* 312 */  OBJ_BOSS_312,
  /* 313 */  OBJ_BOSS_313,
  /* 314 */  OBJ_BOSS_314,
  /* 315 */  OBJ_BOSS_SO,
  /* 316 */  OBJ_BOSS_316,
  /* 317 */  OBJ_BOSS_317,
  /* 318 */  OBJ_BOSS_AQ,
  /* 319 */  OBJ_BOSS_319,
  /* 320 */  OBJ_BOSS_320,
  /* 321 */  OBJ_BOSS_321,
  /* 322 */  OBJ_ITEM_LASERS,
  /* 323 */  OBJ_ITEM_CHECKPOINT,
  /* 324 */  OBJ_ITEM_SILVER_RING,
  /* 325 */  OBJ_ITEM_SILVER_STAR,
  /* 326 */  OBJ_ITEM_METEO_WARP,
  /* 327 */  OBJ_ITEM_BOMB,
  /* 328 */  OBJ_ITEM_PATH_SPLIT_X,
  /* 329 */  OBJ_ITEM_PATH_TURN_LEFT,
  /* 330 */  OBJ_ITEM_PATH_TURN_RIGHT,
  /* 331 */  OBJ_ITEM_PATH_SPLIT_Y,
  /* 332 */  OBJ_ITEM_PATH_TURN_UP,
  /* 333 */  OBJ_ITEM_PATH_TURN_DOWN,
  /* 334 */  OBJ_ITEM_RING_CHECK,
  /* 335 */  OBJ_ITEM_1UP,
  /* 336 */  OBJ_ITEM_GOLD_RING,
  /* 337 */  OBJ_ITEM_WING_REPAIR,
  /* 338 */  OBJ_ITEM_TRAINING_RING,
  /* 339 */  OBJ_EFFECT_339,
  /* 340 */  OBJ_EFFECT_340,
  /* 341 */  OBJ_EFFECT_341,
  /* 342 */  OBJ_EFFECT_342,
  /* 343 */  OBJ_EFFECT_343,
  /* 344 */  OBJ_EFFECT_344,
  /* 345 */  OBJ_EFFECT_345,
  /* 346 */  OBJ_EFFECT_346,
  /* 347 */  OBJ_EFFECT_347,
  /* 348 */  OBJ_EFFECT_348,
  /* 349 */  OBJ_EFFECT_349,
  /* 350 */  OBJ_EFFECT_350,
  /* 351 */  OBJ_EFFECT_351,
  /* 352 */  OBJ_EFFECT_352,
  /* 353 */  OBJ_EFFECT_353,
  /* 354 */  OBJ_EFFECT_354,
  /* 355 */  OBJ_EFFECT_355,
  /* 356 */  OBJ_EFFECT_356,
  /* 357 */  OBJ_EFFECT_357,
  /* 358 */  OBJ_EFFECT_358,
  /* 359 */  OBJ_EFFECT_359,
  /* 360 */  OBJ_EFFECT_360,
  /* 361 */  OBJ_EFFECT_361,
  /* 362 */  OBJ_EFFECT_362,
  /* 363 */  OBJ_EFFECT_363,
  /* 364 */  OBJ_EFFECT_364,
  /* 365 */  OBJ_EFFECT_365,
  /* 366 */  OBJ_EFFECT_366,
  /* 367 */  OBJ_EFFECT_367,
  /* 368 */  OBJ_EFFECT_368,
  /* 369 */  OBJ_EFFECT_369,
  /* 370 */  OBJ_EFFECT_370,
  /* 371 */  OBJ_EFFECT_371,
  /* 372 */  OBJ_EFFECT_372,
  /* 373 */  OBJ_EFFECT_373,
  /* 374 */  OBJ_EFFECT_374,
  /* 375 */  OBJ_EFFECT_375,
  /* 376 */  OBJ_EFFECT_376,
  /* 377 */  OBJ_EFFECT_377,
  /* 378 */  OBJ_EFFECT_378,
  /* 379 */  OBJ_EFFECT_379,
  /* 380 */  OBJ_EFFECT_380,
  /* 381 */  OBJ_EFFECT_381,
  /* 382 */  OBJ_EFFECT_382,
  /* 383 */  OBJ_EFFECT_383,
  /* 384 */  OBJ_EFFECT_384,
  /* 385 */  OBJ_EFFECT_385,
  /* 386 */  OBJ_EFFECT_386,
  /* 387 */  OBJ_EFFECT_387,
  /* 388 */  OBJ_EFFECT_388,
  /* 389 */  OBJ_EFFECT_389,
  /* 390 */  OBJ_EFFECT_390,
  /* 391 */  OBJ_EFFECT_391,
  /* 392 */  OBJ_EFFECT_392,
  /* 393 */  OBJ_EFFECT_393,
  /* 394 */  OBJ_EFFECT_394,
  /* 395 */  OBJ_EFFECT_395,
  /* 396 */  OBJ_EFFECT_396,
  /* 397 */  OBJ_EFFECT_397,
  /* 398 */  OBJ_EFFECT_398,
  /* 399 */  OBJ_EFFECT_399,
  /* 400 */  OBJ_UNK_400,
  /* 401 */  OBJ_UNK_401,
  /* 402 */  OBJ_UNK_402,
  /* 403 */  OBJ_UNK_403,
  /* 404 */  OBJ_UNK_404,
  /* 405 */  OBJ_UNK_405,
  /* 406 */  OBJ_UNK_406,
  /* 407 */  OBJ_ID_MAX,
} ObjectId;

#define ACTOR_EVENT_ID 1000

typedef enum ItemDrop {
    /*  0 */ DROP_NONE,
    /*  1 */ DROP_SILVER_RING,
    /*  2 */ DROP_SILVER_RING_50p,
    /*  3 */ DROP_SILVER_RING_33p,
    /*  4 */ DROP_SILVER_RING_25p,
    /*  5 */ DROP_BOMB,
    /*  6 */ DROP_BOMB_50p,
    /*  7 */ DROP_BOMB_33p,
    /*  8 */ DROP_BOMB_25p,
    /*  9 */ DROP_LASERS,
    /* 10 */ DROP_LASERS_50p,
    /* 11 */ DROP_LASERS_33p,
    /* 12 */ DROP_LASERS_25p,
    /* 13 */ DROP_1UP,
    /* 14 */ DROP_GOLD_RING_1,
    /* 15 */ DROP_GOLD_RING_2,
    /* 16 */ DROP_GOLD_RING_3,
    /* 17 */ DROP_GOLD_RING_4,
    /* 18 */ DROP_GOLD_RING_GROUP,
    /* 19 */ DROP_LASERS_GROUP,
    /* 20 */ DROP_BOMB_GROUP,
    /* 21 */ DROP_SILVER_RING_GROUP,
    /* 22 */ DROP_SILVER_RING_10p,
    /* 23 */ DROP_WING_REPAIR,
    /* 24 */ DROP_TEAM_MESG,
    /* 25 */ DROP_SILVER_STAR,
    /* 26 */ DROP_MAX,
} ItemDrop;

typedef enum AllRangeAi {
    /*   0 */ AI360_FOX,
    /*   1 */ AI360_FALCO,
    /*   2 */ AI360_SLIPPY,
    /*   3 */ AI360_PEPPY,
    /*   4 */ AI360_WOLF,
    /*   5 */ AI360_LEON,
    /*   6 */ AI360_PIGMA,
    /*   7 */ AI360_ANDREW,
    /*   8 */ AI360_KATT,
    /*   9 */ AI360_BILL,
    /*  10 */ AI360_10,
    /* 100 */ AI360_GREAT_FOX = 100,
    /* 200 */ AI360_MISSILE = 200,
    /* 200 */ AI360_EVENT_HANDLER = 1000,
} AllRangeAi;

Actor* func_game_800A3608(ObjectId);

// template enums for boss work buffers

typedef enum {
    /*  0 */ LN_SWK_0,
    /*  1 */ LN_SWK_1,
    /*  2 */ LN_SWK_2,
    /*  3 */ LN_SWK_3,
    /*  4 */ LN_SWK_4,
    /*  5 */ LN_SWK_5,
    /*  6 */ LN_SWK_6,
    /*  7 */ LN_SWK_7,
    /*  8 */ LN_SWK_8,
    /*  9 */ LN_SWK_9,
    /* 10 */ LN_SWK_10,
    /* 11 */ LN_SWK_11,
    /* 12 */ LN_SWK_12,
    /* 13 */ LN_SWK_13,
    /* 14 */ LN_SWK_14,
    /* 15 */ LN_SWK_15,
    /* 16 */ LN_SWK_16,
    /* 17 */ LN_SWK_17,
    /* 18 */ LN_SWK_18,
    /* 19 */ LN_SWK_19,
    /* 20 */ LN_SWK_20,
    /* 21 */ LN_SWK_21,
    /* 22 */ LN_SWK_22,
    /* 23 */ LN_SWK_23,
    /* 24 */ LN_SWK_24,
    /* 25 */ LN_SWK_25,
    /* 26 */ LN_SWK_26,
    /* 27 */ LN_SWK_27,
    /* 28 */ LN_SWK_28,
    /* 29 */ LN_SWK_29,
    /* 30 */ LN_SWK_30,
    /* 31 */ LN_SWK_31,
    /* 32 */ LN_SWK_32,
    /* 33 */ LN_SWK_33,
    /* 34 */ LN_SWK_34,
    /* 35 */ LN_SWK_35,
    /* 36 */ LN_SWK_36,
    /* 37 */ LN_SWK_37,
    /* 38 */ LN_SWK_38,
    /* 39 */ LN_SWK_39,
    /* 40 */ LN_SWK_MAX,
} BossLNswork;

typedef enum {
    /*  0 */ LN_FWK_0,
    /*  1 */ LN_FWK_1,
    /*  2 */ LN_FWK_2,
    /*  3 */ LN_FWK_3,
    /*  4 */ LN_FWK_4,
    /*  5 */ LN_FWK_5,
    /*  6 */ LN_FWK_6,
    /*  7 */ LN_FWK_7,
    /*  8 */ LN_FWK_8,
    /*  9 */ LN_FWK_9,
    /* 10 */ LN_FWK_10,
    /* 11 */ LN_FWK_11,
    /* 12 */ LN_FWK_12,
    /* 13 */ LN_FWK_13,
    /* 14 */ LN_FWK_14,
    /* 15 */ LN_FWK_15,
    /* 16 */ LN_FWK_16,
    /* 17 */ LN_FWK_17,
    /* 18 */ LN_FWK_18,
    /* 19 */ LN_FWK_19,
    /* 20 */ LN_FWK_20,
    /* 21 */ LN_FWK_21,
    /* 22 */ LN_FWK_22,
    /* 23 */ LN_FWK_23,
    /* 24 */ LN_FWK_24,
    /* 25 */ LN_FWK_25,
    /* 26 */ LN_FWK_26,
    /* 27 */ LN_FWK_27,
    /* 28 */ LN_FWK_28,
    /* 29 */ LN_FWK_29,
    /* 30 */ LN_FWK_30,
    /* 31 */ LN_FWK_31,
    /* 32 */ LN_FWK_32,
    /* 33 */ LN_FWK_33,
    /* 34 */ LN_FWK_34,
    /* 35 */ LN_FWK_35,
    /* 36 */ LN_FWK_36,
    /* 37 */ LN_FWK_37,
    /* 38 */ LN_FWK_38,
    /* 39 */ LN_FWK_39,
    /* 40 */ LN_FWK_40,
    /* 41 */ LN_FWK_41,
    /* 42 */ LN_FWK_42,
    /* 43 */ LN_FWK_43,
    /* 44 */ LN_FWK_44,
    /* 45 */ LN_FWK_45,
    /* 46 */ LN_FWK_46,
    /* 47 */ LN_FWK_47,
    /* 48 */ LN_FWK_48,
    /* 49 */ LN_FWK_49,
    /* 50 */ LN_FWK_MAX,
} BossLNfwork;

typedef enum {
    /*  0 */ LN_VWK_0,
    /*  1 */ LN_VWK_1,
    /*  2 */ LN_VWK_2,
    /*  3 */ LN_VWK_3,
    /*  4 */ LN_VWK_4,
    /*  5 */ LN_VWK_5,
    /*  6 */ LN_VWK_6,
    /*  7 */ LN_VWK_7,
    /*  8 */ LN_VWK_8,
    /*  9 */ LN_VWK_9,
    /* 10 */ LN_VWK_10,
    /* 11 */ LN_VWK_11,
    /* 12 */ LN_VWK_12,
    /* 13 */ LN_VWK_13,
    /* 14 */ LN_VWK_14,
    /* 15 */ LN_VWK_15,
    /* 16 */ LN_VWK_16,
    /* 17 */ LN_VWK_17,
    /* 18 */ LN_VWK_18,
    /* 19 */ LN_VWK_19,
    /* 20 */ LN_VWK_20,
    /* 21 */ LN_VWK_21,
    /* 22 */ LN_VWK_22,
    /* 23 */ LN_VWK_23,
    /* 24 */ LN_VWK_24,
    /* 25 */ LN_VWK_25,
    /* 26 */ LN_VWK_26,
    /* 27 */ LN_VWK_27,
    /* 28 */ LN_VWK_28,
    /* 29 */ LN_VWK_29,
    /* 30 */ LN_VWK_30,
    /* 31 */ LN_VWK_31,
    /* 32 */ LN_VWK_32,
    /* 33 */ LN_VWK_33,
    /* 34 */ LN_VWK_34,
    /* 35 */ LN_VWK_35,
    /* 36 */ LN_VWK_36,
    /* 37 */ LN_VWK_37,
    /* 38 */ LN_VWK_38,
    /* 39 */ LN_VWK_39,
    /* 40 */ LN_VWK_40,
    /* 41 */ LN_VWK_41,
    /* 42 */ LN_VWK_42,
    /* 43 */ LN_VWK_43,
    /* 44 */ LN_VWK_44,
    /* 45 */ LN_VWK_45,
    /* 46 */ LN_VWK_46,
    /* 47 */ LN_VWK_47,
    /* 48 */ LN_VWK_48,
    /* 49 */ LN_VWK_49,
    /* 50 */ LN_VWK_MAX,
} BossLNvwork;

typedef Object_80 Object80_0;  
typedef Object_80 Object80_1;  
typedef Object_80 Object80_2;  
typedef Object_80 Object80_3;  
typedef Object_80 Object80_4;  
typedef Object_80 Object80_5;  
typedef Object_80 Object80_6;  
typedef Object_80 Object80_7;  
typedef Object_80 Object80_8;  
typedef Object_80 Object80_9;  
typedef Object_80 Object80_10; 
typedef Object_80 Object80_11; 
typedef Object_80 Object80_12; 
typedef Object_80 Object80_13; 
typedef Object_80 Object80_14; 
typedef Object_80 Object80_15; 
typedef Object_80 Object80_16; 
typedef Object_80 Object80_17; 
typedef Object_80 Object80_18; 
typedef Object_80 Object80_19; 
typedef Object_80 Object80_20; 
typedef Object_80 Object80_21; 
typedef Object_80 Object80_22; 
typedef Object_80 Object80_23; 
typedef Object_80 Object80_24; 
typedef Object_80 Object80_25; 
typedef Object_80 Object80_26; 
typedef Object_80 Object80_27; 
typedef Object_80 Object80_28; 
typedef Object_80 Object80_29; 
typedef Object_80 Object80_30; 
typedef Object_80 Object80_31; 
typedef Object_80 Object80_32; 
typedef Object_80 Object80_33; 
typedef Object_80 Object80_34; 
typedef Object_80 Object80_35; 
typedef Object_80 Object80_36; 
typedef Object_80 Object80_37; 
typedef Object_80 Object80_38; 
typedef Object_80 Object80_39; 
typedef Object_80 Object80_40; 
typedef Object_80 Object80_41; 
typedef Object_80 Object80_42; 
typedef Object_80 Object80_43; 
typedef Object_80 Object80_44; 
typedef Object_80 Object80_45; 
typedef Object_80 Object80_46; 
typedef Object_80 Object80_47; 
typedef Object_80 Object80_48; 
typedef Object_80 Object80_49; 
typedef Object_80 Object80_50; 
typedef Object_80 Object80_51; 
typedef Object_80 Object80_52; 
typedef Object_80 Object80_53; 
typedef Object_80 Object80_54; 
typedef Object_80 Object80_55; 
typedef Object_80 Object80_56; 
typedef Object_80 Object80_57; 
typedef Object_80 Object80_58; 
typedef Object_80 Object80_59; 
typedef Object_80 Object80_60; 
typedef Object_80 Object80_61; 
typedef Object_80 Object80_62; 
typedef Object_80 Object80_63; 
typedef Object_80 Object80_64; 
typedef Object_80 Object80_65; 
typedef Object_80 Object80_66; 
typedef Object_80 Object80_67; 
typedef Object_80 Object80_68; 
typedef Object_80 Object80_69; 
typedef Object_80 Object80_70; 
typedef Object_80 Object80_71; 
typedef Object_80 Object80_72; 
typedef Object_80 Object80_73; 
typedef Object_80 Object80_74; 
typedef Object_80 Object80_75; 
typedef Object_80 Object80_76; 
typedef Object_80 Object80_77; 
typedef Object_80 Object80_78; 
typedef Object_80 Object80_79; 
typedef Object_80 Object80_80; 
typedef Object_80 Object80_81; 
typedef Object_80 Object80_82; 
typedef Object_80 Object80_83; 
typedef Object_80 Object80_84; 
typedef Object_80 Object80_85; 
typedef Object_80 Object80_86; 
typedef Object_80 Object80_87; 
typedef Object_80 Object80_88; 
typedef Object_80 Object80_89; 
typedef Object_80 Object80_90; 
typedef Object_80 Object80_91; 
typedef Object_80 Object80_92; 
typedef Object_80 Object80_93; 
typedef Object_80 Object80_94; 
typedef Object_80 Object80_95; 
typedef Object_80 Object80_96; 
typedef Object_80 Object80_97; 
typedef Object_80 Object80_98; 
typedef Object_80 Object80_99; 
typedef Object_80 Object80_100;
typedef Object_80 Object80_101;
typedef Object_80 Object80_102;
typedef Object_80 Object80_103;
typedef Object_80 Object80_104;
typedef Object_80 Object80_105;
typedef Object_80 Object80_106;
typedef Object_80 Object80_107;
typedef Object_80 Object80_108;
typedef Object_80 Object80_109;
typedef Object_80 Object80_110;
typedef Object_80 Object80_111;
typedef Object_80 Object80_112;
typedef Object_80 Object80_113;
typedef Object_80 Object80_114;
typedef Object_80 Object80_115;
typedef Object_80 Object80_116;
typedef Object_80 Object80_117;
typedef Object_80 Object80_118;
typedef Object_80 Object80_119;
typedef Object_80 Object80_120;
typedef Object_80 Object80_121;
typedef Object_80 Object80_122;
typedef Object_80 Object80_123;
typedef Object_80 Object80_124;
typedef Object_80 Object80_125;
typedef Object_80 Object80_126;
typedef Object_80 Object80_127;
typedef Object_80 Object80_128;
typedef Object_80 Object80_129;
typedef Object_80 Object80_130;
typedef Object_80 Object80_131;
typedef Object_80 Object80_132;
typedef Object_80 Object80_133;
typedef Object_80 Object80_134;
typedef Object_80 Object80_135;
typedef Object_80 Object80_136;
typedef Object_80 Object80_137;
typedef Object_80 Object80_138;
typedef Object_80 Object80_139;
typedef Object_80 Object80_140;
typedef Object_80 Object80_141;
typedef Object_80 Object80_142;
typedef Object_80 Object80_143;
typedef Object_80 Object80_144;
typedef Object_80 Object80_145;
typedef Object_80 Object80_146;
typedef Object_80 Object80_147;
typedef Object_80 Object80_148;
typedef Object_80 Object80_149;
typedef Object_80 Object80_150;
typedef Object_80 Object80_151;
typedef Object_80 Object80_152;
typedef Object_80 Object80_153;
typedef Object_80 Object80_154;
typedef Object_80 Object80_155;
typedef Object_80 Object80_156;
typedef Object_80 Object80_157;
typedef Object_80 Object80_158;
typedef Object_80 Object80_159;
typedef Object_80 Object80_160;
typedef Sprite CoPole;
typedef Sprite CoTree;
typedef Sprite FoPole;
typedef Sprite FogShadow;
typedef Sprite CoRuin1;
typedef Sprite CoRuin2;
typedef Sprite Sprite167;
typedef Sprite Sprite168;
typedef Sprite TiCactus;
typedef Sprite CoSmoke;
typedef Sprite Ve1BossTrigger1;
typedef Sprite Ve1BossTrigger2;
typedef Sprite Ve1BossTrigger3;
typedef Sprite Ve1BossTrigger4;
typedef Sprite GfoxTarget;
typedef Actor Actor176;
typedef Actor Actor177;
typedef Actor Actor178;
typedef Actor Actor179;
typedef Actor Actor180;
typedef Actor Actor181;
typedef Actor Actor182;
typedef Actor Actor183;
typedef Actor Actor184;
typedef Actor Actor185;
typedef Actor Actor186;
typedef Actor Actor187;
typedef Actor Actor188;
typedef Actor Actor189;
typedef Actor Actor190;
typedef Actor Actor191;
typedef Actor Actor192;
typedef Actor Actor193;
typedef Actor Actor194;
typedef Actor Actor195;
typedef Actor Actor196;
typedef Actor ActorAllRange;
typedef Actor ActorTeamBoss;
typedef Actor Actor199;
typedef Actor ActorEvent;
typedef Actor Actor201;
typedef Actor Actor202;
typedef Actor ActorSlippySX;
typedef Actor Actor204;
typedef Actor Actor205;
typedef Actor Actor206;
typedef Actor Actor207;
typedef Actor Actor208;
typedef Actor Actor209;
typedef Actor Actor210;
typedef Actor Actor211;
typedef Actor Actor212;
typedef Actor Actor213;
typedef Actor Actor214;
typedef Actor Actor215;
typedef Actor Actor216;
typedef Actor Actor217;
typedef Actor Actor218;
typedef Actor Actor219;
typedef Actor Actor220;
typedef Actor Actor221;
typedef Actor Actor222;
typedef Actor Actor223;
typedef Actor Actor224;
typedef Actor Actor225;
typedef Actor Actor226;
typedef Actor Actor227;
typedef Actor Actor228;
typedef Actor Actor229;
typedef Actor Actor230;
typedef Actor Actor231;
typedef Actor Actor232;
typedef Actor Actor233;
typedef Actor Actor234;
typedef Actor Actor235;
typedef Actor Actor236;
typedef Actor Actor237;
typedef Actor Actor238;
typedef Actor Actor239;
typedef Actor Actor240;
typedef Actor Actor241;
typedef Actor Actor242;
typedef Actor Actor243;
typedef Actor Actor244;
typedef Actor Actor245;
typedef Actor Actor246;
typedef Actor Actor247;
typedef Actor Actor248;
typedef Actor Actor249;
typedef Actor Actor250;
typedef Actor Actor251;
typedef Actor Actor252;
typedef Actor Actor253;
typedef Actor Actor254;
typedef Actor Actor255;
typedef Actor Actor256;
typedef Actor Actor257;
typedef Actor Actor258;
typedef Actor Actor259;
typedef Actor Actor260;
typedef Actor Actor261;
typedef Actor Actor262;
typedef Actor Actor263;
typedef Actor Actor264;
typedef Actor Actor265;
typedef Actor Actor266;
typedef Actor Actor267;
typedef Actor Actor268;
typedef Actor Actor269;
typedef Actor Actor270;
typedef Actor Actor271;
typedef Actor Actor272;
typedef Actor Actor273;
typedef Actor Actor274;
typedef Actor Actor275;
typedef Actor Actor276;
typedef Actor Actor277;
typedef Actor Actor278;
typedef Actor Actor279;
typedef Actor Actor280;
typedef Actor Actor281;
typedef Actor Actor282;
typedef Actor Actor283;
typedef Actor Actor284;
typedef Actor Actor285;
typedef Actor Actor286;
typedef Actor Actor287;
typedef Actor Actor288;
typedef Actor Actor289;
typedef Actor Actor290;
typedef Actor ActorSupplies;
typedef Boss Boss292;
typedef Boss Boss293;
typedef Boss Boss294;
typedef Boss Boss295;
typedef Boss Boss296;
typedef Boss Boss297;
typedef Boss Boss298;
typedef Boss Boss299;
typedef Boss Boss300;
typedef Boss Boss301;
typedef Boss BossA6;
typedef Boss Boss303;
typedef Boss Boss304;
typedef Boss Boss305;
typedef Boss Boss306;
typedef Boss BossZO;
typedef Boss Boss308;
typedef Boss Boss309;
typedef Boss Boss310;
typedef Boss Boss311;
typedef Boss Boss312;
typedef Boss Boss313;
typedef Boss Boss314;
typedef Boss BossSO;
typedef Boss Boss316;
typedef Boss Boss317;
typedef Boss BossAQ;
typedef Boss Boss319;
typedef Boss Boss320;
typedef Boss Boss321;
typedef Item ItemLasers;
typedef Item ItemCheckpoint;
typedef Item ItemSilverStar;
typedef Item ItemSilverRing;
typedef Item ItemMeteoWarp;
typedef Item ItemBomb;
typedef Item ItemPathSplitX;
typedef Item ItemPathTurnLeft;
typedef Item ItemPathTurnRight;
typedef Item ItemPathSplitY;
typedef Item ItemPathTurnUp;
typedef Item ItemPathTurnDown;
typedef Item ItemRingCheck;
typedef Item Item1UP;
typedef Item ItemGoldRing;
typedef Item ItemWingRepair;
typedef Item ItemTrainingRing;
typedef Effect Effect339;
typedef Effect Effect340;
typedef Effect Effect341;
typedef Effect Effect342;
typedef Effect Effect343;
typedef Effect Effect344;
typedef Effect Effect345;
typedef Effect Effect346;
typedef Effect Effect347;
typedef Effect Effect348;
typedef Effect Effect349;
typedef Effect Effect350;
typedef Effect Effect351;
typedef Effect Effect352;
typedef Effect Effect353;
typedef Effect Effect354;
typedef Effect Effect355;
typedef Effect Effect356;
typedef Effect Effect357;
typedef Effect Effect358;
typedef Effect Effect359;
typedef Effect Effect360;
typedef Effect Effect361;
typedef Effect Effect362;
typedef Effect Effect363;
typedef Effect Effect364;
typedef Effect Effect365;
typedef Effect Effect366;
typedef Effect Effect367;
typedef Effect Effect368;
typedef Effect Effect369;
typedef Effect Effect370;
typedef Effect Effect371;
typedef Effect Effect372;
typedef Effect Effect373;
typedef Effect Effect374;
typedef Effect Effect375;
typedef Effect Effect376;
typedef Effect Effect377;
typedef Effect Effect378;
typedef Effect Effect379;
typedef Effect Effect380;
typedef Effect Effect381;
typedef Effect Effect382;
typedef Effect Effect383;
typedef Effect Effect384;
typedef Effect Effect385;
typedef Effect Effect386;
typedef Effect Effect387;
typedef Effect Effect388;
typedef Effect Effect389;
typedef Effect Effect390;
typedef Effect Effect391;
typedef Effect Effect392;
typedef Effect Effect393;
typedef Effect Effect394;
typedef Effect Effect395;
typedef Effect Effect396;
typedef Effect Effect397;
typedef Effect Effect398;
typedef Effect Effect399;


#endif
