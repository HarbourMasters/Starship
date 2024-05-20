#include "macros.h"
#include "variables.h"
#include "assets/ast_aquas.h"
#include "assets/ast_bolse.h"
#include "assets/ast_meteo.h"
#include "assets/ast_corneria.h"
#include "assets/ast_macbeth.h"
#include "assets/ast_venom_2.h"
#include "assets/ast_fortuna.h"
#include "assets/ast_sector_y.h"
#include "assets/ast_sector_z.h"
#include "assets/ast_versus.h"
#include "assets/ast_zoness.h"

static Vec3f D_800D2920[16] = {
    { 1075.0f, 0.0f, 0.0f },   { 746.0f, 0.0f, -746.0f },    { 202.0f, 361.0f, -202.0f }, { 0.0f, 0.0f, -1075.0f },
    { 291.0f, 558.0f, 0.0f },  { 0.0f, 354.0f, -291.0f },    { 202.0f, 594.0f, 202.0f },  { 772.0f, 0.0f, 622.0f },
    { 0.0f, 473.0f, 291.0f },  { 144.0f, 0.0f, 1075.0f },    { -202.0f, 461.0f, 202.0f }, { -515.0f, 0.0f, 746.0f },
    { -291.0f, 453.0f, 0.0f }, { -372.0f, 390.0f, -281.0f }, { -951.0f, 0.0f, 0.0f },     { -746.0f, 0.0f, -746.0f },
};
static Triangle D_800D29E0[22] = {
    { 0, 1, 2 },  { 2, 1, 3 },   { 4, 2, 5 },   { 3, 5, 2 },    { 2, 4, 0 },    { 4, 6, 7 },
    { 7, 0, 4 },  { 6, 4, 5 },   { 7, 6, 8 },   { 8, 9, 7 },    { 8, 10, 11 },  { 10, 8, 6 },
    { 11, 9, 8 }, { 12, 10, 6 }, { 6, 13, 12 }, { 14, 12, 13 }, { 10, 12, 14 }, { 14, 11, 10 },
    { 5, 13, 6 }, { 5, 3, 15 },  { 15, 13, 5 }, { 13, 15, 14 },
};
static Triangle D_800D2A64[13] = {
    { 0, 1, 2 }, { 2, 3, 4 }, { 2, 5, 0 }, { 4, 5, 2 }, { 4, 3, 6 },  { 4, 7, 5 },  { 8, 7, 4 },
    { 4, 6, 8 }, { 7, 8, 9 }, { 0, 7, 9 }, { 5, 7, 0 }, { 9, 10, 0 }, { 10, 1, 0 },
};
static Vec3f D_800D2AB4[11] = {
    { -218.0f, 131.0f, 0.0f }, { -435.0f, 0.0f, 0.0f },     { -336.0f, 0.0f, 218.0f },  { 0.0f, 0.0f, 435.0f },
    { 0.0f, 160.0f, 218.0f },  { -168.0f, 131.0f, 109.0f }, { 336.0f, 0.0f, 218.0f },   { 0.0f, 174.0f, 0.0f },
    { 435.0f, 0.0f, -204.0f }, { 0.0f, 0.0f, -435.0f },     { -318.0f, 0.0f, -218.0f },
};

CollisionHeader D_800D2B38[10] = {
    {
        { -1128.0f, -1835.0f, -1202.0f },
        { 997.0f, 139.0f, 1360.0f },
        ARRAY_COUNT(D_ME_602FA9C),
        D_ME_602FA9C,
        D_ME_60300C8,
    },
    {
        { -3006.0f, -2274.0f, -4530.0f },
        { 3015.0f, 3348.0f, 5246.0f },
        ARRAY_COUNT(D_ME_60305DC),
        D_ME_60305DC,
        D_ME_603184C,
    },
    {
        { -152.0f, -200.0f, -152.0f },
        { 165.0f, 204.0f, 181.0f },
        ARRAY_COUNT(D_ME_6030208),
        D_ME_6030208,
        D_ME_6030550,
    },
    {
        { -1704.0f, -1006.0f, -4751.0f },
        { 1704.0f, 1030.0f, 4842.0f },
        ARRAY_COUNT(D_SY_6033070),
        D_SY_6033070,
        D_SY_6033E08,
    },
    {
        { -1308.0f, 0.0f, -1460.0f },
        { 1310.0f, 666.0f, 807.0f },
        ARRAY_COUNT(D_FO_600F60C),
        D_FO_600F60C,
        D_FO_600FD50,
    },
    {
        { -951.0f, 0.0f, -1075.0f },
        { 1075.0f, 1014.0f, 1075.0f },
        ARRAY_COUNT(D_FO_600F3F4),
        D_FO_600F3F4,
        D_FO_600F5AC,
    },
    {
        { -951.0f, 0.0f, -1075.0f },
        { 1075.0f, 384.0f, 1075.0f },
        ARRAY_COUNT(D_FO_600F1DC),
        D_FO_600F1DC,
        D_FO_600F394,
    },
    {
        { -1554.0f, -2.0f, -1401.0f },
        { 1554.0f, 590.0f, 1401.0f },
        ARRAY_COUNT(D_BO_6010294),
        D_BO_6010294,
        D_BO_601170C,
    },
    {
        { -1386.0f, -696.0f, -2274.0f },
        { 1386.0f, 1033.0f, 1833.0f },
        ARRAY_COUNT(D_SZ_6007558),
        D_SZ_6007558,
        D_SZ_6008E08,
    },
    {
        { -671.0f, 0.0f, -671.0f },
        { 671.0f, 648.0f, 671.0f },
        ARRAY_COUNT(D_VE2_6014FEC),
        D_VE2_6014FEC,
        D_VE2_6016374,
    },
};

CollisionHeader2 D_800D2CA0[19] = {
    {
        { -951.0f, 0.0f, -1075.0f },
        { 1075.0f, 594.0f, 1075.0f },
        ARRAY_COUNT(D_800D29E0),
        D_800D29E0,
        D_800D2920,
    },
    {
        { -1220.0f, 0.0f, -1315.0f },
        { 1403.0f, 174.0f, 1308.0f },
        ARRAY_COUNT(D_CO_603F338),
        D_CO_603F338,
        D_CO_603F388,
    },
    {
        { -1311.0f, 0.0f, -1120.0f },
        { 1266.0f, 1465.0f, 1266.0f },
        ARRAY_COUNT(D_CO_603F40C),
        D_CO_603F40C,
        D_CO_603F4E4,
    },
    {
        { -435.0f, -10.0f, -435.0f },
        { 435.0f, 174.0f, 435.0f },
        ARRAY_COUNT(D_800D2A64),
        D_800D2A64,
        D_800D2AB4,
    },
    {
        { -498.0f, -10.0f, -498.0f },
        { 498.0f, 705.0f, 498.0f },
        ARRAY_COUNT(D_versus_302EEE8),
        D_versus_302EEE8,
        D_versus_302EF00,
    },
    {
        { -1494.0f, -30.0f, -1494.0f },
        { 1494.0f, 2115.0f, 1494.0f },
        ARRAY_COUNT(D_versus_302EF6C),
        D_versus_302EF6C,
        D_versus_302EF84,
    },
    {
        { -623.0f, -10.0f, -623.0f },
        { 623.0f, 200.0f, 623.0f },
        ARRAY_COUNT(D_versus_302EFF0),
        D_versus_302EFF0,
        D_versus_302F008,
    },
    {
        { -488.0f, 0.0f, -568.0f },
        { 488.0f, 148.0f, 567.0f },
        ARRAY_COUNT(D_ZO_602CACC),
        D_ZO_602CACC,
        D_ZO_602CB80,
    },
    {
        { -900.0f, -110.0f, -1900.0f },
        { 900.0f, 190.0f, 100.0f },
        ARRAY_COUNT(D_MA_6030E74),
        D_MA_6030E74,
        D_MA_6030E80,
    },
    {
        { -900.0f, -100.0f, -1000.0f },
        { 900.0f, 250.0f, 100.0f },
        ARRAY_COUNT(D_MA_6030EB0),
        D_MA_6030EB0,
        D_MA_6030EBC,
    },
    {
        { -900.0f, -190.0f, -1900.0f },
        { 900.0f, 100.0f, 100.0f },
        ARRAY_COUNT(D_MA_6030EEC),
        D_MA_6030EEC,
        D_MA_6030EF8,
    },
    {
        { -500.0f, -250.0f, -1010.0f },
        { 500.0f, 100.0f, 100.0f },
        ARRAY_COUNT(D_MA_6030F28),
        D_MA_6030F28,
        D_MA_6030F34,
    },
    {
        { -1200.0f, 0.0f, -1800.0f },
        { 0.0f, 900.0f, 1500.0f },
        ARRAY_COUNT(D_MA_6030F64),
        D_MA_6030F64,
        D_MA_6030F7C,
    },
    {
        { -400.0f, 0.0f, -900.0f },
        { 400.0f, 0.0f, 0.0f },
        ARRAY_COUNT(D_MA_6030FC4),
        D_MA_6030FC4,
        D_MA_6030FD0,
    },
    {
        { -74.0f, 0.0f, -84.0f },
        { 74.0f, 125.0f, 84.0f },
        ARRAY_COUNT(D_AQ_60320B8),
        D_AQ_60320B8,
        D_AQ_603216C,
    },
    {
        { -1200.0f, 0.0f, -1315.0f },
        { 1403.0f, 200.0f, 1308.0f },
        ARRAY_COUNT(D_AQ_6031FB0),
        D_AQ_6031FB0,
        D_AQ_6031FE0,
    },
    {
        { -600.0f, 0.0f, -657.0f },
        { 701.0f, 100.0f, 654.0f },
        ARRAY_COUNT(D_AQ_6031FB0),
        D_AQ_6031FB0,
        D_AQ_603204C,
    },
    {
        { -2965.0f, -16.0f, -2965.0f },
        { 2965.0f, 544.0f, 2965.0f },
        ARRAY_COUNT(D_versus_302F044),
        D_versus_302F044,
        D_versus_302F098,
    },
    {
        { -814.0f, 0.0f, -691.0f },
        { 814.0f, 752.0f, 691.0f },
        ARRAY_COUNT(D_AQ_6032388),
        D_AQ_6032388,
        D_AQ_6032430,
    },
};
