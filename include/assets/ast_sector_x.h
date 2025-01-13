#pragma once

#include "gfx.h"
#include "sf64object.h"
#include "sf64level.h"
#include "sf64event.h"
#include "sf64player.h"
#include "sf64audio_external.h"
#include "sf64mesg.h"

static const ALIGN_ASSET(2) char aSxTitleCardTex[] = "__OTR__ast_sector_x/aSxTitleCardTex";

static const ALIGN_ASSET(2) char aSxSpaceMineDL[] = "__OTR__ast_sector_x/aSxSpaceMineDL";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_890[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_890";

static const ALIGN_ASSET(2) char D_SX_60008C0[] = "__OTR__ast_sector_x/D_SX_60008C0";

static const ALIGN_ASSET(2) char D_SX_60010C0[] = "__OTR__ast_sector_x/D_SX_60010C0";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_1110[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_1110";

static const ALIGN_ASSET(2) char D_SX_6001150[] = "__OTR__ast_sector_x/D_SX_6001150";

static const ALIGN_ASSET(2) char aSxLaserDestroyedDL[] = "__OTR__ast_sector_x/aSxLaserDestroyedDL";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_19B8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_19B8";

static const ALIGN_ASSET(2) char D_SX_6001AD8[] = "__OTR__ast_sector_x/D_SX_6001AD8";

static const ALIGN_ASSET(2) char aSxWatchPostDL[] = "__OTR__ast_sector_x/aSxWatchPostDL";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_1E40[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_1E40";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_1E80[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_1E80";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_1FB0[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_1FB0";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_2090[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_2090";

static const ALIGN_ASSET(2) char D_SX_60020C0[] = "__OTR__ast_sector_x/D_SX_60020C0";

static const ALIGN_ASSET(2) char D_SX_60022C0[] = "__OTR__ast_sector_x/D_SX_60022C0";

static const ALIGN_ASSET(2) char D_SX_60024C0[] = "__OTR__ast_sector_x/D_SX_60024C0";

static const ALIGN_ASSET(2) char D_SX_60026C0[] = "__OTR__ast_sector_x/D_SX_60026C0";

static const ALIGN_ASSET(2) char D_SX_60028C0[] = "__OTR__ast_sector_x/D_SX_60028C0";

static const ALIGN_ASSET(2) char D_SX_6002AC0[] = "__OTR__ast_sector_x/D_SX_6002AC0";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_2E88[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_2E88";

static const ALIGN_ASSET(2) char D_SX_60036E8[] = "__OTR__ast_sector_x/D_SX_60036E8";

static const ALIGN_ASSET(2) char D_SX_6003EE8[] = "__OTR__ast_sector_x/D_SX_6003EE8";

static const ALIGN_ASSET(2) char D_SX_60046E8[] = "__OTR__ast_sector_x/D_SX_60046E8";

static const ALIGN_ASSET(2) char D_SX_6004EE8[] = "__OTR__ast_sector_x/D_SX_6004EE8";

static const ALIGN_ASSET(2) char D_SX_6005EE8[] = "__OTR__ast_sector_x/D_SX_6005EE8";

static const ALIGN_ASSET(2) char aSxLaserDL[] = "__OTR__ast_sector_x/aSxLaserDL";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_6760[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_6760";

static const ALIGN_ASSET(2) char D_SX_6006810[] = "__OTR__ast_sector_x/D_SX_6006810";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_6A38[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_6A38";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_6B18[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_6B18";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_6C18[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_6C18";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_6C58[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_6C58";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_6DF8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_6DF8";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_6FF8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_6FF8";

static const ALIGN_ASSET(2) char D_SX_6007128[] = "__OTR__ast_sector_x/D_SX_6007128";

static const ALIGN_ASSET(2) char D_SX_6007928[] = "__OTR__ast_sector_x/D_SX_6007928";

static const ALIGN_ASSET(2) char D_SX_6008128[] = "__OTR__ast_sector_x/D_SX_6008128";

static const ALIGN_ASSET(2) char D_SX_6008928[] = "__OTR__ast_sector_x/D_SX_6008928";

static const ALIGN_ASSET(2) char D_SX_6008B30[] = "__OTR__ast_sector_x/D_SX_6008B30";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_8E28[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_8E28";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_8F18[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_8F18";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_8F98[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_8F98";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_9188[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_9188";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_9378[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_9378";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_93F8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_93F8";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_9468[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_9468";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_94E8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_94E8";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_9518[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_9518";

static const ALIGN_ASSET(2) char D_SX_6009548[] = "__OTR__ast_sector_x/D_SX_6009548";

static const ALIGN_ASSET(2) char D_SX_6009748[] = "__OTR__ast_sector_x/D_SX_6009748";

static const ALIGN_ASSET(2) char aSxBaseFloor1DL[] = "__OTR__ast_sector_x/aSxBaseFloor1DL";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_9AA8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_9AA8";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_9B28[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_9B28";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_9B68[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_9B68";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_9BE8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_9BE8";

static const ALIGN_ASSET(2) char D_SX_6009C30[] = "__OTR__ast_sector_x/D_SX_6009C30";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_9C80[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_9C80";

static const ALIGN_ASSET(2) char D_SX_6009CC0[] = "__OTR__ast_sector_x/D_SX_6009CC0";

static const ALIGN_ASSET(2) char D_SX_6009FF8[] = "__OTR__ast_sector_x/D_SX_6009FF8";

static const ALIGN_ASSET(2) char D_SX_600A2D4[] = "__OTR__ast_sector_x/D_SX_600A2D4";

static const ALIGN_ASSET(2) char aSxBaseWall3DL[] = "__OTR__ast_sector_x/aSxBaseWall3DL";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_A3F0[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_A3F0";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_A430[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_A430";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_A530[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_A530";

static const ALIGN_ASSET(2) char D_SX_600A570[] = "__OTR__ast_sector_x/D_SX_600A570";

static const ALIGN_ASSET(2) char D_SX_600AD70[] = "__OTR__ast_sector_x/D_SX_600AD70";

static const ALIGN_ASSET(2) char aSxBaseWall1DL[] = "__OTR__ast_sector_x/aSxBaseWall1DL";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_B088[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_B088";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_B0C8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_B0C8";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_B118[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_B118";

static const ALIGN_ASSET(2) char aSxBaseWall2DL[] = "__OTR__ast_sector_x/aSxBaseWall2DL";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_B3C0[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_B3C0";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_B400[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_B400";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_B500[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_B500";

static const ALIGN_ASSET(2) char aSxBaseWall4DL[] = "__OTR__ast_sector_x/aSxBaseWall4DL";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_B6C8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_B6C8";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_B6F8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_B6F8";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_B778[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_B778";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_B7A8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_B7A8";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_B7E8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_B7E8";

static const ALIGN_ASSET(2) char aSxBorzoiFighterDL[] = "__OTR__ast_sector_x/aSxBorzoiFighterDL";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_BA30[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_BA30";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_BC10[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_BC10";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_BD10[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_BD10";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_BD60[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_BD60";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_BDC0[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_BDC0";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_BE90[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_BE90";

static const ALIGN_ASSET(2) char D_SX_600C000[] = "__OTR__ast_sector_x/D_SX_600C000";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_C1B0[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_C1B0";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_C380[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_C380";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_C3C0[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_C3C0";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_C4E0[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_C4E0";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_C550[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_C550";

static const ALIGN_ASSET(2) char D_SX_600C5A0[] = "__OTR__ast_sector_x/D_SX_600C5A0";

static const ALIGN_ASSET(2) char D_SX_600F890[] = "__OTR__ast_sector_x/D_SX_600F890";

static const ALIGN_ASSET(2) char D_SX_600F8A0[] = "__OTR__ast_sector_x/D_SX_600F8A0";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_F8F8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_F8F8";

static const ALIGN_ASSET(2) char D_SX_600F938[] = "__OTR__ast_sector_x/D_SX_600F938";

static const ALIGN_ASSET(2) char D_SX_6010140[] = "__OTR__ast_sector_x/D_SX_6010140";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_10220[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_10220";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_10330[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_10330";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_gfx_103B0[] = "__OTR__ast_sector_x/ast_sector_x_seg6_gfx_103B0";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_10470[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_10470";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_10560[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_10560";

static const ALIGN_ASSET(2) char D_SX_60105A0[] = "__OTR__ast_sector_x/D_SX_60105A0";

static const ALIGN_ASSET(2) char D_SX_60123BC[] = "__OTR__ast_sector_x/D_SX_60123BC";

static const ALIGN_ASSET(2) char D_SX_6013798[] = "__OTR__ast_sector_x/D_SX_6013798";

static const ALIGN_ASSET(2) char D_SX_6013820[] = "__OTR__ast_sector_x/D_SX_6013820";

static const ALIGN_ASSET(2) char D_SX_601390C[] = "__OTR__ast_sector_x/D_SX_601390C";

static const ALIGN_ASSET(2) char D_SX_60158C4[] = "__OTR__ast_sector_x/D_SX_60158C4";

static const ALIGN_ASSET(2) char D_SX_6016E28[] = "__OTR__ast_sector_x/D_SX_6016E28";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_gfx_16E40[] = "__OTR__ast_sector_x/ast_sector_x_seg6_gfx_16E40";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_16F78[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_16F78";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_17138[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_17138";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_171B8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_171B8";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_gfx_17240[] = "__OTR__ast_sector_x/ast_sector_x_seg6_gfx_17240";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_17330[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_17330";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_17470[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_17470";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_gfx_17570[] = "__OTR__ast_sector_x/ast_sector_x_seg6_gfx_17570";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_176F0[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_176F0";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_177B0[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_177B0";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_17880[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_17880";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_178E0[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_178E0";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_gfx_17A20[] = "__OTR__ast_sector_x/ast_sector_x_seg6_gfx_17A20";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_17BC0[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_17BC0";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_17DC0[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_17DC0";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_17E40[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_17E40";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_17EA0[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_17EA0";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_gfx_18060[] = "__OTR__ast_sector_x/ast_sector_x_seg6_gfx_18060";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_18228[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_18228";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_18428[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_18428";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_184D8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_184D8";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_185F8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_185F8";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_18678[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_18678";

static const ALIGN_ASSET(2) char D_SX_601AA28[] = "__OTR__ast_sector_x/D_SX_601AA28";

static const ALIGN_ASSET(2) char D_SX_601C690[] = "__OTR__ast_sector_x/D_SX_601C690";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_gfx_1C6A0[] = "__OTR__ast_sector_x/ast_sector_x_seg6_gfx_1C6A0";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_1C7D8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_1C7D8";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_1C948[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_1C948";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_1C9C8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_1C9C8";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_gfx_1CA50[] = "__OTR__ast_sector_x/ast_sector_x_seg6_gfx_1CA50";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_1CB38[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_1CB38";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_1CC78[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_1CC78";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_gfx_1CD80[] = "__OTR__ast_sector_x/ast_sector_x_seg6_gfx_1CD80";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_1CF00[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_1CF00";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_1CFD0[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_1CFD0";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_1D0D0[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_1D0D0";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_1D130[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_1D130";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_gfx_1D260[] = "__OTR__ast_sector_x/ast_sector_x_seg6_gfx_1D260";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_1D400[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_1D400";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_1D5E0[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_1D5E0";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_1D690[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_1D690";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_1D6F0[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_1D6F0";

static const ALIGN_ASSET(2) char D_SX_60206DC[] = "__OTR__ast_sector_x/D_SX_60206DC";

static const ALIGN_ASSET(2) char aSxSpyborgSkel[] = "__OTR__ast_sector_x/aSxSpyborgSkel";

static const ALIGN_ASSET(2) char aSxBaseWallTile1DL[] = "__OTR__ast_sector_x/aSxBaseWallTile1DL";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_20E30[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_20E30";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_20E70[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_20E70";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_20F70[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_20F70";

static const ALIGN_ASSET(2) char D_SX_6020FB0[] = "__OTR__ast_sector_x/D_SX_6020FB0";

static const ALIGN_ASSET(2) char D_SX_6021ED0[] = "__OTR__ast_sector_x/D_SX_6021ED0";

static const ALIGN_ASSET(2) char aSxCanineDL[] = "__OTR__ast_sector_x/aSxCanineDL";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_23028[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_23028";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_23068[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_23068";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_230B8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_230B8";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_23188[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_23188";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_231C8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_231C8";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_23268[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_23268";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_232C8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_232C8";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_23378[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_23378";

static const ALIGN_ASSET(2) char aSxSpyEyeDL[] = "__OTR__ast_sector_x/aSxSpyEyeDL";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_236D0[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_236D0";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_23790[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_23790";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_23860[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_23860";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_23960[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_23960";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_23B20[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_23B20";

static const ALIGN_ASSET(2) char D_SX_6023C30[] = "__OTR__ast_sector_x/D_SX_6023C30";

static const ALIGN_ASSET(2) char aSxBaseDebris2DL[] = "__OTR__ast_sector_x/aSxBaseDebris2DL";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_23EB0[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_23EB0";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_gfx_24030[] = "__OTR__ast_sector_x/ast_sector_x_seg6_gfx_24030";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_24168[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_24168";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_242E8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_242E8";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_24368[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_24368";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_gfx_243F0[] = "__OTR__ast_sector_x/ast_sector_x_seg6_gfx_243F0";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_24528[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_24528";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_246A8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_246A8";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_24728[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_24728";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_gfx_247B0[] = "__OTR__ast_sector_x/ast_sector_x_seg6_gfx_247B0";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_248E8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_248E8";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_24A78[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_24A78";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_24AF8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_24AF8";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_gfx_24B80[] = "__OTR__ast_sector_x/ast_sector_x_seg6_gfx_24B80";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_24CB8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_24CB8";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_24E58[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_24E58";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_24ED8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_24ED8";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_gfx_24F60[] = "__OTR__ast_sector_x/ast_sector_x_seg6_gfx_24F60";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_25098[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_25098";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_25248[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_25248";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_252C8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_252C8";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_gfx_25350[] = "__OTR__ast_sector_x/ast_sector_x_seg6_gfx_25350";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_25488[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_25488";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_25628[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_25628";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_256A8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_256A8";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_gfx_25730[] = "__OTR__ast_sector_x/ast_sector_x_seg6_gfx_25730";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_25868[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_25868";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_25A08[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_25A08";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_25A88[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_25A88";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_gfx_25B10[] = "__OTR__ast_sector_x/ast_sector_x_seg6_gfx_25B10";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_25C48[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_25C48";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_25DE8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_25DE8";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_25E68[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_25E68";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_gfx_25EF0[] = "__OTR__ast_sector_x/ast_sector_x_seg6_gfx_25EF0";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_26028[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_26028";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_261B8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_261B8";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_26238[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_26238";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_gfx_262C0[] = "__OTR__ast_sector_x/ast_sector_x_seg6_gfx_262C0";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_263F8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_263F8";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_265A8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_265A8";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_26628[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_26628";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_gfx_266B0[] = "__OTR__ast_sector_x/ast_sector_x_seg6_gfx_266B0";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_267E8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_267E8";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_26998[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_26998";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_26A18[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_26A18";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_gfx_26AA0[] = "__OTR__ast_sector_x/ast_sector_x_seg6_gfx_26AA0";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_26BD8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_26BD8";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_26D88[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_26D88";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_26E08[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_26E08";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_gfx_26E90[] = "__OTR__ast_sector_x/ast_sector_x_seg6_gfx_26E90";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_26FC8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_26FC8";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_27178[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_27178";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_271F8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_271F8";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_gfx_27280[] = "__OTR__ast_sector_x/ast_sector_x_seg6_gfx_27280";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_273B8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_273B8";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_27558[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_27558";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_275D8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_275D8";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_gfx_27660[] = "__OTR__ast_sector_x/ast_sector_x_seg6_gfx_27660";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_27798[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_27798";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_27908[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_27908";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_27988[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_27988";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_gfx_27A10[] = "__OTR__ast_sector_x/ast_sector_x_seg6_gfx_27A10";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_27B48[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_27B48";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_27CE8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_27CE8";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_27D68[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_27D68";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_gfx_27DF0[] = "__OTR__ast_sector_x/ast_sector_x_seg6_gfx_27DF0";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_27F28[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_27F28";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_280B8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_280B8";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_28138[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_28138";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_gfx_281C0[] = "__OTR__ast_sector_x/ast_sector_x_seg6_gfx_281C0";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_28328[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_28328";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_284A8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_284A8";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_28528[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_28528";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_28568[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_28568";

static const ALIGN_ASSET(2) char aSxBaseDebris1DL[] = "__OTR__ast_sector_x/aSxBaseDebris1DL";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_287E8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_287E8";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_289E8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_289E8";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_28BE8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_28BE8";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_28DE8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_28DE8";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_28E68[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_28E68";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_28FD8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_28FD8";

static const ALIGN_ASSET(2) char D_SX_6029098[] = "__OTR__ast_sector_x/D_SX_6029098";

static const ALIGN_ASSET(2) char D_SX_60292A0[] = "__OTR__ast_sector_x/D_SX_60292A0";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_29380[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_29380";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_29420[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_29420";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_gfx_294D0[] = "__OTR__ast_sector_x/ast_sector_x_seg6_gfx_294D0";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_29610[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_29610";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_29710[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_29710";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_29810[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_29810";

static const ALIGN_ASSET(2) char D_SX_6029890[] = "__OTR__ast_sector_x/D_SX_6029890";

static const ALIGN_ASSET(2) char ast_sector_x_seg6_vtx_298E8[] = "__OTR__ast_sector_x/ast_sector_x_seg6_vtx_298E8";

static const ALIGN_ASSET(2) char D_SX_6029918[] = "__OTR__ast_sector_x/D_SX_6029918";

static const ALIGN_ASSET(2) char D_SX_602A120[] = "__OTR__ast_sector_x/D_SX_602A120";

static const ALIGN_ASSET(2) char D_SX_602A164[] = "__OTR__ast_sector_x/D_SX_602A164";

static const ALIGN_ASSET(2) char D_SX_602F18C[] = "__OTR__ast_sector_x/D_SX_602F18C";

static const char D_SX_60320D0[] = "__OTR__ast_sector_x/D_SX_60320D0";

static const ALIGN_ASSET(2) char D_SX_6032328[] = "__OTR__ast_sector_x/D_SX_6032328";

static const ALIGN_ASSET(2) char aSxWarpGateHitbox[] = "__OTR__ast_sector_x/aSxWarpGateHitbox";

static const ALIGN_ASSET(2) char D_SX_6032408[] = "__OTR__ast_sector_x/D_SX_6032408";

static const ALIGN_ASSET(2) char aSxSpyborgLeftArmHitbox[] = "__OTR__ast_sector_x/aSxSpyborgLeftArmHitbox";

static const ALIGN_ASSET(2) char aSxSpyborgRightArmHitbox[] = "__OTR__ast_sector_x/aSxSpyborgRightArmHitbox";

static const ALIGN_ASSET(2) char aSxSpyborgHitbox[] = "__OTR__ast_sector_x/aSxSpyborgHitbox";

static const ALIGN_ASSET(2) char D_SX_603265C[] = "__OTR__ast_sector_x/D_SX_603265C";

static const ALIGN_ASSET(2) char D_SX_6032768[] = "__OTR__ast_sector_x/D_SX_6032768";

static const ALIGN_ASSET(2) char aSxLaserHitbox[] = "__OTR__ast_sector_x/aSxLaserHitbox";

static const ALIGN_ASSET(2) char aSxBaseFloor1Hitbox[] = "__OTR__ast_sector_x/aSxBaseFloor1Hitbox";

static const ALIGN_ASSET(2) char aSxBaseWall2Hitbox[] = "__OTR__ast_sector_x/aSxBaseWall2Hitbox";

static const ALIGN_ASSET(2) char aSxBaseWall3Hitbox[] = "__OTR__ast_sector_x/aSxBaseWall3Hitbox";

static const ALIGN_ASSET(2) char aSxBaseWallTile1Hitbox[] = "__OTR__ast_sector_x/aSxBaseWallTile1Hitbox";

static const ALIGN_ASSET(2) char aSxBaseWall4Hitbox[] = "__OTR__ast_sector_x/aSxBaseWall4Hitbox";

static const ALIGN_ASSET(2) char aSxBaseWall1Hitbox[] = "__OTR__ast_sector_x/aSxBaseWall1Hitbox";

static const ALIGN_ASSET(2) char aSxWatchPostHitbox[] = "__OTR__ast_sector_x/aSxWatchPostHitbox";

static const ALIGN_ASSET(2) char aSxSpaceMineHitbox[] = "__OTR__ast_sector_x/aSxSpaceMineHitbox";

static const ALIGN_ASSET(2) char aSxBaseDebris2Hitbox[] = "__OTR__ast_sector_x/aSxBaseDebris2Hitbox";

static const ALIGN_ASSET(2) char aSxBaseDebris1Hitbox[] = "__OTR__ast_sector_x/aSxBaseDebris1Hitbox";

