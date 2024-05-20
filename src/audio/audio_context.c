#include "sys.h"
#include "sf64audio_provisional.h"

u64 gAudioContextStart[2];
SynthesisReverb gSynthReverbs[4];
u8 sAudioContextPad10[0x10]; // 0x10
u16 D_8014C1B0;
s8 D_8014C1B2;
s8 gNumSynthReverbs;
s16 D_8014C1B4;
NoteSubEu* gNoteSubsEu;
// 0x4
AudioAllocPool gSessionPool;
AudioAllocPool gInitPool;
AudioAllocPool gMiscPool;
u8 gAudioContextPad20[0x20]; // 0x20
AudioAllocPool gCachePool;
AudioAllocPool gPersistentCommonPool;
AudioAllocPool gTemporaryCommonPool;
AudioCache gSeqCache;        // seqCache
AudioCache gFontCache;       // fontCache
AudioCache gSampleBankCache; // sampleBankCache
PermanentCache gPermanentPool;
AudioSampleCache gPersistentSampleCache;
// 0x4
AudioSampleCache gTemporarySampleCache;
// 0x4
AudioSessionPoolSplit gSessionPoolSplit;
AudioCachePoolSplit gCachePoolSplit;
AudioCommonPoolSplit gPersistentCommonPoolSplit;
// 0x4
AudioCommonPoolSplit gTemporaryCommonPoolSplit;
// 0x4
u8 gSampleFontLoadStatus[64];
u8 gFontLoadStatus[64];
u8 gSeqLoadStatus[256];
volatile u8 gResetStatus;
u8 gAudioSpecId;
s32 gResetFadeoutFramesLeft;
u8 sAudioContextPad1000[0x1000]; // 0x1000 gap
Note* gNotes;
// 0x4
SequencePlayer gSeqPlayers[4];
SequenceChannel gSeqChannels[48];
SequenceLayer gSeqLayers[64];
SequenceChannel gSeqChannelNone;
AudioListItem gLayerFreeList;
NotePool gNoteFreeLists;
Sample* gUsedSamples[128];
AudioPreloadReq gPreloadSampleStack[128];
s32 gNumUsedSamples;
s32 gPreloadSampleStackTop;
AudioAsyncLoad gAsyncLoads[16];
OSMesgQueue gExternalLoadQueue;
OSMesg gExternalLoadMsg[16];
OSMesgQueue gPreloadSampleQueue;
OSMesg gPreloadSampleMsg[16];
OSMesgQueue gCurAudioFrameDmaQueue;
OSMesg gCurAudioFrameDmaMsg[64];
OSIoMesg gCurAudioFrameDmaIoMsgBuf[64];
OSMesgQueue gSyncDmaQueue;
OSMesg gSyncDmaMsg[1];
// 0x4
OSIoMesg gSyncDmaIoMsg;
SampleDma gSampleDmas[0x100];
u32 gSampleDmaCount;
u32 gSampleDmaListSize1;
s32 D_80155A50;
// 0x4
u8 gSampleDmaReuseQueue1[0x100];
u8 gSampleDmaReuseQueue2[0x100];
u8 gSampleDmaReuseQueue1RdPos;
u8 gSampleDmaReuseQueue2RdPos;
u8 gSampleDmaReuseQueue1WrPos;
u8 gSampleDmaReuseQueue2WrPos;
AudioTable* gSequenceTable;
AudioTable* gSoundFontTable;
AudioTable* gSampleBankTable;
u8* gSeqFontTable;
s16 gNumSequences;
SoundFont* gSoundFontList;
// 0x4
AudioBufferParameters gAudioBufferParams;
s32 gSampleDmaBuffSize;
s32 gMaxAudioCmds;
s32 gNumNotes;
s16 gMaxTempo;
s8 gAudioSoundMode;
volatile s32 gAudioTaskCountQ;
s32 gCurAudioFrameDmaCount;
s32 gAudioTaskIndexQ;
s32 gCurAiBuffIndex;
Acmd* gAbiCmdBuffs[2];
Acmd* gCurAbiCmdBuffer;
SPTask* gAudioCurTask;
SPTask gAudioRspTasks[2];
f32 gMaxTempoTvTypeFactors;
s32 gRefreshRate;
s16* gAiBuffers[3];
s16 gAiBuffLengths[3];
u32 gAudioRandom;
u32 D_80155D88;
volatile u32 gResetTimer;

u64 gAudioContextEnd[2];

static ReverbSettings D_800C74D0[2] = { { 1, 0x30, 0x3000, 0, 0 }, { 1, 0x40, 0x4000, 0xD000, 0x3000 } };
static ReverbSettings D_800C74E0[2] = { { 1, 0x30, 0x3000, 0, 0 }, { 1, 0x38, 0x6400, 0x1000, 0x1000 } };
static ReverbSettings D_800C74F0[2] = { { 1, 0x30, 0x3000, 0, 0 }, { 1, 0x40, 0x4000, 0, 0 } };
static ReverbSettings D_800C7500[2] = { { 1, 0x30, 0x3000, 0, 0 }, { 1, 0x30, 0x5000, 0, 0 } };
static ReverbSettings D_800C7510[2] = { { 1, 0x30, 0x3000, 0, 0 }, { 1, 0x40, 0x6000, 0, 0 } };
static ReverbSettings D_800C7520[2] = { { 1, 0x30, 0x3000, 0, 0 }, { 1, 0x30, 0x3000, 0, 0 } };
static ReverbSettings D_800C7530[2] = { { 1, 0x30, 0x3000, 0, 0 }, { 1, 0x30, 0x5800, 0, 0 } };
static ReverbSettings D_800C7540[2] = { { 1, 0x30, 0x3000, 0, 0 }, { 1, 0x30, 0x5000, 0, 0 } };
static ReverbSettings D_800C7550[2] = { { 1, 0x30, 0x3000, 0, 0 }, { 1, 0x30, 0x3000, 0, 0 } };
static ReverbSettings D_800C7560[2] = { { 1, 0x30, 0x3000, 0, 0 }, { 1, 0x40, 0x6000, 0, 0 } };
static ReverbSettings D_800C7570[2] = { { 1, 0x30, 0x3000, 0, 0 }, { 1, 0x30, 0x3000, 0, 0 } };
static ReverbSettings D_800C7580[2] = { { 1, 0x30, 0x3000, 0, 0 }, { 1, 0x40, 0x4000, 0, 0 } };
static ReverbSettings D_800C7590[2] = { { 1, 0x30, 0x3000, 0, 0 }, { 2, 0x28, 0x5800, 0, 0 } };
static ReverbSettings D_800C75A0[2] = { { 1, 0x30, 0x3000, 0, 0 }, { 1, 0x30, 0x3000, 0, 0 } };
static ReverbSettings D_800C75B0[2] = { { 1, 0x30, 0x3000, 0, 0 }, { 1, 0x38, 0x5000, 0, 0 } };
static ReverbSettings D_800C75C0[3] = {
    { 1, 0x30, 0x3000, 0, 0 },
    { 1, 0x38, 0x3000, 0, 0 },
    { 2, 0x48, 0x6000, 0xC000, 0x4000 },
};
static ReverbSettings D_800C75D8[2] = { { 1, 0x30, 0x3000, 0, 0 }, { 1, 0x30, 0x3000, 0, 0 } };
static ReverbSettings D_800C75E8[2] = { { 1, 0x30, 0x3000, 0, 0 }, { 1, 0x30, 0x3000, 0, 0 } };
static ReverbSettings D_800C75F8[2] = { { 1, 0x30, 0x3000, 0, 0 }, { 1, 0x30, 0x3000, 0, 0 } };
static ReverbSettings D_800C7608[2] = { { 1, 0x30, 0x3000, 0, 0 }, { 1, 0x30, 0x3000, 0, 0 } };
static ReverbSettings D_800C7618[2] = { { 1, 0x30, 0x3000, 0, 0 }, { 1, 0x30, 0x3000, 0, 0 } };
static ReverbSettings D_800C7628[2] = { { 1, 0x30, 0x3000, 0, 0 }, { 1, 0x30, 0x3000, 0, 0 } };
static ReverbSettings D_800C7638[2] = { { 1, 0x30, 0x3000, 0, 0 }, { 1, 0x30, 0x6800, 0, 0 } };
static ReverbSettings D_800C7648[2] = { { 1, 0x30, 0x3000, 0, 0 }, { 1, 0x18, 0x3000, 0, 0 } };
static ReverbSettings D_800C7658[2] = { { 1, 0x30, 0x3000, 0, 0 }, { 2, 0x18, 0x3000, 0, 0 } };
static ReverbSettings D_800C7668[2] = { { 1, 0x30, 0x3000, 0, 0 }, { 1, 0x18, 0x3000, 0, 0 } };
static ReverbSettings D_800C7678[2] = { { 1, 0x30, 0x3000, 0, 0 }, { 1, 0x30, 0x3000, 0, 0 } };
static ReverbSettings D_800C7688[2] = { { 1, 0x30, 0x3000, 0, 0 }, { 1, 0x30, 0x3000, 0, 0 } };
static ReverbSettings D_800C76A8[] = {
    // unused?
    { 1, 0x40, 0x4FFF, 0, 0 },
    { 1, 0x30, 0x4FFF, 0, 0 },
    { 1, 0x30, 0x4FFF, 0, 0 },
    { 1, 0x30, 0x4FFF, 0, 0 },
};
AudioSpec gAudioSpecs[] = {
    /*  0 */ { 32000, 2, 22, ARRAY_COUNT(D_800C74D0), D_800C74D0, 0x7FFF, 0x1200, 0x1100, 0, 0x5000, 0x2400, 0, 0x1B000,
               0x35000 },
    /*  1 */
    { 32000, 2, 22, ARRAY_COUNT(D_800C74E0), D_800C74E0, 0x7FFF, 0x1200, 0x1100, 0, 0x5000, 0x2400, 0, 0x1B000,
      0x35000 },
    /*  2 */
    { 32000, 2, 22, ARRAY_COUNT(D_800C74F0), D_800C74F0, 0x7FFF, 0x1200, 0x1100, 0, 0x5000, 0x2400, 0, 0x1B000,
      0x35000 },
    /*  3 */
    { 32000, 2, 22, ARRAY_COUNT(D_800C7500), D_800C7500, 0x7FFF, 0x1200, 0x1100, 0, 0x5000, 0x2400, 0, 0x1B000,
      0x35000 },
    /*  4 */
    { 32000, 2, 22, ARRAY_COUNT(D_800C7510), D_800C7510, 0x7FFF, 0x1200, 0x1100, 0, 0x5000, 0x2400, 0, 0x1B000,
      0x35000 },
    /*  5 */
    { 32000, 2, 22, ARRAY_COUNT(D_800C7520), D_800C7520, 0x7FFF, 0x1200, 0x1100, 0, 0x5000, 0x2400, 0, 0x1B000,
      0x35000 },
    /*  6 */
    { 32000, 2, 22, ARRAY_COUNT(D_800C7530), D_800C7530, 0x7FFF, 0x1200, 0x1100, 0, 0x5000, 0x2400, 0, 0x1B000,
      0x35000 },
    /*  7 */
    { 32000, 2, 22, ARRAY_COUNT(D_800C7540), D_800C7540, 0x7FFF, 0x1200, 0x1100, 0, 0x5000, 0x2400, 0, 0x1B000,
      0x35000 },
    /*  8 */
    { 32000, 2, 22, ARRAY_COUNT(D_800C7550), D_800C7550, 0x7FFF, 0x1200, 0x1100, 0, 0x5000, 0x2400, 0, 0x1B000,
      0x35000 },
    /*  9 */
    { 32000, 2, 22, ARRAY_COUNT(D_800C7560), D_800C7560, 0x7FFF, 0x1200, 0x1100, 0, 0x5000, 0x2400, 0, 0x1B000,
      0x35000 },
    /* 10 */
    { 32000, 2, 22, ARRAY_COUNT(D_800C7570), D_800C7570, 0x7FFF, 0x1200, 0x1100, 0, 0x5000, 0x2400, 0, 0x1B000,
      0x35000 },
    /* 11 */
    { 32000, 2, 22, ARRAY_COUNT(D_800C7580), D_800C7580, 0x7FFF, 0x1200, 0x1100, 0, 0x5000, 0x2400, 0, 0x1B000,
      0x35000 },
    /* 12 */
    { 32000, 1, 22, ARRAY_COUNT(D_800C7590), D_800C7590, 0x7FFF, 0x1200, 0x1100, 0, 0x5000, 0x2400, 0, 0x2B000,
      0x35000 },
    /* 13 */
    { 32000, 2, 22, ARRAY_COUNT(D_800C75A0), D_800C75A0, 0x7FFF, 0x1200, 0x1100, 0, 0x5000, 0x2400, 0, 0x1B000,
      0x35000 },
    /* 14 */
    { 32000, 2, 22, ARRAY_COUNT(D_800C75B0), D_800C75B0, 0x7FFF, 0x1200, 0x1100, 0, 0x5000, 0x2400, 0, 0x1B000,
      0x35000 },
    /* 15 */
    { 32000, 2, 22, ARRAY_COUNT(D_800C75C0), D_800C75C0, 0x7FFF, 0x1200, 0x1100, 0, 0x5000, 0x2400, 0, 0x1B000,
      0x34000 },
    /* 16 */
    { 32000, 2, 22, ARRAY_COUNT(D_800C75D8), D_800C75D8, 0x7FFF, 0x1200, 0x1100, 0, 0x5000, 0x2400, 0, 0x1B000,
      0x35000 },
    /* 17 */
    { 32000, 2, 22, ARRAY_COUNT(D_800C75E8), D_800C75E8, 0x7FFF, 0x1200, 0x1100, 0, 0x5000, 0x2400, 0, 0x1B000,
      0x35000 },
    /* 18 */
    { 32000, 2, 22, ARRAY_COUNT(D_800C75F8), D_800C75F8, 0x7FFF, 0x1200, 0x1100, 0, 0x5000, 0x2400, 0, 0x1B000,
      0x35000 },
    /* 19 */
    { 32000, 2, 22, ARRAY_COUNT(D_800C7608), D_800C7608, 0x7FFF, 0x1200, 0x1100, 0, 0x5000, 0x2400, 0, 0x1B000,
      0x35000 },
    /* 20 */
    { 32000, 2, 22, ARRAY_COUNT(D_800C7618), D_800C7618, 0x7FFF, 0x1200, 0x1100, 0, 0x5000, 0x2400, 0, 0x1B000,
      0x35000 },
    /* 21 */
    { 32000, 2, 32, ARRAY_COUNT(D_800C7628), D_800C7628, 0x7FFF, 0x1200, 0x1100, 0, 0x5000, 0x2400, 0, 0x1B000,
      0x00000 },
    /* 22 */
    { 32000, 1, 32, ARRAY_COUNT(D_800C7638), D_800C7638, 0x7FFF, 0x1200, 0x1100, 0, 0x5000, 0x2400, 0, 0x1B000,
      0x00000 },
    /* 23 */
    { 32000, 1, 32, ARRAY_COUNT(D_800C7648), D_800C7648, 0x7FFF, 0x1200, 0xA000, 0, 0x5B00, 0x1D00, 0, 0x00000,
      0x00000 },
    /* 24 */
    { 32000, 1, 22, ARRAY_COUNT(D_800C7658), D_800C7658, 0x7FFF, 0x1200, 0x1100, 0, 0x5000, 0x2400, 0, 0x00000,
      0x60000 },
    /* 25 */
    { 32000, 2, 22, ARRAY_COUNT(D_800C7668), D_800C7668, 0x7FFF, 0x1200, 0x1100, 0, 0x5000, 0x2400, 0, 0x1B000,
      0x00000 },
    /* 26 */
    { 32000, 2, 22, ARRAY_COUNT(D_800C7678), D_800C7678, 0x7FFF, 0x1200, 0x1100, 0, 0x5000, 0x2400, 0, 0x1B000,
      0x00000 },
    /* 27 */
    { 32000, 2, 32, ARRAY_COUNT(D_800C7688), D_800C7688, 0x7FFF, 0x1200, 0x1100, 0, 0x5000, 0x2400, 0, 0x1B000,
      0x00000 },
    /* 28 */
    { 32000, 2, 22, ARRAY_COUNT(D_800C74D0), D_800C74D0, 0x7FFF, 0x1200, 0x1100, 0, 0x5000, 0x2400, 0, 0x1B000,
      0x35000 },
};
s32 D_800C7C28 = 0x20000000; // unused?
s16 gSeqTicksPerBeat = 0x30;
s32 gAudioHeapSize = 0xAFE00;
s32 gInitPoolSize = 0x26000;
u32 gPermanentPoolSize = 0x21000;
u16 gSequenceMedium = 0;
u16 gSoundFontMedium = 0;
u16 gSampleBankMedium = 0;
