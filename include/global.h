#ifndef GLOBAL_H
#define GLOBAL_H

#include "sys.h"

typedef enum OverlayCalls {
    /*  90 */ OVLCALL_FO_CS_COMPLETE = 90,
    /*  91 */ OVLCALL_BOSS309_UPDATE,
    /*  92 */ OVLCALL_BOSS309_DRAW,
    /*  93 */ OVLCALL_BOSS310_UPDATE,
    /*  94 */ OVLCALL_BOSS310_DRAW,
    /*  95 */ OVLCALL_ACTOR271_UPDATE,
    /*  96 */ OVLCALL_ACTOR271_DRAW,
    /*  97 */ OVLCALL_ACTOR272_UPDATE,
    /*  98 */ OVLCALL_ACTOR272_DRAW,
    /* 103 */ OVLCALL_TITLE_UPDATE = 103,
    /* 104 */ OVLCALL_TITLE_DRAW,
    /* 105 */ OVLCALL_MAP_UPDATE,
    /* 106 */ OVLCALL_MAP_DRAW,
    /* 107 */ OVLCALL_OPTION_UPDATE,
    /* 108 */ OVLCALL_OPTION_DRAW,
    /* 109 */ OVLCALL_GAME_OVER_UPDATE,
    /* 110 */ OVLCALL_UNKMAP_DRAW,
} OverlayCalls;

#include "sf64audio_external.h"
#include "functions.h"
#include "variables.h"
#include "context.h"
#include "sf64mesg.h"
#include "assets/ast_radio.h"
#include "sf64object.h"
#include "sf64level.h"
#include "sf64event.h"
#include "sf64player.h"
#include "i1.h"
#include "i2.h"
#include "i3.h"
#include "i4.h"
#include "i5.h"
#include "i6.h"
#include "libc/math.h"
#include "assets/ast_common.h"
#include "gfx_dimensions.h"
#include <libultraship.h>



#endif // GLOBAL_H
