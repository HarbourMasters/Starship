#ifndef SF64_EVENT
#define SF64_EVENT

#define EV_OPC(opcode) (((opcode) & 0x7F) << 9)
#define EV_OPC_MASK(cmd) ((cmd) & (0x7F << 9))
#define EVENT_CMD(opcode, arg1, arg2) (EV_OPC(opcode) | ((s16) (arg1) & 0x1FF)), (arg2)

#define EV_ZMODE(zmode) (((zmode) & 3) << 7)
#define EV_ZMODE_MASK(cmd) ((cmd) & (3 << 7))

#define EV_CHANGE_AI 200

#define EVENT_PLAY_MSG(rcid, msg) EVENT_CMD(EVOP_PLAY_MSG, rcid, msg)
#define EVENT_STOP_SCRIPT() EVENT_CMD(EVOP_STOP_SCRIPT, 0, 0)
#define EVENT_MAKE_TEXLINE(color) EVENT_CMD(EVOP_MAKE_TEXLINE, 0, color)
#define EVENT_STOP_TEXLINE() EVENT_CMD(EVOP_STOP_TEXLINE, 0, 0)
#define EVENT_INIT_ACTOR(info, health) EVENT_CMD(EVOP_INIT_ACTOR, health, info)
#define EVENT_SET_SPEED(speed, zmode, time) EVENT_CMD(EVOP_SET_SPEED, EV_ZMODE(zmode) | ((speed) & 0x7F), time)
#define EVENT_SET_ACCEL(speedTarget, zmode, time) EVENT_CMD(EVOP_SET_ACCEL, EV_ZMODE(zmode) | ((speedTarget) & 0x7F), time)
#define EVENT_SET_ROTATE() EVENT_CMD(EVOP_SET_ROTATE, 0, 0)
#define EVENT_STOP_ROTATE() EVENT_CMD(EVOP_STOP_ROTATE, 0, 0)
#define EVENT_SET_TRIGGER(cond, cmd) EVENT_CMD(EVOP_SET_TRIGGER, cmd, cond)
#define EVENT_CLEAR_TRIGGER(cmd) EVENT_SET_TRIGGER(EVC_NONE, cmd)
#define EVENT_LOOP(count, cmd) EVENT_CMD(EVOP_LOOP, cmd, count)
#define EVENT_GOTO(cmd) EVENT_LOOP(0, cmd)
#define EVENT_SET_GROUND(type) EVENT_CMD(EVOP_SET_GROUND, 0, type)
#define EVENT_DROP_ITEM(item) EVENT_CMD(EVOP_DROP_ITEM, 0, item)
#define EVENT_ADD_TO_GROUP(num, flags) EVENT_CMD(EVOP_ADD_TO_GROUP, flags, num)
#define EVENT_SET_REVERB(reverb) EVENT_CMD(EVOP_SET_REVERB, 0, reverb)
#define EVENT_STOP_BGM() EVENT_CMD(EVOP_STOP_BGM, 0, 0)
#define EVENT_SET_ACTION(action) EVENT_CMD(EVOP_SET_ACTION, 0, action)
#define EVENT_RESTORE_TEAM(teammate) EVENT_CMD(EVOP_RESTORE_TEAM, 0, teammate)
#define EVENT_PLAY_SFX(sfx) EVENT_CMD(EVOP_PLAY_SFX, 0, sfx)
#define EVENT_STOP_SFX(sfx) EVENT_CMD(EVOP_STOP_SFX, 0, sfx)
#define EVENT_SET_CALL(duration, voiceParam) EVENT_CMD(EVOP_SET_CALL, voiceParam, duration)
#define EVENT_ROT_PLUS_X(rot, rotVel) EVENT_CMD(EVOP_ROT_PLUS_X, rotVel * 10, rot)
#define EVENT_ROT_MINUS_X(rot, rotVel) EVENT_CMD(EVOP_ROT_MINUS_X, rotVel * 10, rot)
#define EVENT_ROT_PLUS_Y(rot, rotVel) EVENT_CMD(EVOP_ROT_PLUS_Y, rotVel * 10, rot)
#define EVENT_ROT_MINUS_Y(rot, rotVel) EVENT_CMD(EVOP_ROT_MINUS_Y, rotVel * 10, rot)
#define EVENT_ROT_PLUS_Z(rot, rotVel) EVENT_CMD(EVOP_ROT_PLUS_Z, rotVel * 10, rot)
#define EVENT_ROT_MINUS_Z(rot, rotVel) EVENT_CMD(EVOP_ROT_MINUS_Z, rotVel * 10, rot)
#define EVENT_F4_PLUS_X(rot, rotVel) EVENT_CMD(EVOP_F4_PLUS_X, rotVel * 10, rot)
#define EVENT_F4_MINUS_X(rot, rotVel) EVENT_CMD(EVOP_F4_MINUS_X, rotVel * 10, rot)
#define EVENT_F4_PLUS_Y(rot, rotVel) EVENT_CMD(EVOP_F4_PLUS_Y, rotVel * 10, rot)
#define EVENT_F4_MINUS_Y(rot, rotVel) EVENT_CMD(EVOP_F4_MINUS_Y, rotVel * 10, rot)
#define EVENT_SET_BASE_ZVEL(zvel) EVENT_CMD(EVOP_SET_BASE_ZVEL, 0, zvel)
#define EVENT_SET_TEAM_ID(teamId) EVENT_CMD(EVOP_SET_TEAM_ID, 0, teamId)
#define EVENT_DAMAGE_TEAM(teamId, damage) EVENT_CMD(EVOP_DAMAGE_TEAM, damage, teamId)
#define EVENT_SET_TARGET(teamId, spread) EVENT_CMD(EVOP_SET_TARGET, teamId, spread)
#define EVENT_CHASE_TARGET(duration, turnRate) EVENT_CMD(EVOP_CHASE_TARGET, duration, turnRate)

typedef enum EventModeZ {
    EMZ_REST,
    EMZ_RELATIVE,
    EMZ_PLAYER,
    EMZ_3,
} EventModeZ;

typedef enum EventOpcode {
    /*   0 */ EVOP_SET_SPEED,
    /*   1 */ EVOP_SET_ACCEL,
    /*   2 */ EVOP_SET_BASE_ZVEL,
    /*   3 */ EVOP_SET_TO_IWORK_9,
    /*   4 */ EVOP_SET_IWORK_13,
    /*   8 */ EVOP_CLEAR_IWORK_13 = 8,
    /*   9 */ EVOP_F4_PLUS_X,
    /*  10 */ EVOP_F4_MINUS_X,
    /*  11 */ EVOP_F4_PLUS_Y,
    /*  12 */ EVOP_F4_MINUS_Y,
    /*  16 */ EVOP_ROT_PLUS_X = 16,
    /*  17 */ EVOP_ROT_MINUS_X,
    /*  18 */ EVOP_ROT_PLUS_Y,
    /*  19 */ EVOP_ROT_MINUS_Y,
    /*  20 */ EVOP_ROT_PLUS_Z,
    /*  21 */ EVOP_ROT_MINUS_Z,
    /*  24 */ EVOP_SET_ROTATE = 24,
    /*  25 */ EVOP_STOP_ROTATE,
    /*  40 */ EVOP_SET_STATE_6 = 40,
    /*  41 */ EVOP_SET_STATE_7,
    /*  42 */ EVOP_SET_STATE_8,
    /*  43 */ EVOP_SET_STATE_9,
    /*  44 */ EVOP_CHASE_TARGET,
    /*  45 */ EVOP_SET_TARGET,
    /*  46 */ EVOP_SET_STATE_14,
    /*  47 */ EVOP_SET_STATE_15,
    /*  48 */ EVOP_SET_WAIT,
    /*  56 */ EVOP_SET_CALL = 56,
    /*  57 */ EVOP_RESTORE_TEAM,
    /*  58 */ EVOP_PLAY_SFX,
    /*  59 */ EVOP_STOP_SFX,
    /*  96 */ EVOP_SET_TRIGGER = 96,
    /* 104 */ EVOP_INIT_ACTOR = 104,
    /* 105 */ EVOP_SET_TEAM_ID,
    /* 112 */ EVOP_SET_ACTION = 112,
    /* 113 */ EVOP_ADD_TO_GROUP,
    /* 116 */ EVOP_DROP_ITEM = 116,
    /* 118 */ EVOP_SET_REVERB = 118,
    /* 119 */ EVOP_SET_GROUND,
    /* 120 */ EVOP_PLAY_MSG,
    /* 121 */ EVOP_DAMAGE_TEAM,
    /* 122 */ EVOP_STOP_BGM,
    /* 124 */ EVOP_MAKE_TEXLINE = 124,
    /* 125 */ EVOP_STOP_TEXLINE,
    /* 126 */ EVOP_LOOP,
    /* 127 */ EVOP_STOP_SCRIPT,
} EventOpcode;

typedef enum EventCondition {
    /*  0 */ EVC_NONE,
    /*  1 */ EVC_1,
    /*  2 */ EVC_TEAM_COUNT_3,
    /*  3 */ EVC_TEAM_COUNT_2,
    /*  4 */ EVC_TEAM_COUNT_1,
    /*  5 */ EVC_TEAM_COUNT_0,
    /*  6 */ EVC_FALCO_ACTIVE,
    /*  7 */ EVC_PEPPY_ACTIVE,
    /*  8 */ EVC_SLIPPY_ACTIVE,
    /*  9 */ EVC_CLOSE_LEFT_100,
    /* 10 */ EVC_CLOSE_LEFT_400,
    /* 11 */ EVC_CLOSE_LEFT_700,
    /* 12 */ EVC_CLOSE_LEFT_200,
    /* 13 */ EVC_CLOSE_RIGHT_100,
    /* 14 */ EVC_CLOSE_RIGHT_400,
    /* 15 */ EVC_CLOSE_RIGHT_700,
    /* 16 */ EVC_CLOSE_RIGHT_200,
    /* 17 */ EVC_CLOSE_ABOVE_100,
    /* 18 */ EVC_CLOSE_ABOVE_400,
    /* 19 */ EVC_CLOSE_ABOVE_700,
    /* 20 */ EVC_CLOSE_ABOVE_200,
    /* 21 */ EVC_CLOSE_BELOW_100,
    /* 22 */ EVC_CLOSE_BELOW_400,
    /* 23 */ EVC_CLOSE_BELOW_700,
    /* 24 */ EVC_CLOSE_BELOW_200,
    /* 25 */ EVC_HEALTH_100p,
    /* 26 */ EVC_HEALTH_75p,
    /* 27 */ EVC_HEALTH_50p,
    /* 28 */ EVC_HEALTH_25p,
    /* 29 */ EVC_HEALTH_0p,
    /* 30 */ EVC_UNK270_5PLUS,
    /* 31 */ EVC_UNK270_NONZERO,
    /* 32 */ EVC_UNK270_ZERO,
    /* 33 */ EVC_UNK250_GREATER_168,
    /* 34 */ EVC_UNK250_LESS_84,
    /* 35 */ EVC_SINGLE_LASER,
    /* 36 */ EVC_TWIN_LASER,
    /* 37 */ EVC_HYPER_LASER,
    /* 38 */ EVC_UNK3_LASER,
    /* 39 */ EVC_SHOT_CLOSE_150,
    /* 40 */ EVC_SHOT_CLOSE_300,
    /* 41 */ EVC_41,
    /* 42 */ EVC_42,
    /* 43 */ EVC_43,
    /* 44 */ EVC_TOOK_DAMAGE,
    /* 45 */ EVC_PASSED_ALL_RINGS,
    /* 46 */ EVC_46,
    /* 47 */ EVC_PRESS_CRIGHT,
    /* 48 */ EVC_WING_BROKEN,
    /* 49 */ EVC_ME_CLEAR,
    /* 50 */ EVC_FO_CLEAR,
    /* 51 */ EVC_SX_CLEAR,
    /* 52 */ EVC_TI_CLEAR,
    /* 53 */ EVC_BO_CLEAR,
    /* 54 */ EVC_SY_CLEAR,
    /* 55 */ EVC_KA_CLEAR,
    /* 56 */ EVC_SO_CLEAR,
    /* 57 */ EVC_MA_CLEAR,
    /* 58 */ EVC_AQ_CLEAR,
    /* 59 */ EVC_ZO_CLEAR,
    /* 60 */ EVC_SZ_CLEAR,
    /* 61 */ EVC_A6_CLEAR,
    /* 62 */ EVC_62,
    /* 63 */ EVC_63,
    /* 64 */ EVC_MISSED_SEARCHLIGHT,
    /* 65 */ EVC_30_HITS,
    /* 66 */ EVC_80_HITS,
    /* 67 */ EVC_EXPERT_MODE,
    /* 68 */ EVC_68,
    /* 69 */ EVC_69,
    /* 100 */ EVC_100=100,
} EventCondition;

typedef enum EventState {
    /*  0 */ EVSTATE_READY,
    /*  1 */ EVSTATE_WAIT,
    /*  2 */ EVSTATE_F4_PLUS_X,
    /*  3 */ EVSTATE_F4_MINUS_X,
    /*  4 */ EVSTATE_F4_PLUS_Y,
    /*  5 */ EVSTATE_F4_MINUS_Y,
    /*  6 */ EVSTATE_6,
    /*  7 */ EVSTATE_7,
    /*  8 */ EVSTATE_8,
    /*  9 */ EVSTATE_9,
    /* 10 */ EVSTATE_ME_AS_OPEN,
    /* 11 */ EVSTATE_ME_AS_CLOSE,
    /* 12 */ EVSTATE_TEAM_RETREAT,
    /* 13 */ EVSTATE_CHASE_TARGET,
    /* 14 */ EVSTATE_14,
    /* 15 */ EVSTATE_15,  
    /* 200 */ EVSTATE_SCRIPT_END = 200,
    /* 1000 */ EVSTATE_1000 = 1000,
} EventState;

typedef enum EventAction {
    /*  0 */ EVACT_NONE,
    /*  1 */ EVACT_1,
    /*  2 */ EVACT_2,
    /*  3 */ EVACT_3,
    /*  4 */ EVACT_4,
    /*  5 */ EVACT_5,
    /*  6 */ EVACT_6,
    /*  7 */ EVACT_7,
    /*  8 */ EVACT_8,
    /*  9 */ EVACT_9,
    /* 10 */ EVACT_10,
    /* 11 */ EVACT_11,
    /* 12 */ EVACT_DESPAWN,
    /* 13 */ EVACT_13,
    /* 14 */ EVACT_ME_AS_OPEN,
    /* 15 */ EVACT_ME_AS_CLOSE,
    /* 16 */ EVACT_16,
    /* 17 */ EVACT_17,
    /* 18 */ EVACT_GFOX_COVER_FIRE,
    /* 19 */ EVACT_19,
} EventAction;

typedef enum EventActorInfo {
    /*   0 */ EINFO_0,
    /*   1 */ EINFO_1,
    /*   2 */ EINFO_2,
    /*   3 */ EINFO_3,
    /*   4 */ EINFO_4,
    /*   5 */ EINFO_5,
    /*   6 */ EINFO_6,
    /*   7 */ EINFO_7,
    /*   8 */ EINFO_8,
    /*   9 */ EINFO_9,
    /*  10 */ EINFO_10,
    /*  11 */ EINFO_11,
    /*  12 */ EINFO_12,
    /*  13 */ EINFO_13,
    /*  14 */ EINFO_14,
    /*  15 */ EINFO_15,
    /*  16 */ EINFO_16,
    /*  17 */ EINFO_17,
    /*  18 */ EINFO_18,
    /*  19 */ EINFO_19,
    /*  20 */ EINFO_20,
    /*  21 */ EINFO_21,
    /*  22 */ EINFO_22,
    /*  23 */ EINFO_23,
    /*  24 */ EINFO_24,
    /*  25 */ EINFO_25,
    /*  26 */ EINFO_26,
    /*  27 */ EINFO_27,
    /*  28 */ EINFO_28,
    /*  29 */ EINFO_29,
    /*  30 */ EINFO_30,
    /*  31 */ EINFO_31,
    /*  32 */ EINFO_32,
    /*  33 */ EINFO_33,
    /*  34 */ EINFO_34,
    /*  35 */ EINFO_35,
    /*  36 */ EINFO_36,
    /*  37 */ EINFO_37,
    /*  38 */ EINFO_38,
    /*  39 */ EINFO_39,
    /*  40 */ EINFO_40,
    /*  41 */ EINFO_41,
    /*  42 */ EINFO_42,
    /*  43 */ EINFO_43,
    /*  44 */ EINFO_44,
    /*  45 */ EINFO_45,
    /*  46 */ EINFO_46,
    /*  47 */ EINFO_47,
    /*  48 */ EINFO_48,
    /*  49 */ EINFO_49,
    /*  50 */ EINFO_50,
    /*  51 */ EINFO_51,
    /*  52 */ EINFO_52,
    /*  53 */ EINFO_53,
    /*  54 */ EINFO_54,
    /*  55 */ EINFO_55,
    /*  56 */ EINFO_56,
    /*  57 */ EINFO_57,
    /*  58 */ EINFO_58,
    /*  59 */ EINFO_59,
    /*  60 */ EINFO_60,
    /*  61 */ EINFO_61,
    /*  62 */ EINFO_62,
    /*  63 */ EINFO_63,
    /*  64 */ EINFO_64,
    /*  65 */ EINFO_65,
    /*  66 */ EINFO_66,
    /*  67 */ EINFO_67,
    /*  68 */ EINFO_68,
    /*  69 */ EINFO_69,
    /*  70 */ EINFO_70,
    /*  71 */ EINFO_71,
    /*  72 */ EINFO_72,
    /*  73 */ EINFO_73,
    /*  74 */ EINFO_74,
    /*  75 */ EINFO_75,
    /*  76 */ EINFO_76,
    /*  77 */ EINFO_77,
    /*  78 */ EINFO_78,
    /*  79 */ EINFO_79,
    /*  80 */ EINFO_80,
    /*  81 */ EINFO_81,
    /*  82 */ EINFO_82,
    /*  83 */ EINFO_83,
    /*  84 */ EINFO_84,
    /*  85 */ EINFO_85,
    /*  86 */ EINFO_86,
    /*  87 */ EINFO_87,
    /*  88 */ EINFO_88,
    /*  89 */ EINFO_89,
    /*  90 */ EINFO_90,
    /*  91 */ EINFO_91,
    /*  92 */ EINFO_92,
    /*  93 */ EINFO_93,
    /*  94 */ EINFO_94,
    /*  95 */ EINFO_95,
    /*  96 */ EINFO_96,
    /*  97 */ EINFO_97,
    /*  98 */ EINFO_98,
    /*  99 */ EINFO_99,
    /* 100 */ EINFO_100,
    /* 101 */ EINFO_101,
    /* 102 */ EINFO_102,
    /* 103 */ EINFO_103,
    /* 104 */ EINFO_104,
    /* 105 */ EINFO_105,
    /* 106 */ EINFO_106,
    /* 107 */ EINFO_107,
    /* 200 */ EINFO_200 = 200,
    /* 300 */ EINFO_300 = 300,
} EventActorInfo;

typedef enum EventSfx {
    /*  0 */ EVSFX_0,
    /*  1 */ EVSFX_1,
    /*  2 */ EVSFX_2,
    /*  3 */ EVSFX_3,
    /*  4 */ EVSFX_4,
    /*  5 */ EVSFX_5,
    /*  6 */ EVSFX_6,
    /*  7 */ EVSFX_7,
    /*  8 */ EVSFX_8,
    /*  9 */ EVSFX_9,
    /* 10 */ EVSFX_10,
    /* 11 */ EVSFX_11,
    /* 12 */ EVSFX_12,
    /* 13 */ EVSFX_13,
    /* 14 */ EVSFX_14,
    /* 15 */ EVSFX_15,
    /* 16 */ EVSFX_16,
    /* 17 */ EVSFX_17,
    /* 18 */ EVSFX_18,
    /* 19 */ EVSFX_19,
    /* 20 */ EVSFX_20,
    /* 21 */ EVSFX_21,
    /* 22 */ EVSFX_22,
} EventSfx;

typedef enum TexLineColor {
    /* 0 */ TXLC_WHITE,
    /* 1 */ TXLC_LIGHT_BLUE,
    /* 2 */ TXLC_BLUE,
    /* 3 */ TXLC_GREEN,
    /* 4 */ TXLC_RED,
    /* 5 */ TXLC_YELLOW,
} TexLineColor;

#endif
