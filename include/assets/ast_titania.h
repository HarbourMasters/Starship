#pragma once

#include "gfx.h"
#include "sf64object.h"
#include "sf64level.h"
#include "sf64event.h"
#include "sf64player.h"
#include "sf64audio_external.h"
#include "sf64mesg.h"

static const ALIGN_ASSET(2) char aTiTitleCardTex[] = "__OTR__ast_titania/aTiTitleCardTex";

static const ALIGN_ASSET(2) char D_TI_6000A80[] = "__OTR__ast_titania/D_TI_6000A80";

static const ALIGN_ASSET(2) char ast_titania_seg6_vtx_AD0[] = "__OTR__ast_titania/ast_titania_seg6_vtx_AD0";

static const ALIGN_ASSET(2) char D_TI_6000B10[] = "__OTR__ast_titania/D_TI_6000B10";

static const ALIGN_ASSET(2) char D_TI_6001B10[] = "__OTR__ast_titania/D_TI_6001B10";

static const ALIGN_ASSET(2) char ast_titania_seg6_vtx_1B68[] = "__OTR__ast_titania/ast_titania_seg6_vtx_1B68";

static const ALIGN_ASSET(2) char D_TI_6001BA8[] = "__OTR__ast_titania/D_TI_6001BA8";

static const ALIGN_ASSET(2) char aTiCactusDL[] = "__OTR__ast_titania/aTiCactusDL";

static const ALIGN_ASSET(2) char ast_titania_seg6_vtx_2408[] = "__OTR__ast_titania/ast_titania_seg6_vtx_2408";

static const ALIGN_ASSET(2) char D_TI_6002438[] = "__OTR__ast_titania/D_TI_6002438";

static const ALIGN_ASSET(2) char D_TI_6003440[] = "__OTR__ast_titania/D_TI_6003440";

static const ALIGN_ASSET(2) char ast_titania_seg6_vtx_3498[] = "__OTR__ast_titania/ast_titania_seg6_vtx_3498";

static const ALIGN_ASSET(2) char D_TI_60034E0[] = "__OTR__ast_titania/D_TI_60034E0";

static const ALIGN_ASSET(2) char ast_titania_seg6_vtx_3538[] = "__OTR__ast_titania/ast_titania_seg6_vtx_3538";

static const ALIGN_ASSET(2) char D_TI_6003580[] = "__OTR__ast_titania/D_TI_6003580";

static const ALIGN_ASSET(2) char ast_titania_seg6_vtx_35D8[] = "__OTR__ast_titania/ast_titania_seg6_vtx_35D8";

static const ALIGN_ASSET(2) char D_TI_6003620[] = "__OTR__ast_titania/D_TI_6003620";

static const ALIGN_ASSET(2) char ast_titania_seg6_vtx_3678[] = "__OTR__ast_titania/ast_titania_seg6_vtx_3678";

static const ALIGN_ASSET(2) char D_TI_60036C0[] = "__OTR__ast_titania/D_TI_60036C0";

static const ALIGN_ASSET(2) char ast_titania_seg6_vtx_3718[] = "__OTR__ast_titania/ast_titania_seg6_vtx_3718";

static const ALIGN_ASSET(2) char D_TI_6003760[] = "__OTR__ast_titania/D_TI_6003760";

static const ALIGN_ASSET(2) char ast_titania_seg6_vtx_37B8[] = "__OTR__ast_titania/ast_titania_seg6_vtx_37B8";

static const ALIGN_ASSET(2) char D_TI_6003800[] = "__OTR__ast_titania/D_TI_6003800";

static const ALIGN_ASSET(2) char D_TI_6003C00[] = "__OTR__ast_titania/D_TI_6003C00";

static const ALIGN_ASSET(2) char D_TI_6004000[] = "__OTR__ast_titania/D_TI_6004000";

static const ALIGN_ASSET(2) char D_TI_6004400[] = "__OTR__ast_titania/D_TI_6004400";

static const ALIGN_ASSET(2) char D_TI_6004800[] = "__OTR__ast_titania/D_TI_6004800";

static const ALIGN_ASSET(2) char D_TI_6004C00[] = "__OTR__ast_titania/D_TI_6004C00";

static const ALIGN_ASSET(2) char D_TI_6005000[] = "__OTR__ast_titania/D_TI_6005000";

static const char D_TI_600631C[] = "__OTR__ast_titania/D_TI_600631C";

static const ALIGN_ASSET(2) char aTi1LandmineHitbox[] = "__OTR__ast_titania/aTi1LandmineHitbox";

static const ALIGN_ASSET(2) char aTiDesertRoverHitbox[] = "__OTR__ast_titania/aTiDesertRoverHitbox";

static const ALIGN_ASSET(2) char aTiSkullHitbox[] = "__OTR__ast_titania/aTiSkullHitbox";

static const ALIGN_ASSET(2) char aTiRib0Hitbox[] = "__OTR__ast_titania/aTiRib0Hitbox";

static const ALIGN_ASSET(2) char aTiRib1Hitbox[] = "__OTR__ast_titania/aTiRib1Hitbox";

static const ALIGN_ASSET(2) char aTiRib2Hitbox[] = "__OTR__ast_titania/aTiRib2Hitbox";

static const ALIGN_ASSET(2) char aTiRib3Hitbox[] = "__OTR__ast_titania/aTiRib3Hitbox";

static const ALIGN_ASSET(2) char aTiRib4Hitbox[] = "__OTR__ast_titania/aTiRib4Hitbox";

static const ALIGN_ASSET(2) char aTiRib5Hitbox[] = "__OTR__ast_titania/aTiRib5Hitbox";

static const ALIGN_ASSET(2) char aTiRib6Hitbox[] = "__OTR__ast_titania/aTiRib6Hitbox";

static const ALIGN_ASSET(2) char aTiRib7Hitbox[] = "__OTR__ast_titania/aTiRib7Hitbox";

static const ALIGN_ASSET(2) char aTiRib8Hitbox[] = "__OTR__ast_titania/aTiRib8Hitbox";

static const ALIGN_ASSET(2) char aTiDelphorHitbox[] = "__OTR__ast_titania/aTiDelphorHitbox";

static const ALIGN_ASSET(2) char aTiDelphorHeadHitbox[] = "__OTR__ast_titania/aTiDelphorHeadHitbox";

static const ALIGN_ASSET(2) char aTiBoulderHitbox[] = "__OTR__ast_titania/aTiBoulderHitbox";

static const ALIGN_ASSET(2) char aTiBombHitbox[] = "__OTR__ast_titania/aTiBombHitbox";

static const ALIGN_ASSET(2) char D_TI_6006874[] = "__OTR__ast_titania/D_TI_6006874";

static const ALIGN_ASSET(2) char aTiRascoHitbox[] = "__OTR__ast_titania/aTiRascoHitbox";

static const ALIGN_ASSET(2) char aTiCactusHitbox[] = "__OTR__ast_titania/aTiCactusHitbox";

static const ALIGN_ASSET(2) char aTiFekudaHitbox[] = "__OTR__ast_titania/aTiFekudaHitbox";

static const ALIGN_ASSET(2) char D_TI_6006924[] = "__OTR__ast_titania/D_TI_6006924";

static const ALIGN_ASSET(2) char D_TI_6006940[] = "__OTR__ast_titania/D_TI_6006940";

static const ALIGN_ASSET(2) char D_TI_600695C[] = "__OTR__ast_titania/D_TI_600695C";

static const ALIGN_ASSET(2) char D_TI_6006978[] = "__OTR__ast_titania/D_TI_6006978";

static const ALIGN_ASSET(2) char D_TI_6006994[] = "__OTR__ast_titania/D_TI_6006994";

static const ALIGN_ASSET(2) char D_TI_60069B0[] = "__OTR__ast_titania/D_TI_60069B0";

static const ALIGN_ASSET(2) char D_TI_60069CC[] = "__OTR__ast_titania/D_TI_60069CC";

static const ALIGN_ASSET(2) char D_TI_60069E8[] = "__OTR__ast_titania/D_TI_60069E8";

static const ALIGN_ASSET(2) char D_TI_6006A04[] = "__OTR__ast_titania/D_TI_6006A04";

static const ALIGN_ASSET(2) char D_TI_6006A20[] = "__OTR__ast_titania/D_TI_6006A20";

static const ALIGN_ASSET(2) char aTiDesertCrawlerHitbox[] = "__OTR__ast_titania/aTiDesertCrawlerHitbox";

static const ALIGN_ASSET(2) char aTiPillarHitbox[] = "__OTR__ast_titania/aTiPillarHitbox";

static const ALIGN_ASSET(2) char D_TI_6006C0C[] = "__OTR__ast_titania/D_TI_6006C0C";

static const ALIGN_ASSET(2) char D_TI_6006C28[] = "__OTR__ast_titania/D_TI_6006C28";

static const ALIGN_ASSET(2) char aTiBridgeHitbox[] = "__OTR__ast_titania/aTiBridgeHitbox";

static const ALIGN_ASSET(2) char D_TI_6006C60[] = "__OTR__ast_titania/D_TI_6006C60";

static const ALIGN_ASSET(2) char D_TI_6009BB8[] = "__OTR__ast_titania/D_TI_6009BB8";

