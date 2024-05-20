#ifndef SF64_MESG
#define SF64_MESG

#include <libultraship.h>
#include "stdbool.h"

typedef struct {
    s32 msgId;
    u16* msgPtr;
} MsgLookup;

u16* Message_PtrFromId(u16 msgId);
u16 Message_IdFromPtr(u16*);
s32 Message_GetWidth(u16* msgPtr);
s32 Message_GetCharCount(u16* msgPtr);
void Message_DisplayChar(Gfx** gfxPtr, u16 msgChar, s32 xpos, s32 ypos);
bool Message_DisplayText(Gfx** gfxPtr, u16* msgPtr, s32 xPos, s32 yPos, s32 len);
void Message_DisplayScrollingText(Gfx** gfxPtr, u16* msgPtr, s32 xPos, s32 yPos, s32 yRangeHi, s32 yRangeLo, s32 len);
bool Message_IsPrintingChar(u16* msgPtr, s32 charPos);

 // Id + 1 gives the other frame of the animation
typedef enum RadioCharacterId {
    RCID_FOX = 0,
    RCID_STATIC = 2,
    RCID_FOX_RED = 5,
    RCID_FALCO = 10,
    RCID_FALCO_RED = 15,
    RCID_SLIPPY = 20,
    RCID_SLIPPY_RED = 25,
    RCID_PEPPY = 30,
    RCID_PEPPY_RED = 35,
    RCID_KATT = 40,
    RCID_ANDROSS = 50,
    RCID_ANDROSS_RED = 55,
    RCID_JAMES = 60,
    RCID_GEN_PEPPER = 70,
    RCID_BOSS_CORNERIA = 80,
    RCID_ROB64 = 90,
    RCID_ROB64_RED = 95,
    RCID_BOSS_METEO = 100,
    RCID_BOSS_CORNERIA2 = 110,
    RCID_BOSS_AREA6 = 120,
    RCID_BOSS_ZONESS = 130,
    RCID_ROB64_2 = 140,
    RCID_BOSS_SECTORX = 150,
    RCID_BOSS_SECTORY = 160,
    RCID_BILL = 170,
    RCID_CAIMAN_AREA6 = 180,
    RCID_BOSS_MACBETH = 190,
    RCID_WOLF = 200,
    RCID_PIGMA = 210,
    RCID_LEON = 220,
    RCID_ANDREW = 230,
    RCID_WOLF_2 = 240,
    RCID_PIGMA_2 = 250,
    RCID_LEON_2 = 260,
    RCID_ANDREW_2 = 270,
    RCID_ROB64_TITLE = 300,
    RCID_GEN_PEPPER_TITLE = 310,
    RCID_TR = 350,
    RCID_FOX_EXPERT = 400,
    RCID_1000 = 1000,
} RadioCharacterId;

void Radio_PlayMessage(u16*, RadioCharacterId);
void func_radio_800BB388(void);
void Radio_Draw(void);

typedef enum MsgCharCode {
    // Non-printing and whitespace
    /*  0 */ MSGCHAR_END,   // End message
    /*  1 */ MSGCHAR_NWL,   // New line
    /*  2 */ MSGCHAR_NP2,   // No effect
    /*  3 */ MSGCHAR_NP3,   // No effect
    /*  4 */ MSGCHAR_NP4,   // No effect
    /*  5 */ MSGCHAR_NP5,   // No effect
    /*  6 */ MSGCHAR_NP6,   // No effect
    /*  7 */ MSGCHAR_NP7,   // No effect
    /*  8 */ MSGCHAR_PRI0,  // Set message priority
    /*  9 */ MSGCHAR_PRI1,  // Set message priority
    /* 10 */ MSGCHAR_PRI2,  // Set message priority
    /* 11 */ MSGCHAR_PRI3,  // Set message priority
    /* 12 */ MSGCHAR_SPC,   // Space
    /* 13 */ MSGCHAR_QSP,   // Quarter space
    /* 14 */ MSGCHAR_HSP,   // Half Space
    /* 15 */ MSGCHAR_NXT,   // Next text box

    // printing characters
    /* 16 */ MSGCHAR_CLF,   // C-Left
    /* 17 */ MSGCHAR_CUP,   // C-Up
    /* 18 */ MSGCHAR_CRT,   // C-Right
    /* 19 */ MSGCHAR_CDN,   // C-Down
    /* 20 */ MSGCHAR_AUP,   // Up arrow
    /* 21 */ MSGCHAR_ALF,   // Left arrow
    /* 22 */ MSGCHAR_ADN,   // Down arrow
    /* 23 */ MSGCHAR_ART,   // Right arrow
    /* 24 */ MSGCHAR_A,     // A
    /* 25 */ MSGCHAR_B,     // B
    /* 26 */ MSGCHAR_C,     // C
    /* 27 */ MSGCHAR_D,     // D
    /* 28 */ MSGCHAR_E,     // E
    /* 29 */ MSGCHAR_F,     // F
    /* 30 */ MSGCHAR_G,     // G
    /* 31 */ MSGCHAR_H,     // H
    /* 32 */ MSGCHAR_I,     // I
    /* 33 */ MSGCHAR_J,     // J
    /* 34 */ MSGCHAR_K,     // K
    /* 35 */ MSGCHAR_L,     // L
    /* 36 */ MSGCHAR_M,     // M
    /* 37 */ MSGCHAR_N,     // N
    /* 38 */ MSGCHAR_O,     // O
    /* 39 */ MSGCHAR_P,     // P
    /* 40 */ MSGCHAR_Q,     // Q
    /* 41 */ MSGCHAR_R,     // R
    /* 42 */ MSGCHAR_S,     // S
    /* 43 */ MSGCHAR_T,     // T
    /* 44 */ MSGCHAR_U,     // U
    /* 45 */ MSGCHAR_V,     // V
    /* 46 */ MSGCHAR_W,     // W
    /* 47 */ MSGCHAR_X,     // X
    /* 48 */ MSGCHAR_Y,     // Y
    /* 49 */ MSGCHAR_Z,     // Z
    /* 50 */ MSGCHAR_a,     // a
    /* 51 */ MSGCHAR_b,     // b
    /* 52 */ MSGCHAR_c,     // c
    /* 53 */ MSGCHAR_d,     // d
    /* 54 */ MSGCHAR_e,     // e
    /* 55 */ MSGCHAR_f,     // f
    /* 56 */ MSGCHAR_g,     // g
    /* 57 */ MSGCHAR_h,     // h
    /* 58 */ MSGCHAR_i,     // i
    /* 59 */ MSGCHAR_j,     // j
    /* 60 */ MSGCHAR_k,     // k
    /* 61 */ MSGCHAR_l,     // l
    /* 62 */ MSGCHAR_m,     // m
    /* 63 */ MSGCHAR_n,     // n
    /* 64 */ MSGCHAR_o,     // o
    /* 65 */ MSGCHAR_p,     // p
    /* 66 */ MSGCHAR_q,     // q
    /* 67 */ MSGCHAR_r,     // r
    /* 68 */ MSGCHAR_s,     // s
    /* 69 */ MSGCHAR_t,     // t
    /* 70 */ MSGCHAR_u,     // u
    /* 71 */ MSGCHAR_v,     // v
    /* 72 */ MSGCHAR_w,     // w
    /* 73 */ MSGCHAR_x,     // x
    /* 74 */ MSGCHAR_y,     // y
    /* 75 */ MSGCHAR_z,     // z
    /* 76 */ MSGCHAR_EXM,   // !
    /* 77 */ MSGCHAR_QST,   // ?
    /* 78 */ MSGCHAR_DSH,   // -
    /* 79 */ MSGCHAR_CMA,   // ,
    /* 80 */ MSGCHAR_PRD,   // .
    /* 81 */ MSGCHAR_0,     // 0
    /* 82 */ MSGCHAR_1,     // 1
    /* 83 */ MSGCHAR_2,     // 2
    /* 84 */ MSGCHAR_3,     // 3
    /* 85 */ MSGCHAR_4,     // 4
    /* 86 */ MSGCHAR_5,     // 5
    /* 87 */ MSGCHAR_6,     // 6
    /* 88 */ MSGCHAR_7,     // 7
    /* 89 */ MSGCHAR_8,     // 8
    /* 90 */ MSGCHAR_9,     // 9
    /* 91 */ MSGCHAR_APS,   // '
    /* 92 */ MSGCHAR_LPR,   // (
    /* 93 */ MSGCHAR_RPR,   // )
    /* 94 */ MSGCHAR_CLN,   // :
    /* 95 */ MSGCHAR_PIP,   // |
} MsgCharCode;

#endif
