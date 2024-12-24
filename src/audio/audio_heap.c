#include "sys.h"
#include "sf64audio_provisional.h"

void AudioHeap_DiscardSampleCacheEntry(SampleCacheEntry* entry);
void AudioHeap_Init(void);
void AudioHeap_DiscardSampleCaches(void);
void AudioHeap_InitSampleCaches(u32, u32);
void AudioHeap_UnapplySampleCache(SampleCacheEntry* entry, Sample* sample);
SampleCacheEntry* AudioHeap_AllocTemporarySampleCacheEntry(s32);
void* AudioHeap_SearchRegularCaches(s32 tableType, s32 cache, s32 id);
void* AudioHeap_SearchPermanentCache(s32 tableType, s32 id);
SampleCacheEntry* AudioHeap_AllocPersistentSampleCacheEntry(u32);

static const char devstr00[] = "Warning:Kill Note  %x \n";
static const char devstr01[] = "Kill Voice %d (ID %d) %d\n";
static const char devstr02[] = "Warning: Running Sequence's data disappear!\n";
static const char devstr03[] = "%x %x %x\n";
static const char devstr04[] = "Audio:Memory:Heap OverFlow : Not Allocate %d!\n";
static const char devstr05[] = "%x %x %x\n";
static const char devstr06[] = "Audio:Memory:Heap OverFlow : Not Allocate %d!\n";
static const char devstr07[] = "Audio:Memory:DataHeap Not Allocate \n";
static const char devstr08[] = "StayHeap Not Allocate %d\n";
static const char devstr09[] = "AutoHeap Not Allocate %d\n";
static const char devstr10[] = "Status ID0 : %d  ID1 : %d\n";
static const char devstr11[] = "id 0 is Stopping\n";
static const char devstr12[] = "id 0 is Stop\n";
static const char devstr13[] = "id 1 is Stopping\n";
static const char devstr14[] = "id 1 is Stop\n";
static const char devstr15[] = "WARNING: NO FREE AUTOSEQ AREA.\n";
static const char devstr16[] = "WARNING: NO STOP AUTO AREA.\n";
static const char devstr17[] = "         AND TRY FORCE TO STOP SIDE \n";
static const char devstr18[] = "Check ID0  (seq ID %d) Useing ...\n";
static const char devstr19[] = "Check ID1  (seq ID %d) Useing ...\n";
static const char devstr20[] = "No Free Seq area.\n";
static const char devstr21[] = "CH %d: ID %d\n";
static const char devstr22[] = "TWO SIDES ARE LOADING... ALLOC CANCELED.\n";
static const char devstr23[] = "WARNING: Before Area Overlaid After.";
static const char devstr24[] = "WARNING: After Area Overlaid Before.";
static const char devstr25[] = "MEMORY:SzHeapAlloc ERROR: sza->side %d\n";
static const char devstr26[] = "Audio:MEMORY:SzHeap Overflow error. (%d bytes)\n";
static const char devstr27[] = "Auto Heap Unhit for ID %d\n";
static const char devstr28[] = "Heap Reconstruct Start %x\n";
static const char devstr29[] = "---------------------------------------TEMPO %d %f\n";
static const char devstr30[] = "%f \n";
static const char devstr31[] = "%f \n";
static const char devstr32[] = "AHPBASE %x\n";
static const char devstr33[] = "AHPCUR  %x\n";
static const char devstr34[] = "HeapTop %x\n";
static const char devstr35[] = "SynoutRate %d / %d \n";
static const char devstr36[] = "FXSIZE %d\n";
static const char devstr37[] = "FXCOMP %d\n";
static const char devstr38[] = "FXDOWN %d\n";
static const char devstr39[] = "WaveCacheLen: %d\n";
static const char devstr40[] = "SpecChange Finished\n";
static const char devstr41[] = "Warning:Emem Over,not alloc %d\n";
static const char devstr42[] = "Single AutoSize %d\n";
static const char devstr43[] = "Single Ptr %x\n";
static const char devstr44[] = "Request--------Single-Auto, %d\n";
static const char devstr45[] = "Retry %x, %x, len %x\n";
static const char devstr46[] = "DMAing list %d is killed.\n";
static const char devstr47[] = "Try Kill %d \n";
static const char devstr48[] = "Try Kill %x %x\n";
static const char devstr49[] = "Try Kill %x %x %x\n";
static const char devstr50[] = "Rom back %x %x \n";
static const char devstr51[] = "Error sw NULL \n";
static const char devstr52[] = "Request--------Single-Stay, %d\n";
static const char devstr53[] = "Try Kill %d \n";
static const char devstr54[] = "Try Kill %x %x\n";
static const char devstr55[] = "Try Kill %x %x %x\n";

void AudioHeap_ResetLoadStatus(void) {
    s32 i;

    for (i = 0; i < 64; i++) {
        if (gFontLoadStatus[i] != 5) {
            gFontLoadStatus[i] = 0;
        }
    }
    for (i = 0; i < 64; i++) {
        if (gSampleFontLoadStatus[i] != 5) {
            gSampleFontLoadStatus[i] = 0;
        }
    }
    for (i = 0; i < 256; i++) {
        if (gSeqLoadStatus[i] != 5) {
            gSeqLoadStatus[i] = 0;
        }
    }
}

void AudioHeap_DiscardFont(s32 fontId) {
    Note* note;
    s32 i;

    for (i = 0; i < gNumNotes; i++) {
        note = &gNotes[i];
        if (fontId == note->playbackState.fontId) {
            if ((note->playbackState.unk_04 == 0) && (note->playbackState.priority != 0)) {
                note->playbackState.parentLayer->enabled = false;
                note->playbackState.parentLayer->finished = true;
            }
            Audio_NoteDisable(note);
            Audio_AudioListRemove(note);
            AudioSeq_AudioListPushBack(&gNoteFreeLists.disabled, &note->listItem);
        }
    }
}

void AudioHeap_DiscardSequence(s32 seqId) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gSeqPlayers); i++) {
        if (gSeqPlayers[i].enabled && gSeqPlayers[i].seqId == seqId) {
            AudioSeq_SequencePlayerDisable(&gSeqPlayers[i]);
        }
    }
}

void* AudioHeap_AllocZeroed(AudioAllocPool* pool, u32 size) {
    u32 aligned = ALIGN16(size);
    u8* ramAddr = pool->curRamAddr;
    u8* ptr;

    if (pool->startRamAddr + pool->size >= pool->curRamAddr + aligned) {
        pool->curRamAddr += aligned;
        for (ptr = ramAddr; ptr < pool->curRamAddr; ptr++) {
            *ptr = 0;
        }
    } else {
        return NULL;
    }
    pool->numEntries++;
    return ramAddr;
}

void* AudioHeap_Alloc(AudioAllocPool* pool, u32 size) {
    u32 aligned = ALIGN16(size);
    u8* ramAddr = pool->curRamAddr;

    if ((pool->startRamAddr + pool->size) >= (pool->curRamAddr + aligned)) {
        pool->curRamAddr += aligned;
    } else {
        return NULL;
    }
    pool->numEntries++;
    return ramAddr;
}

void AudioHeap_InitPool(AudioAllocPool* pool, void* ramAddr, u32 size) {
    pool->curRamAddr = pool->startRamAddr = (u8*) ramAddr;
    pool->size = size - ((uintptr_t) ramAddr & 0xF);
    pool->numEntries = 0;
}

void AudioHeap_InitPersistentCache(AudioPersistentCache* persistent) {
    persistent->pool.numEntries = 0;
    persistent->numEntries = 0;
    persistent->pool.curRamAddr = persistent->pool.startRamAddr;
}

void AudioHeap_InitTemporaryCache(AudioTemporaryCache* temporary) {
    temporary->pool.numEntries = 0;
    temporary->pool.curRamAddr = temporary->pool.startRamAddr;
    temporary->nextSide = 0;
    temporary->entries[0].ramAddr = temporary->pool.startRamAddr;
    temporary->entries[1].ramAddr = temporary->pool.startRamAddr + temporary->pool.size;
    temporary->entries[0].id = -1;
    temporary->entries[1].id = -1;
}

void AudioHeap_ResetPool(AudioAllocPool* pool) {
    pool->numEntries = 0;
    pool->curRamAddr = pool->startRamAddr;
}

void AudioHeap_InitMainPools(s32 initPoolSize) {
    AudioHeap_InitPool(&gInitPool, gAudioHeap, initPoolSize);
    AudioHeap_InitPool(&gSessionPool, gAudioHeap + initPoolSize, gAudioHeapSize - initPoolSize);
}

void AudioHeap_InitSessionPools(AudioSessionPoolSplit* split) {
    gSessionPool.curRamAddr = gSessionPool.startRamAddr;
    AudioHeap_InitPool(&gMiscPool, AudioHeap_Alloc(&gSessionPool, split->miscPoolSize), split->miscPoolSize);
    AudioHeap_InitPool(&gCachePool, AudioHeap_Alloc(&gSessionPool, split->cachePoolSize), split->cachePoolSize);
}

void AudioHeap_InitCachePools(AudioCachePoolSplit* split) {
    gCachePool.curRamAddr = gCachePool.startRamAddr;
    AudioHeap_InitPool(&gPersistentCommonPool, AudioHeap_Alloc(&gCachePool, split->persistentCommonPoolSize),
                       split->persistentCommonPoolSize);
    AudioHeap_InitPool(&gTemporaryCommonPool, AudioHeap_Alloc(&gCachePool, split->temporaryCommonPoolSize),
                       split->temporaryCommonPoolSize);
}

void AudioHeap_InitPersistentPoolsAndCaches(AudioCommonPoolSplit* split) {
    gPersistentCommonPool.curRamAddr = gPersistentCommonPool.startRamAddr;
    AudioHeap_InitPool(&gSeqCache.persistent.pool, AudioHeap_Alloc(&gPersistentCommonPool, split->seqCacheSize),
                       split->seqCacheSize);
    AudioHeap_InitPool(&gFontCache.persistent.pool, AudioHeap_Alloc(&gPersistentCommonPool, split->fontCacheSize),
                       split->fontCacheSize);
    AudioHeap_InitPool(&gSampleBankCache.persistent.pool,
                       AudioHeap_Alloc(&gPersistentCommonPool, split->sampleBankCacheSize), split->sampleBankCacheSize);
    AudioHeap_InitPersistentCache(&gSeqCache.persistent);
    AudioHeap_InitPersistentCache(&gFontCache.persistent);
    AudioHeap_InitPersistentCache(&gSampleBankCache.persistent);
}

void AudioHeap_InitTemporaryPoolsAndCaches(AudioCommonPoolSplit* split) {
    gTemporaryCommonPool.curRamAddr = gTemporaryCommonPool.startRamAddr;
    AudioHeap_InitPool(&gSeqCache.temporary.pool, AudioHeap_Alloc(&gTemporaryCommonPool, split->seqCacheSize),
                       split->seqCacheSize);
    AudioHeap_InitPool(&gFontCache.temporary.pool, AudioHeap_Alloc(&gTemporaryCommonPool, split->fontCacheSize),
                       split->fontCacheSize);
    AudioHeap_InitPool(&gSampleBankCache.temporary.pool,
                       AudioHeap_Alloc(&gTemporaryCommonPool, split->sampleBankCacheSize), split->sampleBankCacheSize);
    AudioHeap_InitTemporaryCache(&gSeqCache.temporary);
    AudioHeap_InitTemporaryCache(&gFontCache.temporary);
    AudioHeap_InitTemporaryCache(&gSampleBankCache.temporary);
}

void* AudioHeap_AllocCached(s32 tableType, s32 size, s32 cache, s32 id) {
    AudioCache* loadedCache;
    AudioTemporaryCache* temporaryCache;
    AudioAllocPool* temporaryPool;
    void* persistentRamAddr;
    void* temporaryRamAddr;
    u8 loadStatusEntry0;
    u8 loadStatusEntry1;
    s32 i;
    u8* loadStatus;

    switch (tableType) {
        case SEQUENCE_TABLE:
            loadedCache = &gSeqCache;
            loadStatus = gSeqLoadStatus;
            break;
        case FONT_TABLE:
            loadedCache = &gFontCache;
            loadStatus = gFontLoadStatus;
            break;
        case SAMPLE_TABLE:
            loadedCache = &gSampleBankCache;
            loadStatus = gSampleFontLoadStatus;
            break;
    }
    if (cache == CACHE_TEMPORARY) {
        temporaryCache = &loadedCache->temporary;
        temporaryPool = &temporaryCache->pool;
        if (loadedCache->temporary.entries[0].id == -1) {
            loadStatusEntry0 = 0;
        } else {
            loadStatusEntry0 = loadStatus[temporaryCache->entries[0].id];
        }
        if (temporaryCache->entries[1].id == -1) {
            loadStatusEntry1 = 0;
        } else {
            loadStatusEntry1 = loadStatus[temporaryCache->entries[1].id];
        }
        if (tableType == FONT_TABLE) {
            if (loadStatusEntry0 == 4) {
                for (i = 0; i < gNumNotes; i++) {
                    if ((gNotes[i].playbackState.fontId == temporaryCache->entries[0].id) &&
                        gNotes[i].noteSubEu.bitField0.enabled) {
                        break;
                    }
                }
                if (i == gNumNotes) {
                    if (gFontLoadStatus[temporaryCache->entries[0].id] != 5) {
                        gFontLoadStatus[temporaryCache->entries[0].id] = 3;
                    }
                    loadStatusEntry0 = 3;
                }
            }
            if (loadStatusEntry1 == 4) {
                for (i = 0; i < gNumNotes; i++) {
                    if ((gNotes[i].playbackState.fontId == temporaryCache->entries[1].id) &&
                        gNotes[i].noteSubEu.bitField0.enabled) {
                        break;
                    }
                }
                if (i == gNumNotes) {
                    if (gFontLoadStatus[temporaryCache->entries[1].id] != 5) {
                        gFontLoadStatus[temporaryCache->entries[1].id] = 3;
                    }
                    loadStatusEntry1 = 3;
                }
            }
        }
        if (loadStatusEntry0 == 0) {
            temporaryCache->nextSide = 0;
        } else if (loadStatusEntry1 == 0) {
            temporaryCache->nextSide = 1;
        } else if ((loadStatusEntry0 == 3) && (loadStatusEntry1 == 3)) {
            // Use the opposite side from last time.
        } else if (loadStatusEntry0 == 3) {
            temporaryCache->nextSide = 0;
        } else if (loadStatusEntry1 == 3) {
            temporaryCache->nextSide = 1;
        } else {
            // Check if there is a side which isn't in active use, if so, evict that one.
            if (tableType == SEQUENCE_TABLE) {
                if (loadStatusEntry0 == 2) {
                    for (i = 0; i < ARRAY_COUNT(gSeqPlayers); i++) {
                        if (gSeqPlayers[i].enabled && (gSeqPlayers[i].seqId == temporaryCache->entries[0].id)) {
                            break;
                        }
                    }
                    if (i == 4) {
                        temporaryCache->nextSide = 0;
                        goto block_85;
                    }
                }
                if (loadStatusEntry1 == 2) {
                    for (i = 0; i < ARRAY_COUNT(gSeqPlayers); i++) {
                        if (gSeqPlayers[i].enabled && (gSeqPlayers[i].seqId == temporaryCache->entries[1].id)) {
                            break;
                        }
                    }
                    if (i == 4) {
                        temporaryCache->nextSide = 1;
                        goto block_85;
                    }
                }
            } else if (tableType == FONT_TABLE) {
                if (loadStatusEntry0 == 2) {
                    for (i = 0; i < gNumNotes; i++) {
                        if ((gNotes[i].playbackState.fontId == temporaryCache->entries[0].id) &&
                            gNotes[i].noteSubEu.bitField0.enabled) {
                            break;
                        }
                    }

                    if (i == gNumNotes) {
                        temporaryCache->nextSide = 0;
                        goto block_85;
                    }
                }
                if (loadStatusEntry1 == 2) {
                    for (i = 0; i < gNumNotes; i++) {
                        if ((gNotes[i].playbackState.fontId == temporaryCache->entries[1].id) &&
                            gNotes[i].noteSubEu.bitField0.enabled) {
                            break;
                        }
                    }
                    if (i == gNumNotes) {
                        temporaryCache->nextSide = 1;
                        goto block_85;
                    }
                }
            }
            // No such luck. Evict the side that wasn't chosen last time, except
            // if it is being loaded into.
            if (temporaryCache->nextSide == 0) {
                if (loadStatusEntry0 == 1) {
                    if (loadStatusEntry1 == 1) {
                        goto block_84;
                    }
                    temporaryCache->nextSide = 1;
                }
                goto block_85;
            }
            if (loadStatusEntry1 == 1) {
                if (loadStatusEntry0 == 1) {
                    goto block_84;
                }
                temporaryCache->nextSide = 0;
                goto block_85;
            block_84:
                return NULL;
            }
        }
    block_85:

        if (temporaryCache->entries[temporaryCache->nextSide].id != -1) {
            loadStatus[temporaryCache->entries[temporaryCache->nextSide].id] = 0;
            if (tableType == FONT_TABLE) {
                AudioHeap_DiscardFont(temporaryCache->entries[temporaryCache->nextSide].id);
            }
        }
        switch (temporaryCache->nextSide) {
            case 0:
                temporaryCache->entries[0].ramAddr = temporaryPool->startRamAddr;
                temporaryCache->entries[0].id = id;
                temporaryCache->entries[0].size = size;
                temporaryPool->curRamAddr = &temporaryPool->startRamAddr[size];
                if ((temporaryCache->entries[1].id != -1) &&
                    (temporaryCache->entries[1].ramAddr < temporaryPool->curRamAddr)) {
                    loadStatus[temporaryCache->entries[1].id] = 0;
                    switch (tableType) {
                        case SEQUENCE_TABLE:
                            AudioHeap_DiscardSequence(temporaryCache->entries[1].id);
                            break;
                        case FONT_TABLE:
                            AudioHeap_DiscardFont(temporaryCache->entries[1].id);
                            break;
                    }
                    temporaryCache->entries[1].id = -1;
                    temporaryCache->entries[1].ramAddr = &temporaryPool->startRamAddr[temporaryPool->size];
                }
                temporaryRamAddr = temporaryCache->entries[0].ramAddr;
                break;
            case 1:
                temporaryCache->entries[1].ramAddr =
                    (u8*) ((uintptr_t) &temporaryPool->startRamAddr[temporaryPool->size] - size & ~0xF);
                temporaryCache->entries[1].id = id;
                temporaryCache->entries[1].size = size;
                if ((temporaryCache->entries[0].id != -1) &&
                    (temporaryCache->entries[1].ramAddr < temporaryPool->curRamAddr)) {
                    loadStatus[temporaryCache->entries[0].id] = 0;
                    switch (tableType) {
                        case SEQUENCE_TABLE:
                            AudioHeap_DiscardSequence(temporaryCache->entries[0].id);
                            break;
                        case FONT_TABLE:
                            AudioHeap_DiscardFont(temporaryCache->entries[0].id);
                            break;
                    }
                    temporaryCache->entries[0].id = -1;
                    temporaryPool->curRamAddr = temporaryPool->startRamAddr;
                }
                temporaryRamAddr = temporaryCache->entries[1].ramAddr;
                break;
            default:
                return NULL;
        }
        temporaryCache->nextSide ^= 1;
        return temporaryRamAddr;
    }
    persistentRamAddr = AudioHeap_Alloc(&loadedCache->persistent.pool, size);
    loadedCache->persistent.entries[loadedCache->persistent.numEntries].ramAddr = persistentRamAddr;
    if (persistentRamAddr == NULL) {
        switch (cache) {
            case CACHE_EITHER:
                return AudioHeap_AllocCached(tableType, size, CACHE_TEMPORARY, id);
            case CACHE_TEMPORARY:
            case CACHE_PERSISTENT:
                return NULL;
        }
    }
    loadedCache->persistent.entries[loadedCache->persistent.numEntries].id = id;
    loadedCache->persistent.entries[loadedCache->persistent.numEntries].size = size;
    return loadedCache->persistent.entries[loadedCache->persistent.numEntries++].ramAddr;
}

uintptr_t AudioHeap_SearchCaches(s32 tableType, s32 cache, s32 id) {
    void* ramAddr;

    // Always search the permanent cache in addition to the regular ones.
    ramAddr = AudioHeap_SearchPermanentCache(tableType, id);
    if (ramAddr != NULL) {
        return (uintptr_t) ramAddr;
    }
    if (cache == CACHE_PERMANENT) {
        // return (uintptr_t) NULL;
    }
    return (uintptr_t) AudioHeap_SearchRegularCaches(tableType, cache, id);
}

void* AudioHeap_SearchRegularCaches(s32 tableType, s32 cache, s32 id) {
    u32 i;
    AudioCache* loadedCache;
    AudioTemporaryCache* temporary;
    AudioPersistentCache* persistent;

    switch (tableType) {
        case SEQUENCE_TABLE:
            loadedCache = &gSeqCache;
            break;

        case FONT_TABLE:
            loadedCache = &gFontCache;
            break;

        case SAMPLE_TABLE:
            loadedCache = &gSampleBankCache;
            break;
    }

    temporary = &loadedCache->temporary;
    if (cache == CACHE_TEMPORARY) {
        if (temporary->entries[0].id == id) {
            temporary->nextSide = 1;
            return temporary->entries[0].ramAddr;
        } else if (temporary->entries[1].id == id) {
            temporary->nextSide = 0;
            return temporary->entries[1].ramAddr;
        } else {
            return NULL;
        }
    }

    persistent = &loadedCache->persistent;
    for (i = 0; i < persistent->numEntries; i++) {
        if (persistent->entries[i].id == id) {
            return persistent->entries[i].ramAddr;
        }
    }

    if (cache == CACHE_EITHER) {
        return (void*) AudioHeap_SearchCaches(tableType, CACHE_TEMPORARY, id);
    }
    return NULL;
}

void func_8000CAF4(f32 p, f32 q, u16* out) {
    // With the bug below fixed, this mysterious unused function computes two recurrences
    // out[0..7] = a_i, out[8..15] = b_i, where
    // a_{-2} = b_{-1} = 262159 = 2^18 + 15
    // a_{-1} = b_{-2} = 0
    // a_i = q * a_{i-1} + p * a_{i-2}
    // b_i = q * b_{i-1} + p * b_{i-2}
    // These grow exponentially if p < -1 or p + |q| > 1.
    s32 i;
    f32 tmp[16];

    tmp[0] = (f32) (q * 262159.0f);
    tmp[8] = (f32) (p * 262159.0f);
    tmp[1] = (f32) ((q * p) * 262159.0f);
    tmp[9] = (f32) (((p * p) + q) * 262159.0f);

    for (i = 2; i < 8; i++) {
        //! @bug value should be stored to tmp[i] and tmp[8 + i], otherwise we read
        //! garbage in later loop iterations.
        out[i] = q * tmp[i - 2] + p * tmp[i - 1];
        out[8 + i] = q * tmp[6 + i] + p * tmp[7 + i];
    }

    for (i = 0; i < 16; i++) {
        out[i] = tmp[i];
    }
}

void AudioHeap_UpdateReverbs(void) {
    s32 i;
    s32 count;
    s32 reverbIndex;

    if (gAudioBufferParams.numBuffers == 2) {
        count = 2;
    } else {
        count = 1;
    }
    for (reverbIndex = 0; reverbIndex < gNumSynthReverbs; reverbIndex++) {
        for (i = 0; i < count; i++) {
            gSynthReverbs[reverbIndex].decayRatio -= gSynthReverbs[reverbIndex].decayRatio / 3;
        }
    }
}

void AudioHeap_ClearCurrentAiBuffer(void) {
    s32 i;
    s32 index = gCurAiBuffIndex;

    gAiBuffLengths[index] = gAudioBufferParams.minAiBufferLength;

    for (i = 0; i < AIBUF_LEN; i++) {
        gAiBuffers[index][i] = 0;
    }
}

s32 AudioHeap_ResetStep(void) {
    s32 i;
    s32 j;
    s32 sp24;

    if (gAudioBufferParams.numBuffers == 2) {
        sp24 = 2;
    } else {
        sp24 = 1;
    }
    switch (gAudioResetStep) {
        case 5:
            for (i = 0; i < ARRAY_COUNT(gSeqPlayers); i++) {
                AudioSeq_SequencePlayerDisable(&gSeqPlayers[i]);
            }
            gResetFadeoutFramesLeft = 4 / sp24;
            gAudioResetStep--;
            break;
        case 4:
            if (gResetFadeoutFramesLeft != 0) {
                gResetFadeoutFramesLeft--;
                AudioHeap_UpdateReverbs();
            } else {
                for (i = 0; i < gNumNotes; i++) {
                    if (gNotes[i].noteSubEu.bitField0.enabled && (gNotes[i].playbackState.adsr.state != 0)) {
                        gNotes[i].playbackState.adsr.fadeOutVel = gAudioBufferParams.ticksPerUpdateInv;
                        gNotes[i].playbackState.adsr.action.asByte |= 0x10;
                    }
                }

                gResetFadeoutFramesLeft = 16 / sp24;
                gAudioResetStep--;
            }
            break;
        case 3:
            if (gResetFadeoutFramesLeft != 0) {
                gResetFadeoutFramesLeft--;
                AudioHeap_UpdateReverbs();
            } else {
                //                memset(audio_buffer, 0, (1056 * 2 * 3) * 2 * 2);
                gResetFadeoutFramesLeft = 4 / sp24;
                gAudioResetStep--;
                break; // needed to match
            }
            break;
        case 2:
            AudioHeap_ClearCurrentAiBuffer();
            if (gResetFadeoutFramesLeft != 0) {
                gResetFadeoutFramesLeft--;
            } else {
                gAudioResetStep--;
                AudioHeap_DiscardSampleCaches();
            }
            break;
        case 1:
            AudioHeap_Init();
            gAudioResetStep = 0;
            //            memset(audio_buffer, 0, (1056 * 2 * 3) * 2 * 2);
            break;
    }
    if (gAudioResetStep < 3) {
        return 0;
    }
    return 1;
}

void AudioHeap_Init(void) {
    s32 i;
    s32 j;
    AudioSpec* spec = &gAudioSpecs[gAudioSpecId];
    s16* ramAddr;
    u32 persistentSize;
    u32 temporarySize;
    u32 cachePoolSize;
    u32 miscPoolSize;

    gSampleDmaCount = 0;
    gAudioBufferParams.samplingFrequency = spec->samplingFrequency;
    gAudioBufferParams.aiSamplingFrequency = osAiSetFrequency(gAudioBufferParams.samplingFrequency);
    gAudioBufferParams.samplesPerFrameTarget = ALIGN16(gAudioBufferParams.samplingFrequency / gRefreshRate);

    gAudioBufferParams.minAiBufferLength = gAudioBufferParams.samplesPerFrameTarget - 0x10;
    gAudioBufferParams.maxAiBufferLength = gAudioBufferParams.samplesPerFrameTarget + 0x10;

    gAudioBufferParams.ticksPerUpdate = ((gAudioBufferParams.samplesPerFrameTarget + 0x10) / 192) + 1;
    gAudioBufferParams.samplesPerTick =
        (gAudioBufferParams.samplesPerFrameTarget / gAudioBufferParams.ticksPerUpdate) & ~7;
    gAudioBufferParams.samplesPerTickMax = gAudioBufferParams.samplesPerTick + 8;
    gAudioBufferParams.samplesPerTickMin = gAudioBufferParams.samplesPerTick - 8;
    gAudioBufferParams.resampleRate = 32000.0f / (s32) gAudioBufferParams.samplingFrequency;
    gAudioBufferParams.ticksPerUpdateInvScaled = (3.0f / 2560.0f) / gAudioBufferParams.ticksPerUpdate;
    gAudioBufferParams.ticksPerUpdateInv = 1.0f / gAudioBufferParams.ticksPerUpdate;

    gNumNotes = spec->numNotes;
    D_8014C1B0 = spec->unk_14;

    gMaxTempo = (u16) ((gAudioBufferParams.ticksPerUpdate * 2880000.0f / gSeqTicksPerBeat) / gMaxTempoTvTypeFactors);

    gAudioBufferParams.numBuffers = spec->numBuffers;
    gAudioBufferParams.numBuffers = 1;

    gAudioBufferParams.samplesPerFrameTarget *= gAudioBufferParams.numBuffers;
    gAudioBufferParams.maxAiBufferLength *= gAudioBufferParams.numBuffers;
    gAudioBufferParams.minAiBufferLength *= gAudioBufferParams.numBuffers;
    gAudioBufferParams.ticksPerUpdate *= gAudioBufferParams.numBuffers;
    if (gAudioBufferParams.numBuffers >= 2) {
        gAudioBufferParams.maxAiBufferLength -= 0x10;
    }

    gMaxAudioCmds = (gNumNotes * 20 * gAudioBufferParams.ticksPerUpdate) + (spec->numReverbs * 32) + 480;
    persistentSize = spec->persistentSeqCacheSize + spec->persistentFontCacheSize +
                     spec->persistentSampleBankCacheSize + spec->persistentSampleCacheSize + 0x10;
    temporarySize = spec->temporarySeqCacheSize + spec->temporaryFontCacheSize + spec->temporarySampleBankCacheSize +
                    spec->temporarySampleCacheSize + 0x10;
    cachePoolSize = persistentSize + temporarySize;
    miscPoolSize = gSessionPool.size - cachePoolSize - 0x100;
    gSessionPoolSplit.miscPoolSize = miscPoolSize;
    gSessionPoolSplit.cachePoolSize = cachePoolSize;

    AudioHeap_InitSessionPools(&gSessionPoolSplit);

    gCachePoolSplit.persistentCommonPoolSize = persistentSize;
    gCachePoolSplit.temporaryCommonPoolSize = temporarySize;

    AudioHeap_InitCachePools(&gCachePoolSplit);

    gPersistentCommonPoolSplit.seqCacheSize = spec->persistentSeqCacheSize;
    gPersistentCommonPoolSplit.fontCacheSize = spec->persistentFontCacheSize;
    gPersistentCommonPoolSplit.sampleBankCacheSize = spec->persistentSampleBankCacheSize;

    AudioHeap_InitPersistentPoolsAndCaches(&gPersistentCommonPoolSplit);

    gTemporaryCommonPoolSplit.seqCacheSize = spec->temporarySeqCacheSize;
    gTemporaryCommonPoolSplit.fontCacheSize = spec->temporaryFontCacheSize;
    gTemporaryCommonPoolSplit.sampleBankCacheSize = spec->temporarySampleBankCacheSize;

    AudioHeap_InitTemporaryPoolsAndCaches(&gTemporaryCommonPoolSplit);
    AudioHeap_InitSampleCaches(spec->persistentSampleCacheSize, spec->temporarySampleCacheSize);
    AudioHeap_ResetLoadStatus();

    gNotes = AudioHeap_AllocZeroed(&gMiscPool, gNumNotes * sizeof(Note));
    Audio_NoteInitAll();
    Audio_InitNoteFreeList();
    gNoteSubsEu = AudioHeap_AllocZeroed(&gMiscPool, gAudioBufferParams.ticksPerUpdate * gNumNotes * sizeof(NoteSubEu));

    for (i = 0; i != 2; i++) {
        gAbiCmdBuffs[i] = AudioHeap_AllocZeroed(&gMiscPool, gMaxAudioCmds * 8);
    }
    for (i = 0; i < ARRAY_COUNT(gSynthReverbs); i++) {
        gSynthReverbs[i].useReverb = 0;
    }

    gNumSynthReverbs = spec->numReverbs;
    for (i = 0; i < gNumSynthReverbs; i++) {
        ReverbSettings* settings = &spec->reverbSettings[i];
        SynthesisReverb* reverb = &gSynthReverbs[i];
        reverb->downsampleRate = settings->downsampleRate;
        reverb->windowSize = settings->windowSize * 64;
        reverb->decayRatio = settings->decayRatio;
        reverb->leakRtL = settings->leakRtL;
        reverb->leakLtR = settings->leakLtR;
        reverb->useReverb = 8;

        reverb->leftRingBuf = AudioHeap_AllocZeroed(&gMiscPool, reverb->windowSize * 2);
        reverb->rightRingBuf = AudioHeap_AllocZeroed(&gMiscPool, reverb->windowSize * 2);
        reverb->nextRingBufPos = 0;
        reverb->unk_20 = 0;
        reverb->curFrame = 0;

        reverb->bufSizePerChan = reverb->windowSize;
        reverb->framesToIgnore = 2;

        if (reverb->downsampleRate != 1) {
            reverb->resampleFlags = 1;
            reverb->unk_0A = (0x8000 / reverb->downsampleRate);
            reverb->unk_30 = AudioHeap_AllocZeroed(&gMiscPool, 0x20);
            reverb->unk_34 = AudioHeap_AllocZeroed(&gMiscPool, 0x20);
            reverb->unk_38 = AudioHeap_AllocZeroed(&gMiscPool, 0x20);
            reverb->unk_3C = AudioHeap_AllocZeroed(&gMiscPool, 0x20);
            for (j = 0; j < gAudioBufferParams.ticksPerUpdate; j++) {
                ramAddr = AudioHeap_AllocZeroed(&gMiscPool, 0x300);
                reverb->items[0][j].toDownsampleLeft = ramAddr;
                reverb->items[0][j].toDownsampleRight = ramAddr + 192;
                ramAddr = AudioHeap_AllocZeroed(&gMiscPool, 0x300);
                reverb->items[1][j].toDownsampleLeft = ramAddr;
                reverb->items[1][j].toDownsampleRight = ramAddr + 192;
            }
        }
    }

    AudioLoad_InitSampleDmaBuffers(gNumNotes);
    gPreloadSampleStackTop = 0;
    D_8014C1B4 = 0x1000;
    osWritebackDCacheAll();
}

void* AudioHeap_SearchPermanentCache(s32 tableType, s32 id) {
    s32 i;

    for (i = 0; i < gPermanentPool.pool.numEntries; i++) {
        if ((tableType == gPermanentPool.entry[i].tableType) && (id == gPermanentPool.entry[i].id)) {
            return gPermanentPool.entry[i].ramAddr;
        }
    }
    return NULL;
}

u8* AudioHeap_AllocPermanent(s32 tableType, s32 id, u32 size) {
    u8* ramAddr;
    s32 index = gPermanentPool.pool.numEntries;

    ramAddr = AudioHeap_Alloc(&gPermanentPool.pool, size);
    gPermanentPool.entry[index].ramAddr = ramAddr;

    if (ramAddr == NULL) {
        return NULL;
    }

    gPermanentPool.entry[index].tableType = tableType;
    gPermanentPool.entry[index].id = id;
    gPermanentPool.entry[index].size = size;

#ifdef AVOID_UB
    return ramAddr;
#endif
}

void* AudioHeap_AllocTemporarySampleCache(s32 size, s32 fontId, uintptr_t sampleAddr, s8 medium) {
    SampleCacheEntry* entry = AudioHeap_AllocTemporarySampleCacheEntry(size);

    if (entry != NULL) {
        entry->sampleBankId = fontId;
        entry->sampleAddr = sampleAddr;
        entry->origMedium = medium;
        return entry->allocatedAddr;
    } else {
        return NULL;
    }
}

void* AudioHeap_AllocPersistentSampleCache(s32 size, s32 fontId, uintptr_t sampleAddr, s8 medium) {
    SampleCacheEntry* entry = AudioHeap_AllocPersistentSampleCacheEntry(size);

    if (entry != NULL) {
        entry->sampleBankId = fontId;
        entry->sampleAddr = sampleAddr;
        entry->origMedium = medium;
        return entry->allocatedAddr;
    } else {
        return NULL;
    }
}

void* AudioHeap_AllocPersistentSampleCache_2(u32 size, s32 fontId, s32 sampleAddr, s8 medium) {
    SampleCacheEntry* entry = AudioHeap_AllocPersistentSampleCacheEntry(size);

    if (entry != NULL) {
        entry->sampleBankId = fontId;
        entry->sampleAddr = sampleAddr;
        entry->origMedium = medium;
        return entry->allocatedAddr;
    } else {
        return NULL;
    }
}

void AudioHeap_InitSampleCaches(u32 persistentSampleCacheSize, u32 temporarySampleCacheSize) {
    void* ramAddr;

    ramAddr = AudioHeap_Alloc(&gPersistentCommonPool, persistentSampleCacheSize);
    if (ramAddr == NULL) {
        gPersistentSampleCache.pool.size = 0;
    } else {
        AudioHeap_InitPool(&gPersistentSampleCache.pool, ramAddr, persistentSampleCacheSize);
    }
    ramAddr = AudioHeap_Alloc(&gTemporaryCommonPool, temporarySampleCacheSize);
    if (ramAddr == NULL) {
        gTemporarySampleCache.pool.size = 0;
    } else {
        AudioHeap_InitPool(&gTemporarySampleCache.pool, ramAddr, temporarySampleCacheSize);
    }
    gPersistentSampleCache.numEntries = 0;
    gTemporarySampleCache.numEntries = 0;
}

SampleCacheEntry* AudioHeap_AllocTemporarySampleCacheEntry(s32 size) {
    u8* endRamAddr;
    u8* old;
    u8* ramAddr;
    s32 i;
    s32 entryIdx;
    SampleCacheEntry* entry;
    AudioPreloadReq* preload;
    AudioSampleCache* cache;
    u8* allocAfter;
    u8* startRamAddr;
    u8* allocBefore;

    cache = &gTemporarySampleCache;
    allocBefore = cache->pool.curRamAddr;
    ramAddr = AudioHeap_Alloc(&cache->pool, size);
    if (ramAddr == NULL) {
        old = cache->pool.curRamAddr;
        cache->pool.curRamAddr = cache->pool.startRamAddr;
        ramAddr = AudioHeap_Alloc(&cache->pool, size);
        if (ramAddr == NULL) {
            cache->pool.curRamAddr = old;
            return NULL;
        }
        allocBefore = cache->pool.startRamAddr;
    }
    allocAfter = cache->pool.curRamAddr;
    entryIdx = -1;
    for (i = 0; i < gPreloadSampleStackTop; i++) {
        preload = &gPreloadSampleStack[i];
        if (preload->isFree == 0) {
            startRamAddr = preload->ramAddr;
            endRamAddr = preload->ramAddr + preload->sample->size - 1;
            if ((endRamAddr < allocBefore) && (startRamAddr < allocBefore)) {
                continue;
            }
            if ((endRamAddr >= allocAfter) && (startRamAddr >= allocAfter)) {
                continue;
            }
            preload->isFree = 1;
        }
    }
    for (i = 0; i < cache->numEntries; i++) {
        if (cache->entries[i].inUse == 0) {
            continue;
        }
        startRamAddr = cache->entries[i].allocatedAddr;
        endRamAddr = startRamAddr + cache->entries[i].size - 1;
        if ((endRamAddr < allocBefore) && (startRamAddr < allocBefore)) {
            continue;
        }
        if ((endRamAddr >= allocAfter) && (startRamAddr >= allocAfter)) {
            continue;
        }
        AudioHeap_DiscardSampleCacheEntry(&cache->entries[i]);
        if (entryIdx == -1) {
            entryIdx = i;
        }
    }
    if (entryIdx == -1) {
        entryIdx = cache->numEntries++;
    }
    entry = &cache->entries[entryIdx];
    entry->inUse = 1;
    entry->allocatedAddr = ramAddr;
    entry->size = size;
    return entry;
}

void AudioHeap_DiscardSampleCacheEntry(SampleCacheEntry* entry) {
    s32 fondId;
    s32 numFonts;
    Drum* drum;
    Instrument* instrument;
    s32 instId;
    s32 drumId;
    s32 sampleBankId2;
    s32 sampleBankId1;

    numFonts = gSoundFontTable->base.numEntries;
    for (fondId = 0; fondId < numFonts; fondId++) {
        sampleBankId1 = gSoundFontList[fondId].sampleBankId1;
        sampleBankId2 = gSoundFontList[fondId].sampleBankId2;
        if (((sampleBankId1 != SAMPLES_NONE) && (entry->sampleBankId == sampleBankId1)) ||
            ((sampleBankId2 != SAMPLES_NONE) && (entry->sampleBankId == sampleBankId2)) ||
            (entry->sampleBankId == SAMPLES_SFX)) {
            if (((void*) AudioHeap_SearchCaches(FONT_TABLE, CACHE_EITHER, fondId) != NULL) &&
                (gFontLoadStatus[fondId] > 1) != 0) {
                for (instId = 0; instId < gSoundFontList[fondId].numInstruments; instId++) {
                    instrument = Audio_GetInstrument(fondId, instId);
                    if (instrument != NULL) {
                        if (instrument->normalRangeLo != 0) {
                            AudioHeap_UnapplySampleCache(entry, instrument->lowPitchTunedSample.sample);
                        }
                        if (instrument->normalRangeHi != 0x7F) {
                            AudioHeap_UnapplySampleCache(entry, instrument->highPitchTunedSample.sample);
                        }
                        AudioHeap_UnapplySampleCache(entry, instrument->normalPitchTunedSample.sample);
                    }
                }
                for (drumId = 0; drumId < gSoundFontList[fondId].numDrums; drumId++) {
                    drum = Audio_GetDrum(fondId, drumId);
                    if (drum != NULL) {
                        AudioHeap_UnapplySampleCache(entry, drum->tunedSample.sample);
                    }
                }
            }
        }
    }
}

void AudioHeap_UnapplySampleCache(SampleCacheEntry* entry, Sample* sample) {
    if ((sample != NULL) && (sample->sampleAddr == entry->allocatedAddr)) {
        sample->sampleAddr = (u8*) entry->sampleAddr;
        sample->medium = entry->origMedium;
    }
}

SampleCacheEntry* AudioHeap_AllocPersistentSampleCacheEntry(u32 size) {
    AudioSampleCache* cache = &gPersistentSampleCache;
    SampleCacheEntry* entry;
    u8* ramAddr;

    ramAddr = AudioHeap_Alloc(&cache->pool, size);
    if (ramAddr == NULL) {
        return NULL;
    }
    entry = &cache->entries[cache->numEntries];
    entry->inUse = 1;
    entry->allocatedAddr = ramAddr;
    entry->size = size;
    cache->numEntries++;
    return entry;
}

void AudioHeap_DiscardSampleCaches(void) {
    s32 fontId;
    s32 i;
    s32 numFonts = gSoundFontTable->base.numEntries;
    s32 pad;
    s32 sampleBankId2;
    s32 sampleBankId1;
    s32 instId;
    s32 drumId;
    Drum* drum;
    Instrument* instrument;
    SampleCacheEntry* entry;

#ifdef AVOID_UB
    entry = gPersistentSampleCache.entries;
#endif

    for (fontId = 0; fontId < numFonts; fontId++) {
        sampleBankId1 = gSoundFontList[fontId].sampleBankId1;
        sampleBankId2 = gSoundFontList[fontId].sampleBankId2;
        if (((sampleBankId1 != SAMPLES_NONE_U) && (entry->sampleBankId == sampleBankId1)) ||
            ((sampleBankId2 != SAMPLES_NONE) && (entry->sampleBankId == sampleBankId2)) ||
            (entry->sampleBankId == SAMPLES_SFX)) {
            if (((void*) AudioHeap_SearchCaches(FONT_TABLE, CACHE_PERMANENT, fontId) != NULL) &&
                ((gFontLoadStatus[fontId] > 1) != 0)) {
                for (i = 0; i < gPersistentSampleCache.numEntries; i++) {
                    entry = &gPersistentSampleCache.entries[i];
                    for (instId = 0; instId < gSoundFontList[fontId].numInstruments; instId++) {
                        instrument = Audio_GetInstrument(fontId, instId);
                        if (instrument != NULL) {
                            if (instrument->normalRangeLo != 0) {
                                AudioHeap_UnapplySampleCache(entry, instrument->lowPitchTunedSample.sample);
                            }
                            if (instrument->normalRangeHi != 0x7F) {
                                AudioHeap_UnapplySampleCache(entry, instrument->highPitchTunedSample.sample);
                            }
                            AudioHeap_UnapplySampleCache(entry, instrument->normalPitchTunedSample.sample);
                        }
                    }
                    for (drumId = 0; drumId < gSoundFontList[fontId].numDrums; drumId++) {
                        drum = Audio_GetDrum(fontId, drumId);
                        if (drum != NULL) {
                            AudioHeap_UnapplySampleCache(entry, drum->tunedSample.sample);
                        }
                    }
                }
            }
        }
    }
}
