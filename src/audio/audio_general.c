#include "sys.h"
#include "sf64audio_provisional.h"
#include "sf64context.h"
#include "audiothread_cmd.h"
#include "audioseq_cmd.h"

void Audio_SetModulationAndPlaySfx(f32* sfxSource, u32 sfxId, f32 freqMod);
s32 Audio_GetCurrentVoice(void);
void Audio_PlaySequence(u8, u16, u8, u8);
void Audio_PlayFanfare(u16, u8, u8, u8);
void Audio_PlaySequenceDistorted(u8, u16, u16, u8, u8);

void Audio_RestartSeqPlayers(void);
void Audio_PlayMapMenuSfx(u8);
void Audio_StartReset(u8);

static const char devstr1[] = "preload start (%d): ";
static const char devstr2[] = "%d ";
static const char devstr3[] = "\n";
static const char devstr4[] = "***** START SEQ : %d *****\n";
static const char devstr5[] = "spec change finished !!!\n";
static const char devstr6[] = "interface wait spec change finished !!!\n";
static const char devstr7[] = "********** SE Interface Buffer SE Stop %08X **********\n";
static const char devstr8[] = "MedlayStart : \n";
static const char devstr9[] = "MedlayStart : \n";
static const char devstr10[] = "MedlayStart(TuneUp) : \n";
static const char devstr11[] = "MedlayStart(cross) : \n";
static const char devstr12[] = "MedlayEnd : \n";
static const char devstr13[] = "MedlayWait : %d\n";
static const char devstr14[] = "ControlSePicth : %f %f %f \n";
static const char devstr15[] = "ChangeWarningSePara : %d %d\n";
static const char devstr16[] = "set Grp 0 port %02x \n";
static const char devstr17[] = "main BGM start %08X\n";
static const char devstr18[] = "<<<<< PlayCrossMixBgm pass !!! >>>>>\n";
static const char devstr19[] = "SetVolumeBallnce %d %d\n";
static const char devstr20[] = "START HANDLE : %d (old:%d)\n";
static const char devstr21[] = "All Sound Fade Out time:%d\n";

SfxRequest sSfxRequests[256];
SfxBankEntry sSfxBanks[5][20];
u8 sSfxBankListEnd[5];
u8 sSfxBankFreeListStart[5];
u8 sSfxBankUnused[5];
ActiveSfx sActiveSfx[5][8];
u8 sCurSfxPlayerChannelIndex;
u8 sSfxBankMuted[5];
Modulation sSfxVolumeMods[5];
f32 sAudioAnalyzerData[256];
f32 sAnalyzerBuffer1[256];
f32 sAnalyzerBuffer2[384];
f32 sNewFreqAmplitudes[32];
u8 sFreqAnalyzerBars[32];
SeqRequest sSeqRequests[SEQ_PLAYER_MAX][5];
u8 sNumSeqRequests[SEQ_PLAYER_MAX];
s32 sAudioSeqCmds[256];
ActiveSequence sActiveSequences[SEQ_PLAYER_MAX];
u16 sDelayedSeqCmdFlags;
DelayedSeqCmd sDelayedSeqCmds[16];
SfxChannelState sSfxChannelState[16];
PlayerNoiseModulation sPlayerNoise[4];
f32 sBombFreqMod[4];
u8 sBombType[4];
u8 sBombState[4];
s32 sBombStartFrame[4];

u8 sChannelsPerBank[5][5] = {
    { 3, 2, 2, 2, 2 }, { 3, 1, 2, 2, 2 }, { 3, 2, 2, 2, 3 }, { 6, 0, 2, 0, 4 }, { 0, 0, 0, 0, 0 },
};
u8 sUsedChannelsPerBank[5][5] = {
    { 3, 2, 1, 2, 3 }, { 3, 2, 1, 1, 2 }, { 3, 2, 1, 1, 3 }, { 2, 0, 1, 0, 1 }, { 0, 0, 0, 0, 0 },
};
u8 sSfxRequestWriteIndex = 0;
u8 sSfxRequestReadIndex = 0;
u8 sSfxChannelLayout = SFXCHAN_0;
u16 sChannelMuteFlags = 0;
f32 gDefaultSfxSource[3] = { 0.0f, 0.0f, 0.0f };
f32 gDefaultMod = 1.0f;
s32 D_800C5D38 = 0; // unused. perhaps a default pan?
s8 gDefaultReverb = 0;
s32 sAudioFrameCounter = 0;
u8 sSeqCmdWritePos = 0;
u8 sSeqCmdReadPos = 0;
u8 sStartSeqDisabled = 0;
u8 sSoundModeList[4] = { SOUNDMODE_STEREO, SOUNDMODE_HEADSET, SOUNDMODE_SURROUND, SOUNDMODE_MONO };
u8 sAudioSpecId = AUDIOSPEC_CO;
u8 sAudioResetStatus = AUDIORESET_READY;
s32 D_800C5D5C = 0; // unused. file split?
s8 sEnvReverb = 0;
s8 sAudioSpecReverb = 0;
u8 sVolumeSettings[3] = { 99, 99, 99 };
u8 sAudioSpecInstrumentSets[29][7] = {
    { 0, 3, 4, 80, 12, 21, 255 },    { 17, 18, 15, 96, 20, 22, 255 }, { 0, 3, 5, 80, 16, 255, 0 },
    { 17, 18, 15, 96, 20, 22, 255 }, { 0, 3, 4, 80, 12, 21, 255 },    { 17, 18, 15, 96, 20, 22, 255 },
    { 0, 3, 4, 80, 12, 21, 255 },    { 17, 18, 15, 96, 20, 22, 255 }, { 0, 3, 4, 80, 12, 21, 255 },
    { 0, 3, 4, 80, 12, 21, 255 },    { 17, 18, 15, 96, 20, 22, 255 }, { 0, 3, 4, 80, 12, 21, 255 },
    { 17, 18, 95, 96, 41, 255, 0 },  { 17, 18, 15, 96, 20, 22, 255 }, { 0, 3, 5, 80, 16, 255, 0 },
    { 0, 3, 4, 80, 12, 21, 255 },    { 0, 3, 4, 80, 12, 21, 255 },    { 17, 18, 15, 96, 20, 22, 255 },
    { 0, 3, 4, 80, 12, 21, 255 },    { 0, 3, 4, 80, 12, 21, 255 },    { 0, 3, 4, 80, 12, 21, 255 },
    { 255, 0, 0, 0, 0, 0, 0 },       { 255, 0, 0, 0, 0, 0, 0 },       { 255, 0, 0, 0, 0, 0, 0 },
    { 255, 0, 0, 0, 0, 0, 0 },       { 255, 0, 0, 0, 0, 0, 0 },       { 255, 0, 0, 0, 0, 0, 0 },
    { 255, 0, 0, 0, 0, 0, 0 },       { 0, 3, 4, 80, 12, 21, 255 },
};
s8 sAudioSpecReverbAdd[29] = {
    10, 0, 25, 0, 25, 0, 10, 0, 10, 35, 0, 10, 40, 0, 25, 64, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
u32 sPlayerNoiseTimes[5] = { 20, 16, 10, 10, 20 };
s32 D_800C5E6C = 0; // unused. file split?
u8 D_800C5E70 = 0;
f32 sSfxFreqMod = 1.0f;
f32 sSfxVolMod = 1.0f; // never modified
u8 sPlaylistIndex = 255;
s32 sPlaylistTimer = 0;
u8 sPlaylistCmdIndex = 0;
u32 sEventSfx[] = {
    NA_SE_OB_SLIDE_OPEN,        NA_SE_OB_SLIDE_CLOSE,
    NA_SE_OB_STEELFRAME,        NA_SE_OB_HEAVY_BOUND,
    NA_SE_ITEM_APPEAR,          NA_SE_OB_BLOCK_APPEAR,
    NA_SE_OB_ROCKWALL_UP,       NA_SE_EN_UNIT_GATHERING,
    NA_SE_EN_MOTOR_STOP,        NA_SE_EN_MS_DASH,
    NA_SE_OB_ROCK_CRASH,        NA_SE_OB_ROCK_EYE_OPEN,
    NA_SE_OB_SHIP_FALLDOWN,     NA_SE_OB_ROCK_BOUND,
    NA_SE_OB_SPEAR_PILLAR,      NA_SE_OB_PILLAR_ROLL,
    NA_SE_SEARCHLIGHT_MISS,     NA_SE_OB_ROUTEGATE_OPEN_Q,
    NA_SE_OB_ROUTEGATE_CLOSE_Q, NA_SE_OB_ROUTEGATE_OPEN_S,
    NA_SE_OB_ROUTEGATE_CLOSE_S, NA_SE_OB_LIFT,
    NA_SE_OB_PLATE_ROLL,
};
SoundTestTrack sSoundTestTracks[] = {
    /*  0 */ { NA_BGM_OPENING, AUDIOSPEC_22 | (SFXCHAN_0 << 8), -1 },
    /*  1 */ { NA_BGM_TITLE, AUDIOSPEC_23 | (SFXCHAN_0 << 8), -1 },
    /*  2 */ { NA_BGM_SELECT, AUDIOSPEC_23 | (SFXCHAN_0 << 8), -1 },
    /*  3 */ { NA_BGM_MAP, AUDIOSPEC_24 | (SFXCHAN_1 << 8), -1 },
    /*  4 */ { NA_BGM_START_DEMO, AUDIOSPEC_CO | (SFXCHAN_0 << 8), -1 },
    /*  5 */ { NA_BGM_START_DEMO_S, AUDIOSPEC_ME | (SFXCHAN_0 << 8), -1 },
    /*  6 */ { NA_BGM_START_DEMO_M, AUDIOSPEC_ME | (SFXCHAN_0 << 8), -1 },
    /*  7 */ { NA_BGM_ME_START_DEMO, AUDIOSPEC_ME | (SFXCHAN_0 << 8), -1 },
    /*  8 */ { NA_BGM_FO_START_DEMO, AUDIOSPEC_FO | (SFXCHAN_0 << 8), -1 },
    /*  9 */ { NA_BGM_STAGE_CO, AUDIOSPEC_CO | (SFXCHAN_0 << 8), -1 },
    /* 10 */ { NA_BGM_STAGE_ME, AUDIOSPEC_ME | (SFXCHAN_0 << 8), -1 },
    /* 11 */ { NA_BGM_STAGE_TI, AUDIOSPEC_TI | (SFXCHAN_0 << 8), -1 },
    /* 12 */ { NA_BGM_STAGE_SX, AUDIOSPEC_SX | (SFXCHAN_0 << 8), -1 },
    /* 13 */ { NA_BGM_STAGE_ZO, AUDIOSPEC_ZO | (SFXCHAN_0 << 8), -1 },
    /* 14 */ { NA_BGM_STAGE_A6, AUDIOSPEC_A6 | (SFXCHAN_0 << 8), -1 },
    /* 15 */ { NA_BGM_STAGE_VE1, AUDIOSPEC_6 | (SFXCHAN_0 << 8), -1 },
    /* 16 */ { NA_BGM_STAGE_SY, AUDIOSPEC_SY | (SFXCHAN_0 << 8), -1 },
    /* 17 */ { NA_BGM_STAGE_FO, AUDIOSPEC_FO | (SFXCHAN_0 << 8), -1 },
    /* 18 */ { NA_BGM_STAGE_BO, AUDIOSPEC_BO | (SFXCHAN_0 << 8), -1 },
    /* 19 */ { NA_BGM_STAGE_KA, AUDIOSPEC_KA | (SFXCHAN_0 << 8), -1 },
    /* 20 */ { NA_BGM_STAGE_AQ, AUDIOSPEC_AQ | (SFXCHAN_0 << 8), -1 },
    /* 21 */ { NA_BGM_STAGE_WZ, AUDIOSPEC_ME | (SFXCHAN_0 << 8), -1 },
    /* 22 */ { NA_BGM_KATT, AUDIOSPEC_SZ | (SFXCHAN_0 << 8), -1 },
    /* 23 */ { NA_BGM_BILL, AUDIOSPEC_KA | (SFXCHAN_0 << 8), -1 },
    /* 24 */ { NA_BGM_BOSS_CO, AUDIOSPEC_CO | (SFXCHAN_0 << 8), -1 },
    /* 25 */ { NA_BGM_BOSS_ME, AUDIOSPEC_ME | (SFXCHAN_0 << 8), 0 },
    /* 26 */ { NA_BGM_BOSS_ME, AUDIOSPEC_ME | (SFXCHAN_0 << 8), -1 },
    /* 27 */ { NA_BGM_REAL_BOSS, AUDIOSPEC_SY | (SFXCHAN_0 << 8), -1 },
    /* 28 */ { NA_BGM_BOSS_BO, AUDIOSPEC_BO | (SFXCHAN_0 << 8), -1 },
    /* 29 */ { NA_BGM_STARWOLF, AUDIOSPEC_6 | (SFXCHAN_0 << 8), -1 },
    /* 30 */ { NA_BGM_COURSE_CLEAR, AUDIOSPEC_CO | (SFXCHAN_0 << 8), -1 },
    /* 31 */ { NA_BGM_COURSE_FAILURE, AUDIOSPEC_CO | (SFXCHAN_0 << 8), -1 },
    /* 32 */ { NA_BGM_PLAYER_DOWN, AUDIOSPEC_CO | (SFXCHAN_0 << 8), -1 },
    /* 33 */ { NA_BGM_GAME_OVER, AUDIOSPEC_25 | (SFXCHAN_0 << 8), -1 },
    /* 34 */ { NA_BGM_TRAINING, AUDIOSPEC_28 | (SFXCHAN_0 << 8), -1 },
    /* 35 */ { NA_BGM_BATTLE, AUDIOSPEC_16 | (SFXCHAN_3 << 8), -1 },
    /* 36 */ { NA_BGM_BATTLE_LAST, AUDIOSPEC_17 | (SFXCHAN_3 << 8), -1 },
    /* 37 */ { NA_BGM_VS_SELECT, AUDIOSPEC_23 | (SFXCHAN_0 << 8), -1 },
    /* 38 */ { NA_BGM_DASH_INTO_BASE, AUDIOSPEC_6 | (SFXCHAN_0 << 8), 0 },
    /* 39 */ { NA_BGM_STAGE_ANDROSS, AUDIOSPEC_23 | (SFXCHAN_0 << 8), -1 },
    /* 40 */ { NA_BGM_BOSS_ANDROSS, AUDIOSPEC_6 | (SFXCHAN_0 << 8), 0 },
    /* 41 */ { NA_BGM_BOSS_ANDROSS, AUDIOSPEC_6 | (SFXCHAN_0 << 8), -1 },
    /* 42 */ { NA_BGM_ANDROSS_BRAIN, AUDIOSPEC_6 | (SFXCHAN_0 << 8), -1 },
    /* 43 */ { NA_BGM_ALL_CLEAR, AUDIOSPEC_6 | (SFXCHAN_0 << 8), -1 },
    /* 44 */ { NA_BGM_STAFF_ROLL, AUDIOSPEC_27 | (SFXCHAN_0 << 8), -1 },
};

PlaylistCmd sPlaylists[][100] = {
    {
        { 0, 0, NA_BGM_START_DEMO, 0, 255, 1620 },     { 0, 0, NA_BGM_STAGE_CO, 0, 255, 2490 },
        { 1, 0, NA_BGM_STAGE_CO, 50, 255, 50 },        { 0, 0, NA_BGM_BOSS_CO, 0, 255, 1600 },
        { 1, 0, NA_BGM_BOSS_CO, 1, 255, 50 },          { 0, 0, NA_BGM_COURSE_CLEAR, 0, 255, 1091 },
        { 1, 0, NA_BGM_COURSE_CLEAR, 100, 255, 100 },  { 0, 0, NA_BGM_ME_START_DEMO, 0, 255, 838 },
        { 0, 0, NA_BGM_STAGE_ME, 0, 255, 1584 },       { 1, 0, NA_BGM_STAGE_ME, 50, 255, 50 },
        { 0, 0, NA_BGM_BOSS_ME, 0, 0, 1620 },          { 1, 0, NA_BGM_BOSS_ME, 1, 255, 50 },
        { 0, 0, NA_BGM_REAL_BOSS, 0, 255, 1620 },      { 1, 0, NA_BGM_REAL_BOSS, 1, 255, 50 },
        { 0, 0, NA_BGM_COURSE_CLEAR, 0, 255, 1091 },   { 1, 0, NA_BGM_COURSE_CLEAR, 100, 255, 100 },
        { 0, 0, NA_BGM_FO_START_DEMO, 0, 255, 241 },   { 0, 0, NA_BGM_STAGE_FO, 0, 255, 1632 },
        { 1, 0, NA_BGM_STAGE_FO, 100, 255, 100 },      { 0, 0, NA_BGM_STARWOLF, 0, 255, 2120 },
        { 0, 0, NA_BGM_STAGE_FO, 0, 0, 450 },          { 1, 0, NA_BGM_STAGE_FO, 50, 255, 200 },
        { 0, 0, NA_BGM_COURSE_FAILURE, 0, 255, 1604 }, { 1, 0, NA_BGM_COURSE_FAILURE, 100, 255, 100 },
        { 0, 0, NA_BGM_START_DEMO_S, 0, 255, 242 },    { 0, 0, NA_BGM_STAGE_SX, 0, 255, 2291 },
        { 1, 0, NA_BGM_STAGE_SX, 50, 255, 100 },       { 0, 0, NA_BGM_BOSS_SX, 0, 255, 1600 },
        { 1, 0, NA_BGM_BOSS_SX, 1, 255, 50 },          { 2, 0, NA_BGM_BOSS_SX, 0, 255, 1600 },
        { 1, 0, NA_BGM_BOSS_SX, 1, 255, 50 },          { 0, 0, NA_BGM_COURSE_CLEAR, 0, 255, 1091 },
        { 1, 0, NA_BGM_COURSE_CLEAR, 100, 255, 100 },  { 0, 0, NA_BGM_START_DEMO_M, 0, 255, 542 },
        { 0, 0, NA_BGM_STAGE_TI, 0, 255, 1920 },       { 1, 0, NA_BGM_STAGE_TI, 50, 255, 50 },
        { 0, 0, NA_BGM_BOSS_TI, 0, 255, 1600 },        { 1, 0, NA_BGM_BOSS_TI, 1, 255, 50 },
        { 0, 0, NA_BGM_COURSE_CLEAR, 0, 255, 1091 },   { 1, 0, NA_BGM_COURSE_CLEAR, 100, 255, 100 },
        { 0, 0, NA_BGM_BO_START_DEMO, 0, 255, 241 },   { 0, 0, NA_BGM_STAGE_BO, 0, 255, 1177 },
        { 1, 0, NA_BGM_STAGE_BO, 100, 255, 100 },      { 0, 0, NA_BGM_BOSS_BO, 0, 255, 1115 },
        { 1, 0, NA_BGM_BOSS_BO, 50, 255, 50 },         { 0, 0, NA_BGM_STARWOLF, 0, 255, 2120 },
        { 1, 0, NA_BGM_STARWOLF, 1, 255, 50 },         { 0, 0, NA_BGM_PLAYER_DOWN, 0, 255, 150 },
        { 0, 0, NA_BGM_GAME_OVER, 0, 255, 1020 },      { 1, 0, NA_BGM_GAME_OVER, 100, 255, 100 },
        { 255, 0, NA_BGM_STAGE_CO, 50, 255, 50 },
    },
    {
        { 0, 0, NA_BGM_START_DEMO, 0, 255, 1620 },    { 0, 0, NA_BGM_STAGE_CO, 0, 255, 2490 },
        { 1, 0, NA_BGM_STAGE_CO, 50, 255, 50 },       { 0, 0, NA_BGM_BOSS_A_CARRIER, 0, 255, 1620 },
        { 1, 0, NA_BGM_BOSS_A_CARRIER, 1, 255, 50 },  { 0, 0, NA_BGM_COURSE_CLEAR, 0, 255, 1091 },
        { 1, 0, NA_BGM_COURSE_CLEAR, 100, 255, 100 }, { 0, 0, NA_BGM_START_DEMO_S, 0, 255, 242 },
        { 0, 0, NA_BGM_STAGE_SY, 0, 255, 2096 },      { 1, 0, NA_BGM_STAGE_SY, 50, 255, 50 },
        { 0, 0, NA_BGM_BOSS_SY, 0, 2, 1600 },         { 1, 0, NA_BGM_BOSS_SY, 1, 255, 50 },
        { 0, 0, NA_BGM_REAL_BOSS, 0, 255, 1600 },     { 1, 0, NA_BGM_REAL_BOSS, 1, 255, 50 },
        { 0, 0, NA_BGM_COURSE_CLEAR, 0, 255, 1091 },  { 1, 0, NA_BGM_COURSE_CLEAR, 100, 255, 100 },
        { 0, 0, NA_BGM_KA_START_DEMO, 0, 255, 241 },  { 0, 0, NA_BGM_STAGE_KA, 0, 255, 2184 },
        { 1, 0, NA_BGM_STAGE_KA, 1, 255, 100 },       { 0, 0, NA_BGM_BOSS_KA, 0, 1, 1115 },
        { 1, 0, NA_BGM_BOSS_KA, 50, 255, 100 },       { 0, 0, NA_BGM_COURSE_CLEAR, 0, 255, 1091 },
        { 1, 0, NA_BGM_COURSE_CLEAR, 100, 255, 100 }, { 0, 0, NA_BGM_SO_START_DEMO, 0, 255, 250 },
        { 0, 0, NA_BGM_STAGE_SO, 0, 255, 1096 },      { 3, 0, NA_BGM_BILL, 0, 255, 1000 },
        { 1, 0, NA_BGM_STAGE_SO, 50, 255, 50 },       { 0, 0, NA_BGM_BOSS_SO, 0, 255, 1600 },
        { 1, 0, NA_BGM_BOSS_SO, 1, 255, 50 },         { 0, 0, NA_BGM_COURSE_CLEAR, 0, 255, 1091 },
        { 1, 0, NA_BGM_COURSE_CLEAR, 100, 255, 100 }, { 0, 0, NA_BGM_START_DEMO_S, 0, 255, 260 },
        { 0, 0, NA_BGM_STAGE_MA, 0, 255, 1920 },      { 1, 0, NA_BGM_STAGE_MA, 50, 255, 50 },
        { 0, 0, NA_BGM_BOSS_MA, 0, 255, 1600 },       { 1, 0, NA_BGM_BOSS_MA, 1, 255, 50 },
        { 0, 0, NA_BGM_COURSE_CLEAR, 0, 255, 1091 },  { 1, 0, NA_BGM_COURSE_CLEAR, 100, 255, 100 },
        { 0, 0, NA_BGM_BO_START_DEMO, 0, 255, 241 },  { 0, 0, NA_BGM_STAGE_BO, 0, 255, 1177 },
        { 1, 0, NA_BGM_STAGE_BO, 100, 255, 100 },     { 0, 0, NA_BGM_BOSS_BO, 0, 255, 1115 },
        { 1, 0, NA_BGM_BOSS_BO, 50, 255, 50 },        { 0, 0, NA_BGM_STARWOLF, 0, 255, 2120 },
        { 1, 0, NA_BGM_STARWOLF, 1, 255, 50 },        { 0, 0, NA_BGM_COURSE_CLEAR, 0, 255, 1091 },
        { 1, 0, NA_BGM_COURSE_CLEAR, 100, 255, 100 }, { 0, 0, NA_BGM_STAGE_VE1, 0, 255, 1671 },
        { 1, 0, NA_BGM_STAGE_VE1, 50, 255, 50 },      { 0, 0, NA_BGM_BOSS_VE, 0, 255, 1600 },
        { 1, 0, NA_BGM_BOSS_VE, 1, 255, 50 },         { 0, 0, NA_BGM_DASH_INTO_BASE, 0, 0, 176 },
        { 0, 0, NA_BGM_STAGE_ANDROSS, 0, 255, 588 },  { 0, 0, NA_BGM_BOSS_ANDROSS, 0, 0, 2420 },
        { 1, 0, NA_BGM_BOSS_ANDROSS, 10, 255, 50 },   { 0, 0, NA_BGM_BOSS_ANDROSS, 0, 255, 1200 },
        { 1, 0, NA_BGM_BOSS_ANDROSS, 1, 255, 150 },   { 0, 0, NA_BGM_ALL_CLEAR, 0, 255, 1091 },
        { 1, 0, NA_BGM_ALL_CLEAR, 80, 255, 160 },     { 0, 0, NA_BGM_STAFF_ROLL, 0, 255, 9500 },
        { 255, 0, NA_BGM_STAGE_CO, 50, 255, 50 },
    },
    {
        { 0, 0, NA_BGM_START_DEMO, 0, 255, 1620 },    { 0, 0, NA_BGM_STAGE_CO, 0, 255, 2490 },
        { 1, 0, NA_BGM_STAGE_CO, 50, 255, 50 },       { 0, 0, NA_BGM_BOSS_A_CARRIER, 0, 255, 1620 },
        { 1, 0, NA_BGM_BOSS_A_CARRIER, 1, 255, 50 },  { 0, 0, NA_BGM_COURSE_CLEAR, 0, 255, 1091 },
        { 1, 0, NA_BGM_COURSE_CLEAR, 100, 255, 100 }, { 0, 0, NA_BGM_START_DEMO_S, 0, 255, 260 },
        { 0, 0, NA_BGM_STAGE_SY, 0, 255, 2096 },      { 1, 0, NA_BGM_STAGE_SY, 50, 255, 50 },
        { 0, 0, NA_BGM_BOSS_SY, 0, 2, 1590 },         { 1, 0, NA_BGM_BOSS_SY, 1, 255, 50 },
        { 0, 0, NA_BGM_REAL_BOSS, 0, 255, 1600 },     { 1, 0, NA_BGM_REAL_BOSS, 1, 255, 50 },
        { 0, 0, NA_BGM_COURSE_CLEAR, 0, 255, 1091 },  { 1, 0, NA_BGM_COURSE_CLEAR, 100, 255, 100 },
        { 0, 0, NA_BGM_START_DEMO_S, 0, 255, 260 },   { 0, 0, NA_BGM_STAGE_AQ, 0, 255, 2400 },
        { 1, 0, NA_BGM_STAGE_AQ, 150, 255, 200 },     { 0, 0, NA_BGM_BOSS_AQ, 0, 1, 1590 },
        { 1, 0, NA_BGM_BOSS_AQ, 1, 255, 50 },         { 0, 0, NA_BGM_COURSE_CLEAR, 0, 255, 1091 },
        { 1, 0, NA_BGM_COURSE_CLEAR, 100, 255, 100 }, { 0, 0, NA_BGM_START_DEMO_S, 0, 255, 260 },
        { 0, 0, NA_BGM_STAGE_ZO, 0, 255, 1005 },      { 3, 0, NA_BGM_KATT, 0, 255, 1000 },
        { 1, 0, NA_BGM_STAGE_ZO, 50, 255, 100 },      { 0, 0, NA_BGM_BOSS_ZO, 0, 255, 1600 },
        { 1, 0, NA_BGM_BOSS_ZO, 1, 255, 50 },         { 0, 0, NA_BGM_COURSE_CLEAR, 0, 255, 1091 },
        { 1, 0, NA_BGM_COURSE_CLEAR, 100, 255, 100 }, { 0, 0, NA_BGM_SZ_START_DEMO, 0, 255, 241 },
        { 0, 0, NA_BGM_STAGE_SZ, 0, 255, 1632 },      { 1, 0, NA_BGM_STAGE_SZ, 50, 255, 100 },
        { 0, 0, NA_BGM_BOSS_SZ, 0, 1, 1310 },         { 3, 0, NA_BGM_KATT, 0, 255, 500 },
        { 1, 0, NA_BGM_BOSS_SZ, 1, 255, 50 },         { 0, 0, NA_BGM_COURSE_CLEAR, 0, 255, 1091 },
        { 1, 0, NA_BGM_COURSE_CLEAR, 100, 255, 100 }, { 0, 0, NA_BGM_A6_START_DEMO, 0, 255, 241 },
        { 0, 0, NA_BGM_STAGE_A6, 0, 255, 1906 },      { 1, 0, NA_BGM_STAGE_A6, 50, 255, 100 },
        { 0, 0, NA_BGM_BOSS_A6, 0, 1, 1590 },         { 1, 0, NA_BGM_BOSS_A6, 1, 255, 50 },
        { 0, 0, NA_BGM_COURSE_CLEAR, 0, 255, 1091 },  { 1, 0, NA_BGM_COURSE_CLEAR, 100, 255, 100 },
        { 0, 0, NA_BGM_STARWOLF, 0, 255, 2120 },      { 1, 0, NA_BGM_STARWOLF, 30, 255, 150 },
        { 0, 0, NA_BGM_DASH_INTO_BASE, 0, 0, 176 },   { 0, 0, NA_BGM_STAGE_ANDROSS, 0, 255, 588 },
        { 0, 0, NA_BGM_BOSS_ANDROSS, 0, 0, 2392 },    { 1, 0, NA_BGM_BOSS_ANDROSS, 10, 255, 50 },
        { 0, 0, NA_BGM_ANDROSS_BRAIN, 0, 255, 1700 }, { 1, 0, NA_BGM_BOSS_ANDROSS, 10, 255, 250 },
        { 0, 0, NA_BGM_BOSS_A6, 0, 255, 1600 },       { 1, 0, NA_BGM_BOSS_A6, 1, 255, 50 },
        { 0, 0, NA_BGM_ALL_CLEAR, 0, 255, 1091 },     { 1, 0, NA_BGM_ALL_CLEAR, 80, 255, 160 },
        { 0, 0, NA_BGM_STAFF_ROLL, 0, 255, 9250 },    { 255, 0, NA_BGM_STAGE_CO, 50, 255, 50 },
    },
    {
        { 0, 0, NA_BGM_START_DEMO, 0, 255, 1620 },      { 0, 0, NA_BGM_STAGE_CO, 0, 255, 2490 },
        { 1, 0, NA_BGM_STAGE_CO, 50, 255, 50 },         { 0, 0, NA_BGM_BOSS_CO, 0, 255, 1600 },
        { 1, 0, NA_BGM_BOSS_CO, 1, 255, 50 },           { 0, 0, NA_BGM_COURSE_CLEAR, 0, 255, 1091 },
        { 1, 0, NA_BGM_COURSE_CLEAR, 100, 255, 100 },   { 0, 0, NA_BGM_ME_START_DEMO, 0, 255, 838 },
        { 0, 0, NA_BGM_STAGE_ME, 0, 255, 1584 },        { 1, 0, NA_BGM_STAGE_ME, 150, 255, 150 },
        { 0, 0, NA_BGM_STAGE_WZ, 0, 255, 1635 },        { 1, 0, NA_BGM_STAGE_WZ, 150, 255, 150 },
        { 0, 0, NA_BGM_KA_START_DEMO, 0, 255, 241 },    { 0, 0, NA_BGM_STAGE_KA, 0, 255, 2184 },
        { 1, 0, NA_BGM_STAGE_KA, 1, 255, 100 },         { 0, 0, NA_BGM_BOSS_KA, 0, 1, 1115 },
        { 1, 0, NA_BGM_BOSS_KA, 50, 255, 100 },         { 0, 0, NA_BGM_COURSE_FAILURE, 0, 255, 1604 },
        { 1, 0, NA_BGM_COURSE_FAILURE, 100, 255, 100 }, { 0, 0, NA_BGM_START_DEMO_S, 0, 255, 242 },
        { 0, 0, NA_BGM_STAGE_SX, 0, 255, 1291 },        { 3, 0, NA_BGM_BILL, 0, 255, 1000 },
        { 1, 0, NA_BGM_STAGE_SX, 50, 255, 100 },        { 0, 0, NA_BGM_STAGE_WZ, 0, 255, 1635 },
        { 1, 0, NA_BGM_STAGE_WZ, 150, 255, 150 },       { 0, 0, NA_BGM_SZ_START_DEMO, 0, 255, 241 },
        { 0, 0, NA_BGM_STAGE_SZ, 0, 255, 1632 },        { 1, 0, NA_BGM_STAGE_SZ, 50, 255, 100 },
        { 0, 0, NA_BGM_BOSS_SZ, 0, 1, 1115 },           { 1, 0, NA_BGM_BOSS_SZ, 1, 255, 50 },
        { 0, 0, NA_BGM_COURSE_CLEAR, 0, 255, 1091 },    { 1, 0, NA_BGM_COURSE_CLEAR, 100, 255, 100 },
        { 0, 0, NA_BGM_A6_START_DEMO, 0, 255, 241 },    { 0, 0, NA_BGM_STAGE_A6, 0, 255, 1906 },
        { 1, 0, NA_BGM_STAGE_A6, 50, 255, 100 },        { 0, 0, NA_BGM_BOSS_A6, 0, 1, 1590 },
        { 1, 0, NA_BGM_BOSS_A6, 1, 255, 50 },           { 0, 0, NA_BGM_PLAYER_DOWN, 0, 255, 150 },
        { 0, 0, NA_BGM_GAME_OVER, 0, 255, 1020 },       { 1, 0, NA_BGM_GAME_OVER, 100, 255, 100 },
        { 255, 0, NA_BGM_STAGE_CO, 50, 255, 50 },
    },
    {
        { 0, 0, NA_BGM_OPENING, 0, 255, 2926 },
        { 0, 0, NA_BGM_TITLE, 0, 255, 1251 },
        { 1, 0, NA_BGM_TITLE, 200, 255, 200 },
        { 0, 0, NA_BGM_SELECT, 0, 255, 1636 },
        { 1, 0, NA_BGM_SELECT, 200, 255, 200 },
        { 0, 0, NA_BGM_MAP, 0, 255, 1560 },
        { 1, 0, NA_BGM_MAP, 200, 255, 200 },
        { 0, 0, NA_BGM_START_DEMO, 0, 255, 1618 },
        { 0, 0, NA_BGM_START_DEMO_S, 0, 255, 242 },
        { 0, 0, NA_BGM_START_DEMO_M, 0, 255, 582 },
        { 0, 0, NA_BGM_ME_START_DEMO, 0, 255, 868 },
        { 0, 0, NA_BGM_FO_START_DEMO, 0, 255, 281 },
        { 0, 0, NA_BGM_STAGE_CO, 0, 255, 2490 },
        { 1, 0, NA_BGM_STAGE_CO, 200, 255, 200 },
        { 0, 0, NA_BGM_STAGE_ME, 0, 255, 1584 },
        { 1, 0, NA_BGM_STAGE_ME, 200, 255, 200 },
        { 0, 0, NA_BGM_STAGE_TI, 0, 255, 1920 },
        { 1, 0, NA_BGM_STAGE_TI, 200, 255, 200 },
        { 0, 0, NA_BGM_STAGE_SX, 0, 255, 2290 },
        { 1, 0, NA_BGM_STAGE_SX, 200, 255, 200 },
        { 0, 0, NA_BGM_STAGE_ZO, 0, 255, 2005 },
        { 1, 0, NA_BGM_STAGE_ZO, 200, 255, 200 },
        { 0, 0, NA_BGM_STAGE_A6, 0, 255, 1905 },
        { 1, 0, NA_BGM_STAGE_A6, 200, 255, 200 },
        { 0, 0, NA_BGM_STAGE_VE1, 0, 255, 1671 },
        { 1, 0, NA_BGM_STAGE_VE1, 200, 255, 200 },
        { 0, 0, NA_BGM_STAGE_SY, 0, 255, 2095 },
        { 1, 0, NA_BGM_STAGE_SY, 200, 255, 200 },
        { 0, 0, NA_BGM_STAGE_FO, 0, 255, 1632 },
        { 1, 0, NA_BGM_STAGE_FO, 200, 255, 200 },
        { 0, 0, NA_BGM_STAGE_KA, 0, 255, 2184 },
        { 1, 0, NA_BGM_STAGE_KA, 200, 255, 200 },
        { 0, 0, NA_BGM_STAGE_AQ, 0, 255, 2400 },
        { 1, 0, NA_BGM_STAGE_AQ, 200, 255, 200 },
        { 0, 0, NA_BGM_STAGE_WZ, 0, 255, 1635 },
        { 1, 0, NA_BGM_STAGE_WZ, 200, 255, 200 },
        { 0, 0, NA_BGM_KATT, 0, 255, 389 },
        { 0, 0, NA_BGM_BILL, 0, 255, 268 },
        { 0, 0, NA_BGM_BOSS_CO, 0, 255, 1598 },
        { 1, 0, NA_BGM_BOSS_CO, 200, 255, 200 },
        { 0, 0, NA_BGM_BOSS_ME, 0, 0, 1470 },
        { 1, 0, NA_BGM_BOSS_ME, 200, 255, 200 },
        { 0, 0, NA_BGM_BOSS_ME, 0, 255, 1470 },
        { 1, 0, NA_BGM_BOSS_ME, 200, 255, 200 },
        { 0, 0, NA_BGM_REAL_BOSS, 0, 255, 1311 },
        { 1, 0, NA_BGM_REAL_BOSS, 200, 255, 200 },
        { 0, 0, NA_BGM_BOSS_BO, 0, 255, 1115 },
        { 1, 0, NA_BGM_BOSS_BO, 200, 255, 200 },
        { 0, 0, NA_BGM_STARWOLF, 0, 255, 2120 },
        { 1, 0, NA_BGM_STARWOLF, 200, 255, 200 },
        { 0, 0, NA_BGM_COURSE_CLEAR, 0, 255, 1091 },
        { 1, 0, NA_BGM_COURSE_CLEAR, 200, 255, 200 },
        { 0, 0, NA_BGM_COURSE_FAILURE, 0, 255, 1604 },
        { 1, 0, NA_BGM_COURSE_FAILURE, 200, 255, 200 },
        { 0, 0, NA_BGM_PLAYER_DOWN, 0, 255, 200 },
        { 0, 0, NA_BGM_GAME_OVER, 0, 255, 1020 },
        { 1, 0, NA_BGM_GAME_OVER, 200, 255, 200 },
        { 0, 0, NA_BGM_TRAINING, 0, 255, 900 },
        { 1, 0, NA_BGM_TRAINING, 200, 255, 200 },
        { 0, 0, NA_BGM_VS_SELECT, 0, 255, 665 },
        { 1, 0, NA_BGM_VS_SELECT, 200, 255, 200 },
        { 0, 0, NA_BGM_BATTLE, 0, 255, 1647 },
        { 1, 0, NA_BGM_BATTLE, 200, 255, 200 },
        { 0, 0, NA_BGM_BATTLE_LAST, 0, 255, 1667 },
        { 1, 0, NA_BGM_BATTLE_LAST, 200, 255, 200 },
        { 0, 0, NA_BGM_DASH_INTO_BASE, 0, 0, 176 },
        { 0, 0, NA_BGM_STAGE_ANDROSS, 0, 255, 588 },
        { 1, 0, NA_BGM_STAGE_ANDROSS, 200, 255, 200 },
        { 0, 0, NA_BGM_BOSS_ANDROSS, 0, 0, 2391 },
        { 1, 0, NA_BGM_BOSS_ANDROSS, 200, 255, 200 },
        { 0, 0, NA_BGM_BOSS_ANDROSS, 0, 255, 2391 },
        { 1, 0, NA_BGM_BOSS_ANDROSS, 200, 255, 200 },
        { 0, 0, NA_BGM_ANDROSS_BRAIN, 0, 255, 1700 },
        { 1, 0, NA_BGM_ANDROSS_BRAIN, 200, 255, 200 },
        { 0, 0, NA_BGM_ALL_CLEAR, 0, 255, 1459 },
        { 1, 0, NA_BGM_ALL_CLEAR, 200, 255, 200 },
        { 0, 0, NA_BGM_STAFF_ROLL, 0, 255, 9250 },
        { 1, 0, NA_BGM_STAFF_ROLL, 200, 255, 200 },
        { 255, 0, NA_BGM_STAGE_CO, 50, 255, 50 },
    },
};

s32 D_800C737C = 0;    // unused. file split?
f32 D_800C7380 = 1.0f; // unused/
u32 sNextVoiceId = 0;
u32 sCurrentVoiceId = 0;
u8 sSetNextVoiceId = 0;
u8 sUnkVoiceParam = 0;
u8 sMuteBgmForVoice = 0;

void Audio_dummy_80016A50(void) {
}

f32 Audio_GetSfxFalloff(u8 bankId, u8 entryIndex) {
    f32 cutoff;
    f32 midDist;
    f32 distance;
    f32 falloff;
    f32 midrange;
    f32 range;

    if (sSfxBanks[bankId][entryIndex].sfxId & SFX_FLAG_22) {
        return 1.0f;
    }
    distance = sSfxBanks[bankId][entryIndex].distance;
    if (distance > 33000.0f) {
        falloff = 0.0f;
    } else {
        switch ((sSfxBanks[bankId][entryIndex].sfxId & SFX_RANGE_MASK)) {
            default:
                range = 33000.0f / 20.0f;
                break;
            case 1 << SFX_RANGE_SHIFT:
                range = 33000.0f / 15.0f;
                break;
            case 2 << SFX_RANGE_SHIFT:
                range = 33000.0f / 10.5f;
                break;
            case 3 << SFX_RANGE_SHIFT:
                range = 33000.0f / 5.2f;
                break;
        }
        cutoff = range / 5.0f;
        if (distance < range / 5.0f) {
            falloff = 1.0f;
        } else if (distance < range) {
            midDist = range - cutoff;
            midrange = distance - cutoff;
            falloff = (((midDist - midrange) / midDist) * 0.19f) + 0.81f;
        } else {
            falloff = (1.0f - ((distance - range) / (33000.0f - range))) * 0.81f;
        }
        falloff = SQ(falloff);
    }
    return falloff;
}

s8 Audio_GetSfxReverb(u8 bankId, u8 entryIndex, u8 channelId) {
    s32 totalReverb;
    s8 distReverb = 0;
    s8 scriptReverb = 0;

    if (!(sSfxBanks[bankId][entryIndex].sfxId & SFX_FLAG_21)) {
        if (sSfxBanks[bankId][entryIndex].distance < (33000.0f / 4.0f)) {
            distReverb = (sSfxBanks[bankId][entryIndex].distance / (33000.0f / 4.0f)) * 40.0f;
        } else {
            distReverb = 40;
        }
    }
    if (IS_SEQUENCE_CHANNEL_VALID(gSeqPlayers[SEQ_PLAYER_SFX].channels[channelId])) {
        scriptReverb = gSeqPlayers[SEQ_PLAYER_SFX].channels[channelId]->seqScriptIO[6];
    }
    if (scriptReverb == -1) {
        scriptReverb = 0;
    }
    totalReverb = *sSfxBanks[bankId][entryIndex].reverbAdd + distReverb + scriptReverb + sEnvReverb + sAudioSpecReverb;
    totalReverb = MIN(127, totalReverb);
    return totalReverb;
}

s8 Audio_GetSfxPan(f32 xPos, f32 zPos, u8 mode) {
    if (sSfxChannelLayout != SFXCHAN_3) {
        f32 absx = ABSF(xPos);
        f32 absz = ABSF(zPos);
        f32 pan;

        if ((absx < 1.0f) && (absz < 1.0f)) {
            return 64;
        }
        absx = MIN(1200.0f, absx);
        absz = MIN(1200.0f, absz);

        if ((xPos == 0) && (zPos == 0)) {
            pan = 0.5f;
        } else if ((xPos >= 0.f) && (absz <= absx)) {
            pan = 1.0f - ((2400.0f - absx) / (10.0f * (2400.0f - absz)));
        } else if ((xPos < 0.0f) && (absz <= absx)) {
            pan = (2400.0f - absx) / (10.0f * (2400.0f - absz));
        } else {
            pan = (xPos / (2.5f * absz)) + 0.5f;
        }
        return ROUND(pan * 127.0f);
    } else if (mode != 4) {
        return ((mode & 1) * 127);
    }
    return 64;
}

f32 Audio_GetSfxFreqMod(u8 bankId, u8 entryIndex) {
    f32 distance;
    f32 freqMod = 1.0f;

    if (sSfxBanks[bankId][entryIndex].sfxId & SFX_FLAG_23) {
        freqMod -= ((gAudioRandom % 16) / 192.0f);
    }
    distance = sSfxBanks[bankId][entryIndex].distance;
    if (!(sSfxBanks[bankId][entryIndex].sfxId & SFX_FLAG_22)) {
        if (distance >= 33000.0f) {
            freqMod += 0.2f;
        } else {
            freqMod += 0.2f * (distance / 33000.0f);
        }
    }
    if ((sSfxChannelLayout != SFXCHAN_0) && (sSfxBanks[bankId][entryIndex].token & 2)) {
        freqMod *= 1.1f;
    }
    return freqMod;
}

void Audio_SetSfxProperties(u8 bankId, u8 entryIndex, u8 channelId) {
    f32 volumeMod = 1.0f;
    s8 reverb = 0;
    f32 freqMod = 1.0f;
    s8 pan = 64;
    SfxBankEntry* entry = &sSfxBanks[bankId][entryIndex];

    switch (bankId) {
        case SFX_BANK_PLAYER:
        case SFX_BANK_1:
        case SFX_BANK_2:
        case SFX_BANK_3:
            if (entry->state == 2) {
                AUDIOCMD_CHANNEL_SET_IO(SEQ_PLAYER_SFX, channelId, 1, gLevelType);
            }
            if ((entry->sfxId & SFX_FLAG_18) && (*entry->zPos > 0.0f)) {
                f32 yScaled = *entry->yPos / 2.5f;

                entry->distance = SQ(*entry->xPos) + SQ(yScaled);
            }
            entry->distance = sqrtf(entry->distance);
            volumeMod = Audio_GetSfxFalloff(bankId, entryIndex) * *entry->volMod * sSfxVolumeMods[bankId].value;
            reverb = Audio_GetSfxReverb(bankId, entryIndex, channelId);
            freqMod = Audio_GetSfxFreqMod(bankId, entryIndex) * *entry->freqMod;
            if (!((bankId == SFX_BANK_PLAYER) && ((-200.0f < *entry->zPos) && (*entry->zPos < 200.0f)) &&
                  (sSfxChannelLayout != SFXCHAN_3))) {
                pan = Audio_GetSfxPan(*entry->xPos, *entry->zPos, entry->token);
            }
            break;
        case SFX_BANK_SYSTEM:
            if (sSfxChannelLayout == SFXCHAN_3) {
                if (entry->token != 4) {
                    pan = (entry->token & 1) * 127;
                }
            }
            break;
    }
    if (volumeMod != sSfxChannelState[channelId].volMod) {
        AUDIOCMD_CHANNEL_SET_VOL_SCALE(SEQ_PLAYER_SFX, channelId, volumeMod);
        sSfxChannelState[channelId].volMod = volumeMod;
    }
    if (reverb != sSfxChannelState[channelId].reverb) {
        AUDIOCMD_CHANNEL_SET_REVERB_VOLUME(SEQ_PLAYER_SFX, channelId, reverb);
        sSfxChannelState[channelId].reverb = reverb;
    }
    if (freqMod != sSfxChannelState[channelId].freqMod) {
        AUDIOCMD_CHANNEL_SET_FREQ_SCALE(SEQ_PLAYER_SFX, channelId, freqMod);
        sSfxChannelState[channelId].freqMod = freqMod;
    }
    if (pan != sSfxChannelState[channelId].pan) {
        AUDIOCMD_CHANNEL_SET_PAN(SEQ_PLAYER_SFX, channelId, pan);
        sSfxChannelState[channelId].pan = pan;
    }
}

f32 Audio_UpdateDopplerShift(f32* srcPos, f32* srcVel, f32 soundSpeed, f32* curDopplerShift) {
    f32 xVel;
    f32 zVel;
    f32 xPos;
    f32 zPos;
    f32 xzDist;
    f32 xPosNext;
    f32 zPosNext;
    f32 xzDistNext;
    f32 step;
    f32 newShift;
    f32 relativeSpeed;
    f32 targetDopplerShift;
    s32 pad;

#ifdef AVOID_UB
    if ((srcPos == NULL) || (srcVel == NULL) || (curDopplerShift == NULL)) {
        return 0.0f;
    }
#endif

    xPos = srcPos[0];
    zPos = srcPos[2];
    xVel = srcVel[0];
    zVel = srcVel[2];
    xzDist = sqrtf(SQ(xPos) + SQ(zPos));
    xPosNext = xPos + xVel;
    zPosNext = zPos + zVel;
    xzDistNext = sqrtf(SQ(xPosNext) + SQ(zPosNext));
    relativeSpeed = (xzDist - xzDistNext) / soundSpeed;
    targetDopplerShift = 1.0f / (1.0f - relativeSpeed);

    step = targetDopplerShift - *curDopplerShift;
    newShift = *curDopplerShift;
    if (step != 0.0f) {
        if (step > 0.2f) {
            newShift += 0.2f;
        } else if (step < -0.2f) {
            newShift -= 0.2f;
        } else {
            newShift += step;
        }
    }
    *curDopplerShift = newShift;

    if (newShift > 4.0f) {
        newShift = 4.0f;
    } else if (newShift < 0.1f) {
        newShift = 0.1f;
    }

    return newShift;
}

void Audio_LoadInstruments(void) {
    u8 i;

    for (i = 0; sAudioSpecInstrumentSets[sAudioSpecId][i] != 0xFF; i++) {
        AUDIOCMD_GLOBAL_SYNC_LOAD_INSTRUMENT(0, sAudioSpecInstrumentSets[sAudioSpecId][i], 0);
    }
}

void Audio_LoadAquasSequence(void) {
    if (sAudioSpecId == AUDIOSPEC_AQ) {
        AUDIOCMD_GLOBAL_SYNC_LOAD_SEQ_PARTS(NA_BGM_STAGE_AQ, 0);
    }
}

void Audio_ResetSfxChannelState(void) {
    u8 i;

    sEnvReverb = 0;
    sAudioSpecReverb = sAudioSpecReverbAdd[sAudioSpecId];
    for (i = 0; i < 16; i++) {
        sSfxChannelState[i].volMod = 1.0f;
        sSfxChannelState[i].freqMod = 1.0f;
        sSfxChannelState[i].reverb = 0;
        sSfxChannelState[i].pan = 64;
    }
}

void Audio_StartSequence(u8 seqPlayId, u8 seqId, u8 seqArgs, u16 fadeInTime) {
    u8 i = 0;
    s32 pad;

    if (!sStartSeqDisabled || (seqPlayId == SEQ_PLAYER_SFX)) {
        AUDIOCMD_GLOBAL_INIT_SEQPLAYER((u32) seqPlayId, (u32) seqId, 0, fadeInTime);
        sActiveSequences[seqPlayId].prevSeqId = sActiveSequences[seqPlayId].seqId = seqId | ((seqArgs) << 8);
        if (sActiveSequences[seqPlayId].mainVolume.mod != 1.0f) {
            AUDIOCMD_SEQPLAYER_FADE_VOLUME_SCALE((u32) seqPlayId, sActiveSequences[seqPlayId].mainVolume.mod);
        }
        sActiveSequences[seqPlayId].tempo.timer = 0;
        sActiveSequences[seqPlayId].tempoOriginal = 0;
        sActiveSequences[seqPlayId].tempoCmd = 0;
        for (i = 0; i < 16; i++) {
            sActiveSequences[seqPlayId].channelMod[i].volume.value = 1.0f;
            sActiveSequences[seqPlayId].channelMod[i].volume.timer = 0;
            sActiveSequences[seqPlayId].channelMod[i].freq.value = 1.0f;
            sActiveSequences[seqPlayId].channelMod[i].freq.timer = 0;
        }
        sActiveSequences[seqPlayId].volChannelFlags = sActiveSequences[seqPlayId].freqModChannelFlags = 0;
    }
}

void Audio_StopSequence(u8 seqPlayId, u16 fadeOutTime) {
    AUDIOCMD_GLOBAL_DISABLE_SEQPLAYER(seqPlayId, fadeOutTime);
    sActiveSequences[seqPlayId].seqId = SEQ_ID_NONE;
}

void Audio_ProcessSeqCmd(u32 seqCmd) {
    u16 flag;
    u16 channelDisableMask;
    u16 fadeTimer;
    u16 val;
    s32 priority;
    u8 i; // sp63
    u8 specId;
    u8 oldSpecId;
    u8 ioPort;
    u8 channel;
    u8 found;
    u8 muteFlag;
    u8 duration;
    u8 seqNumber;
    u8 subOp;
    u8 seqPlayId;
    u8 seqArgs;
    u8* tempptr; // sp54
    u8* tempPtr2;
    u32 sp4C;

    seqPlayId = (seqCmd & 0x0F000000) >> 0x18;
    switch ((seqCmd >> 0x1C) & 0xFF) {
        case SEQCMD_OP_PLAY_SEQUENCE:
            seqNumber = seqCmd & 0xFF;
            seqArgs = (seqCmd & 0xFF00) >> 8;
            fadeTimer = (seqCmd & 0xFF0000) >> 13;

			seqArgs = 0;

            //if (!sActiveSequences[seqPlayId].isWaitingForFonts) 
			if (true)
			{
                if (seqArgs < 0x80) {
                    Audio_StartSequence(seqPlayId, seqNumber, seqArgs, fadeTimer);
                } else {
                    sActiveSequences[seqPlayId].startSeqCmd = seqCmd & ~0x8000;
                    sActiveSequences[seqPlayId].isWaitingForFonts = true;
                    Audio_StopSequence(seqPlayId, 1);
                    if (sActiveSequences[seqPlayId].prevSeqId != SEQ_ID_NONE) {
                        tempptr = AudioThread_GetFontsForSequence(seqNumber, &sp4C);
                        tempPtr2 = AudioThread_GetFontsForSequence(sActiveSequences[seqPlayId].prevSeqId & 0xFF, &sp4C);
                        if (tempptr[0] != tempPtr2[0]) {
                            AUDIOCMD_GLOBAL_DISCARD_SEQ_FONTS(seqNumber);
                        }
                    }
                    AUDIOCMD_GLOBAL_ASYNC_LOAD_FONT(seqNumber, 20, (s8) (seqPlayId + 1));
                }
            }
            break;
        case SEQCMD_OP_STOP_SEQUENCE:
            fadeTimer = (seqCmd & 0xFF0000) >> 13;
            Audio_StopSequence(seqPlayId, fadeTimer);
            return;
        case SEQCMD_OP_QUEUE_SEQUENCE:
            seqNumber = seqCmd & 0xFF;
            seqArgs = (seqCmd & 0xFF00) >> 8;
            fadeTimer = (seqCmd & 0xFF0000) >> 13;
            priority = seqArgs;
            for (i = 0; i < sNumSeqRequests[seqPlayId]; i++) {
                if (seqNumber == sSeqRequests[seqPlayId][i].seqId) {
                    if (i == 0) {
                        Audio_StartSequence(seqPlayId, seqNumber, seqArgs, fadeTimer);
                    }
                    return;
                }
            }
            found = sNumSeqRequests[seqPlayId];
            for (i = 0; i < sNumSeqRequests[seqPlayId]; i++) {
                if (seqArgs >= sSeqRequests[seqPlayId][i].priority) {
                    found = i;
                    i = sNumSeqRequests[seqPlayId];
                }
            }
            if ((found != sNumSeqRequests[seqPlayId]) || (found == 0)) {
                if (sNumSeqRequests[seqPlayId] < 5) {
                    sNumSeqRequests[seqPlayId]++;
                }
                for (i = sNumSeqRequests[seqPlayId] - 1; i != found; i--) {
                    sSeqRequests[seqPlayId][i].priority = sSeqRequests[seqPlayId][i - 1].priority;
                    sSeqRequests[seqPlayId][i].seqId = sSeqRequests[seqPlayId][i - 1].seqId;
                }
                sSeqRequests[seqPlayId][found].priority = seqArgs;
                sSeqRequests[seqPlayId][found].seqId = seqNumber;
            }
            if (found == 0) {
                Audio_StartSequence(seqPlayId, seqNumber, seqArgs, fadeTimer);
            }
            break;
        case SEQCMD_OP_UNQUEUE_SEQUENCE:
            fadeTimer = (seqCmd & 0xFF0000) >> 0xD;
            found = sNumSeqRequests[seqPlayId];
            for (i = 0; i < sNumSeqRequests[seqPlayId]; i++) {
                seqNumber = seqCmd & 0xFF;
                if (sSeqRequests[seqPlayId][i].seqId == seqNumber) {
                    found = i;
                    i = sNumSeqRequests[seqPlayId];
                }
            }
            if (found != sNumSeqRequests[seqPlayId]) {
                for (i = found; i < sNumSeqRequests[seqPlayId] - 1; i++) {
                    sSeqRequests[seqPlayId][i].priority = sSeqRequests[seqPlayId][i + 1].priority;
                    sSeqRequests[seqPlayId][i].seqId = sSeqRequests[seqPlayId][i + 1].seqId;
                }
                sNumSeqRequests[seqPlayId]--;
            }
            if (found == 0) {
                Audio_StopSequence(seqPlayId, fadeTimer);
                if (sNumSeqRequests[seqPlayId] != 0) {

                    Audio_StartSequence(seqPlayId, sSeqRequests[seqPlayId][0].seqId,
                                        sSeqRequests[seqPlayId][0].priority, fadeTimer);
                }
            }
            break;
        case SEQCMD_OP_SET_SEQPLAYER_VOLUME:
            val = seqCmd & 0xFF;
            duration = (seqCmd & 0xFF0000) >> 0xF;

            if (duration == 0) {
                duration++;
            }
            sActiveSequences[seqPlayId].mainVolume.target = val / 127.0f;
            if (sActiveSequences[seqPlayId].mainVolume.mod != sActiveSequences[seqPlayId].mainVolume.target) {
                sActiveSequences[seqPlayId].mainVolume.step =
                    (sActiveSequences[seqPlayId].mainVolume.mod - sActiveSequences[seqPlayId].mainVolume.target) /
                    duration;
                sActiveSequences[seqPlayId].mainVolume.timer = duration;
            }
            break;
        case SEQCMD_OP_SET_SEQPLAYER_FREQ:
            val = (seqCmd & 0xFFFF);
            duration = (seqCmd & 0xFF0000) >> 0xF;

            if (duration == 0) {
                duration++;
            }
            for (i = 0; i < 16; i++) {
                sActiveSequences[seqPlayId].channelMod[i].freq.target = val / 1000.0f;
                sActiveSequences[seqPlayId].channelMod[i].freq.step =
                    (sActiveSequences[seqPlayId].channelMod[i].freq.value -
                     sActiveSequences[seqPlayId].channelMod[i].freq.target) /
                    duration;
                sActiveSequences[seqPlayId].channelMod[i].freq.timer = duration;
            }
            sActiveSequences[seqPlayId].freqModChannelFlags = 0xFFFF;
            break;
        case SEQCMD_OP_SET_CHANNEL_VOLUME:
            val = (seqCmd & 0xFF);
            channel = (seqCmd & 0xF00) >> 8;
            duration = (seqCmd & 0xFF0000) >> 0xF;

            if (duration == 0) {
                duration++;
            }

            sActiveSequences[seqPlayId].channelMod[channel].volume.target = val / 127.0f;
            if (sActiveSequences[seqPlayId].channelMod[channel].volume.value !=
                sActiveSequences[seqPlayId].channelMod[channel].volume.target) {
                sActiveSequences[seqPlayId].channelMod[channel].volume.step =
                    (sActiveSequences[seqPlayId].channelMod[channel].volume.value -
                     sActiveSequences[seqPlayId].channelMod[channel].volume.target) /
                    duration;
                sActiveSequences[seqPlayId].channelMod[channel].volume.timer = duration;
                sActiveSequences[seqPlayId].freqModChannelFlags |= 1 << channel;
            }
            break;
        case SEQCMD_OP_SET_SEQPLAYER_IO:
            val = seqCmd & 0xFF;
            ioPort = ((seqCmd & 0xFF0000) >> 0x10); // may be misnamed
            AUDIOCMD_SEQPLAYER_SET_IO(seqPlayId, ioPort, val);
            break;
        case SEQCMD_OP_SET_CHANNEL_IO:
            val = seqCmd & 0xFF;
            channel = (seqCmd & 0xF00) >> 8;

            ioPort = (seqCmd & 0xFF0000) >> 0x10;
            if (!(sActiveSequences[seqPlayId].channelPortMask & (1 << channel))) {
                AUDIOCMD_CHANNEL_SET_IO(seqPlayId, (u32) channel, ioPort, val);
            }
            break;
        case SEQCMD_OP_SET_CHANNEL_IO_DISABLE_MASK:
            channelDisableMask = seqCmd & 0xFFFF;
            sActiveSequences[seqPlayId].channelPortMask = channelDisableMask;
            break;
        case SEQCMD_OP_SET_CHANNEL_DISABLE_MASK:
            channelDisableMask = seqCmd & 0xFFFF;

            flag = 1;
            for (i = 0; i < 16; i++) {
                AUDIOCMD_CHANNEL_SET_MUTE(seqPlayId, (u32) i, (channelDisableMask & flag) ? 1 : 0);
                flag <<= 1;
            }
            break;
        case SEQCMD_OP_TEMPO_CMD:
            sActiveSequences[seqPlayId].tempoCmd = seqCmd;
            break;
        case SEQCMD_OP_SETUP_CMD:
            subOp = (seqCmd & 0xF00000) >> 20;
            if (subOp != SEQCMD_SUB_OP_SETUP_RESET_SETUP_CMDS) {
                found = sActiveSequences[seqPlayId].setupCmdNum++;
                if (found < 5) {
                    sActiveSequences[seqPlayId].setupCmd[found] = seqCmd;
                    sActiveSequences[seqPlayId].setupCmdTimer = 2;
                }
            } else {
                sActiveSequences[seqPlayId].setupCmdNum = 0;
            }
            break;
        case SEQCMD_OP_GLOBAL_CMD:
            val = seqCmd & 0xFF;
            subOp = (seqCmd & 0xF00) >> 8;

            switch (subOp) {
                case SEQCMD_SUB_OP_GLOBAL_SET_SOUND_MODE:
                    AUDIOCMD_GLOBAL_SET_SOUND_MODE(sSoundModeList[val]);
                    break;
                case SEQCMD_SUB_OP_GLOBAL_DISABLE_NEW_SEQUENCES:
                    sStartSeqDisabled = val & 1;
                    break;
            }
            break;
        case SEQCMD_OP_RESET_AUDIO_HEAP:
            specId = seqCmd & 0xFF;
            sSfxChannelLayout = (seqCmd & 0xFF00) >> 8;
            oldSpecId = sAudioSpecId;
            sAudioSpecId = specId;

            if (oldSpecId != specId) 
			{
                AudioThread_ResetAudioHeap(specId);
                Audio_StartReset(oldSpecId);
                AUDIOCMD_GLOBAL_STOP_AUDIOCMDS();
            } 
			else 
			{
                Audio_StopSequence(SEQ_PLAYER_BGM, 1);
                Audio_StopSequence(SEQ_PLAYER_FANFARE, 1);
            }
            break;
    }
}

void Audio_QueueSeqCmd(s32 seqCmd) {
    sAudioSeqCmds[sSeqCmdWritePos] = seqCmd;
    sSeqCmdWritePos++;
}

void Audio_ProcessSeqCmds(void) {
    while (sSeqCmdWritePos != sSeqCmdReadPos) {
        Audio_ProcessSeqCmd(sAudioSeqCmds[sSeqCmdReadPos++]);
    }
}

u16 Audio_GetActiveSeqId(u8 seqPlayId) {
    if (!gSeqPlayers[seqPlayId].enabled) {
        return 0xFFFF;
    }
    return sActiveSequences[seqPlayId].seqId;
}

s32 Audio_SeqCmdNotQueued(s32 seqCmd) {
    s32 notFound = true;
    u8 i;

    for (i = sSeqCmdReadPos; i < sSeqCmdWritePos; i++) {
        if (seqCmd == sAudioSeqCmds[i]) {
            notFound = false;
            i = sSeqCmdWritePos;
        }
    }
    return notFound;
}

s32 Audio_SeqCmdValueNotQueued(s32 cmdVal, s32 cmdMask) {
    s32 notFound = true;
    u8 i;

    for (i = sSeqCmdReadPos; i < sSeqCmdWritePos; i++) {
        if (cmdVal == (sAudioSeqCmds[i] & cmdMask)) {
            notFound = false;
            i = sSeqCmdWritePos;
        }
    }
    return notFound;
}

void Audio_ResetSequenceRequests(u8 seqPlayId) {
    sNumSeqRequests[seqPlayId] = 0;
}

// unused
void Audio_DisableSetupOp(u8 seqPlayId, u8 opcode) {
    u8 i;

    for (i = 0; i < sActiveSequences[seqPlayId].setupCmdNum; i++) {
        u8 setupOp = ((sActiveSequences[seqPlayId].setupCmd[i] & 0xF00000) >> 20);

        if (setupOp == opcode) {
            sActiveSequences[seqPlayId].setupCmd[i] = 0xFF000000; // 0 duration volume reset on SEQ_PLAYER_BGM
        }
    }
}

void Audio_SetSequenceFade(u8 seqPlayId, u8 fadeModId, u8 fadeMod, u8 fadeTime) {
    sActiveSequences[seqPlayId].mainVolume.fadeMod[fadeModId] = fadeMod;
    sActiveSequences[seqPlayId].mainVolume.fadeTimer = fadeTime;
    sActiveSequences[seqPlayId].mainVolume.fadeActive = true;
}

void Audio_UpdateActiveSequences(void) {
    u8 seqPlayId;
    u8 i;
    u8 tempoTimer;
    u8 channelId;
    u16 tempoTarget;
    u16 prevTempo;
    u16 seqId;
    u8 tempoOp;
    u8 setupSeqPlayId;
    u8 val1;
    u8 setupOp;
    u8 val2;
    u8 temp2;
    s32 temp;
    u32 cmd;
    f32 fadeMod;
    u32 out;
    s32 pad1;
    s32 pad2;

    for (seqPlayId = 0; seqPlayId < SEQ_PLAYER_MAX; seqPlayId++) {
        if (sActiveSequences[seqPlayId].isWaitingForFonts) {
            switch ((s32) AudioThread_GetAsyncLoadStatus(&out)) 
			{
                case SEQ_PLAYER_BGM + 1:
                case SEQ_PLAYER_FANFARE + 1:
                case SEQ_PLAYER_SFX + 1:
                case SEQ_PLAYER_VOICE + 1:
                    sActiveSequences[seqPlayId].isWaitingForFonts = false;
                    Audio_ProcessSeqCmd(sActiveSequences[seqPlayId].startSeqCmd);
                    break;
            }
        }
        if (sActiveSequences[seqPlayId].mainVolume.fadeActive) {
            fadeMod = 1.0f;
            for (i = 0; i < 3; i++) {
                fadeMod *= sActiveSequences[seqPlayId].mainVolume.fadeMod[i] / 127.0f;
            }
            SEQCMD_SET_SEQPLAYER_VOLUME(seqPlayId, sActiveSequences[seqPlayId].mainVolume.fadeTimer,
                                        (u8) (fadeMod * 127.0f));
            sActiveSequences[seqPlayId].mainVolume.fadeActive = false;
        }
        if (sActiveSequences[seqPlayId].mainVolume.timer != 0) {
            sActiveSequences[seqPlayId].mainVolume.timer--;
            if (sActiveSequences[seqPlayId].mainVolume.timer != 0) {
                sActiveSequences[seqPlayId].mainVolume.mod -= sActiveSequences[seqPlayId].mainVolume.step;
            } else {
                sActiveSequences[seqPlayId].mainVolume.mod = sActiveSequences[seqPlayId].mainVolume.target;
            }
            AUDIOCMD_SEQPLAYER_FADE_VOLUME_SCALE((u32) seqPlayId, sActiveSequences[seqPlayId].mainVolume.mod);
        }
        if (sActiveSequences[seqPlayId].tempoCmd != 0) {
            cmd = sActiveSequences[seqPlayId].tempoCmd;
            temp = cmd & 0xFFF;
            temp2 = (cmd & 0xFF0000) >> 0xF;
            tempoTimer = temp2;
            tempoTarget = temp;

            if (temp2 == 0) {
                tempoTimer = temp2 + 1;
            }
            if (gSeqPlayers[seqPlayId].enabled) {
                prevTempo = gSeqPlayers[seqPlayId].tempo / 48;
                tempoOp = ((cmd & 0xF000) >> 0xC);

                switch (tempoOp) {
                    case SEQCMD_SUB_OP_TEMPO_SPEED_UP:
                        tempoTarget = tempoTarget + prevTempo;
                        break;
                    case SEQCMD_SUB_OP_TEMPO_SLOW_DOWN:
                        if (tempoTarget < prevTempo) {
                            tempoTarget = prevTempo - tempoTarget;
                        }
                        break;
                    case SEQCMD_SUB_OP_TEMPO_SCALE:
                        tempoTarget = prevTempo * (tempoTarget / 100.0f);
                        break;
                    case SEQCMD_SUB_OP_TEMPO_RESET:
                        if (sActiveSequences[seqPlayId].tempoOriginal != 0) {
                            tempoTarget = sActiveSequences[seqPlayId].tempoOriginal;
                        } else {
                            tempoTarget = prevTempo;
                        }
                        break;
                }
                if (tempoTarget > 300) {
                    tempoTarget = 300;
                }
                if (!sActiveSequences[seqPlayId].tempoOriginal) {
                    sActiveSequences[seqPlayId].tempoOriginal = prevTempo;
                }
                sActiveSequences[seqPlayId].tempo.target = tempoTarget;
                sActiveSequences[seqPlayId].tempo.value = (s32) gSeqPlayers[seqPlayId].tempo / 48;

                sActiveSequences[seqPlayId].tempo.step =
                    (sActiveSequences[seqPlayId].tempo.value - sActiveSequences[seqPlayId].tempo.target) / tempoTimer;
                sActiveSequences[seqPlayId].tempo.timer = tempoTimer;
                sActiveSequences[seqPlayId].tempoCmd = 0;
            }
        }
        if (sActiveSequences[seqPlayId].tempo.timer != 0) {
            sActiveSequences[seqPlayId].tempo.timer--;
            if (sActiveSequences[seqPlayId].tempo.timer != 0) {
                sActiveSequences[seqPlayId].tempo.value -= sActiveSequences[seqPlayId].tempo.step;
            } else {
                sActiveSequences[seqPlayId].tempo.value = sActiveSequences[seqPlayId].tempo.target;
            }
            AUDIOCMD_SEQPLAYER_SET_TEMPO((u32) seqPlayId, (s32) sActiveSequences[seqPlayId].tempo.value);
        }
        if (sActiveSequences[seqPlayId].volChannelFlags != 0) {
            for (channelId = 0; channelId < 16; channelId++) {
                if (sActiveSequences[seqPlayId].channelMod[channelId].volume.timer != 0) {
                    sActiveSequences[seqPlayId].channelMod[channelId].volume.timer--;
                    if (sActiveSequences[seqPlayId].channelMod[channelId].volume.timer) {
                        sActiveSequences[seqPlayId].channelMod[channelId].volume.value -=
                            sActiveSequences[seqPlayId].channelMod[channelId].volume.step;
                    } else {
                        sActiveSequences[seqPlayId].channelMod[channelId].volume.value =
                            sActiveSequences[seqPlayId].channelMod[channelId].volume.target;
                        sActiveSequences[seqPlayId].volChannelFlags ^= 1 << channelId;
                    }
                    AUDIOCMD_CHANNEL_SET_VOL_SCALE((u32) seqPlayId, (u32) channelId,
                                                   sActiveSequences[seqPlayId].channelMod[channelId].volume.value);
                }
            }
        }
        if (sActiveSequences[seqPlayId].freqModChannelFlags != 0) {
            for (channelId = 0; channelId < 16; channelId++) {
                if (sActiveSequences[seqPlayId].channelMod[channelId].freq.timer != 0) {
                    sActiveSequences[seqPlayId].channelMod[channelId].freq.timer--;
                    if (sActiveSequences[seqPlayId].channelMod[channelId].freq.timer != 0) {
                        sActiveSequences[seqPlayId].channelMod[channelId].freq.value -=
                            sActiveSequences[seqPlayId].channelMod[channelId].freq.step;
                    } else {
                        sActiveSequences[seqPlayId].channelMod[channelId].freq.value =
                            sActiveSequences[seqPlayId].channelMod[channelId].freq.target;
                        sActiveSequences[seqPlayId].freqModChannelFlags ^= 1 << channelId;
                    }
                    AUDIOCMD_CHANNEL_SET_FREQ_SCALE((u32) seqPlayId, (u32) channelId,
                                                    sActiveSequences[seqPlayId].channelMod[channelId].freq.value);
                }
            }
        }
        if (sActiveSequences[seqPlayId].setupCmdNum == 0) {
            continue;
        }
        if (!Audio_SeqCmdValueNotQueued(SEQCMD_OP_RESET_AUDIO_HEAP << 28, SEQCMD_OP_MASK)) {
            sActiveSequences[seqPlayId].setupCmdNum = 0;
            break;
        }
        if (sActiveSequences[seqPlayId].setupCmdTimer != 0) {
            sActiveSequences[seqPlayId].setupCmdTimer--;
        } else if (!gSeqPlayers[seqPlayId].enabled) {
            for (i = 0; i < sActiveSequences[seqPlayId].setupCmdNum; i++) {
                setupOp = (sActiveSequences[seqPlayId].setupCmd[i] & 0xF00000) >> 20;

                setupSeqPlayId = (sActiveSequences[seqPlayId].setupCmd[i] & 0xF0000) >> 16;
                val2 = (sActiveSequences[seqPlayId].setupCmd[i] & 0xFF00) >> 8;
                val1 = sActiveSequences[seqPlayId].setupCmd[i] & 0xFF;
                switch (setupOp) {
                    case SEQCMD_SUB_OP_SETUP_RESTORE_SEQPLAYER_VOLUME:
                        Audio_SetSequenceFade(setupSeqPlayId, 1, 127, val2);
                        break;
                    case SEQCMD_SUB_OP_SETUP_SEQ_UNQUEUE:
                        SEQCMD_UNQUEUE_SEQUENCE(seqPlayId, 0, sActiveSequences[seqPlayId].seqId);
                        break;
                    case SEQCMD_SUB_OP_SETUP_RESTART_SEQ:
                        SEQCMD_PLAY_SEQUENCE(setupSeqPlayId, 1, 0, sActiveSequences[setupSeqPlayId].seqId);
                        sActiveSequences[setupSeqPlayId].mainVolume.fadeActive = true;
                        sActiveSequences[setupSeqPlayId].mainVolume.fadeMod[1] = 127;
                        break;
                    case SEQCMD_SUB_OP_SETUP_TEMPO_SCALE:
                        SEQCMD_SCALE_TEMPO(setupSeqPlayId, val2, val1);
                        break;
                    case SEQCMD_SUB_OP_SETUP_TEMPO_RESET:
                        SEQCMD_RESET_TEMPO(setupSeqPlayId, val1);
                        break;
                    case SEQCMD_SUB_OP_SETUP_PLAY_SEQ:
                        seqId = sActiveSequences[seqPlayId].setupCmd[i] & 0xFFFF;
                        SEQCMD_PLAY_SEQUENCE(setupSeqPlayId, sActiveSequences[setupSeqPlayId].setupFadeTimer, 0, seqId);
                        Audio_SetSequenceFade(setupSeqPlayId, 1, 127, 0);
                        sActiveSequences[setupSeqPlayId].setupFadeTimer = 0;
                        break;
                    case SEQCMD_SUB_OP_SETUP_SET_FADE_TIMER:
                        sActiveSequences[seqPlayId].setupFadeTimer = val2;
                        break;
                }
            }
            sActiveSequences[seqPlayId].setupCmdNum = 0;
        }
    }
}

void Audio_SetDelayedSeqCmd(u32 seqCmd, u16 delay) {
    u8 opcode = (seqCmd >> 0x1C);

    sDelayedSeqCmds[opcode].seqData = seqCmd;
    sDelayedSeqCmds[opcode].timer = delay;
    sDelayedSeqCmdFlags |= 1 << opcode;
}

void Audio_UpdateDelayedSeqCmds(void) {
    u8 opcode = 0;
    u16 flag = 1;
    u16 delayedCmdFlags = sDelayedSeqCmdFlags;

    while (delayedCmdFlags) {
        if (delayedCmdFlags & flag) {
            if (sDelayedSeqCmds[opcode].timer != 0) {
                sDelayedSeqCmds[opcode].timer--;
            } else {
                Audio_QueueSeqCmd(sDelayedSeqCmds[opcode].seqData);
                sDelayedSeqCmdFlags ^= flag;
            }
            delayedCmdFlags ^= flag;
        }
        opcode++;
        flag <<= 1;
    }
}

u8 Audio_HandleReset(void) {
    if (sAudioResetStatus != AUDIORESET_READY) {
        if (sAudioResetStatus == AUDIORESET_WAIT) {
            if (AudioThread_ResetComplete() == true) {
                sAudioResetStatus = AUDIORESET_READY;
                AUDIOCMD_SEQPLAYER_SET_IO(SEQ_PLAYER_SFX, 0, sSfxChannelLayout);
                Audio_RestartSeqPlayers();
            }
        } else if (sAudioResetStatus == AUDIORESET_BLOCK) {
            while (AudioThread_ResetComplete() != true) {
                ;
            }
            sAudioResetStatus = AUDIORESET_READY;
            AUDIOCMD_SEQPLAYER_SET_IO(SEQ_PLAYER_SFX, 0, sSfxChannelLayout);
            Audio_RestartSeqPlayers();
        }
    }
    return sAudioResetStatus;
}

void Audio_ResetActiveSequences(void) {
    u8 i;

    for (i = 0; i < 4; i++) {
        sNumSeqRequests[i] = 0;
        sActiveSequences[i].seqId = SEQ_ID_NONE;
        sActiveSequences[i].prevSeqId = SEQ_ID_NONE;
        sActiveSequences[i].tempo.timer = 0;
        sActiveSequences[i].tempoOriginal = 0;
        sActiveSequences[i].tempoCmd = 0;
        sActiveSequences[i].channelPortMask = 0;
        sActiveSequences[i].setupCmdNum = 0;
        sActiveSequences[i].setupFadeTimer = 0;
        sActiveSequences[i].freqModChannelFlags = 0;
        sActiveSequences[i].volChannelFlags = 0;
        sActiveSequences[i].mainVolume.fadeMod[2] = 127;
    }
}

void Audio_ResetActiveSequencesAndVolume(void) {
    u8 i;

    for (i = 0; i < 4; i++) {
        sActiveSequences[i].mainVolume.mod = 1.0f;
        sActiveSequences[i].mainVolume.timer = 0;
        sActiveSequences[i].mainVolume.fadeActive = false;
        sActiveSequences[i].mainVolume.fadeMod[0] = 127;
        sActiveSequences[i].mainVolume.fadeMod[1] = 127;
        sActiveSequences[i].mainVolume.fadeMod[2] = 127;
    }
    Audio_ResetActiveSequences();
}

void Audio_SetSfxBanksMute(u16 muteFlags) {
    u8 i;

    for (i = 0; i < 5; i++) {
        sSfxBankMuted[i] = (muteFlags & 1) ? true : false;
        muteFlags = muteFlags >> 1;
    }
}

void Audio_ClearBGMMute(u8 channelIndex) {
    sChannelMuteFlags &= (1 << channelIndex) ^ 0xFFFF;
    if (sChannelMuteFlags == 0) {
        Audio_SetSequenceFade(SEQ_PLAYER_BGM, 2, 127, 15);
    }
}

void Audio_PlaySfx(u32 sfxId, f32* sfxSource, u8 token, f32* freqMod, f32* volMod, s8* reverbAdd) {
    if (sSfxBankMuted[SFX_BANK_ALT(sfxId)] == 0) {
        SfxRequest* request = &sSfxRequests[sSfxRequestWriteIndex];

        request->sfxId = sfxId;
        request->source = sfxSource;
        request->token = token;
        request->freqMod = freqMod;
        request->volMod = volMod;
        request->reverbAdd = reverbAdd;
        sSfxRequestWriteIndex++;
    }
}

void Audio_RemoveMatchingSfxRequests(u8 aspect, SfxBankEntry* data) {
    u8 i = sSfxRequestReadIndex;

    for (i; i != sSfxRequestWriteIndex; i++) {
        s32 found = false;
        SfxRequest* request = &sSfxRequests[i];

        switch (aspect) {
            case 0:
                if ((request->sfxId & SFX_BANK_MASK) == (data->sfxId & SFX_BANK_MASK)) {
                    found = true;
                }
                break;
            case 1:
                if (((request->sfxId & SFX_BANK_MASK) == (data->sfxId & SFX_BANK_MASK)) &&
                    (&request->source[0] == data->xPos)) {
                    found = true;
                }
                break;
            case 2:
                if (&request->source[0] == data->xPos) {
                    found = true;
                }
                break;
            case 3:
                if ((&request->source[0] == data->xPos) && (request->sfxId == data->sfxId)) {
                    found = true;
                }
                break;
            case 4:
                if ((request->token == data->token) && (request->sfxId == data->sfxId)) {
                    found = true;
                }
                break;
            case 5:
                if (request->sfxId == data->sfxId) {
                    found = true;
                }
                break;
        }
        if (found) {
            request->sfxId = NA_SE_NONE;
        }
    }
}

void Audio_ProcessSfxRequest(void) {
    SfxRequest* request = &sSfxRequests[sSfxRequestReadIndex];
    u8 next;
    s32 bankId;
    u8 evict = 0;
    u32 sfxId;
    u8 count;
    SfxBankEntry* entry;

    if (request->sfxId == NA_SE_NONE) {
        return;
    }
    bankId = SFX_BANK(request->sfxId);
    next = sSfxBanks[bankId][0].next;
    count = 0;
    while ((next != 0xFF) && (next != 0)) {
        if (&request->source[0] == sSfxBanks[bankId][next].xPos) {
            if (request->sfxId == sSfxBanks[bankId][next].sfxId) {
                count = sUsedChannelsPerBank[sSfxChannelLayout][bankId];
            } else {
                if (count == 0) {
                    evict = next;
                    sfxId = sSfxBanks[bankId][next].sfxId;
                } else if ((sSfxBanks[bankId][next].sfxId & SFX_IMPORT_MASK) < (sfxId & SFX_IMPORT_MASK)) {
                    evict = next;
                    sfxId = sSfxBanks[bankId][next].sfxId;
                }
                count++;
                if (count == sUsedChannelsPerBank[sSfxChannelLayout][bankId]) {
                    if ((request->sfxId & SFX_IMPORT_MASK) >= (sfxId & SFX_IMPORT_MASK)) {
                        next = evict;
                    } else {
                        next = 0;
                    }
                }
            }
            if (count == sUsedChannelsPerBank[sSfxChannelLayout][bankId]) {
                if ((request->sfxId & SFX_FLAG_27) || (request->sfxId & SFX_FLAG_18) || (next == evict)) {
                    if ((sSfxBanks[bankId][next].sfxId & SFX_FLAG_19) && (sSfxBanks[bankId][next].state != 1)) {
                        Audio_ClearBGMMute(sSfxBanks[bankId][next].channelIndex);
                    }
                    sSfxBanks[bankId][next].token = request->token;
                    sSfxBanks[bankId][next].sfxId = request->sfxId;
                    sSfxBanks[bankId][next].state = SFX_STATE(request->sfxId);
                    sSfxBanks[bankId][next].freshness = 2;
                    sSfxBanks[bankId][next].freqMod = request->freqMod;
                    sSfxBanks[bankId][next].volMod = request->volMod;
                    sSfxBanks[bankId][next].reverbAdd = request->reverbAdd;
                }
                next = 0;
            }
        }
        if (next != 0) {
            next = sSfxBanks[bankId][next].next;
        }
    }
    if ((sSfxBanks[bankId][sSfxBankFreeListStart[bankId]].next != 0xFF) && (next != 0)) {
        next = sSfxBankFreeListStart[bankId];
        entry = &sSfxBanks[bankId][next];
        entry->xPos = &request->source[0];
        entry->yPos = &request->source[1];
        entry->zPos = &request->source[2];
        entry->token = request->token;
        entry->freqMod = request->freqMod;
        entry->volMod = request->volMod;
        entry->reverbAdd = request->reverbAdd;
        entry->sfxId = request->sfxId;
        entry->state = SFX_STATE(request->sfxId);
        entry->freshness = 2;

        entry->prev = sSfxBankListEnd[bankId];

        sSfxBanks[bankId][sSfxBankListEnd[bankId]].next = sSfxBankFreeListStart[bankId];
        sSfxBankListEnd[bankId] = sSfxBankFreeListStart[bankId];
        sSfxBankFreeListStart[bankId] = sSfxBanks[bankId][sSfxBankFreeListStart[bankId]].next;
        sSfxBanks[bankId][sSfxBankFreeListStart[bankId]].prev = 0xFF;

        entry->next = 0xFF;
    }
}

void Audio_RemoveSfxBankEntry(u8 bankId, u8 entryIndex) {
    SfxBankEntry* sfxBank = sSfxBanks[bankId];
    s32 pad;

    if (sfxBank[entryIndex].sfxId & SFX_FLAG_19) {
        Audio_ClearBGMMute(sfxBank[entryIndex].channelIndex);
    }
    if (entryIndex == sSfxBankListEnd[bankId]) {
        sSfxBankListEnd[bankId] = sfxBank[entryIndex].prev;
    } else {
        sfxBank[sfxBank[entryIndex].next].prev = sfxBank[entryIndex].prev;
    }
    sfxBank[sfxBank[entryIndex].prev].next = sfxBank[entryIndex].next;
    sfxBank[entryIndex].next = sSfxBankFreeListStart[bankId];
    sfxBank[entryIndex].prev = 0xFF;

    sfxBank[sSfxBankFreeListStart[bankId]].prev = entryIndex;
    sSfxBankFreeListStart[bankId] = entryIndex;
    sfxBank[entryIndex].state = 0;
}

void Audio_ChooseActiveSfx(u8 bankId) {
    u8 numChosenSfx = 0;
    u8 numChannels;
    u8 k;
    u8 i;
    SfxBankEntry* entry;
    ActiveSfx* activeSfx;
    f32 maxRangeSq;
    f32 yScaled;
    ActiveSfx chosenSfx[8];
    u8 chosenEntryIndex;
    u8 j;
    u8 entryIndex;
    u8 needNewSfx;
    s32 importance;

    for (i = 0; i < 8; i++) {
        chosenSfx[i].priority = INT32_MAX;
        chosenSfx[i].entryIndex = 0xFF;
    }
    entryIndex = sSfxBanks[bankId][0].next;
    k = 0;
    while (entryIndex != 0xFF) {
        if ((sSfxBanks[bankId][entryIndex].state == 1) &&
            ((sSfxBanks[bankId][entryIndex].sfxId & SFX_FLAG_27) == SFX_FLAG_27)) {
            sSfxBanks[bankId][entryIndex].freshness--;
        }
        if (sSfxBanks[bankId][entryIndex].freshness == 0) {
            Audio_RemoveSfxBankEntry(bankId, entryIndex);
        } else if (sSfxBanks[bankId][entryIndex].state != 0) {
            entry = &sSfxBanks[bankId][entryIndex];

            if (&entry->xPos[0] == gDefaultSfxSource) {
                entry->distance = 0.0f;
            } else {
                yScaled = *entry->yPos / 2.5f;
                entry->distance = SQ(*entry->xPos) + SQ(yScaled) + SQ(*entry->zPos);
            }
            importance = SFX_IMPORT(entry->sfxId);
            if (entry->sfxId & SFX_FLAG_20) {
                entry->priority = SQ(0xFF - importance) * SQ(76);
            } else {
                entry->priority = (u32) entry->distance + SQ(0xFF - importance) * SQ(76);
                if (*entry->zPos > 0.0f) {
                    entry->priority += (s32) (*entry->zPos * 6.0f);
                }
            }
            if (SFX_RANGE(entry->sfxId) != 0) {
                maxRangeSq = SQ(33000.0f) / SQ((s32) SFX_RANGE(entry->sfxId));
            } else {
                maxRangeSq = SQ(100000.0f);
            }
            if (entry->distance > maxRangeSq) {
                if (entry->state == 4) {
                    AUDIOCMD_CHANNEL_SET_IO(2, entry->channelIndex, 0, 0);
                    if (entry->sfxId & SFX_FLAG_27) {
                        Audio_RemoveSfxBankEntry(bankId, entryIndex);
                        entryIndex = k;
                    }
                }
            } else {
                numChannels = sChannelsPerBank[sSfxChannelLayout][bankId];
                for (i = 0; i < numChannels; i++) {
                    if (chosenSfx[i].priority >= entry->priority) {
                        if (numChosenSfx < sChannelsPerBank[sSfxChannelLayout][bankId]) {
                            numChosenSfx++;
                        }
                        for (j = numChannels - 1; j > i; j--) {
                            chosenSfx[j].priority = chosenSfx[j - 1].priority;
                            chosenSfx[j].entryIndex = chosenSfx[j - 1].entryIndex;
                        }
                        chosenSfx[i].priority = entry->priority;
                        chosenSfx[i].entryIndex = entryIndex;
                        i = numChannels;
                    }
                }
            }
            k = entryIndex;
        }
        entryIndex = sSfxBanks[bankId][k].next;
    }

    for (i = 0; i < numChosenSfx; i++) {
        if (sSfxBanks[bankId][chosenSfx[i].entryIndex].state == 1) {
            sSfxBanks[bankId][chosenSfx[i].entryIndex].state = 2;
        } else if (sSfxBanks[bankId][chosenSfx[i].entryIndex].state == 4) {
            sSfxBanks[bankId][chosenSfx[i].entryIndex].state = 3;
        }
    }
    numChannels = sChannelsPerBank[sSfxChannelLayout][bankId];
    for (i = 0; i < numChannels; i++) {
        activeSfx = &sActiveSfx[bankId][i];
        needNewSfx = 0;
        if (activeSfx->entryIndex == 0xFF) {
            needNewSfx = 1;
        } else if (sSfxBanks[bankId][activeSfx->entryIndex].state == 4) {
            if (sSfxBanks[bankId][activeSfx->entryIndex].sfxId & SFX_FLAG_27) {
                Audio_RemoveSfxBankEntry(bankId, activeSfx->entryIndex);
            } else {
                sSfxBanks[bankId][activeSfx->entryIndex].state = 1;
            }
            needNewSfx = 1;
        } else if (sSfxBanks[bankId][activeSfx->entryIndex].state == 0) {
            activeSfx->entryIndex = 0xFF;
            needNewSfx = 1;
        } else {
            for (j = 0; j < numChannels; j++) {
                if (activeSfx->entryIndex == chosenSfx[j].entryIndex) {
                    chosenSfx[j].entryIndex = 0xFF;
                    j = numChannels;
                }
            }
            numChosenSfx--;
        }

        if (needNewSfx == 1) {
            for (j = 0; j < numChannels; j++) {
                chosenEntryIndex = chosenSfx[j].entryIndex;
                if ((chosenEntryIndex != 0xFF) && (sSfxBanks[bankId][chosenEntryIndex].state != 3)) {
                    for (k = 0; k < numChannels; k++) {
                        if (chosenEntryIndex == sActiveSfx[bankId][k].entryIndex) {
                            needNewSfx = 0;
                            k = numChannels;
                        }
                    }
                    if (needNewSfx == 1) {
                        activeSfx->entryIndex = chosenEntryIndex;
                        chosenSfx[j].entryIndex = 0xFF;
                        j = numChannels + 1;
                        numChosenSfx--;
                    }
                }
            }
            if (j == numChannels) {
                activeSfx->entryIndex = 0xFF;
            }
        }
    }
}

void Audio_PlayActiveSfx(u8 bankId) {
    u8 i;

    for (i = 0; i < sChannelsPerBank[sSfxChannelLayout][bankId]; i++) {
        u8 entryIndex = sActiveSfx[bankId][i].entryIndex;

        if (entryIndex != 0xFF) {
            SfxBankEntry* entry = &sSfxBanks[bankId][entryIndex];
            SequenceChannel* channel = gSeqPlayers[SEQ_PLAYER_SFX].channels[sCurSfxPlayerChannelIndex];
            s32 pad;

            if (entry->state == 2) {
                entry->channelIndex = sCurSfxPlayerChannelIndex;
                if (entry->sfxId & SFX_FLAG_19) {
                    sChannelMuteFlags |= 1 << sCurSfxPlayerChannelIndex;
                    Audio_SetSequenceFade(SEQ_PLAYER_BGM, 2, 64, 15);
                }
                Audio_SetSfxProperties(bankId, entryIndex, sCurSfxPlayerChannelIndex);
                AUDIOCMD_CHANNEL_SET_IO(SEQ_PLAYER_SFX, sCurSfxPlayerChannelIndex, 0, 1);
                AUDIOCMD_CHANNEL_SET_IO(SEQ_PLAYER_SFX, sCurSfxPlayerChannelIndex, 4, SFX_INDEX(entry->sfxId) & 0xFF);
                entry->state = 4;
            } else if ((u8) channel->seqScriptIO[7] == 0x80) {
                AUDIOCMD_CHANNEL_SET_IO(SEQ_PLAYER_SFX, sCurSfxPlayerChannelIndex, 7, 0);
                Audio_RemoveSfxBankEntry(bankId, entryIndex);
            } else if (entry->state == 3) {
                Audio_SetSfxProperties(bankId, entryIndex, sCurSfxPlayerChannelIndex);
                entry->state = 4;
            }
        }
        sCurSfxPlayerChannelIndex++;
    }
}

void Audio_KillSfxByBank(u8 bankId) {
    // LAudioTODO: Stub for now
    // return;

    SfxBankEntry* entry;
    u8 next = sSfxBanks[bankId][0].next;

    SfxBankEntry cmp;

    while (next != 0xFF) {
        entry = &sSfxBanks[bankId][next];
        if (entry->state >= 3) {
            AUDIOCMD_CHANNEL_SET_IO(2, entry->channelIndex, 0, 0);
        }
        if (entry->state != 0) {
            Audio_RemoveSfxBankEntry(bankId, next);
        }
        next = sSfxBanks[bankId][0].next;
    }
    cmp.sfxId = bankId << SFX_BANK_SHIFT;
    Audio_RemoveMatchingSfxRequests(0, &cmp);
}

void Audio_StopSfxByBankAndSource(u8 bankId, f32* sfxSource) {
    // LAudioTODO: Stub for now
    // return;

    SfxBankEntry* entry;
    u8 curIndex = 0;
    u8 nextIndex = sSfxBanks[bankId][0].next;

    while (nextIndex != 0xFF) {
        entry = &sSfxBanks[bankId][nextIndex];
        if (entry->xPos == sfxSource) {
            if (entry->state >= 3) {
                AUDIOCMD_CHANNEL_SET_IO(SEQ_PLAYER_SFX, entry->channelIndex, 0, 0);
            }
            if (entry->state != 0) {
                Audio_RemoveSfxBankEntry(bankId, nextIndex);
            }
        } else {
            curIndex = nextIndex;
        }
        nextIndex = sSfxBanks[bankId][curIndex].next;
    }
}

void Audio_KillSfxByBankAndSource(u8 bankId, f32* sfxSource) {
    // LAudioTODO: Stub for now
    // return;

    SfxBankEntry cmp;

    Audio_StopSfxByBankAndSource(bankId, sfxSource);
    cmp.sfxId = bankId << SFX_BANK_SHIFT;
    cmp.xPos = sfxSource;
    Audio_RemoveMatchingSfxRequests(1, &cmp);
}

void Audio_KillSfxBySource(f32* sfxSource) {
    // LAudioTODO: Stub for now
    // return;

    u8 i;
    SfxBankEntry cmp;

    for (i = 0; i < 5; i++) {
        Audio_StopSfxByBankAndSource(i, sfxSource);
    }
    cmp.xPos = sfxSource;
    Audio_RemoveMatchingSfxRequests(2, &cmp);
}

void Audio_KillSfxBySourceAndId(f32* sfxSource, u32 sfxId) {
    // LAudioTODO: Stub for now
    // return;

    u32 bankId = SFX_BANK(sfxId);
    u8 next = sSfxBanks[bankId][0].next;
    u8 current = 0;
    SfxBankEntry cmp;

    while (next != 0xFF) {
        if ((sSfxBanks[bankId][next].xPos == sfxSource) && (sSfxBanks[bankId][next].sfxId == sfxId)) {
            if (sSfxBanks[bankId][next].state >= 3) {
                AUDIOCMD_CHANNEL_SET_IO(SEQ_PLAYER_SFX, sSfxBanks[bankId][next].channelIndex, 0, 0);
            }
            if (sSfxBanks[bankId][next].state != 0) {
                Audio_RemoveSfxBankEntry(bankId, next);
            }
            next = 0xFF;
        } else {
            current = next;
        }
        if (next != 0xFF) {
            next = sSfxBanks[bankId][current].next;
        }
    }
    cmp.sfxId = sfxId;
    cmp.xPos = sfxSource;
    Audio_RemoveMatchingSfxRequests(3, &cmp);
}

void Audio_KillSfxByTokenAndId(u8 token, u32 sfxId) {
    // LAudioTODO: Stub for now
    // return;

    u32 bankId = SFX_BANK(sfxId);
    u8 next = sSfxBanks[bankId][0].next;
    u8 current = 0;
    SfxBankEntry cmp;

    while (next != 0xFF) {
        if ((sSfxBanks[bankId][next].token == token) && (sSfxBanks[bankId][next].sfxId == sfxId)) {
            if (sSfxBanks[bankId][next].state >= 3) {
                AUDIOCMD_CHANNEL_SET_IO(SEQ_PLAYER_SFX, sSfxBanks[bankId][next].channelIndex, 0, 0);
            }
            if (sSfxBanks[bankId][next].state != 0) {
                Audio_RemoveSfxBankEntry(bankId, next);
            }
        } else {
            current = next;
        }
        if (next != 0xFF) {
            next = sSfxBanks[bankId][current].next;
        }
    }
    cmp.token = token;
    cmp.sfxId = sfxId;
    Audio_RemoveMatchingSfxRequests(4, &cmp);
}

void Audio_KillSfxById(u32 sfxId) {
    // LAudioTODO: Stub for now
    // return;

    u32 bankId = SFX_BANK(sfxId);
    u8 next = sSfxBanks[bankId][0].next;
    u8 current = 0;
    SfxBankEntry cmp;

    while (next != 0xFF) {
        if (sfxId == sSfxBanks[bankId][next].sfxId) {
            if (sSfxBanks[bankId][next].state >= 3) {
                AUDIOCMD_CHANNEL_SET_IO(SEQ_PLAYER_SFX, sSfxBanks[bankId][next].channelIndex, 0, 0);
            }
            if (sSfxBanks[bankId][next].state != 0) {
                Audio_RemoveSfxBankEntry(bankId, next);
            }
        } else {
            current = next;
        }
        next = sSfxBanks[bankId][current].next;
    }
    cmp.sfxId = sfxId;
    Audio_RemoveMatchingSfxRequests(5, &cmp);
}

void Audio_ProcessSfxRequests(void) {
    while (sSfxRequestWriteIndex != sSfxRequestReadIndex) {
        Audio_ProcessSfxRequest();
        sSfxRequestReadIndex++;
    }
}

void Audio_SetSfxVolumeMod(u8 bankId, u8 target, u16 timer) {
    Modulation* scale = &sSfxVolumeMods[bankId];

    if (timer == 0) {
        timer++;
    }

    scale->target = target / 127.0f;
    scale->timer = timer;
    scale->step = (scale->value - scale->target) / timer;
}

void Audio_UpdateSfxVolumeMod(u8 bankId) {
    Modulation* scale = &sSfxVolumeMods[bankId];

    if (scale->timer != 0) {
        scale->timer--;
        if (scale->timer != 0) {
            scale->value -= scale->step;
        } else {
            scale->value = scale->target;
        }
    }
}

void Audio_PlayAllSfx(void) {
    u8 bankId;

    if (IS_SEQUENCE_CHANNEL_VALID(gSeqPlayers[SEQ_PLAYER_SFX].channels[0])) {
        sCurSfxPlayerChannelIndex = 0;
        for (bankId = 0; bankId < ARRAY_COUNT(sSfxBanks); bankId++) {
            Audio_ChooseActiveSfx(bankId);
            Audio_PlayActiveSfx(bankId);
            Audio_UpdateSfxVolumeMod(bankId);
        }
    }
}

void Audio_ResetSfx(void) {
    u8 i;
    u8 j;

    sSfxRequestWriteIndex = 0;
    sSfxRequestReadIndex = 0;
    sChannelMuteFlags = 0;
    for (i = 0; i < 5; i++) {
        sSfxBankListEnd[i] = 0;
        sSfxBankFreeListStart[i] = 1;
        sSfxBankUnused[i] = 0;
        sSfxBankMuted[i] = 0;
        sSfxVolumeMods[i].value = 1.0f;
        sSfxVolumeMods[i].timer = 0;
    }
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 8; j++) {
            sActiveSfx[i][j].entryIndex = 0xFF;
        }
    }
    for (i = 0; i < 5; i++) {
        sSfxBanks[i][0].prev = 0xFF;
        sSfxBanks[i][0].next = 0xFF;
        for (j = 1; j < 19; j++) {
            sSfxBanks[i][j].prev = j - 1;
            sSfxBanks[i][j].next = j + 1;
        }
        sSfxBanks[i][j].prev = j - 1;
        sSfxBanks[i][j].next = 0xFF;
    }
}

void Audio_PlayVoice(s32 msgId) {
    sCurrentVoiceId = sNextVoiceId = msgId;
    sSetNextVoiceId = true;
}

void Audio_PlayVoiceWithoutBGM(u32 msgId) {
    sMuteBgmForVoice = true;
    Audio_SetSequenceFade(SEQ_PLAYER_BGM, 2, 64, 15);
    Audio_PlayVoice(msgId);
}

void Audio_UpdateVoice(void) {
    s8 voiceBank;
    u16 voiceId;
    u8 voiceIdHi;
    u8 voiceIdLo;

    if (sSetNextVoiceId) {
        voiceBank = sNextVoiceId / 1000;
        voiceId = sNextVoiceId % 1000;
        voiceIdHi = voiceId / 256;
        voiceIdLo = voiceId % 256;

        AUDIOCMD_CHANNEL_SET_IO(SEQ_PLAYER_VOICE, 15, 0, 1);
        AUDIOCMD_CHANNEL_SET_IO(SEQ_PLAYER_VOICE, 15, 4, voiceBank);
        AUDIOCMD_CHANNEL_SET_IO(SEQ_PLAYER_VOICE, 15, 5, voiceIdHi);
        AUDIOCMD_CHANNEL_SET_IO(SEQ_PLAYER_VOICE, 15, 6, voiceIdLo);
        sSetNextVoiceId = false;
    } else if ((sMuteBgmForVoice) && (Audio_GetCurrentVoice() == 0)) {
        Audio_SetSequenceFade(SEQ_PLAYER_BGM, 2, 127, 15);
        sMuteBgmForVoice = false;
    }
}

void Audio_ClearVoice(void) {
    sCurrentVoiceId = 0;
    sNextVoiceId = 1;
    sSetNextVoiceId = true;
}

s32 Audio_GetCurrentVoice(void) {
    // LAudioTODO: Stub for now
    // return 0;

    if (!IS_SEQUENCE_CHANNEL_VALID(gSeqPlayers[SEQ_PLAYER_VOICE].channels[15])) {
        return 0;
    }
    if (gSeqPlayers[SEQ_PLAYER_VOICE].channels[15]->seqScriptIO[1] == 1) {
        if (sCurrentVoiceId < 4) {
            return 0;
        } else {
            return sCurrentVoiceId;
        }
    }
    return 0;
}

s32 Audio_GetCurrentVoiceStatus(void) {
    // LAudioTODO: Stub for now
    // return 1;
    
    SequenceChannel* channel = gSeqPlayers[SEQ_PLAYER_VOICE].channels[15];
    SequenceLayer* layer = channel->layers[0];

    if (!IS_SEQUENCE_CHANNEL_VALID(channel) || (layer == NULL) || (channel->seqScriptIO[1] != 1)) {
        return 0;
    }
    if (layer->note != NULL) {
        if (layer != layer->note->playbackState.parentLayer) {
            return 2;
        } else {
            return 1;
        }
    }
    return 0;
}

void Audio_SetUnkVoiceParam(u8 unkVoiceParam) {
    sUnkVoiceParam = unkVoiceParam;
}

void Audio_UpdateUnkVoiceParam(void) {
    if (sUnkVoiceParam != 0xFF) {
        AUDIOCMD_CHANNEL_SET_IO(SEQ_PLAYER_VOICE, 14, 0, sUnkVoiceParam);
        sUnkVoiceParam = 0xFF;
    }
}

void Audio_ResetPlayerFreqMods(void) {
    u8 i;
    u8 j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 5; j++) {
            sPlayerNoise[i].freqMod[j].value = 1.0f;
            sPlayerNoise[i].freqMod[j].timer = 0;
            sPlayerNoise[i].freqMod[j].boost = 0;
            sPlayerNoise[i].freqMod[j].brake = 0;
        }
    }
}

void Audio_UpdateArwingNoise(u8 playerId) {
    f32 freqMod;
    u8 i;

    if (gPlayer[playerId].sfx.boost) {
        sPlayerNoise[playerId].freqMod[0].target = 1.5f;
        sPlayerNoise[playerId].freqMod[0].timer = 18;
        sPlayerNoise[playerId].freqMod[0].step =
            (sPlayerNoise[playerId].freqMod[0].target - sPlayerNoise[playerId].freqMod[0].value) / 18;
        sPlayerNoise[playerId].freqMod[0].boost = true;
    } else if (sPlayerNoise[playerId].freqMod[0].boost) {
        sPlayerNoise[playerId].freqMod[0].boost = false;
        sPlayerNoise[playerId].freqMod[0].timer = 1;
    }
    if (gPlayer[playerId].sfx.brake) {
        sPlayerNoise[playerId].freqMod[0].target = 0.65f;
        sPlayerNoise[playerId].freqMod[0].timer = 20;
        sPlayerNoise[playerId].freqMod[0].step =
            (sPlayerNoise[playerId].freqMod[0].target - sPlayerNoise[playerId].freqMod[0].value) / 20;
        sPlayerNoise[playerId].freqMod[0].brake = true;
    } else if (sPlayerNoise[playerId].freqMod[0].brake) {
        sPlayerNoise[playerId].freqMod[0].brake = false;
        sPlayerNoise[playerId].freqMod[0].timer = 1;
    }
    if ((gPlayer[playerId].sfx.bank != 0) && (gPlayer[playerId].sfx.zRot < 45.0f)) {
        sPlayerNoise[playerId].freqMod[2].target = 1.25f;
        sPlayerNoise[playerId].freqMod[2].timer = 10;
        sPlayerNoise[playerId].freqMod[2].step =
            (sPlayerNoise[playerId].freqMod[2].target - sPlayerNoise[playerId].freqMod[2].value) / 10;
    }
    if (gPlayer[playerId].sfx.roll != 0) {
        AUDIO_PLAY_SFX(NA_SE_ROLLING_AIR, gPlayer[playerId].sfx.srcPos, playerId);
        sPlayerNoise[playerId].freqMod[1].target = 1.65f;
        sPlayerNoise[playerId].freqMod[1].timer = 8;
        sPlayerNoise[playerId].freqMod[1].step =
            (sPlayerNoise[playerId].freqMod[1].target - sPlayerNoise[playerId].freqMod[1].value) / 8;
    }
    if (ABS(gPlayer[playerId].sfx.yVel) > 2.0f) {
        sPlayerNoise[playerId].freqMod[3].target = 1.25f;
        sPlayerNoise[playerId].freqMod[3].timer = 15;
        sPlayerNoise[playerId].freqMod[3].step =
            (sPlayerNoise[playerId].freqMod[3].target - sPlayerNoise[playerId].freqMod[3].value) / 15;
        sPlayerNoise[playerId].freqMod[3].boost = true;
    } else if (sPlayerNoise[playerId].freqMod[3].boost) {
        sPlayerNoise[playerId].freqMod[3].boost = false;
        sPlayerNoise[playerId].freqMod[3].timer = 1;
    }
    if (sPlayerNoise[playerId].freqMod[4].timer == 0) {
        sPlayerNoise[playerId].freqMod[4].target = (((f32) (gAudioRandom % 0x10000) / 32768.0) * 0.15f) + 1.0f - 0.15f;
        sPlayerNoise[playerId].freqMod[4].timer = 16 + (gAudioRandom >> 27);
        sPlayerNoise[playerId].freqMod[4].step =
            (sPlayerNoise[playerId].freqMod[4].target - sPlayerNoise[playerId].freqMod[3].value) /
            sPlayerNoise[playerId].freqMod[4].timer;
    }
    for (i = 0; i < 5; i++) {
        if (sPlayerNoise[playerId].freqMod[i].timer != 0) {
            sPlayerNoise[playerId].freqMod[i].timer--;
            sPlayerNoise[playerId].freqMod[i].value += sPlayerNoise[playerId].freqMod[i].step;
            if ((sPlayerNoise[playerId].freqMod[i].timer == 0) && (sPlayerNoise[playerId].freqMod[i].target != 1.0f)) {
                sPlayerNoise[playerId].freqMod[i].target = 1.0f;
                sPlayerNoise[playerId].freqMod[i].timer = sPlayerNoiseTimes[i];
                sPlayerNoise[playerId].freqMod[i].step =
                    (1.0f - sPlayerNoise[playerId].freqMod[i].value) / sPlayerNoiseTimes[i];
            }
        }
    }
    freqMod = 1.0f;
    for (i = 0; i < 5; i++) {
        freqMod *= sPlayerNoise[playerId].freqMod[i].value;
    }
    if (freqMod >= 4.0f) {
        freqMod = 4.0f;
    }
    sPlayerNoise[playerId].totalMod = freqMod;
}

void Audio_UpdateLandmasterNoise(u8 playerId) {
    f32 freqMod;
    u8 i;

    if ((gPlayer[playerId].sfx.bank != 0) && (gPlayer[playerId].sfx.zRot < 45.0f)) {
        sPlayerNoise[playerId].freqMod[2].timer = 10;
        sPlayerNoise[playerId].freqMod[2].target = 1.25f;
        sPlayerNoise[playerId].freqMod[2].step = (1.25f - sPlayerNoise[playerId].freqMod[2].value) / 10;
    }
    if (gPlayer[playerId].sfx.roll != 0) {
        sPlayerNoise[playerId].freqMod[1].timer = 8;
        sPlayerNoise[playerId].freqMod[1].target = 1.65f;
        sPlayerNoise[playerId].freqMod[1].step = (1.65f - sPlayerNoise[playerId].freqMod[1].value) / 8;
    }
    if (ABS(gPlayer[playerId].sfx.yVel) > 2.0f) {
        sPlayerNoise[playerId].freqMod[3].target = 1.25f;
        sPlayerNoise[playerId].freqMod[3].timer = 15;
        sPlayerNoise[playerId].freqMod[3].boost = true;
        sPlayerNoise[playerId].freqMod[3].step = (1.25f - sPlayerNoise[playerId].freqMod[3].value) / 15;
    } else if (sPlayerNoise[playerId].freqMod[3].boost) {
        sPlayerNoise[playerId].freqMod[3].boost = false;
        sPlayerNoise[playerId].freqMod[3].timer = 1;
    }
    for (i = 0; i < 5; i++) {
        if (sPlayerNoise[playerId].freqMod[i].timer != 0) {
            sPlayerNoise[playerId].freqMod[i].timer--;
            sPlayerNoise[playerId].freqMod[i].value += sPlayerNoise[playerId].freqMod[i].step;
            if ((sPlayerNoise[playerId].freqMod[i].timer == 0) && (sPlayerNoise[playerId].freqMod[i].target != 1.0f)) {
                sPlayerNoise[playerId].freqMod[i].target = 1.0f;
                sPlayerNoise[playerId].freqMod[i].timer = sPlayerNoiseTimes[i];
                sPlayerNoise[playerId].freqMod[i].step =
                    (1.0f - sPlayerNoise[playerId].freqMod[i].value) / sPlayerNoiseTimes[i];
            }
        }
    }
    freqMod = 1.0f;
    for (i = 0; i < 5; i++) {
        freqMod *= sPlayerNoise[playerId].freqMod[i].value;
    }
    if (ABS(gPlayer[playerId].pos.y) < 600.0f) {
        freqMod += (gPlayer[playerId].pos.y / 600.0f);
    } else {
        freqMod += 1.0f;
    }
    if (gPlayer[playerId].baseSpeed > 25.0f) {
        freqMod += 0.5f;
    } else if (gPlayer[playerId].baseSpeed < 5.0f) {
        freqMod -= 0.5f;
    } else {
        freqMod += (gPlayer[playerId].baseSpeed - 15.0f) * 0.05f;
    }
    if (freqMod > 2.0f) {
        freqMod = 2.0f;
    }
    sPlayerNoise[playerId].totalMod = freqMod;
}

void Audio_UpdateBlueMarineNoise(u8 playerId) {
    u8 i;
    f32 freqMod;

    if ((gPlayer[playerId].sfx.bank != 0) && (gPlayer[playerId].sfx.zRot < 45.0f)) {
        sPlayerNoise[playerId].freqMod[2].timer = 10;
        sPlayerNoise[playerId].freqMod[2].target = 1.1f;
        sPlayerNoise[playerId].freqMod[2].step = (1.1f - sPlayerNoise[playerId].freqMod[2].value) / 10;
    }
    if (gPlayer[playerId].sfx.roll != 0) {
        AUDIO_PLAY_SFX(NA_SE_MAR_ROLLING_AIR, gPlayer[playerId].sfx.srcPos, playerId);
        sPlayerNoise[playerId].freqMod[1].timer = 8;
        sPlayerNoise[playerId].freqMod[1].target = 1.2f;
        sPlayerNoise[playerId].freqMod[1].step = (1.2f - sPlayerNoise[playerId].freqMod[1].value) / 8;
    }
    if (ABS(gPlayer[playerId].sfx.yVel) > 2.0f) {
        sPlayerNoise[playerId].freqMod[3].timer = 15;
        sPlayerNoise[playerId].freqMod[3].boost = true;
        sPlayerNoise[playerId].freqMod[3].target = 1.12f;
        sPlayerNoise[playerId].freqMod[3].step = (1.12f - sPlayerNoise[playerId].freqMod[3].value) / 15;
    } else if (sPlayerNoise[playerId].freqMod[3].boost) {
        sPlayerNoise[playerId].freqMod[3].boost = false;
        sPlayerNoise[playerId].freqMod[3].timer = 1;
    }
    for (i = 0; i < 5; i++) {
        if (sPlayerNoise[playerId].freqMod[i].timer != 0) {
            sPlayerNoise[playerId].freqMod[i].timer--;
            sPlayerNoise[playerId].freqMod[i].value += sPlayerNoise[playerId].freqMod[i].step;
            if ((sPlayerNoise[playerId].freqMod[i].timer == 0) && (sPlayerNoise[playerId].freqMod[i].target != 1.0f)) {
                sPlayerNoise[playerId].freqMod[i].target = 1.0f;
                sPlayerNoise[playerId].freqMod[i].timer = sPlayerNoiseTimes[i];
                sPlayerNoise[playerId].freqMod[i].step =
                    (1.0f - sPlayerNoise[playerId].freqMod[i].value) / sPlayerNoiseTimes[i];
            }
        }
    }
    freqMod = 1.0f;

    for (i = 0; i < 5; i++) {
        freqMod *= sPlayerNoise[playerId].freqMod[i].value;
    }
    if (freqMod > 2.0f) {
        freqMod = 2.0f;
    }
    sPlayerNoise[playerId].totalMod = freqMod;
}

void Audio_UpdatePlayerFreqMod(void) {
    u8 playerId;

#ifdef AVOID_UB
    for (playerId = 0; playerId < gCamCount; playerId++) {
#else
    for (playerId = 0; playerId < 4; playerId++) {
#endif
        switch (sPlayerNoise[playerId].form) {
            case FORM_ARWING:
                Audio_UpdateArwingNoise(playerId);
                sPlayerNoise[playerId].totalMod *=
                    Audio_UpdateDopplerShift(gPlayer[playerId].sfx.srcPos, gPlayer[playerId].sfx.srcVel, 150.0f,
                                             &sPlayerNoise[playerId].dopplerShift);
                break;
            case FORM_LANDMASTER:
                Audio_UpdateLandmasterNoise(playerId);
                break;
            case FORM_BLUE_MARINE:
                Audio_UpdateBlueMarineNoise(playerId);
                break;
            case FORM_NONE:
                break;
        }
    }
}

void Audio_UpdatePlayerReverb(void) {
    u8 playerId;

    for (playerId = 0; playerId < 4; playerId++) {
        if ((sPlayerNoise[playerId].form == FORM_ARWING) && (gPlayer[playerId].sfx.levelType == LEVELTYPE_PLANET)) {
            if (gPlayer[playerId].pos.y < 150.0f) {
                sPlayerNoise[playerId].reverbAdd = (150.0f - gPlayer[playerId].pos.y) * 0.53f;
            } else {
                sPlayerNoise[playerId].reverbAdd = 0;
            }
        }
    }
}

void Audio_UpdatePlayerNoise(void) {
    Audio_UpdatePlayerFreqMod();
    Audio_UpdatePlayerReverb();
}

void Audio_ResetVoicesAndPlayers(void) {
    u8 playerId;

    Audio_ResetPlayerFreqMods();
    for (playerId = 0; playerId < 4; playerId++) {
        sPlayerNoise[playerId].form = FORM_NONE;
        sPlayerNoise[playerId].reverbAdd = 0;
        sPlayerNoise[playerId].totalMod = 1.0f;
        sPlayerNoise[playerId].dopplerShift = 1.0f;
        sBombState[playerId] = 0;
        sBombStartFrame[playerId] = 0;
    }
    sSfxFreqMod = 1.0f;
    sSfxVolMod = 1.0f;
    sNextVoiceId = 0;
    sCurrentVoiceId = 0;
    sSetNextVoiceId = 0;
    sMuteBgmForVoice = 0;
    sPlaylistIndex = 0xFF;
}

void Audio_ProcessPlaylist(void) {
    PlaylistCmd* cmd;
    u32 temp;
    u32 temp2;
    u32 temp1;
    u32 temp5;

    if (sPlaylistIndex != 0xFF) {
        if (sPlaylistTimer == 0) {
            cmd = &sPlaylists[sPlaylistIndex][sPlaylistCmdIndex];
            switch (cmd->opCode) {
                case 0:
                    Audio_PlaySequence(cmd->seqPlayId, cmd->seqId & 0xFF, 0, cmd->bgmParam);
                    sPlaylistTimer = sPlaylists[sPlaylistIndex][sPlaylistCmdIndex].timer;
                    sPlaylistCmdIndex++;
                    break;
                case 1:
                    SEQCMD_STOP_SEQUENCE_ALT(cmd->seqPlayId, cmd->fadeoutTime);
                    sPlaylistTimer = sPlaylists[sPlaylistIndex][sPlaylistCmdIndex].timer;
                    sPlaylistCmdIndex++;
                    break;
                case 2:
                    Audio_PlaySequenceDistorted(cmd->seqPlayId, cmd->seqId & 0xFF, 1121, 25, cmd->bgmParam);
                    sPlaylistTimer = sPlaylists[sPlaylistIndex][sPlaylistCmdIndex].timer;
                    sPlaylistCmdIndex++;
                    break;
                case 3:
                    Audio_PlayFanfare(cmd->seqId & 0xFF, 20, 10, 10);
                    sPlaylistTimer = sPlaylists[sPlaylistIndex][sPlaylistCmdIndex].timer;
                    sPlaylistCmdIndex++;
                    break;
                case 0xFF:
                    sPlaylistIndex = 0xFF;
                    break;
            }
        } else {
            sPlaylistTimer--;
        }
    }
}

void Audio_AnalyzeFrequencies(f32* buffer0, f32* buffer1, s32 length, f32* buffer2) {
    f32 temp_ft0;
    f32 var_fs0;
    f32* buff0fromStart;
    f32* buf2half2;
    f32* buf2half3;
    f32* buff1half1;
    f32* buff0FromEnd;
    f32* buff1half2;
    s32 half;
    s32 i;
    s32 size;

    size = 1 << length;
    half = size >> 1;

    // Initialize buffer 2 if it is the wrong size for this calculation
    if (size != (s32) buffer2[0]) {
        buf2half2 = &buffer2[half];
        buf2half3 = &buf2half2[half];
        var_fs0 = 0.0f;
        temp_ft0 = D_PI / (2 * size);
        for (i = 0; i < half; i++) {
            *buf2half2++ = (__cosf(var_fs0) - __sinf(var_fs0)) * 0.707107f; // approx 1/sqrt(2)
            *buf2half3++ = (__cosf(var_fs0) + __sinf(var_fs0)) * 0.707107f; // approx 1/sqrt(2)
            var_fs0 += temp_ft0;
        }
    }

    buff0fromStart = buffer0;
    buff0FromEnd = &buffer0[size - 1];
    buff1half1 = buffer1;
    buff1half2 = &buffer1[half];

    // Copy even entries of buffer 0 into the first half of buffer 1. Copy odd entries into the second half in reverse
    // order
    for (i = 0; i < half; i++) {
        *buff1half1++ = *buff0fromStart;
        *buff1half2++ = *buff0FromEnd;
        buff0fromStart += 2;
        buff0FromEnd -= 2;
    }

    // reset the buffer pointers
    buff0FromEnd = &buffer0[size - 1];
    buff0fromStart = buffer0;
    buf2half2 = &buffer2[half];
    buf2half3 = &buf2half2[half];
    buff1half1 = buffer1;

    // FFT buffer 1 using buffer 2
    AudioSynth_HartleyTransform(buffer1, length, buffer2);

    // handle i = 0 case
    buff0fromStart[0] = buff1half1[0];
    buff0fromStart[half] = buff1half1[half];

    // advance buffer pointers
    buf2half2++;
    buf2half3++;
    buff0fromStart++;
    buff1half1++;

    // second half of buffer 1 in reverse order this time
    buff1half2 = &buffer1[size - 1];

    // convert to real amplitudes
    for (i = 1; i < half; i++) {
        *buff0fromStart++ = (*buf2half2 * *buff1half1) + (*buf2half3 * *buff1half2);
        *buff0FromEnd-- = (*buf2half3 * *buff1half1) - (*buf2half2 * *buff1half2);
        buff1half1++;
        buf2half3++;
        buf2half2++;
        buff1half2--;
    }
}

u8* Audio_UpdateFrequencyAnalysis(void) {
    s32 fmax;
    s32 i1;
    s32 fmin;
    s32 i2;
    s32 i3;
    s32 fbin;
    s16* aiData;
    s32 pad;
    static s32 sFreqBins[] = {
        0,  1,  2,  3,  4,  6,  7,  8,   9,   10,  11,  12,  14,  16,  19,  22,
        26, 31, 37, 44, 54, 68, 88, 108, 138, 163, 188, 208, 222, 234, 242, 246,
    };
    static f32 sFreqGain = 17.0f;
    static f32 sFreqAmplitudes[32] = {
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    };

    Audio_ProcessPlaylist();
    // clang-format off
    aiData = gAiBuffers[gCurAiBuffIndex];\
    for(i3 = 0; i3 < 256; i3++) {\
        sAudioAnalyzerData[i3] = *aiData++;
    }
    // clang-format on
    Audio_AnalyzeFrequencies(sAudioAnalyzerData, sAnalyzerBuffer1, 8, sAnalyzerBuffer2);
    fmin = 0;
    for (i1 = 0; i1 < 32; i1++) {
        fmax = sFreqBins[i1] + 1;
        for (fbin = fmin; fbin < fmax; fbin++) {
            if (sAudioAnalyzerData[fbin] > 0.0f) {
                sNewFreqAmplitudes[i1] += sAudioAnalyzerData[fbin];
            } else {
                sNewFreqAmplitudes[i1] -= sAudioAnalyzerData[fbin];
            }
        }
        fmin = fbin;
    }
    for (i2 = 0; i2 < 32; i2++) {
        sNewFreqAmplitudes[i2] /= 8;
    }
    for (i3 = 0; i3 < 32; i3++) {
        sNewFreqAmplitudes[i3] = (sNewFreqAmplitudes[i3] / 32768.0f) * sFreqGain;
        if (sNewFreqAmplitudes[i3] > 1.0f) {
            sNewFreqAmplitudes[i3] = 1.0f;
        }
        sFreqAmplitudes[i3] = sFreqAmplitudes[i3] * 0.75f + 0.25f * sNewFreqAmplitudes[i3];
        sFreqAnalyzerBars[i3] = sFreqAmplitudes[i3] * 255.0f;
    }
    return sFreqAnalyzerBars;
}

void Audio_StartPlayerNoise(u8 playerId) {
    u32 sfxId = NA_SE_NONE;

    sPlayerNoise[playerId].form = gPlayer[playerId].sfx.form;
    Audio_ResetPlayerFreqMods();
    switch (sPlayerNoise[playerId].form) {
        case FORM_ARWING:
            if (gPlayer[playerId].sfx.levelType == LEVELTYPE_SPACE) {
                sfxId = NA_SE_ARWING_ENGIN_SPC;
            } else {
                sfxId = NA_SE_ARWING_ENGIN_GRD;
            }
            break;
        case FORM_LANDMASTER:
            sfxId = NA_SE_TANK_ENGIN;
            break;
        case FORM_BLUE_MARINE:
            sfxId = NA_SE_MARINE_ENGINE00;
            Audio_PlaySfx(NA_SE_SUBMARINE_ATM, gPlayer[playerId].sfx.srcPos, playerId, &gDefaultMod, &gDefaultMod,
                          &sPlayerNoise[playerId].reverbAdd);
            break;
    }
    if (sfxId != NA_SE_NONE) {
        Audio_PlaySfx(sfxId, gPlayer[playerId].sfx.srcPos, playerId, &sPlayerNoise[playerId].totalMod, &gDefaultMod,
                      &sPlayerNoise[playerId].reverbAdd);
    }
}

void Audio_StopPlayerNoise(u8 playerId) {
    u32 sfxId = NA_SE_NONE;

    switch (sPlayerNoise[playerId].form) {
        case FORM_ARWING:
            if (gPlayer[playerId].sfx.levelType == LEVELTYPE_SPACE) {
                sfxId = NA_SE_ARWING_ENGIN_SPC;
            } else {
                sfxId = NA_SE_ARWING_ENGIN_GRD;
            }
            Audio_KillSfxBySourceAndId(gPlayer[playerId].sfx.srcPos, NA_SE_SPLASH_LEVEL_S);
            break;
        case FORM_LANDMASTER:
            sfxId = NA_SE_TANK_ENGIN;
            break;
        case FORM_BLUE_MARINE:
            sfxId = NA_SE_MARINE_ENGINE00;
            Audio_KillSfxBySourceAndId(gPlayer[playerId].sfx.srcPos, NA_SE_SUBMARINE_ATM);
            break;
    }
    sPlayerNoise[playerId].form = FORM_NONE;
    if (sfxId != NA_SE_NONE) {
        Audio_KillSfxBySourceAndId(gPlayer[playerId].sfx.srcPos, sfxId);
    }
}

void Audio_InitBombSfx(u8 playerId, u8 type) {
    sBombStartFrame[playerId] = sAudioFrameCounter;
    switch (type) {
        case 1:
            sBombFreqMod[playerId] = 1.0f;
            sBombType[playerId] = 1;
            break;
        case 2:
            sBombFreqMod[playerId] = 1.5f;
            sBombType[playerId] = 2;
            break;
        default:
        case 0:
            sBombFreqMod[playerId] = 0.75f;
            sBombType[playerId] = 0;
            break;
    }
    if (sBombState[playerId] != 1) {
        Audio_PlaySfx(NA_SE_BOMB_CHARGE, gPlayer[playerId].sfx.srcPos, playerId, &sBombFreqMod[playerId], &gDefaultMod,
                      &sPlayerNoise[playerId].reverbAdd);
        sBombState[playerId] = 1;
    }
}

void Audio_PlayBombFlightSfx(u8 playerId, f32* sfxSource) {
    if (sBombState[playerId] != 0) {
        switch (sBombType[playerId]) {
            case 1:
                sBombFreqMod[playerId] = 1.2f;
                break;
            case 2:
                sBombFreqMod[playerId] = 1.5f;
                break;
            default:
            case 0:
                sBombFreqMod[playerId] = 1.0f;
                break;
        }
        Audio_KillSfxBySourceAndId(gPlayer[playerId].sfx.srcPos, NA_SE_BOMB_CHARGE);
        Audio_PlaySfx(NA_SE_SMART_BOMB_SHOT, sfxSource, playerId, &sBombFreqMod[playerId], &gDefaultMod,
                      &sPlayerNoise[playerId].reverbAdd);
        sBombState[playerId] = 2;
    }
}

void Audio_PlayBombExplodeSfx(u8 playerId, f32* sfxSource) {
    u32 sfxId;

    if (sBombState[playerId] != 0) {
        switch (sBombType[playerId]) {
            case 1:
                sfxId = NA_SE_BOMB_EXPLODE1;
                break;
            case 2:
                sfxId = NA_SE_BOMB_EXPLODE2;
                break;
            default:
            case 0:
                sfxId = NA_SE_BOMB_EXPLODE0;
                break;
        }
        Audio_KillSfxByTokenAndId(playerId, NA_SE_SMART_BOMB_SHOT);
        AUDIO_PLAY_SFX(sfxId, sfxSource, playerId);
        sBombState[playerId] = 0;
    }
}

void Audio_StartEngineNoise(f32* sfxSource) {
    u32 sfxId = (gPlayer[0].sfx.levelType == LEVELTYPE_SPACE) ? NA_SE_ARWING_ENGINE_FS : NA_SE_ARWING_ENGINE_FG;

    AUDIO_PLAY_SFX(sfxId, sfxSource, 0);
}

void Audio_StopEngineNoise(f32* sfxSource) {
    u32 sfxId = (gPlayer[0].sfx.levelType == LEVELTYPE_SPACE) ? NA_SE_ARWING_ENGINE_FS : NA_SE_ARWING_ENGINE_FG;

    Audio_KillSfxBySourceAndId(sfxSource, sfxId);
}

void Audio_SetSfxSpeedModulation(f32 vel) {
    f32 speed = ABS(vel);

    if (speed < 6.0f) {
        speed = 6.0f;
    } else if (speed > 30.0f) {
        speed = 30.0f;
    }

    sSfxFreqMod = ((speed - 18.0f) / 24.0f) + 1.0f;
}

void Audio_SetTransposeAndPlaySfx(f32* sfxSource, u32 sfxId, u8 semitones) {
    f32 semitoneMods[] = {
        1.0f, 1.059f, 1.122f, 1.189f, 1.26f, 1.335f, 1.414f, 1.498f, 1.587f, 1.682f, 1.782f, 1.888f, 2.0f,
    };

    if (semitones > 12) {
        semitones = 12;
    }
    Audio_SetModulationAndPlaySfx(sfxSource, sfxId, semitoneMods[semitones]);
}

void Audio_SetModulationAndPlaySfx(f32* sfxSource, u32 sfxId, f32 freqMod) {
    sSfxFreqMod = freqMod;
    Audio_PlaySfx(sfxId, sfxSource, 0, &sSfxFreqMod, &gDefaultMod, &gDefaultReverb);
}

void Audio_PlaySfxModulated(f32* sfxSource, u32 sfxId) {
    Audio_PlaySfx(sfxId, sfxSource, 0, &sSfxFreqMod, &sSfxVolMod, &gDefaultReverb);
}

void Audio_SetSfxMapModulation(u8 fMod) {
    if (fMod < 12) {
        sSfxFreqMod = (fMod / 11.0f) + 0.5f;
    } else {
        sSfxFreqMod = 1.5f;
    }
}

void Audio_SetHeatAlarmParams(u8 shields, u8 heightParam) {
    // height param is (s32) height / 100 - 1, clamped to [0, 5]
    u8 alarmVolume;
    u8 heightVolume;

    // modifies tempo
    AUDIOCMD_CHANNEL_SET_IO(SEQ_PLAYER_SFX, 9, 2, 8 + (shields >> 2));
    AUDIOCMD_CHANNEL_SET_IO(SEQ_PLAYER_SFX, 10, 2, 8 + (shields >> 2));
    AUDIOCMD_CHANNEL_SET_IO(SEQ_PLAYER_SFX, 11, 2, 8 + (shields >> 2));

    // modifies frequency
    AUDIOCMD_CHANNEL_SET_IO(SEQ_PLAYER_SFX, 9, 1, 19 - (heightParam * 3));
    AUDIOCMD_CHANNEL_SET_IO(SEQ_PLAYER_SFX, 10, 1, 19 - (heightParam * 3));
    AUDIOCMD_CHANNEL_SET_IO(SEQ_PLAYER_SFX, 11, 1, 19 - (heightParam * 3));

    alarmVolume = 68 - (shields >> 3);
    heightVolume = 80 - (heightParam * 10);
    if (heightVolume > alarmVolume) {
        alarmVolume = heightVolume;
    }
    AUDIOCMD_CHANNEL_SET_IO(SEQ_PLAYER_SFX, 9, 3, alarmVolume);
    AUDIOCMD_CHANNEL_SET_IO(SEQ_PLAYER_SFX, 10, 3, alarmVolume);
    AUDIOCMD_CHANNEL_SET_IO(SEQ_PLAYER_SFX, 11, 3, alarmVolume);
}

void Audio_PlayEventSfx(f32* sfxSource, u16 eventSfxId) {
    if ((sEventSfx[eventSfxId] & SFX_BANK_MASK) != (SFX_BANK_SYSTEM << SFX_BANK_SHIFT)) {
        AUDIO_PLAY_SFX(sEventSfx[eventSfxId], sfxSource, 0);
    } else {
        AUDIO_PLAY_SFX(sEventSfx[eventSfxId], gDefaultSfxSource, 0);
    }
}

void Audio_StopEventSfx(f32* sfxSource, u16 eventSfxId) {
    if ((sEventSfx[eventSfxId] & SFX_BANK_MASK) != (SFX_BANK_SYSTEM << SFX_BANK_SHIFT)) {
        Audio_KillSfxBySourceAndId(sfxSource, sEventSfx[eventSfxId]);
    } else {
        Audio_KillSfxBySourceAndId(gDefaultSfxSource, sEventSfx[eventSfxId]);
    }
}

void Audio_SetEnvSfxReverb(s8 reverb) {
    sEnvReverb = reverb;
}

void Audio_SetBgmParam(s8 bgmParam) {
    SEQCMD_SET_SEQPLAYER_IO(SEQ_PLAYER_BGM, 0, bgmParam);
}

void Audio_PlaySequence(u8 seqPlayId, u16 seqId, u8 fadeinTime, u8 bgmParam) {
    //seqId &= 0xFF;
    SEQCMD_SET_SEQPLAYER_IO(seqPlayId, 0, bgmParam);
    SEQCMD_PLAY_SEQUENCE(seqPlayId, fadeinTime, 0, seqId);
}

void Audio_PlayFanfare(u16 seqId, u8 bgmVolume, u8 bgmFadeoutTime, u8 bgmFadeinTime) {
    if (Audio_GetActiveSeqId(SEQ_PLAYER_BGM) != NA_BGM_PLAYER_DOWN) {
        Audio_SetSequenceFade(SEQ_PLAYER_BGM, 1, bgmVolume, bgmFadeoutTime);
        SEQCMD_SETUP_RESTORE_SEQPLAYER_VOLUME(SEQ_PLAYER_FANFARE, SEQ_PLAYER_BGM, bgmFadeinTime);
        SEQCMD_PLAY_SEQUENCE(SEQ_PLAYER_FANFARE, 0, 0, seqId);
    }
}

void Audio_PlayDeathSequence(void) {
    u8 i;

    if (sAudioSpecId == AUDIOSPEC_24) {
        Audio_ClearVoice();
        Audio_PlayMapMenuSfx(0);
        AUDIO_PLAY_SFX(NA_SE_ARWING_EXPLOSION, gDefaultSfxSource, 4);
        SEQCMD_SET_SEQPLAYER_VOLUME(SEQ_PLAYER_BGM, 5, 30);
        SEQCMD_SETUP_RESTORE_SEQPLAYER_VOLUME(SEQ_PLAYER_FANFARE, SEQ_PLAYER_BGM, 30);
        SEQCMD_PLAY_SEQUENCE(SEQ_PLAYER_FANFARE, 0, 0, NA_BGM_PLAYER_DOWN);
    } else {
        for (i = 0; i < 5; i++) {
            Audio_KillSfxByBank(i);
        }
        AUDIOCMD_GLOBAL_UNMUTE(true);
        AUDIO_PLAY_SFX(NA_SE_ARWING_EXPLOSION, gDefaultSfxSource, 4);
        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 0);
        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 0);
        SEQCMD_PLAY_SEQUENCE(SEQ_PLAYER_BGM, 0, 0, NA_BGM_PLAYER_DOWN);
    }
}

void Audio_PlayPauseSfx(u8 active) {
    if (active) {
        AUDIO_PLAY_SFX(NA_SE_PAUSE_ON, gDefaultSfxSource, 4);
        AUDIOCMD_GLOBAL_MUTE();
    } else {
        AUDIO_PLAY_SFX(NA_SE_PAUSE_ON, gDefaultSfxSource, 4);
        AUDIOCMD_GLOBAL_UNMUTE(false);
    }
}

void Audio_PlayMapMenuSfx(u8 active) {
    if (active) {
        AUDIO_PLAY_SFX(NA_SE_MAP_WINDOW_OPEN, gDefaultSfxSource, 4);
        AUDIOCMD_GLOBAL_MUTE();
    } else {
        AUDIO_PLAY_SFX(NA_SE_MAP_WINDOW_CLOSE, gDefaultSfxSource, 4);
        AUDIOCMD_GLOBAL_UNMUTE(false);
    }
}

void Audio_RestoreVolumeSettings(u8 audioType) {
    s8 volume = ((sVolumeSettings[audioType] * 127) / 99) % 128U;
    u8 i;

    switch (audioType) {
        case AUDIO_TYPE_MUSIC:
            Audio_SetSequenceFade(SEQ_PLAYER_BGM, 0, volume, 1);
            Audio_SetSequenceFade(SEQ_PLAYER_FANFARE, 0, volume, 1);
            break;
        case AUDIO_TYPE_SFX:
            for (i = 0; i < 15; i++) {
                AUDIOCMD_CHANNEL_SET_VOL(SEQ_PLAYER_SFX, (u32) i, volume / 127.0f);
            }
            break;
        case AUDIO_TYPE_VOICE:
            AUDIOCMD_CHANNEL_SET_VOL(SEQ_PLAYER_VOICE, 15, volume / 127.0f);
            break;
    }
}

void Audio_SetVolume(u8 audioType, u8 volume) {    
    if (volume > 99) {
        volume = 99;
    }
    sVolumeSettings[audioType] = volume;
    Audio_RestoreVolumeSettings(audioType);
}

void Audio_PlaySoundTest(u8 enable) {
    switch (enable) {
        case false:
            AUDIO_PLAY_BGM(NA_BGM_SELECT);
            Audio_PlayVoice(1);
            Audio_KillSfxById(NA_SE_VOLUME_TEST);
            Audio_KillSfxById(NA_SE_ARWING_ENGIN_GRD);
            break;
        case true:
            AUDIO_PLAY_BGM(NA_BGM_VOLUME_TEST);
            Audio_PlayVoice(2);
            AUDIO_PLAY_SFX(NA_SE_VOLUME_TEST, gDefaultSfxSource, 0);
            AUDIO_PLAY_SFX(NA_SE_ARWING_ENGIN_GRD, gDefaultSfxSource, 0);
            break;
    }
}

void Audio_PlaySequenceDistorted(u8 seqPlayId, u16 seqId, u16 distortion, u8 fadeinTime, u8 unused) {
    u8 tempoDistortion = (distortion / 10);

    Audio_PlaySequence(seqPlayId, seqId & ~SEQ_FLAG, 0, -1);
    SEQCMD_SET_SEQPLAYER_FREQ(seqPlayId, fadeinTime, distortion);
    SEQCMD_SCALE_TEMPO(seqPlayId, fadeinTime, tempoDistortion);
}

void Audio_PlaySoundTestTrack(u8 trackNumber) {
    u16 seqId;
    u8 bgmParam;

    if ((trackNumber >= 45) && (trackNumber < 50)) {
        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 1);
        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 1);
        sPlaylistIndex = trackNumber - 45;
        sPlaylistCmdIndex = 0;
        sPlaylistTimer = 0;
    } else if (trackNumber >= 50) {
        AUDIO_PLAY_SFX(NA_SE_ERROR, gDefaultSfxSource, 4);
    } else {
        sPlaylistIndex = 0xFF;
        seqId = sSoundTestTracks[trackNumber].seqId & 0xFF;
        bgmParam = sSoundTestTracks[trackNumber].bgmParam;
        SEQCMD_STOP_SEQUENCE(D_800C5E70 ^ 1, 5);
        Audio_PlaySequence(D_800C5E70, seqId, 0, bgmParam);
        D_800C5E70 ^= 1;
    }
}

void Audio_FadeOutAll(u8 fadeoutTime) {
    SEQCMD_SET_SEQPLAYER_VOLUME(SEQ_PLAYER_BGM, fadeoutTime, 0);
    SEQCMD_SET_SEQPLAYER_VOLUME(SEQ_PLAYER_FANFARE, fadeoutTime, 0);
    SEQCMD_SET_SEQPLAYER_VOLUME(SEQ_PLAYER_SFX, fadeoutTime, 0);
    SEQCMD_SET_SEQPLAYER_VOLUME(SEQ_PLAYER_VOICE, fadeoutTime, 0);
}

void Audio_KillAllSfx(void) {
    u8 i;

    for (i = 0; i < 5; i++) {
        Audio_KillSfxByBank(i);
    }
}

void Audio_SetAudioSpec(u8 unused, u16 specParam) {
    u8 sfxChannelLayout = ((specParam & 0xFF00) >> 8);
    u8 specId = specParam & 0xFF;

    SEQCMD_RESET_AUDIO_HEAP(sfxChannelLayout, specId);
}

// unused
void Audio_PlayBgm(u16 seqId) {
    SEQCMD_PLAY_SEQUENCE(SEQ_PLAYER_BGM, 1, 0, seqId);
}

void Audio_InitSounds(void) {
    Audio_ResetVoicesAndPlayers();
    Audio_ResetSfxChannelState();
    Audio_ResetActiveSequencesAndVolume();
    Audio_ResetSfx();
    Audio_StartSequence(SEQ_PLAYER_VOICE, NA_BGM_VO, -1, 1);
    Audio_StartSequence(SEQ_PLAYER_SFX, NA_BGM_SE, -1, 10);
}

void Audio_RestartSeqPlayers(void) {
    s32 pad1;
    s32 pad2;
    u16 fadeIn = 1;

    Audio_StartSequence(SEQ_PLAYER_VOICE, NA_BGM_VO, -1, 1);
    if (sAudioSpecId == AUDIOSPEC_AQ) {
        fadeIn = 360;
    } else if (sAudioSpecId < AUDIOSPEC_23) {
        fadeIn = 90;
    }
    Audio_StartSequence(SEQ_PLAYER_SFX, NA_BGM_SE, -1, fadeIn);
    Audio_LoadInstruments();
    Audio_LoadAquasSequence();
    SEQCMD_SET_SEQPLAYER_VOLUME(SEQ_PLAYER_SFX, 0, 127);
    SEQCMD_SET_SEQPLAYER_VOLUME(SEQ_PLAYER_VOICE, 0, 127);
    AudioThread_ScheduleProcessCmds();
    AUDIOCMD_GLOBAL_STOP_AUDIOCMDS();
    AUDIOCMD_GLOBAL_STOP_AUDIOCMDS();
    AUDIOCMD_GLOBAL_STOP_AUDIOCMDS();
    Audio_RestoreVolumeSettings(AUDIO_TYPE_MUSIC);
    Audio_RestoreVolumeSettings(AUDIO_TYPE_SFX);
    Audio_RestoreVolumeSettings(AUDIO_TYPE_VOICE);
}

void Audio_StartReset(u8 oldSpecId) {
    if (oldSpecId == AUDIOSPEC_16) {
        if ((sAudioSpecId == AUDIOSPEC_22) || (sAudioSpecId == AUDIOSPEC_23)) {
            sAudioResetStatus = AUDIORESET_BLOCK;
        }
    } else if ((oldSpecId == AUDIOSPEC_28) && (sAudioSpecId == AUDIOSPEC_23)) {
        sAudioResetStatus = AUDIORESET_BLOCK;
    } else {
        sAudioResetStatus = AUDIORESET_WAIT;
    }
    // LTODO: Workaround for the crash after quitting the Practice mode
    sAudioResetStatus = AUDIORESET_WAIT;

    AUDIOCMD_GLOBAL_UNMUTE(true);
    Audio_ResetVoicesAndPlayers();
    Audio_ResetSfxChannelState();
    Audio_ResetActiveSequences();
    Audio_ResetSfx();
}

void Audio_Update(void) {
    if (Audio_HandleReset() == AUDIORESET_READY) {
        Audio_ProcessSfxRequests();
        Audio_ProcessSeqCmds();
        Audio_PlayAllSfx();
        Audio_UpdatePlayerNoise();
        Audio_UpdateVoice();
        Audio_UpdateUnkVoiceParam();
        Audio_UpdateActiveSequences();
        Audio_UpdateDelayedSeqCmds();
        AudioThread_ScheduleProcessCmds();
    }
    sAudioFrameCounter++;
}
