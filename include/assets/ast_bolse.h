#pragma once

#include "gfx.h"
#include "sf64object.h"
#include "sf64level.h"
#include "sf64event.h"
#include "sf64player.h"
#include "sf64audio_external.h"
#include "sf64mesg.h"

static const ALIGN_ASSET(2) char aBoTitleCardTex[] = "__OTR__ast_bolse/aBoTitleCardTex";

static const ALIGN_ASSET(2) char D_BO_6000C80[] = "__OTR__ast_bolse/D_BO_6000C80";

static const ALIGN_ASSET(2) char D_BO_6000D80[] = "__OTR__ast_bolse/D_BO_6000D80";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_F38[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_F38";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_1138[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_1138";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_1318[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_1318";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_1508[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_1508";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_16E8[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_16E8";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_18C8[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_18C8";

static const ALIGN_ASSET(2) char D_BO_6001908[] = "__OTR__ast_bolse/D_BO_6001908";

static const ALIGN_ASSET(2) char aBoBaseCoreAnim[] = "__OTR__ast_bolse/aBoBaseCoreAnim";

static const ALIGN_ASSET(2) char aBoBaseCoreSkel[] = "__OTR__ast_bolse/aBoBaseCoreSkel";

static const ALIGN_ASSET(2) char D_BO_6002020[] = "__OTR__ast_bolse/D_BO_6002020";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_2608[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_2608";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_2788[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_2788";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_2958[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_2958";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_2B58[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_2B58";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_2D38[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_2D38";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_2F18[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_2F18";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_3108[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_3108";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_32F8[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_32F8";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_34E8[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_34E8";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_3518[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_3518";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_36F8[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_36F8";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_38D8[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_38D8";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_3AD8[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_3AD8";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_3CD8[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_3CD8";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_3ED8[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_3ED8";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_40D8[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_40D8";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_42C8[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_42C8";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_44C8[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_44C8";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_46A8[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_46A8";

static const ALIGN_ASSET(2) char D_BO_6004848[] = "__OTR__ast_bolse/D_BO_6004848";

static const ALIGN_ASSET(2) char D_BO_6005048[] = "__OTR__ast_bolse/D_BO_6005048";

static const ALIGN_ASSET(2) char ast_bolse_seg6_gfx_5450[] = "__OTR__ast_bolse/ast_bolse_seg6_gfx_5450";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_5538[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_5538";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_5708[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_5708";

static const ALIGN_ASSET(2) char D_BO_6005908[] = "__OTR__ast_bolse/D_BO_6005908";

static const ALIGN_ASSET(2) char D_BO_6006108[] = "__OTR__ast_bolse/D_BO_6006108";

static const ALIGN_ASSET(2) char D_BO_6006910[] = "__OTR__ast_bolse/D_BO_6006910";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_6990[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_6990";

static const ALIGN_ASSET(2) char D_BO_6006AD0[] = "__OTR__ast_bolse/D_BO_6006AD0";

static const ALIGN_ASSET(2) char D_BO_6006ED0[] = "__OTR__ast_bolse/D_BO_6006ED0";

static const ALIGN_ASSET(2) char D_BO_6006F50[] = "__OTR__ast_bolse/D_BO_6006F50";

static const ALIGN_ASSET(2) char D_BO_6006FD0[] = "__OTR__ast_bolse/D_BO_6006FD0";

static const ALIGN_ASSET(2) char D_BO_60077D0[] = "__OTR__ast_bolse/D_BO_60077D0";

static const ALIGN_ASSET(2) char D_BO_6007BD0[] = "__OTR__ast_bolse/D_BO_6007BD0";

static const ALIGN_ASSET(2) char ast_bolse_seg6_gfx_7C50[] = "__OTR__ast_bolse/ast_bolse_seg6_gfx_7C50";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_7D08[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_7D08";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_7DC8[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_7DC8";

static const ALIGN_ASSET(2) char D_BO_6007DF8[] = "__OTR__ast_bolse/D_BO_6007DF8";

static const ALIGN_ASSET(2) char ast_bolse_seg6_gfx_8200[] = "__OTR__ast_bolse/ast_bolse_seg6_gfx_8200";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_82C0[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_82C0";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_8400[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_8400";

static const ALIGN_ASSET(2) char D_BO_6008440[] = "__OTR__ast_bolse/D_BO_6008440";

static const ALIGN_ASSET(2) char D_BO_6008668[] = "__OTR__ast_bolse/D_BO_6008668";

static const ALIGN_ASSET(2) char D_BO_60086B4[] = "__OTR__ast_bolse/D_BO_60086B4";

static const ALIGN_ASSET(2) char D_BO_60086F4[] = "__OTR__ast_bolse/D_BO_60086F4";

static const ALIGN_ASSET(2) char D_BO_6008760[] = "__OTR__ast_bolse/D_BO_6008760";

static const ALIGN_ASSET(2) char D_BO_6008770[] = "__OTR__ast_bolse/D_BO_6008770";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_88C8[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_88C8";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_8978[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_8978";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_8A48[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_8A48";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_8B58[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_8B58";

static const ALIGN_ASSET(2) char D_BO_6008BB8[] = "__OTR__ast_bolse/D_BO_6008BB8";

static const ALIGN_ASSET(2) char D_BO_60093B8[] = "__OTR__ast_bolse/D_BO_60093B8";

static const ALIGN_ASSET(2) char D_BO_6009BC0[] = "__OTR__ast_bolse/D_BO_6009BC0";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_9C68[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_9C68";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_9D68[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_9D68";

static const ALIGN_ASSET(2) char ast_bolse_seg6_gfx_9DB0[] = "__OTR__ast_bolse/ast_bolse_seg6_gfx_9DB0";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_9E20[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_9E20";

static const ALIGN_ASSET(2) char ast_bolse_seg6_gfx_9F20[] = "__OTR__ast_bolse/ast_bolse_seg6_gfx_9F20";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_9F78[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_9F78";

static const ALIGN_ASSET(2) char ast_bolse_seg6_gfx_9FC0[] = "__OTR__ast_bolse/ast_bolse_seg6_gfx_9FC0";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_A0D8[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_A0D8";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_A258[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_A258";

static const ALIGN_ASSET(2) char D_BO_600A2C0[] = "__OTR__ast_bolse/D_BO_600A2C0";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_A3D8[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_A3D8";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_A558[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_A558";

static const ALIGN_ASSET(2) char ast_bolse_seg6_gfx_A5C0[] = "__OTR__ast_bolse/ast_bolse_seg6_gfx_A5C0";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_A680[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_A680";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_A7C0[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_A7C0";

static const ALIGN_ASSET(2) char D_BO_600A810[] = "__OTR__ast_bolse/D_BO_600A810";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_A910[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_A910";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_AA90[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_AA90";

static const ALIGN_ASSET(2) char D_BO_600AB90[] = "__OTR__ast_bolse/D_BO_600AB90";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_AC40[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_AC40";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_AC80[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_AC80";

static const ALIGN_ASSET(2) char D_BO_600AD80[] = "__OTR__ast_bolse/D_BO_600AD80";

static const ALIGN_ASSET(2) char ast_bolse_seg6_gfx_B580[] = "__OTR__ast_bolse/ast_bolse_seg6_gfx_B580";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_B698[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_B698";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_B708[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_B708";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_B848[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_B848";

static const ALIGN_ASSET(2) char aBoBuildingDL[] = "__OTR__ast_bolse/aBoBuildingDL";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_B960[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_B960";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_B9A0[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_B9A0";

static const ALIGN_ASSET(2) char D_BO_600BAA0[] = "__OTR__ast_bolse/D_BO_600BAA0";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_BC00[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_BC00";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_BC80[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_BC80";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_BD80[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_BD80";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_BDC0[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_BDC0";

static const ALIGN_ASSET(2) char D_BO_600BEC0[] = "__OTR__ast_bolse/D_BO_600BEC0";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_BEF0[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_BEF0";

static const ALIGN_ASSET(2) char D_BO_600BF30[] = "__OTR__ast_bolse/D_BO_600BF30";

static const ALIGN_ASSET(2) char D_BO_600C0B8[] = "__OTR__ast_bolse/D_BO_600C0B8";

static const ALIGN_ASSET(2) char D_BO_600C2D8[] = "__OTR__ast_bolse/D_BO_600C2D8";

static const ALIGN_ASSET(2) char aBoBaseShieldDL[] = "__OTR__ast_bolse/aBoBaseShieldDL";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_C638[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_C638";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_C828[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_C828";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_CA28[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_CA28";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_CC08[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_CC08";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_CE08[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_CE08";

static const ALIGN_ASSET(2) char aBoBaseShieldTex[] = "__OTR__ast_bolse/aBoBaseShieldTex";

static const ALIGN_ASSET(2) char D_BO_600D190[] = "__OTR__ast_bolse/D_BO_600D190";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_D220[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_D220";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_D260[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_D260";

static const ALIGN_ASSET(2) char D_BO_600D2A0[] = "__OTR__ast_bolse/D_BO_600D2A0";

static const ALIGN_ASSET(2) char D_BO_600E2A0[] = "__OTR__ast_bolse/D_BO_600E2A0";

static const ALIGN_ASSET(2) char aBoLaserCannonAnim[] = "__OTR__ast_bolse/aBoLaserCannonAnim";

static const ALIGN_ASSET(2) char aBoLaserCannonSkel[] = "__OTR__ast_bolse/aBoLaserCannonSkel";

static const ALIGN_ASSET(2) char aBoShieldReactorAnim[] = "__OTR__ast_bolse/aBoShieldReactorAnim";

static const ALIGN_ASSET(2) char aBoShieldReactorSkel[] = "__OTR__ast_bolse/aBoShieldReactorSkel";

static const ALIGN_ASSET(2) char aBoPoleDL[] = "__OTR__ast_bolse/aBoPoleDL";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_F578[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_F578";

static const ALIGN_ASSET(2) char ast_bolse_seg6_vtx_F668[] = "__OTR__ast_bolse/ast_bolse_seg6_vtx_F668";

static const ALIGN_ASSET(2) char D_BO_600F728[] = "__OTR__ast_bolse/D_BO_600F728";

static const ALIGN_ASSET(2) char D_BO_600FF30[] = "__OTR__ast_bolse/D_BO_600FF30";

static const ALIGN_ASSET(2) char D_BO_600FF74[] = "__OTR__ast_bolse/D_BO_600FF74";

static const ALIGN_ASSET(2) char D_BO_6010294[] = "__OTR__ast_bolse/D_BO_6010294";

static const ALIGN_ASSET(2) char D_BO_601170C[] = "__OTR__ast_bolse/D_BO_601170C";

static const ALIGN_ASSET(2) char D_BO_6011B20[] = "__OTR__ast_bolse/D_BO_6011B20";

static const ALIGN_ASSET(2) char aBoShieldReactorHitbox[] = "__OTR__ast_bolse/aBoShieldReactorHitbox";

static const ALIGN_ASSET(2) char D_BO_6011BA4[] = "__OTR__ast_bolse/D_BO_6011BA4";

static const ALIGN_ASSET(2) char aBoLaserCannonHitbox[] = "__OTR__ast_bolse/aBoLaserCannonHitbox";

static const ALIGN_ASSET(2) char aBoPoleHitbox[] = "__OTR__ast_bolse/aBoPoleHitbox";

static const ALIGN_ASSET(2) char aBoBuildingHitbox[] = "__OTR__ast_bolse/aBoBuildingHitbox";

static const ALIGN_ASSET(2) char aBoBaseCoreHitbox[] = "__OTR__ast_bolse/aBoBaseCoreHitbox";

static const ALIGN_ASSET(2) char D_BO_6011E28[] = "__OTR__ast_bolse/D_BO_6011E28";

