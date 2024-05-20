#include "global.h"

// SDK states that 1 cycle takes about 21.33 nanoseconds
#if 1
#define SECONDS_PER_CYCLE 0.00000002133f
#else
// Use this macro if your N64 CPU is overclocked to 125 Mhz (x2 Multiplier)
#define SECONDS_PER_CYCLE 0.000000016f
#endif

#define FPS_COUNTER_X_POS 14
#define FPS_COUNTER_Y_POS 9

static OSTime gLastOSTime = 0;
static float gFrameTime = 0.0f;
static u16 gFrames = 0;
static u16 gFPS = 0;
static u8 gRenderFPS = false;

static void CalculateFrameTimeFromOSTime(OSTime diff) {
    gFrameTime += diff * SECONDS_PER_CYCLE;
    gFrames++;
}

static void Play_RenderFps(void) {
    // Toggle rendering framerate with the L button.
    if (gControllerPress[0].button & L_TRIG) {
        gRenderFPS ^= 1;
    }
    if (gRenderFPS) {
        OSTime newTime = osGetTime();
        CalculateFrameTimeFromOSTime(newTime - gLastOSTime);
        // If frame time is longer or equal to a second, update FPS counter.
        if (gFrameTime >= 1.0f) {
            gFPS = gFrames;
            gFrames = 0;
            gFrameTime -= 1.0f;
        }

        /* Draw */
        RCP_SetupDL(&gMasterDisp, SETUPDL_83);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);
        Graphics_DisplaySmallText(FPS_COUNTER_X_POS, FPS_COUNTER_Y_POS, 1.0f, 1.0f, "FPS:");
        Graphics_DisplaySmallNumber(FPS_COUNTER_X_POS + 35, FPS_COUNTER_Y_POS, gFPS);
        gLastOSTime = newTime;
    }
}
