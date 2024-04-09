#include "global.h"

void func_800A3CA0(void) {
    Matrix_Push(&gGfxMatrix);
    Matrix_LookAt(gGfxMatrix, gCsCamEyeX, gCsCamEyeY, gCsCamEyeZ, gCsCamAtX, gCsCamAtY, gCsCamAtZ, 0.0f, 1.0f, 0.0f, 1);
    Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -200.0f, 1);
    Matrix_RotateY(gGfxMatrix, gControllerPress[gPlayerNum].stick_x * M_DTOR, 1);
    Matrix_RotateX(gGfxMatrix, gControllerPress[gPlayerNum].stick_y * M_DTOR, 1);
    Matrix_SetGfxMtx(&gMasterDisp);
    RCP_SetupDL_23();
    Matrix_Pop(&gGfxMatrix);
}

void func_800A3E00(void) {
    switch (D_ctx_80177868) {
        case 0:
            if (gNextGameStateTimer == 0) {
                D_ctx_80177868 = 1;
            }
            break;
        case 1:
            D_ctx_80177868 = 2;
            gDrawMode = DRAW_UNK_7;
            gCsCamAtY = 0.0f;
            gCsCamAtX = gCsCamAtY;
            gCsCamEyeZ = gCsCamAtX;
            gCsCamEyeY = gCsCamEyeZ;
            gCsCamEyeX = gCsCamEyeY;
            gCsCamAtZ = -10.0f;
            break;
        case 2:
            if ((gControllerPress[0].button & START_BUTTON) || (gControllerPress[1].button & START_BUTTON)) {
                func_8001D638(0);
                D_ctx_80177868 = 3;
                gDrawMode = DRAW_NONE;
                Play_Setup();
                gNextGameStateTimer = 0;
            }
            break;
        case 3:
            if (gNextGameStateTimer == 0) {
                gPlayState = PLAY_UPDATE;
            }
            break;
    }
}
