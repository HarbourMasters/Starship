/*
 * File: fox_ma.c
 * System: Macbeth
 * Description: Level: Macbeth
 */

// #include "prevent_bss_reordering.h"
#include "global.h"
#include "assets/ast_macbeth.h"
#include "assets/ast_landmaster.h"
#include "assets/ast_enmy_planet.h"
// #include "prevent_bss_reordering2.h"

typedef struct {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ s16 unk_10;
} UnkStruct_D_i5_801B8E50; // size = 0x14

typedef struct {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ s16 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ s16 unk_10;
} UnkStruct_D_i5_801BA1EC; // size = 0x14

void Macbeth_Effect357_Spawn1(f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, s16, s16, f32);
bool Macbeth_801A0308(Actor*, f32, f32, u8);
void Macbeth_MaShockBox_Spawn(f32, f32, f32, f32, f32, f32);
void Macbeth_801A015C(Actor*);
void Macbeth_8019D048(Actor*);
void Macbeth_8019FC54(Actor*, s32*, s32*, s32, s32, f32, f32, s32*);
void Macbeth_MaBoulder_Spawn(f32, f32, f32, f32, f32, f32, f32, s32, u8);
void Macbeth_8019D910(Actor*, s32*, s32*, s32, f32, f32, s32*, s32*);
bool Macbeth_MaTrainCar1_OverrideLimbDraw(s32, Gfx**, Vec3f*, Vec3f*, void*);
void Macbeth_MaBoulder_HandleDamage(Actor*);
void Macbeth_MaBombDrop_Spawn(f32, f32, f32, f32, f32, f32);
void Macbeth_MaSpear_Spawn(f32, f32, f32, f32, f32, f32, s16);
void Macbeth_Effect379_Spawn(f32, f32, f32, f32, f32, f32);
void Macbeth_EffectClouds_Spawn(void);

f32 D_MA_801BE250[40];
s16 D_MA_801BE2F0[9];
// #include "prevent_bss_reordering.h"
char D_i5_801BE308[8];
s16 D_i5_801BE310;
u8 D_i5_801BE312;
u8 D_i5_801BE313;
s16 D_i5_801BE314;
s16 D_i5_801BE316;
s16 D_i5_801BE318;
s16 D_i5_801BE320[35];
f32 D_i5_801BE368[50];
Vec3f D_i5_801BE430[50];
Vec3f D_i5_801BE688[2];
Vec3f D_i5_801BE6A0[12];
s32 D_i5_801BE734[4];

UnkStruct_D_i5_801B8E50 D_i5_801B8E50[156] = {
    { 5174.4f, -2141.0f, 0.0f, 350.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { 3401.4f, -1828.0f, 0.0f, 350.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { 1627.8999f, -1515.0f, 0.0f, 350.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -145.0f, -1202.0f, 0.0f, 350.0f, OBJ_SCENERY_MA_TRAIN_TRACK_5 },
    { -1933.0f, -1046.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -3733.0f, -1046.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -5533.0f, -1046.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -7333.0f, -1046.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -9133.0f, -1046.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -10933.0f, -1046.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -12733.0f, -1046.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -14533.0f, -1046.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -16333.0f, -1046.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -18133.0f, -1046.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_4 },
    { -19921.6f, -889.0f, 0.0f, 350.0f, OBJ_SCENERY_MA_TRAIN_TRACK_4 },
    { -21656.4f, -423.0f, 0.0f, 340.0f, OBJ_SCENERY_MA_TRAIN_TRACK_5 },
    { -23390.7f, 40.0f, 0.0f, 350.0f, OBJ_SCENERY_MA_TRAIN_TRACK_5 },
    { -25125.0f, 197.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -26925.0f, 197.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_5 },
    { -28713.6f, 40.0f, 0.0f, 10.0f, OBJ_SCENERY_MA_TRAIN_TRACK_5 },
    { -30447.3f, -424.0f, 0.0f, 20.0f, OBJ_SCENERY_MA_TRAIN_TRACK_4 },
    { -32181.3f, -889.0f, 0.0f, 10.0f, OBJ_SCENERY_MA_TRAIN_TRACK_4 },
    { -33971.1f, -1045.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_9 },
    { -35771.1f, -1045.0f, 90.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_9 },
    { -37571.1f, -1045.0f, 180.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_9 },
    { -39371.1f, -1045.0f, 270.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_9 },
    { -41171.1f, -1045.0f, 360.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_9 },
    { -42971.1f, -1045.0f, 450.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_4 },
    { -44760.0f, -889.0f, 450.0f, 350.0f, OBJ_SCENERY_MA_TRAIN_TRACK_5 },
    { -46547.9f, -733.0f, 450.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -48347.5f, -733.0f, 450.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_4 },
    { -50136.4f, -576.0f, 450.0f, 350.0f, OBJ_SCENERY_MA_TRAIN_TRACK_4 },
    { -51872.1f, -111.0f, 450.0f, 340.0f, OBJ_SCENERY_MA_TRAIN_TRACK_5 },
    { -53606.4f, 352.0f, 450.0f, 350.0f, OBJ_SCENERY_MA_TRAIN_TRACK_5 },
    { -55395.4f, 509.0f, 450.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_5 },
    { -57184.2f, 353.0f, 450.0f, 10.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -58957.5f, 40.0f, 450.0f, 10.0f, OBJ_SCENERY_MA_TRAIN_TRACK_4 },
    { -60746.9f, -115.0f, 450.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -62548.2f, -114.0f, 450.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_10 },
    { -64349.1f, -114.0f, 360.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_10 },
    { -66149.3f, -115.0f, 270.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_10 },
    { -67950.3f, -115.0f, 180.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_10 },
    { -69751.2f, -115.0f, 90.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_10 },
    { -71551.2f, -115.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -73351.0f, -116.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_5 },
    { -75139.2f, -273.0f, 0.0f, 10.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -76912.4f, -587.0f, 0.0f, 10.0f, OBJ_SCENERY_MA_TRAIN_TRACK_4 },
    { -78702.0f, -743.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -80502.2f, -743.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -82302.2f, -743.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -84102.0f, -743.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_4 },
    { -85890.6f, -586.0f, 0.0f, 350.0f, OBJ_SCENERY_MA_TRAIN_TRACK_5 },
    { -87679.9f, -431.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -89479.9f, -431.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -91279.9f, -431.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -93079.9f, -431.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -94879.9f, -431.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -96680.0f, -431.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -98480.0f, -431.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -100280.0f, -431.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -102079.9f, -431.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -103879.9f, -431.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -105679.9f, -431.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -107479.9f, -431.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -109279.9f, -431.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -111079.9f, -431.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -112879.9f, -431.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -114679.9f, -431.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -116479.9f, -431.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -118279.9f, -431.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -120079.9f, -431.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -121879.9f, -431.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -123679.9f, -431.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -125479.9f, -431.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -127279.9f, -431.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_4 },
    { -129068.2f, -274.0f, 0.0f, 350.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -130841.2f, 38.0f, 0.0f, 350.0f, OBJ_SCENERY_MA_TRAIN_TRACK_5 },
    { -132630.4f, 194.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -134430.4f, 194.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_5 },
    { -136219.4f, 37.0f, 0.0f, 10.0f, OBJ_SCENERY_MA_TRAIN_TRACK_4 },
    { -138009.0f, -119.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_5 },
    { -139798.6f, -277.0f, 0.0f, 10.0f, OBJ_SCENERY_MA_TRAIN_TRACK_4 },
    { -141587.6f, -433.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_4 },
    { -143376.3f, -276.0f, 0.0f, 350.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -145149.0f, 35.0f, 0.0f, 350.0f, OBJ_SCENERY_MA_TRAIN_TRACK_5 },
    { -146883.3f, 192.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -148683.3f, 192.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_5 },
    { -150471.9f, 34.0f, 0.0f, 10.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -152244.8f, -278.0f, 0.0f, 10.0f, OBJ_SCENERY_MA_TRAIN_TRACK_4 },
    { -154034.2f, -434.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -155834.2f, -434.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -157634.2f, -434.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -159434.2f, -434.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -161234.2f, -434.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -163034.2f, -434.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -164834.2f, -434.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -166634.2f, -434.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -168435.2f, -435.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_4 },
    { -170223.8f, -278.0f, 0.0f, 350.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -171996.6f, 34.0f, 0.0f, 350.0f, OBJ_SCENERY_MA_TRAIN_TRACK_5 },
    { -173785.4f, 191.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_5 },
    { -175574.2f, 33.0f, 0.0f, 10.0f, OBJ_SCENERY_MA_TRAIN_TRACK_4 },
    { -177364.0f, -123.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -179164.9f, -122.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_4 },
    { -180954.4f, 32.0f, 0.0f, 350.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -182727.1f, 345.0f, 0.0f, 350.0f, OBJ_SCENERY_MA_TRAIN_TRACK_5 },
    { -184515.8f, 501.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_5 },
    { -186304.5f, 344.0f, 0.0f, 10.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -188077.7f, 30.0f, 0.0f, 10.0f, OBJ_SCENERY_MA_TRAIN_TRACK_4 },
    { -189866.6f, -125.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -191667.3f, -125.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_4 },
    { -193455.9f, 31.0f, 0.0f, 350.0f, OBJ_SCENERY_MA_TRAIN_TRACK_5 },
    { -195245.1f, 187.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_4 },
    { -197033.7f, 344.0f, 0.0f, 350.0f, OBJ_SCENERY_MA_TRAIN_TRACK_5 },
    { -198823.2f, 500.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_5 },
    { -200612.3f, 343.0f, 0.0f, 10.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -202385.6f, 30.0f, 0.0f, 10.0f, OBJ_SCENERY_MA_TRAIN_TRACK_4 },
    { -204175.1f, -125.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_5 },
    { -205964.3f, -282.0f, 0.0f, 10.0f, OBJ_SCENERY_MA_TRAIN_TRACK_4 },
    { -207754.0f, -440.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_4 },
    { -209542.5f, -283.0f, 0.0f, 350.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -211315.1f, 29.0f, 0.0f, 350.0f, OBJ_SCENERY_MA_TRAIN_TRACK_5 },
    { -213104.5f, 185.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_5 },
    { -214893.4f, 28.0f, 0.0f, 10.0f, OBJ_SCENERY_MA_TRAIN_TRACK_4 },
    { -216683.2f, -128.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_4 },
    { -218471.8f, 28.0f, 0.0f, 350.0f, OBJ_SCENERY_MA_TRAIN_TRACK_5 },
    { -220261.3f, 184.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_5 },
    { -222050.1f, 27.0f, 0.0f, 10.0f, OBJ_SCENERY_MA_TRAIN_TRACK_4 },
    { -223839.6f, -129.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -225639.6f, -129.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -227439.6f, -129.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -229239.6f, -129.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -231039.6f, -129.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -232839.6f, -129.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -234639.6f, -129.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -236439.6f, -129.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -238239.6f, -129.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -240039.6f, -129.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -241839.6f, -129.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -243639.6f, -129.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -245439.6f, -129.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -247239.6f, -129.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -249039.6f, -129.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -250839.6f, -129.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -252639.6f, -129.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -254439.6f, -129.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -256240.5f, -129.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -258040.5f, -129.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -259840.5f, -129.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -261640.5f, -129.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -263440.5f, -129.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -265240.5f, -129.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -267040.5f, -129.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -268840.5f, -129.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -507035.0f, -319.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
};

UnkStruct_D_i5_801B8E50 D_i5_801B9A80[86] = {
    { 5174.4f, -2141.0f, 0.0f, 350.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { 3401.4f, -1828.0f, 0.0f, 350.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { 1627.8999f, -1515.0f, 0.0f, 350.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -145.0f, -1202.0f, 0.0f, 350.0f, OBJ_SCENERY_MA_TRAIN_TRACK_5 },
    { -1933.0f, -1046.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -3733.0f, -1046.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -5533.0f, -1046.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -7333.0f, -1046.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -9133.0f, -1046.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -10933.0f, -1046.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -12733.0f, -1046.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -14533.0f, -1046.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -16333.0f, -1046.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -18133.0f, -1046.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_4 },
    { -19921.6f, -889.0f, 0.0f, 350.0f, OBJ_SCENERY_MA_TRAIN_TRACK_4 },
    { -21656.4f, -423.0f, 0.0f, 340.0f, OBJ_SCENERY_MA_TRAIN_TRACK_5 },
    { -23390.7f, 40.0f, 0.0f, 350.0f, OBJ_SCENERY_MA_TRAIN_TRACK_5 },
    { -25125.0f, 197.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -26925.0f, 197.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_5 },
    { -28713.6f, 40.0f, 0.0f, 10.0f, OBJ_SCENERY_MA_TRAIN_TRACK_5 },
    { -30447.3f, -424.0f, 0.0f, 20.0f, OBJ_SCENERY_MA_TRAIN_TRACK_4 },
    { -32181.3f, -889.0f, 0.0f, 10.0f, OBJ_SCENERY_MA_TRAIN_TRACK_4 },
    { -33971.1f, -1045.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_9 },
    { -35771.1f, -1045.0f, 90.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_9 },
    { -37571.1f, -1045.0f, 180.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_9 },
    { -39371.1f, -1045.0f, 270.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_9 },
    { -41171.1f, -1045.0f, 360.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_9 },
    { -42971.1f, -1045.0f, 450.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_4 },
    { -44760.0f, -889.0f, 450.0f, 350.0f, OBJ_SCENERY_MA_TRAIN_TRACK_5 },
    { -46547.9f, -733.0f, 450.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -48347.5f, -733.0f, 450.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_4 },
    { -50136.4f, -576.0f, 450.0f, 350.0f, OBJ_SCENERY_MA_TRAIN_TRACK_4 },
    { -51872.1f, -111.0f, 450.0f, 340.0f, OBJ_SCENERY_MA_TRAIN_TRACK_5 },
    { -53606.4f, 352.0f, 450.0f, 350.0f, OBJ_SCENERY_MA_TRAIN_TRACK_5 },
    { -55395.4f, 509.0f, 450.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_5 },
    { -57184.2f, 353.0f, 450.0f, 10.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -58957.5f, 40.0f, 450.0f, 10.0f, OBJ_SCENERY_MA_TRAIN_TRACK_4 },
    { -60746.9f, -115.0f, 450.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -62548.2f, -114.0f, 450.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_10 },
    { -64349.1f, -114.0f, 360.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_10 },
    { -66149.3f, -115.0f, 270.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_10 },
    { -67950.3f, -115.0f, 180.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_10 },
    { -69751.2f, -115.0f, 90.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_10 },
    { -71551.2f, -115.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -73351.0f, -116.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_5 },
    { -75139.2f, -273.0f, 0.0f, 10.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -76912.4f, -587.0f, 0.0f, 10.0f, OBJ_SCENERY_MA_TRAIN_TRACK_4 },
    { -78702.0f, -743.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -80502.2f, -743.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -82302.2f, -743.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -84102.0f, -743.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_4 },
    { -85890.6f, -586.0f, 0.0f, 350.0f, OBJ_SCENERY_MA_TRAIN_TRACK_5 },
    { -87679.9f, -431.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -89479.9f, -431.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -91279.9f, -431.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -93079.9f, -431.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -94879.9f, -431.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -96680.0f, -431.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -98480.0f, -431.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -100280.0f, -431.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -102079.9f, -431.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -103879.9f, -431.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -105679.9f, -431.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -107479.9f, -431.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -109279.9f, -431.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -111079.9f, -431.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -112879.9f, -431.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_3 },
    { -114679.9f, -431.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_SWITCH_TRACK },
    { -116453.5f, -118.0f, 0.0f, 350.0f, OBJ_SCENERY_MA_TRAIN_TRACK_7 },
    { -118188.5f, 346.0f, 0.0f, 340.0f, OBJ_SCENERY_MA_TRAIN_TRACK_7 },
    { -119815.5f, 1105.0f, 0.0f, 330.0f, OBJ_SCENERY_MA_TRAIN_TRACK_6 },
    { -121374.3f, 2005.0f, 0.0f, 330.0f, OBJ_SCENERY_MA_TRAIN_TRACK_6 },
    { -122933.3f, 2905.0f, 0.0f, 330.0f, OBJ_SCENERY_MA_TRAIN_TRACK_6 },
    { -124491.9f, 3806.0f, 0.0f, 330.0f, OBJ_SCENERY_MA_TRAIN_TRACK_6 },
    { -126051.4f, 4707.0f, 0.0f, 330.0f, OBJ_SCENERY_MA_TRAIN_TRACK_6 },
    { -127609.9f, 5607.0f, 0.0f, 330.0f, OBJ_SCENERY_MA_TRAIN_TRACK_6 },
    { -129168.9f, 6507.0f, 0.0f, 330.0f, OBJ_SCENERY_MA_TRAIN_TRACK_6 },
    { -130728.1f, 7408.0f, 0.0f, 330.0f, OBJ_SCENERY_MA_TRAIN_TRACK_6 },
    { -132287.2f, 8308.0f, 0.0f, 330.0f, OBJ_SCENERY_MA_TRAIN_TRACK_6 },
    { -133846.4f, 9208.0f, 0.0f, 330.0f, OBJ_SCENERY_MA_TRAIN_TRACK_6 },
    { -135405.4f, 10109.0f, 0.0f, 330.0f, OBJ_SCENERY_MA_TRAIN_TRACK_6 },
    { -136964.0f, 11009.0f, 0.0f, 330.0f, OBJ_SCENERY_MA_TRAIN_TRACK_6 },
    { -138522.9f, 11909.0f, 0.0f, 330.0f, OBJ_SCENERY_MA_TRAIN_TRACK_6 },
    { -140082.1f, 12810.0f, 0.0f, 330.0f, OBJ_SCENERY_MA_TRAIN_TRACK_6 },
    { -507035.0f, -489.0f, 0.0f, 0.0f, OBJ_SCENERY_MA_TRAIN_TRACK_6 },
};

UnkStruct_D_i5_801B8E50 D_i5_801BA138[8] = {
    { -43605.8f, -1095.0f, 450.0f, -350.0f, 105 }, { -44786.7f, -884.0f, 450.0f, -350.0f, 105 },
    { -50739.8f, -519.0f, 450.0f, -340.0f, 105 },  { -51871.2f, -110.0f, 450.0f, -340.0f, 105 },
    { -84502.5f, 356.0f, 200.0f, -0.0f, 105 },     { -86080.9f, 352.0f, 200.0f, -0.0f, 105 },
    { -87278.9f, 347.0f, 200.0f, -0.0f, 105 },     { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
};

u8 D_i5_801BA1D8 = 0;

f32 sMaTrainSpeedTarget = 0.0f;
f32 D_i5_801BA1E0 = 10000000.0f;
u8 D_i5_801BA1E4 = 0;
u8 D_MA_801BA1E8 = 0;

UnkStruct_D_i5_801BA1EC D_i5_801BA1EC[45] = {
    { -0.0f, 16, -2000.0f, -3500.0f, 0 },      { -3500.0f, 16, -2000.0f, -5500.0f, 0 },
    { -6500.0f, 16, -3500.0f, -5500.0f, 0 },   { -7300.0f, 16, -3500.0f, -5500.0f, 0 },
    { -9000.0f, 16, -3000.0f, -5500.0f, 0 },   { -12000.0f, 16, -3000.0f, -4000.0f, 0 },
    { -13600.0f, 16, -3500.0f, -5500.0f, 13 }, { -15100.0f, 16, -3000.0f, -5500.0f, 12 },
    { -16700.0f, 16, -2500.0f, -5500.0f, 11 }, { -17000.0f, 16, 1000.0f, -1000.0f, 0 },
    { -20800.0f, 16, 2000.0f, 0.0f, 14 },      { -21000.0f, 16, 2000.0f, 0.0f, 102 },
    { -29000.0f, 16, 1500.0f, 0.0f, 14 },      { -31500.0f, 16, -500.0f, -4000.0f, 0 },
    { -33000.0f, 16, -1500.0f, -3500.0f, 0 },  { -34000.0f, 16, -1500.0f, -3500.0f, 103 },
    { -41000.0f, 11, 3000.0f, -500.0f, 10 },   { -44300.0f, 11, 3000.0f, -500.0f, 102 },
    { -49000.0f, 10, 2000.0f, 500.0f, 10 },    { -54000.0f, 8, 2500.0f, 500.0f, 0 },
    { -57500.0f, 8, 2000.0f, 500.0f, 8 },      { -59000.0f, 8, 2000.0f, 500.0f, 103 },
    { -63500.0f, 8, 500.0f, -1000.0f, 0 },     { -67000.0f, 7, 2000.0f, 500.0f, 0 },
    { -69000.0f, 7, 1000.0f, -1000.0f, 0 },    { -71500.0f, 6, 2000.0f, 1000.0f, 0 },
    { -73500.0f, 6, 2000.0f, 1000.0f, 0 },     { -74000.0f, 6, 2000.0f, -1500.0f, 0 },
    { -79000.0f, 4, 4000.0f, -500.0f, 4 },     { -83000.0f, 4, 5500.0f, 3000.0f, 0 },
    { -93000.0f, 3, 4000.0f, -500.0f, 0 },     { -95600.0f, 3, 1000.0f, 0.0f, 2 },
    { -95700.0f, 3, 1500.0f, 500.0f, 1 },      { -95750.0f, 3, 2000.0f, 500.0f, 102 },
    { -99000.0f, 2, 2500.0f, 1000.0f, 0 },     { -100000.0f, 2, 3000.0f, 1000.0f, 200 },
    { -100100.0f, 2, 3000.0f, 1000.0f, 301 },  { -103000.0f, 2, 3000.0f, 1000.0f, 203 },
    { -106000.0f, 2, 5000.0f, 3000.0f, 0 },    { -118000.0f, 2, 3000.0f, 1000.0f, 201 },
    { -176000.0f, 2, 3000.0f, 1000.0f, 302 },  { -236000.0f, 2, 3000.0f, 1000.0f, 303 },
    { -258000.0f, 3, 4000.0f, 3000.0f, 304 },  { -999999.0f, 5, 1000.0f, 500.0f, 0 },
    { -1.0f, -1, -1.0f, -1.0f, -1 },
};

f32 D_i5_801BA570[5][10] = {
    { 450.0f, 350.0f, 250.0f, 150.0f, 50.0f, -50.0f, -150.0f, -250.0f, -350.0f, -450.0f },
    { 50.0f, -50.0f, 150.0f, -150.0f, 250.0f, -250.0f, 350.0f, -350.0f, 450.0f, -450.0f },
    { 50.0f, -50.0f, 250.0f, -250.0f, 150.0f, -150.0f, 350.0f, -350.0f, 450.0f, -450.0f },
    { 400.0f, 360.0f, 290.0f, 200.0f, 70.0f, -70.0f, -200.0f, -290.0f, -360.0f, -400.0f },
    { -200.0f, -100.0f, 0.0f, 100.0f, 200.0f, 400.0f, 300.0f, 200.0f, 100.0f, 0.0f },
};

f32 D_i5_801BA638[5][10] = {
    { 1000.0f, 1000.0f, 1000.0f, 1000.0f, 1000.0f, 1000.0f, 1000.0f, 1000.0f, 1000.0f, 1000.0f },
    { 700.0f, 700.0f, 850.0f, 850.0f, 1000.0f, 1000.0f, 1150.0f, 1150.0f, 1300.0f, 1300.0f },
    { 1000.0f, 1000.0f, 1000.0f, 1000.0f, 1500.0f, 1500.0f, 1500.0f, 1500.0f, 1500.0f, 1500.0f },
    { 500.0f, 750.0f, 850.0f, 940.0f, 1000.0f, 1000.0f, 940.0f, 850.0f, 750.0f, 500.0f },
    { 700.0f, 850.0f, 1000.0f, 1150.0f, 1300.0f, 1800.0f, 1950.0f, 2100.0f, 2250.0f, 2400.0f },
};

f32 D_i5_801BA700[] = { 610.0f, 0.0f }; // unused?

void Macbeth_InitLevel(void) {
    s16 i;

    sMaTrainSpeedTarget = -15.0f;
    D_MA_801BE2F0[0] = 0;
    D_MA_801BE2F0[1] = 999;
    D_MA_801BE2F0[2] = 0;
    D_MA_801BE2F0[3] = 999;
    D_MA_801BE2F0[4] = -1;
    D_MA_801BE2F0[5] = 0;
    D_i5_801BA1E4 = 0;
    D_MA_801BE250[6] = 0.0f;
    D_MA_801BE250[16] = 0.0f;
    D_MA_801BE250[20] = 0.0f;
    D_MA_801BA1E8 = 98;
    D_i5_801BA1E0 = 1e7f;
    D_i5_801BE310 = 999;
    D_i5_801BE312 = 0;
    D_i5_801BE313 = 1;
    D_i5_801BA1D8 = 0;

    Graphics_ClearPrintBuffer(D_i5_801BE308, 0, 8);

    for (i = 0; i < 35; i++) {
        D_i5_801BE320[i] = 0;
    }

    for (i = 0; i < 50; i++) {
        D_i5_801BE368[i] = 0;
    }
}

/* 32 x 32 pixels texture rotation */
void Macbeth_Texture_RotateZ(u8* destTex, u8* srcTex, f32 angle) {
    s32 i;
    s32 j;
    s32 xDest;
    s32 yDest;
    Vec3f var_fs0;
    Vec3f dest;
    Vec3f src;

    Matrix_Push(&gCalcMatrix);

    destTex = SEGMENTED_TO_VIRTUAL(destTex);
    srcTex = SEGMENTED_TO_VIRTUAL(srcTex);

    Matrix_RotateZ(gCalcMatrix, M_DTOR * angle, MTXF_NEW);

    src.z = 0.0f;

    for (i = 0, var_fs0.y = 0.0f; i < 32; i++, var_fs0.y++) {
        for (j = 0, var_fs0.x = 0.0f; j < 32; j++, var_fs0.x++) {
            src.y = var_fs0.y - 16.0f;
            src.x = var_fs0.x - 16.0f;

            Matrix_MultVec3f(gCalcMatrix, &src, &dest);

            xDest = (s32) (dest.x + 16.0f);
            yDest = (s32) (dest.y + 16.0f);

            if ((xDest >= 0) && (xDest < 32) && (yDest >= 0) && (yDest < 32)) {
                destTex[xDest + (yDest << 5)] = srcTex[(i << 5) + j];
            }
        }
    }
    Matrix_Pop(&gCalcMatrix);
}

void Macbeth_Texture_Scroll(u8* tex, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    // return;

    // LTODO: this is causing corruption, overflow.
    // Texture at D_MA_6023228 might be the culprit.
    u8* texPtr = SEGMENTED_TO_VIRTUAL(tex);
    s32 i;
    s32 j;
    u8 a;
    u8 b;

    for (i = arg3; i < arg3 + arg4; i++) {
        b = texPtr[i];
        a = texPtr[i + arg1];

        for (j = 1; j < arg2; j += 2) {
            texPtr[arg1 * (j - 1) + i] = texPtr[arg1 * (j + 1) + i];
            texPtr[arg1 * j + i] = texPtr[arg1 * (j + 2) + i];
        }

        texPtr[((arg2 - 2) * arg1) + i] = b;
        texPtr[((arg2 - 1) * arg1) + i] = a;
    }
}

void Macbeth_Texture_Scroll2(u16* tex, s32 arg1, s32 arg2) {
    u16* texPtr = SEGMENTED_TO_VIRTUAL(tex);
    u16 a;
    s32 i;
    s32 j;

    for (i = 0; i < arg1; i++) {
        a = texPtr[(arg2 - 1) * arg1 + i];

        for (j = arg2; j > 0; j--) {
            texPtr[j * arg1 + i] = texPtr[(j - 1) * arg1 + i];
        }

        texPtr[i] = a;
    }
}

void Macbeth_Train_Init(Actor* this) {
    this->state = 0;
    this->iwork[1] = 0;
    this->iwork[2] = 0;
    this->iwork[3] = 0;
    this->iwork[4] = 0;
    this->iwork[5] = D_i5_801BA1E4;
    this->iwork[7] = 0;
    this->iwork[8] = 0;
    this->iwork[9] = 0;
    this->iwork[10] = 0;

    switch (this->obj.id) {
        case OBJ_ACTOR_MA_LOCOMOTIVE:
            this->health = 50;
            D_i5_801BE314 = this->index;
            break;
        case OBJ_ACTOR_207:
            this->health = 250;
            D_i5_801BE316 = this->index;
            break;
        case OBJ_ACTOR_MA_TRAIN_CAR_2:
            this->health = 20;
            /* fallthrough */
        case OBJ_ACTOR_MA_TRAIN_CAR_3:
            this->health = 20;
            break;
        case OBJ_ACTOR_MA_TRAIN_CAR_5:
            this->health = 20;
            break;
        case OBJ_ACTOR_MA_TRAIN_CAR_6:
            this->health = 200;
            break;
        case OBJ_ACTOR_MA_TRAIN_CAR_7:
            this->health = 80;
            break;
        case OBJ_ACTOR_MA_TRAIN_CAR_4:
            this->health = 160;
        default:
            break;
    }

    this->iwork[12] = 20;
    this->iwork[13] = 0;
    this->iwork[14] = 0;
    this->iwork[16] = 20;
    this->iwork[17] = 0;
    this->iwork[18] = 0;
    this->iwork[20] = 20;
    this->iwork[21] = 0;
    this->iwork[22] = 0;
    this->iwork[23] = 0;
    this->iwork[24] = 0;
    this->iwork[11] = this->health;
    this->iwork[15] = this->health;
    this->iwork[19] = this->health;
    this->fwork[1] = 0.0f;
    this->fwork[5] = 0.0f;
    this->fwork[6] = 0.0f;
    this->fwork[7] = 0.0f;
    this->fwork[8] = 0.0f;
    this->fwork[9] = 0.0f;
    this->fwork[10] = 0.0f;
    this->fwork[11] = 0.0f;
    this->fwork[12] = 0.0f;
    this->fwork[13] = 0.0f;
    this->fwork[14] = 0.0f;
    this->fwork[15] = 0.0f;
    this->fwork[16] = 0.0f;
    this->fwork[17] = 0.0f;
    this->fwork[18] = 0.0f;
    this->fwork[19] = 0.0f;
    this->fwork[20] = 0.0f;
    this->fwork[21] = 0.0f;
    this->fwork[22] = 0.0f;
    this->fwork[23] = 0.0f;
    this->fwork[24] = 0.0f;
    this->fwork[25] = 0.0f;
    this->fwork[26] = 0.0f;
    this->fwork[27] = 0.0f;
    this->fwork[28] = 0.0f;
    this->fwork[29] = 0.0f;
    D_i5_801BA1E4++;
}

void Macbeth_RotateTrainWheels(void) {
    // LTODO: ASAN accuses Heap overflow
    Macbeth_Texture_Scroll(D_MA_6023228, 16, 16, 0, 8);
    Macbeth_Texture_RotateZ(D_MA_6023388, D_Tex_800DB4B8, gGameFrameCount * -20.0f);
}

void Macbeth_8019A198(Actor* this) {
    if ((this->iwork[5] >= D_i5_801BA1E4) || (this->iwork[5] >= D_MA_801BE2F0[3])) {
        Math_SmoothStepToF(&this->vel.z, 0.0f, 0.02f, 10.0f, 0.01f);
    } else {
        this->vel.z = sMaTrainSpeedTarget;
        if ((this->iwork[5] == D_MA_801BE2F0[3] - 1) || (this->iwork[5] == D_i5_801BA1E4 - 1)) {
            if (D_i5_801BE310 != this->iwork[5]) {
                if (this->vel.z > -6.0f) {
                    Audio_SetSfxSpeedModulation(-6.0f);
                } else {
                    Audio_SetSfxSpeedModulation(this->vel.z);
                }
                Audio_PlaySfxModulated(this->sfxSource, NA_SE_EN_FREIGHT_TRAIN);
                D_i5_801BE310 = this->iwork[5];
            }

            D_i5_801BA1E0 = this->obj.pos.z;

            if (D_i5_801BE313 != 0) {
                if (this->vel.z > -6.0f) {
                    Audio_SetSfxSpeedModulation(-6.0f);
                } else {
                    Audio_SetSfxSpeedModulation(this->vel.z);
                }
            }
        }
    }
}

void Macbeth_8019A2F4(MaLocomotive* this) {
    f32 var_fa1 = 0.0f;
    f32 var_ft4 = 0.0f;
    u8 i;
    s32 j;

    for (i = D_MA_801BE2F0[0]; D_i5_801BA1EC[i].unk_00 != -1.0f; i++) {
        if (D_i5_801BA1EC[i].unk_00 < gPlayer[0].trueZpos) {
            j = i;
            if (i == 0) {
                j = 1;
            }

            D_MA_801BE2F0[0] = j;

            if (D_i5_801BA1E4 != D_i5_801BA1EC[j - 1].unk_04) {
                AUDIO_PLAY_SFX(NA_SE_OB_CONNECT_CUT, this->sfxSource, 0);
            }

            D_i5_801BA1E4 = D_i5_801BA1EC[j - 1].unk_04;

            var_fa1 = D_i5_801BA1EC[j - 1].unk_08;
            var_ft4 = D_i5_801BA1EC[j - 1].unk_0C;

            D_MA_801BE2F0[4] = D_i5_801BA1EC[j - 1].unk_10;

            if (D_i5_801BA1EC[j - 1].unk_10 >= 300) {
                D_i5_801BE320[18] = (D_i5_801BA1EC[j - 1].unk_10 - 300);
            } else if (D_i5_801BA1EC[j - 1].unk_10 == 200) {
                if (D_i5_801BE320[16] == 0) {
                    D_i5_801BE320[16] = 1;
                }
            } else if (D_i5_801BA1EC[j - 1].unk_10 == 201) {
                D_i5_801BE320[17] = 1;
            } else if (D_i5_801BA1EC[j - 1].unk_10 == 202) {
                D_i5_801BE320[26] = 0;
            } else if (D_i5_801BA1EC[j - 1].unk_10 == 203) {
                D_i5_801BE320[26] = 1;
            } else if (D_i5_801BA1EC[j - 1].unk_10 >= 100) {
                D_MA_801BA1E8 = D_i5_801BA1EC[j - 1].unk_10;
            }
            break;
        }
    }

    if (D_i5_801BE320[16] != 0) {
        switch (D_i5_801BE320[19]) {
            case 0:
                var_fa1 = 1000.0f;
                var_ft4 = 700.0f;
                break;
            case 1:
                var_fa1 = -200.0f;
                var_ft4 = -250.0f;
                break;
        }
    }

    if (gPlayer[0].state != PLAYERSTATE_LEVEL_COMPLETE) {
        if (var_fa1 < (gPlayer[0].trueZpos - this->obj.pos.z - (D_i5_801BA1E4 * 1416 - 1416))) {
            Math_SmoothStepToF(&sMaTrainSpeedTarget, -6.0f, 0.1f, 0.2f, 0.01f);
        }

        if ((gPlayer[0].trueZpos - this->obj.pos.z - (D_i5_801BA1E4 * 1416 - 1416)) < var_ft4) {
            Math_SmoothStepToF(&sMaTrainSpeedTarget, -30.0f, 0.1f, 0.2f, 0.01f);
        }

        if ((D_i5_801BA1E4 < 5) && (gPlayer[0].trueZpos - this->obj.pos.z > 4000.0f)) {
            Math_SmoothStepToF(&sMaTrainSpeedTarget, 0.0f, 0.1f, 1.0f, 0.01f);
        }

        if (gPlayer[0].trueZpos - this->obj.pos.z > 25000.0f) {
            sMaTrainSpeedTarget = 0.0f;
        }
        if (gPlayer[0].trueZpos - this->obj.pos.z < -8000.0f) {
            sMaTrainSpeedTarget = -200.0f;
        }
    }
}

void Macbeth_8019A728(Actor* this) {
    u8 i;
    u32 j;

    for (i = this->iwork[2]; D_i5_801BA1EC[i].unk_00 != -1.0f; i++) {
        if (D_i5_801BA1EC[i].unk_00 < this->obj.pos.z) {
            j = i;
            if (i == 0) {
                j = 1;
            }
            this->iwork[2] = j;

            if ((D_i5_801BA1EC[j - 1].unk_10 == this->iwork[5]) && (this->iwork[1] == 0)) {
                if (this->obj.id == OBJ_ACTOR_MA_TRAIN_CAR_6) {
                    this->timer_0BC = 30;
                    Radio_PlayMessage(gMsg_ID_17476, RCID_BOSS_MACBETH);
                }
                this->iwork[1] = 1;
            }
            break;
        }
    }
}

void Macbeth_8019A830(Actor* this) {
    if ((gPlayer[0].trueZpos - this->obj.pos.z) < -20000.0f) {
        Object_Kill(&this->obj, this->sfxSource);
    }
}

void Macbeth_8019A87C(Actor* this) {
    if ((gPlayer[0].trueZpos - this->obj.pos.z) < -2000.0f) {
        Object_Kill(&this->obj, this->sfxSource);
    }
}

void Macbeth_8019A8C8(Actor* this, s16 arg1) {
    s32 i;

    Effect386_Spawn1(this->obj.pos.x + this->fwork[25], this->obj.pos.y + 290.0f, this->obj.pos.z, 0.0f, 0.0f, 0.0f,
                     22.0f, 5);

    for (i = 0; i < 10; i++) {
        Macbeth_Effect357_Spawn1(
            this->obj.pos.x + RAND_FLOAT_CENTERED(200.0f) + this->fwork[21],
            this->obj.pos.y + 280.0f + RAND_FLOAT_CENTERED(100.0f), this->obj.pos.z - 420.0f + RAND_FLOAT(50.0f),
            RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT(7.0f) + 7.0f, RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT(360.0f),
            RAND_FLOAT(360.0f), RAND_FLOAT(360.0f), RAND_FLOAT_CENTERED(30.0f), RAND_FLOAT_CENTERED(30.0f),
            RAND_FLOAT_CENTERED(30.0f), (s32) (RAND_FLOAT(50.0f) + 70.0f), arg1, RAND_FLOAT(0.8f) + 0.3f);
        Macbeth_Effect357_Spawn1(
            this->obj.pos.x + RAND_FLOAT_CENTERED(200.0f) + this->fwork[25],
            this->obj.pos.y + 280.0f + RAND_FLOAT_CENTERED(100.0f), this->obj.pos.z + RAND_FLOAT(50.0f),
            RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT(7.0f) + 7.0f, RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT(360.0f),
            RAND_FLOAT(360.0f), RAND_FLOAT(360.0f), RAND_FLOAT_CENTERED(30.0f), RAND_FLOAT_CENTERED(30.0f),
            RAND_FLOAT_CENTERED(30.0f), (s32) (RAND_FLOAT(50.0f) + 70.0f), arg1, RAND_FLOAT(0.8f) + 0.3f);
        Macbeth_Effect357_Spawn1(this->obj.pos.x + RAND_FLOAT_CENTERED(200.0f) + this->fwork[23],
                                 this->obj.pos.y + 280.0f + RAND_FLOAT_CENTERED(100.0f),
                                 this->obj.pos.z + 420.0f + 100.0f + RAND_FLOAT(50.0f), RAND_FLOAT_CENTERED(10.0f),
                                 RAND_FLOAT(7.0f) + 7.0f, RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT(360.0f),
                                 RAND_FLOAT(360.0f), RAND_FLOAT(360.0f), RAND_FLOAT_CENTERED(30.0f),
                                 RAND_FLOAT_CENTERED(30.0f), RAND_FLOAT_CENTERED(30.0f),
                                 (s32) (RAND_FLOAT(50.0f) + 70.0f), arg1, RAND_FLOAT(0.8f) + 0.3f);
    }
    AUDIO_PLAY_SFX(NA_SE_EN_EXPLOSION_L, this->sfxSource, 4);
}

void Macbeth_8019AF34(Actor* this) {
    s32 i;

    Effect386_Spawn1(this->obj.pos.x + this->fwork[25], this->obj.pos.y + 290.0f, this->obj.pos.z, 0.0f, 0.0f, 0.0f,
                     22.0f, 5);

    for (i = 0; i < 10; i++) {
        Macbeth_Effect357_Spawn1(
            this->obj.pos.x + RAND_FLOAT_CENTERED(200.0f) + this->fwork[21],
            this->obj.pos.y + 280.0f + RAND_FLOAT_CENTERED(100.0f), this->obj.pos.z - 420.0f + RAND_FLOAT(50.0f),
            RAND_FLOAT_CENTERED(50.0f), RAND_FLOAT(30.0f) + 7.0f, RAND_FLOAT_CENTERED(30.0f), RAND_FLOAT(360.0f),
            RAND_FLOAT(360.0f), RAND_FLOAT(360.0f), RAND_FLOAT_CENTERED(30.0f), RAND_FLOAT_CENTERED(30.0f),
            RAND_FLOAT_CENTERED(30.0f), (s32) (RAND_FLOAT(50.0f) + 70.0f), 1, RAND_FLOAT(0.8f) + 0.3f);
        Macbeth_Effect357_Spawn1(
            this->obj.pos.x + RAND_FLOAT_CENTERED(200.0f) + this->fwork[25],
            this->obj.pos.y + 280.0f + RAND_FLOAT_CENTERED(100.0f), this->obj.pos.z + RAND_FLOAT(50.0f),
            RAND_FLOAT_CENTERED(45.0f), RAND_FLOAT(25.0f) + 7.0f, RAND_FLOAT_CENTERED(20.0f), RAND_FLOAT(360.0f),
            RAND_FLOAT(360.0f), RAND_FLOAT(360.0f), RAND_FLOAT_CENTERED(30.0f), RAND_FLOAT_CENTERED(30.0f),
            RAND_FLOAT_CENTERED(30.0f), (s32) (RAND_FLOAT(50.0f) + 70.0f), 1, 2.0f * (RAND_FLOAT(0.8f) + 0.3f));
        Macbeth_Effect357_Spawn1(this->obj.pos.x + RAND_FLOAT_CENTERED(200.0f) + this->fwork[23],
                                 this->obj.pos.y + 280.0f + RAND_FLOAT_CENTERED(100.0f),
                                 this->obj.pos.z + 420.0f + 100.0f + RAND_FLOAT(50.0f), RAND_FLOAT_CENTERED(40.0f),
                                 RAND_FLOAT(35.0f) + 7.0f, RAND_FLOAT_CENTERED(20.0f), RAND_FLOAT(360.0f),
                                 RAND_FLOAT(360.0f), RAND_FLOAT(360.0f), RAND_FLOAT_CENTERED(30.0f),
                                 RAND_FLOAT_CENTERED(30.0f), RAND_FLOAT_CENTERED(30.0f),
                                 (s32) (RAND_FLOAT(50.0f) + 70.0f), 1, RAND_FLOAT(0.8f) + 0.3f);
    }
    AUDIO_PLAY_SFX(NA_SE_EN_EXPLOSION_L, this->sfxSource, 4);
}

void Macbeth_8019B580(Actor* this, s32* arg1) {
    if (*arg1 > 10) {
        return;
    }
    if ((gGameFrameCount % 32U) == 0) {
        func_effect_8007D2C8(this->obj.pos.x + RAND_FLOAT_CENTERED(200.0f) + this->fwork[21],
                             this->obj.pos.y + 280.0f + RAND_FLOAT_CENTERED(100.0f),
                             this->obj.pos.z - 420.0f + RAND_FLOAT(50.0f), 10.0f);
    } else if ((gGameFrameCount % 32U) == 8) {
        func_effect_8007D2C8(this->obj.pos.x + RAND_FLOAT_CENTERED(200.0f) + this->fwork[25],
                             this->obj.pos.y + 280.0f + RAND_FLOAT_CENTERED(100.0f),
                             this->obj.pos.z + RAND_FLOAT(50.0f), 10.0f);
    } else if ((gGameFrameCount % 32U) == 16) {
        func_effect_8007D2C8(this->obj.pos.x + RAND_FLOAT_CENTERED(200.0f) + this->fwork[23],
                             this->obj.pos.y + 280.0f + RAND_FLOAT_CENTERED(100.0f),
                             (this->obj.pos.z + 320.0f) + RAND_FLOAT(50.0f), 10.0f);
    } else if ((gGameFrameCount % 32U) == 24) {
        func_effect_8007D2C8(this->obj.pos.x + RAND_FLOAT_CENTERED(200.0f) + this->fwork[25],
                             this->obj.pos.y + 280.0f + RAND_FLOAT_CENTERED(100.0f),
                             this->obj.pos.z + RAND_FLOAT(50.0f), 10.0f);
    }
    if ((u16) (gGameFrameCount % 4U) == 0) { // fake?
        Effect_Effect390_Spawn(this->obj.pos.x + this->fwork[25], this->obj.pos.y + 350.0f, this->obj.pos.z,
                               this->vel.x, this->vel.y, this->vel.z, 0.2f, 10);
    }
}

void Macbeth_8019B8B0(Actor* this) {
    if ((gGameFrameCount % 4U) == 0) {
        func_effect_8007D2C8(this->obj.pos.x + RAND_FLOAT_CENTERED(200.0f) + this->fwork[21],
                             this->obj.pos.y + 280.0f + RAND_FLOAT_CENTERED(100.0f),
                             this->obj.pos.z - 420.0f + RAND_FLOAT(50.0f), 20.0f);
    } else if ((gGameFrameCount % 4U) == 1) {
        func_effect_8007D2C8(this->obj.pos.x + RAND_FLOAT_CENTERED(200.0f) + this->fwork[25],
                             this->obj.pos.y + 280.0f + RAND_FLOAT_CENTERED(100.0f),
                             RAND_FLOAT(50.0f) + this->obj.pos.z, 20.0f);
    } else if ((gGameFrameCount % 4U) == 2) {
        func_effect_8007D2C8(this->obj.pos.x + RAND_FLOAT_CENTERED(200.0f) + this->fwork[23],
                             this->obj.pos.y + 280.0f + RAND_FLOAT_CENTERED(100.0f),
                             RAND_FLOAT(50.0f) + (this->obj.pos.z + 420.0f), 20.0f);
    } else if ((gGameFrameCount % 4U) == 3) {
        func_effect_8007D2C8(this->obj.pos.x + RAND_FLOAT_CENTERED(200.0f) + this->fwork[25],
                             this->obj.pos.y + 280.0f + RAND_FLOAT_CENTERED(100.0f),
                             RAND_FLOAT(50.0f) + this->obj.pos.z, 20.0f);
    }
    if ((gGameFrameCount % 4U) == 0) {
        Effect_Effect390_Spawn(this->obj.pos.x + this->fwork[25], this->obj.pos.y + 350.0f, this->obj.pos.z,
                               this->vel.x, this->vel.y, this->vel.z, 0.2f, 20);
    }
}

void Macbeth_8019BBEC(Actor* this) {
    if ((this->timer_0BC % 16U) == 0) {
        func_effect_8007D2C8(this->obj.pos.x + RAND_FLOAT_CENTERED(200.0f) + this->fwork[21],
                             RAND_FLOAT_CENTERED(100.0f) + (this->obj.pos.y + 100.0f),
                             RAND_FLOAT(50.0f) + (this->obj.pos.z - 400.0f), 3.0f);
    } else if ((this->timer_0BC % 16U) == 4) {
        func_effect_8007D2C8(this->obj.pos.x + RAND_FLOAT_CENTERED(200.0f) + this->fwork[25],
                             RAND_FLOAT_CENTERED(100.0f) + (this->obj.pos.y + 100.0f),
                             RAND_FLOAT(50.0f) + this->obj.pos.z, 3.0f);
    } else if ((this->timer_0BC % 16U) == 8) {
        func_effect_8007D2C8(this->obj.pos.x + RAND_FLOAT_CENTERED(200.0f) + this->fwork[23],
                             RAND_FLOAT_CENTERED(100.0f) + (this->obj.pos.y + 100.0f),
                             RAND_FLOAT(50.0f) + (this->obj.pos.z + 450.0f), 3.0f);
    } else if ((this->timer_0BC % 16U) == 12) {
        Effect_Effect390_Spawn(this->obj.pos.x + this->fwork[25], this->obj.pos.y + 100.0f, this->obj.pos.z,
                               this->vel.x, this->vel.y, this->vel.z, 0.15f, 10);
    }
}

void Macbeth_8019BE50(Actor* this) {
    s16 i;

    Effect386_Spawn1(this->obj.pos.x + this->fwork[25], this->obj.pos.y + 90.0f, this->obj.pos.z, 0.0f, 0.0f, 0.0f,
                     10.0f, 5);
    Effect386_Spawn1(this->obj.pos.x + this->fwork[23], this->obj.pos.y + 90.0f, this->obj.pos.z + 420.0f + 300.0f,
                     0.0f, 0.0f, 0.0f, 10.0f, 5);

    for (i = 0; i < 10; i++) {
        Macbeth_Effect357_Spawn1(
            this->obj.pos.x + RAND_FLOAT_CENTERED(200.0f) + this->fwork[21],
            this->obj.pos.y + 80.0f + RAND_FLOAT_CENTERED(100.0f), this->obj.pos.z - 420.0f + RAND_FLOAT(50.0f),
            RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT(7.0f) + 7.0f, RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT(360.0f),
            RAND_FLOAT(360.0f), RAND_FLOAT(360.0f), RAND_FLOAT_CENTERED(30.0f), RAND_FLOAT_CENTERED(30.0f),
            RAND_FLOAT_CENTERED(30.0f), (s32) (RAND_FLOAT(50.0f) + 70.0f), 0, RAND_FLOAT(0.8f) + 0.3f);
        Macbeth_Effect357_Spawn1(
            this->obj.pos.x + RAND_FLOAT_CENTERED(200.0f) + this->fwork[25],
            this->obj.pos.y + 80.0f + RAND_FLOAT_CENTERED(100.0f), this->obj.pos.z + RAND_FLOAT(50.0f),
            RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT(10.0f) + 7.0f, RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT(360.0f),
            RAND_FLOAT(360.0f), RAND_FLOAT(360.0f), RAND_FLOAT_CENTERED(30.0f), RAND_FLOAT_CENTERED(30.0f),
            RAND_FLOAT_CENTERED(30.0f), (s32) (RAND_FLOAT(50.0f) + 70.0f), 0, (RAND_FLOAT(0.8f) + 0.3f));
        Macbeth_Effect357_Spawn1(this->obj.pos.x + RAND_FLOAT_CENTERED(200.0f) + this->fwork[23],
                                 this->obj.pos.y + 80.0f + RAND_FLOAT_CENTERED(100.0f),
                                 this->obj.pos.z + 420.0f + 100.0f + RAND_FLOAT(50.0f), RAND_FLOAT_CENTERED(10.0f),
                                 RAND_FLOAT(7.0f) + 7.0f, RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT(360.0f),
                                 RAND_FLOAT(360.0f), RAND_FLOAT(360.0f), RAND_FLOAT_CENTERED(30.0f),
                                 RAND_FLOAT_CENTERED(30.0f), RAND_FLOAT_CENTERED(30.0f),
                                 (s32) (RAND_FLOAT(50.0f) + 70.0f), 0, RAND_FLOAT(0.8f) + 0.3f);
    }
    Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_EXPLOSION_L);
    gHitCount++;
}

bool Macbeth_MaLocomotive_HandleDamage(MaLocomotive* this) {
    if (this->dmgType != DMG_NONE) {
        this->dmgType = DMG_NONE;
        if (this->dmgPart == 1) {
            AUDIO_PLAY_SFX(NA_SE_OB_DAMAGE_M, this->sfxSource, 4);
            this->dmgType = DMG_NONE;
            this->iwork[7] = 15;
            D_i5_801BE320[22] = 0;
            D_i5_801BE320[4] = 120;
            D_i5_801BE320[21] = 2;
            return true;
        }
        AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
    }

    return false;
}

void Macbeth_8019C5B8(Actor* this) {
    f32 var_ft4;

    Macbeth_801A0308(this, this->obj.pos.z + 520.0f, this->obj.rot.y, 0);
    var_ft4 = RAND_FLOAT_CENTERED(12.0f);
    if ((var_ft4 > -2.0f) && (var_ft4 < 2.0f)) {
        if (var_ft4 >= 0.0f) {
            var_ft4 = 2.5f;
        } else {
            var_ft4 = -2.5f;
        }
    }
    Macbeth_MaShockBox_Spawn(this->fwork[19], this->obj.pos.y + 300.0f, this->obj.pos.z + 520.0f, var_ft4, 10.0f, 0.0f);
}

void Macbeth_Boss_HitCountBonus(MaLocomotive* this) {
    s32 hitBonus;

    if (gBossFrameCount < 3840) {
        hitBonus = 10;
    } else if (gBossFrameCount < 5760) {
        hitBonus = 5;
    } else if (gBossFrameCount < 7680) {
        hitBonus = 2;
    } else if (gBossFrameCount < 9600) {
        hitBonus = 1;
    } else {
        hitBonus = 0;
    }

    if (hitBonus != 0) {
        BonusText_Display(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, hitBonus);
    }

    gHitCount += hitBonus + 1;
    D_ctx_80177850 = 15;
}

void Macbeth_MaLocomotive_Update(MaLocomotive* this) {
    if (this->vel.z < -3.0f) {
        Macbeth_RotateTrainWheels();
    }

    D_i5_801BE368[4] = this->vwork[0].x + this->obj.pos.x;
    D_i5_801BE368[5] = this->vwork[0].y + this->obj.pos.y;
    D_i5_801BE368[6] = this->vwork[0].z + this->obj.pos.z;

    Macbeth_8019A2F4(this);
    Macbeth_8019A198(this);
    Macbeth_801A015C(this);
    Macbeth_8019A830(this);

    switch (this->state) {
        s32 pad;

        case 0:
            D_i5_801BE320[25] = 1;
            if ((D_i5_801BE320[9] <= 0) && (D_i5_801BE320[10] <= 0) && (D_i5_801BE320[17] != 0) &&
                (gPlayer[0].state != PLAYERSTATE_LEVEL_COMPLETE)) {
                D_i5_801BE320[30] = 0;
                this->timer_0BC = 150;
                this->timer_0BE = 200;
                D_i5_801BE320[19] = 1;
                this->state++;
            }
            break;

        case 1:
            if (this->timer_0BC == 1) {
                AUDIO_PLAY_SFX(NA_SE_OB_GATE_OPEN, this->sfxSource, 4);
            }
            if (this->timer_0BC <= 0) {
                Math_SmoothStepToF(&this->fwork[2], -60.0f, 0.4f, 10.0f, 0.01f);
                if (this->timer_0BE == 30) {
                    Macbeth_8019C5B8(this);
                    Radio_PlayMessage(gMsg_ID_17470, RCID_BOSS_MACBETH);
                }
                if ((this->fwork[2] < -58.0f) &&
                    ((Macbeth_MaLocomotive_HandleDamage(this) != 0) || (this->timer_0BE <= 0))) {
                    this->timer_0BC = 200;
                    D_i5_801BE320[19] = 0;
                    this->state++;
                    AUDIO_PLAY_SFX(NA_SE_OB_GATE_CLOSE, this->sfxSource, 4);
                }
            }
            break;

        case 2:
            Math_SmoothStepToF(&this->fwork[2], 0.0f, 0.4f, 30.0f, 0.01f);
            if ((this->timer_0BC <= 0) && (D_i5_801BE320[25] == 1)) {
                this->timer_0BC = 60;
                this->state++;
                AUDIO_PLAY_SFX(NA_SE_OB_GATE_OPEN, this->sfxSource, 4);
            }
            break;

        case 3:
            Math_SmoothStepToF(&this->fwork[2], -60.0f, 0.4f, 10.0f, 0.01f);

            if ((this->fwork[2] < -58.0f) && (Macbeth_MaLocomotive_HandleDamage(this) != 0)) {
                this->timer_0BC = 150;
                this->state--;
                D_i5_801BE320[30]++;
                if (D_i5_801BE320[30] >= 2) {
                    D_i5_801BE320[30] = 0;
                    D_i5_801BE320[25] = 0;
                }
                AUDIO_PLAY_SFX(NA_SE_OB_GATE_CLOSE, this->sfxSource, 4);
            }

            if (this->timer_0BC <= 0) {
                D_i5_801BE320[30]++;
                if (D_i5_801BE320[30] >= 2) {
                    D_i5_801BE320[30] = 0;
                    D_i5_801BE320[25] = 0;
                }
                this->timer_0BC = 100;
                this->state--;
                AUDIO_PLAY_SFX(NA_SE_OB_GATE_CLOSE, this->sfxSource, 4);
            }

            if (this->timer_0BC == 30) {
                Macbeth_8019C5B8(this);
            }
            break;

        case 4:
            Macbeth_8019AF34(this);
            this->health = 0;
            this->timer_0BC = 200;
            gCameraShake = 30;
            this->state++;
            break;

        case 5:
            if (this->timer_0BC == 198) {
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = gFillScreenAlpha = 255;
            } else if (this->timer_0BC == 197) {
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = gFillScreenAlpha = 0;
            }
            if (((this->timer_0BC < 150) || (this->timer_0BC > 170)) && (this->timer_0BC > 80)) {
                Macbeth_8019B8B0(this);
            }
            if (this->timer_0BC == 160) {
                gShowBossHealth = false;
                Radio_PlayMessage(gMsg_ID_17440, RCID_BOSS_MACBETH);
                Effect_Effect383_Spawn(this->obj.pos.x + this->fwork[25], this->obj.pos.y, this->obj.pos.z, 40.0f);
                Macbeth_Boss_HitCountBonus(this);
                this->vel.z = 0.0f;
                gCameraShake = 25;
            }
            if (this->timer_0BC == 100) {
                Object_Kill(&this->obj, this->sfxSource);
                if (gPlayer[0].state == PLAYERSTATE_ACTIVE) {
                    gPlayer[0].state = PLAYERSTATE_LEVEL_COMPLETE;
                    gPlayer[0].csState = 0;
                    gMissionStatus = MISSION_COMPLETE;
                }
                this->state++;
                Audio_KillSfxBySourceAndId(gPlayer[0].sfxSource, NA_SE_TANK_SLIDE);
                Audio_KillSfxBySourceAndId(gPlayer[0].sfxSource, NA_SE_TANK_BURNER_HALF);
            }
            break;
    }

    if (this->dmgType != DMG_NONE) {
        this->dmgType = DMG_NONE;
        AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
    }

    if (D_i5_801BE320[4] > 0) {
        D_i5_801BE320[4]--;
    }

    this->fwork[3] = 0.0f;

    if (D_i5_801BE320[21] != 0) {
        D_i5_801BE320[22]++;

        if (D_i5_801BE320[22] >= 30) {
            if (D_i5_801BE320[4] == 0) {
                D_i5_801BE320[21] = 0;
            }
            D_i5_801BE320[22] = 0;
        }

        if ((gGameFrameCount % 2) == 0) {
            this->fwork[3] = 15.0f;
        } else {
            this->fwork[3] = -15.0f;
        }
    }

    D_i5_801BE320[20] = this->state;

    if (D_i5_801BE320[23] != 0) {
        D_i5_801BE320[23] = 0;
        this->state = 4;
    }

    if ((gPlayer[0].state == PLAYERSTATE_LEVEL_COMPLETE) && (gCsFrameCount > 630)) {
        Object_Kill(&this->obj, this->sfxSource);
    }
}

void Macbeth_MaTrainCar4_Update(Actor* this) {
    switch (this->state) {
        case 0:
            Macbeth_8019A198(this);
            Macbeth_801A015C(this);
            Macbeth_8019FC54(this, &this->iwork[10], &this->iwork[11], 1, 1, this->fwork[25], 0.0f, &this->iwork[13]);
            Macbeth_8019A728(this);
            if (this->iwork[1] != 0) {
                Macbeth_8019D048(this);
            }
            Macbeth_8019A830(this);
            break;

        case 1:
            if (this->iwork[5] < D_MA_801BE2F0[3]) {
                D_MA_801BE2F0[3] = this->iwork[5];
            }
            this->state = 2;
            Macbeth_801A015C(this);
            Macbeth_8019A830(this);
            break;

        case 2:
            Macbeth_8019BBEC(this);

            if (this->timer_0BC == 0) {
                this->timer_0BC = 60;
            }

            Math_SmoothStepToF(&this->vel.z, 0.0f, 0.02f, 10.0f, 0.01f);
            Macbeth_801A015C(this);
            Macbeth_8019A87C(this);

            if (this->dmgType != DMG_NONE) {
                this->dmgType = DMG_NONE;
                this->timer_0BC = 20;
                Macbeth_8019BE50(this);
                this->state = 3;
            }
            break;

        case 3:
            Macbeth_801A015C(this);
            Math_SmoothStepToF(&this->scale, 0.0f, 0.02f, 10.0f, 0.01f);
            if (this->timer_0BC <= 0) {
                Object_Kill(&this->obj, this->sfxSource);
            }
            break;
    }
}

void Macbeth_8019D048(Actor* this) {
    switch (this->iwork[3]) {
        case 0:
            if (D_i5_801BE320[28] != 0) {
                D_i5_801BE320[28]--;
            }

            if (this->fwork[25] == 0.0f) {
                if (D_i5_801BE320[28] <= 0) {
                    Radio_PlayMessage(gMsg_ID_17390, RCID_BOSS_MACBETH);
                    D_i5_801BE320[28] = 100;
                }

                if (this->obj.pos.x <= gPlayer[0].pos.x) {
                    this->iwork[4] = 1;
                } else {
                    this->iwork[4] = -1;
                }
                this->iwork[3]++;
            }
            break;

        case 1:
            Math_SmoothStepToF(&this->fwork[4], this->iwork[4] * -60.0f, 0.5f, 2.0f, 1.0f);

            if ((this->fwork[4] < -30.0f) || (this->fwork[4] > 30.0f)) {
                Macbeth_MaBoulder_Spawn(this->obj.pos.x + this->fwork[25] + this->iwork[4] * 73.0f,
                                        this->obj.pos.y + this->fwork[8] + 330.0f, this->obj.pos.z,
                                        this->iwork[4] * 70.0f, this->vel.z, this->iwork[4] * -34.0f, 0.0f, 2, 5);
                Macbeth_MaBoulder_Spawn(this->obj.pos.x + this->fwork[25] + this->iwork[4] * 74.0f,
                                        this->obj.pos.y + this->fwork[8] + 330.0f, this->obj.pos.z - 350.0f,
                                        this->iwork[4] * 38.0f, this->vel.z, this->iwork[4] * -34.0f, 0.0f, 4, 6);
                Macbeth_MaBoulder_Spawn(this->obj.pos.x + this->fwork[25] + this->iwork[4] * 74.0f,
                                        this->obj.pos.y + this->fwork[8] + 330.0f, this->obj.pos.z + 350.0f,
                                        this->iwork[4] * 40.0f, this->vel.z, this->iwork[4] * -35.0f, 0.0f, 0, 7);
                Macbeth_MaBoulder_Spawn(this->obj.pos.x + this->fwork[25] + this->iwork[4] * 35.0f,
                                        this->obj.pos.y + this->fwork[8] + 290.0f, this->obj.pos.z - 175.0f,
                                        this->iwork[4] * 20.0f, this->vel.z, this->iwork[4] * -35.0f, 0.0f, 12, 4);
                Macbeth_MaBoulder_Spawn(this->obj.pos.x + this->fwork[25] + this->iwork[4] * 35.0f,
                                        this->obj.pos.y + this->fwork[8] + 290.0f, this->obj.pos.z + 175.0f,
                                        this->iwork[4] * 35.0f, this->vel.z, this->iwork[4] * -35.0f, 0.0f, 14, 5);
                this->iwork[3]++;
                this->info.hitbox = SEGMENTED_TO_VIRTUAL(D_MA_6035DD0);
            }
            break;

        case 2:
            Math_SmoothStepToF(&this->fwork[4], this->iwork[4] * -70.0f, 0.5f, 2.0f, 1.0f);
            this->iwork[3]++;
            break;

        case 3:
            Math_SmoothStepToF(&this->fwork[4], this->iwork[4] * -70.0f, 0.2f, 2.0f, 0.0f);
            if ((this->fwork[4] < -69.0f) || (this->fwork[4] > 69.0f)) {
                this->timer_0BC = 20;
                this->iwork[3]++;
            }
            break;

        case 4:
            if (this->timer_0BC == 0) {
                Math_SmoothStepToF(&this->fwork[4], 0.0f, 0.02f, 2.0f, 0.0f);
            }
            break;

        default:
            break;
    }
}

void Macbeth_MaBoulder_Setup(MaBoulder* this, f32 xPos, f32 yPos, f32 zPos, f32 arg4, f32 zVel, f32 zRot, f32 yRot,
                             s32 arg8, u8 arg9) {
    Actor_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_ACTOR_MA_BOULDER;
    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;
    this->obj.rot.z = zRot;
    this->obj.rot.y = yRot;
    this->timer_0BC = arg8;
    this->timer_0BE = 20;
    this->fwork[0] = arg4;
    this->vel.z = zVel;
    this->work_046 = arg9;
    Object_SetInfo(&this->info, this->obj.id);
}

void Macbeth_MaBoulder_Spawn(f32 xPos, f32 yPos, f32 zPos, f32 arg3, f32 zVel, f32 zRot, f32 yRot, s32 arg7, u8 arg8) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gActors); i++) {
        if (gActors[i].obj.status == OBJ_FREE) {
            Macbeth_MaBoulder_Setup(&gActors[i], xPos, yPos, zPos, arg3, zVel, zRot, yRot, arg7, arg8);
            break;
        }
    }
}

void Macbeth_MaTrainCar3_Update(MaTrainCar3* this) {
    switch (this->state) {
        case 0:
            Macbeth_8019A198(this);
            Macbeth_801A015C(this);
            Macbeth_8019D910(this, &this->iwork[10], &this->iwork[11], 1, this->fwork[21], -420.0f, &this->iwork[12],
                             &this->iwork[13]);
            Macbeth_8019D910(this, &this->iwork[14], &this->iwork[15], 2, this->fwork[25], 0.0f, &this->iwork[16],
                             &this->iwork[17]);
            Macbeth_8019D910(this, &this->iwork[18], &this->iwork[19], 3, this->fwork[23], 420.0f, &this->iwork[20],
                             &this->iwork[21]);
            Macbeth_8019A830(this);
            break;

        case 1:
            if (this->iwork[5] < D_MA_801BE2F0[3]) {
                D_MA_801BE2F0[3] = this->iwork[5];
            }
            this->state = 2;
            Macbeth_801A015C(this);
            Macbeth_8019A830(this);
            break;

        case 2:
            Macbeth_8019BBEC(this);
            if (this->timer_0BC == 0) {
                this->timer_0BC = 60;
            }

            Math_SmoothStepToF(&this->vel.z, 0.0f, 0.02f, 10.0f, 0);
            Macbeth_801A015C(this);
            Macbeth_8019A830(this);

            if (this->dmgType != DMG_NONE) {
                this->dmgType = DMG_NONE;
                this->timer_0BC = 20;
                Macbeth_8019BE50(this);
                this->state = 3;
            }
            break;

        case 3:
            Macbeth_801A015C(this);
            Math_SmoothStepToF(&this->scale, 0.0f, 0.02f, 10.0f, 0.01f);
            if (this->timer_0BC <= 0) {
                Object_Kill(&this->obj, this->sfxSource);
            }
            break;
    }
}

void Macbeth_8019D910(Actor* this, s32* arg1, s32* arg2, s32 arg3, f32 arg4, f32 arg5, s32* arg6, s32* arg7) {
    s32 var_v0;
    u8 i;

    switch (*arg1) {
        case 0:
            if (((this->dmgType != DMG_NONE) && (arg3 == this->dmgPart)) ||
                ((D_MA_801BE2F0[1] - 1 == this->iwork[5]) && (this->iwork[5] < D_MA_801BE2F0[3])) ||
                (((D_MA_801BE2F0[1] + 1) == this->iwork[5]) && (D_MA_801BE2F0[3] < this->iwork[5]))) {
                AUDIO_PLAY_SFX(NA_SE_OB_DAMAGE_M, this->sfxSource, 4);

                this->dmgType = DMG_NONE;

                Effect_Effect390_Spawn(this->obj.pos.x + arg4, this->obj.pos.y + 200.0f, this->obj.pos.z + arg5,
                                       this->vel.x, this->vel.y, this->vel.z, 0.15f, 20);

                this->iwork[arg3 + 6] = 15;

                *arg2 -= this->damage;
                if ((*arg2 <= 0) || ((D_MA_801BE2F0[1] - 1 == this->iwork[5]) && (this->iwork[5] < D_MA_801BE2F0[3])) ||
                    (((D_MA_801BE2F0[1] + 1) == this->iwork[5]) && (D_MA_801BE2F0[3] < this->iwork[5]))) {
                    (*arg1)++;
                }
            } else if ((this->dmgType != DMG_NONE) && (this->dmgPart == 0)) {
                this->dmgType = DMG_NONE;
                AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
            }
            break;

        case 1:
            Effect386_Spawn1(this->obj.pos.x + arg4, this->obj.pos.y + 250.0f, this->obj.pos.z + arg5, 0.0f, 0.0f, 0.0f,
                             10.0f, 5);

            for (i = 0; i < 10; i++) {
                Macbeth_Effect357_Spawn1(
                    this->obj.pos.x + arg4, this->obj.pos.y + 200.0f, this->obj.pos.z + arg5 + RAND_FLOAT(80.0f),
                    RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT(7.0f) + 7.0f, RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT(360.0f),
                    RAND_FLOAT(360.0f), RAND_FLOAT(360.0f), RAND_FLOAT_CENTERED(30.0f), RAND_FLOAT_CENTERED(30.0f),
                    RAND_FLOAT_CENTERED(30.0f), (s32) (RAND_FLOAT(50.0f) + 70.0f), 3, (RAND_FLOAT(0.8f) + 0.3f) * 2.0f);
            }

            AUDIO_PLAY_SFX(NA_SE_EN_EXPLOSION_M, this->sfxSource, 4);
            *arg7 = 1;
            *arg2 = 20;
            (*arg1)++;
            break;

        case 2:
            if (((this->dmgType != DMG_NONE) && (arg3 == this->dmgPart)) ||
                ((D_MA_801BE2F0[1] - 1 == this->iwork[5]) && (this->iwork[5] < D_MA_801BE2F0[3])) ||
                (((D_MA_801BE2F0[1] + 1) == this->iwork[5]) && (D_MA_801BE2F0[3] < this->iwork[5])) ||
                ((this->obj.id == OBJ_ACTOR_MA_TRAIN_CAR_3) && (arg3 == 2))) {
                AUDIO_PLAY_SFX(NA_SE_OB_DAMAGE_M, this->sfxSource, 4);
                this->dmgType = DMG_NONE;
                Effect_Effect390_Spawn(this->obj.pos.x + arg4, this->obj.pos.y + 200.0f, this->obj.pos.z + arg5,
                                       this->vel.x, this->vel.y, this->vel.z, 0.15f, 20);
                this->iwork[arg3 + 6] = 20;
                *arg2 -= this->damage;
                if ((*arg2 <= 0) ||
                    ((D_MA_801BE2F0[1] - 1 == (this->iwork[5])) && (this->iwork[5] < D_MA_801BE2F0[3])) ||
                    (((D_MA_801BE2F0[1] + 1) == this->iwork[5]) && (D_MA_801BE2F0[3] < this->iwork[5])) ||
                    ((this->obj.id == OBJ_ACTOR_MA_TRAIN_CAR_3) && (arg3 == 2))) {
                    gHitCount++;
                    (*arg1)++;
                }
            } else if ((this->dmgType != DMG_NONE) && (this->dmgPart == 0)) {
                this->dmgType = DMG_NONE;
                AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
            }
            break;

        case 3:
            Effect386_Spawn1(this->obj.pos.x + arg4, this->obj.pos.y + 250.0f, this->obj.pos.z + arg5, 0.0f, 0.0f, 0.0f,
                             10.0f, 5);
            if ((this->obj.id != OBJ_ACTOR_MA_TRAIN_CAR_3) || (arg3 != 2)) {
                for (i = 0; i < 15; i++) {
                    Macbeth_Effect357_Spawn1(this->obj.pos.x + arg4, this->obj.pos.y + 200.0f,
                                             this->obj.pos.z + arg5 + RAND_FLOAT(20.0f), RAND_FLOAT_CENTERED(10.0f),
                                             RAND_FLOAT(7.0f) + 7.0f, RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT(360.0f),
                                             RAND_FLOAT(360.0f), RAND_FLOAT(360.0f), RAND_FLOAT_CENTERED(30.0f),
                                             RAND_FLOAT_CENTERED(30.0f), RAND_FLOAT_CENTERED(30.0f),
                                             (s32) (RAND_FLOAT(50.0f) + 70.0f), 2, (RAND_FLOAT(0.8f) + 0.3f) * 1.5f);
                }
            }

            AUDIO_PLAY_SFX(NA_SE_EN_EXPLOSION_M, this->sfxSource, 4);

            *arg7 = 2;

            var_v0 = arg3;
            if (var_v0 == 3) {
                var_v0 = 4;
            }
            this->iwork[22] |= var_v0;

            switch (this->iwork[22]) {
                case 1:
                    this->info.hitbox = SEGMENTED_TO_VIRTUAL(D_MA_6035E68);
                    break;
                case 2:
                    this->info.hitbox = SEGMENTED_TO_VIRTUAL(D_MA_6035ECC);
                    break;
                case 3:
                    this->info.hitbox = SEGMENTED_TO_VIRTUAL(D_MA_6035F30);
                    break;
                case 4:
                    this->info.hitbox = SEGMENTED_TO_VIRTUAL(D_MA_6035F94);
                    break;
                case 5:
                    this->info.hitbox = SEGMENTED_TO_VIRTUAL(D_MA_6035FF8);
                    break;
                case 6:
                    this->info.hitbox = SEGMENTED_TO_VIRTUAL(D_MA_603605C);
                    break;
                case 7:
                    this->state = 1;
                    this->timer_0BC = 60;
                    this->info.hitbox = SEGMENTED_TO_VIRTUAL(D_MA_60359AC);
                    break;
            }
            (*arg1)++;
            break;

        case 4:
            break;

        default:
            break;
    }
}

void Macbeth_MaTrainCar5_Update(MaTrainCar5* this) {
    switch (this->state) {
        case 0:
            Macbeth_8019A198(this);
            Macbeth_801A015C(this);
            Macbeth_8019D910(this, &this->iwork[10], &this->iwork[11], 1, this->fwork[21], -420.0f, &this->iwork[12],
                             &this->iwork[13]);
            Macbeth_8019D910(this, &this->iwork[14], &this->iwork[15], 2, this->fwork[25], 0.0f, &this->iwork[16],
                             &this->iwork[17]);
            Macbeth_8019D910(this, &this->iwork[18], &this->iwork[19], 3, this->fwork[23], 420.0f, &this->iwork[20],
                             &this->iwork[21]);
            Macbeth_8019A830(this);
            break;

        case 1:
            if (this->iwork[5] < D_MA_801BE2F0[3]) {
                D_MA_801BE2F0[3] = this->iwork[5];
            }
            this->state = 2;
            Macbeth_801A015C(this);
            Macbeth_8019A830(this);
            break;

        case 2:
            Macbeth_8019BBEC(this);
            if (this->timer_0BC == 0) {
                this->timer_0BC = 60;
            }
            Math_SmoothStepToF(&this->vel.z, 0.0f, 0.02f, 10.0f, 0.01f);
            Macbeth_801A015C(this);
            Macbeth_8019A87C(this);
            if (this->dmgType != DMG_NONE) {
                this->dmgType = DMG_NONE;
                this->timer_0BC = 20;
                Macbeth_8019BE50(this);
                this->state = 3;
            }
            break;

        case 3:
            Macbeth_801A015C(this);
            Math_SmoothStepToF(&this->scale, 0.0f, 0.02f, 10.0f, 0.01f);
            if (this->timer_0BC <= 0) {
                Object_Kill(&this->obj, this->sfxSource);
            }
            break;
    }
}

f32 D_i5_801BE240;
f32 D_i5_801BE244;
f32 D_i5_801BE248;
f32 D_i5_801BE24C;

void Macbeth_8019E624(Actor* this, s32* arg1, s32* arg2, s32 arg3, f32 arg4, f32 arg5, s32* arg6) {
    switch (*arg1) {
        case 0:
            if (((this->dmgType != DMG_NONE) && (arg3 == this->dmgPart)) ||
                ((D_MA_801BE2F0[1] - 1 == this->iwork[5]) && (this->iwork[5] < D_MA_801BE2F0[3])) ||
                (((D_MA_801BE2F0[1] + 1) == this->iwork[5]) && (D_MA_801BE2F0[3] < this->iwork[5]))) {
                AUDIO_PLAY_SFX(NA_SE_OB_DAMAGE_M, this->sfxSource, 4);

                this->dmgType = DMG_NONE;

                Effect_Effect390_Spawn(this->obj.pos.x + arg4, this->obj.pos.y + 200.0f, this->obj.pos.z + arg5,
                                       this->vel.x, this->vel.y, this->vel.z, 0.15f, 10);

                this->iwork[7] = 15;

                *arg2 -= this->damage;
                if ((*arg2 <= 0) || ((D_MA_801BE2F0[1] - 1 == this->iwork[5]) && (this->iwork[5] < D_MA_801BE2F0[3])) ||
                    (((D_MA_801BE2F0[1] + 1) == this->iwork[5]) && (D_MA_801BE2F0[3] < this->iwork[5]))) {
                    (*arg1)++;
                }
            } else if (this->dmgType != DMG_NONE) {
                this->dmgType = DMG_NONE;
                AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
            }
            Macbeth_8019B580(this, arg2);
            break;

        case 1:
            Macbeth_8019A8C8(this, 5);
            *arg6 = 1;
            *arg2 = 80;
            (*arg1)++;
            break;

        case 2:
            if (((this->dmgType != DMG_NONE) && (arg3 == this->dmgPart)) ||
                ((D_MA_801BE2F0[1] - 1 == this->iwork[5]) && (this->iwork[5] < D_MA_801BE2F0[3])) ||
                (((D_MA_801BE2F0[1] + 1) == this->iwork[5]) && (D_MA_801BE2F0[3] < this->iwork[5]))) {
                AUDIO_PLAY_SFX(NA_SE_OB_DAMAGE_M, this->sfxSource, 4);

                this->dmgType = DMG_NONE;

                Effect_Effect390_Spawn(this->obj.pos.x + arg4, this->obj.pos.y + 200.0f, this->obj.pos.z + arg5,
                                       this->vel.x, this->vel.y, this->vel.z, 0.2f, 10);

                this->iwork[7] = 15;

                *arg2 -= this->damage;
                if ((*arg2 <= 0) || ((D_MA_801BE2F0[1] - 1 == this->iwork[5]) && (this->iwork[5] < D_MA_801BE2F0[3])) ||
                    (((D_MA_801BE2F0[1] + 1) == this->iwork[5]) && (D_MA_801BE2F0[3] < this->iwork[5]))) {
                    gHitCount++;
                    (*arg1)++;
                }
            } else {
                if (this->dmgType != DMG_NONE) {
                    this->dmgType = DMG_NONE;
                    AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
                }
            }
            break;

        case 3:
            Macbeth_8019A8C8(this, 1);
            *arg6 = 2;
            this->info.hitbox = SEGMENTED_TO_VIRTUAL(D_MA_60359AC);
            (*arg1)++;
            this->state = 1;
            break;

        case 4:
            break;
    }
}

void Macbeth_MaTrainCar2_Update(Actor* this) {
    switch (this->state) {
        case 0:
            Macbeth_8019A198(this);
            Macbeth_801A015C(this);
            Macbeth_8019E624(this, &this->iwork[10], &this->iwork[11], 1, this->fwork[25], 0.0f, &this->iwork[13]);
            Macbeth_8019A830(this);
            break;

        case 1:
            if (this->iwork[5] < D_MA_801BE2F0[3]) {
                D_MA_801BE2F0[3] = this->iwork[5];
            }
            Macbeth_801A015C(this);
            Macbeth_8019A830(this);
            this->state = 2;
            break;

        case 2:
            Macbeth_8019BBEC(this);

            if (this->timer_0BC == 0) {
                this->timer_0BC = 60;
            }

            Math_SmoothStepToF(&this->vel.z, 0.0f, 0.02f, 10.0f, 0.01f);
            Macbeth_801A015C(this);
            Macbeth_8019A87C(this);

            if (this->dmgType != DMG_NONE) {
                this->dmgType = DMG_NONE;
                this->timer_0BC = 20;
                Macbeth_8019BE50(this);
                this->state = 3;
            }
            break;

        case 3:
            Macbeth_801A015C(this);
            Math_SmoothStepToF(&this->scale, 0.0f, 0.02f, 10.0f, 0.01f);
            if (this->timer_0BC <= 0) {
                Object_Kill(&this->obj, this->sfxSource);
            }
            break;
    }
}

void Macbeth_8019EBF8(Actor* this, s32* arg1, s32* arg2, s32 arg3, f32 arg4, f32 arg5, s32* arg6) {
    switch (*arg1) {
        case 0:
            if (((this->dmgType != DMG_NONE) && (arg3 == this->dmgPart)) ||
                ((D_MA_801BE2F0[1] - 1 == this->iwork[5]) && (this->iwork[5] < D_MA_801BE2F0[3])) ||
                (((D_MA_801BE2F0[1] + 1) == this->iwork[5]) && (D_MA_801BE2F0[3] < this->iwork[5]))) {
                AUDIO_PLAY_SFX(NA_SE_OB_DAMAGE_M, this->sfxSource, 4);

                this->dmgType = DMG_NONE;

                Effect_Effect390_Spawn(this->obj.pos.x + arg4, this->obj.pos.y + 200.0f, this->obj.pos.z + arg5,
                                       this->vel.x, this->vel.y, this->vel.z, 0.15f, 10);

                this->iwork[7] = 15;

                *arg2 -= this->damage;
                if ((*arg2 <= 0) || ((D_MA_801BE2F0[1] - 1 == this->iwork[5]) && (this->iwork[5] < D_MA_801BE2F0[3])) ||
                    (((D_MA_801BE2F0[1] + 1) == this->iwork[5]) && (D_MA_801BE2F0[3] < this->iwork[5]))) {
                    gHitCount++;
                    (*arg1)++;
                }
            } else if (this->dmgType != DMG_NONE) {
                this->dmgType = DMG_NONE;
                AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
            }
            Macbeth_8019B580(this, arg2);
            break;

        case 1:
            Macbeth_8019AF34(this);
            *arg6 = 2;
            this->info.hitbox = SEGMENTED_TO_VIRTUAL(D_MA_60359AC);
            (*arg1)++;
            break;

        case 2:
            this->state = 1;
            break;
    }
}

void Macbeth_MaTrainCar7_Update(Actor* this) {
    switch (this->state) {
        case 0:
            Macbeth_8019A198(this);
            Macbeth_801A015C(this);
            Macbeth_8019EBF8(this, &this->iwork[10], &this->iwork[11], 1, this->fwork[25], 0.0f, &this->iwork[13]);
            Macbeth_8019A830(this);
            break;

        case 1:
            if (this->iwork[5] < D_MA_801BE2F0[3]) {
                D_MA_801BE2F0[3] = this->iwork[5];
            }

            gFillScreenRed = gFillScreenGreen = gFillScreenBlue = gFillScreenAlpha = 255;
            gCameraShake = 35;

            if ((gPlayer[0].trueZpos - this->obj.pos.z > -200.0f) && (gPlayer[0].trueZpos - this->obj.pos.z < 200.0f) &&
                (gPlayer[0].pos.y - this->obj.pos.y > -300.0f) && (gPlayer[0].pos.y - this->obj.pos.y < 300.0f) &&
                (gPlayer[0].pos.x - this->obj.pos.x > -800.0f) && (gPlayer[0].pos.x - this->obj.pos.x < 800.0f)) {
                gFillScreenRed = gFillScreenAlpha = 255;
                gFillScreenGreen = gFillScreenBlue = 0;
                Player_ApplyDamage(&gPlayer[0], 0, 60);
            }

            Macbeth_801A015C(this);
            Macbeth_8019A830(this);

            D_ctx_801779A8[gMainController] = 100.0f;
            this->state = 2;
            break;

        case 2:
            if (gCameraShake == 20) {
                D_MA_801BE2F0[1] = this->iwork[5];
            }

            Macbeth_8019BBEC(this);

            if (this->timer_0BC == 0) {
                this->timer_0BC = 60;
            }

            Math_SmoothStepToF(&this->vel.z, 0.0f, 0.02f, 10.0f, 0.01f);

            Macbeth_801A015C(this);
            Macbeth_8019A87C(this);

            if (gCameraShake == 20) {
                this->dmgType = DMG_NONE;
                this->timer_0BC = 20;
                Macbeth_8019BE50(this);
                this->state = 3;
            }
            break;

        case 3:
            Macbeth_801A015C(this);
            Math_SmoothStepToF(&this->scale, 0.0f, 0.02f, 10.0f, 0.01f);
            if (this->timer_0BC <= 0) {
                Object_Kill(&this->obj, this->sfxSource);
            }
            break;
    }
}

void Macbeth_8019F164(MaTrainCar6* this) {
    static Vec3f D_i5_801BA708 = { 0.0f, 610.0f, 0.0f };
    static Vec3f D_i5_801BA714 = { 0.0f, 0.0f, 65.0f };
    Vec3f sp84;
    Vec3f sp78;
    Vec3f sp6C;
    Vec3f sp60;
    Vec3f sp54;
    Vec3f sp48;
    s16 i;
    s16 sp44 = 0;

    sp6C.x = gPlayer[0].pos.x - this->obj.pos.x + this->fwork[25];
    sp6C.y = gPlayer[0].pos.y - 25.0f - this->obj.pos.y + this->fwork[8] + 25.0f;
    sp6C.z = gPlayer[0].trueZpos - 500.0f - this->obj.pos.z;

    for (i = 0; i < ARRAY_COUNT(gActors); i++) {
        if ((gActors[i].obj.id == OBJ_ACTOR_MA_FALLING_BOULDER) && (gActors[i].obj.status == OBJ_ACTIVE)) {
            if ((this->obj.pos.z < (gActors[i].obj.pos.z + 3000.0f)) &&
                ((gActors[i].obj.pos.z - this->obj.pos.z) < 5000.0f)) {
                sp6C.x = gActors[i].obj.pos.x - this->obj.pos.x + this->fwork[25];
                sp6C.y = gActors[i].obj.pos.y - this->obj.pos.y + this->fwork[8] + 25.0f;
                sp6C.z = gActors[i].obj.pos.z + 300.0f - this->obj.pos.z;
                sp44 = 1;
            }
            break;
        }
    }

    if ((this->iwork[4] == 0) || (sp44 != 0)) {
        Matrix_RotateZ(gCalcMatrix, -this->obj.rot.z * M_DTOR, MTXF_NEW);
        Matrix_RotateX(gCalcMatrix, -(this->obj.rot.x + this->fwork[29]) * M_DTOR, MTXF_APPLY);
        Matrix_RotateY(gCalcMatrix, -(this->obj.rot.y + this->fwork[26]) * M_DTOR, MTXF_APPLY);

        Matrix_MultVec3f(gCalcMatrix, &sp6C, &sp84);

        sp78.x = sp84.x - D_i5_801BA708.x;
        sp78.y = sp84.y - D_i5_801BA708.y;
        sp78.z = sp84.z - D_i5_801BA708.z;

        Math_SmoothStepToAngle(&this->fwork[4], Math_RadToDeg(Math_Atan2F(sp78.x, sp78.z)), 0.1f, 2.0f, 0.01f);
        Math_SmoothStepToAngle(&this->fwork[3], Math_RadToDeg(-Math_Atan2F(sp78.y, sqrtf(SQ(sp78.x) + SQ(sp78.z)))),
                               0.1f, 2.0f, 0.01f);

        if ((this->fwork[4] > 120.0f) && (this->fwork[4] < 180.0f)) {
            this->fwork[4] = 120.0f;
        }
        if ((this->fwork[4] < 240.0f) && (this->fwork[4] > 180.0f)) {
            this->fwork[4] = 240.0f;
        }

        if ((this->fwork[3] > 60.0f) && (this->fwork[3] < 180.0f)) {
            this->fwork[3] = 60.0f;
        }
        if ((this->fwork[3] < 300.0f) && (this->fwork[3] > 180.0f)) {
            this->fwork[3] = 300.0f;
        }
    }

    Math_SmoothStepToAngle(&this->fwork[2], this->fwork[4], 0.2f, 5.0f, 0.01f);
    Math_SmoothStepToAngle(&this->fwork[1], this->fwork[3], 0.2f, 5.0f, 0.01f);

    Matrix_RotateY(gCalcMatrix, (this->obj.rot.y + this->fwork[26]) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, (this->obj.rot.x + this->fwork[29]) * M_DTOR, MTXF_APPLY);
    Matrix_RotateZ(gCalcMatrix, this->obj.rot.z * M_DTOR, MTXF_APPLY);

    Matrix_MultVec3f(gCalcMatrix, &D_i5_801BA708, &sp84);

    sp60.x = sp84.x + this->obj.pos.x + this->fwork[25];
    sp60.y = sp84.y + this->obj.pos.y + this->fwork[8] + 25.0f;
    sp60.z = sp84.z + this->obj.pos.z;

    sp54.x = this->fwork[1];
    sp54.y = this->fwork[2];
    sp54.z = 0.0f;

    sp48.x = this->obj.rot.x + this->fwork[29];
    sp48.y = this->obj.rot.y + this->fwork[26];
    sp48.z = this->obj.rot.z;

    switch (this->iwork[4]) {
        case 0:
            if (sp44 != 0) {
                sp60.x -= 60.0f;
                func_effect_8007EE68(OBJ_EFFECT_378, &sp60, &sp54, &sp48, &D_i5_801BA714, 1.0f);
                AUDIO_PLAY_SFX(NA_SE_EN_MISSILE_SHOT, this->sfxSource, 4);
                this->iwork[4]++;
            } else if ((D_i5_801BE310 == this->iwork[5]) ||
                       ((gPlayer[0].pos.x - this->obj.pos.x > 300.0f) &&
                        (gPlayer[0].pos.x - this->obj.pos.x < 3000.0f)) ||
                       ((gPlayer[0].pos.x - this->obj.pos.x < -300.0f) &&
                        (gPlayer[0].pos.x - this->obj.pos.x > -3000.0f))) {
                if ((gPlayer[0].trueZpos - this->obj.pos.z < 5000.0f) &&
                    (gPlayer[0].trueZpos - this->obj.pos.z > 200.0f) && (this->timer_0BC == 0) && (this->health != 0)) {
                    sp60.x -= 60.0f;
                    func_effect_8007EE68(OBJ_EFFECT_378, &sp60, &sp54, &sp48, &D_i5_801BA714, 1.0f);
                    AUDIO_PLAY_SFX(NA_SE_EN_MISSILE_SHOT, this->sfxSource, 4);
                    this->iwork[4]++;
                }
            }
            break;

        case 1:
            Math_SmoothStepToF(&this->fwork[0], -100.0f, 0.8f, 30.0f, 20.0f);
            if (this->fwork[0] <= -100.0f) {
                this->iwork[4]++;
            }
            break;

        case 2:
            Math_SmoothStepToF(&this->fwork[0], 0.0f, 0.6f, 30.0f, 0.2f);
            if (this->fwork[0] >= 0.0f) {
                if (sp44 == 0) {
                    this->timer_0BC = 15;
                }
                this->iwork[4]++;
            }
            break;

        case 3:
            if ((this->timer_0BC == 0) && (this->health != 0)) {
                func_effect_8007EE68(OBJ_EFFECT_378, &sp60, &sp54, &sp48, &D_i5_801BA714, 1.0f);
                AUDIO_PLAY_SFX(NA_SE_EN_MISSILE_SHOT, this->sfxSource, 4);
                this->iwork[4]++;
            }
            break;

        case 4:
            Math_SmoothStepToF(&this->fwork[0], -100.0f, 0.8f, 30.0f, 20.0f);
            if (this->fwork[0] <= -100.0f) {
                this->iwork[4]++;
            }
            break;

        case 5:
            Math_SmoothStepToF(&this->fwork[0], 0.0f, 0.6f, 30.0f, 0.2f);
            if (this->fwork[0] >= 0.0f) {
                if (sp44 == 0) {
                    this->timer_0BC = 15;
                }
                this->iwork[4]++;
            }
            break;

        case 6:
            if ((this->timer_0BC == 0) && (this->health != 0)) {
                sp60.x += 60.0f;
                func_effect_8007EE68(OBJ_EFFECT_378, &sp60, &sp54, &sp48, &D_i5_801BA714, 1.0f);
                AUDIO_PLAY_SFX(NA_SE_EN_MISSILE_SHOT, this->sfxSource, 4);
                this->iwork[4]++;
            }
            break;

        case 7:
            Math_SmoothStepToF(&this->fwork[0], -100.0f, 0.8f, 30.0f, 20.0f);
            if (this->fwork[0] <= -100.0f) {
                this->iwork[4]++;
            }
            break;

        case 8:
            Math_SmoothStepToF(&this->fwork[0], 0.0f, 0.6f, 30.0f, 0.2f);
            if (this->fwork[0] >= 0.0f) {
                if (sp44 == 0) {
                    this->timer_0BC = (u32) (RAND_FLOAT(100.0f) + 50.0f);
                }
                this->iwork[4] = 0;
            }
            break;

        default:
            break;
    }
}

void Macbeth_8019FC54(Actor* this, s32* arg1, s32* arg2, s32 arg3, s32 arg4, f32 arg5, f32 arg6, s32* arg7) {
    switch (*arg1) {
        case 0:
            if (((this->dmgType != DMG_NONE) && (this->dmgPart >= arg3) && (arg4 >= this->dmgPart)) ||
                ((D_MA_801BE2F0[1] - 1 == this->iwork[5]) && (this->iwork[5] < D_MA_801BE2F0[3])) ||
                (((D_MA_801BE2F0[1] + 1) == this->iwork[5]) && (D_MA_801BE2F0[3] < this->iwork[5]))) {
                AUDIO_PLAY_SFX(NA_SE_OB_DAMAGE_M, this->sfxSource, 4);

                this->dmgType = DMG_NONE;

                Effect_Effect390_Spawn(this->obj.pos.x + arg5, this->obj.pos.y + 200.0f, this->obj.pos.z + arg6,
                                       this->vel.x, this->vel.y, this->vel.z, 0.15f, 10);
                this->iwork[7] = 15;

                *arg2 -= this->damage;
                if ((*arg2 <= 0) || ((D_MA_801BE2F0[1] - 1 == this->iwork[5]) && (this->iwork[5] < D_MA_801BE2F0[3])) ||
                    (((D_MA_801BE2F0[1] + 1) == this->iwork[5]) && (D_MA_801BE2F0[3] < this->iwork[5]))) {
                    gHitCount++;
                    if ((this->obj.id == OBJ_ACTOR_MA_TRAIN_CAR_4) && (this->iwork[3] < 2)) {
                        gHitCount += 5;
                    }
                    (*arg1)++;
                }
            } else if (this->dmgType != DMG_NONE) {
                this->dmgType = DMG_NONE;
                AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
            }
            Macbeth_8019B580(this, arg2);
            break;

        case 1:
            Macbeth_8019A8C8(this, 6);
            if (this->obj.id == OBJ_ACTOR_MA_TRAIN_CAR_6) {
                Effect386_Spawn1(this->obj.pos.x + this->fwork[25], this->obj.pos.y + 360.0f, this->obj.pos.z, 0.0f,
                                 0.0f, 0.0f, 20.0f, 20);
                Effect386_Spawn1(this->obj.pos.x + this->fwork[25], this->obj.pos.y + 660.0f, this->obj.pos.z, 0.0f,
                                 0.0f, 0.0f, 20.0f, 20);
            }
            *arg7 = 2;
            this->info.hitbox = SEGMENTED_TO_VIRTUAL(D_MA_60359AC);
            (*arg1)++;
            this->state = 1;
            break;

        case 2:
            break;
    }
}

void Macbeth_MaTrainCar6_Update(MaTrainCar6* this) {
    switch (this->state) {
        case 0:
            Macbeth_8019A198(this);
            Macbeth_801A015C(this);
            Macbeth_8019FC54(this, &this->iwork[10], &this->iwork[11], 1, 3, this->fwork[25], 0.0f, &this->iwork[13]);
            Macbeth_8019A728(this);

            if (this->iwork[1] != 0) {
                Macbeth_8019F164(this);
            }

            Macbeth_8019A830(this);
            break;

        case 1:
            if (this->iwork[5] < D_MA_801BE2F0[3]) {
                D_MA_801BE2F0[3] = this->iwork[5];
            }
            this->state = 2;
            Macbeth_801A015C(this);
            Macbeth_8019A830(this);
            break;

        case 2:
            Macbeth_8019BBEC(this);

            if (this->timer_0BC == 0) {
                this->timer_0BC = 60;
            }

            Math_SmoothStepToF(&this->vel.z, 0.0f, 0.02f, 10.0f, 0.01f);

            Macbeth_801A015C(this);
            Macbeth_8019A87C(this);

            if (this->dmgType != DMG_NONE) {
                this->dmgType = DMG_NONE;
                this->timer_0BC = 20;
                Macbeth_8019BE50(this);
                this->state = 3;
            }
            break;

        case 3:
            Macbeth_801A015C(this);
            Math_SmoothStepToF(&this->scale, 0.0f, 0.02f, 10.0f, 0.01f);

            if (this->timer_0BC <= 0) {
                Object_Kill(&this->obj, this->sfxSource);
            }
            break;
    }
}

void Macbeth_801A015C(Actor* this) {
    if (!Macbeth_801A0308(this, this->obj.pos.z, this->obj.rot.y, 0)) {
        this->obj.pos.x = this->fwork[19];
        this->obj.pos.y = this->fwork[5];

        if (!Macbeth_801A0308(this, this->obj.pos.z - 420.0f, this->fwork[22], 1)) {
            this->fwork[21] = this->fwork[19] - this->obj.pos.x;
            this->fwork[22] = this->fwork[20];
            this->fwork[6] = this->fwork[5] - this->obj.pos.y;
            this->fwork[27] = this->fwork[9];

            if (!Macbeth_801A0308(this, this->obj.pos.z + 420.0f, this->fwork[24], 2)) {
                this->fwork[23] = this->fwork[19] - this->obj.pos.x;
                this->fwork[24] = this->fwork[20];
                this->fwork[7] = this->fwork[5] - this->obj.pos.y;
                this->fwork[28] = this->fwork[9];

                if (this->fwork[19] - this->obj.pos.x < this->fwork[21]) {
                    this->fwork[25] = this->fwork[23] + ((this->fwork[21] - this->fwork[23]) / 2);
                } else {
                    this->fwork[25] = this->fwork[21] + ((this->fwork[23] - this->fwork[21]) / 2);
                }

                if (this->fwork[7] < this->fwork[6]) {
                    this->fwork[8] = this->fwork[7] + ((this->fwork[6] - this->fwork[7]) / 2);
                } else {
                    this->fwork[8] = this->fwork[6] + ((this->fwork[7] - this->fwork[6]) / 2);
                }

                this->fwork[26] = (this->fwork[22] + this->fwork[24]) / 2;
                this->fwork[29] = (this->fwork[27] + this->fwork[28]) / 2;
            }
        }
    }
}

bool Macbeth_801A0308(Actor* this, f32 arg1, f32 arg2, u8 arg3) {
    s16 var_a0;
    s16 sp4C;
    f32 temp_fv0;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 sp24;

    switch (D_MA_801BE2F0[5]) {
        case 0:
            for (var_a0 = this->fwork[arg3 + 16]; D_i5_801B8E50[var_a0].unk_10 != 0; var_a0++) {
                if (D_i5_801B8E50[var_a0].unk_00 < arg1) {
                    if (var_a0 == 0) {
                        var_a0 = 1;
                    }

                    sp3C = D_i5_801B8E50[var_a0 - 1].unk_00;
                    sp44 = D_i5_801B8E50[var_a0 - 1].unk_04;
                    sp40 = D_i5_801B8E50[var_a0 - 1].unk_08;
                    sp38 = D_i5_801B8E50[var_a0 - 1].unk_0C;
                    sp4C = D_i5_801B8E50[var_a0 - 1].unk_10;
                    sp2C = D_i5_801B8E50[var_a0].unk_00;
                    sp34 = D_i5_801B8E50[var_a0].unk_04;
                    sp30 = D_i5_801B8E50[var_a0].unk_08;
                    sp28 = D_i5_801B8E50[var_a0].unk_0C;

                    if (sp38 >= 180.0f) {
                        sp38 -= 360.0f;
                    }
                    if (sp28 >= 180.0f) {
                        sp28 -= 360.0f;
                    }

                    if (D_i5_801B8E50[var_a0 - 1].unk_10 == OBJ_SCENERY_MA_SWITCH_TRACK) {
                        sp38 = 0.0f;
                    }
                    if (D_i5_801B8E50[var_a0].unk_10 == OBJ_SCENERY_MA_SWITCH_TRACK) {
                        sp28 = 0.0f;
                    }

                    this->fwork[arg3 + 16] = var_a0;
                    break;
                }
            }

            if (D_i5_801B8E50[var_a0].unk_10 == 0) {
                this->fwork[arg3 + 16] = 1.0f;
            }
            break;

        case 1:
            for (var_a0 = this->fwork[arg3 + 16]; D_i5_801B9A80[var_a0].unk_10 != 0; var_a0++) {
                if (D_i5_801B9A80[var_a0].unk_00 < arg1) {
                    if (var_a0 == 0) {
                        var_a0 = 1;
                    }

                    sp3C = D_i5_801B9A80[var_a0 - 1].unk_00;
                    sp44 = D_i5_801B9A80[var_a0 - 1].unk_04;
                    sp40 = D_i5_801B9A80[var_a0 - 1].unk_08;
                    sp38 = D_i5_801B9A80[var_a0 - 1].unk_0C;
                    sp4C = D_i5_801B9A80[var_a0 - 1].unk_10;
                    sp2C = D_i5_801B9A80[var_a0].unk_00;
                    sp34 = D_i5_801B9A80[var_a0].unk_04;
                    sp30 = D_i5_801B9A80[var_a0].unk_08;
                    sp28 = D_i5_801B9A80[var_a0].unk_0C;

                    if (sp38 >= 180.0f) {
                        sp38 -= 360.0f;
                    }
                    if (sp28 >= 180.0f) {
                        sp28 -= 360.0f;
                    }

                    if (D_i5_801B8E50[var_a0 - 1].unk_10 == OBJ_SCENERY_MA_SWITCH_TRACK) {
                        sp38 = 0.0f;
                    }
                    if (D_i5_801B8E50[var_a0].unk_10 == OBJ_SCENERY_MA_SWITCH_TRACK) {
                        sp28 = 0.0f;
                    }

                    this->fwork[arg3 + 16] = var_a0;
                    break;
                }
            }

            if (D_i5_801B9A80[var_a0].unk_10 == 0) {
                this->fwork[arg3 + 16] = 1.0f;
            }
            break;
    }

    sp24 = 1.0f - ((sp2C - arg1) / (sp2C - sp3C));

    if ((sp4C == OBJ_SCENERY_MA_TRAIN_TRACK_4) || (sp4C == OBJ_SCENERY_MA_TRAIN_TRACK_5) ||
        (sp4C == OBJ_SCENERY_MA_TRAIN_TRACK_7) || (sp4C == OBJ_SCENERY_MA_TRAIN_TRACK_8)) {
        if ((this->iwork[5] < (s32) D_i5_801BA1E4) && (this->iwork[5] < D_MA_801BE2F0[3])) {
            this->vel.z *= 0.98f;
        }

        temp_fv0 = fabsf((sp2C - sp3C) / 3.0f);

        if (sp24 < 0.3333333f) {
            if ((sp4C == OBJ_SCENERY_MA_TRAIN_TRACK_4) || (sp4C == OBJ_SCENERY_MA_TRAIN_TRACK_7)) {
                this->fwork[19] = (((sp34 - sp44) * sp24) + sp44) -
                                  (52.160667f * (1.0f - (((sp3C - temp_fv0) - arg1) / ((sp3C - temp_fv0) - sp3C))));
            } else {
                this->fwork[19] = ((sp34 - sp44) * sp24) + sp44 +
                                  (52.160667f * (1.0f - (((sp3C - temp_fv0) - arg1) / ((sp3C - temp_fv0) - sp3C))));
            }
        } else if (sp24 < 0.666666f) {
            if ((sp4C == OBJ_SCENERY_MA_TRAIN_TRACK_4) || (sp4C == OBJ_SCENERY_MA_TRAIN_TRACK_7)) {
                this->fwork[19] = (((sp34 - sp44) * sp24) + sp44) - 52.160667f;
            } else {
                this->fwork[19] = ((sp34 - sp44) * sp24) + sp44 + 52.160667f;
            }
        } else if ((sp4C == OBJ_SCENERY_MA_TRAIN_TRACK_4) || (sp4C == OBJ_SCENERY_MA_TRAIN_TRACK_7)) {
            this->fwork[19] = (((sp34 - sp44) * sp24) + sp44) -
                              (52.160667f * (1.0f - (1.0f - ((sp2C - arg1) / (sp2C - (sp3C - (temp_fv0 * 2)))))));
        } else {
            this->fwork[19] = ((sp34 - sp44) * sp24) + sp44 +
                              (52.160667f * (1.0f - (1.0f - ((sp2C - arg1) / (sp2C - (sp3C - (temp_fv0 * 2)))))));
        }
    } else {
        if (sp4C == OBJ_SCENERY_MA_SWITCH_TRACK) {
            if ((this->iwork[5] < (s32) D_i5_801BA1E4) && (this->iwork[5] < D_MA_801BE2F0[3])) {
                this->vel.z *= 0.94f;
            }
        }
        this->fwork[19] = ((sp34 - sp44) * sp24) + sp44;
    }

    this->fwork[5] = ((sp30 - sp40) * sp24) + sp40;

    if ((sp4C == OBJ_SCENERY_MA_TRAIN_TRACK_9) || (sp4C == OBJ_SCENERY_MA_TRAIN_TRACK_11)) {
        Math_SmoothStepToF(&this->fwork[9], 3.0f, 0.05f, 1.0f, 0.001f);
    } else if ((sp4C == OBJ_SCENERY_MA_TRAIN_TRACK_10) || (sp4C == OBJ_SCENERY_MA_TRAIN_TRACK_12)) {
        Math_SmoothStepToF(&this->fwork[9], -3.0f, 0.05f, 1.0f, 0.001f);
    } else {
        Math_SmoothStepToF(&this->fwork[9], 0.0f, 0.05f, 1.0f, 0.0f);
    }

    this->fwork[20] = ((sp28 - sp38) * sp24) + sp38;
    return false;
}

bool Macbeth_801A0A74(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    if ((limbIndex == 5) || (limbIndex == 6)) {
        gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
    } else {
        gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
    }
    if ((limbIndex == 2) || (limbIndex == 3)) {
        *dList = NULL;
    }
    return false;
}

bool Macbeth_801A0B00(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    if (limbIndex == 3) {
        *dList = NULL;
    }
    return false;
}

bool Macbeth_801A0B20(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    Actor* actor = (Actor*) thisx;

    if ((limbIndex == 3) || (limbIndex == 7)) {
        gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
    } else {
        gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
    }
    if (limbIndex == 1) {
        pos->z += actor->fwork[0];
    }
    if (limbIndex == 5) {
        rot->x += actor->fwork[1];
        rot->y += actor->fwork[2];
    }
    return false;
}

void Macbeth_MaSwitchTrack_Update(MaSwitchTrack* this) {
    switch (this->state) {
        case 0:
            this->vel.y = 0.0f;
            this->vel.x = 0.0f;
            if (D_i5_801BE312 != 0) {
                this->state = 1;
                this->timer_4C = 20;
            }
            break;

        case 1:
            if (this->timer_4C == 1) {
                AUDIO_PLAY_SFX(NA_SE_TANK_BURNER_HALF, gPlayer[0].sfxSource, 0);
            }
            if (this->timer_4C <= 0) {
                Math_SmoothStepToF(&this->vel.x, 1751.0f, 0.2f, 80.0f, 1.0f);
                if (this->vel.x >= 1750.0) {
                    AUDIO_PLAY_SFX(NA_SE_OB_POINT_SWITCH, this->sfxSource, 0);
                    Audio_KillSfxBySourceAndId(gPlayer[0].sfxSource, NA_SE_TANK_BURNER_HALF);
                    this->timer_4C = 5;
                    this->state = 2;
                }
            }
            break;

        case 2:
            Math_SmoothStepToF(&this->vel.y, -11.0f, 0.1f, 2.5f, 0.01f);
            if (this->vel.y <= -10.0f) {
                this->state = 3;
            }
            break;

        case 3:
            break;
    }

    if (this->timer_4C != 0) {
        this->vel.z = 2.0f + RAND_FLOAT(1.0f);
    } else {
        this->vel.z = 1.0f + RAND_FLOAT(1.0f);
    }
}

bool Macbeth_801A0DD8(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    Scenery* this = (Scenery*) thisx;

    if (limbIndex == 5) {
        rot->y += this->vel.y;
    }
    if ((limbIndex == 1) || (limbIndex == 2)) {
        pos->z -= this->vel.x;
    }
    return false;
}

void Macbeth_801A0E2C(s32 limbIndex, Vec3f* rot, void* thisx) {
    Vec3f sp24 = { 0.0f, 0.0f, 0.0f };
    s32 pad;

    switch (limbIndex) {
        case 1:
            Matrix_MultVec3f(gCalcMatrix, &sp24, &D_i5_801BE688[0]);
            break;
        case 2:
            Matrix_MultVec3f(gCalcMatrix, &sp24, &D_i5_801BE688[1]);
            break;
    }
}

bool Macbeth_MaLocomotive_OverrideLimbDraw(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    MaLocomotive* this = (MaLocomotive*) thisx;

    RCP_SetupDL(&gMasterDisp, SETUPDL_29);
    gSPClearGeometryMode(gMasterDisp++, G_TEXTURE_GEN);

    if ((limbIndex == 3) || (limbIndex == 6) || (limbIndex == 9)) {
        gSPTexture(gMasterDisp++, 3000, 3000, 0, G_TX_RENDERTILE, G_ON);
        gSPSetGeometryMode(gMasterDisp++, G_TEXTURE_GEN);
    }

    if ((limbIndex == 5) || (limbIndex == 9)) {
        if ((this->iwork[7] % 2) != 0) {
            RCP_SetupDL_27();
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
        }
        if ((this->iwork[7] > 0) && (limbIndex == 5)) {
            this->iwork[7]--;
        }
        rot->x += this->fwork[2];
        if (limbIndex == 5) {
            RCP_SetupDL(&gMasterDisp, SETUPDL_34);
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, D_i5_801BE368[20], D_i5_801BE368[21], D_i5_801BE368[22], 255);
            gSPDisplayList(gMasterDisp++, D_MA_6010470);
            RCP_SetupDL(&gMasterDisp, SETUPDL_29);
        }
    }

    switch (limbIndex) {
        case 1:
            rot->x += this->fwork[3] / 2;
            break;
        case 2:
            rot->x -= this->fwork[3] / 2;
            break;
    }
    return false;
}

void Macbeth_MaLocomotive_PostLimbDraw(s32 limbIndex, Vec3f* rot, void* thisx) {
    Vec3f src = { 0.0f, 0.0f, 0.0f };
    MaLocomotive* this = (MaLocomotive*) thisx;

    if (limbIndex == 4) {
        Matrix_MultVec3f(gCalcMatrix, &src, this->vwork);
    }
}

// Actors 205, 206, 208, 209, 210, 211, 212, 213
void Macbeth_Train_Draw(Actor* this) {
    Vec3f frameTable[50];
    s32 id;

    if (gPlayer[0].state == PLAYERSTATE_ACTIVE) {
        if (((gPlayer[0].trueZpos - this->obj.pos.z) > 7000.0f) ||
            ((gPlayer[0].trueZpos - this->obj.pos.z) < -1000.0f)) {
            return;
        }
    } else {
        if (((gPlayer[0].trueZpos - this->obj.pos.z) > 7000.0f) ||
            ((gPlayer[0].trueZpos - this->obj.pos.z) < -5000.0f)) {
            return;
        }
    }

    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, this->fwork[25], this->fwork[8] + 25.0f, 0.0f, MTXF_APPLY);
    Matrix_RotateY(gGfxMatrix, this->fwork[26] * M_DTOR, MTXF_APPLY);
    Matrix_RotateX(gGfxMatrix, this->fwork[29] * M_DTOR, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);

    if ((this->obj.id != OBJ_ACTOR_MA_TRAIN_CAR_1) && (this->obj.id != OBJ_ACTOR_MA_LOCOMOTIVE)) {
        if (((gPlayer[0].trueZpos - this->obj.pos.z) > 3000.0f) && (D_i5_801BE310 != this->iwork[5])) {
            gSPDisplayList(gMasterDisp++, D_MA_6027BF0);
            gSPDisplayList(gMasterDisp++, D_MA_601BE90);
        } else {
            Matrix_Scale(gGfxMatrix, this->scale, this->scale, this->scale, MTXF_APPLY);
            Animation_GetFrameData(&D_MA_602EA0C, 0, frameTable);
            Animation_DrawSkeleton(1, D_MA_602EBB8, frameTable, Macbeth_801A0A74, NULL, this, &gIdentityMatrix);
        }
    }

    switch (this->obj.id) {
        case OBJ_ACTOR_MA_TRAIN_CAR_6:
            if (this->iwork[13] == 0) {
                if ((this->iwork[7] % 2) != 0) {
                    RCP_SetupDL_27();
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
                }
                if (this->iwork[7] > 0) {
                    this->iwork[7]--;
                }
                Animation_GetFrameData(&D_MA_6027320, 0, frameTable);
                Animation_DrawSkeleton(1, D_MA_602742C, frameTable, Macbeth_801A0B20, NULL, this, &gIdentityMatrix);
            }
            break;

        case OBJ_ACTOR_MA_TRAIN_CAR_4:
            if (this->iwork[13] == 0) {
                Animation_GetFrameData(&D_MA_6027A04, 0, frameTable);
                Animation_DrawSkeleton(1, D_MA_6027AF0, frameTable, Macbeth_801A0B00, NULL, this, &gIdentityMatrix);

                Matrix_Translate(gGfxMatrix, 0.0f, 205.0f, 0.0f, MTXF_APPLY);
                Matrix_RotateZ(gGfxMatrix, this->fwork[4] * M_DTOR, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);

                if ((this->iwork[7] % 2) != 0) {
                    RCP_SetupDL_27();
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
                }
                if (this->iwork[7] > 0) {
                    this->iwork[7]--;
                }

                if (this->iwork[3] >= 3) {
                    gSPDisplayList(gMasterDisp++, D_MA_6027EB0);
                } else {
                    gSPDisplayList(gMasterDisp++, D_MA_60288A0);
                }
            }
            break;

        case OBJ_ACTOR_MA_TRAIN_CAR_3:
            if (this->iwork[17] != 2) {
                Matrix_Translate(gGfxMatrix, 0.0f, 5.0f, 0.0f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                if ((this->iwork[8] % 2) != 0) {
                    RCP_SetupDL_27();
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
                }
                if (this->iwork[8] > 0) {
                    this->iwork[8]--;
                }
                gSPDisplayList(gMasterDisp++, D_MA_6029890);
                RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
            }
            break;

        case OBJ_ACTOR_MA_TRAIN_CAR_5:
            if (this->iwork[17] != 2) {
                Matrix_Translate(gGfxMatrix, 0.0f, -15.0f, 0.0f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);

                if ((this->iwork[8] % 2) != 0) {
                    RCP_SetupDL_27();
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
                }
                if (this->iwork[8] > 0) {
                    this->iwork[8]--;
                }
                if (this->iwork[17] == 0) {
                    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
                    gSPDisplayList(gMasterDisp++, D_MA_6004440);
                } else {
                    RCP_SetupDL(&gMasterDisp, SETUPDL_57);
                    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                    gSPDisplayList(gMasterDisp++, D_MA_6022200);
                    RCP_SetupDL(&gMasterDisp, SETUPDL_29);
                }
                RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
            }
            break;

        case OBJ_ACTOR_MA_TRAIN_CAR_7:
            if (this->iwork[13] < 2) {
                Matrix_Translate(gGfxMatrix, 0.0f, -5.0f, 0.0f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                RCP_SetupDL(&gMasterDisp, SETUPDL_57);
                if ((this->iwork[7] % 2) != 0) {
                    RCP_SetupDL_27();
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
                }
                if (this->iwork[7] > 0) {
                    this->iwork[7]--;
                }
                gSPDisplayList(gMasterDisp++, D_MA_6024670);
                RCP_SetupDL(&gMasterDisp, SETUPDL_29);
            }
            break;

        case OBJ_ACTOR_MA_TRAIN_CAR_2:
            if (this->iwork[13] < 2) {
                if ((this->iwork[7] % 2) != 0) {
                    RCP_SetupDL_27();
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
                }
                if (this->iwork[7] > 0) {
                    this->iwork[7]--;
                }
                if (this->iwork[13] == 0) {
                    Matrix_Translate(gGfxMatrix, 0.0f, -5.0f, 0.0f, MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_MA_60269E0);
                } else {
                    Matrix_Translate(gGfxMatrix, 0.0f, -5.0f, 0.0f, MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_MA_6017720);
                }
                gDPSetTextureFilter(gMasterDisp++, G_TF_BILERP);
            }
            break;

        case OBJ_ACTOR_MA_TRAIN_CAR_1:
            Animation_GetFrameData(&D_MA_601EAB0, 0, frameTable);
            Animation_DrawSkeleton(1, D_MA_601EBBC, frameTable, Macbeth_MaTrainCar1_OverrideLimbDraw, NULL, this,
                                   &gIdentityMatrix);
            break;

        case OBJ_ACTOR_MA_LOCOMOTIVE:
            Matrix_Translate(gGfxMatrix, this->fwork[3], 0.0f, 0.0f, MTXF_APPLY);

            if (D_i5_801BE320[21] == 0) {
                Animation_GetFrameData(&D_MA_6010220, 0, frameTable);
            } else if (D_i5_801BE320[21] == 1) {
                Animation_GetFrameData(&D_MA_600FEC4, D_i5_801BE320[22], frameTable);
            } else {
                Animation_GetFrameData(&D_MA_6010144, D_i5_801BE320[22], frameTable);
            }

            Animation_DrawSkeleton(1, D_MA_601042C, frameTable, Macbeth_MaLocomotive_OverrideLimbDraw,
                                   Macbeth_MaLocomotive_PostLimbDraw, this, &gIdentityMatrix);

            if (gPlayer[0].state == PLAYERSTATE_LEVEL_COMPLETE) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_29);
                gSPClearGeometryMode(gMasterDisp++, G_TEXTURE_GEN);
                gSPDisplayList(gMasterDisp++, D_MA_6003370);
            }
            break;
    }

    Matrix_Pop(&gGfxMatrix);
    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, this->fwork[21], this->fwork[6] + 65.0f, -420.0f, MTXF_APPLY);
    Matrix_RotateY(gGfxMatrix, this->fwork[22] * M_DTOR, MTXF_APPLY);
    Matrix_RotateX(gGfxMatrix, this->fwork[27] * M_DTOR, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    Matrix_Scale(gGfxMatrix, this->scale, this->scale, this->scale, MTXF_APPLY);

    if ((gPlayer[0].trueZpos - this->obj.pos.z) > 3000.0f) {
        gSPDisplayList(gMasterDisp++, D_MA_6027D40);
    } else if (this->vel.z > -2.0f) {
        gSPDisplayList(gMasterDisp++, D_MA_60227F0);
    } else {
        gSPDisplayList(gMasterDisp++, D_MA_60239D0);
    }

    Matrix_Pop(&gGfxMatrix);
    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, this->fwork[23], this->fwork[7] + 65.0f, 420.0f, MTXF_APPLY);
    Matrix_RotateY(gGfxMatrix, this->fwork[24] * M_DTOR, MTXF_APPLY);
    Matrix_RotateX(gGfxMatrix, this->fwork[28] * M_DTOR, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, this->scale, this->scale, this->scale, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    RCP_SetupDL(&gMasterDisp, SETUPDL_29);

    if ((gPlayer[0].trueZpos - this->obj.pos.z) > 3000.0f) {
        gSPDisplayList(gMasterDisp++, D_MA_6027D40);
    } else if (this->vel.z > -2.0f) {
        gSPDisplayList(gMasterDisp++, D_MA_60227F0);
    } else {
        gSPDisplayList(gMasterDisp++, D_MA_60239D0);
    }

    Matrix_Pop(&gGfxMatrix);

    id = this->obj.id;
    if ((id == OBJ_ACTOR_MA_TRAIN_CAR_3) || (id == OBJ_ACTOR_MA_TRAIN_CAR_5)) {
        if (this->iwork[13] != 2) {
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, this->fwork[21], this->fwork[6] + 10.0f, -420.0f, MTXF_APPLY);
            Matrix_RotateY(gGfxMatrix, this->fwork[26] * M_DTOR, MTXF_APPLY);
            Matrix_RotateX(gGfxMatrix, this->fwork[29] * M_DTOR, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);

            if ((this->iwork[7] % 2) != 0) {
                RCP_SetupDL_27();
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
            }
            if (this->iwork[7] > 0) {
                this->iwork[7]--;
            }

            if (this->iwork[13] == 0) {
                gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
                gSPDisplayList(gMasterDisp++, D_MA_6004440);
            } else {
                RCP_SetupDL(&gMasterDisp, SETUPDL_57);
                gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                gSPDisplayList(gMasterDisp++, D_MA_6022200);
                RCP_SetupDL(&gMasterDisp, SETUPDL_29);
            }
            RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
            Matrix_Pop(&gGfxMatrix);
        }

        if (this->iwork[21] != 2) {
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, this->fwork[23], this->fwork[7] + 10.0f, 420.0f, MTXF_APPLY);
            Matrix_RotateY(gGfxMatrix, this->fwork[26] * M_DTOR, MTXF_APPLY);
            Matrix_RotateX(gGfxMatrix, this->fwork[29] * M_DTOR, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);

            if ((this->iwork[9] % 2) != 0) {
                RCP_SetupDL_27();
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
            }
            if (this->iwork[9] > 0) {
                this->iwork[9]--;
            }

            if (this->iwork[21] == 0) {
                gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
                gSPDisplayList(gMasterDisp++, D_MA_6004440);
            } else {
                RCP_SetupDL(&gMasterDisp, SETUPDL_57);
                gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                gSPDisplayList(gMasterDisp++, D_MA_6022200);
                RCP_SetupDL(&gMasterDisp, SETUPDL_29);
            }
            RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
            Matrix_Pop(&gGfxMatrix);
        }
    }
}

void Macbeth_TrainTrack_Draw(Scenery* this) {
    Vec3f frameTable[50];

    RCP_SetupDL(&gMasterDisp, SETUPDL_57);

    switch (this->obj.id) {
        case OBJ_SCENERY_MA_TRAIN_TRACK_3:
        case OBJ_SCENERY_MA_TRAIN_TRACK_6:
            if ((gPlayer[0].state != PLAYERSTATE_LEVEL_COMPLETE) &&
                ((gPlayer[0].trueZpos - this->obj.pos.z) < -2500.0f)) {
                Object_Kill(&this->obj, this->sfxSource);
            }
            gSPDisplayList(gMasterDisp++, D_MA_6026860);
            break;

        case OBJ_SCENERY_MA_TRAIN_TRACK_4:
        case OBJ_SCENERY_MA_TRAIN_TRACK_7:
            if ((gPlayer[0].state != PLAYERSTATE_LEVEL_COMPLETE) &&
                ((gPlayer[0].trueZpos - this->obj.pos.z) < -2500.0f)) {
                Object_Kill(&this->obj, this->sfxSource);
            }
            gSPDisplayList(gMasterDisp++, D_MA_602FBF0);
            break;

        case OBJ_SCENERY_MA_TRAIN_TRACK_5:
        case OBJ_SCENERY_MA_TRAIN_TRACK_8:
            gSPDisplayList(gMasterDisp++, D_MA_6022610);
            break;

        case OBJ_SCENERY_MA_TRAIN_TRACK_9:
        case OBJ_SCENERY_MA_TRAIN_TRACK_11:
            gSPDisplayList(gMasterDisp++, D_MA_60309D0);
            break;

        case OBJ_SCENERY_MA_TRAIN_TRACK_10:
        case OBJ_SCENERY_MA_TRAIN_TRACK_12:
            gSPDisplayList(gMasterDisp++, D_MA_6030750);
            break;

        case OBJ_SCENERY_MA_TRAIN_TRACK_13:
            RCP_SetupDL(&gMasterDisp, SETUPDL_29);
            gSPDisplayList(gMasterDisp++, D_MA_602D380);
            break;

        case OBJ_SCENERY_MA_SWITCH_TRACK:
            Matrix_Push(&gGfxMatrix);
            Animation_GetFrameData(&D_MA_6025CA0, 0, frameTable);
            Animation_DrawSkeleton(1, D_MA_6025DAC, frameTable, Macbeth_801A0DD8, Macbeth_801A0E2C, this,
                                   &gIdentityMatrix);
            Matrix_Pop(&gGfxMatrix);

            if ((this->state == 1) && (this->timer_4C <= 0)) {
                Matrix_Push(&gGfxMatrix);
                RCP_SetupDL_49();
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
                gDPSetEnvColor(gMasterDisp++, 255, 48, 0, 255);
                Matrix_Translate(gGfxMatrix, D_i5_801BE688[0].x, D_i5_801BE688[0].y + 50.0f,
                                 D_i5_801BE688[0].z + 100.0f, MTXF_APPLY);
                Matrix_RotateX(gCalcMatrix, (D_PI / 2), MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, this->vel.z, this->vel.z / 2, this->vel.z, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, aOrbDL);
                Matrix_Pop(&gGfxMatrix);
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, D_i5_801BE688[1].x, D_i5_801BE688[1].y + 50.0f,
                                 D_i5_801BE688[1].z + 100.0f, MTXF_APPLY);
                Matrix_RotateX(gCalcMatrix, (D_PI / 2), MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, this->vel.z, this->vel.z / 2, this->vel.z, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, aOrbDL);
                RCP_SetupDL(&gMasterDisp, SETUPDL_29);
                Matrix_Pop(&gGfxMatrix);
            } else if (this->state == 2) {
                Matrix_Push(&gGfxMatrix);
                RCP_SetupDL_49();
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
                gDPSetEnvColor(gMasterDisp++, 255, 48, 0, 255);
                Matrix_Translate(gGfxMatrix, D_i5_801BE688[1].x - 50.0f, D_i5_801BE688[1].y + 50.0f,
                                 D_i5_801BE688[1].z + 50.0f, MTXF_APPLY);
                Matrix_RotateX(gCalcMatrix, (D_PI / 2), MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, this->vel.z, this->vel.z / 2, this->vel.z, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, aOrbDL);
                RCP_SetupDL(&gMasterDisp, SETUPDL_29);
                Matrix_Pop(&gGfxMatrix);
            }

            if (D_MA_801BE2F0[5] != 0) {
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -1800.0f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_MA_601C170);
                Matrix_Pop(&gGfxMatrix);
            } else {
                Matrix_Push(&gGfxMatrix);
                Matrix_RotateY(gGfxMatrix, -(D_PI / 18), MTXF_APPLY);
                Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -1800.0f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_MA_601C170);
                Matrix_Pop(&gGfxMatrix);
            }
            break;

        case OBJ_SCENERY_MA_TRAIN_TRACK_1:
            gSPDisplayList(gMasterDisp++, D_MA_60014A0);
            break;

        case OBJ_SCENERY_MA_TRAIN_TRACK_2:
            gSPDisplayList(gMasterDisp++, D_MA_6001180);
            break;
    }
    RCP_SetupDL(&gMasterDisp, SETUPDL_29);
}

void Macbeth_MaTower_Draw(Scenery* this) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_57);
    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
    gSPDisplayList(gMasterDisp++, aMaTowerBottomDL);
    gSPDisplayList(gMasterDisp++, aMaTowerTopDL);
    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
    RCP_SetupDL(&gMasterDisp, SETUPDL_29);
}

// Scenery 77 to 82, and 84 to 91
void Macbeth_IndicatorSign_Draw(Scenery* this) {
    if (gPlayer[0].state == PLAYERSTATE_LEVEL_COMPLETE) {
        Object_Kill(&this->obj, this->sfxSource);
    }

    RCP_SetupDL(&gMasterDisp, SETUPDL_57);

    switch (this->obj.id) {
        case OBJ_SCENERY_MA_INDICATOR_SIGN:
            gSPDisplayList(gMasterDisp++, aMaIndicatorSignDL);
            break;
        case OBJ_SCENERY_MA_DISTANCE_SIGN_1:
            gSPDisplayList(gMasterDisp++, aMaDistanceSign1DL);
            break;
        case OBJ_SCENERY_MA_DISTANCE_SIGN_2:
            gSPDisplayList(gMasterDisp++, aMaDistanceSign2DL);
            break;
        case OBJ_SCENERY_MA_DISTANCE_SIGN_3:
            gSPDisplayList(gMasterDisp++, aMaDistanceSign3DL);
            break;
        case OBJ_SCENERY_MA_DISTANCE_SIGN_4:
            gSPDisplayList(gMasterDisp++, aMaDistanceSign4DL);
            break;
        case OBJ_SCENERY_MA_DISTANCE_SIGN_5:
            gSPDisplayList(gMasterDisp++, aMaDistanceSign5DL);
            break;
        case OBJ_SCENERY_MA_RAILROAD_SWITCH_1:
            gSPDisplayList(gMasterDisp++, aMaRailroadSwitch1DL);
            break;
        case OBJ_SCENERY_MA_RAILROAD_SWITCH_2:
            gSPDisplayList(gMasterDisp++, aMaRailroadSwitch2DL);
            break;
        case OBJ_SCENERY_MA_RAILROAD_SWITCH_3:
            gSPDisplayList(gMasterDisp++, aMaRailroadSwitch3DL);
            break;
        case OBJ_SCENERY_MA_RAILROAD_SWITCH_4:
            gSPDisplayList(gMasterDisp++, aMaRailroadSwitch4DL);
            break;
        case OBJ_SCENERY_MA_RAILROAD_SWITCH_5:
            gSPDisplayList(gMasterDisp++, aMaRailroadSwitch5DL);
            break;
        case OBJ_SCENERY_MA_RAILROAD_SWITCH_6:
            gSPDisplayList(gMasterDisp++, aMaRailroadSwitch6DL);
            break;
        case OBJ_SCENERY_MA_RAILROAD_SWITCH_7:
            gSPDisplayList(gMasterDisp++, aMaRailroadSwitch7DL);
            break;
        case OBJ_SCENERY_MA_RAILROAD_SWITCH_8:
            gSPDisplayList(gMasterDisp++, aMaRailroadSwitch8DL);
            break;
    }
    RCP_SetupDL(&gMasterDisp, SETUPDL_29);
}

void Macbeth_MaTrainStopBlock_Update(MaTrainStopBlock* this) {
    s16 i;

    switch (this->state) {
        case 0:
            if ((D_i5_801BE312 != 0) && (gActors[D_i5_801BE314].obj.pos.z - 900.0f < this->obj.pos.z)) {
                this->state = 1;
            }
            break;

        case 1:
            Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_EXPLOSION_M);

            gControllerRumbleFlags[gMainController] = 1;
            gControllerRumbleTimers[gMainController] = 15;

            for (i = 0; i < 6; i++) {
                func_effect_8007D2C8(this->obj.pos.x + D_i5_801BE6A0[i].x, this->obj.pos.y + D_i5_801BE6A0[i].y,
                                     this->obj.pos.z + D_i5_801BE6A0[i].z, 18.0f);
                Macbeth_Effect357_Spawn1(
                    this->obj.pos.x + D_i5_801BE6A0[i].x, this->obj.pos.y + D_i5_801BE6A0[i].y,
                    this->obj.pos.z + D_i5_801BE6A0[i].z, RAND_FLOAT_CENTERED(30.0f), RAND_FLOAT(30.0f) + 30.0f,
                    RAND_FLOAT(-50.0f), this->obj.rot.x + D_i5_801BE6A0[i + 6].x,
                    this->obj.rot.y + D_i5_801BE6A0[i + 6].y, this->obj.rot.z + D_i5_801BE6A0[i + 6].z,
                    RAND_FLOAT_CENTERED(5.0f), RAND_FLOAT_CENTERED(5.0f), RAND_FLOAT_CENTERED(5.0f),
                    (s32) (RAND_FLOAT(50.0f) + 70.0f), i + 12, 1.0f);
            }
            Object_Kill(&this->obj, this->sfxSource);
            break;
    }
}

void Macbeth_MaTrainStopBlock_PostLimbDraw(s32 limbIndex, Vec3f* rot, void* thisx) {
    Vec3f src = { 0.0f, 0.0f, 0.0f };

    switch (limbIndex) {
        case 1:
            Matrix_MultVec3f(gCalcMatrix, &src, &D_i5_801BE6A0[0]);
            Matrix_GetYRPAngles(gCalcMatrix, &D_i5_801BE6A0[6]);
            break;
        case 2:
            Matrix_MultVec3f(gCalcMatrix, &src, &D_i5_801BE6A0[1]);
            Matrix_GetYRPAngles(gCalcMatrix, &D_i5_801BE6A0[7]);
            break;
        case 3:
            Matrix_MultVec3f(gCalcMatrix, &src, &D_i5_801BE6A0[2]);
            Matrix_GetYRPAngles(gCalcMatrix, &D_i5_801BE6A0[8]);
            break;
        case 4:
            Matrix_MultVec3f(gCalcMatrix, &src, &D_i5_801BE6A0[3]);
            Matrix_GetYRPAngles(gCalcMatrix, &D_i5_801BE6A0[9]);
            break;
        case 5:
            Matrix_MultVec3f(gCalcMatrix, &src, &D_i5_801BE6A0[4]);
            Matrix_GetYRPAngles(gCalcMatrix, &D_i5_801BE6A0[10]);
            break;
        case 11:
            Matrix_MultVec3f(gCalcMatrix, &src, &D_i5_801BE6A0[5]);
            Matrix_GetYRPAngles(gCalcMatrix, &D_i5_801BE6A0[11]);
            break;

        default:
            break;
    }
}

void Macbeth_MaTrainStopBlock_Draw(MaTrainStopBlock* this) {
    Vec3f frameTable[50];

    RCP_SetupDL(&gMasterDisp, SETUPDL_29);
    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
    Animation_GetFrameData(&D_MA_600C4D0, 0, frameTable);
    Animation_DrawSkeleton(1, D_MA_600C65C, frameTable, NULL, Macbeth_MaTrainStopBlock_PostLimbDraw, this,
                           &gIdentityMatrix);
    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
}

bool Macbeth_801A3300(Player* player, f32 arg1, f32 arg2) {
    s16 var_v1 = D_MA_801BE250[6];
    s16 temp_a0;
    f32 temp_ft4;
    f32 temp_fa0;
    f32 sp40;
    f32 temp_fv0_2;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    s32 pad;

    while (true) {
        if (D_i5_801B8E50[var_v1].unk_10 == 0) {
            return true;
        }

        if (D_i5_801B8E50[var_v1].unk_00 < arg1) {
            if (var_v1 == 0) {
                return true;
            }

            temp_ft4 = D_i5_801B8E50[var_v1 - 1].unk_00;
            temp_fa0 = D_i5_801B8E50[var_v1 - 1].unk_04;
            sp40 = D_i5_801B8E50[var_v1 - 1].unk_08;
            temp_a0 = D_i5_801B8E50[var_v1 - 1].unk_10;
            sp30 = D_i5_801B8E50[var_v1].unk_00;
            sp38 = D_i5_801B8E50[var_v1].unk_04;
            sp34 = D_i5_801B8E50[var_v1].unk_08;

            if (var_v1 != D_MA_801BE250[6]) {
                D_MA_801BE250[7] = arg2;
                switch (D_i5_801B8E50[var_v1 - 1].unk_10) {
                    case OBJ_SCENERY_MA_TRAIN_TRACK_3:
                    case OBJ_SCENERY_MA_TRAIN_TRACK_9:
                    case OBJ_SCENERY_MA_TRAIN_TRACK_10:
                        D_MA_801BE250[8] = 0.0f;
                        break;
                    case OBJ_SCENERY_MA_TRAIN_TRACK_4:
                        D_MA_801BE250[8] = -10.0f;
                        break;
                    case OBJ_SCENERY_MA_TRAIN_TRACK_5:
                        D_MA_801BE250[8] = 10.0f;
                        break;
                }
                D_MA_801BE250[6] = var_v1;
            }
            break;
        } else {
            var_v1++;
        }
    }

    sp2C = 1.0f - ((sp30 - arg1) / (sp30 - temp_ft4));

    if ((temp_a0 == OBJ_SCENERY_MA_TRAIN_TRACK_4) || (temp_a0 == OBJ_SCENERY_MA_TRAIN_TRACK_5) ||
        (temp_a0 == OBJ_SCENERY_MA_TRAIN_TRACK_7) || (temp_a0 == OBJ_SCENERY_MA_TRAIN_TRACK_8)) {
        temp_fv0_2 = fabsf((sp30 - temp_ft4) / 3.0f);
        if (sp2C < 0.3333333f) {
            if ((temp_a0 == OBJ_SCENERY_MA_TRAIN_TRACK_4) || (temp_a0 == OBJ_SCENERY_MA_TRAIN_TRACK_7)) {
                D_MA_801BE250[9] =
                    (((sp38 - temp_fa0) * sp2C) + temp_fa0) -
                    (52.160667f * (1.0f - (((temp_ft4 - temp_fv0_2) - arg1) / ((temp_ft4 - temp_fv0_2) - temp_ft4))));
            } else {
                D_MA_801BE250[9] =
                    ((sp38 - temp_fa0) * sp2C) + temp_fa0 +
                    (52.160667f * (1.0f - (((temp_ft4 - temp_fv0_2) - arg1) / ((temp_ft4 - temp_fv0_2) - temp_ft4))));
            }
        } else if (sp2C < 0.666666f) {
            if ((temp_a0 == OBJ_SCENERY_MA_TRAIN_TRACK_4) || (temp_a0 == OBJ_SCENERY_MA_TRAIN_TRACK_7)) {
                D_MA_801BE250[9] = (((sp38 - temp_fa0) * sp2C) + temp_fa0) - 52.160667f;
            } else {
                D_MA_801BE250[9] = (((sp38 - temp_fa0) * sp2C) + temp_fa0 + 52.160667f);
            }
        } else if ((temp_a0 == OBJ_SCENERY_MA_TRAIN_TRACK_4) || (temp_a0 == OBJ_SCENERY_MA_TRAIN_TRACK_7)) {
            D_MA_801BE250[9] =
                (((sp38 - temp_fa0) * sp2C) + temp_fa0) -
                (52.160667f * (1.0f - (1.0f - ((sp30 - arg1) / (sp30 - (temp_ft4 - (temp_fv0_2 * 2)))))));
        } else {
            D_MA_801BE250[9] =
                ((sp38 - temp_fa0) * sp2C) + temp_fa0 +
                (52.160667f * (1.0f - (1.0f - ((sp30 - arg1) / (sp30 - (temp_ft4 - (temp_fv0_2 * 2)))))));
        }
    } else {
        D_MA_801BE250[9] = ((sp38 - temp_fa0) * sp2C) + temp_fa0;
    }

    D_MA_801BE250[2] = (((sp34 - sp40) * sp2C) + sp40);

    if ((temp_a0 == 100) || (temp_a0 == OBJ_SCENERY_MA_TRAIN_TRACK_11)) {
        Math_SmoothStepToF(&D_MA_801BE250[3], 3.0f, 0.05f, 1.0f, 0.0f);
    } else if ((temp_a0 == OBJ_SCENERY_MA_TRAIN_TRACK_10) || (temp_a0 == OBJ_SCENERY_MA_TRAIN_TRACK_12)) {
        Math_SmoothStepToF(&D_MA_801BE250[3], -3.0f, 0.05f, 1.0f, 0.0f);
    } else {
        Math_SmoothStepToF(&D_MA_801BE250[3], 0.0f, 0.05f, 1.0f, 0.0f);
    }

    D_MA_801BE250[4] = (D_MA_801BE250[8] * sp2C) + D_MA_801BE250[7];

    return false;
}

bool Macbeth_801A3790(Player* player, f32 arg1, f32 arg2) {
    s16 var_v1 = D_MA_801BE250[16];
    s16 temp_a0;
    f32 temp_ft4;
    f32 temp_fa0;
    f32 sp40;
    f32 temp_fv0_2;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    s32 pad;

    while (true) {
        if (D_i5_801B9A80[var_v1].unk_10 == 0) {
            return true;
        }

        if (D_i5_801B9A80[var_v1].unk_00 < arg1) {
            if (var_v1 == 0) {
                return true;
            }

            temp_ft4 = D_i5_801B9A80[var_v1 - 1].unk_00;
            temp_fa0 = D_i5_801B9A80[var_v1 - 1].unk_04;
            sp40 = D_i5_801B9A80[var_v1 - 1].unk_08;
            temp_a0 = D_i5_801B9A80[var_v1 - 1].unk_10;
            sp30 = D_i5_801B9A80[var_v1].unk_00;
            sp38 = D_i5_801B9A80[var_v1].unk_04;
            sp34 = D_i5_801B9A80[var_v1].unk_08;

            if (var_v1 != D_MA_801BE250[16]) {
                D_MA_801BE250[17] = arg2;
                switch (D_i5_801B9A80[var_v1 - 1].unk_10) {
                    case OBJ_SCENERY_MA_TRAIN_TRACK_6:
                    case OBJ_SCENERY_MA_TRAIN_TRACK_9:
                    case OBJ_SCENERY_MA_TRAIN_TRACK_10:
                        D_MA_801BE250[18] = 0.0f;
                        break;
                    case OBJ_SCENERY_MA_TRAIN_TRACK_7:
                        D_MA_801BE250[18] = -10.0f;
                        break;
                    case OBJ_SCENERY_MA_TRAIN_TRACK_8:
                        D_MA_801BE250[18] = 10.0f;
                        break;
                }
                D_MA_801BE250[16] = var_v1;
            }
            break;
        } else {
            var_v1++;
        }
    }

    sp2C = 1.0f - ((sp30 - arg1) / (sp30 - temp_ft4));

    if ((temp_a0 == OBJ_SCENERY_MA_TRAIN_TRACK_4) || (temp_a0 == OBJ_SCENERY_MA_TRAIN_TRACK_5) ||
        (temp_a0 == OBJ_SCENERY_MA_TRAIN_TRACK_7) || (temp_a0 == OBJ_SCENERY_MA_TRAIN_TRACK_8)) {
        temp_fv0_2 = fabsf((sp30 - temp_ft4) / 3.0f);
        if (sp2C < 0.3333333f) {
            if ((temp_a0 == OBJ_SCENERY_MA_TRAIN_TRACK_4) || (temp_a0 == OBJ_SCENERY_MA_TRAIN_TRACK_7)) {
                D_MA_801BE250[19] =
                    (((sp38 - temp_fa0) * sp2C) + temp_fa0) -
                    (52.160667f * (1.0f - (((temp_ft4 - temp_fv0_2) - arg1) / ((temp_ft4 - temp_fv0_2) - temp_ft4))));
            } else {
                D_MA_801BE250[19] =
                    ((sp38 - temp_fa0) * sp2C) + temp_fa0 +
                    (52.160667f * (1.0f - (((temp_ft4 - temp_fv0_2) - arg1) / ((temp_ft4 - temp_fv0_2) - temp_ft4))));
            }
        } else if (sp2C < 0.666666f) {
            if ((temp_a0 == OBJ_SCENERY_MA_TRAIN_TRACK_4) || (temp_a0 == OBJ_SCENERY_MA_TRAIN_TRACK_7)) {
                D_MA_801BE250[19] = (((sp38 - temp_fa0) * sp2C) + temp_fa0) - 52.160667f;
            } else {
                D_MA_801BE250[19] = (((sp38 - temp_fa0) * sp2C) + temp_fa0 + 52.160667f);
            }
        } else if ((temp_a0 == OBJ_SCENERY_MA_TRAIN_TRACK_4) || (temp_a0 == OBJ_SCENERY_MA_TRAIN_TRACK_7)) {
            D_MA_801BE250[19] =
                (((sp38 - temp_fa0) * sp2C) + temp_fa0) -
                (52.160667f * (1.0f - (1.0f - ((sp30 - arg1) / (sp30 - (temp_ft4 - (temp_fv0_2 * 2)))))));
        } else {
            D_MA_801BE250[19] =
                ((sp38 - temp_fa0) * sp2C) + temp_fa0 +
                (52.160667f * (1.0f - (1.0f - ((sp30 - arg1) / (sp30 - (temp_ft4 - (temp_fv0_2 * 2)))))));
        }
    } else {
        D_MA_801BE250[19] = ((sp38 - temp_fa0) * sp2C) + temp_fa0;
    }

    D_MA_801BE250[12] = (((sp34 - sp40) * sp2C) + sp40);

    if ((temp_a0 == OBJ_SCENERY_MA_TRAIN_TRACK_9) || (temp_a0 == OBJ_SCENERY_MA_TRAIN_TRACK_11)) {
        Math_SmoothStepToF(&D_MA_801BE250[13], 2.0f, 0.05f, 1.0f, 0.0f);
    } else if ((temp_a0 == OBJ_SCENERY_MA_TRAIN_TRACK_10) || (temp_a0 == OBJ_SCENERY_MA_TRAIN_TRACK_12)) {
        Math_SmoothStepToF(&D_MA_801BE250[13], -2.0f, 0.05f, 1.0f, 0.0f);
    } else {
        Math_SmoothStepToF(&D_MA_801BE250[13], 0.0f, 0.05f, 1.0f, 0.0f);
    }

    D_MA_801BE250[14] = (D_MA_801BE250[18] * sp2C) + D_MA_801BE250[17];

    return false;
}

bool Macbeth_801A3C20(f32 arg0) {
    s16 var_a0;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 temp_fv0_2;

    for (var_a0 = D_MA_801BE250[20]; D_i5_801BA138[var_a0].unk_10 != 0; var_a0++) {
        if ((arg0 < D_i5_801BA138[var_a0].unk_00) && ((D_i5_801BA138[var_a0].unk_00 - 1200) < arg0)) {
            D_MA_801BE250[20] = var_a0;
            D_MA_801BE250[22] = D_i5_801BA138[var_a0].unk_08;
            sp38 = D_i5_801BA138[var_a0].unk_00;
            sp40 = D_i5_801BA138[var_a0].unk_04;
            sp3C = D_i5_801BA138[var_a0].unk_08;
            sp2C = sp38 - (COS_DEG(D_i5_801BA138[var_a0].unk_0C) * 1200.0f);
            sp34 = SIN_DEG(D_i5_801BA138[var_a0].unk_0C) * 1200.0f + sp40;
            sp30 = D_i5_801BA138[var_a0].unk_08;
            break;
        }
    }

    if (D_i5_801BA138[var_a0].unk_10 == 0) {
        return false;
    }

    temp_fv0_2 = 1.0f - ((sp2C - arg0) / (sp2C - sp38));

    D_MA_801BE250[21] = (((sp34 - sp40) * temp_fv0_2) + sp40);
    D_MA_801BE250[22] = (((sp30 - sp3C) * temp_fv0_2) + sp3C);

    if (sp30 < sp3C) {
        Math_SmoothStepToF(&D_MA_801BE250[23], -10.0f, 0.05f, 1.0f, 0);
    } else if (sp3C < sp30) {
        Math_SmoothStepToF(&D_MA_801BE250[23], 10.0f, 0.05f, 1.0f, 0);
    } else {
        Math_SmoothStepToF(&D_MA_801BE250[23], 0.0f, 0.05f, 1.0f, 0);
    }
    return true;
}

void Macbeth_MaMaRailroadSwitch_Init(MaRailroadSwitch* this) {
    this->state = 0;
    this->work_046 = D_i5_801BA1D8;
    D_i5_801BA1D8++;
}

void Macbeth_MaRailroadSwitch_Update(MaRailroadSwitch* this) {
    if ((gPlayer[0].trueZpos - this->obj.pos.z) < -500.0f) {
        Object_Kill(&this->obj, this->sfxSource);
    }

    switch (this->state) {
        case 0:
            if ((this->dmgType != DMG_NONE) && (this->dmgType != DMG_COLLISION)) {
                this->dmgType = DMG_NONE;
                AUDIO_PLAY_SFX(NA_SE_OB_MA_SWITCH_ON, this->sfxSource, 0);
                this->state = 1;
            }
            break;

        case 1:
            Math_SmoothStepToF(&this->fwork[1], -181.0f, 0.6f, 20.0f, 0.0f);
            if (this->fwork[1] <= -180.0f) {
                AUDIO_PLAY_SFX(NA_SE_OB_MA_SWITCH_UP, this->sfxSource, 0);
                this->info.hitbox = SEGMENTED_TO_VIRTUAL(D_MA_603648C);
                this->iwork[0] = 2;
                this->state = 2;
            }
            break;

        case 2:
            if (this->iwork[0] <= 0) {
                Math_SmoothStepToF(&this->fwork[2], 41.0f, 0.6f, 8.0f, 0.0f);
                if (this->fwork[2] >= 40.0f) {
                    this->state = 3;
                    D_i5_801BE308[this->work_046] = 1;
                }
            } else {
                this->iwork[0]--;
            }
            break;

        case 3:
            break;
    }

    if (this->dmgType != DMG_NONE) {
        AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
        this->dmgType = DMG_NONE;
    }

    Math_SmoothStepToF(&this->fwork[0], 30.0f, 0.4f, 10.0f, 0.0f);
    Math_SmoothStepToF(&this->fwork[4], 30.0f, 0.4f, 10.0f, 0.0f);

    if (this->fwork[0] < 31.0f) {
        if (this->state >= 3) {
            AUDIO_PLAY_SFX(NA_SE_OB_MA_SWITCH_GRN, this->sfxSource, 0);
        } else {
            AUDIO_PLAY_SFX(NA_SE_OB_MA_SWITCH_RED, this->sfxSource, 0);
        }
        this->fwork[0] = 255.0f;
        this->fwork[4] = 170.0f;
    }
}

bool Macbeth_MaRailroadSwitch_OverrideLimbDraw(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    MaRailroadSwitch* actor = (MaRailroadSwitch*) thisx;

    RCP_SetupDL(&gMasterDisp, SETUPDL_29);
    gDPSetTextureFilter(gMasterDisp++, G_TF_BILERP);

    if (limbIndex == 2) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_34);
        gDPSetTextureFilter(gMasterDisp++, G_TF_POINT);
        if (actor->state >= 2) {
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 0, actor->fwork[0], actor->fwork[4], 255);
        }
    }
    if ((limbIndex == 1) || (limbIndex == 3)) {
        *dList = NULL;
    }
    return false;
}

void Macbeth_MaRailroadSwitch_Draw(MaRailroadSwitch* this) {
    Vec3f frameTable[50];

    Matrix_Push(&gGfxMatrix);
    Animation_GetFrameData(&D_MA_602FEB4, 0, frameTable);
    Animation_DrawSkeleton(1, D_MA_602FFA0, frameTable, Macbeth_MaRailroadSwitch_OverrideLimbDraw, NULL, this,
                           &gIdentityMatrix);
    Matrix_Pop(&gGfxMatrix);
    RCP_SetupDL(&gMasterDisp, SETUPDL_29);
    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, 0.0f, this->fwork[2] + 204.0f, 0.0f, MTXF_APPLY);
    Matrix_RotateY(gGfxMatrix, this->fwork[1] * M_DTOR, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_MA_602FFC0);
    Matrix_Pop(&gGfxMatrix);
    RCP_SetupDL(&gMasterDisp, SETUPDL_34);
    gDPSetTextureFilter(gMasterDisp++, G_TF_POINT);
    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, this->fwork[0], 0, 0, 255);
    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, 0.0f, this->fwork[2] + 204.0f, 0.0f, MTXF_APPLY);
    Matrix_RotateY(gGfxMatrix, this->fwork[1] * M_DTOR, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_MA_602F380);
    gDPSetTextureFilter(gMasterDisp++, G_TF_BILERP);
    Matrix_Pop(&gGfxMatrix);
}

void Macbeth_MaBoulder_Init(MaBoulder* this) {
    this->gravity = 0;
    this->work_04A = this->work_046;
    this->health = 60;
    if (this->fwork[0] < 0.0f) {
        this->work_048 = 0;
    } else {
        this->work_048 = 1;
    }
}

void Macbeth_MaBoulder_Update(MaBoulder* this) {
    if ((gPlayer[0].trueZpos - this->obj.pos.z) < -500.0f) {
        Object_Kill(&this->obj, this->sfxSource);
    }

    switch (this->state) {
        case 0:
            if (this->timer_0BC == 0) {
                Math_SmoothStepToF(&this->vel.x, this->fwork[0], 0.5f, 3.0f, 0.0f);
                Math_SmoothStepToF(&this->gravity, 5.0f, 0.08f, 1.0f, 0.0f);

                if (this->obj.pos.y < 80.0f) {
                    if (this->work_046 != 0) {
                        AUDIO_PLAY_SFX(NA_SE_OB_ROCK_BOUND, this->sfxSource, 0);
                        this->obj.pos.y = 80.0f;
                        if (this->vel.y < 0) {
                            this->vel.y = -this->vel.y * (this->work_046 * 0.07f);
                        }

                        this->fwork[0] /= 1.2f + RAND_FLOAT(1.0f) / 2.0f;
                        this->work_046--;
                        this->vel.z /= 1.5f;
                        if (this->work_046 == 0) {
                            this->timer_0BE = RAND_INT(30.0f);
                        }
                    } else {
                        if (this->timer_0BE <= 0) {
                            this->fwork[0] = 0.0f;
                            this->vel.x = 0.0f;
                        }
                        this->vel.y = 0.0f;
                        this->vel.z = 0.0f;
                    }
                }

                if (this->work_048 != 0) {
                    this->obj.rot.z -= 0.5f * this->vel.x;
                } else {
                    this->obj.rot.z -= 0.5f * this->vel.x;
                }

                if (this->work_046 != this->work_04A) {
                    this->obj.rot.x = this->obj.rot.x + (0.1f * this->vel.z);
                }
            }

            if (this->work_046 == 7) {
                if (this->work_048 != 0) {
                    this->obj.rot.z -= 1.0f;
                } else {
                    this->obj.rot.z += 1.0f;
                }
            }

            Macbeth_MaBoulder_HandleDamage(this);
            break;

        case 1:
            Macbeth_MaBoulder_HandleDamage(this);
            break;

        case 2:
            func_effect_8007D2C8(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 10.0f);
            Object_Kill(&this->obj, this->sfxSource);
            break;
    }
}

void Macbeth_MaBoulder_HandleDamage(MaBoulder* this) {
    if (this->dmgType != DMG_NONE) {
        AUDIO_PLAY_SFX(NA_SE_EN_DAMAGE_M, this->sfxSource, 0);
        this->timer_0C6 = 15;
        this->health -= this->damage;
        if (this->health <= 0) {
            Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_EXPLOSION_M);
            gHitCount++;
            this->state = 2;
        }
        this->dmgType = DMG_NONE;
    }
}

void Macbeth_MaBoulder_Draw(MaBoulder* this) {
    if (this->state < 2) {
        if (this->scale != 1.0f) {
            Matrix_Scale(gGfxMatrix, this->scale, this->scale, this->scale, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
        }
        gSPDisplayList(gMasterDisp++, aMaBoulderDL);
    }
}

void Macbeth_MaRailwaySignal_Init(MaRailwaySignal* this) {
    this->fwork[1] = 10.0f;
    this->fwork[6] = -100.0f;
    D_i5_801BE318 = this->index;
}

void Macbeth_MaRailwaySignal_Update(MaRailwaySignal* this) {
    s32 pad[2];
    s32 i;
    ObjectInit* objInit;
    u8 var_s0 = 0;
    u8 j;

    if ((gPlayer[0].trueZpos - this->obj.pos.z) < -700.0f) {
        if (D_MA_801BE2F0[5] == 0) {
            Radio_PlayMessage(gMsg_ID_17170, RCID_PEPPY);
        }
        Object_Kill(&this->obj, this->sfxSource);
    }

    switch (this->state) {
        case 0:
            for (j = 0; j < 8; j++) {
                if (D_i5_801BE308[j] != 0) {
                    var_s0++;
                }
            }
            if (var_s0 >= 8) {
                Radio_PlayMessage(gMsg_ID_17150, RCID_PEPPY);
                this->state = 1;
            }
            break;

        case 1:
            if ((gPlayer[0].trueZpos - this->obj.pos.z) < 2000.0f) {
                this->info.hitbox = SEGMENTED_TO_VIRTUAL(D_MA_6036520);
                this->state = 2;
            }
            break;

        case 2:
            Math_SmoothStepToF(&this->fwork[2], -76.0f, 0.2f, 10.0f, 0.01f);
            Math_SmoothStepToF(&this->fwork[3], 76.0f, 0.2f, 10.0f, 0.01f);
            Math_SmoothStepToF(&this->fwork[6], 0.0f, 0.2f, 4.0f, 0.00001f);
            if (this->fwork[3] >= 75.0f) {
                this->state = 3;
            }
            break;

        case 3:
            Math_SmoothStepToF(&this->fwork[5], -75.0f, 0.2f, 10.0f, 0.00001f);
            Math_SmoothStepToF(&this->fwork[6], 1.0f, 0.2f, 4.0f, 0.01f);
            if (this->fwork[6] >= 0.0f) {
                this->state = 4;
            }
            break;

        case 4:
            Math_SmoothStepToF(&this->fwork[7], 31.0f, 0.2f, 2.0f, 0.01f);
            if (this->fwork[7] >= 30.0f) {
                this->state = 5;
            }
            break;

        case 5:
            if ((this->dmgType != DMG_NONE) && (this->dmgPart == 3)) {
                this->dmgType = DMG_NONE;
                D_MA_801BE2F0[5] = 1;

                gLevelObjects = SEGMENTED_TO_VIRTUAL(gLevelObjectInits[gCurrentLevel]);

                for (i = gObjectLoadIndex - 5, objInit = &gLevelObjects[i]; i < gObjectLoadIndex + 50; i++, objInit++) {
                    Object_Load(objInit, 40000.0f, -2000.0f, 40000.0f, -2000.0f);
                }
                gObjectLoadIndex = i;
                gTeamLowHealthMsgTimer = -1;
                gPlayer[0].state = PLAYERSTATE_LEVEL_COMPLETE;
                gPlayer[0].csState = 0;
                gMissionStatus = MISSION_ACCOMPLISHED;
                this->timer_0BC = 5;
                this->state = 6;
                Audio_KillSfxBySourceAndId(gPlayer[0].sfxSource, NA_SE_TANK_SLIDE);
                Audio_KillSfxBySourceAndId(gPlayer[0].sfxSource, NA_SE_TANK_BURNER_HALF);
            }
            break;

        case 6:
            if (this->timer_0BC == 1) {
                AUDIO_PLAY_SFX(NA_SE_OB_HEAVY_SWITCH, this->sfxSource, 0);
            }
            if (this->timer_0BC == 0) {
                Math_SmoothStepToF(&this->fwork[7], -41.0f, 0.2f, 5.0f, 0.01f);
                if (this->fwork[7] <= -40.0f) {
                    this->fwork[1] = 150.0f;
                    Radio_PlayMessage(gMsg_ID_17160, RCID_PEPPY);
                    this->timer_0BC = 30;
                    this->state = 7;
                }
            }
            break;

        case 7:
            break;

        default:
            break;
    }

    if (this->dmgType != DMG_NONE) {
        this->dmgType = DMG_NONE;
        AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
    }

    Math_SmoothStepToF(&this->fwork[0], 30, 0.4f, this->fwork[1], 0.0f);
    Math_SmoothStepToF(&this->fwork[4], 30, 0.4f, this->fwork[1], 0.0f);

    if (this->fwork[0] < 31.0f) {
        this->fwork[0] = 255.0f;
        this->fwork[4] = 170.0f;
    }
}

bool Macbeth_MaRailwaySignal_OverrideLimbDraw2(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    MaRailwaySignal* this = (MaRailwaySignal*) thisx;

    RCP_SetupDL(&gMasterDisp, SETUPDL_29);
    gDPSetTextureFilter(gMasterDisp++, G_TF_BILERP);

    if ((limbIndex == 9) || (limbIndex == 10)) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_57);
    }
    if ((limbIndex > 0) && (limbIndex < 9)) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_34);
        gDPSetTextureFilter(gMasterDisp++, G_TF_POINT);
        if (D_i5_801BE308[limbIndex - 1] != 0) {
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 0, this->fwork[0], this->fwork[4], 255);
        } else {
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, this->fwork[0], 0, 0, 255);
        }
    }
    if ((limbIndex == 1) || (limbIndex == 3) || (limbIndex == 5) || (limbIndex == 7) || (limbIndex == 9)) {
        pos->x = this->fwork[2] + pos->x;
        pos->y = this->fwork[5] + pos->y;
    }
    if ((limbIndex == 2) || (limbIndex == 4) || (limbIndex == 6) || (limbIndex == 8) || (limbIndex == 10)) {
        pos->x = this->fwork[3] + pos->x;
        pos->y = this->fwork[5] + pos->y;
    }
    return false;
}

bool Macbeth_MaRailwaySignal_OverrideLimbDraw1(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    MaRailwaySignal* this = (MaRailwaySignal*) thisx;

    pos->y = this->fwork[6] + pos->y;
    if (limbIndex == 1) {
        rot->x = this->fwork[7] + rot->x;
    }
    return false;
}

void Macbeth_MaRailwaySignal_Draw(MaRailwaySignal* this) {
    Vec3f frameTable[50];

    Matrix_Push(&gGfxMatrix);
    // Lever
    Animation_GetFrameData(&D_MA_602F2E0, 0, frameTable);
    Animation_DrawSkeleton(1, D_MA_602F36C, frameTable, Macbeth_MaRailwaySignal_OverrideLimbDraw1, NULL, this,
                           &gIdentityMatrix);
    Matrix_Pop(&gGfxMatrix);
    Matrix_Push(&gGfxMatrix);
    Animation_GetFrameData(&D_MA_602F098, 0, frameTable);
    // Base
    Animation_DrawSkeleton(1, D_MA_602F264, frameTable, Macbeth_MaRailwaySignal_OverrideLimbDraw2, NULL, this,
                           &gIdentityMatrix);
    Matrix_Pop(&gGfxMatrix);
    RCP_SetupDL(&gMasterDisp, SETUPDL_29);
}

s32 Macbeth_801A55D4(s32 arg0, Vec3f* arg1, Vec3f* arg2, s32 arg3) {
    Scenery* scenery;
    Actor* actor;
    s32 i;

    for (scenery = &gScenery[0], i = 0; i < ARRAY_COUNT(gScenery); i++, scenery++) {
        if ((scenery->obj.status == OBJ_ACTIVE) && (scenery->obj.id != OBJ_SCENERY_MA_WALL_4) &&
            (fabsf(arg1->x - scenery->obj.pos.x) < 2000.0f) && (fabsf(arg1->z - scenery->obj.pos.z) < 2000.0f) &&
            (Object_CheckHitboxCollision(arg1, scenery->info.hitbox, &scenery->obj, 0.0f, 0.0f, 0.0f) != 0)) {
            return i + 10;
        }
    }

    for (actor = &gActors[0], i = 0; i < ARRAY_COUNT(gActors); i++, actor++) {
        if ((actor->obj.status >= OBJ_ACTIVE) && (fabsf(arg1->x - actor->obj.pos.x) < 1000.0f) &&
            (fabsf(arg1->z - actor->obj.pos.z) < 1500.0f) && (arg0 != i) && (actor->info.unk_16 != 2) &&
            (actor->timer_0C2 == 0) && (Object_CheckSingleHitbox(arg1, actor->info.hitbox, &actor->obj.pos) != 0)) {
            actor->dmgType = DMG_BEAM;
            actor->dmgPart = -1;
            actor->hitPos.x = arg1->x;
            actor->hitPos.y = arg1->y;
            actor->hitPos.z = arg1->z;
            return 1;
        }
    }
    return 0;
}

void Macbeth_Effect378_Update(Effect378* this) {
    u8 i;
    Vec3f sp50;
    Vec3f sp44;
    Vec3f sp38;

    if ((gPlayer[0].trueZpos - this->obj.pos.z) < -2000.0f) {
        Object_Kill(&this->obj, this->sfxSource);
    }

    this->obj.rot.x = 0.0f;
    this->obj.rot.y = 0.0f;
    this->obj.rot.z = 0.0f;

    if (this->timer_50 == 96) {
        for (i = 0; i < 2; i++) {
            Effect_Effect362_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 6.0f);
        }
    }

    if ((fabsf(gPlayer[0].trueZpos - this->obj.pos.z) < 50.0f) && (fabsf(gPlayer[0].pos.x - this->obj.pos.x) < 30.0f) &&
        (fabsf(gPlayer[0].pos.y - this->obj.pos.y) < 30.0f)) {
        if ((gPlayer[0].barrelRollAlpha != 0) || (gPlayer[0].meteoWarpTimer != 0)) {
            sp50.x = 0.0f;
            sp50.y = 0.0f;
            sp50.z = 100.0f;
            Matrix_MultVec3f(gCalcMatrix, &sp50, &sp44);
            this->vel.x = sp44.x;
            this->vel.y = sp44.y;
            this->vel.z = sp44.z;
            AUDIO_PLAY_SFX(NA_SE_ROLLING_REFLECT, this->sfxSource, 4);
        }
        if ((gPlayer[0].barrelRollAlpha == 0) && (gPlayer[0].mercyTimer == 0)) {
            Player_ApplyDamage(&gPlayer[0], 0, this->info.damage);
            gPlayer[0].knockback.x = 20.0f;
            if (this->vel.x < 0.0f) {
                gPlayer[0].knockback.x *= -1.0f;
            }
            Object_Kill(&this->obj, this->sfxSource);
        }
    }

    if (this->obj.pos.y < gGroundHeight) {
        Macbeth_MaBombDrop_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 999.9f, -10.0f, 5.0f);
        Object_Kill(&this->obj, this->sfxSource);
        if (gGroundSurface != SURFACE_WATER) {
            this->obj.pos.y = gGroundHeight;
        }
    }

    sp38.x = this->vel.x;
    sp38.y = this->vel.y;
    sp38.z = this->vel.z;

    if (Macbeth_801A55D4(1000, &this->obj.pos, &sp38, 0) != 0) {
        Macbeth_MaBombDrop_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 999.9f, -10.0f, 5.0f);
        Object_Kill(&this->obj, this->sfxSource);
    }
}

void Macbeth_Effect378_Draw(Effect378* this) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_60);
    gSPDisplayList(gMasterDisp++, D_MA_601A840);
    RCP_SetupDL(&gMasterDisp, SETUPDL_64);
}

void Macbeth_Effect380_Update(Effect380* this) {
    if ((gPlayer[0].trueZpos - this->obj.pos.z) < -2000.0f) {
        Object_Kill(&this->obj, this->sfxSource);
    }

    this->obj.rot.x = 20.0f;
    if (this->scale2 < 10.0f) {
        this->obj.rot.y = 180.0f;
    } else {
        this->obj.rot.y = 0.0f;
    }
    this->obj.rot.z = 0.0f;

    if ((fabsf(gPlayer[0].trueZpos - this->obj.pos.z) < 100.0f) &&
        (fabsf(gPlayer[0].pos.x - this->obj.pos.x) < 100.0f) && (fabsf(gPlayer[0].pos.y - this->obj.pos.y) < 30.0f) &&
        (gPlayer[0].mercyTimer == 0)) {
        Player_ApplyDamage(gPlayer, 0, this->info.damage);
        gPlayer[0].knockback.x = 20.0f;
        if (this->vel.x < 0.0f) {
            gPlayer[0].knockback.x *= -1.0f;
        }
        gPlayer[0].knockback.y = 20.0f;
        if (this->vel.y < 0.0f) {
            gPlayer[0].knockback.y *= -1.0f;
        }
        Object_Kill(&this->obj, this->sfxSource);
    }

    if (this->obj.pos.y < (gGroundHeight - 100.0f)) {
        Object_Kill(&this->obj, this->sfxSource);
    }

    if (this->unk_44 < 235) {
        this->unk_44 += 20;
    }
}

void Macbeth_Effect380_Draw(Effect380* this) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_67);
    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 112, 255, 243, this->unk_44);
    gDPSetEnvColor(gMasterDisp++, 255, 255, 255, this->unk_44);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_MA_6012A60);
    RCP_SetupDL(&gMasterDisp, SETUPDL_64);
}

void Macbeth_LockBars_Init(Actor* this) {
    this->fwork[0] = this->obj.pos.x;
    this->fwork[1] = this->obj.pos.y;
    this->fwork[2] = this->obj.rot.z;
    this->obj.rot.z = 0.0f;
}

void Macbeth_MaHorizontalLockBar_Update(MaHorizontalLockBar* this) {
    if ((gPlayer[0].trueZpos - this->obj.pos.z) < -500.0f) {
        Object_Kill(&this->obj, this->sfxSource);
    }

    if ((D_i5_801BA1E0 - this->obj.pos.z) < -800.0f) {
        if (this->iwork[0] == 0) {
            AUDIO_PLAY_SFX(NA_SE_OB_SIDE_GATE_CLOSE, this->sfxSource, 0);
            this->iwork[0]++;
        }
        Math_SmoothStepToF(&this->obj.pos.x, this->fwork[0] + (this->fwork[2] * 400.0f), 0.1f, 4.0f, 0.01f);
    }

    if (this->dmgType != DMG_NONE) {
        this->dmgType = DMG_NONE;
        AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
    }
}

void Macbeth_MaHorizontalLockBar_Draw(MaHorizontalLockBar* this) {
    gSPDisplayList(gMasterDisp++, aMaHorizontalLockBarDL);
}

void Macbeth_801A5FC4(s32 arg0) {
}

void Macbeth_MaVerticalLockBar_Update(MaVerticalLockBar* this) {
    if (gPlayer[0].trueZpos - this->obj.pos.z < -500.0f) {
        Object_Kill(&this->obj, this->sfxSource);
    }
    if (gPlayer[0].trueZpos - this->obj.pos.z < this->fwork[2]) {
        if (this->iwork[0] == 0) {
            AUDIO_PLAY_SFX(NA_SE_OB_POST_UP, this->sfxSource, 0);
            this->iwork[0]++;
        }
        Math_SmoothStepToF(&this->obj.pos.y, this->fwork[1] + 356.0f, 0.4f, 20.0f, 0.01f);
    }

    if (this->dmgType != DMG_NONE) {
        this->dmgType = DMG_NONE;
        AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
    }
}

void Macbeth_MaVerticalLockBar_Draw(MaVerticalLockBar* this) {
    gSPDisplayList(gMasterDisp++, aMaVerticalLockBarDL);
}

void Macbeth_MaBarrier_Init(MaBarrier* this) {
    this->health = 30;
}

void Macbeth_MaBarrier_Update(MaBarrier* this) {
    s16 i;

    if ((gPlayer[0].trueZpos - this->obj.pos.z) < -500.0f) {
        Object_Kill(&this->obj, this->sfxSource);
    }

    switch (this->state) {
        case 0:
            if (this->dmgType != DMG_NONE) {
                Effect_Effect390_Spawn(this->obj.pos.x, this->obj.pos.y + 100.0f, this->obj.pos.z, this->vel.x,
                                       this->vel.y, this->vel.z, 0.15f, 20);

                AUDIO_PLAY_SFX(NA_SE_EN_DAMAGE_S, this->sfxSource, 4);

                this->health -= this->damage;
                this->timer_0C6 = 15;

                if ((gPlayer[0].trueZpos - 20.0f) < this->obj.pos.z) {
                    this->health = 0;
                }

                if (this->health <= 0) {
                    AUDIO_PLAY_SFX(NA_SE_EN_EXPLOSION_M, this->sfxSource, 0);
                    Effect386_Spawn1(this->obj.pos.x, this->obj.pos.y + 100.0f, this->obj.pos.z, 0.0f, 0.0f, 0.0f,
                                     14.0f, 5);
                    for (i = 0; i < 20; i++) {
                        Macbeth_Effect357_Spawn1(
                            RAND_FLOAT_CENTERED(500.0f) + this->obj.pos.x, this->obj.pos.y + 100.0f,
                            RAND_FLOAT(150.0f) + this->obj.pos.z, RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT(7.0f) + 7.0f,
                            RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT(360.0f), RAND_FLOAT(360.0f), RAND_FLOAT(360.0f),
                            RAND_FLOAT_CENTERED(30.0f), RAND_FLOAT_CENTERED(30.0f), RAND_FLOAT_CENTERED(30.0f),
                            (s32) (RAND_FLOAT(50.0f) + 70.0f), 4, (RAND_FLOAT(0.8f) + 0.3f) * 1.5f);
                    }
                    this->timer_0BC = 20;
                    this->state = 1;
                }
                this->dmgType = DMG_NONE;
            }
            break;

        case 1:
            Math_SmoothStepToF(&this->obj.rot.x, -90.0f, 0.5f, 5.0f, 0.01f);
            if (this->timer_0BC == 0) {
                Object_Kill(&this->obj, this->sfxSource);
            }
            break;
    }
}

void Macbeth_MaBarrier_Draw(MaBarrier* this) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_57);
    if ((this->timer_0C6 % 2) != 0) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_58);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
    }
    gSPDisplayList(gMasterDisp++, aMaBarrierDL);
    RCP_SetupDL(&gMasterDisp, SETUPDL_29);
}

void Macbeth_MaProximityLight_Init(MaProximityLight* this) {
    this->vel.x = this->obj.pos.x;
    this->vel.y = this->obj.pos.y;
    this->vel.z = this->obj.rot.z;
    this->obj.rot.z = 0.0f;
}

void Macbeth_MaProximityLight_Draw(MaProximityLight* this) {
    if ((gPlayer[0].trueZpos - this->obj.pos.z) < this->vel.z) {
        if (gPlayState != PLAY_PAUSE) {
            Math_SmoothStepToF(&this->vel.x, 30, 0.5f, 30.0f, 0.0f);
            if (this->vel.x < 31.0f) {
                this->vel.x = 255.0f;
            }
        }
        RCP_SetupDL(&gMasterDisp, SETUPDL_34);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, this->vel.x, 0, 0, 255);
    }
    gSPDisplayList(gMasterDisp++, aMaProximityLightSidesDL);
    RCP_SetupDL(&gMasterDisp, SETUPDL_29);
    gSPDisplayList(gMasterDisp++, aMaProximityLightTopDL);
}

void Macbeth_801A67BC(s32 arg0) {
}

void Macbeth_MaFallingBoulder_Update(MaFallingBoulder* this) {
    if ((gPlayer[0].trueZpos - this->obj.pos.z) < -300.0f) {
        Object_Kill(&this->obj, this->sfxSource);
    }

    if ((this->dmgType != DMG_NONE) && (this->dmgPart == -1)) {
        this->dmgType = DMG_NONE;
        if (this->obj.pos.x <= gPlayer[0].pos.x) {
            this->iwork[4] = 1;
        } else {
            this->iwork[4] = -1;
        }

        Macbeth_MaBoulder_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z,
                                (RAND_FLOAT(2.0f) + 20.0f) * (s32) this->iwork[4], 0.0f, (s32) this->iwork[4] * -34.0f,
                                0.0f, 2, 3);
        Object_Kill(&this->obj, this->sfxSource);
    }
}

void Macbeth_MaFallingBoulder_Draw(MaFallingBoulder* this) {
    /* Unimplemented */
}

void Macbeth_801A68F8(Actor207* this, s16 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    gTexturedLines[arg1].mode = 3;
    gTexturedLines[arg1].posAA.x = arg2;
    gTexturedLines[arg1].posAA.y = arg3;
    gTexturedLines[arg1].xyScale = 5.0f;
    gTexturedLines[arg1].prim.r = gTexturedLines[arg1].prim.g = gTexturedLines[arg1].prim.b =
        gTexturedLines[arg1].prim.a = 255;
    gTexturedLines[arg1].timer = 3;
    gTexturedLines[arg1].posAA.z = arg4;
    gTexturedLines[arg1].posBB.x = arg5;
    gTexturedLines[arg1].posBB.y = arg6;
    gTexturedLines[arg1].posBB.z = arg7;
}

void Macbeth_801A6984(Actor207* this) {
    s16 var_s3 = 0;
    Vec3f test;
    f32 temp_fs3;
    s32 var_s4;
    f32 temp_fs2_2;
    f32 temp_fs3_2;
    f32 temp_fs4;
    f32 spA8;
    f32 var_fs5;
    f32 spA0;
    f32 sp9C;
    f32 temp;
    s32 pad1;
    s32 pad2;
    s32 i;
    f32 sp88;
    f32 sp84;
    f32 sp80;

    if ((gPlayer[0].trueZpos - this->obj.pos.z) > 7000.0f) {
        return;
    }

    test.x = this->obj.pos.x - D_i5_801BE368[4];
    test.y = this->obj.pos.y - D_i5_801BE368[5];
    test.z = this->obj.pos.z - D_i5_801BE368[6];

    temp_fs3 = VEC3F_MAG(&test);

    Math_Atan2F(test.x, test.z);
    Math_Atan2F(test.y, sqrtf(SQ(test.x) + SQ(test.z)));

    var_s4 = (s32) (temp_fs3 / 40.0f);
    if (var_s4 == 0) {
        var_s4 = 1;
    }

    spA8 = (180.0f / var_s4) + 1.0f;
    var_fs5 = this->obj.pos.x;
    spA0 = this->obj.pos.y;
    sp9C = this->obj.pos.z;

    sp88 = (D_i5_801BE368[4] - this->obj.pos.x) / var_s4;
    sp84 = (D_i5_801BE368[5] - this->obj.pos.y) / var_s4;
    sp80 = (D_i5_801BE368[6] - this->obj.pos.z) / var_s4;

    for (i = 0; i < var_s4; i++) {
        if (D_i5_801BE320[1] == 0) {
            Math_SmoothStepToF(&D_i5_801BE368[7], 0.0f, 0.01f, 0.05f, 0.01f);
        } else {
            Math_SmoothStepToF(&D_i5_801BE368[7], 100.0f, 0.01f, 0.01f, 0.01f);
        }
        temp = SIN_DEG(i * spA8) * (-(D_i5_801BE368[7] * 3.0f) * (1.0f - ((f32) i / var_s4)));
        temp_fs2_2 = this->obj.pos.x + (sp88 * i);
        temp_fs3_2 = this->obj.pos.y + (sp84 * i) + temp;
        temp_fs4 = this->obj.pos.z + (sp80 * i);
        Macbeth_801A68F8(this, var_s3++, var_fs5, spA0, sp9C, temp_fs2_2, temp_fs3_2, temp_fs4);
        var_fs5 = temp_fs2_2;
        spA0 = temp_fs3_2;
        sp9C = temp_fs4;
    }
    // LTODO: ASAN accuses Heap overflow
    Macbeth_Texture_Scroll2(D_MA_6012C98, 4, 8);
}

void Macbeth_801A6C78(Actor207* this) {
    // FAKE
    if (1) {}

    Macbeth_801A0308(this, this->obj.pos.z, this->obj.rot.y, 0);

    switch (D_i5_801BE320[0]) {
        case 0:
            Math_SmoothStepToF(&D_i5_801BE368[0], 30.0f, 0.1f, RAND_FLOAT(1.0f) + 1.0f, 0.01f);
            D_i5_801BE368[1] += D_i5_801BE368[0];
            if (D_i5_801BE368[1] > 200.0f) {
                D_i5_801BE320[0] = 1;
            }
            break;

        case 1:
            Math_SmoothStepToF(&D_i5_801BE368[0], -30.0f, 0.1f, RAND_FLOAT(1.0f) + 1.0f, 0.01f);
            D_i5_801BE368[1] += D_i5_801BE368[0];
            if (D_i5_801BE368[1] < -200.0f) {
                D_i5_801BE320[0] = 0;
            }
            break;
    }

    switch (D_i5_801BE320[1]) {
        case 0:
            D_i5_801BE320[6] = 1;
            D_i5_801BE320[8] = 1;
            D_i5_801BE320[5] = 0;
            D_i5_801BE320[7] = 0;

            Math_SmoothStepToF(&D_i5_801BE368[2], 15.0f, 0.2f, 2.0f, 0.01f);

            D_i5_801BE368[3] += D_i5_801BE368[2];

            if ((((gPlayer[0].trueZpos - this->obj.pos.z) * 0.25f) < D_i5_801BE368[3]) ||
                (D_i5_801BE368[3] > 8000.0f)) {
                D_i5_801BE320[1] = 1;
            }
            break;

        case 1:
            D_i5_801BE320[6] = 0;
            D_i5_801BE320[8] = 0;
            D_i5_801BE320[5] = 0;
            D_i5_801BE320[7] = 0;

            Math_SmoothStepToF(&D_i5_801BE368[2], -4.0f, 0.1f, 2.0f, 0.01f);

            D_i5_801BE368[3] += D_i5_801BE368[2];
            if (D_i5_801BE368[3] < -300.0f) {
                D_i5_801BE320[1] = 0;
            }
            break;
    }
    Math_SmoothStepToF(&this->obj.pos.x, this->fwork[19] + D_i5_801BE368[1], 0.2f, 30.0f, 0.01f);
    Math_SmoothStepToF(&this->obj.pos.y, (this->fwork[5] + 600.0f) + D_i5_801BE368[3], 0.2f, 30.0f, 0.01f);
    Math_SmoothStepToF(&this->obj.pos.z, 1200.0f + D_i5_801BE368[6], 0.2f, 30.0f, 0.01f);
}

void Macbeth_801A6FB4(Actor207* this) {
    // FAKE
    if (1) {}

    Macbeth_801A0308(this, this->obj.pos.z, this->obj.rot.y, 0);

    switch (D_i5_801BE320[0]) {
        case 0:
            Math_SmoothStepToF(&D_i5_801BE368[0], 20.0f, 0.1f, RAND_FLOAT(1.0f) + 1.0f, 0.01f);
            D_i5_801BE368[1] += D_i5_801BE368[0];
            if (D_i5_801BE368[1] > 200.0f) {
                D_i5_801BE320[0] = 1;
            }
            break;

        case 1:
            Math_SmoothStepToF(&D_i5_801BE368[0], -20.0f, 0.1f, RAND_FLOAT(1.0f) + 1.0f, 0.01f);
            D_i5_801BE368[1] += D_i5_801BE368[0];
            if (D_i5_801BE368[1] < -200.0f) {
                D_i5_801BE320[0] = 0;
            }
            break;
    }

    switch (D_i5_801BE320[1]) {
        case 0:
            D_i5_801BE320[6] = 1;
            D_i5_801BE320[8] = 1;

            Math_SmoothStepToF(&D_i5_801BE368[2], 15.0f, 0.2f, 2.0f, 0.01f);

            D_i5_801BE368[3] += D_i5_801BE368[2];

            if ((((gPlayer[0].trueZpos - this->obj.pos.z) * 0.25f) < D_i5_801BE368[3]) ||
                (D_i5_801BE368[3] > 8000.0f)) {
                D_i5_801BE320[1] = 1;
            }
            break;

        case 1:
            D_i5_801BE320[6] = 0;
            D_i5_801BE320[8] = 0;
            Math_SmoothStepToF(&D_i5_801BE368[2], -4.0f, 0.1f, 2.0f, 0.01f);
            D_i5_801BE368[3] += D_i5_801BE368[2];
            if (D_i5_801BE368[3] < 0.0f) {
                D_i5_801BE320[1] = 0;
            }
            break;
    }
    Math_SmoothStepToF(&this->obj.pos.x, this->fwork[19] + D_i5_801BE368[1], 0.2f, 30.0f, 0.01f);
    Math_SmoothStepToF(&this->obj.pos.y, (this->fwork[5] + 600.0f) + D_i5_801BE368[3], 0.2f, 30.0f, 0.01f);
    Math_SmoothStepToF(&this->obj.pos.z, 1200.0f + D_i5_801BE368[6], 0.2f, 30.0f, 0.01f);
}

void Macbeth_801A72DC(Actor207* this) {
    Macbeth_801A0308(this, this->obj.pos.z, this->obj.rot.y, 0);

    switch (D_i5_801BE320[0]) {
        case 0:
            Math_SmoothStepToF(&D_i5_801BE368[0], 5.0f, 0.1f, RAND_FLOAT(1.0f) + 0.3f, 0.01f);
            D_i5_801BE368[1] += D_i5_801BE368[0];
            if (D_i5_801BE368[1] > 100.0f) {
                D_i5_801BE320[0] = 1;
            }
            break;

        case 1:
            Math_SmoothStepToF(&D_i5_801BE368[0], -5.0f, 0.1f, RAND_FLOAT(1.0f) + 0.3f, 0.01f);
            D_i5_801BE368[1] += D_i5_801BE368[0];
            if (D_i5_801BE368[1] < -100.0f) {
                D_i5_801BE320[0] = 0;
            }
            break;
    }
    Math_SmoothStepToF(&this->obj.pos.x, this->fwork[19] + D_i5_801BE368[1], 0.2f, 30.0f, 0.01f);
    Math_SmoothStepToF(&this->obj.pos.y, this->fwork[5] + 600.0f, 0.2f, 30.0f, 0.01f);
    Math_SmoothStepToF(&this->obj.pos.z, 1200.0f + D_i5_801BE368[6], 0.2f, 30.0f, 0.01f);
}

void Macbeth_801A74C4(Actor207* this) {
    Macbeth_801A0308(this, this->obj.pos.z, this->obj.rot.y, 0);

    switch (D_i5_801BE320[0]) {
        case 0:
            Math_SmoothStepToF(&D_i5_801BE368[0], 22.0f, 0.1f, RAND_FLOAT(1.0f) + 1.0f, 0.01f);
            D_i5_801BE368[1] += D_i5_801BE368[0];
            if (D_i5_801BE368[1] > 200.0f) {
                D_i5_801BE320[0] = 1;
            }
            break;

        case 1:
            Math_SmoothStepToF(&D_i5_801BE368[0], -22.0f, 0.1f, RAND_FLOAT(1.0f) + 1.0f, 0.01f);
            D_i5_801BE368[1] += D_i5_801BE368[0];
            if (D_i5_801BE368[1] < -200.0f) {
                D_i5_801BE320[0] = 0;
            }
            break;
    }

    switch (D_i5_801BE320[1]) {
        case 0:
            D_i5_801BE320[5] = 1;
            D_i5_801BE320[7] = 1;
            Math_SmoothStepToF(&D_i5_801BE368[2], 10.0f, 0.4f, 10.0f, 0.01f);
            D_i5_801BE368[3] += D_i5_801BE368[2];
            if ((((gPlayer[0].trueZpos - this->obj.pos.z) * 0.25f) < D_i5_801BE368[3]) ||
                (D_i5_801BE368[3] > 8000.0f)) {
                D_i5_801BE320[1] = 1;
            }
            break;

        case 1:
            D_i5_801BE320[5] = 0;
            D_i5_801BE320[7] = 0;
            D_i5_801BE320[6] = 0;
            D_i5_801BE320[8] = 0;
            Math_SmoothStepToF(&D_i5_801BE368[2], -20.0f, 0.3f, 8.0f, 0.01f);
            D_i5_801BE368[3] += D_i5_801BE368[2];
            if (D_i5_801BE368[3] < -200.0f) {
                D_i5_801BE320[1] = 0;
            }
            break;
    }

    switch (D_i5_801BE320[12]) {
        case 0:
            Math_SmoothStepToF(&this->obj.rot.z, 45.0f, 0.4f, 10.0f, 1.0f);
            if (this->obj.rot.z >= 45.0f) {
                D_i5_801BE320[12] = 1;
            }
            break;

        case 1:
            Math_SmoothStepToF(&this->obj.rot.z, -45.0f, 0.4f, 10.0f, 1.0f);
            if (this->obj.rot.z <= -45.0f) {
                D_i5_801BE320[12] = 0;
            }
            break;
    }
    Math_SmoothStepToF(&this->obj.pos.x, this->fwork[19] + D_i5_801BE368[1], 0.2f, 30.0f, 0.01f);
    Math_SmoothStepToF(&this->obj.pos.y, (this->fwork[5] + 600.0f) + D_i5_801BE368[3], 0.2f, 30.0f, 0.01f);
    Math_SmoothStepToF(&this->obj.pos.z, 1200.0f + D_i5_801BE368[6], 0.2f, 30.0f, 0.01f);
}

void Macbeth_801A78B0(Actor207* this) {
    Macbeth_801A0308(this, this->obj.pos.z, this->obj.rot.y, 0);

    switch (D_i5_801BE320[0]) {
        case 0:
            Math_SmoothStepToF(&D_i5_801BE368[0], 10.0f, 0.1f, RAND_FLOAT(1.0f) + 1.0f, 0.01f);
            D_i5_801BE368[1] += D_i5_801BE368[0];
            if (D_i5_801BE368[1] > 200.0f) {
                D_i5_801BE320[0] = 1;
            }
            break;

        case 1:
            Math_SmoothStepToF(&D_i5_801BE368[0], -10.0f, 0.1f, RAND_FLOAT(1.0f) + 1.0f, 0.01f);
            D_i5_801BE368[1] += D_i5_801BE368[0];
            if (D_i5_801BE368[1] < -200.0f) {
                D_i5_801BE320[0] = 0;
            }
            break;
    }
    Math_SmoothStepToF(&this->obj.pos.x, this->fwork[19] + D_i5_801BE368[1], 0.1f, 10.0f, 0.01f);
}

void Macbeth_801A7A30(Actor207* this) {
    Macbeth_801A0308(this, this->obj.pos.z, this->obj.rot.y, 0);

    switch (D_i5_801BE320[0]) {
        case 0:
            Math_SmoothStepToF(&D_i5_801BE368[0], 30.0f, 0.1f, RAND_FLOAT(1.0f) + 1.0f, 0.01f);
            D_i5_801BE368[1] += D_i5_801BE368[0];
            if (D_i5_801BE368[1] > 10.0f) {
                D_i5_801BE320[0] = 1;
            }
            break;

        case 1:
            Math_SmoothStepToF(&D_i5_801BE368[0], -30.0f, 0.1f, RAND_FLOAT(1.0f) + 1.0f, 0.01f);
            D_i5_801BE368[1] += D_i5_801BE368[0];
            if (D_i5_801BE368[1] < -10.0f) {
                D_i5_801BE320[0] = 0;
            }
            break;
    }

    switch (D_i5_801BE320[1]) {
        case 0:
            D_i5_801BE320[6] = 0;
            D_i5_801BE320[8] = 0;
            D_i5_801BE320[5] = 0;
            D_i5_801BE320[7] = 0;
            Math_SmoothStepToF(&D_i5_801BE368[2], 15.0f, 0.2f, 2.0f, 0.01f);
            D_i5_801BE368[3] += D_i5_801BE368[2];
            if (D_i5_801BE368[3] > 500.0f) {
                D_i5_801BE320[1] = 1;
            }
            break;

        case 1:
            D_i5_801BE320[6] = 0;
            D_i5_801BE320[8] = 0;
            D_i5_801BE320[5] = 0;
            D_i5_801BE320[7] = 0;
            Math_SmoothStepToF(&D_i5_801BE368[2], -4.0f, 0.1f, 2.0f, 0.01f);
            D_i5_801BE368[3] += D_i5_801BE368[2];
            if (D_i5_801BE368[3] < 350.0f) {
                D_i5_801BE320[1] = 0;
            }
            break;
    }
    this->obj.pos.x = this->fwork[19] + D_i5_801BE368[1];
    this->obj.pos.y = this->fwork[5] + D_i5_801BE368[3];
    this->obj.pos.z = 1200.0f + D_i5_801BE368[6];
}

void Macbeth_Actor207_FacePlayer(Actor207* this) {
    f32 xDist;
    f32 yDist;
    f32 xRot;
    f32 yRot;
    f32 EuclDist;

    xDist = gPlayer[0].pos.x - this->obj.pos.x;
    yDist = (gPlayer[0].trueZpos - 130.0f) - this->obj.pos.z;

    EuclDist = sqrtf(SQ(xDist) + SQ(yDist));

    yRot = Math_Atan2F(xDist, yDist);
    xRot = -Math_Atan2F(gPlayer[0].pos.y - this->obj.pos.y, EuclDist);

    Math_SmoothStepToAngle(&this->obj.rot.y, Math_RadToDeg(yRot), 0.1f, 20.0f, 0.01f);
    Math_SmoothStepToAngle(&this->obj.rot.x, Math_RadToDeg(xRot), 0.1f, 20.0f, 0.01f);
}

void Macbeth_Actor207_Init(Actor207* this) {
    u8 i;

    Macbeth_Train_Init(this);
    // clang-format off
    for (i = 0; i < 35; i++) { D_i5_801BE320[i] = 0; }
    for (i = 0; i < 50; i++) { D_i5_801BE368[i] = 0.0f; }
    // clang-format on
    D_i5_801BE320[29] = 250;
    D_i5_801BE320[9] = 200;
    D_i5_801BE320[10] = 250;

    this->info.hitbox = SEGMENTED_TO_VIRTUAL(gNoHitbox);

    D_i5_801BE320[14] = 0;
    D_i5_801BE320[15] = 0;

    gBossFrameCount = 0;
}

Vec3f D_i5_801BA744 = { 0.0f, 0.0f, 0.0f };
Vec3f D_i5_801BA750 = { 0.0f, 0.0f, 30.0f };

void Macbeth_Actor207_Update(Actor207* this) {
    s32 pad;
    f32 temp;
    f32 sp374;
    f32 var_fv0;
    s32 temp_a3;
    Vec3f sp360;
    Vec3f sp354;
    Vec3f sp348;
    Vec3f sp33C;
    Vec3f sp330;
    s32 var_s0;
    Vec3f spD4[50];
    s32 pad2;
    s32 var_v0;
    s32 var_v1;
    s16 spC6;
    u8 i;

#ifdef AVOID_UB
    sp374 = 0.0f;
#endif

    switch (this->state) {
        case 0:
            Macbeth_8019A198(this);
            Macbeth_801A015C(this);

            this->obj.pos.y += 250.0f;
            D_i5_801BE320[3] = 0;

            Macbeth_8019A830(this);
            Macbeth_8019A728(this);

            if (this->iwork[1] != 0) {
                AUDIO_PLAY_BGM(NA_BGM_BOSS_MA);
                this->state = 1;
            }
            Macbeth_801A6984(this);
            break;

        case 1:
            Macbeth_8019A198(this);
            Macbeth_801A015C(this);
            this->obj.pos.y += 250.0f;

            D_i5_801BE320[3]++;
            if (D_i5_801BE320[3] >= 20) {
                this->timer_0BC = 20;
                this->state = 2;
            }
            Macbeth_8019A830(this);
            Macbeth_801A6984(this);
            break;

        case 2:
            Macbeth_8019A198(this);
            Macbeth_801A0308(this, this->obj.pos.z, this->obj.rot.y, 0);

            if (this->timer_0BC == 0) {
                Math_SmoothStepToF(&this->obj.pos.y, this->fwork[5] + 500.0f, 0.5f, 5.0f, 5.0f);
                D_i5_801BE320[5] = 1;
                D_i5_801BE320[7] = 1;
                if ((this->fwork[5] + 500.0f) <= this->obj.pos.y) {
                    Radio_PlayMessage(gMsg_ID_17430, RCID_BOSS_MACBETH);
                    this->info.hitbox = SEGMENTED_TO_VIRTUAL(aMaActor207Hitbox);
                    this->state = 3;
                }
            }
            Macbeth_8019A830(this);
            Macbeth_801A6984(this);
            break;

        case 3:
            Macbeth_8019A198(this);

            if (this->timer_0BC == 0) {
                this->obj.pos.z -= 2.0f;
                if (D_i5_801BE320[3] < 70) {
                    D_i5_801BE320[3] = (s16) (D_i5_801BE320[3] + 1);
                }
                if (D_i5_801BE320[3] == 30) {
                    D_i5_801BE320[5] = 0;
                    D_i5_801BE320[7] = 0;
                    D_i5_801BE320[6] = 1;
                    D_i5_801BE320[8] = 1;
                }

                Math_SmoothStepToF(&this->obj.pos.y, this->fwork[5] + 1600.0f, 0.2f, 30.0f, 10.0f);

                if ((this->fwork[5] + 1600.0f) <= this->obj.pos.y) {
                    D_i5_801BE320[6] = 0;
                    D_i5_801BE320[8] = 0;
                    D_i5_801BE320[3] = 0;
                    D_i5_801BE320[2] = 1;
                    D_i5_801BE320[31] = 30;
                    this->timer_0C0 = 1500;
                    this->state = 4;
                }
            }
            Macbeth_8019A830(this);
            Macbeth_801A6984(this);
            break;

        case 4:
            Math_SmoothStepToAngle(&this->obj.rot.z, 0.0f, 0.1f, 20.0f, 0.01f);
            Macbeth_8019A198(this);

            D_i5_801BE320[3]++;
            if (D_i5_801BE320[3] >= 60) {
                D_i5_801BE320[3] = 0;
            }

            Macbeth_801A6C78(this);
            Macbeth_801A6984(this);
            Macbeth_Actor207_FacePlayer(this);

            if ((D_i5_801BE320[16] != 0) && (gPlayer[0].state == PLAYERSTATE_ACTIVE)) {
                var_v1 = 0xFF;
                if (D_i5_801BE320[18] == 2) {
                    var_v1 = 3;
                } else if (D_i5_801BE320[18] == 3) {
                    var_v1 = 0;
                } else if (D_i5_801BE320[18] == 4) {
                    D_i5_801BE320[3] = 0;
                    D_i5_801BE320[2] = 2;
                    D_i5_801BE320[31] = 30;
                    this->iwork[7] = 0;
                    this->iwork[8] = 0;
                    this->iwork[9] = 0;
                    Radio_PlayMessage(gMsg_ID_17475, RCID_BOSS_MACBETH);
                    this->state = 18;
                    break;
                }

                if ((var_v1 & gGameFrameCount) == 0) {
                    if ((D_i5_801BE320[9] > 0) || (D_i5_801BE320[10] > 0)) {
                        if (this->timer_0C0 == 0) {
                            this->timer_0C0 = 1500;
                            Radio_PlayMessage(gMsg_ID_17460, RCID_BOSS_MACBETH);
                        }
                        if (((D_i5_801BE320[9] > 0) && (Rand_ZeroOne() > 0.5f)) || (D_i5_801BE320[10] <= 0) ||
                            ((D_i5_801BE320[9] > 0) && (D_i5_801BE320[26] == 0))) {
                            if (D_i5_801BE320[9] > 0) {
                                D_i5_801BE320[6] = 1;
                                D_i5_801BE320[8] = 1;
                                D_i5_801BE320[5] = 1;
                                D_i5_801BE320[7] = 1;
                                D_i5_801BE320[3] = 0;
                                D_i5_801BE320[2] = 5;
                                D_i5_801BE320[31] = 30;
                                this->timer_0BC = 100;
                                AUDIO_PLAY_SFX(NA_SE_EN_MABOSS_CHARGE0, this->sfxSource, 4);
                                this->state = 12;
                            }
                        } else if ((D_i5_801BE320[26] != 0) && (D_i5_801BE320[10] > 0)) {
                            D_i5_801BE320[6] = 1;
                            D_i5_801BE320[8] = 1;
                            D_i5_801BE320[5] = 0;
                            D_i5_801BE320[7] = 0;
                            D_i5_801BE320[3] = 0;
                            D_i5_801BE320[2] = 2;
                            D_i5_801BE320[31] = 30;
                            this->state = 5;
                        }
                    } else if ((D_i5_801BE320[20] != 3) && (D_i5_801BE320[25] == 0)) {
                        if ((Rand_ZeroOne() > 0.5f) && (D_i5_801BE320[26] != 0)) {
                            D_i5_801BE320[6] = 0;
                            D_i5_801BE320[8] = 0;
                            D_i5_801BE320[5] = 0;
                            D_i5_801BE320[7] = 0;
                            D_i5_801BE320[3] = 0;
                            D_i5_801BE320[2] = 7;
                            D_i5_801BE320[31] = 30;
                            this->timer_0BC = 100;
                            this->state = 15;
                        } else {
                            D_i5_801BE320[6] = 1;
                            D_i5_801BE320[8] = 0;
                            D_i5_801BE320[5] = 0;
                            D_i5_801BE320[7] = 0;
                            D_i5_801BE320[3] = 0;
                            D_i5_801BE320[2] = 4;
                            D_i5_801BE320[31] = 30;
                            this->timer_0BC = 20;
                            this->state = 11;
                        }
                    }
                }
            }
            break;

        case 5:
            Macbeth_8019A198(this);
            Macbeth_801A0308(this, this->obj.pos.z, this->obj.rot.y, 0);

            Math_SmoothStepToF(&this->obj.pos.x, gPlayer[0].pos.x, 0.1f, 10.0f, 0.01f);
            Math_SmoothStepToF(&this->obj.pos.z, gPlayer[0].trueZpos - 1500.0f, 0.1f, 20.0f, 0.01f);
            Math_SmoothStepToF(&this->obj.pos.y,
                               (this->fwork[5] + 600.0f + (gPlayer[0].trueZpos - this->obj.pos.z) * 0.25f) + 10.0f,
                               0.1f, 10.0f, 0.01f);
            if (((this->fwork[5] + 600.0f + (gPlayer[0].trueZpos - this->obj.pos.z) * 0.25f) <= this->obj.pos.y) &&
                (this->obj.pos.z < (gPlayer[0].trueZpos - 1300.0f))) {
                this->timer_0BC = 0;
                this->state = 6;
            }
            Macbeth_Actor207_FacePlayer(this);
            Macbeth_801A6984(this);
            break;

        case 6:
            Macbeth_8019A198(this);

            if (this->timer_0BC <= 0) {
                this->state = 7;
            }

            D_i5_801BE368[9] = gPlayer[0].pos.x;

            Macbeth_Actor207_FacePlayer(this);
            Macbeth_801A6984(this);
            break;

        case 7:
            if ((gPlayer[0].trueZpos - this->obj.pos.z) < 1200.0f) {
                if (D_i5_801BE320[3] < (Animation_GetFrameCount(&D_MA_601D188) - 1)) {
                    D_i5_801BE320[3] = (s16) (D_i5_801BE320[3] + 1);
                    if ((D_i5_801BE320[3] == 26) && (D_i5_801BE320[10] > 0)) {
                        this->info.hitbox = SEGMENTED_TO_VIRTUAL(D_MA_6036818);
                        AUDIO_PLAY_SFX(NA_SE_EN_CATCH, this->sfxSource, 4);
                    }
                } else {
                    this->info.hitbox = SEGMENTED_TO_VIRTUAL(gNoHitbox);
                    if ((gPlayer[0].pos.y + 1200.0f) < this->obj.pos.y) {
                        this->info.hitbox = SEGMENTED_TO_VIRTUAL(aMaActor207Hitbox);
                        D_i5_801BE320[3] = 0;
                        D_i5_801BE320[2] = 1;
                        D_i5_801BE320[31] = 30;
                        D_i5_801BE320[6] = 0;
                        D_i5_801BE320[8] = 0;
                        this->state = 4;
                    }
                }
            }

            switch (D_i5_801BE320[18]) {
                case 0:
                case 1:
                    var_fv0 = 500.0f;
                    break;
                case 2:
                    var_fv0 = 350.0f;
                    break;
                case 3:
                    var_fv0 = 200.0f;
                    break;
                default:
                    var_fv0 = 100.0f;
                    break;
            }

            if (var_fv0 < (gPlayer[0].trueZpos - this->obj.pos.z)) {
                Macbeth_Actor207_FacePlayer(this);
                D_i5_801BE368[9] = gPlayer[0].pos.x;
            }

            Math_SmoothStepToF(&this->obj.pos.x, D_i5_801BE368[9], 0.2f, 30.0f, 0.01f);

            if (D_i5_801BE320[3] < 29) {
                Math_SmoothStepToF(&this->obj.pos.y, gPlayer[0].pos.y + 250.0f, 0.3f, 45.0f, 0.01f);
            } else {
                Math_SmoothStepToF(&this->obj.pos.y, gPlayer[0].pos.y + 1210.0f, 0.1f, 20.0f, 0.01f);
            }

            Math_SmoothStepToF(&this->obj.pos.z, gPlayer[0].trueZpos - 100.0f, 0.3f, 60.0f, 0.01f);
            Math_SmoothStepToF(&this->obj.rot.x, 0.0f, 0.2f, 20.0f, 0.01f);
            Macbeth_801A6984(this);
            break;

        case 8:
            Macbeth_8019A198(this);

            if (((gGameFrameCount % 16) == 0)) {
                AUDIO_PLAY_SFX(NA_SE_EN_MABOSS_RAGE, this->sfxSource, 4);
            }

            Macbeth_801A74C4(this);
            Macbeth_801A6984(this);

            if (D_i5_801BE320[3] < (Animation_GetFrameCount(&D_MA_6017714) - 1)) {
                D_i5_801BE320[3] = (s16) (D_i5_801BE320[3] + 1);
            } else {
                D_i5_801BE320[3] = 0;
            }

            if (D_i5_801BE320[4] <= 0) {
                D_i5_801BE320[3] = 0;
                D_i5_801BE320[2] = 1;
                this->obj.rot.x -= 360.0f;
                D_i5_801BE320[3] = 0;
                D_i5_801BE320[2] = 1;
                D_i5_801BE320[31] = 30;
                D_i5_801BE320[5] = 0;
                D_i5_801BE320[7] = 0;
                D_i5_801BE320[6] = 0;
                D_i5_801BE320[8] = 0;
                this->state = 4;
                break;
            }

            if (this->dmgType != DMG_NONE) {
                this->dmgType = DMG_NONE;
                this->iwork[9] = 15;

                D_i5_801BE320[29] -= this->damage;
                if (D_i5_801BE320[29] <= 0) {
                    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 1);
                    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 1);
                    gFillScreenRed = gFillScreenGreen = gFillScreenBlue = gFillScreenAlpha = 255;
                    AUDIO_PLAY_SFX(NA_SE_EN_DOWN_IMPACT, this->sfxSource, 4);
                    Radio_PlayMessage(gMsg_ID_17450, RCID_BOSS_MACBETH);
                    func_effect_8007D2C8(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 10.0f);
                    Macbeth_Effect357_Spawn1(this->vwork[2].x, this->vwork[2].y, this->vwork[2].z,
                                             RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT(7.0f) + 7.0f, -2.0f,
                                             RAND_FLOAT(360.0f), RAND_FLOAT(360.0f), RAND_FLOAT(360.0f),
                                             RAND_FLOAT_CENTERED(30.0f), RAND_FLOAT_CENTERED(30.0f),
                                             RAND_FLOAT_CENTERED(30.0f), (s32) (RAND_FLOAT(50.0f) + 70.0f), 11, 1.0f);
                    D_i5_801BE320[3] = 0;
                    D_i5_801BE320[2] = 1;
                    D_i5_801BE320[31] = 30;
                    this->state = 9;
                    break;
                }

                D_i5_801BE368[12] = 30.0f;
                D_i5_801BE368[13] = 30.0f;

                if (D_i5_801BE320[29] > 0) {
                    if (D_i5_801BE320[29] > 100) {
                        AUDIO_PLAY_SFX(NA_SE_OB_DAMAGE_M, this->sfxSource, 4);
                    } else {
                        AUDIO_PLAY_SFX(NA_SE_EN_KNOCK_DOWN, this->sfxSource, 4);
                    }
                }
            }

            if ((gGameFrameCount % 2) == 0) {
                this->obj.pos.x += D_i5_801BE368[12];
                this->obj.pos.y += D_i5_801BE368[13];
            } else {
                this->obj.pos.x -= D_i5_801BE368[12];
                this->obj.pos.y -= D_i5_801BE368[13];
            }

            if (D_i5_801BE368[12] > 0.0f) {
                D_i5_801BE368[12] -= 1.0f;
            }

            if (D_i5_801BE368[13] > 0.0f) {
                D_i5_801BE368[13] -= 1.0f;
            }

            Math_SmoothStepToAngle(&this->obj.rot.x, 0.0f, 0.1f, 20.0f, 0.01f);
            Math_SmoothStepToAngle(&this->obj.rot.y, 0.0f, 0.1f, 20.0f, 0.01f);

            if ((gGameFrameCount % 32) == 0) {
                D_i5_801BE320[6] = 0;
                D_i5_801BE320[8] = 0;
                D_i5_801BE320[5] = 0;
                D_i5_801BE320[7] = 0;

                if (Rand_ZeroOne() >= 0.5f) {
                    D_i5_801BE320[6] = 1;
                }
                if (Rand_ZeroOne() >= 0.5f) {
                    D_i5_801BE320[8] = 1;
                }
                if (Rand_ZeroOne() >= 0.5f) {
                    D_i5_801BE320[5] = 1;
                }
                if (Rand_ZeroOne() >= 0.5f) {
                    D_i5_801BE320[7] = 1;
                }
            }
            break;

        case 9:
            if (D_i5_801BE368[6] < this->obj.pos.z) {
                D_i5_801BE320[1] = 1;
                Macbeth_801A6984(this);
            }

            if ((this->obj.pos.z - D_i5_801BE368[6]) < 500) {
                Math_SmoothStepToF(&this->obj.pos.x, D_i5_801BE368[4], 0.1f, 10.0f, 1.0f);
                Math_SmoothStepToF(&this->obj.pos.y, D_i5_801BE368[5] - 100.0f, 0.1f, 15.0f, 10.0f);
            } else {
                Math_SmoothStepToF(&this->obj.pos.y, D_i5_801BE368[5] + 600.0f, 0.1f, 20.0f, 10.0f);
            }

            Math_SmoothStepToF(&this->obj.pos.z, D_i5_801BE368[6] - 100.0f, 0.2f, 5.0f - gActors[D_i5_801BE314].vel.z,
                               1.0f);

            this->obj.rot.x += 10.0f;
            this->obj.rot.z += 10.0f;

            if ((gGameFrameCount % 8) == 0) {
                func_effect_8007D2C8(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 10.0f);
                Effect_Effect387_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 5.0f, 8);
            }

            if ((this->obj.pos.z <= D_i5_801BE368[6]) && (this->obj.pos.y <= D_i5_801BE368[5])) {
                D_i5_801BE320[23] = 1;
                gTeamLowHealthMsgTimer = -1;
                this->state = 10;
                this->timer_0BC = 50;
            }
            break;

        case 10:
            Object_Kill(&this->obj, this->sfxSource);
            break;

        case 11:
            Math_SmoothStepToAngle(&this->obj.rot.y, 0.0f, 0.1f, 20.0f, 0.01f);
            Math_SmoothStepToAngle(&this->obj.rot.x, 0.0f, 0.1f, 20.0f, 0.01f);
            Math_SmoothStepToAngle(&this->obj.rot.z, 0.0f, 0.1f, 20.0f, 0.01f);

            Macbeth_8019A198(this);
            Macbeth_801A6FB4(this);
            Macbeth_801A6984(this);

            if (this->timer_0BC == 0) {
                if (D_i5_801BE320[3] < (Animation_GetFrameCount(&D_MA_6016B2C) - 1)) {
                    D_i5_801BE320[3]++;
                } else {
                    D_i5_801BE320[3] = 0;
                }

                switch (D_i5_801BE320[18]) {
                    case 0:
                    case 1:
                        var_v0 = 16 - 1;
                        var_s0 = 10;
                        break;
                    case 2:
                        var_v0 = 16 - 1;
                        var_s0 = 20;
                        break;
                    case 3:
                        var_v0 = 8 - 1;
                        var_s0 = 20;
                        break;
                    default:
                        var_v0 = 4 - 1;
                        var_s0 = 10;
                        break;
                }

                if ((var_v0 & gGameFrameCount) == 0) {
                    Macbeth_MaBombDrop_Spawn(this->obj.pos.x, this->obj.pos.y - 90.0f, this->obj.pos.z - 50.0f,
                                             D_i5_801BE368[0] * 0.8f, -10.0f, 8.0f);
                    D_i5_801BE320[11]++;
                    if (D_i5_801BE320[11] >= var_s0) {
                        this->info.hitbox = SEGMENTED_TO_VIRTUAL(aMaActor207Hitbox);
                        D_i5_801BE320[3] = 0;
                        D_i5_801BE320[2] = 1;
                        D_i5_801BE320[31] = 30;
                        D_i5_801BE320[5] = 0;
                        D_i5_801BE320[7] = 0;
                        D_i5_801BE320[11] = 0;
                        this->state = 4;
                        D_i5_801BE320[25] = 1;
                    }
                }
            }

            if ((gGameFrameCount % 32) == 0) {
                D_i5_801BE320[6] = 0;
                D_i5_801BE320[8] = 0;
                D_i5_801BE320[5] = 0;
                D_i5_801BE320[7] = 0;

                if (Rand_ZeroOne() >= 0.5f) {
                    D_i5_801BE320[6] = 1;
                }
                if (Rand_ZeroOne() >= 0.5f) {
                    D_i5_801BE320[8] = 1;
                }
                if (Rand_ZeroOne() >= 0.5f) {
                    D_i5_801BE320[5] = 1;
                }
                if (Rand_ZeroOne() >= 0.5f) {
                    D_i5_801BE320[7] = 1;
                }
            }
            break;

        case 12:
            Math_SmoothStepToAngle(&this->obj.rot.y, 0.0f, 0.1f, 20.0f, 0.01f);
            Math_SmoothStepToAngle(&this->obj.rot.x, 0.0f, 0.1f, 20.0f, 0.01f);
            Math_SmoothStepToAngle(&this->obj.rot.z, 0.0f, 0.1f, 20.0f, 0.01f);

            if (D_i5_801BE320[3] < (Animation_GetFrameCount(&D_MA_60163F0) - 1)) {
                D_i5_801BE320[3]++;
            } else {
                D_i5_801BE320[3] = 0;
            }

            Macbeth_8019A198(this);
            Macbeth_801A72DC(this);
            Macbeth_801A6984(this);

            if (D_i5_801BE320[9] <= 0) {
                Audio_KillSfxBySourceAndId(this->sfxSource, NA_SE_EN_MABOSS_CHARGE0);
                this->state = 14;
                this->vel.y = -20.0f;
            }

            D_i5_801BE368[14] = this->vwork[0].x;
            D_i5_801BE368[15] = this->vwork[0].y;
            D_i5_801BE368[16] = this->vwork[0].z;

            if (this->timer_0BC > 15) {
                for (i = 0; i < 2; i++) {
                    D_i5_801BE368[23] = 3.0f;
                    Macbeth_Effect379_Spawn(this->vwork[2].x + RAND_FLOAT_CENTERED(400.0f),
                                            this->vwork[2].y + RAND_FLOAT_CENTERED(400.0f), this->vwork[2].z + 50.0f,
                                            this->vwork[2].x - 200.0f, this->vwork[2].y, this->vwork[2].z);
                    D_i5_801BE368[23] = 4.0f;
                    Macbeth_Effect379_Spawn(this->vwork[4].x + RAND_FLOAT_CENTERED(400.0f),
                                            this->vwork[4].y + RAND_FLOAT_CENTERED(400.0f), this->vwork[4].z + 50.0f,
                                            this->vwork[4].x + 200.0f, this->vwork[4].y, this->vwork[4].z);
                }
            }

            if (this->timer_0BC == 0) {
                Audio_KillSfxBySourceAndId(this->sfxSource, NA_SE_EN_MABOSS_CHARGE0);
                D_i5_801BE320[3] = 0;
                D_i5_801BE320[2] = 6;
                D_i5_801BE320[31] = 30;
                this->timer_0BC = 70;
                this->state = 13;
            }
            break;

        case 13:
            Math_SmoothStepToAngle(&this->obj.rot.y, 0.0f, 0.1f, 20.0f, 0.01f);
            Math_SmoothStepToAngle(&this->obj.rot.x, 0.0f, 0.1f, 20.0f, 0.01f);
            Math_SmoothStepToAngle(&this->obj.rot.z, 0.0f, 0.1f, 20.0f, 0.01f);

            if (D_i5_801BE320[3] < (Animation_GetFrameCount(&D_MA_6016040) - 1)) {
                D_i5_801BE320[3]++;
            }

            Macbeth_8019A198(this);
            Macbeth_801A72DC(this);
            Macbeth_801A6984(this);

            D_i5_801BE320[5] = 0;
            D_i5_801BE320[7] = 0;

            if (this->timer_0BC == 60) {
                AUDIO_PLAY_SFX(NA_SE_EN_MABOSS_SHOT0, this->sfxSource, 4);
                D_i5_801BE320[24] = 0;

                spC6 = RAND_INT(5.0f);

                for (i = 0; i < 10; i++) {
                    Macbeth_MaSpear_Spawn(this->vwork[0].x, this->vwork[0].y + 100.0f, this->vwork[0].z,
                                          RAND_FLOAT_CENTERED(35.0f), RAND_FLOAT(80) + 90.0f, RAND_RANGE(-72.0f, 8.0f),
                                          spC6);
                }

                for (i = 0; i < 20; i++) {
                    Macbeth_Effect357_Spawn1(
                        this->vwork[0].x, this->vwork[0].y + 50.0f + RAND_FLOAT(50.0f), this->vwork[0].z,
                        RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT(5.0f), this->vel.z + 2.0f, RAND_FLOAT(360.0f),
                        RAND_FLOAT(360.0f), RAND_FLOAT(360.0f), RAND_FLOAT_CENTERED(30.0f), RAND_FLOAT_CENTERED(30.0f),
                        RAND_FLOAT_CENTERED(30.0f), (s32) (RAND_FLOAT(25.0f) + 30.f), 10, RAND_FLOAT(1.0f));
                }
                this->timer_0BC = 80;
                this->state = 14;
                this->vel.y = -20.0f;
            }
            break;

        case 14:
            Math_SmoothStepToAngle(&this->obj.rot.y, 0.0f, 0.1f, 20.0f, 0.01f);
            Math_SmoothStepToAngle(&this->obj.rot.x, 0.0f, 0.1f, 20.0f, 0.01f);
            Math_SmoothStepToAngle(&this->obj.rot.z, 0.0f, 0.1f, 20.0f, 0.01f);

            if (D_i5_801BE320[3] < (Animation_GetFrameCount(&D_MA_6016040) - 1)) {
                D_i5_801BE320[3]++;
            }

            Macbeth_8019A198(this);

            this->vel.y += 1.0f;

            Macbeth_801A6984(this);

            D_i5_801BE320[6] = 1;
            D_i5_801BE320[8] = 1;

            if (this->timer_0BC == 0) {
                this->vel.y = 0.0f;
                this->info.hitbox = SEGMENTED_TO_VIRTUAL(aMaActor207Hitbox);
                D_i5_801BE320[3] = 0;
                D_i5_801BE320[2] = 1;
                D_i5_801BE320[31] = 30;
                this->state = 4;
            }
            break;

        case 15:
            Math_SmoothStepToAngle(&this->obj.rot.y, 0.0f, 0.1f, 20.0f, 0.01f);
            Math_SmoothStepToAngle(&this->obj.rot.x, 0.0f, 0.1f, 20.0f, 0.01f);
            Math_SmoothStepToAngle(&this->obj.rot.z, 0.0f, 0.1f, 20.0f, 0.01f);

            Math_SmoothStepToF(&this->obj.pos.z, gPlayer[0].trueZpos - 700.0f, 0.2f, 15.0f, 0.01f);
            Math_SmoothStepToF(&this->obj.pos.y, gPlayer[0].pos.y + 400.0f, 0.2f, 10.0f, 0.01f);
            Math_SmoothStepToF(&this->obj.pos.x, gPlayer[0].pos.x, 0.1f, 10.0f, 0.01f);

            if (D_i5_801BE320[3] < 15) {
                D_i5_801BE320[3]++;
            }

            Macbeth_8019A198(this);
            Macbeth_801A6984(this);

            if (this->timer_0BC < 100) {
                if (this->timer_0BC == 98) {
                    AUDIO_PLAY_SFX(NA_SE_EN_MABOSS_PLATECHARGE, this->sfxSource, 4);
                }

                Matrix_RotateY(gCalcMatrix, RAND_FLOAT(2.0f) * (M_DTOR * 180.0f), MTXF_NEW);

                sp360.x = 0.0f;
                sp360.y = RAND_FLOAT(100.0f);
                sp360.z = RAND_FLOAT(200.0f) + 100.0f;

                Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp360, &sp354);

                D_i5_801BE368[23] = 1.0f;

                Macbeth_Effect379_Spawn(this->vwork[2].x + sp354.x - 50.0f, this->vwork[2].y + sp354.y + 100.0f,
                                        this->vwork[2].z + sp354.z, this->vwork[2].x, this->vwork[2].y,
                                        this->vwork[2].z);

                D_i5_801BE368[23] = 2.0f;

                Macbeth_Effect379_Spawn(this->vwork[4].x + sp354.x + 50.0f, this->vwork[4].y + sp354.y + 100.0f,
                                        this->vwork[4].z + sp354.z, this->vwork[4].x, this->vwork[4].y,
                                        this->vwork[4].z);
            }

            if (this->timer_0BC == 0) {
                switch (D_i5_801BE320[18]) {
                    case 0:
                    case 1:
                        D_i5_801BE320[27] = 150;
                        break;
                    case 2:
                        D_i5_801BE320[27] = 200;
                        break;
                    case 3:
                        D_i5_801BE320[27] = 250;
                        break;
                    default:
                        D_i5_801BE320[27] = 300;
                        break;
                }
                this->timer_0BC = D_i5_801BE320[27];
                this->state = 16;
                Audio_KillSfxBySourceAndId(this->sfxSource, NA_SE_EN_MABOSS_PLATECHARGE);
            }
            break;

        case 16:
            Math_SmoothStepToAngle(&this->obj.rot.y, 0.0f, 0.1f, 20.0f, 0.01f);
            Math_SmoothStepToAngle(&this->obj.rot.x, 0.0f, 0.1f, 20.0f, 0.01f);
            Math_SmoothStepToAngle(&this->obj.rot.z, 0.0f, 0.1f, 20.0f, 0.01f);

            Math_SmoothStepToF(&this->obj.pos.z, gPlayer[0].trueZpos - 250.0f, 0.1f, 15.0f, 0.01f);
            Math_SmoothStepToF(&this->obj.pos.y, 250.0f, 0.1f, 10.0f, 0.01f);

            if (D_i5_801BE320[3] < (Animation_GetFrameCount(&D_MA_6015C24) - 1)) {
                D_i5_801BE320[3]++;
            }

            Macbeth_8019A198(this);
            Macbeth_801A6984(this);

            if (this->timer_0BC < (D_i5_801BE320[27] - 40)) {
                if ((this->timer_0BC + 42) == D_i5_801BE320[27]) {
                    this->sfxSource[0] = this->vwork[2].x;
                    AUDIO_PLAY_SFX(NA_SE_EN_RNG_BEAM_SHOT, this->sfxSource, 4);
                    this->sfxSource[0] = this->vwork[4].x;
                    AUDIO_PLAY_SFX(NA_SE_EN_RNG_BEAM_SHOT, this->sfxSource, 4);
                    this->sfxSource[0] = this->obj.pos.x;
                }

                if (((gGameFrameCount % 2) == 0) && (D_i5_801BE320[15] == 0)) {
                    this->vwork[6].x = this->vwork[2].x + 80.0f;
                    this->vwork[6].y = 0.0f;
                    this->vwork[6].z = gPlayer[0].trueZpos + 50.0f;
                    this->vwork[7].x = this->vwork[4].x - 80.0f;
                    this->vwork[7].y = 0.0f;
                    this->vwork[7].z = gPlayer[0].trueZpos + 50.0f;
                    this->vwork[6].z += this->vel.z;
                    this->vwork[7].z += this->vel.z;

                    sp348.x = this->vwork[6].x - this->vwork[2].x;
                    sp348.y = this->vwork[6].y - this->vwork[2].y + 25.0f;
                    sp348.z = this->vwork[6].z - this->vwork[2].z;

                    Matrix_RotateZ(gCalcMatrix, -this->vwork[3].z * M_DTOR, MTXF_NEW);
                    Matrix_RotateX(gCalcMatrix, -this->vwork[3].x * M_DTOR, MTXF_APPLY);
                    Matrix_RotateY(gCalcMatrix, -this->vwork[3].y * M_DTOR, MTXF_APPLY);

                    Matrix_MultVec3f(gCalcMatrix, &sp348, &sp354);

                    D_i5_801BE368[14] = Math_RadToDeg(Math_Atan2F(sp354.x, sp354.z));

                    temp = sqrtf(SQ(sp354.x) + SQ(sp354.z));

                    D_i5_801BE368[13] = Math_RadToDeg(-Math_Atan2F(sp354.y, temp));

                    Matrix_RotateY(gCalcMatrix, this->vwork[3].y * M_DTOR, MTXF_NEW);
                    Matrix_RotateX(gCalcMatrix, this->vwork[3].x * M_DTOR, MTXF_APPLY);
                    Matrix_RotateZ(gCalcMatrix, this->vwork[3].z * M_DTOR, MTXF_APPLY);

                    Matrix_MultVec3f(gCalcMatrix, &D_i5_801BA744, &sp354);

                    sp348.x = this->vwork[2].x + sp354.x;
                    sp348.y = this->vwork[2].y + sp354.y + 25.0f;
                    sp348.z = this->vwork[2].z + sp354.z;

                    sp33C.x = D_i5_801BE368[13];
                    sp33C.y = D_i5_801BE368[14];
                    sp33C.z = 0.0f;

                    sp330.x = this->vwork[3].x;
                    sp330.y = this->vwork[3].y;
                    sp330.z = this->vwork[3].z;

                    func_effect_8007EE68(OBJ_EFFECT_380, &sp348, &sp33C, &sp330, &D_i5_801BA750, 5.0f);

                    sp348.x = this->vwork[7].x - this->vwork[4].x;
                    sp348.y = this->vwork[7].y - this->vwork[4].y + 25.0f;
                    sp348.z = this->vwork[7].z - this->vwork[4].z;

                    Matrix_RotateZ(gCalcMatrix, -this->vwork[5].z * M_DTOR, MTXF_NEW);
                    Matrix_RotateX(gCalcMatrix, -this->vwork[5].x * M_DTOR, MTXF_APPLY);
                    Matrix_RotateY(gCalcMatrix, -this->vwork[5].y * M_DTOR, MTXF_APPLY);

                    Matrix_MultVec3f(gCalcMatrix, &sp348, &sp354);

                    D_i5_801BE368[14] = Math_RadToDeg(Math_Atan2F(sp354.x, sp354.z));

                    temp = sqrtf(SQ(sp354.x) + SQ(sp354.z));

                    D_i5_801BE368[13] = Math_RadToDeg(-Math_Atan2F(sp354.y, temp));

                    Matrix_RotateY(gCalcMatrix, this->vwork[5].y * M_DTOR, MTXF_NEW);
                    Matrix_RotateX(gCalcMatrix, this->vwork[5].x * M_DTOR, MTXF_APPLY);
                    Matrix_RotateZ(gCalcMatrix, this->vwork[5].z * M_DTOR, MTXF_APPLY);

                    Matrix_MultVec3f(gCalcMatrix, &D_i5_801BA744, &sp354);

                    sp348.x = this->vwork[4].x + sp354.x;
                    sp348.y = this->vwork[4].y + sp354.y + 25.0f;
                    sp348.z = this->vwork[4].z + sp354.z;

                    sp33C.x = D_i5_801BE368[13];
                    sp33C.y = D_i5_801BE368[14];
                    sp33C.z = 0.0f;

                    sp330.x = this->vwork[5].x;
                    sp330.y = this->vwork[5].y;
                    sp330.z = this->vwork[5].z;
                    func_effect_8007EE68(OBJ_EFFECT_380, &sp348, &sp33C, &sp330, &D_i5_801BA750, 10.0f);
                }
            }

            if (this->timer_0BC < (D_i5_801BE320[27] - 50)) {
                Macbeth_801A78B0(this);
            }
            if (this->timer_0BC == 0) {
                Audio_KillSfxBySourceAndId(this->sfxSource, NA_SE_EN_RNG_BEAM_SHOT);
                this->info.hitbox = SEGMENTED_TO_VIRTUAL(aMaActor207Hitbox);
                D_i5_801BE320[3] = 0;
                D_i5_801BE320[2] = 1;
                D_i5_801BE320[31] = 30;
                this->state = 4;
                D_i5_801BE320[25] = 1;
            }
            break;

        case 18:
            Macbeth_8019A198(this);
            Macbeth_801A0308(this, this->obj.pos.z, this->obj.rot.y, 0);

            Math_SmoothStepToF(&this->obj.pos.x, gPlayer[0].pos.x, 0.1f, 10.0f, 0.01f);
            Math_SmoothStepToF(&this->obj.pos.z, gPlayer[0].trueZpos - 1200.0f, 0.1f, 35.0f, 0.01f);
            Math_SmoothStepToF(&this->obj.pos.y, this->fwork[5] + 600.0f + D_i5_801BE368[3], 0.1f, 20.0f, 10.0f);

            if (D_i5_801BE368[3] < ((gPlayer[0].trueZpos - this->obj.pos.z) / 5.0f)) {
                Math_SmoothStepToF(&D_i5_801BE368[2], 15.0f, 0.2f, 2.0f, 0.01f);
                D_i5_801BE368[3] += D_i5_801BE368[2];
            } else if (((this->fwork[5] + 600.0f) + D_i5_801BE368[3]) <= this->obj.pos.y) {
                this->timer_0BC = 0;
                this->state = 19;
            }

            Macbeth_Actor207_FacePlayer(this);
            Macbeth_801A6984(this);
            break;

        case 19:
            this->vel.z = gPlayer[0].vel.z;

            Macbeth_Actor207_FacePlayer(this);

            D_i5_801BE368[4] += D_i5_801BE368[32];
            D_i5_801BE368[5] += D_i5_801BE368[33];
            D_i5_801BE368[6] += D_i5_801BE368[34];

            if (D_i5_801BE320[1] < 200) {
                D_i5_801BE320[1]++;
            }

            Math_SmoothStepToF(&D_i5_801BE368[32], this->obj.pos.x + RAND_FLOAT(500.0f), 0.2f, 20.0f, 0.01f);
            Math_SmoothStepToF(&D_i5_801BE368[33], this->obj.pos.y + RAND_FLOAT(100.0f), 0.2f, 10.0f, 0.01f);
            Math_SmoothStepToF(&D_i5_801BE368[34], this->obj.pos.y + RAND_FLOAT(500.0f), 0.2f, 20.0f, 0.01f);

            if (this->dmgType != DMG_NONE) {
                gPlayer[0].shields = 0;
            }

            if ((gGameFrameCount % 16) == 0) {
                func_effect_8007D2C8(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 10.0f);
            }

            D_i5_801BE368[9] = gPlayer[0].pos.x;

            Math_SmoothStepToF(&this->obj.pos.x, D_i5_801BE368[9], 0.2f, 35.0f, 0.01f);
            Math_SmoothStepToF(&this->obj.pos.y, gPlayer[0].pos.y, 0.3f, 15.0f, 0.01f);
            Math_SmoothStepToF(&this->obj.pos.z, gPlayer[0].trueZpos, 0.3f, 20.0f, 0.01f);
            Math_SmoothStepToF(&this->obj.rot.x, 60.0f, 0.2f, 20.0f, 0.01f);

            Macbeth_801A6984(this);
            break;

        case 20:
            Math_SmoothStepToF(&this->obj.rot.z, 0.0f, 0.1f, 20.0f, 0.01f);
            Macbeth_8019A198(this);

            this->vel.z = gActors[D_i5_801BE314].vel.z;

            D_i5_801BE320[3]++;
            if (D_i5_801BE320[3] >= 60) {
                D_i5_801BE320[3] = 0;
            }

            Macbeth_801A7A30(this);
            Macbeth_801A6984(this);

            Math_SmoothStepToF(&this->obj.rot.y, 0.0f, 0.1f, 20.0f, 0.01f);

            if (this->obj.pos.z < -135200.0f) {
                BonusText_Display(this->obj.pos.x, this->obj.pos.y + sp374, this->obj.pos.z, 50);
                if (1) {}
                gHitCount += 51;
                D_ctx_80177850 = 15;
                func_effect_8007D2C8(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 20.0f);
                Macbeth_Effect357_Spawn1(this->vwork[2].x, this->vwork[2].y, this->vwork[2].z,
                                         RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT(7.0f) + 7.0f, 2.0f, RAND_FLOAT(360.0f),
                                         RAND_FLOAT(360.0f), RAND_FLOAT(360.0f), RAND_FLOAT_CENTERED(10.0f),
                                         RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT_CENTERED(10.0f),
                                         (s32) (RAND_FLOAT(50.0f) + 70.0f), 11, 1.0f);
                gControllerRumbleFlags[gMainController] = 1;
                gControllerRumbleTimers[gMainController] = 15;
                AUDIO_PLAY_SFX(NA_SE_EN_EXPLOSION_L, this->sfxSource, 4);
                this->state = 21;
            }
            break;

        case 21:
            Object_Kill(&this->obj, this->sfxSource);
            break;

        default:
            break;
    }

    if ((this->dmgType != DMG_NONE) && (this->state >= 2)) {
        this->dmgType = DMG_NONE;
        if ((this->dmgPart == 0) && (D_i5_801BE320[9] > 0) && ((gPlayer[0].trueZpos - this->obj.pos.z) > 200.0f)) {
            AUDIO_PLAY_SFX(NA_SE_EN_DAMAGE_S, this->sfxSource, 4);

            this->iwork[7] = 15;

            D_i5_801BE320[9] -= this->damage;

            Macbeth_Effect357_Spawn1(this->obj.pos.x, this->obj.pos.y + 80, this->obj.pos.z + 50.0f,
                                     RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT(5.0f), RAND_FLOAT_CENTERED(3.0f),
                                     RAND_FLOAT(360.0f), RAND_FLOAT(360.0f), RAND_FLOAT(360.0f),
                                     RAND_FLOAT_CENTERED(30.0f), RAND_FLOAT_CENTERED(30.0f), RAND_FLOAT_CENTERED(30.0f),
                                     (s32) (RAND_FLOAT(50.0f) + 70.0f), 3, RAND_FLOAT(1.0f));

            if (D_i5_801BE320[9] <= 0) {
                AUDIO_PLAY_SFX(NA_SE_EN_EXPLOSION_M, this->sfxSource, 4);
                func_effect_8007D2C8(this->obj.pos.x, this->obj.pos.y + 80.0f, this->obj.pos.z + 50.0f, 5.0f);
                for (i = 0; i < 2; i++) {
                    Macbeth_Effect357_Spawn1(
                        this->obj.pos.x, this->obj.pos.y + 80.0f, this->obj.pos.z + 50.0f, RAND_FLOAT_CENTERED(10.0f),
                        RAND_FLOAT(5.0f), RAND_FLOAT_CENTERED(3.0f), RAND_FLOAT(360.0f), RAND_FLOAT(360.0f),
                        RAND_FLOAT(360.0f), RAND_FLOAT_CENTERED(30.0f), RAND_FLOAT_CENTERED(30.0f),
                        RAND_FLOAT_CENTERED(30.f), (s32) (RAND_FLOAT(50.0f) + 70.0f), 3, RAND_FLOAT(1.0f));
                }
                Macbeth_Effect357_Spawn1(this->obj.pos.x, this->obj.pos.y + 80.0f, this->obj.pos.z + 50.0f,
                                         RAND_FLOAT_CENTERED(3.0f), RAND_FLOAT(15.0f), -2.0f, RAND_FLOAT(360.0f),
                                         RAND_FLOAT(360.0f), RAND_FLOAT(360.0f), RAND_FLOAT_CENTERED(10.0f),
                                         RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT_CENTERED(10.0f),
                                         (s32) (RAND_FLOAT(50.0f) + 70.0f), 8, 1.0f);
            }
        } else if ((this->dmgPart == 1) && (D_i5_801BE320[10] > 0) &&
                   ((gPlayer[0].trueZpos - this->obj.pos.z) > 200.0f)) {
            AUDIO_PLAY_SFX(NA_SE_EN_DAMAGE_S, this->sfxSource, 4);

            this->iwork[8] = 16;

            D_i5_801BE320[10] -= this->damage;

            Macbeth_Effect357_Spawn1(this->obj.pos.x, this->obj.pos.y - 30.0f, this->obj.pos.z,
                                     RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT(7.0f) + 7.0f, RAND_FLOAT_CENTERED(3.0f),
                                     RAND_FLOAT(360.0f), RAND_FLOAT(360.0f), RAND_FLOAT(360.0f),
                                     RAND_FLOAT_CENTERED(30.0f), RAND_FLOAT_CENTERED(30.0f), RAND_FLOAT_CENTERED(30.0f),
                                     (s32) (RAND_FLOAT(50.0f) + 70.0f), 3, RAND_FLOAT(1.0f));

            if (D_i5_801BE320[10] <= 0) {
                AUDIO_PLAY_SFX(NA_SE_EN_EXPLOSION_M, this->sfxSource, 4);
                func_effect_8007D2C8(this->obj.pos.x, this->obj.pos.y - 30.0f, this->obj.pos.z, 6.0f);

                for (i = 0; i < 10; i++) {
                    Macbeth_Effect357_Spawn1(
                        this->obj.pos.x, this->obj.pos.y - 30.0f, this->obj.pos.z, RAND_FLOAT_CENTERED(10.0f),
                        RAND_FLOAT(7.0f) + 7.0f, RAND_FLOAT_CENTERED(3.0f), RAND_FLOAT(360.0f), RAND_FLOAT(360.0f),
                        RAND_FLOAT(360.0f), RAND_FLOAT_CENTERED(30.0f), RAND_FLOAT_CENTERED(30.0f),
                        RAND_FLOAT_CENTERED(30.0f), (s32) (RAND_FLOAT(50.0f) + 70.0f), 3, RAND_FLOAT(1.0f));
                }
                Macbeth_Effect357_Spawn1(this->obj.pos.x, this->obj.pos.y - 30.0f, this->obj.pos.z + 50.0f,
                                         RAND_FLOAT_CENTERED(3.0f), RAND_FLOAT(15.0f), -2.0f, RAND_FLOAT(360.0f),
                                         RAND_FLOAT(360.0f), RAND_FLOAT(360.0f), RAND_FLOAT_CENTERED(10.0f),
                                         RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT_CENTERED(10.0f),
                                         (s32) (RAND_FLOAT(50.0f) + 70.0f), 9, 1.0f);
            }
        } else {
            AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
        }
    }

    if (D_i5_801BE320[4] != 0) {
        if ((this->state != 8) && (this->state != 10) && (this->state != 9)) {
            D_i5_801BE320[5] = 1;
            D_i5_801BE320[7] = 1;
            D_i5_801BE320[6] = 1;
            D_i5_801BE320[8] = 1;
            D_i5_801BE320[3] = 0;
            D_i5_801BE320[2] = 3;
            D_i5_801BE320[31] = 30;
            D_i5_801BE368[12] = 0.0f;
            D_i5_801BE368[13] = 0.0f;
            this->state = 8;
        }
    }

    if ((D_i5_801BE320[16] != 0) && (gPlayer[0].state != PLAYERSTATE_LEVEL_COMPLETE)) {
        if (gBossFrameCount == 0) {
            Radio_PlayMessage(gMsg_ID_2225, RCID_SLIPPY);
        } else if (gBossFrameCount > 155) {
            gShowBossHealth = true;
            gBossHealthBar = (s32) ((D_i5_801BE320[29] / 250.f) * 85.0f);
            gBossHealthBar += (s32) ((D_i5_801BE320[9] / 200.f) * 85.0f);
            gBossHealthBar += (s32) ((D_i5_801BE320[10] / 250.f) * 85.0f);
        }
        gBossFrameCount++;
    }

    if (this->iwork[7] > 0) {
        this->iwork[7]--;
    }

    if (this->iwork[8] > 0) {
        this->iwork[8]--;
    }

    if (this->iwork[9] > 0) {
        this->iwork[9]--;
    }

    D_i5_801BE368[14] = this->vwork[0].x;
    D_i5_801BE368[15] = this->vwork[0].y;
    D_i5_801BE368[16] = this->vwork[0].z;
    D_i5_801BE368[24] = this->vwork[2].x;
    D_i5_801BE368[25] = this->vwork[2].y;
    D_i5_801BE368[26] = this->vwork[2].z;
    D_i5_801BE368[27] = this->vwork[4].x;
    D_i5_801BE368[28] = this->vwork[4].y;
    D_i5_801BE368[29] = this->vwork[4].z;
    D_i5_801BE368[19] = this->vel.z;
    D_i5_801BE368[30] = RAND_FLOAT(1.0f);
    D_i5_801BE368[31] = RAND_FLOAT(1.0f);

    if (D_i5_801BE368[30] < 0.5f) {
        D_i5_801BE368[30] = 0.6f;
    }
    if (D_i5_801BE368[31] < 0.8f) {
        D_i5_801BE368[31] = 0.8f;
    }

    Math_SmoothStepToF(&D_i5_801BE368[20], 0.0f, 0.4f, 25.0f, 0.1f);
    Math_SmoothStepToF(&D_i5_801BE368[21], 0.0f, 0.4f, 20.0f, 0.1f);
    Math_SmoothStepToF(&D_i5_801BE368[22], 0.0f, 0.2f, 20.0f, 0.1f);

    if ((D_i5_801BE368[20] <= 1.0f) && (D_i5_801BE368[21] <= 1.0f)) {
        D_i5_801BE368[20] = 255.0f;
        D_i5_801BE368[21] = 160.0f;
        D_i5_801BE368[22] = 16.0f;
    }

    if ((gPlayer[0].state == PLAYERSTATE_LEVEL_COMPLETE) && (this->state < 20)) {
        D_i5_801BE320[3] = 0;
        D_i5_801BE320[2] = 1;
        D_i5_801BE320[31] = 30;
        this->state = 20;
    }

    switch (D_i5_801BE320[2]) {
        case 1:
            temp_a3 = Animation_GetFrameData(&D_MA_600CD18, D_i5_801BE320[3], spD4);
            Math_SmoothStepToVec3fArray(spD4, D_i5_801BE430, 1, temp_a3, 0.2f, 100.0f, 0.01f);
            break;

        case 2:
            temp_a3 = Animation_GetFrameData(&D_MA_601D188, D_i5_801BE320[3], spD4);
            Math_SmoothStepToVec3fArray(spD4, D_i5_801BE430, 1, temp_a3, 0.15f, 100.0f, 0.01f);
            break;

        case 3:
            temp_a3 = Animation_GetFrameData(&D_MA_6017714, D_i5_801BE320[3], spD4);
            if (D_i5_801BE320[31] != 0) {
                Math_SmoothStepToVec3fArray(spD4, D_i5_801BE430, 1, temp_a3, 0.1f, 100.0f, 0.01f);
            } else {
                Math_SmoothStepToVec3fArray(spD4, D_i5_801BE430, 1, temp_a3, 1.0f, 100.0f, 0.01f);
            }
            break;

        case 4:
            temp_a3 = Animation_GetFrameData(&D_MA_6016B2C, D_i5_801BE320[3], spD4);
            Math_SmoothStepToVec3fArray(spD4, D_i5_801BE430, 1, temp_a3, 0.2f, 50.0f, 0.01f);
            break;

        case 5:
            temp_a3 = Animation_GetFrameData(&D_MA_60163F0, D_i5_801BE320[3], spD4);
            Math_SmoothStepToVec3fArray(spD4, D_i5_801BE430, 1, temp_a3, 0.2f, 100.0f, 0.01f);
            break;

        case 6:
            temp_a3 = Animation_GetFrameData(&D_MA_6016040, D_i5_801BE320[3], spD4);
            Math_SmoothStepToVec3fArray(spD4, D_i5_801BE430, 1, temp_a3, 0.1f, 50.0f, 0.01f);
            break;

        case 7:
            temp_a3 = Animation_GetFrameData(&D_MA_6015C24, D_i5_801BE320[3], spD4);
            Math_SmoothStepToVec3fArray(spD4, D_i5_801BE430, 1, temp_a3, 0.1f, 50.0f, 0.01f);
            break;
    }

    if (D_i5_801BE320[31] != 0) {
        D_i5_801BE320[31]--;
    }
}

bool Macbeth_Actor207_OverrideLimbDraw(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    Actor* this = (Actor*) thisx;
    s16 sp62;

    RCP_SetupDL(&gMasterDisp, SETUPDL_29);
    gSPClearGeometryMode(gMasterDisp++, G_TEXTURE_GEN);
    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);

    switch (limbIndex) {
        case 2:
        case 3:
        case 4:
        case 25:
        case 26:
        case 27:
            if (this->state == 9) {
                *dList = NULL;
                return false;
            }
        default:
            break;
    }

    switch (limbIndex) {
        case 1:
        case 4:
        case 7:
        case 10:
        case 11:
        case 12:
        case 13:
        case 17:
        case 19:
        case 20:
        case 26:
        case 27:
        case 29:
        case 30:
            gSPTexture(gMasterDisp++, 3000, 3000, 0, G_TX_RENDERTILE, G_ON);
            gSPSetGeometryMode(gMasterDisp++, G_TEXTURE_GEN);
            break;
        case 8:
            RCP_SetupDL(&gMasterDisp, SETUPDL_34);
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, D_i5_801BE368[20], D_i5_801BE368[21], D_i5_801BE368[22], 255);
            break;
        case 2:
        case 3:
        case 5:
        case 6:
            if (limbIndex == 2) {
                sp62 = 5;
            } else if (limbIndex == 3) {
                sp62 = 6;
            } else if (limbIndex == 5) {
                sp62 = 7;
            } else if (limbIndex == 6) {
                sp62 = 8;
            }
            if (D_i5_801BE320[sp62] == 0) {
                *dList = NULL;
            } else {
                RCP_SetupDL_49();
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 180, 200, 255, 255);
                gDPSetEnvColor(gMasterDisp++, 16, 32, 255, 255);
                gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                Matrix_Push(&gCalcMatrix);
                Matrix_Mult(gGfxMatrix, gCalcMatrix, MTXF_APPLY);
                Matrix_Push(&gGfxMatrix);
                Matrix_Scale(gGfxMatrix, D_i5_801BE368[31], D_i5_801BE368[30], D_i5_801BE368[31], MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, *dList);
                Matrix_Pop(&gGfxMatrix);
                Matrix_Pop(&gCalcMatrix);
                return true;
            }
            break;

        default:
            break;
    }

    switch (limbIndex) {
        case 14:
            if ((this->iwork[7] % 2) != 0) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_28);
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
            }
            if (D_i5_801BE320[9] <= 0) {
                *dList = NULL;
            }
            break;

        case 9:
        case 10:
        case 11:
        case 12:
        case 18:
        case 19:
        case 20:
            if ((this->iwork[8] % 2) != 0) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_28);
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
            }
            if (D_i5_801BE320[10] <= 0) {
                *dList = NULL;
            }
            break;

        default:
            break;
    }

    if ((this->iwork[9] % 2) != 0) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_28);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
    }
    return false;
}

void Macbeth_Actor207_PostLimbDraw(s32 limbIndex, Vec3f* rot, void* thisx) {
    Vec3f sp2C = { 0.0f, 0.0f, 0.0f };
    Actor207* this = (Actor207*) thisx;

    switch (limbIndex) {
        case 14:
            Matrix_MultVec3f(gCalcMatrix, &sp2C, &this->vwork[0]);
            Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[1]);
            break;
        case 4:
            Matrix_MultVec3f(gCalcMatrix, &sp2C, &this->vwork[2]);
            Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[3]);
            break;
        case 7:
            Matrix_MultVec3f(gCalcMatrix, &sp2C, &this->vwork[4]);
            Matrix_GetYRPAngles(gCalcMatrix, &this->vwork[5]);
            break;
    }
}

void Macbeth_Actor207_Draw(Actor207* this) {
    if (gPlayer[0].state == PLAYERSTATE_ACTIVE) {
        if (((gPlayer[0].trueZpos - this->obj.pos.z) > 7000.0f) ||
            ((gPlayer[0].trueZpos - this->obj.pos.z) < -1000.0f)) {
            return;
        }
    } else {
        if (((gPlayer[0].trueZpos - this->obj.pos.z) > 7000.0f) ||
            ((gPlayer[0].trueZpos - this->obj.pos.z) < -5000.0f)) {
            return;
        }
    }

    if (D_i5_801BE320[2] == 0) {
        Matrix_Translate(gCalcMatrix, this->fwork[25], 0.0f, 0.0f, MTXF_APPLY);
        Matrix_RotateY(gCalcMatrix, this->fwork[26] * M_DTOR, MTXF_APPLY);
        Matrix_RotateX(gCalcMatrix, this->fwork[29] * M_DTOR, MTXF_APPLY);
        Animation_GetFrameData(&D_MA_601EA28, D_i5_801BE320[3], D_i5_801BE430);
    }
    Animation_DrawSkeleton(3, D_MA_600D1E4, D_i5_801BE430, Macbeth_Actor207_OverrideLimbDraw,
                           Macbeth_Actor207_PostLimbDraw, this, gCalcMatrix);
}

void Macbeth_801AC42C(s32 arg0) {
}

void Macbeth_MaTrainCar1_Update(MaTrainCar1* this) {
    switch (this->state) {
        case 0:
            Macbeth_8019A198(this);
            Macbeth_801A015C(this);
            Macbeth_8019A728(this);
            if (this->iwork[1] != 0) {
                Radio_PlayMessage(gMsg_ID_17420, RCID_BOSS_MACBETH);
                AUDIO_PLAY_SFX(NA_SE_EN_MABOSS_HATCH, this->sfxSource, 4);
                this->info.hitbox = SEGMENTED_TO_VIRTUAL(D_MA_6035A94);
                this->state++;
            }
            Macbeth_8019A830(this);
            break;

        case 1:
            Macbeth_8019A198(this);
            Macbeth_801A015C(this);
            Math_SmoothStepToF(&D_i5_801BE368[8], 160.0f, 0.1f, 3.0f, 0.01f);
            Macbeth_8019A830(this);
            break;
    }

    if (this->dmgType != DMG_NONE) {
        this->dmgType = DMG_NONE;
        AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, this->sfxSource, 4);
    }
}

bool Macbeth_MaTrainCar1_OverrideLimbDraw(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_29);
    gSPClearGeometryMode(gMasterDisp++, G_TEXTURE_GEN);

    if ((limbIndex == 1) || (limbIndex == 3)) {
        gSPTexture(gMasterDisp++, 3000, 3000, 0, G_TX_RENDERTILE, G_ON);
        gSPSetGeometryMode(gMasterDisp++, G_TEXTURE_GEN);
    }
    if ((limbIndex == 1) || (limbIndex == 6)) {
        pos->z -= D_i5_801BE368[8];
    } else if ((limbIndex == 3) || (limbIndex == 7)) {
        pos->z += D_i5_801BE368[8];
    }
    return false;
}

// unused
void Macbeth_801AC6B4(ActorCutscene* this) {
    Actor_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_ACTOR_CUTSCENE;
    this->obj.pos.x = 0.0f;
    this->obj.pos.y = 3000.0f;
    this->obj.pos.z = 0.0f;
    this->obj.rot.y = 180.0f;
    Object_SetInfo(&this->info, this->obj.id);
    AUDIO_PLAY_SFX(NA_SE_GREATFOX_ENGINE, this->sfxSource, 0);
    this->animFrame = ACTOR_CS_GREAT_FOX;
}

f32 D_i5_801BA768 = 0.0f;

void Macbeth_LevelStart(Player* player) {
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    ObjectInit* objInit;
    s32 i;
    f32 zeroVar = 0.0f;

    sp4C = 0.0f;
    sp48 = 0.0f;
    sp44 = 0.0f;

    Player_UpdatePath(player);

    switch (player->csState) {
        case 0:
            gLevelObjects = SEGMENTED_TO_VIRTUAL(D_MA_6035678);

            for (i = 0, objInit = gLevelObjects; objInit->id != OBJ_INVALID; i++, objInit++) {
                Object_Load(objInit, 4000.0f, -4000.0f, 4000.0f, -4000.0f);
            }

            gLevelObjects = SEGMENTED_TO_VIRTUAL(gLevelObjectInits[gCurrentLevel]);

            for (i = 0, objInit = gLevelObjects; i < 40; i++, objInit++) {
                Object_Load(objInit, 4000.0f, -4000.0f, 4000.0f, -4000.0f);
            }

            gFillScreenRed = gFillScreenGreen = gFillScreenBlue = gFillScreenAlpha = 255;

            player->zPath -= 800.0f;
            player->csState = 1;

            D_i5_801BE24C = 8.0f;
            D_i5_801BA768 = 0.0f;
            break;

        case 1:
            gCsFrameCount = 0;
            player->gravity = 0.0f;
            player->pos.x = 0.0f;
            player->pos.y = -3.0f;
            player->vel.z = -15.0f;
            player->cam.eye.x = gCsCamEyeX = -518.0f;
            player->cam.eye.y = gCsCamEyeY = 3882.5f;
            player->cam.eye.z = gCsCamEyeZ = 200.0f;
            player->cam.at.x = gCsCamAtX = -910.0f;
            player->cam.at.y = gCsCamAtY = 42.0f;
            player->cam.at.z = gCsCamAtZ = -800.0f;
            player->hideShadow = true;
            player->csState = 2;
            gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
            gFillScreenAlpha = 255;
            Macbeth_EffectClouds_Spawn();
            /* fallthrough */
        case 2:
            if (gCsFrameCount < 30) {
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
                gFillScreenAlpha = 255;
            }
            if ((gCsFrameCount < 60) && ((gCsFrameCount % 16U) == 0)) {
                Macbeth_EffectClouds_Spawn();
            } else if ((gCsFrameCount < 100) && ((gCsFrameCount % 32) == 0)) {
                Macbeth_EffectClouds_Spawn();
            }
            if (gCsFrameCount > 50) {
                gCsCamEyeX = zeroVar;
                gCsCamEyeY = 92.5f;
                gCsCamEyeZ = 200.0f;
                gCsCamAtX = zeroVar;
                gCsCamAtY = 42.0f;
                gCsCamAtZ = -800.0f;

                D_ctx_80177A48[0] = 0.1f;
                D_ctx_80177A48[1] = 0.1f;
                D_ctx_80177A48[2] = 0.1f;

                if (gCsFrameCount < 80) {
                    sp4C = 5.0f;
                    sp48 = 8.0f;
                    sp44 = 30.0f;
                } else {
                    sp4C = 5.0f;
                    if (D_i5_801BE24C < 35.0f) {
                        D_i5_801BE24C += 0.2f;
                    }
                    sp48 = zeroVar + D_i5_801BE24C;
                    sp44 = 30.0f;
                }
                if (gCsFrameCount == 260) {
                    player->csState = 3;
                    player->csTimer = 10;
                }
            }
            break;

        case 3:
            AUDIO_PLAY_BGM(NA_BGM_STAGE_MA);
            gLevelStartStatusScreenTimer = 50;
            player->state = PLAYERSTATE_ACTIVE;
            player->csState = player->csTimer = player->csEventTimer = player->hideShadow = 0;
            player->gravity = 3.0f;
            player->unk_014 = 0.0f;
            D_ctx_8017782C = true;
            Play_InitEnvironment();
            D_ctx_8017782C = false;
            gObjectLoadIndex = 40;
            player->csState = 4;
            break;

        case 4:

        default:
            break;
    }
    player->trueZpos = player->pos.z += player->vel.z;
    Math_SmoothStepToF(&player->cam.eye.x, gCsCamEyeX, D_ctx_80177A48[0], sp4C, 0);
    Math_SmoothStepToF(&player->cam.eye.y, gCsCamEyeY, D_ctx_80177A48[1], sp48, 0);
    Math_SmoothStepToF(&player->cam.eye.z, gCsCamEyeZ, D_ctx_80177A48[2], sp44, 0);
    Math_SmoothStepToF(&player->cam.at.x, gCsCamAtX, D_ctx_80177A48[0], sp4C, 0);
    Math_SmoothStepToF(&player->cam.at.y, gCsCamAtY, D_ctx_80177A48[1], sp48, 0);
    Math_SmoothStepToF(&player->cam.at.z, gCsCamAtZ, D_ctx_80177A48[2], sp44, 0);

    player->pathHeight = 0.0f;
    player->rockPhase += player->vel.z * 5.0f;
    player->rockAngle = SIN_DEG(player->rockPhase) * 0.7f;

    Lib_Texture_Scroll(D_landmaster_3002E80, 32, 32, 0);

    if ((gCsFrameCount > 150) && ((-player->trueZpos - player->zPath) > 200.0f)) {
        if (D_i5_801BA768 < 11.5f) {
            D_i5_801BA768 += 0.2f;
        }
        player->zPath += D_i5_801BA768;
    }
}

void Macbeth_EffectClouds_Setup(EffectClouds* this) {
    Effect_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.pos.x = gPlayer[0].cam.eye.x + RAND_FLOAT_CENTERED(600.0f);
    this->obj.pos.y = gPlayer[0].cam.eye.y - 1000.0f;
    this->obj.pos.z = gPlayer[0].trueZpos - 2000.0f;
    this->obj.id = OBJ_EFFECT_CLOUDS;
    this->timer_50 = 80;
    this->unk_46 = 144;
    this->vel.x = 10.0f;
    this->vel.z = 40.0f;
    this->vel.y = 8.0f;
    this->scale2 = RAND_FLOAT(15.0f) + 10.0f;

    if (Rand_ZeroOne() < 0.5f) {
        this->obj.rot.z = 180.0f;
    }
    Object_SetInfo(&this->info, this->obj.id);
}

void Macbeth_EffectClouds_Spawn(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Macbeth_EffectClouds_Setup(&gEffects[i]);
            break;
        }
    }
}

void Macbeth_801ACFBC(void) {
    ObjectInit* objInit;

    gLevelObjects = SEGMENTED_TO_VIRTUAL(D_MA_60357CC);

    for (objInit = gLevelObjects; objInit->id != OBJ_INVALID; objInit++) {
        Object_Load(objInit, 4000.0f, -4000.0f, 4000.0f, -4000.0f);
    }
}

void Macbeth_801AD080(void) {
    ObjectInit* objInit;

    gLevelObjects = SEGMENTED_TO_VIRTUAL(D_MA_6035920);

    for (objInit = gLevelObjects; objInit->id != OBJ_INVALID; objInit++) {
        Object_Load(objInit, 4000.0f, -4000.0f, 4000.0f, -4000.0f);
    }
}

void Macbeth_801AD144(PlayerShot* shot) {
    s32 i;
    s32 j;
    Actor* actor;
    f32 temp_fs2;
    Vec3f test;
    f32* var_s1;
    Vec3f sp8C;
    Vec3f sp80;
    s32 temp_ft3;
    s32 temp_s6;

    temp_fs2 = shot->scale * 40.0f;
    actor = &gActors[0];

    for (i = 0; i < ARRAY_COUNT(gActors); i++, actor++) {
        if ((actor->obj.status == OBJ_ACTIVE) && (actor->timer_0C2 == 0) &&
            (actor->obj.id >= OBJ_ACTOR_MA_LOCOMOTIVE) && (actor->obj.id <= OBJ_ACTOR_MA_TRAIN_CAR_7)) {
            temp_s6 = gGameFrameCount % 8U;
            var_s1 = &actor->info.hitbox[0];
            temp_ft3 = var_s1[0];
            var_s1++;

            if (temp_ft3 != 0) {
                for (j = 0; j < temp_ft3; j++, var_s1 += 6) {
                    if (var_s1[0] == 200000.0f) {
                        Matrix_RotateZ(gCalcMatrix, -var_s1[3] * M_DTOR, MTXF_NEW);
                        Matrix_RotateX(gCalcMatrix, -var_s1[1] * M_DTOR, MTXF_APPLY);
                        Matrix_RotateY(gCalcMatrix, -var_s1[2] * M_DTOR, MTXF_APPLY);
                        Matrix_RotateZ(gCalcMatrix, -actor->obj.rot.z * M_DTOR, MTXF_APPLY);
                        Matrix_RotateX(gCalcMatrix, -actor->obj.rot.x * M_DTOR, MTXF_APPLY);
                        Matrix_RotateY(gCalcMatrix, -actor->obj.rot.y * M_DTOR, MTXF_APPLY);
                        var_s1 += 4;
                    } else {
                        Matrix_RotateZ(gCalcMatrix, -actor->obj.rot.z * M_DTOR, MTXF_NEW);
                        Matrix_RotateX(gCalcMatrix, -actor->obj.rot.x * M_DTOR, MTXF_APPLY);
                        Matrix_RotateY(gCalcMatrix, -actor->obj.rot.y * M_DTOR, MTXF_APPLY);
                    }

                    if ((j == temp_s6) && (var_s1[1] > -100.0f) && (var_s1[3] > -100.0f)) {
                        sp8C.x = shot->obj.pos.x - actor->obj.pos.x;
                        sp8C.y = shot->obj.pos.y - actor->obj.pos.y;
                        sp8C.z = shot->obj.pos.z - actor->obj.pos.z;
                        Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp8C, &sp80);

                        test.x = (var_s1[4] + actor->obj.pos.x) - (actor->obj.pos.x + sp80.x);
                        test.y = (var_s1[2] + actor->obj.pos.y) - (actor->obj.pos.y + sp80.y);
                        test.z = (var_s1[0] + actor->obj.pos.z) - (actor->obj.pos.z + sp80.z);

                        if ((gLevelMode == LEVELMODE_ON_RAILS) && (test.z < 0.0f)) {
                            test.z *= 0.6f;
                        }

                        if (VEC3F_MAG(&test) < temp_fs2) {
                            actor->dmgPart = j;
                            actor->dmgType = -1;
                            if ((gPlayer[0].trueZpos - actor->obj.pos.z) < 5000.0f) {
                                actor->damage = 20;
                            } else {
                                actor->damage = 1;
                            }
                            if (actor->obj.id == OBJ_ACTOR_207) {
                                actor->damage = 4;
                            }
                        }
                    }
                }
            }
        }
    }
}

void Macbeth_Effect357_Setup(Effect357* this, f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 xRot,
                             f32 yRot, f32 zRot, f32 argA, f32 argB, f32 argC, s16 argD, s16 argE, f32 scale2) {
    Effect_Initialize(this);
    this->obj.status = OBJ_ACTIVE;
    this->obj.id = OBJ_EFFECT_357;
    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;
    this->obj.rot.x = xRot;
    this->obj.rot.y = yRot;
    this->obj.rot.z = zRot;
    this->vel.x = xVel;
    this->vel.y = yVel;
    this->vel.z = zVel;
    this->scale2 = scale2;
    this->timer_50 = argD;
    this->unk_60.x = argA;
    this->unk_60.y = argB;
    this->unk_60.z = argC;
    this->unk_44 = argE;
    Object_SetInfo(&this->info, this->obj.id);
}

void Macbeth_Effect357_Spawn1(f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 xRot, f32 yRot, f32 zRot,
                              f32 arg9, f32 argA, f32 argB, s16 argC, s16 argD, f32 scale2) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Macbeth_Effect357_Setup(&gEffects[i], xPos, yPos, zPos, xVel, yVel, zVel, xRot, yRot, zRot, arg9, argA,
                                    argB, argC, argD, scale2);
            break;
        }
    }
}

void Macbeth_801AD6E8(void) {
}

void Macbeth_MaBombDrop_Update(MaBombDrop* this) {
    Vec3f sp4C = { 0.0f, -10.0f, 0.0f };

    if ((gPlayer[0].trueZpos - this->obj.pos.z) < -500.0f) {
        Object_Kill(&this->obj, this->sfxSource);
    }

    switch (this->state) {
        case 0:
            if ((this->timer_0BC == 0) &&
                ((this->vel.y -= 0.5f, (Object_CheckCollision(this->index, &this->obj.pos, &sp4C, 1) != 0)) ||
                 (this->obj.pos.y < (gGroundHeight + 10.0f)) || (this->iwork[0] != 0))) {
                this->vel.x = 0.0f;
                this->vel.y = 0.0f;
                this->vel.z = 0.0f;

                if (this->obj.pos.y < (gGroundHeight + 10.0f)) {
                    this->obj.pos.y = gGroundHeight;
                }

                this->state = 1;
                this->timer_0BC = 200;
                this->work_046 = 192;
                this->scale = 2.5f;
                this->fwork[0] = 2.5f;

                AUDIO_PLAY_SFX(NA_SE_EN_EXPLOSION_M, this->sfxSource, 4);

                func_effect_8007D0E0(this->obj.pos.x, this->obj.pos.y + 30.0f, this->obj.pos.z, 7.0f);

                Effect386_Spawn1(this->obj.pos.x, this->obj.pos.y + 30.0f, this->obj.pos.z, 0.0f, 0.0f, 0.0f, 4.0f, 5);

                if (this->obj.pos.y < (gGroundHeight + 10.0f)) {
                    PlayerShot_SpawnEffect344(this->obj.pos.x, 3.0f, this->obj.pos.z, this->obj.pos.x, this->obj.pos.z,
                                              0.0f, 0.0f, 90.0f, 5.0f, 0, 0);
                }
                gControllerRumbleFlags[gMainController] = 1;
                gControllerRumbleTimers[gMainController] = 10;
            }
            break;

        case 1:
            this->scale += ((20.0f - this->scale) * 0.1f);
            if (this->scale > 19.0f) {
                this->fwork[0] -= 0.3f;
                this->work_046 -= 20;
                if (this->work_046 < 0) {
                    Object_Kill(&this->obj, this->sfxSource);
                }
            }

            this->obj.rot.y = 180.0f - this->obj.rot.y;

            if ((fabsf(gPlayer[0].trueZpos - this->obj.pos.z) < 40.0f) &&
                (fabsf(gPlayer[0].pos.x - this->obj.pos.x) < 80.0f)) {
                if ((gPlayer[0].pos.y - this->obj.pos.y > -5.0f) &&
                    (gPlayer[0].pos.y - this->obj.pos.y < (this->scale * 35.0f)) && (gPlayer[0].mercyTimer == 0)) {
                    Player_ApplyDamage(&gPlayer[0], 0, this->info.damage);
                }
            }
            break;
    }
}

void Macbeth_MaBombDrop_Draw(MaBombDrop* this) {
    switch (this->state) {
        case 0:
            Graphics_SetScaleMtx(this->scale);
            RCP_SetupDL_60(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
            gSPDisplayList(gMasterDisp++, D_ENMY_PLANET_4008CE0);
            RCP_SetupDL(&gMasterDisp, SETUPDL_64);
            break;

        case 1:
            Matrix_Scale(gGfxMatrix, this->fwork[0], this->scale, 2.5f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            RCP_SetupDL_40();
            gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
            gSPDisplayList(gMasterDisp++, D_ENMY_PLANET_4008F70);
            RCP_SetupDL(&gMasterDisp, SETUPDL_64);
            break;
    }
}

void Macbeth_MaBombDrop_Setup(MaBombDrop* this, f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel) {
    Actor_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_ACTOR_MA_BOMBDROP;

    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;

    if (xVel == 999.9f) {
        this->iwork[0] = 1;
        this->vel.x = 0.0f;
    } else {
        this->vel.x = xVel;
        this->iwork[0] = 0;
    }

    this->vel.y = yVel;
    this->vel.z = zVel;
    this->timer_0BC = 0;
    Object_SetInfo(&this->info, this->obj.id);
    AUDIO_PLAY_SFX(NA_SE_EN_FALLING_DOWN, this->sfxSource, 4);
}

void Macbeth_MaBombDrop_Spawn(f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel) {
    s32 i;

    for (i = ARRAY_COUNT(gActors) - 1; i >= 0; i--) {
        if (gActors[i].obj.status == OBJ_FREE) {
            Macbeth_MaBombDrop_Setup(&gActors[i], xPos, yPos, zPos, xVel, yVel, zVel);
            break;
        }
    }
}

void Macbeth_MaSpear_Update(MaSpear* this) {
    Vec3f sp3C = { 0.0f, -10.0f, 0.0f };
    s32 var_v0;

    if ((gPlayer[0].trueZpos - this->obj.pos.z) < -500.0f) {
        Object_Kill(&this->obj, this->sfxSource);
    }

    switch (this->state) {
        case 0:
            if (this->timer_0BC == 0) {
                this->vel.y -= 2.5f;
                if (this->vel.y < 20.0f) {
                    switch (D_i5_801BE320[18]) {
                        case 0:
                        case 1:
                            var_v0 = 1;
                            break;
                        case 2:
                            var_v0 = 2;
                            break;
                        case 3:
                            var_v0 = 3;
                            break;
                        default:
                            var_v0 = 5;
                            break;
                    }

                    Math_SmoothStepToF(&this->obj.pos.x,
                                       gPlayer[0].pos.x + D_i5_801BA570[this->iwork[2]][this->iwork[1]] / var_v0, 0.2f,
                                       30.0f, 0.01f);
                    Math_SmoothStepToF(&this->obj.pos.z,
                                       gPlayer[0].trueZpos - D_i5_801BA638[this->iwork[2]][this->iwork[1]] / var_v0,
                                       0.2f, 40.0f, 0.01f);
                    Math_SmoothStepToF(&this->obj.rot.z, RAND_FLOAT_CENTERED(15.0f), 0.1f, 10.0f, 0.01f);

                    if (this->fwork[2] < 1.0f) {
                        this->fwork[2] += 0.02;
                    }
                }
            }

            if ((Object_CheckCollision(this->index, &this->obj.pos, &sp3C, 1) != 0) ||
                (this->obj.pos.y < (gGroundHeight + 200.0f))) {
                AUDIO_PLAY_SFX(NA_SE_OB_SPEAR_STICK, this->sfxSource, 4);
                gControllerRumbleFlags[gMainController] = 1;
                gControllerRumbleTimers[gMainController] = 5;
                this->vel.x = 0.0f;
                this->vel.y = 0.0f;
                this->vel.z = 0.0f;
                if (this->obj.pos.y < gGroundHeight + 200.0f) {
                    this->obj.pos.y = gGroundHeight + 200.0f;
                }
                this->state = 1;
            }

            if (this->obj.pos.y < (gGroundHeight + 800.0f)) {
                if (this->iwork[0] > 10) {
                    this->iwork[0] -= 10;
                } else if (this->iwork[0] > 0) {
                    this->iwork[0] -= 1;
                }
            }
            break;

        case 1:
            if (this->iwork[0] > 10) {
                this->iwork[0] -= 10;
            } else if (this->iwork[0] > 0) {
                this->iwork[0] -= 1;
            }

            if (this->dmgType != DMG_NONE) {
                this->dmgType = DMG_NONE;
                this->iwork[7] = 15;
                this->health -= this->damage;

                if (this->health <= 0) {
                    Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_EXPLOSION_S);
                    func_effect_8007D2C8(this->obj.pos.x + RAND_FLOAT_CENTERED(20.0f), this->obj.pos.y - 200.0f,
                                         this->obj.pos.z, 8.0f);
                    func_effect_8007D2C8(this->obj.pos.x + RAND_FLOAT_CENTERED(20.0f), this->obj.pos.y, this->obj.pos.z,
                                         8.0f);
                    func_effect_8007D2C8(this->obj.pos.x + RAND_FLOAT_CENTERED(20.0f), this->obj.pos.y + 200.0f,
                                         this->obj.pos.z, 7.0f);
                    func_effect_8007D2C8(this->obj.pos.x + RAND_FLOAT_CENTERED(20.0f), this->obj.pos.y + 400.0f,
                                         this->obj.pos.z, 7.0f);
                    Object_Kill(&this->obj, this->sfxSource);
                } else {
                    AUDIO_PLAY_SFX(NA_SE_EN_DAMAGE_S, this->sfxSource, 4);
                }
            }
            break;
    }
    this->dmgType = DMG_NONE;
}

Vec3f D_i5_801BA784[8] = {
    { 40.0f, 10.0f, 30.0f },  { 41.0f, 10.0f, 10.0f },  { 43.0f, 10.0f, -10.0f },  { 45.0f, 10.0f, -30.0f },
    { -40.0f, 10.0f, 30.0f }, { -41.0f, 10.0f, 10.0f }, { -43.0f, 10.0f, -10.0f }, { -45.0f, 10.0f, -30.0f },
}; // unused?

void Macbeth_MaSpear_Draw(MaSpear* this) {
    if (this->state < 2) {
        Graphics_SetScaleMtx(this->scale);
        if (this->iwork[0] >= 128) {
            RCP_SetupDL(&gMasterDisp, SETUPDL_67);
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, this->iwork[0]);
            gDPSetEnvColor(gMasterDisp++, 255, 48, 0, this->iwork[0]);
            Matrix_Scale(gGfxMatrix, 1.0f, this->fwork[2], 1.0f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_MA_6013060);
            RCP_SetupDL(&gMasterDisp, SETUPDL_67);
            Matrix_Scale(gGfxMatrix, 1.0f, this->fwork[2], 1.0f, MTXF_APPLY);
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 53, 53, 53, 255 - this->iwork[0]);
            gDPSetEnvColor(gMasterDisp++, 0, 0, 0, this->iwork[0]);
        } else {
            RCP_SetupDL(&gMasterDisp, SETUPDL_23);
            if ((this->iwork[7] % 2) != 0) {
                RCP_SetupDL_27();
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
            }
            if (this->iwork[7] > 0) {
                this->iwork[7]--;
            }
        }
        gSPDisplayList(gMasterDisp++, aMaSpearDL);
    }
}

void Macbeth_MaSpear_Setup(MaSpear* this, f32 xPos, f32 yPos, f32 zPos, f32 arg4, f32 yVel, f32 arg6, s16 arg7) {
    Actor_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_ACTOR_MA_SPEAR;
    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;
    this->vel.y = yVel;
    this->iwork[0] = 255;
    this->fwork[1] = arg6;
    this->fwork[2] = 0.2f;
    this->timer_0BC = 0;
    this->iwork[1] = D_i5_801BE320[24]++;
    this->iwork[2] = arg7;

    if (D_i5_801BA570[this->iwork[2]][this->iwork[1]] < 0.0f) {
        this->obj.rot.z = -180.0f;
    } else {
        this->obj.rot.z = 180.0f;
    }

    this->health = 30;
    Object_SetInfo(&this->info, this->obj.id);
    AUDIO_PLAY_SFX(NA_SE_EN_FALLING_DOWN, this->sfxSource, 4);
}

void Macbeth_MaSpear_Spawn(f32 xPos, f32 yPos, f32 zPos, f32 arg3, f32 yVel, f32 arg5, s16 arg6) {
    s32 i;

    for (i = ARRAY_COUNT(gActors) - 1; i >= 0; i--) {
        if (gActors[i].obj.status == OBJ_FREE) {
            Macbeth_MaSpear_Setup(&gActors[i], xPos, yPos, zPos, arg3, yVel, arg5, arg6);
            break;
        }
    }
}

void Macbeth_Effect379_Setup(Effect379* this, f32 xPos, f32 yPos, f32 zPos, f32 arg4, f32 arg5, f32 arg6) {
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    Vec3f sp38;
    Vec3f sp2C;

    Effect_Initialize(this);
    this->obj.status = OBJ_ACTIVE;
    this->obj.id = OBJ_EFFECT_379;

    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;

    this->scale2 = D_i5_801BE368[23];

    this->unk_46 = xPos - arg4;
    this->unk_48 = yPos - arg5;
    this->unk_4A = zPos - arg6;

    sp48 = Math_Atan2F(arg4 - xPos, arg6 - zPos);
    sp44 = sqrtf(SQ(arg4 - xPos) + SQ(arg6 - zPos));
    sp4C = -Math_Atan2F(arg5 - yPos, sp44);

    Matrix_RotateY(gCalcMatrix, sp48, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, sp4C, MTXF_APPLY);

    sp38.x = 0.0f;
    sp38.y = 0.0f;
    sp38.z = 30.0f;

    Matrix_MultVec3f(gCalcMatrix, &sp38, &sp2C);

    this->unk_60.x = sp2C.x;
    this->unk_60.y = sp2C.y;
    this->unk_60.z = sp2C.z;

    Object_SetInfo(&this->info, this->obj.id);
}

void Macbeth_Effect379_Spawn(f32 xPos, f32 yPos, f32 zPos, f32 arg3, f32 arg4, f32 arg5) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Macbeth_Effect379_Setup(&gEffects[i], xPos, yPos, zPos, arg3, arg4, arg5);
            break;
        }
    }
}

void Macbeth_Effect379_Update(Effect* this) {
    f32 sp34;
    f32 sp30;
    f32 sp2C;

    this->vel.x = this->unk_60.x * this->scale1;
    this->vel.y = this->unk_60.y * this->scale1;
    this->vel.z = this->unk_60.z * this->scale1;

    this->unk_46 += (s16) this->vel.x;
    this->unk_48 += (s16) this->vel.y;
    this->unk_4A += (s16) this->vel.z;

    if (this->scale2 == 3.0f) {
        sp34 = D_i5_801BE368[24];
        sp30 = D_i5_801BE368[25];
        sp2C = D_i5_801BE368[26];
    } else if (this->scale2 == 4.0f) {
        sp34 = D_i5_801BE368[27];
        sp30 = D_i5_801BE368[28];
        sp2C = D_i5_801BE368[29];
    } else if (this->scale2 == 1.0f) {
        sp34 = D_i5_801BE368[24];
        sp30 = D_i5_801BE368[25];
        sp2C = D_i5_801BE368[26];
    } else {
        sp34 = D_i5_801BE368[27];
        sp30 = D_i5_801BE368[28];
        sp2C = D_i5_801BE368[29];
    }

    this->obj.pos.x = this->unk_46 + sp34;
    this->obj.pos.y = this->unk_48 + sp30;
    this->obj.pos.z = this->unk_4A + sp2C;

    Math_SmoothStepToF(&this->scale1, 1.0f, 1.0f, 0.1f, 0.0f);

    if (this->unk_44 < 240) {
        this->unk_44 += 15;
    } else {
        Object_Kill(&this->obj, this->sfxSource);
    }

    if ((fabsf(this->obj.pos.x - sp34) <= 30.0f) && (fabsf(this->obj.pos.z - sp2C) <= 30.0f)) {
        Object_Kill(&this->obj, this->sfxSource);
    }
}

void Macbeth_Effect379_Draw(Effect379* this) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_67);

    if (this->scale2 >= 3.0f) {
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, this->unk_44);
        gDPSetEnvColor(gMasterDisp++, 255, 0, 0, this->unk_44);
    } else {
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, this->unk_44);
        gDPSetEnvColor(gMasterDisp++, 0, 128, 255, this->unk_44);
    }

    Matrix_Scale(gGfxMatrix, 0.5f, 0.5f, 0.5f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, aOrbDL);
    RCP_SetupDL(&gMasterDisp, SETUPDL_64);
}

void Macbeth_MaShockBox_Update(MaShockBox* this) {
    if ((gPlayer[0].trueZpos - this->obj.pos.z) < -300.0f) {
        Object_Kill(&this->obj, this->sfxSource);
    }

    switch (this->state) {
        case 0:
            this->vel.y -= 0.5f;
            if (this->obj.pos.y < (gGroundHeight + 35.0f)) {
                this->vel.x = 0.0f;
                this->vel.y = 0.0f;
                this->vel.z = 0.0f;
                if (this->obj.pos.y < gGroundHeight + 35.0f) {
                    this->obj.pos.y = gGroundHeight + 35.0f;
                }
                this->state = 1;
                this->timer_0BC = 200;
                AUDIO_PLAY_SFX(NA_SE_OB_SPARK_BEAM, this->sfxSource, 4);
            }
            break;

        case 1:
            if (this->fwork[0] < 10.0f) {
                this->fwork[0] += 1.0f;
            }

            if (this->fwork[2] < 3.0f) {
                this->fwork[2] += 0.1f;
            }

            if ((gGameFrameCount % 16) == 0) {
                Effect_Effect390_Spawn(this->obj.pos.x - 35.0f, this->obj.pos.y + 15.0f, this->obj.pos.z, -3.0f, 0.0f,
                                       0.0f, 0.1f, 20);
                Effect_Effect390_Spawn(this->obj.pos.x + 35.0f, this->obj.pos.y + 15.0f, this->obj.pos.z, 3.0f, 0.0f,
                                       0.0f, 0.1f, 20);
            }
            break;

        default:
            break;
    }

    if ((gGameFrameCount % 2) != 0) {
        this->fwork[1] = 255.0f;
    } else {
        this->fwork[1] = 32.0f;
    }

    if ((this->dmgType != DMG_NONE) && (this->dmgPart == 0)) {
        AUDIO_PLAY_SFX(NA_SE_EN_DAMAGE_S, this->sfxSource, 4);
        this->dmgType = DMG_NONE;
        this->health -= this->damage;
        this->timer_0C6 = 15;
        if (this->health <= 0) {
            Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EXPLOSION_S);
            func_effect_8007D2C8(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 8.0f);
            Object_Kill(&this->obj, this->sfxSource);
        }
    }
}

void Macbeth_MaShockBox_Draw(MaShockBox* this) {
    gSPDisplayList(gMasterDisp++, aMaShockBoxDL);
    Matrix_Scale(gGfxMatrix, this->fwork[0], this->fwork[2], 1.0f, MTXF_APPLY);
    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, 0.0f, -10.0f, 0.0f, MTXF_APPLY);
    RCP_SetupDL(&gMasterDisp, SETUPDL_67);
    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 111, 175, 64, this->fwork[1]);
    gDPSetEnvColor(gMasterDisp++, 255, 255, 208, this->fwork[1]);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, aMaShockBoxLightDL);
    Matrix_Pop(&gGfxMatrix);
}

void Macbeth_MaShockBox_Setup(MaShockBox* this, f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel) {
    Actor_Initialize(this);
    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_ACTOR_MA_SHOCK_BOX;
    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;
    this->vel.x = xVel;
    this->vel.y = yVel;
    this->vel.z = zVel;
    this->timer_0BC = 0;
    this->health = 30;
    this->fwork[0] = 1.0f;
    this->fwork[2] = 1.0f;
    Object_SetInfo(&this->info, this->obj.id);
    AUDIO_PLAY_SFX(NA_SE_EN_FALLING_DOWN, this->sfxSource, 4);
}

void Macbeth_MaShockBox_Spawn(f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel) {
    s32 i;

    for (i = ARRAY_COUNT(gActors) - 1; i >= 0; i--) {
        if (gActors[i].obj.status == OBJ_FREE) {
            Macbeth_MaShockBox_Setup(&gActors[i], xPos, yPos, zPos, xVel, yVel, zVel);
            break;
        }
    }
}

f32 D_i5_801BA7E4[5] = { 0.0f, 0.0f, 1180.0f, 200.0f, 1000.0f };
f32 D_i5_801BA7F8[5] = { 600.0f, 200.0f, 400.0f, 2000.0f, 1200.0f };
f32 D_i5_801BA80C[5] = { 500.0f, 600.0f, 200.0f, 4500.0f, 2300.0f };
f32 D_i5_801BA820[5] = { 90.0f, -90.0f, 25.0f, 0.0f, 225.0f };

void Macbeth_801AF27C(ActorCutscene* this, s32 arg1) {
    Player* player = &gPlayer[0];

    Actor_Initialize(this);

    this->obj.pos.x = D_i5_801BA7E4[arg1] + player->pos.x;
    this->obj.pos.y = D_i5_801BA7F8[arg1] + player->pos.y;
    this->obj.pos.z = D_i5_801BA80C[arg1] + player->pos.z;

    this->fwork[7] = RAND_FLOAT(360.0f);
    this->fwork[8] = RAND_FLOAT(360.0f);

    this->vel.x = player->vel.x;
    this->vel.y = player->vel.y;
    this->vel.z = player->vel.z;

    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_ACTOR_CUTSCENE;
    this->obj.rot.y = 180.0f;

    Object_SetInfo(&this->info, this->obj.id);

    if (arg1 < 3) {
        this->iwork[11] = 1;
        this->drawShadow = true;
        this->fwork[3] = D_i5_801BA820[arg1];
        this->state = 30;
        AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, this->sfxSource, 4);
    } else {
        this->animFrame = ACTOR_CS_GREAT_FOX;
        this->state = 21;
        this->obj.rot.z = 32.5f;
        AUDIO_PLAY_SFX(NA_SE_GREATFOX_ENGINE, this->sfxSource, 0);
        this->fwork[9] = 20.0f;
    }
}

void Macbeth_801AF44C(void) {
    ActorCutscene* actor = &gActors[8];

    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_CUTSCENE;
    actor->obj.pos.x = gPlayer[0].pos.x + D_i5_801BA7E4[4];
    actor->obj.pos.y = gPlayer[0].pos.y + D_i5_801BA7F8[4];
    actor->obj.pos.z = gPlayer[0].pos.z + D_i5_801BA80C[4];

    actor->vel.x = gPlayer[0].vel.x;
    actor->vel.y = gPlayer[0].vel.y;
    actor->vel.z = gPlayer[0].vel.z;

    actor->fwork[7] = RAND_FLOAT(360.0f);
    actor->fwork[8] = RAND_FLOAT(360.0f);
    actor->fwork[9] = 30.0f;

    actor->rot_0F4.y = D_i5_801BA820[4];
    actor->rot_0F4.x = 0.0f;
    actor->rot_0F4.z = 330.0f;

    actor->obj.rot.x = -0.0f;
    actor->obj.rot.y = actor->rot_0F4.y;
    actor->obj.rot.z = -330.0f;

    actor->fwork[0] = 0.0f;
    actor->animFrame = ACTOR_CS_KATT;
    actor->iwork[11] = 1;
    actor->state = 15;
    actor->fwork[3] = D_i5_801BA820[4];

    Object_SetInfo(&actor->info, actor->obj.id);
    AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, actor->sfxSource, 4);
}

Vec3f D_i5_801BA834[2] = {
    { 2000.0f, 300.0f, 500.0f },
    { 2500.0f, 300.0f, -3300.0f },
};

f32 D_i5_801BA84C[2] = { 0.0f, 60.0f };

// Unused
void Macbeth_801AF628(ActorCutscene* this, s32 index) {
    Actor_Initialize(this);
    this->obj.status = OBJ_ACTIVE;
    this->obj.id = OBJ_ACTOR_CUTSCENE;
    this->obj.pos.x = gPlayer[0].xPath + D_i5_801BA834[index].x;
    this->obj.pos.y = D_i5_801BA834[index].y;
    this->obj.pos.z = D_i5_801BA834[index].z - gPathProgress;
    this->animFrame = ACTOR_CS_37;
    this->obj.rot.y = D_i5_801BA84C[index];
    this->iwork[4] = this->iwork[5] = 192;
    this->iwork[0] = this->iwork[1] = this->iwork[2] = this->iwork[7] = this->iwork[3] = 255;
    this->iwork[6] = 128;
    Object_SetInfo(&this->info, this->obj.id);
}

void Macbeth_Effect357_Spawn2(f32 xPos, f32 yPos, f32 zPos, f32 arg3) {
    Effect* effect = NULL;
    Effect* effectPtr;
    s32 i;

    for (effectPtr = &gEffects[0], i = 0; i < 99; i++, effectPtr++) {
        if (effectPtr->obj.status == OBJ_FREE) {
            effect = effectPtr;
            break;
        }
    }

    if (i != 99) {
        Effect_Initialize(effect);
        effect->obj.status = OBJ_ACTIVE;
        effect->obj.id = OBJ_EFFECT_357;
        effect->obj.pos.x = xPos;
        effect->obj.pos.y = yPos;
        effect->obj.pos.z = zPos;
        effect->vel.x = RAND_FLOAT_CENTERED(20.0f) - 60.0f;
        effect->vel.y = RAND_FLOAT(3.0f) + 10.0f;
        effect->vel.z = RAND_FLOAT(30.0f) + 240.0f;
        effect->scale2 = RAND_FLOAT(0.8f) + 0.3f + arg3;
        effect->timer_50 = RAND_INT(5.0f) + 30;
        effect->obj.rot.x = RAND_FLOAT(360.0f);
        effect->unk_60.x = RAND_FLOAT_CENTERED(30.0f);
        effect->unk_60.y = RAND_FLOAT_CENTERED(30.0f);
        effect->unk_60.z = RAND_FLOAT_CENTERED(30.0f);
        effect->unk_44 = i % 4U;
        Object_SetInfo(&effect->info, effect->obj.id);
    }
}

f32 D_i5_801BA854[8] = { 1.5f, -1.0f, 0.7f, 0.0f, 0.9f, 0.7f, -1.0f, 1.5f };
f32 D_i5_801BA874[8] = { 200.0f, 300.0f, 400.0f, 0.0f, 500.0f, 100.0f, 120.0f, 100.0f };
f32 D_i5_801BA894[8] = { 200.0f, 250.0f, 220.0f, 0.0f, 200.0f, 230.0f, 220.0f, 350.0f };

void Macbeth_LevelComplete2(Player* player) {
    s32 i;
    s32 j;
    Vec3f spE4;
    Vec3f spD8;
    f32 zeroVar = 0.0f;

    switch (player->csState) {
        case 0:
            gCsFrameCount = 0;
            gLoadLevelObjects = 1;
            player->draw = false;

            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 30);
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 30);

            player->csState = 1;

            D_ctx_80177A48[0] = 0.0f;
            D_ctx_80177A48[4] = -60.0f;
            D_ctx_80177A48[5] = 240.0f;

            player->gravity = 3.0f;

            gCameraShakeY = player->vel.x = player->vel.y = player->vel.z = player->baseSpeed = 0.0f;

            if (player->shields <= 0) {
                player->shields = 1;
            }

            player->cam.eye.x = gCsCamEyeX = gActors[D_i5_801BE318].obj.pos.x - 250.0f;
            player->cam.eye.y = gCsCamEyeY = gActors[D_i5_801BE318].obj.pos.y + 150.0f;
            player->cam.eye.z = gCsCamEyeZ = gActors[D_i5_801BE318].obj.pos.z + gPathProgress + 500.0f;
            player->cam.at.x = gCsCamAtX = gActors[D_i5_801BE318].obj.pos.x;
            player->cam.at.y = gCsCamAtY = gActors[D_i5_801BE318].obj.pos.y + 200.0f;
            player->cam.at.z = gCsCamAtZ = gActors[D_i5_801BE318].obj.pos.z + gPathProgress;

            player->pos.x = 500.0f;
            player->pos.y = -3.0f;

            sMaTrainSpeedTarget = 0.0f;
            player->aerobaticPitch = 0.0f;
            player->camRoll = 0.0f;
            player->boostSpeed = 0.0f;
            player->arwing.upperLeftFlapYrot = player->arwing.bottomRightFlapYrot = player->arwing.bottomLeftFlapYrot =
                player->zRotBarrelRoll = player->zRotBank = 0.0f;
            player->yBob = 0.0f;
            player->rockAngle = 0.0f;
            player->unk_16C = 0.0f;
            player->unk_170 = 0.0f;
            player->arwing.upperRightFlapYrot = 0.0f;
            /* fallthrough */
        case 1:
            gShowBossHealth = false;
            if (gCsFrameCount == 70) {
                gObjectLoadIndex = 498;

                for (i = 0; i < ARRAY_COUNT(gActors); i++) {
                    if (gActors[i].obj.id == OBJ_ACTOR_MA_RAILWAY_SIGNAL) {
                        gActors[i].state++;
                        break;
                    }
                }

                player->csState++;

                gCsCamEyeX = -100.0f;
                gCsCamEyeY = 250.0f;
                gCsCamEyeZ = 2090.0f;
                gCsCamAtX = -250.0f;
                gCsCamAtY = 10.0f;
                gCsCamAtZ = -3210.0f;

                player->cam.eye.x = -250.0f;
                player->cam.eye.y = 50.0f;
                player->cam.eye.z = 1580.0f;
                player->cam.at.x = -250.0f;
                player->cam.at.y = 10.0f;
                player->cam.at.z = -3210.0f;

                D_i5_801BE312 = 1;

                player->pos.x = 500.0f;
                player->pos.y = -3.0f;
                player->pos.z = player->trueZpos = -111130.0f;
                player->zPath = gPathProgress = 115930.0f;
                player->flags_228 = PFLAG_228_4;

                gLastPathChange = OBJ_ITEM_PATH_TURN_RIGHT;

                sMaTrainSpeedTarget = 0.0f;

                gActors[D_i5_801BE314].obj.pos.x = -431.0f;
                gActors[D_i5_801BE314].obj.pos.y = 0.0f;
                gActors[D_i5_801BE314].obj.pos.z = -111174.0f;
                gActors[D_i5_801BE314].vel.x = 0.0f;
                gActors[D_i5_801BE314].vel.y = 0.0f;
                gActors[D_i5_801BE314].vel.z = 0.0f;
                gActors[D_i5_801BE316].obj.pos.x = -864.0f;
                gActors[D_i5_801BE316].obj.pos.y = 874.0f;
                gActors[D_i5_801BE316].obj.pos.z = -109864.0f;
            }
            break;

        case 2:
            if (gCsFrameCount > 105) {
                Math_SmoothStepToF(&D_ctx_80177A48[0], 1.0f, 1.0f, 0.005f, 0.0f);
            }
            if (gCsFrameCount < 160) {
                gActors[D_i5_801BE314].obj.pos.x = -431.0f;
                gActors[D_i5_801BE314].obj.pos.y = 0.0f;
                gActors[D_i5_801BE314].obj.pos.z = -111174.0f;
                gActors[D_i5_801BE314].vel.x = 0.0f;
                gActors[D_i5_801BE314].vel.y = 0.0f;
                gActors[D_i5_801BE314].vel.z = 0.0f;
                gActors[D_i5_801BE316].obj.pos.x = -864.0f;
                gActors[D_i5_801BE316].obj.pos.y = 874.0f;
                gActors[D_i5_801BE316].obj.pos.z = -109864.0f;
            } else {
                D_ctx_80177A48[0] = 0.0f;
                sMaTrainSpeedTarget = -40.0f;
                player->csState++;
            }
            /* fallthrough */
        case 3:
            player->vel.z = gActors[D_i5_801BE314].vel.z;
            if (gCsFrameCount == 252) {
                gCsCamEyeY = 570.0f;
                player->pathChangeTimer = 1000;
                player->xPathTarget = 20000.0f;
                player->pathChangeYaw = -23.0f;
                player->pathStep = 0.0f;
            }
            if (gCsFrameCount >= 252) {
                player->pos.x = gActors[D_i5_801BE314].obj.pos.x + 500.0f;
                player->zPathVel = -gActors[D_i5_801BE314].vel.z;
                player->zPath += player->zPathVel;

                gPathVelZ = player->zPathVel;
                gPathProgress = player->zPath;
                gPathTexScroll += player->zPathVel;

                player->pos.z = player->trueZpos = -(gPathProgress + 210.0f);

                Math_SmoothStepToF(&D_ctx_80177A48[0], 1.0f, 0.1f, 0.00025f, 0.0f);

                gCsCamAtX = gActors[D_i5_801BE314].obj.pos.x + 2500.0f;
                gCsCamAtZ = gActors[D_i5_801BE314].obj.pos.z + gPathProgress - 2000.0f;
                gCsCamEyeX = gCsCamAtX - 2340.0f;
                gCsCamEyeZ = gCsCamAtZ + 1410.0f;
            }
            if (gCsFrameCount == 389) {
                player->csState++;
                player->vel.z = 0.0f;
                player->zPathVel = 0.0f;

                gPathVelX = 0.0f;
                gPathVelY = 0.0f;

                player->pathChangeTimer = 0;

                player->cam.eye.x = gCsCamEyeX = 2750.0f;
                player->cam.eye.y = gCsCamEyeY = 50.0f;
                player->cam.eye.z = gCsCamEyeZ = -620.0f;
                player->cam.at.x = gCsCamAtX = -650.0f;
                player->cam.at.y = gCsCamAtY = 30.0f;
                player->cam.at.z = gCsCamAtZ = 1900.0f;

                player->yRot_114 = 0.0f;
                sMaTrainSpeedTarget = -100.0f;
                Audio_KillSfxById(NA_SE_EN_FREIGHT_TRAIN);
                AUDIO_PLAY_SFX(NA_SE_EN_TRAIN_BREAK, gActors[D_i5_801BE314].sfxSource, 4);
                D_i5_801BE313 = 0;
            }
            break;

        case 4:
            if (gCsFrameCount == 403) {
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
                gFillScreenAlphaTarget = 255;
                gFillScreenAlphaStep = 20;
            }
            if (gCsFrameCount == 416) {
                player->csState++;

                D_ctx_80177A48[0] = 1.0f;

                player->yRot_114 = 30.0f;
                player->xPath = 4600.0f;

                sMaTrainSpeedTarget = -80.0f;

                player->zPath = gPathProgress += 300.0f;

                D_ctx_80177A48[5] = 0.0f;
                D_ctx_80177A48[6] = 0.5f;
                D_ctx_80177A48[7] = 1560.0f;
                D_ctx_80177A48[8] = 2400.0f;

                player->cam.at.x = gCsCamAtX = gActors[D_i5_801BE314].obj.pos.x;
                player->cam.at.z = gCsCamAtZ = (gActors[D_i5_801BE314].obj.pos.z + gPathProgress) - 2000.0f;
                player->cam.eye.y = gCsCamEyeY = 50.0f;
                player->cam.at.y = gCsCamAtY = 10.0f;
                player->cam.eye.x = gCsCamEyeX = D_ctx_80177A48[7] + gCsCamAtX;
                player->cam.eye.z = gCsCamEyeZ = D_ctx_80177A48[8] + gCsCamAtZ;

                player->pathChangeYaw = -30.0f;
                player->xPathTarget = 10014.0f;
                player->pathChangeTimer = 1000;
                player->pathStep = 0.0f;

                gFillScreenAlphaTarget = 0;
                gFillScreenAlphaStep = 127;
            }
            break;

        case 5:
            if (gCsFrameCount <= 625) {
                Math_SmoothStepToF(&sMaTrainSpeedTarget, 0.0f, 0.1f, 0.05f, 0.0f);
            }
            if (gCsFrameCount >= 430) {
                Math_SmoothStepToF(&D_ctx_80177A48[6], 22.0f, 0.1f, 1.0f, 0.0f);
                Math_SmoothStepToF(&D_ctx_80177A48[7], 2600.0f, 0.1f, D_ctx_80177A48[6], 0.0f);
                Math_SmoothStepToF(&D_ctx_80177A48[8], 3800.0f, 0.1f, D_ctx_80177A48[6], 0.0f);
                Math_SmoothStepToF(&gCsCamEyeY, 1300.0f, 0.1f, 17.0f, 0.0f);
            }
            if (gCsFrameCount <= 505) {
                gCsCamAtZ = gActors[D_i5_801BE314].obj.pos.z + gPathProgress - 2000.0f;
                gCsCamAtX = gActors[D_i5_801BE314].obj.pos.x;
                player->vel.z = gActors[D_i5_801BE314].vel.z;
                player->pos.x = gActors[D_i5_801BE314].obj.pos.x + 500.0f;
                player->pos.z = player->trueZpos = -(gPathProgress + 210.0f);
                player->zPathVel = -gActors[D_i5_801BE314].vel.z;
                gCsCamEyeX = D_ctx_80177A48[7] + gCsCamAtX;
                gCsCamEyeZ = D_ctx_80177A48[8] + gCsCamAtZ;
                Effect_Effect390_Spawn(gActors[D_i5_801BE314].obj.pos.x + 480.0f,
                                       gActors[D_i5_801BE314].obj.pos.y + 15.0f,
                                       gActors[D_i5_801BE314].obj.pos.z - 400.0f, gActors[D_i5_801BE314].vel.x,
                                       gActors[D_i5_801BE314].vel.y, 0.0f, 0.2f, 10);
            } else {
                player->vel.z = 0.0f;
                if ((gGameFrameCount % 16) == 0) {
                    gFogRed -= 1;
                    gFogGreen -= 1;
                    gFogBlue -= 2;
                }

                Math_SmoothStepToF(&player->zPathVel, 0.0f, 1.0f, 0.6f, 0.0f);
                Math_SmoothStepToF(&gCsCamAtX, 11700.0f, 0.1f, 50.0f, 0.0f);
                Math_SmoothStepToF(&D_ctx_80177A48[5], 30.0f, 0.1f, 0.05f, 0.0f);
                Math_SmoothStepToF(&gCsCamAtY, 1600.0f, 0.1f, D_ctx_80177A48[5], 0.0f);

                if (player->zPathVel >= 2.5f) {
                    player->pos.x = gActors[D_i5_801BE314].obj.pos.x + 500.0f;
                    player->pos.z = player->trueZpos = -(gPathProgress + 210.0f);
                } else {
                    player->xPathTarget = player->xPath;
                    gPathVelX = 0.0f;
                }

                Effect_Effect362_Spawn(gActors[D_i5_801BE314].obj.pos.x + 190.0f,
                                       gActors[D_i5_801BE314].obj.pos.y + 30.0f,
                                       gActors[D_i5_801BE314].obj.pos.z - 100.0f, 6.0f);
                Effect_Effect362_Spawn(gActors[D_i5_801BE314].obj.pos.x + 190.0f,
                                       gActors[D_i5_801BE314].obj.pos.y + 30.0f,
                                       gActors[D_i5_801BE314].obj.pos.z - 120.0f, 6.0f);
                Effect_Effect362_Spawn(gActors[D_i5_801BE314].obj.pos.x - 190.0f,
                                       gActors[D_i5_801BE314].obj.pos.y + 30.0f,
                                       gActors[D_i5_801BE314].obj.pos.z - 100.0f, 6.0f);
                Effect_Effect362_Spawn(gActors[D_i5_801BE314].obj.pos.x - 190.0f,
                                       gActors[D_i5_801BE314].obj.pos.y + 30.0f,
                                       gActors[D_i5_801BE314].obj.pos.z - 120.0f, 6.0f);
            }

            player->zPath += player->zPathVel;
            gPathVelZ = player->zPathVel;
            gPathProgress = player->zPath;
            gPathTexScroll += player->zPathVel;

            if (gCsFrameCount == 630) {
                Audio_KillSfxBySourceAndId(gActors[D_i5_801BE314].sfxSource, NA_SE_EN_TRAIN_BREAK);
                AUDIO_PLAY_SFX(NA_SE_EN_EXPLOSION_L, gActors[D_i5_801BE314].sfxSource, 4);
                player->csState++;
                player->vel.z = 0.0f;
                player->zPathVel = 0.0f;

                gPathVelZ = 0.0f;
                gPathVelX = 0.0f;
                gPathVelY = 0.0f;

                player->pathChangeTimer = 10000;

                D_ctx_80177A48[0] = 1.0f;

                sMaTrainSpeedTarget = 0.0f;

                gControllerRumbleFlags[0] = 1;
                gControllerRumbleTimers[0] = 10;

                gCameraShake = 10;

                D_ctx_80177A48[4] = -70.0f;
                D_ctx_80177A48[5] = 280.0f;
            }
            break;

        case 6:
            Math_SmoothStepToF(&D_ctx_80177A48[4], -60.0f, 1.0f, 0.5f, 0.0f);
            Math_SmoothStepToF(&D_ctx_80177A48[5], 240.0f, 1.0f, 2.0f, 0.0f);

            if ((gGameFrameCount % 2) == 0) {
                Effect_FireSmoke_Spawn2(11000.0f, 200.0f, -139000.0f, D_ctx_80177A48[4], 4.0f, D_ctx_80177A48[5],
                                        20.0f);
            }

            if (gCsFrameCount == 710) {
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = gFillScreenAlpha = 255;
                gFillScreenAlphaTarget = 0;
                gFillScreenAlphaStep = 128;

                Effect_Effect367_Spawn(gActors[D_i5_801BE314].obj.pos.x + 1000.0f,
                                       gActors[D_i5_801BE314].obj.pos.y + 20.0f, -138500.0f, 100.0f, 1000.0f, 0);
                Effect_Effect383_Spawn(gActors[D_i5_801BE314].obj.pos.x + 200.0f,
                                       gActors[D_i5_801BE314].obj.pos.y + 700.0f, -137750.0f, 100.0f);

                for (i = 0; i < 8; i++) {
                    Effect_Effect357_Spawn50(gActors[D_i5_801BE314].obj.pos.x + RAND_FLOAT_CENTERED(1000.0f),
                                             gActors[D_i5_801BE314].obj.pos.y + 1300.0f,
                                             gActors[D_i5_801BE314].obj.pos.z + 700.0f + RAND_FLOAT_CENTERED(1000.0f),
                                             6.0f);
                    Macbeth_Effect357_Spawn2(RAND_FLOAT_CENTERED(650.0f) + 11250.0f, 300.0f,
                                             RAND_FLOAT(650.0f) + -139000.0f, 0.7f);
                }

                gActors[58].scale = 0.8f;

                func_effect_8007D0E0(gActors[D_i5_801BE314].obj.pos.x + 500.0f + RAND_FLOAT_CENTERED(700.0f),
                                     gActors[D_i5_801BE314].obj.pos.y + 500.0f + RAND_FLOAT_CENTERED(700.0f),
                                     gActors[D_i5_801BE314].obj.pos.z + 3000.0f + RAND_FLOAT_CENTERED(700.0f), 30.0f);
            }
            if ((gCsFrameCount > 710) && ((gGameFrameCount % 8) == 0)) {
                func_effect_8007D0E0(gActors[D_i5_801BE314].obj.pos.x + 500.0f + RAND_FLOAT_CENTERED(700.0f),
                                     gActors[D_i5_801BE314].obj.pos.y + 500.0f + RAND_FLOAT_CENTERED(700.0f),
                                     gActors[D_i5_801BE314].obj.pos.z + 3000.0f + RAND_FLOAT_CENTERED(700.0f), 30.0f);
            }
            if ((gCsFrameCount > 725) && ((gGameFrameCount % 8) == 0)) {
                func_effect_8007D0E0(gActors[D_i5_801BE314].obj.pos.x - 1500.0f + RAND_FLOAT_CENTERED(700.0f),
                                     gActors[D_i5_801BE314].obj.pos.y + 1000.0f + RAND_FLOAT_CENTERED(700.0f),
                                     gActors[D_i5_801BE314].obj.pos.z + 1700.0f + RAND_FLOAT_CENTERED(700.0f), 30.0f);
            }
            if ((gCsFrameCount > 740) && ((gGameFrameCount % 8) == 0)) {
                func_effect_8007D0E0(gActors[D_i5_801BE314].obj.pos.x - 3500.0f + RAND_FLOAT_CENTERED(700.0f),
                                     gActors[D_i5_801BE314].obj.pos.y + 600.0f + RAND_FLOAT_CENTERED(700.0f),
                                     gActors[D_i5_801BE314].obj.pos.z + 1200.0f + RAND_FLOAT_CENTERED(700.0f), 30.0f);
            }
            if ((gCsFrameCount > 755) && ((gGameFrameCount % 8) == 0)) {
                func_effect_8007D0E0(gActors[D_i5_801BE314].obj.pos.x - 3000.0f + RAND_FLOAT_CENTERED(700.0f),
                                     gActors[D_i5_801BE314].obj.pos.y + 400.0f + RAND_FLOAT_CENTERED(700.0f),
                                     gActors[D_i5_801BE314].obj.pos.z + 1300.0f + RAND_FLOAT_CENTERED(700.0f), 30.0f);
            }
            if (gCsFrameCount == 800) {
                Effect_Effect383_Spawn(gActors[D_i5_801BE314].obj.pos.x - 3000.0f,
                                       gActors[D_i5_801BE314].obj.pos.y + 500.0f,
                                       gActors[D_i5_801BE314].obj.pos.z + 1600.0f, 10000.0f);
                for (i = 0; i < 8; i++) {
                    Effect_Effect357_Spawn50(gActors[D_i5_801BE314].obj.pos.x - 3000.0f + RAND_FLOAT_CENTERED(1000.0f),
                                             gActors[D_i5_801BE314].obj.pos.y + 700.0f,
                                             gActors[D_i5_801BE314].obj.pos.z + 1600.0f + RAND_FLOAT_CENTERED(1000.0f),
                                             6.0f);
                    Macbeth_Effect357_Spawn2(RAND_FLOAT_CENTERED(650.0f) + 11250.0f, 300.0f,
                                             RAND_FLOAT(650.0f) + -139000.0f, 0.7f);
                }
            }
            if (gCsFrameCount == 820) {
                Effect_Effect383_Spawn(gActors[D_i5_801BE314].obj.pos.x, gActors[D_i5_801BE314].obj.pos.y + 500.0f,
                                       gActors[D_i5_801BE314].obj.pos.z + 3300.0f, 14000.0f);
                for (i = 0; i < 8; i++) {
                    Effect_Effect357_Spawn50(gActors[D_i5_801BE314].obj.pos.x + 500.0f + RAND_FLOAT_CENTERED(1000.0f),
                                             gActors[D_i5_801BE314].obj.pos.y + 900.0f,
                                             gActors[D_i5_801BE314].obj.pos.z + 3300.0f + RAND_FLOAT_CENTERED(1000.0f),
                                             6.0f);
                    Macbeth_Effect357_Spawn2(RAND_FLOAT_CENTERED(650.0f) + 11250.0f, 300.0f,
                                             RAND_FLOAT(650.0f) + -139000.0f, 0.7f);
                }
            }
            if (gCsFrameCount == 835) {
                Effect_Effect383_Spawn(gActors[D_i5_801BE314].obj.pos.x - 1500.0f,
                                       gActors[D_i5_801BE314].obj.pos.y + 500.0f,
                                       gActors[D_i5_801BE314].obj.pos.z + 2000.0f, 80.0f);
                for (i = 0; i < 8; i++) {
                    Effect_Effect357_Spawn50(gActors[D_i5_801BE314].obj.pos.x - 1500.0f + RAND_FLOAT_CENTERED(1000.0f),
                                             gActors[D_i5_801BE314].obj.pos.y + 1200.0f,
                                             gActors[D_i5_801BE314].obj.pos.z + 2000.0f + RAND_FLOAT_CENTERED(1000.0f),
                                             6.0f);
                    Macbeth_Effect357_Spawn2(RAND_FLOAT_CENTERED(650.0f) + 11250.0f, 300.0f,
                                             RAND_FLOAT(650.0f) + -139000.0f, 0.7f);
                }
            }
            if (gCsFrameCount == 845) {
                Effect_Effect383_Spawn(gActors[D_i5_801BE314].obj.pos.x - 500.0f,
                                       gActors[D_i5_801BE314].obj.pos.y + 500.0f,
                                       gActors[D_i5_801BE314].obj.pos.z + 2800.0f, 10000.0f);
                for (i = 0; i < 11; i++) {
                    Effect_Effect357_Spawn50(gActors[D_i5_801BE314].obj.pos.x - 500.0f + RAND_FLOAT_CENTERED(1000.0f),
                                             gActors[D_i5_801BE314].obj.pos.y + 900.0f,
                                             gActors[D_i5_801BE314].obj.pos.z + 2800.0f + RAND_FLOAT_CENTERED(1000.0f),
                                             6.0f);
                    Macbeth_Effect357_Spawn2(RAND_FLOAT_CENTERED(650.0f) + 11250.0f, 300.0f,
                                             RAND_FLOAT(650.0f) + -139000.0f, 0.7f);
                }
            }
            if (gCsFrameCount == 853) {
                Effect_Effect383_Spawn(gActors[D_i5_801BE314].obj.pos.x - 3500.0f,
                                       gActors[D_i5_801BE314].obj.pos.y + 500.0f,
                                       gActors[D_i5_801BE314].obj.pos.z + 2500.0f, 14000.0f);
                for (i = 0; i < 8; i++) {
                    Effect_Effect357_Spawn50(gActors[D_i5_801BE314].obj.pos.x - 3500.0f + RAND_FLOAT_CENTERED(1000.0f),
                                             gActors[D_i5_801BE314].obj.pos.y + 900.0f,
                                             gActors[D_i5_801BE314].obj.pos.z + 1500.0f + RAND_FLOAT_CENTERED(1000.0f),
                                             6.0f);
                    Macbeth_Effect357_Spawn2(RAND_FLOAT_CENTERED(650.0f) + 11250.0f, 300.0f,
                                             RAND_FLOAT(650.0f) + -139000.0f, 0.7f);
                }
                gCameraShake = 30;
            }
            if (gCsFrameCount == 860) {
                Effect_Effect367_Spawn(gActors[D_i5_801BE314].obj.pos.x + 1000.0f,
                                       gActors[D_i5_801BE314].obj.pos.y + 20.0f, -138500.0f, 100.0f, 1000.0f, 0);
                Effect_Effect383_Spawn(gActors[D_i5_801BE314].obj.pos.x - 1500.0f,
                                       gActors[D_i5_801BE314].obj.pos.y + 700.0f,
                                       gActors[D_i5_801BE314].obj.pos.z + 3000.0f, 180.0f);
                for (i = 0; i < 8; i++) {
                    Effect_Effect357_Spawn50(gActors[D_i5_801BE314].obj.pos.x - 1500.0f + RAND_FLOAT_CENTERED(1000.0f),
                                             gActors[D_i5_801BE314].obj.pos.y + 1300.0f,
                                             gActors[D_i5_801BE314].obj.pos.z + 2500.0f + RAND_FLOAT_CENTERED(1000.0f),
                                             6.0f);
                    Macbeth_Effect357_Spawn2(RAND_FLOAT_CENTERED(650.0f) + 11250.0f, 300.0f,
                                             RAND_FLOAT(650.0f) + -139000.0f, 0.7f);
                }
            }
            if (gCsFrameCount == 880) {
                gControllerRumbleFlags[0] = 1;
                gControllerRumbleTimers[0] = 10;

                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
                gFillScreenAlphaTarget = 255;
                gFillScreenAlphaStep = 20;

                AUDIO_PLAY_SFX(NA_SE_EN_STAR_EXPLOSION, gActors[D_i5_801BE314].sfxSource, 4);
                gBossActive = gLoadLevelObjects = false;
            }
            if (gCsFrameCount == 940) {
                player->csState++;

                Play_ClearObjectData();

                player->pos.z = player->trueZpos = -(gPathProgress + 210.0f);
                player->pos.x = player->xPath;

                Effect_Effect383_Spawn(player->pos.x - 1800.0f, -50.0f, player->pos.z + 5000.0f, 40.0f);

                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = gFillScreenAlpha = 255;
                gFillScreenAlphaTarget = 0;
                gFillScreenAlphaStep = 8;

                D_ctx_80177A48[0] = 0.0f;

                player->draw = true;

                player->cam.at.x = gCsCamAtX = player->cam.eye.x = gCsCamEyeX = player->pos.x;
                player->cam.at.y = gCsCamAtY = player->pos.y + 70.0f;
                player->cam.eye.y = gCsCamEyeY = player->pos.y + 30.0f;
                player->cam.eye.z = gCsCamEyeZ = (player->trueZpos + gPathProgress) - 300.0f;
                player->cam.at.z = gCsCamAtZ = player->trueZpos + gPathProgress;

                player->savedAlternateView = player->pathChangeTimer = 0;
                player->unk_190 = player->unk_194 = player->unk_188 = player->unk_18C = player->pathChangeYaw =
                    player->yRot_114 = player->aerobaticPitch = player->camRoll = player->unk_174 = player->unk_178 =
                        player->unk_17C = player->unk_180 = player->unk_184 = player->arwing.upperRightFlapYrot =
                            player->unk_170 = player->unk_16C = player->rockAngle = player->yBob =
                                player->arwing.upperLeftFlapYrot = player->arwing.bottomRightFlapYrot =
                                    player->arwing.bottomLeftFlapYrot = player->zRotBarrelRoll = player->zRotBank =
                                        player->boostSpeed = 0.0f;

                player->baseSpeed = 5.0f;

                D_ctx_80177A48[3] = D_ctx_80177A48[6] = D_ctx_80177A48[7] = D_ctx_80177A48[8] = 0.0f;

                player->grounded = true;
                player->hitTimer = 0;
                player->pos.y = gGroundHeight - 3.0f;
                player->vel.y = -3.0f;

                player->rollState = player->boostCooldown = player->boostMeter = player->unk_184 = player->rot_104.y =
                    player->rot_104.z = player->rot.y = player->rot.x = player->rot_104.x = 0.0f;
                player->rollInputTimerL = player->sfx.bank = 0;
            }
            break;

        case 7:
            if ((gGameFrameCount % 4) == 0) {
                func_effect_8007D0E0(player->pos.x - 1750.0f + RAND_FLOAT_CENTERED(700.0f), 10.0f,
                                     player->pos.z + 5000.0f + RAND_FLOAT_CENTERED(700.0f), 5.0f);
                Effect_Effect343_Spawn(player->pos.x - 1800.0f + RAND_FLOAT_CENTERED(40.0f), -100.0f,
                                       player->pos.z + 5000.0f + RAND_FLOAT_CENTERED(40.0f), 9.0f);
            }

            if ((gCsFrameCount >= 1059) && (gCsFrameCount < 2120)) {
                Math_SmoothStepToF(&D_ctx_80177A48[0], 1.0f, 1.0f, 0.005f, 0.0f);
                Math_SmoothStepToF(&D_ctx_80177A48[3], 1080.0f, 0.1f, D_ctx_80177A48[0] * 1.2f, 0.0f);
                Matrix_RotateY(gCalcMatrix, -D_ctx_80177A48[3] * M_DTOR, MTXF_NEW);
                spE4.x = 0.0f;
                spE4.y = 0.0f;
                spE4.z = -300.0f;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &spE4, &spD8);
                gCsCamEyeX = player->pos.x + spD8.x;
                gCsCamEyeZ = player->pos.z + gPathProgress + spD8.z;
            }
            if (gCsFrameCount >= 2120) {
                Math_SmoothStepToF(&D_ctx_80177A48[0], 1.0f, 1.0f, 0.001f, 0.0f);
                Math_SmoothStepToF(&D_ctx_80177A48[8], 20.0f, 0.1f, 0.1f, 0.0f);
                Math_SmoothStepToF(&gCsCamEyeX, player->pos.x - 2000.0f, 0.1f, D_ctx_80177A48[8], 0.0f);
                gCsCamEyeZ -= 1.0f;
            }

            //! @BUG: The following condition is always true:
            // if ((gCsFrameCount >= 2120) || (gCsFrameCount < 2175)) {
            if (CVarGetInteger("gMaCameraFix", 0) == 1) {
                if ((gCsFrameCount >= 2120) && (gCsFrameCount < 2175)) {
                    Math_SmoothStepToF(&gCsCamAtY, player->pos.y + 70.0f, 0.1f, 8.0f, 0.0f);
                }
            } else {
                if ((gCsFrameCount >= 2120) || (gCsFrameCount < 2175)) {
                    Math_SmoothStepToF(&gCsCamAtY, player->pos.y + 70.0f, 0.1f, 8.0f, 0.0f);
                }
            }

            if (gCsFrameCount == 2120) {
                D_ctx_80177A48[0] = 0.0f;
            }
            if (gCsFrameCount >= 2160) {
                player->vel.y = 4.0f;
                Math_SmoothStepToF(&player->unk_170, 2.0f, 1.0f, 0.3f, 0.0f);
                Math_SmoothStepToF(&player->unk_16C, 2.0f, 1.0f, 0.3f, 0.0f);
                if ((gCsFrameCount >= 2165) && (gCsFrameCount <= 2180)) {
                    Effect_Effect362_Spawn(player->pos.x + RAND_FLOAT_CENTERED(30.0f), 0.0f,
                                           RAND_FLOAT_CENTERED(30.0f) + player->trueZpos, RAND_FLOAT(2.0f) + 3.5f);
                    Effect_Effect362_Spawn(player->pos.x - RAND_FLOAT_CENTERED(30.0f), 0.0f,
                                           RAND_FLOAT_CENTERED(30.0f) + player->trueZpos, RAND_FLOAT(2.0f) + 3.5f);
                }
                Math_SmoothStepToF(&D_ctx_80177A48[7], 4.5f, 0.1f, 0.3f, 0.0f);
                player->trueZpos = player->pos.z;
            }

            func_tank_80045130(player);
            func_tank_80044868(player);
            func_tank_800444BC(player);

            Player_UpdatePath(player);

            if (gCsFrameCount >= 2175) {
                Math_SmoothStepToF(&gCsCamAtZ, gActors[3].obj.pos.z + gPathProgress - 300.0f, 0.1f, 20.0f, 0.0f);
                Math_SmoothStepToF(&gCsCamAtY, gActors[3].obj.pos.y + 100.0f, 0.1f, 10.0f, 0.0f);
            } else {
                player->cam.at.z = gCsCamAtZ = player->trueZpos + gPathProgress;
            }
            Math_SmoothStepToF(&player->pos.y, 260.0f, 0.1f, D_ctx_80177A48[7], 0.0f);
            break;
    }

    switch (gCsFrameCount) {
        case 973:
            gLevelClearScreenTimer = 100;
            break;

        case 340:
            Radio_PlayMessage(gMsg_ID_17471, RCID_BOSS_MACBETH);
            break;

        case 520:
            Radio_PlayMessage(gMsg_ID_17472, RCID_BOSS_MACBETH);
            break;

        case 710:
        case 800:
        case 820:
        case 835:
        case 845:
        case 860:
            gCameraShake = 20;
            D_ctx_80177A48[4] = -90.0f;
            D_ctx_80177A48[5] = 360.0f;
            break;

        case 910:
            AUDIO_PLAY_BGM(NA_BGM_COURSE_CLEAR);
            break;

        case 1040:
            Radio_PlayMessage(gMsg_ID_20010, RCID_FOX);
            break;

        case 1060:
            if (gTeamShields[TEAM_ID_SLIPPY] > 0) {
                Macbeth_801AF27C(&gActors[5], 0);
            }
            break;

        case 1130:
            switch (gTeamShields[TEAM_ID_SLIPPY]) {
                case 0:
                    Radio_PlayMessage(gMsg_ID_20345, RCID_ROB64);
                    break;
                case -1:
                    Radio_PlayMessage(gMsg_ID_20333, RCID_ROB64);
                    break;
                default:
                    Radio_PlayMessage(gMsg_ID_17330, RCID_SLIPPY);
                    break;
            }
            break;

        case 1240:
            if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                Macbeth_801AF27C(&gActors[6], 1);
            }
            break;

        case 1310:
            D_i5_801BA874[5] = 220.0f;
            break;

        case 1350:
            switch (gTeamShields[TEAM_ID_PEPPY]) {
                case 0:
                    Radio_PlayMessage(gMsg_ID_20344, RCID_ROB64);
                    break;
                case -1:
                    Radio_PlayMessage(gMsg_ID_20332, RCID_ROB64);
                    break;
                default:
                    Radio_PlayMessage(gMsg_ID_17310, RCID_PEPPY);
                    break;
            }
            break;

        case 1420:
            if (gLeveLClearStatus[LEVEL_ZONESS] != 0) {
                Macbeth_801AF44C();
            }
            break;

        case 1460:
            D_i5_801BA874[6] = 170.0f;
            break;

        case 1500:
            if (gLeveLClearStatus[LEVEL_ZONESS] != 0) {
                Radio_PlayMessage(gMsg_ID_17300, RCID_KATT);
            }
            break;

        case 1640:
            if (gTeamShields[TEAM_ID_FALCO] > 0) {
                Macbeth_801AF27C(&gActors[7], 2);
            }
            break;

        case 1660:
            switch (gTeamShields[TEAM_ID_FALCO]) {
                case 0:
                    Radio_PlayMessage(gMsg_ID_20340, RCID_ROB64);
                    break;
                case -1:
                    Radio_PlayMessage(gMsg_ID_20331, RCID_ROB64);
                    break;
                default:
                    Radio_PlayMessage(gMsg_ID_17320, RCID_FALCO);
                    break;
            }
            break;

        case 1661:
            D_i5_801BA854[6] = -0.5f;
            break;

        case 1810:
            Object_Kill(&gActors[8].obj, gActors[8].sfxSource);
            gSceneSetup = 1;
            break;

        case 1817:
            gShowLevelClearStatusScreen = true;
            break;

        case 1960:
            Macbeth_801AF27C(&gActors[3], 3);
            gActors[3].info.hitbox = SEGMENTED_TO_VIRTUAL(gNoHitbox);
            break;

        case 2017:
            gShowLevelClearStatusScreen = false;
            break;

        case 2040:
            gActors[5].state++;
            break;

        case 2080:
            gActors[6].state++;
            break;

        case 2130:
            gActors[7].state++;
            break;

        case 2160:
            gProjectFar = 30000.0f;
            player->hideShadow = true;
            Audio_StopPlayerNoise(0);
            AUDIO_PLAY_SFX(NA_SE_TANK_GO_UP, player->sfxSource, 0);
            break;

        case 2310:
            gActors[3].state++;
            break;

        case 2440:
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 60);
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 60);
            break;
    }

    // @port: Make the Great Fox carry the landmaster for real.
    if (gCsFrameCount >= 2300) {
        player->pos = gActors[3].obj.pos;
    }

    if (player->pathChangeTimer != 0) {
        player->pathChangeTimer--;
        Math_SmoothStepToF(&player->yRot_114, -player->pathChangeYaw, 0.03f, 0.5f, 0.0001f);
        Math_SmoothStepToF(&player->pathStep, gPathVelZ * .3f, 0.1f, 2.0f, 0.0001f);
        gPathVelX = Math_SmoothStepToF(&player->xPath, player->xPathTarget, 0.1f, player->pathStep, 0.0001f);
        gPathVelY = Math_SmoothStepToF(&player->yPath, player->yPathTarget, 0.1f, player->pathStep, 0.0001f);
    } else {
        Math_SmoothStepToF(&player->yRot_114, 0.0f, 0.03f, 0.5f, 0.0001f);
    }

    Math_SmoothStepToF(&player->cam.eye.x, gCsCamEyeX, D_ctx_80177A48[0], 20000.0f, 0);
    Math_SmoothStepToF(&player->cam.eye.y, gCsCamEyeY, D_ctx_80177A48[0], 20000.0f, 0);
    Math_SmoothStepToF(&player->cam.eye.z, gCsCamEyeZ, D_ctx_80177A48[0], 20000.0f, 0);
    Math_SmoothStepToF(&player->cam.at.x, gCsCamAtX, D_ctx_80177A48[0], 20000.0f, 0);
    Math_SmoothStepToF(&player->cam.at.y, gCsCamAtY, D_ctx_80177A48[0], 20000.0f, 0);
    Math_SmoothStepToF(&player->cam.at.z, gCsCamAtZ, D_ctx_80177A48[0], 20000.0f, 0);

    player->cam.at.y += zeroVar;

    if (player->csState >= 6) {
        player->cam.eye.y += gCameraShakeY * 10.0f;
    }

    if (gCsFrameCount > 2500) {
        gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
        gFillScreenAlphaTarget = 255;

        if (gFillScreenAlpha == 255) {
            player->state = PLAYERSTATE_NEXT;
            gFadeoutType = 4;
            Play_ClearObjectData();
            Audio_FadeOutAll(10);
            gLeveLClearStatus[LEVEL_MACBETH] = Play_CheckMedalStatus(150) + 1;
        }
    }
}

void Macbeth_801B28BC(ActorCutscene* this) {
    Vec3f sp5C;
    Vec3f sp50;
    Vec3f sp44;
    Player* player = &gPlayer[0];
    f32 sp3C;

    this->fwork[7] += 3.0f;
    this->rot_0F4.z = SIN_DEG(this->fwork[7]) * 1.5f;
    this->fwork[8] += 2.0f;
    sp3C = SIN_DEG(this->fwork[8]) * 10.0f;

    switch (this->state) {
        case 10:
            this->fwork[3] += D_i5_801BA854[4];

            Matrix_RotateY(gCalcMatrix, this->fwork[3] * M_DTOR, MTXF_NEW);

            sp5C.x = 0.0f;
            sp5C.y = D_i5_801BA874[4];
            sp5C.z = D_i5_801BA894[4];

            Math_SmoothStepToF(&D_i5_801BA894[4], 100.0f, 0.05f, 0.5f, 0.01f);
            Matrix_MultVec3f(gCalcMatrix, &sp5C, &sp44);

            this->fwork[0] = sp44.x;
            this->fwork[1] = sp44.y;
            this->fwork[2] = sp44.z - 100.0f;

            Math_SmoothStepToF(&this->obj.rot.z, SIN_DEG(this->fwork[3]) * -30.0f, 0.1f, 2.0f, 0.0f);
            Math_SmoothStepToF(&this->obj.pos.x, this->fwork[0] + player->pos.x, 0.03f, 10.0f, 0.0f);
            Math_SmoothStepToF(&this->obj.pos.y, this->fwork[1] + player->pos.y + sp3C, 0.03f, 10.0f, 0.0f);
            Math_SmoothStepToF(&this->obj.pos.z, this->fwork[2] + player->trueZpos, 0.03f, 10.0f, 0.0f);
            break;

        case 11:
            AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, this->sfxSource, 0);
            this->timer_0BC = 10;
            this->state++;
            this->fwork[29] = 5.0f;
            /* fallthrough */
        case 12:
            Math_SmoothStepToF(&this->obj.rot.z, 0.0f, 0.1f, 2.0f, 0.0f);
            Math_SmoothStepToF(&this->obj.pos.x, player->pos.x - 150.0f, 0.1f, 1.0f, 0.0f);

            this->iwork[11] = 2;

            Math_SmoothStepToF(&this->fwork[9], 20.0f, 0.1f, 2.0f, 0.0f);
            Math_SmoothStepToF(&this->obj.rot.z, 0.0f, 0.1f, 1.0f, 0.0f);

            if (this->timer_0BC <= 0) {
                this->timer_0BC = 10;
                this->state++;
            }
            break;

        case 13:
            Math_SmoothStepToF(&this->obj.pos.x, player->pos.x - 150.0f, 0.1f, 2.0f, 0.0f);
            Math_SmoothStepToF(&this->obj.rot.x, -120.0f, 0.1f, 5.0f, 0.0f);
            Math_SmoothStepToF(&this->fwork[9], -20.0f, 0.05f, 0.2f, 0.0f);

            this->fwork[29] = 3.0f;
            if (this->timer_0BC <= 0) {
                this->state++;
            }
            break;

        case 14:
            Math_SmoothStepToF(&this->obj.pos.x, player->pos.x - 150.0f, 0.1f, 3.0f, 0.0f);
            Math_SmoothStepToF(&this->obj.rot.x, -120.0f, 0.1f, 5.0f, 0.0f);
            Math_SmoothStepToF(&this->fwork[9], 22.0f, 0.05f, 0.2f, 0.0f);

            if (this->obj.rot.x <= -115.0f) {
                Math_SmoothStepToF(&this->obj.rot.z, 800.0f, 0.1f, 18.0f, 0.0f);
                Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
                Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);
                Matrix_RotateZ(gCalcMatrix, this->obj.rot.z * M_DTOR, MTXF_APPLY);
                sp5C.x = 0.0f;
                sp5C.y = 70.0f;
                sp5C.z = -70.0f;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp5C, &sp44);
                Effect_Effect393_Spawn(this->obj.pos.x + sp44.x, this->obj.pos.y + sp44.y, this->obj.pos.z + sp44.z,
                                       3.1f);
            }
            break;

        case 15:
            Math_SmoothStepToAngle(&this->obj.rot.z, 0.0f, 0.05f, 0.05f, 0);
            Math_SmoothStepToAngle(&this->obj.rot.y, 180.0f, 1.0f, 0.3f, 0);
            Math_SmoothStepToF(&this->obj.pos.y, player->pos.y + 240.0f, 0.03f, 20.0f, 0.0f);

            if (this->obj.rot.y == 180.0f) {
                this->state++;
            }
            break;

        case 16:
            this->fwork[0] += 2.0f;
            this->obj.rot.y = 180.0f - this->fwork[0];

            Math_SmoothStepToAngle(&this->obj.rot.z, 62.0f, 1.0f, 0.5f, 0);

            if (this->fwork[0] > 180.0f) {
                this->state++;
                AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, this->sfxSource, 0);
                this->timer_0BC = 160;
                this->fwork[29] = 5.0f;
            }
            break;

        case 17:
            Math_SmoothStepToAngle(&this->obj.rot.y, 345.0f, 1.0f, 0.5f, 0.01f);
            Math_SmoothStepToAngle(&this->obj.rot.x, 328.0f, 0.1f, 1.0f, 0.0f);
            Math_SmoothStepToF(&this->fwork[9], 35.0f, 0.1f, 0.5f, 0.0f);

            this->fwork[29] = 3.0f;

            Math_SmoothStepToF(&this->obj.rot.z, 405.0f, 0.1f, 10.0f, 0.0f);

            if (this->timer_0BC == 0) {
                Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
                Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);
                Matrix_RotateZ(gCalcMatrix, this->obj.rot.z * M_DTOR, MTXF_APPLY);
                sp5C.x = 0.0f;
                sp5C.y = 70.0f;
                sp5C.z = -70.0f;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp5C, &sp44);
                Effect_Effect393_Spawn(this->obj.pos.x + sp44.x, this->obj.pos.y + sp44.y, this->obj.pos.z + sp44.z,
                                       3.1f);
            }
            break;

        case 20:
            Math_SmoothStepToAngle(&this->obj.rot.x, 345.0f, 0.01f, this->fwork[4], 0.0f);
            Math_SmoothStepToF(&this->vel.z, -300.0f, 0.1f, 0.25f, 0.0f);
            break;

        case 21:
            Math_SmoothStepToF(&this->obj.rot.z, 0.0f, 0.1f, 0.25f, 0.0f);
            Math_SmoothStepToF(&this->obj.pos.x, player->pos.x, 0.1f, 5.0f, 0.0f);
            Math_SmoothStepToF(&this->obj.pos.y, 800.0f, 0.1f, 10.0f, 0.0f);
            break;

        case 22:
            Math_SmoothStepToAngle(&this->fwork[4], 0.25f, 0.1f, 0.005f, 0.0f);
            Math_SmoothStepToAngle(&this->obj.rot.x, 345.0f, 0.01f, this->fwork[4], 0.0f);
            break;

        case 30:
            this->fwork[3] += D_i5_801BA854[this->index];

            Matrix_RotateY(gCalcMatrix, this->fwork[3] * M_DTOR, MTXF_NEW);

            sp5C.x = 0.0f;
            sp5C.y = D_i5_801BA874[this->index];
            sp5C.z = D_i5_801BA894[this->index];

            Math_SmoothStepToF(&D_i5_801BA894[this->index], 250.0f, 0.05f, 0.5f, 0.01f);
            Matrix_MultVec3f(gCalcMatrix, &sp5C, &sp44);

            this->fwork[0] = sp44.x;
            this->fwork[1] = sp44.y;
            this->fwork[2] = sp44.z - 100.0f;

            Math_SmoothStepToF(&this->obj.rot.z, SIN_DEG(this->fwork[3]) * -30.0f, 0.1f, 2.0f, 0.0f);
            Math_SmoothStepToF(&this->obj.pos.x, this->fwork[0] + player->pos.x, 0.03f, 10.0f, 0.0f);
            Math_SmoothStepToF(&this->obj.pos.y, this->fwork[1] + player->pos.y + sp3C, 0.03f, 10.0f, 0.0f);
            Math_SmoothStepToF(&this->obj.pos.z, this->fwork[2] + player->trueZpos, 0.03f, 10.0f, 0.0f);
            break;

        case 31:
            AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, this->sfxSource, 0);
            this->drawShadow = false;
            this->timer_0BC = 20;
            this->state++;
            this->fwork[29] = 5.0f;
            /* fallthrough */
        case 32:
            if (this->timer_0BC <= 0) {
                this->drawShadow = true;
            }
            this->iwork[11] = 2;
            Math_SmoothStepToF(&this->obj.rot.x, -20.0f, 0.1f, 0.5f, 0.0f);
            Math_SmoothStepToF(&this->fwork[9], 25.0f, 0.1f, 2.0f, 0.0f);
            Math_SmoothStepToF(&this->obj.rot.z, 0.0f, 0.1f, 0.5f, 0.0f);
            break;
    }
    Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);

    sp5C.x = 0.0f;
    sp5C.y = 0.0f;
    sp5C.z = this->fwork[9];

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp5C, &sp50);

    this->vel.x = sp50.x;
    this->vel.y = sp50.y;
    this->vel.z = sp50.z;
}

f32 D_i5_801BA8B4[5] = { -100.0f, 380.0f, -450.0f, 0.0f, -340.0f };
f32 D_i5_801BA8C8[5] = { 500.0f, 400.0f, 850.0f, 650.0f, 950.0f };
f32 D_i5_801BA8DC[5] = { 500.0f, 500.0f, 600.0f, 2500.0f, 590.0f };
f32 D_i5_801BA8F0[4] = { 90.0f, -90.0f, 0.0f, 0.0f };

void Macbeth_LevelComplete1_TeamSetup(Actor* this, s32 teamIndex) {
    Player* player = &gPlayer[0];

    Actor_Initialize(this);

    this->obj.pos.x = player->pos.x + D_i5_801BA8B4[teamIndex];
    this->obj.pos.y = player->pos.y + D_i5_801BA8C8[teamIndex];
    this->obj.pos.z = player->pos.z + D_i5_801BA8DC[teamIndex];

    this->fwork[7] = RAND_FLOAT(360.0f);
    this->fwork[8] = RAND_FLOAT(360.0f);

    this->vel.x = player->vel.x;
    this->vel.y = player->vel.y;
    this->vel.z = player->vel.z;

    this->obj.status = OBJ_INIT;
    this->obj.id = OBJ_ACTOR_CUTSCENE;
    this->obj.rot.y = 180.0f;

    Object_SetInfo(&this->info, this->obj.id);

    if (teamIndex < 3) {
        this->iwork[11] = 1;
        this->drawShadow = true;
        this->fwork[3] = D_i5_801BA8F0[teamIndex];
        this->state = 30;
        AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, this->sfxSource, 4);
        return;
    }
    this->animFrame = ACTOR_CS_GREAT_FOX;
    this->state = 20;
    AUDIO_PLAY_SFX(NA_SE_GREATFOX_ENGINE, this->sfxSource, 0);
    this->fwork[9] = 20.0f;
}

f32 D_i5_801BA900 = 90.0f;

void Macbeth_801B3718(void) {
    ActorCutscene* actor = &gActors[8];

    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_CUTSCENE;
    actor->obj.pos.x = gPlayer[0].pos.x + D_i5_801BA8B4[4];
    actor->obj.pos.y = gPlayer[0].pos.y + D_i5_801BA8C8[4];
    actor->obj.pos.z = gPlayer[0].pos.z + D_i5_801BA8DC[4];

    actor->vel.x = gPlayer[0].vel.x;
    actor->vel.y = gPlayer[0].vel.y;
    actor->vel.z = gPlayer[0].vel.z;

    actor->fwork[7] = RAND_FLOAT(360.0f);
    actor->fwork[8] = RAND_FLOAT(360.0f);

    actor->rot_0F4.y = 180.0f;
    actor->rot_0F4.x = 0.0f;

    actor->obj.rot.x = -0.0f;
    actor->obj.rot.y = actor->rot_0F4.y;
    actor->obj.rot.z = -actor->rot_0F4.z;

    actor->fwork[0] = 30.0f;
    actor->animFrame = ACTOR_CS_KATT;
    actor->iwork[11] = 1;
    actor->state = 10;
    actor->fwork[3] = D_i5_801BA900;

    Object_SetInfo(&actor->info, actor->obj.id);
    AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, actor->sfxSource, 4);
}

void Macbeth_801B38E0(void) {
    s16 i;
    s16 j;

    for (i = 0; i < ARRAY_COUNT(gRadarMarks); i++) {
        gRadarMarks[i].enabled = false;
    }

    for (i = 0; i < ARRAY_COUNT(gTexturedLines); i++) {
        gTexturedLines[i].mode = 0;
    }

    for (i = 0; i < ARRAY_COUNT(gScenery); i++) {
        if ((gScenery[i].obj.id <= OBJ_SCENERY_MA_RAILROAD_SWITCH_8) ||
            (gScenery[i].obj.id >= OBJ_SCENERY_MA_TRAIN_TRACK_6)) {
            Object_Kill(&gScenery[i].obj, gScenery[i].sfxSource);
            Scenery_Initialize(&gScenery[i]);
        }
    }

    for (i = 0; i < ARRAY_COUNT(gSprites); i++) {
        gSprites[i].obj.status = OBJ_FREE;
        Sprite_Initialize(&gSprites[i]);
    }

    for (i = 0; i < ARRAY_COUNT(gActors); i++) {
        Object_Kill(&gActors[i].obj, gActors[i].sfxSource);
        Actor_Initialize(&gActors[i]);
    }

    for (i = 0; i < ARRAY_COUNT(gBosses); i++) {
        Object_Kill(&gBosses[i].obj, gBosses[i].sfxSource);
        Boss_Initialize(&gBosses[i]);
    }

    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        Object_Kill(&gEffects[i].obj, gEffects[i].sfxSource);
        Effect_Initialize(&gEffects[i]);
    }

    for (i = 0; i < ARRAY_COUNT(gItems); i++) {
        Object_Kill(&gItems[i].obj, gItems[i].sfxSource);
        Item_Initialize(&gItems[i]);
    }

    for (i = 0; i < ARRAY_COUNT(gPlayerShots); i++) {
        Object_Kill(&gPlayerShots[i].obj, gPlayerShots[i].sfxSource);
        PlayerShot_Initialize(&gPlayerShots[i]);
    }

    gDrawSmallRocks = D_ctx_801782BC = D_ctx_801782C0 = D_ctx_801782D0 = gBossActive = gKillEventActors =
        gGroundClipMode = gPrevEventActorIndex = gFormationLeaderIndex = gRingPassCount = 0;
    gFormationInitPos.x = gFormationInitPos.y = gFormationInitPos.z = gFormationInitRot.x = gFormationInitRot.y =
        gFormationInitRot.z = 0.0f;

    for (i = 0; i < ARRAY_COUNT(gTeamArrowsViewPos); i++) {
        gTeamArrowsViewPos[i].x = gTeamArrowsViewPos[i].y = gTeamArrowsViewPos[i].z = 100.0f;
    }

    for (i = 0; i < 2; i++) {
        gMeMoraStatus[i] = 0;
        for (j = 0; j < 100; j++) {
            gMeMoraYpos[i][j] = -5000.0f;
        }
    }
}

void Macbeth_LevelComplete1(Player* player) {
    f32 zeroVar = 0.0f;

    gCsCamEyeX = player->pos.x;
    gCsCamEyeY = player->pos.y;
    gCsCamEyeZ = player->pos.z + player->zPath + 50.0f;
    switch (player->csState) {
        case 0:
            gCsFrameCount = gBossActive = gLoadLevelObjects = 1;
            D_i5_801BA894[4] = 80.0f;
            D_i5_801BA894[3] = D_i5_801BA894[4];
            D_i5_801BA894[2] = D_i5_801BA894[4];
            D_i5_801BA894[1] = D_i5_801BA894[4];
            D_i5_801BA894[0] = D_i5_801BA894[4];

            gFillScreenRed = 255;
            gFillScreenGreen = 255;
            gFillScreenBlue = 255;
            gFillScreenAlpha = gFillScreenAlphaTarget = D_ctx_80177A10[9] = 0;

            D_ctx_80177A48[0] = 0.0f;
            player->csState++;
            /* fallthrough */
        case 1:
            D_i5_801BE240 = 2000.0f;
            D_i5_801BE244 = 2000.0f;
            D_i5_801BE248 = 2000.0f;

            Math_SmoothStepToF(D_ctx_80177A48, 0.1f, 1.0f, 0.01f, 0.0f);
            Math_SmoothStepToF(&player->baseSpeed, 4.9f, 0.1f, 1.0f, 0.0f);
            Math_SmoothStepToF(&player->camDist, 0.0f, 0.1f, 1.0f, 0.0f);

            gCsCamEyeX = player->pos.x;
            gCsCamEyeY = player->pos.y;
            gCsCamEyeZ = player->pos.z + player->zPath + 50.0f;

            if (gCsCamEyeY < 5.0f) {
                gCsCamEyeY = 5.0f;
            }

            gCsCamAtX = player->pos.x;
            gCsCamAtY = player->pos.y + 30.0f;
            gCsCamAtZ = player->pos.z + player->zPath;
            gFillScreenRed = 255;
            gFillScreenGreen = 255;
            gFillScreenBlue = 255;

            if (D_ctx_80177A10[9] >= 248) {
                D_ctx_80177A10[9] = 255;
            } else {
                D_ctx_80177A10[9] += 8;
            }

            gFillScreenAlpha = gFillScreenAlphaTarget = D_ctx_80177A10[9];

            if (gCsFrameCount > 40) {
                D_ctx_80177A10[9] = 255;
                player->cam.eye.x = gCsCamEyeX = 0.0f;
                player->cam.eye.y = gCsCamEyeY = 21.182106f;
                player->cam.eye.z = gCsCamEyeZ = -112.08748f;
                player->cam.at.x = gCsCamAtX = 0.0f;
                player->cam.at.y = gCsCamAtY = 22.873417f;
                player->cam.at.z = gCsCamAtZ = -283.55914f;
                player->csState++;
                player->pos.x = 0.0f;
                player->pos.y = -3.0f;
                player->camDist = 0.0f;
                Macbeth_801B38E0();
            }
            func_tank_80045130(player);
            func_tank_80044868(player);
            func_tank_80045678(player);
            func_tank_80045E7C(player);
            Player_CollisionCheck(player);
            Player_UpdatePath(player);
            break;

        case 2:
            Math_SmoothStepToF(D_ctx_80177A48, 0.01f, 0.1f, 0.01f, 0.0f);

            gCsCamEyeX = gCsCamAtX = player->pos.x;
            gCsCamEyeY = 3520.0f;
            gCsCamAtY = 0.0f;
            gCsCamEyeZ = 350.0f;
            gCsCamAtZ = -300.0f;

            D_i5_801BE240 = 2.0f;
            D_i5_801BE244 = 2.0f;
            D_i5_801BE248 = 2.0f;

            if (gCsFrameCount > 85) {
                gFillScreenAlphaTarget = gFillScreenAlpha = D_ctx_80177A10[9];
                D_ctx_80177A10[9] -= 10;
                if (D_ctx_80177A10[9] < 11) {
                    gFillScreenAlphaTarget = gFillScreenAlpha = 0;
                    player->csState = 10;
                }
            }

            func_tank_80045130(player);
            func_tank_80044868(player);
            func_tank_80045678(player);
            func_tank_80045E7C(player);
            Player_CollisionCheck(player);
            Player_UpdatePath(player);
            break;

        case 10:
            player->csState = 11;
            player->gravity = 3.0f;
            D_i5_801BE240 = 0.2f;
            /* fallthrough */
        case 11:
            Math_SmoothStepToF(D_ctx_80177A48, 0.01f, 0.1f, 0.01f, 0.0f);

            gCsCamEyeX = gCsCamAtX = player->pos.x;
            gCsCamEyeY = 3520.0f;
            gCsCamAtY = 0.0f;
            gCsCamEyeZ = 350.0f;

            if (gCsFrameCount < 1265) {
                gCsCamAtZ = -300.0f;
            } else {
                D_i5_801BE248 = 20.0f;
                gCsCamEyeZ = 1000.0f;
                gCsCamAtZ = -50000.0f;
            }
            if (gCsFrameCount < 270) {
                D_i5_801BE244 = 1.0f;
                D_i5_801BE248 = 1.0f;
            } else if (gCsFrameCount < 690) {
                Math_SmoothStepToF(&D_i5_801BE248, 0.3f, 0.1f, 0.1f, 0.01f);
                D_i5_801BE244 = 1.2f;
            } else {
                Math_SmoothStepToF(&D_i5_801BE244, 1.5f, 0.1f, 0.05f, 0.01f);
                Math_SmoothStepToF(&D_i5_801BE248, 2.0f, 0.1f, 0.1f, 0.01f);
            }

            Math_SmoothStepToF(&player->baseSpeed, 4.9f, 0.1f, 1.0f, 0.0f);
            Math_SmoothStepToF(&player->camDist, 0.0f, 0.1f, 1.0f, 0.0f);

            func_tank_80045130(player);
            func_tank_80044868(player);
            func_tank_80045678(player);
            func_tank_80045E7C(player);
            Player_CollisionCheck(player);
            Player_UpdatePath(player);
            break;

        case 12:
            break;
    }

    switch (gCsFrameCount) {
        case 755:
            gShowLevelClearStatusScreen = true;
            break;

        case 1025:
            gShowLevelClearStatusScreen = false;
            break;

        case 50:
            AUDIO_PLAY_BGM(NA_BGM_COURSE_CLEAR);
            break;

        case 100:
            gLevelClearScreenTimer = 100;
            break;

        case 160:
            Radio_PlayMessage(gMsg_ID_20010, RCID_FOX);
            break;

        case 230:
            if (gTeamShields[TEAM_ID_SLIPPY] > 0.0f) {
                Macbeth_LevelComplete1_TeamSetup(&gActors[0], 0);
            }
            break;

        case 260:
            switch (gTeamShields[TEAM_ID_SLIPPY]) {
                case 0:
                    Radio_PlayMessage(gMsg_ID_20345, RCID_ROB64);
                    break;
                case -1:
                    Radio_PlayMessage(gMsg_ID_20333, RCID_ROB64);
                    break;
                default:
                    func_demo_80048AC0(TEAM_ID_SLIPPY);
                    break;
            }
            break;

        case 380:
            if (gTeamShields[TEAM_ID_PEPPY] > 0.0f) {
                Macbeth_LevelComplete1_TeamSetup(&gActors[1], 1);
            }
            break;

        case 410:
            switch (gTeamShields[TEAM_ID_PEPPY]) {
                case 0:
                    Radio_PlayMessage(gMsg_ID_20344, RCID_ROB64);
                    break;
                case -1:
                    Radio_PlayMessage(gMsg_ID_20332, RCID_ROB64);
                    break;
                default:
                    func_demo_80048AC0(TEAM_ID_PEPPY);
                    break;
            }
            break;

        case 530:
            if (gTeamShields[TEAM_ID_FALCO] > 0.0f) {
                Macbeth_LevelComplete1_TeamSetup(&gActors[2], 2);
            }
            break;

        case 560:
            switch (gTeamShields[TEAM_ID_FALCO]) {
                case 0:
                    Radio_PlayMessage(gMsg_ID_20340, RCID_ROB64);
                    break;
                case -1:
                    Radio_PlayMessage(gMsg_ID_20331, RCID_ROB64);
                    break;
                default:
                    func_demo_80048AC0(TEAM_ID_FALCO);
                    break;
            }
            break;

        case 680:
            if (gLeveLClearStatus[LEVEL_ZONESS] != 0) {
                Macbeth_801B3718();
            }
            break;

        case 1027:
            if (gLeveLClearStatus[LEVEL_ZONESS] != 0) {
                Radio_PlayMessage(gMsg_ID_17350, RCID_KATT);
            }
            break;

        case 1065:
            if (gLeveLClearStatus[LEVEL_ZONESS] != 0) {
                gActors[8].state++;
            }
            break;

        case 1157:
            gActors[0].state++;
            break;

        case 1136:
            gActors[1].state++;
            break;

        case 1197:
            gActors[2].state++;
            break;

        case 1158:
            if (gLeveLClearStatus[LEVEL_ZONESS] != 0) {
                Object_Kill(&gActors[8].obj, gActors[8].sfxSource);
            }
            /* fallthrough */
        case 1195:
            gSceneSetup = 1;
            break;

        case 1200:
            Macbeth_LevelComplete1_TeamSetup(&gActors[3], 3);
            gLoadLevelObjects = 0;
            break;
    }
    Math_SmoothStepToF(&player->cam.eye.x, gCsCamEyeX, D_ctx_80177A48[0], D_i5_801BE240, 0.0f);
    Math_SmoothStepToF(&player->cam.eye.y, gCsCamEyeY, D_ctx_80177A48[0], D_i5_801BE244, 0.0f);
    Math_SmoothStepToF(&player->cam.eye.z, gCsCamEyeZ, D_ctx_80177A48[0], D_i5_801BE248, 0.0f);
    Math_SmoothStepToF(&player->cam.at.x, gCsCamAtX, D_ctx_80177A48[0], D_i5_801BE240, 0.0f);
    Math_SmoothStepToF(&player->cam.at.y, gCsCamAtY, D_ctx_80177A48[0], D_i5_801BE244, 0.0f);
    Math_SmoothStepToF(&player->cam.at.z, gCsCamAtZ, D_ctx_80177A48[0], D_i5_801BE248, 0.0f);
    player->cam.at.y += zeroVar;

    if ((gCsFrameCount >= 850) && ((gGameFrameCount % 16) == 0)) {
        Macbeth_EffectClouds_Spawn();
    }
    if (gCsFrameCount == 1220) {
        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 60);
        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 60);
    }
    if (gCsFrameCount > 1280) {
        gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
        gFillScreenAlphaTarget = 255;
        if (gFillScreenAlpha == 255) {
            player->state = PLAYERSTATE_NEXT;
            gFadeoutType = 4;
            Play_ClearObjectData();
            Audio_FadeOutAll(10);
            gLeveLClearStatus[LEVEL_MACBETH] = Play_CheckMedalStatus(150) + 1;
        }
    }
}
