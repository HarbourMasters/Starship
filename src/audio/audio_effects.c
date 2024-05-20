#include "sys.h"
#include "sf64audio_provisional.h"

static const char devstr[] = "Audio:Envp: overflow  %f\n";

void func_80013400(SequenceChannel* channel, s32 updateVolume) {
    s32 i;

    if (channel->changes.s.volume || updateVolume) {
        f32 channelVolume = channel->volume * channel->volumeMod * channel->seqPlayer->appliedFadeVolume;

        if (channel->seqPlayer->muted && (channel->muteBehavior & 0x20)) {
            channelVolume = channel->seqPlayer->muteVolumeMod * channelVolume;
        }
        channel->appliedVolume = SQ(channelVolume);
    }
    if (channel->changes.s.pan) {
        channel->pan = channel->newPan * channel->panChannelWeight;
    }
    for (i = 0; i < ARRAY_COUNT(channel->layers); i++) {
        SequenceLayer* layer = channel->layers[i];

        if ((layer != NULL) && layer->enabled && (layer->note != NULL)) {
            if (layer->ignoreDrumPan) {
                layer->noteFreqMod = layer->freqMod * channel->freqMod;
                layer->noteVelocity = layer->velocitySquare * channel->appliedVolume;
                layer->notePan = (channel->pan + (layer->pan * (0x80 - channel->panChannelWeight))) >> 7;
                layer->ignoreDrumPan = false;
            } else {
                if (channel->changes.s.freqMod) {
                    layer->noteFreqMod = layer->freqMod * channel->freqMod;
                }
                if (channel->changes.s.volume || updateVolume) {
                    layer->noteVelocity = layer->velocitySquare * channel->appliedVolume;
                }
                if (channel->changes.s.pan) {
                    layer->notePan = (channel->pan + (layer->pan * (0x80 - channel->panChannelWeight))) >> 7;
                }
            }
        }
    }
    channel->changes.asByte = 0;
}

void func_800135A8(SequencePlayer* seqplayer) {
    s32 i;

    if (seqplayer->fadeTimer != 0) {
        seqplayer->fadeVolume += seqplayer->fadeVelocity;
        seqplayer->recalculateVolume = true;
        if (seqplayer->fadeVolume > 1.0f) {
            seqplayer->fadeVolume = 1.0f;
        }
        if (seqplayer->fadeVolume < 0.0f) {
            seqplayer->fadeVolume = 0.0f;
        }
        seqplayer->fadeTimer--;
        if ((seqplayer->fadeTimer == 0) && (seqplayer->state == 2)) {
            func_800144E4(seqplayer);
            return;
        }
    }
    if (seqplayer->recalculateVolume) {
        seqplayer->appliedFadeVolume = seqplayer->fadeVolume * seqplayer->fadeVolumeMod;
    }
    for (i = 0; i < 16; i++) {
        if ((IS_SEQUENCE_CHANNEL_VALID(seqplayer->channels[i]) == 1) && (seqplayer->channels[i]->enabled == 1)) {
            func_80013400(seqplayer->channels[i], seqplayer->recalculateVolume);
        }
    }
    seqplayer->recalculateVolume = false;
}

f32 func_80013708(Portamento* portamento) {
    u32 temp;
    f32 temp2;

    portamento->cur += portamento->speed;
    temp = portamento->cur;
    if (temp > 127) {
        temp = 127;
    }
    temp2 = 1.0f + ((gBendPitchOneOctaveFrequencies[0x80 + temp] - 1.0f) * portamento->extent);
    return temp2;
}

s16 func_800137DC(VibratoState* vibrato) {
    s32 index;

    vibrato->time += (s32) vibrato->rate;
    index = (vibrato->time >> 10) & 0x3F;
    return vibrato->curve[index] >> 8;
}

f32 func_80013820(VibratoState* vibrato) {
    s32 ret;
    f32 temp;
    f32 temp2;

    if (vibrato->delay != 0) {
        vibrato->delay--;
        return 1.0f;
    }
    if (vibrato->depthChangeTimer) {
        if (vibrato->depthChangeTimer == 1) {
            vibrato->depth = (s32) vibrato->channel->vibratoDepthTarget;
        } else {
            vibrato->depth +=
                ((s32) vibrato->channel->vibratoDepthTarget - vibrato->depth) / (s32) vibrato->depthChangeTimer;
        }
        vibrato->depthChangeTimer--;
    } else if (vibrato->channel->vibratoDepthTarget != (s32) vibrato->depth) {
        if ((vibrato->depthChangeTimer = vibrato->channel->vibratoDepthChangeDelay) == 0) {
            vibrato->depth = (s32) vibrato->channel->vibratoDepthTarget;
        }
    }
    if (vibrato->rateChangeTimer) {
        if (vibrato->rateChangeTimer == 1) {
            vibrato->rate = (s32) vibrato->channel->vibratoRateTarget;
        } else {
            vibrato->rate +=
                ((s32) vibrato->channel->vibratoRateTarget - vibrato->rate) / (s32) vibrato->rateChangeTimer;
        }
        vibrato->rateChangeTimer--;
    } else if (vibrato->channel->vibratoRateTarget != (s32) vibrato->rate) {
        if ((vibrato->rateChangeTimer = vibrato->channel->vibratoRateChangeDelay) == 0) {
            vibrato->rate = (s32) vibrato->channel->vibratoRateTarget;
        }
    }
    if (vibrato->depth == 0.0f) {
        return 1.0f;
    }
    ret = func_800137DC(vibrato);
    temp = vibrato->depth / 4096.0f;
    temp2 = 1.0f + temp * (gBendPitchOneOctaveFrequencies[0x80 + ret] - 1.0f);
    return temp2;
}

void func_80013A18(Note* note) {
    if (note->playbackState.portamento.mode != 0) {
        note->playbackState.portamentoFreqMod = func_80013708(&note->playbackState.portamento);
    }
    if ((note->playbackState.vibratoState.active != 0) && (note->playbackState.parentLayer != NO_LAYER)) {
        note->playbackState.vibratoFreqMod = func_80013820(&note->playbackState.vibratoState);
    }
}

void func_80013A84(Note* note) {
    NotePlaybackState* temp_v0_3 = &note->playbackState;
    VibratoState* temp_v1 = &temp_v0_3->vibratoState;

    temp_v1->active = 1;
    temp_v1->time = 0;
    temp_v0_3->vibratoFreqMod = 1.0f;
    temp_v0_3->portamentoFreqMod = 1.0f;

    temp_v1->curve = gWaveSamples[2];

    temp_v1->channel = temp_v0_3->parentLayer->channel;

    if ((temp_v1->depthChangeTimer = temp_v1->channel->vibratoDepthChangeDelay) == 0) {
        temp_v1->depth = (s32) temp_v1->channel->vibratoDepthTarget;
    } else {
        temp_v1->depth = (s32) temp_v1->channel->vibratoDepthStart;
    }
    if ((temp_v1->rateChangeTimer = temp_v1->channel->vibratoRateChangeDelay) == 0) {
        temp_v1->rate = (s32) temp_v1->channel->vibratoRateTarget;
    } else {
        temp_v1->rate = (s32) temp_v1->channel->vibratoRateStart;
    }

    temp_v1->delay = temp_v1->channel->vibratoDelay;
    temp_v0_3->portamento = temp_v0_3->parentLayer->portamento;
}

void func_80013B6C(AdsrState* adsr, EnvelopePoint* envelope, s16* arg2) {
    adsr->action.asByte = 0;
    adsr->state = 0;
    adsr->delay = 0;
    adsr->envelope = envelope;
    adsr->sustain = 0.0f;
    adsr->current = 0.0f;
}

f32 func_80013B90(AdsrState* adsr) {
    u8 action = adsr->action.asByte;
    u8 state = adsr->state;

    switch (state) {
        case 0:
            return 0.0f;
        case 1:
            if (action & 0x40) {
                adsr->state = 5;
                break;
            }
        case 2:
            adsr->envIndex = 0;
            adsr->state = 3;
        case_3:
        case 3:
            adsr->delay = adsr->envelope[adsr->envIndex].delay;
            switch (adsr->delay) {
                case 0:
                    adsr->state = 0;
                    break;
                case -1:
                    adsr->state = 5;
                    break;
                case -2:
                    adsr->envIndex = adsr->envelope[adsr->envIndex].arg;
                    goto case_3;
                case -3:
                    adsr->state = 1;
                    break;
                default:
                    if (adsr->delay >= 4) {
                        adsr->delay = (adsr->delay * gAudioBufferParams.ticksPerUpdate / gAudioBufferParams.count) / 4;
                    }
                    if (adsr->delay == 0) {
                        adsr->delay = 1;
                    }

                    adsr->target = adsr->envelope[adsr->envIndex].arg / 32767.0f;
                    adsr->target = SQ(adsr->target);
                    adsr->velocity = (adsr->target - adsr->current) / adsr->delay;
                    adsr->state = 4;
                    adsr->envIndex++;
                    break;
            }
            if (adsr->state != 4) {
                break;
            }
        case 4:
            adsr->delay -= 1;
            adsr->current += adsr->velocity;
            if (adsr->delay <= 0) {
                adsr->state = 3;
            }
            break;
        case 6:
        case 7:
            adsr->current -= adsr->fadeOutVel;
            if ((adsr->sustain != 0.0f) && (state == 6)) {
                if (adsr->current < adsr->sustain) {
                    adsr->current = adsr->sustain;
                    adsr->delay = 0x80;
                    adsr->state = 8;
                }
            } else if (adsr->current < 0.00001f) {
                adsr->current = 0.0f;
                adsr->state = 0;
            }
            break;
        case 8:
            adsr->delay--;
            if (adsr->delay == 0) {
                adsr->state = 7;
            }
            break;
    }
    if (action & 0x20) {
        adsr->state = 6;
        adsr->action.asByte = action & ~0x20;
    }
    if (action & 0x10) {
        adsr->state = 7;
        adsr->action.asByte = action & ~0x10;
    }
    if (adsr->current < 0.0f) {
        return 0.0f;
    }
    if (adsr->current > 1.0f) {
        return 1.0f;
    }
    return adsr->current;
}
