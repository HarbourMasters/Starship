#include "global.h"
#include "mods.h"

u16* Message_PtrFromId(u16 msgId) {
    s32 i;
    MsgLookup* lookup = (MsgLookup*) LOAD_ASSET(gMsgLookup);

    while (lookup->msgId != -1) {
        if (lookup->msgId == msgId) {
            return lookup->msgPtr;
        }
        lookup++;
    }
    return NULL;
}

u16 Message_IdFromPtr(u16* msgPtr) {
    s32 i;
    MsgLookup* lookup = (MsgLookup*) LOAD_ASSET(gMsgLookup);

    while (lookup->msgPtr != NULL) {
        if (lookup->msgPtr == msgPtr) {
            return lookup->msgId;
        }
        lookup++;
    }
    return -1;
}

s32 Message_GetWidth(u16* msgPtr) {
    s32 width = 0;
    u16* msgChar = LOAD_ASSET(msgPtr);

    while (*msgChar != MSGCHAR_END) {
        if ((*msgChar >= MSGCHAR_CLF) || (*msgChar == MSGCHAR_SPC)) {
            width++;
        }
        msgChar++;
    }
    return width;
}

s32 Message_GetCharCount(u16* msgPtr) {
    s32 count = 0;
    u16* msgChar = LOAD_ASSET(msgPtr);

    if (CVarGetInteger("gLevelSelector", 0) && gCurrentPlanet == 6) {
        return 0;
    }

    while (*msgChar != MSGCHAR_END) {
        count++;
        msgChar++;
    }
    return count;
}

void Message_DisplayChar(Gfx** gfxPtr, u16 msgChar, s32 xpos, s32 ypos) {
    gDPLoadTextureBlock_4b((*gfxPtr)++, gTextCharTextures[msgChar >> 2], G_IM_FMT_CI, 16, 13, msgChar % 4U,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                           G_TX_NOLOD);
    gSPTextureRectangle((*gfxPtr)++, xpos << 2, ypos << 2, (xpos + 13) << 2, (ypos + 13) << 2, G_TX_RENDERTILE, 64, 0,
                        1024, 1024);
}

bool Message_DisplayText(Gfx** gfxPtr, u16* msgPtr, s32 xPos, s32 yPos, s32 len) {
    s32 xChar = xPos;
    s32 yChar = yPos;
    s32 i;
    bool print;

    msgPtr = LOAD_ASSET(msgPtr);
    gDPSetPrimColor((*gfxPtr)++, 0x00, 0x00, 255, 255, 255, 255);
    gDPSetTextureLUT((*gfxPtr)++, G_TT_RGBA16);
    gDPLoadTLUT((*gfxPtr)++, 64, 256, gTextCharPalettes);

#ifdef AVOID_UB
    print = false;
#endif
    // bug: if the for loop is skipped, print is never initialized
    for (i = 0; msgPtr[i] != MSGCHAR_END && i < len; i++) {
        print = false;
        switch (msgPtr[i]) {
            case MSGCHAR_NWL:
                xChar = xPos;
                yChar += 13;
                break;
            case MSGCHAR_CLF:
            case MSGCHAR_CUP:
            case MSGCHAR_CRT:
            case MSGCHAR_CDN:
                gDPSetPrimColor((*gfxPtr)++, 0x00, 0x00, 255, 255, 0, 255);
                Message_DisplayChar(gfxPtr, msgPtr[i], xChar, yChar);
                xChar += 14;
                print = true;
                gDPSetPrimColor((*gfxPtr)++, 0x00, 0x00, 255, 255, 255, 255);
                break;
            case MSGCHAR_SPC:
            default:
                Message_DisplayChar(gfxPtr, msgPtr[i], xChar, yChar);
                xChar += 7;
                print = true;
                break;
            case MSGCHAR_NP2:
            case MSGCHAR_NP3:
            case MSGCHAR_NP4:
            case MSGCHAR_NP5:
            case MSGCHAR_NP6:
            case MSGCHAR_NP7:
            case MSGCHAR_PRI0:
            case MSGCHAR_PRI1:
            case MSGCHAR_PRI2:
            case MSGCHAR_PRI3:
            case MSGCHAR_QSP:
            case MSGCHAR_HSP:
            case MSGCHAR_NXT:
                break;
        }
    }
    return print;
}

void Message_DisplayScrollingText(Gfx** gfxPtr, u16* msgPtr, s32 xPos, s32 yPos, s32 yRangeHi, s32 yRangeLo, s32 len) {
    s32 x = xPos;
    s32 y = yPos;
    s32 i;
    msgPtr = LOAD_ASSET(msgPtr);

    gDPSetTextureLUT((*gfxPtr)++, G_TT_RGBA16);
    gDPLoadTLUT((*gfxPtr)++, 64, 256, gTextCharPalettes);

    for (i = 0; msgPtr[i] != 0 && i < len; i++) {
        switch (msgPtr[i]) {
            case MSGCHAR_NWL:
                x = xPos;
                y += 15;
                break;

            case MSGCHAR_QSP:
                x += 2;
                break;

            case MSGCHAR_HSP:
                x += 3;
                break;

            case MSGCHAR_SPC:
                x += 7;
                break;

            default:
                if ((yRangeLo < y) && (y < yRangeHi)) {
                    Message_DisplayChar(gfxPtr, msgPtr[i], x, y);
                }
                x += 7;
                break;

            case MSGCHAR_NP2:
            case MSGCHAR_NP3:
            case MSGCHAR_NP4:
            case MSGCHAR_NP5:
            case MSGCHAR_NP6:
            case MSGCHAR_NP7:
            case MSGCHAR_PRI0:
            case MSGCHAR_PRI1:
            case MSGCHAR_PRI2:
            case MSGCHAR_PRI3:
            case MSGCHAR_NXT:
                break;
        }
    }
}

bool Message_IsPrintingChar(u16* msgPtr, s32 charPos) {
    s32 i;
    bool print;
    msgPtr = LOAD_ASSET(msgPtr);

#ifdef AVOID_UB
    print = false;
#endif
    // bug: if the for loop is skipped, print is never initialized
    for (i = 0; msgPtr[i] != 0 && i < charPos; i++) {
        print = false;
        switch (msgPtr[i]) {
            case MSGCHAR_NWL:
            case MSGCHAR_NP2:
            case MSGCHAR_NP3:
            case MSGCHAR_NP4:
            case MSGCHAR_NP5:
            case MSGCHAR_NP6:
            case MSGCHAR_NP7:
            case MSGCHAR_PRI0:
            case MSGCHAR_PRI1:
            case MSGCHAR_PRI2:
            case MSGCHAR_PRI3:
            case MSGCHAR_SPC:
            case MSGCHAR_QSP:
            case MSGCHAR_HSP:
            case MSGCHAR_NXT:
                break;
            default:
                print = true;
                break;
        }
    }
    return print;
}
