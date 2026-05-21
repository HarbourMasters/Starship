#include "AudioDebug.h"

namespace SF64 {

std::unordered_map<SampleData*, std::string> gSamplePathMap;
std::mutex                                   gSamplePathMapMutex;

AudioDebugSnapshot gSnapshot;
std::mutex         gSnapshotMutex;
std::atomic<bool>  gSnapshotReady{ false };

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
