#pragma once

#include "gfx.h"
#include "sf64object.h"
#include "sf64level.h"
#include "sf64event.h"
#include "sf64player.h"
#include "sf64audio_external.h"
#include "sf64mesg.h"

static const ALIGN_ASSET(2) char D_versus_3000000[] = "__OTR__ast_versus/D_versus_3000000";

static const ALIGN_ASSET(2) char D_versus_3000080[] = "__OTR__ast_versus/D_versus_3000080";

static const ALIGN_ASSET(2) char D_versus_30000A0[] = "__OTR__ast_versus/D_versus_30000A0";

static const ALIGN_ASSET(2) char D_versus_3000120[] = "__OTR__ast_versus/D_versus_3000120";

static const ALIGN_ASSET(2) char D_versus_3000140[] = "__OTR__ast_versus/D_versus_3000140";

static const ALIGN_ASSET(2) char D_versus_30001C0[] = "__OTR__ast_versus/D_versus_30001C0";

static const ALIGN_ASSET(2) char D_versus_30001E0[] = "__OTR__ast_versus/D_versus_30001E0";

static const ALIGN_ASSET(2) char D_versus_3000380[] = "__OTR__ast_versus/D_versus_3000380";

static const ALIGN_ASSET(2) char D_versus_30003A0[] = "__OTR__ast_versus/D_versus_30003A0";

static const ALIGN_ASSET(2) char D_versus_30004E0[] = "__OTR__ast_versus/D_versus_30004E0";

static const ALIGN_ASSET(2) char D_versus_3000510[] = "__OTR__ast_versus/D_versus_3000510";

static const ALIGN_ASSET(2) char D_versus_30006A0[] = "__OTR__ast_versus/D_versus_30006A0";

static const ALIGN_ASSET(2) char D_versus_30006D0[] = "__OTR__ast_versus/D_versus_30006D0";

static const ALIGN_ASSET(2) char D_versus_3000810[] = "__OTR__ast_versus/D_versus_3000810";

static const ALIGN_ASSET(2) char D_versus_3000840[] = "__OTR__ast_versus/D_versus_3000840";

static const ALIGN_ASSET(2) char D_versus_30008E0[] = "__OTR__ast_versus/D_versus_30008E0";

static const ALIGN_ASSET(2) char D_versus_3000900[] = "__OTR__ast_versus/D_versus_3000900";

static const ALIGN_ASSET(2) char D_versus_30009F0[] = "__OTR__ast_versus/D_versus_30009F0";

static const ALIGN_ASSET(2) char D_versus_3000A10[] = "__OTR__ast_versus/D_versus_3000A10";

static const ALIGN_ASSET(2) char D_versus_3000B00[] = "__OTR__ast_versus/D_versus_3000B00";

static const ALIGN_ASSET(2) char aVsBoostGaugeFrameTex[] = "__OTR__ast_versus/aVsBoostGaugeFrameTex";

static const ALIGN_ASSET(2) char aVsShieldGaugeFrameTex[] = "__OTR__ast_versus/aVsShieldGaugeFrameTex";

static const ALIGN_ASSET(2) char aVsStarTex[] = "__OTR__ast_versus/aVsStarTex";

static const ALIGN_ASSET(2) char D_versus_3001420[] = "__OTR__ast_versus/D_versus_3001420";

static const ALIGN_ASSET(2) char D_versus_3003E20[] = "__OTR__ast_versus/D_versus_3003E20";

static const ALIGN_ASSET(2) char D_versus_3004010[] = "__OTR__ast_versus/D_versus_3004010";

static const ALIGN_ASSET(2) char D_versus_3004D58[] = "__OTR__ast_versus/D_versus_3004D58";

static const ALIGN_ASSET(2) char D_versus_3004F60[] = "__OTR__ast_versus/D_versus_3004F60";

static const ALIGN_ASSET(2) char D_versus_3005E38[] = "__OTR__ast_versus/D_versus_3005E38";

static const ALIGN_ASSET(2) char D_versus_3006040[] = "__OTR__ast_versus/D_versus_3006040";

static const ALIGN_ASSET(2) char D_versus_3006A68[] = "__OTR__ast_versus/D_versus_3006A68";

static const ALIGN_ASSET(2) char D_versus_3006C60[] = "__OTR__ast_versus/D_versus_3006C60";

static const ALIGN_ASSET(2) char D_versus_3007500[] = "__OTR__ast_versus/D_versus_3007500";

static const ALIGN_ASSET(2) char D_versus_30076C0[] = "__OTR__ast_versus/D_versus_30076C0";

static const ALIGN_ASSET(2) char D_versus_3008598[] = "__OTR__ast_versus/D_versus_3008598";

static const ALIGN_ASSET(2) char D_versus_30087A0[] = "__OTR__ast_versus/D_versus_30087A0";

static const ALIGN_ASSET(2) char D_versus_3008DE0[] = "__OTR__ast_versus/D_versus_3008DE0";

static const ALIGN_ASSET(2) char D_versus_3008EC0[] = "__OTR__ast_versus/D_versus_3008EC0";

static const ALIGN_ASSET(2) char D_versus_30098C0[] = "__OTR__ast_versus/D_versus_30098C0";

static const ALIGN_ASSET(2) char D_versus_3009990[] = "__OTR__ast_versus/D_versus_3009990";

static const ALIGN_ASSET(2) char D_versus_300A390[] = "__OTR__ast_versus/D_versus_300A390";

static const ALIGN_ASSET(2) char D_versus_300A470[] = "__OTR__ast_versus/D_versus_300A470";

static const ALIGN_ASSET(2) char D_versus_300B218[] = "__OTR__ast_versus/D_versus_300B218";

static const ALIGN_ASSET(2) char D_versus_300B3F0[] = "__OTR__ast_versus/D_versus_300B3F0";

static const ALIGN_ASSET(2) char D_versus_300C458[] = "__OTR__ast_versus/D_versus_300C458";

static const ALIGN_ASSET(2) char D_versus_300C660[] = "__OTR__ast_versus/D_versus_300C660";

static const ALIGN_ASSET(2) char D_versus_300D150[] = "__OTR__ast_versus/D_versus_300D150";

static const ALIGN_ASSET(2) char aVsBoostGaugeCoolTex[] = "__OTR__ast_versus/aVsBoostGaugeCoolTex";

static const ALIGN_ASSET(2) char aVsBoostGaugeCoolTLUT[] = "__OTR__ast_versus/aVsBoostGaugeCoolTLUT";

static const ALIGN_ASSET(2) char aVsBoostGaugeOverheatTex[] = "__OTR__ast_versus/aVsBoostGaugeOverheatTex";

static const ALIGN_ASSET(2) char aVsBoostGaugeOverheatTLUT[] = "__OTR__ast_versus/aVsBoostGaugeOverheatTLUT";

static const ALIGN_ASSET(2) char aVsShieldGaugeTex[] = "__OTR__ast_versus/aVsShieldGaugeTex";

static const ALIGN_ASSET(2) char aVsShieldGaugeTLUT[] = "__OTR__ast_versus/aVsShieldGaugeTLUT";

static const ALIGN_ASSET(2) char D_versus_300D550[] = "__OTR__ast_versus/D_versus_300D550";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_D860[] = "__OTR__ast_versus/ast_versus_seg3_vtx_D860";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_D970[] = "__OTR__ast_versus/ast_versus_seg3_vtx_D970";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_D9F0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_D9F0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_DA20[] = "__OTR__ast_versus/ast_versus_seg3_vtx_DA20";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_DAC0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_DAC0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_DCB0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_DCB0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_DD40[] = "__OTR__ast_versus/ast_versus_seg3_vtx_DD40";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_DDD0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_DDD0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_DE20[] = "__OTR__ast_versus/ast_versus_seg3_vtx_DE20";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_DE50[] = "__OTR__ast_versus/ast_versus_seg3_vtx_DE50";

static const ALIGN_ASSET(2) char D_versus_300DE80[] = "__OTR__ast_versus/D_versus_300DE80";

static const ALIGN_ASSET(2) char D_versus_300E080[] = "__OTR__ast_versus/D_versus_300E080";

static const ALIGN_ASSET(2) char D_versus_300E280[] = "__OTR__ast_versus/D_versus_300E280";

static const ALIGN_ASSET(2) char D_versus_300E680[] = "__OTR__ast_versus/D_versus_300E680";

static const ALIGN_ASSET(2) char D_versus_300E880[] = "__OTR__ast_versus/D_versus_300E880";

static const ALIGN_ASSET(2) char D_versus_300EA80[] = "__OTR__ast_versus/D_versus_300EA80";

static const ALIGN_ASSET(2) char D_versus_300EC80[] = "__OTR__ast_versus/D_versus_300EC80";

static const ALIGN_ASSET(2) char D_versus_300EE80[] = "__OTR__ast_versus/D_versus_300EE80";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_F150[] = "__OTR__ast_versus/ast_versus_seg3_vtx_F150";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_F350[] = "__OTR__ast_versus/ast_versus_seg3_vtx_F350";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_F460[] = "__OTR__ast_versus/ast_versus_seg3_vtx_F460";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_F4E0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_F4E0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_F510[] = "__OTR__ast_versus/ast_versus_seg3_vtx_F510";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_F5B0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_F5B0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_F770[] = "__OTR__ast_versus/ast_versus_seg3_vtx_F770";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_F800[] = "__OTR__ast_versus/ast_versus_seg3_vtx_F800";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_F850[] = "__OTR__ast_versus/ast_versus_seg3_gfx_F850";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_F9C0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_F9C0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_F9F0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_F9F0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_FA60[] = "__OTR__ast_versus/ast_versus_seg3_vtx_FA60";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_FAF0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_FAF0";

static const ALIGN_ASSET(2) char aVsLandmasterModelDL[] = "__OTR__ast_versus/aVsLandmasterModelDL";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_FE90[] = "__OTR__ast_versus/ast_versus_seg3_vtx_FE90";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_10080[] = "__OTR__ast_versus/ast_versus_seg3_vtx_10080";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_10180[] = "__OTR__ast_versus/ast_versus_seg3_vtx_10180";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_101B0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_101B0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_101E0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_101E0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_10280[] = "__OTR__ast_versus/ast_versus_seg3_vtx_10280";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_102E0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_102E0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_103E0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_103E0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_10560[] = "__OTR__ast_versus/ast_versus_seg3_vtx_10560";

static const ALIGN_ASSET(2) char D_versus_3010690[] = "__OTR__ast_versus/D_versus_3010690";

static const ALIGN_ASSET(2) char D_versus_3010890[] = "__OTR__ast_versus/D_versus_3010890";

static const ALIGN_ASSET(2) char D_versus_3010A90[] = "__OTR__ast_versus/D_versus_3010A90";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_10D80[] = "__OTR__ast_versus/ast_versus_seg3_vtx_10D80";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_10F70[] = "__OTR__ast_versus/ast_versus_seg3_vtx_10F70";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_10FA0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_10FA0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_11020[] = "__OTR__ast_versus/ast_versus_seg3_vtx_11020";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_11050[] = "__OTR__ast_versus/ast_versus_seg3_vtx_11050";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_110F0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_110F0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_112F0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_112F0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_11350[] = "__OTR__ast_versus/ast_versus_seg3_vtx_11350";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_113E0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_113E0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_11440[] = "__OTR__ast_versus/ast_versus_seg3_vtx_11440";

static const ALIGN_ASSET(2) char D_versus_3011470[] = "__OTR__ast_versus/D_versus_3011470";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_11760[] = "__OTR__ast_versus/ast_versus_seg3_vtx_11760";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_11960[] = "__OTR__ast_versus/ast_versus_seg3_vtx_11960";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_11990[] = "__OTR__ast_versus/ast_versus_seg3_vtx_11990";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_11A10[] = "__OTR__ast_versus/ast_versus_seg3_vtx_11A10";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_11A40[] = "__OTR__ast_versus/ast_versus_seg3_vtx_11A40";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_11AE0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_11AE0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_11CC0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_11CC0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_11D20[] = "__OTR__ast_versus/ast_versus_seg3_vtx_11D20";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_11DB0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_11DB0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_11E10[] = "__OTR__ast_versus/ast_versus_seg3_vtx_11E10";

static const ALIGN_ASSET(2) char D_versus_3011E40[] = "__OTR__ast_versus/D_versus_3011E40";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_11E90[] = "__OTR__ast_versus/ast_versus_seg3_vtx_11E90";

static const ALIGN_ASSET(2) char D_versus_3011ED0[] = "__OTR__ast_versus/D_versus_3011ED0";

static const ALIGN_ASSET(2) char aVsSpaceJunk3DL[] = "__OTR__ast_versus/aVsSpaceJunk3DL";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_131A0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_131A0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_13220[] = "__OTR__ast_versus/ast_versus_seg3_vtx_13220";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_132E0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_132E0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_13440[] = "__OTR__ast_versus/ast_versus_seg3_vtx_13440";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_134C0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_134C0";

static const ALIGN_ASSET(2) char aVsSpaceJunk2DL[] = "__OTR__ast_versus/aVsSpaceJunk2DL";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_13640[] = "__OTR__ast_versus/ast_versus_seg3_vtx_13640";

static const ALIGN_ASSET(2) char aVsSpaceJunk1DL[] = "__OTR__ast_versus/aVsSpaceJunk1DL";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_13AD0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_13AD0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_13B50[] = "__OTR__ast_versus/ast_versus_seg3_vtx_13B50";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_13C50[] = "__OTR__ast_versus/ast_versus_seg3_vtx_13C50";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_13CD0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_13CD0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_13DD0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_13DD0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_13E90[] = "__OTR__ast_versus/ast_versus_seg3_vtx_13E90";

static const ALIGN_ASSET(2) char D_versus_3013F50[] = "__OTR__ast_versus/D_versus_3013F50";

static const ALIGN_ASSET(2) char D_versus_3014350[] = "__OTR__ast_versus/D_versus_3014350";

static const ALIGN_ASSET(2) char D_versus_3014510[] = "__OTR__ast_versus/D_versus_3014510";

static const ALIGN_ASSET(2) char D_versus_3014550[] = "__OTR__ast_versus/D_versus_3014550";

static const ALIGN_ASSET(2) char D_versus_3014590[] = "__OTR__ast_versus/D_versus_3014590";

static const ALIGN_ASSET(2) char D_versus_3014690[] = "__OTR__ast_versus/D_versus_3014690";

static const ALIGN_ASSET(2) char D_versus_30146B0[] = "__OTR__ast_versus/D_versus_30146B0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_14700[] = "__OTR__ast_versus/ast_versus_seg3_vtx_14700";

static const ALIGN_ASSET(2) char D_versus_3014740[] = "__OTR__ast_versus/D_versus_3014740";

static const ALIGN_ASSET(2) char D_versus_3015740[] = "__OTR__ast_versus/D_versus_3015740";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_157A8[] = "__OTR__ast_versus/ast_versus_seg3_vtx_157A8";

static const ALIGN_ASSET(2) char D_versus_3015898[] = "__OTR__ast_versus/D_versus_3015898";

static const ALIGN_ASSET(2) char D_versus_30160A0[] = "__OTR__ast_versus/D_versus_30160A0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_16168[] = "__OTR__ast_versus/ast_versus_seg3_vtx_16168";

static const ALIGN_ASSET(2) char D_versus_30162F8[] = "__OTR__ast_versus/D_versus_30162F8";

static const ALIGN_ASSET(2) char aVsKaFlBaseDL[] = "__OTR__ast_versus/aVsKaFlBaseDL";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_16C00[] = "__OTR__ast_versus/ast_versus_seg3_vtx_16C00";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_16D00[] = "__OTR__ast_versus/ast_versus_seg3_vtx_16D00";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_16D40[] = "__OTR__ast_versus/ast_versus_seg3_vtx_16D40";

static const ALIGN_ASSET(2) char D_versus_3016DC0[] = "__OTR__ast_versus/D_versus_3016DC0";

static const ALIGN_ASSET(2) char D_versus_3016FC0[] = "__OTR__ast_versus/D_versus_3016FC0";

static const ALIGN_ASSET(2) char D_versus_30171C0[] = "__OTR__ast_versus/D_versus_30171C0";

static const ALIGN_ASSET(2) char aVsPyramid1DL[] = "__OTR__ast_versus/aVsPyramid1DL";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_17420[] = "__OTR__ast_versus/ast_versus_seg3_vtx_17420";

static const ALIGN_ASSET(2) char aVsPyramid2DL[] = "__OTR__ast_versus/aVsPyramid2DL";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_17540[] = "__OTR__ast_versus/ast_versus_seg3_vtx_17540";

static const ALIGN_ASSET(2) char aVsBuildingDL[] = "__OTR__ast_versus/aVsBuildingDL";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_176C0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_176C0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_177C0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_177C0";

static const ALIGN_ASSET(2) char D_versus_3017800[] = "__OTR__ast_versus/D_versus_3017800";

static const ALIGN_ASSET(2) char D_versus_3018000[] = "__OTR__ast_versus/D_versus_3018000";

static const ALIGN_ASSET(2) char D_versus_3018800[] = "__OTR__ast_versus/D_versus_3018800";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_18960[] = "__OTR__ast_versus/ast_versus_seg3_vtx_18960";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_189E0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_189E0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_18AE0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_18AE0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_18BA0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_18BA0";

static const ALIGN_ASSET(2) char D_versus_3018D60[] = "__OTR__ast_versus/D_versus_3018D60";

static const ALIGN_ASSET(2) char D_versus_3019560[] = "__OTR__ast_versus/D_versus_3019560";

static const ALIGN_ASSET(2) char D_versus_3019D60[] = "__OTR__ast_versus/D_versus_3019D60";

static const ALIGN_ASSET(2) char D_versus_301A560[] = "__OTR__ast_versus/D_versus_301A560";

static const ALIGN_ASSET(2) char D_versus_301AD60[] = "__OTR__ast_versus/D_versus_301AD60";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_1ADB8[] = "__OTR__ast_versus/ast_versus_seg3_vtx_1ADB8";

static const ALIGN_ASSET(2) char D_versus_301ADE8[] = "__OTR__ast_versus/D_versus_301ADE8";

static const ALIGN_ASSET(2) char D_versus_301AEF0[] = "__OTR__ast_versus/D_versus_301AEF0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_1AF48[] = "__OTR__ast_versus/ast_versus_seg3_vtx_1AF48";

static const ALIGN_ASSET(2) char D_versus_301AF78[] = "__OTR__ast_versus/D_versus_301AF78";

static const ALIGN_ASSET(2) char aVsArchDL[] = "__OTR__ast_versus/aVsArchDL";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_1B138[] = "__OTR__ast_versus/ast_versus_seg3_vtx_1B138";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_1B338[] = "__OTR__ast_versus/ast_versus_seg3_vtx_1B338";

static const ALIGN_ASSET(2) char D_versus_301B438[] = "__OTR__ast_versus/D_versus_301B438";

static const ALIGN_ASSET(2) char D_versus_301B640[] = "__OTR__ast_versus/D_versus_301B640";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_1B698[] = "__OTR__ast_versus/ast_versus_seg3_vtx_1B698";

static const ALIGN_ASSET(2) char D_versus_301B6E0[] = "__OTR__ast_versus/D_versus_301B6E0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_1B738[] = "__OTR__ast_versus/ast_versus_seg3_vtx_1B738";

static const ALIGN_ASSET(2) char D_versus_301B768[] = "__OTR__ast_versus/D_versus_301B768";

static const ALIGN_ASSET(2) char D_versus_301C0A4[] = "__OTR__ast_versus/D_versus_301C0A4";

static const ALIGN_ASSET(2) char D_versus_301C3A8[] = "__OTR__ast_versus/D_versus_301C3A8";

static const ALIGN_ASSET(2) char aVsOnFootFalcoSkel[] = "__OTR__ast_versus/aVsOnFootFalcoSkel";

static const ALIGN_ASSET(2) char D_versus_301C79C[] = "__OTR__ast_versus/D_versus_301C79C";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_1C7B0[] = "__OTR__ast_versus/ast_versus_seg3_gfx_1C7B0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_1C880[] = "__OTR__ast_versus/ast_versus_seg3_vtx_1C880";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_1C910[] = "__OTR__ast_versus/ast_versus_seg3_vtx_1C910";

static const ALIGN_ASSET(2) char D_versus_301C9B0[] = "__OTR__ast_versus/D_versus_301C9B0";

static const ALIGN_ASSET(2) char D_versus_301CCE4[] = "__OTR__ast_versus/D_versus_301CCE4";

static const ALIGN_ASSET(2) char D_versus_301CFEC[] = "__OTR__ast_versus/D_versus_301CFEC";

static const ALIGN_ASSET(2) char aVsOnFootFoxSkel[] = "__OTR__ast_versus/aVsOnFootFoxSkel";

static const ALIGN_ASSET(2) char D_versus_301D3DC[] = "__OTR__ast_versus/D_versus_301D3DC";

static const ALIGN_ASSET(2) char D_versus_301D568[] = "__OTR__ast_versus/D_versus_301D568";

static const ALIGN_ASSET(2) char D_versus_301D888[] = "__OTR__ast_versus/D_versus_301D888";

static const ALIGN_ASSET(2) char aVsOnFootPeppySkel[] = "__OTR__ast_versus/aVsOnFootPeppySkel";

static const ALIGN_ASSET(2) char D_versus_301DD6C[] = "__OTR__ast_versus/D_versus_301DD6C";

static const ALIGN_ASSET(2) char D_versus_301DEA4[] = "__OTR__ast_versus/D_versus_301DEA4";

static const ALIGN_ASSET(2) char D_versus_301E19C[] = "__OTR__ast_versus/D_versus_301E19C";

static const ALIGN_ASSET(2) char aVsOnFootSlippySkel[] = "__OTR__ast_versus/aVsOnFootSlippySkel";

static const ALIGN_ASSET(2) char D_versus_301E560[] = "__OTR__ast_versus/D_versus_301E560";

static const ALIGN_ASSET(2) char D_versus_301E570[] = "__OTR__ast_versus/D_versus_301E570";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_1E5C8[] = "__OTR__ast_versus/ast_versus_seg3_vtx_1E5C8";

static const ALIGN_ASSET(2) char D_versus_301E5F8[] = "__OTR__ast_versus/D_versus_301E5F8";

static const ALIGN_ASSET(2) char D_versus_301E700[] = "__OTR__ast_versus/D_versus_301E700";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_1E758[] = "__OTR__ast_versus/ast_versus_seg3_vtx_1E758";

static const ALIGN_ASSET(2) char D_versus_301E788[] = "__OTR__ast_versus/D_versus_301E788";

static const ALIGN_ASSET(2) char D_versus_301E990[] = "__OTR__ast_versus/D_versus_301E990";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_1E9E8[] = "__OTR__ast_versus/ast_versus_seg3_vtx_1E9E8";

static const ALIGN_ASSET(2) char D_versus_301EA18[] = "__OTR__ast_versus/D_versus_301EA18";

static const ALIGN_ASSET(2) char D_versus_301EC20[] = "__OTR__ast_versus/D_versus_301EC20";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_1EC78[] = "__OTR__ast_versus/ast_versus_seg3_vtx_1EC78";

static const ALIGN_ASSET(2) char D_versus_301ECA8[] = "__OTR__ast_versus/D_versus_301ECA8";

static const ALIGN_ASSET(2) char D_versus_301EEB0[] = "__OTR__ast_versus/D_versus_301EEB0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_1EF08[] = "__OTR__ast_versus/ast_versus_seg3_vtx_1EF08";

static const ALIGN_ASSET(2) char D_versus_301EF38[] = "__OTR__ast_versus/D_versus_301EF38";

static const ALIGN_ASSET(2) char aVsLandmasterCanonDL[] = "__OTR__ast_versus/aVsLandmasterCanonDL";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_1F208[] = "__OTR__ast_versus/ast_versus_seg3_vtx_1F208";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_1F278[] = "__OTR__ast_versus/ast_versus_seg3_vtx_1F278";

static const ALIGN_ASSET(2) char D_versus_301F2E0[] = "__OTR__ast_versus/D_versus_301F2E0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_1F338[] = "__OTR__ast_versus/ast_versus_seg3_vtx_1F338";

static const ALIGN_ASSET(2) char D_versus_301F368[] = "__OTR__ast_versus/D_versus_301F368";

static const ALIGN_ASSET(2) char D_versus_301F570[] = "__OTR__ast_versus/D_versus_301F570";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_1F5C8[] = "__OTR__ast_versus/ast_versus_seg3_vtx_1F5C8";

static const ALIGN_ASSET(2) char D_versus_301F5F8[] = "__OTR__ast_versus/D_versus_301F5F8";

static const ALIGN_ASSET(2) char D_versus_301F800[] = "__OTR__ast_versus/D_versus_301F800";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_1F858[] = "__OTR__ast_versus/ast_versus_seg3_vtx_1F858";

static const ALIGN_ASSET(2) char D_versus_301F888[] = "__OTR__ast_versus/D_versus_301F888";

static const ALIGN_ASSET(2) char D_versus_301FA90[] = "__OTR__ast_versus/D_versus_301FA90";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_1FAE8[] = "__OTR__ast_versus/ast_versus_seg3_vtx_1FAE8";

static const ALIGN_ASSET(2) char D_versus_301FB18[] = "__OTR__ast_versus/D_versus_301FB18";

static const ALIGN_ASSET(2) char D_versus_301FD20[] = "__OTR__ast_versus/D_versus_301FD20";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_1FD78[] = "__OTR__ast_versus/ast_versus_seg3_vtx_1FD78";

static const ALIGN_ASSET(2) char D_versus_301FDA8[] = "__OTR__ast_versus/D_versus_301FDA8";

static const ALIGN_ASSET(2) char D_versus_301FFB0[] = "__OTR__ast_versus/D_versus_301FFB0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_20008[] = "__OTR__ast_versus/ast_versus_seg3_vtx_20008";

static const ALIGN_ASSET(2) char D_versus_3020048[] = "__OTR__ast_versus/D_versus_3020048";

static const ALIGN_ASSET(2) char D_versus_3020850[] = "__OTR__ast_versus/D_versus_3020850";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_208A8[] = "__OTR__ast_versus/ast_versus_seg3_vtx_208A8";

static const ALIGN_ASSET(2) char D_versus_30208D8[] = "__OTR__ast_versus/D_versus_30208D8";

static const ALIGN_ASSET(2) char D_versus_3020AE0[] = "__OTR__ast_versus/D_versus_3020AE0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_20B38[] = "__OTR__ast_versus/ast_versus_seg3_vtx_20B38";

static const ALIGN_ASSET(2) char D_versus_3020B78[] = "__OTR__ast_versus/D_versus_3020B78";

static const ALIGN_ASSET(2) char D_versus_3020D80[] = "__OTR__ast_versus/D_versus_3020D80";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_20DD8[] = "__OTR__ast_versus/ast_versus_seg3_vtx_20DD8";

static const ALIGN_ASSET(2) char D_versus_3020E18[] = "__OTR__ast_versus/D_versus_3020E18";

static const ALIGN_ASSET(2) char D_versus_3021620[] = "__OTR__ast_versus/D_versus_3021620";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_21678[] = "__OTR__ast_versus/ast_versus_seg3_vtx_21678";

static const ALIGN_ASSET(2) char D_versus_30216B8[] = "__OTR__ast_versus/D_versus_30216B8";

static const ALIGN_ASSET(2) char D_versus_30218C0[] = "__OTR__ast_versus/D_versus_30218C0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_21918[] = "__OTR__ast_versus/ast_versus_seg3_vtx_21918";

static const ALIGN_ASSET(2) char D_versus_3021958[] = "__OTR__ast_versus/D_versus_3021958";

static const ALIGN_ASSET(2) char D_versus_3022160[] = "__OTR__ast_versus/D_versus_3022160";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_221B8[] = "__OTR__ast_versus/ast_versus_seg3_vtx_221B8";

static const ALIGN_ASSET(2) char D_versus_30221E8[] = "__OTR__ast_versus/D_versus_30221E8";

static const ALIGN_ASSET(2) char D_versus_30223F0[] = "__OTR__ast_versus/D_versus_30223F0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_22450[] = "__OTR__ast_versus/ast_versus_seg3_vtx_22450";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_22490[] = "__OTR__ast_versus/ast_versus_seg3_gfx_22490";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_224F0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_224F0";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_22530[] = "__OTR__ast_versus/ast_versus_seg3_gfx_22530";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_225A0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_225A0";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_22600[] = "__OTR__ast_versus/ast_versus_seg3_gfx_22600";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_22670[] = "__OTR__ast_versus/ast_versus_seg3_vtx_22670";

static const ALIGN_ASSET(2) char D_versus_30226D0[] = "__OTR__ast_versus/D_versus_30226D0";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_22750[] = "__OTR__ast_versus/ast_versus_seg3_gfx_22750";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_227B0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_227B0";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_227F0[] = "__OTR__ast_versus/ast_versus_seg3_gfx_227F0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_22850[] = "__OTR__ast_versus/ast_versus_seg3_vtx_22850";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_22890[] = "__OTR__ast_versus/ast_versus_seg3_gfx_22890";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_22A40[] = "__OTR__ast_versus/ast_versus_seg3_vtx_22A40";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_22B60[] = "__OTR__ast_versus/ast_versus_seg3_vtx_22B60";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_22C30[] = "__OTR__ast_versus/ast_versus_seg3_vtx_22C30";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_22CB0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_22CB0";

static const ALIGN_ASSET(2) char D_versus_3022DE0[] = "__OTR__ast_versus/D_versus_3022DE0";

static const ALIGN_ASSET(2) char D_versus_3022E60[] = "__OTR__ast_versus/D_versus_3022E60";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_23060[] = "__OTR__ast_versus/ast_versus_seg3_gfx_23060";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_23138[] = "__OTR__ast_versus/ast_versus_seg3_vtx_23138";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_231B8[] = "__OTR__ast_versus/ast_versus_seg3_vtx_231B8";

static const ALIGN_ASSET(2) char D_versus_3023238[] = "__OTR__ast_versus/D_versus_3023238";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_23A40[] = "__OTR__ast_versus/ast_versus_seg3_gfx_23A40";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_23AA8[] = "__OTR__ast_versus/ast_versus_seg3_vtx_23AA8";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_23B00[] = "__OTR__ast_versus/ast_versus_seg3_gfx_23B00";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_23B68[] = "__OTR__ast_versus/ast_versus_seg3_vtx_23B68";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_23BC0[] = "__OTR__ast_versus/ast_versus_seg3_gfx_23BC0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_23C28[] = "__OTR__ast_versus/ast_versus_seg3_vtx_23C28";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_23C80[] = "__OTR__ast_versus/ast_versus_seg3_gfx_23C80";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_23DE8[] = "__OTR__ast_versus/ast_versus_seg3_vtx_23DE8";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_23E18[] = "__OTR__ast_versus/ast_versus_seg3_vtx_23E18";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_23E88[] = "__OTR__ast_versus/ast_versus_seg3_vtx_23E88";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_23F18[] = "__OTR__ast_versus/ast_versus_seg3_vtx_23F18";

static const ALIGN_ASSET(2) char D_versus_3023F68[] = "__OTR__ast_versus/D_versus_3023F68";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_23FF0[] = "__OTR__ast_versus/ast_versus_seg3_gfx_23FF0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_24050[] = "__OTR__ast_versus/ast_versus_seg3_vtx_24050";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_24090[] = "__OTR__ast_versus/ast_versus_seg3_gfx_24090";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_240F0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_240F0";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_24130[] = "__OTR__ast_versus/ast_versus_seg3_gfx_24130";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_241A0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_241A0";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_24200[] = "__OTR__ast_versus/ast_versus_seg3_gfx_24200";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_24270[] = "__OTR__ast_versus/ast_versus_seg3_vtx_24270";

static const ALIGN_ASSET(2) char D_versus_30242D0[] = "__OTR__ast_versus/D_versus_30242D0";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_24350[] = "__OTR__ast_versus/ast_versus_seg3_gfx_24350";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_243B0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_243B0";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_243F0[] = "__OTR__ast_versus/ast_versus_seg3_gfx_243F0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_24450[] = "__OTR__ast_versus/ast_versus_seg3_vtx_24450";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_24490[] = "__OTR__ast_versus/ast_versus_seg3_gfx_24490";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_244E8[] = "__OTR__ast_versus/ast_versus_seg3_vtx_244E8";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_24520[] = "__OTR__ast_versus/ast_versus_seg3_gfx_24520";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_24578[] = "__OTR__ast_versus/ast_versus_seg3_vtx_24578";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_245C0[] = "__OTR__ast_versus/ast_versus_seg3_gfx_245C0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_24618[] = "__OTR__ast_versus/ast_versus_seg3_vtx_24618";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_24660[] = "__OTR__ast_versus/ast_versus_seg3_gfx_24660";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_246B8[] = "__OTR__ast_versus/ast_versus_seg3_vtx_246B8";

static const ALIGN_ASSET(2) char D_versus_30246E8[] = "__OTR__ast_versus/D_versus_30246E8";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_24770[] = "__OTR__ast_versus/ast_versus_seg3_gfx_24770";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_248C0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_248C0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_24A40[] = "__OTR__ast_versus/ast_versus_seg3_vtx_24A40";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_24AC0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_24AC0";

static const ALIGN_ASSET(2) char D_versus_3024C30[] = "__OTR__ast_versus/D_versus_3024C30";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_24E30[] = "__OTR__ast_versus/ast_versus_seg3_gfx_24E30";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_24F68[] = "__OTR__ast_versus/ast_versus_seg3_vtx_24F68";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_25068[] = "__OTR__ast_versus/ast_versus_seg3_vtx_25068";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_250B8[] = "__OTR__ast_versus/ast_versus_seg3_vtx_250B8";

static const ALIGN_ASSET(2) char D_versus_3025138[] = "__OTR__ast_versus/D_versus_3025138";

static const ALIGN_ASSET(2) char D_versus_3025938[] = "__OTR__ast_versus/D_versus_3025938";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_259C0[] = "__OTR__ast_versus/ast_versus_seg3_gfx_259C0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_25A30[] = "__OTR__ast_versus/ast_versus_seg3_vtx_25A30";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_25A90[] = "__OTR__ast_versus/ast_versus_seg3_gfx_25A90";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_25B08[] = "__OTR__ast_versus/ast_versus_seg3_vtx_25B08";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_25B80[] = "__OTR__ast_versus/ast_versus_seg3_gfx_25B80";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_25BF8[] = "__OTR__ast_versus/ast_versus_seg3_vtx_25BF8";

static const ALIGN_ASSET(2) char D_versus_3025C68[] = "__OTR__ast_versus/D_versus_3025C68";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_25E70[] = "__OTR__ast_versus/ast_versus_seg3_gfx_25E70";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_25ED0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_25ED0";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_25F10[] = "__OTR__ast_versus/ast_versus_seg3_gfx_25F10";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_25F80[] = "__OTR__ast_versus/ast_versus_seg3_vtx_25F80";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_25FE0[] = "__OTR__ast_versus/ast_versus_seg3_gfx_25FE0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_26050[] = "__OTR__ast_versus/ast_versus_seg3_vtx_26050";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_260C0[] = "__OTR__ast_versus/ast_versus_seg3_gfx_260C0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_26130[] = "__OTR__ast_versus/ast_versus_seg3_vtx_26130";

static const ALIGN_ASSET(2) char D_versus_30261A0[] = "__OTR__ast_versus/D_versus_30261A0";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_26220[] = "__OTR__ast_versus/ast_versus_seg3_gfx_26220";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_26290[] = "__OTR__ast_versus/ast_versus_seg3_vtx_26290";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_262F0[] = "__OTR__ast_versus/ast_versus_seg3_gfx_262F0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_26350[] = "__OTR__ast_versus/ast_versus_seg3_vtx_26350";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_26390[] = "__OTR__ast_versus/ast_versus_seg3_gfx_26390";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_26668[] = "__OTR__ast_versus/ast_versus_seg3_vtx_26668";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_266F8[] = "__OTR__ast_versus/ast_versus_seg3_vtx_266F8";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_26728[] = "__OTR__ast_versus/ast_versus_seg3_vtx_26728";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_26798[] = "__OTR__ast_versus/ast_versus_seg3_vtx_26798";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_267F8[] = "__OTR__ast_versus/ast_versus_seg3_vtx_267F8";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_26828[] = "__OTR__ast_versus/ast_versus_seg3_vtx_26828";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_26898[] = "__OTR__ast_versus/ast_versus_seg3_vtx_26898";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_26988[] = "__OTR__ast_versus/ast_versus_seg3_vtx_26988";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_26A08[] = "__OTR__ast_versus/ast_versus_seg3_vtx_26A08";

static const ALIGN_ASSET(2) char D_versus_3026A38[] = "__OTR__ast_versus/D_versus_3026A38";

static const ALIGN_ASSET(2) char D_versus_3026AB8[] = "__OTR__ast_versus/D_versus_3026AB8";

static const ALIGN_ASSET(2) char D_versus_3026B38[] = "__OTR__ast_versus/D_versus_3026B38";

static const ALIGN_ASSET(2) char D_versus_3026BB8[] = "__OTR__ast_versus/D_versus_3026BB8";

static const ALIGN_ASSET(2) char D_versus_3026C38[] = "__OTR__ast_versus/D_versus_3026C38";

static const ALIGN_ASSET(2) char D_versus_3026CB8[] = "__OTR__ast_versus/D_versus_3026CB8";

static const ALIGN_ASSET(2) char D_versus_3026DB8[] = "__OTR__ast_versus/D_versus_3026DB8";

static const ALIGN_ASSET(2) char D_versus_3026EB8[] = "__OTR__ast_versus/D_versus_3026EB8";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_270C0[] = "__OTR__ast_versus/ast_versus_seg3_gfx_270C0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_27188[] = "__OTR__ast_versus/ast_versus_seg3_vtx_27188";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_271F8[] = "__OTR__ast_versus/ast_versus_seg3_vtx_271F8";

static const ALIGN_ASSET(2) char D_versus_3027268[] = "__OTR__ast_versus/D_versus_3027268";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_27A70[] = "__OTR__ast_versus/ast_versus_seg3_gfx_27A70";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_27AE8[] = "__OTR__ast_versus/ast_versus_seg3_vtx_27AE8";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_27BE0[] = "__OTR__ast_versus/ast_versus_seg3_gfx_27BE0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_27C50[] = "__OTR__ast_versus/ast_versus_seg3_vtx_27C50";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_27CB0[] = "__OTR__ast_versus/ast_versus_seg3_gfx_27CB0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_27D20[] = "__OTR__ast_versus/ast_versus_seg3_vtx_27D20";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_27D80[] = "__OTR__ast_versus/ast_versus_seg3_gfx_27D80";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_27EF0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_27EF0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_27F30[] = "__OTR__ast_versus/ast_versus_seg3_vtx_27F30";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_27FC0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_27FC0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_28050[] = "__OTR__ast_versus/ast_versus_seg3_vtx_28050";

static const ALIGN_ASSET(2) char D_versus_3028130[] = "__OTR__ast_versus/D_versus_3028130";

static const ALIGN_ASSET(2) char D_versus_3028230[] = "__OTR__ast_versus/D_versus_3028230";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_28630[] = "__OTR__ast_versus/ast_versus_seg3_gfx_28630";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_28690[] = "__OTR__ast_versus/ast_versus_seg3_vtx_28690";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_286D0[] = "__OTR__ast_versus/ast_versus_seg3_gfx_286D0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_28730[] = "__OTR__ast_versus/ast_versus_seg3_vtx_28730";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_28770[] = "__OTR__ast_versus/ast_versus_seg3_gfx_28770";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_287F0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_287F0";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_28870[] = "__OTR__ast_versus/ast_versus_seg3_gfx_28870";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_288F0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_288F0";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_28970[] = "__OTR__ast_versus/ast_versus_seg3_gfx_28970";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_289D0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_289D0";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_28A10[] = "__OTR__ast_versus/ast_versus_seg3_gfx_28A10";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_28A70[] = "__OTR__ast_versus/ast_versus_seg3_vtx_28A70";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_28AB0[] = "__OTR__ast_versus/ast_versus_seg3_gfx_28AB0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_28B80[] = "__OTR__ast_versus/ast_versus_seg3_vtx_28B80";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_28BC0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_28BC0";

static const ALIGN_ASSET(2) char D_versus_3028C60[] = "__OTR__ast_versus/D_versus_3028C60";

static const ALIGN_ASSET(2) char D_versus_3028CE0[] = "__OTR__ast_versus/D_versus_3028CE0";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_28EE0[] = "__OTR__ast_versus/ast_versus_seg3_gfx_28EE0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_28FC0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_28FC0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_29060[] = "__OTR__ast_versus/ast_versus_seg3_vtx_29060";

static const ALIGN_ASSET(2) char D_versus_3029160[] = "__OTR__ast_versus/D_versus_3029160";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_291E0[] = "__OTR__ast_versus/ast_versus_seg3_gfx_291E0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_292A8[] = "__OTR__ast_versus/ast_versus_seg3_vtx_292A8";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_29318[] = "__OTR__ast_versus/ast_versus_seg3_vtx_29318";

static const ALIGN_ASSET(2) char D_versus_3029388[] = "__OTR__ast_versus/D_versus_3029388";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_29B90[] = "__OTR__ast_versus/ast_versus_seg3_gfx_29B90";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_29BF8[] = "__OTR__ast_versus/ast_versus_seg3_vtx_29BF8";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_29C50[] = "__OTR__ast_versus/ast_versus_seg3_gfx_29C50";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_29CB8[] = "__OTR__ast_versus/ast_versus_seg3_vtx_29CB8";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_29D20[] = "__OTR__ast_versus/ast_versus_seg3_gfx_29D20";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_29D88[] = "__OTR__ast_versus/ast_versus_seg3_vtx_29D88";

static const ALIGN_ASSET(2) char ast_versus_seg3_gfx_29DF0[] = "__OTR__ast_versus/ast_versus_seg3_gfx_29DF0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_29F50[] = "__OTR__ast_versus/ast_versus_seg3_vtx_29F50";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_29F90[] = "__OTR__ast_versus/ast_versus_seg3_vtx_29F90";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_29FF0[] = "__OTR__ast_versus/ast_versus_seg3_vtx_29FF0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_2A050[] = "__OTR__ast_versus/ast_versus_seg3_vtx_2A050";

static const ALIGN_ASSET(2) char D_versus_302A0A0[] = "__OTR__ast_versus/D_versus_302A0A0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_2A0F8[] = "__OTR__ast_versus/ast_versus_seg3_vtx_2A0F8";

static const ALIGN_ASSET(2) char D_versus_302A138[] = "__OTR__ast_versus/D_versus_302A138";

static const ALIGN_ASSET(2) char D_versus_302A940[] = "__OTR__ast_versus/D_versus_302A940";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_2A998[] = "__OTR__ast_versus/ast_versus_seg3_vtx_2A998";

static const ALIGN_ASSET(2) char D_versus_302A9C8[] = "__OTR__ast_versus/D_versus_302A9C8";

static const ALIGN_ASSET(2) char D_versus_302ABD0[] = "__OTR__ast_versus/D_versus_302ABD0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_2AC28[] = "__OTR__ast_versus/ast_versus_seg3_vtx_2AC28";

static const ALIGN_ASSET(2) char D_versus_302AC68[] = "__OTR__ast_versus/D_versus_302AC68";

static const ALIGN_ASSET(2) char D_versus_302B470[] = "__OTR__ast_versus/D_versus_302B470";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_2B4C8[] = "__OTR__ast_versus/ast_versus_seg3_vtx_2B4C8";

static const ALIGN_ASSET(2) char D_versus_302B4F8[] = "__OTR__ast_versus/D_versus_302B4F8";

static const ALIGN_ASSET(2) char D_versus_302B700[] = "__OTR__ast_versus/D_versus_302B700";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_2B758[] = "__OTR__ast_versus/ast_versus_seg3_vtx_2B758";

static const ALIGN_ASSET(2) char D_versus_302B788[] = "__OTR__ast_versus/D_versus_302B788";

static const ALIGN_ASSET(2) char D_versus_302B890[] = "__OTR__ast_versus/D_versus_302B890";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_2B8E8[] = "__OTR__ast_versus/ast_versus_seg3_vtx_2B8E8";

static const ALIGN_ASSET(2) char D_versus_302B918[] = "__OTR__ast_versus/D_versus_302B918";

static const ALIGN_ASSET(2) char D_versus_302BA20[] = "__OTR__ast_versus/D_versus_302BA20";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_2BA78[] = "__OTR__ast_versus/ast_versus_seg3_vtx_2BA78";

static const ALIGN_ASSET(2) char D_versus_302BAA8[] = "__OTR__ast_versus/D_versus_302BAA8";

static const ALIGN_ASSET(2) char D_versus_302BBB0[] = "__OTR__ast_versus/D_versus_302BBB0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_2BC08[] = "__OTR__ast_versus/ast_versus_seg3_vtx_2BC08";

static const ALIGN_ASSET(2) char D_versus_302BC38[] = "__OTR__ast_versus/D_versus_302BC38";

static const ALIGN_ASSET(2) char D_versus_302BD40[] = "__OTR__ast_versus/D_versus_302BD40";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_2BD98[] = "__OTR__ast_versus/ast_versus_seg3_vtx_2BD98";

static const ALIGN_ASSET(2) char D_versus_302BDC8[] = "__OTR__ast_versus/D_versus_302BDC8";

static const ALIGN_ASSET(2) char D_versus_302BED0[] = "__OTR__ast_versus/D_versus_302BED0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_2BF58[] = "__OTR__ast_versus/ast_versus_seg3_vtx_2BF58";

static const ALIGN_ASSET(2) char D_versus_302BF88[] = "__OTR__ast_versus/D_versus_302BF88";

static const ALIGN_ASSET(2) char D_versus_302C088[] = "__OTR__ast_versus/D_versus_302C088";

static const ALIGN_ASSET(2) char D_versus_302C0D0[] = "__OTR__ast_versus/D_versus_302C0D0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_2C158[] = "__OTR__ast_versus/ast_versus_seg3_vtx_2C158";

static const ALIGN_ASSET(2) char D_versus_302C188[] = "__OTR__ast_versus/D_versus_302C188";

static const ALIGN_ASSET(2) char D_versus_302C288[] = "__OTR__ast_versus/D_versus_302C288";

static const ALIGN_ASSET(2) char D_versus_302C350[] = "__OTR__ast_versus/D_versus_302C350";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_2C3D8[] = "__OTR__ast_versus/ast_versus_seg3_vtx_2C3D8";

static const ALIGN_ASSET(2) char D_versus_302C408[] = "__OTR__ast_versus/D_versus_302C408";

static const ALIGN_ASSET(2) char D_versus_302C508[] = "__OTR__ast_versus/D_versus_302C508";

static const ALIGN_ASSET(2) char D_versus_302C5A0[] = "__OTR__ast_versus/D_versus_302C5A0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_2C628[] = "__OTR__ast_versus/ast_versus_seg3_vtx_2C628";

static const ALIGN_ASSET(2) char D_versus_302C658[] = "__OTR__ast_versus/D_versus_302C658";

static const ALIGN_ASSET(2) char D_versus_302C758[] = "__OTR__ast_versus/D_versus_302C758";

static const ALIGN_ASSET(2) char D_versus_302C830[] = "__OTR__ast_versus/D_versus_302C830";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_2C8B8[] = "__OTR__ast_versus/ast_versus_seg3_vtx_2C8B8";

static const ALIGN_ASSET(2) char D_versus_302C8E8[] = "__OTR__ast_versus/D_versus_302C8E8";

static const ALIGN_ASSET(2) char D_versus_302C9E8[] = "__OTR__ast_versus/D_versus_302C9E8";

static const ALIGN_ASSET(2) char D_versus_302CB40[] = "__OTR__ast_versus/D_versus_302CB40";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_2CBC8[] = "__OTR__ast_versus/ast_versus_seg3_vtx_2CBC8";

static const ALIGN_ASSET(2) char D_versus_302CBF8[] = "__OTR__ast_versus/D_versus_302CBF8";

static const ALIGN_ASSET(2) char D_versus_302CCF8[] = "__OTR__ast_versus/D_versus_302CCF8";

static const ALIGN_ASSET(2) char D_versus_302CE40[] = "__OTR__ast_versus/D_versus_302CE40";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_2CEC8[] = "__OTR__ast_versus/ast_versus_seg3_vtx_2CEC8";

static const ALIGN_ASSET(2) char D_versus_302CEF8[] = "__OTR__ast_versus/D_versus_302CEF8";

static const ALIGN_ASSET(2) char D_versus_302CFF8[] = "__OTR__ast_versus/D_versus_302CFF8";

static const ALIGN_ASSET(2) char D_versus_302D120[] = "__OTR__ast_versus/D_versus_302D120";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_2D178[] = "__OTR__ast_versus/ast_versus_seg3_vtx_2D178";

static const ALIGN_ASSET(2) char D_versus_302D1B8[] = "__OTR__ast_versus/D_versus_302D1B8";

static const ALIGN_ASSET(2) char D_versus_302D240[] = "__OTR__ast_versus/D_versus_302D240";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_2D298[] = "__OTR__ast_versus/ast_versus_seg3_vtx_2D298";

static const ALIGN_ASSET(2) char D_versus_302D2C8[] = "__OTR__ast_versus/D_versus_302D2C8";

static const ALIGN_ASSET(2) char D_versus_302D4D0[] = "__OTR__ast_versus/D_versus_302D4D0";

static const ALIGN_ASSET(2) char ast_versus_seg3_vtx_2D528[] = "__OTR__ast_versus/ast_versus_seg3_vtx_2D528";

static const ALIGN_ASSET(2) char D_versus_302D568[] = "__OTR__ast_versus/D_versus_302D568";

static const ALIGN_ASSET(2) char D_versus_302DD70[] = "__OTR__ast_versus/D_versus_302DD70";

static const ALIGN_ASSET(2) char D_versus_302DDB4[] = "__OTR__ast_versus/D_versus_302DDB4";

static const ALIGN_ASSET(2) char D_versus_302DDF8[] = "__OTR__ast_versus/D_versus_302DDF8";

static const ALIGN_ASSET(2) char D_versus_302DE3C[] = "__OTR__ast_versus/D_versus_302DE3C";

static const ALIGN_ASSET(2) char D_versus_302E0E4[] = "__OTR__ast_versus/D_versus_302E0E4";

static const ALIGN_ASSET(2) char D_versus_302E170[] = "__OTR__ast_versus/D_versus_302E170";

static const ALIGN_ASSET(2) char D_versus_302E378[] = "__OTR__ast_versus/D_versus_302E378";

static const ALIGN_ASSET(2) char D_versus_302E56C[] = "__OTR__ast_versus/D_versus_302E56C";

static const ALIGN_ASSET(2) char D_versus_302E65C[] = "__OTR__ast_versus/D_versus_302E65C";

static const ALIGN_ASSET(2) char D_versus_302E74C[] = "__OTR__ast_versus/D_versus_302E74C";

static const ALIGN_ASSET(2) char D_versus_302E830[] = "__OTR__ast_versus/D_versus_302E830";

static const ALIGN_ASSET(2) char D_versus_302E95C[] = "__OTR__ast_versus/D_versus_302E95C";

static const ALIGN_ASSET(2) char D_versus_302EA4C[] = "__OTR__ast_versus/D_versus_302EA4C";

static const ALIGN_ASSET(2) char D_versus_302EB3C[] = "__OTR__ast_versus/D_versus_302EB3C";

static const ALIGN_ASSET(2) char D_versus_302EC20[] = "__OTR__ast_versus/D_versus_302EC20";

static const ALIGN_ASSET(2) char aVsSpaceJunk1Hitbox[] = "__OTR__ast_versus/aVsSpaceJunk1Hitbox";

static const ALIGN_ASSET(2) char aVsSpaceJunk2Hitbox[] = "__OTR__ast_versus/aVsSpaceJunk2Hitbox";

static const ALIGN_ASSET(2) char aVsSpaceJunk3Hitbox[] = "__OTR__ast_versus/aVsSpaceJunk3Hitbox";

static const ALIGN_ASSET(2) char aVsKaFlBaseHitbox[] = "__OTR__ast_versus/aVsKaFlBaseHitbox";

static const ALIGN_ASSET(2) char aVsBuilding1Hibox[] = "__OTR__ast_versus/aVsBuilding1Hibox";

static const ALIGN_ASSET(2) char aVsBuilding2Hibox[] = "__OTR__ast_versus/aVsBuilding2Hibox";

static const ALIGN_ASSET(2) char aVsArchHitbox[] = "__OTR__ast_versus/aVsArchHitbox";

static const ALIGN_ASSET(2) char D_versus_302EEE8[] = "__OTR__ast_versus/D_versus_302EEE8";

static const ALIGN_ASSET(2) char D_versus_302EF00[] = "__OTR__ast_versus/D_versus_302EF00";

static const ALIGN_ASSET(2) char D_versus_302EF6C[] = "__OTR__ast_versus/D_versus_302EF6C";

static const ALIGN_ASSET(2) char D_versus_302EF84[] = "__OTR__ast_versus/D_versus_302EF84";

static const ALIGN_ASSET(2) char D_versus_302EFF0[] = "__OTR__ast_versus/D_versus_302EFF0";

static const ALIGN_ASSET(2) char D_versus_302F008[] = "__OTR__ast_versus/D_versus_302F008";

static const ALIGN_ASSET(2) char D_versus_302F044[] = "__OTR__ast_versus/D_versus_302F044";

static const ALIGN_ASSET(2) char D_versus_302F098[] = "__OTR__ast_versus/D_versus_302F098";

