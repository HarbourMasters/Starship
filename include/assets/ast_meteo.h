#pragma once

#include "gfx.h"
#include "sf64object.h"
#include "sf64level.h"
#include "sf64event.h"
#include "sf64player.h"
#include "sf64audio_external.h"
#include "sf64mesg.h"

static const ALIGN_ASSET(2) char aMeTitleCardTex[] = "__OTR__ast_meteo/aMeTitleCardTex";

static const ALIGN_ASSET(2) char D_ME_6000A80[] = "__OTR__ast_meteo/D_ME_6000A80";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_AD0[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_AD0";

static const ALIGN_ASSET(2) char D_ME_6000B10[] = "__OTR__ast_meteo/D_ME_6000B10";

static const ALIGN_ASSET(2) char aMeCrusherDL[] = "__OTR__ast_meteo/aMeCrusherDL";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_1BF8[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_1BF8";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_1DF8[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_1DF8";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_1FD8[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_1FD8";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_21D8[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_21D8";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_23A8[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_23A8";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_2578[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_2578";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_2758[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_2758";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_2958[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_2958";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_2B48[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_2B48";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_2D48[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_2D48";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_2F48[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_2F48";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_3148[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_3148";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_3348[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_3348";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_3538[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_3538";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_35D8[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_35D8";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_37D8[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_37D8";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_39A8[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_39A8";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_3A08[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_3A08";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_3BD8[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_3BD8";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_3D68[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_3D68";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_3E98[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_3E98";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_4098[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_4098";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_4298[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_4298";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_4448[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_4448";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_4558[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_4558";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_4638[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_4638";

static const ALIGN_ASSET(2) char D_ME_6004738[] = "__OTR__ast_meteo/D_ME_6004738";

static const ALIGN_ASSET(2) char D_ME_6004F38[] = "__OTR__ast_meteo/D_ME_6004F38";

static const ALIGN_ASSET(2) char D_ME_6005738[] = "__OTR__ast_meteo/D_ME_6005738";

static const ALIGN_ASSET(2) char D_ME_6005F38[] = "__OTR__ast_meteo/D_ME_6005F38";

static const ALIGN_ASSET(2) char D_ME_6006738[] = "__OTR__ast_meteo/D_ME_6006738";

static const ALIGN_ASSET(2) char D_ME_6006F38[] = "__OTR__ast_meteo/D_ME_6006F38";

static const ALIGN_ASSET(2) char D_ME_6006FB8[] = "__OTR__ast_meteo/D_ME_6006FB8";

static const ALIGN_ASSET(2) char D_ME_6007038[] = "__OTR__ast_meteo/D_ME_6007038";

static const ALIGN_ASSET(2) char D_ME_6007838[] = "__OTR__ast_meteo/D_ME_6007838";

static const ALIGN_ASSET(2) char D_ME_60078B8[] = "__OTR__ast_meteo/D_ME_60078B8";

static const ALIGN_ASSET(2) char D_ME_60080C0[] = "__OTR__ast_meteo/D_ME_60080C0";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_8378[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_8378";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_83C8[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_83C8";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_85C8[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_85C8";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_86A8[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_86A8";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_8888[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_8888";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_88B8[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_88B8";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_8918[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_8918";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_8958[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_8958";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_89B8[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_89B8";

static const ALIGN_ASSET(2) char D_ME_6008A18[] = "__OTR__ast_meteo/D_ME_6008A18";

static const ALIGN_ASSET(2) char aMeFlipBot1DL[] = "__OTR__ast_meteo/aMeFlipBot1DL";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_8C78[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_8C78";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_8E78[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_8E78";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_8EA8[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_8EA8";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_8F78[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_8F78";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_8FB8[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_8FB8";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_9198[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_9198";

static const ALIGN_ASSET(2) char D_ME_6009228[] = "__OTR__ast_meteo/D_ME_6009228";

static const ALIGN_ASSET(2) char D_ME_6009A28[] = "__OTR__ast_meteo/D_ME_6009A28";

static const ALIGN_ASSET(2) char D_ME_6009C28[] = "__OTR__ast_meteo/D_ME_6009C28";

static const ALIGN_ASSET(2) char aMeFlipBot2DL[] = "__OTR__ast_meteo/aMeFlipBot2DL";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_9E90[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_9E90";

static const ALIGN_ASSET(2) char aMeBigMeteorDL[] = "__OTR__ast_meteo/aMeBigMeteorDL";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_A0D0[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_A0D0";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_A2B0[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_A2B0";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_A490[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_A490";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_A670[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_A670";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_A850[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_A850";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_AA30[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_AA30";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_AC10[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_AC10";

static const ALIGN_ASSET(2) char aMeMeteor7DL[] = "__OTR__ast_meteo/aMeMeteor7DL";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_AD90[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_AD90";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_AF90[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_AF90";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_B190[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_B190";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_B390[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_B390";

static const ALIGN_ASSET(2) char D_ME_600B540[] = "__OTR__ast_meteo/D_ME_600B540";

static const ALIGN_ASSET(2) char aMeSecretMarker2DL[] = "__OTR__ast_meteo/aMeSecretMarker2DL";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_BDC0[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_BDC0";

static const ALIGN_ASSET(2) char D_ME_600BF30[] = "__OTR__ast_meteo/D_ME_600BF30";

static const ALIGN_ASSET(2) char aMeRockGull2DL[] = "__OTR__ast_meteo/aMeRockGull2DL";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_C1A0[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_C1A0";

static const ALIGN_ASSET(2) char aMeMeteor6DL[] = "__OTR__ast_meteo/aMeMeteor6DL";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_C358[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_C358";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_C548[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_C548";

static const ALIGN_ASSET(2) char aMeRockGull3DL[] = "__OTR__ast_meteo/aMeRockGull3DL";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_C7E0[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_C7E0";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_C9D0[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_C9D0";

static const ALIGN_ASSET(2) char aMeRockGull1DL[] = "__OTR__ast_meteo/aMeRockGull1DL";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_CB30[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_CB30";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_CD30[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_CD30";

static const ALIGN_ASSET(2) char aMeMeteorShower3DL[] = "__OTR__ast_meteo/aMeMeteorShower3DL";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_CDB8[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_CDB8";

static const ALIGN_ASSET(2) char D_ME_600CDE8[] = "__OTR__ast_meteo/D_ME_600CDE8";

static const ALIGN_ASSET(2) char D_ME_600DDF0[] = "__OTR__ast_meteo/D_ME_600DDF0";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_E038[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_E038";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_E078[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_E078";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_E0B8[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_E0B8";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_E0F8[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_E0F8";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_E138[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_E138";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_E178[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_E178";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_E1B8[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_E1B8";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_E1F8[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_E1F8";

static const ALIGN_ASSET(2) char D_ME_600E238[] = "__OTR__ast_meteo/D_ME_600E238";

static const ALIGN_ASSET(2) char D_ME_600F238[] = "__OTR__ast_meteo/D_ME_600F238";

static const ALIGN_ASSET(2) char D_ME_6010238[] = "__OTR__ast_meteo/D_ME_6010238";

static const ALIGN_ASSET(2) char D_ME_6011238[] = "__OTR__ast_meteo/D_ME_6011238";

static const ALIGN_ASSET(2) char D_ME_6012238[] = "__OTR__ast_meteo/D_ME_6012238";

static const ALIGN_ASSET(2) char D_ME_6013238[] = "__OTR__ast_meteo/D_ME_6013238";

static const ALIGN_ASSET(2) char D_ME_6014238[] = "__OTR__ast_meteo/D_ME_6014238";

static const ALIGN_ASSET(2) char D_ME_6015238[] = "__OTR__ast_meteo/D_ME_6015238";

static const ALIGN_ASSET(2) char aMeMeteorShower2DL[] = "__OTR__ast_meteo/aMeMeteorShower2DL";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_16298[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_16298";

static const ALIGN_ASSET(2) char D_ME_60162C8[] = "__OTR__ast_meteo/D_ME_60162C8";

static const ALIGN_ASSET(2) char D_ME_60172C8[] = "__OTR__ast_meteo/D_ME_60172C8";

static const ALIGN_ASSET(2) char aMeMeteorShower1DL[] = "__OTR__ast_meteo/aMeMeteorShower1DL";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_17B28[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_17B28";

static const ALIGN_ASSET(2) char aMeMeteor3DL[] = "__OTR__ast_meteo/aMeMeteor3DL";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_17C98[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_17C98";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_17CC8[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_17CC8";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_17EB8[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_17EB8";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_180A8[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_180A8";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_18288[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_18288";

static const ALIGN_ASSET(2) char aMeLaserCannon2DL[] = "__OTR__ast_meteo/aMeLaserCannon2DL";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_18620[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_18620";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_187A0[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_187A0";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_187E0[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_187E0";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_188A0[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_188A0";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_18920[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_18920";

static const ALIGN_ASSET(2) char aMeMeteor5DL[] = "__OTR__ast_meteo/aMeMeteor5DL";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_189F0[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_189F0";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_18BD0[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_18BD0";

static const ALIGN_ASSET(2) char aMeMeteor1DL[] = "__OTR__ast_meteo/aMeMeteor1DL";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_18D18[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_18D18";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_18F08[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_18F08";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_190F8[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_190F8";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_192F8[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_192F8";

static const ALIGN_ASSET(2) char aMeMeteor4DL[] = "__OTR__ast_meteo/aMeMeteor4DL";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_194E0[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_194E0";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_196D0[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_196D0";

static const ALIGN_ASSET(2) char D_ME_6019880[] = "__OTR__ast_meteo/D_ME_6019880";

static const ALIGN_ASSET(2) char D_ME_601A080[] = "__OTR__ast_meteo/D_ME_601A080";

static const ALIGN_ASSET(2) char aMeSecretMarker1DL[] = "__OTR__ast_meteo/aMeSecretMarker1DL";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_1A988[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_1A988";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_1AB78[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_1AB78";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_1AD58[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_1AD58";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_1ADF8[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_1ADF8";

static const ALIGN_ASSET(2) char aMeMeteoTunnelDL[] = "__OTR__ast_meteo/aMeMeteoTunnelDL";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_1B2B0[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_1B2B0";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_1B4B0[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_1B4B0";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_1B6B0[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_1B6B0";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_1B8B0[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_1B8B0";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_1BAB0[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_1BAB0";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_1BCB0[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_1BCB0";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_1BEB0[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_1BEB0";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_1C0B0[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_1C0B0";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_1C2A0[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_1C2A0";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_1C480[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_1C480";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_1C680[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_1C680";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_1C880[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_1C880";

static const ALIGN_ASSET(2) char D_ME_601C8E0[] = "__OTR__ast_meteo/D_ME_601C8E0";

static const ALIGN_ASSET(2) char D_ME_601D800[] = "__OTR__ast_meteo/D_ME_601D800";

static const ALIGN_ASSET(2) char aMeHopBotAnim[] = "__OTR__ast_meteo/aMeHopBotAnim";

static const ALIGN_ASSET(2) char aMeHopBotSkel[] = "__OTR__ast_meteo/aMeHopBotSkel";

static const ALIGN_ASSET(2) char D_ME_601EA00[] = "__OTR__ast_meteo/D_ME_601EA00";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_1EA58[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_1EA58";

static const ALIGN_ASSET(2) char D_ME_601EA98[] = "__OTR__ast_meteo/D_ME_601EA98";

static const ALIGN_ASSET(2) char aMeMeteor2DL[] = "__OTR__ast_meteo/aMeMeteor2DL";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_1F478[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_1F478";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_1F668[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_1F668";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_1F698[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_1F698";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_1F6D8[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_1F6D8";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_1F718[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_1F718";

static const ALIGN_ASSET(2) char D_ME_601F778[] = "__OTR__ast_meteo/D_ME_601F778";

static const ALIGN_ASSET(2) char D_ME_601FF80[] = "__OTR__ast_meteo/D_ME_601FF80";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_1FFD8[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_1FFD8";

static const ALIGN_ASSET(2) char D_ME_6020008[] = "__OTR__ast_meteo/D_ME_6020008";

static const ALIGN_ASSET(2) char aMeCorneriaBgDL[] = "__OTR__ast_meteo/aMeCorneriaBgDL";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_208A0[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_208A0";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_208E0[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_208E0";

static const ALIGN_ASSET(2) char aMeCorneriaBg1Tex[] = "__OTR__ast_meteo/aMeCorneriaBg1Tex";

static const ALIGN_ASSET(2) char aMeCorneriaBg2Tex[] = "__OTR__ast_meteo/aMeCorneriaBg2Tex";

static const ALIGN_ASSET(2) char aMeLaserCannon1DL[] = "__OTR__ast_meteo/aMeLaserCannon1DL";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_22AB0[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_22AB0";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_22C30[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_22C30";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_22E20[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_22E20";

static const ALIGN_ASSET(2) char D_ME_6022E50[] = "__OTR__ast_meteo/D_ME_6022E50";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_22F78[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_22F78";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_23138[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_23138";

static const ALIGN_ASSET(2) char D_ME_60231C0[] = "__OTR__ast_meteo/D_ME_60231C0";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_23230[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_23230";

static const ALIGN_ASSET(2) char D_ME_6023290[] = "__OTR__ast_meteo/D_ME_6023290";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_23300[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_23300";

static const ALIGN_ASSET(2) char D_ME_6023360[] = "__OTR__ast_meteo/D_ME_6023360";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_23488[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_23488";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_23668[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_23668";

static const ALIGN_ASSET(2) char D_ME_60236F0[] = "__OTR__ast_meteo/D_ME_60236F0";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_23748[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_23748";

static const ALIGN_ASSET(2) char D_ME_6023788[] = "__OTR__ast_meteo/D_ME_6023788";

static const ALIGN_ASSET(2) char D_ME_6023810[] = "__OTR__ast_meteo/D_ME_6023810";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_23868[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_23868";

static const ALIGN_ASSET(2) char D_ME_60238A8[] = "__OTR__ast_meteo/D_ME_60238A8";

static const ALIGN_ASSET(2) char D_ME_60240B0[] = "__OTR__ast_meteo/D_ME_60240B0";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_242C0[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_242C0";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_243E0[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_243E0";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_24580[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_24580";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_24660[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_24660";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_24860[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_24860";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_248F0[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_248F0";

static const ALIGN_ASSET(2) char D_ME_6024AD0[] = "__OTR__ast_meteo/D_ME_6024AD0";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_24B28[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_24B28";

static const ALIGN_ASSET(2) char aMeMolarRockDL[] = "__OTR__ast_meteo/aMeMolarRockDL";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_24D10[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_24D10";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_24F10[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_24F10";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_25110[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_25110";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_252F0[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_252F0";

static const ALIGN_ASSET(2) char D_ME_6025350[] = "__OTR__ast_meteo/D_ME_6025350";

static const ALIGN_ASSET(2) char aMeMeteoBallDL[] = "__OTR__ast_meteo/aMeMeteoBallDL";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_25BA8[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_25BA8";

static const ALIGN_ASSET(2) char D_ME_6025BE8[] = "__OTR__ast_meteo/D_ME_6025BE8";

static const ALIGN_ASSET(2) char D_ME_60263F0[] = "__OTR__ast_meteo/D_ME_60263F0";

static const ALIGN_ASSET(2) char ast_meteo_seg6_vtx_26448[] = "__OTR__ast_meteo/ast_meteo_seg6_vtx_26448";

static const ALIGN_ASSET(2) char D_ME_6026478[] = "__OTR__ast_meteo/D_ME_6026478";

static const ALIGN_ASSET(2) char D_ME_6026C80[] = "__OTR__ast_meteo/D_ME_6026C80";

static const ALIGN_ASSET(2) char D_ME_6026CC4[] = "__OTR__ast_meteo/D_ME_6026CC4";

static const ALIGN_ASSET(2) char D_ME_602B148[] = "__OTR__ast_meteo/D_ME_602B148";

static const char D_ME_602F3AC[] = "__OTR__ast_meteo/D_ME_602F3AC";

static const ALIGN_ASSET(2) char aMeFlipBotHitbox[] = "__OTR__ast_meteo/aMeFlipBotHitbox";

static const ALIGN_ASSET(2) char D_ME_602F638[] = "__OTR__ast_meteo/D_ME_602F638";

static const ALIGN_ASSET(2) char aMeMeteoBallHitbox[] = "__OTR__ast_meteo/aMeMeteoBallHitbox";

static const ALIGN_ASSET(2) char aMeHopBotHitbox[] = "__OTR__ast_meteo/aMeHopBotHitbox";

static const ALIGN_ASSET(2) char aMeMeteor1Hitbox[] = "__OTR__ast_meteo/aMeMeteor1Hitbox";

static const ALIGN_ASSET(2) char aMeMeteor2Hitbox[] = "__OTR__ast_meteo/aMeMeteor2Hitbox";

static const ALIGN_ASSET(2) char aMeLaserCannon1Hitbox[] = "__OTR__ast_meteo/aMeLaserCannon1Hitbox";

static const ALIGN_ASSET(2) char aMeLaserCannon2Hitbox[] = "__OTR__ast_meteo/aMeLaserCannon2Hitbox";

static const ALIGN_ASSET(2) char aMeCrusherHitbox[] = "__OTR__ast_meteo/aMeCrusherHitbox";

static const ALIGN_ASSET(2) char aMeCrusherShieldHitbox[] = "__OTR__ast_meteo/aMeCrusherShieldHitbox";

static const ALIGN_ASSET(2) char D_ME_602FA9C[] = "__OTR__ast_meteo/D_ME_602FA9C";

static const ALIGN_ASSET(2) char D_ME_60300C8[] = "__OTR__ast_meteo/D_ME_60300C8";

static const ALIGN_ASSET(2) char D_ME_6030208[] = "__OTR__ast_meteo/D_ME_6030208";

static const ALIGN_ASSET(2) char D_ME_6030550[] = "__OTR__ast_meteo/D_ME_6030550";

static const ALIGN_ASSET(2) char D_ME_60305DC[] = "__OTR__ast_meteo/D_ME_60305DC";

static const ALIGN_ASSET(2) char D_ME_603184C[] = "__OTR__ast_meteo/D_ME_603184C";

