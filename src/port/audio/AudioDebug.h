#pragma once

// ── C-visible section ────────────────────────────────────────────────────────
// AudioDebug_SetLastPlayed is called from audio_synthesis.c (pure C).
// Takes void* to avoid conflicting with the C-side "Sample" typedef.
#ifdef __cplusplus
extern "C" {
#endif

// Called from audio_synthesis.c each time a non-synthetic note is processed.
// Captures a full snapshot of the sample + synthesis state for display.
void AudioDebug_SetLastPlayed(void* sample, int samplePosInt, unsigned int endPos,
                              int loopStart, int loopEnd, unsigned int loopCount,
                              unsigned short resampleRate, int codec, unsigned int sampleSize);

// Called from audio_seqplayer.c inside the channel processing loop.
// Returns 1 if the channel should be skipped (muted), 0 if it should run.
int AudioDebug_IsChannelMuted(int channelIndex);

#ifdef __cplusplus
}

// ── C++-only section ─────────────────────────────────────────────────────────
#include <atomic>
#include <cstdint>
#include <mutex>
#include <string>
#include <unordered_map>
#include "port/resource/type/audio/Sample.h"

namespace SF64 {

// Snapshot of one note's playback state, written by the audio thread.
struct AudioDebugSnapshot {
    SampleData*   sample      = nullptr;
    int           samplePos   = 0;       // samplePosInt at time of call
    uint32_t      endPos      = 0;       // loopInfo->end
    uint32_t      loopStart   = 0;       // loopInfo->start
    uint32_t      loopEnd     = 0;       // loopInfo->end (alias, same as endPos)
    uint32_t      loopCount   = 0;       // loopInfo->count  (0=no loop, 0xFFFFFFFF=infinite)
    uint16_t      resampleRate = 0;      // noteSub->resampleRate (fixed-point)
    int           codec       = 0;       // bookSample->codec
    uint32_t      sampleSize  = 0;       // bookSample->size (bytes)
};

// Per-channel mute flags — written by the render/UI thread, read by the audio thread.
// Index matches seqPlayer->channels[i].  16 channels per SEQ_NUM_CHANNELS.
static constexpr int kNumSeqChannels = 16;
extern std::atomic<bool> gMutedChannels[kNumSeqChannels];

// Populated at sample-factory load time.
extern std::unordered_map<SampleData*, std::string> gSamplePathMap;
extern std::mutex gSamplePathMapMutex;

// Written lock-free by the audio thread; read by the render thread.
// Access via AudioDebug_GetSnapshot() for a consistent copy.
extern std::atomic<bool>          gSnapshotReady;
extern AudioDebugSnapshot         gSnapshot;       // written by audio thread
extern std::mutex                 gSnapshotMutex;

void AudioDebug_RegisterSample(SampleData* sample, const std::string& path);
const std::string& AudioDebug_GetSamplePath(SampleData* sample);

// Returns a safe copy of the latest snapshot for the render thread.
AudioDebugSnapshot AudioDebug_GetSnapshot();

} // namespace SF64

#endif // __cplusplus
