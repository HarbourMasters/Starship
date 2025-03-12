#include "sys.h"
#include "sf64audio_provisional.h"
#include "port/resource/loaders/AudioLoader.h"

static const char devstr00[] = "Audio: setvol: volume minus %f\n";
static const char devstr01[] = "Audio: setvol: volume overflow %f\n";
static const char devstr02[] = "Audio: setpitch: pitch zero or minus %f\n";
static const char devstr03[] = "Audio: voiceman: No bank error %d\n";
static const char devstr04[] = "Audio: voiceman: progNo. overflow %d,%d\n";
static const char devstr05[] = "ptr2 %x\n";
static const char devstr06[] = "Audio: voiceman: progNo. undefined %d,%d\n";
static const char devstr07[] = "Audio: voiceman: No bank error %d\n";
static const char devstr08[] = "Audio: voiceman: Percussion Overflow %d,%d\n";
static const char devstr09[] = "Audio: voiceman: Percussion table pointer (bank %d) is irregular %x.\n";
static const char devstr10[] = "Audio: voiceman: Percpointer NULL %d,%d\n";
static const char devstr11[] = "--4 %x\n";
static const char devstr12[] = "----------------------Double-Error CH: %x %f\n";
static const char devstr13[] = "----------------------Double-Error NT: %x\n";
static const char devstr14[] = "CAUTION:SUB IS SEPARATED FROM GROUP\n";
static const char devstr15[] = "CAUTION:PAUSE EMERGENCY\n";
static const char devstr16[] = "Error:Wait Track disappear\n";
static const char devstr17[] = "NoteOff Comes during wait release %x (note %x)\n";
static const char devstr18[] = "Slow Release Batting\n";

u8 sSamplesPerWavePeriod[] = { 64, 32, 16, 8 };

static const char devstr19[] = "Audio:Wavemem: Bad voiceno (%d)\n";
static const char devstr20[] = "Audio: C-Alloc : Dealloc voice is NULL\n";
static const char devstr21[] = "Alloc Error:Dim voice-Alloc %d";
static const char devstr22[] = "Error:Same List Add\n";
static const char devstr23[] = "Already Cut\n";
static const char devstr24[] = "Audio: C-Alloc : lowerPrio is NULL\n";
static const char devstr25[] = "Intterupt UseStop %d (Kill %d)\n";
static const char devstr26[] = "Intterupt RelWait %d (Kill %d)\n";
static const char devstr27[] = "Drop Voice (Prio %x)\n";

void Audio_NoteSetResamplingRate(Note* note, f32);
void Audio_SeqLayerNoteRelease(SequenceLayer* layer);
void Audio_AudioListPushFront(AudioListItem* list, AudioListItem* item);
void Audio_AudioListRemove(Note* note);
void Audio_NoteInitForLayer(Note* note, SequenceLayer* layer);

#if 0
typedef struct {                                  // Little Endian
    /* 0x00 */ uint8_t strongLeft : 1;            // 0000 0001
    /* 0x00 */ uint8_t strongRight : 1;           // 0000 0010
    /* 0x00 */ uint8_t bit2 : 2;                  // 0000 0100
    /* 0x00 */ uint8_t unused : 2;                // 0001 0000
    /* 0x00 */ uint8_t usesHeadsetPanEffects : 1; // 0100 0000
    /* 0x00 */ uint8_t stereoHeadsetEffects : 1;  // 1000 0000
} StereoDataTest;

typedef union {
    StereoDataTest data;
    uint8_t raw;
} StereoUnionTest;

int testBits(void) {
    StereoUnionTest test;

    test.raw = 0; // Clear all bits
    test.data.stereoHeadsetEffects = 1;

    printf("Raw byte value: 0x%08X\n", test.raw);
}
#endif

void Audio_InitNoteSub(Note* note, NoteAttributes* noteAttr) {
    NoteSubEu* noteSub;
    f32 panVolumeLeft = 0, panVolumeRight = 0, panVolumeRearLeft = 0, panVolumeRearRight = 0, panVolumeCenter = 0;
    f32 velocity;
    s32 temp_t0;
    s32 var_a0;
    s32 strongRight;
    s32 strongLeft;
    u8 pan;
    u8 reverb;
    Stereo stereo;

    // testBits();

    Audio_NoteSetResamplingRate(note, noteAttr->freqMod);
    noteSub = &note->noteSubEu;
    velocity = noteAttr->velocity;
    pan = noteAttr->pan;
    reverb = noteAttr->reverb;
    stereo = noteAttr->stereo;

    if (GetNumAudioChannels() == 2) {
        pan %= ARRAY_COUNTU(gHeadsetPanVolume);
        if ((noteSub->bitField0.stereoHeadsetEffects) && (gAudioSoundMode == SOUNDMODE_HEADSET)) {
            var_a0 = pan >> 1;
            if (var_a0 >= ARRAY_COUNT(gHaasEffectDelaySizes)) {
                var_a0 = ARRAY_COUNT(gHaasEffectDelaySizes) - 1;
            }
            noteSub->rightDelaySize = gHaasEffectDelaySizes[var_a0];
            noteSub->leftDelaySize = gHaasEffectDelaySizes[ARRAY_COUNT(gHaasEffectDelaySizes) - 1 - var_a0];
            noteSub->bitField0.stereoStrongRight = false;
            noteSub->bitField0.stereoStrongLeft = false;
            noteSub->bitField0.usesHeadsetPanEffects = true;
            panVolumeLeft = gHeadsetPanVolume[pan];
            panVolumeRight = gHeadsetPanVolume[ARRAY_COUNT(gHeadsetPanVolume) - 1 - pan];
        } else if (noteSub->bitField0.stereoHeadsetEffects && (gAudioSoundMode == SOUNDMODE_STEREO)) {
            noteSub->leftDelaySize = 0;
            noteSub->rightDelaySize = 0;
            noteSub->bitField0.usesHeadsetPanEffects = false;
            panVolumeLeft = gStereoPanVolume[pan];
            panVolumeRight = gStereoPanVolume[ARRAY_COUNT(gStereoPanVolume) - 1 - pan];
            strongRight = false;
            strongLeft = false;
            if (pan < 32) {
                strongLeft = true;
            } else if (pan > 96) {
                strongRight = true;
            }
            noteSub->bitField0.stereoStrongRight = strongRight;
            noteSub->bitField0.stereoStrongLeft = strongLeft;
            switch (stereo.s.bit2) {
                case 0:
                    noteSub->bitField0.stereoStrongRight = stereo.s.strongRight;
                    noteSub->bitField0.stereoStrongLeft = stereo.s.strongLeft;
                    break;
                case 1:
                    break;
                case 2:
                    noteSub->bitField0.stereoStrongRight = stereo.s.strongRight | strongRight;
                    noteSub->bitField0.stereoStrongLeft = stereo.s.strongLeft | strongLeft;
                    break;
                case 3:
                    noteSub->bitField0.stereoStrongRight = stereo.s.strongRight ^ strongRight;
                    noteSub->bitField0.stereoStrongLeft = stereo.s.strongLeft ^ strongLeft;
                    break;
            }
        } else if (gAudioSoundMode == SOUNDMODE_MONO) {
            panVolumeLeft = 0.707f;
            panVolumeRight = 0.707f;
        } else {
            panVolumeLeft = gDefaultPanVolume[pan];
            panVolumeRight = gDefaultPanVolume[ARRAY_COUNT(gDefaultPanVolume) - 1 - pan];
        }
    } else {
        // Surround 5.1
        if (stereo.s.is_voice) { // VOICE
            panVolumeCenter = 1.0f;
        }
        else if (stereo.s.is_sfx) { // SFX
            float pan_angle = (float)(pan + 64) / 128 * 2 * M_PI;
            
            // Speaker angles in radians
            const float front_left = -0.5236;
            const float front_right = 0.5236;
            const float rear_left = -1.92;
            const float rear_right = 1.92;

            // Normalize pan_angle to [0, 2π]
            pan_angle = fmodf(pan_angle, 2 * M_PI);
            if (pan_angle < 0) pan_angle += 2 * M_PI;

            // Calculate volumes using cosine panning law
            panVolumeLeft = fmaxf(0, cosf(pan_angle - front_left));  // Front Left
            panVolumeRight = fmaxf(0, cosf(pan_angle - front_right)); // Front Right
            panVolumeRearLeft = fmaxf(0, cosf(pan_angle - rear_left));   // Rear Left
            panVolumeRearRight = fmaxf(0, cosf(pan_angle - rear_right));  // Rear Right
        } else { // MUSIC
            panVolumeLeft = gStereoPanVolume[pan];
            panVolumeRight = gStereoPanVolume[ARRAY_COUNT(gStereoPanVolume) - 1 - pan];
            panVolumeRearLeft = gStereoPanVolume[pan];
            panVolumeRearRight = gStereoPanVolume[ARRAY_COUNT(gStereoPanVolume) - 1 - pan];
        }
    }

    if (velocity < 0.0f) {
        velocity = 0.0f;
    }
    if (velocity > 1.0f) {
        velocity = 1.0f;
    }

    float master_vol = CVarGetFloat("gGameMasterVolume", 1.0f);
    noteSub->panVolLeft = (s32) (velocity * panVolumeLeft * 4095.999f) * master_vol;
    noteSub->panVolRight = (s32) (velocity * panVolumeRight * 4095.999f) * master_vol;
    noteSub->panVolRLeft = (s32) (velocity * panVolumeRearLeft * 4095.999f) * master_vol;
    noteSub->panVolRRight = (s32) (velocity * panVolumeRearRight * 4095.999f) * master_vol;
    noteSub->panVolCenter = (s32) (velocity * panVolumeCenter * 4095.999f) * master_vol;
    noteSub->panVolLfe = (s32) (velocity * 4095.999f) * master_vol;

    noteSub->gain = noteAttr->gain;
    if (noteSub->reverb != reverb) {
        noteSub->reverb = reverb;
    }
}

void Audio_NoteSetResamplingRate(Note* note, f32 resamplingRateInput) {
    NoteSubEu* noteSub = &note->noteSubEu;
    f32 resamplingRate;

    if (resamplingRateInput < 2.0f) {
        noteSub->bitField1.hasTwoParts = false;
        resamplingRate = CLAMP_MAX(resamplingRateInput, 1.99998f);
    } else {
        noteSub->bitField1.hasTwoParts = true;
        if (resamplingRateInput > 3.99996f) {
            resamplingRate = 1.99998f;
        } else {
            resamplingRate = resamplingRateInput * 0.5f;
        }
    }
    note->noteSubEu.resampleRate = (s32) (resamplingRate * 32768.0f);
}

TunedSample* Audio_GetInstrumentTunedSample(Instrument* instrument, s32 semitone) {
    TunedSample* sample;

    if (semitone < instrument->normalRangeLo) {
        sample = &instrument->lowPitchTunedSample;
    } else if (semitone <= instrument->normalRangeHi) {
        sample = &instrument->normalPitchTunedSample;
    } else {
        sample = &instrument->highPitchTunedSample;
    }
    return sample;
}

Instrument* Audio_GetInstrument(s32 fontId, s32 instId) {
    Instrument* instrument;

    // fontId = 7;

    if (gSoundFontList[fontId].instruments == NULL) {
        gSoundFontList[fontId] = *Audio_LoadFont(gSoundFontTable->entries[fontId], fontId);
    }

    if ((gFontLoadStatus[fontId] < 2) != 0) {
        D_80155D88 = fontId + 0x10000000;
        return NULL;
    }
    if (instId >= gSoundFontList[fontId].numInstruments) {
        D_80155D88 = (fontId << 8) + instId + 0x03000000;
        return NULL;
    }
    instrument = gSoundFontList[fontId].instruments[instId];
    if (instrument == NULL) {
        D_80155D88 = (fontId << 8) + instId + 0x01000000;
        return instrument;
    }
    printf("InstId: %d\n", instId);
    return instrument;
}

Drum* Audio_GetDrum(s32 fontId, s32 drumId) {
    Drum* drum;

    // LTODO: Remove this
    if (gSoundFontList[fontId].drums == NULL) {
        gSoundFontList[fontId] = *Audio_LoadFont(gSoundFontTable->entries[fontId], fontId);
    }

    if ((gFontLoadStatus[fontId] < 2) != 0) {
        D_80155D88 = fontId + 0x10000000;
        return NULL;
    }
    if (drumId >= gSoundFontList[fontId].numDrums) {
        D_80155D88 = (fontId << 8) + drumId + 0x04000000;
        return NULL;
    }
    //    if ((u32) gSoundFontList[fontId].drums < AUDIO_RELOCATED_ADDRESS_START) {
    //        return NULL;
    //    }
    drum = gSoundFontList[fontId].drums[drumId];
    if (gSoundFontList[fontId].drums[drumId] == NULL) {
        D_80155D88 = (fontId << 8) + drumId + 0x05000000;
    }
    return drum;
}

void Audio_NoteInit(Note* note) {
    if (note->playbackState.parentLayer->adsr.decayIndex == 0) {
        Audio_AdsrInit(&note->playbackState.adsr, note->playbackState.parentLayer->channel->adsr.envelope,
                       &note->playbackState.adsrVolModUnused);
    } else {
        Audio_AdsrInit(&note->playbackState.adsr, note->playbackState.parentLayer->adsr.envelope,
                       &note->playbackState.adsrVolModUnused);
    }
    note->playbackState.adsr.state = ADSR_STATE_INITIAL;
    note->noteSubEu = gDefaultNoteSub;
}

void Audio_NoteDisable(Note* note) {
    if (note->noteSubEu.bitField0.needsInit == true) {
        note->noteSubEu.bitField0.needsInit = false;
    }
    note->playbackState.priority = 0;
    note->noteSubEu.bitField0.enabled = false;
    note->playbackState.unk_04 = 0;
    note->playbackState.parentLayer = NO_LAYER;
    note->playbackState.prevParentLayer = NO_LAYER;
    note->noteSubEu.bitField0.finished = 0;
    note->playbackState.adsr.state = ADSR_STATE_DISABLED;
    note->playbackState.adsr.current = 0.0f;
}

void Audio_ProcessNotes(void) {
    s32 pad2;
    s32 pad;
    Note* note;
    NotePlaybackState* playbackState;
    NoteSubEu* noteSub;
    NoteAttributes* attr;
    s32 i;
    NoteAttributes sp70;
    u8 bookOffset;
    f32 scale;

    for (i = 0; i < gNumNotes; i++) {
        note = &gNotes[i];

        playbackState = &note->playbackState;
        if ((playbackState->parentLayer != NO_LAYER)) {
            if ((note != playbackState->parentLayer->note) && (playbackState->unk_04 == 0)) {
                playbackState->adsr.action.asByte |= 0x10;
                playbackState->adsr.fadeOutVel = gAudioBufferParams.ticksPerUpdateInv;
                playbackState->priority = 1;
                playbackState->unk_04 = 2;
                goto out;
            } else {
                if ((playbackState->parentLayer->enabled) || (playbackState->unk_04 != 0) ||
                    (playbackState->priority <= 0)) {
                    if (playbackState->parentLayer->channel->seqPlayer == NULL) {
                        AudioSeq_SequenceChannelDisable(playbackState->parentLayer->channel);
                        playbackState->priority = 1;
                        playbackState->unk_04 = 1;
                        continue;
                    }
                    if (!(playbackState->parentLayer->channel->seqPlayer->muted &&
                          (playbackState->parentLayer->channel->muteBehavior & MUTE_BEHAVIOR_STOP_NOTES))) {
                        goto out;
                    }
                }
                Audio_SeqLayerNoteRelease(playbackState->parentLayer);
                Audio_AudioListRemove(note);
                Audio_AudioListPushFront(&note->listItem.pool->decaying, &note->listItem);
                playbackState->priority = 1;
                playbackState->unk_04 = 2;
            }
        } else if ((playbackState->unk_04 == 0) && (playbackState->priority > 0)) {
            continue;
        }
    out:

        if (playbackState->priority != 0) {
            noteSub = &note->noteSubEu;
            if ((playbackState->unk_04 > 0) || noteSub->bitField0.finished) {
                if ((playbackState->adsr.state == 0) || noteSub->bitField0.finished) {
                    if (playbackState->wantedParentLayer != NO_LAYER) {
                        Audio_NoteDisable(note);
                        if (playbackState->wantedParentLayer->channel != NULL) {
                            Audio_NoteInitForLayer(note, playbackState->wantedParentLayer);
                            Audio_NoteVibratoInit(note);
                            Audio_AudioListRemove(note);
                            AudioSeq_AudioListPushBack(&note->listItem.pool->active, &note->listItem);
                            playbackState->wantedParentLayer = NO_LAYER;
                        } else {
                            Audio_NoteDisable(note);
                            Audio_AudioListRemove(note);
                            AudioSeq_AudioListPushBack(&note->listItem.pool->disabled, &note->listItem);
                            playbackState->wantedParentLayer = NO_LAYER;
                            goto next;
                        }
                    } else {
                        Audio_NoteDisable(note);
                        Audio_AudioListRemove(note);
                        AudioSeq_AudioListPushBack(&note->listItem.pool->disabled, &note->listItem);
                        goto next;
                    }
                }
            } else if (playbackState->adsr.state == 0) {
                Audio_NoteDisable(note);
                Audio_AudioListRemove(note);
                AudioSeq_AudioListPushBack(&note->listItem.pool->disabled, &note->listItem);
                goto next;
            }

            scale = Audio_AdsrUpdate(&playbackState->adsr);
            Audio_NoteVibratoUpdate(note);
            attr = &playbackState->attributes;
            if ((playbackState->unk_04 == 1) || (playbackState->unk_04 == 2)) {
                sp70.freqMod = attr->freqMod;
                sp70.velocity = attr->velocity;
                sp70.pan = attr->pan;
                sp70.reverb = attr->reverb;
                sp70.stereo = attr->stereo;
                sp70.gain = attr->gain;
                bookOffset = noteSub->bitField1.bookOffset;
            } else {
                sp70.freqMod = playbackState->parentLayer->noteFreqMod;
                sp70.velocity = playbackState->parentLayer->noteVelocity;
                sp70.pan = playbackState->parentLayer->notePan;
                sp70.stereo = playbackState->parentLayer->stereo;
                sp70.stereo.s.is_voice = playbackState->parentLayer->channel->is_voice;
                sp70.stereo.s.is_sfx = playbackState->parentLayer->channel->is_sfx;
                sp70.reverb = playbackState->parentLayer->channel->targetReverbVol;
                sp70.gain = playbackState->parentLayer->channel->reverbIndex;

                bookOffset = playbackState->parentLayer->channel->bookOffset % 8U;
                if ((playbackState->parentLayer->channel->seqPlayer->muted) &&
                    (playbackState->parentLayer->channel->muteBehavior & 8)) {
                    sp70.freqMod = 0.0f;
                    sp70.velocity = 0.0f;
                }
            }
            sp70.freqMod *= playbackState->vibratoFreqMod * playbackState->portamentoFreqMod;
            sp70.freqMod *= gAudioBufferParams.resampleRate;
            sp70.velocity *= scale;
            Audio_InitNoteSub(note, &sp70);
            noteSub->bitField1.bookOffset = bookOffset;
        next:;
        }
    }
}

void Audio_SeqLayerDecayRelease(SequenceLayer* layer, s32 arg1) {
    Note* note;
    NoteAttributes* noteAttr;

    if (layer == NO_LAYER) {
        return;
    }
    layer->unk_3 = 0;
    if (layer->note == NULL) {
        return;
    }
    note = layer->note;
    if (layer == note->playbackState.wantedParentLayer) {
        note->playbackState.wantedParentLayer = NO_LAYER;
    }

    if (layer != note->playbackState.parentLayer) {
        if ((note->playbackState.parentLayer == NO_LAYER) && (note->playbackState.wantedParentLayer == NO_LAYER) &&
            (layer == note->playbackState.prevParentLayer) && (arg1 != 6)) {
            note->playbackState.adsr.fadeOutVel = gAudioBufferParams.ticksPerUpdateInv;
            note->playbackState.adsr.action.asByte |= 0x10;
        }
    } else {
        noteAttr = &note->playbackState.attributes;
        if (note->playbackState.adsr.state != 6) {
            noteAttr->freqMod = layer->noteFreqMod;
            noteAttr->velocity = layer->noteVelocity;
            noteAttr->pan = layer->notePan;
            noteAttr->stereo = layer->stereo;
            if (layer->channel != NULL) {
                noteAttr->reverb = layer->channel->targetReverbVol;
                noteAttr->gain = layer->channel->reverbIndex;
                if (layer->channel->seqPlayer->muted && (layer->channel->muteBehavior & 8)) {
                    note->noteSubEu.bitField0.finished = 1;
                }
            }
            note->playbackState.priority = 1;
            note->playbackState.prevParentLayer = note->playbackState.parentLayer;
            note->playbackState.parentLayer = NO_LAYER;

            if (arg1 == 7) {
                note->playbackState.adsr.fadeOutVel = gAudioBufferParams.ticksPerUpdateInv;
                note->playbackState.adsr.action.asByte |= 0x10;
                note->playbackState.unk_04 = 2;

            } else {
                note->playbackState.unk_04 = 1;
                note->playbackState.adsr.action.asByte |= 0x20;
                if (layer->adsr.decayIndex == 0) {
                    note->playbackState.adsr.fadeOutVel =
                        layer->channel->adsr.decayIndex * gAudioBufferParams.ticksPerUpdateInvScaled;
                } else {
                    note->playbackState.adsr.fadeOutVel =
                        layer->adsr.decayIndex * gAudioBufferParams.ticksPerUpdateInvScaled;
                }
                note->playbackState.adsr.sustain =
                    (s32) layer->channel->adsr.sustain * note->playbackState.adsr.current / 256.0f;
            }
        }
        if (arg1 == 6) {
            Audio_AudioListRemove(note);
            Audio_AudioListPushFront(&note->listItem.pool->decaying, &note->listItem);
        }
    }
}

void Audio_SeqLayerNoteDecay(SequenceLayer* layer) {
    Audio_SeqLayerDecayRelease(layer, ADSR_STATE_DECAY);
}

void Audio_SeqLayerNoteRelease(SequenceLayer* layer) {
    Audio_SeqLayerDecayRelease(layer, ADSR_STATE_RELEASE);
}

s32 Audio_BuildSyntheticWave(Note* note, SequenceLayer* layer, s32 waveId) {
    f32 freqMod;
    u8 harmonicIndex = 0;

    if (waveId < 128) {
        waveId = 128;
    }
    freqMod = layer->freqMod;
    if ((layer->portamento.mode != 0) && (layer->portamento.extent > 0.0f)) {
        freqMod *= layer->portamento.extent + 1.0f;
    }
    if (freqMod < 1.0f) {
        freqMod = 1.0465f;
    } else if (freqMod < 2.0f) {
        harmonicIndex = 1;
        freqMod = 0.52325f;
    } else if (freqMod < 4.0f) {
        harmonicIndex = 2;
        freqMod = 0.26263f;
    } else {
        harmonicIndex = 3;
        freqMod = 0.13081f;
    }

    layer->freqMod *= freqMod;
    note->playbackState.waveId = waveId;
    note->playbackState.harmonicIndex = harmonicIndex;
    note->noteSubEu.waveSampleAddr = &gWaveSamples[waveId - 128][harmonicIndex * 64];
    return harmonicIndex;
}

void Audio_InitSyntheticWave(Note* note, SequenceLayer* layer) {
    s32 harmonicIndex;
    s32 waveId;

    waveId = layer->instOrWave;
    if (waveId == 0xFF) {
        waveId = layer->channel->instOrWave;
    }
    harmonicIndex = note->playbackState.harmonicIndex;
    note->synthesisState.samplePosInt =
        (note->synthesisState.samplePosInt * sSamplesPerWavePeriod[Audio_BuildSyntheticWave(note, layer, waveId)]) /
        sSamplesPerWavePeriod[harmonicIndex];
}

void Audio_InitNoteList(AudioListItem* item) {
    item->prev = item;
    item->next = item;
    item->u.value = NULL;
}

void Audio_InitNoteLists(NotePool* pool) {
    Audio_InitNoteList(&pool->disabled);
    Audio_InitNoteList(&pool->decaying);
    Audio_InitNoteList(&pool->releasing);
    Audio_InitNoteList(&pool->active);
    pool->disabled.pool = pool;
    pool->decaying.pool = pool;
    pool->releasing.pool = pool;
    pool->active.pool = pool;
}

void Audio_InitNoteFreeList(void) {
    s32 i;

    Audio_InitNoteLists(&gNoteFreeLists);
    for (i = 0; i < gNumNotes; i++) {
        gNotes[i].listItem.u.value = &gNotes[i];
        gNotes[i].listItem.prev = NULL;
        AudioSeq_AudioListPushBack(&gNoteFreeLists.disabled, &gNotes[i].listItem);
    }
}

void Audio_NotePoolClear(NotePool* pool) {
    s32 poolType;
    AudioListItem* poolItem;
    AudioListItem* nextPoolItem;
    AudioListItem* freeList;

    for (poolType = 0; poolType < 4; poolType++) {
        switch (poolType) {
            case 0:
                poolItem = &pool->disabled;
                freeList = &gNoteFreeLists.disabled;
                break;
            case 1:
                poolItem = &pool->decaying;
                freeList = &gNoteFreeLists.decaying;
                break;
            case 2:
                poolItem = &pool->releasing;
                freeList = &gNoteFreeLists.releasing;
                break;
            case 3:
                poolItem = &pool->active;
                freeList = &gNoteFreeLists.active;
                break;
        }

        while (true) {
            nextPoolItem = poolItem->next;
            if ((nextPoolItem == poolItem) || (nextPoolItem == NULL)) {
                break;
            }
            Audio_AudioListRemove((Note*) nextPoolItem);
            AudioSeq_AudioListPushBack(freeList, nextPoolItem);
        }
    }
}

void Audio_NotePoolFill(NotePool* pool, s32 count) {
    s32 j;
    s32 poolType;
    AudioListItem* note;
    AudioListItem* freeList;
    AudioListItem* poolList;

    Audio_NotePoolClear(pool);

    for (poolType = 0, j = 0; j < count; poolType++) {
        if (poolType == 4) {
            return;
        }
        switch (poolType) {
            case 0:
                freeList = &gNoteFreeLists.disabled;
                poolList = &pool->disabled;
                break;
            case 1:
                freeList = &gNoteFreeLists.decaying;
                poolList = &pool->decaying;
                break;
            case 2:
                freeList = &gNoteFreeLists.releasing;
                poolList = &pool->releasing;
                break;
            case 3:
                freeList = &gNoteFreeLists.active;
                poolList = &pool->active;
                break;
        }
        while (j < count) {
            note = AudioSeq_AudioListPopBack(freeList);
            if (note == NULL) {
                break;
            }
            AudioSeq_AudioListPushBack(poolList, note);
            j++;
        }
    }
}

void Audio_AudioListPushFront(AudioListItem* list, AudioListItem* item) {
    // add 'item' to the front of the list given by 'list', if it's not in any list
    if (item->prev == NULL) {
        item->prev = list;
        item->next = list->next;
        list->next->prev = item;
        list->next = item;
        list->u.count++;
        item->pool = list->pool;
    }
}

void Audio_AudioListRemove(Note* note) {
    // remove 'item' from the list it's in, if any
    if (note->listItem.prev != NULL) {
        note->listItem.prev->next = note->listItem.next;
        note->listItem.next->prev = note->listItem.prev;
        note->listItem.prev = NULL;
    }
}

Note* Audio_FindNodeWithPrioLessThan(AudioListItem* item, s32 priority) {
    AudioListItem* priorityItem;
    AudioListItem* nextItem = item->next;

    if (nextItem == item) {
        return NULL;
    }
    priorityItem = nextItem;
    for (nextItem; nextItem != item; nextItem = nextItem->next) {
        if (((Note*) nextItem->u.value)->playbackState.priority <=
            ((Note*) priorityItem->u.value)->playbackState.priority) {
            priorityItem = nextItem;
        }
    }

    if (priorityItem == NULL) {
        return NULL;
    }

    if (((Note*) priorityItem->u.value)->playbackState.priority >= priority) {
        return NULL;
    }
    return (Note*) priorityItem->u.value;
}

void Audio_NoteInitForLayer(Note* note, SequenceLayer* layer) {
    s32 pad[4];
    s32 var_a2;
    NoteSubEu* noteSub;

    note->playbackState.prevParentLayer = NO_LAYER;
    note->playbackState.parentLayer = layer;
    note->playbackState.priority = layer->channel->notePriority;
    layer->ignoreDrumPan = 1;
    layer->unk_3 = 3;
    layer->note = note;
    layer->channel->noteUnused = note;
    layer->channel->layerUnused = layer;
    layer->noteVelocity = 0.0f;
    Audio_NoteInit(note);
    var_a2 = layer->instOrWave;
    noteSub = &note->noteSubEu;
    if (var_a2 == 0xFF) {
        var_a2 = layer->channel->instOrWave;
    }
    noteSub->waveSampleAddr = (s16*) layer->tunedSample;
    if (var_a2 >= 128) {
        noteSub->bitField1.isSyntheticWave = true;
    } else {
        noteSub->bitField1.isSyntheticWave = false;
    }
    if (noteSub->bitField1.isSyntheticWave) {
        Audio_BuildSyntheticWave(note, layer, var_a2);
    }
    note->playbackState.fontId = layer->channel->fontId;
    noteSub->bitField0.stereoHeadsetEffects = layer->channel->stereoHeadsetEffects;
    noteSub->bitField1.reverbIndex = layer->channel->someOtherPriority & 3;
}

void func_80012E28(Note* note, SequenceLayer* layer) {
    Audio_SeqLayerNoteRelease(note->playbackState.parentLayer);
    note->playbackState.wantedParentLayer = layer;
}

void Audio_NoteReleaseAndTakeOwnership(Note* note, SequenceLayer* layer) {
    note->playbackState.wantedParentLayer = layer;
    note->playbackState.priority = layer->channel->notePriority;
    note->playbackState.adsr.fadeOutVel = gAudioBufferParams.ticksPerUpdateInv;
    note->playbackState.adsr.action.asByte |= 0x10;
}

Note* Audio_AllocNoteFromDisabled(NotePool* pool, SequenceLayer* layer) {
    Note* note = AudioSeq_AudioListPopBack(&pool->disabled);

    if (note != NULL) {
        Audio_NoteInitForLayer(note, layer);
        Audio_AudioListPushFront(&pool->active, &note->listItem);
    }
    return note;
}

Note* Audio_AllocNoteFromDecaying(NotePool* pool, SequenceLayer* layer) {
    Note* note = AudioSeq_AudioListPopBack(&pool->decaying);

    if (note != NULL) {
        Audio_NoteReleaseAndTakeOwnership(note, layer);
        AudioSeq_AudioListPushBack(&pool->releasing, &note->listItem);
    }
    return note;
}

Note* Audio_AllocNoteFromActive(NotePool* pool, SequenceLayer* layer) {
    Note* rNote;
    Note* aNote;
    s32 rPriority;
    s32 aPriority;

    rPriority = aPriority = 0x10;
    rNote = Audio_FindNodeWithPrioLessThan(&pool->releasing, layer->channel->notePriority);

    if (rNote != NULL) {
        rPriority = rNote->playbackState.priority;
    }

    aNote = Audio_FindNodeWithPrioLessThan(&pool->active, layer->channel->notePriority);

    if (aNote != NULL) {
        aPriority = aNote->playbackState.priority;
    }

    if (rNote == NULL && aNote == NULL) {
        return NULL;
    }

    if (aPriority < rPriority) {
        Audio_AudioListRemove(aNote);
        func_80012E28(aNote, layer);
        AudioSeq_AudioListPushBack(&pool->releasing, &aNote->listItem);
        aNote->playbackState.priority = layer->channel->notePriority;
        return aNote;
    }
    rNote->playbackState.wantedParentLayer = layer;
    rNote->playbackState.priority = layer->channel->notePriority;
    return rNote;
}

Note* Audio_AllocNote(SequenceLayer* layer) {
    Note* note;

    if (layer->channel->noteAllocPolicy & 1) {
        note = layer->note;
        if ((note != NULL) && (layer == note->playbackState.prevParentLayer) &&
            (note->playbackState.wantedParentLayer == NO_LAYER)) {

            Audio_NoteReleaseAndTakeOwnership(note, layer);
            Audio_AudioListRemove(note);
            AudioSeq_AudioListPushBack(&note->listItem.pool->releasing, &note->listItem);
            return note;
        }
    }

    if (layer->channel->noteAllocPolicy & 2) {
        if (((note = Audio_AllocNoteFromDisabled(&layer->channel->notePool, layer)) != NULL) ||
            ((note = Audio_AllocNoteFromDecaying(&layer->channel->notePool, layer)) != NULL) ||
            ((note = Audio_AllocNoteFromActive(&layer->channel->notePool, layer)) != NULL)) {
            return note;
        }
    } else if (layer->channel->noteAllocPolicy & 4) {
        if (((note = Audio_AllocNoteFromDisabled(&layer->channel->notePool, layer)) != NULL) ||
            ((note = Audio_AllocNoteFromDisabled(&layer->channel->seqPlayer->notePool, layer)) != NULL) ||
            ((note = Audio_AllocNoteFromDecaying(&layer->channel->notePool, layer)) != NULL) ||
            ((note = Audio_AllocNoteFromDecaying(&layer->channel->seqPlayer->notePool, layer)) != NULL) ||
            ((note = Audio_AllocNoteFromActive(&layer->channel->notePool, layer)) != NULL) ||
            ((note = Audio_AllocNoteFromActive(&layer->channel->seqPlayer->notePool, layer)) != NULL)) {
            return note;
        }
    } else if (layer->channel->noteAllocPolicy & 8) {
        if (((note = Audio_AllocNoteFromDisabled(&gNoteFreeLists, layer)) != NULL) ||
            ((note = Audio_AllocNoteFromDecaying(&gNoteFreeLists, layer)) != NULL) ||
            ((note = Audio_AllocNoteFromActive(&gNoteFreeLists, layer)) != NULL)) {
            return note;
        }
    } else {
        if (((note = Audio_AllocNoteFromDisabled(&layer->channel->notePool, layer)) != NULL) ||
            ((note = Audio_AllocNoteFromDisabled(&layer->channel->seqPlayer->notePool, layer)) != NULL) ||
            ((note = Audio_AllocNoteFromDisabled(&gNoteFreeLists, layer)) != NULL) ||
            ((note = Audio_AllocNoteFromDecaying(&layer->channel->notePool, layer)) != NULL) ||
            ((note = Audio_AllocNoteFromDecaying(&layer->channel->seqPlayer->notePool, layer)) != NULL) ||
            ((note = Audio_AllocNoteFromDecaying(&gNoteFreeLists, layer)) != NULL) ||
            ((note = Audio_AllocNoteFromActive(&layer->channel->notePool, layer)) != NULL) ||
            ((note = Audio_AllocNoteFromActive(&layer->channel->seqPlayer->notePool, layer)) != NULL) ||
            ((note = Audio_AllocNoteFromActive(&gNoteFreeLists, layer)) != NULL)) {
            return note;
        }
    }
    layer->unk_3 = 0;
    return NULL;
}

void Audio_NoteInitAll(void) {
    s32 i;
    Note* note;

    for (i = 0; i < gNumNotes; i++) {
        note = &gNotes[i];

        note->noteSubEu = gZeroNoteSub;

        note->playbackState.priority = 0;
        note->playbackState.unk_04 = 0;
        note->playbackState.parentLayer = NO_LAYER;
        note->playbackState.wantedParentLayer = NO_LAYER;
        note->playbackState.prevParentLayer = NO_LAYER;
        note->playbackState.waveId = 0;
        note->playbackState.attributes.velocity = 0.0f;
        note->playbackState.adsrVolModUnused = 0;
        note->playbackState.adsr.state = 0;
        note->playbackState.adsr.action.asByte = 0;
        note->playbackState.vibratoState.active = 0;
        note->playbackState.portamento.cur = 0.0f;
        note->playbackState.portamento.speed = 0.0f;

        note->synthesisState.synthesisBuffers = AudioHeap_Alloc(&gMiscPool, sizeof(Note));
    }
}
