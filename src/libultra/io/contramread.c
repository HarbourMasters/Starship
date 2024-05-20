#include "PR/os_internal.h"
#include "PR/rcp.h"
#include "PR/controller.h"
#include "siint.h"

#define READFORMAT(ptr) ((__OSContRamReadFormat*) (ptr))

#if BUILD_VERSION >= VERSION_J
s32 __osPfsLastChannel = -1;

s32 __osContRamRead(OSMesgQueue* mq, int channel, u16 address, u8* buffer) {
    s32 ret = 0;
    s32 i;
    u8* ptr;
    s32 retry = 2;

    __osSiGetAccess();

    do {
        ptr = (u8*) &__osPfsPifRam;

        if (__osContLastCmd != CONT_CMD_READ_PAK || (u32) __osPfsLastChannel != channel) {
            __osContLastCmd = CONT_CMD_READ_PAK;
            __osPfsLastChannel = channel;

            for (i = 0; i < channel; i++) {
                *ptr++ = CONT_CMD_REQUEST_STATUS;
            }

            __osPfsPifRam.pifstatus = CONT_CMD_EXE;

            READFORMAT(ptr)->dummy = CONT_CMD_NOP;
            READFORMAT(ptr)->txsize = CONT_CMD_READ_PAK_TX;
            READFORMAT(ptr)->rxsize = CONT_CMD_READ_PAK_RX;
            READFORMAT(ptr)->cmd = CONT_CMD_READ_PAK;
            READFORMAT(ptr)->datacrc = 0xFF;

            ptr[sizeof(__OSContRamReadFormat)] = CONT_CMD_END;
        } else {
            ptr += channel;
        }

#if BUILD_VERSION >= VERSION_J
        READFORMAT(ptr)->addrh = address >> 3;
        READFORMAT(ptr)->addrl = (u8) ((address << 5) | __osContAddressCrc(address));
#else
        READFORMAT(ptr)->address = (address << 0x5) | __osContAddressCrc(address);
#endif

        ret = __osSiRawStartDma(OS_WRITE, &__osPfsPifRam);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);

        ret = __osSiRawStartDma(OS_READ, &__osPfsPifRam);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);

        ret = CHNL_ERR(*READFORMAT(ptr));

        if (!ret) {
            if (__osContDataCrc(READFORMAT(ptr)->data) != READFORMAT(ptr)->datacrc) {
                ret = __osPfsGetStatus(mq, channel);

                if (ret) {
                    break;
                } else {
                    ret = PFS_ERR_CONTRFAIL;
                }
            } else {
                bcopy(READFORMAT(ptr)->data, buffer, BLOCKSIZE);
            }
        } else {
            ret = PFS_ERR_NOPACK;
        }
    } while ((ret == PFS_ERR_CONTRFAIL) && (retry-- >= 0));
    __osSiRelAccess();
    return ret;
}
#else

static void __osPackRamReadData(int channel, u16 address);

s32 __osContRamRead(OSMesgQueue* mq, int channel, u16 address, u8* buffer) {
    s32 ret = 0;
    int i;
    u8* ptr = (u8*) &__osPfsPifRam;
    __OSContRamReadFormat ramreadformat;
    int retry = 2;

    __osSiGetAccess();
    __osContLastCmd = CONT_CMD_READ_PAK;
    __osPackRamReadData(channel, address);
    ret = __osSiRawStartDma(OS_WRITE, &__osPfsPifRam);
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);

    do {
        ret = __osSiRawStartDma(OS_READ, &__osPfsPifRam);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);
        ptr = (u8*) &__osPfsPifRam;

        if (channel != 0) {
            for (i = 0; i < channel; i++) {
                ptr++;
            }
        }

        ramreadformat = *READFORMAT(ptr);

        ret = CHNL_ERR(ramreadformat);
        if (ret == 0) {
            u8 c = __osContDataCrc((u8*) &ramreadformat.data);
            if (c != ramreadformat.datacrc) {
                ret = __osPfsGetStatus(mq, channel);

                if (ret != 0) {
                    __osSiRelAccess();
                    return ret;
                }

                ret = PFS_ERR_CONTRFAIL;
            } else {
                for (i = 0; i < ARRLEN(ramreadformat.data); i++) {
                    *buffer++ = ramreadformat.data[i];
                }
            }
        } else {
            ret = PFS_ERR_NOPACK;
        }
    } while ((ret == PFS_ERR_CONTRFAIL) && retry-- >= 0);

    __osSiRelAccess();

    return ret;
}

static void __osPackRamReadData(int channel, u16 address) {
    u8* ptr;
    __OSContRamReadFormat ramreadformat;
    int i;

    ptr = (u8*) __osPfsPifRam.ramarray;

#if BUILD_VERSION < VERSION_I
    for (i = 0; i < ARRLEN(__osPfsPifRam.raw); i++) {
        __osPfsPifRam.raw[i] = 0;
    }
#endif

    __osPfsPifRam.pifstatus = CONT_CMD_EXE;
    ramreadformat.dummy = CONT_CMD_NOP;
    ramreadformat.txsize = CONT_CMD_READ_PAK_TX;
    ramreadformat.rxsize = CONT_CMD_READ_PAK_RX;
    ramreadformat.cmd = CONT_CMD_READ_PAK;
    ramreadformat.address = (address << 0x5) | __osContAddressCrc(address);
    ramreadformat.datacrc = CONT_CMD_NOP;

    for (i = 0; i < ARRLEN(ramreadformat.data); i++) {
        ramreadformat.data[i] = CONT_CMD_NOP;
    }

    if (channel != 0) {
        for (i = 0; i < channel; i++) {
            *ptr++ = CONT_CMD_REQUEST_STATUS;
        }
    }

    *(__OSContRamReadFormat*) ptr = ramreadformat;
    ptr += sizeof(__OSContRamReadFormat);
    ptr[0] = CONT_CMD_END;
}

#endif
