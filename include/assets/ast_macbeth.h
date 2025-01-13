#pragma once

#include "gfx.h"
#include "sf64object.h"
#include "sf64level.h"
#include "sf64event.h"
#include "sf64player.h"
#include "sf64audio_external.h"
#include "sf64mesg.h"

static const ALIGN_ASSET(2) char aMaTitleCardTex[] = "__OTR__ast_macbeth/aMaTitleCardTex";

static const ALIGN_ASSET(2) char D_MA_6001180[] = "__OTR__ast_macbeth/D_MA_6001180";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1220[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1220";

static const ALIGN_ASSET(2) char D_MA_60012A0[] = "__OTR__ast_macbeth/D_MA_60012A0";

static const ALIGN_ASSET(2) char D_MA_60013A0[] = "__OTR__ast_macbeth/D_MA_60013A0";

static const ALIGN_ASSET(2) char D_MA_60014A0[] = "__OTR__ast_macbeth/D_MA_60014A0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1538[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1538";

static const ALIGN_ASSET(2) char D_MA_6001578[] = "__OTR__ast_macbeth/D_MA_6001578";

static const ALIGN_ASSET(2) char D_MA_6001978[] = "__OTR__ast_macbeth/D_MA_6001978";

static const ALIGN_ASSET(2) char D_MA_6001A60[] = "__OTR__ast_macbeth/D_MA_6001A60";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1AF8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1AF8";

static const ALIGN_ASSET(2) char D_MA_6001B38[] = "__OTR__ast_macbeth/D_MA_6001B38";

static const ALIGN_ASSET(2) char D_MA_6001C38[] = "__OTR__ast_macbeth/D_MA_6001C38";

static const ALIGN_ASSET(2) char D_MA_6001C78[] = "__OTR__ast_macbeth/D_MA_6001C78";

static const ALIGN_ASSET(2) char D_MA_6002078[] = "__OTR__ast_macbeth/D_MA_6002078";

static const ALIGN_ASSET(2) char D_MA_6002118[] = "__OTR__ast_macbeth/D_MA_6002118";

static const ALIGN_ASSET(2) char D_MA_6002518[] = "__OTR__ast_macbeth/D_MA_6002518";

static const ALIGN_ASSET(2) char D_MA_60026F8[] = "__OTR__ast_macbeth/D_MA_60026F8";

static const ALIGN_ASSET(2) char D_MA_60027F8[] = "__OTR__ast_macbeth/D_MA_60027F8";

static const ALIGN_ASSET(2) char aMaGuillotine2DL[] = "__OTR__ast_macbeth/aMaGuillotine2DL";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_2A40[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_2A40";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_2B40[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_2B40";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_2B80[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_2B80";

static const ALIGN_ASSET(2) char D_MA_6002C20[] = "__OTR__ast_macbeth/D_MA_6002C20";

static const ALIGN_ASSET(2) char D_MA_6002E20[] = "__OTR__ast_macbeth/D_MA_6002E20";

static const ALIGN_ASSET(2) char D_MA_6002E60[] = "__OTR__ast_macbeth/D_MA_6002E60";

static const ALIGN_ASSET(2) char D_MA_6002F60[] = "__OTR__ast_macbeth/D_MA_6002F60";

static const ALIGN_ASSET(2) char D_MA_6002FF0[] = "__OTR__ast_macbeth/D_MA_6002FF0";

static const ALIGN_ASSET(2) char D_MA_6003030[] = "__OTR__ast_macbeth/D_MA_6003030";

static const ALIGN_ASSET(2) char aMaRailroadSwitch3DL[] = "__OTR__ast_macbeth/aMaRailroadSwitch3DL";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_3108[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_3108";

static const ALIGN_ASSET(2) char D_MA_6003138[] = "__OTR__ast_macbeth/D_MA_6003138";

static const ALIGN_ASSET(2) char D_MA_6003238[] = "__OTR__ast_macbeth/D_MA_6003238";

static const ALIGN_ASSET(2) char D_MA_6003370[] = "__OTR__ast_macbeth/D_MA_6003370";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_3628[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_3628";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_37F8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_37F8";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_3878[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_3878";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_3A08[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_3A08";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_3B28[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_3B28";

static const ALIGN_ASSET(2) char D_MA_6003B58[] = "__OTR__ast_macbeth/D_MA_6003B58";

static const ALIGN_ASSET(2) char D_MA_6003F58[] = "__OTR__ast_macbeth/D_MA_6003F58";

static const ALIGN_ASSET(2) char D_MA_6003FC8[] = "__OTR__ast_macbeth/D_MA_6003FC8";

static const ALIGN_ASSET(2) char D_MA_60043C8[] = "__OTR__ast_macbeth/D_MA_60043C8";

static const ALIGN_ASSET(2) char D_MA_6004440[] = "__OTR__ast_macbeth/D_MA_6004440";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_4560[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_4560";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_45A0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_45A0";

static const ALIGN_ASSET(2) char D_MA_6004640[] = "__OTR__ast_macbeth/D_MA_6004640";

static const ALIGN_ASSET(2) char D_MA_6004A40[] = "__OTR__ast_macbeth/D_MA_6004A40";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_4C40[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_4C40";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_4E58[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_4E58";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_4EA8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_4EA8";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_4FA8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_4FA8";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_5028[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_5028";

static const ALIGN_ASSET(2) char D_MA_60050F8[] = "__OTR__ast_macbeth/D_MA_60050F8";

static const ALIGN_ASSET(2) char D_MA_60051F8[] = "__OTR__ast_macbeth/D_MA_60051F8";

static const ALIGN_ASSET(2) char D_MA_6005238[] = "__OTR__ast_macbeth/D_MA_6005238";

static const ALIGN_ASSET(2) char D_MA_6005638[] = "__OTR__ast_macbeth/D_MA_6005638";

static const ALIGN_ASSET(2) char D_MA_6005828[] = "__OTR__ast_macbeth/D_MA_6005828";

static const ALIGN_ASSET(2) char D_MA_6006030[] = "__OTR__ast_macbeth/D_MA_6006030";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_62F8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_62F8";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_63F8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_63F8";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_64F8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_64F8";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_6578[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_6578";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_65B8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_65B8";

static const ALIGN_ASSET(2) char aMaIndicatorSignDL[] = "__OTR__ast_macbeth/aMaIndicatorSignDL";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_6888[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_6888";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_68C8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_68C8";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_6908[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_6908";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_6968[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_6968";

static const ALIGN_ASSET(2) char D_MA_60069A8[] = "__OTR__ast_macbeth/D_MA_60069A8";

static const ALIGN_ASSET(2) char D_MA_6006AA8[] = "__OTR__ast_macbeth/D_MA_6006AA8";

static const ALIGN_ASSET(2) char D_MA_6006BE8[] = "__OTR__ast_macbeth/D_MA_6006BE8";

static const ALIGN_ASSET(2) char D_MA_6006FE8[] = "__OTR__ast_macbeth/D_MA_6006FE8";

static const ALIGN_ASSET(2) char aMaDistanceSign4DL[] = "__OTR__ast_macbeth/aMaDistanceSign4DL";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_7258[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_7258";

static const ALIGN_ASSET(2) char aMaDistanceSign3DL[] = "__OTR__ast_macbeth/aMaDistanceSign3DL";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_7328[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_7328";

static const ALIGN_ASSET(2) char aMaDistanceSign2DL[] = "__OTR__ast_macbeth/aMaDistanceSign2DL";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_73F8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_73F8";

static const ALIGN_ASSET(2) char aMaDistanceSign1DL[] = "__OTR__ast_macbeth/aMaDistanceSign1DL";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_74C8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_74C8";

static const ALIGN_ASSET(2) char aMaDistanceSign5DL[] = "__OTR__ast_macbeth/aMaDistanceSign5DL";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_7598[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_7598";

static const ALIGN_ASSET(2) char aMaWeaponsFactoryDL[] = "__OTR__ast_macbeth/aMaWeaponsFactoryDL";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_8360[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_8360";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_8420[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_8420";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_8460[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_8460";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_84A0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_84A0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_8520[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_8520";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_85E0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_85E0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_8620[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_8620";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_8750[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_8750";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_8820[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_8820";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_8860[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_8860";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_88E0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_88E0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_8A10[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_8A10";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_8AE0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_8AE0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_8B60[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_8B60";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_8C20[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_8C20";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_8D60[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_8D60";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_8E00[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_8E00";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_8E40[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_8E40";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_8FA0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_8FA0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_8FE0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_8FE0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_9020[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_9020";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_90E0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_90E0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_91A0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_91A0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_91E0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_91E0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_9220[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_9220";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_9260[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_9260";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_92A0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_92A0";

static const ALIGN_ASSET(2) char D_MA_60092E0[] = "__OTR__ast_macbeth/D_MA_60092E0";

static const ALIGN_ASSET(2) char D_MA_6009AE0[] = "__OTR__ast_macbeth/D_MA_6009AE0";

static const ALIGN_ASSET(2) char D_MA_6009BE0[] = "__OTR__ast_macbeth/D_MA_6009BE0";

static const ALIGN_ASSET(2) char aMaRailroadSwitch8DL[] = "__OTR__ast_macbeth/aMaRailroadSwitch8DL";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_9CE8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_9CE8";

static const ALIGN_ASSET(2) char D_MA_6009D18[] = "__OTR__ast_macbeth/D_MA_6009D18";

static const ALIGN_ASSET(2) char D_MA_6009E18[] = "__OTR__ast_macbeth/D_MA_6009E18";

static const ALIGN_ASSET(2) char aMaRailroadSwitch7DL[] = "__OTR__ast_macbeth/aMaRailroadSwitch7DL";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_9FA8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_9FA8";

static const ALIGN_ASSET(2) char D_MA_6009FD8[] = "__OTR__ast_macbeth/D_MA_6009FD8";

static const ALIGN_ASSET(2) char D_MA_600A0D8[] = "__OTR__ast_macbeth/D_MA_600A0D8";

static const ALIGN_ASSET(2) char aMaRailroadSwitch6DL[] = "__OTR__ast_macbeth/aMaRailroadSwitch6DL";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_A288[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_A288";

static const ALIGN_ASSET(2) char D_MA_600A2B8[] = "__OTR__ast_macbeth/D_MA_600A2B8";

static const ALIGN_ASSET(2) char D_MA_600A3B8[] = "__OTR__ast_macbeth/D_MA_600A3B8";

static const ALIGN_ASSET(2) char aMaRailroadSwitch5DL[] = "__OTR__ast_macbeth/aMaRailroadSwitch5DL";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_A568[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_A568";

static const ALIGN_ASSET(2) char D_MA_600A598[] = "__OTR__ast_macbeth/D_MA_600A598";

static const ALIGN_ASSET(2) char D_MA_600A698[] = "__OTR__ast_macbeth/D_MA_600A698";

static const ALIGN_ASSET(2) char aMaRailroadSwitch4DL[] = "__OTR__ast_macbeth/aMaRailroadSwitch4DL";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_A868[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_A868";

static const ALIGN_ASSET(2) char D_MA_600A898[] = "__OTR__ast_macbeth/D_MA_600A898";

static const ALIGN_ASSET(2) char D_MA_600A998[] = "__OTR__ast_macbeth/D_MA_600A998";

static const ALIGN_ASSET(2) char aMaRailroadSwitch2DL[] = "__OTR__ast_macbeth/aMaRailroadSwitch2DL";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_AB08[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_AB08";

static const ALIGN_ASSET(2) char D_MA_600AB38[] = "__OTR__ast_macbeth/D_MA_600AB38";

static const ALIGN_ASSET(2) char D_MA_600AC38[] = "__OTR__ast_macbeth/D_MA_600AC38";

static const ALIGN_ASSET(2) char aMaRailroadSwitch1DL[] = "__OTR__ast_macbeth/aMaRailroadSwitch1DL";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_ADE8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_ADE8";

static const ALIGN_ASSET(2) char D_MA_600AE18[] = "__OTR__ast_macbeth/D_MA_600AE18";

static const ALIGN_ASSET(2) char D_MA_600AE98[] = "__OTR__ast_macbeth/D_MA_600AE98";

static const ALIGN_ASSET(2) char aMaGuillotine1DL[] = "__OTR__ast_macbeth/aMaGuillotine1DL";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_B120[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_B120";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_B160[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_B160";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_B260[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_B260";

static const ALIGN_ASSET(2) char D_MA_600B2E0[] = "__OTR__ast_macbeth/D_MA_600B2E0";

static const ALIGN_ASSET(2) char D_MA_600C2E0[] = "__OTR__ast_macbeth/D_MA_600C2E0";

static const ALIGN_ASSET(2) char D_MA_600C3E0[] = "__OTR__ast_macbeth/D_MA_600C3E0";

static const ALIGN_ASSET(2) char D_MA_600C4D0[] = "__OTR__ast_macbeth/D_MA_600C4D0";

static const ALIGN_ASSET(2) char D_MA_600C65C[] = "__OTR__ast_macbeth/D_MA_600C65C";

static const ALIGN_ASSET(2) char D_MA_600CD18[] = "__OTR__ast_macbeth/D_MA_600CD18";

static const ALIGN_ASSET(2) char D_MA_600D1E4[] = "__OTR__ast_macbeth/D_MA_600D1E4";

static const ALIGN_ASSET(2) char D_MA_600D280[] = "__OTR__ast_macbeth/D_MA_600D280";

static const ALIGN_ASSET(2) char aMaSpearDL[] = "__OTR__ast_macbeth/aMaSpearDL";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_D638[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_D638";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_D6B8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_D6B8";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_D768[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_D768";

static const ALIGN_ASSET(2) char D_MA_600D878[] = "__OTR__ast_macbeth/D_MA_600D878";

static const ALIGN_ASSET(2) char D_MA_600D978[] = "__OTR__ast_macbeth/D_MA_600D978";

static const ALIGN_ASSET(2) char aMaLaserTurretDL[] = "__OTR__ast_macbeth/aMaLaserTurretDL";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_DCF0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_DCF0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_DD60[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_DD60";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_DDF0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_DDF0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_DE50[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_DE50";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_DEA0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_DEA0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_DF10[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_DF10";

static const ALIGN_ASSET(2) char D_MA_600DF60[] = "__OTR__ast_macbeth/D_MA_600DF60";

static const ALIGN_ASSET(2) char D_MA_600E360[] = "__OTR__ast_macbeth/D_MA_600E360";

static const ALIGN_ASSET(2) char D_MA_600E460[] = "__OTR__ast_macbeth/D_MA_600E460";

static const ALIGN_ASSET(2) char D_MA_600E480[] = "__OTR__ast_macbeth/D_MA_600E480";

static const ALIGN_ASSET(2) char D_MA_600E880[] = "__OTR__ast_macbeth/D_MA_600E880";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_EA50[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_EA50";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_EC08[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_EC08";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_EC78[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_EC78";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_EDB8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_EDB8";

static const ALIGN_ASSET(2) char D_MA_600EE38[] = "__OTR__ast_macbeth/D_MA_600EE38";

static const ALIGN_ASSET(2) char D_MA_600EF38[] = "__OTR__ast_macbeth/D_MA_600EF38";

static const ALIGN_ASSET(2) char D_MA_600EF98[] = "__OTR__ast_macbeth/D_MA_600EF98";

static const ALIGN_ASSET(2) char D_MA_600F018[] = "__OTR__ast_macbeth/D_MA_600F018";

static const ALIGN_ASSET(2) char D_MA_600F028[] = "__OTR__ast_macbeth/D_MA_600F028";

static const ALIGN_ASSET(2) char D_MA_600F128[] = "__OTR__ast_macbeth/D_MA_600F128";

static const ALIGN_ASSET(2) char D_MA_600F160[] = "__OTR__ast_macbeth/D_MA_600F160";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_F270[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_F270";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_F2B0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_F2B0";

static const ALIGN_ASSET(2) char D_MA_600F2F0[] = "__OTR__ast_macbeth/D_MA_600F2F0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_F388[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_F388";

static const ALIGN_ASSET(2) char D_MA_600F3D0[] = "__OTR__ast_macbeth/D_MA_600F3D0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_F5D0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_F5D0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_F610[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_F610";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_F650[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_F650";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_F690[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_F690";

static const ALIGN_ASSET(2) char D_MA_600F6C0[] = "__OTR__ast_macbeth/D_MA_600F6C0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_F8C0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_F8C0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_F900[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_F900";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_F940[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_F940";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_F980[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_F980";

static const ALIGN_ASSET(2) char D_MA_600F9B0[] = "__OTR__ast_macbeth/D_MA_600F9B0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_FB70[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_FB70";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_FC30[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_FC30";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_FCD0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_FCD0";

static const ALIGN_ASSET(2) char D_MA_600FEC4[] = "__OTR__ast_macbeth/D_MA_600FEC4";

static const ALIGN_ASSET(2) char D_MA_6010144[] = "__OTR__ast_macbeth/D_MA_6010144";

static const ALIGN_ASSET(2) char D_MA_6010220[] = "__OTR__ast_macbeth/D_MA_6010220";

static const ALIGN_ASSET(2) char D_MA_601042C[] = "__OTR__ast_macbeth/D_MA_601042C";

static const ALIGN_ASSET(2) char D_MA_6010470[] = "__OTR__ast_macbeth/D_MA_6010470";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_10598[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_10598";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_106B8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_106B8";

static const ALIGN_ASSET(2) char aMaProximityLightSidesDL[] = "__OTR__ast_macbeth/aMaProximityLightSidesDL";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_107A8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_107A8";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_10870[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_10870";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_109C0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_109C0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_10BB0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_10BB0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_10BE0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_10BE0";

static const ALIGN_ASSET(2) char D_MA_6010C20[] = "__OTR__ast_macbeth/D_MA_6010C20";

static const ALIGN_ASSET(2) char D_MA_6011B40[] = "__OTR__ast_macbeth/D_MA_6011B40";

static const ALIGN_ASSET(2) char D_MA_6012A60[] = "__OTR__ast_macbeth/D_MA_6012A60";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_12AC0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_12AC0";

static const ALIGN_ASSET(2) char D_MA_6012BC0[] = "__OTR__ast_macbeth/D_MA_6012BC0";

static const ALIGN_ASSET(2) char D_MA_6012C00[] = "__OTR__ast_macbeth/D_MA_6012C00";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_12C58[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_12C58";

static const ALIGN_ASSET(2) char D_MA_6012C98[] = "__OTR__ast_macbeth/D_MA_6012C98";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_12CE0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_12CE0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_12E08[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_12E08";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_12E48[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_12E48";

static const ALIGN_ASSET(2) char aMaShockBoxLightDL[] = "__OTR__ast_macbeth/aMaShockBoxLightDL";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_12FA0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_12FA0";

static const ALIGN_ASSET(2) char D_MA_6012FE0[] = "__OTR__ast_macbeth/D_MA_6012FE0";

static const ALIGN_ASSET(2) char D_MA_6013060[] = "__OTR__ast_macbeth/D_MA_6013060";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_130C8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_130C8";

static const ALIGN_ASSET(2) char D_MA_6013158[] = "__OTR__ast_macbeth/D_MA_6013158";

static const ALIGN_ASSET(2) char aMaGuillotineHousingDL[] = "__OTR__ast_macbeth/aMaGuillotineHousingDL";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_13AE8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_13AE8";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_13B68[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_13B68";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_13CA8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_13CA8";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_13DD0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_13DD0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_13E98[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_13E98";

static const ALIGN_ASSET(2) char D_MA_6013F58[] = "__OTR__ast_macbeth/D_MA_6013F58";

static const ALIGN_ASSET(2) char D_MA_6014058[] = "__OTR__ast_macbeth/D_MA_6014058";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_14110[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_14110";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_14328[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_14328";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_14368[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_14368";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_143F8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_143F8";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_14428[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_14428";

static const ALIGN_ASSET(2) char D_MA_6014458[] = "__OTR__ast_macbeth/D_MA_6014458";

static const ALIGN_ASSET(2) char D_MA_6015494[] = "__OTR__ast_macbeth/D_MA_6015494";

static const ALIGN_ASSET(2) char D_MA_6015500[] = "__OTR__ast_macbeth/D_MA_6015500";

static const ALIGN_ASSET(2) char aMaShockBoxDL[] = "__OTR__ast_macbeth/aMaShockBoxDL";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_156E0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_156E0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_15760[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_15760";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_157E0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_157E0";

static const ALIGN_ASSET(2) char D_MA_6015C24[] = "__OTR__ast_macbeth/D_MA_6015C24";

static const ALIGN_ASSET(2) char D_MA_6016040[] = "__OTR__ast_macbeth/D_MA_6016040";

static const ALIGN_ASSET(2) char D_MA_60163F0[] = "__OTR__ast_macbeth/D_MA_60163F0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_16400[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_16400";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_165C0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_165C0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_166E0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_166E0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_16820[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_16820";

static const ALIGN_ASSET(2) char D_MA_6016B2C[] = "__OTR__ast_macbeth/D_MA_6016B2C";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_16B40[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_16B40";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_16D00[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_16D00";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_16E20[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_16E20";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_16F60[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_16F60";

static const ALIGN_ASSET(2) char D_MA_6017714[] = "__OTR__ast_macbeth/D_MA_6017714";

static const ALIGN_ASSET(2) char D_MA_6017720[] = "__OTR__ast_macbeth/D_MA_6017720";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_17998[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_17998";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_17B58[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_17B58";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_17BC8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_17BC8";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_17D48[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_17D48";

static const ALIGN_ASSET(2) char D_MA_6017EB8[] = "__OTR__ast_macbeth/D_MA_6017EB8";

static const ALIGN_ASSET(2) char D_MA_60186B8[] = "__OTR__ast_macbeth/D_MA_60186B8";

static const ALIGN_ASSET(2) char D_MA_6018AB8[] = "__OTR__ast_macbeth/D_MA_6018AB8";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_18C90[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_18C90";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_18DF8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_18DF8";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_18EA8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_18EA8";

static const ALIGN_ASSET(2) char D_MA_6019028[] = "__OTR__ast_macbeth/D_MA_6019028";

static const ALIGN_ASSET(2) char D_MA_6019128[] = "__OTR__ast_macbeth/D_MA_6019128";

static const ALIGN_ASSET(2) char D_MA_6019220[] = "__OTR__ast_macbeth/D_MA_6019220";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_19270[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_19270";

static const ALIGN_ASSET(2) char D_MA_60192B0[] = "__OTR__ast_macbeth/D_MA_60192B0";

static const ALIGN_ASSET(2) char aMaBoulderDL[] = "__OTR__ast_macbeth/aMaBoulderDL";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1A3A8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1A3A8";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1A5A8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1A5A8";

static const ALIGN_ASSET(2) char D_MA_601A5E8[] = "__OTR__ast_macbeth/D_MA_601A5E8";

static const ALIGN_ASSET(2) char D_MA_601A6E8[] = "__OTR__ast_macbeth/D_MA_601A6E8";

static const ALIGN_ASSET(2) char D_MA_601A7A0[] = "__OTR__ast_macbeth/D_MA_601A7A0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1A7F8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1A7F8";

static const ALIGN_ASSET(2) char D_MA_601A840[] = "__OTR__ast_macbeth/D_MA_601A840";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1A898[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1A898";

static const ALIGN_ASSET(2) char D_MA_601A8C8[] = "__OTR__ast_macbeth/D_MA_601A8C8";

static const ALIGN_ASSET(2) char aMaFloor6DL[] = "__OTR__ast_macbeth/aMaFloor6DL";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1B128[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1B128";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_1B170[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_1B170";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1B458[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1B458";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1B498[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1B498";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1B578[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1B578";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1B678[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1B678";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1B738[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1B738";

static const ALIGN_ASSET(2) char aMaWall4DL[] = "__OTR__ast_macbeth/aMaWall4DL";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1B988[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1B988";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1BA08[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1BA08";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1BA58[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1BA58";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1BB38[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1BB38";

static const ALIGN_ASSET(2) char D_MA_601BB78[] = "__OTR__ast_macbeth/D_MA_601BB78";

static const ALIGN_ASSET(2) char D_MA_601BC78[] = "__OTR__ast_macbeth/D_MA_601BC78";

static const ALIGN_ASSET(2) char D_MA_601BD08[] = "__OTR__ast_macbeth/D_MA_601BD08";

static const ALIGN_ASSET(2) char D_MA_601BE08[] = "__OTR__ast_macbeth/D_MA_601BE08";

static const ALIGN_ASSET(2) char D_MA_601BE90[] = "__OTR__ast_macbeth/D_MA_601BE90";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1BF38[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1BF38";

static const ALIGN_ASSET(2) char aMaTowerTopDL[] = "__OTR__ast_macbeth/aMaTowerTopDL";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1C0A8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1C0A8";

static const ALIGN_ASSET(2) char D_MA_601C170[] = "__OTR__ast_macbeth/D_MA_601C170";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1C318[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1C318";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1C458[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1C458";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1C4D8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1C4D8";

static const ALIGN_ASSET(2) char aMaRailroadCartDL[] = "__OTR__ast_macbeth/aMaRailroadCartDL";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1C7C8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1C7C8";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1C848[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1C848";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1C898[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1C898";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1C958[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1C958";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1C9D8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1C9D8";

static const ALIGN_ASSET(2) char D_MA_601D188[] = "__OTR__ast_macbeth/D_MA_601D188";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_1D1A0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_1D1A0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1D270[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1D270";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_1D370[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_1D370";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1D608[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1D608";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1D808[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1D808";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1D968[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1D968";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1D9D8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1D9D8";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1DB18[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1DB18";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_1DBA0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_1DBA0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1DC58[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1DC58";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_1DD30[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_1DD30";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1DE88[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1DE88";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1DF18[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1DF18";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_1E080[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_1E080";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1E130[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1E130";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_1E1D0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_1E1D0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1E270[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1E270";

static const ALIGN_ASSET(2) char D_MA_601EA28[] = "__OTR__ast_macbeth/D_MA_601EA28";

static const ALIGN_ASSET(2) char D_MA_601EAB0[] = "__OTR__ast_macbeth/D_MA_601EAB0";

static const ALIGN_ASSET(2) char D_MA_601EBBC[] = "__OTR__ast_macbeth/D_MA_601EBBC";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_1EBE0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_1EBE0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1ED20[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1ED20";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1EE20[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1EE20";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_1EF20[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_1EF20";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1EFF0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1EFF0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_1F0F0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_1F0F0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1F188[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1F188";

static const ALIGN_ASSET(2) char aMaWall2DL[] = "__OTR__ast_macbeth/aMaWall2DL";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1F228[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1F228";

static const ALIGN_ASSET(2) char aMaProximityLightTopDL[] = "__OTR__ast_macbeth/aMaProximityLightTopDL";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1F308[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1F308";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_1F350[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_1F350";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1F3E8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1F3E8";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_1F430[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_1F430";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1F588[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1F588";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1F6C8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1F6C8";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_1F730[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_1F730";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1F7D0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1F7D0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_1F850[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_1F850";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1F950[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1F950";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_1FA50[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_1FA50";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1FB10[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1FB10";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_1FB90[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_1FB90";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1FC58[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1FC58";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_1FCE0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_1FCE0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1FDA8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1FDA8";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_1FE50[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_1FE50";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_1FF20[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_1FF20";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_1FFC0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_1FFC0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_20060[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_20060";

static const ALIGN_ASSET(2) char D_MA_60200E0[] = "__OTR__ast_macbeth/D_MA_60200E0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_201D8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_201D8";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_202E0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_202E0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_203A0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_203A0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_20420[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_20420";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_204E8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_204E8";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_20580[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_20580";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_20648[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_20648";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_206F0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_206F0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_207C0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_207C0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_20860[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_20860";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_20920[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_20920";

static const ALIGN_ASSET(2) char D_MA_6020A30[] = "__OTR__ast_macbeth/D_MA_6020A30";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_20B98[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_20B98";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_20C58[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_20C58";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_20D10[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_20D10";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_20DD0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_20DD0";

static const ALIGN_ASSET(2) char D_MA_6020E60[] = "__OTR__ast_macbeth/D_MA_6020E600";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_20FB8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_20FB8";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_21028[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_21028";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_211B0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_211B0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_21250[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_21250";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_212A0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_212A0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_21388[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_21388";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_21460[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_21460";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_21570[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_21570";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_215B0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_215B0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_215E0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_215E0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_217C0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_217C0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_218F0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_218F0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_219D0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_219D0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_21A48[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_21A48";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_21B10[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_21B10";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_21B88[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_21B88";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_21C50[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_21C50";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_21CC8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_21CC8";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_21D90[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_21D90";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_21E08[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_21E08";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_21ED0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_21ED0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_21FC0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_21FC0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_221C0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_221C0";

static const ALIGN_ASSET(2) char D_MA_6022200[] = "__OTR__ast_macbeth/D_MA_6022200";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_22278[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_22278";

static const ALIGN_ASSET(2) char D_MA_60223C0[] = "__OTR__ast_macbeth/D_MA_60223C0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_22418[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_22418";

static const ALIGN_ASSET(2) char D_MA_6022450[] = "__OTR__ast_macbeth/D_MA_6022450";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_224E8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_224E8";

static const ALIGN_ASSET(2) char D_MA_6022530[] = "__OTR__ast_macbeth/D_MA_6022530";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_225C8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_225C8";

static const ALIGN_ASSET(2) char D_MA_6022610[] = "__OTR__ast_macbeth/D_MA_6022610";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_226E8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_226E8";

static const ALIGN_ASSET(2) char D_MA_60227F0[] = "__OTR__ast_macbeth/D_MA_60227F0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_229A8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_229A8";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_22A68[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_22A68";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_22AC8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_22AC8";

static const ALIGN_ASSET(2) char D_MA_6022B68[] = "__OTR__ast_macbeth/D_MA_6022B68";

static const ALIGN_ASSET(2) char D_MA_6022F68[] = "__OTR__ast_macbeth/D_MA_6022F68";

static const ALIGN_ASSET(2) char D_MA_60230C8[] = "__OTR__ast_macbeth/D_MA_60230C8";

static const ALIGN_ASSET(2) char D_MA_60231C8[] = "__OTR__ast_macbeth/D_MA_60231C8";

static const ALIGN_ASSET(2) char D_MA_6023228[] = "__OTR__ast_macbeth/D_MA_6023228";

static const ALIGN_ASSET(2) char D_MA_6023328[] = "__OTR__ast_macbeth/D_MA_6023328";

static const ALIGN_ASSET(2) char D_MA_6023388[] = "__OTR__ast_macbeth/D_MA_6023388";

static const ALIGN_ASSET(2) char D_MA_6023788[] = "__OTR__ast_macbeth/D_MA_6023788";

static const ALIGN_ASSET(2) char aMaWall3DL[] = "__OTR__ast_macbeth/aMaWall3DL";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_23950[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_23950";

static const ALIGN_ASSET(2) char D_MA_60239D0[] = "__OTR__ast_macbeth/D_MA_60239D0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_23B88[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_23B88";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_23C48[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_23C48";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_23CE8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_23CE8";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_23D50[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_23D50";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_23EE8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_23EE8";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_23F68[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_23F68";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_23FC8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_23FC8";

static const ALIGN_ASSET(2) char aMaBuilding1DL[] = "__OTR__ast_macbeth/aMaBuilding1DL";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_24130[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_24130";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_241F0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_241F0";

static const ALIGN_ASSET(2) char D_MA_6024230[] = "__OTR__ast_macbeth/D_MA_6024230";

static const ALIGN_ASSET(2) char D_MA_6024630[] = "__OTR__ast_macbeth/D_MA_6024630";

static const ALIGN_ASSET(2) char D_MA_6024670[] = "__OTR__ast_macbeth/D_MA_6024670";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_249E8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_249E8";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_24B28[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_24B28";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_24C68[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_24C68";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_24D28[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_24D28";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_24DE8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_24DE8";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_24EA8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_24EA8";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_24F30[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_24F30";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_25098[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_25098";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_25118[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_25118";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_25158[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_25158";

static const ALIGN_ASSET(2) char aMaHorizontalLockBarDL[] = "__OTR__ast_macbeth/aMaHorizontalLockBarDL";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_252A0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_252A0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_25320[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_25320";

static const ALIGN_ASSET(2) char aMaTowerBottomDL[] = "__OTR__ast_macbeth/aMaTowerBottomDL";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_255B0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_255B0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_25670[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_25670";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_256B0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_256B0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_25770[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_25770";

static const ALIGN_ASSET(2) char aMaBarrierDL[] = "__OTR__ast_macbeth/aMaBarrierDL";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_25808[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_25808";

static const ALIGN_ASSET(2) char aMaVerticalLockBarDL[] = "__OTR__ast_macbeth/aMaVerticalLockBarDL";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_25970[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_25970";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_25A30[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_25A30";

static const ALIGN_ASSET(2) char D_MA_6025A70[] = "__OTR__ast_macbeth/D_MA_6025A70";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_25B08[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_25B08";

static const ALIGN_ASSET(2) char D_MA_6025B50[] = "__OTR__ast_macbeth/D_MA_6025B50";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_25BE8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_25BE8";

static const ALIGN_ASSET(2) char D_MA_6025CA0[] = "__OTR__ast_macbeth/D_MA_6025CA0";

static const ALIGN_ASSET(2) char D_MA_6025DAC[] = "__OTR__ast_macbeth/D_MA_6025DAC";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_25DD0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_25DD0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_25F98[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_25F98";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_26028[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_26028";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_261E8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_261E8";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_26270[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_26270";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_26428[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_26428";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_264E8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_264E8";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_26568[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_26568";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_265F0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_265F0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_26758[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_26758";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_267D8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_267D8";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_26818[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_26818";

static const ALIGN_ASSET(2) char D_MA_6026860[] = "__OTR__ast_macbeth/D_MA_6026860";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_26910[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_26910";

static const ALIGN_ASSET(2) char D_MA_60269E0[] = "__OTR__ast_macbeth/D_MA_60269E0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_26B00[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_26B00";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_26BC0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_26BC0";

static const ALIGN_ASSET(2) char D_MA_6026C00[] = "__OTR__ast_macbeth/D_MA_6026C00";

static const ALIGN_ASSET(2) char D_MA_6027000[] = "__OTR__ast_macbeth/D_MA_6027000";

static const ALIGN_ASSET(2) char aMaWall1DL[] = "__OTR__ast_macbeth/aMaWall1DL";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_27138[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_27138";

static const ALIGN_ASSET(2) char aMaBuilding2DL[] = "__OTR__ast_macbeth/aMaBuilding2DL";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_271E8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_271E8";

static const ALIGN_ASSET(2) char D_MA_6027320[] = "__OTR__ast_macbeth/D_MA_6027320";

static const ALIGN_ASSET(2) char D_MA_602742C[] = "__OTR__ast_macbeth/D_MA_602742C";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_27450[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_27450";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_27588[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_27588";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_27628[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_27628";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_27750[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_27750";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_27800[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_27800";

static const ALIGN_ASSET(2) char aMaFloor2DL[] = "__OTR__ast_macbeth/aMaFloor2DL";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_27958[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_27958";

static const ALIGN_ASSET(2) char D_MA_6027A04[] = "__OTR__ast_macbeth/D_MA_6027A04";

static const ALIGN_ASSET(2) char D_MA_6027AF0[] = "__OTR__ast_macbeth/D_MA_6027AF0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_27B10[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_27B10";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_27BA8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_27BA8";

static const ALIGN_ASSET(2) char D_MA_6027BF0[] = "__OTR__ast_macbeth/D_MA_6027BF0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_27C98[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_27C98";

static const ALIGN_ASSET(2) char D_MA_6027D40[] = "__OTR__ast_macbeth/D_MA_6027D40";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_27DE8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_27DE8";

static const ALIGN_ASSET(2) char D_MA_6027EB0[] = "__OTR__ast_macbeth/D_MA_6027EB0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_28160[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_28160";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_281C0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_281C0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_282C0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_282C0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_283A0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_283A0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_283E0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_283E0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_28460[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_28460";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_28580[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_28580";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_285C0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_285C0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_28680[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_28680";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_287A0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_287A0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_287E0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_287E0";

static const ALIGN_ASSET(2) char D_MA_60288A0[] = "__OTR__ast_macbeth/D_MA_60288A0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_28D20[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_28D20";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_28D80[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_28D80";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_28E80[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_28E80";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_29080[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_29080";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_29280[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_29280";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_29460[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_29460";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_29640[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_29640";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_296F0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_296F0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_297D0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_297D0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_29810[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_29810";

static const ALIGN_ASSET(2) char D_MA_6029890[] = "__OTR__ast_macbeth/D_MA_6029890";

static const ALIGN_ASSET(2) char D_MA_VTX_602A0D0[] = "__OTR__ast_macbeth/D_MA_VTX_602A0D0";

static const ALIGN_ASSET(2) char D_MA_602B980[] = "__OTR__ast_macbeth/D_MA_602B980";

static const ALIGN_ASSET(2) char D_MA_602BB80[] = "__OTR__ast_macbeth/D_MA_602BB80";

static const ALIGN_ASSET(2) char D_MA_602C380[] = "__OTR__ast_macbeth/D_MA_602C380";

static const ALIGN_ASSET(2) char D_MA_602CB80[] = "__OTR__ast_macbeth/D_MA_602CB80";

static const ALIGN_ASSET(2) char D_MA_602D380[] = "__OTR__ast_macbeth/D_MA_602D380";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_2D560[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_2D560";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_2D5E0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_2D5E0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_2D720[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_2D720";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_2D8A0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_2D8A0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_2D998[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_2D998";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_2DA98[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_2DA98";

static const ALIGN_ASSET(2) char aMaFloor1DL[] = "__OTR__ast_macbeth/aMaFloor1DL";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_2DB38[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_2DB38";

static const ALIGN_ASSET(2) char aMaFloor3DL[] = "__OTR__ast_macbeth/aMaFloor3DL";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_2DBD8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_2DBD8";

static const ALIGN_ASSET(2) char aMaFloor5DL[] = "__OTR__ast_macbeth/aMaFloor5DL";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_2DC78[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_2DC78";

static const ALIGN_ASSET(2) char D_MA_602DCB8[] = "__OTR__ast_macbeth/D_MA_602DCB8";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_2E4C0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_2E4C0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_2E5E8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_2E5E8";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_2E628[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_2E628";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_2E710[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_2E710";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_2E7B8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_2E7B8";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_2E880[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_2E880";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_2E918[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_2E918";

static const ALIGN_ASSET(2) char D_MA_602EA0C[] = "__OTR__ast_macbeth/D_MA_602EA0C";

static const ALIGN_ASSET(2) char D_MA_602EBB8[] = "__OTR__ast_macbeth/D_MA_602EBB8";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_2EBF0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_2EBF0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_2ECA8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_2ECA8";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_2EDA0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_2EDA0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_2EE98[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_2EE98";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_2EF98[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_2EF98";

static const ALIGN_ASSET(2) char D_MA_602F098[] = "__OTR__ast_macbeth/D_MA_602F098";

static const ALIGN_ASSET(2) char D_MA_602F264[] = "__OTR__ast_macbeth/D_MA_602F264";

static const ALIGN_ASSET(2) char D_MA_602F2E0[] = "__OTR__ast_macbeth/D_MA_602F2E0";

static const ALIGN_ASSET(2) char D_MA_602F36C[] = "__OTR__ast_macbeth/D_MA_602F36C";

static const ALIGN_ASSET(2) char D_MA_602F380[] = "__OTR__ast_macbeth/D_MA_602F380";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_2F418[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_2F418";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_2F460[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_2F460";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_2F4F8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_2F4F8";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_2F540[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_2F540";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_2F5D8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_2F5D8";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_2F620[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_2F620";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_2F6B8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_2F6B8";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_2F700[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_2F700";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_2F798[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_2F798";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_2F7E0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_2F7E0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_2F878[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_2F878";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_2F8C0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_2F8C0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_2F970[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_2F970";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_2FA30[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_2FA30";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_2FAC8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_2FAC8";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_2FB10[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_2FB10";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_2FBA8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_2FBA8";

static const ALIGN_ASSET(2) char D_MA_602FBF0[] = "__OTR__ast_macbeth/D_MA_602FBF0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_2FCC8[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_2FCC8";

static const ALIGN_ASSET(2) char D_MA_602FEB4[] = "__OTR__ast_macbeth/D_MA_602FEB4";

static const ALIGN_ASSET(2) char D_MA_602FFA0[] = "__OTR__ast_macbeth/D_MA_602FFA0";

static const ALIGN_ASSET(2) char D_MA_602FFC0[] = "__OTR__ast_macbeth/D_MA_602FFC0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_300C0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_300C0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_302A0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_302A0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_gfx_30390[] = "__OTR__ast_macbeth/ast_macbeth_seg6_gfx_30390";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_30438[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_30438";

static const ALIGN_ASSET(2) char aMaTerrainBumpDL[] = "__OTR__ast_macbeth/aMaTerrainBumpDL";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_30580[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_30580";

static const ALIGN_ASSET(2) char aMaFloor4DL[] = "__OTR__ast_macbeth/aMaFloor4DL";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_30688[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_30688";

static const ALIGN_ASSET(2) char D_MA_60306D0[] = "__OTR__ast_macbeth/D_MA_60306D0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_306F0[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_306F0";

static const ALIGN_ASSET(2) char D_MA_6030750[] = "__OTR__ast_macbeth/D_MA_6030750";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_30820[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_30820";

static const ALIGN_ASSET(2) char D_MA_60309D0[] = "__OTR__ast_macbeth/D_MA_60309D0";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_30A98[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_30A98";

static const ALIGN_ASSET(2) char D_MA_6030C50[] = "__OTR__ast_macbeth/D_MA_6030C50";

static const ALIGN_ASSET(2) char ast_macbeth_seg6_vtx_30D30[] = "__OTR__ast_macbeth/ast_macbeth_seg6_vtx_30D30";

static const ALIGN_ASSET(2) char D_MA_6030E30[] = "__OTR__ast_macbeth/D_MA_6030E30";

static const ALIGN_ASSET(2) char D_MA_6030E74[] = "__OTR__ast_macbeth/D_MA_6030E74";

static const ALIGN_ASSET(2) char D_MA_6030E80[] = "__OTR__ast_macbeth/D_MA_6030E80";

static const ALIGN_ASSET(2) char D_MA_6030EB0[] = "__OTR__ast_macbeth/D_MA_6030EB0";

static const ALIGN_ASSET(2) char D_MA_6030EBC[] = "__OTR__ast_macbeth/D_MA_6030EBC";

static const ALIGN_ASSET(2) char D_MA_6030EEC[] = "__OTR__ast_macbeth/D_MA_6030EEC";

static const ALIGN_ASSET(2) char D_MA_6030EF8[] = "__OTR__ast_macbeth/D_MA_6030EF8";

static const ALIGN_ASSET(2) char D_MA_6030F28[] = "__OTR__ast_macbeth/D_MA_6030F28";

static const ALIGN_ASSET(2) char D_MA_6030F34[] = "__OTR__ast_macbeth/D_MA_6030F34";

static const ALIGN_ASSET(2) char D_MA_6030F64[] = "__OTR__ast_macbeth/D_MA_6030F64";

static const ALIGN_ASSET(2) char D_MA_6030F7C[] = "__OTR__ast_macbeth/D_MA_6030F7C";

static const ALIGN_ASSET(2) char D_MA_6030FC4[] = "__OTR__ast_macbeth/D_MA_6030FC4";

static const ALIGN_ASSET(2) char D_MA_6030FD0[] = "__OTR__ast_macbeth/D_MA_6030FD0";

static const ALIGN_ASSET(2) char D_MA_6031000[] = "__OTR__ast_macbeth/D_MA_6031000";

static const ALIGN_ASSET(2) char D_MA_6035678[] = "__OTR__ast_macbeth/D_MA_6035678";

static const ALIGN_ASSET(2) char D_MA_60357CC[] = "__OTR__ast_macbeth/D_MA_60357CC";

static const ALIGN_ASSET(2) char D_MA_6035920[] = "__OTR__ast_macbeth/D_MA_6035920";

static const ALIGN_ASSET(2) char D_MA_60359AC[] = "__OTR__ast_macbeth/D_MA_60359AC";

static const ALIGN_ASSET(2) char aMaLocomotiveHitbox[] = "__OTR__ast_macbeth/aMaLocomotiveHitbox";

static const ALIGN_ASSET(2) char aMaTrainCar2Hitbox[] = "__OTR__ast_macbeth/aMaTrainCar2Hitbox";

static const ALIGN_ASSET(2) char aMaTrainCar1Hitbox[] = "__OTR__ast_macbeth/aMaTrainCar1Hitbox";

static const ALIGN_ASSET(2) char D_MA_6035A94[] = "__OTR__ast_macbeth/D_MA_6035A94";

static const ALIGN_ASSET(2) char aMaTrainCar3Hitbox[] = "__OTR__ast_macbeth/aMaTrainCar3Hitbox";

static const ALIGN_ASSET(2) char D_MA_6035B44[] = "__OTR__ast_macbeth/D_MA_6035B44";

static const ALIGN_ASSET(2) char D_MA_6035BA8[] = "__OTR__ast_macbeth/D_MA_6035BA8";

static const ALIGN_ASSET(2) char D_MA_6035C0C[] = "__OTR__ast_macbeth/D_MA_6035C0C";

static const ALIGN_ASSET(2) char D_MA_6035C70[] = "__OTR__ast_macbeth/D_MA_6035C70";

static const ALIGN_ASSET(2) char D_MA_6035CD4[] = "__OTR__ast_macbeth/D_MA_6035CD4";

static const ALIGN_ASSET(2) char D_MA_6035D38[] = "__OTR__ast_macbeth/D_MA_6035D38";

static const ALIGN_ASSET(2) char aMaTrainCar4Hitbox[] = "__OTR__ast_macbeth/aMaTrainCar4Hitbox";

static const ALIGN_ASSET(2) char D_MA_6035DD0[] = "__OTR__ast_macbeth/D_MA_6035DD0";

static const ALIGN_ASSET(2) char aMaTrainCar5Hitbox[] = "__OTR__ast_macbeth/aMaTrainCar5Hitbox";

static const ALIGN_ASSET(2) char D_MA_6035E68[] = "__OTR__ast_macbeth/D_MA_6035E68";

static const ALIGN_ASSET(2) char D_MA_6035ECC[] = "__OTR__ast_macbeth/D_MA_6035ECC";

static const ALIGN_ASSET(2) char D_MA_6035F30[] = "__OTR__ast_macbeth/D_MA_6035F30";

static const ALIGN_ASSET(2) char D_MA_6035F94[] = "__OTR__ast_macbeth/D_MA_6035F94";

static const ALIGN_ASSET(2) char D_MA_6035FF8[] = "__OTR__ast_macbeth/D_MA_6035FF8";

static const ALIGN_ASSET(2) char D_MA_603605C[] = "__OTR__ast_macbeth/D_MA_603605C";

static const ALIGN_ASSET(2) char aMaTrainCar6Hitbox[] = "__OTR__ast_macbeth/aMaTrainCar6Hitbox";

static const ALIGN_ASSET(2) char aMaTrainCar7Hitbox[] = "__OTR__ast_macbeth/aMaTrainCar7Hitbox";

static const ALIGN_ASSET(2) char D_MA_6036188[] = "__OTR__ast_macbeth/D_MA_6036188";

static const ALIGN_ASSET(2) char aMaTrainTrack13Hitbox[] = "__OTR__ast_macbeth/aMaTrainTrack13Hitbox";

static const ALIGN_ASSET(2) char D_MA_6036250[] = "__OTR__ast_macbeth/D_MA_6036250";

static const ALIGN_ASSET(2) char aMaBuilding1Hitbox[] = "__OTR__ast_macbeth/aMaBuilding1Hitbox";

static const ALIGN_ASSET(2) char aMaBuilding2Hitbox[] = "__OTR__ast_macbeth/aMaBuilding2Hitbox";

static const ALIGN_ASSET(2) char aMaTowerHitbox[] = "__OTR__ast_macbeth/aMaTowerHitbox";

static const ALIGN_ASSET(2) char aMaWall2Hitbox[] = "__OTR__ast_macbeth/aMaWall2Hitbox";

static const ALIGN_ASSET(2) char aMaWall4Hitbox[] = "__OTR__ast_macbeth/aMaWall4Hitbox";

static const ALIGN_ASSET(2) char aMaWall3Hitbox[] = "__OTR__ast_macbeth/aMaWall3Hitbox";

static const ALIGN_ASSET(2) char aMaIndicatorSignHitbox[] = "__OTR__ast_macbeth/aMaIndicatorSignHitbox";

static const ALIGN_ASSET(2) char aMaTerrainBumpHitbox[] = "__OTR__ast_macbeth/aMaTerrainBumpHitbox";

static const ALIGN_ASSET(2) char aMaFloor1Hitbox[] = "__OTR__ast_macbeth/aMaFloor1Hitbox";

static const ALIGN_ASSET(2) char aMaFloor2Hitbox[] = "__OTR__ast_macbeth/aMaFloor2Hitbox";

static const ALIGN_ASSET(2) char aMaFloor3Hitbox[] = "__OTR__ast_macbeth/aMaFloor3Hitbox";

static const ALIGN_ASSET(2) char aMaFloor4Hitbox[] = "__OTR__ast_macbeth/aMaFloor4Hitbox";

static const ALIGN_ASSET(2) char aMaFloor5Hitbox[] = "__OTR__ast_macbeth/aMaFloor5Hitbox";

static const ALIGN_ASSET(2) char aMaMaRailroadSwitchHitbox[] = "__OTR__ast_macbeth/aMaMaRailroadSwitchHitbox";

static const ALIGN_ASSET(2) char D_MA_603648C[] = "__OTR__ast_macbeth/D_MA_603648C";

static const ALIGN_ASSET(2) char aMaBoulderHitbox[] = "__OTR__ast_macbeth/aMaBoulderHitbox";

static const ALIGN_ASSET(2) char aMaRailwaySignalHitbox[] = "__OTR__ast_macbeth/aMaRailwaySignalHitbox";

static const ALIGN_ASSET(2) char D_MA_6036520[] = "__OTR__ast_macbeth/D_MA_6036520";

static const ALIGN_ASSET(2) char aMaSwitchTrackHitbox[] = "__OTR__ast_macbeth/aMaSwitchTrackHitbox";

static const ALIGN_ASSET(2) char D_MA_6036668[] = "__OTR__ast_macbeth/D_MA_6036668";

static const ALIGN_ASSET(2) char aMaHorizontalLockBarHitbox[] = "__OTR__ast_macbeth/aMaHorizontalLockBarHitbox";

static const ALIGN_ASSET(2) char aMaVerticalLockBarHitbox[] = "__OTR__ast_macbeth/aMaVerticalLockBarHitbox";

static const ALIGN_ASSET(2) char aMaProximityLightHitbox[] = "__OTR__ast_macbeth/aMaProximityLightHitbox";

static const ALIGN_ASSET(2) char aMaBarrierHitbox[] = "__OTR__ast_macbeth/aMaBarrierHitbox";

static const ALIGN_ASSET(2) char aMaFallingBoulderHitbox[] = "__OTR__ast_macbeth/aMaFallingBoulderHitbox";

static const ALIGN_ASSET(2) char aMaFloor6Hitbox[] = "__OTR__ast_macbeth/aMaFloor6Hitbox";

static const ALIGN_ASSET(2) char aMaActor207Hitbox[] = "__OTR__ast_macbeth/aMaActor207Hitbox";

static const ALIGN_ASSET(2) char D_MA_6036818[] = "__OTR__ast_macbeth/D_MA_6036818";

static const ALIGN_ASSET(2) char aMaGuillotineHousingHitbox[] = "__OTR__ast_macbeth/aMaGuillotineHousingHitbox";

static const ALIGN_ASSET(2) char aMaGuillotineHitbox[] = "__OTR__ast_macbeth/aMaGuillotineHitbox";

static const ALIGN_ASSET(2) char aMaRailroadCartHitbox[] = "__OTR__ast_macbeth/aMaRailroadCartHitbox";

static const ALIGN_ASSET(2) char aMaBombDropHitbox[] = "__OTR__ast_macbeth/aMaBombDropHitbox";

static const ALIGN_ASSET(2) char aMaSpearHitbox[] = "__OTR__ast_macbeth/aMaSpearHitbox";

static const ALIGN_ASSET(2) char aMaShockBoxHitbox[] = "__OTR__ast_macbeth/aMaShockBoxHitbox";

static const char D_MA_60381D8[] = "__OTR__ast_macbeth/D_MA_60381D8";

