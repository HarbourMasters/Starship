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

extern Record gCarrierCutsceneRecord[13];
extern Record gWarpzoneCsRecord[19];
extern Record gA6GorgonCsRecord[12];
extern Record gSyRobotCutsceneRecord[3];
extern Record gAndrossRobotKillCutscene2[20];
extern Record gAndrossRobotKillCutscene1[25];
extern Record gMacbethCutsceneRecord[14];
extern Record gGrangaCutsceneRecord[13];
extern Record gMeCrusherCutsceneRecord[3];
extern Record gEndingCsRecord[37];
extern Record gSolarIntroCsRecord[16];

extern int gA6GorgonCsFrameCount;
extern int gWarpzoneCsFrameCount;

void UpdateVisPerFrameFromRecording(Record* record, s32 maxFrames, int* frameCounter);

#endif
