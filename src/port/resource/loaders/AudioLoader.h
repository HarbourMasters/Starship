#pragma once

#include <stdint.h>
#include "sf64audio_provisional.h"

#define OTR_AUDIO 1

#ifdef __cplusplus
extern "C" {
#endif

#ifdef OTR_AUDIO
SoundFont* Audio_LoadFont(AudioTableEntry entry, uint32_t fontId);
#else
char* Audio_LoadBlob(const char* resource, u32 offset);
AdpcmBook* Audio_LoadBook(uint32_t addr);
AdpcmLoop* Audio_LoadLoop(uint32_t addr);
Instrument* Audio_LoadInstrument(uint32_t addr, AudioTableEntry entry, uint32_t sampleBankID);
Drum* Audio_LoadDrum(uint32_t addr, AudioTableEntry entry, uint32_t sampleBankID);
Sample* Audio_LoadSample(uint32_t addr, AudioTableEntry entry, uint32_t sampleBankID);
SoundFont* Audio_LoadFont(AudioTableEntry entry, uint32_t fontId);
#endif
#ifdef __cplusplus
}
#endif