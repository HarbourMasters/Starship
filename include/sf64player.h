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
    /* 9 */ DRAW_MAX,
} DrawMode;

typedef enum LevelMode {
    /* 0 */ LEVELMODE_ON_RAILS,
    /* 1 */ LEVELMODE_ALL_RANGE,
    /* 2 */ LEVELMODE_UNK_2,
    /* 3 */ LEVELMODE_MAX,
} LevelMode;

typedef enum PlayerState1C8 {
    /*  0 */ PLAYERSTATE_1C8_STANDBY,
    /*  1 */ PLAYERSTATE_1C8_INIT,
    /*  2 */ PLAYERSTATE_1C8_LEVEL_INTRO,
    /*  3 */ PLAYERSTATE_1C8_ACTIVE,
    /*  4 */ PLAYERSTATE_1C8_DOWN,
    /*  5 */ PLAYERSTATE_1C8_U_TURN,
    /*  6 */ PLAYERSTATE_1C8_NEXT,
    /*  7 */ PLAYERSTATE_1C8_LEVEL_COMPLETE,
    /*  8 */ PLAYERSTATE_1C8_ENTER_WARP_ZONE,
    /*  9 */ PLAYERSTATE_1C8_START_360,
    /* 10 */ PLAYERSTATE_1C8_GFOX_REPAIR,
    /* 11 */ PLAYERSTATE_1C8_ANDROSS_MOUTH,
    /* 12 */ PLAYERSTATE_1C8_12,
    /* 13 */ PLAYERSTATE_1C8_VS_STANDBY,
    /* 14 */ PLAYERSTATE_1C8_MAX,
} PlayerState1C8;

typedef enum PlayerShotStatus {
    /* 0 */ SHOT_FREE,
    /* 1 */ SHOT_ACTIVE,
    /* 2 */ SHOT_HITMARK,
} PlayerShotStatus;

typedef enum PlayerShotId {
    /* 0 */ PLAYERSHOT_SINGLE_LASER, // single laser?
    /* 1 */ PLAYERSHOT_TWIN_LASER, // twin laser?
    /* 2 */ PLAYERSHOT_2,
    /* 3 */ PLAYERSHOT_BOMB, // bomb?
    /* 4 */ PLAYERSHOT_LOCK_SEARCH,
    /* 5 */ PLAYERSHOT_TANK, // landmaster shot
    /* 6 */ PLAYERSHOT_ON_FOOT, // on-foot shot
    /* 7 */ PLAYERSHOT_7, // unused? related to on-foot shot somehow
    /* 8 */ PLAYERSHOT_LOCK_ON, // charge shot
    /* 9 */ PLAYERSHOT_GFOX_LASER,
} PlayerShotId;

#define NPC_SHOT_ID 100
#define CS_SHOT_ID 100
#define DMG_SRC_2 2
#define DMG_SRC_100 100

typedef enum LaserStrength {
    /* 0 */ LASERS_SINGLE,
    /* 1 */ LASERS_TWIN,
    /* 2 */ LASERS_HYPER,
    /* 3 */ LASERS_UNK_3,
    /* 4 */ LASERS_MAX,
} LaserStrength;

typedef struct PlayerShot {
    /* 0x00 */ Object obj;
    /* 0x1C */ s32 index;
    /* 0x20 */ Vec3f vel;
    /* 0x2C */ Vec3f vec_2C;
    /* 0x38 */ f32 sfxSource[3];
    /* 0x44 */ f32 scale;
    /* 0x48 */ f32 unk_48;
    /* 0x4C */ f32 unk_4C;
    /* 0x50 */ f32 unk_50;
    /* 0x54 */ f32 unk_54;
    /* 0x58 */ s32 unk_58;
    /* 0x5C */ s32 unk_5C;
    /* 0x60 */ s32 unk_60;
    /* 0x64 */ s32 timer;
    /* 0x68 */ s32 sourceId;
    /* 0x6C */ u8 bonus;
} PlayerShot; // size = 0x70

typedef struct WingInfo {
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
    /* 0x2C */ u8 modelId;
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ f32 unk_34;
    /* 0x38 */ f32 unk_38;
} WingInfo; // size = 0x3C

typedef struct PlayerSfx {
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
    /* 0x034 */ f32 camRoll; 
    /* 0x038 */ char pad38[8];
    /* 0x040 */ CameraPoint cam;
    /* 0x058 */ f32 camYaw;
    /* 0x05C */ f32 camPitch;
    /* 0x05C */ f32 xRock;
    /* 0x064 */ Vec3f groundPos; // position on ground directly below player
    /* 0x070 */ f32 groundRotY; // y rotation of actor under player when acting as ground
    /* 0x074 */ Vec3f pos; // pos.z is position along path. see trueZpos for the actual z position
    /* 0x080 */ f32 yBob;
    /* 0x084 */ f32 xShake;
    /* 0x088 */ f32 bobPhase;
    /* 0x08C */ f32 camDist;
    /* 0x090 */ Vec3f basePos; // position at start of update
    /* 0x09C */ f32 pathWidth;
    /* 0x0A0 */ f32 pathHeight;
    /* 0x0A4 */ f32 pathFloor;
    /* 0x0A8 */ f32 unk_0A8; // set to 3000.0f, not used. May have been z-extent of path?
    /* 0x0AC */ f32 xPath;
    /* 0x0B0 */ f32 yPath;
    /* 0x0B4 */ f32 pathStep;
    /* 0x0B8 */ f32 xPathTarget;
    /* 0x0BC */ f32 yPathTarget;
    /* 0x0C0 */ Vec3f vel;
    /* 0x0CC */ f32 warpCamSpeed;
    /* 0x0D0 */ f32 baseSpeed;
    /* 0x0D4 */ f32 gravity;
    /* 0x0D8 */ Vec3f knockback;
    /* 0x0E4 */ Vec3f rot;
    /* 0x0F0 */ f32 rockAngle;
    /* 0x0F4 */ f32 rockPhase;
    /* 0x0F8 */ f32 bankAngle;
    /* 0x0FC */ f32 xRot_0FC;
    /* 0x100 */ f32 zRot_0FC;
    /* 0x104 */ Vec3f rot_104;
    /* 0x110 */ f32 boostSpeed;
    /* 0x114 */ f32 yRot_114;
    /* 0x118 */ f32 pathChangeYaw;
    /* 0x11C */ f32 yRotVel_11C;
    /* 0x120 */ f32 xRot_120;
    /* 0x124 */ f32 pathChangePitch;
    /* 0x128 */ char pad128[4];
    /* 0x12C */ f32 zRotBank;
    /* 0x130 */ f32 zRotBarrelRoll;
    /* 0x134 */ f32 damageShake;
    /* 0x138 */ f32 trueZpos; // the actual position of the arwing. pos.z is its z position along the path
    /* 0x13C */ char pad13C[4];
    /* 0x140 */ f32 zPathVel;
    /* 0x144 */ f32 zPath;
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
    /* 0x198 */ s32 savedAlternateView;
    /* 0x19C */ s32 unk_19C;
    /* 0x1A0 */ s32 unk_1A0;
    /* 0x1A4 */ s32 unk_1A4;
    /* 0x1A8 */ char pad1A8[8];
    /* 0x1B0 */ s32 turretState;
    /* 0x1B4 */ s32 turretActor;
    /* 0x1B8 */ char pad1B8[4];
    /* 0x1BC */ s32 turretRecoil;
    /* 0x1C0 */ s32 turretLockOnCount;
    /* 0x1C4 */ s32 num;
    /* 0x1C8 */ PlayerState1C8 state_1C8;
    /* 0x1CC */ PlayerForm form;
    /* 0x1D0 */ s32 csState;
    /* 0x1D4 */ bool grounded;
    /* 0x1D8 */ s32 meTargetIndex;
    /* 0x1DC */ s32 barrelRoll;
    /* 0x1E0 */ s32 barrelInputTimerL;
    /* 0x1E4 */ s32 barrelInputTimerR;
    /* 0x1E8 */ s32 timer_1E8;
    /* 0x1EC */ s32 rollRate;
    /* 0x1F0 */ s32 baseRollRate;
    /* 0x1F4 */ s32 hitTimer;
    /* 0x1F8 */ s32 csTimer;
    /* 0x1FC */ s32 csEventTimer;
    /* 0x200 */ s32 unk_200;
    /* 0x204 */ s32 unk_204;
    /* 0x208 */ s32 unk_208;
    /* 0x20C */ s32 unk_20C; 
    /* 0x210 */ s32 pathChangeTimer;
    /* 0x214 */ s32 timer_214;
    /* 0x218 */ s32 timer_218;
    /* 0x21C */ s32 unk_21C;
    /* 0x220 */ s32 radioDamageTimer;
    /* 0x224 */ s32 timer_224;
    /* 0x228 */ s32 flags_228;
    /* 0x22C */ s32 whooshTimer;
    /* 0x230 */ s32 unk_230;
    /* 0x234 */ s32 unk_234;
    /* 0x238 */ s32 alternateView;
    /* 0x23C */ s32 shadowing;
    /* 0x240 */ s32 unk_240;
    /* 0x244 */ s32 shotTimer;
    /* 0x248 */ f32 unk_248;
    /* 0x24C */ f32 unk_24C;
    /* 0x250 */ f32 unk_250; // checked for by event actors, but unused?
    /* 0x250 */ char pad254[4];
    /* 0x258 */ f32 meteoWarpSpinSpeed;
    /* 0x25C */ f32 contrailScale;
    /* 0x260 */ char pad260[4];
    /* 0x264 */ s32 shields;
    /* 0x268 */ s32 damage;
    /* 0x26C */ s32 heal;
    /* 0x270 */ s32 unk_270; // checked for by event actors, but unused?
    /* 0x274 */ char pad274[4];
    /* 0x278 */ s32 timer_278;
    /* 0x27C */ s32 meteoWarpTimer;
    /* 0x280 */ s32 barrelRollAlpha;
    /* 0x284 */ s32 unk_284;
    /* 0x288 */ s32 attacker;
    /* 0x28C */ char pad28C[0x28];
    /* 0x2B4 */ bool boostCooldown;
    /* 0x2B8 */ bool boostActive;
    /* 0x2BC */ f32 boostMeter;
    /* 0x2C0 */ f32 unk_2C0; // has to do with starting right tank jet
    /* 0x2C4 */ s32 unk_2C4; // counts up during some effects. never used
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
    /* 0x4D8 */ f32 aerobaticPitch;
    /* 0x4DC */ s32 somersault;
} Player; // size = 0x4E0


#endif
