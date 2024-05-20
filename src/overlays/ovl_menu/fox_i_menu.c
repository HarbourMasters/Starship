#include "global.h"

void Title_Main(void);
void Title_Draw(void);
void Option_Main(void);
void Option_DrawEntry(void);
void Map_8019E85C(void);
void Map_8019E8C8(void);
void Map_Main(void);
void Map_Draw(void);

s32 D_menu_801B7BA0;
s32 D_menu_801AD9F0 = 0;

extern void Title_8018F77C(void);

void OvlMenu_CallFunction(u32 mode, void* ptr) {
    switch (mode) {
        case OVLCALL_TITLE_UPDATE:
            Title_Main();
            break;

        case OVLCALL_TITLE_DRAW:
            Title_Draw();
            break;

        case OVLCALL_MAP_UPDATE:
            Map_Main();
            break;

        case OVLCALL_MAP_DRAW:
            Map_Draw();
            break;

        case OVLCALL_OPTION_UPDATE:
            Option_Main();
            break;

        case OVLCALL_OPTION_DRAW:
            Option_DrawEntry();
            break;

        case OVLCALL_GAME_OVER_UPDATE:
            Map_8019E85C();
            break;

        case OVLCALL_UNKMAP_DRAW:
            Map_8019E8C8();
            break;

        case 999:
            Title_8018F77C();
            break;

        default:
            break;
    }
}
