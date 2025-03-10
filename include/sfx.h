#ifndef SFX_H
#define SFX_H

#include "sys.h"

#ifdef __cplusplus
extern "C" {
#endif

extern f32 gDefaultSfxSource[];
extern f32 gDefaultMod;
extern s8 gDefaultReverb;

void Audio_PlaySfx(u32 sfxId, f32* sfxSource, u8 token, f32* freqMod, f32* volMod, s8* reverbAdd);
void Audio_KillSfxByBank(u8 bankId);
void Audio_StopSfxByBankAndSource(u8 bankId, f32* sfxSource);
void Audio_KillSfxByBankAndSource(u8 bankId, f32* sfxSource);
void Audio_KillSfxBySource(f32* sfxSource);
void Audio_KillSfxBySourceAndId(f32* sfxSource, u32 sfxId);
void Audio_KillSfxByTokenAndId(u8 token, u32 sfxId);
void Audio_KillSfxById(u32 sfxId);
void Audio_StartPlayerNoise(u8 playerId);
void Audio_StopPlayerNoise(u8 playerId);
void Audio_InitBombSfx(u8 playerId, u8 type);
void Audio_PlayBombFlightSfx(u8 playerId, f32* sfxSource);
void Audio_PlayBombExplodeSfx(u8 playerId, f32* sfxSource);
void Audio_StopEngineNoise(f32* sfxSource);
void Audio_SetSfxSpeedModulation(f32 vel);
void Audio_SetTransposeAndPlaySfx(f32* sfxSource, u32 sfxId, u8 semitones);
void Audio_SetModulationAndPlaySfx(f32* sfxSource, u32 sfxId, f32 freqMod);
void Audio_PlaySfxModulated(f32* sfxSource, u32 sfxId);
void Audio_SetSfxMapModulation(u8 fMod);
void Audio_SetHeatAlarmParams(u8 shields, u8 heightParam);
void Audio_PlayEventSfx(f32* sfxSource, u16 eventSfxId);
void Audio_StopEventSfx(f32* sfxSource, u16 eventSfxId);
void Audio_SetEnvSfxReverb(s8 reverb);
void Audio_PlayPauseSfx(u8 active);
void Audio_PlayMapMenuSfx(u8 active);
void Audio_KillAllSfx(void);
void Audio_SetVoiceLanguage(u8 language);

#ifdef __cplusplus
}
#endif

#define AUDIO_PLAY_SFX(sfxId, srcPos, token) (Audio_PlaySfx((sfxId),(srcPos),(token),&gDefaultMod,&gDefaultMod,&gDefaultReverb))

#define SFX_FLAG_18 (1 << 18)  // makes distance ignore z position? probably more
#define SFX_FLAG_19 (1 << 19)
#define SFX_FLAG_20 (1 << 20)  // make priority ignore distance
#define SFX_FLAG_21 (1 << 21)  // make reverb ignore distance
#define SFX_FLAG_22 (1 << 22)  // make volume ignore distance
#define SFX_FLAG_23 (1 << 23)  // make noisy

#define SFX_FLAG_27 (1 << 27)  // allow duplicate requests

#define SFX_BANK_SHIFT 28
#define SFX_STATE_SHIFT 24
#define SFX_RANGE_SHIFT 16
#define SFX_IMPORT_SHIFT 8

#define SFX_BANK_MASK (0xF << SFX_BANK_SHIFT)
#define SFX_STATE_FLAG (1 << SFX_STATE_SHIFT)
#define SFX_RANGE_MASK (3 << SFX_RANGE_SHIFT)
#define SFX_IMPORT_MASK (0xFF << SFX_IMPORT_SHIFT)

#define SFX_BANK(sfxId) ((((sfxId) & SFX_BANK_MASK) >> SFX_BANK_SHIFT) & 0xFF)
#define SFX_BANK_ALT(sfxId) (((sfxId) >> SFX_BANK_SHIFT) & 0xFF)
#define SFX_STATE(sfxId) (((sfxId) & SFX_STATE_FLAG) >> SFX_STATE_SHIFT)
#define SFX_RANGE(sfxId) ((((sfxId) & SFX_RANGE_MASK) >> SFX_RANGE_SHIFT) & 0xFF)
#define SFX_IMPORT(sfxId) ((((sfxId) & SFX_IMPORT_MASK) >> SFX_IMPORT_SHIFT) & 0xFF)
#define SFX_INDEX(sfxId) ((sfxId) & 0xFF)

#define SFX_PACK(bank, index, range, importance, flags) \
        ((((bank)<<SFX_BANK_SHIFT)&SFX_BANK_MASK)|(((range)<<SFX_RANGE_SHIFT)&SFX_RANGE_MASK)|\
        (((importance)<<SFX_IMPORT_SHIFT)&SFX_IMPORT_MASK)|((index)&0xFF)|SFX_STATE_FLAG|(flags))

typedef enum SfxBankId {
    SFX_BANK_PLAYER,
    SFX_BANK_1,
    SFX_BANK_2,
    SFX_BANK_3,
    SFX_BANK_SYSTEM,
} SfxBankId;

#define NA_SE_NONE                  0x00000000

#define NA_SE_TURRET_SHOT           0x09000000 // Invented name. Appears in unused turret mode.
#define NA_SE_ARWING_SHOT           0x09400000
#define NA_SE_SMART_BOMB_SHOT       0x09001001
#define NA_SE_ARWING_BOOST          0x09000002
#define NA_SE_ARWING_DASH           0x09004002 // Boost variant used by Venom 1 intro and boss Titania
#define NA_SE_ARWING_BRAKE          0x09000003
#define NA_SE_ARWING_EXPLOSION      0x0903F004
#define NA_SE_SLIPPY_HIT            0x09000004 // From Sector X boss
#define NA_SE_ARWING_ENGIN_GRD      0x0100F005
#define NA_SE_TANK_ENGIN            0x0100F006
#define NA_SE_WING_OPEN             0x09000007
#define NA_SE_BOMB_CHARGE           0x01008008 // iniial bomb flight. only plays for 1 frame. Bombs were chargeable?
#define NA_SE_BOMB_EXPLODE0         0x0901A009 // unused bomb explosion
#define NA_SE_BOMB_EXPLODE1         0x0903A00A // used bomb explosion
#define NA_SE_BOMB_EXPLODE2         0x0901A00B // unused bomb explosion
#define NA_SE_BACKUP_CLEAR          0x0940A00B // Also used for explosion on Corneria at game start
#define NA_SE_ARWING_TWIN_LASER     0x0940800C
#define NA_SE_ZERO_SHIELD           0x0900000D // Unreferenced. Sounds like an explosion
#define NA_SE_DAMAGE_S              0x0903900E
#define NA_SE_DAMAGE_L              0x0903A00F
#define NA_SE_ARWING_DOWN           0x0900C010
#define NA_SE_ROLLING_REFLECT       0x09007011
#define NA_SE_ROLLING_AIR           0x09000012
#define NA_SE_WING_OPEN_END         0x09000013
#define NA_SE_LIFT_UP_END           0x09002013
#define NA_SE_TANK_SHOT             0x09000014 // Also used for on-foot shot
#define NA_SE_TANK_BOUND            0x09008015 // Same as NA_SE_TANK_WALL_HIT
#define NA_SE_TANK_WALL_HIT         0x09008015 // Same as NA_SE_TANK_BOUND
#define NA_SE_TANK_GO_UP            0x01008016
#define NA_SE_MAR_ROLLING_AIR       0x09000017
#define NA_SE_STEP_FOX              0x09000018 // Unreferenced
#define NA_SE_STEP_FALCO            0x09000019 // Unreferenced
#define NA_SE_STEP_PEPPY            0x0900001A // Unreferenced
#define NA_SE_STEP_SLIPPY           0x0900001B // Unreferenced
#define NA_SE_DEMO_RUNNING          0x0140001C
#define NA_SE_LIFT_UP               0x0100001D
#define NA_SE_ENGINE_START          0x0100001E
#define NA_SE_VOLUME_TEST           0x0100001F
#define NA_SE_ARWING_ENGIN_SPC      0x0100F020
#define NA_SE_MAR_SHOT              0x09400021
#define NA_SE_MARINE_ENGINE00       0x0100F022
#define NA_SE_WING_REPAIR           0x09008023
#define NA_SE_TANK_BURNER_HALF      0x01004024
#define NA_SE_MAR_BOMB_SHOT         0x01000025
#define NA_SE_MAR_LAUNCH            0x01038026
#define NA_SE_MAR_TWIN_LASER        0x09400027 // Also used for hyper lasers
#define NA_SE_MAR_BOUND             0x09404028
#define NA_SE_LOCK_ON_LASER         0x09007029 // Charge shot fire
#define NA_SE_ARWING_WARP_DASH      0x0940802A // During warp zone entrance cutscene
#define NA_SE_MAP_ARWING_WARP_DASH  0x0900802A
#define NA_SE_ARWING_TWIN_LASER2    0x0940802B
#define NA_SE_ARWING_WING_BROKEN    0x0900A02C
#define NA_SE_LOCK_SEARCH           0x0900302D // Charge shot charge
#define NA_SE_SPREAD_EXPLOSION      0x0903502E // Charge shot/torpedo explode
#define NA_SE_TANK_DASH             0x0900402F
#define NA_SE_MARINE_BOOST          0x09004030
#define NA_SE_MARINE_BRAKE          0x09004031
#define NA_SE_MAP_ARWING_DASH       0x09000032

#define NA_SE_FALL                  0x11000000
#define NA_SE_PASS                  0x19000001
#define NA_SE_OB_METAL_BOUND_S      0x19030002 // Unreferenced.
#define NA_SE_OB_METAL_BOUND_M      0x19030003
#define NA_SE_EN_METAL_BOUND_M      0x19130003
#define NA_SE_EN_MS_LAND            0x19031003
#define NA_SE_OB_METAL_BOUND_L      0x19030004
#define NA_SE_OB_BLOCK_APPEAR       0x19122005
#define NA_SE_OB_BOUND_M            0x19020006
#define NA_SE_OB_ROCK_BOUND         0x19030006
#define NA_SE_OB_AQ_ROCK_BOUND      0x19400007
#define NA_SE_METALBOMB_REFLECT     0x19020008
#define NA_SE_OB_MA_SWITCH_UP       0x19033008
#define NA_SE_METALBOMB_BOUND       0x19030009 // Unreferenced.
#define NA_SE_TANK_SLIDE            0x1100000A
#define NA_SE_SPLASH_LEVEL_S        0x1100000B
#define NA_SE_SPLASH_LEVEL_L        0x1100000C
#define NA_SE_OB_GATE_OPEN          0x1900000D
#define NA_SE_OB_SLIDE_OPEN         0x1903000D
#define NA_SE_OB_GATE_CLOSE         0x1900000E
#define NA_SE_OB_SLIDE_CLOSE        0x1903000E
#define NA_SE_OB_EXPLOSION_S        0x1903400F
#define NA_SE_GREATFOX_ENGINE       0x11030010
#define NA_SE_EARTHQUAKE            0x11000011
#define NA_SE_MAP_ZOOM_START        0x19003012
#define NA_SE_MAP_ZOOM_END          0x19004013
#define NA_SE_OB_WATER_BOUND_M      0x19000014
#define NA_SE_OB_STEELFRAME         0x19500015
#define NA_SE_EXPLOSION_DEMO2       0x11030016
#define NA_SE_KA_UFO_FALLING        0x11404016
#define NA_SE_IN_SPLASH_S           0x19800017
#define NA_SE_OUT_SPLASH_S          0x19800018 // Unreferenced.
#define NA_SE_IN_SPLASH_L           0x19832019
#define NA_SE_OUT_SPLASH_L          0x1983201A
#define NA_SE_OB_CRAME_MOTOR        0x1900001B
#define NA_SE_OB_BROKEN_BOX         0x1903901C
#define NA_SE_OB_MINI_BOMB          0x1903001D
#define NA_SE_OB_WT_WHEEL_ROLL      0x1903001E
#define NA_SE_OB_WALL_UP            0x1903001F
#define NA_SE_ON_SPLASH_S           0x19000020
#define NA_SE_EN_PULL_CHAIN0        0x19003021
#define NA_SE_EN_GATHER_PARTS       0x11033022
#define NA_SE_EN_HEARTBEAT          0x11003023
#define NA_SE_OB_SAND_BOUND_S       0x19000024
#define NA_SE_KA_UFO_ENGINE         0x11037025
#define NA_SE_MAP_ZOOM_OUT          0x19000026
#define NA_SE_EN_BROKEN_SPARK       0x11000027             
#define NA_SE_OB_SPARK_BEAM         0x11000028
#define NA_SE_OB_BOMB_ALARM         0x19000029
#define NA_SE_WARP_HOLE             0x1900602A
#define NA_SE_OB_WING               0x1900302B
#define NA_SE_SUBMARINE_ATM         0x1100802C
#define NA_SE_WATER_PRESSURE        0x1900002D
#define NA_SE_BUBBLE_UP             0x1900002E
#define NA_SE_EN_WT_BROKEN          0x1902102F
#define NA_SE_EN_WT_DISAPPEAR_S     0x19003030
#define NA_SE_EN_WT_BOUND_M         0x19402031
#define NA_SE_OB_BOMB_ALARM_LAST    0x19000032
#define NA_SE_EN_WT_DISAPPEAR_L     0x19000033
#define NA_SE_EN_RNG_BEAM_CHARGE    0x11015034
#define NA_SE_EN_RNG_BEAM_SHOT      0x19006035
#define NA_SE_EN_SHIELD_ROLL        0x19030036
#define NA_SE_GREATFOX_SHOT_DEMO    0x19030037
#define NA_SE_WARP_RING_1           0x19404038
#define NA_SE_WARP_RING_2           0x19404139
#define NA_SE_WARP_RING_3           0x1940423A
#define NA_SE_WARP_RING_4           0x1940433B
#define NA_SE_WARP_RING_5           0x1940443C
#define NA_SE_WARP_RING_6           0x1940453D
#define NA_SE_WARP_RING_7           0x1940463E
#define NA_SE_KA_UFO_HATCH_OPEN     0x1903203F
#define NA_SE_KA_UFO_HATCH_CLOSE    0x19032040
#define NA_SE_KA_UFO_CORE_OPEN      0x19032041
#define NA_SE_BO_CORE_APPEAR        0x19034041
#define NA_SE_KA_UFO_HATCH_STOP     0x19034042
#define NA_SE_KA_UFO_LONG_CHARGE    0x11034043
#define NA_SE_KA_UFO_LAST_CHARGE    0x19406044
#define NA_SE_KA_UFO_BEAM           0x1140B045
#define NA_SE_EXPLOSION_DEMO3       0x11038046
#define NA_SE_KA_UFO_BOUND          0x19408047
#define NA_SE_OB_BARRIER_RELEASE    0x19401048
#define NA_SE_EN_SPACE_SNAKE        0x11032049
#define NA_SE_OB_ROCKWALL_UP        0x1913204A
#define NA_SE_COLONY_LEVEL          0x1100004B // Unreferenced.
#define NA_SE_MAP_MOVE              0x1100004C
#define NA_SE_MAP_ROLL              0x1100204C
#define NA_SE_MAP_LINE_DRAW         0x1900404D
#define NA_SE_SHIP_ENGINE_SPC       0x1100004E // Unreferenced.
#define NA_SE_OB_BROKEN_SPARK_L     0x1900404F
#define NA_SE_EN_SHIELD_ROLL_LEVEL  0x11002050
#define NA_SE_EN_SHIELD_ROLL_STOP   0x19004051
#define NA_SE_OB_MAGMA_WAVE         0x11002052
#define NA_SE_EN_OUT_PROMINENCE     0x19035053
#define NA_SE_EN_OUT_MAGMA          0x19036053
#define NA_SE_EN_IN_PROMINENCE      0x19035054
#define NA_SE_EN_IN_MAGMA           0x19036054
#define NA_SE_OB_SMOKE              0x11000055
#define NA_SE_OB_ROCK_CRASH         0x19032056
#define NA_SE_OB_ROCK_EYE_OPEN      0x19030057
#define NA_SE_OB_SHIP_FALLDOWN      0x19033058
#define NA_SE_EN_VEBOSS_BROKEN      0x19030059
#define NA_SE_OB_ARM_SWING          0x1903005A
#define NA_SE_OB_POLE_MOVE          0x1903205B
#define NA_SE_OB_POLE_BOUND         0x1903205C
#define NA_SE_OB_HEAVY_SWITCH       0x1940405D
#define NA_SE_OB_CONNECT_CUT        0x1940205E
#define NA_SE_OB_MA_SWITCH_ON       0x1903205F
#define NA_SE_OB_MA_SWITCH_GRN      0x19020060
#define NA_SE_OB_MA_SWITCH_RED      0x19020061
#define NA_SE_OB_POST_UP            0x19001062
#define NA_SE_OB_SIDE_GATE_CLOSE    0x11001063
#define NA_SE_OB_SPEAR_STICK        0x19032064
#define NA_SE_RAILWAY_BOUND         0x19000065
#define NA_SE_EN_MABOSS_HATCH       0x19034066
#define NA_SE_EN_MABOSS_CHARGE0     0x19022067
#define NA_SE_EN_MABOSS_SHOT0       0x19023068
#define NA_SE_EN_MABOSS_PLATECHARGE 0x19022069
#define NA_SE_VO_ANDROSS_PUNCH      0x1940306A
#define NA_SE_VO_ANDROSS_SLAP       0x1940306B
#define NA_SE_VO_ANDROSS_WHAND      0x1940306C
#define NA_SE_VO_ANDROSS_CHOKE      0x1940306D
#define NA_SE_VO_ANDROSS_LAUGH      0x1940306E
#define NA_SE_VO_ANDROSS_GROAN      0x1940306F
#define NA_SE_VO_ANDROSS_DEATH      0x19403070
#define NA_SE_OB_ROUTE_EXPLOSION0   0x11403071
#define NA_SE_OB_ROUTEGATE_OPEN_Q   0x19038072
#define NA_SE_EN_ANDROSS_ROBOT      0x11030073
#define NA_SE_EN_ANDROSS_BRAIN      0x11034074
#define NA_SE_EN_ANDROSS_EYE        0x11032075
#define NA_SE_OB_ROUTE_EXPLOSION1    0x11403076
#define NA_SE_OB_FISH_AWAY          0x19400077
#define NA_SE_OB_AQ_PILLAR_BROKE    0x19021078
#define NA_SE_WARP_OUT              0x11407079
#define NA_SE_ARWING_HATCH          0x1950107A
#define NA_SE_OB_POINT_SWITCH       0x1940807B
#define NA_SE_VO_ANDROSS_EXCITE     0x1940307C
#define NA_SE_OB_PILLAR_ROLL        0x1903407D
#define NA_SE_OB_ROUTEGATE_CLOSE_Q  0x1903807E
#define NA_SE_OB_ROUTEGATE_OPEN_S   0x1903807F
#define NA_SE_OB_ROUTEGATE_CLOSE_S  0x19038080 // events that play this are unused
#define NA_SE_OB_LIFT               0x11032081
#define NA_SE_OB_PLATE_ROLL         0x19031082
#define NA_SE_STARFOX_SEAL          0x19031083
#define NA_SE_EXPLOSION_DEMO6       0x11020084

#define NA_SE_EXPLOSION_S           0x29000000
#define NA_SE_BIG_EXPLOSION         0x29000001 // Unreferenced.
#define NA_SE_EN_SHOT_0             0x29002002
#define NA_SE_EN_DAMAGE_M           0x29024003
#define NA_SE_OB_DAMAGE_M           0x29034003
#define NA_SE_EN_BREATH             0x31000004 // Unreferenced.
#define NA_SE_EN_WOLF_ENGINE        0x31004005
#define NA_SE_EN_WOLF_ENGINE2       0x31004006
#define NA_SE_EN_REFLECT            0x29121007
#define NA_SE_EN_EXPLOSION_S        0x2903A008
#define NA_SE_EN_EXPLOSION_M        0x2903B009
#define NA_SE_EN_EXPLOSION_L        0x2940C00A
#define NA_SE_EN_CRASH_DOWN         0x2903700B
#define NA_SE_ARWING_ENGINE_FG      0x3100000C
#define NA_SE_ARWING_SHOT_F         0x2900000D
#define NA_SE_EN_DAMAGE_S           0x2903300E
#define NA_SE_EN_DAMAGE_L           0x2900300F
#define NA_SE_EN_KNOCK_DOWN         0x2943500F
#define NA_SE_EN_S_FIGHTER_ENGINE   0x31000010 // Unreferenced.
#define NA_SE_EN_ENGINE_01          0x31000011
#define NA_SE_EN_MISSILE_ENGINE     0x31000012
#define NA_SE_EN_LONG_BEAM          0x31000013
#define NA_SE_EN_ALIEN_FLY          0x31000014
#define NA_SE_EN_SPACE_SHIP         0x31000015
#define NA_SE_EN_TANK_RB_ENGINE     0x31000016
#define NA_SE_EN_TANK_ENGINE        0x31000017
#define NA_SE_A_CARRIER_ENGINE      0x31038018
#define NA_SE_EN_HEAVY_WALK         0x29022019
#define NA_SE_EN_HATCH              0x2940201A
#define NA_SE_EN_MISSILE_SHOT       0x2903101B
#define NA_SE_EN_BARREL_SHOT        0x2903201B
#define NA_SE_EN_THROW              0x2902401C
#define NA_SE_EN_MS_PUNCH           0x2903401C
#define NA_SE_EN_FALLING_DOWN       0x2900201D
#define NA_SE_EN_LASER_BEAM         0x3100001E
#define NA_SE_EN_HEAVY_WALK1        0x2902201F
#define NA_SE_EN_HEAVY_JUMP         0x29023020
#define NA_SE_EN_HEAVY_BOUND        0x29034021
#define NA_SE_OB_HEAVY_BOUND        0x2903A021
#define NA_SE_EN_COMBINE            0x29433022
#define NA_SE_EN_MOTOR_ROLL         0x29400023
#define NA_SE_EN_MOTOR_STOP         0x29034024
#define NA_SE_EN_UNIT_COMBINE       0x29402024
#define NA_SE_EN_ENERGY_BEAM        0x31000025
#define NA_SE_EN_ZOBOSS_BEAM        0x31034025
#define NA_SE_EN_BOSS_EXPLOSION     0x2902F026
#define NA_SE_EN_STAR_EXPLOSION     0x2940F026
#define NA_SE_EN_PARTS_BROKEN       0x2940C027
#define NA_SE_EN_THROW_S            0x29000028
#define NA_SE_EN_HEAVY_WALK2        0x29406029
#define NA_SE_EN_APPEAR_SAND        0x2900502A
#define NA_SE_EN_TIBOSS_AT_CRY      0x2940702B
#define NA_SE_EN_TIBOSS_DM_CRY      0x2940802C
#define NA_SE_EN_TIBOSS_DW_CRY      0x2940902D
#define NA_SE_EXPLOSION_DEMO        0x3140402E
#define NA_SE_EXPLOSION_DEMO5       0x3143402E
#define NA_SE_EN_BOSS_BEAM0         0x3143102F
#define NA_SE_EN_BOSS_CHARGE        0x39435830
#define NA_SE_OB_SAND_BOUND_M       0x29003031
#define NA_SE_EN_BOSS_ATTACK        0x29403031
#define NA_SE_OB_SPEAR_PILLAR       0x29503032
#define NA_SE_EN_WT_EXPLOSION_S     0x29038033
#define NA_SE_EN_WT_EXPLOSION_M     0x29000034 // Unreferenced.
#define NA_SE_EN_WT_EXPLOSION_L     0x29000035 // Unreferenced.
#define NA_SE_EN_BIRD_DOWN          0x29018036
#define NA_SE_EN_BIRD_DAMAGE        0x29033037
#define NA_SE_EN_SPIDER_MOVE        0x21000038 // Unreferenced.
#define NA_SE_EN_SHIP_ENGINE_S      0x31012039
#define NA_SE_EN_SHIP_ENGINE_L      0x3100203A
#define NA_SE_EN_S_BALL_SHOT        0x2903203B
#define NA_SE_EN_SINK_PARTS         0x2940983C
#define NA_SE_EN_M_BALL_SHOT        0x2900403D
#define NA_SE_EN_PULL_CHAIN1        0x3100503E
#define NA_SE_EN_HEART_OPEN         0x2900803F
#define NA_SE_ARWING_ENGINE_FS      0x31000040
#define NA_SE_EN_SNAKE_DAMAGE       0x29034041
#define NA_SE_EN_KANI_DOWN          0x29000042 // Unreferenced.
#define NA_SE_EN_KANI_MOTOR         0x31030043
#define NA_SE_EN_DISAPPEAR_SAND     0x29000044 // Unreferenced.
#define NA_SE_EN_SANADA_DAMAGE      0x29034045
#define NA_SE_EN_SANADA_DOWN        0x2902A046
#define NA_SE_EN_SANADA_SWIM        0x31000047
#define NA_SE_EN_SANADA_APPEAR      0x29022048
#define NA_SE_EN_SEA_EXPLOSION_S    0x29018049
#define NA_SE_EN_SEA_EXPLOSION_L    0x2900004A // Unreferenced.
#define NA_SE_EN_P_BALL_SHOT        0x2903404B
#define NA_SE_EN_WT_DAMAGE_S        0x2903604C
#define NA_SE_EN_EYEFILM_DAMAGE     0x2940604C
#define NA_SE_EN_SHELL_BEAT         0x3140904D
#define NA_SE_EN_SHELL_DAMAGE       0x2940804E
#define NA_SE_EN_SHELL_DOWN         0x2940A04F
#define NA_SE_EN_KAIBASHIRA_DAMAGE  0x29036050
#define NA_SE_EN_EYEFILM_REVIVAL    0x29409051
#define NA_SE_EN_P_GUN_APPEAR       0x29400052
#define NA_SE_EN_P_GUN_DISAPPEAR    0x29000053 // Unreferenced.
#define NA_SE_EN_SHELL_CLOSE        0x29408054
#define NA_SE_EN_SHELL_FILLOPEN     0x29408055
#define NA_SE_EN_S_BEAM_CHARGE      0x31016056
#define NA_SE_EN_S_BEAM_SHOT        0x31037057
#define NA_SE_EN_S_BEAM_END         0x29038058
#define NA_SE_GREATFOX_BURNER       0x31024059
#define NA_SE_EN_BURNER_L           0x3102505A
#define NA_SE_EN_GRN_BEAM_CHARGE    0x3103605B
#define NA_SE_EN_GRN_BEAM_SHOT      0x3102705C
#define NA_SE_EN_MEBOSS_SHIELD      0x3102405D
#define NA_SE_EN_CATCH              0x2902405E
#define NA_SE_EN_PASS               0x2903305F
#define NA_SE_EN_MS_EXPLOSION_S     0x2903A060
#define NA_SE_EN_SZMIS_ENGINE       0x31032061
#define NA_SE_EN_PUNCH_ENGINE       0x3103A061
#define NA_SE_EN_BARRIER_REFLECT    0x29001062
#define NA_SE_EN_ANDROSS_EXPLOSION  0x31009063
#define NA_SE_EN_SPARK_DAMAGE_M     0x29033064
#define NA_SE_EN_VEBOSS_DAMAGE      0x31034064
#define NA_SE_EN_ARM_SWING          0x29034065
#define NA_SE_EN_COVER_OPEN         0x31404066
#define NA_SE_EN_COVER_CLOSE        0x31404067
#define NA_SE_EN_COVER_MOVE_STOP    0x39404068
#define NA_SE_EN_ENERGY_BALL        0x31008069
#define NA_SE_EN_UNIT_GATHERING     0x2900306A
#define NA_SE_EN_MS_SHOT_S          0x2900306B
#define NA_SE_EN_MS_DASH            0x2902306C
#define NA_SE_EN_MS_KICK            0x2902306D
#define NA_SE_EN_MS_SHOT_L          0x2901306E
#define NA_SE_EN_MS_SHIELD_BROKEN   0x2903A06F
#define NA_SE_EN_MS_EXPLOSION_L     0x29000070 // Unreferenced.
#define NA_SE_OB_SOROCK_APPEAR      0x29000071
#define NA_SE_OB_SOROCK_DISAPPEAR   0x29000072
#define NA_SE_EN_SOBOSS_CRY         0x29432073
#define NA_SE_EN_SOBOSS_DAMAGE      0x29433074
#define NA_SE_EN_SOBOSS_BROKEN      0x29434075
#define NA_SE_EN_SOBOSS_DOWN        0x39439076
#define NA_SE_EN_SOBOSS_SWING       0x29432077
#define NA_SE_EN_SOBOSS_BREATH      0x31033078
#define NA_SE_EN_SOBOSS_ROLL        0x39033079
#define NA_SE_EN_ANGLER_DAMAGE      0x2900007A // Unreferenced.
#define NA_SE_EN_ANGLER_DOWN        0x2900007B // Unreferenced.
#define NA_SE_BANK2_UNK_7C          0x2100007C // Unreferenced. Sounds like many small explosions
#define NA_SE_ROCK_REFLECT          0x2902107D       
#define NA_SE_OB_MAGMA_BUBBLE       0x3140807E
#define NA_SE_BANK2_UNK_7F          0x2900007F // Unreferenced. Sounds like an impact
#define NA_SE_OB_VEBOSS_WALK        0x29032080
#define NA_SE_OB_VEBOSS_JUMP        0x29033081
#define NA_SE_OB_VEBOSS_LAND        0x29034082
#define NA_SE_OB_VEBOSS_ATTACK      0x31030083
#define NA_SE_OB_VEBOSS_BOUND       0x29405084
#define NA_SE_EN_FREIGHT_TRAIN      0x31078085
#define NA_SE_EN_MABOSS_REFLECT     0x29022086
#define NA_SE_EN_ANDROSS_BREATH     0x31022087
#define NA_SE_EN_ANDROSS_BITE0      0x29022088
#define NA_SE_EN_ANDROSS_BITE1      0x29022089
#define NA_SE_EN_ANDROSS_VOMIT      0x3140208A
#define NA_SE_EN_ANDROSS_SPARK      0x3103108B
#define NA_SE_EN_WT_THROW           0x2900308C
#define NA_SE_EN_WT_SPARK_CHARGE    0x2900208D
#define NA_SE_EN_WT_SPARK_BEAM      0x3100208E
#define NA_SE_EN_AQ_ZAKO_DAMAGE     0x2903408F
#define NA_SE_EN_AQ_ZAKO_DOWN       0x29038090
#define NA_SE_EN_WARP_IN            0x39408091
#define NA_SE_EN_WARP_OUT           0x39408092
#define NA_SE_EN_A6BOSS_CHARGE      0x39033093
#define NA_SE_EN_A6BOSS_BEAM        0x31405094
#define NA_SE_EN_TRAIN_BREAK        0x31408095
#define NA_SE_EN_ANDROSS_WARP       0x2940B096
#define NA_SE_EN_ANDROSS_CATCH      0x31408097
#define NA_SE_EN_KANI_STOP          0x29030098
#define NA_SE_EN_MABOSS_RAGE        0x29036099
#define NA_SE_EN_DOWN_IMPACT        0x2940D09A
#define NA_SE_EN_MARBLE_BEAM        0x3103109B

#define NA_SE_PAUSE_ON              0x4900F000
#define NA_SE_PAUSE_OFF             0x4900F001 // Unreferenced. Seems to be identical to NA_SE_PAUSE_ON
#define NA_SE_CURSOR                0x49000002
#define NA_SE_DECIDE                0x49000003
#define NA_SE_TWIN_LASER_GET        0x49002004
#define NA_SE_BOMB_GET              0x49002005 // Collect bomb. Seems to be identical to NA_SE_BOMB_GUAGE_UP
#define NA_SE_BOMB_GAUGE_UP         0x49002006 // Collect bomb. Seems to be identical to NA_SE_BOMB_GET
#define NA_SE_COUNT_UP              0x49004007
#define NA_SE_READY                 0x49000008
#define NA_SE_GO                    0x49000009
#define NA_SE_ERROR                 0x4900100A
#define NA_SE_DIR_WARNING           0x4100000B // Unreferenced.
#define NA_SE_ITEM_APPEAR           0x4900000C
#define NA_SE_SHIELD_RING_M         0x4900200D
#define NA_SE_SHIELD_RING           0x4900200E
#define NA_SE_CHECKPOINT            0x4900400F
#define NA_SE_SHIELD_WARNING0       0x49008010 // Low health hit alarm
#define NA_SE_SHIELD_WARNING1       0x49008011 // Critical health hit alarm
#define NA_SE_TEAM_SHIELD_UP        0x41007012
#define NA_SE_GOLD_RING             0x49003013
#define NA_SE_DEMO_SIREN            0x49000014
#define NA_SE_SHIELD_UPGRADE        0x49008015
#define NA_SE_GOOD_LUCK             0x49002016
#define NA_SE_MESSAGE_MOVE          0x49000017 // Used for text in training mode
#define NA_SE_COMMU_REQUEST         0x49002018 // C> call alert
#define NA_SE_MAP_WINDOW_OPEN       0x49000019 // Also reticles on
#define NA_SE_MAP_WINDOW_CLOSE      0x4900101A // Also reticles off
#define NA_SE_MAR_LOCKON            0x4900001B
#define NA_SE_MISSILE_ALARM         0x4900001C
#define NA_SE_CANCEL                0x4900101D
#define NA_SE_COMPUTER_NOISE        0x4100001E // Used in mission briefing
#define NA_SE_MAP_MOVE_STOP         0x4900001F
#define NA_SE_ARWING_DECIDE         0x49000020 // Used in main menu
#define NA_SE_ARWING_CANCEL         0x49000021 // Used in main menu
#define NA_SE_ARWING_CURSOR         0x49000022 // Used in main menu
#define NA_SE_OVERHEAT_ALARM        0x4100C023
#define NA_SE_ONE_UP                0x4900C024
#define NA_SE_RING_PASS             0x49008025 // Also used for Corneria mech boss secret 1UP
#define NA_SE_SHIELD_BUZZER         0x49001026
#define NA_SE_LOCK_ON               0x49008027
#define NA_SE_BOSS_GAUGE_OPEN       0x4900C028
#define NA_SE_BANK4_UNK_1           0x40000029 // Unreferenced. Sounds like an item collect jingle
#define NA_SE_COUNTDOWN             0x4900C02A
#define NA_SE_VIEW_SITCHW_ON        0x4000002B // Unreferenced. Related to gFovYMode?
#define NA_SE_VIEW_MOVE_IN          0x4900002C
#define NA_SE_VIEW_MOVE_OUT         0x4900002D
#define NA_SE_SEARCHLIGHT_MISS      0x4900402E
#define NA_SE_RING_MISS             0x4900402F 
#define NA_SE_GET_EMBLEM            0x49008030
#define NA_SE_MISSION_ACCOMPLISHED  0x49008031
#define NA_SE_VO_PEPPER_CONSENT     0x49000032 // This is ONE steep bill, but it's worth it.
#define NA_SE_VO_PEPPER_SURPRISE    0x49000033 // WHAT?!
#define NA_SE_MISSION_COMPLETE      0x49008034
#define NA_SE_BANL4_UNK_2           0x40000035 // Unreferenced. Hard to make out what it is
#define NA_SE_TIME_OVER             0x4900D036

#endif


