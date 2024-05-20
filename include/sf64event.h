#ifndef SF64_EVENT
#define SF64_EVENT

#define evaLoopCount(actor) (actor)->iwork[0]
#define evaTargetActorIndex(actor) (actor)->iwork[1]
#define evaTrigCondition(actor) (actor)->iwork[2]
#define evaTrigCmdIndex(actor) (actor)->iwork[3]
#define EvaIwork4(actor) (actor)->iwork[4]
#define evaMoveModeZ(actor) (actor)->iwork[5]
#define evaRotateFlag(actor) (actor)->iwork[6]
#define evaTexLineFlag(actor) (actor)->iwork[7]
#define evaTexLineIndex(actor) (actor)->iwork[8]
#define evaLeaderActorIndex(actor) (actor)->iwork[9]
#define EvaIwork10(actor) (actor)->iwork[10]
#define EvaIwork11(actor) (actor)->iwork[11]
#define EvaIwork12(actor) (actor)->iwork[12]
#define evaFormationFly(actor) (actor)->iwork[13]
#define EvaIwork14(actor) (actor)->iwork[14]
#define EvaIwork15(actor) (actor)->iwork[15]
#define EvaIwork16(actor) (actor)->iwork[16]
#define EvaIwork17(actor) (actor)->iwork[17]
#define EvaIwork18(actor) (actor)->iwork[18]
#define EvaIwork19(actor) (actor)->iwork[19]
#define evaTrigCondition0(actor) (actor)->iwork[20]
#define evaTrigCondition1(actor) (actor)->iwork[21]
#define evaTrigCondition2(actor) (actor)->iwork[22]
#define evaTrigCondition3(actor) (actor)->iwork[23]
#define evaTrigCondition4(actor) (actor)->iwork[24]

#define EvaFwork0(actor) (actor)->fwork[0]
#define EvaFwork1(actor) (actor)->fwork[1]
#define EvaFwork2(actor) (actor)->fwork[2]
#define EvaFwork3(actor) (actor)->fwork[3]
#define EvaFwork4(actor) (actor)->fwork[4]
#define EvaFwork5(actor) (actor)->fwork[5]
#define EvaFwork6(actor) (actor)->fwork[6]
#define EvaFwork7(actor) (actor)->fwork[7]
#define EvaFwork8(actor) (actor)->fwork[8]
#define EvaFwork9(actor) (actor)->fwork[9]
#define EvaFwork10(actor) (actor)->fwork[10]
#define EvaFwork11(actor) (actor)->fwork[11]
#define EvaFwork12(actor) (actor)->fwork[12]
#define EvaFwork13(actor) (actor)->fwork[13]
#define EvaFwork14(actor) (actor)->fwork[14]
#define EvaFwork15(actor) (actor)->fwork[15]
#define EvaFwork16(actor) (actor)->fwork[16]
#define evaTargetSpread(actor) (actor)->fwork[17]
#define EvaFwork18(actor) (actor)->fwork[18]
#define EvaFwork19(actor) (actor)->fwork[19]
#define EvaFwork20(actor) (actor)->fwork[20]
#define EvaFwork21(actor) (actor)->fwork[21]
#define EvaFwork22(actor) (actor)->fwork[22]
#define EvaFwork23(actor) (actor)->fwork[23]
#define evaTargetTurnRate(actor) (actor)->fwork[24]
#define EvaFwork25(actor) (actor)->fwork[25]
#define EvaFwork26(actor) (actor)->fwork[26]
#define EvaFwork27(actor) (actor)->fwork[27]
#define EvaFwork28(actor) (actor)->fwork[28]
#define EvaFwork29(actor) (actor)->fwork[29]

#define EV_OPC(opcode) (((opcode) & 0x7F) << 9)
#define EV_OPC_MASK(cmd) ((cmd) & (0x7F << 9))
#define EVENT_CMD(opcode, arg1, arg2) (EV_OPC(opcode) | ((s16) (arg1) & 0x1FF)), (arg2)

#define EV_ZMODE(zmode) (((zmode) & 3) << 7)
#define EV_ZMODE_MASK(cmd) ((cmd) & (3 << 7))

#define EV_CHANGE_AI 200

#define EVENT_SET_SPEED(speed, zmode, time) EVENT_CMD(EVOP_SET_SPEED, EV_ZMODE(zmode) | ((speed) & 0x7F), time)
#define EVENT_SET_ACCEL(speedTarget, zmode, time) EVENT_CMD(EVOP_SET_ACCEL, EV_ZMODE(zmode) | ((speedTarget) & 0x7F), time)
#define EVENT_SET_BASE_ZVEL(zvel) EVENT_CMD(EVOP_SET_BASE_ZVEL, 0, zvel)
#define EVENT_SET_AS_LEADER() EVENT_CMD(EVOP_SET_AS_LEADER, 0 ,0 )
#define EVENT_START_FORMATION(duration) EVENT_CMD(EVOP_START_FORMATION, 0, duration)
#define EVENT_STOP_FORMATION() EVENT_CMD(EVOP_STOP_FORMATION, 0, 0)

#define EVENT_F4_PLUS_X(rot, rotVel) EVENT_CMD(EVOP_F4_PLUS_X, (rotVel) * 10, rot)
#define EVENT_F4_MINUS_X(rot, rotVel) EVENT_CMD(EVOP_F4_MINUS_X, (rotVel) * 10, rot)
#define EVENT_F4_PLUS_Y(rot, rotVel) EVENT_CMD(EVOP_F4_PLUS_Y, (rotVel) * 10, rot)
#define EVENT_F4_MINUS_Y(rot, rotVel) EVENT_CMD(EVOP_F4_MINUS_Y, (rotVel) * 10, rot)

#define EVENT_ROT_PLUS_X(rot, rotVel) EVENT_CMD(EVOP_ROT_PLUS_X, (rotVel) * 10, rot)
#define EVENT_ROT_MINUS_X(rot, rotVel) EVENT_CMD(EVOP_ROT_MINUS_X, (rotVel) * 10, rot)
#define EVENT_ROT_PLUS_Y(rot, rotVel) EVENT_CMD(EVOP_ROT_PLUS_Y, (rotVel) * 10, rot)
#define EVENT_ROT_MINUS_Y(rot, rotVel) EVENT_CMD(EVOP_ROT_MINUS_Y, (rotVel) * 10, rot)
#define EVENT_ROT_PLUS_Z(rot, rotVel) EVENT_CMD(EVOP_ROT_PLUS_Z, (rotVel) * 10, rot)
#define EVENT_ROT_MINUS_Z(rot, rotVel) EVENT_CMD(EVOP_ROT_MINUS_Z, (rotVel) * 10, rot)

#define EVENT_SET_ROTATE() EVENT_CMD(EVOP_SET_ROTATE, 0, 0)
#define EVENT_STOP_ROTATE() EVENT_CMD(EVOP_STOP_ROTATE, 0, 0)

#define EVENT_PURSUE_PLAYER(duration, turnRate) EVENT_CMD(EVOP_PURSUE_PLAYER, turnRate, duration)
#define EVENT_FLEE_PLAYER(duration, turnRate) EVENT_CMD(EVOP_FLEE_PLAYER, turnRate, duration)
#define EVENT_PURSUE_TARGET(duration, turnRate) EVENT_CMD(EVOP_PURSUE_TARGET, turnRate, duration)
#define EVENT_FLEE_TARGET(duration, turnRate) EVENT_CMD(EVOP_FLEE_TARGET, turnRate, duration)
#define EVENT_CHASE_TARGET(duration, turnRate) EVENT_CMD(EVOP_CHASE_TARGET, turnRate, duration)
#define EVENT_SET_TARGET(teamId, spread) EVENT_CMD(EVOP_SET_TARGET, teamId, spread)
#define EVENT_PURSUE_CAMERA(duration, turnRate) EVENT_CMD(EVOP_PURSUE_CAMERA, turnRate, duration)
#define EVENT_FLEE_CAMERA(duration, turnRate) EVENT_CMD(EVOP_FLEE_CAMERA, turnRate, duration)
#define EVENT_SET_WAIT(duration) EVENT_CMD(EVOP_SET_WAIT, 0, duration)

#define EVENT_SET_CALL(duration, voiceParam) EVENT_CMD(EVOP_SET_CALL, voiceParam, duration)
#define EVENT_RESTORE_TEAM(teammate) EVENT_CMD(EVOP_RESTORE_TEAM, 0, teammate)
#define EVENT_PLAY_SFX(sfx) EVENT_CMD(EVOP_PLAY_SFX, 0, sfx)
#define EVENT_STOP_SFX(sfx) EVENT_CMD(EVOP_STOP_SFX, 0, sfx)

#define EVENT_SET_TRIGGER(cond, cmd) EVENT_CMD(EVOP_SET_TRIGGER, cmd, cond)
#define EVENT_SET_Z_TRIGGER(z, cmd) EVENT_SET_TRIGGER(EVC_CLOSE_Z + (s32)((z) / 100), cmd)
#define EVENT_CLEAR_TRIGGER(cmd) EVENT_SET_TRIGGER(EVC_NONE, cmd)

#define EVENT_INIT_ACTOR(info, health) EVENT_CMD(EVOP_INIT_ACTOR, health, info)
#define EVENT_SET_TEAM_ID(teamId) EVENT_CMD(EVOP_SET_TEAM_ID, 0, teamId)

#define EVENT_SET_ACTION(action) EVENT_CMD(EVOP_SET_ACTION, 0, action)
#define EVENT_ADD_TO_GROUP(num, flags) EVENT_CMD(EVOP_ADD_TO_GROUP, flags, num)

#define EVENT_DROP_ITEM(item) EVENT_CMD(EVOP_DROP_ITEM, 0, item)

#define EVENT_SET_REVERB(reverb) EVENT_CMD(EVOP_SET_REVERB, 0, reverb)
#define EVENT_SET_SURFACE(type) EVENT_CMD(EVOP_SET_SURFACE, 0, type)
#define EVENT_PLAY_MSG(rcid, msg) EVENT_CMD(EVOP_PLAY_MSG, rcid, msg)
#define EVENT_DAMAGE_TEAM(teamId, damage) EVENT_CMD(EVOP_DAMAGE_TEAM, damage, teamId)
#define EVENT_STOP_BGM() EVENT_CMD(EVOP_STOP_BGM, 0, 0)

#define EVENT_MAKE_TEXLINE(color) EVENT_CMD(EVOP_MAKE_TEXLINE, 0, color)
#define EVENT_STOP_TEXLINE() EVENT_CMD(EVOP_STOP_TEXLINE, 0, 0)

#define EVENT_LOOP(count, cmd) EVENT_CMD(EVOP_LOOP, cmd, count)
#define EVENT_GOTO(cmd) EVENT_LOOP(0, cmd)

#define EVENT_STOP_SCRIPT() EVENT_CMD(EVOP_STOP_SCRIPT, 0, 0)


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
    /*   3 */ EVOP_SET_AS_LEADER,
    /*   4 */ EVOP_START_FORMATION,
    /*   8 */ EVOP_STOP_FORMATION = 8,
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
    /*  40 */ EVOP_PURSUE_PLAYER = 40,
    /*  41 */ EVOP_FLEE_PLAYER,
    /*  42 */ EVOP_PURSUE_TARGET,
    /*  43 */ EVOP_FLEE_TARGET,
    /*  44 */ EVOP_CHASE_TARGET,
    /*  45 */ EVOP_SET_TARGET,
    /*  46 */ EVOP_PURSUE_CAMERA,
    /*  47 */ EVOP_FLEE_CAMERA,
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
    /* 119 */ EVOP_SET_SURFACE,
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
    /*  1 */ EVC_NO_TARGET,
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
    /* 41 */ EVC_NO_LEADER,
    /* 42 */ EVC_NO_FOLLOWER,
    /* 43 */ EVC_HAS_FOLLOWER,
    /* 44 */ EVC_TOOK_DAMAGE,
    /* 45 */ EVC_PASSED_ALL_RINGS,
    /* 46 */ EVC_ATTACK_GROUP_CLEARED,
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
    /* 62 */ EVC_NOT_CHASED,
    /* 63 */ EVC_CHASED,
    /* 64 */ EVC_MISSED_SEARCHLIGHT,
    /* 65 */ EVC_30_HITS,
    /* 66 */ EVC_80_HITS,
    /* 67 */ EVC_EXPERT_MODE,
    /* 100 */ EVC_CLOSE_Z=100,
} EventCondition;

typedef enum EventState {
    /*  0 */ EVSTATE_READY,
    /*  1 */ EVSTATE_WAIT,
    /*  2 */ EVSTATE_F4_PLUS_X,
    /*  3 */ EVSTATE_F4_MINUS_X,
    /*  4 */ EVSTATE_F4_PLUS_Y,
    /*  5 */ EVSTATE_F4_MINUS_Y,
    /*  6 */ EVSTATE_PURSUE_PLAYER,
    /*  7 */ EVSTATE_FLEE_PLAYER,
    /*  8 */ EVSTATE_PURSUE_TARGET,
    /*  9 */ EVSTATE_FLEE_TARGET,
    /* 10 */ EVSTATE_ME_AS_OPEN,
    /* 11 */ EVSTATE_ME_AS_CLOSE,
    /* 12 */ EVSTATE_TEAM_RETREAT,
    /* 13 */ EVSTATE_CHASE_TARGET,
    /* 14 */ EVSTATE_PURSUE_CAMERA,
    /* 15 */ EVSTATE_FLEE_CAMERA,  
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
    /* 13 */ EVACT_TI_DROP_MINE,
    /* 14 */ EVACT_ME_AS_OPEN,
    /* 15 */ EVACT_ME_AS_CLOSE,
    /* 16 */ EVACT_16,
    /* 17 */ EVACT_17,
    /* 18 */ EVACT_GFOX_COVER_FIRE,
    /* 19 */ EVACT_19,
} EventAction;

typedef enum EventActorId {
    /*   0 */ EVID_0,
    /*   1 */ EVID_1,
    /*   2 */ EVID_2,
    /*   3 */ EVID_3,
    /*   4 */ EVID_4,
    /*   5 */ EVID_5,
    /*   6 */ EVID_6,
    /*   7 */ EVID_7,
    /*   8 */ EVID_8,
    /*   9 */ EVID_9,
    /*  10 */ EVID_10,
    /*  11 */ EVID_11,
    /*  12 */ EVID_12,
    /*  13 */ EVID_13,
    /*  14 */ EVID_14,
    /*  15 */ EVID_15,
    /*  16 */ EVID_16,
    /*  17 */ EVID_17,
    /*  18 */ EVID_18,
    /*  19 */ EVID_19,
    /*  20 */ EVID_20,
    /*  21 */ EVID_A6_MISSILE,
    /*  22 */ EVID_A6_ROCKET,
    /*  23 */ EVID_23,
    /*  24 */ EVID_24,
    /*  25 */ EVID_25,
    /*  26 */ EVID_26,
    /*  27 */ EVID_27,
    /*  28 */ EVID_28,
    /*  29 */ EVID_29,
    /*  30 */ EVID_30,
    /*  31 */ EVID_31,
    /*  32 */ EVID_32,
    /*  33 */ EVID_33,
    /*  34 */ EVID_34,
    /*  35 */ EVID_35,
    /*  36 */ EVID_36,
    /*  37 */ EVID_37,
    /*  38 */ EVID_SX_WARP_GATE,
    /*  39 */ EVID_39,
    /*  40 */ EVID_EVENT_HANDLER,
    /*  41 */ EVID_41,
    /*  42 */ EVID_42,
    /*  43 */ EVID_TEAMMATE,
    /*  44 */ EVID_44,
    /*  45 */ EVID_45,
    /*  46 */ EVID_46,
    /*  47 */ EVID_47,
    /*  48 */ EVID_48,
    /*  49 */ EVID_49,
    /*  50 */ EVID_50,
    /*  51 */ EVID_51,
    /*  52 */ EVID_52,
    /*  53 */ EVID_53,
    /*  54 */ EVID_54,
    /*  55 */ EVID_55,
    /*  56 */ EVID_56,
    /*  57 */ EVID_57,
    /*  58 */ EVID_58,
    /*  59 */ EVID_59,
    /*  60 */ EVID_60,
    /*  61 */ EVID_61,
    /*  62 */ EVID_62,
    /*  63 */ EVID_63,
    /*  64 */ EVID_64,
    /*  65 */ EVID_65,
    /*  66 */ EVID_66,
    /*  67 */ EVID_METEO_PYRAMID_SHIP,
    /*  68 */ EVID_68,
    /*  69 */ EVID_69,
    /*  70 */ EVID_70,
    /*  71 */ EVID_WING_REPAIR,
    /*  72 */ EVID_72,
    /*  73 */ EVID_73,
    /*  74 */ EVID_74,
    /*  75 */ EVID_75,
    /*  76 */ EVID_76,
    /*  77 */ EVID_77,
    /*  78 */ EVID_SUPPLY_CRATE,
    /*  79 */ EVID_79,
    /*  80 */ EVID_80,
    /*  81 */ EVID_81,
    /*  82 */ EVID_82,
    /*  83 */ EVID_AQ_CLAM,
    /*  84 */ EVID_84,
    /*  85 */ EVID_BILL,
    /*  86 */ EVID_KATT,
    /*  87 */ EVID_87,
    /*  88 */ EVID_AQ_STARFISH,
    /*  89 */ EVID_89,
    /*  90 */ EVID_90,
    /*  91 */ EVID_91,
    /*  92 */ EVID_92,
    /*  93 */ EVID_93,
    /*  94 */ EVID_94,
    /*  95 */ EVID_95,
    /*  96 */ EVID_96,
    /*  97 */ EVID_97,
    /*  98 */ EVID_98,
    /*  99 */ EVID_99,
    /* 100 */ EVID_100,
    /* 101 */ EVID_101,
    /* 102 */ EVID_TR_BARRIER,
    /* 103 */ EVID_ANDROSS_GATE,
    /* 104 */ EVID_ANDROSS_GATE_2,
    /* 105 */ EVID_SX_WARP_ENMY,
    /* 106 */ EVID_KILLER_BEE,
    /* 107 */ EVID_MA_SHOT_GATE,
    /* 200 */ EVID_200 = 200,
    /* 300 */ EVID_300 = 300,
    /* 4095*/ EVID_FFF = 4095,
} EventActorId;

typedef enum EventSfx {
    /*  0 */ EVSFX_OB_SLIDE_OPEN,
    /*  1 */ EVSFX_OB_SLIDE_CLOSE,
    /*  2 */ EVSFX_OB_STEELFRAME,
    /*  3 */ EVSFX_OB_HEAVY_BOUND,
    /*  4 */ EVSFX_ITEM_APPEAR,
    /*  5 */ EVSFX_OB_BLOCK_APPEAR,
    /*  6 */ EVSFX_OB_ROCKWALL_UP,
    /*  7 */ EVSFX_EN_UNIT_GATHERING,
    /*  8 */ EVSFX_EN_MOTOR_STOP,
    /*  9 */ EVSFX_EN_MS_DASH,
    /* 10 */ EVSFX_OB_ROCK_CRASH,
    /* 11 */ EVSFX_OB_ROCK_EYE_OPEN,
    /* 12 */ EVSFX_OB_SHIP_FALLDOWN,
    /* 13 */ EVSFX_OB_BOUND_M,
    /* 14 */ EVSFX_OB_SPEAR_PILLAR,
    /* 15 */ EVSFX_OB_PILLER_ROLL,
    /* 16 */ EVSFX_SEARCHLIGHT_MISS,
    /* 17 */ EVSFX_OB_ROUTEGATE_OPEN_Q,
    /* 18 */ EVSFX_OB_ROUTEGATE_CLOSE_Q,
    /* 19 */ EVSFX_OB_ROUTEGATE_OPEN_S,
    /* 20 */ EVSFX_OB_ROUTEGATE_CLOSE_S,
    /* 21 */ EVSFX_OB_LIFT,
    /* 22 */ EVSFX_OB_PLATE_ROLL,
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
