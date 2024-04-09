#ifndef SF64_LEVEL
#define SF64_LEVEL

#include "structs.h"

#define SAVE_SLOT_SOLAR 13
#define SAVE_SLOT_VENOM_1 14
#define SAVE_SLOT_VENOM_2 15

typedef enum {
    /* 0 */ LEVELTYPE_PLANET,
    /* 1 */ LEVELTYPE_SPACE,
    /* 2 */ LEVELTYPE_UNK2,
    /* 3 */ LEVELTYPE_UNK3,
} LevelType;

typedef struct {
    /* 0x00 */ s32 type;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ u16 bgColor;
    /* 0x0A */ u16 seqId;
    /* 0x0C */ s32 fogR;
    /* 0x10 */ s32 fogG;
    /* 0x14 */ s32 fogB;
    /* 0x18 */ s32 fogN;
    /* 0x1C */ s32 fogF;
    /* 0x20 */ Vec3f unk_20;
    /* 0x2C */ s32 lightR;
    /* 0x30 */ s32 lightG;
    /* 0x34 */ s32 lightB;
    /* 0x38 */ s32 ambR;
    /* 0x3C */ s32 ambG;
    /* 0x40 */ s32 ambB;
} EnvSettings; // size = 0x44

typedef enum {
    /*  0 */ OVL_SETUP_TITLE,
    /*  1 */ OVL_SETUP_MENU,
    /*  2 */ OVL_SETUP_MAP,
    /*  3 */ OVL_SETUP_GAME_OVER,
    /*  4 */ OVL_SETUP_CREDITS,
    /*  5 */ OVL_SETUP_CORNERIA,
    /*  6 */ OVL_SETUP_METEO,
    /*  7 */ OVL_SETUP_TITANIA,
    /*  8 */ OVL_SETUP_SECTOR_X,
    /*  9 */ OVL_SETUP_AQUAS,
    /* 10 */ OVL_SETUP_AREA_6,
    /* 11 */ OVL_SETUP_FORTUNA,
    /* 12 */ OVL_SETUP_UNK_4,
    /* 13 */ OVL_SETUP_SECTOR_Y,
    /* 14 */ OVL_SETUP_SOLAR,
    /* 15 */ OVL_SETUP_ZONESS,
    /* 16 */ OVL_SETUP_VENOM_ANDROSS,
    /* 17 */ OVL_SETUP_TRAINING,
    /* 18 */ OVL_SETUP_VENOM_1,
    /* 19 */ OVL_SETUP_KATINA,
    /* 10 */ OVL_SETUP_20,
    /* 11 */ OVL_SETUP_MACBETH,
    /* 12 */ OVL_SETUP_BOLSE,
    /* 13 */ OVL_SETUP_SECTOR_Z,
    /* 14 */ OVL_SETUP_VENOM_2,
    /* 50 */ OVL_SETUP_VERSUS = 50,
    /* 99 */ OVL_SETUP_LOGO = 99,
} OverlaySetups;

typedef enum LevelId {
    /* -1 */ LEVEL_UNK_M1 = -1,
    /*  0 */ LEVEL_CORNERIA,
    /*  1 */ LEVEL_METEO,
    /*  2 */ LEVEL_SECTOR_X,
    /*  3 */ LEVEL_AREA_6,
    /*  4 */ LEVEL_UNK_4,
    /*  5 */ LEVEL_SECTOR_Y,
    /*  6 */ LEVEL_VENOM_1,
    /*  7 */ LEVEL_SOLAR,
    /*  8 */ LEVEL_ZONESS,
    /*  9 */ LEVEL_VENOM_ANDROSS,
    /* 10 */ LEVEL_TRAINING,
    /* 11 */ LEVEL_MACBETH,
    /* 12 */ LEVEL_TITANIA,
    /* 13 */ LEVEL_AQUAS,
    /* 14 */ LEVEL_FORTUNA,
    /* 15 */ LEVEL_UNK_15,
    /* 16 */ LEVEL_KATINA,
    /* 17 */ LEVEL_BOLSE,
    /* 18 */ LEVEL_SECTOR_Z,
    /* 19 */ LEVEL_VENOM_2,
    /* 20 */ LEVEL_VERSUS,
    /* 77 */ LEVEL_WARP_ZONE = 77,
} LevelId;

typedef enum PlanetId {
    /* -1 */ PLANET_NONE=-1,
    /*  0 */ PLANET_METEO,
    /*  1 */ PLANET_AREA_6,
    /*  2 */ PLANET_BOLSE,
    /*  3 */ PLANET_SECTOR_Z,
    /*  4 */ PLANET_SECTOR_X,
    /*  5 */ PLANET_SECTOR_Y,
    /*  6 */ PLANET_KATINA,
    /*  7 */ PLANET_MACBETH,
    /*  8 */ PLANET_ZONESS,
    /*  9 */ PLANET_CORNERIA,
    /* 10 */ PLANET_TITANIA,
    /* 11 */ PLANET_AQUAS,
    /* 12 */ PLANET_FORTUNA,
    /* 13 */ PLANET_VENOM,
    /* 14 */ PLANET_SOLAR,
    /* 15 */ PLANET_MAX,
} PlanetId;

typedef enum VsStage {
    /* 0 */ VS_STAGE_CORNERIA,
    /* 1 */ VS_STAGE_KATINA,
    /* 2 */ VS_STAGE_SECTOR_Z,
} VsStage;

typedef enum GroundType {
    /* 0 */ GROUNDTYPE_GRASS,
    /* 1 */ GROUNDTYPE_ROCK,
    /* 2 */ GROUNDTYPE_WATER,
} GroundType;

#endif
