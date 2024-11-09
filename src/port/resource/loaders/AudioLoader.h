#pragma once

#include <stdint.h>
#include "sf64audio_provisional.h"

#ifdef __cplusplus
extern "C" {
#endif

char* Audio_LoadBlob(const char* resource, u32 offset);
AdpcmBook* Audio_LoadBook(uintptr_t addr);
AdpcmLoop* Audio_LoadLoop(uintptr_t addr);
Instrument* Audio_LoadInstrument(uint32_t addr, AudioTableEntry entry, uint32_t sampleBankID);
Drum* Audio_LoadDrum(uint32_t addr, AudioTableEntry entry, uint32_t sampleBankID);
Sample* Audio_LoadSample(uint32_t addr, AudioTableEntry entry, uint32_t sampleBankID);
SoundFont* Audio_LoadFont(AudioTableEntry entry);

#ifdef __cplusplus
}
#endif