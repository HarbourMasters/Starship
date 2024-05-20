#ifndef SF64_LEVEL
#define SF64_LEVEL

#define SAVE_SLOT_SOLAR 13
#define SAVE_SLOT_VENOM_1 14
#define SAVE_SLOT_VENOM_2 15

typedef enum LevelType {
    /* 0 */ LEVELTYPE_PLANET,
    /* 1 */ LEVELTYPE_SPACE,
    /* 2 */ LEVELTYPE_UNK2,
    /* 3 */ LEVELTYPE_UNK3,
} LevelType;

typedef enum MissionStatus {
    /* 0 */ MISSION_COMPLETE,
    /* 1 */ MISSION_ACCOMPLISHED,
    /* 2 */ MISSION_WARP,
    /* 3 */ MISSION_MAX,
} MissionStatus;

typedef struct Environment {
    /* 0x00 */ s32 type;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ u16 bgColor;
    /* 0x0A */ u16 seqId;
    /* 0x0C */ s32 fogR;
    /* 0x10 */ s32 fogG;
    /* 0x14 */ s32 fogB;
    /* 0x18 */ s32 fogN;
    /* 0x1C */ s32 fogF;
    /* 0x20 */ Vec3f lightDir;
    /* 0x2C */ s32 lightR;
    /* 0x30 */ s32 lightG;
    /* 0x34 */ s32 lightB;
    /* 0x38 */ s32 ambR;
    /* 0x3C */ s32 ambG;
    /* 0x40 */ s32 ambB;
} Environment; // size = 0x44

typedef enum GroundType {
    /*  0 */ GROUND_0,
    /*  1 */ GROUND_1,
    /*  2 */ GROUND_2,
    /*  3 */ GROUND_3,
    /*  4 */ GROUND_4,
    /*  5 */ GROUND_5,
    /*  6 */ GROUND_6,
    /*  7 */ GROUND_7,
    /* 10 */ GROUND_10 = 10,
    /* 11 */ GROUND_11,
    /* 12 */ GROUND_12,
    /* 13 */ GROUND_13,
} GroundType;

typedef enum SceneId {
    /*  0 */ SCENE_TITLE,
    /*  1 */ SCENE_MENU,
    /*  2 */ SCENE_MAP,
    /*  3 */ SCENE_GAME_OVER,
    /*  4 */ SCENE_CREDITS,
    /*  5 */ SCENE_CORNERIA,
    /*  6 */ SCENE_METEO,
    /*  7 */ SCENE_TITANIA,
    /*  8 */ SCENE_SECTOR_X,
    /*  9 */ SCENE_AQUAS,
    /* 10 */ SCENE_AREA_6,
    /* 11 */ SCENE_FORTUNA,
    /* 12 */ SCENE_UNK_4,
    /* 13 */ SCENE_SECTOR_Y,
    /* 14 */ SCENE_SOLAR,
    /* 15 */ SCENE_ZONESS,
    /* 16 */ SCENE_VENOM_ANDROSS,
    /* 17 */ SCENE_TRAINING,
    /* 18 */ SCENE_VENOM_1,
    /* 19 */ SCENE_KATINA,
    /* 20 */ SCENE_20,
    /* 21 */ SCENE_MACBETH,
    /* 22 */ SCENE_BOLSE,
    /* 23 */ SCENE_SECTOR_Z,
    /* 24 */ SCENE_VENOM_2,
    /* 50 */ SCENE_VERSUS = 50,
    /* 99 */ SCENE_LOGO = 99,
} SceneId;

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

typedef enum GroundSurface {
    /* 0 */ SURFACE_GRASS,
    /* 1 */ SURFACE_ROCK,
    /* 2 */ SURFACE_WATER,
} GroundSurface;

#endif
