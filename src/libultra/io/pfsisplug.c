#include "macros.h"
#include "PR/os_internal.h"
#include "PR/controller.h"
#include "siint.h"

OSPifRam __osPfsPifRam ALIGNED(16);

s32 osPfsIsPlug(OSMesgQueue* mq, u8* pattern) {
    s32 ret = 0;
    OSMesg msg;
    u8 bitpattern;
    OSContStatus contData[MAXCONTROLLERS];
    s32 channel;
    u8 bits = 0;
    s32 crcErrorCount = 3;

    __osSiGetAccess();

    do {
        __osPfsRequestData(CONT_CMD_REQUEST_STATUS);

        ret = __osSiRawStartDma(OS_WRITE, &__osPfsPifRam);
        osRecvMesg(mq, &msg, OS_MESG_BLOCK);

        ret = __osSiRawStartDma(OS_READ, &__osPfsPifRam);
        osRecvMesg(mq, &msg, OS_MESG_BLOCK);

        __osPfsGetInitData(&bitpattern, &contData[0]);

        for (channel = 0; channel < __osMaxControllers; channel++) {
            if ((contData[channel].status & CONT_ADDR_CRC_ER) == 0) {
                crcErrorCount--;
                break;
            }
        }

        if (channel == __osMaxControllers) {
            crcErrorCount = 0;
        }
    } while (crcErrorCount > 0);

    for (channel = 0; channel < __osMaxControllers; channel++) {
        if ((contData[channel].errno == 0) && ((contData[channel].status & CONT_CARD_ON) != 0)) {
            bits |= (1 << channel);
        }
    }
    __osSiRelAccess();
    *pattern = bits;
    return ret;
}

void __osPfsRequestData(u8 cmd) {
    u8* ptr;
    __OSContRequesFormat requestformat;
    int i;

    __osContLastCmd = cmd;

#if BUILD_VERSION < VERSION_I
    for (i = 0; i < ARRLEN(__osPfsPifRam.raw); i++) {
        __osPfsPifRam.raw[i] = 0;
    }
    __osPfsPifRam.pifstatus = CONT_CMD_EXE;
#endif

    ptr = (u8*) &__osPfsPifRam;
    requestformat.dummy = CONT_CMD_NOP;
    requestformat.txsize = CONT_CMD_REQUEST_STATUS_TX;
    requestformat.rxsize = CONT_CMD_REQUEST_STATUS_RX;
    requestformat.cmd = cmd;
    requestformat.typeh = CONT_CMD_NOP;
    requestformat.typel = CONT_CMD_NOP;
    requestformat.status = CONT_CMD_NOP;
    requestformat.dummy1 = CONT_CMD_NOP;

    for (i = 0; i < __osMaxControllers; i++) {
        *((__OSContRequesFormat*) ptr) = requestformat;
        ptr += sizeof(__OSContRequesFormat);
    }

    *ptr = CONT_CMD_END;
}

void __osPfsGetInitData(u8* pattern, OSContStatus* data) {
    u8* ptr;
    __OSContRequesFormat requestformat;
    int i;
    u8 bits = 0;

    ptr = (u8*) &__osPfsPifRam;

    for (i = 0; i < __osMaxControllers; i++, ptr += sizeof(requestformat), data++) {
        requestformat = *((__OSContRequesFormat*) ptr);
        data->errno = CHNL_ERR(requestformat);

        if (data->errno != 0) {
            continue;
        }

        data->type = ((requestformat.typel << 8) | requestformat.typeh);
        data->status = requestformat.status;
        bits |= (1 << i);
    }
    *pattern = bits;
}
