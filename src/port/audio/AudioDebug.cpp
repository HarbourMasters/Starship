#include "AudioDebug.h"

namespace SF64 {

std::unordered_map<SampleData*, std::string> gSamplePathMap;
std::mutex                                   gSamplePathMapMutex;

AudioDebugSnapshot gSnapshot;
std::mutex         gSnapshotMutex;
std::atomic<bool>  gSnapshotReady{ false };

// All channels unmuted by default.
std::atomic<bool> gMutedChannels[kNumSeqChannels] = {};

// Frame-step controls — all inactive by default.
std::atomic<bool>      gAudioStepMode{ false };
std::atomic<bool>      gAudioStepOnce{ false };
std::atomic<int>       gAudioStepN{ 0 };
std::atomic<uint64_t>  gAudioFrameCount{ 0 };

// Capture / record controls.
std::atomic<bool>     gAudioRecording{ false };
std::atomic<bool>     gAudioRecordPaused{ false };
std::atomic<bool>     gAudioSaveAndStop{ false };
std::atomic<uint64_t> gAudioRecordBytes{ 0 };
std::string           gAudioRecordPath;
std::mutex            gAudioRecordMutex;

void AudioDebug_RegisterSample(SampleData* sample, const std::string& path) {
    if (sample == nullptr) return;
    std::lock_guard<std::mutex> lk(gSamplePathMapMutex);
    gSamplePathMap[sample] = path;
}

const std::string& AudioDebug_GetSamplePath(SampleData* sample) {
    static const std::string sEmpty;
    if (sample == nullptr) return sEmpty;
    std::lock_guard<std::mutex> lk(gSamplePathMapMutex);
    auto it = gSamplePathMap.find(sample);
    return (it != gSamplePathMap.end()) ? it->second : sEmpty;
}

AudioDebugSnapshot AudioDebug_GetSnapshot() {
    std::lock_guard<std::mutex> lk(gSnapshotMutex);
    return gSnapshot;
}

} // namespace SF64

extern "C" void AudioDebug_SetLastPlayed(void* sample, int samplePosInt, unsigned int endPos,
                                         int loopStart, int loopEnd, unsigned int loopCount,
                                         unsigned short resampleRate, int codec,
                                         unsigned int sampleSize) {
    SF64::AudioDebugSnapshot snap;
    snap.sample       = reinterpret_cast<SF64::SampleData*>(sample);
    snap.samplePos    = samplePosInt;
    snap.endPos       = endPos;
    snap.loopStart    = loopStart;
    snap.loopEnd      = loopEnd;
    snap.loopCount    = loopCount;
    snap.resampleRate = resampleRate;
    snap.codec        = codec;
    snap.sampleSize   = sampleSize;

    {
        std::lock_guard<std::mutex> lk(SF64::gSnapshotMutex);
        SF64::gSnapshot = snap;
    }
    SF64::gSnapshotReady.store(true, std::memory_order_release);
}

extern "C" int AudioDebug_IsChannelMuted(int channelIndex) {
    if (channelIndex < 0 || channelIndex >= SF64::kNumSeqChannels) return 0;
    return SF64::gMutedChannels[channelIndex].load(std::memory_order_relaxed) ? 1 : 0;
}
