#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void Sequence_AddRemap(u16 from, u16 to);
void Sequence_RemoveRemap(u16 from);
u16 Sequence_GetCurrentSeqId(u8 seqPlayId);
bool Sequence_IsMapped(u16 seqId);

#ifdef __cplusplus
}
#endif
