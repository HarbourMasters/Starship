#include "sys.h"

u64 gDramStack[SP_DRAM_STACK_SIZE64];
u8 gOSYieldData[OS_YIELD_DATA_SIZE];
FrameBuffer gZBuffer; // z buffer
u8 gTaskOutputBuffer[0x30000];
u8 gAudioHeap[0xB0000];
u16 gFillBuffer[3 * SCREEN_WIDTH];
FrameBuffer gFrameBuffers[3];
