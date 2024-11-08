#include "sys.h"
#include "sf64audio_provisional.h"

static const char devstr00[] = "Audio:Track:Warning: No Free Notetrack\n";
static const char devstr01[] = "SUBTRACK DIM\n";
static const char devstr02[] = "Audio:Track: Warning :SUBTRACK had been stolen by other Group.\n";
static const char devstr03[] = "SEQID %d,BANKID %d\n";
static const char devstr04[] = "ERR:SUBTRACK %d NOT ALLOCATED\n";
static const char devstr05[] = "Stop Release\n";
static const char devstr06[] = "Error:Same List Add\n";
static const char devstr07[] = "Wait Time out!\n";
static const char devstr08[] = "Macro Level Over Error!\n";
static const char devstr09[] = "Macro Level Over Error!\n";
static const char devstr10[] = "WARNING: NPRG: cannot change %d\n";
static const char devstr11[] = "Audio:Track:NOTE:UNDEFINED NOTE COM. %x\n";
static const char devstr12[] = "Audio: Note:Velocity Error %d\n";
static const char devstr13[] = "Error: Subtrack no prg.\n";
static const char devstr14[] = "ERR %x\n";
static const char devstr15[] = "Error: Your assignchannel is stolen.\n";
static const char devstr16[] = "Audio:Track :Call Macro Level Over Error!\n";
static const char devstr17[] = "Audio:Track :Loops Macro Level Over Error!\n";
static const char devstr18[] = "SUB:ERR:BANK %d NOT CACHED.\n";
static const char devstr19[] = "SUB:ERR:BANK %d NOT CACHED.\n";
static const char devstr20[] = "Audio:Track: CTBLCALL Macro Level Over Error!\n";
static const char devstr21[] = "Set Noise %d\n";
static const char devstr22[] = "[%2x] \n";
static const char devstr23[] = "Err :Sub %x ,address %x:Undefined SubTrack Function %x";
static const char devstr24[] = "VoiceLoad Error Bank:%d,Prog:%d\n";
static const char devstr25[] = "Disappear Sequence or Bank %d\n";
static const char devstr26[] = "[FIN] group.\n";
static const char devstr27[] = "Macro Level Over Error!\n";
static const char devstr28[] = "Macro Level Over Error!\n";
static const char devstr29[] = "Group:Undefine upper C0h command (%x)\n";
static const char devstr30[] = "Group:Undefined Command\n";

void func_800145BC(AudioListItem* list, AudioListItem* item);
void* func_800145FC(AudioListItem* list);
u8 func_800152C0(SequenceChannel* channel, u8 arg1, Instrument** instrument, AdsrSettings* adsrSettings);

void func_80013EA0(SequenceChannel* channel) {
    s32 i;

    channel->enabled = 0;
    channel->finished = 0;
    channel->stopScript = 0;
    channel->muted = 0;
    channel->hasInstrument = false;
    channel->stereoHeadsetEffects = 0;
    channel->transposition = 0;
    channel->largeNotes = 0;
    channel->bookOffset = 0;
    channel->changes.asByte = 0xFF;
    channel->scriptState.depth = 0;
    channel->newPan = 0x40;
    channel->panChannelWeight = 0x80;
    channel->noteUnused = NULL;
    channel->someOtherPriority = 0;
    channel->targetReverbVol = 0;
    channel->reverbIndex = 0;
    channel->notePriority = 3;
    channel->delay = 0;
    channel->adsr.envelope = gDefaultEnvelope;
    channel->adsr.decayIndex = 0x20;
    channel->vibratoRateTarget = 0x800;
    channel->vibratoRateStart = 0x800;
    channel->adsr.sustain = 0;
    channel->vibratoDepthTarget = 0;
    channel->vibratoDepthStart = 0;
    channel->vibratoRateChangeDelay = 0;
    channel->vibratoDepthChangeDelay = 0;
    channel->vibratoDelay = 0;
    channel->volume = 1.0f;
    channel->volumeMod = 1.0f;
    channel->freqMod = 1.0f;
    for (i = 0; i < 8; i++) {
        channel->seqScriptIO[i] = -1;
    }
    channel->unused = 0;
    func_80012864(&channel->notePool);
}

s32 func_80013FC4(SequenceChannel* channel, s32 arg1) {
    SequenceLayer* temp_v0;
    SequenceLayer* temp;

    if (channel->layers[arg1] == NULL) {
        temp_v0 = func_800145FC(&gLayerFreeList);
        channel->layers[arg1] = temp_v0;
        if (temp_v0 == NULL) {
            channel->layers[arg1] = NULL;
            return -1;
        }
    } else {
        func_8001266C(channel->layers[arg1]);
    }
    temp = channel->layers[arg1];
    temp->channel = channel;
    temp->adsr = channel->adsr;
    temp->enabled = 1;
    temp->muted = 0;
    temp->continuousNotes = 0;
    temp->finished = 0;
    temp->adsr.decayIndex = 0;
    temp->bit1 = 0;
    temp->stereo.asByte = 0x40;
    temp->portamento.mode = 0;
    temp->state.depth = 0;
    temp->unk_3 = 0;
    temp->gateTime = 0x80;
    temp->pan = 0x40;
    temp->transposition = 0;
    temp->delay = 0;
    temp->gateDelay = 0;
    temp->delay2 = 0;
    temp->note = NULL;
    temp->instrument = NULL;
    temp->instOrWave = 0xFF;
    temp->freqMod = 1.0f;
    temp->velocitySquare = 0.0f;

    return 0;
}

void func_800140D0(SequenceLayer* layer) {
    if (layer != NULL) {
        func_8001266C(layer);
        layer->enabled = 0;
        layer->finished = 1;
    }
}

void func_8001410C(SequenceChannel* channel, s32 arg1) {
    SequenceLayer* temp_a2 = channel->layers[arg1];

    if (temp_a2 != NULL) {
        func_800145BC(&gLayerFreeList, &temp_a2->listItem);
        func_800140D0(temp_a2);
        channel->layers[arg1] = NULL;
    }
}

void func_8001415C(SequenceChannel* channel) {
    s32 var_s0;

    for (var_s0 = 0; var_s0 < ARRAY_COUNT(channel->layers); var_s0++) {
        func_8001410C(channel, var_s0);
    }
    func_80012964(&channel->notePool);
    channel->enabled = 0;
    channel->finished = 1;
}

SequenceChannel* func_800141C8(void) {
    s32 i;
    SequenceChannel* var_v1;

    for (i = 0; i < 48; i++) {
        if (gSeqChannels[i].seqPlayer == NULL) {
            return &gSeqChannels[i];
        }
    }
    return &gSeqChannelNone;
}

void func_80014244(SequencePlayer* seqPlayer, u16 arg1) {
    SequenceChannel* temp_s0;
    SequenceChannel* temp_v0;
    s32 i;

    for (i = 0; i < 16; i++) {
        if (arg1 & 1) {
            temp_s0 = seqPlayer->channels[i];
            if ((IS_SEQUENCE_CHANNEL_VALID(temp_s0) == 1) && (seqPlayer == temp_s0->seqPlayer)) {
                func_8001415C(temp_s0);
                temp_s0->seqPlayer = NULL;
            }
            temp_v0 = func_800141C8();
            if (IS_SEQUENCE_CHANNEL_VALID(temp_v0) == 0) {
                D_80155D88 = i + 0x10000;
                seqPlayer->channels[i] = temp_v0;
            } else {
                func_80013EA0(temp_v0);
                seqPlayer->channels[i] = temp_v0;
                temp_v0->seqPlayer = seqPlayer;
                temp_v0->fontId = seqPlayer->defaultFont;
                temp_v0->muteBehavior = seqPlayer->muteBehavior;
                temp_v0->noteAllocPolicy = seqPlayer->noteAllocPolicy;
            }
        }
        arg1 = arg1 >> 1;
    }
}

void func_80014370(SequencePlayer* seqPlayer, u16 arg1) {
    s32 i;

    for (i = 0; i < 16; i++) {
        if (arg1 & 1) {
            SequenceChannel* temp_s0 = seqPlayer->channels[i];

            if (IS_SEQUENCE_CHANNEL_VALID(temp_s0) == 1) {
                if (seqPlayer == temp_s0->seqPlayer) {
                    func_8001415C(temp_s0);
                    if (0) {}
                    temp_s0->seqPlayer = NULL;
                }
                seqPlayer->channels[i] = &gSeqChannelNone;
            }
        }
        arg1 = arg1 >> 1;
    }
}

void func_80014440(SequencePlayer* seqPlayer, u8 arg1, u8* arg2) {
    SequenceChannel* channel = seqPlayer->channels[arg1];
    s32 i;

    if (IS_SEQUENCE_CHANNEL_VALID(channel) != 0) {
        channel->scriptState.depth = 0;
        channel->scriptState.pc = arg2;
        channel->enabled = 1;
        channel->finished = 0;
        channel->delay = 0;
        for (i = 0; i < ARRAY_COUNT(channel->layers); i++) {
            if (channel->layers[i] != NULL) {
                func_8001410C(channel, i);
            }
        }
    }
}

void func_800144E4(SequencePlayer* seqPlayer) {
    func_80014370(seqPlayer, 0xFFFF);
    func_80012964(&seqPlayer->notePool);
    seqPlayer->finished = 1;
    seqPlayer->enabled = 0;
    if ((gSeqLoadStatus[seqPlayer->seqId] >= 2) && (gSeqLoadStatus[seqPlayer->seqId] != 5)) {
        gSeqLoadStatus[seqPlayer->seqId] = 3;
    }
    if ((gFontLoadStatus[seqPlayer->defaultFont] >= 2) && (gFontLoadStatus[seqPlayer->defaultFont] != 5)) {
        gFontLoadStatus[seqPlayer->defaultFont] = 4;
    }
    if (seqPlayer->defaultFont == gFontCache.temporary.entries[0].id) {
        gFontCache.temporary.nextSide = 1;
    } else if (seqPlayer->defaultFont == gFontCache.temporary.entries[1].id) {
        gFontCache.temporary.nextSide = 0;
    }
}

void func_800145BC(AudioListItem* list, AudioListItem* item) {
    if (item->prev == NULL) {
        list->prev->next = item;
        item->prev = list->prev;
        item->next = list;
        list->prev = item;
        list->u.count++;
        item->pool = list->pool;
    }
}

void* func_800145FC(AudioListItem* list) {
    AudioListItem* item = list->prev;

    if (item == list) {
        return NULL;
    }
    item->prev->next = list;
    list->prev = item->prev;
    item->prev = NULL;
    list->u.count--;
    return (void*) item->u.value;
}

void func_8001463C(void) {
    s32 i;

    gLayerFreeList.prev = &gLayerFreeList;
    gLayerFreeList.next = &gLayerFreeList;
    gLayerFreeList.u.value = NULL;
    gLayerFreeList.pool = NULL;

    for (i = 0; i < 64; i++) {
        gSeqLayers[i].listItem.u.value = &gSeqLayers[i];
        gSeqLayers[i].listItem.prev = NULL;
        func_800145BC(&gLayerFreeList, &gSeqLayers[i].listItem);
    }
}

u8 func_800146C0(SeqScriptState* state) {
    return *(state->pc++);
}

s16 func_800146D4(SeqScriptState* state) {
    s16 ret = *(state->pc++) << 8;

    ret = *(state->pc++) | ret;
    return ret;
}

u16 func_80014704(SeqScriptState* state) {
    u16 ret = *(state->pc++);

    if (ret & 0x80) {
        ret = (ret << 8) & 0x7F00;
        ret = *(state->pc++) | ret;
    }
    return ret;
}

void func_80014748(SequenceLayer* layer) {
    SequencePlayer* seqPlayer;
    SequenceChannel* channel; // sp60
    SeqScriptState* state;
    u8 cmd;
    Drum* drum;
    Instrument* instrument;
    TunedSample* sample;
    Portamento* portamento;
    s16 var_s2;
    u16 sp44;        // sp44
    s32 sp40 = true; // sp40

    if (!layer->enabled) {
        return;
    }
    if (layer->delay >= 2) {
        layer->delay--;
        if (!layer->muted && (layer->gateDelay >= layer->delay)) {
            func_8001266C(layer);
            layer->muted = 1;
        }
        return;
    }
    if (!layer->continuousNotes) {
        func_8001266C(layer);
    } else if ((layer->note != NULL) && (layer == layer->note->playbackState.wantedParentLayer)) {
        func_8001266C(layer);
    }
    if (((layer->portamento.mode & ~0x80) == 1) || ((layer->portamento.mode & ~0x80) == 2)) {
        layer->portamento.mode = 0;
    }
    channel = layer->channel;
    state = &layer->state;
    seqPlayer = channel->seqPlayer;
    layer->ignoreDrumPan = 1;
    while (true) {
        cmd = func_800146C0(state);
        if (cmd <= 0xC0) {
            break;
        }
        switch (cmd) { /* switch 5; irregular */
            case 0xFF:
                if (state->depth == 0) {
                    func_800140D0(layer);
                    return;
                }
                state->pc = state->stack[--state->depth];
                break;
            case 0xFC:
                sp44 = func_800146D4(state);
                state->stack[state->depth] = state->pc;
                state->depth++;
                state->pc = &seqPlayer->seqData[sp44];
                break;
            case 0xF8:
                state->remLoopIters[state->depth] = func_800146C0(state);
                state->stack[state->depth] = state->pc;
                state->depth++;
                break;
            case 0xF7:
                state->remLoopIters[state->depth - 1]--;
                if (state->remLoopIters[state->depth - 1] != 0) {
                    state->pc = state->stack[state->depth - 1];
                } else {
                    state->depth--;
                }
                break;
            case 0xFB:
                sp44 = func_800146D4(state);
                state->pc = &seqPlayer->seqData[sp44];
                break;
            case 0xF4:
                state->pc += (s8) func_800146C0(state);
                break;
            case 0xC1:
            case 0xCA:
                var_s2 = *state->pc++;
                if (cmd == 0xC1) {
                    layer->velocitySquare = (f32) (var_s2 * var_s2) / 16129.0f;
                } else {
                    layer->pan = var_s2;
                }
                break;
            case 0xC2:
            case 0xC9:
                var_s2 = *state->pc++;
                if (cmd == 0xC9) {
                    layer->gateTime = var_s2;
                } else {
                    layer->transposition = var_s2;
                }
                break;
            case 0xC4:
            case 0xC5:
                if (cmd == 0xC4) {
                    layer->continuousNotes = 1;
                } else {
                    layer->continuousNotes = 0;
                }
                func_8001266C(layer);
                break;
            case 0xC3:
                sp44 = func_80014704(state);
                layer->shortNoteDefaultDelay = sp44;
                break;
            case 0xC6:
                cmd = func_800146C0(state);
                if (cmd >= 127) {
                    if (cmd == 127) {
                        layer->instOrWave = 0;
                    } else {
                        layer->instOrWave = cmd;
                        layer->instrument = NULL;
                    }
                    if (cmd == 255) {
                        layer->adsr.decayIndex = 0;
                    }
                } else {
                    // cmd = func_800152C0(channel, cmd, &layer->instrument, &layer->adsr);
                    // layer->instOrWave = cmd;
                    if ((layer->instOrWave = func_800152C0(channel, cmd, &layer->instrument, &layer->adsr)) == 0) {
                        layer->instOrWave = 0xFF;
                    }
                }
                break;
            case 0xC7:
                layer->portamento.mode = func_800146C0(state);
                cmd = func_800146C0(state) + channel->transposition + layer->transposition + seqPlayer->transposition;
                if (cmd > 127) {
                    cmd = 0;
                }
                layer->portamentoTargetNote = cmd;
                if (layer->portamento.mode & 0x80) {
                    layer->portamentoTime = *state->pc++;
                } else {
                    sp44 = func_80014704(state);
                    layer->portamentoTime = sp44;
                }
                break;
            case 0xC8:
                layer->portamento.mode = 0;
                break;
            case 0xCB:
                sp44 = func_800146D4(state);
                layer->adsr.envelope = (EnvelopePoint*) &seqPlayer->seqData[sp44];
                layer->adsr.decayIndex = func_800146C0(state);
                break;
            case 0xCC:
                layer->bit1 = 1;
                break;
            case 0xCD:
                layer->stereo.asByte = func_800146C0(state);
                break;
            default:
                switch (cmd & 0xF0) { /* switch 6; irregular */
                    case 0xD0:
                        sp44 = (u16) seqPlayer->shortNoteVelocityTable[cmd & 0xF];
                        layer->velocitySquare = (f32) (sp44 * sp44) / 16129.0f;
                        break;
                    case 0xE0:
                        layer->gateTime = seqPlayer->shortNoteGateTimeTable[cmd & 0xF];
                        break;
                    default:
                        break;
                }
                break;
        }
    }
    if (cmd == 0xC0) {
        layer->delay = func_80014704(state);
        layer->muted = true;
    } else {
        f32 tuning;
        f32 freqMod;
        u32 instOrWave;
        s32 vel; // sp30
        f32 temp_fa1;
        f32 temp_fv1;
        f32 var_v0_2;
        s32 temp2;

        layer->muted = false;
        if (channel->largeNotes == 1) {
            switch (cmd & 0xC0) {
                case 0x00:
                    sp44 = func_80014704(state);
                    vel = *state->pc++;
                    layer->gateTime = *state->pc++;
                    layer->lastDelay = sp44;
                    break;
                case 0x40:
                    sp44 = func_80014704(state);
                    vel = *state->pc++;
                    layer->gateTime = 0;
                    layer->lastDelay = sp44;
                    break;
                case 0x80:
                    sp44 = layer->lastDelay;
                    vel = *state->pc++;
                    layer->gateTime = *state->pc++;

                    break;
            }
            if ((vel > 127) || (vel < 0)) {
                vel = 127;
            }
            layer->velocitySquare = SQ((f32) vel) / 16129.0f;
            cmd -= (cmd & 0xC0);
        } else {
            switch (cmd & 0xC0) { /* switch 4; irregular */
                case 0x0:
                    sp44 = func_80014704(state);
                    layer->lastDelay = sp44;
                    break;
                case 0x40:
                    sp44 = layer->shortNoteDefaultDelay;
                    break;
                case 0x80:
                    sp44 = layer->lastDelay;
                    break;
            }
            cmd -= (cmd & 0xC0);
        }
        layer->delay = sp44;
        layer->gateDelay = (layer->gateTime * sp44) >> 8;
        if ((seqPlayer->muted && (channel->muteBehavior & 0x50)) || (channel->muted)) {
            layer->muted = 1;
        } else {
            instOrWave = layer->instOrWave;
            if (instOrWave == 0xFF) {
                if (!channel->hasInstrument) {
                    return;
                }
                instOrWave = channel->instOrWave;
            }
            if (instOrWave == 0) {
                cmd = cmd + channel->transposition + layer->transposition;
                drum = Audio_GetDrum(channel->fontId, cmd);
                if (drum == NULL) {
                    layer->muted = true;
                    layer->delay2 = layer->delay;
                    return;
                }
                layer->adsr.envelope = drum->envelope;
                layer->adsr.decayIndex = drum->adsrDecayIndex;
                if (!layer->bit1) {
                    layer->pan = drum->pan;
                }
                layer->tunedSample = &drum->tunedSample;
                layer->freqMod = layer->tunedSample->tuning;
            } else {
                cmd = cmd + seqPlayer->transposition + channel->transposition + layer->transposition;
                if (cmd >= 0x80) {
                    layer->muted = 1;
                } else {
                    if (layer->instOrWave == 0xFF) {
                        instrument = channel->instrument;
                    } else {
                        instrument = layer->instrument;
                    }
                    if (layer->portamento.mode != 0) {

                        if (layer->portamentoTargetNote < cmd) {
                            temp2 = cmd;
                        } else {
                            temp2 = layer->portamentoTargetNote;
                        }
                        if (instrument != NULL) {
                            sample = func_80011D10(instrument, temp2);
                            sp40 = (sample == layer->tunedSample);
                            layer->tunedSample = sample;
                            tuning = sample->tuning;
                        } else {
                            tuning = 1.0f;
                            layer->tunedSample = NULL;
                        }
                        temp_fv1 = gPitchFrequencies[cmd] * tuning;
                        temp_fa1 = gPitchFrequencies[layer->portamentoTargetNote] * tuning;
                        portamento = &layer->portamento;
                        switch (portamento->mode & ~0x80) {
                            case 1:
                            case 3:
                            case 5:
                                var_v0_2 = temp_fv1;
                                freqMod = temp_fa1;
                                break;
                            case 2:
                            case 4:
                                freqMod = temp_fv1;
                                var_v0_2 = temp_fa1;
                                break;
                            default:
                                freqMod = temp_fv1;
                                var_v0_2 = temp_fv1;
                                break;
                        }

                        portamento->extent = (var_v0_2 / freqMod) - 1.0f;
                        if (layer->portamento.mode & 0x80) {
                            portamento->speed = ((s32) seqPlayer->tempo * 32512.0f) /
                                                ((f32) layer->delay * gMaxTempo * (s32) layer->portamentoTime);
                        } else {
                            portamento->speed = 127.0f / (s32) layer->portamentoTime;
                        }
                        portamento->cur = 0.0f;
                        layer->freqMod = freqMod;
                        if ((layer->portamento.mode & ~0x80) == 5) {
                            layer->portamentoTargetNote = cmd;
                        }
                    } else if (instrument != NULL) {
                        sample = func_80011D10(instrument, cmd);
                        sp40 = (sample == layer->tunedSample);
                        layer->tunedSample = sample;
                        layer->freqMod = gPitchFrequencies[cmd] * sample->tuning;
                    } else {
                        layer->tunedSample = NULL;
                        layer->freqMod = gPitchFrequencies[cmd];
                    }
                }
            }
            layer->delay2 = layer->delay;
        }
    }
    if ((layer->muted == 0) && (layer->tunedSample != NULL) && (layer->tunedSample->sample->codec == 2) &&
        (layer->tunedSample->sample->medium != 0)) {
        layer->muted = 1;
    }
    if (layer->muted == 1) {
        if ((layer->note != NULL) || (layer->continuousNotes)) {
            func_8001266C(layer);
        }
    } else {
        cmd = 0;
        if (!layer->continuousNotes) {
            cmd = 1;
        } else if ((layer->note == NULL) || ((u8) layer->unk_3 == 0)) {
            cmd = 1;
        } else if (sp40 == 0) {
            func_8001266C(layer);
            cmd = 1;
        } else if (layer != layer->note->playbackState.parentLayer) {
            cmd = 1;
        } else if (layer->tunedSample == NULL) {
            func_800127B0(layer->note, layer);
        }
        if (cmd != 0) {
            layer->note = func_8001301C(layer);
        }
        if ((layer->note != NULL) && (layer == layer->note->playbackState.parentLayer)) {
            func_80013A84(layer->note);
        }
    }
    if (!channel) {}
}

u8 func_800152C0(SequenceChannel* channel, u8 arg1, Instrument** instrument, AdsrSettings* adsrSettings) {
    Instrument* temp_v0;

    temp_v0 = Audio_GetInstrument(channel->fontId, arg1);
    if (temp_v0 == NULL) {
        *instrument = NULL;
        return 0;
    }

    adsrSettings->envelope = temp_v0->envelope;
    adsrSettings->decayIndex = temp_v0->adsrDecayIndex;
    *instrument = temp_v0;
    arg1++;
    return arg1;
}

void func_80015330(SequenceChannel* channel, u8 arg1) {
    if (arg1 >= 0x80) {
        channel->instOrWave = arg1;
        channel->instrument = NULL;
    } else if (arg1 == 0x7F) {
        channel->instOrWave = 0;
        channel->instrument = (Instrument*) 1;
    } else {
        if ((channel->instOrWave = func_800152C0(channel, arg1, &channel->instrument, &channel->adsr)) == 0) {
            channel->hasInstrument = false;
            return;
        }
    }
    channel->hasInstrument = true;
}

void func_800153C4(SequenceChannel* channel, u8 arg1) {
    channel->volume = (s32) arg1 / 127.0f;
}

void func_800153E8(SequenceChannel* channel) {
    s32 i;
    SequencePlayer* seqPlayer;
    u8 cmd;
    s8 temps8;
    u8 loBits;
    u16 sp52;
    SeqScriptState* state;
    s8 sp4B;
    u8* seqData;
    s32 pad;

    if (!channel->enabled) {
        return;
    }
    if (channel->stopScript) {
        for (i = 0; i < ARRAY_COUNT(channel->layers); i++) {
            if (channel->layers[i] != NULL) {
                func_80014748(channel->layers[i]);
            }
        }
        return;
    }
    seqPlayer = channel->seqPlayer;
    if ((seqPlayer->muted) && (channel->muteBehavior & 0x80)) {
        return;
    }

    if (channel->delay != 0) {
        channel->delay--;
    }

    if (channel->delay == 0) {

        while (true) {
            state = &channel->scriptState;
            cmd = func_800146C0(state);
            if (cmd > 0xC0) {
                switch (cmd) {
                    case 0xD5:
                    case 0xD6:
                        break;
                    case 0xFF:
                        if (state->depth == 0) {
                            func_8001415C(channel);
                            goto end_loop;
                        }
                        state->pc = state->stack[--state->depth];
                        break;
                    case 0xFE:
                        goto end_loop;
                    case 0xFD:
                        channel->delay = func_80014704(state);
                        goto end_loop;
                    case 0xEA:
                        channel->stopScript = 1;
                        goto end_loop;
                    case 0xFC:
                        // if (0 && state->depth >= 4) {
                        // }
                        sp52 = func_800146D4(state);
                        state->stack[state->depth] = state->pc;
                        state->depth++;
                        state->pc = &seqPlayer->seqData[sp52];
                        break;
                    case 0xF8:
                        // if (0 && state->depth >= 4) {
                        // }
                        state->remLoopIters[state->depth] = func_800146C0(state);
                        state->stack[state->depth] = state->pc;
                        state->depth++;
                        break;
                    case 0xF7:
                        state->remLoopIters[state->depth - 1]--;
                        if (state->remLoopIters[state->depth - 1] != 0) {
                            state->pc = state->stack[state->depth - 1];
                        } else {
                            state->depth--;
                        }
                        break;
                    case 0xF6:
                        state->depth--;
                        break;
                    case 0xF5:
                    case 0xF9:
                    case 0xFA:
                    case 0xFB:
                        sp52 = func_800146D4(state);
                        if (((cmd == 0xFA) && (sp4B != 0)) || ((cmd == 0xF9) && (sp4B >= 0)) ||
                            ((cmd == 0xF5) && (sp4B < 0))) {
                            break;
                        }
                        state->pc = &seqPlayer->seqData[sp52];
                        break;
                    case 0xF2:
                    case 0xF3:
                    case 0xF4:
                        temps8 = func_800146C0(state);
                        if (((cmd == 0xF3) && (sp4B != 0)) || ((cmd == 0xF2) && (sp4B >= 0))) {
                            break;
                        }
                        state->pc = &state->pc[temps8];
                        break;
                    case 0xF1:
                        func_80012964(&channel->notePool);
                        func_80012AC4(&channel->notePool, func_800146C0(state));
                        break;
                    case 0xF0:
                        func_80012964(&channel->notePool);
                        break;
                    case 0xC2:
                        sp52 = func_800146D4(state);
                        channel->dynTable = (u8(*)[2]) & seqPlayer->seqData[sp52];
                        break;
                    case 0xC5:
                        if (sp4B != -1) {
                            seqData = channel->dynTable[sp4B];
                            sp52 = (seqData[0] << 8) + seqData[1];
                            channel->dynTable = (u8(*)[2]) & seqPlayer->seqData[sp52];
                        }
                        break;
                    case 0xEB:
                        cmd = func_800146C0(state);
                        sp52 = ((u16*) gSeqFontTable)[seqPlayer->seqId];
                        loBits = gSeqFontTable[sp52];
                        cmd = gSeqFontTable[sp52 + loBits - cmd];
                        if (AudioHeap_SearchCaches(FONT_TABLE, CACHE_EITHER, cmd) != NULL) {
                            channel->fontId = cmd;
                        }
                        /* fallthrough */
                    case 0xC1:
                        cmd = func_800146C0(state);
                        func_80015330(channel, cmd);
                        break;
                    case 0xC3:
                        channel->largeNotes = false;
                        break;
                    case 0xC4:
                        channel->largeNotes = true;
                        break;
                    case 0xDF:
                        cmd = func_800146C0(state);
                        func_800153C4(channel, cmd);
                        channel->changes.s.volume = 1;
                        break;
                    case 0xE0:
                        channel->volumeMod = (s32) func_800146C0(state) / 128.0f;
                        channel->changes.s.volume = 1;
                        break;
                    case 0xDE:
                        sp52 = func_800146D4(state);
                        channel->freqMod = (s32) sp52 / 32768.0f;
                        channel->changes.s.freqMod = 1;
                        break;
                    case 0xD3:
                        cmd = func_800146C0(state) + 0x80;
                        channel->freqMod = gBendPitchOneOctaveFrequencies[cmd];
                        channel->changes.s.freqMod = 1;
                        break;
                    case 0xEE:
                        cmd = func_800146C0(state) + 0x80;
                        channel->freqMod = gBendPitchTwoSemitonesFrequencies[cmd];
                        channel->changes.s.freqMod = 1;
                        break;
                    case 0xDD:
                        channel->newPan = func_800146C0(state);
                        channel->changes.s.pan = 1;
                        break;
                    case 0xDC:
                        channel->panChannelWeight = func_800146C0(state);
                        channel->changes.s.pan = 1;
                        break;
                    case 0xDB:
                        temps8 = *(state->pc++);
                        channel->transposition = temps8;
                        break;
                    case 0xDA:
                        sp52 = func_800146D4(state);
                        channel->adsr.envelope = (EnvelopePoint*) &seqPlayer->seqData[sp52];
                        break;
                    case 0xD9:
                        channel->adsr.decayIndex = func_800146C0(state);
                        break;
                    case 0xD8:
                        channel->vibratoDepthTarget = func_800146C0(state) * 8;
                        channel->vibratoDepthStart = 0;
                        channel->vibratoDepthChangeDelay = 0;
                        break;
                    case 0xD7:
                        channel->vibratoRateStart = channel->vibratoRateTarget = func_800146C0(state) * 32;
                        channel->vibratoRateChangeDelay = 0;
                        break;
                    case 0xE2:
                        channel->vibratoDepthStart = func_800146C0(state) * 8;
                        channel->vibratoDepthTarget = func_800146C0(state) * 8;
                        channel->vibratoDepthChangeDelay = func_800146C0(state) * 0x10;
                        break;
                    case 0xE1:
                        channel->vibratoRateStart = func_800146C0(state) * 32;
                        channel->vibratoRateTarget = func_800146C0(state) * 32;
                        channel->vibratoRateChangeDelay = func_800146C0(state) * 0x10;
                        break;
                    case 0xE3:
                        channel->vibratoDelay = func_800146C0(state) * 0x10;
                        break;
                    case 0xD4:
                        channel->targetReverbVol = func_800146C0(state);
                        break;
                    case 0xC6:
                        cmd = func_800146C0(state);
                        sp52 = ((u16*) gSeqFontTable)[seqPlayer->seqId];
                        loBits = gSeqFontTable[sp52];
                        cmd = gSeqFontTable[sp52 + loBits - cmd];
                        if (AudioHeap_SearchCaches(FONT_TABLE, CACHE_EITHER, cmd) != NULL) {
                            channel->fontId = cmd;
                        }
                        break;
                    case 0xC7:
                        cmd = func_800146C0(state);
                        sp52 = func_800146D4(state);
                        seqData = &seqPlayer->seqData[sp52];
                        *seqData = (u8) sp4B + cmd;
                        break;
                    case 0xC8:
                    case 0xC9:
                    case 0xCC:
                        temps8 = func_800146C0(state);
                        if (cmd == 0xC8) {
                            sp4B -= temps8;
                        } else if (cmd == 0xCC) {
                            sp4B = temps8;
                        } else {
                            sp4B &= temps8;
                        }
                        break;
                    case 0xCD:
                        func_8001415C(seqPlayer->channels[func_800146C0(state)]);
                        break;
                    case 0xCA:
                        channel->muteBehavior = func_800146C0(state);
                        break;
                    case 0xCB:
                        sp52 = func_800146D4(state);
                        pad = sp52 + sp4B;
                        // seqData =&seqPlayer->seqData[sp4B];
                        sp4B = seqPlayer->seqData[pad];
                        break;
                    case 0xCE:
                        channel->unkC4 = func_800146D4(state);
                        break;
                    case 0xCF:
                        sp52 = func_800146D4(state);
                        seqData = &seqPlayer->seqData[sp52];
                        seqData[0] = (channel->unkC4 >> 8) & 0xFF;
                        seqData[1] = channel->unkC4 & 0xFF;
                        break;
                    case 0xD0:
                        channel->stereoHeadsetEffects = func_800146C0(state);
                        break;
                    case 0xD1:
                        channel->noteAllocPolicy = func_800146C0(state);
                        break;
                    case 0xD2:
                        channel->adsr.sustain = func_800146C0(state);
                        break;
                    case 0xE5:
                        channel->someOtherPriority = func_800146C0(state);
                        break;
                    case 0xE4:
                        if (sp4B != -1) {
                            if (state->depth >= 4) {
                                // eu_stubbed_printf_0("Audio:Track: CTBLCALL Macro Level Over Error!\n");
                            }
                            seqData = channel->dynTable[sp4B];
                            state->stack[state->depth++] = state->pc;
                            sp52 = (seqData[0] << 8) + seqData[1];
                            state->pc = &seqPlayer->seqData[sp52];
                            // if (0 && sp52 >= gSequenceTable->entries[seqPlayer->seqId].size) {
                            //     // eu_stubbed_printf_3("Err :Sub %x ,address %x:Undefined SubTrack Function %x",
                            //     seqChannel, state->pc, sp38);
                            // }
                        }
                        break;
                    case 0xE6:
                        channel->bookOffset = func_800146C0(state);
                        break;
                    case 0xE7:
                        sp52 = func_800146D4(state);
                        seqData = &seqPlayer->seqData[sp52];
                        channel->muteBehavior = *seqData++;
                        channel->noteAllocPolicy = *seqData++;
                        channel->notePriority = *seqData++;
                        channel->transposition = (s8) *seqData++;
                        channel->newPan = *seqData++;
                        channel->panChannelWeight = *seqData++;
                        channel->targetReverbVol = *seqData++;
                        channel->someOtherPriority = *seqData++;
                        channel->changes.s.pan = 1;
                        break;
                    case 0xE8:
                        channel->muteBehavior = func_800146C0(state);
                        channel->noteAllocPolicy = func_800146C0(state);
                        channel->notePriority = func_800146C0(state);
                        channel->transposition = (s8) func_800146C0(state);
                        channel->newPan = func_800146C0(state);
                        channel->panChannelWeight = func_800146C0(state);
                        channel->targetReverbVol = func_800146C0(state);
                        channel->someOtherPriority = func_800146C0(state);
                        channel->changes.s.pan = 1;
                        break;
                    case 0xEC:
                        channel->vibratoDepthTarget = 0;
                        channel->vibratoDepthStart = 0;
                        channel->vibratoDepthChangeDelay = 0;
                        channel->vibratoRateTarget = 0;
                        channel->vibratoRateStart = 0;
                        channel->vibratoRateChangeDelay = 0;
                        channel->freqMod = 1.0f;
                        break;
                    case 0xE9:
                        channel->notePriority = func_800146C0(state);
                        break;
                    case 0xED:
                        // cmd =
                        channel->reverbIndex = func_800146C0(state);
                        break;
                    case 0xEF:
                        func_800146D4(state);
                        func_800146C0(state);
                        break;
                }
            } else {
                loBits = cmd & 0xF;
                switch (cmd & 0xF0) {
                    case 0x0:
                        if (channel->layers[loBits] != NULL) {
                            sp4B = channel->layers[loBits]->finished;
                        } else {
                            sp4B = -1;
                        }
                        break;
                    case 0x10:
                        channel->seqScriptIO[loBits] = -1;
                        if (AudioLoad_SlowLoadSample(channel->fontId, sp4B, &channel->seqScriptIO[loBits]) == -1) {}
                        break;
                    case 0x70:
                        channel->seqScriptIO[loBits] = sp4B;
                        break;
                    case 0x80:
                        sp4B = channel->seqScriptIO[loBits];
                        if (loBits < 4) {
                            channel->seqScriptIO[loBits] = -1;
                        }
                        break;
                    case 0x50:
                        sp4B -= channel->seqScriptIO[loBits];
                        break;
                    case 0x60:
                        channel->delay = loBits;
                        goto end_loop;
                    case 0x90:
                        sp52 = func_800146D4(state);
                        if (func_80013FC4(channel, loBits) == 0) {
                            // if(1) {}
                            channel->layers[loBits]->state.pc = &seqPlayer->seqData[sp52];
                        }
                        break;
                    case 0xA0:
                        func_8001410C(channel, loBits);
                        break;
                    case 0xB0:
                        if ((sp4B != -1) && (func_80013FC4(channel, loBits) != -1)) {
                            seqData = channel->dynTable[sp4B];
                            sp52 = (seqData[0] << 8) + seqData[1];
                            channel->layers[loBits]->state.pc = &seqPlayer->seqData[sp52];
                        }
                        break;
                    case 0x20:
                        sp52 = func_800146D4(state);
                        func_80014440(seqPlayer, loBits, &seqPlayer->seqData[sp52]);
                        break;
                    case 0x30:
                        cmd = func_800146C0(state);
                        seqPlayer->channels[loBits]->seqScriptIO[cmd] = sp4B;
                        break;
                    case 0x40:
                        cmd = func_800146C0(state);
                        sp4B = seqPlayer->channels[loBits]->seqScriptIO[cmd];
                        break;
                }
            }
        }
    }
end_loop:;
    for (i = 0; i < ARRAY_COUNT(channel->layers); i++) {
        if (channel->layers[i] != NULL) {
            func_80014748(channel->layers[i]);
        }
    }
}

void func_80015FD4(SequencePlayer* seqPlayer) {
    u8 temp_s2;
    u8 temp_v0_8;
    u16 temp_v0_7;
    u8* temp_v1_7;
    SeqScriptState* temp_s0;
    s32 sp50;
    s32 i;
    s8 pad;
    u8* pad2;
    s32 pad3;

    if (!seqPlayer->enabled) {
        return;
    }
    if (((gSeqLoadStatus[seqPlayer->seqId] < 2) != 0) ||
        ((seqPlayer->defaultFont != 0xFF) && ((gFontLoadStatus[seqPlayer->defaultFont] < 2) != 0))) {
        func_800144E4(seqPlayer);
        return;
    }
    if (gSeqLoadStatus[seqPlayer->seqId] != 5) {
        gSeqLoadStatus[seqPlayer->seqId] = 2;
    }
    if (gFontLoadStatus[seqPlayer->defaultFont] != 5) {
        gFontLoadStatus[seqPlayer->defaultFont] = 2;
    }
    if (seqPlayer->muted && (seqPlayer->muteBehavior & 0x80)) {
        return;
    }
    seqPlayer->tempoAcc += seqPlayer->tempo;
    seqPlayer->tempoAcc = seqPlayer->tempoAcc + (s16) seqPlayer->tempoChange;
    if (seqPlayer->tempoAcc < gMaxTempo) {
        return;
    }
    seqPlayer->tempoAcc = (seqPlayer->tempoAcc - gMaxTempo) & 0xFFFF; // fake?
    if (seqPlayer->delay > 1) {
        seqPlayer->delay--;
    } else {
        temp_s0 = &seqPlayer->scriptState;
        seqPlayer->recalculateVolume = true;
        while (true) {
            temp_s2 = func_800146C0(temp_s0);
            if (temp_s2 == 0xFF) {
                if (temp_s0->depth == 0) {
                    func_800144E4(seqPlayer);
                    break;
                }
                temp_s0->pc = temp_s0->stack[--temp_s0->depth];
            }
            if (temp_s2 == 0xFD) {
                seqPlayer->delay = func_80014704(temp_s0);
                break;
            }
            if (temp_s2 == 0xFE) {
                seqPlayer->delay = 1;
                break;
            }
            if (temp_s2 >= 0xC0) {
                switch (temp_s2) {
                    case 0xFF:
                        break;
                    case 0xFC:
                        temp_v0_7 = func_800146D4(temp_s0);

                        temp_s0->stack[temp_s0->depth] = temp_s0->pc;
                        temp_s0->depth++;
                        temp_s0->pc = &seqPlayer->seqData[temp_v0_7];
                        break;
                    case 0xF8:
                        temp_s0->remLoopIters[temp_s0->depth] = func_800146C0(temp_s0);
                        temp_s0->stack[temp_s0->depth] = temp_s0->pc;
                        temp_s0->depth++;
                        break;
                    case 0xF7:
                        temp_s0->remLoopIters[temp_s0->depth - 1]--;
                        if (temp_s0->remLoopIters[temp_s0->depth - 1] != 0) {
                            temp_s0->pc = temp_s0->stack[temp_s0->depth - 1];
                        } else {
                            temp_s0->depth--;
                        }
                        break;
                    case 0xF5:
                    case 0xF9:
                    case 0xFA:
                    case 0xFB:
                        temp_v0_7 = func_800146D4(temp_s0);
                        if (((temp_s2 != 0xFA) || (sp50 == 0)) && ((temp_s2 != 0xF9) || (sp50 < 0)) &&
                            ((temp_s2 != 0xF5) || (sp50 >= 0))) {
                            temp_s0->pc = &seqPlayer->seqData[temp_v0_7];
                        }
                        break;
                    case 0xF2:
                    case 0xF3:
                    case 0xF4:
                        pad = func_800146C0(temp_s0);
                        if (((temp_s2 != 0xF3) || (sp50 == 0)) && ((temp_s2 != 0xF2) || (sp50 < 0))) {
                            temp_s0->pc = &temp_s0->pc[pad];
                        }
                        break;
                    case 0xF1:
                        func_80012964(&seqPlayer->notePool);
                        func_80012AC4(&seqPlayer->notePool, func_800146C0(temp_s0));
                        break;
                    case 0xF0:
                        func_80012964(&seqPlayer->notePool);
                        break;
                    case 0xDF:
                        seqPlayer->transposition = 0;
                        /* fallthrough */
                    case 0xDE:
                        seqPlayer->transposition += (s8) func_800146C0(temp_s0);
                        break;
                    case 0xDD:
                        seqPlayer->tempo = func_800146C0(temp_s0) * 0x30;
                        if (seqPlayer->tempo > gMaxTempo) {
                            seqPlayer->tempo = gMaxTempo;
                        }
                        if ((s16) seqPlayer->tempo <= 0) {
                            seqPlayer->tempo = 1;
                        }
                        break;
                    case 0xDC:
                        seqPlayer->tempoChange = (s8) func_800146C0(temp_s0) * 0x30;
                        break;
                    case 0xDA:
                        temp_s2 = func_800146C0(temp_s0);
                        temp_v0_7 = func_800146D4(temp_s0);
                        switch (temp_s2) {
                            case 0:
                            case 1:
                                if (seqPlayer->state != 2) {
                                    seqPlayer->fadeTimerUnkEu = temp_v0_7;
                                    seqPlayer->state = temp_s2;
                                }
                                break;
                            case 2:
                                seqPlayer->fadeTimer = temp_v0_7;
                                seqPlayer->state = temp_s2;
                                seqPlayer->fadeVelocity = (0.0f - seqPlayer->fadeVolume) / (s32) seqPlayer->fadeTimer;
                                break;
                        }
                        break;
                    case 0xDB:
                        temp_v0_8 = func_800146C0(temp_s0);
                        switch (seqPlayer->state) {
                            case 2:
                                break;
                            case 1:
                                seqPlayer->state = 0;
                                seqPlayer->fadeVolume = 0.0f;
                                /* fallthrough */
                            case 0:
                                seqPlayer->fadeTimer = seqPlayer->fadeTimerUnkEu;
                                if (seqPlayer->fadeTimerUnkEu != 0) {
                                    seqPlayer->fadeVelocity = (((s32) temp_v0_8 / 127.0f) - seqPlayer->fadeVolume) /
                                                              (s32) seqPlayer->fadeTimer;
                                } else {
                                    seqPlayer->fadeVolume = (s32) temp_v0_8 / 127.f;
                                }
                                break;
                        }
                        break;
                    case 0xD9:
                        seqPlayer->fadeVolumeMod = (s8) func_800146C0(temp_s0) / 127.0f;
                        break;
                    case 0xD7:
                        func_80014244(seqPlayer, func_800146D4(temp_s0));
                        break;
                    case 0xD6:
                        func_80014370(seqPlayer, func_800146D4(temp_s0));
                        break;
                    case 0xD5:
                        seqPlayer->muteVolumeMod = (s8) func_800146C0(temp_s0) / 127.0f;
                        break;
                    case 0xD4:
                        seqPlayer->muted = 1;
                        break;
                    case 0xD3:
                        seqPlayer->muteBehavior = func_800146C0(temp_s0);
                        break;
                    case 0xD1:
                    case 0xD2:
                        temp_v0_7 = func_800146D4(temp_s0);
                        temp_v1_7 = &seqPlayer->seqData[(temp_v0_7)];
                        if (temp_s2 == 0xD2) {
                            seqPlayer->shortNoteVelocityTable = temp_v1_7;
                        } else {
                            seqPlayer->shortNoteGateTimeTable = temp_v1_7;
                        }
                        break;
                    case 0xD0:
                        seqPlayer->noteAllocPolicy = func_800146C0(temp_s0);
                        break;
                    case 0xCC:
                        sp50 = func_800146C0(temp_s0);
                        break;
                    case 0xC9:
                        sp50 &= func_800146C0(temp_s0);
                        break;
                    case 0xC8:
                        sp50 -= func_800146C0(temp_s0);
                        break;
                    case 0xC7:
                        temp_s2 = func_800146C0(temp_s0);
                        temp_v0_7 = func_800146D4(temp_s0);
                        temp_v1_7 = &seqPlayer->seqData[temp_v0_7];
                        temp_v0_8 = sp50;
                        *temp_v1_7 = temp_v0_8 + temp_s2;
                        break;
                }
            } else {
                switch (temp_s2 & 0xF0) {
                    case 0x0:
                        sp50 = seqPlayer->channels[(u8) (temp_s2 & 0xF)]->finished;
                        break;
                    case 0x50:
                        sp50 -= seqPlayer->unk_07[0];
                        break;
                    case 0x70:
                        seqPlayer->unk_07[0] = sp50;
                        break;
                    case 0x80:
                        sp50 = seqPlayer->unk_07[0];
                        break;
                    case 0x90:
                        temp_v0_7 = func_800146D4(temp_s0);
                        func_80014440(seqPlayer, temp_s2 & 0xF, &seqPlayer->seqData[temp_v0_7]);
                        break;
                    case 0x10:
                        break;
                    case 0x20:
                        break;
                    case 0x40:
                        break;
                    case 0x60:
                        break;
                    case 0xA0:
                        break;
                }
            }
        }
    }
    for (i = 0; i < 0x10; i++) {
        if (IS_SEQUENCE_CHANNEL_VALID(seqPlayer->channels[i]) == 1) {
            func_800153E8(seqPlayer->channels[i]);
        }
    }
}

void func_8001678C(s32 arg0) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gSeqPlayers); i++) {
        if (gSeqPlayers[i].enabled == 1) {
            func_80015FD4(&gSeqPlayers[i]);
            func_800135A8(&gSeqPlayers[i]);
        }
    }
    func_80011FA8();
}

void func_80016804(s32 arg0) {
    SequencePlayer* seqPlayer = &gSeqPlayers[arg0];

    func_800144E4(seqPlayer);
    seqPlayer->delay = 0;
    seqPlayer->state = 1;
    seqPlayer->fadeTimer = 0;
    seqPlayer->fadeTimerUnkEu = 0;
    seqPlayer->tempoAcc = 0;
    seqPlayer->tempo = 0x1680;
    seqPlayer->tempoChange = 0;
    seqPlayer->transposition = 0;
    seqPlayer->noteAllocPolicy = 0;
    seqPlayer->shortNoteVelocityTable = gDefaultShortNoteVelocityTable;
    seqPlayer->shortNoteGateTimeTable = gDefaultShortNoteGateTimeTable;
    seqPlayer->fadeVolume = 1.0f;
    seqPlayer->fadeVolumeMod = 1.0f;
    seqPlayer->fadeVelocity = 0.0f;
    seqPlayer->volume = 0.0f;
    seqPlayer->muteVolumeMod = 0.5f;
}

void func_800168BC(void) {
    s32 i;
    s32 j;

    for (i = 0; i < ARRAY_COUNT(gSeqChannels); i++) {
        gSeqChannels[i].seqPlayer = NULL;
        gSeqChannels[i].enabled = false;
#ifdef AVOID_UB
        for (j = 0; j < ARRAY_COUNT(gSeqChannels->layers); j++) {
#else
        for (j = 0; j < 64;
             j++) { // bug: this is ARRAY_COUNT(gSeqLayers) instead of ARRAY_COUNT(gSeqChannels[i].layers)
#endif
            gSeqChannels[i].layers[j] = NULL;
        }
    }

    func_8001463C();

    for (i = 0; i < ARRAY_COUNT(gSeqLayers); i++) {
        gSeqLayers[i].channel = NULL;
        gSeqLayers[i].enabled = false;
    }
    for (i = 0; i < ARRAY_COUNT(gSeqPlayers); i++) {
        for (j = 0; j < 16; j++) {
            gSeqPlayers[i].channels[j] = &gSeqChannelNone;
        }
        gSeqPlayers[i].unk_07[0] = -1;
        gSeqPlayers[i].muteBehavior = 0xE0;
        gSeqPlayers[i].enabled = false;
        gSeqPlayers[i].muted = false;
        gSeqPlayers[i].fontDmaInProgress = false;
        gSeqPlayers[i].seqDmaInProgress = false;
        func_80012864(&gSeqPlayers[i].notePool);
        func_80016804(i);
    }
}
