#ifndef BUFFERS_H
#define BUFFERS_H

#include "gfx.h"

extern_s u64 gDramStack[];
extern_s u8 gOSYieldData[];
extern_s FrameBuffer gZBuffer; // z buffer
extern_s u8 gTaskOutputBuffer[];
extern_s u8 gAudioHeap[];
extern_s u16 gTextureRenderBuffer[];
extern_s u16 gFillBuffer[];
extern_s FrameBuffer gFrameBuffers[]; // 8038F800

#endif
