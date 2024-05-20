#include "global.h"

void Wipe_Horizontal(s32 frame) {
    Graphics_FillRectangle(&gMasterDisp, 0, 0, frame, SCREEN_HEIGHT, 0, 0, 0, 255);
    Graphics_FillRectangle(&gMasterDisp, SCREEN_WIDTH - frame, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 0, 255);
}

void Wipe_Vertical(s32 frame) {
    Graphics_FillRectangle(&gMasterDisp, 0, 0, SCREEN_WIDTH, frame, 0, 0, 0, 255);
    Graphics_FillRectangle(&gMasterDisp, 0, SCREEN_HEIGHT - frame, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 0, 255);
}

void Wipe_Circular(s32 frame) {
    s32 var_s1;

    RCP_SetupDL_12();
    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -150.0f, MTXF_NEW);
    for (var_s1 = 0; var_s1 < MIN(360, frame * 15); var_s1 += 15) {
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 0, 0, 0, MIN((frame - (var_s1 / 15)) * 15, 255));
        Matrix_Push(&gGfxMatrix);
        Matrix_RotateZ(gGfxMatrix, var_s1 * M_DTOR, MTXF_APPLY);
        Matrix_Scale(gGfxMatrix, 0.53f, 1.0f, 1.0f, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, D_Gfx_800D9688);
        Matrix_Pop(&gGfxMatrix);
    }
    Matrix_Pop(&gGfxMatrix);
}

void Wipe_Draw(WipeMode mode, s32 frame) {
    if (frame != 0) {
        switch (mode) {
            case WIPE_CIRCULAR:
                Wipe_Circular(frame);
                break;
            case WIPE_HORIZONTAL:
                Wipe_Horizontal(frame);
                break;
            case WIPE_VERTICAL:
                Wipe_Vertical(frame);
                break;
            default:
                (void) "そのような フェード は ない (%d)\n"; // There is no such fade
                break;
        }
    }
}
