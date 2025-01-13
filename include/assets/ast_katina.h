#pragma once

#include "gfx.h"
#include "sf64object.h"
#include "sf64level.h"
#include "sf64event.h"
#include "sf64player.h"
#include "sf64audio_external.h"

static const ALIGN_ASSET(2) char aKaTitleCardTex[] = "__OTR__ast_katina/aKaTitleCardTex";

static const ALIGN_ASSET(2) char D_KA_6001260[] = "__OTR__ast_katina/D_KA_6001260";

static const ALIGN_ASSET(2) char aKaDestroyedHatchDL[] = "__OTR__ast_katina/aKaDestroyedHatchDL";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_1330[] = "__OTR__ast_katina/ast_katina_seg6_vtx_1330";

static const ALIGN_ASSET(2) char aKaEnemyDL[] = "__OTR__ast_katina/aKaEnemyDL";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_1658[] = "__OTR__ast_katina/ast_katina_seg6_vtx_1658";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_1698[] = "__OTR__ast_katina/ast_katina_seg6_vtx_1698";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_1738[] = "__OTR__ast_katina/ast_katina_seg6_vtx_1738";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_1938[] = "__OTR__ast_katina/ast_katina_seg6_vtx_1938";

static const ALIGN_ASSET(2) char D_KA_6001968[] = "__OTR__ast_katina/D_KA_6001968";

static const ALIGN_ASSET(2) char D_KA_6002170[] = "__OTR__ast_katina/D_KA_6002170";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_28F8[] = "__OTR__ast_katina/ast_katina_seg6_vtx_28F8";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_2AC8[] = "__OTR__ast_katina/ast_katina_seg6_vtx_2AC8";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_2CA8[] = "__OTR__ast_katina/ast_katina_seg6_vtx_2CA8";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_2EA8[] = "__OTR__ast_katina/ast_katina_seg6_vtx_2EA8";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_3088[] = "__OTR__ast_katina/ast_katina_seg6_vtx_3088";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_31A8[] = "__OTR__ast_katina/ast_katina_seg6_vtx_31A8";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_33A8[] = "__OTR__ast_katina/ast_katina_seg6_vtx_33A8";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_34A8[] = "__OTR__ast_katina/ast_katina_seg6_vtx_34A8";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_3698[] = "__OTR__ast_katina/ast_katina_seg6_vtx_3698";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_3888[] = "__OTR__ast_katina/ast_katina_seg6_vtx_3888";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_3A88[] = "__OTR__ast_katina/ast_katina_seg6_vtx_3A88";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_3AE8[] = "__OTR__ast_katina/ast_katina_seg6_vtx_3AE8";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_3BE8[] = "__OTR__ast_katina/ast_katina_seg6_vtx_3BE8";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_3D78[] = "__OTR__ast_katina/ast_katina_seg6_vtx_3D78";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_3DB8[] = "__OTR__ast_katina/ast_katina_seg6_vtx_3DB8";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_3DF8[] = "__OTR__ast_katina/ast_katina_seg6_vtx_3DF8";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_3E38[] = "__OTR__ast_katina/ast_katina_seg6_vtx_3E38";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_3E78[] = "__OTR__ast_katina/ast_katina_seg6_vtx_3E78";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_3EB8[] = "__OTR__ast_katina/ast_katina_seg6_vtx_3EB8";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_3EF8[] = "__OTR__ast_katina/ast_katina_seg6_vtx_3EF8";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_3F38[] = "__OTR__ast_katina/ast_katina_seg6_vtx_3F38";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_3F78[] = "__OTR__ast_katina/ast_katina_seg6_vtx_3F78";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_3FB8[] = "__OTR__ast_katina/ast_katina_seg6_vtx_3FB8";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_3FF8[] = "__OTR__ast_katina/ast_katina_seg6_vtx_3FF8";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_4038[] = "__OTR__ast_katina/ast_katina_seg6_vtx_4038";

static const ALIGN_ASSET(2) char D_KA_6004078[] = "__OTR__ast_katina/D_KA_6004078";

static const ALIGN_ASSET(2) char D_KA_60040F8[] = "__OTR__ast_katina/D_KA_60040F8";

static const ALIGN_ASSET(2) char D_KA_60048F8[] = "__OTR__ast_katina/D_KA_60048F8";

static const ALIGN_ASSET(2) char D_KA_60050F8[] = "__OTR__ast_katina/D_KA_60050F8";

static const ALIGN_ASSET(2) char D_KA_60052F8[] = "__OTR__ast_katina/D_KA_60052F8";

static const ALIGN_ASSET(2) char D_KA_6005AF8[] = "__OTR__ast_katina/D_KA_6005AF8";

static const ALIGN_ASSET(2) char D_KA_60062F8[] = "__OTR__ast_katina/D_KA_60062F8";

static const ALIGN_ASSET(2) char D_KA_6006AF8[] = "__OTR__ast_katina/D_KA_6006AF8";

static const ALIGN_ASSET(2) char aKaDestroyedKaSaucererDL[] = "__OTR__ast_katina/aKaDestroyedKaSaucererDL";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_7B00[] = "__OTR__ast_katina/ast_katina_seg6_vtx_7B00";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_7CD0[] = "__OTR__ast_katina/ast_katina_seg6_vtx_7CD0";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_7EB0[] = "__OTR__ast_katina/ast_katina_seg6_vtx_7EB0";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_80B0[] = "__OTR__ast_katina/ast_katina_seg6_vtx_80B0";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_8290[] = "__OTR__ast_katina/ast_katina_seg6_vtx_8290";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_8330[] = "__OTR__ast_katina/ast_katina_seg6_vtx_8330";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_8530[] = "__OTR__ast_katina/ast_katina_seg6_vtx_8530";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_8630[] = "__OTR__ast_katina/ast_katina_seg6_vtx_8630";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_8820[] = "__OTR__ast_katina/ast_katina_seg6_vtx_8820";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_8A20[] = "__OTR__ast_katina/ast_katina_seg6_vtx_8A20";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_8A50[] = "__OTR__ast_katina/ast_katina_seg6_vtx_8A50";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_8B50[] = "__OTR__ast_katina/ast_katina_seg6_vtx_8B50";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_8C60[] = "__OTR__ast_katina/ast_katina_seg6_vtx_8C60";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_8CA0[] = "__OTR__ast_katina/ast_katina_seg6_vtx_8CA0";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_8CE0[] = "__OTR__ast_katina/ast_katina_seg6_vtx_8CE0";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_8D20[] = "__OTR__ast_katina/ast_katina_seg6_vtx_8D20";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_8D60[] = "__OTR__ast_katina/ast_katina_seg6_vtx_8D60";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_8DA0[] = "__OTR__ast_katina/ast_katina_seg6_vtx_8DA0";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_8DE0[] = "__OTR__ast_katina/ast_katina_seg6_vtx_8DE0";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_8E20[] = "__OTR__ast_katina/ast_katina_seg6_vtx_8E20";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_8E60[] = "__OTR__ast_katina/ast_katina_seg6_vtx_8E60";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_8FE0[] = "__OTR__ast_katina/ast_katina_seg6_vtx_8FE0";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_9150[] = "__OTR__ast_katina/ast_katina_seg6_vtx_9150";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_9190[] = "__OTR__ast_katina/ast_katina_seg6_vtx_9190";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_91D0[] = "__OTR__ast_katina/ast_katina_seg6_vtx_91D0";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_9210[] = "__OTR__ast_katina/ast_katina_seg6_vtx_9210";

static const ALIGN_ASSET(2) char D_KA_6009250[] = "__OTR__ast_katina/D_KA_6009250";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_9318[] = "__OTR__ast_katina/ast_katina_seg6_vtx_9318";

static const ALIGN_ASSET(2) char D_KA_60094A8[] = "__OTR__ast_katina/D_KA_60094A8";

static const ALIGN_ASSET(2) char D_KA_6009CB0[] = "__OTR__ast_katina/D_KA_6009CB0";

static const ALIGN_ASSET(2) char D_KA_600ABD0[] = "__OTR__ast_katina/D_KA_600ABD0";

static const ALIGN_ASSET(2) char aKaFLBaseDL[] = "__OTR__ast_katina/aKaFLBaseDL";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_BBF0[] = "__OTR__ast_katina/ast_katina_seg6_vtx_BBF0";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_BCF0[] = "__OTR__ast_katina/ast_katina_seg6_vtx_BCF0";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_BD30[] = "__OTR__ast_katina/ast_katina_seg6_vtx_BD30";

static const ALIGN_ASSET(2) char D_KA_600BDB0[] = "__OTR__ast_katina/D_KA_600BDB0";

static const ALIGN_ASSET(2) char D_KA_600BFB0[] = "__OTR__ast_katina/D_KA_600BFB0";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_C058[] = "__OTR__ast_katina/ast_katina_seg6_vtx_C058";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_C258[] = "__OTR__ast_katina/ast_katina_seg6_vtx_C258";

static const ALIGN_ASSET(2) char D_KA_600C2D8[] = "__OTR__ast_katina/D_KA_600C2D8";

static const ALIGN_ASSET(2) char aKaFLBaseDestroyedDL[] = "__OTR__ast_katina/aKaFLBaseDestroyedDL";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_C5A0[] = "__OTR__ast_katina/ast_katina_seg6_vtx_C5A0";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_C620[] = "__OTR__ast_katina/ast_katina_seg6_vtx_C620";

static const ALIGN_ASSET(2) char D_KA_600C760[] = "__OTR__ast_katina/D_KA_600C760";

static const ALIGN_ASSET(2) char D_KA_600C960[] = "__OTR__ast_katina/D_KA_600C960";

static const ALIGN_ASSET(2) char D_KA_600CB60[] = "__OTR__ast_katina/D_KA_600CB60";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_CC18[] = "__OTR__ast_katina/ast_katina_seg6_vtx_CC18";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_CCB8[] = "__OTR__ast_katina/ast_katina_seg6_vtx_CCB8";

static const ALIGN_ASSET(2) char aDestroyedHatch2DL[] = "__OTR__ast_katina/aDestroyedHatch2DL";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_CE58[] = "__OTR__ast_katina/ast_katina_seg6_vtx_CE58";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_D058[] = "__OTR__ast_katina/ast_katina_seg6_vtx_D058";

static const ALIGN_ASSET(2) char aDestroyedCoreDL[] = "__OTR__ast_katina/aDestroyedCoreDL";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_D140[] = "__OTR__ast_katina/ast_katina_seg6_vtx_D140";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_D250[] = "__OTR__ast_katina/ast_katina_seg6_vtx_D250";

static const ALIGN_ASSET(2) char aDestroyedHatch4DL[] = "__OTR__ast_katina/aDestroyedHatch4DL";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_D318[] = "__OTR__ast_katina/ast_katina_seg6_vtx_D318";

static const ALIGN_ASSET(2) char aDestroyedHatch3DL[] = "__OTR__ast_katina/aDestroyedHatch3DL";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_D568[] = "__OTR__ast_katina/ast_katina_seg6_vtx_D568";

static const ALIGN_ASSET(2) char aKaCornerianFighterShadowDL[] = "__OTR__ast_katina/aKaCornerianFighterShadowDL";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_D788[] = "__OTR__ast_katina/ast_katina_seg6_vtx_D788";

static const ALIGN_ASSET(2) char D_KA_600D7B8[] = "__OTR__ast_katina/D_KA_600D7B8";

static const ALIGN_ASSET(2) char aKaEnemyShadowDL[] = "__OTR__ast_katina/aKaEnemyShadowDL";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_DC18[] = "__OTR__ast_katina/ast_katina_seg6_vtx_DC18";

static const ALIGN_ASSET(2) char D_KA_600DC48[] = "__OTR__ast_katina/D_KA_600DC48";

static const ALIGN_ASSET(2) char aKaCornerianFighterDL[] = "__OTR__ast_katina/aKaCornerianFighterDL";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_E208[] = "__OTR__ast_katina/ast_katina_seg6_vtx_E208";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_E3F8[] = "__OTR__ast_katina/ast_katina_seg6_vtx_E3F8";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_E4C8[] = "__OTR__ast_katina/ast_katina_seg6_vtx_E4C8";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_E6C8[] = "__OTR__ast_katina/ast_katina_seg6_vtx_E6C8";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_E728[] = "__OTR__ast_katina/ast_katina_seg6_vtx_E728";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_E7B8[] = "__OTR__ast_katina/ast_katina_seg6_vtx_E7B8";

static const ALIGN_ASSET(2) char D_KA_600E7E8[] = "__OTR__ast_katina/D_KA_600E7E8";

static const ALIGN_ASSET(2) char D_KA_600E9E8[] = "__OTR__ast_katina/D_KA_600E9E8";

static const ALIGN_ASSET(2) char D_KA_600EBE8[] = "__OTR__ast_katina/D_KA_600EBE8";

static const ALIGN_ASSET(2) char D_KA_600EDE8[] = "__OTR__ast_katina/D_KA_600EDE8";

static const ALIGN_ASSET(2) char aKaEnemyLowPolyDL[] = "__OTR__ast_katina/aKaEnemyLowPolyDL";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_F098[] = "__OTR__ast_katina/ast_katina_seg6_vtx_F098";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_F128[] = "__OTR__ast_katina/ast_katina_seg6_vtx_F128";

static const ALIGN_ASSET(2) char D_KA_600F1D0[] = "__OTR__ast_katina/D_KA_600F1D0";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_F220[] = "__OTR__ast_katina/ast_katina_seg6_vtx_F220";

static const ALIGN_ASSET(2) char D_KA_600F260[] = "__OTR__ast_katina/D_KA_600F260";

static const ALIGN_ASSET(2) char D_KA_6010260[] = "__OTR__ast_katina/D_KA_6010260";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_10338[] = "__OTR__ast_katina/ast_katina_seg6_vtx_10338";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_104B8[] = "__OTR__ast_katina/ast_katina_seg6_vtx_104B8";

static const ALIGN_ASSET(2) char D_KA_60105D8[] = "__OTR__ast_katina/D_KA_60105D8";

static const ALIGN_ASSET(2) char D_KA_6010744[] = "__OTR__ast_katina/D_KA_6010744";

static const ALIGN_ASSET(2) char D_KA_6010780[] = "__OTR__ast_katina/D_KA_6010780";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_10858[] = "__OTR__ast_katina/ast_katina_seg6_vtx_10858";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_109F8[] = "__OTR__ast_katina/ast_katina_seg6_vtx_109F8";

static const ALIGN_ASSET(2) char D_KA_6010A60[] = "__OTR__ast_katina/D_KA_6010A60";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_10B38[] = "__OTR__ast_katina/ast_katina_seg6_vtx_10B38";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_10CB8[] = "__OTR__ast_katina/ast_katina_seg6_vtx_10CB8";

static const ALIGN_ASSET(2) char D_KA_6010D20[] = "__OTR__ast_katina/D_KA_6010D20";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_10DF8[] = "__OTR__ast_katina/ast_katina_seg6_vtx_10DF8";

static const ALIGN_ASSET(2) char ast_katina_seg6_vtx_10F98[] = "__OTR__ast_katina/ast_katina_seg6_vtx_10F98";

static const ALIGN_ASSET(2) char D_KA_6011000[] = "__OTR__ast_katina/D_KA_6011000";

static const ALIGN_ASSET(2) char D_KA_6011044[] = "__OTR__ast_katina/D_KA_6011044";

static const ALIGN_ASSET(2) char aKaSaucererHitbox[] = "__OTR__ast_katina/aKaSaucererHitbox";

static const ALIGN_ASSET(2) char aKaFrontlineBaseHitbox[] = "__OTR__ast_katina/aKaFrontlineBaseHitbox";

static const ALIGN_ASSET(2) char D_KA_60111D8[] = "__OTR__ast_katina/D_KA_60111D8";

