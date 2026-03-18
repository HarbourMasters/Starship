#include "global.h"
#include "fox_record.h"

void UpdateVisPerFrameFromRecording(Record* record, s32 maxFrames, int* frameCounter) {
    int i;

    if (*frameCounter > record[maxFrames - 1].frame) {
        return;
    }

    for (i = 0; i < maxFrames; i++) {
        if (*frameCounter == record[i].frame) {
            gVIsPerFrame = record[i].vis;
        }
    }
}

int gWarpzoneCsFrameCount = 0;
int gA6GorgonCsFrameCount = 0;

// clang-format off

Record gWarpzoneCsRecord[19] = {
    { 2, 1 },  { 3, 3 },  { 4, 4 },   { 3, 8 },   { 2, 9 },   { 3, 52 },  { 2, 54 },  { 3, 69 },  { 2, 70 },  { 3, 75 },
    { 2, 76 }, { 3, 79 }, { 2, 117 }, { 3, 118 }, { 2, 120 }, { 3, 145 }, { 2, 215 }, { 3, 216 }, { 2, 230 },
};

Record gA6GorgonCsRecord[12] = {
    { 3, 0 },  { 4, 3 },  { 5, 6 },  { 4, 37 }, { 5, 38 }, { 4, 44 },
    { 3, 53 }, { 4, 54 }, { 3, 57 }, { 4, 58 }, { 3, 59 }, { 2, 170 },
};

Record gEndingCsRecord[37] = {
    { 2, 0 },    { 5, 1 },    { 2, 2 },    { 3, 277 },  { 2, 278 },  { 3, 340 },  { 2, 397 },  { 3, 537 },
    { 2, 538 },  { 3, 548 },  { 2, 549 },  { 3, 568 },  { 2, 569 },  { 3, 620 },  { 2, 623 },  { 3, 803 },
    { 2, 806 },  { 3, 814 },  { 2, 823 },  { 3, 1282 }, { 2, 1284 }, { 5, 3703 }, { 2, 3704 }, { 4, 3904 },
    { 2, 3905 }, { 3, 4782 }, { 2, 4783 }, { 3, 4785 }, { 2, 4820 }, { 3, 4986 }, { 2, 6779 }, { 5, 6780 },
    { 2, 6781 }, { 3, 6785 }, { 4, 6786 }, { 3, 6793 }, { 2, 6799 },
};

// MeCrusher destroy cutscene timings recorded from a real N64
Record gMeCrusherCutsceneRecord[3] = {
    { 2, 0 },
    { 3, 200 },
    { 2, 224 },
};

// Carrier destroy cutscene timings recorded from a real N64
Record gCarrierCutsceneRecord[13] = {
    { 2, 0 },
    { 3, 2 },
    { 4, 16 },
    { 3, 50 },
    { 4, 58 },
    { 5, 67 },
    { 4, 68 },
    { 5, 71 },
    { 4, 73 },
    { 5, 74 },
    { 4, 106 },
    { 3, 146 },
    { 2, 194 },
};

// Granga destroy cutscene timings recorded from a real N64
Record gGrangaCutsceneRecord[13] = {
    { 2, 0 },
    { 3, 1 },
    { 2, 5 },
    { 3, 7 },
    { 2, 52 },
    { 3, 78 },
    { 4, 103 },
    { 3, 125 },
    { 2, 153 },
    { 3, 155 },
    { 2, 157 },
    { 3, 158 },
    { 2, 160 },
};

// Train cutscene timings recorded from a real N64
Record gMacbethCutsceneRecord[14] = {
    // Train breaking barriers
    { 2, 0 },
    { 3, 2 },
    { 2, 31 },
    { 3, 400 },
    { 2, 418 },
    { 3, 433 },
    { 4, 435 },
    { 3, 444 },
    { 2, 509 },
    // { 3, 559 },
    // { 2, 581 },
    // { 3, 587 },
    // Explosions
    { 2, 589 },
    { 3, 714 },
    { 4, 821 },
    { 5, 849 },
    { 2, 942 },
};

// After defeating Andross
Record gAndrossRobotKillCutscene1[25] = {
    { 3, 0 },
    { 2, 8 },
    { 3, 19 },
    { 2, 35 },
    { 3, 156 },
    { 2, 166 },
    { 3, 193 },
    { 4, 198 },
    { 3, 199 },
    { 4, 201 },
    { 3, 205 },
    { 4, 207 },
    { 3, 215 },
    { 4, 234 },
    // { 3, 236 },
    { 4, 237 },
    { 3, 239 },
    { 4, 244 },
    // { 3, 245 },
    { 4, 246 },
    // { 3, 272 },
    { 4, 274 },
    // { 3, 290 },
    { 4, 292 },
    // { 3, 295 }, // too much?
    { 4, 301 },
    // { 3, 302 },
    { 4, 304 },
    // { 3, 305 },
    { 4, 307 },
    // { 3, 332 },
    { 4, 334 },
    // { 3, 335 },
    { 2, 339 },
};

Record gAndrossRobotKillCutscene2[20] = {
    { 4, 0 },
    { 2, 1 },
    { 5, 2 },
    { 2, 3 },
    { 3, 42 },
    { 2, 43 },
    { 3, 57 },
    { 2, 58 },
    { 3, 63 },
    { 2, 69 },
    { 3, 158 },
    { 4, 161 },
    { 5, 163 },
    { 4, 182 },
    { 3, 185 },
    { 4, 189 },
    { 5, 193 },
    { 4, 205 },
    { 3, 207 },
    { 2, 211 },
};

// SyRobot destroy cutscene timings recorded from a real N64
Record gSyRobotCutsceneRecord[3] = {
    { 2, 0 },
    { 3, 129 },
    { 2, 230 },
};

Record gSolarIntroCsRecord[16] = {
    { 2, 0   },
    { 3, 94  },
    { 2, 105 },
    { 3, 362 },
    { 4, 377 },
    { 3, 379 },
    { 4, 381 },
    { 2, 382 },
    { 3, 443 },
    { 2, 444 },
    { 3, 456 },
    { 2, 492 },
    { 3, 494 },
    { 2, 499 },
    { 3, 552 },
    { 2, 629 },
};

// clang-format on
