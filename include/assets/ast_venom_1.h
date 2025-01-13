#pragma once

#include "gfx.h"
#include "sf64object.h"
#include "sf64level.h"
#include "sf64event.h"
#include "sf64player.h"
#include "sf64audio_external.h"
#include "sf64mesg.h"

static const ALIGN_ASSET(2) char D_VE1_6000000[] = "__OTR__ast_venom_1/D_VE1_6000000";

static const ALIGN_ASSET(2) char D_VE1_6000A80[] = "__OTR__ast_venom_1/D_VE1_6000A80";

static const ALIGN_ASSET(2) char aVe1TitleCardTex[] = "__OTR__ast_venom_1/aVe1TitleCardTex";

static const ALIGN_ASSET(2) char D_VE1_6001B80[] = "__OTR__ast_venom_1/D_VE1_6001B80";

static const ALIGN_ASSET(2) char aVe1EnemyGateDL[] = "__OTR__ast_venom_1/aVe1EnemyGateDL";

static const ALIGN_ASSET(2) char ast_venom_1_seg6_vtx_26D8[] = "__OTR__ast_venom_1/ast_venom_1_seg6_vtx_26D8";

static const ALIGN_ASSET(2) char ast_venom_1_seg6_vtx_27F8[] = "__OTR__ast_venom_1/ast_venom_1_seg6_vtx_27F8";

static const ALIGN_ASSET(2) char ast_venom_1_seg6_vtx_28F8[] = "__OTR__ast_venom_1/ast_venom_1_seg6_vtx_28F8";

static const ALIGN_ASSET(2) char D_VE1_60029F8[] = "__OTR__ast_venom_1/D_VE1_60029F8";

static const ALIGN_ASSET(2) char D_VE1_6002A78[] = "__OTR__ast_venom_1/D_VE1_6002A78";

static const ALIGN_ASSET(2) char D_VE1_6002AA8[] = "__OTR__ast_venom_1/D_VE1_6002AA8";

static const ALIGN_ASSET(2) char D_VE1_6002EA8[] = "__OTR__ast_venom_1/D_VE1_6002EA8";

static const ALIGN_ASSET(2) char D_VE1_6003078[] = "__OTR__ast_venom_1/D_VE1_6003078";

static const ALIGN_ASSET(2) char D_VE1_6003478[] = "__OTR__ast_venom_1/D_VE1_6003478";

static const ALIGN_ASSET(2) char aVe1WatchPostDL[] = "__OTR__ast_venom_1/aVe1WatchPostDL";

static const ALIGN_ASSET(2) char ast_venom_1_seg6_vtx_37E0[] = "__OTR__ast_venom_1/ast_venom_1_seg6_vtx_37E0";

static const ALIGN_ASSET(2) char ast_venom_1_seg6_vtx_3910[] = "__OTR__ast_venom_1/ast_venom_1_seg6_vtx_3910";

static const ALIGN_ASSET(2) char ast_venom_1_seg6_vtx_3970[] = "__OTR__ast_venom_1/ast_venom_1_seg6_vtx_3970";

static const ALIGN_ASSET(2) char D_VE1_6003B10[] = "__OTR__ast_venom_1/D_VE1_6003B10";

static const ALIGN_ASSET(2) char aVe1EnemyGateDoorLeftDL[] = "__OTR__ast_venom_1/aVe1EnemyGateDoorLeftDL";

static const ALIGN_ASSET(2) char ast_venom_1_seg6_vtx_43A8[] = "__OTR__ast_venom_1/ast_venom_1_seg6_vtx_43A8";

static const ALIGN_ASSET(2) char aVe1EnemyGateDoorRightDL[] = "__OTR__ast_venom_1/aVe1EnemyGateDoorRightDL";

static const ALIGN_ASSET(2) char ast_venom_1_seg6_vtx_4490[] = "__OTR__ast_venom_1/ast_venom_1_seg6_vtx_4490";

static const ALIGN_ASSET(2) char D_VE1_60044D0[] = "__OTR__ast_venom_1/D_VE1_60044D0";

static const ALIGN_ASSET(2) char D_VE1_60045D0[] = "__OTR__ast_venom_1/D_VE1_60045D0";

static const ALIGN_ASSET(2) char D_VE1_60046F0[] = "__OTR__ast_venom_1/D_VE1_60046F0";

static const ALIGN_ASSET(2) char ast_venom_1_seg6_vtx_4740[] = "__OTR__ast_venom_1/ast_venom_1_seg6_vtx_4740";

static const ALIGN_ASSET(2) char D_VE1_6004780[] = "__OTR__ast_venom_1/D_VE1_6004780";

static const ALIGN_ASSET(2) char aVe1GeneratorDL[] = "__OTR__ast_venom_1/aVe1GeneratorDL";

static const ALIGN_ASSET(2) char ast_venom_1_seg6_vtx_5990[] = "__OTR__ast_venom_1/ast_venom_1_seg6_vtx_5990";

static const ALIGN_ASSET(2) char ast_venom_1_seg6_vtx_5AD0[] = "__OTR__ast_venom_1/ast_venom_1_seg6_vtx_5AD0";

static const ALIGN_ASSET(2) char ast_venom_1_seg6_vtx_5CB0[] = "__OTR__ast_venom_1/ast_venom_1_seg6_vtx_5CB0";

static const ALIGN_ASSET(2) char ast_venom_1_seg6_vtx_5CF0[] = "__OTR__ast_venom_1/ast_venom_1_seg6_vtx_5CF0";

static const ALIGN_ASSET(2) char D_VE1_6005D50[] = "__OTR__ast_venom_1/D_VE1_6005D50";

static const ALIGN_ASSET(2) char D_VE1_6005E50[] = "__OTR__ast_venom_1/D_VE1_6005E50";

static const ALIGN_ASSET(2) char D_VE1_6005F90[] = "__OTR__ast_venom_1/D_VE1_6005F90";

static const ALIGN_ASSET(2) char D_VE1_6006390[] = "__OTR__ast_venom_1/D_VE1_6006390";

static const ALIGN_ASSET(2) char D_VE1_6006530[] = "__OTR__ast_venom_1/D_VE1_6006530";

static const ALIGN_ASSET(2) char D_VE1_6006630[] = "__OTR__ast_venom_1/D_VE1_6006630";

static const ALIGN_ASSET(2) char D_VE1_60066D0[] = "__OTR__ast_venom_1/D_VE1_60066D0";

static const ALIGN_ASSET(2) char ast_venom_1_seg6_vtx_66F0[] = "__OTR__ast_venom_1/ast_venom_1_seg6_vtx_66F0";

static const ALIGN_ASSET(2) char D_VE1_6006750[] = "__OTR__ast_venom_1/D_VE1_6006750";

static const ALIGN_ASSET(2) char aVe1HallwayObstacleDL[] = "__OTR__ast_venom_1/aVe1HallwayObstacleDL";

static const ALIGN_ASSET(2) char ast_venom_1_seg6_vtx_7028[] = "__OTR__ast_venom_1/ast_venom_1_seg6_vtx_7028";

static const ALIGN_ASSET(2) char ast_venom_1_seg6_vtx_7218[] = "__OTR__ast_venom_1/ast_venom_1_seg6_vtx_7218";

static const ALIGN_ASSET(2) char aVe1SceneryWall3DL[] = "__OTR__ast_venom_1/aVe1SceneryWall3DL";

static const ALIGN_ASSET(2) char ast_venom_1_seg6_vtx_7468[] = "__OTR__ast_venom_1/ast_venom_1_seg6_vtx_7468";

static const ALIGN_ASSET(2) char D_VE1_60074E8[] = "__OTR__ast_venom_1/D_VE1_60074E8";

static const ALIGN_ASSET(2) char aVe1Wall2DL[] = "__OTR__ast_venom_1/aVe1Wall2DL";

static const ALIGN_ASSET(2) char ast_venom_1_seg6_vtx_7D48[] = "__OTR__ast_venom_1/ast_venom_1_seg6_vtx_7D48";

static const ALIGN_ASSET(2) char aVe1Wall1DL[] = "__OTR__ast_venom_1/aVe1Wall1DL";

static const ALIGN_ASSET(2) char ast_venom_1_seg6_vtx_7DE8[] = "__OTR__ast_venom_1/ast_venom_1_seg6_vtx_7DE8";

static const ALIGN_ASSET(2) char D_VE1_6007E30[] = "__OTR__ast_venom_1/D_VE1_6007E30";

static const ALIGN_ASSET(2) char D_VE1_6007E74[] = "__OTR__ast_venom_1/D_VE1_6007E74";

static const ALIGN_ASSET(2) char D_VE1_6010088[] = "__OTR__ast_venom_1/D_VE1_6010088";

static const char aVe1EventScript[] = "__OTR__ast_venom_1/aVe1EventScript";

static const ALIGN_ASSET(2) char aVe1Pillar5Hitbox[] = "__OTR__ast_venom_1/aVe1Pillar5Hitbox";

static const ALIGN_ASSET(2) char D_VE1_601B474[] = "__OTR__ast_venom_1/D_VE1_601B474";

static const ALIGN_ASSET(2) char D_VE1_601B4C4[] = "__OTR__ast_venom_1/D_VE1_601B4C4";

static const ALIGN_ASSET(2) char Ve1Wall1Hitbox[] = "__OTR__ast_venom_1/Ve1Wall1Hitbox";

static const ALIGN_ASSET(2) char aVe1Wall2Hitbox[] = "__OTR__ast_venom_1/aVe1Wall2Hitbox";

static const ALIGN_ASSET(2) char aVe1SceneryWall3Hitbox[] = "__OTR__ast_venom_1/aVe1SceneryWall3Hitbox";

static const ALIGN_ASSET(2) char aVe1HallwayObstacleHitbox[] = "__OTR__ast_venom_1/aVe1HallwayObstacleHitbox";

static const ALIGN_ASSET(2) char aVe1GeneratorHitbox[] = "__OTR__ast_venom_1/aVe1GeneratorHitbox";

static const ALIGN_ASSET(2) char aVe1WatchPostHitbox[] = "__OTR__ast_venom_1/aVe1WatchPostHitbox";

static const ALIGN_ASSET(2) char aVe1TempleEntranceHitbox[] = "__OTR__ast_venom_1/aVe1TempleEntranceHitbox";

static const ALIGN_ASSET(2) char aVe1TempleInterior1Hitbox[] = "__OTR__ast_venom_1/aVe1TempleInterior1Hitbox";

static const ALIGN_ASSET(2) char aVe1TempleInterior2Hitbox[] = "__OTR__ast_venom_1/aVe1TempleInterior2Hitbox";

static const ALIGN_ASSET(2) char aVe1TempleInterior3Hitbox[] = "__OTR__ast_venom_1/aVe1TempleInterior3Hitbox";

static const ALIGN_ASSET(2) char aVe1Pillar1Hitbox[] = "__OTR__ast_venom_1/aVe1Pillar1Hitbox";

static const ALIGN_ASSET(2) char aVe1Pillar2Hitbox[] = "__OTR__ast_venom_1/aVe1Pillar2Hitbox";

static const ALIGN_ASSET(2) char aVe1Pillar3Hitbox[] = "__OTR__ast_venom_1/aVe1Pillar3Hitbox";

static const ALIGN_ASSET(2) char aVe1Pillar4Hitbox[] = "__OTR__ast_venom_1/aVe1Pillar4Hitbox";

static const ALIGN_ASSET(2) char aVe1MonkeyStatueHitbox[] = "__OTR__ast_venom_1/aVe1MonkeyStatueHitbox";

static const ALIGN_ASSET(2) char aVe1EnemyGateHitbox[] = "__OTR__ast_venom_1/aVe1EnemyGateHitbox";

