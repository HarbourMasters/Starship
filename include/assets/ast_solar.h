#pragma once

#include "gfx.h"
#include "sf64object.h"
#include "sf64level.h"
#include "sf64event.h"
#include "sf64player.h"
#include "sf64audio_external.h"
#include "sf64mesg.h"

static const ALIGN_ASSET(2) char aSoTitleCardTex[] = "__OTR__ast_solar/aSoTitleCardTex";

static const ALIGN_ASSET(2) char D_SO_60005B0[] = "__OTR__ast_solar/D_SO_60005B0";

static const ALIGN_ASSET(2) char D_SO_6001C50[] = "__OTR__ast_solar/D_SO_6001C50";

static const ALIGN_ASSET(2) char D_SO_6002E60[] = "__OTR__ast_solar/D_SO_6002E60";

static const ALIGN_ASSET(2) char D_SO_6004500[] = "__OTR__ast_solar/D_SO_6004500";

static const ALIGN_ASSET(2) char D_SO_6005710[] = "__OTR__ast_solar/D_SO_6005710";

static const ALIGN_ASSET(2) char aSoGoreAnim[] = "__OTR__ast_solar/aSoGoreAnim";

static const ALIGN_ASSET(2) char aSoGoreSkel[] = "__OTR__ast_solar/aSoGoreSkel";

static const ALIGN_ASSET(2) char ast_solar_seg6_gfx_65A0[] = "__OTR__ast_solar/ast_solar_seg6_gfx_65A0";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_6600[] = "__OTR__ast_solar/ast_solar_seg6_vtx_6600";

static const ALIGN_ASSET(2) char ast_solar_seg6_gfx_66C0[] = "__OTR__ast_solar/ast_solar_seg6_gfx_66C0";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_6720[] = "__OTR__ast_solar/ast_solar_seg6_vtx_6720";

static const ALIGN_ASSET(2) char ast_solar_seg6_gfx_67E0[] = "__OTR__ast_solar/ast_solar_seg6_gfx_67E0";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_6840[] = "__OTR__ast_solar/ast_solar_seg6_vtx_6840";

static const ALIGN_ASSET(2) char ast_solar_seg6_gfx_6900[] = "__OTR__ast_solar/ast_solar_seg6_gfx_6900";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_69B8[] = "__OTR__ast_solar/ast_solar_seg6_vtx_69B8";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_6B98[] = "__OTR__ast_solar/ast_solar_seg6_vtx_6B98";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_6D78[] = "__OTR__ast_solar/ast_solar_seg6_vtx_6D78";

static const ALIGN_ASSET(2) char D_SO_6006DD8[] = "__OTR__ast_solar/D_SO_6006DD8";

static const ALIGN_ASSET(2) char ast_solar_seg6_gfx_75E0[] = "__OTR__ast_solar/ast_solar_seg6_gfx_75E0";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_7670[] = "__OTR__ast_solar/ast_solar_seg6_vtx_7670";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_7870[] = "__OTR__ast_solar/ast_solar_seg6_vtx_7870";

static const ALIGN_ASSET(2) char ast_solar_seg6_gfx_78A0[] = "__OTR__ast_solar/ast_solar_seg6_gfx_78A0";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_78F8[] = "__OTR__ast_solar/ast_solar_seg6_vtx_78F8";

static const ALIGN_ASSET(2) char ast_solar_seg6_gfx_7930[] = "__OTR__ast_solar/ast_solar_seg6_gfx_7930";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_7988[] = "__OTR__ast_solar/ast_solar_seg6_vtx_7988";

static const ALIGN_ASSET(2) char ast_solar_seg6_gfx_79D0[] = "__OTR__ast_solar/ast_solar_seg6_gfx_79D0";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_7A28[] = "__OTR__ast_solar/ast_solar_seg6_vtx_7A28";

static const ALIGN_ASSET(2) char ast_solar_seg6_gfx_7A70[] = "__OTR__ast_solar/ast_solar_seg6_gfx_7A70";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_7AC8[] = "__OTR__ast_solar/ast_solar_seg6_vtx_7AC8";

static const ALIGN_ASSET(2) char ast_solar_seg6_gfx_7B00[] = "__OTR__ast_solar/ast_solar_seg6_gfx_7B00";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_7B58[] = "__OTR__ast_solar/ast_solar_seg6_vtx_7B58";

static const ALIGN_ASSET(2) char ast_solar_seg6_gfx_7BA0[] = "__OTR__ast_solar/ast_solar_seg6_gfx_7BA0";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_7BF8[] = "__OTR__ast_solar/ast_solar_seg6_vtx_7BF8";

static const ALIGN_ASSET(2) char D_SO_6007C40[] = "__OTR__ast_solar/D_SO_6007C40";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_7C90[] = "__OTR__ast_solar/ast_solar_seg6_vtx_7C90";

static const ALIGN_ASSET(2) char D_SO_6007CC0[] = "__OTR__ast_solar/D_SO_6007CC0";

static const ALIGN_ASSET(2) char D_SO_60084C0[] = "__OTR__ast_solar/D_SO_60084C0";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_8510[] = "__OTR__ast_solar/ast_solar_seg6_vtx_8510";

static const ALIGN_ASSET(2) char D_SO_6008540[] = "__OTR__ast_solar/D_SO_6008540";

static const ALIGN_ASSET(2) char D_SO_6008D40[] = "__OTR__ast_solar/D_SO_6008D40";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_8D90[] = "__OTR__ast_solar/ast_solar_seg6_vtx_8D90";

static const ALIGN_ASSET(2) char D_SO_6008DC0[] = "__OTR__ast_solar/D_SO_6008DC0";

static const ALIGN_ASSET(2) char D_SO_6009D30[] = "__OTR__ast_solar/D_SO_6009D30";

static const ALIGN_ASSET(2) char D_SO_600B1B4[] = "__OTR__ast_solar/D_SO_600B1B4";

static const ALIGN_ASSET(2) char D_SO_600C15C[] = "__OTR__ast_solar/D_SO_600C15C";

static const ALIGN_ASSET(2) char D_SO_600D3DC[] = "__OTR__ast_solar/D_SO_600D3DC";

static const ALIGN_ASSET(2) char D_SO_600E2C4[] = "__OTR__ast_solar/D_SO_600E2C4";

static const ALIGN_ASSET(2) char D_SO_600E470[] = "__OTR__ast_solar/D_SO_600E470";

static const ALIGN_ASSET(2) char D_SO_600F744[] = "__OTR__ast_solar/D_SO_600F744";

static const ALIGN_ASSET(2) char D_SO_600F750[] = "__OTR__ast_solar/D_SO_600F750";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_F9D8[] = "__OTR__ast_solar/ast_solar_seg6_vtx_F9D8";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_FBC8[] = "__OTR__ast_solar/ast_solar_seg6_vtx_FBC8";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_FDC8[] = "__OTR__ast_solar/ast_solar_seg6_vtx_FDC8";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_FFA8[] = "__OTR__ast_solar/ast_solar_seg6_vtx_FFA8";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_100E8[] = "__OTR__ast_solar/ast_solar_seg6_vtx_100E8";

static const ALIGN_ASSET(2) char D_SO_6010198[] = "__OTR__ast_solar/D_SO_6010198";

static const ALIGN_ASSET(2) char D_SO_6010998[] = "__OTR__ast_solar/D_SO_6010998";

static const ALIGN_ASSET(2) char D_SO_6011198[] = "__OTR__ast_solar/D_SO_6011198";

static const ALIGN_ASSET(2) char D_SO_6011398[] = "__OTR__ast_solar/D_SO_6011398";

static const ALIGN_ASSET(2) char D_SO_6012C00[] = "__OTR__ast_solar/D_SO_6012C00";

static const ALIGN_ASSET(2) char D_SO_601388C[] = "__OTR__ast_solar/D_SO_601388C";

static const ALIGN_ASSET(2) char D_SO_60138A0[] = "__OTR__ast_solar/D_SO_60138A0";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_139C0[] = "__OTR__ast_solar/ast_solar_seg6_vtx_139C0";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_13B10[] = "__OTR__ast_solar/ast_solar_seg6_vtx_13B10";

static const ALIGN_ASSET(2) char D_SO_6013C70[] = "__OTR__ast_solar/D_SO_6013C70";

static const ALIGN_ASSET(2) char D_SO_6014470[] = "__OTR__ast_solar/D_SO_6014470";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_14528[] = "__OTR__ast_solar/ast_solar_seg6_vtx_14528";

static const ALIGN_ASSET(2) char D_SO_60146D0[] = "__OTR__ast_solar/D_SO_60146D0";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_14790[] = "__OTR__ast_solar/ast_solar_seg6_vtx_14790";

static const ALIGN_ASSET(2) char D_SO_6014930[] = "__OTR__ast_solar/D_SO_6014930";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_149F0[] = "__OTR__ast_solar/ast_solar_seg6_vtx_149F0";

static const ALIGN_ASSET(2) char D_SO_6014B80[] = "__OTR__ast_solar/D_SO_6014B80";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_14C40[] = "__OTR__ast_solar/ast_solar_seg6_vtx_14C40";

static const ALIGN_ASSET(2) char D_SO_6014DB0[] = "__OTR__ast_solar/D_SO_6014DB0";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_14EC8[] = "__OTR__ast_solar/ast_solar_seg6_vtx_14EC8";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_15038[] = "__OTR__ast_solar/ast_solar_seg6_vtx_15038";

static const ALIGN_ASSET(2) char D_SO_60151A0[] = "__OTR__ast_solar/D_SO_60151A0";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_15378[] = "__OTR__ast_solar/ast_solar_seg6_vtx_15378";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_15578[] = "__OTR__ast_solar/ast_solar_seg6_vtx_15578";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_155E8[] = "__OTR__ast_solar/ast_solar_seg6_vtx_155E8";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_157B8[] = "__OTR__ast_solar/ast_solar_seg6_vtx_157B8";

static const ALIGN_ASSET(2) char D_SO_6015810[] = "__OTR__ast_solar/D_SO_6015810";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_15C88[] = "__OTR__ast_solar/ast_solar_seg6_vtx_15C88";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_15E88[] = "__OTR__ast_solar/ast_solar_seg6_vtx_15E88";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_16078[] = "__OTR__ast_solar/ast_solar_seg6_vtx_16078";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_16278[] = "__OTR__ast_solar/ast_solar_seg6_vtx_16278";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_16478[] = "__OTR__ast_solar/ast_solar_seg6_vtx_16478";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_164A8[] = "__OTR__ast_solar/ast_solar_seg6_vtx_164A8";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_16698[] = "__OTR__ast_solar/ast_solar_seg6_vtx_16698";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_167C8[] = "__OTR__ast_solar/ast_solar_seg6_vtx_167C8";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_16868[] = "__OTR__ast_solar/ast_solar_seg6_vtx_16868";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_16A58[] = "__OTR__ast_solar/ast_solar_seg6_vtx_16A58";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_16C58[] = "__OTR__ast_solar/ast_solar_seg6_vtx_16C58";

static const ALIGN_ASSET(2) char aSoRock3DL[] = "__OTR__ast_solar/aSoRock3DL";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_16DF8[] = "__OTR__ast_solar/ast_solar_seg6_vtx_16DF8";

static const ALIGN_ASSET(2) char D_SO_6016F08[] = "__OTR__ast_solar/D_SO_6016F08";

static const ALIGN_ASSET(2) char D_SO_6017008[] = "__OTR__ast_solar/D_SO_6017008";

static const ALIGN_ASSET(2) char aSoRock2DL[] = "__OTR__ast_solar/aSoRock2DL";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_17160[] = "__OTR__ast_solar/ast_solar_seg6_vtx_17160";

static const ALIGN_ASSET(2) char D_SO_6017200[] = "__OTR__ast_solar/D_SO_6017200";

static const ALIGN_ASSET(2) char D_SO_6017300[] = "__OTR__ast_solar/D_SO_6017300";

static const ALIGN_ASSET(2) char aSoRock1DL[] = "__OTR__ast_solar/aSoRock1DL";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_17440[] = "__OTR__ast_solar/ast_solar_seg6_vtx_17440";

static const ALIGN_ASSET(2) char D_SO_60174E0[] = "__OTR__ast_solar/D_SO_60174E0";

static const ALIGN_ASSET(2) char D_SO_6017520[] = "__OTR__ast_solar/D_SO_6017520";

static const ALIGN_ASSET(2) char D_SO_6017550[] = "__OTR__ast_solar/D_SO_6017550";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_175A8[] = "__OTR__ast_solar/ast_solar_seg6_vtx_175A8";

static const ALIGN_ASSET(2) char D_SO_60175D8[] = "__OTR__ast_solar/D_SO_60175D8";

static const ALIGN_ASSET(2) char D_SO_60185E0[] = "__OTR__ast_solar/D_SO_60185E0";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_18638[] = "__OTR__ast_solar/ast_solar_seg6_vtx_18638";

static const ALIGN_ASSET(2) char D_SO_6018668[] = "__OTR__ast_solar/D_SO_6018668";

static const ALIGN_ASSET(2) char D_SO_6019670[] = "__OTR__ast_solar/D_SO_6019670";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_196C8[] = "__OTR__ast_solar/ast_solar_seg6_vtx_196C8";

static const ALIGN_ASSET(2) char D_SO_60196F8[] = "__OTR__ast_solar/D_SO_60196F8";

static const ALIGN_ASSET(2) char D_SO_601A700[] = "__OTR__ast_solar/D_SO_601A700";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_1A758[] = "__OTR__ast_solar/ast_solar_seg6_vtx_1A758";

static const ALIGN_ASSET(2) char D_SO_601A788[] = "__OTR__ast_solar/D_SO_601A788";

static const ALIGN_ASSET(2) char D_SO_601B790[] = "__OTR__ast_solar/D_SO_601B790";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_1B7E8[] = "__OTR__ast_solar/ast_solar_seg6_vtx_1B7E8";

static const ALIGN_ASSET(2) char D_SO_601B818[] = "__OTR__ast_solar/D_SO_601B818";

static const ALIGN_ASSET(2) char D_SO_601C820[] = "__OTR__ast_solar/D_SO_601C820";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_1C878[] = "__OTR__ast_solar/ast_solar_seg6_vtx_1C878";

static const ALIGN_ASSET(2) char D_SO_601C8A8[] = "__OTR__ast_solar/D_SO_601C8A8";

static const ALIGN_ASSET(2) char D_SO_601D8B0[] = "__OTR__ast_solar/D_SO_601D8B0";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_1D908[] = "__OTR__ast_solar/ast_solar_seg6_vtx_1D908";

static const ALIGN_ASSET(2) char D_SO_601D948[] = "__OTR__ast_solar/D_SO_601D948";

static const ALIGN_ASSET(2) char D_SO_601E150[] = "__OTR__ast_solar/D_SO_601E150";

static const ALIGN_ASSET(2) char ast_solar_seg6_vtx_1E1A8[] = "__OTR__ast_solar/ast_solar_seg6_vtx_1E1A8";

static const ALIGN_ASSET(2) char D_SO_601E1E8[] = "__OTR__ast_solar/D_SO_601E1E8";

static const ALIGN_ASSET(2) char D_SO_601F1F0[] = "__OTR__ast_solar/D_SO_601F1F0";

static const ALIGN_ASSET(2) char D_SO_601F234[] = "__OTR__ast_solar/D_SO_601F234";

static const char D_SO_6020DD0[] = "__OTR__ast_solar/D_SO_6020DD0";

static const ALIGN_ASSET(2) char D_SO_6020F60[] = "__OTR__ast_solar/D_SO_6020F60";

static const ALIGN_ASSET(2) char D_SO_6021F60[] = "__OTR__ast_solar/D_SO_6021F60";

static const ALIGN_ASSET(2) char D_SO_6022760[] = "__OTR__ast_solar/D_SO_6022760";

static const ALIGN_ASSET(2) char D_SO_60229A4[] = "__OTR__ast_solar/D_SO_60229A4";

static const ALIGN_ASSET(2) char D_SO_60231A4[] = "__OTR__ast_solar/D_SO_60231A4";

