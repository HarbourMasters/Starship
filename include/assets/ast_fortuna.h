#pragma once

#include "gfx.h"
#include "sf64object.h"
#include "sf64level.h"
#include "sf64event.h"
#include "sf64player.h"
#include "sf64audio_external.h"

static const ALIGN_ASSET(2) char aFoTitleCardTex[] = "__OTR__ast_fortuna/aFoTitleCardTex";

static const ALIGN_ASSET(2) char D_FO_6001260[] = "__OTR__ast_fortuna/D_FO_6001260";

static const ALIGN_ASSET(2) char D_FO_6001360[] = "__OTR__ast_fortuna/D_FO_6001360";

static const ALIGN_ASSET(2) char ast_fortuna_seg6_vtx_1490[] = "__OTR__ast_fortuna/ast_fortuna_seg6_vtx_1490";

static const ALIGN_ASSET(2) char ast_fortuna_seg6_vtx_15D0[] = "__OTR__ast_fortuna/ast_fortuna_seg6_vtx_15D0";

static const ALIGN_ASSET(2) char ast_fortuna_seg6_vtx_1790[] = "__OTR__ast_fortuna/ast_fortuna_seg6_vtx_1790";

static const ALIGN_ASSET(2) char D_FO_6001890[] = "__OTR__ast_fortuna/D_FO_6001890";

static const ALIGN_ASSET(2) char D_FO_6002090[] = "__OTR__ast_fortuna/D_FO_6002090";

static const ALIGN_ASSET(2) char D_FO_6002890[] = "__OTR__ast_fortuna/D_FO_6002890";

static const ALIGN_ASSET(2) char aFoBaseDL2[] = "__OTR__ast_fortuna/aFoBaseDL2";

static const ALIGN_ASSET(2) char ast_fortuna_seg6_vtx_33B0[] = "__OTR__ast_fortuna/ast_fortuna_seg6_vtx_33B0";

static const ALIGN_ASSET(2) char ast_fortuna_seg6_vtx_3520[] = "__OTR__ast_fortuna/ast_fortuna_seg6_vtx_3520";

static const ALIGN_ASSET(2) char ast_fortuna_seg6_vtx_3710[] = "__OTR__ast_fortuna/ast_fortuna_seg6_vtx_3710";

static const ALIGN_ASSET(2) char ast_fortuna_seg6_vtx_3900[] = "__OTR__ast_fortuna/ast_fortuna_seg6_vtx_3900";

static const ALIGN_ASSET(2) char ast_fortuna_seg6_vtx_3A30[] = "__OTR__ast_fortuna/ast_fortuna_seg6_vtx_3A30";

static const ALIGN_ASSET(2) char ast_fortuna_seg6_vtx_3B30[] = "__OTR__ast_fortuna/ast_fortuna_seg6_vtx_3B30";

static const ALIGN_ASSET(2) char ast_fortuna_seg6_vtx_3D20[] = "__OTR__ast_fortuna/ast_fortuna_seg6_vtx_3D20";

static const ALIGN_ASSET(2) char ast_fortuna_seg6_vtx_3E00[] = "__OTR__ast_fortuna/ast_fortuna_seg6_vtx_3E00";

static const ALIGN_ASSET(2) char D_FO_6003EC0[] = "__OTR__ast_fortuna/D_FO_6003EC0";

static const ALIGN_ASSET(2) char D_FO_60046C0[] = "__OTR__ast_fortuna/D_FO_60046C0";

static const ALIGN_ASSET(2) char D_FO_60048C0[] = "__OTR__ast_fortuna/D_FO_60048C0";

static const ALIGN_ASSET(2) char D_FO_6004AC0[] = "__OTR__ast_fortuna/D_FO_6004AC0";

static const ALIGN_ASSET(2) char D_FO_6005AC0[] = "__OTR__ast_fortuna/D_FO_6005AC0";

static const ALIGN_ASSET(2) char D_FO_6005CC0[] = "__OTR__ast_fortuna/D_FO_6005CC0";

static const ALIGN_ASSET(2) char ast_fortuna_seg6_vtx_5DC0[] = "__OTR__ast_fortuna/ast_fortuna_seg6_vtx_5DC0";

static const ALIGN_ASSET(2) char ast_fortuna_seg6_vtx_5E20[] = "__OTR__ast_fortuna/ast_fortuna_seg6_vtx_5E20";

static const ALIGN_ASSET(2) char D_FO_6005F20[] = "__OTR__ast_fortuna/D_FO_6005F20";

static const ALIGN_ASSET(2) char D_FO_6006120[] = "__OTR__ast_fortuna/D_FO_6006120";

static const ALIGN_ASSET(2) char D_FO_6006220[] = "__OTR__ast_fortuna/D_FO_6006220";

static const ALIGN_ASSET(2) char aFoMountain3DL[] = "__OTR__ast_fortuna/aFoMountain3DL";

static const ALIGN_ASSET(2) char ast_fortuna_seg6_vtx_63B8[] = "__OTR__ast_fortuna/ast_fortuna_seg6_vtx_63B8";

static const ALIGN_ASSET(2) char ast_fortuna_seg6_vtx_65B8[] = "__OTR__ast_fortuna/ast_fortuna_seg6_vtx_65B8";

static const ALIGN_ASSET(2) char aFoTowerDL[] = "__OTR__ast_fortuna/aFoTowerDL";

static const ALIGN_ASSET(2) char ast_fortuna_seg6_vtx_6898[] = "__OTR__ast_fortuna/ast_fortuna_seg6_vtx_6898";

static const ALIGN_ASSET(2) char D_FO_6006BE0[] = "__OTR__ast_fortuna/D_FO_6006BE0";

static const ALIGN_ASSET(2) char ast_fortuna_seg6_vtx_6D00[] = "__OTR__ast_fortuna/ast_fortuna_seg6_vtx_6D00";

static const ALIGN_ASSET(2) char D_FO_60070E0[] = "__OTR__ast_fortuna/D_FO_60070E0";

static const ALIGN_ASSET(2) char D_FO_60072E0[] = "__OTR__ast_fortuna/D_FO_60072E0";

static const ALIGN_ASSET(2) char D_FO_60074E0[] = "__OTR__ast_fortuna/D_FO_60074E0";

static const ALIGN_ASSET(2) char ast_fortuna_seg6_vtx_7540[] = "__OTR__ast_fortuna/ast_fortuna_seg6_vtx_7540";

static const ALIGN_ASSET(2) char D_FO_6007590[] = "__OTR__ast_fortuna/D_FO_6007590";

static const ALIGN_ASSET(2) char ast_fortuna_seg6_vtx_7648[] = "__OTR__ast_fortuna/ast_fortuna_seg6_vtx_7648";

static const ALIGN_ASSET(2) char ast_fortuna_seg6_vtx_76B8[] = "__OTR__ast_fortuna/ast_fortuna_seg6_vtx_76B8";

static const ALIGN_ASSET(2) char D_FO_6007730[] = "__OTR__ast_fortuna/D_FO_6007730";

static const ALIGN_ASSET(2) char ast_fortuna_seg6_vtx_7788[] = "__OTR__ast_fortuna/ast_fortuna_seg6_vtx_7788";

static const ALIGN_ASSET(2) char aFoRadarAnim[] = "__OTR__ast_fortuna/aFoRadarAnim";

static const ALIGN_ASSET(2) char aFoRadarSkel[] = "__OTR__ast_fortuna/aFoRadarSkel";

static const ALIGN_ASSET(2) char aFoMountain1DL[] = "__OTR__ast_fortuna/aFoMountain1DL";

static const ALIGN_ASSET(2) char ast_fortuna_seg6_vtx_7A60[] = "__OTR__ast_fortuna/ast_fortuna_seg6_vtx_7A60";

static const ALIGN_ASSET(2) char ast_fortuna_seg6_vtx_7C60[] = "__OTR__ast_fortuna/ast_fortuna_seg6_vtx_7C60";

static const ALIGN_ASSET(2) char aFoMountain2DL[] = "__OTR__ast_fortuna/aFoMountain2DL";

static const ALIGN_ASSET(2) char ast_fortuna_seg6_vtx_7E30[] = "__OTR__ast_fortuna/ast_fortuna_seg6_vtx_7E30";

static const ALIGN_ASSET(2) char ast_fortuna_seg6_vtx_8030[] = "__OTR__ast_fortuna/ast_fortuna_seg6_vtx_8030";

static const ALIGN_ASSET(2) char D_FO_6008150[] = "__OTR__ast_fortuna/D_FO_6008150";

static const ALIGN_ASSET(2) char D_FO_6009070[] = "__OTR__ast_fortuna/D_FO_6009070";

static const ALIGN_ASSET(2) char aFoEnemyShadowDL[] = "__OTR__ast_fortuna/aFoEnemyShadowDL";

static const ALIGN_ASSET(2) char ast_fortuna_seg6_vtx_9FE8[] = "__OTR__ast_fortuna/ast_fortuna_seg6_vtx_9FE8";

static const ALIGN_ASSET(2) char D_FO_600A018[] = "__OTR__ast_fortuna/D_FO_600A018";

static const ALIGN_ASSET(2) char aFoPoleDL[] = "__OTR__ast_fortuna/aFoPoleDL";

static const ALIGN_ASSET(2) char ast_fortuna_seg6_vtx_A478[] = "__OTR__ast_fortuna/ast_fortuna_seg6_vtx_A478";

static const ALIGN_ASSET(2) char D_FO_600A4A8[] = "__OTR__ast_fortuna/D_FO_600A4A8";

static const ALIGN_ASSET(2) char D_FO_600B4B0[] = "__OTR__ast_fortuna/D_FO_600B4B0";

static const ALIGN_ASSET(2) char ast_fortuna_seg6_vtx_B540[] = "__OTR__ast_fortuna/ast_fortuna_seg6_vtx_B540";

static const ALIGN_ASSET(2) char ast_fortuna_seg6_vtx_B580[] = "__OTR__ast_fortuna/ast_fortuna_seg6_vtx_B580";

static const ALIGN_ASSET(2) char D_FO_600B5C0[] = "__OTR__ast_fortuna/D_FO_600B5C0";

static const ALIGN_ASSET(2) char D_FO_600C5C0[] = "__OTR__ast_fortuna/D_FO_600C5C0";

static const ALIGN_ASSET(2) char aFoBaseDL1[] = "__OTR__ast_fortuna/aFoBaseDL1";

static const ALIGN_ASSET(2) char ast_fortuna_seg6_vtx_D638[] = "__OTR__ast_fortuna/ast_fortuna_seg6_vtx_D638";

static const ALIGN_ASSET(2) char D_FO_600D7E8[] = "__OTR__ast_fortuna/D_FO_600D7E8";

static const ALIGN_ASSET(2) char D_FO_600D9F0[] = "__OTR__ast_fortuna/D_FO_600D9F0";

static const ALIGN_ASSET(2) char ast_fortuna_seg6_vtx_DA48[] = "__OTR__ast_fortuna/ast_fortuna_seg6_vtx_DA48";

static const ALIGN_ASSET(2) char D_FO_600DA88[] = "__OTR__ast_fortuna/D_FO_600DA88";

static const ALIGN_ASSET(2) char D_FO_600EA90[] = "__OTR__ast_fortuna/D_FO_600EA90";

static const ALIGN_ASSET(2) char D_FO_600EAD4[] = "__OTR__ast_fortuna/D_FO_600EAD4";

static const ALIGN_ASSET(2) char D_FO_600F1DC[] = "__OTR__ast_fortuna/D_FO_600F1DC";

static const ALIGN_ASSET(2) char D_FO_600F394[] = "__OTR__ast_fortuna/D_FO_600F394";

static const ALIGN_ASSET(2) char D_FO_600F3F4[] = "__OTR__ast_fortuna/D_FO_600F3F4";

static const ALIGN_ASSET(2) char D_FO_600F5AC[] = "__OTR__ast_fortuna/D_FO_600F5AC";

static const ALIGN_ASSET(2) char D_FO_600F60C[] = "__OTR__ast_fortuna/D_FO_600F60C";

static const ALIGN_ASSET(2) char D_FO_600FD50[] = "__OTR__ast_fortuna/D_FO_600FD50";

static const ALIGN_ASSET(2) char aFoPoleHitbox[] = "__OTR__ast_fortuna/aFoPoleHitbox";

static const ALIGN_ASSET(2) char aFoTowerHitbox[] = "__OTR__ast_fortuna/aFoTowerHitbox";

static const ALIGN_ASSET(2) char aFoRadarHitbox[] = "__OTR__ast_fortuna/aFoRadarHitbox";

static const ALIGN_ASSET(2) char D_FO_600FF64[] = "__OTR__ast_fortuna/D_FO_600FF64";

static const ALIGN_ASSET(2) char aFoMountain1Hitbox[] = "__OTR__ast_fortuna/aFoMountain1Hitbox";

static const ALIGN_ASSET(2) char aFoMountain2Hitbox[] = "__OTR__ast_fortuna/aFoMountain2Hitbox";

static const ALIGN_ASSET(2) char aFoMountain3Hitbox[] = "__OTR__ast_fortuna/aFoMountain3Hitbox";

static const ALIGN_ASSET(2) char aFoBaseHitbox[] = "__OTR__ast_fortuna/aFoBaseHitbox";

