#include "sys.h"

s32 Lib_vsPrintf(char* dst, const char* fmt, va_list args) {
    return vsprintf(dst, fmt, args);
}

void Lib_vTable(s32 index, void (**table)(s32, s32), s32 arg0, s32 arg1) {
    void (*func)(s32, s32) = table[index];

    func(arg0, arg1);
}

void Lib_SwapBuffers(u8* buf1, u8* buf2, s32 len) {
    s32 i;
    u8 temp;

    for (i = 0; i < len; i++) {
        temp = buf2[i];
        buf2[i] = buf1[i];
        buf1[i] = temp;
    }
}

void Lib_QuickSort(u8* first, u32 length, u32 size, CompareFunc cFunc) {
    u32 splitIdx;
    u8* last;
    u8* right;
    u8* left;

    while (true) {
        last = first + (length - 1) * size;

        if (length == 2) {
            if (cFunc(first, last) > 0) {
                Lib_SwapBuffers(first, last, size);
            }
            return;
        }
        if (size && size && size) {} //! FAKE: must be here with at least 3 && operands.
        left = first;
        right = last - size;

        while (true) {
            while (cFunc(left, last) < 0) {
                left += size;
            }
            while ((cFunc(right, last) >= 0) && (left < right)) {
                right -= size;
            }
            if (left >= right) {
                break;
            }
            Lib_SwapBuffers(left, right, size);
            left += size;
            right -= size;
        }
        Lib_SwapBuffers(last, left, size);
        splitIdx = (left - first) / size;
        if (length / 2 < splitIdx) {
            if ((length - splitIdx) > 2) {
                Lib_QuickSort(left + size, length - splitIdx - 1, size, cFunc);
            }

            if (splitIdx < 2) {
                return;
            }
            left = first;
            length = splitIdx;
        } else {
            if (splitIdx >= 2) {
                Lib_QuickSort(first, splitIdx, size, cFunc);
            }

            if ((length - splitIdx) <= 2) {
                return;
            }

            first = left + size;
            length -= splitIdx + 1;
        }
    }
}

void Lib_InitPerspective(Gfx** dList) {
    u16 norm;

    guPerspective(gGfxMtx, &norm, gFovY, (f32) SCREEN_WIDTH / SCREEN_HEIGHT, gProjectNear, gProjectFar, 1.0f);
    gSPPerspNormalize((*dList)++, norm);
    gSPMatrix((*dList)++, gGfxMtx++, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    guLookAt(gGfxMtx, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -12800.0f, 0.0f, 1.0f, 0.0f);
    gSPMatrix((*dList)++, gGfxMtx++, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
    Matrix_Copy(gGfxMatrix, &gIdentityMatrix);
}

void Lib_InitOrtho(Gfx** dList) {
    guOrtho(gGfxMtx, -SCREEN_WIDTH / 2, SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 2, gProjectNear,
            gProjectFar, 1.0f);
    gSPMatrix((*dList)++, gGfxMtx++, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    guLookAt(gGfxMtx, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -12800.0f, 0.0f, 1.0f, 0.0f);
    gSPMatrix((*dList)++, gGfxMtx++, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
    Matrix_Copy(gGfxMatrix, &gIdentityMatrix);
}

void Lib_DmaRead(void* src, void* dst, s32 size) {
    osInvalICache(dst, size);
    osInvalDCache(dst, size);
    while (size > 0x100) {
        osPiStartDma(&gDmaIOMsg, 0, 0, (uintptr_t) src, dst, 0x100, &gDmaMesgQueue);
        size -= 0x100;
        src = (void*) ((uintptr_t) src + 0x100);
        dst = (void*) ((uintptr_t) dst + 0x100);
        MQ_WAIT_FOR_MESG(&gDmaMesgQueue, NULL);
    }
    if (size != 0) {
        osPiStartDma(&gDmaIOMsg, 0, 0, (uintptr_t) src, dst, size, &gDmaMesgQueue);
        MQ_WAIT_FOR_MESG(&gDmaMesgQueue, NULL);
    }
}

void Lib_FillScreen(u8 setFill) {
    s32 i;

    // TODO: Implement fill screen
    gFillScreenColor |= 1;
    if (setFill == true) {
        if (gFillScreen == false) {
            if (gFillScreenColor == 1) {
                // osViBlack(1);
            } else {
                for (i = 0; i < 3 * SCREEN_WIDTH; i++) {
                    gFillBuffer[i] = gFillScreenColor;
                }
                // osWritebackDCacheAll();
                // osViSwapBuffer(&gFillBuffer[SCREEN_WIDTH]);
                // osViRepeatLine(1);
            }
            gFillScreen = true;
        }
    } else if (gFillScreen == true) {
        // osViRepeatLine(0);
        // osViBlack(0);
        gFillScreen = false;
    }
}
