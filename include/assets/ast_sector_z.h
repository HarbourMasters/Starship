#pragma once

#include "gfx.h"
#include "sf64object.h"
#include "sf64level.h"
#include "sf64event.h"
#include "sf64player.h"
#include "sf64audio_external.h"
#include "sf64mesg.h"

static const ALIGN_ASSET(2) char aSzTitleCardTex[] = "__OTR__ast_sector_z/aSzTitleCardTex";

static const ALIGN_ASSET(2) char D_SZ_6000840[] = "__OTR__ast_sector_z/D_SZ_6000840";

static const ALIGN_ASSET(2) char D_SZ_60012D0[] = "__OTR__ast_sector_z/D_SZ_60012D0";

static const ALIGN_ASSET(2) char aSzSpaceJunk1DL[] = "__OTR__ast_sector_z/aSzSpaceJunk1DL";

static const ALIGN_ASSET(2) char ast_sector_z_seg6_vtx_15C8[] = "__OTR__ast_sector_z/ast_sector_z_seg6_vtx_15C8";

static const ALIGN_ASSET(2) char ast_sector_z_seg6_vtx_1748[] = "__OTR__ast_sector_z/ast_sector_z_seg6_vtx_1748";

static const ALIGN_ASSET(2) char ast_sector_z_seg6_vtx_1808[] = "__OTR__ast_sector_z/ast_sector_z_seg6_vtx_1808";

static const ALIGN_ASSET(2) char ast_sector_z_seg6_vtx_1908[] = "__OTR__ast_sector_z/ast_sector_z_seg6_vtx_1908";

static const ALIGN_ASSET(2) char aSzSpaceJunk2DL[] = "__OTR__ast_sector_z/aSzSpaceJunk2DL";

static const ALIGN_ASSET(2) char ast_sector_z_seg6_vtx_1B40[] = "__OTR__ast_sector_z/ast_sector_z_seg6_vtx_1B40";

static const ALIGN_ASSET(2) char ast_sector_z_seg6_vtx_1C00[] = "__OTR__ast_sector_z/ast_sector_z_seg6_vtx_1C00";

static const ALIGN_ASSET(2) char D_SZ_6001C80[] = "__OTR__ast_sector_z/D_SZ_6001C80";

static const ALIGN_ASSET(2) char D_SZ_6001D80[] = "__OTR__ast_sector_z/D_SZ_6001D80";

static const ALIGN_ASSET(2) char aSzSpaceJunk3DL[] = "__OTR__ast_sector_z/aSzSpaceJunk3DL";

static const ALIGN_ASSET(2) char ast_sector_z_seg6_vtx_2040[] = "__OTR__ast_sector_z/ast_sector_z_seg6_vtx_2040";

static const ALIGN_ASSET(2) char ast_sector_z_seg6_vtx_2230[] = "__OTR__ast_sector_z/ast_sector_z_seg6_vtx_2230";

static const ALIGN_ASSET(2) char ast_sector_z_seg6_vtx_2330[] = "__OTR__ast_sector_z/ast_sector_z_seg6_vtx_2330";

static const ALIGN_ASSET(2) char ast_sector_z_seg6_vtx_23F0[] = "__OTR__ast_sector_z/ast_sector_z_seg6_vtx_23F0";

static const ALIGN_ASSET(2) char ast_sector_z_seg6_vtx_24F0[] = "__OTR__ast_sector_z/ast_sector_z_seg6_vtx_24F0";

static const ALIGN_ASSET(2) char D_SZ_60025F0[] = "__OTR__ast_sector_z/D_SZ_60025F0";

static const ALIGN_ASSET(2) char D_SZ_60029F0[] = "__OTR__ast_sector_z/D_SZ_60029F0";

static const ALIGN_ASSET(2) char D_SZ_6002BD0[] = "__OTR__ast_sector_z/D_SZ_6002BD0";

static const ALIGN_ASSET(2) char D_SZ_6002C10[] = "__OTR__ast_sector_z/D_SZ_6002C10";

static const ALIGN_ASSET(2) char D_SZ_6002C30[] = "__OTR__ast_sector_z/D_SZ_6002C30";

static const ALIGN_ASSET(2) char D_SZ_6002D30[] = "__OTR__ast_sector_z/D_SZ_6002D30";

static const ALIGN_ASSET(2) char D_SZ_6002DE0[] = "__OTR__ast_sector_z/D_SZ_6002DE0";

static const ALIGN_ASSET(2) char D_SZ_6002EE0[] = "__OTR__ast_sector_z/D_SZ_6002EE0";

static const ALIGN_ASSET(2) char aSzBackgroundDL[] = "__OTR__ast_sector_z/aSzBackgroundDL";

static const ALIGN_ASSET(2) char ast_sector_z_seg6_vtx_2FD0[] = "__OTR__ast_sector_z/ast_sector_z_seg6_vtx_2FD0";

static const ALIGN_ASSET(2) char aSzBackgroundTex[] = "__OTR__ast_sector_z/aSzBackgroundTex";

static const ALIGN_ASSET(2) char D_SZ_6004010[] = "__OTR__ast_sector_z/D_SZ_6004010";

static const ALIGN_ASSET(2) char ast_sector_z_seg6_vtx_40D8[] = "__OTR__ast_sector_z/ast_sector_z_seg6_vtx_40D8";

static const ALIGN_ASSET(2) char ast_sector_z_seg6_vtx_41C8[] = "__OTR__ast_sector_z/ast_sector_z_seg6_vtx_41C8";

static const ALIGN_ASSET(2) char D_SZ_60041F8[] = "__OTR__ast_sector_z/D_SZ_60041F8";

static const ALIGN_ASSET(2) char D_SZ_60042F8[] = "__OTR__ast_sector_z/D_SZ_60042F8";

static const ALIGN_ASSET(2) char aSzMissileMark[] = "__OTR__ast_sector_z/aSzMissileMark";

static const ALIGN_ASSET(2) char ast_sector_z_seg6_vtx_43D8[] = "__OTR__ast_sector_z/ast_sector_z_seg6_vtx_43D8";

static const ALIGN_ASSET(2) char D_SZ_6004458[] = "__OTR__ast_sector_z/D_SZ_6004458";

static const ALIGN_ASSET(2) char D_SZ_6004558[] = "__OTR__ast_sector_z/D_SZ_6004558";

static const ALIGN_ASSET(2) char aSzMissileRadarMarkDL[] = "__OTR__ast_sector_z/aSzMissileRadarMarkDL";

static const ALIGN_ASSET(2) char ast_sector_z_seg6_vtx_4590[] = "__OTR__ast_sector_z/ast_sector_z_seg6_vtx_4590";

static const ALIGN_ASSET(2) char aSzSpaceJunk4DL[] = "__OTR__ast_sector_z/aSzSpaceJunk4DL";

static const ALIGN_ASSET(2) char ast_sector_z_seg6_vtx_4660[] = "__OTR__ast_sector_z/ast_sector_z_seg6_vtx_4660";

static const ALIGN_ASSET(2) char D_SZ_60047E0[] = "__OTR__ast_sector_z/D_SZ_60047E0";

static const ALIGN_ASSET(2) char aSzInvaderIIIDL[] = "__OTR__ast_sector_z/aSzInvaderIIIDL";

static const ALIGN_ASSET(2) char ast_sector_z_seg6_vtx_5140[] = "__OTR__ast_sector_z/ast_sector_z_seg6_vtx_5140";

static const ALIGN_ASSET(2) char ast_sector_z_seg6_vtx_5320[] = "__OTR__ast_sector_z/ast_sector_z_seg6_vtx_5320";

static const ALIGN_ASSET(2) char aSzInvaderIIITex2[] = "__OTR__ast_sector_z/aSzInvaderIIITex2";

static const ALIGN_ASSET(2) char aSzInvaderIIITex2TLUT[] = "__OTR__ast_sector_z/aSzInvaderIIITex2TLUT";

static const ALIGN_ASSET(2) char aSzInvaderIIITex1[] = "__OTR__ast_sector_z/aSzInvaderIIITex1";

static const ALIGN_ASSET(2) char aSzInvaderIIITex1TLUT[] = "__OTR__ast_sector_z/aSzInvaderIIITex1TLUT";

static const ALIGN_ASSET(2) char D_SZ_6005BF0[] = "__OTR__ast_sector_z/D_SZ_6005BF0";

static const ALIGN_ASSET(2) char ast_sector_z_seg6_vtx_5D70[] = "__OTR__ast_sector_z/ast_sector_z_seg6_vtx_5D70";

static const ALIGN_ASSET(2) char ast_sector_z_seg6_vtx_5F10[] = "__OTR__ast_sector_z/ast_sector_z_seg6_vtx_5F10";

static const ALIGN_ASSET(2) char D_SZ_6006090[] = "__OTR__ast_sector_z/D_SZ_6006090";

static const ALIGN_ASSET(2) char D_SZ_6006490[] = "__OTR__ast_sector_z/D_SZ_6006490";

static const ALIGN_ASSET(2) char D_SZ_6006660[] = "__OTR__ast_sector_z/D_SZ_6006660";

static const ALIGN_ASSET(2) char ast_sector_z_seg6_vtx_6700[] = "__OTR__ast_sector_z/ast_sector_z_seg6_vtx_6700";

static const ALIGN_ASSET(2) char D_SZ_6006780[] = "__OTR__ast_sector_z/D_SZ_6006780";

static const ALIGN_ASSET(2) char ast_sector_z_seg6_vtx_68C8[] = "__OTR__ast_sector_z/ast_sector_z_seg6_vtx_68C8";

static const ALIGN_ASSET(2) char ast_sector_z_seg6_vtx_6968[] = "__OTR__ast_sector_z/ast_sector_z_seg6_vtx_6968";

static const ALIGN_ASSET(2) char D_SZ_6006A30[] = "__OTR__ast_sector_z/D_SZ_6006A30";

static const ALIGN_ASSET(2) char ast_sector_z_seg6_vtx_6AD8[] = "__OTR__ast_sector_z/ast_sector_z_seg6_vtx_6AD8";

static const ALIGN_ASSET(2) char D_SZ_6006BD8[] = "__OTR__ast_sector_z/D_SZ_6006BD8";

static const ALIGN_ASSET(2) char D_SZ_6006CD8[] = "__OTR__ast_sector_z/D_SZ_6006CD8";

static const ALIGN_ASSET(2) char aSzMissileAnim[] = "__OTR__ast_sector_z/aSzMissileAnim";

static const ALIGN_ASSET(2) char aSzMissileSkel[] = "__OTR__ast_sector_z/aSzMissileSkel";

static const ALIGN_ASSET(2) char D_SZ_6006E70[] = "__OTR__ast_sector_z/D_SZ_6006E70";

static const ALIGN_ASSET(2) char D_SZ_6006EB4[] = "__OTR__ast_sector_z/D_SZ_6006EB4";

static const ALIGN_ASSET(2) char D_SZ_6007558[] = "__OTR__ast_sector_z/D_SZ_6007558";

static const ALIGN_ASSET(2) char D_SZ_6008E08[] = "__OTR__ast_sector_z/D_SZ_6008E08";

static const ALIGN_ASSET(2) char aSZMissileHitbox[] = "__OTR__ast_sector_z/aSZMissileHitbox";

static const ALIGN_ASSET(2) char aSzSpaceJunk3Hitbox[] = "__OTR__ast_sector_z/aSzSpaceJunk3Hitbox";

static const ALIGN_ASSET(2) char aSzSpaceJunk1Hitbox[] = "__OTR__ast_sector_z/aSzSpaceJunk1Hitbox";

static const ALIGN_ASSET(2) char aSzGreatFoxHitbox[] = "__OTR__ast_sector_z/aSzGreatFoxHitbox";

