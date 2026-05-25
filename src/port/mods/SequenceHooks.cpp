#include <mutex>
#include <unordered_map>

#include <ship/events/EventSystem.h>

#include "port/ShipInit.h"
#include "port/mods/SequenceHooks.h"

#include "port/hooks/Events.h"

#include "sf64audio_provisional.h"
#include "audioseq_cmd.h"
#include "bgm.h"

static std::mutex sRemapMtx;
static std::unordered_map<uint16_t, uint16_t> sSeqRemap;
static uint16_t sCurrentSeqId[SEQ_PLAYER_MAX];

static uint16_t ApplyRemap(uint16_t seqId) {
    std::lock_guard<std::mutex> lock(sRemapMtx);
    auto it = sSeqRemap.find(seqId);
    return (it != sSeqRemap.end()) ? it->second : seqId;
}

static void OnPlaySequence(IEvent* ev) {
    auto* event = reinterpret_cast<PlaySequenceEvent*>(ev);
    *event->seqId = ApplyRemap(*event->seqId);
    if (event->seqPlayId < SEQ_PLAYER_MAX) {
        sCurrentSeqId[event->seqPlayId] = *event->seqId;
    }
}

static void OnPlayFanfare(IEvent* ev) {
    auto* event = reinterpret_cast<PlayFanfareEvent*>(ev);
    *event->seqId = ApplyRemap(*event->seqId);
    sCurrentSeqId[SEQ_PLAYER_FANFARE] = *event->seqId;
}

static void OnStopSequence(IEvent* ev) {
    auto* event = reinterpret_cast<StopSequenceEvent*>(ev);
    if (event->seqPlayId < SEQ_PLAYER_MAX) {
        sCurrentSeqId[event->seqPlayId] = SEQ_ID_NONE;
    }
}

void Sequence_AddRemap(uint16_t from, uint16_t to) {
    std::lock_guard<std::mutex> lock(sRemapMtx);
    sSeqRemap[from] = to;
}

void Sequence_RemoveRemap(uint16_t from) {
    std::lock_guard<std::mutex> lock(sRemapMtx);
    sSeqRemap.erase(from);
}

uint16_t Sequence_GetCurrentSeqId(uint8_t seqPlayId) {
    if (seqPlayId >= SEQ_PLAYER_MAX) {
        return SEQ_ID_NONE;
    }
    return sCurrentSeqId[seqPlayId];
}

bool Sequence_IsMapped(uint16_t seqId) {
    std::lock_guard<std::mutex> lock(sRemapMtx);
    return sSeqRemap.find(seqId) != sSeqRemap.end();
}

extern "C" void SequenceHooks_Init() {
    for (int i = 0; i < SEQ_PLAYER_MAX; i++) {
        sCurrentSeqId[i] = SEQ_ID_NONE;
    }
    REGISTER_LISTENER(PlaySequenceEvent, EVENT_PRIORITY_HIGH, OnPlaySequence);
    REGISTER_LISTENER(PlayFanfareEvent, EVENT_PRIORITY_HIGH, OnPlayFanfare);
    REGISTER_LISTENER(StopSequenceEvent, EVENT_PRIORITY_NORMAL, OnStopSequence);
}

static RegisterShipInitFunc sInitFunc(SequenceHooks_Init);
