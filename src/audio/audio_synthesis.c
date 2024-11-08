#include "sys.h"
#include "sf64audio_provisional.h"
#include "audio/mixer.h"
#include "endianness.h"

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

void func_80009A2C(s32 updateIndex, s32 noteIndex);
void func_80009AAC(s32 updateIndex);
Acmd* func_8000A700(s32 noteIndex, NoteSubEu* noteSub, NoteSynthesisState* synthState, s16* aiBuf, s32 aiBufLen,
                    Acmd* aList, s32 updateIndex);
Acmd* func_8000A25C(s16* aiBuf, s32 aiBufLen, Acmd* aList, s32 updateIndex);
Acmd* func_800098DC(Acmd* aList, u16 dmem, u16 startPos, s32 size, s32 reverbIndex);
Acmd* func_80009984(Acmd* aList, u16 dmem, u16 startPos, s32 size, s32 reverbIndex);
Acmd* func_80009D78(Acmd* aList, s32 aiBufLen, s16 reverbIndex, s16 updateIndex);
Acmd* func_8000A128(Acmd* aList, s16 reverbIndex, s16 updateIndex);
Acmd* func_8000B3F0(Acmd* aList, NoteSubEu* noteSub, NoteSynthesisState* synthState, s32 numSamplesToLoad);
Acmd* func_8000B480(Acmd* aList, NoteSynthesisState* synthState, s32 size, u16 pitch, u16 inpDmem, u32 resampleFlags);
Acmd* func_8000B51C(Acmd* aList, NoteSubEu* noteSub, NoteSynthesisState* synthState, s32 aiBufLen, u16 dmemSrc,
                    s32 delaySide, s32 flags);
Acmd* func_8000B98C(Acmd* aList, NoteSubEu* noteSub, NoteSynthesisState* synthState, s32 size, s32 flags,
                    s32 delaySide);

void func_800080C0(s32 sampleCount, s32 itemIndex, s32 reverbIndex) {
    ReverbRingBufferItem* ringItem;
    SynthesisReverb* reverb = &gSynthReverbs[reverbIndex];
    s32 temp_lo;
    s32 temp_v1_3;
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
    temp_lo = sampleCount / reverb->downsampleRate;
    temp_v1_3 = reverb->nextRingBufPos + temp_lo - reverb->bufSizePerChan;

    if (temp_v1_3 < 0) {
        ringItem->lengthA = temp_lo * 2;
        ringItem->lengthB = 0;
        ringItem->startPos = reverb->nextRingBufPos;
        reverb->nextRingBufPos += temp_lo;
    } else {
        ringItem->lengthA = (temp_lo - temp_v1_3) * 2;
        ringItem->lengthB = temp_v1_3 * 2;
        ringItem->startPos = reverb->nextRingBufPos;
        reverb->nextRingBufPos = temp_v1_3;
    }
    ringItem->numSamplesAfterDownsampling = temp_lo;
    ringItem->chunkLen = sampleCount;
}

void func_80008364(f32* buffer0, f32* buffer1, s32 length, f32* buffer2) {
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
    func_80008780(buffer1, length, buffer2);

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
void func_80008780(f32* arg0, s32 arg1, f32* arg2) {
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
#pragma GLOBAL_ASM("asm/us/rev1/nonmatchings/audio/audio_synthesis/func_80008780.s")
#endif

// https://decomp.me/scratch/mYlns
#ifdef NON_MATCHING
void func_80009124(s16** arg0) {
    s16* var_a1;
    s32 temp_a0;
    u8 temp_s0;
    u8 temp_s1;
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

    var_a1 = *arg0;

    for (i = 255; i >= 0; i--) {
        D_80145D48[i] = 0.0f;
    }
    var_t3 = *var_a1++ << 0x10;
    var_t3 |= *var_a1++;

    for (var_t2 = 0; var_t2 != 0x100; var_t2 += 0x40) {
        temp_s0 = var_t3 >> 0x18;
        var_v1 = var_t2;
        var_t3 <<= 8;

        temp_v0 = ((temp_s0 >> 4) & 0xF);
        temp_a0 = temp_s0 & 0xF;
        if (((temp_s0 >> 4) & 0xF) == 0) {
            continue;
        }
        switch (temp_v0) {
            case 1:
                while (true) {
                    var_s0 = *var_a1++;
                    for (var_s1 = 0; var_s1 < 4; var_s1++) {
                        temp_s1 = (var_s0 >> 0xC) & 0xF;
                        var_s0 <<= 4;
                        D_80145D48[var_v1++] = ((temp_s1 & 7) - 4) << temp_a0;

                        if (temp_s1 >= 8) {
                            goto case_1_break;
                        }
                    }
                }
            case_1_break:
                break;
            case 2:
                var_s1 = -1;
                while (++var_s1 < 16) {
                    var_s0 = *var_a1++;
                    for (i = 0; i < 4; i++) {
                        temp_s1 = (var_s0 >> 0xC) & 0xF;
                        var_s0 <<= 4;
                        D_80145D48[var_v1++] = (temp_s1 - 8) << temp_a0;
                    }
                }
                break;
            case 6:
                while (true) {
                    var_s0 = *var_a1++;
                    temp_s1 = (var_s0 >> 8) & 0xFF;

                    D_80145D48[var_v1] = ((temp_s1 & 0x3F) - 0x20) << temp_a0;
                    if (temp_s1 >> 6 == 0) {

                        break;
                    }
                    var_v1 += temp_s1 >> 6;
                    temp_s1 = var_s0 & 0xFF;
                    D_80145D48[var_v1] = ((temp_s1 & 0x3F) - 0x20) << temp_a0;
                    if (temp_s1 >> 6 == 0) {

                        break;
                    }
                    var_v1 += temp_s1 >> 6;
                }
                break;
            case 3:
                while (true) {
                    var_s0 = *var_a1++;

                    temp_s1 = (var_s0 >> 8) & 0xFF;

                    D_80145D48[var_v1++] = ((temp_s1 & 0x7F) - 0x40) << temp_a0;
                    if (temp_s1 >= 0x80) {
                        break;
                    }
                    temp_s1 = var_s0 & 0xFF;
                    D_80145D48[var_v1++] = ((temp_s1 & 0x7F) - 0x40) << temp_a0;
                    if (temp_s1 >= 0x80) {
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
                    D_80145D48[var_v1] = ((var_s0 & 0x7FFF) - 0x4000) << temp_a0;
                    if ((var_s0 >> 0xF) == 1) {
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

    func_80008364(D_80145D48, D_80146148, 8, D_80146548);

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
    s32 pad1;
    SampleDma* pad2;
    SampleDma* sp1C;

    if (flags == 1) {
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
    sp1C->devAddr = (uintptr_t) sample->sampleAddr;
    sp1C->sizeUnused = length * 2;
    pad2 = arg3->unk_14;
    pad2->ttl = 2;
    arg3->unk_8 += func_8000967C(length, (s16*) sp1C->ramAddr, arg3);
    return sp1C->ramAddr;
}

Acmd* func_800098DC(Acmd* aList, u16 dmem, u16 startPos, s32 size, s32 reverbIndex) {
    aLoadBuffer(aList++, OS_K0_TO_PHYSICAL(&gSynthReverbs[reverbIndex].leftRingBuf[startPos]), dmem, size);
    aLoadBuffer(aList++, OS_K0_TO_PHYSICAL(&gSynthReverbs[reverbIndex].rightRingBuf[startPos]), dmem + 0x180, size);
    return aList;
}

Acmd* func_80009984(Acmd* aList, u16 dmem, u16 startPos, s32 size, s32 reverbIndex) {
    aSaveBuffer(aList++, dmem, OS_K0_TO_PHYSICAL(&gSynthReverbs[reverbIndex].leftRingBuf[startPos]), size);
    aSaveBuffer(aList++, dmem + 0x180, OS_K0_TO_PHYSICAL(&gSynthReverbs[reverbIndex].rightRingBuf[startPos]), size);
    return aList;
}

void func_80009A2C(s32 updateIndex, s32 noteIndex) {
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

void func_80009AAC(s32 updateIndex) {
    NoteSubEu* subEu;
    NoteSubEu* subEu2;
    s32 i;

    for (i = 0; i < gNumNotes; i++) {
        subEu = &gNotes[i].noteSubEu;
        subEu2 = &gNoteSubsEu[gNumNotes * updateIndex + i];
        if (subEu->bitField0.enabled) {
            *subEu2 = *subEu;
            subEu->bitField0.needsInit = false;
        } else {
            subEu2->bitField0.enabled = false;
        }
    }
}

Acmd* func_80009B64(Acmd* aList, s32* cmdCount, s16* aiBufStart, s32 aiBufLen) {
    Acmd* aCmdPtr;
    s16* aiBufPtr;
    s32 chunkLen;
    s32 i;
    s32 j;

    aCmdPtr = aList;
    for (i = gAudioBufferParams.ticksPerUpdate; i > 0; i--) {
        func_8001678C(i - 1);
        func_80009AAC(gAudioBufferParams.ticksPerUpdate - i);
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
                func_800080C0(chunkLen, gAudioBufferParams.ticksPerUpdate - i, j);
            }
        }

        aCmdPtr = func_8000A25C(aiBufPtr, chunkLen, aCmdPtr, gAudioBufferParams.ticksPerUpdate - i);
        aiBufLen -= chunkLen;
        aiBufPtr += chunkLen;
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

Acmd* func_80009D78(Acmd* aList, s32 aiBufLen, s16 reverbIndex, s16 updateIndex) {
    ReverbRingBufferItem* sp64 = &gSynthReverbs[reverbIndex].items[gSynthReverbs[reverbIndex].curFrame][updateIndex];
    s16 sp62;
    s16 sp60;

    aClearBuffer(aList++, 0xC90, 0x300);

    if (gSynthReverbs[reverbIndex].downsampleRate == 1) {
        aList = func_800098DC(aList, 0xC90, sp64->startPos, sp64->lengthA, reverbIndex);
        if (sp64->lengthB != 0) {
            aList = func_800098DC(aList, sp64->lengthA + 0xC90, 0, sp64->lengthB, reverbIndex);
        }
        aAddMixer(aList++, 0x300, 0xC90, 0x990);
        aMix(aList++, 0x30, gSynthReverbs[reverbIndex].decayRatio + 0x8000, 0xC90, 0xC90);
    } else {
        sp62 = (sp64->startPos & 7) * 2;
        sp60 = ALIGN16(sp62 + sp64->lengthA);
        aList = func_800098DC(aList, 0x470, sp64->startPos - (sp62 / 2), 0x180, reverbIndex);
        if (sp64->lengthB != 0) {
            aList = func_800098DC(aList, sp60 + 0x470, 0, 0x180 - sp60, reverbIndex);
        }
        aSetBuffer(aList++, 0, sp62 + 0x470, 0xC90, aiBufLen * 2);
        aResample(aList++, gSynthReverbs[reverbIndex].resampleFlags, gSynthReverbs[reverbIndex].unk_0A,
                  OS_K0_TO_PHYSICAL(gSynthReverbs[reverbIndex].unk_30));
        aSetBuffer(aList++, 0, sp62 + 0x5F0, 0xE10, aiBufLen * 2);
        aResample(aList++, gSynthReverbs[reverbIndex].resampleFlags, gSynthReverbs[reverbIndex].unk_0A,
                  OS_K0_TO_PHYSICAL(gSynthReverbs[reverbIndex].unk_34));
        aAddMixer(aList++, 0x300, 0xC90, 0x990);
        aMix(aList++, 0x30, gSynthReverbs[reverbIndex].decayRatio + 0x8000, 0xC90, 0xC90);
    }

    if ((gSynthReverbs[reverbIndex].leakRtL != 0) || (gSynthReverbs[reverbIndex].leakLtR != 0)) {
        aDMEMMove(aList++, 0xC90, 0x470, 0x180);
        aMix(aList++, 0x18, gSynthReverbs[reverbIndex].leakRtL, 0xE10, 0xC90);
        aMix(aList++, 0x18, gSynthReverbs[reverbIndex].leakLtR, 0x470, 0xE10);
    }
    return aList;
}

Acmd* func_8000A128(Acmd* aList, s16 reverbIndex, s16 updateIndex) {
    ReverbRingBufferItem* sp24;

    sp24 = &gSynthReverbs[reverbIndex].items[gSynthReverbs[reverbIndex].curFrame][updateIndex];
    switch (gSynthReverbs[reverbIndex].downsampleRate) {
        case 1:
            aList = func_80009984(aList, 0xC90, sp24->startPos, sp24->lengthA, reverbIndex);
            if (sp24->lengthB != 0) {
                aList = func_80009984(aList, sp24->lengthA + 0xC90, 0, sp24->lengthB, reverbIndex);
            }
            break;

        default:
            aSaveBuffer(aList++, 0xC90,
                        OS_K0_TO_PHYSICAL(gSynthReverbs[reverbIndex]
                                              .items[gSynthReverbs[reverbIndex].curFrame][updateIndex]
                                              .toDownsampleLeft),
                        0x300);
            gSynthReverbs[reverbIndex].resampleFlags = 0;
            break;
    }

    return aList;
}

Acmd* func_8000A25C(s16* aiBuf, s32 aiBufLen, Acmd* aList, s32 updateIndex) {
    u8 sp84[0x3C];
    NoteSubEu* temp_v0;
    s16 var_s2;
    s16 i = 0;
    s32 j = 0;

    var_s2 = 0;
    if (gNumSynthReverbs == 0) {
        if (gSynthReverbs[i].useReverb) {} // fake?
        for (j = 0; j < gNumNotes; j++) {
            if (gNoteSubsEu[gNumNotes * updateIndex + j].bitField0.enabled) {
                sp84[var_s2++] = j;
            }
        }
    } else {
        for (i = 0; i < gNumSynthReverbs; i++) {
            for (j = 0; j < gNumNotes; j++) {
                temp_v0 = &gNoteSubsEu[gNumNotes * updateIndex + j];
                if (temp_v0->bitField0.enabled && (temp_v0->bitField1.reverbIndex == i)) {
                    sp84[var_s2++] = j;
                }
            }
        }
        for (j = 0; j < gNumNotes; j++) {
            temp_v0 = &gNoteSubsEu[gNumNotes * updateIndex + j];
            if (temp_v0->bitField0.enabled && (temp_v0->bitField1.reverbIndex >= gNumSynthReverbs)) {
                sp84[var_s2++] = j;
            }
        }
    }

    aClearBuffer(aList++, 0x990, 0x300);

    j = 0;
    for (i = 0; i < gNumSynthReverbs; i++) {
        D_8014C1B2 = gSynthReverbs[i].useReverb;
        if (D_8014C1B2) {
            aList = func_80009D78(aList, aiBufLen, i, updateIndex);
        }
        while (j < var_s2) {
            if (i != gNoteSubsEu[updateIndex * gNumNotes + sp84[j]].bitField1.reverbIndex) {
                break;
            }
            aList = func_8000A700(sp84[j], &gNoteSubsEu[updateIndex * gNumNotes + sp84[j]],
                                  &gNotes[sp84[j]].synthesisState, aiBuf, aiBufLen, aList, updateIndex);
            j++;
        }
        if (gSynthReverbs[i].useReverb) {
            aList = func_8000A128(aList, i, updateIndex);
        }
    }

    while (j < var_s2) {
        aList = func_8000A700(sp84[j], &gNoteSubsEu[updateIndex * gNumNotes + sp84[j]], &gNotes[sp84[j]].synthesisState,
                              aiBuf, aiBufLen, aList, updateIndex);
        j++;
    }

    j = aiBufLen * 2;
    aSetBuffer(aList++, 0, 0, 0x450, j);
    aInterleave(aList++, 0, 0x990, 0xB10, 0);
    aSaveBuffer(aList++, 0x450, OS_K0_TO_PHYSICAL(aiBuf), j * 2);

    return aList;
}

// https://decomp.me/scratch/RgX4r
#ifdef NON_MATCHING
Acmd* func_8000A700(s32 noteIndex, NoteSubEu* noteSub, NoteSynthesisState* synthState, s16* aiBuf, s32 aiBufLen,
                    Acmd* aList, s32 updateIndex) {
    s32 pad11C;
    s32 pad118;
    s32 pad114;
    Sample* bookSample;  // sp110
    AdpcmLoop* loopInfo; // sp10C
    void* currentBook;   // sp108
    s32 pad104;
    s32 pad100;
    s32 noteFinished;           // spFC
    u32 restart;                // spF8
    s32 flags;                  // spF4
    u16 resampleRateFixedPoint; // spF2
    s32 nSamplesToLoad;         // spEC
    s32 padE8;
    s32 padE4;
    s32 padE0;
    s32 skipBytes; // spDC
    s32 padD8;
    s32 padD4;
    s32 padD0;
    uintptr_t sampleAddr; // spCC
    s32 padC8;
    s32 samplesLenAdjusted;     // spC4
    s32 nAdpcmSamplesProcessed; // spC0
    uintptr_t endPos;                 // spBC
    s32 nSamplesToProcess;      // spB8
    s32 padB4;
    s32 padB0;
    s32 padAC;
    s32 padA8;
    s32 padA4;
    s32 nTrailingSamplesToIgnore; // spA0
    s32 pad9C;
    s32 pad98;
    s32 pad94;
    s32 frameSize; // sp90
    s32 pad8C;
    s32 skipInitialSamples; // sp88
    s32 sampleDmaStart;     // sp84
    s32 pad80;
    s32 nParts;  // sp7C
    s32 curPart; // sp78
    s32 nSamplesInThisIteration;
    uintptr_t sampleDataStartPad;
    s32 resampledTempLen;                    // sp6C
    u16 noteSamplesDmemAddrBeforeResampling; // sp6A
    s32 samplesRemaining;
    s32 frameIndex;
    uintptr_t sampleDataOffset;
    Note* note; // sp58
    u16 sp56;   // sp56

    s32 nSamplesInFirstFrame;
    s32 delaySide;
    s32 nSamplesToDecode;
    s32 nFramesToDecode;
    s32 nFirstFrameSamplesToIgnore;
    s32 s5;
    u32 sampleslenFixedPoint;
    u8* sampleData;
    s32 temp;
    s32 temp2;
    u32 nEntries;
    s32 aligned;
    s32 align2;
    uintptr_t addr;

    currentBook = NULL;
    note = &gNotes[noteIndex];
    flags = 0;
    if (noteSub->bitField0.needsInit == 1) {
        flags = 1;
        synthState->restart = 0;
        synthState->samplePosInt = 0;
        synthState->samplePosFrac = 0;
        synthState->curVolLeft = 0;
        synthState->curVolRight = 0;
        synthState->prevHaasEffectLeftDelaySize = 0;
        synthState->prevHaasEffectRightDelaySize = 0;
        synthState->numParts = 0;
        note->noteSubEu.bitField0.finished = 0;
    }
    resampleRateFixedPoint = noteSub->resampleRate;
    nParts = noteSub->bitField1.hasTwoParts + 1;
    sampleslenFixedPoint = (resampleRateFixedPoint * aiBufLen * 2) + synthState->samplePosFrac;
    nSamplesToLoad = (sampleslenFixedPoint) >> 0x10;
    synthState->samplePosFrac = sampleslenFixedPoint & 0xFFFF;
    if ((synthState->numParts == 1) && (nParts == 2)) {
        nSamplesToLoad += 2;
        sp56 = 2;
    } else if ((synthState->numParts == 2) && (nParts == 1)) {
        nSamplesToLoad -= 4;
        sp56 = 4;
    } else {
        sp56 = 0;
    }
    synthState->numParts = nParts;
    if (noteSub->bitField1.isSyntheticWave) {
        aList = func_8000B3F0(aList, noteSub, synthState, nSamplesToLoad);
        noteSamplesDmemAddrBeforeResampling = (synthState->samplePosInt * 2) + 0x5F0;
        synthState->samplePosInt += nSamplesToLoad;
    } else {
        bookSample = *(Sample**) noteSub->waveSampleAddr;
        loopInfo = bookSample->loop;
        endPos = loopInfo->end;
        sampleAddr = bookSample->sampleAddr;
        resampledTempLen = 0;

        for (curPart = 0; curPart < nParts; curPart++) {
            nAdpcmSamplesProcessed = 0;
            s5 = 0;
            if (nParts == 1) {
                samplesLenAdjusted = nSamplesToLoad;
            } else if (nSamplesToLoad & 1) {
                samplesLenAdjusted = (nSamplesToLoad & ~1) + (curPart * 2);
            } else {
                samplesLenAdjusted = nSamplesToLoad;
            }
            if ((bookSample->codec == 0) && (currentBook != bookSample->book->book)) {
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

                nEntries = 16 * bookSample->book->order * bookSample->book->numPredictors;
                aLoadADPCM(aList++, nEntries, OS_K0_TO_PHYSICAL(currentBook));
            }
            while (nAdpcmSamplesProcessed != samplesLenAdjusted) {
                restart = 0;
                noteFinished = 0;
                samplesRemaining = endPos - synthState->samplePosInt;
                nSamplesToProcess = samplesLenAdjusted - nAdpcmSamplesProcessed;

                nFirstFrameSamplesToIgnore = synthState->samplePosInt & 0xF;

                if ((nFirstFrameSamplesToIgnore == 0) && !synthState->restart) {
                    nFirstFrameSamplesToIgnore = 0x10;
                }

                nSamplesInFirstFrame = 0x10 - nFirstFrameSamplesToIgnore;
                if (nSamplesToProcess < samplesRemaining) {
                    nFramesToDecode = (nSamplesToProcess - nSamplesInFirstFrame + 0xF) / 16;
                    nSamplesToDecode = nFramesToDecode * 0x10;
                    // if(1) {}
                    nTrailingSamplesToIgnore = (nSamplesInFirstFrame + nSamplesToDecode) - nSamplesToProcess;
                } else {
                    nSamplesToDecode = samplesRemaining - nSamplesInFirstFrame;
                    nTrailingSamplesToIgnore = 0;
                    if (nSamplesToDecode <= 0) {
                        nSamplesToDecode = 0;
                        nSamplesInFirstFrame = samplesRemaining;
                    }
                    nFramesToDecode = (nSamplesToDecode + 0xF) / 16;
                    if (loopInfo->count != 0) {
                        restart = 1;
                    } else {
                        noteFinished = 1;
                    }
                }
                switch (bookSample->codec) {
                    case 0:
                        frameSize = 9;
                        skipInitialSamples = 0x10;
                        sampleDmaStart = 0;
                        break;
                    case 1:
                        frameSize = 0x10;
                        skipInitialSamples = 0x10;
                        sampleDmaStart = 0;
                        break;
                    case 2:
                        temp =
                            func_800097A8(bookSample, samplesLenAdjusted, flags, &synthState->synthesisBuffers->unk_40);
                        aLoadBuffer(aList++, OS_K0_TO_PHYSICAL(temp), 0x5F0, (samplesLenAdjusted + 0x10) * 2);
                        s5 = samplesLenAdjusted;
                        nAdpcmSamplesProcessed = samplesLenAdjusted;
                        skipBytes = 0;
                        goto skip;
                }
                aligned = ALIGN16(nFramesToDecode * frameSize + SAMPLES_PER_FRAME);
                addr = 0x990 - aligned;
                if (nFramesToDecode != 0) {
                    // LTODO: Validate this
                    // bookSample->medium = 0;

                    frameIndex = (synthState->samplePosInt + skipInitialSamples - nFirstFrameSamplesToIgnore) / SAMPLES_PER_FRAME;
                    sampleDataOffset = frameIndex * frameSize;
                    if (bookSample->medium == 0) {
                        sampleData = sampleDmaStart + sampleDataOffset + sampleAddr;
                    } else {
                        sampleData = AudioLoad_DmaSampleData(sampleDmaStart + sampleDataOffset + sampleAddr, aligned,
                                                             flags, &synthState->sampleDmaIndex, bookSample->medium);
                    }
                    // if (1){}
                    sampleDataStartPad = (uintptr_t) sampleData & 0xF;
                    aLoadBuffer(aList++, OS_K0_TO_PHYSICAL(sampleData - sampleDataStartPad), addr, aligned);
                } else {
                    nSamplesToDecode = 0;
                    sampleDataStartPad = 0;
                }
                if (synthState->restart) {
                    aSetLoop(aList++, OS_K0_TO_PHYSICAL(bookSample->loop->predictorState));
                    flags = 2;
                    synthState->restart = 0;
                }
                nSamplesInThisIteration = nSamplesToDecode + nSamplesInFirstFrame - nTrailingSamplesToIgnore;

                if (nAdpcmSamplesProcessed == 0) {
                    switch (bookSample->codec) {
                        case 0:
                            aSetBuffer(aList++, 0, addr + sampleDataStartPad, 0x5F0, nSamplesToDecode * 2);
                            aADPCMdec(aList++, flags, OS_K0_TO_PHYSICAL(synthState->synthesisBuffers));
                            break;
                        case 1:
                            aSetBuffer(aList++, 0, addr + sampleDataStartPad, 0x5F0, nSamplesToDecode * 2);
                            aS8Dec(aList++, flags, OS_K0_TO_PHYSICAL(synthState->synthesisBuffers));
                            break;
                    }

                    skipBytes = nFirstFrameSamplesToIgnore * 2;
                } else {
                    // if (1) {}
                    align2 = ALIGN16(s5 + 0x10);
                    switch (bookSample->codec) {
                        case 0:
                            aSetBuffer(aList++, 0, addr + sampleDataStartPad, align2 + 0x5F0, nSamplesToDecode * 2);
                            aADPCMdec(aList++, flags, OS_K0_TO_PHYSICAL(synthState->synthesisBuffers));
                            break;
                        case 1:
                            aSetBuffer(aList++, 0, addr + sampleDataStartPad, align2 + 0x5F0, nSamplesToDecode * 2);
                            aS8Dec(aList++, flags, OS_K0_TO_PHYSICAL(synthState->synthesisBuffers));
                            break;
                    }
                    aDMEMMove(aList++, (align2 + (nFirstFrameSamplesToIgnore * 2) + 0x5F0), s5 + 0x5F0,
                              nSamplesInThisIteration * 2);
                }
                nAdpcmSamplesProcessed += nSamplesInThisIteration;
                switch (flags) {
                    case 1:
                        skipBytes = 0x20;
                        s5 = (nSamplesToDecode + 0x10) * 2;
                        break;
                    case 2:
                        // if(1) {}
                        s5 = nSamplesInThisIteration * 2 + s5;
                        break;
                    default:
                        if (s5 != 0) {
                            s5 = nSamplesInThisIteration * 2 + s5;
                        } else {
                            // if (1) { }
                            s5 = (nFirstFrameSamplesToIgnore + nSamplesInThisIteration) * 2;
                        }
                        break;
                }
            skip:
                flags = 0;
                // goto dummy_label_147574; dummy_label_147574: ;
                if (noteFinished) {
                    aClearBuffer(aList++, s5 + 0x5F0, (samplesLenAdjusted - nAdpcmSamplesProcessed) * 2);
                    noteSub->bitField0.finished = 1;
                    note->noteSubEu.bitField0.finished = 1;
                    func_80009A2C(updateIndex, noteIndex);
                    break;
                }
                if (restart) {
                    synthState->restart = 1;
                    synthState->samplePosInt = loopInfo->start;
                } else {
                    synthState->samplePosInt += nSamplesToProcess;
                }
            }
            switch (nParts) {
                case 1:
                    noteSamplesDmemAddrBeforeResampling = skipBytes + 0x5F0;
                    break;
                case 2:
                    switch (curPart) {
                        case 0:
                            aInterl(aList++, skipBytes + 0x5F0, 0x470, ALIGN8(samplesLenAdjusted / 2));
                            resampledTempLen = samplesLenAdjusted;
                            noteSamplesDmemAddrBeforeResampling = 0x470;
                            if (noteSub->bitField0.finished) {
                                aClearBuffer(aList++, resampledTempLen + noteSamplesDmemAddrBeforeResampling,
                                             samplesLenAdjusted + 0x10);
                            }
                            break;
                        case 1:
                            aInterl(aList++, skipBytes + 0x5F0, resampledTempLen + 0x470,
                                    ALIGN8(samplesLenAdjusted / 2));
                            break;
                    }
                    break;
            }

            if (noteSub->bitField0.finished) {
                break;
            }
        }
    }

    flags = 0;
    if (noteSub->bitField0.needsInit == 1) {
        flags = 1;
        noteSub->bitField0.needsInit = 0;
    }
    flags = sp56 | flags;
    aList = func_8000B480(aList, synthState, aiBufLen * 2, resampleRateFixedPoint, noteSamplesDmemAddrBeforeResampling,
                          flags);
    if (flags & 1) {
        flags = 1;
    }
    if (noteSub->bitField1.bookOffset == 3) {
        aUnkCmd19(aList++, 0, aiBufLen * 2, 0x450, 0x450);
    }

    temp2 = noteSub->gain;
    if (temp2 != 0) {
        if (temp2 < 0x10) {
            temp2 = 0x10;
        }
        aHiLoGain(aList++, temp2, (aiBufLen + 0x10) * 2, 0x450, 0);
    }
    if ((noteSub->leftDelaySize != 0) || (synthState->prevHaasEffectLeftDelaySize != 0)) {
        delaySide = 1;
    } else if ((noteSub->rightDelaySize != 0) || (synthState->prevHaasEffectRightDelaySize != 0)) {
        delaySide = 2;
    } else {
        delaySide = 0;
    }

    aList = func_8000B51C(aList, noteSub, synthState, aiBufLen, 0x450, delaySide, flags);
    // if(restart) {}
    if (noteSub->bitField0.usesHeadsetPanEffects) {
        if (!(flags & 1)) {
            flags = 0;
        }
        aList = func_8000B98C(aList, noteSub, synthState, aiBufLen * 2, flags, delaySide);
    }

    return aList;
}
#else
#pragma GLOBAL_ASM("asm/us/rev1/nonmatchings/audio/audio_synthesis/func_8000A700.s")
#endif

Acmd* func_8000B3F0(Acmd* aList, NoteSubEu* noteSub, NoteSynthesisState* synthState, s32 numSamplesToLoad) {
    s32 temp_v1;

    aLoadBuffer(aList++, OS_K0_TO_PHYSICAL(noteSub->waveSampleAddr), 0x5F0, 0x80);
    synthState->samplePosInt &= 0x3F;
    temp_v1 = 0x40 - synthState->samplePosInt;
    if (temp_v1 < numSamplesToLoad) {
        if ((((numSamplesToLoad - temp_v1) + 0x3F) / 64) != 0) {
            aDuplicate(aList++, ((numSamplesToLoad - temp_v1) + 0x3F) / 64, 0x5F0, 0x670);
        }
    }
    return aList;
}

Acmd* func_8000B480(Acmd* aList, NoteSynthesisState* synthState, s32 size, u16 pitch, u16 inpDmem, u32 resampleFlags) {
    if (pitch == 0) {
        aClearBuffer(aList++, 0x450, size);
    } else {
        aSetBuffer(aList++, 0, inpDmem, 0x450, size);
        aResample(aList++, resampleFlags, pitch, OS_K0_TO_PHYSICAL(synthState->synthesisBuffers->finalResampleState));
    }
    return aList;
}

Acmd* func_8000B51C(Acmd* aList, NoteSubEu* noteSub, NoteSynthesisState* synthState, s32 aiBufLen, u16 dmemSrc,
                    s32 delaySide, s32 flags) {
    s16 var_a2;
    s16 var_a3;
    s16 var_t0;
    u16 temp_t7;
    u16 temp_t9;
    u16 temp_t1;
    u16 temp_t2;
    s32 temp_a1;
    s32 temp = 0;

    temp_t1 = synthState->curVolLeft;
    temp_t2 = synthState->curVolRight;

    temp_t7 = noteSub->panVolLeft;
    temp_t9 = noteSub->panVolRight;

    temp_t7 <<= 4;
    temp_t9 <<= 4;

    if (temp_t7 != temp_t1) {
        var_t0 = (temp_t7 - temp_t1) / (aiBufLen >> 3);
    } else {
        var_t0 = 0;
    }
    if (temp_t9 != temp_t2) {
        var_a3 = (temp_t9 - temp_t2) / (aiBufLen >> 3);
    } else {
        var_a3 = 0;
    }

    temp_a1 = synthState->reverbVol;

    if (noteSub->reverb != temp_a1) {
        temp = (((noteSub->reverb & 0x7F) - (temp_a1 & 0x7F)) << 8);
        var_a2 = temp / (aiBufLen >> 3);
        synthState->reverbVol = noteSub->reverb;
    } else {
        var_a2 = 0;
    }

    synthState->curVolLeft = temp_t1 + (var_t0 * (aiBufLen >> 3));
    synthState->curVolRight = temp_t2 + (var_a3 * (aiBufLen >> 3));

    if (noteSub->bitField0.usesHeadsetPanEffects) {
        aClearBuffer(aList++, 0x650, 0x180);
        aEnvSetup1(aList++, (temp_a1 & 0x7F), var_a2, var_t0, var_a3);
        aEnvSetup2(aList++, temp_t1, temp_t2);

        switch (delaySide) {
            case 1:
                aEnvMixer(aList++, dmemSrc, aiBufLen, 0, 0, ((temp_a1 & 0x80) >> 7),
                          noteSub->bitField0.stereoStrongRight, noteSub->bitField0.stereoStrongLeft, 0x65B1C9E1, 0);
                break;
            case 2:
                aEnvMixer(aList++, dmemSrc, aiBufLen, 0, 0, ((temp_a1 & 0x80) >> 7),
                          noteSub->bitField0.stereoStrongRight, noteSub->bitField0.stereoStrongLeft, 0x9965C9E1, 0);
                break;
            default:
                aEnvMixer(aList++, dmemSrc, aiBufLen, 0, 0, ((temp_a1 & 0x80) >> 7),
                          noteSub->bitField0.stereoStrongRight, noteSub->bitField0.stereoStrongLeft, 0x99B1C9E1, 0);
                break;
        }
    } else {
        aEnvSetup1(aList++, (temp_a1 & 0x7F), var_a2, var_t0, var_a3);
        aEnvSetup2(aList++, temp_t1, temp_t2);
        aEnvMixer(aList++, dmemSrc, aiBufLen, 0, 0, ((temp_a1 & 0x80) >> 7), noteSub->bitField0.stereoStrongRight,
                  noteSub->bitField0.stereoStrongLeft, 0x99B1C9E1, 0);
    }

    return aList;
}

Acmd* func_8000B98C(Acmd* aList, NoteSubEu* noteSub, NoteSynthesisState* synthState, s32 size, s32 flags,
                    s32 delaySide) {
    u16 var_t0;
    u8 var_a1;
    u8 var_v1;
    u16 temp;

    switch (delaySide) {
        case 1:
            var_t0 = 0x990;
            var_a1 = noteSub->leftDelaySize;
            synthState->prevHaasEffectRightDelaySize = 0;
            var_v1 = synthState->prevHaasEffectLeftDelaySize;
            synthState->prevHaasEffectLeftDelaySize = var_a1;
            break;

        case 2:
            var_t0 = 0xB10;
            var_a1 = noteSub->rightDelaySize;
            synthState->prevHaasEffectLeftDelaySize = 0;
            var_v1 = synthState->prevHaasEffectRightDelaySize;
            synthState->prevHaasEffectRightDelaySize = var_a1;
            break;

        default:
            return aList;
    }

    if (flags != 1) {
        if (var_a1 != var_v1) {
            temp = (((size << 0xF) / 2) - 1) / ((size + var_a1 - var_v1 - 2) / 2);
            aSetBuffer(aList++, 0, 0x650, 0x450, size + var_a1 - var_v1);
            aResampleZoh(aList++, temp, 0);
        } else {
            aDMEMMove(aList++, 0x650, 0x450, size);
        }
        if (var_v1 != 0) {
            aLoadBuffer(aList++, OS_K0_TO_PHYSICAL(synthState->synthesisBuffers->panSamplesBuffer), 0x650,
                        ALIGN16(var_v1));
            aDMEMMove(aList++, 0x450, var_v1 + 0x650, size + var_a1 - var_v1);
        } else {
            aDMEMMove(aList++, 0x450, 0x650, size + var_a1);
        }
    } else {
        aDMEMMove(aList++, 0x650, 0x450, size);
        aClearBuffer(aList++, 0x650, var_a1);
        aDMEMMove(aList++, 0x450, var_a1 + 0x650, size);
    }
    if (var_a1) {
        aSaveBuffer(aList++, size + 0x650, OS_K0_TO_PHYSICAL(synthState->synthesisBuffers->panSamplesBuffer),
                    ALIGN16(var_a1));
    }

    aAddMixer(aList++, ALIGN64(size), 0x650, var_t0);

    return aList;
}
