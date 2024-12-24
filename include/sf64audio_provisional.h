/**
 * This file is provisional, some of the structs need to be corrected, and others might be unused
 * This file is only meant to be used as reference to help audio decompilation
 */

#ifndef SF64_AUDIO_H
#define SF64_AUDIO_H

#include <libultra/types.h>
#include "sf64audio_external.h"

typedef void (*AudioCustomUpdateFunction)(void);

#define REFRESH_RATE_PAL 50
#define REFRESH_RATE_MPAL 60
#define REFRESH_RATE_NTSC 60

// Small deviation parameters used in estimating the max tempo
// It is unclear why these vary by region, and aren't all just 1
#define REFRESH_RATE_DEVIATION_PAL 1.001521f
#define REFRESH_RATE_DEVIATION_MPAL 0.99276f
#define REFRESH_RATE_DEVIATION_NTSC 1.00278f

#define AUDIO_MK_CMD(b0, b1, b2, b3) \
    ((((b0) &0xFF) << 0x18) | (((b1) &0xFF) << 0x10) | (((b2) &0xFF) << 0x8) | (((b3) &0xFF) << 0))

#define NO_LAYER ((SequenceLayer*) (-1))

// Also known as "Pulses Per Quarter Note" or "Tatums Per Beat"
#define SEQTICKS_PER_BEAT 48

#define IS_SEQUENCE_CHANNEL_VALID(ptr) ((uintptr_t) (ptr) != (uintptr_t) &gSeqChannelNone)
#define SEQ_NUM_CHANNELS 16
#define SEQ_IO_VAL_NONE -1

#define MAX_CHANNELS_PER_BANK 3

#define MUTE_BEHAVIOR_3 (1 << 3)           // prevent further noteSubEus from playing
#define MUTE_BEHAVIOR_4 (1 << 4)           // stop something in seqLayer scripts
#define MUTE_BEHAVIOR_SOFTEN (1 << 5)      // lower volume, by default to half
#define MUTE_BEHAVIOR_STOP_NOTES (1 << 6)  // prevent further notes from playing
#define MUTE_BEHAVIOR_STOP_SCRIPT (1 << 7) // stop processing sequence/channel scripts

#define ADSR_DISABLE 0
#define ADSR_HANG -1
#define ADSR_GOTO -2
#define ADSR_RESTART -3

// size of a single sample point
#define SAMPLE_SIZE sizeof(s16)

// Samples are processed in groups of 16 called a "frame"
#define SAMPLES_PER_FRAME ADPCMFSIZE

// The length of one left/right channel is 12 frames
#define DMEM_1CH_SIZE (12 * SAMPLES_PER_FRAME * SAMPLE_SIZE)
// Both left and right channels
#define DMEM_2CH_SIZE (2 * DMEM_1CH_SIZE)

#define AIBUF_LEN (170 * SAMPLES_PER_FRAME)  // number of samples
#define AIBUF_SIZE (AIBUF_LEN * SAMPLE_SIZE) // number of bytes

// Filter sizes
#define FILTER_SIZE (8 * SAMPLE_SIZE)
#define FILTER_BUF_PART1 (8 * SAMPLE_SIZE)
#define FILTER_BUF_PART2 (8 * SAMPLE_SIZE)

// Must be the same amount of samples as copied by aDuplicate() (audio microcode)
#define WAVE_SAMPLE_COUNT 64

#define AUDIO_RELOCATED_ADDRESS_START K0BASE

#define AUDIOLOAD_SYNC 0
#define AUDIOLOAD_ASYNC 1

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    /* 0 */ ADSR_STATE_DISABLED,
    /* 1 */ ADSR_STATE_INITIAL,
    /* 2 */ ADSR_STATE_START_LOOP,
    /* 3 */ ADSR_STATE_LOOP,
    /* 4 */ ADSR_STATE_FADE,
    /* 5 */ ADSR_STATE_HANG,
    /* 6 */ ADSR_STATE_DECAY,
    /* 7 */ ADSR_STATE_RELEASE,
    /* 8 */ ADSR_STATE_SUSTAIN
} AdsrStatus;

typedef enum {
    /* 0 */ MEDIUM_RAM,
    /* 1 */ MEDIUM_UNK,
    /* 2 */ MEDIUM_CART,
    /* 3 */ MEDIUM_DISK_DRIVE
} SampleMedium;

typedef enum {
    /* 0 */ CODEC_ADPCM, // 16 2-byte samples (32 bytes) compressed into 4-bit samples (8 bytes) + 1 header byte
    /* 1 */ CODEC_S8,    // 16 2-byte samples (32 bytes) compressed into 8-bit samples (16 bytes)
    /* 2 */ CODEC_S16_INMEMORY,
    /* 3 */ CODEC_SMALL_ADPCM, // 16 2-byte samples (32 bytes) compressed into 2-bit samples (4 bytes) + 1 header byte
    /* 4 */ CODEC_REVERB,
    /* 5 */ CODEC_S16
} SampleCodec;

typedef enum {
    /*  0 */ SAMPLES_SFX,
    /*  1 */ SAMPLES_MAP,
    /*  2 */ SAMPLES_VOICE,
    /*  3 */ SAMPLES_INST,
    /*  4 */ SAMPLES_MAX,
    /* -1 */ SAMPLES_NONE = 255,
} SampleBank;

#define SAMPLES_NONE_U 255U

typedef enum {
    /* 0 */ SEQUENCE_TABLE,
    /* 1 */ FONT_TABLE,
    /* 2 */ SAMPLE_TABLE
} AudioTableType;

typedef enum {
    /* 0 */ CACHE_TEMPORARY,
    /* 1 */ CACHE_PERSISTENT,
    /* 2 */ CACHE_EITHER,
    /* 3 */ CACHE_PERMANENT
} AudioCacheType;

typedef enum {
    /* 0 */ CACHEPOLICY_0,
    /* 1 */ CACHEPOLICY_1,
    /* 2 */ CACHEPOLICY_2,
    /* 3 */ CACHEPOLICY_3,
    /* 4 */ CACHEPOLICY_4,
} AudioCachePolicy;

typedef enum {
    /* 0 */ LOAD_STATUS_NOT_LOADED,  // the entry data is not loaded
    /* 1 */ LOAD_STATUS_IN_PROGRESS, // the entry data is being loaded asynchronously
    /* 2 */ LOAD_STATUS_COMPLETE,    // the entry data is loaded, it may be discarded if not stored persistently, and
                                     // either no longer in use, or the memory is needed for something else
    /* 3 */ LOAD_STATUS_DISCARDABLE, // the entry data is loaded, and can be discarded
    /* 4 */ LOAD_STATUS_MAYBE_DISCARDABLE, // only for font table entries, like COMPLETE but prefer discarding it over a
                                           // COMPLETE entry
    /* 5 */ LOAD_STATUS_PERMANENTLY_LOADED // the entry data is loaded in the permanent pool, it won't be discarded
} AudioLoadStatus;

typedef enum {
    /* 0 */ SLOW_LOAD_WAITING,
    /* 1 */ SLOW_LOAD_START,
    /* 2 */ SLOW_LOAD_LOADING,
    /* 3 */ SLOW_LOAD_DONE
} SlowLoadState;

typedef enum {
    /* 0 */ SLOW_LOAD_STATUS_0,
    /* 1 */ SLOW_LOAD_STATUS_1,
    /* 2 */ SLOW_LOAD_STATUS_2,
    /* 3 */ SLOW_LOAD_STATUS_3
} SlowLoadStatus;

typedef enum AudioResetStatus {
    /* 0 */ AUDIORESET_READY,
    /* 1 */ AUDIORESET_WAIT,
    /* 2 */ AUDIORESET_BLOCK,
} AudioResetStatus;

typedef s32 (*DmaHandler)(OSPiHandle* handle, OSIoMesg* mb, s32 direction);

struct Note;
struct NotePool;
struct SequenceChannel;
struct SequenceLayer;

typedef struct AudioListItem {
    // A node in a circularly linked list. Each node is either a head or an item:
    // - Items can be either detached (prev = NULL), or attached to a list.
    //   'value' points to something of interest.
    // - List heads are always attached; if a list is empty, its head points
    //   to itself. 'count' contains the size of the list.
    // If the list holds notes, 'pool' points back to the pool where it lives.
    // Otherwise, that member is NULL.
    /* 0x00 */ struct AudioListItem* prev;
    /* 0x04 */ struct AudioListItem* next;
    /* 0x08 */ union {
        void* value; // either Note* or SequenceLayer*
        s32 count;
    } u;
    /* 0x0C */ struct NotePool* pool;
} AudioListItem; // size = 0x10

typedef struct NotePool {
    /* 0x00 */ AudioListItem disabled;
    /* 0x10 */ AudioListItem decaying;
    /* 0x20 */ AudioListItem releasing;
    /* 0x30 */ AudioListItem active;
} NotePool; // size = 0x40

// Pitch sliding by up to one octave in the positive direction. Negative
// direction is "supported" by setting extent to be negative. The code
// exterpolates exponentially in the wrong direction in that case, but that
// doesn't prevent seqplayer from doing it, AFAICT.
typedef struct {
    /* 0x00 */ u8 mode; // bit 0x80 denotes something; the rest are an index 0-5
    /* 0x04 */ f32 cur;
    /* 0x08 */ f32 speed;
    /* 0x0C */ f32 extent;
} Portamento; // size = 0x10

typedef struct {
    /* 0x0 */ s16 delay;
    /* 0x2 */ s16 arg;
} EnvelopePoint; // size = 0x4

typedef struct {
    /* 0x00 */ u32 start;
    /* 0x04 */ u32 end;
    /* 0x08 */ u32 count;
    /* 0x10 */ s16 predictorState[16]; // only exists if count != 0. 8-byte aligned
} AdpcmLoop;                          // size = 0x30 or 0x10, 0x8 aligned

typedef struct {
    /* 0x00 */ s32 order;
    /* 0x04 */ s32 numPredictors;
    /* 0x08 */ s16* book; // size 8 * order * numPredictors.
} AdpcmBook; // size >= 8, 0x8 aligned

typedef struct {
    /* 0x00 */ u32 codec : 4;  // The state of compression or decompression
    /* 0x00 */ u32 medium : 2; // Medium where sample is currently stored
    /* 0x00 */ u32 unk_bit26 : 1;
    /* 0x00 */ u32 isRelocated : 1; // Has the sample header been relocated (offsets to pointers)
    /* 0x01 */ u32 size : 24;       // Size of the sample
    /* 0x04 */ u8* sampleAddr;      // Raw sample data. Offset from the start of the sample bank or absolute address to
                                    // either rom or ram
    /* 0x08 */ AdpcmLoop*
        loop; // Adpcm loop parameters used by the sample. Offset from the start of the sound font / pointer to ram
    /* 0x0C */ AdpcmBook*
        book; // Adpcm book parameters used by the sample. Offset from the start of the sound font / pointer to ram
} Sample;     // size = 0x10

typedef struct {
    /* 0x00 */ Sample* sample;
    /* 0x04 */ f32 tuning; // frequency modulation factor
} TunedSample;// size = 0x8

typedef struct {
    /* 0x00 */ u8 isRelocated; // have the envelope and all samples been relocated (offsets to pointers)
    /* 0x01 */ u8 normalRangeLo;
    /* 0x02 */ u8 normalRangeHi;
    /* 0x03 */ u8 adsrDecayIndex; // index used to obtain adsr decay rate from adsrDecayTable
    /* 0x04 */ EnvelopePoint* envelope;
    /* 0x08 */ TunedSample lowPitchTunedSample;
    /* 0x10 */ TunedSample normalPitchTunedSample;
    /* 0x18 */ TunedSample highPitchTunedSample;
} Instrument; // size = 0x20

typedef struct {
    /* 0x00 */ u8 adsrDecayIndex; // index used to obtain adsr decay rate from adsrDecayTable
    /* 0x01 */ u8 pan;
    /* 0x02 */ u8 isRelocated; // have tunedSample.sample and envelope been relocated (offsets to pointers)
    /* 0x04 */ TunedSample tunedSample;
    /* 0x0C */ EnvelopePoint* envelope;
} Drum; // size = 0x10

typedef struct {
    /* 0x00 */ TunedSample tunedSample;
} SoundEffect; // size = 0x08

/**
 * Stores parsed information from soundfont data
 */
typedef struct {
    /* 0x00 */ u8 numInstruments;
    /* 0x01 */ u8 numDrums;
    /* 0x02 */ u8 sampleBankId1;
    /* 0x03 */ u8 sampleBankId2;
    /* 0x04 */ Instrument** instruments;
    /* 0x08 */ Drum** drums;
} SoundFont; // size = 0x10

typedef struct {
    /* 0x00 */ s16 numSamplesAfterDownsampling; // never read
    /* 0x02 */ s16 chunkLen;                    // never read
    /* 0x04 */ s16* toDownsampleLeft;
    /* 0x08 */ s16* toDownsampleRight;          // data pointed to by left and right are adjacent in memory
    /* 0x0C */ s32 startPos;                    // start pos in ring buffer
    /* 0x10 */ s16 lengthA;                     // first length in ring buffer (from startPos, at most until end)
    /* 0x12 */ s16 lengthB;                     // second length in ring buffer (from pos 0)
} ReverbRingBufferItem;                         // size = 0x14

typedef struct {
    /* 0x000 */ u8 resampleFlags;
    /* 0x001 */ u8 useReverb;
    /* 0x002 */ u8 framesToIgnore;
    /* 0x003 */ u8 curFrame;
    /* 0x004 */ u8 downsampleRate;
    /* 0x005 */ s8 unk_05;
    /* 0x006 */ u16 windowSize;
    /* 0x008 */ u16 decayRatio; // determines how much reverb persists
    /* 0x00A */ u16 unk_0A;
    /* 0x00C */ u16 leakRtL;
    /* 0x00E */ u16 leakLtR;
    /* 0x010 */ s32 nextRingBufPos;
    /* 0x014 */ s32 unk_20;
    /* 0x018 */ s32 bufSizePerChan;
    /* 0x01C */ s16* leftRingBuf;
    /* 0x020 */ s16* rightRingBuf;
    /* 0x024 */ void* unk_30;
    /* 0x028 */ void* unk_34;
    /* 0x02C */ void* unk_38;
    /* 0x030 */ void* unk_3C;
    /* 0x034 */ ReverbRingBufferItem items[2][10];
    char pad[0x10];
} SynthesisReverb; // size = 0x1D4

typedef struct {
    /* 0x00 */ u8* pc; // program counter
    /* 0x04 */ u8* stack[4];
    /* 0x14 */ u8 remLoopIters[4]; // remaining loop iterations
    /* 0x18 */ u8 depth;
    /* 0x19 */ s8 value;
} SeqScriptState; // size = 0x1C

// Also known as a Group, according to debug strings.
typedef struct {
    /* 0x000 */ u8 enabled : 1;
    /* 0x000 */ u8 finished : 1;
    /* 0x000 */ u8 muted : 1;
    /* 0x000 */ u8 seqDmaInProgress : 1;
    /* 0x000 */ u8 fontDmaInProgress : 1;
    /* 0x000 */ u8 recalculateVolume : 1;
    /* 0x000 */ u8 stopScript : 1;
    /* 0x000 */ u8 applyBend : 1;
    /* 0x001 */ u8 state;
    /* 0x002 */ u8 noteAllocPolicy;
    /* 0x003 */ u8 muteBehavior;
    /* 0x004 */ u8 seqId;
    /* 0x005 */ u8 defaultFont;
    /* 0x006 */ u8 unk_06[1];
    /* 0x007 */ s8 unk_07[1];    // indexed like an array, but that can't be
    /* 0x008 */ u16 tempo;       // seqTicks per minute
    /* 0x00A */ u16 tempoAcc;    // tempo accumulation, used in a discretized algorithm to apply tempo.
    /* 0x00C */ u16 tempoChange; // Used to adjust the tempo without altering the base tempo.
    /* 0x00E */ s16 transposition;
    /* 0x010 */ u16 delay;
    /* 0x012 */ u16 fadeTimer; // in ticks
    /* 0x014 */ u16 fadeTimerUnkEu;
    /* 0x018 */ u8* seqData;
    /* 0x01C */ f32 fadeVolume;
    /* 0x020 */ f32 fadeVelocity;
    /* 0x024 */ f32 volume;
    /* 0x028 */ f32 muteVolumeMod;
    /* 0x02C */ f32 fadeVolumeMod;
    /* 0x030 */ f32 appliedFadeVolume;
    // /* 0x034 */ f32 bend;
    /* 0x034 */ struct SequenceChannel* channels[SEQ_NUM_CHANNELS];
    /* 0x074 */ SeqScriptState scriptState;
    /* 0x090 */ u8* shortNoteVelocityTable;
    /* 0x094 */ u8* shortNoteGateTimeTable;
    /* 0x098 */ NotePool notePool;
    /* 0x0D8 */ s32 skipTicks;
    /* 0x0DC */ u32 scriptCounter;
    /* 0x0E0 */ char
        padE4[0x6C]; // unused struct members for sequence/sound font dma management, according to sm64 decomp
} SequencePlayer;    // size = 0x14C

typedef struct {
    /* 0x0 */ u8 decayIndex; // index used to obtain adsr decay rate from adsrDecayTable
    /* 0x1 */ u8 sustain;
    /* 0x4 */ EnvelopePoint* envelope;
} AdsrSettings; // size = 0x8

typedef struct {
    /* 0x00 */ union {
        struct A {
            /* 0x00 */ u8 unused : 1;
            /* 0x00 */ u8 hang : 1;
            /* 0x00 */ u8 decay : 1;
            /* 0x00 */ u8 release : 1;
            /* 0x00 */
        } s;
        /* 0x00 */ u8 asByte;
    } action;
    /* 0x01 */ u8 state;
    /* 0x02 */ s16 envIndex;
    /* 0x04 */ s16 delay;
    /* 0x08 */ f32 sustain;
    /* 0x0C */ f32 velocity;
    /* 0x10 */ f32 fadeOutVel;
    /* 0x14 */ f32 current;
    /* 0x18 */ f32 target;
    /* 0x1C */ char pad[4];
    /* 0x20 */ EnvelopePoint* envelope;
} AdsrState; // size = 0x24

typedef struct {
    /* 0x00 */ u8 stereoHeadsetEffects : 1;
    /* 0x00 */ u8 usesHeadsetPanEffects : 1;
    /* 0x00 */ u8 unused : 2;
    /* 0x00 */ u8 bit2 : 2;
    /* 0x00 */ u8 strongRight : 1;
    /* 0x00 */ u8 strongLeft : 1;
} StereoData; // size = 0x1

typedef union {
    /* 0x00 */ StereoData s;
    /* 0x00 */ u8 asByte;
} Stereo; // size = 0x1

typedef struct {
    /* 0x00 */ u8 reverb;
    /* 0x01 */ u8 gain; // Increases volume by a multiplicative scaling factor. Represented as a UQ4.4 number
    /* 0x02 */ u8 pan;
    /* 0x03 */ Stereo stereo;
    /* 0x04 */ f32 freqMod;
    /* 0x08 */ f32 velocity;
} NoteAttributes; // size = 0xC

// Also known as a SubTrack, according to sm64 debug strings.
typedef struct SequenceChannel {
    /* 0x00 */ u8 enabled : 1;
    /* 0x00 */ u8 finished : 1;
    /* 0x00 */ u8 stopScript : 1;
    /* 0x00 */ u8 muted : 1; // sets SequenceLayer.muted
    /* 0x00 */ u8 hasInstrument : 1;
    /* 0x00 */ u8 stereoHeadsetEffects : 1;
    /* 0x00 */ u8 largeNotes : 1; // notes specify duration and velocity
    /* 0x00 */ u8 unused : 1;
    union {
        struct {
            /* 0x01 */ u8 freqMod : 1;
            /* 0x01 */ u8 volume : 1;
            /* 0x01 */ u8 pan : 1;
        } s;
        /* 0x01 */ u8 asByte;
    } changes;
    /* 0x02 */ u8 noteAllocPolicy;
    /* 0x03 */ u8 muteBehavior;
    /* 0x04 */ u8 targetReverbVol;
    /* 0x05 */ u8 notePriority; // 0-3
    /* 0x06 */ u8 fontId;
    /* 0x07 */ u8 someOtherPriority;
    /* 0x08 */ u8 bookOffset;
    /* 0x09 */ u8 newPan;
    /* 0x0A */ u8 panChannelWeight; // proportion of pan that comes from the channel (0..128)
    /* 0x0B */ u8 reverbIndex;
    /* 0x0C */ u16 vibratoRateStart;
    /* 0x0E */ u16 vibratoDepthStart;
    /* 0x10 */ u16 vibratoRateTarget;
    /* 0x12 */ u16 vibratoDepthTarget;
    /* 0x14 */ u16 vibratoRateChangeDelay;
    /* 0x16 */ u16 vibratoDepthChangeDelay;
    /* 0x18 */ u16 vibratoDelay;
    /* 0x1A */ u16 delay;
    /* 0x1C */ s16 instOrWave; // either 0 (none), instrument index + 1, or
                               // 0x80..0x83 for sawtooth/triangle/sine/square waves.
    /* 0x1E */ s16 transposition;
    /* 0x20 */ f32 volumeMod;
    /* 0x24 */ f32 volume;
    /* 0x28 */ s32 pan;
    /* 0x2C */ f32 appliedVolume;
    /* 0x30 */ f32 freqMod;
    /* 0x34 */ u8 (*dynTable)[2];
    /* 0x38 */ struct Note* noteUnused;
    /* 0x3C */ struct SequenceLayer* layerUnused;
    /* 0x40 */ Instrument* instrument;
    /* 0x44 */ SequencePlayer* seqPlayer;
    /* 0x48 */ struct SequenceLayer* layers[4];
    /* 0x58 */ SeqScriptState scriptState;
    /* 0x74 */ AdsrSettings adsr;
    /* 0x7C */ NotePool notePool;
    /* 0xBC */ s8 seqScriptIO[8]; // bridge between .seq script and audio lib, "io ports"
    /* 0xC4 */ u16 unkC4;
} SequenceChannel;                // size = 0xC8

// Might also be known as a Track, according to sm64 debug strings (?).
typedef struct SequenceLayer {
    /* 0x00 */ u8 enabled : 1;
    /* 0x00 */ u8 finished : 1;
    /* 0x00 */ u8 muted : 1;
    /* 0x00 */ u8 continuousNotes : 1; // keep the same note for consecutive notes with the same sound
    /* 0x00 */ u8 bit3 : 1;            // "loaded"?
    /* 0x00 */ u8 ignoreDrumPan : 1;
    /* 0x00 */ u8 bit1 : 1; // "has initialized continuous notes"?
    /* 0x00 */ u8 notePropertiesNeedInit : 1;
    /* 0x01 */ Stereo stereo;
    /* 0x02 */ u8 instOrWave;
    /* 0x03 */ s8 unk_3;
    /* 0x04 */ u8 gateTime;
    /* 0x05 */ u8 portamentoTargetNote;
    /* 0x06 */ u8 pan;
    /* 0x07 */ u8 notePan;
    /* 0x08 */ Portamento portamento;
    /* 0x18 */ AdsrSettings adsr;
    /* 0x20 */ u16 portamentoTime;
    /* 0x22 */ s16 transposition;
    /* 0x24 */ f32 freqMod;
    /* 0x28 */ f32 velocitySquare;
    /* 0x2C */ f32 noteVelocity;
    /* 0x30 */ f32 noteFreqMod;
    /* 0x34 */ u16 shortNoteDefaultDelay;
    /* 0x36 */ u16 lastDelay;
    /* 0x38 */ s16 delay;
    /* 0x3A */ s16 gateDelay;
    /* 0x3C */ s16 delay2;
    /* 0x40 */ struct Note* note;
    /* 0x44 */ Instrument* instrument;
    /* 0x48 */ TunedSample* tunedSample;
    /* 0x4C */ SequenceChannel* channel;
    /* 0x50 */ SeqScriptState state;
    /* 0x6C */ AudioListItem listItem;
    /* 0x7C */ char pad7C[4];
} SequenceLayer; // size = 0x80

typedef struct UnkStruct_800097A8 {
    /* 0x00 */ s16* unk_0;
    /* 0x04 */ s32 unk_4;
    /* 0x08 */ s32 unk_8;
    /* 0x0C */ s16* unk_C;
    /* 0x10 */ char pad10[4];
    /* 0x14 */ struct SampleDma* unk_14;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ char pad1A[6];
} UnkStruct_800097A8; /* size = 0x20 */

typedef struct {
    /* 0x000 */ s16 adpcmdecState[16];
    /* 0x020 */ s16 finalResampleState[16];
    /* 0x040 */ UnkStruct_800097A8 unk_40;
    /* 0x060 */ char pad[0x20];
    /* 0x080 */ s16 panSamplesBuffer[0x20];
    // /* 0x040 */ s16 mixEnvelopeState[32];
    // /* 0x080 */ s16 unusedState[16];
    // /* 0x0A0 */ s16 haasEffectDelayState[32];
    // /* 0x0E0 */ s16 combFilterState[128];
} NoteSynthesisBuffers; // size = 0xC0

typedef struct {
    /* 0x00 */ u8 restart;
    /* 0x01 */ u8 sampleDmaIndex;
    /* 0x02 */ u8 prevHaasEffectLeftDelaySize;
    /* 0x03 */ u8 prevHaasEffectRightDelaySize;
    /* 0x04 */ u8 reverbVol;
    /* 0x05 */ u8 numParts;
    /* 0x06 */ u16 samplePosFrac;
    /* 0x08 */ s32 samplePosInt;
    /* 0x0C */ NoteSynthesisBuffers* synthesisBuffers;
    /* 0x10 */ s16 curVolLeft;
    /* 0x12 */ s16 curVolRight;
    /* 0x14 */ char unk_14[0xC];
} NoteSynthesisState; // size = 0x20

typedef struct {
    /* 0x00 */ struct SequenceChannel* channel;
    /* 0x04 */ u32 time;
    /* 0x08 */ s16* curve; // sineWave
    /* 0x0C */ f32 depth;
    /* 0x10 */ f32 rate;
    /* 0x14 */ u8 active;
    /* 0x16 */ u16 rateChangeTimer;
    /* 0x18 */ u16 depthChangeTimer;
    /* 0x1A */ u16 delay;
} VibratoState; // size = 0x1C

typedef struct {
    /* 0x00 */ u8 priority;
    /* 0x01 */ u8 waveId;
    /* 0x02 */ u8 harmonicIndex; // the harmonic index for the synthetic wave contained in gWaveSamples (also matches
                                 // the base 2 logarithm of the harmonic order)
    /* 0x03 */ u8 fontId;
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 stereoHeadsetEffects;
    /* 0x06 */ s16 adsrVolModUnused;
    /* 0x08 */ f32 portamentoFreqMod;
    /* 0x0C */ f32 vibratoFreqMod;
    /* 0x10 */ struct SequenceLayer* prevParentLayer;
    /* 0x14 */ struct SequenceLayer* parentLayer;
    /* 0x18 */ struct SequenceLayer* wantedParentLayer;
    /* 0x1C */ NoteAttributes attributes;
    /* 0x28 */ AdsrState adsr;
    /* 0x4C */ Portamento portamento;
    /* 0x5C */ VibratoState vibratoState;
} NotePlaybackState; // size = 0x78

typedef struct {
    struct {
        /* 0x00 */ volatile u8 enabled : 1;
        /* 0x00 */ u8 needsInit : 1;
        /* 0x00 */ u8 finished : 1; // ?
        /* 0x00 */ u8 unused : 1;
        /* 0x00 */ u8 stereoStrongRight : 1;
        /* 0x00 */ u8 stereoStrongLeft : 1;
        /* 0x00 */ u8 stereoHeadsetEffects : 1;
        /* 0x00 */ u8 usesHeadsetPanEffects : 1; // ?
    } bitField0;
    struct {
        /* 0x01 */ u8 reverbIndex : 3;
        /* 0x01 */ u8 bookOffset : 3;
        /* 0x01 */ u8 isSyntheticWave : 1;
        /* 0x01 */ u8 hasTwoParts : 1;
    } bitField1;
    /* 0x02 */ u8 gain;
    /* 0x03 */ u8 leftDelaySize;
    /* 0x04 */ u8 rightDelaySize;
    /* 0x05 */ u8 reverb;
    /* 0x06 */ u16 panVolLeft;
    /* 0x08 */ u16 panVolRight;
    /* 0x0A */ u16 resampleRate;
    /* 0x0C */ Sample** waveSampleAddr;
} NoteSubEu; // size = 0x10

typedef struct Note {
    /* 0x00 */ AudioListItem listItem;
    /* 0x10 */ NoteSynthesisState synthesisState;
    /* 0x30 */ NotePlaybackState playbackState;
    /* 0xA8 */ char padA0[0x8];
    /* 0xB0 */ NoteSubEu noteSubEu;
} Note; // size = 0xC0

typedef struct {
    /* 0x00 */ u8 downsampleRate;
    /* 0x01 */ u8 windowSize;
    /* 0x02 */ u16 decayRatio; // determines how much reverb persists
    /* 0x04 */ u16 leakRtL;
    /* 0x06 */ u16 leakLtR;
} ReverbSettings; // size = 0x8

/**
 * The high-level audio specifications requested when initializing or resetting the audio heap.
 * The audio heap can be reset on various occasions, including on most scene transitions.
 */
typedef struct {
    /* 0x00 */ u32 samplingFrequency; // Target sampling rate in Hz
    /* 0x04 */ u8 numBuffers;
    /* 0x05 */ u8 numNotes;
    /* 0x06 */ u8 numReverbs;
    /* 0x08 */ ReverbSettings* reverbSettings;
    /* 0x0C */ u16 unk_14;
    /* 0x10 */ u32 persistentSeqCacheSize;  // size of cache on audio pool to store sequences persistently
    /* 0x14 */ u32 persistentFontCacheSize; // size of cache on audio pool to store soundFonts persistently
    /* 0x18 */ u32
        persistentSampleBankCacheSize;     // size of cache on audio pool to store entire sample banks persistently
    /* 0x1C */ u32 temporarySeqCacheSize;  // size of cache on audio pool to store sequences temporarily
    /* 0x20 */ u32 temporaryFontCacheSize; // size of cache on audio pool to store soundFonts temporarily
    /* 0x24 */ u32 temporarySampleBankCacheSize; // size of cache on audio pool to store entire sample banks temporarily
    /* 0x28 */ s32
        persistentSampleCacheSize; // size of cache in the audio misc pool to store individual samples persistently
    /* 0x2C */ s32
        temporarySampleCacheSize; // size of cache in the audio misc pool to store individual samples temporarily
} AudioSpec;                      // size = 0x30

/**
 * The audio buffer stores the fully processed digital audio before it is sent to the audio interface (AI), then to the
 * digital-analog converter (DAC), then to play on the speakers. The audio buffer is written to by the rsp after
 * processing audio commands. This struct parameterizes that buffer.
 */
typedef struct {
    /* 0x00 */ s16 numBuffers;
    /* 0x02 */ u16 samplingFrequency;   // Target sampling rate in Hz
    /* 0x04 */ u16 aiSamplingFrequency; // True sampling rate of the audio interface (AI), see `osAiSetFrequency`
    /* 0x06 */ s16 samplesPerFrameTarget;
    /* 0x08 */ s16 maxAiBufferLength;
    /* 0x0A */ s16 minAiBufferLength;
    /* 0x0C */ s16 ticksPerUpdate; // for each audio thread update, number of ticks to process audio
    /* 0x0E */ s16 samplesPerTick;
    /* 0x10 */ s16 samplesPerTickMax;
    /* 0x12 */ s16 samplesPerTickMin;
    /* 0x14 */ f32 resampleRate;
    /* 0x18 */ f32 ticksPerUpdateInv;       // inverse (reciprocal) of ticksPerUpdate
    /* 0x1C */ f32 ticksPerUpdateInvScaled; // ticksPerUpdateInv scaled down by a factor of 256
} AudioBufferParameters;                    // size = 0x20

/**
 * Meta-data associated with a pool (contained within the Audio Heap)
 */
typedef struct {
    /* 0x0 */ u8* startRamAddr; // start addr of the pool
    /* 0x4 */ u8* curRamAddr;   // address of the next available memory for allocation
    /* 0x8 */ s32 size;         // size of the pool
    /* 0xC */ s32 numEntries;   // number of entries allocated to the pool
} AudioAllocPool;               // size = 0x10

/**
 * Audio cache entry data to store a single entry containing either a sequence, soundfont, or entire sample banks
 */
typedef struct {
    /* 0x0 */ u8* ramAddr;
    /* 0x4 */ u32 size;
    /* 0x8 */ s16 tableType;
    /* 0xA */ s16 id;
} AudioCacheEntry; // size = 0xC

/**
 * Audio cache entry data to store a single entry containing an individual sample
 */
typedef struct {
    /* 0x00 */ s8 inUse;
    /* 0x01 */ s8 origMedium;
    /* 0x02 */ s8 sampleBankId;
    /* 0x03 */ char unk_03[0x5];
    /* 0x08 */ u8* allocatedAddr;
    /* 0x0C */ void* sampleAddr;
    /* 0x10 */ u32 size;
} SampleCacheEntry; // size = 0x14

/**
 * Audio cache entry data to store individual samples
 */
typedef struct {
    /* 0x000 */ AudioAllocPool pool;
    /* 0x010 */ SampleCacheEntry entries[64];
    /* 0x290 */ s32 numEntries;
} AudioSampleCache; // size = 0x294

typedef struct {
    /* 0x00*/ u32 numEntries;
    /* 0x04*/ AudioAllocPool pool;
    /* 0x14*/ AudioCacheEntry entries[32];
} AudioPersistentCache; // size = 0x194

typedef struct {
    /* 0x00*/ u32 nextSide;
    /* 0x04*/ AudioAllocPool pool;
    /* 0x14*/ AudioCacheEntry entries[2];
} AudioTemporaryCache; // size = 0x2C

typedef struct {
    /* 0x000*/ AudioPersistentCache persistent;
    /* 0x194*/ AudioTemporaryCache temporary;
    /* 0x1C0*/ char pad[0x10];
} AudioCache; // size = 0x1D0

typedef struct {
    /* 0x0 */ u32 persistentCommonPoolSize;
    /* 0x4 */ u32 temporaryCommonPoolSize;
} AudioCachePoolSplit; // size = 0x8

typedef struct {
    /* 0x0 */ u32 seqCacheSize;
    /* 0x4 */ u32 fontCacheSize;
    /* 0x8 */ u32 sampleBankCacheSize;
} AudioCommonPoolSplit; // size = 0xC

typedef struct {
    /* 0x0 */ u32 miscPoolSize;
    /* 0x4 */ u32 unkSizes[2];
    /* 0xC */ u32 cachePoolSize;
} AudioSessionPoolSplit; // size = 0x10

typedef struct {
    /* 0x00 */ u32 endAndMediumKey;
    /* 0x04 */ Sample* sample;
    /* 0x08 */ u8* ramAddr;
    /* 0x0C */ u32 encodedInfo;
    /* 0x10 */ s32 isFree;
} AudioPreloadReq; // size = 0x14

/**
 * Audio commands used to transfer audio requests from the graph thread to the audio thread
 */
typedef struct {
    /* 0x0 */ union {
        u32 opArgs;
        struct {
            u8 arg2;
            u8 arg1;
            u8 arg0;
            u8 op;
        };
    };
    union {
        void* data;
        f32 asFloat;
        s32 asInt;
        uintptr_t asPtr;
        u16 asUShort;
        s8 asSbyte;
        u8 asUbyte;
        u32 asUInt;
    };
} AudioCmd; // size = 0x8

typedef struct {
    /* 0x00 */ s8 status;
    /* 0x01 */ s8 delay;
    /* 0x02 */ s8 medium;
    /* 0x04 */ u8* ramAddr;
    /* 0x08 */ uintptr_t curDevAddr;
    /* 0x0C */ u8* curRamAddr;
    /* 0x10 */ u32 bytesRemaining;
    /* 0x14 */ u32 chunkSize;
    /* 0x18 */ OSMesg retMsg;
    /* 0x1C */ OSMesgQueue* retQueue;
    /* 0x20 */ OSMesgQueue mesgQueue;
    /* 0x38 */ OSMesg msg;
    /* 0x3C */ OSIoMesg ioMesg;
} AudioAsyncLoad; // size = 0x54

typedef struct {
    /* 0x00 */ u8 medium;
    /* 0x01 */ u8 seqOrFontId;
    /* 0x02 */ u8 instId;
    /* 0x04 */ uintptr_t curDevAddr;
    /* 0x08 */ u8* curRamAddr;
    /* 0x0C */ u8* ramAddr;
    /* 0x10 */ s32 state;
    /* 0x14 */ s32 bytesRemaining;
    /* 0x18 */ s8* status; // write-only
    /* 0x1C */ Sample sample;
    /* 0x2C */ OSMesgQueue mesgQueue;
    /* 0x44 */ OSMesg msg;
    /* 0x48 */ OSIoMesg ioMesg;
} AudioSlowLoad; // size = 0x60

typedef struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ AudioSlowLoad slowLoad[2];
} AudioSlowLoadBuffer; // size = 0xC4

typedef struct {
    /* 0x00 */ s16 numEntries;
    /* 0x02 */ s16 unkMediumParam;
    /* 0x04 */ uintptr_t romAddr;
    /* 0x08 */ char pad[8];
} AudioTableBase;

typedef struct {
    /* 0x00 */ uintptr_t romAddr;
    /* 0x04 */ u32 size;
    /* 0x08 */ s8 medium;
    /* 0x09 */ s8 cachePolicy;
    /* 0x0A */ s16 shortData1;
    /* 0x0C */ s16 shortData2;
    /* 0x0E */ s16 shortData3;
} AudioTableEntry; // size = 0x10

typedef struct {
    /* 0x00 */ AudioTableBase base;
    /* 0x10 */ AudioTableEntry* entries; // (dynamic size)
} AudioTable; // size >= 0x20

typedef struct SampleDma {
    /* 0x00 */ u8* ramAddr;
    /* 0x04 */ uintptr_t devAddr;
    /* 0x08 */ u16 sizeUnused;
    /* 0x0A */ u16 size;
    /* 0x0C */ u8 unused;
    /* 0x0D */ u8 reuseIndex; // position in sSampleDmaReuseQueue1/2, if ttl == 0
    /* 0x0E */ u8 ttl;        // duration after which the DMA can be discarded
} SampleDma;                  // size = 0x10

typedef struct {
    /* 0x00 */ u8 reverbVol;
    /* 0x01 */ u8 gain; // Increases volume by a multiplicative scaling factor. Represented as a UQ4.4 number
    /* 0x02 */ u8 pan;
    /* 0x03 */ Stereo stereo;
    /* 0x04 */ f32 frequency;
    /* 0x08 */ f32 velocity;
    /* 0x0C */ char unk_0C[0x4];
    /* 0x10 */ s16* filter;
    /* 0x14 */ u8 combFilterSize;
    /* 0x16 */ u16 combFilterGain;
} NoteSubAttributes; // size = 0x18

typedef struct {
    /* 0x0 */ s16 unk_00; // set to 0x1C00, unused
    /* 0x2 */ s16 seqTicksPerBeat;
} TempoData; // size = 0x4

typedef struct {
    /* 0x00 */ u32 heapSize; // total number of bytes allocated to the audio heap. Must be <= the size of `gAudioHeap`
                             // (ideally about the same size)
    /* 0x04 */ u32 initPoolSize; // The entire audio heap is split into two pools.
    /* 0x08 */ u32 permanentPoolSize;
} AudioHeapInitSizes; // size = 0xC

typedef struct {
    AudioAllocPool pool;
    AudioCacheEntry entry[32];
} PermanentCache; // size = 0x190

typedef struct {
    /* 0x00 */ s32 sampleBankId1;
    /* 0x04 */ s32 sampleBankId2;
    /* 0x08 */ uintptr_t baseAddr1;
    /* 0x0C */ uintptr_t baseAddr2;
    /* 0x10 */ u32 medium1;
    /* 0x14 */ u32 medium2;
} SampleBankRelocInfo; // size = 0x18

typedef struct {
    /* 0x0 */ u8 opCode;
    /* 0x1 */ u8 seqPlayId;
    /* 0x2 */ u16 seqId;
    /* 0x5 */ u16 fadeoutTime;
    /* 0x6 */ u8 bgmParam;
    /* 0x8 */ u16 timer;
} PlaylistCmd; // size:0xA

typedef struct {
    /* 0x0 */ u16 seqId;
    /* 0x2 */ u16 audioSpec;
    /* 0x4 */ u8 bgmParam;
} SoundTestTrack; // size: 0x6

typedef struct {
    /* 0x00 */ f32* xPos;
    /* 0x04 */ f32* yPos;
    /* 0x08 */ f32* zPos;
    /* 0x0C */ u8 token;
    /* 0x10 */ f32* freqMod;
    /* 0x14 */ f32* volMod;
    /* 0x18 */ s8* reverbAdd;
    /* 0x1C */ f32 distance;
    /* 0x20 */ u32 priority;
    /* 0x24 */ u32 sfxId;
    /* 0x28 */ u8 state;
    /* 0x29 */ u8 freshness;
    /* 0x2A */ u8 prev;
    /* 0x2B */ u8 next;
    /* 0x2C */ u8 channelIndex;
} SfxBankEntry; // size = 0x30

typedef struct {
    /* 0x00 */ u32 sfxId;
    /* 0x04 */ f32* source;
    /* 0x08 */ u8 token;
    /* 0x0C */ f32* freqMod;
    /* 0x10 */ f32* volMod;
    /* 0x14 */ s8* reverbAdd;
} SfxRequest; // size = 0x18

typedef struct {
    /* 0x0 */ u32 priority; // lower is more prioritized
    /* 0x4 */ u8 entryIndex;
} ActiveSfx;                // size 0x8

typedef struct {
    /* 0x0 */ u8 seqId;
    /* 0x1 */ u8 priority; // higher values have higher priority
} SeqRequest;              // size = 0x2

typedef struct {
    /* 0x0 */ f32 value;
    /* 0x4 */ f32 target;
    /* 0x8 */ f32 step;
    /* 0xC */ u16 timer;
} Modulation; // size 0x10

typedef struct {
    /* 0x000 */ f32 mod;
    /* 0x004 */ f32 target;
    /* 0x008 */ f32 step;
    /* 0x00C */ u16 timer;
    /* 0x00E */ u8 fadeMod[3];
    /* 0x011 */ u8 fadeTimer;
    /* 0x012 */ u8 fadeActive;
} FadeModulation; // size 0x14

typedef struct {
    /* 0x00 */ Modulation volume;
    /* 0x10 */ Modulation freq;
} ChannelModulation; // size = 0x20

typedef struct {
    /* 0x000 */ FadeModulation mainVolume;
    /* 0x014 */ u32 tempoCmd;
    /* 0x018 */ u16 tempoOriginal; // stores the original tempo before modifying it (to reset back to)
    /* 0x01C */ Modulation tempo;
    /* 0x02C */ u32 setupCmd[5];   // a queue of cmds to execute once the player is disabled
    /* 0x040 */ u8 setupCmdTimer;  // only execute setup commands when the timer is at 0.
    /* 0x041 */ u8 setupCmdNum;    // number of setup commands requested once the player is disabled
    /* 0x042 */ u8 setupFadeTimer;
    /* 0x044 */ ChannelModulation channelMod[16];
    /* 0x244 */ u16 freqModChannelFlags;
    /* 0x246 */ u16 volChannelFlags;
    /* 0x248 */ u16 seqId;            // active seqId currently playing. Resets when sequence stops
    /* 0x24A */ u16 prevSeqId;        // last seqId played on a player. Does not reset when sequence stops
    /* 0x24C */ u16 channelPortMask;
    /* 0x250 */ u32 startSeqCmd;      // This name comes from MM
    /* 0x254 */ u8 isWaitingForFonts; // This name comes from MM
} ActiveSequence;                     // size 0x258

typedef struct {
    /* 0x0 */ f32 volMod;
    /* 0x4 */ f32 freqMod;
    /* 0x8 */ s8 reverb;
    /* 0x9 */ s8 pan;
} SfxChannelState; // size 0xC

typedef struct {
    /* 0x0 */ u32 seqData;
    /* 0x4 */ u16 timer;
} DelayedSeqCmd; // size 0x08

typedef struct {
    /* 0x00 */ f32 value;
    /* 0x04 */ f32 target;
    /* 0x08 */ u32 timer;
    /* 0x0C */ f32 step;
    /* 0x10 */ u8 boost;
    /* 0x11 */ u8 brake;
} FrequencyLerp; // size 0x14

typedef struct {
    /* 0x00 */ FrequencyLerp freqMod[5];
    /* 0x64 */ f32 dopplerShift;
    /* 0x68 */ f32 totalMod;
    /* 0x6C */ u8 form;
    /* 0x6D */ s8 reverbAdd;
} PlayerNoiseModulation; // size 0x70

#define SEQ_HEX0(seqId) ((seqId) >> 28 & 0xFF)
#define SEQ_HEX1(seqId) (((seqId) & (0xF << 24)) >> 24 & 0xFF)
#define SEQ_BYTE4(seqId) ((seqId) &0xFF)
#define SEQ_BYTE3(seqId) (((seqId) & (0xFF << 8)) >> 8 & 0xFF)
#define SEQ_BYTE2(seqId) (((seqId) & (0xFF << 16)) >> 13 & 0xFFFF)

// audio_synthesis
void AudioSynth_HartleyTransform(f32*, s32, f32*);
Acmd* AudioSynth_Update(Acmd* aList, s32* cmdCount, s16* aiBufStart, s32 aiBufLen);

// audio_effects
void Audio_SequencePlayerProcessSound(SequencePlayer* seqplayer);
void Audio_NoteVibratoUpdate(Note* note);
void Audio_NoteVibratoInit(Note* note);
void Audio_AdsrInit(AdsrState* adsr, EnvelopePoint* envelope, s16* arg2);
f32 Audio_AdsrUpdate(AdsrState* adsr);

// audio_heap
void AudioHeap_DiscardFont(s32 fontId);
void* AudioHeap_Alloc(AudioAllocPool* pool, u32 size);
void AudioHeap_InitPool(AudioAllocPool* pool, void* ramAddr, u32 size);
void AudioHeap_InitMainPools(s32 initPoolSize);
void* AudioHeap_AllocCached(s32 tableType, s32 size, s32 cache, s32 id);
uintptr_t AudioHeap_SearchCaches(s32 tableType, s32 cache, s32 id);
s32 AudioHeap_ResetStep(void);
void* AudioHeap_SearchPermanentCache(s32 tableType, s32 id);
u8* AudioHeap_AllocPermanent(s32 tableType, s32 id, u32 size);
void* AudioHeap_AllocTemporarySampleCache(s32 size, s32 fontId, uintptr_t sampleAddr, s8 medium);
void* AudioHeap_AllocPersistentSampleCache(s32 size, s32 fontId, uintptr_t sampleAddr, s8 medium);

// audio_load
void AudioLoad_DecreaseSampleDmaTtls(void);
void AudioLoad_ProcessLoads(s32 resetStatus);
void AudioLoad_SyncInitSeqPlayer(s32 playerIdx, s32 seqId, s32 arg2);
void* AudioLoad_DmaSampleData(uintptr_t devAddr, u32 size, u32 arg2, u8* dmaIndexRef, s32 medium);
void AudioLoad_InitSampleDmaBuffers(s32 numNotes);
void AudioLoad_SyncLoadSeqParts(s32 seqId, s32 flags);
s32 AudioLoad_SyncLoadInstrument(s32 fontId, s32 instId, s32 drumId);
void AudioLoad_AsyncLoadSampleBank(s32 sampleBankId, s32 nChunks, s32 retData, OSMesgQueue* retQueue);
void AudioLoad_AsyncLoadSeq(s32 seqId, s32 nChunks, s32 retData, OSMesgQueue* retQueue);
u8* AudioLoad_GetFontsForSequence(s32 seqId, u32* outNumFonts);
void AudioLoad_DiscardSeqFonts(s32 seqId);
s32 AudioLoad_SlowLoadSample(s32 fontId, u8 instId, s8* status);

// audio_playback
TunedSample* Audio_GetInstrumentTunedSample(Instrument* instrument, s32 semitone);
Instrument* Audio_GetInstrument(s32, s32);
Drum* Audio_GetDrum(s32, s32);
void Audio_NoteDisable(Note* note);
void Audio_ProcessNotes(void);
void Audio_SeqLayerNoteDecay(SequenceLayer* layer);
void Audio_InitSyntheticWave(Note* note, SequenceLayer* layer);
void Audio_InitNoteLists(NotePool* pool);
void Audio_InitNoteFreeList(void);
void Audio_NotePoolClear(NotePool* pool);
void Audio_NotePoolFill(NotePool* pool, s32);
void Audio_AudioListRemove(Note* note);
Note* Audio_AllocNote(SequenceLayer* layer);
void Audio_NoteInitAll(void);

// audio_seqplayer
void AudioSeq_SequenceChannelDisable(SequenceChannel* channel);
void AudioSeq_SequencePlayerDisable(SequencePlayer* seqPlayer);
void AudioSeq_AudioListPushBack(AudioListItem* list, AudioListItem* item);
void* AudioSeq_AudioListPopBack(AudioListItem* list);
void AudioSeq_ProcessSequences(s32 arg0);
void AudioSeq_ResetSequencePlayer(s32 arg0);
void AudioSeq_InitSequencePlayers(void);

// audio_thread
void AudioThread_ScheduleProcessCmds(void);
u32 AudioThread_GetAsyncLoadStatus(u32*);
u8* AudioThread_GetFontsForSequence(s32 seqId, u32* outNumFonts);
bool AudioThread_ResetComplete(void);
void AudioThread_ResetAudioHeap(s32);
void AudioThread_Init(void);

// extern AudioTable gSampleBankTableInit;
// extern AudioTable gSeqTableInit;
// extern AudioTable gSoundFontTableInit;
// extern u8 gSeqFontTableInit[];

extern AudioSpec gAudioSpecs[];
extern s16 gSeqTicksPerBeat;
extern s32 gAudioHeapSize;
extern s32 gInitPoolSize;
extern u32 gPermanentPoolSize;
extern u16 gSequenceMedium;
extern u16 gSoundFontMedium;
extern u16 gSampleBankMedium;

extern u64 gAudioContextStart[];
extern SynthesisReverb gSynthReverbs[4];
extern u8 sAudioContextPad10[0x10]; // 0x10
extern u16 D_8014C1B0;
extern s8 D_8014C1B2;
extern s8 gNumSynthReverbs;
extern s16 D_8014C1B4;
extern NoteSubEu* gNoteSubsEu;
// 0x4
extern AudioAllocPool gSessionPool;
extern AudioAllocPool gInitPool;
extern AudioAllocPool gMiscPool;
extern u8 gAudioContextPad20[0x20]; // 0x20
extern AudioAllocPool gCachePool;
extern AudioAllocPool gPersistentCommonPool;
extern AudioAllocPool gTemporaryCommonPool;
extern AudioCache gSeqCache;
extern AudioCache gFontCache;
extern AudioCache gSampleBankCache;
extern PermanentCache gPermanentPool;
extern AudioSampleCache gPersistentSampleCache;
// 0x4
extern AudioSampleCache gTemporarySampleCache;
// 0x4
extern AudioSessionPoolSplit gSessionPoolSplit;
extern AudioCachePoolSplit gCachePoolSplit;
extern AudioCommonPoolSplit gPersistentCommonPoolSplit;
// 0x4
extern AudioCommonPoolSplit gTemporaryCommonPoolSplit;
// 0x4
extern u8 gSampleFontLoadStatus[2048];
extern u8 gFontLoadStatus[2048];
extern u8 gSeqLoadStatus[2048];
extern volatile u8 gAudioResetStep;
extern u8 gAudioSpecId;
extern s32 gResetFadeoutFramesLeft;
extern u8 sAudioContextPad1000[0x1000]; // 0x1000 gap
extern Note* gNotes;
// 0x4
extern SequencePlayer gSeqPlayers[4];
extern SequenceChannel gSeqChannels[48];
extern SequenceLayer gSeqLayers[64];
extern SequenceChannel gSeqChannelNone;
extern AudioListItem gLayerFreeList;
extern NotePool gNoteFreeLists;
extern Sample* gUsedSamples[2048];
extern AudioPreloadReq gPreloadSampleStack[128];
extern s32 gNumUsedSamples;
extern s32 gPreloadSampleStackTop;
extern AudioAsyncLoad gAsyncLoads[16];
extern OSMesgQueue gExternalLoadQueue;
extern OSMesg gExternalLoadMsg[16];
extern OSMesgQueue gPreloadSampleQueue;
extern OSMesg gPreloadSampleMsg[16];
extern OSMesgQueue gCurAudioFrameDmaQueue;
extern OSMesg gCurAudioFrameDmaMsg[64];
extern OSIoMesg gCurAudioFrameDmaIoMsgBuf[64];
extern OSMesgQueue gSyncDmaQueue;
extern OSMesg gSyncDmaMsg[1];
// 0x4
extern OSIoMesg gSyncDmaIoMsg;
extern SampleDma gSampleDmas[0x100];
extern u32 gSampleDmaCount;
extern u32 gSampleDmaListSize1;
extern s32 D_80155A50;
// 0x4
extern u8 gSampleDmaReuseQueue1[0x100];
extern u8 gSampleDmaReuseQueue2[0x100];
extern u8 gSampleDmaReuseQueue1RdPos;
extern u8 gSampleDmaReuseQueue2RdPos;
extern u8 gSampleDmaReuseQueue1WrPos;
extern u8 gSampleDmaReuseQueue2WrPos;
extern AudioTable* gSequenceTable;
extern AudioTable* gSoundFontTable;
extern AudioTable* gSampleBankTable;
extern u8* gSeqFontTable;
extern s16 gNumSequences;
extern SoundFont* gSoundFontList;
// 0x4
extern AudioBufferParameters gAudioBufferParams;
extern s32 gSampleDmaBuffSize;
extern s32 gMaxAudioCmds;
extern s32 gNumNotes;
extern s16 gMaxTempo;
extern s8 gAudioSoundMode;
extern volatile s32 gAudioTaskCountQ;
extern s32 gCurAudioFrameDmaCount;
extern s32 gAudioTaskIndexQ;
extern s32 gCurAiBuffIndex;
extern Acmd* gAbiCmdBuffs[2];
extern Acmd* gCurAbiCmdBuffer;
extern SPTask* gAudioCurTask;
extern SPTask gAudioRspTasks[2];
extern f32 gMaxTempoTvTypeFactors;
extern s32 gRefreshRate;
extern s16* gAiBuffers[3];
extern s16 gAiBuffLengths[3];
extern u32 gAudioRandom;
extern u32 D_80155D88;
extern volatile u32 gAudioResetTimer;

extern u64 gAudioContextEnd[];

// wave_samples
extern s16* gWaveSamples[];

// note_data
extern f32 gBendPitchOneOctaveFrequencies[];
extern f32 gBendPitchTwoSemitonesFrequencies[];
extern f32 gPitchFrequencies[];
extern u8 gDefaultShortNoteVelocityTable[];
extern u8 gDefaultShortNoteGateTimeTable[];
extern u16 gHaasEffectDelaySizes[64];
extern EnvelopePoint gDefaultEnvelope[];
extern NoteSubEu gZeroNoteSub;
extern NoteSubEu gDefaultNoteSub;
extern s16 gD_800DD200[];
extern f32 gHeadsetPanVolume[128];
extern f32 gStereoPanVolume[128];
extern f32 gDefaultPanVolume[128];

#ifdef __cplusplus
}
#endif

#endif
