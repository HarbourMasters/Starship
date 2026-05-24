#include <chrono>

#include <spdlog/spdlog.h>
#include <ship/utils/StringHelper.h>
#include <ship/events/EventSystem.h>
#include "port/ShipInit.h"
#include "port/resource/importers/ResourceUtil.h"

#include "sf64audio_provisional.h"
#include "audioseq_cmd.h"
#include "port/hooks/Events.h"

// Pending override request — written by game thread, read by audio thread
// -1 = no request, -2 = clear request, >=0 = msgId to activate
static volatile s32 sPendingVoiceMsgId = -1;

// Audio-thread-only state
static bool sDirectVoiceActive = false;
static u32 sDirectVoiceMsgId = 0;
static u32 sDirectVoiceNumSamples = 0;
static u32 sDirectVoiceSampleRate = 0;
static u32 sDirectVoiceChannels = 0;
static Sample* sDirectVoiceData = nullptr;
static std::chrono::steady_clock::time_point sVoiceStartTime;
static bool sLoggedNoteCreated = false;
static s32 sMouthState = 0;
static s32 sMouthHoldFrames = 0;

static TunedSample* gVoiceOverrideTunedSample = nullptr;
static TunedSample* gVoiceOverrideCommSample = nullptr;
static float gVoiceOverrideFreqMod = 1.0f;
static s32 gVoiceOverrideArmed = 0;
static s32 gVoiceOverrideSilencing = 0;
static s32 gVoiceOverrideActiveNote = 0;
static s32 gVoiceOverrideNotesToSkip = 0;
static s32 gVoiceOverrideStarted = 0;

static Sample sDirectVoiceSample;
static AdpcmLoop sDirectVoiceLoop;
static TunedSample sDirectVoiceTunedSample;
static Instrument sDirectVoiceInstrument;
static EnvelopePoint sDirectVoiceEnvelope[3];

static s16 sSilentSampleData = 0;
static Sample sSilentSample;
static AdpcmLoop sSilentLoop;
static TunedSample sSilentTunedSample;
static bool sSilentSampleInitialized = false;

static void InitSilentSample() {
    if (sSilentSampleInitialized)
        return;
    sSilentLoop.start = 0;
    sSilentLoop.end = 1;
    sSilentLoop.count = 0;
    sSilentSample.codec = CODEC_S16;
    sSilentSample.medium = MEDIUM_RAM;
    sSilentSample.unk_bit26 = 0;
    sSilentSample.isRelocated = true;
    sSilentSample.size = 2;
    sSilentSample.sampleAddr = (u8*) &sSilentSampleData;
    sSilentSample.loop = &sSilentLoop;
    sSilentSample.book = nullptr;
    sSilentTunedSample.sample = &sSilentSample;
    sSilentTunedSample.tuning = 1.0f;
    sSilentSampleInitialized = true;
}

static SequenceChannel* Voice_GetChannel15() {
    if (!IS_SEQUENCE_CHANNEL_VALID(gSeqPlayers[SEQ_PLAYER_VOICE].channels[15])) {
        return nullptr;
    }
    return gSeqPlayers[SEQ_PLAYER_VOICE].channels[15];
}

static void SetupDirectVoiceInstrument(Sample* voiceData) {
    sDirectVoiceLoop.start = 0;
    sDirectVoiceLoop.end = voiceData->numFrames * voiceData->channels;
    sDirectVoiceLoop.count = 0;

    sDirectVoiceSample.codec = CODEC_S16;
    sDirectVoiceSample.medium = MEDIUM_RAM;
    sDirectVoiceSample.unk_bit26 = 0;
    sDirectVoiceSample.isRelocated = true;
    sDirectVoiceSample.size = voiceData->size;
    sDirectVoiceSample.sampleAddr = voiceData->sampleAddr;
    sDirectVoiceSample.loop = &sDirectVoiceLoop;
    sDirectVoiceSample.book = nullptr;

    sDirectVoiceTunedSample.sample = &sDirectVoiceSample;
    sDirectVoiceTunedSample.tuning = 1.0f;

    sDirectVoiceEnvelope[0] = { 1, 32000 };
    sDirectVoiceEnvelope[1] = { -2, 32000 };
    sDirectVoiceEnvelope[2] = { -1, 0 };

    sDirectVoiceInstrument.isRelocated = true;
    sDirectVoiceInstrument.normalRangeLo = 0;
    sDirectVoiceInstrument.normalRangeHi = 127;
    sDirectVoiceInstrument.adsrDecayIndex = 0;
    sDirectVoiceInstrument.envelope = sDirectVoiceEnvelope;
    sDirectVoiceInstrument.lowPitchTunedSample = sDirectVoiceTunedSample;
    sDirectVoiceInstrument.normalPitchTunedSample = sDirectVoiceTunedSample;
    sDirectVoiceInstrument.highPitchTunedSample = sDirectVoiceTunedSample;

    SPDLOG_INFO("[VoiceHook] Setup: loop [{}, {}), size={}, codec=S16", sDirectVoiceLoop.start, sDirectVoiceLoop.end,
                voiceData->size);
    SPDLOG_INFO("[VoiceHook] Expected duration: {:.3f}s ({} samples / {} rate / {}ch)",
                (float) voiceData->numFrames / (float) voiceData->sampleRate, voiceData->numFrames,
                voiceData->sampleRate, voiceData->channels);
    SPDLOG_INFO("[VoiceHook] freqMod={:.4f} ({}Hz * {}ch / 32000)", gVoiceOverrideFreqMod, voiceData->sampleRate,
                voiceData->channels);
}

static void VoiceOverride_Finish() {
    SPDLOG_INFO("[VoiceHook] VoiceOverride_Finish called (was active={}, msgId={})", sDirectVoiceActive,
                sDirectVoiceMsgId);
    InitSilentSample();
    if (sDirectVoiceActive) {
        gVoiceOverrideSilencing = 1;
    }
    gVoiceOverrideArmed = 0;
    gVoiceOverrideStarted = 0;
    gVoiceOverrideActiveNote = 0;
    gVoiceOverrideNotesToSkip = 0;
    gVoiceOverrideTunedSample = &sSilentTunedSample;
    gVoiceOverrideFreqMod = 1.0f;
    sDirectVoiceActive = false;
    sDirectVoiceData = nullptr;
    sLoggedNoteCreated = false;
    sMouthState = 0;
    sMouthHoldFrames = 0;
}

// Called from GAME THREAD — only write sPendingVoiceMsgId
static void OnPlayVoice(IEvent* ev) {
    auto* event = reinterpret_cast<PlayVoiceEvent*>(ev);

    const std::string path = StringHelper::Sprintf("ast_radio/gMsg_ID_%04d", (u32) event->msgId);
    Sample* sample = LoadChild<Sample*>(path.c_str());

    SPDLOG_INFO("[VoiceHook] PlayVoice msgId={}, hasOverride={}, active={}, pending={}, activeMsg={}", event->msgId,
                sample != nullptr, sDirectVoiceActive, (s32) sPendingVoiceMsgId,
                sDirectVoiceMsgId);

    if (sample == nullptr) {
        // No override — signal audio thread to clear if needed
        if (sDirectVoiceActive || sPendingVoiceMsgId >= 0 || gVoiceOverrideSilencing) {
            sPendingVoiceMsgId = -2;
        }
        return;
    }

    // Don't re-request if already active for the same message
    if (sDirectVoiceActive && sDirectVoiceMsgId == (u32) event->msgId) {
        SPDLOG_INFO("[VoiceHook] PlayVoice msgId={} — already active, skipping", event->msgId);
        return;
    }

    sPendingVoiceMsgId = event->msgId;
    SPDLOG_INFO("[VoiceHook] PlayVoice msgId={} — set pending", event->msgId);
}

// Called from AUDIO THREAD — all state mutations happen here
static void OnUpdateVoice(IEvent* ev) {
    auto* event = reinterpret_cast<UpdateVoiceEvent*>(ev);

    // Process pending request from game thread
    s32 pending = sPendingVoiceMsgId;
    if (pending >= 0) {
        sPendingVoiceMsgId = -1;
        SPDLOG_INFO("[VoiceHook] Processing pending msgId={}", pending);

        // Unfreeze channel for new message
        {
            SequenceChannel* ch = Voice_GetChannel15();
            if (ch != nullptr) {
                SPDLOG_INFO("[VoiceHook] Before unfreeze: stopScript={}, delay={}, layerNote={}", (int) ch->stopScript,
                            (ch->layers[0] != nullptr ? (int) ch->layers[0]->delay : -1),
                            (ch->layers[0] != nullptr && ch->layers[0]->note != nullptr ? 1 : 0));
                ch->stopScript = false;
                if (ch->layers[0] != nullptr) {
                    ch->layers[0]->delay = 1;
                }
            } else {
                SPDLOG_INFO("[VoiceHook] Channel15 is NULL during unfreeze!");
            }
        }
        if (sDirectVoiceActive) {
            VoiceOverride_Finish();
        }

        // Load and activate override
        const std::string path = StringHelper::Sprintf("ast_radio/gMsg_ID_%04d", pending);
        Sample* sample = LoadChild<Sample*>(path.c_str());

        if (sample != nullptr) {
            sDirectVoiceMsgId = (u32) pending;
            sDirectVoiceNumSamples = sample->numFrames;
            sDirectVoiceSampleRate = sample->sampleRate;
            sDirectVoiceChannels = sample->channels;
            sDirectVoiceData = sample;
            SetupDirectVoiceInstrument(sample);

            gVoiceOverrideFreqMod = (float) (sample->sampleRate * sample->channels) / 32000.0f;
            gVoiceOverrideTunedSample = &sDirectVoiceTunedSample;
            gVoiceOverrideArmed = 1;
            gVoiceOverrideCommSample = nullptr;
            gVoiceOverrideSilencing = 0;
            gVoiceOverrideNotesToSkip = (pending >= 2000) ? 1 : 0;
            gVoiceOverrideStarted = 0;
            sDirectVoiceActive = true;
            sVoiceStartTime = std::chrono::steady_clock::now();

            SequenceChannel* ch = Voice_GetChannel15();
            SequenceLayer* layer = (ch != nullptr && ch->layers[0] != nullptr) ? ch->layers[0] : nullptr;
            SPDLOG_INFO("[VoiceHook] Activated msgId={}, ch={}, stopScript={}, delay={}, layer={}, note={}", pending,
                        (void*) ch, (ch ? (int) ch->stopScript : -1), (layer ? (int) layer->delay : -1), (void*) layer,
                        (layer && layer->note ? (void*) layer->note : nullptr));
        }
    } else if (pending == -2) {
        sPendingVoiceMsgId = -1;
        gVoiceOverrideSilencing = 0;
        gVoiceOverrideTunedSample = nullptr;
        gVoiceOverrideCommSample = nullptr;
        if (sDirectVoiceActive) {
            SequenceChannel* ch = Voice_GetChannel15();
            if (ch != nullptr) {
                ch->stopScript = false;
                if (ch->layers[0] != nullptr) {
                    ch->layers[0]->delay = 1;
                }
            }
            VoiceOverride_Finish();
            SPDLOG_INFO("[VoiceHook] Cleared override (no override for new message)");
        }
        return;
    }

    if (!sDirectVoiceActive) {
        return;
    }

    SequenceChannel* ch = Voice_GetChannel15();
    if (ch == nullptr) {
        SPDLOG_INFO("[VoiceHook] UpdateVoice: channel15 is null, finishing");
        VoiceOverride_Finish();
        *event->finished = true;
        return;
    }

    // Safety net: if gVoiceOverrideStarted never set within 2x expected duration, force finish
    auto elapsed = std::chrono::steady_clock::now() - sVoiceStartTime;
    float elapsedSec = std::chrono::duration<float>(elapsed).count();
    float expectedDuration =
        sDirectVoiceSampleRate > 0 ? (float) sDirectVoiceNumSamples / (float) sDirectVoiceSampleRate : 0.0f;

    if (gVoiceOverrideStarted == 0) {
        if (expectedDuration > 0 && elapsedSec > expectedDuration * 2.0f) {
            SPDLOG_INFO("[VoiceHook] Safety net: override never started for msgId={} ({:.3f}s > {:.3f}s)",
                        sDirectVoiceMsgId, elapsedSec, expectedDuration * 2.0f);
            ch->seqScriptIO[1] = 0;
            ch->stopScript = false;
            SequenceLayer* layer = ch->layers[0];
            if (layer != nullptr) {
                layer->delay = 1;
            }
            VoiceOverride_Finish();
            *event->finished = true;
        }
        return;
    }

    // Only check noteFinished/timer after gVoiceOverrideStarted == 1
    SequenceLayer* layer = ch->layers[0];

    bool noteFinished = false;
    if (layer != nullptr && layer->note != nullptr) {
        noteFinished = (layer->note->noteSubEu.bitField0.finished != 0);
        if (!sLoggedNoteCreated) {
            sVoiceStartTime = std::chrono::steady_clock::now();
            SPDLOG_INFO("[VoiceHook] Note detected for msgId={}, noteFinished={}, delay={}, elapsed={:.3f}s",
                        sDirectVoiceMsgId, (int) noteFinished, (int) layer->delay, elapsedSec);
            sLoggedNoteCreated = true;
        }
    } else if (elapsedSec > 0.5f && !sLoggedNoteCreated) {
        sLoggedNoteCreated = true;
        SPDLOG_INFO("[VoiceHook] WARNING: No note for msgId={} after {:.3f}s, layer={}, delay={}", sDirectVoiceMsgId,
                    elapsedSec, (layer ? "exists" : "NULL"), (layer ? (int) layer->delay : -1));
    }

    if (!noteFinished && expectedDuration > 0 && elapsedSec > expectedDuration * 1.5f) {
        SPDLOG_INFO("[VoiceHook] Timer backup finish for msgId={} ({:.3f}s > {:.3f}s)", sDirectVoiceMsgId, elapsedSec,
                    expectedDuration);
        noteFinished = true;
    }

    if (noteFinished) {
        SPDLOG_INFO("[VoiceHook] Finish msgId={}, stopScript={}, delay={}", sDirectVoiceMsgId, (int) ch->stopScript,
                    (layer ? (int) layer->delay : -1));
        ch->seqScriptIO[1] = 0;
        ch->stopScript = false;
        if (layer != nullptr) {
            layer->delay = 1;
        }
        VoiceOverride_Finish();
        *event->finished = true;
    }
}

static void OnGetCurrentVoice(IEvent* ev) {
    auto* event = reinterpret_cast<GetCurrentVoiceEvent*>(ev);
    if (sDirectVoiceActive) {
        *event->result = (s32) sDirectVoiceMsgId;
    }
}

static void OnGetVoiceStatus(IEvent* ev) {
    auto* event = reinterpret_cast<GetVoiceStatusEvent*>(ev);
    if (!sDirectVoiceActive || sDirectVoiceData == nullptr || gVoiceOverrideStarted == 0) {
        return;
    }

    // Compute elapsed playback position
    auto elapsed = std::chrono::steady_clock::now() - sVoiceStartTime;
    float elapsedSec = std::chrono::duration<float>(elapsed).count();
    u32 sampleIndex = (u32) (elapsedSec * (float) sDirectVoiceSampleRate) * sDirectVoiceChannels;

    // Compute RMS amplitude in a window around current position
    const u32 WINDOW = 256;
    const s16* pcm = (const s16*) sDirectVoiceData->sampleAddr;
    u32 totalSamples = sDirectVoiceData->numFrames * sDirectVoiceData->channels;

    if (sampleIndex >= totalSamples || pcm == nullptr) {
        *event->result = 0;
        sMouthState = 0;
        return;
    }

    u32 windowStart = (sampleIndex >= WINDOW / 2) ? sampleIndex - WINDOW / 2 : 0;
    u32 windowEnd = windowStart + WINDOW;
    if (windowEnd > totalSamples)
        windowEnd = totalSamples;

    double sumSq = 0.0;
    u32 count = windowEnd - windowStart;
    for (u32 i = windowStart; i < windowEnd; i++) {
        double s = (double) pcm[i];
        sumSq += s * s;
    }
    double rms = (count > 0) ? sqrt(sumSq / (double) count) : 0.0;

    // Threshold: ~5% of max 16-bit value
    const double THRESHOLD = 1600.0;
    s32 desired = (rms > THRESHOLD) ? 1 : 0;

    // Hysteresis: hold mouth state for at least 3 frames to prevent flicker
    if (desired != sMouthState) {
        sMouthHoldFrames++;
        if (sMouthHoldFrames >= 3) {
            sMouthState = desired;
            sMouthHoldFrames = 0;
        }
    } else {
        sMouthHoldFrames = 0;
    }

    *event->result = sMouthState;
}

static void OnClearVoice(IEvent* ev) {
    if (sDirectVoiceActive) {
        SequenceChannel* ch = Voice_GetChannel15();
        if (ch != nullptr) {
            ch->stopScript = false;
            if (ch->layers[0] != nullptr) {
                ch->layers[0]->delay = 1;
            }
        }
    }
    VoiceOverride_Finish();
    gVoiceOverrideSilencing = 0;
    gVoiceOverrideCommSample = nullptr;
    gVoiceOverrideTunedSample = nullptr;
    gVoiceOverrideNotesToSkip = 0;
    gVoiceOverrideStarted = 0;
    sDirectVoiceMsgId = 0;
    sPendingVoiceMsgId = -1;
}

static void OnPreNote(IEvent* ev) {
    gVoiceOverrideActiveNote = 0;

    auto* event = reinterpret_cast<SeqLayerPreNoteEvent*>(ev);
    auto* layer = event->layer;
    auto* channel = event->channel;

    if ((gVoiceOverrideArmed || gVoiceOverrideSilencing) &&
        layer->channel == gSeqPlayers[SEQ_PLAYER_VOICE].channels[15] && channel->seqScriptIO[1] == 1) {
        if (gVoiceOverrideNotesToSkip > 0) {
            gVoiceOverrideNotesToSkip--;
            gVoiceOverrideCommSample = layer->tunedSample;
            return;
        }
        layer->portamento.mode = 0;
        layer->portamento.extent = 0.0f;
        if (gVoiceOverrideArmed) {
            gVoiceOverrideActiveNote = 1;
            gVoiceOverrideStarted = 1;
        }
        layer->tunedSample = gVoiceOverrideTunedSample;
        layer->freqMod = gVoiceOverrideFreqMod;
        return;
    }

    if (gVoiceOverrideSilencing && layer->channel == gSeqPlayers[SEQ_PLAYER_VOICE].channels[15] &&
        layer->tunedSample != gVoiceOverrideCommSample) {
        layer->tunedSample = gVoiceOverrideTunedSample;
    }
}

static void OnPostNote(IEvent* ev) {
    if (!gVoiceOverrideActiveNote) {
        return;
    }

    auto* event = reinterpret_cast<SeqLayerPostNoteEvent*>(ev);
    event->layer->delay = 0x7FFF;
    event->layer->gateDelay = 0;
    event->layer->note->playbackState.portamento.mode = 0;
    event->layer->note->playbackState.portamento.extent = 0.0f;
}

extern "C" void VoiceHooks_Init() {
    REGISTER_LISTENER(PlayVoiceEvent, EVENT_PRIORITY_HIGH, OnPlayVoice);
    REGISTER_LISTENER(ClearVoiceEvent, EVENT_PRIORITY_HIGH, OnClearVoice);
    REGISTER_LISTENER(UpdateVoiceEvent, EVENT_PRIORITY_HIGH, OnUpdateVoice);
    REGISTER_LISTENER(GetVoiceStatusEvent, EVENT_PRIORITY_HIGH, OnGetVoiceStatus);
    REGISTER_LISTENER(GetCurrentVoiceEvent, EVENT_PRIORITY_HIGH, OnGetCurrentVoice);

    REGISTER_LISTENER(SeqLayerPreNoteEvent, EVENT_PRIORITY_HIGH, OnPreNote);
    REGISTER_LISTENER(SeqLayerPostNoteEvent, EVENT_PRIORITY_HIGH, OnPostNote);
}

static RegisterShipInitFunc initFunc(VoiceHooks_Init);