#include "macros.h"
#include "PR/rcp.h"
#include "PR/controller.h"
#include "siint.h"

OSPifRam __osEepPifRam ALIGNED(16);
#if BUILD_VERSION >= VERSION_L
s32 __osEepromRead16K;
#endif
void __osPackEepReadData(u8 address);

s32 osEepromRead(OSMesgQueue* mq, u8 address, u8* buffer) {
    s32 ret = 0;
    int i = 0;
    u8* ptr = (u8*) &__osEepPifRam;
    OSContStatus sdata;
    __OSContEepromFormat eepromformat;

    if (address > 0x40) {
        return -1;
    }
    __osSiGetAccess();
    ret = __osEepStatus(mq, &sdata);
    if (ret != 0 || sdata.type != 0x8000) {
        return 8;
    }
    while (sdata.status & 0x80) {
        __osEepStatus(mq, &sdata);
    }
    __osPackEepReadData(address);
    ret = __osSiRawStartDma(OS_WRITE, &__osEepPifRam);
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);
    for (i = 0; i < ARRLEN(__osEepPifRam.raw); i++) {
        __osEepPifRam.raw[i] = CONT_CMD_NOP;
    }
    __osEepPifRam.pifstatus = 0;
    ret = __osSiRawStartDma(OS_READ, &__osEepPifRam);
    __osContLastCmd = 4;
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);
    for (i = 0; i < 4; i++) {
        ptr++;
    }
    eepromformat = *(__OSContEepromFormat*) ptr;
    ret = CHNL_ERR(eepromformat);

    if (ret == 0) {
        for (i = 0; i < 8; i++) {
            *buffer++ = eepromformat.data[i];
        }
    }
    __osSiRelAccess();
    return ret;
}

void __osPackEepReadData(u8 address) {
    u8* ptr = (u8*) __osEepPifRam.ramarray;
    __OSContEepromFormat eepromformat;
    int i;

#if BUILD_VERSION < VERSION_J
    for (i = 0; i < ARRLEN(__osEepPifRam.raw); i++) {
        __osEepPifRam.raw[i] = CONT_CMD_NOP;
    }
#endif

    __osEepPifRam.pifstatus = CONT_CMD_EXE;

    eepromformat.txsize = CONT_CMD_READ_EEPROM_TX;
    eepromformat.rxsize = CONT_CMD_READ_EEPROM_RX;
    eepromformat.cmd = CONT_CMD_READ_EEPROM;
    eepromformat.address = address;

#if BUILD_VERSION < VERSION_J
    for (i = 0; i < ARRLEN(eepromformat.data); i++) {
        eepromformat.data[i] = 0;
    }
#endif

    for (i = 0; i < MAXCONTROLLERS; i++) {
        *ptr++ = 0;
    }

    *(__OSContEepromFormat*) (ptr) = eepromformat;
    ptr += sizeof(__OSContEepromFormat);
    ptr[0] = CONT_CMD_END;
}
