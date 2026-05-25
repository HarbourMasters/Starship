#pragma once

#include <cstdint>

#ifdef __cplusplus
extern "C" {
#endif

void Sequence_AddRemap(uint16_t from, uint16_t to);
void Sequence_RemoveRemap(uint16_t from);
uint16_t Sequence_GetCurrentSeqId(uint8_t seqPlayId);
bool Sequence_IsMapped(uint16_t seqId);

#ifdef __cplusplus
}
#endif
