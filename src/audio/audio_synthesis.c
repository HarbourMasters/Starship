#include "sys.h"
#include "sf64audio_provisional.h"
#include "audio/mixer.h"
#include "endianness.h"
#include "port/Engine.h"

#define DMEM_WET_SCRATCH 0x470
#define DMEM_COMPRESSED_ADPCM_DATA 0x990
#define DMEM_LEFT_CH 0x990
#define DMEM_RIGHT_CH 0xB10
#define DMEM_HAAS_TEMP 0x650
#define DMEM_TEMP 0x450
#define DMEM_UNCOMPRESSED_NOTE 0x5F0
#define DMEM_WET_LEFT_CH 0xC90
#define DMEM_WET_RIGHT_CH 0xE10 // = DMEM_WET_LEFT_CH + DMEM_1CH_SIZE
#define SAMPLE_SIZE sizeof(s16)

typedef enum {
    /* 0 */ HAAS_EFFECT_DELAY_NONE,
    /* 1 */ HAAS_EFFECT_DELAY_LEFT, // Delay left channel so that right channel is heard first
    /* 2 */ HAAS_EFFECT_DELAY_RIGHT // Delay right channel so that left channel is heard first
} HaasEffectDelaySide;

s32 D_80145D40; // unused

// all of these are part of the DFT-related function
f32 D_80145D48[256];
f32 D_80146148[256];
f32 D_80146548[515];
f32 D_80146D54;
f32 D_80146D58;
f32 D_80146D5C;
f32 D_80146D60;
f32 D_80146D64;
f32 D_80146D68;
f32 D_80146D6C;
f32 D_80146D70;

static const char devstr0[] = "Table Remake\n";
static const char devstr1[] = "-------------------Undefined Ctype \n";
static const char devstr2[] = "Error? Limit OVER %d in %d\n";
static const char devstr3[] = "";
static const char devstr4[] = "Get %x  %x\n";
static const char devstr5[] = "Break %x %d %d \n";
static const char devstr6[] = "Terminate-Canceled Channel %d,Phase %d\n";
static const char devstr7[] = "S->W\n";
static const char devstr8[] = "W->S\n";
static const char devstr9[] = "S-Resample Pitch %x (old %d -> delay %d)\n";

void AudioSynth_DisableSampleStates(s32 updateIndex, s32 noteIndex);
void AudioSynth_SyncSampleStates(s32 updateIndex);
Acmd* AudioSynth_ProcessNote(s32 noteIndex, NoteSubEu* noteSub, NoteSynthesisState* synthState, s16* aiBuf,
                             s32 aiBufLen, Acmd* aList, s32 updateIndex);
Acmd* AudioSynth_DoOneAudioUpdate(s16* aiBuf, s32 aiBufLen, Acmd* aList, s32 updateIndex);
Acmd* AudioSynth_LoadRingBufferPart(Acmd* aList, u16 dmem, u16 startPos, s32 size, s32 reverbIndex);
Acmd* AudioSynth_SaveRingBufferPart(Acmd* aList, u16 dmem, u16 startPos, s32 size, s32 reverbIndex);
Acmd* AudioSynth_LoadReverbSamples(Acmd* aList, s32 aiBufLen, s16 reverbIndex, s16 updateIndex);
Acmd* AudioSynth_SaveReverbSamples(Acmd* aList, s16 reverbIndex, s16 updateIndex);
Acmd* AudioSynth_LoadWaveSamples(Acmd* aList, NoteSubEu* noteSub, NoteSynthesisState* synthState, s32 numSamplesToLoad);
Acmd* AudioSynth_FinalResample(Acmd* aList, NoteSynthesisState* synthState, s32 size, u16 pitch, u16 inpDmem,
                               u32 resampleFlags);
Acmd* AudioSynth_ProcessEnvelope(Acmd* aList, NoteSubEu* noteSub, NoteSynthesisState* synthState, s32 aiBufLen,
                                 u16 dmemSrc, s32 delaySide, s32 flags);
Acmd* AudioSynth_ApplyHaasEffect(Acmd* aList, NoteSubEu* noteSub, NoteSynthesisState* synthState, s32 size, s32 flags,
                                 s32 delaySide);

void AudioSynth_InitNextRingBuf(s32 sampleCount, s32 itemIndex, s32 reverbIndex) {
    ReverbRingBufferItem* ringItem;
    SynthesisReverb* reverb = &gSynthReverbs[reverbIndex];
    s32 numSamples;
    s32 extraSamples;
    s32 i;
    s32 j;
    s32 pad1;
    s32 pad2;
    s32 pad3;

    if ((reverb->downsampleRate != 1) && (reverb->framesToIgnore == 0)) {
        ringItem = &reverb->items[reverb->curFrame][itemIndex];
        osInvalDCache(ringItem->toDownsampleLeft, 0x300);
        j = 0;
        for (i = 0; i < ringItem->lengthA / 2; i++, j += reverb->downsampleRate) {
            reverb->leftRingBuf[ringItem->startPos + i] = ringItem->toDownsampleLeft[j];
            reverb->rightRingBuf[ringItem->startPos + i] = ringItem->toDownsampleRight[j];
        }
        for (i = 0; i < ringItem->lengthB / 2; i++, j += reverb->downsampleRate) {
            reverb->leftRingBuf[i] = ringItem->toDownsampleLeft[j];
            reverb->rightRingBuf[i] = ringItem->toDownsampleRight[j];
        }
    }

    ringItem = &reverb->items[reverb->curFrame][itemIndex];
    numSamples = sampleCount / reverb->downsampleRate;
    extraSamples = reverb->nextRingBufPos + numSamples - reverb->bufSizePerChan;

    if (extraSamples < 0) {
        ringItem->lengthA = numSamples * SAMPLE_SIZE;
        ringItem->lengthB = 0;
        ringItem->startPos = reverb->nextRingBufPos;
        reverb->nextRingBufPos += numSamples;
    } else {
        ringItem->lengthA = (numSamples - extraSamples) * SAMPLE_SIZE;
        ringItem->lengthB = extraSamples * SAMPLE_SIZE;
        ringItem->startPos = reverb->nextRingBufPos;
        reverb->nextRingBufPos = extraSamples;
    }
    ringItem->numSamplesAfterDownsampling = numSamples;
    ringItem->chunkLen = sampleCount;
}

void AudioSynth_InverseDiscreteCosineTransform(f32* buffer0, f32* buffer1, s32 length, f32* buffer2) {
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
        temp_ft0 = D_PI / (f32) (2 * size);
        for (i = 0; i < half; i++) {
            *buf2half2++ = (__cosf(var_fs0) - __sinf(var_fs0)) * 0.707107f;
            *buf2half3++ = (__cosf(var_fs0) + __sinf(var_fs0)) * 0.707107f;
            var_fs0 += temp_ft0;
        }
    }

    // reset the buffer pointers
    buf2half2 = &buffer2[half];
    buf2half3 = &buf2half2[half];
    buff1half1 = buffer1;
    buff0fromStart = buffer0;

    // handle i = 0 case
    buffer1[0] = buffer0[0];
    buffer1[half] = buffer0[half];

    // advance buffer pointers
    buf2half2++;
    buf2half3++;
    buff0fromStart++;
    buff0FromEnd = &buffer0[size - 1];
    buff1half1++;
    buff1half2 = &buffer1[size - 1];

    // convert to real amplitudes
    for (i = 1; i < half; i++) {
        *buff1half1++ = (*buf2half2 * *buff0fromStart) + (*buf2half3 * *buff0FromEnd);
        *buff1half2-- = (*buf2half3 * *buff0fromStart) - (*buf2half2 * *buff0FromEnd);
        buff0fromStart++;
        buf2half3++;
        buf2half2++;
        buff0FromEnd--;
    }

    // FFT buffer 1 using buffer 2
    AudioSynth_HartleyTransform(buffer1, length, buffer2);

    buff0fromStart = buffer0;
    buff0FromEnd = &buffer0[size - 1];
    buff1half1 = buffer1;
    buff1half2 = &buffer1[half];

    // Copy even entries of buffer 0 into the first half of buffer 1. Copy odd entries into the second half in reverse
    // order
    for (i = 0; i < half; i++) {
        *buff0fromStart = *buff1half1++;
        *buff0FromEnd = *buff1half2++;
        buff0fromStart += 2;
        buff0FromEnd -= 2;
    }
}

// https://decomp.me/scratch/8eyVg
#ifdef NON_MATCHING
void AudioSynth_HartleyTransform(f32* arg0, s32 arg1, f32* arg2) {
    s32 length;
    s32 spD0;
    s32 spCC;
    s32 spC8;
    s32 var_a0;
    s32 spC0;
    s32 spBC;
    s32 pad;
    s32 spB4;
    s32 sp58;
    s32 sp50;
    s32 spA8;
    f32 var_fs0;
    f32 temp_fa0;
    f32 temp_fv1;
    f32* temp_a0;
    f32* temp_a1;
    f32* temp_a2;
    f32* temp_a3;
    f32* temp_b0;
    f32* temp_b1;
    f32* temp_b2;
    f32* temp_b3;
    f32* var_s0;
    f32* var_s1;
    f32* var_s2;
    f32* var_s3;

    length = 1 << arg1;
    spBC = length * 2;
    sp58 = (length / 8) - 1;
    switch (length) {
        case 1:
            break;
        case 2:
            temp_fa0 = arg0[1];
            temp_fv1 = arg0[0];

            arg0[0] = (temp_fa0 + temp_fv1) * 0.707107f;
            arg0[1] = (temp_fv1 - temp_fa0) * 0.707107f;
            break;
        case 4:
            temp_fv1 = arg0[0];
            arg0[0] = (arg0[2] + temp_fv1) / 2.0f;
            arg0[2] = (temp_fv1 - arg0[2]) / 2.0f;

            temp_fa0 = arg0[1];
            arg0[1] = (arg0[3] + temp_fa0) / 2.0f;
            arg0[3] = (temp_fa0 - arg0[3]) / 2.0f;

            temp_fv1 = arg0[0];
            temp_fa0 = arg0[1];
            arg0[0] = arg0[1] + temp_fv1;
            arg0[1] = arg0[3] + arg0[2];
            arg0[3] = arg0[2] - arg0[3];
            arg0[2] = temp_fv1 - temp_fa0;
            break;
        default:
            if (length != (s32) *arg2) {
                *arg2 = length;

                var_s0 = &arg2[1];
                var_s1 = &var_s0[sp58];
                var_s2 = &var_s1[sp58];
                var_s3 = &var_s2[sp58];

                var_fs0 = 6.283186f / length;
                for (spCC = 0; spCC < sp58; spCC++) {
                    *var_s0++ = __cosf(var_fs0);
                    *var_s1++ = __sinf(var_fs0);
                    *var_s2++ = __cosf(3.0f * var_fs0);
                    *var_s3++ = __sinf(3.0f * var_fs0);
                    var_fs0 += 6.283186f / length;
                }
            }
            spC0 = 1;
            for (spD0 = 0; spD0 < arg1 - 1; spD0++) {
                spA8 = spBC;
                spBC >>= 1;
                spB4 = spBC >> 3;
                sp50 = spBC >> 2;
                var_a0 = 1;
                do {
                    for (spCC = var_a0 - 1; spCC < length; spCC += spA8) {
                        // if (0) { }
                        temp_a0 = arg0 + spCC;
                        temp_a1 = temp_a0 + sp50;
                        temp_a2 = temp_a1 + sp50;
                        temp_a3 = temp_a2 + sp50;

                        D_80146D54 = *temp_a0;
                        *temp_a0 = *temp_a2 + D_80146D54;
                        D_80146D58 = *temp_a1;
                        *temp_a1 = *temp_a1 + *temp_a3;
                        D_80146D5C = *temp_a2;
                        *temp_a2 = D_80146D54 - D_80146D5C + D_80146D58 - *temp_a3;
                        *temp_a3 = D_80146D54 - D_80146D5C - D_80146D58 + *temp_a3;
                        if (sp50 > 1) {
                            temp_a0 = arg0 + spCC + spB4;
                            temp_a1 = temp_a0 + sp50;
                            temp_a2 = temp_a1 + sp50;
                            temp_a3 = temp_a2 + sp50;

                            D_80146D54 = *temp_a0;
                            *temp_a0 = *temp_a2 + D_80146D54;
                            D_80146D58 = *temp_a1;
                            *temp_a1 = *temp_a3 + D_80146D58;
                            *temp_a2 = (D_80146D54 - *temp_a2) * 1.414214f;
                            *temp_a3 = (D_80146D58 - *temp_a3) * 1.414214f;

                            var_s0 = &arg2[spC0];
                            var_s1 = &var_s0[sp58];
                            var_s2 = &var_s1[sp58];
                            var_s3 = &var_s2[sp58];
                            for (spC8 = 1; spC8 < spB4; spC8++) {
                                temp_a0 = arg0 + spCC + spC8;
                                temp_a1 = temp_a0 + sp50;
                                temp_a2 = temp_a1 + sp50;
                                temp_a3 = temp_a2 + sp50;

                                temp_b0 = arg0 + spCC + sp50 - spC8;
                                temp_b1 = temp_b0 + sp50;
                                temp_b2 = temp_b1 + sp50;
                                temp_b3 = temp_b2 + sp50;

                                D_80146D54 = *temp_a0;
                                D_80146D58 = *temp_a1;
                                D_80146D5C = *temp_a2;
                                D_80146D60 = *temp_a3;

                                D_80146D64 = *temp_b0;
                                D_80146D68 = *temp_b1;
                                D_80146D6C = *temp_b2;
                                D_80146D70 = *temp_b3;

                                *temp_a0 = D_80146D54 + D_80146D5C;
                                *temp_a1 = D_80146D58 + D_80146D60;
                                *temp_a2 = ((D_80146D54 - D_80146D5C + D_80146D64 - D_80146D6C) * *var_s0) +
                                           ((D_80146D60 - D_80146D58 + D_80146D68 - D_80146D70) * *var_s1);
                                *temp_a3 = ((D_80146D54 - D_80146D5C - D_80146D64 + D_80146D6C) * *var_s2) -
                                           ((D_80146D60 - D_80146D58 - D_80146D68 + D_80146D70) * *var_s3);
                                *temp_b0 = D_80146D64 + D_80146D6C;
                                *temp_b1 = D_80146D68 + D_80146D70;
                                *temp_b2 = ((D_80146D54 - D_80146D5C + D_80146D64 - D_80146D6C) * *var_s1) -
                                           ((D_80146D60 - D_80146D58 + D_80146D68 - D_80146D70) * *var_s0);
                                *temp_b3 = ((D_80146D54 - D_80146D5C - D_80146D64 + D_80146D6C) * *var_s3) +
                                           ((D_80146D60 - D_80146D58 - D_80146D68 + D_80146D70) * *var_s2);
                                var_s0 += spC0;
                                var_s1 += spC0;
                                var_s2 += spC0;
                                var_s3 += spC0;
                            }
                        }
                    }
                    var_a0 = ((spA8 * 2) - spBC) + 1;
                    spA8 *= 4;
                } while (var_a0 < length);
                spC0 = spC0 * 2;
                temp_a0 = arg0;
                for (spC8 = 0; spC8 < length; spC8++, temp_a0++) {
                    *temp_a0 /= 1.414214f;
                }
            }
            var_a0 = 1;
            spA8 = 4;

            do {
                for (spCC = var_a0 - 1; spCC < length; spCC += spA8) {
                    D_80146D54 = arg0[spCC];
                    arg0[spCC] = arg0[spCC + 1] + D_80146D54;
                    arg0[spCC + 1] = D_80146D54 - arg0[spCC + 1];
                }
                var_a0 = (spA8 * 2) - 1;
                spA8 *= 4;
            } while (var_a0 < length);
            temp_a0 = arg0;
            for (spC8 = 0; spC8 < length; spC8++) {
                *temp_a0++ /= 1.414214f;
            }
            spB4 = 1;
            temp_a0 = arg0;

            for (spC8 = 1; spC8 < length; spC8++) {
                if (spC8 < spB4) {
                    D_80146D54 = arg0[spB4 - 1];
                    arg0[spB4 - 1] = *temp_a0;
                    *temp_a0 = D_80146D54;
                }
                temp_a0++;
                spC0 = length >> 1;
                while (spC0 < spB4) {
                    spB4 -= spC0;
                    spC0 >>= 1;
                }
                spB4 += spC0;
            }
            break;
    }
}
#else
#pragma GLOBAL_ASM("asm/us/rev1/nonmatchings/audio/audio_synthesis/AudioSynth_HartleyTransform.s")
#endif

// https://decomp.me/scratch/TZQNS
#ifdef NON_MATCHING
void func_80009124(s16** arg0) {
    s16* var_a1;
    s32 temp_a0;
    u8 temp_s0;
    u8 temp_s1;
    u8 temp_u1;
    s32 temp_t5_4;
    s32 temp_v0;
    u8 temp_v1;
    s32 var_s1;
    s32 var_t2;
    s32 var_v1;
    u16 var_s0;
    u32 var_t3;
    s32 i;
    s32 j;
    s16 new_var2;

    var_a1 = *arg0;

    for (i = 255; i >= 0; i--) {
        D_80145D48[i] = 0.0f;
    }
    temp_v0 = *var_a1++;
    var_t3 = temp_v0 << 0x10;
    temp_v0 = *var_a1++;
    var_t3 |= temp_v0;

    for (var_t2 = 0; var_t2 < 4; var_t2++) {
        var_v1 = var_t2 * 0x40;
        temp_s0 = var_t3 >> 0x18;

        var_t3 <<= 8;

        temp_v1 = ((temp_s0 >> 4) & 0xF);
        temp_a0 = temp_s0 & 0xF;
        if (temp_v1 == 0) {
            continue;
        }
        switch (temp_v1) {
            case 1:
                while (true) {
                    var_s0 = *var_a1++;
                    for (var_s1 = 0; var_s1 < 4; var_s1++) {
                        temp_u1 = (var_s0 >> 0xC) & 0xF;
                        var_s0 <<= 4;
                        D_80145D48[var_v1++] = ((temp_u1 & 7) - 4) << temp_a0;
                        if (temp_u1 >= 8) {
                            goto case_1_break;
                        }
                    }
                }
            case_1_break:
                break;
            case 2:
                for (var_s1 = 0; var_s1 < 16; var_s1++) {
                    var_s0 = *var_a1++;
                    for (i = 0; i < 4; i++) {
                        temp_u1 = (var_s0 >> 0xC) & 0xF;
                        var_s0 <<= 4;
                        D_80145D48[var_v1++] = (temp_u1 - 8) << temp_a0;
                    }
                }
                break;
            case 6:
                while (true) {
                    var_s0 = *var_a1++;
                    temp_u1 = (var_s0 >> 8) & 0xFF;
                    temp_t5_4 = temp_u1 >> 6;
                    D_80145D48[var_v1] = ((temp_u1 & 0x3F) - 0x20) << temp_a0;
                    if (temp_t5_4 == 0) {
                        break;
                    }
                    var_v1 += temp_t5_4;
                    temp_u1 = var_s0 & 0xFF;
                    temp_t5_4 = temp_u1 >> 6;
                    D_80145D48[var_v1] = ((temp_u1 & 0x3F) - 0x20) << temp_a0;
                    if (temp_t5_4 == 0) {
                        break;
                    }
                    var_v1 += temp_t5_4;
                }
                break;
            case 3:
                while (true) {
                    var_s0 = *var_a1++;
                    temp_u1 = (var_s0 >> 8) & 0xFF;

                    D_80145D48[var_v1++] = ((temp_u1 & 0x7F) - 0x40) << temp_a0;

                    if (temp_u1 >= 0x80) {
                        break;
                    }
                    temp_u1 = var_s0 & 0xFF;
                    D_80145D48[var_v1++] = ((temp_u1 & 0x7F) - 0x40) << temp_a0;
                    if (temp_u1 >= 0x80) {
                        break;
                    }
                }
                break;
            case 4:
                while (true) {
                    var_s0 = *var_a1++;
                    temp_t5_4 = var_s0 >> 0xC;
                    D_80145D48[var_v1] = ((var_s0 & 0xFFF) - 0x800) << temp_a0;
                    if (temp_t5_4 == 0) {
                        break;
                    }
                    var_v1 += temp_t5_4;
                }
                break;
            case 5:
                while (true) {
                    var_s0 = *var_a1++;
                    temp_t5_4 = var_s0 >> 0xF;
                    D_80145D48[var_v1] = ((var_s0 & 0x7FFF) - 0x4000) << temp_a0;
                    if (temp_t5_4 == 1) {
                        break;
                    }
                    var_v1++;
                }
                break;
        }
    }
    *arg0 = var_a1;
}
#else
void func_80009124(s16** arg0);
#pragma GLOBAL_ASM("asm/us/rev1/nonmatchings/audio/audio_synthesis/func_80009124.s")
#endif

void func_80009504(s16* arg0, UnkStruct_800097A8* arg1) {
    s32 i;

    if (arg1->unk_0 != NULL) {
        arg1->unk_C = arg1->unk_0;
        arg1->unk_0 = 0;
    }

    arg1->unk18 += D_8014C1B4;
    while (arg1->unk18 > 0x1000) {
        func_80009124(&arg1->unk_C);
        arg1->unk18 -= 0x1000;
    }

    AudioSynth_InverseDiscreteCosineTransform(D_80145D48, D_80146148, 8, D_80146548);

    for (i = 0; i < 256; i++) {
        if (D_80145D48[i] > 32767.0f) {
            D_80145D48[i] = 32767.0f;
        }
        if (D_80145D48[i] < -32767.0f) {
            D_80145D48[i] = -32767.0f;
        }
    }

    for (i = 0; i < 0x100; i++, arg0++) {
        *arg0 = D_80145D48[i];
    }
}

s32 func_8000967C(s32 length, s16* ramAddr, UnkStruct_800097A8* arg2) {
    s32 pad;
    s32 temp_t0;
    s32 i;
    s32 var_s1;
    s16* temp_t7 = (s16*) arg2->unk_14->ramAddr;

    for (i = 0; i < arg2->unk_4; i++) {
        ramAddr[i] = temp_t7[i];
    }

    var_s1 = arg2->unk_4;
    temp_t0 = (length - arg2->unk_4 + 0xFF) / 256;
    arg2->unk_4 = (temp_t0 * 256) + arg2->unk_4 - length;

    for (i = 0; i < temp_t0; i++) {
        func_80009504(&ramAddr[var_s1], arg2);
        var_s1 += 0x100;
    }

    for (i = 0; i < arg2->unk_4; i++) {
        temp_t7[i] = ramAddr[length + i];
    }
    return temp_t0;
}

u8* func_800097A8(Sample* sample, s32 length, u32 flags, UnkStruct_800097A8* arg3) {
    // @port: We don't need to do a dma call
    // return sample->sampleAddr;
    s32 pad1;
    SampleDma* pad2;
    SampleDma* sp1C = NULL;

    if (flags == A_INIT) {
        arg3->unk_0 = (s16*) sample->sampleAddr;
        arg3->unk_4 = 0;
        arg3->unk_8 = 0;
        arg3->unk18 = 0;

        if (gSampleDmaReuseQueue1RdPos != gSampleDmaReuseQueue1WrPos) {
            arg3->unk_14 = &gSampleDmas[gSampleDmaReuseQueue1[gSampleDmaReuseQueue1RdPos++]];
            arg3->unk_14->devAddr = -1;
            arg3->unk_14->sizeUnused = 0;
        }
    }

    if (gSampleDmaReuseQueue1RdPos != gSampleDmaReuseQueue1WrPos) {
        sp1C = &gSampleDmas[gSampleDmaReuseQueue1[gSampleDmaReuseQueue1RdPos++]];
    }

    if (1) {} //! FAKE

    sp1C->ttl = 2;
    // @port: (uintptr_t)
    sp1C->devAddr = (uintptr_t) sample->sampleAddr;
    sp1C->sizeUnused = length * 2;
    pad2 = arg3->unk_14;
    pad2->ttl = 2;
    arg3->unk_8 += func_8000967C(length, (s16*) sp1C->ramAddr, arg3);
    return sp1C->ramAddr;
}

Acmd* AudioSynth_LoadRingBufferPart(Acmd* aList, u16 dmem, u16 startPos, s32 size, s32 reverbIndex) {
    aLoadBuffer(aList++, OS_K0_TO_PHYSICAL(&gSynthReverbs[reverbIndex].leftRingBuf[startPos]), dmem, size);
    aLoadBuffer(aList++, OS_K0_TO_PHYSICAL(&gSynthReverbs[reverbIndex].rightRingBuf[startPos]), dmem + DMEM_1CH_SIZE,
                size);
    return aList;
}

Acmd* AudioSynth_SaveRingBufferPart(Acmd* aList, u16 dmem, u16 startPos, s32 size, s32 reverbIndex) {
    aSaveBuffer(aList++, dmem, OS_K0_TO_PHYSICAL(&gSynthReverbs[reverbIndex].leftRingBuf[startPos]), size);
    aSaveBuffer(aList++, dmem + DMEM_1CH_SIZE, OS_K0_TO_PHYSICAL(&gSynthReverbs[reverbIndex].rightRingBuf[startPos]),
                size);
    return aList;
}

void AudioSynth_DisableSampleStates(s32 updateIndex, s32 noteIndex) {
    NoteSubEu* noteSubEu;
    s32 i;

    for (i = updateIndex + 1; i < gAudioBufferParams.ticksPerUpdate; i++) {
        if (!gNoteSubsEu[(gNumNotes * i) + noteIndex].bitField0.needsInit) {
            gNoteSubsEu[(gNumNotes * i) + noteIndex].bitField0.enabled = false;
        } else {
            break;
        }
    }
}

/**
 * Sync the sample states between the notes and the list
 */
void AudioSynth_SyncSampleStates(s32 updateIndex) {
    NoteSubEu* noteSampleState;
    NoteSubEu* sampleState;
    s32 i;

    for (i = 0; i < gNumNotes; i++) {
        noteSampleState = &gNotes[i].noteSubEu;
        sampleState = &gNoteSubsEu[gNumNotes * updateIndex + i];
        if (noteSampleState->bitField0.enabled) {
            *sampleState = *noteSampleState;
            noteSampleState->bitField0.needsInit = false;
        } else {
            sampleState->bitField0.enabled = false;
        }
    }
}

Acmd* AudioSynth_Update(Acmd* aList, s32* cmdCount, s16* aiBufStart, s32 aiBufLen) {
    Acmd* aCmdPtr;
    s16* aiBufPtr;
    s32 chunkLen;
    s32 i;
    s32 j;

    aCmdPtr = aList;
    for (i = gAudioBufferParams.ticksPerUpdate; i > 0; i--) {
        AudioSeq_ProcessSequences(i - 1);
        AudioSynth_SyncSampleStates(gAudioBufferParams.ticksPerUpdate - i);
    }

    aiBufPtr = aiBufStart;
    for (i = gAudioBufferParams.ticksPerUpdate; i > 0; i--) {
        if (i == 1) {
            chunkLen = aiBufLen;
        } else if ((aiBufLen / i) >= gAudioBufferParams.samplesPerTickMax) {
            chunkLen = gAudioBufferParams.samplesPerTickMax;
        } else if (gAudioBufferParams.samplesPerTickMin >= (aiBufLen / i)) {
            chunkLen = gAudioBufferParams.samplesPerTickMin;
        } else {
            chunkLen = gAudioBufferParams.samplesPerTick;
        }

        for (j = 0; j < gNumSynthReverbs; j++) {
            if (gSynthReverbs[j].useReverb) {
                AudioSynth_InitNextRingBuf(chunkLen, gAudioBufferParams.ticksPerUpdate - i, j);
            }
        }

        aCmdPtr =
            AudioSynth_DoOneAudioUpdate((s16*) aiBufPtr, chunkLen, aCmdPtr, gAudioBufferParams.ticksPerUpdate - i);
        aiBufLen -= chunkLen;
        aiBufPtr += chunkLen * 2;
    }

    for (j = 0; j < gNumSynthReverbs; j++) {
        if (gSynthReverbs[j].framesToIgnore != 0) {
            gSynthReverbs[j].framesToIgnore--;
        }
        gSynthReverbs[j].curFrame ^= 1;
    }

    *cmdCount = aCmdPtr - aList;

    return aCmdPtr;
}

Acmd* AudioSynth_LoadReverbSamples(Acmd* aList, s32 aiBufLen, s16 reverbIndex, s16 updateIndex) {
    ReverbRingBufferItem* sp64 = &gSynthReverbs[reverbIndex].items[gSynthReverbs[reverbIndex].curFrame][updateIndex];
    s16 sp62;
    s16 sp60;

    aClearBuffer(aList++, DMEM_WET_LEFT_CH, DMEM_2CH_SIZE);

    if (gSynthReverbs[reverbIndex].downsampleRate == 1) {
        aList = AudioSynth_LoadRingBufferPart(aList, DMEM_WET_LEFT_CH, sp64->startPos, sp64->lengthA, reverbIndex);
        if (sp64->lengthB != 0) {
            aList =
                AudioSynth_LoadRingBufferPart(aList, sp64->lengthA + DMEM_WET_LEFT_CH, 0, sp64->lengthB, reverbIndex);
        }
        aAddMixer(aList++, 0x300, DMEM_WET_LEFT_CH, DMEM_LEFT_CH);
        aMix(aList++, 0x30, gSynthReverbs[reverbIndex].decayRatio + 0x8000, DMEM_WET_LEFT_CH, DMEM_WET_LEFT_CH);
    } else {
        sp62 = (sp64->startPos & 7) * 2;
        sp60 = ALIGN16(sp62 + sp64->lengthA);
        aList = AudioSynth_LoadRingBufferPart(aList, DMEM_WET_SCRATCH, sp64->startPos - (sp62 / 2), DMEM_1CH_SIZE,
                                              reverbIndex);
        if (sp64->lengthB != 0) {
            aList = AudioSynth_LoadRingBufferPart(aList, sp60 + DMEM_WET_SCRATCH, 0, DMEM_1CH_SIZE - sp60, reverbIndex);
        }
        aSetBuffer(aList++, 0, sp62 + DMEM_WET_SCRATCH, DMEM_WET_LEFT_CH, aiBufLen * 2);
        aResample(aList++, gSynthReverbs[reverbIndex].resampleFlags, gSynthReverbs[reverbIndex].unk_0A,
                  OS_K0_TO_PHYSICAL(gSynthReverbs[reverbIndex].unk_30));
        aSetBuffer(aList++, 0, sp62 + DMEM_UNCOMPRESSED_NOTE, DMEM_WET_RIGHT_CH, aiBufLen * 2);
        aResample(aList++, gSynthReverbs[reverbIndex].resampleFlags, gSynthReverbs[reverbIndex].unk_0A,
                  OS_K0_TO_PHYSICAL(gSynthReverbs[reverbIndex].unk_34));
        aAddMixer(aList++, 0x300, DMEM_WET_LEFT_CH, DMEM_LEFT_CH);
        aMix(aList++, 0x30, gSynthReverbs[reverbIndex].decayRatio + 0x8000, DMEM_WET_LEFT_CH, DMEM_WET_LEFT_CH);
    }

    if ((gSynthReverbs[reverbIndex].leakRtL != 0) || (gSynthReverbs[reverbIndex].leakLtR != 0)) {
        aDMEMMove(aList++, DMEM_WET_LEFT_CH, DMEM_WET_SCRATCH, DMEM_1CH_SIZE);
        aMix(aList++, DMEM_1CH_SIZE >> 4, gSynthReverbs[reverbIndex].leakRtL, DMEM_WET_RIGHT_CH, DMEM_WET_LEFT_CH);
        aMix(aList++, DMEM_1CH_SIZE >> 4, gSynthReverbs[reverbIndex].leakLtR, DMEM_WET_SCRATCH, DMEM_WET_RIGHT_CH);
    }
    return aList;
}

Acmd* AudioSynth_SaveReverbSamples(Acmd* aList, s16 reverbIndex, s16 updateIndex) {
    ReverbRingBufferItem* sp24;
    sp24 = &gSynthReverbs[reverbIndex].items[gSynthReverbs[reverbIndex].curFrame][updateIndex];
    switch (gSynthReverbs[reverbIndex].downsampleRate) {
        case 1:
            aList = AudioSynth_SaveRingBufferPart(aList, DMEM_WET_LEFT_CH, sp24->startPos, sp24->lengthA, reverbIndex);
            if (sp24->lengthB != 0) {
                aList = AudioSynth_SaveRingBufferPart(aList, sp24->lengthA + DMEM_WET_LEFT_CH, 0, sp24->lengthB,
                                                      reverbIndex);
            }
            break;

        default:
            aSaveBuffer(aList++, DMEM_WET_LEFT_CH,
                        OS_K0_TO_PHYSICAL(gSynthReverbs[reverbIndex]
                                              .items[gSynthReverbs[reverbIndex].curFrame][updateIndex]
                                              .toDownsampleLeft),
                        0x300);
            gSynthReverbs[reverbIndex].resampleFlags = 0;
            break;
    }

    return aList;
}

Acmd* AudioSynth_DoOneAudioUpdate(s16* aiBuf, s32 aiBufLen, Acmd* aList, s32 updateIndex) {
    u8 sp84[0x3C];
    NoteSubEu* temp_v0;
    s16 count;
    s16 i = 0;
    s32 j = 0;

    count = 0;
    if (gNumSynthReverbs == 0) {
        for (j = 0; j < gNumNotes; j++) {
            if (gNoteSubsEu[gNumNotes * updateIndex + j].bitField0.enabled) {
                sp84[count++] = j;
            }
        }
    } else {
        for (i = 0; i < gNumSynthReverbs; i++) {
            for (j = 0; j < gNumNotes; j++) {
                temp_v0 = &gNoteSubsEu[gNumNotes * updateIndex + j];
                if (temp_v0->bitField0.enabled && (temp_v0->bitField1.reverbIndex == i)) {
                    sp84[count++] = j;
                }
            }
        }
        for (j = 0; j < gNumNotes; j++) {
            temp_v0 = &gNoteSubsEu[gNumNotes * updateIndex + j];
            if (temp_v0->bitField0.enabled && (temp_v0->bitField1.reverbIndex >= gNumSynthReverbs)) {
                sp84[count++] = j;
            }
        }
    }

    aClearBuffer(aList++, DMEM_LEFT_CH, DMEM_2CH_SIZE);

    j = 0;
    for (i = 0; i < gNumSynthReverbs; i++) {
        D_8014C1B2 = gSynthReverbs[i].useReverb;
        if (D_8014C1B2) {
            aList = AudioSynth_LoadReverbSamples(aList, aiBufLen, i, updateIndex);
        }
        while (j < count) {
            if (i != gNoteSubsEu[updateIndex * gNumNotes + sp84[j]].bitField1.reverbIndex) {
                break;
            }
            aList = AudioSynth_ProcessNote(sp84[j], &gNoteSubsEu[updateIndex * gNumNotes + sp84[j]],
                                           &gNotes[sp84[j]].synthesisState, aiBuf, aiBufLen, aList, updateIndex);
            j++;
        }
        if (gSynthReverbs[i].useReverb) {
            aList = AudioSynth_SaveReverbSamples(aList, i, updateIndex);
        }
    }

    while (j < count) {
        aList = AudioSynth_ProcessNote(sp84[j], &gNoteSubsEu[updateIndex * gNumNotes + sp84[j]],
                                       &gNotes[sp84[j]].synthesisState, aiBuf, aiBufLen, aList, updateIndex);
        j++;
    }

    j = aiBufLen * 2;
    aSetBuffer(aList++, 0, 0, DMEM_TEMP, j);
    aInterleave(aList++, DMEM_LEFT_CH, DMEM_RIGHT_CH);
    aSaveBuffer(aList++, DMEM_TEMP, OS_K0_TO_PHYSICAL(aiBuf), j * 2);

    return aList;
}

Acmd* AudioSynth_ProcessNote(s32 noteIndex, NoteSubEu* noteSub, NoteSynthesisState* synthState, s16* aiBuf,
                             s32 aiBufLen, Acmd* aList, s32 updateIndex) {
    s32 pad11C[3];
    Sample* bookSample;
    AdpcmLoop* loopInfo;
    void* currentBook;
    s32 pad104[2];
    bool sampleFinished;
    bool loopToPoint;
    s32 flags;
    u16 resampleRateFixedPoint;
    s32 numSamplesToLoad;
    s32 padE8[3];
    s32 skipBytes = 0;
    s32 padD8[3];
    uintptr_t sampleAddr;
    s32 padC8;
    s32 numSamplesToLoadAdj;
    s32 numSamplesProcessed;
    u32 endPos;
    s32 nSamplesToProcess;
    s32 padB4[5];
    s32 numTrailingSamplesToIgnore;
    s32 pad9C[3];
    s32 frameSize;
    s32 pad8C;
    s32 skipInitialSamples;
    s32 sampleDmaStart;
    s32 pad80;
    s32 numParts;
    s32 curPart;
    s32 numSamplesInThisIteration;
    s32 sampleDataChunkAlignPad;
    s32 resampledTempLen;
    u16 noteSamplesDmemAddrBeforeResampling;
    s32 pasdasd;
    s32 frameIndex;
    uintptr_t sampleDataOffset;
    Note* note;
    u16 sp56;
    s32 numSamplesInFirstFrame;
    s32 delaySide;
    s32 nFramesToDecode;
    s32 nFirstFrameSamplesToIgnore;
    s32 dmemUncompressedAddrOffset1;
    u32 sampleslenFixedPoint;
    u8* samplesToLoadAddr;
    s32 gain;
    u32 nEntries;
    s32 aligned;
    s16 addr;
    s32 samplesRemaining;
    s32 numSamplesToDecode;
    uintptr_t buffAddr;

    currentBook = NULL;
    note = &gNotes[noteIndex];
    flags = A_CONTINUE;

    if (noteSub->bitField0.needsInit == 1) {
        flags = A_INIT;
        synthState->restart = 0;
        synthState->samplePosInt = 0;
        synthState->samplePosFrac = 0;
        synthState->curVolLeft = 0;
        synthState->curVolRight = 0;
        synthState->numParts = synthState->prevHaasEffectRightDelaySize = synthState->prevHaasEffectLeftDelaySize = 0;
        note->noteSubEu.bitField0.finished = 0;
    }

    resampleRateFixedPoint = noteSub->resampleRate;
    numParts = noteSub->bitField1.hasTwoParts + 1;
    sampleslenFixedPoint = ((resampleRateFixedPoint * aiBufLen) * 2) + synthState->samplePosFrac;
    numSamplesToLoad = sampleslenFixedPoint >> 16;
    synthState->samplePosFrac = sampleslenFixedPoint & 0xFFFF;

    if ((synthState->numParts == 1) && (numParts == 2)) {
        numSamplesToLoad += 2;
        sp56 = 2;
    } else if ((synthState->numParts == 2) && (numParts == 1)) {
        numSamplesToLoad -= 4;
        sp56 = 4;
    } else {
        sp56 = 0;
    }

    synthState->numParts = numParts;
    if (noteSub->bitField1.isSyntheticWave) {
        aList = AudioSynth_LoadWaveSamples(aList, noteSub, synthState, numSamplesToLoad);
        noteSamplesDmemAddrBeforeResampling = DMEM_UNCOMPRESSED_NOTE + (synthState->samplePosInt * SAMPLE_SIZE);
        synthState->samplePosInt += numSamplesToLoad;
    } else {
        bookSample = *(noteSub->waveSampleAddr);
        loopInfo = bookSample->loop;

        endPos = loopInfo->end;
        sampleAddr = bookSample->sampleAddr;
        resampledTempLen = 0;

        for (curPart = 0; curPart < numParts; curPart++) {
            numSamplesProcessed = 0;
            dmemUncompressedAddrOffset1 = 0;

            if (numParts == 1) {
                numSamplesToLoadAdj = numSamplesToLoad;
            } else if (numSamplesToLoad & 1) {
                numSamplesToLoadAdj = (numSamplesToLoad & ~1) + (curPart * 2);
            } else {
                numSamplesToLoadAdj = numSamplesToLoad;
            }

            if ((bookSample->codec == CODEC_ADPCM) && (currentBook != bookSample->book->book)) {
                switch (noteSub->bitField1.bookOffset) {
                    case 1:
                        currentBook = &gD_800DD200[1];
                        break;

                    case 2:
                        currentBook = &gD_800DD200[2];
                        break;

                    default:

                    case 3:
                        currentBook = bookSample->book->book;
                        break;
                }

                nEntries = (SAMPLES_PER_FRAME * bookSample->book->order) * bookSample->book->numPredictors;
                aLoadADPCM(aList++, nEntries, OS_K0_TO_PHYSICAL(currentBook));
            }

            while (numSamplesProcessed != numSamplesToLoadAdj) {
                sampleFinished = false;
                loopToPoint = false;

                samplesRemaining = endPos - synthState->samplePosInt;
                nSamplesToProcess = numSamplesToLoadAdj - numSamplesProcessed;

                nFirstFrameSamplesToIgnore = synthState->samplePosInt & 0xF;

                if ((nFirstFrameSamplesToIgnore == 0) && (!synthState->restart)) {
                    nFirstFrameSamplesToIgnore = SAMPLES_PER_FRAME;
                }

                numSamplesInFirstFrame = SAMPLES_PER_FRAME - nFirstFrameSamplesToIgnore;

                if (nSamplesToProcess < samplesRemaining) {
                    nFramesToDecode =
                        ((nSamplesToProcess - numSamplesInFirstFrame) + SAMPLES_PER_FRAME - 1) / SAMPLES_PER_FRAME;
                    numSamplesToDecode = nFramesToDecode * SAMPLES_PER_FRAME;
                    numTrailingSamplesToIgnore = (numSamplesInFirstFrame + numSamplesToDecode) - nSamplesToProcess;
                } else {
                    numSamplesToDecode = samplesRemaining - numSamplesInFirstFrame;
                    numTrailingSamplesToIgnore = 0;
                    if (numSamplesToDecode <= 0) {
                        numSamplesToDecode = 0;
                        numSamplesInFirstFrame = samplesRemaining;
                    }

                    nFramesToDecode = (numSamplesToDecode + SAMPLES_PER_FRAME - 1) / SAMPLES_PER_FRAME;
                    if (loopInfo->count != 0) {
                        // Loop around and restart
                        loopToPoint = true;
                    } else {
                        sampleFinished = true;
                    }
                }

                switch (bookSample->codec) {
                    case CODEC_ADPCM:
                        frameSize = 9;
                        skipInitialSamples = SAMPLES_PER_FRAME;
                        sampleDmaStart = 0;
                        break;

                    case CODEC_S8:
                        frameSize = 16;
                        skipInitialSamples = SAMPLES_PER_FRAME;
                        sampleDmaStart = 0;
                        break;

                   case CODEC_S16_INMEMORY:
                        buffAddr = func_800097A8(bookSample, numSamplesToLoadAdj, flags,
                                                 &synthState->synthesisBuffers->unk_40);
                        aLoadBuffer(aList++, OS_K0_TO_PHYSICAL(buffAddr), DMEM_UNCOMPRESSED_NOTE,
                                    (numSamplesToLoadAdj + SAMPLES_PER_FRAME) * 2);
                        flags = A_CONTINUE;
                        skipBytes = 0;
                        numSamplesProcessed = numSamplesToLoadAdj;
                        dmemUncompressedAddrOffset1 = numSamplesToLoadAdj;
                        goto skip;

                    case CODEC_S16:
                        aLoadBuffer(aList++, OS_K0_TO_PHYSICAL(bookSample->sampleAddr + synthState->samplePosInt * 2), DMEM_UNCOMPRESSED_NOTE,
                                    (numSamplesToLoadAdj + SAMPLES_PER_FRAME) * 2);
                        flags = A_CONTINUE;
                        skipBytes = 0;
                        numSamplesProcessed = numSamplesToLoadAdj;
                        dmemUncompressedAddrOffset1 = numSamplesToLoadAdj;

                        goto skip;
                }

                aligned = ALIGN16((nFramesToDecode * frameSize) + 0x10);
                addr = DMEM_COMPRESSED_ADPCM_DATA - aligned;

#if __SANITIZE_ADDRESS__
                uintptr_t actualAddrLoaded = samplesToLoadAddr - sampleDataChunkAlignPad;
                uintptr_t offset = actualAddrLoaded - (uintptr_t)sampleAddr;
                if (offset + aligned > bookSample->size) {
                    aligned -= (offset + aligned - bookSample->size);
                }
#endif
                if (nFramesToDecode != 0) {
                    if (1) {}
                    frameIndex = (synthState->samplePosInt + skipInitialSamples - nFirstFrameSamplesToIgnore) / 16;
                    sampleDataOffset = frameIndex * frameSize;
                    samplesToLoadAddr = (u8*) (sampleDmaStart + sampleDataOffset + sampleAddr);
                    sampleDataChunkAlignPad = ((uintptr_t) samplesToLoadAddr) % SAMPLES_PER_FRAME;

                    aLoadBuffer(aList++, OS_K0_TO_PHYSICAL(samplesToLoadAddr - sampleDataChunkAlignPad), addr, aligned);
                } else {
                    numSamplesToDecode = 0;
                    sampleDataChunkAlignPad = 0;
                }

                if (synthState->restart) {
                    aSetLoop(aList++, OS_K0_TO_PHYSICAL(bookSample->loop->predictorState));
                    flags = A_LOOP;
                    synthState->restart = 0;
                }

                numSamplesInThisIteration = (numSamplesToDecode + numSamplesInFirstFrame) - numTrailingSamplesToIgnore;

                if (numSamplesProcessed == 0) {
                    switch (bookSample->codec) {
                        case 0:
                            aSetBuffer(aList++, 0, addr + sampleDataChunkAlignPad, DMEM_UNCOMPRESSED_NOTE,
                                       numSamplesToDecode * SAMPLE_SIZE);
                            aADPCMdec(aList++, flags, OS_K0_TO_PHYSICAL(synthState->synthesisBuffers));
                            break;

                        case 1:
                            aSetBuffer(aList++, 0, addr + sampleDataChunkAlignPad, DMEM_UNCOMPRESSED_NOTE,
                                       numSamplesToDecode * SAMPLE_SIZE);
                            aS8Dec(aList++, flags, OS_K0_TO_PHYSICAL(synthState->synthesisBuffers));
                            break;
                    }

                    skipBytes = nFirstFrameSamplesToIgnore * SAMPLE_SIZE;
                } else {
                    aligned = ALIGN16(dmemUncompressedAddrOffset1 + SAMPLES_PER_FRAME);
                    switch (bookSample->codec) {
                        case 0:
                            aSetBuffer(aList++, 0, addr + sampleDataChunkAlignPad, DMEM_UNCOMPRESSED_NOTE + aligned,
                                       numSamplesToDecode * SAMPLE_SIZE);
                            aADPCMdec(aList++, flags, OS_K0_TO_PHYSICAL(synthState->synthesisBuffers));
                            break;

                        case 1:
                            aSetBuffer(aList++, 0, addr + sampleDataChunkAlignPad, DMEM_UNCOMPRESSED_NOTE + aligned,
                                       numSamplesToDecode * SAMPLE_SIZE);
                            aS8Dec(aList++, flags, OS_K0_TO_PHYSICAL(synthState->synthesisBuffers));
                            break;
                    }

                    aDMEMMove(aList++, DMEM_UNCOMPRESSED_NOTE + aligned + (nFirstFrameSamplesToIgnore * SAMPLE_SIZE),
                              DMEM_UNCOMPRESSED_NOTE + dmemUncompressedAddrOffset1,
                              numSamplesInThisIteration * SAMPLE_SIZE);
                }

                numSamplesProcessed += numSamplesInThisIteration;

                switch (flags) {
                    case A_INIT:
                        skipBytes = SAMPLES_PER_FRAME * SAMPLE_SIZE;
                        dmemUncompressedAddrOffset1 = (numSamplesToDecode + SAMPLES_PER_FRAME) * SAMPLE_SIZE;
                        break;

                    case A_LOOP:
                        dmemUncompressedAddrOffset1 =
                            (numSamplesInThisIteration * SAMPLE_SIZE) + dmemUncompressedAddrOffset1;
                        break;

                    default:
                        if (dmemUncompressedAddrOffset1 != 0) {
                            dmemUncompressedAddrOffset1 =
                                (numSamplesInThisIteration * SAMPLE_SIZE) + dmemUncompressedAddrOffset1;
                        } else {
                            dmemUncompressedAddrOffset1 =
                                (nFirstFrameSamplesToIgnore + numSamplesInThisIteration) * SAMPLE_SIZE;
                        }
                        break;
                }

            skip:

                flags = A_CONTINUE;

                if (sampleFinished) {
                    aClearBuffer(aList++, DMEM_UNCOMPRESSED_NOTE + dmemUncompressedAddrOffset1,
                                 (numSamplesToLoadAdj - numSamplesProcessed) * SAMPLE_SIZE);
                    noteSub->bitField0.finished = true;
                    note->noteSubEu.bitField0.finished = true;
                    AudioSynth_DisableSampleStates(updateIndex, noteIndex);
                    break;
                }

                if (loopToPoint) {
                    synthState->restart = true;
                    synthState->samplePosInt = loopInfo->start;
                } else {
                    synthState->samplePosInt += nSamplesToProcess;
                }
            }

            switch (numParts) {
                case 1:
                    noteSamplesDmemAddrBeforeResampling = DMEM_UNCOMPRESSED_NOTE + skipBytes;
                    break;

                case 2:
                    switch (curPart) {
                        case 0:
                            aInterl(aList++, skipBytes + DMEM_UNCOMPRESSED_NOTE, DMEM_WET_SCRATCH, ALIGN8(numSamplesToLoadAdj / 2));
                            resampledTempLen = numSamplesToLoadAdj;
                            noteSamplesDmemAddrBeforeResampling = DMEM_WET_SCRATCH;
                            if (noteSub->bitField0.finished) {
                                aClearBuffer(aList++, resampledTempLen + noteSamplesDmemAddrBeforeResampling,
                                             numSamplesToLoadAdj + SAMPLES_PER_FRAME);
                            }
                            break;

                        case 1:
                            aInterl(aList++, skipBytes + DMEM_UNCOMPRESSED_NOTE, resampledTempLen + DMEM_WET_SCRATCH,
                                    ALIGN8(numSamplesToLoadAdj / 2));
                            break;
                    }

                    break;
            }

            if (noteSub->bitField0.finished) {
                break;
            }
        }
    }

    flags = A_CONTINUE;
    if (noteSub->bitField0.needsInit == true) {
        flags = A_INIT;
        noteSub->bitField0.needsInit = false;
    }

    flags = sp56 | flags;

    aList = AudioSynth_FinalResample(aList, synthState, aiBufLen * SAMPLE_SIZE, resampleRateFixedPoint,
                                     noteSamplesDmemAddrBeforeResampling, flags);

    if (flags & A_INIT) {
        flags = A_INIT;
    }

    if (noteSub->bitField1.bookOffset == 3) {
        aUnkCmd19(aList++, 0, aiBufLen * SAMPLE_SIZE, DMEM_TEMP, DMEM_TEMP);
    }

    gain = noteSub->gain;
    if (gain != 0) {
        // A gain of 0x10 (a UQ4.4 number) is equivalent to 1.0 and represents no volume change
        if (gain < 0x10) {
            gain = 0x10;
        }
        aHiLoGain(aList++, gain, (aiBufLen + SAMPLES_PER_FRAME) * SAMPLE_SIZE, DMEM_TEMP, 0);
    }

    if ((noteSub->leftDelaySize != 0) || (synthState->prevHaasEffectLeftDelaySize != 0)) {
        delaySide = HAAS_EFFECT_DELAY_LEFT;
    } else if ((noteSub->rightDelaySize != 0) || (synthState->prevHaasEffectRightDelaySize != 0)) {
        delaySide = HAAS_EFFECT_DELAY_RIGHT;
    } else {
        delaySide = HAAS_EFFECT_DELAY_NONE;
    }

    aList = AudioSynth_ProcessEnvelope(aList, noteSub, synthState, aiBufLen, DMEM_TEMP, delaySide, flags);
    if (noteSub->bitField0.usesHeadsetPanEffects) {
        if (!(flags & 1)) {
            flags = 0;
        }
        aList = AudioSynth_ApplyHaasEffect(aList, noteSub, synthState, aiBufLen * 2, flags, delaySide);
    }
    return aList;
}

Acmd* AudioSynth_LoadWaveSamples(Acmd* aList, NoteSubEu* noteSub, NoteSynthesisState* synthState,
                                 s32 numSamplesToLoad) {
    s32 numSamplesAvail;
    s32 numDuplicates;

    aLoadBuffer(aList++, OS_K0_TO_PHYSICAL(noteSub->waveSampleAddr), DMEM_UNCOMPRESSED_NOTE,
                WAVE_SAMPLE_COUNT * SAMPLE_SIZE);

    // Offset in the WAVE_SAMPLE_COUNT samples of gWaveSamples to start processing the wave for continuity
    synthState->samplePosInt = (u32) synthState->samplePosInt % WAVE_SAMPLE_COUNT;
    // Number of samples in the initial WAVE_SAMPLE_COUNT samples available to be used to process
    numSamplesAvail = WAVE_SAMPLE_COUNT - synthState->samplePosInt;

    if (numSamplesToLoad > numSamplesAvail) {
        // Duplicate (copy) the WAVE_SAMPLE_COUNT samples as many times as needed to reach numSamplesToLoad.
        // (numSamplesToLoad - numSamplesAvail) is the number of samples missing.
        // Divide by WAVE_SAMPLE_COUNT, rounding up, to get the amount of duplicates
        numDuplicates = ((numSamplesToLoad - numSamplesAvail + WAVE_SAMPLE_COUNT - 1) / WAVE_SAMPLE_COUNT);
        if (numDuplicates != 0) {
            aDuplicate(aList++, numDuplicates, DMEM_UNCOMPRESSED_NOTE,
                       DMEM_UNCOMPRESSED_NOTE + (WAVE_SAMPLE_COUNT * SAMPLE_SIZE));
        }
    }
    return aList;
}

Acmd* AudioSynth_FinalResample(Acmd* aList, NoteSynthesisState* synthState, s32 size, u16 pitch, u16 inpDmem,
                               u32 resampleFlags) {
    if (pitch == 0) {
        aClearBuffer(aList++, DMEM_TEMP, size);
    } else {
        aSetBuffer(aList++, 0, inpDmem, DMEM_TEMP, size);
        aResample(aList++, resampleFlags, pitch, OS_K0_TO_PHYSICAL(synthState->synthesisBuffers->finalResampleState));
    }
    return aList;
}

Acmd* AudioSynth_ProcessEnvelope(Acmd* aList, NoteSubEu* noteSub, NoteSynthesisState* synthState, s32 aiBufLen,
                                 u16 dmemSrc, s32 delaySide, s32 flags) {
    s16 rampReverb;
    s16 rampRight;
    s16 rampLeft;
    u16 panVolLeft;
    u16 panVolRight;
    u16 curVolLeft;
    u16 curVolRight;
    s32 sourceReverbVol;
    s32 temp = 0;

    curVolLeft = synthState->curVolLeft;
    curVolRight = synthState->curVolRight;

    panVolLeft = noteSub->panVolLeft;
    panVolRight = noteSub->panVolRight;

    panVolLeft <<= 4;
    panVolRight <<= 4;

    if (panVolLeft != curVolLeft) {
        rampLeft = (panVolLeft - curVolLeft) / (aiBufLen >> 3);
    } else {
        rampLeft = 0;
    }
    if (panVolRight != curVolRight) {
        rampRight = (panVolRight - curVolRight) / (aiBufLen >> 3);
    } else {
        rampRight = 0;
    }

    sourceReverbVol = synthState->reverbVol;

    if (noteSub->reverb != sourceReverbVol) {
        temp = (((noteSub->reverb & 0x7F) - (sourceReverbVol & 0x7F)) << 8);
        rampReverb = temp / (aiBufLen >> 3);
        synthState->reverbVol = noteSub->reverb;
    } else {
        rampReverb = 0;
    }

    synthState->curVolLeft = curVolLeft + (rampLeft * (aiBufLen >> 3));
    synthState->curVolRight = curVolRight + (rampRight * (aiBufLen >> 3));

    if (noteSub->bitField0.usesHeadsetPanEffects) {
        aClearBuffer(aList++, DMEM_HAAS_TEMP, DMEM_1CH_SIZE);
        aEnvSetup1(aList++, (sourceReverbVol & 0x7F), rampReverb, rampLeft, rampRight);
        aEnvSetup2(aList++, curVolLeft, curVolRight);

        switch (delaySide) {
            case HAAS_EFFECT_DELAY_LEFT:
                aEnvMixer(aList++, dmemSrc, aiBufLen, 0, 0, ((sourceReverbVol & 0x80) >> 7),
                          noteSub->bitField0.stereoStrongRight, noteSub->bitField0.stereoStrongLeft, 0x65B1C9E1, 0);
                break;

            case HAAS_EFFECT_DELAY_RIGHT:
                aEnvMixer(aList++, dmemSrc, aiBufLen, 0, 0, ((sourceReverbVol & 0x80) >> 7),
                          noteSub->bitField0.stereoStrongRight, noteSub->bitField0.stereoStrongLeft, 0x9965C9E1, 0);
                break;

            default: // HAAS_EFFECT_DELAY_NONE
                aEnvMixer(aList++, dmemSrc, aiBufLen, 0, 0, ((sourceReverbVol & 0x80) >> 7),
                          noteSub->bitField0.stereoStrongRight, noteSub->bitField0.stereoStrongLeft, 0x99B1C9E1, 0);
                break;
        }
    } else {
        aEnvSetup1(aList++, (sourceReverbVol & 0x7F), rampReverb, rampLeft, rampRight);
        aEnvSetup2(aList++, curVolLeft, curVolRight);
        aEnvMixer(aList++, dmemSrc, aiBufLen, 0, 0, ((sourceReverbVol & 0x80) >> 7),
                  noteSub->bitField0.stereoStrongRight, noteSub->bitField0.stereoStrongLeft, 0x99B1C9E1, 0);
    }

    return aList;
}

/**
 * The Haas Effect gives directionality to sound by applying a small (< 35ms) delay to either the left or right channel.
 * The delay is small enough that the sound is still perceived as one sound, but the channel that is not delayed will
 * reach our ear first and give a sense of directionality. The sound is directed towards the opposite side of the delay.
 */
Acmd* AudioSynth_ApplyHaasEffect(Acmd* aList, NoteSubEu* noteSub, NoteSynthesisState* synthState, s32 size, s32 flags,
                                 s32 delaySide) {
    u16 dmemDest;
    u8 haasEffectDelaySize;
    u8 prevHaasEffectDelaySize;
    u16 pitch;

    switch (delaySide) {
        case HAAS_EFFECT_DELAY_LEFT:
            dmemDest = DMEM_LEFT_CH;
            haasEffectDelaySize = noteSub->leftDelaySize;
            prevHaasEffectDelaySize = synthState->prevHaasEffectLeftDelaySize;
            synthState->prevHaasEffectRightDelaySize = 0;
            synthState->prevHaasEffectLeftDelaySize = haasEffectDelaySize;
            break;

        case HAAS_EFFECT_DELAY_RIGHT:
            dmemDest = DMEM_RIGHT_CH;
            haasEffectDelaySize = noteSub->rightDelaySize;
            prevHaasEffectDelaySize = synthState->prevHaasEffectRightDelaySize;
            synthState->prevHaasEffectRightDelaySize = haasEffectDelaySize;
            synthState->prevHaasEffectLeftDelaySize = 0;
            break;

        default: // HAAS_EFFECT_DELAY_NONE
            return aList;
    }

    if (flags != A_INIT) {
        if (haasEffectDelaySize != prevHaasEffectDelaySize) {
            pitch = (((size << 0xF) / 2) - 1) / ((size + haasEffectDelaySize - prevHaasEffectDelaySize - 2) / 2);
            aSetBuffer(aList++, 0, DMEM_HAAS_TEMP, DMEM_TEMP, size + haasEffectDelaySize - prevHaasEffectDelaySize);
            aResampleZoh(aList++, pitch, 0);
        } else {
            aDMEMMove(aList++, DMEM_HAAS_TEMP, DMEM_TEMP, size);
        }
        if (prevHaasEffectDelaySize != 0) {
            aLoadBuffer(aList++, OS_K0_TO_PHYSICAL(synthState->synthesisBuffers->panSamplesBuffer), DMEM_HAAS_TEMP,
                        ALIGN16(prevHaasEffectDelaySize));
            aDMEMMove(aList++, DMEM_TEMP, prevHaasEffectDelaySize + DMEM_HAAS_TEMP,
                      size + haasEffectDelaySize - prevHaasEffectDelaySize);
        } else {
            aDMEMMove(aList++, DMEM_TEMP, DMEM_HAAS_TEMP, size + haasEffectDelaySize);
        }
    } else {
        aDMEMMove(aList++, DMEM_HAAS_TEMP, DMEM_TEMP, size);
        aClearBuffer(aList++, DMEM_HAAS_TEMP, haasEffectDelaySize);
        aDMEMMove(aList++, DMEM_TEMP, haasEffectDelaySize + DMEM_HAAS_TEMP, size);
    }

    if (haasEffectDelaySize) {
        aSaveBuffer(aList++, size + DMEM_HAAS_TEMP, OS_K0_TO_PHYSICAL(synthState->synthesisBuffers->panSamplesBuffer),
                    ALIGN16(haasEffectDelaySize));
    }

    aAddMixer(aList++, ALIGN64(size), DMEM_HAAS_TEMP, dmemDest);

    return aList;
}
