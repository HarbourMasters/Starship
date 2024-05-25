#ifndef SF64_OBJECT
#define SF64_OBJECT

#include <libultraship.h>
#include "sf64math.h"

#define HITBOX_ROTATED 200000.0f
#define HITBOX_SHADOW 300000.0f
#define HITBOX_WHOOSH 400000.0f

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
    /*  1 */ COL1_1, // OBJ_SCENERY_ME_TUNNEL
    /*  2 */ COL1_2,
    /*  3 */ COL1_3, // ACTOR_EVENT_ID
    /*  4 */ COL1_4, // OBJ_BOSS_FO
    /*  5 */ COL1_5, // OBJ_SCENERY_149
    /*  6 */ COL1_6, // OBJ_SCENERY_150
    /*  7 */ COL1_7, // OBJ_BOSS_309
    /*  8 */ COL1_8, // OBJ_BOSS_SZ
    /*  9 */ COL1_9, // OBJ_BOSS_VE2
} CollisonId_1;

typedef enum {
    /*  0 */  COL2_0, // default
    /*  1 */  COL2_1, // OBJ_SCENERY_4, OBJ_SCENERY_5
    /*  2 */  COL2_2, // OBJ_SCENERY_2
    /*  3 */  COL2_3, // OBJ_SCENERY_3, OBJ_SCENERY_69
    /*  4 */  COL2_4, // OBJ_SCENERY_140
    /*  5 */  COL2_5, // PLAYERSHOT_7 ?
    /*  6 */  COL2_6, // OBJ_SCENERY_141
    /*  7 */  COL2_7, // OBJ_SCENERY_47
    /*  8 */  COL2_8, // OBJ_SCENERY_70
    /*  9 */  COL2_9, // OBJ_SCENERY_72
    /* 10 */ COL2_10, // OBJ_SCENERY_71
    /* 11 */ COL2_11, // OBJ_SCENERY_73
    /* 12 */ COL2_12, // OBJ_SCENERY_67
    /* 13 */ COL2_13, // OBJ_SCENERY_74
    /* 14 */ COL2_14, // OBJ_SCENERY_117
    /* 15 */ COL2_15, // OBJ_SCENERY_124
    /* 16 */ COL2_16, // OBJ_SCENERY_126
    /* 17 */ COL2_17, // OBJ_SCENERY_143
    /* 18 */ COL2_18, // OBJ_SCENERY_120
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
    /* 0x00 */ u8 status;
    /* 0x02 */ u16 type;
    /* 0x04 */ Vec3f pos;
    /* 0x10 */ f32 yRot;
    /* 0x14 */ char pad14[0x14];
} RadarMark; // size = 0x28

typedef struct {
    /* 0x00 */ u8 mode;
    /* 0x02 */ u16 timer;
    /* 0x04 */ Vec3f posAA;
    /* 0x10 */ Vec3f posBB;
    /* 0x1C */ f32 xRot;
    /* 0x20 */ f32 yRot;
    /* 0x24 */ f32 zScale;
    /* 0x28 */ f32 xyScale;
    /* 0x2C */ Color_RGBA32 prim;
} TexturedLine; // size = 0x30

typedef struct {
    /* 0x00 */ u8 hits;
    /* 0x04 */ Vec3f pos;
    /* 0x10 */ f32 rise;
    /* 0x14 */ char pad14[0x4];
    /* 0x18 */ u16 timer;
} BonusText; // size = 0x1C

#define BONUS_TEXT_FREE 0
#define BONUS_TEXT_GREAT 100
#define BONUS_TEXT_1UP 101

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
    /* 0x10 */ f32 cullDistance; // z coordinate of something
    /* 0x14 */ s16 unk_14; // can be -1, 0, 1. governs camera-related behavior in effects (billboarding?)
    /* 0x16 */ s16 unk_16; // can be 0, 1, 2. affects death behavior?
    /* 0x18 */ u8 damage;
    /* 0x19 */ u8 unk_19; // can be 0, 1, 2. Also camera-related?
    /* 0x1C */ f32 targetOffset; // target lock y offset. 0.0f can't be targeted
    /* 0x20 */ u8 bonus; // hits when killed. numbers above 1 indicate the hit+ bonus
} ObjectInfo; // size = 0x24

typedef struct {
    /* 0x00 */ Object obj;
    /* 0x1C */ ObjectInfo info;
    /* 0x40 */ u8 pathIndex;
    /* 0x41 */ char unk_41[7];
    /* 0x48 */ f32 sfxSource[3];
    /* 0x54 */ f32 unk_54;
} Scenery360; // size = 0x58

typedef struct {
    /* 0x00 */ Object obj;
    /* 0x1C */ ObjectInfo info;
    /* 0x40 */ s32 index;
    /* 0x44 */ s32 unk_44;
    /* 0x48 */ s32 state;
    /* 0x4C */ s32 timer_4C;
    /* 0x50 */ s8 dmgType;
    /* 0x54 */ s32 dmgPart;
    /* 0x58 */ Vec3f effectVel;
    /* 0x64 */ Vec3f vel;
    /* 0x70 */ f32 sfxSource[3];
    /* 0x7C */ char pad7C[4];
} Scenery; // size = 0x80

typedef struct {
    /* 0x00 */ Object obj;
    /* 0x1C */ ObjectInfo info;
    /* 0x40 */ s32 index;
    /* 0x44 */ char pad44[1];
    /* 0x45 */ u8 sceneryId;
    /* 0x46 */ s8 destroy;
    /* 0x48 */ s32 toLeft;
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
    /* 0x68 */ f32 width;
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
    /* 0x05E */ u8 drawShadow;
    /* 0x060 */ s16 health;
    /* 0x062 */ s8 dmgType;
    /* 0x064 */ s16 damage;
    /* 0x066 */ s16 dmgPart;
    /* 0x068 */ f32 yOffset;
    /* 0x06C */ Vec3f vel;
    /* 0x078 */ Vec3f rot_078;
    /* 0x084 */ f32 gravity;
    /* 0x088 */ s16 swork[40];
    /* 0x0D8 */ f32 fwork[50];
    /* 0x1A0 */ Vec3f vwork[50];
    /* 0x3F8 */ f32 scale;
    /* 0x3FC */ f32 sfxSource[3];
} Boss; // size = 0x408

#define DMG_COLLISION 3
#define DMG_EXPLOSION 2
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
    /* 0x04E */ s16 counter_04E;
    /* 0x050 */ uintptr_t iwork[25];
    /* 0x0B4 */ s16 eventType;
    /* 0x0B6 */ s16 animFrame; // used for model type in ActorAllRange and ActorCutscene
    /* 0x0B8 */ s16 state;
    /* 0x0BA */ char pad0BA[0x2];
    /* 0x0BC */ u16 timer_0BC;
    /* 0x0BE */ u16 timer_0BE;
    /* 0x0C0 */ u16 timer_0C0;
    /* 0x0C2 */ u16 timer_0C2;
    /* 0x0C4 */ u16 timer_0C4;
    /* 0x0C6 */ u16 timer_0C6;
    /* 0x0C8 */ u8 unk_0C8; // may have been used for scenery shadowing
    /* 0x0C9 */ u8 drawShadow;
    /* 0x0CA */ u8 lockOnTimers[4];
    /* 0x0CE */ s16 health;
    /* 0x0D0 */ s8 dmgType;
    /* 0x0D2 */ s16 dmgPart;
    /* 0x0D4 */ s16 dmgSource;
    /* 0x0D6 */ u16 damage;
    /* 0x0D8 */ Vec3f hitPos;
    /* 0x0E4 */ s16 aiType; // Actor index for AllRange, script index for Event
    /* 0x0E6 */ s16 aiIndex; // Target index for AllRange, program counter for Event
    /* 0x0E8 */ Vec3f vel;
    /* 0x0F4 */ Vec3f rot_0F4;
    /* 0x100 */ f32 sfxSource[3];
    /* 0x10C */ f32 gravity;
    /* 0x110 */ f32 scale;
    /* 0x114 */ f32 fwork[30];
    /* 0x18C */ Vec3f vwork[30];
} Actor; // size = 0x2F4

typedef enum ObjectId {
  /*  -1 */  OBJ_INVALID=-1,
  /*   0 */  OBJ_SCENERY_0,
  /*   1 */  OBJ_SCENERY_1,
  /*   2 */  OBJ_SCENERY_2,
  /*   3 */  OBJ_SCENERY_3,
  /*   4 */  OBJ_SCENERY_4,
  /*   5 */  OBJ_SCENERY_5,
  /*   6 */  OBJ_SCENERY_6,
  /*   7 */  OBJ_SCENERY_7,
  /*   8 */  OBJ_SCENERY_8,
  /*   9 */  OBJ_SCENERY_9,
  /*  10 */  OBJ_SCENERY_10,
  /*  11 */  OBJ_SCENERY_11,
  /*  12 */  OBJ_SCENERY_12,
  /*  13 */  OBJ_SCENERY_13,
  /*  14 */  OBJ_SCENERY_14,
  /*  15 */  OBJ_SCENERY_15,
  /*  16 */  OBJ_SCENERY_16,
  /*  17 */  OBJ_SCENERY_17,
  /*  18 */  OBJ_SCENERY_18,
  /*  19 */  OBJ_SCENERY_19,
  /*  20 */  OBJ_SCENERY_20,
  /*  21 */  OBJ_SCENERY_21,
  /*  22 */  OBJ_SCENERY_22,
  /*  23 */  OBJ_SCENERY_23,
  /*  24 */  OBJ_SCENERY_24,
  /*  25 */  OBJ_SCENERY_25,
  /*  26 */  OBJ_SCENERY_26,
  /*  27 */  OBJ_SCENERY_27,
  /*  28 */  OBJ_SCENERY_28,
  /*  29 */  OBJ_SCENERY_TI_SKULL,
  /*  30 */  OBJ_SCENERY_TI_RIB_0,
  /*  31 */  OBJ_SCENERY_TI_RIB_1,
  /*  32 */  OBJ_SCENERY_TI_RIB_2,
  /*  33 */  OBJ_SCENERY_TI_RIB_3,
  /*  34 */  OBJ_SCENERY_TI_RIB_4,
  /*  35 */  OBJ_SCENERY_TI_RIB_5,
  /*  36 */  OBJ_SCENERY_TI_RIB_6,
  /*  37 */  OBJ_SCENERY_TI_RIB_7,
  /*  38 */  OBJ_SCENERY_TI_RIB_8,
  /*  39 */  OBJ_SCENERY_ME_TUNNEL,
  /*  40 */  OBJ_SCENERY_40,
  /*  41 */  OBJ_SCENERY_41,
  /*  42 */  OBJ_SCENERY_42,
  /*  43 */  OBJ_SCENERY_43,
  /*  44 */  OBJ_SCENERY_44,
  /*  45 */  OBJ_SCENERY_45,
  /*  46 */  OBJ_SCENERY_46,
  /*  47 */  OBJ_SCENERY_47,
  /*  48 */  OBJ_SCENERY_48,
  /*  49 */  OBJ_SCENERY_49,
  /*  50 */  OBJ_SCENERY_50,
  /*  51 */  OBJ_SCENERY_51,
  /*  52 */  OBJ_SCENERY_52,
  /*  53 */  OBJ_SCENERY_53,
  /*  54 */  OBJ_SCENERY_54,
  /*  55 */  OBJ_SCENERY_55,
  /*  56 */  OBJ_SCENERY_56,
  /*  57 */  OBJ_SCENERY_57,
  /*  58 */  OBJ_SCENERY_58,
  /*  59 */  OBJ_SCENERY_59,
  /*  60 */  OBJ_SCENERY_60,
  /*  61 */  OBJ_SCENERY_61,
  /*  62 */  OBJ_SCENERY_62,
  /*  63 */  OBJ_SCENERY_63,
  /*  64 */  OBJ_SCENERY_64,
  /*  65 */  OBJ_SCENERY_65,
  /*  66 */  OBJ_SCENERY_66,
  /*  67 */  OBJ_SCENERY_67,
  /*  68 */  OBJ_SCENERY_68,
  /*  69 */  OBJ_SCENERY_69,
  /*  70 */  OBJ_SCENERY_70,
  /*  71 */  OBJ_SCENERY_71,
  /*  72 */  OBJ_SCENERY_72,
  /*  73 */  OBJ_SCENERY_73,
  /*  74 */  OBJ_SCENERY_74,
  /*  75 */  OBJ_SCENERY_75,
  /*  76 */  OBJ_SCENERY_76,
  /*  77 */  OBJ_SCENERY_77,
  /*  78 */  OBJ_SCENERY_78,
  /*  79 */  OBJ_SCENERY_79,
  /*  80 */  OBJ_SCENERY_80,
  /*  81 */  OBJ_SCENERY_81,
  /*  82 */  OBJ_SCENERY_82,
  /*  83 */  OBJ_SCENERY_83,
  /*  84 */  OBJ_SCENERY_84,
  /*  85 */  OBJ_SCENERY_85,
  /*  86 */  OBJ_SCENERY_86,
  /*  87 */  OBJ_SCENERY_87,
  /*  88 */  OBJ_SCENERY_88,
  /*  89 */  OBJ_SCENERY_89,
  /*  90 */  OBJ_SCENERY_90,
  /*  91 */  OBJ_SCENERY_91,
  /*  92 */  OBJ_SCENERY_92,
  /*  93 */  OBJ_SCENERY_93,
  /*  94 */  OBJ_SCENERY_94,
  /*  95 */  OBJ_SCENERY_95,
  /*  96 */  OBJ_SCENERY_96,
  /*  97 */  OBJ_SCENERY_97,
  /*  98 */  OBJ_SCENERY_98,
  /*  99 */  OBJ_SCENERY_99,
  /* 100 */  OBJ_SCENERY_100,
  /* 101 */  OBJ_SCENERY_101,
  /* 102 */  OBJ_SCENERY_102,
  /* 103 */  OBJ_SCENERY_103,
  /* 104 */  OBJ_SCENERY_104,
  /* 105 */  OBJ_SCENERY_105,
  /* 106 */  OBJ_SCENERY_106,
  /* 107 */  OBJ_SCENERY_107,
  /* 108 */  OBJ_SCENERY_108,
  /* 109 */  OBJ_SCENERY_109,
  /* 110 */  OBJ_SCENERY_110,
  /* 111 */  OBJ_SCENERY_111,
  /* 112 */  OBJ_SCENERY_112,
  /* 113 */  OBJ_SCENERY_113,
  /* 114 */  OBJ_SCENERY_114,
  /* 115 */  OBJ_SCENERY_115,
  /* 116 */  OBJ_SCENERY_116,
  /* 117 */  OBJ_SCENERY_117,
  /* 118 */  OBJ_SCENERY_118,
  /* 119 */  OBJ_SCENERY_119,
  /* 120 */  OBJ_SCENERY_120,
  /* 121 */  OBJ_SCENERY_121,
  /* 122 */  OBJ_SCENERY_122,
  /* 123 */  OBJ_SCENERY_123,
  /* 124 */  OBJ_SCENERY_124,
  /* 125 */  OBJ_SCENERY_125,
  /* 126 */  OBJ_SCENERY_126,
  /* 127 */  OBJ_SCENERY_127,
  /* 128 */  OBJ_SCENERY_128,
  /* 129 */  OBJ_SCENERY_129,
  /* 130 */  OBJ_SCENERY_130,
  /* 131 */  OBJ_SCENERY_131,
  /* 132 */  OBJ_SCENERY_132,
  /* 133 */  OBJ_SCENERY_133,
  /* 134 */  OBJ_SCENERY_134,
  /* 135 */  OBJ_SCENERY_135,
  /* 136 */  OBJ_SCENERY_136,
  /* 137 */  OBJ_SCENERY_137,
  /* 138 */  OBJ_SCENERY_138,
  /* 139 */  OBJ_SCENERY_139,
  /* 140 */  OBJ_SCENERY_140,
  /* 141 */  OBJ_SCENERY_141,
  /* 142 */  OBJ_SCENERY_142,
  /* 143 */  OBJ_SCENERY_143,
  /* 144 */  OBJ_SCENERY_144,
  /* 145 */  OBJ_SCENERY_145,
  /* 146 */  OBJ_SCENERY_146,
  /* 147 */  OBJ_SCENERY_147,
  /* 148 */  OBJ_SCENERY_148,
  /* 149 */  OBJ_SCENERY_149,
  /* 150 */  OBJ_SCENERY_150,
  /* 151 */  OBJ_SCENERY_151,
  /* 152 */  OBJ_SCENERY_152,
  /* 153 */  OBJ_SCENERY_153,
  /* 154 */  OBJ_SCENERY_154,
  /* 155 */  OBJ_SCENERY_155,
  /* 156 */  OBJ_SCENERY_156,
  /* 157 */  OBJ_SCENERY_157,
  /* 158 */  OBJ_SCENERY_158,
  /* 159 */  OBJ_SCENERY_159,
  /* 160 */  OBJ_SCENERY_160,
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
  /* 189 */  OBJ_ACTOR_DEBRIS,
  /* 190 */  OBJ_ACTOR_190,
  /* 191 */  OBJ_ACTOR_191,
  /* 192 */  OBJ_ACTOR_192,
  /* 193 */  OBJ_ACTOR_193,
  /* 194 */  OBJ_ACTOR_194,
  /* 195 */  OBJ_ACTOR_CUTSCENE,
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
  /* 306 */  OBJ_BOSS_TI,
  /* 307 */  OBJ_BOSS_ZO,
  /* 308 */  OBJ_BOSS_FO,
  /* 309 */  OBJ_BOSS_309,
  /* 310 */  OBJ_BOSS_310,
  /* 311 */  OBJ_BOSS_311,
  /* 312 */  OBJ_BOSS_VE2,
  /* 313 */  OBJ_BOSS_SZ,
  /* 314 */  OBJ_BOSS_SY,
  /* 315 */  OBJ_BOSS_SO,
  /* 316 */  OBJ_BOSS_KA,
  /* 317 */  OBJ_BOSS_KA_BASE,
  /* 318 */  OBJ_BOSS_AQ,
  /* 319 */  OBJ_BOSS_VE1,
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
  /* 339 */  OBJ_EFFECT_FIRE_SMOKE,
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
  /* 407 */  OBJ_ID_MAX,
} ObjectId;

#define OBJ_SCENERY_START OBJ_SCENERY_0
#define OBJ_SPRITE_START  OBJ_SPRITE_CO_POLE
#define OBJ_ACTOR_START   OBJ_ACTOR_176
#define OBJ_BOSS_START    OBJ_BOSS_292
#define OBJ_ITEM_START    OBJ_ITEM_LASERS
#define OBJ_EFFECT_START  OBJ_EFFECT_FIRE_SMOKE
#define OBJ_ENV_START     OBJ_UNK_400

#define OBJ_SCENERY_MAX   OBJ_SPRITE_START
#define OBJ_SPRITE_MAX    OBJ_ACTOR_START
#define OBJ_ACTOR_MAX     OBJ_BOSS_START
#define OBJ_BOSS_MAX      OBJ_ITEM_START
#define OBJ_ITEM_MAX      OBJ_EFFECT_START
#define OBJ_EFFECT_MAX    OBJ_ENV_START

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

Actor* Game_SpawnActor(ObjectId);

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

typedef Scenery Scenery_0;
typedef Scenery Scenery_1;
typedef Scenery Scenery_2;
typedef Scenery Scenery_3;
typedef Scenery Scenery_4;
typedef Scenery Scenery_5;
typedef Scenery Scenery_6;
typedef Scenery Scenery_7;
typedef Scenery Scenery_8;
typedef Scenery Scenery_9;
typedef Scenery Scenery_10;
typedef Scenery Scenery_11;
typedef Scenery Scenery_12;
typedef Scenery Scenery_13;
typedef Scenery Scenery_14;
typedef Scenery Scenery_15;
typedef Scenery Scenery_16;
typedef Scenery Scenery_17;
typedef Scenery Scenery_18;
typedef Scenery Scenery_19;
typedef Scenery Scenery_20;
typedef Scenery Scenery_21;
typedef Scenery Scenery_22;
typedef Scenery Scenery_23;
typedef Scenery Scenery_24;
typedef Scenery Scenery_25;
typedef Scenery Scenery_26;
typedef Scenery Scenery_27;
typedef Scenery Scenery_28;
typedef Scenery Scenery_29;
typedef Scenery Scenery_30;
typedef Scenery Scenery_31;
typedef Scenery Scenery_32;
typedef Scenery Scenery_33;
typedef Scenery Scenery_34;
typedef Scenery Scenery_35;
typedef Scenery Scenery_36;
typedef Scenery Scenery_37;
typedef Scenery Scenery_38;
typedef Scenery MeteoTunnel;
typedef Scenery Scenery_40;
typedef Scenery Scenery_41;
typedef Scenery Scenery_42;
typedef Scenery Scenery_43;
typedef Scenery Scenery_44;
typedef Scenery Scenery_45;
typedef Scenery Scenery_46;
typedef Scenery Scenery_47;
typedef Scenery Scenery_48;
typedef Scenery Scenery_49;
typedef Scenery Scenery_50;
typedef Scenery Scenery_51;
typedef Scenery Scenery_52;
typedef Scenery Scenery_53;
typedef Scenery Scenery_54;
typedef Scenery Scenery_55;
typedef Scenery Scenery_56;
typedef Scenery Scenery_57;
typedef Scenery Scenery_58;
typedef Scenery Scenery_59;
typedef Scenery Scenery_60;
typedef Scenery Scenery_61;
typedef Scenery Scenery_62;
typedef Scenery Scenery_63;
typedef Scenery Scenery_64;
typedef Scenery Scenery_65;
typedef Scenery Scenery_66;
typedef Scenery Scenery_67;
typedef Scenery Scenery_68;
typedef Scenery Scenery_69;
typedef Scenery Scenery_70;
typedef Scenery Scenery_71;
typedef Scenery Scenery_72;
typedef Scenery Scenery_73;
typedef Scenery Scenery_74;
typedef Scenery Scenery_75;
typedef Scenery Scenery_76;
typedef Scenery Scenery_77;
typedef Scenery Scenery_78;
typedef Scenery Scenery_79;
typedef Scenery Scenery_80;
typedef Scenery Scenery_81;
typedef Scenery Scenery_82;
typedef Scenery Scenery_83;
typedef Scenery Scenery_84;
typedef Scenery Scenery_85;
typedef Scenery Scenery_86;
typedef Scenery Scenery_87;
typedef Scenery Scenery_88;
typedef Scenery Scenery_89;
typedef Scenery Scenery_90;
typedef Scenery Scenery_91;
typedef Scenery Scenery_92;
typedef Scenery Scenery_93;
typedef Scenery Scenery_94;
typedef Scenery Scenery_95;
typedef Scenery Scenery_96;
typedef Scenery Scenery_97;
typedef Scenery Scenery_98;
typedef Scenery Scenery_99;
typedef Scenery Scenery_100;
typedef Scenery Scenery_101;
typedef Scenery Scenery_102;
typedef Scenery Scenery_103;
typedef Scenery Scenery_104;
typedef Scenery Scenery_105;
typedef Scenery Scenery_106;
typedef Scenery Scenery_107;
typedef Scenery Scenery_108;
typedef Scenery Scenery_109;
typedef Scenery Scenery_110;
typedef Scenery Scenery_111;
typedef Scenery Scenery_112;
typedef Scenery Scenery_113;
typedef Scenery Scenery_114;
typedef Scenery Scenery_115;
typedef Scenery Scenery_116;
typedef Scenery Scenery_117;
typedef Scenery Scenery_118;
typedef Scenery Scenery_119;
typedef Scenery Scenery_120;
typedef Scenery Scenery_121;
typedef Scenery Scenery_122;
typedef Scenery Scenery_123;
typedef Scenery Scenery_124;
typedef Scenery Scenery_125;
typedef Scenery Scenery_126;
typedef Scenery Scenery_127;
typedef Scenery Scenery_128;
typedef Scenery Scenery_129;
typedef Scenery Scenery_130;
typedef Scenery Scenery_131;
typedef Scenery Scenery_132;
typedef Scenery Scenery_133;
typedef Scenery Scenery_134;
typedef Scenery Scenery_135;
typedef Scenery Scenery_136;
typedef Scenery Scenery_137;
typedef Scenery Scenery_138;
typedef Scenery Scenery_139;
typedef Scenery Scenery_140;
typedef Scenery Scenery_141;
typedef Scenery Scenery_142;
typedef Scenery Scenery_143;
typedef Scenery Scenery_144;
typedef Scenery Scenery_145;
typedef Scenery Scenery_146;
typedef Scenery Scenery_147;
typedef Scenery Scenery_148;
typedef Scenery Scenery_149;
typedef Scenery Scenery_150;
typedef Scenery Scenery_151;
typedef Scenery Scenery_152;
typedef Scenery Scenery_153;
typedef Scenery Scenery_154;
typedef Scenery Scenery_155;
typedef Scenery Scenery_156;
typedef Scenery Scenery_157;
typedef Scenery Scenery_158;
typedef Scenery Scenery_159;
typedef Scenery Scenery_160;
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
typedef Actor ActorDebris;
typedef Actor Actor190;
typedef Actor Actor191;
typedef Actor Actor192;
typedef Actor Actor193;
typedef Actor Actor194;
typedef Actor ActorCutscene;
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
typedef Boss Saucerer;
typedef Boss Frontlinebase;
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
typedef Effect EffectFireSmoke;
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
