#include "global.h"

/*
 * File: fox_blur.c
 * System: Blur
 * Description: Some unused blurring code.
 */

void func_blur_800846F0(FrameBuffer* arg0) {
    s32 i;
    s32 j;
    u16* var_v0;
    s32 sp60[5];
    s32 sp4C[5];
    s32 sp38[5];

    for (i = 0; i < gSysFrameCount % SCREEN_HEIGHT; i++) {
        var_v0 = SCREEN_WIDTH * i + arg0->data;
        for (j = 0; j < gSysFrameCount % SCREEN_WIDTH; j++, var_v0++) {
            sp60[1] = RGBA16_RED(var_v0[0]);
            sp4C[1] = RGBA16_GRN(var_v0[0]);
            sp38[1] = RGBA16_BLU(var_v0[0]);

            sp60[2] = RGBA16_RED(var_v0[1]);
            sp4C[2] = RGBA16_GRN(var_v0[1]);
            sp38[2] = RGBA16_BLU(var_v0[1]);

            sp60[3] = RGBA16_RED(var_v0[SCREEN_WIDTH]);
            sp4C[3] = RGBA16_GRN(var_v0[SCREEN_WIDTH]);
            sp38[3] = RGBA16_BLU(var_v0[SCREEN_WIDTH]);

            sp60[4] = RGBA16_RED(var_v0[SCREEN_WIDTH + 1]);
            sp4C[4] = RGBA16_GRN(var_v0[SCREEN_WIDTH + 1]);
            sp38[4] = RGBA16_BLU(var_v0[SCREEN_WIDTH + 1]);

            sp60[0] = (sp60[1] + sp60[2] + sp60[3] + sp60[4]) / 4;
            sp4C[0] = (sp4C[1] + sp4C[2] + sp4C[3] + sp4C[4]) / 4;
            sp38[0] = (sp38[1] + sp38[2] + sp38[3] + sp38[4]) / 4;

            var_v0[0] = (sp60[0] << 11) | (sp4C[0] << 6) | (sp38[0] << 1);
        }
    }
    osWritebackDCacheAll();
}
