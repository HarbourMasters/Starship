#pragma once

#include "gfx.h"
#include "sf64object.h"
#include "sf64level.h"
#include "sf64event.h"
#include "sf64player.h"
#include "sf64audio_external.h"
#include "sf64mesg.h"

static const ALIGN_ASSET(2) char D_ANDROSS_C000000[] = "__OTR__ast_andross/D_ANDROSS_C000000";

static const ALIGN_ASSET(2) char aAndTitleCardTex[] = "__OTR__ast_andross/aAndTitleCardTex";

static const ALIGN_ASSET(2) char D_ANDROSS_C001880[] = "__OTR__ast_andross/D_ANDROSS_C001880";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_18E8[] = "__OTR__ast_andross/ast_andross_seg12_vtx_18E8";

static const ALIGN_ASSET(2) char D_ANDROSS_C0019E8[] = "__OTR__ast_andross/D_ANDROSS_C0019E8";

static const ALIGN_ASSET(2) char D_ANDROSS_C00208C[] = "__OTR__ast_andross/D_ANDROSS_C00208C";

static const ALIGN_ASSET(2) char D_ANDROSS_C002654[] = "__OTR__ast_andross/D_ANDROSS_C002654";

static const ALIGN_ASSET(2) char D_ANDROSS_C002B08[] = "__OTR__ast_andross/D_ANDROSS_C002B08";

static const ALIGN_ASSET(2) char D_ANDROSS_C002B20[] = "__OTR__ast_andross/D_ANDROSS_C002B20";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_2C40[] = "__OTR__ast_andross/ast_andross_seg12_vtx_2C40";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_2D00[] = "__OTR__ast_andross/ast_andross_seg12_vtx_2D00";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_2DC0[] = "__OTR__ast_andross/ast_andross_seg12_vtx_2DC0";

static const ALIGN_ASSET(2) char D_ANDROSS_C002F00[] = "__OTR__ast_andross/D_ANDROSS_C002F00";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_3000[] = "__OTR__ast_andross/ast_andross_seg12_vtx_3000";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_3040[] = "__OTR__ast_andross/ast_andross_seg12_vtx_3040";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_3080[] = "__OTR__ast_andross/ast_andross_seg12_vtx_3080";

static const ALIGN_ASSET(2) char D_ANDROSS_C0031D0[] = "__OTR__ast_andross/D_ANDROSS_C0031D0";

static const ALIGN_ASSET(2) char D_ANDROSS_C0039D0[] = "__OTR__ast_andross/D_ANDROSS_C0039D0";

static const ALIGN_ASSET(2) char D_ANDROSS_C0041D0[] = "__OTR__ast_andross/D_ANDROSS_C0041D0";

static const ALIGN_ASSET(2) char D_ANDROSS_C0043D0[] = "__OTR__ast_andross/D_ANDROSS_C0043D0";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_44D8[] = "__OTR__ast_andross/ast_andross_seg12_vtx_44D8";

static const ALIGN_ASSET(2) char D_ANDROSS_C004658[] = "__OTR__ast_andross/D_ANDROSS_C004658";

static const ALIGN_ASSET(2) char D_ANDROSS_C004860[] = "__OTR__ast_andross/D_ANDROSS_C004860";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_4978[] = "__OTR__ast_andross/ast_andross_seg12_vtx_4978";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_4B78[] = "__OTR__ast_andross/ast_andross_seg12_vtx_4B78";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_4BE8[] = "__OTR__ast_andross/ast_andross_seg12_vtx_4BE8";

static const ALIGN_ASSET(2) char D_ANDROSS_C006F08[] = "__OTR__ast_andross/D_ANDROSS_C006F08";

static const ALIGN_ASSET(2) char ast_andross_seg12_gfx_6F20[] = "__OTR__ast_andross/ast_andross_seg12_gfx_6F20";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_7250[] = "__OTR__ast_andross/ast_andross_seg12_vtx_7250";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_73F0[] = "__OTR__ast_andross/ast_andross_seg12_vtx_73F0";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_7460[] = "__OTR__ast_andross/ast_andross_seg12_vtx_7460";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_74C0[] = "__OTR__ast_andross/ast_andross_seg12_vtx_74C0";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_76C0[] = "__OTR__ast_andross/ast_andross_seg12_vtx_76C0";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_78A0[] = "__OTR__ast_andross/ast_andross_seg12_vtx_78A0";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_7A80[] = "__OTR__ast_andross/ast_andross_seg12_vtx_7A80";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_7C70[] = "__OTR__ast_andross/ast_andross_seg12_vtx_7C70";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_7E00[] = "__OTR__ast_andross/ast_andross_seg12_vtx_7E00";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_7F30[] = "__OTR__ast_andross/ast_andross_seg12_vtx_7F30";

static const ALIGN_ASSET(2) char D_ANDROSS_C007FC0[] = "__OTR__ast_andross/D_ANDROSS_C007FC0";

static const ALIGN_ASSET(2) char D_ANDROSS_C0087C0[] = "__OTR__ast_andross/D_ANDROSS_C0087C0";

static const ALIGN_ASSET(2) char D_ANDROSS_C00DE48[] = "__OTR__ast_andross/D_ANDROSS_C00DE48";

static const ALIGN_ASSET(2) char D_ANDROSS_C00E598[] = "__OTR__ast_andross/D_ANDROSS_C00E598";

static const ALIGN_ASSET(2) char ast_andross_seg12_gfx_E5B0[] = "__OTR__ast_andross/ast_andross_seg12_gfx_E5B0";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_E8A8[] = "__OTR__ast_andross/ast_andross_seg12_vtx_E8A8";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_E8E8[] = "__OTR__ast_andross/ast_andross_seg12_vtx_E8E8";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_E9F8[] = "__OTR__ast_andross/ast_andross_seg12_vtx_E9F8";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_EBF8[] = "__OTR__ast_andross/ast_andross_seg12_vtx_EBF8";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_ED68[] = "__OTR__ast_andross/ast_andross_seg12_vtx_ED68";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_EDE8[] = "__OTR__ast_andross/ast_andross_seg12_vtx_EDE8";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_EF68[] = "__OTR__ast_andross/ast_andross_seg12_vtx_EF68";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_F098[] = "__OTR__ast_andross/ast_andross_seg12_vtx_F098";

static const ALIGN_ASSET(2) char D_ANDROSS_C00F108[] = "__OTR__ast_andross/D_ANDROSS_C00F108";

static const ALIGN_ASSET(2) char D_ANDROSS_C010108[] = "__OTR__ast_andross/D_ANDROSS_C010108";

static const ALIGN_ASSET(2) char D_ANDROSS_C010188[] = "__OTR__ast_andross/D_ANDROSS_C010188";

static const ALIGN_ASSET(2) char D_ANDROSS_C010988[] = "__OTR__ast_andross/D_ANDROSS_C010988";

static const ALIGN_ASSET(2) char D_ANDROSS_C011988[] = "__OTR__ast_andross/D_ANDROSS_C011988";

static const ALIGN_ASSET(2) char D_ANDROSS_C012188[] = "__OTR__ast_andross/D_ANDROSS_C012188";

static const ALIGN_ASSET(2) char D_ANDROSS_C012988[] = "__OTR__ast_andross/D_ANDROSS_C012988";

static const ALIGN_ASSET(2) char ast_andross_seg12_gfx_13190[] = "__OTR__ast_andross/ast_andross_seg12_gfx_13190";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_13308[] = "__OTR__ast_andross/ast_andross_seg12_vtx_13308";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_13508[] = "__OTR__ast_andross/ast_andross_seg12_vtx_13508";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_13578[] = "__OTR__ast_andross/ast_andross_seg12_vtx_13578";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_136F8[] = "__OTR__ast_andross/ast_andross_seg12_vtx_136F8";

static const ALIGN_ASSET(2) char D_ANDROSS_C013738[] = "__OTR__ast_andross/D_ANDROSS_C013738";

static const ALIGN_ASSET(2) char D_ANDROSS_C013F38[] = "__OTR__ast_andross/D_ANDROSS_C013F38";

static const ALIGN_ASSET(2) char D_ANDROSS_C014738[] = "__OTR__ast_andross/D_ANDROSS_C014738";

static const ALIGN_ASSET(2) char D_ANDROSS_C015740[] = "__OTR__ast_andross/D_ANDROSS_C015740";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_15848[] = "__OTR__ast_andross/ast_andross_seg12_vtx_15848";

static const ALIGN_ASSET(2) char ast_andross_seg12_gfx_159D0[] = "__OTR__ast_andross/ast_andross_seg12_gfx_159D0";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_15AD0[] = "__OTR__ast_andross/ast_andross_seg12_vtx_15AD0";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_15B50[] = "__OTR__ast_andross/ast_andross_seg12_vtx_15B50";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_15B90[] = "__OTR__ast_andross/ast_andross_seg12_vtx_15B90";

static const ALIGN_ASSET(2) char ast_andross_seg12_gfx_15C00[] = "__OTR__ast_andross/ast_andross_seg12_gfx_15C00";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_15D00[] = "__OTR__ast_andross/ast_andross_seg12_vtx_15D00";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_15DA0[] = "__OTR__ast_andross/ast_andross_seg12_vtx_15DA0";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_15DE0[] = "__OTR__ast_andross/ast_andross_seg12_vtx_15DE0";

static const ALIGN_ASSET(2) char ast_andross_seg12_gfx_15E50[] = "__OTR__ast_andross/ast_andross_seg12_gfx_15E50";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_15F10[] = "__OTR__ast_andross/ast_andross_seg12_vtx_15F10";

static const ALIGN_ASSET(2) char D_ANDROSS_C016100[] = "__OTR__ast_andross/D_ANDROSS_C016100";

static const ALIGN_ASSET(2) char D_ANDROSS_C017050[] = "__OTR__ast_andross/D_ANDROSS_C017050";

static const ALIGN_ASSET(2) char D_ANDROSS_C017430[] = "__OTR__ast_andross/D_ANDROSS_C017430";

static const ALIGN_ASSET(2) char D_ANDROSS_C017440[] = "__OTR__ast_andross/D_ANDROSS_C017440";

static const ALIGN_ASSET(2) char D_ANDROSS_C017598[] = "__OTR__ast_andross/D_ANDROSS_C017598";

static const ALIGN_ASSET(2) char D_ANDROSS_C0177B8[] = "__OTR__ast_andross/D_ANDROSS_C0177B8";

static const ALIGN_ASSET(2) char D_ANDROSS_C018BC4[] = "__OTR__ast_andross/D_ANDROSS_C018BC4";

static const ALIGN_ASSET(2) char ast_andross_seg12_gfx_18BD0[] = "__OTR__ast_andross/ast_andross_seg12_gfx_18BD0";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_18CE8[] = "__OTR__ast_andross/ast_andross_seg12_vtx_18CE8";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_18ED8[] = "__OTR__ast_andross/ast_andross_seg12_vtx_18ED8";

static const ALIGN_ASSET(2) char D_ANDROSS_C01C490[] = "__OTR__ast_andross/D_ANDROSS_C01C490";

static const ALIGN_ASSET(2) char D_ANDROSS_C01CC3C[] = "__OTR__ast_andross/D_ANDROSS_C01CC3C";

static const ALIGN_ASSET(2) char ast_andross_seg12_gfx_1CD40[] = "__OTR__ast_andross/ast_andross_seg12_gfx_1CD40";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_1CE50[] = "__OTR__ast_andross/ast_andross_seg12_vtx_1CE50";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_1D050[] = "__OTR__ast_andross/ast_andross_seg12_vtx_1D050";

static const ALIGN_ASSET(2) char ast_andross_seg12_gfx_1D150[] = "__OTR__ast_andross/ast_andross_seg12_gfx_1D150";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_1D248[] = "__OTR__ast_andross/ast_andross_seg12_vtx_1D248";

static const ALIGN_ASSET(2) char ast_andross_seg12_gfx_1D450[] = "__OTR__ast_andross/ast_andross_seg12_gfx_1D450";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_1D548[] = "__OTR__ast_andross/ast_andross_seg12_vtx_1D548";

static const ALIGN_ASSET(2) char ast_andross_seg12_gfx_1D750[] = "__OTR__ast_andross/ast_andross_seg12_gfx_1D750";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_1D870[] = "__OTR__ast_andross/ast_andross_seg12_vtx_1D870";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_1DA60[] = "__OTR__ast_andross/ast_andross_seg12_vtx_1DA60";

static const ALIGN_ASSET(2) char ast_andross_seg12_gfx_1DB80[] = "__OTR__ast_andross/ast_andross_seg12_gfx_1DB80";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_1DC78[] = "__OTR__ast_andross/ast_andross_seg12_vtx_1DC78";

static const ALIGN_ASSET(2) char ast_andross_seg12_gfx_1DE80[] = "__OTR__ast_andross/ast_andross_seg12_gfx_1DE80";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_1DFA8[] = "__OTR__ast_andross/ast_andross_seg12_vtx_1DFA8";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_1E1A8[] = "__OTR__ast_andross/ast_andross_seg12_vtx_1E1A8";

static const ALIGN_ASSET(2) char ast_andross_seg12_gfx_1E2C0[] = "__OTR__ast_andross/ast_andross_seg12_gfx_1E2C0";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_1E3B8[] = "__OTR__ast_andross/ast_andross_seg12_vtx_1E3B8";

static const ALIGN_ASSET(2) char ast_andross_seg12_gfx_1E5C0[] = "__OTR__ast_andross/ast_andross_seg12_gfx_1E5C0";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_1E6C8[] = "__OTR__ast_andross/ast_andross_seg12_vtx_1E6C8";

static const ALIGN_ASSET(2) char ast_andross_seg12_gfx_1E8D0[] = "__OTR__ast_andross/ast_andross_seg12_gfx_1E8D0";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_1E9C8[] = "__OTR__ast_andross/ast_andross_seg12_vtx_1E9C8";

static const ALIGN_ASSET(2) char ast_andross_seg12_gfx_1EBD0[] = "__OTR__ast_andross/ast_andross_seg12_gfx_1EBD0";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_1ED78[] = "__OTR__ast_andross/ast_andross_seg12_vtx_1ED78";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_1EF78[] = "__OTR__ast_andross/ast_andross_seg12_vtx_1EF78";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_1F158[] = "__OTR__ast_andross/ast_andross_seg12_vtx_1F158";

static const ALIGN_ASSET(2) char ast_andross_seg12_gfx_1F2E0[] = "__OTR__ast_andross/ast_andross_seg12_gfx_1F2E0";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_1F3F0[] = "__OTR__ast_andross/ast_andross_seg12_vtx_1F3F0";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_1F5F0[] = "__OTR__ast_andross/ast_andross_seg12_vtx_1F5F0";

static const ALIGN_ASSET(2) char ast_andross_seg12_gfx_1F750[] = "__OTR__ast_andross/ast_andross_seg12_gfx_1F750";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_1F848[] = "__OTR__ast_andross/ast_andross_seg12_vtx_1F848";

static const ALIGN_ASSET(2) char ast_andross_seg12_gfx_1FA20[] = "__OTR__ast_andross/ast_andross_seg12_gfx_1FA20";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_1FB38[] = "__OTR__ast_andross/ast_andross_seg12_vtx_1FB38";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_1FD38[] = "__OTR__ast_andross/ast_andross_seg12_vtx_1FD38";

static const ALIGN_ASSET(2) char ast_andross_seg12_gfx_1FE60[] = "__OTR__ast_andross/ast_andross_seg12_gfx_1FE60";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_1FF58[] = "__OTR__ast_andross/ast_andross_seg12_vtx_1FF58";

static const ALIGN_ASSET(2) char D_ANDROSS_C020128[] = "__OTR__ast_andross/D_ANDROSS_C020128";

static const ALIGN_ASSET(2) char ast_andross_seg12_gfx_20930[] = "__OTR__ast_andross/ast_andross_seg12_gfx_20930";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_20A40[] = "__OTR__ast_andross/ast_andross_seg12_vtx_20A40";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_20C30[] = "__OTR__ast_andross/ast_andross_seg12_vtx_20C30";

static const ALIGN_ASSET(2) char ast_andross_seg12_gfx_20E00[] = "__OTR__ast_andross/ast_andross_seg12_gfx_20E00";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_20EF8[] = "__OTR__ast_andross/ast_andross_seg12_vtx_20EF8";

static const ALIGN_ASSET(2) char ast_andross_seg12_gfx_21100[] = "__OTR__ast_andross/ast_andross_seg12_gfx_21100";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_21210[] = "__OTR__ast_andross/ast_andross_seg12_vtx_21210";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_21400[] = "__OTR__ast_andross/ast_andross_seg12_vtx_21400";

static const ALIGN_ASSET(2) char ast_andross_seg12_gfx_215A0[] = "__OTR__ast_andross/ast_andross_seg12_gfx_215A0";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_21698[] = "__OTR__ast_andross/ast_andross_seg12_vtx_21698";

static const ALIGN_ASSET(2) char ast_andross_seg12_gfx_218A0[] = "__OTR__ast_andross/ast_andross_seg12_gfx_218A0";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_219A0[] = "__OTR__ast_andross/ast_andross_seg12_vtx_219A0";

static const ALIGN_ASSET(2) char ast_andross_seg12_gfx_21BA0[] = "__OTR__ast_andross/ast_andross_seg12_gfx_21BA0";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_21C98[] = "__OTR__ast_andross/ast_andross_seg12_vtx_21C98";

static const ALIGN_ASSET(2) char ast_andross_seg12_gfx_21EA0[] = "__OTR__ast_andross/ast_andross_seg12_gfx_21EA0";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_22040[] = "__OTR__ast_andross/ast_andross_seg12_vtx_22040";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_22240[] = "__OTR__ast_andross/ast_andross_seg12_vtx_22240";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_22430[] = "__OTR__ast_andross/ast_andross_seg12_vtx_22430";

static const ALIGN_ASSET(2) char D_ANDROSS_C022520[] = "__OTR__ast_andross/D_ANDROSS_C022520";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_22640[] = "__OTR__ast_andross/ast_andross_seg12_vtx_22640";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_22820[] = "__OTR__ast_andross/ast_andross_seg12_vtx_22820";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_22970[] = "__OTR__ast_andross/ast_andross_seg12_vtx_22970";

static const ALIGN_ASSET(2) char D_ANDROSS_C022A10[] = "__OTR__ast_andross/D_ANDROSS_C022A10";

static const ALIGN_ASSET(2) char D_ANDROSS_C022A90[] = "__OTR__ast_andross/D_ANDROSS_C022A90";

static const ALIGN_ASSET(2) char D_ANDROSS_C023B54[] = "__OTR__ast_andross/D_ANDROSS_C023B54";

static const ALIGN_ASSET(2) char D_ANDROSS_C0240D0[] = "__OTR__ast_andross/D_ANDROSS_C0240D0";

static const ALIGN_ASSET(2) char D_ANDROSS_C025C00[] = "__OTR__ast_andross/D_ANDROSS_C025C00";

static const ALIGN_ASSET(2) char ast_andross_seg12_gfx_25C10[] = "__OTR__ast_andross/ast_andross_seg12_gfx_25C10";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_25D88[] = "__OTR__ast_andross/ast_andross_seg12_vtx_25D88";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_25F78[] = "__OTR__ast_andross/ast_andross_seg12_vtx_25F78";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_26028[] = "__OTR__ast_andross/ast_andross_seg12_vtx_26028";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_26158[] = "__OTR__ast_andross/ast_andross_seg12_vtx_26158";

static const ALIGN_ASSET(2) char ast_andross_seg12_gfx_261A0[] = "__OTR__ast_andross/ast_andross_seg12_gfx_261A0";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_263B0[] = "__OTR__ast_andross/ast_andross_seg12_vtx_263B0";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_26430[] = "__OTR__ast_andross/ast_andross_seg12_vtx_26430";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_26630[] = "__OTR__ast_andross/ast_andross_seg12_vtx_26630";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_267B0[] = "__OTR__ast_andross/ast_andross_seg12_vtx_267B0";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_26870[] = "__OTR__ast_andross/ast_andross_seg12_vtx_26870";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_268F0[] = "__OTR__ast_andross/ast_andross_seg12_vtx_268F0";

static const ALIGN_ASSET(2) char ast_andross_seg12_gfx_26950[] = "__OTR__ast_andross/ast_andross_seg12_gfx_26950";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_26A68[] = "__OTR__ast_andross/ast_andross_seg12_vtx_26A68";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_26C68[] = "__OTR__ast_andross/ast_andross_seg12_vtx_26C68";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_26E58[] = "__OTR__ast_andross/ast_andross_seg12_vtx_26E58";

static const ALIGN_ASSET(2) char D_ANDROSS_C029F74[] = "__OTR__ast_andross/D_ANDROSS_C029F74";

static const ALIGN_ASSET(2) char D_ANDROSS_C02E494[] = "__OTR__ast_andross/D_ANDROSS_C02E494";

static const ALIGN_ASSET(2) char D_ANDROSS_C02EDA0[] = "__OTR__ast_andross/D_ANDROSS_C02EDA0";

static const ALIGN_ASSET(2) char D_ANDROSS_C02F634[] = "__OTR__ast_andross/D_ANDROSS_C02F634";

static const ALIGN_ASSET(2) char D_ANDROSS_C030244[] = "__OTR__ast_andross/D_ANDROSS_C030244";

static const ALIGN_ASSET(2) char D_ANDROSS_C033780[] = "__OTR__ast_andross/D_ANDROSS_C033780";

static const ALIGN_ASSET(2) char D_ANDROSS_C033D98[] = "__OTR__ast_andross/D_ANDROSS_C033D98";

static const ALIGN_ASSET(2) char ast_andross_seg12_gfx_33DB0[] = "__OTR__ast_andross/ast_andross_seg12_gfx_33DB0";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_33E88[] = "__OTR__ast_andross/ast_andross_seg12_vtx_33E88";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_34088[] = "__OTR__ast_andross/ast_andross_seg12_vtx_34088";

static const ALIGN_ASSET(2) char ast_andross_seg12_gfx_340C0[] = "__OTR__ast_andross/ast_andross_seg12_gfx_340C0";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_34198[] = "__OTR__ast_andross/ast_andross_seg12_vtx_34198";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_34398[] = "__OTR__ast_andross/ast_andross_seg12_vtx_34398";

static const ALIGN_ASSET(2) char ast_andross_seg12_gfx_34590[] = "__OTR__ast_andross/ast_andross_seg12_gfx_34590";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_34668[] = "__OTR__ast_andross/ast_andross_seg12_vtx_34668";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_34868[] = "__OTR__ast_andross/ast_andross_seg12_vtx_34868";

static const ALIGN_ASSET(2) char ast_andross_seg12_gfx_34A50[] = "__OTR__ast_andross/ast_andross_seg12_gfx_34A50";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_34B68[] = "__OTR__ast_andross/ast_andross_seg12_vtx_34B68";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_34D58[] = "__OTR__ast_andross/ast_andross_seg12_vtx_34D58";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_34F58[] = "__OTR__ast_andross/ast_andross_seg12_vtx_34F58";

static const ALIGN_ASSET(2) char D_ANDROSS_C035110[] = "__OTR__ast_andross/D_ANDROSS_C035110";

static const ALIGN_ASSET(2) char D_ANDROSS_C035154[] = "__OTR__ast_andross/D_ANDROSS_C035154";

static const ALIGN_ASSET(2) char D_ANDROSS_C0356A4[] = "__OTR__ast_andross/D_ANDROSS_C0356A4";

static const ALIGN_ASSET(2) char D_ANDROSS_C0356CC[] = "__OTR__ast_andross/D_ANDROSS_C0356CC";

static const ALIGN_ASSET(2) char D_ANDROSS_C036310[] = "__OTR__ast_andross/D_ANDROSS_C036310";

static const ALIGN_ASSET(2) char D_ANDROSS_C036B6C[] = "__OTR__ast_andross/D_ANDROSS_C036B6C";

static const ALIGN_ASSET(2) char D_ANDROSS_C03733C[] = "__OTR__ast_andross/D_ANDROSS_C03733C";

static const char D_ANDROSS_C037E3C[] = "__OTR__ast_andross/D_ANDROSS_C037E3C";

static const ALIGN_ASSET(2) char D_ANDROSS_C037FCC[] = "__OTR__ast_andross/D_ANDROSS_C037FCC";

static const ALIGN_ASSET(2) char D_ANDROSS_C0380C0[] = "__OTR__ast_andross/D_ANDROSS_C0380C0";

static const ALIGN_ASSET(2) char D_ANDROSS_C0381B4[] = "__OTR__ast_andross/D_ANDROSS_C0381B4";

static const ALIGN_ASSET(2) char D_ANDROSS_C0382A8[] = "__OTR__ast_andross/D_ANDROSS_C0382A8";

static const ALIGN_ASSET(2) char D_ANDROSS_C03839C[] = "__OTR__ast_andross/D_ANDROSS_C03839C";

static const ALIGN_ASSET(2) char D_ANDROSS_C038490[] = "__OTR__ast_andross/D_ANDROSS_C038490";

static const ALIGN_ASSET(2) char D_ANDROSS_C038584[] = "__OTR__ast_andross/D_ANDROSS_C038584";

static const ALIGN_ASSET(2) char D_ANDROSS_C038678[] = "__OTR__ast_andross/D_ANDROSS_C038678";

static const ALIGN_ASSET(2) char D_ANDROSS_C03876C[] = "__OTR__ast_andross/D_ANDROSS_C03876C";

static const ALIGN_ASSET(2) char D_ANDROSS_C038860[] = "__OTR__ast_andross/D_ANDROSS_C038860";

static const ALIGN_ASSET(2) char D_ANDROSS_C038954[] = "__OTR__ast_andross/D_ANDROSS_C038954";

static const ALIGN_ASSET(2) char aAndDoorHitbox[] = "__OTR__ast_andross/aAndDoorHitbox";

static const ALIGN_ASSET(2) char D_ANDROSS_C038AC4[] = "__OTR__ast_andross/D_ANDROSS_C038AC4";

static const ALIGN_ASSET(2) char aAndPathHitbox[] = "__OTR__ast_andross/aAndPathHitbox";

static const ALIGN_ASSET(2) char aAndPathIntersectionHitbox[] = "__OTR__ast_andross/aAndPathIntersectionHitbox";

static const ALIGN_ASSET(2) char aAndPassageHitbox[] = "__OTR__ast_andross/aAndPassageHitbox";

static const ALIGN_ASSET(2) char D_ANDROSS_C038CCC[] = "__OTR__ast_andross/D_ANDROSS_C038CCC";

static const ALIGN_ASSET(2) char aAndAndrossHitbox[] = "__OTR__ast_andross/aAndAndrossHitbox";

static const ALIGN_ASSET(2) char aAndBrainHitbox[] = "__OTR__ast_andross/aAndBrainHitbox";

static const ALIGN_ASSET(2) char D_ANDROSS_C038FE8[] = "__OTR__ast_andross/D_ANDROSS_C038FE8";

static const ALIGN_ASSET(2) char D_ANDROSS_C039208[] = "__OTR__ast_andross/D_ANDROSS_C039208";

static const ALIGN_ASSET(2) char ast_andross_seg12_vtx_39260[] = "__OTR__ast_andross/ast_andross_seg12_vtx_39260";

static const ALIGN_ASSET(2) char D_ANDROSS_C039290[] = "__OTR__ast_andross/D_ANDROSS_C039290";

static const ALIGN_ASSET(2) char D_ANDROSS_C03A290[] = "__OTR__ast_andross/D_ANDROSS_C03A290";

