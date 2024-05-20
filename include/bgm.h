#ifndef BGM_H
#define BGM_H

#include "sys.h"

void Audio_SetBgmParam(s8 bgmParam);
void Audio_PlaySequence(u8 seqPlayId, u16 seqId, u8 fadeinTime, u8 bgmParam);
void Audio_PlayFanfare(u16 seqId, u8 bgmVolume, u8 bgmFadeoutTime, u8 bgmFadeinTime);
void Audio_PlayDeathSequence(void);
void Audio_PlaySoundTest(u8 enable);
void Audio_PlaySequenceDistorted(u8 seqPlayId, u16 seqId, u16 distortion, u8 fadeinTime, u8 unused);
void Audio_PlaySoundTestTrack(u8 trackNumber);
void Audio_PlayBgm(u16 seqId);

#define AUDIO_PLAY_BGM(seqId) Audio_PlaySequence(SEQ_PLAYER_BGM, (seqId), 0, -1)

typedef enum BgmSeqIds {
    /*  0 */ SEQ_ID_SFX,
    /*  1 */ SEQ_ID_VOICE,
    /*  2 */ SEQ_ID_CORNERIA,
    /*  3 */ SEQ_ID_METEO,
    /*  4 */ SEQ_ID_TITANIA,
    /*  5 */ SEQ_ID_SECTOR_X,
    /*  6 */ SEQ_ID_ZONESS,
    /*  7 */ SEQ_ID_AREA_6,
    /*  8 */ SEQ_ID_VENOM_1,
    /*  9 */ SEQ_ID_SECTOR_Y,
    /* 10 */ SEQ_ID_FORTUNA,
    /* 11 */ SEQ_ID_SOLAR,
    /* 12 */ SEQ_ID_BOLSE,
    /* 13 */ SEQ_ID_KATINA,
    /* 14 */ SEQ_ID_AQUAS,
    /* 15 */ SEQ_ID_SECTOR_Z,
    /* 16 */ SEQ_ID_MACBETH,
    /* 17 */ SEQ_ID_ANDROSS,
    /* 18 */ SEQ_ID_BOSS_CO_1,
    /* 19 */ SEQ_ID_BOSS_ME,
    /* 20 */ SEQ_ID_BOSS_TI,
    /* 21 */ SEQ_ID_BOSS_SX,
    /* 22 */ SEQ_ID_BOSS_ZO,
    /* 23 */ SEQ_ID_BOSS_A6,
    /* 24 */ SEQ_ID_BOSS_VE,
    /* 25 */ SEQ_ID_BOSS_SY,
    /* 26 */ SEQ_ID_UNK_26,
    /* 27 */ SEQ_ID_BOSS_SO,
    /* 28 */ SEQ_ID_BOSS_BO,
    /* 29 */ SEQ_ID_BOSS_KA,
    /* 30 */ SEQ_ID_BOSS_AQ,
    /* 31 */ SEQ_ID_BOSS_SZ,
    /* 32 */ SEQ_ID_BOSS_MA,
    /* 33 */ SEQ_ID_BOSS_ANDROSS,
    /* 34 */ SEQ_ID_TITLE,
    /* 35 */ SEQ_ID_OPENING,
    /* 36 */ SEQ_ID_MENU,
    /* 37 */ SEQ_ID_CO_INTRO,
    /* 38 */ SEQ_ID_GOOD_END,
    /* 39 */ SEQ_ID_DEATH,
    /* 40 */ SEQ_ID_GAME_OVER,
    /* 41 */ SEQ_ID_UNK_41,
    /* 42 */ SEQ_ID_STAFF_ROLL,
    /* 43 */ SEQ_ID_STAR_WOLF,
    /* 44 */ SEQ_ID_INTRO_S,
    /* 45 */ SEQ_ID_INTRO_M,
    /* 46 */ SEQ_ID_VERSUS,
    /* 47 */ SEQ_ID_VS_HURRY,
    /* 48 */ SEQ_ID_BOSS_CO_2,
    /* 49 */ SEQ_ID_BAD_END,
    /* 50 */ SEQ_ID_ME_INTRO,
    /* 51 */ SEQ_ID_INTRO_51,
    /* 52 */ SEQ_ID_UNK_52,
    /* 53 */ SEQ_ID_UNK_53,
    /* 54 */ SEQ_ID_KATT,
    /* 55 */ SEQ_ID_BILL,
    /* 56 */ SEQ_ID_VS_MENU,
    /* 57 */ SEQ_ID_UNK_57,
    /* 58 */ SEQ_ID_WARP_ZONE,
    /* 59 */ SEQ_ID_UNK_59,
    /* 60 */ SEQ_ID_WORLD_MAP,
    /* 61 */ SEQ_ID_AND_BRAIN,
    /* 62 */ SEQ_ID_TO_ANDROSS,
    /* 63 */ SEQ_ID_TRAINING,
    /* 64 */ SEQ_ID_VE_CLEAR,
    /* 65 */ SEQ_ID_BOSS_RESUME,
    /* 66 */ SEQ_ID_MAX,
    /* -1 */ SEQ_ID_NONE = 0xFFFF,
} BgmSeqIds;

#define SEQ_FLAG 0x8000

#define NA_BGM_SE               (SEQ_ID_SFX)
#define NA_BGM_VO               (SEQ_ID_VOICE)
#define NA_BGM_STAGE_CO         (SEQ_ID_CORNERIA | SEQ_FLAG)
#define NA_BGM_STAGE_ME         (SEQ_ID_METEO | SEQ_FLAG)
#define NA_BGM_STAGE_TI         (SEQ_ID_TITANIA | SEQ_FLAG)
#define NA_BGM_STAGE_SX         (SEQ_ID_SECTOR_X | SEQ_FLAG)
#define NA_BGM_STAGE_ZO         (SEQ_ID_ZONESS | SEQ_FLAG)
#define NA_BGM_STAGE_A6         (SEQ_ID_AREA_6 | SEQ_FLAG)
#define NA_BGM_STAGE_SB         (SEQ_ID_AREA_6 | SEQ_FLAG)
#define NA_BGM_STAGE_VE1        (SEQ_ID_VENOM_1 | SEQ_FLAG)
#define NA_BGM_STAGE_SY         (SEQ_ID_SECTOR_Y | SEQ_FLAG)
#define NA_BGM_STAGE_FO         (SEQ_ID_FORTUNA | SEQ_FLAG)
#define NA_BGM_STAGE_SO         (SEQ_ID_SOLAR | SEQ_FLAG)
#define NA_BGM_STAGE_BO         (SEQ_ID_BOLSE | SEQ_FLAG)
#define NA_BGM_STAGE_KA         (SEQ_ID_KATINA | SEQ_FLAG)
#define NA_BGM_STAGE_AQ         (SEQ_ID_AQUAS)
#define NA_BGM_STAGE_SZ         (SEQ_ID_SECTOR_Z | SEQ_FLAG)
#define NA_BGM_STAGE_MA         (SEQ_ID_MACBETH | SEQ_FLAG)
#define NA_BGM_STAGE_ANDROSS    (SEQ_ID_ANDROSS | SEQ_FLAG)
#define NA_BGM_BOSS_CO          (SEQ_ID_BOSS_CO_1 | SEQ_FLAG)
#define NA_BGM_BOSS_ME          (SEQ_ID_BOSS_ME | SEQ_FLAG)
#define NA_BGM_BOSS_TI          (SEQ_ID_BOSS_TI | SEQ_FLAG)
#define NA_BGM_BOSS_SX          (SEQ_ID_BOSS_SX | SEQ_FLAG)
#define NA_BGM_BOSS_ZO          (SEQ_ID_BOSS_ZO | SEQ_FLAG)
#define NA_BGM_BOSS_A6          (SEQ_ID_BOSS_A6 | SEQ_FLAG)
#define NA_BGM_BOSS_SB          (SEQ_ID_BOSS_A6 | SEQ_FLAG)
#define NA_BGM_BOSS_VE          (SEQ_ID_BOSS_VE | SEQ_FLAG)
#define NA_BGM_BOSS_SY          (SEQ_ID_BOSS_SY | SEQ_FLAG)
#define NA_BGM_BOSS_FO          (SEQ_ID_UNK_26 | SEQ_FLAG)
#define NA_BGM_BOSS_SO          (SEQ_ID_BOSS_SO | SEQ_FLAG)
#define NA_BGM_BOSS_BO          (SEQ_ID_BOSS_BO | SEQ_FLAG)
#define NA_BGM_BOSS_KA          (SEQ_ID_BOSS_KA | SEQ_FLAG)
#define NA_BGM_BOSS_AQ          (SEQ_ID_BOSS_AQ | SEQ_FLAG)
#define NA_BGM_BOSS_SZ          (SEQ_ID_BOSS_SZ | SEQ_FLAG)
#define NA_BGM_BOSS_MA          (SEQ_ID_BOSS_MA | SEQ_FLAG)
#define NA_BGM_BOSS_ANDROSS     (SEQ_ID_BOSS_ANDROSS | SEQ_FLAG)
#define NA_BGM_TITLE            (SEQ_ID_TITLE)
#define NA_BGM_OPENING          (SEQ_ID_OPENING)
#define NA_BGM_SELECT           (SEQ_ID_MENU)
#define NA_BGM_RANKING          (SEQ_ID_MENU)
#define NA_BGM_START_DEMO       (SEQ_ID_CO_INTRO)
#define NA_BGM_COURSE_CLEAR     (SEQ_ID_GOOD_END)
#define NA_BGM_PLAYER_DOWN      (SEQ_ID_DEATH)
#define NA_BGM_GAME_OVER        (SEQ_ID_GAME_OVER)
#define NA_BGM_END_DEMO         (SEQ_ID_UNK_41)
#define NA_BGM_STAFF_ROLL       (SEQ_ID_STAFF_ROLL)
#define NA_BGM_STARWOLF         (SEQ_ID_STAR_WOLF | SEQ_FLAG)
#define NA_BGM_START_DEMO_S     (SEQ_ID_INTRO_S)
#define NA_BGM_START_DEMO_M     (SEQ_ID_INTRO_M)
#define NA_BGM_VOLUME_TEST      (SEQ_ID_VERSUS)
#define NA_BGM_BATTLE           (SEQ_ID_VERSUS | SEQ_FLAG)
#define NA_BGM_VS_00            (SEQ_ID_VERSUS | SEQ_FLAG)
#define NA_BGM_VS_01            (SEQ_ID_VERSUS | SEQ_FLAG)
#define NA_BGM_VS_02            (SEQ_ID_VERSUS | SEQ_FLAG)
#define NA_BGM_BATTLE_LAST      (SEQ_ID_VS_HURRY | SEQ_FLAG)
#define NA_BGM_BOSS_A_CARRIER   (SEQ_ID_BOSS_CO_2 | SEQ_FLAG)
#define NA_BGM_COURSE_FAILURE   (SEQ_ID_BAD_END)
#define NA_BGM_ME_START_DEMO    (SEQ_ID_ME_INTRO)
#define NA_BGM_FO_START_DEMO    (SEQ_ID_INTRO_51)
#define NA_BGM_A6_START_DEMO    (SEQ_ID_INTRO_51)
#define NA_BGM_BO_START_DEMO    (SEQ_ID_INTRO_51)
#define NA_BGM_SO_START_DEMO    (SEQ_ID_INTRO_51)
#define NA_BGM_KA_START_DEMO    (SEQ_ID_INTRO_51)
#define NA_BGM_SZ_START_DEMO    (SEQ_ID_INTRO_51)
#define NA_BGM_AQ_START_DEMO    (SEQ_ID_UNK_52)
#define NA_BGM_VE_START_DEMO    (SEQ_ID_UNK_53)
#define NA_BGM_KATT             (SEQ_ID_KATT)
#define NA_BGM_BILL             (SEQ_ID_BILL)
#define NA_BGM_VS_SELECT        (SEQ_ID_VS_MENU)
#define NA_BGM_VS_RESULT        (SEQ_ID_UNK_57)
#define NA_BGM_STAGE_WZ         (SEQ_ID_WARP_ZONE | SEQ_FLAG)
#define NA_BGM_STAGE_AT         (SEQ_ID_WARP_ZONE | SEQ_FLAG)
#define NA_BGM_STAGE_SS         (SEQ_ID_WARP_ZONE | SEQ_FLAG)
#define NA_BGM_STAGE_BM3        (SEQ_ID_UNK_59 | SEQ_FLAG)
#define NA_BGM_MAP              (SEQ_ID_WORLD_MAP)
#define NA_BGM_ANDROSS_BRAIN    (SEQ_ID_AND_BRAIN | SEQ_FLAG)
#define NA_BGM_DASH_INTO_BASE   (SEQ_ID_TO_ANDROSS | SEQ_FLAG)
#define NA_BGM_TRAINING         (SEQ_ID_TRAINING | SEQ_FLAG)
#define NA_BGM_ALL_CLEAR        (SEQ_ID_VE_CLEAR | SEQ_FLAG)
#define NA_BGM_REAL_BOSS        (SEQ_ID_BOSS_RESUME | SEQ_FLAG)

#endif
