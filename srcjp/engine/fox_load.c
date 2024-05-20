#include "sf64dma.h"

u8 sFillTimer = 3;

#include "fox_load_inits.c"

Scene sCurrentScene = {
    NO_OVERLAY,
    { /* 0x1 */ NO_SEGMENT,
      /* 0x2 */ NO_SEGMENT,
      /* 0x3 */ NO_SEGMENT,
      /* 0x4 */ NO_SEGMENT,
      /* 0x5 */ NO_SEGMENT,
      /* 0x6 */ NO_SEGMENT,
      /* 0x7 */ NO_SEGMENT,
      /* 0x8 */ NO_SEGMENT,
      /* 0x9 */ NO_SEGMENT,
      /* 0xA */ NO_SEGMENT,
      /* 0xB */ NO_SEGMENT,
      /* 0xC */ NO_SEGMENT,
      /* 0xD */ NO_SEGMENT,
      /* 0xE */ NO_SEGMENT,
      /* 0xF */ NO_SEGMENT },
};

#pragma GLOBAL_ASM("asm/jp/rev0/nonmatchings/engine/fox_load/func_800559D0.s")

#pragma GLOBAL_ASM("asm/jp/rev0/nonmatchings/engine/fox_load/func_80055A98.s")

#pragma GLOBAL_ASM("asm/jp/rev0/nonmatchings/engine/fox_load/func_80055D64.s")

#pragma GLOBAL_ASM("asm/jp/rev0/nonmatchings/engine/fox_load/func_800562E8.s")

#pragma GLOBAL_ASM("asm/jp/rev0/nonmatchings/engine/fox_load/D_800DBF90.s")
