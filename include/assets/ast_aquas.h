#pragma once

#include "gfx.h"
#include "sf64object.h"
#include "sf64level.h"
#include "sf64event.h"
#include "sf64player.h"
#include "sf64audio_external.h"
#include "sf64mesg.h"

static const ALIGN_ASSET(2) char aAqTitleCardTex[] = "__OTR__ast_aquas/aAqTitleCardTex";

static const ALIGN_ASSET(2) char aAqSquidAnim[] = "__OTR__ast_aquas/aAqSquidAnim";

static const ALIGN_ASSET(2) char aAqSquidSkel[] = "__OTR__ast_aquas/aAqSquidSkel";

static const ALIGN_ASSET(2) char aAqShellDL[] = "__OTR__ast_aquas/aAqShellDL";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_EB0[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_EB0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_10A0[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_10A0";

static const ALIGN_ASSET(2) char D_AQ_6001130[] = "__OTR__ast_aquas/D_AQ_6001130";

static const ALIGN_ASSET(2) char aAqAnglerFishAnim[] = "__OTR__ast_aquas/aAqAnglerFishAnim";

static const ALIGN_ASSET(2) char aAqAnglerFishSkel[] = "__OTR__ast_aquas/aAqAnglerFishSkel";

static const ALIGN_ASSET(2) char ast_aquas_seg6_gfx_28C0[] = "__OTR__ast_aquas/ast_aquas_seg6_gfx_28C0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_2A38[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_2A38";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_2A98[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_2A98";

static const ALIGN_ASSET(2) char aAqOysterDL[] = "__OTR__ast_aquas/aAqOysterDL";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_2CC8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_2CC8";

static const ALIGN_ASSET(2) char D_AQ_6002D58[] = "__OTR__ast_aquas/D_AQ_6002D58";

static const ALIGN_ASSET(2) char D_AQ_6003158[] = "__OTR__ast_aquas/D_AQ_6003158";

static const ALIGN_ASSET(2) char D_AQ_6003350[] = "__OTR__ast_aquas/D_AQ_6003350";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_3430[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_3430";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_3590[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_3590";

static const ALIGN_ASSET(2) char D_AQ_6003610[] = "__OTR__ast_aquas/D_AQ_6003610";

static const ALIGN_ASSET(2) char ast_aquas_seg6_gfx_3E10[] = "__OTR__ast_aquas/ast_aquas_seg6_gfx_3E10";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_3E80[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_3E80";

static const ALIGN_ASSET(2) char D_AQ_6003FF0[] = "__OTR__ast_aquas/D_AQ_6003FF0";

static const ALIGN_ASSET(2) char D_AQ_60040F0[] = "__OTR__ast_aquas/D_AQ_60040F0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_41D0[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_41D0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_4330[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_4330";

static const ALIGN_ASSET(2) char D_AQ_60043B0[] = "__OTR__ast_aquas/D_AQ_60043B0";

static const ALIGN_ASSET(2) char D_AQ_6004BB0[] = "__OTR__ast_aquas/D_AQ_6004BB0";

static const ALIGN_ASSET(2) char D_AQ_6004DB0[] = "__OTR__ast_aquas/D_AQ_6004DB0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_4E90[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_4E90";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_4FF0[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_4FF0";

static const ALIGN_ASSET(2) char D_AQ_60050F0[] = "__OTR__ast_aquas/D_AQ_60050F0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_51A0[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_51A0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_5230[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_5230";

static const ALIGN_ASSET(2) char aAqSculpinAnim[] = "__OTR__ast_aquas/aAqSculpinAnim";

static const ALIGN_ASSET(2) char aAqSculpinSkel[] = "__OTR__ast_aquas/aAqSculpinSkel";

static const ALIGN_ASSET(2) char ast_aquas_seg6_gfx_5AB0[] = "__OTR__ast_aquas/ast_aquas_seg6_gfx_5AB0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_5C00[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_5C00";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_5C60[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_5C60";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_5CE0[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_5CE0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_5ED0[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_5ED0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_60D0[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_60D0";

static const ALIGN_ASSET(2) char D_AQ_6006160[] = "__OTR__ast_aquas/D_AQ_6006160";

static const ALIGN_ASSET(2) char D_AQ_6006960[] = "__OTR__ast_aquas/D_AQ_6006960";

static const ALIGN_ASSET(2) char D_AQ_6007160[] = "__OTR__ast_aquas/D_AQ_6007160";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_71D8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_71D8";

static const ALIGN_ASSET(2) char D_AQ_6007378[] = "__OTR__ast_aquas/D_AQ_6007378";

static const ALIGN_ASSET(2) char D_AQ_6007B80[] = "__OTR__ast_aquas/D_AQ_6007B80";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_7C08[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_7C08";

static const ALIGN_ASSET(2) char D_AQ_6007D70[] = "__OTR__ast_aquas/D_AQ_6007D70";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_7E28[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_7E28";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_7EA8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_7EA8";

static const ALIGN_ASSET(2) char D_AQ_6007F68[] = "__OTR__ast_aquas/D_AQ_6007F68";

static const ALIGN_ASSET(2) char D_AQ_6008168[] = "__OTR__ast_aquas/D_AQ_6008168";

static const ALIGN_ASSET(2) char aAqStarfishDL[] = "__OTR__ast_aquas/aAqStarfishDL";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_8AE8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_8AE8";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_8CE8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_8CE8";

static const ALIGN_ASSET(2) char D_AQ_6008EC8[] = "__OTR__ast_aquas/D_AQ_6008EC8";

static const ALIGN_ASSET(2) char D_AQ_6008FC8[] = "__OTR__ast_aquas/D_AQ_6008FC8";

static const ALIGN_ASSET(2) char D_AQ_6009188[] = "__OTR__ast_aquas/D_AQ_6009188";

static const ALIGN_ASSET(2) char D_AQ_6009990[] = "__OTR__ast_aquas/D_AQ_6009990";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_9A78[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_9A78";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_9B48[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_9B48";

static const ALIGN_ASSET(2) char D_AQ_6009C28[] = "__OTR__ast_aquas/D_AQ_6009C28";

static const ALIGN_ASSET(2) char D_AQ_600A028[] = "__OTR__ast_aquas/D_AQ_600A028";

static const ALIGN_ASSET(2) char D_AQ_600A220[] = "__OTR__ast_aquas/D_AQ_600A220";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_A298[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_A298";

static const ALIGN_ASSET(2) char D_AQ_600A480[] = "__OTR__ast_aquas/D_AQ_600A480";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_A4D8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_A4D8";

static const ALIGN_ASSET(2) char D_AQ_600A520[] = "__OTR__ast_aquas/D_AQ_600A520";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_A5D8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_A5D8";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_A658[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_A658";

static const ALIGN_ASSET(2) char D_AQ_600A720[] = "__OTR__ast_aquas/D_AQ_600A720";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_A798[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_A798";

static const ALIGN_ASSET(2) char D_AQ_600A840[] = "__OTR__ast_aquas/D_AQ_600A840";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_A898[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_A898";

static const ALIGN_ASSET(2) char D_AQ_600A8E0[] = "__OTR__ast_aquas/D_AQ_600A8E0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_A938[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_A938";

static const ALIGN_ASSET(2) char D_AQ_600A970[] = "__OTR__ast_aquas/D_AQ_600A970";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_AA20[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_AA20";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_AA80[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_AA80";

static const ALIGN_ASSET(2) char D_AQ_600AB10[] = "__OTR__ast_aquas/D_AQ_600AB10";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_AB28[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_AB28";

static const ALIGN_ASSET(2) char D_AQ_600AB68[] = "__OTR__ast_aquas/D_AQ_600AB68";

static const ALIGN_ASSET(2) char ast_aquas_seg6_gfx_B370[] = "__OTR__ast_aquas/ast_aquas_seg6_gfx_B370";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_B3C8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_B3C8";

static const ALIGN_ASSET(2) char ast_aquas_seg6_gfx_B400[] = "__OTR__ast_aquas/ast_aquas_seg6_gfx_B400";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_B488[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_B488";

static const ALIGN_ASSET(2) char D_AQ_600B518[] = "__OTR__ast_aquas/D_AQ_600B518";

static const ALIGN_ASSET(2) char D_AQ_600BD20[] = "__OTR__ast_aquas/D_AQ_600BD20";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_BD80[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_BD80";

static const ALIGN_ASSET(2) char ast_aquas_seg6_gfx_BE40[] = "__OTR__ast_aquas/ast_aquas_seg6_gfx_BE40";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_BEA0[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_BEA0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_gfx_BEF0[] = "__OTR__ast_aquas/ast_aquas_seg6_gfx_BEF0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_BF48[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_BF48";

static const ALIGN_ASSET(2) char aAqTunnel2DL[] = "__OTR__ast_aquas/aAqTunnel2DL";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_C1D0[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_C1D0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_C200[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_C200";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_C2E0[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_C2E0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_C380[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_C380";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_C450[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_C450";

static const ALIGN_ASSET(2) char D_AQ_600C530[] = "__OTR__ast_aquas/D_AQ_600C530";

static const ALIGN_ASSET(2) char D_AQ_600C930[] = "__OTR__ast_aquas/D_AQ_600C930";

static const ALIGN_ASSET(2) char D_AQ_600CB20[] = "__OTR__ast_aquas/D_AQ_600CB20";

static const ALIGN_ASSET(2) char D_AQ_600CF20[] = "__OTR__ast_aquas/D_AQ_600CF20";

static const ALIGN_ASSET(2) char D_AQ_600CFF0[] = "__OTR__ast_aquas/D_AQ_600CFF0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_D0D0[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_D0D0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_D170[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_D170";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_D360[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_D360";

static const ALIGN_ASSET(2) char D_AQ_600D390[] = "__OTR__ast_aquas/D_AQ_600D390";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_D3F0[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_D3F0";

static const ALIGN_ASSET(2) char D_AQ_600D4A0[] = "__OTR__ast_aquas/D_AQ_600D4A0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_D550[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_D550";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_D5E0[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_D5E0";

static const ALIGN_ASSET(2) char D_AQ_600D720[] = "__OTR__ast_aquas/D_AQ_600D720";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_D780[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_D780";

static const ALIGN_ASSET(2) char D_AQ_600D810[] = "__OTR__ast_aquas/D_AQ_600D810";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_D870[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_D870";

static const ALIGN_ASSET(2) char D_AQ_600D900[] = "__OTR__ast_aquas/D_AQ_600D900";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_D9A8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_D9A8";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_DA68[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_DA68";

static const ALIGN_ASSET(2) char D_AQ_600DB80[] = "__OTR__ast_aquas/D_AQ_600DB80";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_DDC8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_DDC8";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_DDF8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_DDF8";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_DE28[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_DE28";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_DE58[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_DE58";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_DE88[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_DE88";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_DEB8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_DEB8";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_DEE8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_DEE8";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_DF18[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_DF18";

static const ALIGN_ASSET(2) char D_AQ_600DF48[] = "__OTR__ast_aquas/D_AQ_600DF48";

static const ALIGN_ASSET(2) char D_AQ_600E150[] = "__OTR__ast_aquas/D_AQ_600E150";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_E1C0[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_E1C0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_gfx_E2E0[] = "__OTR__ast_aquas/ast_aquas_seg6_gfx_E2E0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_E338[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_E338";

static const ALIGN_ASSET(2) char D_AQ_600E368[] = "__OTR__ast_aquas/D_AQ_600E368";

static const ALIGN_ASSET(2) char ast_aquas_seg6_gfx_EB70[] = "__OTR__ast_aquas/ast_aquas_seg6_gfx_EB70";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_EBC8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_EBC8";

static const ALIGN_ASSET(2) char ast_aquas_seg6_gfx_EC00[] = "__OTR__ast_aquas/ast_aquas_seg6_gfx_EC00";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_EC60[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_EC60";

static const ALIGN_ASSET(2) char ast_aquas_seg6_gfx_ECB0[] = "__OTR__ast_aquas/ast_aquas_seg6_gfx_ECB0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_ED38[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_ED38";

static const ALIGN_ASSET(2) char aAqWall1DL[] = "__OTR__ast_aquas/aAqWall1DL";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_EEA8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_EEA8";

static const ALIGN_ASSET(2) char aAqBump2DL[] = "__OTR__ast_aquas/aAqBump2DL";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_EFA0[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_EFA0";

static const ALIGN_ASSET(2) char D_AQ_600F030[] = "__OTR__ast_aquas/D_AQ_600F030";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_F0A0[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_F0A0";

static const ALIGN_ASSET(2) char D_AQ_600F1A0[] = "__OTR__ast_aquas/D_AQ_600F1A0";

static const ALIGN_ASSET(2) char D_AQ_600F9A0[] = "__OTR__ast_aquas/D_AQ_600F9A0";

static const ALIGN_ASSET(2) char D_AQ_60101A0[] = "__OTR__ast_aquas/D_AQ_60101A0";

static const ALIGN_ASSET(2) char D_AQ_60109A0[] = "__OTR__ast_aquas/D_AQ_60109A0";

static const ALIGN_ASSET(2) char D_AQ_60111A0[] = "__OTR__ast_aquas/D_AQ_60111A0";

static const ALIGN_ASSET(2) char D_AQ_60119A0[] = "__OTR__ast_aquas/D_AQ_60119A0";

static const ALIGN_ASSET(2) char D_AQ_6011A78[] = "__OTR__ast_aquas/D_AQ_6011A78";

static const ALIGN_ASSET(2) char D_AQ_6011CD8[] = "__OTR__ast_aquas/D_AQ_6011CD8";

static const ALIGN_ASSET(2) char aAqTunnel1DL[] = "__OTR__ast_aquas/aAqTunnel1DL";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_11FB0[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_11FB0";

static const ALIGN_ASSET(2) char aAqRoofDL[] = "__OTR__ast_aquas/aAqRoofDL";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_12358[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_12358";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_12428[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_12428";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_12508[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_12508";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_12548[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_12548";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_12568[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_12568";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_12618[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_12618";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_12668[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_12668";

static const ALIGN_ASSET(2) char D_AQ_60126A8[] = "__OTR__ast_aquas/D_AQ_60126A8";

static const ALIGN_ASSET(2) char D_AQ_6012AA8[] = "__OTR__ast_aquas/D_AQ_6012AA8";

static const ALIGN_ASSET(2) char D_AQ_6012C98[] = "__OTR__ast_aquas/D_AQ_6012C98";

static const ALIGN_ASSET(2) char D_AQ_6012D98[] = "__OTR__ast_aquas/D_AQ_6012D98";

static const ALIGN_ASSET(2) char D_AQ_6012EA8[] = "__OTR__ast_aquas/D_AQ_6012EA8";

static const ALIGN_ASSET(2) char D_AQ_60132A8[] = "__OTR__ast_aquas/D_AQ_60132A8";

static const ALIGN_ASSET(2) char aAqFishGroupAnim[] = "__OTR__ast_aquas/aAqFishGroupAnim";

static const ALIGN_ASSET(2) char aAqFishGroupSkel1[] = "__OTR__ast_aquas/aAqFishGroupSkel1";

static const ALIGN_ASSET(2) char aAqFishGroupSkel2[] = "__OTR__ast_aquas/aAqFishGroupSkel2";

static const ALIGN_ASSET(2) char D_AQ_60137F0[] = "__OTR__ast_aquas/D_AQ_60137F0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_13960[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_13960";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_13AE0[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_13AE0";

static const ALIGN_ASSET(2) char D_AQ_6013CC0[] = "__OTR__ast_aquas/D_AQ_6013CC0";

static const ALIGN_ASSET(2) char D_AQ_6013EC0[] = "__OTR__ast_aquas/D_AQ_6013EC0";

static const ALIGN_ASSET(2) char D_AQ_6014030[] = "__OTR__ast_aquas/D_AQ_6014030";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_14180[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_14180";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_142C0[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_142C0";

static const ALIGN_ASSET(2) char aAqStoneColumnAnim[] = "__OTR__ast_aquas/aAqStoneColumnAnim";

static const ALIGN_ASSET(2) char aAqStoneColumnSkel[] = "__OTR__ast_aquas/aAqStoneColumnSkel";

static const ALIGN_ASSET(2) char D_AQ_6014520[] = "__OTR__ast_aquas/D_AQ_6014520";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_14670[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_14670";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_14730[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_14730";

static const ALIGN_ASSET(2) char D_AQ_60148B0[] = "__OTR__ast_aquas/D_AQ_60148B0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_149D8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_149D8";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_14A18[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_14A18";

static const ALIGN_ASSET(2) char ast_aquas_seg6_gfx_14B30[] = "__OTR__ast_aquas/ast_aquas_seg6_gfx_14B30";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_14BE8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_14BE8";

static const ALIGN_ASSET(2) char D_AQ_6014CD0[] = "__OTR__ast_aquas/D_AQ_6014CD0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_14D90[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_14D90";

static const ALIGN_ASSET(2) char D_AQ_6014E50[] = "__OTR__ast_aquas/D_AQ_6014E50";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_14F10[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_14F10";

static const ALIGN_ASSET(2) char aAqBoulderDL[] = "__OTR__ast_aquas/aAqBoulderDL";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_15100[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_15100";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_15300[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_15300";

static const ALIGN_ASSET(2) char D_AQ_6015430[] = "__OTR__ast_aquas/D_AQ_6015430";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_154C8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_154C8";

static const ALIGN_ASSET(2) char D_AQ_60154F8[] = "__OTR__ast_aquas/D_AQ_60154F8";

static const ALIGN_ASSET(2) char D_AQ_60155F8[] = "__OTR__ast_aquas/D_AQ_60155F8";

static const ALIGN_ASSET(2) char aAqArchDL[] = "__OTR__ast_aquas/aAqArchDL";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_15838[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_15838";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_15A28[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_15A28";

static const ALIGN_ASSET(2) char ast_aquas_seg6_gfx_15B30[] = "__OTR__ast_aquas/ast_aquas_seg6_gfx_15B30";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_15BE8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_15BE8";

static const ALIGN_ASSET(2) char ast_aquas_seg6_gfx_15C80[] = "__OTR__ast_aquas/ast_aquas_seg6_gfx_15C80";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_15D38[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_15D38";

static const ALIGN_ASSET(2) char D_AQ_6015DD0[] = "__OTR__ast_aquas/D_AQ_6015DD0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_15EF8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_15EF8";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_15F88[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_15F88";

static const ALIGN_ASSET(2) char D_AQ_6015FF0[] = "__OTR__ast_aquas/D_AQ_6015FF0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_161A8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_161A8";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_163A8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_163A8";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_164E8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_164E8";

static const ALIGN_ASSET(2) char ast_aquas_seg6_gfx_16540[] = "__OTR__ast_aquas/ast_aquas_seg6_gfx_16540";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_16640[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_16640";

static const ALIGN_ASSET(2) char ast_aquas_seg6_gfx_16790[] = "__OTR__ast_aquas/ast_aquas_seg6_gfx_16790";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_16890[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_16890";

static const ALIGN_ASSET(2) char ast_aquas_seg6_gfx_169E0[] = "__OTR__ast_aquas/ast_aquas_seg6_gfx_169E0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_16AE8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_16AE8";

static const ALIGN_ASSET(2) char ast_aquas_seg6_gfx_16C00[] = "__OTR__ast_aquas/ast_aquas_seg6_gfx_16C00";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_16D78[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_16D78";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_16E38[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_16E38";

static const ALIGN_ASSET(2) char ast_aquas_seg6_gfx_16F40[] = "__OTR__ast_aquas/ast_aquas_seg6_gfx_16F40";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_17080[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_17080";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_17110[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_17110";

static const ALIGN_ASSET(2) char ast_aquas_seg6_gfx_171A0[] = "__OTR__ast_aquas/ast_aquas_seg6_gfx_171A0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_17458[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_17458";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_175C8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_175C8";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_177A8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_177A8";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_17988[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_17988";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_17B78[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_17B78";

static const ALIGN_ASSET(2) char D_AQ_6017BD8[] = "__OTR__ast_aquas/D_AQ_6017BD8";

static const ALIGN_ASSET(2) char D_AQ_6017CD8[] = "__OTR__ast_aquas/D_AQ_6017CD8";

static const ALIGN_ASSET(2) char ast_aquas_seg6_gfx_17D60[] = "__OTR__ast_aquas/ast_aquas_seg6_gfx_17D60";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_17F70[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_17F70";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_180F0[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_180F0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_182E0[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_182E0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_184E0[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_184E0";

static const ALIGN_ASSET(2) char D_AQ_6018640[] = "__OTR__ast_aquas/D_AQ_6018640";

static const ALIGN_ASSET(2) char D_AQ_6018878[] = "__OTR__ast_aquas/D_AQ_6018878";

static const ALIGN_ASSET(2) char D_AQ_6018C78[] = "__OTR__ast_aquas/D_AQ_6018C78";

static const ALIGN_ASSET(2) char D_AQ_6019078[] = "__OTR__ast_aquas/D_AQ_6019078";

static const ALIGN_ASSET(2) char D_AQ_6019238[] = "__OTR__ast_aquas/D_AQ_6019238";

static const ALIGN_ASSET(2) char D_AQ_6019338[] = "__OTR__ast_aquas/D_AQ_6019338";

static const ALIGN_ASSET(2) char D_AQ_60194D0[] = "__OTR__ast_aquas/D_AQ_60194D0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_19648[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_19648";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_19768[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_19768";

static const ALIGN_ASSET(2) char D_AQ_6019880[] = "__OTR__ast_aquas/D_AQ_6019880";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_199F8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_199F8";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_19B18[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_19B18";

static const ALIGN_ASSET(2) char D_AQ_6019C28[] = "__OTR__ast_aquas/D_AQ_6019C28";

static const ALIGN_ASSET(2) char D_AQ_6019D28[] = "__OTR__ast_aquas/D_AQ_6019D28";

static const ALIGN_ASSET(2) char D_AQ_6019E80[] = "__OTR__ast_aquas/D_AQ_6019E80";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_1A000[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_1A000";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_1A120[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_1A120";

static const ALIGN_ASSET(2) char ast_aquas_seg6_gfx_1A230[] = "__OTR__ast_aquas/ast_aquas_seg6_gfx_1A230";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_1A2C8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_1A2C8";

static const ALIGN_ASSET(2) char D_AQ_601A308[] = "__OTR__ast_aquas/D_AQ_601A308";

static const ALIGN_ASSET(2) char D_AQ_601A708[] = "__OTR__ast_aquas/D_AQ_601A708";

static const ALIGN_ASSET(2) char ast_aquas_seg6_gfx_1A900[] = "__OTR__ast_aquas/ast_aquas_seg6_gfx_1A900";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_1A9D8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_1A9D8";

static const ALIGN_ASSET(2) char ast_aquas_seg6_gfx_1AB30[] = "__OTR__ast_aquas/ast_aquas_seg6_gfx_1AB30";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_1AC80[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_1AC80";

static const ALIGN_ASSET(2) char D_AQ_601AE70[] = "__OTR__ast_aquas/D_AQ_601AE70";

static const ALIGN_ASSET(2) char D_AQ_601AF70[] = "__OTR__ast_aquas/D_AQ_601AF70";

static const ALIGN_ASSET(2) char D_AQ_601AFF0[] = "__OTR__ast_aquas/D_AQ_601AFF0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_1B040[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_1B040";

static const ALIGN_ASSET(2) char D_AQ_601B080[] = "__OTR__ast_aquas/D_AQ_601C110";

static const ALIGN_ASSET(2) char D_AQ_601C080[] = "__OTR__ast_aquas/D_AQ_601C080";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_1C0D0[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_1C0D0";

static const ALIGN_ASSET(2) char D_AQ_601C110[] = "__OTR__ast_aquas/D_AQ_601B080";

static const ALIGN_ASSET(2) char D_AQ_601D110[] = "__OTR__ast_aquas/D_AQ_601D110";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_1D1F0[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_1D1F0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_1D3F0[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_1D3F0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_1D5E0[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_1D5E0";

static const ALIGN_ASSET(2) char D_AQ_601DE50[] = "__OTR__ast_aquas/D_AQ_601DE50";

static const ALIGN_ASSET(2) char aAqCoralReef2DL[] = "__OTR__ast_aquas/aAqCoralReef2DL";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_1DF30[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_1DF30";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_1E130[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_1E130";

static const ALIGN_ASSET(2) char D_AQ_601E1F0[] = "__OTR__ast_aquas/D_AQ_601E1F0";

static const ALIGN_ASSET(2) char D_AQ_601E9F0[] = "__OTR__ast_aquas/D_AQ_601E9F0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_1EA78[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_1EA78";

static const ALIGN_ASSET(2) char aAqCoralAnim[] = "__OTR__ast_aquas/aAqCoralAnim";

static const ALIGN_ASSET(2) char aAqCoralSkel[] = "__OTR__ast_aquas/aAqCoralSkel";

static const ALIGN_ASSET(2) char D_AQ_601EDE0[] = "__OTR__ast_aquas/D_AQ_601EDE0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_1EEB8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_1EEB8";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_1F0B8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_1F0B8";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_1F2B8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_1F2B8";

static const ALIGN_ASSET(2) char D_AQ_601F2F0[] = "__OTR__ast_aquas/D_AQ_601F2F0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_1F3C8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_1F3C8";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_1F5B8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_1F5B8";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_1F798[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_1F798";

static const ALIGN_ASSET(2) char D_AQ_601F830[] = "__OTR__ast_aquas/D_AQ_601F830";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_1F908[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_1F908";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_1FAE8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_1FAE8";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_1FCD8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_1FCD8";

static const ALIGN_ASSET(2) char D_AQ_601FD70[] = "__OTR__ast_aquas/D_AQ_601FD70";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_1FE58[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_1FE58";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_20048[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_20048";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_20248[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_20248";

static const ALIGN_ASSET(2) char aAqSeaweedAnim[] = "__OTR__ast_aquas/aAqSeaweedAnim";

static const ALIGN_ASSET(2) char aAqSeaweedSkel[] = "__OTR__ast_aquas/aAqSeaweedSkel";

static const ALIGN_ASSET(2) char ast_aquas_seg6_gfx_20CC0[] = "__OTR__ast_aquas/ast_aquas_seg6_gfx_20CC0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_20D18[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_20D18";

static const ALIGN_ASSET(2) char ast_aquas_seg6_gfx_20D50[] = "__OTR__ast_aquas/ast_aquas_seg6_gfx_20D50";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_20DA8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_20DA8";

static const ALIGN_ASSET(2) char ast_aquas_seg6_gfx_20DF0[] = "__OTR__ast_aquas/ast_aquas_seg6_gfx_20DF0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_20E48[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_20E48";

static const ALIGN_ASSET(2) char ast_aquas_seg6_gfx_20E90[] = "__OTR__ast_aquas/ast_aquas_seg6_gfx_20E90";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_20EE8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_20EE8";

static const ALIGN_ASSET(2) char ast_aquas_seg6_gfx_20F30[] = "__OTR__ast_aquas/ast_aquas_seg6_gfx_20F30";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_20F88[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_20F88";

static const ALIGN_ASSET(2) char ast_aquas_seg6_gfx_20FD0[] = "__OTR__ast_aquas/ast_aquas_seg6_gfx_20FD0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_21028[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_21028";

static const ALIGN_ASSET(2) char D_AQ_6021058[] = "__OTR__ast_aquas/D_AQ_6021058";

static const ALIGN_ASSET(2) char D_AQ_6021858[] = "__OTR__ast_aquas/D_AQ_6021858";

static const ALIGN_ASSET(2) char D_AQ_6021C58[] = "__OTR__ast_aquas/D_AQ_6021C58";

static const ALIGN_ASSET(2) char ast_aquas_seg6_gfx_21E30[] = "__OTR__ast_aquas/ast_aquas_seg6_gfx_21E30";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_21E90[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_21E90";

static const ALIGN_ASSET(2) char aAqOysterAnim[] = "__OTR__ast_aquas/aAqOysterAnim";

static const ALIGN_ASSET(2) char aAqOysterSkel[] = "__OTR__ast_aquas/aAqOysterSkel";

static const ALIGN_ASSET(2) char D_AQ_6022110[] = "__OTR__ast_aquas/D_AQ_6022110";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_22168[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_22168";

static const ALIGN_ASSET(2) char D_AQ_6022198[] = "__OTR__ast_aquas/D_AQ_6022198";

static const ALIGN_ASSET(2) char D_AQ_6022598[] = "__OTR__ast_aquas/D_AQ_6022598";

static const ALIGN_ASSET(2) char D_AQ_6022788[] = "__OTR__ast_aquas/D_AQ_6022788";

static const ALIGN_ASSET(2) char D_AQ_6022888[] = "__OTR__ast_aquas/D_AQ_6022888";

static const ALIGN_ASSET(2) char D_AQ_60229B8[] = "__OTR__ast_aquas/D_AQ_60229B8";

static const ALIGN_ASSET(2) char aAqCoralReef1DL[] = "__OTR__ast_aquas/aAqCoralReef1DL";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_23290[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_23290";

static const ALIGN_ASSET(2) char aAqJellyfishAnim[] = "__OTR__ast_aquas/aAqJellyfishAnim";

static const ALIGN_ASSET(2) char aAqJellyfishSkel[] = "__OTR__ast_aquas/aAqJellyfishSkel";

static const ALIGN_ASSET(2) char D_AQ_6023940[] = "__OTR__ast_aquas/D_AQ_6023940";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_239F0[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_239F0";

static const ALIGN_ASSET(2) char D_AQ_6023B80[] = "__OTR__ast_aquas/D_AQ_6023B80";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_23C40[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_23C40";

static const ALIGN_ASSET(2) char D_AQ_6023D70[] = "__OTR__ast_aquas/D_AQ_6023D70";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_23DE8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_23DE8";

static const ALIGN_ASSET(2) char D_AQ_6023EB0[] = "__OTR__ast_aquas/D_AQ_6023EB0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_23F08[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_23F08";

static const ALIGN_ASSET(2) char D_AQ_6023F38[] = "__OTR__ast_aquas/D_AQ_6023F38";

static const ALIGN_ASSET(2) char D_AQ_6024738[] = "__OTR__ast_aquas/D_AQ_6024738";

static const ALIGN_ASSET(2) char D_AQ_6024938[] = "__OTR__ast_aquas/D_AQ_6024938";

static const ALIGN_ASSET(2) char D_AQ_60249C0[] = "__OTR__ast_aquas/D_AQ_60249C0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_24A18[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_24A18";

static const ALIGN_ASSET(2) char aAqPearlDL[] = "__OTR__ast_aquas/aAqPearlDL";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_24AA8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_24AA8";

static const ALIGN_ASSET(2) char D_AQ_6024F80[] = "__OTR__ast_aquas/D_AQ_6024F80";

static const ALIGN_ASSET(2) char aAqGaroaSkel[] = "__OTR__ast_aquas/aAqGaroaSkel";

static const ALIGN_ASSET(2) char aAqSpindlyFishAnim[] = "__OTR__ast_aquas/aAqSpindlyFishAnim";

static const ALIGN_ASSET(2) char aAqSpindlyFishSkel[] = "__OTR__ast_aquas/aAqSpindlyFishSkel";

static const ALIGN_ASSET(2) char D_AQ_6026460[] = "__OTR__ast_aquas/D_AQ_6026460";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_26528[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_26528";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_265E8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_265E8";

static const ALIGN_ASSET(2) char D_AQ_60266B0[] = "__OTR__ast_aquas/D_AQ_60266B0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_26780[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_26780";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_26840[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_26840";

static const ALIGN_ASSET(2) char D_AQ_6026950[] = "__OTR__ast_aquas/D_AQ_6026950";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_26A20[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_26A20";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_26AE0[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_26AE0";

static const ALIGN_ASSET(2) char D_AQ_6026BF0[] = "__OTR__ast_aquas/D_AQ_6026BF0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_26C48[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_26C48";

static const ALIGN_ASSET(2) char D_AQ_6026C80[] = "__OTR__ast_aquas/D_AQ_6026C80";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_26CD8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_26CD8";

static const ALIGN_ASSET(2) char D_AQ_6026D10[] = "__OTR__ast_aquas/D_AQ_6026D10";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_26D68[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_26D68";

static const ALIGN_ASSET(2) char D_AQ_6026DA0[] = "__OTR__ast_aquas/D_AQ_6026DA0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_26DF8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_26DF8";

static const ALIGN_ASSET(2) char D_AQ_6026E30[] = "__OTR__ast_aquas/D_AQ_6026E30";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_26E88[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_26E88";

static const ALIGN_ASSET(2) char D_AQ_6026EC0[] = "__OTR__ast_aquas/D_AQ_6026EC0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_26F18[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_26F18";

static const ALIGN_ASSET(2) char D_AQ_6026F60[] = "__OTR__ast_aquas/D_AQ_6026F60";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_27090[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_27090";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_27280[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_27280";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_272E0[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_272E0";

static const ALIGN_ASSET(2) char D_AQ_6027330[] = "__OTR__ast_aquas/D_AQ_6027330";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_27388[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_27388";

static const ALIGN_ASSET(2) char D_AQ_60273C0[] = "__OTR__ast_aquas/D_AQ_60273C0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_27418[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_27418";

static const ALIGN_ASSET(2) char D_AQ_6027460[] = "__OTR__ast_aquas/D_AQ_6027460";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_27538[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_27538";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_275F8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_275F8";

static const ALIGN_ASSET(2) char D_AQ_60276F0[] = "__OTR__ast_aquas/D_AQ_60276F0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_277A0[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_277A0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_277E0[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_277E0";

static const ALIGN_ASSET(2) char D_AQ_6027810[] = "__OTR__ast_aquas/D_AQ_6027810";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_278C0[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_278C0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_27900[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_27900";

static const ALIGN_ASSET(2) char D_AQ_6027930[] = "__OTR__ast_aquas/D_AQ_6027930";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_27A18[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_27A18";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_27A78[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_27A78";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_27C58[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_27C58";

static const ALIGN_ASSET(2) char D_AQ_6027C90[] = "__OTR__ast_aquas/D_AQ_6027C90";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_27D60[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_27D60";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_27E50[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_27E50";

static const ALIGN_ASSET(2) char D_AQ_6027FA0[] = "__OTR__ast_aquas/D_AQ_6027FA0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_28068[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_28068";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_281B8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_281B8";

static const ALIGN_ASSET(2) char D_AQ_6028240[] = "__OTR__ast_aquas/D_AQ_6028240";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_28310[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_28310";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_28400[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_28400";

static const ALIGN_ASSET(2) char D_AQ_6028550[] = "__OTR__ast_aquas/D_AQ_6028550";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_28618[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_28618";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_28768[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_28768";

static const ALIGN_ASSET(2) char D_AQ_60287F0[] = "__OTR__ast_aquas/D_AQ_60287F0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_28850[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_28850";

static const ALIGN_ASSET(2) char D_AQ_6028910[] = "__OTR__ast_aquas/D_AQ_6028910";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_289C0[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_289C0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_28A20[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_28A20";

static const ALIGN_ASSET(2) char D_AQ_6028A80[] = "__OTR__ast_aquas/D_AQ_6028A80";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_28B48[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_28B48";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_28D48[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_28D48";

static const ALIGN_ASSET(2) char D_AQ_6028F50[] = "__OTR__ast_aquas/D_AQ_6028F50";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_29000[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_29000";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_29090[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_29090";

static const ALIGN_ASSET(2) char D_AQ_60290C0[] = "__OTR__ast_aquas/D_AQ_60290C0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_29120[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_29120";

static const ALIGN_ASSET(2) char D_AQ_60291B0[] = "__OTR__ast_aquas/D_AQ_60291B0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_29208[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_29208";

static const ALIGN_ASSET(2) char D_AQ_6029240[] = "__OTR__ast_aquas/D_AQ_6029240";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_292A0[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_292A0";

static const ALIGN_ASSET(2) char D_AQ_6029330[] = "__OTR__ast_aquas/D_AQ_6029330";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_293E0[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_293E0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_29470[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_29470";

static const ALIGN_ASSET(2) char D_AQ_60294A0[] = "__OTR__ast_aquas/D_AQ_60294A0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_294F8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_294F8";

static const ALIGN_ASSET(2) char D_AQ_6029530[] = "__OTR__ast_aquas/D_AQ_6029530";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_295E0[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_295E0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_29670[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_29670";

static const ALIGN_ASSET(2) char D_AQ_60296A0[] = "__OTR__ast_aquas/D_AQ_60296A0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_29700[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_29700";

static const ALIGN_ASSET(2) char D_AQ_6029790[] = "__OTR__ast_aquas/D_AQ_6029790";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_29840[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_29840";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_298D0[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_298D0";

static const ALIGN_ASSET(2) char D_AQ_6029900[] = "__OTR__ast_aquas/D_AQ_6029900";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_29960[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_29960";

static const ALIGN_ASSET(2) char D_AQ_602AC28[] = "__OTR__ast_aquas/D_AQ_602AC28";

static const ALIGN_ASSET(2) char D_AQ_602AC40[] = "__OTR__ast_aquas/D_AQ_602AC40";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_2AC60[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_2AC60";

static const ALIGN_ASSET(2) char D_AQ_602ACC0[] = "__OTR__ast_aquas/D_AQ_602ACC0";

static const ALIGN_ASSET(2) char aAqRockDL[] = "__OTR__ast_aquas/aAqRockDL";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_2B590[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_2B590";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_2B790[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_2B790";

static const ALIGN_ASSET(2) char D_AQ_602B9D4[] = "__OTR__ast_aquas/D_AQ_602B9D4";

static const ALIGN_ASSET(2) char D_AQ_602BD60[] = "__OTR__ast_aquas/D_AQ_602BD60";

static const ALIGN_ASSET(2) char D_AQ_602BF88[] = "__OTR__ast_aquas/D_AQ_602BF88";

static const ALIGN_ASSET(2) char D_AQ_602C014[] = "__OTR__ast_aquas/D_AQ_602C014";

static const ALIGN_ASSET(2) char D_AQ_602C030[] = "__OTR__ast_aquas/D_AQ_602C030";

static const ALIGN_ASSET(2) char D_AQ_602C088[] = "__OTR__ast_aquas/D_AQ_602C088";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_2C0E0[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_2C0E0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_2C120[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_2C120";

static const ALIGN_ASSET(2) char D_AQ_602C160[] = "__OTR__ast_aquas/D_AQ_602C160";

static const ALIGN_ASSET(2) char D_AQ_602C960[] = "__OTR__ast_aquas/D_AQ_602C960";

static const ALIGN_ASSET(2) char ast_aquas_seg6_gfx_2D160[] = "__OTR__ast_aquas/ast_aquas_seg6_gfx_2D160";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_2D208[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_2D208";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_2D268[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_2D268";

static const ALIGN_ASSET(2) char ast_aquas_seg6_gfx_2D2C0[] = "__OTR__ast_aquas/ast_aquas_seg6_gfx_2D2C0";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_2D4A8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_2D4A8";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_2D528[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_2D528";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_2D728[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_2D728";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_2D828[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_2D828";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_2D8A8[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_2D8A8";

static const ALIGN_ASSET(2) char D_AQ_602DA28[] = "__OTR__ast_aquas/D_AQ_602DA28";

static const ALIGN_ASSET(2) char D_AQ_602DC28[] = "__OTR__ast_aquas/D_AQ_602DC28";

static const ALIGN_ASSET(2) char D_AQ_602DE28[] = "__OTR__ast_aquas/D_AQ_602DE28";

static const ALIGN_ASSET(2) char D_AQ_602E028[] = "__OTR__ast_aquas/D_AQ_602E028";

static const ALIGN_ASSET(2) char ast_aquas_seg6_gfx_2E230[] = "__OTR__ast_aquas/ast_aquas_seg6_gfx_2E230";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_2E328[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_2E328";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_2E418[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_2E418";

static const ALIGN_ASSET(2) char ast_aquas_seg6_vtx_2E478[] = "__OTR__ast_aquas/ast_aquas_seg6_vtx_2E478";

static const ALIGN_ASSET(2) char D_AQ_602E540[] = "__OTR__ast_aquas/D_AQ_602E540";

static const ALIGN_ASSET(2) char D_AQ_602E584[] = "__OTR__ast_aquas/D_AQ_602E584";

static const ALIGN_ASSET(2) char D_AQ_602E5C8[] = "__OTR__ast_aquas/D_AQ_602E5C8";

static const char D_AQ_60308B8[] = "__OTR__ast_aquas/D_AQ_60308B8";

static const ALIGN_ASSET(2) char aBoss301Hitbox[] = "__OTR__ast_aquas/aBoss301Hitbox";

static const ALIGN_ASSET(2) char aAqShellHitbox[] = "__OTR__ast_aquas/aAqShellHitbox";

static const ALIGN_ASSET(2) char aAqStarfishHitbox[] = "__OTR__ast_aquas/aAqStarfishHitbox";

static const ALIGN_ASSET(2) char aAqOysterEvHitbox[] = "__OTR__ast_aquas/aAqOysterEvHitbox";

static const ALIGN_ASSET(2) char D_AQ_6030B68[] = "__OTR__ast_aquas/D_AQ_6030B68";

static const ALIGN_ASSET(2) char D_AQ_6030BAC[] = "__OTR__ast_aquas/D_AQ_6030BAC";

static const ALIGN_ASSET(2) char aAqActor188Hitbox[] = "__OTR__ast_aquas/aAqActor188Hitbox";

static const ALIGN_ASSET(2) char aAqActor255Hitbox[] = "__OTR__ast_aquas/aAqActor255Hitbox";

static const ALIGN_ASSET(2) char aAqActor256Hitbox[] = "__OTR__ast_aquas/aAqActor256Hitbox";

static const ALIGN_ASSET(2) char aAqActor257Hitbox[] = "__OTR__ast_aquas/aAqActor257Hitbox";

static const ALIGN_ASSET(2) char aAqCoralReef1Hitbox[] = "__OTR__ast_aquas/aAqCoralReef1Hitbox";

static const ALIGN_ASSET(2) char aAqTunnel1Hitbox[] = "__OTR__ast_aquas/aAqTunnel1Hitbox";

static const ALIGN_ASSET(2) char aAqStoneColumnHitbox[] = "__OTR__ast_aquas/aAqStoneColumnHitbox";

static const ALIGN_ASSET(2) char D_AQ_6030D3C[] = "__OTR__ast_aquas/D_AQ_6030D3C";

static const ALIGN_ASSET(2) char D_AQ_6030D58[] = "__OTR__ast_aquas/D_AQ_6030D58";

static const ALIGN_ASSET(2) char aAqArchHitbox[] = "__OTR__ast_aquas/aAqArchHitbox";

static const ALIGN_ASSET(2) char aAqCoralReef2Hitbox[] = "__OTR__ast_aquas/aAqCoralReef2Hitbox";

static const ALIGN_ASSET(2) char aAqRockHitbox[] = "__OTR__ast_aquas/aAqRockHitbox";

static const ALIGN_ASSET(2) char aAqWall1Hitbox[] = "__OTR__ast_aquas/aAqWall1Hitbox";

static const ALIGN_ASSET(2) char aAqRoofHitbox[] = "__OTR__ast_aquas/aAqRoofHitbox";

static const ALIGN_ASSET(2) char aAqTunnel2Hitbox[] = "__OTR__ast_aquas/aAqTunnel2Hitbox";

static const ALIGN_ASSET(2) char aAqBacoonHitbox[] = "__OTR__ast_aquas/aAqBacoonHitbox";

static const ALIGN_ASSET(2) char aAqAnglerFishHitbox[] = "__OTR__ast_aquas/aAqAnglerFishHitbox";

static const ALIGN_ASSET(2) char aAqGaroaHitbox[] = "__OTR__ast_aquas/aAqGaroaHitbox";

static const ALIGN_ASSET(2) char aAqSculpinHitbox[] = "__OTR__ast_aquas/aAqSculpinHitbox";

static const ALIGN_ASSET(2) char aAqSpindlyFishHitbox[] = "__OTR__ast_aquas/aAqSpindlyFishHitbox";

static const ALIGN_ASSET(2) char aAqSquidHitbox[] = "__OTR__ast_aquas/aAqSquidHitbox";

static const ALIGN_ASSET(2) char D_AQ_60314AC[] = "__OTR__ast_aquas/D_AQ_60314AC";

static const ALIGN_ASSET(2) char aAqOysterHitbox[] = "__OTR__ast_aquas/aAqOysterHitbox";

static const ALIGN_ASSET(2) char D_AQ_60314E4[] = "__OTR__ast_aquas/D_AQ_60314E4";

static const ALIGN_ASSET(2) char aAqBoulderHitbox[] = "__OTR__ast_aquas/aAqBoulderHitbox";

static const ALIGN_ASSET(2) char D_AQ_603151C[] = "__OTR__ast_aquas/D_AQ_603151C";

static const ALIGN_ASSET(2) char aAqCoralHitbox[] = "__OTR__ast_aquas/aAqCoralHitbox";

static const ALIGN_ASSET(2) char aAqJellyfishHitbox[] = "__OTR__ast_aquas/aAqJellyfishHitbox";

static const ALIGN_ASSET(2) char aAqFishGroupHitbox[] = "__OTR__ast_aquas/aAqFishGroupHitbox";

static const ALIGN_ASSET(2) char D_AQ_603158C[] = "__OTR__ast_aquas/D_AQ_603158C";

static const ALIGN_ASSET(2) char D_AQ_6031D90[] = "__OTR__ast_aquas/D_AQ_6031D90";

static const ALIGN_ASSET(2) char D_AQ_6031FB0[] = "__OTR__ast_aquas/D_AQ_6031FB0";

static const ALIGN_ASSET(2) char D_AQ_6031FE0[] = "__OTR__ast_aquas/D_AQ_6031FE0";

static const ALIGN_ASSET(2) char D_AQ_603204C[] = "__OTR__ast_aquas/D_AQ_603204C";

static const ALIGN_ASSET(2) char D_AQ_60320B8[] = "__OTR__ast_aquas/D_AQ_60320B8";

static const ALIGN_ASSET(2) char D_AQ_603216C[] = "__OTR__ast_aquas/D_AQ_603216C";

static const ALIGN_ASSET(2) char D_AQ_6032388[] = "__OTR__ast_aquas/D_AQ_6032388";

static const ALIGN_ASSET(2) char D_AQ_6032430[] = "__OTR__ast_aquas/D_AQ_6032430";

