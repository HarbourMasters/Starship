/**
 * Used to reproduce recordings made from real N64 hardware
 * to accurately play cutscenes at the correct speed.
 * These recordings adjust gVisPerFrame during runtime to produce
 * the same behaviour as the original game.
 */
#ifndef N64_RECORD_H
#define N64_RECORD_H

#include "global.h"

typedef struct Record {
    u8 vis;
    u16 frame;
} Record;

extern_s Record gCarrierCutsceneRecord[13];
extern_s Record gWarpzoneCsRecord[19];
extern_s Record gA6GorgonCsRecord[12];
extern_s Record gSyRobotCutsceneRecord[3];
extern_s Record gAndrossRobotKillCutscene2[20];
extern_s Record gAndrossRobotKillCutscene1[25];
extern_s Record gMacbethCutsceneRecord[14];
extern_s Record gGrangaCutsceneRecord[13];
extern_s Record gMeCrusherCutsceneRecord[3];
extern_s Record gEndingCsRecord[37];
extern_s Record gSolarIntroCsRecord[16];

extern_s int gA6GorgonCsFrameCount;
extern_s int gWarpzoneCsFrameCount;

void UpdateVisPerFrameFromRecording(Record* record, s32 maxFrames, int* frameCounter);

#endif
