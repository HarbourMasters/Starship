#include "sys.h"
#include "sf64audio_provisional.h"

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

void func_80011C58(Note* note, f32);
void func_8001268C(SequenceLayer* layer);
void func_80012C00(AudioListItem* item1, AudioListItem* item2);
void func_80012C40(Note* note);
void func_80012CEC(Note* note, SequenceLayer* layer);

void func_80011890(Note* note, NoteAttributes* noteAttr) {
    NoteSubEu* temp_v0;
    f32 var_fa0;
    f32 var_fa1;
    f32 var_fv1;
    s32 temp_t0;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a1;
    u8 sp27;
    u8 sp26;
    Stereo sp24;

    func_80011C58(note, noteAttr->freqMod);
    temp_v0 = &note->noteSubEu;
    var_fv1 = noteAttr->velocity;
    sp27 = noteAttr->pan;
    sp26 = noteAttr->reverb;
    sp24 = noteAttr->stereo;
    sp27 &= 0x7F;
    if ((temp_v0->bitField0.stereoHeadsetEffects) && (gAudioSoundMode == SOUNDMODE_HEADSET)) {
        var_a0 = sp27 >> 1;
        if (var_a0 >= 0x40) {
            var_a0 = 0x3F;
        }
        temp_v0->unk_04 = gHaasEffectDelaySizes[var_a0];
        temp_v0->unk_03 = gHaasEffectDelaySizes[63 - var_a0];
        temp_v0->bitField0.stereoStrongRight = 0;
        temp_v0->bitField0.stereoStrongLeft = 0;
        temp_v0->bitField0.usesHeadsetPanEffects = 1;

        var_fa0 = gHeadsetPanVolume[sp27];
        var_fa1 = gHeadsetPanVolume[127 - sp27];
    } else if (temp_v0->bitField0.stereoHeadsetEffects && (gAudioSoundMode == SOUNDMODE_STEREO)) {
        temp_v0->unk_03 = 0;
        temp_v0->unk_04 = 0;
        temp_v0->bitField0.usesHeadsetPanEffects = 0;

        var_fa0 = gStereoPanVolume[sp27];
        var_fa1 = gStereoPanVolume[127 - sp27];
        var_a0_2 = 0;
        var_a1 = 0;
        if (sp27 < 0x20) {
            var_a1 = 1;
        } else if (sp27 > 0x60) {
            var_a0_2 = 1;
        }
        temp_v0->bitField0.stereoStrongRight = var_a0_2;
        temp_v0->bitField0.stereoStrongLeft = var_a1;
        switch (sp24.s.bit2) {
            case 0:
                temp_v0->bitField0.stereoStrongRight = sp24.s.strongRight;
                temp_v0->bitField0.stereoStrongLeft = sp24.s.strongLeft;
                break;
            case 1:
                break;
            case 2:
                temp_v0->bitField0.stereoStrongRight = sp24.s.strongRight | var_a0_2;
                temp_v0->bitField0.stereoStrongLeft = sp24.s.strongLeft | var_a1;
                break;
            case 3:
                temp_v0->bitField0.stereoStrongRight = sp24.s.strongRight ^ var_a0_2;
                temp_v0->bitField0.stereoStrongLeft = sp24.s.strongLeft ^ var_a1;
                break;
        }
    } else if (gAudioSoundMode == SOUNDMODE_MONO) {
        var_fa0 = 0.707f;
        var_fa1 = 0.707f;
    } else {
        var_fa0 = gDefaultPanVolume[sp27];
        var_fa1 = gDefaultPanVolume[127 - sp27];
    }
    if (var_fv1 < 0.0f) {
        var_fv1 = 0.0f;
    }
    if (var_fv1 > 1.0f) {
        var_fv1 = 1.0f;
    }
    temp_v0->unk_06 = (s32) (var_fv1 * var_fa0 * 4095.999f);
    temp_v0->unk_08 = (s32) (var_fv1 * var_fa1 * 4095.999f);
    temp_v0->unk_02 = noteAttr->gain;
    if (temp_v0->unk_05 != sp26) {
        temp_v0->unk_05 = sp26;
        temp_v0->bitField0.unused = 1;
    } else if (temp_v0->bitField0.needsInit) {
        temp_v0->bitField0.unused = 1;
    } else {
        temp_v0->bitField0.unused = 0;
    }
}

void func_80011C58(Note* note, f32 arg1) {
    NoteSubEu* noteSub = &note->noteSubEu;
    f32 var_fv0;

    if (arg1 < 2.0f) {
        noteSub->bitField1.hasTwoParts = 0;
        if (arg1 > 1.99998f) {
            var_fv0 = 1.99998f;
        } else {
            var_fv0 = arg1;
        }
    } else {
        noteSub->bitField1.hasTwoParts = 1;
        if (arg1 > 3.99996f) {
            var_fv0 = 1.99998f;
        } else {
            var_fv0 = arg1 * 0.5f;
        }
    }
    note->noteSubEu.unk_0A = (s32) (var_fv0 * 32768.0f);
}

TunedSample* func_80011D10(Instrument* instrument, s32 arg1) {
    TunedSample* sample;

    if (arg1 < instrument->normalRangeLo) {
        sample = &instrument->lowPitchTunedSample;
    } else if (arg1 <= instrument->normalRangeHi) {
        sample = &instrument->normalPitchTunedSample;
    } else {
        sample = &instrument->highPitchTunedSample;
    }
    return sample;
}

Instrument* Audio_GetInstrument(s32 fontId, s32 instId) {
    Instrument* instrument;

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
    return instrument;
}

Drum* Audio_GetDrum(s32 fontId, s32 drumId) {
    Drum* drum;

    if ((gFontLoadStatus[fontId] < 2) != 0) {
        D_80155D88 = fontId + 0x10000000;
        return NULL;
    }
    if (drumId >= gSoundFontList[fontId].numDrums) {
        D_80155D88 = (fontId << 8) + drumId + 0x04000000;
        return NULL;
    }
    if ((u32) gSoundFontList[fontId].drums < AUDIO_RELOCATED_ADDRESS_START) {
        return NULL;
    }
    drum = gSoundFontList[fontId].drums[drumId];
    if (gSoundFontList[fontId].drums[drumId] == NULL) {
        D_80155D88 = (fontId << 8) + drumId + 0x05000000;
    }
    return drum;
}

void func_80011EB8(Note* note) {
    if (note->playbackState.parentLayer->adsr.decayIndex == 0) {
        func_80013B6C(&note->playbackState.adsr, note->playbackState.parentLayer->channel->adsr.envelope,
                      &note->playbackState.adsrVolModUnused);
    } else {
        func_80013B6C(&note->playbackState.adsr, note->playbackState.parentLayer->adsr.envelope,
                      &note->playbackState.adsrVolModUnused);
    }
    note->playbackState.adsr.state = 1;
    note->noteSubEu = gDefaultNoteSub;
}

void func_80011F4C(Note* note) {
    if (note->noteSubEu.bitField0.needsInit == 1) {
        note->noteSubEu.bitField0.needsInit = 0;
    }
    note->playbackState.priority = 0;
    note->playbackState.unk_04 = 0;
    note->noteSubEu.bitField0.enabled = 0;
    note->playbackState.parentLayer = NO_LAYER;
    note->playbackState.prevParentLayer = NO_LAYER;
    note->noteSubEu.bitField0.finished = 0;
    note->playbackState.adsr.state = 0;
    note->playbackState.adsr.current = 0.0f;
}

void func_80011FA8(void) {
    s32 pad2;
    s32 pad;
    Note* temp_s1;
    NotePlaybackState* var_s0;
    NoteSubEu* noteSub;
    NoteAttributes* attr;
    s32 i;
    NoteAttributes sp70;
    u8 sp6F;
    f32 temp_fs0;

    for (i = 0; i < gNumNotes; i++) {
        temp_s1 = &gNotes[i];

        var_s0 = &temp_s1->playbackState;
        if ((var_s0->parentLayer != NO_LAYER)) {
            if ((u32) var_s0->parentLayer < 0x7FFFFFFF) {
                continue;
            }

            if ((temp_s1 != var_s0->parentLayer->note) && (var_s0->unk_04 == 0)) {
                var_s0->adsr.action.asByte |= 0x10;
                var_s0->adsr.fadeOutVel = gAudioBufferParams.ticksPerUpdateInv;
                var_s0->priority = 1;
                var_s0->unk_04 = 2;
                goto block_21;
            } else {
                if ((var_s0->parentLayer->enabled) || (var_s0->unk_04 != 0) || (var_s0->priority <= 0)) {
                    if (var_s0->parentLayer->channel->seqPlayer == NULL) {
                        func_8001415C(var_s0->parentLayer->channel);
                        var_s0->priority = 1;
                        var_s0->unk_04 = 1;
                        continue;
                    }
                    if (!(var_s0->parentLayer->channel->seqPlayer->muted &&
                          (var_s0->parentLayer->channel->muteBehavior & 0x40))) {
                        goto block_21;
                    }
                }
                func_8001268C(var_s0->parentLayer);
                func_80012C40(temp_s1);
                func_80012C00(&temp_s1->listItem.pool->decaying, &temp_s1->listItem);
                var_s0->priority = 1;
                var_s0->unk_04 = 2;
            }
        } else if ((var_s0->unk_04 == 0) && (var_s0->priority > 0)) {
            continue;
        }
    block_21:

        if (var_s0->priority != 0) {
            if (1) {}
            noteSub = &temp_s1->noteSubEu;
            if ((var_s0->unk_04 > 0) || noteSub->bitField0.finished) {
                if ((var_s0->adsr.state == 0) || noteSub->bitField0.finished) {
                    if (var_s0->wantedParentLayer != NO_LAYER) {
                        func_80011F4C(temp_s1);
                        if (var_s0->wantedParentLayer->channel != NULL) {
                            func_80012CEC(temp_s1, var_s0->wantedParentLayer);
                            func_80013A84(temp_s1);
                            func_80012C40(temp_s1);
                            func_800145BC(&temp_s1->listItem.pool->active, &temp_s1->listItem);
                            var_s0->wantedParentLayer = NO_LAYER;
                        } else {
                            func_80011F4C(temp_s1);
                            func_80012C40(temp_s1);
                            func_800145BC(&temp_s1->listItem.pool->disabled, &temp_s1->listItem);
                            var_s0->wantedParentLayer = NO_LAYER;
                            goto next;
                        }
                    } else {
                        func_80011F4C(temp_s1);
                        func_80012C40(temp_s1);
                        func_800145BC(&temp_s1->listItem.pool->disabled, &temp_s1->listItem);
                        goto next;
                    }
                }
            } else if (var_s0->adsr.state == 0) {
                func_80011F4C(temp_s1);
                func_80012C40(temp_s1);
                func_800145BC(&temp_s1->listItem.pool->disabled, &temp_s1->listItem);
                goto next;
            }

            temp_fs0 = func_80013B90(&var_s0->adsr);
            func_80013A18(temp_s1);
            attr = &var_s0->attributes;
            if ((var_s0->unk_04 == 1) || (var_s0->unk_04 == 2)) {

                sp70.freqMod = attr->freqMod;
                sp70.velocity = attr->velocity;
                sp70.pan = attr->pan;
                sp70.reverb = attr->reverb;
                sp70.stereo = attr->stereo;
                sp70.gain = attr->gain;
                sp6F = noteSub->bitField1.bookOffset;
            } else {
                sp70.freqMod = var_s0->parentLayer->noteFreqMod;
                sp70.velocity = var_s0->parentLayer->noteVelocity;
                sp70.pan = var_s0->parentLayer->notePan;
                sp70.stereo = var_s0->parentLayer->stereo;
                sp70.reverb = var_s0->parentLayer->channel->targetReverbVol;
                sp70.gain = var_s0->parentLayer->channel->reverbIndex;

                sp6F = var_s0->parentLayer->channel->bookOffset & 7;
                if ((var_s0->parentLayer->channel->seqPlayer->muted) &&
                    (var_s0->parentLayer->channel->muteBehavior & 8)) {
                    sp70.freqMod = 0.0f;
                    sp70.velocity = 0.0f;
                }
            }
            sp70.freqMod *= (var_s0->vibratoFreqMod * var_s0->portamentoFreqMod);
            sp70.freqMod *= gAudioBufferParams.resampleRate;
            sp70.velocity *= temp_fs0;
            func_80011890(temp_s1, &sp70);
            noteSub->bitField1.bookOffset = sp6F;
        next:;
        }
    }
}

void func_80012438(SequenceLayer* layer, s32 arg1) {
    Note* temp_v0;
    NoteAttributes* temp_v0_3;

    if (layer == NO_LAYER) {
        return;
    }
    layer->unk_3 = 0;
    if (layer->note == NULL) {
        return;
    }
    temp_v0 = layer->note;
    if (layer == temp_v0->playbackState.wantedParentLayer) {
        temp_v0->playbackState.wantedParentLayer = NO_LAYER;
    }

    if (layer != temp_v0->playbackState.parentLayer) {
        if ((temp_v0->playbackState.parentLayer == NO_LAYER) &&
            (temp_v0->playbackState.wantedParentLayer == NO_LAYER) &&
            (layer == temp_v0->playbackState.prevParentLayer) && (arg1 != 6)) {
            temp_v0->playbackState.adsr.fadeOutVel = gAudioBufferParams.ticksPerUpdateInv;
            temp_v0->playbackState.adsr.action.asByte |= 0x10;
        }
        return;
    }
    temp_v0_3 = &temp_v0->playbackState.attributes;
    if (temp_v0->playbackState.adsr.state != 6) {
        temp_v0_3->freqMod = layer->noteFreqMod;
        temp_v0_3->velocity = layer->noteVelocity;
        temp_v0_3->pan = layer->notePan;
        temp_v0_3->stereo = layer->stereo;
        if (layer->channel != NULL) {
            temp_v0_3->reverb = layer->channel->targetReverbVol;
            temp_v0_3->gain = layer->channel->reverbIndex;
            if (layer->channel->seqPlayer->muted && (layer->channel->muteBehavior & 8)) {
                temp_v0->noteSubEu.bitField0.finished = 1;
            }
        }
        temp_v0->playbackState.priority = 1;
        temp_v0->playbackState.prevParentLayer = temp_v0->playbackState.parentLayer;
        temp_v0->playbackState.parentLayer = NO_LAYER;

        if (arg1 == 7) {
            temp_v0->playbackState.adsr.fadeOutVel = gAudioBufferParams.ticksPerUpdateInv;
            temp_v0->playbackState.adsr.action.asByte |= 0x10;
            temp_v0->playbackState.unk_04 = 2;

        } else {
            temp_v0->playbackState.unk_04 = 1;
            temp_v0->playbackState.adsr.action.asByte |= 0x20;
            if (layer->adsr.decayIndex == 0) {
                temp_v0->playbackState.adsr.fadeOutVel =
                    layer->channel->adsr.decayIndex * gAudioBufferParams.ticksPerUpdateInvScaled;
            } else {
                temp_v0->playbackState.adsr.fadeOutVel =
                    layer->adsr.decayIndex * gAudioBufferParams.ticksPerUpdateInvScaled;
            }
            temp_v0->playbackState.adsr.sustain =
                (s32) layer->channel->adsr.sustain * temp_v0->playbackState.adsr.current / 256.0f;
        }
    }
    if (arg1 == 6) {
        func_80012C40(temp_v0);
        func_80012C00(&temp_v0->listItem.pool->decaying, &temp_v0->listItem);
    }
}

void func_8001266C(SequenceLayer* layer) {
    func_80012438(layer, 6);
}

void func_8001268C(SequenceLayer* layer) {
    func_80012438(layer, 7);
}

s32 func_800126AC(Note* note, SequenceLayer* layer, s32 waveId) {
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

void func_800127B0(Note* note, SequenceLayer* layer) {
    s32 sp1C;
    s32 var_a2;

    var_a2 = layer->instOrWave;
    if (var_a2 == 0xFF) {
        var_a2 = layer->channel->instOrWave;
    }
    sp1C = note->playbackState.harmonicIndex;
    note->synthesisState.samplePosInt =
        (note->synthesisState.samplePosInt * sSamplesPerWavePeriod[func_800126AC(note, layer, var_a2)]) /
        sSamplesPerWavePeriod[sp1C];
}

void func_80012854(AudioListItem* item) {
    item->prev = item;
    item->next = item;
    item->u.value = NULL;
}

void func_80012864(NotePool* pool) {
    func_80012854(&pool->disabled);
    func_80012854(&pool->decaying);
    func_80012854(&pool->releasing);
    func_80012854(&pool->active);
    pool->disabled.pool = pool;
    pool->decaying.pool = pool;
    pool->releasing.pool = pool;
    pool->active.pool = pool;
}

void func_800128B4(void) {
    s32 var_s1;

    func_80012864(&gNoteFreeLists);
    for (var_s1 = 0; var_s1 < gNumNotes; var_s1++) {
        gNotes[var_s1].listItem.u.value = &gNotes[var_s1];
        gNotes[var_s1].listItem.prev = NULL;
        func_800145BC(&gNoteFreeLists.disabled, &gNotes[var_s1].listItem);
    }
}

void func_80012964(NotePool* pool) {
    s32 var_s3;
    AudioListItem* sp48;
    AudioListItem* var_s0;
    AudioListItem* sp40;

    for (var_s3 = 0; var_s3 < 4; var_s3++) {
        switch (var_s3) { /* irregular */
            case 0:
                sp48 = &pool->disabled;
                sp40 = &gNoteFreeLists.disabled;
                break;
            case 1:
                sp48 = &pool->decaying;
                sp40 = &gNoteFreeLists.decaying;
                break;
            case 2:
                sp48 = &pool->releasing;
                sp40 = &gNoteFreeLists.releasing;
                break;
            case 3:
                sp48 = &pool->active;
                sp40 = &gNoteFreeLists.active;
                break;
        }

        while (true) {
            var_s0 = sp48->next;
            if ((var_s0 == sp48) || (var_s0 == NULL)) {
                break;
            }
            func_80012C40((Note*) var_s0);
            func_800145BC(sp40, var_s0);
        }
    }
}

void func_80012AC4(NotePool* pool, s32 arg1) {
    s32 var_s0;
    s32 var_s4;
    AudioListItem* temp_v0;
    AudioListItem* sp48;
    AudioListItem* sp44;

    func_80012964(pool);
    var_s4 = 0;
    var_s0 = 0;
    while (var_s0 < arg1) {
        if (var_s4 == 4) {
            return;
        }
        switch (var_s4) {
            case 0:
                sp48 = &gNoteFreeLists.disabled;
                sp44 = &pool->disabled;
                break;
            case 1:
                sp48 = &gNoteFreeLists.decaying;
                sp44 = &pool->decaying;
                break;
            case 2:
                sp48 = &gNoteFreeLists.releasing;
                sp44 = &pool->releasing;
                break;
            case 3:
                sp48 = &gNoteFreeLists.active;
                sp44 = &pool->active;
                break;
        }
        while (var_s0 < arg1) {
            temp_v0 = func_800145FC(sp48);
            if (temp_v0 == NULL) {
                break;
            }
            func_800145BC(sp44, temp_v0);
            var_s0++;
        }
        var_s4++;
    }
}

void func_80012C00(AudioListItem* item1, AudioListItem* item2) {
    if (item2->prev == NULL) {
        item2->prev = item1;
        item2->next = item1->next;
        item1->next->prev = item2;
        item1->next = item2;
        item1->u.count += 1;
        item2->pool = item1->pool;
    }
}

void func_80012C40(Note* note) {
    if (note->listItem.prev != NULL) {
        note->listItem.prev->next = note->listItem.next;
        note->listItem.next->prev = note->listItem.prev;
        note->listItem.prev = NULL;
    }
}

Note* func_80012C6C(AudioListItem* item, s32 priority) {
    AudioListItem* var_v0;
    AudioListItem* var_v1;
    void* temp_a0;

    var_v0 = item->next;
    if (var_v0 == item) {
        return NULL;
    }
    for (var_v1 = var_v0; var_v0 != item; var_v0 = var_v0->next) {
        if (((Note*) var_v1->u.value)->playbackState.priority >= ((Note*) var_v0->u.value)->playbackState.priority) {
            var_v1 = var_v0;
        }
        // var_v0 = var_v0->next;
    }
    if (var_v1 == NULL) {
        return NULL;
    }

    if (((Note*) var_v1->u.value)->playbackState.priority >= priority) {
        return NULL;
    }
    return (Note*) var_v1->u.value;
}

void func_80012CEC(Note* note, SequenceLayer* layer) {
    s32 pad[4];
    s32 var_a2;
    NoteSubEu* temp_v0;

    note->playbackState.prevParentLayer = NO_LAYER;
    note->playbackState.parentLayer = layer;
    note->playbackState.priority = layer->channel->notePriority;
    layer->ignoreDrumPan = 1;
    layer->unk_3 = 3;
    layer->note = note;
    layer->channel->noteUnused = note;
    layer->channel->layerUnused = layer;
    layer->noteVelocity = 0.0f;
    func_80011EB8(note);
    var_a2 = layer->instOrWave;
    temp_v0 = &note->noteSubEu;
    if (var_a2 == 0xFF) {
        var_a2 = layer->channel->instOrWave;
    }
    temp_v0->waveSampleAddr = (s16*) layer->tunedSample;
    if (var_a2 >= 0x80) {
        temp_v0->bitField1.isSyntheticWave = 1;
    } else {
        temp_v0->bitField1.isSyntheticWave = 0;
    }
    if (temp_v0->bitField1.isSyntheticWave) {
        func_800126AC(note, layer, var_a2);
    }
    note->playbackState.fontId = layer->channel->fontId;
    temp_v0->bitField0.stereoHeadsetEffects = layer->channel->stereoHeadsetEffects;
    temp_v0->bitField1.reverbIndex = layer->channel->someOtherPriority & 3;
}

void func_80012E28(Note* note, SequenceLayer* layer) {
    func_8001268C(note->playbackState.parentLayer);
    note->playbackState.wantedParentLayer = layer;
}

void func_80012E5C(Note* note, SequenceLayer* layer) {
    note->playbackState.wantedParentLayer = layer;
    note->playbackState.priority = layer->channel->notePriority;
    note->playbackState.adsr.fadeOutVel = gAudioBufferParams.ticksPerUpdateInv;
    note->playbackState.adsr.action.asByte |= 0x10;
}

Note* func_80012E88(NotePool* pool, SequenceLayer* layer) {
    Note* temp_v0 = func_800145FC(&pool->disabled);

    if (temp_v0 != NULL) {
        func_80012CEC(temp_v0, layer);
        func_80012C00(&pool->active, &temp_v0->listItem);
    }
    return temp_v0;
}

Note* func_80012ED4(NotePool* pool, SequenceLayer* layer) {
    Note* sp1C = func_800145FC(&pool->decaying);

    if (sp1C != NULL) {
        func_80012E5C(sp1C, layer);
        func_800145BC(&pool->releasing, &sp1C->listItem);
    }
    return sp1C;
}

Note* func_80012F24(NotePool* pool, SequenceLayer* layer) {
    Note* sp34;
    Note* sp30;
    s32 sp2C;
    s32 sp28;

    sp2C = sp28 = 0x10;
    sp34 = func_80012C6C(&pool->releasing, layer->channel->notePriority);
    if (sp34 != NULL) {
        sp2C = sp34->playbackState.priority;
    }
    sp30 = func_80012C6C(&pool->active, layer->channel->notePriority);
    if (sp30 != NULL) {
        sp28 = sp30->playbackState.priority;
    }
    if ((sp34 == NULL) && (sp30 == NULL)) {
        return NULL;
    }
    if (sp28 < sp2C) {
        func_80012C40(sp30);
        func_80012E28(sp30, layer);
        func_800145BC(&pool->releasing, &sp30->listItem);
        sp30->playbackState.priority = layer->channel->notePriority;
        return sp30;
    } else {
        sp34->playbackState.wantedParentLayer = layer;
        sp34->playbackState.priority = layer->channel->notePriority;
        return sp34;
    }
}

Note* func_8001301C(SequenceLayer* layer) {
    Note* sp24;

    if (layer->channel->noteAllocPolicy & 1) {
        sp24 = layer->note;
        if ((sp24 != NULL) && (layer == sp24->playbackState.prevParentLayer) &&
            (sp24->playbackState.wantedParentLayer == NO_LAYER)) {

            func_80012E5C(sp24, layer);
            func_80012C40(sp24);
            func_800145BC(&sp24->listItem.pool->releasing, &sp24->listItem);
            return sp24;
        }
    }

    if (layer->channel->noteAllocPolicy & 2) {
        if (((sp24 = func_80012E88(&layer->channel->notePool, layer)) != NULL) ||
            ((sp24 = func_80012ED4(&layer->channel->notePool, layer)) != NULL) ||
            ((sp24 = func_80012F24(&layer->channel->notePool, layer)) != NULL)) {
            return sp24;
        }
    } else if (layer->channel->noteAllocPolicy & 4) {
        if (((sp24 = func_80012E88(&layer->channel->notePool, layer)) != NULL) ||
            ((sp24 = func_80012E88(&layer->channel->seqPlayer->notePool, layer)) != NULL) ||
            ((sp24 = func_80012ED4(&layer->channel->notePool, layer)) != NULL) ||
            ((sp24 = func_80012ED4(&layer->channel->seqPlayer->notePool, layer)) != NULL) ||
            ((sp24 = func_80012F24(&layer->channel->notePool, layer)) != NULL) ||
            ((sp24 = func_80012F24(&layer->channel->seqPlayer->notePool, layer)) != NULL)) {
            return sp24;
        }
    } else if (layer->channel->noteAllocPolicy & 8) {
        if (((sp24 = func_80012E88(&gNoteFreeLists, layer)) != NULL) ||
            ((sp24 = func_80012ED4(&gNoteFreeLists, layer)) != NULL) ||
            ((sp24 = func_80012F24(&gNoteFreeLists, layer)) != NULL)) {
            return sp24;
        }
    } else {
        if (((sp24 = func_80012E88(&layer->channel->notePool, layer)) != NULL) ||
            ((sp24 = func_80012E88(&layer->channel->seqPlayer->notePool, layer)) != NULL) ||
            ((sp24 = func_80012E88(&gNoteFreeLists, layer)) != NULL) ||
            ((sp24 = func_80012ED4(&layer->channel->notePool, layer)) != NULL) ||
            ((sp24 = func_80012ED4(&layer->channel->seqPlayer->notePool, layer)) != NULL) ||
            ((sp24 = func_80012ED4(&gNoteFreeLists, layer)) != NULL) ||
            ((sp24 = func_80012F24(&layer->channel->notePool, layer)) != NULL) ||
            ((sp24 = func_80012F24(&layer->channel->seqPlayer->notePool, layer)) != NULL) ||
            ((sp24 = func_80012F24(&gNoteFreeLists, layer)) != NULL)) {
            return sp24;
        }
    }
    layer->unk_3 = 0;
    return NULL;
}

void func_800132E8(void) {
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
