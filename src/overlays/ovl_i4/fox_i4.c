#include "global.h"

void Fortuna_LevelComplete(Player*);
void Bolse_8018D394(Boss*);
void Bolse_8018D454(Boss*);
void Bolse_8018D7F0(Boss*);
void Bolse_8018D960(Boss*);
void Bolse_8018E710(Actor*);
void Bolse_8018E870(Actor*);
void Bolse_80191BAC(Actor*);
void Bolse_80191DB0(Actor*);

UNK_TYPE D_i4_801A03C0;
s32 D_i4_8019EDD0 = 0;

void OvlI4_CallFunction(u32 mode, void* ptr) {
    switch (mode) {
        case OVLCALL_FO_CS_COMPLETE:
            Fortuna_LevelComplete(ptr);
            break;
        case OVLCALL_BOSS309_UPDATE:
            Bolse_8018E710(ptr);
            break;
        case OVLCALL_BOSS309_DRAW:
            Bolse_8018E870(ptr);
            break;
        case OVLCALL_BOSS310_UPDATE:
            Bolse_80191BAC(ptr);
            break;
        case OVLCALL_BOSS310_DRAW:
            Bolse_80191DB0(ptr);
            break;
        case OVLCALL_ACTOR271_UPDATE:
            Bolse_8018D7F0(ptr);
            break;
        case OVLCALL_ACTOR271_DRAW:
            Bolse_8018D960(ptr);
            break;
        case OVLCALL_ACTOR272_UPDATE:
            Bolse_8018D394(ptr);
            break;
        case OVLCALL_ACTOR272_DRAW:
            Bolse_8018D454(ptr);
        default:
            PRINTF("i4 指定外！\n"); // Not specified!
            break;
    }
}
