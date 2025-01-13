#pragma once

#include "gfx.h"
#include "sf64object.h"
#include "sf64level.h"
#include "sf64event.h"
#include "sf64player.h"
#include "sf64audio_external.h"
#include "sf64mesg.h"

static const ALIGN_ASSET(2) char aA6TitleCardTex[] = "__OTR__ast_area_6/aA6TitleCardTex";

static const ALIGN_ASSET(2) char D_A6_6000B60[] = "__OTR__ast_area_6/D_A6_6000B60";

static const ALIGN_ASSET(2) char D_A6_6001A80[] = "__OTR__ast_area_6/D_A6_6001A80";

static const ALIGN_ASSET(2) char D_A6_60029A0[] = "__OTR__ast_area_6/D_A6_60029A0";

static const ALIGN_ASSET(2) char D_A6_60038C0[] = "__OTR__ast_area_6/D_A6_60038C0";

static const ALIGN_ASSET(2) char D_A6_60047E0[] = "__OTR__ast_area_6/D_A6_60047E0";

static const ALIGN_ASSET(2) char D_A6_6005700[] = "__OTR__ast_area_6/D_A6_6005700";

static const ALIGN_ASSET(2) char D_A6_6006620[] = "__OTR__ast_area_6/D_A6_6006620";

static const ALIGN_ASSET(2) char D_A6_6006A40[] = "__OTR__ast_area_6/D_A6_6006A40";

static const ALIGN_ASSET(2) char ast_area_6_seg6_gfx_6A50[] = "__OTR__ast_area_6/ast_area_6_seg6_gfx_6A50";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_6ED8[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_6ED8";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_70B8[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_70B8";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_7298[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_7298";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_7498[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_7498";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_7698[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_7698";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_7898[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_7898";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_7A98[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_7A98";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_7C98[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_7C98";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_7DB8[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_7DB8";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_7FA8[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_7FA8";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_8188[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_8188";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_8378[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_8378";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_8498[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_8498";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_8698[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_8698";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_8888[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_8888";

static const ALIGN_ASSET(2) char D_A6_6008918[] = "__OTR__ast_area_6/D_A6_6008918";

static const ALIGN_ASSET(2) char D_A6_6008B18[] = "__OTR__ast_area_6/D_A6_6008B18";

static const ALIGN_ASSET(2) char D_A6_6008D18[] = "__OTR__ast_area_6/D_A6_6008D18";

static const ALIGN_ASSET(2) char D_A6_6008F18[] = "__OTR__ast_area_6/D_A6_6008F18";

static const ALIGN_ASSET(2) char D_A6_6009718[] = "__OTR__ast_area_6/D_A6_6009718";

static const ALIGN_ASSET(2) char D_A6_6009B18[] = "__OTR__ast_area_6/D_A6_6009B18";

static const ALIGN_ASSET(2) char ast_area_6_seg6_gfx_A320[] = "__OTR__ast_area_6/ast_area_6_seg6_gfx_A320";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_A7A8[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_A7A8";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_A988[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_A988";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_AB68[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_AB68";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_AD68[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_AD68";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_AF68[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_AF68";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_B168[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_B168";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_B368[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_B368";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_B568[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_B568";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_B688[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_B688";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_B878[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_B878";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_BA58[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_BA58";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_BC48[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_BC48";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_BD68[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_BD68";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_BF68[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_BF68";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_C158[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_C158";

static const ALIGN_ASSET(2) char ast_area_6_seg6_gfx_C1F0[] = "__OTR__ast_area_6/ast_area_6_seg6_gfx_C1F0";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_C678[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_C678";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_C858[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_C858";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_CA38[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_CA38";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_CC38[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_CC38";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_CE38[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_CE38";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_D038[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_D038";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_D238[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_D238";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_D438[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_D438";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_D558[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_D558";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_D748[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_D748";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_D928[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_D928";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_DB18[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_DB18";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_DC38[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_DC38";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_DE38[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_DE38";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_E028[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_E028";

static const ALIGN_ASSET(2) char aA6UmbraStationDL[] = "__OTR__ast_area_6/aA6UmbraStationDL";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_E2D8[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_E2D8";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_E448[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_E448";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_E648[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_E648";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_E7E8[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_E7E8";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_E9E8[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_E9E8";

static const ALIGN_ASSET(2) char D_A6_600EBE8[] = "__OTR__ast_area_6/D_A6_600EBE8";

static const ALIGN_ASSET(2) char D_A6_600EFE8[] = "__OTR__ast_area_6/D_A6_600EFE8";

static const ALIGN_ASSET(2) char D_A6_600F1F0[] = "__OTR__ast_area_6/D_A6_600F1F0";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_F350[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_F350";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_F540[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_F540";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_F610[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_F610";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_F6A0[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_F6A0";

static const ALIGN_ASSET(2) char D_A6_600F850[] = "__OTR__ast_area_6/D_A6_600F850";

static const ALIGN_ASSET(2) char ast_area_6_seg6_gfx_10050[] = "__OTR__ast_area_6/ast_area_6_seg6_gfx_10050";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_10338[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_10338";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_10438[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_10438";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_10638[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_10638";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_106C8[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_106C8";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_10788[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_10788";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_10978[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_10978";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_10A08[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_10A08";

static const ALIGN_ASSET(2) char D_A6_6010A88[] = "__OTR__ast_area_6/D_A6_6010A88";

static const ALIGN_ASSET(2) char D_A6_6011288[] = "__OTR__ast_area_6/D_A6_6011288";

static const ALIGN_ASSET(2) char D_A6_6011688[] = "__OTR__ast_area_6/D_A6_6011688";

static const ALIGN_ASSET(2) char D_A6_6011888[] = "__OTR__ast_area_6/D_A6_6011888";

static const ALIGN_ASSET(2) char D_A6_6011910[] = "__OTR__ast_area_6/D_A6_6011910";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_119C8[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_119C8";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_11BA8[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_11BA8";

static const ALIGN_ASSET(2) char D_A6_6011D48[] = "__OTR__ast_area_6/D_A6_6011D48";

static const ALIGN_ASSET(2) char D_A6_6012550[] = "__OTR__ast_area_6/D_A6_6012550";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_12600[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_12600";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_12800[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_12800";

static const ALIGN_ASSET(2) char D_A6_6012840[] = "__OTR__ast_area_6/D_A6_6012840";

static const ALIGN_ASSET(2) char aA6HarlockFrigateDL[] = "__OTR__ast_area_6/aA6HarlockFrigateDL";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_12D78[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_12D78";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_12F78[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_12F78";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_130C8[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_130C8";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_132C8[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_132C8";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_13338[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_13338";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_13478[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_13478";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_134D8[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_134D8";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_136D8[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_136D8";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_138B8[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_138B8";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_13AB8[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_13AB8";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_13CA8[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_13CA8";

static const ALIGN_ASSET(2) char D_A6_6013CD8[] = "__OTR__ast_area_6/D_A6_6013CD8";

static const ALIGN_ASSET(2) char D_A6_60144D8[] = "__OTR__ast_area_6/D_A6_60144D8";

static const ALIGN_ASSET(2) char D_A6_6014CD8[] = "__OTR__ast_area_6/D_A6_6014CD8";

static const ALIGN_ASSET(2) char D_A6_60154D8[] = "__OTR__ast_area_6/D_A6_60154D8";

static const ALIGN_ASSET(2) char D_A6_6015CD8[] = "__OTR__ast_area_6/D_A6_6015CD8";

static const ALIGN_ASSET(2) char D_A6_6015EE0[] = "__OTR__ast_area_6/D_A6_6015EE0";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_15FA8[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_15FA8";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_16098[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_16098";

static const ALIGN_ASSET(2) char aA6ZeramClassCruiserDL[] = "__OTR__ast_area_6/aA6ZeramClassCruiserDL";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_164E0[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_164E0";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_166D0[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_166D0";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_168D0[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_168D0";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_16AD0[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_16AD0";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_16B80[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_16B80";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_16C80[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_16C80";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_16E00[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_16E00";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_17000[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_17000";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_17080[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_17080";

static const ALIGN_ASSET(2) char D_A6_6017120[] = "__OTR__ast_area_6/D_A6_6017120";

static const ALIGN_ASSET(2) char D_A6_6017920[] = "__OTR__ast_area_6/D_A6_6017920";

static const ALIGN_ASSET(2) char D_A6_6017B20[] = "__OTR__ast_area_6/D_A6_6017B20";

static const ALIGN_ASSET(2) char D_A6_6017D20[] = "__OTR__ast_area_6/D_A6_6017D20";

static const ALIGN_ASSET(2) char D_A6_6017F20[] = "__OTR__ast_area_6/D_A6_6017F20";

static const ALIGN_ASSET(2) char D_A6_6018720[] = "__OTR__ast_area_6/D_A6_6018720";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_187B8[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_187B8";

static const ALIGN_ASSET(2) char D_A6_60187F8[] = "__OTR__ast_area_6/D_A6_60187F8";

static const ALIGN_ASSET(2) char D_A6_6018878[] = "__OTR__ast_area_6/D_A6_6018878";

static const ALIGN_ASSET(2) char D_A6_6018994[] = "__OTR__ast_area_6/D_A6_6018994";

static const ALIGN_ASSET(2) char D_A6_6018BA0[] = "__OTR__ast_area_6/D_A6_6018BA0";

static const ALIGN_ASSET(2) char aA6NinjinMissileDL[] = "__OTR__ast_area_6/aA6NinjinMissileDL";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_18D30[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_18D30";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_18DD0[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_18DD0";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_18FD0[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_18FD0";

static const ALIGN_ASSET(2) char D_A6_6019130[] = "__OTR__ast_area_6/D_A6_6019130";

static const ALIGN_ASSET(2) char D_A6_6019330[] = "__OTR__ast_area_6/D_A6_6019330";

static const ALIGN_ASSET(2) char D_A6_6019530[] = "__OTR__ast_area_6/D_A6_6019530";

static const ALIGN_ASSET(2) char aA6RocketDL[] = "__OTR__ast_area_6/aA6RocketDL";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_19880[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_19880";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_19940[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_19940";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_19AA0[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_19AA0";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_19AE0[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_19AE0";

static const ALIGN_ASSET(2) char D_A6_6019B20[] = "__OTR__ast_area_6/D_A6_6019B20";

static const ALIGN_ASSET(2) char D_A6_6019D20[] = "__OTR__ast_area_6/D_A6_6019D20";

static const ALIGN_ASSET(2) char D_A6_6019F20[] = "__OTR__ast_area_6/D_A6_6019F20";

static const ALIGN_ASSET(2) char aA6SpaceMineDL[] = "__OTR__ast_area_6/aA6SpaceMineDL";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_1A1B0[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_1A1B0";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_1A1E0[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_1A1E0";

static const ALIGN_ASSET(2) char D_A6_601A220[] = "__OTR__ast_area_6/D_A6_601A220";

static const ALIGN_ASSET(2) char D_A6_601AA20[] = "__OTR__ast_area_6/D_A6_601AA20";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_1AA78[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_1AA78";

static const ALIGN_ASSET(2) char D_A6_601AAA8[] = "__OTR__ast_area_6/D_A6_601AAA8";

static const ALIGN_ASSET(2) char D_A6_601B2B0[] = "__OTR__ast_area_6/D_A6_601B2B0";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_1B308[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_1B308";

static const ALIGN_ASSET(2) char D_A6_601B338[] = "__OTR__ast_area_6/D_A6_601B338";

static const ALIGN_ASSET(2) char D_A6_601BB40[] = "__OTR__ast_area_6/D_A6_601BB40";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_1BD20[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_1BD20";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_1BD60[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_1BD60";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_1BDA0[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_1BDA0";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_1BDE0[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_1BDE0";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_1BE20[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_1BE20";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_1BE60[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_1BE60";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_1BEA0[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_1BEA0";

static const ALIGN_ASSET(2) char ast_area_6_seg6_vtx_1BEE0[] = "__OTR__ast_area_6/ast_area_6_seg6_vtx_1BEE0";

static const ALIGN_ASSET(2) char D_A6_601BF20[] = "__OTR__ast_area_6/D_A6_601BF20";

static const ALIGN_ASSET(2) char D_A6_601CF20[] = "__OTR__ast_area_6/D_A6_601CF20";

static const ALIGN_ASSET(2) char D_A6_601DF20[] = "__OTR__ast_area_6/D_A6_601DF20";

static const ALIGN_ASSET(2) char D_A6_601EF20[] = "__OTR__ast_area_6/D_A6_601EF20";

static const ALIGN_ASSET(2) char D_A6_601FF20[] = "__OTR__ast_area_6/D_A6_601FF20";

static const ALIGN_ASSET(2) char D_A6_6020F20[] = "__OTR__ast_area_6/D_A6_6020F20";

static const ALIGN_ASSET(2) char D_A6_6021F20[] = "__OTR__ast_area_6/D_A6_6021F20";

static const ALIGN_ASSET(2) char D_A6_6022F20[] = "__OTR__ast_area_6/D_A6_6022F20";

static const ALIGN_ASSET(2) char D_A6_6023F20[] = "__OTR__ast_area_6/D_A6_6023F20";

static const ALIGN_ASSET(2) char D_A6_6023F64[] = "__OTR__ast_area_6/D_A6_6023F64";

static const char D_A6_6027F50[] = "__OTR__ast_area_6/D_A6_6027F50";

static const ALIGN_ASSET(2) char aA6UmbraStationHitbox[] = "__OTR__ast_area_6/aA6UmbraStationHitbox";

static const ALIGN_ASSET(2) char aA6HarlockFrigateHitbox[] = "__OTR__ast_area_6/aA6HarlockFrigateHitbox";

static const ALIGN_ASSET(2) char aA6ZeramClassCruiserHitbox[] = "__OTR__ast_area_6/aA6ZeramClassCruiserHitbox";

static const ALIGN_ASSET(2) char aA6GorgonHitbox[] = "__OTR__ast_area_6/aA6GorgonHitbox";

static const ALIGN_ASSET(2) char D_A6_6028578[] = "__OTR__ast_area_6/D_A6_6028578";

static const ALIGN_ASSET(2) char D_A6_6028760[] = "__OTR__ast_area_6/D_A6_6028760";

static const ALIGN_ASSET(2) char D_A6_60287A4[] = "__OTR__ast_area_6/D_A6_60287A4";

static const char D_A6_60289FC[] = "__OTR__ast_area_6/D_A6_60289FC";

