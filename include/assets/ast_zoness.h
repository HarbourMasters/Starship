#pragma once

#include "gfx.h"
#include "sf64object.h"
#include "sf64level.h"
#include "sf64event.h"
#include "sf64player.h"
#include "sf64audio_external.h"
#include "sf64mesg.h"

static const ALIGN_ASSET(2) char aZoTitleCardTex[] = "__OTR__ast_zoness/aZoTitleCardTex";

static const ALIGN_ASSET(2) char D_ZO_6000C40[] = "__OTR__ast_zoness/D_ZO_6000C40";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_D28[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_D28";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_D88[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_D88";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_E48[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_E48";

static const ALIGN_ASSET(2) char D_ZO_6000E98[] = "__OTR__ast_zoness/D_ZO_6000E98";

static const ALIGN_ASSET(2) char D_ZO_6001098[] = "__OTR__ast_zoness/D_ZO_6001098";

static const ALIGN_ASSET(2) char aZoDodoraHeadDL[] = "__OTR__ast_zoness/aZoDodoraHeadDL";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_14D0[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_14D0";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1510[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1510";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1560[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1560";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_15D0[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_15D0";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1670[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1670";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1750[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1750";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_17C0[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_17C0";

static const ALIGN_ASSET(2) char D_ZO_6001810[] = "__OTR__ast_zoness/D_ZO_6001810";

static const ALIGN_ASSET(2) char D_ZO_6002010[] = "__OTR__ast_zoness/D_ZO_6002010";

static const ALIGN_ASSET(2) char D_ZO_6002210[] = "__OTR__ast_zoness/D_ZO_6002210";

static const ALIGN_ASSET(2) char D_ZO_6002410[] = "__OTR__ast_zoness/D_ZO_6002410";

static const ALIGN_ASSET(2) char D_ZO_6002610[] = "__OTR__ast_zoness/D_ZO_6002610";

static const ALIGN_ASSET(2) char D_ZO_6002810[] = "__OTR__ast_zoness/D_ZO_6002810";

static const ALIGN_ASSET(2) char D_ZO_6002A10[] = "__OTR__ast_zoness/D_ZO_6002A10";

static const ALIGN_ASSET(2) char aZoRadarBuoyDL[] = "__OTR__ast_zoness/aZoRadarBuoyDL";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_2F08[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_2F08";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_30A8[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_30A8";

static const ALIGN_ASSET(2) char D_ZO_6003288[] = "__OTR__ast_zoness/D_ZO_6003288";

static const ALIGN_ASSET(2) char D_ZO_6003488[] = "__OTR__ast_zoness/D_ZO_6003488";

static const ALIGN_ASSET(2) char D_ZO_6003690[] = "__OTR__ast_zoness/D_ZO_6003690";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_37B0[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_37B0";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_3870[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_3870";

static const ALIGN_ASSET(2) char D_ZO_6003930[] = "__OTR__ast_zoness/D_ZO_6003930";

static const ALIGN_ASSET(2) char D_ZO_6003B30[] = "__OTR__ast_zoness/D_ZO_6003B30";

static const ALIGN_ASSET(2) char D_ZO_6004330[] = "__OTR__ast_zoness/D_ZO_6004330";

static const ALIGN_ASSET(2) char D_ZO_6004380[] = "__OTR__ast_zoness/D_ZO_6004380";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_4418[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_4418";

static const ALIGN_ASSET(2) char D_ZO_6004450[] = "__OTR__ast_zoness/D_ZO_6004450";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_4610[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_4610";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_4800[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_4800";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_48B0[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_48B0";

static const ALIGN_ASSET(2) char D_ZO_6004970[] = "__OTR__ast_zoness/D_ZO_6004970";

static const ALIGN_ASSET(2) char D_ZO_6004A70[] = "__OTR__ast_zoness/D_ZO_6004A70";

static const ALIGN_ASSET(2) char D_ZO_6004B00[] = "__OTR__ast_zoness/D_ZO_6004B00";

static const ALIGN_ASSET(2) char aZoPatrolBoatDL[] = "__OTR__ast_zoness/aZoPatrolBoatDL";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_4FD8[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_4FD8";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_5018[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_5018";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_5208[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_5208";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_5238[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_5238";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_5418[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_5418";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_54B8[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_54B8";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_56B8[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_56B8";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_5718[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_5718";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_5918[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_5918";

static const ALIGN_ASSET(2) char D_ZO_6005958[] = "__OTR__ast_zoness/D_ZO_6005958";

static const ALIGN_ASSET(2) char D_ZO_6005B58[] = "__OTR__ast_zoness/D_ZO_6005B58";

static const ALIGN_ASSET(2) char D_ZO_6006360[] = "__OTR__ast_zoness/D_ZO_6006360";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_66E0[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_66E0";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_67B0[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_67B0";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_6830[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_6830";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_6A10[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_6A10";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_6C10[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_6C10";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_6C40[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_6C40";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_6D10[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_6D10";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_6D40[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_6D40";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_6EE0[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_6EE0";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_6FC0[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_6FC0";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_71C0[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_71C0";

static const ALIGN_ASSET(2) char D_ZO_6007230[] = "__OTR__ast_zoness/D_ZO_6007230";

static const ALIGN_ASSET(2) char D_ZO_6007430[] = "__OTR__ast_zoness/D_ZO_6007430";

static const ALIGN_ASSET(2) char D_ZO_6007C30[] = "__OTR__ast_zoness/D_ZO_6007C30";

static const ALIGN_ASSET(2) char D_ZO_6007E30[] = "__OTR__ast_zoness/D_ZO_6007E30";

static const ALIGN_ASSET(2) char D_ZO_6008030[] = "__OTR__ast_zoness/D_ZO_6008030";

static const ALIGN_ASSET(2) char D_ZO_6008230[] = "__OTR__ast_zoness/D_ZO_6008230";

static const ALIGN_ASSET(2) char D_ZO_6008430[] = "__OTR__ast_zoness/D_ZO_6008430";

static const ALIGN_ASSET(2) char D_ZO_6008630[] = "__OTR__ast_zoness/D_ZO_6008630";

static const ALIGN_ASSET(2) char D_ZO_6008830[] = "__OTR__ast_zoness/D_ZO_6008830";

static const ALIGN_ASSET(2) char D_ZO_6009ED0[] = "__OTR__ast_zoness/D_ZO_6009ED0";

static const ALIGN_ASSET(2) char D_ZO_600B0E0[] = "__OTR__ast_zoness/D_ZO_600B0E0";

static const ALIGN_ASSET(2) char D_ZO_600C780[] = "__OTR__ast_zoness/D_ZO_600C780";

static const ALIGN_ASSET(2) char D_ZO_600D990[] = "__OTR__ast_zoness/D_ZO_600D990";

static const ALIGN_ASSET(2) char aZoBirdAnim[] = "__OTR__ast_zoness/aZoBirdAnim";

static const ALIGN_ASSET(2) char aZoBirdSkel[] = "__OTR__ast_zoness/aZoBirdSkel";

static const ALIGN_ASSET(2) char aZoOilRig3DL[] = "__OTR__ast_zoness/aZoOilRig3DL";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_E950[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_E950";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_EB50[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_EB50";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_EC10[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_EC10";

static const ALIGN_ASSET(2) char aZoOilRig2DL[] = "__OTR__ast_zoness/aZoOilRig2DL";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_EE58[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_EE58";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_F058[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_F058";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_F258[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_F258";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_F298[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_F298";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_F498[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_F498";

static const ALIGN_ASSET(2) char aZoOilRig1DL[] = "__OTR__ast_zoness/aZoOilRig1DL";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_F718[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_F718";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_F918[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_F918";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_FB18[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_FB18";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_FCD8[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_FCD8";

static const ALIGN_ASSET(2) char D_ZO_600FE58[] = "__OTR__ast_zoness/D_ZO_600FE58";

static const ALIGN_ASSET(2) char D_ZO_6010658[] = "__OTR__ast_zoness/D_ZO_6010658";

static const ALIGN_ASSET(2) char D_ZO_6010E58[] = "__OTR__ast_zoness/D_ZO_6010E58";

static const ALIGN_ASSET(2) char D_ZO_6011660[] = "__OTR__ast_zoness/D_ZO_6011660";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_117C8[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_117C8";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_11828[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_11828";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_11868[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_11868";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_118C8[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_118C8";

static const ALIGN_ASSET(2) char D_ZO_6011928[] = "__OTR__ast_zoness/D_ZO_6011928";

static const ALIGN_ASSET(2) char D_ZO_6012128[] = "__OTR__ast_zoness/D_ZO_6012128";

static const ALIGN_ASSET(2) char D_ZO_6012930[] = "__OTR__ast_zoness/D_ZO_6012930";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_12A98[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_12A98";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_12C38[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_12C38";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_12E38[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_12E38";

static const ALIGN_ASSET(2) char D_ZO_6013010[] = "__OTR__ast_zoness/D_ZO_6013010";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_13108[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_13108";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_13188[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_13188";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_13228[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_13228";

static const ALIGN_ASSET(2) char D_ZO_6013330[] = "__OTR__ast_zoness/D_ZO_6013330";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_133A0[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_133A0";

static const ALIGN_ASSET(2) char D_ZO_6013480[] = "__OTR__ast_zoness/D_ZO_6013480";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_134D0[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_134D0";

static const ALIGN_ASSET(2) char D_ZO_6013510[] = "__OTR__ast_zoness/D_ZO_6013510";

static const ALIGN_ASSET(2) char D_ZO_6014510[] = "__OTR__ast_zoness/D_ZO_6014510";

static const ALIGN_ASSET(2) char D_ZO_6015430[] = "__OTR__ast_zoness/D_ZO_6015430";

static const ALIGN_ASSET(2) char D_ZO_6016350[] = "__OTR__ast_zoness/D_ZO_6016350";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_163A8[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_163A8";

static const ALIGN_ASSET(2) char D_ZO_60163E0[] = "__OTR__ast_zoness/D_ZO_60163E0";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_164B0[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_164B0";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_16510[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_16510";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_165A0[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_165A0";

static const ALIGN_ASSET(2) char D_ZO_60165D0[] = "__OTR__ast_zoness/D_ZO_60165D0";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_166B8[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_166B8";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_16728[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_16728";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_167F8[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_167F8";

static const ALIGN_ASSET(2) char D_ZO_6016880[] = "__OTR__ast_zoness/D_ZO_6016880";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_16968[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_16968";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_169C8[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_169C8";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_16AE8[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_16AE8";

static const ALIGN_ASSET(2) char D_ZO_6016B50[] = "__OTR__ast_zoness/D_ZO_6016B50";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_16C30[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_16C30";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_16C90[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_16C90";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_16D30[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_16D30";

static const ALIGN_ASSET(2) char D_ZO_6016D90[] = "__OTR__ast_zoness/D_ZO_6016D90";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_16DE8[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_16DE8";

static const ALIGN_ASSET(2) char D_ZO_6016E30[] = "__OTR__ast_zoness/D_ZO_6016E30";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_16E88[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_16E88";

static const ALIGN_ASSET(2) char D_ZO_6016EC8[] = "__OTR__ast_zoness/D_ZO_6016EC8";

static const ALIGN_ASSET(2) char D_ZO_60176D0[] = "__OTR__ast_zoness/D_ZO_60176D0";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_17728[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_17728";

static const ALIGN_ASSET(2) char D_ZO_6017770[] = "__OTR__ast_zoness/D_ZO_6017770";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_177C8[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_177C8";

static const ALIGN_ASSET(2) char D_ZO_6017810[] = "__OTR__ast_zoness/D_ZO_6017810";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_17868[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_17868";

static const ALIGN_ASSET(2) char D_ZO_60178B0[] = "__OTR__ast_zoness/D_ZO_60178B0";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_17908[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_17908";

static const ALIGN_ASSET(2) char aZoBallDL[] = "__OTR__ast_zoness/aZoBallDL";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_179A8[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_179A8";

static const ALIGN_ASSET(2) char D_ZO_60179D8[] = "__OTR__ast_zoness/D_ZO_60179D8";

static const ALIGN_ASSET(2) char D_ZO_60181E0[] = "__OTR__ast_zoness/D_ZO_60181E0";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_18270[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_18270";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_182B0[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_182B0";

static const ALIGN_ASSET(2) char D_ZO_60182E0[] = "__OTR__ast_zoness/D_ZO_60182E0";

static const ALIGN_ASSET(2) char D_ZO_6018550[] = "__OTR__ast_zoness/D_ZO_6018550";

static const ALIGN_ASSET(2) char D_ZO_601863C[] = "__OTR__ast_zoness/D_ZO_601863C";

static const ALIGN_ASSET(2) char D_ZO_6018660[] = "__OTR__ast_zoness/D_ZO_6018660";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_186B8[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_186B8";

static const ALIGN_ASSET(2) char D_ZO_60186E8[] = "__OTR__ast_zoness/D_ZO_60186E8";

static const ALIGN_ASSET(2) char D_ZO_6018AF0[] = "__OTR__ast_zoness/D_ZO_6018AF0";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_18B48[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_18B48";

static const ALIGN_ASSET(2) char D_ZO_6018B78[] = "__OTR__ast_zoness/D_ZO_6018B78";

static const ALIGN_ASSET(2) char D_ZO_6018C80[] = "__OTR__ast_zoness/D_ZO_6018C80";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_18D38[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_18D38";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_18DB8[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_18DB8";

static const ALIGN_ASSET(2) char D_ZO_6018E80[] = "__OTR__ast_zoness/D_ZO_6018E80";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_18F20[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_18F20";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_18FB0[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_18FB0";

static const ALIGN_ASSET(2) char D_ZO_6019040[] = "__OTR__ast_zoness/D_ZO_6019040";

static const ALIGN_ASSET(2) char D_ZO_60195EC[] = "__OTR__ast_zoness/D_ZO_60195EC";

static const ALIGN_ASSET(2) char D_ZO_6019738[] = "__OTR__ast_zoness/D_ZO_6019738";

static const ALIGN_ASSET(2) char D_ZO_601996C[] = "__OTR__ast_zoness/D_ZO_601996C";

static const ALIGN_ASSET(2) char aZoSarumarineSkel[] = "__OTR__ast_zoness/aZoSarumarineSkel";

static const ALIGN_ASSET(2) char D_ZO_6019EB0[] = "__OTR__ast_zoness/D_ZO_6019EB0";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_19F08[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_19F08";

static const ALIGN_ASSET(2) char ast_zoness_seg6_gfx_19F50[] = "__OTR__ast_zoness/ast_zoness_seg6_gfx_19F50";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1A0A0[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1A0A0";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1A170[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1A170";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1A230[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1A230";

static const ALIGN_ASSET(2) char D_ZO_601A340[] = "__OTR__ast_zoness/D_ZO_601A340";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1A410[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1A410";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1A450[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1A450";

static const ALIGN_ASSET(2) char ast_zoness_seg6_gfx_1A560[] = "__OTR__ast_zoness/ast_zoness_seg6_gfx_1A560";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1A5C8[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1A5C8";

static const ALIGN_ASSET(2) char ast_zoness_seg6_gfx_1A690[] = "__OTR__ast_zoness/ast_zoness_seg6_gfx_1A690";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1A748[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1A748";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1A788[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1A788";

static const ALIGN_ASSET(2) char D_ZO_601AA48[] = "__OTR__ast_zoness/D_ZO_601AA48";

static const ALIGN_ASSET(2) char D_ZO_601AB14[] = "__OTR__ast_zoness/D_ZO_601AB14";

static const ALIGN_ASSET(2) char D_ZO_601AFB8[] = "__OTR__ast_zoness/D_ZO_601AFB8";

static const ALIGN_ASSET(2) char D_ZO_601B184[] = "__OTR__ast_zoness/D_ZO_601B184";

static const ALIGN_ASSET(2) char D_ZO_601B1C0[] = "__OTR__ast_zoness/D_ZO_601B1C0";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1B260[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1B260";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1B2F0[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1B2F0";

static const ALIGN_ASSET(2) char D_ZO_601B3B0[] = "__OTR__ast_zoness/D_ZO_601B3B0";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1B450[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1B450";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1B4E0[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1B4E0";

static const ALIGN_ASSET(2) char D_ZO_601B570[] = "__OTR__ast_zoness/D_ZO_601B570";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1B610[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1B610";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1B680[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1B680";

static const ALIGN_ASSET(2) char D_ZO_601B710[] = "__OTR__ast_zoness/D_ZO_601B710";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1B7B0[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1B7B0";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1B840[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1B840";

static const ALIGN_ASSET(2) char D_ZO_601B8F0[] = "__OTR__ast_zoness/D_ZO_601B8F0";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1B990[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1B990";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1BA20[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1BA20";

static const ALIGN_ASSET(2) char D_ZO_601BAD0[] = "__OTR__ast_zoness/D_ZO_601BAD0";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1BB38[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1BB38";

static const ALIGN_ASSET(2) char D_ZO_601BBB8[] = "__OTR__ast_zoness/D_ZO_601BBB8";

static const ALIGN_ASSET(2) char D_ZO_601BCC0[] = "__OTR__ast_zoness/D_ZO_601BCC0";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1BD80[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1BD80";

static const ALIGN_ASSET(2) char ast_zoness_seg6_gfx_1BF80[] = "__OTR__ast_zoness/ast_zoness_seg6_gfx_1BF80";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1C038[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1C038";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1C098[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1C098";

static const ALIGN_ASSET(2) char ast_zoness_seg6_gfx_1C0D0[] = "__OTR__ast_zoness/ast_zoness_seg6_gfx_1C0D0";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1C1B0[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1C1B0";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1C350[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1C350";

static const ALIGN_ASSET(2) char D_ZO_601C390[] = "__OTR__ast_zoness/D_ZO_601C390";

static const ALIGN_ASSET(2) char D_ZO_601C590[] = "__OTR__ast_zoness/D_ZO_601C590";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1C700[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1C700";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1C750[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1C750";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1C7A0[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1C7A0";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1C800[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1C800";

static const ALIGN_ASSET(2) char D_ZO_601C8E0[] = "__OTR__ast_zoness/D_ZO_601C8E0";

static const ALIGN_ASSET(2) char D_ZO_601D0E0[] = "__OTR__ast_zoness/D_ZO_601D0E0";

static const ALIGN_ASSET(2) char D_ZO_601D2E0[] = "__OTR__ast_zoness/D_ZO_601D2E0";

static const ALIGN_ASSET(2) char ast_zoness_seg6_gfx_1D4E0[] = "__OTR__ast_zoness/ast_zoness_seg6_gfx_1D4E0";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1D548[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1D548";

static const ALIGN_ASSET(2) char D_ZO_601D5B0[] = "__OTR__ast_zoness/D_ZO_601D5B0";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1D618[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1D618";

static const ALIGN_ASSET(2) char D_ZO_601D680[] = "__OTR__ast_zoness/D_ZO_601D680";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1D748[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1D748";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1D808[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1D808";

static const ALIGN_ASSET(2) char ast_zoness_seg6_gfx_1D8D0[] = "__OTR__ast_zoness/ast_zoness_seg6_gfx_1D8D0";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1DBC8[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1DBC8";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1DDB8[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1DDB8";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1DE48[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1DE48";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1DE88[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1DE88";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1DF68[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1DF68";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1E008[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1E008";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1E048[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1E048";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1E248[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1E248";

static const ALIGN_ASSET(2) char ast_zoness_seg6_gfx_1E290[] = "__OTR__ast_zoness/ast_zoness_seg6_gfx_1E290";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1E438[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1E438";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1E4D8[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1E4D8";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1E578[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1E578";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1E5C8[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1E5C8";

static const ALIGN_ASSET(2) char D_ZO_601E618[] = "__OTR__ast_zoness/D_ZO_601E618";

static const ALIGN_ASSET(2) char ast_zoness_seg6_gfx_1E820[] = "__OTR__ast_zoness/ast_zoness_seg6_gfx_1E820";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1E9C8[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1E9C8";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1EB38[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1EB38";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1EB78[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1EB78";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1EC78[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1EC78";

static const ALIGN_ASSET(2) char ast_zoness_seg6_gfx_1ED50[] = "__OTR__ast_zoness/ast_zoness_seg6_gfx_1ED50";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1EE28[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1EE28";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1EF08[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1EF08";

static const ALIGN_ASSET(2) char ast_zoness_seg6_gfx_1EF70[] = "__OTR__ast_zoness/ast_zoness_seg6_gfx_1EF70";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1F020[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1F020";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1F200[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1F200";

static const ALIGN_ASSET(2) char D_ZO_601F260[] = "__OTR__ast_zoness/D_ZO_601F260";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1F300[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1F300";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1F360[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1F360";

static const ALIGN_ASSET(2) char D_ZO_601F420[] = "__OTR__ast_zoness/D_ZO_601F420";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1F4D8[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1F4D8";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1F558[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1F558";

static const ALIGN_ASSET(2) char D_ZO_601F620[] = "__OTR__ast_zoness/D_ZO_601F620";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1F6D8[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1F6D8";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1F758[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1F758";

static const ALIGN_ASSET(2) char aZoSarumarinePeriscopeAnim[] = "__OTR__ast_zoness/aZoSarumarinePeriscopeAnim";

static const ALIGN_ASSET(2) char aZoSarumarinePeriscopeSkel[] = "__OTR__ast_zoness/aZoSarumarinePeriscopeSkel";

static const ALIGN_ASSET(2) char D_ZO_601F940[] = "__OTR__ast_zoness/D_ZO_601F940";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1F9E8[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1F9E8";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1FAA8[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1FAA8";

static const ALIGN_ASSET(2) char D_ZO_601FBC4[] = "__OTR__ast_zoness/D_ZO_601FBC4";

static const ALIGN_ASSET(2) char aZoBarrierSkel[] = "__OTR__ast_zoness/aZoBarrierSkel";

static const ALIGN_ASSET(2) char aZoIslandDL[] = "__OTR__ast_zoness/aZoIslandDL";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1FDC0[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1FDC0";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_1FFC0[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_1FFC0";

static const ALIGN_ASSET(2) char D_ZO_60201B0[] = "__OTR__ast_zoness/D_ZO_60201B0";

static const ALIGN_ASSET(2) char D_ZO_60209B0[] = "__OTR__ast_zoness/D_ZO_60209B0";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_20A50[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_20A50";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_20AE0[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_20AE0";

static const ALIGN_ASSET(2) char D_ZO_6020B70[] = "__OTR__ast_zoness/D_ZO_6020B70";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_20C10[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_20C10";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_20CA0[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_20CA0";

static const ALIGN_ASSET(2) char D_ZO_6020D50[] = "__OTR__ast_zoness/D_ZO_6020D50";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_20DF0[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_20DF0";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_20E80[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_20E80";

static const ALIGN_ASSET(2) char D_ZO_6020F10[] = "__OTR__ast_zoness/D_ZO_6020F10";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_20FB8[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_20FB8";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_210A8[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_210A8";

static const ALIGN_ASSET(2) char D_ZO_6021100[] = "__OTR__ast_zoness/D_ZO_6021100";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_211A0[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_211A0";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_21260[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_21260";

static const ALIGN_ASSET(2) char D_ZO_60212B0[] = "__OTR__ast_zoness/D_ZO_60212B0";

static const ALIGN_ASSET(2) char D_ZO_60214B0[] = "__OTR__ast_zoness/D_ZO_60214B0";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_21568[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_21568";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_215C8[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_215C8";

static const ALIGN_ASSET(2) char D_ZO_60216A8[] = "__OTR__ast_zoness/D_ZO_60216A8";

static const ALIGN_ASSET(2) char D_ZO_6021ABC[] = "__OTR__ast_zoness/D_ZO_6021ABC";

static const ALIGN_ASSET(2) char D_ZO_6021B88[] = "__OTR__ast_zoness/D_ZO_6021B88";

static const ALIGN_ASSET(2) char D_ZO_6021BB0[] = "__OTR__ast_zoness/D_ZO_6021BB0";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_21C08[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_21C08";

static const ALIGN_ASSET(2) char D_ZO_6021C50[] = "__OTR__ast_zoness/D_ZO_6021C50";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_21CA8[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_21CA8";

static const ALIGN_ASSET(2) char D_ZO_6021CE0[] = "__OTR__ast_zoness/D_ZO_6021CE0";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_21D38[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_21D38";

static const ALIGN_ASSET(2) char D_ZO_6021D80[] = "__OTR__ast_zoness/D_ZO_6021D80";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_21DD8[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_21DD8";

static const ALIGN_ASSET(2) char D_ZO_6021E20[] = "__OTR__ast_zoness/D_ZO_6021E20";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_21F00[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_21F00";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_21FB0[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_21FB0";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_22050[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_22050";

static const ALIGN_ASSET(2) char D_ZO_60220A0[] = "__OTR__ast_zoness/D_ZO_60220A0";

static const ALIGN_ASSET(2) char D_ZO_60222A0[] = "__OTR__ast_zoness/D_ZO_60222A0";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_22438[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_22438";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_22628[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_22628";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_22718[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_22718";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_22748[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_22748";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_227A8[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_227A8";

static const ALIGN_ASSET(2) char D_ZO_60227D8[] = "__OTR__ast_zoness/D_ZO_60227D8";

static const ALIGN_ASSET(2) char D_ZO_60229D8[] = "__OTR__ast_zoness/D_ZO_60229D8";

static const ALIGN_ASSET(2) char D_ZO_6022BE0[] = "__OTR__ast_zoness/D_ZO_6022BE0";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_22CA8[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_22CA8";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_22D08[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_22D08";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_22D38[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_22D38";

static const ALIGN_ASSET(2) char D_ZO_6022D70[] = "__OTR__ast_zoness/D_ZO_6022D70";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_22E38[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_22E38";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_22E98[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_22E98";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_22EC8[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_22EC8";

static const ALIGN_ASSET(2) char D_ZO_6022F00[] = "__OTR__ast_zoness/D_ZO_6022F00";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_22FC8[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_22FC8";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_23028[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_23028";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_23058[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_23058";

static const ALIGN_ASSET(2) char D_ZO_6023088[] = "__OTR__ast_zoness/D_ZO_6023088";

static const ALIGN_ASSET(2) char D_ZO_6023288[] = "__OTR__ast_zoness/D_ZO_6023288";

static const ALIGN_ASSET(2) char D_ZO_6023488[] = "__OTR__ast_zoness/D_ZO_6023488";

static const ALIGN_ASSET(2) char D_ZO_6023690[] = "__OTR__ast_zoness/D_ZO_6023690";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_236E8[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_236E8";

static const ALIGN_ASSET(2) char aZoDodoraTailDL[] = "__OTR__ast_zoness/aZoDodoraTailDL";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_23790[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_23790";

static const ALIGN_ASSET(2) char D_ZO_60237E0[] = "__OTR__ast_zoness/D_ZO_60237E0";

static const ALIGN_ASSET(2) char aZoDodoraBodyDL[] = "__OTR__ast_zoness/aZoDodoraBodyDL";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_23B48[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_23B48";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_23C28[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_23C28";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_23C98[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_23C98";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_23D08[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_23D08";

static const ALIGN_ASSET(2) char D_ZO_6023D50[] = "__OTR__ast_zoness/D_ZO_6023D50";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_23DD8[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_23DD8";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_23FB8[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_23FB8";

static const ALIGN_ASSET(2) char D_ZO_6024018[] = "__OTR__ast_zoness/D_ZO_6024018";

static const ALIGN_ASSET(2) char D_ZO_6024220[] = "__OTR__ast_zoness/D_ZO_6024220";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_24278[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_24278";

static const ALIGN_ASSET(2) char D_ZO_60242B8[] = "__OTR__ast_zoness/D_ZO_60242B8";

static const ALIGN_ASSET(2) char aZoRockDL[] = "__OTR__ast_zoness/aZoRockDL";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_24B70[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_24B70";

static const ALIGN_ASSET(2) char D_ZO_6024D60[] = "__OTR__ast_zoness/D_ZO_6024D60";

static const ALIGN_ASSET(2) char ast_zoness_seg6_gfx_25560[] = "__OTR__ast_zoness/ast_zoness_seg6_gfx_25560";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_255D8[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_255D8";

static const ALIGN_ASSET(2) char D_ZO_6025658[] = "__OTR__ast_zoness/D_ZO_6025658";

static const ALIGN_ASSET(2) char D_ZO_6025E60[] = "__OTR__ast_zoness/D_ZO_6025E60";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_25EF8[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_25EF8";

static const ALIGN_ASSET(2) char D_ZO_6025F98[] = "__OTR__ast_zoness/D_ZO_6025F98";

static const ALIGN_ASSET(2) char ast_zoness_seg6_gfx_261A0[] = "__OTR__ast_zoness/ast_zoness_seg6_gfx_261A0";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_26348[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_26348";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_264B8[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_264B8";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_264F8[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_264F8";

static const ALIGN_ASSET(2) char ast_zoness_seg6_vtx_265F8[] = "__OTR__ast_zoness/ast_zoness_seg6_vtx_265F8";

static const ALIGN_ASSET(2) char D_ZO_60266D0[] = "__OTR__ast_zoness/D_ZO_60266D0";

static const ALIGN_ASSET(2) char D_ZO_6026714[] = "__OTR__ast_zoness/D_ZO_6026714";

static const char D_ZO_602AAC0[] = "__OTR__ast_zoness/D_ZO_602AAC0";

static const ALIGN_ASSET(2) char D_ZO_602AC50[] = "__OTR__ast_zoness/D_ZO_602AC50";

static const ALIGN_ASSET(2) char D_ZO_602AE94[] = "__OTR__ast_zoness/D_ZO_602AE94";

static const ALIGN_ASSET(2) char aZoRockHitbox[] = "__OTR__ast_zoness/aZoRockHitbox";

static const ALIGN_ASSET(2) char aZoOilRig1Hitbox[] = "__OTR__ast_zoness/aZoOilRig1Hitbox";

static const ALIGN_ASSET(2) char aZoOilRig2Hitbox[] = "__OTR__ast_zoness/aZoOilRig2Hitbox";

static const ALIGN_ASSET(2) char aZoOilRig3Hitbox[] = "__OTR__ast_zoness/aZoOilRig3Hitbox";

static const ALIGN_ASSET(2) char aZoIslandHitbox[] = "__OTR__ast_zoness/aZoIslandHitbox";

static const ALIGN_ASSET(2) char aZoDodoraHitbox[] = "__OTR__ast_zoness/aZoDodoraHitbox";

static const ALIGN_ASSET(2) char aZoTroikaHitbox[] = "__OTR__ast_zoness/aZoTroikaHitbox";

static const ALIGN_ASSET(2) char aZoObnemaHitbox[] = "__OTR__ast_zoness/aZoObnemaHitbox";

static const ALIGN_ASSET(2) char aZoBarrierHitbox[] = "__OTR__ast_zoness/aZoBarrierHitbox";

static const ALIGN_ASSET(2) char aZoBarrierHitbox2[] = "__OTR__ast_zoness/aZoBarrierHitbox2";

static const ALIGN_ASSET(2) char aZoSarumarineHitbox[] = "__OTR__ast_zoness/aZoSarumarineHitbox";

static const ALIGN_ASSET(2) char aZoSarumarinePeriscopeHitbox[] = "__OTR__ast_zoness/aZoSarumarinePeriscopeHitbox";

static const ALIGN_ASSET(2) char aZoTankerHitbox[] = "__OTR__ast_zoness/aZoTankerHitbox";

static const ALIGN_ASSET(2) char aZoContainerHitbox[] = "__OTR__ast_zoness/aZoContainerHitbox";

static const ALIGN_ASSET(2) char aZoRadarBuoyHitbox[] = "__OTR__ast_zoness/aZoRadarBuoyHitbox";

static const ALIGN_ASSET(2) char aZoSupplyCraneHitbox[] = "__OTR__ast_zoness/aZoSupplyCraneHitbox";

static const ALIGN_ASSET(2) char aZoBirdHitbox[] = "__OTR__ast_zoness/aZoBirdHitbox";

static const ALIGN_ASSET(2) char aZoSearchLightHitbox[] = "__OTR__ast_zoness/aZoSearchLightHitbox";

static const ALIGN_ASSET(2) char D_ZO_602C2CC[] = "__OTR__ast_zoness/D_ZO_602C2CC";

static const ALIGN_ASSET(2) char D_ZO_602CACC[] = "__OTR__ast_zoness/D_ZO_602CACC";

static const ALIGN_ASSET(2) char D_ZO_602CB80[] = "__OTR__ast_zoness/D_ZO_602CB80";

