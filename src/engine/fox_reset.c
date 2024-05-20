#include "global.h"

void Graphics_NMIWipe(void) {
    static s16 sWipeBarLength = 0;
    s32 i;

    gViewport->vp.vscale[0] = SCREEN_WIDTH * 2;
    gViewport->vp.vscale[1] = SCREEN_HEIGHT * 2;
    gViewport->vp.vscale[2] = G_MAXZ / 2;
    gViewport->vp.vscale[3] = 0;
    gViewport->vp.vtrans[0] = SCREEN_WIDTH * 2;
    gViewport->vp.vtrans[1] = SCREEN_HEIGHT * 2;
    gViewport->vp.vtrans[2] = G_MAXZ / 2;
    gViewport->vp.vtrans[3] = 0;
    gSPViewport(gMasterDisp++, gViewport);
    gDPPipeSync(gMasterDisp++);
    gDPSetScissor(gMasterDisp++, G_SC_NON_INTERLACE, SCREEN_MARGIN, SCREEN_MARGIN, SCREEN_WIDTH - SCREEN_MARGIN,
                  SCREEN_HEIGHT - SCREEN_MARGIN);

    Graphics_FillRectangle(&gMasterDisp, SCREEN_MARGIN, SCREEN_MARGIN,
                           MIN(SCREEN_WIDTH - 2 * SCREEN_MARGIN, sWipeBarLength) + SCREEN_MARGIN,
                           SCREEN_HEIGHT / 4 + SCREEN_MARGIN / 2, 0, 0, 0, 255);
    Graphics_FillRectangle(
        &gMasterDisp, SCREEN_WIDTH - SCREEN_MARGIN - MIN(SCREEN_WIDTH - 2 * SCREEN_MARGIN, sWipeBarLength),
        SCREEN_HEIGHT / 4 + SCREEN_MARGIN / 2, SCREEN_WIDTH - SCREEN_MARGIN, SCREEN_HEIGHT / 2, 0, 0, 0, 255);
    Graphics_FillRectangle(&gMasterDisp, SCREEN_MARGIN, SCREEN_HEIGHT / 2,
                           MIN(SCREEN_WIDTH - 2 * SCREEN_MARGIN, sWipeBarLength) + SCREEN_MARGIN,
                           3 * SCREEN_HEIGHT / 4 - SCREEN_MARGIN / 2, 0, 0, 0, 255);
    Graphics_FillRectangle(&gMasterDisp,
                           SCREEN_WIDTH - SCREEN_MARGIN - MIN(SCREEN_WIDTH - 2 * SCREEN_MARGIN, sWipeBarLength),
                           3 * SCREEN_HEIGHT / 4 - SCREEN_MARGIN / 2, SCREEN_WIDTH - SCREEN_MARGIN,
                           SCREEN_HEIGHT - SCREEN_MARGIN, 0, 0, 0, 255);
    if (sWipeBarLength == 0) {
        AudioThread_PreNMIReset();
    }
    sWipeBarLength += SCREEN_WIDTH / 7;
    if (sWipeBarLength >= SCREEN_WIDTH * 85 / 8 / 7) { // Why 85 / 8 == 3400 / 320 == 10.625? Has to do with NMI timing?
        osViBlack(true);
        gStopTasks = true;
    }
    for (i = 0; i < MAXCONTROLLERS; i++) {
        gControllerRumbleEnabled[i] = 0;
        gControllerRumbleFlags[i] = 0;
    }
}
