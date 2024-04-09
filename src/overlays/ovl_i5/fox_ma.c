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

void Macbeth_801AD624(f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, s16, s16, f32);
bool Macbeth_801A0308(Actor*, f32, f32, u8);
void Macbeth_801AF200(f32, f32, f32, f32, f32, f32);
void Macbeth_801A015C(Actor*);
void Macbeth_8019D048(Actor*);
void Macbeth_8019FC54(Actor*, s32*, s32*, s32, s32, f32, f32, s32*);
void Macbeth_8019D670(f32, f32, f32, f32, f32, f32, f32, s32, u8);
void Macbeth_8019D910(Actor*, s32*, s32*, s32, f32, f32, s32*, s32*);
bool Macbeth_801AC5AC(s32, Gfx**, Vec3f*, Vec3f*, void*);
void Macbeth_801A49B8(Actor*);
void Macbeth_801ADCEC(f32, f32, f32, f32, f32, f32);
void Macbeth_801AE610(f32, f32, f32, f32, f32, f32, s16);
void Macbeth_801AE800(f32, f32, f32, f32, f32, f32);
void Macbeth_801ACF6C(void);

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
Vec3f D_i5_801BE6A0[6];
Vec3f D_i5_801BE6E8[6];
s32 D_i5_801BE734[4];

static UnkStruct_D_i5_801B8E50 D_i5_801B8E50[156] = {
    { 5174.4f, -2141.0f, 0.0f, 350.0f, OBJ_80_94 },    { 3401.4f, -1828.0f, 0.0f, 350.0f, OBJ_80_94 },
    { 1627.8999f, -1515.0f, 0.0f, 350.0f, OBJ_80_94 }, { -145.0f, -1202.0f, 0.0f, 350.0f, OBJ_80_96 },
    { -1933.0f, -1046.0f, 0.0f, 0.0f, OBJ_80_94 },     { -3733.0f, -1046.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -5533.0f, -1046.0f, 0.0f, 0.0f, OBJ_80_94 },     { -7333.0f, -1046.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -9133.0f, -1046.0f, 0.0f, 0.0f, OBJ_80_94 },     { -10933.0f, -1046.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -12733.0f, -1046.0f, 0.0f, 0.0f, OBJ_80_94 },    { -14533.0f, -1046.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -16333.0f, -1046.0f, 0.0f, 0.0f, OBJ_80_94 },    { -18133.0f, -1046.0f, 0.0f, 0.0f, OBJ_80_95 },
    { -19921.6f, -889.0f, 0.0f, 350.0f, OBJ_80_95 },   { -21656.4f, -423.0f, 0.0f, 340.0f, OBJ_80_96 },
    { -23390.7f, 40.0f, 0.0f, 350.0f, OBJ_80_96 },     { -25125.0f, 197.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -26925.0f, 197.0f, 0.0f, 0.0f, OBJ_80_96 },      { -28713.6f, 40.0f, 0.0f, 10.0f, OBJ_80_96 },
    { -30447.3f, -424.0f, 0.0f, 20.0f, OBJ_80_95 },    { -32181.3f, -889.0f, 0.0f, 10.0f, OBJ_80_95 },
    { -33971.1f, -1045.0f, 0.0f, 0.0f, OBJ_80_100 },   { -35771.1f, -1045.0f, 90.0f, 0.0f, OBJ_80_100 },
    { -37571.1f, -1045.0f, 180.0f, 0.0f, OBJ_80_100 }, { -39371.1f, -1045.0f, 270.0f, 0.0f, OBJ_80_100 },
    { -41171.1f, -1045.0f, 360.0f, 0.0f, OBJ_80_100 }, { -42971.1f, -1045.0f, 450.0f, 0.0f, OBJ_80_95 },
    { -44760.0f, -889.0f, 450.0f, 350.0f, OBJ_80_96 }, { -46547.9f, -733.0f, 450.0f, 0.0f, OBJ_80_94 },
    { -48347.5f, -733.0f, 450.0f, 0.0f, OBJ_80_95 },   { -50136.4f, -576.0f, 450.0f, 350.0f, OBJ_80_95 },
    { -51872.1f, -111.0f, 450.0f, 340.0f, OBJ_80_96 }, { -53606.4f, 352.0f, 450.0f, 350.0f, OBJ_80_96 },
    { -55395.4f, 509.0f, 450.0f, 0.0f, OBJ_80_96 },    { -57184.2f, 353.0f, 450.0f, 10.0f, OBJ_80_94 },
    { -58957.5f, 40.0f, 450.0f, 10.0f, OBJ_80_95 },    { -60746.9f, -115.0f, 450.0f, 0.0f, OBJ_80_94 },
    { -62548.2f, -114.0f, 450.0f, 0.0f, OBJ_80_101 },  { -64349.1f, -114.0f, 360.0f, 0.0f, OBJ_80_101 },
    { -66149.3f, -115.0f, 270.0f, 0.0f, OBJ_80_101 },  { -67950.3f, -115.0f, 180.0f, 0.0f, OBJ_80_101 },
    { -69751.2f, -115.0f, 90.0f, 0.0f, OBJ_80_101 },   { -71551.2f, -115.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -73351.0f, -116.0f, 0.0f, 0.0f, OBJ_80_96 },     { -75139.2f, -273.0f, 0.0f, 10.0f, OBJ_80_94 },
    { -76912.4f, -587.0f, 0.0f, 10.0f, OBJ_80_95 },    { -78702.0f, -743.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -80502.2f, -743.0f, 0.0f, 0.0f, OBJ_80_94 },     { -82302.2f, -743.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -84102.0f, -743.0f, 0.0f, 0.0f, OBJ_80_95 },     { -85890.6f, -586.0f, 0.0f, 350.0f, OBJ_80_96 },
    { -87679.9f, -431.0f, 0.0f, 0.0f, OBJ_80_94 },     { -89479.9f, -431.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -91279.9f, -431.0f, 0.0f, 0.0f, OBJ_80_94 },     { -93079.9f, -431.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -94879.9f, -431.0f, 0.0f, 0.0f, OBJ_80_94 },     { -96680.0f, -431.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -98480.0f, -431.0f, 0.0f, 0.0f, OBJ_80_94 },     { -100280.0f, -431.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -102079.9f, -431.0f, 0.0f, 0.0f, OBJ_80_94 },    { -103879.9f, -431.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -105679.9f, -431.0f, 0.0f, 0.0f, OBJ_80_94 },    { -107479.9f, -431.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -109279.9f, -431.0f, 0.0f, 0.0f, OBJ_80_94 },    { -111079.9f, -431.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -112879.9f, -431.0f, 0.0f, 0.0f, OBJ_80_94 },    { -114679.9f, -431.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -116479.9f, -431.0f, 0.0f, 0.0f, OBJ_80_94 },    { -118279.9f, -431.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -120079.9f, -431.0f, 0.0f, 0.0f, OBJ_80_94 },    { -121879.9f, -431.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -123679.9f, -431.0f, 0.0f, 0.0f, OBJ_80_94 },    { -125479.9f, -431.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -127279.9f, -431.0f, 0.0f, 0.0f, OBJ_80_95 },    { -129068.2f, -274.0f, 0.0f, 350.0f, OBJ_80_94 },
    { -130841.2f, 38.0f, 0.0f, 350.0f, OBJ_80_96 },    { -132630.4f, 194.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -134430.4f, 194.0f, 0.0f, 0.0f, OBJ_80_96 },     { -136219.4f, 37.0f, 0.0f, 10.0f, OBJ_80_95 },
    { -138009.0f, -119.0f, 0.0f, 0.0f, OBJ_80_96 },    { -139798.6f, -277.0f, 0.0f, 10.0f, OBJ_80_95 },
    { -141587.6f, -433.0f, 0.0f, 0.0f, OBJ_80_95 },    { -143376.3f, -276.0f, 0.0f, 350.0f, OBJ_80_94 },
    { -145149.0f, 35.0f, 0.0f, 350.0f, OBJ_80_96 },    { -146883.3f, 192.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -148683.3f, 192.0f, 0.0f, 0.0f, OBJ_80_96 },     { -150471.9f, 34.0f, 0.0f, 10.0f, OBJ_80_94 },
    { -152244.8f, -278.0f, 0.0f, 10.0f, OBJ_80_95 },   { -154034.2f, -434.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -155834.2f, -434.0f, 0.0f, 0.0f, OBJ_80_94 },    { -157634.2f, -434.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -159434.2f, -434.0f, 0.0f, 0.0f, OBJ_80_94 },    { -161234.2f, -434.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -163034.2f, -434.0f, 0.0f, 0.0f, OBJ_80_94 },    { -164834.2f, -434.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -166634.2f, -434.0f, 0.0f, 0.0f, OBJ_80_94 },    { -168435.2f, -435.0f, 0.0f, 0.0f, OBJ_80_95 },
    { -170223.8f, -278.0f, 0.0f, 350.0f, OBJ_80_94 },  { -171996.6f, 34.0f, 0.0f, 350.0f, OBJ_80_96 },
    { -173785.4f, 191.0f, 0.0f, 0.0f, OBJ_80_96 },     { -175574.2f, 33.0f, 0.0f, 10.0f, OBJ_80_95 },
    { -177364.0f, -123.0f, 0.0f, 0.0f, OBJ_80_94 },    { -179164.9f, -122.0f, 0.0f, 0.0f, OBJ_80_95 },
    { -180954.4f, 32.0f, 0.0f, 350.0f, OBJ_80_94 },    { -182727.1f, 345.0f, 0.0f, 350.0f, OBJ_80_96 },
    { -184515.8f, 501.0f, 0.0f, 0.0f, OBJ_80_96 },     { -186304.5f, 344.0f, 0.0f, 10.0f, OBJ_80_94 },
    { -188077.7f, 30.0f, 0.0f, 10.0f, OBJ_80_95 },     { -189866.6f, -125.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -191667.3f, -125.0f, 0.0f, 0.0f, OBJ_80_95 },    { -193455.9f, 31.0f, 0.0f, 350.0f, OBJ_80_96 },
    { -195245.1f, 187.0f, 0.0f, 0.0f, OBJ_80_95 },     { -197033.7f, 344.0f, 0.0f, 350.0f, OBJ_80_96 },
    { -198823.2f, 500.0f, 0.0f, 0.0f, OBJ_80_96 },     { -200612.3f, 343.0f, 0.0f, 10.0f, OBJ_80_94 },
    { -202385.6f, 30.0f, 0.0f, 10.0f, OBJ_80_95 },     { -204175.1f, -125.0f, 0.0f, 0.0f, OBJ_80_96 },
    { -205964.3f, -282.0f, 0.0f, 10.0f, OBJ_80_95 },   { -207754.0f, -440.0f, 0.0f, 0.0f, OBJ_80_95 },
    { -209542.5f, -283.0f, 0.0f, 350.0f, OBJ_80_94 },  { -211315.1f, 29.0f, 0.0f, 350.0f, OBJ_80_96 },
    { -213104.5f, 185.0f, 0.0f, 0.0f, OBJ_80_96 },     { -214893.4f, 28.0f, 0.0f, 10.0f, OBJ_80_95 },
    { -216683.2f, -128.0f, 0.0f, 0.0f, OBJ_80_95 },    { -218471.8f, 28.0f, 0.0f, 350.0f, OBJ_80_96 },
    { -220261.3f, 184.0f, 0.0f, 0.0f, OBJ_80_96 },     { -222050.1f, 27.0f, 0.0f, 10.0f, OBJ_80_95 },
    { -223839.6f, -129.0f, 0.0f, 0.0f, OBJ_80_94 },    { -225639.6f, -129.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -227439.6f, -129.0f, 0.0f, 0.0f, OBJ_80_94 },    { -229239.6f, -129.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -231039.6f, -129.0f, 0.0f, 0.0f, OBJ_80_94 },    { -232839.6f, -129.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -234639.6f, -129.0f, 0.0f, 0.0f, OBJ_80_94 },    { -236439.6f, -129.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -238239.6f, -129.0f, 0.0f, 0.0f, OBJ_80_94 },    { -240039.6f, -129.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -241839.6f, -129.0f, 0.0f, 0.0f, OBJ_80_94 },    { -243639.6f, -129.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -245439.6f, -129.0f, 0.0f, 0.0f, OBJ_80_94 },    { -247239.6f, -129.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -249039.6f, -129.0f, 0.0f, 0.0f, OBJ_80_94 },    { -250839.6f, -129.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -252639.6f, -129.0f, 0.0f, 0.0f, OBJ_80_94 },    { -254439.6f, -129.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -256240.5f, -129.0f, 0.0f, 0.0f, OBJ_80_94 },    { -258040.5f, -129.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -259840.5f, -129.0f, 0.0f, 0.0f, OBJ_80_94 },    { -261640.5f, -129.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -263440.5f, -129.0f, 0.0f, 0.0f, OBJ_80_94 },    { -265240.5f, -129.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -267040.5f, -129.0f, 0.0f, 0.0f, OBJ_80_94 },    { -268840.5f, -129.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -507035.0f, -319.0f, 0.0f, 0.0f, OBJ_80_94 },    { 0.0f, 0.0f, 0.0f, 0.0f, 0 },
};

static UnkStruct_D_i5_801B8E50 D_i5_801B9A80[86] = {
    { 5174.4f, -2141.0f, 0.0f, 350.0f, OBJ_80_94 },    { 3401.4f, -1828.0f, 0.0f, 350.0f, OBJ_80_94 },
    { 1627.8999f, -1515.0f, 0.0f, 350.0f, OBJ_80_94 }, { -145.0f, -1202.0f, 0.0f, 350.0f, OBJ_80_96 },
    { -1933.0f, -1046.0f, 0.0f, 0.0f, OBJ_80_94 },     { -3733.0f, -1046.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -5533.0f, -1046.0f, 0.0f, 0.0f, OBJ_80_94 },     { -7333.0f, -1046.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -9133.0f, -1046.0f, 0.0f, 0.0f, OBJ_80_94 },     { -10933.0f, -1046.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -12733.0f, -1046.0f, 0.0f, 0.0f, OBJ_80_94 },    { -14533.0f, -1046.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -16333.0f, -1046.0f, 0.0f, 0.0f, OBJ_80_94 },    { -18133.0f, -1046.0f, 0.0f, 0.0f, OBJ_80_95 },
    { -19921.6f, -889.0f, 0.0f, 350.0f, OBJ_80_95 },   { -21656.4f, -423.0f, 0.0f, 340.0f, OBJ_80_96 },
    { -23390.7f, 40.0f, 0.0f, 350.0f, OBJ_80_96 },     { -25125.0f, 197.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -26925.0f, 197.0f, 0.0f, 0.0f, OBJ_80_96 },      { -28713.6f, 40.0f, 0.0f, 10.0f, OBJ_80_96 },
    { -30447.3f, -424.0f, 0.0f, 20.0f, OBJ_80_95 },    { -32181.3f, -889.0f, 0.0f, 10.0f, OBJ_80_95 },
    { -33971.1f, -1045.0f, 0.0f, 0.0f, OBJ_80_100 },   { -35771.1f, -1045.0f, 90.0f, 0.0f, OBJ_80_100 },
    { -37571.1f, -1045.0f, 180.0f, 0.0f, OBJ_80_100 }, { -39371.1f, -1045.0f, 270.0f, 0.0f, OBJ_80_100 },
    { -41171.1f, -1045.0f, 360.0f, 0.0f, OBJ_80_100 }, { -42971.1f, -1045.0f, 450.0f, 0.0f, OBJ_80_95 },
    { -44760.0f, -889.0f, 450.0f, 350.0f, OBJ_80_96 }, { -46547.9f, -733.0f, 450.0f, 0.0f, OBJ_80_94 },
    { -48347.5f, -733.0f, 450.0f, 0.0f, OBJ_80_95 },   { -50136.4f, -576.0f, 450.0f, 350.0f, OBJ_80_95 },
    { -51872.1f, -111.0f, 450.0f, 340.0f, OBJ_80_96 }, { -53606.4f, 352.0f, 450.0f, 350.0f, OBJ_80_96 },
    { -55395.4f, 509.0f, 450.0f, 0.0f, OBJ_80_96 },    { -57184.2f, 353.0f, 450.0f, 10.0f, OBJ_80_94 },
    { -58957.5f, 40.0f, 450.0f, 10.0f, OBJ_80_95 },    { -60746.9f, -115.0f, 450.0f, 0.0f, OBJ_80_94 },
    { -62548.2f, -114.0f, 450.0f, 0.0f, OBJ_80_101 },  { -64349.1f, -114.0f, 360.0f, 0.0f, OBJ_80_101 },
    { -66149.3f, -115.0f, 270.0f, 0.0f, OBJ_80_101 },  { -67950.3f, -115.0f, 180.0f, 0.0f, OBJ_80_101 },
    { -69751.2f, -115.0f, 90.0f, 0.0f, OBJ_80_101 },   { -71551.2f, -115.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -73351.0f, -116.0f, 0.0f, 0.0f, OBJ_80_96 },     { -75139.2f, -273.0f, 0.0f, 10.0f, OBJ_80_94 },
    { -76912.4f, -587.0f, 0.0f, 10.0f, OBJ_80_95 },    { -78702.0f, -743.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -80502.2f, -743.0f, 0.0f, 0.0f, OBJ_80_94 },     { -82302.2f, -743.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -84102.0f, -743.0f, 0.0f, 0.0f, OBJ_80_95 },     { -85890.6f, -586.0f, 0.0f, 350.0f, OBJ_80_96 },
    { -87679.9f, -431.0f, 0.0f, 0.0f, OBJ_80_94 },     { -89479.9f, -431.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -91279.9f, -431.0f, 0.0f, 0.0f, OBJ_80_94 },     { -93079.9f, -431.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -94879.9f, -431.0f, 0.0f, 0.0f, OBJ_80_94 },     { -96680.0f, -431.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -98480.0f, -431.0f, 0.0f, 0.0f, OBJ_80_94 },     { -100280.0f, -431.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -102079.9f, -431.0f, 0.0f, 0.0f, OBJ_80_94 },    { -103879.9f, -431.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -105679.9f, -431.0f, 0.0f, 0.0f, OBJ_80_94 },    { -107479.9f, -431.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -109279.9f, -431.0f, 0.0f, 0.0f, OBJ_80_94 },    { -111079.9f, -431.0f, 0.0f, 0.0f, OBJ_80_94 },
    { -112879.9f, -431.0f, 0.0f, 0.0f, OBJ_80_94 },    { -114679.9f, -431.0f, 0.0f, 0.0f, OBJ_80_104 },
    { -116453.5f, -118.0f, 0.0f, 350.0f, OBJ_80_98 },  { -118188.5f, 346.0f, 0.0f, 340.0f, OBJ_80_98 },
    { -119815.5f, 1105.0f, 0.0f, 330.0f, OBJ_80_97 },  { -121374.3f, 2005.0f, 0.0f, 330.0f, OBJ_80_97 },
    { -122933.3f, 2905.0f, 0.0f, 330.0f, OBJ_80_97 },  { -124491.9f, 3806.0f, 0.0f, 330.0f, OBJ_80_97 },
    { -126051.4f, 4707.0f, 0.0f, 330.0f, OBJ_80_97 },  { -127609.9f, 5607.0f, 0.0f, 330.0f, OBJ_80_97 },
    { -129168.9f, 6507.0f, 0.0f, 330.0f, OBJ_80_97 },  { -130728.1f, 7408.0f, 0.0f, 330.0f, OBJ_80_97 },
    { -132287.2f, 8308.0f, 0.0f, 330.0f, OBJ_80_97 },  { -133846.4f, 9208.0f, 0.0f, 330.0f, OBJ_80_97 },
    { -135405.4f, 10109.0f, 0.0f, 330.0f, OBJ_80_97 }, { -136964.0f, 11009.0f, 0.0f, 330.0f, OBJ_80_97 },
    { -138522.9f, 11909.0f, 0.0f, 330.0f, OBJ_80_97 }, { -140082.1f, 12810.0f, 0.0f, 330.0f, OBJ_80_97 },
    { -507035.0f, -489.0f, 0.0f, 0.0f, OBJ_80_97 },    { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
};

static UnkStruct_D_i5_801B8E50 D_i5_801BA138[8] = {
    { -43605.8f, -1095.0f, 450.0f, -350.0f, 105 }, { -44786.7f, -884.0f, 450.0f, -350.0f, 105 },
    { -50739.8f, -519.0f, 450.0f, -340.0f, 105 },  { -51871.2f, -110.0f, 450.0f, -340.0f, 105 },
    { -84502.5f, 356.0f, 200.0f, -0.0f, 105 },     { -86080.9f, 352.0f, 200.0f, -0.0f, 105 },
    { -87278.9f, 347.0f, 200.0f, -0.0f, 105 },     { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
};

static u8 D_i5_801BA1D8 = 0;

static f32 D_i5_801BA1DC = 0.0f;
static f32 D_i5_801BA1E0 = 10000000.0f;
static u8 D_i5_801BA1E4 = 0;
u8 D_MA_801BA1E8 = 0;

static UnkStruct_D_i5_801BA1EC D_i5_801BA1EC[45] = {
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

static f32 D_i5_801BA570[5][10] = {
    { 450.0f, 350.0f, 250.0f, 150.0f, 50.0f, -50.0f, -150.0f, -250.0f, -350.0f, -450.0f },
    { 50.0f, -50.0f, 150.0f, -150.0f, 250.0f, -250.0f, 350.0f, -350.0f, 450.0f, -450.0f },
    { 50.0f, -50.0f, 250.0f, -250.0f, 150.0f, -150.0f, 350.0f, -350.0f, 450.0f, -450.0f },
    { 400.0f, 360.0f, 290.0f, 200.0f, 70.0f, -70.0f, -200.0f, -290.0f, -360.0f, -400.0f },
    { -200.0f, -100.0f, 0.0f, 100.0f, 200.0f, 400.0f, 300.0f, 200.0f, 100.0f, 0.0f },
};

static f32 D_i5_801BA638[5][10] = {
    { 1000.0f, 1000.0f, 1000.0f, 1000.0f, 1000.0f, 1000.0f, 1000.0f, 1000.0f, 1000.0f, 1000.0f },
    { 700.0f, 700.0f, 850.0f, 850.0f, 1000.0f, 1000.0f, 1150.0f, 1150.0f, 1300.0f, 1300.0f },
    { 1000.0f, 1000.0f, 1000.0f, 1000.0f, 1500.0f, 1500.0f, 1500.0f, 1500.0f, 1500.0f, 1500.0f },
    { 500.0f, 750.0f, 850.0f, 940.0f, 1000.0f, 1000.0f, 940.0f, 850.0f, 750.0f, 500.0f },
    { 700.0f, 850.0f, 1000.0f, 1150.0f, 1300.0f, 1800.0f, 1950.0f, 2100.0f, 2250.0f, 2400.0f },
};

static f32 D_i5_801BA700[] = { 610.0f, 0.0f }; // unused?

void Macbeth_80199920(void) {
    s16 i;

    D_i5_801BA1DC = -15.0f;
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

void Macbeth_80199A40(u8* arg0, u8* arg1, f32 arg2) {
    s32 pad;
    s32 i;
    s32 j;
    f32 var_fs0;
    f32 var_fs4;
    s32 temp_ft2;
    s32 temp_ft5;
    Vec3f sp80;
    Vec3f sp74;

    Matrix_Push(&gCalcMatrix);
    arg0 = LOAD_ASSET(arg0);
    arg1 = LOAD_ASSET(arg1);
    Matrix_RotateZ(gCalcMatrix, M_DTOR * arg2, 0);
    sp74.z = 0.0f;
    for (i = 0, var_fs4 = 0.0f; i < 32; i++, var_fs4++) {
        for (j = 0, var_fs0 = 0.0f; j < 32; j++, var_fs0++) {
            sp74.y = var_fs4 - 16.0f;
            sp74.x = var_fs0 - 16.0f;
            Matrix_MultVec3f(gCalcMatrix, &sp74, &sp80);
            temp_ft5 = (s32) (sp80.x + 16.0f);
            temp_ft2 = (s32) (sp80.y + 16.0f);
            if ((temp_ft5 >= 0) && (temp_ft5 < 32) && (temp_ft2 >= 0) && (temp_ft2 < 32)) {
                arg0[temp_ft5 + (temp_ft2 << 5)] = arg1[(i << 5) + j];
            }
        }
    }
    Matrix_Pop(&gCalcMatrix);
}

void Macbeth_80199C20(u8* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8* temp_v1;
    s32 i;
    s32 j;
    u8 a;
    u8 b;

    temp_v1 = LOAD_ASSET(arg0);

    for (i = arg3; i < arg3 + arg4; i++) {
        b = temp_v1[i];
        a = temp_v1[i + arg1];
        for (j = 1; j < arg2; j += 2) {
            temp_v1[arg1 * (j - 1) + i] = temp_v1[arg1 * (j + 1) + i];
            temp_v1[arg1 * j + i] = temp_v1[arg1 * (j + 2) + i];
        }

        temp_v1[((arg2 - 2) * arg1) + i] = b;
        temp_v1[((arg2 - 1) * arg1) + i] = a;
    }
}

void Macbeth_80199D88(u16* arg0, s32 arg1, s32 arg2) {
    u16* temp_t1;
    u16 a;
    s32 i;
    s32 j;

    temp_t1 = LOAD_ASSET(arg0);

    for (i = 0; i < arg1; i++) {
        a = temp_t1[(arg2 - 1) * arg1 + i];

        for (j = arg2; j > 0; j--) {
            temp_t1[j * arg1 + i] = temp_t1[(j - 1) * arg1 + i];
        }

        temp_t1[i] = a;
    }
}

void Macbeth_80199F8C(Actor* actor) {
    actor->state = 0;
    actor->iwork[1] = 0;
    actor->iwork[2] = 0;
    actor->iwork[3] = 0;
    actor->iwork[4] = 0;
    actor->iwork[5] = D_i5_801BA1E4;
    actor->iwork[7] = 0;
    actor->iwork[8] = 0;
    actor->iwork[9] = 0;
    actor->iwork[10] = 0;
    switch (actor->obj.id) {
        case OBJ_ACTOR_205:
            actor->health = 50;
            D_i5_801BE314 = actor->index;
            break;
        case OBJ_ACTOR_207:
            actor->health = 250;
            D_i5_801BE316 = actor->index;
            break;
        case OBJ_ACTOR_208:
            actor->health = 20;
            /* fallthrough */
        case OBJ_ACTOR_209:
            actor->health = 20;
            break;
        case OBJ_ACTOR_211:
            actor->health = 20;
            break;
        case OBJ_ACTOR_212:
            actor->health = 200;
            break;
        case OBJ_ACTOR_213:
            actor->health = 80;
            break;
        case OBJ_ACTOR_210:
            actor->health = 160;
        default:
            break;
    }

    actor->iwork[12] = 20;
    actor->iwork[13] = 0;
    actor->iwork[14] = 0;
    actor->iwork[16] = 20;
    actor->iwork[17] = 0;
    actor->iwork[18] = 0;
    actor->iwork[20] = 20;
    actor->iwork[21] = 0;
    actor->iwork[22] = 0;
    actor->iwork[23] = 0;
    actor->iwork[24] = 0;
    actor->iwork[11] = actor->health;
    actor->iwork[15] = actor->health;
    actor->iwork[19] = actor->health;
    actor->fwork[1] = 0.0f;
    actor->fwork[5] = 0.0f;
    actor->fwork[6] = 0.0f;
    actor->fwork[7] = 0.0f;
    actor->fwork[8] = 0.0f;
    actor->fwork[9] = 0.0f;
    actor->fwork[10] = 0.0f;
    actor->fwork[11] = 0.0f;
    actor->fwork[12] = 0.0f;
    actor->fwork[13] = 0.0f;
    actor->fwork[14] = 0.0f;
    actor->fwork[15] = 0.0f;
    actor->fwork[16] = 0.0f;
    actor->fwork[17] = 0.0f;
    actor->fwork[18] = 0.0f;
    actor->fwork[19] = 0.0f;
    actor->fwork[20] = 0.0f;
    actor->fwork[21] = 0.0f;
    actor->fwork[22] = 0.0f;
    actor->fwork[23] = 0.0f;
    actor->fwork[24] = 0.0f;
    actor->fwork[25] = 0.0f;
    actor->fwork[26] = 0.0f;
    actor->fwork[27] = 0.0f;
    actor->fwork[28] = 0.0f;
    actor->fwork[29] = 0.0f;
    D_i5_801BA1E4++;
}

void Macbeth_8019A128(void) {
    Macbeth_80199C20(D_MA_6023228, 16, 16, 0, 8);
    Macbeth_80199A40(D_MA_6023388, D_Tex_800DB4B8, gGameFrameCount * -20.0f);
}

void Macbeth_8019A198(Actor* actor) {
    if ((actor->iwork[5] >= D_i5_801BA1E4) || (actor->iwork[5] >= D_MA_801BE2F0[3])) {
        Math_SmoothStepToF(&actor->vel.z, 0.0f, 0.02f, 10.0f, 0.01f);
    } else {
        actor->vel.z = D_i5_801BA1DC;
        if ((actor->iwork[5] == D_MA_801BE2F0[3] - 1) || (actor->iwork[5] == D_i5_801BA1E4 - 1)) {
            if (D_i5_801BE310 != actor->iwork[5]) {
                if (actor->vel.z > -6.0f) {
                    func_8001CFA8(-6.0f);
                } else {
                    func_8001CFA8(actor->vel.z);
                }
                func_8001D10C(actor->sfxSource, 0x31078085);
                D_i5_801BE310 = actor->iwork[5];
            }
            D_i5_801BA1E0 = actor->obj.pos.z;
            if (D_i5_801BE313 != 0) {
                if (actor->vel.z > -6.0f) {
                    func_8001CFA8(-6.0f);
                } else {
                    func_8001CFA8(actor->vel.z);
                }
            }
        }
    }
}

void Macbeth_8019A2F4(Actor* actor) {
    f32 var_fa1 = 0.0f;
    f32 var_ft4 = 0.0f;
    u8 var_v0;
    s32 var_a0;

    for (var_v0 = D_MA_801BE2F0[0]; D_i5_801BA1EC[var_v0].unk_00 != -1.0f; var_v0++) {
        if (D_i5_801BA1EC[var_v0].unk_00 < gPlayer[0].unk_138) {
            var_a0 = var_v0;
            if (var_v0 == 0) {
                var_a0 = 1;
            }
            D_MA_801BE2F0[0] = var_a0;
            if (D_i5_801BA1E4 != D_i5_801BA1EC[var_a0 - 1].unk_04) {
                AUDIO_PLAY_SFX(0x1940205E, actor->sfxSource, 0);
            }
            D_i5_801BA1E4 = D_i5_801BA1EC[var_a0 - 1].unk_04;
            var_fa1 = D_i5_801BA1EC[var_a0 - 1].unk_08;
            var_ft4 = D_i5_801BA1EC[var_a0 - 1].unk_0C;
            D_MA_801BE2F0[4] = D_i5_801BA1EC[var_a0 - 1].unk_10;
            if (D_i5_801BA1EC[var_a0 - 1].unk_10 >= 300) {
                D_i5_801BE320[18] = (D_i5_801BA1EC[var_a0 - 1].unk_10 - 300);
            } else if (D_i5_801BA1EC[var_a0 - 1].unk_10 == 200) {
                if (D_i5_801BE320[16] == 0) {
                    D_i5_801BE320[16] = 1;
                }
            } else if (D_i5_801BA1EC[var_a0 - 1].unk_10 == 201) {
                D_i5_801BE320[17] = 1;
            } else if (D_i5_801BA1EC[var_a0 - 1].unk_10 == 202) {
                D_i5_801BE320[26] = 0;
            } else if (D_i5_801BA1EC[var_a0 - 1].unk_10 == 203) {
                D_i5_801BE320[26] = 1;
            } else if (D_i5_801BA1EC[var_a0 - 1].unk_10 >= 100) {
                D_MA_801BA1E8 = D_i5_801BA1EC[var_a0 - 1].unk_10;
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
    if (gPlayer[0].state_1C8 != PLAYERSTATE_1C8_7) {
        if (var_fa1 < (gPlayer[0].unk_138 - actor->obj.pos.z - (D_i5_801BA1E4 * 1416 - 1416))) {
            Math_SmoothStepToF(&D_i5_801BA1DC, -6.0f, 0.1f, 0.2f, 0.01f);
        }
        if ((gPlayer[0].unk_138 - actor->obj.pos.z - (D_i5_801BA1E4 * 1416 - 1416)) < var_ft4) {
            Math_SmoothStepToF(&D_i5_801BA1DC, -30.0f, 0.1f, 0.2f, 0.01f);
        }
        if ((D_i5_801BA1E4 < 5) && (gPlayer[0].unk_138 - actor->obj.pos.z > 4000.0f)) {
            Math_SmoothStepToF(&D_i5_801BA1DC, 0.0f, 0.1f, 1.0f, 0.01f);
        }
        if (gPlayer[0].unk_138 - actor->obj.pos.z > 25000.0f) {
            D_i5_801BA1DC = 0.0f;
        }
        if (gPlayer[0].unk_138 - actor->obj.pos.z < -8000.0f) {
            D_i5_801BA1DC = -200.0f;
        }
    }
}

void Macbeth_8019A728(Actor* actor) {
    f32 var_fv0;
    u32 var_v1;
    u8 var_v0;

    for (var_v0 = actor->iwork[2]; D_i5_801BA1EC[var_v0].unk_00 != -1.0f; var_v0++) {
        if (D_i5_801BA1EC[var_v0].unk_00 < actor->obj.pos.z) {
            var_v1 = var_v0;
            if (var_v0 == 0) {
                var_v1 = 1;
            }
            actor->iwork[2] = var_v1;
            if ((D_i5_801BA1EC[var_v1 - 1].unk_10 == actor->iwork[5]) && (actor->iwork[1] == 0)) {
                if (actor->obj.id == OBJ_ACTOR_212) {
                    actor->timer_0BC = 30;
                    Radio_PlayMessage(gMsg_ID_17476, RCID_BOSS_MACBETH);
                }
                actor->iwork[1] = 1;
            }
            break;
        }
    }
}

void Macbeth_8019A830(Actor* actor) {
    if ((gPlayer[0].unk_138 - actor->obj.pos.z) < -20000.0f) {
        Object_Kill(&actor->obj, actor->sfxSource);
    }
}

void Macbeth_8019A87C(Actor* actor) {
    if ((gPlayer[0].unk_138 - actor->obj.pos.z) < -2000.0f) {
        Object_Kill(&actor->obj, actor->sfxSource);
    }
}

void Macbeth_8019A8C8(Actor* actor, s16 arg1) {
    s32 i;

    func_effect_8007BFFC(actor->obj.pos.x + actor->fwork[25], actor->obj.pos.y + 290.0f, actor->obj.pos.z, 0.0f, 0.0f,
                         0.0f, 22.0f, 5);

    for (i = 0; i < 10; i++) {
        Macbeth_801AD624(actor->obj.pos.x + RAND_FLOAT_CENTERED(200.0f) + actor->fwork[21],
                         actor->obj.pos.y + 280.0f + RAND_FLOAT_CENTERED(100.0f),
                         actor->obj.pos.z - 420.0f + RAND_FLOAT(50.0f), RAND_FLOAT_CENTERED(10.0f),
                         RAND_FLOAT(7.0f) + 7.0f, RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT(360.0f), RAND_FLOAT(360.0f),
                         RAND_FLOAT(360.0f), RAND_FLOAT_CENTERED(30.0f), RAND_FLOAT_CENTERED(30.0f),
                         RAND_FLOAT_CENTERED(30.0f), (s32) (RAND_FLOAT(50.0f) + 70.0f), arg1, RAND_FLOAT(0.8f) + 0.3f);
        Macbeth_801AD624(actor->obj.pos.x + RAND_FLOAT_CENTERED(200.0f) + actor->fwork[25],
                         actor->obj.pos.y + 280.0f + RAND_FLOAT_CENTERED(100.0f), actor->obj.pos.z + RAND_FLOAT(50.0f),
                         RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT(7.0f) + 7.0f, RAND_FLOAT_CENTERED(10.0f),
                         RAND_FLOAT(360.0f), RAND_FLOAT(360.0f), RAND_FLOAT(360.0f), RAND_FLOAT_CENTERED(30.0f),
                         RAND_FLOAT_CENTERED(30.0f), RAND_FLOAT_CENTERED(30.0f), (s32) (RAND_FLOAT(50.0f) + 70.0f),
                         arg1, RAND_FLOAT(0.8f) + 0.3f);
        Macbeth_801AD624(actor->obj.pos.x + RAND_FLOAT_CENTERED(200.0f) + actor->fwork[23],
                         actor->obj.pos.y + 280.0f + RAND_FLOAT_CENTERED(100.0f),
                         actor->obj.pos.z + 420.0f + 100.0f + RAND_FLOAT(50.0f), RAND_FLOAT_CENTERED(10.0f),
                         RAND_FLOAT(7.0f) + 7.0f, RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT(360.0f), RAND_FLOAT(360.0f),
                         RAND_FLOAT(360.0f), RAND_FLOAT_CENTERED(30.0f), RAND_FLOAT_CENTERED(30.0f),
                         RAND_FLOAT_CENTERED(30.0f), (s32) (RAND_FLOAT(50.0f) + 70.0f), arg1, RAND_FLOAT(0.8f) + 0.3f);
    }
    AUDIO_PLAY_SFX(0x2940C00A, actor->sfxSource, 4);
}

void Macbeth_8019AF34(Actor* actor) {
    s32 i;

    func_effect_8007BFFC(actor->obj.pos.x + actor->fwork[25], actor->obj.pos.y + 290.0f, actor->obj.pos.z, 0.0f, 0.0f,
                         0.0f, 22.0f, 5);

    for (i = 0; i < 10; i++) {
        Macbeth_801AD624(actor->obj.pos.x + RAND_FLOAT_CENTERED(200.0f) + actor->fwork[21],
                         actor->obj.pos.y + 280.0f + RAND_FLOAT_CENTERED(100.0f),
                         actor->obj.pos.z - 420.0f + RAND_FLOAT(50.0f), RAND_FLOAT_CENTERED(50.0f),
                         RAND_FLOAT(30.0f) + 7.0f, RAND_FLOAT_CENTERED(30.0f), RAND_FLOAT(360.0f), RAND_FLOAT(360.0f),
                         RAND_FLOAT(360.0f), RAND_FLOAT_CENTERED(30.0f), RAND_FLOAT_CENTERED(30.0f),
                         RAND_FLOAT_CENTERED(30.0f), (s32) (RAND_FLOAT(50.0f) + 70.0f), 1, RAND_FLOAT(0.8f) + 0.3f);
        Macbeth_801AD624(actor->obj.pos.x + RAND_FLOAT_CENTERED(200.0f) + actor->fwork[25],
                         actor->obj.pos.y + 280.0f + RAND_FLOAT_CENTERED(100.0f), actor->obj.pos.z + RAND_FLOAT(50.0f),
                         RAND_FLOAT_CENTERED(45.0f), RAND_FLOAT(25.0f) + 7.0f, RAND_FLOAT_CENTERED(20.0f),
                         RAND_FLOAT(360.0f), RAND_FLOAT(360.0f), RAND_FLOAT(360.0f), RAND_FLOAT_CENTERED(30.0f),
                         RAND_FLOAT_CENTERED(30.0f), RAND_FLOAT_CENTERED(30.0f), (s32) (RAND_FLOAT(50.0f) + 70.0f), 1,
                         2.0f * (RAND_FLOAT(0.8f) + 0.3f));
        Macbeth_801AD624(actor->obj.pos.x + RAND_FLOAT_CENTERED(200.0f) + actor->fwork[23],
                         actor->obj.pos.y + 280.0f + RAND_FLOAT_CENTERED(100.0f),
                         actor->obj.pos.z + 420.0f + 100.0f + RAND_FLOAT(50.0f), RAND_FLOAT_CENTERED(40.0f),
                         RAND_FLOAT(35.0f) + 7.0f, RAND_FLOAT_CENTERED(20.0f), RAND_FLOAT(360.0f), RAND_FLOAT(360.0f),
                         RAND_FLOAT(360.0f), RAND_FLOAT_CENTERED(30.0f), RAND_FLOAT_CENTERED(30.0f),
                         RAND_FLOAT_CENTERED(30.0f), (s32) (RAND_FLOAT(50.0f) + 70.0f), 1, RAND_FLOAT(0.8f) + 0.3f);
    }
    AUDIO_PLAY_SFX(0x2940C00A, actor->sfxSource, 4);
}

void Macbeth_8019B580(Actor* actor, s32* arg1) {
    if (*arg1 > 10) {
        return;
    }
    if ((gGameFrameCount % 32U) == 0) {
        func_effect_8007D2C8(actor->obj.pos.x + RAND_FLOAT_CENTERED(200.0f) + actor->fwork[21],
                             actor->obj.pos.y + 280.0f + RAND_FLOAT_CENTERED(100.0f),
                             actor->obj.pos.z - 420.0f + RAND_FLOAT(50.0f), 10.0f);
    } else if ((gGameFrameCount % 32U) == 8) {
        func_effect_8007D2C8(actor->obj.pos.x + RAND_FLOAT_CENTERED(200.0f) + actor->fwork[25],
                             actor->obj.pos.y + 280.0f + RAND_FLOAT_CENTERED(100.0f),
                             actor->obj.pos.z + RAND_FLOAT(50.0f), 10.0f);
    } else if ((gGameFrameCount % 32U) == 16) {
        func_effect_8007D2C8(actor->obj.pos.x + RAND_FLOAT_CENTERED(200.0f) + actor->fwork[23],
                             actor->obj.pos.y + 280.0f + RAND_FLOAT_CENTERED(100.0f),
                             (actor->obj.pos.z + 320.0f) + RAND_FLOAT(50.0f), 10.0f);
    } else if ((gGameFrameCount % 32U) == 24) {
        func_effect_8007D2C8(actor->obj.pos.x + RAND_FLOAT_CENTERED(200.0f) + actor->fwork[25],
                             actor->obj.pos.y + 280.0f + RAND_FLOAT_CENTERED(100.0f),
                             actor->obj.pos.z + RAND_FLOAT(50.0f), 10.0f);
    }
    if ((u16) (gGameFrameCount % 4U) == 0) { // fake?
        func_effect_8007C120(actor->obj.pos.x + actor->fwork[25], actor->obj.pos.y + 350.0f, actor->obj.pos.z,
                             actor->vel.x, actor->vel.y, actor->vel.z, 0.2f, 10);
    }
}

void Macbeth_8019B8B0(Actor* actor) {
    if ((gGameFrameCount % 4U) == 0) {
        func_effect_8007D2C8(actor->obj.pos.x + RAND_FLOAT_CENTERED(200.0f) + actor->fwork[21],
                             actor->obj.pos.y + 280.0f + RAND_FLOAT_CENTERED(100.0f),
                             actor->obj.pos.z - 420.0f + RAND_FLOAT(50.0f), 20.0f);
    } else if ((gGameFrameCount % 4U) == 1) {
        func_effect_8007D2C8(actor->obj.pos.x + RAND_FLOAT_CENTERED(200.0f) + actor->fwork[25],
                             actor->obj.pos.y + 280.0f + RAND_FLOAT_CENTERED(100.0f),
                             RAND_FLOAT(50.0f) + actor->obj.pos.z, 20.0f);
    } else if ((gGameFrameCount % 4U) == 2) {
        func_effect_8007D2C8(actor->obj.pos.x + RAND_FLOAT_CENTERED(200.0f) + actor->fwork[23],
                             actor->obj.pos.y + 280.0f + RAND_FLOAT_CENTERED(100.0f),
                             RAND_FLOAT(50.0f) + (actor->obj.pos.z + 420.0f), 20.0f);
    } else if ((gGameFrameCount % 4U) == 3) {
        func_effect_8007D2C8(actor->obj.pos.x + RAND_FLOAT_CENTERED(200.0f) + actor->fwork[25],
                             actor->obj.pos.y + 280.0f + RAND_FLOAT_CENTERED(100.0f),
                             RAND_FLOAT(50.0f) + actor->obj.pos.z, 20.0f);
    }
    if ((gGameFrameCount % 4U) == 0) {
        func_effect_8007C120(actor->obj.pos.x + actor->fwork[25], actor->obj.pos.y + 350.0f, actor->obj.pos.z,
                             actor->vel.x, actor->vel.y, actor->vel.z, 0.2f, 20);
    }
}

void Macbeth_8019BBEC(Actor* actor) {
    if ((actor->timer_0BC % 16U) == 0) {
        func_effect_8007D2C8(actor->obj.pos.x + RAND_FLOAT_CENTERED(200.0f) + actor->fwork[21],
                             RAND_FLOAT_CENTERED(100.0f) + (actor->obj.pos.y + 100.0f),
                             RAND_FLOAT(50.0f) + (actor->obj.pos.z - 400.0f), 3.0f);
    } else if ((actor->timer_0BC % 16U) == 4) {
        func_effect_8007D2C8(actor->obj.pos.x + RAND_FLOAT_CENTERED(200.0f) + actor->fwork[25],
                             RAND_FLOAT_CENTERED(100.0f) + (actor->obj.pos.y + 100.0f),
                             RAND_FLOAT(50.0f) + actor->obj.pos.z, 3.0f);
    } else if ((actor->timer_0BC % 16U) == 8) {
        func_effect_8007D2C8(actor->obj.pos.x + RAND_FLOAT_CENTERED(200.0f) + actor->fwork[23],
                             RAND_FLOAT_CENTERED(100.0f) + (actor->obj.pos.y + 100.0f),
                             RAND_FLOAT(50.0f) + (actor->obj.pos.z + 450.0f), 3.0f);
    } else if ((actor->timer_0BC % 16U) == 12) {
        func_effect_8007C120(actor->obj.pos.x + actor->fwork[25], actor->obj.pos.y + 100.0f, actor->obj.pos.z,
                             actor->vel.x, actor->vel.y, actor->vel.z, 0.15f, 10);
    }
}

void Macbeth_8019BE50(Actor* actor) {
    s16 i;

    func_effect_8007BFFC(actor->obj.pos.x + actor->fwork[25], actor->obj.pos.y + 90.0f, actor->obj.pos.z, 0.0f, 0.0f,
                         0.0f, 10.0f, 5);
    func_effect_8007BFFC(actor->obj.pos.x + actor->fwork[23], actor->obj.pos.y + 90.0f,
                         actor->obj.pos.z + 420.0f + 300.0f, 0.0f, 0.0f, 0.0f, 10.0f, 5);

    for (i = 0; i < 10; i++) {
        Macbeth_801AD624(actor->obj.pos.x + RAND_FLOAT_CENTERED(200.0f) + actor->fwork[21],
                         actor->obj.pos.y + 80.0f + RAND_FLOAT_CENTERED(100.0f),
                         actor->obj.pos.z - 420.0f + RAND_FLOAT(50.0f), RAND_FLOAT_CENTERED(10.0f),
                         RAND_FLOAT(7.0f) + 7.0f, RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT(360.0f), RAND_FLOAT(360.0f),
                         RAND_FLOAT(360.0f), RAND_FLOAT_CENTERED(30.0f), RAND_FLOAT_CENTERED(30.0f),
                         RAND_FLOAT_CENTERED(30.0f), (s32) (RAND_FLOAT(50.0f) + 70.0f), 0, RAND_FLOAT(0.8f) + 0.3f);
        Macbeth_801AD624(actor->obj.pos.x + RAND_FLOAT_CENTERED(200.0f) + actor->fwork[25],
                         actor->obj.pos.y + 80.0f + RAND_FLOAT_CENTERED(100.0f), actor->obj.pos.z + RAND_FLOAT(50.0f),
                         RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT(10.0f) + 7.0f, RAND_FLOAT_CENTERED(10.0f),
                         RAND_FLOAT(360.0f), RAND_FLOAT(360.0f), RAND_FLOAT(360.0f), RAND_FLOAT_CENTERED(30.0f),
                         RAND_FLOAT_CENTERED(30.0f), RAND_FLOAT_CENTERED(30.0f), (s32) (RAND_FLOAT(50.0f) + 70.0f), 0,
                         (RAND_FLOAT(0.8f) + 0.3f));
        Macbeth_801AD624(actor->obj.pos.x + RAND_FLOAT_CENTERED(200.0f) + actor->fwork[23],
                         actor->obj.pos.y + 80.0f + RAND_FLOAT_CENTERED(100.0f),
                         actor->obj.pos.z + 420.0f + 100.0f + RAND_FLOAT(50.0f), RAND_FLOAT_CENTERED(10.0f),
                         RAND_FLOAT(7.0f) + 7.0f, RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT(360.0f), RAND_FLOAT(360.0f),
                         RAND_FLOAT(360.0f), RAND_FLOAT_CENTERED(30.0f), RAND_FLOAT_CENTERED(30.0f),
                         RAND_FLOAT_CENTERED(30.0f), (s32) (RAND_FLOAT(50.0f) + 70.0f), 0, RAND_FLOAT(0.8f) + 0.3f);
    }
    func_effect_8007A6F0(&actor->obj.pos, 0x2940C00A);
    gHitCount++;
}

bool Macbeth_8019C4EC(Actor* actor) {
    if (actor->unk_0D0 != 0) {
        actor->unk_0D0 = 0;
        if (actor->unk_0D2 == 1) {
            AUDIO_PLAY_SFX(0x29034003, actor->sfxSource, 4);
            actor->unk_0D0 = 0;
            actor->iwork[7] = 15;
            D_i5_801BE320[22] = 0;
            D_i5_801BE320[4] = 120;
            D_i5_801BE320[21] = 2;
            return true;
        }
        AUDIO_PLAY_SFX(0x29121007, actor->sfxSource, 4);
    }

    return false;
}

void Macbeth_8019C5B8(Actor* actor) {
    f32 var_ft4;

    Macbeth_801A0308(actor, actor->obj.pos.z + 520.0f, actor->obj.rot.y, 0);
    var_ft4 = RAND_FLOAT_CENTERED(12.0f);
    if ((var_ft4 > -2.0f) && (var_ft4 < 2.0f)) {
        if (var_ft4 >= 0.0f) {
            var_ft4 = 2.5f;
        } else {
            var_ft4 = -2.5f;
        }
    }
    Macbeth_801AF200(actor->fwork[19], actor->obj.pos.y + 300.0f, actor->obj.pos.z + 520.0f, var_ft4, 10.0f, 0.0f);
}

void Macbeth_8019C6C4(Actor* actor) {
    s32 var_a3;

    if (gBossFrameCount < 3840) {
        var_a3 = 10;
    } else if (gBossFrameCount < 5760) {
        var_a3 = 5;
    } else if (gBossFrameCount < 7680) {
        var_a3 = 2;
    } else {
        if (gBossFrameCount < 9600) {
            var_a3 = 1;
        } else {
            var_a3 = 0;
        }
    }
    if (var_a3 != 0) {
        BonusText_Display(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, var_a3);
    }
    gHitCount += var_a3 + 1;
    D_ctx_80177850 = 15;
}

void Macbeth_8019C778(Actor* actor) {
    if (actor->vel.z < -3.0f) {
        Macbeth_8019A128();
    }
    D_i5_801BE368[4] = actor->vwork[0].x + actor->obj.pos.x;
    D_i5_801BE368[5] = actor->vwork[0].y + actor->obj.pos.y;
    D_i5_801BE368[6] = actor->vwork[0].z + actor->obj.pos.z;
    Macbeth_8019A2F4(actor);
    Macbeth_8019A198(actor);
    Macbeth_801A015C(actor);
    Macbeth_8019A830(actor);
    switch (actor->state) {
        s32 unused;
        case 0:
            D_i5_801BE320[25] = 1;
            if ((D_i5_801BE320[9] <= 0) && (D_i5_801BE320[10] <= 0) && (D_i5_801BE320[17] != 0) &&
                (gPlayer[0].state_1C8 != PLAYERSTATE_1C8_7)) {
                D_i5_801BE320[30] = 0;
                actor->timer_0BC = 150;
                actor->timer_0BE = 200;
                D_i5_801BE320[19] = 1;
                actor->state++;
            }
            break;
        case 1:
            if (actor->timer_0BC == 1) {
                AUDIO_PLAY_SFX(0x1900000D, actor->sfxSource, 4);
            }
            if (actor->timer_0BC <= 0) {
                Math_SmoothStepToF(&actor->fwork[2], -60.0f, 0.4f, 10.0f, 0.01f);
                if (actor->timer_0BE == 30) {
                    Macbeth_8019C5B8(actor);
                    Radio_PlayMessage(gMsg_ID_17470, RCID_BOSS_MACBETH);
                }
                if ((actor->fwork[2] < -58.0f) && ((Macbeth_8019C4EC(actor) != 0) || (actor->timer_0BE <= 0))) {
                    actor->timer_0BC = 200;
                    D_i5_801BE320[19] = 0;
                    actor->state++;
                    AUDIO_PLAY_SFX(0x1900000E, actor->sfxSource, 4);
                }
            }
            break;
        case 2:
            Math_SmoothStepToF(&actor->fwork[2], 0.0f, 0.4f, 30.0f, 0.01f);
            if ((actor->timer_0BC <= 0) && (D_i5_801BE320[25] == 1)) {
                actor->timer_0BC = 60;
                actor->state++;
                AUDIO_PLAY_SFX(0x1900000D, actor->sfxSource, 4);
            }
            break;
        case 3:
            Math_SmoothStepToF(&actor->fwork[2], -60.0f, 0.4f, 10.0f, 0.01f);
            if ((actor->fwork[2] < -58.0f) && (Macbeth_8019C4EC(actor) != 0)) {
                actor->timer_0BC = 150;
                actor->state--;
                D_i5_801BE320[30]++;
                if (D_i5_801BE320[30] >= 2) {
                    D_i5_801BE320[30] = 0;
                    D_i5_801BE320[25] = 0;
                }
                AUDIO_PLAY_SFX(0x1900000E, actor->sfxSource, 4);
            }
            if (actor->timer_0BC <= 0) {
                D_i5_801BE320[30]++;
                if (D_i5_801BE320[30] >= 2) {
                    D_i5_801BE320[30] = 0;
                    D_i5_801BE320[25] = 0;
                }
                actor->timer_0BC = 100;
                actor->state--;
                AUDIO_PLAY_SFX(0x1900000E, actor->sfxSource, 4);
            }
            if (actor->timer_0BC == 30) {
                Macbeth_8019C5B8(actor);
            }
            break;
        case 4:
            Macbeth_8019AF34(actor);
            actor->health = 0;
            actor->timer_0BC = 200;
            gCameraShake = 30;
            actor->state++;
            break;
        case 5:
            if (actor->timer_0BC == 198) {
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = gFillScreenAlpha = 255;
            } else if (actor->timer_0BC == 197) {
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = gFillScreenAlpha = 0;
            }
            if (((actor->timer_0BC < 150) || (actor->timer_0BC > 170)) && (actor->timer_0BC > 80)) {
                Macbeth_8019B8B0(actor);
            }
            if (actor->timer_0BC == 160) {
                gShowBossHealth = 0;
                Radio_PlayMessage(gMsg_ID_17440, RCID_BOSS_MACBETH);
                func_effect_8007A568(actor->obj.pos.x + actor->fwork[25], actor->obj.pos.y, actor->obj.pos.z, 40.0f);
                Macbeth_8019C6C4(actor);
                actor->vel.z = 0.0f;
                gCameraShake = 25;
            }
            if (actor->timer_0BC == 100) {
                Object_Kill(&actor->obj, actor->sfxSource);
                if (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_3) {
                    gPlayer[0].state_1C8 = PLAYERSTATE_1C8_7;
                    gPlayer[0].unk_1D0 = 0;
                    gNextPlanetPath = 0;
                }
                actor->state++;
                Audio_KillSfxBySourceAndId(gPlayer[0].sfxSource, 0x1100000A);
                Audio_KillSfxBySourceAndId(gPlayer[0].sfxSource, 0x01004024);
            }
            break;
    }

    if (actor->unk_0D0 != 0) {
        actor->unk_0D0 = 0;
        AUDIO_PLAY_SFX(0x29121007, actor->sfxSource, 4);
    }

    if (D_i5_801BE320[4] > 0) {
        D_i5_801BE320[4]--;
    }
    actor->fwork[3] = 0.0f;
    if (D_i5_801BE320[21] != 0) {
        D_i5_801BE320[22]++;
        if (D_i5_801BE320[22] >= 30) {
            if (D_i5_801BE320[4] == 0) {
                D_i5_801BE320[21] = 0;
            }
            D_i5_801BE320[22] = 0;
        }
        if (((gGameFrameCount % 2) == 0)) {
            actor->fwork[3] = 15.0f;
        } else {
            actor->fwork[3] = -15.0f;
        }
    }
    D_i5_801BE320[20] = actor->state;
    if (D_i5_801BE320[23] != 0) {
        D_i5_801BE320[23] = 0;
        actor->state = 4;
    }
    if ((gPlayer[0].state_1C8 == PLAYERSTATE_1C8_7) && (gCsFrameCount > 630)) {
        Object_Kill(&actor->obj, actor->sfxSource);
    }
}

void Macbeth_8019CE88(Actor* actor) {
    switch (actor->state) {
        case 0:
            Macbeth_8019A198(actor);
            Macbeth_801A015C(actor);
            Macbeth_8019FC54(actor, &actor->iwork[10], &actor->iwork[11], 1, 1, actor->fwork[25], 0.0f,
                             &actor->iwork[13]);
            Macbeth_8019A728(actor);
            if (actor->iwork[1] != 0) {
                Macbeth_8019D048(actor);
            }
            Macbeth_8019A830(actor);
            break;
        case 1:
            if (actor->iwork[5] < D_MA_801BE2F0[3]) {
                D_MA_801BE2F0[3] = actor->iwork[5];
            }
            actor->state = 2;
            Macbeth_801A015C(actor);
            Macbeth_8019A830(actor);
            break;
        case 2:
            Macbeth_8019BBEC(actor);
            if (actor->timer_0BC == 0) {
                actor->timer_0BC = 60;
            }
            Math_SmoothStepToF(&actor->vel.z, 0.0f, 0.02f, 10.0f, 0.01f);
            Macbeth_801A015C(actor);
            Macbeth_8019A87C(actor);
            if (actor->unk_0D0 != 0) {
                actor->unk_0D0 = 0;
                actor->timer_0BC = 20;
                Macbeth_8019BE50(actor);
                actor->state = 3;
            }
            break;
        case 3:
            Macbeth_801A015C(actor);
            Math_SmoothStepToF(&actor->scale, 0.0f, 0.02f, 10.0f, 0.01f);
            if (actor->timer_0BC <= 0) {
                Object_Kill(&actor->obj, actor->sfxSource);
            }
            break;
    }
}

void Macbeth_8019D048(Actor* actor) {
    switch (actor->iwork[3]) {
        case 0:
            if (D_i5_801BE320[28] != 0) {
                D_i5_801BE320[28]--;
            }
            if (actor->fwork[25] == 0.0f) {
                if (D_i5_801BE320[28] <= 0) {
                    Radio_PlayMessage(gMsg_ID_17390, RCID_BOSS_MACBETH);
                    D_i5_801BE320[28] = 100;
                }
                if (actor->obj.pos.x <= gPlayer[0].pos.x) {
                    actor->iwork[4] = 1;
                } else {
                    actor->iwork[4] = -1;
                }
                actor->iwork[3]++;
            }
            break;
        case 1:
            Math_SmoothStepToF(&actor->fwork[4], actor->iwork[4] * -60.0f, 0.5f, 2.0f, 1.0f);
            if ((actor->fwork[4] < -30.0f) || (actor->fwork[4] > 30.0f)) {
                Macbeth_8019D670(actor->obj.pos.x + actor->fwork[25] + actor->iwork[4] * 73.0f,
                                 actor->obj.pos.y + actor->fwork[8] + 330.0f, actor->obj.pos.z, actor->iwork[4] * 70.0f,
                                 actor->vel.z, actor->iwork[4] * -34.0f, 0.0f, 2, 5);
                Macbeth_8019D670(actor->obj.pos.x + actor->fwork[25] + actor->iwork[4] * 74.0f,
                                 actor->obj.pos.y + actor->fwork[8] + 330.0f, actor->obj.pos.z - 350.0f,
                                 actor->iwork[4] * 38.0f, actor->vel.z, actor->iwork[4] * -34.0f, 0.0f, 4, 6);
                Macbeth_8019D670(actor->obj.pos.x + actor->fwork[25] + actor->iwork[4] * 74.0f,
                                 actor->obj.pos.y + actor->fwork[8] + 330.0f, actor->obj.pos.z + 350.0f,
                                 actor->iwork[4] * 40.0f, actor->vel.z, actor->iwork[4] * -35.0f, 0.0f, 0, 7);
                Macbeth_8019D670(actor->obj.pos.x + actor->fwork[25] + actor->iwork[4] * 35.0f,
                                 actor->obj.pos.y + actor->fwork[8] + 290.0f, actor->obj.pos.z - 175.0f,
                                 actor->iwork[4] * 20.0f, actor->vel.z, actor->iwork[4] * -35.0f, 0.0f, 12, 4);
                Macbeth_8019D670(actor->obj.pos.x + actor->fwork[25] + actor->iwork[4] * 35.0f,
                                 actor->obj.pos.y + actor->fwork[8] + 290.0f, actor->obj.pos.z + 175.0f,
                                 actor->iwork[4] * 35.0f, actor->vel.z, actor->iwork[4] * -35.0f, 0.0f, 14, 5);
                actor->iwork[3]++;
                actor->info.hitbox = LOAD_ASSET(D_MA_6035DD0);
            }
            break;
        case 2:
            Math_SmoothStepToF(&actor->fwork[4], actor->iwork[4] * -70.0f, 0.5f, 2.0f, 1.0f);
            actor->iwork[3]++;
            break;
        case 3:
            Math_SmoothStepToF(&actor->fwork[4], actor->iwork[4] * -70.0f, 0.2f, 2.0f, 0.0f);
            if ((actor->fwork[4] < -69.0f) || (actor->fwork[4] > 69.0f)) {
                actor->timer_0BC = 20;
                actor->iwork[3]++;
            }
            break;
        case 4:
            if (actor->timer_0BC == 0) {
                Math_SmoothStepToF(&actor->fwork[4], 0.0f, 0.02f, 2.0f, 0.0f);
            }
            break;
        default:
            break;
    }
}

void Macbeth_8019D5C8(Actor* actor, f32 xPos, f32 yPos, f32 zPos, f32 arg4, f32 zVel, f32 zRot, f32 yRot, s32 arg8,
                      u8 arg9) {
    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_215;
    actor->obj.pos.x = xPos;
    actor->obj.pos.y = yPos;
    actor->obj.pos.z = zPos;
    actor->obj.rot.z = zRot;
    actor->obj.rot.y = yRot;
    actor->timer_0BC = arg8;
    actor->timer_0BE = 20;
    actor->fwork[0] = arg4;
    actor->vel.z = zVel;
    actor->unk_046 = arg9;
    Object_SetInfo(&actor->info, actor->obj.id);
}

void Macbeth_8019D670(f32 xPos, f32 yPos, f32 zPos, f32 arg3, f32 zVel, f32 zRot, f32 yRot, s32 arg7, u8 arg8) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gActors); i++) {
        if (gActors[i].obj.status == OBJ_FREE) {
            Macbeth_8019D5C8(&gActors[i], xPos, yPos, zPos, arg3, zVel, zRot, yRot, arg7, arg8);
            break;
        }
    }
}

void Macbeth_8019D700(Actor* actor) {
    switch (actor->state) {
        case 0:
            Macbeth_8019A198(actor);
            Macbeth_801A015C(actor);
            Macbeth_8019D910(actor, &actor->iwork[10], &actor->iwork[11], 1, actor->fwork[21], -420.0f,
                             &actor->iwork[12], &actor->iwork[13]);
            Macbeth_8019D910(actor, &actor->iwork[14], &actor->iwork[15], 2, actor->fwork[25], 0.0f, &actor->iwork[16],
                             &actor->iwork[17]);
            Macbeth_8019D910(actor, &actor->iwork[18], &actor->iwork[19], 3, actor->fwork[23], 420.0f,
                             &actor->iwork[20], &actor->iwork[21]);
            Macbeth_8019A830(actor);
            break;
        case 1:
            if (actor->iwork[5] < D_MA_801BE2F0[3]) {
                D_MA_801BE2F0[3] = actor->iwork[5];
            }
            actor->state = 2;
            Macbeth_801A015C(actor);
            Macbeth_8019A830(actor);
            break;
        case 2:
            Macbeth_8019BBEC(actor);
            if (actor->timer_0BC == 0) {
                actor->timer_0BC = 60;
            }
            Math_SmoothStepToF(&actor->vel.z, 0.0f, 0.02f, 10.0f, 0);
            Macbeth_801A015C(actor);
            Macbeth_8019A830(actor);
            if (actor->unk_0D0 != 0) {
                actor->unk_0D0 = 0;
                actor->timer_0BC = 20;
                Macbeth_8019BE50(actor);
                actor->state = 3;
            }
            break;
        case 3:
            Macbeth_801A015C(actor);
            Math_SmoothStepToF(&actor->scale, 0.0f, 0.02f, 10.0f, 0.01f);
            if (actor->timer_0BC <= 0) {
                Object_Kill(&actor->obj, actor->sfxSource);
            }
            break;
    }
}

void Macbeth_8019D910(Actor* actor, s32* arg1, s32* arg2, s32 arg3, f32 arg4, f32 arg5, s32* arg6, s32* arg7) {
    s32 var_v0;
    u8 i;

    switch (*arg1) {
        case 0:
            if (((actor->unk_0D0 != 0) && (arg3 == actor->unk_0D2)) ||
                ((D_MA_801BE2F0[1] - 1 == actor->iwork[5]) && (actor->iwork[5] < D_MA_801BE2F0[3])) ||
                (((D_MA_801BE2F0[1] + 1) == actor->iwork[5]) && (D_MA_801BE2F0[3] < actor->iwork[5]))) {
                AUDIO_PLAY_SFX(0x29034003, actor->sfxSource, 4);
                actor->unk_0D0 = 0;
                func_effect_8007C120(actor->obj.pos.x + arg4, actor->obj.pos.y + 200.0f, actor->obj.pos.z + arg5,
                                     actor->vel.x, actor->vel.y, actor->vel.z, 0.15f, 20);
                actor->iwork[arg3 + 6] = 15;
                *arg2 -= actor->damage;
                if ((*arg2 <= 0) ||
                    ((D_MA_801BE2F0[1] - 1 == actor->iwork[5]) && (actor->iwork[5] < D_MA_801BE2F0[3])) ||
                    (((D_MA_801BE2F0[1] + 1) == actor->iwork[5]) && (D_MA_801BE2F0[3] < actor->iwork[5]))) {
                    (*arg1)++;
                }
            } else if ((actor->unk_0D0 != 0) && (actor->unk_0D2 == 0)) {
                actor->unk_0D0 = 0;
                AUDIO_PLAY_SFX(0x29121007, actor->sfxSource, 4);
            }
            break;
        case 1:
            func_effect_8007BFFC(actor->obj.pos.x + arg4, actor->obj.pos.y + 250.0f, actor->obj.pos.z + arg5, 0.0f,
                                 0.0f, 0.0f, 10.0f, 5);

            for (i = 0; i < 10; i++) {
                Macbeth_801AD624(
                    actor->obj.pos.x + arg4, actor->obj.pos.y + 200.0f, actor->obj.pos.z + arg5 + RAND_FLOAT(80.0f),
                    RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT(7.0f) + 7.0f, RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT(360.0f),
                    RAND_FLOAT(360.0f), RAND_FLOAT(360.0f), RAND_FLOAT_CENTERED(30.0f), RAND_FLOAT_CENTERED(30.0f),
                    RAND_FLOAT_CENTERED(30.0f), (s32) (RAND_FLOAT(50.0f) + 70.0f), 3, (RAND_FLOAT(0.8f) + 0.3f) * 2.0f);
            }

            AUDIO_PLAY_SFX(0x2903B009, actor->sfxSource, 4);
            *arg7 = 1;
            *arg2 = 20;
            (*arg1)++;
            break;
        case 2:
            if (((actor->unk_0D0 != 0) && (arg3 == actor->unk_0D2)) ||
                ((D_MA_801BE2F0[1] - 1 == actor->iwork[5]) && (actor->iwork[5] < D_MA_801BE2F0[3])) ||
                (((D_MA_801BE2F0[1] + 1) == actor->iwork[5]) && (D_MA_801BE2F0[3] < actor->iwork[5])) ||
                ((actor->obj.id == OBJ_ACTOR_209) && (arg3 == 2))) {
                AUDIO_PLAY_SFX(0x29034003, actor->sfxSource, 4);
                actor->unk_0D0 = 0;
                func_effect_8007C120(actor->obj.pos.x + arg4, actor->obj.pos.y + 200.0f, actor->obj.pos.z + arg5,
                                     actor->vel.x, actor->vel.y, actor->vel.z, 0.15f, 20);
                actor->iwork[arg3 + 6] = 20;
                *arg2 -= actor->damage;
                if ((*arg2 <= 0) ||
                    ((D_MA_801BE2F0[1] - 1 == (actor->iwork[5])) && (actor->iwork[5] < D_MA_801BE2F0[3])) ||
                    (((D_MA_801BE2F0[1] + 1) == actor->iwork[5]) && (D_MA_801BE2F0[3] < actor->iwork[5])) ||
                    ((actor->obj.id == OBJ_ACTOR_209) && (arg3 == 2))) {
                    gHitCount++;
                    (*arg1)++;
                }
            } else if ((actor->unk_0D0 != 0) && (actor->unk_0D2 == 0)) {
                actor->unk_0D0 = 0;
                AUDIO_PLAY_SFX(0x29121007, actor->sfxSource, 4);
            }
            break;
        case 3:
            func_effect_8007BFFC(actor->obj.pos.x + arg4, actor->obj.pos.y + 250.0f, actor->obj.pos.z + arg5, 0.0f,
                                 0.0f, 0.0f, 10.0f, 5);
            if ((actor->obj.id != OBJ_ACTOR_209) || (arg3 != 2)) {
                for (i = 0; i < 15; i++) {
                    Macbeth_801AD624(actor->obj.pos.x + arg4, actor->obj.pos.y + 200.0f,
                                     actor->obj.pos.z + arg5 + RAND_FLOAT(20.0f), RAND_FLOAT_CENTERED(10.0f),
                                     RAND_FLOAT(7.0f) + 7.0f, RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT(360.0f),
                                     RAND_FLOAT(360.0f), RAND_FLOAT(360.0f), RAND_FLOAT_CENTERED(30.0f),
                                     RAND_FLOAT_CENTERED(30.0f), RAND_FLOAT_CENTERED(30.0f),
                                     (s32) (RAND_FLOAT(50.0f) + 70.0f), 2, (RAND_FLOAT(0.8f) + 0.3f) * 1.5f);
                }
            }
            AUDIO_PLAY_SFX(0x2903B009, actor->sfxSource, 4);
            *arg7 = 2;
            var_v0 = arg3;
            if (var_v0 == 3) {
                var_v0 = 4;
            }

            actor->iwork[22] |= (var_v0);
            switch (actor->iwork[22]) {
                case 1:
                    actor->info.hitbox = LOAD_ASSET(D_MA_6035E68);
                    break;
                case 2:
                    actor->info.hitbox = LOAD_ASSET(D_MA_6035ECC);
                    break;
                case 3:
                    actor->info.hitbox = LOAD_ASSET(D_MA_6035F30);
                    break;
                case 4:
                    actor->info.hitbox = LOAD_ASSET(D_MA_6035F94);
                    break;
                case 5:
                    actor->info.hitbox = LOAD_ASSET(D_MA_6035FF8);
                    break;
                case 6:
                    actor->info.hitbox = LOAD_ASSET(D_MA_603605C);
                    break;
                case 7:
                    actor->state = 1;
                    actor->timer_0BC = 60;
                    actor->info.hitbox = LOAD_ASSET(D_MA_60359AC);
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

void Macbeth_8019E410(Actor* actor) {
    switch (actor->state) {
        case 0:
            Macbeth_8019A198(actor);
            Macbeth_801A015C(actor);
            Macbeth_8019D910(actor, &actor->iwork[10], &actor->iwork[11], 1, actor->fwork[21], -420.0f,
                             &actor->iwork[12], &actor->iwork[13]);
            Macbeth_8019D910(actor, &actor->iwork[14], &actor->iwork[15], 2, actor->fwork[25], 0.0f, &actor->iwork[16],
                             &actor->iwork[17]);
            Macbeth_8019D910(actor, &actor->iwork[18], &actor->iwork[19], 3, actor->fwork[23], 420.0f,
                             &actor->iwork[20], &actor->iwork[21]);
            Macbeth_8019A830(actor);
            break;
        case 1:
            if (actor->iwork[5] < D_MA_801BE2F0[3]) {
                D_MA_801BE2F0[3] = actor->iwork[5];
            }
            actor->state = 2;
            Macbeth_801A015C(actor);
            Macbeth_8019A830(actor);
            break;
        case 2:
            Macbeth_8019BBEC(actor);
            if (actor->timer_0BC == 0) {
                actor->timer_0BC = 60;
            }
            Math_SmoothStepToF(&actor->vel.z, 0.0f, 0.02f, 10.0f, 0.01f);
            Macbeth_801A015C(actor);
            Macbeth_8019A87C(actor);
            if (actor->unk_0D0 != 0) {
                actor->unk_0D0 = 0;
                actor->timer_0BC = 20;
                Macbeth_8019BE50(actor);
                actor->state = 3;
            }
            break;
        case 3:
            Macbeth_801A015C(actor);
            Math_SmoothStepToF(&actor->scale, 0.0f, 0.02f, 10.0f, 0.01f);
            if (actor->timer_0BC <= 0) {
                Object_Kill(&actor->obj, actor->sfxSource);
            }
            break;
    }
}
f32 D_i5_801BE240;
f32 D_i5_801BE244;
f32 D_i5_801BE248;
f32 D_i5_801BE24C;
void Macbeth_8019E624(Actor* actor, s32* arg1, s32* arg2, s32 arg3, f32 arg4, f32 arg5, s32* arg6) {
    switch (*arg1) {
        case 0:
            if (((actor->unk_0D0 != 0) && (arg3 == actor->unk_0D2)) ||
                ((D_MA_801BE2F0[1] - 1 == actor->iwork[5]) && (actor->iwork[5] < D_MA_801BE2F0[3])) ||
                (((D_MA_801BE2F0[1] + 1) == actor->iwork[5]) && (D_MA_801BE2F0[3] < actor->iwork[5]))) {
                AUDIO_PLAY_SFX(0x29034003, actor->sfxSource, 4);
                actor->unk_0D0 = 0;
                func_effect_8007C120(actor->obj.pos.x + arg4, actor->obj.pos.y + 200.0f, actor->obj.pos.z + arg5,
                                     actor->vel.x, actor->vel.y, actor->vel.z, 0.15f, 10);
                actor->iwork[7] = 15;
                *arg2 -= actor->damage;
                if ((*arg2 <= 0) ||
                    ((D_MA_801BE2F0[1] - 1 == actor->iwork[5]) && (actor->iwork[5] < D_MA_801BE2F0[3])) ||
                    (((D_MA_801BE2F0[1] + 1) == actor->iwork[5]) && (D_MA_801BE2F0[3] < actor->iwork[5]))) {
                    (*arg1)++;
                }
            } else if (actor->unk_0D0 != 0) {
                actor->unk_0D0 = 0;
                AUDIO_PLAY_SFX(0x29121007, actor->sfxSource, 4);
            }
            Macbeth_8019B580(actor, arg2);
            break;
        case 1:
            Macbeth_8019A8C8(actor, 5);
            *arg6 = 1;
            *arg2 = 80;
            (*arg1)++;
            break;
        case 2:
            if (((actor->unk_0D0 != 0) && (arg3 == actor->unk_0D2)) ||
                ((D_MA_801BE2F0[1] - 1 == actor->iwork[5]) && (actor->iwork[5] < D_MA_801BE2F0[3])) ||
                (((D_MA_801BE2F0[1] + 1) == actor->iwork[5]) && (D_MA_801BE2F0[3] < actor->iwork[5]))) {
                AUDIO_PLAY_SFX(0x29034003, actor->sfxSource, 4);
                actor->unk_0D0 = 0;
                func_effect_8007C120(actor->obj.pos.x + arg4, actor->obj.pos.y + 200.0f, actor->obj.pos.z + arg5,
                                     actor->vel.x, actor->vel.y, actor->vel.z, 0.2f, 10);
                actor->iwork[7] = 15;
                *arg2 -= actor->damage;
                if ((*arg2 <= 0) ||
                    ((D_MA_801BE2F0[1] - 1 == actor->iwork[5]) && (actor->iwork[5] < D_MA_801BE2F0[3])) ||
                    (((D_MA_801BE2F0[1] + 1) == actor->iwork[5]) && (D_MA_801BE2F0[3] < actor->iwork[5]))) {
                    gHitCount += 1;
                    (*arg1)++;
                }
            } else {
                if (actor->unk_0D0 != 0) {
                    actor->unk_0D0 = 0;
                    AUDIO_PLAY_SFX(0x29121007, actor->sfxSource, 4);
                }
            }
            break;
        case 3:
            Macbeth_8019A8C8(actor, 1);
            *arg6 = 2;
            actor->info.hitbox = LOAD_ASSET(D_MA_60359AC);
            (*arg1)++;
            actor->state = 1;
            break;
        case 4:
            break;
    }
}

void Macbeth_8019EA60(Actor* actor) {
    switch (actor->state) {
        case 0:
            Macbeth_8019A198(actor);
            Macbeth_801A015C(actor);
            Macbeth_8019E624(actor, &actor->iwork[10], &actor->iwork[11], 1, actor->fwork[25], 0.0f, &actor->iwork[13]);
            Macbeth_8019A830(actor);
            break;
        case 1:
            if (actor->iwork[5] < D_MA_801BE2F0[3]) {
                D_MA_801BE2F0[3] = actor->iwork[5];
            }
            Macbeth_801A015C(actor);
            Macbeth_8019A830(actor);
            actor->state = 2;
            break;
        case 2:
            Macbeth_8019BBEC(actor);
            if (actor->timer_0BC == 0) {
                actor->timer_0BC = 60;
            }
            Math_SmoothStepToF(&actor->vel.z, 0.0f, 0.02f, 10.0f, 0.01f);
            Macbeth_801A015C(actor);
            Macbeth_8019A87C(actor);
            if (actor->unk_0D0 != 0) {
                actor->unk_0D0 = 0;
                actor->timer_0BC = 20;
                Macbeth_8019BE50(actor);
                actor->state = 3;
                break;
            }
            break;
        case 3:
            Macbeth_801A015C(actor);
            Math_SmoothStepToF(&actor->scale, 0.0f, 0.02f, 10.0f, 0.01f);
            if (actor->timer_0BC <= 0) {
                Object_Kill(&actor->obj, actor->sfxSource);
            }
            break;
    }
}

void Macbeth_8019EBF8(Actor* actor, s32* arg1, s32* arg2, s32 arg3, f32 arg4, f32 arg5, s32* arg6) {
    switch (*arg1) {
        case 0:
            if (((actor->unk_0D0 != 0) && (arg3 == actor->unk_0D2)) ||
                ((D_MA_801BE2F0[1] - 1 == actor->iwork[5]) && (actor->iwork[5] < D_MA_801BE2F0[3])) ||
                (((D_MA_801BE2F0[1] + 1) == actor->iwork[5]) && (D_MA_801BE2F0[3] < actor->iwork[5]))) {
                AUDIO_PLAY_SFX(0x29034003, actor->sfxSource, 4);
                actor->unk_0D0 = 0;
                func_effect_8007C120(actor->obj.pos.x + arg4, actor->obj.pos.y + 200.0f, actor->obj.pos.z + arg5,
                                     actor->vel.x, actor->vel.y, actor->vel.z, 0.15f, 10);
                actor->iwork[7] = 15;
                *arg2 -= actor->damage;
                if ((*arg2 <= 0) ||
                    ((D_MA_801BE2F0[1] - 1 == actor->iwork[5]) && (actor->iwork[5] < D_MA_801BE2F0[3])) ||
                    (((D_MA_801BE2F0[1] + 1) == actor->iwork[5]) && (D_MA_801BE2F0[3] < actor->iwork[5]))) {
                    gHitCount++;
                    (*arg1)++;
                }
            } else if (actor->unk_0D0 != 0) {
                actor->unk_0D0 = 0;
                AUDIO_PLAY_SFX(0x29121007, actor->sfxSource, 4);
            }
            Macbeth_8019B580(actor, arg2);
            return;
        case 1:
            Macbeth_8019AF34(actor);
            *arg6 = 2;
            actor->info.hitbox = LOAD_ASSET(D_MA_60359AC);
            (*arg1)++;
            return;
        case 2:
            actor->state = 1;
            return;
    }
}

void Macbeth_8019EE68(Actor* actor) {
    switch (actor->state) {
        case 0:
            Macbeth_8019A198(actor);
            Macbeth_801A015C(actor);
            Macbeth_8019EBF8(actor, &actor->iwork[10], &actor->iwork[11], 1, actor->fwork[25], 0.0f, &actor->iwork[13]);
            Macbeth_8019A830(actor);
            break;
        case 1:
            if (actor->iwork[5] < D_MA_801BE2F0[3]) {
                D_MA_801BE2F0[3] = actor->iwork[5];
            }
            gFillScreenRed = gFillScreenGreen = gFillScreenBlue = gFillScreenAlpha = 255;
            gCameraShake = 35;
            if ((gPlayer[0].unk_138 - actor->obj.pos.z > -200.0f) && (gPlayer[0].unk_138 - actor->obj.pos.z < 200.0f) &&
                (gPlayer[0].pos.y - actor->obj.pos.y > -300.0f) && (gPlayer[0].pos.y - actor->obj.pos.y < 300.0f) &&
                (gPlayer[0].pos.x - actor->obj.pos.x > -800.0f) && (gPlayer[0].pos.x - actor->obj.pos.x < 800.0f)) {
                gFillScreenRed = gFillScreenAlpha = 255;
                gFillScreenGreen = gFillScreenBlue = 0;
                Player_ApplyDamage(&gPlayer[0], 0, 60);
            }
            Macbeth_801A015C(actor);
            Macbeth_8019A830(actor);
            D_ctx_801779A8[gMainController] = 100.0f;
            actor->state = 2;
            break;
        case 2:
            if (gCameraShake == 20) {
                D_MA_801BE2F0[1] = actor->iwork[5];
            }
            Macbeth_8019BBEC(actor);
            if (actor->timer_0BC == 0) {
                actor->timer_0BC = 60;
            }
            Math_SmoothStepToF(&actor->vel.z, 0.0f, 0.02f, 10.0f, 0.01f);
            Macbeth_801A015C(actor);
            Macbeth_8019A87C(actor);
            if (gCameraShake == 20) {
                actor->unk_0D0 = 0;
                actor->timer_0BC = 20;
                Macbeth_8019BE50(actor);
                actor->state = 3;
            }
            break;
        case 3:
            Macbeth_801A015C(actor);
            Math_SmoothStepToF(&actor->scale, 0.0f, 0.02f, 10.0f, 0.01f);
            if (actor->timer_0BC <= 0) {
                Object_Kill(&actor->obj, actor->sfxSource);
            }
            break;
    }
}

void Macbeth_8019F164(Actor* actor) {
    static Vec3f D_i5_801BA708 = { 0.0f, 610.0f, 0.0f };
    static Vec3f D_i5_801BA714 = { 0.0f, 0.0f, 65.0f };
    Vec3f sp84;
    Vec3f sp78;
    Vec3f sp6C;
    Vec3f sp60;
    Vec3f sp54;
    Vec3f sp48;
    s16 i;
    s16 sp44;

    sp44 = 0;
    sp6C.x = gPlayer[0].pos.x - actor->obj.pos.x + actor->fwork[25];
    sp6C.y = gPlayer[0].pos.y - 25.0f - actor->obj.pos.y + actor->fwork[8] + 25.0f;
    sp6C.z = gPlayer[0].unk_138 - 500.0f - actor->obj.pos.z;

    for (i = 0; i < 60; i++) {
        if ((gActors[i].obj.id == OBJ_ACTOR_219) && (gActors[i].obj.status == OBJ_ACTIVE)) {
            if ((actor->obj.pos.z < (gActors[i].obj.pos.z + 3000.0f)) &&
                ((gActors[i].obj.pos.z - actor->obj.pos.z) < 5000.0f)) {
                sp6C.x = gActors[i].obj.pos.x - actor->obj.pos.x + actor->fwork[25];
                sp6C.y = gActors[i].obj.pos.y - actor->obj.pos.y + actor->fwork[8] + 25.0f;
                sp6C.z = gActors[i].obj.pos.z + 300.0f - actor->obj.pos.z;
                sp44 = 1;
            }
            break;
        }
    }
    if ((actor->iwork[4] == 0) || (sp44 != 0)) {
        Matrix_RotateZ(gCalcMatrix, -actor->obj.rot.z * M_DTOR, 0);
        Matrix_RotateX(gCalcMatrix, -(actor->obj.rot.x + actor->fwork[29]) * M_DTOR, 1);
        Matrix_RotateY(gCalcMatrix, -(actor->obj.rot.y + actor->fwork[26]) * M_DTOR, 1);
        Matrix_MultVec3f(gCalcMatrix, &sp6C, &sp84);
        sp78.x = sp84.x - D_i5_801BA708.x;
        sp78.y = sp84.y - D_i5_801BA708.y;
        sp78.z = sp84.z - D_i5_801BA708.z;
        Math_SmoothStepToAngle(&actor->fwork[4], Math_RadToDeg(Math_Atan2F(sp78.x, sp78.z)), 0.1f, 2.0f, 0.01f);
        Math_SmoothStepToAngle(&actor->fwork[3], Math_RadToDeg(-Math_Atan2F(sp78.y, sqrtf(SQ(sp78.x) + SQ(sp78.z)))),
                               0.1f, 2.0f, 0.01f);

        if ((actor->fwork[4] > 120.0f) && (actor->fwork[4] < 180.0f)) {
            actor->fwork[4] = 120.0f;
        }
        if ((actor->fwork[4] < 240.0f) && (actor->fwork[4] > 180.0f)) {
            actor->fwork[4] = 240.0f;
        }

        if ((actor->fwork[3] > 60.0f) && (actor->fwork[3] < 180.0f)) {
            actor->fwork[3] = 60.0f;
        }
        if ((actor->fwork[3] < 300.0f) && (actor->fwork[3] > 180.0f)) {
            actor->fwork[3] = 300.0f;
        }
    }
    Math_SmoothStepToAngle(&actor->fwork[2], actor->fwork[4], 0.2f, 5.0f, 0.01f);
    Math_SmoothStepToAngle(&actor->fwork[1], actor->fwork[3], 0.2f, 5.0f, 0.01f);
    Matrix_RotateY(gCalcMatrix, (actor->obj.rot.y + actor->fwork[26]) * M_DTOR, 0);
    Matrix_RotateX(gCalcMatrix, (actor->obj.rot.x + actor->fwork[29]) * M_DTOR, 1);
    Matrix_RotateZ(gCalcMatrix, actor->obj.rot.z * M_DTOR, 1);
    Matrix_MultVec3f(gCalcMatrix, &D_i5_801BA708, &sp84);
    sp60.x = sp84.x + actor->obj.pos.x + actor->fwork[25];
    sp60.y = sp84.y + actor->obj.pos.y + actor->fwork[8] + 25.0f;
    sp60.z = sp84.z + actor->obj.pos.z;
    sp54.x = actor->fwork[1];
    sp54.y = actor->fwork[2];
    sp54.z = 0.0f;
    sp48.x = actor->obj.rot.x + actor->fwork[29];
    sp48.y = actor->obj.rot.y + actor->fwork[26];
    sp48.z = actor->obj.rot.z;
    switch (actor->iwork[4]) {
        case 0:
            if (sp44 != 0) {
                sp60.x -= 60.0f;
                func_effect_8007EE68(OBJ_EFFECT_378, &sp60, &sp54, &sp48, &D_i5_801BA714, 1.0f);
                AUDIO_PLAY_SFX(0x2903101B, actor->sfxSource, 4);
                actor->iwork[4]++;
            } else if ((D_i5_801BE310 == actor->iwork[5]) ||
                       ((gPlayer[0].pos.x - actor->obj.pos.x > 300.0f) &&
                        (gPlayer[0].pos.x - actor->obj.pos.x < 3000.0f)) ||
                       ((gPlayer[0].pos.x - actor->obj.pos.x < -300.0f) &&
                        (gPlayer[0].pos.x - actor->obj.pos.x > -3000.0f))) {
                if ((gPlayer[0].unk_138 - actor->obj.pos.z < 5000.0f) &&
                    (gPlayer[0].unk_138 - actor->obj.pos.z > 200.0f) && (actor->timer_0BC == 0) &&
                    (actor->health != 0)) {
                    sp60.x -= 60.0f;
                    func_effect_8007EE68(OBJ_EFFECT_378, &sp60, &sp54, &sp48, &D_i5_801BA714, 1.0f);
                    AUDIO_PLAY_SFX(0x2903101B, actor->sfxSource, 4);
                    actor->iwork[4]++;
                }
            }
            break;
        case 1:
            Math_SmoothStepToF(&actor->fwork[0], -100.0f, 0.8f, 30.0f, 20.0f);
            if (actor->fwork[0] <= -100.0f) {
                actor->iwork[4]++;
            }
            break;
        case 2:
            Math_SmoothStepToF(&actor->fwork[0], 0.0f, 0.6f, 30.0f, 0.2f);
            if (actor->fwork[0] >= 0.0f) {
                if (sp44 == 0) {
                    actor->timer_0BC = 15;
                }
                actor->iwork[4]++;
            }
            break;
        case 3:
            if ((actor->timer_0BC == 0) && (actor->health != 0)) {
                func_effect_8007EE68(OBJ_EFFECT_378, &sp60, &sp54, &sp48, &D_i5_801BA714, 1.0f);
                AUDIO_PLAY_SFX(0x2903101B, actor->sfxSource, 4);
                actor->iwork[4]++;
            }
            break;
        case 4:
            Math_SmoothStepToF(&actor->fwork[0], -100.0f, 0.8f, 30.0f, 20.0f);
            if (actor->fwork[0] <= -100.0f) {
                actor->iwork[4]++;
            }
            break;
        case 5:
            Math_SmoothStepToF(&actor->fwork[0], 0.0f, 0.6f, 30.0f, 0.2f);
            if (actor->fwork[0] >= 0.0f) {
                if (sp44 == 0) {
                    actor->timer_0BC = 15;
                }
                actor->iwork[4]++;
            }
            break;
        case 6:
            if ((actor->timer_0BC == 0) && (actor->health != 0)) {
                sp60.x += 60.0f;
                func_effect_8007EE68(OBJ_EFFECT_378, &sp60, &sp54, &sp48, &D_i5_801BA714, 1.0f);
                AUDIO_PLAY_SFX(0x2903101B, actor->sfxSource, 4);
                actor->iwork[4]++;
            }
            break;
        case 7:
            Math_SmoothStepToF(&actor->fwork[0], -100.0f, 0.8f, 30.0f, 20.0f);
            if (actor->fwork[0] <= -100.0f) {
                actor->iwork[4]++;
            }
            break;
        case 8:
            Math_SmoothStepToF(&actor->fwork[0], 0.0f, 0.6f, 30.0f, 0.2f);
            if (actor->fwork[0] >= 0.0f) {
                if (sp44 == 0) {
                    actor->timer_0BC = (u32) (RAND_FLOAT(100.0f) + 50.0f);
                }
                actor->iwork[4] = 0;
            }
            break;
        default:
            break;
    }
}

void Macbeth_8019FC54(Actor* actor, s32* arg1, s32* arg2, s32 arg3, s32 arg4, f32 arg5, f32 arg6, s32* arg7) {
    switch (*arg1) {
        case 0:
            if (((actor->unk_0D0 != 0) && (actor->unk_0D2 >= arg3) && (arg4 >= actor->unk_0D2)) ||
                ((D_MA_801BE2F0[1] - 1 == actor->iwork[5]) && (actor->iwork[5] < D_MA_801BE2F0[3])) ||
                (((D_MA_801BE2F0[1] + 1) == actor->iwork[5]) && (D_MA_801BE2F0[3] < actor->iwork[5]))) {
                AUDIO_PLAY_SFX(0x29034003, actor->sfxSource, 4);
                actor->unk_0D0 = 0;
                func_effect_8007C120(actor->obj.pos.x + arg5, actor->obj.pos.y + 200.0f, actor->obj.pos.z + arg6,
                                     actor->vel.x, actor->vel.y, actor->vel.z, 0.15f, 10);
                actor->iwork[7] = 15;
                *arg2 -= actor->damage;
                if ((*arg2 <= 0) ||
                    ((D_MA_801BE2F0[1] - 1 == actor->iwork[5]) && (actor->iwork[5] < D_MA_801BE2F0[3])) ||
                    (((D_MA_801BE2F0[1] + 1) == actor->iwork[5]) && (D_MA_801BE2F0[3] < actor->iwork[5]))) {
                    gHitCount++;
                    if ((actor->obj.id == OBJ_ACTOR_210) && (actor->iwork[3] < 2)) {
                        gHitCount += 5;
                    }
                    (*arg1)++;
                }
            } else if (actor->unk_0D0 != 0) {
                actor->unk_0D0 = 0;
                AUDIO_PLAY_SFX(0x29121007, actor->sfxSource, 4);
            }
            Macbeth_8019B580(actor, arg2);
            break;
        case 1:
            Macbeth_8019A8C8(actor, 6);
            if (actor->obj.id == OBJ_ACTOR_212) {
                func_effect_8007BFFC(actor->obj.pos.x + actor->fwork[25], actor->obj.pos.y + 360.0f, actor->obj.pos.z,
                                     0.0f, 0.0f, 0.0f, 20.0f, 20);
                func_effect_8007BFFC(actor->obj.pos.x + actor->fwork[25], actor->obj.pos.y + 660.0f, actor->obj.pos.z,
                                     0.0f, 0.0f, 0.0f, 20.0f, 20);
            }
            *arg7 = 2;
            actor->info.hitbox = LOAD_ASSET(D_MA_60359AC);
            (*arg1)++;
            actor->state = 1;
            break;
        case 2:
            break;
    }
}

void Macbeth_8019FF9C(Actor* actor) {
    switch (actor->state) {
        case 0:
            Macbeth_8019A198(actor);
            Macbeth_801A015C(actor);
            Macbeth_8019FC54(actor, &actor->iwork[10], &actor->iwork[11], 1, 3, actor->fwork[25], 0.0f,
                             &actor->iwork[13]);
            Macbeth_8019A728(actor);
            if (actor->iwork[1] != 0) {
                Macbeth_8019F164(actor);
            }
            Macbeth_8019A830(actor);
            break;
        case 1:
            if (actor->iwork[5] < D_MA_801BE2F0[3]) {
                D_MA_801BE2F0[3] = actor->iwork[5];
            }
            actor->state = 2;
            Macbeth_801A015C(actor);
            Macbeth_8019A830(actor);
            break;
        case 2:
            Macbeth_8019BBEC(actor);
            if (actor->timer_0BC == 0) {
                actor->timer_0BC = 60;
            }
            Math_SmoothStepToF(&actor->vel.z, 0.0f, 0.02f, 10.0f, 0.01f);
            Macbeth_801A015C(actor);
            Macbeth_8019A87C(actor);
            if (actor->unk_0D0 != 0) {
                actor->unk_0D0 = 0;
                actor->timer_0BC = 20;
                Macbeth_8019BE50(actor);
                actor->state = 3;
            }
            break;
        case 3:
            Macbeth_801A015C(actor);
            Math_SmoothStepToF(&actor->scale, 0.0f, 0.02f, 10.0f, 0.01f);
            if (actor->timer_0BC <= 0) {
                Object_Kill(&actor->obj, actor->sfxSource);
            }
            break;
    }
}

void Macbeth_801A015C(Actor* actor) {
    if (!Macbeth_801A0308(actor, actor->obj.pos.z, actor->obj.rot.y, 0)) {
        actor->obj.pos.x = actor->fwork[19];
        actor->obj.pos.y = actor->fwork[5];
        if (!Macbeth_801A0308(actor, actor->obj.pos.z - 420.0f, actor->fwork[22], 1)) {
            actor->fwork[21] = actor->fwork[19] - actor->obj.pos.x;
            actor->fwork[22] = actor->fwork[20];
            actor->fwork[6] = actor->fwork[5] - actor->obj.pos.y;
            actor->fwork[27] = actor->fwork[9];
            if (!Macbeth_801A0308(actor, actor->obj.pos.z + 420.0f, actor->fwork[24], 2)) {
                actor->fwork[23] = actor->fwork[19] - actor->obj.pos.x;
                actor->fwork[24] = actor->fwork[20];
                actor->fwork[7] = actor->fwork[5] - actor->obj.pos.y;
                actor->fwork[28] = actor->fwork[9];
                if (actor->fwork[19] - actor->obj.pos.x < actor->fwork[21]) {
                    actor->fwork[25] = actor->fwork[23] + ((actor->fwork[21] - actor->fwork[23]) / 2);
                } else {
                    actor->fwork[25] = actor->fwork[21] + ((actor->fwork[23] - actor->fwork[21]) / 2);
                }

                if (actor->fwork[7] < actor->fwork[6]) {
                    actor->fwork[8] = actor->fwork[7] + ((actor->fwork[6] - actor->fwork[7]) / 2);
                } else {
                    actor->fwork[8] = actor->fwork[6] + ((actor->fwork[7] - actor->fwork[6]) / 2);
                }
                actor->fwork[26] = (actor->fwork[22] + actor->fwork[24]) / 2;
                actor->fwork[29] = (actor->fwork[27] + actor->fwork[28]) / 2;
            }
        }
    }
}

bool Macbeth_801A0308(Actor* actor, f32 arg1, f32 arg2, u8 arg3) {
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

            for (var_a0 = actor->fwork[arg3 + 16]; D_i5_801B8E50[var_a0].unk_10 != 0; var_a0++) {
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
                    if (D_i5_801B8E50[var_a0 - 1].unk_10 == OBJ_80_104) {
                        sp38 = 0.0f;
                    }
                    if (D_i5_801B8E50[var_a0].unk_10 == OBJ_80_104) {
                        sp28 = 0.0f;
                    }
                    actor->fwork[arg3 + 16] = var_a0;
                    break;
                }
            }
            if (D_i5_801B8E50[var_a0].unk_10 == 0) {
                actor->fwork[arg3 + 16] = 1.0f;
            }
            break;
        case 1:
            for (var_a0 = actor->fwork[arg3 + 16]; D_i5_801B9A80[var_a0].unk_10 != 0; var_a0++) {
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
                    if (D_i5_801B8E50[var_a0 - 1].unk_10 == OBJ_80_104) {
                        sp38 = 0.0f;
                    }
                    if (D_i5_801B8E50[var_a0].unk_10 == OBJ_80_104) {
                        sp28 = 0.0f;
                    }
                    actor->fwork[arg3 + 16] = var_a0;
                    break;
                }
            }
            if (D_i5_801B9A80[var_a0].unk_10 == 0) {
                actor->fwork[arg3 + 16] = 1.0f;
            }
            break;
    }

    sp24 = 1.0f - ((sp2C - arg1) / (sp2C - sp3C));
    if ((sp4C == OBJ_80_95) || (sp4C == OBJ_80_96) || (sp4C == OBJ_80_98) || (sp4C == OBJ_80_99)) {
        if ((actor->iwork[5] < (s32) D_i5_801BA1E4) && (actor->iwork[5] < D_MA_801BE2F0[3])) {
            actor->vel.z *= 0.98f;
        }
        temp_fv0 = fabsf((sp2C - sp3C) / 3.0f);
        if (sp24 < 0.3333333f) {
            if ((sp4C == OBJ_80_95) || (sp4C == OBJ_80_98)) {
                actor->fwork[19] = (((sp34 - sp44) * sp24) + sp44) -
                                   (52.160667f * (1.0f - (((sp3C - temp_fv0) - arg1) / ((sp3C - temp_fv0) - sp3C))));
            } else {
                actor->fwork[19] = ((sp34 - sp44) * sp24) + sp44 +
                                   (52.160667f * (1.0f - (((sp3C - temp_fv0) - arg1) / ((sp3C - temp_fv0) - sp3C))));
            }
        } else if (sp24 < 0.666666f) {
            if ((sp4C == OBJ_80_95) || (sp4C == OBJ_80_98)) {
                actor->fwork[19] = (((sp34 - sp44) * sp24) + sp44) - 52.160667f;
            } else {
                actor->fwork[19] = ((sp34 - sp44) * sp24) + sp44 + 52.160667f;
            }
        } else if ((sp4C == OBJ_80_95) || (sp4C == OBJ_80_98)) {
            actor->fwork[19] = (((sp34 - sp44) * sp24) + sp44) -
                               (52.160667f * (1.0f - (1.0f - ((sp2C - arg1) / (sp2C - (sp3C - (temp_fv0 * 2)))))));
        } else {
            actor->fwork[19] = ((sp34 - sp44) * sp24) + sp44 +
                               (52.160667f * (1.0f - (1.0f - ((sp2C - arg1) / (sp2C - (sp3C - (temp_fv0 * 2)))))));
        }
    } else {
        if (sp4C == OBJ_80_104) {
            if ((actor->iwork[5] < (s32) D_i5_801BA1E4) && (actor->iwork[5] < D_MA_801BE2F0[3])) {
                actor->vel.z *= 0.94f;
            }
        }
        actor->fwork[19] = ((sp34 - sp44) * sp24) + sp44;
    }
    actor->fwork[5] = ((sp30 - sp40) * sp24) + sp40;
    if ((sp4C == OBJ_80_100) || (sp4C == OBJ_80_102)) {
        Math_SmoothStepToF(&actor->fwork[9], 3.0f, 0.05f, 1.0f, 0.001f);
    } else if ((sp4C == OBJ_80_101) || (sp4C == OBJ_80_103)) {
        Math_SmoothStepToF(&actor->fwork[9], -3.0f, 0.05f, 1.0f, 0.001f);
    } else {
        Math_SmoothStepToF(&actor->fwork[9], 0.0f, 0.05f, 1.0f, 0.0f);
    }
    actor->fwork[20] = ((sp28 - sp38) * sp24) + sp38;
    return false;
}

bool Macbeth_801A0A74(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* data) {
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

bool Macbeth_801A0B00(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* data) {
    if (limbIndex == 3) {
        *dList = NULL;
    }
    return false;
}

bool Macbeth_801A0B20(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* data) {
    Actor* actor = (Actor*) data;

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

void Macbeth_801A0BD8(Object_80* obj80) {
    switch (obj80->state) {
        case 0:
            obj80->vel.y = 0.0f;
            obj80->vel.x = 0.0f;
            if (D_i5_801BE312 != 0) {
                obj80->state = 1;
                obj80->timer_4C = 20;
            }
            break;
        case 1:
            if (obj80->timer_4C == 1) {
                AUDIO_PLAY_SFX(0x01004024, gPlayer[0].sfxSource, 0);
            }
            if (obj80->timer_4C <= 0) {
                Math_SmoothStepToF(&obj80->vel.x, 1751.0f, 0.2f, 80.0f, 1.0f);
                if (obj80->vel.x >= 1750.0) {
                    AUDIO_PLAY_SFX(0x1940807B, obj80->sfxSource, 0);
                    Audio_KillSfxBySourceAndId(gPlayer[0].sfxSource, 0x01004024);
                    obj80->timer_4C = 5;
                    obj80->state = 2;
                }
            }
            break;
        case 2:
            Math_SmoothStepToF(&obj80->vel.y, -11.0f, 0.1f, 2.5f, 0.01f);
            if (obj80->vel.y <= -10.0f) {
                obj80->state = 3;
            }
            break;
        case 3:
            break;
    }
    if (obj80->timer_4C != 0) {
        obj80->vel.z = 2.0f + RAND_FLOAT(1.0f);
    } else {
        obj80->vel.z = 1.0f + RAND_FLOAT(1.0f);
    }
}

bool Macbeth_801A0DD8(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* data) {
    Object_80* obj80 = (Object_80*) data;

    if (limbIndex == 5) {
        rot->y += obj80->vel.y;
    }
    if ((limbIndex == 1) || (limbIndex == 2)) {
        pos->z -= obj80->vel.x;
    }
    return false;
}

void Macbeth_801A0E2C(s32 limbIndex, Vec3f* rot, void* data) {
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

bool Macbeth_801A0EB8(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* data) {
    Actor* actor = (Actor*) data;

    RCP_SetupDL(&gMasterDisp, 0x1D);
    gSPClearGeometryMode(gMasterDisp++, G_TEXTURE_GEN);
    if ((limbIndex == 3) || (limbIndex == 6) || (limbIndex == 9)) {
        gSPTexture(gMasterDisp++, 3000, 3000, 0, G_TX_RENDERTILE, G_ON);
        gSPSetGeometryMode(gMasterDisp++, G_TEXTURE_GEN);
    }
    if ((limbIndex == 5) || (limbIndex == 9)) {
        if ((actor->iwork[7] % 2) != 0) {
            RCP_SetupDL_27();
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
        }
        if ((actor->iwork[7] > 0) && (limbIndex == 5)) {
            actor->iwork[7]--;
        }
        rot->x += actor->fwork[2];
        if (limbIndex == 5) {
            RCP_SetupDL(&gMasterDisp, 0x22);
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, D_i5_801BE368[20], D_i5_801BE368[21], D_i5_801BE368[22], 255);
            gSPDisplayList(gMasterDisp++, D_MA_6010470);
            RCP_SetupDL(&gMasterDisp, 0x1D);
        }
    }
    switch (limbIndex) {
        case 1:
            rot->x += actor->fwork[3] / 2;
            break;
        case 2:
            rot->x -= actor->fwork[3] / 2;
            break;
    }
    return false;
}

void Macbeth_801A1268(s32 limbIndex, Vec3f* rot, void* data) {
    Vec3f sp1C = { 0.0f, 0.0f, 0.0f };
    Actor* actor = (Actor*) data;

    if (limbIndex == 4) {
        Matrix_MultVec3f(gCalcMatrix, &sp1C, actor->vwork);
    }
}

void Macbeth_801A12C4(Actor* actor) {
    Vec3f spD0[50];
    s32 id;

    if (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_3) {
        if (((gPlayer[0].unk_138 - actor->obj.pos.z) > 7000.0f) ||
            ((gPlayer[0].unk_138 - actor->obj.pos.z) < -1000.0f)) {
            return;
        }
    } else {
        if (((gPlayer[0].unk_138 - actor->obj.pos.z) > 7000.0f) ||
            ((gPlayer[0].unk_138 - actor->obj.pos.z) < -5000.0f)) {
            return;
        }
    }

    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, actor->fwork[25], actor->fwork[8] + 25.0f, 0.0f, 1);
    Matrix_RotateY(gGfxMatrix, actor->fwork[26] * M_DTOR, 1);
    Matrix_RotateX(gGfxMatrix, actor->fwork[29] * M_DTOR, 1);
    Matrix_SetGfxMtx(&gMasterDisp);

    if ((actor->obj.id != OBJ_ACTOR_206) && (actor->obj.id != OBJ_ACTOR_205)) {
        if (((gPlayer[0].unk_138 - actor->obj.pos.z) > 3000.0f) && (D_i5_801BE310 != actor->iwork[5])) {
            gSPDisplayList(gMasterDisp++, D_MA_6027BF0);
            gSPDisplayList(gMasterDisp++, D_MA_601BE90);
        } else {
            Matrix_Scale(gGfxMatrix, actor->scale, actor->scale, actor->scale, 1);
            Animation_GetFrameData(&D_MA_602EA0C, 0, spD0);
            Animation_DrawSkeleton(1, D_MA_602EBB8, spD0, Macbeth_801A0A74, NULL, actor, &gIdentityMatrix);
        }
    }
    switch (actor->obj.id) {
        case OBJ_ACTOR_212:
            if (actor->iwork[13] == 0) {
                if ((actor->iwork[7] % 2) != 0) {
                    RCP_SetupDL_27();
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
                }
                if (actor->iwork[7] > 0) {
                    actor->iwork[7]--;
                }
                Animation_GetFrameData(&D_MA_6027320, 0, spD0);
                Animation_DrawSkeleton(1, D_MA_602742C, spD0, Macbeth_801A0B20, NULL, actor, &gIdentityMatrix);
            }
            break;
        case OBJ_ACTOR_210:
            if (actor->iwork[13] == 0) {
                Animation_GetFrameData(&D_MA_6027A04, 0, spD0);
                Animation_DrawSkeleton(1, D_MA_6027AF0, spD0, Macbeth_801A0B00, NULL, actor, &gIdentityMatrix);
                Matrix_Translate(gGfxMatrix, 0.0f, 205.0f, 0.0f, 1);
                Matrix_RotateZ(gGfxMatrix, actor->fwork[4] * M_DTOR, 1);
                Matrix_SetGfxMtx(&gMasterDisp);
                if ((actor->iwork[7] % 2) != 0) {
                    RCP_SetupDL_27();
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
                }
                if (actor->iwork[7] > 0) {
                    actor->iwork[7]--;
                }
                if (actor->iwork[3] >= 3) {
                    gSPDisplayList(gMasterDisp++, D_MA_6027EB0);
                } else {
                    gSPDisplayList(gMasterDisp++, D_MA_60288A0);
                }
            }
            break;
        case OBJ_ACTOR_209:
            if (actor->iwork[17] != 2) {
                Matrix_Translate(gGfxMatrix, 0.0f, 5.0f, 0.0f, 1);
                Matrix_SetGfxMtx(&gMasterDisp);
                if ((actor->iwork[8] % 2) != 0) {
                    RCP_SetupDL_27();
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
                }
                if (actor->iwork[8] > 0) {
                    actor->iwork[8]--;
                }
                gSPDisplayList(gMasterDisp++, D_MA_6029890);
                RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
            }
            break;
        case OBJ_ACTOR_211:
            if (actor->iwork[17] != 2) {
                Matrix_Translate(gGfxMatrix, 0.0f, -15.0f, 0.0f, 1);
                Matrix_SetGfxMtx(&gMasterDisp);
                if ((actor->iwork[8] % 2) != 0) {
                    RCP_SetupDL_27();
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
                }
                if (actor->iwork[8] > 0) {
                    actor->iwork[8]--;
                }
                if (actor->iwork[17] == 0) {
                    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
                    gSPDisplayList(gMasterDisp++, D_MA_6004440);
                } else {
                    RCP_SetupDL(&gMasterDisp, 0x39);
                    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                    gSPDisplayList(gMasterDisp++, D_MA_6022200);
                    RCP_SetupDL(&gMasterDisp, 0x1D);
                }
                RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
            }
            break;
        case OBJ_ACTOR_213:
            if (actor->iwork[13] < 2) {
                Matrix_Translate(gGfxMatrix, 0.0f, -5.0f, 0.0f, 1);
                Matrix_SetGfxMtx(&gMasterDisp);
                RCP_SetupDL(&gMasterDisp, 0x39);
                if ((actor->iwork[7] % 2) != 0) {
                    RCP_SetupDL_27();
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
                }
                if (actor->iwork[7] > 0) {
                    actor->iwork[7]--;
                }
                gSPDisplayList(gMasterDisp++, D_MA_6024670);
                RCP_SetupDL(&gMasterDisp, 0x1D);
            }
            break;
        case OBJ_ACTOR_208:
            if (actor->iwork[13] < 2) {
                if ((actor->iwork[7] % 2) != 0) {
                    RCP_SetupDL_27();
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
                }
                if (actor->iwork[7] > 0) {
                    actor->iwork[7]--;
                }
                if (actor->iwork[13] == 0) {
                    Matrix_Translate(gGfxMatrix, 0.0f, -5.0f, 0.0f, 1);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_MA_60269E0);
                } else {
                    Matrix_Translate(gGfxMatrix, 0.0f, -5.0f, 0.0f, 1);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_MA_6017720);
                }
                gDPSetTextureFilter(gMasterDisp++, G_TF_BILERP);
            }
            break;
        case OBJ_ACTOR_206:
            Animation_GetFrameData(&D_MA_601EAB0, 0, spD0);
            Animation_DrawSkeleton(1, D_MA_601EBBC, spD0, Macbeth_801AC5AC, NULL, actor, &gIdentityMatrix);
            break;
        case OBJ_ACTOR_205:
            Matrix_Translate(gGfxMatrix, actor->fwork[3], 0.0f, 0.0f, 1);
            if (D_i5_801BE320[21] == 0) {
                Animation_GetFrameData(&D_MA_6010220, 0, spD0);
            } else if (D_i5_801BE320[21] == 1) {
                Animation_GetFrameData(&D_MA_600FEC4, D_i5_801BE320[22], spD0);
            } else {
                Animation_GetFrameData(&D_MA_6010144, D_i5_801BE320[22], spD0);
            }
            Animation_DrawSkeleton(1, D_MA_601042C, spD0, Macbeth_801A0EB8, Macbeth_801A1268, actor, &gIdentityMatrix);
            if (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_7) {
                RCP_SetupDL(&gMasterDisp, 0x1D);
                gSPClearGeometryMode(gMasterDisp++, G_TEXTURE_GEN);
                gSPDisplayList(gMasterDisp++, D_MA_6003370);
            }
            break;
    }
    Matrix_Pop(&gGfxMatrix);
    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, actor->fwork[21], actor->fwork[6] + 65.0f, -420.0f, 1);
    Matrix_RotateY(gGfxMatrix, actor->fwork[22] * M_DTOR, 1);
    Matrix_RotateX(gGfxMatrix, actor->fwork[27] * M_DTOR, 1);
    Matrix_SetGfxMtx(&gMasterDisp);
    Matrix_Scale(gGfxMatrix, actor->scale, actor->scale, actor->scale, 1);
    if ((gPlayer[0].unk_138 - actor->obj.pos.z) > 3000.0f) {
        gSPDisplayList(gMasterDisp++, D_MA_6027D40);
    } else if (actor->vel.z > -2.0f) {
        gSPDisplayList(gMasterDisp++, D_MA_60227F0);
    } else {
        gSPDisplayList(gMasterDisp++, D_MA_60239D0);
    }
    Matrix_Pop(&gGfxMatrix);
    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, actor->fwork[23], actor->fwork[7] + 65.0f, 420.0f, 1);
    Matrix_RotateY(gGfxMatrix, actor->fwork[24] * M_DTOR, 1);
    Matrix_RotateX(gGfxMatrix, actor->fwork[28] * M_DTOR, 1);
    Matrix_Scale(gGfxMatrix, actor->scale, actor->scale, actor->scale, 1);
    Matrix_SetGfxMtx(&gMasterDisp);
    RCP_SetupDL(&gMasterDisp, 0x1D);
    if ((gPlayer[0].unk_138 - actor->obj.pos.z) > 3000.0f) {
        gSPDisplayList(gMasterDisp++, D_MA_6027D40);
    } else if (actor->vel.z > -2.0f) {
        gSPDisplayList(gMasterDisp++, D_MA_60227F0);
    } else {
        gSPDisplayList(gMasterDisp++, D_MA_60239D0);
    }
    Matrix_Pop(&gGfxMatrix);
    id = actor->obj.id;
    if ((id == OBJ_ACTOR_209) || (id == OBJ_ACTOR_211)) {
        if (actor->iwork[13] != 2) {
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, actor->fwork[21], actor->fwork[6] + 10.0f, -420.0f, 1);
            Matrix_RotateY(gGfxMatrix, actor->fwork[26] * M_DTOR, 1);
            Matrix_RotateX(gGfxMatrix, actor->fwork[29] * M_DTOR, 1);
            Matrix_SetGfxMtx(&gMasterDisp);
            if ((actor->iwork[7] % 2) != 0) {
                RCP_SetupDL_27();
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
            }
            if (actor->iwork[7] > 0) {
                actor->iwork[7]--;
            }
            if (actor->iwork[13] == 0) {
                gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
                gSPDisplayList(gMasterDisp++, D_MA_6004440);
            } else {
                RCP_SetupDL(&gMasterDisp, 0x39);
                gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                gSPDisplayList(gMasterDisp++, D_MA_6022200);
                RCP_SetupDL(&gMasterDisp, 0x1D);
            }
            RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
            Matrix_Pop(&gGfxMatrix);
        }
        if (actor->iwork[21] != 2) {
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, actor->fwork[23], actor->fwork[7] + 10.0f, 420.0f, 1);
            Matrix_RotateY(gGfxMatrix, actor->fwork[26] * M_DTOR, 1);
            Matrix_RotateX(gGfxMatrix, actor->fwork[29] * M_DTOR, 1);
            Matrix_SetGfxMtx(&gMasterDisp);
            if ((actor->iwork[9] % 2) != 0) {
                RCP_SetupDL_27();
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
            }
            if (actor->iwork[9] > 0) {
                actor->iwork[9]--;
            }
            if (actor->iwork[21] == 0) {
                gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
                gSPDisplayList(gMasterDisp++, D_MA_6004440);
            } else {
                RCP_SetupDL(&gMasterDisp, 0x39);
                gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                gSPDisplayList(gMasterDisp++, D_MA_6022200);
                RCP_SetupDL(&gMasterDisp, 0x1D);
            }
            RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
            Matrix_Pop(&gGfxMatrix);
        }
    }
}

void Macbeth_801A23AC(Object_80* obj80) {
    Vec3f sp78[50];

    RCP_SetupDL(&gMasterDisp, 0x39);
    switch (obj80->obj.id) {
        case OBJ_80_94:
        case OBJ_80_97:
            if ((gPlayer[0].state_1C8 != PLAYERSTATE_1C8_7) && ((gPlayer[0].unk_138 - obj80->obj.pos.z) < -2500.0f)) {
                Object_Kill(&obj80->obj, obj80->sfxSource);
            }
            gSPDisplayList(gMasterDisp++, D_MA_6026860);
            break;
        case OBJ_80_95:
        case OBJ_80_98:
            if ((gPlayer[0].state_1C8 != PLAYERSTATE_1C8_7) && ((gPlayer[0].unk_138 - obj80->obj.pos.z) < -2500.0f)) {
                Object_Kill(&obj80->obj, obj80->sfxSource);
            }
            gSPDisplayList(gMasterDisp++, D_MA_602FBF0);
            break;
        case OBJ_80_96:
        case OBJ_80_99:
            gSPDisplayList(gMasterDisp++, D_MA_6022610);
            break;
        case OBJ_80_100:
        case OBJ_80_102:
            gSPDisplayList(gMasterDisp++, D_MA_60309D0);
            break;
        case OBJ_80_101:
        case OBJ_80_103:
            gSPDisplayList(gMasterDisp++, D_MA_6030750);
            break;
        case OBJ_80_105:
            RCP_SetupDL(&gMasterDisp, 0x1D);
            gSPDisplayList(gMasterDisp++, D_MA_602D380);
            break;
        case OBJ_80_104:
            Matrix_Push(&gGfxMatrix);
            Animation_GetFrameData(&D_MA_6025CA0, 0, sp78);
            Animation_DrawSkeleton(1, D_MA_6025DAC, sp78, Macbeth_801A0DD8, Macbeth_801A0E2C, obj80, &gIdentityMatrix);
            Matrix_Pop(&gGfxMatrix);
            if ((obj80->state == 1) && (obj80->timer_4C <= 0)) {
                Matrix_Push(&gGfxMatrix);
                RCP_SetupDL_49();
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
                gDPSetEnvColor(gMasterDisp++, 255, 48, 0, 255);
                Matrix_Translate(gGfxMatrix, D_i5_801BE688[0].x, D_i5_801BE688[0].y + 50.0f,
                                 D_i5_801BE688[0].z + 100.0f, 1);
                Matrix_RotateX(gCalcMatrix, (D_PI / 2), 1);
                Matrix_Scale(gGfxMatrix, obj80->vel.z, obj80->vel.z / 2, obj80->vel.z, 1);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_1024AC0);
                Matrix_Pop(&gGfxMatrix);
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, D_i5_801BE688[1].x, D_i5_801BE688[1].y + 50.0f,
                                 D_i5_801BE688[1].z + 100.0f, 1);
                Matrix_RotateX(gCalcMatrix, (D_PI / 2), 1);
                Matrix_Scale(gGfxMatrix, obj80->vel.z, obj80->vel.z / 2, obj80->vel.z, 1);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_1024AC0);
                RCP_SetupDL(&gMasterDisp, 0x1D);
                Matrix_Pop(&gGfxMatrix);
            } else if (obj80->state == 2) {
                Matrix_Push(&gGfxMatrix);
                RCP_SetupDL_49();
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
                gDPSetEnvColor(gMasterDisp++, 255, 48, 0, 255);
                Matrix_Translate(gGfxMatrix, D_i5_801BE688[1].x - 50.0f, D_i5_801BE688[1].y + 50.0f,
                                 D_i5_801BE688[1].z + 50.0f, 1);
                Matrix_RotateX(gCalcMatrix, (D_PI / 2), 1);
                Matrix_Scale(gGfxMatrix, obj80->vel.z, obj80->vel.z / 2, obj80->vel.z, 1);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_1024AC0);
                RCP_SetupDL(&gMasterDisp, 0x1D);
                Matrix_Pop(&gGfxMatrix);
            }
            if (D_MA_801BE2F0[5] != 0) {
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -1800.0f, 1);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_MA_601C170);
                Matrix_Pop(&gGfxMatrix);
            } else {
                Matrix_Push(&gGfxMatrix);
                Matrix_RotateY(gGfxMatrix, -(D_PI / 18), 1);
                Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -1800.0f, 1);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_MA_601C170);
                Matrix_Pop(&gGfxMatrix);
            }
            break;
        case OBJ_80_92:
            gSPDisplayList(gMasterDisp++, D_MA_60014A0);
            break;
        case OBJ_80_93:
            gSPDisplayList(gMasterDisp++, D_MA_6001180);
            break;
    }
    RCP_SetupDL(&gMasterDisp, 0x1D);
}

void Macbeth_801A2A78(Object_80* obj80) {
    RCP_SetupDL(&gMasterDisp, 0x39);
    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
    gSPDisplayList(gMasterDisp++, D_MA_60253E0);
    gSPDisplayList(gMasterDisp++, D_MA_601C000);
    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
    RCP_SetupDL(&gMasterDisp, 0x1D);
}

void Macbeth_801A2B24(Object_80* obj80) {
    if (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_7) {
        Object_Kill(&obj80->obj, obj80->sfxSource);
    }
    RCP_SetupDL(&gMasterDisp, 0x39);
    switch (obj80->obj.id) {
        case OBJ_80_77:
            gSPDisplayList(gMasterDisp++, D_MA_60066A0);
            break;
        case OBJ_80_78:
            gSPDisplayList(gMasterDisp++, D_MA_6007430);
            break;
        case OBJ_80_79:
            gSPDisplayList(gMasterDisp++, D_MA_6007360);
            break;
        case OBJ_80_80:
            gSPDisplayList(gMasterDisp++, D_MA_6007290);
            break;
        case OBJ_80_81:
            gSPDisplayList(gMasterDisp++, D_MA_60071C0);
            break;
        case OBJ_80_82:
            gSPDisplayList(gMasterDisp++, D_MA_6007500);
            break;
        case OBJ_80_84:
            gSPDisplayList(gMasterDisp++, D_MA_600AD50);
            break;
        case OBJ_80_85:
            gSPDisplayList(gMasterDisp++, D_MA_600AA70);
            break;
        case OBJ_80_86:
            gSPDisplayList(gMasterDisp++, D_MA_6003070);
            break;
        case OBJ_80_87:
            gSPDisplayList(gMasterDisp++, D_MA_600A7D0);
            break;
        case OBJ_80_88:
            gSPDisplayList(gMasterDisp++, D_MA_600A4D0);
            break;
        case OBJ_80_89:
            gSPDisplayList(gMasterDisp++, D_MA_600A1F0);
            break;
        case OBJ_80_90:
            gSPDisplayList(gMasterDisp++, D_MA_6009F10);
            break;
        case OBJ_80_91:
            gSPDisplayList(gMasterDisp++, D_MA_6009C50);
            break;
    }
    RCP_SetupDL(&gMasterDisp, 0x1D);
}

void Macbeth_801A2DD8(Object_80* obj80) {
    s16 i;

    switch (obj80->state) {
        case 0:
            if ((D_i5_801BE312 != 0) && (gActors[D_i5_801BE314].obj.pos.z - 900.0f < obj80->obj.pos.z)) {
                obj80->state = 1;
            }
            break;
        case 1:
            func_effect_8007A6F0(&obj80->obj.pos, 0x2903B009);
            D_80137E84[gMainController] = 1;
            D_Timer_80177BD0[gMainController] = 15;
            for (i = 0; i < 6; i++) {
                func_effect_8007D2C8(obj80->obj.pos.x + D_i5_801BE6A0[i].x, obj80->obj.pos.y + D_i5_801BE6A0[i].y,
                                     obj80->obj.pos.z + D_i5_801BE6A0[i].z, 18.0f);
                Macbeth_801AD624(obj80->obj.pos.x + D_i5_801BE6A0[i].x, obj80->obj.pos.y + D_i5_801BE6A0[i].y,
                                 obj80->obj.pos.z + D_i5_801BE6A0[i].z, RAND_FLOAT_CENTERED(30.0f),
                                 RAND_FLOAT(30.0f) + 30.0f, RAND_FLOAT(-50.0f),
                                 obj80->obj.rot.x + D_i5_801BE6A0[i + 6].x, obj80->obj.rot.y + D_i5_801BE6A0[i + 6].y,
                                 obj80->obj.rot.z + D_i5_801BE6A0[i + 6].z, RAND_FLOAT_CENTERED(5.0f),
                                 RAND_FLOAT_CENTERED(5.0f), RAND_FLOAT_CENTERED(5.0f),
                                 (s32) (RAND_FLOAT(50.0f) + 70.0f), i + 12, 1.0f);
            }
            Object_Kill(&obj80->obj, obj80->sfxSource);
            break;
    }
}

void Macbeth_801A30B8(s32 limbIndex, Vec3f* rot, void* data) {
    Vec3f sp24 = { 0.0f, 0.0f, 0.0f };

    switch (limbIndex) {
        case 1:
            Matrix_MultVec3f(gCalcMatrix, &sp24, &D_i5_801BE6A0[0]);
            Matrix_GetYRPAngles(gCalcMatrix, &D_i5_801BE6E8[0]);
            break;
        case 2:
            Matrix_MultVec3f(gCalcMatrix, &sp24, &D_i5_801BE6A0[1]);
            Matrix_GetYRPAngles(gCalcMatrix, &D_i5_801BE6E8[1]);
            break;
        case 3:
            Matrix_MultVec3f(gCalcMatrix, &sp24, &D_i5_801BE6A0[2]);
            Matrix_GetYRPAngles(gCalcMatrix, &D_i5_801BE6E8[2]);
            break;
        case 4:
            Matrix_MultVec3f(gCalcMatrix, &sp24, &D_i5_801BE6A0[3]);
            Matrix_GetYRPAngles(gCalcMatrix, &D_i5_801BE6E8[3]);
            break;
        case 5:
            Matrix_MultVec3f(gCalcMatrix, &sp24, &D_i5_801BE6A0[4]);
            Matrix_GetYRPAngles(gCalcMatrix, &D_i5_801BE6E8[4]);
            break;
        case 11:
            Matrix_MultVec3f(gCalcMatrix, &sp24, &D_i5_801BE6A0[5]);
            Matrix_GetYRPAngles(gCalcMatrix, &D_i5_801BE6E8[5]);
            break;
        default:
            break;
    }
}

void Macbeth_801A3240(Object_80* obj80) {
    Vec3f sp38[50];

    RCP_SetupDL(&gMasterDisp, 0x1D);
    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
    Animation_GetFrameData(&D_MA_600C4D0, 0, sp38);
    Animation_DrawSkeleton(1, D_MA_600C65C, sp38, NULL, Macbeth_801A30B8, obj80, &gIdentityMatrix);
    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
}

bool Macbeth_801A3300(Player* player, f32 arg1, f32 arg2) {
    s16 temp_a0;
    s16 var_v1;
    f32 temp_ft4;
    f32 temp_fa0;
    f32 sp40;
    f32 temp_fv0_2;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    s32 pad;

    var_v1 = D_MA_801BE250[6];
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
                    case OBJ_80_94:
                    case OBJ_80_100:
                    case OBJ_80_101:
                        D_MA_801BE250[8] = 0.0f;
                        break;
                    case OBJ_80_95:
                        D_MA_801BE250[8] = -10.0f;
                        break;
                    case OBJ_80_96:
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

    if ((temp_a0 == OBJ_80_95) || (temp_a0 == OBJ_80_96) || (temp_a0 == OBJ_80_98) || (temp_a0 == OBJ_80_99)) {
        temp_fv0_2 = fabsf((sp30 - temp_ft4) / 3.0f);
        if (sp2C < 0.3333333f) {
            if ((temp_a0 == OBJ_80_95) || (temp_a0 == OBJ_80_98)) {
                D_MA_801BE250[9] =
                    (((sp38 - temp_fa0) * sp2C) + temp_fa0) -
                    (52.160667f * (1.0f - (((temp_ft4 - temp_fv0_2) - arg1) / ((temp_ft4 - temp_fv0_2) - temp_ft4))));
            } else {
                D_MA_801BE250[9] =
                    ((sp38 - temp_fa0) * sp2C) + temp_fa0 +
                    (52.160667f * (1.0f - (((temp_ft4 - temp_fv0_2) - arg1) / ((temp_ft4 - temp_fv0_2) - temp_ft4))));
            }
        } else if (sp2C < 0.666666f) {
            if ((temp_a0 == OBJ_80_95) || (temp_a0 == OBJ_80_98)) {
                D_MA_801BE250[9] = (((sp38 - temp_fa0) * sp2C) + temp_fa0) - 52.160667f;
            } else {
                D_MA_801BE250[9] = (((sp38 - temp_fa0) * sp2C) + temp_fa0 + 52.160667f);
            }
        } else if ((temp_a0 == OBJ_80_95) || (temp_a0 == OBJ_80_98)) {
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
    if ((temp_a0 == 100) || (temp_a0 == OBJ_80_102)) {
        Math_SmoothStepToF(&D_MA_801BE250[3], 3.0f, 0.05f, 1.0f, 0.0f);
    } else if ((temp_a0 == OBJ_80_101) || (temp_a0 == OBJ_80_103)) {
        Math_SmoothStepToF(&D_MA_801BE250[3], -3.0f, 0.05f, 1.0f, 0.0f);
    } else {
        Math_SmoothStepToF(&D_MA_801BE250[3], 0.0f, 0.05f, 1.0f, 0.0f);
    }
    D_MA_801BE250[4] = (D_MA_801BE250[8] * sp2C) + D_MA_801BE250[7];

    return false;
}

bool Macbeth_801A3790(Player* player, f32 arg1, f32 arg2) {
    s16 temp_a0;
    s16 var_v1;
    f32 temp_ft4;
    f32 temp_fa0;
    f32 sp40;
    f32 temp_fv0_2;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    s32 pad;

    var_v1 = D_MA_801BE250[16];
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
                    case OBJ_80_97:
                    case OBJ_80_100:
                    case OBJ_80_101:
                        D_MA_801BE250[18] = 0.0f;
                        break;
                    case OBJ_80_98:
                        D_MA_801BE250[18] = -10.0f;
                        break;
                    case OBJ_80_99:
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

    if ((temp_a0 == OBJ_80_95) || (temp_a0 == OBJ_80_96) || (temp_a0 == OBJ_80_98) || (temp_a0 == OBJ_80_99)) {
        temp_fv0_2 = fabsf((sp30 - temp_ft4) / 3.0f);
        if (sp2C < 0.3333333f) {
            if ((temp_a0 == OBJ_80_95) || (temp_a0 == OBJ_80_98)) {
                D_MA_801BE250[19] =
                    (((sp38 - temp_fa0) * sp2C) + temp_fa0) -
                    (52.160667f * (1.0f - (((temp_ft4 - temp_fv0_2) - arg1) / ((temp_ft4 - temp_fv0_2) - temp_ft4))));
            } else {
                D_MA_801BE250[19] =
                    ((sp38 - temp_fa0) * sp2C) + temp_fa0 +
                    (52.160667f * (1.0f - (((temp_ft4 - temp_fv0_2) - arg1) / ((temp_ft4 - temp_fv0_2) - temp_ft4))));
            }
        } else if (sp2C < 0.666666f) {
            if ((temp_a0 == OBJ_80_95) || (temp_a0 == OBJ_80_98)) {
                D_MA_801BE250[19] = (((sp38 - temp_fa0) * sp2C) + temp_fa0) - 52.160667f;
            } else {
                D_MA_801BE250[19] = (((sp38 - temp_fa0) * sp2C) + temp_fa0 + 52.160667f);
            }
        } else if ((temp_a0 == OBJ_80_95) || (temp_a0 == OBJ_80_98)) {
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
    if ((temp_a0 == OBJ_80_100) || (temp_a0 == OBJ_80_102)) {
        Math_SmoothStepToF(&D_MA_801BE250[13], 2.0f, 0.05f, 1.0f, 0.0f);
    } else if ((temp_a0 == OBJ_80_101) || (temp_a0 == OBJ_80_103)) {
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

void Macbeth_801A3E70(Actor* actor) {
    actor->state = 0;
    actor->unk_046 = D_i5_801BA1D8;
    D_i5_801BA1D8++;
}

void Macbeth_801A3E98(Actor* actor) {
    if ((gPlayer[0].unk_138 - actor->obj.pos.z) < -500.0f) {
        Object_Kill(&actor->obj, actor->sfxSource);
    }

    switch (actor->state) {
        case 0:
            if ((actor->unk_0D0 != 0) && (actor->unk_0D0 != 3)) {
                actor->unk_0D0 = 0;
                AUDIO_PLAY_SFX(0x1903205F, actor->sfxSource, 0);
                actor->state = 1;
            }
            break;
        case 1:
            Math_SmoothStepToF(&actor->fwork[1], -181.0f, 0.6f, 20.0f, 0.0f);
            if (actor->fwork[1] <= -180.0f) {
                AUDIO_PLAY_SFX(0x19033008, actor->sfxSource, 0);
                actor->info.hitbox = LOAD_ASSET(D_MA_603648C);
                actor->iwork[0] = 2;
                actor->state = 2;
            }
            break;
        case 2:
            if (actor->iwork[0] <= 0) {
                Math_SmoothStepToF(&actor->fwork[2], 41.0f, 0.6f, 8.0f, 0.0f);
                if (actor->fwork[2] >= 40.0f) {
                    actor->state = 3;
                    D_i5_801BE308[actor->unk_046] = 1;
                }
            } else {
                actor->iwork[0]--;
            }
            break;
        case 3:
            break;
    }
    if (actor->unk_0D0 != 0) {
        AUDIO_PLAY_SFX(0x29121007, actor->sfxSource, 4);
        actor->unk_0D0 = 0;
    }
    Math_SmoothStepToF(&actor->fwork[0], 30.0f, 0.4f, 10.0f, 0.0f);
    Math_SmoothStepToF(&actor->fwork[4], 30.0f, 0.4f, 10.0f, 0.0f);
    if (actor->fwork[0] < 31.0f) {
        if (actor->state >= 3) {
            AUDIO_PLAY_SFX(0x19020060, actor->sfxSource, 0);
        } else {
            AUDIO_PLAY_SFX(0x19020061, actor->sfxSource, 0);
        }
        actor->fwork[0] = 255.0f;
        actor->fwork[4] = 170.0f;
    }
}

bool Macbeth_801A41B0(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* data) {
    Actor* actor = (Actor*) data;

    RCP_SetupDL(&gMasterDisp, 0x1D);
    gDPSetTextureFilter(gMasterDisp++, G_TF_BILERP);
    if (limbIndex == 2) {
        RCP_SetupDL(&gMasterDisp, 0x22);
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

void Macbeth_801A43BC(Actor* actor) {
    Vec3f sp50[50];

    Matrix_Push(&gGfxMatrix);
    Animation_GetFrameData(&D_MA_602FEB4, 0, sp50);
    Animation_DrawSkeleton(1, D_MA_602FFA0, sp50, Macbeth_801A41B0, NULL, actor, &gIdentityMatrix);
    Matrix_Pop(&gGfxMatrix);
    RCP_SetupDL(&gMasterDisp, 0x1D);
    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, 0.0f, actor->fwork[2] + 204.0f, 0.0f, 1);
    Matrix_RotateY(gGfxMatrix, actor->fwork[1] * M_DTOR, 1);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_MA_602FFC0);
    Matrix_Pop(&gGfxMatrix);
    RCP_SetupDL(&gMasterDisp, 0x22);
    gDPSetTextureFilter(gMasterDisp++, G_TF_POINT);
    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, actor->fwork[0], 0, 0, 255);
    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, 0.0f, actor->fwork[2] + 204.0f, 0.0f, 1);
    Matrix_RotateY(gGfxMatrix, actor->fwork[1] * M_DTOR, 1);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_MA_602F380);
    gDPSetTextureFilter(gMasterDisp++, G_TF_BILERP);
    Matrix_Pop(&gGfxMatrix);
}

void Macbeth_801A4660(Actor* actor) {
    actor->gravity = 0;
    actor->unk_04A = actor->unk_046;
    actor->health = 60;
    if (actor->fwork[0] < 0.0f) {
        actor->unk_048 = 0;
    } else {
        actor->unk_048 = 1;
    }
}

void Macbeth_801A46A0(Actor* actor) {
    if ((gPlayer[0].unk_138 - actor->obj.pos.z) < -500.0f) {
        Object_Kill(&actor->obj, actor->sfxSource);
    }

    switch (actor->state) {
        case 0:
            if (actor->timer_0BC == 0) {
                Math_SmoothStepToF(&actor->vel.x, actor->fwork[0], 0.5f, 3.0f, 0.0f);
                Math_SmoothStepToF(&actor->gravity, 5.0f, 0.08f, 1.0f, 0.0f);
                if (actor->obj.pos.y < 80.0f) {
                    if (actor->unk_046 != 0) {
                        AUDIO_PLAY_SFX(0x19030006, actor->sfxSource, 0);
                        actor->obj.pos.y = 80.0f;
                        if (actor->vel.y < 0) {
                            actor->vel.y = -actor->vel.y * (actor->unk_046 * 0.07f);
                        }

                        actor->fwork[0] /= 1.2f + RAND_FLOAT(1.0f) / 2;
                        actor->unk_046--;
                        actor->vel.z /= 1.5f;
                        if (actor->unk_046 == 0) {
                            actor->timer_0BE = RAND_INT(30.0f);
                        }
                    } else {
                        if (actor->timer_0BE <= 0) {
                            actor->fwork[0] = 0;
                            actor->vel.x = 0;
                        }
                        actor->vel.y = 0;
                        actor->vel.z = 0;
                    }
                }
                if (actor->unk_048 != 0) {
                    actor->obj.rot.z -= 0.5f * actor->vel.x;
                } else {
                    actor->obj.rot.z -= 0.5f * actor->vel.x;
                }
                if (actor->unk_046 != actor->unk_04A) {
                    actor->obj.rot.x = actor->obj.rot.x + (0.1 * actor->vel.z);
                }
            }
            if (actor->unk_046 == 7) {
                if (actor->unk_048 != 0) {
                    actor->obj.rot.z -= 1.0f;
                } else {
                    actor->obj.rot.z += 1.0f;
                }
            }
            Macbeth_801A49B8(actor);
            break;
        case 1:
            Macbeth_801A49B8(actor);
            break;
        case 2:
            func_effect_8007D2C8(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, 10.0f);
            Object_Kill(&actor->obj, actor->sfxSource);
            break;
    }
}

void Macbeth_801A49B8(Actor* actor) {
    if (actor->unk_0D0 != 0) {
        AUDIO_PLAY_SFX(0x29024003, actor->sfxSource, 0);
        actor->timer_0C6 = 15;
        actor->health -= actor->damage;
        if (actor->health <= 0) {
            func_effect_8007A6F0(&actor->obj.pos, 0x2903B009);
            gHitCount++;
            actor->state = 2;
        }
        actor->unk_0D0 = 0;
    }
}

void Macbeth_801A4A64(Actor* actor) {
    if (actor->state < 2) {
        if (actor->scale != 1.0f) {
            Matrix_Scale(gGfxMatrix, actor->scale, actor->scale, actor->scale, 1);
            Matrix_SetGfxMtx(&gMasterDisp);
        }
        gSPDisplayList(gMasterDisp++, D_MA_601A2B0);
    }
}

void Macbeth_801A4AF8(Actor* actor) {
    actor->fwork[1] = 10.0f;
    actor->fwork[6] = -100.0f;
    D_i5_801BE318 = actor->index;
}

void Macbeth_801A4B24(Actor* actor) {
    s32 pad[2];
    s32 i;
    ObjectInit* objInit;
    u8 var_s0;
    u8 j;

    var_s0 = 0;
    if ((gPlayer[0].unk_138 - actor->obj.pos.z) < -700.0f) {
        if (D_MA_801BE2F0[5] == 0) {
            Radio_PlayMessage(gMsg_ID_17170, RCID_PEPPY);
        }
        Object_Kill(&actor->obj, actor->sfxSource);
    }

    switch (actor->state) {
        case 0:

            for (j = 0; j < 8; j++) {
                if (D_i5_801BE308[j] != 0) {
                    var_s0++;
                }
            }
            if (var_s0 >= 8) {
                Radio_PlayMessage(gMsg_ID_17150, RCID_PEPPY);
                actor->state = 1;
            }
            break;
        case 1:
            if ((gPlayer[0].unk_138 - actor->obj.pos.z) < 2000.0f) {
                actor->info.hitbox = LOAD_ASSET(D_MA_6036520);
                actor->state = 2;
            }
            break;
        case 2:
            Math_SmoothStepToF(&actor->fwork[2], -76.0f, 0.2f, 10.0f, 0.01f);
            Math_SmoothStepToF(&actor->fwork[3], 76.0f, 0.2f, 10.0f, 0.01f);
            Math_SmoothStepToF(&actor->fwork[6], 0.0f, 0.2f, 4.0f, 0.00001f);
            if (actor->fwork[3] >= 75.0f) {
                actor->state = 3;
            }
            break;
        case 3:
            Math_SmoothStepToF(&actor->fwork[5], -75.0f, 0.2f, 10.0f, 0.00001f);
            Math_SmoothStepToF(&actor->fwork[6], 1.0f, 0.2f, 4.0f, 0.01f);
            if (actor->fwork[6] >= 0.0f) {
                actor->state = 4;
            }
            break;
        case 4:
            Math_SmoothStepToF(&actor->fwork[7], 31.0f, 0.2f, 2.0f, 0.01f);
            if (actor->fwork[7] >= 30.0f) {
                actor->state = 5;
            }
            break;
        case 5:
            if ((actor->unk_0D0 != 0) && (actor->unk_0D2 == 3)) {
                actor->unk_0D0 = 0;
                D_MA_801BE2F0[5] = 1;

                gLevelObjects = LOAD_ASSET(gLevelObjectInits[gCurrentLevel]);

                for (i = D_ctx_80177DC8 - 5, objInit = &gLevelObjects[i]; i < D_ctx_80177DC8 + 50; i++, objInit++) {
                    Object_Load(objInit, 40000.0f, -2000.0f, 40000.0f, -2000.0f);
                }
                D_ctx_80177DC8 = i;
                D_ctx_8017796C = -1;
                gPlayer[0].state_1C8 = PLAYERSTATE_1C8_7;
                gPlayer[0].unk_1D0 = 0;
                gNextPlanetPath = 1;
                actor->timer_0BC = 5;
                actor->state = 6;
                Audio_KillSfxBySourceAndId(gPlayer[0].sfxSource, 0x1100000A);
                Audio_KillSfxBySourceAndId(gPlayer[0].sfxSource, 0x01004024);
            }
            break;
        case 6:
            if (actor->timer_0BC == 1) {
                AUDIO_PLAY_SFX(0x1940405D, actor->sfxSource, 0);
            }
            if (actor->timer_0BC == 0) {
                Math_SmoothStepToF(&actor->fwork[7], -41.0f, 0.2f, 5.0f, 0.01f);
                if (actor->fwork[7] <= -40.0f) {
                    actor->fwork[1] = 150.0f;
                    Radio_PlayMessage(gMsg_ID_17160, RCID_PEPPY);
                    actor->timer_0BC = 30;
                    actor->state = 7;
                }
            }
            break;
        case 7:
            break;
        default:
            break;
    }
    if (actor->unk_0D0 != 0) {
        actor->unk_0D0 = 0;
        AUDIO_PLAY_SFX(0x29121007, actor->sfxSource, 4);
    }
    Math_SmoothStepToF(&actor->fwork[0], 30, 0.4f, actor->fwork[1], 0.0f);
    Math_SmoothStepToF(&actor->fwork[4], 30, 0.4f, actor->fwork[1], 0.0f);
    if (actor->fwork[0] < 31.0f) {
        actor->fwork[0] = 255.0f;
        actor->fwork[4] = 170.0f;
    }
}

bool Macbeth_801A5124(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* data) {
    Actor* actor = (Actor*) data;

    RCP_SetupDL(&gMasterDisp, 0x1D);
    gDPSetTextureFilter(gMasterDisp++, G_TF_BILERP);
    if ((limbIndex == 9) || (limbIndex == 10)) {
        RCP_SetupDL(&gMasterDisp, 0x39);
    }
    if ((limbIndex > 0) && (limbIndex < 9)) {
        RCP_SetupDL(&gMasterDisp, 0x22);
        gDPSetTextureFilter(gMasterDisp++, G_TF_POINT);
        if (D_i5_801BE308[limbIndex - 1] != 0) {
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 0, actor->fwork[0], actor->fwork[4], 255);
        } else {
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, actor->fwork[0], 0, 0, 255);
        }
    }
    if ((limbIndex == 1) || (limbIndex == 3) || (limbIndex == 5) || (limbIndex == 7) || (limbIndex == 9)) {
        pos->x = actor->fwork[2] + pos->x;
        pos->y = actor->fwork[5] + pos->y;
    }
    if ((limbIndex == 2) || (limbIndex == 4) || (limbIndex == 6) || (limbIndex == 8) || (limbIndex == 10)) {
        pos->x = actor->fwork[3] + pos->x;
        pos->y = actor->fwork[5] + pos->y;
    }
    return false;
}

bool Macbeth_801A54AC(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* data) {
    Actor* actor = (Actor*) data;

    pos->y = actor->fwork[6] + pos->y;
    if (limbIndex == 1) {
        rot->x = actor->fwork[7] + rot->x;
    }
    return false;
}

void Macbeth_801A54E8(Actor* actor) {
    Vec3f sp28[50];

    Matrix_Push(&gGfxMatrix);
    Animation_GetFrameData(&D_MA_602F2E0, 0, sp28);
    Animation_DrawSkeleton(1, D_MA_602F36C, sp28, Macbeth_801A54AC, NULL, actor, &gIdentityMatrix);
    Matrix_Pop(&gGfxMatrix);
    Matrix_Push(&gGfxMatrix);
    Animation_GetFrameData(&D_MA_602F098, 0, sp28);
    Animation_DrawSkeleton(1, D_MA_602F264, sp28, Macbeth_801A5124, NULL, actor, &gIdentityMatrix);
    Matrix_Pop(&gGfxMatrix);
    RCP_SetupDL(&gMasterDisp, 0x1D);
}

s32 Macbeth_801A55D4(s32 arg0, Vec3f* arg1, Vec3f* arg2, s32 arg3) {
    Object_80* obj80;
    Actor* actor;
    s32 i;

    obj80 = &gObjects80[0];
    for (i = 0; i < ARRAY_COUNT(gObjects80); i++, obj80++) {
        if ((obj80->obj.status == OBJ_ACTIVE) && (obj80->obj.id != OBJ_80_68) &&
            (fabsf(arg1->x - obj80->obj.pos.x) < 2000.0f) && (fabsf(arg1->z - obj80->obj.pos.z) < 2000.0f) &&
            (func_enmy_80062DBC(arg1, obj80->info.hitbox, &obj80->obj, 0.0f, 0.0f, 0.0f) != 0)) {
            return i + 10;
        }
    }

    actor = &gActors[0];
    for (i = 0; i < ARRAY_COUNT(gActors); i++, actor++) {
        if ((actor->obj.status >= OBJ_ACTIVE) && (fabsf(arg1->x - actor->obj.pos.x) < 1000.0f) &&
            (fabsf(arg1->z - actor->obj.pos.z) < 1500.0f) && (arg0 != i) && (actor->info.unk_16 != 2) &&
            (actor->timer_0C2 == 0) && (func_enmy_800631A8(arg1, actor->info.hitbox, &actor->obj.pos) != 0)) {
            actor->unk_0D0 = 1;
            actor->unk_0D2 = -1;
            actor->unk_0D8.x = arg1->x;
            actor->unk_0D8.y = arg1->y;
            actor->unk_0D8.z = arg1->z;
            return 1;
        }
    }
    return 0;
}

void Macbeth_801A57D0(Effect* effect) {
    u8 i;
    Vec3f sp50;
    Vec3f sp44;
    Vec3f sp38;

    if ((gPlayer[0].unk_138 - effect->obj.pos.z) < -2000.0f) {
        Object_Kill(&effect->obj, effect->sfxSource);
    }
    effect->obj.rot.x = 0.0f;
    effect->obj.rot.y = 0.0f;
    effect->obj.rot.z = 0.0f;
    if (effect->timer_50 == 96) {
        for (i = 0; i < 2; i++) {
            func_effect_8007BC7C(effect->obj.pos.x, effect->obj.pos.y, effect->obj.pos.z, 6.0f);
        }
    }
    if ((fabsf(gPlayer[0].unk_138 - effect->obj.pos.z) < 50.0f) &&
        (fabsf(gPlayer[0].pos.x - effect->obj.pos.x) < 30.0f) &&
        (fabsf(gPlayer[0].pos.y - effect->obj.pos.y) < 30.0f)) {
        if ((gPlayer[0].unk_280 != 0) || (gPlayer[0].timer_27C != 0)) {
            sp50.x = 0.0f;
            sp50.y = 0.0f;
            sp50.z = 100.0f;
            Matrix_MultVec3f(gCalcMatrix, &sp50, &sp44);
            effect->vel.x = sp44.x;
            effect->vel.y = sp44.y;
            effect->vel.z = sp44.z;
            AUDIO_PLAY_SFX(0x09007011, effect->sfxSource, 4);
        }
        if ((gPlayer[0].unk_280 == 0) && (gPlayer[0].timer_498 == 0)) {
            Player_ApplyDamage(&gPlayer[0], 0, effect->info.damage);
            gPlayer[0].unk_0D8.x = 20.0f;
            if (effect->vel.x < 0.0f) {
                gPlayer[0].unk_0D8.x *= -1.0f;
            }
            Object_Kill(&effect->obj, effect->sfxSource);
        }
    }

    if (effect->obj.pos.y < gGroundLevel) {
        Macbeth_801ADCEC(effect->obj.pos.x, effect->obj.pos.y, effect->obj.pos.z, 999.9f, -10.0f, 5.0f);
        Object_Kill(&effect->obj, effect->sfxSource);
        if (gGroundType != GROUNDTYPE_WATER) {
            effect->obj.pos.y = gGroundLevel;
        }
    }
    sp38.x = effect->vel.x;
    sp38.y = effect->vel.y;
    sp38.z = effect->vel.z;
    if (Macbeth_801A55D4(1000, &effect->obj.pos, &sp38, 0) != 0) {
        Macbeth_801ADCEC(effect->obj.pos.x, effect->obj.pos.y, effect->obj.pos.z, 999.9f, -10.0f, 5.0f);
        Object_Kill(&effect->obj, effect->sfxSource);
    }
}

void Macbeth_801A5AF0(Effect* effect) {
    RCP_SetupDL(&gMasterDisp, 0x3C);
    gSPDisplayList(gMasterDisp++, D_MA_601A840);
    RCP_SetupDL(&gMasterDisp, 0x40);
}

void Macbeth_801A5B4C(Effect* effect) {
    if ((gPlayer[0].unk_138 - effect->obj.pos.z) < -2000.0f) {
        Object_Kill(&effect->obj, effect->sfxSource);
    }
    effect->obj.rot.x = 20.0f;
    if (effect->scale2 < 10.0f) {
        effect->obj.rot.y = 180.0f;
    } else {
        effect->obj.rot.y = 0.0f;
    }
    effect->obj.rot.z = 0.0f;
    if ((fabsf(gPlayer[0].unk_138 - effect->obj.pos.z) < 100.0f) &&
        (fabsf(gPlayer[0].pos.x - effect->obj.pos.x) < 100.0f) &&
        (fabsf(gPlayer[0].pos.y - effect->obj.pos.y) < 30.0f) && (gPlayer[0].timer_498 == 0)) {
        Player_ApplyDamage(gPlayer, 0, effect->info.damage);
        gPlayer[0].unk_0D8.x = 20.0f;
        if (effect->vel.x < 0.0f) {
            gPlayer[0].unk_0D8.x *= -1.0f;
        }
        gPlayer[0].unk_0D8.y = 20.0f;
        if (effect->vel.y < 0.0f) {
            gPlayer[0].unk_0D8.y *= -1.0f;
        }
        Object_Kill(&effect->obj, effect->sfxSource);
    }
    if (effect->obj.pos.y < (gGroundLevel - 100.0f)) {
        Object_Kill(&effect->obj, effect->sfxSource);
    }

    if (effect->unk_44 < 235) {
        effect->unk_44 += 20;
    }
}

void Macbeth_801A5D68(Effect* effect) {
    RCP_SetupDL(&gMasterDisp, 0x43);
    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 112, 255, 243, effect->unk_44);
    gDPSetEnvColor(gMasterDisp++, 255, 255, 255, effect->unk_44);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_MA_6012A60);
    RCP_SetupDL(&gMasterDisp, 0x40);
}

void Macbeth_801A5E2C(Actor* actor) {
    actor->fwork[0] = actor->obj.pos.x;
    actor->fwork[1] = actor->obj.pos.y;
    actor->fwork[2] = actor->obj.rot.z;
    actor->obj.rot.z = 0.0f;
}

void Macbeth_801A5E54(Actor* actor) {
    if ((gPlayer[0].unk_138 - actor->obj.pos.z) < -500.0f) {
        Object_Kill(&actor->obj, actor->sfxSource);
    }
    if ((D_i5_801BA1E0 - actor->obj.pos.z) < -800.0f) {
        if (actor->iwork[0] == 0) {
            AUDIO_PLAY_SFX(0x11001063, actor->sfxSource, 0);
            actor->iwork[0]++;
        }
        Math_SmoothStepToF(&actor->obj.pos.x, actor->fwork[0] + (actor->fwork[2] * 400.0f), 0.1f, 4.0f, 0.01f);
    }
    if (actor->unk_0D0 != 0) {
        actor->unk_0D0 = 0;
        AUDIO_PLAY_SFX(0x29121007, actor->sfxSource, 4);
    }
}

void Macbeth_801A5F90(Actor* actor) {
    gSPDisplayList(gMasterDisp++, D_MA_60251A0);
}

void Macbeth_801A5FC4(s32 arg0) {
}

void Macbeth_801A5FD0(Actor* actor) {
    if (gPlayer[0].unk_138 - actor->obj.pos.z < -500.0f) {
        Object_Kill(&actor->obj, actor->sfxSource);
    }
    if (gPlayer[0].unk_138 - actor->obj.pos.z < actor->fwork[2]) {
        if (actor->iwork[0] == 0) {
            AUDIO_PLAY_SFX(0x19001062, actor->sfxSource, 0);
            actor->iwork[0] += 1;
        }
        Math_SmoothStepToF(&actor->obj.pos.y, actor->fwork[1] + 356.0f, 0.4f, 20.0f, 0.01f);
    }
    if (actor->unk_0D0 != 0) {
        actor->unk_0D0 = 0;
        AUDIO_PLAY_SFX(0x29121007, actor->sfxSource, 4);
    }
}

void Macbeth_801A6100(Actor* actor) {
    gSPDisplayList(gMasterDisp++, D_MA_6025850);
}

void Macbeth_801A6134(Actor* actor) {
    actor->health = 30;
}

void Macbeth_801A6144(Actor* actor) {
    s16 i;

    if ((gPlayer[0].unk_138 - actor->obj.pos.z) < -500.0f) {
        Object_Kill(&actor->obj, actor->sfxSource);
    }

    switch (actor->state) {
        case 0:
            if (actor->unk_0D0 != 0) {
                func_effect_8007C120(actor->obj.pos.x, actor->obj.pos.y + 100.0f, actor->obj.pos.z, actor->vel.x,
                                     actor->vel.y, actor->vel.z, 0.15f, 20);
                AUDIO_PLAY_SFX(0x2903300E, actor->sfxSource, 4);
                actor->health -= actor->damage;
                actor->timer_0C6 = 15;
                if ((gPlayer[0].unk_138 - 20.0f) < actor->obj.pos.z) {
                    actor->health = 0;
                }
                if (actor->health <= 0) {
                    AUDIO_PLAY_SFX(0x2903B009, actor->sfxSource, 0);
                    func_effect_8007BFFC(actor->obj.pos.x, actor->obj.pos.y + 100.0f, actor->obj.pos.z, 0.0f, 0.0f,
                                         0.0f, 14.0f, 5);
                    for (i = 0; i < 20; i++) {
                        Macbeth_801AD624(RAND_FLOAT_CENTERED(500.0f) + actor->obj.pos.x, actor->obj.pos.y + 100.0f,
                                         RAND_FLOAT(150.0f) + actor->obj.pos.z, RAND_FLOAT_CENTERED(10.0f),
                                         RAND_FLOAT(7.0f) + 7.0f, RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT(360.0f),
                                         RAND_FLOAT(360.0f), RAND_FLOAT(360.0f), RAND_FLOAT_CENTERED(30.0f),
                                         RAND_FLOAT_CENTERED(30.0f), RAND_FLOAT_CENTERED(30.0f),
                                         (s32) (RAND_FLOAT(50.0f) + 70.0f), 4, (RAND_FLOAT(0.8f) + 0.3f) * 1.5f);
                    }
                    actor->timer_0BC = 20;
                    actor->state = 1;
                }
                actor->unk_0D0 = 0;
            }
            break;
        case 1:
            Math_SmoothStepToF(&actor->obj.rot.x, -90.0f, 0.5f, 5.0f, 0.01f);
            if (actor->timer_0BC == 0) {
                Object_Kill(&actor->obj, actor->sfxSource);
            }
            break;
    }
}

void Macbeth_801A6540(Actor* actor) {
    RCP_SetupDL(&gMasterDisp, 0x39);
    if ((actor->timer_0C6 % 2) != 0) {
        RCP_SetupDL(&gMasterDisp, 0x3A);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
    }
    gSPDisplayList(gMasterDisp++, D_MA_60257B0);
    RCP_SetupDL(&gMasterDisp, 0x1D);
}

void Macbeth_801A65E0(Object_80* obj80) {
    obj80->vel.x = obj80->obj.pos.x;
    obj80->vel.y = obj80->obj.pos.y;
    obj80->vel.z = obj80->obj.rot.z;
    obj80->obj.rot.z = 0.0f;
}

void Macbeth_801A6608(Object_80* obj80) {
    if ((gPlayer[0].unk_138 - obj80->obj.pos.z) < obj80->vel.z) {
        if (gPlayState != PLAY_PAUSE) {
            Math_SmoothStepToF(&obj80->vel.x, 30, 0.5f, 30.0f, 0.0f);
            if (obj80->vel.x < 31.0f) {
                obj80->vel.x = 255.0f;
            }
        }
        RCP_SetupDL(&gMasterDisp, 0x22);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, obj80->vel.x, 0, 0, 255);
    }
    gSPDisplayList(gMasterDisp++, D_MA_6010700);
    RCP_SetupDL(&gMasterDisp, 0x1D);
    gSPDisplayList(gMasterDisp++, D_MA_601F270);
}

void Macbeth_801A67BC(s32 arg0) {
}

void Macbeth_801A67C8(Actor* actor) {
    if ((gPlayer[0].unk_138 - actor->obj.pos.z) < -300.0f) {
        Object_Kill(&actor->obj, actor->sfxSource);
    }
    if ((actor->unk_0D0 != 0) && (actor->unk_0D2 == -1)) {
        actor->unk_0D0 = 0;
        if (actor->obj.pos.x <= gPlayer[0].pos.x) {
            actor->iwork[4] = 1;
        } else {
            actor->iwork[4] = -1;
        }

        Macbeth_8019D670(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z,
                         (RAND_FLOAT(2.0f) + 20.0f) * actor->iwork[4], 0.0f, actor->iwork[4] * -34.0f, 0.0f, 2, 3);
        Object_Kill(&actor->obj, actor->sfxSource);
    }
}

void Macbeth_801A68EC(Actor* actor) {
}

void Macbeth_801A68F8(Actor* actor, s16 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    gTexturedLines[arg1].mode = 3;
    gTexturedLines[arg1].unk_04.x = arg2;
    gTexturedLines[arg1].unk_04.y = arg3;
    gTexturedLines[arg1].unk_28 = 5.0f;
    gTexturedLines[arg1].unk_2C = gTexturedLines[arg1].unk_2D = gTexturedLines[arg1].unk_2E =
        gTexturedLines[arg1].unk_2F = 255;
    gTexturedLines[arg1].timer = 3;
    gTexturedLines[arg1].unk_04.z = arg4;
    gTexturedLines[arg1].unk_10.x = arg5;
    gTexturedLines[arg1].unk_10.y = arg6;
    gTexturedLines[arg1].unk_10.z = arg7;
}

void Macbeth_801A6984(Actor* actor) {
    s16 var_s3;
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

    var_s3 = 0;
    if ((gPlayer[0].unk_138 - actor->obj.pos.z) > 7000.0f) {
        return;
    }
    test.x = actor->obj.pos.x - D_i5_801BE368[4];
    test.y = actor->obj.pos.y - D_i5_801BE368[5];
    test.z = actor->obj.pos.z - D_i5_801BE368[6];
    temp_fs3 = VEC3F_MAG(&test);
    Math_Atan2F(test.x, test.z);
    Math_Atan2F(test.y, sqrtf(SQ(test.x) + SQ(test.z)));
    var_s4 = (s32) (temp_fs3 / 40.0f);
    if (var_s4 == 0) {
        var_s4 = 1;
    }
    spA8 = (180.0f / var_s4) + 1.0f;
    var_fs5 = actor->obj.pos.x;
    spA0 = actor->obj.pos.y;
    sp9C = actor->obj.pos.z;

    sp88 = (D_i5_801BE368[4] - actor->obj.pos.x) / var_s4;
    sp84 = (D_i5_801BE368[5] - actor->obj.pos.y) / var_s4;
    sp80 = (D_i5_801BE368[6] - actor->obj.pos.z) / var_s4;
    for (i = 0; i < var_s4; i++) {
        if (D_i5_801BE320[1] == 0) {
            Math_SmoothStepToF(&D_i5_801BE368[7], 0.0f, 0.01f, 0.05f, 0.01f);
        } else {
            Math_SmoothStepToF(&D_i5_801BE368[7], 100.0f, 0.01f, 0.01f, 0.01f);
        }
        temp = SIN_DEG(i * spA8) * (-(D_i5_801BE368[7] * 3.0f) * (1.0f - ((f32) i / var_s4)));
        temp_fs2_2 = actor->obj.pos.x + (sp88 * i);
        temp_fs3_2 = actor->obj.pos.y + (sp84 * i) + temp;
        temp_fs4 = actor->obj.pos.z + (sp80 * i);
        Macbeth_801A68F8(actor, var_s3++, var_fs5, spA0, sp9C, temp_fs2_2, temp_fs3_2, temp_fs4);
        var_fs5 = temp_fs2_2;
        spA0 = temp_fs3_2;
        sp9C = temp_fs4;
    }
    Macbeth_80199D88(D_MA_6012C98, 4, 8);
}

void Macbeth_801A6C78(Actor* actor) {
    // FAKE
    if (1) {}
    Macbeth_801A0308(actor, actor->obj.pos.z, actor->obj.rot.y, 0);
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
            if ((((gPlayer[0].unk_138 - actor->obj.pos.z) * 0.25f) < D_i5_801BE368[3]) ||
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
    Math_SmoothStepToF(&actor->obj.pos.x, actor->fwork[19] + D_i5_801BE368[1], 0.2f, 30.0f, 0.01f);
    Math_SmoothStepToF(&actor->obj.pos.y, (actor->fwork[5] + 600.0f) + D_i5_801BE368[3], 0.2f, 30.0f, 0.01f);
    Math_SmoothStepToF(&actor->obj.pos.z, 1200.0f + D_i5_801BE368[6], 0.2f, 30.0f, 0.01f);
}

void Macbeth_801A6FB4(Actor* actor) {
    // FAKE
    if (1) {}
    Macbeth_801A0308(actor, actor->obj.pos.z, actor->obj.rot.y, 0);
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
            if ((((gPlayer[0].unk_138 - actor->obj.pos.z) * 0.25f) < D_i5_801BE368[3]) ||
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
    Math_SmoothStepToF(&actor->obj.pos.x, actor->fwork[19] + D_i5_801BE368[1], 0.2f, 30.0f, 0.01f);
    Math_SmoothStepToF(&actor->obj.pos.y, (actor->fwork[5] + 600.0f) + D_i5_801BE368[3], 0.2f, 30.0f, 0.01f);
    Math_SmoothStepToF(&actor->obj.pos.z, 1200.0f + D_i5_801BE368[6], 0.2f, 30.0f, 0.01f);
}

void Macbeth_801A72DC(Actor* actor) {
    Macbeth_801A0308(actor, actor->obj.pos.z, actor->obj.rot.y, 0);
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
    Math_SmoothStepToF(&actor->obj.pos.x, actor->fwork[19] + D_i5_801BE368[1], 0.2f, 30.0f, 0.01f);
    Math_SmoothStepToF(&actor->obj.pos.y, actor->fwork[5] + 600.0f, 0.2f, 30.0f, 0.01f);
    Math_SmoothStepToF(&actor->obj.pos.z, 1200.0f + D_i5_801BE368[6], 0.2f, 30.0f, 0.01f);
}

void Macbeth_801A74C4(Actor* actor) {
    Macbeth_801A0308(actor, actor->obj.pos.z, actor->obj.rot.y, 0);
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
            if ((((gPlayer[0].unk_138 - actor->obj.pos.z) * 0.25f) < D_i5_801BE368[3]) ||
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
            Math_SmoothStepToF(&actor->obj.rot.z, 45.0f, 0.4f, 10.0f, 1.0f);
            if (actor->obj.rot.z >= 45.0f) {
                D_i5_801BE320[12] = 1;
            }
            break;
        case 1:
            Math_SmoothStepToF(&actor->obj.rot.z, -45.0f, 0.4f, 10.0f, 1.0f);
            if (actor->obj.rot.z <= -45.0f) {
                D_i5_801BE320[12] = 0;
            }
            break;
    }
    Math_SmoothStepToF(&actor->obj.pos.x, actor->fwork[19] + D_i5_801BE368[1], 0.2f, 30.0f, 0.01f);
    Math_SmoothStepToF(&actor->obj.pos.y, (actor->fwork[5] + 600.0f) + D_i5_801BE368[3], 0.2f, 30.0f, 0.01f);
    Math_SmoothStepToF(&actor->obj.pos.z, 1200.0f + D_i5_801BE368[6], 0.2f, 30.0f, 0.01f);
}

void Macbeth_801A78B0(Actor* actor) {
    Macbeth_801A0308(actor, actor->obj.pos.z, actor->obj.rot.y, 0);
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

    Math_SmoothStepToF(&actor->obj.pos.x, actor->fwork[19] + D_i5_801BE368[1], 0.1f, 10.0f, 0.01f);
}

void Macbeth_801A7A30(Actor* actor) {
    Macbeth_801A0308(actor, actor->obj.pos.z, actor->obj.rot.y, 0);
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
    actor->obj.pos.x = actor->fwork[19] + D_i5_801BE368[1];
    actor->obj.pos.y = actor->fwork[5] + D_i5_801BE368[3];
    actor->obj.pos.z = 1200.0f + D_i5_801BE368[6];
}

void Macbeth_801A7CAC(Actor* actor) {
    f32 temp_fa0;
    f32 temp_fa1;
    f32 sp34;
    f32 sp30;
    f32 sp2C;

    temp_fa0 = gPlayer[0].pos.x - actor->obj.pos.x;
    temp_fa1 = (gPlayer[0].unk_138 - 130.0f) - actor->obj.pos.z;
    sp2C = sqrtf(SQ(temp_fa0) + SQ(temp_fa1));
    sp30 = Math_Atan2F(temp_fa0, temp_fa1);
    sp34 = -Math_Atan2F(gPlayer[0].pos.y - actor->obj.pos.y, sp2C);
    Math_SmoothStepToAngle(&actor->obj.rot.y, Math_RadToDeg(sp30), 0.1f, 20.0f, 0.01f);
    Math_SmoothStepToAngle(&actor->obj.rot.x, Math_RadToDeg(sp34), 0.1f, 20.0f, 0.01f);
}

void Macbeth_801A7D98(Actor* actor) {
    u8 i;

    Macbeth_80199F8C(actor);
    // clang-format off
    for (i = 0; i < 35; i++) { D_i5_801BE320[i] = 0; }
    for (i = 0; i < 50; i++) { D_i5_801BE368[i] = 0.0f; }
    // clang-format on
    D_i5_801BE320[29] = 250;
    D_i5_801BE320[9] = 200;
    D_i5_801BE320[10] = 250;
    actor->info.hitbox = LOAD_ASSET(gHitboxNone);
    D_i5_801BE320[14] = 0;
    D_i5_801BE320[15] = 0;
    gBossFrameCount = 0;
}

static Vec3f D_i5_801BA744 = { 0.0f, 0.0f, 0.0f };
static Vec3f D_i5_801BA750 = { 0.0f, 0.0f, 30.0f };

void Macbeth_801A7E7C(Actor* actor) {
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

    switch (actor->state) {
        case 0:
            Macbeth_8019A198(actor);
            Macbeth_801A015C(actor);
            actor->obj.pos.y += 250.0f;
            D_i5_801BE320[3] = 0;
            Macbeth_8019A830(actor);
            Macbeth_8019A728(actor);
            if (actor->iwork[1] != 0) {
                AUDIO_PLAY_BGM(SEQ_ID_MA_BOSS | SEQ_FLAG);
                actor->state = 1;
            }
            Macbeth_801A6984(actor);
            break;
        case 1:
            Macbeth_8019A198(actor);
            Macbeth_801A015C(actor);
            actor->obj.pos.y += 250.0f;
            D_i5_801BE320[3]++;
            if (D_i5_801BE320[3] >= 20) {
                actor->timer_0BC = 20;
                actor->state = 2;
            }
            Macbeth_8019A830(actor);
            Macbeth_801A6984(actor);
            break;
        case 2:
            Macbeth_8019A198(actor);
            Macbeth_801A0308(actor, actor->obj.pos.z, actor->obj.rot.y, 0);
            if (actor->timer_0BC == 0) {
                Math_SmoothStepToF(&actor->obj.pos.y, actor->fwork[5] + 500.0f, 0.5f, 5.0f, 5.0f);
                D_i5_801BE320[5] = 1;
                D_i5_801BE320[7] = 1;
                if ((actor->fwork[5] + 500.0f) <= actor->obj.pos.y) {
                    Radio_PlayMessage(gMsg_ID_17430, RCID_BOSS_MACBETH);
                    actor->info.hitbox = LOAD_ASSET(D_MA_603677C);
                    actor->state = 3;
                }
            }
            Macbeth_8019A830(actor);
            Macbeth_801A6984(actor);
            break;
        case 3:
            Macbeth_8019A198(actor);
            if (actor->timer_0BC == 0) {
                actor->obj.pos.z -= 2.0f;
                if (D_i5_801BE320[3] < 70) {
                    D_i5_801BE320[3] = (s16) (D_i5_801BE320[3] + 1);
                }
                if (D_i5_801BE320[3] == 30) {
                    D_i5_801BE320[5] = 0;
                    D_i5_801BE320[7] = 0;
                    D_i5_801BE320[6] = 1;
                    D_i5_801BE320[8] = 1;
                }
                Math_SmoothStepToF(&actor->obj.pos.y, actor->fwork[5] + 1600.0f, 0.2f, 30.0f, 10.0f);
                if ((actor->fwork[5] + 1600.0f) <= actor->obj.pos.y) {
                    D_i5_801BE320[6] = 0;
                    D_i5_801BE320[8] = 0;
                    D_i5_801BE320[3] = 0;
                    D_i5_801BE320[2] = 1;
                    D_i5_801BE320[31] = 30;
                    actor->timer_0C0 = 1500;
                    actor->state = 4;
                }
            }
            Macbeth_8019A830(actor);
            Macbeth_801A6984(actor);
            break;
        case 4:
            Math_SmoothStepToAngle(&actor->obj.rot.z, 0.0f, 0.1f, 20.0f, 0.01f);
            Macbeth_8019A198(actor);
            D_i5_801BE320[3]++;
            if (D_i5_801BE320[3] >= 60) {
                D_i5_801BE320[3] = 0;
            }
            Macbeth_801A6C78(actor);
            Macbeth_801A6984(actor);
            Macbeth_801A7CAC(actor);
            if ((D_i5_801BE320[16] != 0) && (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_3)) {
                var_v1 = 0xFF;
                if (D_i5_801BE320[18] == 2) {
                    var_v1 = 3;
                } else if (D_i5_801BE320[18] == 3) {
                    var_v1 = 0;
                } else if (D_i5_801BE320[18] == 4) {
                    D_i5_801BE320[3] = 0;
                    D_i5_801BE320[2] = 2;
                    D_i5_801BE320[31] = 30;
                    actor->iwork[7] = 0;
                    actor->iwork[8] = 0;
                    actor->iwork[9] = 0;
                    Radio_PlayMessage(gMsg_ID_17475, RCID_BOSS_MACBETH);
                    actor->state = 18;
                    break;
                }
                if (!(var_v1 & gGameFrameCount)) {
                    if ((D_i5_801BE320[9] > 0) || (D_i5_801BE320[10] > 0)) {
                        if (actor->timer_0C0 == 0) {
                            actor->timer_0C0 = 1500;
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
                                actor->timer_0BC = 100;
                                AUDIO_PLAY_SFX(0x19022067, actor->sfxSource, 4);
                                actor->state = 12;
                            }
                        } else if ((D_i5_801BE320[26] != 0) && (D_i5_801BE320[10] > 0)) {
                            D_i5_801BE320[6] = 1;
                            D_i5_801BE320[8] = 1;
                            D_i5_801BE320[5] = 0;
                            D_i5_801BE320[7] = 0;
                            D_i5_801BE320[3] = 0;
                            D_i5_801BE320[2] = 2;
                            D_i5_801BE320[31] = 30;
                            actor->state = 5;
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
                            actor->timer_0BC = 100;
                            actor->state = 15;
                        } else {
                            D_i5_801BE320[6] = 1;
                            D_i5_801BE320[8] = 0;
                            D_i5_801BE320[5] = 0;
                            D_i5_801BE320[7] = 0;
                            D_i5_801BE320[3] = 0;
                            D_i5_801BE320[2] = 4;
                            D_i5_801BE320[31] = 30;
                            actor->timer_0BC = 20;
                            actor->state = 11;
                        }
                    }
                }
            }
            break;
        case 5:
            Macbeth_8019A198(actor);
            Macbeth_801A0308(actor, actor->obj.pos.z, actor->obj.rot.y, 0);
            Math_SmoothStepToF(&actor->obj.pos.x, gPlayer[0].pos.x, 0.1f, 10.0f, 0.01f);
            Math_SmoothStepToF(&actor->obj.pos.z, gPlayer[0].unk_138 - 1500.0f, 0.1f, 20.0f, 0.01f);
            Math_SmoothStepToF(&actor->obj.pos.y,
                               (actor->fwork[5] + 600.0f + (gPlayer[0].unk_138 - actor->obj.pos.z) * 0.25f) + 10.0f,
                               0.1f, 10.0f, 0.01f);
            if (((actor->fwork[5] + 600.0f + (gPlayer[0].unk_138 - actor->obj.pos.z) * 0.25f) <= actor->obj.pos.y) &&
                (actor->obj.pos.z < (gPlayer[0].unk_138 - 1300.0f))) {
                actor->timer_0BC = 0;
                actor->state = 6;
            }
            Macbeth_801A7CAC(actor);
            Macbeth_801A6984(actor);
            break;
        case 6:
            Macbeth_8019A198(actor);
            if (actor->timer_0BC <= 0) {
                actor->state = 7;
            }
            D_i5_801BE368[9] = gPlayer[0].pos.x;
            Macbeth_801A7CAC(actor);
            Macbeth_801A6984(actor);
            break;
        case 7:
            if ((gPlayer[0].unk_138 - actor->obj.pos.z) < 1200.0f) {
                if (D_i5_801BE320[3] < (Animation_GetFrameCount(&D_MA_601D188) - 1)) {
                    D_i5_801BE320[3] = (s16) (D_i5_801BE320[3] + 1);
                    if ((D_i5_801BE320[3] == 26) && (D_i5_801BE320[10] > 0)) {
                        actor->info.hitbox = LOAD_ASSET(D_MA_6036818);
                        AUDIO_PLAY_SFX(0x2902405E, actor->sfxSource, 4);
                    }
                } else {
                    actor->info.hitbox = LOAD_ASSET(gHitboxNone);
                    if ((gPlayer[0].pos.y + 1200.0f) < actor->obj.pos.y) {
                        actor->info.hitbox = LOAD_ASSET(D_MA_603677C);
                        D_i5_801BE320[3] = 0;
                        D_i5_801BE320[2] = 1;
                        D_i5_801BE320[31] = 30;
                        D_i5_801BE320[6] = 0;
                        D_i5_801BE320[8] = 0;
                        actor->state = 4;
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
            if (var_fv0 < (gPlayer[0].unk_138 - actor->obj.pos.z)) {
                Macbeth_801A7CAC(actor);
                D_i5_801BE368[9] = gPlayer[0].pos.x;
            }
            Math_SmoothStepToF(&actor->obj.pos.x, D_i5_801BE368[9], 0.2f, 30.0f, 0.01f);
            if (D_i5_801BE320[3] < 29) {
                Math_SmoothStepToF(&actor->obj.pos.y, gPlayer[0].pos.y + 250.0f, 0.3f, 45.0f, 0.01f);
            } else {
                Math_SmoothStepToF(&actor->obj.pos.y, gPlayer[0].pos.y + 1210.0f, 0.1f, 20.0f, 0.01f);
            }
            Math_SmoothStepToF(&actor->obj.pos.z, gPlayer[0].unk_138 - 100.0f, 0.3f, 60.0f, 0.01f);
            Math_SmoothStepToF(&actor->obj.rot.x, 0.0f, 0.2f, 20.0f, 0.01f);
            Macbeth_801A6984(actor);
            break;
        case 8:
            Macbeth_8019A198(actor);
            if (((gGameFrameCount % 16) == 0)) {
                AUDIO_PLAY_SFX(0x29036099, actor->sfxSource, 4);
            }
            Macbeth_801A74C4(actor);
            Macbeth_801A6984(actor);
            if (D_i5_801BE320[3] < (Animation_GetFrameCount(&D_MA_6017714) - 1)) {
                D_i5_801BE320[3] = (s16) (D_i5_801BE320[3] + 1);
            } else {
                D_i5_801BE320[3] = 0;
            }
            if (D_i5_801BE320[4] <= 0) {
                D_i5_801BE320[3] = 0;
                D_i5_801BE320[2] = 1;
                actor->obj.rot.x -= 360.0f;
                D_i5_801BE320[3] = 0;
                D_i5_801BE320[2] = 1;
                D_i5_801BE320[31] = 30;
                D_i5_801BE320[5] = 0;
                D_i5_801BE320[7] = 0;
                D_i5_801BE320[6] = 0;
                D_i5_801BE320[8] = 0;
                actor->state = 4;
                break;
            }
            if (actor->unk_0D0 != 0) {
                actor->unk_0D0 = 0;
                actor->iwork[9] = 15;
                D_i5_801BE320[29] -= actor->damage;
                if (D_i5_801BE320[29] <= 0) {
                    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 1);
                    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 1);
                    gFillScreenRed = gFillScreenGreen = gFillScreenBlue = gFillScreenAlpha = 255;
                    AUDIO_PLAY_SFX(0x2940D09A, actor->sfxSource, 4);
                    Radio_PlayMessage(gMsg_ID_17450, RCID_BOSS_MACBETH);
                    func_effect_8007D2C8(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, 10.0f);
                    Macbeth_801AD624(actor->vwork[2].x, actor->vwork[2].y, actor->vwork[2].z,
                                     RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT(7.0f) + 7.0f, -2.0f, RAND_FLOAT(360.0f),
                                     RAND_FLOAT(360.0f), RAND_FLOAT(360.0f), RAND_FLOAT_CENTERED(30.0f),
                                     RAND_FLOAT_CENTERED(30.0f), RAND_FLOAT_CENTERED(30.0f),
                                     (s32) (RAND_FLOAT(50.0f) + 70.0f), 11, 1.0f);
                    D_i5_801BE320[3] = 0;
                    D_i5_801BE320[2] = 1;
                    D_i5_801BE320[31] = 30;
                    actor->state = 9;
                    break;
                }
                D_i5_801BE368[12] = 30.0f;
                D_i5_801BE368[13] = 30.0f;
                if (D_i5_801BE320[29] > 0) {
                    if (D_i5_801BE320[29] > 100) {
                        AUDIO_PLAY_SFX(0x29034003, actor->sfxSource, 4);
                    } else {
                        AUDIO_PLAY_SFX(0x2943500F, actor->sfxSource, 4);
                    }
                }
            }
            if (((gGameFrameCount % 2) == 0)) {
                actor->obj.pos.x += D_i5_801BE368[12];
                actor->obj.pos.y += D_i5_801BE368[13];
            } else {
                actor->obj.pos.x -= D_i5_801BE368[12];
                actor->obj.pos.y -= D_i5_801BE368[13];
            }
            if (D_i5_801BE368[12] > 0.0f) {
                D_i5_801BE368[12] -= 1.0f;
            }
            if (D_i5_801BE368[13] > 0.0f) {
                D_i5_801BE368[13] -= 1.0f;
            }
            Math_SmoothStepToAngle(&actor->obj.rot.x, 0.0f, 0.1f, 20.0f, 0.01f);
            Math_SmoothStepToAngle(&actor->obj.rot.y, 0.0f, 0.1f, 20.0f, 0.01f);
            if (((gGameFrameCount % 32) == 0)) {
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
            if (D_i5_801BE368[6] < actor->obj.pos.z) {
                D_i5_801BE320[1] = 1;
                Macbeth_801A6984(actor);
            }
            if ((actor->obj.pos.z - D_i5_801BE368[6]) < 500) {
                Math_SmoothStepToF(&actor->obj.pos.x, D_i5_801BE368[4], 0.1f, 10.0f, 1.0f);
                Math_SmoothStepToF(&actor->obj.pos.y, D_i5_801BE368[5] - 100.0f, 0.1f, 15.0f, 10.0f);
            } else {
                Math_SmoothStepToF(&actor->obj.pos.y, D_i5_801BE368[5] + 600.0f, 0.1f, 20.0f, 10.0f);
            }
            Math_SmoothStepToF(&actor->obj.pos.z, D_i5_801BE368[6] - 100.0f, 0.2f, 5.0f - gActors[D_i5_801BE314].vel.z,
                               1.0f);
            actor->obj.rot.x += 10.0f;
            actor->obj.rot.z += 10.0f;
            if (((gGameFrameCount % 8) == 0)) {
                func_effect_8007D2C8(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, 10.0f);
                func_effect_8007C688(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, 5.0f, 8);
            }
            if ((actor->obj.pos.z <= D_i5_801BE368[6]) && (actor->obj.pos.y <= D_i5_801BE368[5])) {
                D_i5_801BE320[23] = 1;
                D_ctx_8017796C = -1;
                actor->state = 10;
                actor->timer_0BC = 50;
            }
            break;
        case 10:
            Object_Kill(&actor->obj, actor->sfxSource);
            break;
        case 11:
            Math_SmoothStepToAngle(&actor->obj.rot.y, 0.0f, 0.1f, 20.0f, 0.01f);
            Math_SmoothStepToAngle(&actor->obj.rot.x, 0.0f, 0.1f, 20.0f, 0.01f);
            Math_SmoothStepToAngle(&actor->obj.rot.z, 0.0f, 0.1f, 20.0f, 0.01f);
            Macbeth_8019A198(actor);
            Macbeth_801A6FB4(actor);
            Macbeth_801A6984(actor);
            if (actor->timer_0BC == 0) {
                if (D_i5_801BE320[3] < (Animation_GetFrameCount(&D_MA_6016B2C) - 1)) {
                    D_i5_801BE320[3]++;
                } else {
                    D_i5_801BE320[3] = 0;
                }
                switch (D_i5_801BE320[18]) {
                    case 0:
                    case 1:
                        var_v0 = 0xF;
                        var_s0 = 10;
                        break;
                    case 2:
                        var_v0 = 0xF;
                        var_s0 = 20;
                        break;
                    case 3:
                        var_v0 = 7;
                        var_s0 = 20;
                        break;

                    default:
                        var_v0 = 3;
                        var_s0 = 10;
                        break;
                }
                if (!(var_v0 & gGameFrameCount)) {
                    Macbeth_801ADCEC(actor->obj.pos.x, actor->obj.pos.y - 90.0f, actor->obj.pos.z - 50.0f,
                                     D_i5_801BE368[0] * 0.8f, -10.0f, 8.0f);
                    D_i5_801BE320[11]++;
                    if (D_i5_801BE320[11] >= var_s0) {
                        actor->info.hitbox = LOAD_ASSET(D_MA_603677C);
                        D_i5_801BE320[3] = 0;
                        D_i5_801BE320[2] = 1;
                        D_i5_801BE320[31] = 30;
                        D_i5_801BE320[5] = 0;
                        D_i5_801BE320[7] = 0;
                        D_i5_801BE320[11] = 0;
                        actor->state = 4;
                        D_i5_801BE320[25] = 1;
                    }
                }
            }
            if (((gGameFrameCount % 32) == 0)) {
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
            Math_SmoothStepToAngle(&actor->obj.rot.y, 0.0f, 0.1f, 20.0f, 0.01f);
            Math_SmoothStepToAngle(&actor->obj.rot.x, 0.0f, 0.1f, 20.0f, 0.01f);
            Math_SmoothStepToAngle(&actor->obj.rot.z, 0.0f, 0.1f, 20.0f, 0.01f);
            if (D_i5_801BE320[3] < (Animation_GetFrameCount(&D_MA_60163F0) - 1)) {
                D_i5_801BE320[3]++;
            } else {
                D_i5_801BE320[3] = 0;
            }
            Macbeth_8019A198(actor);
            Macbeth_801A72DC(actor);
            Macbeth_801A6984(actor);
            if (D_i5_801BE320[9] <= 0) {
                Audio_KillSfxBySourceAndId(actor->sfxSource, 0x19022067);
                actor->state = 14;
                actor->vel.y = -20.0f;
            }
            D_i5_801BE368[14] = actor->vwork[0].x;
            D_i5_801BE368[15] = actor->vwork[0].y;
            D_i5_801BE368[16] = actor->vwork[0].z;
            if (actor->timer_0BC > 15) {
                for (i = 0; i < 2; i++) {
                    D_i5_801BE368[23] = 3.0f;
                    Macbeth_801AE800(actor->vwork[2].x + RAND_FLOAT_CENTERED(400.0f),
                                     actor->vwork[2].y + RAND_FLOAT_CENTERED(400.0f), actor->vwork[2].z + 50.0f,
                                     actor->vwork[2].x - 200.0f, actor->vwork[2].y, actor->vwork[2].z);
                    D_i5_801BE368[23] = 4.0f;
                    Macbeth_801AE800(actor->vwork[4].x + RAND_FLOAT_CENTERED(400.0f),
                                     actor->vwork[4].y + RAND_FLOAT_CENTERED(400.0f), actor->vwork[4].z + 50.0f,
                                     actor->vwork[4].x + 200.0f, actor->vwork[4].y, actor->vwork[4].z);
                }
            }
            if (actor->timer_0BC == 0) {
                Audio_KillSfxBySourceAndId(actor->sfxSource, 0x19022067);
                D_i5_801BE320[3] = 0;
                D_i5_801BE320[2] = 6;
                D_i5_801BE320[31] = 30;
                actor->timer_0BC = 70;
                actor->state = 13;
            }

            break;
        case 13:
            Math_SmoothStepToAngle(&actor->obj.rot.y, 0.0f, 0.1f, 20.0f, 0.01f);
            Math_SmoothStepToAngle(&actor->obj.rot.x, 0.0f, 0.1f, 20.0f, 0.01f);
            Math_SmoothStepToAngle(&actor->obj.rot.z, 0.0f, 0.1f, 20.0f, 0.01f);
            if (D_i5_801BE320[3] < (Animation_GetFrameCount(&D_MA_6016040) - 1)) {
                D_i5_801BE320[3]++;
            }
            Macbeth_8019A198(actor);
            Macbeth_801A72DC(actor);
            Macbeth_801A6984(actor);
            D_i5_801BE320[5] = 0;
            D_i5_801BE320[7] = 0;
            if (actor->timer_0BC == 60) {
                AUDIO_PLAY_SFX(0x19023068, actor->sfxSource, 4);
                D_i5_801BE320[24] = 0;

                spC6 = RAND_INT(5.0f);
                for (i = 0; i < 10; i++) {
                    Macbeth_801AE610(actor->vwork[0].x, actor->vwork[0].y + 100.0f, actor->vwork[0].z,
                                     RAND_FLOAT_CENTERED(35.0f), RAND_FLOAT(80) + 90.0f, RAND_RANGE(-72.0f, 8.0f),
                                     spC6);
                }

                for (i = 0; i < 20; i++) {
                    Macbeth_801AD624(actor->vwork[0].x, actor->vwork[0].y + 50.0f + RAND_FLOAT(50.0f),
                                     actor->vwork[0].z, RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT(5.0f),
                                     actor->vel.z + 2.0f, RAND_FLOAT(360.0f), RAND_FLOAT(360.0f), RAND_FLOAT(360.0f),
                                     RAND_FLOAT_CENTERED(30.0f), RAND_FLOAT_CENTERED(30.0f), RAND_FLOAT_CENTERED(30.0f),
                                     (s32) (RAND_FLOAT(25.0f) + 30.f), 10, RAND_FLOAT(1.0f));
                }
                actor->timer_0BC = 80;
                actor->state = 14;
                actor->vel.y = -20.0f;
            }
            break;
        case 14:
            Math_SmoothStepToAngle(&actor->obj.rot.y, 0.0f, 0.1f, 20.0f, 0.01f);
            Math_SmoothStepToAngle(&actor->obj.rot.x, 0.0f, 0.1f, 20.0f, 0.01f);
            Math_SmoothStepToAngle(&actor->obj.rot.z, 0.0f, 0.1f, 20.0f, 0.01f);
            if (D_i5_801BE320[3] < (Animation_GetFrameCount(&D_MA_6016040) - 1)) {
                D_i5_801BE320[3]++;
            }
            Macbeth_8019A198(actor);
            actor->vel.y += 1.0f;
            Macbeth_801A6984(actor);
            D_i5_801BE320[6] = 1;
            D_i5_801BE320[8] = 1;
            if (actor->timer_0BC == 0) {
                actor->vel.y = 0.0f;
                actor->info.hitbox = LOAD_ASSET(D_MA_603677C);
                D_i5_801BE320[3] = 0;
                D_i5_801BE320[2] = 1;
                D_i5_801BE320[31] = 30;
                actor->state = 4;
            }
            break;
        case 15:
            Math_SmoothStepToAngle(&actor->obj.rot.y, 0.0f, 0.1f, 20.0f, 0.01f);
            Math_SmoothStepToAngle(&actor->obj.rot.x, 0.0f, 0.1f, 20.0f, 0.01f);
            Math_SmoothStepToAngle(&actor->obj.rot.z, 0.0f, 0.1f, 20.0f, 0.01f);
            Math_SmoothStepToF(&actor->obj.pos.z, gPlayer[0].unk_138 - 700.0f, 0.2f, 15.0f, 0.01f);
            Math_SmoothStepToF(&actor->obj.pos.y, gPlayer[0].pos.y + 400.0f, 0.2f, 10.0f, 0.01f);
            Math_SmoothStepToF(&actor->obj.pos.x, gPlayer[0].pos.x, 0.1f, 10.0f, 0.01f);
            if (D_i5_801BE320[3] < 15) {
                D_i5_801BE320[3]++;
            }
            Macbeth_8019A198(actor);
            Macbeth_801A6984(actor);
            if (actor->timer_0BC < 100) {
                if (actor->timer_0BC == 98) {
                    AUDIO_PLAY_SFX(0x19022069, actor->sfxSource, 4);
                }
                Matrix_RotateY(gCalcMatrix, RAND_FLOAT(2.0f) * (M_DTOR * 180.0f), 0);
                sp360.x = 0.0f;
                sp360.y = RAND_FLOAT(100.0f);
                sp360.z = RAND_FLOAT(200.0f) + 100.0f;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp360, &sp354);
                D_i5_801BE368[23] = 1.0f;
                Macbeth_801AE800(actor->vwork[2].x + sp354.x - 50.0f, actor->vwork[2].y + sp354.y + 100.0f,
                                 actor->vwork[2].z + sp354.z, actor->vwork[2].x, actor->vwork[2].y, actor->vwork[2].z);
                D_i5_801BE368[23] = 2.0f;
                Macbeth_801AE800(actor->vwork[4].x + sp354.x + 50.0f, actor->vwork[4].y + sp354.y + 100.0f,
                                 actor->vwork[4].z + sp354.z, actor->vwork[4].x, actor->vwork[4].y, actor->vwork[4].z);
            }
            if (actor->timer_0BC == 0) {
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
                actor->timer_0BC = D_i5_801BE320[27];
                actor->state = 16;
                Audio_KillSfxBySourceAndId(actor->sfxSource, 0x19022069);
            }
            break;
        case 16:
            Math_SmoothStepToAngle(&actor->obj.rot.y, 0.0f, 0.1f, 20.0f, 0.01f);
            Math_SmoothStepToAngle(&actor->obj.rot.x, 0.0f, 0.1f, 20.0f, 0.01f);
            Math_SmoothStepToAngle(&actor->obj.rot.z, 0.0f, 0.1f, 20.0f, 0.01f);
            Math_SmoothStepToF(&actor->obj.pos.z, gPlayer[0].unk_138 - 250.0f, 0.1f, 15.0f, 0.01f);
            Math_SmoothStepToF(&actor->obj.pos.y, 250.0f, 0.1f, 10.0f, 0.01f);
            if (D_i5_801BE320[3] < (Animation_GetFrameCount(&D_MA_6015C24) - 1)) {
                D_i5_801BE320[3]++;
            }
            Macbeth_8019A198(actor);
            Macbeth_801A6984(actor);

            if (actor->timer_0BC < (D_i5_801BE320[27] - 40)) {
                if ((actor->timer_0BC + 42) == D_i5_801BE320[27]) {
                    actor->sfxSource[0] = actor->vwork[2].x;
                    AUDIO_PLAY_SFX(0x19006035, actor->sfxSource, 4);
                    actor->sfxSource[0] = actor->vwork[4].x;
                    AUDIO_PLAY_SFX(0x19006035, actor->sfxSource, 4);
                    actor->sfxSource[0] = actor->obj.pos.x;
                }
                if (((gGameFrameCount % 2) == 0) && (D_i5_801BE320[15] == 0)) {
                    actor->vwork[6].x = actor->vwork[2].x + 80.0f;
                    actor->vwork[6].y = 0.0f;
                    actor->vwork[6].z = gPlayer[0].unk_138 + 50.0f;
                    actor->vwork[7].x = actor->vwork[4].x - 80.0f;
                    actor->vwork[7].y = 0.0f;
                    actor->vwork[7].z = gPlayer[0].unk_138 + 50.0f;
                    actor->vwork[6].z += actor->vel.z;
                    actor->vwork[7].z += actor->vel.z;
                    sp348.x = actor->vwork[6].x - actor->vwork[2].x;
                    sp348.y = actor->vwork[6].y - actor->vwork[2].y + 25.0f;
                    sp348.z = actor->vwork[6].z - actor->vwork[2].z;
                    Matrix_RotateZ(gCalcMatrix, -actor->vwork[3].z * M_DTOR, 0);
                    Matrix_RotateX(gCalcMatrix, -actor->vwork[3].x * M_DTOR, 1);
                    Matrix_RotateY(gCalcMatrix, -actor->vwork[3].y * M_DTOR, 1);
                    Matrix_MultVec3f(gCalcMatrix, &sp348, &sp354);
                    D_i5_801BE368[14] = Math_RadToDeg(Math_Atan2F(sp354.x, sp354.z));
                    temp = sqrtf(SQ(sp354.x) + SQ(sp354.z));
                    D_i5_801BE368[13] = Math_RadToDeg(-Math_Atan2F(sp354.y, temp));
                    Matrix_RotateY(gCalcMatrix, actor->vwork[3].y * M_DTOR, 0);
                    Matrix_RotateX(gCalcMatrix, actor->vwork[3].x * M_DTOR, 1);
                    Matrix_RotateZ(gCalcMatrix, actor->vwork[3].z * M_DTOR, 1);
                    Matrix_MultVec3f(gCalcMatrix, &D_i5_801BA744, &sp354);
                    sp348.x = actor->vwork[2].x + sp354.x;
                    sp348.y = actor->vwork[2].y + sp354.y + 25.0f;
                    sp348.z = actor->vwork[2].z + sp354.z;
                    sp33C.x = D_i5_801BE368[13];
                    sp33C.y = D_i5_801BE368[14];
                    sp33C.z = 0.0f;
                    sp330.x = actor->vwork[3].x;
                    sp330.y = actor->vwork[3].y;
                    sp330.z = actor->vwork[3].z;
                    func_effect_8007EE68(OBJ_EFFECT_380, &sp348, &sp33C, &sp330, &D_i5_801BA750, 5.0f);
                    sp348.x = actor->vwork[7].x - actor->vwork[4].x;
                    sp348.y = actor->vwork[7].y - actor->vwork[4].y + 25.0f;
                    sp348.z = actor->vwork[7].z - actor->vwork[4].z;
                    Matrix_RotateZ(gCalcMatrix, -actor->vwork[5].z * M_DTOR, 0);
                    Matrix_RotateX(gCalcMatrix, -actor->vwork[5].x * M_DTOR, 1);
                    Matrix_RotateY(gCalcMatrix, -actor->vwork[5].y * M_DTOR, 1);
                    Matrix_MultVec3f(gCalcMatrix, &sp348, &sp354);
                    D_i5_801BE368[14] = Math_RadToDeg(Math_Atan2F(sp354.x, sp354.z));
                    temp = sqrtf(SQ(sp354.x) + SQ(sp354.z));
                    D_i5_801BE368[13] = Math_RadToDeg(-Math_Atan2F(sp354.y, temp));
                    Matrix_RotateY(gCalcMatrix, actor->vwork[5].y * M_DTOR, 0);
                    Matrix_RotateX(gCalcMatrix, actor->vwork[5].x * M_DTOR, 1);
                    Matrix_RotateZ(gCalcMatrix, actor->vwork[5].z * M_DTOR, 1);
                    Matrix_MultVec3f(gCalcMatrix, &D_i5_801BA744, &sp354);
                    sp348.x = actor->vwork[4].x + sp354.x;
                    sp348.y = actor->vwork[4].y + sp354.y + 25.0f;
                    sp348.z = actor->vwork[4].z + sp354.z;
                    sp33C.x = D_i5_801BE368[13];
                    sp33C.y = D_i5_801BE368[14];
                    sp33C.z = 0.0f;
                    sp330.x = actor->vwork[5].x;
                    sp330.y = actor->vwork[5].y;
                    sp330.z = actor->vwork[5].z;
                    func_effect_8007EE68(OBJ_EFFECT_380, &sp348, &sp33C, &sp330, &D_i5_801BA750, 10.0f);
                }
            }
            if (actor->timer_0BC < (D_i5_801BE320[27] - 50)) {
                Macbeth_801A78B0(actor);
            }
            if (actor->timer_0BC == 0) {
                Audio_KillSfxBySourceAndId(actor->sfxSource, 0x19006035);
                actor->info.hitbox = LOAD_ASSET(D_MA_603677C);
                D_i5_801BE320[3] = 0;
                D_i5_801BE320[2] = 1;
                D_i5_801BE320[31] = 30;
                actor->state = 4;
                D_i5_801BE320[25] = 1;
            }
            break;
        case 18:
            Macbeth_8019A198(actor);
            Macbeth_801A0308(actor, actor->obj.pos.z, actor->obj.rot.y, 0);
            Math_SmoothStepToF(&actor->obj.pos.x, gPlayer[0].pos.x, 0.1f, 10.0f, 0.01f);
            Math_SmoothStepToF(&actor->obj.pos.z, gPlayer[0].unk_138 - 1200.0f, 0.1f, 35.0f, 0.01f);
            Math_SmoothStepToF(&actor->obj.pos.y, actor->fwork[5] + 600.0f + D_i5_801BE368[3], 0.1f, 20.0f, 10.0f);
            if (D_i5_801BE368[3] < ((gPlayer[0].unk_138 - actor->obj.pos.z) / 5.0f)) {
                Math_SmoothStepToF(&D_i5_801BE368[2], 15.0f, 0.2f, 2.0f, 0.01f);
                D_i5_801BE368[3] += D_i5_801BE368[2];
            } else if (((actor->fwork[5] + 600.0f) + D_i5_801BE368[3]) <= actor->obj.pos.y) {
                actor->timer_0BC = 0;
                actor->state = 19;
            }
            Macbeth_801A7CAC(actor);
            Macbeth_801A6984(actor);
            break;
        case 19:
            actor->vel.z = gPlayer[0].vel.z;
            Macbeth_801A7CAC(actor);
            D_i5_801BE368[4] += D_i5_801BE368[32];
            D_i5_801BE368[5] += D_i5_801BE368[33];
            D_i5_801BE368[6] += D_i5_801BE368[34];
            if (D_i5_801BE320[1] < 200) {
                D_i5_801BE320[1]++;
            }
            Math_SmoothStepToF(&D_i5_801BE368[32], actor->obj.pos.x + RAND_FLOAT(500.0f), 0.2f, 20.0f, 0.01f);
            Math_SmoothStepToF(&D_i5_801BE368[33], actor->obj.pos.y + RAND_FLOAT(100.0f), 0.2f, 10.0f, 0.01f);
            Math_SmoothStepToF(&D_i5_801BE368[34], actor->obj.pos.y + RAND_FLOAT(500.0f), 0.2f, 20.0f, 0.01f);
            if (actor->unk_0D0 != 0) {
                gPlayer[0].shields = 0;
            }
            if (((gGameFrameCount % 16) == 0)) {
                func_effect_8007D2C8(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, 10.0f);
            }
            D_i5_801BE368[9] = gPlayer[0].pos.x;
            Math_SmoothStepToF(&actor->obj.pos.x, D_i5_801BE368[9], 0.2f, 35.0f, 0.01f);
            Math_SmoothStepToF(&actor->obj.pos.y, gPlayer[0].pos.y, 0.3f, 15.0f, 0.01f);
            Math_SmoothStepToF(&actor->obj.pos.z, gPlayer[0].unk_138, 0.3f, 20.0f, 0.01f);
            Math_SmoothStepToF(&actor->obj.rot.x, 60.0f, 0.2f, 20.0f, 0.01f);
            Macbeth_801A6984(actor);
            break;
        case 20:
            Math_SmoothStepToF(&actor->obj.rot.z, 0.0f, 0.1f, 20.0f, 0.01f);
            Macbeth_8019A198(actor);
            actor->vel.z = gActors[D_i5_801BE314].vel.z;
            D_i5_801BE320[3]++;
            if (D_i5_801BE320[3] >= 60) {
                D_i5_801BE320[3] = 0;
            }
            Macbeth_801A7A30(actor);
            Macbeth_801A6984(actor);
            Math_SmoothStepToF(&actor->obj.rot.y, 0.0f, 0.1f, 20.0f, 0.01f);
            if (actor->obj.pos.z < -135200.0f) {
                BonusText_Display(actor->obj.pos.x, actor->obj.pos.y + sp374, actor->obj.pos.z, 50);
                if (1) {}
                gHitCount += 51;
                D_ctx_80177850 = 15;
                func_effect_8007D2C8(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, 20.0f);
                Macbeth_801AD624(actor->vwork[2].x, actor->vwork[2].y, actor->vwork[2].z, RAND_FLOAT_CENTERED(10.0f),
                                 RAND_FLOAT(7.0f) + 7.0f, 2.0f, RAND_FLOAT(360.0f), RAND_FLOAT(360.0f),
                                 RAND_FLOAT(360.0f), RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT_CENTERED(10.0f),
                                 RAND_FLOAT_CENTERED(10.0f), (s32) (RAND_FLOAT(50.0f) + 70.0f), 11, 1.0f);
                D_80137E84[gMainController] = 1;
                D_Timer_80177BD0[gMainController] = 15;
                AUDIO_PLAY_SFX(0x2940C00A, actor->sfxSource, 4);
                actor->state = 21;
            }
            break;
        case 21:
            Object_Kill(&actor->obj, actor->sfxSource);
            break;
        default:
            break;
    }
    if ((actor->unk_0D0 != 0) && (actor->state >= 2)) {
        actor->unk_0D0 = 0;
        if ((actor->unk_0D2 == 0) && (D_i5_801BE320[9] > 0) && ((gPlayer[0].unk_138 - actor->obj.pos.z) > 200.0f)) {
            AUDIO_PLAY_SFX(0x2903300E, actor->sfxSource, 4);
            actor->iwork[7] = 15;
            D_i5_801BE320[9] -= actor->damage;
            Macbeth_801AD624(actor->obj.pos.x, actor->obj.pos.y + 80, actor->obj.pos.z + 50.0f,
                             RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT(5.0f), RAND_FLOAT_CENTERED(3.0f),
                             RAND_FLOAT(360.0f), RAND_FLOAT(360.0f), RAND_FLOAT(360.0f), RAND_FLOAT_CENTERED(30.0f),
                             RAND_FLOAT_CENTERED(30.0f), RAND_FLOAT_CENTERED(30.0f), (s32) (RAND_FLOAT(50.0f) + 70.0f),
                             3, RAND_FLOAT(1.0f));
            if (D_i5_801BE320[9] <= 0) {
                AUDIO_PLAY_SFX(0x2903B009, actor->sfxSource, 4);
                func_effect_8007D2C8(actor->obj.pos.x, actor->obj.pos.y + 80.0f, actor->obj.pos.z + 50.0f, 5.0f);
                for (i = 0; i < 2; i++) {
                    Macbeth_801AD624(actor->obj.pos.x, actor->obj.pos.y + 80.0f, actor->obj.pos.z + 50.0f,
                                     RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT(5.0f), RAND_FLOAT_CENTERED(3.0f),
                                     RAND_FLOAT(360.0f), RAND_FLOAT(360.0f), RAND_FLOAT(360.0f),
                                     RAND_FLOAT_CENTERED(30.0f), RAND_FLOAT_CENTERED(30.0f), RAND_FLOAT_CENTERED(30.f),
                                     (s32) (RAND_FLOAT(50.0f) + 70.0f), 3, RAND_FLOAT(1.0f));
                }
                Macbeth_801AD624(actor->obj.pos.x, actor->obj.pos.y + 80.0f, actor->obj.pos.z + 50.0f,
                                 RAND_FLOAT_CENTERED(3.0f), RAND_FLOAT(15.0f), -2.0f, RAND_FLOAT(360.0f),
                                 RAND_FLOAT(360.0f), RAND_FLOAT(360.0f), RAND_FLOAT_CENTERED(10.0f),
                                 RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT_CENTERED(10.0f),
                                 (s32) (RAND_FLOAT(50.0f) + 70.0f), 8, 1.0f);
            }
        } else if ((actor->unk_0D2 == 1) && (D_i5_801BE320[10] > 0) &&
                   ((gPlayer[0].unk_138 - actor->obj.pos.z) > 200.0f)) {
            AUDIO_PLAY_SFX(0x2903300E, actor->sfxSource, 4);
            actor->iwork[8] = 16;
            D_i5_801BE320[10] -= actor->damage;
            Macbeth_801AD624(actor->obj.pos.x, actor->obj.pos.y - 30.0f, actor->obj.pos.z, RAND_FLOAT_CENTERED(10.0f),
                             RAND_FLOAT(7.0f) + 7.0f, RAND_FLOAT_CENTERED(3.0f), RAND_FLOAT(360.0f), RAND_FLOAT(360.0f),
                             RAND_FLOAT(360.0f), RAND_FLOAT_CENTERED(30.0f), RAND_FLOAT_CENTERED(30.0f),
                             RAND_FLOAT_CENTERED(30.0f), (s32) (RAND_FLOAT(50.0f) + 70.0f), 3, RAND_FLOAT(1.0f));
            if (D_i5_801BE320[10] <= 0) {
                AUDIO_PLAY_SFX(0x2903B009, actor->sfxSource, 4);
                func_effect_8007D2C8(actor->obj.pos.x, actor->obj.pos.y - 30.0f, actor->obj.pos.z, 6.0f);

                for (i = 0; i < 10; i++) {
                    Macbeth_801AD624(actor->obj.pos.x, actor->obj.pos.y - 30.0f, actor->obj.pos.z,
                                     RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT(7.0f) + 7.0f, RAND_FLOAT_CENTERED(3.0f),
                                     RAND_FLOAT(360.0f), RAND_FLOAT(360.0f), RAND_FLOAT(360.0f),
                                     RAND_FLOAT_CENTERED(30.0f), RAND_FLOAT_CENTERED(30.0f), RAND_FLOAT_CENTERED(30.0f),
                                     (s32) (RAND_FLOAT(50.0f) + 70.0f), 3, RAND_FLOAT(1.0f));
                }
                Macbeth_801AD624(actor->obj.pos.x, actor->obj.pos.y - 30.0f, actor->obj.pos.z + 50.0f,
                                 RAND_FLOAT_CENTERED(3.0f), RAND_FLOAT(15.0f), -2.0f, RAND_FLOAT(360.0f),
                                 RAND_FLOAT(360.0f), RAND_FLOAT(360.0f), RAND_FLOAT_CENTERED(10.0f),
                                 RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT_CENTERED(10.0f),
                                 (s32) (RAND_FLOAT(50.0f) + 70.0f), 9, 1.0f);
            }
        } else {
            AUDIO_PLAY_SFX(0x29121007, actor->sfxSource, 4);
        }
    }
    if (D_i5_801BE320[4] != 0) {
        if ((actor->state != 8) && (actor->state != 10) && (actor->state != 9)) {
            D_i5_801BE320[5] = 1;
            D_i5_801BE320[7] = 1;
            D_i5_801BE320[6] = 1;
            D_i5_801BE320[8] = 1;
            D_i5_801BE320[3] = 0;
            D_i5_801BE320[2] = 3;
            D_i5_801BE320[31] = 30;
            D_i5_801BE368[12] = 0.0f;
            D_i5_801BE368[13] = 0.0f;
            actor->state = 8;
        }
    }
    if ((D_i5_801BE320[16] != 0) && (gPlayer[0].state_1C8 != PLAYERSTATE_1C8_7)) {
        if (gBossFrameCount == 0) {
            Radio_PlayMessage(gMsg_ID_2225, RCID_SLIPPY);
        } else if (gBossFrameCount > 155) {
            gShowBossHealth = 1;
            gBossHealthBar = (s32) ((D_i5_801BE320[29] / 250.f) * 85.0f);
            gBossHealthBar += (s32) ((D_i5_801BE320[9] / 200.f) * 85.0f);
            gBossHealthBar += (s32) ((D_i5_801BE320[10] / 250.f) * 85.0f);
        }
        gBossFrameCount++;
    }

    if (actor->iwork[7] > 0) {
        actor->iwork[7]--;
    }

    if (actor->iwork[8] > 0) {
        actor->iwork[8]--;
    }

    if (actor->iwork[9] > 0) {
        actor->iwork[9]--;
    }
    D_i5_801BE368[14] = actor->vwork[0].x;
    D_i5_801BE368[15] = actor->vwork[0].y;
    D_i5_801BE368[16] = actor->vwork[0].z;
    D_i5_801BE368[24] = actor->vwork[2].x;
    D_i5_801BE368[25] = actor->vwork[2].y;
    D_i5_801BE368[26] = actor->vwork[2].z;
    D_i5_801BE368[27] = actor->vwork[4].x;
    D_i5_801BE368[28] = actor->vwork[4].y;
    D_i5_801BE368[29] = actor->vwork[4].z;
    D_i5_801BE368[19] = actor->vel.z;
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
    if ((gPlayer[0].state_1C8 == PLAYERSTATE_1C8_7) && (actor->state < 20)) {
        D_i5_801BE320[3] = 0;
        D_i5_801BE320[2] = 1;
        D_i5_801BE320[31] = 30;
        actor->state = 20;
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

bool Macbeth_801ABC14(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* data) {
    Actor* actor = (Actor*) data;
    s16 sp62;

    RCP_SetupDL(&gMasterDisp, 0x1D);
    gSPClearGeometryMode(gMasterDisp++, G_TEXTURE_GEN);
    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
    switch (limbIndex) {
        case 2:
        case 3:
        case 4:
        case 25:
        case 26:
        case 27:
            if (actor->state == 9) {
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
            RCP_SetupDL(&gMasterDisp, 0x22);
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
                Matrix_Mult(gGfxMatrix, gCalcMatrix, 1);
                Matrix_Push(&gGfxMatrix);
                Matrix_Scale(gGfxMatrix, D_i5_801BE368[31], D_i5_801BE368[30], D_i5_801BE368[31], 1);
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
            if ((actor->iwork[7] % 2) != 0) {
                RCP_SetupDL(&gMasterDisp, 0x1C);
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
            if ((actor->iwork[8] % 2) != 0) {
                RCP_SetupDL(&gMasterDisp, 0x1C);
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
            }
            if (D_i5_801BE320[10] <= 0) {
                *dList = NULL;
            }
            break;
        default:
            break;
    }

    if ((actor->iwork[9] % 2) != 0) {
        RCP_SetupDL(&gMasterDisp, 0x1C);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
    }
    return false;
}

void Macbeth_801AC1C0(s32 limbIndex, Vec3f* rot, void* data) {
    Vec3f sp2C = { 0.0f, 0.0f, 0.0f };
    Actor* actor = (Actor*) data;

    switch (limbIndex) {
        case 14:
            Matrix_MultVec3f(gCalcMatrix, &sp2C, &actor->vwork[0]);
            Matrix_GetYRPAngles(gCalcMatrix, &actor->vwork[1]);
            break;
        case 4:
            Matrix_MultVec3f(gCalcMatrix, &sp2C, &actor->vwork[2]);
            Matrix_GetYRPAngles(gCalcMatrix, &actor->vwork[3]);
            break;
        case 7:
            Matrix_MultVec3f(gCalcMatrix, &sp2C, &actor->vwork[4]);
            Matrix_GetYRPAngles(gCalcMatrix, &actor->vwork[5]);
            break;
    }
}

void Macbeth_801AC294(Actor* actor) {
    if (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_3) {
        if (((gPlayer[0].unk_138 - actor->obj.pos.z) > 7000.0f) ||
            ((gPlayer[0].unk_138 - actor->obj.pos.z) < -1000.0f)) {
            return;
        }
    } else {
        if (((gPlayer[0].unk_138 - actor->obj.pos.z) > 7000.0f) ||
            ((gPlayer[0].unk_138 - actor->obj.pos.z) < -5000.0f)) {
            return;
        }
    }

    if (D_i5_801BE320[2] == 0) {
        Matrix_Translate(gCalcMatrix, actor->fwork[25], 0.0f, 0.0f, 1);
        Matrix_RotateY(gCalcMatrix, actor->fwork[26] * M_DTOR, 1);
        Matrix_RotateX(gCalcMatrix, actor->fwork[29] * M_DTOR, 1);
        Animation_GetFrameData(&D_MA_601EA28, D_i5_801BE320[3], D_i5_801BE430);
    }
    Animation_DrawSkeleton(3, D_MA_600D1E4, D_i5_801BE430, Macbeth_801ABC14, Macbeth_801AC1C0, actor, gCalcMatrix);
}

void Macbeth_801AC42C(s32 arg0) {
}

void Macbeth_801AC438(Actor* actor) {
    switch (actor->state) {
        case 0:
            Macbeth_8019A198(actor);
            Macbeth_801A015C(actor);
            Macbeth_8019A728(actor);
            if (actor->iwork[1] != 0) {
                Radio_PlayMessage(gMsg_ID_17420, RCID_BOSS_MACBETH);
                AUDIO_PLAY_SFX(0x19034066, actor->sfxSource, 4);
                actor->info.hitbox = LOAD_ASSET(D_MA_6035A94);
                actor->state += 1;
            }
            Macbeth_8019A830(actor);
            break;
        case 1:
            Macbeth_8019A198(actor);
            Macbeth_801A015C(actor);
            Math_SmoothStepToF(&D_i5_801BE368[8], 160.0f, 0.1f, 3.0f, 0.01f);
            Macbeth_8019A830(actor);
            break;
    }
    if (actor->unk_0D0 != 0) {
        actor->unk_0D0 = 0;
        AUDIO_PLAY_SFX(0x29121007, actor->sfxSource, 4);
    }
}

bool Macbeth_801AC5AC(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* data) {
    RCP_SetupDL(&gMasterDisp, 0x1D);
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

void Macbeth_801AC6B4(Actor* actor) {
    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_195;
    actor->obj.pos.x = 0.0f;
    actor->obj.pos.y = 3000.0f;
    actor->obj.pos.z = 0.0f;
    actor->obj.rot.y = 180.0f;
    Object_SetInfo(&actor->info, actor->obj.id);
    AUDIO_PLAY_SFX(0x11030010, actor->sfxSource, 0);
    actor->unk_0B6 = 1;
}

static f32 D_i5_801BA768 = 0.0f;

void Macbeth_801AC754(Player* player) {
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    ObjectInit* objInit;
    s32 i;
    f32 zeroVar = 0.0f;

    sp4C = 0.0f;
    sp48 = 0.0f;
    sp44 = 0.0f;
    func_play_800ADF58(player);

    switch (player->unk_1D0) {
        case 0:

            objInit = gLevelObjects = LOAD_ASSET(D_MA_6035678);

            for (i = 0; objInit->id != OBJ_INVALID; i++, objInit++) {
                Object_Load(objInit, 4000.0f, -4000.0f, 4000.0f, -4000.0f);
            }

            objInit = gLevelObjects = LOAD_ASSET(gLevelObjectInits[gCurrentLevel]);

            for (i = 0; i < 40; i++, objInit++) {
                Object_Load(objInit, 4000.0f, -4000.0f, 4000.0f, -4000.0f);
            }

            gFillScreenRed = gFillScreenGreen = gFillScreenBlue = gFillScreenAlpha = 255;
            player->unk_144 -= 800.0f;
            player->unk_1D0 = 1;
            D_i5_801BE24C = 8.0f;
            D_i5_801BA768 = 0.0f;
            break;
        case 1:
            gCsFrameCount = 0;
            player->unk_0D4 = 0.0f;
            player->pos.x = 0.0f;
            player->pos.y = -3.0f;
            player->vel.z = -15.0f;
            player->camEye.x = gCsCamEyeX = -518.0f;
            player->camEye.y = gCsCamEyeY = 3882.5f;
            player->camEye.z = gCsCamEyeZ = 200.0f;
            player->camAt.x = gCsCamAtX = -910.0f;
            player->camAt.y = gCsCamAtY = 42.0f;
            player->camAt.z = gCsCamAtZ = -800.0f;
            player->unk_240 = 1;
            player->unk_1D0 = 2;
            gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
            gFillScreenAlpha = 255;
            Macbeth_801ACF6C();
            /* fallthrough */
        case 2:
            if (gCsFrameCount < 30) {
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
                gFillScreenAlpha = 255;
            }
            if ((gCsFrameCount < 60) && ((gCsFrameCount % 16U) == 0)) {
                Macbeth_801ACF6C();
            } else if ((gCsFrameCount < 100) && ((gCsFrameCount % 32) == 0)) {
                Macbeth_801ACF6C();
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
                    player->unk_1D0 = 3;
                    player->timer_1F8 = 10;
                }
            }
            break;
        case 3:
            AUDIO_PLAY_BGM(SEQ_ID_MACBETH | SEQ_FLAG);
            gLevelStatusScreenTimer = 50;
            player->state_1C8 = PLAYERSTATE_1C8_3;
            player->unk_1D0 = player->timer_1F8 = player->timer_1FC = player->unk_240 = 0;
            player->unk_0D4 = 3.0f;
            player->unk_014 = 0.0f;
            D_ctx_8017782C = 1;
            func_play_800A594C();
            D_ctx_8017782C = 0;
            D_ctx_80177DC8 = 40;
            player->unk_1D0 = 4;
            break;
        case 4:
        default:
            break;
    }
    player->unk_138 = player->pos.z += player->vel.z;
    Math_SmoothStepToF(&player->camEye.x, gCsCamEyeX, D_ctx_80177A48[0], sp4C, 0);
    Math_SmoothStepToF(&player->camEye.y, gCsCamEyeY, D_ctx_80177A48[1], sp48, 0);
    Math_SmoothStepToF(&player->camEye.z, gCsCamEyeZ, D_ctx_80177A48[2], sp44, 0);
    Math_SmoothStepToF(&player->camAt.x, gCsCamAtX, D_ctx_80177A48[0], sp4C, 0);
    Math_SmoothStepToF(&player->camAt.y, gCsCamAtY, D_ctx_80177A48[1], sp48, 0);
    Math_SmoothStepToF(&player->camAt.z, gCsCamAtZ, D_ctx_80177A48[2], sp44, 0);
    player->unk_0A0 = 0.0f;
    player->unk_0F4 += player->vel.z * 5.0f;
    player->unk_0F0 = SIN_DEG(player->unk_0F4) * 0.7f;
    Texture_Scroll(D_landmaster_3002E80, 32, 32, 0);
    if ((gCsFrameCount > 150) && ((-player->unk_138 - player->unk_144) > 200.0f)) {
        if (D_i5_801BA768 < 11.5f) {
            D_i5_801BA768 += 0.2f;
        }
        player->unk_144 += D_i5_801BA768;
    }
}

void Macbeth_801ACE40(Effect* effect) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.pos.x = gPlayer[0].camEye.x + RAND_FLOAT_CENTERED(600.0f);
    effect->obj.pos.y = gPlayer[0].camEye.y - 1000.0f;
    effect->obj.pos.z = gPlayer[0].unk_138 - 2000.0f;
    effect->obj.id = OBJ_EFFECT_352;
    effect->timer_50 = 80;
    effect->unk_46 = 144;
    effect->vel.x = 10.0f;
    effect->vel.z = 40.0f;
    effect->vel.y = 8.0f;
    effect->scale2 = RAND_FLOAT(15.0f) + 10.0f;
    if (Rand_ZeroOne() < 0.5f) {
        effect->obj.rot.z = 180.0f;
    }
    Object_SetInfo(&effect->info, effect->obj.id);
}

void Macbeth_801ACF6C(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Macbeth_801ACE40(&gEffects[i]);
            break;
        }
    }
}

void Macbeth_801ACFBC(void) {
    ObjectInit* objInit;

    for (objInit = gLevelObjects = LOAD_ASSET(D_MA_60357CC); objInit->id != OBJ_INVALID; objInit++) {
        Object_Load(objInit, 4000.0f, -4000.0f, 4000.0f, -4000.0f);
    }
}

void Macbeth_801AD080(void) {
    ObjectInit* objInit;

    for (objInit = gLevelObjects = LOAD_ASSET(D_MA_6035920); objInit->id != OBJ_INVALID; objInit++) {
        Object_Load(objInit, 4000.0f, -4000.0f, 4000.0f, -4000.0f);
    }
}

void Macbeth_801AD144(PlayerShot* playerShot) {
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

    temp_fs2 = playerShot->unk_44 * 40.0f;
    actor = &gActors[0];

    for (i = 0; i < 60; i++, actor++) {
        if ((actor->obj.status == OBJ_ACTIVE) && (actor->timer_0C2 == 0) && (actor->obj.id >= OBJ_ACTOR_205) &&
            (actor->obj.id <= OBJ_ACTOR_213)) {
            temp_s6 = gGameFrameCount % 8U;
            var_s1 = &actor->info.hitbox[0];
            temp_ft3 = var_s1[0];
            var_s1++;
            if (temp_ft3 != 0) {
                for (j = 0; j < temp_ft3; j++, var_s1 += 6) {
                    if (var_s1[0] == 200000.0f) {
                        Matrix_RotateZ(gCalcMatrix, -var_s1[3] * M_DTOR, 0);
                        Matrix_RotateX(gCalcMatrix, -var_s1[1] * M_DTOR, 1);
                        Matrix_RotateY(gCalcMatrix, -var_s1[2] * M_DTOR, 1);
                        Matrix_RotateZ(gCalcMatrix, -actor->obj.rot.z * M_DTOR, 1);
                        Matrix_RotateX(gCalcMatrix, -actor->obj.rot.x * M_DTOR, 1);
                        Matrix_RotateY(gCalcMatrix, -actor->obj.rot.y * M_DTOR, 1);
                        var_s1 += 4;
                    } else {
                        Matrix_RotateZ(gCalcMatrix, -actor->obj.rot.z * M_DTOR, 0);
                        Matrix_RotateX(gCalcMatrix, -actor->obj.rot.x * M_DTOR, 1);
                        Matrix_RotateY(gCalcMatrix, -actor->obj.rot.y * M_DTOR, 1);
                    }
                    if ((j == temp_s6) && (var_s1[1] > -100.0f) && (var_s1[3] > -100.0f)) {
                        sp8C.x = playerShot->obj.pos.x - actor->obj.pos.x;
                        sp8C.y = playerShot->obj.pos.y - actor->obj.pos.y;
                        sp8C.z = playerShot->obj.pos.z - actor->obj.pos.z;
                        Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp8C, &sp80);
                        test.x = (var_s1[4] + actor->obj.pos.x) - (actor->obj.pos.x + sp80.x);
                        test.y = (var_s1[2] + actor->obj.pos.y) - (actor->obj.pos.y + sp80.y);
                        test.z = (var_s1[0] + actor->obj.pos.z) - (actor->obj.pos.z + sp80.z);
                        if ((gLevelMode == LEVELMODE_ON_RAILS) && (test.z < 0.0f)) {
                            test.z *= 0.6f;
                        }
                        if (VEC3F_MAG(&test) < temp_fs2) {
                            actor->unk_0D2 = j;
                            actor->unk_0D0 = -1;
                            if ((gPlayer[0].unk_138 - actor->obj.pos.z) < 5000.0f) {
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

void Macbeth_801AD554(Effect* effect, f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 xRot, f32 yRot,
                      f32 zRot, f32 argA, f32 argB, f32 argC, s16 argD, s16 argE, f32 scale2) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_ACTIVE;
    effect->obj.id = OBJ_EFFECT_357;
    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;
    effect->obj.rot.x = xRot;
    effect->obj.rot.y = yRot;
    effect->obj.rot.z = zRot;
    effect->vel.x = xVel;
    effect->vel.y = yVel;
    effect->vel.z = zVel;
    effect->scale2 = scale2;
    effect->timer_50 = argD;
    effect->unk_60.x = argA;
    effect->unk_60.y = argB;
    effect->unk_60.z = argC;
    effect->unk_44 = argE;
    Object_SetInfo(&effect->info, effect->obj.id);
}

void Macbeth_801AD624(f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 xRot, f32 yRot, f32 zRot,
                      f32 arg9, f32 argA, f32 argB, s16 argC, s16 argD, f32 scale2) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Macbeth_801AD554(&gEffects[i], xPos, yPos, zPos, xVel, yVel, zVel, xRot, yRot, zRot, arg9, argA, argB, argC,
                             argD, scale2);
            break;
        }
    }
}
void Macbeth_801AD6E8(void) {
}

void Macbeth_801AD6F0(Actor* actor) {
    Vec3f sp4C = { 0.0f, -10.0f, 0.0f };

    if ((gPlayer[0].unk_138 - actor->obj.pos.z) < -500.0f) {
        Object_Kill(&actor->obj, actor->sfxSource);
    }

    switch (actor->state) {
        case 0:
            if ((actor->timer_0BC == 0) &&
                ((actor->vel.y -= 0.5f, (func_enmy_8006351C(actor->index, &actor->obj.pos, &sp4C, 1) != 0)) ||
                 (actor->obj.pos.y < (gGroundLevel + 10.0f)) || (actor->iwork[0] != 0))) {
                actor->vel.x = 0.0f;
                actor->vel.y = 0.0f;
                actor->vel.z = 0.0f;
                if (actor->obj.pos.y < (gGroundLevel + 10.0f)) {
                    actor->obj.pos.y = gGroundLevel;
                }
                actor->state = 1;
                actor->timer_0BC = 200;
                actor->unk_046 = 192;
                actor->scale = 2.5f;
                actor->fwork[0] = 2.5f;
                AUDIO_PLAY_SFX(0x2903B009, actor->sfxSource, 4);
                func_effect_8007D0E0(actor->obj.pos.x, actor->obj.pos.y + 30.0f, actor->obj.pos.z, 7.0f);
                func_effect_8007BFFC(actor->obj.pos.x, actor->obj.pos.y + 30.0f, actor->obj.pos.z, 0.0f, 0.0f, 0.0f,
                                     4.0f, 5);
                if (actor->obj.pos.y < (gGroundLevel + 10.0f)) {
                    func_beam_800365E4(actor->obj.pos.x, 3.0f, actor->obj.pos.z, actor->obj.pos.x, actor->obj.pos.z,
                                       0.0f, 0.0f, 90.0f, 5.0f, 0, 0);
                }
                D_80137E84[gMainController] = 1;
                D_Timer_80177BD0[gMainController] = 10;
            }
            break;
        case 1:
            actor->scale += ((20.0f - actor->scale) * 0.1f);
            if (actor->scale > 19.0f) {
                actor->fwork[0] -= 0.3f;
                actor->unk_046 -= 20;
                if (actor->unk_046 < 0) {
                    Object_Kill(&actor->obj, actor->sfxSource);
                }
            }
            actor->obj.rot.y = 180.0f - actor->obj.rot.y;
            if ((fabsf(gPlayer[0].unk_138 - actor->obj.pos.z) < 40.0f) &&
                (fabsf(gPlayer[0].pos.x - actor->obj.pos.x) < 80.0f)) {
                if ((gPlayer[0].pos.y - actor->obj.pos.y > -5.0f) &&
                    (gPlayer[0].pos.y - actor->obj.pos.y < (actor->scale * 35.0f)) && (gPlayer[0].timer_498 == 0)) {
                    Player_ApplyDamage(&gPlayer[0], 0, actor->info.damage);
                }
            }
            break;
    }
}

void Macbeth_801ADAC8(Actor* actor) {
    switch (actor->state) {
        case 0:
            Graphics_SetScaleMtx(actor->scale);
            RCP_SetupDL_60(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
            gSPDisplayList(gMasterDisp++, D_ENMY_PLANET_4008CE0);
            RCP_SetupDL(&gMasterDisp, 0x40);
            break;
        case 1:
            Matrix_Scale(gGfxMatrix, actor->fwork[0], actor->scale, 2.5f, 1);
            Matrix_SetGfxMtx(&gMasterDisp);
            RCP_SetupDL_40();
            gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
            gSPDisplayList(gMasterDisp++, D_ENMY_PLANET_4008F70);
            RCP_SetupDL(&gMasterDisp, 0x40);
            break;
    }
}

void Macbeth_801ADC08(Actor* actor, f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel) {
    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_220;
    actor->obj.pos.x = xPos;
    actor->obj.pos.y = yPos;
    actor->obj.pos.z = zPos;
    if (xVel == 999.9f) {
        actor->iwork[0] = 1;
        actor->vel.x = 0.0f;
    } else {
        actor->vel.x = xVel;
        actor->iwork[0] = 0;
    }
    actor->vel.y = yVel;
    actor->vel.z = zVel;
    actor->timer_0BC = 0;
    Object_SetInfo(&actor->info, actor->obj.id);
    AUDIO_PLAY_SFX(0x2900201D, actor->sfxSource, 4);
}

void Macbeth_801ADCEC(f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel) {
    s32 i;

    for (i = ARRAY_COUNT(gActors) - 1; i >= 0; i--) {
        if (gActors[i].obj.status == OBJ_FREE) {
            Macbeth_801ADC08(&gActors[i], xPos, yPos, zPos, xVel, yVel, zVel);
            break;
        }
    }
}

void Macbeth_801ADD68(Actor* actor) {
    Vec3f sp3C = { 0.0f, -10.0f, 0.0f };
    s32 var_v0;

    if ((gPlayer[0].unk_138 - actor->obj.pos.z) < -500.0f) {
        Object_Kill(&actor->obj, actor->sfxSource);
    }

    switch (actor->state) {
        case 0:
            if (actor->timer_0BC == 0) {
                actor->vel.y -= 2.5f;
                if (actor->vel.y < 20.0f) {
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

                    Math_SmoothStepToF(&actor->obj.pos.x,
                                       gPlayer[0].pos.x + D_i5_801BA570[actor->iwork[2]][actor->iwork[1]] / var_v0,
                                       0.2f, 30.0f, 0.01f);
                    Math_SmoothStepToF(&actor->obj.pos.z,
                                       gPlayer[0].unk_138 - D_i5_801BA638[actor->iwork[2]][actor->iwork[1]] / var_v0,
                                       0.2f, 40.0f, 0.01f);
                    Math_SmoothStepToF(&actor->obj.rot.z, RAND_FLOAT_CENTERED(15.0f), 0.1f, 10.0f, 0.01f);

                    if (actor->fwork[2] < 1.0f) {
                        actor->fwork[2] += 0.02;
                    }
                }
            }
            if ((func_enmy_8006351C(actor->index, &actor->obj.pos, &sp3C, 1) != 0) ||
                (actor->obj.pos.y < (gGroundLevel + 200.0f))) {
                AUDIO_PLAY_SFX(0x19032064, actor->sfxSource, 4);
                D_80137E84[gMainController] = 1;
                D_Timer_80177BD0[gMainController] = 5;
                actor->vel.x = 0.0f;
                actor->vel.y = 0.0f;
                actor->vel.z = 0.0f;
                if (actor->obj.pos.y < gGroundLevel + 200.0f) {
                    actor->obj.pos.y = gGroundLevel + 200.0f;
                }
                actor->state = 1;
            }
            if (actor->obj.pos.y < (gGroundLevel + 800.0f)) {
                if (actor->iwork[0] > 10) {
                    actor->iwork[0] -= 10;
                } else if (actor->iwork[0] > 0) {
                    actor->iwork[0] -= 1;
                }
            }
            break;
        case 1:
            if (actor->iwork[0] > 10) {
                actor->iwork[0] -= 10;
            } else if (actor->iwork[0] > 0) {
                actor->iwork[0] -= 1;
            }
            if (actor->unk_0D0 != 0) {
                actor->unk_0D0 = 0;
                actor->iwork[7] = 15;
                actor->health -= actor->damage;

                if (actor->health <= 0) {
                    func_effect_8007A6F0(&actor->obj.pos, 0x2903A008);
                    func_effect_8007D2C8(actor->obj.pos.x + RAND_FLOAT_CENTERED(20.0f), actor->obj.pos.y - 200.0f,
                                         actor->obj.pos.z, 8.0f);
                    func_effect_8007D2C8(actor->obj.pos.x + RAND_FLOAT_CENTERED(20.0f), actor->obj.pos.y,
                                         actor->obj.pos.z, 8.0f);
                    func_effect_8007D2C8(actor->obj.pos.x + RAND_FLOAT_CENTERED(20.0f), actor->obj.pos.y + 200.0f,
                                         actor->obj.pos.z, 7.0f);
                    func_effect_8007D2C8(actor->obj.pos.x + RAND_FLOAT_CENTERED(20.0f), actor->obj.pos.y + 400.0f,
                                         actor->obj.pos.z, 7.0f);
                    Object_Kill(&actor->obj, actor->sfxSource);
                } else {
                    AUDIO_PLAY_SFX(0x2903300E, actor->sfxSource, 4);
                }
            }
            break;
    }
    actor->unk_0D0 = 0;
}

static Vec3f D_i5_801BA784[8] = {
    { 40.0f, 10.0f, 30.0f },  { 41.0f, 10.0f, 10.0f },  { 43.0f, 10.0f, -10.0f },  { 45.0f, 10.0f, -30.0f },
    { -40.0f, 10.0f, 30.0f }, { -41.0f, 10.0f, 10.0f }, { -43.0f, 10.0f, -10.0f }, { -45.0f, 10.0f, -30.0f },
}; // unused?

void Macbeth_801AE2C0(Actor* actor) {
    if (actor->state < 2) {
        Graphics_SetScaleMtx(actor->scale);
        if (actor->iwork[0] >= 128) {
            RCP_SetupDL(&gMasterDisp, 0x43);
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, actor->iwork[0]);
            gDPSetEnvColor(gMasterDisp++, 255, 48, 0, actor->iwork[0]);
            Matrix_Scale(gGfxMatrix, 1.0f, actor->fwork[2], 1.0f, 1);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_MA_6013060);
            RCP_SetupDL(&gMasterDisp, 0x43);
            Matrix_Scale(gGfxMatrix, 1.0f, actor->fwork[2], 1.0f, 1);
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 53, 53, 53, 255 - actor->iwork[0]);
            gDPSetEnvColor(gMasterDisp++, 0, 0, 0, actor->iwork[0]);
        } else {
            RCP_SetupDL(&gMasterDisp, 0x17);
            if ((actor->iwork[7] % 2) != 0) {
                RCP_SetupDL_27();
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
            }
            if (actor->iwork[7] > 0) {
                actor->iwork[7]--;
            }
        }
        gSPDisplayList(gMasterDisp++, D_MA_600D480);
    }
}

void Macbeth_801AE4CC(Actor* actor, f32 xPos, f32 yPos, f32 zPos, f32 arg4, f32 yVel, f32 arg6, s16 arg7) {
    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_221;
    actor->obj.pos.x = xPos;
    actor->obj.pos.y = yPos;
    actor->obj.pos.z = zPos;
    actor->vel.y = yVel;
    actor->iwork[0] = 255;
    actor->fwork[1] = arg6;
    actor->fwork[2] = 0.2f;
    actor->timer_0BC = 0;
    actor->iwork[1] = D_i5_801BE320[24]++;
    actor->iwork[2] = arg7;
    if (D_i5_801BA570[actor->iwork[2]][actor->iwork[1]] < 0.0f) {
        actor->obj.rot.z = -180.0f;
    } else {
        actor->obj.rot.z = 180.0f;
    }
    actor->health = 30;
    Object_SetInfo(&actor->info, actor->obj.id);
    AUDIO_PLAY_SFX(0x2900201D, actor->sfxSource, 4);
}

void Macbeth_801AE610(f32 xPos, f32 yPos, f32 zPos, f32 arg3, f32 yVel, f32 arg5, s16 arg6) {
    s32 i;

    for (i = ARRAY_COUNT(gActors) - 1; i >= 0; i--) {
        if (gActors[i].obj.status == OBJ_FREE) {
            Macbeth_801AE4CC(&gActors[i], xPos, yPos, zPos, arg3, yVel, arg5, arg6);
            break;
        }
    }
}

void Macbeth_801AE694(Effect* effect, f32 xPos, f32 yPos, f32 zPos, f32 arg4, f32 arg5, f32 arg6) {
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    Vec3f sp38;
    Vec3f sp2C;

    Effect_Initialize(effect);
    effect->obj.status = OBJ_ACTIVE;
    effect->obj.id = OBJ_EFFECT_379;
    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;
    effect->scale2 = D_i5_801BE368[23];
    effect->unk_46 = xPos - arg4;
    effect->unk_48 = yPos - arg5;
    effect->unk_4A = zPos - arg6;
    sp48 = Math_Atan2F(arg4 - xPos, arg6 - zPos);
    sp44 = sqrtf(SQ(arg4 - xPos) + SQ(arg6 - zPos));
    sp4C = -Math_Atan2F(arg5 - yPos, sp44);
    Matrix_RotateY(gCalcMatrix, sp48, 0);
    Matrix_RotateX(gCalcMatrix, sp4C, 1);
    sp38.x = 0.0f;
    sp38.y = 0.0f;
    sp38.z = 30.0f;
    Matrix_MultVec3f(gCalcMatrix, &sp38, &sp2C);

    effect->unk_60.x = sp2C.x;
    effect->unk_60.y = sp2C.y;
    effect->unk_60.z = sp2C.z;
    Object_SetInfo(&effect->info, effect->obj.id);
}

void Macbeth_801AE800(f32 xPos, f32 yPos, f32 zPos, f32 arg3, f32 arg4, f32 arg5) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Macbeth_801AE694(&gEffects[i], xPos, yPos, zPos, arg3, arg4, arg5);
            break;
        }
    }
}

void Macbeth_801AE87C(Effect* effect) {
    f32 sp34;
    f32 sp30;
    f32 sp2C;

    effect->vel.x = effect->unk_60.x * effect->scale1;
    effect->vel.y = effect->unk_60.y * effect->scale1;
    effect->vel.z = effect->unk_60.z * effect->scale1;
    effect->unk_46 += (s16) effect->vel.x;
    effect->unk_48 += (s16) effect->vel.y;
    effect->unk_4A += (s16) effect->vel.z;

    if (effect->scale2 == 3.0f) {
        sp34 = D_i5_801BE368[24];
        sp30 = D_i5_801BE368[25];
        sp2C = D_i5_801BE368[26];
    } else if (effect->scale2 == 4.0f) {
        sp34 = D_i5_801BE368[27];
        sp30 = D_i5_801BE368[28];
        sp2C = D_i5_801BE368[29];
    } else if (effect->scale2 == 1.0f) {
        sp34 = D_i5_801BE368[24];
        sp30 = D_i5_801BE368[25];
        sp2C = D_i5_801BE368[26];
    } else {
        sp34 = D_i5_801BE368[27];
        sp30 = D_i5_801BE368[28];
        sp2C = D_i5_801BE368[29];
    }

    effect->obj.pos.x = effect->unk_46 + sp34;
    effect->obj.pos.y = effect->unk_48 + sp30;
    effect->obj.pos.z = effect->unk_4A + sp2C;
    Math_SmoothStepToF(&effect->scale1, 1.0f, 1.0f, 0.1f, 0.0f);
    if (effect->unk_44 < 240) {
        effect->unk_44 += 15;
    } else {
        Object_Kill(&effect->obj, effect->sfxSource);
    }
    if ((fabsf(effect->obj.pos.x - sp34) <= 30.0f) && (fabsf(effect->obj.pos.z - sp2C) <= 30.0f)) {
        Object_Kill(&effect->obj, effect->sfxSource);
    }
}

void Macbeth_801AEAA0(Effect* effect) {
    RCP_SetupDL(&gMasterDisp, 0x43);
    if (effect->scale2 >= 3.0f) {
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, effect->unk_44);
        gDPSetEnvColor(gMasterDisp++, 255, 0, 0, effect->unk_44);
    } else {
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, effect->unk_44);
        gDPSetEnvColor(gMasterDisp++, 0, 128, 255, effect->unk_44);
    }
    Matrix_Scale(gGfxMatrix, 0.5f, 0.5f, 0.5f, 1);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_1024AC0);
    RCP_SetupDL(&gMasterDisp, 0x40);
}

void Macbeth_801AEC04(Actor* actor) {
    if ((gPlayer[0].unk_138 - actor->obj.pos.z) < -300.0f) {
        Object_Kill(&actor->obj, actor->sfxSource);
    }

    switch (actor->state) {
        case 0:
            actor->vel.y -= 0.5f;
            if (actor->obj.pos.y < (gGroundLevel + 35.0f)) {
                actor->vel.x = 0.0f;
                actor->vel.y = 0.0f;
                actor->vel.z = 0.0f;
                if (actor->obj.pos.y < gGroundLevel + 35.0f) {
                    actor->obj.pos.y = gGroundLevel + 35.0f;
                }
                actor->state = 1;
                actor->timer_0BC = 200;
                AUDIO_PLAY_SFX(0x11000028, actor->sfxSource, 4);
            }
            break;
        case 1:

            if (actor->fwork[0] < 10.0f) {
                actor->fwork[0] += 1.0f;
            }

            if (actor->fwork[2] < 3.0f) {
                actor->fwork[2] += 0.1f;
            }

            if (((gGameFrameCount % 16) == 0)) {
                func_effect_8007C120(actor->obj.pos.x - 35.0f, actor->obj.pos.y + 15.0f, actor->obj.pos.z, -3.0f, 0.0f,
                                     0.0f, 0.1f, 20);
                func_effect_8007C120(actor->obj.pos.x + 35.0f, actor->obj.pos.y + 15.0f, actor->obj.pos.z, 3.0f, 0.0f,
                                     0.0f, 0.1f, 20);
            }
            break;
        default:
            break;
    }
    if ((gGameFrameCount % 2) != 0) {
        actor->fwork[1] = 255.0f;
    } else {
        actor->fwork[1] = 32.0f;
    }
    if ((actor->unk_0D0 != 0) && (actor->unk_0D2 == 0)) {
        AUDIO_PLAY_SFX(0x2903300E, actor->sfxSource, 4);
        actor->unk_0D0 = 0;
        actor->health -= actor->damage;
        actor->timer_0C6 = 15;
        if (actor->health <= 0) {
            func_effect_8007A6F0(&actor->obj.pos, 0x29000000);
            func_effect_8007D2C8(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, 8.0f);
            Object_Kill(&actor->obj, actor->sfxSource);
        }
    }
}

void Macbeth_801AEEFC(Actor* actor) {
    gSPDisplayList(gMasterDisp++, D_MA_6015510);
    Matrix_Scale(gGfxMatrix, actor->fwork[0], actor->fwork[2], 1.0f, 1);
    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, 0.0f, -10.0f, 0.0f, 1);
    RCP_SetupDL(&gMasterDisp, 0x43);
    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 111, 175, 64, actor->fwork[1]);
    gDPSetEnvColor(gMasterDisp++, 255, 255, 208, actor->fwork[1]);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_MA_6012F50);
    Matrix_Pop(&gGfxMatrix);
}

void Macbeth_801AF134(Actor* actor, f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel) {
    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_222;
    actor->obj.pos.x = xPos;
    actor->obj.pos.y = yPos;
    actor->obj.pos.z = zPos;
    actor->vel.x = xVel;
    actor->vel.y = yVel;
    actor->vel.z = zVel;
    actor->timer_0BC = 0;
    actor->health = 30;
    actor->fwork[0] = 1.0f;
    actor->fwork[2] = 1.0f;
    Object_SetInfo(&actor->info, actor->obj.id);
    AUDIO_PLAY_SFX(0x2900201D, actor->sfxSource, 4);
}

void Macbeth_801AF200(f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel) {
    s32 i;

    for (i = ARRAY_COUNT(gActors) - 1; i >= 0; i--) {
        if (gActors[i].obj.status == OBJ_FREE) {
            Macbeth_801AF134(&gActors[i], xPos, yPos, zPos, xVel, yVel, zVel);
            break;
        }
    }
}

static f32 D_i5_801BA7E4[5] = { 0.0f, 0.0f, 1180.0f, 200.0f, 1000.0f };

static f32 D_i5_801BA7F8[5] = { 600.0f, 200.0f, 400.0f, 2000.0f, 1200.0f };

static f32 D_i5_801BA80C[5] = { 500.0f, 600.0f, 200.0f, 4500.0f, 2300.0f };

static f32 D_i5_801BA820[5] = { 90.0f, -90.0f, 25.0f, 0.0f, 225.0f };

void Macbeth_801AF27C(Actor* actor, s32 arg1) {
    Player* player = &gPlayer[0];

    Actor_Initialize(actor);
    actor->obj.pos.x = D_i5_801BA7E4[arg1] + player->pos.x;
    actor->obj.pos.y = D_i5_801BA7F8[arg1] + player->pos.y;
    actor->obj.pos.z = D_i5_801BA80C[arg1] + player->pos.z;
    actor->fwork[7] = RAND_FLOAT(360.0f);
    actor->fwork[8] = RAND_FLOAT(360.0f);
    actor->vel.x = player->vel.x;
    actor->vel.y = player->vel.y;
    actor->vel.z = player->vel.z;
    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_195;
    actor->obj.rot.y = 180.0f;
    Object_SetInfo(&actor->info, actor->obj.id);
    if (arg1 < 3) {
        actor->iwork[11] = 1;
        actor->unk_0C9 = 1;
        actor->fwork[3] = D_i5_801BA820[arg1];
        actor->state = 30;
        AUDIO_PLAY_SFX(0x3100000C, actor->sfxSource, 4);
    } else {
        actor->unk_0B6 = 1;
        actor->state = 21;
        actor->obj.rot.z = 32.5f;
        AUDIO_PLAY_SFX(0x11030010, actor->sfxSource, 0);
        actor->fwork[9] = 20.0f;
    }
}

void Macbeth_801AF44C(void) {
    Actor* actor = &gActors[8];

    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_195;
    actor->obj.pos.x = gPlayer[0].pos.x + D_i5_801BA7E4[4];
    actor->obj.pos.y = gPlayer[0].pos.y + D_i5_801BA7F8[4];
    actor->obj.pos.z = gPlayer[0].pos.z + D_i5_801BA80C[4];
    actor->vel.x = gPlayer[0].vel.x;
    actor->vel.y = gPlayer[0].vel.y;
    actor->vel.z = gPlayer[0].vel.z;
    actor->fwork[7] = RAND_FLOAT(360.0f);
    actor->fwork[8] = RAND_FLOAT(360.0f);
    actor->fwork[9] = 30.0f;
    actor->unk_0F4.y = D_i5_801BA820[4];
    actor->unk_0F4.x = 0.0f;
    actor->unk_0F4.z = 330.0f;
    actor->obj.rot.x = -0.0f;
    actor->obj.rot.y = actor->unk_0F4.y;
    actor->obj.rot.z = -330.0f;
    actor->fwork[0] = 0.0f;
    actor->unk_0B6 = 24;
    actor->iwork[11] = 1;
    actor->state = 15;
    actor->fwork[3] = D_i5_801BA820[4];
    Object_SetInfo(&actor->info, actor->obj.id);
    AUDIO_PLAY_SFX(0x3100000C, actor->sfxSource, 4);
}

static Vec3f D_i5_801BA834[2] = {
    { 2000.0f, 300.0f, 500.0f },
    { 2500.0f, 300.0f, -3300.0f },
};

static f32 D_i5_801BA84C[2] = { 0.0f, 60.0f };

void Macbeth_801AF628(Actor* actor, s32 arg1) {
    Actor_Initialize(actor);
    actor->obj.status = OBJ_ACTIVE;
    actor->obj.id = OBJ_ACTOR_195;
    actor->obj.pos.x = gPlayer[0].unk_0AC + D_i5_801BA834[arg1].x;
    actor->obj.pos.y = D_i5_801BA834[arg1].y;
    actor->obj.pos.z = D_i5_801BA834[arg1].z - D_ctx_80177D20;
    actor->unk_0B6 = 37;
    actor->obj.rot.y = D_i5_801BA84C[arg1];
    actor->iwork[4] = actor->iwork[5] = 192;
    actor->iwork[0] = actor->iwork[1] = actor->iwork[2] = actor->iwork[7] = actor->iwork[3] = 255;
    actor->iwork[6] = 128;
    Object_SetInfo(&actor->info, actor->obj.id);
}

void Macbeth_801AF70C(f32 xPos, f32 yPos, f32 zPos, f32 arg3) {
    Effect* effect;
    Effect* effectPtr;
    f32 temp_ft1;
    s32 i;

    effect = NULL;
    effectPtr = &gEffects[0];
    for (i = 0; i < 99; i++, effectPtr++) {
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

static f32 D_i5_801BA854[4] = { 1.5f, -1.0f, 0.7f, 0.0f };

static f32 D_i5_801BA864 = 0.9f;
static f32 D_i5_801BA868 = 0.7f; // unused?
static f32 D_i5_801BA86C = -1.0f;
static f32 D_i5_801BA870 = 1.5f; // unused?
static f32 D_i5_801BA874[4] = { 200.0f, 300.0f, 400.0f, 0.0f };
static f32 D_i5_801BA884 = 500.0f;
static f32 D_i5_801BA888 = 100.0f;
static f32 D_i5_801BA88C = 120.0f;
static f32 D_i5_801BA890 = 100.0f; // unused?
static f32 D_i5_801BA894[5] = { 200.0f, 250.0f, 220.0f, 0.0f, 200.0f };
static f32 D_i5_801BA8A8[3] = { 230.0f, 220.0f, 350.0f }; // unused?

void Macbeth_801AF8F4(Player* player) {
    s32 i;
    s32 j;
    Vec3f spE4;
    Vec3f spD8;
    f32 zeroVar = 0.0f;

    switch (player->unk_1D0) {
        case 0:
            gCsFrameCount = 0;
            D_ctx_80178488 = 1;
            player->unk_234 = 0;
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 30);
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 30);
            player->unk_1D0 = 1;
            D_ctx_80177A48[0] = 0.0f;
            D_ctx_80177A48[4] = -60.0f;
            D_ctx_80177A48[5] = 240.0f;
            player->unk_0D4 = 3.0f;
            gCameraShakeY = player->vel.x = player->vel.y = player->vel.z = player->unk_0D0 = 0.0f;
            if (player->shields <= 0) {
                player->shields = 1;
            }
            player->camEye.x = gCsCamEyeX = gActors[D_i5_801BE318].obj.pos.x - 250.0f;
            player->camEye.y = gCsCamEyeY = gActors[D_i5_801BE318].obj.pos.y + 150.0f;
            player->camEye.z = gCsCamEyeZ = gActors[D_i5_801BE318].obj.pos.z + D_ctx_80177D20 + 500.0f;
            player->camAt.x = gCsCamAtX = gActors[D_i5_801BE318].obj.pos.x;
            player->camAt.y = gCsCamAtY = gActors[D_i5_801BE318].obj.pos.y + 200.0f;
            player->camAt.z = gCsCamAtZ = gActors[D_i5_801BE318].obj.pos.z + D_ctx_80177D20;
            player->pos.x = 500.0f;
            player->pos.y = -3.0f;
            D_i5_801BA1DC = 0.0f;
            player->unk_4D8 = 0.0f;
            player->unk_034 = 0.0f;
            player->unk_110 = 0.0f;
            player->wings.unk_0C = player->wings.unk_08 = player->wings.unk_10 = player->unk_130 = player->unk_12C =
                0.0f;
            player->unk_080 = 0.0f;
            player->unk_0F0 = 0.0f;
            player->unk_16C = 0.0f;
            player->unk_170 = 0.0f;
            player->wings.unk_04 = 0.0f;
            /* fallthrough */
        case 1:
            gShowBossHealth = 0;
            if (gCsFrameCount == 70) {
                D_ctx_80177DC8 = 498;

                for (i = 0; i < ARRAY_COUNT(gActors); i++) {
                    if (gActors[i].obj.id == OBJ_ACTOR_223) {
                        gActors[i].state++;
                        break;
                    }
                }

                player->unk_1D0++;
                gCsCamEyeX = -100.0f;
                gCsCamEyeY = 250.0f;
                gCsCamEyeZ = 2090.0f;
                gCsCamAtX = -250.0f;
                gCsCamAtY = 10.0f;
                gCsCamAtZ = -3210.0f;
                player->camEye.x = -250.0f;
                player->camEye.y = 50.0f;
                player->camEye.z = 1580.0f;
                player->camAt.x = -250.0f;
                player->camAt.y = 10.0f;
                player->camAt.z = -3210.0f;
                D_i5_801BE312 = 1;
                player->pos.x = 500.0f;
                player->pos.y = -3.0f;
                player->pos.z = player->unk_138 = -111130.0f;
                player->unk_144 = D_ctx_80177D20 = 115930.0f;
                player->flags_228 = PFLAG_228_4;
                gLastPathChange = OBJ_ITEM_PATH_TURN_RIGHT;
                D_i5_801BA1DC = 0.0f;
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
                D_i5_801BA1DC = -40.0f;
                player->unk_1D0++;
            }
            /* fallthrough */
        case 3:
            player->vel.z = gActors[D_i5_801BE314].vel.z;
            if (gCsFrameCount == 252) {
                gCsCamEyeY = 570.0f;
                player->timer_210 = 1000;
                player->unk_0B8 = 20000.0f;
                player->unk_118 = -23.0f;
                player->unk_0B4 = 0.0f;
            }
            if (gCsFrameCount >= 252) {
                player->pos.x = gActors[D_i5_801BE314].obj.pos.x + 500.0f;
                player->unk_140 = -gActors[D_i5_801BE314].vel.z;
                player->unk_144 += player->unk_140;
                D_ctx_80177D08 = player->unk_140;
                D_ctx_80177D20 = player->unk_144;
                D_ctx_80177CE8 += player->unk_140;
                player->pos.z = player->unk_138 = -(D_ctx_80177D20 + 210.0f);
                Math_SmoothStepToF(&D_ctx_80177A48[0], 1.0f, 0.1f, 0.00025f, 0.0f);
                gCsCamAtX = gActors[D_i5_801BE314].obj.pos.x + 2500.0f;
                gCsCamAtZ = (gActors[D_i5_801BE314].obj.pos.z + D_ctx_80177D20) - 2000.0f;
                gCsCamEyeX = gCsCamAtX - 2340.0f;
                gCsCamEyeZ = gCsCamAtZ + 1410.0f;
            }
            if (gCsFrameCount == 389) {
                player->unk_1D0++;
                player->vel.z = 0.0f;
                player->unk_140 = 0.0f;
                D_ctx_801779E4 = 0.0f;
                D_ctx_801779F4 = 0.0f;
                player->timer_210 = 0;
                player->camEye.x = gCsCamEyeX = 2750.0f;
                player->camEye.y = gCsCamEyeY = 50.0f;
                player->camEye.z = gCsCamEyeZ = -620.0f;
                player->camAt.x = gCsCamAtX = -650.0f;
                player->camAt.y = gCsCamAtY = 30.0f;
                player->camAt.z = gCsCamAtZ = 1900.0f;
                player->unk_114 = 0.0f;
                D_i5_801BA1DC = -100.0f;
                Audio_KillSfxById(0x31078085);
                AUDIO_PLAY_SFX(0x31408095, gActors[D_i5_801BE314].sfxSource, 4);
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
                player->unk_1D0++;
                D_ctx_80177A48[0] = 1.0f;
                player->unk_114 = 30.0f;
                player->unk_0AC = 4600.0f;
                D_i5_801BA1DC = -80.0f;
                player->unk_144 = D_ctx_80177D20 += 300.0f;
                D_ctx_80177A48[5] = 0.0f;
                D_ctx_80177A48[6] = 0.5f;
                D_ctx_80177A48[7] = 1560.0f;
                D_ctx_80177A48[8] = 2400.0f;
                player->camAt.x = gCsCamAtX = gActors[D_i5_801BE314].obj.pos.x;
                player->camAt.z = gCsCamAtZ = (gActors[D_i5_801BE314].obj.pos.z + D_ctx_80177D20) - 2000.0f;
                player->camEye.y = gCsCamEyeY = 50.0f;
                player->camAt.y = gCsCamAtY = 10.0f;
                player->camEye.x = gCsCamEyeX = D_ctx_80177A48[7] + gCsCamAtX;
                player->camEye.z = gCsCamEyeZ = D_ctx_80177A48[8] + gCsCamAtZ;
                player->unk_118 = -30.0f;
                player->unk_0B8 = 10014.0f;
                player->timer_210 = 1000;
                player->unk_0B4 = 0.0f;
                gFillScreenAlphaTarget = 0;
                gFillScreenAlphaStep = 127;
            }
            break;
        case 5:
            if (gCsFrameCount <= 625) {
                Math_SmoothStepToF(&D_i5_801BA1DC, 0.0f, 0.1f, 0.05f, 0.0f);
            }
            if (gCsFrameCount >= 430) {
                Math_SmoothStepToF(&D_ctx_80177A48[6], 22.0f, 0.1f, 1.0f, 0.0f);
                Math_SmoothStepToF(&D_ctx_80177A48[7], 2600.0f, 0.1f, D_ctx_80177A48[6], 0.0f);
                Math_SmoothStepToF(&D_ctx_80177A48[8], 3800.0f, 0.1f, D_ctx_80177A48[6], 0.0f);
                Math_SmoothStepToF(&gCsCamEyeY, 1300.0f, 0.1f, 17.0f, 0.0f);
            }
            if (gCsFrameCount <= 505) {
                gCsCamAtZ = gActors[D_i5_801BE314].obj.pos.z + D_ctx_80177D20 - 2000.0f;
                gCsCamAtX = gActors[D_i5_801BE314].obj.pos.x;
                player->vel.z = gActors[D_i5_801BE314].vel.z;
                player->pos.x = gActors[D_i5_801BE314].obj.pos.x + 500.0f;
                player->pos.z = player->unk_138 = -(D_ctx_80177D20 + 210.0f);
                player->unk_140 = -gActors[D_i5_801BE314].vel.z;
                gCsCamEyeX = D_ctx_80177A48[7] + gCsCamAtX;
                gCsCamEyeZ = D_ctx_80177A48[8] + gCsCamAtZ;
                func_effect_8007C120(gActors[D_i5_801BE314].obj.pos.x + 480.0f,
                                     gActors[D_i5_801BE314].obj.pos.y + 15.0f,
                                     gActors[D_i5_801BE314].obj.pos.z - 400.0f, gActors[D_i5_801BE314].vel.x,
                                     gActors[D_i5_801BE314].vel.y, 0.0f, 0.2f, 10);
            } else {
                player->vel.z = 0.0f;
                if (((gGameFrameCount % 16) == 0)) {
                    gFogRed -= 1;
                    gFogGreen -= 1;
                    gFogBlue -= 2;
                }
                Math_SmoothStepToF(&player->unk_140, 0.0f, 1.0f, 0.6f, 0.0f);
                Math_SmoothStepToF(&gCsCamAtX, 11700.0f, 0.1f, 50.0f, 0.0f);
                Math_SmoothStepToF(&D_ctx_80177A48[5], 30.0f, 0.1f, 0.05f, 0.0f);
                Math_SmoothStepToF(&gCsCamAtY, 1600.0f, 0.1f, D_ctx_80177A48[5], 0.0f);
                if (player->unk_140 >= 2.5f) {
                    player->pos.x = gActors[D_i5_801BE314].obj.pos.x + 500.0f;
                    player->pos.z = player->unk_138 = -(D_ctx_80177D20 + 210.0f);
                } else {
                    player->unk_0B8 = player->unk_0AC;
                    D_ctx_801779E4 = 0.0f;
                }

                func_effect_8007BC7C(gActors[D_i5_801BE314].obj.pos.x + 190.0f,
                                     gActors[D_i5_801BE314].obj.pos.y + 30.0f,
                                     gActors[D_i5_801BE314].obj.pos.z - 100.0f, 6.0f);
                func_effect_8007BC7C(gActors[D_i5_801BE314].obj.pos.x + 190.0f,
                                     gActors[D_i5_801BE314].obj.pos.y + 30.0f,
                                     gActors[D_i5_801BE314].obj.pos.z - 120.0f, 6.0f);
                func_effect_8007BC7C(gActors[D_i5_801BE314].obj.pos.x - 190.0f,
                                     gActors[D_i5_801BE314].obj.pos.y + 30.0f,
                                     gActors[D_i5_801BE314].obj.pos.z - 100.0f, 6.0f);
                func_effect_8007BC7C(gActors[D_i5_801BE314].obj.pos.x - 190.0f,
                                     gActors[D_i5_801BE314].obj.pos.y + 30.0f,
                                     gActors[D_i5_801BE314].obj.pos.z - 120.0f, 6.0f);
            }
            player->unk_144 += player->unk_140;
            D_ctx_80177D08 = player->unk_140;
            D_ctx_80177D20 = player->unk_144;
            D_ctx_80177CE8 += player->unk_140;
            if (gCsFrameCount == 630) {
                Audio_KillSfxBySourceAndId(gActors[D_i5_801BE314].sfxSource, 0x31408095);
                AUDIO_PLAY_SFX(0x2940C00A, gActors[D_i5_801BE314].sfxSource, 4);
                player->unk_1D0++;
                player->vel.z = 0.0f;
                player->unk_140 = 0.0f;
                D_ctx_80177D08 = 0.0f;
                D_ctx_801779E4 = 0.0f;
                D_ctx_801779F4 = 0.0f;
                player->timer_210 = 10000;
                D_ctx_80177A48[0] = 1.0f;
                D_i5_801BA1DC = 0.0f;
                D_80137E84[0] = 1;
                D_Timer_80177BD0[0] = 10;
                gCameraShake = 10;
                D_ctx_80177A48[4] = -70.0f;
                D_ctx_80177A48[5] = 280.0f;
            }
            break;
        case 6:
            Math_SmoothStepToF(&D_ctx_80177A48[4], -60.0f, 1.0f, 0.5f, 0.0f);
            Math_SmoothStepToF(&D_ctx_80177A48[5], 240.0f, 1.0f, 2.0f, 0.0f);
            if (((gGameFrameCount % 2) == 0)) {
                func_effect_8007797C(11000.0f, 200.0f, -139000.0f, D_ctx_80177A48[4], 4.0f, D_ctx_80177A48[5], 20.0f);
            }

            if (gCsFrameCount == 710) {
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = gFillScreenAlpha = 255;
                gFillScreenAlphaTarget = 0;
                gFillScreenAlphaStep = 128;
                func_effect_8007D9DC(gActors[D_i5_801BE314].obj.pos.x + 1000.0f,
                                     gActors[D_i5_801BE314].obj.pos.y + 20.0f, -138500.0f, 100.0f, 1000.0f, 0);
                func_effect_8007A568(gActors[D_i5_801BE314].obj.pos.x + 200.0f,
                                     gActors[D_i5_801BE314].obj.pos.y + 700.0f, -137750.0f, 100.0f);
                for (i = 0; i < 8; i++) {
                    func_effect_800794CC(gActors[D_i5_801BE314].obj.pos.x + RAND_FLOAT_CENTERED(1000.0f),
                                         gActors[D_i5_801BE314].obj.pos.y + 1300.0f,
                                         gActors[D_i5_801BE314].obj.pos.z + 700.0f + RAND_FLOAT_CENTERED(1000.0f),
                                         6.0f);
                    Macbeth_801AF70C(RAND_FLOAT_CENTERED(650.0f) + 11250.0f, 300.0f, RAND_FLOAT(650.0f) + -139000.0f,
                                     0.7f);
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
                func_effect_8007A568(gActors[D_i5_801BE314].obj.pos.x - 3000.0f,
                                     gActors[D_i5_801BE314].obj.pos.y + 500.0f,
                                     gActors[D_i5_801BE314].obj.pos.z + 1600.0f, 10000.0f);
                for (i = 0; i < 8; i++) {
                    func_effect_800794CC(gActors[D_i5_801BE314].obj.pos.x - 3000.0f + RAND_FLOAT_CENTERED(1000.0f),
                                         gActors[D_i5_801BE314].obj.pos.y + 700.0f,
                                         gActors[D_i5_801BE314].obj.pos.z + 1600.0f + RAND_FLOAT_CENTERED(1000.0f),
                                         6.0f);
                    Macbeth_801AF70C(RAND_FLOAT_CENTERED(650.0f) + 11250.0f, 300.0f, RAND_FLOAT(650.0f) + -139000.0f,
                                     0.7f);
                }
            }
            if (gCsFrameCount == 820) {
                func_effect_8007A568(gActors[D_i5_801BE314].obj.pos.x, gActors[D_i5_801BE314].obj.pos.y + 500.0f,
                                     gActors[D_i5_801BE314].obj.pos.z + 3300.0f, 14000.0f);
                for (i = 0; i < 8; i++) {
                    func_effect_800794CC(gActors[D_i5_801BE314].obj.pos.x + 500.0f + RAND_FLOAT_CENTERED(1000.0f),
                                         gActors[D_i5_801BE314].obj.pos.y + 900.0f,
                                         gActors[D_i5_801BE314].obj.pos.z + 3300.0f + RAND_FLOAT_CENTERED(1000.0f),
                                         6.0f);
                    Macbeth_801AF70C(RAND_FLOAT_CENTERED(650.0f) + 11250.0f, 300.0f, RAND_FLOAT(650.0f) + -139000.0f,
                                     0.7f);
                }
            }
            if (gCsFrameCount == 835) {
                func_effect_8007A568(gActors[D_i5_801BE314].obj.pos.x - 1500.0f,
                                     gActors[D_i5_801BE314].obj.pos.y + 500.0f,
                                     gActors[D_i5_801BE314].obj.pos.z + 2000.0f, 80.0f);
                for (i = 0; i < 8; i++) {
                    func_effect_800794CC(gActors[D_i5_801BE314].obj.pos.x - 1500.0f + RAND_FLOAT_CENTERED(1000.0f),
                                         gActors[D_i5_801BE314].obj.pos.y + 1200.0f,
                                         gActors[D_i5_801BE314].obj.pos.z + 2000.0f + RAND_FLOAT_CENTERED(1000.0f),
                                         6.0f);
                    Macbeth_801AF70C(RAND_FLOAT_CENTERED(650.0f) + 11250.0f, 300.0f, RAND_FLOAT(650.0f) + -139000.0f,
                                     0.7f);
                }
            }
            if (gCsFrameCount == 845) {
                func_effect_8007A568(gActors[D_i5_801BE314].obj.pos.x - 500.0f,
                                     gActors[D_i5_801BE314].obj.pos.y + 500.0f,
                                     gActors[D_i5_801BE314].obj.pos.z + 2800.0f, 10000.0f);
                for (i = 0; i < 11; i++) {
                    func_effect_800794CC(gActors[D_i5_801BE314].obj.pos.x - 500.0f + RAND_FLOAT_CENTERED(1000.0f),
                                         gActors[D_i5_801BE314].obj.pos.y + 900.0f,
                                         gActors[D_i5_801BE314].obj.pos.z + 2800.0f + RAND_FLOAT_CENTERED(1000.0f),
                                         6.0f);
                    Macbeth_801AF70C(RAND_FLOAT_CENTERED(650.0f) + 11250.0f, 300.0f, RAND_FLOAT(650.0f) + -139000.0f,
                                     0.7f);
                }
            }
            if (gCsFrameCount == 853) {
                func_effect_8007A568(gActors[D_i5_801BE314].obj.pos.x - 3500.0f,
                                     gActors[D_i5_801BE314].obj.pos.y + 500.0f,
                                     gActors[D_i5_801BE314].obj.pos.z + 2500.0f, 14000.0f);
                for (i = 0; i < 8; i++) {
                    func_effect_800794CC(gActors[D_i5_801BE314].obj.pos.x - 3500.0f + RAND_FLOAT_CENTERED(1000.0f),
                                         gActors[D_i5_801BE314].obj.pos.y + 900.0f,
                                         gActors[D_i5_801BE314].obj.pos.z + 1500.0f + RAND_FLOAT_CENTERED(1000.0f),
                                         6.0f);
                    Macbeth_801AF70C(RAND_FLOAT_CENTERED(650.0f) + 11250.0f, 300.0f, RAND_FLOAT(650.0f) + -139000.0f,
                                     0.7f);
                }
                gCameraShake = 30;
            }
            if (gCsFrameCount == 860) {
                func_effect_8007D9DC(gActors[D_i5_801BE314].obj.pos.x + 1000.0f,
                                     gActors[D_i5_801BE314].obj.pos.y + 20.0f, -138500.0f, 100.0f, 1000.0f, 0);
                func_effect_8007A568(gActors[D_i5_801BE314].obj.pos.x - 1500.0f,
                                     gActors[D_i5_801BE314].obj.pos.y + 700.0f,
                                     gActors[D_i5_801BE314].obj.pos.z + 3000.0f, 180.0f);
                for (i = 0; i < 8; i++) {
                    func_effect_800794CC(gActors[D_i5_801BE314].obj.pos.x - 1500.0f + RAND_FLOAT_CENTERED(1000.0f),
                                         gActors[D_i5_801BE314].obj.pos.y + 1300.0f,
                                         gActors[D_i5_801BE314].obj.pos.z + 2500.0f + RAND_FLOAT_CENTERED(1000.0f),
                                         6.0f);
                    Macbeth_801AF70C(RAND_FLOAT_CENTERED(650.0f) + 11250.0f, 300.0f, RAND_FLOAT(650.0f) + -139000.0f,
                                     0.7f);
                }
            }
            if (gCsFrameCount == 880) {
                D_80137E84[0] = 1;
                D_Timer_80177BD0[0] = 10;
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
                gFillScreenAlphaTarget = 255;
                gFillScreenAlphaStep = 20;
                AUDIO_PLAY_SFX(0x2940F026, gActors[D_i5_801BE314].sfxSource, 4);
                gBossActive = D_ctx_80178488 = 0;
            }
            if (gCsFrameCount == 940) {
                player->unk_1D0++;
                func_play_800A6148();
                player->pos.z = player->unk_138 = -(D_ctx_80177D20 + 210.0f);
                player->pos.x = player->unk_0AC;
                func_effect_8007A568(player->pos.x - 1800.0f, -50.0f, player->pos.z + 5000.0f, 40.0f);
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = gFillScreenAlpha = 255;
                gFillScreenAlphaTarget = 0;
                gFillScreenAlphaStep = 8;
                D_ctx_80177A48[0] = 0.0f;
                player->unk_234 = 1;
                player->camAt.x = gCsCamAtX = player->camEye.x = gCsCamEyeX = player->pos.x;
                player->camAt.y = gCsCamAtY = player->pos.y + 70.0f;
                player->camEye.y = gCsCamEyeY = player->pos.y + 30.0f;
                player->camEye.z = gCsCamEyeZ = (player->unk_138 + D_ctx_80177D20) - 300.0f;
                player->camAt.z = gCsCamAtZ = player->unk_138 + D_ctx_80177D20;
                player->savedCockpitView = player->timer_210 = 0;
                player->unk_190 = player->unk_194 = player->unk_188 = player->unk_18C = player->unk_118 =
                    player->unk_114 = player->unk_4D8 = player->unk_034 = player->unk_174 = player->unk_178 =
                        player->unk_17C = player->unk_180 = player->unk_184 = player->wings.unk_04 = player->unk_170 =
                            player->unk_16C = player->unk_0F0 = player->unk_080 = player->wings.unk_0C =
                                player->wings.unk_08 = player->wings.unk_10 = player->unk_130 = player->unk_12C =
                                    player->unk_110 = 0.0f;
                player->unk_0D0 = 5.0f;
                D_ctx_80177A48[3] = D_ctx_80177A48[6] = D_ctx_80177A48[7] = D_ctx_80177A48[8] = 0.0f;
                player->unk_1D4 = 1;
                player->unk_1F4 = 0;
                player->pos.y = gGroundLevel - 3.0f;
                player->vel.y = -3.0f;
                player->unk_1DC = player->unk_2B4 = player->unk_2BC = player->unk_184 = player->unk_108 =
                    player->unk_10C = player->unk_0E8 = player->unk_0E4 = player->unk_104 = 0.0f;
                player->timer_1E0 = player->sfx.bank = 0;
            }
            break;
        case 7:
            if (((gGameFrameCount % 4) == 0)) {
                func_effect_8007D0E0(player->pos.x - 1750.0f + RAND_FLOAT_CENTERED(700.0f), 10.0f,
                                     player->pos.z + 5000.0f + RAND_FLOAT_CENTERED(700.0f), 5.0f);
                func_effect_8007C85C(player->pos.x - 1800.0f + RAND_FLOAT_CENTERED(40.0f), -100.0f,
                                     player->pos.z + 5000.0f + RAND_FLOAT_CENTERED(40.0f), 9.0f);
            }

            if ((gCsFrameCount >= 1059) && (gCsFrameCount < 2120)) {
                Math_SmoothStepToF(&D_ctx_80177A48[0], 1.0f, 1.0f, 0.005f, 0.0f);
                Math_SmoothStepToF(&D_ctx_80177A48[3], 1080.0f, 0.1f, D_ctx_80177A48[0] * 1.2f, 0.0f);
                Matrix_RotateY(gCalcMatrix, -D_ctx_80177A48[3] * M_DTOR, 0);
                spE4.x = 0.0f;
                spE4.y = 0.0f;
                spE4.z = -300.0f;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &spE4, &spD8);
                gCsCamEyeX = player->pos.x + spD8.x;
                gCsCamEyeZ = player->pos.z + D_ctx_80177D20 + spD8.z;
            }
            if (gCsFrameCount >= 2120) {
                Math_SmoothStepToF(&D_ctx_80177A48[0], 1.0f, 1.0f, 0.001f, 0.0f);
                Math_SmoothStepToF(&D_ctx_80177A48[8], 20.0f, 0.1f, 0.1f, 0.0f);
                Math_SmoothStepToF(&gCsCamEyeX, player->pos.x - 2000.0f, 0.1f, D_ctx_80177A48[8], 0.0f);
                gCsCamEyeZ -= 1.0f;
            }
            if ((gCsFrameCount >= 2120) || (gCsFrameCount < 2175)) {
                Math_SmoothStepToF(&gCsCamAtY, player->pos.y + 70.0f, 0.1f, 8.0f, 0.0f);
            }
            if (gCsFrameCount == 2120) {
                D_ctx_80177A48[0] = 0.0f;
            }
            if (gCsFrameCount >= 2160) {
                player->vel.y = 4.0f;
                Math_SmoothStepToF(&player->unk_170, 2.0f, 1.0f, 0.3f, 0.0f);
                Math_SmoothStepToF(&player->unk_16C, 2.0f, 1.0f, 0.3f, 0.0f);
                if ((gCsFrameCount >= 2165) && (gCsFrameCount <= 2180)) {
                    func_effect_8007BC7C(player->pos.x + RAND_FLOAT_CENTERED(30.0f), 0.0f,
                                         RAND_FLOAT_CENTERED(30.0f) + player->unk_138, RAND_FLOAT(2.0f) + 3.5f);
                    func_effect_8007BC7C(player->pos.x - RAND_FLOAT_CENTERED(30.0f), 0.0f,
                                         RAND_FLOAT_CENTERED(30.0f) + player->unk_138, RAND_FLOAT(2.0f) + 3.5f);
                }
                Math_SmoothStepToF(&D_ctx_80177A48[7], 4.5f, 0.1f, 0.3f, 0.0f);
                player->unk_138 = player->pos.z;
            }
            func_tank_80045130(player);
            func_tank_80044868(player);
            func_tank_800444BC(player);
            func_play_800ADF58(player);
            if (gCsFrameCount >= 2175) {
                Math_SmoothStepToF(&gCsCamAtZ, gActors[3].obj.pos.z + D_ctx_80177D20 - 300.0f, 0.1f, 20.0f, 0.0f);
                Math_SmoothStepToF(&gCsCamAtY, gActors[3].obj.pos.y + 100.0f, 0.1f, 10.0f, 0.0f);
            } else {
                player->camAt.z = gCsCamAtZ = player->unk_138 + D_ctx_80177D20;
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
            AUDIO_PLAY_BGM(SEQ_ID_GOOD_END);
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
            D_i5_801BA888 = 220.0f;
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
            if (D_play_800D3180[LEVEL_ZONESS] != 0) {
                Macbeth_801AF44C();
            }
            break;
        case 1460:
            D_i5_801BA88C = 170.0f;
            break;
        case 1500:
            if (D_play_800D3180[LEVEL_ZONESS] != 0) {
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
            D_i5_801BA86C = -0.5f;
            break;
        case 1810:
            Object_Kill(&gActors[8].obj, gActors[8].sfxSource);
            gOverlayStage = 1;
            break;
        case 1817:
            D_ctx_80177830 = 1;
            break;
        case 1960:
            Macbeth_801AF27C(&gActors[3], 3);
            gActors[3].info.hitbox = LOAD_ASSET(gHitboxNone);
            break;
        case 2017:
            D_ctx_80177830 = 0;
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
            D_game_80161A44 = 30000.0f;
            player->unk_240 = 1;
            func_8001CA24(0);
            AUDIO_PLAY_SFX(0x01008016, player->sfxSource, 0);
            break;
        case 2310:
            gActors[3].state++;
            break;
        case 2440:
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 60);
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 60);
            break;
    }

    if (player->timer_210 != 0) {
        player->timer_210--;
        Math_SmoothStepToF(&player->unk_114, -player->unk_118, 0.03f, 0.5f, 0.0001f);
        Math_SmoothStepToF(&player->unk_0B4, D_ctx_80177D08 * .3f, 0.1f, 2.0f, 0.0001f);
        D_ctx_801779E4 = Math_SmoothStepToF(&player->unk_0AC, player->unk_0B8, 0.1f, player->unk_0B4, 0.0001f);
        D_ctx_801779F4 = Math_SmoothStepToF(&player->unk_0B0, player->unk_0BC, 0.1f, player->unk_0B4, 0.0001f);
    } else {
        Math_SmoothStepToF(&player->unk_114, 0.0f, 0.03f, 0.5f, 0.0001f);
    }
    Math_SmoothStepToF(&player->camEye.x, gCsCamEyeX, D_ctx_80177A48[0], 20000.0f, 0);
    Math_SmoothStepToF(&player->camEye.y, gCsCamEyeY, D_ctx_80177A48[0], 20000.0f, 0);
    Math_SmoothStepToF(&player->camEye.z, gCsCamEyeZ, D_ctx_80177A48[0], 20000.0f, 0);
    Math_SmoothStepToF(&player->camAt.x, gCsCamAtX, D_ctx_80177A48[0], 20000.0f, 0);
    Math_SmoothStepToF(&player->camAt.y, gCsCamAtY, D_ctx_80177A48[0], 20000.0f, 0);
    Math_SmoothStepToF(&player->camAt.z, gCsCamAtZ, D_ctx_80177A48[0], 20000.0f, 0);
    player->camAt.y += zeroVar;
    if (player->unk_1D0 >= 6) {
        player->camEye.y += gCameraShakeY * 10.0f;
    }
    if (gCsFrameCount > 2500) {
        gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
        gFillScreenAlphaTarget = 255;
        if (gFillScreenAlpha == 255) {
            player->state_1C8 = PLAYERSTATE_1C8_6;
            D_ctx_8017837C = 4;
            func_play_800A6148();
            Audio_FadeOutAll(10);
            D_play_800D3180[LEVEL_MACBETH] = Play_CheckMedalStatus(150) + 1;
        }
    }
}

void Macbeth_801B28BC(Actor* actor) {
    Vec3f sp5C;
    Vec3f sp50;
    Vec3f sp44;
    Player* player;
    f32 sp3C;

    player = &gPlayer[0];
    actor->fwork[7] += 3.0f;
    actor->unk_0F4.z = SIN_DEG(actor->fwork[7]) * 1.5f;
    actor->fwork[8] += 2.0f;
    sp3C = SIN_DEG(actor->fwork[8]) * 10.0f;

    switch (actor->state) {
        case 10:
            actor->fwork[3] += D_i5_801BA864;
            Matrix_RotateY(gCalcMatrix, actor->fwork[3] * M_DTOR, 0);
            sp5C.x = 0.0f;
            sp5C.y = D_i5_801BA884;
            sp5C.z = D_i5_801BA894[4];
            Math_SmoothStepToF(&D_i5_801BA894[4], 100.0f, 0.05f, 0.5f, 0.01f);
            Matrix_MultVec3f(gCalcMatrix, &sp5C, &sp44);
            actor->fwork[0] = sp44.x;
            actor->fwork[1] = sp44.y;
            actor->fwork[2] = sp44.z - 100.0f;
            Math_SmoothStepToF(&actor->obj.rot.z, SIN_DEG(actor->fwork[3]) * -30.0f, 0.1f, 2.0f, 0.0f);
            Math_SmoothStepToF(&actor->obj.pos.x, actor->fwork[0] + player->pos.x, 0.03f, 10.0f, 0.0f);
            Math_SmoothStepToF(&actor->obj.pos.y, actor->fwork[1] + player->pos.y + sp3C, 0.03f, 10.0f, 0.0f);
            Math_SmoothStepToF(&actor->obj.pos.z, actor->fwork[2] + player->unk_138, 0.03f, 10.0f, 0.0f);
            break;
        case 11:
            AUDIO_PLAY_SFX(0x09000002, actor->sfxSource, 0);
            actor->timer_0BC = 10;
            actor->state++;
            actor->fwork[29] = 5.0f;
            /* fallthrough */
        case 12:
            Math_SmoothStepToF(&actor->obj.rot.z, 0.0f, 0.1f, 2.0f, 0.0f);
            Math_SmoothStepToF(&actor->obj.pos.x, player->pos.x - 150.0f, 0.1f, 1.0f, 0.0f);
            actor->iwork[11] = 2;
            Math_SmoothStepToF(&actor->fwork[9], 20.0f, 0.1f, 2.0f, 0.0f);
            Math_SmoothStepToF(&actor->obj.rot.z, 0.0f, 0.1f, 1.0f, 0.0f);
            if (actor->timer_0BC <= 0) {
                actor->timer_0BC = 10;
                actor->state++;
            }
            break;
        case 13:
            Math_SmoothStepToF(&actor->obj.pos.x, player->pos.x - 150.0f, 0.1f, 2.0f, 0.0f);
            Math_SmoothStepToF(&actor->obj.rot.x, -120.0f, 0.1f, 5.0f, 0.0f);
            Math_SmoothStepToF(&actor->fwork[9], -20.0f, 0.05f, 0.2f, 0.0f);
            actor->fwork[29] = 3.0f;
            if (actor->timer_0BC <= 0) {
                actor->state++;
            }
            break;
        case 14:
            Math_SmoothStepToF(&actor->obj.pos.x, player->pos.x - 150.0f, 0.1f, 3.0f, 0.0f);
            Math_SmoothStepToF(&actor->obj.rot.x, -120.0f, 0.1f, 5.0f, 0.0f);
            Math_SmoothStepToF(&actor->fwork[9], 22.0f, 0.05f, 0.2f, 0.0f);
            if (actor->obj.rot.x <= -115.0f) {
                Math_SmoothStepToF(&actor->obj.rot.z, 800.0f, 0.1f, 18.0f, 0.0f);
                Matrix_RotateY(gCalcMatrix, actor->obj.rot.y * M_DTOR, 0);
                Matrix_RotateX(gCalcMatrix, actor->obj.rot.x * M_DTOR, 1);
                Matrix_RotateZ(gCalcMatrix, actor->obj.rot.z * M_DTOR, 1);
                sp5C.x = 0.0f;
                sp5C.y = 70.0f;
                sp5C.z = -70.0f;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp5C, &sp44);
                func_effect_80078E50(actor->obj.pos.x + sp44.x, actor->obj.pos.y + sp44.y, actor->obj.pos.z + sp44.z,
                                     3.1f);
            }
            break;
        case 15:
            Math_SmoothStepToAngle(&actor->obj.rot.z, 0.0f, 0.05f, 0.05f, 0);
            Math_SmoothStepToAngle(&actor->obj.rot.y, 180.0f, 1.0f, 0.3f, 0);
            Math_SmoothStepToF(&actor->obj.pos.y, player->pos.y + 240.0f, 0.03f, 20.0f, 0.0f);
            if (actor->obj.rot.y == 180.0f) {
                actor->state++;
            }
            break;
        case 16:
            actor->fwork[0] += 2.0f;
            actor->obj.rot.y = 180.0f - actor->fwork[0];
            Math_SmoothStepToAngle(&actor->obj.rot.z, 62.0f, 1.0f, 0.5f, 0);
            if (actor->fwork[0] > 180.0f) {
                actor->state++;
                AUDIO_PLAY_SFX(0x09000002, actor->sfxSource, 0);
                actor->timer_0BC = 160;
                actor->fwork[29] = 5.0f;
            }
            break;
        case 17:
            Math_SmoothStepToAngle(&actor->obj.rot.y, 345.0f, 1.0f, 0.5f, 0.01f);
            Math_SmoothStepToAngle(&actor->obj.rot.x, 328.0f, 0.1f, 1.0f, 0.0f);
            Math_SmoothStepToF(&actor->fwork[9], 35.0f, 0.1f, 0.5f, 0.0f);
            actor->fwork[29] = 3.0f;
            Math_SmoothStepToF(&actor->obj.rot.z, 405.0f, 0.1f, 10.0f, 0.0f);
            if (actor->timer_0BC == 0) {
                Matrix_RotateY(gCalcMatrix, actor->obj.rot.y * M_DTOR, 0);
                Matrix_RotateX(gCalcMatrix, actor->obj.rot.x * M_DTOR, 1);
                Matrix_RotateZ(gCalcMatrix, actor->obj.rot.z * M_DTOR, 1);
                sp5C.x = 0.0f;
                sp5C.y = 70.0f;
                sp5C.z = -70.0f;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp5C, &sp44);
                func_effect_80078E50(actor->obj.pos.x + sp44.x, actor->obj.pos.y + sp44.y, actor->obj.pos.z + sp44.z,
                                     3.1f);
            }
            break;
        case 20:
            Math_SmoothStepToAngle(&actor->obj.rot.x, 345.0f, 0.01f, actor->fwork[4], 0.0f);
            Math_SmoothStepToF(&actor->vel.z, -300.0f, 0.1f, 0.25f, 0.0f);
            break;
        case 21:
            Math_SmoothStepToF(&actor->obj.rot.z, 0.0f, 0.1f, 0.25f, 0.0f);
            Math_SmoothStepToF(&actor->obj.pos.x, player->pos.x, 0.1f, 5.0f, 0.0f);
            Math_SmoothStepToF(&actor->obj.pos.y, 800.0f, 0.1f, 10.0f, 0.0f);
            break;
        case 22:
            Math_SmoothStepToAngle(&actor->fwork[4], 0.25f, 0.1f, 0.005f, 0.0f);
            Math_SmoothStepToAngle(&actor->obj.rot.x, 345.0f, 0.01f, actor->fwork[4], 0.0f);
            break;
        case 30:
            actor->fwork[3] += D_i5_801BA854[actor->index];
            Matrix_RotateY(gCalcMatrix, actor->fwork[3] * M_DTOR, 0);
            sp5C.x = 0.0f;
            sp5C.y = D_i5_801BA874[actor->index];
            sp5C.z = D_i5_801BA894[actor->index];
            Math_SmoothStepToF(&D_i5_801BA894[actor->index], 250.0f, 0.05f, 0.5f, 0.01f);
            Matrix_MultVec3f(gCalcMatrix, &sp5C, &sp44);
            actor->fwork[0] = sp44.x;
            actor->fwork[1] = sp44.y;
            actor->fwork[2] = sp44.z - 100.0f;
            Math_SmoothStepToF(&actor->obj.rot.z, SIN_DEG(actor->fwork[3]) * -30.0f, 0.1f, 2.0f, 0.0f);
            Math_SmoothStepToF(&actor->obj.pos.x, actor->fwork[0] + player->pos.x, 0.03f, 10.0f, 0.0f);
            Math_SmoothStepToF(&actor->obj.pos.y, actor->fwork[1] + player->pos.y + sp3C, 0.03f, 10.0f, 0.0f);
            Math_SmoothStepToF(&actor->obj.pos.z, actor->fwork[2] + player->unk_138, 0.03f, 10.0f, 0.0f);
            break;
        case 31:
            AUDIO_PLAY_SFX(0x09000002, actor->sfxSource, 0);
            actor->unk_0C9 = 0;
            actor->timer_0BC = 20;
            actor->state++;
            actor->fwork[29] = 5.0f;
            /* fallthrough */
        case 32:
            if (actor->timer_0BC <= 0) {
                actor->unk_0C9 = 1;
            }
            actor->iwork[11] = 2;
            Math_SmoothStepToF(&actor->obj.rot.x, -20.0f, 0.1f, 0.5f, 0.0f);
            Math_SmoothStepToF(&actor->fwork[9], 25.0f, 0.1f, 2.0f, 0.0f);
            Math_SmoothStepToF(&actor->obj.rot.z, 0.0f, 0.1f, 0.5f, 0.0f);
            break;
    }
    Matrix_RotateY(gCalcMatrix, actor->obj.rot.y * M_DTOR, 0);
    Matrix_RotateX(gCalcMatrix, actor->obj.rot.x * M_DTOR, 1);
    sp5C.x = 0.0f;
    sp5C.y = 0.0f;
    sp5C.z = actor->fwork[9];
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp5C, &sp50);
    actor->vel.x = sp50.x;
    actor->vel.y = sp50.y;
    actor->vel.z = sp50.z;
}

static f32 D_i5_801BA8B4[5] = { -100.0f, 380.0f, -450.0f, 0.0f, -340.0f };

static f32 D_i5_801BA8C8[5] = { 500.0f, 400.0f, 850.0f, 650.0f, 950.0f };

static f32 D_i5_801BA8DC[5] = { 500.0f, 500.0f, 600.0f, 2500.0f, 590.0f };

static f32 D_i5_801BA8F0[4] = { 90.0f, -90.0f, 0.0f, 0.0f };

void Macbeth_801B3554(Actor* actor, s32 arg1) {
    Player* player;

    player = &gPlayer[0];
    Actor_Initialize(actor);
    actor->obj.pos.x = player->pos.x + D_i5_801BA8B4[arg1];
    actor->obj.pos.y = player->pos.y + D_i5_801BA8C8[arg1];
    actor->obj.pos.z = player->pos.z + D_i5_801BA8DC[arg1];
    actor->fwork[7] = RAND_FLOAT(360.0f);
    actor->fwork[8] = RAND_FLOAT(360.0f);
    actor->vel.x = player->vel.x;
    actor->vel.y = player->vel.y;
    actor->vel.z = player->vel.z;
    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_195;
    actor->obj.rot.y = 180.0f;
    Object_SetInfo(&actor->info, actor->obj.id);
    if (arg1 < 3) {
        actor->iwork[11] = 1;
        actor->unk_0C9 = 1;
        actor->fwork[3] = D_i5_801BA8F0[arg1];
        actor->state = 30;
        AUDIO_PLAY_SFX(0x3100000C, actor->sfxSource, 4);
        return;
    }
    actor->unk_0B6 = 1;
    actor->state = 20;
    AUDIO_PLAY_SFX(0x11030010, actor->sfxSource, 0);
    actor->fwork[9] = 20.0f;
}

static f32 D_i5_801BA900 = 90.0f;

void Macbeth_801B3718(void) {
    Actor* actor = &gActors[8];

    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_195;
    actor->obj.pos.x = gPlayer[0].pos.x + D_i5_801BA8B4[4];
    actor->obj.pos.y = gPlayer[0].pos.y + D_i5_801BA8C8[4];
    actor->obj.pos.z = gPlayer[0].pos.z + D_i5_801BA8DC[4];
    actor->vel.x = gPlayer[0].vel.x;
    actor->vel.y = gPlayer[0].vel.y;
    actor->vel.z = gPlayer[0].vel.z;
    actor->fwork[7] = RAND_FLOAT(360.0f);
    actor->fwork[8] = RAND_FLOAT(360.0f);
    actor->unk_0F4.y = 180.0f;
    actor->unk_0F4.x = 0.0f;
    actor->obj.rot.x = -0.0f;
    actor->obj.rot.y = actor->unk_0F4.y;
    actor->obj.rot.z = -actor->unk_0F4.z;
    actor->fwork[0] = 30.0f;
    actor->unk_0B6 = 24;
    actor->iwork[11] = 1;
    actor->state = 10;
    actor->fwork[3] = D_i5_801BA900;
    Object_SetInfo(&actor->info, actor->obj.id);
    AUDIO_PLAY_SFX(0x3100000C, actor->sfxSource, 4);
}

void Macbeth_801B38E0(void) {
    s16 i;
    s16 j;

    for (i = 0; i < 65; i++) {
        gRadarMarks[i].unk_00 = 0;
    }

    for (i = 0; i < 100; i++) {
        gTexturedLines[i].mode = 0;
    }

    for (i = 0; i < 50; i++) {
        if (gObjects80[i].obj.id <= OBJ_80_91 || gObjects80[i].obj.id >= OBJ_80_97) {
            Object_Kill(&gObjects80[i].obj, gObjects80[i].sfxSource);
            Object_80_Initialize(&gObjects80[i]);
        }
    }

    for (i = 0; i < 40; i++) {
        gSprites[i].obj.status = OBJ_FREE;
        Sprite_Initialize(&gSprites[i]);
    }

    for (i = 0; i < 60; i++) {
        Object_Kill(&gActors[i].obj, gActors[i].sfxSource);
        Actor_Initialize(&gActors[i]);
    }

    for (i = 0; i < 4; i++) {
        Object_Kill(&gBosses[i].obj, gBosses[i].sfxSource);
        Boss_Initialize(&gBosses[i]);
    }

    for (i = 0; i < 100; i++) {
        Object_Kill(&gEffects[i].obj, gEffects[i].sfxSource);
        Effect_Initialize(&gEffects[i]);
    }

    for (i = 0; i < 20; i++) {
        Object_Kill(&gItems[i].obj, gItems[i].sfxSource);
        Item_Initialize(&gItems[i]);
    }

    for (i = 0; i < 16; i++) {
        Object_Kill(&gPlayerShots[i].obj, gPlayerShots[i].sfxSource);
        PlayerShot_Initialize(&gPlayerShots[i]);
    }

    D_ctx_801782B8 = D_ctx_801782BC = D_ctx_801782C0 = D_ctx_801782D0 = gBossActive = D_ctx_8017828C = D_ctx_8017812C =
        D_ctx_80177E70 = D_ctx_80177E78 = gRingPassCount = 0;
    D_ctx_80177F10.x = D_ctx_80177F10.y = D_ctx_80177F10.z = D_ctx_80177E88.x = D_ctx_80177E88.y = D_ctx_80177E88.z =
        0.0f;

    for (i = 0; i < 10; i++) {
        gTeamArrowsViewPos[i].x = gTeamArrowsViewPos[i].y = gTeamArrowsViewPos[i].z = 100.0f;
    }

    for (i = 0; i < 2; i++) {
        D_ctx_80176550[i] = 0;
        for (j = 0; j < 100; j++) {
            D_ctx_80176878[i][j] = -5000.0f;
        }
    }
}

void Macbeth_801B3D04(Player* player) {
    f32 zeroVar = 0.0f;

    gCsCamEyeX = player->pos.x;
    gCsCamEyeY = player->pos.y;
    gCsCamEyeZ = player->pos.z + player->unk_144 + 50.0f;
    switch (player->unk_1D0) {
        case 0:
            gCsFrameCount = gBossActive = D_ctx_80178488 = 1;
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
            player->unk_1D0++;
            /* fallthrough */
        case 1:
            D_i5_801BE240 = 2000.0f;
            D_i5_801BE244 = 2000.0f;
            D_i5_801BE248 = 2000.0f;
            Math_SmoothStepToF(D_ctx_80177A48, 0.1f, 1.0f, 0.01f, 0.0f);
            Math_SmoothStepToF(&player->unk_0D0, 4.9f, 0.1f, 1.0f, 0.0f);
            Math_SmoothStepToF(&player->unk_08C, 0.0f, 0.1f, 1.0f, 0.0f);
            gCsCamEyeX = player->pos.x;
            gCsCamEyeY = player->pos.y;
            gCsCamEyeZ = player->pos.z + player->unk_144 + 50.0f;
            if (gCsCamEyeY < 5.0f) {
                gCsCamEyeY = 5.0f;
            }
            gCsCamAtX = player->pos.x;
            gCsCamAtY = player->pos.y + 30.0f;
            gCsCamAtZ = player->pos.z + player->unk_144;
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
                player->camEye.x = gCsCamEyeX = 0.0f;
                player->camEye.y = gCsCamEyeY = 21.182106f;
                player->camEye.z = gCsCamEyeZ = -112.08748f;
                player->camAt.x = gCsCamAtX = 0.0f;
                player->camAt.y = gCsCamAtY = 22.873417f;
                player->camAt.z = gCsCamAtZ = -283.55914f;
                player->unk_1D0++;
                player->pos.x = 0.0f;
                player->pos.y = -3.0f;
                player->unk_08C = 0.0f;
                Macbeth_801B38E0();
            }
            func_tank_80045130(player);
            func_tank_80044868(player);
            func_tank_80045678(player);
            func_tank_80045E7C(player);
            func_play_800A8BA4(player);
            func_play_800ADF58(player);
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
                    player->unk_1D0 = 10;
                }
            }
            func_tank_80045130(player);
            func_tank_80044868(player);
            func_tank_80045678(player);
            func_tank_80045E7C(player);
            func_play_800A8BA4(player);
            func_play_800ADF58(player);
            break;
        case 10:
            player->unk_1D0 = 11;
            player->unk_0D4 = 3.0f;
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
            Math_SmoothStepToF(&player->unk_0D0, 4.9f, 0.1f, 1.0f, 0.0f);
            Math_SmoothStepToF(&player->unk_08C, 0.0f, 0.1f, 1.0f, 0.0f);
            func_tank_80045130(player);
            func_tank_80044868(player);
            func_tank_80045678(player);
            func_tank_80045E7C(player);
            func_play_800A8BA4(player);
            func_play_800ADF58(player);
            break;
        case 12:
            break;
    }
    switch (gCsFrameCount) {
        case 755:
            D_ctx_80177830 = 1;
            break;
        case 1025:
            D_ctx_80177830 = 0;
            break;
        case 50:
            AUDIO_PLAY_BGM(SEQ_ID_GOOD_END);
            break;
        case 100:
            gLevelClearScreenTimer = 100;
            break;
        case 160:
            Radio_PlayMessage(gMsg_ID_20010, RCID_FOX);
            break;
        case 230:
            if (gTeamShields[TEAM_ID_SLIPPY] > 0.0f) {
                Macbeth_801B3554(&gActors[0], 0);
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
                    func_demo_80048AC0(2);
                    break;
            }
            break;
        case 380:
            if (gTeamShields[TEAM_ID_PEPPY] > 0.0f) {
                Macbeth_801B3554(&gActors[1], 1);
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
                    func_demo_80048AC0(3);
                    break;
            }
            break;
        case 530:
            if (gTeamShields[TEAM_ID_FALCO] > 0.0f) {
                Macbeth_801B3554(&gActors[2], 2);
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
                    func_demo_80048AC0(1);
                    break;
            }
            break;
        case 680:
            if (D_play_800D3180[LEVEL_ZONESS] != 0) {
                Macbeth_801B3718();
            }
            break;
        case 1027:
            if (D_play_800D3180[LEVEL_ZONESS] != 0) {
                Radio_PlayMessage(gMsg_ID_17350, RCID_KATT);
            }
            break;
        case 1065:
            if (D_play_800D3180[LEVEL_ZONESS] != 0) {
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
            if (D_play_800D3180[LEVEL_ZONESS] != 0) {
                Object_Kill(&gActors[8].obj, gActors[8].sfxSource);
            }
            /* fallthrough */
        case 1195:
            gOverlayStage = 1;
            break;
        case 1200:
            Macbeth_801B3554(&gActors[3], 3);
            D_ctx_80178488 = 0;
            break;
    }
    Math_SmoothStepToF(&player->camEye.x, gCsCamEyeX, D_ctx_80177A48[0], D_i5_801BE240, 0.0f);
    Math_SmoothStepToF(&player->camEye.y, gCsCamEyeY, D_ctx_80177A48[0], D_i5_801BE244, 0.0f);
    Math_SmoothStepToF(&player->camEye.z, gCsCamEyeZ, D_ctx_80177A48[0], D_i5_801BE248, 0.0f);
    Math_SmoothStepToF(&player->camAt.x, gCsCamAtX, D_ctx_80177A48[0], D_i5_801BE240, 0.0f);
    Math_SmoothStepToF(&player->camAt.y, gCsCamAtY, D_ctx_80177A48[0], D_i5_801BE244, 0.0f);
    Math_SmoothStepToF(&player->camAt.z, gCsCamAtZ, D_ctx_80177A48[0], D_i5_801BE248, 0.0f);
    player->camAt.y += zeroVar;

    if ((gCsFrameCount >= 850) && ((gGameFrameCount % 16) == 0)) {
        Macbeth_801ACF6C();
    }
    if (gCsFrameCount == 1220) {
        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 60);
        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 60);
    }
    if (gCsFrameCount > 1280) {
        gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
        gFillScreenAlphaTarget = 255;
        if (gFillScreenAlpha == 255) {
            player->state_1C8 = PLAYERSTATE_1C8_6;
            D_ctx_8017837C = 4;
            func_play_800A6148();
            Audio_FadeOutAll(10);
            D_play_800D3180[LEVEL_MACBETH] = Play_CheckMedalStatus(150) + 1;
        }
    }
}
