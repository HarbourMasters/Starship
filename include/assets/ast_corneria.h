#pragma once

#include "gfx.h"
#include "sf64object.h"
#include "sf64level.h"
#include "sf64event.h"
#include "sf64player.h"
#include "sf64audio_external.h"
#include "sf64mesg.h"

static const ALIGN_ASSET(2) char aCoTitleCardTex[] = "__OTR__ast_corneria/aCoTitleCardTex";

static const ALIGN_ASSET(2) char aCoWaterfallDL[] = "__OTR__ast_corneria/aCoWaterfallDL";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_FF8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_FF8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_11F8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_11F8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_13D8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_13D8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_14A8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_14A8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_1698[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_1698";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_1878[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_1878";

static const ALIGN_ASSET(2) char D_CO_60018F8[] = "__OTR__ast_corneria/D_CO_60018F8";

static const ALIGN_ASSET(2) char D_CO_60020F8[] = "__OTR__ast_corneria/D_CO_60020F8";

static const ALIGN_ASSET(2) char D_CO_60028F8[] = "__OTR__ast_corneria/D_CO_60028F8";

static const ALIGN_ASSET(2) char D_CO_60038F8[] = "__OTR__ast_corneria/D_CO_60038F8";

static const ALIGN_ASSET(2) char D_CO_60040F8[] = "__OTR__ast_corneria/D_CO_60040F8";

static const ALIGN_ASSET(2) char D_CO_6004900[] = "__OTR__ast_corneria/D_CO_6004900";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_4970[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_4970";

static const ALIGN_ASSET(2) char D_CO_60049F0[] = "__OTR__ast_corneria/D_CO_60049F0";

static const ALIGN_ASSET(2) char D_CO_60059F0[] = "__OTR__ast_corneria/D_CO_60059F0";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_5A40[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_5A40";

static const ALIGN_ASSET(2) char D_CO_6005A80[] = "__OTR__ast_corneria/D_CO_6005A80";

static const ALIGN_ASSET(2) char aCoArch3DL[] = "__OTR__ast_corneria/aCoArch3DL";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_6BC8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_6BC8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_6CC8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_6CC8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_6D88[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_6D88";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_6DC8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_6DC8";

static const ALIGN_ASSET(2) char D_CO_6006E08[] = "__OTR__ast_corneria/D_CO_6006E08";

static const ALIGN_ASSET(2) char D_CO_6007610[] = "__OTR__ast_corneria/D_CO_6007610";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_7C88[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_7C88";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_7CC8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_7CC8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_7D08[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_7D08";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_7ED8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_7ED8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_7FF8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_7FF8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_81D8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_81D8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_8268[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_8268";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_82E8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_82E8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_8488[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_8488";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_8658[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_8658";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_8858[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_8858";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_8A48[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_8A48";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_8C48[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_8C48";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_8CC8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_8CC8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_8D48[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_8D48";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_8E48[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_8E48";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_9028[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_9028";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_9068[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_9068";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_90A8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_90A8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_9188[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_9188";

static const ALIGN_ASSET(2) char D_CO_60091C8[] = "__OTR__ast_corneria/D_CO_60091C8";

static const ALIGN_ASSET(2) char D_CO_60099C8[] = "__OTR__ast_corneria/D_CO_60099C8";

static const ALIGN_ASSET(2) char D_CO_6009BC8[] = "__OTR__ast_corneria/D_CO_6009BC8";

static const ALIGN_ASSET(2) char D_CO_600A3C8[] = "__OTR__ast_corneria/D_CO_600A3C8";

static const ALIGN_ASSET(2) char D_CO_600ABC8[] = "__OTR__ast_corneria/D_CO_600ABC8";

static const ALIGN_ASSET(2) char D_CO_600B3C8[] = "__OTR__ast_corneria/D_CO_600B3C8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_gfx_BBD0[] = "__OTR__ast_corneria/ast_corneria_seg6_gfx_BBD0";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_BE68[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_BE68";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_BF68[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_BF68";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_C138[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_C138";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_C1F8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_C1F8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_C278[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_C278";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_C358[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_C358";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_C398[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_C398";

static const ALIGN_ASSET(2) char D_CO_600C3D8[] = "__OTR__ast_corneria/D_CO_600C3D8";

static const ALIGN_ASSET(2) char D_CO_600CBD8[] = "__OTR__ast_corneria/D_CO_600CBD8";

static const ALIGN_ASSET(2) char D_CO_600DBD8[] = "__OTR__ast_corneria/D_CO_600DBD8";

static const ALIGN_ASSET(2) char D_CO_600E3D8[] = "__OTR__ast_corneria/D_CO_600E3D8";

static const ALIGN_ASSET(2) char D_CO_600EBD8[] = "__OTR__ast_corneria/D_CO_600EBD8";

static const ALIGN_ASSET(2) char D_CO_600F3D8[] = "__OTR__ast_corneria/D_CO_600F3D8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_gfx_FBE0[] = "__OTR__ast_corneria/ast_corneria_seg6_gfx_FBE0";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_FD40[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_FD40";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_FE40[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_FE40";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_FFD0[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_FFD0";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_10010[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_10010";

static const ALIGN_ASSET(2) char D_CO_6010050[] = "__OTR__ast_corneria/D_CO_6010050";

static const ALIGN_ASSET(2) char D_CO_6010250[] = "__OTR__ast_corneria/D_CO_6010250";

static const ALIGN_ASSET(2) char aCoHighway7DL[] = "__OTR__ast_corneria/aCoHighway7DL";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_10BB8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_10BB8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_10BF8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_10BF8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_10C38[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_10C38";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_10C78[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_10C78";

static const ALIGN_ASSET(2) char aCoHighway5DL[] = "__OTR__ast_corneria/aCoHighway5DL";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_10EB0[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_10EB0";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_10F50[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_10F50";

static const ALIGN_ASSET(2) char D_CO_6010F90[] = "__OTR__ast_corneria/D_CO_6010F90";

static const ALIGN_ASSET(2) char D_CO_6011790[] = "__OTR__ast_corneria/D_CO_6011790";

static const ALIGN_ASSET(2) char aCoCornerianFighterDL[] = "__OTR__ast_corneria/aCoCornerianFighterDL";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_12120[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_12120";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_12310[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_12310";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_12370[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_12370";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_12560[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_12560";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_125C0[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_125C0";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_12610[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_12610";

static const ALIGN_ASSET(2) char D_CO_6012640[] = "__OTR__ast_corneria/D_CO_6012640";

static const ALIGN_ASSET(2) char D_CO_6012840[] = "__OTR__ast_corneria/D_CO_6012840";

static const ALIGN_ASSET(2) char ast_corneria_seg6_gfx_12A40[] = "__OTR__ast_corneria/ast_corneria_seg6_gfx_12A40";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_12AC0[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_12AC0";

static const ALIGN_ASSET(2) char ast_corneria_seg6_gfx_12BA0[] = "__OTR__ast_corneria/ast_corneria_seg6_gfx_12BA0";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_12C20[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_12C20";

static const ALIGN_ASSET(2) char D_CO_6012D00[] = "__OTR__ast_corneria/D_CO_6012D00";

static const ALIGN_ASSET(2) char ast_corneria_seg6_gfx_12F00[] = "__OTR__ast_corneria/ast_corneria_seg6_gfx_12F00";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_13070[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_13070";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_130F0[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_130F0";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_131B0[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_131B0";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_131F0[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_131F0";

static const ALIGN_ASSET(2) char aCoHighway1DL[] = "__OTR__ast_corneria/aCoHighway1DL";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_133F8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_133F8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_13478[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_13478";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_13678[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_13678";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_136A8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_136A8";

static const ALIGN_ASSET(2) char aCoArch2DL[] = "__OTR__ast_corneria/aCoArch2DL";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_13860[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_13860";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_13A40[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_13A40";

static const ALIGN_ASSET(2) char aCoRockwallDL[] = "__OTR__ast_corneria/aCoRockwallDL";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_13BA0[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_13BA0";

static const ALIGN_ASSET(2) char D_CO_6013BE0[] = "__OTR__ast_corneria/D_CO_6013BE0";

static const ALIGN_ASSET(2) char aCoHighway8DL[] = "__OTR__ast_corneria/aCoHighway8DL";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_14450[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_14450";

static const ALIGN_ASSET(2) char aCoHighway4DL[] = "__OTR__ast_corneria/aCoHighway4DL";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_14568[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_14568";

static const ALIGN_ASSET(2) char aCoHighway6DL[] = "__OTR__ast_corneria/aCoHighway6DL";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_147D8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_147D8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_14958[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_14958";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_14998[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_14998";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_149D8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_149D8";

static const ALIGN_ASSET(2) char aCoHighway9DL[] = "__OTR__ast_corneria/aCoHighway9DL";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_14A90[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_14A90";

static const ALIGN_ASSET(2) char aCoBuilding3DL[] = "__OTR__ast_corneria/aCoBuilding3DL";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_14D68[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_14D68";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_14E28[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_14E28";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_14E68[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_14E68";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_14F48[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_14F48";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_14FC8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_14FC8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_150A8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_150A8";

static const ALIGN_ASSET(2) char D_CO_60151A8[] = "__OTR__ast_corneria/D_CO_60151A8";

static const ALIGN_ASSET(2) char aCoTowerDL[] = "__OTR__ast_corneria/aCoTowerDL";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_15480[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_15480";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_15600[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_15600";

static const ALIGN_ASSET(2) char D_CO_6015700[] = "__OTR__ast_corneria/D_CO_6015700";

static const ALIGN_ASSET(2) char aCoStoneArchDL[] = "__OTR__ast_corneria/aCoStoneArchDL";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_15FC8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_15FC8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_161C8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_161C8";

static const ALIGN_ASSET(2) char aRadarDL[] = "__OTR__ast_corneria/aRadarDL";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_16350[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_16350";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_163F0[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_163F0";

static const ALIGN_ASSET(2) char aCoHighway3DL[] = "__OTR__ast_corneria/aCoHighway3DL";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_16540[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_16540";

static const ALIGN_ASSET(2) char aCoBuilding4DL[] = "__OTR__ast_corneria/aCoBuilding4DL";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_16660[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_16660";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_16720[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_16720";

static const ALIGN_ASSET(2) char ast_corneria_seg6_gfx_168D0[] = "__OTR__ast_corneria/ast_corneria_seg6_gfx_168D0";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_16AC8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_16AC8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_16B88[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_16B88";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_16D08[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_16D08";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_16F08[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_16F08";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_16F98[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_16F98";

static const ALIGN_ASSET(2) char ast_corneria_seg6_gfx_170E0[] = "__OTR__ast_corneria/ast_corneria_seg6_gfx_170E0";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_17290[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_17290";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_17480[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_17480";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_17540[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_17540";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_17580[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_17580";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_175C0[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_175C0";

static const ALIGN_ASSET(2) char ast_corneria_seg6_gfx_176C0[] = "__OTR__ast_corneria/ast_corneria_seg6_gfx_176C0";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_17908[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_17908";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_17948[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_17948";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_17B48[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_17B48";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_17BA8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_17BA8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_17CA8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_17CA8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_17DA8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_17DA8";

static const ALIGN_ASSET(2) char D_CO_6017F10[] = "__OTR__ast_corneria/D_CO_6017F10";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_180F8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_180F8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_18158[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_18158";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_182B8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_182B8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_183F8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_183F8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_185F8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_185F8";

static const ALIGN_ASSET(2) char D_CO_60186E0[] = "__OTR__ast_corneria/D_CO_60186E0";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_188D0[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_188D0";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_18930[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_18930";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_18A80[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_18A80";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_18BE0[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_18BE0";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_18DE0[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_18DE0";

static const ALIGN_ASSET(2) char aCoBuilding7DL[] = "__OTR__ast_corneria/aCoBuilding7DL";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_19008[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_19008";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_19088[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_19088";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_190E8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_190E8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_19168[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_19168";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_19198[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_19198";

static const ALIGN_ASSET(2) char D_CO_60191C8[] = "__OTR__ast_corneria/D_CO_60191C8";

static const ALIGN_ASSET(2) char D_CO_60199D0[] = "__OTR__ast_corneria/D_CO_60199D0";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_19A90[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_19A90";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_19B60[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_19B60";

static const ALIGN_ASSET(2) char D_CO_6019C60[] = "__OTR__ast_corneria/D_CO_6019C60";

static const ALIGN_ASSET(2) char D_CO_6019E60[] = "__OTR__ast_corneria/D_CO_6019E60";

static const ALIGN_ASSET(2) char ast_corneria_seg6_gfx_1A660[] = "__OTR__ast_corneria/ast_corneria_seg6_gfx_1A660";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_1A710[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_1A710";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_1A790[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_1A790";

static const ALIGN_ASSET(2) char aCoBuilding2DL[] = "__OTR__ast_corneria/aCoBuilding2DL";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_1A920[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_1A920";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_1AB10[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_1AB10";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_1AB50[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_1AB50";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_1ABD0[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_1ABD0";

static const ALIGN_ASSET(2) char D_CO_601AD60[] = "__OTR__ast_corneria/D_CO_601AD60";

static const ALIGN_ASSET(2) char aCoBuilding5DL[] = "__OTR__ast_corneria/aCoBuilding5DL";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_1B5B8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_1B5B8";

static const ALIGN_ASSET(2) char D_CO_601B640[] = "__OTR__ast_corneria/D_CO_601B640";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_1B660[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_1B660";

static const ALIGN_ASSET(2) char D_CO_601B6C0[] = "__OTR__ast_corneria/D_CO_601B6C0";

static const ALIGN_ASSET(2) char aCoBump2DL[] = "__OTR__ast_corneria/aCoBump2DL";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_1BF78[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_1BF78";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_1C178[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_1C178";

static const ALIGN_ASSET(2) char D_CO_601C1A8[] = "__OTR__ast_corneria/D_CO_601C1A8";

static const ALIGN_ASSET(2) char aCoTreeDL[] = "__OTR__ast_corneria/aCoTreeDL";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_1CA40[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_1CA40";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_1CA70[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_1CA70";

static const ALIGN_ASSET(2) char D_CO_601CAA0[] = "__OTR__ast_corneria/D_CO_601CAA0";

static const ALIGN_ASSET(2) char D_CO_601DAA0[] = "__OTR__ast_corneria/D_CO_601DAA0";

static const ALIGN_ASSET(2) char D_CO_601EAA0[] = "__OTR__ast_corneria/D_CO_601EAA0";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_1EB70[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_1EB70";

static const ALIGN_ASSET(2) char D_CO_601ED00[] = "__OTR__ast_corneria/D_CO_601ED00";

static const ALIGN_ASSET(2) char aCoRuin2DL[] = "__OTR__ast_corneria/aCoRuin2DL";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_1F558[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_1F558";

static const ALIGN_ASSET(2) char aCoArch1DL[] = "__OTR__ast_corneria/aCoArch1DL";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_1F740[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_1F740";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_1F780[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_1F780";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_1F800[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_1F800";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_1F880[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_1F880";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_1F900[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_1F900";

static const ALIGN_ASSET(2) char ast_corneria_seg6_gfx_1F980[] = "__OTR__ast_corneria/ast_corneria_seg6_gfx_1F980";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_1FAE8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_1FAE8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_1FCE8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_1FCE8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_1FDD8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_1FDD8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_1FF18[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_1FF18";

static const ALIGN_ASSET(2) char D_CO_601FF58[] = "__OTR__ast_corneria/D_CO_601FF58";

static const ALIGN_ASSET(2) char D_CO_6020760[] = "__OTR__ast_corneria/D_CO_6020760";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_20810[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_20810";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_209F0[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_209F0";

static const ALIGN_ASSET(2) char aCoRadarDL[] = "__OTR__ast_corneria/aCoRadarDL";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_20CB8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_20CB8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_20E18[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_20E18";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_21008[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_21008";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_210C8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_210C8";

static const ALIGN_ASSET(2) char D_CO_6021188[] = "__OTR__ast_corneria/D_CO_6021188";

static const ALIGN_ASSET(2) char ast_corneria_seg6_gfx_21390[] = "__OTR__ast_corneria/ast_corneria_seg6_gfx_21390";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_216D0[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_216D0";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_218B0[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_218B0";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_21A20[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_21A20";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_21AA0[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_21AA0";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_21B20[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_21B20";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_21CC0[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_21CC0";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_21D80[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_21D80";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_21F80[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_21F80";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_22000[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_22000";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_22090[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_22090";

static const ALIGN_ASSET(2) char D_CO_60220D0[] = "__OTR__ast_corneria/D_CO_60220D0";

static const ALIGN_ASSET(2) char ast_corneria_seg6_gfx_228D0[] = "__OTR__ast_corneria/ast_corneria_seg6_gfx_228D0";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_22980[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_22980";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_22AC0[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_22AC0";

static const ALIGN_ASSET(2) char ast_corneria_seg6_gfx_22B00[] = "__OTR__ast_corneria/ast_corneria_seg6_gfx_22B00";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_22BF8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_22BF8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_22C78[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_22C78";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_22CF8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_22CF8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_gfx_22D40[] = "__OTR__ast_corneria/ast_corneria_seg6_gfx_22D40";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_22E38[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_22E38";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_22EB8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_22EB8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_22F38[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_22F38";

static const ALIGN_ASSET(2) char ast_corneria_seg6_gfx_22F80[] = "__OTR__ast_corneria/ast_corneria_seg6_gfx_22F80";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_23120[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_23120";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_23160[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_23160";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_23320[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_23320";

static const ALIGN_ASSET(2) char ast_corneria_seg6_gfx_23420[] = "__OTR__ast_corneria/ast_corneria_seg6_gfx_23420";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_23610[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_23610";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_237C0[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_237C0";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_238C0[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_238C0";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_23A40[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_23A40";

static const ALIGN_ASSET(2) char aCoIBeamDL[] = "__OTR__ast_corneria/aCoIBeamDL";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_23BA8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_23BA8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_23D28[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_23D28";

static const ALIGN_ASSET(2) char D_CO_6023DE8[] = "__OTR__ast_corneria/D_CO_6023DE8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_gfx_23FF0[] = "__OTR__ast_corneria/ast_corneria_seg6_gfx_23FF0";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_240A0[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_240A0";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_24120[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_24120";

static const ALIGN_ASSET(2) char D_CO_6024160[] = "__OTR__ast_corneria/D_CO_6024160";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_24230[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_24230";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_24420[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_24420";

static const ALIGN_ASSET(2) char aCoBump4DL[] = "__OTR__ast_corneria/aCoBump4DL";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_24528[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_24528";

static const ALIGN_ASSET(2) char D_CO_60245E0[] = "__OTR__ast_corneria/D_CO_60245E0";

static const ALIGN_ASSET(2) char D_CO_6025500[] = "__OTR__ast_corneria/D_CO_6025500";

static const ALIGN_ASSET(2) char D_CO_6026420[] = "__OTR__ast_corneria/D_CO_6026420";

static const ALIGN_ASSET(2) char D_CO_6027340[] = "__OTR__ast_corneria/D_CO_6027340";

static const ALIGN_ASSET(2) char D_CO_6028260[] = "__OTR__ast_corneria/D_CO_6028260";

static const ALIGN_ASSET(2) char D_CO_6028A60[] = "__OTR__ast_corneria/D_CO_6028A60";

static const ALIGN_ASSET(2) char aCoSkibotAnim[] = "__OTR__ast_corneria/aCoSkibotAnim";

static const ALIGN_ASSET(2) char aCoSkibotSkel[] = "__OTR__ast_corneria/aCoSkibotSkel";

static const ALIGN_ASSET(2) char aCoGaruda1Anim[] = "__OTR__ast_corneria/aCoGaruda1Anim";

static const ALIGN_ASSET(2) char aCoGarudaSkel[] = "__OTR__ast_corneria/aCoGarudaSkel";

static const ALIGN_ASSET(2) char aCoGaruda3Anim[] = "__OTR__ast_corneria/aCoGaruda3Anim";

static const ALIGN_ASSET(2) char D_CO_602AA04[] = "__OTR__ast_corneria/D_CO_602AA04";

static const ALIGN_ASSET(2) char aCoDoorsAnim[] = "__OTR__ast_corneria/aCoDoorsAnim";

static const ALIGN_ASSET(2) char aCoDoorsSkel[] = "__OTR__ast_corneria/aCoDoorsSkel";

static const ALIGN_ASSET(2) char aCoGrangaWalkingAnim[] = "__OTR__ast_corneria/aCoGrangaWalkingAnim";

static const ALIGN_ASSET(2) char aCoGrangaSkel[] = "__OTR__ast_corneria/aCoGrangaSkel";

static const ALIGN_ASSET(2) char aCoGrangaStationaryAnim[] = "__OTR__ast_corneria/aCoGrangaStationaryAnim";

static const ALIGN_ASSET(2) char D_CO_602D31C[] = "__OTR__ast_corneria/D_CO_602D31C";

static const ALIGN_ASSET(2) char aCoCarrierAnim[] = "__OTR__ast_corneria/aCoCarrierAnim";

static const ALIGN_ASSET(2) char aCoCarrierSkel[] = "__OTR__ast_corneria/aCoCarrierSkel";

static const ALIGN_ASSET(2) char aCoBuilding1DL[] = "__OTR__ast_corneria/aCoBuilding1DL";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_2D768[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_2D768";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_2D7E8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_2D7E8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_2D8A8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_2D8A8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_2D9A8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_2D9A8";

static const ALIGN_ASSET(2) char aCoBuilding9DL[] = "__OTR__ast_corneria/aCoBuilding9DL";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_2DB18[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_2DB18";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_2DC18[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_2DC18";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_2DC58[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_2DC58";

static const ALIGN_ASSET(2) char aCoRuin1DL[] = "__OTR__ast_corneria/aCoRuin1DL";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_2DCF8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_2DCF8";

static const ALIGN_ASSET(2) char D_CO_602DD40[] = "__OTR__ast_corneria/D_CO_602DD40";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_2DE08[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_2DE08";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_2DFF8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_2DFF8";

static const ALIGN_ASSET(2) char aCoHighway2DL[] = "__OTR__ast_corneria/aCoHighway2DL";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_2E1C8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_2E1C8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_2E248[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_2E248";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_2E438[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_2E438";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_2E468[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_2E468";

static const ALIGN_ASSET(2) char aCoBump5DL[] = "__OTR__ast_corneria/aCoBump5DL";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_2E5F8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_2E5F8";

static const ALIGN_ASSET(2) char aCoBump3DL[] = "__OTR__ast_corneria/aCoBump3DL";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_2E828[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_2E828";

static const ALIGN_ASSET(2) char aCoBump1DL[] = "__OTR__ast_corneria/aCoBump1DL";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_2EA78[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_2EA78";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_2EC78[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_2EC78";

static const ALIGN_ASSET(2) char D_CO_602ECB0[] = "__OTR__ast_corneria/D_CO_602ECB0";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_2ED10[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_2ED10";

static const ALIGN_ASSET(2) char D_CO_602ED50[] = "__OTR__ast_corneria/D_CO_602ED50";

static const ALIGN_ASSET(2) char ast_corneria_seg6_gfx_2EE50[] = "__OTR__ast_corneria/ast_corneria_seg6_gfx_2EE50";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_2EEC8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_2EEC8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_gfx_2F010[] = "__OTR__ast_corneria/ast_corneria_seg6_gfx_2F010";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_2F0A8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_2F0A8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_2F298[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_2F298";

static const ALIGN_ASSET(2) char ast_corneria_seg6_gfx_2F300[] = "__OTR__ast_corneria/ast_corneria_seg6_gfx_2F300";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_2F378[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_2F378";

static const ALIGN_ASSET(2) char ast_corneria_seg6_gfx_2F4C0[] = "__OTR__ast_corneria/ast_corneria_seg6_gfx_2F4C0";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_2F558[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_2F558";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_2F758[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_2F758";

static const ALIGN_ASSET(2) char aCoPoleDL[] = "__OTR__ast_corneria/aCoPoleDL";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_2F818[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_2F818";

static const ALIGN_ASSET(2) char D_CO_602F848[] = "__OTR__ast_corneria/D_CO_602F848";

static const ALIGN_ASSET(2) char D_CO_6030850[] = "__OTR__ast_corneria/D_CO_6030850";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_309E8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_309E8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_30B28[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_30B28";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_30BE8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_30BE8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_30DD8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_30DD8";

static const ALIGN_ASSET(2) char D_CO_6030FD0[] = "__OTR__ast_corneria/D_CO_6030FD0";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_31040[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_31040";

static const ALIGN_ASSET(2) char D_CO_6031130[] = "__OTR__ast_corneria/D_CO_6031130";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_311A0[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_311A0";

static const ALIGN_ASSET(2) char D_CO_6031280[] = "__OTR__ast_corneria/D_CO_6031280";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_31420[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_31420";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_31560[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_31560";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_31620[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_31620";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_31820[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_31820";

static const ALIGN_ASSET(2) char ast_corneria_seg6_gfx_319C0[] = "__OTR__ast_corneria/ast_corneria_seg6_gfx_319C0";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_31B30[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_31B30";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_31CC0[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_31CC0";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_31D00[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_31D00";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_31E80[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_31E80";

static const ALIGN_ASSET(2) char ast_corneria_seg6_gfx_31ED0[] = "__OTR__ast_corneria/ast_corneria_seg6_gfx_31ED0";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_32150[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_32150";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_32350[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_32350";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_323C0[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_323C0";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_324C0[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_324C0";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_325B0[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_325B0";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_326C0[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_326C0";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_328C0[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_328C0";

static const ALIGN_ASSET(2) char aCoGarudaTracksTex[] = "__OTR__ast_corneria/aCoGarudaTracksTex";

static const ALIGN_ASSET(2) char CoMoleMissileDL[] = "__OTR__ast_corneria/CoMoleMissileDL";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_32CE8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_32CE8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_32E38[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_32E38";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_32F18[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_32F18";

static const ALIGN_ASSET(2) char D_CO_6033000[] = "__OTR__ast_corneria/D_CO_6033000";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_33058[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_33058";

static const ALIGN_ASSET(2) char D_CO_6033088[] = "__OTR__ast_corneria/D_CO_6033088";

static const ALIGN_ASSET(2) char D_CO_6033290[] = "__OTR__ast_corneria/D_CO_6033290";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_33350[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_33350";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_33440[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_33440";

static const ALIGN_ASSET(2) char ast_corneria_seg6_gfx_33540[] = "__OTR__ast_corneria/ast_corneria_seg6_gfx_33540";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_336D8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_336D8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_33848[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_33848";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_33998[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_33998";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_33A98[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_33A98";

static const ALIGN_ASSET(2) char D_CO_6033AF0[] = "__OTR__ast_corneria/D_CO_6033AF0";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_33BB0[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_33BB0";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_33CB0[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_33CB0";

static const ALIGN_ASSET(2) char ast_corneria_seg6_gfx_33DB0[] = "__OTR__ast_corneria/ast_corneria_seg6_gfx_33DB0";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_33F48[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_33F48";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_340E8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_340E8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_34248[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_34248";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_34338[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_34338";

static const ALIGN_ASSET(2) char D_CO_6034388[] = "__OTR__ast_corneria/D_CO_6034388";

static const ALIGN_ASSET(2) char aCoShadow1DL[] = "__OTR__ast_corneria/aCoShadow1DL";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_34BE8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_34BE8";

static const ALIGN_ASSET(2) char D_CO_6034C28[] = "__OTR__ast_corneria/D_CO_6034C28";

static const ALIGN_ASSET(2) char D_CO_6035430[] = "__OTR__ast_corneria/D_CO_6035430";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_35490[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_35490";

static const ALIGN_ASSET(2) char D_CO_60354F0[] = "__OTR__ast_corneria/D_CO_60354F0";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_35550[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_35550";

static const ALIGN_ASSET(2) char D_CO_60355A0[] = "__OTR__ast_corneria/D_CO_60355A0";

static const ALIGN_ASSET(2) char aCoBuilding10DL[] = "__OTR__ast_corneria/aCoBuilding10DL";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_35E50[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_35E50";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_35ED0[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_35ED0";

static const ALIGN_ASSET(2) char aCoBuilding8DL[] = "__OTR__ast_corneria/aCoBuilding8DL";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_35FE8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_35FE8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_360E8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_360E8";

static const ALIGN_ASSET(2) char aCoBuilding6DL[] = "__OTR__ast_corneria/aCoBuilding6DL";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_362E8[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_362E8";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_36328[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_36328";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_36368[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_36368";

static const ALIGN_ASSET(2) char D_CO_60363B0[] = "__OTR__ast_corneria/D_CO_60363B0";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_36408[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_36408";

static const ALIGN_ASSET(2) char D_CO_6036438[] = "__OTR__ast_corneria/D_CO_6036438";

static const ALIGN_ASSET(2) char D_CO_6036840[] = "__OTR__ast_corneria/D_CO_6036840";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_36898[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_36898";

static const ALIGN_ASSET(2) char D_CO_60368C8[] = "__OTR__ast_corneria/D_CO_60368C8";

static const ALIGN_ASSET(2) char D_CO_6036CD0[] = "__OTR__ast_corneria/D_CO_6036CD0";

static const ALIGN_ASSET(2) char ast_corneria_seg6_vtx_36D28[] = "__OTR__ast_corneria/ast_corneria_seg6_vtx_36D28";

static const ALIGN_ASSET(2) char D_CO_6036D58[] = "__OTR__ast_corneria/D_CO_6036D58";

static const ALIGN_ASSET(2) char D_CO_6037160[] = "__OTR__ast_corneria/D_CO_6037160";

static const ALIGN_ASSET(2) char aCoOnRailsLevelObjects[] = "__OTR__ast_corneria/aCoOnRailsLevelObjects";

static const ALIGN_ASSET(2) char aCoAllRangeLevelObjects[] = "__OTR__ast_corneria/aCoAllRangeLevelObjects";

static const char D_CO_603D9E8[] = "__OTR__ast_corneria/D_CO_603D9E8";

static const ALIGN_ASSET(2) char D_CO_603DC40[] = "__OTR__ast_corneria/D_CO_603DC40";

static const ALIGN_ASSET(2) char aCoHighway1Hitbox[] = "__OTR__ast_corneria/aCoHighway1Hitbox";

static const ALIGN_ASSET(2) char aCoHighway2Hitbox[] = "__OTR__ast_corneria/aCoHighway2Hitbox";

static const ALIGN_ASSET(2) char aCoBuilding1Hitbox[] = "__OTR__ast_corneria/aCoBuilding1Hitbox";

static const ALIGN_ASSET(2) char aCoBuilding2Hitbox[] = "__OTR__ast_corneria/aCoBuilding2Hitbox";

static const ALIGN_ASSET(2) char aCoBuilding3Hitbox[] = "__OTR__ast_corneria/aCoBuilding3Hitbox";

static const ALIGN_ASSET(2) char aCoBuilding4Hitbox[] = "__OTR__ast_corneria/aCoBuilding4Hitbox";

static const ALIGN_ASSET(2) char aCoBuilding5Hitbox[] = "__OTR__ast_corneria/aCoBuilding5Hitbox";

static const ALIGN_ASSET(2) char aCoBuilding6Hitbox[] = "__OTR__ast_corneria/aCoBuilding6Hitbox";

static const ALIGN_ASSET(2) char aCoBuilding7Hitbox[] = "__OTR__ast_corneria/aCoBuilding7Hitbox";

static const ALIGN_ASSET(2) char aCoBuilding8Hitbox[] = "__OTR__ast_corneria/aCoBuilding8Hitbox";

static const ALIGN_ASSET(2) char aCoWaterfallHitbox[] = "__OTR__ast_corneria/aCoWaterfallHitbox";

static const ALIGN_ASSET(2) char aCoTowerHitbox[] = "__OTR__ast_corneria/aCoTowerHitbox";

static const ALIGN_ASSET(2) char aCoArch1Hitbox[] = "__OTR__ast_corneria/aCoArch1Hitbox";

static const ALIGN_ASSET(2) char aCoArch2Hitbox[] = "__OTR__ast_corneria/aCoArch2Hitbox";

static const ALIGN_ASSET(2) char aCoArch3Hitbox[] = "__OTR__ast_corneria/aCoArch3Hitbox";

static const ALIGN_ASSET(2) char D_CO_603E2C0[] = "__OTR__ast_corneria/D_CO_603E2C0";

static const ALIGN_ASSET(2) char D_CO_603E2F4[] = "__OTR__ast_corneria/D_CO_603E2F4";

static const ALIGN_ASSET(2) char aCoStoneArchHitbox[] = "__OTR__ast_corneria/aCoStoneArchHitbox";

static const ALIGN_ASSET(2) char aCoPoleHitbox[] = "__OTR__ast_corneria/aCoPoleHitbox";

static const ALIGN_ASSET(2) char aCoTreeHitbox[] = "__OTR__ast_corneria/aCoTreeHitbox";

static const ALIGN_ASSET(2) char aCoRadarHitbox[] = "__OTR__ast_corneria/aCoRadarHitbox";

static const ALIGN_ASSET(2) char aCoBuilding9Hitbox[] = "__OTR__ast_corneria/aCoBuilding9Hitbox";

static const ALIGN_ASSET(2) char aCoBuilding10Hitbox[] = "__OTR__ast_corneria/aCoBuilding10Hitbox";

static const ALIGN_ASSET(2) char aCoIBeamHitbox[] = "__OTR__ast_corneria/aCoIBeamHitbox";

static const ALIGN_ASSET(2) char aCoActorSkibotHitbox[] = "__OTR__ast_corneria/aCoActorSkibotHitbox";

static const ALIGN_ASSET(2) char aCoActorRadarHitbox[] = "__OTR__ast_corneria/aCoActorRadarHitbox";

static const ALIGN_ASSET(2) char aCoMoleMissileHitbox[] = "__OTR__ast_corneria/aCoMoleMissileHitbox";

static const ALIGN_ASSET(2) char CoGarudaHitbox[] = "__OTR__ast_corneria/CoGarudaHitbox";

static const ALIGN_ASSET(2) char aCoGarudaDestroyHitbox[] = "__OTR__ast_corneria/aCoGarudaDestroyHitbox";

static const ALIGN_ASSET(2) char aCoGrangaHitbox[] = "__OTR__ast_corneria/aCoGrangaHitbox";

static const ALIGN_ASSET(2) char aCoCarrierLeftHitbox[] = "__OTR__ast_corneria/aCoCarrierLeftHitbox";

static const ALIGN_ASSET(2) char aCoCarrierUpperHitbox[] = "__OTR__ast_corneria/aCoCarrierUpperHitbox";

static const ALIGN_ASSET(2) char aCoCarrierBottomHitbox[] = "__OTR__ast_corneria/aCoCarrierBottomHitbox";

static const ALIGN_ASSET(2) char aCoCarrierHitbox[] = "__OTR__ast_corneria/aCoCarrierHitbox";

static const ALIGN_ASSET(2) char aCoRockwallHitbox[] = "__OTR__ast_corneria/aCoRockwallHitbox";

static const ALIGN_ASSET(2) char aCoDoorsHitbox[] = "__OTR__ast_corneria/aCoDoorsHitbox";

static const ALIGN_ASSET(2) char D_CO_603E924[] = "__OTR__ast_corneria/D_CO_603E924";

static const ALIGN_ASSET(2) char aCoBuildingOnFireHitbox[] = "__OTR__ast_corneria/aCoBuildingOnFireHitbox";

static const ALIGN_ASSET(2) char aCoHighway5Hitbox[] = "__OTR__ast_corneria/aCoHighway5Hitbox";

static const ALIGN_ASSET(2) char aCoHighway6Hitbox[] = "__OTR__ast_corneria/aCoHighway6Hitbox";

static const ALIGN_ASSET(2) char aCoHighway7Hitbox[] = "__OTR__ast_corneria/aCoHighway7Hitbox";

static const ALIGN_ASSET(2) char aCoHighway8Hitbox[] = "__OTR__ast_corneria/aCoHighway8Hitbox";

static const ALIGN_ASSET(2) char aCoHighway9Hitbox[] = "__OTR__ast_corneria/aCoHighway9Hitbox";

static const ALIGN_ASSET(2) char D_CO_603EB38[] = "__OTR__ast_corneria/D_CO_603EB38";

static const ALIGN_ASSET(2) char D_CO_603F338[] = "__OTR__ast_corneria/D_CO_603F338";

static const ALIGN_ASSET(2) char D_CO_603F388[] = "__OTR__ast_corneria/D_CO_603F388";

static const ALIGN_ASSET(2) char D_CO_603F40C[] = "__OTR__ast_corneria/D_CO_603F40C";

static const ALIGN_ASSET(2) char D_CO_603F4E4[] = "__OTR__ast_corneria/D_CO_603F4E4";

