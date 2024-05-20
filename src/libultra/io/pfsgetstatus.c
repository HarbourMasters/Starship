#include "PR/os_internal.h"
#include "PR/controller.h"
#include "siint.h"

s32 __osPfsGetStatus(OSMesgQueue* queue, int channel) {
    s32 ret = 0;
    OSMesg dummy;
    u8 pattern;
    OSContStatus status[4];

    __osPfsRequestData(CONT_CMD_REQUEST_STATUS);
    ret = __osSiRawStartDma(OS_WRITE, &__osPfsPifRam);
    osRecvMesg(queue, &dummy, OS_MESG_BLOCK);
    ret = __osSiRawStartDma(OS_READ, &__osPfsPifRam);
    osRecvMesg(queue, &dummy, OS_MESG_BLOCK);
    __osPfsGetInitData(&pattern, status);

    if (status[channel].status & CONT_CARD_ON && status[channel].status & CONT_CARD_PULL) {
        return 2;
    }
    if (status[channel].errno || !(status[channel].status & CONT_CARD_ON)) {
        return 1;
    }
    if (status[channel].status & CONT_ADDR_CRC_ER) {
        return 4;
    }
    return ret;
}
